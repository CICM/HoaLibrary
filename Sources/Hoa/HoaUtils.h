/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __DEF_HOA_UTILS__
#define __DEF_HOA_UTILS__

namespace Hoa
{
	//! The int to string conversion
    /** The function converts a interger to a string.
     
	 @param     value   The value to convert.
	 @return    The function return value in a string format.
     */
    inline std::string int_to_string(int aValue)
    {
        char number[256];
        sprintf(number, "%i", aValue);
        return number;
    }
	
	static const float  MIT_HRTF_44100[] = {0};
    static const float  MIT_HRTF_48000[] = {0};
    static const float  MIT_HRTF_88200[] = {0};
    static const float  MIT_HRTF_96000[] = {0};
    
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
}

#endif


