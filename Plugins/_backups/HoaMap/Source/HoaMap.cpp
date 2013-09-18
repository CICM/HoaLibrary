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
    m_padding = 10;
    m_speaker_dir_of_rotation = -1;
    
    for (int i = 0; i < MAX_SOURCES; i++) {
        m_sources_dragState[i] = -1; // end dragging
        m_sources_ValueChanged[i] = 0;
    }
}

HoaMap::~HoaMap()
{
}

HoaMap::Source::Source() : Point<float>()
{
    //m_factor = 1.5;
    m_factor = 1.;
    m_azimuth = m_radius = 0;
}

void HoaMap::Source::timerCallback()
{
    //m_factor = 0.5;
    /*
    this->m_smooth.x = this->m_prev.x + (this->x - this->m_prev.x) * (2/(this->m_factor+1));
    this->m_smooth.y = this->m_prev.y + (this->y - this->m_prev.y) * (2/(this->m_factor+1));
    this->m_prev.x = this->m_smooth.x;
    this->m_prev.y = this->m_smooth.y;
    */
}
void HoaMap::Source::doSmoothValue()
{
    if (this->m_smooth.x != this->x) {
        this->m_smooth.x = this->m_prev.x + (this->x - this->m_prev.x) * (2/(this->m_factor+1));
        this->m_prev.x = this->m_smooth.x;
    }
    if (this->m_smooth.y != this->y) {
        this->m_smooth.y = this->m_prev.y + (this->y - this->m_prev.y) * (2/(this->m_factor+1));
        this->m_prev.y = this->m_smooth.y;
    }
}


void HoaMap::mouseMove (const MouseEvent &event)
{
    Point<float> mouse = event.getPosition().toFloat();
    // coordonnées mouse en cartesien :
    mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1,
                                                           getPadWidth(), 0, 1, 1,
                                                           getPadWidth(), getPadWidth(), 1, -1));
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
                                                           getPadWidth(), 0, 1, 1,
                                                           getPadWidth(), getPadWidth(), 1, -1));
    m_sourcePointed = -1;
    for (int i = 0; i < m_nbSources; i++) {
        if (mouse.getDistanceFrom(m_sources[i]) < m_sourceSize*0.5) {
            m_sourcePointed = i;
            m_sources_dragState[i] = 1; // begin dragging
            triggerChangeMessage(sendNotificationSync);
            break;
        }
    }
}
void HoaMap::mouseDrag (const MouseEvent &event)
{
    Point<float> mouse = event.getPosition().toFloat();
    Point<float> newPos;
    ModifierKeys modifierKey = event.mods;
    // conversion en cartesien :
    //mouse.applyTransform(AffineTransform::translation(m_padding, m_padding));
    mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1,
                                                           getPadWidth(), 0, 1, 1,
                                                           getPadWidth(), getPadWidth(), 1, -1));
    
    newPos = mouse;
    
    if (m_sourcePointed >= 0 && m_sourcePointed < m_nbSources) {
        setMouseCursor(MouseCursor::DraggingHandCursor);
        m_sources_dragState[m_sourcePointed] = -1; // reset dragging state
        m_sources_ValueChanged[m_sourcePointed] = 1;
        if (modifierKey.isShiftDown()) { // constrain move to distance
            setPolarCoordinates(m_sourcePointed, Tools::radius(newPos.x, newPos.y), m_sources[m_sourcePointed].getAzimuth());
        }
        else if (modifierKey.isCtrlDown()) { // constrain move to angle
            setPolarCoordinates(m_sourcePointed, m_sources[m_sourcePointed].getRadius(), Tools::angle(newPos.x, newPos.y));
        }
        else {
            setCartesianCoordinates(m_sourcePointed, newPos.x, newPos.y, sendNotificationSync);
        }
    }
}

void HoaMap::mouseUp   (const MouseEvent &event)
{
    if (m_sourcePointed >= 0) {
        m_sources_dragState[m_sourcePointed] = 0; // end dragging
        m_sources_ValueChanged[m_sourcePointed] = 0;
        triggerChangeMessage(sendNotificationSync);
    }
    m_sourcePointed = -1;
    setMouseCursor(MouseCursor::NormalCursor);
}

void HoaMap::paint (Graphics& g)
{
    draw_speakers(g);
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
    Path source;
    float sourceSize = m_sourceSize;
    m_sources[_sourceIndex].doSmoothValue();
    //float sourceX = m_sources[_sourceIndex].getSmoothX();
    //float sourceY = m_sources[_sourceIndex].getSmoothY();
    float sourceX = m_sources[_sourceIndex].getX();
    float sourceY = m_sources[_sourceIndex].getY();
    float sourceThickness = sourceSize*0.1;
    if (_sourceIndex == m_sourceOver) sourceThickness *= 1.5;
    
    g.beginTransparencyLayer(1);
    
    //g.addTransform(AffineTransform::translation(m_padding, m_padding));
    g.addTransform(AffineTransform::fromTargetPoints(-1, 1, 0, 0,
                                                     1, 1, getPadWidth(), 0,
                                                     1, -1, getPadWidth(), getPadWidth()));

    //g.setColour ( (Colour((float)fmod( (float)_sourceIndex * 1.61803398875, 1), (float)0.5, (float)0.8, (float)0.9 )).withAlpha((float)0.9) );
    
    g.setColour( Colour(0xff444444) );
    
    source.addCentredArc(sourceX, sourceY, sourceSize*0.35, sourceSize*0.35, 0, 0, CICM_2PI);
    g.fillPath(source);
    source.clear();
    
    //g.setColour ( Colour(0xff444444) );
    source.startNewSubPath(sourceX, sourceY-sourceSize*0.5);
    source.addCentredArc(sourceX, sourceY, sourceSize*0.5, sourceSize*0.5, 0, 0, CICM_2PI);
    g.strokePath(source, sourceThickness);
    
    g.endTransparencyLayer();
    
    // add text to the source :
    g.setFont(11);
    g.setColour ( Colour(0xff444444) );
    g.drawText(String(_sourceIndex+1), getSourcePixRect(m_sources[_sourceIndex]).translated(-sourceSize*0.35*getPadWidth(), -sourceSize*0.35*getPadWidth()), Justification(4), FALSE);
}

Rectangle<int> HoaMap::getSourcePixRect(Source& sourcePoint)
{
    //float center = getPadWidth() * 0.5;
    float center = getCenter();
    float sourceSizeinPix = m_sourceSize * center;
    return Rectangle<int>(((sourcePoint.getSmoothX()+1) * center) - sourceSizeinPix*0.5,
                          ((1-sourcePoint.getSmoothY()) * center) - sourceSizeinPix*0.5,
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
    float distSpeakerRayon = getPadWidth() * m_speakerDistance;
    float distSpeakerCenter = getCenter() - distSpeakerRayon*0.5;
    float center = getCenter();
    float stepAngle = HOA_2PI/(float)m_nbSpeakers;
    float speakerOffset = m_speakerOffset / (180 / HOA_PI);
    
    //draw a circle who represents distance of loudspeaker :
    g.setColour ( (Colours::black).withAlpha((float)0.1) );
    g.fillEllipse(distSpeakerCenter, distSpeakerCenter, distSpeakerRayon, distSpeakerRayon);
    g.setColour ( Colour(0xff444444) );
    g.drawEllipse(distSpeakerCenter, distSpeakerCenter, distSpeakerRayon, distSpeakerRayon, 1);

    //g.setColour ( Colour(0xff444444) );
    g.beginTransparencyLayer(1);
    for (i=0; i < m_nbSpeakers; i++) {
        g.addTransform(AffineTransform::rotation( m_speaker_dir_of_rotation*(i*stepAngle + speakerOffset), center, center));
        g.drawLine(center, distSpeakerCenter+((distSpeakerRayon*0.5) * 0.25 * ( (m_nbSpeakers-i)/(double)m_nbSpeakers) ), center, distSpeakerCenter, 2);
        g.addTransform(AffineTransform::rotation( -m_speaker_dir_of_rotation*(i*stepAngle + speakerOffset), center, center));
    }
    g.endTransparencyLayer();
}

void HoaMap::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}

/* --- getters --- */
float HoaMap::getSourceAbscissa(const int _sourceIndex)
{
    if (_sourceIndex >= 0 && _sourceIndex < m_maximum_of_sources) {
        return m_sources[_sourceIndex].getX();
    }
    return 0;
}
float HoaMap::getSourceOrdinate(const int _sourceIndex)
{
    if (_sourceIndex >= 0 && _sourceIndex < m_maximum_of_sources) {
        return m_sources[_sourceIndex].getY();
    }
    return 0;
}

int HoaMap::getDragState(const int _sourceIndex)
{
    if (_sourceIndex >= 0 && _sourceIndex < m_maximum_of_sources) {
        return m_sources_dragState[_sourceIndex];
    }
    return -1;
}
int HoaMap::getValueChanged(const int _sourceIndex)
{
    if (_sourceIndex >= 0 && _sourceIndex < m_maximum_of_sources) {
        return m_sources_ValueChanged[_sourceIndex];
    }
    return -1;
}

void HoaMap::resetDragState(const int _sourceIndex)
{
    if (_sourceIndex >= 0 && _sourceIndex < m_maximum_of_sources)
        m_sources_dragState[_sourceIndex] = -1;
}
void HoaMap::resetValueChanged(const int _sourceIndex)
{
    if (_sourceIndex >= 0 && _sourceIndex < m_maximum_of_sources)
        m_sources_ValueChanged[_sourceIndex] = 0;
}

/* --- setters --- */
int HoaMap::setNbSources(const int _nbSources, NotificationType notification)
{
    if (_nbSources < m_minimum_of_sources ) m_nbSources = m_minimum_of_sources;
    else if (_nbSources > m_maximum_of_sources) m_nbSources = m_maximum_of_sources;
    else m_nbSources = _nbSources;
    triggerChangeMessage (notification);
    repaint();
    return 1;
}
int HoaMap::setNbSpeakers(const int _nbSpeakers, NotificationType notification)
{
    if (_nbSpeakers < m_minimum_of_loudspeakers ) m_nbSpeakers = m_minimum_of_loudspeakers;
    else if (_nbSpeakers > m_maximum_of_loudspeakers) m_nbSpeakers = m_maximum_of_loudspeakers;
    else m_nbSpeakers = _nbSpeakers;
    triggerChangeMessage (notification);
    repaint();
    return 1;
}
int HoaMap::setSpeakerDistance(const float _speakerDistance, NotificationType notification)
{
    if (_speakerDistance < 0 ) m_speakerDistance = 0;
    else if (_speakerDistance > 1) m_speakerDistance = 1;
    else m_speakerDistance = _speakerDistance;
    triggerChangeMessage (notification);
    repaint();
    return 1;
}
int HoaMap::setSpeakerOffset(const float _speakerOffset, NotificationType notification)
{
    if (_speakerOffset < -180 ) m_speakerOffset = -180;
    else if (_speakerOffset > 180 ) m_speakerOffset = 180;
    else m_speakerOffset = _speakerOffset;
    triggerChangeMessage (notification);
    repaint();
    return 1;
}
int HoaMap::setSourceAbscissa(const int _sourceIndex, const float _newAbscissa, NotificationType notification)
{
    if (_sourceIndex >= m_minimum_of_sources-1 && _sourceIndex < m_maximum_of_sources) {
        setCartesianCoordinates(_sourceIndex, _newAbscissa, m_sources[_sourceIndex].y, notification);
        return 1;
    }
    return 0;
}
int HoaMap::setSourceOrdinate(const int _sourceIndex, const float _newOrdinate, NotificationType notification)
{
    if (_sourceIndex >= m_minimum_of_sources-1 && _sourceIndex < m_maximum_of_sources) {
        setCartesianCoordinates(_sourceIndex, m_sources[_sourceIndex].x, _newOrdinate, notification);
        return 1;
    }
    return 0;
}
int HoaMap::setCartesianCoordinates(const int _sourceIndex, const float _newAbscissa, const float _newOrdinate, NotificationType notification)
{
    Point<float> goodCoord(Tools::clip(_newAbscissa, -1.0f, 1.0f), Tools::clip(_newOrdinate, -1.0f, 1.0f));
    if (_sourceIndex >= m_minimum_of_sources-1 && _sourceIndex < m_maximum_of_sources) {
        
        float maxRadius, angle;
        maxRadius = 1.0f-m_sourceSize*0.5;
        angle = Tools::angle(goodCoord.x, goodCoord.y);
        if ( goodCoord.getDistanceFromOrigin() >= maxRadius)
            m_sources[_sourceIndex].setPolarCoordinates(maxRadius, angle);
        else
            m_sources[_sourceIndex].setPolarCoordinates(Tools::radius(goodCoord.x, goodCoord.y), angle);
        
        triggerChangeMessage (notification);
        repaint();
        return 1;
    }
    return 0;
}

int HoaMap::setPolarCoordinates(const int _sourceIndex, float _newRadius, float _newAzimuth, NotificationType notification)
{
    setCartesianCoordinates(_sourceIndex, Tools::abscissa(_newRadius, _newAzimuth), Tools::ordinate(_newRadius, _newAzimuth), notification);
    return 1;
}

int HoaMap::Source::setPolarCoordinates(float _newRadius, float _newAzimuth)
{
    m_azimuth = _newAzimuth;
    m_radius = _newRadius;
    setXY(Tools::abscissa(_newRadius, _newAzimuth), Tools::ordinate(_newRadius, _newAzimuth));
    return 1;
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

void HoaMap::constrainPointToRadius (Point<float>& source, const float radius)
{
    float angle;
    if ( source.getDistanceFromOrigin() > radius) {
        angle = Tools::angle(source.y, source.x);
        source.setXY(Tools::ordinate(radius, angle), Tools::abscissa(radius, angle));
    }
}
void HoaMap::constrainPointToRadius (Source& source, Point<float>& newPoint, const float radius)
{
    float angle;
    angle = Tools::angle(newPoint.x, newPoint.y);
    if ( newPoint.getDistanceFromOrigin() > radius)
    {        
        source.setPolarCoordinates(radius, angle);
    }
    else {
        source.setPolarCoordinates(Tools::radius(newPoint.x, newPoint.y), angle);
    }
}