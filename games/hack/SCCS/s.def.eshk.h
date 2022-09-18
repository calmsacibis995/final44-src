h05595
s 00024/00000/00000
d D 5.1 90/05/02 08:39:14 bostic 1 0
c date and time created 90/05/02 08:39:14 by bostic
e
u
U
t
T
I 1
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* def.eshk.h - version 1.0.2 : added 'following' */

#define	BILLSZ	200
struct bill_x {
	unsigned bo_id;
	unsigned useup:1;
	unsigned bquan:7;
	unsigned price;		/* price per unit */
};

struct eshk {
	long int robbed;	/* amount stolen by most recent customer */
	boolean following;	/* following customer since he owes us sth */
	schar shoproom;		/* index in rooms; set by inshop() */
	coord shk;		/* usual position shopkeeper */
	coord shd;		/* position shop door */
	int shoplevel;		/* level of his shop */
	int billct;
	struct bill_x bill[BILLSZ];
	int visitct;		/* nr of visits by most recent customer */
	char customer[PL_NSIZ];	/* most recent customer */
	char shknam[PL_NSIZ];
};
E 1
