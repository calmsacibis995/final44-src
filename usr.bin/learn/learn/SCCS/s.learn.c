h33140
s 00005/00005/00088
d D 8.1 93/06/06 14:56:24 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00002/00078
d D 4.7 91/04/17 18:00:34 bostic 9 8
c new copyright; att/bsd/shared
e
s 00004/00001/00076
d D 4.6 91/03/01 14:33:05 bostic 8 7
c ANSI
e
s 00004/00003/00073
d D 4.5 89/05/10 22:47:10 bostic 7 6
c file reorg, pathnames.h, paths.h
e
s 00005/00001/00071
d D 4.4 86/05/15 17:58:21 bloom 6 5
c updates from John Kunze
e
s 00000/00003/00072
d D 4.3 84/05/15 11:19:09 ralph 5 4
c remove useless setbuf()'s.
e
s 00008/00001/00067
d D 4.2 83/04/27 15:26:06 mckusick 4 1
c now works with C shell and Ex -- see README for details
e
s 00000/00000/00075
d R 4.3 83/04/27 15:20:57 mckusick 3 2
c 
e
s 00008/00001/00067
d R 4.2 83/04/25 23:58:50 mckusick 2 1
c 
e
s 00068/00000/00000
d D 4.1 83/02/24 12:55:48 mckusick 1 0
c date and time created 83/02/24 12:55:48 by mckusick
e
u
U
t
T
I 9
/*-
D 10
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * %sccs.include.proprietary.c%
 */

E 9
I 1
#ifndef lint
D 9
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 9
I 9
D 10
char copyright[] =
"%Z% Copyright (c) 1986 The Regents of the University of California.\n\
 All rights reserved.\n";
E 10
I 10
static char copyright[] =
"%Z% Copyright (c) 1986, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 10
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 9

D 7
#include "stdio.h"
E 7
I 7
#include <sys/signal.h>
#include <stdio.h>
E 7
#include "lrnref.h"
D 7
#include "signal.h"
E 7
I 7
#include "pathnames.h"
E 7

D 7
char	*direct	= "/usr/lib/learn";	/* CHANGE THIS ON YOUR SYSTEM */
E 7
I 7
char	*direct	= _PATH_LEARN;
E 7
int	more;
char	*level;
int	speed;
char	*sname;
char	*todo;
FILE	*incopy	= NULL;
int	didok;
int	sequence	= 1;
int	comfile	= -1;
int	status;
int	wrong;
char	*pwline;
char	*dir;
FILE	*scrin;
int	logging	= 1;	/* set to 0 to turn off logging */
int	ask;
I 4
int	again;
int	skip;
int	teed;
int	total;
E 4

I 8
extern void hangup(), intrpt();

E 8
main(argc,argv)
I 4
int argc;
E 4
char *argv[];
{
D 8
	extern hangup(), intrpt();
E 8
D 6
	extern char * getlogin();
E 6
I 6
	extern char * getlogin(), *malloc();
E 6
D 5
	char *malloc();
E 5

	speed = 0;
	more = 1;
	pwline = getlogin();
I 6
#ifndef BSD4_2
	setbuf(stdout, malloc(BUFSIZ));
	setbuf(stderr, malloc(BUFSIZ));
#endif
E 6
D 5
	setbuf(stdout, malloc(BUFSIZ));
I 4
	setbuf(stderr, malloc(BUFSIZ));
E 5
E 4
	selsub(argc, argv);
I 4
	chgenv();
E 4
	signal(SIGHUP, hangup);
	signal(SIGINT, intrpt);
	while (more) {
		selunit();
		dounit();
		whatnow();
	}
	wrapup(0);
}

I 8
void
E 8
hangup()
{
	wrapup(1);
}

I 8
void
E 8
intrpt()
{
	char response[20], *p;

	signal(SIGINT, hangup);
	write(2, "\nInterrupt.\nWant to go on?  ", 28);
	p = response;
	*p = 'n';
	while (read(0, p, 1) == 1 && *p != '\n')
		p++;
	if (response[0] != 'y')
D 4
		wrapup(1);
E 4
I 4
		wrapup(0);
E 4
	ungetc('\n', stdin);
	signal(SIGINT, intrpt);
}
E 1
