/*
 ==============================================================================
 
 HoaMap.h
 Created: 13 Mar 2013 11:15:41pm
 Author:  eliott PARIS
 
 ==============================================================================
 */

#ifndef __HoaMap_H_5D25AFEF__
#define __HoaMap_H_5D25AFEF__

#include "../JuceLibraryCode/JuceHeader.h"
#include "CicmTools.h"

#ifndef HOA_PI
#define HOA_PI		(3.1415926535897932384626433832795028842)
#define HOA_2PI		(2. * 3.1415926535897932384626433832795028842)
#endif

//==============================================================================
class HoaMap    :
public Component,
public ChangeBroadcaster
{
public:
    HoaMap();
    ~HoaMap();
    
    void paint (Graphics&);
    void draw_head (Graphics&);
    void draw_speakers (Graphics&);
    void draw_sources (Graphics&);
    void draw_source (Graphics& g, int _sourceIndex);
    void draw_source_in_polar(Graphics& g, int _sourceIndex, float _radius, float _angle);
    void draw_source_in_cart(Graphics& g, int _sourceIndex, float _X, float _Y);
    void draw_source_in_pixel(Graphics& g, int _sourceIndex, float _X, float _Y);
    void resized();
    
    //mouse events :
    void mouseMove (const MouseEvent &event);
    void mouseDown (const MouseEvent &event);
    void mouseDrag (const MouseEvent &event);
    void mouseUp   (const MouseEvent &event);
    
    // setters :
    int setNbSources(const int _nbSources, NotificationType notification = dontSendNotification);
    int setNbSpeakers(const int _nbSpeakers, NotificationType notification = dontSendNotification);
    int setSpeakerDistance(const float _speakerDistance, NotificationType notification = dontSendNotification);
    int setSpeakerOffset(const float _speakerOffset, NotificationType notification = dontSendNotification);
    int setSourceAbscissa(const int _sourceIndex, float _newAbscissa, NotificationType notification = sendNotificationAsync);
    int setSourceOrdinate(const int _sourceIndex, float _newOrdinate, NotificationType notification = sendNotificationAsync);
    int setCartesianCoordinates(const int _sourceIndex, float _newAbscissa, float _newOrdinate, NotificationType notification = sendNotificationAsync);
    int setPolarCoordinates(const int _sourceIndex, float _newRadius, float _newAzimuth, NotificationType notification = sendNotificationAsync);
    
    // getters :
    inline  int   getNbSources()  { return m_nbSources; }
    inline  int   getNbSpeakers() { return m_nbSpeakers; }
    inline  float getSpeakerDistance() { return m_speakerDistance; }
    float getSpeakerOffset() { return m_speakerOffset; }
    float getSourceOrdinate(const int _sourceIndex);
    float getSourceAbscissa(const int _sourceIndex);
    int   getDragState(const int _sourceIndex);
    int   getValueChanged(const int _sourceIndex);
    
    void resetDragState(const int _sourceIndex);
    void resetValueChanged(const int _sourceIndex);
    
    void triggerChangeMessage (const NotificationType notification);
    
private:
    
    class Source : public Point<float>, public Timer
    {
    public:
        Source();
        inline Point<float> getSmoothPoint() { return m_smooth;}
        inline float getSmoothX() { return m_smooth.getX();}
        inline float getSmoothY() { return m_smooth.getY();}
        inline void resetDragState() {m_dragState = -1;}
        inline int  getDragState() {return m_dragState;}
        inline void resetValueChanged() {m_valueChanged = 0;}
        inline int  getValueChanged() {return m_dragState;}
        void timerCallback();
        void doSmoothValue();
        int setPolarCoordinates(float _newRadius, float _newAzimuth);
        inline float getAzimuth() {return m_azimuth;}
        inline float getRadius() {return m_radius;}
        
    private:
        Point<float> m_prev;
        Point<float> m_smooth;
        float m_factor;
        int m_dragState;
        bool m_valueChanged;
        float m_azimuth;
        float m_radius;
    };
    
    friend class Source;
    Source m_sources[MAX_SOURCES];
    
    int m_minimum_of_loudspeakers, m_maximum_of_loudspeakers, m_minimum_of_sources, m_maximum_of_sources;
    int m_nbSources, m_nbSpeakers;
    int m_speaker_dir_of_rotation;
    float m_speakerOffset, m_speakerDistance;
    float m_sourceSize;
    int m_sourcePointed, m_sourceOver;
    int m_padding;
    //inline int getPadWidth() {return getWidth()-(m_padding*2);};
    inline int getPadWidth() {return getWidth();};
    inline float getCenter() {return getWidth()*0.5;};
    
    int m_sources_dragState[MAX_SOURCES];
    int m_sources_ValueChanged[MAX_SOURCES];
    
    void constrainPointToRadius (Point<float>& source, float radius);
    void constrainPointToRadius (Source& source, Point<float>& newPoint, const float radius);
    Rectangle<int> getSourcePixRect(Point<float>& sourcePoint);
    Rectangle<int> getSourcePixRect(Source& sourcePoint);
    
    //Point<float> m_sources[MAX_SOURCES];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HoaMap)
};


#endif  // __HoaMap_H_5D25AFEF__