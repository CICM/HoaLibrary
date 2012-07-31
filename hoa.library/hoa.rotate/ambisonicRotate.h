/*
 *  untitled.h
 *  hoa.decoder~
 *
 *  Created by julien colafrancesco on 30/07/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */

#ifndef define DEF_AMBIROTATE
#define DEF_AMBIROTATE




//#define PI 3.1415926535897932384626433832795
#undef check
#include "math.h"
#include <stdio.h>

class ambisonicRotate{
	
private:
	int m_order;
	int m_numberOfSphericalComponents;
	double m_tmpOrderTheta;
	double m_tmpSin;
	double m_tmpCos;
	int m_tmpNegativeBIndex;
	int m_tmpPositiveBIndex;
	
	double* m_output;
public:
	
	ambisonicRotate(int anOrder){
		m_order = anOrder;
		m_numberOfSphericalComponents = 2*m_order+1;
		m_output = new double[m_numberOfSphericalComponents]; 
	}
	
	double* process(double* encodedSignals, double aTheta){
		
		m_tmpOrderTheta  = aTheta;
		m_tmpPositiveBIndex = m_order;
		m_tmpNegativeBIndex = m_order;
		m_output[m_order] = encodedSignals[m_order];
		while (m_tmpNegativeBIndex>0) {
			m_tmpPositiveBIndex++;
			m_tmpNegativeBIndex--;
			m_tmpCos = cos(m_tmpOrderTheta);
			//m_tmpSin = sqrt(1-m_tmpCos*m_tmpCos);
			m_tmpSin = sin(m_tmpOrderTheta);
			
			m_output[m_tmpPositiveBIndex] = m_tmpCos*encodedSignals[m_tmpPositiveBIndex] - m_tmpSin*encodedSignals[m_tmpNegativeBIndex];
			m_output[m_tmpNegativeBIndex] = m_tmpSin*encodedSignals[m_tmpPositiveBIndex] + m_tmpCos*encodedSignals[m_tmpNegativeBIndex];
			
			m_tmpOrderTheta += aTheta;
		}
		
		return m_output;
		
	}
	
};

#endif