h31790
s 00002/00002/00392
d D 8.1 93/05/31 16:42:33 bostic 24 23
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00389
d D 5.19 93/05/22 19:06:42 christos 23 22
c Fixed gcc -Wall warnings
e
s 00002/00002/00392
d D 5.18 91/11/06 16:09:49 christos 22 21
c Added support for displaying non-printable characters
e
s 00000/00000/00394
d D 5.17 91/11/04 18:22:38 christos 21 20
c We need strstr now...
e
s 00012/00006/00382
d D 5.16 91/10/28 21:28:06 leres 20 19
c Fix gcc "bodyless for/while" warnings.
e
s 00003/00003/00385
d D 5.15 91/09/04 01:36:51 christos 19 18
c fix xfree() so it can be re-written as a macro
e
s 00006/00005/00382
d D 5.14 91/07/19 17:31:12 christos 18 17
c stdio based version; brace glob fix; builtin prototypes
e
s 00002/00000/00385
d D 5.13 91/06/27 19:36:35 christos 17 16
c dmove did not close always close the source file descriptor
e
s 00006/00000/00379
d D 5.12 91/06/08 17:08:55 christos 16 15
c More prototype fixes, Removed TERMIOS define
e
s 00003/00000/00376
d D 5.11 91/06/08 12:20:28 bostic 15 14
c include file pass, csh.h no longer include every .h in the system
c rename sigmast_t to sigset_t to match signal.h; minor pointer cleanups
e
s 00002/00002/00374
d D 5.10 91/06/07 20:57:34 christos 14 13
c static function prototypes
e
s 00003/00002/00373
d D 5.9 91/06/07 11:13:36 bostic 13 12
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00002/00002/00373
d D 5.8 91/06/05 16:33:21 christos 12 11
c Removed -DTELL V6 compatibility flag
e
s 00226/00211/00149
d D 5.7 91/06/04 13:31:48 bostic 11 10
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00007/00006/00353
d D 5.6 91/04/04 18:17:51 bostic 10 9
c new copyright; att/bsd/shared
e
s 00000/00024/00359
d D 5.5 91/03/14 12:32:46 bostic 9 8
c any -> index (use the faster library routine) 
c copy -> bcopy (more than vax and tahoe now)
e
s 00000/00000/00383
d D 5.4 89/02/15 11:06:44 bostic 8 7
c use pathname include files; remove IIASA commands; remove newgrp
c command; add globall .cshrc, .login, and .logout files; minor cleanups
e
s 00003/00026/00380
d D 5.3 86/03/29 07:37:21 lepreau 7 6
c Minor speedups & cleanups:
c replace letter() et al with ctype-like cmap macros and expand cmap to short
c for new LET and DIG bits; use bzero in private calloc; make btell a macro.
e
s 00003/00003/00403
d D 5.2 85/06/06 13:10:06 edward 6 5
c cleaning up after bozos
e
s 00008/00002/00398
d D 5.1 85/06/04 11:05:44 dist 5 4
c Add copyright
e
s 00096/00063/00304
d D 4.4 84/12/13 14:40:33 edward 4 3
c performance
e
s 00000/00007/00367
d D 4.3 84/08/31 09:31:25 ralph 3 2
c use new signal calls instead of compatibility routines.
e
s 00002/00000/00372
d D 4.2 84/07/06 22:41:52 sam 2 1
c turn copy() into bcopy(); fix up profiling
e
s 00372/00000/00000
d D 4.1 80/10/09 12:41:25 bill 1 0
c date and time created 80/10/09 12:41:25 by bill
e
u
U
t
T
I 5
D 10
/*
 * Copyright (c) 1980 Regents of the University of California.
D 6
 * All rights reserved.  The Berkeley software License Agreement
E 6
I 6
 * All rights reserved.  The Berkeley Software License Agreement
E 6
 * specifies the terms and conditions for redistribution.
E 10
I 10
/*-
D 24
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 24
I 24
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 24
 *
 * %sccs.include.redist.c%
E 10
 */

E 5
I 1
D 4
static	char *sccsid = "%Z%%M% %I% %G%";
E 4
I 4
#ifndef lint
D 5
static	char *sccsid = "%W% (Berkeley) %G%";
#endif
E 5
I 5
D 6
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 6
I 6
D 10
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 10
I 10
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 10
E 6
E 5
E 4

I 15
#include <sys/param.h>
#include <stdlib.h>
#include <unistd.h>
I 16
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif

E 16
E 15
D 13
#include "sh.h"
E 13
I 13
#include "csh.h"
#include "extern.h"
E 13

D 11
/*
 * C Shell
 */
E 11
I 11
D 14
static int renum();
E 14
I 14
static int	renum __P((int, int));
E 14
E 11

D 7
letter(c)
	register char c;
{

	return (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_');
}

digit(c)
	register char c;
{

	return (c >= '0' && c <= '9');
}

alnum(c)
	register char c;
{
	return (letter(c) || digit(c));
}

E 7
D 9
any(c, s)
	register int c;
	register char *s;
{

	while (*s)
		if (*s++ == c)
			return(1);
	return(0);
}

E 9
I 4
D 11
onlyread(cp)
	char *cp;
E 11
I 11
int
any(s, c)
    register char *s;
    register int c;
E 11
{
D 11
	extern char end[];

	return (cp < end);
E 11
I 11
    if (!s)
	return (0);		/* Check for nil pointer */
    while (*s)
	if (*s++ == c)
	    return (1);
    return (0);
E 11
}

D 11
xfree(cp)
	char *cp;
E 11
I 11
void
setzero(cp, i)
    char   *cp;
    int     i;
E 11
{
D 11
	extern char end[];

	if (cp >= end && cp < (char *) &cp)
		free(cp);
E 11
I 11
    if (i != 0)
	do
	    *cp++ = 0;
	while (--i);
E 11
}

E 4
D 11
char *
I 4
savestr(s)
	register char *s;
E 11
I 11
char   *
strsave(s)
    register char *s;
E 11
{
D 11
	char *n;
	register char *p;
E 11
I 11
    char   *n;
    register char *p;
E 11

D 11
	if (s == 0)
		s = "";
	for (p = s; *p++;)
		;
	n = p = xalloc((unsigned) (p - s));
	while (*p++ = *s++)
		;
	return (n);
E 11
I 11
D 13
    if (s == 0)
E 13
I 13
    if (s == NULL)
E 13
	s = "";
D 20
    for (p = s; *p++;);
E 20
I 20
    for (p = s; *p++;)
	continue;
E 20
    n = p = (char *) xmalloc((size_t) ((p - s) * sizeof(char)));
D 20
    while (*p++ = *s++);
E 20
I 20
D 23
    while (*p++ = *s++)
E 23
I 23
    while ((*p++ = *s++) != '\0')
E 23
	continue;
E 20
    return (n);
E 11
}

D 11
char *
E 4
calloc(i, j)
	register unsigned i;
	unsigned j;
E 11
I 11
Char  **
blkend(up)
    register Char **up;
E 11
{
D 7
	register char *cp, *dp;
E 7
I 7
D 11
	char *cp;
E 11
E 7
D 4
#ifdef debug
	static char *av[2] = {0, 0};
#endif
E 4

D 11
	i *= j;
D 4
	cp = (char *) malloc(i);
	if (cp == 0) {
		child++;
#ifndef debug
		error("Out of memory");
#else
		showall(av);
		printf("i=%d, j=%d: ", i/j, j);
		printf("Out of memory\n");
		chdir("/usr/bill/cshcore");
		abort();
#endif
	}
	dp = cp;
E 4
I 4
D 7
	dp = cp = xalloc(i);
E 4
	if (i != 0)
		do
			*dp++ = 0;
		while (--i);
E 7
I 7
	cp = xalloc(i);
	bzero(cp, (int)i);
E 7
	return (cp);
E 11
I 11
    while (*up)
	up++;
    return (up);
E 11
}

I 4
D 11
nomem(i)
	unsigned i;
{
#ifdef debug
	static char *av[2] = {0, 0};
#endif
E 11

D 11
	child++;
#ifndef debug
	error("Out of memory");
#ifdef lint
	i = i;
#endif
#else
	showall(av);
	printf("i=%d: Out of memory\n", i);
	chdir("/usr/bill/cshcore");
	abort();
#endif
	return 0;		/* fool lint */
}

E 4
D 3
cfree(p)
	char *p;
{

	free(p);
}

E 3
char **
blkend(up)
	register char **up;
{

	while (*up)
		up++;
	return (up);
}
 
E 11
I 11
void
E 11
D 18
blkpr(av)
E 18
I 18
blkpr(fp, av)
    FILE *fp;
E 18
D 11
	register char **av;
E 11
I 11
    register Char **av;
E 11
{

D 11
	for (; *av; av++) {
		printf("%s", *av);
		if (av[1])
			printf(" ");
	}
E 11
I 11
    for (; *av; av++) {
D 18
	xprintf("%s", short2str(*av));
E 18
I 18
D 22
	(void) fprintf(fp, "%s", short2str(*av));
E 22
I 22
	(void) fprintf(fp, "%s", vis_str(*av));
E 22
E 18
	if (av[1])
D 18
	    xprintf(" ");
E 18
I 18
	    (void) fprintf(fp, " ");
E 18
    }
E 11
}

I 11
int
E 11
blklen(av)
D 11
	register char **av;
E 11
I 11
    register Char **av;
E 11
{
D 11
	register int i = 0;
E 11
I 11
    register int i = 0;
E 11

D 11
	while (*av++)
		i++;
	return (i);
E 11
I 11
    while (*av++)
	i++;
    return (i);
E 11
}

D 11
char **
E 11
I 11
Char  **
E 11
blkcpy(oav, bv)
D 11
	char **oav;
	register char **bv;
E 11
I 11
    Char  **oav;
    register Char **bv;
E 11
{
D 11
	register char **av = oav;
E 11
I 11
    register Char **av = oav;
E 11

D 11
	while (*av++ = *bv++)
		continue;
	return (oav);
E 11
I 11
D 23
    while (*av++ = *bv++)
E 23
I 23
    while ((*av++ = *bv++) != NULL)
E 23
	continue;
    return (oav);
E 11
}

D 11
char **
E 11
I 11
Char  **
E 11
blkcat(up, vp)
D 11
	char **up, **vp;
E 11
I 11
    Char  **up, **vp;
E 11
{

D 4
	blkcpy(blkend(up), vp);
E 4
I 4
D 11
	(void) blkcpy(blkend(up), vp);
E 4
	return (up);
E 11
I 11
    (void) blkcpy(blkend(up), vp);
    return (up);
E 11
}

I 11
void
E 11
blkfree(av0)
D 11
	char **av0;
E 11
I 11
    Char  **av0;
E 11
{
D 11
	register char **av = av0;
E 11
I 11
    register Char **av = av0;
E 11

D 4
	while (*av)
		xfree(*av++);
	xfree((char *)av0);
E 4
I 4
D 11
	for (; *av; av++)
		XFREE(*av)
	XFREE((char *)av0)
E 11
I 11
    if (!av0)
	return;
    for (; *av; av++)
	xfree((ptr_t) * av);
    xfree((ptr_t) av0);
E 11
E 4
}

D 11
char **
E 11
I 11
Char  **
E 11
saveblk(v)
D 11
	register char **v;
E 11
I 11
    register Char **v;
E 11
{
D 4
	register int len = blklen(v) + 1;
	register char **newv = (char **) calloc(len, sizeof (char **));
E 4
I 4
D 11
	register char **newv =
		(char **) calloc((unsigned) (blklen(v) + 1), sizeof (char **));
E 4
	char **onewv = newv;
E 11
I 11
    register Char **newv =
    (Char **) xcalloc((size_t) (blklen(v) + 1), sizeof(Char **));
    Char  **onewv = newv;
E 11

D 11
	while (*v)
		*newv++ = savestr(*v++);
	return (onewv);
E 11
I 11
    while (*v)
	*newv++ = Strsave(*v++);
    return (onewv);
E 11
}

D 11
char *
E 11
I 11
D 12
#ifdef notdef
E 12
I 12
#ifdef NOTUSED
E 12
char   *
strstr(s, t)
    register char *s, *t;
{
    do {
	register char *ss = s;
	register char *tt = t;

	do
	    if (*tt == '\0')
		return (s);
	while (*ss++ == *tt++);
    } while (*s++ != '\0');
D 14
    return ((char *) 0);
E 14
I 14
    return (NULL);
E 14
}

D 12
#endif				/* notdef */
E 12
I 12
#endif /* NOTUSED */
E 12

#ifndef SHORT_STRINGS
char   *
E 11
strspl(cp, dp)
D 4
	register char *cp, *dp;
E 4
I 4
D 11
	char *cp, *dp;
E 11
I 11
    char   *cp, *dp;
E 11
E 4
{
D 4
	register char *ep = calloc(1, strlen(cp) + strlen(dp) + 1);
E 4
I 4
D 11
	char *ep;
	register char *p, *q;
E 11
I 11
    char   *ep;
    register char *p, *q;
E 11
E 4

D 4
	strcpy(ep, cp);
	strcat(ep, dp);
E 4
I 4
D 11
	for (p = cp; *p++;)
		;
	for (q = dp; *q++;)
		;
	ep = xalloc((unsigned) ((p - cp) + (q - dp) - 1));
	for (p = ep, q = cp; *p++ = *q++;)
		;
	for (p--, q = dp; *p++ = *q++;)
		;
E 4
	return (ep);
E 11
I 11
    if (!cp)
	cp = "";
    if (!dp)
	dp = "";
D 20
    for (p = cp; *p++;);
    for (q = dp; *q++;);
E 20
I 20
    for (p = cp; *p++;)
	continue;
    for (q = dp; *q++;)
	continue;
E 20
    ep = (char *) xmalloc((size_t) (((p - cp) + (q - dp) - 1) * sizeof(char)));
D 20
    for (p = ep, q = cp; *p++ = *q++;);
    for (p--, q = dp; *p++ = *q++;);
E 20
I 20
    for (p = ep, q = cp; *p++ = *q++;)
	continue;
    for (p--, q = dp; *p++ = *q++;)
	continue;
E 20
    return (ep);
E 11
}

D 11
char **
E 11
I 11
#endif

Char  **
E 11
blkspl(up, vp)
D 11
	register char **up, **vp;
E 11
I 11
    register Char **up, **vp;
E 11
{
D 4
	register char **wp = (char **) calloc(blklen(up) + blklen(vp) + 1, sizeof (char **));
E 4
I 4
D 11
	register char **wp =
		(char **) calloc((unsigned) (blklen(up) + blklen(vp) + 1),
			sizeof (char **));
E 11
I 11
    register Char **wp =
    (Char **) xcalloc((size_t) (blklen(up) + blklen(vp) + 1),
		      sizeof(Char **));
E 11
E 4

D 4
	blkcpy(wp, up);
E 4
I 4
D 11
	(void) blkcpy(wp, up);
E 4
	return (blkcat(wp, vp));
E 11
I 11
    (void) blkcpy(wp, up);
    return (blkcat(wp, vp));
E 11
}

I 11
Char
E 11
lastchr(cp)
D 11
	register char *cp;
E 11
I 11
    register Char *cp;
E 11
{

D 11
	if (!*cp)
		return (0);
	while (cp[1])
		cp++;
	return (*cp);
E 11
I 11
    if (!cp)
	return (0);
    if (!*cp)
	return (0);
    while (cp[1])
	cp++;
    return (*cp);
E 11
}

/*
 * This routine is called after an error to close up
 * any units which may have been left open accidentally.
 */
I 11
void
E 11
closem()
{
D 11
	register int f;
E 11
I 11
    register int f;
E 11

D 11
	for (f = 0; f < NOFILE; f++)
		if (f != SHIN && f != SHOUT && f != SHDIAG && f != OLDSTD &&
		    f != FSHTTY)
D 4
			close(f);
E 4
I 4
			(void) close(f);
E 11
I 11
    for (f = 0; f < NOFILE; f++)
D 18
	if (f != SHIN && f != SHOUT && f != SHDIAG && f != OLDSTD &&
E 18
I 18
	if (f != SHIN && f != SHOUT && f != SHERR && f != OLDSTD &&
E 18
	    f != FSHTTY)
	    (void) close(f);
E 11
E 4
}

I 11
void
E 11
D 4
/*
 * Close files before executing a file.
 * We could be MUCH more intelligent, since (on a version 7 system)
 * we need only close files here during a source, the other
 * shell fd's being in units 16-19 which are closed automatically!
 */
closech()
{
	register int f;

	if (didcch)
		return;
	didcch = 1;
	SHIN = 0; SHOUT = 1; SHDIAG = 2; OLDSTD = 0;
	for (f = 3; f < NOFILE; f++)
		close(f);
}

E 4
donefds()
{
D 18

E 18
D 4
	close(0), close(1), close(2);
E 4
I 4
D 11
	(void) close(0);
	(void) close(1);
	(void) close(2);
E 4
	didfds = 0;
E 11
I 11
    (void) close(0);
    (void) close(1);
    (void) close(2);
I 18

E 18
    didfds = 0;
E 11
}

/*
 * Move descriptor i to j.
 * If j is -1 then we just want to get i to a safe place,
 * i.e. to a unit > 2.  This also happens in dcopy.
 */
I 11
int
E 11
dmove(i, j)
D 11
	register int i, j;
E 11
I 11
    register int i, j;
E 11
{

D 11
	if (i == j || i < 0)
		return (i);
D 4
#ifdef V7
E 4
	if (j >= 0) {
D 4
		dup2(i, j);
E 4
I 4
		(void) dup2(i, j);
E 4
		return (j);
D 4
	} else
#endif
		j = dcopy(i, j);
E 4
I 4
	}
	j = dcopy(i, j);
E 4
	if (j != i)
D 4
		close(i);
E 4
I 4
		(void) close(i);
E 11
I 11
    if (i == j || i < 0)
	return (i);
    if (j >= 0) {
	(void) dup2(i, j);
I 17
	if (j != i)
	    (void) close(i);
E 17
E 11
E 4
	return (j);
I 11
    }
    j = dcopy(i, j);
    if (j != i)
	(void) close(i);
    return (j);
E 11
}

I 11
int
E 11
dcopy(i, j)
D 11
	register int i, j;
E 11
I 11
    register int i, j;
E 11
{

D 11
	if (i == j || i < 0 || j < 0 && i > 2)
		return (i);
D 4
#ifdef V7
E 4
	if (j >= 0) {
D 4
		dup2(i, j);
E 4
I 4
		(void) dup2(i, j);
E 4
		return (j);
	}
D 4
#endif
	close(j);
E 4
I 4
	(void) close(j);
E 4
	return (renum(i, j));
E 11
I 11
D 23
    if (i == j || i < 0 || j < 0 && i > 2)
E 23
I 23
    if (i == j || i < 0 || (j < 0 && i > 2))
E 23
	return (i);
    if (j >= 0) {
	(void) dup2(i, j);
	return (j);
    }
    (void) close(j);
    return (renum(i, j));
E 11
}

I 11
static int
E 11
renum(i, j)
D 11
	register int i, j;
E 11
I 11
    register int i, j;
E 11
{
D 11
	register int k = dup(i);
E 11
I 11
    register int k = dup(i);
E 11

D 11
	if (k < 0)
		return (-1);
	if (j == -1 && k > 2)
		return (k);
	if (k != j) {
		j = renum(k, j);
D 4
		close(k);
E 4
I 4
		(void) close(k);
E 4
		return (j);
	}
E 11
I 11
    if (k < 0)
	return (-1);
    if (j == -1 && k > 2)
E 11
	return (k);
I 11
    if (k != j) {
	j = renum(k, j);
	(void) close(k);
	return (j);
    }
    return (k);
E 11
}
D 9

I 2
#ifndef copy
E 2
copy(to, from, size)
	register char *to, *from;
	register int size;
{

	if (size)
		do
			*to++ = *from++;
		while (--size != 0);
}
I 2
#endif
E 9
E 2

/*
 * Left shift a command argument list, discarding
 * the first c arguments.  Used in "shift" commands
 * as well as by commands like "repeat".
 */
I 11
void
E 11
lshift(v, c)
D 11
	register char **v;
	register int c;
E 11
I 11
    register Char **v;
    register int c;
E 11
{
D 11
	register char **u = v;
E 11
I 11
D 19
    register Char **u = v;
E 19
I 19
    register Char **u;
E 19
E 11

D 11
	while (*u && --c >= 0)
		xfree(*u++);
D 4
	blkcpy(v, u);
E 4
I 4
	(void) blkcpy(v, u);
E 11
I 11
D 19
    while (*u && --c >= 0)
	xfree((ptr_t) * u++);
E 19
I 19
    for (u = v; *u && --c >= 0; u++)
	xfree((ptr_t) *u);
E 19
    (void) blkcpy(v, u);
E 11
E 4
}

I 11
int
E 11
number(cp)
D 11
	char *cp;
E 11
I 11
    Char   *cp;
E 11
{
D 11

	if (*cp == '-') {
		cp++;
		if (!digit(*cp++))
			return (0);
	}
	while (*cp && digit(*cp))
		cp++;
	return (*cp == 0);
E 11
I 11
    if (!cp)
	return(0);
    if (*cp == '-') {
	cp++;
	if (!Isdigit(*cp))
	    return (0);
	cp++;
    }
    while (*cp && Isdigit(*cp))
	cp++;
    return (*cp == 0);
E 11
}

D 11
char **
E 11
I 11
Char  **
E 11
copyblk(v)
D 11
	register char **v;
E 11
I 11
    register Char **v;
E 11
{
D 4
	register char **nv = (char **) calloc(blklen(v) + 1, sizeof (char **));
E 4
I 4
D 11
	register char **nv =
		(char **) calloc((unsigned) (blklen(v) + 1), sizeof (char **));
E 11
I 11
    Char  **nv = (Char **) xcalloc((size_t) (blklen(v) + 1), sizeof(Char **));
E 11
E 4

D 11
	return (blkcpy(nv, v));
E 11
I 11
    return (blkcpy(nv, v));
E 11
}

D 11
char *
E 11
I 11
#ifndef SHORT_STRINGS
char   *
E 11
strend(cp)
D 11
	register char *cp;
E 11
I 11
    register char *cp;
E 11
{
D 11

	while (*cp)
		cp++;
E 11
I 11
    if (!cp)
E 11
	return (cp);
I 11
    while (*cp)
	cp++;
    return (cp);
E 11
}

D 11
char *
E 11
I 11
D 23
#endif				/* SHORT_STRINGS */
E 23
I 23
#endif /* SHORT_STRINGS */
E 23

Char   *
E 11
strip(cp)
D 11
	char *cp;
E 11
I 11
    Char   *cp;
E 11
{
D 11
	register char *dp = cp;
E 11
I 11
    register Char *dp = cp;
E 11

D 11
	while (*dp++ &= TRIM)
		continue;
E 11
I 11
    if (!cp)
E 11
	return (cp);
I 11
D 23
    while (*dp++ &= TRIM)
E 23
I 23
    while ((*dp++ &= TRIM) != '\0')
E 23
	continue;
    return (cp);
E 11
}

I 11
void
E 11
udvar(name)
D 11
	char *name;
E 11
I 11
    Char   *name;
E 11
{

D 11
	setname(name);
	bferr("Undefined variable");
E 11
I 11
D 22
    setname(short2str(name));
E 22
I 22
    setname(vis_str(name));
E 22
    stderror(ERR_NAME | ERR_UNDVAR);
E 11
}

I 11
int
E 11
prefix(sub, str)
D 11
	register char *sub, *str;
E 11
I 11
    register Char *sub, *str;
E 11
{

D 11
	for (;;) {
		if (*sub == 0)
			return (1);
		if (*str == 0)
			return (0);
		if (*sub++ != *str++)
			return (0);
	}
E 11
I 11
    for (;;) {
	if (*sub == 0)
	    return (1);
	if (*str == 0)
	    return (0);
	if (*sub++ != *str++)
	    return (0);
    }
E 11
}
E 1
