h23514
s 00002/00002/00052
d D 8.1 93/06/06 11:51:18 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00053
d D 5.4 92/02/09 08:31:10 pendry 4 3
c merge in new release
e
s 00005/00005/00049
d D 5.3 91/05/12 15:58:56 pendry 3 2
c checkpoint for network tape
e
s 00001/00001/00053
d D 5.2 91/03/17 13:49:26 pendry 2 1
c from amd5.3 alpha11
e
s 00054/00000/00000
d D 5.1 90/06/29 12:41:11 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
D 2
/* $Id: os-convex.h,v 5.2 90/06/23 22:20:42 jsp Rel $ */
E 2
I 2
D 3
/* $Id: os-convex.h,v 5.2.1.1 90/10/21 22:30:48 jsp Exp $ */
E 2

E 3
/*
D 3
 * Convex C220, version 7.1 definitions for Amd (automounter)
 *         from Eitan Mizrotsky <eitan@shum.huji.ac.il>
 *
E 3
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: os-convex.h,v 5.2.1.2 91/05/07 22:19:37 jsp Alpha $
E 4
I 4
 * $Id: os-convex.h,v 5.2.2.1 1992/02/09 15:10:16 jsp beta $
E 4
 *
 * Convex C220, version 7.1 definitions for Amd (automounter)
 *         from Eitan Mizrotsky <eitan@shum.huji.ac.il>
E 3
 */


/*
 * Does the compiler grok void *
 */
#undef	VOIDP
 
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
 * Byte ordering
 */
#undef ARCH_ENDIAN
#define	ARCH_ENDIAN	"big"
 
/*
 * Name of filesystem types
 */
#define	MOUNT_TYPE_UFS	MOUNT_UFS
#define MOUNT_TYPE_NFS	MOUNT_NFS
 
 
#define strrchr rindex
#define strchr  index
E 1
