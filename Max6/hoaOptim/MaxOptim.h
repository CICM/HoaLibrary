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
 *  - Redistributions may not be sold, nor may they be used in a commercial product or activity.
 *  - Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  - Neither the name of the CICM nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DEF_MAX_OPTIM
#define DEF_MAX_OPTIM

#include "../MaxAmbisonic.h"

class MaxOptim: public MaxAmbisonic
{
private:
    t_symbol* m_optim;
    
public:
    MaxOptim(t_hoa_object* aParentObject, long argc = 0, t_atom* argv = NULL) : MaxAmbisonic(aParentObject, argc, argv)
    {
        m_optim = gensym("inPhase");
        if(argc >= 2 && atom_gettype(argv+1) == A_SYM)
        {
            if(atom_getsym(argv+1) == gensym("basic") || atom_getsym(argv+1) == gensym("maxRe"))
                m_optim = atom_getsym(argv+1);
        }
        OBJ_ATTR_SYM            ((t_object *)m_parent,"optim", 0, m_optim);
        OBJ_ATTR_ATTR_FORMAT    ((t_object *)m_parent,"optim","label",    USESYM(symbol),0,"s",gensym_tr("Optimization"));
        OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"optim","category", USESYM(symbol),0,str_tr("HoaLibrary"));
        OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"optim","style",    USESYM(symbol),0,"enum");
        OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"optim","enumvals", USESYM(atom),  0,"basic maxRe inPhase");
        OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"optim","order",    USESYM(long),  0,"2");
        OBJ_ATTR_ATTR_PARSE     ((t_object *)m_parent,"optim","save",     USESYM(long),  1,"1");
        
        rename_box();
    }
    
    void realloc_ambisonic()
    {
        m_parent->f_ambi = new AmbisonicOptim(object_attr_getlong(m_parent, gensym("order")), Hoa_InPhase_Optim, sys_getblksize());
        attr_notification(gensym("optim"));
    }
    
    void attr_notification(t_symbol* name)
    {
        if(name == gensym("optim"))
        {
            AmbisonicOptim* optim = (AmbisonicOptim*)m_parent->f_ambi;
            m_optim = object_attr_getsym(m_parent, gensym("optim"));
            if(m_optim == gensym("basic"))
                optim->setOptimMode(Hoa_Basic_Optim);
            else if(m_optim == gensym("maxRe"))
                optim->setOptimMode(Hoa_MaxRe_Optim);
            else
                optim->setOptimMode(Hoa_InPhase_Optim);
            rename_box();
        }
    }
    
    long getOptim()
    {
        m_optim = object_attr_getsym(m_parent, gensym("optim"));
        if(m_optim == gensym("basic"))
            return Hoa_Basic_Optim;
        else if(m_optim == gensym("maxRe"))
            return Hoa_MaxRe_Optim;
        else
            return Hoa_InPhase_Optim;
    }
    
    char* add_text()
    {
        return m_optim->s_name;
    }
    
    ~MaxOptim(){};
};

#endif