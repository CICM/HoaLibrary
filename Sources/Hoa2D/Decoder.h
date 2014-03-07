/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_2D_DECODER
#define DEF_HOA_2D_DECODER

#include "Ambisonic.h"
#include "Planewaves.h"
#include "Encoder.h"

namespace Hoa2D
{
    //! The ambisonic regular decoder.
    /** The regular decoder should be used to decode an ambisonic sound field for a set a channels at equal distances on a circle depending on a decomposition order. The number of channels must be at least the number of harmonics. Note that you can only change the offset of the channels.
     */
    class DecoderRegular : public Ambisonic, public Planewaves
    {
        
    private:
        double          m_offset;
        double*         m_decoder_matrix;
        float*          m_decoder_matrix_float;
		double*         m_harmonics_vector;
        Encoder*        m_encoder;
        
    public:
        
        //! The regular decoder constructor.
        /**	The regular decoder constructor allocates and initialize the member values to the decoding matrix depending of a decomposition order and a number of channels. The order must be at least 1 and the number of channels must be at least the number of harmonics.
         
            @param     order				The order
            @param     numberOfChannels     The number of channels.
         */
		DecoderRegular(unsigned int order, unsigned int numberOfChannels);
		
        //! The regular decoder destructor.
        /**	The regular decoder destructor free the memory.
         */
		~DecoderRegular();
        
        //! Set the offset of the channels.
		/**	Set the azimuth offset of the channels in radian.
         
            @param     offset		An azimuth value.
         */
		void setChannelsOffset(double offset);
        
        //! Get the offset of the channels.
        /**	Retreive the azimuth offset of the channels in radian.
         
            @return    The offset of the channels.
         */
		double getChannelsOffset() const
        {
            return m_offset;
        }
				
        //! This method performs the regular decoding with single precision.
		/**	You should use this method for in-place or not-in-place processing and performs the regular decoding sample by sample. The inputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics and the outputs array contains the channels samples and the minimym size must be the number of channels.
         
            @param     input	The input sample.
            @param     outputs The output array that contains samples destinated to channels.
         */
		void process(const float* input, float* output);
		
        //! This method performs the regular decoding with double precision.
		/**	You should use this method for in-place or not-in-place processing and performs the regular decoding sample by sample. The inputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics and the outputs array contains the channels samples and the minimym size must be the number of channels.
         
            @param     input	The input sample.
            @param     outputs The output array that contains samples destinated to channels.
         */
		void process(const double* input, double* output);
    };
    
    
    
    
    
    //! The ambisonic irregular decoder.
    /** The irregular decoder should be used to decode an ambisonic sound field for a set a channels not equally spaced on a  circle, like stereo or 5.1, depending on a decomposition order. The number of channels must be at least 1.
     */
    class DecoderIrregular : public Ambisonic, public Planewaves
    {
        
    private:
        double*         m_decoder_matrix;
        float*          m_decoder_matrix_float;
		double*         m_harmonics_vector;
        double*         m_channels_azimuth_sorted;
        double*         m_decoder_matrix_sorted;
        Encoder*        m_encoder;
        
    public:
        
        //! The irregular decoder constructor.
        /**	The irregular decoder constructor allocates and initialize the member values to the decoding matrix depending of a decomposition order and a number of channels. The order and the number of channels must be at least 1.
         
            @param     order				The order
            @param     numberOfChannels     The number of channels.
         */
		DecoderIrregular(unsigned int order, unsigned int numberOfChannels);
		
        //! The irregular decoder destructor.
        /**	The irregular decoder destructor free the memory.
         */
		~DecoderIrregular();
        
        //! Set the azimuth of a channel.
        /** Set the azimuth of a channel. The azimuth is in radian between 0 and 2 Pi, O is the front of the soundfield and Pi is the back of the sound field. The maximum index must be the number of channel - 1.
         
            @param     index		The index of the loudspeaker.
            @param     azimuth		The azimuth.
         
            @see    setChannelsPosition
         */
        void setChannelPosition(unsigned int index, double azimuth);
        
        //! Set the azimtuh of all the channels.
        /** Set the azimtuh of all the channels. It is more efficient to set all the channels azimuths at the same time because even if only one channel has changed, all the decoding matrix have to be recomputed. The azimuths are in radian between 0 and 2 Pi, O is the front of the soundfield and Pi is the back of the sound field. The azimtuhs array must have a minimum size of the number of channels.
        
            @param     azimuths		The azimuths array.
         
            @see    setChannelPosition
         */
        void setChannelsPosition(double* azimuths);
        
        //! This method performs the irregular decoding with single precision.
		/**	You should use this method for in-place or not-in-place processing and performs the irregular decoding sample by sample. The inputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics and the outputs array contains the channels samples and the minimum size must be the number of channels.
         
            @param     input	The input sample.
            @param     outputs The output array that contains samples destinated to channels.
         */
		void process(const float* input, float* output);
		
        //! This method performs the irregular decoding with double precision.
		/**	You should use this method for in-place or not-in-place processing and performs the irregular decoding sample by sample. The inputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics and the outputs array contains the channels samples and the minimum size must be the number of channels.
         
            @param     input	The input sample.
            @param     outputs The output array that contains samples destinated to channels.
         */
		void process(const double* input, double* output);
    };
    
    
    
    
    const float* get_mit_hrtf_2D(unsigned long samplerate, unsigned long azimuth);
    
    //! The ambisonic binaural decoder.
    /** The binaural decoder should be used to decode an ambisonic sound field for headphones.
     */
    class DecoderBinaural : public Ambisonic, public Planewaves
    {
        
    private:
        float*          m_impulses_matrix;
        float*          m_harmonics_vector;
        float*          m_channels_vector;
        unsigned int    m_number_of_virtual_channels;
        unsigned int    m_sample_rate;
        unsigned int    m_vector_size;
        unsigned int    m_impulses_size;
        
        bool            m_impulses_loaded;
        bool            m_matrix_allocated;
        
        float*          m_input_matrix;
        float*          m_result_matrix;
        float*          m_result_matrix_left;
        float*          m_result_matrix_right;
        float*          m_linear_vector_left;
        float*          m_linear_vector_right;
        
        const float**   m_impulses_vector;
        
        DecoderRegular* m_decoder;
    public:
        
        //! The binaural decoder constructor.
        /**	The binaural decoder constructor allocates and initialize the member values to the decoding matrix depending of a decomposition order and a number of channels. The order and the number of channels must be at least 1 and the maximum order is 35.
         
         @param     order				The order
         @param     numberOfChannels     The number of channels.
         */
		DecoderBinaural(unsigned int order);
		
        //! The binaural decoder destructor.
        /**	The binaural decoder destructor free the memory.
         */
		~DecoderBinaural();
        
        void setSampleRate(unsigned int sampleRate);
        void setVectorSize(unsigned int vectorSize);
        
        //! Retrieve if the impulses has been loaded
        /** Retrieve if the impulses has been loaded.
         
            @return    The true if the impulses has been loaded and false if not.
         */
		inline bool getState() const
        {
            if(m_impulses_loaded && m_matrix_allocated)
                return true;
            else
                return false;
        };
        
        
        //! Retrieve a name for a channel.
        /** Retrieve a name for a channel in a std::string format that will be "Headphone Left" or "Headphone Right".
         
         @param     index	The index of a channel.
         @return    The method returns a name for the channel that contains its index and its azimuth if the channel exists, otherwise the function generates an error.
         
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
		/**	You should use this method for in-place or not-in-place processing and performs the binaural decoding sample by sample. The inputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics and the outputs array contains the headphones samples and the minimum size must be 2.
         
         @param     inputs	The input sample.
         @param     outputs The output array that contains samples destinated to channels.
         */
		void process(const float* const* inputs, float** outputs);
		
        //! This method performs the binaural decoding with double precision.
		/**	You should use this method for in-place or not-in-place processing and performs the binaural decoding sample by sample. The inputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics and the outputs array contains the headphones samples and the minimum size must be 2.
         
         @param     input	The input sample.
         @param     outputs The output array that contains samples destinated to channels.
         */
		void process(const double* const* inputs, double** outputs);
    };
}




#endif


