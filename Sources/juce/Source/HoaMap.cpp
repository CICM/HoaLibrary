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
    m_minimum_of_loudspeakers = 3;
    m_maximum_of_loudspeakers = m_maximum_of_sources = 64;
    m_minimum_of_sources = 1;
    m_sourceSize = 0.08;
    m_sourcePointed = m_sourceOver = -1;
    for (int i = 0; i < m_maximum_of_loudspeakers; i++)
    {
        m_sources_ordinate[i] = m_sources_abscissa[i] = 0.;
        //m_sources[i] = new Point();
    }
}

HoaMap::~HoaMap()
{
}

void HoaMap::mouseMove (const MouseEvent &event)
{
    /*
     Point<float> mouse = event.getPosition().toFloat();
     
     mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1,
     getWidth(), 0, 1, 1,
     getWidth(), getHeight(), 1, -1));
     
     m_sources[0].setXY(mouse.getX(), mouse.getY());
     repaint();
     */
}
void HoaMap::mouseDown (const MouseEvent &event)
{
    Point<float> mouse = event.getPosition().toFloat();
    // coordonnées mouse en cartesien :
    mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1,
                                                           getWidth(), 0, 1, 1,
                                                           getWidth(), getHeight(), 1, -1));
    m_sourcePointed = -1;
    for (int i = 0; i < m_maximum_of_sources; i++) {
        if (mouse.getDistanceFrom(m_sources[i]) < m_sourceSize) {
            m_sourcePointed = i;
            break;
        }
    }
}
void HoaMap::mouseDrag (const MouseEvent &event)
{
    Point<float> mouse = event.getPosition().toFloat();
    
    // conversion en cartesien :
    mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1,
                                                           getWidth(), 0, 1, 1,
                                                           getWidth(), getHeight(), 1, -1));
    
    if (m_sourcePointed >= 0 && m_sourcePointed < m_maximum_of_sources) {
        setSourceAbscissa(m_sourcePointed, mouse.getX());
        setSourceOrdinate(m_sourcePointed, mouse.getY());
        //m_sources[m_sourcePointed].setXY(mouse.getX(), mouse.getY());
        //setMouseCursor(CrosshairCursor);
        repaint();
    }
    /*
     if (mouse.getDistanceFromOrigin() < 1.0f - m_sourceSize) {
     m_sources[0].setXY(mouse.getX(), mouse.getY());
     repaint();
     }
     */
}
void HoaMap::mouseUp   (const MouseEvent &event)
{
    m_sourcePointed = -1;
}

void HoaMap::paint (Graphics& g)
{
    g.setColour (Colours::grey);
    g.drawEllipse(1, 1, getWidth()-2, getHeight()-2, 2);
    
    draw_speakers(g);
    draw_head(g);
    draw_sources(g);
    g.drawText(String(m_sources[0].getX()), 0, 0, getWidth(), 50, Justification(4), 1);
    g.drawText(String(m_sources[0].getY()), 0, 80, getWidth(), 50, Justification(4), 1);
    
}

void HoaMap::draw_sources(Graphics& g)
{
    for (int i = 0; i < m_nbSources; i++)
    {
        draw_source(g, i);
    }
}

void HoaMap::draw_source(Graphics& g, int _sourceIndex)
{
    float sourceSize = 0.08;
    
    g.beginTransparencyLayer(1);
    
    g.addTransform(AffineTransform::fromTargetPoints(-1, 1, 0, 0,
                                                     1, 1, getWidth(), 0,
                                                     1, -1, getWidth(), getHeight()));
    
    g.setColour ( (Colours::tomato).withAlpha((float)0.9) );
    
    g.fillEllipse(m_sources[_sourceIndex].getX()-sourceSize*0.5,
                  m_sources[_sourceIndex].getY()-sourceSize*0.5,
                  sourceSize, sourceSize);
    
    g.setColour ( Colour(0xff444444) );
    g.drawEllipse(m_sources[_sourceIndex].getX()-sourceSize*0.5,
                  m_sources[_sourceIndex].getY()-sourceSize*0.5,
                  sourceSize, sourceSize, sourceSize*0.1);
    
    g.setFont(sourceSize*0.01);
    g.drawText(String(_sourceIndex),
               m_sources[_sourceIndex].getX()-sourceSize*0.5,
               m_sources[_sourceIndex].getY()-sourceSize*0.5,
               sourceSize, sourceSize, Justification(4), false);
    g.endTransparencyLayer();
}

void HoaMap::draw_source_in_polar(Graphics& g, int _sourceIndex, float _radius, float _angle)
{
    ;
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

/* --- getters --- */
float HoaMap::getSourceAbscissa(int _sourceIndex)
{
    if (_sourceIndex >= 0 && _sourceIndex < m_maximum_of_sources) {
        return m_sources[_sourceIndex].getX();
    }
    return 0;
}
float HoaMap::getSourceOrdinate(int _sourceIndex)
{
    if (_sourceIndex >= 0 && _sourceIndex < m_maximum_of_sources) {
        return m_sources[_sourceIndex].getY();
    }
    return 0;
}

/* --- setters --- */
int HoaMap::setNbSources(int _nbSources)
{
    if (_nbSources < m_minimum_of_sources ) m_nbSources = m_minimum_of_sources;
    else if (_nbSources > m_maximum_of_sources) m_nbSources = m_maximum_of_sources;
    else m_nbSources = _nbSources;
    repaint();
    return 1;
}
int HoaMap::setNbSpeakers(int _nbSpeakers)
{
    if (_nbSpeakers < m_minimum_of_loudspeakers ) m_nbSpeakers = m_minimum_of_loudspeakers;
    else if (_nbSpeakers > m_maximum_of_loudspeakers) m_nbSpeakers = m_maximum_of_loudspeakers;
    else m_nbSpeakers = _nbSpeakers;
    repaint();
    return 1;
}
int HoaMap::setSpeakerDistance(float _speakerDistance)
{
    if (_speakerDistance < 0 ) m_speakerDistance = 0;
    else if (_speakerDistance > 1) m_speakerDistance = 1;
    else m_speakerDistance = _speakerDistance;
    repaint();
    return 1;
}
int HoaMap::setSpeakerOffset(float _speakerOffset)
{
    if (_speakerOffset < -180 ) m_speakerOffset = -180;
    else if (_speakerOffset > 180 ) m_speakerOffset = 180;
    else m_speakerOffset = _speakerOffset;
    repaint();
    return 1;
}
int HoaMap::setSourceAbscissa(int _sourceIndex, float _newAbscissa, NotificationType notification)
{
    if (_sourceIndex >= m_minimum_of_sources-1 && _sourceIndex < m_maximum_of_sources) {
        m_sources[_sourceIndex].setX(Tools::clip(_newAbscissa, -1.0f, 1.0f));
        triggerChangeMessage (notification);
        return 1;
    }
    return 0;
}
int HoaMap::setSourceOrdinate(int _sourceIndex, float _newOrdinate, NotificationType notification)
{
    if (_sourceIndex >= m_minimum_of_sources-1 && _sourceIndex < m_maximum_of_sources) {
        m_sources[_sourceIndex].setY(Tools::clip(_newOrdinate, -1.0f, 1.0f));
        triggerChangeMessage (notification);
        return 1;
    }
    return 0;
}

void HoaMap::triggerChangeMessage (const NotificationType notification)
{
    if (notification != dontSendNotification)
    {
        if (notification == sendNotificationSync)
        {
            sendSynchronousChangeMessage();
        }
        else sendChangeMessage ();
    }
}