
#include "../../Sources/Hoa2D/Hoa2D.h"

#include "../../ThirdParty/Csound/csdl.h"
#include "../../ThirdParty/Csound/pstream.h"

typedef struct
{
    OPDS    h;
    MYFLT   *outlet[3];
    MYFLT   *sig;
    
    Encoder* encoder;
    
    } HOAENC;


static int HoaEnc_set(CSOUND *csound, HOAENC *p)
{

    MYFLT ordre = 1;
     char message[1024];
    
     if(ordre< 1)
         return NOTOK;
     else
     {
         p->encoder = new Encoder(ordre);

         
         sprintf(message, "Number of args %i", p->h.optext->t.inArgCount);
         csound->InitError(csound, Str(message));
     for (int i = 0; i < p->h.optext->t.inArgCount; i++)
     {
         sprintf(message, "Arg %i : %i", i, p->h.optext->t.inArgs[i].type);
         csound->InitError(csound, Str(message));
     }
     return OK;
     }

    
    
}

static int HoaEnc(CSOUND *csound,HOAENC *p)
{
    double vecsize = csound->GetInputBufferSize(csound);
    double azimuth = 100;
    
    //double azimuth = Hoa::wrap_twopi(*p->azimuth);
    
    
    p->encoder->setAzimuth(azimuth);
    
    //MYFLT value = *p->sig;
    
    for (int i = 0; i < vecsize; i++)
    {
        p->encoder->process(p->sig[i], p->outlet[i]);
    }
    
    return OK;
}

    static OENTRY localops[] =
    {
        {"hoaenc",  sizeof(HOAENC), CR , 3, "mmm",  "a", (SUBR)HoaEnc, (SUBR)HoaEnc}
        
    };
    
    LINKAGE

