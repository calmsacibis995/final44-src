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
 *	Dump_Field (field_ptr, where)
 *
 *	The procedure prints the current value of the specified field on
 *	the specified stream.  This is hardly necessary from C, but it is
 *	required for interpreted versions.
 *
 */

Dump_Field (field_ptr, where)
register struct field_item      *field_ptr;
register FILE * where;
{
	F_Ok (field_ptr, "Dump_Field");

	fprintf (where, "%s\n", field_ptr -> txbuf);
}
