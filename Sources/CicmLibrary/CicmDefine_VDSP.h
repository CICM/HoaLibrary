/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.re Guillot, CICM - Université Paris 8
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/HoaLibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * This file is part of HOA LIBRARY.
 *
 * HOA LIBRARY is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
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

#define	Cicm_Complex_Packed_Float_Malloc(packedComplex, size) packedComplex = (Cicm_Complex_Packed_Float *)malloc(sizeof(Cicm_Complex_Packed_Float)); packedComplex[0].realp = (cicm_vector_float)malloc(size * sizeof(float)); packedComplex[0].imagp = (cicm_vector_float)malloc(size * sizeof(float));

#define	Cicm_Complex_Packed_Double_Malloc(packedComplex, size) packedComplex = (Cicm_Complex_Packed_Double *)malloc(sizeof(Cicm_Complex_Packed_Double)); packedComplex[0].realp = (cicm_vector_double)malloc(size * sizeof(double)); packedComplex[0].imagp = (Cicm__Vector_Double *)malloc(size * sizeof(double));


#define cicm_free_Complex_Packed(vector) free(vector[0].realp); free(vector[0].imagp);

#define Cicm_fft_init_handle(order) vDSP_create_fftsetup(order, FFT_RADIX2)
#define	cicm_free_packed(pointeur) free(pointeur[0].realp) free(pointeur[0].imagp)

#define Cicm_fft_free_handle vDSP_destroy_fftsetup

#define Cicm_packed_mul(source1, source2, dest, length) vDSP_zvmul(source1, 1, source2, 1, dest, 1, length, 1)
#define Cicm_packed_clear(source, length) vDSP_vclr(source[0].imagp, 1, length); vDSP_vclr(source[0].realp, 1, length);

#define Cicm_fft_forward(fft_handle, complex, order) vDSP_fft_zrip(fft_handle, complex, 1, order, FFT_FORWARD)
#define Cicm_fft_inverse(fft_handle, complex, order) vDSP_fft_zrip(fft_handle, complex, 1, order, FFT_INVERSE)

#endif
