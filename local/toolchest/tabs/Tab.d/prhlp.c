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
 *	prhlp (field_ptr, message, indent, list_item)
 *
 *	This procedure breaks the help messages into line sized pieces for
 *	_prhlp ().
 *
 *	_prhlp (field_ptr, message, indent)
 *
 *	This procedure prints a help message in the fields error window.
 *	This procedure also provides -more- style processing when the window
 *	has been filled with text.
 *
 */

extern int     hlp_status;		/* Flags from comnd () */
static int     hlp_cnt;			/* Number of lines printed */

static int
_prhlp (field_ptr, message, indent)
register struct field_item     *field_ptr;
register char  *message;
int indent;
{
	static int dont_print;

	if ((message == 0) || (*message == '\0'))
		return;

	if (field_ptr -> cmflg & CMHLP)
	{
		if (hlp_status & HLP_OPTIONS)
		{
			hlp_cnt = 1;
			Print_Help_Window (field_ptr, 0, " Options:\n");
			hlp_status &= ~(HLP_OPTIONS | HLP_OR);
			dont_print = do_more (field_ptr);
		}
		else
		if (hlp_status & HLP_OR)
		{
			hlp_status &= ~(HLP_OR);
			if (dont_print) return;
			hlp_cnt++;
			Print_Help_Window (field_ptr, 0, " or:\n");
			dont_print = do_more (field_ptr);
		}

		if (dont_print) return;

		if (*message == '\n')
		{
			hlp_cnt++;
			Print_Help_Window (field_ptr, 0, "%s", message);
		}
		else
		{
			if (indent)	/* add a Tab */
				Print_Help_Window (field_ptr, 0, "\011%s", message);
			else
				Print_Help_Window (field_ptr, 0, "%s", message);
		}

		dont_print = do_more (field_ptr);
	}
}

static int
do_more (field_ptr)
struct field_item *field_ptr;
{
	int rc;
	int x;

	if (field_ptr -> errwin -> _type_scroll == FALSE)
	{
		if (field_ptr -> errwin -> _x_pos <
			(field_ptr -> errwin -> _bot_x -
			 field_ptr -> errwin -> _top_x - 1))
			return (FALSE);
	}
	else
	if (hlp_cnt < (field_ptr -> errwin -> _bot_x -
			field_ptr -> errwin -> _top_x - 1))
		return (FALSE);

	while (TRUE)
	{
		Print_Help_Window (field_ptr, 0, "-more-");
		rc = getachar (0);
		w_xgo (field_ptr -> errwin,
			field_ptr -> errwin -> _x_pos, 0);
		wclrl (field_ptr -> errwin);

		switch (rc)
		{
		case REFRESHC:	/* Quick Refresh */
			Refresh ();
			continue;

		case '?':
			if (field_ptr -> errwin -> _type_scroll == FALSE)
			{
				x = field_ptr -> errwin -> _x_pos;
				w_xgo (field_ptr -> errwin, 0, 0);
			}
			hlp_cnt = 1;
			prhlp (field_ptr,
	"Enter `q' to quit printing or any other character to continue.",
				FALSE, FALSE);
	
			if (field_ptr -> errwin -> _type_scroll == FALSE)
			{
				w_xgo (field_ptr -> errwin, x, 0);
				wclrl (field_ptr -> errwin);
			}
			continue;
	
		case CLEARC:		/* Clear the error window */
			Push_Window (field_ptr -> errwin);

		case 'q':		/* Quit - No More Messages */
			return (TRUE);
		}

		break;
	}

	hlp_cnt = 1;

	if (field_ptr -> errwin -> _type_scroll == FALSE)
	{
		Print_Help_Window (field_ptr, 0, "-continued-");
		w_xgo (field_ptr -> errwin, 0, 0);
		wclrl (field_ptr -> errwin);
		w_xgo (field_ptr -> errwin, 0, 0);
	}

	return (FALSE);
}

prhlp (field_ptr, message, indent, list_item)
register struct field_item     *field_ptr;
register char  *message;
boole indent;
boole list_item;
{
	int     length;
	int     t_length;
	int	y;
	char   *ptr;
	char   *optr;
	char   *bptr;
	char   *lbptr;
	char    ch;

	if ((message == 0) || (*message == '\0'))
		return;

	if ((field_ptr -> cmflg & CMHLP) == 0) return;

	t_length = field_ptr -> errwin -> _bot_y - field_ptr -> errwin -> _top_y - 1;
	if ((field_ptr -> fnflg & FNHLST) == 0)
	{
		if ((!list_item) &&
			((length = field_ptr -> errwin -> _y_pos) != 0))
		{
			_prhlp (field_ptr, "\n", indent);
		}
	}
	else
	if ((hlp_status & HLP_OPTIONS) == 0)
	{
		if ((length = field_ptr -> errwin -> _y_pos) != 0)
		{
			_prhlp (field_ptr, "\n", indent);
		}
	}
	if (field_ptr -> errwin -> _depth < INVISIBLE)
		length = field_ptr -> errwin -> _y_pos;
	else
		length = 0;

	if (indent)
		length = fc_length (0, CTRL(I), length);

	ptr = message;
	optr = ptr;
	bptr = 0;
	lbptr = 0;
	while (*ptr)
	{
		length = fc_length (0, *ptr, length);
		if ((length >= t_length) ||
			(*ptr == '\n'))
		{
			if (*ptr == '\n')
				bptr = 0;

			if (bptr == 0)
			{
				_prhlp (field_ptr, "\n", indent);
				ch = *ptr;
				*ptr = '\0';
				y = f_length (0, optr);
				if (indent)
					y = fc_length (0, CTRL(I), y);

				if (y >= t_length)
				{
					_prhlp (field_ptr, optr, indent);
					length = field_ptr -> errwin -> _y_pos;
					if (length >= t_length)
					{
						_prhlp (field_ptr, "\n", indent);
					}
				}
				else
				{
					length = y;
					*ptr++ = ch;
					continue;
				}
			}
			else
			{
				ch = *bptr;
				*bptr = '\0';
				_prhlp (field_ptr, optr, indent);
				ptr = bptr;
				_prhlp (field_ptr, "\n", indent);
			}

			length = field_ptr -> errwin -> _y_pos;

			if (indent)
				length = fc_length (0, CTRL(I), length);

			*ptr = ch;
			while (*ptr == ' ')
				ptr++;
			optr = ptr;
			bptr = 0;
		}

		if (*ptr == ' ')
		{
			if (lbptr < ptr)
			{
				bptr = ptr;
				lbptr = bptr;
				while (*lbptr == ' ')
				{
					lbptr++;
				}
			}
		}

		ptr++;
	}

	if (ptr > optr)
		_prhlp (field_ptr, optr, indent);

	if (!list_item)
		_prhlp (field_ptr, "\n", indent);
}
