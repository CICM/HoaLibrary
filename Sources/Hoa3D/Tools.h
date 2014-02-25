/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/


#ifndef DEF_HOA_3D_TOOLS
#define DEF_HOA_3D_TOOLS

#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string>

#ifdef __APPLE__

#include <Accelerate/Accelerate.h>

#endif

#ifdef _WINDOWS

#include <ipps.h>
#include <ippm.h>
#include <mkl.h>
#include <mkl_cblas.h>

#endif
    
#define CICM_PI  (3.141592653589793238462643383279502884)
#define CICM_2PI (6.283185307179586476925286766559005)
#define CICM_PI2 (1.57079632679489661923132169163975144)
#define CICM_PI4 (0.785398163397448309615660845819875721)

#define NUMBEROFLINEARPOINTS 10000
#define NUMBEROFCIRCLEPOINTS 36000
#define NUMBEROFCIRCLEPOINTS_UI 360

namespace Hoa3D
{
    //! The factorial
    /**	The function computes the factorial, the product of all positive integers less than or equal to an integer.
        \f[n! = n \times (n - 1) \times (n - 2) \times {...} \f]
     
        @param     n     The interger.
        @return    The function return the factorial of n.
     
        @see    double_factorial
     */
    inline unsigned long factorial(long n)
	{
        long result = n;
		if(n == 0)
			return 1;
        
		while(--n > 0)
			result *= n;
        
		return result;
	}
    
    //! The double factorial
    /**	The function computes the double factorial, the product of all the odd integers up to some odd positive integer :\n
        \f[n!! = n \times (n - 2) \times (n - 4) \times {...} \f]
     
        @param     n     The interger.
        @return    The function return the double factorial of n.
     
        @see    factorial
     */
    inline unsigned long double_factorial(long n)
	{
		if (n == 0 || n == -1) {
			return 1;
		}
        
		long result = n;
		while ((n -= 2) > 0) {
			result *= n;
		}
        
		return result;
	}
    
    //! The associated Legendre polynomials
    /**	The function computes the associated Legendre polynomial \f$P(l, m)\f$ that is a part of the formula that compute the spherical harmonic coefficient where l is the band and the m is the argument of a spherical harmonic and x is the cosinus of the elevation. It uses three recurrence formulas :
        \f[P(l, l)(x) = (-1)^l \times (2l - 1)!! \times (1 - x^2)^{0.5l}\f]
        \f[P(l + 1, l)(x) = x \times (2l + 1) \times P(l, l)\f]
        \f[P(l + 1, m)(x) = \frac{(2l + 1) \times x \times P(m, l) - (l + m) \times P(m, l - 1)}{(l - m + 1)}\f]
        with \f$0 \leq l\f$ and \f$-l \leq m \leq +l\f$
     
        @param     l    The band of the spherical harmonic.
        @param     m	The argument of the spherical harmonic.
        @param     x    The cosinus of the elevation.
        @return    The function return the associated Legendre polynomial of x for l and m.
     
        @see    legendre_normalization
        @see    spherical_harmonics
     */
	inline double associated_legendre(int l, int m, double x)
	{
        l = abs(l);
        m = abs(m);
        
		if(l == m)
        {
			return pow(-1.0f, (double)m) * double_factorial(2. * m - 1) * pow(1. - x * x, 0.5 * m);
		}
		else if(l == m + 1)
        {
			return x * (2 * m + 1) * associated_legendre(m, m, x);
		}
        else
        {
            return ((double)(2 * l - 1) * x *  associated_legendre(l - 1, m, x) - (double)(l + m - 1.) * associated_legendre(l - 2, m, x)) / (double)(l - m);
        }
	}
    
    //! The legendre normalization
    /**	The function normalizes the associated Legendre polynomial over \f$2\pi\f$ : \n
        if \f$ m = 0\f$
        \f[K(l) = \sqrt{\frac{2 \times l + 1}{4\pi}}\f]
        else
        \f[K(l, m) = \sqrt{2 \times \frac{2 \times l + 1}{4\pi} \times \frac{(l - |m|)!}{(l + |m|)!}}\f]
        with \f$0 \leq l\f$ and \f$-l \leq m \leq +l\f$
     
        @param     l    The band of the spherical harmonic.
        @param     m    The argument of the spherical harmonic.
        @return    The function return the normalization of the associated Legendre polynomial for l and m.
     
        @see    associated_legendre
        @see    spherical_harmonics
     */
    inline double legendre_normalization(int l, int m)
	{
        if(m == 0)
            return sqrt((2. * l + 1.) / (4. * CICM_PI));
        else
            return sqrt((2. * l + 1.) / (4. * CICM_PI) * (long double)factorial(l - abs(m)) / (long double)factorial(l + abs(m))) * sqrt(2.);
	}
    
    //! The azimuth part of the spherical harmonics function
    /**	The function computes the azimuth coefficient of the spherical harmonic \f$[l, m]\f$ for an angle \f$\phi\f$ in radian :\n
        if \f$ m \geq 0\f$
        \f[Y_{azimuth}(l, m, \phi) = cos(m \times \phi)\f]
        else
        \f[Y_{azimuth}(l, m, \phi) = sin(-m \times \phi)\f]
        with \f$0 \leq l\f$ and \f$-l \leq m \leq +l\f$
     
        @param     l    The band of the spherical harmonic.
        @param     m    The argument of the spherical harmonic.
        @param     phi  The azimuth.
        @return    The function return the azimuth coefficient for phi of the spherical harmonic of band l and argument m.
     
        @see    spherical_harmonics_elevation
        @see    spherical_harmonics
     */
    inline double spherical_harmonics_azimuth(int l, int m, double phi)
	{
        if(m >= 0)
            return cos((double)m * phi);
        else
            return sin((double)-m * phi);
    }
    
    //! The elevation part of the spherical harmonics function
    /**	The function computes the elevation coefficient of the the spherical harmonic \f$[l, m]\f$  for an angle \f$\theta\f$ in radian. It uses the associated Legendre polynomial and applies the Legendre normalization :
        \f[Y_{elevation}(l, m, \theta) = N(l, m) \times P(l, m, cos(/theta)\f]
        with \f$0 \leq l\f$, \f$-l \leq m \leq +l\f$ and \f$N\f$ the normalization and \f$P\f$ the associated Legendre polynomial.
     
        @param     l        The band of the spherical harmonic.
        @param     m        The argument of the spherical harmonic.
        @param     theta    The elevation.
        @return    The function return the elevation coefficient for theta of the spherical harmonic of band l and argument m.
     
        @see    legendre_normalization
        @see    associated_legendre
        @see    spherical_harmonics_azimuth
        @see    spherical_harmonics
     */
    inline double spherical_harmonics_elevation(int l, int m, double theta)
	{
        return legendre_normalization(l, m) * associated_legendre(l, m, cos(theta));
    }
    
    //! The spherical harmonics function
    /** The function computes the spherical harmonics coefficient for the angles \f$\phi\f$ and \f$\theta\f$ in radian.
        \f[Y(l, m, \phi, \theta) = Y_{azimuth}(l, m, \phi) \times Y_{elevation}(l, m, \theta)\f]
     
        @param     l        The band of the spherical harmonic.
        @param     m        The argument of the spherical harmonic.
        @param     phi      The azimuth.
        @param     theta    The elevation.
        @return    The function return the coefficient for phi and theta for the spherical harmonics of band l and argument m.
     
        @see    spherical_harmonics_azimuth
        @see    spherical_harmonics_elevation
     */
    inline double spherical_harmonics(int l, int m, double phi, double theta)
	{
        return spherical_harmonics_elevation(l, m, theta) * spherical_harmonics_azimuth(l, m, phi);
    }
    
    //! The wrapping function
    /** The function wraps a number between boundaries.
     
        @param     value   The value to wrap.
        @param     low     The low boundarie.
        @param     high    The high boundarie.
        @return    The function return the wrapped value.
     
        @see    wrap_twopi
     */
    inline double wrap(double value, double low, double high)
    {
        double increment = high - low;
        while(value < low)
        {
            value += increment;
        }
        
        while(value > high)
        {
            value -= increment;
        }
        
        return value;
    }
    
    //! The wrapping function over \f$2\pi\f$
    /** The function wraps a number between 0 and \f$2\pi\f$.
     
        @param     value   The value to wrap.
        @return    The function return the wrapped value.
     
        @see    wrap
     */
    inline double wrap_twopi(double value)
    {
        double new_value = value;
        while(new_value < 0.)
        {
            new_value += CICM_2PI;
        }
        
        while(new_value > CICM_2PI)
        {
            new_value -= CICM_2PI;
        }
        return new_value;
    }
    
    //! The clipping function
    /** The function clips a number between boundaries. \n
        If \f$x < min\f$, \f$f(x) = min\f$ else if \f$x > max\f$, \f$f(x) = max\f$ else \f$f(x) = x\f$.
     
        @param     value   The value to clip.
        @param     low     The low boundarie.
        @param     high    The high boundarie.
        @return    The function return the clipped value.
     
        @see    clip_min
        @see    clip_max
     */
    inline double clip_minmax(double value, double low, double high)
    {
        if(value < low)
            return low;
        else if(value > high)
            return high;
        else
            return value;
    }
    
    //! The minimum clipping function
    /** The function clips a number at a minimum value. \n
        If \f$x < min\f$, \f$f(x) = min\f$ else \f$f(x) = x\f$.
     
        @param     value   The value to clip.
        @param     low     The low boundarie.
        @return    The function return the clipped value.
     
        @see    clip_minmax
        @see    clip_max
     */
    inline double clip_min(double value, double low)
    {
        if(value < low)
            return low;
        else
            return value;
    }
    
    //! The maximum clipping function
    /** The function clips a number at a maximum value. \n
        If \f$x > max\f$, \f$f(x) = max\f$ else \f$f(x) = x\f$.
     
        @param     value   The value to clip.
        @param     high    The high boundarie.
        @return    The function return the clipped value.
     
        @see    clip_minmax
        @see    clip_min
     */
    inline double clip_max(const double value, const double high)
    {
        if(value > high)
            return high;
        else
            return value;
    }
    
    inline double radius(const double x, const double y)
	{
		return sqrt(x*x + y*y);
	}
    
	inline double angle(const double x, const double y)
	{
		return atan2(y, x) + CICM_PI2;
	}
    
	inline double ordinate(const double radius, const double angle)
	{
		return radius * sin(angle - CICM_PI2);
	}
    
    inline double abscissa(const double radius, const double angle)
	{
		return radius * cos(angle - CICM_PI2);
	}
    
    inline double radius(double x, double y, double z)
	{
		return sqrt(x*x + y*y + z*z);
	}
    
	inline double azimuth(double x, double y, double z)
	{
		return angle(x, y);
	}
    
    inline double elevation(double x, double y, double z)
	{
		return acos(z / radius(x, y, z));
	}
    
	inline double ordinate(double radius, double phi, double theta)
	{
		return radius * sin(phi - CICM_PI2) * cos(theta);
	}
    
    inline double abscissa(double radius, double phi, double theta)
	{
		return radius * cos(phi - CICM_PI2) * cos(theta);
	}
    
    inline double height(double radius, double phi, double theta)
	{
		return radius * sin(theta);
	}
    
    inline double distance(double x1, double y1, double x2, double y2)
	{
		return sqrt((x1-x2) * (x1-x2) + (y1-y2) * (y1-y2));
	}
    
    inline double distance(double x1, double y1, double z1, double x2, double y2, double z2)
	{
		return sqrt((x1-x2) * (x1-x2) + (y1-y2) * (y1-y2) + (z1-z2) * (z1-z2));
	}
    
    //! The int to string conversion
    /** The function converts a interger to a string.
     
        @param     value   The value to convert.
        @return    The function return value in a string format.
     */
    inline std::string int_to_string(int aValue)
    {
        char number[256];
        sprintf(number, "%i", aValue);
        return number;
    }
    
    inline void sphere_normalize_point(double* point)
    {
        double length = sqrt(point[0] * point[0] + point[1] * point[1] + point[2] * point[2]);
        if (length != 0)
        {
            point[0] /= length;
            point[1] /= length;
            point[2] /= length;
        }
        else
        {
            point[0] = 0;
            point[1] = 0;
            point[2] = 0;
        }
    }
    
    inline unsigned int sphere_discretize(double** facets, unsigned int numberOfIterations)
    {
        double p[6][3];
        double pa[3], pb[3], pc[3];
        unsigned int nt = 0, ntold;
    
        p[5][2] = p[4][2] = p[3][2] = p[2][2] = p[1][0] = p[0][0] = p[1][1] = p[0][1] = 0;
        p[5][1] = p[4][1] = p[4][0] = p[3][0] = p[0][2] = 1;
        p[5][0] = p[3][1] = p[2][1] = p[2][0] = p[1][2] = -1;
        
        // Create the level 0 object
        double a = 1 / sqrt(2.0);
        for(unsigned int i = 0; i < 6; i++)
        {
            p[i][0] *= a;
            p[i][1] *= a;
        }
        
        memcpy(&facets[0][0], p[0], sizeof(double) * 3);
        memcpy(&facets[0][3], p[3], sizeof(double) * 3);
        memcpy(&facets[0][6], p[4], sizeof(double) * 3);
        
        memcpy(&facets[1][0], p[0], sizeof(double) * 3);
        memcpy(&facets[1][3], p[4], sizeof(double) * 3);
        memcpy(&facets[1][6], p[5], sizeof(double) * 3);
        
        memcpy(&facets[2][0], p[0], sizeof(double) * 3);
        memcpy(&facets[2][3], p[5], sizeof(double) * 3);
        memcpy(&facets[2][6], p[2], sizeof(double) * 3);
        
        memcpy(&facets[3][0], p[0], sizeof(double) * 3);
        memcpy(&facets[3][3], p[2], sizeof(double) * 3);
        memcpy(&facets[3][6], p[3], sizeof(double) * 3);
        
        memcpy(&facets[4][0], p[1], sizeof(double) * 3);
        memcpy(&facets[4][3], p[4], sizeof(double) * 3);
        memcpy(&facets[4][6], p[3], sizeof(double) * 3);
    
        memcpy(&facets[5][0], p[1], sizeof(double) * 3);
        memcpy(&facets[5][3], p[5], sizeof(double) * 3);
        memcpy(&facets[5][6], p[4], sizeof(double) * 3);
    
        memcpy(&facets[6][0], p[1], sizeof(double) * 3);
        memcpy(&facets[6][3], p[2], sizeof(double) * 3);
        memcpy(&facets[6][6], p[5], sizeof(double) * 3);
        
        memcpy(&facets[7][0], p[1], sizeof(double) * 3);
        memcpy(&facets[7][3], p[3], sizeof(double) * 3);
        memcpy(&facets[7][6], p[2], sizeof(double) * 3);
        nt = 8;
        
        // Bisect each edge and move to the surface of a unit sphere
        for(unsigned int it = 0; it < numberOfIterations; it++)
        {
            ntold = nt;
            for(unsigned int i = 0; i < ntold; i++)
            {
                pa[0] = (facets[i][0] + facets[i][3]) / 2;
                pa[1] = (facets[i][1] + facets[i][4]) / 2;
                pa[2] = (facets[i][2] + facets[i][5]) / 2;
                pb[0] = (facets[i][3] + facets[i][6]) / 2;
                pb[1] = (facets[i][4] + facets[i][7]) / 2;
                pb[2] = (facets[i][5] + facets[i][8]) / 2;
                pc[0] = (facets[i][6] + facets[i][0]) / 2;
                pc[1] = (facets[i][7] + facets[i][1]) / 2;
                pc[2] = (facets[i][8] + facets[i][2]) / 2;
                sphere_normalize_point(pa);
                sphere_normalize_point(pb);
                sphere_normalize_point(pc);
                memcpy(&facets[nt][0], &facets[i][0], sizeof(double) * 3);
                memcpy(&facets[nt][3], pa, sizeof(double) * 3);
                memcpy(&facets[nt][6], pc, sizeof(double) * 3);
                nt++;
                memcpy(&facets[nt][0], pa, sizeof(double) * 3);
                memcpy(&facets[nt][3], &facets[i][3], sizeof(double) * 3);
                memcpy(&facets[nt][6], pb, sizeof(double) * 3);
                nt++;
                memcpy(&facets[nt][0], pb, sizeof(double) * 3);
                memcpy(&facets[nt][3], &facets[i][6], sizeof(double) * 3);
                memcpy(&facets[nt][6], pc, sizeof(double) * 3);
                nt++;
                memcpy(&facets[i][0], pa, sizeof(double) * 3);
                memcpy(&facets[i][3], pb, sizeof(double) * 3);
                memcpy(&facets[i][6], pc, sizeof(double) * 3);
            }
        }
        
        return nt;
    }
    
    inline void facet_cartopol(double *facets)
    {
        double x, y, z;
        for(int i = 0; i < 9; i += 3)
        {
            x = facets[i];
            y = facets[i+1];
            z = facets[i+2];
            facets[i] = 1.;
            facets[i+1] = azimuth(x, y, z);
            facets[i+1] = elevation(x, y, z);
        }
    }
    
    inline void facet_poltocar(double *facets)
    {
        double r, a, e;
        for(int i = 0; i < 9; i += 3)
        {
            r = facets[i];
            a = facets[i+1];
            e = facets[i+2];
            facets[i] = abscissa(r, a, e);
            facets[i+1] = elevation(r, a, e);
            facets[i+1] = height(r, a, e);
        }
    }
}

#endif
