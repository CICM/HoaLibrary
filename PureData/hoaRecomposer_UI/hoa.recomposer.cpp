//
//  hoa.recomposer.cpp
//  hoa.recomposer_UI
//
//  Created by Manuel Deneu on 31/07/13.
//
//

#pragma GCC diagnostic ignored "-Wwrite-strings"

extern "C"
{
#include "../m_pd.h"
#include "../iemlib.h"
#include "../iemgui.h"
#include "../g_canvas.h"
#include "../g_all_guis.h"

    
}
#include "../PdCompliant.h"
#include "../../Sources/HoaLibrary.h"


#define MAX_MICS 64
#define MIN_MICS 3
#define DEF_MICS 8




t_widgetbehavior hoaRecomposer_widgetbehavior;

typedef struct  _HoaRecomposerUI
{
    t_iemgui  x_gui;
    
    int       x_pos_x;
    int       x_pos_y;
    
    // colors
    
	t_jrgba		f_colorBackground;
    t_jrgba		f_colorBorder;
    t_jrgba		f_colorInnerCircle;
	t_jrgba		f_colorMic;
    t_jrgba		f_colorMicSelected;
	t_jrgba		f_color_selection;
    t_jrgba		f_colorHarmonics;
    t_jrgba     f_fisheyecolor;
    t_jrgba     f_colorTextMic;
    t_jrgba     f_colorTextMicSelected;
    
    // microphones
    AmbisonicVirtualMicUIManager* f_mics;
    int			f_numberOfMic;
    int         f_showFishEye;
    double      f_fisheyeAngle;
    
    // mouse
    t_pt        f_rectSelectionBegin;
    t_rect      f_rectSelection;
    bool        f_rectSelectionExist;
	t_pt		f_last_mouseMove;
    int         f_last_mouseMoveOverMic;
    t_pt		f_last_mouseDown;
    int         f_last_mouseDownOverMic;
    t_pt		f_last_mouseUp;
    int         f_last_mouseUpOverMic;
    t_pt		f_last_mouseDrag;
    double		f_last_mouseDragAngle;
    double      f_last_mouseDragRadius;
    
    // draw utility

    int f_micRadius;
    
    // outlets
	t_outlet		*f_out;
    t_outlet		*f_outlet_infos;
    
} t_HoaRecomposerUI;

static t_class *HoaRecomposerUI_class;

/* ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** */
/* Interface */

static void hoaRecomposer_draw_update(t_HoaRecomposerUI *x, t_glist *glist);
static void hoaRecomposer_draw_move(t_HoaRecomposerUI *x, t_glist *glist);
static void hoaRecomposer_draw_new(t_HoaRecomposerUI *x, t_glist *glist);
static void hoaRecomposer_draw_select(t_HoaRecomposerUI *x, t_glist *glist);
static void hoaRecomposer_draw_erase(t_HoaRecomposerUI *x, t_glist *glist);


/* ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** */
/* Implementation */


/* ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** */
//                  DRAW
/* ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** */
static void draw_fishEye(t_HoaRecomposerUI *x,  t_glist *glist)
{
    int xpos=text_xpix(&x->x_gui.x_obj, glist);
    int ypos=text_ypix(&x->x_gui.x_obj, glist);
    t_canvas *canvas=glist_getcanvas(glist);
    
    t_pt cartFisheyeDest,
         cart;
    
    double micAngle, w;
    w = x->x_gui.x_w;
    
    double dashes[2] = {4, 4};

	if (x->f_showFishEye)
    {
        
//        jgraphics_set_source_jrgba(g, &x->f_fisheyecolor);
//        jgraphics_set_line_width(g, 1);
//        jgraphics_set_dash(g, dashes, 2, 0);

        cartFisheyeDest.x = Tools::abscisse(x->f_micRadius, x->f_fisheyeAngle);
        cartFisheyeDest.y = Tools::ordinate(x->f_micRadius, x->f_fisheyeAngle);
        cartFisheyeDest.x = (cartFisheyeDest.x + (w*0.5));
        cartFisheyeDest.y = ( (w - cartFisheyeDest.y) - (w*0.5) );
        
        for (int i=0; i < x->f_numberOfMic; i++)
        {
            if (x->f_mics->isSelected(i))
            {
                micAngle = x->f_mics->getAngleInRadian(i);
                cart.x = (int) Tools::abscisse(x->f_micRadius, micAngle + CICM_PI2);
                cart.y = (int)  Tools::ordinate(x->f_micRadius, micAngle + CICM_PI2);
                cart.x = (int) (cart.x + (w*0.5));
                cart.y = (int) ( (w - cart.y) - (w*0.5) );
                post("%i %i %i %i",
                                    cart.x,
                                    cart.y,
                                    cartFisheyeDest.x,
                                    cartFisheyeDest.y);
                // jgraphics_move_to(g, cartFisheyeDest.x, cartFisheyeDest.y);
                // jgraphics_line_to(g, cart.x, cart.y);
                
                sys_vgui(".x%lx.c create line %d %d %d %d -fill #%6.6x -tag %lxFISH%d \n",
                         canvas,
                         xpos+cartFisheyeDest.x,
                         ypos+cartFisheyeDest.x,
                         xpos+cart.x,
                         ypos+cart.y,
                         getTkColorFromRGB(x->f_fisheyecolor),
                         x,
                         i
                         );
                
                
                
                
//                jgraphics_stroke(g);
//                jgraphics_arc(g, cart.x, cart.y, 2, 0, CICM_2PI);
//                jgraphics_fill(g);
            }
        }
        
//        jgraphics_arc(g, cartFisheyeDest.x, cartFisheyeDest.y, 4, 0, CICM_2PI);
//        jgraphics_fill(g);
        
		
	}
}

static void draw_background(t_HoaRecomposerUI *x,  t_glist *glist)
{

    int xpos=text_xpix(&x->x_gui.x_obj, glist);
    int ypos=text_ypix(&x->x_gui.x_obj, glist);
    t_canvas *canvas=glist_getcanvas(glist);
    
	double w = x->x_gui.x_w;
    
    t_jrgba HpMarkerColor = {0.2,0.2,0.2,1};
    int colorFactor;
    t_jrgba shadLight, shadDark;
    int hpSize = (w / 20) * 0.5;

    double mic_angle = CICM_2PI / x->f_mics->getNumberOfMics();
    
    shadLight = shadDark = x->f_colorInnerCircle;
    shadDark.red = Tools::clip_min(shadDark.red - 0.05);
    shadDark.green = Tools::clip_min(shadDark.green - 0.05);
    shadDark.blue = Tools::clip_min(shadDark.blue - 0.05);
    
    shadLight.red = Tools::clip_max(shadLight.red + 0.05, 1.);
    shadLight.green = Tools::clip_max(shadLight.green + 0.05, 1.);
    shadLight.blue = Tools::clip_max(shadLight.blue + 0.05, 1.);
    
    HpMarkerColor = x->f_colorInnerCircle;
    colorFactor = (x->f_colorInnerCircle.red + x->f_colorInnerCircle.green + x->f_colorInnerCircle.blue > 1.5) ? -1 : 1;
    HpMarkerColor.red = Tools::clip(HpMarkerColor.red + (0.2*colorFactor), 0., 1.);
    HpMarkerColor.green = Tools::clip(HpMarkerColor.green + (0.2*colorFactor), 0., 1.);
    HpMarkerColor.blue = Tools::clip(HpMarkerColor.blue + (0.2*colorFactor), 0., 1.);
    
        
    //jgraphics_set_line_cap(g, JGRAPHICS_LINE_CAP_ROUND);
    //jgraphics_set_source_jrgba(g, &x->f_colorInnerCircle);
	//jgraphics_arc(g, w*0.5, w*0.5, x->f_micRadius,  0., JGRAPHICS_2PI);
	//jgraphics_fill(g);
    
    sys_vgui(".x%lx.c create oval %d %d %d %d -fill #%6.6x -outline #%6.6x -tag %lxCIRCLE1 \n",
             canvas,
             xpos+(x->x_gui.x_w)/2-x->f_micRadius,
             ypos+(x->x_gui.x_h)/2-x->f_micRadius,
             xpos+(x->x_gui.x_w)/2+x->f_micRadius,
             ypos+(x->x_gui.x_h)/2+x->f_micRadius,
             getTkColorFromRGB(x->f_colorInnerCircle),
             getTkColorFromRGB(x->f_colorInnerCircle),             
             x
             );

    
/*
    jgraphics_matrix_init(&transform, 1, 0, 0, -1, w*0.5, w*0.5);
    jgraphics_set_matrix(g, &transform);
    jgraphics_set_source_jrgba(g, &HpMarkerColor);
    jgraphics_set_line_width(g, 1.);
*/        
    for (int i=0; i < x->f_mics->getNumberOfMics(); i++)
    {

        float angle = mic_angle*i;
        int translate = x->f_micRadius;

        int cX = xpos+(x->x_gui.x_w)/2 +translate*cos(angle);
        int cY = ypos+(x->x_gui.x_h)/2 +translate*sin(angle);
        sys_vgui(".x%lx.c create oval %d %d %d %d -fill #%6.6x -outline #%6.6x -tag %lxMIC%d \n",
                 canvas,
                 cX-hpSize,
                 cY-hpSize,
                 cX+hpSize,
                 cY+hpSize,
                 getTkColorFromRGB(x->f_colorInnerCircle),
                 getTkColorFromRGB(x->f_colorInnerCircle),                 
                 x,
                 i
                 );
        /*
        sys_vgui(".x%lx.c create line %d %d %d %d -fill #%6.6x -tag %lxMIC20%d \n",
                 canvas,
                 cX,
                 cY-hpSize,
                 cX,
                 cY+hpSize,
                 getTkColorFromRGB(HpMarkerColor),
                 x,
                 i
                 );
         */
    }

    // center crosshair
    // tags CROSS00, CROSS01,CROSS10, CROSS11,
    
    for (int i=0; i<2; i++)
    {
        t_jrgba color = (i==0? shadLight : shadDark);
        
        sys_vgui(".x%lx.c create line %d %d %d %d -fill #%6.6x -tag %lxCROSS0%d \n",
                 canvas,
                 xpos+(x->x_gui.x_w)/2 + 5,
                 ypos+(x->x_gui.x_h)/2 + 5 +i,
                 xpos+(x->x_gui.x_w)/2 - 5,
                 ypos+(x->x_gui.x_h)/2 - 5 +i,
                 getTkColorFromRGB(color),
                 x,
                 i
                 );

        sys_vgui(".x%lx.c create line %d %d %d %d -fill #%6.6x -tag %lxCROSS1%d \n",
                 canvas,
                 xpos+(x->x_gui.x_w)/2 - 5,
                 ypos+(x->x_gui.x_h)/2 + 5 +i,
                 xpos+(x->x_gui.x_w)/2 + 5,
                 ypos+(x->x_gui.x_h)/2 - 5 +i,
                 getTkColorFromRGB(color),
                 x,
                 i
                 );
        

    }
		


}

static void hoaRecomposer_draw(t_HoaRecomposerUI *x, t_glist *glist, int mode)
{
    if(mode == IEM_GUI_DRAW_MODE_UPDATE)
        hoaRecomposer_draw_update(x, glist);
    else if(mode == IEM_GUI_DRAW_MODE_MOVE)
        hoaRecomposer_draw_move(x, glist);
    else if(mode == IEM_GUI_DRAW_MODE_NEW)
        hoaRecomposer_draw_new(x, glist);
    else if(mode == IEM_GUI_DRAW_MODE_SELECT)
        hoaRecomposer_draw_select(x, glist);
    else if(mode == IEM_GUI_DRAW_MODE_ERASE)
        hoaRecomposer_draw_erase(x, glist);
}

static void hoaRecomposer_draw_update(t_HoaRecomposerUI *x, t_glist *glist)
{
    
}


static void hoaRecomposer_draw_move(t_HoaRecomposerUI *x, t_glist *glist)
{
    int xpos=text_xpix(&x->x_gui.x_obj, glist);
    int ypos=text_ypix(&x->x_gui.x_obj, glist);
    t_canvas *canvas=glist_getcanvas(glist);
    
    sys_vgui(".x%lx.c coords %lxBASE %d %d %d %d\n",
             canvas,
             x,
             xpos,
             ypos,
             xpos + x->x_gui.x_w,
             ypos + x->x_gui.x_h
             );
    
    // INLETS
    sys_vgui(".x%lx.c coords %xril %d %d %d %d\n",
             canvas,
             x,
             xpos,
             ypos,
             xpos + 8,
             ypos + 3);
    // OUTLETS
    sys_vgui(".x%lx.c coords %xrol1 %d %d %d %d \n",
             canvas,
             x,
             xpos + 0,
             ypos+x->x_gui.x_h -3,
             xpos + 8,
             ypos+x->x_gui.x_h
             );
    
    sys_vgui(".x%lx.c coords %lxCIRCLE1 %d %d %d %d  \n",
             canvas,
             x,
             xpos+(x->x_gui.x_w)/2-x->f_micRadius,
             ypos+(x->x_gui.x_h)/2-x->f_micRadius,
             xpos+(x->x_gui.x_w)/2+x->f_micRadius,
             ypos+(x->x_gui.x_h)/2+x->f_micRadius
             );
    
    double mic_angle = CICM_2PI / x->f_mics->getNumberOfMics();
    int hpSize = (x->x_gui.x_w / 20) * 0.5;
    for (int i=0; i < x->f_mics->getNumberOfMics(); i++)
    {
        float angle = mic_angle*i;
        int translate = x->f_micRadius;

        int cX = xpos+(x->x_gui.x_w)/2 +translate*cos(angle);
        int cY = ypos+(x->x_gui.x_h)/2 +translate*sin(angle);
        sys_vgui(".x%lx.c coords %lxMIC%d %d %d %d %d  \n",
                 canvas,
                 x,
                 i,
                 cX-hpSize,
                 cY-hpSize,
                 cX+hpSize,
                 cY+hpSize
                 );
    }

    
    for (int i=0; i<2; i++)
    {
    
        
        sys_vgui(".x%lx.c coords %lxCROSS0%d %d %d %d %d \n",
                 canvas,
                 x,
                 i,
                 xpos+(x->x_gui.x_w)/2 + 5,
                 ypos+(x->x_gui.x_h)/2 + 5 +i,
                 xpos+(x->x_gui.x_w)/2 - 5,
                 ypos+(x->x_gui.x_h)/2 - 5 +i
                 );
        
        sys_vgui(".x%lx.c coords %lxCROSS1%d %d %d %d %d  \n",
                 canvas,
                 x,
                 i,
                 xpos+(x->x_gui.x_w)/2 - 5,
                 ypos+(x->x_gui.x_h)/2 + 5 +i,
                 xpos+(x->x_gui.x_w)/2 + 5,
                 ypos+(x->x_gui.x_h)/2 - 5 +i
                 );
    }

    
    

}

static void hoaRecomposer_draw_new(t_HoaRecomposerUI *x, t_glist *glist)
{
    int xpos=text_xpix(&x->x_gui.x_obj, glist);
    int ypos=text_ypix(&x->x_gui.x_obj, glist);
    
    
    t_canvas *canvas=glist_getcanvas(glist);
    

    
    
    sys_vgui(".x%lx.c create rectangle %d %d %d %d -fill white -outline #%6.6x -fill #%6.6x -tags %lxBASE\n",
             canvas,
             xpos,
             ypos,
             xpos + x->x_gui.x_w,
             ypos + x->x_gui.x_h,
             getTkColorFromRGB( x->f_colorBorder),
             getTkColorFromRGB( x->f_colorBackground),
             x);
    
    
    // INLET
    sys_vgui(".x%lx.c create rectangle %d %d %d %d -tags %xril -fill #FFFFFF\n",
             canvas,
             xpos,
             ypos,
             xpos + 8,
             ypos + 3,
             x
             );
    
    // OUTLET
    sys_vgui(".x%lx.c create rectangle %d %d %d %d -tags %xrol1 -fill #FFFFFF\n",
             canvas,
             xpos + 0,
             ypos+x->x_gui.x_h -3,
             xpos + 8,
             ypos+x->x_gui.x_h,
             x
             );
    
    draw_background(x, glist);
    draw_fishEye(x, glist); 
}

static void hoaRecomposer_draw_select(t_HoaRecomposerUI *x, t_glist *glist)
{
    t_canvas *canvas=glist_getcanvas(glist);
    
    
    
    if(x->x_gui.x_fsf.x_selected)
    {
        sys_vgui(".x%lx.c itemconfigure %lxBASE -outline #%6.6x\n",
                 canvas,
                 x,
                 IEM_GUI_COLOR_SELECTED
                 );
    }
    else
    {
        sys_vgui(".x%lx.c itemconfigure %lxBASE -outline #%6.6x\n",
                 canvas,
                 x,
                 IEM_GUI_COLOR_NORMAL
                 );
    }
}

static void hoaRecomposer_draw_erase(t_HoaRecomposerUI *x, t_glist *glist)
{
    t_canvas *canvas=glist_getcanvas(glist);
    sys_vgui(".x%lx.c delete %lxBASE\n", canvas, x);
    sys_vgui(".x%lx.c delete %xril\n", canvas, x);
    sys_vgui(".x%lx.c delete %xrol1\n", canvas, x);
    sys_vgui(".x%lx.c delete %xCIRCLE1\n", canvas, x);
    
    for (int i=0; i < x->f_mics->getNumberOfMics(); i++)
    {
        sys_vgui(".x%lx.c delete %lxMIC%d\n", canvas, x,i);
    }
    
    for (int i=0; i<2; i++)
    {
        sys_vgui(".x%lx.c delete %lxCROSS0%d \n",
                 canvas,
                 x,
                 i
                 );
        
        sys_vgui(".x%lx.c delete %lxCROSS1%d \n",
                 canvas,
                 x,
                 i
                 );
    }

}

/* ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** */
//                  INTERACTIONS
/* ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** */


static void hoaRecomposer_motion(t_HoaRecomposerUI *x, t_floatarg dx, t_floatarg dy)
{
    
}

static int hoaRecomposer_newclick(t_gobj *z, struct _glist *glist, int xpix, int ypix, int shift, int alt, int dbl, int doit)
{
    t_HoaRecomposerUI *x=(t_HoaRecomposerUI*) z;
    

    
    return (1);
}

static void hoaRecomposer_click(t_HoaRecomposerUI *x, t_floatarg xpos, t_floatarg ypos,
                           t_floatarg shift, t_floatarg ctrl, t_floatarg alt)
{
    

    
    glist_grab(x->x_gui.x_glist, &x->x_gui.x_obj.te_g,
               (t_glistmotionfn)hoaRecomposer_motion, 0, xpos, ypos);
}

static void hoaRecomposer_getrect(t_gobj *z, t_glist *glist, int *xp1, int *yp1, int *xp2, int *yp2)
{
    t_HoaRecomposerUI *x = (t_HoaRecomposerUI *)z;
    
    *xp1 = text_xpix(&x->x_gui.x_obj, glist);
    *yp1 = text_ypix(&x->x_gui.x_obj, glist);
    *xp2 = *xp1 + x->x_gui.x_w;
    *yp2 = *yp1 + x->x_gui.x_h;
}

static void hoaRecomposer_save(t_gobj *z, t_binbuf *b)
{
    t_HoaRecomposerUI *x = (t_HoaRecomposerUI *)z;
    int i;
    
    binbuf_addv(b, "ssiis", gensym("#X"),gensym("obj"),
                (t_int)x->x_gui.x_obj.te_xpix, (t_int)x->x_gui.x_obj.te_ypix,
                atom_getsymbol(binbuf_getvec(x->x_gui.x_obj.te_binbuf))
                );
    
   
    binbuf_addv(b, ";");
}


/* ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** */
//                  INIT
/* ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** */

static void *hoaRecomposer_new(t_symbol *s, int argc, t_atom *argv)
{
    t_HoaRecomposerUI *x = (t_HoaRecomposerUI *)pd_new(HoaRecomposerUI_class);
    if (x)
    {
        x->f_outlet_infos = outlet_new(&x->x_gui.x_obj, &s_list);
        x->f_out =  outlet_new(&x->x_gui.x_obj, NULL);
        
        x->f_numberOfMic = DEF_MICS;
        x->f_last_mouseMoveOverMic = x->f_last_mouseDownOverMic = x->f_last_mouseUpOverMic = -1;
        x->f_showFishEye = 0;
        
        x->f_mics = new AmbisonicVirtualMicUIManager(x->f_numberOfMic);
        
        x->f_mics->setNumberOfMics(x->f_numberOfMic);


        // couleurs
        x->f_colorBackground = RGBAColor1(0.35, 0.35, 0.35, 1.);
        x->f_colorBorder     = RGBAColor1(0.2 , 0.2 , 0.2 , 1.);
        x->f_colorInnerCircle= RGBAColor1(0.2 ,0.2, 0.2, 1.);
        x->f_colorMic        = RGBAColor1(0.5 ,0.5, 0.5, 1. );
        x->f_colorMicSelected= RGBAColor1(0.86 ,0.86, 0.86, 1.);
        x->f_colorHarmonics  = RGBAColor1(0.4, 0.4 ,0.4 ,0.3);
        x->f_fisheyecolor    = RGBAColor1(0.69, 0.18, 0.18, 1.);
        x->f_color_selection = RGBAColor1(0.39 ,0.52 ,0.8, 1.);
        x->f_colorTextMic    = RGBAColor1(0.9, 0.9, 0.9, 1.);
        x->f_colorTextMicSelected = RGBAColor1(0.4, 0.4, 0.4, 1.);
        
        
        x->x_gui.x_w = 400;
        x->x_gui.x_h = 400;
        x->x_gui.x_draw = (t_iemfunptr)hoaRecomposer_draw;
        x->x_gui.x_glist = (t_glist *)canvas_getcurrent();
        x->f_micRadius = x->x_gui.x_w * 0.46;
        
        
    }
    return (x);
}
static void hoaRecomposer_free(t_HoaRecomposerUI *x)
{
    gfxstub_deleteforkey(x);

    delete x->f_mics;

}





extern "C" void setup_hoa0x2erecomposer(void)
{
    HoaRecomposerUI_class = class_new(gensym("hoa.recomposer"), (t_newmethod)hoaRecomposer_new,
                               (t_method)hoaRecomposer_free, sizeof(t_HoaRecomposerUI), 0, A_GIMME, 0);
    
    class_addmethod(HoaRecomposerUI_class, (t_method)hoaRecomposer_click, gensym("click"),
                    A_FLOAT, A_FLOAT, A_FLOAT, A_FLOAT, A_FLOAT, 0);
    
    
    
    class_addmethod(HoaRecomposerUI_class, (t_method)hoaRecomposer_motion, gensym("motion"),
                    A_FLOAT, A_FLOAT, 0);
    
    
    //class_addmethod(HoaRecomposerUI_class, (t_method)hoaRecomposer_list, gensym("list"), A_GIMME,0);
    
    hoaRecomposer_widgetbehavior.w_getrectfn = hoaRecomposer_getrect;
    hoaRecomposer_widgetbehavior.w_displacefn = iemgui_displace;
    hoaRecomposer_widgetbehavior.w_selectfn = iemgui_select;
    hoaRecomposer_widgetbehavior.w_activatefn = NULL;
    hoaRecomposer_widgetbehavior.w_deletefn = iemgui_delete;
    hoaRecomposer_widgetbehavior.w_visfn = iemgui_vis;
    hoaRecomposer_widgetbehavior.w_clickfn = hoaRecomposer_newclick;
    
    //class_setpropertiesfn(hoaSpace_class, hoaSpace_properties);
    
    
#if defined(PD_MAJOR_VERSION) && (PD_MINOR_VERSION >= 37)
    class_setsavefn(HoaRecomposerUI_class, hoaRecomposer_save);
#else
    hoaRecomposer_widgetbehavior.w_propertiesfn = NULL;
    hoaRecomposer_widgetbehavior.w_savefn = hoaRecomposer_save;
#endif
    
    class_setwidget(HoaRecomposerUI_class, &hoaRecomposer_widgetbehavior);
    //  class_sethelpsymbol(room_sim_2d_class, gensym("iemhelp2/help-room_sim_2d"));
}


