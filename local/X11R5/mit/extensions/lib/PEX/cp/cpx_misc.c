/* $XConsortium: cpx_misc.c,v 5.1 91/02/16 09:48:32 rws Exp $ */

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

/* Miscellaneous CP functions used in both client and monitor processes. */

#include "phg.h"
#include "cp.h"
#include "cp_priv.h"
#include "PEX.h"
#include "PEXmacs.h"
#include "PEXfuncs.h"
#include "phigspex.h"


void
phg_cpx_set_err_hand_mode( cph, cp_args )
    Cp_handle		cph;
    Phg_args		*cp_args;
{
    Cpx_css_srvr	*css_srvr;

    cph->erh->mode =  (Perr_mode)cp_args->data.idata;
    CPX_FOR_ALL_SERVERS(cph,css_srvr) {
	if ( css_srvr->set_err_hand_mode )
	    (*css_srvr->set_err_hand_mode)( cph, cp_args, css_srvr );
    }
}


void
phg_cpx_dummy_await_event( cph, args, ret )
    Cp_handle		cph;
    Phg_args		*args;
    Phg_ret		*ret;
{
    ret->err = 0;
    ret->data.inp_event.id.class = PIN_NONE;
    /* TODO: May want to wait the specified timeout. */
}

void
phg_cpx_dummy_flush_dev( cph, args )
    Cp_handle		cph;
    Phg_args		*args;
{
    /* do nothing */
}

void
phg_cpx_dummy_inq_overflow( cph, args, ret )
    Cp_handle		cph;
    Phg_args		*args;
    Phg_ret		*ret;
{
    /* The input queue will never overflow since there is no input. */
    ret->err = ERR257;
}

void
phg_cpx_dummy_inq_more_events( cph, args, ret )
    Cp_handle		cph;
    Phg_args		*args;
    Phg_ret		*ret;
{
    ret->err = 0;
    ret->data.idata = (Pint)PSIMULT_NO_MORE;
}

