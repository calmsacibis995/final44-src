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
 *	cmnum (field_ptr)
 *
 *	At present this function parses any number.  The function
 *	behaves much like cmstr.  If a valid number is parsed
 *	the string is placed in the string pointed to by
 *	field_ptr -> txbuf.  Legal numbers may include one plus or
 *	one minus (not both), one period, and any number of digits.
 *	Range checking is done using integer mathematics.
 *
 *	fndfv contains the number of digits after the decimal point
 *	plus one.  Zero for integers.
 */

static int      decimal_part;

cmnum (field_ptr)
register struct field_item     *field_ptr;
{
	char    sbuf[FORM_BUF];
	char   *ptr;
	char   *error;

	error = "An illegal number was entered";

	if (!cm_start (field_ptr, error, error))
		return;

	if (field_ptr -> cmflg & CMHLP)
	{
		field_ptr -> cmflg |= CMNOP;

		if (field_ptr -> fndfv)
		{
			sprintf (sbuf,
					"Enter a decimal number with %d %s behind the decimal point.",
					field_ptr -> fndfv - 1,
					(field_ptr -> fndfv == 2) ? "digit" : "digits");

			prhlp (field_ptr, sbuf, FALSE, FALSE);
		}
		else
		{
			prhlp (field_ptr, "Enter an integer.", FALSE, FALSE);
		}
		if ((field_ptr -> keywords) && *(field_ptr -> keywords))
		{
			ptr = (char *) strchr (field_ptr -> keywords, ',');
			*ptr++ = '\0';
			sprintf (sbuf,
					"The number should also be greater than or equal to %s and less than or equal to %s.",
					field_ptr -> keywords, ptr);
			ptr--;
			*ptr = ',';
			prhlp (field_ptr, sbuf, FALSE, FALSE);
		}

		if (*(field_ptr -> txbuf) != '\0')
		{
			if (xnum (field_ptr -> txbuf, field_ptr -> length,
					field_ptr -> fndfv, FALSE) == 0)
				prhlp (field_ptr, "The current entry is not a legal number.", FALSE, FALSE);
			else
			if (chk_range (field_ptr -> txbuf,
					field_ptr -> keywords) == FALSE)
				prhlp (field_ptr, "The current entry is out side of the specified range.", FALSE, FALSE);
		}

		if ((field_ptr -> fnflg & FNHLP) == 0)
			prhlp (field_ptr, "Enter a number.", FALSE, FALSE);

		return;
	}

	if (xnum (field_ptr -> txbuf, field_ptr -> length, field_ptr -> fndfv, FALSE) == 0)
	{
		field_ptr -> cmflg |= CMNOP;
		error_fields = error;
		return;
	}
	else
	{
		if (field_ptr -> fndfv)
		{
			field_ptr -> txptr = &field_ptr -> txbuf[strlen (field_ptr -> txbuf)];
			if ((decimal_part == 0) &&
					(*(field_ptr -> txptr - 1) != '.'))
			{
				if ((field_ptr -> txptr + 1)
					< field_ptr -> txend)
					*((field_ptr -> txptr)++) = '.';
			}

			for (; decimal_part + 1 < field_ptr -> fndfv;
					decimal_part++)
			{
				if ((field_ptr -> txptr + 1)
					< field_ptr -> txend)
					*((field_ptr -> txptr)++) = '0';
			}
			*field_ptr -> txptr = '\0';
		}

		complete (field_ptr, field_ptr -> txbuf);
		if ((field_ptr -> keywords) &&
				(chk_range (field_ptr -> txbuf,
						field_ptr -> keywords) == FALSE))
		{
			field_ptr -> cmflg |= CMNOP;
			error_fields = "The number is outside the range";
			return;
		}
		if (field_ptr -> cmflg & CMCMP)
		{
			field_ptr -> cmflg |= CMREP;
		}
		return;
	}
}

/*
 * Verifies that p contains a legal number
 */
static int
xnum (p, length, integerp, interactive)
register char  *p;
int     length;
int     integerp;
int     interactive;
{
	register int    x_first = 0;
	char    x_minus = 0;
	char    x_plus = 0;
	char    x_dot = 0;
	int     p_test = 0;

	decimal_part = 0;

	if (!integerp)
		x_dot++;

	length -= integerp;

	for (; *p != '\0'; p++, x_first++)
	{
		switch (*p)
		{
			case '-': 
				if (x_minus)
					return (0);
				if (x_plus)
					return (0);
				if (x_first)
					return (0);
				x_minus++;
				if (interactive)
					p_test++;
				continue;
			case '+': 
				if (x_plus)
					return (0);
				if (x_minus)
					return (0);
				if (x_first)
					return (0);
				x_plus++;
				if (interactive)
					p_test++;
				continue;
			case '.': 
				if (x_dot)
					return (0);
				x_dot++;
				if (interactive)
					p_test++;
				continue;
			default: 
				if ((*p >= '0') && (*p <= '9'))
				{
					p_test++;
					if (x_dot && integerp)
					{
						decimal_part++;
						if (decimal_part >
								(integerp - 1))
							return (0);
					}
					if ((x_dot == 0) &&
							(x_first >= length))
						return (0);
					continue;
				}
				return (0);
		}
	}
	return (p_test);
}

/*
 *	read_num (field_ptr)
 *
 *	Simple minded numeric reader - keeping with the philosophy
 *	of the rest of the forms routines, this routine does not
 *	check the range.  Range checking is done after the field is
 *	marked as complete by the user.  This reader does however
 *	check for "legal" decimal numbers - number of digits after
 *	the decimal point - usefull for dollar amounts.
 *
 */

read_num (field_ptr)
struct field_item      *field_ptr;
{
	extern char    *copy_to_ptr ();
	register char  *resp_ptr;
	char   *error;
	char    response[FORM_BUF];
	int     rc;
	int     punc;

	error = "Numeric format mismatch ";

	*response = '\0';
	resp_ptr = copy_to_ptr (field_ptr -> txbuf, field_ptr -> txptr, response, FALSE, &punc);

	*resp_ptr = '\0';
	if ((*response) &&
			(xnum (response, field_ptr -> length, field_ptr -> fndfv, TRUE) == 0))
	{
		beep ();
		Print_Message (field_ptr -> meswin, Mess_Attribute, error, Help_Help_String);
	}

Read_Again: 
	rc = getachar (field_ptr);

	switch (chartyp[rc & 0377])
	{
		case NORMAL: 
			resp_ptr = copy_to_ptr (field_ptr -> txbuf,
					field_ptr -> txcursor, response, FALSE, &punc);
			if (punc == FALSE)
			{
				*resp_ptr++ = rc;
				resp_ptr = copy_to_ptr (field_ptr -> txcursor,
						field_ptr -> txptr, resp_ptr, TRUE, &punc);
			}
			*resp_ptr = '\0';
			if (xnum (response, field_ptr -> length,
						field_ptr -> fndfv, TRUE) == 0)
			{
				beep ();
				Print_Message (field_ptr -> meswin, Mess_Attribute, error, Help_Help_String);
				goto Read_Again;
			}
			Print_Message (field_ptr -> meswin, Mess_Attribute, "\0");
			break;

		case PUNC: 
		case BREAK: 
		case CORRECT: 
		case DSCARD: 
			break;
	}

	return (rc);
}

static char   *
copy_to_ptr (start, end, resp_ptr, notrim, punc)
char   *start;
register char  *end;
register char  *resp_ptr;
int     notrim;
int    *punc;
{
	register char  *txbuf_ptr;

	txbuf_ptr = start;
	while ((chartyp[*txbuf_ptr & 0377] == PUNC) &&
			(txbuf_ptr < end))
	{
		if (notrim)
			return (resp_ptr);
		txbuf_ptr++;
	}

	while ((txbuf_ptr < end) && (chartyp[*txbuf_ptr & 0377] != PUNC))
	{ 

		*resp_ptr++ = *txbuf_ptr++;
	}
	if (txbuf_ptr < end)
		*punc = TRUE;
	else
		*punc = FALSE;

	return (resp_ptr);
}

/*
 *
 *	chk_range (value, range)
 *
 *	This function checks that the number contained in "value" is within
 *	the range specified in "range".  All checking is done
 *	with integer mathematics.  This is to allow the code to be ported
 *	to Blit or BitGraph worlds.
 *
 *		chk_range ("-123.5", "-124,124.77")
 *
 */

static int
chk_range (value, range)
char   *value;
char   *range;
{
	register char  *ptr;
	register int    largest;

	int     lower_dec;
	int     lower_int;
	int     lower_pnts;

	int     upper_dec;
	int     upper_int;
	int     upper_pnts;

	int     value_dec;
	int     value_int;
	int     value_pnts;

	int    *iptr;
	int     neg = 0;

/*
 * Integer values for the values string
 *
 */
	ptr = value;
	if (*ptr == '+')
	{
		ptr++;
	}
	if (*ptr == '-')
	{
		neg++;
		ptr++;
	}

	for (iptr = &value_int, value_int = 0, value_dec = 0, value_pnts = 100;
			*ptr; ptr++)
	{
		if (*ptr == '.')
		{
			iptr = &value_dec;
			value_pnts = 0;
			continue;
		}
		(*iptr) = (*iptr) * 10 + *ptr - '0';
		value_pnts++;
	}

	if (neg)
	{
		value_int = -value_int;
		value_dec = -value_dec;
		neg = 0;
	}

/*
 * Integer values for the lower bound
 *
 */
	ptr = range;
	if (*ptr == '+')
	{
		ptr++;
	}
	if (*ptr == '-')
	{
		neg++;
		ptr++;
	}

	for (iptr = &lower_int, lower_int = 0, lower_dec = 0, lower_pnts = 100;
			*ptr != ','; ptr++)
	{
		if (*ptr == '.')
		{
			iptr = &lower_dec;
			lower_pnts = 0;
			continue;
		}
		(*iptr) = (*iptr) * 10 + *ptr - '0';
		lower_pnts++;
	}

	if (neg)
	{
		lower_int = -lower_int;
		lower_dec = -lower_dec;
		neg = 0;
	}

/*
 * Integer values for the upper bound
 *
 */
	ptr++;
	if (*ptr == '+')
	{
		ptr++;
	}
	if (*ptr == '-')
	{
		neg++;
		ptr++;
	}

	for (iptr = &upper_int, upper_int = 0, upper_dec = 0, upper_pnts = 100;
			*ptr; ptr++)
	{
		if (*ptr == '.')
		{
			iptr = &upper_dec;
			upper_pnts = 0;
			continue;
		}
		(*iptr) = (*iptr) * 10 + *ptr - '0';
		upper_pnts++;
	}

	if (neg)
	{
		upper_int = -upper_int;
		upper_dec = -upper_dec;
	}

/*
 * Normalize the decimal part
 *
 */
	if (value_pnts > 99)
		value_pnts = 0;
	if (lower_pnts > 99)
		lower_pnts = 0;
	if (upper_pnts > 99)
		upper_pnts = 0;

	largest = value_pnts;
	if (lower_pnts > largest)
		largest = lower_pnts;
	if (upper_pnts > largest)
		largest = upper_pnts;

	while (value_pnts < largest)
	{
		value_dec *= 10;
		value_pnts++;
	}

	while (lower_pnts < largest)
	{
		lower_dec *= 10;
		lower_pnts++;
	}

	while (upper_pnts < largest)
	{
		upper_dec *= 10;
		upper_pnts++;
	}

/*
 * Perform the comparison
 *
 */
	if (value_int >= lower_int)
	{
		if ((value_int == lower_int) &&
				(value_dec < lower_dec))
		{
			return (FALSE);
		}
	}
	else
		return (FALSE);

	if (value_int <= upper_int)
	{
		if ((value_int == upper_int) &&
				(value_dec > upper_dec))
		{
			return (FALSE);
		}
	}
	else
		return (FALSE);

	return (TRUE);
}
