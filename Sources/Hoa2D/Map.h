/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_2D_MAP
#define DEF_HOA_2D_MAP

#include "Ambisonic.h"
#include "Encoder.h"
#include "Wider.h"

namespace Hoa2D
{
    //! The ambisonic multi-encoder with distance compensation.
    /** The map is a multi Encoder with distance compensation. It uses intances of the Wider class to decrease the directionnality of sources by simulating fractionnal orders when the sources are inside the ambisonic circle and a simple diminution of the gain when the sources get away from the ambisonic circle.
     
        @see Encoder
     */
    class Map : public Ambisonic
    {
        
    private:
        
        unsigned int			m_number_of_sources;
        float*					m_harmonics_float;
        double*					m_harmonics_double;
        double*					m_gains;
		double*					m_radius;
		double*					m_azimuth;
		bool*					m_muted;
        std::vector<Encoder*>   m_encoders;
        std::vector<Wider*>     m_widers;
        
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
        /**	The angle of azimuth is in radian, look at the Encoder for further informations. The index must be between 0 and the number of sources.
         
            @param     index	The index of the source.
            @param     azimuth	The azimuth.
            @see       setElevation()
            @see       setDistance()
         */
        void setAzimuth(unsigned int index, const double azimuth);
        
        //! This method set the radius of a source.
        /**	The radius is between 0 and infinity. At 0, the source is in the center of the ambisonic circle and at 1, the source is at the surface of the ambisonic circle. Over 1, the source get away the ambisonic circle. The index must be between 0 and the number of sources.
         
            @param     index	The index of the source.
            @param     elevation The elevation.
            @see       setAzimuth()
            @see       setElevation()
         */
        void setRadius(unsigned int index, const double distance);
		
		//! This method mute or unmute a source.
        /**	Mute or unmute a source.
         
		 @param     index	The index of the source.
		 @param     muted	The mute state.
		 @see       getMute()
         */
        void setMute(unsigned int index, const bool muted) {assert(index < m_number_of_sources); m_muted[index] = muted;}
		
		//! This method retrieve the mute or unmute state of a source.
        /**	Get the Mute state of a source.
         
		 @param     index	The index of the source.
		 @return    The mute state.
		 @see       setMute()
         */
        bool getMute(unsigned int index, const bool muted) const {assert(index < m_number_of_sources); return m_muted[index];}
        
        //! This method retrieve the number of sources.
        /** Retrieve the number of sources.
         
            @return The number of sources.
         */
        unsigned int getNumberOfSources() const {return m_number_of_sources;};
		
		//! This method retrieve the radius of a source.
        /** Retrieve the radius of a source.
         
		 @return The radius of the source.
         */
        double getRadius(unsigned int index) const {assert(index < m_number_of_sources); return m_radius[index];}
		
		//! This method retrieve the azimuth of a source.
        /** Retrieve the azimuth of a source.
         
		 @return The azimuth of the source.
         */
        double getAzimuth(unsigned int index) const {assert(index < m_number_of_sources); return m_azimuth[index];}
        
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
