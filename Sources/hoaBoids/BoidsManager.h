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

#include "../../Sources/CicmLibrary/CicmTools.h"
#include <iostream>
#include <vector.h>


// initial flight parameters
const short			kNumBoids		= 12;	// number of boids
const short			kNumNeighbors	= 2;	// must be <= kMaxNeighbors
const double 		kMinSpeed		= 0.15;	// boids' minimum speed
const double		kMaxSpeed		= 0.25;	// boids' maximum speed
const double		kCenterWeight	= 0.25;	// bflock centering
const double		kAttractWeight	= 0.300;// attraction point seeking
const double		kMatchWeight	= 0.100;// neighbors velocity matching
const double		kAvoidWeight	= 0.10;	// neighbors avoidance
//const double		kWallsWeight	= 0.500;// wall avoidance [210]
const double		kWallsWeight	= 10000;// wall avoidance [210]
const double		kEdgeDist		= 0.;	// vision distance to avoid wall edges [5]
const double		kSpeedupFactor	= 0.100;// alter animation speed
const double		kInertiaFactor	= 0.20;	// willingness to change speed & direction
const double		kAccelFactor	= 0.100;// neighbor avoidance accelerate or decelerate rate
const double		kPrefDist		= 0.25;	// preferred distance from neighbors
const double		kFlyRectTop		= 1.0;	// fly rect boundaries
const double		kFlyRectLeft	= -1.0;
const double		kFlyRectBottom	= -1.0;
const double		kFlyRectRight	= 1.0;


#define	MAX_NEIGHBORS 4
#define	kMaxLong 0xFFFFFFFF

// typedefs
typedef struct Velocity {
	double		x;
	double		y;
} Velocity;

typedef struct Point2d {
	double		x;
	double		y;
} Point2d;

typedef struct Box2D {
	double		left, right;
	double		top, bottom;
} Box2D;

class Boid {
public:
    inline Boid() {;}
    //inline Boid(double _x, double _y, double _vx, double _vy) { x = _x; y = _y; vx = _vx; vy = _vy;}
    ~Boid() {;}
    Point2d		oldPos;
	Point2d		newPos;
	Velocity	oldDir;
	Velocity	newDir;
	double		speed;
	short		neighbor[MAX_NEIGHBORS]; //kMaxNeighbors
	double		neighborDistSqr[MAX_NEIGHBORS]; //kMaxNeighbors
};

class BoidsManager {
	long		    m_numBoids;
	long		    m_numNeighbors;
	Box2D		    m_flyRect;
	double 		    m_minSpeed;
	double		    m_maxSpeed;
	double		    m_centerWeight;
	double		    m_attractWeight;
	double		    m_matchWeight;
	double		    m_avoidWeight;
	double		    m_wallsWeight;
	double		    m_edgeDist;
	double		    m_speedupFactor;
	double		    m_inertiaFactor;
	double		    m_accelFactor;
	double		    m_prefDist;
	double		    m_prefDistSqr;
	Point2d		    m_centerPt;
	Point2d		    m_attractPt;
    vector<Boid>    m_boids;
	double 		    m_d2r, m_r2d;
    
public:
    BoidsManager();
    ~BoidsManager();
    
    void initFlock();
    void resetBoids();
    void update();
    Point2d FindFlockCenter();
    float MatchAndAvoidNeighbors(short theBoid, Velocity *matchNeighborVel, Velocity *avoidNeighborVel);
    Velocity SeekPoint(short theBoid, Point2d seekPt);
    Velocity AvoidWalls(short theBoid);
    double DistSqrToPt(Point2d firstPoint, Point2d secondPoint);
    void NormalizeVelocity(Velocity *direction);
    Boolean InFront(Boid* theBoid, Boid* neighbor);
    
    void boid_set_pos(long index, double posX, double posY);
    void boid_set_dir(long index, double dirX, double dirY);
    void boid_set_speed(long index, double speed);
    void boid_set_speedinv(long index);
    
    void setNumberOfBoids(long _numberOfBoids);
    void setNumberOfNeighbors(long _numberOfNeighbors);
    void setFlyRect(double left, double right, double top, double bottom);
    void setMinSpeed(double _minSpeed);
    void setMaxSpeed(double _maxSpeed);
    void setCenterWeight(double _centerWeight);
    void setAttractWeight(double _attractWeight);
    void setMatchWeight(double _matchWeight);
    void setAvoidWeight(double _avoidWeight);
    void setWallsWeight(double _wallWeight);
    void setEdgeDistance(double _edgeDistance);
    void setSpeedupFactor(double _speedupFactor);
    void setInertiaFactor(double _inertiaFactor);
    void setAccelFactor(double _accelFactor);
    void setPrefDistance(double _prefDistance);
    void setPrefDistanceSqr(double _prefDistanceSqr);
    void setCenterPt(double _center_X, double _center_Y);
    void setAttractPt(double _attract_X, double _attract_Y);
    
    inline long   getNumberOfBoids()        {return m_numBoids;}
    inline long   getNumberOfNeighbors()    {return m_numNeighbors;}
    inline double getFlyRect_Left()         {return m_flyRect.left;}
    inline double getFlyRect_Right()        {return m_flyRect.right;}
    inline double getFlyRect_Top()          {return m_flyRect.top;}
    inline double getFlyRect_Bottom()       {return m_flyRect.bottom;}
    inline double getMinSpeed()             {return m_minSpeed;}
    inline double getMaxSpeed()             {return m_maxSpeed;}
    inline double getCenterWeight()         {return m_centerWeight;}
    inline double getAttractWeight()        {return m_attractWeight;}
    inline double getMatchWeight()          {return m_matchWeight;}
    inline double getAvoidWeight()          {return m_avoidWeight;}
    inline double getWallsWeight()           {return m_wallsWeight;}
    inline double getEdgeDistance()         {return m_edgeDist;}
    inline double getSpeedupFactor()        {return m_speedupFactor;}
    inline double getInertiaFactor()        {return m_inertiaFactor;}
    inline double getAccelFactor()          {return m_accelFactor;}
    inline double getPrefDistance()         {return m_prefDist;}
    inline double getPrefDistanceSqr()      {return m_prefDistSqr;}
    inline double getCenterPt_abscissa()    {return m_centerPt.x;}
    inline double getCenterPt_ordinate()    {return m_centerPt.y;}
    inline double getAttractPt_abscissa()   {return m_attractPt.x;}
    inline double getAttractPt_ordinate()   {return m_attractPt.y;}
    
    int getBoidPosCoord(long _index, double* _BoidArrayCoord);
    int getBoidDirCoord(long _index, double* _BoidArrayCoord);
    int getFlockCenterCoord(long _index, double* _BoidArrayCoord);
};

#endif /* defined(__hoa_boids__BoidsManager__) */
