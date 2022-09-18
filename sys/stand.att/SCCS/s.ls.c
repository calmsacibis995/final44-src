h02041
s 00002/00002/00076
d D 8.1 93/06/11 16:01:59 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00077
d D 7.11 93/05/24 22:44:01 mckusick 16 15
c new include location
e
s 00005/00004/00073
d D 7.10 92/10/11 10:01:04 bostic 15 14
c make kernel includes standard
e
s 00001/00011/00076
d D 7.9 90/06/28 21:56:40 bostic 14 13
c new copyright notice
e
s 00000/00002/00087
d D 7.8 90/04/04 16:37:23 mckusick 13 12
c delete unneeded header files
e
s 00006/00006/00083
d D 7.7 90/03/15 20:06:44 mckusick 12 11
c update to use dinode.h instead of inode.h
e
s 00007/00005/00082
d D 7.6 90/03/15 19:54:15 root 11 10
c update location of include files
e
s 00038/00014/00049
d D 7.5 89/03/21 10:03:28 karels 10 9
c omments? allow more than one dir to be listed, ^D<CR> to end; cleanups
e
s 00010/00005/00053
d D 7.4 88/06/29 18:19:17 bostic 9 8
c install approved copyright notice
e
s 00039/00028/00019
d D 7.3 88/05/24 13:31:31 bostic 8 7
c cleanup; work on new file system
e
s 00004/00004/00043
d D 7.2 88/01/28 20:53:07 karels 7 6
c uvax changes; fix devsw index in confxx; header updates
e
s 00001/00001/00046
d D 7.1 86/06/05 01:43:37 mckusick 6 5
c 4.3BSD release version
e
s 00007/00001/00040
d D 6.2 85/06/08 13:09:47 mckusick 5 4
c Add copyright
e
s 00000/00000/00041
d D 6.1 83/07/29 07:47:18 sam 4 3
c 4.2 distribution
e
s 00001/00001/00040
d D 4.2 81/03/15 20:46:21 wnj 3 2
c 
e
s 00000/00000/00041
d D 4.1 80/11/09 16:29:21 bill 2 1
c stamp for 4bsd
e
s 00041/00000/00000
d D 1.1 80/06/28 10:42:53 bill 1 0
c date and time created 80/06/28 10:42:53 by bill
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%G%	*/
E 3
I 3
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*
D 6
 * Copyright (c) 1982 Regents of the University of California.
E 6
I 6
D 8
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
D 17
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1982, 1986, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
E 8
 *
I 8
D 14
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 14
I 14
 * %sccs.include.redist.c%
E 14
E 9
 *
E 8
 *	%W% (Berkeley) %G%
 */
E 5
E 3

D 7
#include "../h/param.h"
#include "../h/inode.h"
#include "../h/ino.h"
#include "../h/dir.h"
E 7
I 7
D 11
#include "param.h"
#include "inode.h"
D 8
#include "ino.h"
E 8
#include "dir.h"
I 8
#include "fs.h"
E 11
I 11
D 15
#include "sys/param.h"
D 12
#include "sys/time.h"
#include "sys/vnode.h"
#include "ufs/inode.h"
E 12
I 12
D 13
#include "ufs/dinode.h"
E 12
#include "ufs/fs.h"
E 13
#include "ufs/dir.h"
E 11
E 8
E 7
#include "saio.h"
I 10
D 11
#include "ttychars.h"
E 11
I 11
#include "sys/ttychars.h"
E 15
I 15
#include <sys/param.h>
#include <sys/ttychars.h>

#include <ufs/ufs/dir.h>
D 16
#include <stand/saio.h>
E 16
I 16
#include <stand.att/saio.h>
E 16
E 15
E 11
E 10

D 8
char line[100];

E 8
main()
{
D 8
	int i;
E 8
I 8
D 12
	struct inode *ip;
E 12
I 12
	struct dinode *ip;
E 12
	int fd;
E 8

D 8
	printf("ls\n");
	do  {
		printf(": "); gets(line);
		i = open(line, 0);
	} while (i < 0);

	ls(i);
E 8
I 8
D 10
	fd = getfile("ls", 0);
	ip = &iob[fd - 3].i_ino;
	if ((ip->i_mode & IFMT) != IFDIR)
		_stop("ls: not a directory");
	if (ip->i_size == 0)
		_stop("ls: zero length directory");
	ls(fd);
E 10
I 10
	for (;;) {
		if ((fd = getfile("ls", 0)) == -1)
			exit();
		ip = &iob[fd - 3].i_ino;
D 12
		if ((ip->i_mode & IFMT) != IFDIR) {
E 12
I 12
		if ((ip->di_mode & IFMT) != IFDIR) {
E 12
			printf("ls: not a directory\n");
			continue;
		}
D 12
		if (ip->i_size == 0) {
E 12
I 12
		if (ip->di_size == 0) {
E 12
			printf("ls: zero length directory\n");
			continue;
		}
		ls(fd);
	}
E 10
E 8
}
I 12

#define CTRL(x)	(x&037)
E 12

I 10
getfile(prompt, mode)
	char *prompt;
	int mode;
{
	int fd;
	char buf[100];

	do {
		printf("%s: ", prompt);
		gets(buf);
		if (buf[0] == CTRL('d') && buf[1] == 0)
			return (-1);
	} while ((fd = open(buf, mode)) <= 0);
	return(fd);
}

E 10
D 8
ls(io)
register io;
E 8
I 8
typedef struct direct	DP;
static
ls(fd)
	register int fd;
E 8
{
D 8
	struct direct d;
	register i;
E 8
I 8
	register int size;
	register char *dp;
	char dirbuf[DIRBLKSIZ];
E 8

D 8
	while (read(io, (char *)&d, sizeof d) == sizeof d) {
		if (d.d_ino == 0)
			continue;
		printf("%d\t", d.d_ino);
		for (i=0; i<DIRSIZ; i++) {
			if (d.d_name[i] == 0)
				break;
			printf("%c", d.d_name[i]);
E 8
I 8
D 10
	printf("\nname->inode\n");
E 10
I 10
	printf("\ninode\tname\n");
E 10
	while ((size = read(fd, dirbuf, DIRBLKSIZ)) == DIRBLKSIZ)
		for(dp = dirbuf; (dp < (dirbuf + size)) &&
		    (dp + ((DP *)dp)->d_reclen) < (dirbuf + size);
		    dp += ((DP *)dp)->d_reclen) {
			if (((DP *)dp)->d_ino == 0)
				continue;
D 10
			if (((DP *)dp)->d_reclen > DIRSIZ(((DP *)dp)))
				continue;
			if (((DP *)dp)->d_namlen > MAXNAMLEN+1)
				_stop("Corrupt file name length!  Run fsck soon!\n");
			printf("%s->%d\n", ((DP *)dp)->d_name,
			    ((DP *)dp)->d_ino);
E 10
I 10
			if (((DP *)dp)->d_namlen > MAXNAMLEN+1) {
				printf("Corrupt file name length!  Run fsck soon!\n");
				return;
			}
			printf("%d\t%s\n", ((DP *)dp)->d_ino,
			    ((DP *)dp)->d_name);
E 10
E 8
		}
D 8
		printf("\n");
	}
E 8
}
E 1
