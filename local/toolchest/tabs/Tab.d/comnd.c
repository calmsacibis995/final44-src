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
 *	comnd (field_ptr)
 *
 *	The function provides the low level control for reading input
 *	for fields and subsequently verifying that the input is valid.
 *	See fields.h for a more detailed description of flags and
 *	internals.
 *
 */

comnd (field_ptr)
register struct field_item *field_ptr;
{
	extern int hlp_status;
	register struct field_item    *field_star;
	char *first_error;

	do
	{
		field_star = field_ptr;

		if (field_star -> type != CMINI)
		{
			field_star -> cmflg &= ~(CMVERIFY);
			getatm (field_star);
			if ((field_star -> cmflg & CMIBO) ||
					(field_star -> cmflg & CMABO))
			{
				Print_Message (field_star -> meswin, 0,
						"***Buffer overflow***");
			}

			if (field_star -> cmflg & CMREP)
			{
				if (field_ptr -> fnflg & FNALT)
				{
					field_ptr -> txflg = field_star -> txflg;
					field_ptr -> txptr = field_star -> txptr;
					field_ptr -> cmflg = field_star -> cmflg;
				}
				reset ();
			}
		}

		if ((field_star -> cmflg & CMNOP) == 0)
		{

			hlp_status = HLP_OPTIONS;
			error_fields = 0;
			first_error = 0;

			do
			{
				field_star -> cmflg &= ~(CMNOP | CMNUQ);

				if (field_star -> type == CMREGN)
				{
					struct field_item *f[1];
					f[0] = field_star;
					Get_List (f, 1, FALSE, FALSE);
					return;
				}

				if ((int) field_star -> type == 0)
				{
					Print_Message (field_star -> meswin, 0,
						    "Unknown field type.");
					field_star -> cmflg |= CMNOP;
					return;
				}

				(*field_star -> type ) (field_star);

				if ((error_fields) && (first_error == 0))
				{
					if (field_star -> fnerr)
						first_error = field_star -> fnerr;
					else
						first_error = error_fields;
				}

				if ((field_star -> cmflg & CMHLP) &&
					(field_star -> fnflg & FNHLP))
				{
					if (field_star -> help_routine)
						(*field_star -> help_routine ) (field_star);
					if (field_star -> fnhlp)
					{
						prhlp (field_star, field_star -> fnhlp, FALSE, FALSE);
					}
				}

				if (field_star -> cmflg & CMREP)
				{
					if (field_ptr -> fnflg & FNALT)
					{
						field_ptr -> txflg = field_star -> txflg;
						field_ptr -> txptr = field_star -> txptr;
						field_ptr -> cmflg = field_star -> cmflg;
					}
					reset ();
				}

				if ((field_star -> fnflg & FNSNUC) &&
						(field_star -> cmflg & CMNUQ))
					break;

			} while ((field_star -> fnflg & FNALT) &&
				(field_star -> cmflg & (CMNOP | CMHLP)) &&
				(
				field_star -> fnalt -> txflg = field_star -> txflg,
				field_star -> fnalt -> txbuf = field_star -> txbuf,
				field_star -> fnalt -> txptr = field_star -> txptr,
				field_star -> fnalt -> txend = field_star -> txend,
				field_star -> fnalt -> cmflg = field_star -> cmflg,
				field_star -> fnalt -> window = field_star -> window,
				field_star -> fnalt -> errwin = field_star -> errwin,
				field_star -> fnalt -> meswin = field_star -> meswin,
				field_star = field_star -> fnalt,
				hlp_status |= HLP_OR
				));

		}

		if ((field_star -> cmflg & CMNOP) &&
				((field_star -> cmflg & CMHLP) == 0))
		{
			field_ptr -> cmflg = field_star -> cmflg;
			error_fields = first_error;
			clean_err (field_ptr);
		}

	} while (field_star -> cmflg & CMNOP);
	field_ptr -> type_used = field_star -> type;
	field_ptr -> cmflg |= CMVERIFY;
}
