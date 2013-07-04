// popu.js
//
// simulates the logistic population equation:
// f(x) = rx(1-x)
// 
// input is r.  output is current x.
//
// rld, 5.04
//

// inlets and outlets
inlets = 1;
outlets = 1;

// global variables
var x = 0.66;

// float -- run the equation once
function msg_float(r)
{
	x = r*x*(1.-x);
	outlet(0, x);
}

// bang -- post the current population to the max window
function bang()
{
	post("the current population is");
	post(x);
	post();
}