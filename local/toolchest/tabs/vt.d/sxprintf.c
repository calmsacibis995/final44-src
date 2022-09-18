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
#include "vt.h"

seprintf (string, fmt, x)
char   *string;
char   *fmt;
unsigned        x;
{
	sxprintf (string, fmt, &x);	/* Depends on arg list format */
}

/* Internal printf formatter */

sxprintf (string, fmt, adx)
register char  *string;
register char  *fmt;
register unsigned int  *adx;
{
	int     c;
	int     width;

	if (fmt == NULL)
		fmt = "";

loop: 
	while ((c = *fmt++) != '%')
	{
		*string++ = c;
		if (c == '\0')
		{
			return;
		}
	}
	width = 0;
	c = *fmt++;
	if ((c >= '0') && (c <= '9'))
	{
		fmt = nscan (fmt - 1, &width);
		c = *fmt++;
	}

	switch (c)
	{
		case 'd': 
		case 'D': 
		case 'o': 
		case 'O': 
			{
				register int    b;
				long    n;
				long    n1;
				register int    i;
				char    dstack[20];

				b = (((c == 'o') || (c == 'O')) ? 8 : 10);
					/* number base */
				if ((c == 'o') || (c == 'd'))
				{
					n = (long) (*adx);
					if (n > 32768L)
						n = n - 65536L;
					/* sign correction */
				}
				else
				{
					n = *((long *) adx);
					adx += ((sizeof (n) - sizeof (i))
								/ sizeof (i));
				}
				i = 0;
				if (n < 0)
				{
					n = -n;
					*string++ = '-';
				}

				do
				{
					n1 = n / b;
					dstack[i++] = (short) (n - (n1 * b));
					n = n1;
				} while (n != 0);	/* figure number */

				if ((b == 8) && ((i != 1) || (dstack[0] != 0)))
					dstack[i++] = 0;
				while (i < width)
					dstack[i++] = 0;
				while (i > 0)
					*string++ = (dstack[--i] + '0');
				/* print number */
			}
			break;
		case 'P': 
			width *= SREGION;
			/* Fall through */
		case 'p': 
			while (width > 0)
			{
				*string++ = *NOP;
				width -= ttywarp;
			}
			adx--;
			break;
		case 's': 
			string = cpy_ret (string, (char *) * adx);
			break;
		case 'm': 
		case 'M': 
			{
				char   *cp;
				if (c=='m')
				{
					cp = &TMAP[width * (*adx)];
				}
				else
				{
					cp = &SMAP[width * (*adx)];
				}
				for (c = 0; c < width; c++)
				{
					if (*cp)
						*string++ = *cp++;
				}
			}
			break;
		case 'c': 
			c = *adx;
			if (c)
			{
				*string++ = c;
			}
			else
			{
				*string++ = '^';
				*string++ = '@';/* punt */
			}
			break;
		case '%': 
			*string++ = '%';
			adx--;
			break;
		default: 
			break;		/* character in printf */
	}
	adx++;
	goto loop;
}
