/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_2D_AMBISONIC
#define DEF_HOA_2D_AMBISONIC

#include "../Hoa/Hoa.h"

namespace Hoa2D
{
    //! The ambisonic class.
    /**
     Most of the ambisonic classes inherit from this classe. It computes the number of harmonics, their arguments and their orders depending of the decomposition order. etc...
     */
    class Ambisonic
    {
    protected:
        unsigned int	m_order;
        unsigned int	m_number_of_harmonics;
        long*           m_harmonics_arguments;
    
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
        unsigned int getOrder() const
        {
            return m_order;
        }
        
        /** Retrieve the number of harmonics.
         */
        unsigned int getNumberOfHarmonics() const
        {
            return m_number_of_harmonics;
        }
        
        //! Retrieve the argument of an harmonic.
        /** The argument of an harmonic is in the range -order to order. The harmonics are sorted by their bands, from 0 to the decomposition order and, in each band, there are the 2 harmonics with the arguments -band and band. For the first bands, the harmonics arrangement is h[0] h[-1] h[1] h[-2] h[2] h[-3] h[3]etc. with h[argument].
         
            @param     index	The index of an harmonic.
            @return    The method returns the argument of the harmonic if the harmonic exists, otherwise the function generates an error.
            @see       getHarmonicBand()
            @see       getHarmonicsName()
         */
        long getHarmonicArgument(unsigned int index) const
        {
            assert(index < m_number_of_harmonics);
            return m_harmonics_arguments[index];
        }
        
        //! Retrieve the band of an harmonic.
        /** The bands of the harmonics are in the range 0 to the decomposition order. Each band contains 2 harmonics with the arguments -band and band. For the first bands, the harmonics arrangement is h[0] h[-1] h[1] h[-2] h[2] h[-3] h[3], etc. with h[argument].
         
            @param     index	The index of an harmonic.
            @return    The method returns the band of the harmonic if the harmonic exists, otherwise the function generates an error.
            @see       getHarmonicArgument()
            @see       getHarmonicsName()
         */
        long getHarmonicBand(unsigned int index) const
        {
            assert(index < m_number_of_harmonics);
            return abs(m_harmonics_arguments[index]);
        }
        
        //! Retrieve a name for an harmonic.
        /** Retrieve a name for an harmonic in a std::string format that will be "harmonic argument".
         
            @param     index	The index of an harmonic.
            @return    The method returns a name for the harmonic that contains its argument if the harmonic exists, otherwise the function generates an error.
         
            @see       getHarmonicBand()
            @see       getHarmonicArgument()
         */
        std::string getHarmonicsName(unsigned int index) const
        {
            assert(index < m_number_of_harmonics);
            return "Harmonic " + int_to_string(getHarmonicArgument(index));
        }
    };
}


#endif


