h38534
s 00028/00024/00322
d D 8.2 95/05/04 17:59:35 christos 6 5
c 
e
s 00002/00002/00344
d D 8.1 93/05/31 15:18:32 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00024/00005/00322
d D 5.4 92/07/15 10:35:07 marc 4 3
c add cd -
e
s 00000/00013/00327
d D 5.3 92/04/30 15:05:09 marc 3 2
c remove UDIR (we now have tilde)
e
s 00002/00001/00338
d D 5.2 91/03/13 17:36:40 marc 2 1
c wrong source
e
s 00339/00000/00000
d D 5.1 91/03/07 20:27:18 bostic 1 0
c date and time created 91/03/07 20:27:18 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 6
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

E 6
/*
 * The cd and pwd commands.
 */

#include "shell.h"
#include "var.h"
#include "nodes.h"	/* for jobs.h */
#include "jobs.h"
#include "options.h"
#include "output.h"
#include "memalloc.h"
#include "error.h"
I 6
#include "redir.h"
E 6
#include "mystring.h"
D 6
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
E 6
I 6
#include "show.h"
E 6

I 6
STATIC int docd __P((char *, int));
STATIC char *getcomponent __P((void));
STATIC void updatepwd __P((char *));
STATIC void getpwd __P((void));
E 6

D 6
#ifdef __STDC__
STATIC int docd(char *, int);
STATIC void updatepwd(char *);
STATIC void getpwd(void);
STATIC char *getcomponent(void);
#else
STATIC int docd();
STATIC void updatepwd();
STATIC void getpwd();
STATIC char *getcomponent();
#endif


E 6
char *curdir;			/* current working directory */
I 4
char *prevdir;			/* previous working directory */
E 4
STATIC char *cdcomppath;

D 3
#if UDIR
extern int didudir;		/* set if /u/logname expanded */
#endif


E 3
int
D 6
cdcmd(argc, argv)  char **argv; {
E 6
I 6
cdcmd(argc, argv)
	int argc;
	char **argv; 
{
E 6
	char *dest;
	char *path;
	char *p;
	struct stat statb;
	char *padvance();
I 4
	int print = 0;
E 4

D 2
	if ((dest = argv[1]) == NULL && (dest = bltinlookup("HOME", 1)) == NULL)
E 2
I 2
	nextopt(nullstr);
	if ((dest = *argptr) == NULL && (dest = bltinlookup("HOME", 1)) == NULL)
E 2
		error("HOME not set");
I 4
	if (dest[0] == '-' && dest[1] == '\0') {
		dest = prevdir ? prevdir : curdir;
		print = 1;
	}
E 4
	if (*dest == '/' || (path = bltinlookup("CDPATH", 1)) == NULL)
		path = nullstr;
	while ((p = padvance(&path, dest)) != NULL) {
D 6
		if (stat(p, &statb) >= 0
D 4
		 && (statb.st_mode & S_IFMT) == S_IFDIR
		 && docd(p, strcmp(p, dest)) >= 0)
			return 0;
E 4
I 4
		 && (statb.st_mode & S_IFMT) == S_IFDIR) {
E 6
I 6
		if (stat(p, &statb) >= 0 && S_ISDIR(statb.st_mode)) {
E 6
			if (!print) {
				/*
				 * XXX - rethink
				 */
				if (p[0] == '.' && p[1] == '/')
					p += 2;
				print = strcmp(p, dest);
			}
			if (docd(p, print) >= 0)
				return 0;

		}
E 4
	}
	error("can't cd to %s", dest);
I 6
	/*NOTREACHED*/
	return 0;
E 6
}


/*
 * Actually do the chdir.  If the name refers to symbolic links, we
 * compute the actual directory name before doing the cd.  In an
 * interactive shell, print the directory name if "print" is nonzero
 * or if the name refers to a symbolic link.  We also print the name
 * if "/u/logname" was expanded in it, since this is similar to a
 * symbolic link.  (The check for this breaks if the user gives the
 * cd command some additional, unused arguments.)
 */

#if SYMLINKS == 0
STATIC int
docd(dest, print)
	char *dest;
	{
D 3
#if UDIR
	if (didudir)
		print = 1;
#endif
E 3
	INTOFF;
	if (chdir(dest) < 0) {
		INTON;
		return -1;
	}
	updatepwd(dest);
	INTON;
	if (print && iflag)
		out1fmt("%s\n", stackblock());
	return 0;
}

#else



STATIC int
docd(dest, print)
	char *dest;
D 6
	{
E 6
I 6
	int print;
{
E 6
	register char *p;
	register char *q;
	char *symlink;
	char *component;
	struct stat statb;
	int first;
	int i;

	TRACE(("docd(\"%s\", %d) called\n", dest, print));
D 3
#if UDIR
	if (didudir)
		print = 1;
#endif
E 3

top:
	cdcomppath = dest;
	STARTSTACKSTR(p);
	if (*dest == '/') {
		STPUTC('/', p);
		cdcomppath++;
	}
	first = 1;
	while ((q = getcomponent()) != NULL) {
D 6
		if (q[0] == '\0' || q[0] == '.' && q[1] == '\0')
E 6
I 6
		if (q[0] == '\0' || (q[0] == '.' && q[1] == '\0'))
E 6
			continue;
		if (! first)
			STPUTC('/', p);
		first = 0;
		component = q;
		while (*q)
			STPUTC(*q++, p);
		if (equal(component, ".."))
			continue;
		STACKSTRNUL(p);
		if (lstat(stackblock(), &statb) < 0)
			error("lstat %s failed", stackblock());
D 6
		if ((statb.st_mode & S_IFMT) != S_IFLNK)
E 6
I 6
		if (!S_ISLNK(statb.st_mode))
E 6
			continue;

		/* Hit a symbolic link.  We have to start all over again. */
		print = 1;
		STPUTC('\0', p);
		symlink = grabstackstr(p);
		i = (int)statb.st_size + 2;		/* 2 for '/' and '\0' */
		if (cdcomppath != NULL)
			i += strlen(cdcomppath);
		p = stalloc(i);
		if (readlink(symlink, p, (int)statb.st_size) < 0) {
			error("readlink %s failed", stackblock());
		}
		if (cdcomppath != NULL) {
			p[(int)statb.st_size] = '/';
			scopy(cdcomppath, p + (int)statb.st_size + 1);
		} else {
			p[(int)statb.st_size] = '\0';
		}
		if (p[0] != '/') {	/* relative path name */
			char *r;
			q = r = symlink;
			while (*q) {
				if (*q++ == '/')
					r = q;
			}
			*r = '\0';
			dest = stalloc(strlen(symlink) + strlen(p) + 1);
			scopy(symlink, dest);
			strcat(dest, p);
		} else {
			dest = p;
		}
		goto top;
	}
	STPUTC('\0', p);
	p = grabstackstr(p);
	INTOFF;
	if (chdir(p) < 0) {
		INTON;
		return -1;
	}
	updatepwd(p);
	INTON;
	if (print && iflag)
		out1fmt("%s\n", p);
	return 0;
}
#endif /* SYMLINKS */



/*
 * Get the next component of the path name pointed to by cdcomppath.
 * This routine overwrites the string pointed to by cdcomppath.
 */

STATIC char *
getcomponent() {
	register char *p;
	char *start;

	if ((p = cdcomppath) == NULL)
		return NULL;
	start = cdcomppath;
	while (*p != '/' && *p != '\0')
		p++;
	if (*p == '\0') {
		cdcomppath = NULL;
	} else {
		*p++ = '\0';
		cdcomppath = p;
	}
	return start;
}



/*
 * Update curdir (the name of the current directory) in response to a
 * cd command.  We also call hashcd to let the routines in exec.c know
 * that the current directory has changed.
 */

void hashcd();

STATIC void
updatepwd(dir)
	char *dir;
	{
	char *new;
	char *p;

	hashcd();				/* update command hash table */
	cdcomppath = stalloc(strlen(dir) + 1);
	scopy(dir, cdcomppath);
	STARTSTACKSTR(new);
	if (*dir != '/') {
		if (curdir == NULL)
			return;
		p = curdir;
		while (*p)
			STPUTC(*p++, new);
		if (p[-1] == '/')
			STUNPUTC(new);
	}
	while ((p = getcomponent()) != NULL) {
		if (equal(p, "..")) {
			while (new > stackblock() && (STUNPUTC(new), *new) != '/');
		} else if (*p != '\0' && ! equal(p, ".")) {
			STPUTC('/', new);
			while (*p)
				STPUTC(*p++, new);
		}
	}
	if (new == stackblock())
		STPUTC('/', new);
	STACKSTRNUL(new);
D 4
	if (curdir)
		ckfree(curdir);
E 4
I 4
	INTOFF;
	if (prevdir)
		ckfree(prevdir);
	prevdir = curdir;
E 4
	curdir = savestr(stackblock());
I 4
	INTON;
E 4
}



int
D 6
pwdcmd(argc, argv)  char **argv; {
E 6
I 6
pwdcmd(argc, argv)
	int argc;
	char **argv; 
{
E 6
	getpwd();
	out1str(curdir);
	out1c('\n');
	return 0;
}



/*
 * Run /bin/pwd to find out what the current directory is.  We suppress
 * interrupts throughout most of this, but the user can still break out
 * of it by killing the pwd program.  If we already know the current
 * directory, this routine returns immediately.
 */

#define MAXPWD 256

STATIC void
getpwd() {
	char buf[MAXPWD];
	char *p;
	int i;
	int status;
	struct job *jp;
	int pip[2];

	if (curdir)
		return;
	INTOFF;
	if (pipe(pip) < 0)
		error("Pipe call failed");
	jp = makejob((union node *)NULL, 1);
	if (forkshell(jp, (union node *)NULL, FORK_NOJOB) == 0) {
		close(pip[0]);
		if (pip[1] != 1) {
			close(1);
			copyfd(pip[1], 1);
			close(pip[1]);
		}
		execl("/bin/pwd", "pwd", (char *)0);
		error("Cannot exec /bin/pwd");
	}
	close(pip[1]);
	pip[1] = -1;
	p = buf;
	while ((i = read(pip[0], p, buf + MAXPWD - p)) > 0
D 6
	     || i == -1 && errno == EINTR) {
E 6
I 6
	     || (i == -1 && errno == EINTR)) {
E 6
		if (i > 0)
			p += i;
	}
	close(pip[0]);
	pip[0] = -1;
	status = waitforjob(jp);
	if (status != 0)
		error((char *)0);
	if (i < 0 || p == buf || p[-1] != '\n')
		error("pwd command failed");
	p[-1] = '\0';
	curdir = savestr(buf);
	INTON;
}
E 1
