h00255
s 00104/00011/00421
d D 8.2 95/04/28 15:38:28 tef 16 15
c Better portability to other systems.
e
s 00002/00002/00430
d D 8.1 93/06/06 13:59:03 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00020/00006/00412
d D 5.8 92/07/21 10:28:23 bostic 14 13
c prototype lpr to fix quad's
e
s 00004/00004/00414
d D 5.7 91/03/04 13:33:07 bostic 13 12
c don't define BUFSIZ unless necessary
e
s 00002/00000/00416
d D 5.6 91/02/06 12:03:34 bostic 12 11
c stdio.h defines BUFSIZ
e
s 00001/00011/00415
d D 5.5 90/06/01 18:44:28 bostic 11 10
c new copyright notice
e
s 00006/00006/00420
d D 5.4 89/05/11 14:09:42 bostic 10 9
c file reorg, pathnames.h, paths.h
e
s 00010/00005/00416
d D 5.3 88/06/30 18:00:05 bostic 9 8
c install approved copyright notice
e
s 00009/00003/00412
d D 5.2 88/05/05 18:08:22 bostic 8 7
c written by Ralph Campbell; add Berkeley specific header
e
s 00007/00002/00408
d D 5.1 85/06/06 10:07:04 dist 7 6
c Add copyright
e
s 00004/00001/00406
d D 1.6 83/07/17 00:11:53 sam 6 5
c put sccs id's to some use
e
s 00054/00002/00353
d D 1.5 83/05/13 11:52:02 ralph 5 4
c bug fixes and changes for lpc command.
e
s 00000/00000/00355
d D 1.4 83/01/05 11:27:27 root 4 3
c Working version of remote spooling.
e
s 00001/00000/00354
d D 1.3 81/06/01 16:33:46 sam 3 2
c forgot the keyword id line
e
s 00144/00033/00210
d D 1.2 81/06/01 16:31:17 sam 2 1
c updated to the newest version of termcap
e
s 00243/00000/00000
d D 1.1 81/05/09 16:34:48 root 1 0
c date and time created 81/05/09 16:34:48 by root
e
u
U
t
T
I 7
/*
D 15
 * Copyright (c) 1983 Regents of the University of California.
D 8
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
D 11
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
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 9
E 8
 */

E 7
I 3
D 6
/*	%M%	%I%	%E%	*/
E 6
I 6
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif
E 7
I 7
D 8
#endif not lint
E 8
I 8
#endif /* not lint */
E 8
E 7

I 13
D 14
#include <ctype.h>
E 14
I 14
#include <sys/param.h>

#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
E 14
#include <stdio.h>
I 14
#include <ctype.h>
#include <string.h>
#include "lp.h"
E 14
#include "pathnames.h"

E 13
I 12
#ifndef BUFSIZ
E 12
E 6
E 3
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
D 7
/* Copyright (c) 1979 Regents of the University of California */
E 7
D 2
#define	BUFSIZ	512
E 2
I 2
#define	BUFSIZ	1024
I 12
#endif
E 12
#define MAXHOP	32	/* max number of tc= indirections */
E 2
D 13

#include <ctype.h>
I 2
D 5
#include "local/uparm.h"
E 5
I 5
#include <stdio.h>
I 10
#include "pathnames.h"
E 13

E 10
E 5
E 2
/*
I 16
 * getcap-style interface for the old printcap routines.
 *
 * !!!USE THIS INTERFACE ONLY IF YOU DON'T HAVE THE REAL GETCAP!!!
 */

static char *pbp;		/* pointer into pbuf for pgetstr() */
static char pbuf[BUFSIZ];	/* buffer for capability strings */
extern char line[];		/* buffer for printcap entries */

int
cgetnext(bp, db_array)
        register char **bp;
	char **db_array;
{
	int ret;
	char *strdup();

	pbp = pbuf;
	ret = getprent(line);
	*bp = strdup(line);
	return (ret);
}

int
cgetent(bp, db_array, name)
	char **bp, **db_array, *name;
{
	int i;

	*bp = line;
	pbp = pbuf;
	i = pgetent(*bp, name);
	if (i < 0)
		return (-2);
	else if (i == 0)
		return (-1);
	else
		return (0);
}

char *
cgetcap(buf, cap, type)
	char *buf, *cap;
	int type;
{
	return ((char *) pgetflag(cap));
}

int
cgetstr(buf, cap, str)
	char *buf, *cap;
	char **str;
{
	char *pgetstr __P((char *, char **));

	if (pbp >= pbuf+BUFSIZ) {
		write(2, "Capability string buffer overflow\n", 34);
		return (-1);
	}
	return ((*str = pgetstr(cap, &pbp)) == NULL ? -1 : 0);
}

int
cgetnum(buf, cap, num)
	char *buf, *cap;
	long *num;
{
	return ((*num = pgetnum(cap)) < 0 ? -1 : 0);
}

int
cgetclose()
{
	void endprent __P((void));

	endprent();
	return (0);
}


/*
E 16
D 2
 * printcap - routines for dealing with the line printer capability data base
E 2
I 2
 * termcap - routines for dealing with the terminal capability data base
E 2
 *
 * BUG:		Should use a "last" pointer in tbuf, so that searching
 *		for capabilities alphabetically would not be a n**2/2
 *		process when large numbers of capabilities are given.
I 2
 * Note:	If we add a last pointer now we will screw up the
 *		tc capability. We really should compile termcap.
E 2
 *
 * Essentially all the work here is scanning and decoding escapes
 * in string capabilities.  We don't use stdio because the editor
 * doesn't, and because living w/o it is not hard.
 */

D 2
static	char *pbuf;
char	*pskip();
char	*pgetstr();
char	*pdecode();
E 2
I 2
#define PRINTCAP
E 2

I 2
#ifdef PRINTCAP
#define tgetent	pgetent
#define tskip	pskip
#define tgetstr	pgetstr
#define tdecode pdecode
#define tgetnum	pgetnum
#define	tgetflag pgetflag
#define tdecode pdecode
#define tnchktc	pnchktc
#define	tnamatch pnamatch
D 10
#undef E_TERMCAP
#define E_TERMCAP "/etc/printcap"
E 10
#define V6
#endif

I 5
static	FILE *pfp = NULL;	/* printcap data base file pointer */
E 5
static	char *tbuf;
D 5
static	int hopcount;	/* detect infinite loops in termcap, init 0 */
E 5
I 5
static	int hopcount;		/* detect infinite loops in termcap, init 0 */
I 16
static	int tf;
E 16
E 5
D 14
char	*tskip();
char	*tgetstr();
char	*tdecode();
char	*getenv();
E 14
I 5

I 16
char *tgetstr __P((char *, char **));
E 16
I 14
static char *tskip __P((char *));
D 16
static char *tskip __P((char *bp));
E 16
static char *tdecode __P((char *, char **));

E 14
/*
 * Similar to tgetent except it returns the next enrty instead of
 * doing a lookup.
 */
I 14
int
E 14
getprent(bp)
	register char *bp;
{
	register int c, skip = 0;

D 10
	if (pfp == NULL && (pfp = fopen(E_TERMCAP, "r")) == NULL)
E 10
I 10
	if (pfp == NULL && (pfp = fopen(_PATH_PRINTCAP, "r")) == NULL)
E 10
		return(-1);
	tbuf = bp;
	for (;;) {
		switch (c = getc(pfp)) {
		case EOF:
			fclose(pfp);
			pfp = NULL;
			return(0);
		case '\n':
			if (bp == tbuf) {
				skip = 0;
				continue;
			}
			if (bp[-1] == '\\') {
				bp--;
				continue;
			}
			*bp = '\0';
			return(1);
		case '#':
			if (bp == tbuf)
				skip++;
		default:
			if (skip)
				continue;
			if (bp >= tbuf+BUFSIZ) {
				write(2, "Termcap entry too long\n", 23);
				*bp = '\0';
				return(1);
			}
			*bp++ = c;
		}
	}
}

I 14
void
E 14
endprent()
{
D 16
	if (pfp != NULL)
		fclose(pfp);
E 16
I 16
	if (pfp != NULL) {
		/*
		 * Can't use fclose here because on POSIX-compliant
		 * systems, fclose() causes the file pointer of the
		 * underlying file descriptor (which is possibly shared
		 * with a parent process) to be adjusted, and this
		 * reeks havoc in the parent because it doesn't know
		 * the file pointer has changed.
		 */
		(void) close(fileno(pfp));
		pfp = NULL;
	}
E 16
}
E 5

E 2
/*
D 2
 * Get an entry for printer name in buffer bp,
 * from the printcap file.  Parse is very rudimentary;
E 2
I 2
 * Get an entry for terminal name in buffer bp,
 * from the termcap file.  Parse is very rudimentary;
E 2
 * we just notice escaped newlines.
 */
I 14
int
E 14
D 2
pgetent(bp, name)
E 2
I 2
tgetent(bp, name)
E 2
	char *bp, *name;
{
	register char *cp;
	register int c;
	register int i = 0, cnt = 0;
	char ibuf[BUFSIZ];
I 2
D 14
	char *cp2;
E 14
E 2
D 16
	int tf;
E 16

D 2
	pbuf = bp;
	tf = open("/etc/printcap", 0);
E 2
I 2
	tbuf = bp;
D 16
	tf = 0;
E 16
#ifndef V6
	cp = getenv("TERMCAP");
	/*
	 * TERMCAP can have one of two things in it. It can be the
	 * name of a file to use instead of /etc/termcap. In this
	 * case it better start with a "/". Or it can be an entry to
	 * use so we don't have to read the file. In this case it
	 * has to already have the newlines crunched out.
	 */
	if (cp && *cp) {
		if (*cp!='/') {
			cp2 = getenv("TERM");
			if (cp2==(char *) 0 || strcmp(name,cp2)==0) {
				strcpy(bp,cp);
				return(tnchktc());
			} else {
D 10
				tf = open(E_TERMCAP, 0);
E 10
I 10
				tf = open(_PATH_PRINTCAP, 0);
E 10
			}
		} else
			tf = open(cp, 0);
	}
I 16
#endif
E 16
	if (tf==0)
D 10
		tf = open(E_TERMCAP, 0);
E 10
I 10
		tf = open(_PATH_PRINTCAP, 0);
E 10
D 16
#else
D 10
	tf = open(E_TERMCAP, 0);
E 10
I 10
	tf = open(_PATH_PRINTCAP, 0);
E 10
#endif
E 16
E 2
	if (tf < 0)
		return (-1);
	for (;;) {
		cp = bp;
		for (;;) {
			if (i == cnt) {
				cnt = read(tf, ibuf, BUFSIZ);
				if (cnt <= 0) {
					close(tf);
I 16
					tf = 0;
E 16
					return (0);
				}
				i = 0;
			}
			c = ibuf[i++];
			if (c == '\n') {
				if (cp > bp && cp[-1] == '\\'){
					cp--;
					continue;
				}
				break;
			}
D 2
			*cp++ = c;
E 2
I 2
			if (cp >= bp+BUFSIZ) {
				write(2,"Termcap entry too long\n", 23);
				break;
			} else
				*cp++ = c;
E 2
		}
		*cp = 0;

		/*
		 * The real work for the match.
		 */
D 2
		if (pnamatch(name)) {
E 2
I 2
		if (tnamatch(name)) {
E 2
D 16
			close(tf);
D 2
			return (1);
E 2
I 2
			return(tnchktc());
E 16
I 16
			lseek(tf, 0L, 0);
			i = tnchktc();
			if (tf) {
				close(tf);
				tf = 0;
			}
			return(i);
E 16
E 2
		}
	}
}

/*
D 2
 * Tnamatch deals with name matching.  The first field of the printcap
E 2
I 2
 * tnchktc: check the last entry, see if it's tc=xxx. If so,
 * recursively find xxx and append that entry (minus the names)
 * to take the place of the tc=xxx entry. This allows termcap
 * entries to say "like an HP2621 but doesn't turn on the labels".
 * Note that this works because of the left to right scan.
 */
I 14
int
E 14
tnchktc()
{
	register char *p, *q;
	char tcname[16];	/* name of similar terminal */
	char tcbuf[BUFSIZ];
	char *holdtbuf = tbuf;
	int l;

	p = tbuf + strlen(tbuf) - 2;	/* before the last colon */
	while (*--p != ':')
		if (p<tbuf) {
			write(2, "Bad termcap entry\n", 18);
			return (0);
		}
	p++;
	/* p now points to beginning of last field */
	if (p[0] != 't' || p[1] != 'c')
		return(1);
	strcpy(tcname,p+3);
	q = tcname;
	while (q && *q != ':')
		q++;
	*q = 0;
	if (++hopcount > MAXHOP) {
		write(2, "Infinite tc= loop\n", 18);
		return (0);
	}
	if (tgetent(tcbuf, tcname) != 1)
		return(0);
	for (q=tcbuf; *q != ':'; q++)
		;
	l = p - holdtbuf + strlen(q);
	if (l > BUFSIZ) {
		write(2, "Termcap entry too long\n", 23);
		q[BUFSIZ - (p-tbuf)] = 0;
	}
	strcpy(p, q+1);
	tbuf = holdtbuf;
	return(1);
}

/*
 * Tnamatch deals with name matching.  The first field of the termcap
E 2
 * entry is a sequence of names separated by |'s, so we compare
 * against each such name.  The normal : terminator after the last
 * name (before the first field) stops us.
 */
I 14
int
E 14
D 2
pnamatch(np)
E 2
I 2
tnamatch(np)
E 2
	char *np;
{
	register char *Np, *Bp;

D 2
	Bp = pbuf;
E 2
I 2
	Bp = tbuf;
	if (*Bp == '#')
		return(0);
E 2
	for (;;) {
		for (Np = np; *Np && *Bp == *Np; Bp++, Np++)
			continue;
		if (*Np == 0 && (*Bp == '|' || *Bp == ':' || *Bp == 0))
			return (1);
		while (*Bp && *Bp != ':' && *Bp != '|')
			Bp++;
		if (*Bp == 0 || *Bp == ':')
			return (0);
		Bp++;
	}
}

/*
 * Skip to the next field.  Notice that this is very dumb, not
 * knowing about \: escapes or any such.  If necessary, :'s can be put
D 2
 * into the printcap file in octal.
E 2
I 2
 * into the termcap file in octal.
E 2
 */
static char *
D 2
pskip(bp)
E 2
I 2
tskip(bp)
E 2
	register char *bp;
{

	while (*bp && *bp != ':')
		bp++;
	if (*bp == ':')
		bp++;
	return (bp);
}

/*
 * Return the (numeric) option id.
 * Numeric options look like
 *	li#80
 * i.e. the option string is separated from the numeric value by
 * a # character.  If the option is not found we return -1.
 * Note that we handle octal numbers beginning with 0.
 */
I 14
int
E 14
D 2
pgetnum(id)
E 2
I 2
tgetnum(id)
E 2
	char *id;
{
	register int i, base;
D 2
	register char *bp = pbuf;
E 2
I 2
	register char *bp = tbuf;
E 2

	for (;;) {
D 2
		bp = pskip(bp);
E 2
I 2
		bp = tskip(bp);
E 2
		if (*bp == 0)
			return (-1);
		if (*bp++ != id[0] || *bp == 0 || *bp++ != id[1])
			continue;
I 2
		if (*bp == '@')
			return(-1);
E 2
		if (*bp != '#')
			continue;
		bp++;
		base = 10;
		if (*bp == '0')
			base = 8;
		i = 0;
		while (isdigit(*bp))
			i *= base, i += *bp++ - '0';
		return (i);
	}
}

/*
 * Handle a flag option.
 * Flag options are given "naked", i.e. followed by a : or the end
 * of the buffer.  Return 1 if we find the option, or 0 if it is
 * not given.
 */
I 14
int
E 14
D 2
pgetflag(id)
E 2
I 2
tgetflag(id)
E 2
	char *id;
{
D 2
	register char *bp = pbuf;
E 2
I 2
	register char *bp = tbuf;
E 2

	for (;;) {
D 2
		bp = pskip(bp);
E 2
I 2
		bp = tskip(bp);
E 2
		if (!*bp)
			return (0);
D 2
		if (*bp++ == id[0] && *bp != 0 && *bp++ == id[1] && (!*bp || *bp == ':'))
			return (1);
E 2
I 2
		if (*bp++ == id[0] && *bp != 0 && *bp++ == id[1]) {
			if (!*bp || *bp == ':')
				return (1);
			else if (*bp == '@')
				return(0);
		}
E 2
	}
}

/*
 * Get a string valued option.
 * These are given as
 *	cl=^Z
 * Much decoding is done on the strings, and the strings are
 * placed in area, which is a ref parameter which is updated.
 * No checking on area overflow.
 */
char *
D 2
pgetstr(id, area)
E 2
I 2
tgetstr(id, area)
E 2
	char *id, **area;
{
D 2
	register char *bp = pbuf;
E 2
I 2
	register char *bp = tbuf;
E 2

	for (;;) {
D 2
		bp = pskip(bp);
E 2
I 2
		bp = tskip(bp);
E 2
		if (!*bp)
			return (0);
		if (*bp++ != id[0] || *bp == 0 || *bp++ != id[1])
			continue;
I 2
		if (*bp == '@')
			return(0);
E 2
		if (*bp != '=')
			continue;
		bp++;
D 2
		return (pdecode(bp, area));
E 2
I 2
		return (tdecode(bp, area));
E 2
	}
}

/*
 * Tdecode does the grung work to decode the
 * string capability escapes.
 */
static char *
D 2
pdecode(str, area)
E 2
I 2
tdecode(str, area)
E 2
	register char *str;
	char **area;
{
	register char *cp;
	register int c;
	register char *dp;
	int i;

	cp = *area;
	while ((c = *str++) && c != ':') {
		switch (c) {

		case '^':
			c = *str++ & 037;
			break;

		case '\\':
			dp = "E\033^^\\\\::n\nr\rt\tb\bf\f";
			c = *str++;
nextc:
			if (*dp++ == c) {
				c = *dp++;
				break;
			}
			dp++;
			if (*dp)
				goto nextc;
			if (isdigit(c)) {
				c -= '0', i = 2;
				do
					c <<= 3, c |= *str++ - '0';
				while (--i && isdigit(*str));
			}
			break;
		}
		*cp++ = c;
	}
	*cp++ = 0;
	str = *area;
	*area = cp;
	return (str);
}
I 14
D 16

E 16
E 14
E 1
