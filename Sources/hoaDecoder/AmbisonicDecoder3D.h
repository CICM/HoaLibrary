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

#ifndef DEF_AMBISONICDECODER3D
#define DEF_AMBISONICDECODER3D

#include "../hoaEncoder/AmbisonicEncoder3D.h"
#include "../HoaAmbisonics/Ambisonic3D.h"

class AmbisonicDecoder3D : public Ambisonic3D
{
	
private:
    Cicm_Matrix_Double   m_decoder_matrix;
    
    void computeMatrices();
public:
	AmbisonicDecoder3D(long anOrder = 1, long aNumberOfLoudspeakers = 0, long aVectorSize = 2, long aSamlingRate = 44100);

    void    setVectorSize(long aVectorSize);
    
	~AmbisonicDecoder3D();
    
    /************************************************************************************/
    /***************************** Perform sample by sample *****************************/
    /************************************************************************************/

    /*********************************** Out Of Place ***********************************/
    
    inline void process(float anInput, float* anOutput)
    {
       
    }
    
    inline void process(double anInput, double* anOutput)
    {
        
    }
    
    /************************************* In Place *************************************/

    
    inline void process(float* anInputOutput)
    {
       
    }
    
    inline void process(double* anInputOutput)
    {
        
    }
    
    /************************************************************************************/
    /******************************* Perform sample block *******************************/
    /************************************************************************************/
    
    /*********************************** Out Of Place ***********************************/
    
    inline void process(float* anInput, float** anOutput)
    {
        
    }
    
    inline void process(double* anInput, double** anOutput)
    {
        
    }
    
    /************************************* In Place *************************************/
    
       
    inline void process(float** anInputOutput)
    {
        
    }
    
    inline void process(double** anInputOutput)
    {
        
    }
};
#endif