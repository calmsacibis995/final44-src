h64196
s 00008/00009/00433
d D 8.9 95/04/28 10:38:09 bostic 39 38
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00021/00013/00421
d D 8.8 95/04/27 11:33:03 mckusick 38 37
c add function prototypes
e
s 00005/00006/00429
d D 8.7 95/01/06 17:33:18 mckusick 37 36
c consistency
e
s 00018/00000/00417
d D 8.6 94/10/27 15:46:56 mckusick 36 35
c byte swapping prototype directory entries on old little
c endian filesystems (from mycroft)
e
s 00009/00004/00408
d D 8.5 94/09/13 11:35:29 mckusick 35 34
c additional work to properly recognize whiteouts
e
s 00002/00002/00410
d D 8.4 94/08/14 16:40:00 mckusick 34 33
c IS_WHT is gone, compare directly
e
s 00008/00000/00404
d D 8.3 94/07/28 03:38:46 pendry 33 32
c changes for whiteouts and union filesystem
e
s 00002/00001/00402
d D 8.2 94/02/27 00:04:38 mkm 32 30
c avoid stomping on random blocks when attempting to fix corrupted directories
e
s 00002/00001/00402
d R 8.2 94/02/27 00:03:32 mkm 31 30
c 
e
s 00002/00002/00401
d D 8.1 93/06/05 10:56:36 bostic 30 29
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00003/00396
d D 5.22 93/01/25 12:27:07 mckusick 29 28
c zero length directories are not an error (just deleted)
e
s 00004/00000/00395
d D 5.21 92/07/12 18:22:47 mckusick 28 27
c always have to initialize d_type
e
s 00034/00006/00361
d D 5.20 92/07/02 16:37:44 mckusick 27 26
c fmttype argument to DIRSIZ; check type values in new filesystems
e
s 00001/00000/00366
d D 5.19 92/05/27 22:45:27 mckusick 26 25
c add <sys/time.h> for dinode.h
e
s 00003/00003/00363
d D 5.18 91/11/04 22:20:34 bostic 25 24
c break FFS into UFS/FFS/LFS
e
s 00001/00001/00365
d D 5.17 90/12/28 17:00:54 mckusick 24 23
c minor optimization
e
s 00001/00000/00365
d D 5.16 90/09/18 22:10:13 mckusick 23 22
c have to initialize the di_mode field (from Hibler)
e
s 00003/00004/00362
d D 5.15 90/07/27 16:52:53 mckusick 22 21
c avoid duplicate error messages for short directories
e
s 00009/00008/00357
d D 5.14 90/07/20 16:51:47 mckusick 21 20
c lint (from Torek)
e
s 00001/00011/00364
d D 5.13 90/06/01 16:17:25 bostic 20 19
c new copyright notice
e
s 00001/00001/00374
d D 5.12 90/05/15 19:53:10 bostic 19 18
c string.h is ANSI C include file
e
s 00009/00009/00366
d D 5.11 90/04/29 13:45:59 mckusick 18 16
c skip zero length directories; ask for deletion when found
e
s 00006/00007/00368
d R 5.11 90/04/29 12:31:33 mckusick 17 16
c check for zero length directory sooner
e
s 00004/00000/00371
d D 5.10 90/03/22 18:34:44 mckusick 16 15
c do not complain about unreferenced . and .. entries
e
s 00147/00055/00224
d D 5.9 90/02/07 00:23:02 mckusick 15 14
c check directory contents with a scan in disk block order
c instead of in the order encountered during descent from the root
e
s 00015/00004/00264
d D 5.8 90/02/01 17:17:49 mckusick 14 13
c convert to BSD only copyright
e
s 00019/00018/00249
d D 5.7 90/02/01 16:18:09 mckusick 13 12
c lint and other aesthetic cleanups
e
s 00001/00003/00266
d D 5.6 89/10/24 19:05:48 mckusick 12 11
c no longer need to include time.h, vnode.h, and inode.h; just include dinode.h
e
s 00005/00003/00264
d D 5.5 89/06/26 21:42:07 mckusick 11 10
c new include file locations engendered by vnodes
e
s 00003/00003/00264
d D 5.4 89/02/17 17:02:39 mckusick 10 9
c add -m flag to override default creation mode for lost+found
e
s 00001/00000/00266
d D 5.3 87/03/10 16:22:59 mckusick 9 8
c must save link count when changing file type
e
s 00004/00000/00262
d D 5.2 86/03/05 17:14:37 mckusick 8 7
c add firewall check for bad entry in state map
e
s 00008/00002/00254
d D 5.1 85/06/05 08:57:06 dist 7 6
c Add copyright
e
s 00011/00003/00245
d D 3.6 85/02/15 12:09:05 mckusick 6 5
c calc and print out pathname of offending hard links to directories
e
s 00029/00009/00219
d D 3.5 85/02/14 19:18:33 mckusick 5 4
c recreate root directory if missing or trashed
e
s 00003/00003/00225
d D 3.4 85/02/11 18:29:25 mckusick 4 3
c ginode() succeeds or exits
e
s 00018/00006/00210
d D 3.3 85/02/08 19:15:42 mckusick 3 2
c merge passes 5 and 6 into a single pass
e
s 00001/00001/00215
d D 3.2 85/02/07 17:52:11 mckusick 2 1
c code reorganization and cleanup
e
s 00216/00000/00000
d D 3.1 84/03/31 21:03:48 mckusick 1 0
c date and time created 84/03/31 21:03:48 by mckusick
e
u
U
t
T
I 7
/*
D 14
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 14
I 14
D 30
 * Copyright (c) 1980, 1986 The Regents of the University of California.
 * All rights reserved.
E 30
I 30
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 30
 *
D 20
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
E 20
I 20
 * %sccs.include.redist.c%
E 20
E 14
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
D 14
#endif not lint
E 14
I 14
#endif /* not lint */
E 14
E 7

#include <sys/param.h>
I 26
#include <sys/time.h>
I 38

E 38
I 35
D 37
#include <sys/stat.h>
E 37
E 35
E 26
D 11
#include <sys/inode.h>
#include <sys/fs.h>
#include <sys/dir.h>
E 11
I 11
D 12
#include <sys/time.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
E 12
I 12
D 25
#include <ufs/dinode.h>
E 12
#include <ufs/fs.h>
E 25
I 25
#include <ufs/ufs/dinode.h>
E 25
I 15
D 27
#define KERNEL
E 27
E 15
D 25
#include <ufs/dir.h>
E 25
I 25
#include <ufs/ufs/dir.h>
E 25
I 15
D 27
#undef KERNEL
E 27
I 25
#include <ufs/ffs/fs.h>
E 25
I 21
D 38
#include <stdlib.h>
E 38
I 38

#include <err.h>
E 38
E 21
E 15
E 11
D 19
#include <strings.h>
E 19
I 19
#include <string.h>
I 38

E 38
E 19
#include "fsck.h"

D 15
int	pass2check();
E 15
I 15
#define MINDIRSIZE	(sizeof (struct dirtemplate))
E 15

I 15
D 38
int	pass2check(), blksort();
E 38
I 38
static int blksort __P((const void *, const void *));
static int pass2check __P((struct inodesc *));
E 38

I 38
void
E 38
E 15
pass2()
{
D 13
	register DINODE *dp;
E 13
I 13
	register struct dinode *dp;
E 13
D 15
	struct inodesc rootdesc;
E 15
I 15
	register struct inoinfo **inpp, *inp;
	struct inoinfo **inpend;
	struct inodesc curino;
	struct dinode dino;
	char pathbuf[MAXPATHLEN + 1];
E 15

D 15
	bzero((char *)&rootdesc, sizeof(struct inodesc));
	rootdesc.id_type = ADDR;
	rootdesc.id_func = pass2check;
	rootdesc.id_number = ROOTINO;
	pathp = pathname;
E 15
	switch (statemap[ROOTINO]) {

	case USTATE:
D 5
		errexit("ROOT INODE UNALLOCATED. TERMINATING.\n");
E 5
I 5
		pfatal("ROOT INODE UNALLOCATED");
		if (reply("ALLOCATE") == 0)
D 38
			errexit("");
E 38
I 38
			exit(EEXIT);
E 38
D 10
		if (allocdir(ROOTINO, ROOTINO) != ROOTINO)
E 10
I 10
		if (allocdir(ROOTINO, ROOTINO, 0755) != ROOTINO)
E 10
D 38
			errexit("CANNOT ALLOCATE ROOT INODE\n");
E 38
I 38
			errx(EEXIT, "CANNOT ALLOCATE ROOT INODE");
E 38
D 15
		descend(&rootdesc, ROOTINO);
E 15
		break;
E 5

I 5
	case DCLEAR:
		pfatal("DUPS/BAD IN ROOT INODE");
		if (reply("REALLOCATE")) {
			freeino(ROOTINO);
D 10
			if (allocdir(ROOTINO, ROOTINO) != ROOTINO)
E 10
I 10
			if (allocdir(ROOTINO, ROOTINO, 0755) != ROOTINO)
E 10
D 38
				errexit("CANNOT ALLOCATE ROOT INODE\n");
E 38
I 38
				errx(EEXIT, "CANNOT ALLOCATE ROOT INODE");
E 38
D 15
			descend(&rootdesc, ROOTINO);
E 15
			break;
		}
		if (reply("CONTINUE") == 0)
D 38
			errexit("");
E 38
I 38
			exit(EEXIT);
E 38
D 15
		statemap[ROOTINO] = DSTATE;
		descend(&rootdesc, ROOTINO);
E 15
		break;

E 5
	case FSTATE:
I 3
	case FCLEAR:
E 3
		pfatal("ROOT INODE NOT DIRECTORY");
I 5
		if (reply("REALLOCATE")) {
			freeino(ROOTINO);
D 10
			if (allocdir(ROOTINO, ROOTINO) != ROOTINO)
E 10
I 10
			if (allocdir(ROOTINO, ROOTINO, 0755) != ROOTINO)
E 10
D 38
				errexit("CANNOT ALLOCATE ROOT INODE\n");
E 38
I 38
				errx(EEXIT, "CANNOT ALLOCATE ROOT INODE");
E 38
D 15
			descend(&rootdesc, ROOTINO);
E 15
			break;
		}
E 5
D 4
		if (reply("FIX") == 0 || (dp = ginode(ROOTINO)) == NULL)
E 4
I 4
		if (reply("FIX") == 0)
E 4
D 38
			errexit("");
E 38
I 38
			exit(EEXIT);
E 38
I 4
		dp = ginode(ROOTINO);
E 4
D 35
		dp->di_mode &= ~IFMT;
		dp->di_mode |= IFDIR;
E 35
I 35
D 37
		dp->di_mode &= ~S_IFMT;
		dp->di_mode |= S_IFDIR;
E 37
I 37
		dp->di_mode &= ~IFMT;
		dp->di_mode |= IFDIR;
E 37
E 35
		inodirty();
D 3
		inosumbad++;
E 3
D 15
		statemap[ROOTINO] = DSTATE;
		/* fall into ... */
E 15
I 15
		break;
E 15

	case DSTATE:
D 15
		descend(&rootdesc, ROOTINO);
E 15
		break;
D 5

D 3
	case CLEAR:
E 3
I 3
	case DCLEAR:
E 3
		pfatal("DUPS/BAD IN ROOT INODE");
		printf("\n");
		if (reply("CONTINUE") == 0)
			errexit("");
		statemap[ROOTINO] = DSTATE;
		descend(&rootdesc, ROOTINO);
E 5
I 3

	default:
D 38
		errexit("BAD STATE %d FOR ROOT INODE", statemap[ROOTINO]);
E 38
I 38
		errx(EEXIT, "BAD STATE %d FOR ROOT INODE", statemap[ROOTINO]);
E 38
E 3
	}
I 15
	statemap[ROOTINO] = DFOUND;
I 35
	if (newinofmt) {
		statemap[WINO] = FSTATE;
D 37
		typemap[WINO] = IFTODT(S_IFWHT);
E 37
I 37
		typemap[WINO] = DT_WHT;
E 37
	}
E 35
	/*
	 * Sort the directory list into disk block order.
	 */
D 21
	qsort((char *)inpsort, (int)inplast, sizeof *inpsort, blksort);
E 21
I 21
	qsort((char *)inpsort, (size_t)inplast, sizeof *inpsort, blksort);
E 21
	/*
	 * Check the integrity of each directory.
	 */
D 39
	bzero((char *)&curino, sizeof(struct inodesc));
E 39
I 39
	memset(&curino, 0, sizeof(struct inodesc));
E 39
	curino.id_type = DATA;
	curino.id_func = pass2check;
I 23
D 32
	dino.di_mode = IFDIR;
E 32
E 23
	dp = &dino;
	inpend = &inpsort[inplast];
	for (inpp = inpsort; inpp < inpend; inpp++) {
		inp = *inpp;
I 18
		if (inp->i_isize == 0)
			continue;
E 18
		if (inp->i_isize < MINDIRSIZE) {
			direrror(inp->i_number, "DIRECTORY TOO SHORT");
D 22
			inp->i_isize = MINDIRSIZE;
E 22
I 22
			inp->i_isize = roundup(MINDIRSIZE, DIRBLKSIZ);
E 22
			if (reply("FIX") == 1) {
				dp = ginode(inp->i_number);
D 22
				dp->di_size = MINDIRSIZE;
E 22
I 22
				dp->di_size = inp->i_isize;
E 22
				inodirty();
				dp = &dino;
			}
D 22
		}
		if ((inp->i_isize & (DIRBLKSIZ - 1)) != 0) {
E 22
I 22
		} else if ((inp->i_isize & (DIRBLKSIZ - 1)) != 0) {
E 22
			getpathname(pathbuf, inp->i_number, inp->i_number);
			pwarn("DIRECTORY %s: LENGTH %d NOT MULTIPLE OF %d",
				pathbuf, inp->i_isize, DIRBLKSIZ);
			if (preen)
				printf(" (ADJUSTED)\n");
			inp->i_isize = roundup(inp->i_isize, DIRBLKSIZ);
			if (preen || reply("ADJUST") == 1) {
				dp = ginode(inp->i_number);
				dp->di_size = roundup(inp->i_isize, DIRBLKSIZ);
				inodirty();
				dp = &dino;
			}
		}
I 32
D 39
		bzero((char *)&dino, sizeof(struct dinode));
E 39
I 39
		memset(&dino, 0, sizeof(struct dinode));
E 39
D 35
		dino.di_mode = IFDIR;
E 35
I 35
D 37
		dino.di_mode = S_IFDIR;
E 37
I 37
		dino.di_mode = IFDIR;
E 37
E 35
E 32
		dp->di_size = inp->i_isize;
D 39
		bcopy((char *)&inp->i_blks[0], (char *)&dp->di_db[0],
D 21
			(int)inp->i_numblks);
E 21
I 21
			(size_t)inp->i_numblks);
E 39
I 39
		memmove(&dp->di_db[0], &inp->i_blks[0], (size_t)inp->i_numblks);
E 39
E 21
		curino.id_number = inp->i_number;
		curino.id_parent = inp->i_parent;
		(void)ckinode(dp, &curino);
	}
	/*
	 * Now that the parents of all directories have been found,
	 * make another pass to verify the value of `..'
	 */
	for (inpp = inpsort; inpp < inpend; inpp++) {
		inp = *inpp;
D 18
		if (inp->i_parent == 0)
E 18
I 18
		if (inp->i_parent == 0 || inp->i_isize == 0)
E 18
			continue;
		if (statemap[inp->i_parent] == DFOUND &&
		    statemap[inp->i_number] == DSTATE)
			statemap[inp->i_number] = DFOUND;
		if (inp->i_dotdot == inp->i_parent ||
		    inp->i_dotdot == (ino_t)-1)
			continue;
		if (inp->i_dotdot == 0) {
			inp->i_dotdot = inp->i_parent;
			fileerror(inp->i_parent, inp->i_number, "MISSING '..'");
			if (reply("FIX") == 0)
				continue;
D 21
			makeentry(inp->i_number, inp->i_parent, "..");
E 21
I 21
			(void)makeentry(inp->i_number, inp->i_parent, "..");
E 21
			lncntp[inp->i_parent]--;
			continue;
		}
		fileerror(inp->i_parent, inp->i_number,
D 27
			"BAD INODE NUMBER FOR '..'");
E 27
I 27
		    "BAD INODE NUMBER FOR '..'");
E 27
		if (reply("FIX") == 0)
			continue;
		lncntp[inp->i_dotdot]++;
		lncntp[inp->i_parent]--;
		inp->i_dotdot = inp->i_parent;
		(void)changeino(inp->i_number, "..", inp->i_parent);
	}
	/*
	 * Mark all the directories that can be found from the root.
	 */
	propagate();
E 15
}

I 38
static int
E 38
pass2check(idesc)
	struct inodesc *idesc;
{
D 13
	register DIRECT *dirp = idesc->id_dirp;
E 13
I 13
	register struct direct *dirp = idesc->id_dirp;
E 13
D 15
	char *curpathloc;
E 15
I 15
	register struct inoinfo *inp;
E 15
	int n, entrysize, ret = 0;
D 13
	DINODE *dp;
	DIRECT proto;
E 13
I 13
	struct dinode *dp;
I 18
	char *errmsg;
E 18
	struct direct proto;
E 13
I 6
D 15
	char namebuf[BUFSIZ];
E 15
I 15
	char namebuf[MAXPATHLEN + 1];
	char pathbuf[MAXPATHLEN + 1];
E 15
E 6

I 27
	/*
	 * If converting, set directory entry type.
	 */
	if (doinglevel2 && dirp->d_ino > 0 && dirp->d_ino < maxino) {
		dirp->d_type = typemap[dirp->d_ino];
		ret |= ALTERED;
	}
E 27
	/* 
	 * check for "."
	 */
	if (idesc->id_entryno != 0)
		goto chk1;
	if (dirp->d_ino != 0 && strcmp(dirp->d_name, ".") == 0) {
		if (dirp->d_ino != idesc->id_number) {
D 13
			direrr(idesc->id_number, "BAD INODE NUMBER FOR '.'");
E 13
I 13
			direrror(idesc->id_number, "BAD INODE NUMBER FOR '.'");
E 13
			dirp->d_ino = idesc->id_number;
			if (reply("FIX") == 1)
				ret |= ALTERED;
		}
I 27
		if (newinofmt && dirp->d_type != DT_DIR) {
			direrror(idesc->id_number, "BAD TYPE VALUE FOR '.'");
			dirp->d_type = DT_DIR;
			if (reply("FIX") == 1)
				ret |= ALTERED;
		}
E 27
		goto chk1;
	}
D 13
	direrr(idesc->id_number, "MISSING '.'");
E 13
I 13
	direrror(idesc->id_number, "MISSING '.'");
E 13
	proto.d_ino = idesc->id_number;
I 27
	if (newinofmt)
		proto.d_type = DT_DIR;
I 28
	else
		proto.d_type = 0;
E 28
E 27
	proto.d_namlen = 1;
	(void)strcpy(proto.d_name, ".");
I 36
#	if BYTE_ORDER == LITTLE_ENDIAN
		if (!newinofmt) {
			u_char tmp;

			tmp = proto.d_type;
			proto.d_type = proto.d_namlen;
			proto.d_namlen = tmp;
		}
#	endif
E 36
D 27
	entrysize = DIRSIZ(&proto);
E 27
I 27
	entrysize = DIRSIZ(0, &proto);
E 27
	if (dirp->d_ino != 0 && strcmp(dirp->d_name, "..") != 0) {
		pfatal("CANNOT FIX, FIRST ENTRY IN DIRECTORY CONTAINS %s\n",
			dirp->d_name);
	} else if (dirp->d_reclen < entrysize) {
		pfatal("CANNOT FIX, INSUFFICIENT SPACE TO ADD '.'\n");
	} else if (dirp->d_reclen < 2 * entrysize) {
		proto.d_reclen = dirp->d_reclen;
D 21
		bcopy((char *)&proto, (char *)dirp, entrysize);
E 21
I 21
D 39
		bcopy((char *)&proto, (char *)dirp, (size_t)entrysize);
E 39
I 39
		memmove(dirp, &proto, (size_t)entrysize);
E 39
E 21
		if (reply("FIX") == 1)
			ret |= ALTERED;
	} else {
		n = dirp->d_reclen - entrysize;
		proto.d_reclen = entrysize;
D 21
		bcopy((char *)&proto, (char *)dirp, entrysize);
E 21
I 21
D 39
		bcopy((char *)&proto, (char *)dirp, (size_t)entrysize);
E 39
I 39
		memmove(dirp, &proto, (size_t)entrysize);
E 39
E 21
		idesc->id_entryno++;
		lncntp[dirp->d_ino]--;
D 13
		dirp = (DIRECT *)((char *)(dirp) + entrysize);
E 13
I 13
		dirp = (struct direct *)((char *)(dirp) + entrysize);
E 13
D 21
		bzero((char *)dirp, n);
E 21
I 21
D 39
		bzero((char *)dirp, (size_t)n);
E 39
I 39
		memset(dirp, 0, (size_t)n);
E 39
E 21
		dirp->d_reclen = n;
		if (reply("FIX") == 1)
			ret |= ALTERED;
	}
chk1:
	if (idesc->id_entryno > 1)
		goto chk2;
D 15
	proto.d_ino = idesc->id_parent;
E 15
I 15
	inp = getinoinfo(idesc->id_number);
	proto.d_ino = inp->i_parent;
I 27
	if (newinofmt)
		proto.d_type = DT_DIR;
I 28
	else
		proto.d_type = 0;
E 28
E 27
E 15
	proto.d_namlen = 2;
	(void)strcpy(proto.d_name, "..");
I 36
#	if BYTE_ORDER == LITTLE_ENDIAN
		if (!newinofmt) {
			u_char tmp;

			tmp = proto.d_type;
			proto.d_type = proto.d_namlen;
			proto.d_namlen = tmp;
		}
#	endif
E 36
D 27
	entrysize = DIRSIZ(&proto);
E 27
I 27
	entrysize = DIRSIZ(0, &proto);
E 27
	if (idesc->id_entryno == 0) {
D 27
		n = DIRSIZ(dirp);
E 27
I 27
		n = DIRSIZ(0, dirp);
E 27
		if (dirp->d_reclen < n + entrysize)
			goto chk2;
		proto.d_reclen = dirp->d_reclen - n;
		dirp->d_reclen = n;
		idesc->id_entryno++;
		lncntp[dirp->d_ino]--;
D 13
		dirp = (DIRECT *)((char *)(dirp) + n);
E 13
I 13
		dirp = (struct direct *)((char *)(dirp) + n);
E 13
D 15
		bzero((char *)dirp, n);
		dirp->d_reclen = n;
E 15
I 15
D 21
		bzero((char *)dirp, (int)proto.d_reclen);
E 21
I 21
D 39
		bzero((char *)dirp, (size_t)proto.d_reclen);
E 39
I 39
		memset(dirp, 0, (size_t)proto.d_reclen);
E 39
E 21
		dirp->d_reclen = proto.d_reclen;
E 15
	}
	if (dirp->d_ino != 0 && strcmp(dirp->d_name, "..") == 0) {
D 15
		if (dirp->d_ino != idesc->id_parent) {
D 13
			direrr(idesc->id_number, "BAD INODE NUMBER FOR '..'");
E 13
I 13
			direrror(idesc->id_number, "BAD INODE NUMBER FOR '..'");
E 13
			dirp->d_ino = idesc->id_parent;
			if (reply("FIX") == 1)
				ret |= ALTERED;
		}
E 15
I 15
		inp->i_dotdot = dirp->d_ino;
I 27
		if (newinofmt && dirp->d_type != DT_DIR) {
			direrror(idesc->id_number, "BAD TYPE VALUE FOR '..'");
			dirp->d_type = DT_DIR;
			if (reply("FIX") == 1)
				ret |= ALTERED;
		}
E 27
E 15
		goto chk2;
	}
D 13
	direrr(idesc->id_number, "MISSING '..'");
E 13
I 13
D 15
	direrror(idesc->id_number, "MISSING '..'");
E 15
E 13
	if (dirp->d_ino != 0 && strcmp(dirp->d_name, ".") != 0) {
I 15
		fileerror(inp->i_parent, idesc->id_number, "MISSING '..'");
E 15
		pfatal("CANNOT FIX, SECOND ENTRY IN DIRECTORY CONTAINS %s\n",
			dirp->d_name);
I 15
		inp->i_dotdot = (ino_t)-1;
E 15
	} else if (dirp->d_reclen < entrysize) {
I 15
		fileerror(inp->i_parent, idesc->id_number, "MISSING '..'");
E 15
		pfatal("CANNOT FIX, INSUFFICIENT SPACE TO ADD '..'\n");
D 15
	} else {
E 15
I 15
		inp->i_dotdot = (ino_t)-1;
	} else if (inp->i_parent != 0) {
		/*
		 * We know the parent, so fix now.
		 */
		inp->i_dotdot = inp->i_parent;
		fileerror(inp->i_parent, idesc->id_number, "MISSING '..'");
E 15
		proto.d_reclen = dirp->d_reclen;
D 21
		bcopy((char *)&proto, (char *)dirp, entrysize);
E 21
I 21
D 39
		bcopy((char *)&proto, (char *)dirp, (size_t)entrysize);
E 39
I 39
		memmove(dirp, &proto, (size_t)entrysize);
E 39
E 21
		if (reply("FIX") == 1)
			ret |= ALTERED;
	}
I 15
	idesc->id_entryno++;
	if (dirp->d_ino != 0)
		lncntp[dirp->d_ino]--;
	return (ret|KEEPON);
E 15
chk2:
	if (dirp->d_ino == 0)
		return (ret|KEEPON);
	if (dirp->d_namlen <= 2 &&
	    dirp->d_name[0] == '.' &&
	    idesc->id_entryno >= 2) {
		if (dirp->d_namlen == 1) {
D 13
			direrr(idesc->id_number, "EXTRA '.' ENTRY");
E 13
I 13
			direrror(idesc->id_number, "EXTRA '.' ENTRY");
E 13
			dirp->d_ino = 0;
			if (reply("FIX") == 1)
				ret |= ALTERED;
			return (KEEPON | ret);
		}
		if (dirp->d_name[1] == '.') {
D 13
			direrr(idesc->id_number, "EXTRA '..' ENTRY");
E 13
I 13
			direrror(idesc->id_number, "EXTRA '..' ENTRY");
E 13
			dirp->d_ino = 0;
			if (reply("FIX") == 1)
				ret |= ALTERED;
			return (KEEPON | ret);
		}
	}
D 15
	curpathloc = pathp;
	*pathp++ = '/';
	if (pathp + dirp->d_namlen >= endpathname) {
		*pathp = '\0';
		errexit("NAME TOO LONG %s%s\n", pathname, dirp->d_name);
	}
D 13
	bcopy(dirp->d_name, pathp, dirp->d_namlen + 1);
E 13
I 13
	bcopy(dirp->d_name, pathp, (int)dirp->d_namlen + 1);
E 13
	pathp += dirp->d_namlen;
E 15
	idesc->id_entryno++;
	n = 0;
D 13
	if (dirp->d_ino > imax || dirp->d_ino <= 0) {
		direrr(dirp->d_ino, "I OUT OF RANGE");
E 13
I 13
D 24
	if (dirp->d_ino > maxino || dirp->d_ino <= 0) {
E 24
I 24
	if (dirp->d_ino > maxino) {
E 24
D 15
		direrror(dirp->d_ino, "I OUT OF RANGE");
E 15
I 15
		fileerror(idesc->id_number, dirp->d_ino, "I OUT OF RANGE");
E 15
E 13
		n = reply("REMOVE");
I 33
	} else if (newinofmt &&
D 34
		   ((dirp->d_ino == WINO && !DT_ISWHT(dirp->d_type)) ||
		    (dirp->d_ino != WINO && DT_ISWHT(dirp->d_type)))) {
E 34
I 34
		   ((dirp->d_ino == WINO && dirp->d_type != DT_WHT) ||
		    (dirp->d_ino != WINO && dirp->d_type == DT_WHT))) {
E 34
		fileerror(idesc->id_number, dirp->d_ino, "BAD WHITEOUT ENTRY");
		dirp->d_ino = WINO;
		dirp->d_type = DT_WHT;
		if (reply("FIX") == 1)
			ret |= ALTERED;
E 33
	} else {
again:
		switch (statemap[dirp->d_ino]) {
		case USTATE:
I 16
			if (idesc->id_entryno <= 2)
				break;
E 16
D 13
			direrr(dirp->d_ino, "UNALLOCATED");
E 13
I 13
D 15
			direrror(dirp->d_ino, "UNALLOCATED");
E 15
I 15
			fileerror(idesc->id_number, dirp->d_ino, "UNALLOCATED");
E 15
E 13
			n = reply("REMOVE");
			break;

D 3
		case CLEAR:
E 3
I 3
		case DCLEAR:
		case FCLEAR:
I 16
			if (idesc->id_entryno <= 2)
				break;
E 16
E 3
D 13
			direrr(dirp->d_ino, "DUP/BAD");
E 13
I 13
D 15
			direrror(dirp->d_ino, "DUP/BAD");
E 15
I 15
D 18
			fileerror(idesc->id_number, dirp->d_ino, "DUP/BAD");
E 18
I 18
D 29
			if (statemap[dirp->d_ino] == DCLEAR)
				errmsg = "ZERO LENGTH DIRECTORY";
			else
E 29
I 29
			if (statemap[dirp->d_ino] == FCLEAR)
E 29
				errmsg = "DUP/BAD";
I 29
			else if (!preen)
				errmsg = "ZERO LENGTH DIRECTORY";
			else {
				n = 1;
				break;
			}
E 29
			fileerror(idesc->id_number, dirp->d_ino, errmsg);
E 18
E 15
E 13
			if ((n = reply("REMOVE")) == 1)
				break;
D 4
			if ((dp = ginode(dirp->d_ino)) == NULL)
				break;
E 4
I 4
			dp = ginode(dirp->d_ino);
E 4
D 2
			statemap[dirp->d_ino] = DIRCT ? DSTATE : FSTATE;
E 2
I 2
D 13
			statemap[dirp->d_ino] = DIRCT(dp) ? DSTATE : FSTATE;
E 13
I 13
			statemap[dirp->d_ino] =
D 35
			    (dp->di_mode & IFMT) == IFDIR ? DSTATE : FSTATE;
E 35
I 35
D 37
			    (dp->di_mode & S_IFMT) == S_IFDIR ? DSTATE : FSTATE;
E 37
I 37
			    (dp->di_mode & IFMT) == IFDIR ? DSTATE : FSTATE;
E 37
E 35
E 13
I 9
			lncntp[dirp->d_ino] = dp->di_nlink;
E 9
E 2
			goto again;

I 15
		case DSTATE:
			if (statemap[idesc->id_number] == DFOUND)
				statemap[dirp->d_ino] = DFOUND;
			/* fall through */

E 15
I 3
		case DFOUND:
D 6
			if (idesc->id_entryno > 2)
				pwarn("WARNING: %s IS %s\n", pathname,
				    "AN EXTRANEOUS HARD LINK TO A DIRECTORY");
E 6
I 6
D 15
			if (idesc->id_entryno > 2) {
E 15
I 15
			inp = getinoinfo(dirp->d_ino);
D 18
			if (inp->i_isize == 0) {
				direrror(dirp->d_ino, "ZERO LENGTH DIRECTORY");
				if ((n = reply("REMOVE")) == 1) {
					statemap[dirp->d_ino] = DCLEAR;
					break;
				}
			}
E 18
			if (inp->i_parent != 0 && idesc->id_entryno > 2) {
				getpathname(pathbuf, idesc->id_number,
				    idesc->id_number);
E 15
				getpathname(namebuf, dirp->d_ino, dirp->d_ino);
D 15
				pwarn("%s %s %s\n", pathname,
E 15
I 15
				pwarn("%s %s %s\n", pathbuf,
E 15
				    "IS AN EXTRANEOUS HARD LINK TO DIRECTORY",
				    namebuf);
				if (preen)
					printf(" (IGNORED)\n");
				else if ((n = reply("REMOVE")) == 1)
					break;
			}
I 15
			if (idesc->id_entryno > 2)
				inp->i_parent = idesc->id_number;
E 15
E 6
			/* fall through */

E 3
		case FSTATE:
I 27
			if (newinofmt && dirp->d_type != typemap[dirp->d_ino]) {
				fileerror(idesc->id_number, dirp->d_ino,
				    "BAD TYPE VALUE");
				dirp->d_type = typemap[dirp->d_ino];
				if (reply("FIX") == 1)
					ret |= ALTERED;
			}
E 27
			lncntp[dirp->d_ino]--;
			break;

D 15
		case DSTATE:
			descend(idesc, dirp->d_ino);
D 3
			if (statemap[dirp->d_ino] != CLEAR) {
E 3
I 3
			if (statemap[dirp->d_ino] == DFOUND) {
E 3
				lncntp[dirp->d_ino]--;
D 3
			} else {
E 3
I 3
			} else if (statemap[dirp->d_ino] == DCLEAR) {
E 3
				dirp->d_ino = 0;
				ret |= ALTERED;
D 3
			}
E 3
I 3
			} else
				errexit("BAD RETURN STATE %d FROM DESCEND",
				    statemap[dirp->d_ino]);
E 3
			break;
I 8

E 15
		default:
D 38
			errexit("BAD STATE %d FOR INODE I=%d",
E 38
I 38
			errx(EEXIT, "BAD STATE %d FOR INODE I=%d",
E 38
			    statemap[dirp->d_ino], dirp->d_ino);
E 8
		}
	}
D 15
	pathp = curpathloc;
	*pathp = '\0';
E 15
	if (n == 0)
		return (ret|KEEPON);
	dirp->d_ino = 0;
	return (ret|KEEPON|ALTERED);
I 15
}

/*
 * Routine to sort disk blocks.
 */
D 38
blksort(inpp1, inpp2)
	struct inoinfo **inpp1, **inpp2;
E 38
I 38
static int
blksort(arg1, arg2)
	const void *arg1, *arg2;
E 38
{

D 38
	return ((*inpp1)->i_blks[0] - (*inpp2)->i_blks[0]);
E 38
I 38
	return ((*(struct inoinfo **)arg1)->i_blks[0] -
		(*(struct inoinfo **)arg2)->i_blks[0]);
E 38
E 15
}
E 1
