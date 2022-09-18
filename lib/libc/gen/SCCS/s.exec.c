h11807
s 00002/00002/00243
d D 8.1 93/06/04 12:01:37 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00035/00029/00210
d D 5.10 92/05/08 17:00:03 bostic 12 11
c don't leak memory; bug report net2/lib/0; KNF
e
s 00022/00006/00212
d D 5.9 91/06/17 10:58:36 bostic 11 10
c don't use snprintf(3) here, exec shouldn't require stdio(3).
c also, if a component of the path is too long, complain violently.
e
s 00010/00007/00208
d D 5.8 91/03/15 16:29:21 bostic 10 9
c execvp has to do ENOEXEC recovery even if `/' in the path
c when using the interpreter, lose the first argument
e
s 00001/00001/00214
d D 5.7 91/03/06 15:15:13 bostic 9 8
c init argv, used by realloc
e
s 00056/00006/00159
d D 5.6 91/02/23 20:19:14 donn 8 7
c Ruin Keith's finely crafted ANSI C code to make it compile with PCC.
e
s 00142/00067/00023
d D 5.5 91/02/23 16:37:02 bostic 7 6
c redo all the exec routines from scratch in C (well, ANSI C)
c changed path to look at "." last
c don't let execlp/execvp ignore execve errors
c changed name from execvp.c to exec.c
e
s 00008/00005/00082
d D 5.4 91/02/23 09:45:44 donn 6 5
c Changes to accommodate prototype declarations.
e
s 00002/00002/00085
d D 5.3 88/04/24 15:33:44 bostic 5 4
c fix for ANSI C
e
s 00002/00002/00085
d D 5.2 86/03/09 19:46:03 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00083
d D 5.1 85/06/05 12:14:23 mckusick 3 2
c Add copyright
e
s 00001/00001/00083
d D 4.2 84/10/16 21:52:01 sam 2 1
c remove use of '-' as pathname delimiter
e
s 00084/00000/00000
d D 4.1 80/12/21 16:39:39 wnj 1 0
c date and time created 80/12/21 16:39:39 by wnj
e
u
U
t
T
I 7
/*-
D 13
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * %sccs.include.redist.c%
 */

E 7
I 1
D 3
/* %W% (Berkeley) %G% */
E 3
I 3
D 4
#ifndef lint
E 4
I 4
#if defined(LIBC_SCCS) && !defined(lint)
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
D 7
#endif LIBC_SCCS and not lint
E 7
I 7
#endif /* LIBC_SCCS and not lint */
E 7
E 4

E 3
D 7
/*
 *	execlp(name, arg,...,0)	(like execl, but does path search)
 *	execvp(name, argv)	(like execv, but does path search)
 */
E 7
I 7
#include <sys/param.h>
#include <sys/types.h>
E 7
#include <errno.h>
I 7
#include <unistd.h>
E 7
D 6
#define	NULL	0
E 6
I 6
#include <stdlib.h>
I 11
#include <string.h>
#include <stdio.h>
#include <paths.h>

E 11
I 8
#if __STDC__
E 8
I 7
#include <stdarg.h>
I 8
#else
#include <varargs.h>
#endif
E 8
E 7
D 11
#include <string.h>
D 7
#include <unistd.h>
E 7
I 7
#include <stdio.h>
#include <paths.h>
E 11
E 7
E 6

D 7
static	char shell[] =	"/bin/sh";
E 7
I 7
extern char **environ;
E 7
D 5
char	*execat(), *getenv();
E 5
I 5
D 6
char	*getenv();
E 5
extern	errno;
E 6

I 6
D 7
int
E 6
execlp(name, argv)
D 6
char *name, *argv;
E 6
I 6
const char *name, *argv;
E 7
I 7
D 8
static char **buildargv(va_list ap, const char *arg, char ***envpp)
E 8
I 8
static char **
buildargv(ap, arg, envpp)
	va_list ap;
	const char *arg;
	char ***envpp;
E 8
E 7
E 6
{
D 7
	return(execvp(name, &argv));
E 7
I 7
D 12
	register size_t max, off;
D 9
	register char **argv;
E 9
I 9
	register char **argv = NULL;
E 12
I 12
	static int memsize;
	static char **argv;
	register int off;
E 12
E 9

D 12
	for (off = max = 0;; ++off) {
		if (off >= max) {
			max += 50;	/* Starts out at 0. */
			max *= 2;	/* Ramp up fast. */
			if (!(argv = realloc(argv, max * sizeof(char *))))
				return(NULL);
E 12
I 12
	argv = NULL;
	for (off = 0;; ++off) {
		if (off >= memsize) {
			memsize += 50;	/* Starts out at 0. */
			memsize *= 2;	/* Ramp up fast. */
			if (!(argv = realloc(argv, memsize * sizeof(char *)))) {
				memsize = 0;
				return (NULL);
			}
E 12
			if (off == 0) {
				argv[0] = (char *)arg;
				off = 1;
			}
		}
		if (!(argv[off] = va_arg(ap, char *)))
			break;
	}
D 11
	/* Get environment pointer if need user supposed to provide one. */
E 11
I 11
	/* Get environment pointer if user supposed to provide one. */
E 11
	if (envpp)
		*envpp = va_arg(ap, char **);
D 12
	return(argv);
E 12
I 12
	return (argv);
E 12
E 7
}

I 6
D 7
int
E 6
execvp(name, argv)
D 6
char *name, **argv;
E 6
I 6
const char *name;
char * const *argv;
E 7
I 7
D 8
int execl(const char *name, const char *arg, ...)
E 8
I 8
int
#if __STDC__
execl(const char *name, const char *arg, ...)
#else
execl(name, arg, va_alist)
	const char *name;
	const char *arg;
	va_dcl
#endif
E 8
E 7
E 6
{
D 7
	char *pathstr;
	register char *cp;
	char fname[128];
D 5
	char *newargs[256];
E 5
I 5
	char *newargs[256], *execat();
E 5
	int i;
	register unsigned etxtbsy = 1;
	register eacces = 0;
E 7
I 7
	va_list ap;
	int sverrno;
	char **argv;
E 7

I 8
#if __STDC__
E 8
D 7
	if ((pathstr = getenv("PATH")) == NULL)
		pathstr = ":/bin:/usr/bin";
	cp = index(name, '/')? "": pathstr;
E 7
I 7
	va_start(ap, arg);
I 8
#else
	va_start(ap);
#endif
E 8
D 12
	if (argv = buildargv(ap, arg, (char ***)NULL))
E 12
I 12
	if (argv = buildargv(ap, arg, NULL))
E 12
		(void)execve(name, argv, environ);
	va_end(ap);
	sverrno = errno;
	free(argv);
	errno = sverrno;
D 12
	return(-1);
E 12
I 12
	return (-1);
E 12
}
E 7

D 7
	do {
		cp = execat(cp, name, fname);
	retry:
		execv(fname, argv);
E 7
I 7
D 8
int execle(const char *name, const char *arg, ...)
E 8
I 8
int
#if __STDC__
execle(const char *name, const char *arg, ...)
#else
execle(name, arg, va_alist)
	const char *name;
	const char *arg;
	va_dcl
#endif
E 8
{
	va_list ap;
	int sverrno;
	char **argv, **envp;

I 8
#if __STDC__
E 8
	va_start(ap, arg);
I 8
#else
	va_start(ap);
#endif
E 8
	if (argv = buildargv(ap, arg, &envp))
		(void)execve(name, argv, envp);
	va_end(ap);
	sverrno = errno;
	free(argv);
	errno = sverrno;
D 12
	return(-1);
E 12
I 12
	return (-1);
E 12
}

D 8
int execlp(const char *name, const char *arg, ...)
E 8
I 8
int
#if __STDC__
execlp(const char *name, const char *arg, ...)
#else
execlp(name, arg, va_alist)
	const char *name;
	const char *arg;
	va_dcl
#endif
E 8
{
	va_list ap;
	int sverrno;
	char **argv;

I 8
#if __STDC__
E 8
	va_start(ap, arg);
I 8
#else
	va_start(ap);
#endif
E 8
D 12
	if (argv = buildargv(ap, arg, (char ***)NULL))
E 12
I 12
	if (argv = buildargv(ap, arg, NULL))
E 12
		(void)execvp(name, argv);
	va_end(ap);
	sverrno = errno;
	free(argv);
	errno = sverrno;
D 12
	return(-1);
E 12
I 12
	return (-1);
E 12
}

D 8
int execv(const char *name, char * const *argv)
E 8
I 8
int
execv(name, argv)
	const char *name;
	char * const *argv;
E 8
{
	(void)execve(name, argv, environ);
D 12
	return(-1);
E 12
I 12
	return (-1);
E 12
}

D 8
int execvp(const char *name, char * const *argv)
E 8
I 8
int
execvp(name, argv)
	const char *name;
	char * const *argv;
E 8
{
I 11
D 12
	register int lp, ln;
E 12
I 12
	static int memsize;
	static char **memp;
	register int cnt, lp, ln;
E 12
E 11
	register char *p;
	int eacces, etxtbsy;
D 10
	char *cur, *path, buf[MAXPATHLEN];
E 10
I 10
	char *bp, *cur, *path, buf[MAXPATHLEN];
E 10

	/* If it's an absolute or relative path name, it's easy. */
	if (index(name, '/')) {
D 10
		(void)execve(name, argv, environ);
		return(-1);
E 10
I 10
		bp = (char *)name;
		cur = path = NULL;
		goto retry;
E 10
	}
I 10
	bp = buf;
E 10

	/* Get the path we're searching. */
	if (!(path = getenv("PATH")))
		path = _PATH_DEFPATH;
	cur = path = strdup(path);

	eacces = etxtbsy = 0;
	while (p = strsep(&cur, ":")) {
		/*
		 * It's a SHELL path -- double, leading and trailing colons
		 * mean the current directory.
		 */
D 11
		if (!*p)
E 11
I 11
		if (!*p) {
E 11
			p = ".";
D 11
		(void)snprintf(buf, sizeof(buf), "%s/%s", p, name);
E 11
I 11
			lp = 1;
		} else
			lp = strlen(p);
		ln = strlen(name);

		/*
		 * If the path is too long complain.  This is a possible
		 * security issue; given a way to make the path too long
		 * the user may execute the wrong program.
		 */
		if (lp + ln + 2 > sizeof(buf)) {
			(void)write(STDERR_FILENO, "execvp: ", 8);
			(void)write(STDERR_FILENO, p, lp);
			(void)write(STDERR_FILENO, ": path too long\n", 16);
			continue;
		}
		bcopy(p, buf, lp);
		buf[lp] = '/';
		bcopy(name, buf + lp + 1, ln);
		buf[lp + ln + 1] = '\0';
E 11

D 10
retry:		(void)execve(buf, argv, environ);
E 10
I 10
retry:		(void)execve(bp, argv, environ);
E 10
E 7
		switch(errno) {
D 7
		case ENOEXEC:
			newargs[0] = "sh";
			newargs[1] = fname;
			for (i=1; newargs[i+1]=argv[i]; i++) {
				if (i>=254) {
					errno = E2BIG;
					return(-1);
				}
E 7
I 7
		case EACCES:
			eacces = 1;
			break;
		case ENOENT:
			break;
D 12
		case ENOEXEC: {
			register size_t cnt;
			register char **ap;

			for (cnt = 0, ap = (char **)argv; *ap; ++ap, ++cnt);
			if (ap = malloc((cnt + 2) * sizeof(char *))) {
D 10
				bcopy(argv, ap + 2, cnt * sizeof(char *));
E 10
I 10
				bcopy(argv + 1, ap + 2, cnt * sizeof(char *));
E 10
				ap[0] = "sh";
D 10
				ap[1] = buf;
E 10
I 10
				ap[1] = bp;
E 10
				(void)execve(_PATH_BSHELL, ap, environ);
				free(ap);
E 12
I 12
		case ENOEXEC:
			for (cnt = 0; argv[cnt]; ++cnt);
			if ((cnt + 2) * sizeof(char *) > memsize) {
				memsize = (cnt + 2) * sizeof(char *);
				if ((memp = realloc(memp, memsize)) == NULL) {
					memsize = 0;
					goto done;
				}
E 12
E 7
			}
I 12
			memp[0] = "sh";
			memp[1] = bp;
			bcopy(argv + 1, memp + 2, cnt * sizeof(char *));
			(void)execve(_PATH_BSHELL, memp, environ);
E 12
D 7
			execv(shell, newargs);
			return(-1);
E 7
I 7
			goto done;
D 12
		}
E 12
E 7
		case ETXTBSY:
D 7
			if (++etxtbsy > 5)
				return(-1);
			sleep(etxtbsy);
E 7
I 7
			if (etxtbsy < 3)
				(void)sleep(++etxtbsy);
E 7
			goto retry;
D 7
		case EACCES:
			eacces++;
			break;
		case ENOMEM:
		case E2BIG:
			return(-1);
E 7
I 7
		default:
			goto done;
E 7
		}
D 7
	} while (cp);
E 7
I 7
	}
E 7
	if (eacces)
		errno = EACCES;
I 7
	else if (!errno)
		errno = ENOENT;
D 10
done:	free(path);
E 10
I 10
done:	if (path)
		free(path);
E 10
E 7
D 12
	return(-1);
E 12
I 12
	return (-1);
E 12
D 7
}

static char *
execat(s1, s2, si)
register char *s1, *s2;
char *si;
{
	register char *s;

	s = si;
D 2
	while (*s1 && *s1 != ':' && *s1 != '-')
E 2
I 2
	while (*s1 && *s1 != ':')
E 2
		*s++ = *s1++;
	if (si != s)
		*s++ = '/';
	while (*s2)
		*s++ = *s2++;
	*s = '\0';
	return(*s1? ++s1: 0);
E 7
}
E 1
