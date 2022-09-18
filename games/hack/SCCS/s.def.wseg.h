h31438
s 00013/00000/00000
d D 5.1 90/05/02 08:39:30 bostic 1 0
c date and time created 90/05/02 08:39:30 by bostic
e
u
U
t
T
I 1
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* def.wseg.h - version 1.0.2 */

#ifndef NOWORM
/* worm structure */
struct wseg {
	struct wseg *nseg;
	xchar wx,wy;
	unsigned wdispl:1;
};

#define newseg()	(struct wseg *) alloc(sizeof(struct wseg))
#endif NOWORM
E 1
