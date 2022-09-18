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
 * strmatch - match shell file patterns
 *
 * derived from Korn shell gmatch()
 *
 * strmatch compares the string s with the shell pattern p
 * returns 1 for match, 0 otherwise
 */

strmatch(s, p)
register char	*p;
char		*s;
{
	register int	scc, c;

	while (scc = *s++) switch (c = *p++)
	{
	case '[':
		{
			int	ok = 0;
			int	lc = -1;
			int	notflag = 0;

			if (*p == '!')
			{
				notflag = 1;
				p++;
			}
			while (c = *p++)
			{
				if (c == ']' && lc >= 0) return(ok ? strmatch(s, p) : 0);
				else if (c == '-' && lc >= 0 && *p != ']')
				{
					/* character range */
					c = *p++;
					if (notflag)
					{
						if (lc > scc || scc > c) ok++;
						else return(0);
					}
					else if (lc < scc && scc <= c) ok++;
				}
				else
				{
					if (notflag)
					{
						if (scc != c) ok++;
						else return(0);
					}
					else if (scc == c) ok++;
					lc = c;
				}
			}
			return(0);
		}
	default:
		if (c != scc) return(0);
	case '?':
		break;
	case '*':
		/* several *'s are the same as one */
		while (*p == '*') p++;
		if (!*p) return(1);
		--s;
		c = *p;
		while(*s)
		{
			if (c != *s && *p != '?' && *p != '[') s++;
			else if (strmatch(s++, p)) return(1);
		}
		return(0);
	case '\0':
		return(!scc);
	}
	while (*p == '*') p++;
	return(!*p);
}

