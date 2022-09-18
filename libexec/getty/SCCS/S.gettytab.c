h16150
s 00012/00006/00307
d D 5.7 93/05/17 10:36:51 bostic 9 8
c ANSI C prototypes
e
s 00003/00003/00310
d D 5.6 92/10/24 15:26:17 ralph 8 7
c fix gcc2 static warnings
e
s 00003/00001/00310
d D 5.5 91/02/25 17:03:34 bostic 7 6
c ANSI fixes
e
s 00001/00011/00310
d D 5.4 90/06/01 15:53:41 bostic 6 5
c new copyright notice
e
s 00003/00001/00318
d D 5.3 89/04/02 12:51:20 bostic 5 4
c add pathnames.h
e
s 00015/00004/00304
d D 5.2 89/02/27 09:47:03 bostic 4 3
c add Berkeley specific header for networking release
e
s 00008/00002/00300
d D 5.1 85/04/29 12:33:30 dist 3 2
c Add copyright
e
s 00004/00004/00298
d D 4.2 83/09/25 16:31:15 karels 2 1
c correct counts on writes to stderr
e
s 00302/00000/00000
d D 4.1 83/07/06 00:10:18 sam 1 0
c date and time created 83/07/06 00:10:18 by sam
e
u
U
t
T
I 3
/*
D 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
 *
D 6
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 4
 */

E 3
I 1
#ifndef lint
D 3
static char sccsid[] = "%W% (Berkeley) %E%";
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4
E 3

I 9
#include <ctype.h>
E 9
I 5
D 7
#include <sys/file.h>
E 7
I 7
#include <fcntl.h>
D 9
#include <unistd.h>
E 9
#include <string.h>
E 7
E 5
D 9
#include <ctype.h>
E 9
I 9
#include <unistd.h>

E 9
I 5
#include "pathnames.h"
E 5

#define	TABBUFSIZ	512

static	char *tbuf;
int	hopcount;	/* detect infinite loops in termcap, init 0 */
D 8
char	*skip();
char	*getstr();
char	*decode();
E 8
I 8
D 9
static char	*skip();
extern char	*getstr();
static char	*decode();
E 9
E 8

I 9
static char	*decode __P((char *, char **));
static int	 namatch __P((char *));
static int	 nchktc __P((void));
static char	*skip __P((char *));

E 9
/*
 * Get an entry for terminal name in buffer bp,
 * from the termcap file.  Parse is very rudimentary;
 * we just notice escaped newlines.
 */
I 9
int
E 9
getent(bp, name)
	char *bp, *name;
{
	register char *cp;
	register int c;
	register int i = 0, cnt = 0;
	char ibuf[TABBUFSIZ];
D 9
	char *cp2;
E 9
	int tf;

	tbuf = bp;
D 5
	tf = open("/etc/gettytab", 0);
E 5
I 5
	tf = open(_PATH_GETTYTAB, O_RDONLY, 0);
E 5
	if (tf < 0)
		return (-1);
	for (;;) {
		cp = bp;
		for (;;) {
			if (i == cnt) {
				cnt = read(tf, ibuf, TABBUFSIZ);
				if (cnt <= 0) {
					close(tf);
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
			if (cp >= bp+TABBUFSIZ) {
D 2
				write(2,"Gettytab entry too long\n", 23);
E 2
I 2
				write(2,"Gettytab entry too long\n", 24);
E 2
				break;
			} else
				*cp++ = c;
		}
		*cp = 0;

		/*
		 * The real work for the match.
		 */
		if (namatch(name)) {
			close(tf);
			return(nchktc());
		}
	}
}

/*
 * tnchktc: check the last entry, see if it's tc=xxx. If so,
 * recursively find xxx and append that entry (minus the names)
 * to take the place of the tc=xxx entry. This allows termcap
 * entries to say "like an HP2621 but doesn't turn on the labels".
 * Note that this works because of the left to right scan.
 */
#define	MAXHOP	32
I 9
static int
E 9
nchktc()
{
	register char *p, *q;
	char tcname[16];	/* name of similar terminal */
	char tcbuf[TABBUFSIZ];
	char *holdtbuf = tbuf;
	int l;

	p = tbuf + strlen(tbuf) - 2;	/* before the last colon */
	while (*--p != ':')
		if (p<tbuf) {
D 2
			write(2, "Bad gettytab entry\n", 18);
E 2
I 2
			write(2, "Bad gettytab entry\n", 19);
E 2
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
D 2
		write(2, "Getty: infinite tc= loop\n", 18);
E 2
I 2
		write(2, "Getty: infinite tc= loop\n", 25);
E 2
		return (0);
	}
	if (getent(tcbuf, tcname) != 1)
		return(0);
	for (q=tcbuf; *q != ':'; q++)
		;
	l = p - holdtbuf + strlen(q);
	if (l > TABBUFSIZ) {
D 2
		write(2, "Gettytab entry too long\n", 23);
E 2
I 2
		write(2, "Gettytab entry too long\n", 24);
E 2
		q[TABBUFSIZ - (p-tbuf)] = 0;
	}
	strcpy(p, q+1);
	tbuf = holdtbuf;
	return(1);
}

/*
 * Tnamatch deals with name matching.  The first field of the termcap
 * entry is a sequence of names separated by |'s, so we compare
 * against each such name.  The normal : terminator after the last
 * name (before the first field) stops us.
 */
I 9
static int
E 9
namatch(np)
	char *np;
{
	register char *Np, *Bp;

	Bp = tbuf;
	if (*Bp == '#')
		return(0);
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
 * into the termcap file in octal.
 */
static char *
skip(bp)
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
long
getnum(id)
	char *id;
{
	register long i, base;
	register char *bp = tbuf;

	for (;;) {
		bp = skip(bp);
		if (*bp == 0)
			return (-1);
		if (*bp++ != id[0] || *bp == 0 || *bp++ != id[1])
			continue;
		if (*bp == '@')
			return(-1);
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
I 9
int
E 9
getflag(id)
	char *id;
{
	register char *bp = tbuf;

	for (;;) {
		bp = skip(bp);
		if (!*bp)
			return (-1);
		if (*bp++ == id[0] && *bp != 0 && *bp++ == id[1]) {
			if (!*bp || *bp == ':')
				return (1);
			else if (*bp == '!')
				return (0);
			else if (*bp == '@')
				return(-1);
		}
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
getstr(id, area)
	char *id, **area;
{
	register char *bp = tbuf;

	for (;;) {
		bp = skip(bp);
		if (!*bp)
			return (0);
		if (*bp++ != id[0] || *bp == 0 || *bp++ != id[1])
			continue;
		if (*bp == '@')
			return(0);
		if (*bp != '=')
			continue;
		bp++;
		return (decode(bp, area));
	}
}

/*
 * Tdecode does the grung work to decode the
 * string capability escapes.
 */
static char *
decode(str, area)
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
E 1
