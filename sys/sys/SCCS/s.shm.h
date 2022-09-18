h30226
s 00001/00001/00068
d D 8.6 94/01/21 17:44:37 bostic 9 8
c note Univ. of Wisconsin (map to sysv_shm.c)
e
s 00005/00000/00064
d D 8.5 94/01/21 17:25:17 bostic 8 7
c add USL's copyright notice
e
s 00000/00004/00064
d D 8.4 94/01/11 16:44:04 mckusick 7 6
c cleanup include syntax
e
s 00003/00003/00065
d D 8.3 94/01/04 16:16:46 bostic 6 5
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00001/00001/00067
d D 8.2 93/09/22 08:34:01 bostic 5 3
c changes for 4.4BSD-Lite requested by USL
e
s 00001/00001/00067
d R 8.2 93/09/21 08:10:21 bostic 4 3
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00066
d D 8.1 93/06/02 19:55:11 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00065
d D 7.2 91/02/05 17:04:07 bostic 2 1
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00068/00000/00000
d D 7.1 90/05/08 22:59:42 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
I 8
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 8
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
D 9
 * Science Department.
E 9
I 9
 * Science Department.  Originally from the University of Wisconsin.
E 9
 *
D 5
 * %sccs.include.redist.c%
E 5
I 5
 * %sccs.include.proprietary.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */

/*
 * SVID compatible shm.h file
 */
D 2
#ifndef _SHM_
#define _SHM_
E 2
I 2
D 6
#ifndef _SHM_H_
#define _SHM_H_
E 6
I 6
#ifndef _SYS_SHM_H_
#define _SYS_SHM_H_
E 6
E 2

D 7
#ifdef KERNEL
#include "ipc.h"
#else
E 7
#include <sys/ipc.h>
D 7
#endif
E 7

struct shmid_ds {
	struct	ipc_perm shm_perm;	/* operation perms */
	int	shm_segsz;		/* size of segment (bytes) */
	ushort	shm_cpid;		/* pid, creator */
	ushort	shm_lpid;		/* pid, last operation */
	short	shm_nattch;		/* no. of current attaches */
	time_t	shm_atime;		/* last attach time */
	time_t	shm_dtime;		/* last detach time */
	time_t	shm_ctime;		/* last change time */
	void	*shm_handle;		/* internal handle for shm segment */
};

/*
 * System 5 style catch-all structure for shared memory constants that
 * might be of interest to user programs.  Do we really want/need this?
 */
struct	shminfo {
	int	shmmax;		/* max shared memory segment size (bytes) */
	int	shmmin;		/* min shared memory segment size (bytes) */
	int	shmmni;		/* max number of shared memory identifiers */
	int	shmseg;		/* max shared memory segments per process */
	int	shmall;		/* max amount of shared memory (pages) */
};

/* internal "mode" bits */
#define	SHM_ALLOC	01000	/* segment is allocated */
#define	SHM_DEST	02000	/* segment will be destroyed on last detach */

/* SVID required constants (same values as system 5) */
#define	SHM_RDONLY	010000	/* read-only access */
#define	SHM_RND		020000	/* round attach address to SHMLBA boundary */

/* implementation constants */
#define	SHMLBA		CLBYTES	/* segment low boundary address multiple */
#define	SHMMMNI		512	/* maximum value for shminfo.shmmni */

#ifdef KERNEL
struct	shmid_ds	*shmsegs;
struct	shminfo		shminfo;
#endif

D 2
#endif /* _SHM_ */
E 2
I 2
D 6
#endif /* !_SHM_H_ */
E 6
I 6
#endif /* !_SYS_SHM_H_ */
E 6
E 2
E 1
