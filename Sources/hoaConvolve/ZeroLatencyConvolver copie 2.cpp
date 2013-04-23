/*
 *
 * Copyright (C) 2012 Pierre Guillot, Universite Paris 8
 * 
 * This library is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Library General Public License as published 
 * by the Free Software Foundation; either version 2 of the License.
 * 
 * This library is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public 
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License 
 * along with this library; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#include "ZeroLatencyConvolver.h"

ZeroLatencyConvolver::ZeroLatencyConvolver() 
{
    m_fir       = new FirFilter(128);
    m_fft_128   = new FftConvolution(128, 2);
    m_fft_256   = new FftConvolution(256, 2);
    m_fft_512   = new FftConvolution(512, 2);
    m_fft_1024  = new FftConvolution(1024, 2);
    m_fft_2048  = new FftConvolution(2048, 2);
    m_fft_4096  = new FftConvolution(4096, 2);
    m_fft_8192  = new FftConvolution(8192, 2);
    m_fft_16384 = new FftConvolution(16384, 2);
    m_number_of_convolutions = 0;
}

void ZeroLatencyConvolver::setImpulseResponse(float* anImpulseResponse, long aSize)
{
    int responseSize = 0;
     m_number_of_convolutions = 0;
    if(aSize > 0)
    {
        Cicm_Signal* impulseResponse;
        if(aSize < 128) // FIR //
        {
            responseSize = 128;
            m_number_of_convolutions = 1;
            Cicm_signal_malloc(impulseResponse, responseSize);
            for(int i = 0; i < responseSize; i++)
            {
                if(i < aSize)
                    impulseResponse[i] = anImpulseResponse[i];
                else
                    impulseResponse[i] = 0.;
            }
            m_fir->setImpulseResponse(impulseResponse);
        }
        else if(aSize < 384) // FFT 128 //
        {
            responseSize = 384;
            m_number_of_convolutions = 3;
            Cicm_signal_malloc(impulseResponse, responseSize - 128);
            for(int i = 128; i < responseSize - 128; i++)
            {
                if(i < aSize)
                    impulseResponse[i-128] = anImpulseResponse[i];
                else
                    impulseResponse[i-128] = 0.;
            }
            m_fir->setImpulseResponse(anImpulseResponse);
            m_fft_128->loadImpulseResponse(impulseResponse);
        }
        else if(aSize < 896) // FFT 256 //
        {
            responseSize = 896;
            m_number_of_convolutions = 5;
            Cicm_signal_malloc(impulseResponse, responseSize - 384);
            for(int i = 384; i < responseSize - 384; i++)
            {
                if(i < aSize)
                    impulseResponse[i-384] = anImpulseResponse[i];
                else
                    impulseResponse[i-384] = 0.;
            }
            m_fir->setImpulseResponse(anImpulseResponse);
            m_fft_128->loadImpulseResponse(anImpulseResponse+128);
            m_fft_256->loadImpulseResponse(impulseResponse);
        }
        else if(aSize < 1920) // FFT 512 //
        {
            responseSize = 1920;
            m_number_of_convolutions = 7;
            Cicm_signal_malloc(impulseResponse, responseSize - 896);
            for(int i = 896; i < responseSize - 896; i++)
            {
                if(i < aSize)
                    impulseResponse[i-896] = anImpulseResponse[i];
                else
                    impulseResponse[i-896] = 0.;
            }
            m_fir->setImpulseResponse(anImpulseResponse);
            m_fft_128->loadImpulseResponse(anImpulseResponse+128);
            m_fft_256->loadImpulseResponse(anImpulseResponse+384);
            m_fft_512->loadImpulseResponse(impulseResponse);
        }
        else if(aSize < 3968) // FFT 1024 //
        {
            responseSize = 3968;
            m_number_of_convolutions = 9;
            Cicm_signal_malloc(impulseResponse, responseSize - 1920);
            for(int i = 1920; i < responseSize - 1920; i++)
            {
                if(i < aSize)
                    impulseResponse[i-1920] = anImpulseResponse[i];
                else
                    impulseResponse[i-1920] = 0.;
            }
            m_fir->setImpulseResponse(anImpulseResponse);
            m_fft_128->loadImpulseResponse(anImpulseResponse+128);
            m_fft_256->loadImpulseResponse(anImpulseResponse+284);
            m_fft_512->loadImpulseResponse(anImpulseResponse+896);
            m_fft_1024->loadImpulseResponse(impulseResponse);
        }
        else if(aSize < 8064) // FFT 2048 //
        {
            responseSize = 8064;
            m_number_of_convolutions = 11;
            Cicm_signal_malloc(impulseResponse, responseSize - 3968);
            for(int i = 3968; i < responseSize - 3968; i++)
            {
                if(i < aSize)
                    impulseResponse[i-3968] = anImpulseResponse[i];
                else
                    impulseResponse[i-3968] = 0.;
            }
            m_fir->setImpulseResponse(anImpulseResponse);
            m_fft_128->loadImpulseResponse(anImpulseResponse+128);
            m_fft_256->loadImpulseResponse(anImpulseResponse+284);
            m_fft_512->loadImpulseResponse(anImpulseResponse+896);
            m_fft_1024->loadImpulseResponse(anImpulseResponse+1920);
            m_fft_2048->loadImpulseResponse(impulseResponse);
        }
        else if(aSize < 16256) // FFT 4096 //
        {
            responseSize = 16256;
            m_number_of_convolutions = 13;
            Cicm_signal_malloc(impulseResponse, responseSize - 8064);
            for(int i = 8064; i < responseSize - 8064; i++)
            {
                if(i < aSize)
                    impulseResponse[i-8064] = anImpulseResponse[i];
                else
                    impulseResponse[i-8064] = 0.;
            }
            m_fir->setImpulseResponse(anImpulseResponse);
            m_fft_128->loadImpulseResponse(anImpulseResponse+128);
            m_fft_256->loadImpulseResponse(anImpulseResponse+284);
            m_fft_512->loadImpulseResponse(anImpulseResponse+896);
            m_fft_1024->loadImpulseResponse(anImpulseResponse+1920);
            m_fft_2048->loadImpulseResponse(anImpulseResponse+3968);
            m_fft_4096->loadImpulseResponse(impulseResponse);
        }
        else if(aSize < 32640) // FFT 8192 //
        {
            responseSize = 32640;
            m_number_of_convolutions = 15;
            Cicm_signal_malloc(impulseResponse, responseSize - 16256);
            for(int i = 16256; i < responseSize - 16256; i++)
            {
                if(i < aSize)
                    impulseResponse[i-16256] = anImpulseResponse[i];
                else
                    impulseResponse[i-16256] = 0.;
            }
            m_fir->setImpulseResponse(anImpulseResponse);
            m_fft_128->loadImpulseResponse(anImpulseResponse+128);
            m_fft_256->loadImpulseResponse(anImpulseResponse+284);
            m_fft_512->loadImpulseResponse(anImpulseResponse+896);
            m_fft_1024->loadImpulseResponse(anImpulseResponse+1920);
            m_fft_2048->loadImpulseResponse(anImpulseResponse+3968);
            m_fft_4096->loadImpulseResponse(anImpulseResponse+8064);
            m_fft_8192->loadImpulseResponse(impulseResponse);
        }
        else
        {
            responseSize = 32640;
            m_number_of_convolutions = 15;
            while(responseSize < aSize)
            {
                responseSize += 16384;
                m_number_of_convolutions++;
            }
            if(m_fft_16384->getNumberOfInstances() != m_number_of_convolutions - 15)
            {
                delete m_fft_16384;
                m_fft_16384 = new FftConvolution(16384, m_number_of_convolutions - 15);
            }
            Cicm_signal_malloc(impulseResponse, responseSize - 32640);
            
            for(int i = 32640; i < responseSize - 32640; i++)
            {
                if(i < aSize)
                    impulseResponse[i-32640] = anImpulseResponse[i];
                else
                    impulseResponse[i-32640] = 0.;
            }
            m_fir->setImpulseResponse(anImpulseResponse);
            m_fft_128->loadImpulseResponse(anImpulseResponse+128);
            m_fft_256->loadImpulseResponse(anImpulseResponse+284);
            m_fft_512->loadImpulseResponse(anImpulseResponse+896);
            m_fft_1024->loadImpulseResponse(anImpulseResponse+1920);
            m_fft_2048->loadImpulseResponse(anImpulseResponse+3968);
            m_fft_4096->loadImpulseResponse(anImpulseResponse+8064);
            m_fft_8192->loadImpulseResponse(anImpulseResponse+16256);
            m_fft_16384->loadImpulseResponse(impulseResponse);
        }
        
        Cicm_free(impulseResponse);
    }
}

ZeroLatencyConvolver::~ZeroLatencyConvolver()
{
	delete m_fir;
	delete m_fft_128;
    delete m_fft_256;
    delete m_fft_512;
    delete m_fft_1024;
    delete m_fft_2048;
    delete m_fft_4096;
    delete m_fft_8192;
    delete m_fft_16384;
}
