h34858
s 00002/00002/00070
d D 8.1 93/06/04 13:06:38 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00003/00067
d D 5.2 91/02/24 14:32:50 bostic 2 1
c add ANSI prototypes
e
s 00070/00000/00000
d D 5.1 90/10/30 12:41:30 bostic 1 0
c date and time created 90/10/30 12:41:30 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <unistd.h>
I 2
#include <stdlib.h>
E 2

/*
 * The SVID interface to getsubopt provides no way of figuring out which
 * part of the suboptions list wasn't matched.  This makes error messages
D 2
 * tricky...  The extern variable suboptarg is a pointer to the token which
 * didn't match.
E 2
I 2
 * tricky...  The extern variable suboptarg is a pointer to the token
 * which didn't match.
E 2
 */
char *suboptarg;

getsubopt(optionp, tokens, valuep)
D 2
	register char **optionp, **tokens, **valuep;
E 2
I 2
	register char **optionp, **valuep;
	register char * const *tokens;
E 2
{
	register int cnt;
	register char *p;

	suboptarg = *valuep = NULL;

	if (!optionp || !*optionp)
		return(-1);

	/* skip leading white-space, commas */
	for (p = *optionp; *p && (*p == ',' || *p == ' ' || *p == '\t'); ++p);

	if (!*p) {
		*optionp = p;
		return(-1);
	}

	/* save the start of the token, and skip the rest of the token. */
	for (suboptarg = p;
	    *++p && *p != ',' && *p != '=' && *p != ' ' && *p != '\t';);

	if (*p) {
		/*
		 * If there's an equals sign, set the value pointer, and
		 * skip over the value part of the token.  Terminate the
		 * token.
		 */
		if (*p == '=') {
			*p = '\0';
			for (*valuep = ++p;
			    *p && *p != ',' && *p != ' ' && *p != '\t'; ++p);
			if (*p) 
				*p++ = '\0';
		} else
			*p++ = '\0';
		/* Skip any whitespace or commas after this token. */
		for (; *p && (*p == ',' || *p == ' ' || *p == '\t'); ++p);
	}

	/* set optionp for next round. */
	*optionp = p;

	for (cnt = 0; *tokens; ++tokens, ++cnt)
		if (!strcmp(suboptarg, *tokens))
			return(cnt);
	return(-1);
}
E 1
