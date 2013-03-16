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
    
    head = ImageCache::getFromMemory (BinaryData::head_png, BinaryData::head_pngSize);
    m_nbSources = 1;
    m_nbSpeakers = 4;
    m_speakerOffset = 0;
    m_speakerDistance = 0.5;
}

HoaMap::~HoaMap()
{
}

void HoaMap::paint (Graphics& g)
{
    
    float headScale = 0.3;
    g.setColour (Colours::grey);
    g.drawEllipse(1, 1, getWidth()-2, getHeight()-2, 2);
    
    draw_speakers(g);
    draw_head(g);
    /*
    g.drawImage(head,
                getWidth()*0.5 - (head.getWidth()*headScale*0.5)+0.5,
                getHeight()*0.5 - (head.getHeight()*headScale*0.5)+0.5,
                head.getWidth()*headScale,
                head.getHeight()*headScale,
                0, 0, head.getWidth(), head.getHeight());
     */
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
    float headSize = 20;
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
