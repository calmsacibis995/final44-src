h52838
s 00002/00002/00177
d D 8.1 93/06/06 11:41:23 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00178
d D 5.4 92/02/09 08:49:03 pendry 4 3
c merge in new release
e
s 00003/00002/00176
d D 5.3 91/05/12 15:56:13 pendry 3 2
c checkpoint for network tape
e
s 00001/00001/00177
d D 5.2 91/03/17 13:34:06 pendry 2 1
c from amd5.3 alpha11
e
s 00178/00000/00000
d D 5.1 90/06/29 12:01:19 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: srvr_afs.c,v 5.2 90/06/23 22:20:00 jsp Rel $
E 2
I 2
D 3
 * $Id: srvr_afs.c,v 5.2.1.1 90/10/21 22:29:44 jsp Exp $
E 2
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
 * $Id: srvr_afs.c,v 5.2.1.2 91/05/07 22:18:35 jsp Alpha $
E 4
I 4
 * $Id: srvr_afs.c,v 5.2.2.1 1992/02/09 15:09:05 jsp beta $
E 4
 *
E 3
 */

/*
 * Automount FS server ("localhost") modeling
 */

#include "am.h"

extern qelem afs_srvr_list;
qelem afs_srvr_list = { &afs_srvr_list, &afs_srvr_list };

static fserver *localhost;

/*
 * Find an nfs server for the local host
 */
fserver *find_afs_srvr P((mntfs *));
fserver *find_afs_srvr(mf)
mntfs *mf;
{
	fserver *fs = localhost;

	if (!fs) {
		fs = ALLOC(fserver);
		fs->fs_refc = 0;
		fs->fs_host = strdup("localhost");
		fs->fs_ip = 0;
		fs->fs_cid = 0;
		fs->fs_pinger = 0;
		fs->fs_flags = FSF_VALID;
		fs->fs_type = "local";
		fs->fs_private = 0;
		fs->fs_prfree = 0;

		ins_que(&fs->fs_q, &afs_srvr_list);

		srvrlog(fs, "starts up");

		localhost = fs;
	}

	fs->fs_refc++;

	return fs;
}

/*------------------------------------------------------------------*/
		/* Generic routines follow */

/*
 * Wakeup anything waiting for this server
 */
void wakeup_srvr P((fserver *fs));
void wakeup_srvr(fs)
fserver *fs;
{
	fs->fs_flags &= ~FSF_WANT;
	wakeup((voidp) fs);
}

/*
 * Called when final ttl of server has expired
 */
static void timeout_srvr P((fserver *fs));
static void timeout_srvr(fs)
fserver *fs;
{
	/*
	 * If the reference count is still zero then
	 * we are free to remove this node
	 */
	if (fs->fs_refc == 0) {
#ifdef DEBUG
		dlog("Deleting file server %s", fs->fs_host);
#endif /* DEBUG */
		if (fs->fs_flags & FSF_WANT)
			wakeup_srvr(fs);

		/*
		 * Remove from queue.
		 */
		rem_que(&fs->fs_q);
		/*
		 * (Possibly) call the private free routine.
		 */
		if (fs->fs_private && fs->fs_prfree)
			(*fs->fs_prfree)(fs->fs_private);

		/*
		 * Free the net address
		 */
		if (fs->fs_ip)
			free((voidp) fs->fs_ip);

		/*
		 * Free the host name.
		 */
		free((voidp) fs->fs_host);

		/*
		 * Discard the fserver object.
		 */
		free((voidp) fs);
	}
}

/*
 * Free a file server
 */
void free_srvr P((fserver *fs));
void free_srvr(fs)
fserver *fs;
{
	if (--fs->fs_refc == 0) {
		/*
		 * The reference count is now zero,
		 * so arrange for this node to be
		 * removed in AM_TTL seconds if no
		 * other mntfs is referencing it.
		 */
		int ttl = (fs->fs_flags & (FSF_DOWN|FSF_ERROR)) ? 19 : AM_TTL;
#ifdef DEBUG
		dlog("Last hard reference to file server %s - will timeout in %ds", fs->fs_host, ttl);
#endif /* DEBUG */
		if (fs->fs_cid) {
			untimeout(fs->fs_cid);
			/*
			 * Turn off pinging - XXX
			 */
			fs->fs_flags &= ~FSF_PINGING;
		}
		/*
		 * Keep structure lying around for a while
		 */
		fs->fs_cid = timeout(ttl, timeout_srvr, (voidp) fs);
		/*
		 * Mark the fileserver down and invalid again
		 */
		fs->fs_flags &= ~FSF_VALID;
		fs->fs_flags |= FSF_DOWN;
	}
}

/*
 * Make a duplicate fserver reference
 */
fserver *dup_srvr P((fserver *fs));
fserver *dup_srvr(fs)
fserver *fs;
{
	fs->fs_refc++;
	return fs;
}

/*
 * Log state change
 */
void srvrlog P((fserver *fs, char *state));
void srvrlog(fs, state)
fserver *fs;
char *state;
{
	plog(XLOG_INFO, "file server %s type %s %s", fs->fs_host, fs->fs_type, state);
}
E 1
