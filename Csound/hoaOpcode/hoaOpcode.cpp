
#include "../../ThirdParty/Csound/csdl.h"
#include "../../ThirdParty/Csound/pstream.h"
#include "../../Sources/Hoa2D/Hoa2D.h"

using namespace Hoa2D;

typedef struct {
    OPDS    h;
    MYFLT   *ar, *asig, *kfco, *kres, *istor;
    double  ynm1, ynm2;
    double  coef1, coef2, okf, okr, k;
    Encoder* encoder;
} LOWPR;

static int lowpr_set(CSOUND *csound, LOWPR *p)
{
    if (*p->istor==FL(0.0))
        p->ynm1 = p->ynm2 = 0.0;
    p->okf = 0.0;
    p->okr = 0.0;
    p->k = 0.0;
    return OK;
}

static int lowpr(CSOUND *csound, LOWPR *p)
{
    double b, k = p->k;
    MYFLT *ar, *asig;
    double yn, ynm1, ynm2 ;
    MYFLT kfco = *p->kfco;
    MYFLT kres = *p->kres;
    double coef1 = p->coef1, coef2 = p->coef2;
    uint32_t offset = p->h.insdshead->ksmps_offset;
    uint32_t early  = p->h.insdshead->ksmps_no_end;
    uint32_t n, nsmps = CS_KSMPS;
    
    if (p->okf != kfco || p->okr != kres) { /* Only if changed */
        b = 10.0 / (*p->kres * sqrt((double)kfco)) - 1.0;
        p->k = k = 1000.0 / (double)kfco;
        p->coef1 = coef1 = (b+2.0 * k);
        p->coef2 = coef2 = 1.0/(1.0 + b + k);
        p->okf = kfco; p->okr = kres; /* remember to save recalculation */
    }
    ar = p->ar;
    asig = p->asig;
    ynm1 = p->ynm1;
    ynm2 = p->ynm2;
    
    if (UNLIKELY(offset)) memset(ar, '\0', offset*sizeof(MYFLT));
    if (UNLIKELY(early)) {
        nsmps -= early;
        memset(&ar[nsmps], '\0', early*sizeof(MYFLT));
    }
    for (n=offset; n<nsmps;n++) {
        ar[n] = (MYFLT)(yn = (coef1 * ynm1 - k * ynm2 + (double)asig[n]) * coef2);
        ynm2 = ynm1;
        ynm1 =  yn;
    }
    p->ynm1 = ynm1;
    p->ynm2 = ynm2;             /* And save */
    
    return OK;
}

static OENTRY localops[] = { "lowres",   sizeof(LOWPR), 0, 5, "a", Str("akko"), (SUBR)lowpr_set, NULL,   (SUBR)lowpr };

int lowpassr_init_(CSOUND *csound)
{
    return csound->AppendOpcodes(csound, &(localops[0]),(int) (sizeof(localops) / sizeof(OENTRY)));
}
