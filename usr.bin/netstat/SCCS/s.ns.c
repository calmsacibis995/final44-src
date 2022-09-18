h01174
s 00002/00002/00323
d D 8.1 93/06/06 15:44:10 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00008/00317
d D 5.16 92/07/07 16:57:23 sklower 16 15
c not every value return in an nlist structure was being
c coerced to an (off_t) which was only being smashed back down to a (u_long)
c as an argument to kvm_read.  If you ask me nl.n_value ought to be a (void *)
c but since the type of nl.n_value and the second argument to kvm_read are
c the same I got fed up and changed all the off_t's to be that type (u_long).
e
s 00002/00001/00323
d D 5.15 92/07/06 15:36:07 sklower 15 14
c Multicast changes from lbl
e
s 00019/00015/00305
d D 5.14 92/05/27 18:11:44 sklower 14 13
c incorporate changes for new kvm interfaces from lbl
e
s 00018/00011/00302
d D 5.13 91/03/01 15:17:30 bostic 13 12
c ANSI
e
s 00008/00015/00305
d D 5.12 90/06/18 17:20:48 sklower 12 11
c use kvm_nlist to avoid numerous lseeks of nlist; use kvm_read to avoid duplication.
e
s 00001/00011/00319
d D 5.11 90/06/01 17:08:09 bostic 11 10
c new copyright notice
e
s 00001/00001/00329
d D 5.10 89/09/25 13:15:16 sklower 10 9
c have to include param.h instead of types.h to compile
e
s 00012/00007/00318
d D 5.9 88/06/29 20:42:09 bostic 9 8
c install approved copyright notice
e
s 00001/00001/00324
d D 5.8 88/03/29 09:13:47 karels 8 7
c use spp_timer.h (for bostic)
e
s 00091/00012/00234
d D 5.7 88/03/03 17:24:57 sklower 7 6
c deal with revised error statistics scheme
e
s 00009/00004/00237
d D 5.6 88/02/07 20:38:22 karels 6 5
c new copyrights
e
s 00001/00001/00240
d D 5.5 86/12/15 17:10:41 sam 5 4
c all statistics are unsigned
e
s 00008/00007/00233
d D 5.4 86/08/11 11:51:01 kupfer 4 3
c Some lint.
e
s 00014/00013/00226
d D 5.3 85/09/12 08:38:34 karels 3 2
c don't print header without any connections
e
s 00006/00012/00233
d D 5.2 85/09/10 08:48:22 karels 2 1
c no messages if protocols not present
e
s 00245/00000/00000
d D 5.1 85/08/16 20:04:55 sklower 1 0
c XNS statistics printing routines & such.
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
D 9
 * Copyright (c) 1985,1988 Regents of the University of California.
E 9
I 9
D 15
 * Copyright (c) 1985, 1988 Regents of the University of California.
E 15
I 15
D 17
 * Copyright (c) 1983, 1988 Regents of the University of California.
E 15
E 9
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1983, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
D 11
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
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 9
E 6
 */
D 6

E 6

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9

D 13
#include <stdio.h>
#include <errno.h>
#include <nlist.h>

E 13
D 10
#include <sys/types.h>
E 10
I 10
#include <sys/param.h>
E 10
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>

#include <net/route.h>
#include <net/if.h>

#include <netinet/tcp_fsm.h>
D 8
#include <netinet/tcp_timer.h>
E 8

#include <netns/ns.h>
#include <netns/ns_pcb.h>
#include <netns/idp.h>
#include <netns/idp_var.h>
#include <netns/ns_error.h>
#include <netns/sp.h>
#include <netns/spidp.h>
I 8
#include <netns/spp_timer.h>
E 8
#include <netns/spp_var.h>
#define SANAMES
#include <netns/spp_debug.h>

I 13
#include <nlist.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
I 14
#include "netstat.h"
E 14
E 13

struct	nspcb nspcb;
struct	sppcb sppcb;
struct	socket sockb;
D 4
struct	protosw proto;
E 4
D 12
extern	int kmem;
E 12
D 14
extern	int Aflag;
extern	int aflag;
extern	int nflag;
I 4
extern	char *plural();
E 4
char *ns_prpr();
E 14

I 14
static char *ns_prpr __P((struct ns_addr *));
I 15
static void ns_erputil __P((int, int));
E 15

E 14
static	int first = 1;

/*
 * Print a summary of connections related to a Network Systems
 * protocol.  For SPP, also give state of connection.
 * Listening processes (aflag) are suppressed unless the
 * -a (all) flag is specified.
 */

I 14
void
E 14
nsprotopr(off, name)
D 16
	off_t off;
E 16
I 16
	u_long off;
E 16
	char *name;
{
	struct nspcb cb;
	register struct nspcb *prev, *next;
	int isspp;

D 2
	if (off == 0) {
		printf("%s control block: symbol not in namelist\n", name);
E 2
I 2
	if (off == 0)
E 2
		return;
D 2
	}
E 2
	isspp = strcmp(name, "spp") == 0;
D 12
	klseek(kmem, off, 0);
D 4
	read(kmem, &cb, sizeof (struct nspcb));
E 4
I 4
	read(kmem, (char *)&cb, sizeof (struct nspcb));
E 12
I 12
D 14
	kvm_read(off, (char *)&cb, sizeof (struct nspcb));
E 14
I 14
	kread(off, (char *)&cb, sizeof (struct nspcb));
E 14
E 12
E 4
	nspcb = cb;
	prev = (struct nspcb *)off;
I 2
	if (nspcb.nsp_next == (struct nspcb *)off)
		return;
E 2
D 3
	if (first) {
		printf("Active connections");
		if (aflag)
			printf(" (including servers)");
		putchar('\n');
		if (Aflag)
			printf("%-8.8s ", "PCB");
		printf(Aflag ? "%-5.5s %-6.6s %-6.6s  %-18.18s %-18.18s %s\n" :
			"%-5.5s %-6.6s %-6.6s  %-22.22s %-22.22s %s\n",
			"Proto", "Recv-Q", "Send-Q",
			"Local Address", "Foreign Address", "(state)");
		first = 0;
	}
E 3
	for (;nspcb.nsp_next != (struct nspcb *)off; prev = next) {
D 4
		char *cp;
E 4
D 16
		off_t ppcb;
E 16
I 16
		u_long ppcb;
E 16

		next = nspcb.nsp_next;
D 12
		klseek(kmem, (off_t)next, 0);
D 4
		read(kmem, &nspcb, sizeof (nspcb));
E 4
I 4
		read(kmem, (char *)&nspcb, sizeof (nspcb));
E 12
I 12
D 14
		kvm_read((off_t)next, (char *)&nspcb, sizeof (nspcb));
E 14
I 14
D 16
		kread((off_t)next, (char *)&nspcb, sizeof (nspcb));
E 16
I 16
		kread((u_long)next, (char *)&nspcb, sizeof (nspcb));
E 16
E 14
E 12
E 4
		if (nspcb.nsp_prev != prev) {
			printf("???\n");
			break;
		}
		if (!aflag && ns_nullhost(nspcb.nsp_faddr) ) {
			continue;
		}
D 12
		klseek(kmem, (off_t)nspcb.nsp_socket, 0);
D 4
		read(kmem, &sockb, sizeof (sockb));
E 4
I 4
		read(kmem, (char *)&sockb, sizeof (sockb));
E 12
I 12
D 14
		kvm_read((off_t)nspcb.nsp_socket,
E 14
I 14
D 16
		kread((off_t)nspcb.nsp_socket,
E 16
I 16
		kread((u_long)nspcb.nsp_socket,
E 16
E 14
				(char *)&sockb, sizeof (sockb));
E 12
E 4
D 16
		ppcb = (off_t) nspcb.nsp_pcb;
E 16
I 16
		ppcb = (u_long) nspcb.nsp_pcb;
E 16
		if (ppcb) {
			if (isspp) {
D 12
				klseek(kmem, ppcb, 0);
D 4
				read(kmem, &sppcb, sizeof (sppcb));
E 4
I 4
				read(kmem, (char *)&sppcb, sizeof (sppcb));
E 12
I 12
D 14
				kvm_read(ppcb, (char *)&sppcb, sizeof (sppcb));
E 14
I 14
				kread(ppcb, (char *)&sppcb, sizeof (sppcb));
E 14
E 12
E 4
			} else continue;
		} else
			if (isspp) continue;
I 3
		if (first) {
			printf("Active NS connections");
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
E 3
		if (Aflag)
			printf("%8x ", ppcb);
		printf("%-5.5s %6d %6d ", name, sockb.so_rcv.sb_cc,
			sockb.so_snd.sb_cc);
		printf("  %-22.22s", ns_prpr(&nspcb.nsp_laddr));
		printf(" %-22.22s", ns_prpr(&nspcb.nsp_faddr));
		if (isspp) {
			extern char *tcpstates[];
D 4
			if (sppcb.s_state < 0 || sppcb.s_state >= TCP_NSTATES)
E 4
I 4
			if (sppcb.s_state >= TCP_NSTATES)
E 4
				printf(" %d", sppcb.s_state);
			else
				printf(" %s", tcpstates[sppcb.s_state]);
		}
		putchar('\n');
		prev = next;
	}
}
D 5
#define ANY(x,y,z)  ((x) ? printf("\t%d %s%s%s\n",x,y,plural(x),z) : 0)
E 5
I 5
D 7
#define ANY(x,y,z)  ((x) ? printf("\t%u %s%s%s\n",x,y,plural(x),z) : 0)
E 7
I 7
D 13
#define ANY(x,y,z)  ((x) ? printf("\t%d %s%s%s -- %s\n",x,y,plural(x),z,"x") : 0)
E 13
I 13
#define ANY(x,y,z) \
	((x) ? printf("\t%d %s%s%s -- %s\n",x,y,plural(x),z,"x") : 0)
E 13
E 7
E 5

/*
 * Dump SPP statistics structure.
 */
I 14
void
E 14
spp_stats(off, name)
D 16
	off_t off;
E 16
I 16
	u_long off;
E 16
	char *name;
{
	struct spp_istat spp_istat;
I 7
#define sppstat spp_istat.newstats
E 7

D 2
	if (off == 0) {
		printf("%sstat: symbol not in namelist\n", name);
E 2
I 2
	if (off == 0)
E 2
		return;
D 2
	}
E 2
D 12
	klseek(kmem, off, 0);
	read(kmem, (char *)&spp_istat, sizeof (spp_istat));
E 12
I 12
D 14
	kvm_read(off, (char *)&spp_istat, sizeof (spp_istat));
E 14
I 14
	kread(off, (char *)&spp_istat, sizeof (spp_istat));
E 14
E 12
	printf("%s:\n", name);
	ANY(spp_istat.nonucn, "connection", " dropped due to no new sockets ");
	ANY(spp_istat.gonawy, "connection", " terminated due to our end dying");
D 13
	ANY(spp_istat.nonucn, "connection", " dropped due to inability to connect");
	ANY(spp_istat.noconn, "connection", " dropped due to inability to connect");
	ANY(spp_istat.notme, "connection", " incompleted due to mismatched id's");
E 13
I 13
	ANY(spp_istat.nonucn, "connection",
	    " dropped due to inability to connect");
	ANY(spp_istat.noconn, "connection",
	    " dropped due to inability to connect");
	ANY(spp_istat.notme, "connection",
	    " incompleted due to mismatched id's");
E 13
	ANY(spp_istat.wrncon, "connection", " dropped due to mismatched id's");
	ANY(spp_istat.bdreas, "packet", " dropped out of sequence");
	ANY(spp_istat.lstdup, "packet", " duplicating the highest packet");
	ANY(spp_istat.notyet, "packet", " refused as exceeding allocation");
I 7
	ANY(sppstat.spps_connattempt, "connection", " initiated");
	ANY(sppstat.spps_accepts, "connection", " accepted");
	ANY(sppstat.spps_connects, "connection", " established");
	ANY(sppstat.spps_drops, "connection", " dropped");
	ANY(sppstat.spps_conndrops, "embryonic connection", " dropped");
	ANY(sppstat.spps_closed, "connection", " closed (includes drops)");
	ANY(sppstat.spps_segstimed, "packet", " where we tried to get rtt");
	ANY(sppstat.spps_rttupdated, "time", " we got rtt");
	ANY(sppstat.spps_delack, "delayed ack", " sent");
	ANY(sppstat.spps_timeoutdrop, "connection", " dropped in rxmt timeout");
	ANY(sppstat.spps_rexmttimeo, "retransmit timeout", "");
	ANY(sppstat.spps_persisttimeo, "persist timeout", "");
	ANY(sppstat.spps_keeptimeo, "keepalive timeout", "");
	ANY(sppstat.spps_keepprobe, "keepalive probe", " sent");
	ANY(sppstat.spps_keepdrops, "connection", " dropped in keepalive");
	ANY(sppstat.spps_sndtotal, "total packet", " sent");
	ANY(sppstat.spps_sndpack, "data packet", " sent");
	ANY(sppstat.spps_sndbyte, "data byte", " sent");
	ANY(sppstat.spps_sndrexmitpack, "data packet", " retransmitted");
	ANY(sppstat.spps_sndrexmitbyte, "data byte", " retransmitted");
	ANY(sppstat.spps_sndacks, "ack-only packet", " sent");
	ANY(sppstat.spps_sndprobe, "window probe", " sent");
	ANY(sppstat.spps_sndurg, "packet", " sent with URG only");
	ANY(sppstat.spps_sndwinup, "window update-only packet", " sent");
	ANY(sppstat.spps_sndctrl, "control (SYN|FIN|RST) packet", " sent");
	ANY(sppstat.spps_sndvoid, "request", " to send a non-existant packet");
	ANY(sppstat.spps_rcvtotal, "total packet", " received");
	ANY(sppstat.spps_rcvpack, "packet", " received in sequence");
	ANY(sppstat.spps_rcvbyte, "byte", " received in sequence");
	ANY(sppstat.spps_rcvbadsum, "packet", " received with ccksum errs");
	ANY(sppstat.spps_rcvbadoff, "packet", " received with bad offset");
	ANY(sppstat.spps_rcvshort, "packet", " received too short");
	ANY(sppstat.spps_rcvduppack, "duplicate-only packet", " received");
	ANY(sppstat.spps_rcvdupbyte, "duplicate-only byte", " received");
	ANY(sppstat.spps_rcvpartduppack, "packet", " with some duplicate data");
	ANY(sppstat.spps_rcvpartdupbyte, "dup. byte", " in part-dup. packet");
	ANY(sppstat.spps_rcvoopack, "out-of-order packet", " received");
	ANY(sppstat.spps_rcvoobyte, "out-of-order byte", " received");
	ANY(sppstat.spps_rcvpackafterwin, "packet", " with data after window");
	ANY(sppstat.spps_rcvbyteafterwin, "byte", " rcvd after window");
	ANY(sppstat.spps_rcvafterclose, "packet", " rcvd after 'close'");
	ANY(sppstat.spps_rcvwinprobe, "rcvd window probe packet", "");
	ANY(sppstat.spps_rcvdupack, "rcvd duplicate ack", "");
	ANY(sppstat.spps_rcvacktoomuch, "rcvd ack", " for unsent data");
	ANY(sppstat.spps_rcvackpack, "rcvd ack packet", "");
	ANY(sppstat.spps_rcvackbyte, "byte", " acked by rcvd acks");
	ANY(sppstat.spps_rcvwinupd, "rcvd window update packet", "");
E 7
}
I 7
#undef ANY
#define ANY(x,y,z)  ((x) ? printf("\t%d %s%s%s\n",x,y,plural(x),z) : 0)
E 7

/*
 * Dump IDP statistics structure.
 */
I 14
void
E 14
idp_stats(off, name)
D 16
	off_t off;
E 16
I 16
	u_long off;
E 16
	char *name;
{
	struct idpstat idpstat;

D 2
	if (off == 0) {
		printf("%sstat: symbol not in namelist\n", name);
E 2
I 2
	if (off == 0)
E 2
		return;
D 2
	}
E 2
D 12
	klseek(kmem, off, 0);
	read(kmem, (char *)&idpstat, sizeof (idpstat));
E 12
I 12
D 14
	kvm_read(off, (char *)&idpstat, sizeof (idpstat));
E 14
I 14
	kread(off, (char *)&idpstat, sizeof (idpstat));
E 14
E 12
I 4
	printf("%s:\n", name);
E 4
	ANY(idpstat.idps_toosmall, "packet", " smaller than a header");
	ANY(idpstat.idps_tooshort, "packet", " smaller than advertised");
	ANY(idpstat.idps_badsum, "packet", " with bad checksums");
}

D 7
static	char *((ns_errnames[])[2]) = {
	{"Unspecified Error", " at Destination"},
	{"Bad Checksum", " at Destination"},
	{"No Listener", " at Socket"},
	{"Packet", " Refused due to lack of space at Destination"},
	{"Unspecified Error", " while gatewayed"},
	{"Bad Checksum", " while gatewayed"},
	{"Packet", " forwarded too many times"},
	{"Packet", " too large to be forwarded"},
E 7
I 7
static	struct {
	u_short code;
	char *name;
	char *where;
} ns_errnames[] = {
	{0, "Unspecified Error", " at Destination"},
	{1, "Bad Checksum", " at Destination"},
	{2, "No Listener", " at Socket"},
	{3, "Packet", " Refused due to lack of space at Destination"},
	{01000, "Unspecified Error", " while gatewayed"},
	{01001, "Bad Checksum", " while gatewayed"},
	{01002, "Packet", " forwarded too many times"},
	{01003, "Packet", " too large to be forwarded"},
	{-1, 0, 0},
E 7
};

/*
 * Dump NS Error statistics structure.
 */
I 4
/*ARGSUSED*/
I 14
void
E 14
E 4
nserr_stats(off, name)
D 16
	off_t off;
E 16
I 16
	u_long off;
E 16
	char *name;
{
	struct ns_errstat ns_errstat;
	register int j;
	register int histoprint = 1;
	int z;

D 2
	if (off == 0) {
		printf("%sstat: symbol not in namelist\n", name);
E 2
I 2
	if (off == 0)
E 2
		return;
D 2
	}
E 2
D 12
	klseek(kmem, off, 0);
	read(kmem, (char *)&ns_errstat, sizeof (ns_errstat));
E 12
I 12
D 14
	kvm_read(off, (char *)&ns_errstat, sizeof (ns_errstat));
E 14
I 14
	kread(off, (char *)&ns_errstat, sizeof (ns_errstat));
E 14
E 12
	printf("NS error statistics:\n");
	ANY(ns_errstat.ns_es_error, "call", " to ns_error");
	ANY(ns_errstat.ns_es_oldshort, "error",
		" ignored due to insufficient addressing");
	ANY(ns_errstat.ns_es_oldns_err, "error request",
		" in response to error packets");
	ANY(ns_errstat.ns_es_tooshort, "error packet",
		" received incomplete");
	ANY(ns_errstat.ns_es_badcode, "error packet",
		" received of unknown type");
	for(j = 0; j < NS_ERR_MAX; j ++) {
		z = ns_errstat.ns_es_outhist[j];
		if (z && histoprint) {
			printf("Output Error Histogram:\n");
			histoprint = 0;
		}
D 7
		ANY(z, ns_errnames[j][0], ns_errnames[j][1]);
E 7
I 7
		ns_erputil(z, ns_errstat.ns_es_codes[j]);

E 7
	}
	histoprint = 1;
	for(j = 0; j < NS_ERR_MAX; j ++) {
		z = ns_errstat.ns_es_inhist[j];
		if (z && histoprint) {
			printf("Input Error Histogram:\n");
			histoprint = 0;
		}
D 7
		ANY(z, ns_errnames[j][0], ns_errnames[j][1]);
E 7
I 7
		ns_erputil(z, ns_errstat.ns_es_codes[j]);
E 7
	}
I 7
}
D 13
static
E 13
I 13

I 14
static void
E 14
E 13
ns_erputil(z, c)
I 14
	int z, c;
E 14
{
	int j;
	char codebuf[30];
	char *name, *where;
I 13

E 13
	for(j = 0;; j ++) {
		if ((name = ns_errnames[j].name) == 0)
			break;
		if (ns_errnames[j].code == c)
			break;
	}
	if (name == 0)  {
		if (c > 01000)
			where = "in transit";
		else
			where = "at destination";
		sprintf(codebuf, "Unknown XNS error code 0%o", c);
		name = codebuf;
D 14
	} else 
E 14
I 14
	} else
E 14
		where =  ns_errnames[j].where;
	ANY(z, name, where);
E 7
}
I 13

E 13
static struct sockaddr_ns ssns = {AF_NS};

I 14
static
E 14
char *ns_prpr(x)
D 13
struct ns_addr *x;
E 13
I 13
	struct ns_addr *x;
E 13
{
D 13
	extern char *ns_print();
E 13
	struct sockaddr_ns *sns = &ssns;
I 13
D 14
	extern char *ns_print();
E 14

E 13
	sns->sns_addr = *x;
D 14
	return(ns_print(sns));
E 14
I 14
	return(ns_print((struct sockaddr *)sns));
E 14
}
E 1
