// 46jParticles.js
// 
// a 3-D particle generator with simple gravity simulation
// demonstrating different techniques for mathematical
// matrix manipulation using Jitter objects in [js].
//
// rld, 7.05
//

inlets = 1;
outlets = 1;

var PARTICLE_COUNT = 1000; // initial number of particle vertices
var ATTRACTOR_COUNT = 3; // initial number of points of gravity

// create a [jit.noise] object for particle and velocity generation
var noisegen = new JitterObject("jit.noise");
noisegen.dim = PARTICLE_COUNT;
noisegen.planecount = 3;
noisegen.type = "float32";

// create a [jit.noise] object for attractor generation
var attgen = new JitterObject("jit.noise");
attgen.dim = ATTRACTOR_COUNT;
attgen.planecount = 3;
attgen.type = "float32";

// create two [jit.expr] objects for the bang_expr() function

// first expression: sum all the planes in the input matrix
var myexpr = new JitterObject("jit.expr");
myexpr.expr = "in[0].p[0]+in[0].p[1]+in[0].p[2]"; 
// second expression: evaluate a+((b-c)*d/e)
var myexpr2 = new JitterObject("jit.expr");
myexpr2.expr = "in[0]+((in[1]-in[2])*in[3]/in[4])"; 

// create the Jitter matrices we need to store our data

// matrix of x,y,z particle vertices
var particlemat = new JitterMatrix(3, "float32", PARTICLE_COUNT); 
// matrix of x,y,z particle velocities
var velomat = new JitterMatrix(3, "float32", PARTICLE_COUNT); 
// matrix of x,y,z points of attraction (gravity centers)
var attmat = new JitterMatrix(3, "float32", ATTRACTOR_COUNT); 
// matrix for aggregate distances
var distmat = new JitterMatrix(3, "float32", PARTICLE_COUNT); 
// temporary matrix for the bang_op() function
var tempmat = new JitterMatrix(3, "float32", PARTICLE_COUNT); 
// temporary summing matrix for the bang_op() function
var summat = new JitterMatrix(1, "float32", PARTICLE_COUNT); 
// another temporary summing matrix for the bang_op() function
var summat2 = new JitterMatrix(1, "float32", PARTICLE_COUNT); 
// a scalar matrix to store the current gravity point
var scalarmat = new JitterMatrix(3, "float32", PARTICLE_COUNT); 
// a scalar matrix to store acceleration (expr_op() function only)
var amat = new JitterMatrix(1, "float32", PARTICLE_COUNT); 

var a = 0.001; // acceleration factor
var d = 0.01; // decay factor

var perform_mode="op"; // default perform function
var draw_primitive = "points"; // default drawing primitive

function loadbang() // execute this code when our Max patch opens
{
	init(); // initialize our matrices
	post("particles initialized.\n");
}

function init() 
// initialization routine... call at load, as well as 
// when we change the number of particles or attractors
{
	// generate a matrix of random particles spread between -1 and 1
	noisegen.matrixcalc(particlemat, particlemat);
	particlemat.op("*", 2.0);
	particlemat.op("-", 1.0);
	// generate a matrix of random velocities spread between -1 and 1
	noisegen.matrixcalc(velomat, velomat);
	velomat.op("*", 2.0);
	velomat.op("-", 1.0);
	// generate a matrix of random attractors spread between -1 and 1
	attgen.matrixcalc(attmat, attmat);
	attmat.op("*", 2.0);
	attmat.op("-", 1.0);
}

function bang() // perform one iteration of our particle system
{
	switch(perform_mode) { // choose from the following...
		case "op": // use Jitter matrix operators
			bang_op();
			break;
		case "expr": // use [jit.expr] for the bulk of the algorithm
			bang_expr();
			break;
		case "iter": // iterate cell-by-cell through the matrices
			bang_iter();
			break;
		default: // use bang_op() as our default
			bang_op();
			break;
	}

	// output our new matrix of particle vertices 
	// with the current drawing primitive
	outlet(0, "jit_matrix", particlemat.name, draw_primitive);

}

function bang_op() // create our particle matrix using Matrix operators
{
	for(var i = 0; i < ATTRACTOR_COUNT; i++) 
	// do one iteration per gravity point
	{
		// create a scalar matrix out of the current attractor:
		scalarmat.setall(attmat.getcell(i)); 

		// subtract our particle positions from the current attractor 
		// and store in a temporary matrix (x,y,z):
		tempmat.op("-", scalarmat, particlemat); 

		// square to create a cartesian distance matrix (x*x, y*y, z*z):
		distmat.op("*", tempmat, tempmat); 

		// sum the planes of the distance matrix (x*x+y*y+z*z)
		summat.planemap = 0;
		summat.frommatrix(distmat);
		summat2.planemap = 1;
		summat.frommatrix(distmat);
		summat.op("+", summat, summat2);
		summat2.planemap = 2;
		summat2.frommatrix(distmat);
		summat.op("+", summat, summat2);

		// scale our distances by the acceleration value:
		tempmat.op("*", a); 
		// divide our distances by the sum of the distances 
		// to derive gravity for this frame:
		tempmat.op("/", summat); 
		// add to the current velocity bearings to get the 
		// amount of motion for this frame:
		velomat.op("+", tempmat); 
	}

		// offset our current positions by the amount of motion:
		particlemat.op("+", velomat); 
		// reduce our velocities by the decay factor for the next frame:
		velomat.op("*", d); 
}

function bang_expr() // create our particle matrix using [jit.expr]
{
	// create a scalar matrix out of our acceleration value:
	amat.setall(a); 

	for(var i = 0; i < ATTRACTOR_COUNT; i++) 
	// do one iteration per gravity point
	{
		// create a scalar matrix out of the current attractor:
		scalarmat.setall(attmat.getcell(i)); 
		// subtract our particle positions from the current attractor 
		// and store in a temporary matrix (x,y,z):
		tempmat.op("-", scalarmat, particlemat); 
		// square to create a cartesian distance matrix (x*x, y*y, z*z):
		distmat.op("*", tempmat, tempmat); 

		// sum the planes of the distance matrix (x*x+y*y+z*z) : 
		// "in[0].p[0]+in[0].p[1]+in[0].p[2]" : 
		myexpr.matrixcalc(distmat, summat);

		// derive amount of motion for this frame : 
		// "in[0]+((in[1]-in[2])*in[3]/in[4])" :
		myexpr2.matrixcalc([velomat,scalarmat,particlemat,amat,summat],	velomat); 
	} 

		// offset our current positions by the amount of motion:
		particlemat.op("+", velomat); 
		// reduce our velocities by the decay factor for the next frame:
		velomat.op("*", d); 
} 

function bang_iter() // create our particle matrix cell-by-cell
{
	var p_array = new Array(3); // array for a single particle
	var v_array = new Array(3); // array for a single velocity
	var a_array = new Array(3); // array for a single attractor

	for(var j = 0; j < PARTICLE_COUNT; j++) 
	// do one iteration per particle
	{
		// fill an array with the current particle:
		p_array = particlemat.getcell(j); 
		// fill an array with the current particle's velocity:
		v_array = velomat.getcell(j); 

		for(var i = 0; i < ATTRACTOR_COUNT; i++) 
		// do one iteration per gravity point
		{
			// fill an array with the current attractor:
			a_array = attmat.getcell(i); 

			// find the distance from this particle to the 
			// current attractor:
			var distsum = (a_array[0]-p_array[0])*(a_array[0]-p_array[0]);
			distsum+= (a_array[1]-p_array[1])*(a_array[1]-p_array[1]);
			distsum+= (a_array[2]-p_array[2])*(a_array[2]-p_array[2]);

			// derive the amount of motion for this frame:
			v_array[0]+= (a_array[0]-p_array[0])*a/distsum; // x
			v_array[1]+= (a_array[1]-p_array[1])*a/distsum; // y
			v_array[2]+= (a_array[2]-p_array[2])*a/distsum; // z
		}

		// offset our current positions by the amount of motion
		p_array[0]+=v_array[0]; // x
		p_array[1]+=v_array[1]; // y
		p_array[2]+=v_array[2]; // z

		// reduce our velocities by the decay factor for the next frame:
		v_array[0]*=d; // x
		v_array[1]*=d; // y
		v_array[2]*=d; // z

		// set the position for this particle in the Jitter matrix:
		particlemat.setcell1d(j, p_array[0],p_array[1],p_array[2]); 
		// set the velocity for this particle in the Jitter matrix:
		velomat.setcell1d(j, v_array[0],v_array[1],v_array[2]); 
	}
} 


function particles(v) // change the number of particles we're working with
{
	PARTICLE_COUNT = v;

	// resize matrices
	noisegen.dim = PARTICLE_COUNT;
	particlemat.dim = PARTICLE_COUNT;
	velomat.dim = PARTICLE_COUNT;
	distmat.dim = PARTICLE_COUNT;
	attmat.dim = PARTICLE_COUNT;
	tempmat.dim = PARTICLE_COUNT;
	summat.dim = PARTICLE_COUNT;
	summat2.dim = PARTICLE_COUNT;
	scalarmat.dim = PARTICLE_COUNT;
	amat.dim = PARTICLE_COUNT;

	init(); // re-initialize particle system
}

function attractors(v) 
// change the number of gravity points we're working with
{
	ATTRACTOR_COUNT = v;

	// resize attractor matrix
	attgen.dim = ATTRACTOR_COUNT;

	init(); // re-initialize particle system
}

function accel(v) // set acceleration
{
	a = v*0.001;
}

function decay(v) // set decay
{
	d = v*0.001;
}

function mode(v) // change perform mode
{
	perform_mode = v;
}

function primitive(v) // change OpenGL drawing primitive
{
	draw_primitive = v;
}

function smear(v) // turn on drawing smear by zeroing the alpha on the renderer's erase color
{
	if(v) {
		// smear on (alpha=0):
		outlet(0, "erase_color", 1., 1., 1., 0.); 
	}
	else {
		// smear off (alpha=0.1):
		outlet(0, "erase_color", 1., 1., 1., 0.1); 
	}
}
