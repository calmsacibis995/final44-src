h18260
s 00002/00002/00055
d D 8.1 93/06/06 11:50:46 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00056
d D 5.4 92/02/09 08:30:52 pendry 4 3
c merge in new release
e
s 00003/00002/00054
d D 5.3 91/05/12 15:59:15 pendry 3 2
c checkpoint for network tape
e
s 00001/00013/00055
d D 5.2 91/03/17 13:49:06 pendry 2 1
c from amd5.3 alpha11
e
s 00068/00000/00000
d D 5.1 91/03/17 11:48:58 pendry 1 0
c date and time created 91/03/17 11:48:58 by pendry
e
u
U
t
T
I 1
/*
D 3
 * $Id: mount_irix.c,v 5.2.1.1 90/10/21 22:30:59 jsp Exp $
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
I 3
 *
D 4
 * $Id: mount_irix.c,v 5.2.1.2 91/05/07 22:19:50 jsp Alpha $
E 4
I 4
 * $Id: mount_irix.c,v 5.2.2.1 1992/02/09 15:10:32 jsp beta $
E 4
 *
E 3
 */


/*
 * IRIX Mount helper
 */

#include "misc-irix.h"

/*
 * Map from conventional mount arguments
 * to IRIX style arguments.
 */
irix_mount(fsname, dir, flags, type, data)
char *fsname;
char *dir;
int flags;
int type;
void *data;
{
	int size;

#ifdef DEBUG
	dlog("irix_mount: fsname %s, dir %s, type %d", fsname, dir, type);
#endif /* DEBUG */

	if (type == MOUNT_TYPE_NFS) {

		size = sizeof (struct nfs_args);

		return mount(dir, dir, (MS_FSS|MS_DATA|flags),
			     type, (struct nfs_args *) data, size);

	} else if (type == MOUNT_TYPE_UFS) {

		return mount(fsname, dir, (MS_FSS|flags), type);

	} else {
		return EINVAL;
	}

}
E 1
