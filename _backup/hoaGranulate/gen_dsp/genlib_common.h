#ifndef GENLIB_COMMON_H
#define GENLIB_COMMON_H 1

//////////// genlib_common.h ////////////
// common data structure header file -- this is the stuff required by the
// common code and accessed by the export and max code
	
#define DSP_GEN_MAX_SIGNALS 16	

typedef double t_sample;
typedef char *t_ptr; 
	
typedef long t_genlib_err;
typedef enum {
	GENLIB_ERR_NONE =			0,	///< No error
	GENLIB_ERR_GENERIC =		-1,	///< Generic error
	GENLIB_ERR_INVALID_PTR =	-2,	///< Invalid Pointer
	GENLIB_ERR_DUPLICATE =		-3,	///< Duplicate
	GENLIB_ERR_OUT_OF_MEM =		-4,	///< Out of memory
	
	GENLIB_ERR_LOOP_OVERFLOW =  100,	// too many iterations of loops in perform()
	GENLIB_ERR_NULL_BUFFER =	101	// missing signal data in perform()
	
} e_genlib_errorcodes;

typedef enum {
	GENLIB_PARAMTYPE_FLOAT	=	0,
	GENLIB_PARAMTYPE_SYM	= 	1
} e_genlib_paramtypes;

struct ParamInfo
{
	double defaultvalue;
	void * defaultref;
	char hasinputminmax;
	char hasminmax;
	double inputmin, inputmax;
	double outputmin, outputmax;
	char *name;
	char *units;
	int paramtype;		// 0 -> float64, 1 -> symbol (table name)
	double exp;			// future, for scaling
};

struct CommonState
{
	double sr;
	int vs;	
	int numins;
	int numouts;
	char **inputnames;
	char **outputnames;
	int numparams;
	ParamInfo *params;
	
	void * parammap;	// implementation-dependent
	void * api;			// implementation-dependent
};

// opaque interface to float32 buffer:
typedef struct _genlib_buffer t_genlib_buffer;
typedef struct {
	char b_name[256];	///< name of the buffer
	float *b_samples;	///< stored with interleaved channels if multi-channel
	long b_frames;		///< number of sample frames (each one is sizeof(float) * b_nchans bytes)
	long b_nchans;		///< number of channels
	long b_size;		///< size of buffer in floats
	float b_sr;			///< sampling rate of the buffer
	long b_modtime;		///< last modified time ("dirty" method)
	long b_rfu[57];		///< reserved for future use
} t_genlib_buffer_info;

// opaque interface to float64 buffer: 
typedef struct _genlib_data t_genlib_data;
typedef struct {
	int					dim, channels;
	double *			data;
} t_genlib_data_info;

extern "C" {
	
	int num_inputs();
	int num_outputs();
	void *create(double sr, long vs);
	void reset(CommonState *cself);
	void destroy(CommonState *cself);
	void setparameter(CommonState *cself, long index, double value, void *ref);
	void getparameter(CommonState *cself, long index, double *value);
	int perform(CommonState *cself, t_sample **perform_ins, long perform_numins, t_sample **perform_outs, long perform_numouts, long perform_n);
	
} // extern "C"

#endif // GENLIB_COMMON_H
