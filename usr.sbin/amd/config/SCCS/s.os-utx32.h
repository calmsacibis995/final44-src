h02723
s 00002/00002/00057
d D 8.1 93/06/06 11:52:29 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00059
d D 5.3 91/05/12 15:59:17 pendry 3 2
c checkpoint for network tape
e
s 00001/00001/00058
d D 5.2 91/03/17 13:50:01 pendry 2 1
c from amd5.3 alpha11
e
s 00059/00000/00000
d D 5.1 90/06/29 12:41:21 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
D 2
/* $Id: os-utx32.h,v 5.2 90/06/23 22:21:00 jsp Rel $ */
E 2
I 2
/* $Id: os-utx32.h,v 5.2.1.1 90/10/21 22:31:11 jsp Exp $ */
E 2

/*
 * Gould UTX/32 definitions for Amd (automounter)
 *
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 4
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Does the compiler grok void *
 */
#ifdef __GNUC__
#define	VOIDP
#endif

/*
 * Which version of the Sun RPC library we are using
 * This is the implementation release number, not
 * the protocol revision number.
 */
#define	RPC_3

/*
 * Which version of the NFS interface are we using.
 * This is the implementation release number, not
 * the protocol revision number.
 */
#define	NFS_3

/*
 * Does this OS have NDBM support?
 */
#define OS_HAS_NDBM

/*
 * Byte ordering
 */
#undef ARCH_ENDIAN
#if defined(gould) || defined(GOULD_PN)
#define	ARCH_ENDIAN	"big"
#endif

/*
 * Name of filesystem types
 */
#define	MOUNT_TYPE_NFS	MOUNT_NFS
#define	MOUNT_TYPE_UFS	MOUNT_UFS
#undef MTAB_TYPE_UFS
#define	MTAB_TYPE_UFS	"4.3"
E 1
