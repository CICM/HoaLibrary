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
    private :
        class MeterPoint
		{
            public :
			double azi;
            double ele;
            double x;
            double y;
            double ref_x;
            double ref_y;
			MeterPoint(double _azi, double _ele)
            {
                azi = _azi;
                ele = _ele;
                x = abscissa(1., azi, ele);
                y = ordinate(1., azi, ele);
            };
			~MeterPoint(){};
            
            static bool compare(MeterPoint c1, MeterPoint c2)
			{
				return azimuth(c1.x - c1.ref_x, c1.y - c1.ref_y) < azimuth(c2.x - c1.ref_x, c2.y - c1.ref_y);
			};
            
            static bool isBetween(MeterPoint a, MeterPoint b, MeterPoint c)
            {
                if(fabs(c.ele - a.ele) - fabs(b.ele - a.ele) > FLT_EPSILON)
                    return 1;
                if(fabs(c.azi - a.azi) - fabs(b.azi - a.azi) > FLT_EPSILON)
                    return 1;
                double crossproduct = (c.y - a.y) * (b.x - a.x) - (c.x - a.x) * (b.y - a.y);
                if(fabs(crossproduct) > FLT_EPSILON)
                    return 0;
                    
                double dotproduct = (c.x - a.x) * (b.x - a.x) + (c.y - a.y)*(b.y - a.y);
                if(dotproduct < 0)
                    return 0;
                        
                double squaredlengthba = (b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y);
                if(dotproduct > squaredlengthba)
                    return 0;
                
                return 1;
            }
            
		};

        unsigned int    m_ramp;
        unsigned int    m_vector_size;
        double*         m_channels_peaks;
        int*            m_channels_top;
        int*            m_channels_bottom;
        std::vector<MeterPoint>* m_points_top;
        std::vector<MeterPoint>* m_points_bottom;
        std::vector<MeterPoint>  m_channels;
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

		inline unsigned int getChannelNumberOfPoints(unsigned int index) const
        {
            assert(index < m_number_of_channels);
			return m_points_top[index].size();
        }

		inline double getChannelPointAzimuth(unsigned int index, unsigned int pointindex) const
        {
            assert(index < m_number_of_channels);
            return m_points_top[index][pointindex].azi;
        }

		inline double getChannelPointElevation(unsigned int index, unsigned int pointindex) const
        {
            assert(index < m_number_of_channels);
            return m_points_top[index][pointindex].ele;
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



