h42867
s 00003/00000/00045
d D 8.2 95/04/27 11:32:54 mckusick 18 17
c add function prototypes
e
s 00002/00002/00043
d D 8.1 93/06/05 10:56:41 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00044
d D 5.12 92/05/27 22:45:20 mckusick 16 15
c add <sys/time.h> for dinode.h
e
s 00002/00002/00042
d D 5.11 91/11/04 22:20:35 bostic 15 14
c break FFS into UFS/FFS/LFS
e
s 00001/00011/00043
d D 5.10 90/06/01 16:17:30 bostic 14 13
c new copyright notice
e
s 00002/00000/00052
d D 5.9 90/04/29 12:32:11 mckusick 13 12
c skip directories marked DCLEAR
e
s 00019/00034/00033
d D 5.8 90/02/07 00:20:55 mckusick 12 11
c use inoinfo structure to quickly find any orphaned directories
e
s 00001/00001/00066
d D 5.7 90/02/01 23:36:24 mckusick 11 10
c save block pointers of directories as they are encountered in pass1
c so that they do not have to be reread when descending in pass2
e
s 00015/00004/00052
d D 5.6 90/02/01 17:17:47 mckusick 10 9
c convert to BSD only copyright
e
s 00002/00002/00054
d D 5.5 90/02/01 16:18:07 mckusick 9 8
c lint and other aesthetic cleanups
e
s 00001/00003/00055
d D 5.4 89/10/24 19:05:46 mckusick 8 7
c no longer need to include time.h, vnode.h, and inode.h; just include dinode.h
e
s 00004/00002/00054
d D 5.3 89/06/26 21:42:10 mckusick 7 6
c new include file locations engendered by vnodes
e
s 00001/00002/00055
d D 5.2 87/01/07 19:26:44 mckusick 6 5
c be more persistent in trying to read directories; 
c add FOUND return status for routines called from dirscan
e
s 00008/00002/00049
d D 5.1 85/06/05 08:57:29 dist 5 4
c Add copyright
e
s 00000/00001/00051
d D 3.4 85/02/15 12:07:07 mckusick 4 3
c filesize now set by ckinode(); pass1() uses id_entryno to calc block count
e
s 00002/00001/00050
d D 3.3 85/02/11 18:29:30 mckusick 3 2
c ginode() succeeds or exits
e
s 00001/00001/00050
d D 3.2 85/02/07 17:52:14 mckusick 2 1
c code reorganization and cleanup
e
s 00051/00000/00000
d D 3.1 84/03/31 21:03:49 mckusick 1 0
c date and time created 84/03/31 21:03:49 by mckusick
e
u
U
t
T
I 5
/*
D 10
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
D 17
 * Copyright (c) 1980, 1986 The Regents of the University of California.
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
D 14
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
E 14
I 14
 * %sccs.include.redist.c%
E 14
E 10
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
D 10
#endif not lint
E 10
I 10
#endif /* not lint */
E 10
E 5

#include <sys/param.h>
I 16
#include <sys/time.h>
I 18

E 18
E 16
D 7
#include <sys/inode.h>
#include <sys/fs.h>
E 7
I 7
D 8
#include <sys/time.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
E 8
I 8
D 15
#include <ufs/dinode.h>
E 8
#include <ufs/fs.h>
E 15
I 15
#include <ufs/ufs/dinode.h>
#include <ufs/ffs/fs.h>
I 18

E 18
E 15
E 7
#include "fsck.h"

I 18
void
E 18
D 12
int	pass2check();

E 12
pass3()
{
D 9
	register DINODE *dp;
E 9
I 9
D 12
	register struct dinode *dp;
E 9
	struct inodesc idesc;
	ino_t inumber, orphan;
E 12
I 12
	register struct inoinfo **inpp, *inp;
	ino_t orphan;
E 12
	int loopcnt;

D 12
	bzero((char *)&idesc, sizeof(struct inodesc));
	idesc.id_type = DATA;
	for (inumber = ROOTINO; inumber <= lastino; inumber++) {
		if (statemap[inumber] == DSTATE) {
			pathp = pathname;
			*pathp++ = '?';
			*pathp = '\0';
			idesc.id_func = findino;
D 2
			srchname = "..";
E 2
I 2
			idesc.id_name = "..";
E 2
			idesc.id_parent = inumber;
			loopcnt = 0;
			do {
				orphan = idesc.id_parent;
D 3
				if ((dp = ginode(orphan)) == NULL)
E 3
I 3
D 9
				if (orphan < ROOTINO || orphan > imax)
E 9
I 9
				if (orphan < ROOTINO || orphan > maxino)
E 9
E 3
					break;
I 3
D 11
				dp = ginode(orphan);
E 11
I 11
				dp = getcacheino(orphan);
E 11
E 3
				idesc.id_parent = 0;
D 4
				idesc.id_filesize = dp->di_size;
E 4
				idesc.id_number = orphan;
D 6
				(void)ckinode(dp, &idesc);
				if (idesc.id_parent == 0)
E 6
I 6
				if ((ckinode(dp, &idesc) & FOUND) == 0)
E 6
					break;
				if (loopcnt >= sblock.fs_cstotal.cs_ndir)
					break;
				loopcnt++;
			} while (statemap[idesc.id_parent] == DSTATE);
			if (linkup(orphan, idesc.id_parent) == 1) {
				idesc.id_func = pass2check;
				idesc.id_number = lfdir;
				descend(&idesc, orphan);
			}
E 12
I 12
	for (inpp = &inpsort[inplast - 1]; inpp >= inpsort; inpp--) {
		inp = *inpp;
		if (inp->i_number == ROOTINO ||
		    !(inp->i_parent == 0 || statemap[inp->i_number] == DSTATE))
			continue;
I 13
		if (statemap[inp->i_number] == DCLEAR)
			continue;
E 13
		for (loopcnt = 0; ; loopcnt++) {
			orphan = inp->i_number;
			if (inp->i_parent == 0 ||
			    statemap[inp->i_parent] != DSTATE ||
			    loopcnt > numdirs)
				break;
			inp = getinoinfo(inp->i_parent);
E 12
		}
I 12
		(void)linkup(orphan, inp->i_dotdot);
		inp->i_parent = inp->i_dotdot = lfdir;
		lncntp[lfdir]--;
		statemap[orphan] = DFOUND;
		propagate();
E 12
	}
}
E 1
