h06310
s 00002/00002/00112
d D 8.1 93/05/31 17:47:29 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00113
d D 5.3 90/06/01 13:18:16 bostic 3 2
c new copyright notice
e
s 00032/00000/00092
d D 5.2 89/02/07 17:13:08 bostic 2 1
c add Berkeley copyright notice; add Tim's copyright notice to random.c
e
s 00092/00000/00000
d D 5.1 87/11/25 15:24:53 bostic 1 0
c from Tim Stoehr
e
u
U
t
T
I 2
/*
D 4
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Timothy C. Stoehr.
 *
D 3
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

E 2
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
I 2

/*
 * random.c
 *
 * This source herein may be modified and/or distributed by anybody who
 * so desires, with the following restrictions:
 *    1.)  No portion of this notice shall be removed.
 *    2.)  Credit shall not be taken for the creation of this source.
 *    3.)  This code is not to be traded, sold, or used for personal
 *         gain or profit.
 *
 */
E 2

static long rntb[32] = {
	         3, 0x9a319039, 0x32d9c024, 0x9b663182, 0x5da1f342, 
	0xde3b81e0, 0xdf0a6fb5, 0xf103bc02, 0x48f340fb, 0x7449e56b,
	0xbeb1dbb0, 0xab5c5918, 0x946554fd, 0x8c2e680f, 0xeb3d799f,
	0xb11ee0b7, 0x2d436b86, 0xda672e2a, 0x1588ca88, 0xe369735d,
	0x904f35f7, 0xd7158fd6, 0x6fa6f051, 0x616e6b96, 0xac94efdc, 
	0x36413f93, 0xc622c298, 0xf5a42ab8, 0x8a88d77b, 0xf5ad9d0e,
	0x8999220b, 0x27fb47b9
};

static long *fptr = &rntb[4];
static long *rptr = &rntb[1];
static long *state = &rntb[1];
static int rand_type = 3;
static int rand_deg = 31;
static int rand_sep = 3;
static long *end_ptr = &rntb[32];

srrandom(x)
int x;
{
	register int i;
	long rrandom();

	state[0] = (long) x;
	if (rand_type != 0) {
		for (i = 1; i < rand_deg; i++) {
			state[i] = 1103515245 * state[i - 1] + 12345;
		}
		fptr = &state[rand_sep];
		rptr = &state[0];
		for (i = 0; i < 10 * rand_deg; i++) {
			(void) rrandom();
		}
	}
}

long
rrandom()
{
	long i;
	
	if (rand_type == 0) {
		i = state[0] = (state[0]*1103515245 + 12345) & 0x7fffffff;
	} else {
		*fptr += *rptr;
		i = (*fptr >> 1) & 0x7fffffff;
		if (++fptr >= end_ptr) {
			fptr = state;
			++rptr;
		} else {
			if (++rptr >= end_ptr) {
				rptr = state;
			}
		}
	}
	return(i);
}

get_rand(x, y)
register int x, y;
{
	register int r, t;
	long lr;

	if (x > y) {
		t = y;
		y = x;
		x = t;
	}
	lr = rrandom();
	lr &= (long) 0x00003fff;
	r = (int) lr;
	r = (r % ((y - x) + 1)) + x;
	return(r);
}

rand_percent(percentage)
register int percentage;
{
	return(get_rand(1, 100) <= percentage);
}

coin_toss()
{

	return(((rrandom() & 01) ? 1 : 0));
}
E 1
