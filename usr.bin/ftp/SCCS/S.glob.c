h24368
s 00001/00001/00678
d D 8.3 94/04/02 15:11:13 pendry 15 14
c add 1994 copyright
e
s 00089/00064/00590
d D 8.2 94/04/02 15:06:56 pendry 14 13
c prettyness police
e
s 00002/00002/00652
d D 8.1 93/06/06 14:41:18 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00024/00020/00630
d D 5.9 91/02/25 16:42:07 bostic 12 11
c ANSI fixes, struct direct -> struct dirent, rename glob() -> ftpglob()
e
s 00001/00011/00649
d D 5.8 90/06/01 15:52:05 bostic 11 10
c new copyright notice
e
s 00000/00001/00660
d D 5.7 88/12/14 15:37:59 bostic 10 9
c globbing allocation/freeing wrong; bug report 4.3BSD/etc/149
e
s 00001/00001/00660
d D 5.6 88/11/30 20:29:17 bostic 9 8
c Rick Adams for Bill Scherlis, the night that MilNet died
e
s 00002/00002/00659
d D 5.5 88/11/14 18:51:58 bostic 8 7
c From: jqj@hogg.cc.uoregon.edu
c cc -O  -sun3 -c  glob.c
c "glob.c", line 482: warning: constant 174761 is out of range of short comparison
c "glob.c", line 482: warning: result of comparison is always false
c Analysis:  on SUN, NCARGS is 0x100000, so NCARGS/6-1 is too big for a short.
e
s 00010/00005/00651
d D 5.4 88/06/29 20:34:25 bostic 7 6
c install approved copyright notice
e
s 00009/00003/00647
d D 5.3 88/03/14 17:21:41 bostic 6 5
c add Berkeley specific headers
e
s 00012/00013/00638
d D 5.2 86/03/07 12:32:02 minshall 5 4
c Clean up for lint; change some stderr to stdout; bug fix
c (in ruserpass.c, routine rnetrc()).
e
s 00008/00002/00643
d D 5.1 85/05/31 17:01:53 dist 4 3
c Add copyright
e
s 00002/00002/00643
d D 4.3 85/05/11 15:15:55 sam 3 2
c make copyblk public for use in ftpd
e
s 00001/00001/00644
d D 4.2 83/03/01 02:11:05 sam 2 1
c nothing much
e
s 00645/00000/00000
d D 4.1 83/01/14 00:01:41 sam 1 0
c date and time created 83/01/14 00:01:41 by sam
e
u
U
t
T
I 4
/*
D 13
 * Copyright (c) 1980 Regents of the University of California.
D 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * All rights reserved.
E 13
I 13
D 15
 * Copyright (c) 1980, 1993
E 15
I 15
 * Copyright (c) 1980, 1993, 1994
E 15
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 11
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
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 7
E 6
 */

E 4
I 1
#ifndef lint
D 4
static char sccsid[] = "%W% %G%";
#endif
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6
E 4

/*
 * C-shell glob for random programs.
 */

#include <sys/param.h>
#include <sys/stat.h>
D 12
#include <sys/dir.h>
E 12
I 12
D 14
#include <dirent.h>
E 14
E 12

D 12
#include <stdio.h>
#include <errno.h>
E 12
D 14
#include <pwd.h>
E 14
I 14
#include <dirent.h>
E 14
I 12
#include <errno.h>
I 14
#include <pwd.h>
#include <setjmp.h>
E 14
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
E 12

I 14
#include "extern.h"

E 14
#define	QUOTE 0200
#define	TRIM 0177
#define	eq(a,b)		(strcmp(a, b)==0)
#define	GAVSIZ		(NCARGS/6)
#define	isdir(d)	((d.st_mode & S_IFMT) == S_IFDIR)

I 14
char	*globerr;
char	*home;

E 14
static	char **gargv;		/* Pointer to the (stack) arglist */
D 8
static	short gargc;		/* Number args in gargv */
static	short gnleft;
E 8
I 8
static	int gargc;		/* Number args in gargv */
static	int gnleft;
E 8
static	short gflag;
D 14
static	int tglob();
D 12
char	**glob();
E 12
I 12
char	**ftpglob();
E 12
char	*globerr;
char	*home;
D 12
struct	passwd *getpwnam();
E 12
extern	int errno;
D 3
static	char *strspl(), **copyblk(), *strend();
E 3
I 3
static	char *strspl(), *strend();
E 3
D 12
char	*malloc(), *strcpy(), *strcat();
E 12
I 3
char	**copyblk();
E 14
E 3

I 12
D 14
static void acollect(), addpath(), collect(), expand(), Gcat();
static void ginit(), matchdir(), rscan(), sort();
static int amatch(), execbrc(), match();
E 14
I 14
static void	Gcat __P((char *, char *));
static int	Gmatch __P((char *, char *));
static void	acollect __P((char *));
static void	addpath __P((int));
static int	amatch __P((char *, char *));
static int	any __P((int, char *));
static int	blklen __P((char **));
static void	collect __P((char *));
static char   **copyblk __P((char **));
static int	digit __P((int));
static int	execbrc __P((char *, char *));
static void	expand __P((char *));
static int	gethdir __P((char *));
static void	ginit __P((char **));
static int	letter __P((int));
static int	match __P((char *, char *));
static void	matchdir __P((char *));
static void	rscan __P((char **, int (*)(int)));
static void	sort __P((void));
static char    *strend __P((char *));
static char    *strspl __P((char *, char *));
static int	tglob __P((int));
E 14

E 12
static	int globcnt;

char	*globchars = "`{[*?";

static	char *gpath, *gpathp, *lastgpathp;
static	int globbed;
static	char *entp;
static	char **sortbas;

char **
D 12
glob(v)
E 12
I 12
ftpglob(v)
E 12
D 14
	register char *v;
E 14
I 14
	char *v;
E 14
{
	char agpath[BUFSIZ];
	char *agargv[GAVSIZ];
	char *vv[2];
	vv[0] = v;
	vv[1] = 0;
	gflag = 0;
	rscan(vv, tglob);
	if (gflag == 0)
D 2
		return copyblk(vv);
E 2
I 2
		return (copyblk(vv));
E 2

	globerr = 0;
	gpath = agpath; gpathp = gpath; *gpathp = 0;
	lastgpathp = &gpath[sizeof agpath - 2];
	ginit(agargv); globcnt = 0;
	collect(v);
	if (globcnt == 0 && (gflag&1)) {
		blkfree(gargv), gargv = 0;
		return (0);
	} else
		return (gargv = copyblk(gargv));
}

D 12
static
E 12
I 12
static void
E 12
ginit(agargv)
	char **agargv;
{

	agargv[0] = 0; gargv = agargv; sortbas = agargv; gargc = 0;
	gnleft = NCARGS - 4;
}

D 12
static
E 12
I 12
static void
E 12
collect(as)
D 14
	register char *as;
E 14
I 14
	char *as;
E 14
{
	if (eq(as, "{") || eq(as, "{}")) {
		Gcat(as, "");
		sort();
	} else
		acollect(as);
}

D 12
static
E 12
I 12
static void
E 12
acollect(as)
D 14
	register char *as;
E 14
I 14
	char *as;
E 14
{
D 14
	register int ogargc = gargc;
E 14
I 14
	int ogargc = gargc;
E 14

	gpathp = gpath; *gpathp = 0; globbed = 0;
	expand(as);
	if (gargc != ogargc)
		sort();
}

D 12
static
E 12
I 12
static void
E 12
sort()
{
D 14
	register char **p1, **p2, *c;
E 14
I 14
	char **p1, **p2, *c;
E 14
	char **Gvp = &gargv[gargc];

	p1 = sortbas;
	while (p1 < Gvp-1) {
		p2 = p1;
		while (++p2 < Gvp)
			if (strcmp(*p1, *p2) > 0)
				c = *p1, *p1 = *p2, *p2 = c;
		p1++;
	}
	sortbas = Gvp;
}

D 12
static
E 12
I 12
static void
E 12
expand(as)
	char *as;
{
D 14
	register char *cs;
	register char *sgpathp, *oldcs;
E 14
I 14
	char *cs;
	char *sgpathp, *oldcs;
E 14
	struct stat stb;

	sgpathp = gpathp;
	cs = as;
	if (*cs == '~' && gpathp == gpath) {
		addpath('~');
		for (cs++; letter(*cs) || digit(*cs) || *cs == '-';)
			addpath(*cs++);
		if (!*cs || *cs == '/') {
			if (gpathp != gpath + 1) {
				*gpathp = 0;
				if (gethdir(gpath + 1))
					globerr = "Unknown user name after ~";
D 5
				strcpy(gpath, gpath + 1);
E 5
I 5
				(void) strcpy(gpath, gpath + 1);
E 5
			} else
D 5
				strcpy(gpath, home);
E 5
I 5
				(void) strcpy(gpath, home);
E 5
			gpathp = strend(gpath);
		}
	}
	while (!any(*cs, globchars)) {
		if (*cs == 0) {
			if (!globbed)
				Gcat(gpath, "");
			else if (stat(gpath, &stb) >= 0) {
				Gcat(gpath, "");
				globcnt++;
			}
			goto endit;
		}
		addpath(*cs++);
	}
	oldcs = cs;
	while (cs > as && *cs != '/')
		cs--, gpathp--;
	if (*cs == '/')
		cs++, gpathp++;
	*gpathp = 0;
	if (*oldcs == '{') {
D 5
		execbrc(cs, ((char *)0));
E 5
I 5
		(void) execbrc(cs, ((char *)0));
E 5
		return;
	}
	matchdir(cs);
endit:
	gpathp = sgpathp;
	*gpathp = 0;
}

D 12
static
E 12
I 12
static void
E 12
matchdir(pattern)
	char *pattern;
{
	struct stat stb;
D 12
	register struct direct *dp;
E 12
I 12
D 14
	register struct dirent *dp;
E 14
I 14
	struct dirent *dp;
E 14
E 12
	DIR *dirp;
D 5
	register int cnt;
E 5

	dirp = opendir(gpath);
	if (dirp == NULL) {
		if (globbed)
			return;
		goto patherr2;
	}
	if (fstat(dirp->dd_fd, &stb) < 0)
		goto patherr1;
	if (!isdir(stb)) {
		errno = ENOTDIR;
		goto patherr1;
	}
	while ((dp = readdir(dirp)) != NULL) {
		if (dp->d_ino == 0)
			continue;
		if (match(dp->d_name, pattern)) {
			Gcat(gpath, dp->d_name);
			globcnt++;
		}
	}
	closedir(dirp);
	return;

patherr1:
	closedir(dirp);
patherr2:
	globerr = "Bad directory components";
}

D 12
static
E 12
I 12
static int
E 12
execbrc(p, s)
	char *p, *s;
{
	char restbuf[BUFSIZ + 2];
D 14
	register char *pe, *pm, *pl;
E 14
I 14
	char *pe, *pm, *pl;
E 14
	int brclev = 0;
	char *lm, savec, *sgpathp;

	for (lm = restbuf; *p != '{'; *lm++ = *p++)
		continue;
	for (pe = ++p; *pe; pe++)
	switch (*pe) {

	case '{':
		brclev++;
		continue;

	case '}':
		if (brclev == 0)
			goto pend;
		brclev--;
		continue;

	case '[':
		for (pe++; *pe && *pe != ']'; pe++)
			continue;
		continue;
	}
pend:
	brclev = 0;
	for (pl = pm = p; pm <= pe; pm++)
	switch (*pm & (QUOTE|TRIM)) {

	case '{':
		brclev++;
		continue;

	case '}':
		if (brclev) {
			brclev--;
			continue;
		}
		goto doit;

	case ','|QUOTE:
	case ',':
		if (brclev)
			continue;
doit:
		savec = *pm;
		*pm = 0;
D 5
		strcpy(lm, pl);
		strcat(restbuf, pe + 1);
E 5
I 5
		(void) strcpy(lm, pl);
		(void) strcat(restbuf, pe + 1);
E 5
		*pm = savec;
		if (s == 0) {
			sgpathp = gpathp;
			expand(restbuf);
			gpathp = sgpathp;
			*gpathp = 0;
		} else if (amatch(s, restbuf))
			return (1);
		sort();
		pl = pm + 1;
		if (brclev)
			return (0);
		continue;

	case '[':
		for (pm++; *pm && *pm != ']'; pm++)
			continue;
		if (!*pm)
			pm--;
		continue;
	}
	if (brclev)
		goto doit;
	return (0);
}

D 12
static
E 12
I 12
static int
E 12
match(s, p)
	char *s, *p;
{
D 14
	register int c;
	register char *sentp;
E 14
I 14
	int c;
	char *sentp;
E 14
	char sglobbed = globbed;

	if (*s == '.' && *p != '.')
		return (0);
	sentp = entp;
	entp = s;
	c = amatch(s, p);
	entp = sentp;
	globbed = sglobbed;
	return (c);
}

D 12
static
E 12
I 12
static int
E 12
amatch(s, p)
D 14
	register char *s, *p;
E 14
I 14
	char *s, *p;
E 14
{
D 14
	register int scc;
E 14
I 14
	int scc;
E 14
	int ok, lc;
	char *sgpathp;
	struct stat stb;
	int c, cc;

	globbed = 1;
	for (;;) {
		scc = *s++ & TRIM;
		switch (c = *p++) {

		case '{':
			return (execbrc(p - 1, s - 1));

		case '[':
			ok = 0;
			lc = 077777;
			while (cc = *p++) {
				if (cc == ']') {
					if (ok)
						break;
					return (0);
				}
				if (cc == '-') {
					if (lc <= scc && scc <= *p++)
						ok++;
				} else
					if (scc == (lc = cc))
						ok++;
			}
			if (cc == 0)
				if (ok)
					p--;
				else
					return 0;
			continue;

		case '*':
			if (!*p)
				return (1);
			if (*p == '/') {
				p++;
				goto slash;
			}
			s--;
			do {
				if (amatch(s, p))
					return (1);
			} while (*s++);
			return (0);

		case 0:
			return (scc == 0);

		default:
			if (c != scc)
				return (0);
			continue;

		case '?':
			if (scc == 0)
				return (0);
			continue;

		case '/':
			if (scc)
				return (0);
slash:
			s = entp;
			sgpathp = gpathp;
			while (*s)
				addpath(*s++);
			addpath('/');
			if (stat(gpath, &stb) == 0 && isdir(stb))
				if (*p == 0) {
					Gcat(gpath, "");
					globcnt++;
				} else
					expand(p);
			gpathp = sgpathp;
			*gpathp = 0;
			return (0);
		}
	}
}

D 14
static
E 14
I 14
static int
E 14
Gmatch(s, p)
D 14
	register char *s, *p;
E 14
I 14
	char *s, *p;
E 14
{
D 14
	register int scc;
E 14
I 14
	int scc;
E 14
	int ok, lc;
	int c, cc;

	for (;;) {
		scc = *s++ & TRIM;
		switch (c = *p++) {

		case '[':
			ok = 0;
			lc = 077777;
			while (cc = *p++) {
				if (cc == ']') {
					if (ok)
						break;
					return (0);
				}
				if (cc == '-') {
					if (lc <= scc && scc <= *p++)
						ok++;
				} else
					if (scc == (lc = cc))
						ok++;
			}
			if (cc == 0)
				if (ok)
					p--;
				else
					return 0;
			continue;

		case '*':
			if (!*p)
				return (1);
			for (s--; *s; s++)
				if (Gmatch(s, p))
					return (1);
			return (0);

		case 0:
			return (scc == 0);

		default:
			if ((c & TRIM) != scc)
				return (0);
			continue;

		case '?':
			if (scc == 0)
				return (0);
			continue;

		}
	}
}

D 12
static
E 12
I 12
static void
E 12
Gcat(s1, s2)
D 14
	register char *s1, *s2;
E 14
I 14
	char *s1, *s2;
E 14
{
D 14
	register int len = strlen(s1) + strlen(s2) + 1;
E 14
I 14
	int len = strlen(s1) + strlen(s2) + 1;
E 14

	if (len >= gnleft || gargc >= GAVSIZ - 1)
		globerr = "Arguments too long";
	else {
		gargc++;
		gnleft -= len;
		gargv[gargc] = 0;
		gargv[gargc - 1] = strspl(s1, s2);
	}
}

D 12
static
E 12
I 12
static void
E 12
addpath(c)
D 14
	char c;
E 14
I 14
	int c;
E 14
{

	if (gpathp >= lastgpathp)
		globerr = "Pathname too long";
	else {
		*gpathp++ = c;
		*gpathp = 0;
	}
}

D 12
static
E 12
I 12
static void
E 12
rscan(t, f)
D 14
	register char **t;
	int (*f)();
E 14
I 14
	char **t;
	int (*f) __P((int));
E 14
{
D 14
	register char *p, c;
E 14
I 14
	char *p, c;
E 14

	while (p = *t++) {
		if (f == tglob)
			if (*p == '~')
				gflag |= 2;
			else if (eq(p, "{") || eq(p, "{}"))
				continue;
		while (c = *p++)
			(*f)(c);
	}
}
I 14

E 14
D 5

E 5
I 5
/*
E 5
D 14
static
E 14
I 14
static int
E 14
scan(t, f)
D 14
	register char **t;
E 14
I 14
	char **t;
E 14
	int (*f)();
{
D 14
	register char *p, c;
E 14
I 14
	char *p, c;
E 14

	while (p = *t++)
		while (c = *p)
			*p++ = (*f)(c);
D 5
}
E 5
I 5
} */
E 5

D 14
static
E 14
I 14
static int
E 14
tglob(c)
D 14
	register char c;
E 14
I 14
	int c;
E 14
{

	if (any(c, globchars))
		gflag |= c == '{' ? 2 : 1;
	return (c);
}
I 14

E 14
D 5

E 5
I 5
/*
E 5
D 14
static
E 14
I 14
static int
E 14
trim(c)
	char c;
{

	return (c & TRIM);
D 5
}
E 5
I 5
D 14
} */
E 14
I 14
}
*/
E 14
E 5

D 14

E 14
I 14
static int
E 14
letter(c)
D 14
	register char c;
E 14
I 14
	int c;
E 14
{

	return (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_');
}

I 14
static int
E 14
digit(c)
D 14
	register char c;
E 14
I 14
	int c;
E 14
{

	return (c >= '0' && c <= '9');
}

I 14
static int
E 14
any(c, s)
D 14
	register int c;
	register char *s;
E 14
I 14
	int c;
	char *s;
E 14
{

	while (*s)
		if (*s++ == c)
D 14
			return(1);
	return(0);
E 14
I 14
			return (1);
	return (0);
E 14
}
I 14

static int
E 14
blklen(av)
D 14
	register char **av;
E 14
I 14
	char **av;
E 14
{
D 14
	register int i = 0;
E 14
I 14
	int i = 0;
E 14

	while (*av++)
		i++;
	return (i);
}

char **
blkcpy(oav, bv)
	char **oav;
D 14
	register char **bv;
E 14
I 14
	char **bv;
E 14
{
D 14
	register char **av = oav;
E 14
I 14
	char **av = oav;
E 14

	while (*av++ = *bv++)
		continue;
	return (oav);
}

I 14
void
E 14
blkfree(av0)
	char **av0;
{
D 14
	register char **av = av0;
E 14
I 14
	char **av = av0;
E 14

	while (*av)
		free(*av++);
D 10
	free((char *)av0);
E 10
}

D 14
static
char *
E 14
I 14
static char *
E 14
strspl(cp, dp)
D 14
	register char *cp, *dp;
E 14
I 14
	char *cp, *dp;
E 14
{
D 14
	register char *ep = malloc((unsigned)(strlen(cp) + strlen(dp) + 1));
E 14
I 14
	char *ep = malloc((unsigned)(strlen(cp) + strlen(dp) + 1));
E 14

	if (ep == (char *)0)
		fatal("Out of memory");
D 5
	strcpy(ep, cp);
	strcat(ep, dp);
E 5
I 5
	(void) strcpy(ep, cp);
	(void) strcat(ep, dp);
E 5
	return (ep);
}

D 3
static
E 3
D 14
char **
E 14
I 14
static char **
E 14
copyblk(v)
D 14
	register char **v;
E 14
I 14
	char **v;
E 14
{
D 14
	register char **nv = (char **)malloc((unsigned)((blklen(v) + 1) *
E 14
I 14
	char **nv = (char **)malloc((unsigned)((blklen(v) + 1) *
E 14
						sizeof(char **)));
	if (nv == (char **)0)
		fatal("Out of memory");

	return (blkcpy(nv, v));
}

D 14
static
char *
E 14
I 14
static char *
E 14
strend(cp)
D 14
	register char *cp;
E 14
I 14
	char *cp;
E 14
{

	while (*cp)
		cp++;
	return (cp);
}
/*
 * Extract a home directory from the password file
 * The argument points to a buffer where the name of the
 * user whose home directory is sought is currently.
 * We write the home directory of the user back there.
 */
I 14
static int
E 14
gethdir(home)
	char *home;
{
D 14
	register struct passwd *pp = getpwnam(home);
E 14
I 14
	struct passwd *pp = getpwnam(home);
E 14

D 9
	if (pp == 0)
E 9
I 9
	if (!pp || home + strlen(pp->pw_dir) >= lastgpathp)
E 9
		return (1);
D 5
	strcpy(home, pp->pw_dir);
E 5
I 5
	(void) strcpy(home, pp->pw_dir);
E 5
	return (0);
}
E 1
