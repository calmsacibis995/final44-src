h02886
s 00002/00002/00045
d D 8.1 93/06/04 17:43:01 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00006/00039
d D 5.2 91/04/22 15:49:35 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00038
d D 5.1 85/05/07 12:09:46 dist 2 1
c Add copyright notice
e
s 00039/00000/00000
d D 4.1 83/11/10 14:13:34 ralph 1 0
c date and time created 83/11/10 14:13:34 by ralph
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
D 3
/*
I 2
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
D 4
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
E 3
 *
D 3
 *	%W% (Berkeley) %G%
E 3
I 3
 * %sccs.include.proprietary.c%
E 3
 *
D 3
 *
E 3
I 3
 *	%W% (Berkeley) %G%
 */

/*
E 3
E 2
 * Displays plot files on an hp2648a graphics terminals.  I have heard
 * that all hp plotting devices use the same control sequences, so this
 * might work for all hp devices capable of plotting.
 */

#include <stdio.h>

#define TERMINAL "/dev/tty"

#define	ENQ	05
#define ACK	06
#define ESC	033
#define GRAPHIC	'*'
#define MODE	'm'
#define PLOT	'p'
#define DISPLAY 'd'
#define PENUP	'a'
#define BINARY	'i'
#define ASCII	'f'
#define CR	'\n'

#define TRUE  1
#define FALSE 0

#define xsc(xi) ((int) (xi - lowx) * scalex + 0.5)
#define ysc(yi) ((int) (yi - lowy) * scaley + 0.5)

extern int shakehands;
extern int currentx;
extern int currenty;
extern int buffcount;
extern int fildes;
extern float lowx;
extern float lowy;
extern float scalex;
extern float scaley;
extern struct sgttyb sarg;
E 1
