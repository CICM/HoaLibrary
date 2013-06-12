//
//  BoidsManager.h
//  hoa.boids
//
//  Created by eliott PARIS on 11/06/13.
//
//

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
