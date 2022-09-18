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
 *	New_Field (x_pos, y_pos, type, fill_char, help, keywords)
 *
 *	This function creates a new field with the specified attributes.
 *
 */

struct field_item      *
New_Field (x_pos, y_pos, type, fill_char, help, keywords)
int     x_pos;
int     y_pos;
int     (*type) ();
char   *fill_char;
char   *help;
char   *keywords;
{
	extern struct window   *stdwindow;
	extern struct window   *errwindow;
	extern int	getachar ();
	extern int	read_num ();
	extern char    *malloc ();

	register struct field_item      *field_ptr;
	register char  *ptr;

	field_ptr = (struct field_item *)
              malloc (sizeof (struct field_item) + MXTRA);

	if (field_ptr == 0)
	{
		Print_Message (stdwindow, 0, "Cannot allocate field space.");
		return (0);
	}

	field_ptr -> x_pos = x_pos;
	field_ptr -> y_pos = y_pos;
	field_ptr -> type = type;
	field_ptr -> type_used = 0;
	field_ptr -> ext_fill_char = 0;
	if (type == CMREGN)
		field_ptr -> length = 8;
	else
		field_ptr -> length = strlen (fill_char);
	field_ptr -> fill_char = fill_char;
	field_ptr -> keywords = 0;
	field_ptr -> window = stdwindow;
	field_ptr -> errwin = errwindow;
	field_ptr -> meswin = stdwindow;

	field_ptr -> attribute = 0;
	field_ptr -> user_mask = 0;
	field_ptr -> user_pointer = 0;
	field_ptr -> read_routine = getachar;
	field_ptr -> pre_action = 0;
	field_ptr -> post_action = 0;
	field_ptr -> help_routine = 0;

	field_ptr -> fnhlp = 0;
	field_ptr -> fndfs = 0;
	field_ptr -> fndfv = 0;
	field_ptr -> fnalt = 0;
	field_ptr -> label = 0;

	field_ptr -> txflg = 0;
	field_ptr -> txbuf = malloc (field_ptr -> length + 2 + MXTRA);
	if (field_ptr -> txbuf == 0)
	{
		Print_Message (stdwindow, 0, "Cannot allocate field space.");
		return (0);
	}

	field_ptr -> txend = &(field_ptr -> txbuf[field_ptr -> length + 1]);
	for (ptr = field_ptr -> txbuf; ptr < field_ptr -> txend; ptr++)
	{
		*ptr = '\0';
	}

/*
 * Switch on Type - Can't switch on procedure names (not known until ld)
 *
 */
	if ((type == CMKEY) || (type == CMKEY_LIST))
	{
		field_ptr -> keywords = keywords;
	}
	else
	if (type == CMFILE)
	{
		field_ptr -> fndfv = 1;
		if ((keywords) && (*keywords))
		{
			ptr = nscan (keywords, &(field_ptr -> fndfv));
			if ((field_ptr -> fndfv) < 1)
				field_ptr -> fndfv = 1;
		}
	}
	else
	if (type == CMNUM)
	{
		field_ptr -> read_routine = read_num;
		if ((keywords) && (*keywords))
		{
			ptr = nscan (keywords, &(field_ptr -> fndfv));
			if ((field_ptr -> fndfv) < 0)
				field_ptr -> fndfv = 0;
			if ((field_ptr -> fndfv) > 9)
				field_ptr -> fndfv = 9;
			ptr++;
			field_ptr -> keywords = malloc (strlen (ptr) + MXTRA);
			if (field_ptr -> keywords == 0)
			{
				Print_Message (stdwindow, 0,
					"Cannot allocate field space.");
				return (0);
			}
			strcpy (field_ptr -> keywords, ptr);
		}
	}
	else
	if (type == CMCFM)
	{
		field_ptr -> length = 0;
	}
	else
	if (type == CMREGN)
	{
		field_ptr -> fnalt = (struct field_item *) fill_char;
		field_ptr -> length = (int) help;
		goto Done_Field;
	}

	field_ptr -> fnflg = FNHLST;
	if ((help != 0) && (*help != '\0'))
	{
		field_ptr -> fnhlp = help;
		field_ptr -> fnflg |= FNHLP;
	}
	field_ptr -> fnerr = 0;
	field_ptr -> cmflg = CMVERIFY;

Done_Field:
	field_ptr -> _field_check = GOOD_FIELD;
	if (_F_Field == 0)
		_F_Field = field_ptr;
	if (_F_Field > field_ptr)
		_F_Field = field_ptr;
	if (_L_Field < field_ptr)
		_L_Field = field_ptr;
	return (field_ptr);
}
