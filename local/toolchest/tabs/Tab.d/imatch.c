/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*
 *	imatch(shorts,string,type,caseless)
 *
 *	This function returns true iff shorts is an initial part
 *	of string.  A string is an initial part of itself, and the
 *	null string is an initial part of all strings.
 *
 */

imatch (shorts, string, type, caseless)
register char  *shorts;
register char  *string;
int     type;
int	caseless;
{
	char    a;
	char    b;

	while (*shorts != '\0')
	{
		a = *shorts;
		b = *string;

		if (caseless)
		{
			a |= 040;
			b |= 040;
		}

		if (a != b)
			return (type ? 0 : (a - b));

		shorts++;
		string++;
	}
	return (type);
}
