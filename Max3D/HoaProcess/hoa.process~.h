
/*
 *  dynamicdsp header
 *
 *	This header file provides an interface for querying and seting the state of a parent dynamicdsp object.
 *	All communication with a host object should be done using this interface - the dynamicdsp.c file has some more information.
 *	For examples of use see the dynamicdsp set of objects (dynamicdsp.in~ / dynamicdsp.out~ / dynamicdsp.this~ etc.).
 *
 *  Copyright 2010 Alex Harker. All rights reserved.
 *
 */


#ifndef HOA_PATCHER_DEF
#define HOA_PATCHER_DEF

#include "ext.h"

#define HoaPatcherIsValid(x) \
(x && ((((t_symbol *) ob_sym (x)) == gensym("dynamicdsp~")) || (ob_sym (x)) == gensym("dynamicserial~") || (ob_sym (x)) == gensym("dyndsp~")))

//////////////////////////////////////////////// Object Queries ////////////////////////////////////////////////

// These routines *must* be called these routines at loadbang - they are bogus at any other time

__inline void *Get_Dynamic_Object() 
{
	void *Dynamic_Object = (void *) gensym("___DynamicDSP~___")->s_thing;

	if (HoaPatcherIsValid(Dynamic_Object))
		return Dynamic_Object;
	else
		return 0;
}


__inline long Get_Dynamic_Patch_Index(void *Dynamic_Object) 
{
	if (HoaPatcherIsValid(Dynamic_Object))
		return (long) gensym("___DynamicPatchIndex___")->s_thing;
	else
		return 0;
}


//////////////////////////////////////////////// Signal IO Queries ////////////////////////////////////////////////


__inline long Dynamic_Get_Declared_Sigins(void *Dynamic_Object)
{
	if (HoaPatcherIsValid(Dynamic_Object))
		return (long) mess0((t_object *)Dynamic_Object, gensym("get_declared_sigins"));
	else
		return 0;
}


__inline long Dynamic_Get_Declared_Sigouts(void *Dynamic_Object)
{
	if (HoaPatcherIsValid(Dynamic_Object))
		return (long) mess0((t_object *)Dynamic_Object, gensym ("get_declared_sigouts"));
	else
		return 0;
}


__inline void **Dynamic_Get_Sigins(void *Dynamic_Object)
{
	if (HoaPatcherIsValid(Dynamic_Object))
		return (void**)mess0((t_object *)Dynamic_Object, gensym ("get_sigins"));
	else	
		return 0;
}


__inline void ***Dynamic_Get_Outptrs_Ptr(void *Dynamic_Object, long index)
{
	if (HoaPatcherIsValid(Dynamic_Object) && index > 0)
		return (void***)mess1((t_object *)Dynamic_Object, gensym("get_outptrs_ptr"), (void *)index);
	else
		return 0;
}


//////////////////////////////////////////////// State Queries ////////////////////////////////////////////////


__inline long Dynamic_Get_Patch_On (void *Dynamic_Object, long index)
{
	if (HoaPatcherIsValid(Dynamic_Object) && index > 0)
		return (long) mess1((t_object *)Dynamic_Object, gensym("get_patch_on"), (void *)index);
	
	return 0;
}


__inline void Dynamic_Set_Patch_Busy (void *Dynamic_Object, long index, long state)
{
	if (HoaPatcherIsValid(Dynamic_Object) && index > 0)
		mess2((t_object *)Dynamic_Object, gensym("set_patch_busy"), (void *)index, (void *)state);
}


__inline void Dynamic_Set_Patch_On (void *Dynamic_Object, long index, long state)
{
	if (HoaPatcherIsValid(Dynamic_Object) && index > 0)
		mess2((t_object *)Dynamic_Object, gensym("set_patch_on"), (void *)index, (void *)state);
}


__inline long Dynamic_Get_Patch_Busy (void *Dynamic_Object, long index)
{
	if (HoaPatcherIsValid(Dynamic_Object) && index > 0)
		return (long) mess1((t_object *)Dynamic_Object, gensym("get_patch_busy"), (void *)index);
	
	return 0;
}

//////////////////////////////////////////////// Temporary Memory Queries ////////////////////////////////////////////////


__inline long Dynamic_Temp_Mem_Resize (void *Dynamic_Object, long index, long size)
{
	if (HoaPatcherIsValid(Dynamic_Object))
		return (long) mess2((t_object *)Dynamic_Object, gensym("temp_mem_resize"), (void *) index, (void *) size);
	else
		return 0;
}


__inline void **Dynamic_Get_TempMem (void *Dynamic_Object, long index, void **DefMem)
{
	if (HoaPatcherIsValid(Dynamic_Object) && index > 0)
		return (void**)mess1((t_object *)Dynamic_Object, gensym("get_temp_mem"), (void *) index);
	else
		return DefMem;
}


#endif