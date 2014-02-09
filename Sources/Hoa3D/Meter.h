/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_3D_Meter
#define DEF_HOA_3D_Meter

#include "Planewaves.h"

namespace Hoa3D
{
    //! The ambisonic Meter.
    /** The Meter should be used to widen the sound propagation.
     */
    class Meter : public Planewaves
    {
    private:
		
		unsigned int m_numberOfChannels;
        
    public:
        
        //! The Meter constructor.
        /**	The Meter constructor allocates and initialize the member values to computes spherical harmonics weighted coefficients depending of a decomposition order. The order must be at least 1.
         
            @param     order	The order.
         */
        Meter(unsigned int numberOfChannels);
        
        //! The Meter destructor.
        /**	The Meter destructor free the memory.
         */
        ~Meter();
        
        //! This method performs the widening with single precision.
        /**	You should use this method for in-place or not-in-place processing and performs the widening sample by sample. The inputs array and outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         
            @param     inputs   The input array.
         */
        void process(const float* inputs);
        
        //! This method performs the widening with double precision.
        /**	You should use this method for in-place or not-in-place processing and performs the widening sample by sample. The inputs array and outputs array contains the spherical harmonics samples and the minimum size must be the number of harmonics.
         
            @param     inputs   The input array.
         */
        void process(const double* inputs);
    };
}

#endif



