h53826
s 00001/00001/01037
d D 8.3 94/01/21 19:49:57 bostic 106 105
c copyright typo
e
s 00007/00006/01031
d D 8.2 94/01/03 17:39:01 bostic 105 104
c In ip_ctloutput, if the option is at level IPPROTO_IP but not
c recognized/supported, return ENOPROTOOPT (from POSIX 1003.12).  I continued
c to return EINVAL if the level was not IPPROTO_IP.  Also, in the latter
c case, I added a check to free any mbuf only for setsockopt, not getsockopt,
c although that is not strictly necessary (getsockopt passes a pointer
c to a null pointer).  From: Mike Karels <karels@BSDI.COM>
e
s 00002/00002/01035
d D 8.1 93/06/10 23:08:54 bostic 104 103
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/01032
d D 7.34 93/06/04 17:22:54 bostic 103 102
c prototype everything
e
s 00001/00001/01036
d D 7.33 93/05/19 16:23:41 sklower 102 100
c In Cherenson's mbuf leak fix, we forgot to (void) the return of m_free()
e
s 00028/00002/01035
d R 7.33 93/05/19 16:19:19 sklower 101 100
c cast m_free() output as void
e
s 00007/00007/01030
d D 7.32 93/04/07 19:28:02 sklower 100 99
c Mostly changes recommended by jch for variable subnets & multiple
c IP addresses per physical interface. May require further work.
e
s 00001/00000/01036
d D 7.31 93/03/12 18:06:20 andrew 99 98
c (by sklower) obvious bug fix in mbuf starvation case
e
s 00004/00030/01032
d D 7.30 93/02/12 22:58:45 andrew 98 97
c fix sccs notice
e
s 00029/00003/01033
d D 7.29 93/02/12 22:55:39 andrew 97 96
c use new flag to distinquish forwarded pkts from IP_HDRINCL pkts
e
s 00007/00005/01029
d D 7.28 93/02/07 21:23:37 sklower 96 95
c #ifdef MROUTING didn't quite get all refs to external variables
e
s 00018/00022/01016
d D 7.27 93/01/08 18:42:21 andrew 95 94
c (By Sklower) checkpoint the current state of Cherenson's work.
e
s 00016/00016/01022
d D 7.26 92/10/11 12:02:01 bostic 94 93
c make kernel includes standard
e
s 00463/00002/00575
d D 7.25 92/07/06 15:08:17 sklower 93 91
c multicast changes from lbl
e
s 00001/00000/00577
d R 7.25 92/02/15 17:59:56 mckusick 92 91
c have to include proc.h before socketvar.h
e
s 00002/00001/00575
d D 7.24 91/10/02 22:45:17 sklower 91 90
c setsockopt of SO level options get passed down to lower levels for info
e
s 00002/00002/00574
d D 7.23 90/11/12 13:23:37 sklower 90 89
c fix broken IP_TTL option (was setting tos instead) (from jch@cornell)
e
s 00016/00004/00560
d D 7.22 90/07/28 10:33:03 karels 89 88
c oops, 7.19 wasn't finished; back part out for now, but leave TOS/TTL
e
s 00001/00011/00563
d D 7.21 90/06/28 21:38:45 bostic 88 87
c new copyright notice
e
s 00008/00006/00566
d D 7.20 90/06/28 14:24:12 karels 87 86
c watch out for ip_len >32767 (is incorrectly declared as short)
e
s 00092/00016/00480
d D 7.19 90/06/28 14:13:29 karels 86 85
c deprecate ENETUNREACH, always use EHOSTUNREACH; support for new pcb options
e
s 00009/00014/00487
d D 7.18 90/04/05 11:49:36 sklower 85 84
c pass rtentry ptr to if_output; get ip_src addr from ifaddr_in if not set
e
s 00003/00002/00498
d D 7.17 90/03/01 16:21:06 mckusick 84 83
c need to adjust length on the fragment, not the head of the packet (from macklem)
e
s 00005/00003/00495
d D 7.16 89/09/20 13:26:17 sklower 83 82
c add more counters for SNMP
e
s 00001/00001/00497
d D 7.15 89/04/25 13:22:47 mckusick 82 81
c ../machine => machine
e
s 00026/00020/00472
d D 7.14 89/04/08 16:16:21 karels 81 80
c new mbufs, route structures
e
s 00010/00005/00482
d D 7.13 88/06/29 17:07:02 bostic 80 79
c install approved copyright notice
e
s 00002/00002/00485
d D 7.12 88/06/27 17:27:12 karels 79 78
c free those mbufs (need to iterate over chain)
e
s 00001/00001/00486
d D 7.11 88/05/26 09:38:22 karels 78 77
c lint
e
s 00002/00002/00485
d D 7.10 88/04/07 17:23:07 karels 77 76
c oops (worked on tahoe!)
e
s 00046/00028/00441
d D 7.9 88/03/15 21:12:35 karels 76 75
c don't copy first packet when fragmenting; use registers better
e
s 00033/00030/00436
d D 7.8 88/02/26 08:40:08 karels 75 74
c first fix for fragmentation of packets with options
e
s 00008/00002/00458
d D 7.7 87/12/07 17:45:49 bostic 74 73
c use Berkeley specific header
e
s 00001/00001/00459
d D 7.6 87/06/20 12:32:19 mckusick 73 72
c check for null mbuf ptr before freeing (4.3BSD/sys/{130,131,133})
e
s 00004/00001/00456
d D 7.5 87/05/24 22:20:55 karels 72 71
c use host unreachables within network (may be subnet unreach.)
e
s 00003/00002/00454
d D 7.4 87/05/07 14:44:59 karels 71 70
c correct comment
e
s 00001/00001/00455
d D 7.3 87/04/02 16:32:09 karels 70 69
c why check host flag for dest?
e
s 00001/00001/00455
d D 7.2 86/10/28 22:53:32 karels 69 68
c byte order changes for tahoe
e
s 00001/00001/00455
d D 7.1 86/06/05 00:28:23 mckusick 68 67
c 4.3BSD release version
e
s 00001/00001/00455
d D 6.16 86/05/11 16:10:11 karels 67 66
c typo
e
s 00001/00001/00455
d D 6.15 86/05/06 16:22:56 karels 66 65
c fix offset calculation when fragmenting fragmented packets
c (from borman)
e
s 00004/00001/00452
d D 6.14 86/04/19 23:08:11 karels 65 64
c with ROUTETOIF, check for pt-pt links first
e
s 00013/00011/00440
d D 6.13 86/02/23 23:24:34 karels 64 63
c lint
e
s 00010/00011/00441
d D 6.12 86/02/12 17:48:27 karels 63 62
c using sockaddr in route for dst; watch out for old route
c if only routing to interface
e
s 00031/00027/00421
d D 6.11 86/02/03 20:10:09 karels 62 61
c consolidate route caching, manipulation in IP
e
s 00011/00012/00437
d D 6.10 86/02/02 20:12:35 karels 61 60
c modify ip_pcbopts to make usable from raw ip
e
s 00211/00005/00238
d D 6.9 85/09/16 23:11:54 karels 60 59
c add code to insert IP options in outgoing packets,
c allow user-settable IP options
e
s 00022/00001/00221
d D 6.8 85/06/24 15:48:56 karels 59 58
c copyright; leave hack for patching address until tested otherwise
e
s 00008/00018/00214
d D 6.7 85/03/18 15:43:58 karels 58 57
c move net addresses from interface to protocol layer;
c move ip_id swapping to ip_forward; zap freed route so rtalloc doesn't
c hand it back again
e
s 00009/00009/00223
d D 6.6 84/08/29 15:36:41 bloom 57 56
c Include file changes.  No more ../h
e
s 00008/00008/00224
d D 6.5 84/06/22 22:25:40 sam 56 55
c slight cleanup -- this is inet, so use sockaddr_in's
e
s 00006/00003/00226
d D 6.4 84/05/25 14:26:28 karels 55 54
c propagate IP_MF when fragmenting forwarded packets; paren error in checking
c route
e
s 00006/00000/00223
d D 6.3 83/12/15 15:18:33 karels 54 53
c abandon old route if marked ~RTF_UP, reallocate.
e
s 00001/00001/00222
d D 6.2 83/10/22 14:48:57 sam 53 52
c wasn't handling routes to host properly (from bill croft)
e
s 00000/00000/00223
d D 6.1 83/07/29 07:11:51 sam 52 51
c 4.2 distribution
e
s 00001/00003/00222
d D 1.49 83/05/27 13:45:21 sam 51 50
c lint found this one...
e
s 00003/00001/00222
d D 1.48 83/05/15 17:20:28 sam 50 49
c one more time, this time mtpr.h is vax specific
e
s 00020/00019/00203
d D 1.47 83/05/12 15:03:59 sam 49 48
c fix ip packet forwarding to not stomp on headers when fragmented;
e
s 00007/00004/00215
d D 1.46 83/02/10 22:11:34 sam 48 47
c remove /usr/include dependencies
e
s 00005/00007/00214
d D 1.45 83/01/17 20:21:00 sam 47 46
c do broadcast mapping in drivers; sanity check against bind botch
e
s 00001/00001/00220
d D 1.44 83/01/08 16:24:35 sam 46 45
c casting problem
e
s 00017/00006/00204
d D 1.43 83/01/04 23:36:09 sam 45 43
c clean up some stuff; map Internet broadcast address to 
c hardware broadcast address and don't allow fragmentation on broadcasts
e
s 00017/00006/00204
d R 1.43 83/01/04 23:19:51 sam 44 43
c clean up some stuff; map broadcast addresses to interface values
c and don't allow broadcast packets to be fragmented
e
s 00001/00001/00209
d D 1.42 82/12/30 12:33:13 sam 43 42
c missing parameter
e
s 00000/00006/00210
d D 1.41 82/10/30 13:03:29 root 42 41
c get rid of conditional htons/ntohs etc
e
s 00000/00000/00216
d D 1.40 82/10/20 01:22:55 root 41 40
c lint
e
s 00001/00001/00215
d D 1.39 82/10/17 22:47:39 root 40 39
c lint
e
s 00003/00003/00213
d D 1.38 82/10/17 14:55:32 root 39 38
c fix lint
e
s 00001/00001/00215
d D 1.37 82/10/13 22:44:05 root 38 37
c move mtpr.h to vax directory
e
s 00004/00004/00212
d D 1.36 82/10/09 05:46:15 wnj 37 36
c localize header files
e
s 00000/00002/00216
d D 1.35 82/06/20 00:54:35 sam 36 35
c purge COUNT stuff now that we can use gprof
e
s 00001/00001/00217
d D 1.34 82/06/13 23:01:52 sam 35 34
c add class a/b/c net #'s and purge logical host kludge code
e
s 00045/00020/00173
d D 1.33 82/06/12 23:19:33 wnj 34 33
c now the routing code might wokr
e
s 00025/00013/00168
d D 1.32 82/04/10 18:26:42 sam 33 32
c invert output path to pass back error indications
e
s 00005/00004/00176
d D 1.31 82/03/31 20:36:50 sam 32 31
c routing tried and working, add logical host stuff
e
s 00006/00002/00174
d D 1.30 82/03/30 19:57:29 sam 31 30
c routing code now operational
e
s 00009/00028/00167
d D 1.29 82/03/30 11:32:45 sam 30 29
c with routing, but not forwarding
e
s 00015/00009/00180
d D 1.28 82/03/29 11:32:44 sam 29 28
c first cut (incomplete) at routing
e
s 00043/00010/00146
d D 1.27 82/03/28 14:23:00 sam 28 27
c convert interfaces to sockaddr's and add hooks for routing
e
s 00005/00001/00151
d D 1.26 82/03/15 04:44:20 wnj 27 26
c interfac queueing, restrictions on packets, tcp keep alives done 
c properly, bug fix to raw
e
s 00006/00006/00146
d D 1.25 82/02/18 11:59:30 root 26 25
c fixes to fragmentation code (feldman)
e
s 00008/00003/00144
d D 1.24 82/02/12 15:16:48 wnj 25 24
c getting reassembly to work
e
s 00001/00001/00146
d D 1.23 82/01/19 07:29:56 root 24 23
c m_get(0) -> m_get(M_DONTWAIT)
e
s 00001/00001/00146
d D 1.22 81/12/11 22:15:09 root 23 22
c lint
e
s 00005/00001/00142
d D 1.21 81/12/09 20:44:30 wnj 22 21
c bug fixes for hlen
e
s 00033/00058/00110
d D 1.20 81/11/26 11:56:47 wnj 21 20
c before carry to ARPAVAX
e
s 00001/00000/00167
d D 1.19 81/11/24 07:53:44 wnj 20 19
c minor fixups pre tcp<->spec coordination
e
s 00000/00001/00167
d D 1.18 81/11/23 00:06:27 wnj 19 18
c caller now sets ip_ttl (&& ip_len!)
e
s 00001/00000/00167
d D 1.17 81/11/21 15:20:57 wnj 18 17
c define IMPLOOP
e
s 00001/00001/00166
d D 1.16 81/11/20 14:41:51 wnj 17 16
c more lint
e
s 00009/00005/00158
d D 1.15 81/11/20 00:46:56 wnj 16 15
c linted
e
s 00099/00065/00064
d D 1.14 81/11/18 15:37:30 wnj 15 14
c more cleanup
e
s 00015/00013/00114
d D 1.13 81/11/16 14:17:07 wnj 14 13
c more lint
e
s 00002/00001/00125
d D 1.12 81/11/15 12:59:50 wnj 13 12
c listing
e
s 00007/00007/00119
d D 1.11 81/11/08 16:24:52 wnj 12 11
c first listing
e
s 00002/00000/00124
d D 1.10 81/11/02 19:48:15 wnj 11 10
c setsoftnet() in IMPLOOP so it will work
e
s 00001/00001/00123
d D 1.9 81/11/01 22:32:08 wnj 10 9
c minor fixups
e
s 00015/00015/00109
d D 1.8 81/10/31 14:33:19 wnj 9 8
c checksum macro for ip output
e
s 00001/00001/00123
d D 1.7 81/10/31 12:01:28 wnj 8 7
c faster imp code...
e
s 00046/00129/00078
d D 1.6 81/10/30 19:27:11 wnj 7 6
c name changes pre rearrange
e
s 00018/00015/00189
d D 1.5 81/10/29 20:26:54 wnj 6 4
c cleanup of header files
e
s 00075/00134/00070
d R 1.5 81/10/26 02:09:37 wnj 5 4
c first compile of major cleanup
e
s 00002/00002/00202
d D 1.4 81/10/23 11:43:56 wnj 4 3
c working with snd_copy incr ref cnt
e
s 00003/00000/00201
d D 1.3 81/10/21 19:06:40 wnj 3 2
c cleanup the headers
e
s 00049/00048/00152
d D 1.2 81/10/18 15:52:37 wnj 2 1
c cleanup imp_snd, arpa_ether, more robuts memall, remove netprepr
e
s 00200/00000/00000
d D 1.1 81/10/14 09:56:57 wnj 1 0
c date and time created 81/10/14 09:56:57 by wnj
e
u
U
t
T
I 18
D 21
#define IMPLOOP
E 21
E 18
I 1
D 15
/* %M% %I% %E% */
E 15
I 15
D 59
/*	%M%	%I%	%E%	*/
E 59
I 59
/*
D 68
 * Copyright (c) 1982 Regents of the University of California.
E 68
I 68
D 79
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 79
I 79
D 86
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
E 86
I 86
D 98
 * Copyright (c) 1982, 1986, 1988, 1990 Regents of the University of California.
E 86
E 79
E 68
D 74
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 74
I 74
 * All rights reserved.
E 98
I 98
D 104
 * Copyright (c) 1982, 1986, 1988, 1990, 1993 Regents of the University
 * of California.  All rights reserved.
E 104
I 104
 * Copyright (c) 1982, 1986, 1988, 1990, 1993
D 106
 *	Regents of the University of California.  All rights reserved.
E 106
I 106
 *	The Regents of the University of California.  All rights reserved.
E 106
E 104
E 98
 *
D 88
 * Redistribution and use in source and binary forms are permitted
D 80
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 80
I 80
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
E 88
I 88
D 97
 * %sccs.include.redist.c%
E 97
I 97
D 98
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
E 98
I 98
 * %sccs.include.redist.c%
E 98
E 97
E 88
E 80
E 74
 *
D 97
 *	%W% (Berkeley) %G%
E 97
I 97
D 98
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)ip_output.c	7.28 (Berkeley) 2/7/93
E 98
I 98
 *	%W% (Berkeley) %G%
E 98
E 97
 */
E 59
E 15
I 3

E 3
D 57
#include "../h/param.h"
D 6
#include "../bbnnet/net.h"
I 3
#include "../bbnnet/mbuf.h"
#include "../bbnnet/host.h"
E 3
#include "../bbnnet/tcp.h"
#include "../bbnnet/ip.h"
#include "../bbnnet/imp.h"
#include "../bbnnet/ucb.h"
E 6
I 6
#include "../h/mbuf.h"
I 11
D 38
#include "../h/mtpr.h"
E 38
I 38
D 48
#include "../vax/mtpr.h"
E 48
I 48
#include "../h/errno.h"
E 48
E 38
E 11
#include "../h/socket.h"
I 9
D 10
#include "../inet/cksum.h"
E 10
I 10
D 12
#include "../inet/inet_cksum.h"
E 10
E 9
#include "../inet/inet.h"
#include "../inet/inet_systm.h"
#include "../inet/imp.h"
#include "../inet/inet_host.h"
#include "../inet/ip.h"
#include "../inet/tcp.h"
E 12
I 12
D 15
#include "../net/inet_cksum.h"
E 15
I 15
#include "../h/socketvar.h"
E 57
I 57
D 94
#include "param.h"
I 81
#include "malloc.h"
E 81
#include "mbuf.h"
#include "errno.h"
I 60
#include "protosw.h"
E 60
#include "socket.h"
#include "socketvar.h"
E 94
I 94
#include <sys/param.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/errno.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
E 94
E 57
I 48

D 94
#include "../net/if.h"
#include "../net/route.h"
E 94
I 94
#include <net/if.h>
#include <net/route.h>
E 94

E 48
E 15
D 21
#include "../net/inet.h"
#include "../net/inet_systm.h"
#include "../net/imp.h"
E 21
I 21
D 37
#include "../net/in.h"
#include "../net/in_systm.h"
E 37
I 37
D 57
#include "../netinet/in.h"
#include "../netinet/in_systm.h"
E 37
D 48
#include "../net/if.h"
E 48
E 21
D 16
#include "../net/inet_host.h"
E 16
D 37
#include "../net/ip.h"
D 13
#include "../net/tcp.h"
E 13
I 13
#include "../net/ip_var.h"
E 37
I 37
#include "../netinet/ip.h"
#include "../netinet/ip_var.h"
E 57
I 57
D 94
#include "in.h"
I 60
D 85
#include "in_pcb.h"
E 85
E 60
#include "in_systm.h"
I 58
D 85
#include "in_var.h"
E 85
E 58
#include "ip.h"
I 85
#include "in_pcb.h"
#include "in_var.h"
E 85
#include "ip_var.h"
E 94
I 94
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/in_pcb.h>
#include <netinet/in_var.h>
#include <netinet/ip_var.h>
E 94
E 57
E 37
I 28
D 48
#include "../net/route.h"
I 33
#include <errno.h>
E 48
I 48

D 50
#include "../machine/mtpr.h"
E 50
I 50
#ifdef vax
D 69
#include "../vax/mtpr.h"
E 69
I 69
D 82
#include "../machine/mtpr.h"
E 82
I 82
D 94
#include "machine/mtpr.h"
E 94
I 94
#include <machine/mtpr.h>
E 94
E 82
E 69
#endif
E 50
E 48
E 33
E 28
E 13
E 12
E 6

I 60
D 93
struct mbuf *ip_insertoptions();
E 93
I 93
D 103
struct	mbuf *ip_insertoptions __P((struct mbuf *, struct mbuf *, int *));
static	void ip_mloopback __P((struct ifnet *, struct mbuf *,
	    struct sockaddr_in *));
E 103
I 103
static struct mbuf *ip_insertoptions __P((struct mbuf *, struct mbuf *, int *));
static void ip_mloopback
	__P((struct ifnet *, struct mbuf *, struct sockaddr_in *));
E 103
E 93

/*
 * IP output.  The packet in mbuf chain m contains a skeletal IP
D 71
 * header (as ipovly).  The mbuf chain containing the packet will
 * be freed.  The mbuf opt, if present, will not be freed.
E 71
I 71
 * header (with len, off, ttl, proto, tos, src, dst).
 * The mbuf chain containing the packet will be freed.
 * The mbuf opt, if present, will not be freed.
E 71
 */
E 60
I 34
D 51
int	ipnorouteprint = 0;

E 51
E 34
D 2
/*****************************************************************************
*                                                                            *
*         internet level output:  called from higher level protocol          *
*         or "raw internet driver."  passed a pointer to an mbuf             *
*         chain containing the message to be sent, a partially filled        *
*         in ip leader, and room for an 1822 leader and 2 pointers.          *
*         this routine does fragmentation and mapping of ip parameters       *
*         to 1822 ones.                                                      *
*                                                                            *
*****************************************************************************/

E 2
D 15
ip_output(mp)
D 2
struct mbuf *mp;
E 2
I 2
	struct mbuf *mp;
E 15
I 15
D 21
ip_output(m)
E 21
I 21
D 27
ip_output(m, opt)
E 27
I 27
D 28
ip_output(m, opt, allowbroadcast)
E 28
I 28
D 49
ip_output(m, opt, ro, allowbroadcast)
E 49
I 49
D 75
ip_output(m, opt, ro, flags)
E 49
E 28
E 27
E 21
	struct mbuf *m;
E 75
I 75
D 93
ip_output(m0, opt, ro, flags)
E 93
I 93
int
D 95
ip_output(m0, opt, ro, flags
#ifdef MULTICAST
    , imo
#endif
    )
E 95
I 95
ip_output(m0, opt, ro, flags, imo)
E 95
E 93
	struct mbuf *m0;
E 75
I 21
	struct mbuf *opt;
I 28
	struct route *ro;
E 28
I 27
D 49
	int allowbroadcast;
E 49
I 49
	int flags;
I 93
D 95
#ifdef MULTICAST
E 95
	struct ip_moptions *imo;
D 95
#endif
E 95
E 93
E 49
E 27
E 21
E 15
E 2
{
D 15
	register i, rnd;
	register struct mbuf *m, *n;
	register struct ip *p;
	struct mbuf *mm;
	int hlen, adj, max, len, off;
E 15
I 15
D 60
	register struct ip *ip = mtod(m, struct ip *);
E 60
I 60
D 75
	register struct ip *ip;
E 75
I 75
	register struct ip *ip, *mhip;
E 75
E 60
I 21
	register struct ifnet *ifp;
E 21
D 22
	int len, hlen = ip->ip_hl << 2, off;
E 22
I 22
D 29
	int len, hlen = sizeof (struct ip), off;
E 29
I 29
D 30
	int len, hlen = sizeof (struct ip), off, direct;
E 29
I 28
	struct sockaddr_in tempaddr;	/* temp kludge */
E 30
I 30
D 33
	int len, hlen = sizeof (struct ip), off;
E 33
I 33
D 75
	int len, hlen = sizeof (struct ip), off, error = 0;
E 75
I 75
	register struct mbuf *m = m0;
	register int hlen = sizeof (struct ip);
	int len, off, error = 0;
E 75
E 33
E 30
	struct route iproute;
I 29
D 56
	struct sockaddr *dst;
E 56
I 56
	struct sockaddr_in *dst;
I 85
	struct in_ifaddr *ia;
E 85
E 56
E 29
E 28
E 22
E 15

I 81
D 89
if ((m->m_flags & M_PKTHDR) == 0)
panic("ip_output no HDR");
E 89
I 89
#ifdef	DIAGNOSTIC
	if ((m->m_flags & M_PKTHDR) == 0)
		panic("ip_output no HDR");
#endif
E 89
E 81
D 36
COUNT(IP_OUTPUT);
E 36
I 22
D 60
	if (opt)				/* XXX */
D 23
		m_free(opt);			/* XXX */
E 23
I 23
		(void) m_free(opt);		/* XXX */
E 60
I 60
D 75
	if (opt)
		m = ip_insertoptions(m, opt, &hlen);
E 75
I 75
	if (opt) {
		m = ip_insertoptions(m, opt, &len);
		hlen = len;
	}
E 75
	ip = mtod(m, struct ip *);
E 60
E 23
E 22
D 9
	p = (struct ip *)((int)mp + mp->m_off); /* -> ip header */
D 2
	hlen = sizeof(struct ip);               /* header length */
E 2
I 2
	hlen = sizeof (struct ip);               /* header length */
E 9
I 9
D 15
	p = mtod(mp, struct ip *);
	hlen = sizeof (struct ip);
E 9
E 2

E 15
D 2
	/* fill in unspecified fields and byte swap others */

	p->ip_v = IPVERSION;    
E 2
I 2
	/*
D 15
	 * Fill in and byte swap ip header.
E 15
I 15
	 * Fill in IP header.
E 15
	 */
D 15
	p->ip_v = IPVERSION;
E 2
	p->ip_hl = hlen >> 2;
D 6
	p->ip_off = 0 | (p->ip_off & ip_df);
E 6
I 6
	p->ip_off = 0 | (p->ip_off & IP_DF);
E 6
	p->ip_ttl = MAXTTL;
I 13
D 14
/*###35 [cc] ip_id undefined %%%*/
E 14
E 13
D 6
	p->ip_id = netcb.n_ip_cnt++;
E 6
I 6
	p->ip_id = ip_id++;
E 15
I 15
D 49
	ip->ip_v = IPVERSION;
E 49
D 55
	ip->ip_hl = hlen >> 2;
E 55
D 49
	ip->ip_off &= IP_DF;
D 19
	ip->ip_ttl = MAXTTL;
E 19
D 21
	ip->ip_id = ip_id++;
E 21
I 21
	ip->ip_id = htons(ip_id++);
E 49
I 49
D 97
	if ((flags & IP_FORWARDING) == 0) {
E 97
I 97
	if ((flags & (IP_FORWARDING|IP_RAWOUTPUT)) == 0) {
E 97
		ip->ip_v = IPVERSION;
		ip->ip_off &= IP_DF;
		ip->ip_id = htons(ip_id++);
D 55
	}
E 55
I 55
		ip->ip_hl = hlen >> 2;
I 95
		ipstat.ips_localout++;
E 95
D 58
	} else
		ip->ip_id = htons(ip->ip_id);
E 58
I 58
D 60
	}
E 60
I 60
D 83
	} else
E 83
I 83
	} else {
E 83
		hlen = ip->ip_hl << 2;
E 60
E 58
E 55
E 49
E 21
E 15
E 6
D 83

E 83
I 83
D 95
		ipstat.ips_localout++;
E 95
	}
E 83
I 28
D 30
#ifdef notdef
E 30
E 28
D 7
	if (p->ip_len > MTU) {          /* must fragment */
D 6
		if (p->ip_off & ip_df)
E 6
I 6
		if (p->ip_off & IP_DF)
E 6
D 2
			return(FALSE);
E 2
I 2
			return (0);
E 2
		max = MTU - hlen;       /* maximum data length in fragment */
		len = p->ip_len - hlen; /* data length */
		off = 0;                /* fragment offset */
		m = mp;

		while (len > 0) {

			/* correct the header */

			p->ip_off |= off >> 3;

			/* find the end of the fragment */

			i = -hlen;
			while (m != NULL) {
				i += m->m_len;
				if (i > max)
					break;
				n = m;
				m = m->m_next;
			}

			if (i < max || m == NULL) {     /* last fragment */
D 6
				p->ip_off = p->ip_off & ~ip_mf;
E 6
I 6
				p->ip_off = p->ip_off &~ IP_MF;
E 6
				p->ip_len = i + hlen;
E 7
I 7
D 14
	if (p->ip_len <= MTU)
		return (ip_send(p));
E 14
I 14
D 15
	if (p->ip_len <= MTU) {
		ip_send(p);
E 15
I 15
	/*
I 21
D 29
	 * Find interface for this packet.
E 29
I 29
D 34
	 * Find interface for this packet in the routing
	 * table.  Note each interface has placed itself
D 31
	 * in there at boot time, so call on route degenerates
	 * to if_ifonnetof(ip->ip_dst.s_net).
E 31
I 31
	 * in there at boot time, so calls to rtalloc
	 * degenerate to if_ifonnetof(ip->ip_dst.s_net).
E 34
I 34
	 * Route packet.
E 34
E 31
E 29
	 */
D 28
	ifp = if_ifonnetof(ip->ip_dst);
	if (ifp == 0) {
		ifp = if_gatewayfor(ip->ip_dst);
		if (ifp == 0)
			goto bad;
E 28
I 28
	if (ro == 0) {
		ro = &iproute;
		bzero((caddr_t)ro, sizeof (*ro));
E 28
	}
I 34
D 56
	dst = &ro->ro_dst;
E 56
I 56
	dst = (struct sockaddr_in *)&ro->ro_dst;
I 63
	/*
	 * If there is a cached route,
	 * check that it is to the same destination
	 * and is still up.  If not, free it and try again.
	 */
	if (ro->ro_rt && ((ro->ro_rt->rt_flags & RTF_UP) == 0 ||
	   dst->sin_addr.s_addr != ip->ip_dst.s_addr)) {
		RTFREE(ro->ro_rt);
		ro->ro_rt = (struct rtentry *)0;
	}
E 63
E 56
E 34
I 27
D 28
	if (!allowbroadcast && ifp->if_broadaddr.s_addr != 0 &&
	    ifp->if_broadaddr.s_addr == ip->ip_dst.s_addr)
E 28
I 28
	if (ro->ro_rt == 0) {
D 30
		ro->ro_dest.sin_addr = ip->ip_dst;
		ro->ro_dest.sin_family = AF_INET;
D 29
		route(ro);
E 29
I 29
		direct = allocroute(ro);
E 30
I 30
D 56
		ro->ro_dst.sa_family = AF_INET;
		((struct sockaddr_in *)&ro->ro_dst)->sin_addr = ip->ip_dst;
E 56
I 56
		dst->sin_family = AF_INET;
I 81
		dst->sin_len = sizeof(*dst);
E 81
		dst->sin_addr = ip->ip_dst;
E 56
I 34
D 62
		/*
D 49
		 * If routing to interface only, short circuit routing lookup.
E 49
I 49
		 * If routing to interface only,
		 * short circuit routing lookup.
E 49
		 */
D 49
		if (ro == &routetoif) {
			/* check ifp is AF_INET??? */
E 49
I 49
		if (flags & IP_ROUTETOIF) {
E 49
D 35
			ifp = if_ifonnetof(ip->ip_dst.s_net);
E 35
I 35
D 40
			ifp = if_ifonnetof(IN_NETOF(ip->ip_dst));
E 40
I 40
D 58
			ifp = if_ifonnetof(in_netof(ip->ip_dst));
E 40
E 35
D 49
			if (ifp == 0)
				goto unreachable;
E 49
I 49
			if (ifp == 0) {
E 58
I 58
			struct in_ifaddr *ia;
			ia = in_iaonnetof(in_netof(ip->ip_dst));
			if (ia == 0) {
E 58
				error = ENETUNREACH;
				goto bad;
			}
I 58
			ifp = ia->ia_ifp;
E 58
E 49
			goto gotif;
E 62
I 62
	}
	/*
	 * If routing to interface only,
	 * short circuit routing lookup.
	 */
I 100
#define ifatoia(ifa)	((struct in_ifaddr *)(ifa))
#define sintosa(sin)	((struct sockaddr *)(sin))
E 100
	if (flags & IP_ROUTETOIF) {
D 85
		struct in_ifaddr *ia;
E 85
D 65
		ia = in_iaonnetof(in_netof(ip->ip_dst));
E 65
I 65
D 100

D 67
		ia = (struct in_ifadddr *)ifa_ifwithdstaddr(dst);
E 67
I 67
D 78
		ia = (struct in_ifaddr *)ifa_ifwithdstaddr(dst);
E 78
I 78
		ia = (struct in_ifaddr *)ifa_ifwithdstaddr((struct sockaddr *)dst);
E 78
E 67
		if (ia == 0)
			ia = in_iaonnetof(in_netof(ip->ip_dst));
E 65
		if (ia == 0) {
E 100
I 100
		if ((ia = ifatoia(ifa_ifwithdstaddr(sintosa(dst)))) == 0 &&
		    (ia = ifatoia(ifa_ifwithnet(sintosa(dst)))) == 0) {
E 100
I 95
			ipstat.ips_noroute++;
E 95
			error = ENETUNREACH;
			goto bad;
E 62
		}
E 34
D 62
		rtalloc(ro);
I 54
D 55
	} else if (ro->ro_rt->rt_flags & RTF_UP == 0) {
E 55
I 55
	} else if ((ro->ro_rt->rt_flags & RTF_UP) == 0) {
E 62
I 62
		ifp = ia->ia_ifp;
I 100
		ip->ip_ttl = 1;
E 100
	} else {
E 62
E 55
D 63
		/*
D 62
		 * The old route has gone away; try for a new one.
E 62
I 62
		 * If there is a cached route,
		 * check that it is to the same destination
		 * and is still up.  If not, free it and try again.
E 62
		 */
D 62
		rtfree(ro->ro_rt);
I 58
		ro->ro_rt = NULL;
E 58
		rtalloc(ro);
E 62
I 62
		if (ro->ro_rt && ((ro->ro_rt->rt_flags & RTF_UP) == 0 ||
		   dst->sin_addr.s_addr != ip->ip_dst.s_addr)) {
			RTFREE(ro->ro_rt);
			ro->ro_rt = (struct rtentry *)0;
			dst->sin_addr = ip->ip_dst;
		}
E 63
		if (ro->ro_rt == 0)
			rtalloc(ro);
D 86
		if (ro->ro_rt == 0 || (ifp = ro->ro_rt->rt_ifp) == 0) {
D 72
			error = ENETUNREACH;
E 72
I 72
			if (in_localaddr(ip->ip_dst))
				error = EHOSTUNREACH;
			else
				error = ENETUNREACH;
E 86
I 86
		if (ro->ro_rt == 0) {
I 95
			ipstat.ips_noroute++;
E 95
			error = EHOSTUNREACH;
E 86
E 72
			goto bad;
		}
I 85
D 100
		ia = (struct in_ifaddr *)ro->ro_rt->rt_ifa;
E 100
I 100
		ia = ifatoia(ro->ro_rt->rt_ifa);
E 100
I 86
		ifp = ro->ro_rt->rt_ifp;
E 86
E 85
		ro->ro_rt->rt_use++;
D 70
		if (ro->ro_rt->rt_flags & (RTF_GATEWAY|RTF_HOST))
E 70
I 70
		if (ro->ro_rt->rt_flags & RTF_GATEWAY)
E 70
D 81
			dst = (struct sockaddr_in *)&ro->ro_rt->rt_gateway;
E 81
I 81
			dst = (struct sockaddr_in *)ro->ro_rt->rt_gateway;
E 81
E 62
E 54
I 31
D 32
		if (ro != &iproute)
			ro->ro_rt->rt_refcnt++;
E 32
E 31
E 30
E 29
	}
I 93
D 95
#ifdef MULTICAST
E 95
	if (IN_MULTICAST(ntohl(ip->ip_dst.s_addr))) {
		struct in_multi *inm;
		extern struct ifnet loif;
D 96
		extern struct socket *ip_mrouter;
E 96

		m->m_flags |= M_MCAST;
		/*
		 * IP destination address is multicast.  Make sure "dst"
		 * still points to the address in "ro".  (It may have been
		 * changed to point to a gateway address, above.)
		 */
		dst = (struct sockaddr_in *)&ro->ro_dst;
		/*
		 * See if the caller provided any multicast options
		 */
		if (imo != NULL) {
			ip->ip_ttl = imo->imo_multicast_ttl;
			if (imo->imo_multicast_ifp != NULL)
				ifp = imo->imo_multicast_ifp;
		} else
			ip->ip_ttl = IP_DEFAULT_MULTICAST_TTL;
		/*
		 * Confirm that the outgoing interface supports multicast.
		 */
		if ((ifp->if_flags & IFF_MULTICAST) == 0) {
I 95
			ipstat.ips_noroute++;
E 95
			error = ENETUNREACH;
			goto bad;
		}
		/*
		 * If source address not specified yet, use address
		 * of outgoing interface.
		 */
		if (ip->ip_src.s_addr == INADDR_ANY) {
			register struct in_ifaddr *ia;

			for (ia = in_ifaddr; ia; ia = ia->ia_next)
				if (ia->ia_ifp == ifp) {
					ip->ip_src = IA_SIN(ia)->sin_addr;
					break;
				}
		}

		IN_LOOKUP_MULTI(ip->ip_dst, ifp, inm);
		if (inm != NULL &&
		   (imo == NULL || imo->imo_multicast_loop)) {
			/*
			 * If we belong to the destination multicast group
			 * on the outgoing interface, and the caller did not
			 * forbid loopback, loop back a copy.
			 */
			ip_mloopback(ifp, m, dst);
		}
#ifdef MROUTING
D 96
		else if (ip_mrouter && (flags & IP_FORWARDING) == 0) {
E 96
I 96
		else {
E 96
			/*
			 * If we are acting as a multicast router, perform
			 * multicast forwarding as if the packet had just
			 * arrived on the interface to which we are about
			 * to send.  The multicast forwarding function
			 * recursively calls this function, using the
			 * IP_FORWARDING flag to prevent infinite recursion.
			 *
			 * Multicasts that are looped back by ip_mloopback(),
			 * above, will be forwarded by the ip_input() routine,
			 * if necessary.
			 */
D 96
			if (ip_mforward(m, ifp) != 0) {
				m_freem(m);
				goto done;
E 96
I 96
			extern struct socket *ip_mrouter;
			if (ip_mrouter && (flags & IP_FORWARDING) == 0) {
				if (ip_mforward(m, ifp) != 0) {
					m_freem(m);
					goto done;
				}
E 96
			}
		}
#endif
		/*
		 * Multicasts with a time-to-live of zero may be looped-
		 * back, above, but must not be transmitted on a network.
		 * Also, multicasts addressed to the loopback interface
		 * are not sent -- the above call to ip_mloopback() will
		 * loop back a copy if this host actually belongs to the
		 * destination group on the loopback interface.
		 */
		if (ip->ip_ttl == 0 || ifp == &loif) {
			m_freem(m);
			goto done;
		}

		goto sendit;
	}
D 95
#endif
E 95
E 93
D 30
	if (ro->ro_rt == 0 || (ifp = ro->ro_rt->rt_ifp) == 0)
E 30
I 30
D 34
	if (ro->ro_rt == 0 || (ifp = ro->ro_rt->rt_ifp) == 0) {
D 32
printf("no route to %x\n", ip->ip_dst.s_addr);
E 32
I 32
D 33
		printf("no route to %x (from %x, len %d)\n",
		    ip->ip_dst.s_addr, ip->ip_src.s_addr, ip->ip_len);
E 33
I 33
		extern int ipprintfs;
E 34
I 34
D 49
	if (ro->ro_rt == 0 || (ifp = ro->ro_rt->rt_ifp) == 0)
		goto unreachable;
E 49
I 49
D 62
	if (ro->ro_rt == 0 || (ifp = ro->ro_rt->rt_ifp) == 0) {
		error = ENETUNREACH;
		goto bad;
	}
E 49
	ro->ro_rt->rt_use++;
D 53
	if (ro->ro_rt->rt_flags & RTF_GATEWAY)
E 53
I 53
	if (ro->ro_rt->rt_flags & (RTF_GATEWAY|RTF_HOST))
E 53
D 56
		dst = &ro->ro_rt->rt_gateway;
E 56
I 56
		dst = (struct sockaddr_in *)&ro->ro_rt->rt_gateway;
E 56
gotif:
E 62
I 59
#ifndef notdef
	/*
	 * If source address not specified yet, use address
	 * of outgoing interface.
	 */
D 85
	if (ip->ip_src.s_addr == INADDR_ANY) {
		register struct in_ifaddr *ia;

		for (ia = in_ifaddr; ia; ia = ia->ia_next)
			if (ia->ia_ifp == ifp) {
				ip->ip_src = IA_SIN(ia)->sin_addr;
				break;
			}
	}
E 85
I 85
	if (ip->ip_src.s_addr == INADDR_ANY)
		ip->ip_src = IA_SIN(ia)->sin_addr;
E 85
#endif
E 59
I 47
D 58
#ifndef notdef
E 58
E 47
	/*
D 58
	 * If source address not specified yet, use address
	 * of outgoing interface.
	 */
D 45
	if (ip->ip_src.s_addr == 0)
E 45
I 45
D 47
	if (ip->ip_src.s_addr == INADDR_ANY)
E 47
I 47
	if (in_lnaof(ip->ip_src) == INADDR_ANY)
E 47
E 45
		ip->ip_src.s_addr =
		    ((struct sockaddr_in *)&ifp->if_addr)->sin_addr.s_addr;
I 47
#endif
E 47
E 34

D 34
		if (ipprintfs)
			printf("no route to %x (from %x, len %d)\n",
			    ip->ip_dst.s_addr, ip->ip_src.s_addr, ip->ip_len);
		error = ENETUNREACH;
E 33
E 32
E 30
E 28
		goto bad;
I 29
D 30
	dst = direct ? (struct sockaddr *)&ro->ro_dest :
		&ro->ro_rt->rt_gateway;
E 29
I 28
#else
	/* interim kludge before routing fallout */
	ifp = if_ifonnetof(ip->ip_dst.s_net);
	if (ifp == 0)
		goto bad;
	tempaddr.sin_family = AF_INET;
	tempaddr.sin_addr = ip->ip_dst;
#endif
E 28
E 27

E 30
I 30
D 32
}
E 32
I 32
	}
E 32
D 33
	dst = ro->ro_rt->rt_flags&RTF_DIRECT ?
E 33
I 33
	dst = ro->ro_rt->rt_flags & RTF_DIRECT ?
E 33
	    (struct sockaddr *)&ro->ro_dst : &ro->ro_rt->rt_gateway;
I 32
	if (ro == &iproute)
		RTFREE(ro->ro_rt);
E 34
I 34
	/*
E 58
D 45
	 * Have interface for packet.  Allow
	 * broadcasts only by authorized users.
E 45
I 45
D 47
	 * Map broadcast address to hardware's broadcast
	 * address and verify user is allowed to send
E 47
I 47
	 * Look for broadcast address and
	 * and verify user is allowed to send
E 47
	 * such a packet.
E 45
	 */
E 34
E 32
E 30
I 28
D 45
	if (!allowbroadcast && (ifp->if_flags & IFF_BROADCAST)) {
E 45
I 45
D 51
	if (in_lnaof(dst) == INADDR_ANY) {
E 51
I 51
D 56
	if (in_lnaof(((struct sockaddr_in *)dst)->sin_addr) == INADDR_ANY) {
E 56
I 56
D 58
	if (in_lnaof(dst->sin_addr) == INADDR_ANY) {
E 58
I 58
D 100
	if (in_broadcast(dst->sin_addr)) {
E 100
I 100
	if (in_broadcast(dst->sin_addr, ifp)) {
E 100
E 58
E 56
E 51
E 45
D 47
		struct sockaddr_in *sin;

E 47
D 45
		sin = (struct sockaddr_in *)&ifp->if_broadaddr;
D 33
		if (sin->sin_addr.s_addr == ip->ip_dst.s_addr)
E 33
I 33
		if (sin->sin_addr.s_addr == ip->ip_dst.s_addr) {
E 45
I 45
		if ((ifp->if_flags & IFF_BROADCAST) == 0) {
			error = EADDRNOTAVAIL;
			goto bad;
		}
D 49
		if (!allowbroadcast) {
E 49
I 49
		if ((flags & IP_ALLOWBROADCAST) == 0) {
E 49
E 45
D 34
			error = EPERM;		/* ??? */
E 34
I 34
			error = EACCES;
E 34
E 33
			goto bad;
I 33
		}
I 45
		/* don't allow broadcast messages to be fragmented */
D 87
		if (ip->ip_len > ifp->if_mtu) {
E 87
I 87
		if ((u_short)ip->ip_len > ifp->if_mtu) {
E 87
			error = EMSGSIZE;
			goto bad;
		}
I 81
		m->m_flags |= M_BCAST;
E 81
D 47
		sin = (struct sockaddr_in *)&ifp->if_broadaddr;
D 46
		dst.sin_addr = sin->sin_addr;
E 46
I 46
		((struct sockaddr_in *)dst)->sin_addr = sin->sin_addr;
E 47
E 46
E 45
E 33
D 95
	}
E 95
I 95
	} else
		m->m_flags &= ~M_BCAST;
E 95

I 93
D 95
#ifdef MULTICAST
E 95
sendit:
D 95
#endif
E 95
E 93
E 28
	/*
E 21
	 * If small enough for interface, can just send directly.
	 */
D 21
	if (ip->ip_len <= MTU) {
		ip_send(ip);
E 15
		return;
E 21
I 21
D 87
	if (ip->ip_len <= ifp->if_mtu) {
E 87
I 87
	if ((u_short)ip->ip_len <= ifp->if_mtu) {
E 87
I 22
D 39
#if vax
E 39
I 39
D 42
#if vax || pdp11 || ns16032
E 42
E 39
E 22
		ip->ip_len = htons((u_short)ip->ip_len);
		ip->ip_off = htons((u_short)ip->ip_off);
I 22
D 42
#endif
E 42
E 22
		ip->ip_sum = 0;
		ip->ip_sum = in_cksum(m, hlen);
I 31
D 34
		ro->ro_rt->rt_use++;
E 31
D 28
		return ((*ifp->if_output)(ifp, m, PF_INET));
E 28
I 28
D 29
		return ((*ifp->if_output)(ifp, m,
E 29
D 30
#ifdef notdef
E 30
D 29
		  &ro->ro_rt->rt_dest));
E 29
I 29
		return ((*ifp->if_output)(ifp, m, dst));
E 34
I 34
D 56
		error = (*ifp->if_output)(ifp, m, dst);
E 56
I 56
D 85
		error = (*ifp->if_output)(ifp, m, (struct sockaddr *)dst);
E 85
I 85
		error = (*ifp->if_output)(ifp, m,
				(struct sockaddr *)dst, ro->ro_rt);
E 85
E 56
		goto done;
E 34
E 29
D 30
#else
D 29
		  (struct sockaddr *)&tempaddr));
E 29
I 29
		return ((*ifp->if_output)(ifp, m,
			(struct sockaddr *)&tempaddr));
E 29
#endif
E 30
E 28
E 21
	}
E 14
D 15
	if (p->ip_off & IP_DF)
D 14
		return (0);
E 14
I 14
		return;
E 14
	max = MTU - hlen;
	len = p->ip_len - hlen;
	off = 0;
	m = mp;
	while (len > 0) {
		p->ip_off |= off >> 3;
		i = -hlen;
		while (m != NULL) {
			i += m->m_len;
			if (i > max)
E 7
				break;
D 7

			} else {                        /* more fragments */

				/* allocate header mbuf for next fragment */

				if ((mm = m_get(1)) == NULL)    /* no more bufs */
D 2
					return(FALSE);
E 2
I 2
					return(0);
E 2

D 6
				p->ip_off |= ip_mf;
E 6
I 6
				p->ip_off |= IP_MF;
E 6

				/* terminate fragment at 8 byte boundary (round down) */

				i -= m->m_len;
        			rnd = i & ~7;           /* fragment length */
				adj = i - rnd;          /* leftover in mbuf */
D 2
				p->ip_len = rnd + hlen; 
E 2
I 2
				p->ip_len = rnd + hlen;
E 2

D 2
				/* setup header for next fragment and 
E 2
I 2
				/* setup header for next fragment and
E 2
				   append remaining fragment data */

D 2
				n->m_next = NULL;                   
				mm->m_next = m;        
E 2
I 2
				n->m_next = NULL;
				mm->m_next = m;
E 2
				m = mm;
D 4
				m->m_off = MSIZE - hlen - adj;
E 4
I 4
				m->m_off = MMAXOFF - hlen - adj;
E 4
				m->m_len = hlen + adj;

				/* copy old header to new */

				bcopy(p, (caddr_t)((int)m + m->m_off), hlen);

				/* copy leftover data from previous frag */

				if (adj) {
					n->m_len -= adj;
					bcopy((caddr_t)((int)n + n->m_len + n->m_off),
					      (caddr_t)((int)m + m->m_off + hlen), adj);
				}
			}

			ip_send(p);             /* pass frag to local net level */

			p = (struct ip *)((int)m + m->m_off);   /* -> new hdr */
			len -= rnd;
			off += rnd;
E 7
I 7
			n = m;
			m = m->m_next;
E 15
I 15
D 83

E 83
I 83
D 95
	ipstat.ips_fragmented++;
E 95
E 83
	/*
	 * Too large for interface; fragment if possible.
	 * Must be able to put at least 8 bytes per fragment.
	 */
D 33
	if (ip->ip_off & IP_DF)
E 33
I 33
	if (ip->ip_off & IP_DF) {
		error = EMSGSIZE;
I 95
		ipstat.ips_cantfrag++;
E 95
E 33
		goto bad;
I 33
	}
E 33
D 21
	len = (MTU-hlen) &~ 7;
E 21
I 21
	len = (ifp->if_mtu - hlen) &~ 7;
E 21
D 33
	if (len < 8)
E 33
I 33
	if (len < 8) {
		error = EMSGSIZE;
E 33
		goto bad;
I 33
	}
E 33

I 76
    {
	int mhlen, firstlen = len;
D 81
	struct mbuf **mnext = &m->m_act;
E 81
I 81
	struct mbuf **mnext = &m->m_nextpkt;
E 81

E 76
	/*
D 76
	 * Discard IP header from logical mbuf for m_copy's sake.
	 * Loop through length of segment, make a copy of each
	 * part and output.
E 76
I 76
	 * Loop through length of segment after first fragment,
	 * make new header and copy data of each part and link onto chain.
E 76
	 */
D 75
	m->m_len -= sizeof (struct ip);
	m->m_off += sizeof (struct ip);
D 26
	for (off = 0; off < ip->ip_len; off += len) {
E 26
I 26
	for (off = 0; off < ip->ip_len-hlen; off += len) {
E 26
D 24
		struct mbuf *mh = m_get(0);
E 24
I 24
D 43
		struct mbuf *mh = m_get(M_DONTWAIT);
E 43
I 43
		struct mbuf *mh = m_get(M_DONTWAIT, MT_HEADER);
E 43
E 24
		struct ip *mhip;
E 75
I 75
D 76
	m->m_len -= hlen;
	m->m_off += hlen;
E 76
	m0 = m;
D 76
	for (off = 0; off < ip->ip_len - hlen; off += len) {
		int mhlen;
E 75

E 76
I 76
	mhlen = sizeof (struct ip);
D 87
	for (off = hlen + len; off < ip->ip_len; off += len) {
E 87
I 87
	for (off = hlen + len; off < (u_short)ip->ip_len; off += len) {
E 87
E 76
D 33
		if (mh == 0)
E 33
I 33
D 75
		if (mh == 0) {
E 75
I 75
D 81
		MGET(m, M_DONTWAIT, MT_HEADER);
E 81
I 81
		MGETHDR(m, M_DONTWAIT, MT_HEADER);
E 81
		if (m == 0) {
E 75
			error = ENOBUFS;
I 95
			ipstat.ips_odropped++;
E 95
E 33
D 79
			goto bad;
E 79
I 79
			goto sendorfree;
E 79
I 33
		}
E 33
D 75
		mh->m_off = MMAXOFF - hlen;
		mhip = mtod(mh, struct ip *);
E 75
I 75
D 81
		m->m_off = MMAXOFF - hlen;
E 81
I 81
		m->m_data += max_linkhdr;
E 81
		mhip = mtod(m, struct ip *);
E 75
		*mhip = *ip;
D 16
		if (ip->ip_hl > sizeof (struct ip) >> 2) {
E 16
I 16
		if (hlen > sizeof (struct ip)) {
E 16
D 75
			int olen = ip_optcopy(ip, mhip, off);
			mh->m_len = sizeof (struct ip) + olen;
E 75
I 75
D 76
			mhlen = ip_optcopy(ip, mhip, off) + sizeof (struct ip);
E 76
I 76
			mhlen = ip_optcopy(ip, mhip) + sizeof (struct ip);
E 76
			mhip->ip_hl = mhlen >> 2;
E 75
D 76
		} else
D 75
			mh->m_len = sizeof (struct ip);
E 75
I 75
			mhlen = sizeof (struct ip);
E 76
I 76
		}
E 76
		m->m_len = mhlen;
E 75
D 25
		mhip->ip_off = off;
E 25
I 25
D 66
		mhip->ip_off = off >> 3;
E 66
I 66
D 76
		mhip->ip_off = (off >> 3) + (ip->ip_off & ~IP_MF);
E 76
I 76
		mhip->ip_off = ((off - hlen) >> 3) + (ip->ip_off & ~IP_MF);
E 76
E 66
I 55
		if (ip->ip_off & IP_MF)
			mhip->ip_off |= IP_MF;
E 55
E 25
D 26
		if (off + len >= ip->ip_len)
D 25
			mhip->ip_len = ip->ip_len - off;
E 25
I 25
			len = mhip->ip_len = ip->ip_len - off;
E 26
I 26
D 75
		if (off + len >= ip->ip_len-hlen)
			len = mhip->ip_len = ip->ip_len - hlen - off;
E 26
E 25
		else {
			mhip->ip_len = len;
E 75
I 75
D 76
		if (off + len >= ip->ip_len - hlen)
			len = ip->ip_len - hlen - off;
E 76
I 76
D 87
		if (off + len >= ip->ip_len)
			len = ip->ip_len - off;
E 87
I 87
		if (off + len >= (u_short)ip->ip_len)
			len = (u_short)ip->ip_len - off;
E 87
E 76
		else
E 75
			mhip->ip_off |= IP_MF;
E 15
E 7
D 75
		}
I 20
D 21
		mhip->ip_len += sizeof (struct ip);
E 21
I 21
D 25
		mhip->ip_len = htons((u_short)(mhip->ip_len + sizeof (struct ip)));
E 25
I 25
		mhip->ip_len += sizeof (struct ip);
D 39
#if vax
E 39
I 39
D 42
#if vax || pdp11 || ns16032
E 42
E 39
		mhip->ip_len = htons((u_short)mhip->ip_len);
D 42
#endif
E 42
E 25
E 21
E 20
I 7
D 15
		if (i < max || m == NULL) {
			p->ip_off = p->ip_off &~ IP_MF;
			p->ip_len = i + hlen;
D 14
			return (ip_send(p));
E 14
I 14
			ip_send(p);
			return;
E 15
I 15
		mh->m_next = m_copy(m, off, len);
		if (mh->m_next == 0) {
D 17
			m_free(mh);
E 17
I 17
			(void) m_free(mh);
E 75
I 75
		mhip->ip_len = htons((u_short)(len + mhlen));
		m->m_next = m_copy(m0, off, len);
		if (m->m_next == 0) {
I 99
D 102
			m_free(m);
E 102
I 102
			(void) m_free(m);
E 102
E 99
D 76
			(void) m_free(m);
E 76
E 75
I 33
			error = ENOBUFS;	/* ??? */
I 95
			ipstat.ips_odropped++;
E 95
E 33
E 17
D 76
			goto bad;
E 76
I 76
			goto sendorfree;
E 76
E 15
E 14
		}
I 81
		m->m_pkthdr.len = mhlen + len;
		m->m_pkthdr.rcvif = (struct ifnet *)0;
E 81
I 25
D 39
#if vax
E 39
I 39
D 42
#if vax || pdp11 || ns16032
E 42
E 39
E 25
D 15
		if ((mm = m_get(1)) == NULL)    /* no more bufs */
D 14
			return(0);
E 14
I 14
			return;
E 14
		p->ip_off |= IP_MF;
		i -= m->m_len;
		rnd = i & ~7;
		adj = i - rnd;
		p->ip_len = rnd + hlen;
		n->m_next = NULL;
		mm->m_next = m;
		m = mm;
		m->m_off = MMAXOFF - hlen - adj;
		m->m_len = hlen + adj;
D 14
		bcopy(p, (caddr_t)((int)m + m->m_off), hlen);
E 14
I 14
		bcopy((caddr_t)p, mtod(m, caddr_t), (unsigned)hlen);
E 14
		if (adj) {
			n->m_len -= adj;
D 14
			bcopy((caddr_t)((int)n + n->m_len + n->m_off),
			      (caddr_t)((int)m + m->m_off + hlen), adj);
E 14
I 14
			bcopy(mtod(n, caddr_t) + n->m_len,
			    mtod(m, caddr_t) + hlen, (unsigned) adj);
E 15
I 15
D 16
		ip_send(mh);
E 16
I 16
D 21
		ip_send(mhip);
E 21
I 21
D 26
		ip->ip_off = htons((u_short)ip->ip_off);
E 26
I 26
		mhip->ip_off = htons((u_short)mhip->ip_off);
E 26
I 25
D 42
#endif
E 42
E 25
D 26
		ip->ip_sum = 0;
		ip->ip_sum = in_cksum(m, hlen);
E 26
I 26
		mhip->ip_sum = 0;
D 75
		mhip->ip_sum = in_cksum(mh, hlen);
I 31
D 34
		ro->ro_rt->rt_use++;
E 34
E 31
E 26
D 28
		if ((*ifp->if_output)(ifp, mh, PF_INET) == 0)
E 28
I 28
D 29
		if ((*ifp->if_output)(ifp, mh,
E 29
D 30
#ifdef notdef
E 30
D 29
		  &ro->ro_rt->rt_dest) == 0)
E 29
I 29
D 33
		if ((*ifp->if_output)(ifp, mh, dst) == 0)
E 29
D 30
#else
D 29
		  (struct sockaddr *)&tempaddr) == 0)
E 29
I 29
		if ((*ifp->if_output)(ifp, mh, 
		    (struct sockaddr *)&tempaddr) == 0)
E 29
#endif
E 30
E 28
			goto bad;
E 33
I 33
D 56
		if (error = (*ifp->if_output)(ifp, mh, dst))
E 56
I 56
		if (error = (*ifp->if_output)(ifp, mh, (struct sockaddr *)dst))
E 75
I 75
		mhip->ip_sum = in_cksum(m, mhlen);
D 76
		if (error = (*ifp->if_output)(ifp, m, (struct sockaddr *)dst))
E 75
E 56
			break;
E 76
I 76
		*mnext = m;
D 81
		mnext = &m->m_act;
E 81
I 81
		mnext = &m->m_nextpkt;
I 83
		ipstat.ips_ofragments++;
E 83
E 81
E 76
E 33
E 21
E 16
	}
I 34
D 58
	m_freem(m);
	goto done;

E 58
D 49
unreachable:
	if (ipnorouteprint)
		printf("no route to %x (from %x, len %d)\n",
		    ip->ip_dst.s_addr, ip->ip_src.s_addr, ip->ip_len);
	error = ENETUNREACH;
E 49
E 34
I 21
D 33
	m_freem(m);
	return (1);
E 33
E 21
D 76
bad:
D 75
	m_freem(m);
E 75
I 75
	m_freem(m0);
E 76
I 76
	/*
	 * Update first fragment by trimming what's been copied out
	 * and updating header, then send each fragment (in order).
	 */
D 84
	m_adj(m0, hlen + firstlen - ip->ip_len);
E 84
I 84
	m = m0;
D 87
	m_adj(m, hlen + firstlen - ip->ip_len);
E 87
I 87
	m_adj(m, hlen + firstlen - (u_short)ip->ip_len);
E 87
E 84
D 77
	ip->ip_len = hlen + firstlen;
	ip->ip_off |= IP_MF;
E 77
I 77
D 81
	ip->ip_len = htons((u_short)(hlen + firstlen));
E 81
I 81
	m->m_pkthdr.len = hlen + firstlen;
	ip->ip_len = htons((u_short)m->m_pkthdr.len);
E 81
	ip->ip_off = htons((u_short)(ip->ip_off | IP_MF));
E 77
	ip->ip_sum = 0;
D 84
	ip->ip_sum = in_cksum(m0, hlen);
E 84
I 84
	ip->ip_sum = in_cksum(m, hlen);
E 84
sendorfree:
	for (m = m0; m; m = m0) {
D 81
		m0 = m->m_act;
		m->m_act = 0;
E 81
I 81
		m0 = m->m_nextpkt;
		m->m_nextpkt = 0;
E 81
		if (error == 0)
			error = (*ifp->if_output)(ifp, m,
D 85
			    (struct sockaddr *)dst);
E 85
I 85
			    (struct sockaddr *)dst, ro->ro_rt);
E 85
		else
			m_freem(m);
	}
I 95

	if (error == 0)
		ipstat.ips_fragmented++;
E 95
    }
E 76
E 75
I 34
done:
D 49
	if (ro == &iproute && ro->ro_rt)
E 49
I 49
	if (ro == &iproute && (flags & IP_ROUTETOIF) == 0 && ro->ro_rt)
E 49
		RTFREE(ro->ro_rt);
E 34
I 21
D 33
	return (0);
E 33
I 33
	return (error);
I 76
bad:
	m_freem(m0);
	goto done;
E 76
E 33
E 21
}

/*
I 60
 * Insert IP options into preformed packet.
 * Adjust IP destination as required for IP source routing,
 * as indicated by a non-zero in_addr at the start of the options.
 */
D 103
struct mbuf *
E 103
I 103
static struct mbuf *
E 103
ip_insertoptions(m, opt, phlen)
	register struct mbuf *m;
	struct mbuf *opt;
	int *phlen;
{
	register struct ipoption *p = mtod(opt, struct ipoption *);
	struct mbuf *n;
	register struct ip *ip = mtod(m, struct ip *);
D 64
	int optlen;
E 64
I 64
	unsigned optlen;
E 64

	optlen = opt->m_len - sizeof(p->ipopt_dst);
I 87
	if (optlen + (u_short)ip->ip_len > IP_MAXPACKET)
		return (m);		/* XXX should fail */
E 87
	if (p->ipopt_dst.s_addr)
		ip->ip_dst = p->ipopt_dst;
D 81
	if (m->m_off >= MMAXOFF || MMINOFF + optlen > m->m_off) {
		MGET(n, M_DONTWAIT, MT_HEADER);
E 81
I 81
	if (m->m_flags & M_EXT || m->m_data - optlen < m->m_pktdat) {
		MGETHDR(n, M_DONTWAIT, MT_HEADER);
E 81
		if (n == 0)
			return (m);
I 81
		n->m_pkthdr.len = m->m_pkthdr.len + optlen;
E 81
		m->m_len -= sizeof(struct ip);
D 81
		m->m_off += sizeof(struct ip);
E 81
I 81
		m->m_data += sizeof(struct ip);
E 81
		n->m_next = m;
		m = n;
D 81
		m->m_off = MMAXOFF - sizeof(struct ip) - optlen;
E 81
		m->m_len = optlen + sizeof(struct ip);
I 81
		m->m_data += max_linkhdr;
E 81
		bcopy((caddr_t)ip, mtod(m, caddr_t), sizeof(struct ip));
	} else {
D 81
		m->m_off -= optlen;
E 81
I 81
		m->m_data -= optlen;
E 81
		m->m_len += optlen;
I 81
		m->m_pkthdr.len += optlen;
E 81
		ovbcopy((caddr_t)ip, mtod(m, caddr_t), sizeof(struct ip));
	}
	ip = mtod(m, struct ip *);
D 64
	bcopy((caddr_t)p->ipopt_list, (caddr_t)(ip + 1), optlen);
E 64
I 64
	bcopy((caddr_t)p->ipopt_list, (caddr_t)(ip + 1), (unsigned)optlen);
E 64
	*phlen = sizeof(struct ip) + optlen;
	ip->ip_len += optlen;
	return (m);
}

/*
E 60
D 76
 * Copy options from ip to jp.
D 16
 * If off is 0 all options are copies
E 16
I 16
 * If off is 0 all options are copied
E 16
 * otherwise copy selectively.
E 76
I 76
 * Copy options from ip to jp,
 * omitting those not copied during fragmentation.
E 76
 */
I 93
int
E 93
D 76
ip_optcopy(ip, jp, off)
E 76
I 76
ip_optcopy(ip, jp)
E 76
	struct ip *ip, *jp;
D 76
	int off;
E 76
{
	register u_char *cp, *dp;
	int opt, optlen, cnt;

I 16
D 36
COUNT(IP_OPTCOPY);
E 36
E 16
	cp = (u_char *)(ip + 1);
	dp = (u_char *)(jp + 1);
	cnt = (ip->ip_hl << 2) - sizeof (struct ip);
	for (; cnt > 0; cnt -= optlen, cp += optlen) {
		opt = cp[0];
		if (opt == IPOPT_EOL)
			break;
D 95
		if (opt == IPOPT_NOP)
E 95
I 95
		if (opt == IPOPT_NOP) {
			/* Preserve for IP mcast tunnel's LSRR alignment. */
			*dp++ = IPOPT_NOP;
E 95
			optlen = 1;
D 95
		else
E 95
I 95
			continue;
		} else
E 95
D 60
			optlen = cp[1];
E 60
I 60
			optlen = cp[IPOPT_OLEN];
E 60
D 76
		if (optlen > cnt)			/* XXX */
			optlen = cnt;			/* XXX */
		if (off == 0 || IPOPT_COPIED(opt)) {
E 76
I 76
		/* bogus lengths should have been caught by ip_dooptions */
		if (optlen > cnt)
			optlen = cnt;
		if (IPOPT_COPIED(opt)) {
E 76
D 16
			bcopy(cp, dp, optlen);
E 16
I 16
			bcopy((caddr_t)cp, (caddr_t)dp, (unsigned)optlen);
E 16
			dp += optlen;
E 15
E 14
		}
D 15
		ip_send(p);
		p = (struct ip *)((int)m + m->m_off);
		len -= rnd;
		off += rnd;
E 15
E 7
D 2
	} 
E 2
I 2
	}
I 14
D 15
	return;
E 15
I 15
	for (optlen = dp - (u_char *)(jp+1); optlen & 0x3; optlen++)
		*dp++ = IPOPT_EOL;
	return (optlen);
I 60
}

/*
 * IP socket option processing.
 */
I 93
int
E 93
D 86
ip_ctloutput(op, so, level, optname, m)
E 86
I 86
ip_ctloutput(op, so, level, optname, mp)
E 86
	int op;
	struct socket *so;
	int level, optname;
D 86
	struct mbuf **m;
E 86
I 86
	struct mbuf **mp;
E 86
{
I 86
	register struct inpcb *inp = sotoinpcb(so);
	register struct mbuf *m = *mp;
	register int optval;
E 86
	int error = 0;
D 86
	struct inpcb *inp = sotoinpcb(so);
E 86

D 105
	if (level != IPPROTO_IP)
D 91
		error = EINVAL;
E 91
I 91
		goto freeit;
E 91
	else switch (op) {
E 105
I 105
	if (level != IPPROTO_IP) {
		error = EINVAL;
		if (op == PRCO_SETOPT && *mp)
			(void) m_free(*mp);
	} else switch (op) {
E 105

	case PRCO_SETOPT:
		switch (optname) {
		case IP_OPTIONS:
I 89
#ifdef notyet
E 89
D 61
			return (ip_pcbopts(inp, *m));
E 61
I 61
D 86
			return (ip_pcbopts(&inp->inp_options, *m));
E 86
I 86
		case IP_RETOPTS:
			return (ip_pcbopts(optname, &inp->inp_options, m));
I 89
#else
			return (ip_pcbopts(&inp->inp_options, m));
#endif
E 89
E 86
E 61

I 86
		case IP_TOS:
		case IP_TTL:
		case IP_RECVOPTS:
		case IP_RECVRETOPTS:
		case IP_RECVDSTADDR:
			if (m->m_len != sizeof(int))
				error = EINVAL;
			else {
				optval = *mtod(m, int *);
D 89
				switch (op) {
E 89
I 89
				switch (optname) {
E 89

				case IP_TOS:
					inp->inp_ip.ip_tos = optval;
					break;

				case IP_TTL:
D 90
					inp->inp_ip.ip_tos = optval;
E 90
I 90
					inp->inp_ip.ip_ttl = optval;
E 90
					break;
#define	OPTSET(bit) \
	if (optval) \
		inp->inp_flags |= bit; \
	else \
		inp->inp_flags &= ~bit;

				case IP_RECVOPTS:
					OPTSET(INP_RECVOPTS);
					break;

				case IP_RECVRETOPTS:
					OPTSET(INP_RECVRETOPTS);
					break;

				case IP_RECVDSTADDR:
					OPTSET(INP_RECVDSTADDR);
					break;
				}
			}
			break;
#undef OPTSET

I 93
D 95
#ifdef MULTICAST
E 95
		case IP_MULTICAST_IF:
		case IP_MULTICAST_TTL:
		case IP_MULTICAST_LOOP:
		case IP_ADD_MEMBERSHIP:
		case IP_DROP_MEMBERSHIP:
			error = ip_setmoptions(optname, &inp->inp_moptions, m);
			break;
D 95
#endif
E 95

E 93
I 91
D 105
		freeit:
E 105
E 91
E 86
		default:
D 105
			error = EINVAL;
E 105
I 105
			error = ENOPROTOOPT;
E 105
			break;
		}
I 86
		if (m)
			(void)m_free(m);
E 86
		break;

	case PRCO_GETOPT:
		switch (optname) {
		case IP_OPTIONS:
I 89
		case IP_RETOPTS:
E 89
D 86
			*m = m_get(M_WAIT, MT_SOOPTS);
E 86
I 86
			*mp = m = m_get(M_WAIT, MT_SOOPTS);
E 86
			if (inp->inp_options) {
D 81
				(*m)->m_off = inp->inp_options->m_off;
E 81
D 86
				(*m)->m_len = inp->inp_options->m_len;
E 86
I 86
				m->m_len = inp->inp_options->m_len;
E 86
				bcopy(mtod(inp->inp_options, caddr_t),
D 64
				    mtod(*m, caddr_t), (*m)->m_len);
E 64
I 64
D 86
				    mtod(*m, caddr_t), (unsigned)(*m)->m_len);
E 86
I 86
				    mtod(m, caddr_t), (unsigned)m->m_len);
E 86
E 64
			} else
D 86
				(*m)->m_len = 0;
E 86
I 86
				m->m_len = 0;
E 86
			break;
I 86

		case IP_TOS:
		case IP_TTL:
		case IP_RECVOPTS:
		case IP_RECVRETOPTS:
		case IP_RECVDSTADDR:
			*mp = m = m_get(M_WAIT, MT_SOOPTS);
			m->m_len = sizeof(int);
D 89
			switch (op) {
E 89
I 89
			switch (optname) {
E 89

			case IP_TOS:
				optval = inp->inp_ip.ip_tos;
				break;

			case IP_TTL:
D 90
				optval = inp->inp_ip.ip_tos;
E 90
I 90
				optval = inp->inp_ip.ip_ttl;
E 90
				break;

#define	OPTBIT(bit)	(inp->inp_flags & bit ? 1 : 0)

			case IP_RECVOPTS:
				optval = OPTBIT(INP_RECVOPTS);
				break;

			case IP_RECVRETOPTS:
				optval = OPTBIT(INP_RECVRETOPTS);
				break;

			case IP_RECVDSTADDR:
				optval = OPTBIT(INP_RECVDSTADDR);
				break;
			}
			*mtod(m, int *) = optval;
			break;

I 93
D 95
#ifdef MULTICAST
E 95
		case IP_MULTICAST_IF:
		case IP_MULTICAST_TTL:
		case IP_MULTICAST_LOOP:
		case IP_ADD_MEMBERSHIP:
		case IP_DROP_MEMBERSHIP:
			error = ip_getmoptions(optname, inp->inp_moptions, mp);
			break;
D 95
#endif
E 95

E 93
E 86
		default:
D 105
			error = EINVAL;
E 105
I 105
			error = ENOPROTOOPT;
E 105
			break;
		}
		break;
	}
D 73
	if (op == PRCO_SETOPT)
E 73
I 73
D 86
	if (op == PRCO_SETOPT && *m)
E 73
D 64
		m_free(*m);
E 64
I 64
		(void)m_free(*m);
E 86
E 64
	return (error);
}

/*
D 61
 * Set up IP options in inpcb for insertion in output packets.
 * Store in mbuf, adding pseudo-option with destination address
 * if source routed.
E 61
I 61
 * Set up IP options in pcb for insertion in output packets.
 * Store in mbuf with pointer in pcbopt, adding pseudo-option
 * with destination address if source routed.
E 61
 */
I 93
int
E 93
I 89
#ifdef notyet
ip_pcbopts(optname, pcbopt, m)
	int optname;
#else
E 89
D 61
ip_pcbopts(inp, m)
	struct inpcb *inp;
	struct mbuf *m;
E 61
I 61
ip_pcbopts(pcbopt, m)
I 89
#endif
E 89
	struct mbuf **pcbopt;
	register struct mbuf *m;
E 61
{
	register cnt, optlen;
	register u_char *cp;
	u_char opt;

	/* turn off any old options */
D 61
	if (inp->inp_options)
		m_free(inp->inp_options);
	inp->inp_options = 0;

E 61
I 61
	if (*pcbopt)
D 64
		m_free(*pcbopt);
E 64
I 64
		(void)m_free(*pcbopt);
E 64
	*pcbopt = 0;
E 61
	if (m == (struct mbuf *)0 || m->m_len == 0) {
		/*
		 * Only turning off any previous options.
		 */
		if (m)
D 64
			m_free(m);
E 64
I 64
			(void)m_free(m);
E 64
		return (0);
	}

#ifndef	vax
	if (m->m_len % sizeof(long))
		goto bad;
#endif
	/*
	 * IP first-hop destination address will be stored before
	 * actual options; move other options back
	 * and clear it when none present.
	 */
D 81
#if	MAX_IPOPTLEN >= MMAXOFF - MMINOFF
	if (m->m_off + m->m_len + sizeof(struct in_addr) > MAX_IPOPTLEN)
E 81
I 81
	if (m->m_data + m->m_len + sizeof(struct in_addr) >= &m->m_dat[MLEN])
E 81
		goto bad;
D 81
#else
	if (m->m_off + m->m_len + sizeof(struct in_addr) > MMAXOFF)
		goto bad;
#endif
E 81
	cnt = m->m_len;
	m->m_len += sizeof(struct in_addr);
	cp = mtod(m, u_char *) + sizeof(struct in_addr);
D 64
	ovbcopy(mtod(m, caddr_t), cp, cnt);
E 64
I 64
	ovbcopy(mtod(m, caddr_t), (caddr_t)cp, (unsigned)cnt);
E 64
	bzero(mtod(m, caddr_t), sizeof(struct in_addr));

	for (; cnt > 0; cnt -= optlen, cp += optlen) {
		opt = cp[IPOPT_OPTVAL];
		if (opt == IPOPT_EOL)
			break;
		if (opt == IPOPT_NOP)
			optlen = 1;
		else {
			optlen = cp[IPOPT_OLEN];
			if (optlen <= IPOPT_OLEN || optlen > cnt)
				goto bad;
		}
		switch (opt) {

		default:
			break;

		case IPOPT_LSRR:
		case IPOPT_SSRR:
			/*
			 * user process specifies route as:
			 *	->A->B->C->D
			 * D must be our final destination (but we can't
			 * check that since we may not have connected yet).
			 * A is first hop destination, which doesn't appear in
			 * actual IP option, but is stored before the options.
			 */
			if (optlen < IPOPT_MINOFF - 1 + sizeof(struct in_addr))
				goto bad;
			m->m_len -= sizeof(struct in_addr);
			cnt -= sizeof(struct in_addr);
			optlen -= sizeof(struct in_addr);
			cp[IPOPT_OLEN] = optlen;
			/*
			 * Move first hop before start of options.
			 */
D 64
			bcopy(&cp[IPOPT_OFFSET+1], mtod(m, caddr_t),
E 64
I 64
			bcopy((caddr_t)&cp[IPOPT_OFFSET+1], mtod(m, caddr_t),
E 64
			    sizeof(struct in_addr));
			/*
			 * Then copy rest of options back
			 * to close up the deleted entry.
			 */
D 64
			ovbcopy(&cp[IPOPT_OFFSET+1] + sizeof(struct in_addr),
			    &cp[IPOPT_OFFSET+1], cnt + sizeof(struct in_addr));
E 64
I 64
			ovbcopy((caddr_t)(&cp[IPOPT_OFFSET+1] +
			    sizeof(struct in_addr)),
			    (caddr_t)&cp[IPOPT_OFFSET+1],
			    (unsigned)cnt + sizeof(struct in_addr));
E 64
			break;
		}
	}
I 81
	if (m->m_len > MAX_IPOPTLEN + sizeof(struct in_addr))
		goto bad;
E 81
D 61
	inp->inp_options = m;
E 61
I 61
	*pcbopt = m;
E 61
	return (0);

bad:
D 64
	m_free(m);
E 64
I 64
	(void)m_free(m);
E 64
	return (EINVAL);
E 60
E 15
E 14
E 2
D 7

	return(ip_send(p));     /* pass datagram to local net level */
E 7
}
I 93

D 95
#ifdef MULTICAST
E 95
/*
 * Set the IP multicast options in response to user setsockopt().
 */
int
ip_setmoptions(optname, imop, m)
	int optname;
	struct ip_moptions **imop;
	struct mbuf *m;
{
	register int error = 0;
	u_char loop;
	register int i;
	struct in_addr addr;
	register struct ip_mreq *mreq;
	register struct ifnet *ifp;
	register struct ip_moptions *imo = *imop;
	struct route ro;
	register struct sockaddr_in *dst;

	if (imo == NULL) {
		/*
		 * No multicast option buffer attached to the pcb;
		 * allocate one and initialize to default values.
		 */
		imo = (struct ip_moptions*)malloc(sizeof(*imo), M_IPMOPTS,
		    M_WAITOK);

		if (imo == NULL)
			return (ENOBUFS);
		*imop = imo;
		imo->imo_multicast_ifp = NULL;
		imo->imo_multicast_ttl = IP_DEFAULT_MULTICAST_TTL;
		imo->imo_multicast_loop = IP_DEFAULT_MULTICAST_LOOP;
		imo->imo_num_memberships = 0;
	}

	switch (optname) {

	case IP_MULTICAST_IF:
		/*
		 * Select the interface for outgoing multicast packets.
		 */
		if (m == NULL || m->m_len != sizeof(struct in_addr)) {
			error = EINVAL;
			break;
		}
		addr = *(mtod(m, struct in_addr *));
		/*
		 * INADDR_ANY is used to remove a previous selection.
		 * When no interface is selected, a default one is
		 * chosen every time a multicast packet is sent.
		 */
		if (addr.s_addr == INADDR_ANY) {
			imo->imo_multicast_ifp = NULL;
			break;
		}
		/*
		 * The selected interface is identified by its local
		 * IP address.  Find the interface and confirm that
		 * it supports multicasting.
		 */
		INADDR_TO_IFP(addr, ifp);
		if (ifp == NULL || (ifp->if_flags & IFF_MULTICAST) == 0) {
			error = EADDRNOTAVAIL;
			break;
		}
		imo->imo_multicast_ifp = ifp;
		break;

	case IP_MULTICAST_TTL:
		/*
		 * Set the IP time-to-live for outgoing multicast packets.
		 */
		if (m == NULL || m->m_len != 1) {
			error = EINVAL;
			break;
		}
		imo->imo_multicast_ttl = *(mtod(m, u_char *));
		break;

	case IP_MULTICAST_LOOP:
		/*
		 * Set the loopback flag for outgoing multicast packets.
		 * Must be zero or one.
		 */
		if (m == NULL || m->m_len != 1 ||
		   (loop = *(mtod(m, u_char *))) > 1) {
			error = EINVAL;
			break;
		}
		imo->imo_multicast_loop = loop;
		break;

	case IP_ADD_MEMBERSHIP:
		/*
		 * Add a multicast group membership.
		 * Group must be a valid IP multicast address.
		 */
		if (m == NULL || m->m_len != sizeof(struct ip_mreq)) {
			error = EINVAL;
			break;
		}
		mreq = mtod(m, struct ip_mreq *);
		if (!IN_MULTICAST(ntohl(mreq->imr_multiaddr.s_addr))) {
			error = EINVAL;
			break;
		}
		/*
		 * If no interface address was provided, use the interface of
		 * the route to the given multicast address.
		 */
		if (mreq->imr_interface.s_addr == INADDR_ANY) {
			ro.ro_rt = NULL;
			dst = (struct sockaddr_in *)&ro.ro_dst;
			dst->sin_len = sizeof(*dst);
			dst->sin_family = AF_INET;
			dst->sin_addr = mreq->imr_multiaddr;
			rtalloc(&ro);
			if (ro.ro_rt == NULL) {
				error = EADDRNOTAVAIL;
				break;
			}
			ifp = ro.ro_rt->rt_ifp;
			rtfree(ro.ro_rt);
		}
		else {
			INADDR_TO_IFP(mreq->imr_interface, ifp);
		}
		/*
		 * See if we found an interface, and confirm that it
		 * supports multicast.
		 */
		if (ifp == NULL || (ifp->if_flags & IFF_MULTICAST) == 0) {
			error = EADDRNOTAVAIL;
			break;
		}
		/*
		 * See if the membership already exists or if all the
		 * membership slots are full.
		 */
		for (i = 0; i < imo->imo_num_memberships; ++i) {
			if (imo->imo_membership[i]->inm_ifp == ifp &&
			    imo->imo_membership[i]->inm_addr.s_addr
						== mreq->imr_multiaddr.s_addr)
				break;
		}
		if (i < imo->imo_num_memberships) {
			error = EADDRINUSE;
			break;
		}
		if (i == IP_MAX_MEMBERSHIPS) {
			error = ETOOMANYREFS;
			break;
		}
		/*
		 * Everything looks good; add a new record to the multicast
		 * address list for the given interface.
		 */
		if ((imo->imo_membership[i] =
		    in_addmulti(&mreq->imr_multiaddr, ifp)) == NULL) {
			error = ENOBUFS;
			break;
		}
		++imo->imo_num_memberships;
		break;

	case IP_DROP_MEMBERSHIP:
		/*
		 * Drop a multicast group membership.
		 * Group must be a valid IP multicast address.
		 */
		if (m == NULL || m->m_len != sizeof(struct ip_mreq)) {
			error = EINVAL;
			break;
		}
		mreq = mtod(m, struct ip_mreq *);
		if (!IN_MULTICAST(ntohl(mreq->imr_multiaddr.s_addr))) {
			error = EINVAL;
			break;
		}
		/*
		 * If an interface address was specified, get a pointer
		 * to its ifnet structure.
		 */
		if (mreq->imr_interface.s_addr == INADDR_ANY)
			ifp = NULL;
		else {
			INADDR_TO_IFP(mreq->imr_interface, ifp);
			if (ifp == NULL) {
				error = EADDRNOTAVAIL;
				break;
			}
		}
		/*
		 * Find the membership in the membership array.
		 */
		for (i = 0; i < imo->imo_num_memberships; ++i) {
			if ((ifp == NULL ||
			     imo->imo_membership[i]->inm_ifp == ifp) &&
			     imo->imo_membership[i]->inm_addr.s_addr ==
			     mreq->imr_multiaddr.s_addr)
				break;
		}
		if (i == imo->imo_num_memberships) {
			error = EADDRNOTAVAIL;
			break;
		}
		/*
		 * Give up the multicast address record to which the
		 * membership points.
		 */
		in_delmulti(imo->imo_membership[i]);
		/*
		 * Remove the gap in the membership array.
		 */
		for (++i; i < imo->imo_num_memberships; ++i)
			imo->imo_membership[i-1] = imo->imo_membership[i];
		--imo->imo_num_memberships;
		break;

	default:
		error = EOPNOTSUPP;
		break;
	}

	/*
	 * If all options have default values, no need to keep the mbuf.
	 */
	if (imo->imo_multicast_ifp == NULL &&
	    imo->imo_multicast_ttl == IP_DEFAULT_MULTICAST_TTL &&
	    imo->imo_multicast_loop == IP_DEFAULT_MULTICAST_LOOP &&
	    imo->imo_num_memberships == 0) {
		free(*imop, M_IPMOPTS);
		*imop = NULL;
	}

	return (error);
}

/*
 * Return the IP multicast options in response to user getsockopt().
 */
int
ip_getmoptions(optname, imo, mp)
	int optname;
	register struct ip_moptions *imo;
	register struct mbuf **mp;
{
	u_char *ttl;
	u_char *loop;
	struct in_addr *addr;
	struct in_ifaddr *ia;

	*mp = m_get(M_WAIT, MT_SOOPTS);

	switch (optname) {

	case IP_MULTICAST_IF:
		addr = mtod(*mp, struct in_addr *);
		(*mp)->m_len = sizeof(struct in_addr);
		if (imo == NULL || imo->imo_multicast_ifp == NULL)
			addr->s_addr = INADDR_ANY;
		else {
			IFP_TO_IA(imo->imo_multicast_ifp, ia);
			addr->s_addr = (ia == NULL) ? INADDR_ANY
					: IA_SIN(ia)->sin_addr.s_addr;
		}
		return (0);

	case IP_MULTICAST_TTL:
		ttl = mtod(*mp, u_char *);
		(*mp)->m_len = 1;
		*ttl = (imo == NULL) ? IP_DEFAULT_MULTICAST_TTL
				     : imo->imo_multicast_ttl;
		return (0);

	case IP_MULTICAST_LOOP:
		loop = mtod(*mp, u_char *);
		(*mp)->m_len = 1;
		*loop = (imo == NULL) ? IP_DEFAULT_MULTICAST_LOOP
				      : imo->imo_multicast_loop;
		return (0);

	default:
		return (EOPNOTSUPP);
	}
}

/*
 * Discard the IP multicast options.
 */
void
ip_freemoptions(imo)
	register struct ip_moptions *imo;
{
	register int i;

	if (imo != NULL) {
		for (i = 0; i < imo->imo_num_memberships; ++i)
			in_delmulti(imo->imo_membership[i]);
		free(imo, M_IPMOPTS);
	}
}

/*
 * Routine called from ip_output() to loop back a copy of an IP multicast
 * packet to the input queue of a specified interface.  Note that this
 * calls the output routine of the loopback "driver", but with an interface
 * pointer that might NOT be &loif -- easier than replicating that code here.
 */
static void
ip_mloopback(ifp, m, dst)
	struct ifnet *ifp;
	register struct mbuf *m;
	register struct sockaddr_in *dst;
{
	register struct ip *ip;
	struct mbuf *copym;

	copym = m_copy(m, 0, M_COPYALL);
	if (copym != NULL) {
		/*
		 * We don't bother to fragment if the IP length is greater
		 * than the interface's MTU.  Can this possibly matter?
		 */
		ip = mtod(copym, struct ip *);
		ip->ip_len = htons((u_short)ip->ip_len);
		ip->ip_off = htons((u_short)ip->ip_off);
		ip->ip_sum = 0;
		ip->ip_sum = in_cksum(copym, ip->ip_hl << 2);
D 103
		(void) looutput(ifp, copym, (struct sockaddr *)dst);
E 103
I 103
		(void) looutput(ifp, copym, (struct sockaddr *)dst, NULL);
E 103
	}
}
D 95
#endif
E 95
E 93
D 21

I 16
/* REST OF CODE HERE IS GARBAGE */

E 16
D 7
ip_send(p)      /* format header and send message to 1822 level */
struct ip *p;
E 7
I 7
D 9
ip_send(p)
	struct ip *p;
E 9
I 9
ip_send(ip)
D 15
	register struct ip *ip;		/* known to be r11 */
E 15
I 15
	register struct ip *ip;
E 15
E 9
E 7
{
	register struct mbuf *m;
	register struct imp *l;
I 9
D 15
	register int hlen = ip->ip_hl << 2;
E 15
I 15
	int hlen = ip->ip_hl << 2;
E 15
E 9
I 2
	int s;
E 2
COUNT(IP_SEND);

D 7
	m = dtom(p);                    /* ->header mbuf */

	/* set up 1822 leader fields for transmit */

E 7
I 7
D 9
	m = dtom(p);
E 9
I 9
	m = dtom(ip);
E 9
E 7
D 14
	l = (struct imp *)((int)m + m->m_off - L1822);
E 14
I 14
	l = (struct imp *)(mtod(m, caddr_t) - L1822);
E 14
D 7
/*
	l->i_hst = p->ip_dst.s_host;
	l->i_impno = p->ip_dst.s_imp;
	l->i_mlen = p->ip_len + L1822;
	l->i_link = IPLINK;
	l->i_type = 0;
	l->i_htype = 0;
	l->i_stype = 0;
*/
E 7
D 2
	l->i_shost = arpa_ether(p->ip_src.s_host);
	l->i_dhost = arpa_ether(p->ip_dst.s_host);
E 2
I 2
D 9
	if ((l->i_shost = p->ip_src.s_host) == 0)
		l->i_shost = 253;
	if ((l->i_dhost = p->ip_dst.s_host) == 0)
		l->i_dhost = 253;
E 9
I 9
	l->i_shost = ip->ip_src.s_host;
	l->i_dhost = ip->ip_dst.s_host;
E 9
E 2
	l->i_type = IPTYPE;
D 7

	/* finish ip leader by calculating checksum and doing
	   necessary byte-swapping  */

E 7
D 9
	p->ip_sum = 0;
D 6
 	ip_bswap(p);
E 6
I 6
	p->ip_len = htons(p->ip_len);
	p->ip_id = htons(p->ip_id);
	p->ip_off = htons(p->ip_off);
E 6
D 2
	p->ip_sum = cksum(m, sizeof(struct ip));     
E 2
I 2
	p->ip_sum = cksum(m, sizeof(struct ip));
E 2
D 7

E 7
	m->m_off -= L1822;              /* -> 1822 leader */
E 9
I 9
	ip->ip_sum = 0;
D 14
	ip->ip_len = htons(ip->ip_len);
E 14
I 14
	ip->ip_len = htons((u_short)ip->ip_len);
E 14
	ip->ip_id = htons(ip->ip_id);
D 14
	ip->ip_off = htons(ip->ip_off);
E 14
I 14
	ip->ip_off = htons((u_short)ip->ip_off);
E 14
D 15
	CKSUM_IPSET(m, ip, r11, hlen);
E 15
I 15
	ip->ip_sum = inet_cksum(m, hlen);
E 15
	m->m_off -= L1822;
E 9
	m->m_len += L1822;
D 7

E 7
D 2
	return(imp_snd(m));             /* pass frag to 1822 */
E 2
I 2
	m->m_act = NULL;
D 7

E 7
#ifndef IMPLOOP
D 7

	/* put output message on queue */

E 7
D 6
	s = spl_imp();
E 6
I 6
	s = splimp();
E 6
	if (imp_stat.outq_head != NULL)
		imp_stat.outq_tail->m_act = m;
	else
		imp_stat.outq_head = m;
	imp_stat.outq_tail = m;
	splx(s);
D 7

	/* if no outstanding output, start some */

E 7
	if (!imp_stat.outactive)
D 8
		imp_output(0);
E 8
I 8
		enstart(0);
E 8
D 7

E 7
#else
D 7
	/* software looping: put msg chain on input queue */

E 7
	if (imp_stat.inq_head != NULL)
		imp_stat.inq_tail->m_act = m;
	else
		imp_stat.inq_head = m;
	imp_stat.inq_tail = m;
I 11
	setsoftnet();
E 11
D 7

E 7
#endif IMPLOOP
D 14
	return (1);
E 14
E 2
D 7
}

ip_setup(up, m, len)            /* setup an ip header for raw write */
register struct ucb *up;
register struct mbuf *m;
int len;
{
	register struct ip *ip;
COUNT(IP_SETUP);

D 4
	m->m_off = MSIZE - sizeof(struct ip);
E 4
I 4
	m->m_off = MMAXOFF - sizeof(struct ip);
E 4
	m->m_len = sizeof(struct ip);

	ip = (struct ip *)((int)m + m->m_off);

	ip->ip_tos = 0;
	ip->ip_id = 0;
	ip->ip_off = 0;
	ip->ip_p = up->uc_lolink;
	ip->ip_len = len + sizeof(struct ip);

D 6
	ip->ip_src.s_addr = netcb.n_lhost.s_addr;
E 6
I 6
	ip->ip_src.s_addr = n_lhost.s_addr;
E 6
        ip->ip_dst.s_addr = up->uc_host->h_addr.s_addr;
E 7
D 2
}


/*
 * Convert logical host on imp to ethernet address.
 * (Primitive; use gateway table in next version.)
 *	0/78	arpavax		253
 *	1/78	ucb-c70		-
 *	-	csvax		252
 *	-	ucb-comet	223
 */
arpa_ether(n)
	int n;
{
COUNT(ARPA_ETHER);
	switch (n) {
	case 0:			/* arpavax */
		return 253;
	default:
		return n;
	}
E 2
}
I 16

/* END GARBAGE */
E 21
E 16
E 1
