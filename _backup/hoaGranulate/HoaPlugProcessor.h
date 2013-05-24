/*
 *
 * Copyright (C) 2012 Julien Colafrancesco, Pierre Guillot & Eliott Paris, Universite Paris 8
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

#ifndef __hoa_granulate___HoaPlugProcessor__
#define __hoa_granulate___HoaPlugProcessor__

#include "../cicmTools.h"

class HoaPlugProcessor
{
public:
    enum Modes {
        NO = 0,
        PRE,
        POST,
        OUT
    };

private :
    // variables
    Modes       m_mode;
    long        m_vector_size;
    long        m_sampling_rate;
    long        m_order;
	long        m_number_of_harmonics;
	long        m_number_of_outputs;
	long        m_number_of_inputs;
    
    // methods
    void setupIO();
    
public:
    HoaPlugProcessor(long _order = 0, Modes _mode = NO, long _vectorSize = 0, long _samplingRate = 0);
    virtual ~HoaPlugProcessor();
    
    // setters :
    void setOrder(const long _order, bool _doSetupIO = true);
    void setMode(const Modes _mode, bool _doSetupIO = true);
    void setVectorSize(const long _vectorSize);
    void setSamplingRate(const long _samplingRate);
    
    virtual void IOChangeCallback() = 0;
    
    // getters :
    inline long  getOrder() {return m_order;}
    inline long  getVectorSize() {return m_vector_size;}
    inline long  getSamplingRate() {return m_sampling_rate;}
    inline long  getNumberOfInputs() {return m_number_of_inputs;}
    inline long  getNumberOfOutputs() {return m_number_of_outputs;}
    inline long  getNumberOfHarmonics() {return m_number_of_harmonics;}
    inline Modes getMode() {return m_mode;}
};


#endif /* defined(__hoa_granulate___HoaPlugProcessor__) */
