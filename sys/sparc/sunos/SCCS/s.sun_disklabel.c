h41856
s 00002/00002/00114
d D 8.1 93/06/11 15:19:29 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00115
d D 7.4 93/04/06 19:41:15 torek 4 3
c spelling
e
s 00006/00006/00110
d D 7.3 92/10/11 12:59:32 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00111
d D 7.2 92/07/21 16:55:41 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00111/00000/00000
d D 7.1 92/07/13 00:40:45 torek 1 0
c date and time created 92/07/13 00:40:45 by torek
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
 * from: $Header: sun_disklabel.c,v 1.5 92/06/17 07:04:12 torek Exp $
 */

/*
 * SunOS disk label code.
 */

D 3
#include "sys/param.h"
#include "sys/disklabel.h"
#include "sys/device.h"
#include "sys/disk.h"
#include "sys/ioctl.h"
E 3
I 3
#include <sys/param.h>
#include <sys/disklabel.h>
#include <sys/device.h>
#include <sys/disk.h>
#include <sys/ioctl.h>
E 3

D 3
#include "sun_disklabel.h"
E 3
I 3
#include <sparc/sunos/sun_disklabel.h>
E 3

/*
 * Take a sector (cp) containing a SunOS disk label and set lp to a BSD
 * disk label.
 */
int
sun_disklabel(cp, lp)
	register caddr_t cp;
	register struct disklabel *lp;
{
	register u_short *sp;
	register struct sun_disklabel *sl;
	register int i, v;

	sp = (u_short *)(cp + sizeof(struct sun_disklabel));
	--sp;
	v = 0;
	while (sp >= (u_short *)cp)
		v ^= *sp--;
	if (v)
		return (0);
	sl = (struct sun_disklabel *)cp;
	lp->d_magic = 0;	/* denote as pseudo */
	lp->d_ncylinders = sl->sl_ncylinders;
	lp->d_acylinders = sl->sl_acylinders;
	v = (lp->d_ntracks = sl->sl_ntracks) *
	    (lp->d_nsectors = sl->sl_nsectors);
	lp->d_secpercyl = v;
	lp->d_npartitions = 8;
	for (i = 0; i < 8; i++) {
		lp->d_partitions[i].p_offset =
		    sl->sl_part[i].sdkp_cyloffset * v;
		lp->d_partitions[i].p_size = sl->sl_part[i].sdkp_nsectors;
	}
	return (1);
}

int
sun_dkioctl(dk, cmd, data, partition)
	struct dkdevice *dk;
	int cmd;
	caddr_t data;
	int partition;
{
	register struct partition *p;

	switch (cmd) {

	case DKIOCGGEOM:
#define geom ((struct sun_dkgeom *)data)
		bzero(data, sizeof(*geom));
		geom->sdkc_ncylinders = dk->dk_label.d_ncylinders;
		geom->sdkc_acylinders = dk->dk_label.d_acylinders;
		geom->sdkc_ntracks = dk->dk_label.d_ntracks;
		geom->sdkc_nsectors = dk->dk_label.d_nsectors;
		geom->sdkc_interleave = dk->dk_label.d_interleave;
		geom->sdkc_sparespercyl = dk->dk_label.d_sparespercyl;
		geom->sdkc_rpm = dk->dk_label.d_rpm;
		geom->sdkc_pcylinders =
		    dk->dk_label.d_ncylinders + dk->dk_label.d_acylinders;
#undef	geom
		break;

	case DKIOCINFO:
		/* Homey don't do DKIOCINFO */
		bzero(data, sizeof(struct sun_dkctlr));
		break;

	case DKIOCGPART:
		if (dk->dk_label.d_secpercyl == 0)
			return (ERANGE);	/* XXX */
		p = &dk->dk_label.d_partitions[partition];
		if (p->p_offset % dk->dk_label.d_secpercyl != 0)
			return (ERANGE);	/* XXX */
#define part ((struct sun_dkpart *)data)
		part->sdkp_cyloffset = p->p_offset / dk->dk_label.d_secpercyl;
		part->sdkp_nsectors = p->p_size;
#undef	part
		break;

	default:
		return (-1);
	}
	return (0);
}
E 1
