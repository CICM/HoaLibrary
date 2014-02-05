/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DEF_AMBISONICDECODER3D
#define DEF_AMBISONICDECODER3D

#include "../hoaAmbisonics/Hoa3DAmbisonic.h"
#include "../hoaEncoder/Hoa3DEncoder.h"

namespace Hoa3D
{
	enum
	{
		Hoa_Full_Sphere = 0,
		Hoa_Half_Sphere
	};
	
	class Decoder : public Ambisonic
	{
		
	private:
		bool                m_shape;
		double**			m_decoder_matrix;
		double*				m_loudspeakers_azimuth;
		double*				m_loudspeakers_elevation;
		void computeMatrices();
		
	public:
		Decoder(long order = 1, long numberOfLoudspeakers = 8, bool shape = Hoa_Full_Sphere);
		
		void setNumberOfLoudspeakers(long numberOfLoudspeakers, bool shape = Hoa_Full_Sphere);
		void setLoudspeakerPosition(long anIndex, double anAzimuth, double anElevation);
		double getLoudspeakerAzimuth(long anIndex);
		double getLoudspeakerElevation(long anIndex);
		
		~Decoder();
		
		/**	This method performs the decoding with single precision.
         @param     input	The input sample.
         @param     outputs The output array that contains samples destinated to loudspeakers.
         */
		void process(const float input, float* output);
		
		/**	This method performs the decoding with double precision.
         @param     input	The input sample.
         @param     outputs The output array that contains samples destinated to loudspeakers.
         */
		void process(const double input, double* output);
	};
	
} // end of namespace Hoa3D

#endif