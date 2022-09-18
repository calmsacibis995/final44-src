h35663
s 00002/00002/00187
d D 8.1 93/06/06 15:56:53 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00023/00023/00166
d D 5.2 93/04/30 16:58:49 bostic 2 1
c minor integration in 4BSD source tree
e
s 00189/00000/00000
d D 5.1 93/04/30 13:30:02 muller 1 0
c date and time created 93/04/30 13:30:02 by muller
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
E 2
I 2
 * Copyright (c) 1991 Keith Muller.
D 3
 * Copyright (c) 1993 The Regents of the University of California.
E 2
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
I 2
 * This code is derived from software contributed to Berkeley by
 * Keith Muller of the University of California, San Diego.
 *
E 2
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 2
#include <stdio.h>
E 2
#include <ctype.h>
I 2
#include <stdio.h>
E 2
#include <stdlib.h>
#include <string.h>
I 2

E 2
#include "extern.h"

/*
 * egetopt:	get option letter from argument vector (an extended
 *		version of getopt).
 *
 * Non standard additions to the ostr specs are:
 * 1) '?': immediate value following arg is optional (no white space
 *    between the arg and the value)
 * 2) '#': +/- followed by a number (with an optional sign but
 *    no white space between the arg and the number). The - may be
 *    combined with other options, but the + cannot.
 */

int	eopterr = 1;		/* if error message should be printed */
int	eoptind = 1;		/* index into parent argv vector */
int	eoptopt;		/* character checked for validity */
char	*eoptarg;		/* argument associated with option */

#define	BADCH	(int)'?'
#define	EMSG	""

D 2
#if __STDC__
E 2
int
D 2
egetopt(int nargc, char * const *nargv, const char *ostr)
#else
int
E 2
egetopt(nargc, nargv, ostr)
	int nargc;
D 2
	char **nargv;
	char *ostr;
#endif
E 2
I 2
	char * const *nargv;
	const char *ostr;
E 2
{
	static char *place = EMSG;	/* option letter processing */
	register char *oli;		/* option letter list index */
	static int delim;		/* which option delimeter */
	register char *p;
	static char savec = '\0';

	if (savec != '\0') {
		*place = savec;
		savec = '\0';
	}

	if (!*place) {
		/*
		 * update scanning pointer
		 */
		if ((eoptind >= nargc) ||
		    ((*(place = nargv[eoptind]) != '-') && (*place != '+'))) {
			place = EMSG;
D 2
			return(EOF);
E 2
I 2
			return (EOF);
E 2
		}

		delim = (int)*place;
		if (place[1] && *++place == '-' && !place[1]) {
			/*
			 * found "--"
			 */
			++eoptind;
			place = EMSG;
D 2
			return(EOF);
E 2
I 2
			return (EOF);
E 2
		}
	}

	/*
	 * check option letter
	 */
	if ((eoptopt = (int)*place++) == (int)':' || (eoptopt == (int)'?') ||
D 2
	    !(oli = index(ostr, eoptopt))) {
E 2
I 2
	    !(oli = strchr(ostr, eoptopt))) {
E 2
		/*
		 * if the user didn't specify '-' as an option,
		 * assume it means EOF when by itself.
		 */
		if ((eoptopt == (int)'-') && !*place)
D 2
			return(EOF);
		if (index(ostr, '#') && (isdigit(eoptopt) ||
E 2
I 2
			return (EOF);
		if (strchr(ostr, '#') && (isdigit(eoptopt) ||
E 2
		    (((eoptopt == (int)'-') || (eoptopt == (int)'+')) &&
		      isdigit(*place)))) {
			/*
			 * # option: +/- with a number is ok
			 */
			for (p = place; *p != '\0'; ++p) {
				if (!isdigit(*p))
					break;
			}
			eoptarg = place-1;

			if (*p == '\0') {
				place = EMSG;
				++eoptind;
			} else {
				place = p;
				savec = *p;
				*place = '\0';
			}
D 2
			return(delim);
E 2
I 2
			return (delim);
E 2
		}

		if (!*place)
			++eoptind;
		if (eopterr) {
D 2
			if (!(p = rindex(*nargv, '/')))
E 2
I 2
			if (!(p = strrchr(*nargv, '/')))
E 2
				p = *nargv;
			else
				++p;
			(void)fprintf(stderr, "%s: illegal option -- %c\n",
			    p, eoptopt);
		}
D 2
		return(BADCH);
E 2
I 2
		return (BADCH);
E 2
	}
	if (delim == (int)'+') {
		/*
		 * '+' is only allowed with numbers
		 */
		if (!*place)
			++eoptind;
		if (eopterr) {
D 2
			if (!(p = rindex(*nargv, '/')))
E 2
I 2
			if (!(p = strrchr(*nargv, '/')))
E 2
				p = *nargv;
			else
				++p;
			(void)fprintf(stderr,
				"%s: illegal '+' delimiter with option -- %c\n",
				p, eoptopt);
		}
D 2
		return(BADCH);
E 2
I 2
		return (BADCH);
E 2
	}
	++oli;
	if ((*oli != ':') && (*oli != '?')) {
		/*
		 * don't need argument
		 */
		eoptarg = NULL;
		if (!*place)
			++eoptind;
D 2
		return(eoptopt);
E 2
I 2
		return (eoptopt);
E 2
	}

	if (*place) {
		/*
		 * no white space
		 */
		eoptarg = place;
	} else if (*oli == '?') {
		/*
		 * no arg, but NOT required
		 */
		eoptarg = NULL;
	} else if (nargc <= ++eoptind) {
		/*
		 * no arg, but IS required
		 */
		place = EMSG;
		if (eopterr) {
D 2
			if (!(p = rindex(*nargv, '/')))
E 2
I 2
			if (!(p = strrchr(*nargv, '/')))
E 2
				p = *nargv;
			else
				++p;
			(void)fprintf(stderr,
			    "%s: option requires an argument -- %c\n", p,
			    eoptopt);
		}
D 2
		return(BADCH);
E 2
I 2
		return (BADCH);
E 2
	} else {
		/*
		 * arg has white space
		 */
		eoptarg = nargv[eoptind];
	}
	place = EMSG;
	++eoptind;
D 2
	return(eoptopt);
E 2
I 2
	return (eoptopt);
E 2
}
E 1
