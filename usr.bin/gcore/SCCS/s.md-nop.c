h29475
s 00002/00002/00025
d D 8.1 93/06/06 14:42:51 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00026
d D 5.5 93/05/25 23:34:08 bostic 5 4
c kinfo_proc => sysctl
e
s 00000/00001/00027
d D 5.4 93/03/31 17:27:37 mckusick 4 3
c convert from kinfo to sysctl
e
s 00004/00000/00024
d D 5.3 92/06/29 18:57:36 bostic 3 2
c put in keywords
e
s 00006/00003/00018
d D 5.2 92/06/29 18:57:19 bostic 2 1
c cleanup and ANSI-ficatoin
e
s 00021/00000/00000
d D 5.1 92/06/19 16:48:51 mccanne 1 0
c date and time created 92/06/19 16:48:51 by mccanne
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 */

I 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 3
D 2
#include <stdio.h>
#include <kvm.h>
E 2
#include <sys/param.h>
D 4
#include <sys/kinfo.h>
E 4
D 5
#include <sys/kinfo_proc.h>
E 5
I 5
#include <sys/sysctl.h>
E 5

I 2
#include <stdio.h>
#include <kvm.h>
#include "extern.h"

void
E 2
md_core(kd, fd, ki)
	kvm_t *kd;
	int fd;
	struct kinfo_proc *ki;
{
	/* Don't need to fix anything for this architecture. */
D 2
	return (0);
E 2
I 2
	return;
E 2
}
E 1
