h02418
s 00002/00002/00113
d R 8.1 93/06/12 09:17:07 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00113
d D 5.16 93/06/12 09:16:57 bostic 19 17
c netimp was deprecated
e
s 00002/00002/00113
d R 8.1 93/06/06 15:43:30 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00112
d D 5.15 92/07/07 16:57:14 sklower 17 16
c not every value return in an nlist structure was being
c coerced to an (off_t) which was only being smashed back down to a (u_long)
c as an argument to kvm_read.  If you ask me nl.n_value ought to be a (void *)
c but since the type of nl.n_value and the second argument to kvm_read are
c the same I got fed up and changed all the off_t's to be that type (u_long).
e
s 00002/00000/00113
d D 5.14 92/07/06 15:36:15 sklower 16 15
c Multicast changes from lbl
e
s 00011/00011/00102
d D 5.13 92/05/27 18:11:50 sklower 15 14
c incorporate changes for new kvm interfaces from lbl
e
s 00001/00001/00112
d D 5.12 91/02/02 18:28:23 torek 14 13
c +=, not ==, to advance by one imp_softc (as noted by gcc -W)
e
s 00007/00010/00106
d D 5.11 90/06/18 17:20:21 sklower 13 12
c use kvm_nlist to avoid numerous lseeks of nlist; use kvm_read to avoid duplication.
e
s 00001/00011/00115
d D 5.10 90/06/01 17:07:23 bostic 12 11
c new copyright notice
e
s 00002/00002/00124
d D 5.9 89/09/25 13:13:38 sklower 11 10
c fix for new mbufs for printing imp stats
e
s 00012/00007/00114
d D 5.8 88/06/29 20:41:59 bostic 10 9
c install approved copyright notice
e
s 00007/00005/00114
d D 5.7 88/02/08 11:02:03 karels 9 8
c print in/out totals for impstats
e
s 00009/00003/00110
d D 5.6 88/02/07 20:38:13 karels 8 7
c new copyrights
e
s 00047/00013/00066
d D 5.5 88/02/07 20:25:00 karels 7 6
c new IMP stuff
e
s 00009/00004/00070
d D 5.4 88/02/06 16:31:49 karels 6 5
c new IMP host entries
e
s 00003/00004/00071
d D 5.3 86/08/11 11:50:29 kupfer 5 4
c Some lint.
e
s 00000/00003/00075
d D 5.2 85/09/27 19:23:58 karels 4 3
c remove unused hostent stuff; confuses h_addr
e
s 00008/00002/00070
d D 5.1 85/06/04 15:47:57 dist 3 2
c Add copyright
e
s 00005/00003/00067
d D 4.2 82/11/14 15:11:19 sam 2 1
c convert to 4.1c directory layout
e
s 00070/00000/00000
d D 4.1 82/08/25 22:21:38 sam 1 0
c date and time created 82/08/25 22:21:38 by sam
e
u
U
t
T
I 3
/*
D 8
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
D 10
 * Copyright (c) 1983,1988 Regents of the University of California.
E 10
I 10
 * Copyright (c) 1983, 1988 Regents of the University of California.
E 10
 * All rights reserved.
 *
D 12
 * Redistribution and use in source and binary forms are permitted
D 10
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 10
I 10
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
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 10
E 8
 */

E 3
I 1
#ifndef lint
D 3
static char sccsid[] = "%W% %E%";
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 10
#endif not lint
E 10
I 10
#endif /* not lint */
E 10
E 3

D 11
#include <sys/types.h>
E 11
I 11
#include <sys/param.h>
I 15
#include <sys/protosw.h>
E 15
E 11
#include <sys/mbuf.h>
I 6
#include <sys/socket.h>
E 6
D 2
#include <net/in.h>
#include <net/if_imp.h>
#include <net/if_imphost.h>
E 2
I 2

I 6
#include <net/if.h>

E 6
#include <netinet/in.h>
D 19
#include <netimp/if_imp.h>
#include <netimp/if_imphost.h>
E 19
I 19
#include <deprecated/netimp/if_imp.h>
#include <deprecated/netimp/if_imphost.h>
E 19

I 16
#include <stdio.h>

E 16
E 2
D 4
#include <netdb.h>

E 4
D 15
extern	int kmem;
extern 	int nflag;
extern	char *inetname();
E 15
I 15
#include "netstat.h"
E 15

/*
 * Print the host tables associated with the ARPANET IMP.
 * Symbolic addresses are shown unless the nflag is given.
 */
I 15
void
E 15
D 7
hostpr(hostsaddr)
	off_t hostsaddr;
E 7
I 7
hostpr(impsoftcaddr, nimpaddr)
D 17
	off_t impsoftcaddr, nimpaddr;
E 17
I 17
	u_long impsoftcaddr, nimpaddr;
E 17
E 7
{
D 15
	struct mbuf *hosts, mb;
E 15
I 15
	struct mbuf mb;
E 15
I 7
	struct imp_softc imp_softc;
E 7
	register struct mbuf *m;
	register struct hmbuf *mh;
	register struct host *hp;
D 4
	struct hostent *p;
E 4
	char flagbuf[10], *flags;
I 7
	int i, nimp;
E 7
D 5
	int first = 1;
E 5

D 7
	if (hostsaddr == 0) {
		printf("hosts: symbol not in namelist\n");
E 7
I 7
	if (impsoftcaddr == 0) {
		printf("imp_softc: symbol not in namelist\n");
E 7
		return;
	}
D 7
	klseek(kmem, hostsaddr, 0);
D 5
	read(kmem, &hosts, sizeof (hosts));
E 5
I 5
	read(kmem, (char *)&hosts, sizeof (hosts));
E 5
	m = hosts;
	printf("IMP Host Table\n");
D 6
	printf("%-5.5s %-15.15s %-4.4s %-9.9s %-4.4s %s\n",
		"Flags", "Host", "Qcnt", "Q Address", "RFNM", "Timer");
E 6
I 6
	printf("%-4.4s %-5.5s %-6.6s %-8.8s %-4.4s %-9.9s %-4.4s %s\n", "Unit",
		"Flags", "Host", "Imp", "Qcnt", "Q Address", "RFNM", "Timer");
E 6
	while (m) {
E 7
I 7
	if (nimpaddr == 0) {
		printf("nimp: symbol not in namelist\n");
		return;
	}
D 13
	klseek(kmem, nimpaddr, 0);
	read(kmem, (char *)&nimp, sizeof (nimp));
	klseek(kmem, impsoftcaddr, 0);
E 13
I 13
D 15
	kvm_read(nimpaddr, (char *)&nimp, sizeof (nimp));
E 15
I 15
	kread(nimpaddr, (char *)&nimp, sizeof (nimp));
E 15
E 13
	for (i = 0; i < nimp; i++) {
D 13
	    read(kmem, (char *)&imp_softc, sizeof (imp_softc));
E 13
I 13
D 15
	    kvm_read(impsoftcaddr, (char *)&imp_softc, sizeof (imp_softc));
E 15
I 15
	    kread(impsoftcaddr, (char *)&imp_softc, sizeof (imp_softc));
E 15
	    impsoftcaddr += sizeof (imp_softc);
E 13
	    m = imp_softc.imp_hosts;
	    printf("IMP%d Host Table\n", i);
	    printf("%-5.5s %-6.6s %-8.8s %-4.4s %-9.9s %-4.4s %s\n", "Flags",
	        "Host", "Imp", "Qcnt", "Q Address", "RFNM", "Timer");
	    while (m) {
E 7
D 5
		klseek(kmem, m, 0);
		read(kmem, &mb, sizeof (mb));
E 5
I 5
D 13
		klseek(kmem, (off_t)m, 0);
		read(kmem, (char *)&mb, sizeof (mb));
E 13
I 13
D 15
		kvm_read((off_t)m, (char *)&mb, sizeof (mb));
E 15
I 15
D 17
		kread((off_t)m, (char *)&mb, sizeof (mb));
E 17
I 17
		kread((u_long)m, (char *)&mb, sizeof (mb));
E 17
E 15
E 13
E 5
		m = &mb;
D 11
		mh = mtod(m, struct hmbuf *);
E 11
I 11
		mh = (struct hmbuf *)(m->m_dat);
E 11
		if (mh->hm_count == 0) {
			m = m->m_next;
			continue;
		}
		for (hp = mh->hm_hosts; hp < mh->hm_hosts + HPMBUF; hp++) {
			if ((hp->h_flags&HF_INUSE) == 0 && hp->h_timer == 0)
				continue;
			flags = flagbuf;
			*flags++ = hp->h_flags&HF_INUSE ? 'A' : 'F';
			if (hp->h_flags&HF_DEAD)
				*flags++ = 'D';
			if (hp->h_flags&HF_UNREACH)
				*flags++ = 'U';
			*flags = '\0';
D 6
			printf("%-5.5s %-15.15s %-4d %-9x %-4d %d\n",
E 6
I 6
D 7
			printf("imp%-1d %-5.5s %-6d %-8d %-4d %-9x %-4d %d\n",
				hp->h_unit,
E 7
I 7
D 15
			printf("%-5.5s %-6d %-8d %-4d %-9x %-4d %d\n",
E 15
I 15
			printf("%-5.5s %-6d %-8d %-4u %-9x %-4u %u\n",
E 15
E 7
E 6
				flagbuf,
D 6
				inetname(hp->h_addr),
E 6
I 6
				hp->h_host,
				ntohs(hp->h_imp),
E 6
				hp->h_qcnt,
				hp->h_q,
				hp->h_rfnm,
				hp->h_timer);
		}
		m = m->m_next;
I 7
	    }
	}
}

I 15
void
E 15
impstats(impsoftcaddr, nimpaddr)
D 17
	off_t impsoftcaddr, nimpaddr;
E 17
I 17
	u_long impsoftcaddr, nimpaddr;
E 17
{
	struct imp_softc imp_softc;
	int i, nimp;
D 15
	extern char *plural();
E 15

	if (impsoftcaddr == 0 || nimpaddr == 0)
		return;
D 13
	klseek(kmem, nimpaddr, 0);
	read(kmem, (char *)&nimp, sizeof (nimp));
	klseek(kmem, impsoftcaddr, 0);
E 13
I 13
D 15
	kvm_read(nimpaddr, (char *)&nimp, sizeof (nimp));
E 15
I 15
	kread(nimpaddr, (char *)&nimp, sizeof (nimp));
E 15
E 13
	for (i = 0; i < nimp; i++) {
D 13
		read(kmem, (char *)&imp_softc, sizeof (imp_softc));
E 13
I 13
D 15
		kvm_read(impsoftcaddr, (char *)&imp_softc, sizeof (imp_softc));
E 15
I 15
		kread(impsoftcaddr, (char *)&imp_softc, sizeof (imp_softc));
E 15
D 14
		impsoftcaddr == sizeof(imp_softc);
E 14
I 14
		impsoftcaddr += sizeof(imp_softc);
E 14
E 13
		printf("imp%d statistics:\n", i);
#define	p(f, m)		printf(m, imp_softc.f, plural(imp_softc.f))
D 9
		printf("\t%d times blocked at least %d sec.\n",
E 9
I 9
		p(imp_if.if_ipackets, "\t%u input message%s\n");
		p(imp_if.if_opackets, "\t%u output message%s\n");
		printf("\t%u times output blocked at least %d sec.\n",
E 9
		    imp_softc.imp_block, IMP_OTIMER);
D 9
		p(imp_incomplete, "\t%d \"incomplete\" message%s\n");
		p(imp_lostrfnm, "\t%d lost RFNM message%s\n");
		p(imp_badrfnm, "\t%d late/bogus RFNM/incomplete message%s\n");
		p(imp_garbage, "\t%d unknown message type%s\n");
E 9
I 9
		p(imp_incomplete, "\t%u \"incomplete\" message%s\n");
		p(imp_lostrfnm, "\t%u lost RFNM message%s\n");
		p(imp_badrfnm, "\t%u late/bogus RFNM/incomplete message%s\n");
		p(imp_garbage, "\t%u unknown message type%s\n");
E 9
E 7
	}
}
E 1
