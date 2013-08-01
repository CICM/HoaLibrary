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
 *  - Redistributions in binary form must reproduce the above copyright notice,
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
#pragma GCC diagnostic ignored "-Wwrite-strings"

#define MAX_ZOOM 1.
#define MIN_ZOOM 0.01

#define MAX_SPEAKER 64



extern "C"
{
#include "../m_pd.h"
#include "../iemlib.h"
#include "../iemgui.h"
#include "../g_canvas.h"
#include "../g_all_guis.h"
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "../../Sources/CicmLibrary/cicmTools.h"


#ifdef MSW
#include <io.h>
#else
#include <unistd.h>
#endif







t_widgetbehavior hoaMeter_widgetbehavior;

static t_class *hoaMeter_class;

typedef struct _hoaMeter
{
    t_iemgui  x_gui;
    
    
    double		f_centerX;
    double		f_centerY;
    
    int			f_startclock;

    int			f_interval;
	long		f_numberOfLoudspeakers;
	double		f_offsetOfLoudspeakers;
	
	int			f_dbperled;
	int			f_nhotleds;
	int			f_ntepidleds;
	int			f_nwarmleds;
	int			f_numleds;
	
	float		f_speakerAngles[MAX_SPEAKER];
	long		f_nSpeakerAngles;
	float		f_speakerRealAngle[MAX_SPEAKER];
	float		f_speakerWidth[MAX_SPEAKER];
	float		f_speakerWidthMax;
	double*		f_amplitudeOfLoudspeakers;
	double*		f_energyOfLoudspeakers;
	double*		f_abscisseOfLoudspeakers;
	double*		f_ordonneOfLoudspeakers;
	double		f_energyVectorX;
	double		f_energyVectorY;
    
    double		f_rayonMax;
	double		f_rayonCircle;
	double		f_fontsize;
	
	double		f_strokeWidth;
	double		f_rayonExt;
	double		f_rayonInt;
	int			f_drawmeter;
	long		f_leds_bg;
	long		f_energy;
	double		f_metersize;
    int         f_speakers_dir_of_rotation;
    int         f_fill_direction;
    
    int         f_colorBaseLed;
    int         f_colorTepidSignal;
    int         f_colorColdSignal;
    int         f_colorWarmSignal;
    int         f_colorHotSignal;
    
    
	


    
} t_hoaMeter;

/*  ****** ****** ****** ****** ****** ****** ****** ****** ****** ****** ****** ****** ****** */
// Interface
double degtorad(double degree);
double radtodeg(double rad);

static void hoaMeter_speakerPosProcess(t_hoaMeter *x);
int f_speakerAngles_set(t_hoaMeter *x,  long ac, t_atom *av);

/*  ****** ****** ****** ****** ****** ****** ****** ****** ****** ****** ****** ****** ****** */
// Implementation

static void hoaMeter_draw_skelton(t_hoaMeter *x,  t_glist *glist)
{
	int i,j;
	long nLoudSpeak = x->f_numberOfLoudspeakers;
	double deg1, deg2, rotateAngle, ledContainerSize, ledStroke, ledMargin, ledOffset;
	
    int xpos=text_xpix(&x->x_gui.x_obj, glist);
    int ypos=text_ypix(&x->x_gui.x_obj, glist);
    t_canvas *canvas=glist_getcanvas(glist);
    
	
	
	deg1 = degtorad(90);
	ledContainerSize = x->f_rayonExt - x->f_rayonInt - (x->f_strokeWidth*4);
	ledOffset = ledContainerSize / (x->f_numleds+1);
	ledStroke = ledOffset * 0.75;
	ledMargin = ledOffset * 0.25;
	
    // Background Ext circle tag : CIRCLE1
    
    int r= x->f_rayonExt;
    sys_vgui(".x%lx.c create oval %d %d %d %d -outline Black -fill #666666   -tags %lxCIRCLEEXT\n",
             canvas,
             xpos+(x->x_gui.x_w)/2-r,
             ypos+(x->x_gui.x_h)/2-r,
             xpos+(x->x_gui.x_w)/2+r,
             ypos+(x->x_gui.x_h)/2+r,
             x
             );
    r= x->f_rayonInt;
    sys_vgui(".x%lx.c create oval %d %d %d %d -outline Black   -tags %lxCIRCLEINT\n",
             canvas,
             xpos+(x->x_gui.x_w)/2-r,
             ypos+(x->x_gui.x_h)/2-r,
             xpos+(x->x_gui.x_w)/2+r,
             ypos+(x->x_gui.x_h)/2+r,
             x
             );
    int _x,_y,_X,_Y;

    for(i=0; i<nLoudSpeak; i++)
    {

        // Separateurs : tag : SEPARATORi
        deg2 = degtorad(90+(x->f_speakerWidth[i]));
        rotateAngle = x->f_speakerRealAngle[i] - (x->f_speakerWidth[i]*0.5) + x->f_offsetOfLoudspeakers;
        if (!x->f_speakers_dir_of_rotation)
        {
            rotateAngle += x->f_speakerWidth[i];
            rotateAngle *= -1;
        }
        
        
        
        // leds
            // leds Background :
            for( j=0; j < x->f_numleds; j++ )
            {
                double  str  = radtodeg(  deg1+(0.008 * (j+1) * x->f_metersize));
                double  extd =radtodeg( deg2-(0.008 * (j+1) * x->f_metersize) )- str;
                
                str+=rotateAngle;
                
                double radius = x->f_rayonExt-(j*ledOffset) - ledMargin*2 - x->f_strokeWidth*2;
                
                _x = (int) xpos+(x->x_gui.x_w)/2 -radius;
                _y = (int) ypos+(x->x_gui.x_h)/2 -radius;
                
                _X = (int)xpos+(x->x_gui.x_w)/2+radius;
                _Y = (int) ypos+(x->x_gui.x_h)/2+radius;
                
                
    
                

                sys_vgui(".x%lx.c create arc  %d %d %d %d -start %f -extent %f  -outline #%6.6x -style arc -width 4 -tags %lxLed%d%d\n",
                         canvas,
                         _x,
                         _y,
                         _X,
                         _Y,
                         str,
                         extd,
                         x->f_colorBaseLed,
                         x,
                         i,
                         j
                         );
                
                if (x->f_numberOfLoudspeakers > 1)
                {
                    if ( x->f_numberOfLoudspeakers < 24  && (x->f_speakerWidth[i] > 14.5))
                    {
                        // inside
                        if (x->f_fill_direction == 0)
                        {
                            

                       
                        }
                        
                        // outside
                        else
                        {
                       
                        }
                    }
                    else
                    {
                        // inside
                        if (x->f_fill_direction == 0)
                        {
                       
                        }

                        // outside
                        else
                        {
                       
                        }
                    }
                }
                
                // mono
                else
                {
                    // inside
                    if (x->f_fill_direction == 0)
                    {
                 
                    }
                    
                    // outside
                    else
                    {
                 
                    }
                }
            }
        // coords sur cercle intérieur
        _x = (int) (x->f_rayonInt*cos( degtorad(rotateAngle)));
        _y = (int) (x->f_rayonInt*sin( degtorad(rotateAngle)));
        
        // coords sur cercle extérieur
        _X = (int) (x->f_rayonExt*cos( degtorad(rotateAngle)));
        _Y = (int) (x->f_rayonExt*sin( degtorad(rotateAngle)));
        
        // separateurs
        sys_vgui(".x%lx.c create line %d %d %d %d -fill Black   -tags %lxSEPARATOR%d\n",
                 canvas,
                 (int) xpos+(x->x_gui.x_w)/2 + _x,
                 (int) ypos+(x->x_gui.x_h)/2 + _y,
                 xpos+(x->x_gui.x_w)/2+_X,
                 ypos+(x->x_gui.x_h)/2+_Y,
                 x,
                 i
                 );
        

    }
}

static void hoaMeter_draw_new_vector(t_hoaMeter *x,   t_glist *glist)
{
    int xpos=text_xpix(&x->x_gui.x_obj, glist);
    int ypos=text_ypix(&x->x_gui.x_obj, glist);
    t_canvas *canvas=glist_getcanvas(glist);
    int _x,_y;
    
	double angle, rayon, value, arrow;

    /* Energy */

    if (x->f_energyVectorX == 0.)
		value = 0.;
	else
		value = atan2(x->f_energyVectorY, x->f_energyVectorX);
		
    angle = value + (x->f_offsetOfLoudspeakers / 180.) * M_PI;
	rayon = x->f_rayonInt * 0.85;
	arrow = rayon * 0.15;
    
    _x = (int) rayon*cos(angle);
    _y = (int) rayon*sin(angle);
    
    sys_vgui(".x%lx.c create line %d %d %d %d -fill Blue -arrow last   -tags %lxARROW\n",
             canvas,
             (int) xpos+(x->x_gui.x_w)/2  ,
             (int) ypos+(x->x_gui.x_h)/2  ,
             xpos+(x->x_gui.x_w)/2 + _x,
             ypos+(x->x_gui.x_h)/2 + _y,
             x
             );
    


    

}
static void hoaMeter_update_vector(t_hoaMeter *x,   t_glist *glist)
{
    int xpos=text_xpix(&x->x_gui.x_obj, glist);
    int ypos=text_ypix(&x->x_gui.x_obj, glist);
    t_canvas *canvas=glist_getcanvas(glist);
    int _x,_y;
    
	double angle, rayon, value, arrow;
    

    
    /* Energy */

    if (x->f_energyVectorX == 0.)
		value = 0.;
	else
		value = atan2(x->f_energyVectorY, x->f_energyVectorX);
    

    angle = value + (x->f_offsetOfLoudspeakers / 180.) * M_PI;

	rayon = x->f_rayonInt * 0.85;
	arrow = rayon * 0.15;
    
    _x = (int) -rayon*sin(angle);
    _y = (int) -rayon*cos(-angle);
    
    sys_vgui(".x%lx.c coords %lxARROW %d %d %d %d \n",
             canvas,
             x,
             (int) xpos+(x->x_gui.x_w)/2  ,
             (int) ypos+(x->x_gui.x_h)/2  ,
             xpos+(x->x_gui.x_w)/2 + _x,
             ypos+(x->x_gui.x_h)/2 + _y
             );
    
        
}
static void hoaMeter_update_meter(t_hoaMeter *x, t_glist *glist)
{

    t_canvas *canvas=glist_getcanvas(glist);
	int i,
        j,
        nbLed,
        tepidLimit,
        warmLimit,
        hotLimit,
        drawOverLed;
    
    int ledColor;
	long nLoudSpeak = x->f_numberOfLoudspeakers;
	double  meter_dB,
            min_dB_to_display;
	

	nbLed = x->f_numleds+1;




    
	hotLimit = x->f_numleds - x->f_nhotleds;
	warmLimit = hotLimit - x->f_nwarmleds;
	tepidLimit = warmLimit - x->f_ntepidleds;

    
	min_dB_to_display = -1 * ( (x->f_numleds * x->f_dbperled) - (x->f_dbperled * 0.5) );

	x->f_speakerWidthMax = 0.;
	
    if(glist_isvisible(glist))
    {
        

		for(i=0; i<nLoudSpeak; i++)
		{
            int ii = (nLoudSpeak-i)%nLoudSpeak;
			meter_dB = x->f_energyOfLoudspeakers[i]; // dB (negatif) de -240 à 0;
			

            
            if ( meter_dB >= 0. ) drawOverLed = 1;
			else drawOverLed = 0;
			
            // au dessus
			if ( meter_dB > min_dB_to_display )
			{
                    
				// leds :
				for(j=0; j<nbLed; j++)
				{
					if ( ( j < nbLed ) && ( meter_dB > min_dB_to_display + (x->f_dbperled * j) ) )
					{
						if ( j < tepidLimit ) ledColor = x->f_colorColdSignal;
						else if ( j < warmLimit ) ledColor = x->f_colorTepidSignal;
						else if ( j < hotLimit ) ledColor = x->f_colorWarmSignal;
						else ledColor = x->f_colorHotSignal;
                        
                        sys_vgui(".x%lx.c itemconfigure %lxLed%d%d -outline #%6.6x\n",
                                 canvas,
                                 x,
                                 ii,
                                 j,
                                 ledColor
                                 );

                        
                        
                        
                    }
                    
				
                }
            }
            
            // en dessous de la limite
            else
            {
                for(j=0; j<nbLed; j++)
				{
                    sys_vgui(".x%lx.c itemconfigure %lxLed%d%d -outline #%6.6x\n",
                             canvas,
                             x,
                             ii,
                             j,
                             x->f_colorBaseLed
                             );
                }
                
            }
	
		
        }
    }
}

static void hoaMeter_draw_update(t_hoaMeter *x, t_glist *glist)
{
    if(glist_isvisible(glist))
    {
        hoaMeter_update_vector(x, glist);
        hoaMeter_update_meter(x, glist);
    }
    
}


void hoaMeter_draw_new(t_hoaMeter *x, t_glist *glist)
{
    hoaMeter_speakerPosProcess(x);
    
    int xpos=text_xpix(&x->x_gui.x_obj, glist);
    int ypos=text_ypix(&x->x_gui.x_obj, glist);


    t_canvas *canvas=glist_getcanvas(glist);

    sys_vgui(".x%lx.c create rectangle %d %d %d %d -fill #%6.6x -outline #%6.6x -tags %lxBASE\n",
             canvas,
             xpos,
             ypos,
             xpos + x->x_gui.x_w,
             ypos + x->x_gui.x_h,
             x->x_gui.x_bcol,
             x->x_gui.x_fsf.x_selected?IEM_GUI_COLOR_SELECTED:IEM_GUI_COLOR_NORMAL,
             x);
    
    hoaMeter_draw_skelton(x, glist);
    hoaMeter_draw_new_vector(x, glist);
    
    // INLET
    sys_vgui(".x%lx.c create rectangle %d %d %d %d -tags %xINLET -fill #FFFFFF\n",
             canvas,
             xpos,
             ypos,
             xpos + 8,
             ypos + 3,
             x
             );

}

void hoaMeter_draw_move(t_hoaMeter *x, t_glist *glist)
{


    int i,j;
	long nLoudSpeak = x->f_numberOfLoudspeakers;
    double deg1, deg2, rotateAngle, ledContainerSize, ledStroke, ledMargin, ledOffset;
    int _x,_y,_X,_Y;
    
    
    deg1 = degtorad(90);
	ledContainerSize = x->f_rayonExt - x->f_rayonInt - (x->f_strokeWidth*4);
	ledOffset = ledContainerSize / (x->f_numleds+1);
	ledStroke = ledOffset * 0.75;
	ledMargin = ledOffset * 0.25;
    
    int xpos=text_xpix(&x->x_gui.x_obj, glist);
    int ypos=text_ypix(&x->x_gui.x_obj, glist);

    t_canvas *canvas=glist_getcanvas(glist);
    
    sys_vgui(".x%lx.c coords %lxBASE %d %d %d %d\n",
             canvas, x, xpos, ypos, xpos + x->x_gui.x_w, ypos + x->x_gui.x_h);
    
    int r= x->f_rayonExt;
    sys_vgui(".x%lx.c coords %lxCIRCLEEXT %d %d %d %d \n",
             canvas,
             x,
             xpos+(x->x_gui.x_w)/2-r,
             ypos+(x->x_gui.x_h)/2-r,
             xpos+(x->x_gui.x_w)/2+r,
             ypos+(x->x_gui.x_h)/2+r
             );
    r= x->f_rayonInt;
    sys_vgui(".x%lx.c coords %lxCIRCLEINT %d %d %d %d  \n",
             canvas,
             x,
             xpos+(x->x_gui.x_w)/2-r,
             ypos+(x->x_gui.x_h)/2-r,
             xpos+(x->x_gui.x_w)/2+r,
             ypos+(x->x_gui.x_h)/2+r
             );
    
    for(i=0; i<nLoudSpeak; i++)
    {
        deg2 = degtorad(90+(x->f_speakerWidth[i]));
        rotateAngle = x->f_speakerRealAngle[i] - (x->f_speakerWidth[i]*0.5) + x->f_offsetOfLoudspeakers;
        if (!x->f_speakers_dir_of_rotation)
        {
            rotateAngle += x->f_speakerWidth[i];
            rotateAngle *= -1;
        }
        
        for( j=0; j < x->f_numleds; j++ )
        {
            double radius = x->f_rayonExt-(j*ledOffset) - ledMargin*2 - x->f_strokeWidth*2;
            
            _x = (int) xpos+(x->x_gui.x_w)/2 -radius;
            _y = (int) ypos+(x->x_gui.x_h)/2 -radius;
            
            _X = (int)xpos+(x->x_gui.x_w)/2+radius;
            _Y = (int) ypos+(x->x_gui.x_h)/2+radius;
            
            
            
            sys_vgui(".x%lx.c coords %lxLed%d%d  %d %d %d %d  \n",
                     canvas,
                     x,
                     i,
                     j,
                     _x,
                     _y,
                     _X,
                     _Y
                    );

        }
        // coords sur cercle intérieur
        _x = (int) (x->f_rayonInt*cos( degtorad(rotateAngle)));
        _y = (int) (x->f_rayonInt*sin( degtorad(rotateAngle)));
        
        // coords sur cercle extérieur
        _X = (int) (x->f_rayonExt*cos( degtorad(rotateAngle)));
        _Y = (int) (x->f_rayonExt*sin( degtorad(rotateAngle)));
        
        // separateurs
        sys_vgui(".x%lx.c coords %lxSEPARATOR%d %d %d %d %d \n",
                 canvas,
                 x,
                 i,
                 (int) xpos+(x->x_gui.x_w)/2 + _x,
                 (int) ypos+(x->x_gui.x_h)/2 + _y,
                 xpos+(x->x_gui.x_w)/2+_X,
                 ypos+(x->x_gui.x_h)/2+_Y
                 );
    }
    
    // INLET
    sys_vgui(".x%lx.c coords %xINLET %d %d %d %d \n",
             canvas,
             x,
             xpos,
             ypos,
             xpos + 8,
             ypos + 3
             );
    

}

void hoaMeter_draw_erase(t_hoaMeter* x, t_glist* glist)
{
    
    t_canvas *canvas=glist_getcanvas(glist);
    
    sys_vgui(".x%lx.c delete %lxBASE\n", canvas, x);
    sys_vgui(".x%lx.c delete %lxCIRCLEEXT\n", canvas, x);
    sys_vgui(".x%lx.c delete %lxCIRCLEINT\n", canvas, x);
    sys_vgui(".x%lx.c delete %lxINLET\n", canvas, x);
    sys_vgui(".x%lx.c delete %lxARROW \n", canvas, x);
    
    
    int i,j;
	long nLoudSpeak = x->f_numberOfLoudspeakers;
    
    for(i=0; i<nLoudSpeak; i++)
    {
        for( j=0; j < x->f_numleds; j++ )
                sys_vgui(".x%lx.c delete %lxLed%d%d \n", canvas, x,i,j);

        sys_vgui(".x%lx.c delete %lxSEPARATOR%d \n", canvas, x,i);
        
    }
        
    
}

void hoaMeter_draw_select(t_hoaMeter* x, t_glist* glist)
{
    t_canvas *canvas=glist_getcanvas(glist);
    
    
    if(x->x_gui.x_fsf.x_selected)
    {
        sys_vgui(".x%lx.c itemconfigure %lxBASE -outline #%6.6x\n", canvas, x, IEM_GUI_COLOR_SELECTED);
    }
    else
    {
        sys_vgui(".x%lx.c itemconfigure %lxBASE -outline #%6.6x\n", canvas, x, IEM_GUI_COLOR_NORMAL);
    }
}

void hoaMeter_draw(t_hoaMeter *x, t_glist *glist, int mode)
{

    
	x->f_centerX = x->x_gui.x_w/2;
    x->f_centerY = x->x_gui.x_h/2;
	
	x->f_metersize=0.8;
	x->f_rayonMax = x->x_gui.x_w * .5;
	if(x->x_gui.x_w > x->x_gui.x_h)
		x->f_rayonMax = x->x_gui.x_h * .5;
	
	x->f_fontsize = (x->f_rayonMax / 14.) - 1.;
	x->f_rayonCircle = x->f_rayonMax / 32;
	
	x->f_strokeWidth = 2;
	x->f_rayonExt = x->f_rayonMax - (x->f_strokeWidth*0.5) - 2;
	x->f_rayonInt = x->f_rayonExt*(1 - x->f_metersize);
	

    if(mode == IEM_GUI_DRAW_MODE_UPDATE)
        hoaMeter_draw_update(x, glist);
    else if(mode == IEM_GUI_DRAW_MODE_MOVE)
        hoaMeter_draw_move(x, glist);
    else if(mode == IEM_GUI_DRAW_MODE_NEW)
        hoaMeter_draw_new(x, glist);
    else if(mode == IEM_GUI_DRAW_MODE_SELECT)
        hoaMeter_draw_select(x, glist);
    else if(mode == IEM_GUI_DRAW_MODE_ERASE)
        hoaMeter_draw_erase(x, glist);
}

/* ------------------------ cnv widgetbehaviour----------------------------- */

static void hoaMeter_getrect(t_gobj *z, t_glist *glist, int *xp1, int *yp1, int *xp2, int *yp2)
{
    t_hoaMeter *x = (t_hoaMeter *)z;
    
    *xp1 = text_xpix(&x->x_gui.x_obj, glist);
    *yp1 = text_ypix(&x->x_gui.x_obj, glist);
    *xp2 = *xp1 + x->x_gui.x_w;
    *yp2 = *yp1 + x->x_gui.x_h;
}

/* ******** ******** ******** ******** ******** ******** ******** ******** ******** ******** */

//                                  COMPUTATION

/* ******** ******** ******** ******** ******** ******** ******** ******** ******** ******** */

// dsp notification
void hoaMeter_dsp(t_hoaMeter *x, t_signal **sp)
{

}

double degtorad(double degree)
{
	return degree / (double)(180. / M_PI);
}

double radtodeg(double rad)
{
	return rad * (double)(180. / M_PI);
}

void meter_tick(t_hoaMeter *x)
{
	int i;
	double sum = 0., square = 0.;
	
	x->f_energyVectorX = x->f_energyVectorY = 0.;
	for(i = 0; i < x->f_numberOfLoudspeakers; i++)
	{
		x->f_energyOfLoudspeakers[i] = 20. * log10(fabs(x->f_amplitudeOfLoudspeakers[i]));
		square = x->f_amplitudeOfLoudspeakers[i] * x->f_amplitudeOfLoudspeakers[i];
		
		x->f_energyVectorX += square * x->f_abscisseOfLoudspeakers[i];
		x->f_energyVectorY += square * x->f_ordonneOfLoudspeakers[i];
		sum += square;
		
		x->f_amplitudeOfLoudspeakers[i] = 0.0;
		
	}
	if (sum == 0.)
	{
		x->f_energyVectorX = 0.;
		x->f_energyVectorY = 0.;
	}
	else
	{
		x->f_energyVectorX /= sum;
		x->f_energyVectorY /= sum;
	}

    
    (*x->x_gui.x_draw)(x, x->x_gui.x_glist, IEM_GUI_DRAW_MODE_UPDATE);
}

static void bubblesort(float array[], int size)
{
	int tmp ,i,j;
	for(i = 0;i < size ; i++)
		for(j=0;j < size;j++)
            if(array[i] < array[j])
            {
                tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
}

static void hoaMeter_speakerPosProcess(t_hoaMeter *x)
{
	int i, nLoudSpeak;
	double curAngle, prevAngle, nextAngle, prevPortion, nextPortion;
	nLoudSpeak = x->f_numberOfLoudspeakers;
	x->f_speakerWidthMax = 0.;
	for(i=0; i < nLoudSpeak; i++)
	{
		curAngle = x->f_speakerAngles[i];
		if (i != 0) prevAngle = x->f_speakerAngles[i-1];
		else prevAngle = x->f_speakerAngles[nLoudSpeak-1];
		if (i != nLoudSpeak-1) nextAngle = x->f_speakerAngles[i+1];
		else nextAngle = x->f_speakerAngles[0];
		
		prevPortion = (curAngle - prevAngle);
		nextPortion = (nextAngle - curAngle);
		
		if (nextPortion < 0.) nextPortion += 360.;
		if (prevPortion < 0.) prevPortion += 360.;
		
		x->f_speakerWidth[i] = (prevPortion + nextPortion)*0.5;
		if (x->f_speakerWidth[i] > x->f_speakerWidthMax) x->f_speakerWidthMax = x->f_speakerWidth[i];
		x->f_speakerRealAngle[i] = (curAngle - prevPortion*0.5) + x->f_speakerWidth[i]*0.5;
		x->f_abscisseOfLoudspeakers[i] = cos(degtorad(x->f_speakerRealAngle[i]));
		x->f_ordonneOfLoudspeakers[i] = sin(degtorad(x->f_speakerRealAngle[i]));
	}
}


static int hoaMeter_speakerAngles_set(t_hoaMeter *x,  long ac, t_atom *av)
{
	float val;
	int i;
	int defaultAngle = 0;
	x->f_nSpeakerAngles = x->f_numberOfLoudspeakers;
	
    if (ac && av)
    {
        for (i = 0; i < x->f_nSpeakerAngles; i++)
		{
			if (defaultAngle == 0 || i < ac)
			{
				val = atom_getfloat(av + i);
				if (val > 360.)
					val = 0.;

				else if (val < 0.)
                {
					if (val < -360.) val = -360.;
					val += 360.;
				}
				x->f_speakerAngles[i] = val;
			}
			else
				x->f_speakerAngles[i] = 360. / x->f_numberOfLoudspeakers * i;

			if (x->f_speakerAngles[i] == 360.) x->f_speakerAngles[i] = 0.;
        }
    }

    // default
    else
    {
        for (i = 0; i < x->f_nSpeakerAngles; i++)
            x->f_speakerAngles[i] = 360. / x->f_numberOfLoudspeakers * i;
    }
    
    
	bubblesort(x->f_speakerAngles, x->f_nSpeakerAngles);
	hoaMeter_speakerPosProcess(x);
    
    
    return 0;
}

static void hoaMeter_list(t_hoaMeter *x, t_symbol *s, int argc, t_atom *argv)
{
    if (argc!=x->f_numberOfLoudspeakers)
    {
        post("list size error");
        return;
    }
    else
    {

        int i;
        double max;
        double val;
        for(i = 0; i < x->f_numberOfLoudspeakers; i++)
        {
            max = x->f_amplitudeOfLoudspeakers[i];
            val = (double)atom_getfloat( argv+i);
            if (fabs(val)>fabs(max))
            {
                x->f_amplitudeOfLoudspeakers[i] = val;
            }
        }
	

        meter_tick(x);

    }

    
}
/* ******** ******** ******** ******** ******** ******** ******** ******** ******** ******** */

//                                  SETUP

/* ******** ******** ******** ******** ******** ******** ******** ******** ******** ******** */

static void *hoaMeter_new(t_symbol *s, int argc, t_atom *argv)
{
    t_hoaMeter *x = (t_hoaMeter *)pd_new(hoaMeter_class);
    int i;
    
    if (x)
    {
        int nbSpeak=8;
     
        if((argc>=1) && ((argv)->a_type==A_FLOAT))
            nbSpeak=atom_getint(argv);
        
        x->x_gui.x_bcol = 9211020;// my_iemgui_color_hex[IEM_GUI_COLNR_ML_GREY];
        x->x_gui.x_fcol = my_iemgui_color_hex[IEM_GUI_COLNR_D_ORANGE];
        x->x_gui.x_w = 400;//(int)(x->x_room_y*x->x_cnvrt_roomlx2pixh + 0.49999f);
        x->x_gui.x_h = 400;//(int)(x->x_room_x*x->x_cnvrt_roomlx2pixh + 0.49999f);
        x->x_gui.x_draw = (t_iemfunptr)hoaMeter_draw;
        x->x_gui.x_glist = (t_glist *)canvas_getcurrent();

        
        // fond disque : 6710886
        x->f_colorBaseLed    =7500402;//my_iemgui_color_hex[IEM_GUI_COLNR_D_GREY];
        x->f_colorColdSignal =39168;    //my_iemgui_color_hex[IEM_GUI_COLNR_D_GREEN];
        x->f_colorTepidSignal=10074624; //my_iemgui_color_hex[IEM_GUI_COLNR_GREEN];
        x->f_colorWarmSignal =14276864; //my_iemgui_color_hex[IEM_GUI_COLNR_L_GREEN];
        x->f_colorHotSignal  =16750848;//my_iemgui_color_hex[IEM_GUI_COLNR_ORANGE];

        x->f_numberOfLoudspeakers = nbSpeak;


        x->f_energyOfLoudspeakers = (double *)getbytes(x->f_numberOfLoudspeakers * sizeof(double));
        x->f_amplitudeOfLoudspeakers = (double *)getbytes(x->f_numberOfLoudspeakers * sizeof(double));
        x->f_abscisseOfLoudspeakers = (double *)getbytes(x->f_numberOfLoudspeakers * sizeof(double));
        x->f_ordonneOfLoudspeakers = (double *)getbytes(x->f_numberOfLoudspeakers * sizeof(double));



        for(i = 0; i < x->f_numberOfLoudspeakers; i++)
        {
            x->f_energyOfLoudspeakers[i] = 0.00001;
            x->f_amplitudeOfLoudspeakers[i] = 0.000001;
            x->f_abscisseOfLoudspeakers[i] = cos(degtorad(x->f_speakerAngles[i]));
            x->f_ordonneOfLoudspeakers[i] = sin(degtorad(x->f_speakerAngles[i]));
        }


        x->f_startclock = 0;
        x->f_drawmeter = 0;
        



        x->f_dbperled=3;
        x->f_numleds = 12;
        x->f_nhotleds = 3;
        x->f_ntepidleds=3;
        x->f_nwarmleds=3;
        
        
        
        hoaMeter_speakerAngles_set(x, 0, NULL);
        
        
    
    }
    return (x);
}

static void hoaMeter_free(t_hoaMeter *x)
{
    gfxstub_deleteforkey(x);

    freebytes(x->f_energyOfLoudspeakers, x->f_numberOfLoudspeakers * sizeof(double));
	freebytes(x->f_amplitudeOfLoudspeakers, x->f_numberOfLoudspeakers * sizeof(double));
	freebytes(x->f_abscisseOfLoudspeakers, x->f_numberOfLoudspeakers * sizeof(double));
	freebytes(x->f_ordonneOfLoudspeakers, x->f_numberOfLoudspeakers * sizeof(double));
}

extern "C" void setup_hoa0x2emeter(void)
{
    hoaMeter_class = class_new(gensym("hoa.meter"),
                                     (t_newmethod)hoaMeter_new,
                                     (t_method)hoaMeter_free,
                                     sizeof(t_hoaMeter),
                                     0,
                                     A_GIMME,
                                     0
                                     );
    
    class_addmethod(hoaMeter_class, (t_method)hoaMeter_list, gensym("list"), A_GIMME,0);

    
    
    hoaMeter_widgetbehavior.w_getrectfn = hoaMeter_getrect;
    hoaMeter_widgetbehavior.w_displacefn = iemgui_displace;
    hoaMeter_widgetbehavior.w_selectfn = iemgui_select;
    hoaMeter_widgetbehavior.w_activatefn = NULL;
    hoaMeter_widgetbehavior.w_deletefn = iemgui_delete;
    hoaMeter_widgetbehavior.w_visfn = iemgui_vis;
    

    

#if defined(PD_MAJOR_VERSION) && (PD_MINOR_VERSION >= 37)
    //class_setsavefn(hoaMeter_class, hoaMeter_save);
#else
    hoaMeter_widgetbehavior.w_propertiesfn = NULL;
    hoaMeter_widgetbehavior.w_savefn = NULL;//hoaMeter_save;
#endif

    class_setwidget(hoaMeter_class, &hoaMeter_widgetbehavior);
    //  class_sethelpsymbol(room_sim_2d_class, gensym("iemhelp2/help-room_sim_2d"));
}



