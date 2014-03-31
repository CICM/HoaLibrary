
//#include "../../Sources/Hoa2D/Hoa2D.h"
#include "../../ThirdParty/Csound/csdl.h"
#include "../../ThirdParty/Csound/pstream.h"

//using namespace Hoa2D;

typedef struct {
    OPDS    h;
    
    MYFLT   **outlets;
    MYFLT   *input, *azimuth, *order;

    //Encoder* encoder;
    
} HoaEnc;

typedef struct {
    OPDS    h;
    
    MYFLT   **outlets;
    MYFLT   **inlets, *order;
    
    //DecoderRegular* decoder;
    
} HoaDec;



static int hoaenc_set(CSOUND *csound, HoaEnc *p)
{
    
    //p->encoder = new Encoder(*p->order);
    
    return OK;
}

static int hoadec_set(CSOUND *csound, HoaDec *p)
{

    
    int order = *p->order;
    
    /*
    int numberOfChannels = *csound->GetNchnls();
    if (numberOfChannels > order * 2 + 1)
        *csound->ErrorMsg("Invalide order");
    */
    
    int numberOfChannels = order * 2 + 2;
    
    //p->decoder = new DecoderRegular(order, numberOfChannels);
    
    return OK;
}

static int hoaenc(CSOUND *csound, HoaEnc *p)
{
    
    
    //*p->outlets = *new MYFLT*[64];
    

    const double input = *p->input;
    const double azimuth = *p->azimuth;
    //float output[] = *p->outlets[];
    
    //p->encoder->setAzimuth(azimuth);
    //p->encoder->process(input, *p->outlets);
    
    return OK;
}
/*
static int hoadec(CSOUND *csound, HoaDec *p)
{
    *p->inlets = *new MYFLT*[64];
    *p->outlets = *new MYFLT*[64];
    
    p->decoder->process(*p->inlets, *p->outlets);
    
    return OK;
}*/

static OENTRY localops[] =
{
    {"HoaEnc", sizeof(HoaEnc), 0, 5, "a", "aki", (SUBR)hoaenc_set, NULL, (SUBR)hoaenc}
    //{"HoaDec", sizeof(HoaDec), 0, 5, "a[]", "a[]i", (SUBR)hoadec_set, NULL, (SUBR)hoadec},
};

    
int hoaenc_init_(CSOUND *csound)
{
    return csound->AppendOpcodes(csound, &(localops[0]),(int) (sizeof(localops) / sizeof(OENTRY)));
}
int hoadec_init_(CSOUND *csound)
{
    return csound->AppendOpcodes(csound, &(localops[0]),(int) (sizeof(localops) / sizeof(OENTRY)));
}

