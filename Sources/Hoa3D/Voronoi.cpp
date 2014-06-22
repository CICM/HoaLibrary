/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Voronoi.h"

namespace Hoa
{
    // Voronoi Sphere
    Voronoi::VoronoiSphere::VoronoiSphere(double _x, double _y, double _z, double _r)
    {
        x = _x;
        y = _y;
        z = _z;
        r = _r;
    }
    
    Voronoi::VoronoiSphere::VoronoiSphere(VoronoiPoint pt, double _r)
    {
        x = pt.x;
        y = pt.y;
        z = pt.z;
        r = _r;
    }
    
    Voronoi::VoronoiSphere::VoronoiSphere(VoronoiPoint pt1, VoronoiPoint pt2, VoronoiPoint pt3, VoronoiPoint pt4)
    {
        double a[12];
        a[0+0*3] = pt2.x - pt1.x;
        a[0+1*3] = pt2.y - pt1.y;
        a[0+2*3] = pt2.z - pt1.z;
        a[0+3*3] = pow(pt2.x - pt1.x, 2) + pow(pt2.y - pt1.y, 2) + pow(pt2.z - pt1.z, 2);
        
        a[1+0*3] = pt3.x - pt1.x;
        a[1+1*3] = pt3.y - pt1.y;
        a[1+2*3] = pt3.z - pt1.z;
        a[1+3*3] = pow(pt3.x - pt1.x, 2) + pow(pt3.y - pt1.y, 2) + pow(pt3.z - pt1.z, 2);
        
        a[2+0*3] = pt4.x - pt1.x;
        a[2+1*3] = pt4.y - pt1.y;
        a[2+2*3] = pt4.z - pt1.z;
        a[2+3*3] = pow(pt4.x - pt1.x, 2 ) + pow(pt4.y - pt1.y, 2) + pow(pt4.z - pt1.z, 2);
        
        if(dmat_solve(3, 1, a) != 0)
        {
            x = 0;
            y = 0;
            z = 0;
            r = -1;
            return;
        }

        r = 0.5 * sqrt(a[0+3*3] * a[0+3*3] + a[1+3*3] * a[1+3*3] + a[2+3*3] * a[2+3*3]);
        
        x = pt1.x + 0.5 * pt4.x;
        y = pt1.y + 0.5 * pt4.y;
        z = pt1.z + 0.5 * pt4.z;
    }
    
    Voronoi::VoronoiSphere::~VoronoiSphere(){};
    
    // Voronoi Circle
    Voronoi::VoronoiCircle::VoronoiCircle(double _x, double _y, double _r)
    {
        x = _x;
        y = _y;
        r = _r;
    };
    
    Voronoi::VoronoiCircle::VoronoiCircle(VoronoiPoint pt, double _r)
    {
        x = pt.x;
        y = pt.y;
        r = _r;
    }
    
    Voronoi::VoronoiCircle::VoronoiCircle(VoronoiPoint pt1, VoronoiPoint pt2, VoronoiPoint pt3)
    {
        double ikx = (pt1.x - pt3.x), jky = (pt2.y - pt3.y), jkx = (pt2.x - pt3.x), iky = (pt1.y - pt3.y), ik_x = (pt1.x + pt3.x), ik_y = (pt1.y + pt3.y), jk_x = (pt2.x + pt3.x), jk_y = (pt2.y + pt3.y);
        double D = ikx * jky - jkx * iky;
        if(!D)
        {
            x = 0;
            y = 0;
            r = -1;
            return;
        }
        
        x = ((ikx * ik_x + iky * ik_y) * 0.5 * jky - (jkx * jk_x + jky * jk_y) * 0.5 * iky) / D;
        y = ((jkx * jk_x + jky * jk_y) * 0.5 * ikx - (ikx * ik_x + iky * ik_y) * 0.5 * jkx) / D;
        r = sqrt((x - pt1.x) * (x - pt1.x) + (y - pt1.y) * (y - pt1.y));
    }
    
    Voronoi::VoronoiCircle::~VoronoiCircle()
    {
        ;
    };
    
    // Voronoi Point
    Voronoi::VoronoiPoint::VoronoiPoint(double _x, double _y, double _z){
        x = _x;
        y = _y;
        z = _z;
    };
    
    Voronoi::VoronoiPoint::~VoronoiPoint()
    {
        circles.clear();
        spheres.clear();
    };
    
    // Voronoi
	Voronoi::Voronoi(Mode _mode)
    {
        mode = _mode;
    };

	Voronoi::~Voronoi()
	{
		clear();
	};

	void Voronoi::clear()
	{
		points.clear();
	};
    
    void Voronoi::addPoint(double _azimuth, double _elevation)
    {
        if(mode == Circle)
        {
             points.push_back(VoronoiPoint(cos(_azimuth + HOA_PI2),
                                           sin(_azimuth + HOA_PI2)));
        }
        else
            points.push_back(VoronoiPoint(cos(_azimuth + HOA_PI2) * cos(_elevation),
                                          sin(_azimuth + HOA_PI2) * cos(_elevation),
                                          sin(_elevation)));
    }
			
	void Voronoi::perform()
	{
        if(mode == Sphere)
        {
            int size = points.size();
            for(int i = 0; i < size - 3; i++)
            {
                for(int j = i+1; j < size - 2; j++)
                {
                    for(int k = j+1; k < size - 1; k++)
                    {
                        for(int l = k+1; l < size; l++)
                        {
                            evaluateSphere(i, j, k, l);
                        }
                    }
                }
            }
            for(int i = 0; i < size; i++)
            {
                for(int j = 0; j < points[i].spheres.size(); j++)
                    points[i].spheres[j].pt = &points[i];
                std::sort(points[i].spheres.begin(), points[i].spheres.end(), VoronoiSphere::compare);
            }
        }
        else
        {
            int size = points.size();
            for(int i = 0; i < size - 2; i++)
            {
                for(int j = i+1; j < size - 1; j++)
                {
                    for(int k = j+1; k < size; k++)
                    {
                        evaluateTriangle(i, j, k);
                    }
                }
            }
            
            for(int i = 0; i < size; i++)
            {
                for(int j = 0; j < points[i].circles.size(); j++)
                    points[i].circles[j].pt = &points[i];
                std::sort(points[i].circles.begin(), points[i].circles.end(), VoronoiCircle::compare);
            }
        }
	};

	void Voronoi::evaluateTriangle(int i, int j, int k)
	{
        int size = points.size();
        VoronoiCircle circle = VoronoiCircle(points[i], points[j], points[k]);
        if(circle.r < 0)
            return;
        for(int l = 0; l < size; l++)
        {
            if(l != i && l != j && l != k && l)
            {
                if(sqrt(pow(circle.x - points[l].x, 2) + pow(circle.y - points[l].y, 2)) < circle.r)
                {
                    return;
                }
            }
        }
        points[i].circles.push_back(circle);
        points[j].circles.push_back(circle);
        points[k].circles.push_back(circle);
	};
    
    void Voronoi::evaluateSphere(int i, int j, int k, int l)
    {
        int size = points.size();
        VoronoiSphere sphere = VoronoiSphere(points[i], points[j], points[k], points[l]);
        post("0 %f", sphere.r);
        sphere = VoronoiSphere(points[j], points[i], points[k], points[l]);
        post("1 %f", sphere.r);
        sphere = VoronoiSphere(points[j], points[i], points[l], points[k]);
        post("2 %f", sphere.r);
        if(sphere.r < 0)
            return;
        
        for(int m = 0; m < size; m++)
        {
            if(m != i && m != j && m != k && m != l)
            {
                if(sqrt(pow(sphere.x - points[m].x, 2) + pow(sphere.y - points[m].y, 2) + pow(sphere.z - points[m].z, 2)) < sphere.r)
                {
                    return;
                }
            }
        }
        points[i].spheres.push_back(sphere);
        points[j].spheres.push_back(sphere);
        points[k].spheres.push_back(sphere);
        points[l].spheres.push_back(sphere);
    }
}

