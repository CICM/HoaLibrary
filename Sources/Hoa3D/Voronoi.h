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
#define Voro2Pi (6.283185307179586476925286766559005)
#define VoroPi2 (1.57079632679489661923132169163975144)
#define VoroMin 0.002
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
        VoronoiPoint(double x_radius = 0, double y_azimuth = 0, double z_elevation = 0, bool polar = 0);
        
        void addBoundary(VoronoiPoint const& pt);
        void clearBoundaries();
        void sortBoundaries();
        void cleanBoundaries();
        void normalizeBoundaries();
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
        
        double getBoundaryRadius(int index) const
        {
            assert(index < boundaries.size());
            return boundaries[index].radius();
        }
        
        void postCartesian() const
        {
            post("Point Cartesian : %f %f %f", x(), y(), z());
        }
        
        void postPolar() const
        {
            post("Point Polar : %f %f %f", radius(), azimuth(), elevation());
        }
        
        void postBoundariesCartesian() const
        {
            for(int i = 0; i < boundaries.size(); i++)
                post("Boundary %i Cartesian : %f %f %f", i, boundaries[i].x(), boundaries[i].y(), boundaries[i].z());
        }
        
        void postBoundariesPolar() const
        {
            for(int i = 0; i < boundaries.size(); i++)
                post("Boundary %i Polar : %f %f %f", i, boundaries[i].radius(), boundaries[i].azimuth(), boundaries[i].elevation());
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
            return sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1] + xyz[2] * xyz[2]);
        }
        
        double azimuth() const
        {
            if(xyz[0] == 0 && xyz[1] == 0)
                return 0;
            return atan2(xyz[1], xyz[0]) - VoroPi2;
        }
        
        double elevation() const
        {
            if(xyz[2] == 0)
                return 0;
            return asin(xyz[2] / radius());
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
            double xm  = x() - pt.x(), ym = y() - pt.y(), zm = z() - pt.z();
            return sqrt(xm*xm + ym *ym + zm *zm);
        }
        
        VoronoiPoint cross(VoronoiPoint const& pt) const
        {
            return VoronoiPoint(y() * pt.z() - z() * pt.y(), z() * pt.x() - x() * pt.z(), x() * pt.y() - y() * pt.x());
        }
        
        void normalize();
        
        void shiftElevation(double elevation);
        void shiftElevation(VoronoiPoint const& pt);
        void shiftAzimuth(double azimuth);
        void shiftAzimuth(VoronoiPoint const& pt);
        void shiftRadius(double radius);
        void shiftRadius(VoronoiPoint const& pt);
        void shiftPolar(double radius, double azimuth, double elevation);
        void shiftPolar(VoronoiPoint const& pt);
        
        void shiftElevation(VoronoiPoint const& ref, double elevation);
        void shiftElevation(VoronoiPoint const& ref, VoronoiPoint const& pt);
        void shiftAzimuth(VoronoiPoint const& ref, double azimuth);
        void shiftAzimuth(VoronoiPoint const& ref, VoronoiPoint const& pt);
        void shiftRadius(VoronoiPoint const& ref, double radius);
        void shiftRadius(VoronoiPoint const& ref, VoronoiPoint const& pt);
        void shiftPolar(VoronoiPoint const& ref, double radius, double azimuth, double elevation);
        void shiftPolar(VoronoiPoint const& ref, VoronoiPoint const& pt);
        
        void translateAbscissa(double abscissa);
        void translateAbscissa(VoronoiPoint const& pt);
        void translateOrdinate(double ordinate);
        void translateOrdinate(VoronoiPoint const& pt);
        void translateHeight(double height);
        void translateHeight(VoronoiPoint const& pt);
        void translateCartesian(double abscissa, double ordinate, double height);
        void translateCartesian(VoronoiPoint const& pt);
        
        void rotateAroundX(double anglex);
        void rotateAroundY(double angley);
        void rotateAroundZ(double anglez);
        void rotateAroundZYX(double anglex, double angley, double anglez);
        void rotateAroundXYZ(double anglex, double angley, double anglez);
        
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
        
        VoronoiPoint& operator=(VoronoiPoint const& pt)
        {
            xyz[0] = pt.x();
            xyz[1] = pt.y();
            xyz[2] = pt.z();
            return *this;
        }
        
        inline bool operator==(VoronoiPoint const& pt) const
        {
            return (fabs(x() - pt.x()) < VoroMin) && (fabs(y() - pt.y()) < VoroMin) && (fabs(z() - pt.z()) < VoroMin);
        };
        
        inline bool operator!=(VoronoiPoint const& pt) const
        {
            return x() != pt.x() || y() != pt.y() || z() != pt.z();
        };

        static bool compareRelativeAzimuth(VoronoiPoint pt1, VoronoiPoint pt2)
        {
            return pt1.azimuth_rel() > pt2.azimuth_rel();
        }
        
        ~VoronoiPoint();
    };
    
    VoronoiPoint operator*(double scalar, VoronoiPoint const& pt);
    
    
    /////////////////////////////////////////////////////////
    // Voronoi Triangle /////////////////////////////////////
    /////////////////////////////////////////////////////////
    class VoronoiTriangle
    {
		private :
        VoronoiPoint pts[3];
        VoronoiPoint circumcenter;
        double circumradius;
        
        public :
        VoronoiTriangle(VoronoiPoint pt1, VoronoiPoint pt2, VoronoiPoint pt3);
        ~VoronoiTriangle();
        
        double getCircumcenterX() const
        {
            return circumcenter.x();
        }
        
        double getCircumcenterY() const
        {
            return circumcenter.y();
        }
        
        double getCircumcenterZ() const
        {
            return circumcenter.z();
        }
        
        VoronoiPoint getCircumcenter() const
        {
            return circumcenter;
        }
        
        double getCircumradius() const
        {
            return circumradius;
        }
        
        VoronoiPoint getPoint(int index) const
        {
            assert(index >= 0 && index < 3);
            return pts[index];
        }
        
        double getPointX(int index) const
        {
            assert(index >= 0 && index < 3);
            return pts[index].x();
        }
        
        double getPointY(int index) const
        {
            assert(index >= 0 && index < 3);
            return pts[index].y();
        }
        
        double getPointZ(int index) const
        {
            assert(index >= 0 && index < 3);
            return pts[index].z();
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
        
        double getPointVoronoiRadius(unsigned int index, unsigned int index2) const
		{
			assert(index < points.size());
            return points[index].getBoundaryRadius(index2);
		};
	};
}

#endif



