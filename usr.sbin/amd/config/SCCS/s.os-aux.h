h20684
s 00002/00002/00089
d D 8.1 93/06/06 11:51:09 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00090
d D 5.4 92/02/09 08:31:05 pendry 4 3
c merge in new release
e
s 00005/00005/00086
d D 5.3 91/05/12 15:58:53 pendry 3 2
c checkpoint for network tape
e
s 00001/00006/00090
d D 5.2 91/03/17 13:49:20 pendry 2 1
c from amd5.3 alpha11
e
s 00096/00000/00000
d D 5.1 90/06/29 12:41:09 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
D 2
/* $Id: os-aux.h,v 5.2 90/06/23 22:20:37 jsp Rel $ */
E 2
I 2
D 3
/* $Id: os-aux.h,v 5.2.1.1 90/10/21 22:30:42 jsp Exp $ */
E 2

E 3
/*
D 3
 * A/UX macII definitions for Amd (automounter)
 * Contributed by Julian Onions <jpo@cs.nott.ac.uk>
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
 * $Id: os-aux.h,v 5.2.1.2 91/05/07 22:19:31 jsp Alpha $
E 4
I 4
 * $Id: os-aux.h,v 5.2.2.1 1992/02/09 15:10:10 jsp beta $
E 4
 *
 * A/UX macII definitions for Amd (automounter)
 * Contributed by Julian Onions <jpo@cs.nott.ac.uk>
E 3
 */

/*
 * Does the compiler grok void *
 */
#define	VOIDP

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
D 2

/*
 * Has support for syslog()
 */
#define HAS_SYSLOG
E 2

/*
 * No support for ndbm
 */
#undef OS_HAS_NDBM

/*
 * Name of filesystem types
 */
#define	MOUNT_TYPE_UFS	MOUNT_UFS
#define MOUNT_TYPE_NFS MOUNT_NFS

#undef MTAB_TYPE_UFS
#define	MTAB_TYPE_UFS	"5.2"

#define SIGCHLD	SIGCLD
#define	SYS5_SIGNALS

/*
 * Use <fcntl.h> rather than <sys/file.h>
 */
#define USE_FCNTL

/*
 * Use fcntl() rather than flock()
 */
#define LOCK_FCNTL

#ifdef __GNUC__
#define alloca(sz) __builtin_alloca(sz)
#endif

#define	bzero(ptr, len)	memset(ptr, 0, len)
#define bcopy(from, to, len) memcpy(to, from, len)
#define getpagesize() (2048)
#undef MOUNT_TRAP
#define MOUNT_TRAP(type, mnt, flags, mnt_data) \
	fsmount(type, mnt->mnt_dir, flags, mnt_data)
#undef UNMOUNT_TRAP
#define	UNMOUNT_TRAP(mnt)	unmount(mnt->mnt_dir)
#define NFDS	30	/* conservative */

/* not included in sys/param.h */
#include <sys/types.h>
/* not part of sys/time.h */
#include <time.h>
/* for NMOUNT */
#include <sys/config.h>
E 1
