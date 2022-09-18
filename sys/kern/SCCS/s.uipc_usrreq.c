h28090
s 00001/00001/00812
d D 8.9 95/05/14 00:18:06 mckusick 100 99
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK
e
s 00001/00001/00812
d D 8.8 95/05/01 21:21:42 mckusick 99 98
c missing second parameter to closef (from Poul-Henning Kamp)
e
s 00011/00002/00802
d D 8.7 95/02/14 10:46:47 cgd 98 97
c return types, KNF, some protos.
e
s 00009/00003/00795
d D 8.6 95/01/09 18:22:27 cgd 97 96
c return types, 64-bit changes: ioctl cmd -> u_long, casts, etc.
e
s 00005/00004/00793
d D 8.5 94/08/22 10:20:03 mckusick 96 95
c use new queue.h data structures
e
s 00001/00001/00796
d D 8.4 94/08/11 00:24:20 mckusick 95 94
c LEASE_CHECK => VOP_LEASE
e
s 00000/00001/00797
d D 8.3 94/01/04 18:44:02 bostic 94 93
c lint
e
s 00001/00001/00797
d D 8.2 93/09/04 10:35:03 mckusick 93 92
c use symbolic names for access permissions
e
s 00002/00002/00796
d D 8.1 93/06/10 22:00:06 bostic 92 91
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00003/00788
d D 7.40 93/04/30 19:07:21 mckusick 91 90
c a better approach than 7.39 to avoid duplicate closef's (from karels@bsdi.com)
e
s 00002/00000/00789
d D 7.39 93/02/26 11:27:15 mckusick 90 89
c avoid duplicate closef's
e
s 00015/00015/00774
d D 7.38 92/10/11 10:39:01 bostic 89 88
c make kernel includes standard
e
s 00053/00004/00736
d D 7.37 92/07/24 13:52:39 mckusick 88 87
c fix for garbage collection from bsy+@CS.CMU.EDU (Bennet Yee)
e
s 00001/00001/00739
d D 7.36 92/07/12 23:45:29 pendry 87 86
c wrong sense in checking for free descriptors available
e
s 00000/00004/00740
d D 7.35 92/07/03 01:40:23 mckusick 86 85
c delete USES
e
s 00004/00000/00740
d D 7.34 92/05/14 17:35:06 heideman 85 76
c vnode interface conversion
e
s 00004/00000/00740
d R 7.34 92/05/14 15:50:39 heideman 84 76
c vnode interface conversion
e
s 00004/00000/00740
d R 7.34 92/05/14 14:53:58 heideman 83 76
c vnode interface conversion
e
s 00004/00000/00740
d R 7.34 92/05/14 12:58:36 heideman 82 76
c vnode interface conversion
e
s 00004/00000/00740
d R 7.34 92/05/14 11:56:15 heideman 81 76
c vnode interface conversion
e
s 00004/00000/00740
d R 7.34 92/05/14 10:36:17 heideman 80 76
c vnode interface conversion
e
s 00004/00000/00740
d R 7.34 92/05/13 23:15:23 heideman 79 76
c vnode interface conversion
e
s 00004/00000/00740
d R 7.34 92/05/13 19:00:33 heideman 78 76
c vnode interface conversion
e
s 00004/00000/00740
d R 7.34 92/05/13 18:32:35 heideman 77 76
c vnode interface conversion
e
s 00003/00002/00737
d D 7.33 92/05/13 16:49:05 mckusick 76 75
c cannot follow a pointer after structure that contains it is freed
e
s 00001/00000/00738
d D 7.32 92/03/15 13:35:57 torek 75 74
c must include systm.h to get decl for panic (for gcc)
e
s 00003/00000/00735
d D 7.31 92/03/13 16:46:09 mckusick 74 73
c paranoia
e
s 00014/00021/00721
d D 7.30 92/02/03 23:34:45 mckusick 73 72
c new namei calling convention
e
s 00002/00002/00740
d D 7.29 92/01/22 09:37:36 heideman 72 71
c lookup converted to new form
e
s 00001/00000/00741
d D 7.28 92/01/14 12:25:09 mckusick 71 70
c lease check when binding unix domain sockets
e
s 00001/00001/00740
d D 7.27 91/12/19 21:07:41 karels 70 69
c unp_discard has to pass a (null) proc ptr to closef
e
s 00003/00003/00738
d D 7.26 91/06/03 20:25:37 mckusick 69 68
c file structures are now dynamically allocated and linked together on a list
e
s 00017/00012/00724
d D 7.25 91/04/15 23:54:53 mckusick 68 67
c add proc pointers to appropriate VOP and vnode operations;
c propogate proc pointer down to levels where needed
e
s 00005/00005/00731
d D 7.24 91/03/24 15:16:30 karels 67 65
c rm user.h, OFILE
e
s 00001/00002/00734
d R 7.24 91/03/24 14:43:47 karels 66 65
c rm user.h
e
s 00015/00011/00721
d D 7.23 91/03/17 15:41:55 karels 65 64
c more-or-less working with new proc & user structs
e
s 00009/00005/00723
d D 7.22 91/01/10 23:43:41 mckusick 64 63
c add dynamically allocated file descriptors
e
s 00021/00006/00707
d D 7.21 90/07/27 22:30:39 karels 63 62
c don't lose control mbufs if sockbuf full; make shutdown on stream socket
c produce eof on other end (from sam); can't do sbwait in uipc_gc, at least
c for now
e
s 00001/00011/00712
d D 7.20 90/06/28 21:25:06 bostic 62 61
c new copyright notice
e
s 00004/00001/00719
d D 7.19 90/06/21 11:07:34 mckusick 61 60
c have to check for "." when releasing parent directory
e
s 00002/00000/00718
d D 7.18 90/05/30 11:38:51 mckusick 60 59
c VOP_ABORTOP is no longer responsible for unlocking and vreleing vnodes
e
s 00001/00002/00717
d D 7.17 90/05/04 14:15:09 mckusick 59 58
c delete unneeded headers
e
s 00001/00001/00718
d D 7.16 90/05/03 18:44:54 mckusick 58 57
c vattr_null => VATTR_NULL
e
s 00024/00020/00695
d D 7.15 90/04/16 10:26:17 karels 57 56
c merge rights into control, change sbappendrights to sbappendcontrol;
c check for other control types; free control here, not above
e
s 00029/00020/00686
d D 7.14 90/04/05 11:55:35 sklower 56 55
c fast hack at making rights special case of ancillary data
e
s 00001/00001/00705
d D 7.13 89/10/19 23:34:13 mckusick 55 54
c closef now returns and error (which is ignored)
e
s 00002/00002/00704
d D 7.12 89/07/03 17:58:53 mckusick 54 53
c do not need vn_access, just use VOP_ACCESS directly
e
s 00013/00012/00693
d D 7.11 89/05/09 17:03:11 mckusick 53 52
c merge in vnodes
e
s 00001/00015/00704
d D 7.10 89/05/02 16:37:18 mckusick 52 50
i 51
c integrate back branch -r7.2.1.1
e
s 00051/00047/00631
d D 7.2.1.1 89/05/02 16:30:06 mckusick 51 41
c merge in vnode changes
e
s 00003/00002/00709
d D 7.9 89/04/22 12:26:37 sklower 50 48
c checkpoint for version to be handed to NIST, simple tp4 connection
e
s 00001/00001/00710
d R 7.9 88/10/12 14:59:32 karels 49 48
c mark semi working version before var length sockaddrs (by sklower)
e
s 00011/00005/00700
d D 7.8 88/08/22 17:51:44 karels 48 47
c working with new mbufs
e
s 00010/00005/00695
d D 7.7 88/06/29 17:20:10 bostic 47 46
c install approved copyright notice
e
s 00015/00013/00685
d D 7.6 88/05/25 18:08:36 karels 46 45
c in attach, don't set sockbuf limits if set (from sonewconn); lint
e
s 00022/00008/00676
d D 7.5 88/05/24 09:47:47 karels 45 43
c fixes for unp_addr's from glenn skinner/dsr, but don't break datagrams
e
s 00023/00006/00678
d R 7.5 88/05/14 14:34:44 karels 44 43
c fixes for unp_addr's from glenn skinner/dsr
e
s 00002/00002/00682
d D 7.4 88/02/08 13:27:23 karels 43 42
c don't trip over files with type socket, f_data null
e
s 00008/00002/00676
d D 7.3 88/01/07 13:26:26 bostic 42 41
c add Berkeley header
e
s 00001/00001/00677
d D 7.2 88/01/07 13:20:41 bostic 41 40
c getpeername typo in mtod call; bug reports 4.3BSD/sys/{101,116}
e
s 00001/00001/00677
d D 7.1 86/06/05 00:18:04 mckusick 40 39
c 4.3BSD release version
e
s 00001/00001/00677
d D 6.23 86/06/02 14:41:53 karels 39 38
c lint
e
s 00005/00000/00673
d D 6.22 86/05/19 16:40:40 karels 38 37
c implement PRU_PEERADDR
e
s 00001/00001/00672
d D 6.21 86/02/23 23:13:12 karels 37 36
c lint
e
s 00003/00005/00670
d D 6.20 86/02/20 16:04:19 karels 36 35
c remove unused sonam arg to unp_connect2
e
s 00006/00001/00669
d D 6.19 86/01/13 17:41:46 karels 35 34
c don't indirect through unp_conn if it's been cleared
e
s 00064/00053/00606
d D 6.18 85/12/19 14:59:47 karels 34 33
c clean up stream flow control, give correct name for accept;
c record socket name at bind time
e
s 00002/00005/00657
d D 6.17 85/11/30 13:08:19 karels 33 32
c don't free ioctl cmds
e
s 00001/00001/00661
d D 6.16 85/10/18 17:10:21 mckusick 32 31
c attempting to bind() an already bound UNIX domain socket returns EINVAL (kre)
e
s 00006/00003/00656
d D 6.15 85/06/17 23:06:18 karels 31 30
c reflect failure back to sender if dg receive buffer full;
c plug another leak
e
s 00007/00001/00652
d D 6.14 85/06/08 15:09:20 mckusick 30 29
c Add copyright
e
s 00002/00001/00651
d D 6.13 85/06/02 23:35:09 karels 29 28
c minor cleanups
e
s 00005/00000/00647
d D 6.12 85/05/27 20:03:59 karels 28 27
c fix race when sosend blocks by returning EPIPE if receiver is gone;
c fake up inode numbers and dev for the naive
e
s 00015/00007/00632
d D 6.11 84/12/20 14:55:07 karels 27 26
c count those mbufs!; check access on Unix-domain socket connection;
c try for async. I/O in Unix domain
e
s 00013/00013/00626
d D 6.10 84/08/29 20:28:57 bloom 26 25
c Change to includes.  no more ../h
e
s 00005/00005/00634
d D 6.9 84/08/27 11:49:38 karels 25 24
c clear i_socket before reeleasing inode; fix unp_scan (no error if no rights)
e
s 00027/00023/00612
d D 6.8 84/08/21 10:43:08 karels 24 23
c change datagram queuing to use m_act properly; type mbufs with rights;
c change protocol family number in protosw to pointer to domain (for sam)
e
s 00030/00007/00605
d D 6.7 84/08/20 16:04:29 karels 23 22
c add sostat for blksize
e
s 00001/00001/00611
d D 6.6 84/07/26 17:11:04 bloom 22 21
c Receiving out of band data shouldn't free mbuf
e
s 00011/00007/00601
d D 6.5 84/07/08 16:18:13 mckusick 21 20
c rework `namei' interface to eliminate global variables
e
s 00001/00000/00607
d D 6.4 84/05/02 13:47:05 karels 20 19
c typo in last fix; free unp_remaddr in unp_drop
e
s 00008/00002/00599
d D 6.3 84/02/15 17:09:48 karels 19 18
c need to free any queued connections when closing;
c temporarily increase recvspace by a sockaddr (otherwise can't send
c max size datagram, but no EMSGSIZE)
e
s 00001/00001/00600
d D 6.2 83/09/08 10:53:32 mckusick 18 17
c fix for passing multiple file descriptors in a message (Bill Shannon)
e
s 00000/00000/00601
d D 6.1 83/07/29 06:50:02 sam 17 16
c 4.2 distribution
e
s 00003/00000/00598
d D 1.16 83/07/25 21:53:50 sam 16 15
c getpeer
e
s 00005/00007/00593
d D 1.15 83/07/21 02:03:43 sam 15 14
c fix datagram sockets so you can send more than one
e
s 00007/00003/00593
d D 1.14 83/06/14 22:11:38 sam 14 13
c no from address for datagrams, so sbappendaddr blows up
e
s 00012/00006/00584
d D 1.13 83/06/14 20:40:51 sam 13 12
c socketpair
e
s 00003/00003/00587
d D 1.12 83/06/13 22:43:14 sam 12 11
c lint
e
s 00001/00002/00589
d D 1.11 83/06/12 19:48:30 sam 11 10
c revamp network ioctls
e
s 00229/00026/00362
d D 1.10 83/05/27 12:51:31 sam 10 9
c merge of bill's code plus lint (plus, of course, cleanup of bill's bugs)
e
s 00004/00000/00384
d D 1.9 83/04/03 00:45:40 sam 9 8
c check error return from namei; from mike@brl-vgr
e
s 00001/00001/00383
d D 1.8 83/03/23 15:43:27 sam 8 7
c not returning errors
e
s 00001/00002/00383
d D 1.7 83/01/13 18:34:19 sam 7 6
c no more opt parameter to usrreq
e
s 00007/00011/00378
d D 1.6 83/01/04 20:49:32 sam 6 5
c from reading the code -- boy is there a lot of work to be done
e
s 00001/00001/00388
d D 1.5 82/12/14 17:11:45 sam 5 4
c typed mbufs
e
s 00000/00001/00389
d D 1.4 82/11/23 14:08:04 sam 4 3
c close's on pipes make read on EOF look like an error
e
s 00109/00118/00281
d D 1.3 82/11/13 22:54:24 sam 3 2
c merge of 4.1b and 4.1c
e
s 00010/00010/00389
d D 1.2 82/11/03 00:46:46 root 2 1
c still not right
e
s 00399/00000/00000
d D 1.1 82/10/28 10:51:18 root 1 0
c date and time created 82/10/28 10:51:18 by root
e
u
U
f b 
t
T
I 1
D 30
/*	%M%	%I%	%E%	*/
E 30
I 30
/*
D 40
 * Copyright (c) 1982 Regents of the University of California.
E 40
I 40
D 51
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 40
D 42
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 51
I 51
D 67
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 67
I 67
D 92
 * Copyright (c) 1982, 1986, 1989, 1991 Regents of the University of California.
E 67
 * All rights reserved.
E 92
I 92
 * Copyright (c) 1982, 1986, 1989, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 92
E 51
E 42
I 42
D 52
 * All rights reserved.
E 52
 *
D 62
 * Redistribution and use in source and binary forms are permitted
D 47
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 47
I 47
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
D 52
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 47
E 42
 *
I 51
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
E 52
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 62
I 62
 * %sccs.include.redist.c%
E 62
 *
E 51
 *	%W% (Berkeley) %G%
 */
E 30

D 26
#include "../h/param.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/mbuf.h"
I 24
#include "../h/domain.h"
E 24
#include "../h/protosw.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
#include "../h/unpcb.h"
#include "../h/un.h"
#include "../h/inode.h"
I 3
D 21
#include "../h/nami.h"
E 21
I 10
#include "../h/file.h"
I 23
#include "../h/stat.h"
E 26
I 26
D 89
#include "param.h"
I 75
#include "systm.h"
E 75
D 53
#include "dir.h"
E 53
D 67
#include "user.h"
E 67
I 64
#include "proc.h"
#include "filedesc.h"
E 64
D 53
#include "mbuf.h"
E 53
#include "domain.h"
#include "protosw.h"
#include "socket.h"
#include "socketvar.h"
#include "unpcb.h"
#include "un.h"
I 68
#include "namei.h"
E 68
D 51
#include "inode.h"
E 51
I 51
#include "vnode.h"
D 59
#include "mount.h"
E 59
E 51
#include "file.h"
#include "stat.h"
I 53
D 59
#include "mbuf.h"	/* XXX must appear after mount.h */
E 59
I 59
#include "mbuf.h"
E 89
I 89
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/filedesc.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/unpcb.h>
#include <sys/un.h>
#include <sys/namei.h>
#include <sys/vnode.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/mbuf.h>
E 89
E 59
E 53
E 26
E 23
E 10
E 3

/*
 * Unix communications domain.
I 10
 *
 * TODO:
 *	SEQPACKET, RDM
D 14
 *	change for names in file system
E 14
I 14
 *	rethink name space problems
E 14
 *	need a proper out-of-band
E 10
 */
I 14
D 50
struct	sockaddr sun_noname = { AF_UNIX };
E 50
I 50
struct	sockaddr sun_noname = { sizeof(sun_noname), AF_UNIX };
E 50
I 28
D 34
ino_t	unp_ino;				/* fake inode numbers */
E 34
I 34
D 51
ino_t	unp_ino;			/* prototype for fake inode numbers */
E 51
I 51
D 56
ino_t	unp_vno;			/* prototype for fake vnode numbers */
E 56
I 56
ino_t	unp_ino;			/* prototype for fake inode numbers */
E 56
E 51
E 34
E 28
E 14

/*ARGSUSED*/
I 98
int
E 98
D 2
uipc_usrreq(so, req, m, addr)
E 2
I 2
D 7
uipc_usrreq(so, req, m, nam, opt)
E 7
I 7
D 10
uipc_usrreq(so, req, m, nam)
E 10
I 10
D 56
uipc_usrreq(so, req, m, nam, rights)
E 56
I 56
uipc_usrreq(so, req, m, nam, control)
E 56
E 10
E 7
E 2
	struct socket *so;
	int req;
D 2
	struct mbuf *m;
	caddr_t addr;
E 2
I 2
D 10
	struct mbuf *m, *nam;
E 10
I 10
D 56
	struct mbuf *m, *nam, *rights;
E 56
I 56
	struct mbuf *m, *nam, *control;
E 56
E 10
D 7
	struct socketopt *opt;
E 7
E 2
{
	struct unpcb *unp = sotounpcb(so);
	register struct socket *so2;
D 57
	int error = 0;
E 57
I 57
	register int error = 0;
I 68
	struct proc *p = curproc;	/* XXX */
E 68
E 57

I 33
	if (req == PRU_CONTROL)
		return (EOPNOTSUPP);
E 33
D 10
	if (unp == 0 && req != PRU_ATTACH)
		return (EINVAL);			/* XXX */
E 10
I 10
D 56
	if (req != PRU_SEND && rights && rights->m_len) {
E 56
I 56
	if (req != PRU_SEND && control && control->m_len) {
E 56
		error = EOPNOTSUPP;
		goto release;
	}
	if (unp == 0 && req != PRU_ATTACH) {
		error = EINVAL;
		goto release;
	}
E 10
	switch (req) {

	case PRU_ATTACH:
		if (unp) {
D 3
			error = EINVAL;
E 3
I 3
			error = EISCONN;
E 3
			break;
		}
D 2
		error = unp_attach(so, (struct sockaddr *)addr);
E 2
I 2
		error = unp_attach(so);
E 2
		break;

	case PRU_DETACH:
		unp_detach(unp);
		break;

I 3
	case PRU_BIND:
D 68
		error = unp_bind(unp, nam);
E 68
I 68
		error = unp_bind(unp, nam, p);
E 68
		break;

	case PRU_LISTEN:
D 51
		if (unp->unp_inode == 0)
E 51
I 51
		if (unp->unp_vnode == 0)
E 51
			error = EINVAL;
		break;

E 3
	case PRU_CONNECT:
D 2
		error = unp_connect(so, (struct sockaddr_un *)addr);
E 2
I 2
D 68
		error = unp_connect(so, nam);
E 68
I 68
		error = unp_connect(so, nam, p);
E 68
E 2
		break;

I 10
D 13
#ifdef notdef
E 13
	case PRU_CONNECT2:
D 13
		error = unp_connect2(so, (struct mbuf *)0, (struct socket *)nam);
E 13
I 13
D 36
		error = unp_connect2(so, (struct mbuf *)0,
		    (struct socket *)nam);
E 36
I 36
		error = unp_connect2(so, (struct socket *)nam);
E 36
E 13
		break;

D 13
#endif
E 13
E 10
	case PRU_DISCONNECT:
		unp_disconnect(unp);
		break;

D 3
/* BEGIN QUESTIONABLE */
	case PRU_ACCEPT: {
D 2
		struct sockaddr_un *soun = (struct sockaddr_un *)addr;
E 2
I 2
		struct sockaddr_un *soun = mtod(nam, struct sockaddr_un *);
E 2

		if (soun) {
			bzero((caddr_t)soun, sizeof (*soun));
			soun->sun_family = AF_UNIX;
			/* XXX */
		}
		}
E 3
I 3
	case PRU_ACCEPT:
D 34
		nam->m_len = unp->unp_remaddr->m_len;
		bcopy(mtod(unp->unp_remaddr, caddr_t),
		    mtod(nam, caddr_t), (unsigned)nam->m_len);
E 34
I 34
D 35
		if (unp->unp_conn->unp_addr) {
E 35
I 35
		/*
		 * Pass back name of connected socket,
		 * if it was bound and we are still connected
		 * (our peer may have closed already!).
		 */
		if (unp->unp_conn && unp->unp_conn->unp_addr) {
E 35
			nam->m_len = unp->unp_conn->unp_addr->m_len;
			bcopy(mtod(unp->unp_conn->unp_addr, caddr_t),
			    mtod(nam, caddr_t), (unsigned)nam->m_len);
		} else {
			nam->m_len = sizeof(sun_noname);
			*(mtod(nam, struct sockaddr *)) = sun_noname;
		}
E 34
E 3
		break;

	case PRU_SHUTDOWN:
		socantsendmore(so);
D 63
		unp_usrclosed(unp);
E 63
I 63
		unp_shutdown(unp);
E 63
		break;
D 3
/* END QUESTIONABLE */
E 3

	case PRU_RCVD:
		switch (so->so_type) {

		case SOCK_DGRAM:
			panic("uipc 1");
I 6
			/*NOTREACHED*/
E 6

D 6
		case SOCK_STREAM: {
E 6
I 6
		case SOCK_STREAM:
E 6
#define	rcv (&so->so_rcv)
#define snd (&so2->so_snd)
			if (unp->unp_conn == 0)
				break;
			so2 = unp->unp_conn->unp_socket;
			/*
D 34
			 * Transfer resources back to send port
E 34
I 34
			 * Adjust backpressure on sender
E 34
			 * and wakeup any waiting to write.
			 */
D 34
			snd->sb_mbmax += rcv->sb_mbmax - rcv->sb_mbcnt;
			rcv->sb_mbmax = rcv->sb_mbcnt;
			snd->sb_hiwat += rcv->sb_hiwat - rcv->sb_cc;
			rcv->sb_hiwat = rcv->sb_cc;
E 34
I 34
			snd->sb_mbmax += unp->unp_mbcnt - rcv->sb_mbcnt;
			unp->unp_mbcnt = rcv->sb_mbcnt;
			snd->sb_hiwat += unp->unp_cc - rcv->sb_cc;
			unp->unp_cc = rcv->sb_cc;
E 34
D 27
			sbwakeup(snd);
E 27
I 27
			sowwakeup(so2);
E 27
#undef snd
#undef rcv
D 6
			}
E 6
			break;

		default:
			panic("uipc 2");
		}
		break;

	case PRU_SEND:
I 34
D 56
		if (rights) {
			error = unp_internalize(rights);
E 56
I 56
D 57
		if (control) {
			error = unp_internalize(control);
E 56
			if (error)
				break;
		}
E 57
I 57
D 68
		if (control && (error = unp_internalize(control)))
E 68
I 68
		if (control && (error = unp_internalize(control, p)))
E 68
			break;
E 57
E 34
		switch (so->so_type) {

D 34
		case SOCK_DGRAM:
E 34
I 34
		case SOCK_DGRAM: {
			struct sockaddr *from;

E 34
D 2
			if (addr) {
E 2
I 2
			if (nam) {
E 2
				if (unp->unp_conn) {
					error = EISCONN;
					break;
				}
D 2
				error = unp_connect(so, addr);
E 2
I 2
D 68
				error = unp_connect(so, nam);
E 68
I 68
				error = unp_connect(so, nam, p);
E 68
E 2
				if (error)
					break;
			} else {
				if (unp->unp_conn == 0) {
					error = ENOTCONN;
					break;
				}
			}
			so2 = unp->unp_conn->unp_socket;
D 3
			if (sbspace(&so2->so_rcv) > 0)		/* XXX */
D 2
				sbappendaddr(so2, m, addr);	/* XXX */
			if (addr)
E 2
I 2
				sbappendaddr(so2, m, nam);	/* XXX */
E 3
I 3
D 34
			/* BEGIN XXX */
D 10
			if (sbspace(&so2->so_rcv) > 0)
E 10
I 10
			if (rights) {
				error = unp_internalize(rights);
				if (error)
					break;
			}
			if (sbspace(&so2->so_rcv) > 0) {
I 14
				/*
				 * There's no record of source socket's
				 * name, so send null name for the moment.
				 */
E 14
E 10
D 27
				(void) sbappendaddr(&so2->so_rcv,
D 10
					mtod(nam, struct sockaddr *), m);
E 10
I 10
D 14
				    mtod(nam, struct sockaddr *), m,
				    rights);
E 14
I 14
				    &sun_noname, m, rights);
E 14
				sbwakeup(&so2->so_rcv);
				m = 0;
E 27
I 27
				if (sbappendaddr(&so2->so_rcv,
				    &sun_noname, m, rights)) {
					sorwakeup(so2);
					m = 0;
D 31
				}
E 31
I 31
				} else
					error = ENOBUFS;
E 31
E 27
			}
E 10
			/* END XXX */
E 34
I 34
			if (unp->unp_addr)
				from = mtod(unp->unp_addr, struct sockaddr *);
			else
				from = &sun_noname;
D 57
			if (sbspace(&so2->so_rcv) > 0 &&
D 56
			    sbappendaddr(&so2->so_rcv, from, m, rights)) {
E 56
I 56
			    sbappendaddr(&so2->so_rcv, from, m, control)) {
E 57
I 57
			if (sbappendaddr(&so2->so_rcv, from, m, control)) {
E 57
E 56
				sorwakeup(so2);
				m = 0;
I 57
				control = 0;
E 57
			} else
				error = ENOBUFS;
E 34
E 3
			if (nam)
E 2
D 3
				unp_disconnect(so);
E 3
I 3
				unp_disconnect(unp);
E 3
			break;
I 34
		}
E 34

		case SOCK_STREAM:
#define	rcv (&so2->so_rcv)
#define	snd (&so->so_snd)
I 10
D 34
			if (rights && rights->m_len) {
				error = EOPNOTSUPP;
				break;
			}
E 34
I 28
D 31
			if (so->so_state & SS_CANTSENDMORE)
				return (EPIPE);
E 31
I 31
			if (so->so_state & SS_CANTSENDMORE) {
				error = EPIPE;
				break;
			}
E 31
E 28
E 10
			if (unp->unp_conn == 0)
				panic("uipc 3");
			so2 = unp->unp_conn->unp_socket;
			/*
D 34
			 * Send to paired receive port, and then
			 * give it enough resources to hold what it already has.
E 34
I 34
			 * Send to paired receive port, and then reduce
			 * send buffer hiwater marks to maintain backpressure.
E 34
			 * Wake up readers.
			 */
D 34
			sbappend(rcv, m);
			snd->sb_mbmax -= rcv->sb_mbcnt - rcv->sb_mbmax;
			rcv->sb_mbmax = rcv->sb_mbcnt;
			snd->sb_hiwat -= rcv->sb_cc - rcv->sb_hiwat;
			rcv->sb_hiwat = rcv->sb_cc;
E 34
I 34
D 56
			if (rights)
D 37
				sbappendrights(rcv, m, rights);
E 37
I 37
				(void)sbappendrights(rcv, m, rights);
E 56
I 56
D 57
			if (control)
				(void)sbappendrights(rcv, m, control);
E 56
E 37
			else
E 57
I 57
			if (control) {
D 63
				(void)sbappendcontrol(rcv, m, control);
				control = 0;
E 63
I 63
				if (sbappendcontrol(rcv, m, control))
					control = 0;
E 63
			} else
E 57
				sbappend(rcv, m);
			snd->sb_mbmax -=
			    rcv->sb_mbcnt - unp->unp_conn->unp_mbcnt;
			unp->unp_conn->unp_mbcnt = rcv->sb_mbcnt;
			snd->sb_hiwat -= rcv->sb_cc - unp->unp_conn->unp_cc;
			unp->unp_conn->unp_cc = rcv->sb_cc;
E 34
D 27
			sbwakeup(rcv);
E 27
I 27
			sorwakeup(so2);
			m = 0;
E 27
#undef snd
#undef rcv
			break;

		default:
			panic("uipc 4");
		}
I 10
D 27
		m = 0;
E 27
E 10
		break;

	case PRU_ABORT:
		unp_drop(unp, ECONNABORTED);
		break;

D 33
/* SOME AS YET UNIMPLEMENTED HOOKS */
	case PRU_CONTROL:
D 11
		error = EOPNOTSUPP;
		break;
E 11
I 11
		return (EOPNOTSUPP);
E 11

D 23
	case PRU_SENSE:
		error = EOPNOTSUPP;
		break;
E 23
/* END UNIMPLEMENTED HOOKS */
E 33
I 23
	case PRU_SENSE:
		((struct stat *) m)->st_blksize = so->so_snd.sb_hiwat;
		if (so->so_type == SOCK_STREAM && unp->unp_conn != 0) {
			so2 = unp->unp_conn->unp_socket;
			((struct stat *) m)->st_blksize += so2->so_rcv.sb_cc;
		}
I 28
		((struct stat *) m)->st_dev = NODEV;
D 34
		((struct stat *) m)->st_ino = unp_ino++;
E 34
I 34
D 51
		if (unp->unp_ino == 0)
			unp->unp_ino = unp_ino++;
		((struct stat *) m)->st_ino = unp->unp_ino;
E 51
I 51
D 56
		if (unp->unp_vno == 0)
			unp->unp_vno = unp_vno++;
		((struct stat *) m)->st_ino = unp->unp_vno;
E 56
I 56
		if (unp->unp_ino == 0)
			unp->unp_ino = unp_ino++;
		((struct stat *) m)->st_ino = unp->unp_ino;
E 56
E 51
E 34
E 28
		return (0);
E 23

	case PRU_RCVOOB:
D 22
		break;
E 22
I 22
		return (EOPNOTSUPP);
E 22

	case PRU_SENDOOB:
I 27
		error = EOPNOTSUPP;
E 27
		break;

	case PRU_SOCKADDR:
I 45
		if (unp->unp_addr) {
			nam->m_len = unp->unp_addr->m_len;
			bcopy(mtod(unp->unp_addr, caddr_t),
			    mtod(nam, caddr_t), (unsigned)nam->m_len);
		} else
			nam->m_len = 0;
E 45
		break;

I 16
	case PRU_PEERADDR:
I 38
		if (unp->unp_conn && unp->unp_conn->unp_addr) {
			nam->m_len = unp->unp_conn->unp_addr->m_len;
			bcopy(mtod(unp->unp_conn->unp_addr, caddr_t),
D 39
			    mtod(m, caddr_t), m->m_len);
E 39
I 39
D 41
			    mtod(m, caddr_t), (unsigned)m->m_len);
E 41
I 41
			    mtod(nam, caddr_t), (unsigned)nam->m_len);
E 41
E 39
D 45
		}
E 45
I 45
		} else
			nam->m_len = 0;
E 45
E 38
		break;

E 16
	case PRU_SLOWTIMO:
		break;

	default:
		panic("piusrreq");
	}
I 10
release:
I 57
	if (control)
		m_freem(control);
E 57
	if (m)
		m_freem(m);
E 10
D 8
	return (0);
E 8
I 8
	return (error);
E 8
}

I 10
D 23
/* SHOULD BE PIPSIZ and 0 */
E 10
int	unp_sendspace = 1024*2;
D 19
int	unp_recvspace = 1024*2;
E 19
I 19
int	unp_recvspace = 1024*2 + sizeof(struct sockaddr);
E 23
I 23
/*
D 34
 * We assign all buffering for stream sockets to the source,
 * as that is where the flow control is implemented.
E 34
I 34
 * Both send and receive buffers are allocated PIPSIZ bytes of buffering
 * for stream sockets, although the total for sender and receiver is
 * actually only PIPSIZ.
E 34
 * Datagram sockets really use the sendspace as the maximum datagram size,
 * and don't really want to reserve the sendspace.  Their recvspace should
 * be large enough for at least one max-size datagram plus address.
 */
#define	PIPSIZ	4096
D 46
int	unpst_sendspace = PIPSIZ;
D 34
int	unpst_recvspace = 0;
E 34
I 34
int	unpst_recvspace = PIPSIZ;
E 34
int	unpdg_sendspace = 2*1024;	/* really max datagram size */
int	unpdg_recvspace = 4*1024;
E 46
I 46
u_long	unpst_sendspace = PIPSIZ;
u_long	unpst_recvspace = PIPSIZ;
u_long	unpdg_sendspace = 2*1024;	/* really max datagram size */
u_long	unpdg_recvspace = 4*1024;
E 46
E 23
E 19

I 34
int	unp_rights;			/* file descriptors in flight */

I 98
int
E 98
E 34
D 3
unp_attach(so, soun)
E 3
I 3
unp_attach(so)
E 3
	struct socket *so;
D 3
	struct sockaddr_un *soun;
E 3
{
I 3
	register struct mbuf *m;
E 3
	register struct unpcb *unp;
D 3
	struct mbuf *m;
E 3
	int error;
	
D 23
	error = soreserve(so, unp_sendspace, unp_recvspace);
E 23
I 23
D 46
	switch (so->so_type) {
E 46
I 46
	if (so->so_snd.sb_hiwat == 0 || so->so_rcv.sb_hiwat == 0) {
		switch (so->so_type) {
E 46

D 46
	case SOCK_STREAM:
		error = soreserve(so, unpst_sendspace, unpst_recvspace);
		break;
E 46
I 46
		case SOCK_STREAM:
			error = soreserve(so, unpst_sendspace, unpst_recvspace);
			break;
E 46

D 46
	case SOCK_DGRAM:
		error = soreserve(so, unpdg_sendspace, unpdg_recvspace);
		break;
E 46
I 46
		case SOCK_DGRAM:
			error = soreserve(so, unpdg_sendspace, unpdg_recvspace);
			break;
I 74

		default:
			panic("unp_attach");
E 74
		}
		if (error)
			return (error);
E 46
	}
E 23
D 46
	if (error)
D 6
		goto bad;
E 6
I 6
		return (error);
E 46
E 6
D 5
	m = m_getclr(M_DONTWAIT);
E 5
I 5
	m = m_getclr(M_DONTWAIT, MT_PCB);
E 5
D 6
	if (m == 0) {
		error = ENOBUFS;
		goto bad;
	}
E 6
I 6
	if (m == NULL)
		return (ENOBUFS);
E 6
	unp = mtod(m, struct unpcb *);
	so->so_pcb = (caddr_t)unp;
	unp->unp_socket = so;
D 3
	if (soun) {
		error = unp_bind(unp, soun);
		if (error) {
			unp_detach(unp);
			goto bad;
		}
	}
E 3
	return (0);
D 6
bad:
	return (error);
E 6
}

I 98
void
E 98
D 3
unp_disconnect(unp)
	struct unpcb *unp;
{
	register struct unpcb *unp2 = unp->unp_conn;

	if (unp2 == 0)
		return;
	unp->unp_conn = 0;
	soisdisconnected(unp->unp_socket);
	switch (unp->unp_socket->so_type) {

	case SOCK_DGRAM:
		if (unp2->unp_refs == unp)
			unp2->unp_refs = unp->unp_nextref;
		else {
			unp2 = unp2->unp_refs;
			for (;;) {
				if (unp2 == 0)
					panic("unp_disconnect");
				if (unp2->unp_nextref == unp)
					break;
				unp2 = unp2->unp_nextref;
			}
			unp2->unp_nextref = unp->unp_nextref;
		}
		unp->unp_nextref = 0;
		break;

	case SOCK_STREAM:
		unp2->unp_conn = 0;
		soisdisconnected(unp2->unp_socket);
		unp_drop(unp2, ECONNRESET);
		break;
	}
}

unp_abort(unp)
	struct unpcb *unp;
{

	unp_detach(unp);
}

E 3
unp_detach(unp)
D 3
	struct unpcb *unp;
E 3
I 3
	register struct unpcb *unp;
E 3
{
	
D 51
	if (unp->unp_inode) {
I 25
		unp->unp_inode->i_socket = 0;
E 25
		irele(unp->unp_inode);
		unp->unp_inode = 0;
E 51
I 51
	if (unp->unp_vnode) {
		unp->unp_vnode->v_socket = 0;
		vrele(unp->unp_vnode);
		unp->unp_vnode = 0;
E 51
	}
	if (unp->unp_conn)
		unp_disconnect(unp);
	while (unp->unp_refs)
		unp_drop(unp->unp_refs, ECONNRESET);
	soisdisconnected(unp->unp_socket);
	unp->unp_socket->so_pcb = 0;
D 3
	m_free(dtom(unp));
E 3
I 3
D 34
	m_freem(unp->unp_remaddr);
E 34
I 34
	m_freem(unp->unp_addr);
E 34
	(void) m_free(dtom(unp));
I 34
D 91
	if (unp_rights)
E 91
I 91
	if (unp_rights) {
		/*
		 * Normally the receive buffer is flushed later,
		 * in sofree, but if our receive buffer holds references
		 * to descriptors that are now garbage, we will dispose
		 * of those descriptor references after the garbage collector
		 * gets them (resulting in a "panic: closef: count < 0").
		 */
		sorflush(unp->unp_socket);
E 91
		unp_gc();
I 91
	}
E 91
E 34
E 3
}

I 98
int
E 98
D 3
unp_usrclosed(unp)
E 3
I 3
D 68
unp_bind(unp, nam)
E 68
I 68
unp_bind(unp, nam, p)
E 68
E 3
	struct unpcb *unp;
I 3
	struct mbuf *nam;
I 68
	struct proc *p;
E 68
E 3
{
I 85
D 86
	USES_VOP_ABORTOP;
	USES_VOP_CREATE;
	USES_VOP_UNLOCK;
E 86
E 85
D 3
	register struct socket *so = unp->unp_socket;

#ifdef sometimes /* ??? */
	soisdisconnected(unp->unp_socket);
#endif
}

unp_drop(unp, errno)
	struct unpcb *unp;
	int errno;
{

	unp->unp_socket->so_error = errno;
	unp_disconnect(unp);
}

unp_drain()
{

}

unp_bind(unp, soun)
	struct unpcb *unp;
	struct sockaddr_un *soun;
{
E 3
I 3
	struct sockaddr_un *soun = mtod(nam, struct sockaddr_un *);
E 3
D 51
	register struct inode *ip;
E 51
I 51
	register struct vnode *vp;
E 51
D 3
	int error;
E 3
D 21
	extern schar();
E 21
I 21
D 65
	register struct nameidata *ndp = &u.u_nd;
E 65
I 65
D 73
	register struct nameidata *ndp;
E 73
E 65
I 51
	struct vattr vattr;
E 51
E 21
I 3
	int error;
I 65
	struct nameidata nd;
E 65
E 3

I 65
D 73
	ndp = &nd;
E 65
D 21
	u.u_dirp = soun->sun_path;
E 21
I 21
	ndp->ni_dirp = soun->sun_path;
E 73
I 73
	NDINIT(&nd, CREATE, FOLLOW | LOCKPARENT, UIO_SYSSPACE,
D 98
		soun->sun_path, p);
E 98
I 98
	    soun->sun_path, p);
E 98
E 73
E 21
D 10
	soun->sun_path[sizeof(soun->sun_path)-1] = 0;
E 10
I 10
D 32
	if (nam->m_len == MLEN)
E 32
I 32
D 48
D 51
	if (unp->unp_inode != NULL || nam->m_len == MLEN)
E 51
I 51
D 52
	if (unp->unp_vnode != NULL || nam->m_len == MLEN)
E 51
E 48
I 48
	if (unp->unp_inode != NULL)
E 52
I 52
	if (unp->unp_vnode != NULL)
E 52
E 48
E 32
		return (EINVAL);
D 48
	*(mtod(nam, caddr_t) + nam->m_len) = 0;
E 48
I 48
	if (nam->m_len == MLEN) {
		if (*(mtod(nam, caddr_t) + nam->m_len - 1) != 0)
			return (EINVAL);
	} else
		*(mtod(nam, caddr_t) + nam->m_len) = 0;
E 48
/* SHOULD BE ABLE TO ADOPT EXISTING AND wakeup() ALA FIFO's */
E 10
D 3
	ip = namei(schar, 1, 1);
E 3
I 3
D 21
	ip = namei(schar, CREATE, 1);
E 21
I 21
D 51
	ndp->ni_nameiop = CREATE | FOLLOW;
E 51
I 51
D 73
	ndp->ni_nameiop = CREATE | FOLLOW | LOCKPARENT;
E 51
	ndp->ni_segflg = UIO_SYSSPACE;
D 51
	ip = namei(ndp);
E 21
E 3
	if (ip) {
		iput(ip);
E 51
I 51
D 65
	if (error = namei(ndp))
E 65
I 65
D 68
	if (error = namei(ndp, curproc)) 		/* XXX */
E 68
I 68
	if (error = namei(ndp, p))
E 73
I 73
	if (error = namei(&nd))
E 73
E 68
E 65
		return (error);
D 73
	vp = ndp->ni_vp;
E 73
I 73
	vp = nd.ni_vp;
E 73
	if (vp != NULL) {
D 53
		vop_abortop(ndp);
E 53
I 53
D 72
		VOP_ABORTOP(ndp);
E 72
I 72
D 73
		VOP_ABORTOP(ndp->ni_dvp, &ndp->ni_cnd);
E 72
I 60
D 61
		vput(ndp->ni_dvp);
E 61
I 61
		if (ndp->ni_dvp == vp)
			vrele(ndp->ni_dvp);
E 73
I 73
		VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
		if (nd.ni_dvp == vp)
			vrele(nd.ni_dvp);
E 73
		else
D 73
			vput(ndp->ni_dvp);
E 73
I 73
			vput(nd.ni_dvp);
E 73
E 61
		vrele(vp);
E 60
E 53
E 51
D 6
		return (EEXIST);
E 6
I 6
		return (EADDRINUSE);
E 6
	}
I 9
D 51
	if (error = u.u_error) {
		u.u_error = 0;			/* XXX */
E 51
I 51
D 58
	vattr_null(&vattr);
E 58
I 58
	VATTR_NULL(&vattr);
E 58
	vattr.va_type = VSOCK;
D 93
	vattr.va_mode = 0777;
E 93
I 93
	vattr.va_mode = ACCESSPERMS;
E 93
I 71
D 73
	LEASE_CHECK(ndp->ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 71
D 53
	if (error = vop_create(ndp, &vattr))
E 53
I 53
D 68
	if (error = VOP_CREATE(ndp, &vattr))
E 68
I 68
D 72
	if (error = VOP_CREATE(ndp, &vattr, p))
E 72
I 72
	if (error = VOP_CREATE(ndp->ni_dvp, &ndp->ni_vp, &ndp->ni_cnd, &vattr))
E 73
I 73
D 95
	LEASE_CHECK(nd.ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 95
I 95
	VOP_LEASE(nd.ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 95
	if (error = VOP_CREATE(nd.ni_dvp, &nd.ni_vp, &nd.ni_cnd, &vattr))
E 73
E 72
E 68
E 53
E 51
		return (error);
D 51
	}
E 9
D 21
	ip = maknode(IFSOCK | 0777);
E 21
I 21
	ip = maknode(IFSOCK | 0777, ndp);
E 21
	if (ip == NULL) {
		error = u.u_error;		/* XXX */
		u.u_error = 0;			/* XXX */
		return (error);
	}
	ip->i_socket = unp->unp_socket;
	unp->unp_inode = ip;
E 51
I 51
D 73
	vp = ndp->ni_vp;
E 73
I 73
	vp = nd.ni_vp;
E 73
	vp->v_socket = unp->unp_socket;
	unp->unp_vnode = vp;
E 51
I 34
	unp->unp_addr = m_copy(nam, 0, (int)M_COPYALL);
E 34
D 51
	iunlock(ip);			/* but keep reference */
E 51
I 51
D 53
	vop_unlock(vp);
E 53
I 53
D 100
	VOP_UNLOCK(vp);
E 100
I 100
	VOP_UNLOCK(vp, 0, p);
E 100
E 53
E 51
	return (0);
}

I 98
int
E 98
D 3
unp_connect(so, soun)
E 3
I 3
D 68
unp_connect(so, nam)
E 68
I 68
unp_connect(so, nam, p)
E 68
E 3
	struct socket *so;
D 3
	struct sockaddr_un *soun;
E 3
I 3
	struct mbuf *nam;
I 68
	struct proc *p;
E 68
E 3
{
I 85
D 86
	USES_VOP_ACCESS;
E 86
E 85
D 3
	struct inode *ip;
E 3
I 3
	register struct sockaddr_un *soun = mtod(nam, struct sockaddr_un *);
D 10
	struct unpcb *unp = sotounpcb(so);
E 10
D 51
	register struct inode *ip;
E 51
I 51
	register struct vnode *vp;
E 51
E 3
D 45
	int error;
I 3
D 10
	struct socket *so2;
	struct unpcb *unp2;
E 10
I 10
	register struct socket *so2;
E 45
I 45
	register struct socket *so2, *so3;
E 45
I 21
D 65
	register struct nameidata *ndp = &u.u_nd;
E 65
I 65
D 73
	register struct nameidata *ndp;
E 73
E 65
I 45
	struct unpcb *unp2, *unp3;
	int error;
I 65
	struct nameidata nd;
E 65
E 45
E 21
E 10
E 3

I 65
D 73
	ndp = &nd;
E 65
D 21
	u.u_dirp = soun->sun_path;
E 21
I 21
	ndp->ni_dirp = soun->sun_path;
E 73
I 73
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_SYSSPACE, soun->sun_path, p);
E 73
E 21
D 10
	soun->sun_path[sizeof(soun->sun_path)-1] = 0;
E 10
I 10
D 48
	if (nam->m_len + (nam->m_off - MMINOFF) == MLEN)
		return (EMSGSIZE);
	*(mtod(nam, caddr_t) + nam->m_len) = 0;
E 48
I 48
	if (nam->m_data + nam->m_len == &nam->m_dat[MLEN]) {	/* XXX */
		if (*(mtod(nam, caddr_t) + nam->m_len - 1) != 0)
			return (EMSGSIZE);
	} else
		*(mtod(nam, caddr_t) + nam->m_len) = 0;
E 48
E 10
D 3
	ip = namei(schar, 0, 1);
E 3
I 3
D 21
	ip = namei(schar, LOOKUP, 1);
E 21
I 21
D 53
	ndp->ni_nameiop = LOOKUP | FOLLOW;
E 53
I 53
D 73
	ndp->ni_nameiop = LOOKUP | FOLLOW | LOCKLEAF;
E 53
	ndp->ni_segflg = UIO_SYSSPACE;
D 51
	ip = namei(ndp);
E 21
E 3
	if (ip == 0) {
		error = u.u_error;
		u.u_error = 0;
D 6
		return (ENOENT);
E 6
I 6
		return (error);		/* XXX */
E 6
	}
I 27
	if (access(ip, IWRITE)) {
		error = u.u_error;
		u.u_error = 0; 		/* XXX */
E 51
I 51
D 65
	if (error = namei(ndp))
E 65
I 65
D 68
	if (error = namei(ndp, curproc))		/* XXX */
E 68
I 68
	if (error = namei(ndp, p))
E 73
I 73
	if (error = namei(&nd))
E 73
E 68
E 65
		return (error);
D 73
	vp = ndp->ni_vp;
E 73
I 73
	vp = nd.ni_vp;
E 73
D 53
	if (error = vn_access(vp, VWRITE, u.u_cred))
E 53
I 53
D 54
	if (error = vn_access(vp, VWRITE, ndp->ni_cred))
E 53
E 51
		goto bad;
E 54
D 51
	}
E 27
D 3
	error = unp_connectip(so, ip);
	return (error);
}

unp_connectip(so, ip)
	struct socket *so;
	struct inode *ip;
{
	struct unpcb *unp = sotounpcb(so);
	struct socket *so2, *so3;
	int error;
	struct unpcb *unp2;

E 3
	if ((ip->i_mode&IFMT) != IFSOCK) {
E 51
I 51
	if (vp->v_type != VSOCK) {
E 51
		error = ENOTSOCK;
		goto bad;
	}
I 54
D 65
	if (error = VOP_ACCESS(vp, VWRITE, ndp->ni_cred))
E 65
I 65
D 68
	if (error = VOP_ACCESS(vp, VWRITE, curproc->p_ucred))
E 68
I 68
	if (error = VOP_ACCESS(vp, VWRITE, p->p_ucred, p))
E 68
E 65
		goto bad;
E 54
D 51
	so2 = ip->i_socket;
E 51
I 51
	so2 = vp->v_socket;
E 51
	if (so2 == 0) {
		error = ECONNREFUSED;
		goto bad;
	}
I 13
	if (so->so_type != so2->so_type) {
		error = EPROTOTYPE;
		goto bad;
	}
D 45
	if (so->so_proto->pr_flags & PR_CONNREQUIRED &&
	    ((so2->so_options&SO_ACCEPTCONN) == 0 ||
	     (so2 = sonewconn(so2)) == 0)) {
		error = ECONNREFUSED;
		goto bad;
E 45
I 45
	if (so->so_proto->pr_flags & PR_CONNREQUIRED) {
		if ((so2->so_options & SO_ACCEPTCONN) == 0 ||
D 56
		    (so3 = sonewconn(so2)) == 0) {
E 56
I 56
		    (so3 = sonewconn(so2, 0)) == 0) {
E 56
			error = ECONNREFUSED;
			goto bad;
		}
		unp2 = sotounpcb(so2);
		unp3 = sotounpcb(so3);
		if (unp2->unp_addr)
D 50
			unp3->unp_addr = m_copy(unp2->unp_addr, 0, M_COPYALL);
E 50
I 50
			unp3->unp_addr =
				  m_copy(unp2->unp_addr, 0, (int)M_COPYALL);
E 50
		so2 = so3;
E 45
	}
E 13
D 10
	if (so2->so_type != so->so_type) {
		error = EPROTOTYPE;
		goto bad;
	}
E 10
I 10
D 36
	error = unp_connect2(so, nam, so2);
E 36
I 36
	error = unp_connect2(so, so2);
E 36
bad:
D 51
	iput(ip);
E 51
I 51
D 53
	vrele(vp);
E 53
I 53
	vput(vp);
E 53
E 51
	return (error);
}

I 98
int
E 98
D 36
unp_connect2(so, sonam, so2)
E 36
I 36
unp_connect2(so, so2)
E 36
	register struct socket *so;
D 36
	struct mbuf *sonam;
E 36
	register struct socket *so2;
{
	register struct unpcb *unp = sotounpcb(so);
	register struct unpcb *unp2;

	if (so2->so_type != so->so_type)
		return (EPROTOTYPE);
I 15
	unp2 = sotounpcb(so2);
	unp->unp_conn = unp2;
E 15
E 10
	switch (so->so_type) {

	case SOCK_DGRAM:
D 10
		unp->unp_conn = sotounpcb(so2);
E 10
D 15
		unp2 = sotounpcb(so2);
I 10
		unp->unp_conn = unp2;
E 15
E 10
		unp->unp_nextref = unp2->unp_refs;
		unp2->unp_refs = unp;
I 27
		soisconnected(so);
E 27
		break;

	case SOCK_STREAM:
D 13
		if ((so2->so_options&SO_ACCEPTCONN) == 0 ||
D 3
		    (so3 = sonewconn(so2)) == 0) {
E 3
I 3
D 10
		    (so2 = sonewconn(so2)) == 0) {
E 3
			error = ECONNREFUSED;
			goto bad;
		}
E 10
I 10
		    (so2 = sonewconn(so2)) == 0)
			return (ECONNREFUSED);
E 13
E 10
D 3
		unp->unp_conn = sotounpcb(so3);
E 3
I 3
D 15
		unp2 = sotounpcb(so2);
		unp->unp_conn = unp2;
E 15
		unp2->unp_conn = unp;
D 10
		unp2->unp_remaddr = m_copy(nam, 0, (int)M_COPYALL);
E 10
I 10
D 34
		if (sonam)
			unp2->unp_remaddr = m_copy(sonam, 0, (int)M_COPYALL);
E 34
I 15
D 56
		soisconnected(so2);
E 56
		soisconnected(so);
I 56
		soisconnected(so2);
E 56
E 15
E 10
E 3
		break;

	default:
D 10
		panic("uipc connip");
E 10
I 10
		panic("unp_connect2");
E 10
	}
D 3
	soisconnected(unp->unp_conn->unp_socket);
E 3
I 3
D 15
	soisconnected(so2);
E 3
	soisconnected(so);
E 15
D 10
	iput(ip);
E 10
	return (0);
D 10
bad:
	iput(ip);
	return (error);
E 10
I 3
}

I 97
void
E 97
unp_disconnect(unp)
	struct unpcb *unp;
{
	register struct unpcb *unp2 = unp->unp_conn;

	if (unp2 == 0)
		return;
	unp->unp_conn = 0;
D 15
	soisdisconnected(unp->unp_socket);
E 15
	switch (unp->unp_socket->so_type) {

	case SOCK_DGRAM:
		if (unp2->unp_refs == unp)
			unp2->unp_refs = unp->unp_nextref;
		else {
			unp2 = unp2->unp_refs;
			for (;;) {
				if (unp2 == 0)
					panic("unp_disconnect");
				if (unp2->unp_nextref == unp)
					break;
				unp2 = unp2->unp_nextref;
			}
			unp2->unp_nextref = unp->unp_nextref;
		}
		unp->unp_nextref = 0;
I 29
		unp->unp_socket->so_state &= ~SS_ISCONNECTED;
E 29
		break;

	case SOCK_STREAM:
I 15
		soisdisconnected(unp->unp_socket);
E 15
		unp2->unp_conn = 0;
		soisdisconnected(unp2->unp_socket);
D 4
		unp_drop(unp2, ECONNRESET);
E 4
		break;
	}
}

I 10
#ifdef notdef
I 98
void
E 98
E 10
unp_abort(unp)
	struct unpcb *unp;
{

	unp_detach(unp);
}
I 10
#endif
E 10

I 97
void
E 97
D 63
/*ARGSUSED*/
unp_usrclosed(unp)
E 63
I 63
unp_shutdown(unp)
E 63
	struct unpcb *unp;
{
I 63
	struct socket *so;
E 63

I 63
	if (unp->unp_socket->so_type == SOCK_STREAM && unp->unp_conn &&
	    (so = unp->unp_conn->unp_socket))
		socantrcvmore(so);
E 63
}

I 97
void
E 97
unp_drop(unp, errno)
	struct unpcb *unp;
	int errno;
{
I 19
	struct socket *so = unp->unp_socket;
E 19

D 19
	unp->unp_socket->so_error = errno;
E 19
I 19
	so->so_error = errno;
E 19
	unp_disconnect(unp);
I 19
	if (so->so_head) {
		so->so_pcb = (caddr_t) 0;
I 20
D 34
		m_freem(unp->unp_remaddr);
E 34
I 34
		m_freem(unp->unp_addr);
E 34
E 20
		(void) m_free(dtom(unp));
		sofree(so);
	}
E 19
}

I 10
#ifdef notdef
E 10
unp_drain()
{

I 10
}
#endif

I 98
int
E 98
unp_externalize(rights)
	struct mbuf *rights;
{
I 64
D 65
	struct filedesc *fdp = u.u_procp->p_fd;		/* XXX */
E 65
I 65
	struct proc *p = curproc;		/* XXX */
E 65
E 64
D 56
	int newfds = rights->m_len / sizeof (int);
E 56
	register int i;
D 56
	register struct file **rp = mtod(rights, struct file **);
E 56
I 56
	register struct cmsghdr *cm = mtod(rights, struct cmsghdr *);
	register struct file **rp = (struct file **)(cm + 1);
E 56
	register struct file *fp;
I 56
	int newfds = (cm->cmsg_len - sizeof(*cm)) / sizeof (int);
E 56
	int f;

D 64
	if (newfds > ufavail()) {
E 64
I 64
D 65
	if (newfds > ufavail(fdp)) {
E 65
I 65
D 87
	if (fdavail(p, newfds)) {
E 87
I 87
	if (!fdavail(p, newfds)) {
E 87
E 65
E 64
		for (i = 0; i < newfds; i++) {
			fp = *rp;
			unp_discard(fp);
			*rp++ = 0;
		}
		return (EMSGSIZE);
	}
	for (i = 0; i < newfds; i++) {
D 51
		f = ufalloc(0);
		if (f < 0)
E 51
I 51
D 64
		if (ufalloc(0, &f))
E 64
I 64
D 65
		if (ufalloc(fdp, 0, &f))
E 65
I 65
		if (fdalloc(p, 0, &f))
E 65
E 64
E 51
			panic("unp_externalize");
		fp = *rp;
D 64
		u.u_ofile[f] = fp;
E 64
I 64
D 65
		OFILE(fdp, f) = fp;
E 65
I 65
D 67
		OFILE(p->p_fd, f) = fp;
E 67
I 67
		p->p_fd->fd_ofiles[f] = fp;
E 67
E 65
E 64
		fp->f_msgcount--;
I 34
		unp_rights--;
E 34
D 18
		*(int *)rp = f;
E 18
I 18
		*(int *)rp++ = f;
E 18
	}
	return (0);
}

I 98
int
E 98
D 57
unp_internalize(rights)
	struct mbuf *rights;
E 57
I 57
D 68
unp_internalize(control)
E 68
I 68
unp_internalize(control, p)
E 68
	struct mbuf *control;
I 68
	struct proc *p;
E 68
E 57
{
I 64
D 65
	struct filedesc *fdp = u.u_procp->p_fd;		/* XXX */
E 65
I 65
D 68
	struct filedesc *fdp = curproc->p_fd;		/* XXX */
E 68
I 68
	struct filedesc *fdp = p->p_fd;
E 68
E 65
E 64
I 57
	register struct cmsghdr *cm = mtod(control, struct cmsghdr *);
E 57
	register struct file **rp;
D 57
	int oldfds = rights->m_len / sizeof (int);
D 53
	register int i;
E 53
I 53
	register int i, fd;
E 57
E 53
	register struct file *fp;
I 56
D 57
	register struct cmsghdr *cm = mtod(rights, struct cmsghdr *);
E 57
I 57
	register int i, fd;
	int oldfds;
E 57
E 56

D 56
	rp = mtod(rights, struct file **);
E 56
I 56
D 57
	if (cm->cmsg_type != SCM_RIGHTS || cm->cmsg_level != SOL_SOCKET)
E 57
I 57
	if (cm->cmsg_type != SCM_RIGHTS || cm->cmsg_level != SOL_SOCKET ||
	    cm->cmsg_len != control->m_len)
E 57
		return (EINVAL);
	oldfds = (cm->cmsg_len - sizeof (*cm)) / sizeof (int);
D 57
	MCHTYPE(rights, MT_RIGHTS);
E 57
	rp = (struct file **)(cm + 1);
E 56
D 12
	for (i = 0; i < oldfds; i++) {
E 12
I 12
D 53
	for (i = 0; i < oldfds; i++)
E 12
		if (getf(*(int *)rp++) == 0)
E 53
I 53
	for (i = 0; i < oldfds; i++) {
		fd = *(int *)rp++;
D 64
		if ((unsigned)fd >= NOFILE || u.u_ofile[fd] == NULL)
E 64
I 64
D 65
		if ((unsigned)fd >= fdp->fd_maxfiles || OFILE(fdp, fd) == NULL)
E 65
I 65
D 67
		if ((unsigned)fd >= fdp->fd_nfiles || OFILE(fdp, fd) == NULL)
E 67
I 67
		if ((unsigned)fd >= fdp->fd_nfiles ||
		    fdp->fd_ofiles[fd] == NULL)
E 67
E 65
E 64
E 53
			return (EBADF);
I 53
	}
E 53
D 56
	rp = mtod(rights, struct file **);
E 56
I 56
	rp = (struct file **)(cm + 1);
E 56
D 12
	for (i = 0; i < oldfds; i++)
E 12
I 12
	for (i = 0; i < oldfds; i++) {
E 12
D 53
		fp = getf(*(int *)rp);
E 53
I 53
D 64
		fp = u.u_ofile[*(int *)rp];
E 64
I 64
D 67
		fp = OFILE(fdp, *(int *)rp);
E 67
I 67
		fp = fdp->fd_ofiles[*(int *)rp];
E 67
E 64
E 53
		*rp++ = fp;
		fp->f_count++;
		fp->f_msgcount++;
I 34
		unp_rights++;
E 34
	}
	return (0);
}

int	unp_defer, unp_gcing;
D 97
int	unp_mark();
E 97
I 24
extern	struct domain unixdomain;
E 24

I 97
void
E 97
unp_gc()
{
D 76
	register struct file *fp;
E 76
I 76
	register struct file *fp, *nextfp;
E 76
	register struct socket *so;
I 88
	struct file **extra_ref, **fpp;
	int nunref, i;
E 88

	if (unp_gcing)
		return;
	unp_gcing = 1;
D 94
restart:
E 94
	unp_defer = 0;
D 69
	for (fp = file; fp < fileNFILE; fp++)
E 69
I 69
D 96
	for (fp = filehead; fp; fp = fp->f_filef)
E 96
I 96
	for (fp = filehead.lh_first; fp != 0; fp = fp->f_list.le_next)
E 96
E 69
		fp->f_flag &= ~(FMARK|FDEFER);
	do {
D 69
		for (fp = file; fp < fileNFILE; fp++) {
E 69
I 69
D 96
		for (fp = filehead; fp; fp = fp->f_filef) {
E 96
I 96
		for (fp = filehead.lh_first; fp != 0; fp = fp->f_list.le_next) {
E 96
E 69
			if (fp->f_count == 0)
				continue;
			if (fp->f_flag & FDEFER) {
				fp->f_flag &= ~FDEFER;
				unp_defer--;
			} else {
				if (fp->f_flag & FMARK)
					continue;
				if (fp->f_count == fp->f_msgcount)
					continue;
				fp->f_flag |= FMARK;
			}
D 43
			if (fp->f_type != DTYPE_SOCKET)
E 43
I 43
			if (fp->f_type != DTYPE_SOCKET ||
			    (so = (struct socket *)fp->f_data) == 0)
E 43
				continue;
D 43
			so = (struct socket *)fp->f_data;
E 43
D 24
			if (so->so_proto->pr_family != AF_UNIX ||
E 24
I 24
			if (so->so_proto->pr_domain != &unixdomain ||
E 24
D 29
			    (so->so_proto->pr_flags&PR_ADDR) == 0)
E 29
I 29
			    (so->so_proto->pr_flags&PR_RIGHTS) == 0)
E 29
				continue;
I 63
#ifdef notdef
E 63
			if (so->so_rcv.sb_flags & SB_LOCK) {
D 63
				sbwait(&so->so_rcv);
E 63
I 63
				/*
				 * This is problematical; it's not clear
				 * we need to wait for the sockbuf to be
				 * unlocked (on a uniprocessor, at least),
				 * and it's also not clear what to do
				 * if sbwait returns an error due to receipt
				 * of a signal.  If sbwait does return
				 * an error, we'll go into an infinite
				 * loop.  Delete all of this for now.
				 */
				(void) sbwait(&so->so_rcv);
E 63
				goto restart;
			}
I 63
#endif
E 63
			unp_scan(so->so_rcv.sb_mb, unp_mark);
		}
	} while (unp_defer);
D 69
	for (fp = file; fp < fileNFILE; fp++) {
E 69
I 69
D 76
	for (fp = filehead; fp; fp = fp->f_filef) {
E 76
I 76
D 88
	for (fp = filehead; fp; fp = nextfp) {
E 88
I 88
	/*
	 * We grab an extra reference to each of the file table entries
	 * that are not otherwise accessible and then free the rights
	 * that are stored in messages on them.
	 *
	 * The bug in the orginal code is a little tricky, so I'll describe
	 * what's wrong with it here.
	 *
	 * It is incorrect to simply unp_discard each entry for f_msgcount
	 * times -- consider the case of sockets A and B that contain
	 * references to each other.  On a last close of some other socket,
	 * we trigger a gc since the number of outstanding rights (unp_rights)
	 * is non-zero.  If during the sweep phase the gc code un_discards,
	 * we end up doing a (full) closef on the descriptor.  A closef on A
	 * results in the following chain.  Closef calls soo_close, which
	 * calls soclose.   Soclose calls first (through the switch
	 * uipc_usrreq) unp_detach, which re-invokes unp_gc.  Unp_gc simply
	 * returns because the previous instance had set unp_gcing, and
	 * we return all the way back to soclose, which marks the socket
	 * with SS_NOFDREF, and then calls sofree.  Sofree calls sorflush
	 * to free up the rights that are queued in messages on the socket A,
	 * i.e., the reference on B.  The sorflush calls via the dom_dispose
	 * switch unp_dispose, which unp_scans with unp_discard.  This second
	 * instance of unp_discard just calls closef on B.
	 *
	 * Well, a similar chain occurs on B, resulting in a sorflush on B,
	 * which results in another closef on A.  Unfortunately, A is already
	 * being closed, and the descriptor has already been marked with
	 * SS_NOFDREF, and soclose panics at this point.
	 *
	 * Here, we first take an extra reference to each inaccessible
	 * descriptor.  Then, we call sorflush ourself, since we know
	 * it is a Unix domain socket anyhow.  After we destroy all the
	 * rights carried in messages, we do a last closef to get rid
	 * of our extra reference.  This is the last close, and the
	 * unp_detach etc will shut down the socket.
	 *
	 * 91/09/19, bsy@cs.cmu.edu
	 */
	extra_ref = malloc(nfiles * sizeof(struct file *), M_FILE, M_WAITOK);
D 96
	for (nunref = 0, fp = filehead, fpp = extra_ref; fp; fp = nextfp) {
E 88
		nextfp = fp->f_filef;
E 96
I 96
	for (nunref = 0, fp = filehead.lh_first, fpp = extra_ref; fp != 0;
	    fp = nextfp) {
		nextfp = fp->f_list.le_next;
E 96
E 76
E 69
		if (fp->f_count == 0)
			continue;
D 34
		if (fp->f_count == fp->f_msgcount && (fp->f_flag&FMARK)==0) {
			if (fp->f_type != DTYPE_SOCKET)
				panic("unp_gc");
			(void) soshutdown((struct socket *)fp->f_data, 0);
		}
E 34
I 34
D 88
		if (fp->f_count == fp->f_msgcount && (fp->f_flag & FMARK) == 0)
			while (fp->f_msgcount)
				unp_discard(fp);
E 88
I 88
		if (fp->f_count == fp->f_msgcount && !(fp->f_flag & FMARK)) {
			*fpp++ = fp;
			nunref++;
			fp->f_count++;
		}
E 88
E 34
	}
I 88
	for (i = nunref, fpp = extra_ref; --i >= 0; ++fpp)
		sorflush((struct socket *)(*fpp)->f_data);
	for (i = nunref, fpp = extra_ref; --i >= 0; ++fpp)
D 99
		closef(*fpp);
E 99
I 99
		closef(*fpp, (struct proc *)NULL);
E 99
	free((caddr_t)extra_ref, M_FILE);
E 88
	unp_gcing = 0;
}

I 97
void
E 97
D 24
unp_scan(m, op)
	register struct mbuf *m;
E 24
I 24
unp_dispose(m)
	struct mbuf *m;
{
D 97
	int unp_discard();
E 97

D 25
	unp_scan(m, unp_discard);
E 25
I 25
	if (m)
		unp_scan(m, unp_discard);
E 25
}

I 97
void
E 97
unp_scan(m0, op)
	register struct mbuf *m0;
E 24
D 97
	int (*op)();
E 97
I 97
D 98
	void (*op)();
E 98
I 98
	void (*op) __P((struct file *));
E 98
E 97
{
I 24
	register struct mbuf *m;
E 24
	register struct file **rp;
I 57
	register struct cmsghdr *cm;
E 57
	register int i;
D 24
	int qfds;
E 24
I 24
D 25
	int qfds = 0;
E 25
I 25
	int qfds;
E 25
E 24

D 24
	while (m) {
		m = m->m_next;
		if (m == 0)
			goto bad;
		if (m->m_len) {
			qfds = m->m_len / sizeof (struct file *);
			rp = mtod(m, struct file **);
			for (i = 0; i < qfds; i++)
				(*op)(*rp++);
		}
		do {
			m = m->m_next;
			if (m == 0)
				goto bad;
		} while (m->m_act == 0);
		m = m->m_next;
E 24
I 24
	while (m0) {
		for (m = m0; m; m = m->m_next)
D 57
			if (m->m_type == MT_RIGHTS && m->m_len) {
D 56
				qfds = m->m_len / sizeof (struct file *);
				rp = mtod(m, struct file **);
E 56
I 56
				register struct cmsghdr *cm;
E 57
I 57
			if (m->m_type == MT_CONTROL &&
			    m->m_len >= sizeof(*cm)) {
E 57
				cm = mtod(m, struct cmsghdr *);
I 57
				if (cm->cmsg_level != SOL_SOCKET ||
				    cm->cmsg_type != SCM_RIGHTS)
					continue;
E 57
				qfds = (cm->cmsg_len - sizeof *cm)
						/ sizeof (struct file *);
				rp = (struct file **)(cm + 1);
E 56
				for (i = 0; i < qfds; i++)
					(*op)(*rp++);
				break;		/* XXX, but saves time */
			}
D 25
		m0 = m0->m_next;
E 25
I 25
		m0 = m0->m_act;
E 25
E 24
	}
D 24
	return;
bad:
	panic("unp_gcscan");
E 24
I 24
D 25
	if (qfds == 0)
		panic("unp_gcscan");
E 25
E 24
}

I 97
void
E 97
unp_mark(fp)
	struct file *fp;
{

	if (fp->f_flag & FMARK)
		return;
	unp_defer++;
	fp->f_flag |= (FMARK|FDEFER);
}

I 97
void
E 97
unp_discard(fp)
	struct file *fp;
{

I 90
D 91
	if (fp->f_msgcount == 0)
		return;
E 91
E 90
	fp->f_msgcount--;
I 34
	unp_rights--;
E 34
D 12
	closef(fp, 0);
E 12
I 12
D 55
	closef(fp);
E 55
I 55
D 70
	(void) closef(fp);
E 70
I 70
	(void) closef(fp, (struct proc *)NULL);
E 70
E 55
E 12
E 10
E 3
}
E 1
