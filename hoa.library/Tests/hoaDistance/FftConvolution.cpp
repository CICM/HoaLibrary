/*
 *  FftConvolution.cpp
 *  signalVec
 *
 *  Created by julien colafrancesco on 13/01/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */

#include "FftConvolution.h"


FftConvolution::FftConvolution():SignalProc(44100)
{}

FftConvolution::FftConvolution(long aFftSize, long aWindowSize, long aOverlap, long aSampleRate, SignalVec* aTransferFunction): 
SignalProc(aSampleRate), m_fftSize(aFftSize), m_windowSize(aWindowSize), m_overlap(aOverlap)
{
	m_hopSize     = m_windowSize/m_overlap;
	m_inputIndex  = m_windowSize-1;
	m_outputIndex = m_fftSize-1;
	
	m_TransferFunction = aTransferFunction;
	
	//std::cout << *m_TransferFunction<< std::endl;
	WindowVector = new SignalVec(m_windowSize, "tmp");
	BufferVector = new SignalVec(m_fftSize, "tmp");
	OutputVector = new SignalVec(m_fftSize, "tmp");
	InputVectors = new SignalVec[m_overlap];
	
	for (int i = 0; i<m_overlap; ++i) {
		InputVectors[i].Init(m_fftSize,"tmp");
	}
	WindowVector->makeHann();
	
}
FftConvolution::~FftConvolution()
{
	delete[] WindowVector;
	delete[] BufferVector;
	delete[] OutputVector;
	delete[] InputVectors;
}

void FftConvolution::changeTransferFunction(SignalVec* aTransferFunction)
{
	m_TransferFunction = aTransferFunction;
}

double FftConvolution::process(double aSample)
{
	OutputVector->setvalue(m_outputIndex, 0);
	
	m_inputIndex  = (m_inputIndex+1)  % m_windowSize;
	m_outputIndex = (m_outputIndex+1) % m_fftSize;
	
	for (int i = 0; i < m_overlap; ++i) {
		
		InputVectors[i].setvalue((i*m_hopSize+m_inputIndex) % m_windowSize, aSample);
		
		if ((i*m_hopSize+m_inputIndex) % m_windowSize == (m_windowSize - 1)) {
			
			InputVectors[i] *= *WindowVector;
			InputVectors[i].fft();
			BufferVector->multiplyWithHC(InputVectors[i], *m_TransferFunction);
			BufferVector->normalize();
			BufferVector->ifft();
			OutputVector->circularAdd(*BufferVector,m_outputIndex);
			InputVectors[i].clear();
		}
	}
	
	
	
	return (OutputVector->getValue(m_outputIndex));//*(m_fftSize/m_overlap)/(m_windowSize-1);//Todo, normalisation optimisation
}