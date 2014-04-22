/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __DEF_HOA_3D_DECODER__
#define __DEF_HOA_3D_DECODER__

#include "Ambisonic_3D.h"
#include "Encoder_3D.h"

namespace Hoa3D
{
	//! The ambisonic decoder.
    /** The decoder should be used to decode a signal encoded in the spherical harmonics domain depending on a decomposition order and a number of loudspeakers.
     */
	class Decoder : public Ambisonic
	{
		
	private:
        unsigned int    m_number_of_loudspeakers;
		double*         m_decoder_matrix;
        float*          m_decoder_matrix_float;
		double*         m_loudspeakers_azimuth;
		double*         m_loudspeakers_elevation;
		double*         m_harmonics_vector;
        Encoder*        m_encoder;
        
	public:
        
		/**	The decoder constructor.
         @param     order					The order, must be at least 1.
		 @param     numberOfLoudspeakers	The number of loudspeakers, must be at least (order + 1)^2.
		 @param     shape					Is a sphere or a half sphere.
         */
		Decoder(unsigned int order, unsigned int numberOfLoudspeakers);
		
        /**	The decoder destructor.
         */
		~Decoder();
        
        //! This method retrieve the number of loudspeakers.
        /** Retrieve the number of loudspeakers.
         
         @return The number of loudspeakers.
         */
        unsigned int getNumberOfLoudspeakers() const {return m_number_of_loudspeakers;};
        
		/**	Set loudspeaker position.
		 @param     index		The index of the loudspeaker.
		 @param     azimuth		An azimuth value. In radian, between 0 and 2π.
		 @param     elevation	An azimuth value. In radian, between 0 and 2π.
         */
		void	setLoudspeakerPosition(unsigned int index, double azimuth, double elevation);
		
		/**	Get loudspeaker azimuth value.
		 @param     index		The index of the loudspeaker.
		 @return	the azimuth value in radians.
		 @see getLoudspeakerElevation
         */
		double	getLoudspeakerAzimuth(unsigned int index) const;
		
		/**	Get loudspeakers elevation value.
		 @param     index		The index of the loudspeaker.
		 @return	the elevation value in radians.
		 @see getLoudspeakerAzimuth
         */
		double	getLoudspeakerElevation(unsigned int index) const;
		
		/**	This method performs the decoding with single precision.
         @param     input	The inputs array.
         @param     outputs The output array that contains samples destinated to loudspeakers.
         */
		void process(const float* input, float* output);
		
		/**	This method performs the decoding with double precision.
         @param     input	The inputs array.
         @param     outputs The output array that contains samples destinated to loudspeakers.
         */
		void process(const double* input, double* output);
	};
	
} // end of namespace Hoa3D

#endif
