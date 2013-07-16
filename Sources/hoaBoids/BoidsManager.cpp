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

#include "BoidsManager.h"

BoidsManager::BoidsManager()
{
    m_numBoids = 4;
    m_boids.resize(m_numBoids);
    
    m_d2r = CICM_PI/180.0;
    m_r2d = 180.0/CICM_PI;
    
    initFlock();
    setNumberOfBoids(m_numBoids);
}

BoidsManager::~BoidsManager()
{
    ;
}

void BoidsManager::initFlock()
{
    m_numNeighbors		= kNumNeighbors;
	m_minSpeed			= kMinSpeed;
	m_maxSpeed			= kMaxSpeed;
	m_centerWeight		= kCenterWeight;
	m_attractWeight		= kAttractWeight;
	m_matchWeight		= kMatchWeight;
	m_avoidWeight		= kAvoidWeight;
	m_wallsWeight		= kWallsWeight;
	m_edgeDist			= kEdgeDist;
	m_speedupFactor		= kSpeedupFactor;
	m_inertiaFactor		= kInertiaFactor;
	m_accelFactor		= kAccelFactor;
	m_prefDist			= kPrefDist;
	m_prefDistSqr		= kPrefDist * kPrefDist;
	m_flyRect.top		= kFlyRectTop;
	m_flyRect.left		= kFlyRectLeft;
	m_flyRect.bottom	= kFlyRectBottom;
	m_flyRect.right		= kFlyRectRight;
	m_attractPt.x		= (kFlyRectLeft + kFlyRectRight) * 0.5;
	m_attractPt.y		= (kFlyRectTop + kFlyRectBottom) * 0.5;
    
	resetBoids();
}

void BoidsManager::update() // FlightStep();
{
	Velocity		goCenterVel;
	Velocity		goAttractVel;
	Velocity		matchNeighborVel;
	Velocity		avoidWallsVel;
	Velocity		avoidNeighborVel;
	float			avoidNeighborSpeed;
	const Velocity	zeroVel	= {0.0, 0.0};
	short			i;
    
	m_centerPt = FindFlockCenter();
    
    // save position and velocity
	for (i = 0; i <  m_numBoids; i++)
    {
		m_boids[i].oldPos.x = m_boids[i].newPos.x;
		m_boids[i].oldPos.y = m_boids[i].newPos.y;
		
		m_boids[i].oldDir.x = m_boids[i].newDir.x;
		m_boids[i].oldDir.y = m_boids[i].newDir.y;
	}
    
	for (i = 0; i < m_numBoids; i++)
    {
        // get all velocity components
		if (m_numNeighbors > 0)
        {
			avoidNeighborSpeed = MatchAndAvoidNeighbors(i,&matchNeighborVel, &avoidNeighborVel);
		}
        else
        {
			matchNeighborVel = zeroVel;
			avoidNeighborVel = zeroVel;
			avoidNeighborSpeed = 0;
		}
        
		goCenterVel = SeekPoint(i, m_centerPt);
		goAttractVel = SeekPoint(i, m_attractPt);
		avoidWallsVel = AvoidWalls(i);
        
		// compute resultant velocity using weights and inertia
		m_boids[i].newDir.x = m_inertiaFactor * (m_boids[i].oldDir.x) +
        (m_centerWeight * goCenterVel.x +
         m_attractWeight * goAttractVel.x +
         m_matchWeight * matchNeighborVel.x +
         m_avoidWeight * avoidNeighborVel.x +
         m_wallsWeight * avoidWallsVel.x) / m_inertiaFactor;
		m_boids[i].newDir.y = m_inertiaFactor * (m_boids[i].oldDir.y) +
        (m_centerWeight * goCenterVel.y +
         m_attractWeight * goAttractVel.y +
         m_matchWeight * matchNeighborVel.y +
         m_avoidWeight * avoidNeighborVel.y +
         m_wallsWeight * avoidWallsVel.y) / m_inertiaFactor;

        // normalize velocity so its length is unity
		NormalizeVelocity(&(m_boids[i].newDir));
        
		// set to avoidNeighborSpeed bounded by minSpeed and maxSpeed
		if ((avoidNeighborSpeed >= m_minSpeed) &&
            (avoidNeighborSpeed <= m_maxSpeed))
			m_boids[i].speed = avoidNeighborSpeed;
		else if (avoidNeighborSpeed > m_maxSpeed)
			m_boids[i].speed = m_maxSpeed;
		else
			m_boids[i].speed = m_minSpeed;
        
		// calculate new position, applying speedupFactor
        m_boids[i].newPos.x += m_boids[i].newDir.x * m_boids[i].speed * m_speedupFactor;
		m_boids[i].newPos.y += m_boids[i].newDir.y * m_boids[i].speed * m_speedupFactor;
        /*
		m_boids[i].newPos.x += m_boids[i].newDir.x * m_boids[i].speed * (m_speedupFactor / 100.0);
		m_boids[i].newPos.y += m_boids[i].newDir.y * m_boids[i].speed * (m_speedupFactor / 100.0);
        */
	}
}

Point2d BoidsManager::FindFlockCenter()
{
	double			totalH = 0, totalV = 0;
	Point2d			centerPoint;
	register short	i;
    
	for (i = 0 ; i < m_numBoids; i++)
	{
		totalH += m_boids[i].oldPos.x;
		totalV += m_boids[i].oldPos.y;
	}
    
	centerPoint.x = (double) (totalH / m_numBoids);
	centerPoint.y = (double) (totalV / m_numBoids);
    
	return(centerPoint);
}

float BoidsManager::MatchAndAvoidNeighbors(short theBoid, Velocity *matchNeighborVel, Velocity *avoidNeighborVel)
{
	short			i, j, neighbor;
	double			distSqr;
	double			dist, distH, distV;
	double			tempSpeed;
	short			numClose = 0;
	Velocity		totalVel = {0.0,0.0};
    
	/**********************/
	/* Find the neighbors */
	/**********************/
    
	/* special case of one neighbor */
	if (m_numNeighbors == 1) {
		m_boids[theBoid].neighborDistSqr[0] = kMaxLong;
        
		for (i = 0; i < m_numBoids; i++)
        {
			if (i != theBoid)
            {
				distSqr = DistSqrToPt(m_boids[theBoid].oldPos, m_boids[i].oldPos);
				
				/* if this one is closer than the closest so far, then remember it */
				if (m_boids[theBoid].neighborDistSqr[0] > distSqr)
                {
					m_boids[theBoid].neighborDistSqr[0] = distSqr;
					m_boids[theBoid].neighbor[0] = i;
				}
			}
		}
	}
	/* more than one neighbor */
	else
    {
		for (j = 0; j < m_numNeighbors; j++)
			m_boids[theBoid].neighborDistSqr[j] = kMaxLong;
		
		for (i = 0 ; i < m_numBoids; i++)
        {
			/* if this one is not me... */
			if (i != theBoid)
            {
				distSqr = DistSqrToPt(m_boids[theBoid].oldPos, m_boids[i].oldPos);
                
				/* if distSqr is less than the distance at the bottom of the array, sort into array */
				if (distSqr < m_boids[theBoid].neighborDistSqr[m_numNeighbors-1])
                {
					j = m_numNeighbors - 1;
                    
					/* sort distSqr in to keep array in size order, smallest first */
					while ((distSqr < m_boids[theBoid].neighborDistSqr[j-1]) && (j > 0))
                    {
						m_boids[theBoid].neighborDistSqr[j] = m_boids[theBoid].neighborDistSqr[j - 1];
						m_boids[theBoid].neighbor[j] = m_boids[theBoid].neighbor[j - 1];
						j--;
					}
					m_boids[theBoid].neighborDistSqr[j] = distSqr;
					m_boids[theBoid].neighbor[j] = i;
				}
			}
		}
	}
    
	/*********************************/
	/* Match and avoid the neighbors */
	/*********************************/
    
	matchNeighborVel->x = 0;
	matchNeighborVel->y = 0;
	
	// set tempSpeed to old speed
	tempSpeed = m_boids[theBoid].speed;
	
	for (i = 0; i < m_numNeighbors; i++) {
		neighbor = m_boids[theBoid].neighbor[i];
		
		// calculate matchNeighborVel by averaging the neighbor velocities
		matchNeighborVel->x += m_boids[neighbor].oldDir.x;
		matchNeighborVel->y += m_boids[neighbor].oldDir.y;
        
		// if distance is less than preferred distance, then neighbor influences boid
		distSqr = m_boids[theBoid].neighborDistSqr[i];
		if (distSqr < m_prefDistSqr)
        {
			dist = sqrt(distSqr);
            
			distH = m_boids[neighbor].oldPos.x - m_boids[theBoid].oldPos.x;
			distV = m_boids[neighbor].oldPos.y - m_boids[theBoid].oldPos.y;
			
			if(dist == 0.0) dist = 0.0000001;
			totalVel.x = totalVel.x - distH - (distH * ((float) m_prefDist / (dist)));
			totalVel.y = totalVel.y - distV - (distV * ((float) m_prefDist / (dist)));
            
			numClose++;
		}
        
        // adjust speed
		if (InFront(&(m_boids[theBoid]), &(m_boids[neighbor])))
        {
			if (distSqr < m_prefDistSqr)
				tempSpeed /= (m_accelFactor / 100.0);
			else
				tempSpeed *= (m_accelFactor / 100.0);
		}
		else
        {
			if (distSqr < m_prefDistSqr)
				tempSpeed *= (m_accelFactor / 100.0);
			else
				tempSpeed /= (m_accelFactor / 100.0);
		}
	}
	if (numClose)
    {
		avoidNeighborVel->x = totalVel.x / numClose;
		avoidNeighborVel->y = totalVel.y / numClose;
		NormalizeVelocity(matchNeighborVel);
	}
	else {
		avoidNeighborVel->x = 0;
		avoidNeighborVel->y = 0;
	}
	return(tempSpeed);
}


Velocity BoidsManager::SeekPoint(short theBoid, Point2d seekPt)
{
	Velocity	tempDir;
	tempDir.x = seekPt.x - m_boids[theBoid].oldPos.x;
	tempDir.y = seekPt.y - m_boids[theBoid].oldPos.y;
	NormalizeVelocity(&tempDir);
	return(tempDir);
}


Velocity BoidsManager::AvoidWalls(short theBoid)
{
	Point2d		testPoint;
	Velocity	tempVel = {0.0, 0.0};
    
	/* calculate test point in front of the nose of the boid */
	/* distance depends on the boid's speed and the avoid edge constant */
	testPoint.x = m_boids[theBoid].oldPos.x + m_boids[theBoid].oldDir.x * m_boids[theBoid].speed * m_edgeDist;
	testPoint.y = m_boids[theBoid].oldPos.y + m_boids[theBoid].oldDir.y * m_boids[theBoid].speed * m_edgeDist;
    
	/* if test point is out of the left (right) side of m_flyRect, */
	/* return a positive (negative) horizontal velocity component */
	if (testPoint.x < m_flyRect.left)
		tempVel.x = fabs(m_boids[theBoid].oldDir.x);
	else if (testPoint.x > m_flyRect.right)
		tempVel.x = - fabs(m_boids[theBoid].oldDir.x);
    
	/* same with top and bottom */
	if (testPoint.y < m_flyRect.top)
		tempVel.y = fabs(m_boids[theBoid].oldDir.y);
	else if (testPoint.y > m_flyRect.bottom)
		tempVel.y = - fabs(m_boids[theBoid].oldDir.y);
	
	return(tempVel);
}

Boolean BoidsManager::InFront(Boid* theBoid, Boid* neighbor)
{
	double	grad, intercept;
	Boolean result;
	
    /*
     Find the gradient and y-intercept of a line passing through theBoid's oldPos
     perpendicular to its direction of motion.  Another boid is in front of theBoid
     if it is to the right or left of this linedepending on whether theBoid is moving
     right or left.  However, if theBoid is travelling vertically then just compare
     their vertical coordinates.
     */
    
	// xy plane
	
	// if theBoid is not travelling vertically...
	if (theBoid->oldDir.x != 0)
    {
		// calculate gradient of a line _perpendicular_ to its direction (hence the minus)
		grad = -theBoid->oldDir.y / theBoid->oldDir.x;
        if(grad == 0.0) grad = 0.00001;
		
		// calculate where this line hits the y axis (from y = mx + c)
		intercept = theBoid->oldPos.y - (grad * theBoid->oldPos.x);
        
		/* compare the horizontal position of the neighbor boid with */
		/* the point on the line that has its vertical coordinate */
		if (neighbor->oldPos.x >= ((neighbor->oldPos.y - intercept) / grad))
        {
			/* return true if the first boid's horizontal movement is +ve */
			result = (theBoid->oldDir.x > 0);
            
			if (result==0) return 0;
			else goto next;
			
		} else
        {
			/* return true if the first boid's horizontal movement is +ve */
			result = (theBoid->oldDir.x < 0);
			if (result==0) return 0;
			else goto next;
		}
	}
	/* else theBoid is travelling vertically, so just compare vertical coordinates */
	else if (theBoid->oldDir.y > 0) {
		result = (neighbor->oldPos.y > theBoid->oldPos.y);
		if ( result == 0 ) return 0;
        else goto next;
	}
    else
    {
		result = (neighbor->oldPos.y < theBoid->oldPos.y);
		if ( result == 0 ) return 0;
        else goto next;
	}
next:
	return 1;
}

void BoidsManager::NormalizeVelocity(Velocity *direction)
{
	float	hypot;
	
	hypot = sqrt(direction->x * direction->x + direction->y * direction->y);
    
	if (hypot != 0.0)
    {
		direction->x = direction->x / hypot;
		direction->y = direction->y / hypot;
	}
}

double BoidsManager::DistSqrToPt(Point2d firstPoint, Point2d secondPoint)
{
	double	a, b;
	a = firstPoint.x - secondPoint.x;
	b = firstPoint.y - secondPoint.y;
	return(a * a + b * b);
}




void BoidsManager::boid_set_pos(long index, double posX, double posY)
{
    if (!Tools::isInside(index, long(0), m_numBoids-1)) return;
    
    // set ith boid to place
    m_boids[index].oldPos.x = m_boids[index].newPos.x = posX;
    m_boids[index].oldPos.y = m_boids[index].newPos.y = posY;
}


void BoidsManager::boid_set_dir(long index, double dirX, double dirY)
{
    if (!Tools::isInside(index, long(0), m_numBoids-1)) return;
    
    // set ith boid to place
    m_boids[index].oldDir.x = m_boids[index].newDir.x = dirX;
    m_boids[index].oldDir.y = m_boids[index].newDir.y = dirY;
}

void BoidsManager::boid_set_speed(long index, double speed)
{
    if (!Tools::isInside(index, long(0), m_numBoids-1)) return;
    
    m_boids[index].speed = speed;
}

void BoidsManager::boid_set_speedinv(long index)
{
    if (!Tools::isInside(index, long(0), m_numBoids-1)) return;
    
    m_boids[index].speed *= -1;
}


void BoidsManager::resetBoids()
{
    long i, j;
	double rndAngle;
	
    // init everything to 0.0
	for (i = 0; i <  m_boids.size(); i++)
    {
		m_boids[i].oldPos.x = 0.0;
		m_boids[i].oldPos.y = 0.0;
        
		m_boids[i].newPos.x = 0.0;
		m_boids[i].newPos.y = 0.0;
		
		m_boids[i].oldDir.x = 0.0;
		m_boids[i].oldDir.y = 0.0;
		
		m_boids[i].newDir.x = 0.0;
		m_boids[i].newDir.y = 0.0;
		
		m_boids[i].speed = 0.0;
		
		for(j=0; j < MAX_NEIGHBORS;j++)
        {
			m_boids[i].neighbor[j] = 0;
			m_boids[i].neighborDistSqr[j] = 0.0;
		}
	}
    
    // set the initial locations and velocities of the boids
	for (i = 0; i <  m_boids.size(); i++)
    {
        // set random location within flyRect
		m_boids[i].newPos.x = m_boids[i].oldPos.x = Tools::getRand(m_flyRect.right,m_flyRect.left);
		m_boids[i].newPos.y = m_boids[i].oldPos.y = Tools::getRand(m_flyRect.bottom, m_flyRect.top);
        
        // set velocity from random angle
		rndAngle = Tools::getRand(0, 360) * m_d2r;
		m_boids[i].newDir.x = sin(rndAngle);
		m_boids[i].newDir.y = cos(rndAngle);
		m_boids[i].speed = (kMaxSpeed + kMinSpeed) * 0.5;
	}
}

void BoidsManager::setNumberOfBoids(long _numberOfBoids)
{
    _numberOfBoids = Tools::clip_min(_numberOfBoids, long(2));
    
    if (_numberOfBoids != m_numBoids)
    {
        long lastNumOfBoids = m_boids.size();
        m_numBoids = _numberOfBoids;
        m_boids.resize(m_numBoids);
        if ( m_numBoids > lastNumOfBoids ) {
            for (int i = lastNumOfBoids; i < m_numBoids; i++)
            {
                // start with random position/velocity
                m_boids[i].newPos.x  = Tools::getRandd(m_attractPt.x - 1., m_attractPt.x + 1.);
                m_boids[i].newPos.y  = Tools::getRandd(m_attractPt.y - 1., m_attractPt.y + 1.);
                m_boids[i].newDir.x = Tools::getRandd(-0.05, 0.05);
                m_boids[i].newDir.y = Tools::getRandd(-0.05, 0.05);
            }
        }
    }
}

void BoidsManager::setNumberOfNeighbors(long _numberOfNeighbors)
{
    m_numNeighbors = Tools::clip(_numberOfNeighbors, 1, MAX_NEIGHBORS);
}

void BoidsManager::setFlyRect(double topLeft_X, double topLeft_Y, double bottomRight_X, double bottomRight_Y)
{
    m_flyRect.left = topLeft_X;
    m_flyRect.right = bottomRight_X;
    m_flyRect.top = bottomRight_Y;
    m_flyRect.bottom = topLeft_Y;
}

void BoidsManager::setMinSpeed(double _minSpeed)
{
    m_minSpeed = Tools::clip_min(_minSpeed, 0.000001);
}

void BoidsManager::setMaxSpeed(double _maxSpeed)
{
    m_maxSpeed = Tools::clip_min(_maxSpeed, m_minSpeed);
}

void BoidsManager::setCenterWeight(double _centerWeight)
{
    m_centerWeight = Tools::clip(_centerWeight, 0., 1.);
}

void BoidsManager::setAttractWeight(double _attractWeight)
{
    m_attractWeight = Tools::clip(_attractWeight, 0., 1.);
}

void BoidsManager::setMatchWeight(double _matchWeight)
{
    m_matchWeight = Tools::clip_min(_matchWeight, 0.);
}

void BoidsManager::setAvoidWeight(double _avoidWeight)
{
    m_avoidWeight = Tools::clip(_avoidWeight, 0., 1.);
}

void BoidsManager::setWallsWeight(double _wallWeight)
{
    m_wallsWeight = Tools::clip_min(_wallWeight, 0.);
}

void BoidsManager::setEdgeDistance(double _edgeDistance)
{
    m_edgeDist = Tools::clip_min(_edgeDistance, 0.);
}

void BoidsManager::setSpeedupFactor(double _speedupFactor)
{
    m_speedupFactor = Tools::clip(_speedupFactor, 0., 1.);
}

void BoidsManager::setInertiaFactor(double _inertiaFactor)
{
    m_inertiaFactor = Tools::clip_min(_inertiaFactor, 0.000001);
}

void BoidsManager::setAccelFactor(double _accelFactor)
{
    m_accelFactor = Tools::clip_min(_accelFactor, 0.000001);
}

void BoidsManager::setPrefDistance(double _prefDistance)
{
    m_prefDist = Tools::clip_min(_prefDistance, 0.);
    m_prefDistSqr = m_prefDist * m_prefDist;
}

void BoidsManager::setPrefDistanceSqr(double _prefDistanceSqr)
{
    m_prefDistSqr = _prefDistanceSqr;
}

void BoidsManager::setCenterPt(double _center_X, double _center_Y)
{
    m_centerPt.x = _center_X;
    m_centerPt.y = _center_Y;
}

void BoidsManager::setAttractPt(double _attract_X, double _attract_Y)
{
    m_attractPt.x = _attract_X;//Tools::clip(_mode, 0, 2);
    m_attractPt.y = _attract_Y;
}

// GETTERS :

int BoidsManager::getBoidPosCoord(long _index, double* _BoidArrayCoord)
{
    _BoidArrayCoord[0] = _BoidArrayCoord[1] = NULL;
    if (Tools::isInside(_index, long(0), long(m_boids.size())))
    {
        _BoidArrayCoord[0] = m_boids.at(_index).newPos.x;
        _BoidArrayCoord[1] = m_boids.at(_index).newPos.y;
        return 1;
    }
    return 0; // bad index
}

int BoidsManager::getBoidDirCoord(long _index, double* _BoidArrayCoord)
{
    _BoidArrayCoord[0] = _BoidArrayCoord[1] = NULL;
    if (Tools::isInside(_index, long(0), long(m_boids.size())))
    {
        _BoidArrayCoord[0] = m_boids.at(_index).newDir.x;
        _BoidArrayCoord[1] = m_boids.at(_index).newDir.y;
        return 1;
    }
    return 0; // bad index
}

