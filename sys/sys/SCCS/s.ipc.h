h05067
s 00000/00002/00051
d D 8.4 95/02/19 07:49:15 cgd 6 5
c key_t moved into types.h
e
s 00005/00000/00048
d D 8.3 94/01/21 17:25:11 bostic 5 4
c add USL's copyright notice
e
s 00003/00003/00045
d D 8.2 94/01/04 16:16:34 bostic 4 3
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00002/00002/00046
d D 8.1 93/06/02 19:53:51 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00045
d D 7.2 91/02/05 17:03:51 bostic 2 1
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00048/00000/00000
d D 7.1 90/05/08 22:59:05 mckusick 1 0
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
I 5
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 5
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * SVID compatible ipc.h file
 */
D 2
#ifndef _IPC_
#define _IPC_
E 2
I 2
D 4
#ifndef _IPC_H_
#define _IPC_H_
E 4
I 4
#ifndef _SYS_IPC_H_
#define _SYS_IPC_H_
E 4
E 2

D 6
typedef	long	key_t;	/* XXX should be in types.h */

E 6
struct ipc_perm {
	ushort	cuid;	/* creator user id */
	ushort	cgid;	/* creator group id */
	ushort	uid;	/* user id */
	ushort	gid;	/* group id */
	ushort	mode;	/* r/w permission */
	ushort	seq;	/* sequence # (to generate unique msg/sem/shm id) */
	key_t	key;	/* user specified msg/sem/shm key */
};

/* common mode bits */
#define	IPC_R		00400	/* read permission */
#define	IPC_W		00200	/* write/alter permission */

/* SVID required constants (same values as system 5) */
#define	IPC_CREAT	01000	/* create entry if key does not exist */
#define	IPC_EXCL	02000	/* fail if key exists */
#define	IPC_NOWAIT	04000	/* error if request must wait */

#define	IPC_PRIVATE	(key_t)0 /* private key */

#define	IPC_RMID	0	/* remove identifier */
#define	IPC_SET		1	/* set options */
#define	IPC_STAT	2	/* get options */

D 2
#endif /* _IPC_ */
E 2
I 2
D 4
#endif /* !_IPC_H_ */
E 4
I 4
#endif /* !_SYS_IPC_H_ */
E 4
E 2
E 1
