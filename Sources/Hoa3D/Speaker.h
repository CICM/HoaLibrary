/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_3D_SPEAKER
#define DEF_HOA_3D_SPEAKER

#include "../CicmLibrary/CicmLibrary.h"

namespace Hoa3D
{
    //! The Speaker class.
    /**
     The Speaker class is a basic class representing a loudspeaker in a, real or virtual, space.
	 @see Planewaves
     */
    class Speaker
    {
	private:
		double m_azimuth, m_elevation, m_distance;
		std::string m_name;
		
    public:
		
		Speaker() : m_azimuth(0.0f), m_elevation(0.0f), m_distance(1.0f), m_name("") {}
        
		//! The Speaker constructor.
        /** The Speaker constructor sets the default position and name of the loudspeaker.
         @param     numberOfLoudspeakers	The number of loudspeakers (more than one could be a good start for an ambisonic setup !).
         */
		Speaker(const double azimuth, const double elevation, std::string name = "")
		{
			m_azimuth = Tools::radian_wrap(azimuth);
			m_elevation = Tools::radian_wrap(elevation);
			m_distance = 1.0f;
			m_name = "";
		}
        
        /** The Speaker destructor.
         */
        ~Speaker() {}
        
        /** Get the loudspeaker azimuth.
		 @return The azimuth value (between 0 and 2π).
		 @see getElevation, getDistance
         */
        double getAzimuth() const {return m_azimuth;}
		
		/** Get the loudspeaker elevation.
		 @return The elevation value (between 0 and 2π).
		 @see getAzimuth, getDistance
         */
        double getElevation() const {return m_elevation;}
		
		/** Get the loudspeaker distance.
		 @return The distance value = 1.
		 @see getAzimuth, getElevation
         */
        double getDistance() const {return m_distance;}
		
		/** Get the loudspeaker's x-axis position.
		 @return The x-axis position of the loudspeaker;
         */
        double getX() const {return Tools::abscissa(m_distance, m_azimuth);}
		
		/** Get the loudspeaker's y-axis position.
		 @return The y-axis position of the loudspeaker;
         */
        double getY() const {return Tools::ordinate(m_distance, m_azimuth);}
		
		/** Get the loudspeaker's z-axis position.
		 @return The z-axis position of the loudspeaker;
         */
        double getZ() const {return Tools::ordinate(m_distance, m_elevation);}
        
        /** Get the name given to the loudspeaker.
		 @return The name of the loudspeaker.
		 @see setName
         */
		std::string getName() const {return m_name;}
		
		/** Set the loudspeaker azimuth.
		 @param azimuth The azimuth value (between 0 and 2π).
		 @see setElevation, setDistance
         */
        void setAzimuth(const double azimuth) {m_azimuth = Tools::radian_wrap(azimuth);}
		
		/** Set the loudspeaker elevation.
		 @param elevation The elevation value (between 0 and 2π).
		 @see setAzimuth, setDistance
         */
        void setElevation(const double elevation) {m_elevation = Tools::radian_wrap(elevation);}
		
		/** Set the loudspeaker distance.
		 @param distance The distance value ( > 0).
		 @see setAzimuth, setElevation
         */
        void setDistance(const double elevation) {m_distance = Tools::clip_min(elevation, 0);}
        
        /** Set the name of the loudspeaker.
		 @param name The name of the loudspeaker.
		 @see getName
         */
		void setName(std::string name) {m_name = name;}
    };
	
} // end of namespace Hoa3D

#endif