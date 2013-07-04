// mymatrix.js
//
// simulates a simple grid of clickable widgets (a la matrixctrl)
//
// rld, 5.04
//

// inlets and outlets
inlets = 1;
outlets = 1;

// global variables
var ncols=4; // default columns
var nrows=4; // default rows

var vbrgb = [0.8,1.,0.8,0.5];
var vmrgb = [0.9,0.5,0.5,0.75];
var vfrgb = [1.,0.,0.2,1.];

// initialize state array
var state = new Array(8);
for(i=0;i<8;i++) 
{
	state[i] = new Array(8);
	for(j=0;j<64;j++) 
	{
		state[i][j] = 0;
	}
}

// set up jsui defaults to 2d
sketch.default2d();

// initialize graphics
draw();
refresh();

// draw -- main graphics function
function draw()
{
	with (sketch) 
	{
		// set how the polygons are rendered
		glclearcolor(vbrgb[0],vbrgb[1],vbrgb[2],vbrgb[3]); // set the clear color
		glclear(); // erase the background
		colstep=2./ncols; // how much to move over per column
		rowstep=2./nrows; // how much to move over per row
		for(i=0;i<ncols;i++) // iterate through the columns
		{	
			for(j=0;j<nrows;j++) // iterate through the rows
			{
				moveto((i*colstep + colstep/2)-1.0, 1.0 - (j*rowstep + rowstep/2), 0.); // move the drawing point
				if(state[i][j]) // set 'on' color
				{
					glcolor(vfrgb[0],vfrgb[1],vfrgb[2],vfrgb[3]);
				}
				else // set 'off' color (midway between vbrgb and vfrgb)
				{
					glcolor(vmrgb[0],vmrgb[1],vmrgb[2],vmrgb[3]);
				}
				circle(0.7/Math.max(nrows,ncols)); // draw the circle
			}
		}					
	}
}

// bang -- draw and refresh display
function bang()
{
	draw();
	refresh();
}

// rows -- change number of rows in jsui
function rows(val)
{
	if(arguments.length) 
	{
		nrows=arguments[0];
		bang(); // draw and refresh display
	}
}


// cols -- change number of columns is jsui
function cols(val)
{
	if(arguments.length) 
	{
		ncols=arguments[0];
		bang(); // draw and refresh display
	}
}

// list -- update our state to respond to a change from Max
function list(v)
{
	if(arguments.length==3) // bail if incorrect number of arguments
	{
		state[arguments[0]][arguments[1]]=arguments[2]; // update our internal state based on the list
		outlet(0, arguments[0], arguments[1], arguments[2]); // echo the list out the outlet	
	}
	bang(); // draw and refresh display
}

// clear -- wipe the state clean
function clear()
{
	for(i=0;i<ncols;i++)
	{
		for(j=0;j<nrows;j++)
		{
			state[i][j]=0; // wipe the state
		}
	}
	outlet(0, "clear"); // clear the router or matrix~ downstream
	bang(); // draw and refresh display
}

// frgb -- change foreground (clicked) sphere color
function frgb(r,g,b)
{
	vfrgb[0] = r/255.;
	vfrgb[1] = g/255.;
	vfrgb[2] = b/255.;
	vmrgb[0] = 0.5*(vfrgb[0]+vbrgb[0]);
	vmrgb[1] = 0.5*(vfrgb[1]+vbrgb[1]);
	vmrgb[2] = 0.5*(vfrgb[2]+vbrgb[2]);
	bang(); // draw and refresh display
}

// brgb -- change background color
function brgb(r,g,b)
{
	vbrgb[0] = r/255.;
	vbrgb[1] = g/255.;
	vbrgb[2] = b/255.;
	vmrgb[0] = 0.5*(vfrgb[0]+vbrgb[0]);
	vmrgb[1] = 0.5*(vfrgb[1]+vbrgb[1]);
	vmrgb[2] = 0.5*(vfrgb[2]+vbrgb[2]);
	bang(); // draw and refresh display
}

// onresize -- deal with a resized jsui box
function onresize(w,h)
{
	bang(); // draw and refresh display
}
onresize.local = 1; // make function private to prevent triggering from Max


// onclick -- deal with mouse click event
function onclick(x,y)
{
	worldx = sketch.screentoworld(x,y)[0];
	worldy = sketch.screentoworld(x,y)[1];

	colwidth = 2./ncols; // width of a column, in world coordinates
	rowheight = 2./nrows; // width of a row, in world coordinates

	x_click = Math.floor((worldx+1.)/colwidth); // which column we clicked
	y_click = Math.floor((1.-worldy)/rowheight); // which row we clicked

	state[x_click][y_click] = !state[x_click][y_click]; // flip the state of the clicked point
	outlet(0, x_click, y_click, state[x_click][y_click]); // output the coordinates and state of the clicked point

	bang(); // draw and refresh display
}
onclick.local = 1; // make function private to prevent triggering from Max

// ondblclick -- pass buck to onclick()
function ondblclick(x,y)
{
	onclick(x,y);
}
ondblclick.local = 1; // make function private to prevent triggering from Max
