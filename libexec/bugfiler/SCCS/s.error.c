h36834
s 00002/00002/00061
d D 8.1 93/06/04 18:46:10 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00002/00056
d D 5.9 93/05/17 10:04:08 bostic 9 8
c lint, ANSI C prototypes, index->strchr
e
s 00004/00001/00054
d D 5.8 91/02/25 16:23:09 bostic 8 7
c ANSI fixes (two real bug fixes!), convert to struct dirent, cleanups
e
s 00001/00011/00054
d D 5.7 90/06/01 15:49:53 bostic 7 6
c new copyright notice
e
s 00010/00005/00055
d D 5.6 88/06/29 21:43:09 bostic 6 5
c install approved copyright notice
e
s 00011/00005/00049
d D 5.5 88/02/01 16:16:31 bostic 5 4
c add Berkeley specific header
e
s 00003/00003/00051
d D 5.4 87/07/21 11:35:58 bostic 4 3
c compress log file messages to single line
e
s 00001/00001/00053
d D 5.3 87/04/11 15:39:48 bostic 3 2
c added keywords
e
s 00014/00021/00040
d D 5.2 87/04/11 15:38:40 bostic 2 1
c version #2; -f flag, remove home_dir, redist per folder
e
s 00061/00000/00000
d D 5.1 86/11/25 13:33:09 bostic 1 0
c date and time created 86/11/25 13:33:09 by bostic
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
D 10
 * Copyright (c) 1986, 1987 Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1986, 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 7
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
E 5
 */

#ifndef lint
D 2
static char sccsid[] = "%W% (Berkeley) %E%";
E 2
I 2
D 3
static char sccsid[] = "@(#)error.c	5.1 (Berkeley) 86/11/25";
E 3
I 3
D 5
static char sccsid[] = "%W% (Berkeley) %E%";
E 3
E 2
#endif not lint
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

I 2
D 8
#include <bug.h>
E 8
I 8
#include <sys/param.h>
I 9

E 9
#include <dirent.h>
E 8
E 2
D 9
#include <syslog.h>
E 9
#include <stdio.h>
I 8
#include <stdlib.h>
I 9
#include <string.h>
#include <syslog.h>

E 9
#include "bug.h"
I 9
#include "extern.h"
E 9
E 8
D 2
#include <bug.h>
E 2

D 2
extern char	*distf,				/* redist temp file */
		tmpname[];			/* temporary file used */

short	made_dist;				/* if dist file made */

E 2
static short	err_redir;			/* stderr redirected */

/*
 * seterr --
 *	redirect stderr for error processing
 */
I 9
void
E 9
seterr()
{
D 2
	if (!freopen(ERROR_FILE,"a",stderr))
		error("unable to open error file %s.\n",ERROR_FILE);
E 2
I 2
	if (!freopen(ERROR_FILE, "a", stderr))
D 4
		error("can't open error file %s.\n", ERROR_FILE);
E 4
I 4
		error("can't open error file %s.", ERROR_FILE);
E 4
E 2
	err_redir = YES;
}

/*
 * error --
 *	write errors to log file and die
 */
I 9
void
E 9
D 2
error(fmt,arg)
register char	*fmt,
		*arg;
E 2
I 2
error(fmt, arg)
	register char	*fmt,
			*arg;
E 2
{
	static char	logmsg[MAXLINELEN];	/* syslog message */
D 9
	char	*strcpy(), *strcat();
E 9

	if (err_redir) {
		/* don't combine these, "fmt" may not require "arg" */
D 2
		fputc('\t',stderr);
		fprintf(stderr,fmt,arg);
		fprintf(stderr,"\n\ttemporary file is %s.\n",tmpname);
E 2
I 2
D 4
		fputc('\t', stderr);
E 4
I 4
		fprintf(stderr, "\t%s\n\t", tmpname);
E 4
		fprintf(stderr, fmt, arg);
D 4
		fprintf(stderr, "\n\ttemporary file is %s.\n", tmpname);
E 4
I 4
		fputc('\n', stderr);
E 4
E 2
	}
	else {
D 2
		strcat(strcpy(logmsg,"bugfiler: "),fmt);
		syslog(LOG_ERR,logmsg,arg);
E 2
I 2
		sprintf(logmsg, "bugfiler: %s", fmt);
		syslog(LOG_ERR, logmsg, arg);
E 2
	}
D 2
	if (made_dist)		/* unlink redist file if necessary */
		unlink(distf);
E 2
#ifdef METOO
	exit(ERR);
D 2
#else !METOO
E 2
I 2
#else
E 2
	exit(OK);
D 2
#endif METOO
E 2
I 2
#endif
E 2
}
E 1
