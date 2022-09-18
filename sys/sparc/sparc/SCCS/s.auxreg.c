h56830
s 00002/00002/00082
d D 8.1 93/06/11 15:15:58 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00005/00066
d D 7.4 93/04/20 21:11:05 torek 5 3
c update from elf: use LED_FLIP; give it a short external name
e
s 00017/00004/00067
d R 7.4 93/04/20 21:09:49 torek 4 3
c update from elf: use LED_FLIP; give it a short name
e
s 00006/00006/00065
d D 7.3 92/10/11 12:57:04 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00066
d D 7.2 92/07/21 16:54:18 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00066/00000/00000
d D 7.1 92/07/13 00:44:28 torek 1 0
c date and time created 92/07/13 00:44:28 by torek
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 5
 *	California, Lawrence Berkeley Laboratories.
E 5
I 5
 *	California, Lawrence Berkeley Laboratory.
E 5
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 5
 * from: $Header: auxreg.c,v 1.7 92/06/17 05:21:54 torek Exp $ (LBL)
E 5
I 5
 * from: $Header: auxreg.c,v 1.11 92/11/26 03:04:44 torek Exp $ (LBL)
E 5
 */

D 3
#include "sys/param.h"
#include "sys/device.h"
#include "sys/kernel.h"
E 3
I 3
#include <sys/param.h>
#include <sys/device.h>
#include <sys/kernel.h>
E 3

D 3
#include "machine/autoconf.h"
E 3
I 3
#include <machine/autoconf.h>
E 3

D 3
#include "vaddrs.h"
#include "auxreg.h"
E 3
I 3
#include <sparc/sparc/vaddrs.h>
#include <sparc/sparc/auxreg.h>
E 3

I 5
static int auxregmatch __P((struct device *, struct cfdata *, void *));
E 5
static void auxregattach __P((struct device *, struct device *, void *));
struct cfdriver auxregcd =
D 5
    { NULL, "auxiliary-io", matchbyname, auxregattach,
      DV_DULL, sizeof(struct device) };
E 5
I 5
    { 0, "auxreg", auxregmatch, auxregattach, DV_DULL, sizeof(struct device) };
E 5

#ifdef BLINK
static int
blink(zero)
	void *zero;
{
	register int s;
	register fixpt_t lav;

	s = splhigh();
D 5
	*AUXIO_REG = (*AUXIO_REG | AUXIO_MB1) ^ AUXIO_LED;
E 5
I 5
	LED_FLIP;
E 5
	splx(s);
	/*
	 * Blink rate is:
	 *	full cycle every second if completely idle (loadav = 0)
	 *	full cycle every 2 seconds if loadav = 1
	 *	full cycle every 3 seconds if loadav = 2
	 * etc.
	 */
	s = (((averunnable[0] + FSCALE) * hz) >> (FSHIFT + 1));
	timeout(blink, (caddr_t)0, s);
}
#endif
I 5

/*
 * The OPENPROM calls this "auxiliary-io".
 */
static int
auxregmatch(parent, cf, aux)
	struct device *parent;
	struct cfdata *cf;
	void *aux;
{

	return (strcmp("auxiliary-io", ((struct romaux *)aux)->ra_name) == 0);
}
E 5

/* ARGSUSED */
static void
auxregattach(parent, self, aux)
	struct device *parent, *self;
	void *aux;
{
	struct romaux *ra = aux;

	(void)mapdev(ra->ra_paddr, AUXREG_VA, sizeof(long));
	printf("\n");
#ifdef BLINK
	blink((caddr_t)0);
#endif
}
E 1
