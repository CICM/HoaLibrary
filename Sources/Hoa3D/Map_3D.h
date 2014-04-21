/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __DEF_HOA_3D_MAP__
#define __DEF_HOA_3D_MAP__

#include "Ambisonic_3D.h"
#include "Encoder_3D.h"
#include "Wider_3D.h"

namespace Hoa3D
{
    //! The ambisonic multi-encoder with distance compensation.
    /** The map is a multi Encoder with distance compensation. It uses intances of the Wider class to decrease the directionnality of sources by simulating fractionnal orders when the sources are inside the ambisonic sphere and a simple diminution of the gain when the sources get away from the ambisonic sphere.
     
        @see Encoder
     */
    class Map : public Ambisonic
    {
        
    private:
        
        unsigned int        m_number_of_sources;
        float*              m_harmonics_float;
        double*             m_harmonics_double;
        double*             m_gains;
        std::vector<Encoder*>    m_encoders;
        std::vector<Wider*>      m_widers;
        
    public:
        
        //! The map constructor.
        /**	The map constructor allocates and initialize the member values and classes depending of a decomposition order and the number of sources. The order and the number of sources must be at least 1.
         
            @param     order            The order.
            @param     numberOfSources	The number of sources.
         */
        Map(unsigned int order, unsigned int numberOfSources);
        
        //! The map destructor.
        /**	The map destructor free the memory and deallocate the member classes.
         */
        ~Map();
        
        //! This method set the angle of azimuth of a source.
        /**	The angle of azimuth in radian, look at the Encoder for further informations. The index must be between 0 and the number of sources.
         
            @param     index	The index of the source.
            @param     azimuth	The azimuth.
            @see       setElevation()
            @see       setDistance()
         */
        void setAzimuth(unsigned int index, const double azimuth);
        
        //! This method set the angle of elevation of a source.
        /**	The angle of elevation in radian, look at the Encoder for further informations. The index must be between 0 and the number of sources.
         
            @param     index	The index of the source.
            @param     elevation The elevation.
            @see       setAzimuth()
            @see       setDistance()
         */
        void setElevation(unsigned int index, const double elevation);
        
        //! This method set the diatnce of a source.
        /**	The distance is between 0 and infinity. At 0, the source is in the center of the ambisonic sphere and at 1, the source is at the surface of the ambisonic sphere. Over 1, the source get away the ambisonic sphere. The index must be between 0 and the number of sources.
         
            @param     index	The index of the source.
            @param     elevation The elevation.
            @see       setAzimuth()
            @see       setElevation()
         */
        void setDistance(unsigned int index, const double distance);
        
        //! This method retrieve the number of sources.
        /** Retrieve the number of sources.
         
            @return The number of sources.
         */
        unsigned int getNumberOfSources() const {return m_number_of_sources;};
        
        //! This method performs the encoding with distance compensation with single precision.
        /**	You should use this method for in-place or not-in-place processing and performs the encoding with distance compensation sample by sample. The inputs array contains the samples of the sources and the minimum size sould be the number of sources. The outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         
            @param     inputs  The inputs array.
            @param     outputs The outputs array.
         */
        void process(const float* inputs, float* outputs);
        
        //! This method performs the encoding with distance compensation with double precision.
        /**	You should use this method for in-place or not-in-place processing and performs the encoding with distance compensation sample by sample. The inputs array contains the samples of the sources and the minimum size sould be the number of sources. The outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         
            @param     inputs  The inputs array.
            @param     outputs The outputs array.
         */
        void process(const double* inputs, double* outputs);
    };
}

#endif



