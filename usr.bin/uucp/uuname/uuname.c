/*-
 * Copyright (c) 1983, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char copyright[] =
"@(#) Copyright (c) 1983, 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "@(#)uuname.c	8.1 (Berkeley) 6/6/93";
#endif /* not lint */

#include "uucp.h"

/*
 * return list of all remote systems recognized by uucp, or  (with -l) the
 * local  uucp name. 
 *
 * return codes: 0 | 1  (can't read) 
 */

struct timeb Now;

main(argc, argv)
char *argv[];
int argc;
{
	register FILE *np;
	register char *buf;
	char s[BUFSIZ];
	char prev[BUFSIZ];

	strcpy(Progname, "uuname");

	if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'l') {
		uucpname(s);
		puts(s);
		exit(0);
	}
	if (argc != 1) {
		fprintf(stderr, "Usage: uuname [-l]\n");
		exit(1);
	}
	if ((np = fopen(SYSFILE, "r")) == NULL) {
		syslog(LOG_WARNING, "fopen(%s) failed: %m", SYSFILE);
		exit(1);
	}
	buf = s;
	while (cfgets(buf, sizeof(s), np) != NULL) {
		register char *cp;
		cp = strpbrk(buf, " \t");
		if (cp)
			*cp = '\0';
		if (strcmp(s, prev) == SAME)
			continue;
		if (*buf == 'x' && buf[1] == 'x' && buf[2] == 'x')
			continue;
		puts(buf);
		if (buf == s)
			buf = prev;
		else
			buf = s;
	}
	exit(0);
}

cleanup(code)
int code;
{
	exit(code);
}
