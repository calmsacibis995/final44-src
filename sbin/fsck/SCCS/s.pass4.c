h46876
s 00001/00001/00109
d D 8.4 95/04/28 10:38:11 bostic 20 19
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00007/00004/00103
d D 8.3 95/04/27 11:33:07 mckusick 19 18
c add function prototypes
e
s 00001/00001/00106
d D 8.2 95/03/21 00:10:51 mckusick 18 17
c daddr_t => ufs_daddr_t
e
s 00002/00002/00105
d D 8.1 93/06/05 10:56:43 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00106
d D 5.12 92/05/27 22:45:28 mckusick 16 15
c add <sys/time.h> for dinode.h
e
s 00002/00002/00104
d D 5.11 91/11/04 22:20:35 bostic 15 14
c break FFS into UFS/FFS/LFS
e
s 00002/00000/00104
d D 5.10 90/07/20 16:51:12 mckusick 14 13
c lint (from Torek)
e
s 00001/00011/00103
d D 5.9 90/06/01 16:17:35 bostic 13 12
c new copyright notice
e
s 00007/00000/00107
d D 5.8 90/04/29 13:44:12 mckusick 12 11
c give a more informative error message for zero length directories
e
s 00015/00004/00092
d D 5.7 90/02/01 17:17:20 mckusick 11 10
c convert to BSD only copyright
e
s 00004/00004/00092
d D 5.6 90/02/01 16:17:26 mckusick 10 9
c lint and other aesthetic cleanups
e
s 00001/00003/00095
d D 5.5 89/10/24 19:05:22 mckusick 9 8
c no longer need to include time.h, vnode.h, and inode.h; just include dinode.h
e
s 00004/00002/00094
d D 5.4 89/06/26 21:42:12 mckusick 8 7
c new include file locations engendered by vnodes
e
s 00007/00000/00089
d D 5.3 86/03/05 17:14:40 mckusick 7 6
c add firewall check for bad entry in state map
e
s 00005/00001/00084
d D 5.2 86/03/05 17:12:35 mckusick 6 5
c free dup list and zero link count entries as they are used
c reinitialize dup list head and zero link count head to empty after each fs check
e
s 00008/00002/00077
d D 5.1 85/06/05 08:57:44 dist 5 4
c Add copyright
e
s 00006/00005/00073
d D 3.4 85/06/02 16:47:13 mckusick 4 3
c dynamically allocate zero link count table
e
s 00016/00010/00062
d D 3.3 85/05/31 20:08:48 mckusick 3 2
c dynamically allocate the duplicate block table
e
s 00003/00011/00069
d D 3.2 85/02/08 19:15:47 mckusick 2 1
c merge passes 5 and 6 into a single pass
e
s 00080/00000/00000
d D 3.1 84/03/31 21:03:50 mckusick 1 0
c date and time created 84/03/31 21:03:50 by mckusick
e
u
U
t
T
I 5
/*
D 11
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
D 17
 * Copyright (c) 1980, 1986 The Regents of the University of California.
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
D 13
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 13
I 13
 * %sccs.include.redist.c%
E 13
E 11
 */

E 5
I 1
#ifndef lint
D 5
static char version[] = "%W% (Berkeley) %G%";
#endif
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 11
#endif not lint
E 11
I 11
#endif /* not lint */
E 11
E 5

#include <sys/param.h>
I 16
#include <sys/time.h>
I 19

E 19
E 16
D 8
#include <sys/inode.h>
#include <sys/fs.h>
E 8
I 8
D 9
#include <sys/time.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
E 9
I 9
D 15
#include <ufs/dinode.h>
E 9
#include <ufs/fs.h>
E 15
I 15
#include <ufs/ufs/dinode.h>
#include <ufs/ffs/fs.h>
E 15
I 14
D 19
#include <stdlib.h>
E 19
I 19

#include <err.h>
E 19
#include <string.h>
I 19

E 19
E 14
E 8
#include "fsck.h"

D 19
int	pass4check();

E 19
I 19
void
E 19
pass4()
{
D 4
	register ino_t inumber, *blp;
	int n;
E 4
I 4
	register ino_t inumber;
	register struct zlncnt *zlnp;
I 12
	struct dinode *dp;
E 12
E 4
	struct inodesc idesc;
I 4
	int n;
E 4

D 20
	bzero((char *)&idesc, sizeof(struct inodesc));
E 20
I 20
	memset(&idesc, 0, sizeof(struct inodesc));
E 20
	idesc.id_type = ADDR;
	idesc.id_func = pass4check;
	for (inumber = ROOTINO; inumber <= lastino; inumber++) {
		idesc.id_number = inumber;
		switch (statemap[inumber]) {

		case FSTATE:
I 2
		case DFOUND:
E 2
			n = lncntp[inumber];
			if (n)
				adjust(&idesc, (short)n);
			else {
D 4
				for (blp = badlncnt;blp < badlnp; blp++)
					if (*blp == inumber) {
E 4
I 4
				for (zlnp = zlnhead; zlnp; zlnp = zlnp->next)
					if (zlnp->zlncnt == inumber) {
I 6
						zlnp->zlncnt = zlnhead->zlncnt;
						zlnp = zlnhead;
						zlnhead = zlnhead->next;
D 10
						free(zlnp);
E 10
I 10
						free((char *)zlnp);
E 10
E 6
E 4
						clri(&idesc, "UNREF", 1);
						break;
					}
			}
			break;

		case DSTATE:
			clri(&idesc, "UNREF", 1);
			break;

D 2
		case CLEAR:
E 2
I 2
		case DCLEAR:
I 12
			dp = ginode(inumber);
			if (dp->di_size == 0) {
				clri(&idesc, "ZERO LENGTH", 1);
				break;
			}
			/* fall through */
E 12
		case FCLEAR:
E 2
			clri(&idesc, "BAD/DUP", 1);
			break;
I 7

		case USTATE:
			break;

		default:
D 19
			errexit("BAD STATE %d FOR INODE I=%d",
E 19
I 19
			errx(EEXIT, "BAD STATE %d FOR INODE I=%d",
E 19
			    statemap[inumber], inumber);
E 7
		}
	}
D 2
	if (imax - ROOTINO - n_files != sblock.fs_cstotal.cs_nifree) {
		pwarn("FREE INODE COUNT WRONG IN SUPERBLK");
		if (preen)
			printf(" (FIXED)\n");
		if (preen || reply("FIX") == 1) {
			sblock.fs_cstotal.cs_nifree = imax - ROOTINO - n_files;
			sbdirty();
		}
	}
	flush(&dfile, &fileblk);
E 2
}

I 19
int
E 19
pass4check(idesc)
	register struct inodesc *idesc;
{
D 3
	register daddr_t *dlp;
E 3
I 3
	register struct dups *dlp;
E 3
	int nfrags, res = KEEPON;
D 18
	daddr_t blkno = idesc->id_blkno;
E 18
I 18
	ufs_daddr_t blkno = idesc->id_blkno;
E 18

	for (nfrags = idesc->id_numfrags; nfrags > 0; blkno++, nfrags--) {
D 3
		if (outrange(blkno, 1))
E 3
I 3
D 10
		if (outrange(blkno, 1)) {
E 10
I 10
		if (chkrange(blkno, 1)) {
E 10
E 3
			res = SKIP;
D 3
		else if (getbmap(blkno)) {
			for (dlp = duplist; dlp < enddup; dlp++)
				if (*dlp == blkno) {
					*dlp = *--enddup;
					return (KEEPON);
				}
			clrbmap(blkno);
			n_blks--;
E 3
I 3
D 10
		} else if (getbmap(blkno)) {
E 10
I 10
		} else if (testbmap(blkno)) {
E 10
			for (dlp = duplist; dlp; dlp = dlp->next) {
				if (dlp->dup != blkno)
					continue;
				dlp->dup = duplist->dup;
				dlp = duplist;
				duplist = duplist->next;
D 4
				free(dlp);
E 4
I 4
D 6
				/* free(dlp); */
E 6
I 6
D 10
				free(dlp);
E 10
I 10
				free((char *)dlp);
E 10
E 6
E 4
				break;
			}
			if (dlp == 0) {
				clrbmap(blkno);
				n_blks--;
			}
E 3
		}
	}
	return (res);
}
E 1
