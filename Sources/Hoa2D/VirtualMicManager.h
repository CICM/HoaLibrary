/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_2D_VIRTUALMICMANAGER
#define DEF_HOA_2D_VIRTUALMICMANAGER

#include "../Hoa/Hoa.h"

namespace Hoa2D
{
	//! The virtual microphone manager
    /** The virtual microphone manager should be used to manage a group of virtual microphones.
     */
	class VirtualMicManager
	{
	private:

		class VirtualMic
		{
		private:
			
			double  m_azimuth;
			double  m_directivity;
			bool    m_isSelected;
			double  m_fisheyeStartAzimuth;
			double  m_fisheyeEndAzimuth;
			
		public:

			VirtualMic(double azimuth = 0.0f, double directivity = 1.0f)
			{
				setAzimuth(azimuth);
				m_fisheyeEndAzimuth = m_fisheyeStartAzimuth = m_azimuth;
				setDirectivity(directivity);
				m_isSelected = false;
			}
			~VirtualMic() {}
			
			bool   isSelected()			const {return m_isSelected;}
			double getDirectivity()		const {return m_directivity;}
			double getFisheyeStartAzimuth() const { return m_fisheyeStartAzimuth; }
			double getAbscissa()		const {return abscissa(1.0f, m_azimuth);}
			double getOrdinate()		const {return ordinate(1.0f, m_azimuth);}
			double getAzimuth()			const {return m_azimuth;}
			
			void setAzimuth(const double angle) { m_azimuth = wrap_twopi(angle); }
			void rotateAzimuth(const double deltaAzimuth) { m_azimuth = wrap_twopi(m_azimuth + deltaAzimuth); }
			void setDirectivity(const double widerValue) { m_directivity = clip_minmax(widerValue, 0, 1); }
			void setFisheyeStartAzimuth() { m_fisheyeStartAzimuth = m_azimuth; }
			void setFisheyeStartAzimuth(const double radian) { m_fisheyeStartAzimuth = wrap_twopi(radian); }
			void setFisheyeEndAngle() { m_fisheyeEndAzimuth = m_azimuth; }
			void setFisheyeEndAngle(const double radian) { m_fisheyeEndAzimuth = wrap_twopi(radian); }
			void setSelected(const int state) { m_isSelected = (state == -1) ? !m_isSelected : (state != 0); }
		};
		
		std::vector <VirtualMic*> m_mics;
		double* m_defaultAngles;
		double  m_fisheyeStep;
		double  m_fisheyeDestAzimuth;
		
		inline int safeIndex(const int index) const {return clip_minmax(index, 0, m_mics.size()-1);}
		double radianInterp(double step, double startRad, double endRad);
		void setDefaultAzimuth();
		
	public:
		
		//! The virtual microphone manager constructor.
		/**	The virtual microphone manager constructor allocates and initialize the member values for each virtual microphone.
		 
		 @param     number_of_mics		The number of virtual microphones you need to manage, default is 1.
		 */
		VirtualMicManager(unsigned int number_of_mics = 1);
		
		//! The virtual microphone manager destructor.
        /**	The virtual microphone manager destructor free the memory.
         */
		~VirtualMicManager();
		
		//! Set the number of virtuals microphones you want to manage.
		/**
		 @param     number_of_mics		The number of virtual microphones you need to manage, default is 1.
         */
		void setNumberOfMics(unsigned int number_of_mics);
		
		//! Set one or each virtual microphone azimuth value.
		/**
		 If you want to reset all of the microphones azimuth value, pass -1 in the index parameter.
         
		 @param     index		The index of the microphone (pass -1 to reset all of them).
		 @param     azimuth		The new azimuth value in radians.
		 @see resetAzimuth, setAzimuthList
         */
		void setAzimuth(const int index, double azimuth);
		
		//! Set several virtual microphone azimuth with a list.
		/**
		 @param     azimuths	An array of azimuth values in radians.
		 @param     size		The size of the array.
		 @see setAzimuth, setDirectivity
         */
		void setAzimuthList(double* azimuths, long size);
		
		//! Reset one or each virtual microphone azimuth value.
		/**	Reset one or each virtual microphone to the default azimuth value.
		 If you want to reset all of the microphones azimuth value, pass -1 in the index parameter.
         
		 @param     index		The index of the microphone (pass -1 to reset all of them).
		 @see setAzimuth, setAzimuthList
         */
		void resetAzimuth(const int index = -1);
		
		//! Set one or each virtual microphone directivity value.
		/**
		 If you want to reset all of the microphones azimuth value, pass -1 in the index parameter.
         
		 @param     index			The index of the microphone (pass -1 to reset all of them).
		 @param     directivity		The new directivity value (between 0 and 1).
		 @see resetDirectivity, setDirectivityList
         */
		void setDirectivity(const int index, const double directivity);
		
		//! Set several virtual microphone directivity value with a list.
		/**
		 @param     directivities	An array of directivity (between 0 and 1).
		 @param     size			The size of the array.
		 @see setDirectivity, resetDirectivity
         */
		void setDirectivityList(double* directivities, long size);
		
		//! Reset one or each virtual microphone directivity to 1.
		/**
		 If you want to reset all of the microphones directivity value, pass -1 in the index parameter.
         
		 @param     index		The index of the microphone (pass -1 to reset all of them).
		 @see setDirectivity, setDirectivityList
         */
		void resetDirectivity(const int index = -1);
		
		//! Set the selected state of one or each virtual microphone.
		/**
		 If you want to reset all of the microphones selected state, pass -1 in the index parameter.
         
		 @param     index				The index of the microphone (pass -1 to reset all of them).
		 @param     selectedState		The selected state, pass 0 to unselect, 1 to select and -1 to toggle the state.
		 @see getNumberOfSelectedMics
         */
		void setSelected(const int index, int selectedState);
		
		//! Rotate all of the currently selected microphones relative to one microphone azimuth rotation.
		/**
		 @param     newRadian			The new azimuth of the source which is being dragged
		 @param     sourceBeingDragged	The index of the microphone which is being dragged.
		 @param     magnet				Pass 1 to magnetize the microphone to one of the default azimuth positions
         */
		void rotateSelectedMics(double newRadian, int sourceBeingDragged, int magnet = 0);
		
		//! Set fisheye destination azimuth.
		/**
		 @param     azimuth		The azimuth value of the fisheye destination in radians.
		 @see getFisheyeDestAzimuth, setFisheyeStartAzimuth
         */
		void setFisheyeDestAzimuth(double azimuth);
		
		//! Set the fisheye start azimuth of one or several microphone with current azimuth.
		/**
		 @param     index				The index of the microphone if greather than -1, pass -2 to affect all selected microphones, pass -1 to affect all microphones
		 @see
         */
		void setFisheyeStartAzimuth(const int index);
		
		//! Set the fisheye start azimuth of one or several microphone.
		/**
		 @param     index				The index of the microphone if greather than -1, pass -2 to affect all selected microphones, pass -1 to affect all microphones
         */
		void setFisheyeStartAzimuth(const int index, double radian);
		
		//! Increment or decrement the fisheye step by a value.
		/**
		 @param     index				The index of the microphone if greather than -1, pass -2 to affect all selected microphones, pass -1 to affect all microphones
		 @see setFisheyeStepDirect
         */
		void setFisheyeStepWithDelta(const int index, double delta);
		
		//! Set the fisheye step directly.
		/**
		 @param     index				The index of the microphone if greather than -1, pass -2 to affect all selected microphones, pass -1 to affect all microphones
		 @param		fisheyeStep			The fisheye step (between 0 and 1).
		 @see setFisheyeStepWithDelta
         */
		void setFisheyeStepDirect(const int index, double fisheyeStep);
		
		//! Set virtual microphone azimuth value to the closest default azimuth position value.
		/**
		 @param     index		The index of the microphone.
		 @see resetAzimuth, setAzimuth
         */
		void setAzimuthToClosestDefMicAzimuth(const int index);
		
		//! Retrieve the number of selected microphones.
		/**
		 @return     The number of selected microphones.
		 @see setSelected
         */
		long          getNumberOfSelectedMics();
		
		//! Retrieve the closest default azimuth position of a virtual microphone.
		/**
		 @param     index		The index of the microphone.
		 @return    closest default azimuth position of the virtual microphone.
		 @see getClosestDefMicDistance
         */
		double        getClosestDefMicAzimuth(const int index);
		
		//! Retrieve the closest default azimuth position relative to an azimuth value.
		/**
		 @param     azimuth		The relative azimuth.
		 @return    The closest default azimuth position of the virtual microphone relative to the azimuth value you passed in.
		 @see getClosestDefMicDistance
         */
		double        getClosestDefMicAzimuth(double azimuth);
		
		//! Retrieve the distance to the closest default azimuth position relative to the azimuth of a virtual microphone.
		/**
		 @param     index		The index of the microphone.
		 @return    The distance to the closest default azimuth position.
		 @see getClosestDefMicAzimuth
         */
		double        getClosestDefMicDistance(const int index);
		
		//! Retrieve the distance to the closest default azimuth position relative to an azimuth value.
		/**
		 @param     azimuth		The relative azimuth.
		 @return    The distance to the closest default azimuth position of the virtual microphone relative to the azimuth value you passed in.
		 @see getClosestDefMicAzimuth
         */
		double        getClosestDefMicDistance(double azimuth);
		
		//! Retrieve the fisheye destination azimuth value.
		/**
		 @return    The fisheye destination azimuth value.
		 @see setFisheyeDestAzimuth
         */
		inline double getFisheyeDestAzimuth()			const { return m_fisheyeDestAzimuth; }
		
		//! Retrieve the number of virtual microphones currently managed.
		/**
		 @return    The number of virtual microphones currently managed.
		 @see setNumberOfMics
         */
		inline long   getNumberOfMics()					const { return m_mics.size(); }
		
		//! Retrieve the current fisheye step.
		/**
		 @return    The current fisheye step.
		 @see setFisheyeStepDirect, setFisheyeStepWithDelta
         */
		inline double getFisheyeStep()					const { return m_fisheyeStep; }
		
		//! Retrieve the selection state of a virtual microphone.
		/**
		 @param     index		The index of the microphone.
		 @return    The selection state of the virtual microphone.
		 @see setSelected
         */
		inline bool   isSelected(const int index)		const {return m_mics[index]->isSelected(); }
		
		//! Retrieve the directivity value of a virtual microphone.
		/**
		 @param     index		The index of the microphone.
		 @return    The directivity value of the virtual microphone.
		 @see setDirectivity
         */
		inline double getDirectivity(const int index)	const {return m_mics[index]->getDirectivity(); }
		
		//! Retrieve the fisheye start azimuth value of a virtual microphone.
		/**
		 @param     index		The index of the microphone.
		 @return    The fisheye start azimuth value of the virtual microphone.
		 @see setFisheyeStartAzimuth
         */
		inline double getFisheyeStartAzimuth(const int index) const { return m_mics[index]->getFisheyeStartAzimuth(); }
		
		//! Retrieve the abscissa of a virtual microphone.
		/**
		 @param     index		The index of the microphone.
		 @return    The abscissa of the virtual microphone.
         */
		inline double getAbscissa(const int index)		const {return m_mics[index]->getAbscissa(); }
		
		//! Retrieve the ordinate of a virtual microphone.
		/**
		 @param     index		The index of the microphone.
		 @return    The ordinate of the virtual microphone.
         */
		inline double getOrdinate(const int index)		const {return m_mics[index]->getOrdinate(); }
		
		//! Retrieve the azimuth of a virtual microphone.
		/**
		 @param     index		The index of the microphone.
		 @return    The azimuth of the virtual microphone.
		 @see setAzimuth
         */
		inline double getAzimuth(const int index)		const {return m_mics[index]->getAzimuth(); }
	};
}

#endif
