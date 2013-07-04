// globaltask.js
//
// generate a stream of numbers timed to an exponentially
// decaying time curve.  arguments set the curve and the
// value to output.
//
// rld, 5.04
//

// inlets and outlets
inlets = 1;
outlets = 2;

// define global variables and set defaults
var tsk = new Task(mytask, this); // our main task
var count = 0;
var decay = 1.0;

// defaults for arguments
var dcoeff = -0.0002; // decay coefficient
var note = 60; // note to trigger upon bounce

// process arguments (decay coefficient, note to trigger)
if(jsarguments.length>1) // argument 0 is the name of the js file
{
	dcoeff = jsarguments[1];
}
if(jsarguments.length>2) 
{
	note = jsarguments[2];
}

// Global (Max namespace) variables
glob = new Global("bounce");
glob.starttime = 500;

// bang -- start the task
function bang()
{
	tsk.cancel(); // cancel the bounce, if it's going already
	count = 0; // reset the number of bounces
	decay = 1.0; // reset the initial decay
	tsk.interval = glob.starttime; // set the initial task interval
	tsk.repeat(); // start the bouncing
}

// stop -- allow the user to stop the bouncing
function stop()
{
	tsk.cancel(); // cancel our task
}

// mytask -- the scheduled task - output number and reschedule next task
function mytask()
{
	if(arguments.callee.task.interval>5) // keep bouncing
	{
		outlet(0, note); // send a note value
		decay = decay*Math.exp(++count*dcoeff); // increment the decay variable
		arguments.callee.task.interval=arguments.callee.task.interval*decay; // update the task interval
	}
	else // bounce interval is too small, so consider it 'floored'
	{
		arguments.callee.task.cancel(); // cancel the task
		outlet(1, bang); // send a bang out the right outlet to signify that we're done bouncing
	}
}
mytask.local = 1; // prevent triggering the task directly from Max
