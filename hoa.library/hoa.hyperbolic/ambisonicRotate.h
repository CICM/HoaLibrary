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
			m_tmpSin = sinh(m_tmpOrderTheta);
			m_tmpCos = cosh(m_tmpOrderTheta);
			m_output[2*i]   =   m_tmpCos*encodedSignals[2*i] - m_tmpSin*encodedSignals[2*i-1];
			m_output[2*i-1] = - m_tmpSin*encodedSignals[2*i] + m_tmpCos*encodedSignals[2*i-1];
			
			m_tmpOrderTheta += aTheta;
		}
		return m_output;
	}
	
//	double* process(double* encodedSignals, double aTheta)
//	{
//		m_tmpOrderTheta  = aTheta;
//		
//		m_tmpSin = sinh(m_tmpOrderTheta);
//		m_tmpCos = cosh(m_tmpOrderTheta);
//		
//		m_output[0] = encodedSignals[0] * m_tmpCos - encodedSignals[1] * m_tmpSin;
//		m_output[1] = encodedSignals[1] * m_tmpCos - encodedSignals[0] * m_tmpSin;
//		m_output[2] = encodedSignals[2];
//
//		return m_output;
//	}
	
//	double* process(double* encodedSignals, double aTheta)
//	{
//		m_tmpOrderTheta  = aTheta;
//		
//		m_tmpSin = sinh(m_tmpOrderTheta);
//		m_tmpCos = cosh(m_tmpOrderTheta);
//		
//		m_output[0] = encodedSignals[0] + encodedSignals[1] * aTheta;
//		m_output[1] = encodedSignals[1] + encodedSignals[0] * aTheta;
//		m_output[2] = sqrt(1 - aTheta * aTheta) * encodedSignals[2];
//		
//		return m_output;
//	}
	
//	double* process(double* encodedSignals, double aTheta)
//	{
//		double mu   = aTheta;
//		double smu  = sqrt( 1 -  mu * mu); 
//
//		m_output[0] = encodedSignals[0];
//		for (int i = 1; i <= m_order; i++) 
//		{
//			m_output[0] += mu * encodedSignals[2 * i -1];
//			m_output[2*i] = smu * encodedSignals[2*i];
//			
//			m_output[2*i-1] = mu * encodedSignals[0];
//			for(int j = 1; j <= m_order; j++)
//			{
//				
//				if (i == j)
//					m_output[2*i-1] += encodedSignals[2*j-1];
//				else 
//					m_output[2*i-1] += mu * encodedSignals[2*j-1];
//
//			}
//		}
//				
//
//		return m_output;
//	}
	
	
};

#endif