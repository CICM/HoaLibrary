/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#ifndef DEF_HOA_3D_OPTIM
#define DEF_HOA_3D_OPTIM

#include "Ambisonic.h"

namespace Hoa2D
{
    //! The ambisonic optimization.
    /** The optimization should be used to widen the sound propagation.
     */
    class Optim : public Ambisonic
    {
    public:
        enum Mode
        {
            Basic   = 0,	/**< Basic Optimization     */
            MaxRe   = 1,	/**< Max Re Optimization    */
            inPhase = 2     /**< In Phase Optimization  */
        };
        
    private:
        
        Mode            m_mode;
        double*         m_harmonics;
        
    public:
        
        //! The optimization constructor.
        /**	The optimization constructor allocates and initialize the member values to computes spherical harmonics weighted coefficients depending of a decomposition order. The order must be at least 1.
         
         @param     order	The order.
         */
        Optim(unsigned int order, Mode mode);
        
        //! The optimization destructor.
        /**	The optimization destructor free the memory.
         */
        ~Optim();
        
        long getMode();
        
        //! This method set the widening value.
        /**	The widening value is clipped between 0 and 1. At 1, the sound field has no changes. At 0, all the sound field is omni directionnal.
         
         @param     value The widening value.
         */
        void setMode(Mode mode);
        
        //! This method performs the widening with single precision.
        /**	You should use this method for in-place or not-in-place processing and performs the widening sample by sample. The inputs array and outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         
         @param     inputs   The input array.
         @param     outputs  The output array.
         */
        void process(const float* inputs, float* outputs);
        
        //! This method performs the widening with double precision.
        /**	You should use this method for in-place or not-in-place processing and performs the widening sample by sample. The inputs array and outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         
         @param     inputs   The input array.
         @param     outputs  The output array.
         */
        void process(const double* inputs, double* outputs);
    };
}

#endif



