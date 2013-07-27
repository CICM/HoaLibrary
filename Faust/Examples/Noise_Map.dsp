import("hoa.lib") ;
import("filter.lib") ;
import("oscillator.lib");

x1 = hslider("Source Radius", 0., 0, 10, 0.001) : smooth(tau2pole(0.02));
y1 = hslider("Source Angle", 1., -10, 10, 0.001) : smooth(tau2pole(0.02));

process(sig) = map(7, sig, x1, y1) : optimInPhase(7) : decoderStereo(7);
