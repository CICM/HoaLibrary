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
    
    void VoronoiPoint::shiftElevation(double elevation)
    {
        xyz[0] = radius() * cos(azimuth()) * sin(elevation + elevation);
        xyz[1] = radius() * sin(azimuth()) * sin(elevation + elevation);
        xyz[2] = radius() * cos(elevation + elevation);
    }
    
    void VoronoiPoint::shiftElevation(VoronoiPoint const& pt)
    {
        shiftElevation(pt.elevation());
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
        int refindex1 = 1;
        VoronoiPoint ref_trans1 = pt1, ref_elev1, ref_elev2, ref_trans2;
        
        post("1 -----------------");
        post("%f %f %f", pt1.x(), pt1.y(), pt1.z());
        post("%f %f %f", pt2.x(), pt2.y(), pt2.z());
        post("%f %f %f", pt3.x(), pt3.y(), pt3.z());
        
        if(fabs(ref_trans1.z()) > fabs(pt2.z()))
        {
            ref_trans1 = pt2;
            refindex1 = 2;
        }
        if(fabs(ref_trans1.z()) > fabs(pt3.z()))
        {
            ref_trans1 = pt3;
            refindex1 = 3;
        }
        
        // Translate all the point with the ref point
        pt1 -= ref_trans1;
        pt2 -= ref_trans1;
        pt3 -= ref_trans1;
        
        post("2 -----------------");
        post("%f %f %f", pt1.x(), pt1.y(), pt1.z());
        post("%f %f %f", pt2.x(), pt2.y(), pt2.z());
        post("%f %f %f", pt3.x(), pt3.y(), pt3.z());
        
        if(refindex1 == 1)
        {
            ref_elev1 = pt2;
            if(fabs(ref_elev1.z()) > fabs(pt3.z()))
            {
                ref_elev1 = pt3;
                pt3.shiftElevation(-ref_elev1.elevation());
                pt2.shiftElevation(-ref_elev1.elevation());
                ref_trans2 = pt3;
                pt1 -= pt3;
                pt2 -= pt3;
                pt3 -= pt3;
                ref_elev2 = pt2;
                pt2.shiftElevation(-ref_elev2.elevation());
            }
            else
            {
                pt2.shiftElevation(-ref_elev1.elevation());
                pt3.shiftElevation(-ref_elev1.elevation());
                ref_trans2 = pt2;
                pt1 -= pt2;
                pt2 -= pt2;
                pt3 -= pt2;
                ref_elev2 = pt3;
                pt3.shiftElevation(-ref_elev2.elevation());
            }
        }
        else if(refindex1 == 2)
        {
            ref_elev1 = pt1;
            if(fabs(ref_elev1.z()) > fabs(pt3.z()))
            {
                ref_elev1 = pt3;
                pt3.shiftElevation(-ref_elev1.elevation());
                pt1.shiftElevation(-ref_elev1.elevation());
                ref_trans2 = pt3;
                pt1 -= pt3;
                pt2 -= pt3;
                pt3 -= pt3;
                ref_elev2 = pt1;
                pt1.shiftElevation(-ref_elev2.elevation());
            }
            else
            {
                pt1.shiftElevation(-ref_elev1.elevation());
                pt3.shiftElevation(-ref_elev1.elevation());
                ref_trans2 = pt1;
                pt1 -= pt1;
                pt2 -= pt1;
                pt3 -= pt1;
                ref_elev2 = pt3;
                pt3.shiftElevation(-ref_elev2.elevation());
            }
        }
        else
        {
            ref_elev1 = pt1;
            if(fabs(ref_elev1.z()) > fabs(pt2.z()))
            {
                ref_elev1 = pt2;
                pt2.shiftElevation(-ref_elev1.elevation());
                pt1.shiftElevation(-ref_elev1.elevation());
                ref_trans2 = pt2;
                pt1 -= pt2;
                pt2 -= pt2;
                pt3 -= pt2;
                ref_elev2 = pt1;
                pt1.shiftElevation(-ref_elev2.elevation());
                
            }
            else
            {
                pt1.shiftElevation(-ref_elev1.elevation());
                pt2.shiftElevation(-ref_elev1.elevation());
                ref_trans2 = pt1;
                pt1 -= pt1;
                pt2 -= pt1;
                pt3 -= pt1;
                ref_elev2 = pt2;
                pt2.shiftElevation(-ref_elev2.elevation());
            }
        }
        post("3 -----------------");
        post("%f %f %f", pt1.x(), pt1.y(), pt1.z());
        post("%f %f %f", pt2.x(), pt2.y(), pt2.z());
        post("%f %f %f", pt3.x(), pt3.y(), pt3.z());
        
        double ikx = (pt1.x() - pt3.x()), jky = (pt2.y() - pt3.y()), jkx = (pt2.x() - pt3.x()), iky = (pt1.y() - pt3.y()), ik_x = (pt1.x() + pt3.x()), ik_y = (pt1.y() + pt3.y()), jk_x = (pt2.x() + pt3.x()), jk_y = (pt2.y() + pt3.y());
        double D = ikx * jky - jkx * iky;
        if(!D)
        {
            xyz[0] = xyz[1] = xyz[2] = 0.;
            rad = -1;
            return;
        }
        
        VoronoiPoint center = VoronoiPoint(((ikx * ik_x + iky * ik_y) * 0.5 * jky - (jkx * jk_x + jky * jk_y) * 0.5 * iky) / D,
                                           ((jkx * jk_x + jky * jk_y) * 0.5 * ikx - (ikx * ik_x + iky * ik_y) * 0.5 * jkx) / D,
                                           0);
        rad = sqrt((center.x() - pt1.x()) * (center.x() - pt1.x()) + (center.y() - pt1.y()) * (center.y() - pt1.y()));
        
        center.shiftElevation(ref_elev2.elevation());
        center += ref_trans2;
        center.shiftElevation(ref_elev1.elevation());
        center += ref_trans1;
        
        xyz[0] = center.x();
        xyz[1] = center.y();
        xyz[2] = center.z();
        post("4 -----------------");
        post("%f %f %f", center.x(), center.y(), center.z());
        
        post("");
        
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
            points[i].sortBoundaries();
        }
	};

	void Voronoi::evaluateTriangle(int i, int j, int k)
	{
        int size = points.size();
        VoronoiCircle circle = VoronoiCircle(points[i], points[j], points[k]);
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
        points[i].addBoundary(circle.center());
        points[j].addBoundary(circle.center());
        points[k].addBoundary(circle.center());
	};
}

