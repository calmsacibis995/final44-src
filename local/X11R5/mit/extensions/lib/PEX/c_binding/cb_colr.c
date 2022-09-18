/* $XConsortium: cb_colr.c,v 5.1 91/02/16 09:47:37 rws Exp $ */

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

/* Colour functions for the PHIGS C binding */

#include "phg.h"
#include "cp.h"
#include "cb_priv.h"


void
pset_colr_rep( ws, index, rep)
    Pint	ws;	/* workstation identifier	*/
    Pint	index;	/* colour bundle index	*/
    Pcolr_rep	*rep;	/* colour representation pointer	*/
{
    Phg_args			cp_args;
    register Phg_args_set_rep	*args = &cp_args.data.set_rep;
    register Wst_phigs_dt	*dt;

    if ( dt = phg_cb_check_set_rep( phg_cur_cph, Pfn_set_colr_rep, ws, 1,
	    index ) ) {
	/* Valid color values depend on the color model in use so we
	 * have to catch invalid values in the ws code.
	 */
	args->wsid = ws;
	args->type = PHG_ARGS_COREP;
	args->rep.index = index;
	args->rep.bundl.corep = *rep;
	CP_FUNC( phg_cur_cph, CP_FUNC_OP_SET_REP, &cp_args, NULL);
    }
}


void
pset_colr_model( ws, model)
    Pint	ws;	/* workstation identifier	*/
    Pint	model;	/* colour model	*/
{
    Phg_args			cp_args;
    Phg_args_set_colour_model	*args = &cp_args.data.set_colour_model;
    Wst_phigs_dt		*dt;
    Psl_ws_info			*wsinfo;

    if ( CB_ENTRY_CHECK( phg_cur_cph, ERR3, Pfn_set_colr_model)) {
        if ( PSL_WS_STATE( phg_cur_cph->psl) != PWS_ST_WSOP) {
	    ERR_REPORT( phg_cur_cph->erh, ERR3);

	} else if ( !(wsinfo = phg_psl_get_ws_info( phg_cur_cph->psl, ws))) {
	    ERR_REPORT( phg_cur_cph->erh, ERR54);	/* ws not open */

	} else {
	    dt = &((Wst*)wsinfo->wstype)->desc_tbl.phigs_dt;
	    if ( !(dt->ws_category == PCAT_OUTIN
		|| dt->ws_category == PCAT_OUT
		|| dt->ws_category == PCAT_MO) ) {
		ERR_REPORT( phg_cur_cph->erh, ERR59);
	    
	    } else if ( !phg_cb_int_in_list( model,
		dt->out_dt.num_colour_models, dt->out_dt.colour_models)) {
		ERR_REPORT( phg_cur_cph->erh, ERR110);

	    } else {
		args->wsid = ws;
		args->model = model;
		CP_FUNC( phg_cur_cph, CP_FUNC_OP_SET_COLOUR_MODEL, &cp_args,
		    NULL);
	    }
	}
    }
}
