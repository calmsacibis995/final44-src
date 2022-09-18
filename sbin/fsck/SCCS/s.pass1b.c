h06578
s 00001/00001/00077
d D 8.4 95/04/28 10:38:09 bostic 17 16
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00006/00001/00072
d D 8.3 95/04/27 11:32:56 mckusick 16 15
c add function prototypes
e
s 00001/00001/00072
d D 8.2 95/03/21 00:10:42 mckusick 15 14
c daddr_t => ufs_daddr_t
e
s 00002/00002/00071
d D 8.1 93/06/05 10:56:33 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00072
d D 5.10 92/05/27 22:45:21 mckusick 13 12
c add <sys/time.h> for dinode.h
e
s 00002/00002/00070
d D 5.9 91/11/04 22:20:33 bostic 12 11
c break FFS into UFS/FFS/LFS
e
s 00001/00000/00071
d D 5.8 90/07/20 16:51:43 mckusick 11 10
c lint (from Torek)
e
s 00001/00011/00070
d D 5.7 90/06/01 16:17:18 bostic 10 9
c new copyright notice
e
s 00015/00004/00066
d D 5.6 90/02/01 17:17:44 mckusick 9 8
c convert to BSD only copyright
e
s 00004/00005/00066
d D 5.5 90/02/01 16:18:03 mckusick 8 7
c lint and other aesthetic cleanups
e
s 00001/00003/00070
d D 5.4 89/10/24 19:05:42 mckusick 7 6
c no longer need to include time.h, vnode.h, and inode.h; just include dinode.h
e
s 00004/00002/00069
d D 5.3 89/06/26 21:42:04 mckusick 6 5
c new include file locations engendered by vnodes
e
s 00001/00002/00070
d D 5.2 88/05/07 00:17:08 mckusick 5 4
c eliminate unnecessary flush
e
s 00008/00002/00064
d D 5.1 85/06/05 08:56:49 dist 4 3
c Add copyright
e
s 00013/00007/00053
d D 3.3 85/05/31 20:08:45 mckusick 3 2
c dynamically allocate the duplicate block table
e
s 00002/00000/00058
d D 3.2 85/05/16 17:26:42 mckusick 2 1
c must not do ginode() on numbers less than ROOTINO
e
s 00058/00000/00000
d D 3.1 84/03/31 21:03:47 mckusick 1 0
c date and time created 84/03/31 21:03:47 by mckusick
e
u
U
t
T
I 4
/*
D 9
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
D 14
 * Copyright (c) 1980, 1986 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 10
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 9
 */

E 4
I 1
#ifndef lint
D 4
static char version[] = "%W% (Berkeley) %G%";
#endif
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9
E 4

#include <sys/param.h>
I 13
#include <sys/time.h>
I 16

E 16
E 13
D 6
#include <sys/inode.h>
#include <sys/fs.h>
E 6
I 6
D 7
#include <sys/time.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
E 7
I 7
D 12
#include <ufs/dinode.h>
E 7
#include <ufs/fs.h>
E 12
I 12
#include <ufs/ufs/dinode.h>
#include <ufs/ffs/fs.h>
I 16

E 16
E 12
I 11
#include <string.h>
I 16

E 16
E 11
E 6
#include "fsck.h"

D 16
int	pass1bcheck();
E 16
I 3
static  struct dups *duphead;
I 16
static int pass1bcheck __P((struct inodesc *));
E 16
E 3

I 16
void
E 16
pass1b()
{
	register int c, i;
D 8
	register DINODE *dp;
E 8
I 8
	register struct dinode *dp;
E 8
	struct inodesc idesc;
	ino_t inumber;

D 17
	bzero((char *)&idesc, sizeof(struct inodesc));
E 17
I 17
	memset(&idesc, 0, sizeof(struct inodesc));
E 17
	idesc.id_type = ADDR;
	idesc.id_func = pass1bcheck;
I 3
	duphead = duplist;
E 3
	inumber = 0;
	for (c = 0; c < sblock.fs_ncg; c++) {
		for (i = 0; i < sblock.fs_ipg; i++, inumber++) {
I 2
			if (inumber < ROOTINO)
				continue;
E 2
			dp = ginode(inumber);
			if (dp == NULL)
				continue;
			idesc.id_number = inumber;
			if (statemap[inumber] != USTATE &&
			    (ckinode(dp, &idesc) & STOP))
D 8
				goto out1b;
E 8
I 8
				return;
E 8
		}
	}
D 5
out1b:
	flush(&dfile, &inoblk);
E 5
I 5
D 8
out1b:;
E 8
E 5
}

I 16
static int
E 16
pass1bcheck(idesc)
	register struct inodesc *idesc;
{
D 3
	register daddr_t *dlp;
E 3
I 3
	register struct dups *dlp;
E 3
	int nfrags, res = KEEPON;
D 15
	daddr_t blkno = idesc->id_blkno;
E 15
I 15
	ufs_daddr_t blkno = idesc->id_blkno;
E 15

	for (nfrags = idesc->id_numfrags; nfrags > 0; blkno++, nfrags--) {
D 8
		if (outrange(blkno, 1))
E 8
I 8
		if (chkrange(blkno, 1))
E 8
			res = SKIP;
D 3
		for (dlp = duplist; dlp < muldup; dlp++)
			if (*dlp == blkno) {
E 3
I 3
		for (dlp = duphead; dlp; dlp = dlp->next) {
			if (dlp->dup == blkno) {
E 3
D 8
				blkerr(idesc->id_number, "DUP", blkno);
E 8
I 8
				blkerror(idesc->id_number, "DUP", blkno);
E 8
D 3
				*dlp = *--muldup;
				*muldup = blkno;
				if (muldup == duplist)
					return (STOP);
E 3
I 3
				dlp->dup = duphead->dup;
				duphead->dup = blkno;
				duphead = duphead->next;
E 3
			}
I 3
			if (dlp == muldup)
				break;
		}
		if (muldup == 0 || duphead == muldup->next)
			return (STOP);
E 3
	}
	return (res);
}
E 1
