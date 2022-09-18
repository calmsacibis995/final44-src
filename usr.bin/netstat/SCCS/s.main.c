h59290
s 00005/00005/00477
d D 8.4 94/03/01 05:45:37 bostic 54 53
c repeat the command name in the different usage statements
e
s 00006/00006/00476
d D 8.3 94/01/04 11:41:53 bostic 53 52
c use -g for multicast instead of -B (follow BSDI)
e
s 00001/00000/00481
d D 8.2 94/01/02 14:17:49 bostic 52 51
c -w should set iflag, so the output looks like the old 'netstat 1'
c From: "Chris G. Demetriou" <cgd@vangogh.CS.Berkeley.EDU>
e
s 00004/00004/00477
d D 8.1 93/06/12 17:05:15 bostic 51 50
c add 1993 to the copyright notice, yank to 8.1 for 4.4BSD snapshot
e
s 00001/00010/00480
d D 5.33 93/06/12 16:45:20 mckusick 50 48
c delete -h option for printing out IMP host table
e
s 00005/00005/00485
d R 8.1 93/06/06 15:43:52 bostic 49 48
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00488
d D 5.32 93/02/16 22:58:20 andrew 48 47
c support IGMP stats
e
s 00002/00002/00486
d D 5.31 92/07/12 13:52:26 bostic 47 46
c w option takes an argument
e
s 00011/00011/00477
d D 5.30 92/07/07 16:57:19 sklower 46 45
c not every value return in an nlist structure was being
c coerced to an (off_t) which was only being smashed back down to a (u_long)
c as an argument to kvm_read.  If you ask me nl.n_value ought to be a (void *)
c but since the type of nl.n_value and the second argument to kvm_read are
c the same I got fed up and changed all the off_t's to be that type (u_long).
e
s 00045/00007/00443
d D 5.29 92/07/06 15:36:11 sklower 45 44
c Multicast changes from lbl
e
s 00112/00109/00338
d D 5.28 92/05/27 18:11:46 sklower 44 43
c incorporate changes for new kvm interfaces from lbl
e
s 00015/00008/00432
d D 5.27 92/01/27 15:18:42 bostic 43 42
c don't let users create their own symbol table for the running kernel
e
s 00002/00004/00438
d D 5.26 92/01/27 14:27:18 sklower 42 41
c change manner of lookups for iso tp connections
e
s 00001/00001/00441
d D 5.25 91/08/20 20:31:56 sklower 41 40
c uses vector of routing trees rather than linked list
e
s 00021/00030/00421
d D 5.24 91/07/30 12:36:41 karels 40 39
c (By Sklower) general cleanups
e
s 00006/00014/00445
d D 5.23 91/07/01 12:10:24 karels 39 38
c rm unused/broken x25 hooks
e
s 00000/00002/00459
d D 5.22 91/07/01 11:55:09 karels 38 37
c don't need pte.h and vmmac.h
e
s 00098/00087/00363
d D 5.21 91/04/23 18:50:25 bostic 37 36
c cleanup and standardization -- add -M, -N, -w
e
s 00001/00001/00449
d D 5.20 91/03/01 15:17:29 bostic 36 35
c ANSI
e
s 00006/00035/00444
d D 5.19 90/06/18 17:20:41 sklower 35 34
c use kvm_nlist to avoid numerous lseeks of nlist; use kvm_read to avoid duplication.
e
s 00001/00011/00478
d D 5.18 90/06/01 17:07:51 bostic 34 33
c new copyright notice
e
s 00010/00003/00479
d D 5.17 90/04/07 16:18:27 sklower 33 32
c add cltp stats and take out x25 stats for time being
e
s 00055/00007/00427
d D 5.16 89/09/25 15:38:46 sklower 32 31
c add support for ISO
e
s 00007/00003/00427
d D 5.15 89/09/21 15:01:40 sklower 31 30
c checkpoint after route trees before AF_ISO
e
s 00012/00007/00418
d D 5.14 88/06/29 20:42:05 bostic 30 29
c install approved copyright notice
e
s 00005/00001/00420
d D 5.13 88/05/14 10:16:52 karels 29 28
c print drops on request
e
s 00074/00094/00347
d D 5.12 88/03/01 18:31:06 bostic 28 27
c add getopt, general cleanup, make it work with dead kernels
e
s 00009/00003/00432
d D 5.11 88/02/07 20:38:19 karels 27 26
c new copyrights
e
s 00010/00006/00425
d D 5.10 88/02/07 20:25:01 karels 26 25
c new IMP stuff
e
s 00001/00003/00430
d D 5.9 87/07/27 17:14:27 bostic 25 24
c checked in for karels; use defined constant for KERNBASE
e
s 00093/00016/00340
d D 5.8 86/08/11 12:17:24 kupfer 24 22
c Implement -p. Some lint.
e
s 00094/00017/00339
d R 5.8 86/08/11 11:49:36 kupfer 23 22
c Implement -p. Some lint.
e
s 00017/00013/00339
d D 5.7 86/05/22 14:44:08 karels 22 21
c oops, don't want unix sockets under stats
e
s 00014/00010/00338
d D 5.6 86/05/08 14:52:43 karels 21 20
c integrate unix domain, get the addresses right
e
s 00001/00000/00347
d D 5.5 86/03/04 23:28:26 lepreau 20 19
c missing exit(0);
e
s 00000/00000/00347
d D 5.4 86/01/18 12:47:50 karels 19 18
x 18
c rm bbnnet
e
s 00044/00013/00334
d D 5.3 85/09/18 16:58:38 karels 18 17
c for walsh
e
s 00048/00002/00299
d D 5.2 85/08/16 19:59:29 sklower 17 15
c Allow user to single out which address family he is interested in;
c and add support for XNS statistics and control blocks.
e
s 00048/00002/00299
d R 5.2 85/08/16 19:40:18 sklower 16 15
c Add XNS statistics and control blocks; fix bug printing port numbers
e
s 00014/00002/00287
d D 5.1 85/06/04 15:45:12 dist 15 14
c Add copyright
e
s 00017/00001/00272
d D 4.13 84/11/20 17:19:16 edward 14 12
c -I to specify which interface we care about
e
s 00011/00000/00273
d R 4.13 84/11/20 16:45:22 edward 13 12
c -I flag to specify interface
e
s 00004/00001/00269
d D 4.12 84/10/31 11:38:54 karels 12 11
c get rthashsize from kernel
e
s 00019/00002/00251
d D 4.11 84/06/03 11:13:41 sam 11 10
c addr unix domain sockets with -u flag
e
s 00001/00001/00252
d D 4.10 84/03/12 20:14:45 leres 10 9
c When cracking flags, use the carefully constructed char pointer instead
c of only switching on the second character in the argument.
e
s 00014/00001/00239
d D 4.9 83/05/30 21:10:20 sam 9 8
c routing statistics
e
s 00002/00002/00238
d D 4.8 83/05/01 18:58:00 sam 8 7
c same thing, only more portable
e
s 00002/00001/00238
d D 4.7 83/03/23 20:54:35 sam 7 6
c btoc rounds instead of truncating
e
s 00006/00002/00233
d D 4.6 83/03/11 11:30:25 sam 6 5
c add icmp statistics printing
e
s 00003/00001/00232
d D 4.5 83/02/09 17:03:21 sam 5 4
c from sun
e
s 00001/00001/00232
d D 4.4 82/12/24 20:25:33 sam 4 3
c pte.h moved
e
s 00025/00009/00208
d D 4.3 82/12/05 23:51:28 sam 3 2
c put back -s option
e
s 00007/00006/00210
d D 4.2 82/10/06 10:30:26 sam 2 1
c add netdb and interval display on interface stats
e
s 00216/00000/00000
d D 4.1 82/08/25 22:21:44 sam 1 0
c date and time created 82/08/25 22:21:44 by sam
e
u
U
t
T
I 15
/*
D 27
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 27
I 27
D 30
 * Copyright (c) 1983,1988 Regents of the University of California.
E 30
I 30
D 51
 * Copyright (c) 1983, 1988 Regents of the University of California.
E 30
 * All rights reserved.
E 51
I 51
 * Copyright (c) 1983, 1988, 1993
 *	Regents of the University of California.  All rights reserved.
E 51
 *
D 34
 * Redistribution and use in source and binary forms are permitted
D 30
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 30
I 30
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
E 34
I 34
 * %sccs.include.redist.c%
E 34
E 30
E 27
 */

E 15
I 1
#ifndef lint
D 11
static char sccsid[] = "%W% %E%";
E 11
I 11
D 15
static char sccsid[] = "%W% (Berkeley) %E%";
E 11
#endif
E 15
I 15
char copyright[] =
D 30
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 30
I 30
D 45
"%Z% Copyright (c) 1983, 1988 Regents of the University of California.\n\
E 45
I 45
D 51
"@(#) Copyright (c) 1983, 1988 Regents of the University of California.\n\
E 45
E 30
 All rights reserved.\n";
E 51
I 51
"@(#) Copyright (c) 1983, 1988, 1993\n\
	Regents of the University of California.  All rights reserved.\n";
E 51
D 28
#endif not lint
E 28
I 28
#endif /* not lint */
E 28

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 28
#endif not lint
E 28
I 28
#endif /* not lint */
E 28
E 15

#include <sys/param.h>
I 45
#include <sys/file.h>
E 45
I 44
#include <sys/protosw.h>
E 44
I 8
D 38
#include <sys/vmmac.h>
E 38
I 17
#include <sys/socket.h>
I 28
D 45
#include <sys/file.h>
E 45
I 45

#include <netinet/in.h>

#include <ctype.h>
E 45
E 28
E 17
E 8
D 4
#include <sys/pte.h>
E 4
I 4
D 38
#include <machine/pte.h>
E 38
E 4
D 37
#include <ctype.h>
E 37
#include <errno.h>
D 45
#include <netdb.h>
#include <nlist.h>
E 45
I 37
#include <kvm.h>
I 44
#include <limits.h>
I 45
#include <netdb.h>
#include <nlist.h>
#include <paths.h>
E 45
E 44
E 37
#include <stdio.h>
I 37
D 45
#include <ctype.h>
E 45
#include <stdlib.h>
#include <string.h>
E 37
I 31
D 45
#include <paths.h>
E 45
I 45
#include <unistd.h>
E 45
I 44
#include "netstat.h"
E 44
E 31

I 35
D 37
#define nl netstatnl
E 37
E 35
struct nlist nl[] = {
#define	N_MBSTAT	0
	{ "_mbstat" },
#define	N_IPSTAT	1
	{ "_ipstat" },
#define	N_TCB		2
	{ "_tcb" },
#define	N_TCPSTAT	3
	{ "_tcpstat" },
#define	N_UDB		4
	{ "_udb" },
#define	N_UDPSTAT	5
	{ "_udpstat" },
D 37
#define	N_RAWCB		6
	{ "_rawcb" },
#define	N_SYSMAP	7
	{ "_Sysmap" },
#define	N_SYSSIZE	8
	{ "_Syssize" },
#define	N_IFNET		9
E 37
I 37
#define	N_IFNET		6
E 37
	{ "_ifnet" },
D 26
#define	N_HOSTS		10
	{ "_hosts" },
E 26
I 26
D 37
#define	N_IMP		10
E 37
I 37
#define	N_IMP		7
E 37
	{ "_imp_softc" },
E 26
D 37
#define	N_RTHOST	11
E 37
I 37
D 40
#define	N_RTHOST	8
E 37
	{ "_rthost" },
D 37
#define	N_RTNET		12
E 37
I 37
#define	N_RTNET		9
E 37
	{ "_rtnet" },
D 6
	0,
E 6
I 6
D 37
#define	N_ICMPSTAT	13
E 37
I 37
#define	N_ICMPSTAT	10
E 40
I 40
#define	N_ICMPSTAT	8
E 40
E 37
	{ "_icmpstat" },
I 9
D 37
#define	N_RTSTAT	14
E 37
I 37
D 40
#define	N_RTSTAT	11
E 40
I 40
#define	N_RTSTAT	9
E 40
E 37
	{ "_rtstat" },
I 11
D 37
#define	N_NFILE		15
E 37
I 37
D 40
#define	N_NFILE		12
E 37
	{ "_nfile" },
D 37
#define	N_FILE		16
E 37
I 37
#define	N_FILE		13
E 37
	{ "_file" },
D 37
#define	N_UNIXSW	17
E 37
I 37
#define	N_UNIXSW	14
E 40
I 40
#define	N_UNIXSW	10
E 40
E 37
	{ "_unixsw" },
I 12
D 37
#define N_RTHASHSIZE	18
E 37
I 37
D 40
#define N_RTHASHSIZE	15
E 37
	{ "_rthashsize" },
I 17
D 37
#define N_IDP		19
E 37
I 37
#define N_IDP		16
E 40
I 40
#define N_IDP		11
E 40
E 37
	{ "_nspcb"},
D 37
#define N_IDPSTAT	20
E 37
I 37
D 40
#define N_IDPSTAT	17
E 40
I 40
#define N_IDPSTAT	12
E 40
E 37
	{ "_idpstat"},
D 37
#define N_SPPSTAT	21
E 37
I 37
D 40
#define N_SPPSTAT	18
E 40
I 40
#define N_SPPSTAT	13
E 40
E 37
	{ "_spp_istat"},
D 37
#define N_NSERR		22
E 37
I 37
D 40
#define N_NSERR		19
E 40
I 40
#define N_NSERR		14
E 40
E 37
	{ "_ns_errstat"},
I 26
D 32
#define N_NIMP		23
E 32
I 32
D 37
#define	N_CLNPSTAT	23
E 37
I 37
D 40
#define	N_CLNPSTAT	20
E 40
I 40
#define	N_CLNPSTAT	15
E 40
E 37
	{ "_clnp_stat"},
D 37
#define	IN_TP		24
E 37
I 37
D 40
#define	IN_TP		21
E 40
I 40
D 42
#define	IN_TP		16
E 42
I 42
#define	IN_NOTUSED	16
E 42
E 40
E 37
	{ "_tp_inpcb" },
D 37
#define	ISO_TP		25
E 37
I 37
D 40
#define	ISO_TP		22
E 40
I 40
#define	ISO_TP		17
E 40
E 37
D 42
	{ "_tp_isopcb" },
E 42
I 42
	{ "_tp_refinfo" },
E 42
D 37
#define	ISO_X25		26
E 37
I 37
D 39
#define	ISO_X25		23
E 37
D 33
	{ "_x25_isopcb" },
E 33
I 33
	{ /*"_x25_isopcb"*/ "_file"}, /* fast gross hack to speed up */
E 33
D 37
#define	N_TPSTAT	27
E 37
I 37
#define	N_TPSTAT	24
E 39
I 39
D 40
#define	N_TPSTAT	23
E 40
I 40
#define	N_TPSTAT	18
E 40
E 39
E 37
	{ "_tp_stat" },
D 37
#define	N_X25STAT	28
E 37
I 37
D 39
#define	N_X25STAT	25
E 37
D 33
	{ "_x25_stat" },
E 33
I 33
	{ /*"_x25_stat"*/ "_file"},
E 33
D 37
#define	N_ESISSTAT	29
E 37
I 37
#define	N_ESISSTAT	26
E 39
I 39
D 40
#define	N_ESISSTAT	24
E 40
I 40
#define	N_ESISSTAT	19
E 40
E 39
E 37
	{ "_esis_stat"},
D 37
#define N_NIMP		30
E 37
I 37
D 39
#define N_NIMP		27
E 39
I 39
D 40
#define N_NIMP		25
E 40
I 40
#define N_NIMP		20
E 40
E 39
E 37
E 32
	{ "_nimp"},
I 31
D 32
#define N_RTREE		24
E 32
I 32
D 37
#define N_RTREE		31
E 37
I 37
D 39
#define N_RTREE		28
E 39
I 39
D 40
#define N_RTREE		26
E 40
I 40
#define N_RTREE		21
E 40
E 39
E 37
E 32
D 41
	{ "_radix_node_head"},
E 41
I 41
	{ "_rt_tables"},
E 41
I 33
D 37
#define N_CLTP		32
E 37
I 37
D 39
#define N_CLTP		29
E 39
I 39
D 40
#define N_CLTP		27
E 40
I 40
#define N_CLTP		22
E 40
E 39
E 37
	{ "_cltb"},
D 37
#define N_CLTPSTAT	33
E 37
I 37
D 39
#define N_CLTPSTAT	30
E 39
I 39
D 40
#define N_CLTPSTAT	28
E 40
I 40
#define N_CLTPSTAT	23
E 40
E 39
E 37
	{ "_cltpstat"},
I 45
#define	N_NFILE		24
	{ "_nfile" },
#define	N_FILE		25
	{ "_file" },
#define N_IGMPSTAT	26
	{ "_igmpstat" },
#define N_MRTPROTO	27
	{ "_ip_mrtproto" },
#define N_MRTSTAT	28
	{ "_mrtstat" },
#define N_MRTTABLE	29
	{ "_mrttable" },
#define N_VIFTABLE	30
	{ "_viftable" },
E 45
I 40
D 44
#define	N_NFILE		24
	{ "_nfile" },
#define	N_FILE		25
	{ "_file" },
E 44
E 40
D 37

E 37
E 33
E 31
E 26
I 18

    /* BBN Internet protocol implementation */
#define	N_TCP		23
	{ "_tcp" },
#define	N_UDP		24
	{ "_udp" },
#define N_RDP		25
	{ "_rdp" },
#define	N_RDPSTAT	26
	{ "_rdpstat" },

E 18
E 17
E 12
E 11
E 9
	"",
E 6
};

I 11
D 44
/* internet protocols */
E 11
I 3
D 18
extern	int protopr();
E 18
I 18
extern	int protopr(), bbnprotopr();
E 18
D 6
extern	int tcp_stats(), udp_stats(), ip_stats();
E 6
I 6
extern	int tcp_stats(), udp_stats(), ip_stats(), icmp_stats();
I 24
/* ns protocols */
E 24
I 18
extern	int tcpstats(), udpstats(), ipstats(), icmpstats(), rdpstats();
E 18
I 17
extern	int nsprotopr();
extern	int spp_stats(), idp_stats(), nserr_stats();
I 32
/* iso protocols */
extern	int iso_protopr();
D 33
extern	int tp_stats(), esis_stats(), clnp_stats();
E 33
I 33
extern	int tp_stats(), esis_stats(), clnp_stats(), cltp_stats();
E 33
E 32
E 17
E 6

E 44
I 24
D 37
#define NULLPROTOX	((struct protox *) 0)
E 37
E 24
E 3
struct protox {
D 3
	short	pr_index;	/* index into nlist of cb head */
	short	pr_wanted;	/* 1 if wanted, 0 otherwise */
	char	*pr_name;	/* well-known name */
E 3
I 3
	u_char	pr_index;		/* index into nlist of cb head */
	u_char	pr_sindex;		/* index into nlist of stat block */
	u_char	pr_wanted;		/* 1 if wanted, 0 otherwise */
D 44
	int	(*pr_cblocks)();	/* control blocks printing routine */
	int	(*pr_stats)();		/* statistics printing routine */
E 44
I 44
	void	(*pr_cblocks)();	/* control blocks printing routine */
	void	(*pr_stats)();		/* statistics printing routine */
E 44
	char	*pr_name;		/* well-known name */
E 3
D 18
} protox[] = {
E 18
I 18
};

struct  protox berkprotox[] = {
E 18
D 3
	{ N_TCB,	1,	"tcp" },
	{ N_UDB,	1,	"udp" },
	{ -1,		0,	0 }
E 3
I 3
	{ N_TCB,	N_TCPSTAT,	1,	protopr,
	  tcp_stats,	"tcp" },
	{ N_UDB,	N_UDPSTAT,	1,	protopr,
	  udp_stats,	"udp" },
I 32
D 42
	{ IN_TP,	N_TPSTAT,	1,	protopr,
	  tp_stats,	"tpip" },
E 42
E 32
	{ -1,		N_IPSTAT,	1,	0,
	  ip_stats,	"ip" },
I 6
	{ -1,		N_ICMPSTAT,	1,	0,
	  icmp_stats,	"icmp" },
I 48
	{ -1,		N_IGMPSTAT,	1,	0,
	  igmp_stats,	"igmp" },
E 48
E 6
	{ -1,		-1,		0,	0,
	  0,		0 }
E 3
};

I 18
struct protox bbnprotox[] = {
	{ N_TCP,	N_TCPSTAT,	1,	bbnprotopr,
	  tcpstats,	"tcp" },
	{ N_UDP,	N_UDPSTAT,	1,	bbnprotopr,
	  udpstats,	"udp" },
	{ N_RDP,	N_RDPSTAT,	1,	bbnprotopr,
	  rdpstats,	"rdp" },
	{ N_RAWCB,	0,		1,	bbnprotopr,
	  0,		"raw" },
	{ -1,		N_IPSTAT,	1,	0,
	  ipstats,	"ip" },
	{ -1,		N_ICMPSTAT,	1,	0,
	  icmpstats,	"icmp" },
	{ -1,		-1,		0,	0,
	  0,		0 }
};

E 18
I 17
struct protox nsprotox[] = {
	{ N_IDP,	N_IDPSTAT,	1,	nsprotopr,
	  idp_stats,	"idp" },
	{ N_IDP,	N_SPPSTAT,	1,	nsprotopr,
	  spp_stats,	"spp" },
	{ -1,		N_NSERR,	1,	0,
	  nserr_stats,	"ns_err" },
	{ -1,		-1,		0,	0,
	  0,		0 }
};

I 32
struct protox isoprotox[] = {
	{ ISO_TP,	N_TPSTAT,	1,	iso_protopr,
	  tp_stats,	"tp" },
I 33
	{ N_CLTP,	N_CLTPSTAT,	1,	iso_protopr,
	  cltp_stats,	"cltp" },
E 33
D 39
#ifdef notdef
	{ ISO_X25,	N_X25STAT,	1,	x25_protopr,
	  x25_stats,	"x25" },
#endif
E 39
	{ -1,		N_CLNPSTAT,	1,	 0,
	  clnp_stats,	"clnp"},
	{ -1,		N_ESISSTAT,	1,	 0,
	  esis_stats,	"esis"},
	{ -1,		-1,		0,	0,
	  0,		0 }
};

D 37
struct protox *protoprotox[] = { protox, nsprotox, isoprotox, NULLPROTOX };
E 37
I 37
struct protox *protoprotox[] = { protox, nsprotox, isoprotox, NULL };
E 37

E 32
E 17
D 37
struct	pte *Sysmap;

D 31
char	*system = "/vmunix";
char	*kmemf = "/dev/kmem";
E 31
I 31
char	*system = _PATH_UNIX;
E 37
I 37
D 43
char	*vmunix = _PATH_UNIX;
E 37
D 35
char	*kmemf = _PATH_KMEM;
E 35
I 35
char	*kmemf;
E 43
I 43
D 44
char	*nlistf;
char	*memf;
E 43
E 35
E 31
int	kmem;
int	kflag;
int	Aflag;
int	aflag;
int	hflag;
int	iflag;
int	mflag;
int	nflag;
I 24
int	pflag;
E 24
int	rflag;
int	sflag;
int	tflag;
I 29
int	dflag;
E 29
I 11
D 21
int	uflag;
E 21
I 17
D 24
int	fflag;
E 24
E 17
E 11
int	interval;
D 11
char	usage[] = "[ -Aaihmnrst ] [ interval ] [ system ] [ core ]";
E 11
I 11
D 14
char	usage[] = "[ -Aaihmnrstu ] [ interval ] [ system ] [ core ]";
E 14
I 14
char	*interface;
int	unit;
E 44
I 44
static void printproto __P((struct protox *, char *));
D 54
static void usage __P(());
E 54
I 54
static void usage __P((void));
E 54
static struct protox *name2protox __P((char *));
static struct protox *knownname __P((char *));
E 44
D 17
char	usage[] = "[ -Aaihmnrstu ] [-I interface] [ interval ] [ system ] [ core ]";
E 17
I 17
D 21
char	usage[] = "[ -Aaihmnrstu ] [-f address_family] [-I interface] [ interval ] [ system ] [ core ]";
E 21
I 21
D 24
char	usage[] = "[ -Aaihmnrst ] [-f address_family] [-I interface] [ interval ] [ system ] [ core ]";
E 24
I 24
D 28
char	usage[] = "[ -Aaihmnrst ] [-f family] [-p proto] [-I interface] [ interval ] [ system ] [ core ]";
E 28
E 24
E 21
E 17
E 14
E 11

I 17
D 44
int	af = AF_UNSPEC;
E 44
I 44
kvm_t *kvmd;
E 44
I 21

I 44
int
E 44
I 24
D 37
extern	char *malloc();
extern	off_t lseek();

E 37
E 24
E 21
E 17
main(argc, argv)
	int argc;
D 37
	char *argv[];
E 37
I 37
D 54
	char **argv;
E 54
I 54
	char *argv[];
E 54
E 37
{
D 24
	int i;
E 24
D 28
	char *cp, *name;
E 28
I 28
	extern char *optarg;
	extern int optind;
E 28
	register struct protoent *p;
I 17
D 24
	register struct protox *tp;
E 17

E 24
I 24
	register struct protox *tp;	/* for printing cblocks & stats */
D 44
	struct protox *name2protox();	/* for -p */
E 44
I 44
	register char *cp;
E 44
D 28
	
E 24
	name = argv[0];
	argc--, argv++;
  	while (argc > 0 && **argv == '-') {
		for (cp = &argv[0][1]; *cp; cp++)
D 10
		switch(argv[0][1]) {
E 10
I 10
		switch(*cp) {
E 28
I 28
	int ch;
I 37
D 44
	void usage(); 
E 44
I 44
	char *nlistf = NULL, *memf = NULL;
	char buf[_POSIX2_LINE_MAX];
E 44
E 37
E 28
E 10

I 44
	if (cp = rindex(argv[0], '/'))
		prog = cp + 1;
	else
		prog = argv[0];
	af = AF_UNSPEC;

E 44
I 28
D 29
	while ((ch = getopt(argc, argv, "AI:af:himnp:rstu")) != EOF)
E 29
I 29
D 37
	while ((ch = getopt(argc, argv, "AI:af:himnp:drstu")) != EOF)
E 37
I 37
D 45
	while ((ch = getopt(argc, argv, "Aadf:hI:iM:mN:np:rstuw")) != EOF)
E 45
I 45
D 47
	while ((ch = getopt(argc, argv, "AaBdf:hI:iM:mN:np:rstuw")) != EOF)
E 45
E 37
E 29
		switch((char)ch) {
E 47
I 47
D 50
	while ((ch = getopt(argc, argv, "AaBdf:hI:iM:mN:np:rstuw:")) != EOF)
E 50
I 50
D 53
	while ((ch = getopt(argc, argv, "AaBdf:I:iM:mN:np:rstuw:")) != EOF)
E 53
I 53
	while ((ch = getopt(argc, argv, "Aadf:ghI:iM:mN:np:rstuw:")) != EOF)
E 53
E 50
		switch(ch) {
E 47
E 28
		case 'A':
D 37
			Aflag++;
E 37
I 37
			Aflag = 1;
E 37
			break;
I 28
D 37
		case 'I': {
			char *cp;
E 28

I 28
			iflag++;
			for (cp = interface = optarg; isalpha(*cp); cp++);
			unit = atoi(cp);
			*cp = '\0';
			break;
		}
E 37
E 28
		case 'a':
D 37
			aflag++;
E 37
I 37
			aflag = 1;
E 37
I 29
			break;
I 45
D 53
		case 'B':
			Bflag = 1;
			break;
E 53
E 45
		case 'd':
D 37
			dflag++;
E 37
I 37
			dflag = 1;
E 37
E 29
			break;
D 28

E 28
I 28
		case 'f':
			if (strcmp(optarg, "ns") == 0)
				af = AF_NS;
			else if (strcmp(optarg, "inet") == 0)
				af = AF_INET;
			else if (strcmp(optarg, "unix") == 0)
				af = AF_UNIX;
I 32
			else if (strcmp(optarg, "iso") == 0)
				af = AF_ISO;
E 32
			else {
D 37
				fprintf(stderr, "%s: unknown address family\n", optarg);
				exit(10);
E 37
I 37
				(void)fprintf(stderr,
D 44
				    "%s: unknown address family\n", optarg);
E 44
I 44
				    "%s: %s: unknown address family\n",
				    prog, optarg);
E 44
				exit(1);
E 37
			}
			break;
I 53
		case 'g':
			gflag = 1;
			break;
E 53
E 28
D 50
		case 'h':
D 37
			hflag++;
E 37
I 37
			hflag = 1;
E 37
			break;
E 50
I 37
		case 'I': {
			char *cp;

			iflag = 1;
D 44
			for (cp = interface = optarg; isalpha(*cp); cp++);
E 44
I 44
			for (cp = interface = optarg; isalpha(*cp); cp++)
				continue;
E 44
			unit = atoi(cp);
			*cp = '\0';
			break;
		}
E 37
D 28

E 28
		case 'i':
D 37
			iflag++;
E 37
I 37
			iflag = 1;
E 37
			break;
I 37
		case 'M':
D 43
			kmemf = optarg;
E 43
I 43
			memf = optarg;
E 43
D 44
			kflag = 1;
E 44
			break;
E 37
D 28

E 28
		case 'm':
D 37
			mflag++;
E 37
I 37
			mflag = 1;
E 37
			break;
I 37
		case 'N':
D 43
			vmunix = optarg;
E 43
I 43
			nlistf = optarg;
E 43
			break;
E 37
D 28

E 28
		case 'n':
D 37
			nflag++;
E 37
I 37
			nflag = 1;
E 37
			break;
D 28

E 28
I 28
		case 'p':
D 37
			if ((tp = name2protox(optarg)) == NULLPROTOX) {
				fprintf(stderr, "%s: unknown or uninstrumented protocol\n", optarg);
				exit(10);
E 37
I 37
			if ((tp = name2protox(optarg)) == NULL) {
				(void)fprintf(stderr,
D 44
				    "%s: unknown or uninstrumented protocol\n",
				    optarg);
E 44
I 44
				    "%s: %s: unknown or uninstrumented protocol\n",
				    prog, optarg);
E 44
				exit(1);
E 37
			}
D 37
			pflag++;
E 37
I 37
			pflag = 1;
E 37
			break;
E 28
		case 'r':
D 37
			rflag++;
E 37
I 37
			rflag = 1;
E 37
			break;
D 28

E 28
		case 's':
D 37
			sflag++;
E 37
I 37
D 44
			sflag = 1;
E 44
I 44
			++sflag;
E 44
E 37
			break;
D 28

E 28
		case 't':
D 37
			tflag++;
E 37
I 37
			tflag = 1;
E 37
			break;
D 28

E 28
I 11
		case 'u':
D 21
			uflag++;
E 21
I 21
			af = AF_UNIX;
E 21
I 14
			break;
I 37
		case 'w':
			interval = atoi(optarg);
I 52
			iflag = 1;
E 52
			break;
E 37
I 28
		case '?':
		default:
			usage();
		}
	argv += optind;
	argc -= optind;
E 28

I 24
D 28
		case 'p':
			argv++;
			argc--;
			if (argc == 0)
				goto use;
			if ((tp = name2protox(*argv)) == NULLPROTOX) {
				fprintf(stderr, "%s: unknown or uninstrumented protocol\n",
					*argv);
				exit(10);
			}
			pflag++;
			break;

E 24
I 17
		case 'f':
			argv++;
			argc--;
D 21
			if (strcmp(*argv,"ns")==0) {
E 21
I 21
			if (strcmp(*argv, "ns") == 0)
E 21
				af = AF_NS;
D 21
			} else if (strcmp(*argv,"inet")==0) {
E 21
I 21
			else if (strcmp(*argv, "inet") == 0)
E 21
				af = AF_INET;
I 21
			else if (strcmp(*argv, "unix") == 0)
				af = AF_UNIX;
			else {
				fprintf(stderr, "%s: unknown address family\n",
					*argv);
				exit(10);
E 21
			}
			break;
			
E 17
		case 'I':
E 28
I 28
D 37
	if (argc > 0) {
		if (isdigit(argv[0][0])) {
			interval = atoi(argv[0]);
E 37
I 37
#define	BACKWARD_COMPATIBILITY
#ifdef	BACKWARD_COMPATIBILITY
	if (*argv) {
		if (isdigit(**argv)) {
			interval = atoi(*argv);
E 37
			if (interval <= 0)
				usage();
D 37
			argv++, argc--;
E 28
			iflag++;
E 37
I 37
			++argv;
			iflag = 1;
E 37
D 28
			if (*(interface = cp + 1) == 0) {
				if ((interface = argv[1]) == 0)
					break;
				argv++;
				argc--;
E 28
I 28
		}
D 37
		if (argc > 0) {
			system = *argv;
			argv++, argc--;
			if (argc > 0) {
E 37
I 37
		if (*argv) {
D 43
			vmunix = *argv;
E 43
I 43
			nlistf = *argv;
E 43
D 44
			if (*++argv) {
E 44
I 44
			if (*++argv)
E 44
E 37
D 43
				kmemf = *argv;
E 43
I 43
				memf = *argv;
E 43
D 37
				kflag++;
E 37
I 37
D 44
				kflag = 1;
E 37
E 28
			}
E 44
D 28
			for (cp = interface; isalpha(*cp); cp++)
				;
			unit = atoi(cp);
			*cp-- = 0;
E 14
			break;

E 11
		default:
use:
			printf("usage: %s %s\n", name, usage);
			exit(1);
E 28
		}
D 28
		argv++, argc--;
E 28
	}
D 28
	if (argc > 0 && isdigit(argv[0][0])) {
		interval = atoi(argv[0]);
		if (interval <= 0)
			goto use;
		argv++, argc--;
I 2
		iflag++;
E 2
	}
	if (argc > 0) {
		system = *argv;
		argv++, argc--;
	}
	nlist(system, nl);
	if (nl[0].n_type == 0) {
E 28
I 28
D 35
	if (nlist(system, nl) < 0 || nl[0].n_type == 0) {
E 28
		fprintf(stderr, "%s: no namelist\n", system);
E 35
I 35
D 37
	if (kvm_openfiles(system, kmemf, (char *)0) == -1) {
D 36
		fprintf("netstat(kvm_openfiles): %s\n", kvm_geterr());
E 36
I 36
		fprintf(stderr, "netstat(kvm_openfiles): %s\n", kvm_geterr());
E 37
I 37
#endif
I 44

E 44
D 43
	if (kvm_openfiles(vmunix, kmemf, NULL) == -1) {
E 43
I 43
	/*
	 * Discard setgid privileges if not the running kernel so that bad
	 * guys can't print interesting stuff from kernel memory.
	 */
	if (nlistf != NULL || memf != NULL)
		setgid(getgid());

D 44
	if (kvm_openfiles(nlistf, memf, NULL) == -1) {
E 43
		fprintf(stderr, "netstat: kvm_openfiles: %s\n", kvm_geterr());
E 44
I 44
	if ((kvmd = kvm_open(nlistf, memf, NULL, O_RDONLY, prog)) == NULL) {
		fprintf(stderr, "%s: kvm_open: %s\n", prog, buf);
E 44
E 37
E 36
E 35
		exit(1);
	}
D 28
	if (argc > 0) {
		kmemf = *argv;
		kflag++;
	}
	kmem = open(kmemf, 0);
E 28
I 28
D 35
	kmem = open(kmemf, O_RDONLY);
E 28
	if (kmem < 0) {
D 28
		fprintf(stderr, "cannot open ");
E 28
		perror(kmemf);
E 35
I 35
D 44
	if (kvm_nlist(nl) < 0 || nl[0].n_type == 0) {
D 37
		fprintf(stderr, "%s: no namelist\n", system);
E 37
I 37
D 43
		fprintf(stderr, "%s: no namelist\n", vmunix);
E 43
I 43
		fprintf(stderr, "netstat: no namelist\n");
E 44
I 44
	if (kvm_nlist(kvmd, nl) < 0 || nl[0].n_type == 0) {
		if (nlistf)
			fprintf(stderr, "%s: %s: no namelist\n", prog, nlistf);
		else
			fprintf(stderr, "%s: no namelist\n", prog);
E 44
E 43
E 37
E 35
		exit(1);
	}
D 35
	if (kflag) {
		off_t off;

D 28
		off = nl[N_SYSMAP].n_value & 0x7fffffff;
		lseek(kmem, off, 0);
		nl[N_SYSSIZE].n_value *= 4;
D 24
		Sysmap = (struct pte *)malloc(nl[N_SYSSIZE].n_value);
E 24
I 24
		Sysmap = (struct pte *)malloc((u_int)nl[N_SYSSIZE].n_value);
E 24
		if (Sysmap == 0) {
			perror("Sysmap");
E 28
I 28
		Sysmap = (struct pte *)
		   malloc((u_int)(nl[N_SYSSIZE].n_value * sizeof(struct pte)));
		if (!Sysmap) {
			fputs("netstat: can't get memory for Sysmap.\n", stderr);
E 28
			exit(1);
		}
D 24
		read(kmem, Sysmap, nl[N_SYSSIZE].n_value);
E 24
I 24
D 28
		read(kmem, (char *)Sysmap, (int)nl[N_SYSSIZE].n_value);
E 28
I 28
		off = nl[N_SYSMAP].n_value & ~KERNBASE;
		(void)lseek(kmem, off, L_SET);
		(void)read(kmem, (char *)Sysmap,
		    (int)(nl[N_SYSSIZE].n_value * sizeof(struct pte)));
E 28
E 24
	}
E 35
	if (mflag) {
D 24
		mbpr(nl[N_MBSTAT].n_value);
E 24
I 24
D 46
		mbpr((off_t)nl[N_MBSTAT].n_value);
E 46
I 46
		mbpr(nl[N_MBSTAT].n_value);
E 46
E 24
I 11
		exit(0);
	}
I 24
	if (pflag) {
		if (tp->pr_stats)
D 28
			(*tp->pr_stats)(nl[tp->pr_sindex].n_value, 
E 28
I 28
			(*tp->pr_stats)(nl[tp->pr_sindex].n_value,
E 28
				tp->pr_name);
		else
			printf("%s: no stats routine\n", tp->pr_name);
		exit(0);
	}
I 26
D 50
	if (hflag) {
		hostpr(nl[N_IMP].n_value, nl[N_NIMP].n_value);
		exit(0);
	}
E 50
E 26
E 24
D 21
	if (uflag) {
		unixpr(nl[N_NFILE].n_value, nl[N_FILE].n_value,
		    nl[N_UNIXSW].n_value);
E 11
		exit(0);
	}
E 21
D 2
	if (iflag) {
		intpr(interval, nl[N_IFNET].n_value);
		exit(0);
	}
E 2
	/*
	 * Keep file descriptors open to avoid overhead
	 * of open/close on each call to get* routines.
	 */
D 2
	setprotoent(1);
E 2
	sethostent(1);
	setnetent(1);
D 2
	setservent(1);
E 2
I 2
	if (iflag) {
		intpr(interval, nl[N_IFNET].n_value);
		exit(0);
	}
E 2
D 26
	if (hflag) {
		hostpr(nl[N_HOSTS].n_value);
		exit(0);
	}
E 26
	if (rflag) {
D 9
		routepr(nl[N_RTHOST].n_value, nl[N_RTNET].n_value);
E 9
I 9
		if (sflag)
D 24
			rt_stats(nl[N_RTSTAT].n_value);
E 24
I 24
D 46
			rt_stats((off_t)nl[N_RTSTAT].n_value);
E 46
I 46
			rt_stats(nl[N_RTSTAT].n_value);
E 46
E 24
		else
D 12
			routepr(nl[N_RTHOST].n_value, nl[N_RTNET].n_value);
E 12
I 12
D 24
			routepr(nl[N_RTHOST].n_value, nl[N_RTNET].n_value,
				nl[N_RTHASHSIZE].n_value);
E 24
I 24
D 40
			routepr((off_t)nl[N_RTHOST].n_value, 
				(off_t)nl[N_RTNET].n_value,
D 31
				(off_t)nl[N_RTHASHSIZE].n_value);
E 31
I 31
				(off_t)nl[N_RTHASHSIZE].n_value,
				(off_t)nl[N_RTREE].n_value);
E 40
I 40
D 46
			routepr((off_t)nl[N_RTREE].n_value);
E 46
I 46
			routepr(nl[N_RTREE].n_value);
E 46
E 40
E 31
E 24
E 12
E 9
		exit(0);
	}
I 45
D 53
	if (Bflag) {
E 53
I 53
	if (gflag) {
E 53
		if (sflag)
D 46
			mrt_stats((off_t)nl[N_MRTPROTO].n_value,
			    (off_t)nl[N_MRTSTAT].n_value);
E 46
I 46
			mrt_stats(nl[N_MRTPROTO].n_value,
			    nl[N_MRTSTAT].n_value);
E 46
		else
D 46
			mroutepr((off_t)nl[N_MRTPROTO].n_value,
			    (off_t)nl[N_MRTTABLE].n_value,
			    (off_t)nl[N_VIFTABLE].n_value);
E 46
I 46
			mroutepr(nl[N_MRTPROTO].n_value,
			    nl[N_MRTTABLE].n_value,
			    nl[N_VIFTABLE].n_value);
E 46
		exit(0);
	}
E 45
I 17
D 44
    if (af == AF_INET || af == AF_UNSPEC) {
I 18
	struct protox *head;

	head = (nl[N_TCB].n_type == 0) ? bbnprotox : berkprotox;
E 18
E 17
I 2
	setprotoent(1);
	setservent(1);
E 2
D 18
	while (p = getprotoent()) {
E 44
I 44
	if (af == AF_INET || af == AF_UNSPEC) {
		setprotoent(1);
		setservent(1);
		/* ugh, this is O(MN) ... why do we do this? */
		while (p = getprotoent()) {
			for (tp = protox; tp->pr_name; tp++)
				if (strcmp(tp->pr_name, p->p_name) == 0)
					break;
			if (tp->pr_name == 0 || tp->pr_wanted == 0)
				continue;
			printproto(tp, p->p_name);
		}
		endprotoent();
	}
	if (af == AF_NS || af == AF_UNSPEC)
		for (tp = nsprotox; tp->pr_name; tp++)
			printproto(tp, tp->pr_name);
	if (af == AF_ISO || af == AF_UNSPEC)
		for (tp = isoprotox; tp->pr_name; tp++)
			printproto(tp, tp->pr_name);
	if ((af == AF_UNIX || af == AF_UNSPEC) && !sflag)
D 46
		unixpr((struct protosw *)nl[N_UNIXSW].n_value);
E 46
I 46
		unixpr(nl[N_UNIXSW].n_value);
E 46
D 50
	if (af == AF_UNSPEC && sflag)
		impstats(nl[N_IMP].n_value, nl[N_NIMP].n_value);
E 50
	exit(0);
}
E 44
E 18
D 17
		register struct protox *tp;
E 17

D 3
		for (tp = protox; tp->pr_index >= 0; tp++)
E 3
I 3
D 18
D 44
		for (tp = protox; tp->pr_name; tp++)
E 3
			if (strcmp(tp->pr_name, p->p_name) == 0)
				break;
D 3
		if (tp->pr_index < 0 || tp->pr_wanted == 0)
E 3
I 3
		if (tp->pr_name == 0 || tp->pr_wanted == 0)
E 18
I 18
	for (tp = head; tp->pr_name; tp++) {
		if (tp->pr_wanted == 0)
E 18
E 3
			continue;
D 3
		protopr(nl[tp->pr_index].n_value, p->p_name);
E 3
I 3
D 18
D 22
		if (sflag && tp->pr_stats) {
			(*tp->pr_stats)(nl[tp->pr_sindex].n_value, p->p_name);
			continue;
		}
		if (tp->pr_cblocks)
			(*tp->pr_cblocks)(nl[tp->pr_index].n_value, p->p_name);
E 22
I 22
		if (sflag) {
			if (tp->pr_stats)
				(*tp->pr_stats)(nl[tp->pr_sindex].n_value,
					p->p_name);
		} else
			if (tp->pr_cblocks)
				(*tp->pr_cblocks)(nl[tp->pr_index].n_value,
					p->p_name);
E 44
I 44
/*
 * Print out protocol statistics or control blocks (per sflag).
 * If the interface was not specifically requested, and the symbol
 * is not in the namelist, ignore this one.
 */
static void
printproto(tp, name)
	register struct protox *tp;
	char *name;
{
	void (*pr)();
D 46
	off_t off;
E 46
I 46
	u_long off;
E 46

	if (sflag) {
		pr = tp->pr_stats;
		off = nl[tp->pr_sindex].n_value;
	} else {
		pr = tp->pr_cblocks;
		off = nl[tp->pr_index].n_value;
E 44
E 22
E 18
I 18

		if (sflag) {
			if (tp->pr_stats)
			    (*tp->pr_stats)(nl[tp->pr_sindex].n_value, tp->pr_name);
		} else if (tp->pr_cblocks)
			(*tp->pr_cblocks)(nl[tp->pr_index].n_value, tp->pr_name);
E 18
E 3
	}
D 44
	endprotoent();
I 17
    }
    if (af == AF_NS || af == AF_UNSPEC) {
	for (tp = nsprotox; tp->pr_name; tp++) {
D 22
		if (sflag && tp->pr_stats) {
			(*tp->pr_stats)(nl[tp->pr_sindex].n_value, tp->pr_name);
			continue;
		}
		if (tp->pr_cblocks)
			(*tp->pr_cblocks)(nl[tp->pr_index].n_value, tp->pr_name);
E 22
I 22
		if (sflag) {
			if (tp->pr_stats)
				(*tp->pr_stats)(nl[tp->pr_sindex].n_value,
					tp->pr_name);
		} else
			if (tp->pr_cblocks)
				(*tp->pr_cblocks)(nl[tp->pr_index].n_value,
					tp->pr_name);
E 44
I 44
	if (pr != NULL && (off || af != AF_UNSPEC))
		(*pr)(off, name);
}

/*
 * Read kernel memory, return 0 on success.
 */
int
kread(addr, buf, size)
D 46
	off_t addr;
E 46
I 46
	u_long addr;
E 46
	char *buf;
	int size;
{

	if (kvm_read(kvmd, addr, buf, size) != size) {
		/* XXX this duplicates kvm_read's error printout */
		(void)fprintf(stderr, "%s: kvm_read %s\n", prog,
		    kvm_geterr(kvmd));
		return (-1);
E 44
E 22
	}
D 44
    }
I 32
    if (af == AF_ISO || af == AF_UNSPEC) {
	for (tp = isoprotox; tp->pr_name; tp++) {
		if (sflag) {
			if (tp->pr_stats)
				(*tp->pr_stats)(nl[tp->pr_sindex].n_value,
					tp->pr_name);
		} else
			if (tp->pr_cblocks)
				(*tp->pr_cblocks)(nl[tp->pr_index].n_value,
					tp->pr_name);
	}
    }
E 32
I 21
D 22
    if (af == AF_UNIX || af == AF_UNSPEC)
E 22
I 22
    if ((af == AF_UNIX || af == AF_UNSPEC) && !sflag)
E 22
D 24
	    unixpr(nl[N_NFILE].n_value, nl[N_FILE].n_value,
		nl[N_UNIXSW].n_value);
E 24
I 24
	    unixpr((off_t)nl[N_NFILE].n_value, (off_t)nl[N_FILE].n_value,
		(struct protosw *)nl[N_UNIXSW].n_value);
I 26
    if (af == AF_UNSPEC && sflag)
	impstats(nl[N_IMP].n_value, nl[N_NIMP].n_value);
E 26
E 24
E 21
I 20
    exit(0);
E 44
I 44
	return (0);
E 44
E 20
E 17
}

D 35
/*
 * Seek into the kernel for a value.
 */
I 24
off_t
E 24
klseek(fd, base, off)
D 24
	int fd, base, off;
E 24
I 24
	int fd, off;
	off_t base;
E 24
{
D 24

E 24
	if (kflag) {
		/* get kernel pte */
I 5
D 25
#ifdef vax
E 5
		base &= 0x7fffffff;
D 5
		base = Sysmap[base >> 9].pg_pfnum * 512 + (base & 0x1ff);
E 5
I 5
#endif
E 25
I 25
		base &= ~KERNBASE;
E 25
D 7
		base = ctob(Sysmap[btoc(base)].pg_pfnum) + (base & (NBPG-1));
E 7
I 7
D 8
		base = ctob(Sysmap[base >> PGSHIFT].pg_pfnum) +
			(base & PGOFSET);
E 8
I 8
		base = ctob(Sysmap[btop(base)].pg_pfnum) + (base & PGOFSET);
E 8
E 7
E 5
	}
D 24
	lseek(fd, base, off);
E 24
I 24
	return (lseek(fd, base, off));
E 24
I 9
}
E 35
D 37

E 37
char *
plural(n)
	int n;
{
D 37

E 37
	return (n != 1 ? "s" : "");
I 45
}

char *
plurales(n)
	int n;
{
	return (n != 1 ? "es" : "");
E 45
I 24
}

/*
 * Find the protox for the given "well-known" name.
 */
D 44
struct protox *
E 44
I 44
static struct protox *
E 44
knownname(name)
	char *name;
{
D 32
	struct protox *tp;
E 32
I 32
	struct protox **tpp, *tp;
E 32
D 28
	
E 28
I 28

E 28
D 32
	for (tp = protox; tp->pr_name; tp++)
		if (strcmp(tp->pr_name, name) == 0)
			return(tp);
	for (tp = nsprotox; tp->pr_name; tp++)
E 32
I 32
	for (tpp = protoprotox; *tpp; tpp++)
D 44
	    for (tp = *tpp; tp->pr_name; tp++)
E 32
		if (strcmp(tp->pr_name, name) == 0)
			return(tp);
D 37
	return(NULLPROTOX);
E 37
I 37
	return(NULL);
E 44
I 44
		for (tp = *tpp; tp->pr_name; tp++)
			if (strcmp(tp->pr_name, name) == 0)
				return (tp);
	return (NULL);
E 44
E 37
}

/*
 * Find the protox corresponding to name.
 */
D 44
struct protox *
E 44
I 44
static struct protox *
E 44
name2protox(name)
	char *name;
{
	struct protox *tp;
	char **alias;			/* alias from p->aliases */
	struct protoent *p;
D 28
	
E 28
I 28

E 28
	/*
	 * Try to find the name in the list of "well-known" names. If that
	 * fails, check if name is an alias for an Internet protocol.
	 */
	if (tp = knownname(name))
D 44
		return(tp);
E 44
I 44
		return (tp);
E 44
D 28
		
E 28
I 28

E 28
	setprotoent(1);			/* make protocol lookup cheaper */
	while (p = getprotoent()) {
		/* assert: name not same as p->name */
		for (alias = p->p_aliases; *alias; alias++)
			if (strcmp(name, *alias) == 0) {
				endprotoent();
D 44
				return(knownname(p->p_name));
E 44
I 44
				return (knownname(p->p_name));
E 44
			}
	}
	endprotoent();
D 37
	return(NULLPROTOX);
E 37
I 37
D 44
	return(NULL);
E 44
I 44
	return (NULL);
E 44
E 37
I 28
}

I 37
D 44
void
E 44
I 44
static void
E 44
E 37
usage()
{
D 37
	fputs("usage: netstat [-Aan] [-f address_family] [system] [core]\n               [-himnrs] [-f address_family] [system] [core]\n               [-n] [-I interface] interval [system] [core]\n", stderr);
E 37
I 37
	(void)fprintf(stderr,
D 44
"usage: netstat [-Aan] [-f address_family] [-M core] [-N system]\n");
E 44
I 44
"usage: %s [-Aan] [-f address_family] [-M core] [-N system]\n", prog);
E 44
	(void)fprintf(stderr,
D 53
"               [-himnrs] [-f address_family] [-M core] [-N system]\n");
E 53
I 53
D 54
"               [-ghimnrs] [-f address_family] [-M core] [-N system]\n");
E 54
I 54
"       %s [-ghimnrs] [-f address_family] [-M core] [-N system]\n", prog);
E 54
E 53
	(void)fprintf(stderr,
D 54
"               [-n] [-I interface] [-M core] [-N system] [-w wait]\n");
E 54
I 54
"       %s [-n] [-I interface] [-M core] [-N system] [-w wait]\n", prog);
E 54
	(void)fprintf(stderr,
D 54
"               [-M core] [-N system] [-p protocol]\n");
E 54
I 54
"       %s [-M core] [-N system] [-p protocol]\n", prog);
E 54
E 37
	exit(1);
E 28
E 24
E 9
}
E 1
