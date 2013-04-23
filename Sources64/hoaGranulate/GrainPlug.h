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

#ifndef __hoa_granulate___GrainPlug__
#define __hoa_granulate___GrainPlug__

#include "HoaPlugProcessor.h"
#include "genlib_common.h"

class GrainPlug : public HoaPlugProcessor
{
public:
    GrainPlug(const long _order = 0, const double _grainsize = 100, const double _delay = 1000, const double _feedback = 0, const double _rarefaction = 0);
    ~GrainPlug();
    
    void setGrainSize(double _grainSize);
    void setDelay(double _delay);
    void setFeedback(double _feedback);
    void setRarefaction(double _rarefaction);
    
    void IOChangeCallback();
    
private:
    double m_grainSize;
    double m_delay;
    double m_feedback;
    double m_rarefaction;
};

#endif /* defined(__hoa_granulate___GrainPlug__) */
