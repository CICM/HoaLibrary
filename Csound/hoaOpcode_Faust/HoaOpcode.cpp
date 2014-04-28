//-----------------------------------------------------
// author: "Pierre Guillot", "Eliott Paris", "Julien Colafrancesco"
// copyright: "2012-2013 Guillot, Paris, Colafrancesco, CICM labex art H2H, U. Paris 8"
// name: "HOA"
//
// Code generated with Faust 2.0.a21 (http://faust.grame.fr)
//-----------------------------------------------------

#ifndef  __mydsp_H__
#define  __mydsp_H__
/************************************************************************
 
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2010-2011 V. Lazzarini and GRAME
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 
 ************************************************************************
 ************************************************************************/

//==============================================================================
//
//          CSOUND architecture file for FAUST
//          Y. Orlarey & V. Lazzarini
//
//          Usage : faust -uim -a csound.cpp <myfx>.dsp -o <myfx>.cpp
//                  g++ -O3 -DOPCODE_NAME=<myfx> -c <myfx>.cpp -o <myfx>.o
//                  ld -E --shared <myfx>.o -o <myfx>.so
//
//          History :
//          - 28/04/09 : first version
//          - 29/04/09 : dynamic allocation
//
//==============================================================================

#include <new>
#include <vector>
#include "csdl.h"                       /* CSOUND plugin API header */

// used to transform a symbol in a string
#define sym(name) xsym(name)
#define xsym(name) #name

// make sure we use csound floats
#define FAUSTFLOAT MYFLT

// we require macro declarations
#define FAUST_UIMACROS

// but we will ignore most of them
#define FAUST_ADDBUTTON(l,f)
#define FAUST_ADDCHECKBOX(l,f)
#define FAUST_ADDVERTICALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDHORIZONTALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDNUMENTRY(l,f,i,a,b,s)
#define FAUST_ADDVERTICALBARGRAPH(l,f,a,b)
#define FAUST_ADDHORIZONTALBARGRAPH(l,f,a,b)

#include "faust/misc.h"
#include "faust/audio/dsp.h"
#include "faust/gui/meta.h"
#include "faust/gui/UI.h"

/******************************************************************************
 *******************************************************************************
    
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/


/**
 * A UI that simply collects the active zones in a vector
 * and provides a method to copy the csound controls
 */
class CSUI : public UI
{
    std::vector<FAUSTFLOAT*>  vZone;
    
public:
    
    // -- widget's layouts
    
    virtual void openTabBox(const char* label)                                                          {}
    virtual void openHorizontalBox(const char* label)                                                   {}
    virtual void openVerticalBox(const char* label)                                                     {}
    virtual void closeBox()                                                                             {}
    
    // -- active widgets
    
    virtual void addButton(const char* label, FAUSTFLOAT* zone)                                                          { vZone.push_back(zone); }
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)                                                     { vZone.push_back(zone); }
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)    { vZone.push_back(zone); }
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)  { vZone.push_back(zone); }
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)          { vZone.push_back(zone); }
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)            {}
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)              {}
    
    void copyfrom(MYFLT* mem[]) {
        for (unsigned int i=0; i<vZone.size(); i++) { *vZone[i] = *(mem[i]); }
    }
    
    int size()                  { return vZone.size(); }
};

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <math.h>

float expf(float dummy0);
#ifndef __faustpower2_f__
#define __faustpower2_f__
float faustpower2_f(float value) {
	return (value * value);
	
}
#endif
float sqrtf(float dummy0);
float atan2f(float dummy0, float dummy1);
float cosf(float dummy0);
float sinf(float dummy0);

#ifndef FAUSTCLASS
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
	
private:
	
	float fRec0[2];
	float fRec1[2];
	float fRec2[2];
	float fRec3[2];
	float fRec4[2];
	float fRec5[2];
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fentry0;
	FAUSTFLOAT fhslider0;
	FAUSTFLOAT fhslider1;
	FAUSTFLOAT fhslider2;
	FAUSTFLOAT fhslider3;
	FAUSTFLOAT fhslider4;
	FAUSTFLOAT fhslider5;
	
public:
	
	void static metadata(Meta* m) {
		m->declare("author", "Pierre Guillot");
		m->declare("contributor", "Eliott Paris");
		m->declare("contributor", "Julien Colafrancesco");
		m->declare("copyright", "2012-2013 Guillot, Paris, Colafrancesco, CICM labex art H2H, U. Paris 8");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("filter.lib/version", "1.29");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/version", "1.0");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "HOA");
		m->declare("title", "High Order Ambisonics library");
	}
    
	virtual int getNumInputs() {
		return 3;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			case 2: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
                
		}
		return rate;
		
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
                
		}
		return rate;
		
	}
	
	static void classInit(int samplingFreq) {
		
	}
	
	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (1000.f / float(min(192000, max(1, fSamplingFreq))));
		fentry0 = FAUSTFLOAT(100.);
		fhslider0 = FAUSTFLOAT(0.);
		for (int i = 0; (i < 2); i = (i + 1)) {
			fRec0[i] = 0.f;
			
		}
		fhslider1 = FAUSTFLOAT(1.);
		for (int i = 0; (i < 2); i = (i + 1)) {
			fRec1[i] = 0.f;
			
		}
		fhslider2 = FAUSTFLOAT(-0.75);
		for (int i = 0; (i < 2); i = (i + 1)) {
			fRec2[i] = 0.f;
			
		}
		fhslider3 = FAUSTFLOAT(-0.75);
		for (int i = 0; (i < 2); i = (i + 1)) {
			fRec3[i] = 0.f;
			
		}
		fhslider4 = FAUSTFLOAT(0.75);
		for (int i = 0; (i < 2); i = (i + 1)) {
			fRec4[i] = 0.f;
			
		}
		fhslider5 = FAUSTFLOAT(-0.75);
		for (int i = 0; (i < 2); i = (i + 1)) {
			fRec5[i] = 0.f;
			
		}
		
	}
	
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	
	virtual void buildUserInterface(UI* interface) {
		interface->openVerticalBox("HoaLibrary");
		interface->addHorizontalSlider("Abscissa : Source 1", &fhslider0, 0.f, -2.f, 2.f, 0.001f);
		interface->addHorizontalSlider("Abscissa : Source 2", &fhslider2, -0.75f, -2.f, 2.f, 0.001f);
		interface->addHorizontalSlider("Abscissa : Source 3", &fhslider4, 0.75f, -2.f, 2.f, 0.001f);
		interface->addNumEntry("Interpolation Time", &fentry0, 100.f, 0.f, 1000.f, 0.1f);
		interface->addHorizontalSlider("Ordinate : Source 1", &fhslider1, 1.f, -2.f, 2.f, 0.001f);
		interface->addHorizontalSlider("Ordinate : Source 2", &fhslider3, -0.75f, -2.f, 2.f, 0.001f);
		interface->addHorizontalSlider("Ordinate : Source 3", &fhslider5, -0.75f, -2.f, 2.f, 0.001f);
		interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* input2 = inputs[2];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = expf((0.f - (fConst0 / float(fentry0))));
		float fSlow1 = (1.f - fSlow0);
		float fSlow2 = (fSlow1 * float(fhslider0));
		float fSlow3 = (fSlow1 * float(fhslider1));
		float fSlow4 = (fSlow1 * float(fhslider2));
		float fSlow5 = (fSlow1 * float(fhslider3));
		float fSlow6 = (float(fhslider4) * fSlow1);
		float fSlow7 = (float(fhslider5) * fSlow1);
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec0[0] = ((fSlow0 * fRec0[1]) + fSlow2);
			fRec1[0] = ((fSlow0 * fRec1[1]) + fSlow3);
			float fTemp0 = sqrtf((faustpower2_f(fRec0[0]) + faustpower2_f(fRec1[0])));
			int iTemp1 = int((fTemp0 > 1.f));
			int iTemp2 = int((fTemp0 < 1.f));
			float fTemp3 = (float(iTemp1) + (fTemp0 * float(iTemp2)));
			float fTemp4 = (1.f + (2.07944f * (0.f - (fTemp3 - 1.f))));
			float fTemp5 = float(input0[i]);
			float fTemp6 = ((faustpower2_f(fTemp0) * float(iTemp1)) + float(iTemp2));
			fRec2[0] = ((fSlow0 * fRec2[1]) + fSlow4);
			fRec3[0] = ((fSlow0 * fRec3[1]) + fSlow5);
			float fTemp7 = sqrtf((faustpower2_f(fRec2[0]) + faustpower2_f(fRec3[0])));
			int iTemp8 = int((fTemp7 > 1.f));
			int iTemp9 = int((fTemp7 < 1.f));
			float fTemp10 = (float(iTemp8) + (fTemp7 * float(iTemp9)));
			float fTemp11 = (1.f + (2.07944f * (0.f - (fTemp10 - 1.f))));
			float fTemp12 = float(input1[i]);
			float fTemp13 = ((faustpower2_f(fTemp7) * float(iTemp8)) + float(iTemp9));
			fRec4[0] = ((fSlow0 * fRec4[1]) + fSlow6);
			fRec5[0] = ((fSlow0 * fRec5[1]) + fSlow7);
			float fTemp14 = sqrtf((faustpower2_f(fRec4[0]) + faustpower2_f(fRec5[0])));
			int iTemp15 = int((fTemp14 > 1.f));
			int iTemp16 = int((fTemp14 < 1.f));
			float fTemp17 = (float(iTemp15) + (fTemp14 * float(iTemp16)));
			float fTemp18 = (1.f + (2.07944f * (0.f - (fTemp17 - 1.f))));
			float fTemp19 = float(input2[i]);
			float fTemp20 = ((faustpower2_f(fTemp14) * float(iTemp15)) + float(iTemp16));
			float fTemp21 = ((((fTemp4 * fTemp5) / fTemp6) + ((fTemp11 * fTemp12) / fTemp13)) + ((fTemp18 * fTemp19) / fTemp20));
			float fTemp22 = (0.0666667f * fTemp21);
			float fTemp23 = (3.f * fTemp3);
			float fTemp24 = ((3.f * ((fTemp3 * float(int((fTemp23 > 0.f)))) * float(int((fTemp23 <= 1.f))))) + float(int((fTemp23 > 1.f))));
			float fTemp25 = atan2f(fRec1[0], fRec0[0]);
			float fTemp26 = (3.f * fTemp10);
			float fTemp27 = ((3.f * ((fTemp10 * float(int((fTemp26 > 0.f)))) * float(int((fTemp26 <= 1.f))))) + float(int((fTemp26 > 1.f))));
			float fTemp28 = atan2f(fRec3[0], fRec2[0]);
			float fTemp29 = (3.f * fTemp17);
			float fTemp30 = ((3.f * ((fTemp17 * float(int((fTemp29 > 0.f)))) * float(int((fTemp29 <= 1.f))))) + float(int((fTemp29 > 1.f))));
			float fTemp31 = atan2f(fRec5[0], fRec4[0]);
			float fTemp32 = ((((((fTemp4 * fTemp24) * cosf(fTemp25)) * fTemp5) / fTemp6) + ((((fTemp11 * fTemp27) * cosf(fTemp28)) * fTemp12) / fTemp13)) + ((((fTemp18 * fTemp30) * cosf(fTemp31)) * fTemp19) / fTemp20));
			float fTemp33 = (2.07944f * fTemp3);
			float fTemp34 = (fTemp33 - 0.693147f);
			float fTemp35 = (2.4663f * fTemp34);
			float fTemp36 = ((2.4663f * ((fTemp34 * float(int((fTemp35 > 0.f)))) * float(int((fTemp35 <= 1.f))))) + float(int((fTemp35 > 1.f))));
			float fTemp37 = (2.f * fTemp25);
			float fTemp38 = (2.07944f * fTemp10);
			float fTemp39 = (fTemp38 - 0.693147f);
			float fTemp40 = (2.4663f * fTemp39);
			float fTemp41 = ((2.4663f * ((fTemp39 * float(int((fTemp40 > 0.f)))) * float(int((fTemp40 <= 1.f))))) + float(int((fTemp40 > 1.f))));
			float fTemp42 = (2.f * fTemp28);
			float fTemp43 = (2.07944f * fTemp17);
			float fTemp44 = (fTemp43 - 0.693147f);
			float fTemp45 = (2.4663f * fTemp44);
			float fTemp46 = ((2.4663f * ((fTemp44 * float(int((fTemp45 > 0.f)))) * float(int((fTemp45 <= 1.f))))) + float(int((fTemp45 > 1.f))));
			float fTemp47 = (2.f * fTemp31);
			float fTemp48 = ((((((fTemp4 * fTemp36) * cosf(fTemp37)) * fTemp5) / fTemp6) + ((((fTemp11 * fTemp41) * cosf(fTemp42)) * fTemp12) / fTemp13)) + ((((fTemp18 * fTemp46) * cosf(fTemp47)) * fTemp19) / fTemp20));
			float fTemp49 = (0.0777778f * fTemp48);
			float fTemp50 = (fTemp33 - 1.09861f);
			float fTemp51 = (3.47606f * fTemp50);
			float fTemp52 = ((3.47606f * ((fTemp50 * float(int((fTemp51 > 0.f)))) * float(int((fTemp51 <= 1.f))))) + float(int((fTemp51 > 1.f))));
			float fTemp53 = (3.f * fTemp25);
			float fTemp54 = (fTemp38 - 1.09861f);
			float fTemp55 = (3.47606f * fTemp54);
			float fTemp56 = ((3.47606f * ((fTemp54 * float(int((fTemp55 > 0.f)))) * float(int((fTemp55 <= 1.f))))) + float(int((fTemp55 > 1.f))));
			float fTemp57 = (3.f * fTemp28);
			float fTemp58 = (fTemp43 - 1.09861f);
			float fTemp59 = (3.47606f * fTemp58);
			float fTemp60 = ((3.47606f * ((fTemp58 * float(int((fTemp59 > 0.f)))) * float(int((fTemp59 <= 1.f))))) + float(int((fTemp59 > 1.f))));
			float fTemp61 = (3.f * fTemp31);
			float fTemp62 = ((((((fTemp4 * fTemp52) * cosf(fTemp53)) * fTemp5) / fTemp6) + ((((fTemp11 * fTemp56) * cosf(fTemp57)) * fTemp12) / fTemp13)) + ((((fTemp18 * fTemp60) * cosf(fTemp61)) * fTemp19) / fTemp20));
			float fTemp63 = (0.0388889f * fTemp62);
			float fTemp64 = (fTemp33 - 1.38629f);
			float fTemp65 = (4.48142f * fTemp64);
			float fTemp66 = ((4.48142f * ((fTemp64 * float(int((fTemp65 > 0.f)))) * float(int((fTemp65 <= 1.f))))) + float(int((fTemp65 > 1.f))));
			float fTemp67 = (4.f * fTemp25);
			float fTemp68 = (fTemp38 - 1.38629f);
			float fTemp69 = (4.48142f * fTemp68);
			float fTemp70 = ((4.48142f * ((fTemp68 * float(int((fTemp69 > 0.f)))) * float(int((fTemp69 <= 1.f))))) + float(int((fTemp69 > 1.f))));
			float fTemp71 = (4.f * fTemp28);
			float fTemp72 = (fTemp43 - 1.38629f);
			float fTemp73 = (4.48142f * fTemp72);
			float fTemp74 = ((4.48142f * ((fTemp72 * float(int((fTemp73 > 0.f)))) * float(int((fTemp73 <= 1.f))))) + float(int((fTemp73 > 1.f))));
			float fTemp75 = (4.f * fTemp31);
			float fTemp76 = ((((((fTemp4 * fTemp66) * cosf(fTemp67)) * fTemp5) / fTemp6) + ((((fTemp11 * fTemp70) * cosf(fTemp71)) * fTemp12) / fTemp13)) + ((((fTemp18 * fTemp74) * cosf(fTemp75)) * fTemp19) / fTemp20));
			float fTemp77 = (0.0141414f * fTemp76);
			float fTemp78 = (fTemp33 - 1.60944f);
			float fTemp79 = (5.48482f * fTemp78);
			float fTemp80 = ((5.48482f * ((fTemp78 * float(int((fTemp79 > 0.f)))) * float(int((fTemp79 <= 1.f))))) + float(int((fTemp79 > 1.f))));
			float fTemp81 = (5.f * fTemp25);
			float fTemp82 = (fTemp38 - 1.60944f);
			float fTemp83 = (5.48482f * fTemp82);
			float fTemp84 = ((5.48482f * ((fTemp82 * float(int((fTemp83 > 0.f)))) * float(int((fTemp83 <= 1.f))))) + float(int((fTemp83 > 1.f))));
			float fTemp85 = (5.f * fTemp28);
			float fTemp86 = (fTemp43 - 1.60944f);
			float fTemp87 = (5.48482f * fTemp86);
			float fTemp88 = ((5.48482f * ((fTemp86 * float(int((fTemp87 > 0.f)))) * float(int((fTemp87 <= 1.f))))) + float(int((fTemp87 > 1.f))));
			float fTemp89 = (5.f * fTemp31);
			float fTemp90 = ((((((fTemp4 * fTemp80) * cosf(fTemp81)) * fTemp5) / fTemp6) + ((((fTemp11 * fTemp84) * cosf(fTemp85)) * fTemp12) / fTemp13)) + ((((fTemp18 * fTemp88) * cosf(fTemp89)) * fTemp19) / fTemp20));
			float fTemp91 = (0.00353535f * fTemp90);
			float fTemp92 = (fTemp33 - 1.79176f);
			float fTemp93 = (6.48716f * fTemp92);
			float fTemp94 = ((6.48716f * ((fTemp92 * float(int((fTemp93 > 0.f)))) * float(int((fTemp93 <= 1.f))))) + float(int((fTemp93 > 1.f))));
			float fTemp95 = (6.f * fTemp25);
			float fTemp96 = (fTemp38 - 1.79176f);
			float fTemp97 = (6.48716f * fTemp96);
			float fTemp98 = ((6.48716f * ((fTemp96 * float(int((fTemp97 > 0.f)))) * float(int((fTemp97 <= 1.f))))) + float(int((fTemp97 > 1.f))));
			float fTemp99 = (6.f * fTemp28);
			float fTemp100 = (fTemp43 - 1.79176f);
			float fTemp101 = (6.48716f * fTemp100);
			float fTemp102 = ((6.48716f * ((fTemp100 * float(int((fTemp101 > 0.f)))) * float(int((fTemp101 <= 1.f))))) + float(int((fTemp101 > 1.f))));
			float fTemp103 = (6.f * fTemp31);
			float fTemp104 = ((((((fTemp4 * fTemp94) * cosf(fTemp95)) * fTemp5) / fTemp6) + ((((fTemp11 * fTemp98) * cosf(fTemp99)) * fTemp12) / fTemp13)) + ((((fTemp18 * fTemp102) * cosf(fTemp103)) * fTemp19) / fTemp20));
			float fTemp105 = (0.00175299f * fTemp104);
			float fTemp106 = (7.f * fTemp25);
			float fTemp107 = (fTemp33 - 1.94591f);
			float fTemp108 = (7.48888f * fTemp107);
			float fTemp109 = ((7.48888f * ((fTemp107 * float(int((fTemp108 > 0.f)))) * float(int((fTemp108 <= 1.f))))) + float(int((fTemp108 > 1.f))));
			float fTemp110 = (7.f * fTemp28);
			float fTemp111 = (fTemp38 - 1.94591f);
			float fTemp112 = (7.48888f * fTemp111);
			float fTemp113 = ((7.48888f * ((fTemp111 * float(int((fTemp112 > 0.f)))) * float(int((fTemp112 <= 1.f))))) + float(int((fTemp112 > 1.f))));
			float fTemp114 = (7.f * fTemp31);
			float fTemp115 = (fTemp43 - 1.94591f);
			float fTemp116 = (7.48888f * fTemp115);
			float fTemp117 = ((7.48888f * ((fTemp115 * float(int((fTemp116 > 0.f)))) * float(int((fTemp116 <= 1.f))))) + float(int((fTemp116 > 1.f))));
			float fTemp118 = ((((((cosf(fTemp106) * fTemp4) * fTemp109) * fTemp5) / fTemp6) + ((((cosf(fTemp110) * fTemp11) * fTemp113) * fTemp12) / fTemp13)) + ((((cosf(fTemp114) * fTemp18) * fTemp117) * fTemp19) / fTemp20));
			float fTemp119 = (0.00264818f * fTemp118);
			float fTemp120 = (0.707107f * (((((((fTemp22 + (0.116667f * fTemp32)) + fTemp49) + fTemp63) + fTemp77) + fTemp91) + fTemp105) + fTemp119));
			float fTemp121 = ((((((fTemp4 * sinf(fTemp25)) * fTemp24) * fTemp5) / fTemp6) + ((((fTemp11 * sinf(fTemp28)) * fTemp27) * fTemp12) / fTemp13)) + ((((fTemp18 * sinf(fTemp31)) * fTemp30) * fTemp19) / fTemp20));
			float fTemp122 = (0.107786f * fTemp32);
			float fTemp123 = ((((((fTemp4 * sinf(fTemp37)) * fTemp36) * fTemp5) / fTemp6) + ((((fTemp11 * sinf(fTemp42)) * fTemp41) * fTemp12) / fTemp13)) + ((((fTemp18 * sinf(fTemp47)) * fTemp46) * fTemp19) / fTemp20));
			float fTemp124 = (0.0549972f * fTemp123);
			float fTemp125 = ((((((fTemp4 * sinf(fTemp53)) * fTemp52) * fTemp5) / fTemp6) + ((((fTemp11 * sinf(fTemp57)) * fTemp56) * fTemp12) / fTemp13)) + ((((fTemp18 * sinf(fTemp61)) * fTemp60) * fTemp19) / fTemp20));
			float fTemp126 = (0.0359286f * fTemp125);
			float fTemp127 = ((((((fTemp4 * sinf(fTemp67)) * fTemp66) * fTemp5) / fTemp6) + ((((fTemp11 * sinf(fTemp71)) * fTemp70) * fTemp12) / fTemp13)) + ((((fTemp18 * sinf(fTemp75)) * fTemp74) * fTemp19) / fTemp20));
			float fTemp128 = (0.0141414f * fTemp127);
			float fTemp129 = ((((((fTemp4 * sinf(fTemp81)) * fTemp80) * fTemp5) / fTemp6) + ((((fTemp11 * sinf(fTemp85)) * fTemp84) * fTemp12) / fTemp13)) + ((((fTemp18 * sinf(fTemp89)) * fTemp88) * fTemp19) / fTemp20));
			float fTemp130 = ((((((fTemp4 * sinf(fTemp95)) * fTemp94) * fTemp5) / fTemp6) + ((((fTemp11 * sinf(fTemp99)) * fTemp98) * fTemp12) / fTemp13)) + ((((fTemp18 * sinf(fTemp103)) * fTemp102) * fTemp19) / fTemp20));
			float fTemp131 = ((((((sinf(fTemp106) * fTemp4) * fTemp109) * fTemp5) / fTemp6) + ((((sinf(fTemp110) * fTemp11) * fTemp113) * fTemp12) / fTemp13)) + ((((sinf(fTemp114) * fTemp18) * fTemp117) * fTemp19) / fTemp20));
			float fTemp132 = (0.0024466f * fTemp118);
			float fTemp133 = ((((((((((((fTemp22 + (0.0446464f * fTemp121)) + fTemp122) + fTemp124) + (0.0549972f * fTemp48)) + fTemp126) + (0.0148821f * fTemp62)) + fTemp128) + (8.65912e-19f * fTemp76)) + (0.00326624f * fTemp129)) + (0.00123955f * fTemp130)) + (0.00101342f * fTemp131)) - (((0.00135292f * fTemp90) + (0.00123955f * fTemp104)) + fTemp132));
			float fTemp134 = (0.0777778f * fTemp123);
			float fTemp135 = (0.00187255f * fTemp118);
			float fTemp136 = (0.00175299f * fTemp130);
			float fTemp137 = (0.00187255f * fTemp131);
			float fTemp138 = (fTemp22 + (0.107786f * fTemp121));
			float fTemp139 = (0.116667f * fTemp121);
			float fTemp140 = (0.00353535f * fTemp129);
			float fTemp141 = (0.0388889f * fTemp125);
			float fTemp142 = (0.00264818f * fTemp131);
			float fTemp143 = (0.0549972f * fTemp48);
			float fTemp144 = ((((fTemp22 + (0.107786f * fTemp32)) + (0.0549972f * fTemp48)) + (0.0148821f * fTemp62)) - ((((((((fTemp128 + (((0.0446464f * fTemp121) + (0.0549972f * fTemp123)) + (0.0359286f * fTemp125))) + (3.81089e-17f * fTemp76)) + (0.00326624f * fTemp129)) + (0.00135292f * fTemp90)) + (0.00123955f * fTemp130)) + (0.00123955f * fTemp104)) + (0.00101342f * fTemp131)) + (0.0024466f * fTemp118)));
			output0[i] = FAUSTFLOAT((((((((((fTemp120 + (0.980785f * fTemp133)) + (0.987688f * ((((((((fTemp22 + (0.0824958f * fTemp121)) + (0.0824958f * fTemp32)) + fTemp134) + (4.76252e-18f * fTemp48)) + (0.0274986f * fTemp125)) + (1.73182e-18f * fTemp127)) + fTemp135) - ((((((fTemp77 + (0.0274986f * fTemp62)) + (0.00249987f * fTemp129)) + (0.00249987f * fTemp90)) + fTemp136) + (3.2202e-19f * fTemp104)) + fTemp137)))) + (0.92388f * (((((((fTemp138 + (0.0446464f * fTemp32)) + (0.0549972f * fTemp123)) + (0.00326624f * fTemp90)) + (0.00123955f * fTemp130)) + (0.00123955f * fTemp104)) + (0.0024466f * fTemp131)) - ((((fTemp128 + (((0.0549972f * fTemp48) + (0.0148821f * fTemp125)) + (0.0359286f * fTemp62))) + (2.59774e-18f * fTemp76)) + (0.00135292f * fTemp129)) + (0.00101342f * fTemp118))))) + (0.809017f * (((((fTemp77 + (((fTemp22 + fTemp139) + (7.14377e-18f * fTemp32)) + (9.52503e-18f * fTemp123))) + fTemp140) + (1.08239e-18f * fTemp90)) + (6.4404e-19f * fTemp130)) - (((fTemp105 + (((fTemp49 + fTemp141) + (7.14377e-18f * fTemp62)) + (3.46365e-18f * fTemp127))) + fTemp142) + (1.13508e-18f * fTemp118))))) + (0.649448f * ((((((fTemp128 + (fTemp138 + (0.0359286f * fTemp62))) + (4.32956e-18f * fTemp76)) + (0.00123955f * fTemp104)) + (0.0024466f * fTemp131)) + (0.00101342f * fTemp118)) - ((((((fTemp124 + (0.0446464f * fTemp32)) + fTemp143) + (0.0148821f * fTemp125)) + (0.00135292f * fTemp129)) + (0.00326624f * fTemp90)) + (0.00123955f * fTemp130))))) + (0.45399f * (((9.6606e-19f * fTemp104) + (fTemp136 + (((((fTemp22 + (0.0824958f * fTemp121)) + (0.0274986f * fTemp125)) + (0.0274986f * fTemp62)) + (5.19547e-18f * fTemp127)) + (0.00249987f * fTemp90)))) - (fTemp135 + (fTemp137 + ((fTemp77 + ((fTemp134 + (0.0824958f * fTemp32)) + (1.42875e-17f * fTemp48))) + (0.00249987f * fTemp129))))))) + (0.233445f * ((((((fTemp126 + ((fTemp22 + (0.0446464f * fTemp121)) + (0.0549972f * fTemp48))) + (0.00326624f * fTemp129)) + (0.00135292f * fTemp90)) + (0.00101342f * fTemp131)) + (0.0024466f * fTemp118)) - ((((fTemp128 + ((fTemp122 + (0.0549972f * fTemp123)) + (0.0148821f * fTemp62))) + (6.06138e-18f * fTemp76)) + (0.00123955f * fTemp130)) + (0.00123955f * fTemp104))))) + (1.22465e-16f * (((1.42875e-17f * ((fTemp125 + ((fTemp121 + (4.66607e+15f * fTemp21)) + (5.44375e+15f * fTemp48))) - ((8.16562e+15f * fTemp32) + (1.33333f * fTemp123)))) + ((fTemp105 + (fTemp77 + (2.16478e-18f * fTemp129))) + (2.27016e-18f * fTemp131))) - (fTemp119 + ((fTemp91 + (fTemp63 + (6.9273e-18f * fTemp127))) + (1.28808e-18f * fTemp130)))))) + (0.19509f * fTemp144)));
			output1[i] = FAUSTFLOAT(((((((((fTemp120 + (0.19509f * fTemp133)) + (0.233445f * ((fTemp132 + ((((fTemp128 + (fTemp143 + (fTemp22 + (0.0549972f * fTemp123)))) + (7.79321e-18f * fTemp76)) + (0.00135292f * fTemp90)) + (0.00123955f * fTemp130))) - (((((((0.0446464f * fTemp121) + (0.107786f * fTemp32)) + (0.0359286f * fTemp125)) + (0.0148821f * fTemp62)) + (0.00326624f * fTemp129)) + (0.00123955f * fTemp104)) + (0.00101342f * fTemp131))))) + (0.45399f * (((0.00249987f * ((fTemp90 + (fTemp129 + (((((26.668f * fTemp21) + (31.1127f * fTemp123)) + (9.52552e-15f * fTemp48)) + (11.f * fTemp62)) + (3.46382e-15f * fTemp127)))) - ((((33.f * fTemp121) + (33.f * fTemp32)) + (11.f * fTemp125)) + (5.65685f * fTemp76)))) + (0.00187255f * fTemp131)) - ((fTemp136 + (4.72404e-18f * fTemp104)) + (0.00187255f * fTemp118))))) + (0.649448f * ((((((((fTemp22 + (0.0549972f * fTemp123)) + (0.0148821f * fTemp125)) + (0.0359286f * fTemp62)) + (0.00135292f * fTemp129)) + (0.00123955f * fTemp130)) + (0.00123955f * fTemp104)) + (0.00101342f * fTemp118)) - ((((fTemp128 + (((0.107786f * fTemp121) + (0.0446464f * fTemp32)) + (0.0549972f * fTemp48))) + (3.46452e-17f * fTemp76)) + (0.00326624f * fTemp90)) + (0.0024466f * fTemp131))))) + (0.809017f * ((fTemp142 + ((fTemp77 + ((fTemp141 + (fTemp22 + (2.85751e-17f * fTemp123))) + (2.14313e-17f * fTemp62))) + (1.93212e-18f * fTemp130))) - ((fTemp105 + ((fTemp140 + ((fTemp49 + (fTemp139 + (2.14313e-17f * fTemp32))) + (1.03909e-17f * fTemp127))) + (9.52722e-18f * fTemp90))) + (1.29887e-18f * fTemp118))))) + (0.92388f * (((((fTemp128 + ((fTemp22 + (0.0446464f * fTemp32)) + (0.0148821f * fTemp125))) + (0.00135292f * fTemp129)) + (0.00326624f * fTemp90)) + (0.00123955f * fTemp104)) - ((((((((0.107786f * fTemp121) + (0.0549972f * fTemp123)) + (0.0549972f * fTemp48)) + (0.0359286f * fTemp62)) + (1.38633e-17f * fTemp76)) + (0.00123955f * fTemp130)) + (0.0024466f * fTemp131)) + (0.00101342f * fTemp118))))) + (0.987688f * ((((fTemp136 + (((fTemp22 + (0.0824958f * fTemp32)) + (1.21228e-17f * fTemp127)) + (0.00249987f * fTemp129))) + (0.00187255f * fTemp131)) + (0.00187255f * fTemp118)) - (((fTemp77 + ((((fTemp134 + (0.0824958f * fTemp121)) + (3.33376e-17f * fTemp48)) + (0.0274986f * fTemp125)) + (0.0274986f * fTemp62))) + (0.00249987f * fTemp90)) + (8.59805e-19f * fTemp104))))) + (0.980785f * fTemp144)));
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			
		}
		
	}
    
	
};


/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

struct dataspace {
    OPDS      h;                          /* basic attributes */
    MYFLT*    aout[FAUST_OUTPUTS];        /* output buffers   */
    MYFLT*    ain[FAUST_INPUTS];          /* input buffers    */
    MYFLT*    ktl[FAUST_ACTIVES];         /* controls         */
    dsp*      DSP;                        /* the Faust generated object */
    CSUI*     interface;                  /* do the mapping between CSound controls and DSP fields */
    AUXCH     dspmem;                     /* aux memory allocated once to store the DSP object */
    AUXCH     intmem;                     /* aux memory allocated once to store the interface object */
};

/**
 * Creates a "aaakkkk" CSound description string. Note that
 * these string will never be released. Potential memory leak
 */
static char* makeDescription(int numa, int numk=0)
{
    char* str = (char*)malloc(numa+numk+1); // NEED TO BE CHANGED ?
    if (str) {
        for (int i=0; i<numa; i++) str[i] = 'a';
        for (int i=0; i<numk; i++) str[numa+i] = 'k';
        str[numa+numk] = 0;
    }
    return str;
}

/**
 * CSOUND callback that allocates and initializes
 * the FAUST generated DSP object and it's CSound interface
 */
static int init(CSOUND *csound, dataspace *p)
{
    if (p->dspmem.auxp == NULL)
        csound->AuxAlloc(csound, sizeof(mydsp), &p->dspmem);
    
    if(p->intmem.auxp == NULL)
        csound->AuxAlloc(csound, sizeof(CSUI), &p->intmem);
    
    p->DSP = new (p->dspmem.auxp) mydsp;
    p->interface = new (p->intmem.auxp) CSUI;
    
    if ((p->DSP == 0) | (p->interface == 0)) return NOTOK;
    
    p->DSP->init((int)csound->GetSr(csound));
    p->DSP->buildUserInterface(p->interface);
    
    return OK;
}

/**
 * CSound callback that process the samples by updating
 * the controls values and calling the compute() method
 * of the DSP object. (Assume MYFLT = FAUSTFLOAT)
 */
static int process32bits(CSOUND *csound, dataspace *p)
{
    AVOIDDENORMALS;
    
    // update all the control values
    p->interface->copyfrom(p->ktl);
    
    p->DSP->compute(csound->GetKsmps(csound), p->ain, p->aout);
    return OK;
}

extern "C" {
    static OENTRY localops[] = {
        {(char*)sym(OPCODE_NAME), sizeof(dataspace),5,makeDescription(FAUST_OUTPUTS), makeDescription(FAUST_INPUTS,FAUST_ACTIVES),
            (SUBR)init, NULL,(SUBR)process32bits }
    };
    LINKAGE
}


/********************END ARCHITECTURE SECTION (part 2/2)****************/




#endif