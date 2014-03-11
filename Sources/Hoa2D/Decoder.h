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
        Encoder*        m_encoder;
        double          m_offset;
        
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
        
        //! Set the azimuth of a channel.
        /** Set the azimuth of a channel. The azimuth is in radian between 0 and 2 Pi, O is the front of the soundfield and Pi is the back of the sound field. The maximum index must be the number of channel - 1.
         
            @param     index		The index of the loudspeaker.
            @param     azimuth		The azimuth.
         
            @see    setChannelsAzimtuh
         */
        void setChannelAzimuth(unsigned int index, double azimuth);
        
        //! Set the azimtuh of all the channels.
        /** Set the azimtuh of all the channels. It is more efficient to set all the channels azimuths at the same time because even if only one channel has changed, all the decoding matrix have to be recomputed. The azimuths are in radian between 0 and 2 Pi, O is the front of the soundfield and Pi is the back of the sound field. The azimtuhs array must have a minimum size of the number of channels.
        
            @param     azimuths		The azimuths array.
         
            @see    setChannelAzimuth
         */
        void setChannelsAzimtuh(double* azimuths);
        
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
        /**	The binaural decoder constructor allocates and initialize the member values to the decoding matrix depending of a decomposition order and a number of channels. The order and the number of channels must be at least 1 and the maximum order is 35. It is essential to set the sample rate and the vector size to load the impulse response and to be able to use the binaural decoding. The binaural process is optimized for block processing.
         
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
         
            @param     vectorSize		The vector rate.
         
            @see    setSampleRate
         */

        void setVectorSize(unsigned int vectorSize);
        
        //! Retrieve if the decoder is ready to process.
        /** Retrieve if the impulses has been loaded and the matrix allocated.
         
            @return    The true if the decoder is ready to process and false if not.
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
		/**	You should use this method for not-in-place processing and performs the binaural decoding on block of samples. The inputs matrix contains the spherical harmonics samples : inputs[number of harmonics][vector size] and the outputs array contains the headphones samples : outputs[2][vector size].
         
            @param     inputs	The input samples.
            @param     outputs  The output array that contains samples destinated to channels.
         */
		void process(const float* const* inputs, float** outputs);
		
        //! This method performs the binaural decoding with double precision.
		/**	You should use this method for not-in-place processing and performs the binaural decoding on block of samples. The inputs matrix contains the spherical harmonics samples : inputs[number of harmonics][vector size] and the outputs array contains the headphones samples : outputs[2][vector size].
         
            @param     input    The input samples.
            @param     outputs  The output array that contains samples destinated to channels.
         */
		void process(const double* const* inputs, double** outputs);
    };
    
    //! The ambisonic multi-decoder.
    /** The multi-decoder is a class that facilitates the use of the three decoder : regular, irregular and binaural.
     */
    class DecoderMulti : public Ambisonic, public Planewaves
    {
    public:
        
        enum Mode
        {
            Regular     = 0,	/**< Regular Decoding   */
            Irregular   = 1,	/**< Irregular Decoding */
            Binaural    = 2     /**< Binaural Decoding  */
        };
        
    private:
        DecoderRegular*     m_decoder_regular;
        DecoderIrregular*   m_decoder_irregular;
        DecoderBinaural*    m_decoder_binaural;
        Mode                m_mode;
        unsigned int        m_sample_rate;
        unsigned int        m_vector_size;

        
    public:
        
        //! The multi-decoder constructor.
        /**	The multi-decoder constructor allocates and initialize the three decoder. The default decoder will be the regular one with 2 * order + 2 number of channels.
         
            @param     order				The order
         */
		DecoderMulti(unsigned int order);
		
        //! The multi-decoder destructor.
        /**	The multi-decoder destructor free the memory.
         */
		~DecoderMulti();
        
        //! Set the decoding mode.
		/**	Set the decoding mode. It will allocate the right decoder and initialize the class.
         
            @param     mode		The decoding mode.
         */
		void setDecodingMode(Mode mode);
        
        //! Retrieve the decoding mode.
        /** Retrieve the current decoding mode of the multi-decoder.
         
            @return    The decoding mode;
         */
		inline Mode getDecodingMode() const
        {
            return m_mode;
        };
        
        //! Set the number of channels for the regular or irregular decoding.
		/**	Set the number of channels for the regular or irregular decoding.
         
            @param     numberOfChannels		The number of channels.
         */
		void setNumberOfChannels(unsigned int numberOfChannels);
        
        //! Retrieve the number of channels.
		/** Retrieve the number of channels of the planewave class.
         
         @return The number of channels.
         */
		inline unsigned int getNumberOfChannels() const
        {
            if(m_mode == Regular)
                return m_decoder_regular->getNumberOfChannels();
            else if(m_mode == Irregular)
                return m_decoder_irregular->getNumberOfChannels();
            else
                return m_decoder_binaural->getNumberOfChannels();
        }
        
        //! Set the offset of the channels for the regular decoding.
		/**	Set the azimuth offset of the channels in radian for the regular decoding, if the decoding mode.
         
            @param     offset		An azimuth value.
         */
		void setChannelsOffset(double offset);
        
        //! Get the offset of the channels of the regular decoding.
        /**	Retreive the azimuth offset of the channels in radian the regular decoding.
         
            @return    The offset of the channels if the regular decoding mode is active, otherwise it returns 0.
         */
		double getChannelsOffset() const
        {
            if(m_mode == Regular)
                return m_decoder_regular->getChannelsOffset();
            else if(m_mode == Irregular)
                return m_decoder_irregular->getChannelsOffset();
            else
                return 0;
        }
        
        //! Set the azimuth of a channel for the irregular decoding mode.
        /** Set the azimuth of a channel for the irregular decoding mode. The azimuth is in radian between 0 and 2 Pi, O is the front of the soundfield and Pi is the back of the sound field. The maximum index must be the number of channel - 1.
         
            @param     index		The index of the loudspeaker.
            @param     azimuth		The azimuth.
         
            @see    setChannelsAzimtuh
         */
        void setChannelAzimuth(unsigned int index, double azimuth);
        
        //! Set the azimtuh of all the channels for the irregular decoding mode.
        /** Set the azimtuh of all the channels for the irregular decoding mode. It is more efficient to set all the channels azimuths at the same time because even if only one channel has changed, all the decoding matrix have to be recomputed. The azimuths are in radian between 0 and 2 Pi, O is the front of the soundfield and Pi is the back of the sound field. The azimtuhs array must have a minimum size of the number of channels.
         
            @param     azimuths		The azimuths array.
         
            @see    setChannelAzimuth
         */
        void setChannelsAzimtuh(double* azimuths);
        
        //! Set the sample rate.
        /** Set the sample rate. The sample will change the impulse responses size and their sizes increase with it. The valid sample rate are 44100, 48000, 88200 and 9600. Setting the sample rate will load the impulse responses, it is essential to define it before the digital signal processing.
         
         @param     sampleRate		The sample rate.
         
         @see    setVectorSize
         */
        void setSampleRate(unsigned int sampleRate);
        
        //! Set the vector size.
        /** Set the vector size. Setting the sample size will allocate the vector to compute the binaural decoding..
         
         @param     vectorSize		The vector rate.
         
         @see    setSampleRate
         */
        
        void setVectorSize(unsigned int vectorSize);
        
        //! Retrieve if the binaural decoder is ready to process.
        /** Retrieve if the impulses has been loaded and the matrix allocated.
         
            @return    The true if the binaural decoder is ready to process and false if not.
         */
		inline bool getBinauralState() const
        {
            if(m_mode == Binaural && m_decoder_binaural->getState())
                return true;
            else
                return false;
        };
        
        //! Retrieve the azimuth of a channel.
        /** Retrieve the azimuth of a channel. The azimuth of the channel is in radian, 0 radian is at the front of the soundfield and Pi is at the back of the sound field. The maximum index must be the number of channels - 1.
         
            @param      index   The index of the channel.
            @return     The azimuth of the channel if the channel exists, otherwise the function generates an error.
         
            @see getChannelAbscissa
            @see getChannelOrdinate
            @see getChannelName
         */
		inline double getChannelAzimuth(unsigned int index) const
        {
            if(m_mode == Regular)
                return m_decoder_regular->getChannelAzimuth(index);
            else if(m_mode == Irregular)
                return m_decoder_irregular->getChannelAzimuth(index);
            else
                return m_decoder_binaural->getChannelAzimuth(index);
        }
        
		
        //! Retrieve the abscissa of a channel.
		/** Retrieve the abscissa of a channel. The abscissa is between -1 and 1, -1 is the left of the soundfield, 0 is the center of the soundfield and 1 is the right of the soundfield. The maximum index must be the number of channels - 1.
         
            @param     index    The index of the loudspeaker.
            @return    The abscissa of the channel if the channel exists, otherwise the function generates an error.
         
            @see getChannelAzimuth
            @see getChannelOrdinate
            @see getChannelName
         */
		inline double getChannelAbscissa(unsigned int index) const
        {
            if(m_mode == Regular)
                return m_decoder_regular->getChannelAbscissa(index);
            else if(m_mode == Irregular)
                return m_decoder_irregular->getChannelAbscissa(index);
            else
                return m_decoder_binaural->getChannelAbscissa(index);
        }
		
        //! Retrieve the ordinate of a channel.
		/** Retrieve the ordinate of a channel. The ordinate is between -1 and 1, -1 is the back of the soundfield, 0 is the center of the soundfield and 1 is the front of the soundfield. The maximum index must be the number of channels - 1.
         
            @param     index	The index of the channel.
            @return    The ordinate of the channel if the channel exists, otherwise the function generates an error.
         
            @see getChannelAzimuth
            @see getChannelAbscissa
            @see getChannelName
         */
		inline double getChannelOrdinate(unsigned int index) const
        {
            if(m_mode == Regular)
                return m_decoder_regular->getChannelOrdinate(index);
            else if(m_mode == Irregular)
                return m_decoder_irregular->getChannelOrdinate(index);
            else
                return m_decoder_binaural->getChannelOrdinate(index);
        }
        
        //! Retrieve a name for a channel.
        /** Retrieve a name for a channel in a std::string format, look at each decoder for further informations.
         
         @param     index	The index of a channel.
         @return    The method returns a name for the channel.
         
         */
		inline std::string getChannelName(unsigned int index)
        {
            if(m_mode == Regular)
                return m_decoder_regular->getChannelName(index);
            else if(m_mode == Irregular)
                return m_decoder_irregular->getChannelName(index);
            else
                return m_decoder_binaural->getChannelName(index);
        };
        
        //! This method performs the binaural decoding with single precision.
		/**	You should use this method for not-in-place processing and performs the binaural decoding on block of samples. The inputs matrix contains the spherical harmonics samples : inputs[number of harmonics][vector size] and the outputs array contains the headphones samples : outputs[2][vector size].
         
            @param     inputs	The input samples.
            @param     outputs  The output array that contains samples destinated to channels.
         */
		inline void processBinaural(const float* const* inputs, float** outputs)
        {
            m_decoder_binaural->process(inputs, outputs);
        }
		
        //! This method performs the binaural decoding with double precision.
		/**	You should use this method for not-in-place processing and performs the binaural decoding on block of samples. The inputs matrix contains the spherical harmonics samples : inputs[number of harmonics][vector size] and the outputs array contains the headphones samples : outputs[2][vector size].
         
            @param     inputs	The input samples.
            @param     outputs  The output array that contains samples destinated to channels.
         */
		inline void processBinaural(const double* const* inputs, double** outputs)
        {
            m_decoder_binaural->process(inputs, outputs);
        }
        
        //! This method performs the decoding depending of the mode with single precision.
		/**	You should use this method for not-in-place processing and performs the binaural decoding on block of samples. The inputs matrix contains the spherical harmonics samples : inputs[number of harmonics][vector size] and the outputs array contains the headphones samples : outputs[2][vector size].
         
            @param     inputs	The input samples.
            @param     outputs  The output array that contains samples destinated to channels.
         */
		inline void processRegular(const float* inputs, float* outputs)
        {
            m_decoder_regular->process(inputs, outputs);
        }
		
        //! This method performs the regular decoding with single precision.
		/**	You should use this method for in-place or not-in-place processing and performs the regular decoding sample by sample. The inputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics and the outputs array contains the channels samples and the minimym size must be the number of channels.
         
            @param     input	The input sample.
            @param     outputs The output array that contains samples destinated to channels.
         */
		inline void processRegular(const double* inputs, double* outputs)
        {
            m_decoder_regular->process(inputs, outputs);
        }
        
        //! This method performs the irregular decoding with single precision.
		/**	You should use this method for in-place or not-in-place processing and performs the irregular decoding sample by sample. The inputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics and the outputs array contains the channels samples and the minimum size must be the number of channels.
         
            @param     input	The input sample.
            @param     outputs The output array that contains samples destinated to channels.
         */
		inline void processIrregular(const float* inputs, float* outputs)
        {
            m_decoder_irregular->process(inputs, outputs);
        }
		
        //! This method performs the irregular decoding with single precision.
		/**	You should use this method for in-place or not-in-place processing and performs the irregular decoding sample by sample. The inputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics and the outputs array contains the channels samples and the minimum size must be the number of channels.
         
            @param     input	The input sample.
            @param     outputs The output array that contains samples destinated to channels.
         */
		inline void processIrregular(const double* inputs, double* outputs)
        {
            m_decoder_irregular->process(inputs, outputs);
        }
    };
    
}




#endif


