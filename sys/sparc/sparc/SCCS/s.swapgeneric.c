h29120
s 00009/00002/00021
d D 8.2 94/03/21 15:12:41 bostic 5 4
c add a copyright notice
e
s 00000/00000/00023
d D 8.1 93/07/19 18:33:30 mckusick 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00009/00002/00014
d D 7.2 93/07/19 18:19:17 torek 3 1
c add a full complement of sd disks so that genvmunix will boot without -a
e
s 00000/00000/00016
d R 8.1 93/06/11 15:18:19 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00016/00000/00000
d D 7.1 93/04/20 23:42:06 torek 1 0
c date and time created 93/04/20 23:42:06 by torek
e
u
U
t
T
I 1
D 5
/*
D 3
 * dummy swapgeneric.c: not used in new config system.
E 3
I 3
 * fake swapgeneric.c -- should do this differently.
E 5
I 5
/*-
 * Copyright (c) 1994
 *	The Regents of the University of California.  All rights reserved.
E 5
E 3
 *
I 5
 * %sccs.include.redist.c%
 *
E 5
 *	%W% (Berkeley) %G%
I 5
 */

/*
 * fake swapgeneric.c -- should do this differently.
E 5
 */

#include <sys/param.h>
#include <sys/conf.h>

dev_t	rootdev = NODEV;
dev_t	dumpdev = NODEV;

struct	swdevt swdevt[] = {
D 3
	{ NODEV, 0, 0 },
E 3
I 3
	{ makedev(7, 1), 0, 0 },	/* sd0b */
	{ makedev(7, 9), 0, 0 },	/* sd1b */
	{ makedev(7, 17), 0, 0 },	/* sd2b */
	{ makedev(7, 25), 0, 0 },	/* sd3b */
	{ makedev(7, 33), 0, 0 },	/* sd4b */
	{ makedev(7, 41), 0, 0 },	/* sd5b */
	{ makedev(7, 49), 0, 0 },	/* sd6b */
	{ makedev(7, 57), 0, 0 },	/* sd7b */
E 3
	{ NODEV, 0, 0 }
};
E 1
