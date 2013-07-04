// autosurface.js
//
// automatically generate a MIDI control surface with
// visual feedback (sliders), hook it up to a funnel
// object, and use it to drive a simple sequencer.
//
// rld, 5.04
//

// inlets and outlets
inlets = 1;
outlets = 2;

// global variables and arrays
var numsliders = 0;
var seqcounter = 0;
var thereverse = 0;
var thevalues = new Array(128);

// Maxobj variables for scripting
var controlin = new Array(128);
var thesliders = new Array(128);
var thefunnel;

// methods start here

// sliders -- generates and binds the sliders in the max patch
function sliders(val)
{

	if(arguments.length) // bail if no arguments
	{
		// parse arguments
		a = arguments[0];

		// safety check for number of sliders
		if(a<0) a = 0; // too few sliders, set to 0
		if(a>128) a = 128; // too many sliders, set to 128

		// out with the old...
		if(numsliders) this.patcher.remove(thefunnel); // if we've done this before, get rid of the funnel
		for(i=0;i<numsliders;i++) // get rid of the ctlin and uslider objects using the old number of sliders
		{
			this.patcher.remove(controlin[i]);
			this.patcher.remove(thesliders[i]);
		}

		// ...in with the new
		numsliders = a; // update our global number of sliders to the new value
		if(numsliders) thefunnel = this.patcher.newdefault(300, 300, "funnel", a); // make the funnel
		for(k=0;k<a;k++) // create the new ctlin and uslider objects, connect them to one another and to the funnel
		{
			controlin[k] = this.patcher.newdefault(300+(k*100), 50, "ctlin", k+1);
			thesliders[k] = this.patcher.newdefault(300+(k*100), 100, "uslider");
			this.patcher.connect(controlin[k], 0, thesliders[k], 0);
			this.patcher.connect(thesliders[k], 0, thefunnel, k);
		}

		// connect new objects to this js object's inlet
		ourself = this.box; // assign a Maxobj to our js object
		if (numsliders) this.patcher.connect(thefunnel, 0, ourself, 0); // connect the funnel to us
	}

	else // complain about arguments
	{
		post("sliders message needs arguments");
		post();
	}
}

// list -- read from the created funnel object
function list(val)
{
	if(arguments.length==2)
	{
		thevalues[arguments[0]] = arguments[1];
	}
}

// bang -- steps through sequencer
function bang()
{
	if(seqcounter>=numsliders) // reset sequencer
	{
		seqcounter = 0;
	}
	if(thereverse) // read from the array backwards
	{
		outlet(1, numsliders-seqcounter-1); // send out our location in the sequence
		outlet(0, thevalues[numsliders-seqcounter-1]); // send out the current note
	}
	else // read from the array forwards
	{
		outlet(1, seqcounter); // sound out our location in the sequence
		outlet(0, thevalues[seqcounter]); // send out the current note
	}
	seqcounter++; // increment the sequence
}

// reverse -- changes sequence direction
function reverse(val)
{
	if(arguments.length) 
	{
		thereverse = arguments[0]; // flip it
	}
}

