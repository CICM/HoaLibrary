/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __DEF_HOA_3D_METER__
#define __DEF_HOA_3D_METER__

#include "Planewaves_3D.h"

namespace Hoa3D
{
    //! The planewaves peak level meter.
    /** The meter should be used to widen the sound propagation.
     */
    class Meter : public Planewaves
    {
    private:
        unsigned int    m_ramp;
        unsigned int    m_vector_size;
        double*         m_channels_peaks;
		int**			m_channels_neighbors;

		unsigned int*   m_channels_number_of_points;
		double**		m_channels_points_azimuth;
		double**		m_channels_points_elevation;
	
		unsigned int*   m_channels_number_of_points_top;
		double**		m_channels_points_azimuth_top;
		double**		m_channels_points_elevation_top;
		
		unsigned int*   m_channels_number_of_points_bottom;
		double**		m_channels_points_azimuth_bottom;
		double**		m_channels_points_elevation_bottom;

		void find_neighbor_channels();
    public:
        
        //! The meter constructor.
        /**	The meter constructor allocates and initialize the member values to computes spherical harmonics weighted coefficients depending of a decomposition order. The order must be at least 1.
         
            @param     order	The order.
         */
        Meter(unsigned int numberOfChannels);
        
        //! The meter destructor.
        /**	The meter destructor free the memory.
         */
        ~Meter();
        
        void setVectorSize(unsigned int vectorSize);
        
        //! Set the position of a channel.
        /** Set the position of a channel with polar coordinates. The azimtuh is in radian between 0 and 2 Pi, O is the front of the soundfield and Pi is the back of the sound field. The elevation is in radian between -1/2 Pi and 1/2 Pi, -1/2 Pi the the bottom of the sound field, 0 is the center of the sound field and 1/2 Pi is the top of the sound field. The maximum index must be the number of channels - 1.
         
         @param     index		The index of the channel.
         @param     azimuth		The azimuth.
         @param     elevation	The elevation.
         */
		void setChannelPosition(unsigned int index, double azimuth, double elevation);
        
		//! Set the position of the channels.
        /** Set the position of the channels with polar coordinates. The azimtuh is in radian between 0 and 2 Pi, O is the front of the soundfield and Pi is the back of the sound field. The elevation is in radian between -1/2 Pi and 1/2 Pi, -1/2 Pi the the bottom of the sound field, 0 is the center of the sound field and 1/2 Pi is the top of the sound field. The maximum index must be the number of channels - 1.
         
            @param     azimuths		The azimuths.
            @param     elevations	The elevations.
         */
		void setChannelsPosition(double* azimuths, double* elevations);

		inline unsigned int getChannelNumberOfPoints(unsigned int index, bool top = 1) const
        {
            assert(index < m_number_of_channels);
			if(top)
				return m_channels_number_of_points[index];
			else
				return m_channels_number_of_points[index];
        }

		inline double getChannelPointAzimuth(unsigned int index, unsigned int pointindex, bool top = 1) const
        {
            assert(index < m_number_of_channels);
            return m_channels_points_azimuth[index][pointindex];
        }

		inline double getChannelPointElevation(unsigned int index, unsigned int pointindex, bool top = 1) const
        {
            assert(index < m_number_of_channels);
            return m_channels_points_elevation[index][pointindex];
        }

        inline double getChannelPeak(unsigned int index) const
        {
            assert(index < m_number_of_channels);
            return m_channels_peaks[index];
        }
        
        inline double getChannelEnergy(unsigned int index) const
        {
            assert(index < m_number_of_channels);
            return 20. * log10(m_channels_peaks[index]);
        }
       
        //! This method performs the widening with single precision.
        /**	You should use this method for in-place or not-in-place processing and performs the widening sample by sample. The inputs array and outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         
            @param     inputs   The inputs array.
         */
        void process(const float* inputs);
        
        //! This method performs the widening with double precision.
        /**	You should use this method for in-place or not-in-place processing and performs the widening sample by sample. The inputs array and outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         
            @param     inputs   The inputs array.
         */
        void process(const double* inputs);
    };
}

#endif



