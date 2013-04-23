#ifndef GENLIB_EXPORT_STATE_H
#define GENLIB_EXPORT_STATE_H 1

#include "genlib.h"

//////////// genlib_export.h ////////////

typedef void (*t_fun)(void *x, ...);

typedef struct _ExportState
{
	CommonState *cstate;
	t_fun perform;
	t_fun setparameter;
	t_fun getparameter;
	t_fun destroy;
	t_fun prepare;
	t_fun reset;
} ExportState;

#endif
