/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#ifndef DEF_JUCEBOX_STRUCT
#define DEF_JUCEBOX_STRUCT

extern "C" {
#include "ext.h"
#include "ext_obex.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "z_dsp.h"
}

#include "../JuceLibraryCode/JuceHeader.h"

class EditorComponentHolder;

typedef long (*t_max_err_method)(void* x, ...);

typedef struct _jucebox
{
	t_jbox	z_box;			///< The box struct used by all ui objects.
	long	z_in;
	void	*z_proxy;
	long	z_disabled;		///< set to non-zero if this object is muted (using the pcontrol or mute~ objects)
	short	z_count;		///< an array that indicates what inlets/outlets are connected with signals
	short	z_misc;			///< flags (bitmask) determining object behaviour, such as #Z_NO_INPLACE, #Z_PUT_FIRST, or #Z_PUT_LAST
	
	// custom
	t_rect      box_rect;
    int         isInitialised;
    t_object*	mPatcherview;
	juce::Component* juceEditorComp;
	EditorComponentHolder* juceWindowComp;
} t_jucebox;

#include "EditorComponentHolder.h"
EditorComponent* getOGLComponent(t_jucebox *x);

void jucebox_class_new(t_class* c, method paint, method notify);
void jucebox_new(t_jucebox* x);
void jucebox_free(t_jucebox* x);

// methods :
void jucebox_paint(t_jucebox* x, t_object *patcherview);
t_max_err jucebox_notify(t_jucebox *x, t_symbol *s, t_symbol *m, void *sender, void *data);
void jucebox_patcherview_vis(t_jucebox* x, t_object* patcherview);
void jucebox_patcherview_invis(t_jucebox* x, t_object* patcherview);
void jucebox_addjucecomponents(t_jucebox* x);

#endif