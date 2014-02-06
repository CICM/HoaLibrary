/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_3D_AMBISONIC
#define DEF_HOA_3D_AMBISONIC

#include "../CicmLibrary/CicmLibrary.h"
#include "Legendre.h"

//! The 3D ambisonic classes.
/**
 All the 3D ambisonic classes will be part of this namespace
 */
namespace Hoa3D
{
    //! The ambisonic class.
    /**
     Most of the ambisonic classes inherit from this classe. It computes the number of harmonics, their indices and their orders depending of the decomposition order. etc...
     */
    class Ambisonic
    {
    protected:
        long	m_order;
        long	m_number_of_harmonics;
        long	m_number_of_inputs;
        long	m_number_of_outputs;
        
        long*    m_harmonics_arguments;
        long*    m_harmonics_bands;
        
    public:
        
        //! The ambisonic constructor.
        /** The ambisonic constructor allocates and initializes the generale member values depending of a decomposition order.
         @param     order	The order, must be at least 1.
         */
        Ambisonic(unsigned int order);
        
        /** The ambisonic destructor.
         */
        ~Ambisonic();
        
        /** Retrieve the decomposition order.
         */
        long getOrder();
        
        /** Retrieve the number of harmonics.
         */
        long getNumberOfHarmonics();
        
        /** Retrieve the number of inputs.
         */
        long getNumberOfInputs();
        
        /** Retrieve the number of outputs.
         */
        long getNumberOfOutputs();
        
        //! Retrieve the argument of an harmonic.
        /** The argument of an harmonic is in the range -band to band. The harmonics are sorted by their bands, from 0 to the decomposition order and, in each band, they are sorted by their arguments in the range -band to band. For the first bands, the harmonics arrangement is h[0, 0] h[1, -1] h[1, 0] h[1, 1] h[2, -2] h[2, -1] h[2, 0] h[2, 1] h[2, 2] etc. with h[band, argument].
         
            @param     index	The global index of an harmonic.
            @return    The method returns the argument of an harmonic or 0 if the harmonic does not exist.
            @see       getHarmonicBand()
         */
        long getHarmonicArgument(unsigned int index);
        
        //! Retrieve the band of an harmonic.
        /** The bands of the harmonics are in the range 0 to the decomposition order. Each band contains 2 * band + 1 harmonics in the range -band to band. For the first bands, the harmonics arrangement is h[0, 0] h[1, -1] h[1, 0] h[1, 1] h[2, -2] h[2, -1] h[2, 0] h[2, 1] h[2, 2] etc. with h[band, argument].
         
            @param     index	The global index of an harmonic.
            @return    The method returns the band of an harmonic or 0 if the harmonic does not exist.
            @see       getHarmonicArgument()
         */
        long getHarmonicBand(unsigned int index);
        
        //! Retrieve a good name for an harmonic.
        /** Retrieve a good name for an harmonic.
         
         @param     index	The global index of an harmonic.
         */
        std::string getHarmonicsName(unsigned int index);
    };
}

#endif


