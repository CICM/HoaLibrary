/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Voronoi.h"

namespace Hoa
{
    /////////////////////////////////////////////////////////
    // Voronoi Point ////////////////////////////////////////
    /////////////////////////////////////////////////////////
    VoronoiPoint::VoronoiPoint(double x, double y, double z)
    {
        xyz[0] = x;
        xyz[1] = y;
        xyz[2] = z;
        
        xyz_rel[0] = x;
        xyz_rel[1] = y;
        xyz_rel[2] = z;
    };
    
    void VoronoiPoint::addBoundary(VoronoiPoint pt)
    {
        boundaries.push_back(pt);
        boundaries[boundaries.size()-1].setRelativePoint(*this);
    }
    
    void VoronoiPoint::setRelativePoint(VoronoiPoint const& pt)
    {
        double azi = azimuth() - azimuth();
        xyz_rel[0] = cos(azi) * this->radius();
        xyz_rel[1] = sin(azi) * this->radius();
        azi = atan2(z(), xyz_rel[0]) - VoroPi * 0.5 - atan2(pt.z(), pt.x());
        xyz_rel[0] = cos(azi) * this->radius();
        xyz_rel[2] = sin(azi) * this->radius();
    }
    
    void VoronoiPoint::clearBoundaries()
    {
        boundaries.clear();
    }
    
    void VoronoiPoint::sortBoundaries()
    {
        std::sort(boundaries.begin(), boundaries.end(), compareRelativeAzimuth);
    }
    
    VoronoiPoint VoronoiPoint::operator-(VoronoiPoint const& pt) const
    {
        return VoronoiPoint(x() - pt.x(), y() - pt.y(), z() - pt.z());
    }
    
    VoronoiPoint VoronoiPoint::operator-(double f) const
    {
        return VoronoiPoint(x() - f, y() - f, z() - f);
    }
    
    VoronoiPoint& VoronoiPoint::operator-=(VoronoiPoint const& pt)
    {
        xyz[0] -= pt.x();
        xyz[1] -= pt.y();
        xyz[2] -= pt.z();
        return *this;
    }
    
    VoronoiPoint& VoronoiPoint::operator-=(double f)
    {
        xyz[0] -= f;
        xyz[1] -= f;
        xyz[2] -= f;
        return *this;
    }
    
    VoronoiPoint VoronoiPoint::operator+(VoronoiPoint const& pt) const
    {
        return VoronoiPoint(x() + pt.x(), y() + pt.y(), z() + pt.z());
    }
    
    VoronoiPoint VoronoiPoint::operator+(double f) const
    {
        return VoronoiPoint(x() + f, y() + f, z() + f);
    }
    
    VoronoiPoint& VoronoiPoint::operator+=(VoronoiPoint const& pt)
    {
        xyz[0] += pt.x();
        xyz[1] += pt.y();
        xyz[2] += pt.z();
        return *this;
    }
    
    VoronoiPoint& VoronoiPoint::operator+=(double f)
    {
        xyz[0] += f;
        xyz[1] += f;
        xyz[2] += f;
        return *this;
    }
    
    VoronoiPoint VoronoiPoint::operator*(VoronoiPoint const& pt) const
    {
        return VoronoiPoint(x() * pt.x(), y() * pt.y(), z() * pt.z());
    }
    
    VoronoiPoint VoronoiPoint::operator*(double f) const
    {
        return VoronoiPoint(x() * f, y() * f, z() * f);
    }
    
    VoronoiPoint operator*(double f, VoronoiPoint const& pt)
    {
        return VoronoiPoint(pt.x() * f, pt.y() * f, pt.z() * f);
    }
    
    VoronoiPoint& VoronoiPoint::operator*=(VoronoiPoint const& pt)
    {
        xyz[0] *= pt.x();
        xyz[1] *= pt.y();
        xyz[2] *= pt.z();
        return *this;
    }
    
    VoronoiPoint& VoronoiPoint::operator*=(double f)
    {
        xyz[0] *= f;
        xyz[1] *= f;
        xyz[2] *= f;
        return *this;
    }
    
    VoronoiPoint VoronoiPoint::operator/(VoronoiPoint const& pt) const
    {
        return VoronoiPoint(x() / pt.x(), y() / pt.y(), z() / pt.z());
    }
    
    VoronoiPoint VoronoiPoint::operator/(double f) const
    {
        return VoronoiPoint(x() / f, y() / f, z() / f);
    }
    
    VoronoiPoint& VoronoiPoint::operator/=(VoronoiPoint const& pt)
    {
        xyz[0] /= pt.x();
        xyz[1] /= pt.y();
        xyz[2] /= pt.z();
        return *this;
    }
    
    VoronoiPoint& VoronoiPoint::operator/=(double f)
    {
        xyz[0] /= f;
        xyz[1] /= f;
        xyz[2] /= f;
        return *this;
    }
    
    bool operator==(VoronoiPoint const& pt1, VoronoiPoint const& pt2)
    {
        return pt1.x() == pt2.x() && pt1.y() == pt2.y() && pt1.z() == pt2.z();
    }
    
    bool operator!=(VoronoiPoint const& pt1, VoronoiPoint const& pt2)
    {
        return pt1.x() != pt2.x() || pt1.y() != pt2.y() || pt1.z() != pt2.z();
    }
    
    VoronoiPoint::~VoronoiPoint()
    {
        boundaries.clear();
    };
    
    /////////////////////////////////////////////////////////
    // Voronoi Circle ///////////////////////////////////////
    /////////////////////////////////////////////////////////
    VoronoiCircle::VoronoiCircle(double x, double y, double r)
    {
        xyz[0] = x;
        xyz[1] = y;
        xyz[2] = 0;
        rad = r;
    };
    
    VoronoiCircle::VoronoiCircle(double x, double y, double z, double r)
    {
        xyz[0] = x;
        xyz[1] = y;
        xyz[2] = z;
        rad = r;
    };
    
    VoronoiCircle::VoronoiCircle(VoronoiPoint pt, double r)
    {
        xyz[0] = pt.x();
        xyz[1] = pt.y();
        xyz[2] = pt.z();
        rad = r;
    }
    
    VoronoiCircle::VoronoiCircle(VoronoiPoint pt1, VoronoiPoint pt2, VoronoiPoint pt3)
    {
        VoronoiPoint ac = pt3 - pt1;
        VoronoiPoint ab = pt2 - pt1;
        VoronoiPoint abXac = ab.cross(ac);
        if(abXac.radius() < 0)
        {
            xyz[0] = 0;
            xyz[1] = 0;
            xyz[2] = 0;
            rad    = -1;
        }
        // (abXac.cross( ab )*ac.len2() + ac.cross( abXac )*ab.len2()) / (2.f*abXac.len2()) ;
        VoronoiPoint toCircumsphereCenter = (abXac.cross(ab) * ac.radius() * ac.radius() + ac.cross(abXac) * ab.radius() *  ab.radius()) / (2. * abXac.radius() * abXac.radius()) ;
        rad = toCircumsphereCenter.radius() ;
        VoronoiPoint center = pt1 + toCircumsphereCenter;
        xyz[0] = center.x();
        xyz[1] = center.y();
        xyz[2] = center.z();
        
        double ikx = (pt1.x() - pt3.x()), jky = (pt2.y() - pt3.y()), jkx = (pt2.x() - pt3.x()), iky = (pt1.y() - pt3.y()), ik_x = (pt1.x() + pt3.x()), ik_y = (pt1.y() + pt3.y()), jk_x = (pt2.x() + pt3.x()), jk_y = (pt2.y() + pt3.y());
        double D = ikx * jky - jkx * iky;
        if(!D)
            return;
        
        xyz[0] = ((ikx * ik_x + iky * ik_y) * 0.5 * jky - (jkx * jk_x + jky * jk_y) * 0.5 * iky) / D;
        xyz[1] = ((jkx * jk_x + jky * jk_y) * 0.5 * ikx - (ikx * ik_x + iky * ik_y) * 0.5 * jkx) / D;
        double abs = xyz[0] - pt1.x();
        double ord = xyz[1] - pt1.y();
        rad = sqrt(abs * abs + ord * ord);
    }
    
    VoronoiCircle::~VoronoiCircle()
    {
        ;
    };
    
    /////////////////////////////////////////////////////////
    // Voronoi //////////////////////////////////////////////
    /////////////////////////////////////////////////////////
	Voronoi::Voronoi()
    {
        ;
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
        points.push_back(VoronoiPoint(cos(_azimuth + HOA_PI2) * cos(_elevation),
                                      sin(_azimuth + HOA_PI2) * cos(_elevation),
                                      sin(_elevation)));
    }
			
	void Voronoi::perform()
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
            pt1.sortBoundaries();
        }
	};

	void Voronoi::evaluateTriangle(int i, int j, int k)
	{
        int size = points.size();
        VoronoiCircle circle = VoronoiCircle(pt1, pt2, pt3);
        if(circle.radius() < 0)
            return;
        
        for(int l = 0; l < size; l++)
        {
            if(l != i && l != j && l != k && l)
            {
                if(points[l].distance(circle.center()) < circle.radius())
                {
                    return;
                }
            }
        }
        pt1.addBoundary(circle.center());
        pt2.addBoundary(circle.center());
        pt3.addBoundary(circle.center());
	};
}

