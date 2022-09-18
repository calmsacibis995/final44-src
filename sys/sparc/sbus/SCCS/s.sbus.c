h54899
s 00002/00002/00150
d D 8.1 93/06/11 15:14:59 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00006/00142
d D 7.4 93/04/20 19:45:24 torek 4 3
c update from elf: add bootpath and bootdv.
e
s 00005/00005/00143
d D 7.3 92/10/11 12:49:49 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00143
d D 7.2 92/07/21 16:52:07 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00143/00000/00000
d D 7.1 92/07/13 00:44:07 torek 1 0
c date and time created 92/07/13 00:44:07 by torek
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
 * from: $Header: sbus.c,v 1.8 92/06/17 06:59:43 torek Exp $ (LBL)
E 4
I 4
 * from: $Header: sbus.c,v 1.10 92/11/26 02:28:13 torek Exp $ (LBL)
E 4
 */

/*
 * Sbus stuff.
 */

D 4
/* #include "sbus.h" */
#define NSBUS 1	/* XXX */

E 4
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
E 3

D 3
#include "sbusreg.h"
#include "sbusvar.h"
E 3
I 3
#include <sparc/sbus/sbusreg.h>
#include <sparc/sbus/sbusvar.h>
E 3

/* autoconfiguration driver */
void	sbus_attach __P((struct device *, struct device *, void *));
struct cfdriver sbuscd =
    { NULL, "sbus", matchbyname, sbus_attach,
      DV_DULL, sizeof(struct sbus_softc) };

/*
 * Print the location of some sbus-attached device (called just
 * before attaching that device).  If `sbus' is not NULL, the
 * device was found but not configured; print the sbus as well.
 * Return UNCONF (config_find ignores this if the device was configured).
 */
int
sbus_print(args, sbus)
	void *args;
	char *sbus;
{
	register struct sbus_attach_args *sa = args;

	if (sbus)
		printf("%s at %s", sa->sa_ra.ra_name, sbus);
	printf(" slot %d offset 0x%x", sa->sa_slot, sa->sa_offset);
	return (UNCONF);
}

/*
 * Attach an Sbus.
 */
void
sbus_attach(parent, self, aux)
	struct device *parent;
	struct device *self;
	void *aux;
{
	register struct sbus_softc *sc = (struct sbus_softc *)self;
	register int base, node, slot;
	register char *name;
	struct sbus_attach_args sa;
I 4
	register struct romaux *ra;
E 4

	/*
	 * XXX there is only one Sbus, for now -- do not know how to
	 * address children on others
	 */
	if (sc->sc_dev.dv_unit > 0) {
		printf(" unsupported\n");
		return;
	}

	/*
	 * Record clock frequency for synchronous SCSI.
	 * IS THIS THE CORRECT DEFAULT??
	 */
D 4
	node = ((struct romaux *)aux)->ra_node;
E 4
I 4
	ra = aux;
	node = ra->ra_node;
E 4
	sc->sc_clockfreq = getpropint(node, "clock-frequency", 25*1000*1000);
	printf(": clock = %s MHz\n", clockfreq(sc->sc_clockfreq));
I 4

	if (ra->ra_bp != NULL && strcmp(ra->ra_bp->name, "sbus") == 0)
		sa.sa_ra.ra_bp = ra->ra_bp + 1;
	else
		sa.sa_ra.ra_bp = NULL;
E 4

	/*
	 * Loop through ROM children, fixing any relative addresses
	 * and then configuring each device.
	 */
	for (node = firstchild(node); node; node = nextsibling(node)) {
		name = getpropstring(node, "name");
		if (!romprop(&sa.sa_ra, name, node))
			continue;
		base = (int)sa.sa_ra.ra_paddr;
		if (SBUS_ABS(base)) {
			sa.sa_slot = SBUS_ABS_TO_SLOT(base);
			sa.sa_offset = SBUS_ABS_TO_OFFSET(base);
		} else {
			sa.sa_slot = slot = sa.sa_ra.ra_iospace;
			sa.sa_offset = base;
			sa.sa_ra.ra_paddr = (void *)SBUS_ADDR(slot, base);
		}
		(void) config_found(&sc->sc_dev, (void *)&sa, sbus_print);
	}
}

/*
 * Each attached device calls sbus_establish after it initializes
 * its sbusdev portion.
 */
void
sbus_establish(sd, dev)
	register struct sbusdev *sd;
	register struct device *dev;
{
	register struct sbus_softc *sc = (struct sbus_softc *)dev->dv_parent;

	sd->sd_dev = dev;
	sd->sd_bchain = sc->sc_sbdev;
	sc->sc_sbdev = sd;
}

/*
 * Reset the given sbus. (???)
 */
void
sbusreset(sbus)
	int sbus;
{
	register struct sbusdev *sd;
	struct sbus_softc *sc = sbuscd.cd_devs[sbus];
	struct device *dev;

	printf("reset %s:", sc->sc_dev.dv_xname);
	for (sd = sc->sc_sbdev; sd != NULL; sd = sd->sd_bchain) {
		if (sd->sd_reset) {
			dev = sd->sd_dev;
			(*sd->sd_reset)(dev);
			printf(" %s", dev->dv_xname);
		}
	}
}
E 1
