h63338
s 00001/00000/00318
d D 8.3 94/05/17 11:48:03 mckusick 9 8
c need libkern.h include file
e
s 00006/00004/00312
d D 8.2 94/05/12 12:12:08 mckusick 8 7
c proper sizing the dev array on first device (from Glass & Torek)
e
s 00002/00002/00314
d D 8.1 93/06/10 21:58:16 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00026/00002/00290
d D 7.6 93/02/01 11:32:05 torek 6 5
c separate out event counters
e
s 00041/00022/00251
d D 7.5 92/11/18 18:08:00 torek 5 4
c add cfroots & simplify; allow duplicate config data; add events
c and make dv_xname an array for export
e
s 00003/00003/00270
d D 7.4 92/10/11 10:38:16 bostic 4 3
c make kernel includes standard
e
s 00077/00048/00196
d D 7.3 92/06/20 00:01:45 mckusick 3 2
c update from Torek
e
s 00003/00003/00241
d D 7.2 92/04/01 18:13:12 mckusick 2 1
c fix LBL contrib notice
e
s 00244/00000/00000
d D 7.1 92/02/19 17:50:00 mckusick 1 0
c from Chris Torek
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 2
 * This code is derived from software contributed to Berkeley by
 * the Computer Systems Engineering group at Lawrence Berkeley
 * Laboratory under DARPA contract BG 91-66.
E 2
I 2
D 3
 * This code is derived from software developed by the Computer Systems
 * Engineering group at Lawrence Berkeley Laboratory under DARPA
 * contract BG 91-66 and contributed to Berkeley.
E 3
I 3
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
E 3
E 2
 *
I 5
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratories.
 *
E 5
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: subr_autoconf.c,v 1.3 91/11/23 00:53:49 torek Exp $ (LBL)
E 3
I 3
D 5
 * from: $Header: subr_autoconf.c,v 1.6 92/06/11 17:56:19 torek Exp $ (LBL)
E 5
I 5
D 6
 * from: $Header: subr_autoconf.c,v 1.9 92/11/19 01:59:01 torek Exp $ (LBL)
E 6
I 6
 * from: $Header: subr_autoconf.c,v 1.12 93/02/01 19:31:48 torek Exp $ (LBL)
E 6
E 5
E 3
 */

D 4
#include "sys/param.h"
#include "sys/device.h"
#include "sys/malloc.h"
E 4
I 4
#include <sys/param.h>
#include <sys/device.h>
#include <sys/malloc.h>
I 9
#include <libkern/libkern.h>
E 9
E 4

/*
 * Autoconfiguration subroutines.
 */

D 5
extern struct cfdata cfdata[];		/* from ioconf.c */
E 5
I 5
/*
 * ioconf.c exports exactly two names: cfdata and cfroots.  All system
 * devices and drivers are found via these tables.
 */
extern struct cfdata cfdata[];
extern short cfroots[];
E 5

#define	ROOT ((struct device *)NULL)

I 3
struct matchinfo {
	cfmatch_t fn;
	struct	device *parent;
	void	*aux;
	struct	cfdata *match;
	int	pri;
};

E 3
/*
I 3
 * Apply the matching function and choose the best.  This is used
 * a few times and we want to keep the code small.
 */
static void
mapply(m, cf)
	register struct matchinfo *m;
	register struct cfdata *cf;
{
	register int pri;

	if (m->fn != NULL)
		pri = (*m->fn)(m->parent, cf, m->aux);
	else
		pri = (*cf->cf_driver->cd_match)(m->parent, cf, m->aux);
	if (pri > m->pri) {
		m->match = cf;
		m->pri = pri;
	}
}

/*
E 3
 * Iterate over all potential children of some device, calling the given
 * function (default being the child's match function) for each one.
 * Nonzero returns are matches; the highest value returned is considered
 * the best match.  Return the `found child' if we got a match, or NULL
 * otherwise.  The `aux' pointer is simply passed on through.
 *
 * Note that this function is designed so that it can be used to apply
 * an arbitrary function to all potential children (its return value
 * can be ignored).
 */
struct cfdata *
D 3
config_search(fn, dev, aux)
	register cfmatch_t fn;
	register struct device *dev;
	register void *aux;
E 3
I 3
config_search(fn, parent, aux)
	cfmatch_t fn;
	register struct device *parent;
	void *aux;
E 3
{
D 3
	register struct cfdata *cf, *pcf, *match = NULL;
E 3
I 3
D 5
	register struct cfdata *cf, *pcf;
E 5
I 5
	register struct cfdata *cf;
E 5
E 3
	register short *p;
D 3
	register int pri, bestpri = 0;
E 3
I 3
	struct matchinfo m;
E 3

I 3
	m.fn = fn;
	m.parent = parent;
	m.aux = aux;
	m.match = NULL;
	m.pri = 0;
E 3
	for (cf = cfdata; cf->cf_driver; cf++) {
		/*
D 5
		 * Skip cf if no longer eligible, or if a root entry.
D 3
		 * Otherwise scan through parents for one matching `dev'
E 3
I 3
		 * Otherwise scan through parents for one matching `parent'
E 3
		 * (and alive), and try match function.
E 5
I 5
		 * Skip cf if no longer eligible, otherwise scan through
		 * parents for one matching `parent', and try match function.
E 5
		 */
D 5
		if (cf->cf_fstate == FSTATE_FOUND ||
		    (p = cf->cf_parents) == NULL)
E 5
I 5
		if (cf->cf_fstate == FSTATE_FOUND)
E 5
			continue;
D 5
		while (*p >= 0) {
			pcf = &cfdata[*p++];
D 3
			if (pcf->cf_fstate != FSTATE_FOUND ||
			    pcf->cf_driver->cd_name != dev->dv_name ||
			    pcf->cf_unit != dev->dv_unit)
				continue;
			if (fn != NULL)
				pri = (*fn)(dev, cf, aux);
			else
				pri = (*cf->cf_driver->cd_match)(dev, cf, aux);
			if (pri > bestpri) {
				match = cf;
				bestpri = pri;
			}
E 3
I 3
			if (parent->dv_cfdata == pcf)
E 5
I 5
		for (p = cf->cf_parents; *p >= 0; p++)
			if (parent->dv_cfdata == &cfdata[*p])
E 5
				mapply(&m, cf);
E 3
D 5
		}
E 5
	}
D 3
	return (match);
E 3
I 3
	return (m.match);
E 3
}

/*
 * Find the given root device.
 * This is much like config_search, but there is no parent.
 */
struct cfdata *
config_rootsearch(fn, rootname, aux)
	register cfmatch_t fn;
	register char *rootname;
	register void *aux;
{
D 3
	register struct cfdata *cf, *match = NULL;
	register int pri, bestpri = 0;
E 3
I 3
	register struct cfdata *cf;
I 5
	register short *p;
E 5
	struct matchinfo m;
E 3

D 3
	for (cf = cfdata; cf->cf_driver; cf++) {
		/*
		 * Look at root entries for matching name.
		 * We do not bother with found-state here
		 * since only one root should ever be searched.
		 */
		if (cf->cf_parents != NULL || cf->cf_unit != 0 ||
		    strcmp(cf->cf_driver->cd_name, rootname) != 0)
			continue;
		if (fn != NULL)
			pri = (*fn)(ROOT, cf, aux);
		else
			pri = (*cf->cf_driver->cd_match)(ROOT, cf, aux);
		if (pri > bestpri) {
			match = cf;
			bestpri = pri;
		}
	}
	return (match);
E 3
I 3
	m.fn = fn;
	m.parent = ROOT;
	m.aux = aux;
	m.match = NULL;
	m.pri = 0;
	/*
	 * Look at root entries for matching name.  We do not bother
D 5
	 * with found-state here since only one root should ever be searched.
E 5
I 5
	 * with found-state here since only one root should ever be
	 * searched (and it must be done first).
E 5
	 */
D 5
	for (cf = cfdata; cf->cf_driver; cf++)
		if (cf->cf_parents == NULL && cf->cf_unit == 0 &&
		    strcmp(cf->cf_driver->cd_name, rootname) == 0)
E 5
I 5
	for (p = cfroots; *p >= 0; p++) {
		cf = &cfdata[*p];
		if (strcmp(cf->cf_driver->cd_name, rootname) == 0)
E 5
			mapply(&m, cf);
I 5
	}
E 5
	return (m.match);
E 3
}

static char *msgs[3] = { "", " not configured\n", " unsupported\n" };

/*
 * The given `aux' argument describes a device that has been found
 * on the given parent, but not necessarily configured.  Locate the
 * configuration data for that device (using the cd_match configuration
 * driver function) and attach it, and return true.  If the device was
 * not configured, call the given `print' function and return 0.
 */
int
config_found(parent, aux, print)
	struct device *parent;
	void *aux;
	cfprint_t print;
{
	struct cfdata *cf;

	if ((cf = config_search((cfmatch_t)NULL, parent, aux)) != NULL) {
		config_attach(parent, cf, aux, print);
		return (1);
	}
	printf(msgs[(*print)(aux, parent->dv_xname)]);
	return (0);
}

/*
 * As above, but for root devices.
 */
int
config_rootfound(rootname, aux)
	char *rootname;
	void *aux;
{
	struct cfdata *cf;

	if ((cf = config_rootsearch((cfmatch_t)NULL, rootname, aux)) != NULL) {
		config_attach(ROOT, cf, aux, (cfprint_t)NULL);
		return (1);
	}
	printf("root device %s not configured\n", rootname);
	return (0);
}

/* just like sprintf(buf, "%d") except that it works from the end */
static char *
number(ep, n)
	register char *ep;
	register int n;
{

	*--ep = 0;
	while (n >= 10) {
		*--ep = (n % 10) + '0';
		n /= 10;
	}
	*--ep = n + '0';
	return (ep);
}

/*
 * Attach a found device.  Allocates memory for device variables.
 */
void
config_attach(parent, cf, aux, print)
	register struct device *parent;
	register struct cfdata *cf;
	register void *aux;
	cfprint_t print;
{
	register struct device *dev;
	register struct cfdriver *cd;
	register size_t lname, lunit;
	register char *xunit;
I 3
	int myunit;
E 3
	char num[10];
I 3
	static struct device **nextp = &alldevs;
E 3

	cd = cf->cf_driver;
	if (cd->cd_devsize < sizeof(struct device))
		panic("config_attach");
I 3
	myunit = cf->cf_unit;
E 3
	if (cf->cf_fstate == FSTATE_NOTFOUND)
		cf->cf_fstate = FSTATE_FOUND;
I 3
	else
		cf->cf_unit++;
E 3

	/* compute length of name and decimal expansion of unit number */
	lname = strlen(cd->cd_name);
D 3
	xunit = number(&num[sizeof num], cf->cf_unit);
E 3
I 3
	xunit = number(&num[sizeof num], myunit);
E 3
	lunit = &num[sizeof num] - xunit;
I 5
	if (lname + lunit >= sizeof(dev->dv_xname))
		panic("config_attach: device name too long");
E 5

D 5
	/* get memory for all device vars, plus expanded name */
	dev = (struct device *)malloc(cd->cd_devsize + lname + lunit,
	    M_DEVBUF, M_WAITOK);		/* XXX cannot wait! */
E 5
I 5
	/* get memory for all device vars */
	dev = (struct device *)malloc(cd->cd_devsize, M_DEVBUF, M_WAITOK);
					/* XXX cannot wait! */
E 5
	bzero(dev, cd->cd_devsize);
I 3
	*nextp = dev;			/* link up */
	nextp = &dev->dv_next;
	dev->dv_class = cd->cd_class;
	dev->dv_cfdata = cf;
E 3
D 5
	dev->dv_name = cd->cd_name;
E 5
D 3
	dev->dv_unit = cf->cf_unit;
	dev->dv_flags = cf->cf_flags;
E 3
I 3
	dev->dv_unit = myunit;
E 3
D 5
	dev->dv_xname = (char *)dev + cd->cd_devsize;
	bcopy(dev->dv_name, dev->dv_xname, lname);
E 5
I 5
	bcopy(cd->cd_name, dev->dv_xname, lname);
E 5
	bcopy(xunit, dev->dv_xname + lname, lunit);
	dev->dv_parent = parent;
I 5
D 6
	bcopy(cd->cd_evnam, dev->dv_evnam, sizeof(cd->cd_evnam));
E 6
E 5
	if (parent == ROOT)
		printf("%s (root)", dev->dv_xname);
	else {
		printf("%s at %s", dev->dv_xname, parent->dv_xname);
		(void) (*print)(aux, (char *)0);
	}

	/* put this device in the devices array */
	if (dev->dv_unit >= cd->cd_ndevs) {
		/*
		 * Need to expand the array.
		 */
		int old = cd->cd_ndevs, oldbytes, new, newbytes;
		void **nsp;

		if (old == 0) {
D 8
			nsp = malloc(MINALLOCSIZE, M_DEVBUF, M_WAITOK);	/*XXX*/
			bzero(nsp, MINALLOCSIZE);
			cd->cd_ndevs = MINALLOCSIZE / sizeof(void *);
E 8
I 8
			new = max(MINALLOCSIZE / sizeof(void *),
			    dev->dv_unit + 1);
			newbytes = new * sizeof(void *);
			nsp = malloc(newbytes, M_DEVBUF, M_WAITOK);	/*XXX*/
			bzero(nsp, newbytes);
E 8
		} else {
			new = cd->cd_ndevs;
			do {
				new *= 2;
			} while (new <= dev->dv_unit);
D 8
			cd->cd_ndevs = new;
E 8
			oldbytes = old * sizeof(void *);
			newbytes = new * sizeof(void *);
			nsp = malloc(newbytes, M_DEVBUF, M_WAITOK);	/*XXX*/
			bcopy(cd->cd_devs, nsp, oldbytes);
			bzero(&nsp[old], newbytes - oldbytes);
			free(cd->cd_devs, M_DEVBUF);
		}
I 8
		cd->cd_ndevs = new;
E 8
		cd->cd_devs = nsp;
	}
I 3
	if (cd->cd_devs[dev->dv_unit])
		panic("config_attach: duplicate %s", dev->dv_xname);
E 3
	cd->cd_devs[dev->dv_unit] = dev;
I 5

	/*
	 * Before attaching, clobber any unfound devices that are
	 * otherwise identical.
	 */
	for (cf = cfdata; cf->cf_driver; cf++)
		if (cf->cf_driver == cd && cf->cf_unit == dev->dv_unit &&
		    cf->cf_fstate == FSTATE_NOTFOUND)
			cf->cf_fstate = FSTATE_FOUND;
E 5
	(*cd->cd_attach)(parent, dev, aux);
I 6
}

/*
 * Attach an event.  These must come from initially-zero space (see
 * commented-out assignments below), but that occurs naturally for
 * device instance variables.
 */
void
evcnt_attach(dev, name, ev)
	struct device *dev;
	const char *name;
	struct evcnt *ev;
{
	static struct evcnt **nextp = &allevents;

#ifdef DIAGNOSTIC
	if (strlen(name) >= sizeof(ev->ev_name))
		panic("evcnt_attach");
#endif
	/* ev->ev_next = NULL; */
	ev->ev_dev = dev;
	/* ev->ev_count = 0; */
	strcpy(ev->ev_name, name);
	*nextp = ev;
	nextp = &ev->ev_next;
E 6
}
E 1
