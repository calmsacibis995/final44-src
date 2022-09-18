h04996
s 00006/00000/00156
d D 5.11 91/06/08 17:08:58 christos 17 16
c More prototype fixes, Removed TERMIOS define
e
s 00002/00000/00154
d D 5.10 91/06/08 12:20:33 bostic 16 15
c include file pass, csh.h no longer include every .h in the system
c rename sigmast_t to sigset_t to match signal.h; minor pointer cleanups
e
s 00001/00001/00153
d D 5.9 91/06/07 21:02:46 christos 15 14
c typo fixes
e
s 00001/00001/00153
d D 5.8 91/06/07 20:57:37 christos 14 13
c static function prototypes
e
s 00002/00001/00152
d D 5.7 91/06/07 11:13:38 bostic 13 12
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00115/00043/00038
d D 5.6 91/06/04 13:31:51 bostic 12 11
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00007/00006/00074
d D 5.5 91/04/04 18:17:53 bostic 11 10
c new copyright; att/bsd/shared
e
s 00005/00017/00075
d D 5.4 88/06/06 11:47:08 bostic 10 9
c make cshputchar a macro
e
s 00002/00002/00090
d D 5.3 88/05/19 15:38:59 bostic 9 8
c install C version of _doprnt
e
s 00003/00003/00089
d D 5.2 85/06/06 13:08:17 edward 8 7
c cleaning up after bozos
e
s 00008/00002/00084
d D 5.1 85/06/04 11:06:34 dist 7 6
c Add copyright
e
s 00010/00029/00076
d D 4.6 84/12/13 14:38:49 edward 6 5
c performance
e
s 00001/00003/00104
d D 4.5 84/08/31 09:30:52 ralph 5 4
c use new signal calls instead of compatibility routines.
e
s 00002/00002/00105
d D 4.4 83/06/11 16:49:42 sam 4 3
c different approach, try signal compatibility package
e
s 00002/00002/00105
d D 4.3 83/06/10 23:59:27 sam 3 2
c new signals; no libjobs; still loses SIGINT by getting it masked 
c sometimes, but we check it in before we lose something
e
s 00000/00008/00107
d D 4.2 82/12/30 17:35:25 sam 2 1
c finally works (updated for 4.1c and merged with sun)
e
s 00115/00000/00000
d D 4.1 80/10/09 12:41:31 bill 1 0
c date and time created 80/10/09 12:41:31 by bill
e
u
U
t
T
I 7
D 11
/*
 * Copyright (c) 1980 Regents of the University of California.
D 8
 * All rights reserved.  The Berkeley software License Agreement
E 8
I 8
 * All rights reserved.  The Berkeley Software License Agreement
E 8
 * specifies the terms and conditions for redistribution.
E 11
I 11
/*-
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
E 11
 */

E 7
I 1
D 6
static	char *sccsid = "%Z%%M% %I% %G%";
E 6
I 6
#ifndef lint
D 7
static	char *sccsid = "%W% (Berkeley) %G%";
#endif
E 7
I 7
D 8
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 8
I 8
D 11
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 11
I 11
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 11
E 8
E 7
E 6

I 16
#include <sys/types.h>
#include <unistd.h>
I 17
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif

E 17
E 16
D 13
#include "sh.h"
E 13
I 13
#include "csh.h"
#include "extern.h"
E 13
I 6
D 12
#include <sys/ioctl.h>
E 12
E 6

D 12
/*
 * C Shell
 */
E 12
I 12
extern int Tty_eight_bit;
extern int Tty_raw_mode;
extern Char GettingInput;
E 12

I 12
int     lbuffed = 1;		/* true if line buffered */

D 14
static void p2dig();
E 14
I 14
D 15
static void	p2dig _P((int));
E 15
I 15
static void	p2dig __P((int));
E 15
E 14

void
E 12
D 2
p60ths(l)
	long l;
{

	l += 3;
	printf("%d.%d", (int) (l / 60), (int) ((l % 60) / 6));
}

E 2
psecs(l)
D 12
	long l;
E 12
I 12
    long    l;
E 12
{
D 12
	register int i;
E 12
I 12
    register int i;
E 12

D 12
	i = l / 3600;
	if (i) {
		printf("%d:", i);
		i = l % 3600;
		p2dig(i / 60);
		goto minsec;
	}
	i = l;
	printf("%d", i / 60);
E 12
I 12
    i = l / 3600;
    if (i) {
	xprintf("%d:", i);
	i = l % 3600;
	p2dig(i / 60);
	goto minsec;
    }
    i = l;
    xprintf("%d", i / 60);
E 12
minsec:
D 12
	i %= 60;
	printf(":");
	p2dig(i);
E 12
I 12
    i %= 60;
    xprintf(":");
    p2dig(i);
E 12
}

I 12
void
pcsecs(l)			/* PWP: print mm:ss.dd, l is in sec*100 */
    long    l;
{
    register int i;

    i = l / 360000;
    if (i) {
	xprintf("%d:", i);
	i = (l % 360000) / 100;
	p2dig(i / 60);
	goto minsec;
    }
    i = l / 100;
    xprintf("%d", i / 60);
minsec:
    i %= 60;
    xprintf(":");
    p2dig(i);
    xprintf(".");
    p2dig((int) (l % 100));
}

static void
E 12
p2dig(i)
D 12
	register int i;
E 12
I 12
    register int i;
E 12
{

D 12
	printf("%d%d", i / 10, i % 10);
E 12
I 12
    xprintf("%d%d", i / 10, i % 10);
E 12
}

D 10
char	linbuf[128];
char	*linp = linbuf;
E 10
I 10
D 12
char linbuf[LINELEN];
char *linp = linbuf;
E 12
I 12
char    linbuf[2048];
char   *linp = linbuf;
bool    output_raw = 0;		/* PWP */
E 12
E 10

D 9
putchar(c)
E 9
I 9
D 10
cshputchar(c)
E 9
	register int c;
E 10
I 10
D 12
cshputchar(ch)
	register int ch;
E 12
I 12
void
xputchar(c)
    register int c;
E 12
E 10
{
D 10

	if ((c & QUOTE) == 0 && (c == 0177 || c < ' ' && c != '\t' && c != '\n')) {
D 9
		putchar('^');
E 9
I 9
		cshputchar('^');
E 9
		if (c == 0177)
			c = '?';
		else
			c |= 'A' - 1;
	}
	c &= TRIM;
	*linp++ = c;
	if (c == '\n' || linp >= &linbuf[sizeof linbuf - 2])
		flush();
E 10
I 10
D 12
	CSHPUTCHAR;
E 12
I 12
    c &= CHAR | QUOTE;
    if (!output_raw && (c & QUOTE) == 0) {
	if (Iscntrl(c)) {
	    if (c != '\t' && c != '\n' && c != '\r') {
		xputchar('^');
		if (c == ASCII)
		    c = '?';
		else
		    c |= 0100;
	    }
	}
	else if (!Isprint(c)) {
	    xputchar('\\');
	    xputchar((((c >> 6) & 7) + '0'));
	    xputchar((((c >> 3) & 7) + '0'));
	    c = (c & 7) + '0';
	}
	(void) putraw(c);
    }
    else {
	c &= TRIM;
	(void) putpure(c);
    }
    if (lbuffed && (c & CHAR) == '\n')
	flush();
E 12
E 10
}

I 12
int
putraw(c)
    register int c;
{
    return putpure(c);
}

int
putpure(c)
    register int c;
{
    c &= CHAR;

    *linp++ = c;
    if (linp >= &linbuf[sizeof linbuf - 10])
	flush();
    return (1);
}

void
E 12
draino()
{
D 10

E 10
D 12
	linp = linbuf;
E 12
I 12
    linp = linbuf;
E 12
}

I 12
void
E 12
flush()
{
D 12
	register int unit;
D 6
	int lmode = 0;
E 6
I 6
	int lmode;
E 12
I 12
    register int unit;
E 12
E 6

D 6
#include <sys/ioctl.h>

E 6
D 12
	if (linp == linbuf)
		return;
	if (haderr)
		unit = didfds ? 2 : SHDIAG;
	else
		unit = didfds ? 1 : SHOUT;
#ifdef TIOCLGET
D 6
	if (didfds==0 && ioctl(unit, TIOCLGET, &lmode)==0 &&
	    lmode & LFLUSHO) {
E 6
I 6
	if (didfds == 0 && ioctl(unit, TIOCLGET, (char *)&lmode) == 0 &&
	    lmode&LFLUSHO) {
E 6
		lmode = LFLUSHO;
D 6
		ioctl(unit, TIOCLBIC, &lmode);
		write(unit, "\n", 1);
E 6
I 6
		(void) ioctl(unit, TIOCLBIC, (char *)&lmode);
		(void) write(unit, "\n", 1);
E 6
	}
E 12
I 12
    /* int lmode; */

    if (linp == linbuf)
	return;
#ifdef notdef
    if (linp < &linbuf[sizeof linbuf - 10])
	return;
E 12
#endif
D 6
	write(unit, linbuf, linp - linbuf);
E 6
I 6
D 12
	(void) write(unit, linbuf, linp - linbuf);
E 6
	linp = linbuf;
E 12
I 12
    if (haderr)
	unit = didfds ? 2 : SHDIAG;
    else
	unit = didfds ? 1 : SHOUT;
    (void) write(unit, linbuf, (size_t) (linp - linbuf));
    linp = linbuf;
E 12
D 6
}

plist(vp)
	register struct varent *vp;
{

	if (setintr)
D 3
		sigrelse(SIGINT);
E 3
I 3
D 4
		(void) sigrelse(mask(SIGINT));
E 4
I 4
D 5
		sigrelse(SIGINT);
E 5
I 5
		sigsetmask(sigblock(0) & ~ sigmask(SIGINT));
E 5
E 4
E 3
	for (vp = vp->link; vp != 0; vp = vp->link) {
		int len = blklen(vp->vec);

		printf(vp->name);
		printf("\t");
		if (len != 1)
			putchar('(');
		blkpr(vp->vec);
		if (len != 1)
			putchar(')');
		printf("\n");
	}
E 6
D 5
	if (setintr)
D 3
		sigrelse(SIGINT);
E 3
I 3
D 4
		(void) sigrelse(mask(SIGINT));
E 4
I 4
		sigrelse(SIGINT);
E 5
E 4
E 3
}
E 1
