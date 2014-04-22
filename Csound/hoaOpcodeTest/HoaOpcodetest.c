
#include "csdl.h"
#include "pstream.h"


typedef struct
{
    OPDS    h;
    MYFLT   *out;
    MYFLT   *in1,*in2;
    

} SOMA;

typedef struct
{
    OPDS    h;
    MYFLT   *out;
    MYFLT   *in1,*in2;
    
    
} MENOS;


static int soma_set(CSOUND *csound,SOMA *p)
{
    return OK;
}

static int menos_set(CSOUND *csound,MENOS *p)
{
    return OK;
}



static int soma(CSOUND *csound,SOMA *p)
{
    MYFLT   result;
    
    result = *p->in1 + *p->in2;
    *p->out = result;

	return OK;
}

static int menos(CSOUND *csound,MENOS *p)
{
    MYFLT   result;
    
    result = *p->in1 - *p->in2;
    *p->out = result;
    
	return OK;
}

static OENTRY localops[] =
{
    {"soma",    sizeof(SOMA), TR, 2, "k",  "kk", (SUBR)soma_set, (SUBR)soma},
    {"menos",  sizeof(MENOS), TR, 2, "k",  "kk",(SUBR)menos_set, (SUBR)menos}
};

LINKAGE
