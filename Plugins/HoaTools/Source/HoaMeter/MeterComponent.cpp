/**
 * HoaLibrary : A High Order Ambisonics Library
 * Copyright (c) 2012-2013 Julien Colafrancesco, Pierre Guillot, Eliott Paris, CICM, Universite Paris-8.
 * All rights reserved.
 *
 * Website  : http://www.mshparisnord.fr/hoalibrary/
 * Contacts : cicm.mshparisnord@gmail.com
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *	- Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice,
 *		this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,Z
 *		this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MeterComponent.h"

/************************************************************************************/
/***************************** EDITOR ***********************************************/
/************************************************************************************/

MeterEditor::MeterEditor(AmbisonicsMeter * aMeter)
{
    m_meter = aMeter;
    startTimer(20);
}

MeterEditor::~MeterEditor()
{
    ;
}

void MeterEditor::timerCallback()
{
    repaint();
}

void MeterEditor::paint(Graphics& g)
{
    Path P;
    float center  = getWidth() * 0.5;
    float led_width = 0.5 / 16. * getWidth();
    
    m_meter->processEnergy();
    
    g.setColour(Colours::grey);
    g.drawEllipse(0.2 * getWidth(), 0.2 * getWidth(), 0.6 * getWidth(), 0.6 * getWidth(), getWidth() * 0.4);
    g.addTransform(AffineTransform::fromTargetPoints(-center, center, 0, 0, center, center, getWidth(), 0,  center, -center, getWidth(), getWidth()));
    
    for(int i = 0; i < m_meter->getNumberOfLoudspeakers(); i++)
    {
        float angle_start = m_meter->getLoudspeakerAngleMappedRadian(i) - m_meter->getLoudspeakerWidthRadian(i) / 2. + 0.025 * getWidth() / 498.;
        float angle_end   = m_meter->getLoudspeakerAngleMappedRadian(i) + m_meter->getLoudspeakerWidthRadian(i) / 2. - 0.025 * getWidth() / 498.;
        
        for(float j = 11, dB = -34.5; j > -2; j--, dB += 3.)
        {
            float center_x  = led_width * (2 - (j / 11.)) * cos(m_meter->getLoudspeakerAngleMappedRadian(i));
            float center_y  = led_width * (2 - (j / 11.)) * sin(m_meter->getLoudspeakerAngleMappedRadian(i));
            
            float radius    = (j + 3.33) * led_width;
            if(m_meter->getLoudspeakerEnergy(i) > dB)
            {
                if(j > 8)
                    g.setColour(Colours::green);
                else if(j > 5)
                    g.setColour(Colours::yellowgreen);
                else if(j > 2)
                    g.setColour(Colours::yellow);
                else if(j > -1)
                    g.setColour(Colours::orange);
                else
                    g.setColour(Colours::red);
                 P.addCentredArc(center_x, center_y, radius, radius, CICM_PI2, angle_start, angle_end, 1);
                
                g.strokePath(P, PathStrokeType(led_width - getWidth() / 166., PathStrokeType::mitered, PathStrokeType::rounded));
                P.clear();
            }
            else if(j != -1)
            {
                g.setColour(Colours::darkgrey);
                P.addCentredArc(center_x, center_y, radius, radius, CICM_PI2, angle_start, angle_end, 1);
                g.strokePath(P, PathStrokeType(led_width  - getWidth() / 166., PathStrokeType::mitered, PathStrokeType::rounded));
                P.clear();
            }
        }
    }
}



