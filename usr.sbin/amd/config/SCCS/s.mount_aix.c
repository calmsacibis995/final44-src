h11088
s 00002/00002/00125
d D 8.1 93/06/06 11:50:43 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00126
d D 5.4 92/02/09 08:30:50 pendry 4 3
c merge in new release
e
s 00003/00002/00124
d D 5.3 91/05/12 15:58:47 pendry 3 2
c checkpoint for network tape
e
s 00001/00013/00125
d D 5.2 91/03/17 13:49:04 pendry 2 1
c from amd5.3 alpha11
e
s 00138/00000/00000
d D 5.1 91/03/17 11:48:57 pendry 1 0
c date and time created 91/03/17 11:48:57 by pendry
e
u
U
t
T
I 1
/*
D 3
 * $Id: mount_aix.c,v 5.2.1.1 90/10/21 22:30:41 jsp Exp $
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
 * $Id: mount_aix.c,v 5.2.1.2 91/05/07 22:19:30 jsp Alpha $
E 4
I 4
 * $Id: mount_aix.c,v 5.2.2.1 1992/02/09 15:10:08 jsp beta $
E 4
 *
E 3
 */


/*
 * AIX 3 Mount helper
 */

#include "misc-aix3.h"

static int aix3_mkvp(p, gfstype, flags, object, stub, host, info, info_size, args)
char *p;
int gfstype;
int flags;
char *object;
char *stub;
char *host;
char *info;
int info_size;
char *args;
{
	struct vmount *vp = (struct vmount *) p;
	bzero((voidp) vp, sizeof(*vp));
	/*
	 * Fill in standard fields
	 */
	vp->vmt_revision = VMT_REVISION;
	vp->vmt_flags = flags;
	vp->vmt_gfstype = gfstype;

#define	VMT_ROUNDUP(len) (4 * ((len + 3) / 4))
#define VMT_ASSIGN(vp, idx, data, size) \
	vp->vmt_data[idx].vmt_off = p - (char *) vp; \
	vp->vmt_data[idx].vmt_size = size; \
	bcopy(data, p, size); \
	p += VMT_ROUNDUP(size);

	/*
	 * Fill in all variable length data
	 */
	p += sizeof(*vp);

	VMT_ASSIGN(vp, VMT_OBJECT, object, strlen(object) + 1);
	VMT_ASSIGN(vp, VMT_STUB, stub, strlen(stub) + 1);
	VMT_ASSIGN(vp, VMT_HOST, host, strlen(host) + 1);
	VMT_ASSIGN(vp, VMT_HOSTNAME, host, strlen(host) + 1);
	VMT_ASSIGN(vp, VMT_INFO, info, info_size);
	VMT_ASSIGN(vp, VMT_ARGS, args, strlen(args) + 1);

#undef VMT_ASSIGN
#undef VMT_ROUNDUP

	/*
	 * Return length
	 */
	return vp->vmt_length = p - (char *) vp;
}

/*
 * Map from conventional mount arguments
 * to AIX 3-style arguments.
 */
aix3_mount(fsname, dir, flags, type, data, args)
char *fsname;
char *dir;
int flags;
int type;
void *data;
char *args;
{
	char buf[4096];
	int size;

#ifdef DEBUG
	dlog("aix3_mount: fsname %s, dir %s, type %d", fsname, dir, type);
#endif /* DEBUG */

/* aix3_mkvp(p, gfstype, flags, object, stub, host, info, info_size, args) */

	switch (type) {

	case MOUNT_TYPE_NFS: {
		char *host = strdup(fsname);
		char *rfs = strchr(host, ':');
		int free_rfs = 0;
		if (rfs) {
			*rfs++ = '\0';
		} else {
			rfs = host;
			free_rfs = 1;
			host = strdup(hostname);
		}

		size = aix3_mkvp(buf, type, flags, rfs, dir, host, data, sizeof(struct nfs_args), args);
		if (free_rfs)
			free((voidp) rfs);
		free(host);

		} break;

	case MOUNT_TYPE_UFS:
		/* Need to open block device and extract log device info from sblk. */
		return EINVAL;

	default:
		return EINVAL;
	}
#ifdef DEBUG
	/*dlog("aix3_mkvp: flags %#x, size %d, args %s", flags, size, args);*/
#endif /* DEBUG */

	return vmount(buf, size);
}
E 1
