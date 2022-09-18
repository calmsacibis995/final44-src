h56567
s 00005/00005/00404
d D 8.1 93/05/31 18:42:20 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00024/00033/00385
d D 5.11 93/03/22 06:04:30 bostic 12 11
c lint for gcc 2; remove USG/termois stuff, not used
e
s 00001/00001/00417
d D 5.10 91/12/14 13:59:05 bostic 11 10
c fix usage message
e
s 00002/00001/00416
d D 5.9 91/02/28 15:45:34 bostic 10 9
c ANSI
e
s 00001/00011/00416
d D 5.8 90/06/01 13:56:49 bostic 9 8
c new copyright notice
e
s 00007/00007/00420
d D 5.7 89/08/02 16:46:53 bostic 8 7
c handle multiple worm characters correctly, clear screen on exit
e
s 00043/00041/00384
d D 5.6 89/08/02 16:27:09 bostic 7 6
c add new chars, allow any number of worms to play
c Keith Gabryelski, Commodore Int'l.
e
s 00010/00005/00415
d D 5.5 88/06/27 16:35:22 bostic 6 5
c install approved copyright notice
e
s 00377/00321/00043
d D 5.4 88/01/02 20:30:12 bostic 5 4
c reformat; use getopt(3); lint cleanups; don't assume 24 row terminal;
c check space allocations; catch relevant signals; don't use floating point
c add Berkeley specific header
e
s 00036/00009/00328
d D 5.3 85/07/15 18:17:40 mckusick 4 3
c more terminal/system independent (from sun!guy Guy Harris)
e
s 00000/00006/00337
d D 5.2 85/06/25 13:44:16 karels 3 2
c not Berkeley copyright
e
s 00014/00001/00329
d D 5.1 85/05/29 11:26:00 dist 2 1
c Add copyright
e
s 00330/00000/00000
d D 4.1 82/10/24 18:27:04 mckusick 1 0
c date and time created 82/10/24 18:27:04 by mckusick
e
u
U
t
T
I 5
/*
D 13
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 9
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 6
 */

E 5
I 2
D 3
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */
E 2
I 1

E 3
D 2
static char sccsid[] = "	%M%	%I%	%E%	";
E 2
I 2
#ifndef lint
D 13
char copyright[] =
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
 All rights reserved.\n";
E 13
I 13
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 13
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5
E 2

I 4
D 5
#define BSD

E 5
E 4
/*
D 5

	 @@@        @@@    @@@@@@@@@@     @@@@@@@@@@@    @@@@@@@@@@@@
	 @@@        @@@   @@@@@@@@@@@@    @@@@@@@@@@@@   @@@@@@@@@@@@@
	 @@@        @@@  @@@@      @@@@   @@@@           @@@@ @@@  @@@@
	 @@@   @@   @@@  @@@        @@@   @@@            @@@  @@@   @@@
	 @@@  @@@@  @@@  @@@        @@@   @@@            @@@  @@@   @@@
	 @@@@ @@@@ @@@@  @@@        @@@   @@@            @@@  @@@   @@@
	  @@@@@@@@@@@@   @@@@      @@@@   @@@            @@@  @@@   @@@
	   @@@@  @@@@     @@@@@@@@@@@@    @@@            @@@  @@@   @@@
	    @@    @@       @@@@@@@@@@     @@@            @@@  @@@   @@@

				 Eric P. Scott
			  Caltech High Energy Physics
				 October, 1980

*/
E 5
I 5
 *
 *	 @@@        @@@    @@@@@@@@@@     @@@@@@@@@@@    @@@@@@@@@@@@
 *	 @@@        @@@   @@@@@@@@@@@@    @@@@@@@@@@@@   @@@@@@@@@@@@@
 *	 @@@        @@@  @@@@      @@@@   @@@@           @@@@ @@@  @@@@
 *	 @@@   @@   @@@  @@@        @@@   @@@            @@@  @@@   @@@
 *	 @@@  @@@@  @@@  @@@        @@@   @@@            @@@  @@@   @@@
 *	 @@@@ @@@@ @@@@  @@@        @@@   @@@            @@@  @@@   @@@
 *	  @@@@@@@@@@@@   @@@@      @@@@   @@@            @@@  @@@   @@@
 *	   @@@@  @@@@     @@@@@@@@@@@@    @@@            @@@  @@@   @@@
 *	    @@    @@       @@@@@@@@@@     @@@            @@@  @@@   @@@
 *
 *				 Eric P. Scott
 *			  Caltech High Energy Physics
 *				 October, 1980
 *
 */
#include <sys/types.h>
E 5
D 12
#include <stdio.h>
I 4
#ifdef USG
#include <termio.h>
#else
E 4
#include <sgtty.h>
D 4
#define cursor(col,row) tputs(tgoto(CM,col,row),1,outc)
outc(c)
{
	putchar(c);
}
E 4
I 4
#endif
E 12
I 12

E 12
#include <signal.h>
I 12
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
E 12
D 5
#define cursor(col,row) tputs(tgoto(CM,col,row),1,fputchar)
E 4
extern char *UP;
extern short ospeed;
int Wrap;
short *ref[24];
static char flavor[]={
    'O', '*', '#', '$', '%', '0'
E 5
I 5

static struct options {
	int nopts;
	int opts[3];
}
	normal[8] = {
	{ 3, { 7, 0, 1 } },
	{ 3, { 0, 1, 2 } },
	{ 3, { 1, 2, 3 } },
	{ 3, { 2, 3, 4 } },
	{ 3, { 3, 4, 5 } },
	{ 3, { 4, 5, 6 } },
	{ 3, { 5, 6, 7 } },
	{ 3, { 6, 7, 0 } }
},	upper[8] = {
	{ 1, { 1, 0, 0 } },
	{ 2, { 1, 2, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 2, { 4, 5, 0 } },
	{ 1, { 5, 0, 0 } },
	{ 2, { 1, 5, 0 } }
},
	left[8] = {
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 2, { 2, 3, 0 } },
	{ 1, { 3, 0, 0 } },
	{ 2, { 3, 7, 0 } },
	{ 1, { 7, 0, 0 } },
	{ 2, { 7, 0, 0 } }
},
	right[8] = {
	{ 1, { 7, 0, 0 } },
	{ 2, { 3, 7, 0 } },
	{ 1, { 3, 0, 0 } },
	{ 2, { 3, 4, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 2, { 6, 7, 0 } }
},
	lower[8] = {
	{ 0, { 0, 0, 0 } },
	{ 2, { 0, 1, 0 } },
	{ 1, { 1, 0, 0 } },
	{ 2, { 1, 5, 0 } },
	{ 1, { 5, 0, 0 } },
	{ 2, { 5, 6, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } }
},
	upleft[8] = {
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 1, { 3, 0, 0 } },
	{ 2, { 1, 3, 0 } },
	{ 1, { 1, 0, 0 } }
},
	upright[8] = {
	{ 2, { 3, 5, 0 } },
	{ 1, { 3, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 1, { 5, 0, 0 } }
},
	lowleft[8] = {
	{ 3, { 7, 0, 1 } },
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 1, { 1, 0, 0 } },
	{ 2, { 1, 7, 0 } },
	{ 1, { 7, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } }
},
	lowright[8] = {
	{ 0, { 0, 0, 0 } },
	{ 1, { 7, 0, 0 } },
	{ 2, { 5, 7, 0 } },
	{ 1, { 5, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } },
	{ 0, { 0, 0, 0 } }
E 5
};
D 5
static short xinc[]={
     1,  1,  1,  0, -1, -1, -1,  0
}, yinc[]={
    -1,  0,  1,  1,  1,  0, -1, -1
E 5
I 5

#define	cursor(c, r)	tputs(tgoto(CM, c, r), 1, fputchar)

D 7
static char	*TE;
static int	fputchar();
E 7
I 7
D 8
char	*TE;
int	fputchar();
E 8
I 8
char *tcp;
D 12
int fputchar();
E 8
E 7

E 12
static char	flavor[] = {
D 7
	'O', '*', '#', '$', '%', '0'
E 7
I 7
	'O', '*', '#', '$', '%', '0', '@', '~'
E 7
E 5
};
D 5
static struct worm {
    int orientation, head;
    short *xpos, *ypos;
} worm[40];
static char *field;
static int length=16, number=3, trail=' ';
static struct options {
    int nopts;
    int opts[3];
} normal[8]={
    { 3, { 7, 0, 1 } },
    { 3, { 0, 1, 2 } },
    { 3, { 1, 2, 3 } },
    { 3, { 2, 3, 4 } },
    { 3, { 3, 4, 5 } },
    { 3, { 4, 5, 6 } },
    { 3, { 5, 6, 7 } },
    { 3, { 6, 7, 0 } }
}, upper[8]={
    { 1, { 1, 0, 0 } },
    { 2, { 1, 2, 0 } },
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 2, { 4, 5, 0 } },
    { 1, { 5, 0, 0 } },
    { 2, { 1, 5, 0 } }
}, left[8]={
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 2, { 2, 3, 0 } },
    { 1, { 3, 0, 0 } },
    { 2, { 3, 7, 0 } },
    { 1, { 7, 0, 0 } },
    { 2, { 7, 0, 0 } }
}, right[8]={
    { 1, { 7, 0, 0 } },
    { 2, { 3, 7, 0 } },
    { 1, { 3, 0, 0 } },
    { 2, { 3, 4, 0 } },
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 2, { 6, 7, 0 } }
}, lower[8]={
    { 0, { 0, 0, 0 } },
    { 2, { 0, 1, 0 } },
    { 1, { 1, 0, 0 } },
    { 2, { 1, 5, 0 } },
    { 1, { 5, 0, 0 } },
    { 2, { 5, 6, 0 } },
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } }
}, upleft[8]={
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 1, { 3, 0, 0 } },
    { 2, { 1, 3, 0 } },
    { 1, { 1, 0, 0 } }
}, upright[8]={
    { 2, { 3, 5, 0 } },
    { 1, { 3, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 1, { 5, 0, 0 } }
}, lowleft[8]={
    { 3, { 7, 0, 1 } },
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 1, { 1, 0, 0 } },
    { 2, { 1, 7, 0 } },
    { 1, { 7, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } }
}, lowright[8]={
    { 0, { 0, 0, 0 } },
    { 1, { 7, 0, 0 } },
    { 2, { 5, 7, 0 } },
    { 1, { 5, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } },
    { 0, { 0, 0, 0 } }
E 5
I 5
static short	xinc[] = {
	1,  1,  1,  0, -1, -1, -1,  0
}, yinc[] = {
	-1,  0,  1,  1,  1,  0, -1, -1
E 5
};
I 4
D 5
char *TE;
E 4
main(argc,argv)
int argc;
char *argv[];
E 5
I 5
static struct	worm {
	int orientation, head;
	short *xpos, *ypos;
D 7
} worm[40];
E 7
I 7
} *worm;
E 7

I 12
void	 fputchar __P((int));
void	 onsig __P((int));
char	*tgetstr __P((char *, char **));
char	*tgoto __P((char *, int, int));
int	 tputs __P((char *, int, void (*)(int)));

int
E 12
main(argc, argv)
	int argc;
D 12
	char **argv;
E 12
I 12
	char *argv[];
E 12
E 5
{
D 5
    extern fputchar();
    char *malloc();
    char *getenv();
    char *tgetstr(), *tgoto();
I 4
    int quit();
E 4
    float ranf();
    register int x, y;
    register int n;
    register struct worm *w;
    register struct options *op;
    register int h;
    register short *ip;
    char *AL, *BC, *CM, *EI, *HO, *IC, *IM, *IP, *SR;
    int CO, IN, LI, last, bottom;
    char *tcp;
    register char *term;
    char tcb[100];
E 5
I 5
	extern int optind;
D 12
	extern short ospeed;
E 12
	extern char *optarg, *UP;
	register int x, y, h, n;
	register struct worm *w;
	register struct options *op;
	register short *ip;
	register char *term;
D 7
	int CO, IN, LI, last, bottom, ch, length, number, trail, Wrap,
		onsig();
E 7
I 7
	int CO, IN, LI, last, bottom, ch, length, number, trail, Wrap;
D 10
	int onsig();
E 10
I 10
D 12
	void onsig();
E 12
E 10
E 7
	short **ref;
D 7
	char *AL, *BC, *CM, *EI, *HO, *IC, *IM, *IP, *SR, *tcp,
		*field, tcb[100], *mp, *malloc(), *getenv(), *tgetstr(),
		*tgoto();
E 7
I 7
D 8
	char *AL, *BC, *CM, *EI, *HO, *IC, *IM, *IP, *SR, *tcp;
E 8
I 8
	char *AL, *BC, *CM, *EI, *HO, *IC, *IM, *IP, *SR;
E 8
D 12
	char *field, tcb[100], *mp, *malloc(), *getenv(), *tgetstr(), *tgoto();
E 12
I 12
	char *field, tcb[100], *mp;
E 12
E 7
	long random();
E 5
I 4
D 12
#ifdef USG
D 5
    struct termio sg;
E 5
I 5
	struct termio sg;
E 5
#else
E 4
D 5
    struct sgttyb sg;
E 5
I 5
	struct sgttyb sg;
E 5
I 4
#endif
E 12
E 4
D 5
    setbuf(stdout,malloc(BUFSIZ));
    for (x=1;x<argc;x++) {
	register char *p;
	p=argv[x];
	if (*p=='-') p++;
	switch (*p) {
	case 'f':
	    field="WORM";
	    break;
	case 'l':
	    if (++x==argc) goto usage;
	    if ((length=atoi(argv[x]))<2||length>1024) {
		fprintf(stderr,"%s: Invalid length\n",*argv);
E 5
I 5

	length = 16;
	number = 3;
	trail = ' ';
	field = NULL;
	while ((ch = getopt(argc, argv, "fl:n:t")) != EOF)
D 7
		switch((char)ch) {
E 7
I 7
		switch(ch) {
E 7
		case 'f':
			field = "WORM";
			break;
		case 'l':
			if ((length = atoi(optarg)) < 2 || length > 1024) {
D 7
				fprintf(stderr, "%s: invalid length; range %d - %d.\n", *argv, 2, 1024);
E 7
I 7
				(void)fprintf(stderr,
				    "worms: invalid length (%d - %d).\n",
				     2, 1024);
E 7
				exit(1);
			}
			break;
		case 'n':
D 7
			if ((number = atoi(optarg)) < 1 || number > 40) {
				fprintf(stderr, "%s: invalid number of worms; range %d - %d.\n", *argv, 1, 40);
E 7
I 7
			if ((number = atoi(optarg)) < 1) {
				(void)fprintf(stderr,
				    "worms: invalid number of worms.\n");
E 7
				exit(1);
			}
			break;
		case 't':
			trail = '.';
			break;
		case '?':
		default:
D 7
			fprintf(stderr, "usage: %s [-ft] [-length #] [-number #]\n", *argv);
E 7
I 7
			(void)fprintf(stderr,
D 11
			    "usage: worms [-ft] [-length #] [-number #]\n");
E 11
I 11
			    "usage: worms [-ft] [-l length] [-n number]\n");
E 11
E 7
			exit(1);
		}

	if (!(term = getenv("TERM"))) {
D 7
		fprintf(stderr, "%s: TERM: parameter not set\n", *argv);
E 7
I 7
		(void)fprintf(stderr, "worms: no TERM environment variable.\n");
E 7
E 5
		exit(1);
D 5
	    }
	    break;
	case 'n':
	    if (++x==argc) goto usage;
	    if ((number=atoi(argv[x]))<1||number>40) {
		fprintf(stderr,"%s: Invalid number of worms\n",*argv);
E 5
I 5
	}
D 7
	if (!(mp = malloc((u_int)1024))) {
		fprintf(stderr, "%s: out of space.\n", *argv);
E 5
		exit(1);
D 5
	    }
	    break;
	case 't':
	    trail='.';
	    break;
	default:
	usage:
	    fprintf(stderr,
		"usage: %s [-field] [-length #] [-number #] [-trail]\n",*argv);
	    exit(1);
	    break;
E 5
	}
E 7
I 7
D 12
	if (!(worm = (struct worm *)malloc((u_int)number *
	    sizeof(struct worm))) || !(mp = malloc((u_int)1024)))
E 12
I 12
	if (!(worm = malloc((size_t)number *
	    sizeof(struct worm))) || !(mp = malloc((size_t)1024)))
E 12
		nomem();
E 7
D 5
    }
    if (!(term=getenv("TERM"))) {
	fprintf(stderr,"%s: TERM: parameter not set\n",*argv);
	exit(1);
    }
    if (tgetent(malloc(1024),term)<=0) {
	fprintf(stderr,"%s: %s: unknown terminal type\n",*argv,term);
	exit(1);
    }
    tcp=tcb;
    if (!(CM=tgetstr("cm",&tcp))) {
	fprintf(stderr,"%s: terminal not capable of cursor motion\n",*argv);
	exit(1);
    }
    AL=tgetstr("al",&tcp);
    BC=tgetflag("bs") ? "\b" : tgetstr("bc",&tcp);
    if ((CO=tgetnum("co"))<=0) CO=80;
    last=CO-1;
    EI=tgetstr("ei",&tcp);
    HO=tgetstr("ho",&tcp);
    IC=tgetstr("ic",&tcp);
    IM=tgetstr("im",&tcp);
    IN=tgetflag("in");
    IP=tgetstr("ip",&tcp);
    if ((LI=tgetnum("li"))<=0) LI=24;
    bottom=LI-1;
    SR=tgetstr("sr",&tcp);
I 4
    TE=tgetstr("te",&tcp);
E 4
    UP=tgetstr("up",&tcp);
E 5
I 5
	if (tgetent(mp, term) <= 0) {
D 7
		fprintf(stderr, "%s: %s: unknown terminal type\n", *argv, term);
E 7
I 7
		(void)fprintf(stderr, "worms: %s: unknown terminal type.\n",
		    term);
E 7
		exit(1);
	}
	tcp = tcb;
	if (!(CM = tgetstr("cm", &tcp))) {
D 7
		fprintf(stderr, "%s: terminal not capable of cursor motion\n", *argv);
E 7
I 7
		(void)fprintf(stderr,
		    "worms: terminal incapable of cursor motion.\n");
E 7
		exit(1);
	}
	AL = tgetstr("al", &tcp);
	BC = tgetflag("bs") ? "\b" : tgetstr("bc", &tcp);
	if ((CO = tgetnum("co")) <= 0)
		CO = 80;
	last = CO - 1;
	EI = tgetstr("ei", &tcp);
	HO = tgetstr("ho", &tcp);
	IC = tgetstr("ic", &tcp);
	IM = tgetstr("im", &tcp);
	IN = tgetflag("in");
	IP = tgetstr("ip", &tcp);
	if ((LI = tgetnum("li")) <= 0)
		LI = 24;
	bottom = LI - 1;
	SR = tgetstr("sr", &tcp);
D 8
	TE = tgetstr("te", &tcp);
E 8
	UP = tgetstr("up", &tcp);
E 5
I 4
D 12
#ifdef USG
D 5
    ioctl(fileno(stdout),TCGETA,&sg);
    ospeed=sg.c_cflag&CBAUD;
E 5
I 5
	ioctl(1, TCGETA, &sg);
	ospeed = sg.c_cflag&CBAUD;
E 5
#else
E 4
D 5
    gtty(fileno(stdout),&sg);
    ospeed=sg.sg_ospeed;
E 5
I 5
	gtty(1, &sg);
	ospeed = sg.sg_ospeed;
E 5
I 4
#endif
E 12
E 4
D 5
    Wrap=tgetflag("am");
    ip=(short *)malloc(LI*CO*sizeof (short));
    for (n=0;n<LI;) {
	ref[n++]=ip; ip+=CO;
    }
    for (ip=ref[0],n=LI*CO;--n>=0;) *ip++=0;
    if (Wrap) ref[bottom][last]=1;
    for (n=number, w= &worm[0];--n>=0;w++) {
	w->orientation=w->head=0;
	if (!(ip=(short *)malloc(length*sizeof (short)))) {
	    fprintf(stderr,"%s: out of memory\n",*argv);
	    exit(1);
E 5
I 5
	Wrap = tgetflag("am");
D 7
	if (!(ip = (short *)malloc((u_int)(LI * CO * sizeof(short))))) {
		fprintf(stderr, "%s: out of memory\n", *argv);
		exit(1);
E 5
	}
D 5
	w->xpos=ip;
	for (x=length;--x>=0;) *ip++ = -1;
	if (!(ip=(short *)malloc(length*sizeof (short)))) {
	    fprintf(stderr,"%s: out of memory\n",*argv);
	    exit(1);
E 5
I 5
	if (!(ref = (short **)malloc((u_int)(LI * sizeof(short *))))) {
		fprintf(stderr, "%s: out of memory\n", *argv);
		exit(1);
E 5
	}
E 7
I 7
D 12
	if (!(ip = (short *)malloc((u_int)(LI * CO * sizeof(short)))))
E 12
I 12
	if (!(ip = malloc((size_t)(LI * CO * sizeof(short)))))
E 12
		nomem();
D 12
	if (!(ref = (short **)malloc((u_int)(LI * sizeof(short *)))))
E 12
I 12
	if (!(ref = malloc((size_t)(LI * sizeof(short *)))))
E 12
		nomem();
E 7
D 5
	w->ypos=ip;
	for (y=length;--y>=0;) *ip++ = -1;
    }
I 4
    signal(SIGINT, quit);
    tputs(tgetstr("ti",&tcp),1,fputchar);
E 4
    tputs(tgetstr("cl",&tcp),1,fputchar);
    if (field) {
	register char *p;
	p=field;
	for (y=bottom;--y>=0;) {
	    for (x=CO;--x>=0;) {
		putchar(*p++);
		if (!*p) p=field;
	    }
            if (!Wrap) putchar('\n');
            fflush(stdout);
        }
	if (Wrap) {
	    if (IM&&!IN) {
		for (x=last;--x>0;) {
		    putchar(*p++);
		    if (!*p) p=field;
E 5
I 5
	for (n = 0; n < LI; ++n) {
		ref[n] = ip;
		ip += CO;
	}
	for (ip = ref[0], n = LI * CO; --n >= 0;)
		*ip++ = 0;
	if (Wrap)
		ref[bottom][last] = 1;
	for (n = number, w = &worm[0]; --n >= 0; w++) {
		w->orientation = w->head = 0;
D 7
		if (!(ip = (short *)malloc((u_int)(length * sizeof(short))))) {
			fprintf(stderr, "%s: out of memory\n", *argv);
			exit(1);
E 5
		}
E 7
I 7
D 12
		if (!(ip = (short *)malloc((u_int)(length * sizeof(short)))))
E 12
I 12
		if (!(ip = malloc((size_t)(length * sizeof(short)))))
E 12
			nomem();
E 7
D 5
		y= *p++; if (!*p) p=field;
		putchar(*p);
D 4
		if (BC) fputs(BC,stdout);
E 4
I 4
		if (BC) tputs(BC,1,fputchar);
E 4
		else cursor(last-1,bottom);
D 4
		fputs(IM,stdout);
E 4
I 4
		tputs(IM,1,fputchar);
E 4
		if (IC) tputs(IC,1,fputchar);
		putchar(y);
		if (IP) tputs(IP,1,fputchar);
D 4
		fputs(EI,stdout);
E 4
I 4
		tputs(EI,1,fputchar);
E 4
	    }
	    else if (SR||AL) {
D 4
		if (HO) fputs(HO,stdout);
E 4
I 4
		if (HO) tputs(HO,1,fputchar);
E 4
		else cursor(0,0);
		if (SR) tputs(SR,1,fputchar);
		else tputs(AL,LI,fputchar);
		for (x=CO;--x>=0;) {
		    putchar(*p++);
		    if (!*p) p=field;
E 5
I 5
		w->xpos = ip;
		for (x = length; --x >= 0;)
			*ip++ = -1;
D 7
		if (!(ip = (short *)malloc((u_int)(length * sizeof(short))))) {
			fprintf(stderr, "%s: out of memory\n", *argv);
			exit(1);
E 5
		}
E 7
I 7
D 12
		if (!(ip = (short *)malloc((u_int)(length * sizeof(short)))))
E 12
I 12
		if (!(ip = malloc((size_t)(length * sizeof(short)))))
E 12
			nomem();
E 7
D 5
	    }
	    else for (x=last;--x>=0;) {
		    putchar(*p++);
		    if (!*p) p=field;
	    }
E 5
I 5
		w->ypos = ip;
		for (y = length; --y >= 0;)
			*ip++ = -1;
E 5
	}
D 5
	else for (x=CO;--x>=0;) {
	    putchar(*p++);
	    if (!*p) p=field;
E 5
I 5

	(void)signal(SIGHUP, onsig);
	(void)signal(SIGINT, onsig);
	(void)signal(SIGQUIT, onsig);
	(void)signal(SIGSTOP, onsig);
	(void)signal(SIGTSTP, onsig);
	(void)signal(SIGTERM, onsig);

	tputs(tgetstr("ti", &tcp), 1, fputchar);
	tputs(tgetstr("cl", &tcp), 1, fputchar);
	if (field) {
		register char *p = field;

		for (y = bottom; --y >= 0;) {
			for (x = CO; --x >= 0;) {
				fputchar(*p++);
				if (!*p)
					p = field;
			}
			if (!Wrap)
				fputchar('\n');
			(void)fflush(stdout);
		}
		if (Wrap) {
			if (IM && !IN) {
				for (x = last; --x > 0;) {
					fputchar(*p++);
					if (!*p)
						p = field;
				}
				y = *p++;
				if (!*p)
					p = field;
				fputchar(*p);
				if (BC)
					tputs(BC, 1, fputchar);
				else
					cursor(last - 1, bottom);
				tputs(IM, 1, fputchar);
				if (IC)
					tputs(IC, 1, fputchar);
				fputchar(y);
				if (IP)
					tputs(IP, 1, fputchar);
				tputs(EI, 1, fputchar);
			}
			else if (SR || AL) {
				if (HO)
					tputs(HO, 1, fputchar);
				else
					cursor(0, 0);
				if (SR)
					tputs(SR, 1, fputchar);
				else
					tputs(AL, LI, fputchar);
				for (x = CO; --x >= 0;) {
					fputchar(*p++);
					if (!*p)
						p = field;
				}
			}
			else for (x = last; --x >= 0;) {
				fputchar(*p++);
				if (!*p)
					p = field;
			}
		}
		else for (x = CO; --x >= 0;) {
			fputchar(*p++);
			if (!*p)
				p = field;
		}
E 5
	}
D 5
    }
    fflush(stdout);
    for (;;) {
	for (n=0,w= &worm[0];n<number;n++,w++) {
	    if ((x=w->xpos[h=w->head])<0) {
		cursor(x=w->xpos[h]=0,y=w->ypos[h]=bottom);
		putchar(flavor[n%6]);
		ref[y][x]++;
	    }
	    else y=w->ypos[h];
	    if (++h==length) h=0;
	    if (w->xpos[w->head=h]>=0) {
		register int x1, y1;
		x1=w->xpos[h]; y1=w->ypos[h];
		if (--ref[y1][x1]==0) {
		    cursor(x1,y1); putchar(trail);
E 5
I 5
	for (;;) {
		(void)fflush(stdout);
		for (n = 0, w = &worm[0]; n < number; n++, w++) {
			if ((x = w->xpos[h = w->head]) < 0) {
				cursor(x = w->xpos[h] = 0,
				     y = w->ypos[h] = bottom);
D 8
				fputchar(flavor[n % 6]);
E 8
I 8
				fputchar(flavor[n % sizeof(flavor)]);
E 8
				ref[y][x]++;
			}
			else
				y = w->ypos[h];
			if (++h == length)
				h = 0;
			if (w->xpos[w->head = h] >= 0) {
				register int x1, y1;

				x1 = w->xpos[h];
				y1 = w->ypos[h];
				if (--ref[y1][x1] == 0) {
					cursor(x1, y1);
					if (trail)
						fputchar(trail);
				}
			}
			op = &(!x ? (!y ? upleft : (y == bottom ? lowleft : left)) : (x == last ? (!y ? upright : (y == bottom ? lowright : right)) : (!y ? upper : (y == bottom ? lower : normal))))[w->orientation];
			switch (op->nopts) {
			case 0:
				(void)fflush(stdout);
				abort();
				return;
			case 1:
				w->orientation = op->opts[0];
				break;
			default:
D 7
				w->orientation = op->opts[(int)random() % op->nopts];
E 7
I 7
				w->orientation =
				    op->opts[(int)random() % op->nopts];
E 7
			}
D 7
			cursor(x += xinc[w->orientation], y += yinc[w->orientation]);
E 7
I 7
			cursor(x += xinc[w->orientation],
			    y += yinc[w->orientation]);
E 7
			if (!Wrap || x != last || y != bottom)
D 8
				fputchar(flavor[n % 6]);
E 8
I 8
				fputchar(flavor[n % sizeof(flavor)]);
E 8
			ref[w->ypos[h] = y][w->xpos[h] = x]++;
E 5
		}
D 5
	    }
            op= &(x==0 ? (y==0 ? upleft : (y==bottom ? lowleft : left)) :
                (x==last ? (y==0 ? upright : (y==bottom ? lowright : right)) :
		(y==0 ? upper : (y==bottom ? lower : normal))))[w->orientation];
	    switch (op->nopts) {
	    case 0:
		fflush(stdout);
		abort();
		return;
	    case 1:
		w->orientation=op->opts[0];
		break;
	    default:
		w->orientation=op->opts[(int)(ranf()*(float)op->nopts)];
	    }
	    cursor(x+=xinc[w->orientation], y+=yinc[w->orientation]);
	    if (!Wrap||x!=last||y!=bottom) putchar(flavor[n%6]);
	    ref[w->ypos[h]=y][w->xpos[h]=x]++;
E 5
	}
D 5
	fflush(stdout);
    }
E 5
}
I 4
D 5
quit()
E 5
I 5

I 10
void
E 10
D 7
static
E 7
D 12
onsig()
E 12
I 12
onsig(signo)
	int signo;
E 12
E 5
{
D 5
    signal(SIGINT, SIG_IGN);
    tputs(TE,1,fputchar);
    exit(0);
E 5
I 5
D 8
	tputs(TE, 1, fputchar);
E 8
I 8
	tputs(tgetstr("cl", &tcp), 1, fputchar);
	tputs(tgetstr("te", &tcp), 1, fputchar);
E 8
	exit(0);
E 5
}
I 5

I 12
void
E 12
D 7
static
E 7
E 5
E 4
fputchar(c)
D 5
char c;
E 5
I 5
D 12
	char c;
E 12
I 12
	int c;
E 12
E 5
{
D 5
    putchar(c);
}
float ranf() {
I 4
#ifdef BSD
E 4
    return((float)rand()/2147483647.);
I 4
#else
    return((float)rand()/32767.);
#endif
E 5
I 5
D 12
	putchar(c);
E 12
I 12
	(void)putchar(c);
E 12
I 7
}

nomem()
{
	(void)fprintf(stderr, "worms: not enough memory.\n");
	exit(1);
E 7
E 5
E 4
}
E 1
