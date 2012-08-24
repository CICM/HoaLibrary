
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


class ambisonicDecode{
	
private:
	int m_order;
	int m_numberOfComponents;
	int m_channelNumber;
	double m_fishEyeFactor;

	gsl_matrix* recompMicCoefs;
	gsl_vector* m_output_vec;
	
	double *spkrsAngles;
	int *m_harmonicsIndex;
	

	
public:
	ambisonicDecode(int channelNumber, int order);
	void SetFishEyeFactor(double aFishEyeFactor);
	void computeMicMatrix();
	double*  process(double* input);
	~ambisonicDecode()
	{
		gsl_matrix_free(recompMicCoefs);
		gsl_vector_free(m_output_vec);
		delete[] spkrsAngles;
		delete[] m_harmonicsIndex;
	}
};



#endif


