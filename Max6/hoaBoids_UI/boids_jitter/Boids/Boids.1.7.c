#include	<ext.h>
#include	<ext_common.h>
#include	<stdlib.h>
#include	<math.h>


// constants
#define			kAssistInlet	1
#define			kAssistOutlet	2
#define			pi				(float) 3.1415927
#define			kMaxLong		0xFFFFFFFF
#define			kMaxNeighbors	4

// initial flight parameters
const short		kNumBoids		= 12;	// number of boids
const short		kNumNeighbors	= 2;	// must be <= kMaxNeighbors
const float 	kMinSpeed		= 15;	// boids' minimum speed
const float		kMaxSpeed		= 25;	// boids' maximum speed
const float		kCenterWeight	= 25;	// flock centering
const float		kAttractWeight	= 300;	// attraction point seeking
const float		kMatchWeight	= 100;	// neighbors velocity matching
const float		kAvoidWeight	= 10;	// neighbors avoidance
const float		kWallsWeight	= 500;	// wall avoidance [210]
const float		kEdgeDist		= 5;	// vision distance to avoid wall edges [5]
const float		kSpeedupFactor	= 100;	// alter animation speed
const float		kInertiaFactor	= 20;	// willingness to change speed & direction
const float		kAccelFactor	= 100;	// neighbor avoidance accelerate or decelerate rate
const long		kPrefDist		= 25;	// preferred distance from neighbors
const long		kFlyRectTop		= 0;	// fly rect boundaries
const long		kFlyRectLeft	= 0;	
const long		kFlyRectBottom	= 300;	
const long		kFlyRectRight	= 300;	


// typedefs
typedef struct Velocity {
	float		h;
	float		v;
} Velocity;

typedef struct FloatPt {
	float		h;
	float		v;
} FloatPt;

typedef struct Boid {
	Point		oldPos;
	FloatPt		fOldPos;
	Point		newPos;
	Velocity	oldDir;
	Velocity	newDir;
	float		speed;
	short		neighbor[kMaxNeighbors];
	long		neighborDistSqr[kMaxNeighbors];
} Boid, *BoidPtr;

typedef struct FlockObject {
	Object		theObject;
	void		*out1;
	short		numBoids;
	short		numNeighbors;
	Rect		flyRect;
	float 		minSpeed;
	float		maxSpeed;
	float		centerWeight;
	float		attractWeight;
	float		matchWeight;
	float		avoidWeight;
	float		wallsWeight;
	float		edgeDist;
	float		speedupFactor;
	float		inertiaFactor;
	float		accelFactor;
	long		prefDist;
	long		prefDistSqr;
	Point		centerPt;
	Point		attractPt;
	BoidPtr		boid;
} FlockObject, *FlockPtr;

// variables
fptr*	FNS;
void*	flock;

// prototypes
void main();
void* Flock_new(long numBoids);
void Flock_free(FlockPtr flockPtr);
void Flock_assist(FlockPtr flockPtr, void* temp, long letType, long letNum, char *assistStr);
void Flock_bang(FlockPtr flockPtr);
void Flock_dump(FlockPtr flockPtr);
void Flock_numNeighbors(FlockPtr flockPtr, long arg);
void Flock_minSpeed(FlockPtr flockPtr, long arg);
void Flock_maxSpeed(FlockPtr flockPtr, long arg);
void Flock_centerWeight(FlockPtr flockPtr, long arg);
void Flock_attractWeight(FlockPtr flockPtr, long arg);
void Flock_matchWeight(FlockPtr flockPtr, long arg);
void Flock_avoidWeight(FlockPtr flockPtr, long arg);
void Flock_wallsWeight(FlockPtr flockPtr, long arg);
void Flock_edgeDist(FlockPtr flockPtr, long arg);
void Flock_speedupFactor(FlockPtr flockPtr, long arg);
void Flock_inertiaFactor(FlockPtr flockPtr, long arg);
void Flock_accelFactor(FlockPtr flockPtr, long arg);
void Flock_prefDist(FlockPtr flockPtr, long arg);
void Flock_flyRect(FlockPtr flockPtr, long left, long top, long right, long bottom);
void Flock_attractPt(FlockPtr flockPtr, long h, long v);
void Flock_reset(FlockPtr flockPtr);
void InitFlock(FlockPtr flockPtr);
void FlightStep(FlockPtr flockPtr);
Point FindFlockCenter(FlockPtr flockPtr);
float MatchAndAvoidNeighbors(FlockPtr flockPtr, short theBoid, Velocity *matchNeighborVel, Velocity *avoidNeighborVel);
Velocity SeekPoint(FlockPtr flockPtr, short theBoid, Point seekPt);
Velocity AvoidWalls(FlockPtr flockPtr, short theBoid);
Boolean InFront(BoidPtr theBoid, BoidPtr neighbor);
void NormalizeVelocity(Velocity *direction);
unsigned short RandomInt(short maxRange);
long DistSqrToPt(Point firstPoint, Point secondPoint);


// routines

void main()
{
	short	i, numSegs, segID;
	/*Handle	resHdl;
	OSType	tempType;
	Str255	tempBuf;

	FNS = f;
	
	#ifndef powerc
	// copy additional segs of type SegX
	numSegs = Count1Resources('SegX');
	for (i = 1; i <= numSegs; i++) {
		resHdl = Get1IndResource('SegX', i);
		GetResInfo(resHdl, &segID, &tempType, tempBuf);
		rescopy('SegX',segID);
	}
	#endif
	*/
	setup((t_messlist **) &flock, (method) Flock_new, (method) Flock_free, (short) sizeof(FlockObject), 0L, A_LONG, 0);
	
	addmess((method) Flock_assist,"assist",	A_CANT, 0);

	addbang((method) Flock_bang);
	addmess((method) Flock_numNeighbors,"neighbors", A_LONG, 0);
	addmess((method) Flock_minSpeed,"minspeed", A_LONG, 0);
	addmess((method) Flock_maxSpeed,"maxspeed", A_LONG, 0);
	addmess((method) Flock_centerWeight,"center", A_LONG, 0);
	addmess((method) Flock_attractWeight,"attract", A_LONG, 0);
	addmess((method) Flock_matchWeight,"match", A_LONG, 0);
	addmess((method) Flock_avoidWeight,"avoid", A_LONG, 0);
	addmess((method) Flock_wallsWeight,"repel", A_LONG, 0);
	addmess((method) Flock_edgeDist,"edgedist", A_LONG, 0);
	addmess((method) Flock_speedupFactor,"speed", A_LONG, 0);
	addmess((method) Flock_inertiaFactor,"inertia", A_LONG, 0);
	addmess((method) Flock_accelFactor,"accel", A_LONG, 0);
	addmess((method) Flock_prefDist,"prefdist", A_LONG, 0);
	addmess((method) Flock_flyRect,"flyrect", A_LONG, A_LONG, A_LONG, A_LONG, 0);
	addmess((method) Flock_attractPt, "attractpt", A_LONG, A_LONG, 0);
	addmess((method) Flock_reset, "reset", 0);
	addmess((method) Flock_dump, "dump", 0);
	
	post("Boids 1.7 (OSX) © 1995-2003 Eric L. Singer (eric@ericsinger.com)");
	post("    Based on Simon Fraser's implementation");
	post("    of Craig Reynolds' Boids algorithm");
	post("    Boids is free for non-commercial use");
}


void* Flock_new(long numBoids)
{
	FlockPtr	flockPtr;
	
	flockPtr = (FlockPtr) newobject(flock);
	flockPtr->boid = (Boid *)sysmem_newptr(sizeof(Boid) * numBoids);
	  
	
	flockPtr->out1 = outlet_new(flockPtr, 0L);;
	flockPtr->numBoids = (short) numBoids;

	InitFlock(flockPtr);
		
	return(flockPtr);
}


void Flock_free(FlockPtr flockPtr)
{
	sysmem_freeptr(flockPtr->boid);
}


void Flock_assist(FlockPtr flockPtr, void* temp, long letType, long letNum, char *assistStr)
{
	switch (letType) {
		case kAssistInlet:
			switch (letNum) {
				case 0:
					sprintf(assistStr, "bangs & parameter messages");
					break;
			}
			break;
		
		case kAssistOutlet:
			switch (letNum) {
				case 0:
					sprintf(assistStr, "boid coordinates (x1, y1, x2, y2, ...)");
					break;
			}
			break;
	}
	}

void Flock_bang(FlockPtr flockPtr)
{
	short	i;
	
	FlightStep(flockPtr);

	for (i = 0; i < flockPtr->numBoids; i++) {
		outlet_int(flockPtr->out1, (long) flockPtr->boid[i].newPos.h);
		outlet_int(flockPtr->out1, (long) flockPtr->boid[i].newPos.v);
	}
}


void Flock_dump(FlockPtr flockPtr)
{
	Atom	outList[4];
	
	outList[0].a_type = A_LONG;
	outList[0].a_w.w_long = (long) flockPtr->numNeighbors;
	outlet_anything(flockPtr->out1, gensym("neighbors"), 1, outList);

	outList[0].a_type = A_LONG;
	outList[0].a_w.w_long = (long) flockPtr->minSpeed;
	outlet_anything(flockPtr->out1, gensym("minspeed"), 1, outList);

	outList[0].a_type = A_LONG;
	outList[0].a_w.w_long = (long) flockPtr->maxSpeed;
	outlet_anything(flockPtr->out1, gensym("maxspeed"), 1, outList);

	outList[0].a_type = A_LONG;
	outList[0].a_w.w_long = (long) flockPtr->centerWeight;
	outlet_anything(flockPtr->out1, gensym("center"), 1, outList);

	outList[0].a_type = A_LONG;
	outList[0].a_w.w_long = (long) flockPtr->attractWeight;
	outlet_anything(flockPtr->out1, gensym("attract"), 1, outList);

	outList[0].a_type = A_LONG;
	outList[0].a_w.w_long = (long) flockPtr->matchWeight;
	outlet_anything(flockPtr->out1, gensym("match"), 1, outList);

	outList[0].a_type = A_LONG;
	outList[0].a_w.w_long = (long) flockPtr->avoidWeight;
	outlet_anything(flockPtr->out1, gensym("avoid"), 1, outList);

	outList[0].a_type = A_LONG;
	outList[0].a_w.w_long = (long) flockPtr->wallsWeight;
	outlet_anything(flockPtr->out1, gensym("repel"), 1, outList);

	outList[0].a_type = A_LONG;
	outList[0].a_w.w_long = (long) flockPtr->edgeDist;
	outlet_anything(flockPtr->out1, gensym("edgedist"), 1, outList);

	outList[0].a_type = A_LONG;
	outList[0].a_w.w_long = (long) flockPtr->speedupFactor;
	outlet_anything(flockPtr->out1, gensym("speed"), 1, outList);

	outList[0].a_type = A_LONG;
	outList[0].a_w.w_long = (long) flockPtr->inertiaFactor;
	outlet_anything(flockPtr->out1, gensym("inertia"), 1, outList);

	outList[0].a_type = A_LONG;
	outList[0].a_w.w_long = (long) flockPtr->accelFactor;
	outlet_anything(flockPtr->out1, gensym("accel"), 1, outList);

	outList[0].a_type = A_LONG;
	outList[0].a_w.w_long = flockPtr->prefDist;
	outlet_anything(flockPtr->out1, gensym("prefdist"), 1, outList);

	outList[0].a_type = A_LONG;
	outList[0].a_w.w_long = (long) flockPtr->flyRect.left;
	outList[1].a_type = A_LONG;
	outList[1].a_w.w_long = (long) flockPtr->flyRect.top;
	outList[2].a_type = A_LONG;
	outList[2].a_w.w_long = (long) flockPtr->flyRect.right;
	outList[3].a_type = A_LONG;
	outList[3].a_w.w_long = (long) flockPtr->flyRect.bottom;
	outlet_anything(flockPtr->out1, gensym("flyrect"), 4, outList);

	outList[0].a_type = A_LONG;
	outList[0].a_w.w_long = (long) flockPtr->attractPt.h;
	outList[1].a_type = A_LONG;
	outList[1].a_w.w_long = (long) flockPtr->attractPt.v;
	outlet_anything(flockPtr->out1, gensym("attractpt"), 2, outList);
}


void Flock_numNeighbors(FlockPtr flockPtr, long arg)
{
	flockPtr->numNeighbors = arg;
}


void Flock_minSpeed(FlockPtr flockPtr, long arg)
{
	flockPtr->minSpeed = arg;
}


void Flock_maxSpeed(FlockPtr flockPtr, long arg)
{
	flockPtr->maxSpeed = arg;
}


void Flock_centerWeight(FlockPtr flockPtr, long arg)
{
	flockPtr->centerWeight = arg;
}


void Flock_attractWeight(FlockPtr flockPtr, long arg)
{
	flockPtr->attractWeight = arg;
}


void Flock_matchWeight(FlockPtr flockPtr, long arg)
{
	flockPtr->matchWeight = arg;
}


void Flock_avoidWeight(FlockPtr flockPtr, long arg)
{
	flockPtr->avoidWeight = arg;
}


void Flock_wallsWeight(FlockPtr flockPtr, long arg)
{
	flockPtr->wallsWeight = arg;
}


void Flock_edgeDist(FlockPtr flockPtr, long arg)
{
	flockPtr->edgeDist = arg;
}


void Flock_speedupFactor(FlockPtr flockPtr, long arg)
{
	flockPtr->speedupFactor = arg;
}


void Flock_inertiaFactor(FlockPtr flockPtr, long arg)
{
	flockPtr->inertiaFactor = arg;
}


void Flock_accelFactor(FlockPtr flockPtr, long arg)
{
	flockPtr->accelFactor = arg;
}


void Flock_prefDist(FlockPtr flockPtr, long arg)
{
	flockPtr->prefDist = arg;
}


void Flock_flyRect(FlockPtr flockPtr, long left, long top, long right, long bottom)
{
	flockPtr->flyRect.left = left;
	flockPtr->flyRect.top = top;
	flockPtr->flyRect.right = right;
	flockPtr->flyRect.bottom = bottom;
}


void Flock_attractPt(FlockPtr flockPtr, long h, long v)
{
	flockPtr->attractPt.h = h;
	flockPtr->attractPt.v = v;
}


void Flock_reset(FlockPtr flockPtr)
{
	InitFlock(flockPtr);
}


void InitFlock(FlockPtr flockPtr)
{
	short	i;
	float	rndAngle;

	flockPtr->numNeighbors		= kNumNeighbors;
	flockPtr->minSpeed			= kMinSpeed;
	flockPtr->maxSpeed			= kMaxSpeed;
	flockPtr->centerWeight		= kCenterWeight;
	flockPtr->attractWeight		= kAttractWeight;
	flockPtr->matchWeight		= kMatchWeight;
	flockPtr->avoidWeight		= kAvoidWeight;
	flockPtr->wallsWeight		= kWallsWeight;
	flockPtr->edgeDist			= kEdgeDist;
	flockPtr->speedupFactor		= kSpeedupFactor;
	flockPtr->inertiaFactor		= kInertiaFactor;
	flockPtr->accelFactor		= kAccelFactor;
	flockPtr->prefDist			= kPrefDist;
	flockPtr->prefDistSqr		= kPrefDist * kPrefDist;
	flockPtr->flyRect.top		= kFlyRectTop;
	flockPtr->flyRect.left		= kFlyRectLeft;
	flockPtr->flyRect.bottom	= kFlyRectBottom;
	flockPtr->flyRect.right		= kFlyRectRight;
	flockPtr->attractPt.h		= (kFlyRectLeft + kFlyRectRight) / 2;
	flockPtr->attractPt.v		= (kFlyRectTop + kFlyRectBottom) / 2;

	/* set the initial locations and velocities of the boids */
	for (i = 0; i <  flockPtr->numBoids; i++) {
		/* set random location within flyRect */
		flockPtr->boid[i].oldPos.h = flockPtr->flyRect.left + RandomInt(flockPtr->flyRect.right - flockPtr->flyRect.left);
		flockPtr->boid[i].oldPos.v = flockPtr->flyRect.top + RandomInt(flockPtr->flyRect.bottom - flockPtr->flyRect.top);

		/* set velocity from random angle */
		rndAngle = (float) RandomInt(360) * pi / (float) 180;
		flockPtr->boid[i].newDir.h = sin(rndAngle);
		flockPtr->boid[i].newDir.v = cos(rndAngle);

		/* set initial speed */
		flockPtr->boid[i].speed = (kMaxSpeed + kMinSpeed) / 2;

		/* store position as floats */
		flockPtr->boid[i].fOldPos.h = flockPtr->boid[i].oldPos.h;
		flockPtr->boid[i].fOldPos.v = flockPtr->boid[i].oldPos.v;
	}
}


void FlightStep(FlockPtr flockPtr)
{
	Velocity		goCenterVel;
	Velocity		goAttractVel;
	Velocity		matchNeighborVel;
	Velocity		avoidWallsVel;
	Velocity		avoidNeighborVel;
	float			avoidNeighborSpeed;
	const Velocity	zeroVel	= {0, 0};
	short			i;

	flockPtr->centerPt = FindFlockCenter(flockPtr);
	 	
	/* save position and velocity */
	for (i = 0; i <  flockPtr->numBoids; i++) {
		flockPtr->boid[i].oldPos = flockPtr->boid[i].newPos;
		flockPtr->boid[i].oldDir = flockPtr->boid[i].newDir;
	}

	for (i = 0; i < flockPtr->numBoids; i++) {
		/* get all velocity components */		
		if (flockPtr->numNeighbors > 0) {
			avoidNeighborSpeed = MatchAndAvoidNeighbors(flockPtr,
									i,
									&matchNeighborVel,
									&avoidNeighborVel);
		}
		else {
			matchNeighborVel = zeroVel;
			avoidNeighborVel = zeroVel;
			avoidNeighborSpeed = 0;
		}
		goCenterVel = SeekPoint(flockPtr, i, flockPtr->centerPt);			
		goAttractVel = SeekPoint(flockPtr, i, flockPtr->attractPt);
		avoidWallsVel = AvoidWalls(flockPtr, i);
	
		/* compute resultant velocity using weights and inertia */
		flockPtr->boid[i].newDir.h = flockPtr->inertiaFactor * (flockPtr->boid[i].oldDir.h) +
							(flockPtr->centerWeight * goCenterVel.h +
							 flockPtr->attractWeight * goAttractVel.h +
							 flockPtr->matchWeight * matchNeighborVel.h +
							 flockPtr->avoidWeight * avoidNeighborVel.h +
							 flockPtr->wallsWeight * avoidWallsVel.h) / flockPtr->inertiaFactor;
		flockPtr->boid[i].newDir.v = flockPtr->inertiaFactor * (flockPtr->boid[i].oldDir.v) +
							(flockPtr->centerWeight * goCenterVel.v +
							 flockPtr->attractWeight * goAttractVel.v +
							 flockPtr->matchWeight * matchNeighborVel.v +
							 flockPtr->avoidWeight * avoidNeighborVel.v +
							 flockPtr->wallsWeight * avoidWallsVel.v) / flockPtr->inertiaFactor;
		
		/* normalize velocity so its length is unity */
		NormalizeVelocity(&(flockPtr->boid[i].newDir));

		/* set to avoidNeighborSpeed bounded by minSpeed and maxSpeed */
		if ((avoidNeighborSpeed >= flockPtr->minSpeed) &&
				(avoidNeighborSpeed <= flockPtr->maxSpeed))
			flockPtr->boid[i].speed = avoidNeighborSpeed;
		else if (avoidNeighborSpeed > flockPtr->maxSpeed)
			flockPtr->boid[i].speed = flockPtr->maxSpeed;
		else
			flockPtr->boid[i].speed = flockPtr->minSpeed;

		/* calculate new position, applying speedupFactor */
		flockPtr->boid[i].fOldPos.h += flockPtr->boid[i].newDir.h * flockPtr->boid[i].speed * (flockPtr->speedupFactor / 100.0);
		flockPtr->boid[i].fOldPos.v += flockPtr->boid[i].newDir.v * flockPtr->boid[i].speed * (flockPtr->speedupFactor / 100.0);
			
		/* save as shorts to speed up calculations */
		// ELS: essentially fOldPos avoids rounding each time by
		// keeping a running float copy of the position
		flockPtr->boid[i].newPos.h = flockPtr->boid[i].fOldPos.h;
		flockPtr->boid[i].newPos.v = flockPtr->boid[i].fOldPos.v;
	}
}


Point FindFlockCenter(FlockPtr flockPtr)
{
	long			totalH = 0, totalV = 0;
	Point			centerPoint;
	register short	i;

	for (i = 0 ; i <  flockPtr->numBoids; i++)
	{
		totalH += flockPtr->boid[i].oldPos.h;
		totalV += flockPtr->boid[i].oldPos.v;
	}

	centerPoint.h = totalH / flockPtr->numBoids;
	centerPoint.v = totalV / flockPtr->numBoids;
		
	return(centerPoint);
}


float MatchAndAvoidNeighbors(FlockPtr flockPtr, short theBoid, Velocity *matchNeighborVel, Velocity *avoidNeighborVel)
{
	short			i, j, neighbor;
	unsigned long	distSqr;
	float			dist, distH, distV;
	float			tempSpeed;
	short			numClose = 0;
	Velocity		totalVel = {0,0};

	/**********************/
	/* Find the neighbors */	
	/**********************/

	/* special case of one neighbor */
	if (flockPtr->numNeighbors == 1) {
		flockPtr->boid[theBoid].neighborDistSqr[0] = kMaxLong;
	
		for (i = 0; i < flockPtr->numBoids; i++) {
			if (i != theBoid) {
				distSqr = DistSqrToPt(flockPtr->boid[theBoid].oldPos, flockPtr->boid[i].oldPos);
				
				/* if this one is closer than the closest so far, then remember it */
				if ((unsigned long)flockPtr->boid[theBoid].neighborDistSqr[0] > distSqr) {
					flockPtr->boid[theBoid].neighborDistSqr[0] = distSqr;
					flockPtr->boid[theBoid].neighbor[0] = i;
				}
			}
		}
	}
	/* more than one neighbor */
	else {
		for (j = 0; j < flockPtr->numNeighbors; j++)
			flockPtr->boid[theBoid].neighborDistSqr[j] = kMaxLong;
		
		for (i = 0 ; i < flockPtr->numBoids; i++) {
			/* if this one is not me... */
			if (i != theBoid) {
				distSqr = DistSqrToPt(flockPtr->boid[theBoid].oldPos, flockPtr->boid[i].oldPos);
	
				/* if distSqr is less than the distance at the bottom of the array, sort into array */
				if (distSqr < (unsigned long)flockPtr->boid[theBoid].neighborDistSqr[flockPtr->numNeighbors-1]) {
					j = flockPtr->numNeighbors - 1;
				
					/* sort distSqr in to keep array in size order, smallest first */
					while ((distSqr < (unsigned long)flockPtr->boid[theBoid].neighborDistSqr[j-1]) && (j > 0)) {
						flockPtr->boid[theBoid].neighborDistSqr[j] = flockPtr->boid[theBoid].neighborDistSqr[j - 1];
						flockPtr->boid[theBoid].neighbor[j] = flockPtr->boid[theBoid].neighbor[j - 1];
						j--;
					}
					flockPtr->boid[theBoid].neighborDistSqr[j] = distSqr;
					flockPtr->boid[theBoid].neighbor[j] = i;					
				}
			}
		}
	}

	/*********************************/
	/* Match and avoid the neighbors */	
	/*********************************/

	matchNeighborVel->h = 0;
	matchNeighborVel->v = 0;
	
	/* set tempSpeed to old speed */
	tempSpeed = flockPtr->boid[theBoid].speed;
	
	for (i = 0; i < flockPtr->numNeighbors; i++) {
		neighbor = flockPtr->boid[theBoid].neighbor[i];
		
		/* calculate matchNeighborVel by averaging the neighbor velocities */
		matchNeighborVel->h += flockPtr->boid[neighbor].oldDir.h;
		matchNeighborVel->v += flockPtr->boid[neighbor].oldDir.v;
			
		/* if distance is less than preferred distance, then neighbor influences boid */
		distSqr = flockPtr->boid[theBoid].neighborDistSqr[i];
		if (distSqr < (unsigned long)flockPtr->prefDistSqr) {
			dist = sqrt(distSqr);

			distH = flockPtr->boid[neighbor].oldPos.h - flockPtr->boid[theBoid].oldPos.h;
			distV = flockPtr->boid[neighbor].oldPos.v - flockPtr->boid[theBoid].oldPos.v;

			totalVel.h = totalVel.h - distH - (distH * ((float) flockPtr->prefDist / (dist + 1)));
			totalVel.v = totalVel.v - distV - (distV * ((float) flockPtr->prefDist / (dist + 1)));
		
			numClose++;
		}
		
		/* adjust speed */
		if (InFront(&(flockPtr->boid[theBoid]), &(flockPtr->boid[neighbor]))) {
			if (distSqr < (unsigned long)flockPtr->prefDistSqr) 
				tempSpeed /= (flockPtr->accelFactor / 100.0);
			else
				tempSpeed *= (flockPtr->accelFactor / 100.0);
		}
		else {
			if (distSqr < (unsigned long)flockPtr->prefDistSqr)
				tempSpeed *= (flockPtr->accelFactor / 100.0);
			else
				tempSpeed /= (flockPtr->accelFactor / 100.0);
		}
	}
	
	if (numClose) {
		avoidNeighborVel->h = totalVel.h / numClose;
		avoidNeighborVel->v = totalVel.v / numClose;
		NormalizeVelocity(matchNeighborVel);
	}
	else {
		avoidNeighborVel->h = 0;
		avoidNeighborVel->v = 0;
	}
	
	return(tempSpeed);
}


Velocity SeekPoint(FlockPtr flockPtr, short theBoid, Point seekPt)
{
	Velocity	tempDir;

	tempDir.h = seekPt.h - flockPtr->boid[theBoid].oldPos.h;	
	tempDir.v = seekPt.v - flockPtr->boid[theBoid].oldPos.v;
	
	NormalizeVelocity(&tempDir);
	return(tempDir);
}


Velocity AvoidWalls(FlockPtr flockPtr, short theBoid)
{
	Point		testPoint;
	Velocity	tempVel = {0, 0};
		
	/* calculate test point in front of the nose of the boid */
	/* distance depends on the boid's speed and the avoid edge constant */
	testPoint.h = flockPtr->boid[theBoid].oldPos.h + flockPtr->boid[theBoid].oldDir.h * flockPtr->boid[theBoid].speed * flockPtr->edgeDist;
	testPoint.v = flockPtr->boid[theBoid].oldPos.v + flockPtr->boid[theBoid].oldDir.v * flockPtr->boid[theBoid].speed * flockPtr->edgeDist;

	/* if test point is out of the left (right) side of flockPtr->flyRect, */
	/* return a positive (negative) horizontal velocity component */
	if (testPoint.h < flockPtr->flyRect.left)
		tempVel.h = fabs(flockPtr->boid[theBoid].oldDir.h);
	else if (testPoint.h > flockPtr->flyRect.right)
		tempVel.h = - fabs(flockPtr->boid[theBoid].oldDir.h);

	/* same with top and bottom */
	if (testPoint.v < flockPtr->flyRect.top)
		tempVel.v = fabs(flockPtr->boid[theBoid].oldDir.v);
	else if (testPoint.v > flockPtr->flyRect.bottom)
		tempVel.v = - fabs(flockPtr->boid[theBoid].oldDir.v);
	
	return(tempVel);
}


Boolean InFront(BoidPtr theBoid, BoidPtr neighbor)
{
	float	grad, intercept;
	
	/*
	Find the gradient and y-intercept of a line passing through theBoid's oldPos
	perpendicular to its direction of motion.  Another boid is in front of theBoid
	if it is to the right or left of this linedepending on whether theBoid is moving
	right or left.  However, if theBoid is travelling vertically then just compare
	their vertical coordinates.
	*/

	/* if theBoid is not travelling vertically... */
	if (theBoid->oldDir.h != 0) {
		/* calculate gradient of a line _perpendicular_ to its direction (hence the minus) */
		grad = -theBoid->oldDir.v / theBoid->oldDir.h;
		
		/* calculate where this line hits the y axis (from y = mx + c) */
		intercept = theBoid->oldPos.v - (grad * theBoid->oldPos.h);

		/* compare the horizontal position of the neighbor boid with */
		/* the point on the line that has its vertical coordinate */
		if (neighbor->oldPos.h >= ((neighbor->oldPos.v - intercept) / grad))
			/* return true if the first boid's horizontal movement is +ve */
			return (theBoid->oldDir.h > 0);
		else
			/* return true if the first boid's horizontal movement is +ve */
			return (theBoid->oldDir.h < 0);
	}
	/* else theBoid is travelling vertically, so just compare vertical coordinates */
	else if (theBoid->oldDir.v > 0) {
		return(neighbor->oldPos.v > theBoid->oldPos.v);
	}
	else {
		return(neighbor->oldPos.v < theBoid->oldPos.v);
	}
}


void NormalizeVelocity(Velocity *direction)
{
	float	hypot;
	
	hypot = sqrt(direction->h * direction->h + direction->v * direction->v);

	if (hypot != 0) {
		direction->h = direction->h / hypot;
		direction->v = direction->v / hypot;
	}
}


unsigned short RandomInt(short maxRange)
{
	unsigned short	qdRdm;
	long			t;
	
	qdRdm = rand();
	t = (qdRdm * maxRange) / 65536; 	// now 0 <= t <= range 
	return(t);
}


long DistSqrToPt(Point firstPoint, Point secondPoint)
{
	long	a, b;

	/* return the square of the distance between two points */
	a = firstPoint.h - secondPoint.h;
	b = firstPoint.v - secondPoint.v;	
	return(a * a + b * b);
}

