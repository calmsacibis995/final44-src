/* $XConsortium: cb_nset.c,v 5.1 91/02/16 09:47:54 rws Exp $ */

/***********************************************************
Copyright 1989, 1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Sun Microsystems,
the X Consortium, and MIT not be used in advertising or publicity 
pertaining to distribution of the software without specific, written 
prior permission.  

SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT 
SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/* Name set functions for the PHIGS C binding */

#include "phg.h"
#include "cp.h"
#include "cb_priv.h"

void
padd_names_set(set)
Pint_list	*set;	/* set of names to be added	*/
{
    Phg_args		cp_args;
    Phg_el_data		ed;
    Phg_args_add_el	*args = &cp_args.data.add_el;
    
    if (CB_ENTRY_CHECK(phg_cur_cph, ERR5, Pfn_add_names_set)) {
	if (PSL_STRUCT_STATE(phg_cur_cph->psl) != PSTRUCT_ST_STOP) {
	    ERR_REPORT(phg_cur_cph->erh, ERR5);

	} else {
	    args->el_type = PELEM_ADD_NAMES_SET;
	    ed.name_set = *set;
	    if ( CB_BUILD_OC(args->el_type, &ed, &args->pex_oc) )
		CP_FUNC( phg_cur_cph, CP_FUNC_OP_ADD_EL, &cp_args, NULL);
	}
    }
}

void
premove_names_set(set)
Pint_list	*set;	/* set of names to be removed	*/
{
    Phg_args		cp_args;
    Phg_el_data		ed;
    Phg_args_add_el	*args = &cp_args.data.add_el;
    
    if (CB_ENTRY_CHECK(phg_cur_cph, ERR5, Pfn_remove_names_set)) {
	if (PSL_STRUCT_STATE(phg_cur_cph->psl) != PSTRUCT_ST_STOP) {
	    ERR_REPORT(phg_cur_cph->erh, ERR5);

	} else {
	    args->el_type = PELEM_REMOVE_NAMES_SET;
	    ed.name_set = *set;
	    if ( CB_BUILD_OC(args->el_type, &ed, &args->pex_oc) )
		CP_FUNC( phg_cur_cph, CP_FUNC_OP_ADD_EL, &cp_args, NULL);
	}
    }
}
