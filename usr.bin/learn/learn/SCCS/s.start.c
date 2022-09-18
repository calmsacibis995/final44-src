h59032
s 00002/00002/00062
d D 8.1 93/06/06 14:56:59 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00063
d D 4.9 93/06/03 17:51:18 bostic 9 8
c MIPS doesn't like routines named "start"
e
s 00009/00002/00055
d D 4.8 91/04/17 18:00:41 bostic 8 7
c new copyright; att/bsd/shared
e
s 00008/00013/00049
d D 4.7 90/06/24 12:36:04 bostic 7 6
c delete unused locals, use correct #defines, handle case where the file
c name length is 1.  -- from Chris Torek
e
s 00004/00014/00058
d D 4.6 90/02/21 10:58:25 bostic 6 5
c signal fixes, gcc/lint fixes, require directory reading subroutines
e
s 00007/00005/00065
d D 4.5 86/05/15 17:58:57 bloom 5 4
c updates from John Kunze
e
s 00002/00001/00068
d D 4.4 85/04/02 12:28:50 ralph 4 3
c define BDS4_2 instead of including whoami.h
e
s 00031/00019/00038
d D 4.3 84/10/20 01:08:51 root 3 2
c fixed bug wherein files not removed between lessons -jak
e
s 00006/00005/00051
d D 4.2 83/04/25 23:59:21 mckusick 2 1
c 
e
s 00056/00000/00000
d D 4.1 83/02/24 12:56:16 mckusick 1 0
c date and time created 83/02/24 12:56:16 by mckusick
e
u
U
t
T
I 8
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

E 8
I 1
#ifndef lint
D 8
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 8
I 8
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 8

#include "stdio.h"
I 2
#include "lrnref.h"
E 2
#include <sys/types.h>
I 5
D 6
#ifndef DIR
E 5
I 3
D 4
#include <whoami.h>
E 4
E 3
#include <sys/dir.h>
I 5
#endif
E 6
I 6
#include <dirent.h>
I 7
#include <unistd.h>
E 7
E 6
E 5
I 4

D 5
#define BSD4_2	1
E 4
D 2
#include "lrnref.h"
E 2
D 3
#define	ND	64
E 3

E 5
D 9
start(lesson)
E 9
I 9
lstart(lesson)
E 9
char *lesson;
{
D 3
	struct direct dv[ND], *dm, *dp;
	int f, c, n;
E 3
I 3
D 6
	struct direct dbuf;
	register struct direct *ep = &dbuf;	/* directory entry pointer */
E 6
I 6
D 7
	struct dirent dbuf;
	register struct dirent *ep = &dbuf;	/* directory entry pointer */
E 7
I 7
	register struct dirent *ep;
E 7
E 6
	int c, n;
E 3
	char where [100];
D 6

D 2
	f = open(".", 0);
E 2
I 2
D 3
	f = open(".", 0);		/* clean up play directory */
E 2
	n = read(f, dv, ND*sizeof(*dp));
	n /= sizeof(*dp);
	if (n==ND)
D 2
		fprintf(stderr, "lesson too long\n");
E 2
I 2
		fprintf(stderr, "Start:  play directory too long\n");
E 2
	dm = dv+n;
	for(dp=dv; dp<dm; dp++)
		if (dp->d_ino) {
			n = strlen(dp->d_name);
			if (dp->d_name[n-2] == '.' && dp->d_name[n-1] == 'c')
				continue;
			c = dp->d_name[0];
			if (c>='a' && c<= 'z')
				unlink(dp->d_name);
		}
	close(f);
E 3
I 3
D 5
#if BSD4_2
E 5
I 5
#ifdef BSD4_2
E 6
E 5
	DIR *dp;
I 6

E 6
D 7
#define OPENDIR(s)	((dp = opendir(s)) != NULL)
#define DIRLOOP(s)	for (s = readdir(dp); s != NULL; s = readdir(dp))
D 5
#define PATHSIZE 256
E 5
#define EPSTRLEN	ep->d_namlen
#define CLOSEDIR	closedir(dp)
D 6
#else
	int f;
#define OPENDIR(s)	((f = open(s, 0)) >= 0)
#define DIRLOOP(s)	while (read(f, s, sizeof *s) == sizeof *s)
#define EPSTRLEN	strlen(ep->d_name)
#define CLOSEDIR	close(f)
#endif
E 6

D 5
	OPENDIR(".");				/* clean up play directory */
E 5
I 5
	if (!OPENDIR(".")) {		/* clean up play directory */
E 7
I 7
	if ((dp = opendir(".")) == NULL) {	/* clean up play directory */
E 7
		perror("Start:  play directory");
		wrapup(1);
	}
E 5
D 7
	DIRLOOP(ep) {
E 7
I 7
	while ((ep = readdir(dp)) != NULL) {
E 7
		if (ep->d_ino == 0)
			continue;
D 7
		n = EPSTRLEN;
		if (ep->d_name[n-2] == '.' && ep->d_name[n-1] == 'c')
E 7
I 7
		n = ep->d_namlen;
		if (n >= 2 && ep->d_name[n-2] == '.' && ep->d_name[n-1] == 'c')
E 7
			continue;
		c = ep->d_name[0];
		if (c>='a' && c<= 'z')
			unlink(ep->d_name);
	}
D 7
	CLOSEDIR;
E 7
I 7
	(void) closedir(dp);
E 7
E 3
	if (ask)
		return;
D 2
	sprintf(where, "../../%s/L%s", sname, lesson);
E 2
I 2
	sprintf(where, "%s/%s/L%s", direct, sname, lesson);
E 2
D 7
	if (access(where, 04)==0)	/* there is a file */
E 7
I 7
	if (access(where, R_OK)==0)	/* there is a file */
E 7
		return;
D 2
	fprintf(stderr, "No lesson %s\n",lesson);
E 2
I 2
	perror(where);
	fprintf(stderr, "Start:  no lesson %s\n",lesson);
E 2
	wrapup(1);
}

fcopy(new,old)
char *new, *old;
{
	char b[BUFSIZ];
	int n, fn, fo;
	fn = creat(new, 0666);
	fo = open(old,0);
	if (fo<0) return;
	if (fn<0) return;
	while ( (n=read(fo, b, BUFSIZ)) > 0)
		write(fn, b, n);
	close(fn);
	close(fo);
}
E 1
