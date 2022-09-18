h37870
s 00025/00001/00728
d D 8.2 95/02/14 10:55:17 cgd 78 77
c return types.
e
s 00002/00002/00727
d D 8.1 93/06/10 21:59:54 bostic 77 76
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00010/00719
d D 7.19 92/10/11 10:38:54 bostic 76 75
c make kernel includes standard
e
s 00002/00026/00727
d D 7.18 92/02/15 21:15:00 mckusick 75 73
c delete sbselqueue; convert to use new select interface, selrecord/selwakeup
e
s 00040/00040/00713
d D 7.16.1.1 91/05/09 19:07:40 sklower 74 71
c try changing conventions about where M_EOR lies (never tested)
e
s 00003/00003/00750
d D 7.17 91/05/04 16:40:31 karels 73 71
c add proc parm to sbselqueue; rm user.h
e
s 00017/00009/00736
d R 7.17 91/05/04 16:30:38 karels 72 71
c add proc parm to sbselqueue
e
s 00014/00006/00739
d D 7.16 91/02/19 17:41:20 sklower 71 70
c fix sbappend to check the last mbuf in a chain for M_EORness;
c fix sbcompress not to compress out zero length mbufs if the type is different.
e
s 00001/00011/00744
d D 7.15 90/06/28 21:24:20 bostic 70 69
c new copyright notice
e
s 00023/00000/00732
d D 7.14 90/06/28 15:14:09 karels 69 68
c add sbcheck for debugging only
e
s 00004/00002/00728
d D 7.13 90/06/25 15:46:44 karels 68 67
c keep track of pending selects
e
s 00036/00039/00694
d D 7.12 90/05/20 16:27:01 karels 67 66
c rights => control, various cleanups
e
s 00047/00008/00686
d D 7.11 90/04/03 21:31:51 karels 66 65
c tsleep; sblock/sbwait catch/return interrupts; implement lowat,
c timeout; move SIGPIPE up to syscall layer; strings for sleep messages
e
s 00034/00019/00660
d D 7.10 90/03/25 16:56:21 karels 65 64
c as currently running: tsleep round one; confirming socket changes;
c added parameter to sonewconn for connstatus (temp. renamed); make so_q's
c be fifo; some EOR stuff in sbappend
e
s 00000/00002/00679
d D 7.9 89/05/09 16:53:08 mckusick 64 63
c get rid of extraneous header files
e
s 00069/00016/00612
d D 7.8 89/04/08 17:47:36 karels 63 62
c malloc sockets (by sklower)
e
s 00004/00004/00624
d D 7.7 88/10/12 15:20:15 marc 62 61
c posix job control (pgrp -> pgid)
e
s 00036/00042/00592
d D 7.6 88/08/21 21:53:56 karels 61 60
c working with new mbufs
e
s 00010/00005/00624
d D 7.5 88/06/29 17:18:09 bostic 60 59
c install approved copyright notice
e
s 00001/00000/00628
d D 7.4 88/05/26 09:00:44 karels 59 58
c in sonewconn, set buffer limits of new socket to those of head
e
s 00006/00005/00622
d D 7.3 88/01/28 10:18:13 karels 58 57
c lint
e
s 00008/00002/00619
d D 7.2 87/12/30 12:06:42 bostic 57 56
c add Berkeley header
e
s 00001/00001/00620
d D 7.1 86/06/05 00:17:08 mckusick 56 55
c 4.3BSD release version
e
s 00003/00003/00618
d D 6.16 86/03/12 11:29:10 karels 55 54
c limit mb_cc to 80% of max so protocols don't get too close to mbcnt overflow
e
s 00001/00005/00620
d D 6.15 86/02/23 23:12:43 karels 54 53
c lint
e
s 00001/00001/00624
d D 6.14 86/02/07 11:37:27 karels 53 52
c make sbflush zap any/all 0-length pakcets
e
s 00001/00001/00624
d D 6.13 86/01/21 22:44:35 karels 52 51
c delay sballoc's in sbappendaddr until committed
e
s 00001/00001/00624
d D 6.12 86/01/20 15:42:06 karels 51 50
c ignore 0-length rights
e
s 00040/00056/00585
d D 6.11 85/12/19 14:52:08 karels 50 49
c change datagram queuing, full packet on one chain; allow rights
c in streams
e
s 00007/00001/00634
d D 6.10 85/06/08 15:04:12 mckusick 49 48
c Add copyright
e
s 00003/00005/00632
d D 6.9 85/06/08 13:11:37 karels 48 47
c reverse sense of pid/pgrp for fcntl, SIOCSPGRP (pgrp is negative)
e
s 00006/00005/00631
d D 6.8 85/06/02 23:25:01 karels 47 45
c minor cleanups
e
s 00006/00005/00631
d R 6.8 85/06/02 23:22:44 karels 46 45
c rights must be MT_RIGHTS (confuses soreceive otherwise!)
e
s 00002/00001/00634
d D 6.7 84/11/21 12:20:23 karels 45 43
c oops
e
s 00001/00000/00635
d R 6.7 84/11/19 10:42:18 karels 44 43
c oops
e
s 00003/00001/00632
d D 6.6 84/11/14 09:58:59 karels 43 42
c add sockopts for buffer sizes, etc.
e
s 00004/00000/00629
d D 6.5 84/11/02 10:39:52 karels 42 41
c drop trailing null mbufs in sbdrop (probably unnecessary now)
e
s 00012/00012/00617
d D 6.4 84/08/29 20:28:24 bloom 41 40
c Change to includes.  no more ../h
e
s 00224/00089/00405
d D 6.3 84/08/21 10:42:47 karels 40 39
c change datagram queuing to use m_act properly; type mbufs with rights;
c change protocol family number in protosw to pointer to domain (for sam)
e
s 00022/00000/00472
d D 6.2 84/01/11 15:57:52 cooper 39 38
c added sowakeup() function for ASYNC notification via SIGIO
e
s 00000/00000/00472
d D 6.1 83/07/29 06:48:38 sam 38 37
c 4.2 distribution
e
s 00038/00079/00434
d D 4.37 83/05/27 12:50:56 sam 37 36
c merge of bill's code plus lint (plus, of course, cleanup of bill's bugs)
e
s 00001/00000/00512
d D 4.36 83/05/01 18:44:01 sam 36 35
c fixes select on accepting connections from bill@dagobah.UUCP
e
s 00001/00001/00511
d D 4.35 83/01/13 18:34:09 sam 35 34
c no more opt parameter to usrreq
e
s 00001/00001/00511
d D 4.34 83/01/08 19:09:04 sam 34 33
c change semantics of sonewconn: socket returned is assumed not 
c to have a file descriptor referencing it; soaccept shaves this flag off 
c now on user accept; this cleans up problems with lost sockets in tcp_input
e
s 00006/00024/00506
d D 4.33 83/01/04 20:49:20 sam 33 32
c from reading the code -- boy is there a lot of work to be done
e
s 00002/00002/00528
d D 4.32 82/12/14 17:11:24 sam 32 31
c typed mbufs
e
s 00016/00000/00514
d D 4.31 82/11/03 00:04:13 root 31 30
c soreserve
e
s 00001/00001/00513
d D 4.30 82/10/22 01:14:41 root 30 29
c lint
e
s 00042/00000/00472
d D 4.29 82/10/16 17:40:41 root 29 28
c add code looking for panic:receive problem
e
s 00000/00002/00472
d D 4.28 82/10/09 05:39:55 wnj 28 27
c fix up header file dependencies 
e
s 00000/00001/00474
d D 4.27 82/10/05 21:58:55 root 27 26
c 
e
s 00001/00001/00474
d D 4.26 82/10/03 23:39:44 root 26 25
c overhaul
e
s 00001/00001/00474
d D 4.25 82/08/22 21:15:09 root 25 24
c restore id keywords
e
s 00106/00004/00369
d D 4.24 82/07/24 18:13:27 root 24 23
c merge with calder
e
s 00001/00003/00372
d D 4.23 82/06/14 22:17:32 wnj 23 22
c get rid of m_release stuff
e
s 00000/00015/00375
d D 4.22 82/03/19 14:22:24 sam 22 21
c purge extraneous stuff
e
s 00010/00009/00380
d D 4.21 82/03/09 20:32:35 root 21 20
c 
e
s 00001/00001/00388
d D 4.20 82/01/19 07:32:26 root 20 19
c m_get(0)->m_get(M_DONTWAIT)
e
s 00010/00002/00379
d D 4.19 82/01/19 04:35:27 wnj 19 18
c missing wakeups and critical section
e
s 00009/00005/00372
d D 4.18 82/01/19 02:05:09 wnj 18 17
c switch in soselect
e
s 00001/00001/00376
d D 4.17 81/12/22 23:45:36 root 17 16
c bug which lost packets
e
s 00021/00001/00356
d D 4.16 81/12/19 12:53:00 wnj 16 15
c don't call sbdrop with 0 chars;
e
s 00000/00004/00357
d D 4.15 81/12/12 18:07:55 root 15 14
c delete prints
e
s 00005/00001/00356
d D 4.14 81/12/12 17:49:54 root 14 13
c almost works
e
s 00003/00003/00354
d D 4.13 81/12/03 17:27:28 wnj 13 12
c cleanup
e
s 00076/00002/00281
d D 4.12 81/12/02 17:27:06 wnj 12 11
c more cleanup
e
s 00002/00002/00281
d D 4.11 81/11/26 11:59:17 wnj 11 10
c before carry to arpavax
e
s 00005/00006/00278
d D 4.10 81/11/24 07:57:49 wnj 10 9
c remove an else to simplify code
e
s 00002/00016/00282
d D 4.9 81/11/23 00:00:28 wnj 9 8
c cleaned up and re-enable compaction
e
s 00029/00007/00269
d D 4.8 81/11/22 23:57:57 wnj 8 7
c several fixes; also crud (first working dg version)
e
s 00001/00001/00275
d D 4.7 81/11/22 10:53:38 wnj 7 6
c scale error on arg to m_release: mbufs, not chars
e
s 00002/00002/00274
d D 4.6 81/11/21 22:13:39 root 6 5
c fix mbuf accounting
e
s 00005/00002/00271
d D 4.5 81/11/21 21:33:53 wnj 5 4
c fix to sbwakeup (missing &); fix to sbappend (initial loop wrong)
e
s 00004/00004/00269
d D 4.4 81/11/21 15:16:47 wnj 4 3
c cc vs. hiwat; mbcnt vs. mbmax typos
e
s 00027/00056/00246
d D 4.3 81/11/18 15:45:33 wnj 3 2
c more cleanup
e
s 00033/00004/00269
d D 4.2 81/11/16 14:21:19 wnj 2 1
c lint
e
s 00273/00000/00000
d D 4.1 81/11/15 13:03:38 wnj 1 0
c date and time created 81/11/15 13:03:38 by wnj
e
u
U
f b 
t
T
I 1
D 24
/*	%M%	%I%	%E%	*/
E 24
I 24
D 25
/*	socketsubr.c	4.24	82/07/21	*/
E 25
I 25
D 49
/*	%M%	%I%	%E%	*/
E 49
I 49
/*
D 56
 * Copyright (c) 1982 Regents of the University of California.
E 56
I 56
D 61
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 61
I 61
D 66
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
E 66
I 66
D 77
 * Copyright (c) 1982, 1986, 1988, 1990 Regents of the University of California.
E 66
E 61
E 56
D 57
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 57
I 57
 * All rights reserved.
E 77
I 77
 * Copyright (c) 1982, 1986, 1988, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 77
 *
D 70
 * Redistribution and use in source and binary forms are permitted
D 60
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 60
I 60
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
E 70
I 70
 * %sccs.include.redist.c%
E 70
E 60
E 57
 *
 *	%W% (Berkeley) %G%
 */
E 49
E 25
E 24

D 41
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/proc.h"
#include "../h/file.h"
#include "../h/inode.h"
#include "../h/buf.h"
#include "../h/mbuf.h"
D 3
#include "../h/protocol.h"
E 3
#include "../h/protosw.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
E 41
I 41
D 76
#include "param.h"
#include "systm.h"
D 64
#include "dir.h"
E 64
D 73
#include "user.h"
E 73
#include "proc.h"
#include "file.h"
D 64
#include "inode.h"
E 64
#include "buf.h"
I 61
#include "malloc.h"
E 61
#include "mbuf.h"
#include "protosw.h"
#include "socket.h"
#include "socketvar.h"
E 76
I 76
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/buf.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
E 76
I 65
D 66
#include "tsleep.h"
E 66
E 65
E 41
D 3
#include "../h/inaddr.h"
E 3
D 11
#include "../net/inet.h"
#include "../net/inet_systm.h"
E 11
I 11
D 28
#include "../net/in.h"
#include "../net/in_systm.h"
E 28
E 11

/*
 * Primitive routines for operating on sockets and socket buffers
 */

I 66
/* strings for sleep message: */
char	netio[] = "netio";
char	netcon[] = "netcon";
char	netcls[] = "netcls";

u_long	sb_max = SB_MAX;		/* patchable */

E 66
/*
 * Procedures to manipulate state flags of socket
D 12
 * and do appropriate wakeups.
E 12
I 12
D 24
 * and do appropriate wakeups.  Normal sequence is that
 * soisconnecting() is called during processing of connect() call,
E 24
I 24
 * and do appropriate wakeups.  Normal sequence from the
 * active (originating) side is that soisconnecting() is
 * called during processing of connect() call,
E 24
 * resulting in an eventual call to soisconnected() if/when the
 * connection is established.  When the connection is torn down
 * soisdisconnecting() is called during processing of disconnect() call,
 * and soisdisconnected() is called when the connection to the peer
 * is totally severed.  The semantics of these routines are such that
 * connectionless protocols can call soisconnected() and soisdisconnected()
 * only, bypassing the in-progress calls when setting up a ``connection''
 * takes no time.
 *
D 24
 * When higher level protocols are implemented in
E 24
I 24
D 37
 * From the passive side, a socket is created with SO_ACCEPTCONN
 * creating two queues of sockets: so_q0 for connections in progress
E 37
I 37
 * From the passive side, a socket is created with
 * two queues of sockets: so_q0 for connections in progress
E 37
 * and so_q for connections already made and awaiting user acceptance.
 * As a protocol is preparing incoming connections, it creates a socket
 * structure queued on so_q0 by calling sonewconn().  When the connection
 * is established, soisconnected() is called, and transfers the
 * socket structure to so_q, making it available to accept().
 * 
D 37
 * If a SO_ACCEPTCONN socket is closed with sockets on either
E 37
I 37
 * If a socket is closed with sockets on either
E 37
 * so_q0 or so_q, these sockets are dropped.
 *
D 37
 * If and when higher level protocols are implemented in
E 37
I 37
 * If higher level protocols are implemented in
E 37
E 24
 * the kernel, the wakeups done here will sometimes
D 37
 * be implemented as software-interrupt process scheduling.
E 37
I 37
 * cause software-interrupt process scheduling.
E 37
E 12
 */
I 12

I 78
void
E 78
E 12
soisconnecting(so)
D 37
	struct socket *so;
E 37
I 37
	register struct socket *so;
E 37
{

I 14
D 15
printf("soisconnecting %x\n", so);
E 15
E 14
	so->so_state &= ~(SS_ISCONNECTED|SS_ISDISCONNECTING);
	so->so_state |= SS_ISCONNECTING;
D 65
	wakeup((caddr_t)&so->so_timeo);
E 65
}

I 78
void
E 78
soisconnected(so)
D 37
	struct socket *so;
E 37
I 37
	register struct socket *so;
E 37
{
I 24
	register struct socket *head = so->so_head;
E 24

I 24
D 65
	if (head) {
		if (soqremque(so, 0) == 0)
			panic("soisconnected");
E 65
I 65
	so->so_state &= ~(SS_ISCONNECTING|SS_ISDISCONNECTING|SS_ISCONFIRMING);
	so->so_state |= SS_ISCONNECTED;
	if (head && soqremque(so, 0)) {
E 65
		soqinsque(head, so, 1);
D 37
		wakeup((caddr_t)&head->so_timeo);
E 37
I 36
		sorwakeup(head);
I 37
		wakeup((caddr_t)&head->so_timeo);
I 65
	} else {
		wakeup((caddr_t)&so->so_timeo);
		sorwakeup(so);
		sowwakeup(so);
E 65
E 37
E 36
	}
E 24
I 14
D 15
printf("soisconnected %x\n", so);
E 15
E 14
D 65
	so->so_state &= ~(SS_ISCONNECTING|SS_ISDISCONNECTING);
	so->so_state |= SS_ISCONNECTED;
	wakeup((caddr_t)&so->so_timeo);
I 19
	sorwakeup(so);
	sowwakeup(so);
E 65
E 19
}

I 78
void
E 78
soisdisconnecting(so)
D 37
	struct socket *so;
E 37
I 37
	register struct socket *so;
E 37
{

D 14
	so->so_state &= ~(SS_ISCONNECTED|SS_ISCONNECTING);
E 14
I 14
D 15
printf("soisdisconnecting %x\n", so);
E 15
	so->so_state &= ~SS_ISCONNECTING;
E 14
	so->so_state |= (SS_ISDISCONNECTING|SS_CANTRCVMORE|SS_CANTSENDMORE);
	wakeup((caddr_t)&so->so_timeo);
I 12
D 13
	sorwakeup(so);
E 13
	sowwakeup(so);
I 13
	sorwakeup(so);
E 13
E 12
}

I 78
void
E 78
soisdisconnected(so)
D 37
	struct socket *so;
E 37
I 37
	register struct socket *so;
E 37
{

I 14
D 15
printf("soisdisconnected %x\n", so);
E 15
E 14
	so->so_state &= ~(SS_ISCONNECTING|SS_ISCONNECTED|SS_ISDISCONNECTING);
	so->so_state |= (SS_CANTRCVMORE|SS_CANTSENDMORE);
	wakeup((caddr_t)&so->so_timeo);
	sowwakeup(so);
	sorwakeup(so);
I 24
}

/*
 * When an attempt at a new connection is noted on a socket
 * which accepts connections, sonewconn is called.  If the
 * connection is possible (subject to space constraints, etc.)
 * then we allocate a new structure, propoerly linked into the
 * data structure of the original socket, and return this.
I 65
 * Connstatus may be 0, or SO_ISCONFIRMING, or SO_ISCONNECTED.
I 66
 *
 * Currently, sonewconn() is defined as sonewconn1() in socketvar.h
 * to catch calls that are missing the (new) second parameter.
E 66
E 65
 */
struct socket *
D 65
sonewconn(head)
E 65
I 65
D 66
sonewsock(head, connstatus)
E 66
I 66
sonewconn1(head, connstatus)
E 66
E 65
	register struct socket *head;
I 65
	int connstatus;
E 65
{
	register struct socket *so;
I 65
	int soqueue = connstatus ? 1 : 0;
E 65
D 37
	struct mbuf *m;
E 37
I 37
D 63
	register struct mbuf *m;
E 63
E 37

	if (head->so_qlen + head->so_q0len > 3 * head->so_qlimit / 2)
D 63
		goto bad;
D 32
	m = m_getclr(M_DONTWAIT);
E 32
I 32
	m = m_getclr(M_DONTWAIT, MT_SOCKET);
E 32
D 33
	if (m == 0)
E 33
I 33
	if (m == NULL)
E 33
		goto bad;
	so = mtod(m, struct socket *);
E 63
I 63
		return ((struct socket *)0);
	MALLOC(so, struct socket *, sizeof(*so), M_SOCKET, M_DONTWAIT);
	if (so == NULL) 
		return ((struct socket *)0);
	bzero((caddr_t)so, sizeof(*so));
E 63
	so->so_type = head->so_type;
	so->so_options = head->so_options &~ SO_ACCEPTCONN;
	so->so_linger = head->so_linger;
D 34
	so->so_state = head->so_state;
E 34
I 34
	so->so_state = head->so_state | SS_NOFDREF;
E 34
	so->so_proto = head->so_proto;
	so->so_timeo = head->so_timeo;
D 62
	so->so_pgrp = head->so_pgrp;
E 62
I 62
	so->so_pgid = head->so_pgid;
E 62
I 59
D 61
	(void) soreserve(so, head->so_snd.sb_hiwat, head->so_snd.sb_hiwat);
E 61
I 61
	(void) soreserve(so, head->so_snd.sb_hiwat, head->so_rcv.sb_hiwat);
E 61
E 59
D 65
	soqinsque(head, so, 0);
E 65
I 65
	soqinsque(head, so, soqueue);
E 65
D 26
	if ((*so->so_proto->pr_usrreq)(so, PRU_ATTACH, 0, 0)) {
E 26
I 26
D 33
	if ((*so->so_proto->pr_usrreq)(so, PRU_ATTACH, 0, 0, 0)) {
E 33
I 33
D 37
	if ((*so->so_proto->pr_usrreq)(so, PRU_ATTACH, (struct mbuf *)0,
D 35
	  (struct mbuf *)0, (struct sockopt *)0)) {
E 35
I 35
	  (struct mbuf *)0)) {
E 37
I 37
	if ((*so->so_proto->pr_usrreq)(so, PRU_ATTACH,
	    (struct mbuf *)0, (struct mbuf *)0, (struct mbuf *)0)) {
E 37
E 35
E 33
E 26
D 65
		(void) soqremque(so, 0);
E 65
I 65
		(void) soqremque(so, soqueue);
E 65
D 30
		m_free(m);
E 30
I 30
D 63
		(void) m_free(m);
E 30
		goto bad;
E 63
I 63
		(void) free((caddr_t)so, M_SOCKET);
		return ((struct socket *)0);
E 63
	}
I 65
	if (connstatus) {
		sorwakeup(head);
		wakeup((caddr_t)&head->so_timeo);
		so->so_state |= connstatus;
	}
E 65
	return (so);
D 63
bad:
	return ((struct socket *)0);
E 63
}

I 78
void
E 78
soqinsque(head, so, q)
	register struct socket *head, *so;
	int q;
{
I 65
D 66
	register struct socket **prev;
E 66
E 65

I 66
	register struct socket **prev;
E 66
	so->so_head = head;
	if (q == 0) {
		head->so_q0len++;
D 65
		so->so_q0 = head->so_q0;
		head->so_q0 = so;
E 65
I 65
		so->so_q0 = 0;
		for (prev = &(head->so_q0); *prev; )
			prev = &((*prev)->so_q0);
E 65
	} else {
		head->so_qlen++;
D 65
		so->so_q = head->so_q;
		head->so_q = so;
E 65
I 65
		so->so_q = 0;
		for (prev = &(head->so_q); *prev; )
			prev = &((*prev)->so_q);
E 65
	}
I 65
	*prev = so;
E 65
}

I 78
int
E 78
soqremque(so, q)
	register struct socket *so;
	int q;
{
	register struct socket *head, *prev, *next;

	head = so->so_head;
	prev = head;
	for (;;) {
		next = q ? prev->so_q : prev->so_q0;
		if (next == so)
			break;
D 65
		if (next == head)
E 65
I 65
		if (next == 0)
E 65
			return (0);
		prev = next;
	}
	if (q == 0) {
		prev->so_q0 = next->so_q0;
		head->so_q0len--;
	} else {
		prev->so_q = next->so_q;
		head->so_qlen--;
	}
	next->so_q0 = next->so_q = 0;
	next->so_head = 0;
	return (1);
E 24
}

I 12
/*
 * Socantsendmore indicates that no more data will be sent on the
 * socket; it would normally be applied to a socket when the user
 * informs the system that no more data is to be sent, by the protocol
 * code (in case PRU_SHUTDOWN).  Socantrcvmore indicates that no more data
 * will be received, and will normally be applied to the socket by a
 * protocol when it detects that the peer will send no more data.
 * Data queued for reading in the socket may yet be read.
 */

I 78
void
E 78
E 12
I 2
socantsendmore(so)
	struct socket *so;
{

	so->so_state |= SS_CANTSENDMORE;
	sowwakeup(so);
}

I 78
void
E 78
socantrcvmore(so)
	struct socket *so;
{

	so->so_state |= SS_CANTRCVMORE;
	sorwakeup(so);
}

E 2
/*
D 12
 * Select a socket.
E 12
I 12
D 75
 * Socket select/wakeup routines.
E 12
 */
I 12

/*
D 37
 * Interface routine to select() system
 * call for sockets.
 */
E 12
D 18
soselect(so, flag)
E 18
I 18
soselect(so, rw)
E 18
	register struct socket *so;
D 18
	int flag;
E 18
I 18
	int rw;
E 18
{
I 19
	int s = splnet();
E 19

D 18
	if (flag & FREAD) {
E 18
I 18
	switch (rw) {

	case FREAD:
E 18
D 19
		if (soreadable(so))
E 19
I 19
		if (soreadable(so)) {
			splx(s);
E 19
			return (1);
I 19
		}
E 19
		sbselqueue(&so->so_rcv);
D 18
	}
	if (flag & FWRITE) {
E 18
I 18
		break;

	case FWRITE:
E 18
D 19
		if (sowriteable(so))
E 19
I 19
		if (sowriteable(so)) {
			splx(s);
E 19
			return (1);
I 19
		}
E 19
		sbselqueue(&so->so_snd);
I 18
		break;
E 18
	}
I 19
	splx(s);
E 19
	return (0);
}

/*
E 37
 * Queue a process for a select on a socket buffer.
 */
D 73
sbselqueue(sb)
E 73
I 73
sbselqueue(sb, cp)
E 73
	struct sockbuf *sb;
I 73
	struct proc *cp;
E 73
{
D 61
	register struct proc *p;
E 61
I 61
	struct proc *p;
E 61

D 2
	if ((p = sb->sb_sel) && p->p_wchan == (caddr_t)select)
E 2
I 2
	if ((p = sb->sb_sel) && p->p_wchan == (caddr_t)&selwait)
E 2
		sb->sb_flags |= SB_COLL;
D 68
	else
E 68
I 68
	else {
E 68
D 73
		sb->sb_sel = u.u_procp;
E 73
I 73
		sb->sb_sel = cp;
E 73
I 68
		sb->sb_flags |= SB_SEL;
	}
E 68
}

/*
E 75
I 2
 * Wait for data to arrive at/drain from a socket buffer.
 */
I 78
int
E 78
sbwait(sb)
	struct sockbuf *sb;
{

	sb->sb_flags |= SB_WAIT;
D 65
	sleep((caddr_t)&sb->sb_cc, PZERO+1);
E 65
I 65
D 66
	tsleep((caddr_t)&sb->sb_cc, PZERO+1, SLP_SO_SBWAIT, 0);
E 66
I 66
	return (tsleep((caddr_t)&sb->sb_cc,
	    (sb->sb_flags & SB_NOINTR) ? PSOCK : PSOCK | PCATCH, netio,
	    sb->sb_timeo));
E 66
E 65
}

I 66
/* 
 * Lock a sockbuf already known to be locked;
 * return any error returned from sleep (EINTR).
 */
I 78
int
E 78
sb_lock(sb)
	register struct sockbuf *sb;
{
	int error;

	while (sb->sb_flags & SB_LOCK) {
		sb->sb_flags |= SB_WANT;
		if (error = tsleep((caddr_t)&sb->sb_flags, 
		    (sb->sb_flags & SB_NOINTR) ? PSOCK : PSOCK|PCATCH,
		    netio, 0))
			return (error);
	}
	sb->sb_flags |= SB_LOCK;
	return (0);
}

E 66
/*
E 2
 * Wakeup processes waiting on a socket buffer.
I 61
 * Do asynchronous notification via SIGIO
 * if the socket has the SS_ASYNC flag set.
E 61
 */
I 78
void
E 78
D 61
sbwakeup(sb)
E 61
I 61
sowakeup(so, sb)
	register struct socket *so;
E 61
D 37
	struct sockbuf *sb;
E 37
I 37
	register struct sockbuf *sb;
E 37
{
I 61
D 63
	register struct proc *p;
E 63
I 63
	struct proc *p;
E 63
E 61

D 75
	if (sb->sb_sel) {
I 8
D 9
		printf("sb %x\n", sb);
E 9
E 8
		selwakeup(sb->sb_sel, sb->sb_flags & SB_COLL);
		sb->sb_sel = 0;
D 68
		sb->sb_flags &= ~SB_COLL;
E 68
I 68
		sb->sb_flags &= ~(SB_SEL|SB_COLL);
E 68
	}
E 75
I 75
	selwakeup(&sb->sb_sel);
	sb->sb_flags &= ~SB_SEL;
E 75
	if (sb->sb_flags & SB_WAIT) {
		sb->sb_flags &= ~SB_WAIT;
D 5
		wakeup((caddr_t)sb->sb_cc);
E 5
I 5
		wakeup((caddr_t)&sb->sb_cc);
E 5
	}
D 61
}

/*
I 39
 * Wakeup socket readers and writers.
 * Do asynchronous notification via SIGIO
 * if the socket has the SS_ASYNC flag set.
 */
sowakeup(so, sb)
	register struct socket *so;
	struct sockbuf *sb;
{
	register struct proc *p;

	sbwakeup(sb);
E 61
	if (so->so_state & SS_ASYNC) {
D 48
		if (so->so_pgrp == 0)
			return;
		else if (so->so_pgrp > 0)
			gsignal(so->so_pgrp, SIGIO);
		else if ((p = pfind(-so->so_pgrp)) != 0)
E 48
I 48
D 62
		if (so->so_pgrp < 0)
			gsignal(-so->so_pgrp, SIGIO);
		else if (so->so_pgrp > 0 && (p = pfind(so->so_pgrp)) != 0)
E 62
I 62
		if (so->so_pgid < 0)
			gsignal(-so->so_pgid, SIGIO);
		else if (so->so_pgid > 0 && (p = pfind(so->so_pgid)) != 0)
E 62
E 48
			psignal(p, SIGIO);
	}
}

/*
E 39
I 12
 * Socket buffer (struct sockbuf) utility routines.
 *
 * Each socket contains two socket buffers: one for sending data and
 * one for receiving data.  Each buffer contains a queue of mbufs,
 * information about the number of mbufs and amount of data in the
 * queue, and other fields allowing select() statements and notification
 * on data availability to be implemented.
 *
I 40
 * Data stored in a socket buffer is maintained as a list of records.
 * Each record is a list of mbufs chained together with the m_next
D 61
 * field.  Records are chained together with the m_act field. The upper
E 61
I 61
 * field.  Records are chained together with the m_nextpkt field. The upper
E 61
 * level routine soreceive() expects the following conventions to be
 * observed when placing information in the receive buffer:
 *
 * 1. If the protocol requires each message be preceded by the sender's
 *    name, then a record containing that name must be present before
 *    any associated data (mbuf's must be of type MT_SONAME).
 * 2. If the protocol supports the exchange of ``access rights'' (really
 *    just additional data associated with the message), and there are
 *    ``rights'' to be received, then a record containing this data
 *    should be present (mbuf's must be of type MT_RIGHTS).
 * 3. If a name or rights record exists, then it must be followed by
 *    a data record, perhaps of zero length.
 *
E 40
 * Before using a new socket structure it is first necessary to reserve
D 40
 * buffer space to the socket, by calling sbreserve.  This commits
E 40
I 40
D 58
 * buffer space to the socket, by calling sbreserve().  This commits
E 58
I 58
 * buffer space to the socket, by calling sbreserve().  This should commit
E 58
E 40
 * some of the available buffer space in the system buffer pool for the
D 40
 * socket.  The space should be released by calling sbrelease when the
E 40
I 40
D 58
 * socket.  The space should be released by calling sbrelease() when the
E 40
 * socket is destroyed.
E 58
I 58
 * socket (currently, it does nothing but enforce limits).  The space
 * should be released by calling sbrelease() when the socket is destroyed.
E 58
D 50
 *
D 40
 * The routine sbappend() is normally called to append new mbufs
 * to a socket buffer, after checking that adequate space is available
 * comparing the function spspace() with the amount of data to be added.
E 40
I 40
 * The routines sbappend() or sbappendrecord() are normally called to
 * append new mbufs to a socket buffer, after checking that adequate
 * space is available, comparing the function sbspace() with the amount
 * of data to be added.  sbappendrecord() differs from sbappend() in
 * that data supplied is treated as the beginning of a new record.
E 40
 * Data is normally removed from a socket buffer in a protocol by
 * first calling m_copy on the socket buffer mbuf chain and sending this
 * to a peer, and then removing the data from the socket buffer with
D 40
 * sbdrop when the data is acknowledged by the peer (or immediately
D 13
 * in the case of unreliable protocols.
E 13
I 13
 * in the case of unreliable protocols.)
E 40
I 40
 * sbdrop() or sbdroprecord() when the data is acknowledged by the peer
 * (or immediately in the case of unreliable protocols.)
E 40
E 13
 *
D 40
 * Protocols which do not require connections place both source address
 * and data information in socket buffer queues.  The source addresses
 * are stored in single mbufs after each data item, and are easily found
 * as the data items are all marked with end of record markers.  The
 * sbappendaddr() routine stores a datum and associated address in
 * a socket buffer.  Note that, unlike sbappend(), this routine checks
E 40
I 40
 * To place a sender's name, optionally, access rights, and data in a
 * socket buffer sbappendaddr() should be used.  To place access rights
 * and data in a socket buffer sbappendrights() should be used.  Note
 * that unlike sbappend() and sbappendrecord(), these routines check
E 40
 * for the caller that there will be enough space to store the data.
D 40
 * It fails if there is not enough space, or if it cannot find
 * a mbuf to store the address in.
 *
 * The higher-level routines sosend and soreceive (in socket.c)
D 13
 * also add data to, and remove data from socket buffers.
E 13
I 13
 * also add data to, and remove data from socket buffers repectively.
E 40
I 40
 * Each fails if there is not enough space, or if it cannot find mbufs
 * to store additional information in.
E 50
E 40
E 13
 */

I 78
int
E 78
I 31
soreserve(so, sndcc, rcvcc)
D 37
	struct socket *so;
E 37
I 37
	register struct socket *so;
E 37
D 58
	int sndcc, rcvcc;
E 58
I 58
	u_long sndcc, rcvcc;
E 58
{

	if (sbreserve(&so->so_snd, sndcc) == 0)
		goto bad;
	if (sbreserve(&so->so_rcv, rcvcc) == 0)
		goto bad2;
I 66
	if (so->so_rcv.sb_lowat == 0)
		so->so_rcv.sb_lowat = 1;
	if (so->so_snd.sb_lowat == 0)
		so->so_snd.sb_lowat = MCLBYTES;
	if (so->so_snd.sb_lowat > so->so_snd.sb_hiwat)
		so->so_snd.sb_lowat = so->so_snd.sb_hiwat;
E 66
	return (0);
bad2:
	sbrelease(&so->so_snd);
bad:
	return (ENOBUFS);
}

E 31
/*
E 12
 * Allot mbufs to a sockbuf.
I 55
D 66
 * Attempt to scale cc so that mbcnt doesn't become limiting
E 66
I 66
 * Attempt to scale mbmax so that mbcnt doesn't become limiting
E 66
 * if buffering efficiency is near the normal case.
E 55
 */
I 78
int
E 78
sbreserve(sb, cc)
	struct sockbuf *sb;
I 58
	u_long cc;
E 58
{

I 43
D 55
	if ((unsigned) cc > SB_MAX)
E 55
I 55
D 58
	if ((unsigned) cc > (unsigned)SB_MAX * CLBYTES / (2 * MSIZE + CLBYTES))
E 58
I 58
D 61
	if (cc > (u_long)SB_MAX * CLBYTES / (2 * MSIZE + CLBYTES))
E 61
I 61
D 66
	if (cc > (u_long)SB_MAX * MCLBYTES / (2 * MSIZE + MCLBYTES))
E 66
I 66
	if (cc > sb_max * MCLBYTES / (MSIZE + MCLBYTES))
E 66
E 61
E 58
E 55
		return (0);
E 43
D 6
	if (m_reserve(cc) == 0)
E 6
I 6
D 23
	if (m_reserve((cc*2)/MSIZE) == 0)
E 6
		return (0);
E 23
I 23
D 55
	/* someday maybe this routine will fail... */
E 55
E 23
D 4
	sb->sb_cc = cc;
	sb->sb_mbcnt = (cc*2)/MSIZE;
E 4
I 4
	sb->sb_hiwat = cc;
I 33
D 37
	/* the 2 implies names can be no more than 1 mbuf each */
E 33
D 8
	sb->sb_mbmax = (cc*2)/MSIZE;
E 8
I 8
	sb->sb_mbmax = cc*2;
E 37
I 37
D 55
	/* * 2 implies names can be no more than 1 mbuf each */
E 55
D 43
	sb->sb_mbmax = cc<<1;
E 43
I 43
D 45
	sb->sb_mbmax = MAX(cc * 2, SB_MAX);
E 45
I 45
D 66
	sb->sb_mbmax = MIN(cc * 2, SB_MAX);
E 66
I 66
	sb->sb_mbmax = min(cc * 2, sb_max);
	if (sb->sb_lowat > sb->sb_hiwat)
		sb->sb_lowat = sb->sb_hiwat;
E 66
E 45
E 43
E 37
E 8
E 4
I 2
	return (1);
E 2
}

/*
 * Free mbufs held by a socket, and reserved mbuf space.
 */
I 78
void
E 78
sbrelease(sb)
	struct sockbuf *sb;
{

	sbflush(sb);
D 4
	m_release(sb->sb_cc);
	sb->sb_cc = sb->sb_mbcnt = 0;
E 4
I 4
D 6
	m_release(sb->sb_hiwat);
E 6
I 6
D 7
	m_release(sb->sb_mbmax);
E 7
I 7
D 23
	m_release(sb->sb_mbmax/MSIZE);
E 23
E 7
E 6
	sb->sb_hiwat = sb->sb_mbmax = 0;
E 4
}

/*
D 40
 * Routines to add (at the end) and remove (from the beginning)
 * data from a mbuf queue.
E 40
I 40
 * Routines to add and remove
 * data from an mbuf queue.
I 50
 *
 * The routines sbappend() or sbappendrecord() are normally called to
 * append new mbufs to a socket buffer, after checking that adequate
 * space is available, comparing the function sbspace() with the amount
 * of data to be added.  sbappendrecord() differs from sbappend() in
 * that data supplied is treated as the beginning of a new record.
 * To place a sender's address, optional access rights, and data in a
 * socket receive buffer, sbappendaddr() should be used.  To place
 * access rights and data in a socket receive buffer, sbappendrights()
 * should be used.  In either case, the new data begins a new record.
 * Note that unlike sbappend() and sbappendrecord(), these routines check
 * for the caller that there will be enough space to store the data.
 * Each fails if there is not enough space, or if it cannot find mbufs
 * to store additional information in.
 *
 * Reliable protocols may use the socket send buffer to hold data
 * awaiting acknowledgement.  Data is normally copied from a socket
 * send buffer in a protocol with m_copy for output to a peer,
 * and then removing the data from the socket buffer with sbdrop()
 * or sbdroprecord() when the data is acknowledged by the peer.
E 50
E 40
 */

/*
D 40
 * Append mbuf queue m to sockbuf sb.
E 40
I 40
 * Append mbuf chain m to the last record in the
 * socket buffer sb.  The additional space associated
 * the mbuf chain is recorded in sb.  Empty mbufs are
 * discarded and mbufs are compacted where possible.
E 40
 */
I 78
void
E 78
sbappend(sb, m)
D 40
	register struct mbuf *m;
	register struct sockbuf *sb;
E 40
I 40
	struct sockbuf *sb;
	struct mbuf *m;
E 40
{
D 21
	register struct mbuf **np, *n;
E 21
I 21
D 74
	register struct mbuf *n;
E 74
I 74
	register struct mbuf *n, *n0;
E 74
E 21

I 29
D 33
SBCHECK(sb, "sbappend begin");
#ifdef notdef
{ struct mbuf *p;
printf("sba: ");
for (p = sb->sb_mb; p; p = p->m_next) printf("%x:(%x,%d) ",p,p->m_off,p->m_len);
printf("+= ");
for (p = m; p; p = p->m_next) printf("%x:(%x,%d) ",p,p->m_off,p->m_len);
printf("\n");
}
#endif
E 33
E 29
D 21
	np = &sb->sb_mb;
D 5
	while ((n = *np) && n->m_next)
E 5
I 5
	n = 0;
	while (*np) {
		n = *np;
E 5
		np = &n->m_next;
I 5
	}
E 21
I 21
D 40
	n = sb->sb_mb;
	if (n)
E 40
I 40
	if (m == 0)
		return;
	if (n = sb->sb_mb) {
D 61
		while (n->m_act)
			n = n->m_act;
E 61
I 61
		while (n->m_nextpkt)
			n = n->m_nextpkt;
E 61
E 40
D 71
		while (n->m_next)
E 71
I 71
D 74
		do {
E 71
D 65
			n = n->m_next;
E 65
I 65
			if (n->m_flags & M_EOR) {
				sbappendrecord(sb, m); /* XXXXXX!!!! */
				return;
D 71
			} else
				n = n->m_next;
E 71
I 71
			}
		} while (n->m_next && (n = n->m_next));
E 74
E 71
E 65
E 21
E 5
D 40
	while (m) {
I 16
		if (m->m_len == 0 && (int)m->m_act == 0) {
D 17
			m = m->m_next;
E 17
I 17
			m = m_free(m);
E 17
			continue;
		}
E 16
I 8
D 9
/*
E 9
E 8
		if (n && n->m_off <= MMAXOFF && m->m_off <= MMAXOFF &&
		   (int)n->m_act == 0 && (int)m->m_act == 0 &&
D 8
		   (n->m_off + n->m_len + m->m_off) <= MMAXOFF) {
D 2
			bcopy(mtod(m, caddr_t), mtod(n, caddr_t), m->m_len);
E 2
I 2
			bcopy(mtod(m, caddr_t), mtod(n, caddr_t),
E 8
I 8
		   (n->m_off + n->m_len + m->m_len) <= MMAXOFF) {
			bcopy(mtod(m, caddr_t), mtod(n, caddr_t) + n->m_len,
E 8
			    (unsigned)m->m_len);
E 2
			n->m_len += m->m_len;
			sb->sb_cc += m->m_len;
			m = m_free(m);
			continue;
		}
I 8
D 9
*/
E 9
E 8
		sballoc(sb, m);
D 21
		*np = m;
E 21
I 21
		if (n == 0)
			sb->sb_mb = m;
		else
			n->m_next = m;
E 21
		n = m;
D 21
		np = &n->m_next;
E 21
		m = m->m_next;
I 21
		n->m_next = 0;
E 40
E 21
	}
I 40
	sbcompress(sb, m, n);
E 40
I 29
D 33
#ifdef notdef
{ struct mbuf *p;
printf("res: ");
for (p = sb->sb_mb; p; p = p->m_next) printf("%x:(%x,%d) ",p,p->m_off,p->m_len);
printf("+= ");
for (p = m; p; p = p->m_next) printf("%x:(%x,%d) ",p,p->m_off,p->m_len);
printf("\n");
E 33
E 29
I 8
D 9
	nullchk("sbappend", sb->sb_mb);
E 9
E 8
}
I 29
D 33
#endif
SBCHECK(sb, "sbappend end");
}
E 33
E 29

I 69
#ifdef SOCKBUF_DEBUG
I 78
void
E 78
sbcheck(sb)
	register struct sockbuf *sb;
{
	register struct mbuf *m;
	register int len = 0, mbcnt = 0;

	for (m = sb->sb_mb; m; m = m->m_next) {
		len += m->m_len;
		mbcnt += MSIZE;
		if (m->m_flags & M_EXT)
			mbcnt += m->m_ext.ext_size;
		if (m->m_nextpkt)
			panic("sbcheck nextpkt");
	}
	if (len != sb->sb_cc || mbcnt != sb->sb_mbcnt) {
		printf("cc %d != %d || mbcnt %d != %d\n", len, sb->sb_cc,
		    mbcnt, sb->sb_mbcnt);
		panic("sbcheck");
	}
}
#endif

E 69
I 12
/*
D 40
 * Append data and address.
 * Return 0 if no space in sockbuf or if
 * can't get mbuf to stuff address in.
E 40
I 40
 * As above, except the mbuf chain
 * begins a new record.
E 40
 */
I 78
void
E 78
E 12
I 3
D 37
sbappendaddr(sb, asa, m0)
E 37
I 37
D 40
sbappendaddr(sb, asa, m0, rights0)
E 37
	struct sockbuf *sb;
	struct sockaddr *asa;
D 37
	struct mbuf *m0;
E 37
I 37
	struct mbuf *m0, *rights0;
E 40
I 40
sbappendrecord(sb, m0)
	register struct sockbuf *sb;
	register struct mbuf *m0;
E 40
E 37
{
D 37
	struct sockaddr *msa;
E 37
	register struct mbuf *m;
D 40
	register int len = sizeof (struct sockaddr);
I 37
	register struct mbuf *rights;
E 40
E 37

I 37
D 40
	if (rights0)
		len += rights0->m_len;
E 40
I 40
	if (m0 == 0)
		return;
	if (m = sb->sb_mb)
D 61
		while (m->m_act)
			m = m->m_act;
E 61
I 61
		while (m->m_nextpkt)
			m = m->m_nextpkt;
E 61
	/*
	 * Put the first mbuf on the queue.
	 * Note this permits zero length records.
	 */
	sballoc(sb, m0);
	if (m)
D 61
		m->m_act = m0;
E 61
I 61
		m->m_nextpkt = m0;
E 61
	else
		sb->sb_mb = m0;
	m = m0->m_next;
	m0->m_next = 0;
I 63
D 74
	if (m && (m0->m_flags & M_EOR)) {
		m0->m_flags &= ~M_EOR;
		m->m_flags |= M_EOR;
	}
E 74
E 63
	sbcompress(sb, m, m0);
}

/*
I 63
 * As above except that OOB data
 * is inserted at the beginning of the sockbuf,
 * but after any other OOB data.
 */
I 78
void
E 78
sbinsertoob(sb, m0)
	register struct sockbuf *sb;
	register struct mbuf *m0;
{
	register struct mbuf *m;
	register struct mbuf **mp;

	if (m0 == 0)
		return;
	for (mp = &sb->sb_mb; m = *mp; mp = &((*mp)->m_nextpkt)) {
	    again:
		switch (m->m_type) {

		case MT_OOBDATA:
			continue;		/* WANT next train */

		case MT_CONTROL:
			if (m = m->m_next)
				goto again;	/* inspect THIS train further */
		}
		break;
	}
	/*
	 * Put the first mbuf on the queue.
	 * Note this permits zero length records.
	 */
D 74
	sballoc(sb, m0);
E 74
	m0->m_nextpkt = *mp;
	*mp = m0;
D 74
	m = m0->m_next;
	m0->m_next = 0;
	if (m && (m0->m_flags & M_EOR)) {
		m0->m_flags &= ~M_EOR;
		m->m_flags |= M_EOR;
	}
	sbcompress(sb, m, m0);
E 74
I 74
	for (m = m0; m; m = m->m_next)
		sballoc(sb, m);
E 74
}

/*
E 63
D 67
 * Append address and data, and optionally, rights
E 67
I 67
 * Append address and data, and optionally, control (ancillary) data
E 67
D 61
 * to the receive queue of a socket.  Return 0 if
E 61
I 61
 * to the receive queue of a socket.  If present,
D 67
 * m0 Return 0 if
E 61
 * no space in sockbuf or insufficient mbufs.
E 67
I 67
 * m0 must include a packet header with total length.
 * Returns 0 if no space in sockbuf or insufficient mbufs.
E 67
 */
I 78
int
E 78
D 50
sbappendaddr(sb, asa, m0, rights0)		/* XXX */
E 50
I 50
D 67
sbappendaddr(sb, asa, m0, rights0)
E 67
I 67
sbappendaddr(sb, asa, m0, control)
E 67
E 50
	register struct sockbuf *sb;
	struct sockaddr *asa;
D 61
	struct mbuf *rights0, *m0;
E 61
I 61
D 67
	struct mbuf *m0, *rights0;
E 67
I 67
	struct mbuf *m0, *control;
E 67
E 61
{
	register struct mbuf *m, *n;
D 63
	int space = sizeof (*asa);
E 63
I 63
D 74
	int space = asa->sa_len;
E 74
I 74
	int space = asa->sa_len, eor = 0;
E 74
E 63

E 40
E 37
I 29
D 33
SBCHECK(sb, "sbappendaddr begin");
E 33
E 29
D 8
	for (m = m0; m; m = m->m_next)
E 8
I 8
D 9
	printf("sbappendaddr %x asa %x ", sb, asa);
E 9
D 50
	m = m0;
	if (m == 0)
		panic("sbappendaddr");
D 40
	for (;;) {
E 8
		len += m->m_len;
D 8
	if (len > sbspace(sb))
E 8
I 8
		if (m->m_next == 0) {
			m->m_act = (struct mbuf *)1;
			break;
		}
E 40
I 40
	do {
E 50
I 50
D 61
	for (m = m0; m; m = m->m_next)
E 50
		space += m->m_len;
E 61
I 61
if (m0 && (m0->m_flags & M_PKTHDR) == 0)
panic("sbappendaddr");
	if (m0)
		space += m0->m_pkthdr.len;
E 61
E 40
D 50
		m = m->m_next;
D 40
	}
D 9
	printf(": sb_cc %d sb_hiwat %d sb_mbcnt %d sb_mbmax %d sbspace %d: ",
	    sb->sb_cc, sb->sb_hiwat, sb->sb_mbcnt, sb->sb_mbmax,
	    sbspace(sb));
	if (len > sbspace(sb)) {
		printf("no space\n");
E 9
I 9
	if (len > sbspace(sb))
E 40
I 40
	} while (m);
E 50
D 67
	if (rights0)
		space += rights0->m_len;
E 67
I 67
	for (n = control; n; n = n->m_next) {
		space += n->m_len;
		if (n->m_next == 0)	/* keep pointer to last control buf */
			break;
	}
E 67
	if (space > sbspace(sb))
E 40
E 9
E 8
		return (0);
I 67
	if (asa->sa_len > MLEN)
		return (0);
E 67
I 8
D 9
	}
E 9
E 8
D 20
	m = m_get(0);
E 20
I 20
D 32
	m = m_get(M_DONTWAIT);
E 32
I 32
D 50
	m = m_get(M_DONTWAIT, MT_SONAME);
E 50
I 50
	MGET(m, M_DONTWAIT, MT_SONAME);
E 50
E 32
E 20
D 8
	if (m == 0)
E 8
I 8
D 9
	if (m == 0) {
		printf("no mbufs\n");
E 9
I 9
D 37
	if (m == 0)
E 37
I 37
D 40
	if (m == NULL)
E 40
I 40
	if (m == 0)
E 40
E 37
E 9
E 8
		return (0);
I 8
D 9
	}
E 9
E 8
D 27
	m->m_off = MMINOFF;
E 27
D 40
	m->m_len = sizeof (struct sockaddr);
D 37
	msa = mtod(m, struct sockaddr *);
	*msa = *asa;
E 37
	m->m_act = (struct mbuf *)1;
E 40
I 37
D 63
	*mtod(m, struct sockaddr *) = *asa;
D 40
	if (rights0 == 0 || rights0->m_len == 0) {
		rights = m_get(M_DONTWAIT, MT_SONAME);
		if (rights)
			rights->m_len = 0;
E 40
I 40
	m->m_len = sizeof (*asa);
E 63
I 63
D 67
	if (asa->sa_len > MLEN) {
		(void) m_free(m);
		return (0);
	}
E 67
	m->m_len = asa->sa_len;
	bcopy((caddr_t)asa, mtod(m, caddr_t), asa->sa_len);
E 63
I 50
D 52
	sballoc(sb, m);
E 52
E 50
D 51
	if (rights0) {
E 51
I 51
D 67
	if (rights0 && rights0->m_len) {
E 51
D 50
		m->m_act = m_copy(rights0, 0, rights0->m_len);
		if (m->m_act == 0) {
E 50
I 50
		m->m_next = m_copy(rights0, 0, rights0->m_len);
		if (m->m_next == 0) {
E 50
			m_freem(m);
			return (0);
		}
D 47
		sballoc(sb, m);
E 47
D 50
		sballoc(sb, m->m_act);
E 50
I 50
		sballoc(sb, m->m_next);
E 50
E 40
D 47
	} else
D 40
		rights = m_copy(rights0, 0, rights0->m_len);
	if (rights == 0) {
		m_freem(m);
E 40
I 40
		sballoc(sb, m);
E 47
I 47
	}
I 52
	sballoc(sb, m);
E 67
I 67
	if (n)
		n->m_next = m0;		/* concatenate data to control */
	else
		control = m0;
	m->m_next = control;
D 74
	for (n = m; n; n = n->m_next)
E 74
I 74
	for (n = m; n; n = n->m_next) {
		eor |= n->m_flags & M_EOR;
E 74
		sballoc(sb, n);
I 74
	}
	m->m_flags |= eor;
E 74
E 67
E 52
D 50
	sballoc(sb, m);
E 50
E 47
	if (n = sb->sb_mb) {
D 61
		while (n->m_act)
			n = n->m_act;
		n->m_act = m;
E 61
I 61
		while (n->m_nextpkt)
			n = n->m_nextpkt;
		n->m_nextpkt = m;
E 61
	} else
		sb->sb_mb = m;
D 50
	if (m->m_act)
		m = m->m_act;
	sballoc(sb, m0);
	m->m_act = m0;
	m = m0->m_next;
	m0->m_next = 0;
D 47
	sbcompress(sb, m, m0);
E 47
I 47
	if (m)
		sbcompress(sb, m, m0);
E 50
I 50
D 67
	if (m->m_next)
		m = m->m_next;
	if (m0)
		sbcompress(sb, m0, m);
E 67
E 50
E 47
	return (1);
}

I 78
int
E 78
D 50
#ifdef notdef
sbappendrights(sb, rights, m0)
E 50
I 50
D 67
sbappendrights(sb, m0, rights)
E 67
I 67
sbappendcontrol(sb, m0, control)
E 67
E 50
	struct sockbuf *sb;
D 50
	struct mbuf *rights, *m;
E 50
I 50
D 67
	struct mbuf *rights, *m0;
E 67
I 67
D 78
	struct mbuf *control, *m0;
E 78
I 78
	struct mbuf *m0, *control;
E 78
E 67
E 50
{
	register struct mbuf *m, *n;
D 74
	int space = 0;
E 74
I 74
	int space = 0, eor = 0;
E 74

D 50
	m = m0;
	if (m == 0 || rights == 0)
E 50
I 50
D 67
	if (rights == 0)
E 50
		panic("sbappendrights");
E 67
I 67
	if (control == 0)
		panic("sbappendcontrol");
	for (m = control; ; m = m->m_next) {
		space += m->m_len;
		if (m->m_next == 0)
			break;
	}
	n = m;			/* save pointer to last control buffer */
E 67
D 50
	do {
E 50
I 50
	for (m = m0; m; m = m->m_next)
E 50
		space += m->m_len;
D 50
		m = m->m_next;
	} while (m);
E 50
D 67
	space += rights->m_len;
E 67
	if (space > sbspace(sb))
E 40
		return (0);
D 40
	}
	rights->m_act = (struct mbuf *)1;
	m->m_next = rights;
	rights->m_next = m0;
E 37
	sbappend(sb, m);
E 40
I 40
D 67
	m = m_copy(rights, 0, rights->m_len);
	if (m == 0)
		return (0);
	sballoc(sb, m);
E 67
I 67
	n->m_next = m0;			/* concatenate data to control */
D 74
	for (m = control; m; m = m->m_next)
E 74
I 74
	for (m = control; m; m = m->m_next) {
		eor |= m->m_flags & M_EOR;
E 74
		sballoc(sb, m);
I 74
	}
	control->m_flags |= eor;
E 74
E 67
	if (n = sb->sb_mb) {
D 61
		while (n->m_act)
			n = n->m_act;
		n->m_act = m;
E 61
I 61
		while (n->m_nextpkt)
			n = n->m_nextpkt;
D 67
		n->m_nextpkt = m;
E 67
I 67
		n->m_nextpkt = control;
E 67
E 61
	} else
D 50
		n->m_act = m;
	sballoc(sb, m0);
	m->m_act = m0;
	m = m0->m_next;
	m0->m_next = 0;
D 47
	sbcompress(sb, m, m0);
E 47
I 47
	if (m)
		sbcompress(sb, m, m0);
E 50
I 50
D 67
		sb->sb_mb = m;
	if (m0)
		sbcompress(sb, m0, m);
E 67
I 67
		sb->sb_mb = control;
E 67
E 50
E 47
E 40
D 8
	m0->m_act = (struct mbuf *)1;
E 8
D 37
	sbappend(sb, m0);
E 37
I 29
D 33
SBCHECK(sb, "sbappendaddr end");
E 33
E 29
I 8
D 9
	printf("inserted: sb_cc now %d\n", sb->sb_cc);
E 9
E 8
	return (1);
I 29
}
I 40
D 50
#endif
E 50
E 40

I 33
D 37
#ifdef notdef
E 33
SBCHECK(sb, str)
	struct sockbuf *sb;
	char *str;
{
	register int cnt = sb->sb_cc;
	register int mbcnt = sb->sb_mbcnt;
	register struct mbuf *m;

	for (m = sb->sb_mb; m; m = m->m_next) {
		cnt -= m->m_len;
		mbcnt -= MSIZE;
		if (m->m_off > MMAXOFF)
			mbcnt -= CLBYTES;
	}
	if (cnt || mbcnt) {
		printf("cnt %d mbcnt %d\n", cnt, mbcnt);
		panic(str);
	}
E 29
}
I 33
#endif
E 33

E 37
E 3
/*
D 40
 * Free all mbufs on a sockbuf mbuf chain.
 * Check that resource allocations return to 0.
E 40
I 40
 * Compress mbuf chain m into the socket
 * buffer sb following mbuf n.  If n
 * is null, the buffer is presumed empty.
E 40
 */
I 78
void
E 78
I 40
D 74
sbcompress(sb, m, n)
E 74
I 74
sbcompress(sb, m, n0)
E 74
	register struct sockbuf *sb;
D 74
	register struct mbuf *m, *n;
E 74
I 74
	register struct mbuf *m;
	struct mbuf *n0;
E 74
{
I 74
	register struct mbuf *n = n0;
E 74
D 67

E 67
I 63
	register int eor = 0;
I 71
D 74
	register struct mbuf *o;
E 74
E 71
I 67

I 74
	if (n) {
		if (n->m_flags & M_EOR)
			n = 0;
		else while (n->m_next)
			n = n->m_next;
	}
E 74
E 67
E 63
	while (m) {
I 63
		eor |= m->m_flags & M_EOR;
E 63
D 71
		if (m->m_len == 0) {
E 71
I 71
D 74
		if (m->m_len == 0 &&
		    (eor == 0 ||
		     (((o = m->m_next) || (o = n)) &&
		      o->m_type == m->m_type))) {
E 71
			m = m_free(m);
			continue;
E 74
I 74
		if (m->m_len == 0) {
			if (eor == 0 || m->m_next || n) {
				m = m_free(m);
				continue;
			}
E 74
		}
D 61
		if (n && n->m_off <= MMAXOFF && m->m_off <= MMAXOFF &&
D 50
		    (n->m_off + n->m_len + m->m_len) <= MMAXOFF) {
E 50
I 50
		    (n->m_off + n->m_len + m->m_len) <= MMAXOFF &&
E 61
I 61
D 63
		if (n && (n->m_flags & M_EXT) == 0 &&
E 63
I 63
D 74
		if (n && (n->m_flags & (M_EXT | M_EOR)) == 0 &&
E 74
I 74
		if (n && (n->m_flags & M_EXT) == 0 &&
E 74
E 63
		    (n->m_data + n->m_len + m->m_len) < &n->m_dat[MLEN] &&
E 61
		    n->m_type == m->m_type) {
E 50
			bcopy(mtod(m, caddr_t), mtod(n, caddr_t) + n->m_len,
			    (unsigned)m->m_len);
			n->m_len += m->m_len;
			sb->sb_cc += m->m_len;
			m = m_free(m);
			continue;
		}
D 63
		sballoc(sb, m);
E 63
D 74
		if (n)
E 74
I 74
		if (n == 0) {
			if (n0)
				n0->m_nextpkt = m;
			else
				sb->sb_mb = m;
			n0 = m;
		} else
E 74
			n->m_next = m;
D 74
		else
			sb->sb_mb = m;
E 74
I 63
		sballoc(sb, m);
E 63
		n = m;
I 63
D 74
		m->m_flags &= ~M_EOR;
E 74
I 74
		/*m->m_flags &= ~M_EOR;*/
E 74
E 63
		m = m->m_next;
		n->m_next = 0;
	}
I 63
D 71
	if (n)
		n->m_flags |= eor;
E 71
I 71
	if (eor) {
D 74
		if (n)
			n->m_flags |= eor;
E 74
I 74
		if (n0)
			n0->m_flags |= eor;
E 74
		else
D 74
			printf("semi-panic: sbcompress\n");
E 74
I 74
			panic("sbcompress");
E 74
	}
E 71
E 63
}

/*
 * Free all mbufs in a sockbuf.
 * Check that all resources are reclaimed.
 */
I 78
void
E 78
E 40
sbflush(sb)
D 37
	struct sockbuf *sb;
E 37
I 37
	register struct sockbuf *sb;
E 37
{

	if (sb->sb_flags & SB_LOCK)
		panic("sbflush");
D 16
	sbdrop(sb, sb->sb_cc);
E 16
I 16
D 53
	if (sb->sb_cc)
E 53
I 53
	while (sb->sb_mbcnt)
E 53
D 54
		sbdrop(sb, sb->sb_cc);
E 54
I 54
		sbdrop(sb, (int)sb->sb_cc);
E 54
E 16
D 67
	if (sb->sb_cc || sb->sb_mbcnt || sb->sb_mb)
E 67
I 67
	if (sb->sb_cc || sb->sb_mb)
E 67
		panic("sbflush 2");
}

/*
D 40
 * Drop data from (the front of) a sockbuf chain.
E 40
I 40
 * Drop data from (the front of) a sockbuf.
E 40
 */
I 78
void
E 78
I 40
D 54
struct mbuf *
E 54
E 40
sbdrop(sb, len)
	register struct sockbuf *sb;
	register int len;
{
D 40
	register struct mbuf *m = sb->sb_mb, *mn;
E 40
I 40
	register struct mbuf *m, *mn;
	struct mbuf *next;
E 40

I 40
D 61
	next = (m = sb->sb_mb) ? m->m_act : 0;
E 61
I 61
	next = (m = sb->sb_mb) ? m->m_nextpkt : 0;
E 61
E 40
	while (len > 0) {
D 40
		if (m == 0)
			panic("sbdrop");
E 40
I 40
		if (m == 0) {
			if (next == 0)
				panic("sbdrop");
			m = next;
D 61
			next = m->m_act;
E 61
I 61
			next = m->m_nextpkt;
E 61
			continue;
		}
E 40
D 10
		if (m->m_len <= len) {
			len -= m->m_len;
			sbfree(sb, m);
			MFREE(m, mn);
			m = mn;
		} else {
E 10
I 10
		if (m->m_len > len) {
E 10
			m->m_len -= len;
D 61
			m->m_off += len;
E 61
I 61
			m->m_data += len;
E 61
			sb->sb_cc -= len;
			break;
		}
I 10
		len -= m->m_len;
		sbfree(sb, m);
		MFREE(m, mn);
		m = mn;
E 10
	}
I 42
	while (m && m->m_len == 0) {
I 45
		sbfree(sb, m);
E 45
		MFREE(m, mn);
		m = mn;
	}
E 42
D 40
	sb->sb_mb = m;
E 40
I 40
	if (m) {
		sb->sb_mb = m;
D 61
		m->m_act = next;
E 61
I 61
		m->m_nextpkt = next;
E 61
	} else
		sb->sb_mb = next;
D 54
	return (sb->sb_mb);
E 54
}

/*
 * Drop a record off the front of a sockbuf
 * and move the next record to the front.
 */
I 78
void
E 78
D 54
struct mbuf *
E 54
sbdroprecord(sb)
	register struct sockbuf *sb;
{
	register struct mbuf *m, *mn;

	m = sb->sb_mb;
	if (m) {
D 61
		sb->sb_mb = m->m_act;
E 61
I 61
		sb->sb_mb = m->m_nextpkt;
E 61
		do {
			sbfree(sb, m);
			MFREE(m, mn);
		} while (m = mn);
	}
D 54
	return (sb->sb_mb);
E 54
E 40
I 8
D 9
	nullchk("sbdrop", sb->sb_mb);
E 9
E 8
D 3
}

struct mbuf *
D 2
sb_copy(sb, off, len)
E 2
I 2
sbcopy(sb, off, len)
E 2
	struct sockbuf *sb;
	int off;
	register int len;
{
	register struct mbuf *m, *n, **np;
	struct mbuf *top, *p;
COUNT(SB_COPY);

	if (len == 0)
		return (0);
	if (off < 0 || len < 0)
		panic("sb_copy");
	m = sb->sb_mb;
	while (off > 0) {
		if (m == 0)
			panic("sb_copy");
		if (off < m->m_len)
			break;
		off -= m->m_len;
		m = m->m_next;
	}
	np = &top;
	top = 0;
	while (len > 0) {
		MGET(n, 1);
		*np = n;
		if (n == 0)
			goto nospace;
		if (m == 0)
			panic("sb_copy");
		n->m_len = MIN(len, m->m_len - off);
		if (m->m_off > MMAXOFF) {
			p = mtod(m, struct mbuf *);
			n->m_off = ((int)p - (int)n) + off;
			mprefcnt[mtopf(p)]++;
		} else {
			n->m_off = MMINOFF;
			bcopy(mtod(m, caddr_t)+off, mtod(n, caddr_t),
D 2
			    n->m_len);
E 2
I 2
			    (unsigned)n->m_len);
E 2
		}
		len -= n->m_len;
		off = 0;
		m = m->m_next;
		np = &n->m_next;
	}
	return (top);
nospace:
	printf("snd_copy: no space\n");
	m_freem(top);
	return (0);
E 3
}
I 16
D 22

/*
printm(m)
	struct mbuf *m;
{

	printf("<");
	while (m) {
		printf("%d,", m->m_len);
		m = m->m_next;
	}
	printf(">");
	printf("\n");
}
*/
E 22
E 16
E 1
