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
	//! The Delaunay triangulation and Voronoi diagram.
    /**
     */
	class Voronoi
	{
	private :
		class VoronoiPoint;
        
        class VoronoiSphere
		{
            public :
			double x;
			double y;
            double z;
			double r;
			VoronoiPoint* pt;
			VoronoiSphere(double _x, double _y, double _z, double _r);
            VoronoiSphere(VoronoiPoint pt, double _r);
            VoronoiSphere(VoronoiPoint pt1, VoronoiPoint pt2, VoronoiPoint pt3, VoronoiPoint pt4);
            ~VoronoiSphere();
            
			static bool compare(VoronoiSphere c1, VoronoiSphere c2)
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
        
		class VoronoiCircle
		{
		public :
			double x;
			double y;
			double r;
			VoronoiPoint* pt;
			VoronoiCircle(double _x, double _y, double _r);
            VoronoiCircle(VoronoiPoint pt, double _r);
            VoronoiCircle(VoronoiPoint pt1, VoronoiPoint pt2, VoronoiPoint pt3);
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
            double z;
			std::vector<VoronoiCircle> circles;
            std::vector<VoronoiSphere> spheres;
			VoronoiPoint(double _x, double _y, double _z = 0);
			~VoronoiPoint();
		};
        
    public :
        enum Mode
        {
            Circle   = 0,
            Sphere   = 1
        };
    private :

		std::vector<VoronoiPoint> points;
        Mode  mode;
		void evaluateTriangle(int i, int j, int k);
        void evaluateSphere(int i, int j, int k, int l);

	public :
		Voronoi(Mode mode);
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
			return atan2(points[index].y, points[index].x) - VoroPi * 0.5;
		};

		double getPointElevation(unsigned int index) const
		{
			assert(index < points.size());
            if(mode == Circle)
                return 0;
            else if (points[index].x == 0 && points[index].y == 0 && points[index].z == 0)
                return 0;
            else
                return VoroPi * 0.5 - acos(points[index].z / sqrt(points[index].x*points[index].x + points[index].y*points[index].y + points[index].z*points[index].z));
            
		};

		unsigned int getPointVoronoiLenght(unsigned int index) const
		{
			assert(index < points.size());
            if(mode == Circle)
                return points[index].circles.size();
            else
                return points[index].spheres.size();
		};

        double getPointVoronoiAzimuth(unsigned int index, unsigned int index2) const
		{
			assert(index < points.size());
            if(mode == Circle)
            {
                assert(index2 < points[index].circles.size());
                return atan2(points[index].circles[index2].y, points[index].circles[index2].x) - VoroPi * 0.5;
            }
            else
            {
                assert(index2 < points[index].spheres.size());
                return atan2(points[index].spheres[index2].y, points[index].spheres[index2].x) - VoroPi * 0.5;
            }
		};
        
        double getPointVoronoiElevation(unsigned int index, unsigned int index2) const
		{
			assert(index < points.size());
            if(mode == Circle)
            {
                assert(index2 < points[index].circles.size());
                return 0;
            }
            else
            {
                assert(index2 < points[index].spheres.size());
                if (points[index].spheres[index2].x == 0 && points[index].spheres[index2].y == 0 && points[index].spheres[index2].z == 0)
                    return 0;
                else
                    return VoroPi * 0.5 - acos(points[index].spheres[index2].z / sqrt(points[index].spheres[index2].x*points[index].spheres[index2].x + points[index].spheres[index2].y*points[index].spheres[index2].y + points[index].spheres[index2].z*points[index].spheres[index2].z));
            }
		};
	};
    
    inline int dmat_solve(int n, int rhs_num, double a[])
    {
        double apivot;
        double factor;
        int i;
        int ipivot;
        int j;
        int k;
        double temp;
        
        for ( j = 0; j < n; j++ )
        {
            //
            //  Choose a pivot row.
            //
            ipivot = j;
            apivot = a[j+j*n];
            
            for ( i = j; i < n; i++ )
            {
                if ( abs ( apivot ) < abs ( a[i+j*n] ) )
                {
                    apivot = a[i+j*n];
                    ipivot = i;
                }
            }
            
            if ( apivot == 0.0 )
            {
                return j;
            }
            //
            //  Interchange.
            //
            for ( i = 0; i < n + rhs_num; i++ )
            {
                temp          = a[ipivot+i*n];
                a[ipivot+i*n] = a[j+i*n];
                a[j+i*n]      = temp;
            }
            //
            //  A(J,J) becomes 1.
            //
            a[j+j*n] = 1.0;
            for ( k = j; k < n + rhs_num; k++ )
            {
                a[j+k*n] = a[j+k*n] / apivot;
            }
            //
            //  A(I,J) becomes 0.
            //
            for ( i = 0; i < n; i++ )
            {
                if ( i != j )
                {
                    factor = a[i+j*n];
                    a[i+j*n] = 0.0;
                    for ( k = j; k < n + rhs_num; k++ )
                    {
                        a[i+k*n] = a[i+k*n] - factor * a[j+k*n];
                    }
                }
                
            }
            
        }
        
        return 0;
    }
}

#endif



