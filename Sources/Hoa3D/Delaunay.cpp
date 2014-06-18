/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Delaunay.h"

namespace Hoa
{
	Delaunay::Delaunay(){};

	Delaunay::~Delaunay()
	{
		clear();
	};

	void Delaunay::clear()
	{
		points.clear();
		circles.clear();
	};

	void Delaunay::addPoint(double _azimuth, double _elevation, bool _bottom)
	{
		double abs;
		double ord;
		if((_bottom && _elevation > 0) || (!_bottom && _elevation < 0))
		{
			abs = cos(_azimuth) * (2. - fabs(2. * _elevation / HOA_PI));
			ord = sin(_azimuth) * (2. - fabs(2. * _elevation / HOA_PI));
		}
		else
		{
			abs = cos(_azimuth) * fabs(2. * _elevation / HOA_PI);
			ord = sin(_azimuth) * fabs(2. * _elevation / HOA_PI);
		}
		points.push_back(DelaunayPoint(abs, ord));
	};
			
	void Delaunay::perform()
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

	void Delaunay::evaluateTriangle(int i, int j, int k)
	{
		int size = points.size();
		double abs, ord, dist, angle, azi1, azi2;
		double ix = points[i].x, iy = points[i].y, jx = points[j].x, jy = points[j].y, kx = points[k].x, ky = points[k].y;
		
		abs = (jx - ix);
		ord = (jx - iy);
		dist = sqrt(abs * abs + ord * ord);
		if(abs == 0 && ord == 0)
			azi1 = 0;
		else
			azi1 = atan2(abs, ord);
		abs = (kx - ix);
		ord = (kx - iy);
		if(abs == 0 && ord == 0)
			azi2 = 0;
		else
			azi2 = atan2(abs, ord);
		angle =  azi1 - azi2;
		if(angle > HOA_PI)
			angle = HOA_PI - angle;

		double circle_radius = dist / sin(angle);
		double circle_abscissa = circle_radius + dist * 0.5;
		double circle_ordinate = circle_radius + points[i].y;
		
		// If one point is inside the circle, the circle is exclude.
		for(int l = 0; l < size; l++)
		{
			abs = circle_abscissa - points[l].x;
			ord = circle_ordinate - points[l].y;
			if(sqrt(abs * abs + ord * ord) < circle_radius)
			{
				return;
			}
		}

		// Else, the points save the circle and the circle save the the points.
		DelaunayCircle circle = DelaunayCircle(circle_abscissa, circle_ordinate, circle_radius);
		circle.points.push_back(&points[i]);
		circle.points.push_back(&points[j]);
		circle.points.push_back(&points[k]);
		circles.push_back(circle);
		points[i].circles.push_back(&circle);
		points[j].circles.push_back(&circle);
		points[k].circles.push_back(&circle);
	};    
}

