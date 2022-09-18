h23934
s 00004/00004/00087
d D 8.3 95/04/27 13:52:32 bostic 17 16
c POSIX.2 has changed getopt to return -1 instead of EOF (to decouple
c getopt() from standard i/o).  This change is more pedantic than
c functional as EOF is defined to be -1.
c Also, POSIX.2 says that getopt lives in unistd.h , not stdlib.h.
c From: "J.T. Conklin" <jtc@sun-lamp.cs.berkeley.edu>
e
s 00019/00027/00072
d D 8.2 94/04/02 09:01:34 bostic 16 15
c use __progname instead of argv[0] for error messages
e
s 00002/00002/00097
d D 8.1 93/06/04 13:06:29 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00003/00091
d D 5.1 92/07/06 13:48:47 marc 14 13
c add optreset global for resetting state of getopt (for using multiple times in the same program).
e
s 00006/00002/00088
d D 4.13 91/02/23 10:11:09 donn 13 12
c Changes for prototype declarations.
e
s 00001/00011/00089
d D 4.12 90/06/01 14:44:57 bostic 12 11
c new copyright notice
e
s 00004/00001/00096
d D 4.11 90/02/20 12:06:34 bostic 11 10
c reset pointer so can call multiple times; bug report 4.3BSD-tahoe/lib/29
e
s 00006/00000/00091
d D 4.10 89/12/14 10:41:09 bostic 10 9
c bug from Sun (Don Cragun).  If '-' wasn't specified as a possible
c option, return EOF, not an error.  For compatibility with System V.
e
s 00013/00004/00078
d D 4.9 89/06/23 17:03:34 bostic 9 8
c don't print out entire pathname in error messages
e
s 00009/00011/00073
d D 4.8 89/03/05 12:26:56 bostic 8 7
c lint; if using getopt, probably using stdio -- simplify
e
s 00010/00005/00074
d D 4.7 88/06/27 18:25:31 bostic 7 6
c install approved copyright notice
e
s 00011/00012/00068
d D 4.6 88/04/19 11:16:10 bostic 6 5
c allow a single '-' to be specified
e
s 00009/00003/00071
d D 4.5 87/11/24 15:57:15 bostic 5 4
c Berkeley code, fix copyright
e
s 00033/00020/00041
d D 4.4 87/09/04 18:57:13 bostic 4 3
c fix opterr usage; bug report 4.3BSD/lib/86; reformat
e
s 00002/00002/00059
d D 4.3 86/03/09 19:33:24 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00003/00003/00058
d D 4.2 85/10/23 19:15:34 mckusick 2 1
c fix from keith@seismo.CSS.GOV
e
s 00061/00000/00000
d D 4.1 85/05/30 13:54:43 mckusick 1 0
c date and time created 85/05/30 13:54:43 by mckusick
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
D 15
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.
E 15
I 15
D 16
 * Copyright (c) 1987, 1993
E 16
I 16
 * Copyright (c) 1987, 1993, 1994
E 16
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
D 12
 * Redistribution and use in source and binary forms are permitted
D 7
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 7
I 7
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 7
E 5
 */

D 3
#ifndef lint
E 3
I 3
#if defined(LIBC_SCCS) && !defined(lint)
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
D 6
#endif LIBC_SCCS and not lint
E 6
I 6
#endif /* LIBC_SCCS and not lint */
E 6
E 3

#include <stdio.h>
I 13
#include <stdlib.h>
#include <string.h>
E 13

D 16
/*
 * get option letter from argument vector
 */
E 16
D 2
int	opterr = 1,		/* useless, never set or used */
E 2
I 2
int	opterr = 1,		/* if error message should be printed */
E 2
	optind = 1,		/* index into parent argv vector */
D 14
	optopt;			/* character checked for validity */
E 14
I 14
	optopt,			/* character checked for validity */
	optreset;		/* reset getopt */
E 14
char	*optarg;		/* argument associated with option */

D 6
#define BADCH	(int)'?'
#define EMSG	""
D 2
#define tell(s)	fputs(*nargv,stderr);fputs(s,stderr); \
		fputc(optopt,stderr);fputc('\n',stderr);return(BADCH);
E 2
I 2
D 4
#define tell(s)	if (opterr) {fputs(*nargv,stderr);fputs(s,stderr); \
		fputc(optopt,stderr);fputc('\n',stderr);return(BADCH);}
E 4
I 4
#define tell(s)	{ \
E 6
I 6
#define	BADCH	(int)'?'
I 14
#define	BADARG	(int)':'
E 14
#define	EMSG	""
D 8
#define	tell(s)	{ \
E 6
	if (opterr) { \
		fputs(*nargv, stderr); \
		fputs(s, stderr); \
		fputc(optopt, stderr); \
		fputc((int)'\n', stderr); \
	} \
	return(BADCH); \
}
E 8
E 4
E 2

I 16
/*
 * getopt --
 *	Parse argc/argv argument vector.
 */
E 16
I 13
int
E 13
D 4
getopt(nargc,nargv,ostr)
int	nargc;
char	**nargv,
	*ostr;
E 4
I 4
getopt(nargc, nargv, ostr)
D 6
	int	nargc;
	char	**nargv, *ostr;
E 6
I 6
	int nargc;
D 13
	char **nargv, *ostr;
E 13
I 13
	char * const *nargv;
	const char *ostr;
E 13
E 6
E 4
{
I 16
	extern char *__progname;
E 16
D 4
	static char	*place = EMSG;	/* option letter processing */
	register char	*oli;		/* option letter list index */
E 4
I 4
D 6
	static char	*place = EMSG;		/* option letter processing */
	register char	*oli;			/* option letter list index */
E 4
	char	*index();
E 6
I 6
	static char *place = EMSG;		/* option letter processing */
D 16
	register char *oli;			/* option letter list index */
D 9
	char *index();
E 9
I 9
D 13
	char *p, *index(), *rindex();
E 13
I 13
	char *p;
E 16
I 16
	char *oli;				/* option letter list index */
E 16
E 13
E 9
E 6

D 4
	if(!*place) {			/* update scanning pointer */
		if(optind >= nargc || *(place = nargv[optind]) != '-' || !*++place) return(EOF);
		if (*place == '-') {	/* found "--" */
E 4
I 4
D 14
	if (!*place) {				/* update scanning pointer */
E 14
I 14
	if (optreset || !*place) {		/* update scanning pointer */
		optreset = 0;
E 14
D 6
		if (optind >= nargc || *(place = nargv[optind]) != '-' ||
		    !*++place)
E 6
I 6
D 11
		if (optind >= nargc || *(place = nargv[optind]) != '-')
E 11
I 11
		if (optind >= nargc || *(place = nargv[optind]) != '-') {
			place = EMSG;
E 11
E 6
D 16
			return(EOF);
E 16
I 16
D 17
			return (EOF);
E 17
I 17
			return (-1);
E 17
E 16
I 11
		}
E 11
D 6
		if (*place == '-') {		/* found "--" */
E 6
I 6
		if (place[1] && *++place == '-') {	/* found "--" */
E 6
E 4
			++optind;
I 11
			place = EMSG;
E 11
D 16
			return(EOF);
E 16
I 16
D 17
			return (EOF);
E 17
I 17
			return (-1);
E 17
E 16
		}
D 4
	}				/* option letter okay? */
	if ((optopt = (int)*place++) == (int)':' || !(oli = index(ostr,optopt))) {
		if(!*place) ++optind;
E 4
I 4
	}					/* option letter okay? */
	if ((optopt = (int)*place++) == (int)':' ||
D 16
	    !(oli = index(ostr, optopt))) {
E 16
I 16
	    !(oli = strchr(ostr, optopt))) {
E 16
I 10
		/*
		 * if the user didn't specify '-' as an option,
D 17
		 * assume it means EOF.
E 17
I 17
		 * assume it means -1.
E 17
		 */
		if (optopt == (int)'-')
D 16
			return(EOF);
E 16
I 16
D 17
			return (EOF);
E 17
I 17
			return (-1);
E 17
E 16
E 10
		if (!*place)
			++optind;
E 4
D 8
		tell(": illegal option -- ");
E 8
I 8
D 9
		if (opterr)
E 9
I 9
D 14
		if (opterr) {
E 14
I 14
D 16
		if (opterr && *ostr != ':') {
E 14
			if (!(p = rindex(*nargv, '/')))
				p = *nargv;
			else
				++p;
E 9
			(void)fprintf(stderr, "%s: illegal option -- %c\n",
D 9
			    *nargv, optopt);
E 9
I 9
			    p, optopt);
		}
E 9
		return(BADCH);
E 16
I 16
		if (opterr && *ostr != ':')
			(void)fprintf(stderr,
			    "%s: illegal option -- %c\n", __progname, optopt);
		return (BADCH);
E 16
E 8
	}
D 4
	if (*++oli != ':') {		/* don't need argument */
E 4
I 4
	if (*++oli != ':') {			/* don't need argument */
E 4
		optarg = NULL;
D 4
		if (!*place) ++optind;
E 4
I 4
		if (!*place)
			++optind;
E 4
	}
D 4
	else {				/* need an argument */
		if (*place) optarg = place;	/* no white space */
E 4
I 4
	else {					/* need an argument */
		if (*place)			/* no white space */
			optarg = place;
E 4
		else if (nargc <= ++optind) {	/* no arg */
			place = EMSG;
I 9
D 16
			if (!(p = rindex(*nargv, '/')))
				p = *nargv;
			else
				++p;
E 16
I 14
			if (*ostr == ':')
D 16
				return(BADARG);
E 16
I 16
				return (BADARG);
E 16
E 14
E 9
D 8
			tell(": option requires an argument -- ");
E 8
I 8
			if (opterr)
				(void)fprintf(stderr,
				    "%s: option requires an argument -- %c\n",
D 9
				    *nargv, optopt);
E 9
I 9
D 16
				    p, optopt);
E 9
			return(BADCH);
E 16
I 16
				    __progname, optopt);
			return (BADCH);
E 16
E 8
		}
D 4
	 	else optarg = nargv[optind];	/* white space */
E 4
I 4
	 	else				/* white space */
			optarg = nargv[optind];
E 4
		place = EMSG;
		++optind;
	}
D 4
	return(optopt);			/* dump back option letter */
E 4
I 4
D 16
	return(optopt);				/* dump back option letter */
E 16
I 16
	return (optopt);			/* dump back option letter */
E 16
E 4
}
E 1
