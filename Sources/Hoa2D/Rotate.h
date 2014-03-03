/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_2D_ROTATE
#define DEF_HOA_2D_ROTATE

#include "Ambisonic.h"

namespace Hoa2D
{
    //! The ambisonic rotation.
    /** The Rotate should be used to rotate an entire soundfield.
     */
    class Rotate : public Ambisonic
    {
    private:
		
		double  m_yaw;
        double  m_cosx;
        double  m_sinx;
        
    public:
        
        //! The Rotate constructor.
        /**	The Rotate constructor allocates and initialize the member values to computes spherical harmonics rotation depending on a decomposition order. The order must be at least 1.
         
            @param     order	The order.
         */
        Rotate(unsigned int order);
        
        //! The Rotate destructor.
        /**	The Rotate destructor free the memory.
         */
        ~Rotate();
		
		//! This method sets the yaw value (rotation on the z-axis).
        /** The yaw is equivalent to a rotation on the z-axis (also named rotation).
		 
		 @param     value The yaw value between 0 and 2π.
         */
        void setYaw(const double value);
		
		//! Get the yaw value (rotation on the z-axis).
        /** The yaw is equivalent to a rotation on the z-axis (also named rotation).
		 
		 @return     value The yaw value between 0 and 2π.
         */
        inline double getYaw() const {return m_yaw;};
        
        //! This method performs the rotation with single precision.
        /**	You should use this method for not-in-place processing and performs the rotation sample by sample.
			(warning : doesn't work with in-place vectors);
			The inputs array and outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         
            @param     inputs   The input array.
            @param     outputs  The output array.
         */
        void process(const float* inputs, float* outputs);
        
        //! This method performs the rotation with double precision.
        /**	You should use this method for not-in-place processing and performs the rotation sample by sample. 
			(warning : doesn't work with in-place vectors);
			The inputs array and outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         
            @param     inputs   The input array.
            @param     outputs  The output array.
         */
        void process(const double* inputs, double* outputs);
    };
	
} // end of namespace Hoa3D

#endif



