/*
// Copyright (c) 2012-2014 Eliott Paris, Julien Colafrancesco & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef DEF_HOA_2D_PROJECTOR
#define DEF_HOA_2D_PROJECTOR

#include "Ambisonic.h"
#include "Planewaves.h"
#include "Encoder.h"

namespace Hoa2D
{
    class Projector : public Ambisonic, public Planewaves
    {
        
    private:
        double*         m_projector_matrix;
        float*          m_projector_matrix_float;
		double*         m_harmonics_vector;
        Encoder*        m_encoder;
        
    public:
        
        /**	The projector constructor.
         @param     order					The order, must be at least 1.
		 @param     numberOfChannels	The number of channels, must be at least (order + 1)^2.
         */
		Projector(unsigned int order, unsigned int numberOfChannels);
		
        /**	The projector destructor.
         */
		~Projector();
        
		/**	This method performs the decoding with single precision.
         @param     input	The input sample.
         @param     outputs The output array that contains samples destinated to channels.
         */
		void process(const float* input, float* output);
		
		/**	This method performs the decoding with double precision.
         @param     input	The input sample.
         @param     outputs The output array that contains samples destinated to channels.
         */
		void process(const double* input, double* output);
    };
}


#endif


