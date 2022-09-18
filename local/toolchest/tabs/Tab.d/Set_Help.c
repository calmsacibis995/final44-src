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
 *	Set_Help (field_ptr, string, print_col, suppress, help_routine)
 *
 *	This procedure is used to change the help attributes of the specified
 *	field.
 *
 *		"string" is the new help string.  If string is 0 or "\0"
 *			then the standard system help line will be used.
 *			Standard system help in the way of filenames and
 *			keywords will be presented as usual - unless
 *			"suppress" is TRUE.
 *
 *		"print_col" is TRUE if the help messages are to be printed
 *			as one column (the default).  If print_col is FALSE
 *			the output is printed as a tight row.  Row style
 *			output is harder to read, but allows more information
 *			to be displayed at one time.
 *
 *		"suppress" is TRUE if you want the default system provided
 *			help information not to be presented.  If suppress
 *			is FALSE (the default) the standard system help
 *			will be provided.
 *
 *	If suppress is TRUE and string is 0 no help of any kind will given.
 *
 */

Set_Help (field_ptr, string, print_col, suppress, help_routine)
register struct field_item *field_ptr;
register char *string;
boole print_col;
boole suppress;
int (*help_routine) ();
{
	F_Ok (field_ptr, "Set_Help");

	if ((string != 0) && (*string != '\0'))
	{
		field_ptr -> fnhlp = string;
		field_ptr -> fnflg |= FNHLP;
	}
	else
	{
		field_ptr -> fnhlp = 0;
		field_ptr -> fnflg &= ~(FNHLP);
	}
	if (help_routine)
	{
		field_ptr -> help_routine = help_routine;
		field_ptr -> fnflg |= FNHLP;
	}
	else
	{
		field_ptr -> help_routine = 0;
		if (field_ptr -> fnhlp == 0)
			field_ptr -> fnflg &= ~(FNHLP);
	}

	if (print_col)
		field_ptr -> fnflg |= FNHLST;
	else
		field_ptr -> fnflg &= ~(FNHLST);

	if (suppress)
		field_ptr -> fnflg |= FNSDH;
	else
		field_ptr -> fnflg &= ~(FNSDH);
}
