h31266
s 00012/00000/00000
d D 5.1 90/05/02 08:39:19 bostic 1 0
c date and time created 90/05/02 08:39:19 by bostic
e
u
U
t
T
I 1
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* def.gold.h - version 1.0.2 */

struct gold {
	struct gold *ngold;
	xchar gx,gy;
	long amount;
};

extern struct gold *fgold;
struct gold *g_at();
#define newgold()	(struct gold *) alloc(sizeof(struct gold))
E 1
