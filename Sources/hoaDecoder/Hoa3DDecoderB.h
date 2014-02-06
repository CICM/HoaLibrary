/*
// Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_AMBISONICDECODER3D
#define DEF_AMBISONICDECODER3D

#include "../hoaAmbisonics/Hoa3DAmbisonic.h"
#include "../hoaEncoder/Hoa3DEncoder.h"

namespace Hoa3D
{
	/** The type of sphere */
	enum sphereShape
	{
		Hoa_Half_Sphere = 0,	/**< Half of a sphere	*/
		Hoa_Full_Sphere			/**< A full sphere		*/
	};
	
	//! The ambisonic decoder.
    /** The decoder should be used to decode a signal encoded in the spherical harmonics domain depending on a decomposition order and a number of loudspeakers.
     */
	class Decoder : public Ambisonic
	{
		
	private:
		bool		m_shape;
		double*		m_decoder_matrix;
		double*		m_loudspeakers_azimuth;
		double*		m_loudspeakers_elevation;
		
		void		computeMatrices();
		
	public:
		/**	The decoder constructor.
         @param     order					The order, must be at least 1.
		 @param     numberOfLoudspeakers	The number of loudspeakers, must be at least (order + 1)^2.
		 @param     shape					Is a sphere or a half sphere.
         */
		Decoder(long order = 1, long numberOfLoudspeakers = 8, bool shape = Hoa_Full_Sphere);
		
		/**	Set the number of loudspeakers.
		 @param     numberOfLoudspeakers	The number of loudspeakers, must be at least (order + 1)^2.
		 @param     shape					Is a sphere or a half sphere.
         */
		void	setNumberOfLoudspeakers(long numberOfLoudspeakers, bool shape = Hoa_Full_Sphere);
		
		/**	Set loudspeaker position.
		 @param     index		The index of the loudspeaker.
		 @param     azimuth		An azimuth value. In radian, between 0 and 2π.
		 @param     elevation	An azimuth value. In radian, between 0 and 2π.
         */
		void	setLoudspeakerPosition(const unsigned int index, const double azimuth, const double elevation);
		
		/**	Get loudspeaker azimuth value.
		 @param     index		The index of the loudspeaker.
		 @return	the azimuth value in radians.
		 @see getLoudspeakerElevation
         */
		double	getLoudspeakerAzimuth(const unsigned int index) const;
		
		/**	Get loudspeakers elevation value.
		 @param     index		The index of the loudspeaker.
		 @return	the elevation value in radians.
		 @see getLoudspeakerAzimuth
         */
		double	getLoudspeakerElevation(const unsigned int index) const;
		
		/**	The decoder destructor.
         */
		~Decoder();
		
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
	
} // end of namespace Hoa3D

#endif