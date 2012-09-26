/*
 *  SignalProc.h
 *  signalVec
 *
 *  Created by julien colafrancesco on 13/01/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */

#ifndef DEF_SIGNALPROC
#define DEF_SIGNALPROC

class SignalProc
{
protected:
	long m_sampleRate;
	
public:
	SignalProc(long aSampleRate);
	virtual double process(double aSample)  = 0;
	long getSampleRate();
	void setSampleRate(double aSampleRate);
};


#endif