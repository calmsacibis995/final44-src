h36172
s 00339/00291/00898
d D 8.6 95/02/14 10:45:58 cgd 104 103
c new argument passing conventions.  minor type size cleanup.
e
s 00004/00006/01185
d D 8.5 94/07/07 17:48:35 mckusick 103 101
c since size_t is unsigned must check for overflow incrementally (from karels)
e
s 00000/00004/01187
d R 8.5 94/06/04 17:04:27 mckusick 102 101
c since size_t is unsigned, testing iov_len < 0 is futile
e
s 00002/00002/01189
d D 8.4 94/02/21 09:39:09 bostic 101 100
c change struct recvfrom_args and struct sendto_args to take a size_t
c as a length parameter
e
s 00000/00001/01191
d D 8.3 94/01/04 18:43:36 bostic 100 99
c lint
e
s 00002/00002/01190
d D 8.2 93/08/10 16:07:32 mckusick 99 98
c avoid mbuf leak
e
s 00002/00002/01190
d D 8.1 93/06/10 22:00:00 bostic 98 97
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/01190
d D 7.29 93/02/27 23:16:35 mckusick 97 96
c fix bugs in sending messages through sockets (4.4BSD-alpha/sys/6)
e
s 00011/00011/01180
d D 7.28 92/10/11 10:38:56 bostic 96 95
c make kernel includes standard
e
s 00148/00160/01043
d D 7.27 92/07/10 21:12:12 torek 95 94
c ANSIfy syscall args, and share args across compat calls
e
s 00008/00006/01195
d D 7.26 92/05/20 19:02:49 bostic 94 93
c don't use free'd mbuf pointer; bug report net2/sys/10
e
s 00028/00025/01173
d D 7.25 92/02/14 17:47:24 torek 93 92
c compatibility for COMPAT_SUNOS
e
s 00005/00008/01193
d D 7.24 91/06/03 20:26:58 mckusick 92 91
c call ffree to free file structures
e
s 00008/00007/01193
d D 7.23 91/04/20 16:16:29 karels 91 90
c rm user.h, OFILE*
e
s 00001/00001/01199
d D 7.22 91/03/17 15:41:49 karels 90 89
c more-or-less working with new proc & user structs
e
s 00062/00079/01138
d D 7.21 91/01/10 23:43:59 mckusick 89 88
c add dynamically allocated file descriptors
e
s 00002/00002/01215
d D 7.20 90/06/30 14:12:23 karels 88 87
c unbalanced parens if !COMPAT_43
e
s 00001/00011/01216
d D 7.19 90/06/28 21:24:40 bostic 87 86
c new copyright notice
e
s 00070/00071/01157
d D 7.18 90/06/28 17:11:29 karels 86 85
c RETURN => return, remove syscontext.h
e
s 00002/00002/01226
d D 7.17 90/06/22 17:18:36 mckusick 85 83
c have to pass error to ktrace
e
s 00001/00001/01227
d R 7.17 90/06/05 22:02:17 mckusick 84 83
c update to new system call convention; expunge more u.u_error
e
s 00235/00159/00993
d D 7.16 90/06/05 11:59:50 mckusick 83 82
c update for new system call convention
e
s 00112/00031/01040
d D 7.15 90/06/05 10:12:33 marc 82 81
c support large iov's.  ktrace socket i/o.
e
s 00100/00129/00971
d D 7.14 90/04/16 09:47:39 karels 81 80
c misc cleanups: rights now in control mbufs; control mbufs now
c passed down, not freed here; check copyout return vals
e
s 00339/00293/00761
d D 7.13 90/04/03 21:14:01 karels 80 79
c remove u.u_error; fixes in previous delta; rearrange compat code
c so tags/vi/*grind recognize functions
e
s 00104/00108/00950
d D 7.12 90/04/03 21:09:03 karels 79 78
c new tsleep, catching interrupts; access rights now in control fields;
c start changing refs to u.u_error to use locals and RETURN; pipes now bidirectional
e
s 00022/00012/01036
d D 7.11 90/04/03 21:05:45 karels 78 77
c as of Feb 23: tsleep; confirming sockets; hack for reduced max size
c of unix-domain sockaddrs
e
s 00007/00004/01041
d D 7.10 89/05/09 17:03:05 mckusick 77 76
c merge in vnodes
e
s 00004/00021/01041
d D 7.9 89/05/02 16:19:56 mckusick 76 74
i 75
c integrate back branch -r7.2.1.1
e
s 00042/00032/00798
d D 7.2.1.1 89/05/02 16:08:45 mckusick 75 68
c merge in vnode changes
e
s 00015/00014/01035
d D 7.8 89/04/22 12:26:45 sklower 74 73
c checkpoint for version to be handed to NIST, simple tp4 connection
e
s 00104/00042/00945
d D 7.7 89/04/08 17:50:24 karels 73 72
c compat: move/swab sa_family for oaccept (XXX)
e
s 00180/00034/00807
d D 7.6 88/10/12 14:59:35 karels 72 71
c mark semi working version before var length sockaddrs (by sklower)
e
s 00010/00005/00831
d D 7.5 88/06/29 17:18:16 bostic 71 70
c install approved copyright notice
e
s 00001/00001/00835
d D 7.4 88/01/20 15:32:01 bostic 70 69
c check all values of namelen against MLEN
e
s 00008/00002/00828
d D 7.3 88/01/07 13:29:08 bostic 69 68
c add Berkeley header
e
s 00000/00004/00830
d D 7.2 87/07/29 17:31:42 mckusick 68 67
c delete unneeded header files
e
s 00001/00001/00833
d D 7.1 86/06/05 00:17:34 mckusick 67 66
c 4.3BSD release version
e
s 00007/00001/00827
d D 6.17 86/05/19 16:39:13 karels 66 65
c make errors on non-blocking connect agree with doc
e
s 00005/00005/00823
d D 6.16 86/05/10 22:54:50 karels 65 64
c don't retry connect (or disconnect) if still in progress
e
s 00004/00004/00824
d D 6.15 86/02/23 23:12:53 karels 64 63
c lint
e
s 00001/00001/00827
d D 6.14 86/02/20 16:04:04 karels 63 62
c remove unused sonam arg to unp_connect2
e
s 00002/00009/00826
d D 6.13 85/12/09 15:48:32 karels 62 61
c logic errors
e
s 00005/00009/00830
d D 6.12 85/11/08 19:05:35 karels 61 60
c correct previous fix to failed connect; let's really free those
c sockets after failed socketpair/pipe
e
s 00001/00000/00838
d D 6.11 85/10/30 18:07:01 karels 60 59
c unsuccessful attempt to connect leaves socket disconnect{ed,ing}
e
s 00001/00000/00837
d D 6.10 85/09/16 20:48:17 karels 59 58
c only report errors on listening socket once
e
s 00007/00001/00830
d D 6.9 85/06/08 15:06:43 mckusick 58 57
c Add copyright
e
s 00008/00007/00823
d D 6.8 85/06/02 23:24:25 karels 57 56
c rights must be MT_RIGHTS (confuses soreceive otherwise!)
e
s 00003/00001/00827
d D 6.7 85/05/27 20:02:53 karels 56 55
c pipe usese connect2 now
e
s 00009/00000/00819
d D 6.6 84/11/27 17:08:00 karels 55 54
c socketpair needs to connect datagram sockets both ways, returns 0
e
s 00008/00013/00811
d D 6.5 84/09/04 21:46:17 sam 54 53
c revise socket option interface so options at SOL_SOCKET take value 
c parameter indicating if option is on/off
e
s 00013/00013/00811
d D 6.4 84/08/29 20:28:38 bloom 53 52
c Change to includes.  no more ../h
e
s 00002/00002/00822
d D 6.3 84/07/08 22:30:40 mckusick 52 51
c use proper definition of UIO flags
e
s 00004/00000/00820
d D 6.2 83/09/25 17:32:38 karels 51 50
c sendit and recvit skip over 0-length vectors
e
s 00000/00000/00820
d D 6.1 83/07/29 06:49:05 sam 50 49
c 4.2 distribution
e
s 00044/00000/00776
d D 4.48 83/07/25 21:53:36 sam 49 48
c getpeer
e
s 00052/00001/00724
d D 4.47 83/06/14 20:40:35 sam 48 47
c socketpair
e
s 00276/00188/00449
d D 4.46 83/05/27 12:51:09 sam 47 46
c merge of bill's code plus lint (plus, of course, cleanup of bill's bugs)
e
s 00007/00001/00630
d D 4.45 83/03/23 15:02:51 sam 46 45
c if M_WAIT worked, these wouldn't be needed
e
s 00015/00007/00616
d D 4.44 83/03/19 14:10:24 sam 45 44
c replace socketaddr with getsockname
e
s 00001/00002/00622
d D 4.43 83/03/04 16:16:39 sam 44 43
c freeing free mbuf
e
s 00036/00031/00588
d D 4.42 83/01/13 19:02:38 sam 43 42
c allow nil pointers for option values
e
s 00096/00095/00523
d D 4.41 83/01/13 18:35:25 sam 42 41
c mv socket options into set and get socket options sys calls
e
s 00032/00003/00586
d D 4.40 83/01/08 20:53:43 sam 41 40
c fill out shutdown stub; add socket option consistency checking
e
s 00027/00024/00562
d D 4.39 82/12/28 23:48:08 sam 40 39
c copyin & copyout now return EFAULT and all callers uniformly 
c return (or ignore) this value
e
s 00004/00004/00582
d D 4.38 82/12/14 17:09:54 sam 39 38
c typed mbufs
e
s 00003/00001/00583
d D 4.37 82/11/15 01:13:06 sam 38 37
c treat domain as AF_*; return residuals on send and sendto
e
s 00005/00003/00579
d D 4.36 82/11/13 22:51:23 sam 37 36
c merge of 4.1b and 4.1c
e
s 00004/00004/00578
d D 4.35 82/10/21 20:58:21 root 36 35
c lint
e
s 00001/00001/00581
d D 4.34 82/10/20 02:41:31 root 35 34
c lint
e
s 00001/00001/00581
d D 4.33 82/10/20 01:09:54 root 34 33
c lint
e
s 00019/00017/00563
d D 4.32 82/10/17 21:50:00 root 33 32
c more lint
e
s 00000/00001/00580
d D 4.31 82/10/17 14:05:00 root 32 31
c fix lint
e
s 00000/00002/00581
d D 4.30 82/10/09 05:38:16 wnj 31 30
c fix up header file dependencies 
e
s 00006/00008/00577
d D 4.29 82/10/05 21:57:36 root 30 29
c send(... SOF_OOB) and receive(... SOF_PREVIEW)
e
s 00004/00004/00581
d D 4.28 82/10/05 10:30:06 root 29 27
c bug in sockopt() error handling in accept
e
s 00388/00216/00197
d R 4.28 82/10/03 23:47:07 root 28 27
c minor bug
e
s 00386/00214/00199
d D 4.27 82/10/03 23:39:09 root 27 26
c overhaul
e
s 00001/00009/00412
d D 4.26 82/09/06 22:54:34 root 26 25
c  
e
s 00024/00032/00397
d D 4.25 82/09/04 09:18:58 root 25 24
c ipc call skeletons
e
s 00025/00006/00404
d D 4.24 82/08/22 20:39:41 root 24 23
c uio'ing
e
s 00011/00004/00399
d D 4.23 82/08/14 18:54:39 root 23 22
c no more readi()
e
s 00001/00001/00402
d D 4.22 82/08/08 18:12:22 sam 22 21
c bug fix for invalid parameters
e
s 00109/00017/00294
d D 4.21 82/07/24 18:11:06 root 21 20
c merge with calder
e
s 00000/00007/00311
d D 4.20 82/06/20 12:21:32 sam 20 19
c purge COUNT crap now that we have gprof
e
s 00001/00001/00317
d D 4.19 82/06/14 22:16:48 wnj 19 18
c get rid of m_release stuff
e
s 00006/00001/00312
d D 4.18 82/06/12 23:09:53 wnj 18 17
c fix to race in accept
e
s 00008/00004/00305
d D 4.17 82/04/10 23:43:24 sam 17 16
c redo socketaddr system call
e
s 00000/00084/00309
d D 4.16 82/03/19 14:22:02 sam 16 15
c purge extraneous stuff
e
s 00003/00003/00390
d D 4.15 82/03/15 04:47:05 wnj 15 14
c shutdown; clear suid; get/set hostname; nbio in state not options fixes
e
s 00006/00001/00387
d D 4.14 82/02/25 12:49:29 wnj 14 13
c race in accept
e
s 00003/00003/00385
d D 4.13 82/01/13 10:31:33 root 13 12
c spelling changes
e
s 00004/00000/00384
d D 4.12 81/12/20 15:24:41 root 12 11
c sleep for connection in accept; return address in accept
e
s 00004/00000/00380
d D 4.11 81/12/09 20:52:08 wnj 11 10
c set u.u_base
e
s 00002/00002/00378
d D 4.10 81/12/02 17:26:14 wnj 10 9
c more cleanup
e
s 00002/00002/00378
d D 4.9 81/11/26 11:57:23 wnj 9 8
c before carry to arpavax
e
s 00001/00001/00379
d D 4.8 81/11/21 15:12:44 wnj 8 7
c args to piconnect backwards
e
s 00006/00001/00374
d D 4.7 81/11/20 14:42:54 wnj 7 6
c more lint
e
s 00021/00000/00354
d D 4.6 81/11/20 01:19:22 wnj 6 5
c ssocketaddr
e
s 00002/00002/00352
d D 4.5 81/11/20 00:45:49 wnj 5 4
c linted
e
s 00095/00036/00259
d D 4.4 81/11/18 15:44:50 wnj 4 3
c more cleanup
e
s 00011/00137/00284
d D 4.3 81/11/16 14:20:30 wnj 3 2
c lint
e
s 00153/00109/00268
d D 4.2 81/11/14 16:42:55 wnj 2 1
c before header overlay
e
s 00377/00000/00000
d D 4.1 81/11/10 16:03:21 wnj 1 0
c date and time created 81/11/10 16:03:21 by wnj
e
u
U
f b 
t
T
I 1
D 58
/*	%M%	%I%	%E%	*/
E 58
I 58
/*
D 67
 * Copyright (c) 1982 Regents of the University of California.
E 67
I 67
D 72
D 75
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 72
I 72
 * Copyright (c) 1982, 1986, 1988 The Regents of the University of California.
E 72
E 67
D 69
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 75
I 75
D 80
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 80
I 80
D 98
 * Copyright (c) 1982, 1986, 1989, 1990 Regents of the University of California.
E 80
 * All rights reserved.
E 98
I 98
 * Copyright (c) 1982, 1986, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 98
E 75
E 69
I 69
D 76
 * All rights reserved.
E 76
 *
D 87
 * Redistribution and use in source and binary forms are permitted
D 71
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 71
I 71
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
E 87
I 87
 * %sccs.include.redist.c%
E 87
E 71
E 69
 *
I 75
D 76
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
 *
E 76
E 75
 *	%W% (Berkeley) %G%
 */
E 58

D 53
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/proc.h"
#include "../h/file.h"
#include "../h/inode.h"
#include "../h/buf.h"
#include "../h/mbuf.h"
D 4
#include "../h/protocol.h"
E 4
#include "../h/protosw.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
D 4
#include "../h/inaddr.h"
E 4
D 9
#include "../net/inet.h"
#include "../net/inet_systm.h"
E 9
I 9
D 31
#include "../net/in.h"
#include "../net/in_systm.h"
E 31
I 21
D 47
#include "../h/descrip.h"
E 47
I 23
#include "../h/uio.h"
E 53
I 53
D 96
#include "param.h"
D 68
#include "systm.h"
E 68
D 77
#include "dir.h"
E 77
D 79
#include "user.h"
E 79
I 79
D 86
/* #include "user.h" */
#include "syscontext.h" /* XXX */
E 86
I 86
D 91
#include "user.h"
E 91
I 89
#include "filedesc.h"
E 89
E 86
E 79
I 72
#include "proc.h"
E 72
D 68
#include "proc.h"
E 68
#include "file.h"
D 68
#include "inode.h"
E 68
#include "buf.h"
I 72
#include "malloc.h"
E 72
#include "mbuf.h"
#include "protosw.h"
#include "socket.h"
#include "socketvar.h"
E 96
I 96
#include <sys/param.h>
I 104
#include <sys/systm.h>
E 104
#include <sys/filedesc.h>
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/buf.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
E 96
I 82
#ifdef KTRACE
D 96
#include "ktrace.h"
E 96
I 96
#include <sys/ktrace.h>
E 96
#endif
E 82
I 78
D 79
#include "tsleep.h"
E 79
E 78
D 68
#include "uio.h"
E 68
E 53
E 23
E 21
E 9

I 104
#include <sys/mount.h>
#include <sys/syscallargs.h>

E 104
I 21
D 25
ssocreate()
I 24
/*###21 [lint] ssocreate defined( sys_socket.c(21) ), but never used%%%*/
E 25
I 25
D 27
socket()
E 25
E 24
{

}

D 25
ssobind()
I 24
/*###26 [lint] ssobind defined( sys_socket.c(26) ), but never used%%%*/
E 25
I 25
bind()
E 25
E 24
{

}

D 25
ssolisten()
I 24
/*###31 [lint] ssolisten defined( sys_socket.c(31) ), but never used%%%*/
E 25
I 25
listen()
E 25
E 24
{

}

D 25
ssoaccept()
I 24
/*###36 [lint] ssoaccept defined( sys_socket.c(36) ), but never used%%%*/
E 25
I 25
accept()
E 25
E 24
{

}

D 25
ssoconnect()
I 24
/*###41 [lint] ssoconnect defined( sys_socket.c(41) ), but never used%%%*/
E 25
I 25
connect()
E 25
E 24
{

}

D 25
ssocreatepair()
I 24
/*###46 [lint] ssocreatepair defined( sys_socket.c(46) ), but never used%%%*/
E 25
I 25
socketpair()
E 25
E 24
{

}

D 25
ssosendto()
I 24
/*###51 [lint] ssosendto defined( sys_socket.c(51) ), but never used%%%*/
E 25
I 25
D 26
spipe()
E 25
E 24
{

}

E 26
D 25
ssosend()
I 24
/*###56 [lint] ssosend defined( sys_socket.c(56) ), but never used%%%*/
E 25
I 25
sendto()
E 25
E 24
{

}

D 25
ssorecvfrom()
I 24
/*###61 [lint] ssorecvfrom defined( sys_socket.c(61) ), but never used%%%*/
E 25
I 25
send()
E 25
E 24
{

}

D 25
ssorecv()
I 24
/*###66 [lint] ssorecv defined( sys_socket.c(66) ), but never used%%%*/
E 25
I 25
recvfrom()
E 25
E 24
{

}

D 25
ssosendm()
I 24
/*###71 [lint] ssosendm defined( sys_socket.c(71) ), but never used%%%*/
E 25
I 25
recv()
E 25
E 24
{

}

D 25
ssorecvm()
I 24
/*###76 [lint] ssorecvm defined( sys_socket.c(76) ), but never used%%%*/
E 25
I 25
sendmsg()
E 25
E 24
{

}

D 25
ssoshutdown()
I 24
/*###81 [lint] ssoshutdown defined( sys_socket.c(81) ), but never used%%%*/
E 25
I 25
recvmsg()
E 25
E 24
{

}

I 25
shutdown()
{

}

E 27
E 25
E 21
/*
D 27
 * Socket system call interface.
 *
 * These routines interface the socket routines to UNIX,
 * isolating the system interface from the socket-protocol interface.
 *
D 2
 * DO SPLICE STUFF
 * DO PIPE STUFF
 * DO PORTALS
 * DO ASSOCIATIONS
 * DO NEWFD STUFF
E 2
I 2
 * TODO:
D 4
 *	SO_NEWFDONCONN
E 4
 *	SO_INTNOTIFY
E 27
I 27
 * System call interface to the socket abstraction.
E 27
E 2
 */
I 93
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
#define COMPAT_OLDSOCK
#endif
E 93

I 47
D 89
struct	file *getsock();
E 89
extern	struct fileops socketops;

I 95
D 104
struct socket_args {
	int	domain;
	int	type;
	int	protocol;
};
E 104
I 104
int
E 104
E 95
E 47
I 2
D 4
static	struct in_addr localaddr = { PF_LOCAL };
E 4
I 4
D 10
static	struct sockproto localproto = { PF_LOCAL, 0 };
E 10
I 10
D 27
static	struct sockproto localproto = { PF_UNIX, 0 };
E 10
E 4
E 2
D 26
/*
D 2
 * Socket system call interface.  Copy in arguments
 * set up file descriptor and call internal socket
 * creation routine.
E 2
I 2
 * Pipe system call interface.
E 2
 */
D 2
ssocket()
E 2
I 2
D 25
spipe()
E 25
I 25
opipe()
E 26
I 26
pipe()
E 27
I 27
D 83
socket()
E 27
E 26
E 25
E 2
{
D 2
	register struct a {
		int	type;
		struct	in_addr *ain;
		int	options;
	} *uap = (struct a *)u.u_ap;
	struct in_addr in;
	struct socket *so0;
	register struct socket *so;
	register struct file *fp;

	if ((fp = falloc()) == NULL)
E 2
I 2
D 27
	register struct file *rf, *wf;
	struct socket *rso, *wso;
	int r;
I 4
D 20
COUNT(SPIPE);
E 20
E 4
D 3
	struct in_addr waddr;
E 3
	
D 4
	u.u_error = socket(&rso, SOCK_STREAM, &localaddr, SO_ACCEPTCONN);
E 4
I 4
	u.u_error = socreate(&rso, SOCK_STREAM,
	    &localproto, (struct sockaddr *)0, 0);
E 4
	if (u.u_error)
E 2
		return;
D 2
	fp->f_flag = FSOCKET|FREAD|FWRITE;
	if (copyin((caddr_t)uap->ain, &in, sizeof (in))) {
		u.u_error = EFAULT;
		return;
	}
	u.u_error = socket(&so0, uap->type, &in, uap->options);
E 2
I 2
D 4
	u.u_error = socket(&wso, SOCK_STREAM, &localaddr, 0);
E 4
I 4
	u.u_error = socreate(&wso, SOCK_STREAM,
	    &localproto, (struct sockaddr *)0, 0);
E 4
E 2
	if (u.u_error)
D 2
		goto bad;
	fp->f_socket = so;
E 2
I 2
		goto free;
	rf = falloc();
	if (rf == NULL)
		goto free2;
	r = u.u_r.r_val1;
D 21
	rf->f_flag = FREAD|FSOCKET;
E 21
I 21
	rf->f_flag = FREAD;
	rf->f_type = DTYPE_SOCKET;
E 21
	rf->f_socket = rso;
	wf = falloc();
	if (wf == NULL)
		goto free3;
D 21
	wf->f_flag = FWRITE|FSOCKET;
E 21
I 21
	wf->f_flag = FWRITE;
	wf->f_type = DTYPE_SOCKET;
E 21
	wf->f_socket = wso;
	u.u_r.r_val2 = u.u_r.r_val1;
	u.u_r.r_val1 = r;
D 4
	if (pi_connect(rso, wso) == 0)
E 4
I 4
D 8
	if (piconnect(rso, wso) == 0)
E 8
I 8
	if (piconnect(wso, rso) == 0)
E 8
E 4
		goto free4;
I 4
D 5
	rso->so_isfilerefd = wso->so_isfilerefd = 1;
E 5
E 4
E 2
	return;
D 2
bad:
E 2
I 2
free4:
	wf->f_count = 0;
E 2
D 19
	u.u_ofile[u.u_r.r_val1] = 0;
E 19
I 19
	u.u_ofile[u.u_r.r_val2] = 0;
E 19
D 2
	fp->f_count = 0;
E 2
I 2
free3:
	rf->f_count = 0;
	u.u_ofile[r] = 0;
free2:
I 5
D 21
	wso->so_state |= SS_USERGONE;
E 21
I 21
	wso->so_state |= SS_NOFDREF;
E 21
E 5
	sofree(wso);
free:
I 5
D 21
	rso->so_state |= SS_USERGONE;
E 21
I 21
	rso->so_state |= SS_NOFDREF;
E 21
E 5
	sofree(rso);
E 2
}

/*
D 2
 * Pipe system call interface.
 */
spipe()
{

}

static	struct in_addr portalproto = { PF_PORTAL, /* rest don't care */ };
/*
E 2
D 3
 * Portal system call interface.
 *
 * This call creates a portal.
 * All the difficulty here is in dealing with errors.
 * A long sequence of steps is necessary:
 *	1. a socket must be allocated
 *	2. the server name length must be determined
D 2
 *	3. the protal must be entered into the file system
E 2
I 2
 *	3. the portal must be entered into the file system
E 2
 *	4. the portal type and server must be entered into the portals' file
 *	5. a file descriptor referencing the socket+inode must be returned
 * If any errors occur in this process we must back it all out.
 */
sportal()
{
	register struct a {
		caddr_t	name;
		int	mode;
		caddr_t server;
		int	kind;
	} *ap = (struct a *)u.u_ap;
	struct socket *so;
	struct inode *ip;
	struct file *fp;
	int err, len;
	char ch;

	/*
	 * Allocate the socket for the portal.
	 */
D 2
	u.u_error = socket(&so, SOCK_STREAM, &portalproto, SO_NEWFDONCONN);
E 2
I 2
	u.u_error = socket(&so, SOCK_STREAM, &localaddr, SO_NEWFDONCONN);
E 2
	if (u.u_error)
		return;

	/*
	 * Check that server name fis in a file system buffer.
	 * This to simplify the creation of the portal service process.
	 */
	if (ap->server) {
		u.u_dirp = ap->server;
		for (len = 0; len < BSIZE-2; len++) {
			register c = uchar();
			if (c < 0)
				goto bad;
			if (c == 0)
				break;
		}
		if (len == BSIZE - 2) {
			u.u_error = EINVAL;
			goto bad;
		}
	}

	/*
	 * Make sure that nothing with the portal's name exists.
	 */
	u.u_dirp = ap->name;
	ip = namei(uchar, 1);
	if (ip != NULL) {
		iput(ip);
		u.u_error = EEXIST;
	}
	if (u.u_error)
		goto bad;

	/*
	 * Make a node in the file system for the portal.
	 */
	ip = maknode((ap->mode & 0x7777) | IFPORTAL);
	if (ip == NULL)
		goto bad;

	/*
	 * Make the first character of the contents of the
	 * portal be the portal type and the rest of the portal be
	 * the pathname of the server (if one was given).
	 */
	ch = (char)ap->kind;
	u.u_base = (caddr_t)&ch;
	u.u_count = 1;
	u.u_offset = 0;
	u.u_segflg = 1;
	writei(ip);
	if (ap->server) {
		u.u_base = ap->server;
		u.u_count = len;
		u.u_segflg = 0;
		writei(ip);
	}
	if (u.u_error)
		goto bad2;
	
	/*
	 * Allocate a file descriptor and make it reference both
	 * the inode representing the portal and the call director
	 * socket for the portal.
	 */
	fp = falloc();
	if (fp == NULL)
		goto bad2;
D 2
	fp->f_flags = FPORTAL|FSOCKET;
E 2
I 2
	fp->f_flag = FPORTAL|FSOCKET;
E 2
	fp->f_inode = ip;
D 2
	fp->f_socket = s;
E 2
I 2
	fp->f_socket = so;
E 2

	/*
	 * Make the in-core inode reference the socket.
	 */
D 2
	ip->i_socket = s;
	prele(ip);
E 2
I 2
	ip->i_un.i_socket = so;
	irele(ip);
E 2
	return;
bad2:
	err = u.u_error;
	iput(ip);
	u.u_dirp = ap->name;
	unlink();
	u.u_error = err;
bad:
D 2
	sofree(s);
E 2
I 2
	sofree(so);
E 2
}

/*
E 3
D 2
 * Close a socket on last file table reference removal.
 * Initiate disconnect if connected.
 * Free socket when disconnect complete.
E 2
I 2
D 16
 * Splice system call interface.
E 2
 */
D 2
skclose(so)
	register struct socket *so;
E 2
I 2
ssplice()
E 2
{
D 2
	int s = splnet();		/* conservative */
E 2
I 2
	register struct a {
		int	fd1;
		int	fd2;
	} *ap = (struct a *)u.u_ap;
	struct file *f1, *f2;
I 4
COUNT(SSPLICE);
E 4
D 3
	struct socket *pso, *pso2;
E 3
E 2

D 2
	if (so->so_pcb == 0)
		goto discard;
	if (so->so_state & SS_ISCONNECTED) {
		u.u_error = disconnect(so, 0);
		if (u.u_error) {
			splx(s);
			return;
		}
		if ((so->so_state & SS_ISDISCONNECTING) &&
		    (so->so_options & SO_NBIO)) {
			u.u_error = EINPROGRESS;
			splx(s);
			return;
		}
		while (so->so_state & SS_ISCONNECTED)
			sleep((caddr_t)&so->so_timeo, PZERO+1);
E 2
I 2
	f1 = getf(ap->fd1);
	if (f1 == NULL)
		return;
	f2 = getf(ap->fd2);
	if (f2 == NULL)
		return;
I 4
	if (f1 == f2) {
		u.u_error = EINVAL;
		return;
	}
E 4
	if ((f1->f_flag & FSOCKET) == 0 || (f2->f_flag & FSOCKET) == 0) {
		u.u_error = ENOTSOCK;
		return;
E 2
	}
D 2
	u.u_error = (*so->so_proto->pr_usrreq)(so, PRU_DETACH, 0, 0);
discard:
	sofree(so);
	splx(s);
E 2
I 2
	if (f1->f_count > 1 || f2->f_count > 1) {
		u.u_error = ETOOMANYREFS;
		return;
	}
D 4
	u.u_error = pi_splice(f1->f_socket, f2->f_socket);
E 4
I 4
	u.u_error = sosplice(f1->f_socket, f2->f_socket);
E 4
	if (u.u_error)
		return;
	u.u_ofile[ap->fd1] = 0;
	u.u_ofile[ap->fd2] = 0;
	f1->f_count = 0;
	f2->f_count = 0;
E 2
}

/*
E 16
D 2
 * Select a socket.
E 2
I 2
D 4
 * Socket system call interface.  Copy in arguments
E 4
I 4
 * Socket system call interface.  Copy sa arguments
E 4
 * set up file descriptor and call internal socket
 * creation routine.
E 2
 */
D 2
soselect(so, flag)
	register struct socket *so;
	int flag;
E 2
I 2
D 25
ssocket()
E 25
I 25
osocket()
E 25
E 2
{
E 27
D 2
	register struct proc *p;
E 2
I 2
	register struct a {
E 83
I 83
D 89
/* ARGSUSED */
E 89
socket(p, uap, retval)
	struct proc *p;
D 95
	register struct args {
E 83
I 27
		int	domain;
E 27
		int	type;
D 4
		struct	in_addr *ain;
E 4
I 4
D 27
		struct	sockproto *asp;
		struct	sockaddr *asa;
E 4
		int	options;
E 27
I 27
		int	protocol;
D 42
		struct	socketopt *opt;
E 42
E 27
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	register struct socket_args *uap;
E 95
	int *retval;
E 104
I 104
	register struct socket_args /* {
		syscallarg(int) domain;
		syscallarg(int) type;
		syscallarg(int) protocol;
	} */ *uap;
	register_t *retval;
E 104
{
I 89
	struct filedesc *fdp = p->p_fd;
E 89
E 83
D 4
	struct in_addr in;
	struct socket *so0;
E 4
I 4
D 27
	struct sockproto sp;
	struct sockaddr sa;
E 27
	struct socket *so;
E 4
D 75
	register struct file *fp;
E 75
I 75
	struct file *fp;
D 80
	int fd;
E 80
I 80
	int fd, error;
E 80
E 75
I 27
D 42
	struct socketopt aopt;
E 42
E 27
I 4
D 20
COUNT(SSOCKET);
E 20
E 4
E 2

D 2
	if (soreadable(so))
		return (1);
	if ((p = so->so_rcv.sb_sel) && p->p_wchan == (caddr_t)select)
		so->so_rcv.sb_flags |= SB_COLL;
	else
		so->so_rcv.sb_sel = u.u_procp;
	return (0);
}

/*
 * Wakeup read sleep/select'ers.
 */
sowakeup(so)
	struct socket *so;
{

	if (so->so_rcv.sb_sel && soreadable(so)) {
		selwakeup(so->so_rcv.sb_sel, so->so_rcv.sb_flags & SB_COLL);
		so->so_rcv.sb_sel = 0;
		so->so_rcv.sb_flags &= ~SB_COLL;
E 2
I 2
D 29
	if ((fp = falloc()) == NULL)
E 29
I 29
D 33
	u.u_error = sockopt(&aopt, uap->opt);
E 33
I 33
D 42
	u.u_error = sockopt(&aopt, (caddr_t)uap->opt);
E 33
	if (u.u_error)
E 29
		return;
E 42
I 29
D 75
	if ((fp = falloc()) == NULL)
E 75
I 75
D 80
	if (u.u_error = falloc(&fp, &fd))
E 75
D 42
		goto freeopt;
E 42
I 42
		return;
E 80
I 80
D 89
	if (error = falloc(&fp, &fd))
E 89
I 89
	if (error = falloc(p, &fp, &fd))
E 89
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
E 80
E 42
E 29
D 21
	fp->f_flag = FSOCKET|FREAD|FWRITE;
E 21
I 21
	fp->f_flag = FREAD|FWRITE;
	fp->f_type = DTYPE_SOCKET;
I 47
	fp->f_ops = &socketops;
E 47
E 21
D 3
	if (copyin((caddr_t)uap->ain, &in, sizeof (in))) {
E 3
I 3
D 4
	if (copyin((caddr_t)uap->ain, (caddr_t)&in, sizeof (in))) {
E 4
I 4
D 27
	if (uap->asp && copyin((caddr_t)uap->asp, (caddr_t)&sp, sizeof (sp)) ||
	    uap->asa && copyin((caddr_t)uap->asa, (caddr_t)&sa, sizeof (sa))) {
E 4
E 3
		u.u_error = EFAULT;
E 27
I 27
D 29
	u.u_error = sockopt(&aopt, uap->opt);
	if (u.u_error)
E 27
D 22
		return;
E 22
I 22
		goto bad;
E 29
E 22
E 2
D 27
	}
D 2
	if (so->so_rcv.sb_flags & SB_WAIT) {
		so->so_rcv.sb_flags &= ~SB_WAIT;
		wakeup((caddr_t)&so->so_rcv.sb_cc);
	}
E 2
I 2
D 4
	u.u_error = socket(&so0, uap->type, &in, uap->options);
E 4
I 4
	u.u_error = socreate(&so, uap->type,
	    uap->asp ? &sp : 0, uap->asa ? &sa : 0, uap->options);
E 27
I 27
D 37
	u.u_error = socreate(0, &so, uap->type, uap->protocol, &aopt);
E 37
I 37
D 38
	u.u_error = socreate(AF_UNSPEC, &so, uap->type, uap->protocol, &aopt);
E 38
I 38
D 42
	u.u_error = socreate(uap->domain, &so, uap->type, uap->protocol, &aopt);
E 42
I 42
D 80
	u.u_error = socreate(uap->domain, &so, uap->type, uap->protocol);
E 42
E 38
E 37
E 27
E 4
	if (u.u_error)
		goto bad;
D 4
	fp->f_socket = so0;
E 4
I 4
D 47
	fp->f_socket = so;
E 47
I 47
	fp->f_data = (caddr_t)so;
I 75
	u.u_r.r_val1 = fd;
E 75
E 47
I 27
D 42
freeopt:
	if (uap->opt)
D 36
		m_free(dtom(aopt.so_optdata));
E 36
I 36
		(void) m_free(dtom(aopt.so_optdata));
E 42
E 36
E 27
D 5
	so->so_isfilerefd = 1;
E 5
E 4
	return;
bad:
D 75
	u.u_ofile[u.u_r.r_val1] = 0;
E 75
I 75
	u.u_ofile[fd] = 0;
	crfree(fp->f_cred);
E 75
	fp->f_count = 0;
E 80
I 80
D 104
	if (error = socreate(uap->domain, &so, uap->type, uap->protocol)) {
E 104
I 104
	if (error = socreate(SCARG(uap, domain), &so, SCARG(uap, type),
	    SCARG(uap, protocol))) {
E 104
D 89
		u.u_ofile[fd] = 0;
E 89
I 89
D 91
		OFILE(fdp, fd) = 0;
E 91
I 91
		fdp->fd_ofiles[fd] = 0;
E 91
E 89
D 92
		crfree(fp->f_cred);
		fp->f_count = 0;
E 92
I 92
		ffree(fp);
E 92
	} else {
		fp->f_data = (caddr_t)so;
D 83
		u.u_r.r_val1 = fd;
E 83
I 83
		*retval = fd;
E 83
	}
D 86
	RETURN (error);
E 86
I 86
	return (error);
E 86
E 80
I 27
D 42
	goto freeopt;
E 42
E 27
E 2
}
I 3

I 95
D 104
struct bind_args {
	int	s;
	caddr_t	name;
	int	namelen;
};
E 104
E 95
I 4
D 27
/*
 * Accept system call interface.
 */
E 4
D 25
saccept()
E 25
I 25
oaccept()
E 27
I 27
D 83
bind()
E 27
E 25
{
I 4
	register struct a {
E 83
I 83
/* ARGSUSED */
I 104
int
E 104
bind(p, uap, retval)
	struct proc *p;
D 95
	register struct args {
E 83
D 27
		int	fdes;
		struct	sockaddr *asa;
E 27
I 27
		int	s;
		caddr_t	name;
		int	namelen;
D 42
		struct	socketopt *opt;
E 42
E 27
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	register struct bind_args *uap;
E 95
	int *retval;
E 104
I 104
	register struct bind_args /* {
		syscallarg(int) s;
		syscallarg(caddr_t) name;
		syscallarg(int) namelen;
	} */ *uap;
	register_t *retval;
E 104
{
E 83
D 27
	struct sockaddr sa;
E 27
D 89
	register struct file *fp;
E 89
I 89
	struct file *fp;
E 89
D 27
	struct socket *so;
	int s;
E 27
I 27
	struct mbuf *nam;
I 80
	int error;
E 80
D 42
	struct socketopt aopt;
E 42
E 27
D 20
COUNT(SACCEPT);
E 20
E 4

I 4
D 27
	if (uap->asa && useracc((caddr_t)uap->asa, sizeof (sa), B_WRITE)==0) {
		u.u_error = EFAULT;
E 27
I 27
D 47
	fp = getf(uap->s);
E 47
I 47
D 80
	fp = getsock(uap->s);
E 80
I 80
D 89
	fp = getsock(uap->s, &error);
E 80
E 47
	if (fp == 0)
E 89
I 89
D 104
	if (error = getsock(p->p_fd, uap->s, &fp))
E 104
I 104
	if (error = getsock(p->p_fd, SCARG(uap, s), &fp))
E 104
E 89
E 27
D 80
		return;
I 27
D 47
	if (fp->f_type != DTYPE_SOCKET) {
		u.u_error = ENOTSOCK;
		return;
E 27
	}
D 27
	fp = getf(uap->fdes);
E 27
I 27
	u.u_error = sockname(&nam, uap->name, uap->namelen);
E 47
I 47
D 57
	u.u_error = sockargs(&nam, uap->name, uap->namelen);
E 57
I 57
	u.u_error = sockargs(&nam, uap->name, uap->namelen, MT_SONAME);
E 57
E 47
	if (u.u_error)
		return;
D 33
	u.u_error = sockopt(&aopt, uap->opt);
E 33
I 33
D 42
	u.u_error = sockopt(&aopt, (caddr_t)uap->opt);
E 33
	if (u.u_error) {
		m_freem(nam);
D 30
		return;
E 30
I 30
		goto freeopt;
E 30
	}
	u.u_error = sobind(fp->f_socket, nam, &aopt);
E 42
I 42
D 47
	u.u_error = sobind(fp->f_socket, nam);
E 47
I 47
	u.u_error = sobind((struct socket *)fp->f_data, nam);
E 80
I 80
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
D 104
	if (error = sockargs(&nam, uap->name, uap->namelen, MT_SONAME))
E 104
I 104
	if (error = sockargs(&nam, SCARG(uap, name), SCARG(uap, namelen),
	    MT_SONAME))
E 104
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
	error = sobind((struct socket *)fp->f_data, nam);
E 80
E 47
E 42
	m_freem(nam);
I 80
D 86
	RETURN (error);
E 86
I 86
	return (error);
E 86
E 80
I 30
D 42
freeopt:
E 30
	if (uap->opt)
D 36
		m_free(dtom(aopt.so_optdata));
E 36
I 36
		(void) m_free(dtom(aopt.so_optdata));
E 42
E 36
}

I 95
D 104
struct listen_args {
	int	s;
	int	backlog;
};
E 104
E 95
D 83
listen()
{
	register struct a {
E 83
I 83
/* ARGSUSED */
I 104
int
E 104
listen(p, uap, retval)
	struct proc *p;
D 95
	register struct args {
E 83
		int	s;
		int	backlog;
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	register struct listen_args *uap;
E 95
	int *retval;
E 104
I 104
	register struct listen_args /* {
		syscallarg(int) s;
		syscallarg(int) backlog;
	} */ *uap;
	register_t *retval;
E 104
{
E 83
D 89
	register struct file *fp;
E 89
I 89
	struct file *fp;
E 89
I 80
	int error;
E 80

D 47
	fp = getf(uap->s);
E 47
I 47
D 80
	fp = getsock(uap->s);
E 80
I 80
D 89
	fp = getsock(uap->s, &error);
E 80
E 47
E 27
	if (fp == 0)
E 89
I 89
D 104
	if (error = getsock(p->p_fd, uap->s, &fp))
E 104
I 104
	if (error = getsock(p->p_fd, SCARG(uap, s), &fp))
E 104
E 89
D 80
		return;
D 21
	if ((fp->f_flag & FSOCKET) == 0) {
E 21
I 21
D 47
	if (fp->f_type != DTYPE_SOCKET) {
E 21
		u.u_error = ENOTSOCK;
		return;
	}
I 27
	u.u_error = solisten(fp->f_socket, uap->backlog);
E 47
I 47
	u.u_error = solisten((struct socket *)fp->f_data, uap->backlog);
E 80
I 80
D 86
		RETURN (error);
	RETURN (solisten((struct socket *)fp->f_data, uap->backlog));
E 86
I 86
		return (error);
D 104
	return (solisten((struct socket *)fp->f_data, uap->backlog));
E 104
I 104
	return (solisten((struct socket *)fp->f_data, SCARG(uap, backlog)));
E 104
E 86
E 80
E 47
}

I 95
D 104
struct accept_args {
	int	s;
	caddr_t	name;
	int	*anamelen;
E 104
E 95
I 73
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
I 95
D 104
	int	compat_43;	/* pseudo */
#endif
};

#ifdef COMPAT_OLDSOCK
E 104
I 104
int
E 104
E 95
E 93
E 73
D 83
accept()
{
I 73
D 80
	accept1(0);
E 80
I 80
	struct a {
E 83
I 83
accept(p, uap, retval)
	struct proc *p;
D 95
	struct args {
E 83
		int	s;
		caddr_t	name;
		int	*anamelen;
		int	compat_43;
D 83
	};
	((struct a *)u.u_ap)->compat_43 = 0;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	struct accept_args *uap;
E 95
	int *retval;
E 104
I 104
	struct accept_args /* {
		syscallarg(int) s;
		syscallarg(caddr_t) name;
		syscallarg(int *) anamelen;
	} */ *uap;
	register_t *retval;
E 104
{
E 83

D 83
	RETURN (accept1());
E 83
I 83
D 104
	uap->compat_43 = 0;
D 86
	RETURN (accept1(p, uap, retval));
E 86
I 86
	return (accept1(p, uap, retval));
E 104
I 104
	return (accept1(p, uap, retval, 0));
E 104
E 86
E 83
E 80
}

D 83
oaccept()
{
D 80
	accept1(1);
E 80
I 80
	struct a {
E 83
I 83
D 104
oaccept(p, uap, retval)
E 104
I 104
int
compat_43_accept(p, uap, retval)
E 104
	struct proc *p;
D 95
	struct args {
E 83
		int	s;
		caddr_t	name;
		int	*anamelen;
		int	compat_43;
D 83
	};
	((struct a *)u.u_ap)->compat_43 = 1;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	struct accept_args *uap;
E 95
	int *retval;
E 104
I 104
	struct accept_args /* {
		syscallarg(int) s;
		syscallarg(caddr_t) name;
		syscallarg(int *) anamelen;
	} */ *uap;
	register_t *retval;
E 104
{
E 83

D 83
	RETURN (accept1());
E 83
I 83
D 104
	uap->compat_43 = 1;
D 86
	RETURN (accept1(p, uap, retval));
E 86
I 86
	return (accept1(p, uap, retval));
E 104
I 104
	return (accept1(p, uap, retval, 1));
E 104
E 86
E 83
E 80
}
I 80
D 93
#else /* COMPAT_43 */
E 93
I 93
#else /* COMPAT_OLDSOCK */
E 93
E 80

D 80
accept1(compat_43)
#else
accept()
E 80
I 80
#define	accept1	accept
E 80
#endif
I 80

D 83
accept1()
E 80
{
E 73
	register struct a {
E 83
I 83
D 89
/* ARGSUSED */
E 89
D 104
accept1(p, uap, retval)
E 104
I 104
int
accept1(p, uap, retval, compat_43)
E 104
	struct proc *p;
D 95
	register struct args {
E 83
		int	s;
		caddr_t	name;
		int	*anamelen;
I 80
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
E 93
		int	compat_43;
#endif
E 80
D 42
		struct	socketopt *opt;
E 42
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	register struct accept_args *uap;
E 95
	int *retval;
E 104
I 104
	register struct accept_args /* {
		syscallarg(int) s;
		syscallarg(caddr_t) name;
		syscallarg(int *) anamelen;
	} */ *uap;
	register_t *retval;
	int compat_43;
E 104
{
E 83
D 75
	register struct file *fp;
E 75
I 75
	struct file *fp;
E 75
	struct mbuf *nam;
D 42
	struct socketopt aopt;
E 42
D 79
	int namelen;
	int s;
E 79
I 79
D 104
	int namelen, error, s;
E 104
I 104
	int namelen, error, s, tmpfd;
E 104
E 79
	register struct socket *so;

D 80
	if (uap->name == 0)
		goto noname;
D 40
	if (copyin((caddr_t)uap->anamelen, (caddr_t)&namelen, sizeof (namelen))) {
		u.u_error = EFAULT;
E 40
I 40
D 79
	u.u_error = copyin((caddr_t)uap->anamelen, (caddr_t)&namelen,
E 79
I 79
	error = copyin((caddr_t)uap->anamelen, (caddr_t)&namelen,
E 79
		sizeof (namelen));
D 79
	if (u.u_error)
E 40
		return;
D 40
	}
E 40
D 33
	if (useracc((caddr_t)uap->name, namelen, B_WRITE) == 0) {
E 33
I 33
	if (useracc((caddr_t)uap->name, (u_int)namelen, B_WRITE) == 0) {
E 33
		u.u_error = EFAULT;
		return;
	}
E 79
I 79
	if (error)
		RETURN (error);
	if (useracc((caddr_t)uap->name, (u_int)namelen, B_WRITE) == 0)
		RETURN (EFAULT);
E 79
noname:
D 33
	u.u_error = sockopt(&aopt, uap->opt);
E 33
I 33
D 42
	u.u_error = sockopt(&aopt, (caddr_t)uap->opt);
E 33
	if (u.u_error)
		return;
E 42
D 47
	fp = getf(uap->s);
E 47
I 47
	fp = getsock(uap->s);
E 80
I 80
D 81
	if (uap->name) {
		error = copyin((caddr_t)uap->anamelen, (caddr_t)&namelen,
			sizeof (namelen));
		if (error)
			return (error);
		if (useracc((caddr_t)uap->name, (u_int)namelen, B_WRITE) == 0)
			return (EFAULT);
	}
E 81
I 81
D 104
	if (uap->name && (error = copyin((caddr_t)uap->anamelen,
E 104
I 104
	if (SCARG(uap, name) && (error = copyin((caddr_t)SCARG(uap, anamelen),
E 104
	    (caddr_t)&namelen, sizeof (namelen))))
D 83
		return (error);
E 83
I 83
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
E 83
E 81
D 89
	fp = getsock(uap->s, &error);
E 80
E 47
	if (fp == 0)
E 89
I 89
D 104
	if (error = getsock(p->p_fd, uap->s, &fp))
E 104
I 104
	if (error = getsock(p->p_fd, SCARG(uap, s), &fp))
E 104
E 89
D 42
		goto bad;
E 42
I 42
D 80
		return;
E 80
I 80
D 83
		return (error);
E 83
I 83
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
E 83
E 80
E 42
D 47
	if (fp->f_type != DTYPE_SOCKET) {
		u.u_error = ENOTSOCK;
D 42
		goto bad;
E 42
I 42
		return;
E 42
	}
E 47
E 27
	s = splnet();
D 47
	so = fp->f_socket;
E 47
I 47
	so = (struct socket *)fp->f_data;
E 47
D 13
	if ((so->so_options & SO_NBIO) &&
E 13
I 13
D 15
	if ((so->so_options & SO_NONBLOCKING) &&
E 15
I 15
D 21
	if ((so->so_state & SS_NBIO) &&
E 15
E 13
	    (so->so_state & SS_CONNAWAITING) == 0) {
E 21
I 21
	if ((so->so_options & SO_ACCEPTCONN) == 0) {
D 79
		u.u_error = EINVAL;
E 79
		splx(s);
D 27
		return;
E 27
I 27
D 42
		goto bad;
E 42
I 42
D 79
		return;
E 79
I 79
D 80
		RETURN (EINVAL);
E 80
I 80
D 83
		return (EINVAL);
E 83
I 83
D 86
		RETURN (EINVAL);
E 86
I 86
		return (EINVAL);
E 86
E 83
E 80
E 79
E 42
E 27
	}
	if ((so->so_state & SS_NBIO) && so->so_qlen == 0) {
E 21
D 79
		u.u_error = EWOULDBLOCK;
E 79
		splx(s);
D 27
		return;
E 27
I 27
D 42
		goto bad;
E 42
I 42
D 79
		return;
E 79
I 79
D 80
		RETURN (EWOULDBLOCK);
E 80
I 80
D 83
		return (EWOULDBLOCK);
E 83
I 83
D 86
		RETURN (EWOULDBLOCK);
E 86
I 86
		return (EWOULDBLOCK);
E 86
E 83
E 80
E 79
E 42
E 27
	}
I 12
D 14
	while ((so->so_state & SS_CONNAWAITING) == 0)
E 14
I 14
D 18
	while ((so->so_state & SS_CONNAWAITING) == 0 && so->so_error == 0)
E 18
I 18
D 21
	while ((so->so_state & SS_CONNAWAITING) == 0 && so->so_error == 0) {
E 21
I 21
	while (so->so_qlen == 0 && so->so_error == 0) {
E 21
		if (so->so_state & SS_CANTRCVMORE) {
			so->so_error = ECONNABORTED;
			break;
		}
E 18
E 14
D 78
		sleep((caddr_t)&so->so_timeo, PZERO+1);
E 78
I 78
D 79
		tsleep((caddr_t)&so->so_timeo, PZERO+1, SLP_SO_ACCEPT, 0);
E 79
I 79
		if (error = tsleep((caddr_t)&so->so_timeo, PSOCK | PCATCH,
		    netcon, 0)) {
			splx(s);
D 80
			RETURN (error);
E 80
I 80
D 83
			return (error);
E 83
I 83
D 86
			RETURN (error);
E 86
I 86
			return (error);
E 86
E 83
E 80
		}
E 79
E 78
I 18
	}
E 18
I 14
	if (so->so_error) {
D 79
		u.u_error = so->so_error;
E 79
I 79
		error = so->so_error;
E 79
I 59
		so->so_error = 0;
E 59
		splx(s);
D 27
		return;
E 27
I 27
D 42
		goto bad;
E 42
I 42
D 79
		return;
E 79
I 79
D 80
		RETURN (error);
E 80
I 80
D 83
		return (error);
E 83
I 83
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
E 83
E 80
E 79
E 42
E 27
	}
E 14
E 12
D 21
	u.u_error = soaccept(so, &sa);
	if (u.u_error) {
E 21
I 21
D 47
	if ((so->so_options & SO_NEWFDONCONN) == 0) {
		struct socket *nso = so->so_q;
		(void) soqremque(nso, 1);
D 34
		soclose(so, 1);
E 34
I 34
		u.u_error = soclose(so, 1);
E 34
		fp->f_socket = nso;
		nso->so_q = 0;
		so = nso;
		goto ret;
	}
	if (ufalloc() < 0) {
E 47
I 47
D 75
	if (ufalloc(0) < 0) {
E 75
I 75
D 79
	if (u.u_error = falloc(&fp, &u.u_r.r_val1)) {
E 79
I 79
D 83
	if (error = falloc(&fp, &u.u_r.r_val1)) {
E 83
I 83
D 89
	if (error = falloc(&fp, retval)) {
E 89
I 89
D 104
	if (error = falloc(p, &fp, retval)) {
E 104
I 104
	if (error = falloc(p, &fp, &tmpfd)) {
E 104
E 89
E 83
E 79
E 75
E 47
E 21
		splx(s);
D 27
		return;
E 27
I 27
D 42
		goto bad;
E 42
I 42
D 79
		return;
E 79
I 79
D 80
		RETURN (error);
E 80
I 80
D 83
		return (error);
E 83
I 83
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
E 83
E 80
E 79
E 42
E 27
	}
I 104
	*retval = tmpfd;
E 104
I 21
D 75
	fp = falloc();
	if (fp == 0) {
		u.u_ofile[u.u_r.r_val1] = 0;
		splx(s);
D 27
		return;
E 27
I 27
D 42
		goto bad;
E 42
I 42
		return;
E 42
E 27
	}
E 75
I 27
	{ struct socket *aso = so->so_q;
	  if (soqremque(aso, 1) == 0)
		panic("accept");
	  so = aso;
	}
E 27
	fp->f_type = DTYPE_SOCKET;
	fp->f_flag = FREAD|FWRITE;
D 27
	fp->f_socket = so->so_q;
	so->so_q = so->so_q->so_q;
	so->so_qlen--;
E 27
I 27
D 47
	fp->f_socket = so;
E 27
ret:
E 47
I 47
	fp->f_ops = &socketops;
	fp->f_data = (caddr_t)so;
E 47
D 27
	soaccept(so, &sa);
E 21
I 12
	if (uap->asa)
		(void) copyout((caddr_t)&sa, (caddr_t)uap->asa, sizeof (sa));
E 27
I 27
D 39
	nam = m_get(M_WAIT);
E 39
I 39
	nam = m_get(M_WAIT, MT_SONAME);
E 39
D 30
	nam->m_off = MMINOFF;
E 30
D 35
	soaccept(so, nam, &aopt);
E 35
I 35
D 42
	(void) soaccept(so, nam, &aopt);
E 42
I 42
	(void) soaccept(so, nam);
E 42
E 35
D 104
	if (uap->name) {
E 104
I 104
	if (SCARG(uap, name)) {
E 104
I 73
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
E 93
D 80
		if (compat_43)
E 80
I 80
D 104
		if (uap->compat_43)
E 104
I 104
		if (compat_43)
E 104
E 80
			mtod(nam, struct osockaddr *)->sa_family =
			    mtod(nam, struct sockaddr *)->sa_family;
#endif
E 73
		if (namelen > nam->m_len)
			namelen = nam->m_len;
		/* SHOULD COPY OUT A CHAIN HERE */
D 33
		(void) copyout(mtod(nam, caddr_t), uap->name, namelen);
		(void) copyout((caddr_t)&namelen, uap->anamelen,
E 33
I 33
D 81
		(void) copyout(mtod(nam, caddr_t), (caddr_t)uap->name,
		    (u_int)namelen);
		(void) copyout((caddr_t)&namelen, (caddr_t)uap->anamelen,
E 33
		    sizeof (*uap->anamelen));
E 81
I 81
D 104
		if ((error = copyout(mtod(nam, caddr_t), (caddr_t)uap->name,
		    (u_int)namelen)) == 0)
E 104
I 104
		if ((error = copyout(mtod(nam, caddr_t),
		    (caddr_t)SCARG(uap, name), (u_int)namelen)) == 0)
E 104
			error = copyout((caddr_t)&namelen,
D 104
			    (caddr_t)uap->anamelen, sizeof (*uap->anamelen));
E 104
I 104
			    (caddr_t)SCARG(uap, anamelen),
			    sizeof (*SCARG(uap, anamelen)));
E 104
E 81
	}
	m_freem(nam);
E 27
E 12
D 21
	/* deal with new file descriptor case */
	/* u.u_r.r_val1 = ... */
E 21
	splx(s);
I 79
D 80
	RETURN (0);
E 80
I 80
D 81
	return (0);
E 81
I 81
D 83
	return (error);
E 83
I 83
D 86
	RETURN (error);
E 86
I 86
	return (error);
E 86
E 83
E 81
E 80
E 79
I 27
D 42
bad:
	if (uap->opt)
D 36
		m_free(dtom(aopt.so_optdata));
E 36
I 36
		(void) m_free(dtom(aopt.so_optdata));
E 42
E 36
E 27
E 4
}

I 95
D 104
struct connect_args {
	int	s;
	caddr_t	name;
	int	namelen;
};
E 104
E 95
I 72
D 73
#ifdef COMPAT_43
oaccept()
{
	return (accept());
}
#endif

E 73
E 72
E 3
D 2

E 2
D 27
/*
 * Connect socket to foreign peer; system call
D 4
 * interface.  Copy in arguments and call internal routine.
E 4
I 4
 * interface.  Copy sa arguments and call internal routine.
E 4
 */
D 25
sconnect()
E 25
I 25
oconnect()
E 27
I 27
D 83
connect()
E 27
E 25
{
	register struct a {
E 83
I 83
/* ARGSUSED */
I 104
int
E 104
connect(p, uap, retval)
	struct proc *p;
D 95
	register struct args {
E 83
D 4
		int fdes;
		struct in_addr *a;
E 4
I 4
D 27
		int	fdes;
		struct	sockaddr *a;
E 27
I 27
		int	s;
		caddr_t	name;
		int	namelen;
D 42
		struct	socketopt *opt;
E 42
E 27
E 4
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	register struct connect_args *uap;
E 95
	int *retval;
E 104
I 104
	register struct connect_args /* {
		syscallarg(int) s;
		syscallarg(caddr_t) name;
		syscallarg(int) namelen;
	} */ *uap;
	register_t *retval;
E 104
{
E 83
D 4
	in_addr in;
E 4
I 4
D 27
	struct sockaddr sa;
E 27
E 4
D 89
	register struct file *fp;
E 89
I 89
	struct file *fp;
E 89
	register struct socket *so;
I 27
	struct mbuf *nam;
D 42
	struct socketopt aopt;
E 42
E 27
D 79
	int s;
E 79
I 79
	int error, s;
E 79
I 4
D 20
COUNT(SCONNECT);
E 20
E 4

D 3
	if (copyin((caddr_t)uap->a, &in, sizeof (in))) {
E 3
I 3
D 4
	if (copyin((caddr_t)uap->a, (caddr_t)&in, sizeof (in))) {
E 4
I 4
D 27
	if (copyin((caddr_t)uap->a, (caddr_t)&sa, sizeof (sa))) {
E 4
E 3
		u.u_error = EFAULT;
		return;
	}
	fp = getf(uap->fdes);
E 27
I 27
D 47
	fp = getf(uap->s);
E 47
I 47
D 80
	fp = getsock(uap->s);
E 80
I 80
D 89
	fp = getsock(uap->s, &error);
E 80
E 47
E 27
	if (fp == 0)
E 89
I 89
D 104
	if (error = getsock(p->p_fd, uap->s, &fp))
E 104
I 104
	if (error = getsock(p->p_fd, SCARG(uap, s), &fp))
E 104
E 89
D 80
		return;
E 80
I 80
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
E 80
D 21
	if ((fp->f_flag & FSOCKET) == 0) {
E 21
I 21
D 47
	if (fp->f_type != DTYPE_SOCKET) {
E 21
		u.u_error = ENOTSOCK;
		return;
	}
	so = fp->f_socket;
D 4
	u.u_error = connect(so, &in);
E 4
I 4
D 27
	u.u_error = soconnect(so, &sa);
E 27
I 27
	u.u_error = sockname(&nam, uap->name, uap->namelen);
E 47
I 47
	so = (struct socket *)fp->f_data;
I 65
D 79
	if ((so->so_state & SS_NBIO) &&
	    (so->so_state & SS_ISCONNECTING)) {
D 66
		u.u_error = EINPROGRESS;
E 66
I 66
		u.u_error = EALREADY;
E 66
		return;
	}
E 65
D 57
	u.u_error = sockargs(&nam, uap->name, uap->namelen);
E 57
I 57
	u.u_error = sockargs(&nam, uap->name, uap->namelen, MT_SONAME);
E 57
E 47
E 27
E 4
	if (u.u_error)
		return;
I 27
D 33
	u.u_error = sockopt(&aopt, uap->opt);
E 33
I 33
D 42
	u.u_error = sockopt(&aopt, (caddr_t)uap->opt);
E 33
	if (u.u_error) {
		m_freem(nam);
		return;
	}
	u.u_error = soconnect(so, nam, &aopt);
E 42
I 42
	u.u_error = soconnect(so, nam);
E 42
	if (u.u_error)
E 79
I 79
	if ((so->so_state & SS_NBIO) && (so->so_state & SS_ISCONNECTING))
D 86
		RETURN (EALREADY);
E 86
I 86
		return (EALREADY);
E 86
D 104
	if (error = sockargs(&nam, uap->name, uap->namelen, MT_SONAME))
E 104
I 104
	if (error = sockargs(&nam, SCARG(uap, name), SCARG(uap, namelen),
	    MT_SONAME))
E 104
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
	error = soconnect(so, nam);
	if (error)
E 79
		goto bad;
I 66
D 79
	if ((so->so_state & SS_NBIO) &&
	    (so->so_state & SS_ISCONNECTING)) {
		u.u_error = EINPROGRESS;
E 79
I 79
	if ((so->so_state & SS_NBIO) && (so->so_state & SS_ISCONNECTING)) {
E 79
		m_freem(nam);
D 79
		return;
E 79
I 79
D 86
		RETURN (EINPROGRESS);
E 86
I 86
		return (EINPROGRESS);
E 86
E 79
	}
E 66
E 27
	s = splnet();
D 2
	if ((so->so_options & SO_NBIO) && (so->so_state & SS_ISCONN) == 0) {
E 2
I 2
D 13
	if ((so->so_options & SO_NBIO) &&
E 13
I 13
D 15
	if ((so->so_options & SO_NONBLOCKING) &&
E 15
I 15
D 65
	if ((so->so_state & SS_NBIO) &&
E 15
E 13
	    (so->so_state & SS_ISCONNECTING)) {
E 2
		u.u_error = EINPROGRESS;
I 2
D 47
		splx(s);
E 2
D 27
		return;
E 27
I 27
		goto bad;
E 47
I 47
		goto bad2;
E 47
E 27
	}
E 65
I 47
D 79
	if (setjmp(&u.u_qsave)) {
		if (u.u_error == 0)
			u.u_error = EINTR;
		goto bad2;
	}
E 79
E 47
D 2
	while ((so->so_state & (SS_ISCONN|SS_ISCONNING)) == SS_ISCONNING)
E 2
I 2
	while ((so->so_state & SS_ISCONNECTING) && so->so_error == 0)
E 2
D 16
		sleep((caddr_t)&so->so_timeo, PZERO+1);
	u.u_error = so->so_error;
I 2
	so->so_error = 0;
	splx(s);
E 2
}

/*
 * Disconnect socket from foreign peer; system call
D 4
 * interface.  Copy in arguments and call internal routine.
E 4
I 4
 * interface.  Copy sa arguments and call internal routine.
E 4
 */
sdisconnect()
{
	register struct a {
		int	fdes;
D 4
		in_addr	 *addr;
E 4
I 4
		struct	sockaddr *asa;
E 4
	} *uap = (struct a *)u.u_ap;
D 4
	in_addr in;
E 4
I 4
	struct sockaddr sa;
E 4
	register struct file *fp;
I 2
	register struct socket *so;
E 2
	int s;
I 4
COUNT(SDISCONNECT);
E 4

D 4
	if (uap->addr &&
	    copyin((caddr_t)uap->addr, (caddr_t)&in, sizeof (in))) {
E 4
I 4
	if (uap->asa &&
	    copyin((caddr_t)uap->asa, (caddr_t)&sa, sizeof (sa))) {
E 4
		u.u_error = EFAULT;
		return;
	}
	fp = getf(uap->fdes);
	if (fp == 0)
		return;
	if ((fp->f_flag & FSOCKET) == 0) {
		u.u_error = ENOTSOCK;
		return;
	}
D 2
	u.u_error = disconnect(fp->f_socket, uap->addr ? &in : 0);
E 2
I 2
	so = fp->f_socket;
D 4
	u.u_error = disconnect(so, uap->addr ? &in : 0);
E 4
I 4
	u.u_error = sodisconnect(so, uap->asa ? &sa : 0);
E 4
E 2
	if (u.u_error)
		return;
	s = splnet();
D 2
	if ((so->so_options&SO_NBIO) && (so->so_state&SS_ISCONNECTED))
		return (EINPROGRESS);
	while ((so)->so_state & (SS_ISCONNECTED|SS_ISDISCONNECTING) == SS_ISDISCONNECTING)
E 2
I 2
D 13
	if ((so->so_options&SO_NBIO) && (so->so_state&SS_ISDISCONNECTING)) {
E 13
I 13
D 15
	if ((so->so_options&SO_NONBLOCKING) && (so->so_state&SS_ISDISCONNECTING)) {
E 15
I 15
	if ((so->so_state&SS_NBIO) && (so->so_state&SS_ISDISCONNECTING)) {
E 15
E 13
		u.u_error = EINPROGRESS;
		splx(s);
		return;
	}
D 10
	while (so->so_state & SS_ISDISCONNECTING)
E 10
I 10
	while ((so->so_state & SS_ISDISCONNECTING) && so->so_error == 0)
E 16
E 10
E 2
D 78
		sleep((caddr_t)&so->so_timeo, PZERO+1);
E 78
I 78
D 79
		tsleep((caddr_t)&so->so_timeo, PZERO+1, SLP_SO_ACCEPT2, 0);
E 78
	u.u_error = so->so_error;
I 2
	so->so_error = 0;
I 60
D 61
	so->so_state &= ~SS_ISCONNECTING;
E 61
E 60
I 47
bad2:
E 79
I 79
		if (error = tsleep((caddr_t)&so->so_timeo, PSOCK | PCATCH,
		    netcon, 0))
			break;
	if (error == 0) {
		error = so->so_error;
		so->so_error = 0;
	}
E 79
E 47
	splx(s);
I 27
bad:
I 61
	so->so_state &= ~SS_ISCONNECTING;
E 61
	m_freem(nam);
I 79
	if (error == ERESTART)
		error = EINTR;
D 86
	RETURN (error);
E 86
I 86
	return (error);
E 86
E 79
D 42
	if (uap->opt)
D 36
		m_free(dtom(aopt.so_optdata));
E 36
I 36
		(void) m_free(dtom(aopt.so_optdata));
E 36
	return;
E 42
E 27
E 2
}

I 95
D 104
struct socketpair_args {
	int	domain;
	int	type;
	int	protocol;
	int	*rsv;
};
E 104
I 104
int
E 104
E 95
D 27
/*
 * Send data on socket.
 */
D 25
ssend()
E 25
I 25
osend()
E 27
I 27
D 83
socketpair()
E 27
E 25
{
I 48
	register struct a {
E 83
I 83
D 89
/* ARGSUSED */
E 89
socketpair(p, uap, retval)
	struct proc *p;
D 95
	register struct args {
E 83
		int	domain;
		int	type;
		int	protocol;
		int	*rsv;
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	register struct socketpair_args *uap;
E 95
	int retval[];
E 104
I 104
	register struct socketpair_args /* {
		syscallarg(int) domain;
		syscallarg(int) type;
		syscallarg(int) protocol;
		syscallarg(int *) rsv;
	} */ *uap;
	register_t *retval;
E 104
{
I 89
	register struct filedesc *fdp = p->p_fd;
E 89
E 83
D 75
	register struct file *fp1, *fp2;
E 75
I 75
	struct file *fp1, *fp2;
E 75
	struct socket *so1, *so2;
D 75
	int sv[2];
E 75
I 75
D 80
	int fd, sv[2];
E 80
I 80
	int fd, error, sv[2];
E 80
E 75
E 48
I 27

D 48
	u.u_error = ENOENT;
E 48
I 48
D 80
	if (useracc((caddr_t)uap->rsv, 2 * sizeof (int), B_WRITE) == 0) {
		u.u_error = EFAULT;
		return;
	}
	u.u_error = socreate(uap->domain, &so1, uap->type, uap->protocol);
	if (u.u_error)
		return;
	u.u_error = socreate(uap->domain, &so2, uap->type, uap->protocol);
	if (u.u_error)
E 80
I 80
D 81
	if (useracc((caddr_t)uap->rsv, 2 * sizeof (int), B_WRITE) == 0)
		RETURN (EFAULT);
E 81
D 104
	if (error = socreate(uap->domain, &so1, uap->type, uap->protocol))
E 104
I 104
	if (error = socreate(SCARG(uap, domain), &so1, SCARG(uap, type),
	    SCARG(uap, protocol)))
E 104
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
D 104
	if (error = socreate(uap->domain, &so2, uap->type, uap->protocol))
E 104
I 104
	if (error = socreate(SCARG(uap, domain), &so2, SCARG(uap, type),
	    SCARG(uap, protocol)))
E 104
E 80
D 73
		goto free;
E 73
I 73
D 76
		goto freeit;
E 76
I 76
		goto free1;
E 76
E 73
D 75
	fp1 = falloc();
	if (fp1 == NULL)
E 75
I 75
D 80
	if (u.u_error = falloc(&fp1, &fd))
E 80
I 80
D 89
	if (error = falloc(&fp1, &fd))
E 89
I 89
	if (error = falloc(p, &fp1, &fd))
E 89
E 80
E 75
		goto free2;
D 75
	sv[0] = u.u_r.r_val1;
E 75
I 75
	sv[0] = fd;
E 75
	fp1->f_flag = FREAD|FWRITE;
	fp1->f_type = DTYPE_SOCKET;
	fp1->f_ops = &socketops;
	fp1->f_data = (caddr_t)so1;
D 75
	fp2 = falloc();
	if (fp2 == NULL)
E 75
I 75
D 80
	if (u.u_error = falloc(&fp2, &fd))
E 80
I 80
D 89
	if (error = falloc(&fp2, &fd))
E 89
I 89
	if (error = falloc(p, &fp2, &fd))
E 89
E 80
E 75
		goto free3;
	fp2->f_flag = FREAD|FWRITE;
	fp2->f_type = DTYPE_SOCKET;
	fp2->f_ops = &socketops;
	fp2->f_data = (caddr_t)so2;
D 75
	sv[1] = u.u_r.r_val1;
E 75
I 75
	sv[1] = fd;
E 75
D 80
	u.u_error = soconnect2(so1, so2);
	if (u.u_error)
E 80
I 80
	if (error = soconnect2(so1, so2))
E 80
		goto free4;
I 55
D 104
	if (uap->type == SOCK_DGRAM) {
E 104
I 104
	if (SCARG(uap, type) == SOCK_DGRAM) {
E 104
		/*
		 * Datagram socket connection is asymmetric.
		 */
D 80
		 u.u_error = soconnect2(so2, so1);
		 if (u.u_error)
E 80
I 80
		 if (error = soconnect2(so2, so1))
E 80
			goto free4;
	}
D 75
	u.u_r.r_val1 = 0;
E 75
E 55
D 80
	(void) copyout((caddr_t)sv, (caddr_t)uap->rsv, 2 * sizeof (int));
I 75
	u.u_r.r_val1 = sv[0];
	u.u_r.r_val2 = sv[1];
E 75
	return;
E 80
I 80
D 104
	error = copyout((caddr_t)sv, (caddr_t)uap->rsv, 2 * sizeof (int));
E 104
I 104
	error = copyout((caddr_t)sv, (caddr_t)SCARG(uap, rsv),
	    2 * sizeof (int));
E 104
D 83
	u.u_r.r_val1 = sv[0];		/* XXX ??? */
	u.u_r.r_val2 = sv[1];		/* XXX ??? */
E 83
I 83
	retval[0] = sv[0];		/* XXX ??? */
	retval[1] = sv[1];		/* XXX ??? */
E 83
D 86
	RETURN (error);
E 86
I 86
	return (error);
E 86
E 80
free4:
I 75
D 92
	crfree(fp2->f_cred);
E 75
	fp2->f_count = 0;
E 92
I 92
	ffree(fp2);
E 92
D 89
	u.u_ofile[sv[1]] = 0;
E 89
I 89
D 91
	OFILE(fdp, sv[1]) = 0;
E 91
I 91
	fdp->fd_ofiles[sv[1]] = 0;
E 91
E 89
free3:
I 75
D 92
	crfree(fp1->f_cred);
E 75
	fp1->f_count = 0;
E 92
I 92
	ffree(fp1);
E 92
D 89
	u.u_ofile[sv[0]] = 0;
E 89
I 89
D 91
	OFILE(fdp, sv[0]) = 0;
E 91
I 91
	fdp->fd_ofiles[sv[0]] = 0;
E 91
E 89
free2:
I 75
D 76
	so2->so_state |= SS_NOFDREF;
E 76
E 75
D 61
	so2->so_state |= SS_NOFDREF;
	sofree(so2);
E 61
I 61
D 64
	soclose(so2);
E 64
I 64
	(void)soclose(so2);
E 64
E 61
D 73
free:
I 75
D 76
	so1->so_state |= SS_NOFDREF;
E 75
E 73
I 73
freeit:
E 76
I 76
free1:
E 76
E 73
D 61
	so1->so_state |= SS_NOFDREF;
	sofree(so1);
E 61
I 61
D 64
	soclose(so1);
E 64
I 64
	(void)soclose(so1);
I 80
D 86
	RETURN (error);
E 86
I 86
	return (error);
E 86
E 80
E 64
E 61
E 48
}

I 95
D 104
struct sendto_args {
	int	s;
	caddr_t	buf;
D 101
	int	len;
E 101
I 101
	size_t	len;
E 101
	int	flags;
	caddr_t	to;
	int	tolen;
};
E 104
I 104
int
E 104
E 95
D 83
sendto()
{
E 27
	register struct a {
E 83
I 83
D 89
/* ARGSUSED */
E 89
sendto(p, uap, retval)
	struct proc *p;
D 95
	register struct args {
E 83
D 27
		int	fdes;
D 4
		in_addr	*ain;
E 4
I 4
		struct	sockaddr *asa;
E 4
		caddr_t	cbuf;
D 3
		int	count;
E 3
I 3
D 4
		u_int	count;
E 4
I 4
		unsigned count;
E 27
I 27
		int	s;
		caddr_t	buf;
		int	len;
		int	flags;
		caddr_t	to;
		int	tolen;
E 27
E 4
E 3
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	register struct sendto_args *uap;
E 95
	int *retval;
E 104
I 104
	register struct sendto_args /* {
		syscallarg(int) s;
		syscallarg(caddr_t) buf;
		syscallarg(size_t) len;
		syscallarg(int) flags;
		syscallarg(caddr_t) to;
		syscallarg(int) tolen;
	} */ *uap;
	register_t *retval;
E 104
{
E 83
D 47
	register struct file *fp;
D 4
	struct in_addr in;
E 4
I 4
D 27
	struct sockaddr sa;
E 27
I 24
	struct uio auio;
E 47
I 47
	struct msghdr msg;
E 47
	struct iovec aiov;
I 89
D 100
	int error;
E 100
E 89
I 27
D 47
	struct mbuf *to;
E 47
E 27
E 24
D 20
COUNT(SSEND);
E 20
E 4

D 27
	fp = getf(uap->fdes);
E 27
I 27
D 47
	fp = getf(uap->s);
E 27
	if (fp == 0)
		return;
D 21
	if ((fp->f_flag & FSOCKET) == 0) {
E 21
I 21
	if (fp->f_type != DTYPE_SOCKET) {
E 21
		u.u_error = ENOTSOCK;
		return;
	}
I 11
D 24
	u.u_base = uap->cbuf;
E 11
D 3
	if (uap->count < 0) {
		u.u_error = EINVAL;
		return;
	}
	u.u_base = uap->cbuf;
E 3
	u.u_count = uap->count;
	u.u_segflg = 0;
E 24
I 24
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
E 47
I 47
D 104
	msg.msg_name = uap->to;
	msg.msg_namelen = uap->tolen;
E 104
I 104
	msg.msg_name = SCARG(uap, to);
	msg.msg_namelen = SCARG(uap, tolen);
E 104
	msg.msg_iov = &aiov;
	msg.msg_iovlen = 1;
I 79
	msg.msg_control = 0;
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
E 93
	msg.msg_flags = 0;
#endif
E 79
E 47
D 27
	aiov.iov_base = uap->cbuf;
	aiov.iov_len = uap->count;
	auio.uio_resid = uap->count;
E 27
I 27
D 104
	aiov.iov_base = uap->buf;
	aiov.iov_len = uap->len;
D 47
	auio.uio_resid = uap->len;
E 27
	auio.uio_segflg = 0;
	auio.uio_offset = 0;	/* XXX */
E 24
D 2
	if (useracc(u.u_base, u.u_count, B_READ) == 0 ||
E 2
I 2
D 27
	if (useracc(uap->cbuf, uap->count, B_READ) == 0 ||
E 2
D 4
	    uap->ain && copyin((caddr_t)uap->ain, (caddr_t)&in, sizeof (in))) {
E 4
I 4
	    uap->asa && copyin((caddr_t)uap->asa, (caddr_t)&sa, sizeof (sa))) {
E 27
I 27
D 33
	if (useracc(uap->buf, uap->len, B_READ) == 0) {
E 33
I 33
	if (useracc(uap->buf, (u_int)uap->len, B_READ) == 0) {
E 33
E 27
E 4
		u.u_error = EFAULT;
		return;
	}
D 4
	u.u_error = send(fp->f_socket, uap->ain ? &in : 0);
E 4
I 4
D 24
	u.u_error = sosend(fp->f_socket, uap->asa ? &sa : 0);
I 11
	u.u_r.r_val1 = uap->count - u.u_count;
E 24
I 24
D 27
	u.u_error = sosend(fp->f_socket, uap->asa ? &sa : 0, &auio);
	u.u_r.r_val1 = uap->count - auio.uio_resid;
E 27
I 27
	u.u_error = sockname(&to, uap->to, uap->tolen);
	if (u.u_error)
D 44
		goto bad;
E 44
I 44
		return;
E 44
D 30
	u.u_error = sosend(fp->f_socket, to, &auio);
E 30
I 30
	u.u_error = sosend(fp->f_socket, to, &auio, uap->flags);
I 38
	u.u_r.r_val1 = uap->len - auio.uio_resid;
E 38
E 30
D 44
bad:
E 44
	m_freem(to);
E 47
I 47
D 79
	msg.msg_accrights = 0;
D 72
	msg.msg_accrightslen = 0;
E 72
I 72
	msg.msg_control = 0;
E 79
E 72
D 80
	sendit(uap->s, &msg, uap->flags);
E 80
I 80
D 83
	RETURN (sendit(uap->s, &msg, uap->flags));
E 83
I 83
D 86
	RETURN (sendit(uap->s, &msg, uap->flags, retval));
E 86
I 86
D 89
	return (sendit(uap->s, &msg, uap->flags, retval));
E 89
I 89
	return (sendit(p, uap->s, &msg, uap->flags, retval));
E 104
I 104
	aiov.iov_base = SCARG(uap, buf);
	aiov.iov_len = SCARG(uap, len);
	return (sendit(p, SCARG(uap, s), &msg, SCARG(uap, flags), retval));
E 104
E 89
E 86
E 83
E 80
E 47
E 27
E 24
E 11
E 4
}

I 2
D 27
/*
 * Receive data on socket.
 */
D 25
sreceive()
E 25
I 25
oreceive()
E 27
I 27
D 72
send()
E 72
I 72
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
I 95
D 104
struct osend_args {
	int	s;
	caddr_t	buf;
	int	len;
	int	flags;
};
E 95
E 93
I 73
D 80

E 80
E 73
D 83
osend()
E 72
E 27
E 25
{
	register struct a {
E 83
I 83
D 89
/* ARGSUSED */
E 89
osend(p, uap, retval)
E 104
I 104
int
compat_43_send(p, uap, retval)
E 104
	struct proc *p;
D 95
	register struct args {
E 83
D 27
		int	fdes;
D 4
		in_addr	*ain;
E 4
I 4
		struct	sockaddr *asa;
E 4
		caddr_t	cbuf;
D 3
		int	count;
E 3
I 3
		u_int	count;
E 27
I 27
		int	s;
		caddr_t	buf;
		int	len;
		int	flags;
E 27
E 3
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	register struct osend_args *uap;
E 95
	int *retval;
E 104
I 104
	register struct compat_43_send_args /* {
		syscallarg(int) s;
		syscallarg(caddr_t) buf;
		syscallarg(int) len;
		syscallarg(int) flags;
	} */ *uap;
	register_t *retval;
E 104
{
E 83
D 47
	register struct file *fp;
D 3
	struct in_addr *in;
E 3
I 3
D 4
	struct in_addr in;
E 4
I 4
D 27
	struct sockaddr sa;
E 27
I 23
	struct uio auio;
E 47
I 47
	struct msghdr msg;
E 47
	struct iovec aiov;
I 27
D 32
	struct mbuf *nam;
E 32
E 27
E 23
D 20
COUNT(SRECEIVE);
E 20
E 4
E 3

D 27
	fp = getf(uap->fdes);
E 27
I 27
D 47
	fp = getf(uap->s);
E 27
	if (fp == 0)
		return;
D 21
	if ((fp->f_flag & FSOCKET) == 0) {
E 21
I 21
	if (fp->f_type != DTYPE_SOCKET) {
E 21
		u.u_error = ENOTSOCK;
		return;
	}
I 11
D 23
	u.u_base = uap->cbuf;
E 11
D 3
	if (uap->count < 0) {
		u.u_error = EINVAL;
		return;
	}
	u.u_base = uap->cbuf;
E 3
	u.u_count = uap->count;
	u.u_segflg = 0;
E 23
I 23
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
E 47
I 47
	msg.msg_name = 0;
	msg.msg_namelen = 0;
	msg.msg_iov = &aiov;
	msg.msg_iovlen = 1;
E 47
D 27
	aiov.iov_base = uap->cbuf;
	aiov.iov_len = uap->count;
	auio.uio_resid = uap->count;
E 27
I 27
D 104
	aiov.iov_base = uap->buf;
	aiov.iov_len = uap->len;
E 104
I 104
	aiov.iov_base = SCARG(uap, buf);
	aiov.iov_len = SCARG(uap, len);
E 104
D 47
	auio.uio_resid = uap->len;
E 27
	auio.uio_segflg = 0;
	auio.uio_offset = 0;	/* XXX */
E 23
D 27
	if (useracc(uap->cbuf, uap->count, B_WRITE) == 0 ||
D 4
	    uap->ain && copyin((caddr_t)uap->ain, (caddr_t)&in, sizeof (in))) {
E 4
I 4
	    uap->asa && copyin((caddr_t)uap->asa, (caddr_t)&sa, sizeof (sa))) {
E 27
I 27
D 33
	if (useracc(uap->buf, uap->len, B_READ) == 0) {
E 33
I 33
	if (useracc(uap->buf, (u_int)uap->len, B_READ) == 0) {
E 33
E 27
E 4
		u.u_error = EFAULT;
E 47
I 47
D 79
	msg.msg_accrights = 0;
E 79
D 72
	msg.msg_accrightslen = 0;
E 72
I 72
	msg.msg_control = 0;
I 79
	msg.msg_flags = 0;
E 79
E 72
D 80
	sendit(uap->s, &msg, uap->flags);
E 80
I 80
D 83
	RETURN (sendit(uap->s, &msg, uap->flags));
E 83
I 83
D 86
	RETURN (sendit(uap->s, &msg, uap->flags, retval));
E 86
I 86
D 89
	return (sendit(uap->s, &msg, uap->flags, retval));
E 89
I 89
D 104
	return (sendit(p, uap->s, &msg, uap->flags, retval));
E 104
I 104
	return (sendit(p, SCARG(uap, s), &msg, SCARG(uap, flags), retval));
E 104
E 89
E 86
E 83
E 80
}

I 79
D 81
#define MSG_OSENDMSG	0x8000
E 81
I 81
#define MSG_COMPAT	0x8000
I 95
D 104
struct osendmsg_args {
	int	s;
	caddr_t	msg;
	int	flags;
};
E 95
E 81
E 79
I 72
D 83
osendmsg()
{
	register struct a {
E 83
I 83
D 89
/* ARGSUSED */
E 89
osendmsg(p, uap, retval)
E 104
I 104
int
compat_43_sendmsg(p, uap, retval)
E 104
	struct proc *p;
D 95
	register struct args {
E 83
		int	s;
		caddr_t	msg;
		int	flags;
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	register struct osendmsg_args *uap;
E 95
	int *retval;
E 104
I 104
	register struct compat_43_sendmsg_args /* {
		syscallarg(int) s;
		syscallarg(caddr_t) msg;
		syscallarg(int) flags;
	} */ *uap;
	register_t *retval;
E 104
{
E 83
	struct msghdr msg;
D 82
	struct iovec aiov[MSG_MAXIOVLEN];
E 82
I 82
	struct iovec aiov[UIO_SMALLIOV], *iov;
E 82
I 80
	int error;
E 80

D 80
	u.u_error = copyin(uap->msg, (caddr_t)&msg, sizeof (struct omsghdr));
	if (u.u_error)
		return;
	if ((u_int)msg.msg_iovlen >= sizeof (aiov) / sizeof (aiov[0])) {
		u.u_error = EMSGSIZE;
		return;
	}
	u.u_error = copyin((caddr_t)msg.msg_iov, (caddr_t)aiov,
		(unsigned)(msg.msg_iovlen * sizeof (aiov[0])));
	if (u.u_error)
		return;
E 80
I 80
D 104
	if (error = copyin(uap->msg, (caddr_t)&msg, sizeof (struct omsghdr)))
E 104
I 104
	if (error = copyin(SCARG(uap, msg), (caddr_t)&msg,
	    sizeof (struct omsghdr)))
E 104
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
D 82
	if ((u_int)msg.msg_iovlen >= sizeof (aiov) / sizeof (aiov[0]))
		RETURN (EMSGSIZE);
	if (error = copyin((caddr_t)msg.msg_iov, (caddr_t)aiov,
	    (unsigned)(msg.msg_iovlen * sizeof (aiov[0]))))
		RETURN (error);
E 82
I 82
	if ((u_int)msg.msg_iovlen >= UIO_SMALLIOV) {
		if ((u_int)msg.msg_iovlen >= UIO_MAXIOV)
D 86
			RETURN (EMSGSIZE);
E 86
I 86
			return (EMSGSIZE);
E 86
		MALLOC(iov, struct iovec *,
		      sizeof(struct iovec) * (u_int)msg.msg_iovlen, M_IOV, 
		      M_WAITOK);
	} else
		iov = aiov;
	if (error = copyin((caddr_t)msg.msg_iov, (caddr_t)iov,
	    (unsigned)(msg.msg_iovlen * sizeof (struct iovec))))
		goto done;
E 82
E 80
D 79
	msg.msg_control = 0;
	msg.msg_controllen = 0;
E 79
I 79
D 81
	msg.msg_flags = MSG_OSENDMSG;
E 81
I 81
	msg.msg_flags = MSG_COMPAT;
E 81
E 79
D 80
	sendit(uap->s, &msg, uap->flags);
E 80
I 80
D 82
	RETURN (sendit(uap->s, &msg, uap->flags));
E 82
I 82
	msg.msg_iov = iov;
D 83
	error = sendit(uap->s, &msg, uap->flags);
E 83
I 83
D 89
	error = sendit(uap->s, &msg, uap->flags, retval);
E 89
I 89
D 104
	error = sendit(p, uap->s, &msg, uap->flags, retval);
E 104
I 104
	error = sendit(p, SCARG(uap, s), &msg, SCARG(uap, flags), retval);
E 104
E 89
E 83
done:
	if (iov != aiov)
		FREE(iov, M_IOV);
D 86
	RETURN (error);
E 86
I 86
	return (error);
E 86
E 82
E 80
}
#endif

I 95
D 104
struct sendmsg_args {
	int	s;
	caddr_t	msg;
	int	flags;
};
E 104
I 104
int
E 104
E 95
E 72
D 83
sendmsg()
{
	register struct a {
E 83
I 83
D 89
/* ARGSUSED */
E 89
sendmsg(p, uap, retval)
	struct proc *p;
D 95
	register struct args {
E 83
		int	s;
		caddr_t	msg;
		int	flags;
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	register struct sendmsg_args *uap;
E 95
	int *retval;
E 104
I 104
	register struct sendmsg_args /* {
		syscallarg(int) s;
		syscallarg(caddr_t) msg;
		syscallarg(int) flags;
	} */ *uap;
	register_t *retval;
E 104
{
E 83
	struct msghdr msg;
D 82
	struct iovec aiov[MSG_MAXIOVLEN];
E 82
I 82
	struct iovec aiov[UIO_SMALLIOV], *iov;
E 82
I 80
	int error;
E 80

D 78
	u.u_error = copyin(uap->msg, (caddr_t)&msg, sizeof (msg));
	if (u.u_error)
E 78
I 78
D 80
	if (u.u_error = copyin(uap->msg, (caddr_t)&msg, sizeof (msg)))
E 78
E 47
		return;
I 47
	if ((u_int)msg.msg_iovlen >= sizeof (aiov) / sizeof (aiov[0])) {
		u.u_error = EMSGSIZE;
		return;
E 47
	}
E 80
I 80
D 104
	if (error = copyin(uap->msg, (caddr_t)&msg, sizeof (msg)))
E 104
I 104
	if (error = copyin(SCARG(uap, msg), (caddr_t)&msg, sizeof (msg)))
E 104
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
D 82
	if ((u_int)msg.msg_iovlen >= sizeof (aiov) / sizeof (aiov[0]))
		RETURN (EMSGSIZE);
E 82
I 82
	if ((u_int)msg.msg_iovlen >= UIO_SMALLIOV) {
		if ((u_int)msg.msg_iovlen >= UIO_MAXIOV)
D 86
			RETURN (EMSGSIZE);
E 86
I 86
			return (EMSGSIZE);
E 86
		MALLOC(iov, struct iovec *,
		       sizeof(struct iovec) * (u_int)msg.msg_iovlen, M_IOV,
		       M_WAITOK);
	} else
		iov = aiov;
E 82
E 80
I 47
D 72
	u.u_error =
	    copyin((caddr_t)msg.msg_iov, (caddr_t)aiov,
E 72
I 72
D 78
	u.u_error = copyin((caddr_t)msg.msg_iov, (caddr_t)aiov,
E 72
		(unsigned)(msg.msg_iovlen * sizeof (aiov[0])));
E 47
D 4
	receive(fp->f_socket, uap->ain ? &in : 0);
E 4
I 4
D 23
	u.u_error = soreceive(fp->f_socket, uap->asa ? &sa : 0);
E 23
I 23
D 27
	u.u_error = soreceive(fp->f_socket, uap->asa ? &sa : 0, &auio);
E 27
E 23
	if (u.u_error)
E 78
I 78
	if (msg.msg_iovlen &&
D 80
	    (u.u_error = copyin((caddr_t)msg.msg_iov, (caddr_t)aiov,
				(unsigned)(msg.msg_iovlen * sizeof (aiov[0])))))
E 78
		return;
E 80
I 80
D 82
	    (error = copyin((caddr_t)msg.msg_iov, (caddr_t)aiov,
	    (unsigned)(msg.msg_iovlen * sizeof (aiov[0])))))
		RETURN (error);
E 80
D 27
	if (uap->asa)
		(void) copyout((caddr_t)&sa, (caddr_t)uap->asa, sizeof (sa));
I 11
D 24
	u.u_r.r_val1 = uap->count - u.u_count;
E 24
I 24
	u.u_r.r_val1 = uap->count - auio.uio_resid;
E 27
I 27
D 30
	u.u_error = sosend(fp->f_socket, (struct mbuf *)0, &auio);
E 30
I 30
D 47
	u.u_error = sosend(fp->f_socket, (struct mbuf *)0, &auio, uap->flags);
I 38
	u.u_r.r_val1 = uap->len - auio.uio_resid;
E 47
I 47
	msg.msg_iov = aiov;
E 82
I 82
	    (error = copyin((caddr_t)msg.msg_iov, (caddr_t)iov,
	    (unsigned)(msg.msg_iovlen * sizeof (struct iovec)))))
		goto done;
	msg.msg_iov = iov;
E 82
I 79
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
E 93
	msg.msg_flags = 0;
#endif
E 79
D 62
#ifdef notdef
printf("sendmsg name %x namelen %d iov %x iovlen %d accrights %x &len %d\n",
msg.msg_name, msg.msg_namelen, msg.msg_iov, msg.msg_iovlen,
msg.msg_accrights, msg.msg_accrightslen);
#endif
E 62
D 80
	sendit(uap->s, &msg, uap->flags);
E 80
I 80
D 82
	RETURN (sendit(uap->s, &msg, uap->flags));
E 82
I 82
D 83
	error = sendit(uap->s, &msg, uap->flags);
E 83
I 83
D 89
	error = sendit(uap->s, &msg, uap->flags, retval);
E 89
I 89
D 104
	error = sendit(p, uap->s, &msg, uap->flags, retval);
E 104
I 104
	error = sendit(p, SCARG(uap, s), &msg, SCARG(uap, flags), retval);
E 104
E 89
E 83
done:
	if (iov != aiov)
		FREE(iov, M_IOV);
D 86
	RETURN (error);
E 86
I 86
	return (error);
E 86
E 82
E 80
E 47
E 38
E 30
E 27
E 24
E 11
E 4
}
I 6

I 104
int
E 104
I 47
D 83
sendit(s, mp, flags)
E 83
I 83
D 89
sendit(s, mp, flags, retsize)
E 89
I 89
sendit(p, s, mp, flags, retsize)
	register struct proc *p;
E 89
E 83
	int s;
	register struct msghdr *mp;
D 83
	int flags;
E 83
I 83
D 104
	int flags, *retsize;
E 104
I 104
	int flags;
	register_t *retsize;
E 104
E 83
{
D 89
	register struct file *fp;
E 89
I 89
	struct file *fp;
E 89
	struct uio auio;
	register struct iovec *iov;
	register int i;
D 72
	struct mbuf *to, *rights;
E 72
I 72
D 79
	struct mbuf *to, *rights, *control;
E 79
I 79
	struct mbuf *to, *control;
E 79
E 72
D 80
	int len;
E 80
I 80
	int len, error;
I 82
#ifdef KTRACE
	struct iovec *ktriov = NULL;
#endif
E 82
E 80
	
D 80
	fp = getsock(s);
E 80
I 80
D 89
	fp = getsock(s, &error);
E 80
	if (fp == 0)
E 89
I 89
	if (error = getsock(p->p_fd, s, &fp))
E 89
D 80
		return;
E 80
I 80
		return (error);
E 80
	auio.uio_iov = mp->msg_iov;
	auio.uio_iovcnt = mp->msg_iovlen;
D 52
	auio.uio_segflg = 0;
E 52
I 52
	auio.uio_segflg = UIO_USERSPACE;
I 77
	auio.uio_rw = UIO_WRITE;
I 91
	auio.uio_procp = p;
E 91
E 77
E 52
	auio.uio_offset = 0;			/* XXX */
	auio.uio_resid = 0;
	iov = mp->msg_iov;
D 62
	for (i = 0; i < mp->msg_iovlen; i++) {
E 62
I 62
	for (i = 0; i < mp->msg_iovlen; i++, iov++) {
E 62
D 80
		if (iov->iov_len < 0) {
			u.u_error = EINVAL;
			return;
		}
E 80
I 80
D 103
		if (iov->iov_len < 0)
E 103
I 103
		if (auio.uio_resid + iov->iov_len < auio.uio_resid)
E 103
			return (EINVAL);
E 80
I 51
D 81
		if (iov->iov_len == 0)
			continue;
E 51
D 80
		if (useracc(iov->iov_base, (u_int)iov->iov_len, B_READ) == 0) {
			u.u_error = EFAULT;
			return;
		}
E 80
I 80
		if (useracc(iov->iov_base, (u_int)iov->iov_len, B_READ) == 0)
			return (EFAULT);
E 80
		auio.uio_resid += iov->iov_len;
E 81
I 81
D 103
		if ((auio.uio_resid += iov->iov_len) < 0)
			return (EINVAL);
E 103
I 103
		auio.uio_resid += iov->iov_len;
E 103
E 81
D 62
		iov++;
E 62
	}
	if (mp->msg_name) {
D 80
		u.u_error =
D 57
		    sockargs(&to, mp->msg_name, mp->msg_namelen);
E 57
I 57
		    sockargs(&to, mp->msg_name, mp->msg_namelen, MT_SONAME);
E 57
		if (u.u_error)
			return;
E 80
I 80
		if (error = sockargs(&to, mp->msg_name, mp->msg_namelen,
		    MT_SONAME))
			return (error);
E 80
	} else
		to = 0;
D 79
	if (mp->msg_accrights) {
		u.u_error =
D 57
		    sockargs(&rights, mp->msg_accrights, mp->msg_accrightslen);
E 57
I 57
		    sockargs(&rights, mp->msg_accrights, mp->msg_accrightslen,
		    MT_RIGHTS);
E 57
		if (u.u_error)
			goto bad;
	} else
		rights = 0;
E 79
I 72
	if (mp->msg_control) {
I 81
		if (mp->msg_controllen < sizeof(struct cmsghdr)
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
E 93
D 88
		    && mp->msg_flags != MSG_COMPAT)
E 88
I 88
		    && mp->msg_flags != MSG_COMPAT
E 88
#endif
D 88
		{
E 88
I 88
		) {
E 88
			error = EINVAL;
			goto bad;
		}
E 81
D 80
		u.u_error =
		    sockargs(&control, mp->msg_control, mp->msg_controllen,
		    MT_CONTROL);
		if (u.u_error)
E 80
I 80
		if (error = sockargs(&control, mp->msg_control,
		    mp->msg_controllen, MT_CONTROL))
E 80
			goto bad;
I 79
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
E 93
D 81
		if (mp->msg_flags) {
E 81
I 81
		if (mp->msg_flags == MSG_COMPAT) {
E 81
			register struct cmsghdr *cm;
I 80

E 80
			M_PREPEND(control, sizeof(*cm), M_WAIT);
D 80
			if (control == 0)
				u.u_error = ENOBUFS;
			else {
E 80
I 80
			if (control == 0) {
				error = ENOBUFS;
				goto bad;
			} else {
E 80
				cm = mtod(control, struct cmsghdr *);
				cm->cmsg_len = control->m_len;
				cm->cmsg_level = SOL_SOCKET;
				cm->cmsg_type = SCM_RIGHTS;
			}
		}
#endif
E 79
	} else
		control = 0;
I 82
#ifdef KTRACE
D 89
	if (KTRPOINT(u.u_procp, KTR_GENIO)) {
E 89
I 89
	if (KTRPOINT(p, KTR_GENIO)) {
E 89
		int iovlen = auio.uio_iovcnt * sizeof (struct iovec);

		MALLOC(ktriov, struct iovec *, iovlen, M_TEMP, M_WAITOK);
		bcopy((caddr_t)auio.uio_iov, (caddr_t)ktriov, iovlen);
	}
#endif
E 82
E 72
	len = auio.uio_resid;
D 72
	u.u_error =
	    sosend((struct socket *)fp->f_data, to, &auio, flags, rights);
E 72
I 72
D 79
	if (setjmp(&u.u_qsave)) {			/* XXX */
		if (auio.uio_resid == len) {
			if ((u.u_sigintr & sigmask(u.u_procp->p_cursig)) != 0)
				u.u_error = EINTR;
			else
				u.u_eosys = RESTARTSYS;
I 78
			return;
E 78
		}
	} else
		u.u_error = sosend((struct socket *)fp->f_data, to, &auio,
		    flags, rights, control);
E 79
I 79
D 80
	u.u_error = sosend((struct socket *)fp->f_data, to, &auio,
	    flags, control);
	if ((u.u_error == EINTR || u.u_error == ERESTART ||
	    u.u_error == EWOULDBLOCK) && auio.uio_resid != len)
		u.u_error = 0;
E 79
E 72
	u.u_r.r_val1 = len - auio.uio_resid;
E 80
I 80
	if (error = sosend((struct socket *)fp->f_data, to, &auio,
D 81
	    flags, control)) {
E 81
I 81
	    (struct mbuf *)0, control, flags)) {
E 81
		if (auio.uio_resid != len && (error == ERESTART ||
		    error == EINTR || error == EWOULDBLOCK))
			error = 0;
		if (error == EPIPE)
D 89
			psignal(u.u_procp, SIGPIPE);
E 89
I 89
			psignal(p, SIGPIPE);
E 89
D 82
	} else
E 82
I 82
	}
	if (error == 0)
E 82
D 83
		u.u_r.r_val1 = len - auio.uio_resid;
E 83
I 83
		*retsize = len - auio.uio_resid;
E 83
I 82
#ifdef KTRACE
	if (ktriov != NULL) {
		if (error == 0)
D 89
			ktrgenio(u.u_procp->p_tracep, s, UIO_WRITE,
E 89
I 89
			ktrgenio(p->p_tracep, s, UIO_WRITE,
E 89
D 83
				ktriov, u.u_r.r_val1);
E 83
I 83
D 85
				ktriov, *retsize);
E 85
I 85
				ktriov, *retsize, error);
E 85
E 83
		FREE(ktriov, M_TEMP);
	}
#endif
E 82
E 80
I 79
D 81
	if (control)
		m_freem(control);
E 81
E 79
I 72
bad:
E 72
D 79
	if (rights)
		m_freem(rights);
E 79
D 72
bad:
E 72
	if (to)
		m_freem(to);
I 80
	return (error);
E 80
I 72
D 79
	if (control)
		m_freem(control);
E 79
E 72
}

I 95
D 104
struct recvfrom_args {
	int	s;
	caddr_t	buf;
D 101
	int	len;
E 101
I 101
	size_t	len;
E 101
	int	flags;
	caddr_t	from;
	int	*fromlenaddr;
};

E 104
E 95
I 73
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
E 93
E 73
E 47
I 27
D 81
recvfrom()
{
I 73
D 80
	recvfrom1(0);
E 80
I 80
	struct a {
		int	s;
		caddr_t	buf;
		int	len;
		int	flags;
		caddr_t	from;
		int	*fromlenaddr;
		int	compat_43;
	};

	((struct a *)u.u_ap)->compat_43 = 0;
	RETURN (recvfrom1());
E 80
}

E 81
D 83
orecvfrom()
{
D 80
	recvfrom1(1);
E 80
I 80
	struct a {
E 83
I 83
D 104
orecvfrom(p, uap, retval)
E 104
I 104
int
compat_43_recvfrom(p, uap, retval)
E 104
	struct proc *p;
D 95
	struct args {
E 83
		int	s;
		caddr_t	buf;
		int	len;
		int	flags;
		caddr_t	from;
		int	*fromlenaddr;
D 81
		int	compat_43;
E 81
D 83
	};
E 83
I 83
	} *uap;
E 95
I 95
D 104
	struct recvfrom_args *uap;
E 95
	int *retval;
E 104
I 104
	struct recvfrom_args /* {
		syscallarg(int) s;
		syscallarg(caddr_t) buf;
		syscallarg(size_t) len;
		syscallarg(int) flags;
		syscallarg(caddr_t) from;
		syscallarg(int *) fromlenaddr;
	} */ *uap;
	register_t *retval;
E 104
{
E 83

D 81
	((struct a *)u.u_ap)->compat_43 = 1;
	RETURN (recvfrom1());
E 81
I 81
D 83
	((struct a *)u.u_ap)->flags |= MSG_COMPAT;
	RETURN (recvfrom());
E 83
I 83
D 104
	uap->flags |= MSG_COMPAT;
E 104
I 104
	SCARG(uap, flags) |= MSG_COMPAT;
E 104
D 86
	RETURN (recvfrom(p, uap, retval));
E 86
I 86
	return (recvfrom(p, uap, retval));
E 86
E 83
E 81
E 80
}
I 80
D 81
#else /* COMPAT_43 */
E 80

D 80
recvfrom1(compat_43)
{	/* vi will want an extra } to be happy! */
#else
recvfrom()
{
	int compat_43 = 0;
E 80
I 80
#define	recvfrom1	recvfrom
E 81
E 80
#endif
I 80

I 104
int
E 104
D 81
recvfrom1()
E 81
I 81
D 83
recvfrom()
E 81
{
E 80
E 73
	register struct a {
E 83
I 83
D 89
/* ARGSUSED */
E 89
recvfrom(p, uap, retval)
	struct proc *p;
D 95
	register struct args {
E 83
		int	s;
		caddr_t	buf;
		int	len;
		int	flags;
		caddr_t	from;
		int	*fromlenaddr;
I 80
D 81
#ifdef COMPAT_43
		int	compat_43;
#endif
E 81
E 80
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	register struct recvfrom_args *uap;
E 95
	int *retval;
E 104
I 104
	register struct recvfrom_args /* {
		syscallarg(int) s;
		syscallarg(caddr_t) buf;
		syscallarg(size_t) len;
		syscallarg(int) flags;
		syscallarg(caddr_t) from;
		syscallarg(int *) fromlenaddr;
	} */ *uap;
	register_t *retval;
E 104
{
E 83
D 47
	register struct file *fp;
	struct uio auio;
E 47
I 47
	struct msghdr msg;
E 47
	struct iovec aiov;
D 47
	struct mbuf *from;
	int fromlen;
E 47
I 47
D 80
	int len;
E 80
I 80
D 81
	int len, error;
E 81
I 81
	int error;
E 81
E 80
E 47

D 40
	if (copyin((caddr_t)uap->fromlenaddr, (caddr_t)&fromlen, sizeof (fromlen))) {
		u.u_error = EFAULT;
E 40
I 40
D 47
	u.u_error = copyin((caddr_t)uap->fromlenaddr, (caddr_t)&fromlen,
		sizeof (fromlen));
E 47
I 47
D 72
	u.u_error = copyin((caddr_t)uap->fromlenaddr, (caddr_t)&len,
	   sizeof (len));
E 47
	if (u.u_error)
E 40
		return;
E 72
I 72
D 104
	if (uap->fromlenaddr) {
D 80
		u.u_error = copyin((caddr_t)uap->fromlenaddr, (caddr_t)&len,
		   sizeof (len));
		if (u.u_error)
			return;
E 80
I 80
D 81
		if (error = copyin((caddr_t)uap->fromlenaddr, (caddr_t)&len,
		   sizeof (len)))
E 81
I 81
		if (error = copyin((caddr_t)uap->fromlenaddr,
E 104
I 104
	if (SCARG(uap, fromlenaddr)) {
		if (error = copyin((caddr_t)SCARG(uap, fromlenaddr),
E 104
		    (caddr_t)&msg.msg_namelen, sizeof (msg.msg_namelen)))
E 81
D 83
			return (error);
E 83
I 83
D 86
			RETURN (error);
E 86
I 86
			return (error);
E 86
E 83
E 80
	} else
D 81
		len = 0;
E 81
I 81
		msg.msg_namelen = 0;
E 81
E 72
D 40
	}
E 40
D 47
	fp = getf(uap->s);
	if (fp == 0)
		return;
	if (fp->f_type != DTYPE_SOCKET) {
		u.u_error = ENOTSOCK;
		return;
	}
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
E 47
I 47
D 104
	msg.msg_name = uap->from;
E 104
I 104
	msg.msg_name = SCARG(uap, from);
E 104
D 81
	msg.msg_namelen = len;
E 81
	msg.msg_iov = &aiov;
	msg.msg_iovlen = 1;
E 47
D 104
	aiov.iov_base = uap->buf;
	aiov.iov_len = uap->len;
E 104
I 104
	aiov.iov_base = SCARG(uap, buf);
	aiov.iov_len = SCARG(uap, len);
E 104
D 47
	auio.uio_resid = uap->len;
	auio.uio_segflg = 0;
	auio.uio_offset = 0;	/* XXX */
D 33
	if (useracc(uap->buf, uap->len, B_WRITE) == 0)  {
E 33
I 33
	if (useracc(uap->buf, (u_int)uap->len, B_WRITE) == 0)  {
E 33
		u.u_error = EFAULT;
		return;
	}
	from = 0;
D 30
	u.u_error = soreceive(fp->f_socket, &from, &auio);
E 30
I 30
	u.u_error = soreceive(fp->f_socket, &from, &auio, uap->flags);
E 30
	if (u.u_error)
		goto bad;
	if (from == 0)
		fromlen = 0;
	else {
		if (fromlen > from->m_len)
			fromlen = from->m_len;
D 33
		if (copyout(mtod(from, caddr_t), uap->from, fromlen)) {
E 33
I 33
D 40
		if (copyout(mtod(from, caddr_t), uap->from, (u_int)fromlen)) {
E 33
			u.u_error = EFAULT;
E 40
I 40
		u.u_error = copyout(mtod(from, caddr_t), uap->from,
			(u_int)fromlen);
		if (u.u_error)
E 40
			goto bad;
D 40
		}
E 40
	}
D 40
	if (copyout((caddr_t)&fromlen, (caddr_t)uap->fromlenaddr,
	    sizeof (fromlen))) {
		u.u_error = EFAULT;
E 40
I 40
	u.u_error = copyout((caddr_t)&fromlen, (caddr_t)uap->fromlenaddr,
	    sizeof (fromlen));
	if (u.u_error)
E 40
		goto bad;
D 40
	}
E 40
	u.u_r.r_val1 = uap->len - auio.uio_resid;
bad:
	if (from)
		m_freem(from);
E 47
I 47
D 79
	msg.msg_accrights = 0;
E 79
D 72
	msg.msg_accrightslen = 0;
	recvit(uap->s, &msg, uap->flags, (caddr_t)uap->fromlenaddr, (caddr_t)0);
E 72
I 72
	msg.msg_control = 0;
D 81
	msg.msg_flags = uap->flags;
D 73
	recvit(uap->s, &msg, (caddr_t)uap->fromlenaddr, (caddr_t)0, (caddr_t)0);
E 73
I 73
D 74
	recvit(uap->s, &msg, (caddr_t)uap->fromlenaddr,
				(caddr_t)0, (caddr_t)0, compat_43);
E 74
I 74
D 80
	recvit(uap->s, &msg, (caddr_t)uap->fromlenaddr, (caddr_t)0, compat_43);
E 80
I 80
	/* COMPAT_43 */
	return (recvit(uap->s, &msg, (caddr_t)uap->fromlenaddr, (caddr_t)0,
	    uap->compat_43));
E 81
I 81
D 82
	msg.msg_flags = uap->flags | MSG_COMPAT;
E 82
I 82
D 104
	msg.msg_flags = uap->flags;
E 82
D 83
	return (recvit(uap->s, &msg, (caddr_t)uap->fromlenaddr));
E 83
I 83
D 86
	RETURN (recvit(uap->s, &msg, (caddr_t)uap->fromlenaddr, retval));
E 86
I 86
D 89
	return (recvit(uap->s, &msg, (caddr_t)uap->fromlenaddr, retval));
E 89
I 89
	return (recvit(p, uap->s, &msg, (caddr_t)uap->fromlenaddr, retval));
E 104
I 104
	msg.msg_flags = SCARG(uap, flags);
	return (recvit(p, SCARG(uap, s), &msg,
	    (caddr_t)SCARG(uap, fromlenaddr), retval));
E 104
E 89
E 86
E 83
E 81
E 80
E 74
E 73
E 72
E 47
D 42
	return;
E 42
}
I 80

E 80
D 73

E 73
D 72
recv()
E 72
I 72
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
I 95
D 104
struct orecv_args {
	int	s;
	caddr_t	buf;
	int	len;
	int	flags;
};
E 95
E 93
D 73
orecvfrom()
E 72
{
I 72
	return (recvfrom());
}

E 73
D 83
orecv()
{
E 72
	register struct a {
E 83
I 83
D 89
/* ARGSUSED */
E 89
orecv(p, uap, retval)
E 104
I 104
int
compat_43_recv(p, uap, retval)
E 104
	struct proc *p;
D 95
	register struct args {
E 83
		int	s;
		caddr_t	buf;
		int	len;
		int	flags;
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	register struct orecv_args *uap;
E 95
	int *retval;
E 104
I 104
	register struct compat_43_recv_args /* {
		syscallarg(int) s;
		syscallarg(caddr_t) buf;
		syscallarg(int) len;
		syscallarg(int) flags;
	} */ *uap;
	register_t *retval;
E 104
{
E 83
D 47
	register struct file *fp;
	struct uio auio;
E 47
I 47
	struct msghdr msg;
E 47
	struct iovec aiov;

D 47
	fp = getf(uap->s);
	if (fp == 0)
		return;
	if (fp->f_type != DTYPE_SOCKET) {
		u.u_error = ENOTSOCK;
		return;
	}
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
E 47
I 47
	msg.msg_name = 0;
	msg.msg_namelen = 0;
	msg.msg_iov = &aiov;
	msg.msg_iovlen = 1;
E 47
D 104
	aiov.iov_base = uap->buf;
	aiov.iov_len = uap->len;
E 104
I 104
	aiov.iov_base = SCARG(uap, buf);
	aiov.iov_len = SCARG(uap, len);
E 104
D 47
	auio.uio_resid = uap->len;
	auio.uio_segflg = 0;
	auio.uio_offset = 0;	/* XXX */
D 33
	if (useracc(uap->buf, uap->len, B_WRITE) == 0)  {
E 33
I 33
	if (useracc(uap->buf, (u_int)uap->len, B_WRITE) == 0)  {
E 33
		u.u_error = EFAULT;
		return;
	}
D 30
	u.u_error = soreceive(fp->f_socket, (struct mbuf *)0, &auio);
E 30
I 30
D 33
	u.u_error = soreceive(fp->f_socket, (struct mbuf *)0, &auio, uap->flags);
E 33
I 33
	u.u_error =
	    soreceive(fp->f_socket, (struct mbuf **)0, &auio, uap->flags);
E 33
E 30
	u.u_r.r_val1 = uap->len - auio.uio_resid;
E 47
I 47
D 78
	msg.msg_accrights = 0;
E 78
D 72
	msg.msg_accrightslen = 0;
	recvit(uap->s, &msg, uap->flags, (caddr_t)0, (caddr_t)0);
E 72
I 72
	msg.msg_control = 0;
D 104
	msg.msg_flags = uap->flags;
D 73
	recvit(uap->s, &msg, (caddr_t)0, (caddr_t)0, (caddr_t)0);
E 73
I 73
D 74
	recvit(uap->s, &msg, (caddr_t)0, (caddr_t)0, (caddr_t)0, 0);
E 74
I 74
D 80
	recvit(uap->s, &msg, (caddr_t)0, (caddr_t)0, 0);
E 80
I 80
D 81
	RETURN (recvit(uap->s, &msg, (caddr_t)0, (caddr_t)0, 0));
E 81
I 81
D 83
	RETURN (recvit(uap->s, &msg, (caddr_t)0));
E 83
I 83
D 86
	RETURN (recvit(uap->s, &msg, (caddr_t)0, retval));
E 86
I 86
D 89
	return (recvit(uap->s, &msg, (caddr_t)0, retval));
E 89
I 89
	return (recvit(p, uap->s, &msg, (caddr_t)0, retval));
E 104
I 104
	msg.msg_flags = SCARG(uap, flags);
	return (recvit(p, SCARG(uap, s), &msg, (caddr_t)0, retval));
E 104
E 89
E 86
E 83
E 81
E 80
E 74
E 73
E 72
E 47
}

I 81
/*
 * Old recvmsg.  This code takes advantage of the fact that the old msghdr
 * overlays the new one, missing only the flags, and with the (old) access
 * rights where the control fields are now.
 */
I 95
D 104
struct orecvmsg_args {
	int	s;
	struct	omsghdr *msg;
	int	flags;
};
E 95
E 81
I 72
D 83
orecvmsg()
{
	register struct a {
E 83
I 83
D 89
/* ARGSUSED */
E 89
orecvmsg(p, uap, retval)
E 104
I 104
int
compat_43_recvmsg(p, uap, retval)
E 104
	struct proc *p;
D 95
	register struct args {
E 83
		int	s;
		struct	omsghdr *msg;
		int	flags;
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	register struct orecvmsg_args *uap;
E 95
	int *retval;
E 104
I 104
	register struct compat_43_recvmsg_args /* {
		syscallarg(int) s;
		syscallarg(struct omsghdr *) msg;
		syscallarg(int) flags;
	} */ *uap;
	register_t *retval;
E 104
{
E 83
	struct msghdr msg;
D 82
	struct iovec aiov[MSG_MAXIOVLEN];
E 82
I 82
	struct iovec aiov[UIO_SMALLIOV], *iov;
E 82
I 80
	int error;
E 80

D 80
	u.u_error = copyin((caddr_t)uap->msg, (caddr_t)&msg,
	    sizeof (struct omsghdr));
	if (u.u_error)
		return;
	if ((u_int)msg.msg_iovlen >= sizeof (aiov) / sizeof (aiov[0])) {
		u.u_error = EMSGSIZE;
		return;
	}
E 80
I 80
D 104
	if (error = copyin((caddr_t)uap->msg, (caddr_t)&msg,
E 104
I 104
	if (error = copyin((caddr_t)SCARG(uap, msg), (caddr_t)&msg,
E 104
	    sizeof (struct omsghdr)))
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
D 82
	if ((u_int)msg.msg_iovlen >= sizeof (aiov) / sizeof (aiov[0]))
		RETURN (EMSGSIZE);
E 82
I 82
	if ((u_int)msg.msg_iovlen >= UIO_SMALLIOV) {
		if ((u_int)msg.msg_iovlen >= UIO_MAXIOV)
D 86
			RETURN (EMSGSIZE);
E 86
I 86
			return (EMSGSIZE);
E 86
		MALLOC(iov, struct iovec *,
		      sizeof(struct iovec) * (u_int)msg.msg_iovlen, M_IOV,
		      M_WAITOK);
	} else
		iov = aiov;
E 82
E 80
D 79
	msg.msg_control = 0;
E 79
D 81
	msg.msg_flags = uap->flags;
E 81
I 81
D 104
	msg.msg_flags = uap->flags | MSG_COMPAT;
E 104
I 104
	msg.msg_flags = SCARG(uap, flags) | MSG_COMPAT;
E 104
E 81
D 80
	u.u_error = copyin((caddr_t)msg.msg_iov, (caddr_t)aiov,
		(unsigned)(msg.msg_iovlen * sizeof (aiov[0])));
	if (u.u_error)
		return;
E 80
I 80
D 82
	if (error = copyin((caddr_t)msg.msg_iov, (caddr_t)aiov,
	    (unsigned)(msg.msg_iovlen * sizeof (aiov[0]))))
		RETURN (error);
E 80
	msg.msg_iov = aiov;
E 82
I 82
	if (error = copyin((caddr_t)msg.msg_iov, (caddr_t)iov,
	    (unsigned)(msg.msg_iovlen * sizeof (struct iovec))))
		goto done;
	msg.msg_iov = iov;
E 82
D 79
	if (msg.msg_accrights)
		if (useracc((caddr_t)msg.msg_accrights,
		    (unsigned)msg.msg_accrightslen, B_WRITE) == 0) {
			u.u_error = EFAULT;
			return;
E 79
I 79
D 80
	if (msg.msg_control)
		if (useracc((caddr_t)msg.msg_control,
		    (unsigned)msg.msg_controllen, B_WRITE) == 0) {
			    u.u_error = EFAULT;
			    return;
E 79
		}
E 80
I 80
D 81
	if (msg.msg_control && useracc((caddr_t)msg.msg_control,
	    (unsigned)msg.msg_controllen, B_WRITE) == 0)
		RETURN (EFAULT);
E 80
	    
D 80
	recvit(uap->s, &msg, (caddr_t)&uap->msg->msg_namelen,
D 73
	    (caddr_t)&uap->msg->msg_accrightslen, (caddr_t)0);
E 73
I 73
D 74
	    (caddr_t)&uap->msg->msg_accrightslen, (caddr_t)0, /* compat_43 */1);
E 74
I 74
	    (caddr_t)&uap->msg->msg_accrightslen, /* compat_43 */1);
E 80
I 80
	RETURN (recvit(uap->s, &msg, (caddr_t)&uap->msg->msg_namelen,
	    (caddr_t)&uap->msg->msg_accrightslen, /* compat_43 */1));
E 81
I 81
D 83
	error = recvit(uap->s, &msg, (caddr_t)&uap->msg->msg_namelen);
E 83
I 83
D 89
	error = recvit(uap->s, &msg, (caddr_t)&uap->msg->msg_namelen, retval);
E 89
I 89
D 104
	error = recvit(p, uap->s, &msg, (caddr_t)&uap->msg->msg_namelen, retval);
E 104
I 104
	error = recvit(p, SCARG(uap, s), &msg,
	    (caddr_t)&SCARG(uap, msg)->msg_namelen, retval);
E 104
E 89
E 83

	if (msg.msg_controllen && error == 0)
		error = copyout((caddr_t)&msg.msg_controllen,
D 104
		    (caddr_t)&uap->msg->msg_accrightslen, sizeof (int));
E 104
I 104
		    (caddr_t)&SCARG(uap, msg)->msg_accrightslen, sizeof (int));
E 104
I 82
done:
	if (iov != aiov)
		FREE(iov, M_IOV);
E 82
D 86
	RETURN (error);
E 86
I 86
	return (error);
E 86
E 81
E 80
E 74
E 73
}
#endif

I 95
D 104
struct recvmsg_args {
	int	s;
	struct	msghdr *msg;
	int	flags;
};
E 104
I 104
int
E 104
E 95
E 72
D 47
sendmsg()
E 47
I 47
D 83
recvmsg()
E 47
{
I 47
	register struct a {
E 83
I 83
D 89
/* ARGSUSED */
E 89
recvmsg(p, uap, retval)
	struct proc *p;
D 95
	register struct args {
E 83
		int	s;
		struct	msghdr *msg;
		int	flags;
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	register struct recvmsg_args *uap;
E 95
	int *retval;
E 104
I 104
	register struct recvmsg_args /* {
		syscallarg(int) s;
		syscallarg(struct msghdr *) msg;
		syscallarg(int) flags;
	} */ *uap;
	register_t *retval;
E 104
{
E 83
	struct msghdr msg;
D 73
	struct iovec aiov[MSG_MAXIOVLEN];
E 73
I 73
D 82
	struct iovec aiov[MSG_MAXIOVLEN], *uiov;
E 82
I 82
	struct iovec aiov[UIO_SMALLIOV], *uiov, *iov;
E 82
I 78
D 80
	register int error1;
E 80
I 80
	register int error;
E 80
E 78
E 73
E 47

D 47
	u.u_error = EINVAL;
E 47
I 47
D 80
	u.u_error = copyin((caddr_t)uap->msg, (caddr_t)&msg, sizeof (msg));
	if (u.u_error)
		return;
	if ((u_int)msg.msg_iovlen >= sizeof (aiov) / sizeof (aiov[0])) {
		u.u_error = EMSGSIZE;
		return;
	}
E 80
I 80
D 104
	if (error = copyin((caddr_t)uap->msg, (caddr_t)&msg, sizeof (msg)))
E 104
I 104
	if (error = copyin((caddr_t)SCARG(uap, msg), (caddr_t)&msg,
	    sizeof (msg)))
E 104
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
D 82
	if ((u_int)msg.msg_iovlen >= sizeof (aiov) / sizeof (aiov[0]))
		RETURN (EMSGSIZE);
E 82
I 82
	if ((u_int)msg.msg_iovlen >= UIO_SMALLIOV) {
		if ((u_int)msg.msg_iovlen >= UIO_MAXIOV)
D 86
			RETURN (EMSGSIZE);
E 86
I 86
			return (EMSGSIZE);
E 86
		MALLOC(iov, struct iovec *,
		       sizeof(struct iovec) * (u_int)msg.msg_iovlen, M_IOV,
		       M_WAITOK);
	} else
		iov = aiov;
E 82
I 81
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
E 93
D 104
	msg.msg_flags = uap->flags &~ MSG_COMPAT;
E 104
I 104
	msg.msg_flags = SCARG(uap, flags) &~ MSG_COMPAT;
E 104
#else
E 81
E 80
D 72
	u.u_error =
	    copyin((caddr_t)msg.msg_iov, (caddr_t)aiov,
E 72
I 72
D 104
	msg.msg_flags = uap->flags;
E 104
I 104
	msg.msg_flags = SCARG(uap, flags);
E 104
I 81
#endif
E 81
D 79
	u.u_error = copyin((caddr_t)msg.msg_iov, (caddr_t)aiov,
E 79
I 79
	uiov = msg.msg_iov;
D 82
	msg.msg_iov = aiov;
D 80
	u.u_error = copyin((caddr_t)uiov, (caddr_t)aiov,
E 79
E 72
		(unsigned)(msg.msg_iovlen * sizeof (aiov[0])));
	if (u.u_error)
		return;
I 73
D 79
	uiov = msg.msg_iov;
E 73
	msg.msg_iov = aiov;
	if (msg.msg_accrights)
		if (useracc((caddr_t)msg.msg_accrights,
		    (unsigned)msg.msg_accrightslen, B_WRITE) == 0) {
			u.u_error = EFAULT;
			return;
		}
E 79
D 72
	recvit(uap->s, &msg, uap->flags,
	    (caddr_t)&uap->msg->msg_namelen,
	    (caddr_t)&uap->msg->msg_accrightslen);
E 72
I 72
	if (msg.msg_control)
		if (useracc((caddr_t)msg.msg_control,
		    (unsigned)msg.msg_controllen, B_WRITE) == 0) {
			u.u_error = EFAULT;
			return;
		}
D 73
	recvit(uap->s, &msg, (caddr_t)0, (caddr_t)0, (caddr_t)0);
	u.u_error = copyout((caddr_t)&msg, (caddr_t)uap->msg, sizeof (msg));
E 73
I 73
D 74
	recvit(uap->s, &msg, (caddr_t)0, (caddr_t)0, (caddr_t)0, 0);
E 74
I 74
	recvit(uap->s, &msg, (caddr_t)0, (caddr_t)0, 0);
E 74
	msg.msg_iov = uiov;
D 78
	u.u_error = copyout((caddr_t)&msg, (caddr_t)uap->msg, sizeof(msg));
E 78
I 78
	error1 = copyout((caddr_t)&msg, (caddr_t)uap->msg, sizeof(msg));
	if (error1 && u.u_error == 0)
		u.u_error = error1;
E 80
I 80
	if (error = copyin((caddr_t)uiov, (caddr_t)aiov,
	    (unsigned)(msg.msg_iovlen * sizeof (aiov[0]))))
		RETURN (error);
E 82
I 82
	msg.msg_iov = iov;
	if (error = copyin((caddr_t)uiov, (caddr_t)iov,
	    (unsigned)(msg.msg_iovlen * sizeof (struct iovec))))
		goto done;
E 82
D 81
	if (msg.msg_control && useracc((caddr_t)msg.msg_control,
	    (unsigned)msg.msg_controllen, B_WRITE) == 0)
		RETURN (EFAULT);
	if ((error = recvit(uap->s, &msg, (caddr_t)0, (caddr_t)0, 0)) == 0) {
E 81
I 81
D 83
	if ((error = recvit(uap->s, &msg, (caddr_t)0)) == 0) {
E 83
I 83
D 89
	if ((error = recvit(uap->s, &msg, (caddr_t)0, retval)) == 0) {
E 89
I 89
D 104
	if ((error = recvit(p, uap->s, &msg, (caddr_t)0, retval)) == 0) {
E 104
I 104
	if ((error = recvit(p, SCARG(uap, s), &msg, (caddr_t)0, retval)) == 0) {
E 104
E 89
E 83
E 81
		msg.msg_iov = uiov;
D 104
		error = copyout((caddr_t)&msg, (caddr_t)uap->msg, sizeof(msg));
E 104
I 104
		error = copyout((caddr_t)&msg, (caddr_t)SCARG(uap, msg),
		    sizeof(msg));
E 104
	}
I 82
done:
	if (iov != aiov)
		FREE(iov, M_IOV);
E 82
D 86
	RETURN (error);
E 86
I 86
	return (error);
E 86
E 80
E 78
E 73
E 72
E 47
}

I 104
int
E 104
I 77
D 80
/* ARGSUSED */
E 80
I 80
D 81
/* ARGSUSED COMPAT_43 */
E 80
E 77
D 47
recvmsg()
E 47
I 47
D 72
recvit(s, mp, flags, namelenp, rightslenp)
E 72
I 72
D 73
recvit(s, mp, namelenp, rightslenp, controllenp)
E 72
	int s;
E 73
I 73
D 74
recvit(s, mp, namelenp, rightslenp, controllenp, compat_43)
E 74
I 74
recvit(s, mp, namelenp, rightslenp, compat_43)
E 74
	int s, compat_43;
E 81
I 81
D 83
recvit(s, mp, namelenp)
E 83
I 83
D 89
recvit(s, mp, namelenp, retsize)
E 89
I 89
recvit(p, s, mp, namelenp, retsize)
	register struct proc *p;
E 89
E 83
	int s;
E 81
E 73
	register struct msghdr *mp;
D 72
	int flags;
	caddr_t namelenp, rightslenp;
E 72
I 72
D 74
	caddr_t namelenp, rightslenp, controllenp;
E 74
I 74
D 81
	caddr_t namelenp, rightslenp;
E 81
I 81
	caddr_t namelenp;
I 83
D 104
	int *retsize;
E 104
I 104
	register_t *retsize;
E 104
E 83
E 81
E 74
E 72
E 47
{
D 47

	u.u_error = EINVAL;
E 47
I 47
D 89
	register struct file *fp;
E 89
I 89
	struct file *fp;
E 89
	struct uio auio;
	register struct iovec *iov;
	register int i;
D 72
	struct mbuf *from, *rights;
E 72
D 80
	int len;
E 80
I 80
	int len, error;
E 80
I 72
D 81
	struct mbuf *from = 0, *rights = 0, *control = 0;
E 81
I 81
	struct mbuf *from = 0, *control = 0;
I 82
#ifdef KTRACE
	struct iovec *ktriov = NULL;
#endif
E 82
E 81
E 72
	
D 80
	fp = getsock(s);
E 80
I 80
D 89
	fp = getsock(s, &error);
E 80
	if (fp == 0)
E 89
I 89
	if (error = getsock(p->p_fd, s, &fp))
E 89
D 80
		return;
E 80
I 80
		return (error);
E 80
	auio.uio_iov = mp->msg_iov;
	auio.uio_iovcnt = mp->msg_iovlen;
D 52
	auio.uio_segflg = 0;
E 52
I 52
	auio.uio_segflg = UIO_USERSPACE;
I 77
	auio.uio_rw = UIO_READ;
I 91
	auio.uio_procp = p;
E 91
E 77
E 52
	auio.uio_offset = 0;			/* XXX */
	auio.uio_resid = 0;
	iov = mp->msg_iov;
D 62
	for (i = 0; i < mp->msg_iovlen; i++) {
E 62
I 62
	for (i = 0; i < mp->msg_iovlen; i++, iov++) {
E 62
D 80
		if (iov->iov_len < 0) {
			u.u_error = EINVAL;
			return;
		}
E 80
I 80
D 103
		if (iov->iov_len < 0)
E 103
I 103
		if (auio.uio_resid + iov->iov_len < auio.uio_resid)
E 103
			return (EINVAL);
E 80
I 51
D 81
		if (iov->iov_len == 0)
			continue;
E 51
D 80
		if (useracc(iov->iov_base, (u_int)iov->iov_len, B_WRITE) == 0) {
			u.u_error = EFAULT;
			return;
		}
E 80
I 80
		if (useracc(iov->iov_base, (u_int)iov->iov_len, B_WRITE) == 0)
			return (EFAULT);
E 80
		auio.uio_resid += iov->iov_len;
E 81
I 81
D 103
		if ((auio.uio_resid += iov->iov_len) < 0)
			return (EINVAL);
E 103
I 103
		auio.uio_resid += iov->iov_len;
E 103
E 81
D 62
		iov++;
E 62
	}
I 82
#ifdef KTRACE
D 89
	if (KTRPOINT(u.u_procp, KTR_GENIO)) {
E 89
I 89
	if (KTRPOINT(p, KTR_GENIO)) {
E 89
		int iovlen = auio.uio_iovcnt * sizeof (struct iovec);

		MALLOC(ktriov, struct iovec *, iovlen, M_TEMP, M_WAITOK);
		bcopy((caddr_t)auio.uio_iov, (caddr_t)ktriov, iovlen);
	}
#endif
E 82
	len = auio.uio_resid;
D 72
	u.u_error =
	    soreceive((struct socket *)fp->f_data, &from, &auio,
		flags, &rights);
E 72
I 72
D 79
	if (setjmp(&u.u_qsave)) {			/* XXX */
		if (auio.uio_resid == len) {
			if ((u.u_sigintr & sigmask(u.u_procp->p_cursig)) != 0)
				u.u_error = EINTR;
			else
				u.u_eosys = RESTARTSYS;
I 78
			return;
E 78
		}
	} else
		u.u_error = soreceive((struct socket *)fp->f_data, &from, &auio,
		    &mp->msg_flags, &rights, &control);
E 79
I 79
D 80
	u.u_error = soreceive((struct socket *)fp->f_data, &from, &auio,
	    &mp->msg_flags, &rights, &control);
	if ((u.u_error == EINTR || u.u_error == ERESTART ||
	    u.u_error == EWOULDBLOCK) && auio.uio_resid != len)
		u.u_error = 0;
E 80
I 80
	if (error = soreceive((struct socket *)fp->f_data, &from, &auio,
D 81
	    &mp->msg_flags, &rights, &control)) {
E 81
I 81
D 97
	    (struct mbuf **)0, &control, &mp->msg_flags)) {
E 97
I 97
	    (struct mbuf **)0, mp->msg_control ? &control : (struct mbuf **)0,
	    &mp->msg_flags)) {
E 97
E 81
		if (auio.uio_resid != len && (error == ERESTART ||
		    error == EINTR || error == EWOULDBLOCK))
			error = 0;
	}
I 82
#ifdef KTRACE
	if (ktriov != NULL) {
		if (error == 0)
D 89
			ktrgenio(u.u_procp->p_tracep, s, UIO_READ,
E 89
I 89
			ktrgenio(p->p_tracep, s, UIO_READ,
E 89
D 85
				ktriov, len - auio.uio_resid);
E 85
I 85
				ktriov, len - auio.uio_resid, error);
E 85
		FREE(ktriov, M_TEMP);
	}
#endif
E 82
	if (error)
		goto out;
E 80
E 79
E 72
D 83
	u.u_r.r_val1 = len - auio.uio_resid;
E 83
I 83
	*retsize = len - auio.uio_resid;
E 83
	if (mp->msg_name) {
		len = mp->msg_namelen;
		if (len <= 0 || from == 0)
			len = 0;
		else {
D 73
			if (len > from->m_len)
E 73
I 73
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
E 93
D 81
			if (compat_43)
E 81
I 81
			if (mp->msg_flags & MSG_COMPAT)
E 81
				mtod(from, struct osockaddr *)->sa_family =
				    mtod(from, struct sockaddr *)->sa_family;
#endif
D 81
			if (len > from->m_len)		/* ??? */
E 81
I 81
			if (len > from->m_len)
E 81
E 73
				len = from->m_len;
D 72
			(void) copyout((caddr_t)mtod(from, caddr_t),
E 72
I 72
D 81
			(void) copyout(mtod(from, caddr_t),
E 72
			    (caddr_t)mp->msg_name, (unsigned)len);
E 81
I 81
			/* else if len < from->m_len ??? */
			if (error = copyout(mtod(from, caddr_t),
			    (caddr_t)mp->msg_name, (unsigned)len))
				goto out;
E 81
		}
I 74
		mp->msg_namelen = len;
E 74
D 72
		(void) copyout((caddr_t)&len, namelenp, sizeof (int));
E 72
I 72
D 81
		if (namelenp)
			(void) copyout((caddr_t)&len, namelenp, sizeof (int));
E 72
	}
D 79
	if (mp->msg_accrights) {
		len = mp->msg_accrightslen;
E 79
I 79
	if (rightslenp) {	/* only from orecvmsg() */
		len = mp->msg_controllen;
E 79
		if (len <= 0 || rights == 0)
			len = 0;
		else {
I 79
			rights->m_len -= sizeof (struct cmsghdr);
			rights->m_data += sizeof (struct cmsghdr);
E 79
			if (len > rights->m_len)
				len = rights->m_len;
			(void) copyout((caddr_t)mtod(rights, caddr_t),
D 79
			    (caddr_t)mp->msg_accrights, (unsigned)len);
E 79
I 79
			    (caddr_t)mp->msg_control, (unsigned)len);
			m_freem(rights);
			rights = 0;
E 81
I 81
		if (namelenp &&
		    (error = copyout((caddr_t)&len, namelenp, sizeof (int)))) {
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
E 93
			if (mp->msg_flags & MSG_COMPAT)
				error = 0;	/* old recvfrom didn't check */
			else
#endif
			goto out;
E 81
E 79
		}
I 74
D 79
		mp->msg_accrightslen = len;
E 74
D 72
		(void) copyout((caddr_t)&len, rightslenp, sizeof (int));
E 72
I 72
		if (rightslenp)
			(void) copyout((caddr_t)&len, rightslenp, sizeof (int));
E 79
I 79
D 81
		(void) copyout((caddr_t)&len, rightslenp, sizeof (int));
		mp->msg_control = 0;
E 81
E 79
E 72
	}
I 72
	if (mp->msg_control) {
I 79
D 81
		if (rights) {
			if (control) {
				rights->m_next = control;
				rights = m_pullup(rights,
						rights->m_len + control->m_len);
				if (rights == 0)
					mp->msg_flags |= MSG_CTRUNC;
E 81
I 81
D 93
#ifdef	COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
E 93
		/*
		 * We assume that old recvmsg calls won't receive access
		 * rights and other control info, esp. as control info
		 * is always optional and those options didn't exist in 4.3.
		 * If we receive rights, trim the cmsghdr; anything else
		 * is tossed.
		 */
		if (control && mp->msg_flags & MSG_COMPAT) {
			if (mtod(control, struct cmsghdr *)->cmsg_level !=
			    SOL_SOCKET ||
			    mtod(control, struct cmsghdr *)->cmsg_type !=
			    SCM_RIGHTS) {
				mp->msg_controllen = 0;
				goto out;
E 81
			}
D 81
			control = rights;
			rights = 0;
E 81
I 81
			control->m_len -= sizeof (struct cmsghdr);
			control->m_data += sizeof (struct cmsghdr);
E 81
		}
I 81
#endif
E 81
E 79
		len = mp->msg_controllen;
		if (len <= 0 || control == 0)
			len = 0;
		else {
			if (len >= control->m_len)
				len = control->m_len;
			else
				mp->msg_flags |= MSG_CTRUNC;
D 81
			(void) copyout((caddr_t)mtod(control, caddr_t),
E 81
I 81
			error = copyout((caddr_t)mtod(control, caddr_t),
E 81
			    (caddr_t)mp->msg_control, (unsigned)len);
		}
D 74
		if (controllenp)
			(void) copyout((caddr_t)&len, controllenp, sizeof(int));
E 74
I 74
		mp->msg_controllen = len;
E 74
	}
I 80
out:
E 80
E 72
D 81
	if (rights)
		m_freem(rights);
E 81
	if (from)
		m_freem(from);
I 72
	if (control)
		m_freem(control);
I 80
	return (error);
E 80
E 72
E 47
}

I 95
D 104
struct shutdown_args {
	int	s;
	int	how;
};
E 104
E 95
D 83
shutdown()
{
I 41
	struct a {
E 83
I 83
/* ARGSUSED */
I 104
int
E 104
shutdown(p, uap, retval)
	struct proc *p;
D 95
	register struct args {
E 83
		int	s;
		int	how;
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	register struct shutdown_args *uap;
E 95
	int *retval;
E 104
I 104
	register struct shutdown_args /* {
		syscallarg(int) s;
		syscallarg(int) how;
	} */ *uap;
	register_t *retval;
E 104
{
E 83
	struct file *fp;
I 80
	int error;
E 80
E 41

D 41
	u.u_error = EINVAL;
E 41
I 41
D 47
	fp = getf(uap->s);
E 47
I 47
D 80
	fp = getsock(uap->s);
E 80
I 80
D 89
	fp = getsock(uap->s, &error);
E 80
E 47
	if (fp == 0)
E 89
I 89
D 104
	if (error = getsock(p->p_fd, uap->s, &fp))
E 104
I 104
	if (error = getsock(p->p_fd, SCARG(uap, s), &fp))
E 104
E 89
D 80
		return;
D 47
	if (fp->f_type != DTYPE_SOCKET) {
		u.u_error = ENOTSOCK;
		return;
	}
	u.u_error = soshutdown(fp->f_socket, uap->how);
E 47
I 47
	u.u_error = soshutdown((struct socket *)fp->f_data, uap->how);
E 80
I 80
D 86
		RETURN (error);
	RETURN (soshutdown((struct socket *)fp->f_data, uap->how));
E 86
I 86
		return (error);
D 104
	return (soshutdown((struct socket *)fp->f_data, uap->how));
E 104
I 104
	return (soshutdown((struct socket *)fp->f_data, SCARG(uap, how)));
E 104
E 86
E 80
E 47
E 41
}

I 95
D 104
struct setsockopt_args {
	int	s;
	int	level;
	int	name;
	caddr_t	val;
	int	valsize;
};
E 104
E 95
I 42
D 83
setsockopt()
{
	struct a {
E 83
I 83
/* ARGSUSED */
I 104
int
E 104
setsockopt(p, uap, retval)
	struct proc *p;
D 95
	register struct args {
E 83
		int	s;
		int	level;
		int	name;
		caddr_t	val;
		int	valsize;
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	register struct setsockopt_args *uap;
E 95
	int *retval;
E 104
I 104
	register struct setsockopt_args /* {
		syscallarg(int) s;
		syscallarg(int) level;
		syscallarg(int) name;
		syscallarg(caddr_t) val;
		syscallarg(int) valsize;
	} */ *uap;
	register_t *retval;
E 104
{
E 83
	struct file *fp;
D 43
	struct mbuf *m;
E 43
I 43
	struct mbuf *m = NULL;
I 80
	int error;
E 80
E 43

D 47
	fp = getf(uap->s);
E 47
I 47
D 80
	fp = getsock(uap->s);
E 80
I 80
D 89
	fp = getsock(uap->s, &error);
E 80
E 47
	if (fp == 0)
E 89
I 89
D 104
	if (error = getsock(p->p_fd, uap->s, &fp))
E 104
I 104
	if (error = getsock(p->p_fd, SCARG(uap, s), &fp))
E 104
E 89
D 80
		return;
D 47
	if (fp->f_type != DTYPE_SOCKET) {
		u.u_error = ENOTSOCK;
		return;
	}
E 47
	if (uap->valsize > MLEN) {
		u.u_error = EINVAL;
		return;
	}
E 80
I 80
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
D 104
	if (uap->valsize > MLEN)
E 104
I 104
	if (SCARG(uap, valsize) > MLEN)
E 104
D 86
		RETURN (EINVAL);
E 86
I 86
		return (EINVAL);
E 86
E 80
D 43
	m = m_get(M_WAIT, MT_SOOPTS);
	if (m == 0) {
		u.u_error = ENOBUFS;
		return;
E 43
I 43
D 104
	if (uap->val) {
E 104
I 104
	if (SCARG(uap, val)) {
E 104
		m = m_get(M_WAIT, MT_SOOPTS);
D 46
		if (m == 0) {
E 46
I 46
D 80
		if (m == NULL) {
E 46
			u.u_error = ENOBUFS;
			return;
		}
D 47
		u.u_error = copyin(uap->val, mtod(m, caddr_t),
		  (u_int)uap->valsize);
E 47
I 47
		u.u_error =
		    copyin(uap->val, mtod(m, caddr_t), (u_int)uap->valsize);
E 47
D 54
		if (u.u_error)
			goto bad;
E 54
I 54
		if (u.u_error) {
E 80
I 80
		if (m == NULL)
D 86
			RETURN (ENOBUFS);
E 86
I 86
			return (ENOBUFS);
E 86
D 104
		if (error = copyin(uap->val, mtod(m, caddr_t),
		    (u_int)uap->valsize)) {
E 104
I 104
		if (error = copyin(SCARG(uap, val), mtod(m, caddr_t),
		    (u_int)SCARG(uap, valsize))) {
E 104
E 80
			(void) m_free(m);
D 80
			return;
E 80
I 80
D 86
			RETURN (error);
E 86
I 86
			return (error);
E 86
E 80
		}
E 54
D 104
		m->m_len = uap->valsize;
E 104
I 104
		m->m_len = SCARG(uap, valsize);
E 104
E 43
	}
D 43
	u.u_error = copyin(uap->val, mtod(m, caddr_t), (u_int)uap->valsize);
	if (u.u_error)
		goto bad;
	m->m_len = uap->valsize;
E 43
D 47
	u.u_error = sosetopt(fp->f_socket, uap->level, uap->name, m);
E 47
I 47
D 80
	u.u_error =
	    sosetopt((struct socket *)fp->f_data, uap->level, uap->name, m);
E 80
I 80
D 86
	RETURN (sosetopt((struct socket *)fp->f_data, uap->level,
E 86
I 86
D 104
	return (sosetopt((struct socket *)fp->f_data, uap->level,
E 86
	    uap->name, m));
E 104
I 104
	return (sosetopt((struct socket *)fp->f_data, SCARG(uap, level),
	    SCARG(uap, name), m));
E 104
E 80
E 47
D 54
bad:
D 43
	(void) m_free(m);
E 43
I 43
	if (m != NULL)
		(void) m_free(m);
E 54
E 43
}

I 95
D 104
struct getsockopt_args {
	int	s;
	int	level;
	int	name;
	caddr_t	val;
	int	*avalsize;
};
E 104
E 95
D 83
getsockopt()
{
	struct a {
E 83
I 83
/* ARGSUSED */
I 104
int
E 104
getsockopt(p, uap, retval)
	struct proc *p;
D 95
	register struct args {
E 83
		int	s;
		int	level;
		int	name;
		caddr_t	val;
		int	*avalsize;
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	register struct getsockopt_args *uap;
E 95
	int *retval;
E 104
I 104
	register struct getsockopt_args /* {
		syscallarg(int) s;
		syscallarg(int) level;
		syscallarg(int) name;
		syscallarg(caddr_t) val;
		syscallarg(int *) avalsize;
	} */ *uap;
	register_t *retval;
E 104
{
E 83
	struct file *fp;
D 43
	struct mbuf *m;
E 43
I 43
	struct mbuf *m = NULL;
E 43
D 80
	int valsize;
E 80
I 80
	int valsize, error;
E 80

D 47
	fp = getf(uap->s);
E 47
I 47
D 80
	fp = getsock(uap->s);
E 80
I 80
D 89
	fp = getsock(uap->s, &error);
E 80
E 47
	if (fp == 0)
E 89
I 89
D 104
	if (error = getsock(p->p_fd, uap->s, &fp))
E 104
I 104
	if (error = getsock(p->p_fd, SCARG(uap, s), &fp))
E 104
E 89
D 80
		return;
E 80
I 80
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
E 80
D 47
	if (fp->f_type != DTYPE_SOCKET) {
		u.u_error = ENOTSOCK;
		return;
	}
E 47
D 43
	u.u_error = copyin((caddr_t)uap->avalsize, (caddr_t)&valsize,
		sizeof (valsize));
	if (u.u_error)
		return;
	if (useracc((caddr_t)uap->val, (u_int)valsize, B_WRITE) == 0) {
		u.u_error = EFAULT;
		return;
E 43
I 43
D 104
	if (uap->val) {
D 80
		u.u_error = copyin((caddr_t)uap->avalsize, (caddr_t)&valsize,
			sizeof (valsize));
		if (u.u_error)
			return;
E 80
I 80
		if (error = copyin((caddr_t)uap->avalsize, (caddr_t)&valsize,
		    sizeof (valsize)))
E 104
I 104
	if (SCARG(uap, val)) {
		if (error = copyin((caddr_t)SCARG(uap, avalsize),
		    (caddr_t)&valsize, sizeof (valsize)))
E 104
D 86
			RETURN (error);
E 86
I 86
			return (error);
E 86
E 80
D 54
		m = m_get(M_WAIT, MT_SOOPTS);
		if (m == NULL) {
			u.u_error = ENOBUFS;
			return;
		}
E 43
	}
E 54
I 54
	} else
		valsize = 0;
E 54
D 43
	m = m_get(M_WAIT, MT_SOOPTS);
	if (m == 0) {
		u.u_error = ENOBUFS;
		return;
	}
E 43
D 47
	u.u_error = sogetopt(fp->f_socket, uap->level, uap->name, m);
E 47
I 47
D 80
	u.u_error =
D 54
	    sogetopt((struct socket *)fp->f_data, uap->level, uap->name, m);
E 54
I 54
	    sogetopt((struct socket *)fp->f_data, uap->level, uap->name, &m);
E 54
E 47
	if (u.u_error)
		goto bad;
D 43
	if (valsize > m->m_len)
		valsize = m->m_len;
	u.u_error = copyout(mtod(m, caddr_t), uap->val, (u_int)valsize);
	if (u.u_error)
		goto bad;
	u.u_error = copyout((caddr_t)&valsize, (caddr_t)uap->avalsize,
	    sizeof (valsize));
E 43
I 43
D 54
	if (uap->val) {
E 54
I 54
	if (uap->val && valsize && m != NULL) {
E 80
I 80
D 104
	if ((error = sogetopt((struct socket *)fp->f_data, uap->level,
	    uap->name, &m)) == 0 && uap->val && valsize && m != NULL) {
E 104
I 104
	if ((error = sogetopt((struct socket *)fp->f_data, SCARG(uap, level),
	    SCARG(uap, name), &m)) == 0 && SCARG(uap, val) && valsize &&
	    m != NULL) {
E 104
E 80
E 54
		if (valsize > m->m_len)
			valsize = m->m_len;
D 80
		u.u_error = copyout(mtod(m, caddr_t), uap->val, (u_int)valsize);
		if (u.u_error)
			goto bad;
		u.u_error = copyout((caddr_t)&valsize, (caddr_t)uap->avalsize,
		    sizeof (valsize));
E 80
I 80
D 104
		error = copyout(mtod(m, caddr_t), uap->val, (u_int)valsize);
E 104
I 104
		error = copyout(mtod(m, caddr_t), SCARG(uap, val),
		    (u_int)valsize);
E 104
		if (error == 0)
			error = copyout((caddr_t)&valsize,
D 104
			    (caddr_t)uap->avalsize, sizeof (valsize));
E 104
I 104
			    (caddr_t)SCARG(uap, avalsize), sizeof (valsize));
E 104
E 80
	}
E 43
D 80
bad:
E 80
D 43
	(void) m_free(m);
E 43
I 43
	if (m != NULL)
		(void) m_free(m);
I 80
D 86
	RETURN (error);
E 86
I 86
	return (error);
E 86
E 80
E 43
}

I 95
D 104
struct pipe_args {
	int	dummy;
};
E 104
E 95
E 42
D 83
pipe()
E 83
I 83
/* ARGSUSED */
I 104
int
E 104
pipe(p, uap, retval)
	struct proc *p;
D 95
	struct args *uap;
E 95
I 95
D 104
	struct pipe_args *uap;
E 95
	int retval[];
E 104
I 104
	void *uap;
	register_t *retval;
E 104
E 83
{
I 89
	register struct filedesc *fdp = p->p_fd;
E 89
D 75
	register struct file *rf, *wf;
E 75
I 75
	struct file *rf, *wf;
E 75
	struct socket *rso, *wso;
D 75
	int r;
E 75
I 75
D 78
	int fd, r;
E 78
I 78
D 80
	int fd;
E 80
I 80
	int fd, error;
E 80
E 78
E 75

D 33
	u.u_error = socreate(1, &rso, SOCK_STREAM, 0, 0);
E 33
I 33
D 37
	u.u_error = socreate(1, &rso, SOCK_STREAM, 0, (struct socketopt *)0);
E 37
I 37
D 47
	u.u_error = socreate(AF_UNIX, &rso, SOCK_STREAM, 0,
		(struct socketopt *)0);
E 47
I 47
D 80
	u.u_error = socreate(AF_UNIX, &rso, SOCK_STREAM, 0);
E 47
E 37
E 33
	if (u.u_error)
		return;
D 33
	u.u_error = socreate(1, &wso, SOCK_STREAM, 0, 0);
E 33
I 33
D 37
	u.u_error = socreate(1, &wso, SOCK_STREAM, 0, (struct socketopt *)0);
E 37
I 37
D 47
	u.u_error = socreate(AF_UNIX, &wso, SOCK_STREAM, 0,
		(struct socketopt *)0);
E 47
I 47
	u.u_error = socreate(AF_UNIX, &wso, SOCK_STREAM, 0);
E 47
E 37
E 33
	if (u.u_error)
E 80
I 80
	if (error = socreate(AF_UNIX, &rso, SOCK_STREAM, 0))
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
	if (error = socreate(AF_UNIX, &wso, SOCK_STREAM, 0))
E 80
D 73
		goto free;
E 73
I 73
D 76
		goto freeit;
E 76
I 76
		goto free1;
E 76
E 73
D 75
	rf = falloc();
	if (rf == NULL)
E 75
I 75
D 80
	if (u.u_error = falloc(&rf, &fd))
E 80
I 80
D 89
	if (error = falloc(&rf, &fd))
E 89
I 89
	if (error = falloc(p, &rf, &fd))
E 89
E 80
E 75
		goto free2;
D 75
	r = u.u_r.r_val1;
E 75
I 75
D 83
	u.u_r.r_val1 = fd;
E 83
I 83
	retval[0] = fd;
E 83
E 75
	rf->f_flag = FREAD;
	rf->f_type = DTYPE_SOCKET;
D 47
	rf->f_socket = rso;
E 47
I 47
	rf->f_ops = &socketops;
	rf->f_data = (caddr_t)rso;
E 47
D 75
	wf = falloc();
	if (wf == NULL)
E 75
I 75
D 80
	if (u.u_error = falloc(&wf, &fd))
E 80
I 80
D 89
	if (error = falloc(&wf, &fd))
E 89
I 89
	if (error = falloc(p, &wf, &fd))
E 89
E 80
E 75
		goto free3;
	wf->f_flag = FWRITE;
	wf->f_type = DTYPE_SOCKET;
D 47
	wf->f_socket = wso;
E 47
I 47
	wf->f_ops = &socketops;
	wf->f_data = (caddr_t)wso;
E 47
D 75
	u.u_r.r_val2 = u.u_r.r_val1;
	u.u_r.r_val1 = r;
E 75
I 75
D 83
	u.u_r.r_val2 = fd;
E 83
I 83
	retval[1] = fd;
E 83
E 75
D 56
	if (piconnect(wso, rso) == 0)
E 56
I 56
D 63
	if (u.u_error = unp_connect2(wso, (struct mbuf *)0, rso))
E 63
I 63
D 80
	if (u.u_error = unp_connect2(wso, rso))
E 80
I 80
	if (error = unp_connect2(wso, rso))
E 80
E 63
E 56
		goto free4;
I 56
D 79
	wso->so_state |= SS_CANTRCVMORE;
	rso->so_state |= SS_CANTSENDMORE;
E 79
E 56
D 80
	return;
E 80
I 80
D 86
	RETURN (0);
E 86
I 86
	return (0);
E 86
E 80
free4:
D 92
	wf->f_count = 0;
E 92
I 92
	ffree(wf);
E 92
D 83
	u.u_ofile[u.u_r.r_val2] = 0;
E 83
I 83
D 89
	u.u_ofile[retval[1]] = 0;
E 89
I 89
D 91
	OFILE(fdp, retval[1]) = 0;
E 91
I 91
	fdp->fd_ofiles[retval[1]] = 0;
E 91
E 89
E 83
free3:
D 92
	rf->f_count = 0;
E 92
I 92
	ffree(rf);
E 92
D 77
	u.u_ofile[r] = 0;
E 77
I 77
D 83
	u.u_ofile[u.u_r.r_val1] = 0;
E 83
I 83
D 89
	u.u_ofile[retval[0]] = 0;
E 89
I 89
D 91
	OFILE(fdp, retval[0]) = 0;
E 91
I 91
	fdp->fd_ofiles[retval[0]] = 0;
E 91
E 89
E 83
E 77
free2:
I 75
D 76
	wso->so_state |= SS_NOFDREF;
E 76
E 75
D 61
	wso->so_state |= SS_NOFDREF;
	sofree(wso);
E 61
I 61
D 64
	soclose(wso);
E 64
I 64
	(void)soclose(wso);
E 64
E 61
D 73
free:
I 75
D 76
	rso->so_state |= SS_NOFDREF;
E 75
E 73
I 73
freeit:
E 76
I 76
free1:
E 76
E 73
D 61
	rso->so_state |= SS_NOFDREF;
	sofree(rso);
E 61
I 61
D 64
	soclose(rso);
E 64
I 64
	(void)soclose(rso);
I 80
D 86
	RETURN (error);
E 86
I 86
	return (error);
E 86
E 80
E 64
E 61
}

E 27
/*
D 45
 * Get socket address.
E 45
I 45
 * Get socket name.
E 45
 */
I 95
D 104
struct getsockname_args {
	int	fdes;
	caddr_t	asa;
	int	*alen;
E 104
E 95
I 73
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
I 95
D 104
	int	compat_43;	/* pseudo */
#endif
};
#ifdef COMPAT_OLDSOCK
E 104
I 104
int
E 104
E 95
E 93
E 73
D 45
ssocketaddr()
E 45
I 45
D 83
getsockname()
E 45
{
I 73
D 80
	getsockname1(0);
E 80
I 80
	struct a {
E 83
I 83
getsockname(p, uap, retval)
	struct proc *p;
D 95
	struct args {
E 83
		int	fdes;
		caddr_t	asa;
		int	*alen;
		int	compat_43;
D 83
	};
	((struct a *)u.u_ap)->compat_43 = 0;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	struct getsockname_args *uap;
E 95
	int *retval;
E 104
I 104
	struct getsockname_args /* {
		syscallarg(int) fdes;
		syscallarg(caddr_t) asa;
		syscallarg(int *) alen;
	} */ *uap;
	register_t *retval;
E 104
{
E 83

D 83
	RETURN (getsockname1());
E 83
I 83
D 104
	uap->compat_43 = 0;
D 86
	RETURN (getsockname1(p, uap, retval));
E 86
I 86
	return (getsockname1(p, uap, retval));
E 104
I 104
	return (getsockname1(p, uap, retval, 0));
E 104
E 86
E 83
E 80
}

D 83
ogetsockname()
{
D 80
	getsockname1(1);
E 80
I 80
	struct a {
E 83
I 83
D 104
ogetsockname(p, uap, retval)
E 104
I 104
int
compat_43_getsockname(p, uap, retval)
E 104
	struct proc *p;
D 95
	struct args {
E 83
		int	fdes;
		caddr_t	asa;
		int	*alen;
		int	compat_43;
D 83
	};
	((struct a *)u.u_ap)->compat_43 = 1;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	struct getsockname_args *uap;
E 95
	int *retval;
E 104
I 104
	struct getsockname_args /* {
		syscallarg(int) fdes;
		syscallarg(caddr_t) asa;
		syscallarg(int *) alen;
	} */ *uap;
	register_t *retval;
E 104
{
E 83

D 83
	RETURN (getsockname1());
E 83
I 83
D 104
	uap->compat_43 = 1;
D 86
	RETURN (getsockname1(p, uap, retval));
E 86
I 86
	return (getsockname1(p, uap, retval));
E 104
I 104
	return (getsockname1(p, uap, retval, 1));
E 104
E 86
E 83
E 80
}
I 80
D 93
#else /* COMPAT_43 */
E 93
I 93
#else /* COMPAT_OLDSOCK */
E 93
E 80

D 80
getsockname1(compat_43)
#else
getsockname()
E 80
I 80
#define	getsockname1	getsockname
E 80
#endif
I 80

D 83
getsockname1()
E 80
{
E 73
	register struct a {
E 83
I 83
/* ARGSUSED */
D 104
getsockname1(p, uap, retval)
E 104
I 104
int
getsockname1(p, uap, retval, compat_43)
E 104
	struct proc *p;
D 95
	register struct args {
E 83
		int	fdes;
D 45
		struct	sockaddr *asa;
E 45
I 45
		caddr_t	asa;
		int	*alen;
I 80
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
E 93
		int	compat_43;
#endif
E 80
E 45
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	register struct getsockname_args *uap;
E 95
	int *retval;
E 104
I 104
	register struct getsockname_args /* {
		syscallarg(int) fdes;
		syscallarg(caddr_t) asa;
		syscallarg(int *) alen;
	} */ *uap;
	register_t *retval;
	int compat_43;
E 104
{
E 83
D 89
	register struct file *fp;
E 89
I 89
	struct file *fp;
E 89
I 17
	register struct socket *so;
D 27
	struct sockaddr addr;
E 27
I 27
	struct mbuf *m;
I 45
D 80
	int len;
E 80
I 80
	int len, error;
E 80
E 45
E 27
E 17
D 20
COUNT(SSOCKETADDR);
E 20

D 47
	fp = getf(uap->fdes);
E 47
I 47
D 80
	fp = getsock(uap->fdes);
E 80
I 80
D 89
	fp = getsock(uap->fdes, &error);
E 80
E 47
	if (fp == 0)
E 89
I 89
D 104
	if (error = getsock(p->p_fd, uap->fdes, &fp))
E 104
I 104
	if (error = getsock(p->p_fd, SCARG(uap, fdes), &fp))
E 104
E 89
D 80
		return;
D 21
	if ((fp->f_flag & FSOCKET) == 0) {
E 21
I 21
D 47
	if (fp->f_type != DTYPE_SOCKET) {
E 21
		u.u_error = ENOTSOCK;
		return;
	}
E 47
I 45
	u.u_error = copyin((caddr_t)uap->alen, (caddr_t)&len, sizeof (len));
	if (u.u_error)
		return;
E 80
I 80
D 83
		return (error);
E 83
I 83
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
E 83
D 104
	if (error = copyin((caddr_t)uap->alen, (caddr_t)&len, sizeof (len)))
E 104
I 104
	if (error = copyin((caddr_t)SCARG(uap, alen), (caddr_t)&len,
	    sizeof (len)))
E 104
D 83
		return (error);
E 83
I 83
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
E 83
E 80
E 45
D 7
	copyout(fp->f_socket->f_
E 7
I 7
D 17
	if (copyout((caddr_t)&fp->f_socket->so_addr, (caddr_t)uap->asa, 
	    sizeof (struct sockaddr))) {
		u.u_error = EFAULT;
E 17
I 17
D 47
	so = fp->f_socket;
E 47
I 47
	so = (struct socket *)fp->f_data;
E 47
I 27
D 39
	m = m_getclr(M_WAIT);
E 39
I 39
	m = m_getclr(M_WAIT, MT_SONAME);
I 46
D 80
	if (m == NULL) {
		u.u_error = ENOBUFS;
		return;
	}
E 46
E 39
E 27
D 45
	u.u_error =
D 27
		(*so->so_proto->pr_usrreq)(so, PRU_SOCKADDR, 0, (caddr_t)&addr);
E 27
I 27
		(*so->so_proto->pr_usrreq)(so, PRU_SOCKADDR, 0, m, 0);
E 45
I 45
	u.u_error = (*so->so_proto->pr_usrreq)(so, PRU_SOCKADDR, 0, m, 0);
E 45
E 27
	if (u.u_error)
E 80
I 80
	if (m == NULL)
D 83
		return (ENOBUFS);
E 83
I 83
D 86
		RETURN (ENOBUFS);
E 86
I 86
		return (ENOBUFS);
E 86
E 83
	if (error = (*so->so_proto->pr_usrreq)(so, PRU_SOCKADDR, 0, m, 0))
E 80
E 17
D 27
		return;
D 17
	}
E 17
I 17
	if (copyout((caddr_t)&addr, (caddr_t)uap->asa, sizeof (addr)))
E 27
I 27
		goto bad;
D 40
	if (copyout(mtod(m, caddr_t), (caddr_t)uap->asa, sizeof (struct sockaddr)))
E 27
		u.u_error = EFAULT;
E 40
I 40
D 45
	u.u_error = copyout(mtod(m, caddr_t), (caddr_t)uap->asa,
		sizeof (struct sockaddr));
E 45
I 45
	if (len > m->m_len)
		len = m->m_len;
I 73
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
E 93
D 80
	if (compat_43)
E 80
I 80
D 104
	if (uap->compat_43)
E 104
I 104
	if (compat_43)
E 104
E 80
		mtod(m, struct osockaddr *)->sa_family =
		    mtod(m, struct sockaddr *)->sa_family;
#endif
E 73
D 80
	u.u_error = copyout(mtod(m, caddr_t), (caddr_t)uap->asa, (u_int)len);
D 73
	if (u.u_error)
		goto bad;
	u.u_error = copyout((caddr_t)&len, (caddr_t)uap->alen, sizeof (len));
E 73
I 73
	if (u.u_error == 0)
		u.u_error = copyout((caddr_t)&len, (caddr_t)uap->alen,
E 80
I 80
D 104
	error = copyout(mtod(m, caddr_t), (caddr_t)uap->asa, (u_int)len);
E 104
I 104
	error = copyout(mtod(m, caddr_t), (caddr_t)SCARG(uap, asa), (u_int)len);
E 104
	if (error == 0)
D 104
		error = copyout((caddr_t)&len, (caddr_t)uap->alen,
E 104
I 104
		error = copyout((caddr_t)&len, (caddr_t)SCARG(uap, alen),
E 104
E 80
		    sizeof (len));
E 73
E 45
E 40
I 27
bad:
	m_freem(m);
I 80
D 83
	return (error);
E 83
I 83
D 86
	RETURN (error);
E 86
I 86
	return (error);
E 86
E 83
E 80
}

I 73
/*
 * Get name of peer for connected socket.
 */
I 95
D 104
struct getpeername_args {
	int	fdes;
	caddr_t	asa;
	int	*alen;
E 104
E 95
E 73
I 72
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
I 95
D 104
	int	compat_43;	/* pseudo */
#endif
};

#ifdef COMPAT_OLDSOCK
E 104
I 104
int
E 104
E 95
E 93
D 73
ogetsockname()
E 73
I 73
D 83
getpeername()
E 73
{
D 73
	return (getsockname());
E 73
I 73
D 80
	getpeername1(0);
E 80
I 80
	register struct a {
E 83
I 83
getpeername(p, uap, retval)
	struct proc *p;
D 95
	struct args {
E 83
		int	fdes;
		caddr_t	asa;
		int	*alen;
		int	compat_43;
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	struct getpeername_args *uap;
E 95
	int *retval;
E 104
I 104
	struct getpeername_args /* {
		syscallarg(int) fdes;
		syscallarg(caddr_t) asa;
		syscallarg(int *) alen;
	} */ *uap;
	register_t *retval;
E 104
{
E 83

D 83
	((struct a *)u.u_ap)->compat_43 = 0;
	getpeername1();
E 83
I 83
D 104
	uap->compat_43 = 0;
D 86
	RETURN (getpeername1(p, uap, retval));
E 86
I 86
	return (getpeername1(p, uap, retval));
E 104
I 104
	return (getpeername1(p, uap, retval, 0));
E 104
E 86
E 83
E 80
E 73
}
D 73
#endif
E 73

E 72
I 49
D 73
/*
 * Get name of peer for connected socket.
 */
E 73
I 73
D 83
ogetpeername()
{
D 80
	getpeername1(1);
E 80
I 80
	register struct a {
E 83
I 83
D 104
ogetpeername(p, uap, retval)
E 104
I 104
int
compat_43_getpeername(p, uap, retval)
E 104
	struct proc *p;
D 95
	struct args {
E 83
		int	fdes;
		caddr_t	asa;
		int	*alen;
		int	compat_43;
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	struct getpeername_args *uap;
E 95
	int *retval;
E 104
I 104
	struct getpeername_args /* {
		syscallarg(int) fdes;
		syscallarg(caddr_t) asa;
		syscallarg(int *) alen;
	} */ *uap;
	register_t *retval;
E 104
{
E 83

D 83
	((struct a *)u.u_ap)->compat_43 = 1;
	getpeername1();
E 83
I 83
D 104
	uap->compat_43 = 1;
D 86
	RETURN (getpeername1(p, uap, retval));
E 86
I 86
	return (getpeername1(p, uap, retval));
E 104
I 104
	return (getpeername1(p, uap, retval, 1));
E 104
E 86
E 83
E 80
}
I 80
D 93
#else /* COMPAT_43 */
E 93
I 93
#else /* COMPAT_OLDSOCK */
E 93
E 80

D 80
getpeername1(compat_43)
#else
E 73
getpeername()
E 80
I 80
#define	getpeername1	getpeername
E 80
I 73
#endif
I 80

D 83
getpeername1()
E 80
E 73
{
	register struct a {
E 83
I 83
/* ARGSUSED */
D 104
getpeername1(p, uap, retval)
E 104
I 104
int
getpeername1(p, uap, retval, compat_43)
E 104
	struct proc *p;
D 95
	register struct args {
E 83
		int	fdes;
		caddr_t	asa;
		int	*alen;
I 80
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
E 93
		int	compat_43;
#endif
E 80
D 83
	} *uap = (struct a *)u.u_ap;
E 83
I 83
	} *uap;
E 95
I 95
D 104
	register struct getpeername_args *uap;
E 95
	int *retval;
E 104
I 104
	register struct getpeername_args /* {
		syscallarg(int) fdes;
		syscallarg(caddr_t) asa;
		syscallarg(int *) alen;
	} */ *uap;
	register_t *retval;
	int compat_43;
E 104
{
E 83
D 89
	register struct file *fp;
E 89
I 89
	struct file *fp;
E 89
	register struct socket *so;
	struct mbuf *m;
D 80
	int len;
E 80
I 80
	int len, error;
E 80

D 80
	fp = getsock(uap->fdes);
E 80
I 80
D 89
	fp = getsock(uap->fdes, &error);
E 80
	if (fp == 0)
E 89
I 89
D 104
	if (error = getsock(p->p_fd, uap->fdes, &fp))
E 104
I 104
	if (error = getsock(p->p_fd, SCARG(uap, fdes), &fp))
E 104
E 89
D 80
		return;
E 80
I 80
D 83
		return (error);
E 83
I 83
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 86
E 83
E 80
	so = (struct socket *)fp->f_data;
D 78
	if ((so->so_state & SS_ISCONNECTED) == 0) {
E 78
I 78
D 80
	if ((so->so_state & (SS_ISCONNECTED|SS_ISCONFIRMING)) == 0) {
E 78
		u.u_error = ENOTCONN;
		return;
	}
E 80
I 80
	if ((so->so_state & (SS_ISCONNECTED|SS_ISCONFIRMING)) == 0)
D 83
		return (ENOTCONN);
E 83
I 83
D 86
		RETURN (ENOTCONN);
E 86
I 86
		return (ENOTCONN);
I 99
D 104
	if (error = copyin((caddr_t)uap->alen, (caddr_t)&len, sizeof (len)))
E 104
I 104
	if (error =
	    copyin((caddr_t)SCARG(uap, alen), (caddr_t)&len, sizeof (len)))
E 104
		return (error);
E 99
E 86
E 83
E 80
	m = m_getclr(M_WAIT, MT_SONAME);
D 80
	if (m == NULL) {
		u.u_error = ENOBUFS;
		return;
	}
	u.u_error = copyin((caddr_t)uap->alen, (caddr_t)&len, sizeof (len));
	if (u.u_error)
		return;
	u.u_error = (*so->so_proto->pr_usrreq)(so, PRU_PEERADDR, 0, m, 0);
	if (u.u_error)
E 80
I 80
	if (m == NULL)
D 83
		return (ENOBUFS);
E 83
I 83
D 86
		RETURN (ENOBUFS);
E 86
I 86
		return (ENOBUFS);
E 86
E 83
D 99
	if (error = copyin((caddr_t)uap->alen, (caddr_t)&len, sizeof (len)))
D 83
		return (error);
E 83
I 83
D 86
		RETURN (error);
E 86
I 86
		return (error);
E 99
E 86
E 83
	if (error = (*so->so_proto->pr_usrreq)(so, PRU_PEERADDR, 0, m, 0))
E 80
		goto bad;
	if (len > m->m_len)
		len = m->m_len;
I 73
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
E 93
D 80
	if (compat_43)
E 80
I 80
D 104
	if (uap->compat_43)
E 104
I 104
	if (compat_43)
E 104
E 80
		mtod(m, struct osockaddr *)->sa_family =
		    mtod(m, struct sockaddr *)->sa_family;
#endif
E 73
D 80
	u.u_error = copyout(mtod(m, caddr_t), (caddr_t)uap->asa, (u_int)len);
	if (u.u_error)
E 80
I 80
D 104
	if (error = copyout(mtod(m, caddr_t), (caddr_t)uap->asa, (u_int)len))
E 104
I 104
	if (error =
	    copyout(mtod(m, caddr_t), (caddr_t)SCARG(uap, asa), (u_int)len))
E 104
E 80
		goto bad;
D 80
	u.u_error = copyout((caddr_t)&len, (caddr_t)uap->alen, sizeof (len));
E 80
I 80
D 104
	error = copyout((caddr_t)&len, (caddr_t)uap->alen, sizeof (len));
E 104
I 104
	error = copyout((caddr_t)&len, (caddr_t)SCARG(uap, alen), sizeof (len));
E 104
E 80
bad:
	m_freem(m);
I 80
D 83
	return (error);
E 83
I 83
D 86
	RETURN (error);
E 86
I 86
	return (error);
E 86
E 83
E 80
}
I 72

I 104
int
E 104
D 73
#ifdef COMPAT_43
ogetpeername()
{
	return (getpeername());
}
#endif
E 72

E 73
E 49
D 47
sockname(aname, name, namelen)
E 47
I 47
D 57
sockargs(aname, name, namelen)
E 57
I 57
D 81
sockargs(aname, name, namelen, type)
E 57
E 47
	struct mbuf **aname;
	caddr_t name;
D 57
	int namelen;
E 57
I 57
	int namelen, type;
E 81
I 81
sockargs(mp, buf, buflen, type)
	struct mbuf **mp;
	caddr_t buf;
	int buflen, type;
E 81
E 57
{
I 94
	register struct sockaddr *sa;
E 94
	register struct mbuf *m;
I 73
D 74
	register struct sockaddr *sa;
E 74
E 73
I 40
	int error;
E 40

D 70
	if (namelen > MLEN)
E 70
I 70
D 78
	if ((u_int)namelen > MLEN)
E 78
I 78
D 81
	if ((u_int)namelen > MLEN) {
E 81
I 81
	if ((u_int)buflen > MLEN) {
E 81
D 93
#ifdef COMPAT_43
E 93
I 93
#ifdef COMPAT_OLDSOCK
E 93
D 81
		if (type == MT_SONAME && (u_int)namelen <= 112)
			namelen = MLEN;		/* unix domain compat. hack */
E 81
I 81
		if (type == MT_SONAME && (u_int)buflen <= 112)
			buflen = MLEN;		/* unix domain compat. hack */
E 81
		else
#endif
E 78
E 70
		return (EINVAL);
I 78
	}
E 78
D 39
	m = m_get(M_WAIT);
E 39
I 39
D 57
	m = m_get(M_WAIT, MT_SONAME);
E 57
I 57
	m = m_get(M_WAIT, type);
E 57
I 46
	if (m == NULL)
		return (ENOBUFS);
E 46
E 39
D 30
	m->m_off = MMINOFF;
E 30
D 81
	m->m_len = namelen;
D 33
	if (copyin(name, mtod(m, caddr_t), namelen)) {
E 33
I 33
D 40
	if (copyin(name, mtod(m, caddr_t), (u_int)namelen)) {
E 40
I 40
	error = copyin(name, mtod(m, caddr_t), (u_int)namelen);
E 81
I 81
	m->m_len = buflen;
	error = copyin(buf, mtod(m, caddr_t), (u_int)buflen);
E 81
D 104
	if (error)
E 104
I 104
	if (error) {
E 104
E 40
E 33
		(void) m_free(m);
D 40
		return (EFAULT);
	}
	*aname = m;
	return (0);
E 40
I 40
D 94
	else
E 94
I 94
D 104
	else {
E 94
D 81
		*aname = m;
E 81
I 81
		*mp = m;
E 81
I 73
D 74
	sa = mtod(m, struct sockaddr *);
E 74
I 74
D 94
	if (type == MT_SONAME) {
		register struct sockaddr *sa = mtod(m, struct sockaddr *);
E 94
I 94
		if (type == MT_SONAME) {
			sa = mtod(m, struct sockaddr *);
E 104
I 104
		return (error);
	}
	*mp = m;
	if (type == MT_SONAME) {
		sa = mtod(m, struct sockaddr *);
E 104
E 94
I 80

E 80
E 74
D 93
#if defined(COMPAT_43) && BYTE_ORDER != BIG_ENDIAN
E 93
I 93
#if defined(COMPAT_OLDSOCK) && BYTE_ORDER != BIG_ENDIAN
E 93
D 74
	if (type == MT_SONAME && sa->sa_family == 0 && sa->sa_len < AF_MAX)
		sa->sa_family = sa->sa_len;
E 74
I 74
D 94
		if (sa->sa_family == 0 && sa->sa_len < AF_MAX)
			sa->sa_family = sa->sa_len;
E 94
I 94
D 104
			if (sa->sa_family == 0 && sa->sa_len < AF_MAX)
				sa->sa_family = sa->sa_len;
E 104
I 104
		if (sa->sa_family == 0 && sa->sa_len < AF_MAX)
			sa->sa_family = sa->sa_len;
E 104
E 94
E 74
#endif
D 74
	sa->sa_len = namelen;
E 74
I 74
D 81
		sa->sa_len = namelen;
E 81
I 81
D 94
		sa->sa_len = buflen;
E 94
I 94
D 104
			sa->sa_len = buflen;
		}
E 104
I 104
		sa->sa_len = buflen;
E 104
E 94
E 81
	}
E 74
E 73
D 104
	return (error);
E 104
I 104
	return (0);
E 104
I 47
}

I 104
int
E 104
D 89
struct file *
D 80
getsock(fdes)
	int fdes;
E 80
I 80
getsock(fdes, errp)
	int fdes, *errp;
E 89
I 89
getsock(fdp, fdes, fpp)
	struct filedesc *fdp;
	int fdes;
	struct file **fpp;
E 89
E 80
{
	register struct file *fp;

D 77
	fp = getf(fdes);
	if (fp == NULL)
E 77
I 77
D 89
	if ((unsigned)fdes >= NOFILE || (fp = u.u_ofile[fdes]) == NULL) {
D 80
		u.u_error = EBADF;
E 80
I 80
		*errp = EBADF;
E 80
E 77
		return (0);
I 77
	}
E 77
	if (fp->f_type != DTYPE_SOCKET) {
D 80
		u.u_error = ENOTSOCK;
E 80
I 80
		*errp = ENOTSOCK;
E 80
		return (0);
	}
	return (fp);
E 89
I 89
D 90
	if ((unsigned)fdes >= fdp->fd_maxfiles ||
E 90
I 90
	if ((unsigned)fdes >= fdp->fd_nfiles ||
E 90
D 91
	    (fp = OFILE(fdp, fdes)) == NULL)
E 91
I 91
	    (fp = fdp->fd_ofiles[fdes]) == NULL)
E 91
		return (EBADF);
	if (fp->f_type != DTYPE_SOCKET)
		return (ENOTSOCK);
	*fpp = fp;
	return (0);
E 89
E 47
E 40
D 42
}

sockopt(so, opt)
	register struct socketopt *so;
	caddr_t opt;
{
	register struct mbuf *m;
I 40
D 41
	int error;
E 41
I 41
	register caddr_t cp;
	int error, len;
E 41
E 40

	if (opt == 0) {
		so->so_optlen = 0;
		so->so_optdata = 0;
		return (0);
	}
D 40
	if (copyin((caddr_t)opt, (caddr_t)so, sizeof (struct socketopt)))
		return (EFAULT);
E 40
I 40
	error = copyin((caddr_t)opt, (caddr_t)so, sizeof (struct socketopt));
	if (error)
		return (error);
E 40
	if (so->so_optlen < 0 || so->so_optlen > MLEN)
		return (EINVAL);
D 39
	m = m_get(M_WAIT);
E 39
I 39
	m = m_get(M_WAIT, MT_SOOPTS);
E 39
D 30
	m->m_off = MMINOFF;
E 30
	m->m_len = so->so_optlen;
D 33
	if (copyin(so->so_optdata, mtod(m, caddr_t), m->m_len)) {
E 33
I 33
D 40
	if (copyin(so->so_optdata, mtod(m, caddr_t), (u_int)m->m_len)) {
E 40
I 40
	error = copyin(so->so_optdata, mtod(m, caddr_t), (u_int)m->m_len);
	if (error) {
E 40
E 33
		(void) m_free(m);
D 40
		return (EFAULT);
E 40
I 40
		return (error);
E 40
	}
D 41
	so->so_optdata = mtod(m, caddr_t);
E 41
I 41
	so->so_optdata = mtod(m, struct sotemplate *);
	/*
	 * Verify data structure consistency.
	 */
	cp = (caddr_t)so->so_optdata;
	len = so->so_optlen;
	while (len > 0 && cp < (caddr_t)so->so_optdata + m->m_len) {
		struct sotemplate *tp;

		if (len < sizeof (struct sotemplate))
			break;
		tp = (struct sotemplate *)cp;
		len -= tp->opt_size + sizeof (int);
		cp += tp->opt_size + sizeof (int);
	}
	if (len != 0 || cp != (caddr_t)so->so_optdata + m->m_len)
		return (EINVAL);
E 41
	return (0);
E 42
E 27
E 17
}
E 7
E 6
E 2
E 1
