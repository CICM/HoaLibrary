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

	class Delaunay
	{
	private :
		class DelaunayPoint;
		class DelaunayCircle
		{
		public :
			double x;
			double y;
			double r;
			std::vector<DelaunayPoint *> points;

			DelaunayCircle(double _x, double _y, double _r){
				x = _x;
				y = _y;
				r = _r;
			};
			~DelaunayCircle()
			{
				points.clear();
			};
		};

		class DelaunayPoint
		{
		public :
			double x;
			double y;
			std::vector<DelaunayCircle *> circles;

			DelaunayPoint(double _x, double _y){
				x = _x;
				y = _y;
			};

			~DelaunayPoint()
			{
				circles.clear();
			};
		};

		std::vector<DelaunayPoint> points;
		std::vector<DelaunayCircle> circles;

		void evaluateTriangle(int i, int j, int k)
		{
			double angle_jik = azimuth(points[j].x - points[i].x, points[j].y - points[i].y) - azimuth(points[k].x - points[i].x, points[k].y - points[i].y);
			if(angle_jik > HOA_PI)
				angle_jik = HOA_PI - angle_jik;
			double dista_ij = distance(points[j].x, points[j].y, points[i].x, points[i].y);
			double radius = dista_ij / sin(angle_jik);

			double abs = radius + dista_ij * 0.5;
			double ord = radius + points[i].y;

			for(int l = 0; l < points.size(); l++)
			{
				if(distance(abs, ord, points[l].x, points[l].y) < radius)
					return;
			}

			DelaunayCircle circle = DelaunayCircle(abs, ord, radius);
			circle.points.push_back(&points[i]);
			circle.points.push_back(&points[j]);
			circle.points.push_back(&points[k]);
			circles.push_back(circle);
			points[i].circles.push_back(&circle);
			points[j].circles.push_back(&circle);
			points[k].circles.push_back(&circle);
		};

	public :
		Delaunay(){};
		~Delaunay()
		{
			clear();
		};

		void clear()
		{
			points.clear();
			circles.clear();
		};

		void addPoint(double _azimuth, double _elevation, bool _bottom = 0)
		{
			double abs = abscissa(1., _azimuth, _elevation);
			double ord = ordinate(1., _azimuth, _elevation);
			if((_bottom && _elevation > 0) || (!_bottom && _elevation < 0))
			{
				double rad = (1. - radius(abs, ord)) + 1.;
				double azy = azimuth(abs, ord);
				abs = abscissa(rad, azy);
				ord = ordinate(rad, azy);
			}
			points.push_back(DelaunayPoint(abs, ord));
		};
			
		void perform()
		{
			int size = points.size();
			for(int i = 0; i < size - 3; i++)
			{
				for(int j = i+1; j < size - 2; j++)
				{
					for(int k = j+1; k < size - 1; k++)
					{
						evaluateTriangle(i, j, k);
					}
				}
			}
		};

		unsigned int getNumberOfCircles() const
		{
			return circles.size();
		};
	};
    //! The planewaves peak level meter.
    /** The meter should be used to widen the sound propagation.
     */
    class Meter : public Planewaves
    {
    private :

        unsigned int    m_ramp;
        unsigned int    m_vector_size;
        double*         m_channels_peaks;
		Delaunay*		m_delaunay;
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
			return 0;
        }

		inline double getChannelPointAzimuth(unsigned int index, unsigned int pointindex, bool top = 1) const
        {
            assert(index < m_number_of_channels);
            return 0;
        }

		inline double getChannelPointElevation(unsigned int index, unsigned int pointindex, bool top = 1) const
        {
            assert(index < m_number_of_channels);
            return 0;
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



