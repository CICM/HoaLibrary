/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __DEF_HOA_2D_VIRTUALMICMANAGER__
#define __DEF_HOA_2D_VIRTUALMICMANAGER__

#include "../Hoa/Hoa.h"

namespace Hoa2D
{
	class VirtualMicManager
	{
	private:
		
		class VirtualMic
		{
		private:
			
			double  m_widerValue;
			double  m_angleInRadian;
			double  m_distance;
			bool    m_isSelected;
			double  m_fisheyeStartAngleInRadian;
			double  m_fisheyeEndAngleInRadian;
			
		public:
			
			VirtualMic()
			{
				m_angleInRadian = 0;
				m_fisheyeEndAngleInRadian = m_fisheyeStartAngleInRadian = m_angleInRadian;
				m_widerValue = 1;
				m_distance = 1;
				m_isSelected = false;
			}
			~VirtualMic() {}
			
			bool   isSelected()			const {return m_isSelected;}
			double getDistance()		const {return m_distance;}
			double getAngleInRadian()	const {return m_angleInRadian;}
			double getAngleInDegree()	const {return radToDeg(m_angleInRadian);}
			double getWiderValue()		const {return m_widerValue;}
			double getFisheyeStartAngle() const { return m_fisheyeStartAngleInRadian; }
			double getAbscissa()		const {return abscissa(m_distance, m_angleInRadian);}
			double getOrdinate()		const {return ordinate(m_distance, m_angleInRadian);}
			double getAzimuth()			const {return m_angleInRadian;}
			
			void setAngleInRadian(const double angle) { m_angleInRadian = wrap_twopi(angle); }
			void setAngleInDegree(const double angle) { setAngleInRadian(degToRad(angle)); }
			void rotateAngleInRadian(const double deltaRadian) { m_angleInRadian = wrap_twopi(m_angleInRadian + deltaRadian); }
			void setAngleCartesianCoordinate(double abscissa, double ordinate) { m_angleInRadian = azimuth(abscissa, ordinate); }
			void setDistance(const double distance) {m_distance = clip_min(distance, 0.);}
			void setWiderValue(const double widerValue) { m_widerValue = clip_minmax(widerValue, 0, 1); }
			void setFisheyeStartAngle() { m_fisheyeStartAngleInRadian = m_angleInRadian; }
			void setFisheyeStartAngle(const double radian) { m_fisheyeStartAngleInRadian = wrap_twopi(radian); }
			void setFisheyeEndAngle() { m_fisheyeEndAngleInRadian = m_angleInRadian; }
			void setFisheyeEndAngle(const double radian) { m_fisheyeEndAngleInRadian = wrap_twopi(radian); }
			void setSelected(int selectedState)
			{
				if (selectedState == -1) // toggle Mode
					m_isSelected = !m_isSelected;
				else if(selectedState == 1)
					m_isSelected = true;
				else
					m_isSelected = false;
			}
		};
		
		std::vector <VirtualMic*> m_mics;
		double* m_defaultAngles;
		double  m_fisheyeStep;
		double  m_fisheyeDestAngleInRadian;
		
		inline int safeIndex(const int index) const {return clip_minmax(index, 0, m_mics.size()-1);}
		double radianInterp(double step, double startRad, double endRad);
		void setDefaultAngles();
		
	public:
		
		VirtualMicManager(long number_of_mics = 0);
		~VirtualMicManager();
		
		void setFisheyeDestAngle(double angle_radian);
		void resetAngles(const int index = -1);
		void resetWides(const int index = -1);
		void setNumberOfMics(long number_of_mics);
		void setAnglesInRadian(double* angles, long size);
		void setAnglesInDegree(double* angles, long size);
		void setAngleInRadian(const int index, double angle);
		void setAngleInDegree(const int index, double angle);
		void setWiderValues(double* widerValues, long size);
		void setWiderValue(const int index, double widerValue);
		void setDistance(const int index, double distance);
		void setSelected(const int index, int selectedState);
		void selectMicsBetweenMics(int index1, int index2);
		void rotateSelectedMicsWithRadian(double newRadian, int sourceBeingDragged, int magnet = 0);
		void setSelectedMicsWiderValueWithRadiusDelta(double deltaRadius);
		void setFisheyeStartAngle(const int index);					// take current angle
		void setFisheyeStartAngle(const int index, double radian);	// take an angle
		void setAngleCartesianCoordinate(const int index, double abscissa, double ordinate);
		void setSelectedMicsFisheyeStepWithDelta(const int index, double delta); // index : -1 = all | -2 = selectedMics | >= 0 = index
		void setFisheyeStepDirect(const int index, double fisheyeStep); // index : -1 = all | -2 = selectedMics | >= 0 = index
		void setAngleToClosestDefMicAngle(const int index);
		
		long          getNumberOfSelectedMics();
		double        getClosestDefMicAngle(const int index);
		double        getClosestDefMicAngle(double angle_radian);
		double        getClosestDefMicDistance(const int index);
		double        getClosestDefMicDistance(double angle_radian);
		
		inline double getDistanceBetweenTwoDefMics()	const { return HOA_2PI / (double)m_mics.size(); }
		inline double getFisheyeDestAngle()				const { return m_fisheyeDestAngleInRadian; }
		inline long   getNumberOfMics()					const { return m_mics.size(); }
		inline double getFisheyeStep()					const { return m_fisheyeStep; }
		inline bool   isSelected(const int index)		const {return m_mics[safeIndex(index)]->isSelected(); }
		inline double getDistance(const int index)		const {return m_mics[safeIndex(index)]->getDistance(); }
		inline double getAngleInRadian(const int index) const {return m_mics[safeIndex(index)]->getAngleInRadian(); }
		inline double getAngleInDegree(const int index) const {return m_mics[safeIndex(index)]->getAngleInDegree(); }
		inline double getWiderValue(const int index)	const {return m_mics[safeIndex(index)]->getWiderValue(); }
		inline double getFisheyeStartAngle(const int index) const { return m_mics[safeIndex(index)]->getFisheyeStartAngle(); }
		inline double getAbscissa(const int index)		const {return m_mics[safeIndex(index)]->getAbscissa(); }
		inline double getOrdinate(const int index)		const {return m_mics[safeIndex(index)]->getOrdinate(); }
		inline double getAzimuth(const int index)		const {return m_mics[safeIndex(index)]->getAzimuth(); }
	};
}

#endif
