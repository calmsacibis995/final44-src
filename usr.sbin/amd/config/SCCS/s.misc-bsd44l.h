h44399
s 00022/00000/00000
d D 8.1 95/05/10 05:37:28 pendry 1 0
c date and time created 95/05/10 05:37:28 by pendry
e
u
U
t
T
I 1
/*
 * Copyright (c) 1995 Jan-Simon Pendry
 * Copyright (c) 1995
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 */

#define M_NEWTYPE	0

#include <sys/ucred.h>
#include <nfs/rpcv2.h>
#define NFS_NPROCS	26		/* from <nfs/nfsproto.h> */
#include <nfs/nfs.h>

#include <ufs/ufs/ufsmount.h>
E 1
