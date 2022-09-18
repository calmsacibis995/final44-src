/* $XConsortium: cpb_ws.c,v 5.2 91/07/12 20:28:55 hersh Exp $ */

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

/* PEX/PHIGS open and close functions. */

#include "phg.h"
#include "cp.h"
#include "ws.h"
#include "css.h"
#include "cp_priv.h"
#include "PEX.h"
#include "PEXproto.h"
#include "PEXmacs.h"
#include "PEXfuncs.h"
#include "phigspex.h"


void
phg_cpb_ws_update( cph, cp_args, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Ws		*ws;
{
    (*ws->update)( ws, cp_args->data.ws_update.flag );
}

void
phg_cpb_ws_redraw_all( cph, cp_args, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Ws		*ws;
{
    (*ws->redraw_all)( ws, cp_args->data.ws_redraw_all.flag );
}


void
phg_cpb_set_disp_state( cph, cp_args, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Ws		*ws;
{
    (*ws->set_disp_update_state)( ws, cp_args->data.set_disp_state.mode,
	cp_args->data.set_disp_state.mod_mode );
}


void
phg_cpb_inq_disp_update_state( cph, cp_args, ret, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Phg_ret	*ret;
    Ws		*ws;
{
    (*ws->inq_disp_update_state)( ws, ret );
}



Ws_handle
phg_cpb_open_ws( cph, cp_args, ret, css_srvr )
    Cp_handle		cph;
    Phg_args		*cp_args;
    Phg_ret		*ret;
    Cpx_css_srvr	*css_srvr;
{
    Ws			*ws;

    ws = phg_wsb_open_ws( cph, cp_args, ret, css_srvr );

    return ws;
}


void
phg_cpb_close_ws( cph, cp_args, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Ws		*ws;
{
    Ws_post_str		*str_list;
    Wsb_output_ws	*owsb = &ws->out_ws.model.b;

    (*ws->update)( ws, PFLAG_PERFORM );

    str_list = owsb->posted.lowest.higher;
    while ( str_list->higher ) {
	phg_css_unpost( owsb->cssh, str_list->structh->struct_id, ws );
	str_list = str_list->higher;
    }
    (*ws->close)( ws );
}


void
phg_cpb_post_struct( cph, cp_args, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Ws		*ws;
{
    Struct_handle	str;
    int			was_posted = 0;

    if ( (str = phg_css_post( ws->out_ws.model.b.cssh,
	    cp_args->data.post_struct.struct_id, ws, &was_posted)) )
	(*ws->post)( ws, str, cp_args->data.post_struct.disp_pri, !was_posted );
}


void
phg_cpb_unpost_struct( cph, cp_args, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Ws		*ws;
{
    Struct_handle	str;

    if ( (str = phg_css_unpost( ws->out_ws.model.b.cssh,
	    cp_args->data.unpost_struct.struct_id, ws)) )
	(*ws->unpost)( ws, str );
}


void
phg_cpb_unpost_all( cph, cp_args, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Ws		*ws;
{
    (*ws->unpost_all)( ws );
    phg_css_unpost_all( ws->out_ws.model.b.cssh, ws );
}


void
phg_cpb_set_rep( cph, cp_args, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Ws		*ws;
{
    (*ws->set_rep)( ws, cp_args->data.set_rep.type,
	&cp_args->data.set_rep.rep );
}


void
phg_cpb_inq_rep( cph, cp_args, ret, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Phg_ret	*ret;
    Ws		*ws;
{
    (*ws->inq_representation)( ws, cp_args->data.q_rep.index,
	cp_args->data.q_rep.type, cp_args->data.q_rep.rep_type, ret );
}


void
phg_cpb_inq_view_rep( cph, cp_args, ret, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Phg_ret	*ret;
    Ws		*ws;
{
    (*ws->inq_view_rep)( ws, cp_args->data.q_view_rep.index, ret );
}


void
phg_cpb_set_hlhsr_mode( cph, cp_args, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Ws		*ws;
{
    (*ws->set_hlhsr_mode)( ws, cp_args->data.set_hlhsr_mode.mode );
}


void
phg_cpb_inq_hlhsr_mode( cph, cp_args, ret, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Phg_ret	*ret;
    Ws		*ws;
{
    (*ws->inq_hlhsr_mode)( ws, ret );
}


void
phg_cpb_set_ws_win( cph, cp_args, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Ws		*ws;
{
    (*ws->set_ws_window)( ws, cp_args->data.set_ws_winvp.two_d,
	&cp_args->data.set_ws_winvp.limits );
}


void
phg_cpb_set_ws_vp( cph, cp_args, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Ws		*ws;
{
    (*ws->set_ws_vp)( ws, cp_args->data.set_ws_winvp.two_d,
	&cp_args->data.set_ws_winvp.limits );
}


void
phg_cpb_inq_ws_xform( cph, cp_args, ret, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Phg_ret	*ret;
    Ws		*ws;
{
    (*ws->inq_ws_xform)( ws, ret );
}


void
phg_cpb_set_filter( cph, cp_args, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Ws		*ws;
{
    (*ws->set_filter)( ws, cp_args->data.set_filter.type,
	cp_args->data.set_filter.devid, &cp_args->data.set_filter.inc_set,
	&cp_args->data.set_filter.exc_set );
}


void
phg_cpb_inq_filter( cph, cp_args, ret, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Phg_ret	*ret;
    Ws		*ws;
{
    (*ws->inq_filter)( ws, cp_args->data.q_filter.type, ret );
}


void
phg_cpb_inq_posted( cph, cp_args, ret, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Phg_ret	*ret;
    Ws		*ws;
{
    (*ws->inq_posted)( ws, ret );
}


void
phg_cpb_set_view_input_priority( cph, cp_args, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Ws		*ws;
{
    (*ws->set_view_input_priority)( ws,
	cp_args->data.set_view_input_prio.idx,
	cp_args->data.set_view_input_prio.ref_idx,
	cp_args->data.set_view_input_prio.priority );
}


void
phg_cpb_inq_indices( cph, cp_args, ret, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Phg_ret	*ret;
    Ws		*ws;
{
    switch ( cp_args->data.q_indices.type ) {
	case PHG_ARGS_LNREP:
	case PHG_ARGS_MKREP:
	case PHG_ARGS_TXREP:
	case PHG_ARGS_INTERREP:
	case PHG_ARGS_EDGEREP:
	case PHG_ARGS_PTREP:
	case PHG_ARGS_COREP:
	case PHG_ARGS_DCUEREP:
	case PHG_ARGS_LIGHTSRCREP:
	case PHG_ARGS_COLRMAPREP:
	    (*ws->inq_bundle_indices)( ws, cp_args->data.q_indices.type, ret );
	    break;
	case PHG_ARGS_VIEWREP:
	    (*ws->inq_view_indices)( ws, ret );
	    break;
    }
}


void
phg_cpb_message( cph, cp_args, ws )
    Cp_handle	cph;
    Phg_args	*cp_args;
    Ws		*ws;
{
    if ( ws->message )
	(*ws->message)( ws, &cp_args->data.message );
}


void
phg_cpb_inq_text_extent( cph, cp_args, ret, ws )
    Cp_handle		cph;
    Phg_args		*cp_args;
    Phg_ret		*ret;
    Ws			*ws;
{
    phg_wsx_inq_text_extent( cph, &cp_args->data.q_text_extent, ret, ws );
}


void
phg_cpb_ws_drawable_pick( cph, cp_args, ret, ws )
    Cp_handle		cph;
    Phg_args		*cp_args;
    Phg_ret		*ret;
    Ws			*ws;
{
    if (ws->drawable_pick )
	(*ws->drawable_pick )( ws, &cp_args->data.map_points, ret );
    else {
	ret->err = ERR350;
	ERR_BUF( cph->erh, ERR350 );
    }
}


void
phg_cpb_ws_map_points( cph, cp_args, ret, ws )
    Cp_handle		cph;
    Phg_args		*cp_args;
    Phg_ret		*ret;
    Ws			*ws;
{
    if (ws->map_points )
	(*ws->map_points )( ws, &cp_args->data.map_points, ret );
    else {
	ret->err = ERR350;
	ERR_BUF( cph->erh, ERR350 );
    }
}

void
phg_cpb_ws_redraw_regions( cph, cp_args, ws )
    Cp_handle		cph;
    Phg_args		*cp_args;
    Ws			*ws;
{
    if ( ws->redraw_regions )
	(*ws->redraw_regions)( ws, &cp_args->data.redraw_regions );
}

void
phg_cpb_ws_synch( cph, cp_args, ws )
    Cp_handle		cph;
    Phg_args		*cp_args;
    Ws			*ws;
{
    if ( ws->synch )
	(*ws->synch)( ws );
}


void
phg_cpb_inq_colr_map_meth_st( cph, cp_args, ret, ws )
    Cp_handle		cph;
    Phg_args		*cp_args;
    Phg_ret		*ret;
    Ws			*ws;
{
    phg_wsx_inq_colr_map_meth_st( cph, &cp_args->data.q_colr_map_meth_st, ret, ws );
}
