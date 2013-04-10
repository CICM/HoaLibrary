/*
 ==============================================================================
 
 HoaMap.cpp
 Created: 13 Mar 2013 11:15:41pm
 Author:  eliott PARIS
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "HoaMap.h"

//==============================================================================
HoaMap::HoaMap()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    m_nbSources = DEF_SOURCES;
    m_nbSpeakers = DEF_LOUDSPEAKERS;
    m_speakerOffset = 0;
    m_speakerDistance = 0.5;
    m_minimum_of_loudspeakers = MIN_LOUDSPEAKERS;
    m_maximum_of_loudspeakers = MAX_LOUDSPEAKERS;
    m_minimum_of_sources = MIN_SOURCES;
    m_maximum_of_sources = MAX_SOURCES;
    m_sourceSize = 0.08;
    m_sourcePointed = m_sourceOver = -1;
    
    for (int i = 0; i < MAX_SOURCES; i++) {
        m_sources_dragState[i] = -1; // end dragging
        m_sources_ValueHasChange[i] = 0;
    }
}

HoaMap::~HoaMap()
{
}

void HoaMap::mouseMove (const MouseEvent &event)
{
    Point<float> mouse = event.getPosition().toFloat();
    // coordonnées mouse en cartesien :
    mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1,
                                                           getWidth(), 0, 1, 1,
                                                           getWidth(), getHeight(), 1, -1));
    setMouseCursor(MouseCursor::NormalCursor);
    m_sourceOver = -1;
    for (int i = 0; i < m_nbSources; i++) {
        if (mouse.getDistanceFrom(m_sources[i]) < m_sourceSize*0.5 && i <= m_nbSources) {
            m_sourceOver = i;
            setMouseCursor(MouseCursor::PointingHandCursor);
            break;
        }
    }
    repaint();
}
void HoaMap::mouseDown (const MouseEvent &event)
{
    Point<float> mouse = event.getPosition().toFloat();
    // coordonnées mouse en cartesien :
    mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1,
                                                           getWidth(), 0, 1, 1,
                                                           getWidth(), getHeight(), 1, -1));
    m_sourcePointed = -1;
    for (int i = 0; i < m_nbSources; i++) {
        if (mouse.getDistanceFrom(m_sources[i]) < m_sourceSize*0.5) {
            m_sourcePointed = i;
            m_sources_dragState[i] = 1; // begin dragging
            m_sources_ValueHasChange[i] = 1;
            triggerChangeMessage(sendNotificationSync);
            break;
        }
    }
}
void HoaMap::mouseDrag (const MouseEvent &event)
{
    Point<float> mouse = event.getPosition().toFloat();
    Point<float> newPos;
    
    // conversion en cartesien :
    mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1,
                                                           getWidth(), 0, 1, 1,
                                                           getWidth(), getHeight(), 1, -1));
    
    newPos = mouse;
    
    if (m_sourcePointed >= 0 && m_sourcePointed < m_nbSources) {
        setMouseCursor(MouseCursor::DraggingHandCursor);
        setCartesianCoordinates(m_sourcePointed, newPos.x, newPos.y, sendNotificationSync);
    }
}

void HoaMap::mouseUp   (const MouseEvent &event)
{
    if (m_sourcePointed >= 0) {
        m_sources_dragState[m_sourcePointed] = 0; // end dragging
        m_sources_ValueHasChange[m_sourcePointed] = 0;
        triggerChangeMessage(sendNotificationSync);
    }
    m_sourcePointed = -1;
    setMouseCursor(MouseCursor::NormalCursor);
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
    int drawSourceInLast = -1;
    for (int i = m_nbSources-1; i >= 0; i--)
    {
        if (i == m_sourcePointed || i == m_sourceOver) {
            drawSourceInLast = i;
        }
        else
        {
            draw_source(g, i);
        }
    }
    if (drawSourceInLast >= 0) {
        draw_source(g, drawSourceInLast);
    }
}

void HoaMap::draw_source(Graphics& g, int _sourceIndex)
{
    float sourceSize = 0.08;
    float sourceX = m_sources[_sourceIndex].getX()-sourceSize*0.5;
    float sourceY = m_sources[_sourceIndex].getY()-sourceSize*0.5;
    float sourceThickness = sourceSize*0.1;
    if (_sourceIndex == m_sourceOver) sourceThickness *= 1.5;
    
    g.beginTransparencyLayer(1);
    
    g.addTransform(AffineTransform::fromTargetPoints(-1, 1, 0, 0,
                                                     1, 1, getWidth(), 0,
                                                     1, -1, getWidth(), getHeight()));

    g.setColour ( (Colour((float)fmod( (float)_sourceIndex * 1.61803398875, 1), (float)0.5, (float)0.8, (float)0.9 )).withAlpha((float)0.9) );
    g.fillEllipse(sourceX, sourceY, sourceSize, sourceSize);
    
    g.setColour ( Colour(0xff444444) );
    g.drawEllipse(sourceX, sourceY, sourceSize, sourceSize, sourceThickness);
    
    g.endTransparencyLayer();
    
    // add text to the source :
    g.setFont(11);
    g.setColour ( Colour(0xff444444) );
    g.drawText(String(_sourceIndex+1), getSourcePixRect(m_sources[_sourceIndex]), Justification(4), FALSE);
}

Rectangle<int> HoaMap::getSourcePixRect(Point<float>& sourcePoint)
{
    float center = getWidth() * 0.5;
    float sourceSizeinPix = m_sourceSize * center;
    return Rectangle<int>(((sourcePoint.x+1) * center) - sourceSizeinPix*0.5,
                          ((1-sourcePoint.y) * center) - sourceSizeinPix*0.5,
                          sourceSizeinPix,
                          sourceSizeinPix);

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
        g.addTransform(AffineTransform::rotation( i*stepAngle+stepAngle + speakerOffset, center, center));
        //g.drawFittedText(String(i+1),
        g.drawFittedText(String(m_nbSpeakers-i),
                         center-speakerSize*0.5,
                         center - getHeight()*0.5*m_speakerDistance - speakerSize*0.5 -1,
                         speakerSize,
                         speakerSize, Justification(4), true);
        g.addTransform(AffineTransform::rotation( -( i*stepAngle+stepAngle + speakerOffset), center, center));
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

int HoaMap::getDragState(int _sourceIndex)
{
    if (_sourceIndex >= 0 && _sourceIndex < m_maximum_of_sources) {
        return m_sources_dragState[_sourceIndex];
    }
    return -1;
}
int HoaMap::getValueHasChanged(int _sourceIndex)
{
    if (_sourceIndex >= 0 && _sourceIndex < m_maximum_of_sources) {
        return m_sources_ValueHasChange[_sourceIndex];
    }
    return -1;
}

/* --- setters --- */
int HoaMap::setNbSources(int _nbSources, NotificationType notification)
{
    if (_nbSources < m_minimum_of_sources ) m_nbSources = m_minimum_of_sources;
    else if (_nbSources > m_maximum_of_sources) m_nbSources = m_maximum_of_sources;
    else m_nbSources = _nbSources;
    triggerChangeMessage (notification);
    repaint();
    return 1;
}
int HoaMap::setNbSpeakers(int _nbSpeakers, NotificationType notification)
{
    if (_nbSpeakers < m_minimum_of_loudspeakers ) m_nbSpeakers = m_minimum_of_loudspeakers;
    else if (_nbSpeakers > m_maximum_of_loudspeakers) m_nbSpeakers = m_maximum_of_loudspeakers;
    else m_nbSpeakers = _nbSpeakers;
    triggerChangeMessage (notification);
    repaint();
    return 1;
}
int HoaMap::setSpeakerDistance(float _speakerDistance, NotificationType notification)
{
    if (_speakerDistance < 0 ) m_speakerDistance = 0;
    else if (_speakerDistance > 1) m_speakerDistance = 1;
    else m_speakerDistance = _speakerDistance;
    triggerChangeMessage (notification);
    repaint();
    return 1;
}
int HoaMap::setSpeakerOffset(float _speakerOffset, NotificationType notification)
{
    if (_speakerOffset < -180 ) m_speakerOffset = -180;
    else if (_speakerOffset > 180 ) m_speakerOffset = 180;
    else m_speakerOffset = _speakerOffset;
    triggerChangeMessage (notification);
    repaint();
    return 1;
}
int HoaMap::setSourceAbscissa(int _sourceIndex, float _newAbscissa, NotificationType notification)
{
    if (_sourceIndex >= m_minimum_of_sources-1 && _sourceIndex < m_maximum_of_sources) {
        m_sources[_sourceIndex].setX(Tools::clip(_newAbscissa, -1.0f, 1.0f));
        constrainPointToRadius(m_sources[_sourceIndex], 1.0f-m_sourceSize*0.5);
        triggerChangeMessage (notification);
        repaint();
        return 1;
    }
    return 0;
}
int HoaMap::setSourceOrdinate(int _sourceIndex, float _newOrdinate, NotificationType notification)
{
    if (_sourceIndex >= m_minimum_of_sources-1 && _sourceIndex < m_maximum_of_sources) {
        m_sources[_sourceIndex].setY(Tools::clip(_newOrdinate, -1.0f, 1.0f));
        constrainPointToRadius(m_sources[_sourceIndex], 1.0f-m_sourceSize*0.5);
        triggerChangeMessage (notification);
        repaint();
        return 1;
    }
    return 0;
}
int HoaMap::setCartesianCoordinates(int _sourceIndex, float _newAbscissa, float _newOrdinate, NotificationType notification)
{
    if (_sourceIndex >= m_minimum_of_sources-1 && _sourceIndex < m_maximum_of_sources) {
        m_sources[_sourceIndex].setXY(Tools::clip(_newAbscissa, -1.0f, 1.0f), Tools::clip(_newOrdinate, -1.0f, 1.0f));
        constrainPointToRadius(m_sources[_sourceIndex], 1.0f-m_sourceSize*0.5);
        triggerChangeMessage (notification);
        repaint();
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

void HoaMap::constrainPointToRadius (Point<float>& source, float radius)
{
    float angle;
    if ( source.getDistanceFromOrigin() > radius) {
        angle = Tools::angle(source.y, source.x);
        source.setXY(Tools::ordinate(radius, angle), Tools::abscisse(radius, angle));
    }
}