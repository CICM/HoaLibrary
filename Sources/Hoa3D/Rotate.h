/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_3D_ROTATE
#define DEF_HOA_3D_ROTATE

#include "Ambisonic.h"

namespace Hoa3D
{
    //! The ambisonic Rotate.
    /** The Rotate should be used to rotate an entire soundfield.
     */
    class Rotate : public Ambisonic
    {
    private:
        
		double			m_roll, m_pitch, m_yaw;
        long            m_rotation;
        double**        m_rotation_matrix;
        
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
		
		//! This method sets the three rotation values at the same time (xyz axis).
        /** This method sets the three rotation values at the same time (xyz axis).
		 
		 @param     roll	The roll value is equivalent to a rotation on the x-axis (also named tilt), between 0 and 2π.
		 @param     pitch	The pitch value is equivalent to a rotation on the y-axis (also named tumble), between 0 and 2π.
		 @param     yaw		The yaw value is equivalent to a rotation on the z-axis (also named rotation), between 0 and 2π.
		 @see setRoll, setPitch, setYaw
         */
        void setRotations(const double roll, const double pitch, const double yaw);
        
        //! This method sets the roll value (rotation on the x-axis).
        /** The roll is equivalent to a rotation on the x-axis (also named tilt).
		 
            @param     value The roll value between 0 and 2π.
         */
        void setRoll(const double value);
		
		//! This method sets the pitch value (rotation on the y-axis).
        /** The pitch is equivalent to a rotation on the y-axis (also named tumble).
		 
		 @param     value The pitch value between 0 and 2π.
         */
        void setPitch(const double value);
		
		//! This method sets the yaw value (rotation on the z-axis).
        /** The yaw is equivalent to a rotation on the z-axis (also named rotation).
		 
		 @param     value The yaw value between 0 and 2π.
         */
        void setYaw(const double value);
		
		//! Get the roll value (rotation on the x-axis).
        /** The roll is equivalent to a rotation on the x-axis (also named tilt).
		 
		 @return     value The roll value between 0 and 2π.
         */
        inline double getRoll() const {return m_roll;};
		
		//! Get the pitch value (rotation on the y-axis).
        /** The pitch is equivalent to a rotation on the y-axis (also named tumble).
		 
		 @return     value The pitch value between 0 and 2π.
         */
        inline double getPitch() const {return m_pitch;};
		
		//! Get the yaw value (rotation on the z-axis).
        /** The yaw is equivalent to a rotation on the z-axis (also named rotation).
		 
		 @return     value The yaw value between 0 and 2π.
         */
        inline double getYaw() const {return m_yaw;};
        
        //! This method performs the rotation with single precision.
        /**	You may use this method for in-place or not-in-place processing and performs the rotation sample by sample. 
			The inputs array and outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         
            @param     inputs   The input array.
            @param     outputs  The output array.
         */
        void process(const float* inputs, float* outputs);
        
        //! This method performs the rotation with double precision.
        /**	You may use this method for in-place or not-in-place processing and performs the rotation sample by sample. 
			The inputs array and outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         
            @param     inputs   The input array.
            @param     outputs  The output array.
         */
        void process(const double* inputs, double* outputs);
    };
	
} // end of namespace Hoa3D

#endif


