/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __DEF_HOA_3D_PLANEWAVES__
#define __DEF_HOA_3D_PLANEWAVES__

#include "../Hoa.h"

namespace Hoa3D
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
		double*         m_channels_elevation;
		
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
		
        //! Set the position of a channel.
        /** Set the position of a channel with polar coordinates. The azimtuh is in radian between 0 and 2 Pi, O is the front of the soundfield and Pi is the back of the sound field. The elevation is in radian between -1/2 Pi and 1/2 Pi, -1/2 Pi the the bottom of the sound field, 0 is the center of the sound field and 1/2 Pi is the top of the sound field. The maximum index must be the number of channels - 1.
         
            @param     index		The index of the channel.
            @param     azimuth		The azimuth.
            @param     elevation	The elevation.
         */
		void setChannelPosition(unsigned int index, double azimuth, double elevation);

		//! Set the position of the channels.
        /** Set the position of the channels with polar coordinates. The azimtuh is in radian between 0 and 2 Pi, O is the front of the soundfield and Pi is the back of the sound field. The elevation is in radian between -1/2 Pi and 1/2 Pi, -1/2 Pi the the bottom of the sound field, 0 is the center of the sound field and 1/2 Pi is the top of the sound field. The maximum index must be the number of channels - 1.
         
            @param     azimuths		The azimuths.
            @param     elevations	The elevations.
         */
		void setChannelsPosition(double* azimuths, double* elevations);
        
        //! Retrieve the number of channels.
		/** Retrieve the number of channels of the planewave class.
            
            @return The number of channels.
         */
		inline unsigned int getNumberOfChannels() const {return m_number_of_channels;}
        
        //! Retrieve the azimuth of a channel.
        /** Retrieve the azimuth of a channel. The azimuth of the channel is in radian, 0 radian is at the front of the soundfield and Pi is at the back of the sound field. The maximum index must be the number of channels - 1.
         
            @param      index   The index of the channel.
            @return     The azimuth of the channel.
            @see getChannelElevation
         */
		inline double getChannelAzimuth(unsigned int index) const
        {
            assert(index < m_number_of_channels);
            return m_channels_azimuth[index];
        }
		
        //! Retrieve the elevation of a channel.
		/** Retrieve the elevation of a channel. The elevation is in radian between -1/2 Pi and 1/2 Pi, -1/2 Pi the the bottom of the sound field, 0 is the center of the sound field and 1/2 Pi is the top of the sound field. The maximum index must be the number of channels - 1.
         
            @param      index   The index of the channel.
            @return     The elevation of the channel.
            @see getChannelAzimuth
         */
		inline double getChannelElevation(unsigned int index) const
        {
            assert(index < m_number_of_channels);
            return m_channels_elevation[index];
        }
		
        //! Retrieve the abscissa of a channel.
		/** Retrieve the abscissa of a channel. The abscissa is between -1 and 1, -1 is the left of the soundfield, 0 is the center of the soundfield and 1 is the right of the soundfield. The maximum index must be the number of channels - 1.
         
            @param     index    The index of the channel.
            @return    The abscissa of the channel.
            @see getChannelOrdinate
            @see getChannelHeight
         */
		inline double getChannelAbscissa(unsigned int index) const
        {
            assert(index < m_number_of_channels);
            return abscissa(1., m_channels_azimuth[index], m_channels_elevation[index]);
        }
		
        //! Retrieve the ordinate of a channel.
		/** Retrieve the ordinate of a channel. The ordinate is between -1 and 1, -1 is the back of the soundfield, 0 is the center of the soundfield and 1 is the front of the soundfield. The maximum index must be the number of channels - 1.
         
            @param     index	The index of the channel.
            @return    The ordinate of the channel.
            @see getChannelAbscissa
            @see getChannelHeight
         */
		inline double getChannelOrdinate(unsigned int index) const
        {
            assert(index < m_number_of_channels);
            return ordinate(1., m_channels_azimuth[index], m_channels_elevation[index]);
        }
        
        //! Retrieve the height of a channel.
        /** Retrieve the height of a channel. The height is between -1 and 1, -1 is the bottom of the soundfield, 0 is the center of the soundfield and 1 is the top of the soundfield. The maximum index must be the number of channels - 1.
         
            @param      index	The index of the channel.
            @return     The height of the channel.
            @see getChannelAbscissa
            @see getChannelOrdinate
         */
		inline double getChannelHeight(unsigned int index) const
        {
            assert(index < m_number_of_channels);
            return height(1., m_channels_azimuth[index], m_channels_elevation[index]);
        }
        
        //! Retrieve the number of channel.
        /** Retrieve a name for an channel in a std::string format that will be "Channel index azimuth elevation".
         
         @param     index	The global index of a channel.
         @return    The name of the channel
         */
		inline std::string getChannelName(unsigned int index)
        {
            assert(index < m_number_of_channels);
            return "Channel " + int_to_string(index + 1) + " " + int_to_string((int)getChannelAzimuth(index)) + " " + int_to_string((int)getChannelElevation(index));
        };
        
    };
    
    inline void sphere_discretize(unsigned int numberOfPoints, double* azimuths, double* elevations)
    {
        if(numberOfPoints == 4) // Tethrahedron
        {
            azimuths[0] = 0.;
            elevations[0] = HOA_PI2;
            azimuths[1] = 0.;
            azimuths[2] = HOA_2PI / 3.;
            azimuths[3] = 2. * HOA_2PI / 3.;
            elevations[1] = elevations[2] = elevations[3] = HOA_PI2 - HOA_2PI / 3.;
        }
        else if(numberOfPoints == 5) // Not regular : Octahedron with only 3 points at 0 azymuth
        {
            azimuths[0] = 0.;
            elevations[0] = HOA_PI2;
            azimuths[1] = 0.;
            azimuths[2] = HOA_2PI / 3.;
            azimuths[3] = 2. * HOA_2PI / 3.;
            elevations[1] = elevations[2] = elevations[3] = 0;
            azimuths[4] = 0.;
            elevations[4] = -HOA_PI2;
        }
        else if(numberOfPoints == 6) // Octahedron
        {
            azimuths[0] = 0.;
            elevations[0] = HOA_PI2;
            azimuths[1] = 0.;
            azimuths[2] = HOA_PI2;
            azimuths[3] = 2. * HOA_PI2;
            azimuths[4] = 3. * HOA_PI2;
            elevations[1] = elevations[2] = elevations[3] = elevations[4] = 0;
            azimuths[5] = 0.;
            elevations[5] = -HOA_PI2;
        }
        else if(numberOfPoints == 7) // Not regular : Octahedron with only 5 points at 0 azymuth
        {
            azimuths[0] = 0.;
            elevations[0] = HOA_PI2;
            azimuths[1] = 0.;
            azimuths[2] = HOA_2PI / 5.;
            azimuths[3] = 2. * HOA_2PI / 5.;
            azimuths[4] = 3. * HOA_2PI / 5.;
            azimuths[5] = 4. * HOA_2PI / 5.;
            elevations[1] = elevations[2] = elevations[3] = elevations[4] = elevations[5] = 0;
            azimuths[6] = 0.;
            elevations[6] = -HOA_PI2;
        }
        else if(numberOfPoints == 8) // Hexahedron or cube
        {
            azimuths[0] = azimuths[4] = HOA_PI4;
            azimuths[1] = azimuths[5] = HOA_PI4 + HOA_PI2;
            azimuths[2] = azimuths[6] = HOA_PI4 + HOA_PI;
            azimuths[3] = azimuths[7] = HOA_PI4 + HOA_PI + HOA_PI2;
            elevations[0] = elevations[1] = elevations[2] = elevations[3] = HOA_PI4;
            elevations[4] = elevations[5] = elevations[6] = elevations[7] = -HOA_PI4;
        }
        else if(numberOfPoints == 9) // Not regular : Hexahedron or cube with 1 at PI/2 elevation
        {
            azimuths[0] = azimuths[4] = HOA_PI4;
            azimuths[1] = azimuths[5] = HOA_PI4 + HOA_PI2;
            azimuths[2] = azimuths[6] = HOA_PI4 + HOA_PI;
            azimuths[3] = azimuths[7] = HOA_PI4 + HOA_PI + HOA_PI2;
            elevations[0] = elevations[1] = elevations[2] = elevations[3] = HOA_PI4;
            elevations[4] = elevations[5] = elevations[6] = elevations[7] = -HOA_PI4;
            elevations[8] = HOA_PI2;
            azimuths[8] = 0;
        }
        else if(numberOfPoints == 10) // Not regular : Hexahedron or cube with 1 at PI/2 elevation and 1 at -Pi/2 elevation
        {
            azimuths[0] = azimuths[4] = HOA_PI4;
            azimuths[1] = azimuths[5] = HOA_PI4 + HOA_PI2;
            azimuths[2] = azimuths[6] = HOA_PI4 + HOA_PI;
            azimuths[3] = azimuths[7] = HOA_PI4 + HOA_PI + HOA_PI2;
            elevations[0] = elevations[1] = elevations[2] = elevations[3] = HOA_PI4;
            elevations[4] = elevations[5] = elevations[6] = elevations[7] = -HOA_PI4;
            elevations[8] = HOA_PI2;
            elevations[9] = -HOA_PI2;
            azimuths[9] = azimuths[8] = 0;
        }
        else if(numberOfPoints == 11) // Not regular : Hexahedron or cube with 1 at PI/2 elevation and 1 at -Pi/2 elevation
        {
            azimuths[0] = azimuths[4] = HOA_PI4;
            azimuths[1] = azimuths[5] = HOA_PI4 + HOA_PI2;
            azimuths[2] = azimuths[6] = HOA_PI4 + HOA_PI;
            azimuths[3] = azimuths[7] = HOA_PI4 + HOA_PI + HOA_PI2;
            elevations[0] = elevations[1] = elevations[2] = elevations[3] = HOA_PI4;
            elevations[4] = elevations[5] = elevations[6] = elevations[7] = -HOA_PI4;
            elevations[8] = HOA_PI2;
            elevations[9] = elevations[9] = -HOA_PI2;
            azimuths[9] = azimuths[8] = 0;
        }
        else if(numberOfPoints == 12) // Icosahedron
        {
            azimuths[0] = 0;
            elevations[0] = HOA_PI2;
            azimuths[11] = 0;
            elevations[11] = -HOA_PI2;
            for(int i = 1; i < 6; i++)
            {
                azimuths[i] = azimuths[i+5] = (i - 1.) / 5. * HOA_2PI;
                elevations[i] = HOA_PI2 / 3.;
                elevations[i+5] = -HOA_PI2 / 3.;
            }
        }
        else // Two circles
        {
            unsigned int i = 0;
            int up = ceil(numberOfPoints * 0.5);
            int down = numberOfPoints - up;
            for(i = 0; i < up; i++)
            {
                azimuths[i] = (double)i / (double)up * HOA_2PI;
                elevations[i] = HOA_PI4;
            }
            for(; i < numberOfPoints; i++)
            {
                azimuths[i] = (double)(i - up) / (double)down * HOA_2PI;
                elevations[i] = -HOA_PI4;
            }
        }
        
        for(int i = 0; i < numberOfPoints; i++)
        {
            azimuths[i] = wrap_twopi(azimuths[i]);
            elevations[i] = wrap_twopi(elevations[i]);
        }
    }
	
} // end of namespace Hoa3D

#endif