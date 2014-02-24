
/*
 *  hoa.process~ header
 *
 *	This header file provides an interface for querying and seting the state of a parent hoa.process~ object.
 *	All communication with a host object should be done using this interface - the hoa.process~.c file has some more information.
 *
 *  based on dynamicdsp suite. Copyright 2010 Alex Harker. All rights reserved.
 *
 */


#ifndef HOA_PROCESSOR_DEF
#define HOA_PROCESSOR_DEF

#include "ext.h"

#define HoaProcessorIsValid(x) (x && ((((t_symbol *) ob_sym (x)) == gensym("hoa.process~"))))

//////////////////////////////////////////////// Object Queries ////////////////////////////////////////////////

// These routines *must* be called these routines at loadbang - they are bogus at any other time

__inline void *Get_HoaProcessor_Object() 
{
	void *HoaProcessor_Object = (void *) gensym("___HoaProcessor~___")->s_thing;

	if (HoaProcessorIsValid(HoaProcessor_Object))
		return HoaProcessor_Object;
	else
		return 0;
}


__inline long Get_HoaProcessor_Patch_Index(void *HoaProcessor_Object) 
{
	if (HoaProcessorIsValid(HoaProcessor_Object))
		return (long) gensym("___HoaProcessorPatchIndex___")->s_thing;
	else
		return 0;
}


//////////////////////////////////////////////// Signal IO Queries ////////////////////////////////////////////////


__inline long HoaProcessor_Get_Declared_Sigins(void *HoaProcessor_Object)
{
	if (HoaProcessorIsValid(HoaProcessor_Object))
		return (long) mess0((t_object *)HoaProcessor_Object, gensym("get_declared_sigins"));
	else
		return 0;
}


__inline long HoaProcessor_Get_Declared_Sigouts(void *HoaProcessor_Object)
{
	if (HoaProcessorIsValid(HoaProcessor_Object))
		return (long) mess0((t_object *)HoaProcessor_Object, gensym ("get_declared_sigouts"));
	else
		return 0;
}


__inline void **HoaProcessor_Get_Sigins(void *HoaProcessor_Object)
{
	if (HoaProcessorIsValid(HoaProcessor_Object))
		return (void**)mess0((t_object *)HoaProcessor_Object, gensym ("get_sigins"));
	else	
		return 0;
}


__inline void ***HoaProcessor_Get_Outptrs_Ptr(void *HoaProcessor_Object, long index)
{
	if (HoaProcessorIsValid(HoaProcessor_Object) && index > 0)
		return (void***)mess1((t_object *)HoaProcessor_Object, gensym("get_outptrs_ptr"), (void *)index);
	else
		return 0;
}


//////////////////////////////////////////////// State Queries ////////////////////////////////////////////////


__inline long HoaProcessor_Get_Patch_On (void *HoaProcessor_Object, long index)
{
	if (HoaProcessorIsValid(HoaProcessor_Object) && index > 0)
		return (long) mess1((t_object *)HoaProcessor_Object, gensym("get_patch_on"), (void *)index);
	
	return 0;
}

__inline void HoaProcessor_Set_Patch_On (void *HoaProcessor_Object, long index, long state)
{
	if (HoaProcessorIsValid(HoaProcessor_Object) && index > 0)
		mess2((t_object *)HoaProcessor_Object, gensym("set_patch_on"), (void *)index, (void *)state);
}

__inline long HoaProcessor_Get_Ambisonic_Order (void *HoaProcessor_Object)
{
	if (HoaProcessorIsValid(HoaProcessor_Object))
		return (long) mess0((t_object *)HoaProcessor_Object, gensym("get_ambisonic_order"));
	
	return 0;
}

__inline long HoaProcessor_Get_PatcherArgs (void *HoaProcessor_Object, long index, long *argc, t_atom **argv)
{
	if (HoaProcessorIsValid(HoaProcessor_Object))
		return (long) mess3((t_object *)HoaProcessor_Object, gensym("get_patcherargs"), (void *) index, argc, argv);
	
	return 0;
}

//////////////////////////////////////////////// Temporary Memory Queries ////////////////////////////////////////////////


__inline long HoaProcessor_Temp_Mem_Resize (void *HoaProcessor_Object, long index, long size)
{
	if (HoaProcessorIsValid(HoaProcessor_Object))
		return (long) mess2((t_object *)HoaProcessor_Object, gensym("temp_mem_resize"), (void *) index, (void *) size);
	else
		return 0;
}


__inline void **HoaProcessor_Get_TempMem (void *HoaProcessor_Object, long index, void **DefMem)
{
	if (HoaProcessorIsValid(HoaProcessor_Object) && index > 0)
		return (void**)mess1((t_object *)HoaProcessor_Object, gensym("get_temp_mem"), (void *) index);
	else
		return DefMem;
}


#endif