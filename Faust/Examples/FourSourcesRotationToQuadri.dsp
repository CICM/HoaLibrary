declare name 		"OneSourceToStereo";
declare version 	"1.0";
declare author 		"CICM";
declare license 	"BSD";
declare copyright 	"(c)CICM 2013";

import("hoa.lib") ;
import("filter.lib") ;
import("oscillator.lib");

angle = hslider("Angle", 0., -PI*2, 2*PI, 0.001) : smooth(tau2pole(0.02));

process(sig1) = map(3, sig1, 1., 0.) : optimInPhase(3) ;
