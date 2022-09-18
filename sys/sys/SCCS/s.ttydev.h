h50891
s 00003/00003/00031
d D 8.2 94/01/04 16:16:55 bostic 15 14
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00002/00002/00032
d D 8.1 93/06/02 19:56:19 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00013/00028
d D 7.8 91/05/09 20:55:54 bostic 13 12
c new copyright; att/bsd/shared
e
s 00003/00003/00038
d D 7.7 91/02/05 17:04:10 bostic 12 11
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00005/00049/00036
d D 7.6 89/11/20 18:12:20 marc 11 10
c posix
e
s 00003/00003/00082
d D 7.5 89/08/13 18:55:48 marc 10 9
c cosmetic.  move some defines around.
e
s 00026/00003/00059
d D 7.4 89/05/01 23:21:31 marc 9 8
c put old speed definitions under "#define USE_OLD_TTY" - for old code
e
s 00035/00017/00027
d D 7.3 88/10/18 15:23:57 marc 8 7
c new terminal driver
e
s 00000/00007/00044
d D 7.2 86/10/13 22:07:52 karels 7 6
c rm old hardware defs
e
s 00001/00001/00050
d D 7.1 86/06/04 23:30:27 mckusick 6 5
c 4.3BSD release version
e
s 00007/00001/00044
d D 6.2 85/06/08 15:11:06 mckusick 5 4
c Add copyright
e
s 00000/00000/00045
d D 6.1 83/07/29 06:14:40 sam 4 3
c 4.2 distribution
e
s 00007/00004/00038
d D 4.3 83/05/18 02:42:26 sam 3 2
c sun changes
e
s 00007/00000/00035
d D 4.2 82/12/05 21:54:39 sam 2 1
c handle multiple #include's cleanly; include more stuff from tty.h
e
s 00035/00000/00000
d D 4.1 82/12/02 11:26:56 sam 1 0
c date and time created 82/12/02 11:26:56 by sam
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
D 13
/*
D 6
 * Copyright (c) 1982 Regents of the University of California.
E 6
I 6
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 13
I 13
/*-
D 14
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
E 13
 *
I 13
 * %sccs.include.redist.c%
 *
E 13
 *	%W% (Berkeley) %G%
 */
E 5

D 13
/*
I 11
 * COMPATABILITY HEADER FILE --
 */
E 13
I 13
/* COMPATABILITY HEADER FILE */
E 13

D 13
/*
E 11
 * Terminal definitions related to underlying hardware.
 */
E 13
I 2
D 12
#ifndef _TTYDEV_
#define	_TTYDEV_
E 12
I 12
D 15
#ifndef _TTYDEV_H_
#define	_TTYDEV_H_
E 15
I 15
#ifndef _SYS_TTYDEV_H_
#define	_SYS_TTYDEV_H_
E 15
E 12
E 2

I 2
D 3
/* hardware bits */
#define	DONE	0200
#define	IENABLE	0100

E 3
E 2
D 11
/*
 * Speeds
 */
E 11
I 9
#ifdef USE_OLD_TTY
D 13
/*
 * Speeds
 */
E 13
E 9
#define B0	0
I 9
#define B50	1
#define B75	2
#define B110	3
#define B134	4
#define B150	5
#define B200	6
#define B300	7
#define B600	8
#define B1200	9
#define	B1800	10
#define B2400	11
#define B4800	12
#define B9600	13
#define EXTA	14
#define EXTB	15
D 11
#else
#define B0	0
E 9
D 8
#define B50	1
#define B75	2
#define B110	3
#define B134	4
#define B150	5
#define B200	6
#define B300	7
#define B600	8
#define B1200	9
#define	B1800	10
#define B2400	11
#define B4800	12
#define B9600	13
#define EXTA	14
#define EXTB	15
E 8
I 8
#define B50	50
#define B75	75
#define B110	110
#define B134	134
#define B150	150
#define B200	200
#define B300	300
#define B600	600
#define B1200	1200
#define	B1800	1800
#define B2400	2400
#define B4800	4800
#define B9600	9600
#define B19200	19200
D 9
#define EXTA	B19200
E 9
#define B38400	38400
D 9
#define EXTB	B38400
E 9
I 9
#define EXTA	14
#define EXTB	15
#endif
E 9
E 8

I 9
#ifdef KERNEL

E 9
I 8
struct speedtab {
	int sp_speed;
	int sp_code;
};

E 8
D 9
#ifdef KERNEL
E 9
I 3
/*
D 7
 * Hardware bits.
 * SHOULD NOT BE HERE.
 */
#define	DONE	0200
#define	IENABLE	0100

E 3
/*
E 7
 * Modem control commands.
 */
#define	DMSET		0
#define	DMBIS		1
#define	DMBIC		2
#define	DMGET		3
I 2
D 8
#endif
E 2
#endif
E 8
I 8

/*
D 10
 * Exceptional conditions possible on character input.
E 10
I 10
 * Flags on character passed to ttyinput
E 10
 */
D 10
#define TTY_FE		0x01000000	/* Framing error or BREAK condition */
#define TTY_PE		0x02000000	/* Parity error */
E 10
#define TTY_CHARMASK	0x000000ff	/* Character mask */
#define TTY_QUOTE	0x00000100	/* Character quoted */
#define TTY_ERRORMASK	0xff000000	/* Error mask */
I 10
#define TTY_FE		0x01000000	/* Framing error or BREAK condition */
#define TTY_PE		0x02000000	/* Parity error */
E 10

#endif /* KERNEL */
E 11
I 11
#endif /* USE_OLD_TTY */
E 11

D 12
#endif /* _TTYDEV_ */
E 12
I 12
D 15
#endif /* !_TTYDEV_H_ */
E 15
I 15
#endif /* !_SYS_TTYDEV_H_ */
E 15
E 12
E 8
E 1
