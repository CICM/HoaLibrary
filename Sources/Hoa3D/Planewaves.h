/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_3D_PLANEWAVES
#define DEF_HOA_3D_PLANEWAVES

#include "Tools.h"

namespace Hoa3D
{
    //! The planewaves class.
    /**
     The planewaves classes, that process on a set of loudspeakers, inherit from this class. It store basic informations like the number, the coordinates and the names of loudspeakers.
	
     */
    class Planewaves
    {
	protected:
        
		unsigned int    m_number_of_loudspeakers;
        double*         m_loudspeakers_azimuth;
		double*         m_loudspeakers_elevation;
		
    public:
        
		//! The planewaves constructor.
        /** The lanewaves constructor allocates and initializes the general member values depending on a number of loudspeakers. The number of loudspkeakers must a least 1.
         
            @param     numberOfLoudspeakers	The number of loudspeakers.
         */
		Planewaves(unsigned int numberOfLoudspeakers);
        
        //! The planewaves destructor.
        /** The Planewaves destructor free the memorie allocated.
         */
        ~Planewaves();
		
        //! Set the position of a loudspeaker.
        /** Set the position of a loudspeaker with polar coordinates. The azimtuh is in radian between 0 and 2 Pi, O is the front of the soundfield and Pi is the back of the sound field. The elevation is in radian between -1/2 Pi and 1/2 Pi, -1/2 Pi the the bottom of the sound field, 0 is the center of the sound field and 1/2 Pi is the top of the sound field. The maximum index must be the number of loudspeakers - 1.
         
            @param     index		The index of the loudspeaker.
            @param     azimuth		The azimuth.
            @param     elevation	The elevation.
         */
		void setLoudspeakerPosition(unsigned int index, double azimuth, double elevation);
        
        //! Retrieve the number of loudspeakers.
		/** Retrieve the number of loudspeakers of the planewave class.
            
            @return The number of loudspeakers.
         */
		inline unsigned int getNumberOfLoudspeakers() const {return m_number_of_loudspeakers;}
        
        //! Retrieve the azimuth of a loudspeaker.
        /** Retrieve the azimuth of a loudspeaker. The azimuth of the loudspeaker is in radian, 0 radian is at the front of the soundfield and Pi is at the back of the sound field. The maximum index must be the number of loudspeakers - 1.
         
            @param      index   The index of the loudspeaker.
            @return     The azimuth of the loudspeaker.
            @see getLoudspeakerElevation
         */
		inline double getLoudspeakerAzimuth(unsigned int index) const
        {
            assert(index < m_number_of_loudspeakers);
            return m_loudspeakers_azimuth[index];
        }
		
        //! Retrieve the elevation of a loudspeaker.
		/** Retrieve the elevation of a loudspeaker. The elevation is in radian between -1/2 Pi and 1/2 Pi, -1/2 Pi the the bottom of the sound field, 0 is the center of the sound field and 1/2 Pi is the top of the sound field. The maximum index must be the number of loudspeakers - 1.
         
            @param      index   The index of the loudspeaker.
            @return     The elevation of the loudspeaker.
            @see getLoudspeakerAzimuth
         */
		inline double getLoudspeakerElevation(unsigned int index) const
        {
            assert(index < m_number_of_loudspeakers);
            return m_loudspeakers_elevation[index];
        }
		
        //! Retrieve the abscissa of a loudspeaker.
		/** Retrieve the abscissa of a loudspeaker. The abscissa is between -1 and 1, -1 is the left of the soundfield, 0 is the center of the soundfield and 1 is the right of the soundfield. The maximum index must be the number of loudspeakers - 1.
         
            @param     index    The index of the loudspeaker.
            @return    The abscissa of the loudspeaker.
            @see getLoudspeakerOrdinate
            @see getLoudspeakerHeight
         */
		inline double getLoudspeakerAbscissa(unsigned int index) const
        {
            assert(index < m_number_of_loudspeakers);
            return abscissa(1., m_loudspeakers_azimuth[index]);
        }
		
        //! Retrieve the ordinate of a loudspeaker.
		/** Retrieve the ordinate of a loudspeaker. The ordinate is between -1 and 1, -1 is the back of the soundfield, 0 is the center of the soundfield and 1 is the front of the soundfield. The maximum index must be the number of loudspeakers - 1.
         
            @param     index	The index of the loudspeaker.
            @return    The ordinate of the loudspeaker.
            @see getLoudspeakerAbscissa
            @see getLoudspeakerHeight
         */
		inline double getLoudspeakerOrdinate(unsigned int index) const
        {
            assert(index < m_number_of_loudspeakers);
            return ordinate(1., m_loudspeakers_azimuth[index]);
        }
        
        //! Retrieve the height of a loudspeaker.
        /** Retrieve the height of a loudspeaker. The height is between -1 and 1, -1 is the bottom of the soundfield, 0 is the center of the soundfield and 1 is the top of the soundfield. The maximum index must be the number of loudspeakers - 1.
         
            @param      index	The index of the loudspeaker.
            @return     The height of the loudspeaker.
            @see getLoudspeakerAbscissa
            @see getLoudspeakerOrdinate
         */
		inline double getLoudspeakerHeight(unsigned int index) const
        {
            assert(index < m_number_of_loudspeakers);
            return abscissa(1., m_loudspeakers_elevation[index]);
        }
        
        //! Retrieve the number of loudspeaker.
        /** Retrieve a name for an loudspeaker in a std::string format that will be "Loudspeaker index azimuth elevation".
         
         @param     index	The global index of a loudspeaker.
         @return    The name of the loudspeaker
         */
		inline std::string getLoudspeakerName(unsigned int index)
        {
            assert(index < m_number_of_loudspeakers);
            return "Loudspeaker " + int_to_string(index + 1) + " " + int_to_string((int)getLoudspeakerAzimuth(index)) + " " + int_to_string((int)getLoudspeakerElevation(index));
        };
    };
	
} // end of namespace Hoa3D

#endif