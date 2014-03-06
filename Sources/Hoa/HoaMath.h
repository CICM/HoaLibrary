/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __DEF_HOA_MATHS__
#define __DEF_HOA_MATHS__

//! The high order ambisonic namespace.
/**
 This namespace have all the standard methods and functions necessary for ambisonic processing.
 */
namespace Hoa
{
	//! The maximum function
    /** This function returns the maximum value between two values
	 
	 @param     v1   The first value.
	 @param     v2   The low boundary.
	 @return    The maximum value.
     
	 @see    min
     */
	inline double max(double v1, double v2)
	{
		if (v1 >= v2)
			return v1;
		else
			return v2;
	}
	
	//! The minimum function
    /** This function returns the minimum value between two values
	 
	 @param     v1   The first value.
	 @param     v2   The low boundary.
	 @return    The maximum value.
     
	 @see    min
     */
	inline double min(double v1, double v2)
	{
		if (v1 <= v2)
			return v1;
		else
			return v2;
	}
	
	//! The clipping function
    /** The function clips a number between boundaries. \n
	 If \f$x < min\f$, \f$f(x) = min\f$ else if \f$x > max\f$, \f$f(x) = max\f$ else \f$f(x) = x\f$.
     
	 @param     value   The value to clip.
	 @param     low     The low boundary.
	 @param     high    The high boundary.
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
	 @param     low     The low boundary.
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
	 @param     high    The high boundary.
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
			return pow(-1.0f, (double)m) * pow(1. - x * x, 0.5 * m) * double_factorial(2. * m - 1);
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
    
    //! The wrapping function
    /** The function wraps a number between boundarys.
     
	 @param     value   The value to wrap.
	 @param     low     The low boundary.
	 @param     high    The high boundary.
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
            new_value += HOA_2PI;
        }
        
        while(new_value > HOA_2PI)
        {
            new_value -= HOA_2PI;
        }
        return new_value;
    }
    
	inline double ordinate(const double radius, const double angle)
	{
		return radius * sin(angle + HOA_PI2);
	}
    
    inline double abscissa(const double radius, const double angle)
	{
		return radius * cos(angle + HOA_PI2);
	}
    
    inline double radius(double x, double y)
	{
		return sqrt(x*x + y*y);
	}
    
	inline double azimuth(double x, double y)
	{
		return atan2(y, x) - HOA_PI2;
	}
    
    inline double distance(double x1, double y1, double x2, double y2)
	{
		return sqrt((x1-x2) * (x1-x2) + (y1-y2) * (y1-y2));
	}
	
	inline double distance_radian(double anAngle1, double anAngle2)
    {
        anAngle1 = wrap_twopi(anAngle1);
        anAngle2 = wrap_twopi(anAngle2);
        if(anAngle1 > anAngle2)
            return (anAngle1 - anAngle2);
        else
            return (anAngle2 - anAngle1);
    }
}

#endif