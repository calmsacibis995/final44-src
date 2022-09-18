h45081
s 00012/00000/00000
d D 5.1 90/05/02 08:39:12 bostic 1 0
c date and time created 90/05/02 08:39:12 by bostic
e
u
U
t
T
I 1
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* def.edog.h - version 1.0.2 */

struct edog {
	long hungrytime;	/* at this time dog gets hungry */
	long eattime;		/* dog is eating */
	long droptime;		/* moment dog dropped object */
	unsigned dropdist;		/* dist of drpped obj from @ */
	unsigned apport;		/* amount of training */
	long whistletime;		/* last time he whistled */
};
#define	EDOG(mp)	((struct edog *)(&(mp->mextra[0])))
E 1
