/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_2D_TOOL
#define DEF_HOA_2D_TOOL

#include "Ambisonic.h"
#include "Planewaves.h"
#include "Map.h"
#include "Optim.h"
#include "Decoder.h"
#include "Meter.h"
#include "SourcesManager.h"

namespace Hoa2D
{
    //! The kit to spatialize points sources.
    /** The KitSources is an all-in-one class that owns a Map, an Optim, a DecoderMulti, a Meter and a SourcesManager and that can be used to spatialize several sources. It allows to dynamicaly change the classes parameters.
     */
    class KitSources
    {
        
    private:
        
        class PolarLines
        {
            
        private:
            float*      m_values_old;
            float*      m_values_new;
            float*      m_values_step;
            unsigned int m_counter;
            unsigned int m_ramp;
            unsigned int m_number_of_sources;
            
        public:
            PolarLines(unsigned int numberOfSources);
            ~PolarLines();
            
            inline unsigned int getNumberOfSources() const
            {
                return m_number_of_sources;
            }
            
            inline unsigned int getRamp() const
            {
                return m_ramp;
            }
            
            inline double getRadius(unsigned int index) const
            {
                assert(index < m_number_of_sources);
                return m_values_new[index];
            }
            
            inline double getAzimuth(unsigned int index) const
            {
                assert(index < m_number_of_sources);
                return m_values_new[m_number_of_sources +index];
            }
            
            void setRamp(unsigned int ramp);
            void setRadius(unsigned int index, double radius);
            void setAzimuth(unsigned int index, double azimuth);
            void setRadiusDirect(unsigned int index, double radius);
            void setAzimuthDirect(unsigned int index, double azimuth);
            
            void process(float* vector);
        };
        
        unsigned int        m_order;
        unsigned int        m_number_of_sources;
        unsigned int        m_number_of_channels;
        DecoderMulti::Mode  m_decoding_mode;
        Optim::Mode         m_optim_mode;
        double              m_offset;
        unsigned int        m_sample_rate;
        unsigned int        m_vector_size;
        
        Map*            m_map;
        Optim*          m_optim;
        DecoderMulti*   m_decoder;
        Meter*          m_meter;
        SourcesManager* m_sources;
        PolarLines*     m_lines;
        
        double*         m_inputs_double;
        double*         m_outputs_double;
        double*         m_harmonics_double;
        float*          m_inputs_float;
        float*          m_outputs_float;
        float*          m_harmonics_float;
        float*          m_lines_vector;
    public:
        
        //! The sources kit constructor.
        /**	The sources kit constructor all the classes.The order must be at least 1;
         
            @param     order				The order.
         */
		KitSources(unsigned int order);
		
        //! The sources kit destructor.
        /**	The sources kit destructor free the memory.
         */
		~KitSources();
        
        //! Set the decomposition order.
		/**	Set the decomposition order. The change will operate during the post process call to avoid conflicts during the process.
         
            @param     order				The order.
         */
		void setOrder(unsigned int order);
        
        //! Retrieve the decomposition order.
        /** Retrieve the decomposition order.
            
            @return The order.
         */
        unsigned int getOrder() const
        {
            return m_order;
        }
        
        //! Set the number of sources.
		/**	Set the number of sources. The change will operate during the post process call to avoid conflicts during the process.
         
            @param     numberOfSources      The number of sources.
         */
        void setNumberOfSources(unsigned int numberOfSources);
        
        //! Retrieve the number of sources.
        /** Retrieve the number of sources.
         
            @return The number of sources.
         */
        unsigned int getNumberOfSources() const
        {
            return m_number_of_sources;
        };
        
        //! Set the number of channels.
		/**	Set the number of channels. The change will operate during the post process call to avoid conflicts during the process.
         
            @param     numberOfChannels      The number of channels.
         */
        void setNumberOfChannels(unsigned int numberOfChannels);
        
        //! Retrieve the number of channels.
		/** Retrieve the number of channels of the planewave class.
         
            @return The number of channels.
         */
		inline unsigned int getNumberOfChannels() const
        {
            return m_number_of_channels;
        }
        
        //! Set the decoding mode.
		/**	Set the decoding mode. The change will operate during the post process call to avoid conflicts during the process.
         
            @param     mode		The decoding mode.
         */
        void setDecodingMode(DecoderMulti::Mode mode);
        
        //! Retrieve the decoding mode.
        /** Retrieve the decoding mode.
         
            @return The decoding mode.
         */
        DecoderMulti::Mode getDecodingMode() const
        {
            return m_decoding_mode;
        };
        
        //! This method set the optimization mode.
        /**	The mode should be one of the 3 optimization modes, Basic, MaxRe or InPhase.         
            @param     mode The optimization mode.
         */
        void setOptimMode(Optim::Mode mode);
        
        //! Retrieve the optimization mode.
        /** Retrieve the optimization mode.
         
            @return The optimization mode.
         */
        Optim::Mode getOptimMode() const
        {
            return m_optim_mode;
        };
        
        //! Set the offset of the channels for the regular decoding.
		/**	Set the azimuth offset of the channels in radian for the regular decoding, if the decoding mode. The change will operate during the post process call to avoid conflicts during the process.
         
            @param     offset		An azimuth value.
         */
		void setChannelsOffset(double offset);
        
        //! Retrieve the offset of the channels .
        /** Retrieve the offset of the channels .
         
            @return The offset of the channels .
         */
        double getChannelsOffset() const
        {
            return m_offset;
        };
        
        //! Set the sample rate.
        /** Set the sample rate. The sample will change the impulse responses size and their sizes increase with it. The valid sample rate are 44100, 48000, 88200 and 9600. Setting the sample rate will load the impulse responses, it is essential to define it before the digital signal processing.
         
            @param     sampleRate		The sample rate.
         
            @see    setVectorSize
         */
        void setSampleRate(unsigned int sampleRate);
        
        //! Retrieve the sample rate.
		/** Retrieve the sample rate.
         
            @return The sample rate.
         */
		inline unsigned int getSampleRate() const
        {
            return m_sample_rate;
        }
        
        //! Set the vector size.
        /** Set the vector size. Setting the sample size will allocate the vector to compute the binaural decoding.
         
            @param     vectorSize		The vector size.
         
            @see    setSampleRate
         */
        void setVectorSize(unsigned int vectorSize);
        
        //! Retrieve the vector size.
		/** Retrieve vector size.
         
            @return The vector size.
         */
		inline unsigned int getVectorSize() const
        {
            return m_vector_size;
        }

        void applyChanges();
        
        void releaseResources();
        
        //! This method performs the regular decoding with single precision.
		/**	You should use this method for in-place or not-in-place processing and performs the regular decoding sample by sample. The inputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics and the outputs array contains the channels samples and the minimym size must be the number of channels.
         
            @param     input	The input sample.
            @param     outputs The output array that contains samples destinated to channels.
         */
		void process(const float** input, float** output);
		
        //! This method performs the regular decoding with double precision.
		/**	You should use this method for in-place or not-in-place processing and performs the regular decoding sample by sample. The inputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics and the outputs array contains the channels samples and the minimym size must be the number of channels.
         
            @param     input	The input sample.
            @param     outputs The output array that contains samples destinated to channels.
         */
		void process(const double* input, double* output);
    };
}




#endif


