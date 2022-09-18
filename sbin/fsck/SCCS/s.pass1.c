h33991
s 00004/00005/00290
d D 8.6 95/04/28 10:38:08 bostic 35 34
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00002/00001/00293
d D 8.5 95/04/27 11:49:22 mckusick 34 33
c check for more limited possible directory size
e
s 00013/00008/00281
d D 8.4 95/04/27 11:32:53 mckusick 33 32
c add function prototypes
e
s 00006/00006/00283
d D 8.3 95/03/21 00:10:41 mckusick 32 31
c daddr_t => ufs_daddr_t
e
s 00003/00002/00286
d D 8.2 95/01/06 17:30:16 mckusick 31 29
c avoid reading partial sectors when reading symbolic links (from mycroft)
e
s 00016/00004/00284
d D 8.1.1.1 94/08/31 15:31:35 mckusick 30 29
c more information on bad indirect blocks
e
s 00002/00002/00286
d D 8.1 93/06/05 10:56:30 bostic 29 28
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00286
d D 5.21 93/03/23 10:03:47 mckusick 28 27
c lint
e
s 00021/00004/00266
d D 5.20 93/01/25 14:02:17 mckusick 27 26
c bugs, fix check for symlinks that cover indirect blocks
e
s 00141/00108/00129
d D 5.19 92/07/02 16:44:26 mckusick 26 25
c code to convert ouid/ogid to uid/gid; convert short symlinks
e
s 00003/00002/00234
d D 5.18 92/06/02 21:38:56 mckusick 25 24
c size now has to be printed out as a quad
e
s 00002/00002/00234
d D 5.17 91/11/04 22:20:32 bostic 24 23
c break FFS into UFS/FFS/LFS
e
s 00002/00002/00234
d D 5.16 91/03/19 15:36:06 mckusick 23 22
c fix sign-post bug
e
s 00013/00011/00223
d D 5.15 90/07/20 16:51:35 mckusick 22 21
c lint (from Torek)
e
s 00001/00011/00233
d D 5.14 90/06/01 16:17:08 bostic 21 20
c new copyright notice
e
s 00004/00001/00240
d D 5.13 90/04/29 13:45:12 mckusick 20 19
c mark zero length directories as DCLEAR so that they will be questioned
c in pass2 and if not removed, offered for deletion in pass4
e
s 00004/00000/00237
d D 5.12 90/03/13 16:44:09 mckusick 19 18
c have to really get the inode before it can be modified
e
s 00004/00001/00233
d D 5.11 90/02/07 00:10:53 mckusick 18 17
c use special routine to scan inode list
e
s 00005/00002/00229
d D 5.10 90/02/01 23:36:17 mckusick 17 16
c save block pointers of directories as they are encountered in pass1
c so that they do not have to be reread when descending in pass2
e
s 00015/00004/00216
d D 5.9 90/02/01 17:17:34 mckusick 16 15
c convert to BSD only copyright
e
s 00015/00013/00205
d D 5.8 90/02/01 16:17:52 mckusick 15 14
c lint and other aesthetic cleanups
e
s 00001/00003/00217
d D 5.7 89/10/24 19:05:35 mckusick 14 13
c no longer need to include time.h, vnode.h, and inode.h; just include dinode.h
e
s 00004/00002/00216
d D 5.6 89/06/26 21:42:02 mckusick 13 12
c new include file locations engendered by vnodes
e
s 00006/00000/00212
d D 5.5 89/03/02 15:01:47 mckusick 12 11
c firewall for files that are too large
e
s 00002/00001/00210
d D 5.4 87/04/09 10:36:09 mckusick 11 10
c more stringent test on negative size (from chris@maryland.edu - 4.2BSD/etc/36)
e
s 00007/00006/00204
d D 5.3 86/05/13 16:36:06 mckusick 10 9
c must check for bad block earlier
e
s 00002/00000/00208
d D 5.2 86/03/05 17:15:22 mckusick 9 8
c must define state of unknown type inodes
e
s 00008/00002/00200
d D 5.1 85/06/05 08:56:24 dist 8 7
c Add copyright
e
s 00007/00003/00195
d D 3.7 85/06/02 16:47:07 mckusick 7 6
c dynamically allocate zero link count table
e
s 00016/00010/00182
d D 3.6 85/05/31 20:08:40 mckusick 6 5
c dynamically allocate the duplicate block table
e
s 00008/00006/00184
d D 3.5 85/02/15 12:07:02 mckusick 5 4
c filesize now set by ckinode(); pass1() uses id_entryno to calc block count
e
s 00001/00002/00189
d D 3.4 85/02/11 18:29:20 mckusick 4 3
c ginode() succeeds or exits
e
s 00081/00118/00110
d D 3.3 85/02/08 19:15:35 mckusick 3 2
c merge passes 5 and 6 into a single pass
e
s 00036/00019/00192
d D 3.2 85/02/07 17:52:06 mckusick 2 1
c code reorganization and cleanup
e
s 00211/00000/00000
d D 3.1 84/03/31 21:03:45 mckusick 1 0
c date and time created 84/03/31 21:03:45 by mckusick
e
u
U
f b 
t
T
I 8
/*
D 16
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 16
I 16
D 29
 * Copyright (c) 1980, 1986 The Regents of the University of California.
 * All rights reserved.
E 29
I 29
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 29
 *
D 21
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
E 21
I 21
 * %sccs.include.redist.c%
E 21
E 16
 */

E 8
I 1
#ifndef lint
D 8
static char version[] = "%W% (Berkeley) %G%";
#endif
E 8
I 8
static char sccsid[] = "%W% (Berkeley) %G%";
D 16
#endif not lint
E 16
I 16
#endif /* not lint */
E 16
E 8

#include <sys/param.h>
I 25
#include <sys/time.h>
I 33

E 33
E 25
D 13
#include <sys/inode.h>
#include <sys/fs.h>
E 13
I 13
D 14
#include <sys/time.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
E 14
I 14
D 24
#include <ufs/dinode.h>
E 14
#include <ufs/fs.h>
E 24
I 24
#include <ufs/ufs/dinode.h>
I 26
#include <ufs/ufs/dir.h>
E 26
#include <ufs/ffs/fs.h>
E 24
I 22
D 33
#include <stdlib.h>
E 33
I 33

#include <err.h>
E 33
#include <string.h>
I 33

E 33
E 22
E 13
#include "fsck.h"

D 3
int	pass1check();
E 3
I 3
D 32
static daddr_t badblk;
static daddr_t dupblk;
E 32
I 32
static ufs_daddr_t badblk;
static ufs_daddr_t dupblk;
E 32
D 33
int pass1check();
I 18
struct dinode *getnextinode();
E 33
I 33
static void checkinode __P((ino_t inumber, struct inodesc *));
E 33
E 18
E 3

I 33
void
E 33
pass1()
{
D 3
	register int c, i, n, j;
E 3
I 3
D 26
	register int c, i, j;
E 3
D 15
	register DINODE *dp;
E 15
I 15
	register struct dinode *dp;
E 15
I 7
	struct zlncnt *zlnp;
E 7
D 2
	int ndb, partial;
E 2
I 2
D 15
	int ndb, partial, cgd;
E 15
I 15
	int ndb, cgd;
E 15
E 2
	struct inodesc idesc;
E 26
	ino_t inumber;
I 26
	int c, i, cgd;
	struct inodesc idesc;
E 26

I 2
	/*
	 * Set file system reserved blocks in used block map.
	 */
	for (c = 0; c < sblock.fs_ncg; c++) {
		cgd = cgdmin(&sblock, c);
		if (c == 0) {
			i = cgbase(&sblock, c);
			cgd += howmany(sblock.fs_cssize, sblock.fs_fsize);
		} else
			i = cgsblock(&sblock, c);
		for (; i < cgd; i++)
			setbmap(i);
	}
	/*
	 * Find all allocated blocks.
	 */
E 2
D 35
	bzero((char *)&idesc, sizeof(struct inodesc));
E 35
I 35
	memset(&idesc, 0, sizeof(struct inodesc));
E 35
	idesc.id_type = ADDR;
	idesc.id_func = pass1check;
	inumber = 0;
D 3
	n_blks += howmany(sblock.fs_cssize, sblock.fs_fsize);
E 3
I 3
	n_files = n_blks = 0;
I 18
	resetinodebuf();
E 18
E 3
	for (c = 0; c < sblock.fs_ncg; c++) {
D 3
		if (getblk(&cgblk, cgtod(&sblock, c), sblock.fs_cgsize) == 0)
			continue;
		if (cgrp.cg_magic != CG_MAGIC) {
			pfatal("CG %d: BAD MAGIC NUMBER\n", c);
			bzero((char *)&cgrp, (int)sblock.fs_cgsize);
		}
		n = 0;
E 3
		for (i = 0; i < sblock.fs_ipg; i++, inumber++) {
D 3
			dp = ginode(inumber);
			if (dp == NULL)
E 3
I 3
			if (inumber < ROOTINO)
E 3
				continue;
D 3
			n++;
D 2
			if (ALLOC) {
E 2
I 2
			if (ALLOC(dp)) {
E 2
				if (!isset(cgrp.cg_iused, i)) {
					if (debug)
						printf("%d bad, not used\n",
						    inumber);
					inosumbad++;
				}
				n--;
				lastino = inumber;
				if (!preen && (dp->di_mode & IFMT) == IFMT &&
				    reply("HOLD BAD BLOCK") == 1) {
					dp->di_size = sblock.fs_fsize;
					dp->di_mode = IFREG|0600;
					inodirty();
				} else if (ftypeok(dp) == 0)
					goto unknown;
				if (dp->di_size < 0) {
					if (debug)
						printf("bad size %d:",
							dp->di_size);
					goto unknown;
				}
				ndb = howmany(dp->di_size, sblock.fs_bsize);
D 2
				if (SPECIAL)
E 2
I 2
				if (SPECIAL(dp))
E 2
					ndb++;
				for (j = ndb; j < NDADDR; j++)
					if (dp->di_db[j] != 0) {
						if (debug)
							printf("bad direct addr: %d\n",
								dp->di_db[j]);
						goto unknown;
					}
				for (j = 0, ndb -= NDADDR; ndb > 0; j++)
					ndb /= NINDIR(&sblock);
				for (; j < NIADDR; j++)
					if (dp->di_ib[j] != 0) {
						if (debug)
							printf("bad indirect addr: %d\n",
								dp->di_ib[j]);
						goto unknown;
					}
				n_files++;
				lncntp[inumber] = dp->di_nlink;
				if (dp->di_nlink <= 0) {
					if (badlnp < &badlncnt[MAXLNCNT])
						*badlnp++ = inumber;
					else {
						pfatal("LINK COUNT TABLE OVERFLOW");
						if (reply("CONTINUE") == 0)
							errexit("");
					}
				}
D 2
				statemap[inumber] = DIRCT ? DSTATE : FSTATE;
E 2
I 2
				statemap[inumber] = DIRCT(dp) ? DSTATE : FSTATE;
E 2
				badblk = dupblk = 0; maxblk = 0;
				idesc.id_number = inumber;
				idesc.id_filesize = 0;
				(void)ckinode(dp, &idesc);
				idesc.id_filesize *= btodb(sblock.fs_fsize);
				if (dp->di_blocks != idesc.id_filesize) {
					pwarn("INCORRECT BLOCK COUNT I=%u (%ld should be %ld)",
					    inumber, dp->di_blocks,
					    idesc.id_filesize);
					if (preen)
						printf(" (CORRECTED)\n");
					else if (reply("CORRECT") == 0)
						continue;
					dp->di_blocks = idesc.id_filesize;
					inodirty();
				}
E 3
I 3
D 4
			if ((dp = ginode(inumber)) == NULL)
E 3
				continue;
E 4
I 4
D 18
			dp = ginode(inumber);
E 18
I 18
D 26
			dp = getnextinode(inumber);
E 18
E 4
D 3
		unknown:
				pfatal("UNKNOWN FILE TYPE I=%u", inumber);
				if (reply("CLEAR") == 1) {
					zapino(dp);
					inodirty();
					inosumbad++;
				}
			} else {
				if (isset(cgrp.cg_iused, i)) {
					if (debug)
						printf("%d bad, marked used\n",
						    inumber);
					inosumbad++;
					n--;
				}
				partial = 0;
				for (j = 0; j < NDADDR; j++)
					if (dp->di_db[j] != 0)
						partial++;
				for (j = 0; j < NIADDR; j++)
					if (dp->di_ib[j] != 0)
						partial++;
				if (partial || dp->di_mode != 0 ||
				    dp->di_size != 0) {
E 3
I 3
D 15
			if (!ALLOC(dp)) {
E 15
I 15
			if ((dp->di_mode & IFMT) == 0) {
E 15
				if (bcmp((char *)dp->di_db, (char *)zino.di_db,
					NDADDR * sizeof(daddr_t)) ||
				    bcmp((char *)dp->di_ib, (char *)zino.di_ib,
					NIADDR * sizeof(daddr_t)) ||
				    dp->di_mode || dp->di_size) {
E 3
D 22
					pfatal("PARTIALLY ALLOCATED INODE I=%u",
E 22
I 22
					pfatal("PARTIALLY ALLOCATED INODE I=%lu",
E 22
						inumber);
					if (reply("CLEAR") == 1) {
I 19
						dp = ginode(inumber);
E 19
D 15
						zapino(dp);
E 15
I 15
						clearinode(dp);
E 15
						inodirty();
D 3
						inosumbad++;
E 3
					}
				}
I 3
				statemap[inumber] = USTATE;
				continue;
E 3
			}
I 3
			lastino = inumber;
D 11
			if (dp->di_size < 0) {
E 11
I 11
D 22
			if (dp->di_size < 0 ||
			    dp->di_size + sblock.fs_bsize - 1 < 0) {
E 22
I 22
			if (/* dp->di_size < 0 || */
			    dp->di_size + sblock.fs_bsize - 1 < dp->di_size) {
E 22
E 11
				if (debug)
D 22
					printf("bad size %d:", dp->di_size);
E 22
I 22
D 25
					printf("bad size %lu:", dp->di_size);
E 25
I 25
					printf("bad size %qu:", dp->di_size);
E 25
E 22
				goto unknown;
			}
I 10
			if (!preen && (dp->di_mode & IFMT) == IFMT &&
			    reply("HOLD BAD BLOCK") == 1) {
I 19
				dp = ginode(inumber);
E 19
				dp->di_size = sblock.fs_fsize;
				dp->di_mode = IFREG|0600;
				inodirty();
			}
E 10
			ndb = howmany(dp->di_size, sblock.fs_bsize);
I 12
			if (ndb < 0) {
				if (debug)
D 22
					printf("bad size %d ndb %d:",
E 22
I 22
D 25
					printf("bad size %lu ndb %d:",
E 25
I 25
					printf("bad size %qu ndb %d:",
E 25
E 22
						dp->di_size, ndb);
				goto unknown;
			}
E 12
D 15
			if (SPECIAL(dp))
E 15
I 15
			if ((dp->di_mode & IFMT) == IFBLK ||
			    (dp->di_mode & IFMT) == IFCHR)
E 15
				ndb++;
			for (j = ndb; j < NDADDR; j++)
				if (dp->di_db[j] != 0) {
					if (debug)
D 22
						printf("bad direct addr: %d\n",
E 22
I 22
						printf("bad direct addr: %ld\n",
E 22
							dp->di_db[j]);
					goto unknown;
				}
			for (j = 0, ndb -= NDADDR; ndb > 0; j++)
				ndb /= NINDIR(&sblock);
			for (; j < NIADDR; j++)
				if (dp->di_ib[j] != 0) {
					if (debug)
D 22
						printf("bad indirect addr: %d\n",
E 22
I 22
						printf("bad indirect addr: %ld\n",
E 22
							dp->di_ib[j]);
					goto unknown;
				}
D 10
			if (!preen && (dp->di_mode & IFMT) == IFMT &&
			    reply("HOLD BAD BLOCK") == 1) {
				dp->di_size = sblock.fs_fsize;
				dp->di_mode = IFREG|0600;
				inodirty();
			} else if (ftypeok(dp) == 0)
E 10
I 10
			if (ftypeok(dp) == 0)
E 10
				goto unknown;
			n_files++;
			lncntp[inumber] = dp->di_nlink;
			if (dp->di_nlink <= 0) {
D 7
				if (badlnp < &badlncnt[MAXLNCNT])
					*badlnp++ = inumber;
				else {
E 7
I 7
				zlnp = (struct zlncnt *)malloc(sizeof *zlnp);
				if (zlnp == NULL) {
E 7
					pfatal("LINK COUNT TABLE OVERFLOW");
					if (reply("CONTINUE") == 0)
						errexit("");
I 7
				} else {
					zlnp->zlncnt = inumber;
					zlnp->next = zlnhead;
					zlnhead = zlnp;
E 7
				}
			}
D 15
			statemap[inumber] = DIRCT(dp) ? DSTATE : FSTATE;
			badblk = dupblk = 0; maxblk = 0;
E 15
I 15
D 17
			statemap[inumber] =
			    (dp->di_mode & IFMT) == IFDIR ? DSTATE : FSTATE;
E 17
I 17
			if ((dp->di_mode & IFMT) == IFDIR) {
D 20
				statemap[inumber] = DSTATE;
E 20
I 20
				if (dp->di_size == 0)
					statemap[inumber] = DCLEAR;
				else
					statemap[inumber] = DSTATE;
E 20
				cacheino(dp, inumber);
			} else
				statemap[inumber] = FSTATE;
E 17
			badblk = dupblk = 0;
E 15
			idesc.id_number = inumber;
D 5
			idesc.id_filesize = 0;
E 5
			(void)ckinode(dp, &idesc);
D 5
			idesc.id_filesize *= btodb(sblock.fs_fsize);
			if (dp->di_blocks != idesc.id_filesize) {
E 5
I 5
			idesc.id_entryno *= btodb(sblock.fs_fsize);
			if (dp->di_blocks != idesc.id_entryno) {
E 5
D 22
				pwarn("INCORRECT BLOCK COUNT I=%u (%ld should be %ld)",
E 22
I 22
				pwarn("INCORRECT BLOCK COUNT I=%lu (%ld should be %ld)",
E 22
D 5
				    inumber, dp->di_blocks, idesc.id_filesize);
E 5
I 5
				    inumber, dp->di_blocks, idesc.id_entryno);
E 5
				if (preen)
					printf(" (CORRECTED)\n");
				else if (reply("CORRECT") == 0)
					continue;
I 19
				dp = ginode(inumber);
E 19
D 5
				dp->di_blocks = idesc.id_filesize;
E 5
I 5
				dp->di_blocks = idesc.id_entryno;
E 5
				inodirty();
			}
			continue;
	unknown:
D 22
			pfatal("UNKNOWN FILE TYPE I=%u", inumber);
E 22
I 22
			pfatal("UNKNOWN FILE TYPE I=%lu", inumber);
E 22
I 9
			statemap[inumber] = FCLEAR;
E 26
I 26
			checkinode(inumber, &idesc);
		}
	}
	freeinodebuf();
}

I 33
static void
E 33
checkinode(inumber, idesc)
	ino_t inumber;
	register struct inodesc *idesc;
{
	register struct dinode *dp;
	struct zlncnt *zlnp;
	int ndb, j;
	mode_t mode;
D 31
	char symbuf[MAXSYMLINKLEN];
E 31
I 31
	char *symbuf;
E 31

	dp = getnextinode(inumber);
	mode = dp->di_mode & IFMT;
	if (mode == 0) {
D 35
		if (bcmp((char *)dp->di_db, (char *)zino.di_db,
E 35
I 35
		if (memcmp(dp->di_db, zino.di_db,
E 35
D 32
			NDADDR * sizeof(daddr_t)) ||
E 32
I 32
			NDADDR * sizeof(ufs_daddr_t)) ||
E 32
D 35
		    bcmp((char *)dp->di_ib, (char *)zino.di_ib,
E 35
I 35
		    memcmp(dp->di_ib, zino.di_ib,
E 35
D 32
			NIADDR * sizeof(daddr_t)) ||
E 32
I 32
			NIADDR * sizeof(ufs_daddr_t)) ||
E 32
		    dp->di_mode || dp->di_size) {
			pfatal("PARTIALLY ALLOCATED INODE I=%lu", inumber);
E 26
E 9
			if (reply("CLEAR") == 1) {
I 9
D 26
				statemap[inumber] = USTATE;
E 26
I 19
				dp = ginode(inumber);
E 19
E 9
D 15
				zapino(dp);
E 15
I 15
				clearinode(dp);
E 15
				inodirty();
			}
E 3
		}
I 26
		statemap[inumber] = USTATE;
		return;
E 26
D 3
		if (n != cgrp.cg_cs.cs_nifree) {
			if (debug)
				printf("cg[%d].cg_cs.cs_nifree is %d; calc %d\n",
				    c, cgrp.cg_cs.cs_nifree, n);
			inosumbad++;
		}
		if (cgrp.cg_cs.cs_nbfree != sblock.fs_cs(&sblock, c).cs_nbfree
		  || cgrp.cg_cs.cs_nffree != sblock.fs_cs(&sblock, c).cs_nffree
		  || cgrp.cg_cs.cs_nifree != sblock.fs_cs(&sblock, c).cs_nifree
		  || cgrp.cg_cs.cs_ndir != sblock.fs_cs(&sblock, c).cs_ndir)
			sbsumbad++;
E 3
	}
I 18
D 26
	freeinodebuf();
E 26
I 26
	lastino = inumber;
	if (/* dp->di_size < 0 || */
D 34
	    dp->di_size + sblock.fs_bsize - 1 < dp->di_size) {
E 34
I 34
	    dp->di_size + sblock.fs_bsize - 1 < dp->di_size ||
	    (mode == IFDIR && dp->di_size > MAXDIRSIZE)) {
E 34
		if (debug)
			printf("bad size %qu:", dp->di_size);
		goto unknown;
	}
	if (!preen && mode == IFMT && reply("HOLD BAD BLOCK") == 1) {
		dp = ginode(inumber);
		dp->di_size = sblock.fs_fsize;
		dp->di_mode = IFREG|0600;
		inodirty();
	}
	ndb = howmany(dp->di_size, sblock.fs_bsize);
	if (ndb < 0) {
		if (debug)
			printf("bad size %qu ndb %d:",
				dp->di_size, ndb);
		goto unknown;
	}
	if (mode == IFBLK || mode == IFCHR)
		ndb++;
	if (mode == IFLNK) {
D 27
		if (doinglevel2 && dp->di_size < MAXSYMLINKLEN &&
		    (dp->di_ouid != -1 || dp->di_gid != -1)) {
E 27
I 27
		if (doinglevel2 &&
		    dp->di_size > 0 && dp->di_size < MAXSYMLINKLEN &&
		    dp->di_blocks != 0) {
I 31
			symbuf = alloca(secsize);
E 31
E 27
			if (bread(fsreadfd, symbuf,
			    fsbtodb(&sblock, dp->di_db[0]),
D 31
			    (long)dp->di_size) != 0)
E 31
I 31
			    (long)secsize) != 0)
E 31
D 33
				errexit("cannot read symlink");
E 33
I 33
				errx(EEXIT, "cannot read symlink");
E 33
I 27
			if (debug) {
				symbuf[dp->di_size] = 0;
				printf("convert symlink %d(%s) of size %d\n",
					inumber, symbuf, (long)dp->di_size);
			}
E 27
			dp = ginode(inumber);
D 35
			bcopy(symbuf, (caddr_t)dp->di_shortlink,
			    (long)dp->di_size);
E 35
I 35
			memmove(dp->di_shortlink, symbuf, (long)dp->di_size);
E 35
			dp->di_blocks = 0;
			inodirty();
		}
D 27
		if (dp->di_size < sblock.fs_maxsymlinklen)
E 27
I 27
		/*
		 * Fake ndb value so direct/indirect block checks below
		 * will detect any garbage after symlink string.
		 */
		if (dp->di_size < sblock.fs_maxsymlinklen) {
E 27
D 32
			ndb = howmany(dp->di_size, sizeof(daddr_t));
E 32
I 32
			ndb = howmany(dp->di_size, sizeof(ufs_daddr_t));
E 32
I 27
			if (ndb > NDADDR) {
				j = ndb - NDADDR;
				for (ndb = 1; j > 1; j--)
					ndb *= NINDIR(&sblock);
				ndb += NDADDR;
			}
		}
E 27
	}
	for (j = ndb; j < NDADDR; j++)
		if (dp->di_db[j] != 0) {
			if (debug)
				printf("bad direct addr: %ld\n", dp->di_db[j]);
			goto unknown;
		}
	for (j = 0, ndb -= NDADDR; ndb > 0; j++)
		ndb /= NINDIR(&sblock);
	for (; j < NIADDR; j++)
		if (dp->di_ib[j] != 0) {
D 30
			if (debug)
				printf("bad indirect addr: %ld\n",
					dp->di_ib[j]);
			goto unknown;
E 30
I 30
			if (debug) {
				for (j = 0; j < NIADDR; j++) {
				printf("bad indirect addr[%d]: %lx\n",
					j, dp->di_ib[j]);
				}
				printf("flags: %x, blocks %d\n",
					dp->di_flags, dp->di_blocks);
				pfatal("BAD THIRD INDIRECT");
				if (reply("ZERO")) {
					dp = ginode(inumber);
					dp->di_ib[2] = 0;
					inodirty();
				} else
					goto unknown;
			} else
				goto unknown;
E 30
		}
	if (ftypeok(dp) == 0)
		goto unknown;
	n_files++;
	lncntp[inumber] = dp->di_nlink;
	if (dp->di_nlink <= 0) {
		zlnp = (struct zlncnt *)malloc(sizeof *zlnp);
		if (zlnp == NULL) {
			pfatal("LINK COUNT TABLE OVERFLOW");
			if (reply("CONTINUE") == 0)
D 33
				errexit("");
E 33
I 33
				exit(EEXIT);
E 33
		} else {
			zlnp->zlncnt = inumber;
			zlnp->next = zlnhead;
			zlnhead = zlnp;
		}
	}
	if (mode == IFDIR) {
		if (dp->di_size == 0)
			statemap[inumber] = DCLEAR;
		else
			statemap[inumber] = DSTATE;
		cacheino(dp, inumber);
	} else
		statemap[inumber] = FSTATE;
	typemap[inumber] = IFTODT(mode);
D 27
	if (doinglevel2 && (dp->di_ouid != -1 || dp->di_gid != -1)) {
E 27
I 27
D 28
	if (doinglevel2 && (dp->di_ouid != -1 || dp->di_ogid != -1)) {
E 28
I 28
	if (doinglevel2 &&
	    (dp->di_ouid != (u_short)-1 || dp->di_ogid != (u_short)-1)) {
E 28
E 27
		dp = ginode(inumber);
		dp->di_uid = dp->di_ouid;
		dp->di_ouid = -1;
		dp->di_gid = dp->di_ogid;
		dp->di_ogid = -1;
		inodirty();
	}
	badblk = dupblk = 0;
	idesc->id_number = inumber;
	(void)ckinode(dp, idesc);
	idesc->id_entryno *= btodb(sblock.fs_fsize);
	if (dp->di_blocks != idesc->id_entryno) {
		pwarn("INCORRECT BLOCK COUNT I=%lu (%ld should be %ld)",
		    inumber, dp->di_blocks, idesc->id_entryno);
		if (preen)
			printf(" (CORRECTED)\n");
		else if (reply("CORRECT") == 0)
			return;
		dp = ginode(inumber);
		dp->di_blocks = idesc->id_entryno;
		inodirty();
	}
	return;
unknown:
	pfatal("UNKNOWN FILE TYPE I=%lu", inumber);
	statemap[inumber] = FCLEAR;
	if (reply("CLEAR") == 1) {
		statemap[inumber] = USTATE;
		dp = ginode(inumber);
		clearinode(dp);
		inodirty();
	}
E 26
E 18
}

I 33
int
E 33
pass1check(idesc)
	register struct inodesc *idesc;
{
D 6
	register daddr_t *dlp;
E 6
	int res = KEEPON;
	int anyout, nfrags;
D 32
	daddr_t blkno = idesc->id_blkno;
E 32
I 32
	ufs_daddr_t blkno = idesc->id_blkno;
E 32
I 6
	register struct dups *dlp;
	struct dups *new;
E 6

D 2
	anyout = outrange(blkno, idesc->id_numfrags);
E 2
I 2
D 15
	if ((anyout = outrange(blkno, idesc->id_numfrags)) != 0) {
		blkerr(idesc->id_number, "BAD", blkno);
E 15
I 15
	if ((anyout = chkrange(blkno, idesc->id_numfrags)) != 0) {
		blkerror(idesc->id_number, "BAD", blkno);
E 15
D 23
		if (++badblk >= MAXBAD) {
E 23
I 23
		if (badblk++ >= MAXBAD) {
E 23
D 22
			pwarn("EXCESSIVE BAD BLKS I=%u",
E 22
I 22
			pwarn("EXCESSIVE BAD BLKS I=%lu",
E 22
				idesc->id_number);
			if (preen)
				printf(" (SKIPPING)\n");
			else if (reply("CONTINUE") == 0)
D 33
				errexit("");
E 33
I 33
				exit(EEXIT);
E 33
			return (STOP);
		}
	}
E 2
	for (nfrags = idesc->id_numfrags; nfrags > 0; blkno++, nfrags--) {
D 15
		if (anyout && outrange(blkno, 1)) {
E 15
I 15
		if (anyout && chkrange(blkno, 1)) {
E 15
D 2
			blkerr(idesc->id_number, "BAD", blkno);
			if (++badblk >= MAXBAD) {
				pwarn("EXCESSIVE BAD BLKS I=%u",
					idesc->id_number);
				if (preen)
					printf(" (SKIPPING)\n");
				else if (reply("CONTINUE") == 0)
					errexit("");
				return (STOP);
			}
E 2
			res = SKIP;
D 2
		} else if (getbmap(blkno)) {
E 2
I 2
D 15
		} else if (!getbmap(blkno)) {
E 15
I 15
		} else if (!testbmap(blkno)) {
E 15
			n_blks++;
			setbmap(blkno);
		} else {
E 2
D 15
			blkerr(idesc->id_number, "DUP", blkno);
E 15
I 15
			blkerror(idesc->id_number, "DUP", blkno);
E 15
D 23
			if (++dupblk >= MAXDUP) {
E 23
I 23
			if (dupblk++ >= MAXDUP) {
E 23
D 22
				pwarn("EXCESSIVE DUP BLKS I=%u",
E 22
I 22
				pwarn("EXCESSIVE DUP BLKS I=%lu",
E 22
					idesc->id_number);
				if (preen)
					printf(" (SKIPPING)\n");
				else if (reply("CONTINUE") == 0)
D 33
					errexit("");
E 33
I 33
					exit(EEXIT);
E 33
				return (STOP);
			}
D 6
			if (enddup >= &duplist[DUPTBLSIZE]) {
E 6
I 6
			new = (struct dups *)malloc(sizeof(struct dups));
			if (new == NULL) {
E 6
				pfatal("DUP TABLE OVERFLOW.");
				if (reply("CONTINUE") == 0)
D 33
					errexit("");
E 33
I 33
					exit(EEXIT);
E 33
				return (STOP);
			}
D 6
			for (dlp = duplist; dlp < muldup; dlp++)
				if (*dlp == blkno) {
					*enddup++ = blkno;
					break;
				}
			if (dlp >= muldup) {
				*enddup++ = *muldup;
				*muldup++ = blkno;
E 6
I 6
			new->dup = blkno;
			if (muldup == 0) {
				duplist = muldup = new;
				new->next = 0;
			} else {
				new->next = muldup->next;
				muldup->next = new;
E 6
			}
I 6
			for (dlp = duplist; dlp != muldup; dlp = dlp->next)
				if (dlp->dup == blkno)
					break;
			if (dlp == muldup && dlp->dup != blkno)
				muldup = new;
E 6
D 2
		} else {
			n_blks++;
			setbmap(blkno);
E 2
		}
D 5
		idesc->id_filesize++;
E 5
I 5
		/*
		 * count the number of blocks found in id_entryno
		 */
		idesc->id_entryno++;
E 5
	}
	return (res);
}
E 1
