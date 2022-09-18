/* $XConsortium: cpb_util.c,v 5.1 91/02/16 09:48:47 rws Exp $ */

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

#include "phg.h"
#include "cp.h"
#include "cp_priv.h"
#include "css.h"
#include "PEX.h"
#include "PEXmacs.h"
#include "PEXfuncs.h"
#include "PEXproto.h"
#include "phigspex.h"


Cpx_css_srvr*
phg_cpb_create( cph, create_css_flag )
    Cp_handle		cph;
    int			create_css_flag;
{
    Cpx_css_srvr	*css_srvr;

    if ( !(css_srvr = (Cpx_css_srvr *)calloc(1,sizeof(Cpx_css_srvr)))) {
	ERR_BUF( cph->erh, ERR900 );
    
    } else if ( create_css_flag &&
	    !(css_srvr->model.b.cssh = phg_css_init( cph->erh, SSH_CSS))) {
	free( (char *)css_srvr );
	ERR_BUF( cph->erh, ERR900 );

    } else if ( !(PHG_SCRATCH_SPACE( &css_srvr->model.b.scratch, 8096 ) ) ) {
	if ( css_srvr->model.b.cssh )
	    phg_css_destroy( css_srvr->model.b.cssh );
	free( (char *)css_srvr );
	css_srvr = (Cpx_css_srvr *)NULL;
	ERR_BUF( cph->erh, ERR900 );

    } else {
	css_srvr->type = CPX_CLNT_SS;
    }

    return css_srvr;
}


void
phg_cpb_destroy( css_srvr )
    Cpx_css_srvr	*css_srvr;
{
    if ( css_srvr->model.b.cssh )
	phg_css_destroy( css_srvr->model.b.cssh );
    if ( css_srvr->model.b.scratch.size >  0 ) {
	free( (char *)css_srvr->model.b.scratch.buf );
	css_srvr->model.b.scratch.buf = NULL;
	css_srvr->model.b.scratch.size = 0;
    }
    free( (char *)css_srvr );
}
