/*
  ==============================================================================

    HoaMap.cpp
    Created: 13 Mar 2013 11:15:41pm
    Author:  eliott PARIS

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "HoaMap.h"

//==============================================================================
HoaMap::HoaMap()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    m_nbSources = 1;
    m_nbSpeakers = 4;
    m_speakerOffset = 0;
    m_speakerDistance = 0.5;
}

HoaMap::~HoaMap()
{
}

void HoaMap::mouseMove (const MouseEvent &event)
{
    Point<int> mouse = event.getPosition();
}
void HoaMap::mouseDown (const MouseEvent &event)
{
    ;
}
void HoaMap::mouseDrag (const MouseEvent &event)
{
    ;
}
void HoaMap::mouseUp   (const MouseEvent &event)
{
    ;
}

void HoaMap::paint (Graphics& g)
{
    
    g.setColour (Colours::grey);
    g.drawEllipse(1, 1, getWidth()-2, getHeight()-2, 2);
    
    draw_speakers(g);
    draw_head(g);
    draw_sources(g);
}

void HoaMap::draw_sources(Graphics& g)
{
    float sourceSize = 15;
    float center = getWidth()*0.5;
    int i;
    for (i=0; i < m_nbSources; i++) {
        //g.setColour ( (Colours::tomato).withAlpha((float)0.9) );
        g.setColour ( Colour((float)1*i, (float)0.5, (float)0.5, (float)0.95) );
        g.fillEllipse(center-sourceSize*0.5, center-sourceSize*0.5-100, sourceSize, sourceSize);
        g.setColour ( Colour(0xff444444) );
        g.drawEllipse(center-sourceSize*0.5, center-sourceSize*0.5-100, sourceSize, sourceSize, .5);
        g.drawFittedText(String(i+1), center-sourceSize*0.5, center-sourceSize*0.5-100, sourceSize, sourceSize, Justification(4), true);
    }
}

void HoaMap::draw_speakers(Graphics& g)
{
    Path speakers;
    Path speaker;
    int i;
    float distSpeakerRayon = getWidth() * m_speakerDistance;
    float distSpeakerCenter = getWidth()*0.5 - distSpeakerRayon*0.5;
    float speakerSize = 10;
    float center = getWidth()*0.5;
    float stepAngle = HOA_2PI/(float)m_nbSpeakers;
    float speakerOffset = m_speakerOffset / (180 / HOA_PI);
    
    //draw a circle who represents distance of loudspeaker :
    g.setColour ( (Colours::black).withAlpha((float)0.1) );
    g.fillEllipse(distSpeakerCenter, distSpeakerCenter, distSpeakerRayon, distSpeakerRayon);
    
    //g.setColour (Colours::black);
    //g.setColour ( (Colours::black).withAlpha((float)0.6) );
    g.setColour ( Colour(0xff444444) );
    for (i=0; i < m_nbSpeakers; i++) {
        speaker.addRectangle(center-speakerSize*0.5,
                            center - getHeight()*0.5*m_speakerDistance - speakerSize*0.5,
                            speakerSize,
                            speakerSize);
        speaker.addTriangle(center,
                           center - getHeight()*0.5*m_speakerDistance - speakerSize*0.5,
                           center+speakerSize*0.9,
                           center - getHeight()*0.5*m_speakerDistance + speakerSize*0.5,
                           center-speakerSize*0.9,
                           center - getHeight()*0.5*m_speakerDistance + speakerSize*0.5);
        
        speakers.addPath(speaker,
                         AffineTransform::rotation( i*stepAngle + speakerOffset, center, center));
    }
    g.fillPath (speakers);
    g.setColour (Colour(0xffDDDDDD));
    g.setFont(11);
    g.beginTransparencyLayer(1);
    for (i=0; i < m_nbSpeakers; i++) {
        g.addTransform(AffineTransform::rotation( i*stepAngle + speakerOffset, center, center));
        g.drawFittedText(String(i+1),
                   center-speakerSize*0.5,
                   center - getHeight()*0.5*m_speakerDistance - speakerSize*0.5 -1,
                   speakerSize,
                   speakerSize, Justification(4), true);
        g.addTransform(AffineTransform::rotation( -( i*stepAngle + speakerOffset), center, center));
    }
    g.endTransparencyLayer();
}

void HoaMap::draw_head(Graphics& g){
    Path headPath;
    float headSize = 15;
    float center = getWidth()*0.5;
    g.setColour ( Colour(0xff444444) );
    
    // head :
    headPath.addCentredArc(center,
                           center,
                           headSize*0.5,
                           headSize*0.5,
                           0,
                           0, HOA_2PI);
    headPath.closeSubPath();
    
    // Left Ear :
    headPath.addCentredArc(center-headSize*0.4,
                           center,
                           headSize*0.2,
                           headSize*0.2,
                           0,
                           0, HOA_2PI);
    headPath.closeSubPath();
    
    // Right Ear :
    headPath.addCentredArc(center+headSize*0.4,
                           center,
                           headSize*0.2,
                           headSize*0.2,
                           0,
                           0, HOA_2PI);
    headPath.closeSubPath();
    
    // Nose :
    headPath.addCentredArc(center,
                           center-headSize*0.3,
                           headSize*0.15,
                           headSize*0.3,
                           0,
                           0, HOA_2PI);
    
    g.fillPath(headPath);
    
    g.setColour ( Colour(0xAADDDDDD) );
    g.drawEllipse(center-headSize*0.5, center-headSize*0.5, headSize, headSize, 0.3);
}

void HoaMap::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void HoaMap::setNbSources(int _nbSources)
{
    m_nbSources = _nbSources;
    repaint();
}
void HoaMap::setNbSpeakers(int _nbSpeakers)
{
    m_nbSpeakers = _nbSpeakers;
    repaint();
}
void HoaMap::setSpeakerDistance(float _speakerDistance)
{
    m_speakerDistance = _speakerDistance;
    repaint();
}
void HoaMap::setSpeakerOffset(float _speakerOffset)
{
    m_speakerOffset = _speakerOffset;
    repaint();
}
