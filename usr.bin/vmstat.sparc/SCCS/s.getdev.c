h29860
s 00002/00002/00040
d D 8.1 93/06/06 22:22:34 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00042/00000/00000
d D 5.1 93/05/21 15:10:05 torek 1 0
c date and time created 93/05/21 15:10:05 by torek
e
u
U
t
T
I 1
/*
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

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/device.h>

#include <kvm.h>

#include "getdev.h"

extern kvm_t *kd;

extern void errexit __P((const char *, ...));
extern void kread __P((u_long, void *, size_t, char *));

/*
 * Read in devices and add those whose predicate matches.
 */
void
getdev(alladdr, take, add)
	u_long alladdr;
	int (*take) __P((struct device *));
	void (*add) __P((u_long, struct device *));
{
	register u_long addr;
	struct device dev, *alldevs;

	kread(alladdr, &alldevs, sizeof(alldevs), "alldevs");
	for (addr = (u_long)alldevs; addr != 0; addr = (u_long)dev.dv_next) {
		kread(addr, &dev, sizeof(dev), "(device)");
		if (take(&dev))
			add(addr, &dev);
	}
}
E 1
