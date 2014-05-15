/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __DEF_HOA_3D_TOOLS__
#define __DEF_HOA_3D_TOOLS__

#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string>
#include <assert.h>

#ifdef __APPLE__

#include <Accelerate/Accelerate.h>

#endif

#ifdef _WINDOWS

#include <gsl_cblas.h>

#endif

#ifdef _LINUX

#include <cblas.h>

#endif

#define HOA_PI  (3.141592653589793238462643383279502884)
#define HOA_2PI (6.283185307179586476925286766559005)
#define HOA_PI2 (1.57079632679489661923132169163975144)
#define HOA_PI4 (0.785398163397448309615660845819875721)

#define NUMBEROFLINEARPOINTS 10000
#define NUMBEROFCIRCLEPOINTS 36000
#define NUMBEROFCIRCLEPOINTS_UI 360

namespace Hoa3D
{
    inline void sphere_discretize(unsigned int numberOfPoints, double* azimuths, double* elevations)
    {
        if(numberOfPoints == 4) // Tethrahedron
        {
            azimuths[0] = 0.;
            elevations[0] = HOA_PI2;
            azimuths[1] = 0.;
            azimuths[2] = HOA_2PI / 3.;
            azimuths[3] = 2. * HOA_2PI / 3.;
            elevations[1] = elevations[2] = elevations[3] = HOA_PI2 - HOA_2PI / 3.;
        }
        else if(numberOfPoints == 5) // Not regular : Octahedron with only 3 points at 0 azymuth
        {
            azimuths[0] = 0.;
            elevations[0] = HOA_PI2;
            azimuths[1] = 0.;
            azimuths[2] = HOA_2PI / 3.;
            azimuths[3] = 2. * HOA_2PI / 3.;
            elevations[1] = elevations[2] = elevations[3] = 0;
            azimuths[4] = 0.;
            elevations[4] = -HOA_PI2;
        }
        else if(numberOfPoints == 6) // Octahedron
        {
            azimuths[0] = 0.;
            elevations[0] = HOA_PI2;
            azimuths[1] = 0.;
            azimuths[2] = HOA_PI2;
            azimuths[3] = 2. * HOA_PI2;
            azimuths[4] = 3. * HOA_PI2;
            elevations[1] = elevations[2] = elevations[3] = elevations[4] = 0;
            azimuths[5] = 0.;
            elevations[5] = -HOA_PI2;
        }
        else if(numberOfPoints == 7) // Not regular : Octahedron with only 5 points at 0 azymuth
        {
            azimuths[0] = 0.;
            elevations[0] = HOA_PI2;
            azimuths[1] = 0.;
            azimuths[2] = HOA_2PI / 5.;
            azimuths[3] = 2. * HOA_2PI / 5.;
            azimuths[4] = 3. * HOA_2PI / 5.;
            azimuths[5] = 4. * HOA_2PI / 5.;
            elevations[1] = elevations[2] = elevations[3] = elevations[4] = elevations[5] = 0;
            azimuths[6] = 0.;
            elevations[6] = -HOA_PI2;
        }
        else if(numberOfPoints == 8) // Hexahedron or cube
        {
            azimuths[0] = azimuths[4] = HOA_PI4;
            azimuths[1] = azimuths[5] = HOA_PI4 + HOA_PI2;
            azimuths[2] = azimuths[6] = HOA_PI4 + HOA_PI;
            azimuths[3] = azimuths[7] = HOA_PI4 + HOA_PI + HOA_PI2;
            elevations[0] = elevations[1] = elevations[2] = elevations[3] = HOA_PI4;
            elevations[4] = elevations[5] = elevations[6] = elevations[7] = -HOA_PI4;
        }
        else if(numberOfPoints == 9) // Not regular : Hexahedron or cube with 1 at PI/2 elevation
        {
            azimuths[0] = azimuths[4] = HOA_PI4;
            azimuths[1] = azimuths[5] = HOA_PI4 + HOA_PI2;
            azimuths[2] = azimuths[6] = HOA_PI4 + HOA_PI;
            azimuths[3] = azimuths[7] = HOA_PI4 + HOA_PI + HOA_PI2;
            elevations[0] = elevations[1] = elevations[2] = elevations[3] = HOA_PI4;
            elevations[4] = elevations[5] = elevations[6] = elevations[7] = -HOA_PI4;
            elevations[8] = HOA_PI2;
            azimuths[8] = 0;
        }
        else if(numberOfPoints == 10) // Not regular : Hexahedron or cube with 1 at PI/2 elevation and 1 at -Pi/2 elevation
        {
            azimuths[0] = azimuths[4] = HOA_PI4;
            azimuths[1] = azimuths[5] = HOA_PI4 + HOA_PI2;
            azimuths[2] = azimuths[6] = HOA_PI4 + HOA_PI;
            azimuths[3] = azimuths[7] = HOA_PI4 + HOA_PI + HOA_PI2;
            elevations[0] = elevations[1] = elevations[2] = elevations[3] = HOA_PI4;
            elevations[4] = elevations[5] = elevations[6] = elevations[7] = -HOA_PI4;
            elevations[8] = HOA_PI2;
            elevations[9] = -HOA_PI2;
            azimuths[9] = azimuths[8] = 0;
        }
        else if(numberOfPoints == 11) // Not regular : Hexahedron or cube with 1 at PI/2 elevation and 1 at -Pi/2 elevation
        {
            azimuths[0] = azimuths[4] = HOA_PI4;
            azimuths[1] = azimuths[5] = HOA_PI4 + HOA_PI2;
            azimuths[2] = azimuths[6] = HOA_PI4 + HOA_PI;
            azimuths[3] = azimuths[7] = HOA_PI4 + HOA_PI + HOA_PI2;
            elevations[0] = elevations[1] = elevations[2] = elevations[3] = HOA_PI4;
            elevations[4] = elevations[5] = elevations[6] = elevations[7] = -HOA_PI4;
            elevations[8] = HOA_PI2;
            elevations[9] = elevations[9] = -HOA_PI2;
            azimuths[9] = azimuths[8] = 0;
        }
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
