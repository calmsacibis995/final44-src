h28341
s 00002/00002/00061
d D 8.1 93/06/06 11:51:34 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00062
d D 5.4 92/02/09 08:31:20 pendry 4 3
c merge in new release
e
s 00004/00004/00059
d D 5.3 91/05/12 15:59:12 pendry 3 2
c checkpoint for network tape
e
s 00003/00002/00060
d D 5.2 91/03/17 13:49:35 pendry 2 1
c from amd5.3 alpha11
e
s 00062/00000/00000
d D 5.1 90/06/29 12:41:15 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
D 2
/* $Id: os-hlh42.h,v 5.2 90/06/23 22:20:46 jsp Rel $ */
E 2
I 2
D 3
/* $Id: os-hlh42.h,v 5.2.1.2 90/11/04 23:17:40 jsp Exp $ */
E 2

E 3
/*
D 3
 * HLH OTS definitions for Amd (automounter)
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
 * $Id: os-hlh42.h,v 5.2.1.3 91/05/07 22:19:42 jsp Alpha $
E 4
I 4
 * $Id: os-hlh42.h,v 5.2.2.1 1992/02/09 15:10:22 jsp beta $
E 4
 *
 * HLH OTS definitions for Amd (automounter)
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
#if defined(hlh)
#define	ARCH_ENDIAN	"little"
#endif

/*
 * Name of filesystem types
 */
#define	MOUNT_TYPE_NFS	MOUNT_NFS
#define	MOUNT_TYPE_UFS	MOUNT_UFS

/*
 * Miscellaneous HLH 4.2 incantations
 */
#define	strchr	index
#define strrchr	rindex
#define sigmask(x)	(1 << ((x)-1))

/*
 * HLH's 4.2 needs the extra RPC definitions.
 */
D 2
#define MISC_RPC
E 2
I 2
#define NEED_XDR_POINTER
#define	NEED_CLNT_SPERRNO
E 2
E 1
