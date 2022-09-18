/* $XConsortium: cb_dcue.c,v 5.1 91/02/16 09:47:39 rws Exp $ */

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


/* Depth Cue functions for the PHIGS C binding */

#include "phg.h"
#include "cp.h"
#include "cb_priv.h"



/* SET DEPTH CUE INDEX */
void
pset_dcue_ind( index)
    Pint	index;	/* depth cue index	*/
{   
    Phg_args		cp_args;
    Phg_el_data		ed;
    Phg_args_add_el	*args = &cp_args.data.add_el;
    
    if (CB_ENTRY_CHECK(phg_cur_cph, ERR5, Pfn_set_dcue_ind)) {
	if (PSL_STRUCT_STATE(phg_cur_cph->psl) != PSTRUCT_ST_STOP) {
	    ERR_REPORT(phg_cur_cph->erh, ERR5);	
	}
	else if (index < 0) {
	    ERR_REPORT(phg_cur_cph->erh, ERR119);
	}
	else {
	    args->el_type = PELEM_DCUE_IND;
	    ed.idata = index;
	    if ( CB_BUILD_OC(args->el_type, &ed, &args->pex_oc) )
		CP_FUNC( phg_cur_cph, CP_FUNC_OP_ADD_EL, &cp_args, NULL);
	}
    }
}


/* SET DEPTH CUE REPRESENTATION */
void
pset_dcue_rep( ws, index, rep)
    Pint	ws;	/* workstation identifier	*/
    Pint	index;	/* depth cue bundle index	*/
    Pdcue_bundle *rep;	/* depth cue representation pointer	*/
{
    Phg_args			cp_args;
    register Phg_args_set_rep	*args = &cp_args.data.set_rep;
    register Wst_phigs_dt	*dt;
    Psl_ws_info			*wsinfo;
    

    if (CB_ENTRY_CHECK(phg_cur_cph, ERR3, Pfn_set_dcue_rep)) {
    	if (PSL_WS_STATE(phg_cur_cph->psl) != PWS_ST_WSOP) {
	    ERR_REPORT(phg_cur_cph->erh, ERR3);
	    return;

	} else if (!(wsinfo = phg_psl_get_ws_info( phg_cur_cph->psl, ws))) {
	    ERR_REPORT(phg_cur_cph->erh, ERR54);
	    return;
	}

	dt = &((Wst*)wsinfo->wstype)->desc_tbl.phigs_dt;
	if ( !( dt->ws_category == PCAT_OUTIN || dt->ws_category == PCAT_OUT
	    || dt->ws_category == PCAT_MO) ) {
	    ERR_REPORT(phg_cur_cph->erh, ERR59);

	} else if (!CB_COLOUR_MODEL_SUPPORTED(rep->colr.type)) {
	    ERR_REPORT( phg_cur_cph->erh, ERR110);

	} else if (index < 1) {
	    ERR_REPORT(phg_cur_cph->erh, ERR120);

	} else if (rep->ref_planes[0] > rep->ref_planes[1]) {
	    ERR_REPORT(phg_cur_cph->erh, ERR130);

	} else {
	    args->wsid = ws;
	    args->type = PHG_ARGS_DCUEREP;
	    args->rep.index = index;
	    args->rep.bundl.dcuerep = *rep;
	    CP_FUNC( phg_cur_cph, CP_FUNC_OP_SET_REP, &cp_args, NULL);
	}
    }
}


/* INQUIRE DEPTH CUE REPRESENTATION */
void
pinq_dcue_rep( ws, index, type, error_ind, rep)
    Pint	 ws;		/* workstation identifier	*/
    Pint	 index;		/* polyline index	*/
    Pinq_type	 type;		/* type of returned value	*/
    Pint	*error_ind;	/* OUT error indicator	*/
    Pdcue_bundle *rep;		/* OUT depth cue representation	*/
{
    Phg_args		cp_args;
    Phg_ret		ret;
    Psl_ws_info		*wsinfo;
    Wst_phigs_dt	*dt;

    if ( !CB_ENTRY_CHECK( phg_cur_cph, 0, Pfn_INQUIRY)) {
	*error_ind = ERR3;

    } else if ( PSL_WS_STATE( phg_cur_cph->psl) != PWS_ST_WSOP) {
	*error_ind = ERR3;

    } else if ( !(wsinfo = phg_psl_get_ws_info( phg_cur_cph->psl, ws))) {
	*error_ind = ERR54;
    } else {
	*error_ind = 0;
	dt = &((Wst*)wsinfo->wstype)->desc_tbl.phigs_dt;
	if ( !(dt->ws_category == PCAT_OUT || 
	       dt->ws_category == PCAT_OUTIN ||
	       dt->ws_category == PCAT_MO) ) {
	    *error_ind = ERR59;

	} else if ( index < 0) {
	    *error_ind = ERR119;
	}

	if (!*error_ind) {
	    cp_args.data.q_rep.wsid = ws;
	    cp_args.data.q_rep.index = index;
	    cp_args.data.q_rep.type = type;
	    cp_args.data.q_rep.rep_type = PHG_ARGS_DCUEREP;
	    CP_FUNC( phg_cur_cph, CP_FUNC_OP_INQ_REPRESENTATION, &cp_args,
			&ret);
	    if ( ret.err) {
		*error_ind = ret.err;
	    } else {
		*rep = ret.data.rep.dcuerep;
	    }
	}
    }
}
