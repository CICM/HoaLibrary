// 47jMarbles.js
// 
// Demonstrates how to set up a JitterListener object to listen
// to the output of a Jitter object instantiated within [js].
//
// rld, 7.05
//

var OBJECT_COUNT = 32; // number of little spheres

// create a [jit.window] object for our display 
// (this is the object we'll "listen" to):
var mywindow = new JitterObject("jit.window","ListenWindow");
// turn off depth testing... we're using blending instead:
mywindow.depthbuffer = 0; 
// turn ON idlemousing... we want to listen for it:
mywindow.idlemouse = 1; 

// create a [jit.gl.render] object for drawing into our window:
var myrender = new JitterObject("jit.gl.render","ListenWindow");
// use a 2-dimensional projection:
myrender.ortho = 2; 
// set background to black with full erase opacity (no trails):
myrender.erase_color = [0,0,0,1]; 

// create a [jit.gl.gridshape] object for use to control with the mouse
var mywidget = new JitterObject("jit.gl.gridshape","ListenWindow");
mywidget.shape = "sphere";
mywidget.lighting_enable = 1;
mywidget.smooth_shading = 1;
mywidget.scale = [0.1,0.1,0.1];
mywidget.color = [1,1,1,0.5] ;
mywidget.blend_enable = 1;
mywidget.position = [0,0]; // no z necessary in orthographic projection

// create an array of [jit.gl.gridshape] objects randomly arrayed across the window
var mysphere = new Array(OBJECT_COUNT);

// initialize our little spheres with random colors and positions (x,y)
for(var i=0;i<OBJECT_COUNT;i++) { 
	mysphere[i] = new JitterObject("jit.gl.gridshape","ListenWindow");
	mysphere[i].shape = "sphere";
	mysphere[i].lighting_enable = 1;
	mysphere[i].smooth_shading = 1;
	mysphere[i].scale = [0.05,0.05,0.05];
	mysphere[i].color = [Math.random(),Math.random(),Math.random(),0.5] ;
	mysphere[i].position = [Math.random()*2.-1, Math.random()*2.-1];
	mysphere[i].blend_enable = 1;
}

// create a JitterListener for our [jit.window] object
var mylistener = new JitterListener(mywindow.getregisteredname(), thecallback);

function randomize() // reorient the little spheres
{
	for(var i=0;i<32;i++) {
		mysphere[i].color = [Math.random(),Math.random(),Math.random(),0.5] ;
		mysphere[i].position = [Math.random()*2.-1, Math.random()*2.-1];
	}
}

function thecallback(event) 
// callback function to handle events triggered by mousing 
// in our [jit.window]
{
	var x,y,button; // some local variables

	if (event.eventname=="mouse") { 
	// we're entering, dragging within, or leaving a "mouse click" event

		// arguments are (x,y,button,cmd,shift,capslock,option,ctrl)... 
		// we only care about the first three
		x = event.args[0];
		y = event.args[1];
		button = event.args[2];
		if (button) // we're clicked down
		{
			mywidget.color = [0,1,0,1]; // color our control object green
			mywidget.shape = "torus"; // change it to a donut shape
		}
		else // we've just unclicked
		{
			mywidget.color = [1,0,0,1]; // color our object red
			mywidget.shape = "sphere"; // change back to a sphere
		}
	}
	else if (event.eventname=="mouseidle") { 
	// we're mousing over the window with the mouse up
		x = event.args[0];
		y = event.args[1];
		mywidget.color = [1,1,1,1] ; // color our object white
	}
	else if (event.eventname=="mouseidleout") { 
	// we're no longer mousing over the window
		x = event.args[0];
		y = event.args[1];
		mywidget.color = [1,1,1,0.5] ; // make our object translucent
	}

	// move our control object to the drawing context's 
	// equivalent of where our mouse event occurred:
	mywidget.position = myrender.screentoworld(x,y); 
}
// don't allow this function to be called from Max
thecallback.local = 1; 

function bang() 
// main drawing loop... figure out which little spheres to move 
// and drive the renderer
{
	// collision detection block. we need to iterate through 
	// the little spheres and check their distance from the control 
	// object. if we're touching we move the little sphere away 
	// along the correct angle of contact.
	for(var i = 0;i<OBJECT_COUNT;i++) { 
		// cartesian distance along the x and y axis
		var distx = mywidget.position[0]-mysphere[i].position[0]; 
		var disty = mywidget.position[1]-mysphere[i].position[1]; 

		// polar distance between the two objects
		var r = Math.sqrt(distx*distx+disty*disty); 
		// angle of little sphere around control object
		var theta = Math.atan2(disty,distx); 

		// check for collision...
		if(r<0.15) 
		// control object is size 0.1, little spheres are 0.05, 
		// so less than 0.15 and it's a hit...
		{
			// convert polar->cartesian to figure out x and y displacement
			var movex = (0.15-r)*Math.cos(theta); 
			var movey = (0.15-r)*Math.sin(theta); 

			// offset the little sphere to the new position, 
			// which should be just beyond touching at the 
			// angle of contact we had before. the result 
			// should look like we've "pushed" it along...
			mysphere[i].position = [mysphere[i].position[0]-movex, mysphere[i].position[1]-movey];
		}
	}

	// rendering block...
	myrender.erase(); // erase the drawing context
	myrender.drawclients(); // draw the client objects
	myrender.swap(); // swap in the new drawing
}

function fullscreen(v) 
// function to send the [jit.window] into fullscreen mode
{
	mywindow.fullscreen = v;
}

