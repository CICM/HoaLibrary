/*
 *  SignalVec.cpp
 *  signalVec
 *
 *  Created by julien colafrancesco on 10/01/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */

#include "SignalVec.h"

SignalVec::SignalVec(){}

SignalVec::SignalVec(int length, std::string domain): m_length(length), m_currentIndex(0), m_domain(domain)
{
	if ((m_domain == "frq" || m_domain == "tmp") == 0 ) {
		m_domain = "tmp";
	}
	
	m_values = (double*) fftw_malloc(sizeof(double) * m_length);
	memset(m_values, 0, sizeof(double)*m_length);
	
	p_fft  = fftw_plan_r2r_1d(m_length, m_values, m_values, FFTW_R2HC, FFTW_ESTIMATE);
	p_ifft = fftw_plan_r2r_1d(m_length, m_values, m_values, FFTW_HC2R, FFTW_ESTIMATE);
}

SignalVec::~SignalVec(){
	fftw_destroy_plan(p_fft);
	fftw_destroy_plan(p_ifft);
	fftw_free(m_values);
}

void SignalVec::Init(int length, std::string domain)
{
	m_length = length;
	m_currentIndex = 0;
	m_domain = domain;
	
	if ((m_domain == "frq" || m_domain == "tmp") == 0 ) {
		m_domain = "tmp";
	}
	
	m_values = (double*) fftw_malloc(sizeof(double) * m_length);
	memset(m_values, 0, sizeof(double)*m_length);
	
	p_fft  = fftw_plan_r2r_1d(m_length, m_values, m_values, FFTW_R2HC, FFTW_ESTIMATE);
	p_ifft = fftw_plan_r2r_1d(m_length, m_values, m_values, FFTW_HC2R, FFTW_ESTIMATE);
}


int SignalVec::getLength() const
{
	return m_length;
}

double SignalVec::getValue(int valueIndex) const
{
	return m_values[valueIndex];
}

void SignalVec::setvalue(int valueIndex, double	aDouble)
{
	m_values[valueIndex] = aDouble;
}

int SignalVec::AddSample(double aSample)
{
	m_values[m_currentIndex] = aSample;
	m_currentIndex++;
	
	return m_currentIndex;
}

void SignalVec::reInitCurrentIndex()
{
	m_currentIndex = 0;
}


void SignalVec::fft()
{
	fftw_execute(p_fft);
	m_domain = "frq";
	
}

void SignalVec::ifft()
{
	fftw_execute(p_ifft);
	m_domain = "tmp";
}

void SignalVec::clear()
{
	memset(m_values, 0, sizeof(double)*m_length);
}

void SignalVec::shift(int shiftSize)
{
	memmove(&m_values[0], &m_values[shiftSize], sizeof(double)*(m_length-shiftSize));
	memset(&m_values[m_length-shiftSize], 0, sizeof(double)*shiftSize);
}

void SignalVec::normalize()
{
	for (int i = 0; i <m_length; ++i) {
		m_values[i] = m_values[i] / m_length;
	}
}

void SignalVec::Display(std::ostream &aCout) const
{
	for (int i = 0; i <m_length; ++i) {
		aCout << m_values[i]<< std::endl;
	}
}
void SignalVec::addWith(SignalVec const& aSignalVec)
{
	for (int i = 0; i < std::min(m_length, aSignalVec.getLength()); ++i) {
		m_values[i] += aSignalVec.getValue(i);
	}
}

void SignalVec::circularAdd(SignalVec const& aSignalVec, int indexOffset)
{
	for (int i = 0; i < std::min(m_length, aSignalVec.getLength()); ++i) {
		
		m_values[(i+indexOffset)%m_length] += aSignalVec.getValue(i); 

	}
}

void SignalVec::multiplyWith(SignalVec const& aSignalVec)
{
	for (int i = 0; i < std::min(m_length, aSignalVec.getLength()); ++i) {
		m_values[i] *= aSignalVec.getValue(i);
	}
	
}
void SignalVec::multiplyWithHC(SignalVec const &aFirstSignal, SignalVec const &aSecondSignal)
{

	if(m_length == aFirstSignal.getLength() && m_length == aSecondSignal.getLength())
	{
		
		
		m_values[0] = aFirstSignal.getValue(0) * aSecondSignal.getValue(0);
		m_values[m_length/2] = aFirstSignal.getValue(m_length/2) * aSecondSignal.getValue(m_length/2);
		
			
		for (int i = 1; i <= m_length/2 - 1; ++i) {
			m_values[i] = aFirstSignal.getValue(i)			  * aSecondSignal.getValue(i) 
						- aFirstSignal.getValue(m_length - i) * aSecondSignal.getValue(m_length - i);
			
			m_values[m_length/2 + i] = aFirstSignal.getValue(m_length/2 - i) * aSecondSignal.getValue(m_length/2 + i)
									 + aFirstSignal.getValue(m_length/2 + i) * aSecondSignal.getValue(m_length/2 - i);
		}
			
	}
	else {
		std::cout << "Signals must have the same length in order to do the half complex multiplication" << std::endl;
	}
	

}

void SignalVec::makeHann()
{
	for (int i = 0; i<m_length; ++i) {
		m_values[i] = 0.5 * (1 - cos(2*SV_PI*i/(m_length)));
	}
}

std::ostream &operator<<(std::ostream &aCout, SignalVec const& aSignalVec )
{
	aSignalVec.Display(aCout);
	return aCout;
}



SignalVec& operator+=(SignalVec &aFirstSignal, SignalVec const& aSecondSignal)
{
	aFirstSignal.addWith(aSecondSignal);
	return     aFirstSignal;
}

SignalVec& operator*=(SignalVec &aFirstSignal, SignalVec const& aSecondSignal)
{
	aFirstSignal.multiplyWith(aSecondSignal);
	return     aFirstSignal;
}

