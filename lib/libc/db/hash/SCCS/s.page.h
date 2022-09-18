h14348
s 00002/00002/00064
d D 8.1 93/06/06 23:04:22 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00065
d D 5.3 93/06/06 22:55:30 bostic 4 2
c The short at page[2] contains the flag value that identifies
c long keys, long data or overflow pages, not page[1].
e
s 00002/00002/00064
d R 8.1 93/06/04 15:22:22 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00027/00027/00039
d D 5.2 91/09/04 12:56:45 bostic 2 1
c Rev #2.  ANSI/POSIX and reformatting, a few bug fixes thrown in
e
s 00066/00000/00000
d D 5.1 91/02/12 20:28:10 bostic 1 0
c date and time created 91/02/12 20:28:10 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Margo Seltzer.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
D 2
    Definitions for hashing page file format.
*/
extern	HTAB	*hashp;
E 2
I 2
 * Definitions for hashing page file format.
 */

E 2
/*
 * routines dealing with a data page
 *
 * page format:
 *	+------------------------------+
 * p	| n | keyoff | datoff | keyoff |
 * 	+------------+--------+--------+
 *	| datoff | free  |  ptr  | --> |
 *	+--------+---------------------+
 *	|	 F R E E A R E A       |
 *	+--------------+---------------+
 *	|  <---- - - - | data          |
 *	+--------+-----+----+----------+
 *	|  key   | data     | key      |
 *	+--------+----------+----------+
 *
 * Pointer to the free space is always:  p[p[0] + 2]
 * Amount of free space on the page is:  p[p[0] + 1]
 */

/*
D 2
    How many bytes required for this pair?
    2 shorts in the table at the top of the page +
    room for the key and room for the data
E 2
I 2
 * How many bytes required for this pair?
 *	2 shorts in the table at the top of the page + room for the
 *	key and room for the data
 *
 * We prohibit entering a pair on a page unless there is also room to append
 * an overflow page. The reason for this it that you can get in a situation
 * where a single key/data pair fits on a page, but you can't append an
 * overflow page and later you'd have to split the key/data and handle like
 * a big pair.
 * You might as well do this up front.
 */
E 2

D 2
    We prohibit entering a pair on a page unless there is also
    room to append an overflow page. The reason for this it that
    you can get in a situation where a single key/data pair fits
    on a page, but you can't append an overflow page and later
    you'd have to split the key/data and handle like a big pair.
    You might as well do this up front.

*/
#define	PAIRSIZE(K,D)	(2*sizeof(u_short) + K->size + D->size)
E 2
I 2
#define	PAIRSIZE(K,D)	(2*sizeof(u_short) + (K)->size + (D)->size)
E 2
#define BIGOVERHEAD	(4*sizeof(u_short))
D 2
#define KEYSIZE(K)	(4*sizeof(u_short) + K->size);
E 2
I 2
#define KEYSIZE(K)	(4*sizeof(u_short) + (K)->size);
E 2
#define OVFLSIZE	(2*sizeof(u_short))
D 2
#define FREESPACE(P)	(P[P[0]+1])
#define	OFFSET(P)	(P[P[0]+2])
#define PAIRFITS(P,K,D)	((P[1] >= REAL_KEY) && \
			 (PAIRSIZE(K,D) + OVFLSIZE) <= FREESPACE(P))
#define PAGE_META(N)	((N+3) * sizeof(u_short))
E 2
I 2
#define FREESPACE(P)	((P)[(P)[0]+1])
#define	OFFSET(P)	((P)[(P)[0]+2])
#define PAIRFITS(P,K,D) \
D 4
	(((P)[1] >= REAL_KEY) && \
E 4
I 4
	(((P)[2] >= REAL_KEY) && \
E 4
	    (PAIRSIZE((K),(D)) + OVFLSIZE) <= FREESPACE((P)))
#define PAGE_META(N)	(((N)+3) * sizeof(u_short))
E 2

typedef struct {
D 2
    BUFHEAD	*newp;
    BUFHEAD	*oldp;
    BUFHEAD	*nextp;
    u_short	next_addr;
} SPLIT_RETURN;

E 2
I 2
	BUFHEAD *newp;
	BUFHEAD *oldp;
	BUFHEAD *nextp;
	u_short next_addr;
}       SPLIT_RETURN;
E 2
E 1
