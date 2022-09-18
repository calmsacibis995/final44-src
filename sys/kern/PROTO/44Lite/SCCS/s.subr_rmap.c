h38093
s 00025/00032/00030
d D 8.1 94/01/21 18:46:08 mckusick 3 2
c update for 4.4BSD-Lite
e
s 00000/00034/00062
d D 1.2 91/06/28 15:47:08 karels 2 1
c not so verbose about the "trade secrets"
e
s 00096/00000/00000
d D 1.1 91/05/11 15:31:09 mckusick 1 0
c date and time created 91/05/11 15:31:09 by mckusick
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.
E 3
I 3
/*-
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 3
 *
 * %sccs.include.redist.c%
 *
D 3
 *	from: @(#)subr_rmap.c	7.9 (Berkeley) 5/11/91
E 3
I 3
 *	from: @(#)subr_rmap.c	8.1 (Berkeley) 6/10/93
E 3
 */

D 3
#include "param.h"
#include "systm.h"
#include "map.h"
#include "dmap.h"		/* XXX */
#include "proc.h"
#include "kernel.h"
E 3
I 3
#include <sys/param.h>
#include <sys/map.h>
#include <sys/proc.h>
E 3

D 3
/*
 * Resource map handling routines.
D 2
 *
 * A resource map is an array of structures each
 * of which describes a segment of the address space of an available
 * resource.  The segments are described by their base address and
 * length, and sorted in address order.  Each resource map has a fixed
 * maximum number of segments allowed.  Resources are allocated
 * by taking part or all of one of the segments of the map.
 *
 * Returning of resources will require another segment if
 * the returned resources are not adjacent in the address
 * space to an existing segment.  If the return of a segment
 * would require a slot which is not available, then one of
 * the resource map segments is discarded after a warning is printed.
 * Returning of resources may also cause the map to collapse
 * by coalescing two existing segments and the returned space
 * into a single segment.  In this case the resource map is
 * made smaller by copying together to fill the resultant gap.
 *
 * N.B.: the current implementation uses a dense array and does
 * not admit the value ``0'' as a legal address, since that is used
 * as a delimiter.
E 2
 */

/*
 * Initialize map mp to have (mapsize-2) segments
 * and to be called ``name'', which we print if
 * the slots become so fragmented that we lose space.
 * The map itself is initialized with size elements free
 * starting at addr.
 */
rminit(mp, size, addr, name, mapsize)
	register struct map *mp;
	long size, addr;
	char *name;
	int mapsize;
E 3
I 3
void
rminit(a1, a2, a3, a4, a5)
	struct map *a1;
	long a2, a3;
	char *a4;
	int a5;
E 3
{

	/*
	 * Body deleted.
	 */
	return;
}

D 2
/*
 * A piece of memory of at least size units is allocated from the
 * specified map using a first-fit algorithm. It returns the starting
 * address of the allocated space.
 *
 * This routine knows about and handles the interleaving of the swapmap.
 */
E 2
long
D 3
rmalloc(mp, size)
	register struct map *mp;
	long size;
E 3
I 3
rmalloc(a1, a2)
	struct map *a1;
	long a2;
E 3
{

	/*
	 * Body deleted.
	 */
	return (0);
}

D 2
/*
 * The previously allocated space at addr of size units is freed
 * into the specified map. This routine is responsible for sorting
 * the frred space into the correct location in the map, and coalescing
 * it with free space on either side if they adjoin.
 */
E 2
D 3
rmfree(mp, size, addr)
	struct map *mp;
	long size, addr;
E 3
I 3
void
rmfree(a1, a2, a3)
	struct map *a1;
	long a2, a3;
E 3
{

	/*
	 * Body deleted.
	 */
	return;
}
E 1
