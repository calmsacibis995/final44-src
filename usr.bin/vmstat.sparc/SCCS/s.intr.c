h12030
s 00002/00002/00061
d D 8.1 93/06/06 22:22:39 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00063/00000/00000
d D 5.1 93/05/21 15:10:06 torek 1 0
c date and time created 93/05/21 15:10:06 by torek
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

#include <errno.h>
#include <kvm.h>
#include <nlist.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "extern.h"

static struct nlist nl[] = {
	{ "_intrcnt" },
#define	X_INTRCNT	0
	{ "_eintrcnt" },
#define	X_EINTRCNT	1
	{ "_intrnames" },
#define	X_INTRNAMES	2
	{ "_eintrnames" },
#define	X_EINTRNAMES	3
	0
};

void
dointr()
{
	register long *intrcnt, inttotal, uptime;
	register int nintr, inamlen;
	register char *intrname;

	knlist(nl);
	uptime = getuptime();
	nintr = nl[X_EINTRCNT].n_value - nl[X_INTRCNT].n_value;
	inamlen = nl[X_EINTRNAMES].n_value - nl[X_INTRNAMES].n_value;
	intrcnt = malloc((size_t)nintr);
	intrname = malloc((size_t)inamlen);
	if (intrcnt == NULL || intrname == NULL)
		errexit("malloc: %s\n", strerror(errno));
	kread(nl[X_INTRCNT].n_value, intrcnt, nintr, "intrcnt");
	kread(nl[X_INTRNAMES].n_value, intrname, inamlen, "intrnames");
	(void)printf("interrupt      total      rate\n");
	inttotal = 0;
	nintr /= sizeof(long);
	while (--nintr >= 0) {
		if (*intrcnt)
			(void)printf("%-12s %8ld %8ld\n", intrname,
			    *intrcnt, *intrcnt / uptime);
		intrname += strlen(intrname) + 1;
		inttotal += *intrcnt++;
	}
	(void)printf("Total        %8ld %8ld\n", inttotal, inttotal / uptime);
}
E 1
