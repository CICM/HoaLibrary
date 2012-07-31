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
m_order(order), m_channelNumber(channelNumber)
{
	
	spkrsAngles = new double[channelNumber];
	for(int i = 0; i < channelNumber; i++)
	{
		spkrsAngles[i] = (2*PI/channelNumber)*i;
		
	}
	
	// Creation et initialisation de la matrice de reencodage
	m = new boost::numeric::ublas::matrix<double>(2*order+1,channelNumber);
	
	for (int i = 0; i < channelNumber; i++){
		
		for (int j=-m_order; j <= m_order; j++) {

			if (j<0) {
				
				(*m)(j+order,i) = sin(abs(j)*spkrsAngles[i]);

			}
			else {
				(*m)(j+order,i) = cos(abs(j)*spkrsAngles[i]);

			}
		}
	}
	
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

std::vector<double>*  ambisonicDecode::process(const double* encodedSignals)
{
	for (int i = 0; i < 2*m_order+1; i++) 
	{
		(*sourceMatrix)(i,0) = encodedSignals[i];
	}
	
	*outputVector = prod(*pseudoInvertedSpkrsMatrix, *sourceMatrix);
	
	//std::cout << *m << std::endl;
	
	return dynamic_cast<std::vector<double>* > (&(outputVector->data()));
	
	
}