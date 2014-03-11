/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Decoder.h"

namespace Hoa2D
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Decoder Regular //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    DecoderRegular::DecoderRegular(unsigned int order, unsigned int numberOfChannels) : Ambisonic(order), Planewaves(numberOfChannels)
    {
        assert(numberOfChannels >= m_number_of_harmonics);
        
        m_harmonics_vector          = new double[m_number_of_harmonics];
        m_decoder_matrix            = new double[m_number_of_channels * m_number_of_harmonics];
        m_decoder_matrix_float      = new float[m_number_of_channels * m_number_of_harmonics];
        m_encoder                   = new Encoder(m_order);
        setChannelsOffset(0.);
    }
    
    void DecoderRegular::setChannelsOffset(double offset)
	{
        m_offset = wrap_twopi(offset);
        for(unsigned int i = 0; i < m_number_of_channels; i++)
        {
            m_encoder->setAzimuth(m_channels_azimuth[i] + m_offset);
            m_encoder->process(1., m_harmonics_vector);
            
            m_decoder_matrix_float[i * m_number_of_harmonics] = m_decoder_matrix[i * m_number_of_harmonics] = 0.5 / (double)(m_order + 1.);
            for(unsigned int j = 1; j < m_number_of_harmonics; j++)
            {
                m_decoder_matrix_float[i * m_number_of_harmonics + j] = m_decoder_matrix[i * m_number_of_harmonics + j] = m_harmonics_vector[j] / (double)(m_order + 1.);
            }
        }
	}

    void DecoderRegular::process(const float* input, float* output)
	{
		cblas_sgemv(CblasRowMajor, CblasNoTrans, m_number_of_channels, m_number_of_harmonics, 1.f, m_decoder_matrix_float, m_number_of_harmonics, input, 1, 0.f, output, 1);
	}
	
	void DecoderRegular::process(const double* input, double* output)
	{
		cblas_dgemv(CblasRowMajor, CblasNoTrans, m_number_of_channels, m_number_of_harmonics, 1.f, m_decoder_matrix, m_number_of_harmonics, input, 1, 0.f, output, 1);
	}
	
	DecoderRegular::~DecoderRegular()
	{
		delete [] m_decoder_matrix;
        delete [] m_decoder_matrix_float;
        delete [] m_harmonics_vector;
        delete m_encoder;
	}
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Decoder Irregular //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    DecoderIrregular::DecoderIrregular(unsigned int order, unsigned int numberOfChannels) : Ambisonic(order), Planewaves(numberOfChannels)
    {
        m_harmonics_vector          = new double[m_number_of_harmonics];
        m_decoder_matrix            = new double[m_number_of_channels * m_number_of_harmonics];
        m_decoder_matrix_float      = new float[m_number_of_channels * m_number_of_harmonics];
        m_encoder                   = new Encoder(m_order);
        m_offset = 0;
        setChannelAzimuth(0, 0.);
    }
    
    void DecoderIrregular::setChannelsOffset(double offset)
	{
        m_offset = wrap_twopi(offset);
        setChannelAzimuth(0, m_channels_azimuth[0]);
    }
    
    void DecoderIrregular::setChannelsAzimtuh(double* azimuths)
    {
        Planewaves::setChannelsAzimuth(azimuths);
        setChannelAzimuth(0, m_channels_azimuth[0]);
    }
    
    void DecoderIrregular::setChannelAzimuth(unsigned int index, double azimuth)
    {
        long    number_of_virutal_channels;
        double  current_distance, minimum_distance;
     
        Planewaves::setChannelAzimuth(index, azimuth);
        
        // Get the minimum distance between the channels
        minimum_distance    = HOA_2PI + 1;
        current_distance    = distance_radian(m_channels_azimuth[0], m_channels_azimuth[m_number_of_channels-1]);
        if(current_distance < minimum_distance)
            minimum_distance    = current_distance;
        for(unsigned int i = 1; i < m_number_of_channels; i++)
        {
            current_distance  = distance_radian(m_channels_azimuth[i], m_channels_azimuth[i-1]);
            if(current_distance < minimum_distance)
                minimum_distance = current_distance;
        }
        
        // Get the optimal number of virtual channels
        // Always prefer the number of harmonics + 2
        number_of_virutal_channels = (HOA_2PI / minimum_distance);
        if(number_of_virutal_channels < m_number_of_harmonics + 2)
        {
            number_of_virutal_channels = m_number_of_harmonics + 2;
        }
        
        for(unsigned int i = 0; i < m_number_of_channels * m_number_of_harmonics; i++)
        {
            m_decoder_matrix[i] = 0.;
            m_decoder_matrix_float[i] = 0.;
        }
        
        // Compute the decoding matrix for sorted channels
        for(unsigned int i = 0; i < number_of_virutal_channels; i++)
        {
            long   channel_index1 = 0, channel_index2 = 0;
            double factor_index1 = 0, factor_index2 = 0;
            
            // Get the pair of real channels corresponding to the virtual channel
            double angle = (double)i / (double)number_of_virutal_channels * HOA_2PI;
            
            for(unsigned int j = 0; j < m_number_of_channels; j++)
            {
                if(j < m_number_of_channels-1 && angle >= m_channels_azimuth[j] && angle <= m_channels_azimuth[j+1])
                {
                    channel_index1 = j;
                    channel_index2 = j+1;
                    
                    // Get the factor for the pair of real channels
                    double distance_index1 = angle - m_channels_azimuth[j];
                    double distance_index2 = m_channels_azimuth[j+1] - angle;
                    double distance_ratio = distance_index1 + distance_index2;
                    factor_index1   = cos(distance_index1 / (distance_ratio) * HOA_PI2);
                    factor_index2   = cos(distance_index2 / (distance_ratio) * HOA_PI2);
                }
                else if(angle >= m_channels_azimuth[m_number_of_channels-1] && angle <= m_channels_azimuth[0] + HOA_2PI)
                {
                    channel_index1 = m_number_of_channels-1;
                    channel_index2 = 0;
                        
                    // Get the factor for the pair of real channels
                    double distance_index1 = angle - m_channels_azimuth[m_number_of_channels-1];
                    double distance_index2 = HOA_2PI - angle + m_channels_azimuth[0];
                    double distance_ratio = distance_index1 + distance_index2;
                    factor_index1   = cos(distance_index1 / (distance_ratio) * HOA_PI2);
                    factor_index2   = cos(distance_index2 / (distance_ratio) * HOA_PI2);
                }
            }
            
            // Get the harmonics coefficients for virtual channel
            m_encoder->setAzimuth(angle + m_offset);
            m_encoder->process(1., m_harmonics_vector);
            
            m_decoder_matrix[channel_index1 * m_number_of_harmonics] += (0.5 / (double)(m_order + 1.)) * factor_index1;
            m_decoder_matrix[channel_index2 * m_number_of_harmonics] += (0.5 / (double)(m_order + 1.)) * factor_index2;
            for(unsigned int j = 1; j < m_number_of_harmonics; j++)
            {
                m_decoder_matrix[channel_index1 * m_number_of_harmonics + j] += (m_harmonics_vector[j] / (double)(m_order + 1.)) * factor_index1;
                m_decoder_matrix[channel_index2 * m_number_of_harmonics + j] += (m_harmonics_vector[j] / (double)(m_order + 1.)) * factor_index2;
            }
            
            for(unsigned int i = 0; i < m_number_of_channels * m_number_of_harmonics; i++)
            {
                m_decoder_matrix_float[i] = m_decoder_matrix[i];
            }
        }
    }
    
    void DecoderIrregular::process(const float* input, float* output)
	{
		cblas_sgemv(CblasRowMajor, CblasNoTrans, m_number_of_channels, m_number_of_harmonics, 1.f, m_decoder_matrix_float, m_number_of_harmonics, input, 1, 0.f, output, 1);
	}
	
	void DecoderIrregular::process(const double* input, double* output)
	{
		cblas_dgemv(CblasRowMajor, CblasNoTrans, m_number_of_channels, m_number_of_harmonics, 1.f, m_decoder_matrix, m_number_of_harmonics, input, 1, 0.f, output, 1);
	}
	
	DecoderIrregular::~DecoderIrregular()
	{
		delete [] m_decoder_matrix;
        delete [] m_decoder_matrix_float;
        delete [] m_harmonics_vector;
        delete m_encoder;
	}
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Decoder Binaural //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    unsigned int hoa_number_binaural_configs    = 8;
    unsigned int hoa_binaural_configs[]         = {4, 6, 8, 12, 18, 24, 36, 72};
    
    unsigned int hoa_number_binaural_samplerate = 4;
    unsigned int hoa_binaural_samplerate[]      = {44100, 48000, 88200, 96000};
    unsigned int hoa_binaural_impulse_sizes[]   = {200, 218, 400, 436}; // 200 // 37
    unsigned int hoa_binaural_crop[]            = {26, 40, 64, 80};
    
    DecoderBinaural::DecoderBinaural(unsigned int order) : Ambisonic(order), Planewaves(2)
    {
        if(order > 35)
            order  = 35;
        
        m_vector_size               = 0;
        m_sample_rate               = 0;
        m_impulses_loaded           = 0;
        m_matrix_allocated          = 0;
        m_impulses_matrix           = NULL;
        m_input_matrix              = NULL;
        m_result_matrix             = NULL;
        m_linear_vector_left        = NULL;
        m_linear_vector_right        = NULL;
   
        for(unsigned int i = 0; i < hoa_number_binaural_configs; i++)
        {
            if(hoa_binaural_configs[i] > m_order * 2 + 2)
            {
                m_number_of_virtual_channels = hoa_binaural_configs[i];
                break;
            }
        }
        m_impulses_vector   = new const float*[m_number_of_virtual_channels];
        m_harmonics_vector  = new float[m_number_of_harmonics];
        m_channels_vector   = new float[m_number_of_virtual_channels];
        m_decoder           = new DecoderRegular(m_order, m_number_of_virtual_channels);
        
        m_channels_azimuth[0] = HOA_PI2;
        m_channels_azimuth[1] = HOA_PI + HOA_PI2;
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
            for(int i = 0; i < m_number_of_virtual_channels; i++)
            {
                m_impulses_vector[i] = get_mit_hrtf_2D(m_sample_rate, wrap_360(-i * 360 / m_number_of_virtual_channels)) +hoa_binaural_crop[index];
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
                    
                    for(unsigned int k = 0; k < m_number_of_virtual_channels; k++)
                    {
                        value_right += m_channels_vector[k] * m_impulses_vector[k][j];
                        if(k == 0)
                            value_left += m_channels_vector[k] * m_impulses_vector[k][j];
                        else
                            value_left += m_channels_vector[k] * m_impulses_vector[m_number_of_virtual_channels - k][j];
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
		const float* input;
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
            cblas_saxpy(m_impulses_size,1.f, m_result_matrix+j+m_vector_size*m_impulses_size, m_vector_size, m_linear_vector_left  + j, 1);
            cblas_saxpy(m_impulses_size,1.f, m_result_matrix+j, m_vector_size, m_linear_vector_right + j, 1);
            
            outputs[0][j] = m_linear_vector_left[j];
            outputs[1][j] = m_linear_vector_right[j];
        }
        cblas_scopy(m_impulses_size-1, m_linear_vector_left+m_vector_size, 1, m_linear_vector_left, 1);
        cblas_scopy(m_impulses_size-1, m_linear_vector_right+m_vector_size, 1, m_linear_vector_right, 1);
        
        memset(m_linear_vector_left + m_impulses_size - 1, 0, m_vector_size * sizeof(float));
        memset(m_linear_vector_right + m_impulses_size - 1, 0, m_vector_size * sizeof(float));
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
    
    DecoderMulti::DecoderMulti(unsigned int order) : Ambisonic(order), Planewaves(order * 2 + 2)
    {
        m_mode = Regular;
        m_decoder_regular   = new DecoderRegular(m_order, m_order * 2 + 2);
        m_decoder_irregular = new DecoderIrregular(m_order, m_order * 2 + 2);
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
            if(m_mode == Regular && numberOfChannels >= m_decoder_regular->getNumberOfHarmonics())
            {
                delete m_decoder_regular;
                m_decoder_regular = new DecoderRegular(m_order, numberOfChannels);
            }
            else if(m_mode == Irregular)
            {
                delete m_decoder_irregular;
                m_decoder_irregular = new DecoderIrregular(m_order, numberOfChannels);
            }
        }
    }
    
    void DecoderMulti::setChannelsOffset(double offset)
	{
        if(m_mode == Regular)
        {
            m_decoder_regular->setChannelsOffset(offset);
        }
        else if(m_mode == Irregular)
        {
            m_decoder_irregular->setChannelsOffset(offset);
        }
	}
    
    void DecoderMulti::setChannelAzimuth(unsigned int index, double azimuth)
    {
        if(m_mode == Irregular)
        {
            m_decoder_irregular->setChannelAzimuth(index, azimuth);
        }
    }
    
    void DecoderMulti::setChannelsAzimtuh(double* azimuths)
    {
        if(m_mode == Irregular)
        {
            m_decoder_irregular->setChannelsAzimtuh(azimuths);
        }
    }
    
    void DecoderMulti::setSampleRate(unsigned int sampleRate)
    {
        if(m_mode == Binaural)
        {
            m_decoder_binaural->setSampleRate(sampleRate);
        }
        m_sample_rate = sampleRate;
    }
    
    void DecoderMulti::setVectorSize(unsigned int vectorSize)
    {
        if(m_mode == Binaural)
        {
            m_decoder_binaural->setVectorSize(vectorSize);
        }
        m_vector_size = vectorSize;
    }
	
	DecoderMulti::~DecoderMulti()
	{
        delete m_decoder_regular;
        delete m_decoder_irregular;
        delete m_decoder_binaural;
	}
}

