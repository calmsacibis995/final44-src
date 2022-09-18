h61557
s 00002/00002/00094
d D 8.1 93/06/06 15:43:57 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00095
d D 5.12 92/07/07 16:57:21 sklower 22 21
c not every value return in an nlist structure was being
c coerced to an (off_t) which was only being smashed back down to a (u_long)
c as an argument to kvm_read.  If you ask me nl.n_value ought to be a (void *)
c but since the type of nl.n_value and the second argument to kvm_read are
c the same I got fed up and changed all the off_t's to be that type (u_long).
e
s 00012/00008/00084
d D 5.11 92/05/27 18:11:58 sklower 21 20
c incorporate changes for new kvm interfaces from lbl
e
s 00002/00002/00090
d D 5.10 91/01/30 11:12:22 karels 20 19
c CLBYTES should be MCLBYTES
e
s 00002/00003/00090
d D 5.9 90/06/18 17:20:45 sklower 19 18
c use kvm_nlist to avoid numerous lseeks of nlist; use kvm_read to avoid duplication.
e
s 00001/00011/00092
d D 5.8 90/06/01 17:08:01 bostic 18 17
c new copyright notice
e
s 00013/00015/00090
d D 5.7 89/09/25 15:52:38 karels 17 16
c checkpoint for alpha tape (by sklower)
e
s 00012/00007/00093
d D 5.6 88/06/29 20:42:08 bostic 16 15
c install approved copyright notice
e
s 00009/00003/00091
d D 5.5 88/02/07 20:38:21 karels 15 14
c new copyrights
e
s 00001/00004/00093
d D 5.4 87/07/27 17:27:08 mckusick 14 13
c MT_ZOMBIE is gone; recalculate mbuf space used
e
s 00012/00008/00085
d D 5.3 87/02/03 22:19:36 karels 13 12
c new statistics
e
s 00001/00001/00092
d D 5.2 86/08/11 11:50:53 kupfer 12 11
c Some lint.
e
s 00008/00002/00085
d D 5.1 85/06/04 15:45:46 dist 11 10
c Add copyright
e
s 00021/00001/00066
d D 4.8 85/04/07 16:45:30 kupfer 10 9
c Know about MT_IFADDR mbufs.  Also, be more graceful if there
c are mbuf types defined that we don't know about.  The code could be
c simplified some, at the cost of breaking whenever old type constants
c get shuffled around.
e
s 00002/00002/00065
d D 4.7 84/11/16 17:40:54 karels 9 8
c bogus mbuf calculations
e
s 00006/00007/00061
d D 4.6 84/10/05 15:18:52 sam 8 7
c m_mfree no longer exists
e
s 00036/00005/00032
d D 4.5 82/12/18 19:13:27 sam 7 4
c new mbuf stats
e
s 00035/00005/00032
d R 4.5 82/12/18 19:09:05 sam 6 4
c new mbuf stats
e
s 00028/00003/00034
d R 4.5 82/12/18 16:45:46 sam 5 4
c print typed mbuf accounting
e
s 00004/00005/00033
d D 4.4 82/12/09 20:56:30 sam 4 3
c prettier
e
s 00001/00002/00037
d D 4.3 82/12/06 20:43:56 sam 3 2
c messed up % calculation (should also round probably)
e
s 00018/00007/00021
d D 4.2 82/12/05 23:51:08 sam 2 1
c make more interesting
e
s 00028/00000/00000
d D 4.1 82/08/25 22:21:46 sam 1 0
c date and time created 82/08/25 22:21:46 by sam
e
u
U
t
T
I 11
/*
D 15
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 15
I 15
D 16
 * Copyright (c) 1983,1988 Regents of the University of California.
E 16
I 16
D 23
 * Copyright (c) 1983, 1988 Regents of the University of California.
E 16
 * All rights reserved.
E 23
I 23
 * Copyright (c) 1983, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 23
 *
D 18
 * Redistribution and use in source and binary forms are permitted
D 16
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 16
I 16
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
E 18
I 18
 * %sccs.include.redist.c%
E 18
E 16
E 15
 */

E 11
I 1
#ifndef lint
D 11
static char sccsid[] = "%W% %E%";
#endif
E 11
I 11
static char sccsid[] = "%W% (Berkeley) %G%";
D 16
#endif not lint
E 16
I 16
#endif /* not lint */
E 16
E 11

I 10
D 21
#include <stdio.h>
E 21
E 10
D 2
#include <sys/types.h>
E 2
I 2
#include <sys/param.h>
I 21
#include <sys/protosw.h>
#include <sys/socket.h>
E 21
E 2
#include <sys/mbuf.h>
I 21

#include <stdio.h>
#include "netstat.h"

E 21
I 10
#define	YES	1
typedef int bool;
E 10

struct	mbstat mbstat;
D 19
extern	int kmem;
E 19

I 7
static struct mbtypes {
	int	mt_type;
	char	*mt_name;
} mbtypes[] = {
	{ MT_DATA,	"data" },
I 17
	{ MT_OOBDATA,	"oob data" },
	{ MT_CONTROL,	"ancillary data" },
E 17
	{ MT_HEADER,	"packet headers" },
D 17
	{ MT_SOCKET,	"socket structures" },
	{ MT_PCB,	"protocol control blocks" },
	{ MT_RTABLE,	"routing table entries" },
	{ MT_HTABLE,	"IMP host table entries" },
E 17
I 17
	{ MT_SOCKET,	"socket structures" },			/* XXX */
	{ MT_PCB,	"protocol control blocks" },		/* XXX */
	{ MT_RTABLE,	"routing table entries" },		/* XXX */
	{ MT_HTABLE,	"IMP host table entries" },		/* XXX */
E 17
D 8
#ifdef notdef
E 8
	{ MT_ATABLE,	"address resolution tables" },
D 8
#endif
E 8
D 17
	{ MT_FTABLE,	"fragment reassembly queue headers" },
E 17
I 17
	{ MT_FTABLE,	"fragment reassembly queue headers" },	/* XXX */
E 17
	{ MT_SONAME,	"socket names and addresses" },
D 14
	{ MT_ZOMBIE,	"zombie process information" },
E 14
	{ MT_SOOPTS,	"socket options" },
I 8
	{ MT_RIGHTS,	"access rights" },
I 10
D 17
	{ MT_IFADDR,	"interface addresses" }, 
E 17
I 17
D 21
	{ MT_IFADDR,	"interface addresses" }, 		/* XXX */
E 21
I 21
	{ MT_IFADDR,	"interface addresses" },		/* XXX */
E 21
E 17
E 10
E 8
	{ 0, 0 }
};

I 10
int nmbtypes = sizeof(mbstat.m_mtypes) / sizeof(short);
bool seen[256];			/* "have we seen this type yet?" */

E 10
E 7
/*
 * Print mbuf statistics.
 */
I 21
void
E 21
mbpr(mbaddr)
D 22
	off_t mbaddr;
E 22
I 22
	u_long mbaddr;
E 22
{
I 2
D 7
	register int totmem, totfree;
E 7
I 7
	register int totmem, totfree, totmbufs;
I 10
	register int i;
E 10
	register struct mbtypes *mp;
E 7

I 10
	if (nmbtypes != 256) {
D 21
		fprintf(stderr, "unexpected change to mbstat; check source\n");
E 21
I 21
		fprintf(stderr,
		    "%s: unexpected change to mbstat; check source\n", prog);
E 21
		return;
	}
E 10
E 2
	if (mbaddr == 0) {
D 21
		printf("mbstat: symbol not in namelist\n");
E 21
I 21
		fprintf(stderr, "%s: mbstat: symbol not in namelist\n", prog);
E 21
		return;
	}
D 2
	printf("mbufs:");
E 2
I 2
D 4
	printf("memory utilization:\n");
E 4
E 2
D 19
	klseek(kmem, mbaddr, 0);
D 2
	if (read(kmem, &mbstat, sizeof (mbstat)) == sizeof (mbstat))
		printf(
	" mbufs %d mbfree %d clusters %d clfree %d drops %d\n",
		mbstat.m_mbufs, mbstat.m_mbfree,
		mbstat.m_clusters, mbstat.m_clfree, mbstat.m_drops);
E 2
I 2
D 12
	if (read(kmem, &mbstat, sizeof (mbstat)) != sizeof (mbstat)) {
E 12
I 12
	if (read(kmem, (char *)&mbstat, sizeof (mbstat)) != sizeof (mbstat)) {
E 19
I 19
D 21
	if (kvm_read(mbaddr, (char *)&mbstat, sizeof (mbstat))
						!= sizeof (mbstat)) {
E 19
E 12
		printf("mbstat: bad read\n");
E 21
I 21
	if (kread(mbaddr, (char *)&mbstat, sizeof (mbstat)))
E 21
		return;
D 21
	}
E 21
D 4
	printf("\t%d/%d mbufs in use\n", mbstat.m_mbufs - mbstat.m_mbfree,
E 4
I 4
D 7
	printf("%d/%d mbufs in use\n", mbstat.m_mbufs - mbstat.m_mbfree,
E 4
		mbstat.m_mbufs);
E 7
I 7
D 13
	printf("%d/%d mbufs in use:\n",
E 13
I 13
D 17
	printf("%u/%u mbufs in use:\n",
E 13
D 8
		mbstat.m_mbufs - mbstat.m_mbfree, mbstat.m_mbufs);
E 8
I 8
		mbstat.m_mbufs - mbstat.m_mtypes[MT_FREE], mbstat.m_mbufs);
E 17
E 8
	totmbufs = 0;
	for (mp = mbtypes; mp->mt_name; mp++)
I 17
		totmbufs += mbstat.m_mtypes[mp->mt_type];
	printf("%u mbufs in use:\n", totmbufs);
	for (mp = mbtypes; mp->mt_name; mp++)
E 17
		if (mbstat.m_mtypes[mp->mt_type]) {
I 10
			seen[mp->mt_type] = YES;
E 10
D 13
			printf("\t%d mbufs allocated to %s\n",
E 13
I 13
			printf("\t%u mbufs allocated to %s\n",
E 13
D 10
				mbstat.m_mtypes[mp->mt_type], mp->mt_name);
E 10
I 10
			    mbstat.m_mtypes[mp->mt_type], mp->mt_name);
E 10
D 17
			totmbufs += mbstat.m_mtypes[mp->mt_type];
E 17
I 10
		}
	seen[MT_FREE] = YES;
	for (i = 0; i < nmbtypes; i++)
		if (!seen[i] && mbstat.m_mtypes[i]) {
D 13
			printf("\t%d mbufs allocated to <mbuf type %d>\n",
E 13
I 13
			printf("\t%u mbufs allocated to <mbuf type %d>\n",
E 13
			    mbstat.m_mtypes[i], i);
D 17
			totmbufs += mbstat.m_mtypes[i];
E 17
E 10
		}
D 8
	if (totmbufs != mbstat.m_mbufs - mbstat.m_mbfree)
E 8
I 8
D 17
	if (totmbufs != mbstat.m_mbufs - mbstat.m_mtypes[MT_FREE])
E 8
D 13
		printf("*** %d mbufs missing ***\n",
E 13
I 13
		printf("*** %u mbufs missing ***\n",
E 13
D 8
			(mbstat.m_mbufs - mbstat.m_mbfree) - totmbufs);
E 8
I 8
			(mbstat.m_mbufs - mbstat.m_mtypes[MT_FREE]) - totmbufs);
E 17
E 8
E 7
D 4
	printf("\t%d/%d mapped pages in use\n",
E 4
I 4
D 13
	printf("%d/%d mapped pages in use\n",
E 13
I 13
	printf("%u/%u mapped pages in use\n",
E 13
E 4
		mbstat.m_clusters - mbstat.m_clfree, mbstat.m_clusters);
D 4
	printf("\t%d requests for memory denied\n", mbstat.m_drops);
E 4
I 4
D 7
	printf("%d requests for memory denied\n", mbstat.m_drops);
E 7
E 4
D 8
	totmem = mbstat.m_mbufs * MSIZE + mbstat.m_clusters * CLBYTES;
	totfree = mbstat.m_mbfree * MSIZE + mbstat.m_clusters * CLBYTES;
E 8
I 8
D 9
	totmem = totmbufs * MSIZE + mbstat.m_clusters * CLBYTES;
	totfree = mbstat.m_mtypes[MT_FREE]*MSIZE + mbstat.m_clusters * CLBYTES;
E 9
I 9
D 13
	totmem = mbstat.m_mbufs * MSIZE + mbstat.m_clusters * CLBYTES;
E 13
I 13
D 14
	printf("%u interface pages allocated\n", mbstat.m_space);
	totmem = mbstat.m_mbufs * MSIZE + mbstat.m_clusters * CLBYTES +
	    mbstat.m_space * CLBYTES;
E 14
I 14
D 17
	totmem = mbstat.m_mbufs * MSIZE + mbstat.m_clusters * CLBYTES;
E 14
E 13
	totfree = mbstat.m_mtypes[MT_FREE]*MSIZE + mbstat.m_clfree * CLBYTES;
E 17
I 17
D 20
	totmem = totmbufs * MSIZE + mbstat.m_clusters * CLBYTES;
	totfree = mbstat.m_clfree * CLBYTES;
E 20
I 20
	totmem = totmbufs * MSIZE + mbstat.m_clusters * MCLBYTES;
	totfree = mbstat.m_clfree * MCLBYTES;
E 20
E 17
E 9
E 8
D 4
	printf("\t%dKbytes allocated to network (%d%% in use)\n",
E 4
I 4
D 7
	printf("%dKbytes allocated to network (%d%% in use)\n",
E 7
I 7
D 13
	printf("%d Kbytes allocated to network (%d%% in use)\n",
E 13
I 13
	printf("%u Kbytes allocated to network (%d%% in use)\n",
E 13
E 7
E 4
D 3
		totmem / 1024,
		(totmem - totfree + totmem - 1) / totmem);
E 3
I 3
		totmem / 1024, (totmem - totfree) * 100 / totmem);
I 7
D 13
	printf("%d requests for memory denied\n", mbstat.m_drops);
E 13
I 13
	printf("%u requests for memory denied\n", mbstat.m_drops);
	printf("%u requests for memory delayed\n", mbstat.m_wait);
	printf("%u calls to protocol drain routines\n", mbstat.m_drain);
E 13
E 7
E 3
E 2
}
E 1
