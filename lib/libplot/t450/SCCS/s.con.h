h31332
s 00002/00002/00035
d D 8.1 93/06/04 18:18:02 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00002/00029
d D 4.2 91/04/22 16:08:07 bostic 2 1
c new copyright; att/bsd/shared
e
s 00031/00000/00000
d D 4.1 83/06/27 14:22:55 sam 1 0
c date and time created 83/06/27 14:22:55 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
/*-
D 3
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */
E 2

D 2
#
E 2
#include <sgtty.h>
/* gsi plotting output routines */
# define DOWN 012
# define UP 013
# define LEFT 010
# define RIGHT 040
# define BEL 007
# define ESC 033
# define ACK 006
#define PLOTIN 063
#define PLOTOUT 064
# define CR 015
# define FF 014
# define VERTRESP 48
# define HORZRESP 60.
# define VERTRES 8.
# define HORZRES 6.
/* down is line feed, up is reverse line feed,
   left is backspace, right is space.  48 points per inch
   vertically, 60 horizontally */

extern int xnow, ynow;
extern int OUTF;
extern struct sgttyb ITTY, PTTY;
extern float HEIGHT, WIDTH, OFFSET;
extern int xscale, xoffset, yscale;
extern float botx, boty, obotx, oboty, scalex,scaley;

E 1
