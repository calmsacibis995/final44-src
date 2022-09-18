h28575
s 00002/00002/00814
d D 8.1 93/06/06 15:43:47 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00815
d D 5.14 92/07/14 09:51:25 bostic 14 13
c don't include .c files, this breaks if /usr/include is a copy!
e
s 00015/00015/00801
d D 5.13 92/07/07 16:57:17 sklower 13 12
c not every value return in an nlist structure was being
c coerced to an (off_t) which was only being smashed back down to a (u_long)
c as an argument to kvm_read.  If you ask me nl.n_value ought to be a (void *)
c but since the type of nl.n_value and the second argument to kvm_read are
c the same I got fed up and changed all the off_t's to be that type (u_long).
e
s 00031/00020/00785
d D 5.12 92/07/06 15:36:14 sklower 12 11
c Multicast changes from lbl
e
s 00000/00000/00805
d D 5.11 92/05/27 18:11:49 sklower 11 10
c incorporate changes for new kvm interfaces from lbl
e
s 00114/00058/00691
d D 5.10 92/05/13 19:34:58 sklower 10 9
c really merged version of my stuff & leres
e
s 00006/00016/00743
d D 5.9 92/05/13 19:24:27 sklower 9 8
c minor other leres-like changes but this branch didn't include 5.7
e
s 00147/00154/00612
d D 5.8 92/04/24 16:33:09 sklower 8 7
c mark changes made by leres@lbl
e
s 00108/00089/00658
d D 5.7 92/01/27 14:30:33 sklower 7 6
c change manner of locating tp pcb's
e
s 00000/00001/00747
d D 5.6 91/04/27 17:06:03 bostic 6 5
c  ANSI fixes; iso.c compiled without the #define KERNEL
e
s 00011/00007/00737
d D 5.5 91/04/18 16:25:02 bostic 5 4
c new copyright; att/bsd/shared
e
s 00007/00015/00737
d D 5.4 90/06/18 17:20:34 sklower 4 3
c use kvm_nlist to avoid numerous lseeks of nlist; use kvm_read to avoid duplication.
e
s 00002/00002/00750
d D 5.3 90/05/01 15:14:40 sklower 3 2
c consistent with new includes
e
s 00066/00027/00686
d D 5.2 90/04/07 16:16:11 sklower 2 1
c add cltp stats; print out (co)tp stats only when on top of clnp
c rather than printing out underlying IP sockaddrs incorrectly.
e
s 00713/00000/00000
d D 5.1 89/09/25 15:48:34 karels 1 0
c date and time created 89/09/25 15:48:34 by karels
e
u
U
t
T
I 1
D 5
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
D 12
/*-
 * Copyright (c) 1989, 1990 The Regents of the University of California.
E 12
I 12
/*
D 15
 * Copyright (c) 1983, 1988 Regents of the University of California.
E 12
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1983, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
 * %sccs.include.redist.c%
E 5
 */

I 5
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 5
/*
D 12
 * $Header: iso.c,v 3.3 88/12/08 14:44:49 hagens Exp $
 * $Source: /usr/argo/src/ucb/netstat/RCS/iso.c,v $
E 12
I 12
 * $Header: iso.c,v 1.5 92/06/04 00:36:32 leres Exp $
 * $Source: /usr/src/usr.bin/netstat/RCS/iso.c,v $
E 12
 */
/*******************************************************************************
D 5
		          Copyright IBM Corporation 1987
E 5
I 5
	          Copyright IBM Corporation 1987
E 5

                      All Rights Reserved

D 8
Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
E 8
I 8
Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
E 8
provided that the above copyright notice appear in all copies and that
D 8
both that copyright notice and this permission notice appear in 
E 8
I 8
both that copyright notice and this permission notice appear in
E 8
supporting documentation, and that the name of IBM not be
used in advertising or publicity pertaining to distribution of the
D 8
software without specific, written prior permission.  
E 8
I 8
software without specific, written prior permission.
E 8

IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

*******************************************************************************/

/*
D 5
 *	ARGO Project, Computer Sciences Dept., University of Wisconsin - Madison
E 5
I 5
 * ARGO Project, Computer Sciences Dept., University of Wisconsin - Madison
E 5
 */
D 5
static char sccsid[] = "%W% (Berkeley) %G%";
E 5

#include <sys/param.h>
#include <sys/mbuf.h>
I 3
D 6
#define KERNEL
E 6
E 3
#include <sys/time.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <errno.h>
#include <net/if.h>
#include <net/route.h>
I 10
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/in_pcb.h>
#include <netinet/ip_var.h>
E 10
I 7
D 8
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/in_pcb.h>
#include <netinet/ip_var.h>
E 8
E 7
#include <netiso/iso.h>
#include <netiso/iso_errno.h>
#include <netiso/clnp.h>
I 2
D 3
#include <netiso/cltp_var.h>
E 3
E 2
#include <netiso/esis.h>
#include <netiso/clnp_stat.h>
#include <netiso/argo_debug.h>
#undef satosiso
#include <netiso/tp_param.h>
#include <netiso/tp_states.h>
D 14
#include <netiso/tp_astring.c>
E 14
D 3
#define KERNEL
E 3
#include <netiso/tp_pcb.h>
#include <netiso/tp_stat.h>
#include <netiso/iso_pcb.h>
I 3
#include <netiso/cltp_var.h>
E 3
#include <netiso/cons.h>
#ifdef IncStat
#undef IncStat
#endif
#include <netiso/cons_pcb.h>
I 12
#include <arpa/inet.h>
E 12
#include <netdb.h>
I 8
#include <string.h>
#include <stdio.h>
I 12
#include <stdlib.h>
E 12
#include "netstat.h"
E 8

I 8
static void tprintstat __P((struct tp_stat *, int));
static void isonetprint __P((struct sockaddr_iso *, int));
static void hexprint __P((int, char *, char *));
I 12
extern void inetprint __P((struct in_addr *, int, char *));
E 12
E 8
D 4
extern	int kmem;
E 4

/*
 *	Dump esis stats
 */
I 8
void
E 8
esis_stats(off, name)
D 13
	off_t	off;
E 13
I 13
	u_long	off;
E 13
	char	*name;
{
	struct esis_stat esis_stat;

D 8
	if (off == 0)
E 8
I 8
	if (off == 0 ||
	    kread(off, (char *)&esis_stat, sizeof (struct esis_stat)))
E 8
		return;
D 4
	klseek(kmem, off, 0);
	read(kmem, (char *)&esis_stat, sizeof (struct esis_stat));
E 4
I 4
D 8
	kvm_read(off, (char *)&esis_stat, sizeof (struct esis_stat));
E 8
E 4
	printf("%s:\n", name);
	printf("\t%d esh sent, %d esh received\n", esis_stat.es_eshsent,
		esis_stat.es_eshrcvd);
	printf("\t%d ish sent, %d ish received\n", esis_stat.es_ishsent,
		esis_stat.es_ishrcvd);
	printf("\t%d rd sent, %d rd received\n", esis_stat.es_rdsent,
		esis_stat.es_rdrcvd);
D 8
	printf("\t%d pdus not sent due to insufficient memory\n", 
E 8
I 8
	printf("\t%d pdus not sent due to insufficient memory\n",
E 8
		esis_stat.es_nomem);
	printf("\t%d pdus received with bad checksum\n", esis_stat.es_badcsum);
D 8
	printf("\t%d pdus received with bad version number\n", 
E 8
I 8
	printf("\t%d pdus received with bad version number\n",
E 8
		esis_stat.es_badvers);
	printf("\t%d pdus received with bad type field\n", esis_stat.es_badtype);
	printf("\t%d short pdus received\n", esis_stat.es_toosmall);
}

/*
 * Dump clnp statistics structure.
 */
I 8
void
E 8
clnp_stats(off, name)
D 13
	off_t off;
E 13
I 13
	u_long off;
E 13
	char *name;
{
	struct clnp_stat clnp_stat;

D 8
	if (off == 0)
E 8
I 8
	if (off == 0 ||
	    kread(off, (char *)&clnp_stat, sizeof (clnp_stat)))
E 8
		return;
D 4
	klseek(kmem, off, 0);
	read(kmem, (char *)&clnp_stat, sizeof (clnp_stat));
E 4
I 4
D 8
	kvm_read(off, (char *)&clnp_stat, sizeof (clnp_stat));
E 8
E 4

	printf("%s:\n\t%d total packets sent\n", name, clnp_stat.cns_sent);
	printf("\t%d total fragments sent\n", clnp_stat.cns_fragments);
	printf("\t%d total packets received\n", clnp_stat.cns_total);
D 8
	printf("\t%d with fixed part of header too small\n", 
E 8
I 8
	printf("\t%d with fixed part of header too small\n",
E 8
		clnp_stat.cns_toosmall);
	printf("\t%d with header length not reasonable\n", clnp_stat.cns_badhlen);
D 8
	printf("\t%d incorrect checksum%s\n", 
E 8
I 8
	printf("\t%d incorrect checksum%s\n",
E 8
		clnp_stat.cns_badcsum, plural(clnp_stat.cns_badcsum));
	printf("\t%d with unreasonable address lengths\n", clnp_stat.cns_badaddr);
D 8
	printf("\t%d with forgotten segmentation information\n", 
E 8
I 8
	printf("\t%d with forgotten segmentation information\n",
E 8
		clnp_stat.cns_noseg);
	printf("\t%d with an incorrect protocol identifier\n", clnp_stat.cns_noproto);
	printf("\t%d with an incorrect version\n", clnp_stat.cns_badvers);
D 8
	printf("\t%d dropped because the ttl has expired\n", 
E 8
I 8
	printf("\t%d dropped because the ttl has expired\n",
E 8
		clnp_stat.cns_ttlexpired);
	printf("\t%d clnp cache misses\n", clnp_stat.cns_cachemiss);
D 8
	printf("\t%d clnp congestion experience bits set\n", 
E 8
I 8
	printf("\t%d clnp congestion experience bits set\n",
E 8
		clnp_stat.cns_congest_set);
D 8
	printf("\t%d clnp congestion experience bits received\n", 
E 8
I 8
	printf("\t%d clnp congestion experience bits received\n",
E 8
		clnp_stat.cns_congest_rcvd);
}
I 2
/*
 * Dump CLTP statistics structure.
 */
I 8
void
E 8
cltp_stats(off, name)
D 13
	off_t off;
E 13
I 13
	u_long off;
E 13
	char *name;
{
	struct cltpstat cltpstat;

D 8
	if (off == 0)
E 8
I 8
	if (off == 0 ||
	    kread(off, (char *)&cltpstat, sizeof (cltpstat)))
E 8
		return;
D 4
	klseek(kmem, off, 0);
	read(kmem, (char *)&cltpstat, sizeof (cltpstat));
E 4
I 4
D 8
	kvm_read(off, (char *)&cltpstat, sizeof (cltpstat));
E 8
E 4
	printf("%s:\n\t%u incomplete header%s\n", name,
		cltpstat.cltps_hdrops, plural(cltpstat.cltps_hdrops));
	printf("\t%u bad data length field%s\n",
		cltpstat.cltps_badlen, plural(cltpstat.cltps_badlen));
	printf("\t%u bad checksum%s\n",
		cltpstat.cltps_badsum, plural(cltpstat.cltps_badsum));
}

E 2
struct	tp_pcb tpcb;
struct	isopcb isopcb;
struct	socket sockb;
union	{
D 8
struct sockaddr_iso	siso;
char	data[128];
E 8
I 8
	struct sockaddr_iso	siso;
	char	data[128];
E 8
} laddr, faddr;
#define kget(o, p) \
D 4
	(klseek(kmem, (off_t)(o), 0), read(kmem, (char *)&p, sizeof (p)))
extern	int kmem;
E 4
I 4
D 8
	(kvm_read((off_t)(o), (char *)&p, sizeof (p)))
E 4
extern	int Aflag;
extern	int aflag;
extern	int nflag;
E 8
I 8
D 13
	(kread((off_t)(o), (char *)&p, sizeof (p)))
E 13
I 13
	(kread((u_long)(o), (char *)&p, sizeof (p)))
E 13
E 8

static	int first = 1;

/*
 * Print a summary of connections related to an Internet
 * protocol.  For TP, also give state of connection.
 * Listening processes (aflag) are suppressed unless the
 * -a (all) flag is specified.
 */
I 8
void
E 8
iso_protopr(off, name)
D 13
	off_t off;
E 13
I 13
	u_long off;
E 13
	char *name;
{
	struct isopcb cb;
	register struct isopcb *prev, *next;
I 8
D 10
	int istp = (strcmp(name, "tp") == 0);
E 10
E 8
I 2
D 7
	int istp = (strcmp(name, "tp") == 0);
E 7
E 2

	if (off == 0) {
		printf("%s control block: symbol not in namelist\n", name);
		return;
	}
I 7
D 8
	if (strcmp(name, "tp") == 0)
		return tp_protopr(off, name);
E 7
	kget(off, cb);
E 8
I 8
D 10
	if (kread(off, (char *)&cb, sizeof (cb)))
E 10
I 10
	if (strcmp(name, "tp") == 0) {
		tp_protopr(off, name);
E 10
		return;
I 10
	}
	if (kread(off, (char *)&cb, sizeof(cb)))
		return;
E 10
E 8
	isopcb = cb;
	prev = (struct isopcb *)off;
	if (isopcb.isop_next == (struct isopcb *)off)
		return;
	while (isopcb.isop_next != (struct isopcb *)off) {
		next = isopcb.isop_next;
		kget(next, isopcb);
		if (isopcb.isop_prev != prev) {
			printf("prev 0x%x next 0x%x isop_prev 0x%x isop_next 0x%x???\n",
				prev, next, isopcb.isop_prev, isopcb.isop_next);
			break;
		}
		kget(isopcb.isop_socket, sockb);
D 2
		kget(sockb.so_tpcb, tpcb);
		if (tpcb.tp_state == ST_ERROR)
			fprintf(stderr,"addr: 0x%x, prev 0x%x\n", next, prev);
		if (!aflag &&
			tpcb.tp_state == TP_LISTENING ||
			tpcb.tp_state == TP_CLOSED ||
			tpcb.tp_state == TP_REFWAIT) {
			prev = next;
			continue;
E 2
I 2
D 7
		if (istp) {
			kget(sockb.so_tpcb, tpcb);
			if (tpcb.tp_state == ST_ERROR)
				fprintf(stderr,"addr: 0x%x, prev 0x%x\n", next, prev);
			if (!aflag &&
				tpcb.tp_state == TP_LISTENING ||
				tpcb.tp_state == TP_CLOSED ||
				tpcb.tp_state == TP_REFWAIT) {
				prev = next;
				continue;
			}
E 2
		}
		if (first) {
			printf("Active ISO net connections");
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
E 7
I 7
D 8
		iso_protopr1((off_t)next, 0);
		putchar('\n');
		prev = next;
	}
}

iso_protopr1(kern_addr, istp)
off_t kern_addr;
{
	if (first) {
		printf("Active ISO net connections");
		if (aflag)
			printf(" (including servers)");
		putchar('\n');
E 8
I 8
D 10
		if (istp) {
			kget(sockb.so_tpcb, tpcb);
			if (tpcb.tp_state == ST_ERROR)
				fprintf(stderr,"addr: 0x%x, prev 0x%x\n", next, prev);
			if (!aflag &&
				tpcb.tp_state == TP_LISTENING ||
				tpcb.tp_state == TP_CLOSED ||
				tpcb.tp_state == TP_REFWAIT) {
				prev = next;
				continue;
			}
		}
		if (first) {
			printf("Active ISO net connections");
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
E 10
I 10
D 13
		iso_protopr1((off_t)next, 0);
E 13
I 13
		iso_protopr1((u_long)next, 0);
E 13
		putchar('\n');
		prev = next;
	}
}

I 12
void
E 12
iso_protopr1(kern_addr, istp)
D 12
off_t kern_addr;
E 12
I 12
D 13
	off_t kern_addr;
E 13
I 13
	u_long kern_addr;
E 13
	int istp;
E 12
{
	if (first) {
		printf("Active ISO net connections");
		if (aflag)
			printf(" (including servers)");
		putchar('\n');
E 10
E 8
E 7
		if (Aflag)
I 10
			printf("%-8.8s ", "PCB");
		printf(Aflag ?
			"%-5.5s %-6.6s %-6.6s  %-18.18s %-18.18s %s\n" :
			"%-5.5s %-6.6s %-6.6s  %-22.22s %-22.22s %s\n",
			"Proto", "Recv-Q", "Send-Q",
			"Local Address", "Foreign Address", "(state)");
		first = 0;
	}
	if (Aflag)
E 10
I 7
D 8
			printf("%-8.8s ", "PCB");
		printf(Aflag ?
			"%-5.5s %-6.6s %-6.6s  %-18.18s %-18.18s %s\n" :
			"%-5.5s %-6.6s %-6.6s  %-22.22s %-22.22s %s\n",
			"Proto", "Recv-Q", "Send-Q",
			"Local Address", "Foreign Address", "(state)");
		first = 0;
	}
	if (Aflag)
E 8
E 7
D 2
				printf("%8x ", sockb.so_tpcb);
E 2
I 2
			printf("%8x ",
D 7
				(istp ? (off_t)sockb.so_tpcb : (off_t)next));
E 2
		printf("%-5.5s %6d %6d ", name, sockb.so_rcv.sb_cc,
			sockb.so_snd.sb_cc);
D 2
		if ((char *)isopcb.isop_laddr == ((char *)next) +
			_offsetof(struct isopcb, isop_sladdr))
			laddr.siso = isopcb.isop_sladdr;
		else
			kget(isopcb.isop_laddr, laddr);
		if ((char *)isopcb.isop_faddr == ((char *)next) +
			_offsetof(struct isopcb, isop_sfaddr))
			faddr.siso = isopcb.isop_sfaddr;
		else
			kget(isopcb.isop_laddr, faddr);
		isonetprint(&laddr, 1);
		isonetprint(&faddr, 0);
		if (tpcb.tp_state >= tp_NSTATES)
			printf(" %d", tpcb.tp_state);
		else
			printf(" %-12.12s", tp_sstring[tpcb.tp_state]);
E 2
I 2
		if (isopcb.isop_laddr == 0)
E 7
I 7
D 8
					(sockb.so_pcb ? (off_t)sockb.so_pcb : (off_t)kern_addr));
	printf("%-5.5s %6d %6d ", "tp", sockb.so_rcv.sb_cc, sockb.so_snd.sb_cc);
	if (istp && tpcb.tp_lsuffixlen) {
			hexprint(tpcb.tp_lsuffixlen, tpcb.tp_lsuffix, "()");
			printf("\t");
	} else if (isopcb.isop_laddr == 0)
E 8
I 8
D 10
				(istp ? (off_t)sockb.so_tpcb : (off_t)next));
		printf("%-5.5s %6d %6d ", name, sockb.so_rcv.sb_cc,
			sockb.so_snd.sb_cc);
		if (isopcb.isop_laddr == 0)
E 10
I 10
D 12
					(sockb.so_pcb ? (off_t)sockb.so_pcb : (off_t)kern_addr));
E 12
I 12
					(sockb.so_pcb ? (void *)sockb.so_pcb : (void *)kern_addr));
E 12
	printf("%-5.5s %6d %6d ", "tp", sockb.so_rcv.sb_cc, sockb.so_snd.sb_cc);
	if (istp && tpcb.tp_lsuffixlen) {
			hexprint(tpcb.tp_lsuffixlen, tpcb.tp_lsuffix, "()");
			printf("\t");
	} else if (isopcb.isop_laddr == 0)
E 10
E 8
E 7
			printf("*.*\t");
D 7
		else {
			if ((char *)isopcb.isop_laddr == ((char *)next) +
				_offsetof(struct isopcb, isop_sladdr))
				laddr.siso = isopcb.isop_sladdr;
E 7
I 7
D 8
	else {
			if ((char *)isopcb.isop_laddr == ((char *)kern_addr) +
					_offsetof(struct isopcb, isop_sladdr))
					laddr.siso = isopcb.isop_sladdr;
E 8
I 8
D 10
		else {
			if ((char *)isopcb.isop_laddr == ((char *)next) +
				_offsetof(struct isopcb, isop_sladdr))
				laddr.siso = isopcb.isop_sladdr;
E 10
I 10
	else {
			if ((char *)isopcb.isop_laddr == ((char *)kern_addr) +
					_offsetof(struct isopcb, isop_sladdr))
					laddr.siso = isopcb.isop_sladdr;
E 10
E 8
E 7
			else
D 7
				kget(isopcb.isop_laddr, laddr);
E 7
I 7
D 8
					kget(isopcb.isop_laddr, laddr);
E 7
			isonetprint(&laddr, 1);
I 7
	}
	if (istp && tpcb.tp_fsuffixlen) {
			hexprint(tpcb.tp_fsuffixlen, tpcb.tp_fsuffix, "()");
			printf("\t");
	} else if (isopcb.isop_faddr == 0)
		printf("*.*\t");
	else {
		if ((char *)isopcb.isop_faddr == ((char *)kern_addr) +
			_offsetof(struct isopcb, isop_sfaddr))
			faddr.siso = isopcb.isop_sfaddr;
		else
			kget(isopcb.isop_faddr, faddr);
		isonetprint(&faddr, 0);
	}
}

tp_protopr(off, name)
off_t off;
char *name;
{
	struct tp_ref *tpr, *tpr_base;
	struct tp_refinfo tpkerninfo;
	int size;

	kget(off, tpkerninfo);
	size = tpkerninfo.tpr_size * sizeof (*tpr);
	tpr_base = (struct tp_ref *)malloc(size);
	if (tpr_base == 0)
		return;
	kvm_read((off_t)(tpkerninfo.tpr_base), (char *)tpr_base, size);
	for (tpr = tpr_base; tpr < tpr_base + tpkerninfo.tpr_size; tpr++) {
		if (tpr->tpr_pcb == 0)
			continue;
		kget(tpr->tpr_pcb, tpcb);
		if (tpcb.tp_state == ST_ERROR)
			printf("undefined tpcb state: 0x%x\n", tpr->tpr_pcb);
		if (!aflag &&
			(tpcb.tp_state == TP_LISTENING ||
			 tpcb.tp_state == TP_CLOSED ||
			 tpcb.tp_state == TP_REFWAIT)) {
			continue;
E 8
I 8
D 10
				kget(isopcb.isop_laddr, laddr);
E 10
I 10
					kget(isopcb.isop_laddr, laddr);
E 10
			isonetprint((struct sockaddr_iso *)&laddr, 1);
I 10
	}
	if (istp && tpcb.tp_fsuffixlen) {
			hexprint(tpcb.tp_fsuffixlen, tpcb.tp_fsuffix, "()");
			printf("\t");
	} else if (isopcb.isop_faddr == 0)
		printf("*.*\t");
	else {
		if ((char *)isopcb.isop_faddr == ((char *)kern_addr) +
			_offsetof(struct isopcb, isop_sfaddr))
			faddr.siso = isopcb.isop_sfaddr;
		else
			kget(isopcb.isop_faddr, faddr);
		isonetprint((struct sockaddr_iso *)&faddr, 0);
	}
}

I 12
void
E 12
tp_protopr(off, name)
D 12
off_t off;
char *name;
E 12
I 12
D 13
	off_t off;
E 13
I 13
	u_long off;
E 13
	char *name;
E 12
{
I 14
	extern char *tp_sstring[];
E 14
	struct tp_ref *tpr, *tpr_base;
	struct tp_refinfo tpkerninfo;
	int size;

	kget(off, tpkerninfo);
	size = tpkerninfo.tpr_size * sizeof (*tpr);
	tpr_base = (struct tp_ref *)malloc(size);
	if (tpr_base == 0)
		return;
D 13
	kread((off_t)(tpkerninfo.tpr_base), (char *)tpr_base, size);
E 13
I 13
	kread((u_long)(tpkerninfo.tpr_base), (char *)tpr_base, size);
E 13
	for (tpr = tpr_base; tpr < tpr_base + tpkerninfo.tpr_size; tpr++) {
		if (tpr->tpr_pcb == 0)
			continue;
		kget(tpr->tpr_pcb, tpcb);
		if (tpcb.tp_state == ST_ERROR)
			printf("undefined tpcb state: 0x%x\n", tpr->tpr_pcb);
		if (!aflag &&
			(tpcb.tp_state == TP_LISTENING ||
			 tpcb.tp_state == TP_CLOSED ||
			 tpcb.tp_state == TP_REFWAIT)) {
			continue;
E 10
E 8
E 7
		}
D 7
		if (isopcb.isop_faddr == 0)
			printf("*.*\t");
		else {
			if ((char *)isopcb.isop_faddr == ((char *)next) +
				_offsetof(struct isopcb, isop_sfaddr))
				faddr.siso = isopcb.isop_sfaddr;
			else
				kget(isopcb.isop_faddr, faddr);
			isonetprint(&faddr, 0);
E 7
I 7
D 8
		kget(tpcb.tp_sock, sockb);
		if (tpcb.tp_npcb) switch(tpcb.tp_netservice) {
			case IN_CLNS:
				tp_inproto(tpkerninfo.tpr_base);
				break;
			default:
				kget(tpcb.tp_npcb, isopcb);
				iso_protopr1(tpcb.tp_npcb, 1);
				break;
E 8
I 8
D 10
		if (isopcb.isop_faddr == 0)
			printf("*.*\t");
		else {
			if ((char *)isopcb.isop_faddr == ((char *)next) +
				_offsetof(struct isopcb, isop_sfaddr))
				faddr.siso = isopcb.isop_sfaddr;
			else
				kget(isopcb.isop_faddr, faddr);
			isonetprint((struct sockaddr_iso *)&faddr, 0);
E 10
I 10
		kget(tpcb.tp_sock, sockb);
		if (tpcb.tp_npcb) switch(tpcb.tp_netservice) {
			case IN_CLNS:
D 12
				tp_inproto(tpkerninfo.tpr_base);
E 12
I 12
D 13
				tp_inproto((off_t)tpkerninfo.tpr_base);
E 13
I 13
				tp_inproto((u_long)tpkerninfo.tpr_base);
E 13
E 12
				break;
			default:
				kget(tpcb.tp_npcb, isopcb);
D 12
				iso_protopr1(tpcb.tp_npcb, 1);
E 12
I 12
D 13
				iso_protopr1((off_t)tpcb.tp_npcb, 1);
E 13
I 13
				iso_protopr1((u_long)tpcb.tp_npcb, 1);
E 13
E 12
				break;
E 10
E 8
E 7
		}
D 7
		if (istp) {
			if (tpcb.tp_state >= tp_NSTATES)
				printf(" %d", tpcb.tp_state);
			else
				printf(" %-12.12s", tp_sstring[tpcb.tp_state]);
		}
E 7
I 7
D 8
		if (tpcb.tp_state >= tp_NSTATES)
			printf(" %d", tpcb.tp_state);
		else
			printf(" %-12.12s", tp_sstring[tpcb.tp_state]);
E 8
I 8
D 10
		if (istp) {
			if (tpcb.tp_state >= tp_NSTATES)
				printf(" %d", tpcb.tp_state);
			else
				printf(" %-12.12s", tp_sstring[tpcb.tp_state]);
		}
E 10
I 10
		if (tpcb.tp_state >= tp_NSTATES)
			printf(" %d", tpcb.tp_state);
		else
			printf(" %-12.12s", tp_sstring[tpcb.tp_state]);
E 10
E 8
E 7
E 2
		putchar('\n');
I 8
D 10
		prev = next;
E 10
E 8
D 7
		prev = next;
E 7
	}
}
I 12

void
E 12
D 7

E 7
I 7
D 8
tp_inproto(pcb)
off_t pcb;
{
	struct inpcb inpcb;
	kget(tpcb.tp_npcb, inpcb);
	if (!aflag && inet_lnaof(inpcb.inp_laddr) == INADDR_ANY)
		return;
	if (Aflag)
		printf("%8x ", pcb);
	printf("%-5.5s %6d %6d ", "tpip", sockb.so_rcv.sb_cc, sockb.so_snd.sb_cc);
	inetprint(&inpcb.inp_laddr, inpcb.inp_lport, "tp");
	inetprint(&inpcb.inp_faddr, inpcb.inp_fport, "tp");
}
E 8
I 8
D 10

E 10
I 10
tp_inproto(pcb)
D 12
off_t pcb;
E 12
I 12
D 13
	off_t pcb;
E 13
I 13
	u_long pcb;
E 13
E 12
{
	struct inpcb inpcb;
	kget(tpcb.tp_npcb, inpcb);
	if (!aflag && inet_lnaof(inpcb.inp_laddr) == INADDR_ANY)
		return;
	if (Aflag)
		printf("%8x ", pcb);
D 12
	printf("%-5.5s %6d %6d ", "tpip", sockb.so_rcv.sb_cc, sockb.so_snd.sb_cc);
E 12
I 12
	printf("%-5.5s %6d %6d ", "tpip",
	    sockb.so_rcv.sb_cc, sockb.so_snd.sb_cc);
E 12
	inetprint(&inpcb.inp_laddr, inpcb.inp_lport, "tp");
	inetprint(&inpcb.inp_faddr, inpcb.inp_fport, "tp");
}
I 12

E 12
E 10
E 8
E 7
/*
 * Pretty print an iso address (net address + port).
 * If the nflag was specified, use numbers instead of names.
 */

#ifdef notdef
char *
isonetname(iso)
	register struct iso_addr *iso;
{
	struct sockaddr_iso sa;
	struct iso_hostent *ihe = 0;
	struct iso_hostent *iso_gethostentrybyaddr();
	struct iso_hostent *iso_getserventrybytsel();
	struct iso_hostent Ihe;
	static char line[80];
D 8
	char *index();
E 8

	bzero(line, sizeof(line));
	if( iso->isoa_afi ) {
		sa.siso_family = AF_ISO;
		sa.siso_addr = *iso;
		sa.siso_tsuffix = 0;

		if (!nflag )
			ihe = iso_gethostentrybyaddr( &sa, 0, 0 );
		if( ihe ) {
			Ihe = *ihe;
			ihe = &Ihe;
			sprintf(line, "%s", ihe->isoh_hname);
		} else {
			sprintf(line, "%s", iso_ntoa(iso));
		}
	} else {
		sprintf(line, "*");
	}
	return line;
}

I 8
static void
E 8
isonetprint(iso, sufx, sufxlen, islocal)
	register struct iso_addr *iso;
	char *sufx;
	u_short	sufxlen;
	int islocal;
{
	struct iso_hostent *iso_getserventrybytsel(), *ihe;
	struct iso_hostent Ihe;
D 8
	char *line, *cp, *index();
E 8
I 8
	char *line, *cp;
E 8
	int Alen = Aflag?18:22;

	line =  isonetname(iso);
	cp = index(line, '\0');
	ihe = (struct iso_hostent *)0;

	if( islocal )
		islocal = 20;
D 8
	else 
E 8
I 8
	else
E 8
		islocal = 22 + Alen;

	if(Aflag)
		islocal += 10 ;

	if(!nflag) {
		if( (cp -line)>10 ) {
			cp = line+10;
			bzero(cp, sizeof(line)-10);
		}
	}

	*cp++ = '.';
	if(sufxlen) {
		if( !Aflag && !nflag && (ihe=iso_getserventrybytsel(sufx, sufxlen))) {
			Ihe = *ihe;
			ihe = &Ihe;
		}
		if( ihe && (strlen(ihe->isoh_aname)>0) ) {
			sprintf(cp, "%s", ihe->isoh_aname);
		} else  {
			iso_sprinttsel(cp, sufx, sufxlen);
		}
	} else
		sprintf(cp, "*");
	/*
	fprintf(stdout, Aflag?" %-18.18s":" %-22.22s", line);
	*/

	if( strlen(line) > Alen ) {
		fprintf(stdout, " %s", line);
		fprintf(stdout, "\n %*.s", islocal+Alen," ");
	} else {
		fprintf(stdout, " %-*.*s", Alen, Alen,line);
	}
}
#endif

#ifdef notdef
I 8
static void
E 8
x25_protopr(off, name)
D 13
	off_t off;
E 13
I 13
	u_long off;
E 13
	char *name;
{
	static char *xpcb_states[] = {
		"CLOSED",
		"LISTENING",
		"CLOSING",
		"CONNECTING",
		"ACKWAIT",
		"OPEN",
	};
	register struct isopcb *prev, *next;
	struct x25_pcb xpcb;

	if (off == 0) {
		printf("%s control block: symbol not in namelist\n", name);
		return;
	}
D 4
	klseek(kmem, off, 0);
	read(kmem, &xpcb, sizeof (struct x25_pcb));
E 4
I 4
D 8
	kvm_read(off, &xpcb, sizeof (struct x25_pcb));
E 8
I 8
	kread(off, &xpcb, sizeof (struct x25_pcb));
E 8
E 4
	prev = (struct isopcb *)off;
	if (xpcb.x_next == (struct isopcb *)off)
		return;
	while (xpcb.x_next != (struct isopcb *)off) {
		next = isopcb.isop_next;
D 4
		klseek(kmem, (off_t)next, 0);
		read(kmem, &xpcb, sizeof (struct x25_pcb));
E 4
I 4
D 8
		kvm_read((off_t)next, &xpcb, sizeof (struct x25_pcb));
E 8
I 8
D 13
		kread((off_t)next, &xpcb, sizeof (struct x25_pcb));
E 13
I 13
		kread((u_long)next, &xpcb, sizeof (struct x25_pcb));
E 13
E 8
E 4
		if (xpcb.x_prev != prev) {
			printf("???\n");
			break;
		}
D 4
		klseek(kmem, (off_t)xpcb.x_socket, 0);
		read(kmem, &sockb, sizeof (sockb));
E 4
I 4
D 8
		kvm_read((off_t)xpcb.x_socket, &sockb, sizeof (sockb));
E 8
I 8
D 13
		kread((off_t)xpcb.x_socket, &sockb, sizeof (sockb));
E 13
I 13
		kread((u_long)xpcb.x_socket, &sockb, sizeof (sockb));
E 13
E 8
E 4

		if (!aflag &&
			xpcb.x_state == LISTENING ||
			xpcb.x_state == TP_CLOSED ) {
			prev = next;
			continue;
		}
		if (first) {
			printf("Active X25 net connections");
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
		printf("%-5.5s %6d %6d ", name, sockb.so_rcv.sb_cc,
			sockb.so_snd.sb_cc);
D 8
		isonetprint(&xpcb.x_laddr.siso_addr, &xpcb.x_lport, 
E 8
I 8
		isonetprint(&xpcb.x_laddr.siso_addr, &xpcb.x_lport,
E 8
			sizeof(xpcb.x_lport), 1);
D 8
		isonetprint(&xpcb.x_faddr.siso_addr, &xpcb.x_fport, 
E 8
I 8
		isonetprint(&xpcb.x_faddr.siso_addr, &xpcb.x_fport,
E 8
			sizeof(xpcb.x_lport), 0);
		if (xpcb.x_state < 0 || xpcb.x_state >= x25_NSTATES)
			printf(" 0x0x0x0x0x0x0x0x0x%x", xpcb.x_state);
		else
			printf(" %-12.12s", xpcb_states[xpcb.x_state]);
		putchar('\n');
		prev = next;
	}
}
#endif

struct	tp_stat tp_stat;

I 8
void
E 8
tp_stats(off, name)
D 8
caddr_t off, name;
E 8
I 8
	caddr_t off, name;
E 8
{
	if (off == 0) {
		printf("TP not configured\n\n");
		return;
	}
I 2
	printf("%s:\n", name);
E 2
	kget(off, tp_stat);
	tprintstat(&tp_stat, 8);
}

#define OUT stdout

D 8
#define plural(x) (x>1?"s":"")

E 8
I 8
static void
E 8
tprintstat(s, indent)
D 8
register struct tp_stat *s;
int indent;
E 8
I 8
	register struct tp_stat *s;
	int indent;
E 8
{
	fprintf(OUT,
		"%*sReceiving:\n",indent," ");
	fprintf(OUT,
		"\t%*s%d variable parameter%s ignored\n", indent," ",
		s->ts_param_ignored ,plural(s->ts_param_ignored));
	fprintf(OUT,
		"\t%*s%d invalid parameter code%s\n", indent, " ",
		s->ts_inv_pcode ,plural(s->ts_inv_pcode));
	fprintf(OUT,
		"\t%*s%d invalid parameter value%s\n", indent, " ",
		s->ts_inv_pval ,plural(s->ts_inv_pval));
	fprintf(OUT,
		"\t%*s%d invalid dutype%s\n", indent, " ",
		s->ts_inv_dutype ,plural(s->ts_inv_dutype));
	fprintf(OUT,
		"\t%*s%d negotiation failure%s\n", indent, " ",
		s->ts_negotfailed ,plural(s->ts_negotfailed));
	fprintf(OUT,
		"\t%*s%d invalid destination reference%s\n", indent, " ",
		s->ts_inv_dref ,plural(s->ts_inv_dref));
	fprintf(OUT,
		"\t%*s%d invalid suffix parameter%s\n", indent, " ",
		s->ts_inv_sufx ,plural(s->ts_inv_sufx));
	fprintf(OUT,
		"\t%*s%d invalid length\n",indent, " ", s->ts_inv_length);
	fprintf(OUT,
		"\t%*s%d invalid checksum%s\n", indent, " ",
		s->ts_bad_csum ,plural(s->ts_bad_csum));
	fprintf(OUT,
		"\t%*s%d DT%s out of order\n", indent, " ",
		s->ts_dt_ooo ,plural(s->ts_dt_ooo));
	fprintf(OUT,
		"\t%*s%d DT%s not in window\n", indent, " ",
		s->ts_dt_niw ,plural(s->ts_dt_niw));
	fprintf(OUT,
		"\t%*s%d duplicate DT%s\n", indent, " ",
		s->ts_dt_dup ,plural(s->ts_dt_dup));
	fprintf(OUT,
			"\t%*s%d XPD%s not in window\n", indent, " ",
			s->ts_xpd_niw ,plural(s->ts_xpd_niw));
		fprintf(OUT,
			"\t%*s%d XPD%s w/o credit to stash\n", indent, " ",
		s->ts_xpd_dup ,plural(s->ts_xpd_dup));
	fprintf(OUT,
		"\t%*s%d time%s local credit reneged\n", indent, " ",
		s->ts_lcdt_reduced ,plural(s->ts_lcdt_reduced));
	fprintf(OUT,
		"\t%*s%d concatenated TPDU%s\n", indent, " ",
		s->ts_concat_rcvd ,plural(s->ts_concat_rcvd));
	fprintf(OUT,
		"%*sSending:\n", indent, " ");
	fprintf(OUT,
		"\t%*s%d XPD mark%s discarded\n", indent, " ",
		s->ts_xpdmark_del ,plural(s->ts_xpdmark_del));
	fprintf(OUT,
		"\t%*sXPD stopped data flow %d time%s\n", indent, " ",
		s->ts_xpd_intheway ,plural(s->ts_xpd_intheway));
	fprintf(OUT,
		"\t%*s%d time%s foreign window closed\n", indent, " ",
		s->ts_zfcdt ,plural(s->ts_zfcdt));
	fprintf(OUT,
		"%*sMiscellaneous:\n", indent, " ");
	fprintf(OUT,
		"\t%*s%d small mbuf%s\n", indent, " ",
		s->ts_mb_small ,plural(s->ts_mb_small));
	fprintf(OUT,
		"\t%*s%d cluster%s\n", indent, " ",
		s->ts_mb_cluster, plural(s->ts_mb_cluster));
	fprintf(OUT,
D 8
		"\t%*s%d source quench \n",indent, " ", 
E 8
I 8
		"\t%*s%d source quench \n",indent, " ",
E 8
		s->ts_quench);
	fprintf(OUT,
		"\t%*s%d dec bit%s\n", indent, " ",
		s->ts_rcvdecbit, plural(s->ts_rcvdecbit));
	fprintf(OUT,
		"\t%*sM:L ( M mbuf chains of length L)\n", indent, " ");
	{
		register int j;

		fprintf(OUT, "\t%*s%d: over 16\n", indent, " ",
		s->ts_mb_len_distr[0]);
		for( j=1; j<=8; j++) {
			fprintf(OUT,
				"\t%*s%d: %d\t\t%d: %d\n", indent, " ",
				s->ts_mb_len_distr[j],j,
				s->ts_mb_len_distr[j<<1],j<<1
				);
		}
	}
	fprintf(OUT,
		"\t%*s%d EOT rcvd\n",  indent, " ", s->ts_eot_input);
	fprintf(OUT,
		"\t%*s%d EOT sent\n",  indent, " ", s->ts_EOT_sent);
	fprintf(OUT,
		"\t%*s%d EOT indication%s\n",  indent, " ",
		s->ts_eot_user ,plural(s->ts_eot_user));

	fprintf(OUT,
		"%*sConnections:\n", indent, " ");
	fprintf(OUT,
		"\t%*s%d connection%s used extended format\n",  indent, " ",
		s->ts_xtd_fmt ,plural(s->ts_xtd_fmt));
	fprintf(OUT,
		"\t%*s%d connection%s allowed transport expedited data\n",  indent, " ",
		s->ts_use_txpd ,plural(s->ts_use_txpd));
	fprintf(OUT,
		"\t%*s%d connection%s turned off checksumming\n",  indent, " ",
		s->ts_csum_off ,plural(s->ts_csum_off));
	fprintf(OUT,
		"\t%*s%d connection%s dropped due to retrans limit\n",  indent, " ",
		s->ts_conn_gaveup ,plural(s->ts_conn_gaveup));
	fprintf(OUT,
		"\t%*s%d tp 4 connection%s\n",  indent, " ",
		s->ts_tp4_conn ,plural(s->ts_tp4_conn));
	fprintf(OUT,
		"\t%*s%d tp 0 connection%s\n",  indent, " ",
		s->ts_tp0_conn ,plural(s->ts_tp0_conn));
I 8
D 10
	{
		register int j, div;
		register float f;
E 10
I 10
    {
		register int j;
E 10
		static char *name[]= {
			"~LOCAL, PDN",
			"~LOCAL,~PDN",
			" LOCAL,~PDN",
			" LOCAL, PDN"
		};
D 9
#define factor(i) \
	div = (s->ts_rtt[(i)].tv_sec * 1000000) + \
		s->ts_rtt[(i)].tv_usec ;\
	if(div) {\
		f = ((s->ts_rtv[(i)].tv_sec * 1000000) + \
				s->ts_rtv[(i)].tv_usec)/div;  \
		div = (int) (f + 0.5);\
	}
E 9

		fprintf(OUT,
D 9
			"\n%*sRound trip times, listed in (sec: usec):\n", indent, " ");
E 9
I 9
			"\n%*sRound trip times, listed in ticks:\n", indent, " ");
E 9
		fprintf(OUT,
			"\t%*s%11.11s  %12.12s | %12.12s | %s\n", indent, " ",
				"Category",
				"Smoothed avg", "Deviation", "Deviation/Avg");
D 10
		for( j=0; j<=3; j++) {
E 10
I 10
		for (j = 0; j <= 3; j++) {
E 10
D 9
			factor(j);
E 9
			fprintf(OUT,
D 9
				"\t%*s%11.11s: %5d:%-6d | %5d:%-6d | %-6d\n", indent, " ",
E 9
I 9
				"\t%*s%11.11s: %-11d | %-11d | %-11d | %-11d\n", indent, " ",
E 9
				name[j],
D 9
				s->ts_rtt[j].tv_sec,
				s->ts_rtt[j].tv_usec,
				s->ts_rtv[j].tv_sec,
				s->ts_rtv[j].tv_usec,
				div);
E 9
I 9
				s->ts_rtt[j],
				s->ts_rtt[j],
				s->ts_rtv[j],
				s->ts_rtv[j]);
E 9
		}
	}
E 8
D 7
	{
		register int j, div;
		register float f;
		static char *name[]= {
			"~LOCAL, PDN", 
			"~LOCAL,~PDN",
			" LOCAL,~PDN",
			" LOCAL, PDN"
		};
#define factor(i) \
	div = (s->ts_rtt[(i)].tv_sec * 1000000) + \
		s->ts_rtt[(i)].tv_usec ;\
	if(div) {\
		f = ((s->ts_rtv[(i)].tv_sec * 1000000) + \
				s->ts_rtv[(i)].tv_usec)/div;  \
		div = (int) (f + 0.5);\
	}

		fprintf(OUT, 
			"\n%*sRound trip times, listed in (sec: usec):\n", indent, " ");
		fprintf(OUT, 
			"\t%*s%11.11s  %12.12s | %12.12s | %s\n", indent, " ",
				"Category",
				"Smoothed avg", "Deviation", "Deviation/Avg");
		for( j=0; j<=3; j++) {
			factor(j);
			fprintf(OUT,
				"\t%*s%11.11s: %5d:%-6d | %5d:%-6d | %-6d\n", indent, " ",
				name[j],
				s->ts_rtt[j].tv_sec,
				s->ts_rtt[j].tv_usec,
				s->ts_rtv[j].tv_sec,
				s->ts_rtv[j].tv_usec,
				div);
		}
	}
E 7
	fprintf(OUT,
"\n%*sTpdus RECVD [%d valid, %3.6f %% of total (%d); %d dropped]\n",indent," ",
		s->ts_tpdu_rcvd ,
D 8
		((s->ts_pkt_rcvd > 0) ? 
E 8
I 8
		((s->ts_pkt_rcvd > 0) ?
E 8
			((100 * (float)s->ts_tpdu_rcvd)/(float)s->ts_pkt_rcvd)
			: 0),
		s->ts_pkt_rcvd,
		s->ts_recv_drop );

	fprintf(OUT,
		"\t%*sDT  %6d   AK  %6d   DR  %4d   CR  %4d \n", indent, " ",
		s->ts_DT_rcvd, s->ts_AK_rcvd, s->ts_DR_rcvd, s->ts_CR_rcvd);
	fprintf(OUT,
		"\t%*sXPD %6d   XAK %6d   DC  %4d   CC  %4d   ER  %4d\n",  indent, " ",
		s->ts_XPD_rcvd, s->ts_XAK_rcvd, s->ts_DC_rcvd, s->ts_CC_rcvd,
		s->ts_ER_rcvd);
	fprintf(OUT,
		"\n%*sTpdus SENT [%d total, %d dropped]\n",  indent, " ",
		s->ts_tpdu_sent, s->ts_send_drop);

	fprintf(OUT,
		"\t%*sDT  %6d   AK  %6d   DR  %4d   CR  %4d \n", indent, " ",
		s->ts_DT_sent, s->ts_AK_sent, s->ts_DR_sent, s->ts_CR_sent);
	fprintf(OUT,
		"\t%*sXPD %6d   XAK %6d   DC  %4d   CC  %4d   ER  %4d\n",  indent, " ",
		s->ts_XPD_sent, s->ts_XAK_sent, s->ts_DC_sent, s->ts_CC_sent,
		s->ts_ER_sent);

	fprintf(OUT,
		"\n%*sRetransmissions:\n", indent, " ");
#define PERCENT(X,Y) (((Y)>0)?((100 *(float)(X)) / (float) (Y)):0)

	fprintf(OUT,
	"\t%*sCR  %6d   CC  %6d   DR  %6d \n", indent, " ",
		s->ts_retrans_cr, s->ts_retrans_cc, s->ts_retrans_dr);
	fprintf(OUT,
	"\t%*sDT  %6d (%5.2f%%)\n", indent, " ",
		s->ts_retrans_dt,
		PERCENT(s->ts_retrans_dt, s->ts_DT_sent));
	fprintf(OUT,
	"\t%*sXPD %6d (%5.2f%%)\n",  indent, " ",
		s->ts_retrans_xpd,
		PERCENT(s->ts_retrans_xpd, s->ts_XPD_sent));
D 8
	
E 8

I 8

E 8
	fprintf(OUT,
		"\n%*sE Timers: [%6d ticks]\n", indent, " ", s->ts_Eticks);
	fprintf(OUT,
		"%*s%6d timer%s set \t%6d timer%s expired \t%6d timer%s cancelled\n",indent, " ",
		s->ts_Eset ,plural(s->ts_Eset),
		s->ts_Eexpired ,plural(s->ts_Eexpired),
		s->ts_Ecan_act ,plural(s->ts_Ecan_act));

	fprintf(OUT,
		"\n%*sC Timers: [%6d ticks]\n",  indent, " ",s->ts_Cticks);
	fprintf(OUT,
	"%*s%6d timer%s set \t%6d timer%s expired \t%6d timer%s cancelled\n",
		indent, " ",
		s->ts_Cset ,plural(s->ts_Cset),
		s->ts_Cexpired ,plural(s->ts_Cexpired),
		s->ts_Ccan_act ,plural(s->ts_Ccan_act));
	fprintf(OUT,
		"%*s%6d inactive timer%s cancelled\n", indent, " ",
		s->ts_Ccan_inact ,plural(s->ts_Ccan_inact));

	fprintf(OUT,
		"\n%*sPathological debugging activity:\n", indent, " ");
	fprintf(OUT,
		"\t%*s%6d CC%s sent to zero dref\n", indent, " ",
		s->ts_zdebug ,plural(s->ts_zdebug));
	/* SAME LINE AS ABOVE */
	fprintf(OUT,
		"\t%*s%6d random DT%s dropped\n", indent, " ",
		s->ts_ydebug ,plural(s->ts_ydebug));
	fprintf(OUT,
		"\t%*s%6d illegally large XPD TPDU%s\n", indent, " ",
		s->ts_vdebug ,plural(s->ts_vdebug));
	fprintf(OUT,
		"\t%*s%6d faked reneging of cdt\n", indent, " ",
		s->ts_ldebug );

	fprintf(OUT,
		"\n%*sACK reasons:\n", indent, " ");
	fprintf(OUT, "\t%*s%6d not acked immediately\n", indent, " ",
D 12
										s->ts_ackreason[_ACK_DONT_] );
E 12
I 12
		s->ts_ackreason[_ACK_DONT_] );
E 12
	fprintf(OUT, "\t%*s%6d strategy==each\n", indent, " ",
D 12
										s->ts_ackreason[_ACK_STRAT_EACH_] );
E 12
I 12
		s->ts_ackreason[_ACK_STRAT_EACH_] );
E 12
	fprintf(OUT, "\t%*s%6d strategy==fullwindow\n", indent, " ",
D 12
										s->ts_ackreason[_ACK_STRAT_FULLWIN_] );
E 12
I 12
		s->ts_ackreason[_ACK_STRAT_FULLWIN_] );
E 12
	fprintf(OUT, "\t%*s%6d duplicate DT\n", indent, " ",
D 12
										s->ts_ackreason[_ACK_DUP_] );
E 12
I 12
		s->ts_ackreason[_ACK_DUP_] );
E 12
	fprintf(OUT, "\t%*s%6d EOTSDU\n", indent, " ",
D 12
										s->ts_ackreason[_ACK_EOT_] );
E 12
I 12
		s->ts_ackreason[_ACK_EOT_] );
E 12
	fprintf(OUT, "\t%*s%6d reordered DT\n", indent, " ",
D 12
										s->ts_ackreason[_ACK_REORDER_] );
E 12
I 12
		s->ts_ackreason[_ACK_REORDER_] );
E 12
	fprintf(OUT, "\t%*s%6d user rcvd\n", indent, " ",
D 12
										s->ts_ackreason[_ACK_USRRCV_] );
E 12
I 12
		s->ts_ackreason[_ACK_USRRCV_] );
E 12
D 8
	fprintf(OUT, "\t%*s%6d fcc reqd\n", 	indent, " ",
E 8
I 8
	fprintf(OUT, "\t%*s%6d fcc reqd\n", indent, " ",
E 8
D 12
										s->ts_ackreason[_ACK_FCC_] );
E 12
I 12
		s->ts_ackreason[_ACK_FCC_] );
E 12
}
#ifndef SSEL
#define SSEL(s) ((s)->siso_tlen + TSEL(s))
#define PSEL(s) ((s)->siso_slen + SSEL(s))
#endif

I 8
static void
E 8
isonetprint(siso, islocal)
D 8
register struct sockaddr_iso *siso;
int islocal;
E 8
I 8
	register struct sockaddr_iso *siso;
	int islocal;
E 8
{
	hexprint(siso->siso_nlen, siso->siso_addr.isoa_genaddr, "{}");
	if (siso->siso_tlen || siso->siso_slen || siso->siso_plen)
		hexprint(siso->siso_tlen, TSEL(siso), "()");
	if (siso->siso_slen || siso->siso_plen)
		hexprint(siso->siso_slen, SSEL(siso), "[]");
	if (siso->siso_plen)
		hexprint(siso->siso_plen, PSEL(siso), "<>");
	putchar(' ');
}
I 12

E 12
static char hexlist[] = "0123456789abcdef", obuf[128];
D 2
static
E 2
I 2

I 8
static void
E 8
E 2
hexprint(n, buf, delim)
D 8
char *buf, *delim;
E 8
I 8
	int n;
	char *buf, *delim;
E 8
{
	register u_char *in = (u_char *)buf, *top = in + n;
	register char *out = obuf;
	register int i;

I 2
	if (n == 0)
		return;
E 2
	while (in < top) {
		i = *in++;
		*out++ = '.';
		if (i > 0xf) {
			out[1] = hexlist[i & 0xf];
			i >>= 4;
			out[0] = hexlist[i];
			out += 2;
		} else
			*out++ = hexlist[i];
	}
	*obuf = *delim; *out++ = delim[1]; *out = 0;
	printf("%s", obuf);
}
E 1
