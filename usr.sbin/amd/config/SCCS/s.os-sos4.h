h60145
s 00002/00002/00088
d D 8.1 93/06/06 11:52:03 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00089
d D 5.4 92/02/09 08:31:31 pendry 4 3
c merge in new release
e
s 00004/00004/00086
d D 5.3 91/05/12 15:59:02 pendry 3 2
c checkpoint for network tape
e
s 00010/00001/00080
d D 5.2 91/03/17 13:49:49 pendry 2 1
c from amd5.3 alpha11
e
s 00081/00000/00000
d D 5.1 90/06/29 12:41:18 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
D 2
/* $Id: os-sos4.h,v 5.2 90/06/23 22:20:52 jsp Rel $ */
E 2
I 2
D 3
/* $Id: os-sos4.h,v 5.2.1.2 91/03/03 20:50:41 jsp Alpha $ */
E 2

E 3
/*
D 3
 * SunOS 4.0 definitions for Amd (automounter)
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
 * $Id: os-sos4.h,v 5.2.1.3 91/05/07 22:19:57 jsp Alpha $
E 4
I 4
 * $Id: os-sos4.h,v 5.2.2.1 1992/02/09 15:10:41 jsp beta $
E 4
 *
 * SunOS 4.0 definitions for Amd (automounter)
E 3
 */

/*
 * Does the compiler grok void *
 */
#define	VOIDP

/*
 * What type is free(void*) returning?
 */
#undef FREE_RETURN_TYPE
#define FREE_RETURN_TYPE	int

/*
 * Which version of the Sun RPC library we are using
 * This is the implementation release number, not
 * the protocol revision number.
 */
#define	RPC_4

/*
 * Which version of the NFS interface are we using.
 * This is the implementation release number, not
 * the protocol revision number.
 */
#define	NFS_4

/*
 * Does this OS have NDBM support?
 */
#define OS_HAS_NDBM

/*
 * Byte ordering
 */
#undef ARCH_ENDIAN
#if defined(mc68010) || defined(mc68020) || defined(sparc)
#define	ARCH_ENDIAN	"big"
#endif
#if defined(i386)
#define ARCH_ENDIAN	"little"
#endif

/*
 * Name of filesystem types
 */
#define MOUNT_TYPE_NFS	"nfs"
#define MOUNT_TYPE_UFS	"4.2"

/*
 * Type of a file handle
 */
#undef NFS_FH_TYPE
#define	NFS_FH_TYPE	caddr_t

/*
 * Type of filesystem type
 */
#undef MTYPE_TYPE
#define	MTYPE_TYPE	char *

/*
 * Add support for SunOS 4 automounter files
 */
#define	SUNOS4_COMPAT
I 2

/*
 * System Vr4 / SunOS 4.1 compatibility
 * - put dev= in the options list
 *
 * From: Brent Callaghan <brent@eng.sun.com>
 */
#define	MNTINFO_DEV	"dev"
#define MNTINFO_PREF	""
E 2
E 1
