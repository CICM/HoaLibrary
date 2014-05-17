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
	
    /*
    inline const float* get_mit_hrtf(long samplerate, long elevation, long azimuth)
    {
        int elevation_index;
        int number_of_samples;
        int elevation_offset;
        
        if(samplerate == 44100)
            number_of_samples = 512;
        else if(samplerate == 48000)
            number_of_samples = 557;
        else if(samplerate == 48000)
            number_of_samples = 1024;
        else if(samplerate == 48000)
            number_of_samples = 1114;
        else
            return NULL;
        
        if(elevation == -40)
            elevation_offset = 0;
        else if(elevation == -30)
            elevation_offset = 56 * number_of_samples;
        else if(elevation == -20)
            elevation_offset = (56 + 60) * number_of_samples;
        else if(elevation == -10)
            elevation_offset = (56 + 60 + 72) * number_of_samples;
        else if(elevation == 0)
            elevation_offset = (56 + 60 + 72 + 72) * number_of_samples;
        else if(elevation == 10)
            elevation_offset = (56 + 60 + 72 + 72 + 72) * number_of_samples;
        else if(elevation == 20)
            elevation_offset = (56 + 60 + 72 + 72 + 72 + 72) * number_of_samples;
        else if(elevation == 30)
            elevation_offset = (56 + 60 + 72 + 72 + 72 + 72 + 72) * number_of_samples;
        else if(elevation == 40)
            elevation_offset = (56 + 60 + 72 + 72 + 72 + 72 + 72 + 60) * number_of_samples;
        else if(elevation == 50)
            elevation_offset = (56 + 60 + 72 + 72 + 72 + 72 + 72 + 60 + 56) * number_of_samples;
        else if(elevation == 60)
            elevation_offset = (56 + 60 + 72 + 72 + 72 + 72 + 72 + 60 + 56 + 45) * number_of_samples;
        else if(elevation == 70)
            elevation_offset = (56 + 60 + 72 + 72 + 72 + 72 + 72 + 60 + 56 + 45 + 36) * number_of_samples;
        else if(elevation == 80)
            elevation_offset = (56 + 60 + 72 + 72 + 72 + 72 + 72 + 60 + 56 + 45 + 36 + 24) * number_of_samples;
        else if(elevation == 90)
            elevation_offset = (56 + 60 + 72 + 72 + 72 + 72 + 72 + 60 + 56 + 45 + 36 + 24 + 12) * number_of_samples;
        else
            return NULL;
        
        elevation_index = (elevation + 40) / 130;
        
        if(samplerate == 44100)
            return MIT_HRTF_44100+elevation_offset;
        else if(samplerate == 48000)
            return MIT_HRTF_44100+elevation_offset;
        else if(samplerate == 88200)
            return MIT_HRTF_88200+elevation_offset;
        else if(samplerate == 96000)
            return MIT_HRTF_96000+elevation_offset;
        return NULL;
    }
    */
} // end of namespace Hoa3D

#endif
