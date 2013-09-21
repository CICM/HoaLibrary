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

#include "MapComponent.h"

/************************************************************************************/
/***************************** PROCESSOR ********************************************/
/************************************************************************************/

MapProcessor::MapProcessor()
{
    m_sources_manager   = new SourcesManager(-1, 1);
    m_map               = new AmbisonicsMultiMaps(1);
    m_zoom              = 0.5;
    m_order             = m_map->getOrder();
    m_number_of_harmonics = m_map->getNumberOfHarmonics();
    m_number_of_sources = m_map->getNumberOfSources();
}


MapProcessor::~MapProcessor()
{
    delete m_sources_manager;
    delete m_map;
}

void MapProcessor::setConfiguation(long anOrder, long aNumberOfSource)
{
    if(anOrder != m_order)
    {
        if(m_map)
            delete m_map;
        m_map = new AmbisonicsMultiMaps(anOrder, aNumberOfSource, 0, 512, 44100);
        m_order             = m_map->getOrder();
        m_number_of_harmonics = m_map->getNumberOfHarmonics();
        m_number_of_sources = m_map->getNumberOfSources();
    }
    if(aNumberOfSource != m_number_of_sources)
    {
        if(m_map)
            delete m_map;
        m_map = new AmbisonicsMultiMaps(m_order, aNumberOfSource, 0, 512, 44100);
        m_order             = m_map->getOrder();
        m_number_of_harmonics = m_map->getNumberOfHarmonics();
        m_number_of_sources = m_map->getNumberOfSources();
    }
    for(int i = 0; i < m_number_of_sources; i++)
    {
        if(!m_sources_manager->sourceGetExistence(i))
            m_sources_manager->sourceSetPolar(i, 1., CICM_2PI / (double)m_number_of_sources * (double)i);
    }
    for(int i = m_number_of_sources; i < m_sources_manager->getMaximumIndexOfSource(); i++)
    {
        m_sources_manager->sourceRemove(i);
    }
        
    for(int i = 0; i < m_number_of_sources; i++)
    {
        m_map->setCoordinatesCartesian(i, m_sources_manager->sourceGetAbscissa(i), m_sources_manager->sourceGetOrdinate(i));
    }
}

void MapProcessor::prepareToPlay(long aSampleRate, long aVectorSize)
{
    m_map->setSamplingRate(aSampleRate);
    m_map->setVectorSize(aVectorSize);
    m_map->setRamp(aVectorSize);
}


void MapProcessor::process(float** inputs, float** outputs)
{
    m_map->process(inputs, outputs);
    for(int i = 0; i < m_number_of_sources; i++)
    {
        m_map->setCoordinatesCartesian(i, m_sources_manager->sourceGetAbscissa(i), m_sources_manager->sourceGetOrdinate(i));
    }
}

void MapProcessor::setZoom(float aZoomvalue)
{
    m_zoom = Tools::clip(aZoomvalue, 0.01, 1.);
}

/************************************************************************************/
/***************************** EDITOR ***********************************************/
/************************************************************************************/

MapEditor::MapEditor(MapProcessor* aMapProcessor)
{
    m_map_processor     = aMapProcessor;
    m_sources_manager   = m_map_processor->getSourceManager();
    m_souce_selected    = -1;
    m_sources_size      = 15.;
}


MapEditor::~MapEditor()
{
    ;
}

void MapEditor::mouseMove(const MouseEvent &event)
{
    Point<float> source;
    Point<float> mouse = event.getPosition().toFloat();
    mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1, getWidth(), 0, 1, 1, getWidth(), getWidth(), 1, -1));
    
    m_souce_selected = -1;
    for (int i = 0; i < m_sources_manager->getNumberOfSources(); i++)
    {
        source.setXY(m_sources_manager->sourceGetAbscissa(i) * m_map_processor->getZoom(), m_sources_manager->sourceGetOrdinate(i) * m_map_processor->getZoom());
        if(mouse.getDistanceFrom(source) < m_sources_size * 0.002)
        {
            m_souce_selected = i;
            setMouseCursor(MouseCursor::PointingHandCursor);
            repaint();
            return;
        }
    }
    repaint();
    setMouseCursor(MouseCursor::NormalCursor);
}
void MapEditor::mouseDown(const MouseEvent &event)
{
    Point<float> source;
    Point<float> mouse = event.getPosition().toFloat();
    mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1, getWidth(), 0, 1, 1, getWidth(), getWidth(), 1, -1));
    
    m_souce_selected = -1;
    for (int i = 0; i < m_sources_manager->getNumberOfSources(); i++)
    {
        source.setXY(m_sources_manager->sourceGetAbscissa(i) * m_map_processor->getZoom(), m_sources_manager->sourceGetOrdinate(i) * m_map_processor->getZoom());
        if(mouse.getDistanceFrom(source) < m_sources_size * 0.002)
        {
            m_souce_selected = i;
            setMouseCursor(MouseCursor::PointingHandCursor);
            repaint();
            return;
        }
    }
    repaint();
    setMouseCursor(MouseCursor::NormalCursor);
}
void MapEditor::mouseDrag(const MouseEvent &event)
{
    Point<float> source;
    Point<float> mouse = event.getPosition().toFloat();
    mouse.applyTransform(AffineTransform::fromTargetPoints(0, 0, -1, 1, getWidth(), 0, 1, 1, getWidth(), getWidth(), 1, -1));
    
    if(m_souce_selected != -1)
    {
        m_sources_manager->sourceSetCartesian(m_souce_selected, mouse.getX() / m_map_processor->getZoom(), mouse.getY() / m_map_processor->getZoom());
        repaint();
    }
}

void MapEditor::mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel)
{
    m_map_processor->setZoom(m_map_processor->getZoom() + wheel.deltaY);
    repaint();
    if(event.mods.isShiftDown() || event.mods.isCtrlDown() || event.mods.isCommandDown())
    {
       
    }
}

void MapEditor::mouseUp(const MouseEvent &event)
{
    ;
}

void MapEditor::paint(Graphics& g)
{
    draw_background(g);
    draw_sources(g);
}

void MapEditor::draw_background(Graphics& g)
{
    float center = getWidth() * 0.5;
    
    for(int i = 1; i <= 5; i++)
    {
        float width = center * (i / 5.) * m_map_processor->getZoom();
        float start = center - width;
        g.setColour(Colours::white);
        g.drawEllipse(start + 0.5, start + 0.5, width * 2., width * 2., 2.);
        g.setColour(Colours::grey);
        g.drawEllipse(start, start, width * 2., width * 2., 1.);
    }
    
    float ecart = m_map_processor->getZoom() * center;
    if(ecart < 10. && ecart >= 5.)
        ecart *= 2.;
    else if(ecart < 5. && ecart > 2.5)
        ecart *= 4.;
    else if(ecart < 2.5)
        ecart *= 8.;
    ecart = (int)ecart;
    
    for(float i = 0; i < center; i += ecart)
    {
        g.setColour(Colours::white);
        g.drawLine(0.5, center - i + 0.5, getWidth() + 0.5, center - i + 0.5, 2.);
        g.drawLine(0.5, center + i + 0.5, getWidth() + 0.5, center + i + 0.5, 2.);
        g.drawLine(center - i + 0.5, getWidth() - i + 0.5, center - i + 0.5, getWidth() + 0.5, 2.);
        g.drawLine(center + i + 0.5, getWidth() + i + 0.5, center + i + 0.5, getWidth() + 0.5, 2.);

        g.setColour(Colours::grey);
        g.drawLine(0., center - i, getWidth(), center - i, 1.);
        g.drawLine(0.,  center + i, getWidth(), center + i, 1.);
        g.drawLine(center - i,  0., center - i, getWidth(), 1.);
        g.drawLine(center + i,  0., center + i, getWidth(), 1.);
    }
}

void MapEditor::draw_sources(Graphics& g)
{
    float source_thickness = 1.;
    float center = getWidth() * 0.5;
    for(int i = 0; i < m_sources_manager->getNumberOfSources(); i++)
    {
        g.setColour(Colour(0xff444444));        
        float source_x = m_sources_manager->sourceGetAbscissa(i) * m_map_processor->getZoom() * center + center;
        float source_y = -m_sources_manager->sourceGetOrdinate(i) * m_map_processor->getZoom() * center + center;
        
        
        if (i == m_souce_selected)
            source_thickness *= 1.5;
        else
            source_thickness = 1.;
        
        g.fillEllipse(source_x - m_sources_size * 0.35, source_y - m_sources_size * 0.35, m_sources_size * 0.7, m_sources_size * 0.7);
        g.drawEllipse(source_x - m_sources_size * 0.5, source_y - m_sources_size * 0.5, m_sources_size , m_sources_size, source_thickness);
        
        g.setFont(11);
        g.setColour(Colours::black);
        g.drawText(String(i+1), source_x - m_sources_size * 0.35, source_y - m_sources_size * 1.5,  m_sources_size, m_sources_size, Justification(4), FALSE);
    }
}

