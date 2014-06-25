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
    VoronoiPoint::VoronoiPoint(double x_radius, double y_azimuth, double z_elevation, bool polar)
    {
        if(polar)
        {
            xyz_rel[0] = xyz[0] = x_radius * cos(y_azimuth + VoroPi2) * cos(z_elevation);
            xyz_rel[1] = xyz[1] = x_radius * sin(y_azimuth + VoroPi2) * cos(z_elevation);
            xyz_rel[2] = xyz[2] = x_radius * sin(z_elevation);
        }
        else
        {
            xyz_rel[0] = xyz[0] = x_radius;
            xyz_rel[1] = xyz[1] = y_azimuth;
            xyz_rel[2] = xyz[2] = z_elevation;
        }
    }
    
    void VoronoiPoint::clearBoundaries()
    {
        boundaries.clear();
    }
    
    void VoronoiPoint::addBoundary(VoronoiPoint const& pt)
    {
        const int size = boundaries.size();
        for(int i = 0; i < size; i++)
        {
            if(pt == boundaries[i])
            {
                return;
            }
        }
        boundaries.push_back(pt);
        boundaries[size].setRelativePoint(*this);
    }
    
    void VoronoiPoint::setRelativePoint(VoronoiPoint const& pt)
    {
        VoronoiPoint rel = *this;
        rel.rotateAroundZYX(-pt.x(), -pt.y(), -pt.z());
        xyz_rel[0] = rel.x();
        xyz_rel[1] = rel.y();
        xyz_rel[2] = rel.z();
    }
    
    void VoronoiPoint::normalizeBoundaries()
    {
        int size = boundaries.size();
        for(int i = 0; i < size; i++)
        {
            boundaries[i] = VoronoiPoint(1, boundaries[i].azimuth(), boundaries[i].elevation(), 1);
        }
    }
    
    void VoronoiPoint::cleanBoundaries()
    {
        int size = boundaries.size();
        for(int i = 0; i < size; i++)
        {
            for(int j = i+1; j < size; j++)
            {
                if(i != j && boundaries[i] == boundaries[j])
                {
                    boundaries.erase(boundaries.begin()+j);
                    size--;
                    j--;
                }
            }
        }
    }
    
    void VoronoiPoint::sortBoundaries()
    {
        std::sort(boundaries.begin(), boundaries.end(), compareRelativeAzimuth);
    }
    
    void VoronoiPoint::normalize()
    {
        *this = VoronoiPoint(1, azimuth(), elevation(), 1);
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
    
    void VoronoiPoint::shiftElevation(double ele)
    {
        double azi = azimuth();
        double rad = radius();
        ele += elevation();
        xyz[0] = rad * cos(azi + VoroPi2) * cos(ele);
        xyz[1] = rad * sin(azi + VoroPi2) * cos(ele);
        xyz[2] = rad * sin(ele);
    }
    
    void VoronoiPoint::shiftElevation(VoronoiPoint const& pt)
    {
        shiftElevation(pt.elevation());
    }
    
    void VoronoiPoint::shiftAzimuth(double azi)
    {
        azi += azimuth();
        double ele = elevation();
        double rad = radius();
        xyz[0] = rad * cos(azi + VoroPi2) * cos(ele);
        xyz[1] = rad * sin(azi + VoroPi2) * cos(ele);
        xyz[2] = rad * sin(ele);
    }
    
    void VoronoiPoint::shiftAzimuth(VoronoiPoint const& pt)
    {
        shiftAzimuth(pt.azimuth());
    }
    
    void VoronoiPoint::shiftRadius(double rad)
    {
        double azi = azimuth();
        double ele = elevation();
        rad += radius();
        xyz[0] = rad * cos(azi + VoroPi2) * cos(ele);
        xyz[1] = rad * sin(azi + VoroPi2) * cos(ele);
        xyz[2] = rad * sin(ele);
    }
    
    void VoronoiPoint::shiftRadius(VoronoiPoint const& pt)
    {
        shiftAzimuth(pt.radius());
    }
    
    void VoronoiPoint::shiftPolar(double rad, double azi, double ele)
    {
        azi += azimuth();
        ele += elevation();
        rad += radius();
        xyz[0] = rad * cos(azi + VoroPi2) * cos(ele);
        xyz[1] = rad * sin(azi + VoroPi2) * cos(ele);
        xyz[2] = rad * sin(ele);
    }
    
    void VoronoiPoint::shiftPolar(VoronoiPoint const& pt)
    {
        shiftPolar(pt.radius(), pt.azimuth(), pt.elevation());
    }
    
    void VoronoiPoint::shiftElevation(VoronoiPoint const& ref, double ele)
    {
        translateCartesian(-ref.x(), -ref.y(), -ref.z());
        shiftElevation(ele);
        translateCartesian(ref);
    }
    
    void VoronoiPoint::shiftElevation(VoronoiPoint const& ref, VoronoiPoint const& pt)
    {
        translateCartesian(-ref.x(), -ref.y(), -ref.z());
        shiftElevation(pt.elevation());
        translateCartesian(ref);
    }
    
    void VoronoiPoint::shiftAzimuth(VoronoiPoint const& ref, double azi)
    {
        translateCartesian(-ref.x(), -ref.y(), -ref.z());
        shiftAzimuth(azi);
        translateCartesian(ref);
    }
    
    void VoronoiPoint::shiftAzimuth(VoronoiPoint const& ref, VoronoiPoint const& pt)
    {
        translateCartesian(-ref.x(), -ref.y(), -ref.z());
        shiftAzimuth(pt.azimuth());
        translateCartesian(ref);
    }
    
    void VoronoiPoint::shiftRadius(VoronoiPoint const& ref, double rad)
    {
        translateCartesian(-ref.x(), -ref.y(), -ref.z());
        shiftRadius(rad);
        translateCartesian(ref);
    }
    
    void VoronoiPoint::shiftRadius(VoronoiPoint const& ref, VoronoiPoint const& pt)
    {
        translateCartesian(-ref.x(), -ref.y(), -ref.z());
        shiftRadius(pt.radius());
        translateCartesian(ref);
    }
    
    void VoronoiPoint::shiftPolar(VoronoiPoint const& ref, double rad, double azi, double ele)
    {
        translateCartesian(-ref.x(), -ref.y(), -ref.z());
        shiftPolar(rad, azi, ele),
        translateCartesian(ref);
    }
    
    void VoronoiPoint::shiftPolar(VoronoiPoint const& ref, VoronoiPoint const& pt)
    {
        translateCartesian(-ref.x(), -ref.y(), -ref.z());
        shiftPolar(pt),
        translateCartesian(ref);
    }
    
    void VoronoiPoint::translateAbscissa(double abs)
    {
        xyz[0] += abs;
    }
    
    void VoronoiPoint::translateAbscissa(VoronoiPoint const& pt)
    {
        xyz[0] += pt.x();
    }
    
    void VoronoiPoint::translateOrdinate(double ord)
    {
        xyz[1] += ord;
    }
    
    void VoronoiPoint::translateOrdinate(VoronoiPoint const& pt)
    {
        xyz[1] += pt.y();
    }
    
    void VoronoiPoint::translateHeight(double hei)
    {
        xyz[2] += hei;
    }
    
    void VoronoiPoint::translateHeight(VoronoiPoint const& pt)
    {
        xyz[2] += pt.z();
    }
    
    void VoronoiPoint::translateCartesian(double abs, double ord, double hei)
    {
        xyz[0] += abs;
        xyz[1] += ord;
        xyz[2] += hei;
    }
    
    void VoronoiPoint::translateCartesian(VoronoiPoint const& pt)
    {
        xyz[0] += pt.x();
        xyz[1] += pt.y();
        xyz[2] += pt.z();
    }
    
    void VoronoiPoint::rotateAroundX(double angle)
    {
        double cosAngle = cos(angle);
        double sinAngle = sin(angle);
        double ry = y() * cosAngle - z() * sinAngle;
        double rz = y() * sinAngle + z() * cosAngle;
        xyz[1] = ry;
        xyz[2] = rz;
    }
    
    void VoronoiPoint::rotateAroundY(double angle)
    {
        double cosAngle = cos(angle);
        double sinAngle = sin(angle);
        double rx = x() * cosAngle - z() * sinAngle;
        double rz = x() * sinAngle + z() * cosAngle;
        xyz[0] = rx;
        xyz[2] = rz;
    }
    
    void VoronoiPoint::rotateAroundZ(double angle)
    {
        double cosAngle = cos(angle);
        double sinAngle = sin(angle);
        double rx = x() * cosAngle - y() * sinAngle;
        double ry = x() * sinAngle + y() * cosAngle;
        xyz[0] = rx;
        xyz[1] = ry;
    }
    
    void VoronoiPoint::rotateAroundZYX(double anglex, double angley, double anglez)
    {
        double cosAnglex = cos(anglex);
        double sinAnglex = sin(anglex);
        double cosAngley = cos(angley);
        double sinAngley = sin(angley);
        double cosAnglez = cos(anglez);
        double sinAnglez = sin(anglez);
        double rx = x() * (cosAngley * cosAnglez) +
                    y() * (cosAnglez * sinAnglex * sinAngley - cosAnglex * sinAnglez) +
                    z() * (cosAnglex * cosAnglez * sinAngley - sinAnglex * sinAnglez);
        double ry = x() * (cosAngley * sinAnglez) +
                    y() * (cosAnglex * cosAnglez + sinAnglex * sinAngley * sinAnglez) +
                    z() * (cosAnglex * sinAngley * sinAnglez - cosAnglez * sinAnglex);
        double rz = x() * (-sinAngley) +
                    y() * (cosAngley * sinAnglex) +
                    z() * (cosAnglex * cosAngley);
        xyz[0] = rx;
        xyz[1] = ry;
        xyz[2] = rz;
    }
    
    void VoronoiPoint::rotateAroundXYZ(double anglex, double angley, double anglez)
    {
        double cosAnglex = cos(anglex);
        double sinAnglex = sin(anglex);
        double cosAngley = cos(angley);
        double sinAngley = sin(angley);
        double cosAnglez = cos(anglez);
        double sinAnglez = sin(anglez);
       
        double rx = x() * (cosAngley * cosAnglez) +
                    y() * (-cosAngley * sinAnglez) +
                    z() * (sinAngley);
        double ry = x() * (cosAnglex * sinAnglez + sinAnglex * sinAngley * cosAnglez) +
                    y() * (cosAnglex * cosAnglez - sinAnglex * sinAngley * sinAnglez) +
                    z() * (-sinAnglex * cosAngley);
        double rz = x() * (sinAnglex * sinAnglez - cosAnglex * sinAngley * cosAnglez) +
                    y() * (sinAnglex * cosAnglez + cosAnglex * sinAngley * sinAnglez) +
                    z() * (cosAnglex * cosAngley);
        xyz[0] = rx;
        xyz[1] = ry;
        xyz[2] = rz;
    }
    
    VoronoiPoint::~VoronoiPoint()
    {
        boundaries.clear();
    };
    
    
    /////////////////////////////////////////////////////////
    // Voronoi Circle ///////////////////////////////////////
    /////////////////////////////////////////////////////////
    
    VoronoiTriangle::VoronoiTriangle(VoronoiPoint pt1, VoronoiPoint pt2, VoronoiPoint pt3)
    {
        pts[0] = pt1;
        pts[1] = pt2;
        pts[2] = pt3;
        
        VoronoiPoint ref_translate = pt1;
        pt1.translateCartesian(-ref_translate.x(), -ref_translate.y(), -ref_translate.z());
        pt2.translateCartesian(-ref_translate.x(), -ref_translate.y(), -ref_translate.z());
        pt3.translateCartesian(-ref_translate.x(), -ref_translate.y(), -ref_translate.z());
        
        double ref_rotate_z = pt2.azimuth();
        pt2.rotateAroundZ(-ref_rotate_z);
        pt3.rotateAroundZ(-ref_rotate_z);

        double ref_rotate_x = pt2.elevation();
        pt2.rotateAroundX(-ref_rotate_x);
        pt3.rotateAroundX(-ref_rotate_x);
        
        double ref_rotate_y = atan2(pt3.z(), pt3.x());
        pt3.rotateAroundY(-ref_rotate_y);
        
        double alpha = pt3.azimuth();
        
        
        if((alpha < 0 && alpha > -VoroPi) || alpha > VoroPi)
        {
            alpha = 2. * sin(Voro2Pi - alpha);
            if(alpha < VoroMin)
                circumradius = -1;

            circumradius =  pt2.distance(pt3) / alpha;
            double y = pt2.y() * 0.5;
            if(fabs(y) > fabs(circumradius))
                circumradius = -1;

            double x = sqrt(circumradius * circumradius - y*y);
            circumcenter = VoronoiPoint(x, y, 0);
        }
        else
        {
            alpha = 2. * sin(alpha);
            if(alpha < VoroMin)
                circumradius = -1;

            circumradius =  pt2.distance(pt3) / alpha;
            double y = pt2.y() * 0.5;
            if(fabs(y) > fabs(circumradius))
                circumradius = -1;
            
            double x = sqrt(circumradius * circumradius - y*y);
            circumcenter = VoronoiPoint(-x, y, 0);
        }
        
        circumcenter.rotateAroundY(ref_rotate_y);
        circumcenter.rotateAroundX(ref_rotate_x);
        circumcenter.rotateAroundZ(ref_rotate_z);
        circumcenter.translateCartesian(ref_translate);
    }
    
    VoronoiTriangle::~VoronoiTriangle()
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
        points.push_back(VoronoiPoint(1, _azimuth, _elevation, 1));
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
        int b = 1;
        int size = points.size();
        if(i == b || j == b || k == b)
        {
            post("\n%i %i %i", i, j, k);
        }
        VoronoiTriangle triangle = VoronoiTriangle(points[i], points[j], points[k]);
        VoronoiPoint center = triangle.getCircumcenter();
        
        if(i == b || j == b || k == b)
            post("result : ");
        if(triangle.getCircumradius() < VoroMin || center.radius() < VoroMin)
        {
            if(i == b || j == b || k == b)
                post("removed by radius or center");
            return;
        }
        
        for(int l = 0; l < size; l++)
        {
            if(l != i && l != j && l != k && l)
            {
                if((points[l].distance(center) + VoroMin) < triangle.getCircumradius())
                {
                    if(i == b || j == b || k == b)
                    post("removed by %i : %f", l, points[l].distance(center));
                    return;
                }
            }
        }
        center.postPolar();
        center.normalize();
        if(i == b || j == b || k == b)
            center.postCartesian();
        if(i == 1 || j == 3 || k == 4)
            post("this one");
        points[i].addBoundary(center);
        points[j].addBoundary(center);
        points[k].addBoundary(center);
	};
}

