h56335
s 00002/00002/00115
d D 8.1 93/06/06 11:51:21 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00116
d D 5.4 92/02/09 08:31:12 pendry 4 3
c merge in new release
e
s 00006/00006/00111
d D 5.3 91/05/12 15:58:57 pendry 3 2
c checkpoint for network tape
e
s 00016/00001/00101
d D 5.2 91/03/17 13:49:27 pendry 2 1
c from amd5.3 alpha11
e
s 00102/00000/00000
d D 5.1 90/06/29 12:41:12 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
D 2
/* $Id: os-defaults.h,v 5.2 90/06/23 22:20:44 jsp Rel $ */
E 2
I 2
D 3
/* $Id: os-defaults.h,v 5.2.1.2 91/03/03 20:49:12 jsp Alpha $ */
E 2

E 3
/*
D 3
 * Common OS definitions.  These may be overridden in
 * the OS specific files ("os-foo.h").
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
 * $Id: os-defaults.h,v 5.2.1.4 91/05/07 22:19:38 jsp Alpha $
E 4
I 4
 * $Id: os-defaults.h,v 5.2.2.1 1992/02/09 15:10:17 jsp beta $
E 4
 *
 * Common OS definitions.  These may be overridden in
 * the OS specific files ("os-foo.h").
E 3
 */

/*
 * What level of AMD are we backward compatible with?
 * This only applies to externally visible characteristics.
 * Rev.Minor.Branch.Patch (2 digits each)
 */
#define	AMD_COMPAT	5000000		/* 5.0 */

/*
 * What type is free(void*) returning?
 */
#define FREE_RETURN_TYPE	void

/*
 * Is the mount table mirrored in software
 */
#define	UPDATE_MTAB

/*
 * Where to get union wait
 */
#define	WAIT	<sys/wait.h>

/*
 * Where to get mount entry info
 */
#define	MNTENT_HDR	<mntent.h>

/*
 * Include support for syslog()
 */
#define	HAS_SYSLOG

/*
 * Byte ordering
 */
#define	ARCH_ENDIAN	"unknown"

/*
 * Name of filesystem types
 */
#define	MTAB_TYPE_NFS	"nfs"
#define	MTAB_TYPE_UFS	"4.2"

/*
 * Name of mount & unmount system calls
 *
 * NOTE:
 *  UNMOUNT_TRAP takes a struct mntent *
 */
#define	MOUNT_TRAP(type, mnt, flags, mnt_data) \
	mount(type, mnt->mnt_dir, flags, mnt_data)
#define	UNMOUNT_TRAP(mnt)	unmount(mnt->mnt_dir)

/*
 * How to unmount filesystems.
 * NEED_UMOUNT_FS includes code to scan the mount table
 * to find the correct information for the unmount system
 * call.  Some systems, such as 4.4bsd, do not require
 * this - they can just do an unmount system call directly.
 */
#define	NEED_UMOUNT_FS
#define	UMOUNT_FS(dir)	umount_fs(dir)

/*
 * Type of a file handle
 */
#define	NFS_FH_TYPE	fhandle_t *
#define	NFS_FH_DREF(dst, src) { (dst) = (src); }

/*
 * How to copy an address into an NFS filehandle
 */
#define	NFS_SA_DREF(dst, src) { (dst).addr = (src); }

/*
 * Type of filesystem type
 */
#define	MTYPE_TYPE	int

/*
 * How to get a mount list
 */
#define	READ_MTAB_FROM_FILE
I 2

/*
 * Make Amd automount points appear
 * to be zero sized.  undef this
 * if the O/S has a divide by zero
 * problem in df et al.
 */
#define	HAS_EMPTY_AUTOMOUNTS

/*
 * For the RE matcher
 */
#define	CHARBITS 0377
#define STRCSPN
D 3
#define	RE_HDR "re.h"
E 3
I 3
#define RE_HDR "re.h"
E 3
E 2
E 1
