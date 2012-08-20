/*
 *  ambisonicDecode.cpp
 *  signalVec
 *
 *  Created by julien colafrancesco on 02/02/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */

#include "ambisonicDecode.h"

ambisonicDecode::ambisonicDecode(int channelNumber,int order): 
m_order(order), m_channelNumber(channelNumber), m_numberOfComponents(order*2+1)
{
	
	m_harmonicsIndex = new int[m_numberOfComponents];
	m_harmonicsIndex[0] = 0;
	for(int i = 1; i < m_numberOfComponents; i++)
	{
		m_harmonicsIndex[i] = (int)floor((i-1)/2) + 1;
		if (i%2 == 1) 
			m_harmonicsIndex[i] = - m_harmonicsIndex[i];
	}
	
	spkrsAngles = new double[channelNumber];
	for(int i = 0; i < channelNumber; i++)
	{
		spkrsAngles[i] = (2*PI/channelNumber)*i;
		
	}
	
	// Creation et initialisation de la matrice de reencodage
	m = new boost::numeric::ublas::matrix<double>(2*order+1,channelNumber);
	
	for (int i = 0; i < m_channelNumber; i++){
		for (int j=0; j < m_numberOfComponents; j++) {
			
			if (m_harmonicsIndex[j]<0)
				(*m)(j,i) = sin(abs(m_harmonicsIndex[j])*spkrsAngles[i]);
			else 
				(*m)(j,i) = cos(abs(m_harmonicsIndex[j])*spkrsAngles[i]);
		}
	}
	
//	for (int i = 0; i < channelNumber; i++){
//		
//		for (int j=-m_order; j <= m_order; j++) {
//
//			if (j<0) {
//				
//				(*m)(j+order,i) = sin(abs(j)*spkrsAngles[i]);
//
//			}
//			else {
//				(*m)(j+order,i) = cos(abs(j)*spkrsAngles[i]);
//
//			}
//		}
//	}
	
	// Calcul de la pseudoInverse 
	matrix<double> MMtrans(2*order+1,2*order+1);
	MMtrans = prod((*m), trans(*m));
	
	matrix<double> InverseMMtrans(2*order+1,2*order+1);
	InvertMatrix(MMtrans, InverseMMtrans);
	
	pseudoInvertedSpkrsMatrix = new boost::numeric::ublas::matrix<double>(channelNumber,2*order+1);
	*pseudoInvertedSpkrsMatrix = prod(trans(*m),InverseMMtrans);	
	
	//Creation du vecteur source
	sourceMatrix = new boost::numeric::ublas::matrix<double>(2*order+1,1);
	
	outputVector = new boost::numeric::ublas::matrix<double,row_major,std::vector<double> >(channelNumber,1);
}

std::vector<double>*  ambisonicDecode::process()
{
	*outputVector = prod(*pseudoInvertedSpkrsMatrix, *sourceMatrix);
	
	//std::cout << *m << std::endl;
	
	return dynamic_cast<std::vector<double>* > (&(outputVector->data()));
}

void ambisonicDecode::record(double harmonic, int index)
{
	(*sourceMatrix)(index,0) = harmonic;
}
