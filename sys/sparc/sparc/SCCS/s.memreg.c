h61488
s 00002/00002/00078
d D 8.1 93/06/11 15:17:09 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00005/00062
d D 7.4 93/04/20 23:36:56 torek 4 3
c ctlreg.h moves; give it a short external name
e
s 00005/00005/00062
d D 7.3 92/10/11 12:57:22 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00062
d D 7.2 92/07/21 16:54:37 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00062/00000/00000
d D 7.1 92/07/13 00:44:40 torek 1 0
c date and time created 92/07/13 00:44:40 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: memreg.c,v 1.4 92/06/17 05:22:17 torek Exp $ (LBL)
E 4
I 4
 * from: $Header: memreg.c,v 1.7 92/11/26 03:05:04 torek Exp $ (LBL)
E 4
 */

D 3
#include "sys/param.h"
#include "sys/device.h"
E 3
I 3
#include <sys/param.h>
#include <sys/device.h>
E 3

D 3
#include "machine/autoconf.h"
E 3
I 3
#include <machine/autoconf.h>
I 4
#include <machine/ctlreg.h>
E 4
E 3

D 3
#include "ctlreg.h"
#include "memreg.h"
E 3
I 3
D 4
#include <sparc/sparc/ctlreg.h>
E 4
#include <sparc/sparc/memreg.h>
E 3

I 4
static int memregmatch __P((struct device *, struct cfdata *, void *));
E 4
static void memregattach __P((struct device *, struct device *, void *));
struct cfdriver memregcd =
D 4
    { NULL, "memory-error", matchbyname, memregattach,
      DV_DULL, sizeof(struct device) };
E 4
I 4
    { 0, "memreg", memregmatch, memregattach, DV_DULL, sizeof(struct device) };

/*
 * The OPENPROM calls this "memory-error".
 */
static int
memregmatch(parent, cf, aux)
	struct device *parent;
	struct cfdata *cf;
	void *aux;
{

	return (strcmp("memory-error", ((struct romaux *)aux)->ra_name) == 0);
}
E 4

/* ARGSUSED */
static void
memregattach(parent, self, aux)
	struct device *parent, *self;
	void *aux;
{
	struct romaux *ra = aux;

	par_err_reg = ra->ra_vaddr ? (volatile int *)ra->ra_vaddr :
	    (volatile int *)mapiodev(ra->ra_paddr, sizeof(int));
	printf("\n");
}

/*
 * Synchronous and asynchronous memory error handler.
 * (This is the level 15 interrupt, which is not vectored.)
 * Should kill the process that got its bits clobbered,
 * and take the page out of the page pool, but for now...
 */
void
memerr(issync, ser, sva, aer, ava)
	int issync, ser, sva, aer, ava;
{

	printf("%ssync mem err: ser=%b sva=%x aer=%b ava=%x\n",
	    issync ? "" : "a", ser, SER_BITS, sva, aer & 0xff, AER_BITS, ava);
	if (par_err_reg)
		printf("parity error register = %b\n", *par_err_reg, PER_BITS);
#ifdef DEBUG
	callrom();
#else
	panic("memory error");		/* XXX */
#endif
}
E 1
