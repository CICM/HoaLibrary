//-----------------------------------------------------
// name: "OneSourceToStereo"
// version: "1.0"
// author: "CICM"
// license: "BSD"
// copyright: "(c)CICM 2013"
//
// Code generated with Faust 0.9.59 (http://faust.grame.fr)
//-----------------------------------------------------
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  

typedef long double quad;
/* link with  */
#include <math.h>
#include <cmath>
template <int N> inline float faustpower(float x) 		{ return powf(x,N); } 
template <int N> inline double faustpower(double x) 	{ return pow(x,N); }
template <int N> inline int faustpower(int x) 			{ return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x) 		{ return 1; }
template <> 	 inline int faustpower<1>(int x) 		{ return x; }

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
  private:
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider0;
	float 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	float 	fRec1[2];
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
		fConst0 = expf((0 - (5e+01f / float(min(192000, max(1, fSamplingFreq))))));
		fConst1 = (1.0f - fConst0);
		fslider0 = 1.0f;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		fslider1 = 62831.0f;
		for (int i=0; i<2; i++) fRec1[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openVerticalBox("OneSourceToStereo.0.tmp");
		interface->addHorizontalSlider("Angle", &fslider1, 62831.0f, -6.28318530717959f, 6.28318530717959f, 0.001f);
		interface->addHorizontalSlider("Radius", &fslider0, 1.0f, 0.0f, 5.0f, 0.001f);
		interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = (fConst1 * fslider0);
		float 	fSlow1 = (fConst1 * fslider1);
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		for (int i=0; i<count; i++) {
			fRec0[0] = (fSlow0 + (fConst0 * fRec0[1]));
			int iTemp0 = (fRec0[0] > 1);
			int iTemp1 = (fRec0[0] < 1);
			float fTemp2 = (iTemp0 + (fRec0[0] * iTemp1));
			float fTemp3 = ((float)input0[i] * (1 + (2.0794415416798357f * (0 - (fTemp2 - 1)))));
			float fTemp4 = (3.0f * fTemp2);
			float fTemp5 = ((3.0f * ((fTemp2 * (fTemp4 > 0)) * (fTemp4 <= 1))) + (fTemp4 > 1));
			fRec1[0] = (fSlow1 + (fConst0 * fRec1[1]));
			float fTemp6 = (fTemp5 * cosf(fRec1[0]));
			float fTemp7 = (0.11666666666666667f * fTemp6);
			float fTemp8 = (2.0794415416798357f * fTemp2);
			float fTemp9 = (fTemp8 - 0.6931471805599453f);
			float fTemp10 = (2.466303462376431f * fTemp9);
			float fTemp11 = ((2.466303462376431f * ((fTemp9 * (fTemp10 > 0)) * (fTemp10 <= 1))) + (fTemp10 > 1));
			float fTemp12 = (2 * fRec1[0]);
			float fTemp13 = (fTemp11 * cosf(fTemp12));
			float fTemp14 = (0.07777777777777778f * fTemp13);
			float fTemp15 = (fTemp8 - 1.0986122886681098f);
			float fTemp16 = (3.4760594967822085f * fTemp15);
			float fTemp17 = ((3.4760594967822085f * ((fTemp15 * (fTemp16 > 0)) * (fTemp16 <= 1))) + (fTemp16 > 1));
			float fTemp18 = (3 * fRec1[0]);
			float fTemp19 = (fTemp17 * cosf(fTemp18));
			float fTemp20 = (0.03888888888888889f * fTemp19);
			float fTemp21 = (fTemp8 - 1.3862943611198906f);
			float fTemp22 = (4.481420117724551f * fTemp21);
			float fTemp23 = ((4.481420117724551f * ((fTemp21 * (fTemp22 > 0)) * (fTemp22 <= 1))) + (fTemp22 > 1));
			float fTemp24 = (4 * fRec1[0]);
			float fTemp25 = (fTemp23 * cosf(fTemp24));
			float fTemp26 = (0.014141414141414142f * fTemp25);
			float fTemp27 = (fTemp8 - 1.6094379124341003f);
			float fTemp28 = (5.484814947747076f * fTemp27);
			float fTemp29 = ((5.484814947747076f * ((fTemp27 * (fTemp28 > 0)) * (fTemp28 <= 1))) + (fTemp28 > 1));
			float fTemp30 = (5 * fRec1[0]);
			float fTemp31 = (fTemp29 * cosf(fTemp30));
			float fTemp32 = (0.0035353535353535356f * fTemp31);
			float fTemp33 = (fTemp8 - 1.791759469228055f);
			float fTemp34 = (6.487159194630884f * fTemp33);
			float fTemp35 = ((6.487159194630884f * ((fTemp33 * (fTemp34 > 0)) * (fTemp34 <= 1))) + (fTemp34 > 1));
			float fTemp36 = (6 * fRec1[0]);
			float fTemp37 = (fTemp35 * cosf(fTemp36));
			float fTemp38 = (0.0017529949315523716f * fTemp37);
			float fTemp39 = (7 * fRec1[0]);
			float fTemp40 = (fTemp8 - 1.9459101490553132f);
			float fTemp41 = (7.488875689418624f * fTemp40);
			float fTemp42 = ((7.488875689418624f * ((fTemp40 * (fTemp41 > 0)) * (fTemp41 <= 1))) + (fTemp41 > 1));
			float fTemp43 = (cosf(fTemp39) * fTemp42);
			float fTemp44 = (0.0026481821020520905f * fTemp43);
			float fTemp45 = (0.7071067811865475f * (((((((0.06666666666666667f + fTemp7) + fTemp14) + fTemp20) + fTemp26) + fTemp32) + fTemp38) + fTemp44));
			float fTemp46 = (sinf(fRec1[0]) * fTemp5);
			float fTemp47 = (0.10778594545965012f * fTemp6);
			float fTemp48 = (sinf(fTemp12) * fTemp11);
			float fTemp49 = (0.054997194092287024f * fTemp48);
			float fTemp50 = (sinf(fTemp18) * fTemp17);
			float fTemp51 = (0.035928648486550044f * fTemp50);
			float fTemp52 = (0.014882133480864604f * fTemp19);
			float fTemp53 = (sinf(fTemp24) * fTemp23);
			float fTemp54 = (0.014141414141414142f * fTemp53);
			float fTemp55 = (sinf(fTemp30) * fTemp29);
			float fTemp56 = (sinf(fTemp36) * fTemp35);
			float fTemp57 = (0.0012395546034863296f * fTemp37);
			float fTemp58 = (sinf(fTemp39) * fTemp42);
			float fTemp59 = (0.0024466012424486424f * fTemp43);
			float fTemp60 = ((((((((((((((0.06666666666666667f + (0.044646400442593805f * fTemp46)) + fTemp47) + fTemp49) + (0.05499719409228703f * fTemp13)) + fTemp51) + fTemp52) + fTemp54) + (8.659118781849972e-19f * fTemp25)) + (0.003266240771504549f * fTemp55)) - (0.0013529212255331455f * fTemp31)) + (0.0012395546034863296f * fTemp56)) - fTemp57) + (0.0010134154163410926f * fTemp58)) - fTemp59);
			float fTemp61 = (0.08249579113843053f * fTemp46);
			float fTemp62 = (0.07777777777777778f * fTemp48);
			float fTemp63 = (0.027498597046143512f * fTemp19);
			float fTemp64 = (0.0024998724587403194f * fTemp55);
			float fTemp65 = (0.0017529949315523716f * fTemp56);
			float fTemp66 = (0.0018725475221778797f * fTemp58);
			float fTemp67 = (0.0018725475221778789f * fTemp43);
			float fTemp68 = (0.06666666666666667f + (0.10778594545965012f * fTemp46));
			float fTemp69 = (0.054997194092287024f * fTemp13);
			float fTemp70 = (0.11666666666666667f * fTemp46);
			float fTemp71 = (0.03888888888888889f * fTemp50);
			float fTemp72 = (0.0035353535353535356f * fTemp55);
			float fTemp73 = (0.0026481821020520905f * fTemp58);
			float fTemp74 = (0.05499719409228705f * fTemp13);
			float fTemp75 = (0.08249579113843053f * fTemp6);
			float fTemp76 = ((((((((((((0.05499719409228696f * fTemp13) + (((0.06666666666666667f - (0.04464640044259388f * fTemp46)) + (0.10778594545965009f * fTemp6)) - (0.05499719409228711f * fTemp48))) - (0.0359286484865501f * fTemp50)) + (0.014882133480864467f * fTemp19)) - fTemp54) - (3.810887590166739e-17f * fTemp25)) - (0.003266240771504547f * fTemp55)) - (0.0013529212255331507f * fTemp31)) - (0.0012395546034863203f * fTemp56)) - (0.0012395546034863392f * fTemp37)) - (0.0010134154163410766f * fTemp58)) - (0.002446601242448649f * fTemp43));
			float fTemp77 = (iTemp1 + (faustpower<2>(fRec0[0]) * iTemp0));
			output0[i] = (FAUSTFLOAT)((fTemp3 * (((((((((fTemp45 + (0.9807852804032304f * fTemp60)) + (0.9876883405951377f * ((((((((((((((0.06666666666666667f + fTemp61) + (0.08249579113843054f * fTemp6)) + fTemp62) + (4.762515330017485e-18f * fTemp13)) + (0.027498597046143516f * fTemp50)) - fTemp63) + (1.7318237563699945e-18f * fTemp53)) - fTemp26) - fTemp64) - (0.0024998724587403202f * fTemp31)) - fTemp65) - (3.220199447770718e-19f * fTemp37)) - fTemp66) + fTemp67))) + (0.9238795325112867f * (((((((((((((fTemp68 + (0.04464640044259381f * fTemp6)) + (0.05499719409228703f * fTemp48)) - fTemp69) - (0.014882133480864599f * fTemp50)) - (0.035928648486550044f * fTemp19)) - fTemp54) - (2.5977356345549916e-18f * fTemp25)) - (0.001352921225533148f * fTemp55)) + (0.0032662407715045483f * fTemp31)) + (0.0012395546034863294f * fTemp56)) + (0.00123955460348633f * fTemp37)) + (0.0024466012424486424f * fTemp58)) - (0.0010134154163410926f * fTemp43)))) + (0.8090169943749475f * (((((((fTemp26 + (((((((0.06666666666666667f + fTemp70) + (7.143772995026227e-18f * fTemp6)) + (9.52503066003497e-18f * fTemp48)) - fTemp14) - fTemp71) - (7.143772995026227e-18f * fTemp19)) - (3.463647512739989e-18f * fTemp53))) + fTemp72) + (1.0823898477312466e-18f * fTemp31)) + (6.440398895541436e-19f * fTemp56)) - fTemp38) - fTemp73) - (1.1350807071930908e-18f * fTemp43)))) + (0.6494480483301838f * ((((((((fTemp54 + ((0.03592864848655004f * fTemp19) + ((((fTemp68 - (0.0446464004425938f * fTemp6)) - fTemp49) - fTemp74) - (0.014882133480864626f * fTemp50)))) + (4.329559390924986e-18f * fTemp25)) - (0.0013529212255331457f * fTemp55)) - (0.003266240771504549f * fTemp31)) - (0.0012395546034863314f * fTemp56)) + (0.001239554603486328f * fTemp37)) + (0.0024466012424486415f * fTemp58)) + (0.0010134154163410948f * fTemp43)))) + (0.45399049973954686f * ((((fTemp65 + ((0.0024998724587403163f * fTemp31) + ((((5.195471269109983e-18f * fTemp53) + (((0.02749859704614351f * fTemp50) + ((((0.06666666666666667f + (0.08249579113843054f * fTemp46)) - fTemp75) - fTemp62) - (1.4287545990052454e-17f * fTemp13))) + (0.027498597046143526f * fTemp19))) - fTemp26) - (0.002499872458740323f * fTemp55)))) + (9.660598343312154e-19f * fTemp37)) - fTemp66) - fTemp67))) + (0.2334453638559055f * (((((((0.0032662407715045483f * fTemp55) + ((((fTemp51 + (fTemp69 + (((0.06666666666666667f + (0.04464640044259381f * fTemp46)) - fTemp47) - (0.05499719409228705f * fTemp48)))) - fTemp52) - fTemp54) - (6.061383147294981e-18f * fTemp25))) + (0.0013529212255331488f * fTemp31)) - (0.00123955460348633f * fTemp56)) - fTemp57) + (0.0010134154163410874f * fTemp58)) + (0.002446601242448644f * fTemp43)))) + (1.2246467991473532e-16f * (((fTemp38 + ((((fTemp26 + ((((1.4287545990052454e-17f * fTemp50) + (fTemp14 + (((0.06666666666666667f + (1.4287545990052454e-17f * fTemp46)) - fTemp7) - (1.905006132006994e-17f * fTemp48)))) - fTemp20) - (6.927295025479978e-18f * fTemp53))) + (2.164779695462493e-18f * fTemp55)) - fTemp32) - (1.2880797791082871e-18f * fTemp56))) + (2.2701614143861816e-18f * fTemp58)) - fTemp44))) + (0.19509032201612825f * fTemp76))) / fTemp77);
			output1[i] = (FAUSTFLOAT)((fTemp3 * ((((((((fTemp45 + (0.19509032201612825f * fTemp60)) + (0.2334453638559054f * (fTemp59 + (((((((fTemp54 + (((fTemp74 + (((0.06666666666666667f - (0.04464640044259379f * fTemp46)) - fTemp47) + (0.05499719409228702f * fTemp48))) - (0.03592864848655003f * fTemp50)) - (0.014882133480864633f * fTemp19))) + (7.793206903664976e-18f * fTemp25)) - (0.0032662407715045496f * fTemp55)) + (0.0013529212255331449f * fTemp31)) + (0.001239554603486332f * fTemp56)) - (0.0012395546034863277f * fTemp37)) - (0.0010134154163410917f * fTemp58))))) + (0.45399049973954675f * ((((((fTemp64 + (((8.659118781849973e-18f * fTemp53) + ((((fTemp62 + ((0.06666666666666667f - fTemp61) - (0.08249579113843057f * fTemp6))) + (2.3812576650087427e-17f * fTemp13)) - (0.027498597046143554f * fTemp50)) + (0.02749859704614348f * fTemp19))) - fTemp26)) + (0.0024998724587403194f * fTemp31)) - fTemp65) - (4.7240442599823884e-18f * fTemp37)) + (0.0018725475221778828f * fTemp58)) - (0.0018725475221778756f * fTemp43)))) + (0.6494480483301837f * ((((((((((((((0.06666666666666667f - (0.10778594545965009f * fTemp46)) - (0.044646400442593874f * fTemp6)) + (0.0549971940922871f * fTemp48)) - (0.05499719409228697f * fTemp13)) + (0.014882133480864536f * fTemp50)) + (0.035928648486550065f * fTemp19)) - fTemp54) - (3.46452283889274e-17f * fTemp25)) + (0.0013529212255331555f * fTemp55)) - (0.0032662407715045453f * fTemp31)) + (0.001239554603486325f * fTemp56)) + (0.0012395546034863342f * fTemp37)) - (0.0024466012424486467f * fTemp58)) + (0.001013415416341082f * fTemp43)))) + (0.8090169943749473f * ((fTemp73 + (((((fTemp26 + (((fTemp71 + ((((0.06666666666666667f - fTemp70) - (2.143131898507868e-17f * fTemp6)) + (2.857509198010491e-17f * fTemp48)) - fTemp14)) + (2.1431318985078683e-17f * fTemp19)) - (1.0390942538219966e-17f * fTemp53))) - fTemp72) - (9.527218975416847e-18f * fTemp31)) + (1.932119668662431e-18f * fTemp56)) - fTemp38)) - (1.298874267378291e-18f * fTemp43)))) + (0.9238795325112867f * ((((((((fTemp54 + ((((((0.06666666666666667f - (0.1077859454596501f * fTemp46)) + (0.04464640044259383f * fTemp6)) - (0.054997194092287066f * fTemp48)) - (0.05499719409228701f * fTemp13)) + (0.014882133480864578f * fTemp50)) - (0.03592864848655006f * fTemp19))) - (1.3863343312487467e-17f * fTemp25)) + (0.0013529212255331496f * fTemp55)) + (0.0032662407715045474f * fTemp31)) - (0.0012395546034863279f * fTemp56)) + (0.0012395546034863316f * fTemp37)) - (0.0024466012424486476f * fTemp58)) - (0.0010134154163410796f * fTemp43)))) + (0.9876883405951378f * ((((fTemp65 + (((((1.2122766294589962e-17f * fTemp53) + (((((fTemp75 + (0.06666666666666667f - (0.08249579113843057f * fTemp46))) - fTemp62) - (3.3337607310122396e-17f * fTemp13)) - (0.027498597046143526f * fTemp50)) - fTemp63)) - fTemp26) + (0.002499872458740324f * fTemp55)) - (0.0024998724587403146f * fTemp31))) - (8.598049226575266e-19f * fTemp37)) + (0.0018725475221778715f * fTemp58)) + (0.0018725475221778869f * fTemp43)))) + (0.9807852804032304f * fTemp76))) / fTemp77);
			// post processing
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
		}
	}
};


