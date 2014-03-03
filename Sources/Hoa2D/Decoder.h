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
    class Decoder : public Ambisonic, public Planewaves
    {
        
    private:
        double          m_offset;
        double*         m_decoder_matrix;
        float*          m_decoder_matrix_float;
		double*         m_harmonics_vector;
        Encoder*        m_encoder;
        
    public:
        
        /**	The decoder constructor.
         @param     order					The order, must be at least 1.
		 @param     numberOfChannels	The number of channels, must be at least (order + 1)^2.
         */
		Decoder(unsigned int order, unsigned int numberOfChannels);
		
        /**	The decoder destructor.
         */
		~Decoder();
        
		/**	Set channel position.
		 @param     index		The index of the channel.
		 @param     azimuth		An azimuth value. In radian, between 0 and 2π.
         */
		void setChannelsOffset(double offset);
        
        /**	Set channel position.
		 @param     index		The index of the channel.
		 @param     azimuth		An azimuth value. In radian, between 0 and 2π.
         */
		double getChannelsOffset() const
        {
            return m_offset;
        }
				
		/**	This method performs the decoding with single precision.
         @param     input	The input sample.
         @param     outputs The output array that contains samples destinated to channels.
         */
		void process(const float* input, float* output);
		
		/**	This method performs the decoding with double precision.
         @param     input	The input sample.
         @param     outputs The output array that contains samples destinated to channels.
         */
		void process(const double* input, double* output);
    };
}


#endif


