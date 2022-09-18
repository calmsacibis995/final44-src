/* $XConsortium: cpx_css.c,v 5.1 91/02/16 09:48:31 rws Exp $ */

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

/* CPX CSS functions used in both client and monitor processes. */

#include "phg.h"
#include "cp.h"
#include "cp_priv.h"
#include "PEX.h"
#include "PEXmacs.h"
#include "PEXfuncs.h"
#include "PEXproto.h"
#include "phigspex.h"


void
phg_cpx_inq_el_type_size( cph, cp_args, ret )
    register Cp_handle		cph;
    Phg_args			*cp_args;
    Phg_ret			*ret;
{
    Cpx_css_srvr	*css_srvr;

    CPX_MASTER_SERVER(cph,css_srvr)
    (*css_srvr->inq_el_type_size)( cph, cp_args, ret, css_srvr );

}


void
phg_cpx_inq_el_content( cph, cp_args, ret )
    register Cp_handle		cph;
    Phg_args			*cp_args;
    Phg_ret			*ret;
{
    Cpx_css_srvr	*css_srvr;

    CPX_MASTER_SERVER(cph,css_srvr)
    (*css_srvr->inq_el_content)( cph, cp_args, ret, css_srvr );
}


void
phg_cpx_inq_el_ptr( cph, cp_args, ret )
    Cp_handle		cph;
    Phg_args		*cp_args;	/* should be NULL */
    Phg_ret		*ret;
{
    Cpx_css_srvr		*css_srvr;

    CPX_MASTER_SERVER(cph,css_srvr)
    (*css_srvr->inq_el_ptr)( cph, cp_args, ret, css_srvr );
}


void
phg_cpx_inq_struct_status( cph, cp_args, ret )
    Cp_handle		cph;
    Phg_args		*cp_args;
    Phg_ret		*ret;
{
    Cpx_css_srvr		*css_srvr;

    ret->data.idata = (int)PSTRUCT_STATUS_NON_EXISTENT;
    CPX_MASTER_SERVER(cph,css_srvr)
    (*css_srvr->inq_struct_status)( cph, cp_args, ret, css_srvr );
}


void
phg_cpx_inq_struct_ids( cph, cp_args, ret )
    Cp_handle		cph;
    Phg_args		*cp_args;	/* should be NULL */
    Phg_ret		*ret;
{
    Cpx_css_srvr	*css_srvr;

    ret->err = 0;
    CPX_MASTER_SERVER(cph,css_srvr)
    (*css_srvr->inq_struct_ids)( cph, cp_args, ret, css_srvr );
}


void
phg_cpx_el_search( cph, cp_args, ret )
    Cp_handle		cph;
    Phg_args		*cp_args;
    Phg_ret		*ret;
{
    Cpx_css_srvr	*css_srvr;

    ret->err = 0;
    CPX_MASTER_SERVER(cph,css_srvr)
    (*css_srvr->el_search)( cph, cp_args, ret, css_srvr );
}


void
phg_cpx_inq_hierarchy( cph, cp_args, ret )
    Cp_handle		cph;
    Phg_args		*cp_args;
    Phg_ret		*ret;
{
    Cpx_css_srvr	*css_srvr;

    ret->err = 0;
    CPX_MASTER_SERVER(cph,css_srvr)
    (*css_srvr->inq_hierarchy)( cph, cp_args, ret, css_srvr );
}


void
phg_cpx_inc_spa_search( cph, cp_args, ret )
    Cp_handle		cph;
    Phg_args		*cp_args;
    Phg_ret		*ret;
{
    Cpx_css_srvr	*css_srvr;

    ret->err = 0;
    CPX_MASTER_SERVER(cph,css_srvr)
    (*css_srvr->inc_spa_search)( cph, cp_args, ret, css_srvr );
}


void
phg_cpx_change_struct_refs( cph, cp_args )
    Cp_handle		cph;
    Phg_args		*cp_args;
{
    Cpx_css_srvr	*css_srvr;

    CPX_FOR_ALL_SERVERS(cph,css_srvr)
	(*css_srvr->change_struct_refs)( cph, cp_args, css_srvr );
}


void
phg_cpx_change_struct_idrefs( cph, cp_args )
    Cp_handle		cph;
    Phg_args		*cp_args;
{
    Cpx_css_srvr	*css_srvr;
    Phg_args		d_cp_args;
    Phg_ret		ret;

    CPX_FOR_ALL_SERVERS(cph,css_srvr)
	(*css_srvr->change_struct_idrefs)( cph, cp_args, css_srvr );
}

