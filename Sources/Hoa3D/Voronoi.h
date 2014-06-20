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
#define Pi  (3.141592653589793238462643383279502884)

namespace Hoa
{
	//! The Voronoi triangulation and Voronoi diagram.
    /**
     */
	class Voronoi
	{
	private :
		class VoronoiPoint;
		class VoronoiCircle
		{
		public :
			double x;
			double y;
			double r;
			VoronoiPoint* pt;
			VoronoiCircle(double _x, double _y, double _r);
            ~VoronoiCircle();
            
			static bool compare(VoronoiCircle c1, VoronoiCircle c2)
			{
				double azi1, azi2, x = 0, y = 0;
				if(c1.pt)
				{
					x = c1.pt->x;
					y = c1.pt->y;
				}
				if(c1.x - x == 0 && c1.y - y == 0)
					azi1 = 0;
				else
					azi1 = atan2(c1.y - y, c1.x -x);
				if(c2.x - x == 0 && c2.y - y == 0)
					azi2 = 0;
				else
					azi2 = atan2(c2.y - y, c2.x - x);
				return azi1 < azi2;
			};
		};

		class VoronoiPoint
		{
		public :
			double x;
			double y;
			std::vector<VoronoiCircle> circles;
			VoronoiPoint(double _x, double _y);
			~VoronoiPoint();
		};
        
    public :
        enum Mode
        {
            Plane    = 0,
            Circle   = 1,
            Sphere   = 2
        };
    private :

		std::vector<VoronoiPoint> points;
        std::vector<VoronoiPoint> points_bottom;
        Mode  mode;
		void evaluateTriangle(int i, int j, int k, bool top = 1);

	public :
		Voronoi(Mode mode);
		~Voronoi();

		void clear();
        void addPointCartesian(double abscissa, double ordinate, double height = 0);
        void addPointPolar(double radius, double azimuth, double elevation = 0);
		void perform();

		unsigned int getNumberOfPoints() const
		{
			return points.size();
		};

		double getPointAbscissa(unsigned int index) const
		{
			assert(index < points.size());
			return points[index].x;
		};

		double getPointOrdinate(unsigned int index) const
		{
			assert(index < points.size());
			return points[index].y;
		};

		unsigned int getPointVoronoiLenght(unsigned int index) const
		{
			assert(index < points.size());
			return points[index].circles.size();
		};
        
        double getPointVoronoiRadius(unsigned int index, unsigned int index2) const
		{
			assert(index < points.size());
			assert(index2 < points[index].circles.size());
            if(mode == Plane)
                return sqrt(points[index].circles[index2].x * points[index].circles[index2].x + points[index].circles[index2].y * points[index].circles[index2].y);
            else
                return 1;
		};

        double getPointVoronoiAzimuth(unsigned int index, unsigned int index2) const
		{
			assert(index < points.size());
			assert(index2 < points[index].circles.size());
            return atan2(points[index].circles[index2].y, points[index].circles[index2].x);
		};
        
        double getPointVoronoiElevation(unsigned int index, unsigned int index2) const
		{
			assert(index < points.size());
			assert(index2 < points[index].circles.size());
            if(mode == Sphere)
            {
                double radius = sqrt(points[index].circles[index2].x * points[index].circles[index2].x + points[index].circles[index2].y * points[index].circles[index2].y);
                //double ptrad = sqrt(points[index].x * points[index].x + points[index].y * points[index].y);
                if(radius > 1)
                {
                    return -(radius - 1.) * Pi * 0.5;
                }
                else
                {
                    return (1. - radius) * Pi * 0.5;
                }
            }
            else
                return 0;
        
		};
        
		double getPointVoronoiAbscissa(unsigned int index, unsigned int index2) const
		{
			assert(index < points.size());
			assert(index2 < points[index].circles.size());
            if(mode == Sphere)
            {
                return 0;
            }
            else
                return  points[index].circles[index2].x;
		};

		double getPointVoronoiOrdinate(unsigned int index, unsigned int index2) const
		{
			assert(index < points.size());
			assert(index2 < points[index].circles.size());
            if(mode == Sphere)
                return 0;
            else
                return points[index].circles[index2].y;
		};
        
        double getPointVoronoiHeight(unsigned int index, unsigned int index2) const
		{
			assert(index < points.size());
			assert(index2 < points[index].circles.size());
            if(mode == Sphere)
                return 0;
            else
                return points[index].circles[index2].y;
		};
	};
}

#endif



