h44272
s 00002/00002/00053
d D 8.1 93/06/06 11:51:31 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00054
d D 5.4 92/02/09 08:31:18 pendry 4 3
c merge in new release
e
s 00003/00004/00052
d D 5.3 91/05/12 15:58:59 pendry 3 2
c checkpoint for network tape
e
s 00001/00013/00055
d D 5.2 91/03/17 13:49:33 pendry 2 1
c from amd5.3 alpha11
e
s 00068/00000/00000
d D 5.1 91/03/17 11:49:02 pendry 1 0
c date and time created 91/03/17 11:49:02 by pendry
e
u
U
t
T
I 1
D 3
/* $Id: os-hcx.h,v 5.2 91/01/27 20:13:28 jsp Alpha $ */

E 3
/*
D 3
 * Harris HCX/UX Release 3.0 definitions for Amd (automounter)
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
D 2
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
 *
I 3
D 4
 * $Id: os-hcx.h,v 5.2.1.1 91/05/07 22:19:41 jsp Alpha $
E 4
I 4
 * $Id: os-hcx.h,v 5.2.2.1 1992/02/09 15:10:20 jsp beta $
E 4
 *
 * Harris HCX/UX Release 3.0 definitions for Amd (automounter)
E 3
 */

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
 * Deviant call necessary.  The mount() routine in libc only works for UFS
 * (it's a backward-compatible piece of C code which traps to mountsyscall).
 */
#undef MOUNT_TRAP
#define	MOUNT_TRAP(type, mnt, flags, mnt_data) \
	mountsyscall(type, mnt->mnt_dir, flags, mnt_data)

/*
 * Name of filesystem types
 */
#define	MOUNT_TYPE_NFS	MOUNT_NFS
#define	MOUNT_TYPE_UFS	MOUNT_UFS

/*
 * Byte ordering
 */
#undef ARCH_ENDIAN
#ifdef _hcx
#define ARCH_ENDIAN "big"
#else
XXX - bizarre!
#endif
E 1
