//
//  BoidsManager.cpp
//  hoa.boids
//
//  Created by eliott PARIS on 11/06/13.
//
//

#include "BoidsManager.h"

BoidsManager::BoidsManager()
{
    m_numberOfBoids = 4;
    
    m_centroid_x = m_centroid_y = 0.;
    m_avgvelocity_x = m_avgvelocity_y = 0.;
    
    m_separation = 0.03;
    m_alignment = 0.05;
    m_coherence = 0.02;
    m_inertia = 0.5;
    m_friction = 0.5;
    m_septhresh = 0.1;
    m_maxvel = 0.05;
    m_gravity = 0.;
    m_gravpoint_x = m_gravpoint_y = 0.5;
    
    setNumberOfBoids(m_numberOfBoids);
}

BoidsManager::~BoidsManager()
{
    ;
}

void BoidsManager::setNumberOfBoids(long _numberOfBoids)
{
    // clip agentcount to range 1.-100.
	m_numberOfBoids = Tools::clip(_numberOfBoids, long(0), long(100));
    
    m_birds.resize(m_numberOfBoids);
    
	for (int i=0; i < m_numberOfBoids; i++)
	{
        // start with random position/velocity
        m_birds[i].x  = Tools::getRandd(-1., 1.);
        m_birds[i].y  = Tools::getRandd(-1., 1.);
        m_birds[i].vx = Tools::getRandd(-0.05, 0.05);
        m_birds[i].vy = Tools::getRandd(-0.05, 0.05);
	}
}

void BoidsManager::update()
{
	double cx, cy, cvx, cvy;
    cx = cy = cvx = cvy = 0.;
    
	for (int i=0; i < m_numberOfBoids; i++)
	{
        birdUpdate(i);
		//m_birds[i].tick();
		
		// calculate current frame's average position/velocity
		cx += m_birds[i].x;
		cy += m_birds[i].y;
		cvx += m_birds[i].vx;
		cvy += m_birds[i].vy;
	}
    
	m_centroid_x = cx/m_numberOfBoids;
	m_centroid_y = cy/m_numberOfBoids;
	m_avgvelocity_x = cvx/m_numberOfBoids;
	m_avgvelocity_y = cvy/m_numberOfBoids;
	
	//outlet(2,"bang");
	//outlet(1, m_centroid_x, m_centroid_y, m_avgvelocity_x, m_avgvelocity_y);
	
    /*
	for (int i=0; i<m_numberOfBoids; i++) {
		outlet(0,m_birds[i].x,m_birds[i].y, m_birds[i].vx,m_birds[i].vy);
	}
    */
}

void BoidsManager::birdUpdate(int _index)
{
    if (!Tools::isInside(_index, int(0), int(m_birds.size()))) return;
    Bird* a = &m_birds[_index];
	double px, py;
	
	// save current velocity for inertia calc
	px = a->vx;
	py = a->vy;
    
    birdSeparate(_index);
    birdAlign(_index);
    birdCohere(_index);
    birdGravitate(_index);
	
	// inertia
	a->vx = px*m_inertia + a->vx*(1.-m_inertia);
	a->vy = py*m_inertia + a->vy*(1.-m_inertia);
	
	// velocity limit
	a->vx = Tools::clip(a->vx,-m_maxvel,m_maxvel);
	a->vy = Tools::clip(a->vy,-m_maxvel,m_maxvel);
    
	// update position based on velocity and friction
	a->x += a->vx*(1.-m_friction);
	a->y += a->vy*(1.-m_friction);
    
	//wrap(this); // torus space	
}

// rules

void BoidsManager::birdSeparate(int _index)
{
    if (!Tools::isInside(_index, int(0), int(m_birds.size()))) return;
    Bird* a = &m_birds[_index];
    
	double dx,dy,proxscale, mag;
	
	// run from positions of neighbors
	for (int i=0; i < m_numberOfBoids; i++)
	{
		if (i != _index)
		{
			dx = m_birds[i].x - a->x;
			dy = m_birds[i].y - a->y;
			
            /*
			//torus space
			if (dx>0.5) dx -= 1.;
			else if (dx<-0.5) dx += 1.;
			//torus space
			if (dy>0.5) dy -= 1.;
			else if (dy<-0.5) dy += 1.;
            */
			
			if ((fabs(dx) > 0.0001) && (fabs(dy) > 0.0001))
				mag = (dx*dx+dy*dy); // cheap mag, no sqrt
			else
				mag = 0.01;
			
			if (mag < m_septhresh) {
				if (mag < 0.0001)
					proxscale = 8;
				else
					proxscale = Tools::clip(m_septhresh/(m_septhresh-(m_septhresh-mag)), 0.,8.);
				a->vx -= dx*m_separation*proxscale;
				a->vy -= dy*m_separation*proxscale;
			}
		}
	}
}

void BoidsManager::birdAlign(int _index)
{
    if (!Tools::isInside(_index, int(0), int(m_birds.size()))) return;
    Bird* a = &m_birds[_index];
	double dvx,dvy;
	
	// conform to velocities towards average velocity
	dvx = m_avgvelocity_x - a->vx;
	dvy = m_avgvelocity_y - a->vy;
    
	a->vx += dvx*m_alignment;
	a->vy += dvy*m_alignment;
}

void BoidsManager::birdCohere(int _index)
{
    if (!Tools::isInside(_index, int(0), int(m_birds.size()))) return;
    Bird* a = &m_birds[_index];
	double dx,dy;
    
	// move towards center of mass
	dx = m_centroid_x - a->x;
	dy = m_centroid_y - a->y;
	
	a->vx += dx*m_coherence;
	a->vy += dy*m_coherence;
}

void BoidsManager::birdGravitate(int _index)
{
    if (!Tools::isInside(_index, int(0), int(m_birds.size()))) return;
    Bird* a = &m_birds[_index];
	double dx,dy;
    
	// move towards center
	dx = m_gravpoint_x - a->x;
	dy = m_gravpoint_y - a->y;
	
	a->vx += dx*m_gravity;
	a->vy += dy*m_gravity;
}

void BoidsManager::setSeparation(double _separation)
{
    m_separation = Tools::clip(_separation,0.,1.)*0.1;
}

void BoidsManager::setAlignment(double _alignment)
{
    m_alignment = Tools::clip(_alignment,0.,1.)*0.1;
}

void BoidsManager::setCoherence(double _coherence)
{
    m_coherence = Tools::clip(_coherence,0.,1.)*0.1;
}

void BoidsManager::setFriction(double _friction)
{
    m_friction = Tools::clip(_friction,0.,1.);
}

void BoidsManager::setInertia(double _inertia)
{
    m_inertia = Tools::clip(_inertia,0.,1.);
}

void BoidsManager::setSepThresh(double _septhresh)
{
    m_septhresh = Tools::clip(_septhresh,0.,1.)*0.5;
}

void BoidsManager::setMaxVel(double _maxvel)
{
    m_maxvel = Tools::clip(_maxvel,0.,1.)*0.1;
}

void BoidsManager::setGravity(double _gravity)
{
    m_gravity = Tools::clip(_gravity,-1.,1.)*0.1;
}

void BoidsManager::setGravPoint_x(double _gravPoint_x)
{
    //m_gravpoint_x = Tools::clip(_gravPoint_x,0.,1.);
    m_gravpoint_x = _gravPoint_x;
}

void BoidsManager::setGravPoint_y(double _gravPoint_y)
{
    //m_gravpoint_y = Tools::clip(_gravPoint_y,0.,1.);
    m_gravpoint_y = _gravPoint_y;
}

void BoidsManager::setGravPoint(double _gravPoint_x, double _gravPoint_y)
{
    setGravPoint_x(_gravPoint_x);
    setGravPoint_y(_gravPoint_y);
}

// GETTERS :

void BoidsManager::getBirdCoord(long _index, double* _birdArrayCoord)
{
    _birdArrayCoord[0] = _birdArrayCoord[1] = NULL;
    if (Tools::isInside(_index, long(0), long(m_birds.size())))
    {
        _birdArrayCoord[0] = m_birds.at(_index).x;
        _birdArrayCoord[1] = m_birds.at(_index).y;
    }
}

