/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_3D_PLANEWAVES
#define DEF_HOA_3D_PLANEWAVES

#include "../CicmLibrary/CicmLibrary.h"
#include "Speaker.h"

namespace Hoa3D
{
    //! The Planewaves class.
    /**
     The Planewaves class is a base class destinated to be inherited by classes who dont care about spherical harmonics but a number of loudpeakers (real or virtual). It store basics information like the umber of channels, number of inputs, outputs...
	 @see Ambisonic
     */
    class Planewaves
    {
	protected:
		unsigned int	m_number_of_inputs;
		unsigned int	m_number_of_outputs;
		unsigned int    m_number_of_loudspeakers;
		Speaker*		m_speakerList;
		bool			m_autoName;
		
		void updateSpeakerName(unsigned int index = -1);
		
    public:
        
		//! The Planewaves constructor.
        /** The Planewaves constructor allocates and initializes the general member values depending on a number of loudspeaker.
         @param     numberOfLoudspeakers	The number of loudspeakers (more than one could be a good start for an ambisonic setup !).
         */
		Planewaves(unsigned int numberOfLoudspeakers = 1, bool autoName = true);
        
        /** The Planewaves destructor.
         */
        ~Planewaves();
        
        /** Retrieve the number of inputs.
		 @return The number of inputs.
         */
        unsigned int	getNumberOfInputs() const {return m_number_of_inputs;}
        
        /** Retrieve the number of outputs.
		 @return The number of outputs.
         */
        unsigned int	getNumberOfOutputs() const {return m_number_of_outputs;}
		
		/** Retrieve the number of loudspeakers.
		 @return The number of loudspeakers.
         */
		unsigned int	getNumberOfLoudspeakers() const {return m_number_of_loudspeakers;}
		
		/** Set the name of a loudspeaker.
         @param     index	The index of the loudspeaker.
		 @return    name	The name of the loudspeaker.
         */
		void			setLoudspeakerName(unsigned int index, std::string name);
		
		/** Get a loudspeaker object.
         @param     index	The index of a loudspeaker.
		 @return    a Speaker object ref.
         */
		Speaker&		getSpeaker(unsigned int index) const { assert(index < m_number_of_loudspeakers); return m_speakerList[index];}
		
		/** Retrieve the name of a loudspeaker.
         @param     index	The global index of a loudspeaker.
		 @return    The name of the loudspeaker
         */
		std::string		getLoudspeakerName(unsigned int index);
		
		/** Get the loudspeaker abscissa.
         @param     index		The index of the loudspeaker.
		 @return				The azimuth value in radians (between 0 and 2π).
		 @see getLoudspeakerOrdinate
         */
		double          getLoudspeakerAbscissa(unsigned int index) const;
		
		/** Get the loudspeaker elevation.
         @param     index		The index of the loudspeaker.
		 @return				The elevation value in radians (between 0 and 2π).
         */
		double          getLoudspeakerOrdinate(unsigned int index) const;
		
		/** Get the loudspeaker azimuth.
         @param     index		The index of the loudspeaker.
		 @return				The azimuth value in radians (between 0 and 2π).
		 @see getLoudspeakerElevation, getLoudspeakerDistance
         */
		double          getLoudspeakerAzimuth(unsigned int index) const;
		
		/** Get the loudspeaker elevation.
         @param     index		The index of the loudspeaker.
		 @return				The elevation value in radians (between 0 and 2π).
		 @see getLoudspeakerAzimuth, getLoudspeakerDistance
         */
		double          getLoudspeakerElevation(unsigned int index) const;
		
		/** Get the loudspeaker distance.
         @param     index		The index of the loudspeaker.
		 @return				The distance value (default 1.0f).
		 @see getLoudspeakerAzimuth, getLoudspeakerElevation
         */
		double          getLoudspeakerDistance(unsigned int index) const;
		
		/** Set the number of loudspeaker.
         @param     numberOfLoudspeakers	The total number of loudspeakers.
         */
		void setNumberOfLoudspeakers(unsigned int numberOfLoudspeakers);
		
		/** Set the position of a loudspeaker.
         @param     index		The index of the loudspeaker.
		 @param     azimuth		The azimuth value in radians (between 0 and 2π).
		 @param     elevation	The elevation value in radians (between 0 and 2π).
         */
		void setLoudspeakerPosition(unsigned int index, double azimuth, double elevation);
    };
	
} // end of namespace Hoa3D

#endif