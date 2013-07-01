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

#ifndef __hoa_boids__BoidsManager__
#define __hoa_boids__BoidsManager__

#include "../CicmLibrary/CicmTools.h"
#include <iostream>
#include <vector.h>


class Bird {
public:
    double x, y, vx, vy;
    inline Bird() {;}
    //inline Bird(double _x, double _y, double _vx, double _vy) { x = _x; y = _y; vx = _vx; vy = _vy;}
    ~Bird() {;}
};

class BoidsManager {
    long   m_numberOfBoids;
    
    double m_centroid_x;
    double m_centroid_y;
    double m_avgvelocity_x;
    double m_avgvelocity_y;
    
    double m_separation;
    double m_alignment;
    double m_coherence;
    double m_inertia;
    double m_friction;
    double m_septhresh;
    double m_maxvel;
    double m_gravity;
    double m_gravpoint_x;
    double m_gravpoint_y;
    
    vector<Bird> m_birds;
    
        
    // initialize agents
    //double agents = new Array();
    //agentcount(20);
    
public:
    BoidsManager();
    ~BoidsManager();
    
    void update();
    void birdUpdate(int _index);
    void birdSeparate(int _index);
    void birdAlign(int _index);
    void birdCohere(int _index);
    void birdGravitate(int _index);
    
    void setNumberOfBoids(long _numberOfBoids);
    void setSeparation(double _separation);
    void setAlignment(double _alignment);
    void setCoherence(double _coherence);
    void setInertia(double _inertia);
    void setFriction(double _friction);
    void setSepThresh(double _septhresh);
    void setMaxVel(double _maxvel);
    void setGravity(double _gravity);
    void setGravPoint_x(double _gravPoint_x);
    void setGravPoint_y(double _gravPoint_y);
    void setGravPoint(double _gravPoint_x, double _gravPoint_y);
    
    inline long getNumberOfBoids() {return m_numberOfBoids;}
    inline double getSeparation() {return m_separation;}
    inline double getAlignment() {return m_alignment;}
    inline double getCoherence() {return m_coherence;}
    inline double getInertia() {return m_inertia;}
    inline double getFriction() {return m_friction;}
    inline double getSepThresh() {return m_septhresh;}
    inline double getMaxVel() {return m_maxvel;}
    inline double getGravity() {return m_gravity;}
    inline double getGravPoint_x() {return m_gravpoint_x;}
    inline double getGravPoint_y() {return m_gravpoint_y;}
    
    void getBirdCoord(long _index, double* _birdArrayCoord);
};

#endif /* defined(__hoa_boids__BoidsManager__) */
