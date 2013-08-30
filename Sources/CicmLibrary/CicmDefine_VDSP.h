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
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef DEF_CICM_DEFINE_FFT
#define DEF_CICM_DEFINE_FFT

/************************************************************************************/
/************************************* FFT ******************************************/
/************************************************************************************/

#define Cicm_Complex_Float DSPComplex
#define Cicm_Complex_Packed_Float DSPSplitComplex

#define Cicm_Complex_Double DSPComplexD
#define Cicm_Complex_Packed_Double DSPSplitComplexD

#define Cicm_Fft_Handle FFTSetup

#define	Cicm_Complex_Packed_Float_Malloc(packedComplex, size) packedComplex = (Cicm_Complex_Packed_Float *)malloc(sizeof(Cicm_Complex_Packed_Float)); packedComplex[0].realp = (Cicm_Vector_Float)malloc(size * sizeof(Cicm_Float)); packedComplex[0].imagp = (Cicm_Vector_Float)malloc(size * sizeof(Cicm_Float));

#define	Cicm_Complex_Packed_Double_Malloc(packedComplex, size) packedComplex = (Cicm_Complex_Packed_Double *)malloc(sizeof(Cicm_Complex_Packed_Double)); packedComplex[0].realp = (Cicm_Vector_Double)malloc(size * sizeof(Cicm_Double)); packedComplex[0].imagp = (Cicm__Vector_Double *)malloc(size * sizeof(Cicm_Double));


#define cicm_free_Complex_Packed(vector) free(vector[0].realp); free(vector[0].imagp);

#define Cicm_fft_init_handle(order) vDSP_create_fftsetup(order, FFT_RADIX2)
#define	cicm_free_packed(pointeur) free(pointeur[0].realp) free(pointeur[0].imagp)

#define Cicm_fft_free_handle vDSP_destroy_fftsetup

#define Cicm_packed_mul(source1, source2, dest, length) vDSP_zvmul(source1, 1, source2, 1, dest, 1, length, 1)
#define Cicm_packed_clear(source, length) vDSP_vclr(source[0].imagp, 1, length); vDSP_vclr(source[0].realp, 1, length);

#define Cicm_fft_forward(fft_handle, complex, order) vDSP_fft_zrip(fft_handle, complex, 1, order, FFT_FORWARD)
#define Cicm_fft_inverse(fft_handle, complex, order) vDSP_fft_zrip(fft_handle, complex, 1, order, FFT_INVERSE)

#endif
