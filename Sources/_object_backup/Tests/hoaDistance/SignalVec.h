/*
 *  SignalVec.h
 *  signalVec
 *
 *  Created by julien colafrancesco on 10/01/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */

#ifndef DEF_SIGNALVEC
#define DEF_SIGNALVEC	

#include <stdio.h>
#include <iostream>
#include <string>
#include <fftw3.h>
#include <math.h>

#define SV_PI 3.1415926535897932384626433832795

class SignalVec {
private:
	int m_length;
	int m_currentIndex;
	std::string m_domain;
	double* m_values;
	
	
	fftw_plan p_fft;
	fftw_plan p_ifft;
public:
	SignalVec();
	SignalVec(int length, std::string domain);
	~SignalVec();
	
	void Init(int length, std::string domain);
	
	void reInitCurrentIndex();
	int getLength() const;
	double getValue(int valueIndex) const;
	void setvalue(int valueIndex, double aDouble);
	int AddSample(double aSample);	
	void fft();
	void ifft();
	void clear();
	void shift(int shiftSize);
	void normalize();
	void Display(std::ostream &aCout) const;
	void addWith(SignalVec const& aSignalVec);
	void circularAdd(SignalVec const& aSignalVec, int indexOffset);
	void multiplyWith(SignalVec const& aSignalVec);
	void multiplyWithHC(SignalVec const &aFirstSignal, SignalVec const &aSecondSignal);
	void makeHann();
	
};

std::ostream &operator<<(std::ostream &aCout, SignalVec const& aSignalVec);
SignalVec& operator+=(SignalVec &aFirstSignal, SignalVec const& aSecondSignal);
SignalVec& operator*=(SignalVec &aFirstSignal, SignalVec const& aSecondSignal);
#endif

