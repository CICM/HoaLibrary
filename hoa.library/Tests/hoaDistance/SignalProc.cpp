/*
 *  SignalProc.cpp
 *  signalVec
 *
 *  Created by julien colafrancesco on 13/01/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */

#include "SignalProc.h"

SignalProc::SignalProc(long aSampleRate)
{
	m_sampleRate = aSampleRate;
}

long SignalProc::getSampleRate()
{
	return m_sampleRate;
}

void SignalProc::setSampleRate(double aSampleRate)
{
	m_sampleRate = aSampleRate;
}