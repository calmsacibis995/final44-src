h54773
s 00002/00002/00081
d D 8.1 93/06/06 16:24:27 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00075
d D 4.3 91/04/18 18:07:55 bostic 3 2
c new copyright; att/bsd/shared
e
s 00003/00001/00073
d D 4.2 91/02/02 17:54:46 torek 2 1
c putw => putword; argument declarations (all from gcc -W)
e
s 00074/00000/00000
d D 4.1 82/12/18 15:11:09 sam 1 0
c date and time created 82/12/18 15:11:09 by sam
e
u
U
t
T
I 1
D 3
/*	%W%	%G%	*/
E 3
I 3
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */
E 3

#include <stdio.h>
#include <ctype.h>

#ifndef unix
#define SHIFT	5
#define TABSIZE (int)(400000/(1<<SHIFT))
int	*tab;	/*honeywell loader deficiency*/
#else
#define Tolower(c)	(isupper(c)?tolower(c):c) /* ugh!!! */
#define SHIFT	4
#define TABSIZE 25000	/*(int)(400000/(1<<shift))--pdp11 compiler deficiency*/
short	tab[TABSIZE];
#endif
long	p[] = {
	399871,
	399887,
	399899,
	399911,
	399913,
	399937,
	399941,
	399953,
	399979,
	399983,
	399989,
};
#define	NP	(sizeof(p)/sizeof(p[0]))
#define	NW	30

/*
* Hash table for spelling checker has n bits.
* Each word w is hashed by k different (modular) hash functions, hi.
* The bits hi(w), i=1..k, are set for words in the dictionary.
* Assuming independence, the probability that no word of a d-word
* dictionary sets a particular bit is given by the Poisson formula
* P = exp(-y)*y**0/0!, where y=d*k/n.
* The probability that a random string is recognized as a word is then
* (1-P)**k.  For given n and d this is minimum when y=log(2), P=1/2,
* whence one finds, for example, that a 25000-word dictionary in a
* 400000-bit table works best with k=11.
*/

long	pow2[NP][NW];

D 2
prime(argc, argv) register char **argv;
E 2
I 2
prime(argc, argv)
	int argc;
	register char **argv;
E 2
{
	int i, j;
	long h;
	register long *lp;

#ifndef unix
	if ((tab = (int *)calloc(sizeof(*tab), TABSIZE)) == NULL)
		return(0);
#endif
	if (argc > 1) {
		FILE *f;
		if ((f = fopen(argv[1], "ri")) == NULL)
			return(0);
		if (fread((char *)tab, sizeof(*tab), TABSIZE, f) != TABSIZE)
			return(0);
		fclose(f);
	}
	for (i=0; i<NP; i++) {
		h = *(lp = pow2[i]) = 1<<14;
		for (j=1; j<NW; j++)
			h = *++lp = (h<<7) % p[i];
	}
	return(1);
}

#define get(h)	(tab[h>>SHIFT]&(1<<((int)h&((1<<SHIFT)-1))))
#define set(h)	tab[h>>SHIFT] |= 1<<((int)h&((1<<SHIFT)-1))
E 1
