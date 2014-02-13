/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_3D_AMBISONIC
#define DEF_HOA_3D_AMBISONIC

#include "Tools.h"

//! The 3D ambisonic classes.
/**
 All the 3D ambisonic and planewaves classes will be part of this namespace
 */
namespace Hoa3D
{
    //! The ambisonic class.
    /** The ambisonics classes inherit from this classe. It computes the number of harmonics depending of the decomposition order and sorts the arguments and the bands of the harmonics in arrays.
     */
    class Ambisonic
    {
    protected:
        unsigned int    m_order;
        unsigned int	m_number_of_harmonics;
        unsigned int*   m_harmonics_bands;
        int*            m_harmonics_arguments;
        
    public:
        
        //! The ambisonic constructor.
        /** The ambisonic constructor allocates and initializes the generale member values depending of a decomposition order. The order must be at least 1.
         
            @param     order	The order.
         */
        Ambisonic(unsigned int order);
        
        //! The ambisonic destructor.
        /**	The ambisonic destructor free the memory.
         */
        ~Ambisonic();
        
        //! Retrieve the decomposition order.
        /** Retrieve the decomposition order of an ambisonic class.
         */
        inline unsigned int getOrder() const {return m_order;};
        
        //! Retrieve the number of harmonics.
        /** Retrieve the number of harmonics of an ambisonic class.
         */
        inline unsigned int getNumberOfHarmonics() const {return m_number_of_harmonics;};
        
        //! Retrieve the argument of an harmonic.
        /** The argument of an harmonic is in the range -band to band. The harmonics are sorted by their bands, from 0 to the decomposition order. In each band contains 2 * band + 1 harmonics, sorted by their arguments in the range -band to band. The harmonic input and output arrays in process method of ambisonic classes must have this configuration. For the first bands, the harmonics arrangement is h[0, 0] h[1, -1] h[1, 0] h[1, 1] h[2, -2] h[2, -1] h[2, 0] h[2, 1] h[2, 2] etc. with h[band, argument].
         
            @param     index	The global index of an harmonic.
            @return    The method returns the argument of an harmonic or 0 if the harmonic does not exist.
            @see       getHarmonicBand()
            @see       getHarmonicsName()
         */
        inline int getHarmonicArgument(const unsigned int index) const
        {
            assert(index < m_number_of_harmonics);
            return m_harmonics_arguments[index];
        };
        
        //! Retrieve the band of an harmonic.
        /** The bands of the harmonics are in the range 0 to the decomposition order. Each band contains 2 * band + 1 harmonics in the range -band to band. The harmonic input and output arrays in process method of ambisonic classes must have this configuration. For the first bands, the harmonics arrangement is h[0, 0] h[1, -1] h[1, 0] h[1, 1] h[2, -2] h[2, -1] h[2, 0] h[2, 1] h[2, 2] etc. with h[band, argument].
         
            @param     index	The global index of an harmonic.
            @return    The method returns the band of an harmonic or 0 if the harmonic does not exist.
            @see       getHarmonicArgument()
            @see       getHarmonicsName()
         */
        inline unsigned int getHarmonicBand(const unsigned int index) const
        {
            assert(index < m_number_of_harmonics);
            return m_harmonics_bands[index];
        };
        
        //! Retrieve a name for an harmonic.
        /** Retrieve a name for an harmonic in a std::string format that will be "harmonic band argument".
         
            @param     index	The global index of an harmonic.
            @return    The method returns a name of an harmonic that contains its band and the argument.
            @see       getHarmonicBand()
            @see       getHarmonicArgument()
         */
        inline std::string getHarmonicsName(const unsigned int index) const
        {
            assert(index < m_number_of_harmonics);
            return "Harmonic " + intToString(getHarmonicBand(index)) + " " + intToString(getHarmonicArgument(index));
        };
    };
}

#endif


