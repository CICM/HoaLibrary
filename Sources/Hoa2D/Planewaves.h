/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_2D_PLANEWAVES
#define DEF_HOA_2D_PLANEWAVES

#include "Tools.h"

namespace Hoa2D
{
    //! The planewaves class.
    /**
     The planewaves classes, that process on a set of channels, inherit from this class. It store basic informations like the number, the coordinates and the names of channels.
	
     */
    class Planewaves
    {
	protected:
        
		unsigned int    m_number_of_channels;
        double*         m_channels_azimuth;
		
    public:
        
		//! The planewaves constructor.
        /** The lanewaves constructor allocates and initializes the general member values depending on a number of channels. The number of loudspkeakers must a least 1.
         
            @param     numberOfChannels	The number of channels.
         */
		Planewaves(unsigned int numberOfChannels);
        
        //! The planewaves destructor.
        /** The Planewaves destructor free the memorie allocated.
         */
        ~Planewaves();
		
        //! Set the position of a loudspeaker.
        /** Set the position of a loudspeaker with polar coordinates. The azimtuh is in radian between 0 and 2 Pi, O is the front of the soundfield and Pi is the back of the sound field. The elevation is in radian between -1/2 Pi and 1/2 Pi, -1/2 Pi the the bottom of the sound field, 0 is the center of the sound field and 1/2 Pi is the top of the sound field. The maximum index must be the number of channels - 1.
         
            @param     index		The index of the loudspeaker.
            @param     azimuth		The azimuth.
            @param     elevation	The elevation.
         */
		void setChannelPosition(unsigned int index, double azimuth);
        
        //! Retrieve the number of channels.
		/** Retrieve the number of channels of the planewave class.
            
            @return The number of channels.
         */
		inline unsigned int getNumberOfChannels() const {return m_number_of_channels;}
        
        //! Retrieve the azimuth of a loudspeaker.
        /** Retrieve the azimuth of a loudspeaker. The azimuth of the loudspeaker is in radian, 0 radian is at the front of the soundfield and Pi is at the back of the sound field. The maximum index must be the number of channels - 1.
         
            @param      index   The index of the loudspeaker.
            @return     The azimuth of the loudspeaker.
            @see getChannelElevation
         */
		inline double getChannelAzimuth(unsigned int index) const
        {
            assert(index < m_number_of_channels);
            return m_channels_azimuth[index];
        }

		
        //! Retrieve the abscissa of a loudspeaker.
		/** Retrieve the abscissa of a loudspeaker. The abscissa is between -1 and 1, -1 is the left of the soundfield, 0 is the center of the soundfield and 1 is the right of the soundfield. The maximum index must be the number of channels - 1.
         
            @param     index    The index of the loudspeaker.
            @return    The abscissa of the loudspeaker.
            @see getChannelOrdinate
            @see getChannelHeight
         */
		inline double getChannelAbscissa(unsigned int index) const
        {
            assert(index < m_number_of_channels);
            return abscissa(1., m_channels_azimuth[index]);
        }
		
        //! Retrieve the ordinate of a loudspeaker.
		/** Retrieve the ordinate of a loudspeaker. The ordinate is between -1 and 1, -1 is the back of the soundfield, 0 is the center of the soundfield and 1 is the front of the soundfield. The maximum index must be the number of channels - 1.
         
            @param     index	The index of the loudspeaker.
            @return    The ordinate of the loudspeaker.
            @see getChannelAbscissa
            @see getChannelHeight
         */
		inline double getChannelOrdinate(unsigned int index) const
        {
            assert(index < m_number_of_channels);
            return ordinate(1., m_channels_azimuth[index]);
        }
        
        //! Retrieve the number of loudspeaker.
        /** Retrieve a name for an loudspeaker in a std::string format that will be "Channel index azimuth elevation".
         
         @param     index	The global index of a loudspeaker.
         @return    The name of the loudspeaker
         */
		inline std::string getChannelName(unsigned int index)
        {
            assert(index < m_number_of_channels);
            return "Channel " + int_to_string(index + 1) + " : " + int_to_string((int)getChannelAzimuth(index) / CICM_2PI * 360.) + "°";
        };
    };
	
} // end of namespace Hoa3D

#endif