import("hoa.lib") ;
import("filter.lib") ;
import("oscillator.lib");

interTime = nentry("Interpolation Time", 100., 0., 1000., 0.1) / 1000.;
x1 = hslider("Source Abscissa", 0., -2, 2, 0.001) : smooth(tau2pole(interTime));
y1 = vslider("Source Ordinate", 1., -2, 2, 0.001) : smooth(tau2pole(interTime));

r1 = sqrt(x1*x1 + y1*y1);
a1 = atan2(y1, x1);

process = map(7, pink_noise*0.3, r1, a1) : optimInPhase(7) : decoderStereo(7);