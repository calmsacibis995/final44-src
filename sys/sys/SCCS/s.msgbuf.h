h42451
s 00002/00002/00018
d D 8.1 93/06/02 19:54:26 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00016
d D 7.5 91/05/02 17:40:34 bostic 13 12
c add comments describing the fields
e
s 00001/00001/00019
d D 7.4 90/12/05 15:29:21 mckusick 12 11
c update for new VM
e
s 00001/00011/00019
d D 7.3 90/06/28 21:59:44 bostic 11 10
c new copyright notice
e
s 00015/00004/00015
d D 7.2 88/12/29 14:36:00 bostic 10 9
c use Berkeley specific copyright notice
e
s 00001/00001/00018
d D 7.1 86/06/04 23:25:21 mckusick 9 8
c 4.3BSD release version
e
s 00007/00001/00012
d D 6.3 85/06/08 15:01:59 mckusick 8 7
c Add copyright
e
s 00003/00002/00010
d D 6.2 84/07/17 16:20:31 ralph 7 6
c changes for log device.
e
s 00000/00000/00012
d D 6.1 83/07/29 06:13:13 sam 6 3
c 4.2 distribution
e
s 00001/00001/00012
d R 4.5 81/08/31 02:29:10 root 5 4
c s/2/4/ (# longs in structure; 1 for slop!)
e
s 00003/00002/00010
d R 4.4 81/08/31 01:12:46 wnj 4 3
c new code for /dev/errlog
e
s 00001/00001/00011
d D 4.3 81/08/30 20:58:27 root 3 2
c make message buffer 4096 not 1024 bytes
e
s 00001/00001/00011
d D 4.2 81/02/19 21:41:22 wnj 2 1
c %G%->%E%
e
s 00012/00000/00000
d D 4.1 81/02/19 21:34:18 wnj 1 0
c date and time created 81/02/19 21:34:18 by wnj
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%G%	*/
E 2
I 2
D 8
/*	%M%	%I%	%E%	*/
E 8
I 8
/*
D 9
 * Copyright (c) 1982 Regents of the University of California.
E 9
I 9
D 10
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 9
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
D 14
 * Copyright (c) 1981, 1984 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1981, 1984, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
E 10
 *
I 10
D 11
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 11
I 11
 * %sccs.include.redist.c%
E 11
 *
E 10
 *	%W% (Berkeley) %G%
 */
E 8
E 2

D 7
#define	MSG_MAGIC	0x063060
D 3
#define	MSG_BSIZE	(NBPG*CLSIZE - 2 * sizeof (long))
E 3
I 3
#define	MSG_BSIZE	(4096 - 2 * sizeof (long))
E 7
I 7
D 13
#define	MSG_MAGIC	0x063061
E 13
D 10
#define	MSG_BSIZE	(4096 - 3 * sizeof (long))
E 10
I 10
#define	MSG_BSIZE	(4096 - 3 * sizeof(long))
E 10
E 7
E 3
struct	msgbuf {
I 13
#define	MSG_MAGIC	0x063061
E 13
	long	msg_magic;
D 13
	long	msg_bufx;
I 7
	long	msg_bufr;
E 7
	char	msg_bufc[MSG_BSIZE];
E 13
I 13
	long	msg_bufx;		/* write pointer */
	long	msg_bufr;		/* read pointer */
	char	msg_bufc[MSG_BSIZE];	/* buffer */
E 13
};
#ifdef KERNEL
D 12
struct	msgbuf msgbuf;
E 12
I 12
struct	msgbuf *msgbufp;
E 12
#endif
E 1
