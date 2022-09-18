h08990
s 00004/00004/00114
d D 8.1 93/06/06 14:01:38 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00117
d D 5.10 92/09/16 10:54:17 elan 15 14
c copyright[] -> static.
e
s 00005/00030/00113
d D 5.9 92/09/15 10:56:20 elan 14 13
c Added SCCS keywords.
e
s 00033/00007/00110
d D 5.8 92/09/01 11:11:08 elan 13 12
c Rewrote to use new getcap(3) library.  Major prototyping and cleanup.
e
s 00016/00002/00101
d D 5.7 92/07/21 10:30:16 bostic 12 11
c prototype lpr to fix quad's
e
s 00002/00004/00101
d D 5.6 91/03/02 15:07:44 bostic 11 10
c ANSI
e
s 00001/00011/00104
d D 5.5 90/06/01 18:45:52 bostic 10 9
c new copyright notice
e
s 00010/00005/00105
d D 5.4 88/06/30 18:00:01 bostic 9 8
c install approved copyright notice
e
s 00010/00004/00100
d D 5.3 88/05/05 18:08:14 bostic 8 7
c written by Ralph Campbell; add Berkeley specific header
e
s 00001/00000/00103
d D 5.2 85/11/17 15:53:51 eric 7 6
c clean up logging
e
s 00013/00001/00090
d D 5.1 85/06/06 10:05:26 dist 6 5
c Add copyright
e
s 00004/00001/00087
d D 4.5 83/07/17 00:11:40 sam 5 4
c put sccs id's to some use
e
s 00007/00007/00081
d D 4.4 83/06/02 12:23:35 ralph 4 3
c made local variables static to improve separation between functions.
e
s 00006/00001/00082
d D 4.3 83/05/26 09:18:48 ralph 3 2
c fixed -P option so -Pprinter and -P printer both work.
e
s 00000/00000/00083
d D 4.2 83/05/13 11:53:09 ralph 2 1
c bug fixes and changes for lpc command.
e
s 00083/00000/00000
d D 4.1 83/04/29 11:29:13 ralph 1 0
c date and time created 83/04/29 11:29:13 by ralph
e
u
U
t
T
I 6
/*
D 14
 * Copyright (c) 1983 Regents of the University of California.
E 14
I 14
D 16
 * Copyright (c) 1983 The Regents of the University of California.
E 14
D 8
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
D 10
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
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
E 10
I 10
D 13
 * %sccs.include.redist.c%
E 13
I 13
D 14
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
E 14
 *
D 14
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
E 14
I 14
 * %sccs.include.redist.c%
E 14
E 13
E 10
E 9
E 8
 */

E 6
I 1
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
#ifndef lint
I 6
D 15
char copyright[] =
E 15
I 15
static char copyright[] =
E 15
D 13
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 13
I 13
D 14
"@(#) Copyright (c) 1983 Regents of the University of California.\n\
E 13
 All rights reserved.\n";
E 14
I 14
D 16
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
 All rights reserved.";
E 16
I 16
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 16
E 14
D 8
#endif not lint
E 8
I 8
#endif /* not lint */
E 8

#ifndef lint
E 6
D 13
static char sccsid[] = "%W% (Berkeley) %G%";
E 13
I 13
D 14
static char sccsid[] = "@(#)lprm.c	5.8 (Berkeley) 8/6/92";
E 14
I 14
static char sccsid[] = "%W% (Berkeley) %G%";
E 14
E 13
D 6
#endif
E 6
I 6
D 8
#endif not lint
E 8
I 8
#endif /* not lint */
E 8
E 6

E 5
/*
 * lprm - remove the current user's spool entry
 *
 * lprm [-] [[job #] [user] ...]
 *
 * Using information in the lock file, lprm will kill the
 * currently active daemon (if necessary), remove the associated files,
 * and startup a new daemon.  Priviledged users may remove anyone's spool
 * entries, otherwise one can only remove their own.
 */

I 12
#include <sys/param.h>

#include <syslog.h>
#include <dirent.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
E 12
#include "lp.h"
I 12
#include "lp.local.h"
E 12

/*
 * Stuff for handling job specifications
 */
D 4
char	*user[MAXUSERS];		/* users to process */
int	users;				/* # of users in user array */
int	requ[MAXREQUESTS];		/* job number of spool entries */
int	requests;			/* # of spool requests */
E 4
I 4
D 13
char	*user[MAXUSERS];	/* users to process */
int	users;			/* # of users in user array */
int	requ[MAXREQUESTS];	/* job number of spool entries */
int	requests;		/* # of spool requests */
E 13
char	*person;		/* name of person doing lprm */
I 13
int	 requ[MAXREQUESTS];	/* job number of spool entries */
int	 requests;		/* # of spool requests */
char	*user[MAXUSERS];	/* users to process */
int	 users;			/* # of users in user array */
E 13
E 4

D 4
extern char	*person;		/* name of person doing lprm */
char		luser[16];		/* buffer for person */
E 4
I 4
static char	luser[16];	/* buffer for person */
E 4

I 12
void usage __P((void));

int
E 12
D 11
struct passwd *getpwuid();

E 11
main(argc, argv)
I 11
	int argc;
E 11
	char *argv[];
{
	register char *arg;
	struct passwd *p;
D 12
	struct direct **files;
	int nitems, assasinated = 0;
E 12
D 4
	int select();
E 4

	name = argv[0];
	gethostname(host, sizeof(host));
I 7
	openlog("lpd", 0, LOG_LPR);
E 7
	if ((p = getpwuid(getuid())) == NULL)
		fatal("Who are you?");
	if (strlen(p->pw_name) >= sizeof(luser))
		fatal("Your name is too long");
	strcpy(luser, p->pw_name);
	person = luser;
	while (--argc) {
		if ((arg = *++argv)[0] == '-')
			switch (arg[1]) {
			case 'P':
D 3
				printer = &arg[2];
E 3
I 3
				if (arg[2])
					printer = &arg[2];
				else if (argc > 1) {
					argc--;
					printer = *++argv;
				}
E 3
				break;
			case '\0':
				if (!users) {
					users = -1;
					break;
				}
			default:
				usage();
			}
		else {
			if (users < 0)
				usage();
			if (isdigit(arg[0])) {
				if (requests >= MAXREQUESTS)
					fatal("Too many requests");
				requ[requests++] = atoi(arg);
			} else {
				if (users >= MAXUSERS)
					fatal("Too many users");
				user[users++] = arg;
			}
		}
	}
	if (printer == NULL && (printer = getenv("PRINTER")) == NULL)
		printer = DEFLP;

	rmjob();
I 12
	exit(0);
E 12
}

I 12
void
E 12
I 4
D 11
static
E 11
E 4
usage()
{
D 11
	printf("usage: lprm [-] [-Pprinter] [[job #] [user] ...]\n");
E 11
I 11
	fprintf(stderr, "usage: lprm [-] [-Pprinter] [[job #] [user] ...]\n");
E 11
	exit(2);
}
E 1
