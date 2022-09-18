h43307
s 00012/00005/00056
d D 8.2 95/04/28 09:48:20 bostic 11 10
c prettiness police
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00005/00005/00056
d D 8.1 93/05/31 14:37:23 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00021/00017/00040
d D 5.5 93/04/29 12:15:24 bostic 9 8
c lint, freezing for 4.4BSD
e
s 00001/00011/00056
d D 5.4 90/05/31 20:30:56 bostic 8 7
c new copyright notice
e
s 00012/00007/00055
d D 5.3 88/06/18 13:20:18 bostic 7 6
c install approved copyright notice
e
s 00043/00023/00019
d D 5.2 88/06/06 15:20:15 bostic 6 5
c add Berkeley specific copyright; add -s flag; general cleanup,
c don't hardcode name length
e
s 00015/00002/00027
d D 5.1 85/04/30 14:55:50 dist 5 4
c Add copyright
e
s 00003/00001/00026
d D 1.4 83/08/11 19:52:41 sam 4 3
c sccs keyword fixes
e
s 00005/00001/00022
d D 1.3 83/03/30 10:48:36 rrh 3 2
c fix bug with printf clobbering the errno return from {set,get}hostname
e
s 00004/00004/00019
d D 1.2 83/01/02 14:14:44 sam 2 1
c from sun
e
s 00023/00000/00000
d D 1.1 82/04/08 01:46:48 sklower 1 0
c date and time created 82/04/08 01:46:48 by sklower
e
u
U
t
T
I 5
/*
D 6
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
D 7
 * Copyright (c) 1983, 1988 Regents of the University of California.
E 7
I 7
D 9
 * Copyright (c) 1983, 1988 Regents of the University of California.
E 9
I 9
D 10
 * Copyright (c) 1988, 1993 Regents of the University of California.
E 9
E 7
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 8
 * Redistribution and use in source and binary forms are permitted
D 7
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 7
E 6
 */

E 5
I 1
D 4
static char *sccsid = "%W% %I% %E%"; 
E 4
I 4
#ifndef lint
D 5
static char *sccsid = "%W% (Berkeley) %G%"; 
#endif
E 5
I 5
D 10
char copyright[] =
D 6
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 6
I 6
D 7
"%Z% Copyright (c) 1983, 1988 Regents of the University of California.\n\
E 7
I 7
D 9
"%Z% Copyright (c) 1983, 1988 Regents of the University of California.\n\
E 9
I 9
"%Z% Copyright (c) 1988, 1993 Regents of the University of California.\n\
E 9
E 7
E 6
 All rights reserved.\n";
E 10
I 10
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 10
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6

E 5
E 4
D 6
/*
 * hostname -- get (or set hostname)
 */
E 6
D 9
#include <stdio.h>
E 9
I 6
#include <sys/param.h>
E 6

I 9
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

I 11
void usage __P((void));

E 11
int
E 9
D 6
char hostname[32];
extern int errno;

E 6
main(argc,argv)
D 2
char *argv[];
E 2
I 2
D 6
	char *argv[];
E 6
I 6
	int argc;
D 9
	char **argv;
E 9
I 9
	char *argv[];
E 9
E 6
E 2
{
I 3
D 6
	int	myerrno;
E 6
I 6
D 11
	extern int optind;
E 11
	int ch, sflag;
D 9
	char hostname[MAXHOSTNAMELEN], *p, *index();
E 9
I 9
	char *p, hostname[MAXHOSTNAMELEN];
E 9
E 6

E 3
D 6
	argc--;
	argv++;
D 2
	if(argc) {
		if(sethostname(*argv,strlen(*argv)+1))
E 2
I 2
	if (argc) {
		if (sethostname(*argv,strlen(*argv)))
E 6
I 6
	sflag = 0;
D 11
	while ((ch = getopt(argc, argv, "s")) != EOF)
E 11
I 11
	while ((ch = getopt(argc, argv, "s")) != -1)
E 11
D 9
		switch((char)ch) {
E 9
I 9
		switch (ch) {
E 9
		case 's':
			sflag = 1;
			break;
		case '?':
		default:
D 9
			fputs("hostname [-s] [hostname]\n", stderr);
E 9
I 9
D 11
			(void)fprintf(stderr,
			    "usage: hostname [-s] [hostname]\n");
E 9
			exit(1);
E 11
I 11
			usage();
E 11
		}
I 9
	argc -= optind;
E 9
	argv += optind;

	if (*argv) {
D 9
		if (sethostname(*argv, strlen(*argv))) {
E 6
E 2
			perror("sethostname");
I 3
D 6
		myerrno = errno;
E 6
I 6
			exit(1);
		}
E 9
I 9
		if (sethostname(*argv, strlen(*argv)))
			err(1, "sethostname");
E 9
E 6
E 3
	} else {
D 6
		gethostname(hostname,sizeof(hostname));
I 3
		myerrno = errno;
E 3
		printf("%s\n",hostname);
E 6
I 6
D 9
		if (gethostname(hostname, sizeof(hostname))) {
			perror("gethostname");
			exit(1);
		}
		if (sflag && (p = index(hostname, '.')))
E 9
I 9
		if (gethostname(hostname, sizeof(hostname)))
			err(1, "gethostname");
		if (sflag && (p = strchr(hostname, '.')))
E 9
			*p = '\0';
D 9
		puts(hostname);
E 9
I 9
		(void)printf("%s\n", hostname);
E 9
E 6
	}
D 2
	return(errno);
E 2
I 2
D 3
	exit(errno);
E 3
I 3
D 6
	exit(myerrno);
E 6
I 6
	exit(0);
I 11
}

void
usage()
{

	(void)fprintf(stderr, "usage: hostname [-s] [hostname]\n");
	exit(1);
E 11
E 6
E 3
E 2
}
E 1
