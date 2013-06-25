/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DEF_AMBISONICSVECTOR
#define DEF_AMBISONICSVECTOR

#include "../HoaAmbisonics/Planewaves.h"

class Ambisonicsvector : public Planewaves
{	
private:
    bool         m_mode;
    
public:
	Ambisonicsvector(long aNumberOfLoudspeakers = 1., bool aMode = Hoa_Polar, long aVectorSize = 0);
	
    std::string  getVectorName(long anIndex);
    long getMode();
    void setMode(bool aMode);
    
	~Ambisonicsvector();
	
	/* Perform sample by sample */
	void process(double* anInput, double *anOutput)
	{
        double sum = 0., weihtedSumAbscissa = 0, weihtedSumOrdinate = 0,  sumAbs = 0.,weihtedSumAbsAbscissa = 0, weihtedSumAbsOrdinate = 0;
        for (int i = 0; i < m_number_of_loudspeakers; i++)
        {
            sum += anInput[i];
            sumAbs += fabs(anInput[i]) * fabs(anInput[i]);
            weihtedSumAbscissa += anInput[i] * m_abscissa_of_loudspeakers[i];
            weihtedSumOrdinate += anInput[i] * m_ordinate_of_loudspeakers[i];
            weihtedSumAbsAbscissa += fabs(anInput[i]) * fabs(anInput[i]) * m_abscissa_of_loudspeakers[i];
            weihtedSumAbsOrdinate += fabs(anInput[i]) * fabs(anInput[i]) * m_ordinate_of_loudspeakers[i];
        }
        if(sum != 0.)
        {
            weihtedSumAbscissa /= sum;
            weihtedSumOrdinate /= sum;
            if(!m_mode)
            {
                anOutput[0] = Tools::radius(weihtedSumAbscissa, weihtedSumOrdinate);
                anOutput[1] = Tools::angle(weihtedSumAbscissa, weihtedSumOrdinate);
            }
            else
            {
                anOutput[0] = weihtedSumAbscissa;
                anOutput[1] = weihtedSumOrdinate;
            }
        }
        else
        {
            anOutput[0] = 0.;
            anOutput[1] = 0.;
        }
        if(sumAbs != 0.)
        {
            weihtedSumAbsAbscissa /= sumAbs;
            weihtedSumAbsOrdinate /= sumAbs;
            if(!m_mode)
            {
                anOutput[2] = Tools::radius(weihtedSumAbsAbscissa, weihtedSumAbsOrdinate);
                anOutput[3]= Tools::angle(weihtedSumAbsAbscissa, weihtedSumAbsOrdinate);
            }
            else
            {
                anOutput[2] = weihtedSumAbsAbscissa;
                anOutput[3] = weihtedSumAbsOrdinate;
            }
        }
        else
        {
            anOutput[2] = 0.;
            anOutput[3] = 0.;
        }
	}
    
    void process(float* anInput, float *anOutput)
	{
        double sum = 0., weihtedSumAbscissa = 0, weihtedSumOrdinate = 0,  sumAbs = 0.,weihtedSumAbsAbscissa = 0, weihtedSumAbsOrdinate = 0;
        for (int i = 0; i < m_number_of_loudspeakers; i++)
        {
            sum += anInput[i];
            sumAbs += fabs(anInput[i]) * fabs(anInput[i]);
            weihtedSumAbscissa += anInput[i] * m_abscissa_of_loudspeakers[i];
            weihtedSumOrdinate += anInput[i] * m_ordinate_of_loudspeakers[i];
            weihtedSumAbsAbscissa += fabs(anInput[i]) * fabs(anInput[i]) * m_abscissa_of_loudspeakers[i];
            weihtedSumAbsOrdinate += fabs(anInput[i]) * fabs(anInput[i]) * m_ordinate_of_loudspeakers[i];
        }
        if(sum != 0.)
        {
            weihtedSumAbscissa /= sum;
            weihtedSumOrdinate /= sum;
            if(!m_mode)
            {
                anOutput[0] = Tools::radius(weihtedSumAbscissa, weihtedSumOrdinate);
                anOutput[1] = Tools::angle(weihtedSumAbscissa, weihtedSumOrdinate);
            }
            else
            {
                anOutput[0] = weihtedSumAbscissa;
                anOutput[1] = weihtedSumOrdinate;
            }
        }
        else
        {
            anOutput[0] = 0.;
            anOutput[1] = 0.;
        }
        if(sumAbs != 0.)
        {
            weihtedSumAbsAbscissa /= sumAbs;
            weihtedSumAbsOrdinate /= sumAbs;
            if(!m_mode)
            {
                anOutput[2] = Tools::radius(weihtedSumAbsAbscissa, weihtedSumAbsOrdinate);
                anOutput[3]= Tools::angle(weihtedSumAbsAbscissa, weihtedSumAbsOrdinate);
            }
            else
            {
                anOutput[2] = weihtedSumAbsAbscissa;
                anOutput[3] = weihtedSumAbsOrdinate;
            }
        }
        else
        {
            anOutput[2] = 0.;
            anOutput[3] = 0.;
        }

	}
	
	/* Perform sample block */
	void process(double** anInputVector, double** anOutputVector)
	{
        for(int j = 0; j < m_vector_size; j++)
		{
            double sum = 0., weihtedSumAbscissa = 0, weihtedSumOrdinate = 0,  sumAbs = 0.,weihtedSumAbsAbscissa = 0, weihtedSumAbsOrdinate = 0;
            for (int i = 0; i < m_number_of_loudspeakers; i++)
            {
                sum += anInputVector[i][j];
                sumAbs += fabs(anInputVector[i][j]) * fabs(anInputVector[i][j]);
                weihtedSumAbscissa += anInputVector[i][j] * m_abscissa_of_loudspeakers[i];
                weihtedSumOrdinate += anInputVector[i][j] * m_ordinate_of_loudspeakers[i];
                weihtedSumAbsAbscissa += fabs(anInputVector[i][j]) * fabs(anInputVector[i][j]) * m_abscissa_of_loudspeakers[i];
                weihtedSumAbsOrdinate += fabs(anInputVector[i][j]) * fabs(anInputVector[i][j]) * m_ordinate_of_loudspeakers[i];
            }
            if(sum != 0.)
            {
                weihtedSumAbscissa /= sum;
                weihtedSumOrdinate /= sum;
                if(!m_mode)
                {
                    anOutputVector[0][j] = Tools::radius(weihtedSumAbscissa, weihtedSumOrdinate);
                    anOutputVector[1][j] = Tools::angle(weihtedSumAbscissa, weihtedSumOrdinate);
                }
                else
                {
                    anOutputVector[0][j] = weihtedSumAbscissa;
                    anOutputVector[1][j] = weihtedSumOrdinate;
                }
            }
            else
            {
                anOutputVector[0][j] = 0.;
                anOutputVector[1][j] = 0.;
            }
            if(sumAbs != 0.)
            {
                weihtedSumAbsAbscissa /= sumAbs;
                weihtedSumAbsOrdinate /= sumAbs;
                if(!m_mode)
                {
                    anOutputVector[2][j] = Tools::radius(weihtedSumAbsAbscissa, weihtedSumAbsOrdinate);
                    anOutputVector[3][j] = Tools::angle(weihtedSumAbsAbscissa, weihtedSumAbsOrdinate);
                }
                else
                {
                    anOutputVector[2][j] = weihtedSumAbsAbscissa;
                    anOutputVector[3][j] = weihtedSumAbsOrdinate;
                }
            }
            else
            {
                anOutputVector[2][j] = 0.;
                anOutputVector[3][j] = 0.;
            }            
		}
	}
    
    void process(float** anInputVector, float** anOutputVector)
	{
        for(int j = 0; j < m_vector_size; j++)
		{
            double sum = 0., weihtedSumAbscissa = 0, weihtedSumOrdinate = 0,  sumAbs = 0.,weihtedSumAbsAbscissa = 0, weihtedSumAbsOrdinate = 0;
            for (int i = 0; i < m_number_of_loudspeakers; i++)
            {
                sum += anInputVector[i][j];
                sumAbs += fabs(anInputVector[i][j]) * fabs(anInputVector[i][j]);
                weihtedSumAbscissa += anInputVector[i][j] * m_abscissa_of_loudspeakers[i];
                weihtedSumOrdinate += anInputVector[i][j] * m_ordinate_of_loudspeakers[i];
                weihtedSumAbsAbscissa += fabs(anInputVector[i][j]) * fabs(anInputVector[i][j]) * m_abscissa_of_loudspeakers[i];
                weihtedSumAbsOrdinate += fabs(anInputVector[i][j]) * fabs(anInputVector[i][j]) * m_ordinate_of_loudspeakers[i];
            }
            if(sum != 0.)
            {
                weihtedSumAbscissa /= sum;
                weihtedSumOrdinate /= sum;
                if(!m_mode)
                {
                    anOutputVector[0][j] = Tools::radius(weihtedSumAbscissa, weihtedSumOrdinate);
                    anOutputVector[1][j] = Tools::angle(weihtedSumAbscissa, weihtedSumOrdinate);
                }
                else
                {
                    anOutputVector[0][j] = weihtedSumAbscissa;
                    anOutputVector[1][j] = weihtedSumOrdinate;
                }
            }
            else
            {
                anOutputVector[0][j] = 0.;
                anOutputVector[1][j] = 0.;
            }
            if(sumAbs != 0.)
            {
                weihtedSumAbsAbscissa /= sumAbs;
                weihtedSumAbsOrdinate /= sumAbs;
                if(!m_mode)
                {
                    anOutputVector[2][j] = Tools::radius(weihtedSumAbsAbscissa, weihtedSumAbsOrdinate);
                    anOutputVector[3][j] = Tools::angle(weihtedSumAbsAbscissa, weihtedSumAbsOrdinate);
                }
                else
                {
                    anOutputVector[2][j] = weihtedSumAbsAbscissa;
                    anOutputVector[3][j] = weihtedSumAbsOrdinate;
                }
            }
            else
            {
                anOutputVector[2][j] = 0.;
                anOutputVector[3][j] = 0.;
            }
		}
	}
	
};

#endif