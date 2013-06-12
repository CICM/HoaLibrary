
/*

	simple agent simulation using "boids" like rules
	
	each agent has a position, a velocity and a set of rules which acts upon its velocity
	
	1. separate: run from positions of nearby neighbors (within septhresh)
	2. align: conform velocity to average velocity 
	3. cohere: move towards center of mass	
	4. gravitate: move towards/away from center of gravitation (gravpoint)
	
	there is also a crass simulation of inertia and friction. the space 
	is considered to be a torus, but certain things, like center of mass, 
	don't currently take this into account. so when an agent "escapes" 
	across a boundary to the other side of the torus, it has dramatic effect 
	on the pack's movement related to the "cohere" rule.
	
	for more info on boids/agent simulation check out Craig Reynolds' site:
	http://www.red3d.com/cwr/
	
	this example also shows a simple example of object oriented programming 
	in javascript (agent class), as well as the use of function pointers 
	(agent class tick method and rules array).
	
	for more info on object oriented programming with javascript, check out:
	http://www.javascriptkit.com/javatutors/oopjs.shtml
	http://www.sitepoint.com/article/470

*/

// set up inlets/outlets/assist strings
outlets = 3;
setinletassist(0,"bang calculates one iteration of simulation");
setoutletassist(2,"bang once for each series of x/y/vx/vy lists");
setoutletassist(1,"average x/y/vx/vy list");
setoutletassist(0,"series of x/y/vx/vy lists");

// global varables and code
var centroid_x = 0.;
var centroid_y = 0.;
var avgvelocity_x = 0.;
var avgvelocity_y = 0.;

var myseparation = 0.03;
var myalignment = 0.05;
var mycoherence = 0.02;
var myinertia = 0.5;
var myfriction = 0.5;
var mysepthresh = 0.1;
var mymaxvel = 0.05;
var mygravity = 0.;
var mygravpoint_x = 0.5;
var mygravpoint_y = 0.5;

var myagentcount = 20;

// initialize agents
var agents = new Array();
agentcount(20);

function agentcount(v)
{
	// clip agentcount to range 1.-100.
	myagentcount = clip(v,1,100);
	for (i=0;i<myagentcount;i++)
	{
		var x,y,vx,vy;
			
		// start with random position/velocity
		x = Math.random();
		y = Math.random();
		vx = (Math.random()-0.5)*0.1;
		vy = (Math.random()-0.5)*0.1;
		
		// create a new agent object
		agents[i] = new agent(x,y,vx,vy);	

		// set this agent's rules
		agents[i].rulecount = 4;
		agents[i].rules[0] = separate;
		agents[i].rules[1] = align;
		agents[i].rules[2] = cohere;		
		agents[i].rules[3] = gravitate;
		
		// the rules array is a set of functions
		// to be called once per simulation tick,
		// in the order in which they inhabit
		// the array. could add/remove rules here		
	}
}


function separation(v)
{
	myseparation = clip(v,0,1)*0.1;
}

function alignment(v)
{
	myalignment = clip(v,0,1)*0.1;
}

function coherence(v)
{
	mycoherence = clip(v,0,1)*0.1;
}

function friction(v)
{
	myfriction = clip(v,0,1);
}

function inertia(v)
{
	myinertia = clip(v,0,1);
}

function septhresh(v)
{
	mysepthresh = clip(v,0,0.5);
}

function maxvel(v)
{
	mymaxvel = clip(v,0,1)*0.1;
}

function gravity(v)
{
	mygravity = clip(v,-1,1)*0.1;
}

function gravpoint(x,y)
{
	mygravpoint_x = clip(x,0,1);
	mygravpoint_y = clip(y,0,1);
}

// task function

function bang()
{
	var i;
	var cx=0;
	var cy=0;
	var cvx=0;
	var cvy=0;
	
	for (i=0;i<myagentcount;i++)
	{	
		agents[i].tick();
		
		// calculate current frame's average position/velocity
		cx += agents[i].x;
		cy += agents[i].y;
		cvx += agents[i].vx;
		cvy += agents[i].vy;	
	}
	centroid_x = cx/myagentcount;	
	centroid_y = cy/myagentcount;	
	avgvelocity_x = cvx/myagentcount;	
	avgvelocity_y = cvy/myagentcount;	
	
	outlet(2,"bang");
	outlet(1,centroid_x,centroid_y,avgvelocity_x,avgvelocity_y);
	
	for (i=0;i<myagentcount;i++) {
		outlet(0,agents[i].x,agents[i].y,agents[i].vx,agents[i].vy);
	}
}

// the agent class constructor

function agent(x,y,vx,vy) 
{
	this.x = x;
	this.y = y;
	this.vx = vx;
	this.vy = vy;
	this.rulecount = 0;
	this.rules = new Array();
	this.tick = agent_tick; // tick method
}

// one iteration of the simulation for a given agent

function agent_tick() 
{
	var i,px,py;
	
	// save current velocity for inertia calc
	px = this.vx;
	py = this.vy;
	
	// apply rules
	for (i=0;i<this.rulecount;i++)
	{
		this.rules[i](this);
	}
	
	// inertia
	this.vx = px*myinertia + this.vx*(1.-myinertia);
	this.vy = py*myinertia + this.vy*(1.-myinertia);
	
	// velocity limit
	this.vx = clip(this.vx,-mymaxvel,mymaxvel);
	this.vy = clip(this.vy,-mymaxvel,mymaxvel);

	// update position based on velocity and friction
	this.x += this.vx*(1.-myfriction);
	this.y += this.vy*(1.-myfriction);

	wrap(this); // torus space	
	
}

// rules

function separate(a)
{
	var i,dx,dy,proxscale;
	
	// run from positions of neighbors 
	for (i=0;i<myagentcount;i++)
	{
		if (a != agents[i])
		{
			dx = agents[i].x - a.x;	
			dy = agents[i].y - a.y;
			
			//torus space
			if (dx>0.5) dx -= 1.;
			else if (dx<-0.5) dx += 1.;
			//torus space
			if (dy>0.5) dy -= 1.;
			else if (dy<-0.5) dy += 1.;
			
			if ((Math.abs(dx)>0.0001)&&(Math.abs(dy)>0.0001))
				mag = (dx*dx+dy*dy); // cheap mag, no sqrt 
			else
				mag = 0.01;
			
			if (mag<mysepthresh) {
				if (mag<0.0001)
					proxscale = 8;
				else
					proxscale = clip(mysepthresh/(mysepthresh-(mysepthresh-mag)),0,8);
				a.vx -= dx*myseparation*proxscale;
				a.vy -= dy*myseparation*proxscale;
			}
		}
	}	
}

function align(a)
{
	var dvx,dvy;
	
	// conform to velocities towards average velocity 
	dvx = avgvelocity_x - a.vx;
	dvy = avgvelocity_y - a.vy;
				 
	a.vx += dvx*myalignment;
	a.vy += dvy*myalignment;
}

function cohere(a)
{
	var dx,dy;

	// move towards center of mass	
	dx = centroid_x - a.x;
	dy = centroid_y - a.y;
	
	a.vx += dx*mycoherence;
	a.vy += dy*mycoherence;
}

function gravitate(a)
{
	var dx,dy;

	// move towards center
	dx = mygravpoint_x - a.x;
	dy = mygravpoint_y - a.y;
	
	a.vx += dx*mygravity;
	a.vy += dy*mygravity;
}


// utility functions

function wrap(a)
{
	if (a.x<0) { 
		a.x = a.x + 1.;
	} else if (a.x>1) {
		a.x = a.x - 1.;
	}
	
	if (a.y<0) {
		a.y = a.y + 1.;
	} else if (a.y>1) {
		a.y = a.y - 1.;
	}
}

function bounce(a)
{	
	if ((a.x<0)||(a.x>1)) {
		a.vx = -a.vx;
	}
	if ((a.y<0)||(a.y>1)) {
		a.vy = -a.vy;
	}
}

function clip(x,min,max)
{	
	return Math.min(Math.max(x,min),max);
}
