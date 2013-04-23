
//#include "hoa.gengrain.h"

static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State { 
	CommonState __commonstate;
    Delay m_delay_1;
	Phasor m_phasor_6;
	Phasor m_phasor_11;
	Phasor m_phasor_10;
	Sah m_sah_9;
	Sah m_sah_17;
	Sah m_sah_12;
	Sah m_sah_14;
	Sah m_sah_13;
	Sah m_sah_15;
	Sah m_sah_8;
	Sah m_sah_7;
	Sah m_sah_16;
	double samples_to_seconds;
	double samplerate;
	double m_feedback_3;
	double m_rarefaction_2;
	double m_grainsize_5;
	double m_delay_4;
	int vectorsize;
	int __exception;
	// re-initialize all member variables;
	inline void reset(double __sr, int __vs) { 
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_delay_1.reset("m_delay_1", 2000000);
		m_rarefaction_2 = 0;
		m_feedback_3 = 0;
		m_delay_4 = 0;
		m_grainsize_5 = 0;
		samples_to_seconds = (1 / samplerate);
		m_phasor_6.reset(0);
		m_sah_7.reset(0);
		m_sah_8.reset(0);
		m_sah_9.reset(0);
		m_phasor_10.reset(0);
		m_phasor_11.reset(0);
		m_sah_12.reset(0);
		m_sah_13.reset(0);
		m_sah_14.reset(0);
		m_sah_15.reset(0);
		m_sah_16.reset(0);
		m_sah_17.reset(0);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) { 
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		if (__exception) { 
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) )) { 
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		double mul_99 = (1 * m_feedback_3);
		double clamp_108 = ((mul_99 <= 0) ? 0 : ((mul_99 >= 1) ? 1 : mul_99));
		double mul_103 = (1 * m_delay_4);
		double mul_114 = (mul_103 * 0.5);
		double mul_101 = (1 * m_grainsize_5);
		double rdiv_111 = safediv(1000, mul_101);
		samples_to_seconds = (1 / samplerate);
		double mul_105 = (1 * m_rarefaction_2);
		double mul_107 = (mul_105 * 2);
		double sub_106 = (mul_107 - 1);
		// the main sample loop;
		while ((__n--)) { 
			const double in1 = (*(__in1++));
			double mul_122 = (in1 * 0.02);
			double phasor_81 = m_phasor_6(rdiv_111, samples_to_seconds);
			int lt_78 = (phasor_81 < 0.01);
			int gt_79 = (phasor_81 > 0.01);
			double noise_83 = noise();
			double sah_82 = m_sah_7(noise_83, phasor_81, 0.01);
			double sah_77 = m_sah_8(sah_82, lt_78, 0.5);
			double sah_76 = m_sah_9(sah_82, gt_79, 0.5);
			double anon_80 = linear_interp(phasor_81, sah_77, sah_76);
			int gt_120 = (anon_80 > sub_106);
			double phasor_91 = m_phasor_10(rdiv_111, samples_to_seconds);
			double phasor_53 = m_phasor_11(rdiv_111, samples_to_seconds);
			int lt_50 = (phasor_53 < 0.01);
			int gt_51 = (phasor_53 > 0.01);
			double noise_55 = noise();
			double sah_54 = m_sah_12(noise_55, phasor_53, 0.01);
			double sah_49 = m_sah_13(sah_54, lt_50, 0.5);
			double sah_48 = m_sah_14(sah_54, gt_51, 0.5);
			double anon_52 = linear_interp(phasor_53, sah_49, sah_48);
			double add_116 = (anon_52 + 1);
			double mul_115 = (add_116 * mul_114);
			double noise_95 = noise();
			double sub1 = (noise_95 - -1);
			double scale_125 = ((safepow(safediv(sub1, 2), 1) * 1) + 0);
			double sah_97 = m_sah_15(scale_125, 1, 0.5);
			double add_89 = (phasor_91 + sah_97);
			double wrap_90 = wrap(add_89, 0, 1);
			double mul_87 = (wrap_90 * 3.1415926535898);
			double sin_86 = sin(mul_87);
			double sah_113 = m_sah_16(mul_115, sin_86, 0.001);
			double mstosamps_88 = (sah_113 * (samplerate * 0.001));
			double tap_94 = m_delay_1.read_linear(mstosamps_88);
			int sah_119 = m_sah_17(gt_120, sin_86, 0.001);
			double mul_118 = (sah_119 * sin_86);
			double mul_110 = (tap_94 * mul_118);
			double mul_109 = (mul_122 * mul_118);
			double out1 = (mul_109 + mul_110);
			double mul_112 = (mul_110 * clamp_108);
			m_delay_1.write((mul_112 + in1));
			m_delay_1.step();
			// assign results to output buffer;
			//(*(__out1++)) = out1;
            (*(__out1++)) = in1*0.2;
			
		};
		return __exception;
		
	};
	inline void set_rarefaction(double __value) {
		m_rarefaction_2 = (__value < 0 ? 0 : (__value > 1 ? 1 : __value));
	};
	inline void set_feedback(double __value) {
		m_feedback_3 = (__value < 0 ? 0 : (__value > 0.99 ? 0.99 : __value));
	};
	inline void set_delay(double __value) {
		m_delay_4 = (__value < 0 ? 0 : (__value > 5000 ? 5000 : __value));
	};
	inline void set_grainsize(double __value) {
		m_grainsize_5 = (__value < 1 ? 1 : (__value > 5000 ? 5000 : __value));
	};
	
} State;


/// 
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs 

int gen_kernel_numins = 1;
int gen_kernel_numouts = 1;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }

/// Assistive lables for the signal inputs and outputs 

char * gen_kernel_innames[] = { "input" };
char * gen_kernel_outnames[] = { "output" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) { 
	State * self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) { 
	State * self = (State *)cself;
	self->reset(cself->sr, cself->vs); 
}

/// Set a parameter of a State object 

void setparameter(CommonState *cself, long index, double value, void *ref) {
	State * self = (State *)cself;
	switch (index) {
		case 0: self->set_rarefaction(value); break;
		case 1: self->set_feedback(value); break;
		case 2: self->set_delay(value); break;
		case 3: self->set_grainsize(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object 

void getparameter(CommonState *cself, long index, double *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_rarefaction_2; break;
		case 1: *value = self->m_feedback_3; break;
		case 2: *value = self->m_delay_4; break;
		case 3: *value = self->m_grainsize_5; break;
		
		default: break;
	}
}

/// Allocate and configure a new State object and it's internal CommonState:

void * create(double sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(4 * sizeof(ParamInfo));
	self->__commonstate.numparams = 4;
	// initialize parameter 0 ("m_rarefaction_2")
	pi = self->__commonstate.params + 0;
	pi->name = "rarefaction";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_rarefaction_2;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1; 
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_feedback_3")
	pi = self->__commonstate.params + 1;
	pi->name = "feedback";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_feedback_3;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1; 
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.99;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_delay_4")
	pi = self->__commonstate.params + 2;
	pi->name = "delay";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_delay_4;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1; 
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 5000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_grainsize_5")
	pi = self->__commonstate.params + 3;
	pi->name = "grainsize";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_grainsize_5;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0; 
	pi->inputmax = 1; 
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 5000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) { 
	State * self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self; 
}
