/*
 // Copyright (c) 2012-2014 Eliott Paris & Pierre Guillot, CICM, Universite Paris 8.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#ifndef DEF_ESTRUCT
#define DEF_ESTRUCT

extern "C" {
#include "ext.h"
#include "ext_obex.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "z_dsp.h"
}

extern juce::Component* createMaxBoxComponent();
class EditorComponentHolder;

typedef struct _oglpx_jucebox
{
	t_jbox	z_box;			///< The box struct used by all ui objects.
	long	z_in;
	void	*z_proxy;
	long	z_disabled;		///< set to non-zero if this object is muted (using the pcontrol or mute~ objects)
	short	z_count;		///< an array that indicates what inlets/outlets are connected with signals
	short	z_misc;			///< flags (bitmask) determining object behaviour, such as #Z_NO_INPLACE, #Z_PUT_FIRST, or #Z_PUT_LAST
	
	// custom
    int         isInitialised;
    t_object    *mPatcher;
    t_object    *mPatcherview;
	
	juce::Component* juceEditorComp;
	EditorComponentHolder* juceWindowComp;
} t_oglpx_jucebox;

// custom t_class
typedef struct _jbclass
{
    struct symbol *c_sym;			///< symbol giving name of class
	struct object **c_freelist;		// linked list of free ones
	method c_freefun;				// function to call when freeing
	t_getbytes_size c_size;			// size of an instance
	char c_tiny;					// flag indicating tiny header
	char c_noinlet;					// flag indicating no first inlet for patcher
	struct symbol *c_filename;		///< name of file associated with this class
	t_messlist *c_newmess;			// constructor method/type information
	method c_menufun;				// function to call when creating from object pallette (default constructor)
	long c_flags;					// class flags used to determine context in which class may be used
	long c_messcount;				// size of messlist array
	t_messlist *c_messlist;			// messlist arrray
	void *c_attributes;				// t_hashtab object
	void *c_extra;					// t_hashtab object
	long c_obexoffset;				// if non zero, object struct contains obex pointer at specified byte offset
	void *c_methods;				// methods t_hashtab object
	method c_attr_get;				// if not set, NULL, if not present CLASS_NO_METHOD
	method c_attr_gettarget;		// if not set, NULL, if not present CLASS_NO_METHOD
	method c_attr_getnames;			// if not set, NULL, if not present CLASS_NO_METHOD
	struct maxclass *c_superclass;	// a superclass point if this is a derived class
} t_jbclass;


t_max_err eclass_addmethod(t_jbclass* c, method m, const char* name, e_max_atomtypes type, long anything);

#endif