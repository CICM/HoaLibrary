#ifndef GENLIB_OPS_H
#define GENLIB_OPS_H 1

#include "genlib_common.h"	// common to common code and any host code
#include "genlib.h"			// this file is different for different "hosts"

//////////// genlib_ops.h ////////////

// system constants
#define GENLIB_DBL_EPSILON (__DBL_EPSILON__)

#define GENLIB_PI (3.14159265358979323846264338327950288)
#define GENLIB_PI_OVER_2 (1.57079632679489661923132169163975144)
#define GENLIB_PI_OVER_4 (0.785398163397448309615660845819875721)
#define GENLIB_1_OVER_LOG_2 (1.442695040888963)

// denormal numbers cannot occur when hosted in MSP:
#ifdef MSP_ON_CLANG
	#define GENLIB_NO_DENORM_TEST 1
#endif

// assumes v is a 64-bit double:
#define GENLIB_IS_NAN_DOUBLE(v)			(((((uint32_t *)&(v))[1])&0x7fe00000)==0x7fe00000) 
#define GENLIB_FIX_NAN_DOUBLE(v)		((v)=GENLIB_IS_NAN_DOUBLE(v)?0.:(v))

#ifdef GENLIB_NO_DENORM_TEST
	#define GENLIB_IS_DENORM_DOUBLE(v)	(v)
	#define GENLIB_FIX_DENORM_DOUBLE(v)	(v)
#else
	#define GENLIB_IS_DENORM_DOUBLE(v)	((((((uint32_t *)&(v))[1])&0x7fe00000)==0)&&((v)!=0.))
	#define GENLIB_FIX_DENORM_DOUBLE(v)	((v)=GENLIB_IS_DENORM_DOUBLE(v)?0.f:(v))
#endif

#define GENLIB_QUANT(f1,f2)			(floor((f1)*(f2)+0.5)/(f2))

inline double genlib_isnan(double v) { return GENLIB_IS_NAN_DOUBLE(v); }
inline double fixnan(double v) { return GENLIB_FIX_NAN_DOUBLE(v); }
inline double fixdenorm(double v) { return GENLIB_FIX_DENORM_DOUBLE(v); }
inline double isdenorm(double v) { return GENLIB_IS_DENORM_DOUBLE(v); }

inline double safemod(double f, double m) {
	if (m > GENLIB_DBL_EPSILON || m < -GENLIB_DBL_EPSILON) {
		if (m<0) 
			m = -m; // modulus needs to be absolute value		
		if (f>=m) {
			if (f>=(m*2.)) {
				double d = f / m;
				d = d - (long) d;
				f = d * m;
			} 
			else {
				f -= m;
			}
		} 
		else if (f<=(-m)) {
			if (f<=(-m*2.)) {
				double d = f / m;
				d = d - (long) d;
				f = d * m;
			}
			 else {
				f += m;
			}
		}
	} else {
		f = 0.0; //don't divide by zero
	}
	return f;
}


inline double safediv(double num, double denom) {
	return denom == 0. ? 0. : num/denom;
}

// fixnan for case of negative base and non-integer exponent:
inline double safepow(double base, double exponent) {
	return fixnan(pow(base, exponent));
}

inline double absdiff(double a, double b) { return fabs(a-b); }

inline double exp2(double v) { return pow(2., v); }

inline double trunc(double v) {
	double epsilon = (v<0.0) * -2 * 1E-9 + 1E-9;
	// copy to long so it gets truncated (probably cheaper than floor())
	long val = v + epsilon;
	return val;
}

inline double sign(double v) { return v > 0. ? 1. : v < 0. ? -1. : 0.; }

inline long is_poweroftwo(long x) {
	return (x & (x - 1)) == 0;
}

inline uint64_t next_power_of_two(uint64_t v) {
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v |= v >> 32;
    v++;
    return v;
}

inline double fold(double v, double lo1, double hi1){
	double lo;
	double hi;
	if(lo1 == hi1){ return lo1; }
	if (lo1 > hi1) {	
		hi = lo1; lo = hi1;
	} else {
		lo = lo1; hi = hi1;
	}
	const double range = hi - lo;
	long numWraps = 0;
	if(v >= hi){
		v -= range;
		if(v >= hi){
			numWraps = (long)((v - lo)/range);
			v -= range * (double)numWraps;
		}
		numWraps++;
	} else if(v < lo){
		v += range;
		if(v < lo){
			numWraps = (long)((v - lo)/range) - 1;
			v -= range * (double)numWraps;
		}
		numWraps--;
	}
	if(numWraps & 1) v = hi + lo - v;	// flip sign for odd folds
	return v;
}

inline double wrap(double v, double lo1, double hi1){
	double lo;
	double hi;
	if(lo1 == hi1) return lo1;
	if (lo1 > hi1) {	
		hi = lo1; lo = hi1;
	} else {
		lo = lo1; hi = hi1;
	}
	const double range = hi - lo;
	if (v >= lo && v < hi) return v;
	if (range <= 0.000000001) return lo;	// no point... 
	const long numWraps = long((v-lo)/range) - (v < lo);
	return v - range * double(numWraps);
}

// this version gives far better performance when wrapping is relatively rare
// and typically double of wraps is very low (>1%)
// but catastrophic if wraps is high (1000%+)
inline double wrapfew(double v, double lo, double hi){
	const double range = hi - lo;
	while (v >= hi) v -= range;
	while (v < lo) v += range;
	return v;
}

inline double phasewrap_few(double val) {
	return wrapfew(val, -GENLIB_PI, GENLIB_PI);
}

inline double phasewrap(double val) {
	const double twopi = GENLIB_PI*2.;
	const double oneovertwopi = 1./twopi;
	if (val>= twopi || val <= twopi) {
		double d = val * oneovertwopi;	//multiply faster
		d = d - (long)d;
		val = d * twopi;
	}	
	if (val > GENLIB_PI) val -= twopi;
	if (val < -GENLIB_PI) val += twopi;
	return val;
}

/// 8th order Taylor series approximation to a cosine.
/// r must be in [-pi, pi].
inline double cosT8(double r) {
	const double t84 = 56.;
	const double t83 = 1680.;
	const double t82 = 20160.;
	const double t81 = 2.4801587302e-05;
	const double t73 = 42.;
	const double t72 = 840.;
	const double t71 = 1.9841269841e-04;
	if(r < GENLIB_PI_OVER_4 && r > -GENLIB_PI_OVER_4){
		double rr = r*r;
		return 1. - rr * t81 * (t82 - rr * (t83 - rr * (t84 - rr)));
	}
	else if(r > 0.){
		r -= GENLIB_PI_OVER_2;
		double rr = r*r;
		return -r * (1. - t71 * rr * (t72 - rr * (t73 - rr)));
	}
	else{
		r += GENLIB_PI_OVER_2;
		double rr = r*r;
		return r * (1. - t71 * rr * (t72 - rr * (t73 - rr)));
	}
}

inline double sin_fast(const double r){
	const double y = (4./GENLIB_PI) * r + (-4./(GENLIB_PI*GENLIB_PI)) * r * fabs(r);
	return 0.225 * (y * fabs(y) - y) + y;   // Q * y + P * y * abs(y)
}

inline double sinP7(double n){
	double nn = n*n;
	return n * (3.138982 + nn * (-5.133625 + nn * (2.428288 - nn * 0.433645)));
}

inline double sinP9(double n){
	double nn = n*n;
	return n * (GENLIB_PI + nn * (-5.1662729 + nn * (2.5422065 + nn * (-0.5811243 + nn * 0.0636716))));
}

inline double sinT7(double r){
	const double t84 = 56.;
	const double t83 = 1680.;
	const double t82 = 20160.;
	const double t81 = 2.4801587302e-05;
	const double t73 = 42.;
	const double t72 = 840.;
	const double t71 = 1.9841269841e-04;
	if(r < GENLIB_PI_OVER_4 && r > -GENLIB_PI_OVER_4){
		double rr = r*r;
		return r * (1. - t71 * rr * (t72 - rr * (t73 - rr)));
	}
	else if(r > 0.){
		r -= GENLIB_PI_OVER_2;
		double rr = r*r;
		return 1. - rr * t81 * (t82 - rr * (t83 - rr * (t84 - rr)));
	}
	else{
		r += GENLIB_PI_OVER_2;
		double rr = r*r;
		return -1. + rr * t81 * (t82 - rr * (t83 - rr * (t84 - rr)));
	}
}

// use these if r is not known to be in [-pi, pi]:
inline double cosT8_safe(double r) { return cosT8(phasewrap(r)); }
inline double sin_fast_safe(double r) { return sin_fast(phasewrap(r)); }
inline double sinP7_safe(double r) { return sinP7(phasewrap(r)); }
inline double sinP9_safe(double r) { return sinP9(phasewrap(r)); }
inline double sinT7_safe(double r) { return sinT7(phasewrap(r)); }

inline double minimum(double x, double y) { return (y<x?y:x); }
inline double maximum(double x, double y) { return (x<y?y:x); }

inline double clamp(double x, double minVal, double maxVal) { 
	return minimum(maximum(x,minVal),maxVal); 
}

template<typename T>
inline T smoothstep(double e0, double e1, T x) {
	T t = clamp( safediv(x-T(e0),T(e1-e0)), 0., 1. );
	return t*t*(T(3) - T(2)*t);
}

inline double mix(double x, double y, double a) { 
	return x+a*(y-x); 
}

double scale(double in, double inlow, double inhigh, double outlow, double outhigh, double power)
{
	double value;
	double inscale = safediv(1., inhigh - inlow);
	double outdiff = outhigh - outlow;
	
	value = (in - inlow) * inscale;
	if (value > 0.0)
		value = pow(value, power);
	else if (value < 0.0)
		value = -pow(-value, power);
	value = (value * outdiff) + outlow;
	
	return value;
}

inline double linear_interp(double a, double x, double y) {
	return x+a*(y-x); 
}

inline double cosine_interp(double a, double x, double y) {
	const double a2 = (1.-cosT8_safe(a*GENLIB_PI))/2.;
	return(x*(1.-a2)+y*a2);
}

inline double cubic_interp(double a, double w, double x, double y, double z) {
	const double a2 = a*a;
	const double f0 = z - y - w + x;
	const double f1 = w - x - f0;
	const double f2 = y - w;
	const double f3 = x;
	return(f0*a*a2 + f1*a2 + f2*a + f3);
}

// Breeuwsma catmull-rom spline interpolation
inline double spline_interp(double a, double w, double x, double y, double z) {
	const double a2 = a*a;
	const double f0 = -0.5*w + 1.5*x - 1.5*y + 0.5*z;
	const double f1 = w - 2.5*x + 2*y - 0.5*z;
	const double f2 = -0.5*w + 0.5*y;
	return(f0*a*a2 + f1*a2 + f2*a + x);
}

template<typename T1, typename T2>
inline T1 neqp(T1 x, T2 y) { 
	return ((((x) != T1(y))) ? (x) : T1(0));
}

template<typename T1, typename T2>
inline T1 gtp(T1 x, T2 y) { return ((((x) > T1(y))) ? (x) : T1(0)); }
template<typename T1, typename T2>
inline T1 gtep(T1 x, T2 y) { return ((((x) >= T1(y))) ? (x) : T1(0)); }
template<typename T1, typename T2>
inline T1 ltp(T1 x, T2 y) { return ((((x) < T1(y))) ? (x) : T1(0)); }
template<typename T1, typename T2>
inline T1 ltep(T1 x, T2 y) { return ((((x) <= T1(y))) ? (x) : T1(0)); }

inline double fract(double x) { double unused; return modf(x, &unused); }

// log2(x) = log(x)/log(2)
template<typename T>
inline T log2(T x) { 
	return log(x)*GENLIB_1_OVER_LOG_2; 
}

inline double atodb(double in) {
	return (in <=0.) ? -999. : (20. * log10(in));
}

inline double dbtoa(double in) {
	return pow(10., in * 0.05);
}

inline double ftom(double in, double tuning=440.) {
	return 69. + 17.31234050465299 * log(safediv(in, tuning));
}

inline double mtof(double in, double tuning=440.) {
	return tuning * exp(.057762265 * (in - 69.0));
}

inline double mstosamps(double ms, double samplerate=44100.) {
	return samplerate * ms * 0.001;
}

inline double sampstoms(double s, double samplerate=44100.) {
	return 1000. * s / samplerate;
}

inline double triangle(double phase, double p1) {
	phase = wrap(phase, 0., 1.);
	p1 = clamp(p1, 0., 1.);
	if (phase < p1)
		return (p1) ? phase/p1 : 0.;
	else
		return (p1==1.) ? phase : 1. - ((phase - p1) / (1. - p1));
}

struct Delta {
	double history;
	Delta() { reset(); }
	inline void reset(double init=0) { history=init; }
	
	inline double operator()(double in1) {
		double ret = in1 - history;
		history = in1;
		return ret;
	}
};
struct Change {
	double history;
	Change() { reset(); }
	inline void reset(double init=0) { history=init; }
	
	inline double operator()(double in1) {
		double ret = in1 - history;
		history = in1;
		return sign(ret);
	}
};

struct Rate {
	double phase, diff, mult, invmult, prev;
	int wantlock, quant;
	
	Rate() { reset(); }
	
	inline void reset() {
		phase = diff = prev = 0;
		mult = invmult = 1;
		wantlock = 1;
		quant = 1;
	}
	
	inline double perform_lock(double in1, double in2) {
		// did multiplier change?
		if (in2 != mult && !genlib_isnan(in2)) {
			mult = in2;
			invmult = safediv(1., mult);
			wantlock = 1;
		}
		double diff = in1 - prev;
		
		if (diff < -0.5) {
			diff += 1;
		} else if (diff > 0.5) {
			diff -= 1;
		}
		
		if (wantlock) {
			// recalculate phase
			phase = (in1 - GENLIB_QUANT(in1, quant)) * invmult 
						+ GENLIB_QUANT(in1, quant * mult);
			diff = 0;
			wantlock = 0;
		} else {
			// diff is always between -0.5 and 0.5
			phase += diff * invmult;
		}
		
		if (phase > 1. || phase < -0.) {
			phase = phase - (long)(phase);
		}	
		
		prev = in1;
		
		return phase;
	}
	
	inline double perform_cycle(double in1, double in2) {
		// did multiplier change?
		if (in2 != mult && !genlib_isnan(in2)) {
			mult = in2;
			invmult = safediv(1., mult);
			wantlock = 1;
		}
		double diff = in1 - prev;
		
		if (diff < -0.5) {
			if (wantlock) {
				wantlock = 0;
				phase = in1 * invmult;
				diff = 0;
			} else {
				diff += 1;
			}
		} else if (diff > 0.5) {
			if (wantlock) {
				wantlock = 0;
				phase = in1 * invmult;
				diff = 0;
			} else {
				diff -= 1;
			}
		}
		
		// diff is always between -0.5 and 0.5
		phase += diff * invmult;
		
		if (phase > 1. || phase < -0.) {
			phase = phase - (long)(phase);
		}	
		
		prev = in1;
		
		return phase;
	}
	
	inline double perform_off(double in1, double in2) {
		// did multiplier change?
		if (in2 != mult && !genlib_isnan(in2)) {
			mult = in2;
			invmult = safediv(1., mult);
			wantlock = 1;
		}
		double diff = in1 - prev;
		
		if (diff < -0.5) {
			diff += 1;
		} else if (diff > 0.5) {
			diff -= 1;
		}
		
		phase += diff * invmult;
		
		if (phase > 1. || phase < -0.) {
			phase = phase - (long)(phase);
		}	
		
		prev = in1;
		
		return phase;
	}
};

struct DCBlock {
	double x1, y1;
	DCBlock() { reset(); }
	inline void reset() { x1=0; y1=0; }
	
	inline double operator()(double in1) {
		double y = in1 - x1 + y1*0.9997;
		x1 = in1;
		y1 = y;
		return y;
	}
};

struct Noise {
	unsigned long last;
	static long uniqueTickCount(void) {
		static long lasttime = 0;
		long time = genlib_ticks();
		return (time <= lasttime) ? (++lasttime) : (lasttime = time);
	}
	
	Noise() { reset(); }
	Noise(double seed) { reset(seed); }
	void reset() { last = uniqueTickCount() * uniqueTickCount(); }
	void reset(double seed) { last = seed; }
	
	inline double operator()() {
		last = 1664525L * last + 1013904223L;
		unsigned long itemp = 0x3f800000 | (0x007fffff & last);
		return ((*(float *)&itemp) * 2.0) - 3.0;
	}
};

struct Phasor {
	double phase;
	Phasor() { reset(); }
	void reset(double v=0.) { phase=v; }
	inline double operator()(double freq, double invsamplerate) {
		const double pincr = freq * invsamplerate;
		//phase = wrapfew(phase + pincr, 0., 1.); // faster for low frequencies, but explodes with high frequencies
		phase = wrap(phase + pincr, 0., 1.);
		return phase;
	}
};

struct PlusEquals {
	double count;
	PlusEquals() { reset(); }
	void reset(double v=0.) { count=v; }
	inline double operator()(double incr, double reset, double min, double max) {
		count = reset ? min : wrap(count+incr, min, max);
		return count;
	}
	inline double operator()(double incr=1., double reset=0., double min=0.) {
		count = reset ? min : count+incr;
		return count;
	}
};

struct MulEquals {
	double count;
	MulEquals() { reset(); }
	void reset(double v=0.) { count=v; }
	inline double operator()(double incr, double reset, double min, double max) {
		count = reset ? min : wrap(fixdenorm(count*incr), min, max);
		return count;
	}
	inline double operator()(double incr=1., double reset=0., double min=0.) {
		count = reset ? min : fixdenorm(count*incr);
		return count;
	}
};

struct Sah {
	double prev, output;
	Sah() { reset(); }
	void reset(double o=0.) {
		output = prev = o;
	}
	
	inline double operator()(double in, double trig, double thresh) {
		if (prev <= thresh && trig > thresh) {
			output = in;
		}
		prev = trig;
		return output;
	}
};

struct Train {
	double phase;
	double state;
	Train() { reset(); }
	void reset(double p=0) { phase = p; state = 0.; }
	
	inline double operator()(double pulseinterval, double width, double pulsephase) {
		if (width <= 0.) {
			state = 0.;	// no pulse!
		} else if (width >= 1.) {
			state = 1.; // constant pulse!
		} else {
			const double interval = maximum(pulseinterval, 1.);	// >= 1.
			const double p1 = clamp(pulsephase, 0., 1.);	// [0..1]
			const double p2 = p1+width;						// (p1..p1+1)
			const double pincr = 1./interval;				// (0..1]
			phase += pincr;									// +ve
			if (state) {	// on:
				if (phase > p2) {	
					state = 0.;				// turn off
					phase -= (int)(1.+phase-p2);	// wrap phase back down
				}
			} else {		// off:
				if (phase > p1) {			
					state = 1.;				// turn on.
				}
			}
		}
		return state;
	}	
};

struct Delay {
	double * memory;
	long size, wrap, maxdelay;
	long reader, writer;
	
	t_genlib_data * dataRef;
	
	Delay() : memory(0) {
		size = wrap = maxdelay = 0;
		reader = writer = 0;
		dataRef = 0;
	}
	~Delay() {
		if (dataRef != 0) {
			// store write position for persistence:
			genlib_data_setcursor(dataRef, writer);
			// decrement reference count:
			genlib_data_release(dataRef);
		}
	}
	
	inline void reset(const char * name, long d) {
		// if needed, acquire the Data's global reference: 
		if (dataRef == 0) {
		
			void * ref = genlib_obtain_reference_from_string(name);
			dataRef = genlib_obtain_data_from_reference(ref);
			if (dataRef == 0) {	
				genlib_report_error("failed to acquire data");
				return; 
			}
			
			// scale maxdelay to next highest power of 2:
			maxdelay = d;
			size = maximum(maxdelay,2);
			size = next_power_of_two(size);
			
			// first reset should resize the memory:
			genlib_data_resize(dataRef, size, 1);
			
			t_genlib_data_info info;
			if (genlib_data_getinfo(dataRef, &info) == GENLIB_ERR_NONE) {
				if (info.dim != size) {
					// at this point, could resolve by reducing to 
					// maxdelay = size = next_power_of_two(info.dim+1)/2;
					// but really, if this happens, it means more than one
					// object is referring to the same t_gen_dsp_data.
					// which is probably bad news.
					genlib_report_error("delay memory size error");
					memory = 0;
					return;
				}
				memory = info.data;
				writer = genlib_data_getcursor(dataRef);
			} else {
				genlib_report_error("failed to acquire data info");
			}
		
		} else {		
			// subsequent reset should zero the memory & heads:
			set_zero64(memory, size);
			writer = 0;
		}
		
		reader = writer;
		wrap = size-1;
	}
	
	// called at bufferloop end, updates read pointer time
	inline void step() {	
		reader++; 
		if (reader >= size) reader = 0;
	}
	
	inline void write(double x) {
		writer = reader;	// update write ptr
		memory[writer] = x;
	}	
	
	inline double read_step(double d) {
		// extra half for nice rounding:
		// min 1 sample delay for read before write (r != w)
		const double r = double(size + reader) - clamp(d-0.5, (reader != writer), maxdelay);	
		long r1 = long(r);
		return memory[r1 & wrap];
	}
	
	inline double read_linear(double d) {
		// min 1 sample delay for read before write (r != w)
		double c = clamp(d, (reader != writer), maxdelay);
		const double r = double(size + reader) - c;	
		long r1 = long(r);
		long r2 = r1+1;
		double a = r - (double)r1;
		double x = memory[r1 & wrap];
		double y = memory[r2 & wrap];
		return linear_interp(a, x, y);
	}
	
	inline double read_cosine(double d) {
		// min 1 sample delay for read before write (r != w)
		const double r = double(size + reader) - clamp(d, (reader != writer), maxdelay);	
		long r1 = long(r);
		long r2 = r1+1;
		double a = r - (double)r1;
		double x = memory[r1 & wrap];
		double y = memory[r2 & wrap];
		return cosine_interp(a, x, y);
	}
	
	// cubic requires extra sample of compensation:
	inline double read_cubic(double d) {
		// min 1 sample delay for read before write (r != w)
		// plus extra 1 sample compensation for 4-point interpolation
		const double r = double(size + reader) - clamp(d, 1.+(reader != writer), maxdelay);	
		long r1 = long(r);
		long r2 = r1+1;
		long r3 = r1+2;
		long r4 = r1+3;
		double a = r - (double)r1;
		double w = memory[r1 & wrap];
		double x = memory[r2 & wrap];
		double y = memory[r3 & wrap];
		double z = memory[r4 & wrap];
		return cubic_interp(a, w, x, y, z);
	}
	
	// spline requires extra sample of compensation:
	inline double read_spline(double d) {
		// min 1 sample delay for read before write (r != w)
		// plus extra 1 sample compensation for 4-point interpolation
		const double r = double(size + reader) - clamp(d, 1.+(reader != writer), maxdelay);	
		long r1 = long(r);
		long r2 = r1+1;
		long r3 = r1+2;
		long r4 = r1+3;
		double a = r - (double)r1;
		double w = memory[r1 & wrap];
		double x = memory[r2 & wrap];
		double y = memory[r3 & wrap];
		double z = memory[r4 & wrap];
		return spline_interp(a, w, x, y, z);
	}
};

template<typename T>
struct DataInterface {
	long dim, channels;
	T * mData;
	void * mDataReference;		// this was t_symbol *mName
	int modified;
	
	DataInterface() : dim(0), channels(1), mData(0), modified(0) { mDataReference = 0; }
	
	// raw reading/writing/overdubbing (internal use only, no bounds checking)
	inline double read(long index, long channel=0) const { 
		return mData[channel+index*channels]; 
	}	
	inline void write(double value, long index, long channel=0) {
		mData[channel+index*channels] = value; 
		modified = 1;
	}
	inline void overdub(double value, long index, long channel=0) { 
		mData[channel+index*channels] += value; 
		modified = 1;
	}
	
	// averaging overdub (used by splat)
	inline void blend(double value, long index, long channel, double alpha) { 
		long offset = channel+index*channels;
		const double old = mData[offset];
		mData[offset] = old + alpha * (value - old); 
		modified = 1;
	}
	
	inline void read_ok(long index, long channel=0, bool ok=1) const { 
		return ok ? mData[channel+index*channels] : T(0); 
	}	
	inline void write_ok(double value, long index, long channel=0, bool ok=1) { 
		if (ok) mData[channel+index*channels] = value; 
	}
	inline void overdub_ok(double value, long index, long channel=0, bool ok=1) { 
		if (ok) mData[channel+index*channels] += value; 
	}
		
	// Bounds strategies:
	inline long index_clamp(long index) const { return clamp(index, 0, dim-1); } 
	inline long index_wrap(long index) const { return wrap(index, 0, dim); } 
	inline long index_fold(long index) const { return fold(index, 0, dim); } 
	inline bool index_oob(long index) const { return (index < 0 || index >= dim); } 
	inline bool index_inbounds(long index) const { return (index >=0 && index < dim); } 
	
	// channel bounds:
	inline long channel_clamp(long c) const { return clamp(c, 0, channels-1); }
	inline long channel_wrap(long c) const { return wrap(c, 0, channels); } 
	inline long channel_fold(long c) const { return fold(c, 0, channels); } 
	inline bool channel_oob(long c) const { return (c < 0 || c >= channels); }
	inline bool channel_inbounds(long c) const { return !channel_oob(c); } 

	// Indexing strategies:
	// [0..1] -> [0..(dim-1)]
	inline double phase2index(double phase) const { return phase * (dim-1); }
	// [0..1] -> [min..max]
	inline double subphase2index(double phase, long min, long max) const { 
		min = index_clamp(min);
		max = index_clamp(max);
		return min + phase * (max-min); 
	}
	// [-1..1] -> [0..(dim-1)]
	inline double signal2index(double signal) const { return phase2index((signal+1.) * 0.5); }
	
	inline double peek(double index, long channel=0) const {
		const long i = (long)index;
		if (index_oob(i) || channel_oob(channel)) {
			return 0.;
		} else {
			return read(i, channel);
		}
	}
	
	inline double index(double index, long channel=0) const {
		channel = channel_clamp(channel);
		// no-interp:
		long i = (long)index;
		// bound:
		i = index_clamp(i);
		return read(i, channel);
	}
	
	inline double cell(double index, long channel=0) const {
		channel = channel_clamp(channel);
		// no-interp:
		long i = (long)index;
		// bound:
		i = index_wrap(i);
		return read(i, channel);
	}
	
	inline double cycle(double phase, long channel=0) const {
		channel = channel_clamp(channel);
		double index = phase2index(phase);
		// interp:
		long i1 = (long)index;
		long i2 = i1+1;
		const double alpha = index - (double)i1;
		// bound:
		i1 = index_wrap(i1);
		i2 = index_wrap(i2);
		// interp:
		double v1 = read(i1, channel);
		double v2 = read(i2, channel);
		return mix(v1, v2, alpha);
	}
	
	inline double lookup(double signal, long channel=0) const {
		channel = channel_clamp(channel);
		double index = signal2index(signal);
		// interp:
		long i1 = (long)index;
		long i2 = i1+1;
		double alpha = index - (double)i1;
		// bound:
		i1 = index_clamp(i1);
		i2 = index_clamp(i2);
		// interp:
		double v1 = read(i1, channel);
		double v2 = read(i2, channel);
		return mix(v1, v2, alpha);
	}
	
	inline void poke(double value, double index, long channel=0) {
		const long i = (long)index;
		if (!(index_oob(i) || channel_oob(channel))) {
			write(fixdenorm(value), i, channel);
		} 
	}
	
	inline void splat_adding(double value, double phase, long channel=0) {
		const double valuef = fixdenorm(value);
		channel = channel_clamp(channel);
		double index = phase2index(phase);
		// interp:
		long i1 = (long)index;
		long i2 = i1+1;
		const double alpha = index - (double)i1;
		// bound:
		i1 = index_wrap(i1);
		i2 = index_wrap(i2);
		// interp:
		overdub(valuef*(1.-alpha), i1, channel);
		overdub(valuef*alpha,      i2, channel);
	}
	
	inline void splat(double value, double phase, long channel=0) {
		const double valuef = fixdenorm(value);
		channel = channel_clamp(channel);
		double index = phase2index(phase);
		// interp:
		long i1 = (long)index;
		long i2 = i1+1;
		const double alpha = index - (double)i1;
		// bound:
		i1 = index_wrap(i1);
		i2 = index_wrap(i2);
		// interp:
		const double v1 = read(i1, channel);
		const double v2 = read(i2, channel);
		write(v1 + (1.-alpha)*(valuef-v1), i1, channel);
		write(v2 + (alpha)*(valuef-v2), i2, channel);
	}
};

// DATA_MAXIMUM_ELEMENTS * 8 bytes = 256 mb limit
#define DATA_MAXIMUM_ELEMENTS	(33554432)

struct Data : public DataInterface<double> {
	t_genlib_data * dataRef;	// a pointer to some external source of the data
	
	Data() : DataInterface<double>() {
		dataRef = 0;
	}
	~Data() { 
		//genlib_report_message("releasing data handle %d", dataRef);
		if (dataRef != 0) {
			genlib_data_release(dataRef);
		}
	}
	void reset(const char * name, long s, long c) {
		// if needed, acquire the Data's global reference: 
		if (dataRef == 0) {
			void * ref = genlib_obtain_reference_from_string(name);
			dataRef = genlib_obtain_data_from_reference(ref);
			if (dataRef == 0) {	
				genlib_report_error("failed to acquire data");
				return; 
			}
		}
		genlib_data_resize(dataRef, s, c);
		getinfo();
	}
	bool setbuffer(void * bufferRef) {
		//genlib_report_message("set buffer %p", bufferRef);
		if (dataRef == 0) {
			// error: no data, or obtain?
			return false;
		}
		genlib_data_setbuffer(dataRef, bufferRef);
		getinfo();
		return true;
	}
	
	void getinfo() {
		t_genlib_data_info info;
		if (genlib_data_getinfo(dataRef, &info) == GENLIB_ERR_NONE) {
			mData = info.data;
			dim = info.dim;
			channels = info.channels;
		} else {
			genlib_report_error("failed to acquire data info");
		}
	}
};

// Used by SineData
struct DataLocal : public DataInterface<double> {
	DataLocal() : DataInterface<double>() {}
	~DataLocal() { 
		if (mData) sysmem_freeptr(mData);
		mData = 0;
	}

	void reset(long s, long c) { 
		mData=0; 
		resize(s, c); 
	}
		
	void resize(long s, long c) {
		if (s * c > DATA_MAXIMUM_ELEMENTS) {
			s = DATA_MAXIMUM_ELEMENTS/c;
			genlib_report_message("warning: resizing data to < 256MB");
		}
		if (mData) {
			sysmem_resizeptr(mData, sizeof(double) * s * c);
		} else {
			mData = (double *)sysmem_newptr(sizeof(double) * s * c);
		}
		if (!mData) {
			genlib_report_error("out of memory");
			resize(512, 1);
			return;
		} else {
			dim = s;
			channels = c;
		}
		set_zero64(mData, dim * channels);
	}

	// copy from a buffer~
	// resizing is safe only during initialization!
	bool setbuffer(void *dataReference) {
		mDataReference = dataReference; // replaced mName
		bool result = false;
		t_genlib_buffer * b;
		t_genlib_buffer_info info;
		if (mDataReference != 0) {
			b = (t_genlib_buffer *)genlib_obtain_buffer_from_reference(mDataReference);
			if (b) {
				if (genlib_buffer_edit_begin(b)==GENLIB_ERR_NONE) {
					if (genlib_buffer_getinfo(b, &info)==GENLIB_ERR_NONE) {
						float * samples = info.b_samples;
						long frames = info.b_frames;
						long nchans = info.b_nchans;
						//long size = info.b_size;
						//long modtime = info.b_modtime;	// cache & compare?
						
						// resizing is safe only during initialization!
						if (mData == 0) resize(frames, nchans);
						
						long frames_safe = frames < dim ? frames : dim;
						long channels_safe = nchans < channels ? nchans : channels;						
						// copy:
						for (int f=0; f<frames_safe; f++) {
							for (int c=0; c<channels_safe; c++) {
								double value = samples[c+f*nchans];
								write(value, f, c);
							}
						}
						result = true;
					} else {
						genlib_report_message("couldn't get info for buffer\n"); 
					}
					genlib_buffer_edit_end(b, 1);
				} else {
					genlib_report_message("buffer locked\n");
				}
			}
		} else {
			genlib_report_message("buffer reference not valid");
		}
		return result;
	}
};

struct Buffer : public DataInterface<float> {
	t_genlib_buffer * mBuf;
	t_genlib_buffer_info mInfo;
	float mDummy;		// safe access in case buffer is not valid
	
	Buffer() : DataInterface<float>() {}
	
	void reset(const char * name) {
		dim = 1;
		channels = 1;
		mData = &mDummy;
		mDummy = 0.f;
		mBuf = 0;
		
		// call into genlib:
		mDataReference = genlib_obtain_reference_from_string(name);		
	}
	
	void setbuffer(void * ref) {
		mDataReference = ref;
	}
	
	void begin() {
		t_genlib_buffer * b = genlib_obtain_buffer_from_reference(mDataReference);
		mBuf = 0;
		if (b) {
			if (genlib_buffer_perform_begin(b) == GENLIB_ERR_NONE) {
				mBuf = b;
			} else {
				//genlib_report_message ("not a buffer~ %s", mName->s_name);
			}
		} else {
			//genlib_report_message("no object %s\n", mName->s_name);
		}
		
		if (mBuf && genlib_buffer_getinfo(mBuf, &mInfo)==GENLIB_ERR_NONE) {
			// grab data:
			mBuf = b;
			mData = mInfo.b_samples;
			dim = mInfo.b_frames;
			channels = mInfo.b_nchans;
		} else {
			//genlib_report_message("couldn't get info");
			mBuf = 0;
			mData = &mDummy;
			dim = 1;
			channels = 1;
		}
	}
	
	void end() {
		if (mBuf) {
			genlib_buffer_perform_end(mBuf);
			if (modified) {
				genlib_buffer_dirty(mBuf);
			}
			modified = 0;
		}
		mBuf = 0;
	}
};

struct SineData : public DataLocal {
	SineData() : DataLocal() {
		const int costable_size = 1 << 14;	// 14 bit index (noise floor at around -156 dB)
		mData=0; 
		resize(costable_size, 1); 
		for (int i=0; i<dim; i++) {
			mData[i] = cos(i * GENLIB_PI * 2. / (double)(dim));
		}
	}
	
	~SineData() { 
		if (mData) sysmem_freeptr(mData);
		mData = 0;
	}
};

template<typename T>
inline int dim(const T& data) { return data.dim; }

template<typename T>
inline int channels(const T& data) { return data.channels; }

// used by cycle when no buffer/data is specified:
struct SineCycle {
			
	uint32_t phasei, pincr;
	double f2i;
	
	void reset(double samplerate, double init = 0) { 
		phasei = init * 4294967296.0;
		pincr = 0;
		f2i = 4294967296.0 / samplerate;
	}
	
	inline void freq(double f) {
		pincr = f * f2i;
	}
	
	inline void phase(double f) {
		phasei = f * 4294967296.0;
	}
	
	inline double phase() const {	
		return phasei * 0.232830643653869629e-9;
	}
	
	template<typename T>
	inline double operator()(const DataInterface<T>& buf) {
		T * data = buf.mData;
		// divide uint32_t range down to buffer size (32-bit to 14-bit)
		uint32_t idx = phasei >> 18;
		// compute fractional portion and divide by 18-bit range
		const double frac = (phasei & 262143) * 3.81471181759574e-6;	
		// index safely in 14-bit range:
		const double y0 = data[idx];
		const double y1 = data[(idx+1) & 16383];
		const double y = linear_interp(frac, y0, y1);
		phasei += pincr;
		return y;
	}
};

// global noise generator
Noise noise;

#endif
