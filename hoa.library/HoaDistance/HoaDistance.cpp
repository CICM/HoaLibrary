/*
 *  HoaDistance.cpp
 *  signalVec
 *
 *  Created by julien colafrancesco on 05/02/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */

#include "HoaDistance.h"



HoaDistance::HoaDistance(int order, double speakersDistance, double sourceDistance):
m_order(order), m_speakersDistance(speakersDistance), m_sourceDistance(sourceDistance), m_theta(0)
{
	m_fftSize = 2048;
	m_fftHalfSize = m_fftSize/2+1;
	m_sampleRate = 44100;
	
	m_tmpOutputArray = new double[m_order+1];
	m_frequencyVector = new double[1+m_fftSize/2];
	
	for (int i = 0; i < (1+m_fftSize/2); ++i) {
		m_frequencyVector[i] = i*m_sampleRate/m_fftSize;
	}
	m_frequencyVector[0] = 0.00001; //to avoid nan value in the transfer function.
	
	m_impulseResponses = new std::complex<double>*[m_order+1];
	
	for (int i = 0; i < m_order+1; i++) {
		m_impulseResponses[i] = new std::complex<double>[m_fftSize];
	}
	
	m_halfComplexImpulseResponses = new SignalVec[m_order+1];
	
	this->ComputeResponses();
	
	ConvolutionArray = new FftConvolution*[m_order+1];
	
	for (int i = 0; i <= m_order; i++) {
		ConvolutionArray[i] = new FftConvolution(m_fftSize, m_fftSize/2,2,44100,&m_halfComplexImpulseResponses[abs(i)]);
	}
	
}
void HoaDistance::ChangeSourceDistance(double sourceDistance)
{
	m_sourceDistance=sourceDistance;
	this->ComputeResponses();
	
	for (int i = 0; i <= m_order; i++) {
		ConvolutionArray[i]->changeTransferFunction(&m_halfComplexImpulseResponses[abs(i)]);
	}
	
}

void HoaDistance::setTheta(double aTheta)
{
	m_theta = aTheta;
}



void HoaDistance::ComputeResponses()
{
	double c = 340;      
	double w= 0;
	double k = 0;
	
	for (int i = 0; i<1+m_fftSize/2; i++) 
	{
		w = 2*PI*m_frequencyVector[i];
		k = w/c;
		
		for (int j = 0; j<= m_order; j++) 
		{
			m_impulseResponses[j][i] = distanceCompensation(j, k, m_sourceDistance, m_speakersDistance);
		}
	}
	
	for (int i = 0 ; i< m_order+1; i++)
	{
		m_halfComplexImpulseResponses[i].Init(m_fftSize,"fft");
	}
	
	for (int i = 0; i<=m_order; i++) {
		m_halfComplexImpulseResponses[i].setvalue(0, m_impulseResponses[i][0].real());
		m_halfComplexImpulseResponses[i].setvalue(m_fftSize/2+1, m_impulseResponses[i][m_fftSize/2+1].real());
		
		for (int j = 1; j <= int(floor((m_fftSize+1)/2))-1; j++) {
			m_halfComplexImpulseResponses[i].setvalue(j, m_impulseResponses[i][j].real());
			m_halfComplexImpulseResponses[i].setvalue(m_fftSize-j, m_impulseResponses[i][j].imag());
		}
	}
}


double* HoaDistance::process(double aSample)
{	
	for (int i = 0 ; i < m_order+1; i++) {
		m_tmpOutputArray[i] = ConvolutionArray[i]->process(aSample);
	}
	return m_tmpOutputArray;
}