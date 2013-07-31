//-----------------------------------------------------
// name: "OneSourceToStereo"
// version: "1.0"
// author: "CICM"
// license: "BSD"
// copyright: "(c)CICM 2013"
//
// Code generated with Faust 0.9.59 (http://faust.grame.fr)
//-----------------------------------------------------
/* link with  */
#include <math.h>
#include <cmath>
template <int N> inline float faustpower(float x) 		{ return powf(x,N); } 
template <int N> inline double faustpower(double x) 	{ return pow(x,N); }
template <int N> inline int faustpower(int x) 			{ return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x) 		{ return 1; }
template <> 	 inline int faustpower<1>(int x) 		{ return x; }
/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections :
	the ARCHITECTURE section (in two parts) and the USER section. Each section
	is governed by its own copyright and license. Please check individually
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
	Copyright (C) 2004-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either version 3
	of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

	EXCEPTION : As a special exception, you may create a larger work
	that contains this FAUST architecture section and distribute
	that work under terms of your choice, so long as this FAUST
	architecture section is not modified.

	MAX MSP SDK : in order to compile a MaxMSP external with this
	architecture file you will need the official MaxMSP SDK from
	cycling'74. Please check the corresponding license.

 ************************************************************************
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <math.h>

#include <iostream>
#include <fstream>
#include <sstream>

#ifdef __APPLE__
#include <Carbon/Carbon.h>
#include <unistd.h>
#endif

#define FAUSTFLOAT double

#include "faust/gui/UI.h"
#include "faust/audio/dsp.h"
#include "faust/misc.h"

using namespace std;

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/


/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  

typedef long double quad;

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
  private:
	double 	fConst0;
	double 	fConst1;
	FAUSTFLOAT 	fslider0;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	double 	fRec1[2];
  public:
	static void metadata(Meta* m) 	{ 
		m->declare("name", "OneSourceToStereo");
		m->declare("version", "1.0");
		m->declare("author", "CICM");
		m->declare("license", "BSD");
		m->declare("copyright", "(c)CICM 2013");
		m->declare("hoa.lib/name", "HOA");
		m->declare("hoa.lib/title", "High Order Ambisonics library");
		m->declare("hoa.lib/author", "Pierre Guillot");
		m->declare("hoa.lib/copyright", "2012-2013 Guillot, Paris, Colafrancesco, CICM labex art H2H, U. Paris 8");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/version", "1.0");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/version", "1.29");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/version", "1.0");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("oscillator.lib/name", "Faust Oscillator Library");
		m->declare("oscillator.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("oscillator.lib/copyright", "Julius O. Smith III");
		m->declare("oscillator.lib/version", "1.11");
		m->declare("oscillator.lib/license", "STK-4.3");
	}

	virtual int getNumInputs() 	{ return 1; }
	virtual int getNumOutputs() 	{ return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = exp((0 - (5e+01 / double(min(192000, max(1, fSamplingFreq))))));
		fConst1 = (1.0 - fConst0);
		fslider0 = 1.0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		fslider1 = 62831.0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openVerticalBox("OneSourceToStereo");
		interface->addHorizontalSlider("Angle", &fslider1, 62831.0, -6.28318530717959, 6.28318530717959, 0.001);
		interface->addHorizontalSlider("Radius", &fslider0, 1.0, 0.0, 5.0, 0.001);
		interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		double 	fSlow0 = (fConst1 * fslider0);
		double 	fSlow1 = (fConst1 * fslider1);
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		for (int i=0; i<count; i++) {
			fRec0[0] = (fSlow0 + (fConst0 * fRec0[1]));
			int iTemp0 = (fRec0[0] > 1);
			int iTemp1 = (fRec0[0] < 1);
			double fTemp2 = (iTemp0 + (fRec0[0] * iTemp1));
			double fTemp3 = ((double)input0[i] * (1 + (2.0794415416798357 * (0 - (fTemp2 - 1)))));
			double fTemp4 = (3.0 * fTemp2);
			double fTemp5 = ((3.0 * ((fTemp2 * (fTemp4 > 0)) * (fTemp4 <= 1))) + (fTemp4 > 1));
			fRec1[0] = (fSlow1 + (fConst0 * fRec1[1]));
			double fTemp6 = (fTemp5 * cos(fRec1[0]));
			double fTemp7 = (0.11666666666666667 * fTemp6);
			double fTemp8 = (2.0794415416798357 * fTemp2);
			double fTemp9 = (fTemp8 - 0.6931471805599453);
			double fTemp10 = (2.466303462376431 * fTemp9);
			double fTemp11 = ((2.466303462376431 * ((fTemp9 * (fTemp10 > 0)) * (fTemp10 <= 1))) + (fTemp10 > 1));
			double fTemp12 = (2 * fRec1[0]);
			double fTemp13 = (fTemp11 * cos(fTemp12));
			double fTemp14 = (0.07777777777777778 * fTemp13);
			double fTemp15 = (fTemp8 - 1.0986122886681098);
			double fTemp16 = (3.4760594967822085 * fTemp15);
			double fTemp17 = ((3.4760594967822085 * ((fTemp15 * (fTemp16 > 0)) * (fTemp16 <= 1))) + (fTemp16 > 1));
			double fTemp18 = (3 * fRec1[0]);
			double fTemp19 = (fTemp17 * cos(fTemp18));
			double fTemp20 = (0.03888888888888889 * fTemp19);
			double fTemp21 = (fTemp8 - 1.3862943611198906);
			double fTemp22 = (4.481420117724551 * fTemp21);
			double fTemp23 = ((4.481420117724551 * ((fTemp21 * (fTemp22 > 0)) * (fTemp22 <= 1))) + (fTemp22 > 1));
			double fTemp24 = (4 * fRec1[0]);
			double fTemp25 = (fTemp23 * cos(fTemp24));
			double fTemp26 = (0.014141414141414142 * fTemp25);
			double fTemp27 = (fTemp8 - 1.6094379124341003);
			double fTemp28 = (5.484814947747076 * fTemp27);
			double fTemp29 = ((5.484814947747076 * ((fTemp27 * (fTemp28 > 0)) * (fTemp28 <= 1))) + (fTemp28 > 1));
			double fTemp30 = (5 * fRec1[0]);
			double fTemp31 = (fTemp29 * cos(fTemp30));
			double fTemp32 = (0.0035353535353535356 * fTemp31);
			double fTemp33 = (fTemp8 - 1.791759469228055);
			double fTemp34 = (6.487159194630884 * fTemp33);
			double fTemp35 = ((6.487159194630884 * ((fTemp33 * (fTemp34 > 0)) * (fTemp34 <= 1))) + (fTemp34 > 1));
			double fTemp36 = (6 * fRec1[0]);
			double fTemp37 = (fTemp35 * cos(fTemp36));
			double fTemp38 = (0.0017529949315523716 * fTemp37);
			double fTemp39 = (7 * fRec1[0]);
			double fTemp40 = (fTemp8 - 1.9459101490553132);
			double fTemp41 = (7.488875689418624 * fTemp40);
			double fTemp42 = ((7.488875689418624 * ((fTemp40 * (fTemp41 > 0)) * (fTemp41 <= 1))) + (fTemp41 > 1));
			double fTemp43 = (cos(fTemp39) * fTemp42);
			double fTemp44 = (0.0026481821020520905 * fTemp43);
			double fTemp45 = (0.7071067811865475 * (((((((0.06666666666666667 + fTemp7) + fTemp14) + fTemp20) + fTemp26) + fTemp32) + fTemp38) + fTemp44));
			double fTemp46 = (sin(fRec1[0]) * fTemp5);
			double fTemp47 = (0.10778594545965012 * fTemp6);
			double fTemp48 = (sin(fTemp12) * fTemp11);
			double fTemp49 = (0.054997194092287024 * fTemp48);
			double fTemp50 = (sin(fTemp18) * fTemp17);
			double fTemp51 = (0.035928648486550044 * fTemp50);
			double fTemp52 = (0.014882133480864604 * fTemp19);
			double fTemp53 = (sin(fTemp24) * fTemp23);
			double fTemp54 = (0.014141414141414142 * fTemp53);
			double fTemp55 = (sin(fTemp30) * fTemp29);
			double fTemp56 = (sin(fTemp36) * fTemp35);
			double fTemp57 = (0.0012395546034863296 * fTemp37);
			double fTemp58 = (sin(fTemp39) * fTemp42);
			double fTemp59 = (0.0024466012424486424 * fTemp43);
			double fTemp60 = ((((((((((((((0.06666666666666667 + (0.044646400442593805 * fTemp46)) + fTemp47) + fTemp49) + (0.05499719409228703 * fTemp13)) + fTemp51) + fTemp52) + fTemp54) + (8.659118781849972e-19 * fTemp25)) + (0.003266240771504549 * fTemp55)) - (0.0013529212255331455 * fTemp31)) + (0.0012395546034863296 * fTemp56)) - fTemp57) + (0.0010134154163410926 * fTemp58)) - fTemp59);
			double fTemp61 = (0.08249579113843053 * fTemp46);
			double fTemp62 = (0.07777777777777778 * fTemp48);
			double fTemp63 = (0.027498597046143512 * fTemp19);
			double fTemp64 = (0.0024998724587403194 * fTemp55);
			double fTemp65 = (0.0017529949315523716 * fTemp56);
			double fTemp66 = (0.0018725475221778797 * fTemp58);
			double fTemp67 = (0.0018725475221778789 * fTemp43);
			double fTemp68 = (0.06666666666666667 + (0.10778594545965012 * fTemp46));
			double fTemp69 = (0.054997194092287024 * fTemp13);
			double fTemp70 = (0.11666666666666667 * fTemp46);
			double fTemp71 = (0.03888888888888889 * fTemp50);
			double fTemp72 = (0.0035353535353535356 * fTemp55);
			double fTemp73 = (0.0026481821020520905 * fTemp58);
			double fTemp74 = (0.05499719409228705 * fTemp13);
			double fTemp75 = (0.08249579113843053 * fTemp6);
			double fTemp76 = ((((((((((((0.05499719409228696 * fTemp13) + (((0.06666666666666667 - (0.04464640044259388 * fTemp46)) + (0.10778594545965009 * fTemp6)) - (0.05499719409228711 * fTemp48))) - (0.0359286484865501 * fTemp50)) + (0.014882133480864467 * fTemp19)) - fTemp54) - (3.810887590166739e-17 * fTemp25)) - (0.003266240771504547 * fTemp55)) - (0.0013529212255331507 * fTemp31)) - (0.0012395546034863203 * fTemp56)) - (0.0012395546034863392 * fTemp37)) - (0.0010134154163410766 * fTemp58)) - (0.002446601242448649 * fTemp43));
			double fTemp77 = (iTemp1 + (faustpower<2>(fRec0[0]) * iTemp0));
			output0[i] = (FAUSTFLOAT)((fTemp3 * (((((((((fTemp45 + (0.9807852804032304 * fTemp60)) + (0.9876883405951377 * ((((((((((((((0.06666666666666667 + fTemp61) + (0.08249579113843054 * fTemp6)) + fTemp62) + (4.762515330017485e-18 * fTemp13)) + (0.027498597046143516 * fTemp50)) - fTemp63) + (1.7318237563699945e-18 * fTemp53)) - fTemp26) - fTemp64) - (0.0024998724587403202 * fTemp31)) - fTemp65) - (3.220199447770718e-19 * fTemp37)) - fTemp66) + fTemp67))) + (0.9238795325112867 * (((((((((((((fTemp68 + (0.04464640044259381 * fTemp6)) + (0.05499719409228703 * fTemp48)) - fTemp69) - (0.014882133480864599 * fTemp50)) - (0.035928648486550044 * fTemp19)) - fTemp54) - (2.5977356345549916e-18 * fTemp25)) - (0.001352921225533148 * fTemp55)) + (0.0032662407715045483 * fTemp31)) + (0.0012395546034863294 * fTemp56)) + (0.00123955460348633 * fTemp37)) + (0.0024466012424486424 * fTemp58)) - (0.0010134154163410926 * fTemp43)))) + (0.8090169943749475 * (((((((fTemp26 + (((((((0.06666666666666667 + fTemp70) + (7.143772995026227e-18 * fTemp6)) + (9.52503066003497e-18 * fTemp48)) - fTemp14) - fTemp71) - (7.143772995026227e-18 * fTemp19)) - (3.463647512739989e-18 * fTemp53))) + fTemp72) + (1.0823898477312466e-18 * fTemp31)) + (6.440398895541436e-19 * fTemp56)) - fTemp38) - fTemp73) - (1.1350807071930908e-18 * fTemp43)))) + (0.6494480483301838 * ((((((((fTemp54 + ((0.03592864848655004 * fTemp19) + ((((fTemp68 - (0.0446464004425938 * fTemp6)) - fTemp49) - fTemp74) - (0.014882133480864626 * fTemp50)))) + (4.329559390924986e-18 * fTemp25)) - (0.0013529212255331457 * fTemp55)) - (0.003266240771504549 * fTemp31)) - (0.0012395546034863314 * fTemp56)) + (0.001239554603486328 * fTemp37)) + (0.0024466012424486415 * fTemp58)) + (0.0010134154163410948 * fTemp43)))) + (0.45399049973954686 * ((((fTemp65 + ((0.0024998724587403163 * fTemp31) + ((((5.195471269109983e-18 * fTemp53) + (((0.02749859704614351 * fTemp50) + ((((0.06666666666666667 + (0.08249579113843054 * fTemp46)) - fTemp75) - fTemp62) - (1.4287545990052454e-17 * fTemp13))) + (0.027498597046143526 * fTemp19))) - fTemp26) - (0.002499872458740323 * fTemp55)))) + (9.660598343312154e-19 * fTemp37)) - fTemp66) - fTemp67))) + (0.2334453638559055 * (((((((0.0032662407715045483 * fTemp55) + ((((fTemp51 + (fTemp69 + (((0.06666666666666667 + (0.04464640044259381 * fTemp46)) - fTemp47) - (0.05499719409228705 * fTemp48)))) - fTemp52) - fTemp54) - (6.061383147294981e-18 * fTemp25))) + (0.0013529212255331488 * fTemp31)) - (0.00123955460348633 * fTemp56)) - fTemp57) + (0.0010134154163410874 * fTemp58)) + (0.002446601242448644 * fTemp43)))) + (1.2246467991473532e-16 * (((fTemp38 + ((((fTemp26 + ((((1.4287545990052454e-17 * fTemp50) + (fTemp14 + (((0.06666666666666667 + (1.4287545990052454e-17 * fTemp46)) - fTemp7) - (1.905006132006994e-17 * fTemp48)))) - fTemp20) - (6.927295025479978e-18 * fTemp53))) + (2.164779695462493e-18 * fTemp55)) - fTemp32) - (1.2880797791082871e-18 * fTemp56))) + (2.2701614143861816e-18 * fTemp58)) - fTemp44))) + (0.19509032201612825 * fTemp76))) / fTemp77);
			output1[i] = (FAUSTFLOAT)((fTemp3 * ((((((((fTemp45 + (0.19509032201612825 * fTemp60)) + (0.2334453638559054 * (fTemp59 + (((((((fTemp54 + (((fTemp74 + (((0.06666666666666667 - (0.04464640044259379 * fTemp46)) - fTemp47) + (0.05499719409228702 * fTemp48))) - (0.03592864848655003 * fTemp50)) - (0.014882133480864633 * fTemp19))) + (7.793206903664976e-18 * fTemp25)) - (0.0032662407715045496 * fTemp55)) + (0.0013529212255331449 * fTemp31)) + (0.001239554603486332 * fTemp56)) - (0.0012395546034863277 * fTemp37)) - (0.0010134154163410917 * fTemp58))))) + (0.45399049973954675 * ((((((fTemp64 + (((8.659118781849973e-18 * fTemp53) + ((((fTemp62 + ((0.06666666666666667 - fTemp61) - (0.08249579113843057 * fTemp6))) + (2.3812576650087427e-17 * fTemp13)) - (0.027498597046143554 * fTemp50)) + (0.02749859704614348 * fTemp19))) - fTemp26)) + (0.0024998724587403194 * fTemp31)) - fTemp65) - (4.7240442599823884e-18 * fTemp37)) + (0.0018725475221778828 * fTemp58)) - (0.0018725475221778756 * fTemp43)))) + (0.6494480483301837 * ((((((((((((((0.06666666666666667 - (0.10778594545965009 * fTemp46)) - (0.044646400442593874 * fTemp6)) + (0.0549971940922871 * fTemp48)) - (0.05499719409228697 * fTemp13)) + (0.014882133480864536 * fTemp50)) + (0.035928648486550065 * fTemp19)) - fTemp54) - (3.46452283889274e-17 * fTemp25)) + (0.0013529212255331555 * fTemp55)) - (0.0032662407715045453 * fTemp31)) + (0.001239554603486325 * fTemp56)) + (0.0012395546034863342 * fTemp37)) - (0.0024466012424486467 * fTemp58)) + (0.001013415416341082 * fTemp43)))) + (0.8090169943749473 * ((fTemp73 + (((((fTemp26 + (((fTemp71 + ((((0.06666666666666667 - fTemp70) - (2.143131898507868e-17 * fTemp6)) + (2.857509198010491e-17 * fTemp48)) - fTemp14)) + (2.1431318985078683e-17 * fTemp19)) - (1.0390942538219966e-17 * fTemp53))) - fTemp72) - (9.527218975416847e-18 * fTemp31)) + (1.932119668662431e-18 * fTemp56)) - fTemp38)) - (1.298874267378291e-18 * fTemp43)))) + (0.9238795325112867 * ((((((((fTemp54 + ((((((0.06666666666666667 - (0.1077859454596501 * fTemp46)) + (0.04464640044259383 * fTemp6)) - (0.054997194092287066 * fTemp48)) - (0.05499719409228701 * fTemp13)) + (0.014882133480864578 * fTemp50)) - (0.03592864848655006 * fTemp19))) - (1.3863343312487467e-17 * fTemp25)) + (0.0013529212255331496 * fTemp55)) + (0.0032662407715045474 * fTemp31)) - (0.0012395546034863279 * fTemp56)) + (0.0012395546034863316 * fTemp37)) - (0.0024466012424486476 * fTemp58)) - (0.0010134154163410796 * fTemp43)))) + (0.9876883405951378 * ((((fTemp65 + (((((1.2122766294589962e-17 * fTemp53) + (((((fTemp75 + (0.06666666666666667 - (0.08249579113843057 * fTemp46))) - fTemp62) - (3.3337607310122396e-17 * fTemp13)) - (0.027498597046143526 * fTemp50)) - fTemp63)) - fTemp26) + (0.002499872458740324 * fTemp55)) - (0.0024998724587403146 * fTemp31))) - (8.598049226575266e-19 * fTemp37)) + (0.0018725475221778715 * fTemp58)) + (0.0018725475221778869 * fTemp43)))) + (0.9807852804032304 * fTemp76))) / fTemp77);
			// post processing
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
		}
	}
};



/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/


/* Faust code wrapper ------- */

#include "ext.h"
#include "z_dsp.h"
#include <string.h>

#define ASSIST_INLET 	1  		/* should be defined somewhere ?? */
#define ASSIST_OUTLET 	2		/* should be defined somewhere ?? */

#define EXTERNAL_VERSION "0.51"

class mspUI;

struct Max_Meta1 : Meta
{
    int fCount;
    
    Max_Meta1():fCount(0)
    {}
     
    void declare(const char* key, const char* value)
    {
        if ((strcmp("name", key) == 0) || (strcmp("author", key) == 0)) {
            fCount++;
        }
    }
};

struct Max_Meta2 : Meta
{
    void declare(const char* key, const char* value)
    {
        if ((strcmp("name", key) == 0) || (strcmp("author", key) == 0)) {
            post("%s : %s", key, value);
        }
    }
};


/*--------------------------------------------------------------------------*/
typedef struct faust
    {
    t_pxobject m_ob;
    t_atom *m_seen, *m_want;
    short m_where;
    bool m_mute;
    void** args;
    mspUI* dspUI;
    mydsp* dsp;
} t_faust;

void *faust_class;

/*--------------------------------------------------------------------------*/
class mspUIObject {

	protected:

		string fLabel;
		double* fZone;

		double range(double min, double max, double val) {return (val < min) ? min : (val > max) ? max : val;}

	public:

		mspUIObject(const char* label, double* zone):fLabel(label),fZone(zone) {}
		virtual ~mspUIObject() {}

		virtual void setValue(double f) {*fZone = range(0.0,1.0,f);}
		virtual void toString(char* buffer) {}
		virtual string getName() {return fLabel;}
};

/*--------------------------------------------------------------------------*/
class mspCheckButton : public mspUIObject {

	public:

		mspCheckButton(const char* label, double* zone):mspUIObject(label,zone) {}
		virtual ~mspCheckButton() {}

		void toString(char* buffer)
		{
            sprintf(buffer, "CheckButton(double): %s", fLabel.c_str());
		}
};

/*--------------------------------------------------------------------------*/
class mspButton : public mspUIObject {

	public:

		mspButton(const char* label, double* zone):mspUIObject(label,zone) {}
		virtual ~mspButton() {}

		void toString(char* buffer)
		{
            sprintf(buffer, "Button(double): %s", fLabel.c_str());
		}
};

/*--------------------------------------------------------------------------*/
class mspSlider : public mspUIObject {

	private:

		double fInit;
		double fMin;
		double fMax;
		double fStep;

	public:

		mspSlider(const char* label, double* zone, double init, double min, double max, double step)
			:mspUIObject(label,zone),fInit(init),fMin(min),fMax(max),fStep(step) {}
		virtual ~mspSlider() {}

		void toString(char* buffer)
		{
            sprintf(buffer, "Slider(double): %s [init=%.1f:min=%.1f:max=%.1f:step=%.1f:cur=%.1f]", fLabel.c_str(), fInit, fMin, fMax, fStep, *fZone);
		}

		void setValue(double f) {*fZone = range(fMin,fMax,f);}
};

/*--------------------------------------------------------------------------*/

#define MULTI_SIZE  256

class mspUI : public UI
{
	private:

		map<string, mspUIObject*> fUITable;
        float* fMultiTable[MULTI_SIZE];
        int fMultiIndex;
        int fMultiControl;

	public:
    
		typedef map<string,mspUIObject*>::iterator iterator;

		mspUI() 
        {
     		for (int i = 0; i < MULTI_SIZE; i++) {
                fMultiTable[i] = 0;
            }
            fMultiIndex = fMultiControl = 0;
        }
		virtual ~mspUI()
		{
			for (iterator iter = fUITable.begin(); iter != fUITable.end(); iter++) {
                delete (iter->second);
            }
   		}
        
        void openTabBox(const char* label) {}
		void openHorizontalBox(const char* label) {}
		void openVerticalBox(const char* label) {}
		void closeBox() {}

		void addButton(const char* label, double* zone) {fUITable[string(label)] = new mspButton(label, zone);}

		void addCheckButton(const char* label, double* zone) {fUITable[string(label)] = new mspCheckButton(label, zone);}

		void addVerticalSlider(const char* label, double* zone, double init, double min, double max, double step)
		{
			fUITable[string(label)] = new mspSlider(label, zone, init, min, max, step);
		}

		void addHorizontalSlider(const char* label, double* zone, double init, double min, double max, double step)
		{
			fUITable[string(label)] = new mspSlider(label, zone, init, min, max, step);
		}

		void addNumEntry(const char* label, double* zone, double init, double min, double max, double step)
		{
			fUITable[string(label)] = new mspSlider(label, zone, init, min, max, step);
		}
        
        // To be implemented
        void addHorizontalBargraph(const char* label, double* zone, double min, double max) {}
		void addVerticalBargraph(const char* label, double* zone, double min, double max) {}
        
        virtual void declare(float* zone, const char* key, const char* val)
        {
            if (strcmp(key,"multi") == 0) {
                int index = atoi(val);
                if (index >= 0 && index < MULTI_SIZE) {
                    fMultiTable[index] = zone;
                    fMultiControl++;
                } else {
                    post("Invalid multi index = %d", index);
                }
            }
        }
        
        void setMultiValues(double* multi, int buffer_size)
		{
            for (int read = 0; read < buffer_size; read++) {
                int write = (fMultiIndex + read) & (MULTI_SIZE - 1);
                if (fMultiTable[write]) {
                    *fMultiTable[write] = multi[read];
                }
            }
            fMultiIndex += buffer_size;
		}
        
        bool isMulti() { return fMultiControl > 0; }

		bool setValue(string name, double f)
		{
			if (fUITable.count(name)) {
                fUITable[name]->setValue(f);
                return true;
            } else {
                return false;
            }
		}
		iterator begin()	{ return fUITable.begin(); }
		iterator end()		{ return fUITable.end(); }

};

//--------------------------------------------------------------------------
static bool check_digit(const string& name)
{
    for (int i = name.size() - 1; i >= 0; i--) {
        if (isdigit(name[i])) return true;
    }
    return false;
}

static int count_digit(const string& name)
{
    int count = 0;
    for (int i = name.size() - 1; i >= 0; i--) {
        if (isdigit(name[i])) count++;
    }
    return count;
}

void faust_method(t_faust* obj, t_symbol* s, short ac, t_atom* av)
{
    bool res = false;
    
    if (ac < 0) return;
    
    // Check if no argument is there, consider it is a toggle message for a button
    if (ac == 0) {
        
        string name = string((s)->s_name);
        float off = 0.0f;
        float on = 1.0f;
        obj->dspUI->setValue(name, off);
        obj->dspUI->setValue(name, on);
        
        av[0].a_type = A_FLOAT;
        av[0].a_w.w_float = off;
        faust_method(obj, s, 1, av);
        
        return;
    }

    string name = string((s)->s_name);
    //printf("param_name name = %s  ac = %d\n", (s)->s_name, ac);
    
    // List of values
    if (check_digit(name)) {
        
        int ndigit = 0;
        int pos;
        
        for (pos = name.size() - 1; pos >= 0; pos--) {
            if (isdigit(name[pos]) || name[pos] == ' ') {
                ndigit++;
            } else {
                break;
            }
        }
        pos++;
        
        string prefix = name.substr(0, pos);
        string num_base = name.substr(pos);
        int num = atoi(num_base.c_str());
        
        int i;
        t_atom* ap;
       
        // Increment ap each time to get to the next atom
        for (i = 0, ap = av; i < ac; i++, ap++) {
            float value;
            switch (atom_gettype(ap)) {
                case A_LONG: {
                    value = (float)ap[0].a_w.w_long;
                    break;
                }
                case A_FLOAT:
                    value = ap[0].a_w.w_float;
                    break;
                    
                default:
                    post("Invalid argument in parameter setting"); 
                    return;         
            }
            
            stringstream num_val;
            num_val << num + i;
            char param_name[256];
            
            switch (ndigit - count_digit(num_val.str())) {
                case 0: 
                    sprintf(param_name, "%s%s", prefix.c_str(), num_val.str().c_str());
                    break;
                case 1: 
                    sprintf(param_name, "%s %s", prefix.c_str(), num_val.str().c_str());
                    break;
                case 2: 
                    sprintf(param_name, "%s  %s", prefix.c_str(), num_val.str().c_str());
                    break;
            }
            
            //printf("param_name = %s value = %f\n", param_name, value);
            res = obj->dspUI->setValue(param_name, value); // Doesn't have any effect if name is unknown
        }
    // Standard parameter
    } else {
        float value = (av[0].a_type == A_LONG) ? (float)av[0].a_w.w_long : av[0].a_w.w_float;
        res = obj->dspUI->setValue(name, value); // Doesn't have any effect if name is unknown
    }
    
    if (!res) {
        post("Unknown parameter : %s", (s)->s_name);
    }
}

/*--------------------------------------------------------------------------*/
void* faust_new(t_symbol* s, short ac, t_atom* av)
{
    t_faust* x = (t_faust*)newobject(faust_class);

    x->m_mute = false;

    x->dsp = new mydsp();
    x->dspUI = new mspUI();

    x->dsp->init(long(sys_getsr()));
    x->dsp->buildUserInterface(x->dspUI);
    
    int num_input;
    
    if (x->dspUI->isMulti()) {
        num_input = x->dsp->getNumInputs() + 1;
    } else {
        num_input = x->dsp->getNumInputs();
    }
    
    x->args = (void**)calloc((num_input + x->dsp->getNumOutputs()) + 2, sizeof(void*));
    /* Multi in */
    dsp_setup((t_pxobject*)x, num_input);

    /* Multi out */
    for (int i = 0; i< x->dsp->getNumOutputs(); i++) {
        outlet_new((t_pxobject*)x, (char*)"signal");
    }

    ((t_pxobject*)x)->z_misc = Z_NO_INPLACE; // To assure input and output buffers are actually different
    return x;
}

/*--------------------------------------------------------------------------*/
void faust_assist(t_faust* x, void* b, long msg, long a, char* dst)
{
    if (msg == ASSIST_INLET) {
        if (a == 0) {
            if (x->dsp->getNumInputs() == 0) {
                sprintf(dst, "(signal) : Unused Input");
            } else {
                sprintf(dst, "(signal) : Audio Input %ld", (a+1));
			}
			post((char*)"------------------");
			for (mspUI::iterator it = x->dspUI->begin(); it != x->dspUI->end(); ++it) {
				char param[256];
				it->second->toString(param);
				post(param);
			}
        } else if (a < x->dsp->getNumInputs()) {
            sprintf(dst, "(signal) : Audio Input %ld", (a+1));
        }
    } else if (msg == ASSIST_OUTLET) {
        sprintf(dst, "(signal) : Audio Output %ld", (a+1));
    }
}

/*--------------------------------------------------------------------------*/
void faust_mute(t_faust* obj, t_symbol* s, short ac, t_atom* at)
{
    if (atom_gettype(at) == A_LONG) {
        obj->m_mute = atom_getlong(at);
    }
}

/*--------------------------------------------------------------------------*/
void faust_free(t_faust* x)
{
	dsp_free((t_pxobject*)x);
	if (x->dsp) delete x->dsp;
	if (x->dspUI) delete x->dspUI;
	if (x->args) free(x->args);
}

/*--------------------------------------------------------------------------*/
void faust_perform64(t_faust* x, t_object* dsp64, double** ins, long numins, double** outs, long numouts, long sampleframes, long flags, void* userparam)
{
    AVOIDDENORMALS;
    if (x->m_mute) {
        // Write null buffers to outs
        for (int i = 0; i < numouts; i++) {
             memset(outs[i], 0, sizeof(double) * sampleframes);
        }
    } else {
        if (x->dspUI->isMulti()) {
            x->dspUI->setMultiValues(ins[0], sampleframes);
            x->dsp->compute(sampleframes, ++ins, outs);
        } else {
            x->dsp->compute(sampleframes, ins, outs);
        }
    }
}

/*--------------------------------------------------------------------------*/
void faust_dsp64(t_faust* x, t_object* dsp64, short* count, double samplerate, long maxvectorsize, long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, faust_perform64, 0, NULL);
}

/*--------------------------------------------------------------------------*/
extern "C" int main(void)
{
	setup((t_messlist**)&faust_class, (method)faust_new, (method)faust_free,
		(short)sizeof(t_faust), 0L, A_DEFFLOAT, 0);

	dsp* thedsp = new mydsp();
    mspUI dspUI;
	thedsp->buildUserInterface(&dspUI);

	// Add the same method for every parameters and use the symbol as a selector
	// inside this method
	for (mspUI::iterator it = dspUI.begin(); it != dspUI.end(); ++it) {
		char* name = const_cast<char*>(it->second->getName().c_str());
		addmess((method)faust_method, name, A_GIMME, 0);
	}

    addmess((method)faust_dsp64, (char*)"dsp64", A_CANT, 0);
	addmess((method)faust_assist, (char*)"assist", A_CANT, 0);
    addmess((method)faust_mute, (char*)"mute", A_GIMME, 0);
	dsp_initclass();

	post((char*)"Faust DSP object 64 bits v%s", EXTERNAL_VERSION);
    post((char*)"Copyright (c) 2012 Grame");
    Max_Meta1 meta1;
    mydsp::metadata(&meta1);
    if (meta1.fCount > 0) {
        Max_Meta2 meta2;
        post("------------------------------");
        mydsp::metadata(&meta2);
        post("------------------------------");
    }
    
    delete(thedsp);
	return 0;
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/




