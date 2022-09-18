h09657
s 00002/00002/00045
d D 8.1 93/06/02 19:56:41 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00046
d D 7.6 90/06/28 22:01:58 bostic 12 11
c new copyright notice
e
s 00001/00001/00056
d D 7.5 90/06/22 17:17:57 karels 11 10
c really, it's an inode (file) number
e
s 00007/00007/00050
d D 7.4 89/05/09 16:35:19 mckusick 10 9
c merge in vnodes
e
s 00010/00005/00047
d D 7.3 88/06/27 18:51:35 bostic 9 8
c install approved copyright notice
e
s 00008/00002/00044
d D 7.2 88/01/07 13:31:05 bostic 8 7
c add Berkeley header
e
s 00001/00001/00045
d D 7.1 86/06/04 23:31:07 mckusick 7 6
c 4.3BSD release version
e
s 00008/00001/00038
d D 6.3 85/12/11 18:55:41 karels 6 5
c clean up stream flow control, fake inodes, address handling
e
s 00007/00001/00032
d D 6.2 85/06/08 15:11:51 mckusick 5 4
c Add copyright
e
s 00000/00000/00033
d D 6.1 83/07/29 06:14:49 sam 4 3
c 4.2 distribution
e
s 00001/00000/00032
d D 5.3 82/11/13 23:08:54 sam 3 2
c merge 4.1b and 4.1c
e
s 00002/00000/00030
d D 5.2 82/08/02 00:05:55 root 2 1
c first cut with UNIX ipc domain
e
s 00030/00000/00000
d D 5.1 82/08/01 12:33:31 root 1 0
c date and time created 82/08/01 12:33:31 by root
e
u
U
t
T
I 1
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*
D 7
 * Copyright (c) 1982 Regents of the University of California.
E 7
I 7
D 10
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 10
I 10
D 13
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 10
E 7
D 8
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 12
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
D 10
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 10
I 10
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 10
E 9
E 8
 *
 *	%W% (Berkeley) %G%
 */
E 5

/*
 * Protocol control block for an active
 * instance of a UNIX internal protocol.
 *
D 10
 * A socket may be associated with an inode in the
 * file system.  If so, the unp_inode pointer holds
 * a reference count to this inode, which should be irele'd
E 10
I 10
 * A socket may be associated with an vnode in the
 * file system.  If so, the unp_vnode pointer holds
 * a reference count to this vnode, which should be irele'd
E 10
 * when the socket goes away.
 *
 * A socket may be connected to another socket, in which
 * case the control block of the socket to which it is connected
 * is given by unp_conn.
 *
 * A socket may be referenced by a number of sockets (e.g. several
 * sockets may be connected to a datagram socket.)  These sockets
 * are in a linked list starting with unp_refs, linked through
 * unp_nextref and null-terminated.  Note that a socket may be referenced
 * by a number of other sockets and may also reference a socket (not
 * necessarily one which is referencing it).  This generates
 * the need for unp_refs and unp_nextref to be separate fields.
I 6
 *
 * Stream sockets keep copies of receive sockbuf sb_cc and sb_mbcnt
 * so that changes in the sockbuf may be computed to modify
 * back pressure on the sender accordingly.
E 6
 */
struct	unpcb {
	struct	socket *unp_socket;	/* pointer back to socket */
D 10
	struct	inode *unp_inode;	/* if associated with file */
I 6
	ino_t	unp_ino;		/* fake inode number */
E 10
I 10
	struct	vnode *unp_vnode;	/* if associated with file */
D 11
	ino_t	unp_vno;		/* fake vnode number */
E 11
I 11
	ino_t	unp_ino;		/* fake inode number */
E 11
E 10
E 6
	struct	unpcb *unp_conn;	/* control block of connected socket */
	struct	unpcb *unp_refs;	/* referencing socket linked list */
	struct 	unpcb *unp_nextref;	/* link in unp_refs list */
I 3
D 6
	struct	mbuf *unp_remaddr;	/* address of connected socket */
E 6
I 6
	struct	mbuf *unp_addr;		/* bound address of socket */
	int	unp_cc;			/* copy of rcv.sb_cc */
	int	unp_mbcnt;		/* copy of rcv.sb_mbcnt */
E 6
E 3
};
I 2

#define	sotounpcb(so)	((struct unpcb *)((so)->so_pcb))
E 2
E 1
