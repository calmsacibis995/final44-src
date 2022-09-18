h49169
s 00002/00002/00285
d D 8.2 93/09/23 19:37:25 bostic 21 20
c changes for 4.4BSD-Lite requested by USL
e
s 00005/00005/00282
d D 8.1 93/06/06 14:41:02 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00285
d D 5.16 93/04/28 10:43:13 bostic 19 18
c <sys/kinfo_proc.h> information moved to <sys/sysctl.h>
e
s 00002/00002/00285
d D 5.15 93/03/31 17:27:39 mckusick 18 17
c convert from kinfo to sysctl
e
s 00005/00002/00282
d D 5.14 92/06/30 09:05:20 bostic 17 16
c assume untouched page if read fail in datadump
e
s 00187/00125/00097
d D 5.13 92/06/29 18:57:07 bostic 16 15
c general cleanup and ANSI-fication; should be no real changes
e
s 00001/00033/00221
d D 5.12 92/06/19 16:50:39 mccanne 15 14
c use sccs include to snarf copyright
e
s 00197/00374/00057
d D 5.11 92/06/19 16:36:34 mccanne 14 13
c port to new kvm interface
e
s 00001/00000/00430
d D 5.10 91/05/02 16:26:01 bostic 13 12
c I lied, it needs user.h (actually, I was lied to...)
e
s 00000/00001/00430
d D 5.9 91/04/27 16:18:55 bostic 12 11
c doesn't need user.h anymore
e
s 00001/00000/00430
d D 5.8 91/03/29 14:27:48 marc 11 10
c add exit code
e
s 00031/00011/00399
d D 5.7 91/02/06 22:46:16 torek 10 9
c fix gcc-detected lint
e
s 00001/00011/00409
d D 5.6 90/06/01 16:02:57 bostic 9 8
c new copyright notice
e
s 00003/00004/00417
d D 5.5 90/02/20 16:10:39 bostic 8 7
c re-order the includes for gcc
e
s 00017/00006/00404
d D 5.4 88/09/15 14:40:21 bostic 7 6
c add Berkeley specific copyright
e
s 00002/00004/00408
d D 5.3 87/03/30 13:41:03 karels 6 5
c so what if it's exiting?
e
s 00001/00001/00411
d D 5.2 85/05/31 09:15:23 dist 5 4
c Add copyright
e
s 00013/00001/00399
d D 5.1 85/05/31 09:13:53 dist 4 3
c Add copyright
e
s 00012/00005/00388
d D 4.3 83/05/22 17:30:57 sam 3 2
c changes for new swap area organization
e
s 00001/00001/00392
d D 4.2 82/12/24 12:54:53 sam 2 1
c header files moved around a bit
e
s 00393/00000/00000
d D 4.1 82/10/22 13:35:05 mckusick 1 0
c date and time created 82/10/22 13:35:05 by mckusick
e
u
U
t
T
I 4
D 14
/*
D 7
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * Copyright (c) 1982 The Regents of the University of California.
E 14
I 14
/*-
D 16
 * Copyright (c) 1992 Regents of the University of California.
E 16
I 16
D 20
 * Copyright (c) 1992 The Regents of the University of California.
E 16
E 14
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
D 9
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 9
I 9
D 14
 * %sccs.include.redist.c%
E 9
E 7
 */

E 4
I 1
D 3
/* Copyright (c) 1982 Regents of the University of California */
E 3
I 3
#ifndef lint
I 4
char copyright[] =
D 5
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 5
I 5
D 7
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 7
I 7
"%Z% Copyright (c) 1982 The Regents of the University of California.\n\
E 7
E 5
 All rights reserved.\n";
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7

#ifndef lint
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif
E 4
I 4
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7
E 4
E 3

D 3
static char sccsid[] = "%W%	(Berkeley)	%G%";

E 3
/*
 * gcore - get core images of running processes
 *
 * Author: Eric Cooper
 * Written: Fall 1981.
 *
E 14
I 14
D 15
 * Originally written by Eric Cooper in Fall 1981.
E 14
 * Inspired by a version 6 program by Len Levin, 1978.
 * Several pieces of code lifted from Bill Joy's 4BSD ps.
I 14
 * Most recently, hacked beyond recognition for 4.4BSD by Steven McCanne,
 * Lawrence Berkeley Laboratory.
E 14
 *
E 15
D 14
 * Permission to copy or modify this program in whole or in part is hereby
 * granted, provided that the above credits are preserved.
E 14
I 14
D 16
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
E 14
 *
E 16
D 14
 * This code performs a simple simulation of the virtual memory system in user
 * code.  If the virtual memory system changes, this program must be modified
 * accordingly.  It must also be recompiled whenever system data structures
 * change.
E 14
I 14
D 15
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
 *      This product includes software developed by the University of
 *      California, Lawrence Berkeley Laboratory and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
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
E 15
I 15
 * %sccs.include.redist.c%
E 15
E 14
 */
D 8
#include <stdio.h>
#include <nlist.h>
E 8
I 8
D 14
#include <machine/pte.h>
E 14
I 14

I 16
#ifndef lint
D 20
char copyright[] =
"%Z% Copyright (c) 1992 The Regents of the University of California.\n\
 All rights reserved.\n";
E 20
I 20
static char copyright[] =
"%Z% Copyright (c) 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 20
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 16
/*
D 16
 * gcore - get core images of running processes
E 16
I 16
 * Originally written by Eric Cooper in Fall 1981.
 * Inspired by a version 6 program by Len Levin, 1978.
 * Several pieces of code lifted from Bill Joy's 4BSD ps.
 * Most recently, hacked beyond recognition for 4.4BSD by Steven McCanne,
 * Lawrence Berkeley Laboratory.
 *
 * Portions of this software were developed by the Computer Systems
 * Engineering group at Lawrence Berkeley Laboratory under DARPA
 * contract BG 91-66 and contributed to Berkeley.
E 16
 */
D 16
#include <stdio.h>
#include <limits.h>
#include <kvm.h>
#include <a.out.h>
E 16
I 16
D 19

E 19
E 16
E 14
E 8
#include <sys/param.h>
I 13
D 14
#include <sys/user.h>
E 14
I 14
#include <sys/time.h>
D 16
#include <sys/file.h>
E 16
I 16
#include <sys/stat.h>
E 16
E 14
E 13
D 8
#include <sys/dir.h>
E 8
D 12
#include <sys/user.h>
E 12
#include <sys/proc.h>
D 2
#include <sys/pte.h>
E 2
I 2
D 8
#include <machine/pte.h>
E 8
E 2
D 14
#include <sys/vm.h>
#include <setjmp.h>
I 8
#include <stdio.h>
#include <nlist.h>
I 10
#include <varargs.h>
E 14
I 14
#include <sys/user.h>
D 18
#include <sys/kinfo.h>
E 18
I 18
#include <sys/sysctl.h>
E 18
D 19
#include <sys/kinfo_proc.h>
E 19
I 19

E 19
#include <machine/vmparam.h>
E 14
E 10
E 8

D 14
/* Various macros for efficiency. */
E 14
I 14
D 16
kvm_t *kd;
E 16
I 16
#include <a.out.h>
#include <fcntl.h>
#include <kvm.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
I 19

E 19
#include "extern.h"
E 16
E 14

D 14
#define	min(a, b)	(a < b ? a : b)
E 14
I 14
D 16
extern int getopt();
extern int optind, opterr;
extern char *optarg;
E 16
I 16
void	core __P((int, int, struct kinfo_proc *));
void	datadump __P((int, int, struct proc *, u_long, int));
void	usage __P((void));
void	userdump __P((int, struct proc *, u_long, int));
E 16
E 14

I 16
kvm_t *kd;
/* XXX undocumented routine, should be in kvm.h? */
ssize_t kvm_uread __P((kvm_t *, struct proc *, u_long, char *, size_t));

E 16
D 14
#define	Seek(f, pos) {\
	if (lseek(f, (long) (pos), 0) != (long) (pos)) \
		panic("seek error"); \
}
E 14
I 14
static int data_offset;
E 14

I 16
int
E 16
D 14
#define	Read(f, addr, n) {\
	if (read(f, (char *) (addr), (int) (n)) != (int) (n)) \
		panic("read error"); \
}

#define	Get(f, pos, addr, n) {\
	Seek(f, pos); \
	Read(f, addr, n); \
}

struct	nlist nl[] = {
	{ "_proc" },
#define	X_PROC		0
	{ "_Usrptmap" },
#define	X_USRPTMA	1
	{ "_usrpt" },
#define	X_USRPT		2
	{ "_nswap" },
#define	X_NSWAP		3
	{ "_nproc" },
#define	X_NPROC		4
I 3
	{ "_dmmin" },
#define	X_DMMIN		5
	{ "_dmmax" },
#define	X_DMMAX		6
E 3
	{ 0 },
};

#define FEW	20		/* for fewer system calls */
struct	proc proc[FEW];

union {
	struct user user;
	char upages[UPAGES][NBPG];
} user;
#define u	user.user
#define uarea	user.upages

#define NLIST	"/vmunix"
#define KMEM	"/dev/kmem"
#define MEM	"/dev/mem"
#define SWAP	"/dev/drum"	/* "/dev/swap" on some systems */

int	nproc;
int	nswap;
I 3
int	dmmin, dmmax;
E 3
struct	pte *Usrptmap, *usrpt;
char	coref[20];
int	kmem, mem, swap, cor;
jmp_buf	cont_frame;

E 14
main(argc, argv)
	int argc;
D 16
	char **argv;
E 16
I 16
	char *argv[];
E 16
{
D 14
	register int i, j;
E 14
	register struct proc *p;
D 16
	off_t procbase, procp;
D 14
	int pid, uid;
	char c;
E 14
I 14
	int pid, uid, fd, cnt, i, op, efd;
E 16
	struct kinfo_proc *ki;
D 16
	char *corefile = 0;
	int err;
	int sflag = 0;
E 16
	struct exec exec;
D 16
	char errbuf[_POSIX2_LINE_MAX];
	char fname[64];
E 16
I 16
	int ch, cnt, efd, fd, pid, sflag, uid;
	char *corefile, errbuf[_POSIX2_LINE_MAX], fname[MAXPATHLEN + 1];
E 16
E 14

D 14
	if (argc < 2) {
		printf("Usage: %s pid ...\n", argv[0]);
		exit(1);
	}
	openfiles();
	getkvars();
D 10
	procbase = getw(nl[X_PROC].n_value);
	nproc = getw(nl[X_NPROC].n_value);
	nswap = getw(nl[X_NSWAP].n_value);
I 3
	dmmin = getw(nl[X_DMMIN].n_value);
	dmmax = getw(nl[X_DMMAX].n_value);
E 10
I 10
	procbase = getword(nl[X_PROC].n_value);
	nproc = getword(nl[X_NPROC].n_value);
	nswap = getword(nl[X_NSWAP].n_value);
	dmmin = getword(nl[X_DMMIN].n_value);
	dmmax = getword(nl[X_DMMAX].n_value);
E 10
E 3
	while (--argc > 0) {
		if ((pid = atoi(*++argv)) <= 0 || setjmp(cont_frame))
			continue;
		printf("%d: ", pid);
		procp = procbase;
		for (i = 0; i < nproc; i += FEW) {
			Seek(kmem, procp);
			j = nproc - i;
			if (j > FEW)
				j = FEW;
			j *= sizeof(struct proc);
			Read(kmem, (char *) proc, j);
			procp += j;
			for (j = j / sizeof(struct proc) - 1; j >= 0; j--) {
				p = &proc[j];
				if (p->p_pid == pid)
					goto found;
			}
E 14
I 14
D 16
	setprog(argv[0]);

        opterr = 0;
        while ((op = getopt(argc, argv, "c:s")) != EOF) {
                switch (op) {

E 16
I 16
	sflag = 0;
	corefile = NULL;
        while ((ch = getopt(argc, argv, "c:s")) != EOF) {
                switch (ch) {
E 16
                case 'c':
			corefile = optarg;
                        break;
D 16

E 16
		case 's':
D 16
			++sflag;
E 16
I 16
			sflag = 1;
E 16
			break;
D 16

E 16
		default:
			usage();
			break;
E 14
		}
D 14
		printf("Process not found.\n");
		continue;
	found:
		if (p->p_uid != (uid = getuid()) && uid != 0) {
			printf("Not owner.\n");
			continue;
		}
		if (p->p_stat == SZOMB) {
			printf("Zombie.\n");
			continue;
		}
D 6
		if (p->p_flag & SWEXIT) {
			printf("Process exiting.\n");
			continue;
		}
E 6
I 6
		if (p->p_flag & SWEXIT)
			printf("Warning: process exiting.\n");
E 6
		if (p->p_flag & SSYS) {
			printf("System process.\n");
			/* i.e. swapper or pagedaemon */
			continue;
		}
		sprintf(coref, "core.%d", pid);
		if ((cor = creat(coref, 0666)) < 0) {
			perror(coref);
			exit(1);
		}
		core(p);
		close(cor);
		printf("%s dumped\n", coref);
E 14
	}
I 11
D 14
	exit(0);
E 11
}
E 14
I 14
	argv += optind;
	argc -= optind;
I 16

E 16
	if (argc != 2)
		usage();
E 14

D 10
getw(loc)
E 10
I 10
D 14
getword(loc)
E 10
	off_t loc;
{
	int word;
E 14
I 14
	kd = kvm_openfiles(0, 0, 0, O_RDONLY, errbuf);
D 16
	if (kd == 0)
		error("%s", errbuf);
E 16
I 16
	if (kd == NULL)
		err(1, "%s", errbuf);
E 16
E 14

D 14
	Get(kmem, loc, &word, sizeof(int));
	return (word);
}
E 14
I 14
	uid = getuid();
	pid = atoi(argv[1]);
			
D 18
	ki = kvm_getprocs(kd, KINFO_PROC_PID, pid, &cnt);
E 18
I 18
	ki = kvm_getprocs(kd, KERN_PROC_PID, pid, &cnt);
E 18
D 16
	if (ki == 0 || cnt != 1)
		error("%d: not found", pid);
E 16
I 16
	if (ki == NULL || cnt != 1)
		err(1, "%d: not found", pid);
E 16
E 14

D 14
openfiles()
{
	kmem = open(KMEM, 0);
	if (kmem < 0) {
		perror(KMEM);
		exit(1);
E 14
I 14
	p = &ki->kp_proc;
	if (ki->kp_eproc.e_pcred.p_ruid != uid && uid != 0)
D 16
		error("%d: not owner", pid);
E 16
I 16
		err(1, "%d: not owner", pid);
E 16

	if (p->p_stat == SZOMB)
D 16
		error("%d: zombie", pid);
E 16
I 16
		err(1, "%d: zombie", pid);
E 16

D 21
	if (p->p_flag & SWEXIT)
E 21
I 21
	if (p->p_flag & P_WEXIT)
E 21
D 16
		warning("process exiting");
	if (p->p_flag & SSYS)
		/* i.e. swapper or pagedaemon */
		error("%d: system process");
E 16
I 16
		err(0, "process exiting");
D 21
	if (p->p_flag & SSYS)		/* Swapper or pagedaemon. */
E 21
I 21
	if (p->p_flag & P_SYSTEM)	/* Swapper or pagedaemon. */
E 21
		err(1, "%d: system process");
E 16

D 16
	if (corefile == 0) {
		sprintf(fname, "core.%d", pid);
E 16
I 16
	if (corefile == NULL) {
		(void)snprintf(fname, sizeof(fname), "core.%d", pid);
E 16
		corefile = fname;
E 14
	}
D 14
	mem = open(MEM, 0);
	if (mem < 0) {
		perror(MEM);
E 14
I 14
D 16
	fd = open(corefile, O_RDWR|O_CREAT|O_TRUNC, 0666);
	if (fd < 0) {
		perror(corefile);
E 14
		exit(1);
	}
D 14
	swap = open(SWAP, 0);
	if (swap < 0) {
		perror(SWAP);
E 14
I 14
	efd = open(argv[0], O_RDONLY);
	if (efd < 0) {
		perror(argv[0]);
E 14
		exit(1);
	}
D 14
}
E 14
I 14
	if (read(efd, &exec, sizeof(exec)) != sizeof(exec))
		error("cannot read exec header of %s", argv[0]);
E 16
I 16
	fd = open(corefile, O_RDWR|O_CREAT|O_TRUNC, DEFFILEMODE);
	if (fd < 0)
		err(1, "%s: %s\n", corefile, strerror(errno));
E 16
E 14

I 16
	efd = open(argv[0], O_RDONLY, 0);
	if (efd < 0)
		err(1, "%s: %s\n", argv[0], strerror(errno));

	cnt = read(efd, &exec, sizeof(exec));
	if (cnt != sizeof(exec))
		err(1, "%s exec header: %s",
		    argv[0], cnt > 0 ? strerror(EIO) : strerror(errno));

E 16
D 14
getkvars()
{
	nlist(NLIST, nl);
	if (nl[0].n_type == 0) {
		printf("%s: No namelist\n", NLIST);
		exit(1);
	}
	Usrptmap = (struct pte *) nl[X_USRPTMA].n_value;
	usrpt = (struct pte *) nl[X_USRPT].n_value;
}
E 14
I 14
	data_offset = N_DATOFF(exec);
E 14

D 14
/*
 * Get the system page table entries (mapping the user page table).
 * These are the entries Usrptmap[i .. i + szpt],
 * where i = btokmx(p->p_p0br) and szpt = p->p_szpt.
 * For our purposes, we can skip over the ptes mapping
 * the text segment ptes.
 */
struct pte	*syspt;		/* pte's from Usrptmap */
int		nsysptes;
E 14
I 14
D 16
	if (sflag && kill(pid, SIGSTOP) < 0) 
		warning("%d: could not deliver stop signal", pid);
E 16
I 16
	if (sflag && kill(pid, SIGSTOP) < 0)
		err(0, "%d: stop signal: %s", pid, strerror(errno));
E 16
E 14

D 14
getsyspt(p)
	register struct proc *p;
{
	nsysptes = p->p_szpt - (p->p_tsize / NPTEPG);
	syspt = (struct pte *) malloc(nsysptes * sizeof(struct pte));
	if (syspt == NULL)
		panic("can't alloc %d page table entries", nsysptes);
	Get(kmem, &Usrptmap[btokmx(p->p_p0br) + (p->p_tsize / NPTEPG)],
		syspt, nsysptes * sizeof(struct pte));
}
E 14
I 14
D 16
	err = core(efd, fd, p);
	if (err == 0)
		err = md_core(kd, fd, p);
E 16
I 16
	core(efd, fd, ki);
E 16
E 14

D 14
/*
 * Get the user page table for a segment.
 * seg 0 = p0 (not including text)
 * seg 1 = p1 (stack and u area)
 * The system pt is consulted to find each page of user ptes.
 */
struct pte *
getpt(p, seg)
	register struct proc *p;
	int seg;
{
	register int i;
	register struct pte *spt;
	struct pte *pt;
	int nptes, offset, n;
E 14
I 14
	if (sflag && kill(pid, SIGCONT) < 0)
D 16
		warning("%d: could not deliver continue signal", pid);
	close(fd);
E 16
I 16
		err(0, "%d: continue signal: %s", pid, strerror(errno));
	(void)close(fd);
E 16
E 14

D 14
	if (seg == 0) {
		nptes = p->p_dsize;
		spt = syspt;
		offset = p->p_tsize % NPTEPG;
	} else {
		nptes = p->p_ssize + UPAGES;
		spt = syspt + (nsysptes - ctopt(nptes));
		offset = -nptes % NPTEPG;
		if (offset < 0)
			offset += NPTEPG;
	}
	pt = (struct pte *) malloc(nptes * sizeof(struct pte));
	if (pt == NULL)
		panic("can't alloc %d page table entries", nptes);
	for (i = 0; i < nptes; i += n) {
		n = min(NPTEPG - offset, nptes - i);
		Get(mem, ctob(spt->pg_pfnum) + offset * sizeof(struct pte),
		     pt + i, n * sizeof(struct pte));
		spt++;
		offset = 0;
	}
	return (pt);
E 14
I 14
	exit(0);
E 14
}

D 14
/*
 * Build the core file.
 */
core(p)
	register struct proc *p;
E 14
I 14
D 16
int
userdump(fd, p, addr, npage)
E 16
I 16
/*
 * core --
 *	Build the core file.
 */
void
core(efd, fd, ki)
	int efd;
	int fd;
	struct kinfo_proc *ki;
{
	union {
		struct user user;
		char ubytes[ctob(UPAGES)];
	} uarea;
	struct proc *p = &ki->kp_proc;
	int tsize = ki->kp_eproc.e_vm.vm_tsize;
	int dsize = ki->kp_eproc.e_vm.vm_dsize;
	int ssize = ki->kp_eproc.e_vm.vm_ssize;
	int cnt;

	/* Read in user struct */
	cnt = kvm_read(kd, (u_long)p->p_addr, &uarea, sizeof(uarea));
	if (cnt != sizeof(uarea))
		err(1, "read user structure: %s",
		    cnt > 0 ? strerror(EIO) : strerror(errno));

	/*
	 * Fill in the eproc vm parameters, since these are garbage unless
	 * the kernel is dumping core or something.
	 */
	uarea.user.u_kproc = *ki;

	/* Dump user area */
	cnt = write(fd, &uarea, sizeof(uarea));
	if (cnt != sizeof(uarea))
		err(1, "write user structure: %s",
		    cnt > 0 ? strerror(EIO) : strerror(errno));

	/* Dump data segment */
	datadump(efd, fd, p, USRTEXT + ctob(tsize), dsize);

	/* Dump stack segment */
	userdump(fd, p, USRSTACK - ctob(ssize), ssize);

	/* Dump machine dependent portions of the core. */
	md_core(kd, fd, ki);
}

void
datadump(efd, fd, p, addr, npage)
	register int efd;
E 16
	register int fd;
	struct proc *p;
	register u_long addr;
	register int npage;
E 14
{
D 14
	register struct pte *p0, *p1;
E 14
I 14
D 16
	register int cc;
E 16
I 16
	register int cc, delta;
E 16
	char buffer[NBPG];
E 14
D 16

E 16
I 16
	
	delta = data_offset - addr;
E 16
D 14
	if (p->p_flag & SLOAD) {		/* page tables are resident */
		getsyspt(p);
		p0 = getpt(p, 0);
		p1 = getpt(p, 1);
#ifdef	DEBUG
		showpt(syspt, nsysptes, "system");
		showpt(p0, p->p_dsize, "p0");
		showpt(p1, p->p_ssize + UPAGES, "p1");
#endif
D 10
	}
E 10
I 10
	} else
		p0 = p1 = NULL;			/* not actually used */
E 10
	getu(p, &p1[p->p_ssize]);			/* u area */
	getseg(p, p->p_dsize, p0, &u.u_dmap, 0);	/* data */
	getseg(p, p->p_ssize, p1, &u.u_smap, 1);	/* stack */
	if (p->p_flag & SLOAD) {
		free((char *) syspt);
		free((char *) p0);
		free((char *) p1);
E 14
I 14
	while (--npage >= 0) {
		cc = kvm_uread(kd, p, addr, buffer, NBPG);
I 16
		if (cc != NBPG) {
			/* Try to read the page from the executable. */
			if (lseek(efd, (off_t)addr + delta, SEEK_SET) == -1)
				err(1, "seek executable: %s", strerror(errno));
			cc = read(efd, buffer, sizeof(buffer));
			if (cc != sizeof(buffer))
D 17
				err(1, "read executable: %s",
				    cc > 0 ? strerror(EIO) : strerror(errno));
E 17
I 17
				if (cc < 0) 
					err(1, "read executable: %s",
					    strerror(errno));
				else	/* Assume untouched bss page. */
					bzero(buffer, sizeof(buffer));
E 17
		}
		cc = write(fd, buffer, NBPG);
E 16
		if (cc != NBPG)
D 16
			return (-1);
		(void)write(fd, buffer, NBPG);
E 16
I 16
			err(1, "write data segment: %s",
			    cc > 0 ? strerror(EIO) : strerror(errno));
E 16
		addr += NBPG;
E 14
	}
I 14
D 16
	return (0);
E 16
E 14
}

D 14
/*
 * Get the u area.
 * Keeps around the u structure for later use
 * (the data and stack disk map structures).
 */
getu(p, pages)
	register struct proc *p;
	register struct pte *pages;
E 14
I 14
D 16
int
datadump(efd, fd, p, addr, npage)
	register int efd;
E 16
I 16
void
userdump(fd, p, addr, npage)
E 16
	register int fd;
	struct proc *p;
	register u_long addr;
	register int npage;
E 14
{
D 14
	register int i;

	if ((p->p_flag & SLOAD) == 0) {
		Get(swap, ctob(p->p_swaddr), uarea, ctob(UPAGES));
		write(cor, uarea, ctob(UPAGES));
		return;
	}
	for (i = 0; i < UPAGES; i += CLSIZE) {
		Get(mem, ctob(pages[i].pg_pfnum), uarea[i], ctob(CLSIZE));
		write(cor, uarea[i], ctob(CLSIZE));
	}
}

/*
 * Copy a segment to the core file.
 * The segment is described by its size in clicks,
 * its page table, its disk map, and whether or not
 * it grows backwards.
 * Note that the page table address is allowed to be meaningless
 * if the process is swapped out.
 */
getseg(p, segsize, pages, map, rev)
	register struct proc *p;
	int segsize;
	register struct pte *pages;
	struct dmap *map;
I 10
	int rev;
E 10
{
	register int i;
	struct dblock db;
	int size;
	char buf[ctob(CLSIZE)];

	for (i = 0; i < segsize; i += CLSIZE) {
		size = min(CLSIZE, segsize - i);
		if ((p->p_flag & SLOAD) == 0 || pages[i].pg_fod ||
		    pages[i].pg_pfnum == 0) {
			vstodb(i, size, map, &db, rev);
			Get(swap, ctob(db.db_base), buf, ctob(size));
			write(cor, buf, ctob(size));
		} else {
			Get(mem, ctob(pages[i].pg_pfnum), buf, ctob(size));
			write(cor, buf, ctob(size));
E 14
I 14
D 16
	register int cc, delta;
E 16
I 16
	register int cc;
E 16
	char buffer[NBPG];
D 16
	
	delta = data_offset - addr;
E 16
I 16

E 16
	while (--npage >= 0) {
		cc = kvm_uread(kd, p, addr, buffer, NBPG);
D 16
		if (cc != NBPG) {
			/*
			 * Try to read page from executable.
			 */
			if (lseek(efd, addr + delta, SEEK_SET) == -1)
				return (-1);
			if (read(efd, buffer, sizeof(buffer)) < 0)
				return (-1);
E 14
		}
I 14
		(void)write(fd, buffer, NBPG);
E 16
I 16
		if (cc != NBPG)
			/* Could be an untouched fill-with-zero page. */
			bzero(buffer, NBPG);
		cc = write(fd, buffer, NBPG);
		if (cc != NBPG)
			err(1, "write stack segment: %s",
			    cc > 0 ? strerror(EIO) : strerror(errno));
E 16
		addr += NBPG;
E 14
	}
I 14
D 16
	return (0);
E 16
E 14
}

D 16
/*
D 14
 * Given a base/size pair in virtual swap area,
 * return a physical base/size pair which is the
 * (largest) initial, physically contiguous block.
E 14
I 14
 * Build the core file.
E 14
 */
D 14
vstodb(vsbase, vssize, dmp, dbp, rev)
	register int vsbase;
	int vssize;
	struct dmap *dmp;
	register struct dblock *dbp;
I 10
	int rev;
E 14
I 14
int
core(efd, fd, ki)
	int efd;
	int fd;
	struct kinfo_proc *ki;
E 16
I 16
void
usage()
E 16
E 14
E 10
{
D 3
	register int blk = DMMIN;
E 3
I 3
D 14
	register int blk = dmmin;
E 3
	register swblk_t *ip = dmp->dm_map;
E 14
I 14
D 16
	struct user user;
E 16
I 16
	(void)fprintf(stderr, "usage: gcore [-s] [-c core] executable pid\n");
	exit(1);
}
E 16
E 14

D 14
	if (vsbase < 0 || vsbase + vssize > dmp->dm_size)
		panic("can't make sense out of virtual memory (gcore probably needs to be recompiled)");
	while (vsbase >= blk) {
		vsbase -= blk;
D 3
		if (blk < DMMAX)
E 3
I 3
		if (blk < dmmax)
E 3
			blk *= 2;
		ip++;
	}
	if (*ip <= 0 || *ip + blk > nswap)
		panic("vstodb *ip");
	dbp->db_size = MIN(vssize, blk - vsbase);
	dbp->db_base = *ip + (rev ? blk - (vsbase + dbp->db_size) : vsbase);
}
E 14
I 14
D 16
	int tsize = ki->kp_eproc.e_vm.vm_tsize;
	int dsize = ki->kp_eproc.e_vm.vm_dsize;
	int ssize = ki->kp_eproc.e_vm.vm_ssize;
	struct proc *p = &ki->kp_proc;
E 16
I 16
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
E 16
E 14

I 10
D 14
#ifdef lint
E 10
/*VARARGS1*/
D 10
panic(cp, a, b, c, d)
	char *cp;
E 10
I 10
panic(fmt)
	char *fmt;
E 10
{
E 14
I 14
D 16
	/* Read in user struct */
	if (kvm_read(kd, (u_long)p->p_addr, (void *)&user, sizeof(user)) 
	    != sizeof(user))
		error("could not read user structure");
E 14
D 10
	printf(cp, a, b, c, d);
	printf("\n");
E 10
I 10

D 14
	fmt = fmt;
E 10
	longjmp(cont_frame, 1);
}
I 10
#else /* lint */
panic(va_alist)
	va_dcl
{
	va_list ap;
	char *fmt;
E 14
I 14
	/*
	 * Fill in the eproc vm parameters, since these are garbage unless
	 * the kernel is dumping core or something.
	 */
	user.u_kproc.kp_eproc.e_vm.vm_tsize = tsize;
	user.u_kproc.kp_eproc.e_vm.vm_dsize = dsize;
	user.u_kproc.kp_eproc.e_vm.vm_ssize = ssize;
	/* write out the user struct and leave the right amount of space */
	(void)write(fd, (char *)&user, sizeof(user));
	(void)lseek(fd, UPAGES * NBPG, SEEK_SET);
E 14

D 14
	va_start(ap);
	fmt = va_arg(ap, char *);
	(void) vprintf(fmt, ap);
	va_end(ap);
	(void) printf("\n");
	longjmp(cont_frame, 1);
}
#endif /* lint */
E 14
I 14
	/* Dump data segment */
	if (datadump(efd, fd, p, USRTEXT + ctob(tsize), dsize) < 0)
		error("could not dump data segment");
E 14
E 10

D 14
/* 
 * Debugging routine to print out page table.
 */
#ifdef	DEBUG
showpt(pt, n, s)
	struct pte *pt;
	int n;
	char *s;
{
	register struct pte *p;
	register int i;
E 14
I 14
	/* Dump stack segment */
	if (userdump(fd, p, USRSTACK - ctob(ssize), ssize) < 0)
		error("could not dump stack segment");
E 14

D 14
	printf("*** %s page table\n", s);
	for (i = 0, p = pt; i < n; i++, p++)
		if (! p->pg_fod)
			printf("%d: %x\n", i, p->pg_pfnum);
E 14
I 14
	return (0);
E 16
I 16
void
#if __STDC__
err(int fatal, const char *fmt, ...)
#else
err(fatal, fmt, va_alist)
	int fatal;
	char *fmt;
        va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "gcore: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 16
E 14
}
D 14
#endif
E 14
E 1
