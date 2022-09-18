/*-
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)mailst.c	8.1 (Berkeley) 6/6/93";
#endif /* not lint */

#include <signal.h>
#include "uucp.h"
#ifdef USG
#include <fcntl.h>
#endif USG

/*LINTLIBRARY*/

/*
 *	mailst  -  this routine will fork and execute
 *	a mail command sending string (str) to user (user).
 *	If file is non-null, the file is also sent.
 *	(this is used for mail returned to sender.)
 */

mailst(user, str, file)
char *user, *str, *file;
{
	register FILE *fp, *fi;
	FILE *popen();
	char buf[BUFSIZ];
	register int c;

	sprintf(buf, "IFS=\" \t\n\";%s '%s'", MAIL, user);
	if ((fp = popen(buf, "w")) != NULL) {
		fprintf(fp, "From: uucp\nTo: %s\nSubject: %s\n\n", user, str);
		if (file && *file != '\0' && (fi = fopen(subfile(file), "r")) != NULL) {
			while ((c = getc(fi)) != EOF)
				putc(c, fp);
			putc('\n', fp);
			fclose(fi);
		}
		pclose(fp);
	}
}
