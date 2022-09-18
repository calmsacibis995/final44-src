/* $XConsortium: ut_path.c,v 5.6 91/07/10 09:21:07 rws Exp $ */

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

#include "phg.h"		/* includes Intrinsic.h and Xos.h */

#if defined(SYSV) && defined(SYSV386)
#include <net/errno.h>
#endif

#ifndef X_NOT_STDC_ENV
#include <stdlib.h>
#else
extern char *getenv();
#endif

#ifndef PEXAPIDIR
#define PEXAPIDIR "/usr/lib/X11/PEX"
#endif

/* The constant below is based on the max value given in access(1) */
#define PHG_MAXPATH	1023


char *
phg_path( fname, erh, test)
    char		*fname;
    Err_handle		erh;
    int			test;
{
    /* Return a full path to "fname" and possibly test for existence of
     * the file.  The path is made from the environment variable PEXAPIDIR
     * if it's specified, else from the PEXAPIDIR define.
     *
     * The PEXAPIDIR path is stored in a static area to avoid lookup next
     * time it's needed.
     *
     * If "test" is true, the existence of the file is checked and NULL is
     * returned if it's not found.
     *
     * If erh is NULL, no errors will be reported.
     */

     /* TODO: put in the correct error codes. */

    static char		dir[PHG_MAXPATH + 1];
    static int		dir_length;

    register char	*str;
    int			err;

    if ( !*dir) {	/* get the path */
	if ( !(str = getenv("PEXAPIDIR")))
	    str = PEXAPIDIR;
	strncpy( dir, str, PHG_MAXPATH - 1);

	if ( *dir)
	    strcat( dir, "/");
	else
	    strcpy( dir, "./");
	dir_length = strlen(dir);
    }
    str = dir;

    /* see if the full path is too big for the file system */
    if ( dir_length + strlen(fname) > PHG_MAXPATH) {
	str = NULL;
	if ( erh) {
	    ERR_BUF( erh, ERRN52);
	}
	*dir = '\0';

    } else {
	strcpy( &dir[dir_length], fname);

	if ( test && access( dir, F_OK) < 0) {
	    str = NULL;
	    switch ( errno) {
		case ENOENT:		err = ERRN54; break;
		case ENOTDIR:		err = ERRN53; break;
		case EACCES:		err = ERRN53; break;
		case ENAMETOOLONG:	err = ERRN52; break;
		case ELOOP:		err = ERRN53; break;
		default:
		    err = ERRN54;
		    break;
	    }
	    if ( erh) {
		ERR_BUF( erh, err);
	    }
	}
    }

    return str;
}
