
#include "MapComponent.h"

MapComponent::MapComponent(SourcesManager* aSourcesManger)
{
    m_sources_manager   = new SourcesManager(-1, 1);
    m_map               = new AmbisonicsMultiMaps(1);
    m_souce_selected    = -1;
    m_sources_size      = 0.08;
    m_background_invalidate = 1;
}

MapComponent::~MapComponent()
{
    delete m_sources_manager;
    delete m_map;
}

/************************************************************************************/
/***************************** PROCESSOR ********************************************/
/************************************************************************************/

void MapComponent::setNumberOfChannels(long aNumberOfInputs, long aNumberOfOuputs)
{
    long order;
    if(aNumberOfOuputs % 2 == 0)
        order = aNumberOfOuputs / 2 - 1;
    else
        order = aNumberOfOuputs / 2;
    
    if(order != m_map->getOrder())
    {
        if(m_map)
            delete m_map;
        m_map       = new AmbisonicsMultiMaps(order, aNumberOfInputs, 0, 512, 44100);
    }
    if(aNumberOfInputs != m_map->getNumberOfSources())
    {
        if(m_map)
            delete m_map;
        m_map = new AmbisonicsMultiMaps(order, aNumberOfInputs, 0, 512, 44100);
        if(aNumberOfInputs > m_sources_manager->getNumberOfSources())
        {
            for(int i = m_sources_manager->getNumberOfSources(); i < aNumberOfInputs; i++)
            {
                m_sources_manager->sourceSetPolar(0, 1., CICM_2PI / (double)aNumberOfInputs * (double)i);
            }
        }
        else if(aNumberOfInputs < m_sources_manager->getNumberOfSources())
        {
            for(int i = m_sources_manager->getNumberOfSources(); i > aNumberOfInputs; i--)
            {
                m_sources_manager->sourceRemove(i-1);
            }
        }
    }
    for(int i = 0; i < aNumberOfInputs; i++)
    {
        m_map->setCoordinatesCartesian(i, m_sources_manager->sourceGetAbscissa(i), m_sources_manager->sourceGetOrdinate(i));
    }
}

void MapComponent::prepareToPlay(long aSampleRate, long aVectorSize)
{
    m_map->setSamplingRate(aSampleRate);
    m_map->setVectorSize(aVectorSize);
    m_map->setRamp(aVectorSize);
}


void MapComponent::process(float** inputs, float** outputs)
{
    m_map->process(inputs, outputs);
    for(int i = 0; i < m_map->getNumberOfSources(); i++)
    {
        m_map->setCoordinatesCartesian(i, m_sources_manager->sourceGetAbscissa(i), m_sources_manager->sourceGetOrdinate(i));
    }
}

/************************************************************************************/
/***************************** EDITOR ***********************************************/
/************************************************************************************/

void MapComponent::mouseMove(const MouseEvent &event)
{
    Point<float> source;
    Point<float> mouse = event.getPosition().toFloat();
    mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1, getWidth(), 0, 1, 1, getWidth(), getWidth(), 1, -1));
    
    m_souce_selected = -1;
    for (int i = 0; i < m_sources_manager->getNumberOfSources(); i++)
    {
        source.setXY(m_sources_manager->sourceGetAbscissa(i), m_sources_manager->sourceGetOrdinate(i));
        if(mouse.getDistanceFrom(source) < m_sources_size * 0.5)
        {
            m_souce_selected = i;
            setMouseCursor(MouseCursor::PointingHandCursor);
            repaint();
            return;
        }
    }
    setMouseCursor(MouseCursor::NormalCursor);
}
void MapComponent::mouseDown(const MouseEvent &event)
{
    Point<float> source;
    Point<float> mouse = event.getPosition().toFloat();
    mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1, getWidth(), 0, 1, 1, getWidth(), getWidth(), 1, -1));
    
    m_souce_selected = -1;
    for (int i = 0; i < m_sources_manager->getNumberOfSources(); i++)
    {
        source.setXY(m_sources_manager->sourceGetAbscissa(i), m_sources_manager->sourceGetOrdinate(i));
        if(mouse.getDistanceFrom(source) < m_sources_size * 0.5)
        {
            m_souce_selected = i;
            setMouseCursor(MouseCursor::PointingHandCursor);
            repaint();
            return;
        }
    }
    setMouseCursor(MouseCursor::NormalCursor);
}
void MapComponent::mouseDrag(const MouseEvent &event)
{
    Point<float> source;
    Point<float> mouse = event.getPosition().toFloat();
    mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1, getWidth(), 0, 1, 1, getWidth(), getWidth(), 1, -1));
    
    if(m_souce_selected != -1)
    {
        m_sources_manager->sourceSetCartesian(m_souce_selected, mouse.getX(), mouse.getY());
        repaint();
    }
}

void MapComponent::mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel)
{
    if(event.mods.isShiftDown() && wheel.deltaX)
    {
        m_sources_manager->setZoom(m_sources_manager->getZoom() + wheel.deltaX);
        m_background_invalidate = 1;
        repaint();
    }
}

void MapComponent::mouseUp(const MouseEvent &event)
{
    ;
}

void MapComponent::paint(Graphics& g)
{
    draw_background(g);
    draw_sources(g);
}

void MapComponent::draw_background(Graphics& g)
{
    if(m_background_invalidate)
    {
        Path backgroung;
        g.addTransform(AffineTransform::fromTargetPoints(-1, 1, 0, 0, 1, 1, getWidth(), 0, 1, -1, getWidth(), getWidth()));
        
        backgroung.addRectangle(-1., -1., 1., 1.);
        g.setColour(Colours::grey);
        g.fillPath(backgroung);
        
        g.setColour(Colours::black);
        g.strokePath(backgroung, 0.01);
        backgroung.clear();
        backgroung.addEllipse(- m_sources_manager->getZoom() / 2., - m_sources_manager->getZoom() / 2., m_sources_manager->getZoom() / 2., m_sources_manager->getZoom() / 2.);
        g.strokePath(backgroung, 0.01);
    }
    m_background_invalidate = 0;
}

void MapComponent::draw_sources(Graphics& g)
{
    Path source;
    float source_thickness = m_sources_size * 0.1;
    g.addTransform(AffineTransform::fromTargetPoints(-1, 1, 0, 0, 1, 1, getWidth(), 0, 1, -1, getWidth(), getWidth()));
    for(int i = 0; i < m_sources_manager->getNumberOfSources(); i++)
    {
        float source_x = m_sources_manager->sourceGetAbscissa(i) / m_sources_manager->getZoom();
        float source_y =m_sources_manager->sourceGetOrdinate(i) / m_sources_manager->getZoom();
        
        if (i == m_souce_selected)
            source_thickness *= 1.5;
        
        g.setColour( Colour(0xff444444) );
        
        source.addCentredArc(source_x, source_y, m_sources_size * 0.35, m_sources_size * 0.35, 0, 0, CICM_2PI);
        g.fillPath(source);
        source.clear();
    
        source.startNewSubPath(source_x, source_y - m_sources_size * 0.5);
        source.addCentredArc(source_x, source_y, m_sources_size * 0.5, m_sources_size * 0.5, 0, 0, CICM_2PI);
        g.strokePath(source, source_thickness);
    }
}

