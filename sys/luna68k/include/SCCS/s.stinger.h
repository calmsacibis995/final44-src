h39381
s 00002/00002/00025
d D 8.1 93/06/10 22:22:26 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00011/00020
d D 7.3 93/01/18 19:11:58 akito 3 2
c add some member to struct KernInter
e
s 00002/00002/00029
d D 7.2 92/10/11 10:57:54 bostic 2 1
c make kernel includes standard
e
s 00031/00000/00000
d D 7.1 92/06/15 06:28:29 fujita 1 0
c date and time created 92/06/15 06:28:29 by fujita
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * stinger.h -- Stinger Kernel Interface Definitions
D 3
 * by A.Fujita, MAR-14-1992
 *
 * This file should be remade.
E 3
I 3
 *   remade by A.Fujita, JAN-12-1993
E 3
 */

D 2
#include "rdvar.h"
#include "memory.h"
E 2
I 2
D 3
#include <machine/rdvar.h>
#include <machine/memory.h>
E 2

E 3
struct KernInter {
D 3
	caddr_t	  maxaddr;
	struct prgmem prg;
	int	  argc;
	char	**argv;
	struct rd_partition *rd;
E 3
I 3
	caddr_t	maxaddr;
	u_int	dipsw;
	int	plane;
E 3
};

I 3
extern struct KernInter KernInter;

#define	KIFF_DIPSW_NOBM		0x0002		/* not use bitmap display as console */
E 3
E 1
