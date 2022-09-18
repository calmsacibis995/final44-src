h13761
s 00002/00002/00911
d D 8.1 93/05/31 16:42:17 bostic 51 50
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00010/00903
d D 5.40 93/05/22 19:06:34 christos 50 49
c Fixed gcc -Wall warnings
e
s 00001/00001/00912
d D 5.39 93/02/11 17:13:47 christos 49 48
c fixed sortscmp typo a -> !a
e
s 00001/00003/00912
d D 5.38 92/06/16 12:36:10 christos 48 47
c Fixed bug with {} when block needed to be re-alloc'ed
e
s 00000/00011/00915
d D 5.37 92/06/05 21:18:26 christos 47 46
c Latest fix broke backquotes with redirection; back it off.
e
s 00011/00000/00915
d D 5.36 92/05/15 00:14:21 christos 46 45
c Add extra file descriptor dups to make sure 0,1,2 exist
e
s 00002/00001/00913
d D 5.35 92/02/05 16:43:12 christos 45 44
c pmatch declaration fix.
e
s 00137/00059/00777
d D 5.34 92/02/05 16:32:23 christos 44 43
c {}{a,b} did not expand correctly; Gmatch() accepts braces now.
e
s 00008/00009/00828
d D 5.33 91/11/12 20:22:06 bostic 43 42
c fix sortscmp to compile under pcc
e
s 00004/00004/00833
d D 5.32 91/11/06 16:09:44 christos 42 41
c Added support for displaying non-printable characters
e
s 00009/00000/00828
d D 5.31 91/11/04 18:49:32 christos 41 40
c reset the alias and eval pointers before calling lex
e
s 00012/00007/00816
d D 5.30 91/10/28 21:28:00 leres 40 39
c Fix gcc "bodyless for/while" warnings.
e
s 00002/00001/00821
d D 5.29 91/10/10 14:59:27 christos 39 38
c Add : as a delimiter in ~ expansions
e
s 00002/00000/00820
d D 5.28 91/08/07 17:52:10 christos 38 37
c Added trim() in globall
e
s 00002/00002/00818
d D 5.27 91/08/02 03:41:21 christos 37 36
c Don't double-free the result of libglob
e
s 00003/00000/00817
d D 5.26 91/08/01 12:42:17 christos 36 35
c Avoid globbing NULL patterns in libglob. (`` returned nothing.)
e
s 00001/00001/00816
d D 5.25 91/07/28 14:12:31 christos 35 34
c Fixed echo ~ {} bug.
e
s 00011/00009/00806
d D 5.24 91/07/26 14:12:42 christos 34 33
c Bugfix for echo * `echo`, fglag would get overwritten
e
s 00014/00010/00801
d D 5.23 91/07/19 17:31:00 christos 33 32
c stdio based version; brace glob fix; builtin prototypes
e
s 00002/00002/00809
d D 5.22 91/07/01 21:15:37 christos 32 31
c Fixed core dump 'echo {foo bar.[ch]}'
e
s 00003/00003/00808
d D 5.21 91/06/24 21:54:50 christos 31 30
c Gmatch did not trim the characters inside a range.
e
s 00010/00002/00801
d D 5.20 91/06/16 15:12:39 christos 30 29
c Fixed bug with `` returning no string.
e
s 00006/00000/00797
d D 5.19 91/06/08 17:08:48 christos 29 28
c More prototype fixes, Removed TERMIOS define
e
s 00006/00001/00791
d D 5.18 91/06/08 12:20:23 bostic 28 27
c include file pass, csh.h no longer include every .h in the system
c rename sigmast_t to sigset_t to match signal.h; minor pointer cleanups
e
s 00020/00020/00772
d D 5.17 91/06/07 20:57:26 christos 27 26
c static function prototypes
e
s 00003/00002/00789
d D 5.16 91/06/07 11:13:28 bostic 26 25
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00635/00535/00156
d D 5.15 91/06/04 13:31:33 bostic 25 24
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00017/00015/00674
d D 5.14 91/04/22 15:29:14 bostic 24 23
c now ~ accumulates all characters until / or EOS, not just alpha-num
c expand tildes and braces separately (bug fix)
e
s 00007/00006/00682
d D 5.13 91/04/04 18:17:43 bostic 23 22
c new copyright; att/bsd/shared
e
s 00002/00002/00686
d D 5.12 91/04/01 17:37:13 bostic 22 21
c setexit -> setjmp, reset -> longjmp, isdir() -> S_ISDIR, ANSI
c Prof. Graham requested semantic changes to #defines in sh.h, removing the
c last vestiges of the PWB/V6 shell
e
s 00009/00024/00679
d D 5.11 91/03/20 18:48:26 bostic 21 20
c add gl_matchc, GLOG_MAGCHAR to glob(3)
e
s 00005/00003/00698
d D 5.10 91/03/18 14:29:07 bostic 20 19
c fix check for no match was wrong.
e
s 00001/00001/00700
d D 5.9 91/03/18 12:03:07 bostic 19 18
c setenv foo `bar -f`, where bar DNE caused csh to dump core
e
s 00002/00000/00699
d D 5.8 91/03/14 16:24:12 bostic 18 17
c forgot to free at one point
e
s 00042/00030/00657
d D 5.7 91/03/14 14:09:17 bostic 17 16
c from Christos Zoulas; fix "echo /bin/*"
e
s 00442/00504/00245
d D 5.6 91/03/14 12:30:08 bostic 16 15
c use the library globbing routines instead of rolling our own
e
s 00000/00001/00749
d D 5.5 87/12/22 02:59:00 bostic 15 14
c {,} construct should allow '\' to escape comma; bug report 4.3BSD/bin/112
e
s 00006/00004/00744
d D 5.4 86/05/13 01:27:04 lepreau 14 13
c make qsort compare routine extern so sh.file.c can use it
e
s 00011/00015/00737
d D 5.3 86/03/29 07:27:22 lepreau 13 12
c replace internal N**2 linear exchange sort with qsort; minor cmap changes
c associated with sh.h change
e
s 00003/00003/00749
d D 5.2 85/06/06 13:10:38 edward 12 11
c cleaning up after bozos
e
s 00008/00002/00744
d D 5.1 85/06/04 10:59:38 dist 11 10
c Add copyright
e
s 00001/00001/00745
d D 4.9 85/02/28 11:12:02 ralph 10 9
c fix quoted chars in path (e.g., 'foo'/*.c clear quote bits on foo)
e
s 00002/00002/00744
d D 4.8 85/01/17 09:21:14 bloom 9 8
c bus error trying to modify shared null string in trim()
e
s 00056/00061/00690
d D 4.7 84/12/13 14:41:23 edward 8 7
c performance
e
s 00004/00004/00747
d D 4.6 84/08/31 09:31:47 ralph 7 6
c use new signal calls instead of compatibility routines.
e
s 00007/00003/00744
d D 4.5 83/07/03 20:15:02 sam 6 4
c fix for noglob from wnj
e
s 00007/00003/00744
d R 4.5 83/07/01 03:53:01 sam 5 4
c fixes from wnj; 
e
s 00001/00001/00746
d D 4.4 82/05/07 18:21:28 mckusick 4 3
c update to new fs
e
s 00021/00033/00726
d D 4.3 82/02/12 15:29:59 mckusic 3 2
c convret to new directory format
e
s 00003/00002/00756
d D 4.2 81/03/11 18:51:52 wnj 2 1
c minor bug fixes
e
s 00758/00000/00000
d D 4.1 80/10/09 12:41:03 bill 1 0
c date and time created 80/10/09 12:41:03 by bill
e
u
U
t
T
I 11
D 23
/*
 * Copyright (c) 1980 Regents of the University of California.
D 12
 * All rights reserved.  The Berkeley software License Agreement
E 12
I 12
 * All rights reserved.  The Berkeley Software License Agreement
E 12
 * specifies the terms and conditions for redistribution.
E 23
I 23
/*-
D 51
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 51
I 51
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 51
 *
 * %sccs.include.redist.c%
E 23
 */

E 11
I 1
D 8
static	char *sccsid = "%Z%%M% %I% %G%";
E 8
I 8
#ifndef lint
D 11
static	char *sccsid = "%W% (Berkeley) %G%";
#endif
E 11
I 11
D 12
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 12
I 12
D 23
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 23
I 23
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 23
E 12
E 11
E 8
I 3

I 28
#include <sys/param.h>
#include <glob.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
I 29
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif

E 29
E 28
E 3
D 26
#include "sh.h"
E 26
I 26
#include "csh.h"
#include "extern.h"
E 26
I 8
D 13
#include "sh.char.h"
E 13
E 8
I 3
D 4
#include <ndir.h>
E 4
I 4
D 6
#include <dir.h>
E 6
I 6
D 16
#include <sys/dir.h>
E 16
I 16
D 25
#include "glob.h"
E 25
I 25
D 28
#include <glob.h>
E 28
E 25
E 16
E 6
E 4
E 3

I 16
D 17
static int noglob;
E 17
I 17
D 33
static int noglob, nonomatch;
E 33
I 33
static int noglob;
E 33
E 17
D 25

E 25
static int pargsiz, gargsiz;
I 25

E 25
E 16
/*
D 16
 * C Shell
E 16
I 16
 * Values for gflag
E 16
 */
I 16
D 25
#define G_NONE	0	/* No globbing needed			*/
#define G_GLOB	1	/* string contains *?[] characters	*/
#define G_CSH	2	/* string contains ~`{ characters	*/
E 25
I 25
#define	G_NONE	0		/* No globbing needed			*/
#define	G_GLOB	1		/* string contains *?[] characters	*/
#define	G_CSH	2		/* string contains ~`{ characters	*/
E 25
E 16

I 25
#define	GLOBSPACE	100	/* Alloc increment			*/

E 25
D 16
int	globcnt;
E 16
I 16
#define LBRC '{'
#define RBRC '}'
#define LBRK '['
#define RBRK ']'
E 16
D 25

E 25
D 8
char	*globchars =	"`{[*?";

E 8
D 16
char	*gpath, *gpathp, *lastgpathp;
int	globbed;
bool	noglob;
bool	nonomatch;
char	*entp;
char	**sortbas;
I 13
D 14
int	argcmp();
E 14
I 14
int	sortscmp();
E 16
I 16
#define EOS '\0'
D 25
char **gargv = (char **) 0;
short gargc = 0;
E 25
E 16
E 14
E 13

I 25
D 27
Char  **gargv = (Char **) 0;
E 27
I 27
Char  **gargv = NULL;
E 27
long    gargc = 0;
D 27
Char  **pargv = (Char **) 0;
E 27
I 27
Char  **pargv = NULL;
E 27
long    pargc = 0;

E 25
I 13
D 16
#define sort()	qsort((char *)sortbas, &gargv[gargc] - sortbas, \
D 14
		      sizeof(*sortbas), argcmp), sortbas = &gargv[gargc]
E 14
I 14
		      sizeof(*sortbas), sortscmp), sortbas = &gargv[gargc]
E 14


E 13
char **
glob(v)
	register char **v;
{
	char agpath[BUFSIZ];
	char *agargv[GAVSIZ];

	gpath = agpath; gpathp = gpath; *gpathp = 0;
	lastgpathp = &gpath[sizeof agpath - 2];
	ginit(agargv); globcnt = 0;
#ifdef GDEBUG
	printf("glob entered: "); blkpr(v); printf("\n");
#endif
	noglob = adrof("noglob") != 0;
	nonomatch = adrof("nonomatch") != 0;
	globcnt = noglob | nonomatch;
	while (*v)
		collect(*v++);
#ifdef GDEBUG
	printf("glob done, globcnt=%d, gflag=%d: ", globcnt, gflag); blkpr(gargv); printf("\n");
#endif
	if (globcnt == 0 && (gflag&1)) {
		blkfree(gargv), gargv = 0;
		return (0);
	} else
		return (gargv = copyblk(gargv));
}

ginit(agargv)
	char **agargv;
{

	agargv[0] = 0; gargv = agargv; sortbas = agargv; gargc = 0;
	gnleft = NCARGS - 4;
}

collect(as)
	register char *as;
{
	register int i;

	if (any('`', as)) {
#ifdef GDEBUG
		printf("doing backp of %s\n", as);
#endif
D 8
		dobackp(as, 0);
E 8
I 8
		(void) dobackp(as, 0);
E 8
#ifdef GDEBUG
		printf("backp done, acollect'ing\n");
#endif
		for (i = 0; i < pargc; i++)
D 6
			if (noglob)
E 6
I 6
			if (noglob) {
E 6
				Gcat(pargv[i], "");
D 6
			else
E 6
I 6
				sortbas = &gargv[gargc];
			} else
E 6
				acollect(pargv[i]);
		if (pargv)
			blkfree(pargv), pargv = 0;
#ifdef GDEBUG
		printf("acollect done\n");
#endif
D 2
	} else if (noglob)
E 2
I 2
	} else if (noglob || eq(as, "{") || eq(as, "{}")) {
E 2
		Gcat(as, "");
D 2
	else
E 2
I 2
		sort();
	} else
E 2
		acollect(as);
}

acollect(as)
	register char *as;
{
	register int ogargc = gargc;

	gpathp = gpath; *gpathp = 0; globbed = 0;
	expand(as);
	if (gargc == ogargc) {
		if (nonomatch) {
			Gcat(as, "");
			sort();
		}
	} else
		sort();
}

E 16
D 13
sort()
E 13
I 13
D 14
static
argcmp(a1, a2)
E 14
I 14
/*
D 16
 * String compare for qsort.  Also used by filec code in sh.file.c.
E 16
I 16
 * globbing is now done in two stages. In the first pass we expand
D 25
 * csh globbing idioms ~`{ and then we proceed doing the normal 
E 25
I 25
 * csh globbing idioms ~`{ and then we proceed doing the normal
E 25
 * globbing if needed ?*[
 *
 * Csh type globbing is handled in globexpand() and the rest is
D 24
 * handled in glob() which is part of the 4.4BSD libc. To do the
 * 'No match' checking, we try to glob everything without checking
 * and then we look if the string still contains globbing characters.
 * If it does, then globbing failed for at least one component of the
 * block.
E 24
I 24
 * handled in glob() which is part of the 4.4BSD libc.
E 24
D 25
 * 
E 25
I 25
 *
E 25
E 16
 */
I 25
D 27
static Char *globtilde();
static Char **libglob();
static Char **globexpand();
static int globbrace();
static void pword();
static void psave();
static void backeval();
E 27
I 27
static Char	*globtilde __P((Char **, Char *));
static Char	**libglob __P((Char **));
static Char	**globexpand __P((Char **));
static int	globbrace __P((Char *, Char *, Char ***));
I 44
static void	expbrace __P((Char ***, Char ***, int));
I 45
static int	pmatch __P((Char *, Char *));
E 45
E 44
static void	pword __P((void));
static void	psave __P((int));
static void	backeval __P((Char *, bool));
E 27
E 25
D 16
sortscmp(a1, a2)
E 14
	char **a1, **a2;
E 13
{
E 16
D 13
	register char **p1, **p2, *c;
	char **Gvp = &gargv[gargc];
E 13

D 13
	p1 = sortbas;
	while (p1 < Gvp-1) {
		p2 = p1;
		while (++p2 < Gvp)
			if (strcmp(*p1, *p2) > 0)
				c = *p1, *p1 = *p2, *p2 = c;
		p1++;
	}
	sortbas = Gvp;
E 13
I 13
D 16
	 return (strcmp(*a1, *a2));
E 13
}
E 16

D 16
expand(as)
	char *as;
E 16
I 16
D 25
static char *
E 25
I 25
static Char *
E 25
D 24
globtilde(s)
char *s;
E 24
I 24
globtilde(nv, s)
D 25
char **nv, *s;
E 25
I 25
    Char  **nv, *s;
E 25
E 24
E 16
{
D 16
	register char *cs;
	register char *sgpathp, *oldcs;
	struct stat stb;
E 16
I 16
D 25
	char gbuf[MAXPATHLEN], *gstart, *b, *u;
E 25
I 25
    Char    gbuf[MAXPATHLEN], *gstart, *b, *u, *e;
E 25
E 16

D 16
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
					error("Unknown user: %s", gpath + 1);
D 8
				strcpy(gpath, gpath + 1);
E 8
I 8
				(void) strcpy(gpath, gpath + 1);
E 8
			} else
D 8
				strcpy(gpath, value("home"));
E 8
I 8
				(void) strcpy(gpath, value("home"));
E 8
			gpathp = strend(gpath);
		}
E 16
I 16
D 25
	gstart = gbuf;
	*gstart++ = *s++;
D 24
	for (u = s, b = gstart; alnum(*s) || *s == '-'; *b++ = *s++)
E 24
I 24
	for (u = s, b = gstart; *s != '\0' && *s != '/'; *b++ = *s++)
E 24
		 continue;
	*b = EOS;
	if (*s == EOS || *s == '/') {
		if (s == u) 
			gstart = strcpy(gbuf, value("home"));
D 24
		else if (gethdir(gstart)) 
E 24
I 24
		else if (gethdir(gstart)) {
			blkfree(nv);
E 24
			error("Unknown user: %s", gstart);
I 24
		}
E 24
		b = &gstart[strlen(gstart)];
E 16
	}
D 8
	while (!any(*cs, globchars)) {
E 8
I 8
D 13
	while (!cmap(*cs, _GLOB)) {
E 13
I 13
D 16
	while (!isglob(*cs)) {
E 13
E 8
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
D 8
		execbrc(cs, NOSTR);
E 8
I 8
		(void) execbrc(cs, NOSTR);
E 8
		return;
	}
	matchdir(cs);
endit:
	gpathp = sgpathp;
	*gpathp = 0;
E 16
I 16
	while (*s) *b++ = *s++;
	*b = EOS;
	return(savestr(gstart));
E 25
I 25
    gstart = gbuf;
    *gstart++ = *s++;
    u = s;
D 39
    for (b = gstart, e = &gbuf[MAXPATHLEN - 1]; *s && *s != '/' && b < e;
E 39
I 39
D 40
    for (b = gstart, e = &gbuf[MAXPATHLEN - 1]; 
E 40
I 40
    for (b = gstart, e = &gbuf[MAXPATHLEN - 1];
E 40
	 *s && *s != '/' && *s != ':' && b < e;
E 39
D 40
	 *b++ = *s++);
E 40
I 40
	 *b++ = *s++)
	 continue;
E 40
    *b = EOS;
    if (gethdir(gstart)) {
	blkfree(nv);
	if (*gstart)
D 42
	    stderror(ERR_UNKUSER, short2str(gstart));
E 42
I 42
	    stderror(ERR_UNKUSER, vis_str(gstart));
E 42
	else
	    stderror(ERR_NOHOME);
    }
    b = &gstart[Strlen(gstart)];
    while (*s)
	*b++ = *s++;
    *b = EOS;
    --u;
    xfree((ptr_t) u);
    return (Strsave(gstart));
E 25
E 16
}

D 16
matchdir(pattern)
	char *pattern;
E 16
I 16
static int
globbrace(s, p, bl)
D 25
char *s, *p, ***bl;
E 25
I 25
    Char   *s, *p, ***bl;
E 25
E 16
{
D 16
	struct stat stb;
D 3
	struct direct dirbuf[BUFSIZ / sizeof (struct direct)];
	char d_name[DIRSIZ+1];
	register int dirf, cnt;
E 3
I 3
	register struct direct *dp;
D 8
	DIR *dirp;
	register int cnt;
E 8
I 8
	register DIR *dirp;
E 16
I 16
D 25
	int i, len;
	char *pm, *pe, *lm, *pl;
	char **nv, **vl;
	char gbuf[MAXPATHLEN];
	int size = GAVSIZ;
E 25
I 25
    int     i, len;
    Char   *pm, *pe, *lm, *pl;
    Char  **nv, **vl;
    Char    gbuf[MAXPATHLEN];
    int     size = GLOBSPACE;
E 25
E 16
E 8
E 3

D 3
	dirf = open(gpath, 0);
	if (dirf < 0) {
E 3
I 3
D 16
	dirp = opendir(gpath);
	if (dirp == NULL) {
E 3
		if (globbed)
			return;
D 3
		goto patherr;
E 3
I 3
		goto patherr2;
E 3
	}
D 3
	if (fstat(dirf, &stb) < 0)
		goto patherr;
E 3
I 3
	if (fstat(dirp->dd_fd, &stb) < 0)
		goto patherr1;
E 3
	if (!isdir(stb)) {
		errno = ENOTDIR;
D 3
		goto patherr;
E 3
I 3
		goto patherr1;
E 3
	}
D 3
	while ((cnt = read(dirf, (char *) dirbuf, sizeof dirbuf)) >= sizeof dirbuf[0]) {
		register struct direct *ep = dirbuf;

		for (cnt /= sizeof (struct direct); cnt > 0; cnt--, ep++) {
			if (ep->d_ino == 0)
				continue;
			copdent(d_name, ep->d_name);
			if (match(d_name, pattern)) {
				Gcat(gpath, d_name);
				globcnt++;
			}
E 3
I 3
	while ((dp = readdir(dirp)) != NULL) {
		if (dp->d_ino == 0)
			continue;
		if (match(dp->d_name, pattern)) {
			Gcat(gpath, dp->d_name);
			globcnt++;
E 3
		}
	}
D 3
	close(dirf);
E 3
I 3
	closedir(dirp);
E 3
	return;
E 16
I 16
D 25
	nv = vl = (char **) xalloc(sizeof(char *) * size);
E 25
I 25
    nv = vl = (Char **) xmalloc((size_t) sizeof(Char *) * size);
D 27
    *vl = (Char *) 0;
E 27
I 27
    *vl = NULL;
E 27
E 25
E 16

D 3
patherr:
E 3
I 3
D 16
patherr1:
	closedir(dirp);
patherr2:
E 3
	Perror(gpath);
D 3
}

copdent(to, from)
	register char *to, *from;
{
	register int cnt = DIRSIZ;

	do
		*to++ = *from++;
	while (--cnt);
	*to = 0;
E 3
}

execbrc(p, s)
	char *p, *s;
{
	char restbuf[BUFSIZ + 2];
	register char *pe, *pm, *pl;
	int brclev = 0;
	char *lm, savec, *sgpathp;

	for (lm = restbuf; *p != '{'; *lm++ = *p++)
E 16
I 16
D 25
	len = 0;
	/* copy part up to the brace */
	for (lm = gbuf, p = s; *p != LBRC; *lm++ = *p++)
E 16
		continue;
E 25
I 25
    len = 0;
    /* copy part up to the brace */
    for (lm = gbuf, p = s; *p != LBRC; *lm++ = *p++)
	continue;
E 25
D 16
	for (pe = ++p; *pe; pe++)
	switch (*pe) {
E 16

D 16
	case '{':
		brclev++;
		continue;
E 16
I 16
D 25
	/* check for balanced braces */
	for (i = 0, pe = ++p; *pe; pe++) 
		if (*pe == LBRK) {
			/* Ignore everything between [] */
			for (++pe; *pe != RBRK && *pe != EOS; pe++)
				continue;
			if (*pe == EOS) {
				blkfree(nv);
				return(- LBRK);
			}
		}
		else if (*pe == LBRC)
			i++;
		else if (*pe == RBRC) {
			if (i == 0)
				break;
			i--;
		}
E 16

D 16
	case '}':
		if (brclev == 0)
			goto pend;
		brclev--;
		continue;

	case '[':
		for (pe++; *pe && *pe != ']'; pe++)
			continue;
		if (!*pe)
			error("Missing ]");
		continue;
E 16
I 16
	if (i != 0) {
E 25
I 25
    /* check for balanced braces */
    for (i = 0, pe = ++p; *pe; pe++)
	if (*pe == LBRK) {
	    /* Ignore everything between [] */
	    for (++pe; *pe != RBRK && *pe != EOS; pe++)
		continue;
	    if (*pe == EOS) {
E 25
		blkfree(nv);
D 25
		return(- LBRC);
E 25
I 25
D 44
		return (-LBRK);
E 44
I 44
		return (-RBRK);
E 44
	    }
E 25
E 16
	}
I 25
	else if (*pe == LBRC)
	    i++;
	else if (*pe == RBRC) {
	    if (i == 0)
		break;
	    i--;
	}
E 25
D 16
pend:
	if (brclev || !*pe)
		error("Missing }");
	for (pl = pm = p; pm <= pe; pm++)
	switch (*pm & (QUOTE|TRIM)) {
E 16

D 16
	case '{':
		brclev++;
		continue;

	case '}':
		if (brclev) {
			brclev--;
E 16
I 16
D 25
	for (i = 0, pl = pm = p; pm <= pe; pm++)
E 25
I 25
D 32
    if (i != 0) {
E 32
I 32
    if (i != 0 || *pe == '\0') {
E 32
	blkfree(nv);
D 32
	return (-LBRC);
E 32
I 32
	return (-RBRC);
E 32
    }

    for (i = 0, pl = pm = p; pm <= pe; pm++)
E 25
	switch (*pm) {
	case LBRK:
D 25
		for (++pm; *pm != RBRK && *pm != EOS; pm++)
E 16
			continue;
I 16
		if (*pm == EOS) {
			blkfree(nv);
			return(- RBRK);
E 16
		}
D 16
		goto doit;

E 16
I 16
		break;
E 25
I 25
	    for (++pm; *pm != RBRK && *pm != EOS; pm++)
		continue;
	    if (*pm == EOS) {
D 27
		*vl = (Char *) 0;
E 27
I 27
		*vl = NULL;
E 27
		blkfree(nv);
		return (-RBRK);
	    }
	    break;
E 25
	case LBRC:
D 25
		i++;
		break;
E 25
I 25
	    i++;
	    break;
E 25
	case RBRC:
D 25
		if (i) {
			i--;
			break;
		}
		/*FALLTHROUGH*/
E 25
I 25
	    if (i) {
		i--;
		break;
	    }
	    /* FALLTHROUGH */
E 25
E 16
D 15
	case ','|QUOTE:
E 15
	case ',':
D 16
		if (brclev)
			continue;
doit:
		savec = *pm;
		*pm = 0;
D 8
		strcpy(lm, pl);
		strcat(restbuf, pe + 1);
E 8
I 8
		(void) strcpy(lm, pl);
		(void) strcat(restbuf, pe + 1);
E 8
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
		continue;

	case '[':
		for (pm++; *pm && *pm != ']'; pm++)
			continue;
		if (!*pm)
			error("Missing ]");
		continue;
E 16
I 16
D 25
		if (i && *pm == ',')
			break;
		else {
			char savec = *pm;
			*pm = EOS;
			(void) strcpy(lm, pl);
			(void) strcat(gbuf, pe + 1);
			*pm = savec;
			*vl++ = savestr(gbuf);
			len++;
			pl = pm + 1;
			if (vl == &nv[size]) {
				size += GAVSIZ;
				nv = (char **) xrealloc(nv, 
							size * sizeof(char *));
				vl = &nv[size - GAVSIZ];
			}
		}
E 25
I 25
	    if (i && *pm == ',')
E 25
		break;
I 25
	    else {
		Char    savec = *pm;

		*pm = EOS;
		(void) Strcpy(lm, pl);
		(void) Strcat(gbuf, pe + 1);
		*pm = savec;
		*vl++ = Strsave(gbuf);
		len++;
		pl = pm + 1;
		if (vl == &nv[size]) {
		    size += GLOBSPACE;
		    nv = (Char **) xrealloc((ptr_t) nv, (size_t)
					    size * sizeof(Char *));
		    vl = &nv[size - GLOBSPACE];
		}
	    }
	    break;
I 44
	default:
	    break;
E 44
E 25
E 16
	}
D 16
	return (0);
E 16
I 16
D 25
	*vl = (char *) 0;
	*bl = nv;
	return(len);
E 25
I 25
D 27
    *vl = (Char *) 0;
E 27
I 27
    *vl = NULL;
E 27
    *bl = nv;
    return (len);
E 25
E 16
}

I 44

static void
expbrace(nvp, elp, size)
    Char ***nvp, ***elp;
    int size;
{
    Char **vl, **el, **nv, *s;

    vl = nv = *nvp;
    if (elp != NULL)
	el = *elp;
    else
	for (el = vl; *el; el++)
	    continue;

    for (s = *vl; s; s = *++vl) {
	Char   *b;
	Char  **vp, **bp;

	/* leave {} untouched for find */
	if (s[0] == '{' && (s[1] == '\0' || (s[1] == '}' && s[2] == '\0')))
	    continue;
D 50
	if (b = Strchr(s, '{')) {
E 50
I 50
	if ((b = Strchr(s, '{')) != NULL) {
E 50
	    Char  **bl;
	    int     len;

	    if ((len = globbrace(s, b, &bl)) < 0) {
		xfree((ptr_t) nv);
		stderror(ERR_MISSING, -len);
	    }
	    xfree((ptr_t) s);
	    if (len == 1) {
		*vl-- = *bl;
		xfree((ptr_t) bl);
		continue;
	    }
	    len = blklen(bl);
	    if (&el[len] >= &nv[size]) {
		int     l, e;

		l = &el[len] - &nv[size];
		size += GLOBSPACE > l ? GLOBSPACE : l;
		l = vl - nv;
		e = el - nv;
		nv = (Char **) xrealloc((ptr_t) nv, (size_t)
					size * sizeof(Char *));
		vl = nv + l;
		el = nv + e;
	    }
	    vp = vl--;
	    *vp = *bl;
	    len--;
	    for (bp = el; bp != vp; bp--)
		bp[len] = *bp;
	    el += len;
	    vp++;
	    for (bp = bl + 1; *bp; *vp++ = *bp++)
		continue;
	    xfree((ptr_t) bl);
	}

    }
    if (elp != NULL)
	*elp = el;
    *nvp = nv;
}

E 44
D 16
match(s, p)
	char *s, *p;
E 16
I 16
D 25
static char **
E 25
I 25
static Char **
E 25
globexpand(v)
D 25
	char **v;
E 25
I 25
    Char  **v;
E 25
E 16
{
D 16
	register int c;
	register char *sentp;
	char sglobbed = globbed;
E 16
I 16
D 25
	char *s;
	char **nv, **vl, **el;
	int size = GAVSIZ;
E 25
I 25
    Char   *s;
    Char  **nv, **vl, **el;
    int     size = GLOBSPACE;
E 25
E 16

D 16
	if (*s == '.' && *p != '.')
		return (0);
	sentp = entp;
	entp = s;
	c = amatch(s, p);
	entp = sentp;
	globbed = sglobbed;
	return (c);
}
E 16

D 16
amatch(s, p)
	register char *s, *p;
{
	register int scc;
	int ok, lc;
	char *sgpathp;
	struct stat stb;
	int c, cc;
E 16
I 16
D 25
	nv = vl = (char **) xalloc(sizeof(char *) * size);
	*vl = (char *) 0;
E 25
I 25
    nv = vl = (Char **) xmalloc((size_t) sizeof(Char *) * size);
D 27
    *vl = (Char *) 0;
E 27
I 27
    *vl = NULL;
E 27
E 25
E 16

D 16
	globbed = 1;
	for (;;) {
		scc = *s++ & TRIM;
		switch (c = *p++) {
E 16
I 16
D 25
	/*
	 * Step 1: expand backquotes.
	 */
	while (s = *v++) {
		if (index(s, '`')) {
			int i;
E 25
I 25
    /*
     * Step 1: expand backquotes.
     */
D 50
    while (s = *v++) {
E 50
I 50
    while ((s = *v++) != NULL) {
E 50
	if (Strchr(s, '`')) {
	    int     i;
E 25
E 16

D 16
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
E 16
I 16
D 25
			dobackp(s, 0);
			for (i = 0; i < pargc; i++) {
				*vl++ = pargv[i];
				if (vl == &nv[size]) {
					size += GAVSIZ;
					nv = (char **) xrealloc(nv, 
							size * sizeof(char *));
					vl = &nv[size - GAVSIZ];
E 16
				}
D 16
				if (cc == '-') {
					if (lc <= scc && scc <= *p++)
						ok++;
				} else
					if (scc == (lc = cc))
						ok++;
E 16
			}
D 16
			if (cc == 0)
				error("Missing ]");
			continue;
E 16
I 16
			xfree((char *) pargv);
			pargv = (char **) 0;
E 25
I 25
	    (void) dobackp(s, 0);
	    for (i = 0; i < pargc; i++) {
		*vl++ = pargv[i];
		if (vl == &nv[size]) {
		    size += GLOBSPACE;
		    nv = (Char **) xrealloc((ptr_t) nv,
					    (size_t) size * sizeof(Char *));
		    vl = &nv[size - GLOBSPACE];
E 25
		}
D 25
		else {
			*vl++ = savestr(s);
			if (vl == &nv[size]) {
				size += GAVSIZ;
				nv = (char **) xrealloc(nv, 
							size * sizeof(char *));
				vl = &nv[size - GAVSIZ];
			}
		}
E 25
I 25
	    }
	    xfree((ptr_t) pargv);
D 27
	    pargv = (Char **) 0;
E 27
I 27
	    pargv = NULL;
E 27
E 25
	}
D 25
	*vl = (char *) 0;
E 25
I 25
	else {
	    *vl++ = Strsave(s);
	    if (vl == &nv[size]) {
		size += GLOBSPACE;
		nv = (Char **) xrealloc((ptr_t) nv, (size_t)
					size * sizeof(Char *));
		vl = &nv[size - GLOBSPACE];
	    }
	}
    }
D 27
    *vl = (Char *) 0;
E 27
I 27
    *vl = NULL;
E 27
E 25
E 16

D 16
		case '*':
			if (!*p)
				return (1);
			if (*p == '/') {
				p++;
				goto slash;
E 16
I 16
D 25
	if (noglob) 
		return(nv);
E 25
I 25
    if (noglob)
	return (nv);
E 25

D 25
	/*
D 24
	 * Step 2: expand tilde and braces
E 24
I 24
	 * Step 2: expand braces
E 24
	 */
	el = vl;
	vl = nv;
	for (s = *vl; s; s = *++vl) {
		char *b;
		char **vp, **bp;
D 24
		if (*s == '~') {
			*vl = globtilde(s);
			xfree(s);
		}
E 24
		if (b = index(s, LBRC)) {
			char **bl;
			int i, len;
			if ((len = globbrace(s, b, &bl)) < 0) {
				blkfree(nv);
				error("Missing %c", -len);
E 16
			}
D 16
			for (s--; *s; s++)
				if (amatch(s, p))
					return (1);
			return (0);
E 16
I 16
			xfree(s);
			if (len == 1) {
				*vl-- = *bl;
				xfree((char *) bl);
				continue;
			}
			len = blklen(bl);
			if (&el[len] >= &nv[size]) {
				int l, e;
				l = &el[len] - &nv[size];
				size += GAVSIZ > l ? GAVSIZ : l;
				l = vl - nv;
				e = el - nv;
				nv = (char **) xrealloc(nv, 
							size * sizeof(char *));
				vl = nv + l;
				el = nv + e;
			}
			vp = vl--;
			*vp = *bl;
			len--;
			for (bp = el; bp != vp; bp--) 
			     bp[len] = *bp;
			el += len;
			vp++;
			for (bp = bl + 1; *bp; *vp++ = *bp++)
				continue;
			xfree(bl);
		}
    
E 25
I 25
    /*
     * Step 2: expand braces
     */
    el = vl;
D 48
    vl = nv;
D 44
    for (s = *vl; s; s = *++vl) {
	Char   *b;
	Char  **vp, **bp;
E 44
I 44
    expbrace(&vl, &el, size);
E 44

E 48
I 48
    expbrace(&nv, &el, size);
E 48
D 33
	if (b = Strchr(s, LBRC)) {
E 33
I 33
D 35
	if ((b = Strchr(s, LBRC)) != NULL && b[1] != '\0') {
E 35
I 35
D 44
	if ((b = Strchr(s, LBRC)) != NULL && b[1] != '\0' && b[1] != RBRC) {
E 35
E 33
	    Char  **bl;
	    int     len;
E 44

D 44
	    if ((len = globbrace(s, b, &bl)) < 0) {
		blkfree(nv);
		stderror(ERR_MISSING, -len);
	    }
	    xfree((ptr_t) s);
	    if (len == 1) {
		*vl-- = *bl;
		xfree((ptr_t) bl);
		continue;
	    }
	    len = blklen(bl);
	    if (&el[len] >= &nv[size]) {
		int     l, e;

		l = &el[len] - &nv[size];
		size += GLOBSPACE > l ? GLOBSPACE : l;
		l = vl - nv;
		e = el - nv;
		nv = (Char **) xrealloc((ptr_t) nv, (size_t)
					size * sizeof(Char *));
		vl = nv + l;
		el = nv + e;
	    }
	    vp = vl--;
	    *vp = *bl;
	    len--;
	    for (bp = el; bp != vp; bp--)
		bp[len] = *bp;
	    el += len;
	    vp++;
	    for (bp = bl + 1; *bp; *vp++ = *bp++)
		continue;
	    xfree((ptr_t) bl);
E 25
	}
I 24
D 25
	/*
	 * Step 3 expand tilde
	 */
E 24
	vl = nv;
D 24
	return(vl);
E 24
I 24
	for (s = *vl; s; s = *++vl)
		if (*s == '~') {
			*vl = globtilde(nv, s);
			xfree(s);
		}
	return(nv);
E 25
I 25

    }

E 44
    /*
     * Step 3: expand ~
     */
    vl = nv;
    for (s = *vl; s; s = *++vl)
	if (*s == '~')
	    *vl = globtilde(nv, s);
    vl = nv;
    return (vl);
E 25
E 24
}

I 17
D 21
int
globcheck(str)
	char *str;
{
	for (; *str; str++)
		if(isglob(*str))
			return(1);
	return(0);
}

E 21
E 17
D 25
char * 
globone(str)
	char *str;
E 25
I 25
static Char *
handleone(str, vl, action)
    Char   *str, **vl;
    int     action;
E 25
{
D 25
	
	char *v[2];
	char *nstr;
E 25
E 16

D 16
		case 0:
			return (scc == 0);
E 16
I 16
D 25
	noglob = adrof("noglob") != 0;
	gflag = 0;
	v[0] = str;
	v[1] = 0;
	tglob(v);
	if (gflag == G_NONE)
		return (strip(savestr(str)));
E 25
I 25
    Char   *cp, **vlp = vl;
E 25
E 16

D 16
		default:
D 7
			if (c != scc)
E 7
I 7
			if ((c & TRIM) != scc)
E 7
				return (0);
			continue;
E 16
I 16
D 25
	if (gflag & G_CSH) {
		char **vl;
E 25
I 25
    switch (action) {
    case G_ERROR:
D 42
	setname(short2str(str));
E 42
I 42
	setname(vis_str(str));
E 42
	blkfree(vl);
	stderror(ERR_NAME | ERR_AMBIG);
	break;
    case G_APPEND:
	trim(vlp);
	str = Strsave(*vlp++);
	do {
	    cp = Strspl(str, STRspace);
	    xfree((ptr_t) str);
	    str = Strspl(cp, *vlp);
	    xfree((ptr_t) cp);
	}
	while (*++vlp);
	blkfree(vl);
	break;
    case G_IGNORE:
	str = Strsave(strip(*vlp));
	blkfree(vl);
	break;
I 44
    default:
	break;
E 44
    }
    return (str);
}
E 25
E 16

D 16
		case '?':
			if (scc == 0)
				return (0);
			continue;
E 16
I 16
D 25
		/*
		 * Expand back-quote, tilde and brace
		 */
		vl = globexpand(v);
		if (vl[1] != (char *) 0) {
			blkfree(vl);
			setname(str);
			bferr("Ambiguous");
			/*NOTREACHED*/
		}
		nstr = vl[0];
		xfree((char *) vl);
E 25
I 25
static Char **
libglob(vl)
    Char  **vl;
{
D 33
    int     gflgs = GLOB_QUOTE | GLOB_NOCHECK;
E 33
I 33
    int     gflgs = GLOB_QUOTE | GLOB_NOMAGIC;
E 33
    glob_t  globv;
    char   *ptr;
I 33
    int     nonomatch = adrof(STRnonomatch) != 0, magic = 0, match = 0;
E 33

I 36
    if (!vl || !vl[0])
	return (vl);

E 36
    globv.gl_offs = 0;
    globv.gl_pathv = 0;
    globv.gl_pathc = 0;
D 33
    nonomatch = adrof(STRnonomatch) != 0;
E 33
I 33

    if (nonomatch)
	gflgs |= GLOB_NOCHECK;

E 33
    do {
	ptr = short2qstr(*vl);
	switch (glob(ptr, gflgs, 0, &globv)) {
	case GLOB_ABEND:
D 42
	    setname(ptr);
E 42
I 42
	    setname(vis_str(*vl));
E 42
	    stderror(ERR_NAME | ERR_GLOB);
	    /* NOTREACHED */
	case GLOB_NOSPACE:
	    stderror(ERR_NOMEM);
	    /* NOTREACHED */
	default:
	    break;
E 25
	}
D 25
	else	
		nstr = str;
	
	if (!noglob && (gflag & G_GLOB)) {
		glob_t globv;
E 25
I 25
D 33
	if (!nonomatch && (globv.gl_matchc == 0) &&
	    (globv.gl_flags & GLOB_MAGCHAR)) {
	    globfree(&globv);
D 27
	    return ((Char **) 0);
E 27
I 27
	    return (NULL);
E 33
I 33
	if (globv.gl_flags & GLOB_MAGCHAR) {
	    match |= (globv.gl_matchc != 0);
	    magic = 1;
E 33
E 27
	}
	gflgs |= GLOB_APPEND;
    }
    while (*++vl);
D 33
    vl = blk2short(globv.gl_pathv);
E 33
I 33
D 40
    vl = (globv.gl_pathc == 0 || (magic && !match && !nonomatch)) ? 
E 40
I 40
    vl = (globv.gl_pathc == 0 || (magic && !match && !nonomatch)) ?
E 40
	NULL : blk2short(globv.gl_pathv);
E 33
    globfree(&globv);
    return (vl);
}
E 25
E 16

D 16
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
E 16
I 16
D 25
		globv.gl_offs = 0;
		globv.gl_pathv = 0;
D 17
		glob(nstr, GLOB_NOCHECK, 0, &globv);
E 17
I 17
		nonomatch = adrof("nonomatch") != 0;
		glob(nstr, nonomatch ? GLOB_NOCHECK : 0, 0, &globv);
E 17
		if (gflag & G_CSH)
			xfree(nstr);
D 17
		if (globv.gl_pathc != 1) {
E 17
I 17
		switch (globv.gl_pathc) {
		case 0:
E 17
			setname(str);
			globfree(&globv);
I 17
			bferr("No match");
			/*NOTREACHED*/
		case 1:
			str = strip(savestr(globv.gl_pathv[0]));
			globfree(&globv);
			return(str);
		default:
			setname(str);
			globfree(&globv);
E 17
			bferr("Ambiguous");
			/*NOTREACHED*/
E 16
		}
E 25
I 25
Char   *
globone(str, action)
    Char   *str;
    int     action;
{
D 34

E 34
    Char   *v[2], **vl, **vo;
I 34
    int    gflg;
E 34

    noglob = adrof(STRnoglob) != 0;
    gflag = 0;
    v[0] = str;
    v[1] = 0;
    tglob(v);
D 34
    if (gflag == G_NONE)
E 34
I 34
    gflg = gflag;
    if (gflg == G_NONE)
E 34
	return (strip(Strsave(str)));

D 34
    if (gflag & G_CSH) {
E 34
I 34
    if (gflg & G_CSH) {
E 34
	/*
	 * Expand back-quote, tilde and brace
	 */
	vo = globexpand(v);
D 34
	if (noglob || (gflag & G_GLOB) == 0) {
E 34
I 34
	if (noglob || (gflg & G_GLOB) == 0) {
E 34
I 30
	    if (vo[0] == NULL) {
		xfree((ptr_t) vo);
		return (Strsave(STRNULL));
	    }
E 30
D 27
	    if (vo[1] != (Char *) 0)
E 27
I 27
	    if (vo[1] != NULL)
E 27
		return (handleone(str, vo, action));
	    else {
		str = strip(vo[0]);
		xfree((ptr_t) vo);
		return (str);
	    }
E 25
I 16
D 17
		if (adrof("nonomatch") == 0) {
			gflag = 0;
			tglob(globv.gl_pathv);
			/* No match */
			if (gflag != G_NONE) {
				setname(str);
				globfree(&globv);
				bferr("No match");
				/*NOTREACHED*/
			}
		}
		str = strip(savestr(globv.gl_pathv[0]));
		globfree(&globv);
		return(str);
E 17
E 16
	}
I 16
D 19
	return(strip(nstr));
E 19
I 19
D 25
	return(nstr ? strip(nstr) : (char *) 0);
E 25
I 25
    }
D 34
    else if (noglob || (gflag & G_GLOB) == 0)
E 34
I 34
    else if (noglob || (gflg & G_GLOB) == 0)
E 34
	return (strip(Strsave(str)));
    else
	vo = v;

    vl = libglob(vo);
D 34
    if (gflag & G_CSH)
E 34
I 34
D 37
    if (gflg & G_CSH)
E 37
I 37
    if ((gflg & G_CSH) && vl != vo)
E 37
E 34
	blkfree(vo);
D 27
    if (vl == (Char **) 0) {
E 27
I 27
    if (vl == NULL) {
E 27
D 42
	setname(short2str(str));
E 42
I 42
	setname(vis_str(str));
E 42
	stderror(ERR_NAME | ERR_NOMATCH);
    }
D 30
    else if (vl[1])
E 30
I 30
    if (vl[0] == NULL) {
	xfree((ptr_t) vl);
	return (Strsave(STRNULL));
    }
    if (vl[1] != NULL)
E 30
	return (handleone(str, vl, action));
    else {
	str = strip(*vl);
	xfree((ptr_t) vl);
I 30
	return (str);
E 30
    }
D 30
    return (str);
E 30
E 25
E 19
E 16
}

D 16
Gmatch(s, p)
	register char *s, *p;
E 16
I 16
D 25
char **
E 25
I 25
Char  **
E 25
globall(v)
D 25
	char **v;
E 25
I 25
    Char  **v;
E 25
E 16
{
D 16
	register int scc;
	int ok, lc;
	int c, cc;
E 16
I 16
D 25
	char *c, **vl, **vo;
E 25
I 25
    Char  **vl, **vo;
I 34
    int   gflg = gflag;
E 34
E 25
E 16

D 16
	for (;;) {
		scc = *s++ & TRIM;
		switch (c = *p++) {
E 16
I 16
D 25
	if (!v || !v[0]) {
		gargv = saveblk(v);
		gargc = blklen(gargv);
		return (gargv);
	}
E 25
I 25
    if (!v || !v[0]) {
	gargv = saveblk(v);
	gargc = blklen(gargv);
	return (gargv);
    }
E 25
E 16

D 16
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
				bferr("Missing ]");
			continue;

		case '*':
			if (!*p)
				return (1);
			for (s--; *s; s++)
				if (Gmatch(s, p))
					return (1);
			return (0);
E 16
I 16
D 25
	noglob = adrof("noglob") != 0;
I 17
	nonomatch = adrof("nonomatch") != 0;
E 17
	
	if (gflag & G_CSH) 
		/*
		 * Expand back-quote, tilde and brace
		 */
		vl = vo = globexpand(v);
	else	
		vl = vo = saveblk(v);
	    
	if (!noglob && (gflag & G_GLOB)) {
		/*
		 * Glob the strings in vl using the glob routine
		 * from libc
		 */
I 17
		int gappend = 0;
E 17
		glob_t globv;
E 25
I 25
    noglob = adrof(STRnoglob) != 0;
E 25
E 16

D 16
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

E 16
I 16
D 25
		globv.gl_offs = 0;
		globv.gl_pathv = 0;
I 20
		gargc = 0;
E 20
D 17
		glob(vl[0], GLOB_NOCHECK, 0, &globv);
		while (*++vl) 
			glob(*vl, GLOB_NOCHECK | GLOB_APPEND, 0, &globv);
		if (gflag & G_CSH)
			blkfree(vo);
		if (adrof("nonomatch") == 0) {
			gflag = 0;
			tglob(globv.gl_pathv);
			if (gflag != G_NONE) {
				/* No match */
				globfree(&globv);
				gargc = 0;
				return(gargv = (char **) 0);
E 17
I 17
		do {
D 20
			if (nonomatch)
E 20
I 20
D 21
			if (nonomatch) 
E 20
				glob(*vl, GLOB_NOCHECK | gappend, 0, &globv);
			else if (globcheck(*vl)) {
				glob(*vl, gappend, 0, &globv);
D 20
				if (globv.gl_pathc == 0) {
E 20
I 20
				if (globv.gl_pathc == gargc) {
E 20
					if (gflag & G_CSH)
						blkfree(vo);
					globfree(&globv);
					gargc = 0;
					return(gargv = (char **) 0);
				}
E 21
I 21
			glob(*vl, gappend | GLOB_NOCHECK, 0, &globv);
			if (!nonomatch && (globv.gl_matchc == 0) && 
			    (globv.gl_flags & GLOB_MAGCHAR)) {
				if (gflag & G_CSH)
					blkfree(vo);
				globfree(&globv);
				gargc = 0;
				return(gargv = (char **) 0);
E 21
E 17
			}
I 17
D 20
			else
E 20
I 20
D 21
			else 
E 20
				glob(*vl, GLOB_NOCHECK | gappend, 0, &globv);
E 21
			gappend = GLOB_APPEND;
I 20
D 21
			gargc = globv.gl_pathc;
E 21
E 20
E 17
E 16
		}
I 17
		while (*++vl);
E 25
I 25
D 34
    if (gflag & G_CSH)
E 34
I 34
    if (gflg & G_CSH)
E 34
	/*
	 * Expand back-quote, tilde and brace
	 */
	vl = vo = globexpand(v);
    else
	vl = vo = saveblk(v);
E 25
I 21

E 21
I 18
D 25
		if (gflag & G_CSH)
			blkfree(vo);
E 18
E 17
I 16
		if (globv.gl_pathc)
			vl = saveblk(globv.gl_pathv);
		else
			vl = 0;
		globfree(&globv);
E 16
	}
E 25
I 25
D 34
    if (!noglob && (gflag & G_GLOB)) {
E 34
I 34
    if (!noglob && (gflg & G_GLOB)) {
E 34
	vl = libglob(vo);
D 34
	if (gflag & G_CSH)
E 34
I 34
D 37
	if (gflg & G_CSH)
E 37
I 37
	if ((gflg & G_CSH) && vl != vo)
E 37
E 34
	    blkfree(vo);
    }
I 38
    else
	trim(vl);
E 38
E 25
D 16
}
E 16

D 16
Gcat(s1, s2)
D 8
	register char *s1, *s2;
E 8
I 8
	char *s1, *s2;
E 8
{
I 8
	register char *p, *q;
	int n;
E 8

D 8
	gnleft -= strlen(s1) + strlen(s2) + 1;
E 8
I 8
	for (p = s1; *p++;)
		;
	for (q = s2; *q++;)
		;
	gnleft -= (n = (p - s1) + (q - s2) - 1);
E 8
	if (gnleft <= 0 || ++gargc >= GAVSIZ)
		error("Arguments too long");
	gargv[gargc] = 0;
D 8
	gargv[gargc - 1] = strspl(s1, s2);
E 8
I 8
	p = gargv[gargc - 1] = xalloc((unsigned)n);
	for (q = s1; *p++ = *q++;)
		;
	for (p--, q = s2; *p++ = *q++;)
		;
E 16
I 16
D 25
	gargc = vl ? blklen(vl) : 0;
	return(gargv = vl);
E 25
I 25
    gargc = vl ? blklen(vl) : 0;
    return (gargv = vl);
E 25
E 16
E 8
}
D 16

addpath(c)
	char c;
E 16
I 16
D 25
		
E 25
I 25

void
E 25
ginit()
E 16
{
D 16

	if (gpathp >= lastgpathp)
		error("Pathname too long");
D 10
	*gpathp++ = c;
E 10
I 10
	*gpathp++ = c & TRIM;
E 10
	*gpathp = 0;
E 16
I 16
D 25
	gargsiz = GAVSIZ;
	gargv = (char **) xalloc(sizeof(char *) * gargsiz);
	gargv[0] = 0;
	gargc = 0;
E 25
I 25
    gargsiz = GLOBSPACE;
    gargv = (Char **) xmalloc((size_t) sizeof(Char *) * gargsiz);
    gargv[0] = 0;
    gargc = 0;
E 25
E 16
}

I 25
void
E 25
rscan(t, f)
D 25
	register char **t;
	int (*f)();
E 25
I 25
    register Char **t;
    void    (*f) ();
E 25
{
D 8
	register char *p, c;
E 8
I 8
D 25
	register char *p;
E 25
I 25
    register Char *p;
E 25
E 8

D 8
	while (p = *t++) {
		if (f == tglob)
			if (*p == '~')
				gflag |= 2;
			else if (eq(p, "{") || eq(p, "{}"))
				continue;
		while (c = *p++)
			(*f)(c);
	}
E 8
I 8
D 25
	while (p = *t++)
		while (*p)
			(*f)(*p++);
E 25
I 25
D 50
    while (p = *t++)
E 50
I 50
    while ((p = *t++) != NULL)
E 50
	while (*p)
	    (*f) (*p++);
E 25
E 8
}

I 25
void
E 25
D 8
scan(t, f)
E 8
I 8
trim(t)
E 8
D 25
	register char **t;
E 25
I 25
    register Char **t;
E 25
D 8
	int (*f)();
E 8
{
D 8
	register char *p, c;
E 8
I 8
D 25
	register char *p;
E 25
I 25
    register Char *p;
E 25
E 8

D 25
	while (p = *t++)
D 8
		while (c = *p)
			*p++ = (*f)(c);
E 8
I 8
D 9
		while (*p++ &= TRIM)
			;
E 9
I 9
		while (*p)
			*p++ &= TRIM;
E 25
I 25
D 50
    while (p = *t++)
E 50
I 50
    while ((p = *t++) != NULL)
E 50
	while (*p)
	    *p++ &= TRIM;
E 25
E 9
E 8
}

I 25
void
E 25
D 8
tglob(c)
	register char c;
E 8
I 8
tglob(t)
D 25
	register char **t;
E 25
I 25
    register Char **t;
E 25
E 8
{
I 8
D 25
	register char *p, c;
E 25
I 25
    register Char *p, c;
E 25
E 8

D 8
	if (any(c, globchars))
		gflag |= c == '{' ? 2 : 1;
	return (c);
E 8
I 8
D 25
	while (p = *t++) {
		if (*p == '~')
D 16
			gflag |= 2;
		else if (*p == '{' && (p[1] == '\0' || p[1] == '}' && p[2] == '\0'))
E 16
I 16
			gflag |= G_CSH;
		else if (*p == '{' &&
		    (p[1] == '\0' || p[1] == '}' && p[2] == '\0'))
E 16
			continue;
		while (c = *p++)
D 13
			if (cmap(c, _GLOB))
E 13
I 13
			if (isglob(c))
E 13
D 16
				gflag |= c == '{' ? 2 : 1;
E 16
I 16
			    gflag |= (c == '{' || c == '`') ? G_CSH : G_GLOB;
E 16
	}
E 25
I 25
D 50
    while (p = *t++) {
E 50
I 50
    while ((p = *t++) != NULL) {
E 50
	if (*p == '~' || *p == '=')
	    gflag |= G_CSH;
	else if (*p == '{' &&
D 44
		 (p[1] == '\0' || p[1] == '}' && p[2] == '\0'))
E 44
I 44
		 (p[1] == '\0' || (p[1] == '}' && p[2] == '\0')))
E 44
	    continue;
D 44
	while (c = *p++)
	    if (isglob(c))
		gflag |= (c == '{' || c == '`') ? G_CSH : G_GLOB;
E 44
I 44
D 50
	while (c = *p++) {
E 50
I 50
	while ((c = *p++) != '\0') {
E 50
	    /*
	     * eat everything inside the matching backquotes
	     */
	    if (c == '`') {
		gflag |= G_CSH;
		while (*p && *p != '`') 
		    if (*p++ == '\\') {
			if (*p)		/* Quoted chars */
			    p++;
			else
			    break;
		    }
		if (*p)			/* The matching ` */
		    p++;
		else
		    break;
	    }
	    else if (c == '{')
		gflag |= G_CSH;
	    else if (isglob(c))
		gflag |= G_GLOB;
	}
E 44
    }
E 25
E 8
}

D 8
trim(c)
	char c;
{

	return (c & TRIM);
}

tback(c)
	char c;
{

	if (c == '`')
		gflag = 1;
}

E 8
D 16
char *
globone(str)
	register char *str;
{
	char *gv[2];
	register char **gvp;
	register char *cp;

	gv[0] = str;
	gv[1] = 0;
	gflag = 0;
D 8
	rscan(gv, tglob);
E 8
I 8
	tglob(gv);
E 8
	if (gflag) {
		gvp = glob(gv);
		if (gvp == 0) {
			setname(str);
			bferr("No match");
		}
		cp = *gvp++;
		if (cp == 0)
			cp = "";
		else if (*gvp) {
			setname(str);
			bferr("Ambiguous");
		} else
			cp = strip(cp);
E 16
/*
D 16
		if (cp == 0 || *gvp) {
			setname(str);
			bferr(cp ? "Ambiguous" : "No output");
		}
*/
		xfree((char *)gargv); gargv = 0;
	} else {
D 8
		scan(gv, trim);
E 8
I 8
		trim(gv);
E 8
		cp = savestr(gv[0]);
	}
	return (cp);
}

/*
 * Command substitute cp.  If literal, then this is
 * a substitution from a << redirection, and so we should
 * not crunch blanks and tabs, separating words only at newlines.
E 16
I 16
 * Command substitute cp.  If literal, then this is a substitution from a
 * << redirection, and so we should not crunch blanks and tabs, separating
 * words only at newlines.
E 16
 */
D 25
char **
E 25
I 25
Char  **
E 25
dobackp(cp, literal)
D 25
	char *cp;
	bool literal;
E 25
I 25
    Char   *cp;
    bool    literal;
E 25
{
D 25
	register char *lp, *rp;
D 16
	char *ep;
	char word[BUFSIZ];
	char *apargv[GAVSIZ + 2];
E 16
I 16
	char *ep, word[MAXPATHLEN];
E 25
I 25
    register Char *lp, *rp;
    Char   *ep, word[MAXPATHLEN];
E 25
E 16

D 25
	if (pargv) {
		abort();
		blkfree(pargv);
E 25
I 25
    if (pargv) {
I 44
#ifdef notdef
E 44
	abort();
I 44
#endif
E 44
	blkfree(pargv);
    }
    pargsiz = GLOBSPACE;
    pargv = (Char **) xmalloc((size_t) sizeof(Char *) * pargsiz);
    pargv[0] = NULL;
    pargcp = pargs = word;
    pargc = 0;
    pnleft = MAXPATHLEN - 4;
    for (;;) {
	for (lp = cp; *lp != '`'; lp++) {
	    if (*lp == 0) {
		if (pargcp != pargs)
		    pword();
		return (pargv);
	    }
	    psave(*lp);
E 25
	}
D 16
	pargv = apargv;
E 16
I 16
D 25
	pargsiz = GAVSIZ;
	pargv = (char **) xalloc(sizeof(char *) * pargsiz);
E 16
	pargv[0] = NOSTR;
	pargcp = pargs = word;
	pargc = 0;
D 16
	pnleft = BUFSIZ - 4;
E 16
I 16
	pnleft = MAXPATHLEN - 4;
E 16
	for (;;) {
		for (lp = cp; *lp != '`'; lp++) {
			if (*lp == 0) {
				if (pargcp != pargs)
					pword();
D 16
#ifdef GDEBUG
				printf("leaving dobackp\n");
#endif
				return (pargv = copyblk(pargv));
E 16
I 16
				return (pargv);
E 16
			}
			psave(*lp);
		}
		lp++;
		for (rp = lp; *rp && *rp != '`'; rp++)
			if (*rp == '\\') {
				rp++;
				if (!*rp)
					goto oops;
			}
E 25
I 25
	lp++;
	for (rp = lp; *rp && *rp != '`'; rp++)
	    if (*rp == '\\') {
		rp++;
E 25
		if (!*rp)
D 16
oops:
			error("Unmatched `");
E 16
I 16
D 25
oops:			error("Unmatched `");
E 16
		ep = savestr(lp);
		ep[rp - lp] = 0;
		backeval(ep, literal);
D 16
#ifdef GDEBUG
		printf("back from backeval\n");
#endif
E 16
		cp = rp + 1;
	}
E 25
I 25
		    goto oops;
	    }
	if (!*rp)
    oops:  stderror(ERR_UNMATCHED, '`');
	ep = Strsave(lp);
	ep[rp - lp] = 0;
	backeval(ep, literal);
	cp = rp + 1;
    }
E 25
}

I 25
static void
E 25
backeval(cp, literal)
D 25
	char *cp;
	bool literal;
E 25
I 25
    Char   *cp;
    bool    literal;
E 25
{
D 16
	int pvec[2];
	int quoted = (literal || (cp[0] & QUOTE)) ? QUOTE : 0;
	char ibuf[BUFSIZ];
	register int icnt = 0, c;
E 16
I 16
D 25
	register int icnt, c;
E 16
	register char *ip;
D 16
	bool hadnl = 0;
	char *fakecom[2];
E 16
	struct command faket;
I 16
	bool hadnl;
	int pvec[2], quoted;
	char *fakecom[2], ibuf[BUFSIZ];
E 25
I 25
    register int icnt, c;
    register Char *ip;
    struct command faket;
    bool    hadnl;
    int     pvec[2], quoted;
    Char   *fakecom[2], ibuf[BUFSIZ];
    char    tibuf[BUFSIZ];
E 25
E 16

I 16
D 25
	hadnl = 0;
	icnt = 0;
	quoted = (literal || (cp[0] & QUOTE)) ? QUOTE : 0;
E 16
D 22
	faket.t_dtyp = TCOM;
E 22
I 22
	faket.t_dtyp = NODE_COMMAND;
E 22
	faket.t_dflg = 0;
	faket.t_dlef = 0;
	faket.t_drit = 0;
	faket.t_dspr = 0;
	faket.t_dcom = fakecom;
	fakecom[0] = "` ... `";
	fakecom[1] = 0;
E 25
I 25
    hadnl = 0;
    icnt = 0;
    quoted = (literal || (cp[0] & QUOTE)) ? QUOTE : 0;
    faket.t_dtyp = NODE_COMMAND;
    faket.t_dflg = 0;
    faket.t_dlef = 0;
    faket.t_drit = 0;
    faket.t_dspr = 0;
    faket.t_dcom = fakecom;
    fakecom[0] = STRfakecom1;
    fakecom[1] = 0;
E 25
I 16

I 46
D 47
    if (didfds == 0) {
	/*
	 * Make sure that we have some file descriptors to
	 * play with, so that the processes have at least 0, 1, 2
	 * open
	 */
	(void) dcopy(SHIN, 0);
	(void) dcopy(SHOUT, 1);
	(void) dcopy(SHERR, 2);
    }

E 47
E 46
E 16
D 25
	/*
D 16
	 * We do the psave job to temporarily change the current job
	 * so that the following fork is considered a separate job.
	 * This is so that when backquotes are used in a
	 * builtin function that calls glob the "current job" is not corrupted.
	 * We only need one level of pushed jobs as long as we are sure to
	 * fork here.
E 16
I 16
	 * We do the psave job to temporarily change the current job so that
	 * the following fork is considered a separate job.  This is so that
	 * when backquotes are used in a builtin function that calls glob the
	 * "current job" is not corrupted.  We only need one level of pushed
	 * jobs as long as we are sure to fork here.
E 16
	 */
	psavejob();
E 25
I 25
    /*
     * We do the psave job to temporarily change the current job so that the
     * following fork is considered a separate job.  This is so that when
     * backquotes are used in a builtin function that calls glob the "current
     * job" is not corrupted.  We only need one level of pushed jobs as long as
     * we are sure to fork here.
     */
    psavejob();
E 25
I 16

I 25
    /*
     * It would be nicer if we could integrate this redirection more with the
     * routines in sh.sem.c by doing a fake execute on a builtin function that
     * was piped out.
     */
    mypipe(pvec);
    if (pfork(&faket, -1) == 0) {
	struct wordent paraml;
	struct command *t;

	(void) close(pvec[0]);
	(void) dmove(pvec[1], 1);
D 33
	(void) dmove(SHDIAG, 2);
E 33
I 33
	(void) dmove(SHERR, 2);
E 33
	initdesc();
E 25
E 16
	/*
D 16
	 * It would be nicer if we could integrate this redirection more
	 * with the routines in sh.sem.c by doing a fake execute on a builtin
E 16
I 16
D 25
	 * It would be nicer if we could integrate this redirection more with
	 * the routines in sh.sem.c by doing a fake execute on a builtin
E 16
	 * function that was piped out.
E 25
I 25
	 * Bugfix for nested backquotes by Michael Greim <greim@sbsvax.UUCP>,
	 * posted to comp.bugs.4bsd 12 Sep. 1989.
E 25
	 */
D 25
	mypipe(pvec);
	if (pfork(&faket, -1) == 0) {
		struct wordent paraml;
		struct command *t;
E 25
I 25
	if (pargv)		/* mg, 21.dec.88 */
	    blkfree(pargv), pargv = 0, pargsiz = 0;
	/* mg, 21.dec.88 */
	arginp = cp;
	while (*cp)
	    *cp++ &= TRIM;
I 41

        /*
	 * In the child ``forget'' everything about current aliases or
	 * eval vectors.
	 */
	alvec = NULL;
	evalvec = NULL;
	alvecp = NULL;
	evalp = NULL;
E 41
	(void) lex(&paraml);
	if (seterr)
	    stderror(ERR_OLD);
	alias(&paraml);
	t = syntax(paraml.next, &paraml, 0);
	if (seterr)
	    stderror(ERR_OLD);
	if (t)
	    t->t_dflg |= F_NOFORK;
	(void) signal(SIGTSTP, SIG_IGN);
	(void) signal(SIGTTIN, SIG_IGN);
	(void) signal(SIGTTOU, SIG_IGN);
D 26
	execute(t, -1);
E 26
I 26
	execute(t, -1, NULL, NULL);
E 26
	exitstat();
    }
    xfree((ptr_t) cp);
    (void) close(pvec[1]);
    c = 0;
D 27
    ip = (Char *) 0;
E 27
I 27
    ip = NULL;
E 27
    do {
	int     cnt = 0;
E 25

D 8
		close(pvec[0]);
		dmove(pvec[1], 1);
		dmove(SHDIAG, 2);
E 8
I 8
D 25
		(void) close(pvec[0]);
		(void) dmove(pvec[1], 1);
		(void) dmove(SHDIAG, 2);
E 8
		initdesc();
		arginp = cp;
		while (*cp)
			*cp++ &= TRIM;
D 8
		lex(&paraml);
E 8
I 8
		(void) lex(&paraml);
E 8
		if (err)
			error(err);
		alias(&paraml);
		t = syntax(paraml.next, &paraml, 0);
		if (err)
			error(err);
		if (t)
D 22
			t->t_dflg |= FPAR;
E 22
I 22
			t->t_dflg |= F_NOFORK;
E 22
I 6
D 7
		sigignore(SIGTSTP);
		sigignore(SIGTTIN);
		sigignore(SIGTTOU);
E 7
I 7
D 8
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
E 8
I 8
		(void) signal(SIGTSTP, SIG_IGN);
		(void) signal(SIGTTIN, SIG_IGN);
		(void) signal(SIGTTOU, SIG_IGN);
E 8
E 7
E 6
		execute(t, -1);
		exitstat();
	}
	xfree(cp);
D 8
	close(pvec[1]);
E 8
I 8
	(void) close(pvec[1]);
E 8
	do {
		int cnt = 0;
		for (;;) {
			if (icnt == 0) {
				ip = ibuf;
				icnt = read(pvec[0], ip, BUFSIZ);
				if (icnt <= 0) {
					c = -1;
					break;
				}
			}
			if (hadnl)
				break;
			--icnt;
			c = (*ip++ & TRIM);
			if (c == 0)
				break;
			if (c == '\n') {
				/*
D 16
				 * Continue around the loop one
				 * more time, so that we can eat
				 * the last newline without terminating
				 * this word.
E 16
I 16
				 * Continue around the loop one more time, so
				 * that we can eat the last newline without
				 * terminating this word.
E 16
				 */
				hadnl = 1;
				continue;
			}
			if (!quoted && (c == ' ' || c == '\t'))
				break;
			cnt++;
			psave(c | quoted);
E 25
I 25
	for (;;) {
	    if (icnt == 0) {
		int     i;

		ip = ibuf;
		do
		    icnt = read(pvec[0], tibuf, BUFSIZ);
		while (icnt == -1 && errno == EINTR);
		if (icnt <= 0) {
		    c = -1;
		    break;
E 25
		}
I 25
		for (i = 0; i < icnt; i++)
		    ip[i] = (unsigned char) tibuf[i];
	    }
	    if (hadnl)
		break;
	    --icnt;
	    c = (*ip++ & TRIM);
	    if (c == 0)
		break;
	    if (c == '\n') {
E 25
		/*
D 16
		 * Unless at end-of-file, we will form a new word
		 * here if there were characters in the word, or in
		 * any case when we take text literally.  If
		 * we didn't make empty words here when literal was
		 * set then we would lose blank lines.
E 16
I 16
D 25
		 * Unless at end-of-file, we will form a new word here if there
		 * were characters in the word, or in any case when we take
		 * text literally.  If we didn't make empty words here when
		 * literal was set then we would lose blank lines.
E 25
I 25
		 * Continue around the loop one more time, so that we can eat
		 * the last newline without terminating this word.
E 25
E 16
		 */
D 25
		if (c != -1 && (cnt || literal))
			pword();
		hadnl = 0;
	} while (c >= 0);
D 16
#ifdef GDEBUG
	printf("done in backeval, pvec: %d %d\n", pvec[0], pvec[1]);
	printf("also c = %c <%o>\n", c, c);
#endif
E 16
D 8
	close(pvec[0]);
E 8
I 8
	(void) close(pvec[0]);
E 8
	pwait();
	prestjob();
E 25
I 25
		hadnl = 1;
		continue;
	    }
	    if (!quoted && (c == ' ' || c == '\t'))
		break;
	    cnt++;
	    psave(c | quoted);
	}
	/*
	 * Unless at end-of-file, we will form a new word here if there were
	 * characters in the word, or in any case when we take text literally.
	 * If we didn't make empty words here when literal was set then we
	 * would lose blank lines.
	 */
	if (c != -1 && (cnt || literal))
	    pword();
	hadnl = 0;
    } while (c >= 0);
    (void) close(pvec[0]);
    pwait();
    prestjob();
E 25
}

I 25
static void
E 25
psave(c)
D 25
	char c;
E 25
I 25
D 27
    Char    c;
E 27
I 27
    int    c;
E 27
E 25
{
D 16

E 16
D 25
	if (--pnleft <= 0)
		error("Word too long");
	*pargcp++ = c;
E 25
I 25
    if (--pnleft <= 0)
	stderror(ERR_WTOOLONG);
    *pargcp++ = c;
E 25
}

I 25
static void
E 25
pword()
{
D 16

E 16
D 25
	psave(0);
D 16
	if (pargc == GAVSIZ)
		error("Too many words from ``");
E 16
I 16
	if (pargc == pargsiz - 1) {
	    pargsiz += GAVSIZ;
	    pargv = (char **) xrealloc(pargv, pargsiz * sizeof(char *));
	}
E 16
	pargv[pargc++] = savestr(pargs);
	pargv[pargc] = NOSTR;
D 16
#ifdef GDEBUG
	printf("got word %s\n", pargv[pargc-1]);
#endif
E 16
	pargcp = pargs;
D 16
	pnleft = BUFSIZ - 4;
E 16
I 16
	pnleft = MAXPATHLEN - 4;
E 25
I 25
    psave(0);
    if (pargc == pargsiz - 1) {
	pargsiz += GLOBSPACE;
	pargv = (Char **) xrealloc((ptr_t) pargv,
				   (size_t) pargsiz * sizeof(Char *));
    }
    pargv[pargc++] = Strsave(pargs);
    pargv[pargc] = NULL;
    pargcp = pargs;
    pnleft = MAXPATHLEN - 4;
E 25
}

I 25
D 44
int
E 44
I 44
int 
E 44
E 25
Gmatch(string, pattern)
I 44
    Char *string, *pattern;
{
    Char **blk, **p;
    int	   gpol = 1, gres = 0;

    if (*pattern == '^') {
	gpol = 0;
	pattern++;
    }

    blk = (Char **) xmalloc(GLOBSPACE * sizeof(Char *));
    blk[0] = Strsave(pattern);
    blk[1] = NULL;

    expbrace(&blk, NULL, GLOBSPACE);

    for (p = blk; *p; p++)
	gres |= pmatch(string, *p);

    blkfree(blk);
    return(gres == gpol);
} 

D 45
int
E 45
I 45
static int
E 45
pmatch(string, pattern)
E 44
D 25
	register char *string, *pattern;
E 25
I 25
    register Char *string, *pattern;
E 25
{
D 25
	register char stringc, patternc;
	int match;
	char lastchar, rangec;
E 25
I 25
    register Char stringc, patternc;
D 44
    int     match;
E 44
I 44
    int     match, negate_range;
E 44
    Char    rangec;
E 25

D 25
	for (;; ++string) {
		stringc = *string & TRIM;
		switch (patternc = *pattern++) {
		case 0:
			return (stringc == 0);
		case '?':
			if (stringc == 0)
				return (0);
E 25
I 25
    for (;; ++string) {
	stringc = *string & TRIM;
	patternc = *pattern++;
	switch (patternc) {
	case 0:
	    return (stringc == 0);
	case '?':
	    if (stringc == 0)
		return (0);
	    break;
	case '*':
	    if (!*pattern)
		return (1);
	    while (*string)
		if (Gmatch(string++, pattern))
		    return (1);
	    return (0);
	case '[':
	    match = 0;
I 44
D 50
	    if (negate_range = (*pattern == '^'))
E 50
I 50
	    if ((negate_range = (*pattern == '^')) != 0)
E 50
		pattern++;
E 44
D 50
	    while (rangec = *pattern++) {
E 50
I 50
	    while ((rangec = *pattern++) != '\0') {
E 50
		if (rangec == ']')
D 44
		    if (match)
E 25
			break;
D 25
		case '*':
			if (!*pattern)
				return (1);
			while (*string) 
				if (Gmatch(string++, pattern))
					return (1);
E 25
I 25
		    else
E 25
			return (0);
E 44
I 44
		    break;
E 44
D 25
		case '[':
			lastchar = -1;
			match = 0;
			while (rangec = *pattern++) {
				if (rangec == ']')
					if (match)
						break;
					else
						return (0);
				if (match)
					continue;
				if (rangec == '-') 
					match = (stringc <= *pattern++ &&
					    *(pattern-2) <= stringc);
				else {
					lastchar = rangec;
					match = (stringc == rangec);
				}
			}
			if (rangec == 0)
				bferr("Missing ]");
			break;
		default:
			if ((patternc & TRIM) != stringc)
				return (0);
			break;

E 25
I 25
		if (match)
		    continue;
D 31
		if (rangec == '-') {
		    match = (stringc <= *pattern &&
			     *(pattern - 2) <= stringc);
E 31
I 31
D 44
		if (rangec == '-' && *(pattern - 2) != '[' && *pattern != ']') {
E 44
I 44
		if (rangec == '-' && *(pattern-2) != '[' && *pattern  != ']') {
E 44
		    match = (stringc <= (*pattern & TRIM) &&
D 44
			     (*(pattern - 2) & TRIM) <= stringc);
E 44
I 44
			      (*(pattern-2) & TRIM) <= stringc);
E 44
E 31
		    pattern++;
E 25
		}
I 25
D 44
		else
		    match = (stringc == rangec);
E 44
I 44
		else 
		    match = (stringc == (rangec & TRIM));
E 44
	    }
	    if (rangec == 0)
		stderror(ERR_NAME | ERR_MISSING, ']');
I 44
	    if (match == negate_range)
		return (0);
E 44
	    break;
	default:
	    if ((patternc & TRIM) != stringc)
		return (0);
	    break;

E 25
	}
I 25
    }
E 25
}

I 25
void
E 25
Gcat(s1, s2)
D 25
	char *s1, *s2;
E 25
I 25
    Char   *s1, *s2;
E 25
{
D 25
	register char *p, *q;
	int n;
E 25
I 25
    register Char *p, *q;
    int     n;
E 25

D 25
	for (p = s1; *p++;);
	for (q = s2; *q++;);
	n = (p - s1) + (q - s2) - 1;
	if (++gargc >= gargsiz) {
		gargsiz += GAVSIZ;
		gargv = (char **) xrealloc(gargv, gargsiz * sizeof(char *));
	}
	gargv[gargc] = 0;
	p = gargv[gargc - 1] = xalloc((unsigned)n);
	for (q = s1; *p++ = *q++;);
	for (p--, q = s2; *p++ = *q++;);
E 25
I 25
D 40
    for (p = s1; *p++;);
    for (q = s2; *q++;);
E 40
I 40
    for (p = s1; *p++;)
	continue;
    for (q = s2; *q++;)
	continue;
E 40
    n = (p - s1) + (q - s2) - 1;
    if (++gargc >= gargsiz) {
	gargsiz += GLOBSPACE;
	gargv = (Char **) xrealloc((ptr_t) gargv,
				   (size_t) gargsiz * sizeof(Char *));
    }
    gargv[gargc] = 0;
    p = gargv[gargc - 1] = (Char *) xmalloc((size_t) n * sizeof(Char));
D 40
    for (q = s1; *p++ = *q++;);
    for (p--, q = s2; *p++ = *q++;);
E 40
I 40
D 50
    for (q = s1; *p++ = *q++;)
E 50
I 50
    for (q = s1; (*p++ = *q++) != '\0';)
E 50
	continue;
D 50
    for (p--, q = s2; *p++ = *q++;)
E 50
I 50
    for (p--, q = s2; (*p++ = *q++) != '\0';)
E 50
	continue;
E 40
E 25
}

I 25
#ifdef FILEC
E 25
int
D 25
sortscmp(a1, a2)
	char **a1, **a2;
E 25
I 25
sortscmp(a, b)
D 43
    register Char **a, **b;
E 43
I 43
D 44
    register void *a, *b;
E 44
I 44
    register const ptr_t a, b;
E 44
E 43
E 25
{
D 25
	return(strcmp(*a1, *a2));
E 25
I 25
#if defined(NLS) && !defined(NOSTRCOLL)
    char    buf[2048];
D 43

E 43
#endif

D 43
    if (!a)			/* check for NULL */
E 43
I 43
D 49
    if (a)			/* check for NULL */
E 49
I 49
    if (!a)			/* check for NULL */
E 49
E 43
	return (b ? 1 : 0);
    if (!b)
	return (-1);

D 43
    if (!*a)			/* check for NULL */
	return (*b ? 1 : 0);
    if (!*b)
E 43
I 43
    if (!*(Char **)a)			/* check for NULL */
	return (*(Char **)b ? 1 : 0);
    if (!*(Char **)b)
E 43
	return (-1);

#if defined(NLS) && !defined(NOSTRCOLL)
D 43
    (void) strcpy(buf, short2str(*a));
    return ((int) strcoll(buf, short2str(*b)));
E 43
I 43
    (void) strcpy(buf, short2str(*(Char **)a));
    return ((int) strcoll(buf, short2str(*(Char **)b)));
E 43
#else
D 43
    return ((int) Strcmp(*a, *b));
E 43
I 43
    return ((int) Strcmp(*(Char **)a, *(Char **)b));
E 43
#endif
E 25
E 16
}
I 25
#endif /* FILEC */
E 25
E 1
