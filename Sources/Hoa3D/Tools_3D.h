/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __DEF_HOA_3D_TOOLS__
#define __DEF_HOA_3D_TOOLS__

#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string>
#include <assert.h>

#ifdef __APPLE__

#include <Accelerate/Accelerate.h>

#endif

#ifdef _WINDOWS

#include <gsl_cblas.h>

#endif

#ifdef _LINUX

#include <cblas.h>

#endif

#define HOA_PI  (3.141592653589793238462643383279502884)
#define HOA_2PI (6.283185307179586476925286766559005)
#define HOA_PI2 (1.57079632679489661923132169163975144)
#define HOA_PI4 (0.785398163397448309615660845819875721)

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
			return pow((double)-1.0, (double)m) * pow((double)(1. - x * x), (double)(0.5 * m)) * double_factorial(2. * m - 1);
		}
		else if(l == m + 1)
        {
			return x * associated_legendre(m, m, x) * (2 * m + 1);
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
            return sqrt((2. * l + 1.) / (4. * HOA_PI));
        else
            return sqrt((2. * l + 1.) / (4. * HOA_PI) * (long double)factorial(l - abs(m)) / (long double)factorial(l + abs(m))) * sqrt(2.);
	}

    /*
    inline double hoa_normalization(int l, int m)
	{
        l = abs(l);
        m = abs(m);
        if(m == l || m == 0)
            return 1. / double_factorial(2. * m - 1);
        else if(l == m + 1)
            return 1. / associated_legendre(l, m , cos(HOA_PI / 4.));
        else if(l == m + 2)
            return 1. / associated_legendre(l, m , cos(HOA_PI / 2.));
        else
            return 1.;
    }*/

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
        return associated_legendre(l, m, cos(theta)) * legendre_normalization(l, m);
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

    inline double radius(double x, double y, double z)
	{
		return sqrt(x*x + y*y + z*z);
	}

	inline double azimuth(double x, double y, double z)
	{
		return atan2(y, x) + HOA_PI2;
	}

    inline double elevation(double x, double y, double z)
	{
		return acos(z / radius(x, y, z));
	}

	inline double ordinate(double radius, double phi, double theta)
	{
		return radius * sin(phi - HOA_PI2) * cos(theta);
	}

    inline double abscissa(double radius, double phi, double theta)
	{
		return radius * cos(phi - HOA_PI2) * cos(theta);
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

    inline void sphere_discretize(unsigned int numberOfPoints, double* azimuths, double* elevations)
    {
        if(numberOfPoints == 4) // Tethrahedron
        {
            azimuths[0] = 0.;
            elevations[0] = HOA_PI2;
            azimuths[1] = 0.;
            azimuths[2] = HOA_2PI / 3.;
            azimuths[3] = 2. * HOA_2PI / 3.;
            elevations[1] = elevations[2] = elevations[3] = HOA_PI2 - HOA_2PI / 3.;
        }
        else if(numberOfPoints == 5) // Not regular : Octahedron with only 3 points at 0 azymuth
        {
            azimuths[0] = 0.;
            elevations[0] = HOA_PI2;
            azimuths[1] = 0.;
            azimuths[2] = HOA_2PI / 3.;
            azimuths[3] = 2. * HOA_2PI / 3.;
            elevations[1] = elevations[2] = elevations[3] = 0;
            azimuths[4] = 0.;
            elevations[4] = -HOA_PI2;
        }
        else if(numberOfPoints == 6) // Octahedron
        {
            azimuths[0] = 0.;
            elevations[0] = HOA_PI2;
            azimuths[1] = 0.;
            azimuths[2] = HOA_PI2;
            azimuths[3] = 2. * HOA_PI2;
            azimuths[4] = 3. * HOA_PI2;
            elevations[1] = elevations[2] = elevations[3] = elevations[4] = 0;
            azimuths[5] = 0.;
            elevations[5] = -HOA_PI2;
        }
        else if(numberOfPoints == 7) // Not regular : Octahedron with only 5 points at 0 azymuth
        {
            azimuths[0] = 0.;
            elevations[0] = HOA_PI2;
            azimuths[1] = 0.;
            azimuths[2] = HOA_2PI / 5.;
            azimuths[3] = 2. * HOA_2PI / 5.;
            azimuths[4] = 3. * HOA_2PI / 5.;
            azimuths[5] = 4. * HOA_2PI / 5.;
            elevations[1] = elevations[2] = elevations[3] = elevations[4] = elevations[5] = 0;
            azimuths[6] = 0.;
            elevations[6] = -HOA_PI2;
        }
        else if(numberOfPoints == 8) // Hexahedron or cube
        {
            azimuths[0] = azimuths[4] = HOA_PI4;
            azimuths[1] = azimuths[5] = HOA_PI4 + HOA_PI2;
            azimuths[2] = azimuths[6] = HOA_PI4 + HOA_PI;
            azimuths[3] = azimuths[7] = HOA_PI4 + HOA_PI + HOA_PI2;
            elevations[0] = elevations[1] = elevations[2] = elevations[3] = HOA_PI4;
            elevations[4] = elevations[5] = elevations[6] = elevations[7] = -HOA_PI4;
        }
        else if(numberOfPoints == 9) // Not regular : Hexahedron or cube with 1 at PI/2 elevation
        {
            azimuths[0] = azimuths[4] = HOA_PI4;
            azimuths[1] = azimuths[5] = HOA_PI4 + HOA_PI2;
            azimuths[2] = azimuths[6] = HOA_PI4 + HOA_PI;
            azimuths[3] = azimuths[7] = HOA_PI4 + HOA_PI + HOA_PI2;
            elevations[0] = elevations[1] = elevations[2] = elevations[3] = HOA_PI4;
            elevations[4] = elevations[5] = elevations[6] = elevations[7] = -HOA_PI4;
            elevations[8] = HOA_PI2;
            azimuths[8] = 0;
        }
        else if(numberOfPoints == 10) // Not regular : Hexahedron or cube with 1 at PI/2 elevation and 1 at -Pi/2 elevation
        {
            azimuths[0] = azimuths[4] = HOA_PI4;
            azimuths[1] = azimuths[5] = HOA_PI4 + HOA_PI2;
            azimuths[2] = azimuths[6] = HOA_PI4 + HOA_PI;
            azimuths[3] = azimuths[7] = HOA_PI4 + HOA_PI + HOA_PI2;
            elevations[0] = elevations[1] = elevations[2] = elevations[3] = HOA_PI4;
            elevations[4] = elevations[5] = elevations[6] = elevations[7] = -HOA_PI4;
            elevations[8] = HOA_PI2;
            elevations[9] = -HOA_PI2;
            azimuths[9] = azimuths[8] = 0;
        }
        else if(numberOfPoints == 11) // Not regular : Hexahedron or cube with 1 at PI/2 elevation and 1 at -Pi/2 elevation
        {
            azimuths[0] = azimuths[4] = HOA_PI4;
            azimuths[1] = azimuths[5] = HOA_PI4 + HOA_PI2;
            azimuths[2] = azimuths[6] = HOA_PI4 + HOA_PI;
            azimuths[3] = azimuths[7] = HOA_PI4 + HOA_PI + HOA_PI2;
            elevations[0] = elevations[1] = elevations[2] = elevations[3] = HOA_PI4;
            elevations[4] = elevations[5] = elevations[6] = elevations[7] = -HOA_PI4;
            elevations[8] = HOA_PI2;
            elevations[9] = elevations[9] = -HOA_PI2;
            azimuths[9] = azimuths[8] = 0;
        }
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

    static const float  MIT_HRTF_44100[] = {0};
    static const float  MIT_HRTF_48000[] = {0};
    static const float  MIT_HRTF_88200[] = {0};
    static const float  MIT_HRTF_96000[] = {0};

    inline const float* get_mit_hrtf(long samplerate, long elevation, long azimuth)
    {
        int elevation_index;
        int number_of_samples;
        int elevation_offset;

        if(samplerate == 44100)
            number_of_samples = 512;
        else if(samplerate == 48000)
            number_of_samples = 557;
        else if(samplerate == 48000)
            number_of_samples = 1024;
        else if(samplerate == 48000)
            number_of_samples = 1114;
        else
            return NULL;

        if(elevation == -40)
            elevation_offset = 0;
        else if(elevation == -30)
            elevation_offset = 56 * number_of_samples;
        else if(elevation == -20)
            elevation_offset = (56 + 60) * number_of_samples;
        else if(elevation == -10)
             elevation_offset = (56 + 60 + 72) * number_of_samples;
        else if(elevation == 0)
            elevation_offset = (56 + 60 + 72 + 72) * number_of_samples;
        else if(elevation == 10)
            elevation_offset = (56 + 60 + 72 + 72 + 72) * number_of_samples;
        else if(elevation == 20)
            elevation_offset = (56 + 60 + 72 + 72 + 72 + 72) * number_of_samples;
        else if(elevation == 30)
            elevation_offset = (56 + 60 + 72 + 72 + 72 + 72 + 72) * number_of_samples;
        else if(elevation == 40)
            elevation_offset = (56 + 60 + 72 + 72 + 72 + 72 + 72 + 60) * number_of_samples;
        else if(elevation == 50)
            elevation_offset = (56 + 60 + 72 + 72 + 72 + 72 + 72 + 60 + 56) * number_of_samples;
        else if(elevation == 60)
            elevation_offset = (56 + 60 + 72 + 72 + 72 + 72 + 72 + 60 + 56 + 45) * number_of_samples;
        else if(elevation == 70)
            elevation_offset = (56 + 60 + 72 + 72 + 72 + 72 + 72 + 60 + 56 + 45 + 36) * number_of_samples;
        else if(elevation == 80)
            elevation_offset = (56 + 60 + 72 + 72 + 72 + 72 + 72 + 60 + 56 + 45 + 36 + 24) * number_of_samples;
        else if(elevation == 90)
            elevation_offset = (56 + 60 + 72 + 72 + 72 + 72 + 72 + 60 + 56 + 45 + 36 + 24 + 12) * number_of_samples;
        else
            return NULL;

        elevation_index = (elevation + 40) / 130;

        if(samplerate == 44100)
            return MIT_HRTF_44100+elevation_offset;
        else if(samplerate == 48000)
            return MIT_HRTF_44100+elevation_offset;
        else if(samplerate == 88200)
            return MIT_HRTF_88200+elevation_offset;
        else if(samplerate == 96000)
            return MIT_HRTF_96000+elevation_offset;
        return NULL;
    }
}




#endif
