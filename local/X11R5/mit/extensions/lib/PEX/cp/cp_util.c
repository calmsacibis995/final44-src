/* $XConsortium: cp_util.c,v 5.1 91/02/16 09:48:26 rws Exp $ */

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

/* Miscellaneous CP utility functions */

#include "phg.h"
#include "cp.h"
#include "cp_priv.h"
#include "version.h"

int
phg_cp_add_wst( cph, wst)
    register Cp_handle		cph;
    register Wst_handle		wst;
{
    int				status = 0;
    Cp_wst_list_entry		*node;

    if ( node = (Cp_wst_list_entry*)malloc( sizeof(*node)) ) {
	status = 1;
	node->wst = wst;
	node->next = cph->wst_list;
	cph->wst_list = node;
    }
    return status;
}


void
phg_cp_rmv_wst( cph, wst)
    register Cp_handle		cph;
    register Wst_handle		wst;
{
    register Cp_wst_list_entry		**node;
    Cp_wst_list_entry			*t;

    node = &cph->wst_list;
    while ( *node) {
	if ( (*node)->wst == wst) {
	    t = *node;
	    *node = (*node)->next;
	    free( (char *)t );
	    break;
	}
	node = &(*node)->next;
    }
}

void
phg_cp_destroy_wst_list( cph)
    register Cp_handle		cph;
{
    register Cp_wst_list_entry		*node, *next;

    node = cph->wst_list;
    while ( node) {
	next = node->next;
	phg_wst_destroy( node->wst );
	free( (char *)node );
	node = next;
    }
}
