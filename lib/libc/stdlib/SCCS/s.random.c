h20418
s 00067/00030/00307
d D 8.2 95/05/19 13:26:04 mckusick 14 13
c update for speed (from jacob@l7indy2.gsfc.nasa.gov (Jack Rosenberg))
e
s 00002/00002/00335
d D 8.1 93/06/04 13:08:18 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00210/00230/00127
d D 5.9 91/02/23 10:47:29 bostic 12 11
c reformat to KNF
e
s 00004/00003/00353
d D 5.8 91/02/23 10:08:45 donn 11 10
c Changes for prototype declarations.
e
s 00001/00011/00355
d D 5.7 90/06/01 14:13:21 bostic 10 9
c new copyright notice
e
s 00002/00002/00364
d D 5.6 90/01/02 13:29:01 mckusick 9 8
c return null on error (4.3BSD/lib/28)
e
s 00015/00004/00351
d D 5.5 88/07/06 13:06:48 bostic 8 7
c written by Earl Cohen; add Berkeley specific copyright
e
s 00001/00000/00354
d D 5.4 88/04/24 17:10:37 bostic 7 6
c fix for ANSI C
e
s 00001/00001/00353
d D 5.3 87/04/06 11:52:48 bostic 6 5
c printf format/argument mismatch
e
s 00002/00002/00352
d D 5.2 86/03/09 19:53:29 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00008/00002/00346
d D 5.1 85/05/30 10:48:34 dist 4 3
c Add copyright
e
s 00001/00001/00347
d D 4.3 84/04/16 11:31:43 earl 3 2
c fixed serious initialization bug which screwed up default generation
e
s 00002/00002/00346
d D 4.2 83/01/02 16:12:27 sam 2 1
c stuff
e
s 00348/00000/00000
d D 4.1 82/11/22 14:56:13 mckusick 1 0
c date and time created 82/11/22 14:56:13 by mckusick
e
u
U
t
T
I 4
/*
D 13
 * Copyright (c) 1983 Regents of the University of California.
D 8
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 10
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 8
 */

E 4
I 1
D 2
/* Copyright (c) 1982 Regents of the University of California */

E 2
I 2
D 5
#ifndef lint
E 5
I 5
#if defined(LIBC_SCCS) && !defined(lint)
E 5
E 2
D 4
static char sccsid[] = "%W%	(Berkeley)	%E%";
I 2
#endif
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
D 8
#endif LIBC_SCCS and not lint
E 8
I 8
#endif /* LIBC_SCCS and not lint */
E 8
E 5
E 4
E 2

D 8
#include	<stdio.h>
E 8
I 8
#include <stdio.h>
I 11
#include <stdlib.h>
E 11
E 8

/*
 * random.c:
I 12
 *
E 12
 * An improved random number generation package.  In addition to the standard
 * rand()/srand() like interface, this package also has a special state info
 * interface.  The initstate() routine is called with a seed, an array of
D 12
 * bytes, and a count of how many bytes are being passed in; this array is then
 * initialized to contain information for random number generation with that
 * much state information.  Good sizes for the amount of state information are
 * 32, 64, 128, and 256 bytes.  The state can be switched by calling the
 * setstate() routine with the same array as was initiallized with initstate().
 * By default, the package runs with 128 bytes of state information and
 * generates far better random numbers than a linear congruential generator.
 * If the amount of state information is less than 32 bytes, a simple linear
 * congruential R.N.G. is used.
E 12
I 12
 * bytes, and a count of how many bytes are being passed in; this array is
 * then initialized to contain information for random number generation with
 * that much state information.  Good sizes for the amount of state
 * information are 32, 64, 128, and 256 bytes.  The state can be switched by
 * calling the setstate() routine with the same array as was initiallized
 * with initstate().  By default, the package runs with 128 bytes of state
 * information and generates far better random numbers than a linear
 * congruential generator.  If the amount of state information is less than
 * 32 bytes, a simple linear congruential R.N.G. is used.
 *
E 12
 * Internally, the state information is treated as an array of longs; the
 * zeroeth element of the array is the type of R.N.G. being used (small
 * integer); the remainder of the array is the state information for the
 * R.N.G.  Thus, 32 bytes of state information will give 7 longs worth of
D 12
 * state information, which will allow a degree seven polynomial.  (Note: the 
 * zeroeth word of state information also has some other information stored
 * in it -- see setstate() for details).
E 12
I 12
 * state information, which will allow a degree seven polynomial.  (Note:
 * the zeroeth word of state information also has some other information
 * stored in it -- see setstate() for details).
 * 
E 12
 * The random number generation technique is a linear feedback shift register
 * approach, employing trinomials (since there are fewer terms to sum up that
 * way).  In this approach, the least significant bit of all the numbers in
D 12
 * the state table will act as a linear feedback shift register, and will have
 * period 2^deg - 1 (where deg is the degree of the polynomial being used,
 * assuming that the polynomial is irreducible and primitive).  The higher
 * order bits will have longer periods, since their values are also influenced
 * by pseudo-random carries out of the lower bits.  The total period of the
 * generator is approximately deg*(2**deg - 1); thus doubling the amount of
 * state information has a vast influence on the period of the generator.
 * Note: the deg*(2**deg - 1) is an approximation only good for large deg,
 * when the period of the shift register is the dominant factor.  With deg
 * equal to seven, the period is actually much longer than the 7*(2**7 - 1)
 * predicted by this formula.
E 12
I 12
 * the state table will act as a linear feedback shift register, and will
 * have period 2^deg - 1 (where deg is the degree of the polynomial being
 * used, assuming that the polynomial is irreducible and primitive).  The
 * higher order bits will have longer periods, since their values are also
 * influenced by pseudo-random carries out of the lower bits.  The total
 * period of the generator is approximately deg*(2**deg - 1); thus doubling
 * the amount of state information has a vast influence on the period of the
 * generator.  Note: the deg*(2**deg - 1) is an approximation only good for
 * large deg, when the period of the shift register is the dominant factor.
 * With deg equal to seven, the period is actually much longer than the
 * 7*(2**7 - 1) predicted by this formula.
I 14
 *
 * Modified 28 December 1994 by Jacob S. Rosenberg.
 * The following changes have been made:
 * All references to the type u_int have been changed to unsigned long.
 * All references to type int have been changed to type long.  Other
 * cleanups have been made as well.  A warning for both initstate and
 * setstate has been inserted to the effect that on Sparc platforms
 * the 'arg_state' variable must be forced to begin on word boundaries.
 * This can be easily done by casting a long integer array to char *.
 * The overall logic has been left STRICTLY alone.  This software was
 * tested on both a VAX and Sun SpacsStation with exactly the same
 * results.  The new version and the original give IDENTICAL results.
 * The new version is somewhat faster than the original.  As the
 * documentation says:  "By default, the package runs with 128 bytes of
 * state information and generates far better random numbers than a linear
 * congruential generator.  If the amount of state information is less than
 * 32 bytes, a simple linear congruential R.N.G. is used."  For a buffer of
 * 128 bytes, this new version runs about 19 percent faster and for a 16
 * byte buffer it is about 5 percent faster.
E 14
E 12
 */

D 12


E 12
/*
 * For each of the currently supported random number generators, we have a
 * break value on the amount of state information (you need at least this
 * many bytes of state info to support this random number generator), a degree
 * for the polynomial (actually a trinomial) that the R.N.G. is based on, and
 * the separation between the two lower order coefficients of the trinomial.
 */
I 12
#define	TYPE_0		0		/* linear congruential */
#define	BREAK_0		8
#define	DEG_0		0
#define	SEP_0		0
E 12

D 12
#define		TYPE_0		0		/* linear congruential */
#define		BREAK_0		8
#define		DEG_0		0
#define		SEP_0		0
E 12
I 12
#define	TYPE_1		1		/* x**7 + x**3 + 1 */
#define	BREAK_1		32
#define	DEG_1		7
#define	SEP_1		3
E 12

D 12
#define		TYPE_1		1		/* x**7 + x**3 + 1 */
#define		BREAK_1		32
#define		DEG_1		7
#define		SEP_1		3
E 12
I 12
#define	TYPE_2		2		/* x**15 + x + 1 */
#define	BREAK_2		64
#define	DEG_2		15
#define	SEP_2		1
E 12

D 12
#define		TYPE_2		2		/* x**15 + x + 1 */
#define		BREAK_2		64
#define		DEG_2		15
#define		SEP_2		1
E 12
I 12
#define	TYPE_3		3		/* x**31 + x**3 + 1 */
#define	BREAK_3		128
#define	DEG_3		31
#define	SEP_3		3
E 12

D 12
#define		TYPE_3		3		/* x**31 + x**3 + 1 */
#define		BREAK_3		128
#define		DEG_3		31
#define		SEP_3		3
E 12
I 12
#define	TYPE_4		4		/* x**63 + x + 1 */
#define	BREAK_4		256
#define	DEG_4		63
#define	SEP_4		1
E 12

D 12
#define		TYPE_4		4		/* x**63 + x + 1 */
#define		BREAK_4		256
#define		DEG_4		63
#define		SEP_4		1


E 12
/*
D 12
 * Array versions of the above information to make code run faster -- relies
 * on fact that TYPE_i == i.
E 12
I 12
 * Array versions of the above information to make code run faster --
 * relies on fact that TYPE_i == i.
E 12
 */
I 12
#define	MAX_TYPES	5		/* max number of types above */
E 12

D 12
#define		MAX_TYPES	5		/* max number of types above */
E 12
I 12
D 14
static int degrees[MAX_TYPES] =	{ DEG_0, DEG_1, DEG_2, DEG_3, DEG_4 };
static int seps [MAX_TYPES] =	{ SEP_0, SEP_1, SEP_2, SEP_3, SEP_4 };
E 14
I 14
static long degrees[MAX_TYPES] =	{ DEG_0, DEG_1, DEG_2, DEG_3, DEG_4 };
static long seps [MAX_TYPES] =	{ SEP_0, SEP_1, SEP_2, SEP_3, SEP_4 };
E 14
E 12

D 12
static  int		degrees[ MAX_TYPES ]	= { DEG_0, DEG_1, DEG_2,
								DEG_3, DEG_4 };

static  int		seps[ MAX_TYPES ]	= { SEP_0, SEP_1, SEP_2,
								SEP_3, SEP_4 };



E 12
/*
D 12
 * Initially, everything is set up as if from :
 *		initstate( 1, &randtbl, 128 );
E 12
I 12
 * Initially, everything is set up as if from:
 *
 *	initstate(1, &randtbl, 128);
 *
E 12
 * Note that this initialization takes advantage of the fact that srandom()
 * advances the front and rear pointers 10*rand_deg times, and hence the
 * rear pointer which starts at 0 will also end up at zero; thus the zeroeth
 * element of the state information, which contains info about the current
 * position of the rear pointer is just
D 12
 *	MAX_TYPES*(rptr - state) + TYPE_3 == TYPE_3.
E 12
I 12
 *
 *	MAX_TYPES * (rptr - state) + TYPE_3 == TYPE_3.
E 12
 */

D 12
static  long		randtbl[ DEG_3 + 1 ]	= { TYPE_3,
			    0x9a319039, 0x32d9c024, 0x9b663182, 0x5da1f342, 
			    0xde3b81e0, 0xdf0a6fb5, 0xf103bc02, 0x48f340fb, 
			    0x7449e56b, 0xbeb1dbb0, 0xab5c5918, 0x946554fd, 
			    0x8c2e680f, 0xeb3d799f, 0xb11ee0b7, 0x2d436b86, 
			    0xda672e2a, 0x1588ca88, 0xe369735d, 0x904f35f7, 
			    0xd7158fd6, 0x6fa6f051, 0x616e6b96, 0xac94efdc, 
			    0x36413f93, 0xc622c298, 0xf5a42ab8, 0x8a88d77b, 
					0xf5ad9d0e, 0x8999220b, 0x27fb47b9 };
E 12
I 12
static long randtbl[DEG_3 + 1] = {
	TYPE_3,
	0x9a319039, 0x32d9c024, 0x9b663182, 0x5da1f342, 0xde3b81e0, 0xdf0a6fb5,
	0xf103bc02, 0x48f340fb, 0x7449e56b, 0xbeb1dbb0, 0xab5c5918, 0x946554fd,
	0x8c2e680f, 0xeb3d799f, 0xb11ee0b7, 0x2d436b86, 0xda672e2a, 0x1588ca88,
	0xe369735d, 0x904f35f7, 0xd7158fd6, 0x6fa6f051, 0x616e6b96, 0xac94efdc,
	0x36413f93, 0xc622c298, 0xf5a42ab8, 0x8a88d77b, 0xf5ad9d0e, 0x8999220b,
	0x27fb47b9,
};
E 12

/*
 * fptr and rptr are two pointers into the state info, a front and a rear
D 12
 * pointer.  These two pointers are always rand_sep places aparts, as they cycle
 * cyclically through the state information.  (Yes, this does mean we could get
 * away with just one pointer, but the code for random() is more efficient this
 * way).  The pointers are left positioned as they would be from the call
 *			initstate( 1, randtbl, 128 )
E 12
I 12
 * pointer.  These two pointers are always rand_sep places aparts, as they
 * cycle cyclically through the state information.  (Yes, this does mean we
 * could get away with just one pointer, but the code for random() is more
 * efficient this way).  The pointers are left positioned as they would be
 * from the call
 *
 *	initstate(1, randtbl, 128);
 *
E 12
 * (The position of the rear pointer, rptr, is really 0 (as explained above
 * in the initialization of randtbl) because the state table pointer is set
 * to point to randtbl[1] (as explained below).
 */
I 12
static long *fptr = &randtbl[SEP_3 + 1];
static long *rptr = &randtbl[1];
E 12

D 12
static  long		*fptr			= &randtbl[ SEP_3 + 1 ];
static  long		*rptr			= &randtbl[ 1 ];



E 12
/*
D 12
 * The following things are the pointer to the state information table,
 * the type of the current generator, the degree of the current polynomial
 * being used, and the separation between the two pointers.
 * Note that for efficiency of random(), we remember the first location of
 * the state information, not the zeroeth.  Hence it is valid to access
 * state[-1], which is used to store the type of the R.N.G.
 * Also, we remember the last location, since this is more efficient than
 * indexing every time to find the address of the last element to see if
 * the front and rear pointers have wrapped.
E 12
I 12
 * The following things are the pointer to the state information table, the
 * type of the current generator, the degree of the current polynomial being
 * used, and the separation between the two pointers.  Note that for efficiency
 * of random(), we remember the first location of the state information, not
 * the zeroeth.  Hence it is valid to access state[-1], which is used to
 * store the type of the R.N.G.  Also, we remember the last location, since
 * this is more efficient than indexing every time to find the address of
 * the last element to see if the front and rear pointers have wrapped.
E 12
 */
I 12
static long *state = &randtbl[1];
D 14
static int rand_type = TYPE_3;
static int rand_deg = DEG_3;
static int rand_sep = SEP_3;
E 14
I 14
static long rand_type = TYPE_3;
static long rand_deg = DEG_3;
static long rand_sep = SEP_3;
E 14
static long *end_ptr = &randtbl[DEG_3 + 1];
E 12

D 3
static  long		*state			= &randtbl[ -1 ];
E 3
I 3
D 12
static  long		*state			= &randtbl[ 1 ];
E 3

static  int		rand_type		= TYPE_3;
static  int		rand_deg		= DEG_3;
static  int		rand_sep		= SEP_3;

static  long		*end_ptr		= &randtbl[ DEG_3 + 1 ];



E 12
/*
 * srandom:
I 12
 *
E 12
 * Initialize the random number generator based on the given seed.  If the
 * type is the trivial no-state-information type, just remember the seed.
 * Otherwise, initializes state[] based on the given "seed" via a linear
 * congruential generator.  Then, the pointers are set to known locations
 * that are exactly rand_sep places apart.  Lastly, it cycles the state
 * information a given number of times to get rid of any initial dependencies
D 12
 * introduced by the L.C.R.N.G.
 * Note that the initialization of randtbl[] for default usage relies on
 * values produced by this routine.
E 12
I 12
 * introduced by the L.C.R.N.G.  Note that the initialization of randtbl[]
 * for default usage relies on values produced by this routine.
E 12
 */
D 12

E 12
I 11
void
E 11
D 12
srandom( x )

    unsigned		x;
E 12
I 12
srandom(x)
D 14
	u_int x;
E 14
I 14
	unsigned long x;
E 14
E 12
{
D 12
    	register  int		i, j;
E 12
I 12
D 14
	register int i, j;
E 14
I 14
	register long i;
E 14
E 12
I 7
D 11
	long random();
E 11
E 7

D 12
	if(  rand_type  ==  TYPE_0  )  {
	    state[ 0 ] = x;
E 12
I 12
	if (rand_type == TYPE_0)
		state[0] = x;
	else {
D 14
		j = 1;
E 14
		state[0] = x;
		for (i = 1; i < rand_deg; i++)
			state[i] = 1103515245 * state[i - 1] + 12345;
		fptr = &state[rand_sep];
		rptr = &state[0];
		for (i = 0; i < 10 * rand_deg; i++)
			(void)random();
E 12
	}
D 12
	else  {
	    j = 1;
	    state[ 0 ] = x;
	    for( i = 1; i < rand_deg; i++ )  {
		state[i] = 1103515245*state[i - 1] + 12345;
	    }
	    fptr = &state[ rand_sep ];
	    rptr = &state[ 0 ];
D 11
	    for( i = 0; i < 10*rand_deg; i++ )  random();
E 11
I 11
	    for( i = 0; i < 10*rand_deg; i++ )
		(void) random();
E 11
	}
E 12
}

D 12


E 12
/*
 * initstate:
D 12
 * Initialize the state information in the given array of n bytes for
 * future random number generation.  Based on the number of bytes we
 * are given, and the break values for the different R.N.G.'s, we choose
 * the best (largest) one we can and set things up for it.  srandom() is
 * then called to initialize the state information.
E 12
I 12
 *
 * Initialize the state information in the given array of n bytes for future
 * random number generation.  Based on the number of bytes we are given, and
 * the break values for the different R.N.G.'s, we choose the best (largest)
 * one we can and set things up for it.  srandom() is then called to
 * initialize the state information.
 * 
E 12
 * Note that on return from srandom(), we set state[-1] to be the type
 * multiplexed with the current value of the rear pointer; this is so
D 12
 * successive calls to initstate() won't lose this information and will
 * be able to restart with setstate().
E 12
I 12
 * successive calls to initstate() won't lose this information and will be
 * able to restart with setstate().
 * 
E 12
 * Note: the first thing we do is save the current state, if any, just like
 * setstate() so that it doesn't matter when initstate is called.
I 12
 *
E 12
 * Returns a pointer to the old state.
I 14
 *
 * Note: The Sparc platform requires that arg_state begin on a long
 * word boundary; otherwise a bus error will occur. Even so, lint will
 * complain about mis-alignment, but you should disregard these messages.
E 14
 */
D 12

char  *
initstate( seed, arg_state, n )

    unsigned		seed;			/* seed for R. N. G. */
    char		*arg_state;		/* pointer to state array */
    int			n;			/* # bytes of state info */
E 12
I 12
char *
initstate(seed, arg_state, n)
D 14
	u_int seed;			/* seed for R.N.G. */
E 14
I 14
	unsigned long seed;		/* seed for R.N.G. */
E 14
	char *arg_state;		/* pointer to state array */
D 14
	int n;				/* # bytes of state info */
E 14
I 14
	long n;				/* # bytes of state info */
E 14
E 12
{
D 12
	register  char		*ostate		= (char *)( &state[ -1 ] );
E 12
I 12
	register char *ostate = (char *)(&state[-1]);
I 14
	register long *long_arg_state = (long *) arg_state;
E 14
E 12

D 12
	if(  rand_type  ==  TYPE_0  )  state[ -1 ] = rand_type;
	else  state[ -1 ] = MAX_TYPES*(rptr - state) + rand_type;
	if(  n  <  BREAK_1  )  {
	    if(  n  <  BREAK_0  )  {
D 6
		fprintf( stderr, "initstate: not enough state (%d bytes) with which to do jack; ignored.\n" );
E 6
I 6
D 9
		fprintf( stderr, "initstate: not enough state (%d bytes) with which to do jack; ignored.\n", n );
E 6
		return;
E 9
I 9
		fprintf( stderr, "initstate: not enough state (%d bytes); ignored.\n", n );
		return 0;
E 9
	    }
	    rand_type = TYPE_0;
	    rand_deg = DEG_0;
	    rand_sep = SEP_0;
E 12
I 12
	if (rand_type == TYPE_0)
		state[-1] = rand_type;
	else
		state[-1] = MAX_TYPES * (rptr - state) + rand_type;
	if (n < BREAK_0) {
		(void)fprintf(stderr,
D 14
		    "random: not enough state (%d bytes); ignored.\n", n);
E 14
I 14
		    "random: not enough state (%ld bytes); ignored.\n", n);
E 14
		return(0);
E 12
	}
D 12
	else  {
	    if(  n  <  BREAK_2  )  {
E 12
I 12
	if (n < BREAK_1) {
		rand_type = TYPE_0;
		rand_deg = DEG_0;
		rand_sep = SEP_0;
	} else if (n < BREAK_2) {
E 12
		rand_type = TYPE_1;
		rand_deg = DEG_1;
		rand_sep = SEP_1;
D 12
	    }
	    else  {
		if(  n  <  BREAK_3  )  {
		    rand_type = TYPE_2;
		    rand_deg = DEG_2;
		    rand_sep = SEP_2;
		}
		else  {
		    if(  n  <  BREAK_4  )  {
			rand_type = TYPE_3;
			rand_deg = DEG_3;
			rand_sep = SEP_3;
		    }
		    else  {
			rand_type = TYPE_4;
			rand_deg = DEG_4;
			rand_sep = SEP_4;
		    }
		}
	    }
E 12
I 12
	} else if (n < BREAK_3) {
		rand_type = TYPE_2;
		rand_deg = DEG_2;
		rand_sep = SEP_2;
	} else if (n < BREAK_4) {
		rand_type = TYPE_3;
		rand_deg = DEG_3;
		rand_sep = SEP_3;
	} else {
		rand_type = TYPE_4;
		rand_deg = DEG_4;
		rand_sep = SEP_4;
E 12
	}
D 12
	state = &(  ( (long *)arg_state )[1]  );	/* first location */
	end_ptr = &state[ rand_deg ];	/* must set end_ptr before srandom */
	srandom( seed );
	if(  rand_type  ==  TYPE_0  )  state[ -1 ] = rand_type;
	else  state[ -1 ] = MAX_TYPES*(rptr - state) + rand_type;
	return( ostate );
E 12
I 12
D 14
	state = &(((long *)arg_state)[1]);	/* first location */
E 14
I 14
	state = (long *) (long_arg_state + 1); /* first location */
E 14
	end_ptr = &state[rand_deg];	/* must set end_ptr before srandom */
	srandom(seed);
	if (rand_type == TYPE_0)
D 14
		state[-1] = rand_type;
E 14
I 14
		long_arg_state[0] = rand_type;
E 14
	else
D 14
		state[-1] = MAX_TYPES*(rptr - state) + rand_type;
E 14
I 14
		long_arg_state[0] = MAX_TYPES * (rptr - state) + rand_type;
E 14
	return(ostate);
E 12
}

D 12


E 12
/*
 * setstate:
I 12
 *
E 12
 * Restore the state from the given state array.
I 12
 *
E 12
 * Note: it is important that we also remember the locations of the pointers
 * in the current state information, and restore the locations of the pointers
 * from the old state information.  This is done by multiplexing the pointer
 * location into the zeroeth word of the state information.
I 12
 *
E 12
 * Note that due to the order in which things are done, it is OK to call
 * setstate() with the same state as the current state.
I 12
 *
E 12
 * Returns a pointer to the old state information.
I 14
 *
 * Note: The Sparc platform requires that arg_state begin on a long
 * word boundary; otherwise a bus error will occur. Even so, lint will
 * complain about mis-alignment, but you should disregard these messages.
E 14
 */
D 12

char  *
setstate( arg_state )

    char		*arg_state;
E 12
I 12
char *
setstate(arg_state)
D 14
	char *arg_state;
E 14
I 14
	char *arg_state;		/* pointer to state array */
E 14
E 12
{
D 12
	register  long		*new_state	= (long *)arg_state;
	register  int		type		= new_state[0]%MAX_TYPES;
	register  int		rear		= new_state[0]/MAX_TYPES;
	char			*ostate		= (char *)( &state[ -1 ] );
E 12
I 12
D 14
	register long *new_state = (long *)arg_state;
	register int type = new_state[0] % MAX_TYPES;
	register int rear = new_state[0] / MAX_TYPES;
E 14
I 14
	register long *new_state = (long *) arg_state;
	register long type = new_state[0] % MAX_TYPES;
	register long rear = new_state[0] / MAX_TYPES;
E 14
	char *ostate = (char *)(&state[-1]);
E 12

D 12
	if(  rand_type  ==  TYPE_0  )  state[ -1 ] = rand_type;
	else  state[ -1 ] = MAX_TYPES*(rptr - state) + rand_type;
	switch(  type  )  {
	    case  TYPE_0:
	    case  TYPE_1:
	    case  TYPE_2:
	    case  TYPE_3:
	    case  TYPE_4:
E 12
I 12
	if (rand_type == TYPE_0)
		state[-1] = rand_type;
	else
		state[-1] = MAX_TYPES * (rptr - state) + rand_type;
	switch(type) {
	case TYPE_0:
	case TYPE_1:
	case TYPE_2:
	case TYPE_3:
	case TYPE_4:
E 12
		rand_type = type;
D 12
		rand_deg = degrees[ type ];
		rand_sep = seps[ type ];
E 12
I 12
		rand_deg = degrees[type];
		rand_sep = seps[type];
E 12
		break;
D 12

	    default:
		fprintf( stderr, "setstate: state info has been munged; not changed.\n" );
E 12
I 12
	default:
		(void)fprintf(stderr,
		    "random: state info corrupted; not changed.\n");
E 12
	}
D 12
	state = &new_state[ 1 ];
	if(  rand_type  !=  TYPE_0  )  {
	    rptr = &state[ rear ];
	    fptr = &state[ (rear + rand_sep)%rand_deg ];
E 12
I 12
D 14
	state = &new_state[1];
E 14
I 14
	state = (long *) (new_state + 1);
E 14
	if (rand_type != TYPE_0) {
		rptr = &state[rear];
		fptr = &state[(rear + rand_sep) % rand_deg];
E 12
	}
D 12
	end_ptr = &state[ rand_deg ];		/* set end_ptr too */
	return( ostate );
E 12
I 12
	end_ptr = &state[rand_deg];		/* set end_ptr too */
	return(ostate);
E 12
}

D 12


E 12
/*
 * random:
I 12
 *
E 12
 * If we are using the trivial TYPE_0 R.N.G., just do the old linear
D 12
 * congruential bit.  Otherwise, we do our fancy trinomial stuff, which is the
 * same in all ther other cases due to all the global variables that have been
 * set up.  The basic operation is to add the number at the rear pointer into
 * the one at the front pointer.  Then both pointers are advanced to the next
 * location cyclically in the table.  The value returned is the sum generated,
 * reduced to 31 bits by throwing away the "least random" low bit.
E 12
I 12
 * congruential bit.  Otherwise, we do our fancy trinomial stuff, which is
 * the same in all the other cases due to all the global variables that have
 * been set up.  The basic operation is to add the number at the rear pointer
 * into the one at the front pointer.  Then both pointers are advanced to
 * the next location cyclically in the table.  The value returned is the sum
 * generated, reduced to 31 bits by throwing away the "least random" low bit.
 *
E 12
 * Note: the code takes advantage of the fact that both the front and
 * rear pointers can't wrap on the same call by not testing the rear
 * pointer if the front one has wrapped.
I 12
 *
E 12
 * Returns a 31-bit random number.
 */
D 12

E 12
long
random()
{
D 12
	long		i;
	
	if(  rand_type  ==  TYPE_0  )  {
	    i = state[0] = ( state[0]*1103515245 + 12345 )&0x7fffffff;
E 12
I 12
D 14
	long i;
E 14
I 14
	register long i;
	register long *f, *r;
E 14

D 14
	if (rand_type == TYPE_0)
		i = state[0] = (state[0] * 1103515245 + 12345) & 0x7fffffff;
	else {
		*fptr += *rptr;
		i = (*fptr >> 1) & 0x7fffffff;	/* chucking least random bit */
		if (++fptr >= end_ptr) {
			fptr = state;
			++rptr;
		} else if (++rptr >= end_ptr)
			rptr = state;
E 14
I 14
	if (rand_type == TYPE_0) {
		i = state[0];
		state[0] = i = (i * 1103515245 + 12345) & 0x7fffffff;
	} else {
		/*
		 * Use local variables rather than static variables for speed.
		 */
		f = fptr; r = rptr;
		*f += *r;
		i = (*f >> 1) & 0x7fffffff;	/* chucking least random bit */
		if (++f >= end_ptr) {
			f = state;
			++r;
		}
		else if (++r >= end_ptr) {
			r = state;
		}

		fptr = f; rptr = r;
E 14
E 12
	}
D 12
	else  {
	    *fptr += *rptr;
	    i = (*fptr >> 1)&0x7fffffff;	/* chucking least random bit */
	    if(  ++fptr  >=  end_ptr  )  {
		fptr = state;
		++rptr;
	    }
	    else  {
		if(  ++rptr  >=  end_ptr  )  rptr = state;
	    }
	}
	return( i );
E 12
I 12
	return(i);
E 12
}
D 11

E 11
E 1
