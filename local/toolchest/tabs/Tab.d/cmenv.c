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
 *	cmenv (field_ptr)
 *
 *	This function looks for an environmental variable name.
 *	If the current field uniquely matches exactly one of the
 *	variables in the env. then the variable name is returned.
 *	If the variable name ends with a '=' then the value of the
 *	variable may be completed (if the user presses escape).
 *
 */

extern char   **environ;

cmenv (field_ptr)
struct field_item     *field_ptr;
{
	extern int strcmp ();
	register char **fmatch;
	register char **lmatch;
	char  **tfmatch;
	char  **tlmatch;
	char   *xenv_ptr;
	char   *error1;
	char   *error2;

	error1 = "More than one variable matches";
	error2 = "No variables match";

	if (!cm_start (field_ptr, error1, error2)) return;

	fmatch = environ;
	while (*fmatch != 0)
		fmatch++;
	gsort (environ, fmatch, strcmp);

	fmatch = environ;
	while ((*fmatch != 0) &&
			(imatch (field_ptr -> txbuf, *fmatch, 0, FALSE) > 0))
	{
		fmatch++;
	}

	lmatch = fmatch;
	while ((*lmatch != 0) &&
			(imatch (field_ptr -> txbuf, *lmatch, 1, FALSE) != 0))
	{
		lmatch++;
	}

	if (field_ptr -> cmflg & CMHLP)
	{
		tfmatch = fmatch;
		tlmatch = lmatch;
/*
 *	Nothing match code
 */
		if (((lmatch - fmatch) == 0) &&
			(*(field_ptr -> txbuf) != '\0'))
		{
			prhlp (field_ptr, "The current entry does not match any of the environmental variables.", FALSE, FALSE);

/*
 *	This piece of code will print all of the items if nothing matches
 */
			tfmatch = environ;
			tlmatch = tfmatch;
			while (*tlmatch != 0)
			{
				tlmatch++;
			}
		}

		while (tfmatch < tlmatch)
		{
			xenv_ptr = (char *) strchr (*tfmatch, '=');
			if (xenv_ptr != NULL)
				*xenv_ptr = '\0';
			prhlp (field_ptr, *(tfmatch++), TRUE, TRUE);
			if (xenv_ptr != NULL)
				*xenv_ptr = '=';
		}

		if ((field_ptr -> fnflg & FNHLP) == 0)
		{
			prhlp (field_ptr, "Enter an environmental variable name.", FALSE, FALSE);
		}

		field_ptr -> cmflg |= CMNOP;
		return;
	}

	switch (lmatch - fmatch)
	{
		case 0: 
			field_ptr -> cmflg |= CMNOP;
			error_fields = error2;
			return;

		case 1: 
			xenv_ptr = (char *) strchr (*fmatch, '=');
			if (xenv_ptr != NULL)
				*xenv_ptr = '\0';

			if (strchr (field_ptr -> txbuf, '='))
			{
				if (xenv_ptr != NULL)
					*xenv_ptr = '=';
			}
			complete (field_ptr, *fmatch);
			if (field_ptr -> cmflg & CMNOP)
			{
				error_fields = "Item specified is longer than the current field";
				return;
			}
			if ((*xenv_ptr == '=') &&
			    (strncmp (field_ptr -> txbuf, *fmatch,
				strlen (*fmatch)) != 0))
			{
				field_ptr -> cmflg |= CMNOP;
				error_fields = error2;
				return;
			}
			if (f_length (field_ptr -> y_pos, *fmatch) < field_ptr -> length)
				strcpy (field_ptr -> txbuf, *fmatch);
			if (xenv_ptr != NULL)
				*xenv_ptr = '=';
			if (field_ptr -> cmflg & CMCMP)
			{
				field_ptr -> cmflg |= CMREP;
			}
			return;

		default:
			xenv_ptr = (char *) strchr (*fmatch, '=');
			if (strchr (field_ptr -> txbuf, '=') == NULL)
			{
				if (xenv_ptr != NULL)
					*xenv_ptr = '\0';
			}
			if ((strncmp (field_ptr -> txbuf, *fmatch,
						strlen (*fmatch)) == 0) &&
					((field_ptr -> cmflg & CMCMP) == 0))
			{
				if (strchr (field_ptr -> txbuf, '='))
				{
					if (xenv_ptr != NULL)
						*xenv_ptr = '=';
				}

				if (f_length (field_ptr -> y_pos, *fmatch) < field_ptr -> length)
					strcpy (field_ptr -> txbuf, *fmatch);
				if (xenv_ptr != NULL)
					*xenv_ptr = '=';
				return;
			}
			if (xenv_ptr != NULL)
				*xenv_ptr = '=';

			field_ptr -> cmflg |= (CMNOP | CMNUQ);
			error_fields = error1;
	}
}

gsort(from, to, function)
char	*from[], *to[];
int (*function) ();
{
	int	k, m, n;
	register int	i, j;

	if ((n = to - from) <= 1)
		return;
	for (j = 1; j <= n; j *= 2)
		;
	for (m = 2 * j - 1; m /= 2; )
	{
		k = n - m;
		for (j = 0; j < k; j++)
		{
			for (i = j; i >= 0; i -= m)
			{
				register char **fromi;

				fromi = &from[i];
				if ((*function) (fromi[m], fromi[0]) > 0)
				{
					break;
				}
				else
				{
					char *s;

					s = fromi[m];
					fromi[m] = fromi[0];
					fromi[0] = s;
				}
			}
		}
	}
}
