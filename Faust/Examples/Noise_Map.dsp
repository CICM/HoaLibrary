import("hoa.lib") ;
import("filter.lib") ;
import("oscillator.lib");

radius = hslider("Source Radius", 0., 0, 10, 0.001) : smooth(tau2pole(0.02));
angle = hslider("Source Angle", 0., -2*PI, 2*PI, 0.001) : smooth(tau2pole(0.02));

process(sig) = map(7, sig, x1, y1) : optimInPhase(7) : decoderStereo(7);
