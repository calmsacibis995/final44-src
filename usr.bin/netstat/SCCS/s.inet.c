h51540
s 00003/00001/00467
d D 8.5 95/05/24 06:01:02 karels 48 47
c two new counters (tcps_badsyn and tcps_persistdrop)
e
s 00002/00002/00466
d D 8.4 94/04/20 12:41:37 bostic 47 46
c Mike's cleanups
e
s 00006/00000/00462
d D 8.3 94/04/16 06:15:01 bostic 46 45
c move tcppredack, tcppreddat, tcppcbcachemiss into the TCP stats structure
c Rich Stevens asked, Mike Karels agreed.
e
s 00002/00002/00460
d D 8.2 93/12/30 17:41:44 mckusick 45 44
c fields printed out backwards (from karels@bsdi.com)
e
s 00002/00002/00460
d D 8.1 93/06/06 15:43:42 bostic 44 43
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00064/00005/00398
d D 5.20 93/02/16 23:00:01 andrew 43 42
c improve ip & udp stats routines, add Deering's igmp routine
e
s 00008/00008/00395
d D 5.19 92/07/07 16:57:16 sklower 42 41
c not every value return in an nlist structure was being
c coerced to an (off_t) which was only being smashed back down to a (u_long)
c as an argument to kvm_read.  If you ask me nl.n_value ought to be a (void *)
c but since the type of nl.n_value and the second argument to kvm_read are
c the same I got fed up and changed all the off_t's to be that type (u_long).
e
s 00004/00003/00399
d D 5.18 92/07/06 15:36:18 sklower 41 40
c Multicast changes from lbl
e
s 00004/00004/00398
d D 5.17 92/06/18 12:19:28 sklower 40 39
c routines to print inet to ascii should not be private; TP4 runs over IP
e
s 00083/00078/00319
d D 5.16 92/05/27 18:11:54 sklower 39 38
c incorporate changes for new kvm interfaces from lbl
e
s 00010/00017/00387
d D 5.15 90/06/18 17:20:28 sklower 38 37
c use kvm_nlist to avoid numerous lseeks of nlist; use kvm_read to avoid duplication.
e
s 00001/00011/00403
d D 5.14 90/06/01 17:07:42 bostic 37 36
c new copyright notice
e
s 00003/00003/00411
d D 5.13 90/05/15 20:01:28 bostic 36 35
c string.h is ANSI C include file
e
s 00001/00001/00413
d D 5.12 90/04/07 16:12:51 sklower 35 34
c in_pcb now has proto ip header; switch order of includes
e
s 00012/00007/00402
d D 5.11 88/06/29 20:42:03 bostic 34 33
c install approved copyright notice
e
s 00009/00003/00400
d D 5.10 88/02/07 20:38:16 karels 33 31
c new copyrights
e
s 00008/00000/00403
d D 5.9.1.1 88/02/07 20:23:42 karels 32 31
c branch for FTP release (#ifdef for sun)
e
s 00048/00039/00355
d D 5.9 88/01/03 00:10:13 bostic 31 30
c fix CPP macros for ANSI C
e
s 00002/00002/00392
d D 5.8 87/09/15 14:41:44 bostic 30 27
c address mask request/reply fix; bug report 4.3BSD/ucb/117
e
s 00001/00001/00393
d R 5.9 87/09/15 14:39:47 bostic 29 28
c address mask request/reply fix; bug report 4.3BSD/ucb/117
e
s 00003/00003/00391
d R 5.8 87/09/15 14:34:17 bostic 28 27
c address mask request/reply fix; bug report 4.3BSD/ucb/117
e
s 00043/00012/00351
d D 5.7 87/02/03 22:19:28 karels 27 26
c new tcp statistics
e
s 00029/00029/00334
d D 5.6 86/12/15 17:10:39 sam 26 25
c all statistics are unsigned
e
s 00013/00011/00350
d D 5.5 86/08/11 11:50:36 kupfer 25 24
c Some lint.
e
s 00001/00001/00360
d D 5.4 86/02/25 21:47:59 karels 24 23
c I wanna see the digits!
e
s 00018/00003/00343
d D 5.3 85/09/18 16:47:21 karels 23 22
c add dynamic route flag; truncate domain names if same as ours;
c simplify subnet guessing, so as not to guess forever
e
s 00051/00041/00295
d D 5.2 85/09/12 08:38:12 karels 22 20
c update for new statistics, reorganize a bit, quiet if not configured
c or nothing to say
e
s 00036/00027/00309
d R 5.2 85/09/10 08:49:06 karels 21 20
c update statistics; quiet if nothing to report
e
s 00008/00002/00328
d D 5.1 85/06/04 15:35:47 dist 20 19
c Add copyright
e
s 00011/00019/00319
d D 4.19 85/06/03 13:29:00 karels 19 18
c new subnets, interface addressing
e
s 00006/00003/00332
d D 4.18 84/10/31 11:39:34 karels 18 17
c wider format not used with -A
e
s 00007/00005/00328
d D 4.17 84/07/04 11:51:04 sam 17 16
c don't search for net number when zero; from dpk@brl
e
s 00013/00005/00320
d D 4.16 84/05/17 11:17:34 karels 16 15
c subnet fixes
e
s 00009/00008/00316
d D 4.15 84/05/11 12:23:28 karels 15 14
c print subnet addresses correctly; wider address fields
e
s 00003/00001/00321
d D 4.14 83/09/21 19:05:54 sam 14 13
c cleanup after wnj changes to icmp
e
s 00002/00001/00320
d D 4.13 83/09/16 07:23:02 sam 13 12
c missing param to printf
e
s 00035/00023/00286
d D 4.12 83/05/30 21:10:00 sam 12 11
c pretty up
e
s 00001/00001/00308
d D 4.11 83/03/12 19:25:00 sam 11 10
c poor grammar
e
s 00003/00003/00306
d D 4.10 83/03/11 13:34:41 sam 10 9
c formatting
e
s 00066/00000/00243
d D 4.9 83/03/11 11:30:17 sam 9 8
c add icmp statistics printing
e
s 00005/00001/00238
d D 4.8 83/02/24 14:04:08 sam 8 7
c new ip statistics
e
s 00001/00004/00238
d D 4.7 82/12/18 19:08:50 sam 7 6
c port numbers byte swapped
e
s 00063/00000/00179
d D 4.6 82/12/05 23:51:23 sam 6 5
c put back -s option
e
s 00017/00001/00162
d D 4.5 82/11/14 15:11:41 sam 5 4
c convert to 4.1c directory layout
e
s 00004/00044/00159
d D 4.4 82/10/07 18:14:23 sam 4 3
c use routines now in libc.a
e
s 00003/00002/00200
d D 4.3 82/10/06 17:52:47 sam 3 2
c add address format
e
s 00004/00003/00198
d D 4.2 82/10/05 22:18:07 sam 2 1
c new library routines
e
s 00201/00000/00000
d D 4.1 82/08/25 22:21:41 sam 1 0
c date and time created 82/08/25 22:21:41 by sam
e
u
U
f b 
t
T
I 20
D 39
/*
E 39
I 39
D 41
    /*
E 41
I 41
/*
E 41
E 39
D 33
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 33
I 33
D 34
 * Copyright (c) 1983,1988 Regents of the University of California.
E 34
I 34
D 44
 * Copyright (c) 1983, 1988 Regents of the University of California.
E 34
 * All rights reserved.
E 44
I 44
D 48
 * Copyright (c) 1983, 1988, 1993
E 48
I 48
 * Copyright (c) 1983, 1988, 1993, 1995
E 48
 *	The Regents of the University of California.  All rights reserved.
E 44
 *
D 37
 * Redistribution and use in source and binary forms are permitted
D 34
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 34
I 34
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
E 37
I 37
 * %sccs.include.redist.c%
E 37
E 34
E 33
 */

E 20
I 1
#ifndef lint
D 14
static char sccsid[] = "%W% %E%";
E 14
I 14
D 20
static char sccsid[] = "%W% (Berkeley) %E%";
E 14
#endif
E 20
I 20
static char sccsid[] = "%W% (Berkeley) %G%";
D 34
#endif not lint
E 34
I 34
#endif /* not lint */
E 34
E 20

I 25
D 36
#include <strings.h>
#include <stdio.h>

E 36
E 25
D 23
#include <sys/types.h>
E 23
I 23
#include <sys/param.h>
E 23
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
I 5

E 5
#include <net/route.h>
I 5
#include <netinet/in.h>
#include <netinet/in_systm.h>
D 35
#include <netinet/in_pcb.h>
E 35
#include <netinet/ip.h>
I 35
#include <netinet/in_pcb.h>
E 35
#include <netinet/ip_icmp.h>
I 9
#include <netinet/icmp_var.h>
I 43
#include <netinet/igmp_var.h>
E 43
E 9
#include <netinet/ip_var.h>
#include <netinet/tcp.h>
#include <netinet/tcpip.h>
#include <netinet/tcp_seq.h>
E 5
#define TCPSTATES
D 5
#include <net/inet.h>
E 5
I 5
#include <netinet/tcp_fsm.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/tcp_debug.h>
#include <netinet/udp.h>
#include <netinet/udp_var.h>

I 39
#include <arpa/inet.h>
E 39
E 5
#include <netdb.h>
I 36
D 39

E 39
#include <stdio.h>
#include <string.h>
I 41
#include <unistd.h>
E 41
I 39
#include "netstat.h"
E 39
E 36

struct	inpcb inpcb;
struct	tcpcb tcpcb;
D 19
struct	socket socket;
E 19
I 19
struct	socket sockb;
E 19
D 25
struct	protosw proto;
E 25
D 38
extern	int kmem;
E 38
D 39
extern	int Aflag;
extern	int aflag;
extern	int nflag;
I 25
extern	char *plural();
E 39
E 25

D 25
static	int first = 1;
E 25
D 39
char	*inetname();
E 39
I 39
D 40
static char *inetname __P((struct in_addr *));
static void inetprint __P((struct in_addr *, int, char *));
E 40
I 40
D 41
char *inetname __P((struct in_addr *));
void inetprint __P((struct in_addr *, int, char *));
E 41
I 41
char	*inetname __P((struct in_addr *));
void	inetprint __P((struct in_addr *, int, char *));
E 41
E 40
E 39

/*
 * Print a summary of connections related to an Internet
 * protocol.  For TCP, also give state of connection.
 * Listening processes (aflag) are suppressed unless the
 * -a (all) flag is specified.
 */
I 39
void
E 39
protopr(off, name)
D 42
	off_t off;
E 42
I 42
	u_long off;
E 42
	char *name;
{
	struct inpcb cb;
	register struct inpcb *prev, *next;
	int istcp;
I 25
	static int first = 1;
E 25

D 22
	if (off == 0) {
		printf("%s control block: symbol not in namelist\n", name);
E 22
I 22
	if (off == 0)
E 22
		return;
D 22
	}
E 22
	istcp = strcmp(name, "tcp") == 0;
D 38
	klseek(kmem, off, 0);
D 25
	read(kmem, &cb, sizeof (struct inpcb));
E 25
I 25
	read(kmem, (char *)&cb, sizeof (struct inpcb));
E 38
I 38
D 39
	kvm_read(off, (char *)&cb, sizeof (struct inpcb));
E 39
I 39
	kread(off, (char *)&cb, sizeof (struct inpcb));
E 39
E 38
E 25
	inpcb = cb;
	prev = (struct inpcb *)off;
D 22
	if (first) {
		printf("Active connections");
		if (aflag)
			printf(" (including servers)");
		putchar('\n');
		if (Aflag)
			printf("%-8.8s ", "PCB");
D 15
		printf("%-5.5s %-6.6s %-6.6s  %-18.18s %-18.18s %s\n",
E 15
I 15
D 18
		printf("%-5.5s %-6.6s %-6.6s  %-22.22s %-22.22s %s\n",
E 18
I 18
		printf(Aflag ? "%-5.5s %-6.6s %-6.6s  %-18.18s %-18.18s %s\n" :
			"%-5.5s %-6.6s %-6.6s  %-22.22s %-22.22s %s\n",
E 18
E 15
			"Proto", "Recv-Q", "Send-Q",
			"Local Address", "Foreign Address", "(state)");
		first = 0;
	}
E 22
I 22
	if (inpcb.inp_next == (struct inpcb *)off)
		return;
E 22
	while (inpcb.inp_next != (struct inpcb *)off) {
D 25
		char *cp;
E 25
D 39

E 39
		next = inpcb.inp_next;
D 38
		klseek(kmem, (off_t)next, 0);
D 25
		read(kmem, &inpcb, sizeof (inpcb));
E 25
I 25
		read(kmem, (char *)&inpcb, sizeof (inpcb));
E 38
I 38
D 39
		kvm_read((off_t)next, (char *)&inpcb, sizeof (inpcb));
E 39
I 39
D 42
		kread((off_t)next, (char *)&inpcb, sizeof (inpcb));
E 42
I 42
		kread((u_long)next, (char *)&inpcb, sizeof (inpcb));
E 42
E 39
E 38
E 25
		if (inpcb.inp_prev != prev) {
			printf("???\n");
			break;
		}
		if (!aflag &&
D 4
		  in_lnaof(inpcb.inp_laddr.s_addr) == INADDR_ANY) {
E 4
I 4
D 25
		  inet_lnaof(inpcb.inp_laddr.s_addr) == INADDR_ANY) {
E 25
I 25
		  inet_lnaof(inpcb.inp_laddr) == INADDR_ANY) {
E 25
E 4
			prev = next;
			continue;
		}
D 38
		klseek(kmem, (off_t)inpcb.inp_socket, 0);
D 19
		read(kmem, &socket, sizeof (socket));
E 19
I 19
D 25
		read(kmem, &sockb, sizeof (sockb));
E 25
I 25
		read(kmem, (char *)&sockb, sizeof (sockb));
E 38
I 38
D 39
		kvm_read((off_t)inpcb.inp_socket,
				(char *)&sockb, sizeof (sockb));
E 39
I 39
D 42
		kread((off_t)inpcb.inp_socket, (char *)&sockb, sizeof (sockb));
E 42
I 42
		kread((u_long)inpcb.inp_socket, (char *)&sockb, sizeof (sockb));
E 42
E 39
E 38
E 25
E 19
		if (istcp) {
D 38
			klseek(kmem, (off_t)inpcb.inp_ppcb, 0);
D 25
			read(kmem, &tcpcb, sizeof (tcpcb));
E 25
I 25
			read(kmem, (char *)&tcpcb, sizeof (tcpcb));
E 38
I 38
D 39
			kvm_read((off_t)inpcb.inp_ppcb,
				(char *)&tcpcb, sizeof (tcpcb));
E 39
I 39
D 42
			kread((off_t)inpcb.inp_ppcb,
E 42
I 42
			kread((u_long)inpcb.inp_ppcb,
E 42
			    (char *)&tcpcb, sizeof (tcpcb));
E 39
E 38
E 25
		}
I 22
		if (first) {
			printf("Active Internet connections");
			if (aflag)
				printf(" (including servers)");
			putchar('\n');
			if (Aflag)
				printf("%-8.8s ", "PCB");
			printf(Aflag ?
				"%-5.5s %-6.6s %-6.6s  %-18.18s %-18.18s %s\n" :
				"%-5.5s %-6.6s %-6.6s  %-22.22s %-22.22s %s\n",
				"Proto", "Recv-Q", "Send-Q",
				"Local Address", "Foreign Address", "(state)");
			first = 0;
		}
E 22
		if (Aflag)
D 22
			printf("%8x ", inpcb.inp_ppcb);
E 22
I 22
			if (istcp)
				printf("%8x ", inpcb.inp_ppcb);
			else
				printf("%8x ", next);
E 22
D 19
		printf("%-5.5s %6d %6d ", name, socket.so_rcv.sb_cc,
			socket.so_snd.sb_cc);
E 19
I 19
		printf("%-5.5s %6d %6d ", name, sockb.so_rcv.sb_cc,
			sockb.so_snd.sb_cc);
E 19
D 39
		inetprint(&inpcb.inp_laddr, inpcb.inp_lport, name);
		inetprint(&inpcb.inp_faddr, inpcb.inp_fport, name);
E 39
I 39
		inetprint(&inpcb.inp_laddr, (int)inpcb.inp_lport, name);
		inetprint(&inpcb.inp_faddr, (int)inpcb.inp_fport, name);
E 39
		if (istcp) {
			if (tcpcb.t_state < 0 || tcpcb.t_state >= TCP_NSTATES)
				printf(" %d", tcpcb.t_state);
			else
				printf(" %s", tcpstates[tcpcb.t_state]);
		}
		putchar('\n');
		prev = next;
	}
}

/*
I 6
 * Dump TCP statistics structure.
 */
I 39
void
E 39
tcp_stats(off, name)
D 42
	off_t off;
E 42
I 42
	u_long off;
E 42
	char *name;
{
	struct tcpstat tcpstat;

D 22
	if (off == 0) {
		printf("%sstat: symbol not in namelist\n", name);
E 22
I 22
	if (off == 0)
E 22
		return;
I 27
	printf ("%s:\n", name);
E 27
D 22
	}
E 22
D 38
	klseek(kmem, off, 0);
	read(kmem, (char *)&tcpstat, sizeof (tcpstat));
E 38
I 38
D 39
	kvm_read(off, (char *)&tcpstat, sizeof (tcpstat));
E 39
I 39
	kread(off, (char *)&tcpstat, sizeof (tcpstat));
E 39
E 38
D 12
	printf("%s:\n\t%d bad header checksums\n", name, tcpstat.tcps_badsum);
	printf("\t%d bad header offset fields\n", tcpstat.tcps_badoff);
	printf("\t%d incomplete headers\n", tcpstat.tcps_hdrops);
E 12
I 12
D 22
	printf("%s:\n\t%d bad header checksum%s\n", name,
E 22
I 22
D 26
	printf("%s:\n\t%d incomplete header%s\n", name,
E 26
I 26
D 27
	printf("%s:\n\t%u incomplete header%s\n", name,
E 26
		tcpstat.tcps_hdrops, plural(tcpstat.tcps_hdrops));
D 26
	printf("\t%d bad checksum%s\n",
E 26
I 26
	printf("\t%u bad checksum%s\n",
E 26
E 22
		tcpstat.tcps_badsum, plural(tcpstat.tcps_badsum));
D 26
	printf("\t%d bad header offset field%s\n",
E 26
I 26
	printf("\t%u bad header offset field%s\n",
E 26
		tcpstat.tcps_badoff, plural(tcpstat.tcps_badoff));
D 22
	printf("\t%d incomplete header%s\n",
		tcpstat.tcps_hdrops, plural(tcpstat.tcps_hdrops));
E 22
E 12
#ifdef notdef
D 12
	printf("\t%d bad segments\n", tcpstat.tcps_badsegs);
	printf("\t%d unacknowledged packets\n", tcpstat.tcps_unack);
E 12
I 12
D 26
	printf("\t%d bad segment%s\n",
E 26
I 26
	printf("\t%u bad segment%s\n",
E 26
		tcpstat.tcps_badsegs, plural(tcpstat.badsegs));
D 26
	printf("\t%d unacknowledged packet%s\n",
E 26
I 26
	printf("\t%u unacknowledged packet%s\n",
E 26
		tcpstat.tcps_unack, plural(tcpstat.tcps_unack));
E 12
#endif
E 27
I 27

D 31
#define p(f,m) printf("	m\n",tcpstat.tcps_/**/f,plural(tcpstat.tcps_/**/f))
#define p2(f1,f2,m) printf("	m\n",tcpstat.tcps_/**/f1,plural(tcpstat.tcps_/**/f1),tcpstat.tcps_/**/f2,plural(tcpstat.tcps_/**/f2))

	p(sndtotal,%d packet%s sent);
	p2(sndpack,sndbyte,\t%d data packet%s (%d byte%s));
	p2(sndrexmitpack,sndrexmitbyte,\t%d data packet%s (%d byte%s) retransmitted);
	p2(sndacks,delack,\t%d ack-only packet%s (%d delayed));
	p(sndurg,\t%d URG only packet%s);
	p(sndprobe,\t%d window probe packet%s);
	p(sndwinup,\t%d window update packet%s);
	p(sndctrl,\t%d control packet%s);

	p(rcvtotal,%d packet%s received);
	p2(rcvackpack,rcvackbyte,\t%d ack%s (for %d byte%s));
	p(rcvdupack,\t%d duplicate ack%s);
	p(rcvacktoomuch,\t%d ack%s for unsent data);
	p2(rcvpack,rcvbyte,\t%d packet%s (%d byte%s) received in-sequence);
	p2(rcvduppack,rcvdupbyte,\t%d completely duplicate packet%s (%d byte%s));
	p2(rcvpartduppack,rcvpartdupbyte,\t%d packet%s with some dup. data (%d byte%s duped));
	p2(rcvoopack,rcvoobyte,\t%d out-of-order packet%s (%d byte%s));
	p2(rcvpackafterwin,rcvbyteafterwin,\t%d packet%s (%d byte%s) of data after window);
	p(rcvwinprobe,\t%d window probe%s);
	p(rcvwinupd,\t%d window update packet%s);
	p(rcvafterclose,\t%d packet%s received after close);
	p(rcvbadsum,\t%d discarded for bad checksum%s);
	p(rcvbadoff,\t%d discarded for bad header offset field%s);
	p(rcvshort,\t%d discarded because packet too short);
	p(connattempt,%d connection request%s);
	p(accepts,%d connection accept%s);
	p(connects,%d connection%s established (including accepts));
	p2(closed,drops,%d connection%s closed (including %d drop%s));
	p(conndrops,%d embryonic connection%s dropped);
	p2(rttupdated,segstimed,%d segment%s updated rtt (of %d attempt%s));
	p(rexmttimeo,%d retransmit timeout%s);
	p(timeoutdrop,\t%d connection%s dropped by rexmit timeout);
	p(persisttimeo,%d persist timeout%s);
	p(keeptimeo,%d keepalive timeout%s);
	p(keepprobe,\t%d keepalive probe%s sent);
	p(keepdrops,\t%d connection%s dropped by keepalive);
E 31
I 31
D 39
#define	p(f, m)		printf(m, tcpstat.f, plural(tcpstat.f))
#define	p2(f1, f2, m)	printf(m, tcpstat.f1, plural(tcpstat.f1), tcpstat.f2, plural(tcpstat.f2))
  
E 39
I 39
#define	p(f, m) if (tcpstat.f || sflag <= 1) \
    printf(m, tcpstat.f, plural(tcpstat.f))
#define	p2(f1, f2, m) if (tcpstat.f1 || tcpstat.f2 || sflag <= 1) \
    printf(m, tcpstat.f1, plural(tcpstat.f1), tcpstat.f2, plural(tcpstat.f2))
I 46
#define	p3(f, m) if (tcpstat.f || sflag <= 1) \
    printf(m, tcpstat.f, plurales(tcpstat.f))
E 46

E 39
	p(tcps_sndtotal, "\t%d packet%s sent\n");
	p2(tcps_sndpack,tcps_sndbyte,
		"\t\t%d data packet%s (%d byte%s)\n");
	p2(tcps_sndrexmitpack, tcps_sndrexmitbyte,
		"\t\t%d data packet%s (%d byte%s) retransmitted\n");
	p2(tcps_sndacks, tcps_delack,
		"\t\t%d ack-only packet%s (%d delayed)\n");
	p(tcps_sndurg, "\t\t%d URG only packet%s\n");
	p(tcps_sndprobe, "\t\t%d window probe packet%s\n");
	p(tcps_sndwinup, "\t\t%d window update packet%s\n");
	p(tcps_sndctrl, "\t\t%d control packet%s\n");
	p(tcps_rcvtotal, "\t%d packet%s received\n");
	p2(tcps_rcvackpack, tcps_rcvackbyte, "\t\t%d ack%s (for %d byte%s)\n");
	p(tcps_rcvdupack, "\t\t%d duplicate ack%s\n");
	p(tcps_rcvacktoomuch, "\t\t%d ack%s for unsent data\n");
	p2(tcps_rcvpack, tcps_rcvbyte,
		"\t\t%d packet%s (%d byte%s) received in-sequence\n");
	p2(tcps_rcvduppack, tcps_rcvdupbyte,
		"\t\t%d completely duplicate packet%s (%d byte%s)\n");
I 43
	p(tcps_pawsdrop, "\t\t%d old duplicate packet%s\n");
E 43
	p2(tcps_rcvpartduppack, tcps_rcvpartdupbyte,
		"\t\t%d packet%s with some dup. data (%d byte%s duped)\n");
	p2(tcps_rcvoopack, tcps_rcvoobyte,
		"\t\t%d out-of-order packet%s (%d byte%s)\n");
	p2(tcps_rcvpackafterwin, tcps_rcvbyteafterwin,
		"\t\t%d packet%s (%d byte%s) of data after window\n");
	p(tcps_rcvwinprobe, "\t\t%d window probe%s\n");
	p(tcps_rcvwinupd, "\t\t%d window update packet%s\n");
	p(tcps_rcvafterclose, "\t\t%d packet%s received after close\n");
	p(tcps_rcvbadsum, "\t\t%d discarded for bad checksum%s\n");
	p(tcps_rcvbadoff, "\t\t%d discarded for bad header offset field%s\n");
	p(tcps_rcvshort, "\t\t%d discarded because packet too short\n");
	p(tcps_connattempt, "\t%d connection request%s\n");
	p(tcps_accepts, "\t%d connection accept%s\n");
I 48
	p(tcps_badsyn, "\t%d bad connection attempt%s\n");
E 48
	p(tcps_connects, "\t%d connection%s established (including accepts)\n");
	p2(tcps_closed, tcps_drops,
		"\t%d connection%s closed (including %d drop%s)\n");
	p(tcps_conndrops, "\t%d embryonic connection%s dropped\n");
	p2(tcps_rttupdated, tcps_segstimed,
		"\t%d segment%s updated rtt (of %d attempt%s)\n");
	p(tcps_rexmttimeo, "\t%d retransmit timeout%s\n");
	p(tcps_timeoutdrop, "\t\t%d connection%s dropped by rexmit timeout\n");
	p(tcps_persisttimeo, "\t%d persist timeout%s\n");
I 48
	p(tcps_persistdrop, "\t%d connection%s timed out in persist\n");
E 48
	p(tcps_keeptimeo, "\t%d keepalive timeout%s\n");
	p(tcps_keepprobe, "\t\t%d keepalive probe%s sent\n");
	p(tcps_keepdrops, "\t\t%d connection%s dropped by keepalive\n");
I 46
	p(tcps_predack, "\t%d correct ACK header prediction%s\n");
D 47
	p(tcps_predack, "\t%d correct data packet header prediction%s\n");
	p3(tcps_pcbcachemiss, "\t%d cache miss%s\n");
E 47
I 47
	p(tcps_preddat, "\t%d correct data packet header prediction%s\n");
	p3(tcps_pcbcachemiss, "\t%d PCB cache miss%s\n");
E 47
E 46
E 31
#undef p
#undef p2
I 46
#undef p3
E 46
E 27
}

/*
 * Dump UDP statistics structure.
 */
I 39
void
E 39
udp_stats(off, name)
D 42
	off_t off;
E 42
I 42
	u_long off;
E 42
	char *name;
{
	struct udpstat udpstat;
I 43
	u_long delivered;
E 43

D 22
	if (off == 0) {
		printf("%sstat: symbol not in namelist\n", name);
E 22
I 22
	if (off == 0)
E 22
		return;
D 22
	}
E 22
D 38
	klseek(kmem, off, 0);
	read(kmem, (char *)&udpstat, sizeof (udpstat));
E 38
I 38
D 39
	kvm_read(off, (char *)&udpstat, sizeof (udpstat));
E 38
D 12
	printf("%s:\n\t%d bad header checksums\n", name, udpstat.udps_badsum);
	printf("\t%d incomplete headers\n", udpstat.udps_hdrops);
	printf("\t%d bad data length fields\n", udpstat.udps_badlen);
E 12
I 12
D 22
	printf("%s:\n\t%d bad header checksum%s\n", name,
		udpstat.udps_badsum, plural(udpstat.udps_badsum));
	printf("\t%d incomplete header%s\n",
E 22
I 22
D 26
	printf("%s:\n\t%d incomplete header%s\n", name,
E 26
I 26
	printf("%s:\n\t%u incomplete header%s\n", name,
E 26
E 22
		udpstat.udps_hdrops, plural(udpstat.udps_hdrops));
D 26
	printf("\t%d bad data length field%s\n",
E 26
I 26
	printf("\t%u bad data length field%s\n",
E 26
		udpstat.udps_badlen, plural(udpstat.udps_badlen));
I 22
D 26
	printf("\t%d bad checksum%s\n",
E 26
I 26
	printf("\t%u bad checksum%s\n",
E 26
		udpstat.udps_badsum, plural(udpstat.udps_badsum));
E 39
I 39
	kread(off, (char *)&udpstat, sizeof (udpstat));
	printf("%s:\n", name);
#define	p(f, m) if (udpstat.f || sflag <= 1) \
    printf(m, udpstat.f, plural(udpstat.f))
D 43
	p(udps_hdrops, "\t%u incomplete header%s\n");
	p(udps_badlen, "\t%u bad data length field%s\n");
	p(udps_badsum, "\t%u bad checksum%s\n");
	p(udps_noport, "\t%u no port%s\n");
	p(udps_noportbcast, "\t%u (arrived as bcast) no port%s\n");
E 43
I 43
	p(udps_ipackets, "\t%u datagram%s received\n");
	p(udps_hdrops, "\t%u with incomplete header\n");
	p(udps_badlen, "\t%u with bad data length field\n");
	p(udps_badsum, "\t%u with bad checksum\n");
	p(udps_noport, "\t%u dropped due to no socket\n");
	p(udps_noportbcast, "\t%u broadcast/multicast datagram%s dropped due to no socket\n");
	p(udps_fullsock, "\t%u dropped due to full socket buffers\n");
	delivered = udpstat.udps_ipackets -
		    udpstat.udps_hdrops -
		    udpstat.udps_badlen -
		    udpstat.udps_badsum -
		    udpstat.udps_noport -
		    udpstat.udps_noportbcast -
		    udpstat.udps_fullsock;
	if (delivered || sflag <= 1)
		printf("\t%u delivered\n", delivered);
	p(udps_opackets, "\t%u datagram%s output\n");
E 43
#undef p
E 39
I 32
#ifdef sun
	printf("\t%d socket overflow%s\n",
		udpstat.udps_fullsock, plural(udpstat.udps_fullsock));
#endif
E 32
E 22
E 12
}

/*
 * Dump IP statistics structure.
 */
I 39
void
E 39
ip_stats(off, name)
D 42
	off_t off;
E 42
I 42
	u_long off;
E 42
	char *name;
{
	struct ipstat ipstat;

D 22
	if (off == 0) {
		printf("%sstat: symbol not in namelist\n", name);
E 22
I 22
	if (off == 0)
E 22
		return;
D 22
	}
E 22
D 38
	klseek(kmem, off, 0);
	read(kmem, (char *)&ipstat, sizeof (ipstat));
E 38
I 38
D 39
	kvm_read(off, (char *)&ipstat, sizeof (ipstat));
E 38
I 32
#if BSD>=43
E 32
D 12
	printf("%s:\n\t%d bad header checksums\n", name, ipstat.ips_badsum);
D 8
	printf("\t%d incomplete packets\n", ipstat.ips_tooshort);
E 8
I 8
	printf("\t%d packet size smaller than minimum\n",
		ipstat.ips_tooshort);
	printf("\t%d data size < data length\n", ipstat.ips_toosmall);
	printf("\t%d header length < data size\n", ipstat.ips_badhlen);
	printf("\t%d data length < header length\n", ipstat.ips_badlen);
E 12
I 12
D 22
	printf("%s:\n\t%d bad header checksum%s\n", name,
E 22
I 22
D 26
	printf("%s:\n\t%d total packets received\n", name,
E 26
I 26
	printf("%s:\n\t%u total packets received\n", name,
E 26
		ipstat.ips_total);
I 32
#endif
E 32
D 26
	printf("\t%d bad header checksum%s\n",
E 26
I 26
	printf("\t%u bad header checksum%s\n",
E 26
E 22
		ipstat.ips_badsum, plural(ipstat.ips_badsum));
D 26
	printf("\t%d with size smaller than minimum\n", ipstat.ips_tooshort);
	printf("\t%d with data size < data length\n", ipstat.ips_toosmall);
	printf("\t%d with header length < data size\n", ipstat.ips_badhlen);
	printf("\t%d with data length < header length\n", ipstat.ips_badlen);
I 22
	printf("\t%d fragment%s received\n",
E 26
I 26
	printf("\t%u with size smaller than minimum\n", ipstat.ips_tooshort);
	printf("\t%u with data size < data length\n", ipstat.ips_toosmall);
	printf("\t%u with header length < data size\n", ipstat.ips_badhlen);
	printf("\t%u with data length < header length\n", ipstat.ips_badlen);
I 32
#if BSD>=43
E 32
	printf("\t%u fragment%s received\n",
E 26
		ipstat.ips_fragments, plural(ipstat.ips_fragments));
D 26
	printf("\t%d fragment%s dropped (dup or out of space)\n",
E 26
I 26
	printf("\t%u fragment%s dropped (dup or out of space)\n",
E 26
		ipstat.ips_fragdropped, plural(ipstat.ips_fragdropped));
D 26
	printf("\t%d fragment%s dropped after timeout\n",
E 26
I 26
	printf("\t%u fragment%s dropped after timeout\n",
E 26
		ipstat.ips_fragtimeout, plural(ipstat.ips_fragtimeout));
D 26
	printf("\t%d packet%s forwarded\n",
E 26
I 26
	printf("\t%u packet%s forwarded\n",
E 26
		ipstat.ips_forward, plural(ipstat.ips_forward));
D 26
	printf("\t%d packet%s not forwardable\n",
E 26
I 26
	printf("\t%u packet%s not forwardable\n",
E 26
		ipstat.ips_cantforward, plural(ipstat.ips_cantforward));
D 26
	printf("\t%d redirect%s sent\n",
E 26
I 26
	printf("\t%u redirect%s sent\n",
E 26
		ipstat.ips_redirectsent, plural(ipstat.ips_redirectsent));
E 39
I 39
	kread(off, (char *)&ipstat, sizeof (ipstat));
	printf("%s:\n", name);

#define	p(f, m) if (ipstat.f || sflag <= 1) \
    printf(m, ipstat.f, plural(ipstat.f))

	p(ips_total, "\t%u total packet%s received\n");
	p(ips_badsum, "\t%u bad header checksum%s\n");
D 45
	p(ips_tooshort, "\t%u with size smaller than minimum\n");
	p(ips_toosmall, "\t%u with data size < data length\n");
E 45
I 45
	p(ips_toosmall, "\t%u with size smaller than minimum\n");
	p(ips_tooshort, "\t%u with data size < data length\n");
E 45
	p(ips_badhlen, "\t%u with header length < data size\n");
	p(ips_badlen, "\t%u with data length < header length\n");
I 43
	p(ips_badoptions, "\t%u with bad options\n");
	p(ips_badvers, "\t%u with incorrect version number\n");
E 43
	p(ips_fragments, "\t%u fragment%s received\n");
	p(ips_fragdropped, "\t%u fragment%s dropped (dup or out of space)\n");
	p(ips_fragtimeout, "\t%u fragment%s dropped after timeout\n");
I 43
	p(ips_reassembled, "\t%u packet%s reassembled ok\n");
	p(ips_delivered, "\t%u packet%s for this host\n");
	p(ips_noproto, "\t%u packet%s for unknown/unsupported protocol\n");
E 43
	p(ips_forward, "\t%u packet%s forwarded\n");
	p(ips_cantforward, "\t%u packet%s not forwardable\n");
	p(ips_redirectsent, "\t%u redirect%s sent\n");
I 43
	p(ips_localout, "\t%u packet%s sent from this host\n");
	p(ips_rawout, "\t%u packet%s sent with fabricated ip header\n");
	p(ips_odropped, "\t%u output packet%s dropped due to no bufs, etc.\n");
	p(ips_noroute, "\t%u output packet%s discarded due to no route\n");
	p(ips_fragmented, "\t%u output datagram%s fragmented\n");
	p(ips_ofragments, "\t%u fragment%s created\n");
	p(ips_cantfrag, "\t%u datagram%s that can't be fragmented\n");
E 43
#undef p
E 39
I 32
#endif
E 32
E 22
E 12
I 9
}

static	char *icmpnames[] = {
	"echo reply",
	"#1",
	"#2",
	"destination unreachable",
	"source quench",
	"routing redirect",
	"#6",
	"#7",
	"echo",
	"#9",
	"#10",
	"time exceeded",
	"parameter problem",
	"time stamp",
	"time stamp reply",
	"information request",
D 22
	"information request reply"
E 22
I 22
	"information request reply",
	"address mask request",
	"address mask reply",
E 22
};

/*
 * Dump ICMP statistics.
 */
I 39
void
E 39
icmp_stats(off, name)
D 42
	off_t off;
E 42
I 42
	u_long off;
E 42
	char *name;
{
	struct icmpstat icmpstat;
	register int i, first;

D 22
	if (off == 0) {
		printf("%sstat: symbol not in namelist\n", name);
E 22
I 22
	if (off == 0)
E 22
		return;
D 22
	}
E 22
D 38
	klseek(kmem, off, 0);
	read(kmem, (char *)&icmpstat, sizeof (icmpstat));
E 38
I 38
D 39
	kvm_read(off, (char *)&icmpstat, sizeof (icmpstat));
E 38
D 12
	printf("%s:\n\t%d calls to icmp_error\n", name, icmpstat.icps_error);
	printf("\t%d errors not generated 'cuz old message too short\n",
		icmpstat.icps_oldshort);
	printf("\t%d errors not generated 'cuz old message was icmp\n",
		icmpstat.icps_oldicmp);
E 12
I 12
D 26
	printf("%s:\n\t%d call%s to icmp_error\n", name,
E 26
I 26
	printf("%s:\n\t%u call%s to icmp_error\n", name,
E 26
		icmpstat.icps_error, plural(icmpstat.icps_error));
D 22
	printf("\t%d error%s not generated 'cuz old message too short\n",
		icmpstat.icps_oldshort, plural(icmpstat.icps_oldshort));
E 22
D 26
	printf("\t%d error%s not generated 'cuz old message was icmp\n",
E 26
I 26
	printf("\t%u error%s not generated 'cuz old message was icmp\n",
E 26
		icmpstat.icps_oldicmp, plural(icmpstat.icps_oldicmp));
E 39
I 39
	kread(off, (char *)&icmpstat, sizeof (icmpstat));
	printf("%s:\n", name);

#define	p(f, m) if (icmpstat.f || sflag <= 1) \
    printf(m, icmpstat.f, plural(icmpstat.f))

	p(icps_error, "\t%u call%s to icmp_error\n");
	p(icps_oldicmp,
	    "\t%u error%s not generated 'cuz old message was icmp\n");
E 39
E 12
D 10
	for (first = 0, i = 0; i < ICMP_IREQREPLY + 1; i++)
E 10
I 10
D 30
	for (first = 1, i = 0; i < ICMP_IREQREPLY + 1; i++)
E 30
I 30
	for (first = 1, i = 0; i < ICMP_MAXTYPE + 1; i++)
E 30
E 10
		if (icmpstat.icps_outhist[i] != 0) {
			if (first) {
				printf("\tOutput histogram:\n");
				first = 0;
			}
D 26
			printf("\t\t%s: %d\n", icmpnames[i],
E 26
I 26
			printf("\t\t%s: %u\n", icmpnames[i],
E 26
				icmpstat.icps_outhist[i]);
		}
I 14
D 26
	printf("\t%d message%s with bad code fields\n",
E 26
I 26
D 39
	printf("\t%u message%s with bad code fields\n",
E 26
		icmpstat.icps_badcode, plural(icmpstat.icps_badcode));
E 14
D 12
	printf("\t%d messages < minimum length\n", icmpstat.icps_tooshort);
	printf("\t%d bad checksums\n", icmpstat.icps_checksum);
	printf("\t%d messages with bad length\n", icmpstat.icps_badlen);
D 10
	printf("\t%d messages respondes generated\n", icmpstat.icps_reflect);
	for (first = 0, i = 0; i < ICMP_IREQREPLY + 1; i++)
E 10
I 10
D 11
	printf("\t%d messages responses generated\n", icmpstat.icps_reflect);
E 11
I 11
	printf("\t%d message responses generated\n", icmpstat.icps_reflect);
E 12
I 12
D 26
	printf("\t%d message%s < minimum length\n",
E 26
I 26
	printf("\t%u message%s < minimum length\n",
E 26
		icmpstat.icps_tooshort, plural(icmpstat.icps_tooshort));
D 13
	printf("\t%d bad checksum%s\n", icmpstat.icps_checksum);
E 13
I 13
D 26
	printf("\t%d bad checksum%s\n",
E 26
I 26
	printf("\t%u bad checksum%s\n",
E 26
		icmpstat.icps_checksum, plural(icmpstat.icps_checksum));
E 13
D 26
	printf("\t%d message%s with bad length\n",
E 26
I 26
	printf("\t%u message%s with bad length\n",
E 26
		icmpstat.icps_badlen, plural(icmpstat.icps_badlen));
E 39
I 39
	p(icps_badcode, "\t%u message%s with bad code fields\n");
	p(icps_tooshort, "\t%u message%s < minimum length\n");
	p(icps_checksum, "\t%u bad checksum%s\n");
	p(icps_badlen, "\t%u message%s with bad length\n");
E 39
D 22
	printf("\t%d message response%s generated\n",
		icmpstat.icps_reflect, plural(icmpstat.icps_reflect));
E 22
E 12
E 11
D 30
	for (first = 1, i = 0; i < ICMP_IREQREPLY + 1; i++)
E 30
I 30
	for (first = 1, i = 0; i < ICMP_MAXTYPE + 1; i++)
E 30
E 10
		if (icmpstat.icps_inhist[i] != 0) {
			if (first) {
				printf("\tInput histogram:\n");
				first = 0;
			}
D 26
			printf("\t\t%s: %d\n", icmpnames[i],
E 26
I 26
			printf("\t\t%s: %u\n", icmpnames[i],
E 26
				icmpstat.icps_inhist[i]);
		}
I 22
D 26
	printf("\t%d message response%s generated\n",
E 26
I 26
D 39
	printf("\t%u message response%s generated\n",
E 26
		icmpstat.icps_reflect, plural(icmpstat.icps_reflect));
E 39
I 39
	p(icps_reflect, "\t%u message response%s generated\n");
#undef p
I 43
}

/*
 * Dump IGMP statistics structure.
 */
void
igmp_stats(off, name)
	u_long off;
	char *name;
{
	struct igmpstat igmpstat;

	if (off == 0)
		return;
	kread(off, (char *)&igmpstat, sizeof (igmpstat));
	printf("%s:\n", name);

#define	p(f, m) if (igmpstat.f || sflag <= 1) \
    printf(m, igmpstat.f, plural(igmpstat.f))
#define	py(f, m) if (igmpstat.f || sflag <= 1) \
    printf(m, igmpstat.f, igmpstat.f != 1 ? "ies" : "y")
	p(igps_rcv_total, "\t%u message%s received\n");
        p(igps_rcv_tooshort, "\t%u message%s received with too few bytes\n");
        p(igps_rcv_badsum, "\t%u message%s received with bad checksum\n");
        py(igps_rcv_queries, "\t%u membership quer%s received\n");
        py(igps_rcv_badqueries, "\t%u membership quer%s received with invalid field(s)\n");
        p(igps_rcv_reports, "\t%u membership report%s received\n");
        p(igps_rcv_badreports, "\t%u membership report%s received with invalid field(s)\n");
        p(igps_rcv_ourreports, "\t%u membership report%s received for groups to which we belong\n");
        p(igps_snd_reports, "\t%u membership report%s sent\n");
#undef p
#undef py
E 43
E 39
E 22
E 9
E 8
}

/*
E 6
 * Pretty print an Internet address (net address + port).
 * If the nflag was specified, use numbers instead of names.
 */
I 39
D 40
static void
E 40
I 40
void
E 40
E 39
inetprint(in, port, proto)
	register struct in_addr *in;
D 25
	int port;
E 25
I 25
D 39
	u_short port; 
E 39
I 39
	int port;
E 39
E 25
	char *proto;
{
	struct servent *sp = 0;
D 39
	char line[80], *cp, *index();
E 39
I 39
	char line[80], *cp;
E 39
I 18
	int width;
E 18

D 15
	sprintf(line, "%.10s.", inetname(*in));
E 15
I 15
D 18
	sprintf(line, "%.16s.", inetname(*in));
E 18
I 18
D 24
	sprintf(line, "%.*s.", Aflag ? 10 : 16, inetname(*in));
E 24
I 24
D 39
	sprintf(line, "%.*s.", (Aflag && !nflag) ? 12 : 16, inetname(*in));
E 39
I 39
	sprintf(line, "%.*s.", (Aflag && !nflag) ? 12 : 16, inetname(in));
E 39
E 24
E 18
E 15
	cp = index(line, '\0');
D 7
#if vax || pdp11
	port = ntohs((u_short)port);
#endif
E 7
	if (!nflag && port)
D 2
		sp = getservport(port, proto);
E 2
I 2
D 25
		sp = getservbyport(port, proto);
E 25
I 25
		sp = getservbyport((int)port, proto);
E 25
E 2
	if (sp || port == 0)
		sprintf(cp, "%.8s", sp ? sp->s_name : "*");
	else
D 7
		sprintf(cp, "%d", port);
E 7
I 7
		sprintf(cp, "%d", ntohs((u_short)port));
E 7
D 15
	printf(" %-18.18s", line);
E 15
I 15
D 18
	printf(" %-22.22s", line);
E 18
I 18
	width = Aflag ? 18 : 22;
	printf(" %-*.*s", width, width, line);
E 18
E 15
}

/*
D 4
 * Return the network number from an internet
 * address; handles class a/b/c network #'s.
 */
in_netof(in)
	struct in_addr in;
{
#if vax || pdp11
	register u_long net;

	if ((in.s_addr&IN_CLASSA) == 0)
		return (in.s_addr & IN_CLASSA_NET);
	if ((in.s_addr&IN_CLASSB) == 0)
		return ((int)htons((u_short)(in.s_addr & IN_CLASSB_NET)));
	net = htonl((u_long)(in.s_addr & IN_CLASSC_NET));
	net >>= 8;
	return ((int)net);
#else
	return (IN_NETOF(in));
#endif
}

/*
 * Return the local network address portion of an
 * internet address; handles class a/b/c network
 * number formats.
 */
in_lnaof(in)
	struct in_addr in;
{
#if vax || pdp11
#define	IN_LNAOF(in) \
	(((in).s_addr&IN_CLASSA) == 0 ? (in).s_addr&IN_CLASSA_LNA : \
		((in).s_addr&IN_CLASSB) == 0 ? (in).s_addr&IN_CLASSB_LNA : \
			(in).s_addr&IN_CLASSC_LNA)
	return ((int)htonl((u_long)IN_LNAOF(in)));
#else
	return (IN_LNAOF(in));
#endif
}

/*
E 4
 * Construct an Internet address representation.
D 39
 * If the nflag has been supplied, give 
E 39
I 39
 * If the nflag has been supplied, give
E 39
 * numeric value, otherwise try for symbolic name.
 */
D 39
char *
inetname(in)
	struct in_addr in;
E 39
I 39
D 40
static char *
E 40
I 40
char *
E 40
inetname(inp)
	struct in_addr *inp;
E 39
{
D 23
	char *cp = 0;
E 23
I 23
	register char *cp;
E 23
	static char line[50];
I 16
	struct hostent *hp;
	struct netent *np;
I 23
	static char domain[MAXHOSTNAMELEN + 1];
	static int first = 1;
E 23
E 16

I 23
	if (first && !nflag) {
		first = 0;
		if (gethostname(domain, MAXHOSTNAMELEN) == 0 &&
		    (cp = index(domain, '.')))
			(void) strcpy(domain, cp + 1);
		else
			domain[0] = 0;
	}
	cp = 0;
E 23
D 17
	if (!nflag) {
E 17
I 17
D 39
	if (!nflag && in.s_addr != INADDR_ANY) {
E 17
D 4
		if (in_lnaof(in) == INADDR_ANY) {
D 2
			struct netent *np = getnetaddr(in_netof(in));
E 2
I 2
D 3
			struct netent *np = getnetbyaddr(in_netof(in));
E 3
I 3
			struct netent *np = getnetbyaddr(in_netof(in), AF_INET);
E 4
I 4
D 15
		if (inet_lnaof(in) == INADDR_ANY) {
			struct netent *np;
E 4
E 3
E 2

I 4
			np = getnetbyaddr(inet_netof(in), AF_INET);
E 15
I 15
D 16
		struct netent *np;
E 16
D 19
		int net = inet_netof(in), subnet = inet_subnetof(in);
E 19
I 19
		int net = inet_netof(in);
E 19
D 16
		if (subnet != net && (np = getnetbyaddr(subnet, AF_INET)))
			cp = np->n_name;
		else if (inet_lnaof(in) == INADDR_ANY) {
E 16
I 16
		int lna = inet_lnaof(in);
E 39
I 39
	if (!nflag && inp->s_addr != INADDR_ANY) {
		int net = inet_netof(*inp);
		int lna = inet_lnaof(*inp);
E 39
I 17

E 17
		if (lna == INADDR_ANY) {
E 16
			np = getnetbyaddr(net, AF_INET);
E 15
E 4
			if (np)
				cp = np->n_name;
I 16
D 17
		} else if ((subnet != net) && ((lna & 0xff) == 0) &&
E 17
I 17
D 19
		} else if (subnet != net && (lna & 0xff) == 0 &&
E 17
		    (np = getnetbyaddr(subnet, AF_INET))) {
			struct in_addr subnaddr, inet_makeaddr();
I 17

E 17
			subnaddr = inet_makeaddr(subnet, INADDR_ANY);
D 17
			if (bcmp(&in, &subnaddr, sizeof(in)) == 0)
E 17
I 17
			if (bcmp(&in, &subnaddr, sizeof (in)) == 0)
E 17
				cp = np->n_name;
			else
				goto host;
E 16
		} else {
D 2
			struct hostent *hp = gethostaddr(in.s_addr);
E 2
I 2
D 16
			struct hostent *hp;
E 16
I 16
host:
E 19
I 19
		}
		if (cp == 0) {
E 19
E 16
E 2
D 15

E 15
I 2
D 3
			hp = gethostbyaddr(&in, sizeof (struct in_addr));
E 3
I 3
D 17
			hp = gethostbyaddr(&in, sizeof (struct in_addr),
				AF_INET);
E 17
I 17
D 25
			hp = gethostbyaddr(&in, sizeof (in), AF_INET);
E 25
I 25
D 39
			hp = gethostbyaddr((char *)&in, sizeof (in), AF_INET);
E 39
I 39
			hp = gethostbyaddr((char *)inp, sizeof (*inp), AF_INET);
E 39
E 25
E 17
E 3
E 2
D 23
			if (hp)
E 23
I 23
			if (hp) {
				if ((cp = index(hp->h_name, '.')) &&
				    !strcmp(cp + 1, domain))
					*cp = 0;
E 23
				cp = hp->h_name;
I 23
			}
E 23
		}
	}
D 39
	if (in.s_addr == INADDR_ANY)
E 39
I 39
	if (inp->s_addr == INADDR_ANY)
E 39
		strcpy(line, "*");
	else if (cp)
		strcpy(line, cp);
	else {
D 19
		u_char *ucp = (u_char *)&in;
I 17

E 17
		sprintf(line, "%u.%u.%u.%u", ucp[0], ucp[1], ucp[2], ucp[3]);
E 19
I 19
D 39
		in.s_addr = ntohl(in.s_addr);
E 39
I 39
		inp->s_addr = ntohl(inp->s_addr);
E 39
#define C(x)	((x) & 0xff)
D 39
		sprintf(line, "%u.%u.%u.%u", C(in.s_addr >> 24),
			C(in.s_addr >> 16), C(in.s_addr >> 8), C(in.s_addr));
E 39
I 39
		sprintf(line, "%u.%u.%u.%u", C(inp->s_addr >> 24),
		    C(inp->s_addr >> 16), C(inp->s_addr >> 8), C(inp->s_addr));
E 39
E 19
	}
	return (line);
}
E 1
