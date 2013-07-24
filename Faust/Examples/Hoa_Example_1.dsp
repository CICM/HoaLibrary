import("hoa.lib") ;
import("filter.lib") ;

interTime = nentry("Interpolation Time", 100., 0., 1000., 0.1) / 1000.;
x1 = hslider("Abscissa : Source 1", 0., -2, 2, 0.001) : smooth(tau2pole(interTime));
x2 = hslider("Abscissa : Source 2", -0.75, -2, 2, 0.001) : smooth(tau2pole(interTime));
x3 = hslider("Abscissa : Source 3", 0.75, -2, 2, 0.001) : smooth(tau2pole(interTime));
//z1 = tgroup("Absissa",(x1,x2,x3));
y1 = hslider("Ordinate : Source 1", 1., -2, 2, 0.001) : smooth(tau2pole(interTime));
y2 = hslider("Ordinate : Source 2", -0.75, -2, 2, 0.001) : smooth(tau2pole(interTime));
y3 = hslider("Ordinate : Source 3", -0.75, -2, 2, 0.001) : smooth(tau2pole(interTime));
//z2 = tgroup("Ordinate",(y1,y2,y3));

r1 = sqrt(x1*x1 + y1*y1);
r2 = sqrt(x2*x2 + y2*y2);
r3 = sqrt(x3*x3 + y3*y3);

a1 = atan2(y1, x1);
a2 = atan2(y2, x2);
a3 = atan2(y3, x3);

process(sig1,sig2,sig3) = map(7, sig1, r1, a1), map(7, sig2, r2, a2), map(7, sig3, r3, a3) :> optimInPhase(7) : decoderStereo(7);