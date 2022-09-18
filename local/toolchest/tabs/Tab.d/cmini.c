/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <stdio.h>
#include <setjmp.h>
#include "vt.h"
#include "windows.h"
#include "fields.h"

/*
 *	cmini (field_ptr)
 *
 *	This function initializes various pointers and flags.  It
 *	should be noted that CMABU (Atom Buffer Unused) is set beacause
 *	this routine does not actually parse anything though it
 *	always returns with CMNOP clear -- indicating a successful parse.
 *
 *	This function will cause the field to be displayed.
 */

cmini (field_ptr, type)
register struct field_item    *field_ptr;
register int type;
{
	if (type)
		field_ptr -> txbuf[0] = '\0';
	field_ptr -> txptr = field_ptr -> txbuf;
	field_ptr -> txcursor = field_ptr -> txbuf;
	field_ptr -> txflg &= ~(TXEOF | TXBRK | TXBLR);
	field_ptr -> cmflg &= ~(CMNOP | CMREP | CMHLP | CMCMP | CMEOF | 
			CMEOL | CMABO | CMIBO | CMNUQ | CMFTAB | CMBTAB |
			CMHOME |  CMBOTTOM | CMUP | CMDOWN | CMLEFT |
			CMRIGHT | CMMOUSE | CMTAMPR);
	field_ptr -> cmflg |= CMABU;
}
