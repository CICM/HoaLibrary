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
    float distSpeakerRayon = getWidth() * m_speakerDistance;
    float distSpeakerCenter = getWidth()*0.5 - distSpeakerRayon*0.5;
    float headScale = 0.3;
    //g.fillAll (Colours::white);   // clear the background

    //g.setColour (Colours::grey);
    //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    g.setColour (Colours::grey);
    g.drawEllipse(1, 1, getWidth()-2, getHeight()-2, 2);
    
    g.setColour (Colours::grey);
    g.fillEllipse(distSpeakerCenter, distSpeakerCenter, distSpeakerRayon, distSpeakerRayon);
    
    //draw_head(g);
    
    draw_speakers(g);
    
    g.drawImage(head,
                getWidth()*0.5 - (head.getWidth()*headScale*0.5)+0.5,
                getHeight()*0.5 - (head.getHeight()*headScale*0.5)+0.5,
                head.getWidth()*headScale,
                head.getHeight()*headScale,
                0, 0, head.getWidth(), head.getHeight());
    
    
}

void HoaMap::draw_speakers(Graphics& g)
{
    Path speakers;
    Path speaker;
    int i;
    float speakerSize = 10;
    float center = getWidth()*0.5;
    g.setColour (Colours::black);
    float stepAngle = 360.0f/(double)m_nbSpeakers;
    float speakerOffset = m_speakerOffset / (180 / HOA_PI);
    
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
                         AffineTransform::rotation( (i*stepAngle) * HOA_PI * (1./180.)+ speakerOffset, center, center));
        //g.setColour (Colours::white);
//        g.drawTextAsPath(String(i),
//                         AffineTransform::rotation( (i*stepAngle) * HOA_PI * (1./180.)+ speakerOffset, center, center));
        //myPath.applyTransform (AffineTransform::rotation( i*stepAngle + speakerOffset, center, center));
    }
    g.fillPath (speakers);
    g.setColour (Colours::white);
    for (i=0; i < m_nbSpeakers; i++) {
        g.drawText(String(i),
                   center-speakerSize*0.5,
                   center - getHeight()*0.5*m_speakerDistance - speakerSize*0.5,
                   speakerSize,
                   speakerSize, Justification(0), true);
        g.addTransform(AffineTransform::rotation( (i*stepAngle)+ speakerOffset, center, center));
    }
}

void HoaMap::draw_head(Graphics& g){
	//t_jrgba ombrecolor = {0,0,0,0.3};
	//double ombre;
    float headSize = 30;
    float center = getWidth()*0.5;
	float size = getWidth()*0.5;
    
   // ombre = floor(size * 0.01) + 0.5;
    
    //tête
    g.setColour (Colours::black);
    //jgraphics_set_source_jrgba(g, &ombrecolor);
    g.fillEllipse(center - headSize*0.5,
                  center - headSize*0.5,
                  headSize, headSize);
    
    // Ear Left
    g.fillEllipse(center - headSize*0.5,
                  center,
                  headSize*0.2,
                  headSize*0.3);
    /*
    jgraphics_arc(g, rect->width * .5 + ombre, rect->height * .5 + ombre, size*0.1,  0., JGRAPHICS_2PI);
    jgraphics_fill(g);
    //oreille G ombre
    jgraphics_set_line_width(g, size*(0.015));
    jgraphics_set_line_cap(g, JGRAPHICS_LINE_CAP_ROUND);
    jgraphics_arc(g, rect->width * .5 + ombre, rect->height * .5 + ombre, size*(0.12), JGRAPHICS_2PI*0.47, JGRAPHICS_2PI*0.53);
    jgraphics_stroke(g);
    //oreille D ombre
    jgraphics_arc(g, rect->width * .5 + ombre, rect->height * .5 + ombre, size*(0.12), JGRAPHICS_2PI*0.97, JGRAPHICS_2PI*0.03);
    jgraphics_stroke(g);
    // nez ombre
    jgraphics_ovalarc(g, rect->width * .5 + ombre, rect->height * .5 - size*0.05 + ombre, size*0.015, size*0.07,  0., JGRAPHICS_2PI);
    jgraphics_fill(g);
    
    x->f_colorHead.alpha = 1;
    
    //tête
    jgraphics_set_source_jrgba(g, &x->f_colorHead);
    jgraphics_arc(g, rect->width * .5, rect->height * .5, size*0.1,  0., JGRAPHICS_2PI);
    jgraphics_fill(g);
    //oreille G
    jgraphics_set_line_width(g, size*(0.015));
    jgraphics_set_line_cap(g, JGRAPHICS_LINE_CAP_ROUND);
    jgraphics_arc(g, rect->width * .5, rect->height * .5, size*(0.12), JGRAPHICS_2PI*0.47, JGRAPHICS_2PI*0.53);
    jgraphics_stroke(g);
    //oreille D
    jgraphics_arc(g, rect->width * .5, rect->height * .5, size*(0.12), JGRAPHICS_2PI*0.97, JGRAPHICS_2PI*0.03);
    jgraphics_stroke(g);
    // nez
    jgraphics_ovalarc(g, rect->width * .5, rect->height * .5 - size*0.05, size*0.015, size*0.07,  0., JGRAPHICS_2PI);
    jgraphics_fill(g);
    */
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
