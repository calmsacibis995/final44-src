h33967
s 00002/00002/00032
d D 8.1 93/06/06 16:22:56 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00000/00000
d D 5.1 93/06/01 16:44:48 bostic 1 0
c date and time created 93/06/01 16:44:48 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Peter McIlroy.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define POW 20			/* exponent for buffer size */
#define BUFSIZE (1 << POW)
#define MAXNUM (BUFSIZE/10)	/* lowish guess at average record size */
#define BUFFEND (EOF-2)
#define MAXFCT 1000
#define MAXLLEN ((1 << min(POW-4, 16)) - 14)

extern u_char **keylist, **l2buf, *buffer, *linebuf;

/* temp files in the stack have a file descriptor, a largest bin (maxb)
 * which becomes the last non-empty bin (lastb) when the actual largest
 * bin is smaller than max(half the total file, BUFSIZE)
 * Max_o is the offset of maxb so it can be sought after the other bins
 * are sorted.
*/
struct tempfile {
	FILE *fd;
	u_char maxb;
	u_char lastb;
	long max_o;
};
extern struct tempfile fstack[MAXFCT];
E 1
