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
	int* m_harmonicsIndex;
	
	double* m_output;
public:
	
	ambisonicRotate(int anOrder){
		m_order = anOrder;
		m_numberOfSphericalComponents = 2*m_order+1;
		m_harmonicsIndex = new int[2*m_order+1];
		m_output = new double[m_numberOfSphericalComponents]; 
		
		m_harmonicsIndex[0] = 0;
		for(int i = 1; i < 2*m_order+1; i++)
		{
			m_harmonicsIndex[i] = (int)floor((i-1)/2) + 1;
			if (i%2 == 1) 
				m_harmonicsIndex[i] = - m_harmonicsIndex[i];
		}
	}
	

	double* process(double* encodedSignals, double aTheta)
	{
		m_tmpOrderTheta  = aTheta;
		m_output[0] = encodedSignals[0];
		for (int i = 1; i <= m_order; i++) {
			m_tmpSin = sin(m_tmpOrderTheta);
			m_tmpCos = cos(m_tmpOrderTheta);
			m_output[2*i]   = m_tmpCos*encodedSignals[2*i] - m_tmpSin*encodedSignals[2*i-1];
			m_output[2*i-1] = m_tmpSin*encodedSignals[2*i] + m_tmpCos*encodedSignals[2*i-1];
			
			m_tmpOrderTheta += aTheta;
		}
		return m_output;
	}
	
};

#endif