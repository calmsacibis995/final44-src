h11056
s 00005/00005/00047
d D 8.1 93/06/04 12:58:07 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00052/00000/00000
d D 5.1 92/06/02 13:38:45 bostic 1 0
c date and time created 92/06/02 13:38:45 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 2
char copyright[] =
"%Z% Copyright (c) 1992 The Regents of the University of California.\n\
 All rights reserved.\n";
E 2
I 2
static char copyright[] =
"%Z% Copyright (c) 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 2
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <stdio.h>

main()
{
	union { long long q; unsigned long v[2]; } a, b, q, r;
	char buf[300];
	extern long long __qdivrem(unsigned long long, unsigned long long,
	    unsigned long long *);

	for (;;) {
		printf("> ");
		if (fgets(buf, sizeof buf, stdin) == NULL)
			break;
		if (sscanf(buf, "%lu:%lu %lu:%lu",
			    &a.v[0], &a.v[1], &b.v[0], &b.v[1]) != 4 &&
		    sscanf(buf, "0x%lx:%lx 0x%lx:%lx",
			    &a.v[0], &a.v[1], &b.v[0], &b.v[1]) != 4) {
			printf("eh?\n");
			continue;
		}
		q.q = __qdivrem(a.q, b.q, &r.q);
		printf("%lx:%lx /%% %lx:%lx => q=%lx:%lx r=%lx:%lx\n",
		    a.v[0], a.v[1], b.v[0], b.v[1],
		    q.v[0], q.v[1], r.v[0], r.v[1]);
		printf("  = %lX%08lX / %lX%08lX => %lX%08lX\n\
  = %lX%08lX %% %lX%08lX => %lX%08lX\n",
		    a.v[0], a.v[1], b.v[0], b.v[1], q.v[0], q.v[1],
		    a.v[0], a.v[1], b.v[0], b.v[1], r.v[0], r.v[1]);
	}
	exit(0);
}
E 1
