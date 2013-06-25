#include "genlib_exportstate.h"	// contains DSPCodeInfo + export.h
#include "genlib_exportfunctions.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "malloc/malloc.h"

// DATA_MAXIMUM_ELEMENTS * 8 bytes = 256 mb limit
#define DATA_MAXIMUM_ELEMENTS	(33554432)

//////////// export_genlib.cpp ////////////
// export version

void my_memset(void *p, int c, long size);
void my_memcpy(void *dst, const void *src, long size);

t_ptr sysmem_newptr(t_ptr_size size)
{
	return (t_ptr)malloc(size);
}

t_ptr sysmem_newptrclear(t_ptr_size size)
{
	t_ptr p = (t_ptr)malloc(size);
	
	if (p)
		my_memset(p, 0, size);
	
	return p;
}

t_ptr sysmem_resizeptr(void *ptr, t_ptr_size newsize)
{
	return (t_ptr)realloc(ptr, newsize);
}

t_ptr sysmem_resizeptrclear(void *ptr, t_ptr_size newsize)
{
	long oldsize = malloc_size(ptr);
	t_ptr p = (t_ptr)realloc(ptr, newsize);
	
	if (p) {
		if (newsize > oldsize)
			my_memset((char *)p + oldsize, 0, newsize - oldsize);
	}	
	return p;
}

t_ptr_size sysmem_ptrsize(void *ptr)
{
	return malloc_size(ptr);
}

void sysmem_freeptr(void *ptr)
{
	free(ptr);
}

void sysmem_copyptr(const void *src, void *dst, t_ptr_size bytes)
{
	my_memcpy(dst, src, bytes);
}

void my_memset(void *p, int c, long size)
{
	char *p2 = (char *)p;
	int i;
	
	for (i = 0; i < size; i++, p2++)
		*p2 = c;
}

void my_memcpy(void *dst, const void *src, long size)
{
	char *s2 = (char *)src;
	char *d2 = (char *)dst;
	int i;
	
	for (i = 0; i < size; i++, s2++, d2++)
		*d2 = *s2;
}

void set_zero64(double *memory, long size)
{
	long i;
	
	for (i = 0; i < size; i++, memory++) {
		*memory = 0.;
	}
}

void genlib_report_error(const char *s)
{
	fprintf(stderr, "%s\n", s);
}

void genlib_report_message(const char *s)
{
	fprintf(stdout, "%s\n", s);
}

unsigned long systime_ticks(void)
{
	return 0;	// Gen code can deal with this
}

// NEED THIS FOR WINDOWS:
void *operator new(size_t size) { return sysmem_newptr(size); }
void operator delete(void *p) { sysmem_freeptr(p); }
void *operator new[](size_t size) { return sysmem_newptr(size); }
void operator delete[](void *p) { sysmem_freeptr(p); }

void * genlib_obtain_reference_from_string(const char * name) {
	return 0; // to be implemented
}

// the rest is stuff to isolate gensym, attrs, atoms, buffers etc.
t_genlib_buffer * genlib_obtain_buffer_from_reference(void *ref)
{
	return 0; // to be implemented
}

t_genlib_err genlib_buffer_edit_begin(t_genlib_buffer *b)
{
	return 0; // to be implemented
}

t_genlib_err genlib_buffer_edit_end(t_genlib_buffer *b, long valid)
{
	return 0; // to be implemented
}

t_genlib_err genlib_buffer_getinfo(t_genlib_buffer *b, t_genlib_buffer_info *info)
{
	return 0; // to be implemented
}

char *genlib_reference_getname(void *ref)
{
	return 0; // to be implemented
}

void genlib_buffer_dirty(t_genlib_buffer *b)
{
	 // to be implemented
}

t_genlib_err genlib_buffer_perform_begin(t_genlib_buffer *b)
{
	return 0; // to be implemented
}
void genlib_buffer_perform_end(t_genlib_buffer *b)
{
	// to be implemented
}

extern "C" void prepare(CommonState *cself, double SR, long VS) {
	cself->sr = SR;
	cself->vs = VS;
} 

// the exported function

extern "C" void initialize(ExportState **state)
{
	CommonState *self;
	
	*state = (ExportState *)malloc(sizeof(ExportState));
	self = (CommonState *)create(44100,2048);	// just some default values
	(*state)->cstate = self;
	
	(*state)->perform = (t_fun)perform;
	(*state)->setparameter = (t_fun)setparameter;
	(*state)->getparameter = (t_fun)getparameter;
	(*state)->destroy = (t_fun)destroy;
	(*state)->prepare = (t_fun)prepare;
	(*state)->reset = (t_fun)reset;
}

#ifdef pow
#undef pow
#endif
#include "math.h"

double gen_msp_pow(double value, double power)
{
	return pow(value, power);
}

void genlib_data_setbuffer(t_genlib_data *b, void *ref) {
	genlib_report_error("not supported for export targets\n");
}

typedef struct {
	t_genlib_data_info	info;
	double				cursor;	// used by Delay
	//t_symbol *			name;
} t_dsp_gen_data;	

t_genlib_data * genlib_obtain_data_from_reference(void *ref) 
{
	t_dsp_gen_data * self = (t_dsp_gen_data *)malloc(sizeof(t_dsp_gen_data));
	self->info.dim = 0;
	self->info.channels = 0;
	self->info.data = 0;
	self->cursor = 0;
	return (t_genlib_data *)self;
}

t_genlib_err genlib_data_getinfo(t_genlib_data *b, t_genlib_data_info *info) {
	t_dsp_gen_data * self = (t_dsp_gen_data *)b;
	info->dim = self->info.dim;
	info->channels = self->info.channels;
	info->data = self->info.data;
	return GENLIB_ERR_NONE;
}

void genlib_data_release(t_genlib_data *b) {
	t_dsp_gen_data * self = (t_dsp_gen_data *)b;
	
	if (self->info.data) {
		genlib_sysmem_freeptr(self->info.data);
		self->info.data = 0;
	}
}

long genlib_data_getcursor(t_genlib_data *b) {
	t_dsp_gen_data * self = (t_dsp_gen_data *)b;
	return self->cursor;
}

void genlib_data_setcursor(t_genlib_data *b, long cursor) {
	t_dsp_gen_data * self = (t_dsp_gen_data *)b;
	self->cursor = cursor;
}

void genlib_data_resize(t_genlib_data *b, long s, long c) {
	t_dsp_gen_data * self = (t_dsp_gen_data *)b;
	
	size_t sz, oldsz, copysz;
	double * old = 0;
	double * replaced = 0;
	int i, j, copydim, copychannels, olddim, oldchannels;
	
	//printf("data resize %d %d\n", s, c);
	
	// cache old for copying:
	old = self->info.data;
	olddim = self->info.dim;
	oldchannels = self->info.channels;
	
	// limit [data] size:
	if (s * c > DATA_MAXIMUM_ELEMENTS) {
		s = DATA_MAXIMUM_ELEMENTS/c;
		genlib_report_message("warning: constraining [data] to < 256MB");
	}
	// bytes required:
	sz = sizeof(double) * s * c;
	oldsz = sizeof(double) * olddim * oldchannels;
	
	if (old && sz == oldsz) {
		// no need to re-allocate, just resize
		// careful, audio thread may still be using it:
		if (s > olddim) {
			self->info.channels = c;
			self->info.dim = s;
		} else {
			self->info.dim = s;
			self->info.channels = c;
		}
		
		set_zero64(self->info.data, s * c);
		return;
		
	} else {
		
		// allocate new:
		replaced = (double *)sysmem_newptr(sz);
		
		// check allocation:
		if (replaced == 0) {
			genlib_report_error("allocating [data]: out of memory");
			// try to reallocate with a default/minimal size instead:
			if (s > 512 || c > 1) {
				genlib_data_resize((t_genlib_data *)self, 512, 1);
			} else {
				// if this fails, then Max is kaput anyway...
				genlib_data_resize((t_genlib_data *)self, 4, 1);
			}
			return;
		}
		
		// fill with zeroes:
		set_zero64(replaced, s * c);
	
		// copy in old data:
		if (old) {
			// frames to copy:
			// clamped:
			copydim = olddim > s ? s : olddim;
			// use memcpy if channels haven't changed:
			if (c == oldchannels) {
				copysz = sizeof(double) * copydim * c;
				//post("reset resize (same channels) %p %p, %d", self->info.data, old, copysz);
				memcpy(replaced, old, copysz);
			} else {
				// memcpy won't work if channels have changed,
				// because data is interleaved.
				// clamp channels copied:
				copychannels = oldchannels > c ? c : oldchannels;
				//post("reset resize (different channels) %p %p, %d %d", self->info.data, old, copydim, copychannels);
				for (i = 0; i<copydim; i++) {
					for (j = 0; j<copychannels; j++) {
						replaced[j + i*c] = old[j + i*oldchannels];
					}
				}
			}
		}
		
		// now update info:
		if (old == 0) {
			self->info.data = replaced;
			self->info.dim = s;
			self->info.channels = c;
		} else {
			// need to be careful; the audio thread may still be using it
			// since dsp_gen_data is preserved through edits
			// the order of resizing has to be carefully done
			// to prevent indexing out of bounds
			// (or maybe I'm being too paranoid here...)
			if (oldsz > sz) {
				// shrink size first
				if (s > olddim) {
					self->info.channels = c;
					self->info.dim = s;
				} else {
					self->info.dim = s;
					self->info.channels = c;
				}
				self->info.data = replaced;
			} else {
				// shrink size after
				self->info.data = replaced;
				if (s > olddim) {
					self->info.channels = c;
					self->info.dim = s;
				} else {
					self->info.dim = s;
					self->info.channels = c;
				}
			}
			
			// done with old:
			sysmem_freeptr(old);
			
		}
		
	}
}

void genlib_reset_complete(void *data) {}

