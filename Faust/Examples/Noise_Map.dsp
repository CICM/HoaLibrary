import("hoa.lib") ;
import("filter.lib") ;
import("oscillator.lib");

interTime = nentry("Interpolation Time (ms)", 100., 0., 1000., 0.1) / 1000.;
x1 = hslider("Source Radius", 0., 0, 10, 0.001) : smooth(tau2pole(interTime));
y1 = hslider("Source Angle", 1., -10, 10, 0.001) : smooth(tau2pole(interTime));

process = map(7, pink_noise*0.3, x1, y1) : optimInPhase(7) : decoderStereo(7);