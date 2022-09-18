h33311
s 00002/00002/00077
d D 8.1 93/06/04 16:53:36 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00079/00000/00000
d D 5.1 93/04/27 15:23:32 bostic 1 0
c date and time created 93/04/27 15:23:32 by bostic
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
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/param.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/proc.h>
#include <sys/sysctl.h>
#include <vm/vm_param.h>

#include <db.h>
#include <fcntl.h>
#include <limits.h>
#include <nlist.h>
#include <kvm.h>

#include "kvm_private.h"

static struct nlist nl[] = {
	{ "_averunnable" },
#define	X_AVERUNNABLE	0
	{ "_fscale" },
#define	X_FSCALE	1
	{ "" },
};

/*
 * kvm_getloadavg() -- Get system load averages, from live or dead kernels.
 *
 * Put `nelem' samples into `loadavg' array.
 * Return number of samples retrieved, or -1 on error.
 */
int
kvm_getloadavg(kd, loadavg, nelem)
	kvm_t *kd;
	double loadavg[];
	int nelem;
{
	struct loadavg loadinfo;
	struct nlist *p;
	int fscale, i;

	if (ISALIVE(kd))
		return (getloadavg(loadavg, nelem));

	if (kvm_nlist(kd, nl) != 0) {
		for (p = nl; p->n_type != 0; ++p);
		_kvm_err(kd, kd->program,
		    "%s: no such symbol", p->n_name);
		return (-1);
	}

#define KREAD(kd, addr, obj) \
	(kvm_read(kd, addr, (char *)(obj), sizeof(*obj)) != sizeof(*obj))
	if (KREAD(kd, nl[X_AVERUNNABLE].n_value, &loadinfo)) {
		_kvm_err(kd, kd->program, "can't read averunnable");
		return (-1);
	}

	/*
	 * Old kernels have fscale separately; if not found assume
	 * running new format.
	 */
	if (!KREAD(kd, nl[X_FSCALE].n_value, &fscale))
		loadinfo.fscale = fscale;

	nelem = MIN(nelem, sizeof(loadinfo.ldavg) / sizeof(fixpt_t));
	for (i = 0; i < nelem; i++)
		loadavg[i] = (double) loadinfo.ldavg[i] / loadinfo.fscale;
	return (nelem);
}
E 1
