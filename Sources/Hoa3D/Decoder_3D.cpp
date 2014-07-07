/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Decoder_3D.h"

namespace Hoa3D
{
	DecoderStandard::DecoderStandard(unsigned int order, unsigned int numberOfChannels) : Ambisonic(order), Planewaves(numberOfChannels)
	{
        m_harmonics_vector          = new double[m_number_of_harmonics];
        m_decoder_matrix            = new double[m_number_of_channels * m_number_of_harmonics];
        m_decoder_matrix_float      = new float[m_number_of_channels * m_number_of_harmonics];
        m_encoder                   = new Encoder(m_order);
        setChannelsPosition(m_channels_azimuth, m_channels_elevation);
	}
	
	void DecoderStandard::setChannelPosition(unsigned int index, double azimuth, double elevation)
	{
        Planewaves::setChannelPosition(index, azimuth, elevation);
        
        m_encoder->setAzimuth(m_channels_rotated_azimuth[index]);
        m_encoder->setElevation(m_channels_rotated_elevation[index]);
        m_encoder->process(12.5 / (double)((m_order+1.)*(m_order+1.)), m_harmonics_vector);
        
        for(unsigned int j = 0; j < m_number_of_harmonics; j++)
        {
            m_decoder_matrix_float[index * m_number_of_harmonics + j] = m_decoder_matrix[index * m_number_of_harmonics + j] = m_harmonics_vector[j] * m_encoder->getNormalization(j) * m_encoder->getNormalization(j);
        }
	}
    
    void DecoderStandard::setChannelsPosition(double* azimuths, double* elevations)
	{
        for(unsigned int i = 0; i < m_number_of_channels; i++)
            setChannelPosition(i, azimuths[i], elevations[i]);
	}
    
    void DecoderStandard::setChannelsRotation(double axis_x, double axis_y, double axis_z)
    {
        Planewaves::setChannelsRotation(axis_x, axis_y, axis_z);
        setChannelsPosition(m_channels_azimuth, m_channels_elevation);
    }
	
	void DecoderStandard::process(const float* input, float* output)
	{
		cblas_sgemv(CblasRowMajor, CblasNoTrans, m_number_of_channels, m_number_of_harmonics, 1.f, m_decoder_matrix_float, m_number_of_harmonics, input, 1, 0.f, output, 1);
	}
	
	void DecoderStandard::process(const double* input, double* output)
	{
		cblas_dgemv(CblasRowMajor, CblasNoTrans, m_number_of_channels, m_number_of_harmonics, 1., m_decoder_matrix, m_number_of_harmonics, input, 1, 0., output, 1);
	}
	
	DecoderStandard::~DecoderStandard()
	{
		delete [] m_decoder_matrix;
        delete [] m_decoder_matrix_float;
        delete [] m_harmonics_vector;
        delete m_encoder;
	}
	
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Decoder Binaural //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    unsigned int hoa_number_binaural_configs    = 4;
    unsigned int hoa_number_binaural_elevation  = 14;
    unsigned int hoa_binaural_configs[] = {
        4, 0,  8, 24,
        0, 6,  0,  28,
        0, 0,  12, 32,
        0, 0,  0,  34,
        8, 12, 18, 36,
        0, 0,  0,  34,
        0, 0,  12, 32,
        0, 6,  0,  28,
        4, 0,  8, 24,
        0, 0,  0,  20,
        0, 4,  4,  14,
        0, 0,  0,  8,
        0, 0,  0,  4,
        1, 1,  1,  1};
    /*
    unsigned int hoa_binaural_configs[] = {
        0, 0,  0, 0,
        0, 8,  0,  0,
        0, 0,  0, 0,
        0, 0,  0,  0,
        9, 12, 18, 18,
        0, 0,  0,  0,
        0, 0,  0, 0,
        0, 8,  0,  0,
        4, 0,  0, 0,
        0, 0,  0,  0,
        0, 4,  0,  0,
        0, 0,  0,  0,
        0, 0,  0,  0,
        1, 1,  0,  0};
    */
    unsigned int hoa_number_binaural_samplerate = 4;
    unsigned int hoa_binaural_samplerate[]      = {44100, 48000, 88200, 96000};
    unsigned int hoa_binaural_impulse_sizes[]   = {128, 142, 256, 286};
    unsigned int hoa_binaural_crop[]            = {36, 40, 64, 80};
    
    DecoderBinaural::DecoderBinaural(unsigned int order) : Ambisonic(order), Planewaves(2)
    {
        if(m_order > 16)
            m_order  = 16;
        
        m_configuration             = 0;
        m_vector_size               = 0;
        m_sample_rate               = 0;
        m_impulses_loaded           = 0;
        m_matrix_allocated          = 0;
        m_impulses_matrix           = NULL;
        m_input_matrix              = NULL;
        m_result_matrix             = NULL;
        m_linear_vector_left        = NULL;
        m_linear_vector_right       = NULL;
        m_pinna_size                = Small;
        m_configuration             = 0;
        
        for(unsigned int i = 0; i < hoa_number_binaural_configs; i++)
        {
            unsigned int number_of_loudspeaker = 0;
            for (unsigned int j = 0; j < hoa_number_binaural_elevation; j++)
            {
                number_of_loudspeaker += hoa_binaural_configs[i + j * hoa_number_binaural_configs];
            }
            if(number_of_loudspeaker > (m_order * 1) * (m_order * 1))
            {
                m_number_of_virtual_channels = number_of_loudspeaker;
                m_configuration = i;
                break;
            }
        }
        
        m_impulses_vector   = new const float*[m_number_of_virtual_channels];
        m_harmonics_vector  = new float[m_number_of_harmonics];
        m_channels_vector   = new float[m_number_of_virtual_channels];
        m_channels_vector_double = new double[m_number_of_virtual_channels];
        m_decoder           = new DecoderStandard(m_order, m_number_of_virtual_channels);
        
        int nimpulse = 0;
        for(unsigned int i = 0; i < hoa_number_binaural_elevation; i++)
        {
            unsigned int n_elev_channels = hoa_binaural_configs[m_configuration + i * hoa_number_binaural_configs];
            for(unsigned int j = 0; j < n_elev_channels; j++)
            {
                m_decoder->setChannelPosition(nimpulse,
                                              (double)j / (double )n_elev_channels * HOA_2PI,
                                              ((double)i * 10. - 40.) / 360. * HOA_2PI);
                nimpulse++;
            }
        }
        
        // Other
        m_channels_azimuth[0] = HOA_PI2;
        m_channels_azimuth[1] = HOA_PI + HOA_PI2;
    }
    
    void DecoderBinaural::setChannelsRotation(double axis_x, double axis_y, double axis_z)
    {
        Planewaves::setChannelsRotation(axis_x, axis_y, axis_z);
    }
    
    void DecoderBinaural::setPinnaSize(PinnaSize pinnaSize)
    {
        if(m_pinna_size != pinnaSize || getState() == 0)
        {
            m_pinna_size = pinnaSize;
            unsigned int sample_rate = m_sample_rate;
            m_sample_rate = 0;
            setSampleRate(sample_rate);
        }
    }
    
    void DecoderBinaural::setSampleRate(unsigned int sampleRate)
    {
        int index;
        float value_left;
        float value_right;
		
        if(sampleRate != m_sample_rate)
        {
            m_impulses_loaded   = 0;
            m_sample_rate       = 0;
            for(unsigned int i = 0; i < hoa_number_binaural_samplerate; i++)
            {
                if(sampleRate == hoa_binaural_samplerate[i])
                {
                    index = i;
                    m_sample_rate   = hoa_binaural_samplerate[i];
                    m_impulses_size = hoa_binaural_impulse_sizes[i];
                }
            }
            if(!m_sample_rate)
            {
                index = 0;
                m_sample_rate       = hoa_binaural_samplerate[0];
                m_impulses_size     = hoa_binaural_impulse_sizes[0];
            }
            
            int nimpulse = 0;
            for(unsigned int i = 0; i < hoa_number_binaural_elevation; i++)
            {
                unsigned int n_elev_channels = hoa_binaural_configs[m_configuration + i * hoa_number_binaural_configs];
                for(unsigned int j = 0; j < n_elev_channels; j++)
                {
                    m_impulses_vector[nimpulse] = get_mit_hrtf_3D(m_sample_rate,
                                                                  (double)j / (double )n_elev_channels * 360.,
                                                                  i * 10 - 40,
                                                                  m_pinna_size) + hoa_binaural_crop[index];
                    
                    nimpulse++;
                }
            }
            
            if(m_impulses_matrix)
                delete [] m_impulses_matrix;
            
            m_impulses_matrix = new float[m_impulses_size * 2 * m_number_of_harmonics];
            
            for(unsigned int i = 0; i < m_number_of_harmonics; i++)
                m_harmonics_vector[i] = 0.;
            for(unsigned int i = 0; i < m_number_of_virtual_channels; i++)
                m_channels_vector[i] = 0.;
            
            m_harmonics_vector[0] = 1.;
            for(unsigned int i = 1; i < m_number_of_harmonics; i++)
            {
                m_harmonics_vector[i] = 0.;
            }
            
            for(unsigned int i = 0; i < m_number_of_harmonics; i++)
            {
                if(i != 0)
                {
                    m_harmonics_vector[i-1] = 0.;
                    m_harmonics_vector[i]   = 1.;
                }
                m_decoder->process(m_harmonics_vector, m_channels_vector);
                
                for(unsigned int j = 0; j < m_impulses_size; j++)
                {
                    value_left = 0;
                    value_right = 0;
                    
                    int nimpulse = 0;
                    for(unsigned int k = 0; k < hoa_number_binaural_elevation; k++)
                    {
                        int n_elev_channels = hoa_binaural_configs[m_configuration + k * hoa_number_binaural_configs];
                        
                        if(n_elev_channels)
                        {
                            int channel_offset = nimpulse + n_elev_channels;
                            value_left += m_channels_vector[nimpulse] * m_impulses_vector[nimpulse][j];
                            value_right += m_channels_vector[nimpulse] * m_impulses_vector[nimpulse][j];
                            nimpulse++;
                            for(unsigned int l = 1; l < n_elev_channels; l++)
                            {
                                value_left  += m_channels_vector[nimpulse] * m_impulses_vector[nimpulse][j];
                                value_right += m_channels_vector[nimpulse] * m_impulses_vector[channel_offset - l][j];
                                nimpulse++;
                            }
                        }
                        
                    }
                    
                    m_impulses_matrix[j * m_number_of_harmonics + i] = value_left;
                    m_impulses_matrix[(j + m_impulses_size) * m_number_of_harmonics + i] = value_right;
                }
            }
            
            m_impulses_loaded = 1;
        }
    }
    
    void DecoderBinaural::setVectorSize(unsigned int vectorSize)
    {
        if(m_vector_size != vectorSize)
        {
            m_matrix_allocated = 0;
            m_vector_size = vectorSize;
            
            if(m_input_matrix)
                delete [] m_input_matrix;
            m_input_matrix = NULL;
            if(m_result_matrix)
                delete [] m_result_matrix;
            m_result_matrix = NULL;
            if(m_linear_vector_left)
                delete [] m_linear_vector_left;
            m_linear_vector_left = NULL;
            if(m_linear_vector_right)
                delete [] m_linear_vector_right;
            m_linear_vector_right = NULL;
            
            m_input_matrix  = new float[m_number_of_harmonics * m_vector_size];
            m_result_matrix = new float[m_impulses_size * 2 * m_vector_size];
            m_linear_vector_left    = new float[m_vector_size + m_impulses_size - 1];
            m_linear_vector_right   = new float[m_vector_size + m_impulses_size - 1];
            
            memset(m_input_matrix, 0, m_number_of_harmonics * m_vector_size * sizeof(float));
            memset(m_result_matrix, 0, m_impulses_size * 2 * m_vector_size * sizeof(float));
            memset(m_linear_vector_left, 0, (m_vector_size + m_impulses_size - 1) * sizeof(float));
            memset(m_linear_vector_right, 0, (m_vector_size + m_impulses_size - 1) * sizeof(float));
            
            m_result_matrix_left    = m_result_matrix;
            m_result_matrix_right   = m_result_matrix + m_vector_size  * m_impulses_size;
            m_matrix_allocated = 1;
        }
    }
    
    void DecoderBinaural::process(const float* const* inputs, float** outputs)
	{
        unsigned int i;
        for(i = 0; i < m_number_of_harmonics; i++)
        {
            cblas_scopy(m_vector_size, inputs[i], 1,  m_input_matrix+i*m_vector_size, 1);
        }
        
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, (m_impulses_size * 2), m_vector_size, m_number_of_harmonics, 1.,
                    m_impulses_matrix, m_number_of_harmonics,
                    m_input_matrix,  m_vector_size,
                    0., m_result_matrix,  m_vector_size);
        
        for(i = 0; i < m_vector_size; i++)
        {
            cblas_saxpy(m_impulses_size, 1.f, m_result_matrix + i, m_vector_size, m_linear_vector_left + i, 1);
            outputs[0][i] = m_linear_vector_left[i];
        }
        
        for(i = 0; i < m_vector_size; i++)
        {
            cblas_saxpy(m_impulses_size, 1.f, m_result_matrix + i + m_vector_size * m_impulses_size, m_vector_size, m_linear_vector_right + i, 1);
            outputs[1][i] = m_linear_vector_right[i];
        }
        
        cblas_scopy(m_impulses_size-1, m_linear_vector_left+m_vector_size, 1, m_linear_vector_left, 1);
        cblas_scopy(m_impulses_size-1, m_linear_vector_right+m_vector_size, 1, m_linear_vector_right, 1);
        
#ifdef __APPLE__
        vDSP_vclr(m_linear_vector_left + m_impulses_size - 1, 1, m_vector_size);
        vDSP_vclr(m_linear_vector_right + m_impulses_size - 1, 1, m_vector_size);
#else
        memset(m_linear_vector_left + m_impulses_size - 1, 0, m_vector_size * sizeof(float));
        memset(m_linear_vector_right + m_impulses_size - 1, 0, m_vector_size * sizeof(float));
#endif
	}
    
	void DecoderBinaural::process(const double* const* inputs, double** outputs)
	{
        const double* input;
        for(unsigned int i = 0; i < m_number_of_harmonics; i++)
        {
            input = inputs[i];
            for(unsigned int j = 0; j < m_vector_size; j++)
            {
                m_input_matrix[i*m_vector_size+j] = input[j];
            }
        }
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, (m_impulses_size * 2), m_vector_size, m_number_of_harmonics, 1.,
                    m_impulses_matrix, m_number_of_harmonics,
                    m_input_matrix,  m_vector_size,
                    0., m_result_matrix,  m_vector_size);
        
        for(unsigned int j = 0; j < m_vector_size; j++)
        {
            cblas_saxpy(m_impulses_size, 1.f, m_result_matrix + j, m_vector_size, m_linear_vector_left + j, 1);
            outputs[0][j] = m_linear_vector_left[j];
        }
        
        for(unsigned int j = 0; j < m_vector_size; j++)
        {
            cblas_saxpy(m_impulses_size, 1.f, m_result_matrix + m_vector_size * m_impulses_size + j, m_vector_size, m_linear_vector_right  + j, 1);
            outputs[1][j] = m_linear_vector_right[j];
        }
        
        cblas_scopy(m_impulses_size-1, m_linear_vector_left + m_vector_size, 1, m_linear_vector_left, 1);
        cblas_scopy(m_impulses_size-1, m_linear_vector_right + m_vector_size, 1, m_linear_vector_right, 1);
        
#ifdef __APPLE__
        vDSP_vclr(m_linear_vector_left + m_impulses_size - 1, 1, m_vector_size);
        vDSP_vclr(m_linear_vector_right + m_impulses_size - 1, 1, m_vector_size);
#else
        memset(m_linear_vector_left + m_impulses_size - 1, 0, m_vector_size * sizeof(float));
        memset(m_linear_vector_right + m_impulses_size - 1, 0, m_vector_size * sizeof(float));
#endif
	}
    
	DecoderBinaural::~DecoderBinaural()
	{
        delete m_decoder;
        delete [] m_impulses_vector;
        delete [] m_harmonics_vector;
        delete [] m_channels_vector;
        delete [] m_channels_vector_double;
        
        if(m_impulses_matrix)
            delete [] m_impulses_matrix;
        if(m_input_matrix)
            delete [] m_input_matrix;
        m_input_matrix = NULL;
        if(m_result_matrix)
            delete [] m_result_matrix;
        m_result_matrix = NULL;
        if(m_linear_vector_left)
            delete [] m_linear_vector_left;
        m_linear_vector_left = NULL;
        if(m_linear_vector_right)
            delete [] m_linear_vector_right;
        m_linear_vector_right = NULL;
	}
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Decoder Multi //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    DecoderMulti::DecoderMulti(unsigned int order) : Ambisonic(order)
    {
        m_mode = Standard;
        m_decoder_regular   = new DecoderStandard(m_order, (m_order + 1) * (m_order + 1));
        m_decoder_binaural  = new DecoderBinaural(m_order);
    }
	
	DecoderMulti::DecoderMulti(unsigned int order, unsigned int numberOfChannels) : Ambisonic(order)
    {
        m_mode = Standard;
        m_decoder_regular   = new DecoderStandard(m_order, numberOfChannels);
        m_decoder_binaural  = new DecoderBinaural(m_order);
    }
    
    void DecoderMulti::setDecodingMode(Mode mode)
    {
        m_mode = mode;
    }
    
    void DecoderMulti::setNumberOfChannels(unsigned int numberOfChannels)
    {
        if(numberOfChannels != getNumberOfChannels())
        {
            if(m_mode == Standard)
            {
                delete m_decoder_regular;
                m_decoder_regular = new DecoderStandard(m_order, numberOfChannels);
            }
        }
    }
    
    void DecoderMulti::setChannelPosition(unsigned int index, double azimuth, double elevation)
    {
        if(m_mode == Standard)
        {
            m_decoder_regular->setChannelPosition(index, azimuth, elevation);
        }
    }
    
    void DecoderMulti::setChannelsPosition(double* azimuths, double* elevations)
    {
        if(m_mode == Standard)
        {
            m_decoder_regular->setChannelsPosition(azimuths, elevations);
        }
    }
    
    void DecoderMulti::setChannelsRotation(double axis_x, double axis_y, double axis_z)
    {
        m_decoder_regular->setChannelsRotation(axis_x, axis_y, axis_z);
        m_decoder_binaural->setChannelsRotation(axis_x, axis_y, axis_z);
    }
    
    void DecoderMulti::setPinnaSize(DecoderBinaural::PinnaSize pinnaSize)
    {
        m_decoder_binaural->setPinnaSize(pinnaSize);
    }
    
    void DecoderMulti::setSampleRate(unsigned int sampleRate)
    {
        m_decoder_binaural->setSampleRate(sampleRate);
        m_sample_rate = sampleRate;
    }
    
    void DecoderMulti::setVectorSize(unsigned int vectorSize)
    {
        m_decoder_binaural->setVectorSize(vectorSize);
        m_vector_size = vectorSize;
    }
    
	DecoderMulti::~DecoderMulti()
	{
        delete m_decoder_regular;
        delete m_decoder_binaural;
	}

}


