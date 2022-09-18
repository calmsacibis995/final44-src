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
#include <termio.h>
#include "vt.h"
#include "windows.h"
#include "fields.h"

/*
 *	corchar (field_ptr, c)
 *
 *	This function handles correction characters.  These are:
 *
 *		The user's kill character from ioctl () - erase the field.
 *
 *		CTRL(W) (control W) deletes the previous word.
 *
 *		The user's erase character from ioctl ().
 *
 *		CTRL(O) (control O) retrieves the previous line.
 *
 *		REFRESHC (control V) Verify the  screen by refreshining.
 *
 *		CLEARC (control C) clear the error window and messages
 *			out of the way.
 *
 *		CTRL(_) (control _) output the screen to the file screen.out
 *			This has to be enabled by changing the chartyp[CTRL(_)]
 *			to CORRECT and f_chartyp[CTRL(_)] to corchar.
 *		see #ifdef SCRN_DUMP below
 *
 *		CTRL(B) beginning of field.
 *
 *		CTRL(E) end of the field.
 *
 *		CTRL(L) left in the field.
 *
 *		CTRL(R) right in the field.
 */

extern struct termio    nttybuf;

#define XBREAK	0
#define	RUBOUT	0177

corchar (field_ptr, c)
register struct field_item *field_ptr;
char    c;
{
	int count;
	int f_length;
	int x;
	int y;
	char   rc;
	register char *ptr1;
	register char *ptr2;
	char string[FORM_BUF];

	rc = c;

	if (rc == nttybuf.c_cc[VERASE])
		rc = '#';

	if (rc == nttybuf.c_cc[VKILL])
		rc = '@';

	count = -1;
	switch (rc & 0377)
	{
		case CTRL(B):		/* Beginning of the field */
			field_ptr -> txcursor = field_ptr -> txbuf;
			break;

		case CTRL(E):		/* End of the field */
			field_ptr -> txcursor = field_ptr -> txptr;
			count = 0;
			goto Control_X;

		case CTRL(R):		/* Right in the field */
			if (field_ptr -> txcursor >= field_ptr -> txptr)
				break;
			count = 1;

Control_X:
		case CTRL(L):		/* Left in the field */
			/* Looks a little odd but it handles TAB's */
			if ((field_ptr -> txcursor + count) >= field_ptr -> txbuf)
			{
				field_ptr -> txcursor += count;
				if ((field_ptr -> txcursor + count) >=
					field_ptr -> txbuf)
				{
					if (*(field_ptr -> txcursor - 1) == '\\')
						field_ptr -> txcursor += count;
				}
				ptr1 = field_ptr -> txbuf;
				ptr2 = string;
				while (ptr1 < field_ptr -> txcursor)
				{
					*ptr2++ = *ptr1++;
				}
				*ptr2 = '\0';
			}
			break;

#ifdef SCREEN_DUMP
		case CTRL(_):	/* Dump the screen to a temporary file */
			{
				FILE *fp;

				fp = fopen ("screen.out", "w");
				SCRN_Dump (fp);
				fclose (fp);
			}
			break;
#endif SCREEN_DUMP

		case CTRL(U):		/* Erase or kill the field */
		case '@': 
		case XBREAK: 
			field_ptr -> txptr = field_ptr -> txbuf;
			field_ptr -> txcursor = field_ptr -> txbuf;
			w_xgo (field_ptr -> window, field_ptr -> x_pos, field_ptr -> y_pos);
			waxprintf (field_ptr -> window,
				field_ptr -> attribute | FAFIELD,
				 "%s", field_ptr -> fill_char);
			break;

		case CTRL(W):		/* Erase or Delete the last word */
			rc = TRUE;
			x = FALSE;
			while (rc)
			{
				if (field_ptr -> txcursor <= field_ptr -> txbuf)
					break;
				switch (*((field_ptr -> txcursor) - 1))
				{
				case '/':
				case ',':
				case '-':
				case '.':
				case '=':
				case '|':
				case ':':
				case ';':
				case '!':
					if (x)
					{
						rc = FALSE;
						continue;
					}
					x = TRUE;
					break;
				case ' ':
				case '\t':
					if (x)
					{
						rc = FALSE;
						continue;
					}
					if ((*((field_ptr -> txcursor) - 2) != ' ') &&
						 (*((field_ptr -> txcursor) - 2) != '\t'))
						rc = FALSE;
					break;
				default:
					x = TRUE;
				}
				txdel (field_ptr);
			}
			break;

		case CTRL(H):		/* Erase or delete the last character */
		case RUBOUT: 
		case '#': 
			txdel (field_ptr);
			break;

		case CTRL(O):		/* Overlay or retrieve the last line */
			w_xgo (field_ptr -> window, field_ptr -> x_pos, field_ptr -> y_pos);

			for (ptr1 = field_ptr -> txbuf, f_length = 0;
					((f_length < field_ptr -> length) &&
					(*ptr1) &&
					(chartyp[rc] != BREAK)) ; ptr1++)
			{
				f_length = fc_length (field_ptr -> y_pos, *ptr1, f_length);

				waxprintf (field_ptr -> window,
					field_ptr -> attribute | FAFIELD,
					"%c", *ptr1);
			}
			field_ptr -> txptr = ptr1;
			field_ptr -> txcursor = ptr1;
			break;

		case REFRESHC:		/* Quickly refresh the screen */
			Refresh ();
			break;

		case CLEARC:		/* Clear the error message and window */
			Push_Window (field_ptr -> errwin);
			Print_Message (field_ptr -> meswin, Mess_Attribute, " ");
			break;
	}

	if (field_ptr -> txptr < field_ptr -> txbuf)
	{
		field_ptr -> txflg |= TXBLR;
	}
	return (FALSE);
}
