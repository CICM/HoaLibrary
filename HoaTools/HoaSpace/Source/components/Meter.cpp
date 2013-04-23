/*
  ==============================================================================

    Meter.cpp
    Created: 10 Apr 2013 7:46:03pm
    Author:  eliott PARIS

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Meter.h"

//==============================================================================
Meter::Meter()
{
    f_numberOfLoudspeakers = 8;
    f_energyOfLoudspeakers = new double[f_numberOfLoudspeakers];
    f_amplitudeOfLoudspeakers = new double[f_numberOfLoudspeakers];
    f_abscisseOfLoudspeakers = new double[f_numberOfLoudspeakers];
    f_ordonneOfLoudspeakers = new double[f_numberOfLoudspeakers];
    f_speakerAngles = new double[f_numberOfLoudspeakers];
    f_speakerRealAngle = new double[f_numberOfLoudspeakers];
    f_speakerWidth = new double[f_numberOfLoudspeakers];
    for(int i = 0; i < f_numberOfLoudspeakers; i++)
    {
        f_speakerAngles[i] = 360. / f_numberOfLoudspeakers * i;
        f_energyOfLoudspeakers[i] = 0.00001;
        f_amplitudeOfLoudspeakers[i] = 0.000001;
    }
    setLoudspeakersAngles();
    
	f_offsetOfLoudspeakers = 0.0f;

	f_dbperled = 3;
	f_nhotleds = 3;
	f_ntepidleds = 3;
	f_nwarmleds = 3;
	f_numleds = 12;
	f_strokeWidth = 2;
	f_leds_bg = 1;
	f_energy = 1;
	f_metersize = 0.8;
    f_speakers_dir_of_rotation = 1;
    f_fill_direction = 0;
    
    setColour (Meter::backgroundColourId, Colour ((uint8)(0.55*255), (uint8)(0.55*255), (uint8)(0.55*255), 1.0f));
    setColour (Meter::meterBgColourId, Colour ((uint8)(0.4*255), (uint8)(0.4*255), (uint8)(0.4*255), 1.0f));
    setColour (Meter::borderColourId, Colour ((uint8)(0.25*255), (uint8)(0.25*255), (uint8)(0.25*255), 1.0f));
    setColour (Meter::meterBorderColourId, Colour ((uint8)(0.25*255), (uint8)(0.25*255), (uint8)(0.25*255), 1.0f));
    setColour (Meter::coldSignalColourId, Colour ((uint8)(0.*255), (uint8)(0.6*255), (uint8)(0.*255), 0.8f));
    setColour (Meter::tepidSignalColourId, Colour ((uint8)(0.6*255), (uint8)(0.73*255), (uint8)(0.*255), 0.8f));
    setColour (Meter::warmSignalColourId, Colour ((uint8)(0.85*255), (uint8)(0.85*255), (uint8)(0.*255), 0.8f));
    setColour (Meter::hotSignalColourId, Colour ((uint8)(1.*255), (uint8)(0.6*255), (uint8)(0.*255), 0.8f));
    setColour (Meter::overSignalColourId, Colour ((uint8)(1.*255), (uint8)(0.*255), (uint8)(0.*255), 0.8f));
    setColour (Meter::energyColourId, Colour ((uint8)(0.*255), (uint8)(0.*255), (uint8)(1.*255), 0.8f));
    setColour (Meter::ledBgColourId, Colour ((uint8)(0.*255), (uint8)(0.*255), (uint8)(0.*255), 0.05f));
}

Meter::~Meter()
{
    delete [] f_energyOfLoudspeakers;
    delete [] f_amplitudeOfLoudspeakers;
    delete [] f_abscisseOfLoudspeakers;
    delete [] f_ordonneOfLoudspeakers;
    delete [] f_speakerAngles;
    delete [] f_speakerRealAngle;
    delete [] f_speakerWidth;
}

void Meter::paint (Graphics& g)
{
    f_widthOver2 = getWidth() * .5;
	f_rayonMax = f_widthOver2;
	f_rayonCircle = f_rayonMax / 32;
	f_rayonExt = f_rayonMax - (f_strokeWidth*0.5) - 2;
	f_rayonInt = f_rayonExt*(1 - f_metersize);
	
	//draw_background(g);
	draw_skelton(g);
    draw_meter(g);
    draw_OverMeter(g);
    //draw_vector(g);
}

void Meter::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void Meter::draw_background(Graphics& g)
{
    /* Background */
    g.setColour (findColour (Meter::backgroundColourId));
    g.fillRoundedRectangle(0, 0, getWidth(), getWidth(), 8);
    //g.setColour (findColour (Meter::borderColourId));
    //g.drawRoundedRectangle(0, 0, getWidth(), getWidth(), 8, 2);
}
void Meter::draw_skelton(Graphics& g)
{
    Path bg;
    int i,j;
	long nLoudSpeak = f_numberOfLoudspeakers;
	double deg1, deg2, rotateAngle, ledContainerSize, ledStroke, ledMargin, ledOffset, radius;
	
	//deg1 = Tools::degtorad((double)90);
    deg1 = Tools::degtorad((double)0);
	ledContainerSize = f_rayonExt - f_rayonInt - (f_strokeWidth*4);
	ledOffset = ledContainerSize / (f_numleds+1);
	ledStroke = ledOffset * 0.75;
	ledMargin = ledOffset * 0.25;
    
    // Background :
    g.setColour (findColour (Meter::meterBgColourId));
    radius = f_rayonExt*0.5+(f_rayonInt*0.5);
    bg.startNewSubPath(f_widthOver2, f_widthOver2-radius);
    bg.addCentredArc(f_widthOver2, f_widthOver2, radius, radius, 0, 0., CICM_2PI+1);
    g.strokePath(bg, PathStrokeType ((f_rayonExt - f_rayonInt) - f_strokeWidth*0.5));
    bg.clear();
     
    // skelton circles :
    g.setColour (findColour (Meter::meterBorderColourId));
    bg.startNewSubPath(f_widthOver2, f_widthOver2-f_rayonExt);
    bg.addCentredArc(f_widthOver2, f_widthOver2, f_rayonExt, f_rayonExt, 0, 0., CICM_2PI);
    bg.closeSubPath();
    g.strokePath(bg, PathStrokeType (f_strokeWidth));
    // int
    bg.startNewSubPath(f_widthOver2, f_widthOver2-f_rayonInt);
    bg.addCentredArc(f_widthOver2, f_widthOver2, f_rayonInt, f_rayonInt, 0, 0., CICM_2PI);
    bg.closeSubPath();
    g.strokePath(bg, PathStrokeType (f_strokeWidth));
    bg.clear();
    
    g.beginTransparencyLayer(1);
    g.addTransform(AffineTransform::fromTargetPoints(-f_widthOver2, f_widthOver2, 0, 0,
                                                     f_widthOver2, f_widthOver2, getWidth(), 0,
                                                     f_widthOver2, -f_widthOver2, getWidth(), getHeight()));
    for(i=0; i<nLoudSpeak; i++)
    {
        //deg2 = Tools::degtorad((double)90+(f_speakerWidth[i]));
        deg2 = Tools::degtorad((double)(f_speakerWidth[i])*4);
        rotateAngle = f_speakerRealAngle[i] - (f_speakerWidth[i]*0.5) + f_offsetOfLoudspeakers;
        if (!f_speakers_dir_of_rotation) {
            rotateAngle += f_speakerWidth[i];
            rotateAngle *= -1;
        }
        g.addTransform(AffineTransform::rotation( Tools::degtorad(rotateAngle*4))); // pourquoi * 4 ???
        
        // separator
        if (f_numberOfLoudspeakers > 1) {
            g.setColour (findColour (Meter::meterBorderColourId));
            bg.startNewSubPath(0, f_rayonInt);
            bg.lineTo(0, f_rayonExt);
            g.strokePath(bg, PathStrokeType (f_strokeWidth));
            bg.clear();
        }
        
        // leds Background :
        if (f_leds_bg) {
            g.setColour (findColour (Meter::ledBgColourId));
            for( j=0; j < f_numleds; j++ )
            {
                if (f_numberOfLoudspeakers > 1) {
                    if (f_fill_direction == 0) { // inside
                        radius = f_rayonExt-(j*ledOffset) - ledMargin*2 - f_strokeWidth*2;
                    } else { // outside
                        radius = f_rayonInt+(j*ledOffset) + ledMargin*2 + f_strokeWidth*2;
                    }
                    bg.startNewSubPath(0, radius);
                    bg.addCentredArc(0, 0, radius, radius, CICM_PI, deg1, deg2);
                }
                else { // mono
                    if (f_fill_direction == 0) { // inside
                        radius = f_rayonExt-(j*ledOffset)-ledMargin*2-f_strokeWidth*2;
                    } else { // outside
                        radius = f_rayonInt+(j*ledOffset)+ledMargin*2+f_strokeWidth*2;
                    }
                    bg.startNewSubPath(0, radius);
                    bg.addCentredArc(0, 0, radius, radius, CICM_PI, 0, CICM_2PI );
                }
                g.strokePath(bg, PathStrokeType (ledStroke));
                bg.clear();
            }
        }
        g.addTransform(AffineTransform::rotation( Tools::degtorad(-rotateAngle*4)));
    }
    g.endTransparencyLayer();
}
void Meter::draw_meter(Graphics& g)
{
    Path led, bg;
    int i, j, nbLed, tepidLimit, warmLimit, hotLimit, drawOverLed;
	long nLoudSpeak = f_numberOfLoudspeakers;
	double deg1, deg2, rotateAngle, ledContainerSize, ledStroke, ledMargin, ledOffset, meter_dB, min_dB_to_display, radius;
	Colour ledColor;
	
	deg1 = Tools::degtorad(90);
	nbLed = f_numleds+1;
	ledContainerSize = f_rayonExt - f_rayonInt - (f_strokeWidth*4);
	ledOffset = ledContainerSize / nbLed;
	ledStroke = ledOffset * 0.75;
	ledMargin = ledOffset * 0.25;
	hotLimit = f_numleds - f_nhotleds;
	warmLimit = hotLimit - f_nwarmleds;
	tepidLimit = warmLimit - f_ntepidleds;
	min_dB_to_display = -1 * ( (f_numleds * f_dbperled) - (f_dbperled * 0.5) );
    
    g.beginTransparencyLayer(1);
    
    g.addTransform(AffineTransform::fromTargetPoints(-f_widthOver2, f_widthOver2, 0, 0,
                                                     f_widthOver2, f_widthOver2, getWidth(), 0,
                                                     f_widthOver2, -f_widthOver2, getWidth(), getHeight()));
    
    for(i=0; i<nLoudSpeak; i++)
    {
        meter_dB = f_energyOfLoudspeakers[i]; // dB (negatif) de -240 à 0;
        if ( meter_dB >= 0. ) drawOverLed = 1;
        else drawOverLed = 0;
        
        if ( meter_dB > min_dB_to_display ) // si on est en dessous pas la peine de dessiner
        {
            deg2 = Tools::degtorad((double)(f_speakerWidth[i])*4);
            rotateAngle = f_speakerRealAngle[i] - (f_speakerWidth[i]*0.5) + f_offsetOfLoudspeakers;
            if (!f_speakers_dir_of_rotation) {
                rotateAngle += f_speakerWidth[i];
                rotateAngle *= -1;
            }
            g.addTransform(AffineTransform::rotation( Tools::degtorad(rotateAngle*4))); // pourquoi * 4 ???
            
            // leds :
            for(j=0; j<nbLed; j++)
            {
                if ( ( j < nbLed-1 ) && ( meter_dB > min_dB_to_display + (f_dbperled * j) ) )
                {
                    if ( j < tepidLimit ) ledColor = findColour (Meter::coldSignalColourId);
                    else if ( j < warmLimit ) ledColor = findColour (Meter::tepidSignalColourId);
                    else if ( j < hotLimit ) ledColor = findColour (Meter::warmSignalColourId);
                    else ledColor = findColour (Meter::hotSignalColourId);
                    g.setColour(ledColor);
                    
                    if (nLoudSpeak > 1) {
                        if (f_fill_direction == 0) { // inside
                            radius = f_rayonExt-(j*ledOffset) - ledMargin*2 - f_strokeWidth*2;
                        } else { // outside
                            radius = f_rayonInt+(j*ledOffset) + ledMargin*2 + f_strokeWidth*2;
                        }
                        led.startNewSubPath(0, radius);
                        led.addCentredArc(0, 0, radius, radius, CICM_PI, deg1, deg2);
                    }
                    else {
                        if (f_fill_direction == 0) { // inside
                            radius = f_rayonExt-(j*ledOffset)-ledMargin*2-f_strokeWidth*2;
                        } else { // outside
                            radius = f_rayonInt+(j*ledOffset)+ledMargin*2+f_strokeWidth*2;
                        }
                        led.startNewSubPath(0, radius);
                        led.addCentredArc(0, 0, radius, radius, CICM_PI, 0, CICM_2PI );
                    }
                    g.strokePath(led, PathStrokeType (ledStroke));
                    led.clear();
                }
                else if ( drawOverLed )
                {
                    g.setColour(findColour (Meter::overSignalColourId));
                    
                    if (nLoudSpeak > 1) {
                        if (f_fill_direction == 0) { // inside
                            radius = f_rayonInt + ledMargin*2 + f_strokeWidth;
                        } else { // outside
                            radius = f_rayonExt - ledMargin*2 - f_strokeWidth;
                        }
                        led.startNewSubPath(0, radius);
                        led.addCentredArc(0, 0, radius, radius, CICM_PI, deg1, deg2);
                    }
                    else {
                        if (f_fill_direction == 0) { // inside
                            radius = f_rayonInt + ledMargin*2;
                        } else { // outside
                            radius = f_rayonExt - ledMargin*2;
                        }
                        led.startNewSubPath(0, radius);
                        led.addCentredArc(0, 0, radius, radius, CICM_PI, 0, CICM_2PI );
                    }
                    g.strokePath(led, PathStrokeType (ledStroke));
                    led.clear();
                }
                else
                {
                    break;
                }
            }
            g.addTransform(AffineTransform::rotation( Tools::degtorad(-rotateAngle*4)));
        }
    }
    g.endTransparencyLayer();
}

void Meter::draw_OverMeter(Graphics& g)
{
    Path bg;
	double rotateAngle, ledStroke;
	ledStroke = ( (f_rayonExt - f_rayonInt - (f_strokeWidth*4)) / (f_numleds+1) ) * 0.75;

    g.beginTransparencyLayer(1);
    g.addTransform(AffineTransform::fromTargetPoints(-f_widthOver2, f_widthOver2, 0, 0,
                                                     f_widthOver2, f_widthOver2, getWidth(), 0,
                                                     f_widthOver2, -f_widthOver2, getWidth(), getHeight()));
    for(int i=0; i<f_numberOfLoudspeakers; i++)
    {
        rotateAngle = f_speakerRealAngle[i] - (f_speakerWidth[i]*0.5) + f_offsetOfLoudspeakers;
        if (!f_speakers_dir_of_rotation) {
            rotateAngle += f_speakerWidth[i];
            rotateAngle *= -1;
        }
        g.addTransform(AffineTransform::rotation( Tools::degtorad(rotateAngle*4))); // pourquoi * 4 ???
        // separator
        if (f_numberOfLoudspeakers > 1) {
            
            bg.startNewSubPath(0, f_rayonInt+f_strokeWidth);
            bg.lineTo(0, f_rayonExt-f_strokeWidth);
            g.setColour (findColour (Meter::meterBgColourId));
            g.strokePath(bg, PathStrokeType (f_strokeWidth*4));
            bg.clear();
            
            bg.startNewSubPath(0, f_rayonInt);
            bg.lineTo(0, f_rayonExt);
            g.setColour (findColour (Meter::meterBorderColourId));
            g.strokePath(bg, PathStrokeType (f_strokeWidth));
            bg.clear();
        }
        g.addTransform(AffineTransform::rotation( Tools::degtorad(-rotateAngle*4))); // pourquoi * 4 ???
    }
    g.endTransparencyLayer();
}

void Meter::draw_vector(Graphics& g)
{
    Path vec;
    double angle, rayon, value, arrow;
    
    if (f_energyVectorX == 0.)
        value = 0.;
    else
        value = Tools::angle(f_energyVectorX, f_energyVectorY);
    
    angle = value + Tools::degtorad(f_offsetOfLoudspeakers);
    if (!f_speakers_dir_of_rotation) angle *= -1;
    
    //g.drawText(String(angle), 0, 0, 20, 100, Justification::left, true);
    
    g.beginTransparencyLayer(1);
    g.addTransform(AffineTransform::fromTargetPoints(-f_widthOver2, f_widthOver2, 0, 0,
                                                     f_widthOver2, f_widthOver2, getWidth(), 0,
                                                     f_widthOver2, -f_widthOver2, getWidth(), getHeight()));
    
    /* Energy */
    g.setColour (findColour (Meter::energyColourId));
    rayon = f_rayonInt * 0.85;
    arrow = rayon * 0.15;
    g.addTransform(AffineTransform::rotation(angle));

    // arrow
    vec.addArrow(Line<float>(0., 0., 0., rayon), 1, f_strokeWidth*4, f_strokeWidth*2);
    g.fillPath(vec);
    vec.clear();
    
    /* Center */
    vec.addCentredArc(0, 0, 2, 2, CICM_PI, 0, CICM_2PI);
    g.fillPath(vec);
    g.endTransparencyLayer();
}

int Meter::setSpeakerOffset(const float _speakerOffset)
{
    if (_speakerOffset < -180 ) f_offsetOfLoudspeakers = -180;
    else if (_speakerOffset > 180 ) f_offsetOfLoudspeakers = 180;
    else f_offsetOfLoudspeakers = _speakerOffset;
    //f_offsetOfLoudspeakers *= -1; // tourne dans le mauvais sens sinon !
    repaint();
    return 1;
}

void Meter::setAmplitudeOfLoudspeakers(const double* _AmplitudeOfLoudspeakers, const int _numberOfLoudspeakers)
{
    setNumberOfLoudspeakers(_numberOfLoudspeakers);
	double sum = 0., square = 0.;
	
	f_energyVectorX = f_energyVectorY = 0.;
	for(int i = 0; i < f_numberOfLoudspeakers; i++)
	{
        f_amplitudeOfLoudspeakers[i] = _AmplitudeOfLoudspeakers[i];
		f_energyOfLoudspeakers[i] = 20. * log10(fabs(f_amplitudeOfLoudspeakers[i]));
		square = f_amplitudeOfLoudspeakers[i] * f_amplitudeOfLoudspeakers[i];
		
		f_energyVectorX += square * f_abscisseOfLoudspeakers[i];
		f_energyVectorY += square * f_ordonneOfLoudspeakers[i];
		sum += square;
		
		f_amplitudeOfLoudspeakers[i] = 0.000000000001;
	}
	if (sum == 0.)
		f_energyVectorX = f_energyVectorY = 0.;
	else
	{
		f_energyVectorX /= sum;
		f_energyVectorY /= sum;
	}
    repaint();
}

void Meter::setNumberOfLoudspeakers(const int _nbLoudspeakers)
{
    if (f_numberOfLoudspeakers != _nbLoudspeakers)
    {
        f_numberOfLoudspeakers = Tools::clip(_nbLoudspeakers, MIN_LOUDSPEAKERS, MAX_LOUDSPEAKERS);
        delete [] f_energyOfLoudspeakers;
        delete [] f_amplitudeOfLoudspeakers;
        delete [] f_abscisseOfLoudspeakers;
        delete [] f_ordonneOfLoudspeakers;
        delete [] f_speakerAngles;
        delete [] f_speakerRealAngle;
        delete [] f_speakerWidth;
        f_energyOfLoudspeakers = new double[f_numberOfLoudspeakers];
        f_amplitudeOfLoudspeakers = new double[f_numberOfLoudspeakers];
        f_abscisseOfLoudspeakers = new double[f_numberOfLoudspeakers];
        f_ordonneOfLoudspeakers = new double[f_numberOfLoudspeakers];
        f_speakerAngles = new double[f_numberOfLoudspeakers];
        f_speakerRealAngle = new double[f_numberOfLoudspeakers];
        f_speakerWidth = new double[f_numberOfLoudspeakers];
        for(int i = 0; i < f_numberOfLoudspeakers; i++)
        {
            f_speakerAngles[i] = 360. / f_numberOfLoudspeakers * i;
            f_energyOfLoudspeakers[i] = 0.00001;
            f_amplitudeOfLoudspeakers[i] = 0.000001;
        }
        setLoudspeakersAngles();
    }
}

void Meter::setLoudspeakersAngles()
{
	double curAngle, prevAngle, nextAngle, prevPortion, nextPortion;
	for(int i = 0; i < f_numberOfLoudspeakers; i++)
	{
		curAngle = f_speakerAngles[i];
		if (i != 0) prevAngle = f_speakerAngles[i-1];
		else prevAngle = f_speakerAngles[f_numberOfLoudspeakers-1];
		if (i != f_numberOfLoudspeakers-1) nextAngle = f_speakerAngles[i+1];
		else nextAngle = f_speakerAngles[0];
		
		prevPortion = (curAngle - prevAngle);
		nextPortion = (nextAngle - curAngle);
		
		if (nextPortion < 0.) nextPortion += 360.;
		if (prevPortion < 0.) prevPortion += 360.;
		
		f_speakerWidth[i] = (prevPortion + nextPortion)*0.5;
		f_speakerRealAngle[i] = (curAngle - prevPortion*0.5) + f_speakerWidth[i]*0.5;
		f_abscisseOfLoudspeakers[i] = cos(Tools::degtorad(f_speakerRealAngle[i]));
		f_ordonneOfLoudspeakers[i] = sin(Tools::degtorad(f_speakerRealAngle[i]));
	}
}