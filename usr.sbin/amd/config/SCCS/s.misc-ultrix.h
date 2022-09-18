h38946
s 00002/00002/00027
d D 8.1 93/06/06 11:50:41 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00028
d D 5.4 92/02/09 08:30:48 pendry 4 3
c merge in new release
e
s 00003/00002/00026
d D 5.3 91/05/12 15:59:15 pendry 3 2
c checkpoint for network tape
e
s 00001/00001/00027
d D 5.2 91/03/17 13:49:02 pendry 2 1
c from amd5.3 alpha11
e
s 00028/00000/00000
d D 5.1 90/06/29 12:41:07 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: misc-ultrix.h,v 5.2 90/06/23 22:20:56 jsp Rel $
E 2
I 2
D 3
 * $Id: misc-ultrix.h,v 5.2.1.1 90/10/21 22:31:08 jsp Exp $
E 2
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
 * $Id: misc-ultrix.h,v 5.2.1.2 91/05/07 22:20:01 jsp Alpha $
E 4
I 4
 * $Id: misc-ultrix.h,v 5.2.2.1 1992/02/09 15:10:49 jsp beta $
E 4
 *
E 3
 */

#include        <nfs/nfs_gfs.h>
#define KERNEL
#include        <sys/fs_types.h>
#undef  KERNEL

#ifndef HOSTNAMESZ
#include <nfs/nfs_clnt.h>
#endif

#include <ufs/ufs_mount.h>

#define	ufs_args ufs_specific
E 1
