/**
	@file
	HoaEncodeNF - High Order Ambisonic Panner
	Julien Colafrancesco	

	@ingroup	examples	
*/
extern "C" {
#include "ext.h"							// standard Max include, always required (except in Jitter)
#include "ext_obex.h"						// required for new style objects
#include "z_dsp.h"							// required for MSP objects
}

#include <HoaDistance.h>
#include <MiscMath.h>
////////////////////////// object struct
typedef struct _HoaEncodeNF 
{
	t_pxobject					ob;			
	HoaDistance*				HoaDistanceInstance;
	t_float**					sp_vec_copy;
	int							sp_n_copy;
	long						inputNumber;
	long						outputNumber;

} t_HoaEncodeNF;

///////////////////////// function prototypes
//// standard set
void *HoaEncodeNF_new(t_symbol *s, long argc, t_atom *argv);
void HoaEncodeNF_free(t_HoaEncodeNF *x);
void HoaEncodeNF_assist(t_HoaEncodeNF *x, void *b, long m, long a, char *s);

void HoaEncodeNF_float(t_HoaEncodeNF *x, double f);

void HoaEncodeNF_dsp(t_HoaEncodeNF *x, t_signal **sp, short *count);
t_int *HoaEncodeNF_perform(t_int *w);
//////////////////////// global class pointer variable
void *HoaEncodeNF_class;


int main(void)
{	

	t_class *c;
	
	c = class_new("Hoa.NFCpre~", (method)HoaEncodeNF_new, (method)HoaEncodeNF_free, (long)sizeof(t_HoaEncodeNF), 0L, A_GIMME, 0);
	
	class_addmethod(c, (method)HoaEncodeNF_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)HoaEncodeNF_dsp,		"dsp",		A_CANT, 0);
	class_addmethod(c, (method)HoaEncodeNF_assist,	"assist",	A_CANT, 0);
	
	class_dspinit(c);				
	class_register(CLASS_BOX, c);	
	HoaEncodeNF_class = c;
	
	class_findbyname(CLASS_NOBOX, gensym("hoa.encoder~"));
	return 0;
}

void HoaEncodeNF_float(t_HoaEncodeNF *x, double f)
{
	int index = proxy_getinlet((t_object *)x);
	

	if(index == 0)
	{
		x->HoaDistanceInstance->ChangeSourceDistance(f);
	}
}


void HoaEncodeNF_dsp(t_HoaEncodeNF *x, t_signal **sp, short *count)
{
	int outputNumber = x->outputNumber;
	int inputNumber = x->inputNumber;
	
	for (int i = 0; i<outputNumber+inputNumber; i++) {
		x->sp_vec_copy[i] = sp[i]->s_vec;
	}
	x->sp_n_copy = (int)sp[0]->s_n;
	
	dsp_add(HoaEncodeNF_perform, 1, x);
}

t_int *HoaEncodeNF_perform(t_int *w)
{
	t_HoaEncodeNF *x = (t_HoaEncodeNF *)(w[1]);

	
	int n;
	int outputNumber = x->outputNumber;
	int inputNumber = x->inputNumber;

	
	t_float *in;
	t_float *out;

	n = x->sp_n_copy;
	
	double* tmp_output;
	
	
	for (int i = 0; i<n; i++) {
		in = (t_float*)x->sp_vec_copy[0];
		tmp_output = x->HoaDistanceInstance->process(in[i]);
		
		for (int j = 0; j<outputNumber; j++) {
			out = (t_float*)   x->sp_vec_copy[inputNumber+j];
			out[i] = tmp_output[j];
			//out[i] = secHankel(3, 5.4).real();
		}
	}
	return w + 2;
}

void HoaEncodeNF_assist(t_HoaEncodeNF *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { //inlet
		sprintf(s, "Inlet %ld", a);
	} 
	else {	// outlet
		sprintf(s, "Outlet %ld", a); 			
	}
}


void HoaEncodeNF_free(t_HoaEncodeNF *x) 
{

	dsp_free((t_pxobject *)x);
	sysmem_freeptr(x->sp_vec_copy);

	
	
}

void *HoaEncodeNF_new(t_symbol *s, long argc, t_atom *argv)
{
	t_HoaEncodeNF *x = NULL;

	long orderNumber = atom_getlong(argv);
	long speakersDistance = atom_getlong(argv+1);
	long inputNumber = 1;
	long outputNumber = orderNumber +1;


	if (x = (t_HoaEncodeNF *)object_alloc((t_class*)HoaEncodeNF_class)) {
		dsp_setup((t_pxobject *)x, inputNumber);	
		
		for (int i=0; i<outputNumber; i++) {
			outlet_new(x, "signal");
		}


//		
		x->HoaDistanceInstance = new HoaDistance(orderNumber,speakersDistance);
//		
		x->sp_vec_copy = (t_float **)sysmem_newptr (sizeof(t_float*) * (outputNumber+inputNumber));
		x->ob.z_misc = Z_NO_INPLACE;  
		x->inputNumber = inputNumber;
		x->outputNumber = outputNumber;

		
	}
	return (x);
}
