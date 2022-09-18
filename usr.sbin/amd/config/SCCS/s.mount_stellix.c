h35535
s 00002/00002/00048
d D 8.1 93/06/06 11:50:49 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00050/00000/00000
d D 5.1 92/07/21 13:20:51 bostic 1 0
c date and time created 92/07/21 13:20:51 by bostic
e
u
U
t
T
I 1
/*
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * IRIX Mount helper
 */

#include "misc-stellix.h"

/*
 * Map from conventional mount arguments
 * to IRIX style arguments.
 */
stellix_mount(fsname, dir, flags, type, data)
char *fsname;
char *dir;
int flags;
int type;
void *data;
{

#ifdef DEBUG
	dlog("stellix_mount: fsname %s, dir %s, type %d", fsname, dir, type);
#endif /* DEBUG */

	if (type == MOUNT_TYPE_NFS) {

		return mount(dir, dir, (MS_FSS|MS_NFS|flags),
			     type, (caddr_t) data );

	} else if (type == MOUNT_TYPE_UFS) {

		return mount(fsname, dir, (MS_FSS|flags), type);

	} else {
		return EINVAL;
	}

}
E 1
