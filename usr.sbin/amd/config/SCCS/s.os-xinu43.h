h09357
s 00002/00002/00084
d D 8.1 93/06/06 11:52:32 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00085
d D 5.4 92/02/09 08:31:44 pendry 4 3
c merge in new release
e
s 00005/00005/00081
d D 5.3 91/05/12 15:59:07 pendry 3 2
c checkpoint for network tape
e
s 00003/00001/00083
d D 5.2 91/03/17 13:50:03 pendry 2 1
c from amd5.3 alpha11
e
s 00084/00000/00000
d D 5.1 90/06/29 12:41:21 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
D 2
/* $Id: os-xinu43.h,v 5.2 90/06/23 22:21:01 jsp Rel $ */
E 2
I 2
D 3
/* $Id: os-xinu43.h,v 5.2.1.2 90/11/04 23:17:45 jsp Exp $ */
E 2

E 3
/*
D 3
 * mt Xinu 4.3 (MORE/bsd) definitions for Amd (automounter)
 * Should work on both Vax and HP ...
 *
E 3
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
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
 * $Id: os-xinu43.h,v 5.2.1.3 91/05/07 22:20:07 jsp Alpha $
E 4
I 4
 * $Id: os-xinu43.h,v 5.2.2.1 1992/02/09 15:10:58 jsp beta $
E 4
 *
 * mt Xinu 4.3 (MORE/bsd) definitions for Amd (automounter)
 * Should work on both Vax and HP ...
E 3
 */

/*
 * Does the compiler grok void *
 */
I 2
#ifdef __GNUC__
E 2
#define	VOIDP
I 2
#endif
E 2

/*
 * Which version of the Sun RPC library we are using
 * This is the implementation release number, not
 * the protocol revision number.
 */
#define	RPC_4

/*
 * mt Xinu have a compatibility problem
 * with getreq vs. getreqset.  On SunOS
 * getreqset takes a pointer to an fd_set,
 * whereas on MORE/bsd, getreq takes a
 * fd_set directly (cf. an integer on SunOS).
 */
#define	svc_getreqset(p)	svc_getreq(*p)

/*
 * Which version of the NFS interface are we using.
 * This is the implementation release number, not
 * the protocol revision number.
 */
#define	NFS_4

/*
 * Name of filesystem types
 */
#define	MOUNT_TYPE_NFS	"nfs"
#define	MOUNT_TYPE_UFS	"ufs"
#undef MTAB_TYPE_UFS
#define	MTAB_TYPE_UFS	"ufs"

/*
 * Byte ordering
 */
#ifndef BYTE_ORDER
#include <machine/endian.h>
#endif /* BYTE_ORDER */

#undef ARCH_ENDIAN
#if BYTE_ORDER == LITTLE_ENDIAN
#define ARCH_ENDIAN "little"
#else
#if BYTE_ORDER == BIG_ENDIAN
#define ARCH_ENDIAN "big"
#else
XXX - Probably no hope of running Amd on this machine!
#endif /* BIG */
#endif /* LITTLE */

/*
 * Type of a file handle
 */
#undef NFS_FH_TYPE
#define NFS_FH_TYPE     caddr_t

/*
 * Type of filesystem type
 */
#undef MTYPE_TYPE
#define	MTYPE_TYPE	char *
E 1
