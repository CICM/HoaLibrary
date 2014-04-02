
#include "csdl.h"
#include "pstream.h"

/**
typedef struct
{
    OPDS    h;
    MYFLT   *inlet;
    MYFLT   *outlet;
    int somme, valeur;

} TESTE;


static int teste_set(CSOUND *csound,TESTE *p)
{
    p->valeur = (int)*p->inlet;
    p->somme = 2;

    return OK;
}

 
 
static int teste(CSOUND *csound,TESTE *p)
{
    int resultat = p->valeur + p->somme;
    
    resultat = *p->outlet;
    
    return OK;
}

static OENTRY localops[] =
{
    //{"teste",  sizeof(TESTE), CW, 3, "k",  "k",(SUBR)teste_set, (SUBR)teste}
    {"teste",  sizeof(TESTE), 3, "k",  "k", NULL, NULL, teste}
};

LINKAGE
*/

typedef struct
{
    OPDS h;
    MYFLT *ar, *asig;
    
} NEGATE;

static int negate(CSOUND *csound, NEGATE *p)
{
    int n, nsmps = csound->ksmps;
    MYFLT *ar = p->ar;
    MYFLT *as = p->asig;
    for (n=0; n<nsmps; n++) {
        ar[n] = - as[nn]
    }
    return OK;
}

static OENTRY localopst [] = {
    { "negate", sizeof(NEGATE), 4, "d". "a", NULL, NULL, negate };
}x

LINKAGE