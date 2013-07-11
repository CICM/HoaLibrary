/*

	boids2d 08/2005 a.sier / jasch adapted from boids by eric singer © 1995-2003 eric l. singer
	free for non-commercial use
*/

#include	<ext.h>
#include	<ext_common.h>
#include	<stdlib.h>
#include	<math.h>

// constants
#define			kAssistInlet	1
#define			kAssistOutlet	2
#define			kMaxLong		0xFFFFFFFF
#define			kMaxNeighbors	4

// initial flight parameters
const short			kNumBoids		= 12;	// number of boids
const short			kNumNeighbors	= 2;	// must be <= kMaxNeighbors
const double 		kMinSpeed		= 0.15;	// boids' minimum speed
const double		kMaxSpeed		= 0.25;	// boids' maximum speed
const double		kCenterWeight	= 0.25;	// bflock centering
const double		kAttractWeight	= 0.300;// attraction point seeking
const double		kMatchWeight	= 0.100;// neighbors velocity matching
const double		kAvoidWeight	= 0.10;	// neighbors avoidance
const double		kWallsWeight	= 0.500;// wall avoidance [210]
const double		kEdgeDist		= 0.5;	// vision distance to avoid wall edges [5]
const double		kSpeedupFactor	= 0.100;// alter animation speed
const double		kInertiaFactor	= 0.20;	// willingness to change speed & direction
const double		kAccelFactor	= 0.100;// neighbor avoidance accelerate or decelerate rate
const double		kPrefDist		= 0.25;	// preferred distance from neighbors
const double		kFlyRectTop		= 1.0;	// fly rect boundaries
const double		kFlyRectLeft	= -1.0;	
const double		kFlyRectBottom	= -1.0;	
const double		kFlyRectRight	= 1.0;	
// const double		kFlyRectFront	= 1.0;	
// const double		kFlyRectBack	= -1.0;	


// typedefs
typedef struct Velocity {
	double		x;
	double		y;
//	double		z;
} Velocity;

typedef struct Point3d {
	double		x;
	double		y;
//	double		z;
} Point3d;

typedef struct Box3D {
	double		left, right;
	double		top, bottom;
//	double		front, back;
} Box3D;

typedef struct Boid {
	Point3d		oldPos;
	Point3d		newPos;
	Velocity	oldDir;
	Velocity	newDir;
	double		speed;
	short		neighbor[kMaxNeighbors];
	double		neighborDistSqr[kMaxNeighbors];
} Boid, *BoidPtr;

typedef struct FlockObject {
	Object		theObject;
	void		*out1, *out2;
	short		mode;
	long		numBoids;
	long		numNeighbors;
	Box3D		flyRect;
	double 		minSpeed;
	double		maxSpeed;
	double		centerWeight;
	double		attractWeight;
	double		matchWeight;
	double		avoidWeight;
	double		wallsWeight;
	double		edgeDist;
	double		speedupFactor;
	double		inertiaFactor;
	double		accelFactor;
	double		prefDist;
	double		prefDistSqr;
	Point3d		centerPt;
	Point3d		attractPt;
	BoidPtr		boid;
	double 		d2r, r2d;
} FlockObject, *FlockPtr;

// variables
void*	bflock;
t_symbol *ps_nothing;

// prototypes
void main();
void* Flock_new(long numBoids, long mode);
void Flock_free(FlockPtr bflockPtr);
void Flock_assist(FlockPtr bflockPtr, void* temp, long letType, long letNum, char *assistStr);
void Flock_bang(FlockPtr bflockPtr);
void Flock_dump(FlockPtr bflockPtr);
void Flock_mode(FlockPtr bflockPtr, long arg);
void Flock_numNeighbors(FlockPtr bflockPtr, long arg);
void Flock_numBoids(FlockPtr bflockPtr, long arg);
void Flock_donumBoids(FlockPtr bflockPtr, Symbol *msg, short argc, Atom *argv);
void Flock_minSpeed(FlockPtr bflockPtr, double arg);
void Flock_maxSpeed(FlockPtr bflockPtr, double arg);
void Flock_centerWeight(FlockPtr bflockPtr, double arg);
void Flock_attractWeight(FlockPtr bflockPtr, double arg);
void Flock_matchWeight(FlockPtr bflockPtr, double arg);
void Flock_avoidWeight(FlockPtr bflockPtr, double arg);
void Flock_wallsWeight(FlockPtr bflockPtr, double arg);
void Flock_edgeDist(FlockPtr bflockPtr, double arg);
void Flock_speedupFactor(FlockPtr bflockPtr, double arg);
void Flock_inertiaFactor(FlockPtr bflockPtr, double arg);
void Flock_accelFactor(FlockPtr bflockPtr, double arg);
void Flock_prefDist(FlockPtr bflockPtr, double arg);
void Flock_flyRect(FlockPtr bflockPtr, Symbol *msg, short argc, Atom *argv);
void Flock_attractPt(FlockPtr bflockPtr, Symbol *msg, short argc, Atom *argv);
void Flock_reset(FlockPtr bflockPtr);
void Flock_resetBoids(FlockPtr bflockPtr);
void InitFlock(FlockPtr bflockPtr);
void FlightStep(FlockPtr bflockPtr);
Point3d FindFlockCenter(FlockPtr bflockPtr);
float MatchAndAvoidNeighbors(FlockPtr bflockPtr, short theBoid, Velocity *matchNeighborVel, Velocity *avoidNeighborVel);
Velocity SeekPoint(FlockPtr bflockPtr, short theBoid, Point3d seekPt);
Velocity AvoidWalls(FlockPtr bflockPtr, short theBoid);
Boolean InFront(BoidPtr theBoid, BoidPtr neighbor);
void NormalizeVelocity(Velocity *direction);
double RandomInt(double minRange, double maxRange);
double DistSqrToPt(Point3d firstPoint, Point3d secondPoint);

void Flock_set_pos(FlockPtr bflockPtr, Symbol *msg, short argc, Atom *argv);
void Flock_set_dir(FlockPtr bflockPtr, Symbol *msg, short argc, Atom *argv);
void Flock_set_speed(FlockPtr bflockPtr, Symbol *msg, short argc, Atom *argv);
void Flock_set_speedinv(FlockPtr bflockPtr, Symbol *msg, short argc, Atom *argv);

void main()
{
	setup((t_messlist **) &bflock, (method) Flock_new, (method) Flock_free, (short) sizeof(FlockObject), 0L, A_LONG, A_DEFLONG, 0);
	addmess((method) Flock_assist,"assist",	A_CANT, 0);
	addint((method)  Flock_numBoids);
	addbang((method) Flock_bang);
	addmess((method) Flock_numNeighbors,	"neighbors", 	A_LONG, 0);
	addmess((method) Flock_numBoids,		"number", 		A_LONG, 0);
	addmess((method) Flock_mode,			"mode", 		A_LONG, 0);
	addmess((method) Flock_minSpeed,		"minspeed", 	A_FLOAT, 0);
	addmess((method) Flock_maxSpeed,		"maxspeed", 	A_FLOAT, 0);
	addmess((method) Flock_centerWeight,	"center", 		A_FLOAT, 0);
	addmess((method) Flock_attractWeight,	"attract", 		A_FLOAT, 0);
	addmess((method) Flock_matchWeight,		"match", 		A_FLOAT, 0);
	addmess((method) Flock_avoidWeight,		"avoid", 		A_FLOAT, 0);
	addmess((method) Flock_wallsWeight,		"repel", 		A_FLOAT, 0);
	addmess((method) Flock_edgeDist,		"edgedist", 	A_FLOAT, 0);
	addmess((method) Flock_speedupFactor,	"speed", 		A_FLOAT, 0);
	addmess((method) Flock_inertiaFactor,	"inertia",	 	A_FLOAT, 0);
	addmess((method) Flock_accelFactor,		"accel", 		A_FLOAT, 0);
	addmess((method) Flock_prefDist,		"prefdist", 	A_FLOAT, 0);
	addmess((method) Flock_flyRect,			"flyrect", 		A_GIMME, 0);
	addmess((method) Flock_attractPt, 		"attractpt", 	A_GIMME, 0);
	addmess((method) Flock_set_pos, 		"set_pos", 	A_GIMME, 0);
	addmess((method) Flock_set_dir, 		"set_dir", 	A_GIMME, 0);
	addmess((method) Flock_set_speed, 		"set_speed", 	A_GIMME, 0);
	addmess((method) Flock_set_speedinv, 	"set_speedinv", 	A_GIMME, 0);
	addmess((method) Flock_resetBoids, 		"reset", 		0);
	addmess((method) Flock_reset, 			"init", 		0);
	addmess((method) Flock_dump, 			"dump", 		0);
	
	post("boids2d 2005 a.sier / jasch   © 1995-2003 eric l. singer   "__DATE__" "__TIME__);	
	ps_nothing = gensym("");
}


void* Flock_new(long numBoids, long mode)
{
	FlockPtr	bflockPtr;
	short		tempmode;
	t_atom 		temp[1];
	t_symbol 	*s = ps_nothing;
	
	bflockPtr = (FlockPtr) newobject(bflock);
	bflockPtr->out2 = outlet_new(bflockPtr, 0L);
	bflockPtr->out1 = outlet_new(bflockPtr, 0L);
	
	bflockPtr->boid = (Boid *) sysmem_newptr(sizeof(Boid));
	
	temp[0].a_type = A_LONG;
	temp[0].a_w.w_long =  numBoids;
	defer(bflockPtr, (method)Flock_donumBoids, s, 1, temp);

	bflockPtr->numBoids = numBoids;

	InitFlock(bflockPtr);
	
	if(mode){
 		bflockPtr->mode = CLIP(mode, 0, 2);
	}else{
		bflockPtr->mode = 0;
	}	
	bflockPtr->d2r = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068/180.0;
	bflockPtr->r2d = 180.0/3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068;
	return(bflockPtr);
}


void Flock_free(FlockPtr bflockPtr)
{
	sysmem_freeptr((Ptr)bflockPtr->boid);
}


void Flock_assist(FlockPtr bflockPtr, void* temp, long letType, long letNum, char *assistStr)
{
	switch (letType){
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
					sprintf(assistStr, "boids data (xyz...)");
				break;
				case 1:	
					sprintf(assistStr, "parameter dump");
				break;
			}
			break;
	}
}

void Flock_bang(FlockPtr bflockPtr)
{
	short	i;
	t_atom 	outlist[10];
	t_atom 	*out;
	
	double 	tempNew_x, tempNew_y; 
	double 	tempOld_x, tempOld_y;
	double	delta_x, delta_y; 
	double 	azi, speed;
	// double tempspeed;
	
	out = outlist;
		
	FlightStep(bflockPtr);


	switch(bflockPtr->mode) { // newpos
		case 0:
		for (i = 0; i < bflockPtr->numBoids; i++){
			SETLONG(out+0, i);
			SETFLOAT(out+1, bflockPtr->boid[i].newPos.x);
			SETFLOAT(out+2, bflockPtr->boid[i].newPos.y);
		//	SETFLOAT(out+3, bflockPtr->boid[i].newPos.z);
			outlet_list(bflockPtr->out1, 0L, 3, out);
		}
		break;
		case 1: //newpos + oldpos
		for (i = 0; i < bflockPtr->numBoids; i++){
			SETLONG(out+0, i);
			SETFLOAT(out+1, bflockPtr->boid[i].newPos.x);
			SETFLOAT(out+2, bflockPtr->boid[i].newPos.y);
			// SETFLOAT(out+3, bflockPtr->boid[i].newPos.z);
			SETFLOAT(out+4, bflockPtr->boid[i].oldPos.x);
			SETFLOAT(out+5, bflockPtr->boid[i].oldPos.y);
			// SETFLOAT(out+6, bflockPtr->boid[i].oldPos.z);
			outlet_list(bflockPtr->out1, 0L, 7, out);
		}
		break;
		case 2:
		for (i = 0; i < bflockPtr->numBoids; i++){						
			tempNew_x = bflockPtr->boid[i].newPos.x;
			tempNew_y = bflockPtr->boid[i].newPos.y;
			// tempNew_z = bflockPtr->boid[i].newPos.z;
			tempOld_x = bflockPtr->boid[i].oldPos.x;
			tempOld_y = bflockPtr->boid[i].oldPos.y;
			// tempOld_z = bflockPtr->boid[i].oldPos.z;
			delta_x = tempNew_x - tempOld_x;
			delta_y = tempNew_y - tempOld_y;
			// delta_z = tempNew_z - tempOld_z;
			azi = atan2(delta_y, delta_x) * bflockPtr->r2d;
			// ele = atan2(delta_y, delta_x) * bflockPtr->r2d;
			speed = sqrt(delta_x * delta_x + delta_y * delta_y);//  + delta_z * delta_z);
			SETLONG(out+0, i);
			SETFLOAT(out+1, tempNew_x);
			SETFLOAT(out+2, tempNew_y);
			// SETFLOAT(out+3, tempNew_z);
			SETFLOAT(out+4, tempOld_x);
			SETFLOAT(out+5, tempOld_y);
			// SETFLOAT(out+6, tempOld_z);
			SETFLOAT(out+7, speed);
			SETFLOAT(out+8, azi);
			// SETFLOAT(out+9, ele);
			outlet_list(bflockPtr->out1, 0L, 9, out); //was 7. mathieu found this bug
		}
		break;	
	}
}

void Flock_dump(FlockPtr bflockPtr)
{
	Atom	outList[6];
	
	outList[0].a_type = A_LONG;
	outList[0].a_w.w_long =  bflockPtr->numNeighbors;
	outlet_anything(bflockPtr->out2, gensym("neighbors"), 1, outList);

	outList[0].a_type = A_FLOAT;
	outList[0].a_w.w_float =  bflockPtr->minSpeed;
	outlet_anything(bflockPtr->out2, gensym("minspeed"), 1, outList);

	outList[0].a_type = A_FLOAT;
	outList[0].a_w.w_float =  bflockPtr->maxSpeed;
	outlet_anything(bflockPtr->out2, gensym("maxspeed"), 1, outList);

	outList[0].a_type = A_FLOAT;
	outList[0].a_w.w_float =  bflockPtr->centerWeight;
	outlet_anything(bflockPtr->out2, gensym("center"), 1, outList);

	outList[0].a_type = A_FLOAT;
	outList[0].a_w.w_float =  bflockPtr->attractWeight;
	outlet_anything(bflockPtr->out2, gensym("attract"), 1, outList);

	outList[0].a_type = A_FLOAT;
	outList[0].a_w.w_float =  bflockPtr->matchWeight;
	outlet_anything(bflockPtr->out2, gensym("match"), 1, outList);

	outList[0].a_type = A_FLOAT;
	outList[0].a_w.w_float =  bflockPtr->avoidWeight;
	outlet_anything(bflockPtr->out2, gensym("avoid"), 1, outList);

	outList[0].a_type = A_FLOAT;
	outList[0].a_w.w_float =  bflockPtr->wallsWeight;
	outlet_anything(bflockPtr->out2, gensym("repel"), 1, outList);

	outList[0].a_type = A_FLOAT;
	outList[0].a_w.w_float =  bflockPtr->edgeDist;
	outlet_anything(bflockPtr->out2, gensym("edgedist"), 1, outList);

	outList[0].a_type = A_FLOAT;
	outList[0].a_w.w_float =  bflockPtr->speedupFactor;
	outlet_anything(bflockPtr->out2, gensym("speed"), 1, outList);

	outList[0].a_type = A_FLOAT;
	outList[0].a_w.w_float =  bflockPtr->inertiaFactor;
	outlet_anything(bflockPtr->out2, gensym("inertia"), 1, outList);

	outList[0].a_type = A_FLOAT;
	outList[0].a_w.w_float =  bflockPtr->accelFactor;
	outlet_anything(bflockPtr->out2, gensym("accel"), 1, outList);

	outList[0].a_type = A_FLOAT;
	outList[0].a_w.w_float = bflockPtr->prefDist;
	outlet_anything(bflockPtr->out2, gensym("prefdist"), 1, outList);

	outList[0].a_type = A_FLOAT;
	outList[0].a_w.w_float =  bflockPtr->flyRect.left;
	outList[1].a_type = A_FLOAT;
	outList[1].a_w.w_float =  bflockPtr->flyRect.top;
	outList[2].a_type = A_FLOAT;
	outList[2].a_w.w_float =  bflockPtr->flyRect.right;
	outList[3].a_type = A_FLOAT;
	outList[3].a_w.w_float =  bflockPtr->flyRect.bottom;
	/*outList[4].a_type = A_FLOAT;
	outList[4].a_w.w_float =  bflockPtr->flyRect.front;
	outList[5].a_type = A_FLOAT;
	outList[5].a_w.w_float =  bflockPtr->flyRect.back;*/
	outlet_anything(bflockPtr->out2, gensym("flyrect"), 4, outList);

	outList[0].a_type = A_FLOAT;
	outList[0].a_w.w_float =  bflockPtr->attractPt.x;
	outList[1].a_type = A_FLOAT;
	outList[1].a_w.w_float =  bflockPtr->attractPt.y;
	/*outList[2].a_type = A_FLOAT;
	outList[2].a_w.w_float =  bflockPtr->attractPt.z;*/
	outlet_anything(bflockPtr->out2, gensym("attractpt"), 2, outList);
	
	outList[0].a_type = A_LONG;
	outList[0].a_w.w_long =  bflockPtr->mode;
	outlet_anything(bflockPtr->out2, gensym("mode"), 1, outList);
	
	outList[0].a_type = A_LONG;
	outList[0].a_w.w_long =  bflockPtr->numBoids;
	outlet_anything(bflockPtr->out2, gensym("number"), 1, outList);
}


void Flock_mode(FlockPtr bflockPtr, long arg)
{
	bflockPtr->mode = CLIP(arg, 0, 2);
}

void Flock_numNeighbors(FlockPtr bflockPtr, long arg)
{
	bflockPtr->numNeighbors = arg;
}

void Flock_numBoids(FlockPtr bflockPtr, long arg)
{
	t_atom temp[1];
	t_symbol *s = ps_nothing;
	
	temp[0].a_type = A_LONG;
	temp[0].a_w.w_long =  arg;
	defer(bflockPtr, (method)Flock_donumBoids, s, 1, temp);
	Flock_resetBoids(bflockPtr);
}

void Flock_donumBoids(FlockPtr bflockPtr, Symbol *msg, short argc, Atom *argv)
{
		bflockPtr->boid = (Boid *)sysmem_resizeptr(bflockPtr->boid, sizeof(Boid) * argv[0].a_w.w_long);
		bflockPtr->numBoids = argv[0].a_w.w_long;
}

void Flock_minSpeed(FlockPtr bflockPtr, double arg)
{
	bflockPtr->minSpeed = MAX(arg, 0.000001);
}

void Flock_maxSpeed(FlockPtr bflockPtr, double arg)
{
	bflockPtr->maxSpeed = arg;
}

void Flock_centerWeight(FlockPtr bflockPtr, double arg)
{
	bflockPtr->centerWeight = arg;
}

void Flock_attractWeight(FlockPtr bflockPtr, double arg)
{
	bflockPtr->attractWeight = arg;
}

void Flock_matchWeight(FlockPtr bflockPtr, double arg)
{
	bflockPtr->matchWeight = arg;
}

void Flock_avoidWeight(FlockPtr bflockPtr, double arg)
{
	bflockPtr->avoidWeight = arg;
}

void Flock_wallsWeight(FlockPtr bflockPtr, double arg)
{
	bflockPtr->wallsWeight = arg;
}

void Flock_edgeDist(FlockPtr bflockPtr, double arg)
{
	bflockPtr->edgeDist = arg;
}

void Flock_speedupFactor(FlockPtr bflockPtr, double arg)
{
	bflockPtr->speedupFactor = arg;
}

void Flock_inertiaFactor(FlockPtr bflockPtr, double arg)
{
	if(arg == 0){
		bflockPtr->inertiaFactor = 0.000001;
	}else{
		bflockPtr->inertiaFactor = arg;
	}
}

void Flock_accelFactor(FlockPtr bflockPtr, double arg)
{
	bflockPtr->accelFactor = arg;
}

void Flock_prefDist(FlockPtr bflockPtr, double arg)
{
	bflockPtr->prefDist = arg;
}

void Flock_flyRect(FlockPtr bflockPtr, Symbol *msg, short argc, Atom *argv)
{
	double temp[4];
	short i;
	if(argc == 4){
		for(i=0;i<4;i++) {
			if(argv[i].a_type == A_FLOAT) {
				temp[i] = (double)argv[i].a_w.w_float;	
			}else if(argv[i].a_type == A_LONG) {
				temp[i] = (double)argv[i].a_w.w_long;	
			}
		}
		bflockPtr->flyRect.left 		= temp[0];
		bflockPtr->flyRect.top 		= temp[1];
		bflockPtr->flyRect.right 	= temp[2];
		bflockPtr->flyRect.bottom 	= temp[3];
		// bflockPtr->flyRect.front 	= temp[4];
		// bflockPtr->flyRect.back 		= temp[5];
	}else{
		error("boids2d: flyrect needs four values");
	}
}

void Flock_attractPt(FlockPtr bflockPtr, Symbol *msg, short argc, Atom *argv)
{
	double temp[2];
	short i;
	if(argc == 2){
	for(i=0;i<2;i++) {
		if(argv[i].a_type == A_FLOAT) {
			temp[i] = (double)argv[i].a_w.w_float;	
		}else if(argv[i].a_type == A_LONG) {
			temp[i] = (double)argv[i].a_w.w_long;	
		}
	}
	bflockPtr->attractPt.x = temp[0];
	bflockPtr->attractPt.y = temp[1];
	// bflockPtr->attractPt.z = temp[2];
	}else{
		error("boids2d: attractPt needs two values");
	}
}

void Flock_reset(FlockPtr bflockPtr)
{
	InitFlock(bflockPtr);
}

void Flock_resetBoids(FlockPtr bflockPtr)
{
	long i, j;
	double rndAngle;
	
	for (i = 0; i <  bflockPtr->numBoids; i++) { // init everything to 0.0
		bflockPtr->boid[i].oldPos.x = 0.0;
		bflockPtr->boid[i].oldPos.y = 0.0;
		// bflockPtr->boid[i].oldPos.z = 0.0;

		bflockPtr->boid[i].newPos.x = 0.0;
		bflockPtr->boid[i].newPos.y = 0.0;
		// bflockPtr->boid[i].newPos.z = 0.0;
		
		bflockPtr->boid[i].oldDir.x = 0.0;
		bflockPtr->boid[i].oldDir.y = 0.0;
		// bflockPtr->boid[i].oldDir.z = 0.0;
		
		bflockPtr->boid[i].newDir.x = 0.0;
		bflockPtr->boid[i].newDir.y = 0.0;
		// bflockPtr->boid[i].newDir.z = 0.0;
		
		bflockPtr->boid[i].speed = 0.0;
		
		for(j=0; j<kMaxNeighbors;j++){
			bflockPtr->boid[i].neighbor[j] = 0;
			bflockPtr->boid[i].neighborDistSqr[j] = 0.0;
		}
	}
	for (i = 0; i <  bflockPtr->numBoids; i++) {				// set the initial locations and velocities of the boids
		bflockPtr->boid[i].newPos.x = bflockPtr->boid[i].oldPos.x = RandomInt(bflockPtr->flyRect.right,bflockPtr->flyRect.left);		// set random location within flyRect
		bflockPtr->boid[i].newPos.y = bflockPtr->boid[i].oldPos.y = RandomInt(bflockPtr->flyRect.bottom, bflockPtr->flyRect.top);
		// bflockPtr->boid[i].newPos.z = bflockPtr->boid[i].oldPos.z = RandomInt(bflockPtr->flyRect.back, bflockPtr->flyRect.front);
		rndAngle = RandomInt(0, 360) * bflockPtr->d2r;		// set velocity from random angle
		bflockPtr->boid[i].newDir.x = sin(rndAngle);
		bflockPtr->boid[i].newDir.y = cos(rndAngle);
		// bflockPtr->boid[i].newDir.z = (cos(rndAngle) + sin(rndAngle)) * 0.5;
		bflockPtr->boid[i].speed = (kMaxSpeed + kMinSpeed) * 0.5;
	}

}

void InitFlock(FlockPtr bflockPtr)
{
	bflockPtr->numNeighbors		= kNumNeighbors;
	bflockPtr->minSpeed			= kMinSpeed;
	bflockPtr->maxSpeed			= kMaxSpeed;
	bflockPtr->centerWeight		= kCenterWeight;
	bflockPtr->attractWeight		= kAttractWeight;
	bflockPtr->matchWeight		= kMatchWeight;
	bflockPtr->avoidWeight		= kAvoidWeight;
	bflockPtr->wallsWeight		= kWallsWeight;
	bflockPtr->edgeDist			= kEdgeDist;
	bflockPtr->speedupFactor		= kSpeedupFactor;
	bflockPtr->inertiaFactor		= kInertiaFactor;
	bflockPtr->accelFactor		= kAccelFactor;
	bflockPtr->prefDist			= kPrefDist;
	bflockPtr->prefDistSqr		= kPrefDist * kPrefDist;
	bflockPtr->flyRect.top		= kFlyRectTop;
	bflockPtr->flyRect.left		= kFlyRectLeft;
	bflockPtr->flyRect.bottom	= kFlyRectBottom;
	bflockPtr->flyRect.right		= kFlyRectRight;
	// bflockPtr->flyRect.front		= kFlyRectFront;
	// bflockPtr->flyRect.back		= kFlyRectBack;
	bflockPtr->attractPt.x		= (kFlyRectLeft + kFlyRectRight) * 0.5;
	bflockPtr->attractPt.y		= (kFlyRectTop + kFlyRectBottom) * 0.5;
	// bflockPtr->attractPt.z		= (kFlyRectFront + kFlyRectBack) * 0.5;
	Flock_resetBoids(bflockPtr);
}

void FlightStep(FlockPtr bflockPtr)
{
	Velocity		goCenterVel;
	Velocity		goAttractVel;
	Velocity		matchNeighborVel;
	Velocity		avoidWallsVel;
	Velocity		avoidNeighborVel;
	float			avoidNeighborSpeed;
	const Velocity	zeroVel	= {0.0, 0.0};//, 0.0};
	short			i;

	bflockPtr->centerPt = FindFlockCenter(bflockPtr);
	for (i = 0; i <  bflockPtr->numBoids; i++) {						// save position and velocity
		bflockPtr->boid[i].oldPos.x = bflockPtr->boid[i].newPos.x;
		bflockPtr->boid[i].oldPos.y = bflockPtr->boid[i].newPos.y;
		// bflockPtr->boid[i].oldPos.z = bflockPtr->boid[i].newPos.z;
		
		bflockPtr->boid[i].oldDir.x = bflockPtr->boid[i].newDir.x;
		bflockPtr->boid[i].oldDir.y = bflockPtr->boid[i].newDir.y;
		// bflockPtr->boid[i].oldDir.z = bflockPtr->boid[i].newDir.z;
	}
	for (i = 0; i < bflockPtr->numBoids; i++) {
		if (bflockPtr->numNeighbors > 0) {							// get all velocity components
			avoidNeighborSpeed = MatchAndAvoidNeighbors(bflockPtr, i,&matchNeighborVel, &avoidNeighborVel);
		} else {
			matchNeighborVel = zeroVel;
			avoidNeighborVel = zeroVel;
			avoidNeighborSpeed = 0;
		}
		goCenterVel = SeekPoint(bflockPtr, i, bflockPtr->centerPt);			
		goAttractVel = SeekPoint(bflockPtr, i, bflockPtr->attractPt);
		avoidWallsVel = AvoidWalls(bflockPtr, i);
	
		// compute resultant velocity using weights and inertia
		bflockPtr->boid[i].newDir.x = bflockPtr->inertiaFactor * (bflockPtr->boid[i].oldDir.x) +
							(bflockPtr->centerWeight * goCenterVel.x +
							 bflockPtr->attractWeight * goAttractVel.x +
							 bflockPtr->matchWeight * matchNeighborVel.x +
							 bflockPtr->avoidWeight * avoidNeighborVel.x +
							 bflockPtr->wallsWeight * avoidWallsVel.x) / bflockPtr->inertiaFactor;
		bflockPtr->boid[i].newDir.y = bflockPtr->inertiaFactor * (bflockPtr->boid[i].oldDir.y) +
							(bflockPtr->centerWeight * goCenterVel.y +
							 bflockPtr->attractWeight * goAttractVel.y +
							 bflockPtr->matchWeight * matchNeighborVel.y +
							 bflockPtr->avoidWeight * avoidNeighborVel.y +
							 bflockPtr->wallsWeight * avoidWallsVel.y) / bflockPtr->inertiaFactor;
		/*bflockPtr->boid[i].newDir.z = bflockPtr->inertiaFactor * (bflockPtr->boid[i].oldDir.z) +
							(bflockPtr->centerWeight * goCenterVel.z +
							 bflockPtr->attractWeight * goAttractVel.z +
							 bflockPtr->matchWeight * matchNeighborVel.z +
							 bflockPtr->avoidWeight * avoidNeighborVel.z +
							 bflockPtr->wallsWeight * avoidWallsVel.z) / bflockPtr->inertiaFactor;*/
		NormalizeVelocity(&(bflockPtr->boid[i].newDir));	// normalize velocity so its length is unity

		// set to avoidNeighborSpeed bounded by minSpeed and maxSpeed
		if ((avoidNeighborSpeed >= bflockPtr->minSpeed) &&
				(avoidNeighborSpeed <= bflockPtr->maxSpeed))
			bflockPtr->boid[i].speed = avoidNeighborSpeed;
		else if (avoidNeighborSpeed > bflockPtr->maxSpeed)
			bflockPtr->boid[i].speed = bflockPtr->maxSpeed;
		else
			bflockPtr->boid[i].speed = bflockPtr->minSpeed;

		// calculate new position, applying speedupFactor
		bflockPtr->boid[i].newPos.x += bflockPtr->boid[i].newDir.x * bflockPtr->boid[i].speed * (bflockPtr->speedupFactor / 100.0);
		bflockPtr->boid[i].newPos.y += bflockPtr->boid[i].newDir.y * bflockPtr->boid[i].speed * (bflockPtr->speedupFactor / 100.0);
		// bflockPtr->boid[i].newPos.z += bflockPtr->boid[i].newDir.z * bflockPtr->boid[i].speed * (bflockPtr->speedupFactor / 100.0);

	}
}

Point3d FindFlockCenter(FlockPtr bflockPtr)
{
	double			totalH = 0, totalV = 0, totalD = 0;
	Point3d			centerPoint;
	register short	i;

	for (i = 0 ; i <  bflockPtr->numBoids; i++)
	{
		totalH += bflockPtr->boid[i].oldPos.x;
		totalV += bflockPtr->boid[i].oldPos.y;
		// totalD += bflockPtr->boid[i].oldPos.z;
	}
	centerPoint.x = (double)	(totalH / bflockPtr->numBoids);
	centerPoint.y = (double)	(totalV / bflockPtr->numBoids);
	// centerPoint.z = (double)	(totalD / bflockPtr->numBoids);
		
	return(centerPoint);
}

float MatchAndAvoidNeighbors(FlockPtr bflockPtr, short theBoid, Velocity *matchNeighborVel, Velocity *avoidNeighborVel)
{
	short			i, j, neighbor;
	double			distSqr;
	double			dist, distH, distV,distD;
	double			tempSpeed;
	short			numClose = 0;
	Velocity		totalVel = {0.0,0.0};//,0.0};

	/**********************/
	/* Find the neighbors */	
	/**********************/

	/* special case of one neighbor */
	if (bflockPtr->numNeighbors == 1) {
		bflockPtr->boid[theBoid].neighborDistSqr[0] = kMaxLong;
	
		for (i = 0; i < bflockPtr->numBoids; i++) {
			if (i != theBoid) {
				distSqr = DistSqrToPt(bflockPtr->boid[theBoid].oldPos, bflockPtr->boid[i].oldPos);
				
				/* if this one is closer than the closest so far, then remember it */
				if (bflockPtr->boid[theBoid].neighborDistSqr[0] > distSqr) {
					bflockPtr->boid[theBoid].neighborDistSqr[0] = distSqr;
					bflockPtr->boid[theBoid].neighbor[0] = i;
				}
			}
		}
	}
	/* more than one neighbor */
	else {
		for (j = 0; j < bflockPtr->numNeighbors; j++)
			bflockPtr->boid[theBoid].neighborDistSqr[j] = kMaxLong;
		
		for (i = 0 ; i < bflockPtr->numBoids; i++) {
			/* if this one is not me... */
			if (i != theBoid) {
				distSqr = DistSqrToPt(bflockPtr->boid[theBoid].oldPos, bflockPtr->boid[i].oldPos);
	
				/* if distSqr is less than the distance at the bottom of the array, sort into array */
				if (distSqr < bflockPtr->boid[theBoid].neighborDistSqr[bflockPtr->numNeighbors-1]) {
					j = bflockPtr->numNeighbors - 1;
				
					/* sort distSqr in to keep array in size order, smallest first */
					while ((distSqr < bflockPtr->boid[theBoid].neighborDistSqr[j-1]) && (j > 0)) {
						bflockPtr->boid[theBoid].neighborDistSqr[j] = bflockPtr->boid[theBoid].neighborDistSqr[j - 1];
						bflockPtr->boid[theBoid].neighbor[j] = bflockPtr->boid[theBoid].neighbor[j - 1];
						j--;
					}
					bflockPtr->boid[theBoid].neighborDistSqr[j] = distSqr;
					bflockPtr->boid[theBoid].neighbor[j] = i;					
				}
			}
		}
	}

	/*********************************/
	/* Match and avoid the neighbors */	
	/*********************************/

	matchNeighborVel->x = 0;
	matchNeighborVel->y = 0;
	// matchNeighborVel->z = 0;
	
	// set tempSpeed to old speed
	tempSpeed = bflockPtr->boid[theBoid].speed;
	
	for (i = 0; i < bflockPtr->numNeighbors; i++) {
		neighbor = bflockPtr->boid[theBoid].neighbor[i];
		
		// calculate matchNeighborVel by averaging the neighbor velocities
		matchNeighborVel->x += bflockPtr->boid[neighbor].oldDir.x;
		matchNeighborVel->y += bflockPtr->boid[neighbor].oldDir.y;
		// matchNeighborVel->z += bflockPtr->boid[neighbor].oldDir.z;
			
		// if distance is less than preferred distance, then neighbor influences boid
		distSqr = bflockPtr->boid[theBoid].neighborDistSqr[i];
		if (distSqr < bflockPtr->prefDistSqr) {
			dist = sqrt(distSqr);

			distH = bflockPtr->boid[neighbor].oldPos.x - bflockPtr->boid[theBoid].oldPos.x;
			distV = bflockPtr->boid[neighbor].oldPos.y - bflockPtr->boid[theBoid].oldPos.y;
			// distD = bflockPtr->boid[neighbor].oldPos.z - bflockPtr->boid[theBoid].oldPos.z;
			
			if(dist == 0.0) dist = 0.0000001;
			totalVel.x = totalVel.x - distH - (distH * ((float) bflockPtr->prefDist / (dist)));
			totalVel.y = totalVel.y - distV - (distV * ((float) bflockPtr->prefDist / (dist)));
			// totalVel.z = totalVel.z - distD - (distV * ((float) bflockPtr->prefDist / (dist)));
		
			numClose++;
		}
		if (InFront(&(bflockPtr->boid[theBoid]), &(bflockPtr->boid[neighbor]))) {	// adjust speed
			if (distSqr < bflockPtr->prefDistSqr) 
				tempSpeed /= (bflockPtr->accelFactor / 100.0);
			else
				tempSpeed *= (bflockPtr->accelFactor / 100.0);
		}
		else {
			if (distSqr < bflockPtr->prefDistSqr)
				tempSpeed *= (bflockPtr->accelFactor / 100.0);
			else
				tempSpeed /= (bflockPtr->accelFactor / 100.0);
		}
	}
	if (numClose) {
		avoidNeighborVel->x = totalVel.x / numClose;
		avoidNeighborVel->y = totalVel.y / numClose;
		// avoidNeighborVel->z = totalVel.z / numClose;
		NormalizeVelocity(matchNeighborVel);
	}
	else {
		avoidNeighborVel->x = 0;
		avoidNeighborVel->y = 0;
		// avoidNeighborVel->z = 0;
	}
	return(tempSpeed);
}


Velocity SeekPoint(FlockPtr bflockPtr, short theBoid, Point3d seekPt)
{
	Velocity	tempDir;
	tempDir.x = seekPt.x - bflockPtr->boid[theBoid].oldPos.x;	
	tempDir.y = seekPt.y - bflockPtr->boid[theBoid].oldPos.y;
	// tempDir.z = seekPt.z - bflockPtr->boid[theBoid].oldPos.z;
	NormalizeVelocity(&tempDir);
	return(tempDir);
}


Velocity AvoidWalls(FlockPtr bflockPtr, short theBoid)
{
	Point3d		testPoint;
	Velocity	tempVel = {0.0, 0.0};//, 0.0};
		
	/* calculate test point in front of the nose of the boid */
	/* distance depends on the boid's speed and the avoid edge constant */
	testPoint.x = bflockPtr->boid[theBoid].oldPos.x + bflockPtr->boid[theBoid].oldDir.x * bflockPtr->boid[theBoid].speed * bflockPtr->edgeDist;
	testPoint.y = bflockPtr->boid[theBoid].oldPos.y + bflockPtr->boid[theBoid].oldDir.y * bflockPtr->boid[theBoid].speed * bflockPtr->edgeDist;
	// testPoint.z = bflockPtr->boid[theBoid].oldPos.z + bflockPtr->boid[theBoid].oldDir.z * bflockPtr->boid[theBoid].speed * bflockPtr->edgeDist;

	/* if test point is out of the left (right) side of bflockPtr->flyRect, */
	/* return a positive (negative) horizontal velocity component */
	if (testPoint.x < bflockPtr->flyRect.left)
		tempVel.x = fabs(bflockPtr->boid[theBoid].oldDir.x);
	else if (testPoint.x > bflockPtr->flyRect.right)
		tempVel.x = - fabs(bflockPtr->boid[theBoid].oldDir.x);

	/* same with top and bottom */
	if (testPoint.y < bflockPtr->flyRect.top)
		tempVel.y = fabs(bflockPtr->boid[theBoid].oldDir.y);
	else if (testPoint.y > bflockPtr->flyRect.bottom)
		tempVel.y = - fabs(bflockPtr->boid[theBoid].oldDir.y);

	/* same with front and back
	if (testPoint.z < bflockPtr->flyRect.front)
		tempVel.z = fabs(bflockPtr->boid[theBoid].oldDir.z);
	else if (testPoint.z > bflockPtr->flyRect.back)
		tempVel.z = - fabs(bflockPtr->boid[theBoid].oldDir.z);
	*/
	
	return(tempVel);
}


Boolean InFront(BoidPtr theBoid, BoidPtr neighbor)
{
	float	grad, intercept;
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
	if (theBoid->oldDir.x != 0) {
		// calculate gradient of a line _perpendicular_ to its direction (hence the minus)
		grad = -theBoid->oldDir.y / theBoid->oldDir.x;
		
		// calculate where this line hits the y axis (from y = mx + c)
		intercept = theBoid->oldPos.y - (grad * theBoid->oldPos.x);

		/* compare the horizontal position of the neighbor boid with */
		/* the point on the line that has its vertical coordinate */
		if (neighbor->oldPos.x >= ((neighbor->oldPos.y - intercept) / grad)) {
			/* return true if the first boid's horizontal movement is +ve */
			result = (theBoid->oldDir.x > 0);

			if (result==0) return 0;
			else goto next;
			
		} else {
			/* return true if the first boid's horizontal movement is +ve */
			result = (theBoid->oldDir.x < 0);
			if (result==0) return 0;
			else goto next;
		}
	}
	/* else theBoid is travelling vertically, so just compare vertical coordinates */
	else if (theBoid->oldDir.y > 0) {
		result = (neighbor->oldPos.y > theBoid->oldPos.y);
		if (result==0){ 
			return 0;
		}else{
			goto next;
		}
	}else{
		result = (neighbor->oldPos.y < theBoid->oldPos.y);
		if (result==0){
			return 0;
		} else {
			goto next;
		}
	}
next:
/*
	// yz plane
	
	// if theBoid is not travelling vertically... 
	if (theBoid->oldDir.y != 0) {
		// calculate gradient of a line _perpendicular_ to its direction (hence the minus) 
		grad = -theBoid->oldDir.z / theBoid->oldDir.y;
		
		// calculate where this line hits the y axis (from y = mx + c) 
		intercept = theBoid->oldPos.z - (grad * theBoid->oldPos.y);

		// compare the horizontal position of the neighbor boid with 
		// the point on the line that has its vertical coordinate 
		if (neighbor->oldPos.y >= ((neighbor->oldPos.z - intercept) / grad)) {
			// return true if the first boid's horizontal movement is +ve 
			result = (theBoid->oldDir.y > 0);
			if (result==0){ 
				return 0;
			}else{
				goto next2;
			}
		} else {
			// return true if the first boid's horizontal movement is +ve 
			result = (theBoid->oldDir.y < 0);
			if (result==0){
				return 0;
			}else{
				goto next2;
			}
		}
	}
	// else theBoid is travelling vertically, so just compare vertical coordinates 
	else if (theBoid->oldDir.z > 0) {
		result = (neighbor->oldPos.z > theBoid->oldPos.z);
		if (result==0){ 
			return 0;
		}else{
			goto next2;
		}
	}else{
		result = (neighbor->oldPos.z < theBoid->oldPos.z);
		if (result==0){
			return 0;
		}else{
			goto next2;
		}
	}
next2: */
	return 1;
}

void NormalizeVelocity(Velocity *direction)
{
	float	hypot;
	
	hypot = sqrt(direction->x * direction->x + direction->y * direction->y);// + direction->z * direction->z );

	if (hypot != 0.0) {
		direction->x = direction->x / hypot;
		direction->y = direction->y / hypot;
		// direction->z = direction->z / hypot;
	}
}

double RandomInt(double minRange, double maxRange)
{
	unsigned short	qdRdm;
	double			t, result;
	
	qdRdm = Random();
	t = (double)qdRdm / 65536.0; 	// now 0 <= t <= 1
	result = (t * (maxRange - minRange)) + minRange;
	return(result);
}

double DistSqrToPt(Point3d firstPoint, Point3d secondPoint)
{
	double	a, b,c;
	a = firstPoint.x - secondPoint.x;
	b = firstPoint.y - secondPoint.y;	
	//c = firstPoint.z - secondPoint.z;	
	return(a * a + b * b); // + c * c);
}




void Flock_set_pos(FlockPtr bflockPtr, Symbol *msg, short argc, Atom *argv)
{
	//receives index posx posy
	int id, i;
	double temp[3];
	
	if(argc) {
		id = CLIP(argv->a_w.w_long,0,bflockPtr->numBoids-1);
		argv++;
		
		for(i=0;i<2;i++) {	//2dims
			if(argv->a_type == A_FLOAT) {
				temp[i] = (double)argv->a_w.w_float;	
				argv++;
			} else if(argv->a_type == A_LONG) {
				temp[i] = (double)argv->a_w.w_long;	
				argv++;
			}
	
		}

			// set ith boid to place
		bflockPtr->boid[id].oldPos.x = temp[0];
		bflockPtr->boid[id].oldPos.y = temp[1];
		bflockPtr->boid[id].newPos.x = temp[0];
		bflockPtr->boid[id].newPos.y = temp[1];


	}
}


void Flock_set_dir(FlockPtr bflockPtr, Symbol *msg, short argc, Atom *argv)
{
	//receives index dirx diry

	int id, i;
	double temp[3];
	
	if(argc) {
		id = CLIP(argv->a_w.w_long,0,bflockPtr->numBoids-1);
		argv++;
		
		for(i=0;i<2;i++) {	//2dims
			if(argv->a_type == A_FLOAT) {
				temp[i] = (double)argv->a_w.w_float;	
				argv++;
			} else if(argv->a_type == A_LONG) {
				temp[i] = (double)argv->a_w.w_long;	
				argv++;
			}
	
		}

			// set ith boid to place
		bflockPtr->boid[id].oldDir.x = temp[0];
		bflockPtr->boid[id].oldDir.y = temp[1];
		bflockPtr->boid[id].newDir.x = temp[0];
		bflockPtr->boid[id].newDir.y = temp[1];

	}

}

void Flock_set_speed(FlockPtr bflockPtr, Symbol *msg, short argc, Atom *argv)
{
	//receives index speed

	int id;
	double speed=0.;
	
	if(argc) {
		id = CLIP(argv->a_w.w_long,0,bflockPtr->numBoids-1);
		argv++;
		
		if(argv->a_type == A_FLOAT) {
			speed = (double)argv->a_w.w_float;	
			argv++;
		} else if(argv->a_type == A_LONG) {
			speed = (double)argv->a_w.w_long;	
			argv++;
		}

		

			// set ith boid to place
		bflockPtr->boid[id].speed = speed;
	}

}

void Flock_set_speedinv(FlockPtr bflockPtr, Symbol *msg, short argc, Atom *argv)
{
	//receives index 

	int id;
	double speed=0.;
	
	if(argc) {
		id = CLIP(argv->a_w.w_long,0,bflockPtr->numBoids-1);
		speed = bflockPtr->boid[id].speed;
		bflockPtr->boid[id].speed = -1*speed;
	}

}
