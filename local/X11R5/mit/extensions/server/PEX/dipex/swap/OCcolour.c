/* $XConsortium: OCcolour.c,v 5.1 91/02/16 09:57:30 rws Exp $ */

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

/*
	Swapping and float conversion routines.

	Variations on a theme by CITI.
 */

#include "X.h"
#include "Xproto.h"
#include "misc.h"
#include "PEX.h"
#include "PEXproto.h"
#include "PEXprotost.h"
#include "dipex.h"
#include "pexSwap.h"
#include "pex_site.h"
#include "convertStr.h"

/*
	colour OCs for Requests
 */
#define SWAP_FILE "OCcolour.ci"
#include "ConvName.ci"
#undef SWAP_FILE

/*
	colour OCs for Replies
 */
#define SWAP_FILE "OCcolour.ci"
#include "UconvName.ci"
#undef SWAP_FILE

