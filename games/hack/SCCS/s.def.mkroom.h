h59043
s 00026/00000/00000
d D 5.1 90/05/02 08:39:20 bostic 1 0
c date and time created 90/05/02 08:39:20 by bostic
e
u
U
t
T
I 1
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* def.mkroom.h - version 1.0.3 */

struct mkroom {
	schar lx,hx,ly,hy;	/* usually xchar, but hx may be -1 */
	schar rtype,rlit,doorct,fdoor;
};

#define	MAXNROFROOMS	15
extern struct mkroom rooms[MAXNROFROOMS+1];

#define	DOORMAX	100
extern coord doors[DOORMAX];

/* various values of rtype */
/* 0: ordinary room; 8-15: various shops */
/* Note: some code assumes that >= 8 means shop, so be careful when adding
   new roomtypes */
#define	SWAMP	3
#define	VAULT	4
#define	BEEHIVE	5
#define	MORGUE	6
#define	ZOO	7
#define	SHOPBASE	8
#define	WANDSHOP	9
#define	GENERAL	15
E 1
