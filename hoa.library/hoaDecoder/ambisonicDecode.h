
/*
 *  ambisonicDecode.h
 *  signalVec
 *
 *  Created by julien colafrancesco on 02/02/12.
 *  Copyright 2012 Ircam. All rights reserved.
 *
 */

#ifndef define DEF_AMBISONICDECODE
#define DEF_AMBISONICDECODE

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

#include <stdio.h>
#include <iostream>
#include <math.h>
#include "gslMatrix.h"
#include <gsl/gsl_sf.h>
#include <vector>
#include <string>


class ambisonicDecode
{
	
private:
	int m_order;
	int m_number_of_harmonics;
	int m_number_of_inputs;
	int m_number_of_outputs;
	int	m_sampling_rate;
	int	m_vector_size;
	std::string m_optimMode;
	
	double		*m_speakers_angles;
	int			*m_index_of_harmonics;
	
	gsl_matrix	*m_decoder_matrix;
	gsl_vector	*m_output_vector;
	gsl_vector	*m_optimVector;
	
public:
	ambisonicDecode(int anOrder, int aSamplingRate, int aVectorSize, int aNumberOfChannels = 0, std::string anOptimMode = "basic");
	
	int	 getParameters(std::string aParameter) const;
	void computeIndex();
	void computeAngles();
	
	void setOptimMode(std::string anOptim);
	void computeBasicOptim();
	void computeReOptim();
	void computeInPhaseOptim();
	
	void computePseudoInverse();
	void setSpkrsAngles(double* someSpkrsAngles, int size);
	double*  process(double* input);
	~ambisonicDecode();
};



#endif


