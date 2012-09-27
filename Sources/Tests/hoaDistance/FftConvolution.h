/*
 *  FftConvolution.h
 *  signalVec
 *
 *  Created by julien colafrancesco on 13/01/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */

#ifndef DEF_FFTCONVOLUTION
#define DEF_FFTCONVOLUTION

#include "SignalProc.h"
#include "SignalVec.h"

class FftConvolution : public SignalProc
{
protected:
	long m_fftSize;
	long m_windowSize;
	long m_overlap;
	long m_hopSize;
	long m_inputIndex;
	long m_outputIndex;
	
	SignalVec* WindowVector;
	SignalVec* InputVectors;
	SignalVec* BufferVector;
	SignalVec* OutputVector;
	
	SignalVec* m_TransferFunction;
	
public:
	FftConvolution();
	FftConvolution(long aFftSize, long aWindowSize, long aOverlap, long aSampleRate, SignalVec* aTransferFunction);
	~FftConvolution();
	void changeTransferFunction(SignalVec* aTransferFunction);
	double process(double aSample);
};
#endif