/* $XConsortium: utx.c,v 5.2 91/05/07 11:50:47 rws Exp $ */

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
#include "PEX.h"
#include "PEXmacs.h"
#include "PEXfuncs.h"
#include "PEXproto.h"
#include "PEXtempl.h"
#include "phigspex.h"

int
phg_utx_pex_supported( display, pexinfo )
    Display		*display;
    Phg_pex_ext_info	*pexinfo;
{
    Phg_pex_ext_info	info;

    if ( !pexinfo )
	pexinfo = &info;

    if ( PEXGetExtensionInfo( display,
	    PEX_PROTO_MAJOR, PEX_PROTO_MINOR,
	    &pexinfo->major_version, &pexinfo->minor_version,
	    &pexinfo->vendor, &pexinfo->release_number,
	    &pexinfo->subset_info ) ) {
	if ( pexinfo == &info )
	    XFree( pexinfo->vendor );
	return 1;
    } else
	return 0;
}

Display*
phg_utx_open_pex_display( name, pexinfo, err )
    char		*name;
    Phg_pex_ext_info	*pexinfo;
    Pint		*err;
{
    Display		*display;
    char		*display_name;

    display_name = XDisplayName( name );
    if ( display = XOpenDisplay( display_name ) ) {
	if ( !PEXGetExtensionInfo( display,
		PEX_PROTO_MAJOR, PEX_PROTO_MINOR,
		&pexinfo->major_version, &pexinfo->minor_version,
		&pexinfo->vendor, &pexinfo->release_number,
		&pexinfo->subset_info ) ) {
	    XCloseDisplay( display );
	    display = (Display *)NULL;
	    *err = ERRN201;
	}
    } else
	*err = ERRN200;

    return display;
}

