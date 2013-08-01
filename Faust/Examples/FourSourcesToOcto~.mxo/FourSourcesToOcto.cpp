//-----------------------------------------------------
// name: "FourSourcesToOcto"
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
	FAUSTFLOAT 	fslider2;
	double 	fRec2[2];
	FAUSTFLOAT 	fslider3;
	double 	fRec3[2];
	FAUSTFLOAT 	fslider4;
	double 	fRec4[2];
	FAUSTFLOAT 	fslider5;
	double 	fRec5[2];
	FAUSTFLOAT 	fslider6;
	double 	fRec6[2];
	FAUSTFLOAT 	fslider7;
	double 	fRec7[2];
  public:
	static void metadata(Meta* m) 	{ 
		m->declare("name", "FourSourcesToOcto");
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

	virtual int getNumInputs() 	{ return 4; }
	virtual int getNumOutputs() 	{ return 8; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = exp((0 - (5e+01 / double(min(192000, max(1, fSamplingFreq))))));
		fConst1 = (1.0 - fConst0);
		fslider0 = 1.0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		fslider1 = 1.0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		fslider2 = 1.0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		fslider3 = 1.0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		fslider4 = 62831.0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		fslider5 = 62831.0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		fslider6 = 62831.0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		fslider7 = 62831.0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openVerticalBox("FourSourcesToOcto");
		interface->addHorizontalSlider("Angle1", &fslider4, 62831.0, -6.28318530717959, 6.28318530717959, 0.001);
		interface->addHorizontalSlider("Angle2", &fslider5, 62831.0, -6.28318530717959, 6.28318530717959, 0.001);
		interface->addHorizontalSlider("Angle3", &fslider6, 62831.0, -6.28318530717959, 6.28318530717959, 0.001);
		interface->addHorizontalSlider("Angle4", &fslider7, 62831.0, -6.28318530717959, 6.28318530717959, 0.001);
		interface->addHorizontalSlider("Radius1", &fslider0, 1.0, 0.0, 5.0, 0.001);
		interface->addHorizontalSlider("Radius2", &fslider1, 1.0, 0.0, 5.0, 0.001);
		interface->addHorizontalSlider("Radius3", &fslider2, 1.0, 0.0, 5.0, 0.001);
		interface->addHorizontalSlider("Radius4", &fslider3, 1.0, 0.0, 5.0, 0.001);
		interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		double 	fSlow0 = (fConst1 * fslider0);
		double 	fSlow1 = (fConst1 * fslider1);
		double 	fSlow2 = (fConst1 * fslider2);
		double 	fSlow3 = (fConst1 * fslider3);
		double 	fSlow4 = (fConst1 * fslider4);
		double 	fSlow5 = (fConst1 * fslider5);
		double 	fSlow6 = (fConst1 * fslider6);
		double 	fSlow7 = (fConst1 * fslider7);
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* input1 = input[1];
		FAUSTFLOAT* input2 = input[2];
		FAUSTFLOAT* input3 = input[3];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		FAUSTFLOAT* output2 = output[2];
		FAUSTFLOAT* output3 = output[3];
		FAUSTFLOAT* output4 = output[4];
		FAUSTFLOAT* output5 = output[5];
		FAUSTFLOAT* output6 = output[6];
		FAUSTFLOAT* output7 = output[7];
		for (int i=0; i<count; i++) {
			double fTemp0 = (double)input0[i];
			fRec0[0] = (fSlow0 + (fConst0 * fRec0[1]));
			int iTemp1 = (fRec0[0] > 1);
			int iTemp2 = (fRec0[0] < 1);
			double fTemp3 = (iTemp1 + (fRec0[0] * iTemp2));
			double fTemp4 = (1 + (1.3862943611198906 * (0 - (fTemp3 - 1))));
			double fTemp5 = (fTemp0 * fTemp4);
			double fTemp6 = (iTemp2 + (faustpower<2>(fRec0[0]) * iTemp1));
			double fTemp7 = (double)input1[i];
			fRec1[0] = (fSlow1 + (fConst0 * fRec1[1]));
			int iTemp8 = (fRec1[0] > 1);
			int iTemp9 = (fRec1[0] < 1);
			double fTemp10 = (iTemp8 + (fRec1[0] * iTemp9));
			double fTemp11 = (1 + (1.3862943611198906 * (0 - (fTemp10 - 1))));
			double fTemp12 = (fTemp7 * fTemp11);
			double fTemp13 = (iTemp9 + (faustpower<2>(fRec1[0]) * iTemp8));
			double fTemp14 = (double)input2[i];
			fRec2[0] = (fSlow2 + (fConst0 * fRec2[1]));
			int iTemp15 = (fRec2[0] > 1);
			int iTemp16 = (fRec2[0] < 1);
			double fTemp17 = (iTemp15 + (fRec2[0] * iTemp16));
			double fTemp18 = (1 + (1.3862943611198906 * (0 - (fTemp17 - 1))));
			double fTemp19 = (fTemp14 * fTemp18);
			double fTemp20 = (iTemp16 + (faustpower<2>(fRec2[0]) * iTemp15));
			double fTemp21 = (double)input3[i];
			fRec3[0] = (fSlow3 + (fConst0 * fRec3[1]));
			int iTemp22 = (fRec3[0] > 1);
			int iTemp23 = (fRec3[0] < 1);
			double fTemp24 = (iTemp22 + (fRec3[0] * iTemp23));
			double fTemp25 = (1 + (1.3862943611198906 * (0 - (fTemp24 - 1))));
			double fTemp26 = (fTemp21 * fTemp25);
			double fTemp27 = (iTemp23 + (faustpower<2>(fRec3[0]) * iTemp22));
			double fTemp28 = (0.14285714285714285 * ((((fTemp5 / fTemp6) + (fTemp12 / fTemp13)) + (fTemp19 / fTemp20)) + (fTemp26 / fTemp27)));
			double fTemp29 = (2.0 * fTemp3);
			double fTemp30 = ((2.0 * ((fTemp3 * (fTemp29 > 0)) * (fTemp29 <= 1))) + (fTemp29 > 1));
			fRec4[0] = (fSlow4 + (fConst0 * fRec4[1]));
			double fTemp31 = (2.0 * fTemp10);
			double fTemp32 = ((2.0 * ((fTemp10 * (fTemp31 > 0)) * (fTemp31 <= 1))) + (fTemp31 > 1));
			fRec5[0] = (fSlow5 + (fConst0 * fRec5[1]));
			double fTemp33 = (2.0 * fTemp17);
			double fTemp34 = ((2.0 * ((fTemp17 * (fTemp33 > 0)) * (fTemp33 <= 1))) + (fTemp33 > 1));
			fRec6[0] = (fSlow6 + (fConst0 * fRec6[1]));
			double fTemp35 = (2.0 * fTemp24);
			double fTemp36 = ((2.0 * ((fTemp24 * (fTemp35 > 0)) * (fTemp35 <= 1))) + (fTemp35 > 1));
			fRec7[0] = (fSlow7 + (fConst0 * fRec7[1]));
			double fTemp37 = ((((((fTemp5 * fTemp30) * cos(fRec4[0])) / fTemp6) + (((fTemp12 * fTemp32) * cos(fRec5[0])) / fTemp13)) + (((fTemp19 * fTemp34) * cos(fRec6[0])) / fTemp20)) + (((fTemp26 * fTemp36) * cos(fRec7[0])) / fTemp27));
			double fTemp38 = (0.21428571428571427 * fTemp37);
			double fTemp39 = (1.3862943611198906 * fTemp3);
			double fTemp40 = (fTemp39 - 0.6931471805599453);
			double fTemp41 = (2.466303462376431 * fTemp40);
			double fTemp42 = ((2.466303462376431 * ((fTemp40 * (fTemp41 > 0)) * (fTemp41 <= 1))) + (fTemp41 > 1));
			double fTemp43 = (2 * fRec4[0]);
			double fTemp44 = (1.3862943611198906 * fTemp10);
			double fTemp45 = (fTemp44 - 0.6931471805599453);
			double fTemp46 = (2.466303462376431 * fTemp45);
			double fTemp47 = ((2.466303462376431 * (((fTemp46 > 0) * fTemp45) * (fTemp46 <= 1))) + (fTemp46 > 1));
			double fTemp48 = (2 * fRec5[0]);
			double fTemp49 = (1.3862943611198906 * fTemp17);
			double fTemp50 = (fTemp49 - 0.6931471805599453);
			double fTemp51 = (2.466303462376431 * fTemp50);
			double fTemp52 = ((2.466303462376431 * (((fTemp51 > 0) * fTemp50) * (fTemp51 <= 1))) + (fTemp51 > 1));
			double fTemp53 = (2 * fRec6[0]);
			double fTemp54 = (1.3862943611198906 * fTemp24);
			double fTemp55 = (fTemp54 - 0.6931471805599453);
			double fTemp56 = (2.466303462376431 * fTemp55);
			double fTemp57 = ((2.466303462376431 * (((fTemp56 > 0) * fTemp55) * (fTemp56 <= 1))) + (fTemp56 > 1));
			double fTemp58 = (2 * fRec7[0]);
			double fTemp59 = ((((((fTemp5 * fTemp42) * cos(fTemp43)) / fTemp6) + (((fTemp12 * fTemp47) * cos(fTemp48)) / fTemp13)) + (((fTemp19 * fTemp52) * cos(fTemp53)) / fTemp20)) + (((fTemp26 * fTemp57) * cos(fTemp58)) / fTemp27));
			double fTemp60 = (0.0857142857142857 * fTemp59);
			double fTemp61 = (3 * fRec4[0]);
			double fTemp62 = (fTemp39 - 1.0986122886681098);
			double fTemp63 = (3.4760594967822085 * fTemp62);
			double fTemp64 = ((3.4760594967822085 * ((fTemp62 * (fTemp63 > 0)) * (fTemp63 <= 1))) + (fTemp63 > 1));
			double fTemp65 = (3 * fRec5[0]);
			double fTemp66 = (fTemp44 - 1.0986122886681098);
			double fTemp67 = (3.4760594967822085 * fTemp66);
			double fTemp68 = ((3.4760594967822085 * ((fTemp66 * (fTemp67 > 0)) * (fTemp67 <= 1))) + (fTemp67 > 1));
			double fTemp69 = (3 * fRec6[0]);
			double fTemp70 = (fTemp49 - 1.0986122886681098);
			double fTemp71 = (3.4760594967822085 * fTemp70);
			double fTemp72 = ((3.4760594967822085 * ((fTemp70 * (fTemp71 > 0)) * (fTemp71 <= 1))) + (fTemp71 > 1));
			double fTemp73 = (3 * fRec7[0]);
			double fTemp74 = (fTemp54 - 1.0986122886681098);
			double fTemp75 = (3.4760594967822085 * fTemp74);
			double fTemp76 = ((3.4760594967822085 * ((fTemp74 * (fTemp75 > 0)) * (fTemp75 <= 1))) + (fTemp75 > 1));
			double fTemp77 = (((((((fTemp0 * cos(fTemp61)) * fTemp4) * fTemp64) / fTemp6) + ((((fTemp7 * cos(fTemp65)) * fTemp11) * fTemp68) / fTemp13)) + ((((fTemp14 * cos(fTemp69)) * fTemp18) * fTemp72) / fTemp20)) + ((((fTemp21 * cos(fTemp73)) * fTemp25) * fTemp76) / fTemp27));
			double fTemp78 = (0.014285714285714285 * fTemp77);
			output0[i] = (FAUSTFLOAT)(((fTemp28 + fTemp38) + fTemp60) + fTemp78);
			double fTemp79 = ((((((fTemp5 * sin(fRec4[0])) * fTemp30) / fTemp6) + (((fTemp12 * sin(fRec5[0])) * fTemp32) / fTemp13)) + (((fTemp19 * sin(fRec6[0])) * fTemp34) / fTemp20)) + (((fTemp26 * sin(fRec7[0])) * fTemp36) / fTemp27));
			double fTemp80 = (0.15152288168283157 * fTemp79);
			double fTemp81 = ((((((fTemp5 * sin(fTemp43)) * fTemp42) / fTemp6) + (((fTemp12 * sin(fTemp48)) * fTemp47) / fTemp13)) + (((fTemp19 * sin(fTemp53)) * fTemp52) / fTemp20)) + (((fTemp26 * sin(fTemp58)) * fTemp57) / fTemp27));
			double fTemp82 = (0.0857142857142857 * fTemp81);
			double fTemp83 = (((((((fTemp0 * sin(fTemp61)) * fTemp4) * fTemp64) / fTemp6) + ((((fTemp7 * sin(fTemp65)) * fTemp11) * fTemp68) / fTemp13)) + ((((fTemp14 * sin(fTemp69)) * fTemp18) * fTemp72) / fTemp20)) + ((((fTemp21 * sin(fTemp73)) * fTemp25) * fTemp76) / fTemp27));
			double fTemp84 = (0.010101525445522105 * fTemp77);
			output1[i] = (FAUSTFLOAT)((((((fTemp28 + fTemp80) + (0.15152288168283162 * fTemp37)) + fTemp82) + (5.248486282060085e-18 * fTemp59)) + (0.010101525445522109 * fTemp83)) - fTemp84);
			double fTemp85 = (0.21428571428571427 * fTemp79);
			double fTemp86 = (0.014285714285714285 * fTemp83);
			output2[i] = (FAUSTFLOAT)((((fTemp28 + fTemp85) + (1.3121215705150213e-17 * fTemp37)) + (1.049697256412017e-17 * fTemp81)) - ((fTemp60 + fTemp86) + (2.6242431410300424e-18 * fTemp77)));
			double fTemp87 = (0.15152288168283157 * fTemp37);
			output3[i] = (FAUSTFLOAT)((((fTemp28 + (0.15152288168283162 * fTemp79)) + (0.010101525445522105 * fTemp83)) + (0.01010152544552211 * fTemp77)) - ((fTemp82 + fTemp87) + (1.5745458846180252e-17 * fTemp59)));
			output4[i] = (FAUSTFLOAT)(((fTemp60 + (fTemp28 + (2.6242431410300427e-17 * fTemp79))) + (5.248486282060085e-18 * fTemp83)) - (fTemp78 + (fTemp38 + (2.099394512824034e-17 * fTemp81))));
			output5[i] = (FAUSTFLOAT)((((fTemp28 + fTemp82) + (2.6242431410300424e-17 * fTemp59)) + (0.010101525445522093 * fTemp77)) - ((fTemp80 + (0.15152288168283165 * fTemp37)) + (0.010101525445522121 * fTemp83)));
			output6[i] = (FAUSTFLOAT)(((fTemp86 + (fTemp28 + (3.1490917692360505e-17 * fTemp81))) + (7.872729423090128e-18 * fTemp77)) - (fTemp60 + (fTemp85 + (3.936364711545064e-17 * fTemp37))));
			output7[i] = (FAUSTFLOAT)((fTemp28 + fTemp87) - (fTemp84 + ((0.01010152544552211 * fTemp83) + ((fTemp82 + (0.15152288168283165 * fTemp79)) + (3.6739403974420595e-17 * fTemp59)))));
			// post processing
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
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




