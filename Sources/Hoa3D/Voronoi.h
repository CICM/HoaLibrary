/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __DEF_Voronoi__
#define __DEF_Voronoi__

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string>
#include <assert.h>
#include <algorithm>
#include "../Hoa.h"
#define VoroPi  (3.141592653589793238462643383279502884)

namespace Hoa
{
    /////////////////////////////////////////////////////////
    // Voronoi Point ////////////////////////////////////////
    /////////////////////////////////////////////////////////
    class VoronoiPoint
    {
		private :
        
        double xyz[3];
        double xyz_rel[3];
        std::vector<VoronoiPoint> boundaries;
        
        public :
        VoronoiPoint(double x, double y, double z = 0);
        
        void addBoundary(VoronoiPoint pt);
        void clearBoundaries();
        void sortBoundaries();
        void setRelativePoint(VoronoiPoint const& pt);
        
        int getNumberOfBoundaries() const
        {
            return boundaries.size();
        }
        
        double getBoundaryAzimuth(int index) const
        {
            assert(index < boundaries.size());
            return boundaries[index].azimuth();
        }
        
        double getBoundaryElevation(int index) const
        {
            assert(index < boundaries.size());
            return boundaries[index].elevation();
        }
        
        double x() const
        {
            return xyz[0];
        }
        
        double y() const
        {
            return xyz[1];
        }
        
        double z() const
        {
            return xyz[2];
        }
        
        double radius() const
        {
            return sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1] + xyz[1] * xyz[1]);
        }
        
        double azimuth() const
        {
            return atan2(xyz[1], xyz[0]);
        }
        
        double elevation() const
        {
            if (xyz[0] == 0 && xyz[1] == 0 && xyz[2] == 0)
                return VoroPi * 0.5;
            return acos(xyz[2] / radius());
        }
        
        double x_rel() const
        {
            return xyz_rel[0];
        }
        
        double y_rel() const
        {
            return xyz_rel[1];
        }
        
        double z_rel() const
        {
            return xyz_rel[2];
        }
        
        double radius_rel() const
        {
            return sqrt(xyz_rel[0] * xyz_rel[0] + xyz_rel[1] * xyz_rel[1] + xyz_rel[1] * xyz_rel[1]);
        }
        
        double azimuth_rel() const
        {
            return atan2(xyz_rel[1], xyz_rel[0]);
        }
        
        double distance(VoronoiPoint const& pt) const
        {
            return sqrt(pow(x() - pt.x(), 2) + pow(y() - pt.y(), 2) + pow(z() - pt.z(), 2));
        }
        
        VoronoiPoint cross(VoronoiPoint const& pt) const
        {
            return VoronoiPoint(y() * pt.z() - z() * pt.y(), z() * pt.x() - x() * pt.z(), x() * pt.y() - y() * pt.x());
        }
        
        VoronoiPoint operator-(VoronoiPoint const& pt) const;
        VoronoiPoint operator-(double scalar) const;
        VoronoiPoint& operator-=(VoronoiPoint const& pt);
        VoronoiPoint& operator-=(double scalar);
        
        VoronoiPoint operator+(VoronoiPoint const& pt) const;
        VoronoiPoint operator+(double scalar) const;
        VoronoiPoint& operator+=(VoronoiPoint const& pt);
        VoronoiPoint& operator+=(double scalar);
        
        VoronoiPoint operator*(VoronoiPoint const& pt) const;
        VoronoiPoint operator*(double scalar) const;
        VoronoiPoint& operator*=(VoronoiPoint const& pt);
        VoronoiPoint& operator*=(double scalar);
        
        VoronoiPoint operator/(VoronoiPoint const& pt) const;
        VoronoiPoint operator/(double scalar) const;
        VoronoiPoint& operator/=(VoronoiPoint const& pt);
        VoronoiPoint& operator/=(double scalar);
        
        static bool compareRelativeAzimuth(VoronoiPoint const& pt1, VoronoiPoint const& pt2)
        {
            return pt1.azimuth_rel() > pt2.azimuth_rel();
        }
        
        ~VoronoiPoint();
    };
    
    
    VoronoiPoint operator*(double scalar, VoronoiPoint const& pt);
    bool operator==(VoronoiPoint const& pt1, VoronoiPoint const& pt2);
    bool operator!=(VoronoiPoint const& pt1, VoronoiPoint const& pt2);
    
    /////////////////////////////////////////////////////////
    // Voronoi Circle ///////////////////////////////////////
    /////////////////////////////////////////////////////////
    class VoronoiCircle
    {
		private :
        double xyz[3];
        double rad;
        
        public :
        VoronoiCircle(double x, double y, double r);
        VoronoiCircle(double x, double y, double z, double r);
        VoronoiCircle(VoronoiPoint pt, double r);
        VoronoiCircle(VoronoiPoint pt1, VoronoiPoint pt2, VoronoiPoint pt3);
        ~VoronoiCircle();
        
        double x() const
        {
            return xyz[0];
        }
        
        double y() const
        {
            return xyz[1];
        }
        
        double z() const
        {
            return xyz[2];
        }
        
        VoronoiPoint center() const
        {
            return VoronoiPoint(x(), y(), z());
        }
        
        double radius() const
        {
            return rad;
        }
    };
    
    /////////////////////////////////////////////////////////
    // Voronoi //////////////////////////////////////////////
    /////////////////////////////////////////////////////////
	class Voronoi
	{
    private :

		std::vector<VoronoiPoint> points;
		void evaluateTriangle(int i, int j, int k);

	public :
		Voronoi();
		~Voronoi();

		void clear();
        void addPoint(double azimuth, double elevation = 0);
		void perform();

		unsigned int getNumberOfPoints() const
		{
			return points.size();
		};

		double getPointAzimuth(unsigned int index) const
		{
			assert(index < points.size());
			return points[index].azimuth();
		};

		double getPointElevation(unsigned int index) const
		{
			assert(index < points.size());
            return points[index].elevation();
            
		};

		unsigned int getPointVoronoiLenght(unsigned int index) const
		{
			assert(index < points.size());
            return points[index].getNumberOfBoundaries();
		};

        double getPointVoronoiAzimuth(unsigned int index, unsigned int index2) const
		{
			assert(index < points.size());
            return points[index].getBoundaryAzimuth(index2);
		};
        
        double getPointVoronoiElevation(unsigned int index, unsigned int index2) const
		{
			assert(index < points.size());
            return points[index].getBoundaryElevation(index2);
		};
	};
}

#endif



