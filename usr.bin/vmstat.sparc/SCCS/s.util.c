h04882
s 00002/00002/00083
d D 8.1 93/06/06 22:22:57 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00085/00000/00000
d D 5.1 93/05/21 15:10:07 torek 1 0
c date and time created 93/05/21 15:10:07 by torek
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>

#include <errno.h>
#include <kvm.h>
#include <nlist.h>
#include <stdio.h>
#include <stdlib.h>
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

#include "extern.h"

/*
 * kvm_nlist, but with error exits.
 */
void
knlist(nl)
	struct nlist *nl;
{
	int nmissing;

	if ((nmissing = kvm_nlist(kd, nl)) == 0)
		return;
	if (nmissing < 0)
		errexit("kvm_nlist: %s\n", kvm_geterr(kd));
	(void)fprintf(stderr, "vmstat: undefined symbols:");
	for (; nl->n_name && *nl->n_name; nl++)
		if (nl->n_type == 0)
			printf(" %s", nl->n_name);
	(void)fputc('\n', stderr);
	exit(1);
}

/*
 * kread reads something from the kernel, given its address.
 * It aborts on failure.
 */
void
kread(addr, buf, size, err)
	u_long addr;
	void *buf;
	size_t size;
	char *err;
{

	if (kvm_read(kd, addr, buf, size) != size)
		errexit("kvm_read(%s): %s\n", err, kvm_geterr(kd));
}

void
#if __STDC__
errexit(const char *fmt, ...)
#else
errexit(fmt, va_alist)
	char *fmt;
	va_dcl
#endif
{
	va_list ap;

#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "vmstat: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	exit(1);
	/* NOTREACHED */
}
E 1
