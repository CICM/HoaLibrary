/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_2D_DECODER
#define DEF_HOA_2D_DECODER

#include "Ambisonic.h"
#include "Encoder.h"

namespace Hoa2D
{
    class Decoder : public Ambisonic
    {
        
    private:
        double*		m_decoder_matrix;
        float*		m_decoder_matrix_float;
        
		double*		m_loudspeakers_azimuth;
		double*		m_harmonics_vector;
        Encoder*    m_encoder;
        
    public:
        
        /**	The decoder constructor.
         @param     order					The order, must be at least 1.
		 @param     numberOfLoudspeakers	The number of loudspeakers, must be at least (order + 1)^2.
         */
		Decoder(unsigned int order, unsigned int numberOfLoudspeakers);
		
        /**	The decoder destructor.
         */
		~Decoder();
        
		/**	Set loudspeaker position.
		 @param     index		The index of the loudspeaker.
		 @param     azimuth		An azimuth value. In radian, between 0 and 2π.
         */
		void	setLoudspeakerPosition(unsigned int index, double azimuth);
		
		/**	Get loudspeaker azimuth value.
		 @param     index		The index of the loudspeaker.
		 @return	the azimuth value in radians.
         */
		double	getLoudspeakerAzimuth(unsigned int index) const;
		
		/**	This method performs the decoding with single precision.
         @param     input	The input sample.
         @param     outputs The output array that contains samples destinated to loudspeakers.
         */
		void process(const float* input, float* output);
		
		/**	This method performs the decoding with double precision.
         @param     input	The input sample.
         @param     outputs The output array that contains samples destinated to loudspeakers.
         */
		void process(const double* input, double* output);
    };
}


#endif


