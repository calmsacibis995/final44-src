h47351
s 00018/00018/00284
d D 8.9 95/04/28 10:38:11 bostic 33 32
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00008/00002/00294
d D 8.8 95/04/27 11:32:59 mckusick 32 31
c add function prototypes
e
s 00005/00005/00291
d D 8.7 95/03/21 00:10:44 mckusick 31 30
c daddr_t => ufs_daddr_t
e
s 00001/00001/00295
d D 8.6 94/11/30 11:00:04 mckusick 30 29
c lint
e
s 00001/00001/00295
d D 8.5 94/11/29 20:59:08 mckusick 29 28
c convert level should be >= 3, not > 3
e
s 00001/00000/00295
d D 8.4 94/11/04 00:08:30 mckusick 28 27
c restore WINO inode to USTATE to keep accounting right
e
s 00006/00004/00289
d D 8.3 94/08/14 16:38:15 mckusick 27 26
c cg_link => cg_firstfield; fs_link => fs_firstfield
e
s 00091/00007/00202
d D 8.2 94/02/02 00:41:39 mckusick 26 25
c add convert level 4 to create, expand, or delete cluster maps
e
s 00002/00002/00207
d D 8.1 93/06/05 10:56:46 bostic 25 24
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00006/00208
d D 5.18 92/09/30 09:42:46 mckusick 24 23
c do not worry about time field in cylinder groups
e
s 00005/00002/00209
d D 5.17 92/07/02 16:34:32 mckusick 23 22
c don't complain about lost blocks when doing a conversion
e
s 00001/00000/00210
d D 5.16 92/05/27 22:45:23 mckusick 22 21
c add <sys/time.h> for dinode.h
e
s 00001/00001/00209
d D 5.15 91/11/11 12:03:10 bostic 21 20
c break UFS up into FFS/UFS/LFS/MFS
e
s 00002/00002/00208
d D 5.14 91/11/04 22:20:36 bostic 20 19
c break FFS into UFS/FFS/LFS
e
s 00009/00006/00201
d D 5.13 90/07/20 16:51:45 mckusick 19 18
c lint (from Torek)
e
s 00001/00011/00206
d D 5.12 90/06/01 16:17:40 bostic 18 17
c new copyright notice
e
s 00002/00001/00215
d D 5.11 90/02/06 21:40:54 mckusick 17 16
c want to round to number of frags not fragmment size
e
s 00015/00004/00201
d D 5.10 90/02/01 17:17:46 mckusick 16 15
c convert to BSD only copyright
e
s 00004/00004/00201
d D 5.9 90/02/01 16:18:05 mckusick 15 14
c lint and other aesthetic cleanups
e
s 00001/00003/00204
d D 5.8 89/10/24 19:05:44 mckusick 14 13
c no longer need to include time.h, vnode.h, and inode.h; just include dinode.h
e
s 00004/00002/00203
d D 5.7 89/06/26 21:42:13 mckusick 13 12
c new include file locations engendered by vnodes
e
s 00008/00007/00197
d D 5.6 89/03/07 19:30:04 mckusick 12 11
c allow different error messages to each appear once
e
s 00057/00056/00147
d D 5.5 88/05/07 00:16:40 mckusick 11 10
c &sblock => fs; &cgrp => cg
e
s 00076/00046/00127
d D 5.4 88/05/01 23:43:26 mckusick 10 9
c conversion and checking of dynamic and static cylinder group tables
e
s 00006/00000/00167
d D 5.3 86/10/13 15:36:25 sam 9 8
c add tahoe compiller  workaround
e
s 00006/00000/00161
d D 5.2 86/03/05 17:14:43 mckusick 8 7
c add firewall check for bad entry in state map
e
s 00008/00002/00153
d D 5.1 85/06/05 08:58:01 dist 7 6
c Add copyright
e
s 00001/00002/00154
d D 3.6 85/05/31 00:19:33 mckusick 6 5
c check for improper directory offsets; recover gracefully from read errors
e
s 00002/00001/00154
d D 3.5 85/04/21 20:42:02 mckusick 5 4
c properly calculate the size of the active block map
e
s 00129/00119/00026
d D 3.4 85/02/08 19:15:49 mckusick 4 3
c merge passes 5 and 6 into a single pass
e
s 00000/00015/00145
d D 3.3 85/01/10 17:04:57 mckusick 3 2
c -r3.2 is no longer needed as the kernel handles all updates of cg_irotor
e
s 00015/00000/00145
d D 3.2 84/08/06 20:27:33 mckusick 2 1
c include validation check for cg_irotor
e
s 00145/00000/00000
d D 3.1 84/03/31 21:03:51 mckusick 1 0
c date and time created 84/03/31 21:03:51 by mckusick
e
u
U
t
T
I 7
/*
D 16
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 16
I 16
D 25
 * Copyright (c) 1980, 1986 The Regents of the University of California.
 * All rights reserved.
E 25
I 25
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 25
 *
D 18
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
E 18
I 18
 * %sccs.include.redist.c%
E 18
E 16
 */

E 7
I 1
#ifndef lint
D 7
static char version[] = "%W% (Berkeley) %G%";
#endif
E 7
I 7
static char sccsid[] = "%W% (Berkeley) %G%";
D 16
#endif not lint
E 16
I 16
#endif /* not lint */
E 16
E 7

#include <sys/param.h>
I 22
#include <sys/time.h>
I 32

E 32
E 22
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
D 20
#include <ufs/dinode.h>
E 14
#include <ufs/fs.h>
E 20
I 20
#include <ufs/ufs/dinode.h>
#include <ufs/ffs/fs.h>
I 32

#include <err.h>
E 32
E 20
I 19
#include <string.h>
I 32

E 32
E 19
E 13
#include "fsck.h"

I 32
void
E 32
pass5()
{
D 4
	register int c, n, i, b, d;
	short bo[MAXCPG][NRPOS];
	long botot[MAXCPG];
	long frsum[MAXFRAG];
	int blk;
	daddr_t cbase;
	int blockbits = (1<<sblock.fs_frag)-1;
E 4
I 4
D 10
	int c, blk, frags, sumsize, mapsize;
	daddr_t dbase, dmax, d;
E 10
I 10
	int c, blk, frags, basesize, sumsize, mapsize, savednrpos;
I 11
D 31
	register struct fs *fs = &sblock;
	register struct cg *cg = &cgrp;
E 11
	daddr_t dbase, dmax;
	register daddr_t d;
E 10
	register long i, j;
E 31
I 31
	struct fs *fs = &sblock;
	struct cg *cg = &cgrp;
	ufs_daddr_t dbase, dmax;
	ufs_daddr_t d;
	long i, j;
E 31
	struct csum *cs;
D 24
	time_t now;
E 24
	struct csum cstotal;
D 12
	struct inodesc idesc;
E 12
I 12
	struct inodesc idesc[3];
E 12
	char buf[MAXBSIZE];
	register struct cg *newcg = (struct cg *)buf;
I 10
	struct ocg *ocg = (struct ocg *)buf;
E 10
E 4

I 28
	statemap[WINO] = USTATE;
E 28
D 4
	bcopy(blockmap, freemap, (unsigned)bmapsz);
	dupblk = 0;
	n_index = sblock.fs_ncg * (cgdmin(&sblock, 0) - cgtod(&sblock, 0));
E 4
I 4
D 11
	bzero((char *)newcg, sblock.fs_cgsize);
D 10
	newcg->cg_magic = CG_MAGIC;
E 10
I 10
	newcg->cg_niblk = sblock.fs_ipg;
	switch (sblock.fs_postblformat) {
E 11
I 11
D 15
	bzero((char *)newcg, fs->fs_cgsize);
E 15
I 15
D 19
	bzero((char *)newcg, (int)fs->fs_cgsize);
E 19
I 19
D 33
	bzero((char *)newcg, (size_t)fs->fs_cgsize);
E 33
I 33
	memset(newcg, 0, (size_t)fs->fs_cgsize);
E 33
E 19
E 15
	newcg->cg_niblk = fs->fs_ipg;
I 26
D 29
	if (cvtlevel > 3) {
E 29
I 29
	if (cvtlevel >= 3) {
E 29
		if (fs->fs_maxcontig < 2 && fs->fs_contigsumsize > 0) {
			if (preen)
				pwarn("DELETING CLUSTERING MAPS\n");
			if (preen || reply("DELETE CLUSTERING MAPS")) {
				fs->fs_contigsumsize = 0;
				doinglevel1 = 1;
				sbdirty();
			}
		}
		if (fs->fs_maxcontig > 1) {
			char *doit = 0;

			if (fs->fs_contigsumsize < 1) {
				doit = "CREAT";
			} else if (fs->fs_contigsumsize < fs->fs_maxcontig &&
				   fs->fs_contigsumsize < FS_MAXCONTIG) {
				doit = "EXPAND";
			}
			if (doit) {
				i = fs->fs_contigsumsize;
				fs->fs_contigsumsize =
				    MIN(fs->fs_maxcontig, FS_MAXCONTIG);
				if (CGSIZE(fs) > fs->fs_bsize) {
					pwarn("CANNOT %s CLUSTER MAPS\n", doit);
					fs->fs_contigsumsize = i;
				} else if (preen ||
				    reply("CREATE CLUSTER MAPS")) {
					if (preen)
						pwarn("%sING CLUSTER MAPS\n",
						    doit);
					fs->fs_cgsize =
					    fragroundup(fs, CGSIZE(fs));
					doinglevel1 = 1;
					sbdirty();
				}
			}
		}
	}
E 26
D 15
	switch (fs->fs_postblformat) {
E 15
I 15
	switch ((int)fs->fs_postblformat) {
E 15
E 11

	case FS_42POSTBLFMT:
D 27
		basesize = (char *)(&ocg->cg_btot[0]) - (char *)(&ocg->cg_link);
		sumsize = &ocg->cg_iused[0] - (char *)(&ocg->cg_btot[0]);
E 27
I 27
		basesize = (char *)(&ocg->cg_btot[0]) -
		    (char *)(&ocg->cg_firstfield);
		sumsize = &ocg->cg_iused[0] - (u_int8_t *)(&ocg->cg_btot[0]);
E 27
D 11
		mapsize = &ocg->cg_free[howmany(sblock.fs_fpg, NBBY)] -
E 11
I 11
		mapsize = &ocg->cg_free[howmany(fs->fs_fpg, NBBY)] -
E 11
			(u_char *)&ocg->cg_iused[0];
		ocg->cg_magic = CG_MAGIC;
D 11
		savednrpos = sblock.fs_nrpos;
		sblock.fs_nrpos = 8;
E 11
I 11
		savednrpos = fs->fs_nrpos;
		fs->fs_nrpos = 8;
E 11
		break;

	case FS_DYNAMICPOSTBLFMT:
		newcg->cg_btotoff =
D 26
		 	&newcg->cg_space[0] - (u_char *)(&newcg->cg_link);
E 26
I 26
D 27
		     &newcg->cg_space[0] - (u_char *)(&newcg->cg_link);
E 27
I 27
		     &newcg->cg_space[0] - (u_char *)(&newcg->cg_firstfield);
E 27
E 26
		newcg->cg_boff =
D 11
			newcg->cg_btotoff + sblock.fs_cpg * sizeof(long);
E 11
I 11
D 26
			newcg->cg_btotoff + fs->fs_cpg * sizeof(long);
E 26
I 26
		    newcg->cg_btotoff + fs->fs_cpg * sizeof(long);
E 26
E 11
		newcg->cg_iusedoff = newcg->cg_boff + 
D 11
			sblock.fs_cpg * sblock.fs_nrpos * sizeof(short);
E 11
I 11
D 26
			fs->fs_cpg * fs->fs_nrpos * sizeof(short);
E 26
I 26
		    fs->fs_cpg * fs->fs_nrpos * sizeof(short);
E 26
E 11
		newcg->cg_freeoff =
D 11
			newcg->cg_iusedoff + howmany(sblock.fs_ipg, NBBY);
E 11
I 11
D 26
			newcg->cg_iusedoff + howmany(fs->fs_ipg, NBBY);
E 11
		newcg->cg_nextfreeoff = newcg->cg_freeoff +
D 11
			howmany(sblock.fs_cpg * sblock.fs_spc / NSPF(&sblock),
E 11
I 11
			howmany(fs->fs_cpg * fs->fs_spc / NSPF(fs),
E 11
				NBBY);
E 26
I 26
		    newcg->cg_iusedoff + howmany(fs->fs_ipg, NBBY);
		if (fs->fs_contigsumsize <= 0) {
			newcg->cg_nextfreeoff = newcg->cg_freeoff +
			    howmany(fs->fs_cpg * fs->fs_spc / NSPF(fs), NBBY);
		} else {
			newcg->cg_clustersumoff = newcg->cg_freeoff +
			    howmany(fs->fs_cpg * fs->fs_spc / NSPF(fs), NBBY) -
			    sizeof(long);
			newcg->cg_clustersumoff =
			    roundup(newcg->cg_clustersumoff, sizeof(long));
			newcg->cg_clusteroff = newcg->cg_clustersumoff +
			    (fs->fs_contigsumsize + 1) * sizeof(long);
			newcg->cg_nextfreeoff = newcg->cg_clusteroff +
			    howmany(fs->fs_cpg * fs->fs_spc / NSPB(fs), NBBY);
		}
E 26
		newcg->cg_magic = CG_MAGIC;
D 27
		basesize = &newcg->cg_space[0] - (u_char *)(&newcg->cg_link);
E 27
I 27
		basesize = &newcg->cg_space[0] -
		    (u_char *)(&newcg->cg_firstfield);
E 27
		sumsize = newcg->cg_iusedoff - newcg->cg_btotoff;
		mapsize = newcg->cg_nextfreeoff - newcg->cg_iusedoff;
		break;

	default:
D 32
		errexit("UNKNOWN ROTATIONAL TABLE FORMAT %d\n",
E 32
I 32
		sumsize = 0;	/* keep lint happy */
		errx(EEXIT, "UNKNOWN ROTATIONAL TABLE FORMAT %d",
E 32
D 11
			sblock.fs_postblformat);
E 11
I 11
			fs->fs_postblformat);
E 11
	}
E 10
D 12
	bzero((char *)&idesc, sizeof(struct inodesc));
	idesc.id_type = ADDR;
E 12
I 12
D 33
	bzero((char *)&idesc[0], sizeof idesc);
E 33
I 33
	memset(&idesc[0], 0, sizeof idesc);
E 33
D 23
	for (i = 0; i < 3; i++)
E 23
I 23
	for (i = 0; i < 3; i++) {
E 23
		idesc[i].id_type = ADDR;
I 23
		if (doinglevel2)
			idesc[i].id_fix = FIX;
	}
E 23
E 12
D 33
	bzero((char *)&cstotal, sizeof(struct csum));
E 33
I 33
	memset(&cstotal, 0, sizeof(struct csum));
E 33
D 10
	sumsize = cgrp.cg_iused - (char *)(&cgrp);
D 5
	mapsize = howmany(MAXIPG + sblock.fs_fpg, NBBY);
E 5
I 5
	mapsize = &cgrp.cg_free[howmany(sblock.fs_fpg, NBBY)] -
		(u_char *)cgrp.cg_iused;
E 10
E 5
D 24
	(void)time(&now);
E 24
I 10
D 11
	for (i = sblock.fs_size; i < fragroundup(&sblock, sblock.fs_size); i++)
E 11
I 11
D 17
	for (i = fs->fs_size; i < fragroundup(fs, fs->fs_size); i++)
E 17
I 17
	j = blknum(fs, fs->fs_size + fs->fs_frag - 1);
	for (i = fs->fs_size; i < j; i++)
E 17
E 11
		setbmap(i);
E 10
E 4
D 11
	for (c = 0; c < sblock.fs_ncg; c++) {
D 4
		cbase = cgbase(&sblock, c);
		bzero((char *)botot, sizeof (botot));
		bzero((char *)bo, sizeof (bo));
		bzero((char *)frsum, sizeof (frsum));
		/*
		 * need to account for the super blocks
		 * which appear (inaccurately) bad
		 */
		n_bad += cgtod(&sblock, c) - cgsblock(&sblock, c);
E 4
D 6
		if (getblk(&cgblk, cgtod(&sblock, c), sblock.fs_cgsize) == 0)
			continue;
E 6
I 6
		getblk(&cgblk, cgtod(&sblock, c), sblock.fs_cgsize);
E 6
D 4
		if (cgrp.cg_magic != CG_MAGIC) {
E 4
I 4
D 10
		if (cgrp.cg_magic != CG_MAGIC)
E 10
I 10
		if (!cg_chkmagic(&cgrp))
E 11
I 11
	for (c = 0; c < fs->fs_ncg; c++) {
		getblk(&cgblk, cgtod(fs, c), fs->fs_cgsize);
		if (!cg_chkmagic(cg))
E 11
E 10
E 4
			pfatal("CG %d: BAD MAGIC NUMBER\n", c);
D 4
			bzero((char *)&cgrp, (int)sblock.fs_cgsize);
E 4
I 4
D 11
		dbase = cgbase(&sblock, c);
		dmax = dbase + sblock.fs_fpg;
		if (dmax > sblock.fs_size)
			dmax = sblock.fs_size;
		if (now > cgrp.cg_time)
			newcg->cg_time = cgrp.cg_time;
E 11
I 11
		dbase = cgbase(fs, c);
		dmax = dbase + fs->fs_fpg;
		if (dmax > fs->fs_size)
			dmax = fs->fs_size;
D 24
		if (now > cg->cg_time)
			newcg->cg_time = cg->cg_time;
E 11
		else
			newcg->cg_time = now;
E 24
I 24
		newcg->cg_time = cg->cg_time;
E 24
		newcg->cg_cgx = c;
D 11
		if (c == sblock.fs_ncg - 1)
			newcg->cg_ncyl = sblock.fs_ncyl % sblock.fs_cpg;
E 11
I 11
		if (c == fs->fs_ncg - 1)
			newcg->cg_ncyl = fs->fs_ncyl % fs->fs_cpg;
E 11
		else
D 11
			newcg->cg_ncyl = sblock.fs_cpg;
E 11
I 11
			newcg->cg_ncyl = fs->fs_cpg;
E 11
D 10
		newcg->cg_niblk = sblock.fs_ipg;
E 10
		newcg->cg_ndblk = dmax - dbase;
I 26
		if (fs->fs_contigsumsize > 0)
			newcg->cg_nclusterblks = newcg->cg_ndblk / fs->fs_frag;
E 26
		newcg->cg_cs.cs_ndir = 0;
		newcg->cg_cs.cs_nffree = 0;
		newcg->cg_cs.cs_nbfree = 0;
D 11
		newcg->cg_cs.cs_nifree = sblock.fs_ipg;
		if (cgrp.cg_rotor < newcg->cg_ndblk)
			newcg->cg_rotor = cgrp.cg_rotor;
E 11
I 11
		newcg->cg_cs.cs_nifree = fs->fs_ipg;
		if (cg->cg_rotor < newcg->cg_ndblk)
			newcg->cg_rotor = cg->cg_rotor;
E 11
		else
			newcg->cg_rotor = 0;
D 11
		if (cgrp.cg_frotor < newcg->cg_ndblk)
			newcg->cg_frotor = cgrp.cg_frotor;
E 11
I 11
		if (cg->cg_frotor < newcg->cg_ndblk)
			newcg->cg_frotor = cg->cg_frotor;
E 11
		else
			newcg->cg_frotor = 0;
D 11
		if (cgrp.cg_irotor < newcg->cg_niblk)
			newcg->cg_irotor = cgrp.cg_irotor;
E 11
I 11
		if (cg->cg_irotor < newcg->cg_niblk)
			newcg->cg_irotor = cg->cg_irotor;
E 11
		else
			newcg->cg_irotor = 0;
D 10
		bzero((char *)newcg->cg_frsum, sizeof newcg->cg_frsum);
		bzero((char *)newcg->cg_btot, sizeof newcg->cg_btot);
		bzero((char *)newcg->cg_b, sizeof newcg->cg_b);
		bzero((char *)newcg->cg_free, howmany(sblock.fs_fpg, NBBY));
		bzero((char *)newcg->cg_iused, howmany(sblock.fs_ipg, NBBY));
E 10
I 10
D 33
		bzero((char *)&newcg->cg_frsum[0], sizeof newcg->cg_frsum);
D 19
		bzero((char *)&cg_blktot(newcg)[0], sumsize + mapsize);
E 19
I 19
		bzero((char *)&cg_blktot(newcg)[0],
E 33
I 33
		memset(&newcg->cg_frsum[0], 0, sizeof newcg->cg_frsum);
		memset(&cg_blktot(newcg)[0], 0,
E 33
		      (size_t)(sumsize + mapsize));
E 19
D 11
		if (sblock.fs_postblformat == FS_42POSTBLFMT)
E 11
I 11
		if (fs->fs_postblformat == FS_42POSTBLFMT)
E 11
			ocg->cg_magic = CG_MAGIC;
E 10
D 11
		j = sblock.fs_ipg * c;
		for (i = 0; i < sblock.fs_ipg; j++, i++) {
E 11
I 11
		j = fs->fs_ipg * c;
		for (i = 0; i < fs->fs_ipg; j++, i++) {
E 11
			switch (statemap[j]) {

			case USTATE:
				break;

			case DSTATE:
			case DCLEAR:
			case DFOUND:
				newcg->cg_cs.cs_ndir++;
				/* fall through */

			case FSTATE:
			case FCLEAR:
				newcg->cg_cs.cs_nifree--;
D 10
				setbit(newcg->cg_iused, i);
E 10
I 10
				setbit(cg_inosused(newcg), i);
E 10
				break;
I 8

			default:
				if (j < ROOTINO)
					break;
D 32
				errexit("BAD STATE %d FOR INODE I=%d",
E 32
I 32
				errx(EEXIT, "BAD STATE %d FOR INODE I=%d",
E 32
				    statemap[j], j);
E 8
			}
E 4
		}
I 2
D 3
		for (i = 0, n = 0; i < sblock.fs_ipg; i += NBBY, n++)
			if (cgrp.cg_iused[n] != 0xff)
				break;
		for ( ; i < sblock.fs_ipg; i++) {
			if (isclr(cgrp.cg_iused, i)) {
				if (i < cgrp.cg_irotor) {
					if (debug) printf(
					    "cg %d, first free %d, irotor %d\n",
					     c, i, cgrp.cg_irotor);
					cgrp.cg_irotor = i;
					cgdirty();
					break;
				}
			}
		}
E 3
E 2
D 4
		for (b = 0; b < sblock.fs_fpg; b += sblock.fs_frag) {
			blk = blkmap(&sblock, cgrp.cg_free, b);
			if (blk == 0)
				continue;
			if (blk == blockbits) {
				if (pass5check(cbase+b, sblock.fs_frag) == STOP)
					goto out5;
				/* this is clumsy ... */
				n_ffree -= sblock.fs_frag;
				n_bfree++;
				botot[cbtocylno(&sblock, b)]++;
				bo[cbtocylno(&sblock, b)]
				    [cbtorpos(&sblock, b)]++;
				continue;
E 4
I 4
		if (c == 0)
			for (i = 0; i < ROOTINO; i++) {
D 10
				setbit(newcg->cg_iused, i);
E 10
I 10
				setbit(cg_inosused(newcg), i);
E 10
				newcg->cg_cs.cs_nifree--;
E 4
			}
D 4
			for (d = 0; d < sblock.fs_frag; d++)
				if ((blk & (1<<d)) &&
				    pass5check(cbase + b + d, (long)1) == STOP)
					goto out5;
			fragacct(&sblock, blk, frsum, 1);
E 4
I 4
		for (i = 0, d = dbase;
D 10
		     d <= dmax - sblock.fs_frag;
E 10
I 10
		     d < dmax;
E 10
D 11
		     d += sblock.fs_frag, i += sblock.fs_frag) {
E 11
I 11
		     d += fs->fs_frag, i += fs->fs_frag) {
E 11
			frags = 0;
D 11
			for (j = 0; j < sblock.fs_frag; j++) {
E 11
I 11
			for (j = 0; j < fs->fs_frag; j++) {
E 11
D 15
				if (getbmap(d + j))
E 15
I 15
				if (testbmap(d + j))
E 15
					continue;
D 10
				setbit(newcg->cg_free, i + j);
E 10
I 10
				setbit(cg_blksfree(newcg), i + j);
E 10
				frags++;
			}
D 11
			if (frags == sblock.fs_frag) {
E 11
I 11
			if (frags == fs->fs_frag) {
E 11
				newcg->cg_cs.cs_nbfree++;
D 11
				j = cbtocylno(&sblock, i);
E 11
I 11
				j = cbtocylno(fs, i);
E 11
D 10
				newcg->cg_btot[j]++;
				newcg->cg_b[j][cbtorpos(&sblock, i)]++;
E 10
I 10
				cg_blktot(newcg)[j]++;
D 11
				cg_blks(&sblock, newcg, j)
				    [cbtorpos(&sblock, i)]++;
E 11
I 11
				cg_blks(fs, newcg, j)[cbtorpos(fs, i)]++;
I 26
				if (fs->fs_contigsumsize > 0)
					setbit(cg_clustersfree(newcg),
					    i / fs->fs_frag);
E 26
E 11
E 10
			} else if (frags > 0) {
				newcg->cg_cs.cs_nffree += frags;
D 10
				blk = blkmap(&sblock, newcg->cg_free, i);
E 10
I 10
D 11
				blk = blkmap(&sblock, cg_blksfree(newcg), i);
E 10
				fragacct(&sblock, blk, newcg->cg_frsum, 1);
E 11
I 11
				blk = blkmap(fs, cg_blksfree(newcg), i);
D 21
				fragacct(fs, blk, newcg->cg_frsum, 1);
E 21
I 21
				ffs_fragacct(fs, blk, newcg->cg_frsum, 1);
I 26
			}
		}
		if (fs->fs_contigsumsize > 0) {
D 30
			long *sump = cg_clustersum(newcg);
E 30
I 30
			int32_t *sump = cg_clustersum(newcg);
E 30
			u_char *mapp = cg_clustersfree(newcg);
			int map = *mapp++;
			int bit = 1;
			int run = 0;

			for (i = 0; i < newcg->cg_nclusterblks; i++) {
				if ((map & bit) != 0) {
					run++;
				} else if (run != 0) {
					if (run > fs->fs_contigsumsize)
						run = fs->fs_contigsumsize;
					sump[run]++;
					run = 0;
				}
				if ((i & (NBBY - 1)) != (NBBY - 1)) {
					bit <<= 1;
				} else {
					map = *mapp++;
					bit = 1;
				}
			}
			if (run != 0) {
				if (run > fs->fs_contigsumsize)
					run = fs->fs_contigsumsize;
				sump[run]++;
E 26
E 21
E 11
			}
E 4
		}
D 4
		if (bcmp((char *)cgrp.cg_frsum, (char *)frsum, sizeof(frsum))) {
			if (debug)
			for (i = 0; i < sblock.fs_frag; i++)
				if (cgrp.cg_frsum[i] != frsum[i])
				printf("cg[%d].cg_frsum[%d] have %d calc %d\n",
				    c, i, cgrp.cg_frsum[i], frsum[i]);
			frsumbad++;
E 4
I 4
D 10
		for (frags = d; d < dmax; d++) {
			if (getbmap(d))
				continue;
			setbit(newcg->cg_free, d - dbase);
			newcg->cg_cs.cs_nffree++;
E 4
		}
D 4
		if (bcmp((char *)cgrp.cg_btot, (char *)botot, sizeof (botot))) {
			if (debug)
			for (n = 0; n < sblock.fs_cpg; n++)
				if (botot[n] != cgrp.cg_btot[n])
				printf("cg[%d].cg_btot[%d] have %d calc %d\n",
				    c, n, cgrp.cg_btot[n], botot[n]);
			offsumbad++;
E 4
I 4
		if (frags != d) {
I 9
#ifdef tahoe
			/* tahoe compiler workaround */
			int x = frags - dbase;
			blk = blkmap(&sblock, newcg->cg_free, x);
#else
E 9
			blk = blkmap(&sblock, newcg->cg_free, (frags - dbase));
I 9
#endif
E 9
			fragacct(&sblock, blk, newcg->cg_frsum, 1);
E 4
		}
E 10
D 4
		if (bcmp((char *)cgrp.cg_b, (char *)bo, sizeof (bo))) {
			if (debug)
			for (i = 0; i < NRPOS; i++)
				if (bo[n][i] != cgrp.cg_b[n][i])
				printf("cg[%d].cg_b[%d][%d] have %d calc %d\n",
				    c, n, i, cgrp.cg_b[n][i], bo[n][i]);
			offsumbad++;
E 4
I 4
		cstotal.cs_nffree += newcg->cg_cs.cs_nffree;
		cstotal.cs_nbfree += newcg->cg_cs.cs_nbfree;
		cstotal.cs_nifree += newcg->cg_cs.cs_nifree;
		cstotal.cs_ndir += newcg->cg_cs.cs_ndir;
D 10
		if (bcmp(newcg->cg_iused, cgrp.cg_iused, mapsize) != 0 &&
		    dofix(&idesc, "BLK(S) MISSING IN BIT MAPS")) {
			bcopy(newcg->cg_iused, cgrp.cg_iused, mapsize);
			cgdirty();
E 4
		}
D 4
	}
out5:
	if (dupblk)
		pwarn("%d DUP BLKS IN BIT MAPS\n", dupblk);
	if (fixcg == 0) {
		if ((b = n_blks+n_ffree+sblock.fs_frag*n_bfree+n_index+n_bad) != fmax) {
			pwarn("%ld BLK(S) MISSING\n", fmax - b);
			fixcg = 1;
		} else if (inosumbad + offsumbad + frsumbad + sbsumbad) {
			pwarn("SUMMARY INFORMATION %s%s%s%sBAD\n",
			    inosumbad ? "(INODE FREE) " : "",
			    offsumbad ? "(BLOCK OFFSETS) " : "",
			    frsumbad ? "(FRAG SUMMARIES) " : "",
			    sbsumbad ? "(SUPER BLOCK SUMMARIES) " : "");
			fixcg = 1;
		} else if (n_ffree != sblock.fs_cstotal.cs_nffree ||
		    n_bfree != sblock.fs_cstotal.cs_nbfree) {
			pwarn("FREE BLK COUNT(S) WRONG IN SUPERBLK");
			if (preen)
				printf(" (FIXED)\n");
			if (preen || reply("FIX") == 1) {
				sblock.fs_cstotal.cs_nffree = n_ffree;
				sblock.fs_cstotal.cs_nbfree = n_bfree;
				sbdirty();
			}
E 4
I 4
		if (bcmp((char *)newcg, (char *)&cgrp, sumsize) != 0 &&
		    dofix(&idesc, "SUMMARY INFORMATION BAD")) {
			bcopy((char *)newcg, (char *)&cgrp, sumsize);
			cgdirty();
E 4
		}
E 10
D 4
	}
	if (fixcg) {
		pwarn("BAD CYLINDER GROUPS");
		if (preen)
			printf(" (SALVAGED)\n");
		else if (reply("SALVAGE") == 0)
			fixcg = 0;
	}
}

pass5check(blk, size)
	daddr_t blk;
	long size;
{

	if (outrange(blk, (int)size)) {
		fixcg = 1;
		if (preen)
			pfatal("BAD BLOCKS IN BIT MAPS.");
		if (++badblk >= MAXBAD) {
			printf("EXCESSIVE BAD BLKS IN BIT MAPS.");
			if (reply("CONTINUE") == 0)
				errexit("");
			return (STOP);
E 4
I 4
D 11
		cs = &sblock.fs_cs(&sblock, c);
E 11
I 11
		cs = &fs->fs_cs(fs, c);
E 11
D 33
		if (bcmp((char *)&newcg->cg_cs, (char *)cs, sizeof *cs) != 0 &&
E 33
I 33
		if (memcmp(&newcg->cg_cs, cs, sizeof *cs) != 0 &&
E 33
D 12
		    dofix(&idesc, "FREE BLK COUNT(S) WRONG IN SUPERBLK")) {
E 12
I 12
		    dofix(&idesc[0], "FREE BLK COUNT(S) WRONG IN SUPERBLK")) {
E 12
D 33
			bcopy((char *)&newcg->cg_cs, (char *)cs, sizeof *cs);
E 33
I 33
			memmove(cs, &newcg->cg_cs, sizeof *cs);
E 33
			sbdirty();
E 4
		}
I 10
D 23
		if (cvtflag) {
E 23
I 23
		if (doinglevel1) {
E 23
D 11
			bcopy((char *)newcg, (char *)&cgrp, sblock.fs_cgsize);
E 11
I 11
D 15
			bcopy((char *)newcg, (char *)cg, fs->fs_cgsize);
E 15
I 15
D 19
			bcopy((char *)newcg, (char *)cg, (int)fs->fs_cgsize);
E 19
I 19
D 33
			bcopy((char *)newcg, (char *)cg, (size_t)fs->fs_cgsize);
E 33
I 33
			memmove(cg, newcg, (size_t)fs->fs_cgsize);
E 33
E 19
E 15
E 11
			cgdirty();
			continue;
		}
D 33
		if (bcmp(cg_inosused(newcg),
E 33
I 33
		if (memcmp(cg_inosused(newcg),
E 33
D 11
			 cg_inosused(&cgrp), mapsize) != 0 &&
E 11
I 11
			 cg_inosused(cg), mapsize) != 0 &&
E 11
D 12
		    dofix(&idesc, "BLK(S) MISSING IN BIT MAPS")) {
E 12
I 12
		    dofix(&idesc[1], "BLK(S) MISSING IN BIT MAPS")) {
E 12
D 11
			bcopy(cg_inosused(newcg), cg_inosused(&cgrp), mapsize);
E 11
I 11
D 19
			bcopy(cg_inosused(newcg), cg_inosused(cg), mapsize);
E 19
I 19
D 33
			bcopy(cg_inosused(newcg), cg_inosused(cg),
E 33
I 33
			memmove(cg_inosused(cg), cg_inosused(newcg),
E 33
			      (size_t)mapsize);
E 19
E 11
			cgdirty();
		}
D 11
		if ((bcmp((char *)newcg, (char *)&cgrp, basesize) != 0 ||
E 11
I 11
D 33
		if ((bcmp((char *)newcg, (char *)cg, basesize) != 0 ||
E 11
		     bcmp((char *)&cg_blktot(newcg)[0],
D 11
			  (char *)&cg_blktot(&cgrp)[0], sumsize) != 0) &&
E 11
I 11
			  (char *)&cg_blktot(cg)[0], sumsize) != 0) &&
E 33
I 33
		if ((memcmp(newcg, cg, basesize) != 0 ||
		     memcmp(&cg_blktot(newcg)[0],
			  &cg_blktot(cg)[0], sumsize) != 0) &&
E 33
E 11
D 12
		    dofix(&idesc, "SUMMARY INFORMATION BAD")) {
E 12
I 12
		    dofix(&idesc[2], "SUMMARY INFORMATION BAD")) {
E 12
D 11
			bcopy((char *)newcg, (char *)&cgrp, basesize);
E 11
I 11
D 19
			bcopy((char *)newcg, (char *)cg, basesize);
E 19
I 19
D 33
			bcopy((char *)newcg, (char *)cg, (size_t)basesize);
E 19
E 11
			bcopy((char *)&cg_blktot(newcg)[0],
D 11
			      (char *)&cg_blktot(&cgrp)[0], sumsize);
E 11
I 11
D 19
			      (char *)&cg_blktot(cg)[0], sumsize);
E 19
I 19
			      (char *)&cg_blktot(cg)[0], (size_t)sumsize);
E 33
I 33
			memmove(cg, newcg, (size_t)basesize);
			memmove(&cg_blktot(cg)[0],
			       &cg_blktot(newcg)[0], (size_t)sumsize);
E 33
E 19
E 11
			cgdirty();
		}
E 10
	}
I 10
D 11
	if (sblock.fs_postblformat == FS_42POSTBLFMT)
		sblock.fs_nrpos = savednrpos;
E 10
D 4
	for (; size > 0; blk++, size--)
		if (getfmap(blk)) {
			fixcg = 1;
			++dupblk;
		} else {
			n_ffree++;
			setfmap(blk);
		}
	return (KEEPON);
E 4
I 4
	if (bcmp((char *)&cstotal, (char *)&sblock.fs_cstotal, sizeof *cs) != 0
E 11
I 11
	if (fs->fs_postblformat == FS_42POSTBLFMT)
		fs->fs_nrpos = savednrpos;
D 33
	if (bcmp((char *)&cstotal, (char *)&fs->fs_cstotal, sizeof *cs) != 0
E 33
I 33
	if (memcmp(&cstotal, &fs->fs_cstotal, sizeof *cs) != 0
E 33
E 11
D 12
	    && dofix(&idesc, "FREE BLK COUNT(S) WRONG IN SUPERBLK")) {
E 12
I 12
	    && dofix(&idesc[0], "FREE BLK COUNT(S) WRONG IN SUPERBLK")) {
E 12
D 11
		bcopy((char *)&cstotal, (char *)&sblock.fs_cstotal, sizeof *cs);
		sblock.fs_ronly = 0;
		sblock.fs_fmod = 0;
E 11
I 11
D 33
		bcopy((char *)&cstotal, (char *)&fs->fs_cstotal, sizeof *cs);
E 33
I 33
		memmove(&fs->fs_cstotal, &cstotal, sizeof *cs);
E 33
		fs->fs_ronly = 0;
		fs->fs_fmod = 0;
E 11
		sbdirty();
	}
E 4
}
E 1
