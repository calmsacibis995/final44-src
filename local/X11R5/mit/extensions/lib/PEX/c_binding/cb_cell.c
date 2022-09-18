/* $XConsortium: cb_cell.c,v 5.1 91/02/16 09:47:36 rws Exp $ */

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

/* Cell array functions for the PHIGS C binding */

#include "phg.h"
#include "cp.h"
#include "cb_priv.h"

void
pcell_array3(parallelogram, colrs)
    Pparal	*parallelogram; /* cell parallelogram: [0]=P; [1]=Q; [2]=R */
    Ppat_rep	*colrs;	/* colour array */
{
    Phg_args		cp_args;
    Phg_el_data		ed;
    Phg_args_add_el	*args = &cp_args.data.add_el;

    register	int	i;
    register	Pint	*colour_index;
    
    if (CB_ENTRY_CHECK(phg_cur_cph, ERR5, Pfn_cell_array3)) {
	if (PSL_STRUCT_STATE(phg_cur_cph->psl) != PSTRUCT_ST_STOP) {
	    ERR_REPORT(phg_cur_cph->erh, ERR5);
	}
	else if ( colrs->dims.size_x < 0 || colrs->dims.size_y < 0 ) {
	    ERR_REPORT(phg_cur_cph->erh, ERR117);
	}
	else {
	    args->el_type = PELEM_CELL_ARRAY3;
	    ed.cell_array3.paral.p = parallelogram->p;
	    ed.cell_array3.paral.q = parallelogram->q;
	    ed.cell_array3.paral.r = parallelogram->r;
	    ed.cell_array3.dim = colrs->dims;
	    ed.cell_array3.colr = colrs->colr_array;
	    colour_index = colrs->colr_array;
	    for (i = 0; i < (colrs->dims.size_x * colrs->dims.size_y); i++) {
		if (*colour_index++ < 0) {
		    ERR_REPORT(phg_cur_cph->erh, ERR113);
		    return;
		}
	    }
	    if ( CB_BUILD_OC(args->el_type, &ed, &args->pex_oc) )
		CP_FUNC( phg_cur_cph, CP_FUNC_OP_ADD_EL, &cp_args, NULL);
	}
    }
}

void
pcell_array(rectangle, colrs)
    Prect	*rectangle;	/* cell rectangle	*/
    Ppat_rep	*colrs;		/* colour array */
{
    Phg_args		cp_args;
    Phg_el_data		ed;
    Phg_args_add_el	*args = &cp_args.data.add_el;

    register	int	i;
    register	Pint	*colour_index;
    
    if (CB_ENTRY_CHECK(phg_cur_cph, ERR5, Pfn_cell_array)) {
	if (PSL_STRUCT_STATE(phg_cur_cph->psl) != PSTRUCT_ST_STOP) {
	    ERR_REPORT(phg_cur_cph->erh, ERR5);
	}
	else if ( colrs->dims.size_x < 0 || colrs->dims.size_y < 0 ) {
	    ERR_REPORT(phg_cur_cph->erh, ERR117);
	}
	else {
	    args->el_type = PELEM_CELL_ARRAY;
	    ed.cell_array.rect = *rectangle;
	    ed.cell_array.dim = colrs->dims;
	    ed.cell_array.colr = colrs->colr_array;
	    colour_index = colrs->colr_array;
	    for (i = 0; i < (colrs->dims.size_x * colrs->dims.size_y); i++) {
		if (*colour_index++ < 0) {
		    ERR_REPORT(phg_cur_cph->erh, ERR113);
		    return;
		}
	    }
	    if ( CB_BUILD_OC(args->el_type, &ed, &args->pex_oc) )
		CP_FUNC( phg_cur_cph, CP_FUNC_OP_ADD_EL, &cp_args, NULL);
	}
    }
}

void
pcell_array3_plus(paral, dim, colour_model, colrs)
Pparal  *paral;                   /* cell parallelogram: [0]=P; [1]=Q; [2]=R */
Pint_size    *dim;                   /* dimension of cell: DX and DY */
Pint	colour_model;		/* colour model */
Pcoval  *colrs;          	/* colour array   */
{
    Phg_args		cp_args;
    Phg_el_data		ed;
    Phg_args_add_el	*args = &cp_args.data.add_el;

    if (CB_ENTRY_CHECK(phg_cur_cph, ERR5, Pfn_cell_array3_plus)) {
        if (PSL_STRUCT_STATE(phg_cur_cph->psl) != PSTRUCT_ST_STOP) {
            ERR_REPORT(phg_cur_cph->erh, ERR5);
        }
        else if ( dim->size_x < 0 || dim->size_y < 0 ) {
            ERR_REPORT(phg_cur_cph->erh, ERR117);
        }
        else {
            args->el_type = PELEM_CELL_ARRAY3_PLUS;
            ed.ext_cell_arr3.paral.p = paral->p;
            ed.ext_cell_arr3.paral.q = paral->q;
            ed.ext_cell_arr3.paral.r = paral->r;
            ed.ext_cell_arr3.dim = *dim;
	    ed.ext_cell_arr3.colour_model = colour_model;
            ed.ext_cell_arr3.colr = colrs;
	    if ( CB_BUILD_OC(args->el_type, &ed, &args->pex_oc) )
		CP_FUNC( phg_cur_cph, CP_FUNC_OP_ADD_EL, &cp_args, NULL);
        }
    }    
}
