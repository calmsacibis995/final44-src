h43647
s 00002/00002/00106
d D 8.1 93/06/06 15:44:22 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00106
d D 5.16 93/04/01 15:25:25 mckusick 17 16
c convert kinfo to sysctl
e
s 00004/00003/00104
d D 5.15 93/02/19 17:59:48 torek 16 15
c get unix domain path length right (from leres@ee.lbl.gov)
e
s 00006/00005/00101
d D 5.14 92/07/07 16:57:26 sklower 15 14
c not every value return in an nlist structure was being
c coerced to an (off_t) which was only being smashed back down to a (u_long)
c as an argument to kvm_read.  If you ask me nl.n_value ought to be a (void *)
c but since the type of nl.n_value and the second argument to kvm_read are
c the same I got fed up and changed all the off_t's to be that type (u_long).
e
s 00008/00004/00098
d D 5.13 92/07/06 15:36:19 sklower 14 13
c Multicast changes from lbl
e
s 00021/00036/00081
d D 5.12 92/05/27 18:11:56 sklower 13 12
c incorporate changes for new kvm interfaces from lbl
e
s 00002/00000/00115
d D 5.11 91/07/01 11:55:46 karels 12 11
c whackety-whack (unix domain is broken with dynamically linked files)
e
s 00002/00001/00113
d D 5.10 91/04/27 17:06:04 bostic 11 10
c  ANSI fixes; iso.c compiled without the #define KERNEL
e
s 00012/00014/00102
d D 5.9 90/06/18 17:20:58 sklower 10 9
c use kvm_nlist to avoid numerous lseeks of nlist; use kvm_read to avoid duplication.
e
s 00003/00013/00113
d D 5.8 90/06/18 14:29:44 karels 9 8
c (By Sklower) ... license terms replaced by sccs keyword;
e
s 00001/00001/00125
d D 5.7 89/09/25 15:45:16 karels 8 7
c mbuf changes (by sklower)
e
s 00012/00007/00114
d D 5.6 88/06/29 20:42:13 bostic 7 6
c install approved copyright notice
e
s 00009/00003/00112
d D 5.5 88/02/07 20:38:25 karels 6 5
c new copyrights
e
s 00010/00009/00105
d D 5.4 86/08/11 11:51:27 kupfer 5 4
c Some lint.
e
s 00006/00002/00108
d D 5.3 86/05/08 14:52:57 karels 4 3
c integrate unix domain, get the addresses right
e
s 00002/00002/00108
d D 5.2 86/02/01 19:23:14 mckusick 3 2
c unp_remaddr becomes unp_addr
e
s 00007/00001/00103
d D 5.1 85/06/04 15:47:30 dist 2 1
c Add copyright
e
s 00104/00000/00000
d D 1.1 84/06/03 11:13:27 sam 1 0
c date and time created 84/06/03 11:13:27 by sam
e
u
U
t
T
I 2
D 9
/*
E 9
I 9
/*-
E 9
D 6
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
D 7
 * Copyright (c) 1983,1988 Regents of the University of California.
E 7
I 7
D 18
 * Copyright (c) 1983, 1988 Regents of the University of California.
E 7
 * All rights reserved.
E 18
I 18
 * Copyright (c) 1983, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 18
 *
D 9
 * Redistribution and use in source and binary forms are permitted
D 7
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 7
I 7
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 7
E 6
 */

E 2
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif
E 2
I 2
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7
E 2

/*
 * Display protocol blocks in the unix domain.
 */
I 13
#include <kvm.h>
E 13
#include <sys/param.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/mbuf.h>
I 13
D 17
#include <sys/kinfo.h>
E 17
I 17
#include <sys/sysctl.h>
E 17
E 13
#include <sys/un.h>
#include <sys/unpcb.h>
D 11
#define	KERNEL
E 11
I 11
#define KERNEL
struct uio;
I 13
struct proc;
E 13
E 11
#include <sys/file.h>
I 14

#include <netinet/in.h>

#include <stdio.h>
E 14
I 12
D 13
struct file *file, *fileNFILE;
int nfile;
E 13
I 13
#include <stdlib.h>
#include "netstat.h"
E 13
E 12

D 13
int	Aflag;
D 10
int	kmem;
E 10
I 5
extern	char *calloc();
E 13
I 13
D 14
static void unixdomainpr __P((struct socket *, caddr_t));
E 14
I 14
static	void unixdomainpr __P((struct socket *, caddr_t));
E 14
E 13
E 5

D 13
unixpr(nfileaddr, fileaddr, unixsw)
	off_t nfileaddr, fileaddr;
E 13
I 13
D 14
struct file *file, *fileNFILE;
int nfiles;
E 14
I 14
D 16
struct	file *file, *fileNFILE;
int	nfiles;
E 16
I 16
static struct	file *file, *fileNFILE;
static int	nfiles;
E 16
E 14
extern	kvm_t *kvmd;

void
D 15
unixpr(unixsw)
E 13
	struct protosw *unixsw;
E 15
I 15
unixpr(off)
	u_long	off;
E 15
{
	register struct file *fp;
D 13
	struct file *filep;
E 13
	struct socket sock, *so = &sock;
I 13
	char *filebuf;
I 15
	struct protosw *unixsw = (struct protosw *)off;
E 15
E 13

D 13
	if (nfileaddr == 0 || fileaddr == 0) {
		printf("nfile or file not in namelist.\n");
		return;
	}
D 10
	klseek(kmem, nfileaddr, L_SET);
D 5
	if (read(kmem, &nfile, sizeof (nfile)) != sizeof (nfile)) {
E 5
I 5
	if (read(kmem, (char *)&nfile, sizeof (nfile)) != sizeof (nfile)) {
E 10
I 10
	if (kvm_read(nfileaddr, (char *)&nfile, sizeof (nfile)) !=
						sizeof (nfile)) {
E 10
E 5
		printf("nfile: bad read.\n");
		return;
	}
D 10
	klseek(kmem, fileaddr, L_SET);
D 5
	if (read(kmem, &filep, sizeof (filep)) != sizeof (filep)) {
E 5
I 5
	if (read(kmem, (char *)&filep, sizeof (filep)) != sizeof (filep)) {
E 10
I 10
	if (kvm_read(fileaddr, (char *)&filep, sizeof (filep))
						!= sizeof (filep)) {
E 10
E 5
		printf("File table address, bad read.\n");
		return;
	}
	file = (struct file *)calloc(nfile, sizeof (struct file));
	if (file == (struct file *)0) {
E 13
I 13
D 17
	filebuf = (char *)kvm_getfiles(kvmd, KINFO_FILE, 0, &nfiles);
E 17
I 17
	filebuf = (char *)kvm_getfiles(kvmd, KERN_FILE, 0, &nfiles);
E 17
	if (filebuf == 0) {
E 13
		printf("Out of memory (file table).\n");
		return;
	}
D 10
	klseek(kmem, (off_t)filep, L_SET);
D 5
	if (read(kmem, file, nfile * sizeof (struct file)) !=
E 5
I 5
	if (read(kmem, (char *)file, nfile * sizeof (struct file)) !=
E 5
	    nfile * sizeof (struct file)) {
E 10
I 10
D 13
	if (kvm_read((off_t)filep, (char *)file, nfile * sizeof (struct file))
					!= nfile * sizeof (struct file)) {
E 10
		printf("File table read error.\n");
		return;
	}
	fileNFILE = file + nfile;
E 13
I 13
	file = (struct file *)(filebuf + sizeof(fp));
	fileNFILE = file + nfiles;
E 13
	for (fp = file; fp < fileNFILE; fp++) {
		if (fp->f_count == 0 || fp->f_type != DTYPE_SOCKET)
			continue;
D 5
		klseek(kmem, fp->f_data, L_SET);
		if (read(kmem, so, sizeof (*so)) != sizeof (*so))
E 5
I 5
D 10
		klseek(kmem, (off_t)fp->f_data, L_SET);
		if (read(kmem, (char *)so, sizeof (*so)) != sizeof (*so))
E 10
I 10
D 13
		if (kvm_read((off_t)fp->f_data, (char *)so, sizeof (*so))
					!= sizeof (*so))
E 13
I 13
D 15
		if (kread((off_t)fp->f_data, (char *)so, sizeof (*so)))
E 15
I 15
		if (kread((u_long)fp->f_data, (char *)so, sizeof (*so)))
E 15
E 13
E 10
E 5
			continue;
		/* kludge */
		if (so->so_proto >= unixsw && so->so_proto <= unixsw + 2)
			if (so->so_pcb)
				unixdomainpr(so, fp->f_data);
	}
D 13
	free((char *)file);
E 13
}

static	char *socktype[] =
    { "#0", "stream", "dgram", "raw", "rdm", "seqpacket" };

I 13
static void
E 13
unixdomainpr(so, soaddr)
	register struct socket *so;
	caddr_t soaddr;
{
	struct unpcb unpcb, *unp = &unpcb;
	struct mbuf mbuf, *m;
I 4
	struct sockaddr_un *sa;
E 4
	static int first = 1;

D 5
	klseek(kmem, so->so_pcb, L_SET);
	if (read(kmem, unp, sizeof (*unp)) != sizeof (*unp))
E 5
I 5
D 10
	klseek(kmem, (off_t)so->so_pcb, L_SET);
	if (read(kmem, (char *)unp, sizeof (*unp)) != sizeof (*unp))
E 10
I 10
D 13
	if (kvm_read((off_t)so->so_pcb, (char *)unp, sizeof (*unp))
				!= sizeof (*unp))
E 13
I 13
D 15
	if (kread((off_t)so->so_pcb, (char *)unp, sizeof (*unp)))
E 15
I 15
	if (kread((u_long)so->so_pcb, (char *)unp, sizeof (*unp)))
E 15
E 13
E 10
E 5
		return;
D 3
	if (unp->unp_remaddr) {
E 3
I 3
	if (unp->unp_addr) {
E 3
		m = &mbuf;
D 3
		klseek(kmem, unp->unp_remaddr, L_SET);
E 3
I 3
D 5
		klseek(kmem, unp->unp_addr, L_SET);
E 3
		if (read(kmem, m, sizeof (*m)) != sizeof (*m))
E 5
I 5
D 10
		klseek(kmem, (off_t)unp->unp_addr, L_SET);
		if (read(kmem, (char *)m, sizeof (*m)) != sizeof (*m))
E 10
I 10
D 13
		if (kvm_read((off_t)unp->unp_addr, (char *)m, sizeof (*m))
				!= sizeof (*m))
E 13
I 13
D 15
		if (kread((off_t)unp->unp_addr, (char *)m, sizeof (*m)))
E 15
I 15
		if (kread((u_long)unp->unp_addr, (char *)m, sizeof (*m)))
E 15
E 13
E 10
E 5
			m = (struct mbuf *)0;
I 4
D 8
		sa = mtod(m, struct sockaddr_un *);
E 8
I 8
		sa = (struct sockaddr_un *)(m->m_dat);
E 8
E 4
	} else
		m = (struct mbuf *)0;
	if (first) {
I 4
		printf("Active UNIX domain sockets\n");
E 4
		printf(
D 4
"%-8.8s %-6.6s %-6.6s %-6.6s %8.8s %8.8s %8.8s %8.8s Remaddr\n",
E 4
I 4
"%-8.8s %-6.6s %-6.6s %-6.6s %8.8s %8.8s %8.8s %8.8s Addr\n",
E 4
		    "Address", "Type", "Recv-Q", "Send-Q",
		    "Inode", "Conn", "Refs", "Nextref");
		first = 0;
	}
	printf("%8x %-6.6s %6d %6d %8x %8x %8x %8x",
	    soaddr, socktype[so->so_type], so->so_rcv.sb_cc, so->so_snd.sb_cc,
D 9
	    unp->unp_inode, unp->unp_conn,
E 9
I 9
	    unp->unp_vnode, unp->unp_conn,
E 9
	    unp->unp_refs, unp->unp_nextref);
	if (m)
D 4
		printf(" %.*s", m->m_len, mtod(m, char *));
E 4
I 4
D 14
		printf(" %.*s", m->m_len - sizeof(sa->sun_family),
E 14
I 14
D 16
		printf(" %.*s", m->m_len - (int)sizeof(sa->sun_family),
E 16
I 16
		printf(" %.*s",
		    m->m_len - (int)(sizeof(*sa) - sizeof(sa->sun_path)),
E 16
E 14
		    sa->sun_path);
E 4
	putchar('\n');
}
E 1
