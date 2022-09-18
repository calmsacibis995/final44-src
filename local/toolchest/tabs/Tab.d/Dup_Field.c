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

struct field_item      *
Dup_Field (f1)
register struct field_item      *f1;
{
	extern char    *malloc ();

	register char  *ptr;
	register int    len;
	struct field_item      *f2;

	F_Ok (f1, "Dup_Field");

	f2 = (struct field_item *) malloc (sizeof (struct field_item) + MXTRA);

	if (f2 == 0)
	{
		Print_Message (stdwindow, 0, "Cannot allocate field space.");
		return (0);
	}

	f2 -> x_pos = f1 -> x_pos;
	f2 -> y_pos = f1 -> y_pos;
	f2 -> type = f1 -> type;
	f2 -> type_used = f1 -> type_used;
	f2 -> length = f1 -> length;
	f2 -> fill_char = f1 -> fill_char;
	f2 -> ext_fill_char = f1 -> ext_fill_char;
	f2 -> keywords = f1 -> keywords;
	f2 -> window = f1 -> window;
	f2 -> errwin = f1 -> errwin;
	f2 -> meswin = f1 -> meswin;

	f2 -> attribute = f1 -> attribute;
	f2 -> user_mask = f1 -> user_mask;
	f2 -> user_pointer = f1 -> user_pointer;
	f2 -> read_routine = f1 -> read_routine;
	f2 -> pre_action = f1 -> pre_action;
	f2 -> post_action = f1 -> post_action;
	f2 -> help_routine = f1 -> help_routine;

	f2 -> txflg = f1 -> txflg;
	f2 -> txbuf = f1 -> txbuf;
	f2 -> txend = f1 -> txend;
	f2 -> txptr = f1 -> txptr;
	f2 -> txcursor = f1 -> txcursor;

	f2 -> fnflg = f1 -> fnflg;
	f2 -> fnhlp = f1 -> fnhlp;
	f2 -> fnerr = f1 -> fnerr;
	f2 -> fndfs = f1 -> fndfs;
	f2 -> fndfv = f1 -> fndfv;
	f2 -> fnalt = f1 -> fnalt;

	f2 -> cmflg = f1 -> cmflg;

	f2 -> label = f1 -> label;
	f2 -> txbuf = malloc (f2 -> length + 2 + MXTRA);
	if (f2 -> txbuf == 0)
	{
		Print_Message (stdwindow, 0, "Cannot allocate field space.");
		return (0);
	}
	for (ptr = f2 -> txbuf, len = 0;
			len < f2 -> length; len++, ptr++)
	{
		*ptr = 0;
	}
	f2 -> txend = &(f2 -> txbuf[f2 -> length + 1]);

	f2 -> _field_check = GOOD_FIELD;

	if (_F_Field > f2)
		_F_Field = f2;
	if (_L_Field < f2)
		_L_Field = f2;

	return (f2);
}
