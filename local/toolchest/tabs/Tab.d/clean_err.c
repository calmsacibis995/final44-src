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
#include "fields.h"

/*
 *	clean_err (field_ptr)
 *
 *	This procedure is called when the current field can not be
 *	parsed.  The input pointer is set to the begining of the
 *	field which did not parse so that a correct value may be
 *	typed.  The terminal's bell is rung to notify the user that
 *	an error has been detected.  The users input is then read into
 *	the current field.  (Note that ^L may be used to retrieve the
 *	discarded portion of the line if this is desired.)
 *
 *	Whenver CMNOP is set for field_ptr -> cmflg the global variable
 *	error_fields must be set to point to the error string.
 *	Not too neat, but quicker than figuring out what type of error
 *	occured based on the field type.
 *
 */

clean_err (field_ptr)
register struct field_item *field_ptr;
{
	register char   *Help;
	char sbuf[FORM_BUF];

	Help = Help_Help_String;

	if (error_fields == 0)
	{
		Print_Message (field_ptr -> meswin, Mess_Attribute, "Error of some kind %s", Help);

		beep ();

		field_ptr -> cmflg &= ~(CMHLP | CMCMP | CMEOL | CMNUQ);

		error_fields = 0;

		return;
	}

	if ((field_ptr -> cmflg & CMCMP) == 0)
	{
		sprintf (sbuf, "%s %s",
				error_fields,
				Help);
	}
	else
	{
		sprintf (sbuf, "%s - %s %s",
				"Cannot complete",
				error_fields,
				Help);
	}

	Print_Message (field_ptr -> meswin, Mess_Attribute, "%s", sbuf);

	beep ();

	field_ptr -> cmflg &= ~(CMHLP | CMCMP | CMEOL | CMEOF | CMNUQ);

	while (field_ptr -> fnflg & FNALT)
	{
		field_ptr = field_ptr -> fnalt;
		field_ptr -> cmflg &= ~(CMHLP | CMCMP | CMEOL | CMEOF | CMNUQ);
	}

	error_fields = 0;
}
