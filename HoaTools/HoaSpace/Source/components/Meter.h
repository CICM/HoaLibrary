/*
  ==============================================================================

    Meter.h
    Created: 10 Apr 2013 7:46:03pm
    Author:  eliott PARIS

  ==============================================================================
*/

#ifndef __METER_H_315EBA1F__
#define __METER_H_315EBA1F__

#include "cicmTools.h"
#include "../JuceLibraryCode/JuceHeader.h"

#define MAX_SPEAKER 32
#define MIN_SPEAKER 1
#define DEF_SPEAKER 8

//==============================================================================
/*
*/
class Meter    : public Component
{
public:
    Meter();
    ~Meter();
    
    void setAmplitudeOfLoudspeakers(const double* _AmplitudeOfLoudspeakers, const int _numberOfLoudspeakers);
    int  setSpeakerOffset(const float _speakerOffset);
    void paint (Graphics&);
    void resized();
    
    enum  ColourIds {
        backgroundColourId = 0x18C8C8C,
        meterBgColourId = 0x1666666,
        borderColourId = 0x1404040,
        meterBorderColourId = 0x1404040,
        coldSignalColourId = 0x1009900,
        tepidSignalColourId = 0x199BA00,
        warmSignalColourId = 0x1D9D900,
        hotSignalColourId = 0x1FF9900,
        overSignalColourId = 0x1FF0000,
        energyColourId = 0x10000FF,
        ledBgColourId = 0x1111111
    };
    
private:
    
    void setNumberOfLoudspeakers(const int _nbLoudspeakers);
    void setLoudspeakersAngles();
    
    void draw_background(Graphics&);
    void draw_skelton(Graphics&);
    void draw_meter(Graphics&);
    void draw_OverMeter(Graphics&);
    void draw_vector(Graphics&);
    
    // graphic vars :
	int         f_numberOfLoudspeakers;
	float		f_offsetOfLoudspeakers;
	
	int			f_dbperled;
	int			f_nhotleds;
	int			f_ntepidleds;
	int			f_nwarmleds;
	int			f_numleds;
    
    double      f_widthOver2;
	double		f_rayonMax;
	double		f_rayonCircle;
	
	double		f_strokeWidth;
	double		f_rayonExt;
	double		f_rayonInt;
	int			f_drawmeter;
	long		f_leds_bg;
	long		f_energy;
	double		f_metersize;
    int         f_speakers_dir_of_rotation;
    int         f_fill_direction;

	double*		f_speakerAngles;
	double*		f_speakerRealAngle;
	double*		f_speakerWidth;
	double*		f_amplitudeOfLoudspeakers;
	double*		f_energyOfLoudspeakers;
	double*		f_abscisseOfLoudspeakers;
	double*		f_ordonneOfLoudspeakers;
	double		f_energyVectorX;
	double		f_energyVectorY;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Meter)
};


#endif  // __METER_H_315EBA1F__
