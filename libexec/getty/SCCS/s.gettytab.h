h03630
s 00003/00003/00116
d D 8.2 94/03/30 13:24:03 bostic 12 11
c 1983 typo...
c From: Andras Olah <olah@cs.utwente.nl>
e
s 00002/00002/00117
d D 8.1 93/06/04 18:50:21 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00115
d D 5.6 93/05/17 10:36:52 bostic 10 9
c ANSI C prototypes
e
s 00001/00000/00118
d D 5.5 91/03/27 12:20:23 william 9 8
c added no parity flage for 386 8-bit character display console
e
s 00001/00011/00117
d D 5.4 90/06/01 15:53:46 bostic 8 7
c new copyright notice
e
s 00014/00003/00114
d D 5.3 89/02/27 09:47:05 bostic 7 6
c add Berkeley specific header for networking release
e
s 00001/00000/00116
d D 5.2 86/01/07 15:10:03 mckusick 6 5
c set DECCTLQ on specifc lines with getty (from muller@nprdc.arpa)
e
s 00007/00001/00109
d D 5.1 85/04/29 12:44:41 dist 5 4
c Add copyright
e
s 00001/00000/00109
d D 4.4 85/02/05 08:48:51 ralph 4 3
c added autobaud detection.
e
s 00001/00000/00108
d D 4.3 83/07/09 18:34:18 sam 3 2
c allow output to be flushed before first prompt to handle open lines
e
s 00004/00000/00104
d D 4.2 83/07/07 03:34:49 kre 2 1
c added a couple of #defines
e
s 00104/00000/00000
d D 4.1 83/07/06 00:10:10 sam 1 0
c date and time created 83/07/06 00:10:10 by sam
e
u
U
t
T
I 1
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*
D 7
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
D 11
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
D 12
 * Copyright (c) 1983, 1993
E 12
I 12
 * Copyright (c) 1983, 1993, 1994
E 12
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 8
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 7
 *
 *	%W% (Berkeley) %G%
 */
E 5

/*
 * Getty description definitions.
 */
struct	gettystrs {
	char	*field;		/* name to lookup in gettytab */
	char	*defalt;	/* value we find by looking in defaults */
	char	*value;		/* value that we find there */
};

struct	gettynums {
	char	*field;		/* name to lookup */
	long	defalt;		/* number we find in defaults */
	long	value;		/* number we find there */
	int	set;		/* we actually got this one */
};

struct gettyflags {
	char	*field;		/* name to lookup */
	char	invrt;		/* name existing in gettytab --> false */
	char	defalt;		/* true/false in defaults */
	char	value;		/* true/false flag */
	char	set;		/* we found it */
};

/*
 * String values.
 */
#define	NX	gettystrs[0].value
#define	CL	gettystrs[1].value
#define IM	gettystrs[2].value
#define	LM	gettystrs[3].value
#define	ER	gettystrs[4].value
#define	KL	gettystrs[5].value
#define	ET	gettystrs[6].value
#define	PC	gettystrs[7].value
#define	TT	gettystrs[8].value
#define	EV	gettystrs[9].value
#define	LO	gettystrs[10].value
#define HN	gettystrs[11].value
#define HE	gettystrs[12].value
#define IN	gettystrs[13].value
#define QU	gettystrs[14].value
#define XN	gettystrs[15].value
#define XF	gettystrs[16].value
#define BK	gettystrs[17].value
#define SU	gettystrs[18].value
#define DS	gettystrs[19].value
#define RP	gettystrs[20].value
#define FL	gettystrs[21].value
#define WE	gettystrs[22].value
#define LN	gettystrs[23].value

/*
 * Numeric definitions.
 */
#define	IS	gettynums[0].value
#define	OS	gettynums[1].value
#define	SP	gettynums[2].value
#define	ND	gettynums[3].value
#define	CD	gettynums[4].value
#define	TD	gettynums[5].value
#define	FD	gettynums[6].value
#define	BD	gettynums[7].value
#define	TO	gettynums[8].value
#define	F0	gettynums[9].value
#define	F0set	gettynums[9].set
#define	F1	gettynums[10].value
#define	F1set	gettynums[10].set
#define	F2	gettynums[11].value
#define	F2set	gettynums[11].set
I 3
#define	PF	gettynums[12].value
E 3

/*
 * Boolean values.
 */
#define	HT	gettyflags[0].value
#define	NL	gettyflags[1].value
#define	EP	gettyflags[2].value
I 2
#define	EPset	gettyflags[2].set
E 2
#define	OP	gettyflags[3].value
I 2
D 12
#define	OPset	gettyflags[2].set
E 12
I 12
#define	OPset	gettyflags[3].set
E 12
E 2
#define	AP	gettyflags[4].value
I 2
D 12
#define	APset	gettyflags[2].set
E 12
I 12
#define	APset	gettyflags[4].set
E 12
E 2
#define	EC	gettyflags[5].value
#define	CO	gettyflags[6].value
#define	CB	gettyflags[7].value
#define	CK	gettyflags[8].value
#define	CE	gettyflags[9].value
#define	PE	gettyflags[10].value
#define	RW	gettyflags[11].value
#define	XC	gettyflags[12].value
#define	LC	gettyflags[13].value
#define	UC	gettyflags[14].value
#define	IG	gettyflags[15].value
#define	PS	gettyflags[16].value
#define	HC	gettyflags[17].value
I 2
#define UB	gettyflags[18].value
I 4
#define AB	gettyflags[19].value
I 6
#define DX	gettyflags[20].value
I 9
#define	NP	gettyflags[21].value
E 9
E 6
E 4
E 2

D 10
int	getent();
long	getnum();
int	getflag();
char	*getstr();
E 10
I 10
int	getent __P((char *, char *));
long	getnum __P((char *));
int	getflag __P((char *));
char	*getstr __P((char *, char **));
E 10

extern	struct gettyflags gettyflags[];
extern	struct gettynums gettynums[];
extern	struct gettystrs gettystrs[];
extern	int hopcount;
E 1
