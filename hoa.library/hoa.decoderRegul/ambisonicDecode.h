
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
#include <vector>


class ambisonicDecode{
	
private:
	int m_order;
	int m_numberOfComponents;
	int m_channelNumber;	
	double *spkrsAngles;
	gsl_vector_view input_vec;
	gsl_matrix* m_regularizedDecod_mat;
	gsl_vector* m_output_vec;
	

public:
	
	ambisonicDecode(int channelNumber, int order);
	//std::vector<ouble>* process();
//	void record(double harmonic, int index);
	double*  process(double* input);

};



#endif


