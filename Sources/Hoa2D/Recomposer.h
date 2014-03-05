/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_2D_RECOMPOSER
#define DEF_HOA_2D_RECOMPOSER

#include "Ambisonic.h"
#include "Planewaves.h"
#include "Encoder.h"
#include "Wider.h"

namespace Hoa2D
{
    //! The ambisonic recomposer.
    /** The recomposer should be in the planewaves domain to come back the the circular harmonics domain. The recomposition is similar to the several encoding exept that we consider planewaves (or virtual microphones) instead of sources. The number of channels (or planewaves) must be a least the number of harmonics, the first angle is 0 radian and the angular distances between the channels are equals.
     */
    class Recomposer : public Ambisonic, public Planewaves
    {
        
    private:
		double*                 m_harmonics_double;
        float*                  m_harmonics_float;
        std::vector<Encoder*>   m_encoders;
        std::vector<Wider*>     m_widers;
        
    public:
        
        //! The recomposer constructor.
        /**	The recomposer constructor allocates and initialize the member values to recompose a set of planewaves in the circular harmonics domain. The order must be at least 1 and the number of channels must be a least the number of harmonics.
         
            @param     order				The order.
            @param     numberOfChannels     The number of channels.
         */
		Recomposer(unsigned int order, unsigned int numberOfChannels);
		
        //! The recomposer destructor.
        /**	The recomposer destructor free the memory.
         */
		~Recomposer();
        
        //! This method set the angle of azimuth of a channel.
        /**	The angle of azimuth in radian and you should prefer to use it between 0 and 2 Pi to avoid recursive wrapping of the value. The direction of rotation is counterclockwise. The 0 radian is Pi/2 phase shifted relative to a mathematical representation of a circle, then the 0 radian is at the "front" of the soundfield. The index must be between 0 and the number of channel - 1.
         
            @param     index	The index of the source.
            @param     azimuth	The azimuth.
            @see       setWideningValue()
         */
        void setAzimuth(unsigned int index, const double azimuth);
        
        //! This method set the widening value of a channel.
        /**	The widening value is clipped between 0 and 1. At 1, the sound field has no changes. At 0, all the sound field is omnidirectionnal, only the harmonic [0 0] remains. From 0 to 1, the circular hamronics appears in logarithmic way to linearly increase the sound field precision.
         
            @param     index	The index of the source.
            @param     value    The widening value.
            @see       setAzimuth()
         */
        void setWideningValue(unsigned int index, const double value);
        
        //! This method retrieve the azimuth of a channel.
        /** Retrieve the azimuth of a source.
         
         @param     index	The index of the channel.
         @return    The azimuth of the channel if the channel exists, otherwise the function generates an error.
         */
        double getAzimuth(unsigned int index) const
        {
            assert(index < m_number_of_channels);
            return m_encoders[index]->getAzimuth();
        }
		
        //! This method retrieve the widening value of a channel.
        /** Retrieve the widening value of a channel.
         
         @param     index	The index of the channel.
         @return    The widening value of the channel if the channel exists, otherwise the function generates an error.
         */
        double getWideningValue(unsigned int index) const
        {
            assert(index < m_number_of_channels);
            return m_widers[index]->getWideningValue();
        }
        
		//! This method performs the recomposition with single precision.
        /**	You should use this method for in-place or not-in-place processing and performs the projection sample by sample. The outputs array contains the circular harmonics samples and the minimum size must be the number of harmonics and the  inputs array contains the channels (or planewaves) samples and the minimum size must be a least the number of channels.
         
            @param     inputs   The inputs array.
            @param     outputs  The outputs array.
         */
		void process(const float* inputs, float* outputs);
		
		//! This method performs the recomposition with double precision.
        /**	You should use this method for in-place or not-in-place processing and performs the projection sample by sample. The outputs array contains the circular harmonics samples and the minimum size must be the number of harmonics and the inputs array contains the channels (or planewaves) samples and the minimum size must be a least the number of channels.
         
            @param     inputs   The inputs array.
            @param     outputs  The outputs array.
         */
		void process(const double* inputs, double* outputs);
    };
}


#endif


