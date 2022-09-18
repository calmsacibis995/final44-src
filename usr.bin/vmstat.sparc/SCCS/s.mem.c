h63704
s 00002/00002/00079
d D 8.1 93/06/06 22:22:45 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00081/00000/00000
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

#include <sys/param.h>
#include <sys/malloc.h>

#include <errno.h>
#include <kvm.h>
#include <nlist.h>
#include <stdio.h>

#include "extern.h"

static struct nlist nl[] = {
#define	X_KMEMSTATS	0
	{ "_kmemstats" },
#define	X_BUCKET	1
	{ "_bucket" },
	0
};
/*
 * These names are defined in <sys/malloc.h>.
 */
char *kmemnames[] = INITKMEMNAMES;

void
domem()
{
	register struct kmembuckets *kp;
	register struct kmemstats *ks;
	register int i;
	int size;
	long totuse = 0, totfree = 0, totreq = 0;
	struct kmemstats kmemstats[M_LAST];
	struct kmembuckets buckets[MINBUCKET + 16];

	knlist(nl);
	kread(nl[X_BUCKET].n_value, &buckets, sizeof buckets, "kmembucket");
	(void)printf("Memory statistics by bucket size\n");
	(void)printf(
	    "    Size   In Use   Free   Requests  HighWater  Couldfree\n");
	for (i = MINBUCKET, kp = &buckets[i]; i < MINBUCKET + 16; i++, kp++) {
		if (kp->kb_calls == 0)
			continue;
		size = 1 << i;
		(void)printf("%8d %8ld %6ld %10ld %7ld %10ld\n", size, 
			kp->kb_total - kp->kb_totalfree,
			kp->kb_totalfree, kp->kb_calls,
			kp->kb_highwat, kp->kb_couldfree);
		totfree += size * kp->kb_totalfree;
	}

	kread(nl[X_KMEMSTATS].n_value, &kmemstats, sizeof kmemstats,
	    "kmemstats");
	(void)printf("\nMemory statistics by type\n");
	(void)printf(
"       Type  In Use  MemUse   HighUse  Limit Requests  TypeLimit KernLimit\n");
	for (i = 0, ks = &kmemstats[0]; i < M_LAST; i++, ks++) {
		if (ks->ks_calls == 0)
			continue;
		(void)printf("%11s %6ld %7ldK %8ldK %5ldK %8ld %6u %9u\n",
		    kmemnames[i] ? kmemnames[i] : "undefined",
		    ks->ks_inuse, (ks->ks_memuse + 1023) / 1024,
		    (ks->ks_maxused + 1023) / 1024,
		    (ks->ks_limit + 1023) / 1024, ks->ks_calls,
		    ks->ks_limblocks, ks->ks_mapblocks);
		totuse += ks->ks_memuse;
		totreq += ks->ks_calls;
	}
	(void)printf("\nMemory Totals:  In Use    Free    Requests\n");
	(void)printf("              %7ldK %6ldK    %8ld\n",
	     (totuse + 1023) / 1024, (totfree + 1023) / 1024, totreq);
}
E 1
