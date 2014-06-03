/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __DEF_HOA_3D_DECODER__
#define __DEF_HOA_3D_DECODER__

#include "Ambisonic_3D.h"
#include "Planewaves_3D.h"
#include "Encoder_3D.h"

namespace Hoa3D
{
	//! The ambisonic decoder.
    /** The decoder should be used to decode a signal encoded in the spherical harmonics domain depending on a decomposition order and a number of channels.
     */
	class Decoder : public Ambisonic, public Planewaves
	{
		
	private:
		double*         m_decoder_matrix;
        float*          m_decoder_matrix_float;
		double*         m_harmonics_vector;
        Encoder*        m_encoder;
        double          m_azimuth_offset;
        double          m_elevation_offset;
        
	public:
        
		/**	The decoder constructor.
         @param     order					The order, must be at least 1.
		 @param     numberOfChannels	The number of channels, must be at least (order + 1)^2.
		 @param     shape					Is a sphere or a half sphere.
         */
		Decoder(unsigned int order, unsigned int numberOfChannels);
		
        /**	The decoder destructor.
         */
		~Decoder();
        
		/**	Set channel position.
		 @param     index		The index of the channel.
		 @param     azimuth		An azimuth value. In radian, between 0 and 2π.
		 @param     elevation	An elevation value. In radian, between 0 and 2π.
         */
		void	setChannelPosition(unsigned int index, double azimuth, double elevation);
        
        //! Set the offset of the channels.
		/**	Set the azimuth and the elevation offsets of the channels in radian.
         
         @param     azimuth		An azimuth value.
         @param     elevation	An elevation value.
         */
		void setChannelsOffset(double azimuth, double elevation);
        
        //! Get the azimuth offset of the channels.
        /**	Retreive the azimuth offset of the channels in radian.
         
         @return    The azimuth offset of the channels.
         */
		double getChannelsAzimuthOffset() const
        {
            return m_azimuth_offset;
        }
        
        //! Get the elevation offset of the channels.
        /**	Retreive the elevation offset of the channels in radian.
         
         @return    The elevation offset of the channels.
         */
		double getChannelsElevationOffset() const
        {
            return m_elevation_offset;
        }
		
        /**	This method performs the decoding with single precision.
         @param     input	The inputs array.
         @param     outputs The output array that contains samples destinated to channels.
         */
		void process(const float* input, float* output);
		
		/**	This method performs the decoding with double precision.
         @param     input	The inputs array.
         @param     outputs The output array that contains samples destinated to channels.
         */
		void process(const double* input, double* output);
	};
    
    const float* get_mit_hrtf_3D(long samplerate, double azimuth, double elevation);
    
    //! The ambisonic binaural decoder.
    /** The binaural decoder should be used to decode an ambisonic sound field for headphones.
     */
    class DecoderBinaural : public Ambisonic, public Planewaves
    {
    public:
        
        enum PinnaSize
        {
            Small       = 0,	/**< Small Pinna Size  */
            Large       = 1,	/**< Large Pinna Size */
        };
        
    private:
        float*          m_impulses_matrix;
        float*          m_harmonics_vector;
        float*          m_channels_vector;
        double*         m_channels_vector_double;
        unsigned int    m_number_of_virtual_channels;
        unsigned int    m_sample_rate;
        unsigned int    m_vector_size;
        unsigned int    m_impulses_size;
        unsigned int    m_configuration;
        
        bool            m_impulses_loaded;
        bool            m_matrix_allocated;
        
        float*          m_input_matrix;
        float*          m_result_matrix;
        float*          m_result_matrix_left;
        float*          m_result_matrix_right;
        float*          m_linear_vector_left;
        float*          m_linear_vector_right;
        
        const float**   m_impulses_vector;
        PinnaSize       m_pinna_size;
        
        Decoder*        m_decoder;
    public:
        
        //! The binaural decoder constructor.
        /**	The binaural decoder constructor allocates and initialize the member values to the decoding matrix depending of a decomposition order and a number of channels. The order and the number of channels must be at least 1 and the maximum order is 35. It is essential to set the sample rate and the vector size to load the impulse response and to be able to use the binaural decoding. The binaural process is optimized for block processing. The HRTF are from the MIT database.
         
         @param     order				The order
         */
		DecoderBinaural(unsigned int order);
		
        //! The binaural decoder destructor.
        /**	The binaural decoder destructor free the memory.
         */
		~DecoderBinaural();
        
        //! Set the sample rate.
        /** Set the sample rate. The sample will change the impulse responses size and their sizes increase with it. The valid sample rate are 44100, 48000, 88200 and 9600. Setting the sample rate will load the impulse responses, it is essential to define it before the digital signal processing.
         
         @param     sampleRate		The sample rate.
         
         @see    setVectorSize
         */
        void setSampleRate(unsigned int sampleRate);
        
        //! Set the vector size.
        /** Set the vector size. Setting the sample size will allocate the vector to compute the binaural decoding..
         
         @param     vectorSize		The vector size.
         
         @see    setSampleRate
         */
        
        void setVectorSize(unsigned int vectorSize);
        
        //! Retrieve if the decoder is ready to process.
        /** Retrieve if the impulses has been loaded and the matrix allocated.
         
         @return    The function returns true if the decoder is ready to process and false if not.
         */
		inline bool getState() const
        {
            if(m_impulses_loaded && m_matrix_allocated)
                return true;
            else
                return false;
        };
        
        //! Set the pinna size.
        /** Set the pinna size used to compute the HRTF. Setting the pinna size will re-allocate the vector to compute the binaural decoding.
         
         @param     pinnaSize		The pinna size.
         
         */
        void setPinnaSize(PinnaSize pinnaSize);
        
        //! Retrieve the pinna size.
        /** Retrieve the current size of the pinna.
         
         @return    The function returns the pinna size used to compute the HRTF.
         */
		inline PinnaSize getPinnaSize() const
        {
            return m_pinna_size;
        };
        
        //! Retrieve a name for a channel.
        /** Retrieve a name for a channel in a std::string format that will be "Headphone Left" or "Headphone Right".
         
         @param     index	The index of a channel.
         @return    The method returns a name for the channel.
         
         */
		inline std::string getChannelName(unsigned int index)
        {
            assert(index < 2);
            if(index == 0)
                return "Headphone Left";
            else
                return "Headphone Right";
        };
        
        //! This method performs the binaural decoding with single precision.
		/**	You should use this method for not-in-place processing and performs the binaural decoding on block of samples. The inputs matrix contains the spherical harmonics samples : inputs[number of harmonics][vector size] and the outputs matrix contains the headphones samples : outputs[2][vector size].
         
         @param     inputs	The input samples.
         @param     outputs  The output array that contains samples destinated to channels.
         */
		void process(const float* const* inputs, float** outputs);
		
        //! This method performs the binaural decoding with double precision.
		/**	You should use this method for not-in-place processing and performs the binaural decoding on block of samples. The inputs matrix contains the spherical harmonics samples : inputs[number of harmonics][vector size] and the outputs matrix contains the headphones samples : outputs[2][vector size].
         
         @param     input    The input samples.
         @param     outputs  The output array that contains samples destinated to channels.
         */
		void process(const double* const* inputs, double** outputs);
        
    };

} // end of namespace Hoa3D

#endif
