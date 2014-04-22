
extern "C"
{
#include "../../ThirdParty/Csound/csdl.h"
#include "../../ThirdParty/Csound/pstream.h"
}

#include "../../Sources/Hoa2D/Hoa2D.h"

typedef struct
{
    OPDS    h;
    MYFLT   outlet[300];
    MYFLT   *sig, *azimuth, *order;

    //Encoder* encoder;
    
    // a1, a2, a3 hoaenc iordre, asig, aazi,
} HOAENC;


static int HoaEnc_set(CSOUND *csound, HOAENC *p)
{
    /*
    char message[1024];
    if(*p->order < 1)
        return NOTOK;
    else
    {
        
        p->encoder = new Encoder(*p->order);
        
        sprintf(message, "Number of args %i", p->h.optext->t.inArgCount);
        csound->InitError(csound, Str(message));
        for (int i = 0; i < p->h.optext->t.inArgCount; i++)
        {
            sprintf(message, "Arg %i : %i", i, p->h.optext->t.inArgs[i].type);
            csound->InitError(csound, Str(message));
        }
        return OK;
    }
    */
    return OK;
}

 
static int HoaEnc(CSOUND *csound,HOAENC *p)
{
    /*
    double azimuth = Hoa::wrap_twopi(*p->azimuth);
    p->encoder->setAzimuth(azimuth);
    
    MYFLT value = *p->sig;
    
    p->encoder->process(value, p->outlet);
    */
    
    
    return OK;
}

extern "C"
{
static OENTRY localops[] =
{
    {"hoaenc",  sizeof(HOAENC), TR, 2, "a[]",  "aki",(SUBR)HoaEnc_set, (SUBR)HoaEnc}

};

LINKAGE
}
*/
