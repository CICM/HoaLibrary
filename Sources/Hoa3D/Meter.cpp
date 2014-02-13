/*
// Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Meter.h"

namespace Hoa3D
{
    Meter::Meter(unsigned int numberOfChannels) : Planewaves(numberOfChannels)
    {
        ;
    }
    
    void Meter::process(const float* inputs)
    {
    }
    
    void Meter::process(const double* inputs)
    {
    }
    
    Meter::~Meter()
    {
    }
}

