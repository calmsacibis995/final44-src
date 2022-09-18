h30360
s 00002/00002/00257
d D 8.1 93/06/04 16:53:44 bostic 31 30
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00258
d D 5.30 93/04/27 10:48:51 bostic 30 29
c typo
e
s 00006/00000/00253
d D 5.29 92/07/10 16:15:27 mckusick 29 28
c update for luna68k
e
s 00103/00034/00150
d D 5.28 92/06/05 10:18:04 hibler 28 27
c changes for 68040 support
e
s 00001/00000/00183
d D 5.27 92/05/28 16:14:09 mckusick 27 26
c need to include <unistd.h>
e
s 00001/00001/00182
d D 5.26 92/05/26 14:40:22 bostic 26 25
c update copyright year
e
s 00004/00000/00179
d D 5.25 92/05/26 14:37:34 bostic 25 24
c add LBL credit line
e
s 00002/00002/00177
d D 5.24 92/04/29 11:49:29 bostic 24 23
c update from LBL (Chris, Craig and Steve)
e
s 00117/01017/00062
d D 5.23 92/04/03 14:53:55 mckusick 23 22
c update from Steve McCanne for Sun compatible kvm
e
s 00010/00004/01069
d D 5.22 92/03/07 09:29:36 ralph 22 21
c don't try to read nswap, its not used if NEWVM defined.
e
s 00000/00007/01073
d D 5.21 91/10/24 13:30:12 marc 21 20
c u-area is pageable under new VM.  no need to read from swap.
e
s 00022/00034/01058
d D 5.20 91/10/24 13:24:04 marc 20 19
c more error checking.  cruft.
e
s 00036/00024/01056
d D 5.19 91/07/02 17:50:56 marc 19 18
c propagate errors more carefully, report missing nlist symbols
e
s 00001/00001/01079
d D 5.18 91/05/07 09:54:13 bostic 18 17
c ANSI cleanup
e
s 00003/00003/01077
d D 5.17 91/05/06 18:13:13 karels 17 16
c fix type conflict for old vm
e
s 00039/00025/01041
d D 5.16 91/05/06 18:09:18 karels 16 15
c (stolen from marc, who had it checked out...) update newvm stuff;
c pte.h is now machine dependent; user.h *is* needed (else is hard to return one);
c make functions agree with their prototypes; marc cleaned up error handling
e
s 00000/00001/01066
d D 5.15 91/04/27 16:19:55 bostic 15 14
c doesn't need user.h anymore
e
s 00179/00012/00888
d D 5.14 91/04/24 14:38:58 karels 14 13
c changes for new vm (more to come)
e
s 00013/00012/00887
d D 5.13 91/02/24 16:22:38 bostic 13 12
c Add include files to get prototype declarations, and fix bugs found.
e
s 00008/00013/00891
d D 5.12 91/02/24 16:15:42 bostic 12 11
c new version of ndbm routines, minor cleanup
e
s 00001/00001/00903
d D 5.11 91/01/31 18:41:27 bostic 11 10
c use paths.h define for /var/run
e
s 00003/00003/00901
d D 5.10 90/10/14 12:43:25 bostic 10 9
c _BSD_LINE_MAX -> _POSIX2_LINE_MAX
e
s 00005/00003/00899
d D 5.9 90/06/27 15:56:47 marc 9 8
c always initialize (XXX), also _BSD_LINE_MAX (???)
e
s 00072/00044/00830
d D 5.8 90/06/06 10:00:15 bostic 8 7
c HP300 fixes from Mike Hibler
e
s 00005/00013/00869
d D 5.7 90/06/01 15:48:45 bostic 7 6
c needed sccs id's
e
s 00001/00001/00881
d D 5.6 90/05/15 20:37:01 bostic 6 5
c cencode.h -> vis.h
e
s 00001/00001/00881
d D 5.5 90/05/15 19:44:17 bostic 5 4
c string.h is ANSI C include file
e
s 00000/00004/00882
d D 5.4 90/05/04 15:23:11 marc 4 3
c don't return <defunct> or <exiting>; comm is available
e
s 00002/00001/00884
d D 5.3 90/05/04 15:21:00 marc 3 2
c tell what size it thinks kinfo_proc should be
e
s 00120/00076/00765
d D 5.2 90/04/23 16:24:13 marc 2 1
c look harder for args, don't hardcode names for pid 0 & 2, other cleanups
c still under development
e
s 00841/00000/00000
d D 5.1 90/03/01 17:31:23 marc 1 0
c date and time created 90/03/01 17:31:23 by marc
e
u
U
t
T
I 1
D 7
/*
E 7
I 7
/*-
E 7
D 26
 * Copyright (c) 1989 The Regents of the University of California.
E 26
I 26
D 31
 * Copyright (c) 1989, 1992 The Regents of the University of California.
E 26
 * All rights reserved.
E 31
I 31
 * Copyright (c) 1989, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 31
 *
I 25
 * This code is derived from software developed by the Computer Systems
 * Engineering group at Lawrence Berkeley Laboratory under DARPA contract
 * BG 91-66 and contributed to Berkeley.
 *
E 25
D 7
 * Redistribution and use in source and binary forms is permitted
 * provided that all copyright information, including this notice,
 * is retained in all such forms, and that any documentation,
 * advertising or other materials related to such distribution and
 * use acknowledge that the software was
 * developed by the University of California, Berkeley.  The name
 * of the University may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
 */

I 7
#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */
E 7

I 23
/*
D 24
 * hp300 machine depedent routines for kvm.  Hopefully, the forthcoming 
E 24
I 24
D 30
 * Hp300 machine depedent routines for kvm.  Hopefully, the forthcoming 
E 30
I 30
 * Hp300 machine dependent routines for kvm.  Hopefully, the forthcoming 
E 30
E 24
 * vm code will one day obsolete this module.
 */

E 23
D 14
#include <machine/pte.h>
I 8
#include <machine/vmparam.h>
E 14
E 8
#include <sys/param.h>
I 16
#include <sys/user.h>
E 16
I 12
D 14
#include <sys/vmmac.h>
E 14
E 12
D 15
#include <sys/user.h>
E 15
#include <sys/proc.h>
D 12
#include <sys/file.h>
E 12
D 14
#include <sys/text.h>
E 14
D 12
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/vmmac.h>
E 12
D 23
#include <sys/ioctl.h>
I 12
#include <sys/kinfo.h>
E 12
#include <sys/tty.h>
I 14
#include <machine/vmparam.h>
E 14
I 12
#include <fcntl.h>
E 23
I 23
#include <sys/stat.h>
I 27
#include <unistd.h>
E 27
E 23
E 12
D 2
#include <sys/kinfo.h>
#include <stdio.h>
E 2
I 2
D 16
#include <kvm.h>
E 16
E 2
D 12
#include <ctype.h>
I 2
D 6
#include <cencode.h>
E 6
I 6
#include <vis.h>
E 12
E 6
E 2
#include <nlist.h>
I 16
#include <kvm.h>
E 16
D 12
#include <pwd.h>
D 5
#include <strings.h>
E 5
I 5
#include <string.h>
E 12
E 5
D 23
#include <ndbm.h>
E 23
I 23

#include <vm/vm.h>
#include <vm/vm_param.h>

E 23
#include <limits.h>
D 23
#include <paths.h>
I 2
#include <stdio.h>
I 12
#include <string.h>
E 23
I 23
D 24
#include <ndbm.h>
E 24
I 24
#include <db.h>
E 24
E 23
E 12
E 2

I 14
D 23
#ifdef SPPWAIT
#define NEWVM
#endif
E 23
I 23
#include "kvm_private.h"
E 23

I 29
#if defined(hp300)
E 29
D 23
#ifdef NEWVM
E 23
I 23
#include <hp300/hp300/pte.h>
I 29
#endif

#if defined(luna68k)
#include <luna68k/luna68k/pte.h>
#endif
E 29

#ifndef btop
E 23
#define	btop(x)		(((unsigned)(x)) >> PGSHIFT)	/* XXX */
#define	ptob(x)		((caddr_t)((x) << PGSHIFT))	/* XXX */
D 23
#include <vm/vm.h>	/* ??? kinfo_proc currently includes this*/
#include <sys/kinfo_proc.h>
D 16
#else
E 16
I 16
#ifdef hp300
#include <hp300/hp300/pte.h>
E 23
#endif
D 23
#else /* NEWVM */
E 16
#include <machine/pte.h>
#include <sys/vmmac.h>
#include <sys/text.h>
D 16
#endif
E 16
I 16
#endif /* NEWVM */
E 23
E 16

E 14
D 23
/*
 * files
 */
D 16
static	char *unixf, *memf, *kmemf, *swapf;
E 16
I 16
static	const char *unixf, *memf, *kmemf, *swapf;
E 16
static	int unixx, mem, kmem, swap;
D 2
DBM	*db;
E 2
I 2
static	DBM *db;
E 2
/*
 * flags
 */
static	int deadkernel;
static	int kvminit = 0;
static	int kvmfilesopen = 0;
/*
 * state
 */
static	struct kinfo_proc *kvmprocbase, *kvmprocptr;
static	int kvmnprocs;
D 2
static	char *err;
E 2
/*
 * u. buffer
 */
static union {
	struct	user user;
	char	upages[UPAGES][NBPG];
} user;
/*
 * random other stuff
 */
I 16
#ifndef NEWVM
E 16
static	struct pte *Usrptmap, *usrpt;
D 16
static	int	dmmin, dmmax;
E 16
static	struct	pte *Sysmap;
static	int	Syssize;
I 16
D 22
#endif
E 22
static	int	dmmin, dmmax;
I 22
static	int	nswap;
#endif
E 22
E 16
D 8
static	int     pcbpf;
D 2
static	int     argaddr;
E 2
I 2
static	int     argaddr0;	/* XXX */
static	int     argaddr1;
E 8
I 8
static	int	pcbpf;
static	int	argaddr0;	/* XXX */
static	int	argaddr1;
E 8
E 2
D 22
static	int	nswap;
E 22
D 2
static char *tmp;
#define basename(cp)	((tmp=rindex((cp), '/')) ? tmp+1 : (cp))
E 2
I 2
static	char	*tmp;
I 8
#if defined(hp300)
static	int	lowram;
I 14
static	struct ste *Sysseg;
E 14
#endif
E 8
E 2

D 2
#define KVMDBDIR	"/var/run"
E 2
I 2
#define basename(cp)	((tmp=rindex((cp), '/')) ? tmp+1 : (cp))
E 2
#define	MAXSYMSIZE	256
D 2
#define	KVMDB_NLIST	1
#define	KVMDB_DEVS	2
E 2

I 8
#if defined(hp300)
#define pftoc(f)	((f) - lowram)
#define iskva(v)	(1)
#endif

#ifndef pftoc
#define pftoc(f)	(f)
#endif
#ifndef iskva
D 17
#define iskva(v)	((v) & KERNBASE)
E 17
I 17
#define iskva(v)	((u_long)(v) & KERNBASE)
E 17
#endif

E 8
static struct nlist nl[] = {
I 22
#ifndef NEWVM
E 22
D 19
	{ "_Usrptmap" },
#define	X_USRPTMAP	0
	{ "_usrpt" },
#define	X_USRPT		1
E 19
	{ "_nswap" },
D 19
#define	X_NSWAP		2
E 19
I 19
#define	X_NSWAP		0
E 19
	{ "_dmmin" },
D 19
#define	X_DMMIN		3
E 19
I 19
#define	X_DMMIN		X_NSWAP+1
E 19
	{ "_dmmax" },
D 19
#define	X_DMMAX		4
E 19
I 19
#define	X_DMMAX		X_DMMIN+1
I 22
#else
#define	X_DMMAX		-1
#endif
E 22
E 19
	/*
	 * everything here and down, only if a dead kernel
	 */
	{ "_Sysmap" },
D 19
#define	X_SYSMAP	5
E 19
I 19
#define	X_SYSMAP	X_DMMAX+1
E 19
D 8
#define	X_DEADKERNEL	X_SYSMAP	
E 8
I 8
#define	X_DEADKERNEL	X_SYSMAP
E 8
D 19
	{ "_Syssize" },
#define	X_SYSSIZE	6
E 19
	{ "_allproc" },
D 19
#define X_ALLPROC	7
E 19
I 19
#define X_ALLPROC	X_SYSMAP+1
E 19
	{ "_zombproc" },
D 19
#define X_ZOMBPROC	8
	{ "_nproc" },
#define	X_NPROC		9
I 8
#define	X_LAST		9
E 19
I 19
#define X_ZOMBPROC	X_ALLPROC+1
	{ "_nprocs" },
#define	X_NPROCS	X_ZOMBPROC+1
E 19
#if defined(hp300)
I 14
	{ "_Sysseg" },
D 19
#define	X_SYSSEG	(X_LAST+1)
E 19
I 19
#define	X_SYSSEG	(X_NPROCS+1)
E 19
E 14
	{ "_lowram" },
D 14
#define	X_LOWRAM	(X_LAST+1)
E 14
I 14
D 19
#define	X_LOWRAM	(X_LAST+2)
E 19
I 19
#define	X_LOWRAM	(X_SYSSEG+1)
E 19
E 14
#endif
E 8
	{ "" },
E 23
I 23
struct vmstate {
	u_long lowram;
I 28
	int mmutype;
E 28
	struct ste *Sysseg;
E 23
};

I 13
D 23
static off_t vtophys();
D 20
static void klseek(), seterr(), setsyserr(), vstodb();
static int getkvars(), kvm_doprocs(), kvm_init();
E 20
I 20
static void seterr(), setsyserr(), vstodb();
static int getkvars(), kvm_doprocs(), kvm_init(), klseek();
E 23
I 23
#define KREAD(kd, addr, p)\
	(kvm_read(kd, addr, (char *)(p), sizeof(*(p))) != sizeof(*(p)))
E 23
E 20

E 13
D 8
static char *savestr();

E 8
D 2
kvm_init(uf, mf, sf)
	char *uf, *mf, *sf;
{
	if (kvminit) {
		seterr("already initialized (can't re-initialize)");
		return (-1);
	}
	if (kvm_openfiles(uf, mf, sf) == -1)
		return (-1);
	if (getkvars() == -1)
		return (-1);
	kvminit = 1;

	return (0);
}

static 
E 2
I 2
D 23
/*
 * returns 	0 if files were opened now,
 * 		1 if files were already opened,
 *		-1 if files could not be opened.
 */
E 2
kvm_openfiles(uf, mf, sf)
D 2
	char *uf, *mf, *sf; {
	if (kvmfilesopen) /* XXX && the file names are all the same ??? */
		return (0);
E 2
I 2
D 16
	char *uf, *mf, *sf; 
E 16
I 16
	const char *uf, *mf, *sf; 
E 23
I 23
void
_kvm_freevtop(kd)
	kvm_t *kd;
E 23
E 16
{
D 23
	if (kvmfilesopen)
		return (1);
E 2
	unixx = mem = kmem = swap = -1;
	unixf = (uf == NULL) ? _PATH_UNIX : uf; 
	memf = (mf == NULL) ? _PATH_MEM : mf;

	if ((unixx = open(unixf, O_RDONLY, 0)) == -1) {
		setsyserr("can't open %s", unixf);
		goto failed;
	}
	if ((mem = open(memf, O_RDONLY, 0)) == -1) {
		setsyserr("can't open %s", memf);
		goto failed;
	}
	if (sf != NULL)
		swapf = sf;
	if (mf != NULL) {
		deadkernel++;
		kmemf = mf;
		kmem = mem;
		swap = -1;
	} else {
		kmemf = _PATH_KMEM;
		if ((kmem = open(kmemf, O_RDONLY, 0)) == -1) {
			setsyserr("can't open %s", kmemf);
			goto failed;
		}
		swapf = (sf == NULL) ?  _PATH_DRUM : sf;
		/*
		 * live kernel - avoid looking up nlist entries
		 * past X_DEADKERNEL.
		 */
		nl[X_DEADKERNEL].n_name = "";
	}
	if (swapf != NULL && ((swap = open(swapf, O_RDONLY, 0)) == -1)) {
		seterr("can't open %s", swapf);
		goto failed;
	}
	kvmfilesopen++;
I 9
	if (kvminit == 0 && kvm_init(NULL, NULL, NULL, 0) == -1) /*XXX*/
		return (-1);
E 9
	return (0);
failed:
	kvm_close();
	return (-1);
E 23
I 23
	if (kd->vmst != 0)
		free(kd->vmst);
E 23
}

I 2
D 23
static
kvm_init(uf, mf, sf)
	char *uf, *mf, *sf;
E 23
I 23
int
_kvm_initvtop(kd)
	kvm_t *kd;
E 23
{
D 23
	if (kvmfilesopen == 0 && kvm_openfiles(NULL, NULL, NULL) == -1)
E 23
I 23
	struct vmstate *vm;
D 28
	struct nlist nlist[3];
E 28
I 28
	struct nlist nlist[4];
E 28

	vm = (struct vmstate *)_kvm_malloc(kd, sizeof(*vm));
	if (vm == 0)
E 23
		return (-1);
D 23
	if (getkvars() == -1)
		return (-1);
	kvminit = 1;
E 23
I 23
	kd->vmst = vm;
E 23

D 23
	return (0);
}
E 23
I 23
	nlist[0].n_name = "_lowram";
D 28
	nlist[1].n_name = "_Sysseg";
	nlist[2].n_name = 0;
E 28
I 28
	nlist[1].n_name = "_mmutype";
	nlist[2].n_name = "_Sysseg";
	nlist[3].n_name = 0;
E 28
E 23

E 2
D 23
kvm_close()
{
D 2
	if (unixx != -1)
E 2
I 2
	if (unixx != -1) {
E 2
		close(unixx);
D 2
	if (mem != -1)
E 2
I 2
		unixx = -1;
E 23
I 23
	if (kvm_nlist(kd, nlist) != 0) {
		_kvm_err(kd, kd->program, "bad namelist");
		return (-1);
E 23
	}
D 23
	if (kmem != -1) {
		if (kmem != mem)
			close(kmem);
		/* otherwise kmem is a copy of mem, and will be closed below */
		kmem = -1;
E 23
I 23
	vm->Sysseg = 0;
	if (KREAD(kd, (u_long)nlist[0].n_value, &vm->lowram)) {
		_kvm_err(kd, kd->program, "cannot read lowram");
		return (-1);
E 23
	}
D 23
	if (mem != -1) {
E 2
		close(mem);
D 2
	if (kmem != -1 && (kmem != mem))
		close(kmem);
	if (swap != -1)
E 2
I 2
		mem = -1;
E 23
I 23
D 28
	if (KREAD(kd, (u_long)nlist[1].n_value, &vm->Sysseg)) {
E 28
I 28
	if (KREAD(kd, (u_long)nlist[1].n_value, &vm->mmutype)) {
		_kvm_err(kd, kd->program, "cannot read mmutype");
		return (-1);
	}
	if (KREAD(kd, (u_long)nlist[2].n_value, &vm->Sysseg)) {
E 28
		_kvm_err(kd, kd->program, "cannot read segment table");
		return (-1);
E 23
	}
D 23
	if (swap != -1) {
E 2
		close(swap);
D 2
	if (db != NULL)
E 2
I 2
		swap = -1;
	}
	if (db != NULL) {
E 2
		dbm_close(db);
I 2
		db = NULL;
	}
E 2
	kvminit = 0;
	kvmfilesopen = 0;
I 2
	deadkernel = 0;
I 16
#ifndef NEWVM
E 16
	if (Sysmap) {
		free(Sysmap);
		Sysmap = NULL;
	}
I 16
#endif
E 23
I 23
	return (0);
E 23
E 16
E 2
}

D 23
kvm_nlist(nl)
	struct nlist *nl;
E 23
I 23
static int
_kvm_vatop(kd, sta, va, pa)
	kvm_t *kd;
	struct ste *sta;
	u_long va;
	u_long *pa;
E 23
{
D 23
	datum key, data;
	char dbname[MAXPATHLEN];
D 9
	char dbversion[LINE_MAX];
	char kversion[LINE_MAX];
E 9
I 9
D 10
	char dbversion[_BSD_LINE_MAX];
	char kversion[_BSD_LINE_MAX];
E 10
I 10
	char dbversion[_POSIX2_LINE_MAX];
	char kversion[_POSIX2_LINE_MAX];
E 10
E 9
	int dbversionlen;
D 12
	char symbuf[MAXSYMSIZE+1];
E 12
I 12
	char symbuf[MAXSYMSIZE];
E 12
	struct nlist nbuf, *n;
	int num, did;
E 23
I 23
	register struct vmstate *vm;
I 28
	register u_long lowram;
E 28
	register u_long addr;
	int p, ste, pte;
	int offset;
D 28
	register u_long lowram;
E 28
E 23

I 28
	if (ISALIVE(kd)) {
		_kvm_err(kd, 0, "vatop called in live kernel!");
		return((off_t)0);
	}
E 28
D 23
	if (kvmfilesopen == 0 && kvm_openfiles(NULL, NULL, NULL) == -1)
		return (-1);
	if (deadkernel)
		goto hard2;
E 23
I 23
	vm = kd->vmst;
I 28
	offset = va & PGOFSET;
E 28
E 23
D 2
	if (db != NULL)
		goto win;
	sprintf(dbname, "%s/kvm_%s", KVMDBDIR, basename(unixf));
	if ((db = dbm_open(dbname, O_RDONLY, 0)) == NULL)
		goto hard2;
E 2
	/*
D 2
	 * read version out of kmem and compare to version
	 * in database.
E 2
I 2
D 23
	 * initialize key datum
E 23
I 23
D 28
	 * If processing a post-mortem and we are initializing
	 * (kernel segment table pointer not yet set) then return
	 * pa == va to avoid infinite recursion.
E 28
I 28
	 * If we are initializing (kernel segment table pointer not yet set)
	 * then return pa == va to avoid infinite recursion.
E 28
E 23
E 2
	 */
D 23
	key.dptr = symbuf;
D 12
	symbuf[0] = KVMDB_NLIST;
E 12
I 2

	if (db != NULL)
		goto win;	/* off to the races */
E 23
I 23
D 28
	if (!ISALIVE(kd) && vm->Sysseg == 0) {
E 28
I 28
	if (vm->Sysseg == 0) {
E 28
		*pa = va;
D 28
		return (NBPG - (va & PGOFSET));
E 28
I 28
		return (NBPG - offset);
E 28
	}
D 28
	addr = (u_long)&sta[va >> SEGSHIFT];
E 23
E 2
	/*
D 2
	 * read version string from database
E 2
I 2
D 23
	 * open database
E 23
I 23
	 * Can't use KREAD to read kernel segment table entries.
	 * Fortunately it is 1-to-1 mapped so we don't have to. 
E 23
E 2
	 */
I 2
D 11
	sprintf(dbname, "%s/kvm_%s", KVMDBDIR, basename(unixf));
E 11
I 11
D 23
	sprintf(dbname, "%s/kvm_%s", _PATH_VARRUN, basename(unixf));
E 11
	if ((db = dbm_open(dbname, O_RDONLY, 0)) == NULL)
		goto hard2;
	/*
	 * read version out of database
	 */
E 2
D 12
	bcopy("VERSION", symbuf+1, sizeof ("VERSION")-1);
E 12
I 12
	bcopy("VERSION", symbuf, sizeof ("VERSION")-1);
E 12
	key.dsize = (sizeof ("VERSION") - 1) + 1;
	data = dbm_fetch(db, key);
	if (data.dptr == NULL)
		goto hard1;
	bcopy(data.dptr, dbversion, data.dsize);
	dbversionlen = data.dsize;
	/*
	 * read version string from kernel memory
	 */
D 12
	bcopy("_version", symbuf+1, sizeof ("_version")-1);
E 12
I 12
	bcopy("_version", symbuf, sizeof ("_version")-1);
E 12
	key.dsize = (sizeof ("_version")-1) + 1;
	data = dbm_fetch(db, key);
	if (data.dptr == NULL)
		goto hard1;
	if (data.dsize != sizeof (struct nlist))
		goto hard1;
	bcopy(data.dptr, &nbuf, sizeof (struct nlist));
	lseek(kmem, nbuf.n_value, 0);
	if (read(kmem, kversion, dbversionlen) != dbversionlen)
		goto hard1;
	/*
	 * if they match, we win - otherwise do it the hard way
	 */
	if (bcmp(dbversion, kversion, dbversionlen) != 0)
		goto hard1;
	/*
	 * getem from the database.
	 */
win:
	num = did = 0;
	for (n = nl; n->n_name && n->n_name[0]; n++, num++) {
		int len;
		/*
D 2
		 * clear out crap from users buffer
E 2
I 2
		 * clear out fields from users buffer
E 2
		 */
		n->n_type = 0;
		n->n_other = 0;
		n->n_desc = 0;
		n->n_value = 0;
		/*
		 * query db
		 */
		if ((len = strlen(n->n_name)) > MAXSYMSIZE) {
D 16
			seterr("kvm_nlist: symbol too large");
E 16
I 16
			seterr("symbol too large");
E 16
			return (-1);
		}
D 12
		strcpy(symbuf+1, n->n_name);
E 12
I 12
		(void)strcpy(symbuf, n->n_name);
E 12
		key.dsize = len + 1;
		data = dbm_fetch(db, key);
		if (data.dptr == NULL || data.dsize != sizeof (struct nlist))
			continue;
		bcopy(data.dptr, &nbuf, sizeof (struct nlist));
		n->n_value = nbuf.n_value;
		n->n_type = nbuf.n_type;
		n->n_desc = nbuf.n_desc;
		n->n_other = nbuf.n_other;
		did++;
E 23
I 23
	if (sta == vm->Sysseg) {
		if (lseek(kd->pmfd, (off_t)addr, 0) == -1 ||
E 28
I 28
	lowram = vm->lowram;
	if (vm->mmutype == -2) {
		struct ste *sta2;

		addr = (u_long)&sta[va >> SG4_SHIFT1];
		/*
		 * Can't use KREAD to read kernel segment table entries.
		 * Fortunately it is 1-to-1 mapped so we don't have to. 
		 */
		if (sta == vm->Sysseg) {
			if (lseek(kd->pmfd, (off_t)addr, 0) == -1 ||
			    read(kd->pmfd, (char *)&ste, sizeof(ste)) < 0)
				goto invalid;
		} else if (KREAD(kd, addr, &ste))
			goto invalid;
		if ((ste & SG_V) == 0) {
			_kvm_err(kd, 0, "invalid level 1 descriptor (%x)",
				 ste);
			return((off_t)0);
		}
		sta2 = (struct ste *)(ste & SG4_ADDR1);
		addr = (u_long)&sta2[(va & SG4_MASK2) >> SG4_SHIFT2];
		/*
		 * Address from level 1 STE is a physical address,
		 * so don't use kvm_read.
		 */
		if (lseek(kd->pmfd, (off_t)(addr - lowram), 0) == -1 || 
E 28
		    read(kd->pmfd, (char *)&ste, sizeof(ste)) < 0)
			goto invalid;
D 28
	} else if (KREAD(kd, addr, &ste))
		goto invalid;
	if ((ste & SG_V) == 0) {
		_kvm_err(kd, 0, "invalid segment (%x)", ste);
		return((off_t)0);
E 28
I 28
		if ((ste & SG_V) == 0) {
			_kvm_err(kd, 0, "invalid level 2 descriptor (%x)",
				 ste);
			return((off_t)0);
		}
		sta2 = (struct ste *)(ste & SG4_ADDR2);
		addr = (u_long)&sta2[(va & SG4_MASK3) >> SG4_SHIFT3];
	} else {
		addr = (u_long)&sta[va >> SEGSHIFT];
		/*
		 * Can't use KREAD to read kernel segment table entries.
		 * Fortunately it is 1-to-1 mapped so we don't have to. 
		 */
		if (sta == vm->Sysseg) {
			if (lseek(kd->pmfd, (off_t)addr, 0) == -1 ||
			    read(kd->pmfd, (char *)&ste, sizeof(ste)) < 0)
				goto invalid;
		} else if (KREAD(kd, addr, &ste))
			goto invalid;
		if ((ste & SG_V) == 0) {
			_kvm_err(kd, 0, "invalid segment (%x)", ste);
			return((off_t)0);
		}
		p = btop(va & SG_PMASK);
		addr = (ste & SG_FRAME) + (p * sizeof(struct pte));
E 28
E 23
	}
D 23
	return (num - did);
hard1:
	dbm_close(db);
	db = NULL;
hard2:
D 2
	return (nlist(unixf, nl));
E 2
I 2
D 16
	return (nlist(unixf, nl));	/* XXX seterr if -1 */
E 16
I 16
	num = nlist(unixf, nl);
	if (num == -1)
		seterr("nlist (hard way) failed");
	return (num);
E 16
E 2
}

kvm_getprocs(what, arg)
I 13
	int what, arg;
E 13
{
I 2
	if (kvminit == 0 && kvm_init(NULL, NULL, NULL, 0) == -1)
		return (NULL);
E 2
	if (!deadkernel) {
		int ret, copysize;

		if ((ret = getkerninfo(what, NULL, NULL, arg)) == -1) {
			setsyserr("can't get estimate for kerninfo");
			return (-1);
		}
		copysize = ret;
		if ((kvmprocbase = (struct kinfo_proc *)malloc(copysize)) 
		     == NULL) {
			seterr("out of memory");
			return (-1);
		}
D 22
		if ((ret = getkerninfo(what, kvmprocbase, &copysize, 
		     arg)) == -1) {
E 22
I 22
		if ((ret = getkerninfo(what, kvmprocbase, &copysize, arg))
		     == -1) {
E 22
			setsyserr("can't get proc list");
			return (-1);
		}
		if (copysize % sizeof (struct kinfo_proc)) {
D 3
			seterr("proc size mismatch");
E 3
I 3
D 14
			seterr("proc size mismatch (kinfo_proc: %d)",
				sizeof (struct kinfo_proc));
E 14
I 14
			seterr("proc size mismatch (got %d total, kinfo_proc: %d)",
				copysize, sizeof (struct kinfo_proc));
E 14
E 3
			return (-1);
		}
		kvmnprocs = copysize / sizeof (struct kinfo_proc);
	} else {
D 2
		int i;
E 2
D 19
		int nproc;
E 19
I 19
		int nprocs;
E 19

D 16
		if (kvm_read(nl[X_NPROC].n_value, &nproc, sizeof (int)) !=
		    sizeof (int)) {
E 16
I 16
D 19
		if (kvm_read((void *) nl[X_NPROC].n_value, &nproc,
E 19
I 19
		if (kvm_read((void *)nl[X_NPROCS].n_value, &nprocs,
E 19
		    sizeof (int)) != sizeof (int)) {
E 16
			seterr("can't read nproc");
			return (-1);
		}
		if ((kvmprocbase = (struct kinfo_proc *)
D 19
		     malloc(nproc * sizeof (struct kinfo_proc))) == NULL) {
D 2
			seterr("out of memory (addr: %x nproc = %d)", nl[X_NPROC].n_value, nproc);
E 2
I 2
			seterr("out of memory (addr: %x nproc = %d)",
				nl[X_NPROC].n_value, nproc);
E 19
I 19
		     malloc(nprocs * sizeof (struct kinfo_proc))) == NULL) {
			seterr("out of memory (addr: %x nprocs = %d)",
				nl[X_NPROCS].n_value, nprocs);
E 19
E 2
			return (-1);
		}
		kvmnprocs = kvm_doprocs(what, arg, kvmprocbase);
		realloc(kvmprocbase, kvmnprocs * sizeof (struct kinfo_proc));
	}
	kvmprocptr = kvmprocbase;

	return (kvmnprocs);
}

/*
 * XXX - should NOT give up so easily - especially since the kernel
 * may be corrupt (it died).  Should gather as much information as possible.
 * Follows proc ptrs instead of reading table since table may go
 * away soon.
 */
static
kvm_doprocs(what, arg, buff)
	int what, arg;
	char *buff;
{
	struct proc *p, proc;
	register char *bp = buff;
	int i = 0;
	int doingzomb = 0;
	struct eproc eproc;
	struct pgrp pgrp;
	struct session sess;
	struct tty tty;
I 14
#ifndef NEWVM
E 14
	struct text text;
I 14
#endif
E 14

	/* allproc */
D 16
	if (kvm_read(nl[X_ALLPROC].n_value, &p, 
E 16
I 16
	if (kvm_read((void *) nl[X_ALLPROC].n_value, &p, 
E 16
	    sizeof (struct proc *)) != sizeof (struct proc *)) {
		seterr("can't read allproc");
		return (-1);
	}

again:
	for (; p; p = proc.p_nxt) {
		if (kvm_read(p, &proc, sizeof (struct proc)) !=
		    sizeof (struct proc)) {
			seterr("can't read proc at %x", p);
			return (-1);
		}
I 14
#ifdef NEWVM
		if (kvm_read(proc.p_cred, &eproc.e_pcred,
		    sizeof (struct pcred)) == sizeof (struct pcred))
			(void) kvm_read(eproc.e_pcred.pc_ucred, &eproc.e_ucred,
			    sizeof (struct ucred));
E 14
		switch(ki_op(what)) {
			
		case KINFO_PROC_PID:
			if (proc.p_pid != (pid_t)arg)
				continue;
			break;


		case KINFO_PROC_UID:
I 14
			if (eproc.e_ucred.cr_uid != (uid_t)arg)
				continue;
			break;

		case KINFO_PROC_RUID:
			if (eproc.e_pcred.p_ruid != (uid_t)arg)
				continue;
			break;
		}
#else
		switch(ki_op(what)) {
			
		case KINFO_PROC_PID:
			if (proc.p_pid != (pid_t)arg)
				continue;
			break;


		case KINFO_PROC_UID:
E 14
			if (proc.p_uid != (uid_t)arg)
				continue;
			break;

		case KINFO_PROC_RUID:
			if (proc.p_ruid != (uid_t)arg)
				continue;
			break;
		}
I 14
#endif
E 14
		/*
		 * gather eproc
		 */
		eproc.e_paddr = p;
		if (kvm_read(proc.p_pgrp, &pgrp, sizeof (struct pgrp)) !=
	            sizeof (struct pgrp)) {
			seterr("can't read pgrp at %x", proc.p_pgrp);
			return (-1);
		}
		eproc.e_sess = pgrp.pg_session;
		eproc.e_pgid = pgrp.pg_id;
		eproc.e_jobc = pgrp.pg_jobc;
		if (kvm_read(pgrp.pg_session, &sess, sizeof (struct session))
		   != sizeof (struct session)) {
			seterr("can't read session at %x", pgrp.pg_session);
			return (-1);
		}
		if ((proc.p_flag&SCTTY) && sess.s_ttyp != NULL) {
			if (kvm_read(sess.s_ttyp, &tty, sizeof (struct tty))
			    != sizeof (struct tty)) {
				seterr("can't read tty at %x", sess.s_ttyp);
				return (-1);
			}
			eproc.e_tdev = tty.t_dev;
			eproc.e_tsess = tty.t_session;
			if (tty.t_pgrp != NULL) {
				if (kvm_read(tty.t_pgrp, &pgrp, sizeof (struct
				    pgrp)) != sizeof (struct pgrp)) {
					seterr("can't read tpgrp at &x", 
						tty.t_pgrp);
					return (-1);
				}
				eproc.e_tpgid = pgrp.pg_id;
			} else
				eproc.e_tpgid = -1;
		} else
			eproc.e_tdev = NODEV;
I 20
		eproc.e_flag = sess.s_ttyvp ? EPROC_CTTY : 0;
		if (sess.s_leader == p)
			eproc.e_flag |= EPROC_SLEADER;
E 20
		if (proc.p_wmesg)
			kvm_read(proc.p_wmesg, eproc.e_wmesg, WMESGLEN);
I 14
#ifdef NEWVM
		(void) kvm_read(proc.p_vmspace, &eproc.e_vm,
		    sizeof (struct vmspace));
		eproc.e_xsize = eproc.e_xrssize =
			eproc.e_xccount = eproc.e_xswrss = 0;
#else
E 14
		if (proc.p_textp) {
			kvm_read(proc.p_textp, &text, sizeof (text));
			eproc.e_xsize = text.x_size;
			eproc.e_xrssize = text.x_rssize;
			eproc.e_xccount = text.x_ccount;
			eproc.e_xswrss = text.x_swrss;
		} else {
			eproc.e_xsize = eproc.e_xrssize =
			  eproc.e_xccount = eproc.e_xswrss = 0;
		}
I 14
#endif
E 23
I 23
D 28
	p = btop(va & SG_PMASK);
	addr = (ste & SG_FRAME) + (p * sizeof(struct pte));
	lowram = vm->lowram;
E 23
E 14

E 28
D 23
		switch(ki_op(what)) {

		case KINFO_PROC_PGRP:
			if (eproc.e_pgid != (pid_t)arg)
				continue;
			break;

		case KINFO_PROC_TTY:
			if ((proc.p_flag&SCTTY) == 0 || 
			     eproc.e_tdev != (dev_t)arg)
				continue;
			break;
		}

		i++;
		bcopy(&proc, bp, sizeof (struct proc));
		bp += sizeof (struct proc);
		bcopy(&eproc, bp, sizeof (struct eproc));
		bp+= sizeof (struct eproc);
	}
	if (!doingzomb) {
		/* zombproc */
D 16
		if (kvm_read(nl[X_ZOMBPROC].n_value, &p, 
E 16
I 16
		if (kvm_read((void *) nl[X_ZOMBPROC].n_value, &p, 
E 16
		    sizeof (struct proc *)) != sizeof (struct proc *)) {
			seterr("can't read zombproc");
			return (-1);
		}
		doingzomb = 1;
		goto again;
	}

	return (i);
}
D 8
	
E 8

struct proc *
kvm_nextproc()
{

	if (!kvmprocbase && kvm_getprocs(0, 0) == -1)
		return (NULL);
	if (kvmprocptr >= (kvmprocbase + kvmnprocs)) {
		seterr("end of proc list");
		return (NULL);
	}
	return((struct proc *)(kvmprocptr++));
}

struct eproc *
kvm_geteproc(p)
D 13
	struct proc *p;
E 13
I 13
	const struct proc *p;
E 13
{
	return ((struct eproc *)(((char *)p) + sizeof (struct proc)));
}

kvm_setproc()
{
D 13

E 13
	kvmprocptr = kvmprocbase;
}

kvm_freeprocs()
{

	if (kvmprocbase) {
		free(kvmprocbase);
		kvmprocbase = NULL;
	}
}

I 14
#ifdef NEWVM
E 14
struct user *
kvm_getu(p)
I 14
D 16
	struct proc *p;
E 16
I 16
	const struct proc *p;
E 16
{
	register struct kinfo_proc *kp = (struct kinfo_proc *)p;
	register int i;
	register char *up;
D 16
	struct pte pte[CLSIZE*2];
E 16

	if (kvminit == 0 && kvm_init(NULL, NULL, NULL, 0) == -1)
		return (NULL);
	if (p->p_stat == SZOMB) {
		seterr("zombie process");
		return (NULL);
	}
E 23
	/*
D 21
	 * Reading from swap is too complicated right now.
	 */
D 20
	if ((p->p_flag & SLOAD) == 0)
E 20
I 20
	if ((p->p_flag & SLOAD) == 0) {
		seterr("can't read from swap yet");
E 20
		return(NULL);
I 20
	}
E 20
	/*
E 21
D 23
	 * Read u-area one page at a time for the benefit of post-mortems
E 23
I 23
	 * Address from STE is a physical address so don't use kvm_read.
E 23
	 */
D 23
	up = (char *) p->p_addr;
	for (i = 0; i < UPAGES; i++) {
D 20
		klseek(kmem, (long)up, 0);
E 20
I 20
		if (klseek(kmem, (long)up, 0) == -1)
			return (NULL);
E 20
		if (read(kmem, user.upages[i], CLBYTES) != CLBYTES) {
			seterr("cant read page %x of u of pid %d from %s",
			    up, p->p_pid, kmemf);
			return(NULL);
		}
		up += CLBYTES;
E 23
I 23
D 28
	if (lseek(kd->pmfd, (off_t)addr - lowram, 0) == -1 || 
E 28
I 28
	if (lseek(kd->pmfd, (off_t)(addr - lowram), 0) == -1 || 
E 28
	    read(kd->pmfd, (char *)&pte, sizeof(pte)) < 0)
		goto invalid;
	addr = pte & PG_FRAME;
D 28
	if (pte == PG_NV || addr < lowram) {
E 28
I 28
	if (pte == PG_NV) {
E 28
		_kvm_err(kd, 0, "page not valid");
		return (0);
E 23
	}
D 23
	pcbpf = (int) btop(p->p_addr);	/* what should this be really? */
	/*
	 * Conjure up a physical address for the arguments.
	 */
	argaddr0 = argaddr1 = 0;
#ifdef hp300
	if (kp->kp_eproc.e_vm.vm_pmap.pm_ptab) {
I 16
		struct pte pte[CLSIZE*2];

E 16
D 20
		klseek(kmem,
E 20
I 20
		if (klseek(kmem,
E 20
		    (long)&kp->kp_eproc.e_vm.vm_pmap.pm_ptab
D 20
		    [btoc(USRSTACK-CLBYTES*2)], 0);
E 20
I 20
		    [btoc(USRSTACK-CLBYTES*2)], 0) == -1)
			return (NULL);
E 20
		if (read(kmem, (char *)&pte, sizeof(pte)) == sizeof(pte)) {
I 16
#if CLBYTES < 2048
E 16
			argaddr0 = ctob(pftoc(pte[CLSIZE*0].pg_pfnum));
I 16
#endif
E 16
			argaddr1 = ctob(pftoc(pte[CLSIZE*1].pg_pfnum));
		}
	}
	kp->kp_eproc.e_vm.vm_rssize =
	    kp->kp_eproc.e_vm.vm_pmap.pm_stats.resident_count; /* XXX */
#endif
	return(&user.user);
}
#else
struct user *
kvm_getu(p)
E 14
D 13
	struct proc *p;
E 13
I 13
	const struct proc *p;
E 13
{
	struct pte *pteaddr, apte;
D 2
	struct pte arguutl[UPAGES+CLSIZE];
E 2
I 2
D 8
	struct pte arguutl[UPAGES+(CLSIZE*2)];
E 8
I 8
	struct pte arguutl[HIGHPAGES+(CLSIZE*2)];
E 8
E 2
	register int i;
	int ncl;

	if (kvminit == 0 && kvm_init(NULL, NULL, NULL, 0) == -1)
		return (NULL);
D 2
	if (p->p_stat == SZOMB)
E 2
I 2
	if (p->p_stat == SZOMB) {
		seterr("zombie process");
E 2
		return (NULL);
I 2
	}
E 2
	if ((p->p_flag & SLOAD) == 0) {
D 2
		if (swap < 0)
E 2
I 2
		if (swap < 0) {
			seterr("no swap");
E 2
			return (NULL);
I 2
		}
E 2
		(void) lseek(swap, (long)dtob(p->p_swaddr), 0);
		if (read(swap, (char *)&user.user, sizeof (struct user)) != 
		    sizeof (struct user)) {
D 14
			seterr("can't read u for pid %d from %s\n",
E 14
I 14
			seterr("can't read u for pid %d from %s",
E 14
			    p->p_pid, swapf);
			return (NULL);
		}
		pcbpf = 0;
D 2
		argaddr = 0;
E 2
I 2
		argaddr0 = 0;
		argaddr1 = 0;
E 2
		return (&user.user);
	}
	pteaddr = &Usrptmap[btokmx(p->p_p0br) + p->p_szpt - 1];
D 20
	klseek(kmem, (long)pteaddr, 0);
E 20
I 20
	if (klseek(kmem, (long)pteaddr, 0) == -1)
		return -1;
E 20
	if (read(kmem, (char *)&apte, sizeof(apte)) != sizeof(apte)) {
		seterr("can't read indir pte to get u for pid %d from %s",
		    p->p_pid, kmemf);
		return (NULL);
	}
D 8
	lseek(mem,
D 2
	    (long)ctob(apte.pg_pfnum+1) - (UPAGES+CLSIZE) * sizeof (struct pte),
E 2
I 2
	    (long)ctob(apte.pg_pfnum+1) - (UPAGES+(CLSIZE*2)) * sizeof (struct pte),
E 2
		0);
E 8
I 8
	lseek(mem, (long)ctob(pftoc(apte.pg_pfnum+1)) - sizeof(arguutl), 0);
E 8
	if (read(mem, (char *)arguutl, sizeof(arguutl)) != sizeof(arguutl)) {
		seterr("can't read page table for u of pid %d from %s",
		    p->p_pid, memf);
		return (NULL);
	}
	if (arguutl[0].pg_fod == 0 && arguutl[0].pg_pfnum)
D 2
		argaddr = ctob(arguutl[0].pg_pfnum);
E 2
I 2
D 8
		argaddr0 = ctob(arguutl[0].pg_pfnum);
E 8
I 8
		argaddr0 = ctob(pftoc(arguutl[0].pg_pfnum));
E 8
E 2
	else
D 2
		argaddr = 0;
	pcbpf = arguutl[CLSIZE].pg_pfnum;
E 2
I 2
		argaddr0 = 0;
	if (arguutl[CLSIZE*1].pg_fod == 0 && arguutl[CLSIZE*1].pg_pfnum)
D 8
		argaddr1 = ctob(arguutl[CLSIZE*1].pg_pfnum);
E 8
I 8
		argaddr1 = ctob(pftoc(arguutl[CLSIZE*1].pg_pfnum));
E 8
	else
		argaddr1 = 0;
	pcbpf = arguutl[CLSIZE*2].pg_pfnum;
E 2
D 8
	ncl = (sizeof (struct user) + NBPG*CLSIZE - 1) / (NBPG*CLSIZE);
E 8
I 8
	ncl = (sizeof (struct user) + CLBYTES - 1) / CLBYTES;
E 8
	while (--ncl >= 0) {
		i = ncl * CLSIZE;
D 2
		lseek(mem, (long)ctob(arguutl[CLSIZE+i].pg_pfnum), 0);
E 2
I 2
D 8
		lseek(mem, (long)ctob(arguutl[(CLSIZE*2)+i].pg_pfnum), 0);
E 2
		if (read(mem, user.upages[i], CLSIZE*NBPG) != CLSIZE*NBPG) {
E 8
I 8
		lseek(mem,
		      (long)ctob(pftoc(arguutl[(CLSIZE*2)+i].pg_pfnum)), 0);
		if (read(mem, user.upages[i], CLBYTES) != CLBYTES) {
E 8
			seterr("can't read page %d of u of pid %d from %s",
D 8
			    arguutl[CLSIZE+i].pg_pfnum, p->p_pid, memf);
E 8
I 8
			    arguutl[(CLSIZE*2)+i].pg_pfnum, p->p_pid, memf);
E 8
			return(NULL);
		}
	}
	return (&user.user);
}
I 14
#endif
E 14

char *
kvm_getargs(p, up)
D 13
	struct proc *p;
	struct user *up;
E 13
I 13
	const struct proc *p;
	const struct user *up;
E 13
{
D 2
	char cmdbuf[CLSIZE*NBPG];
E 2
I 2
D 8
	char cmdbuf[CLSIZE*NBPG*2];
E 8
I 8
D 19
	char cmdbuf[CLBYTES*2];
E 19
I 19
	static char cmdbuf[CLBYTES*2];
E 19
E 8
E 2
	union {
D 2
		char	argc[CLSIZE*NBPG];
		int	argi[CLSIZE*NBPG/sizeof (int)];
E 2
I 2
D 8
		char	argc[CLSIZE*NBPG*2];
		int	argi[CLSIZE*NBPG*2/sizeof (int)];
E 8
I 8
		char	argc[CLBYTES*2];
		int	argi[CLBYTES*2/sizeof (int)];
E 8
E 2
	} argspac;
	register char *cp;
	register int *ip;
	char c;
	int nbad;
I 14
#ifndef NEWVM
E 14
	struct dblock db;
I 14
#endif
E 14
D 18
	char *file;
E 18
I 18
	const char *file;
E 18
I 14
	int stkoff = 0;
E 14

I 14
#if defined(NEWVM) && defined(hp300)
D 16
	stkoff = 24;	/* XXX for sigcode */
E 16
I 16
	stkoff = 20;			/* XXX for sigcode */
E 16
#endif
E 14
D 2
	if (p->p_pid == 0)
		return ("swapper");	/* XXX should be set in kernel */
	if (p->p_pid == 2)
		return ("pagedaemon");
E 2
D 4
	if (p->p_stat == SZOMB)
		return ("<defunct>");
	if (p->p_flag & SWEXIT)
		return ("<exiting>");
E 4
D 2
	if (up == NULL)
E 2
I 2
	if (up == NULL || p->p_pid == 0 || p->p_pid == 2)
E 2
		goto retucomm;
D 2
	if ((p->p_flag & SLOAD) == 0 || argaddr == 0) {
E 2
I 2
	if ((p->p_flag & SLOAD) == 0 || argaddr1 == 0) {
I 14
#ifdef NEWVM
		goto retucomm;	/* XXX for now */
#else
E 14
E 2
D 8
		if (swap < 0)
E 8
I 8
		if (swap < 0 || p->p_ssize == 0)
E 8
			goto retucomm;
		vstodb(0, CLSIZE, &up->u_smap, &db, 1);
		(void) lseek(swap, (long)dtob(db.db_base), 0);
D 2
		if (read(swap, (char *)&argspac, sizeof(argspac))
		    != sizeof(argspac))
E 2
I 2
D 8
		if (read(swap, (char *)&argspac.argc[NBPG*CLSIZE], 
			NBPG*CLSIZE) != NBPG*CLSIZE)
E 8
I 8
		if (read(swap, (char *)&argspac.argc[CLBYTES], CLBYTES)
			!= CLBYTES)
E 8
E 2
			goto bad;
I 2
		vstodb(1, CLSIZE, &up->u_smap, &db, 1);
		(void) lseek(swap, (long)dtob(db.db_base), 0);
D 8
		if (read(swap, (char *)&argspac.argc[0], 
			NBPG*CLSIZE) != NBPG*CLSIZE)
E 8
I 8
		if (read(swap, (char *)&argspac.argc[0], CLBYTES) != CLBYTES)
E 8
			goto bad;
E 2
		file = swapf;
I 14
#endif
E 14
	} else {
D 2
		lseek(mem, (long)argaddr, 0);
		if (read(mem, (char *)&argspac, sizeof (argspac))
		    != sizeof (argspac))
E 2
I 2
		if (argaddr0) {
			lseek(mem, (long)argaddr0, 0);
D 8
			if (read(mem, (char *)&argspac, NBPG*CLSIZE)
			    != NBPG*CLSIZE)
E 8
I 8
			if (read(mem, (char *)&argspac, CLBYTES) != CLBYTES)
E 8
				goto bad;
		} else
D 8
			bzero(&argspac, NBPG*CLSIZE);
E 8
I 8
			bzero(&argspac, CLBYTES);
E 8
		lseek(mem, (long)argaddr1, 0);
D 8
		if (read(mem, &argspac.argc[NBPG*CLSIZE], NBPG*CLSIZE)
		    != NBPG*CLSIZE)
E 8
I 8
		if (read(mem, &argspac.argc[CLBYTES], CLBYTES) != CLBYTES)
E 8
E 2
			goto bad;
D 16
		file = memf;
E 16
I 16
		file = (char *) memf;
E 16
	}
D 2
	ip = &argspac.argi[CLSIZE*NBPG/sizeof (int)];
E 2
I 2
D 8
	ip = &argspac.argi[CLSIZE*NBPG*2/sizeof (int)];
E 8
I 8
	ip = &argspac.argi[CLBYTES*2/sizeof (int)];
E 8
E 2
D 16
	ip -= 2;		/* last arg word and .long 0 */
E 16
I 16
	ip -= 2;                /* last arg word and .long 0 */
E 16
I 14
	ip -= stkoff / sizeof (int);
E 14
	while (*--ip) {
		if (ip == argspac.argi)
			goto retucomm;
	}
	*(char *)ip = ' ';
	ip++;
	nbad = 0;
D 2
	for (cp = (char *)ip; cp < &argspac.argc[CLSIZE*NBPG]; cp++) {
E 2
I 2
D 8
	for (cp = (char *)ip; cp < &argspac.argc[CLSIZE*NBPG*2]; cp++) {
E 8
I 8
D 14
	for (cp = (char *)ip; cp < &argspac.argc[CLBYTES*2]; cp++) {
E 14
I 14
	for (cp = (char *)ip; cp < &argspac.argc[CLBYTES*2-stkoff]; cp++) {
E 14
E 8
E 2
		c = *cp & 0177;
		if (c == 0)
			*cp = ' ';
		else if (c < ' ' || c > 0176) {
			if (++nbad >= 5*(0+1)) {	/* eflg -> 0 XXX */
				*cp++ = ' ';
				break;
			}
			*cp = '?';
		} else if (0 == 0 && c == '=') {	/* eflg -> 0 XXX */
			while (*--cp != ' ')
				if (cp <= (char *)ip)
					break;
			break;
		}
	}
	*cp = 0;
	while (*--cp == ' ')
		*cp = 0;
	cp = (char *)ip;
D 2
	(void) strncpy(cmdbuf, cp, &argspac.argc[CLSIZE*NBPG] - cp);
E 2
I 2
D 8
	(void) strncpy(cmdbuf, cp, &argspac.argc[CLSIZE*NBPG*2] - cp);
E 8
I 8
	(void) strncpy(cmdbuf, cp, &argspac.argc[CLBYTES*2] - cp);
E 8
E 2
	if (cp[0] == '-' || cp[0] == '?' || cp[0] <= ' ') {
		(void) strcat(cmdbuf, " (");
		(void) strncat(cmdbuf, p->p_comm, sizeof(p->p_comm));
		(void) strcat(cmdbuf, ")");
	}
	return (cmdbuf);

bad:
D 14
	seterr("error locating command name for pid %d from %s\n",
E 14
I 14
	seterr("error locating command name for pid %d from %s",
E 14
	    p->p_pid, file);
retucomm:
	(void) strcpy(cmdbuf, " (");
	(void) strncat(cmdbuf, p->p_comm, sizeof (p->p_comm));
	(void) strcat(cmdbuf, ")");
	return (cmdbuf);
}


static
getkvars()
{
D 13

E 13
D 19
	if (kvm_nlist(nl) == -1)
E 19
I 19
	int ret;
	static nlisterr();

	if ((ret = kvm_nlist(nl)) == -1)
E 19
		return (-1);
I 19
	else if (ret > 0)
		nlisterr(nl);
E 19
	if (deadkernel) {
		/* We must do the sys map first because klseek uses it */
		long	addr;
D 20

I 14
#ifndef NEWVM
E 14
		Syssize = nl[X_SYSSIZE].n_value;
		Sysmap = (struct pte *)
			calloc((unsigned) Syssize, sizeof (struct pte));
		if (Sysmap == NULL) {
			seterr("out of space for Sysmap");
			return (-1);
		}
		addr = (long) nl[X_SYSMAP].n_value;
		addr &= ~KERNBASE;
		(void) lseek(kmem, addr, 0);
		if (read(kmem, (char *) Sysmap, Syssize * sizeof (struct pte))
		    != Syssize * sizeof (struct pte)) {
			seterr("can't read Sysmap");
			return (-1);
		}
I 14
#endif
E 20
E 14
I 8
#if defined(hp300)
		addr = (long) nl[X_LOWRAM].n_value;
		(void) lseek(kmem, addr, 0);
		if (read(kmem, (char *) &lowram, sizeof (lowram))
		    != sizeof (lowram)) {
			seterr("can't read lowram");
			return (-1);
		}
		lowram = btop(lowram);
I 14
		Sysseg = (struct ste *) malloc(NBPG);
		if (Sysseg == NULL) {
			seterr("out of space for Sysseg");
			return (-1);
		}
		addr = (long) nl[X_SYSSEG].n_value;
		(void) lseek(kmem, addr, 0);
		read(kmem, (char *)&addr, sizeof(addr));
		(void) lseek(kmem, (long)addr, 0);
		if (read(kmem, (char *) Sysseg, NBPG) != NBPG) {
			seterr("can't read Sysseg");
			return (-1);
		}
E 14
#endif
E 8
	}
I 22
#ifndef NEWVM
E 22
I 14
D 20
#ifndef NEWVM
E 14
	usrpt = (struct pte *)nl[X_USRPT].n_value;
	Usrptmap = (struct pte *)nl[X_USRPTMAP].n_value;
I 14
#endif
E 20
E 14
D 16
	if (kvm_read((long)nl[X_NSWAP].n_value, &nswap, sizeof (long)) !=
E 16
I 16
	if (kvm_read((void *) nl[X_NSWAP].n_value, &nswap, sizeof (long)) !=
E 16
	    sizeof (long)) {
		seterr("can't read nswap");
		return (-1);
	}
D 16
	if (kvm_read((long)nl[X_DMMIN].n_value, &dmmin, sizeof (long)) !=
E 16
I 16
	if (kvm_read((void *) nl[X_DMMIN].n_value, &dmmin, sizeof (long)) !=
E 16
	    sizeof (long)) {
		seterr("can't read dmmin");
		return (-1);
	}
D 16
	if (kvm_read((long)nl[X_DMMAX].n_value, &dmmax, sizeof (long)) !=
E 16
I 16
	if (kvm_read((void *) nl[X_DMMAX].n_value, &dmmax, sizeof (long)) !=
E 16
	    sizeof (long)) {
		seterr("can't read dmmax");
		return (-1);
	}
I 22
#endif
E 23
I 23
D 28
	offset = va & PGOFSET;
E 28
	*pa = addr - lowram + offset;
	
	return (NBPG - offset);
invalid:
	_kvm_err(kd, 0, "invalid address (%x)", va);
E 23
E 22
	return (0);
}
I 19

D 23
static
nlisterr(nl)
	struct nlist nl[];
E 23
I 23
int
_kvm_kvatop(kd, va, pa)
	kvm_t *kd;
	u_long va;
	u_long *pa;
E 23
{
D 23
	int i;

	fprintf(stderr, "kvm_nlist: can't find following names:");
	for (i = 0; nl[i].n_name[0] != '\0'; i++)
		if (nl[i].n_value == 0)
			fprintf(stderr, " %s", nl[i].n_name);
	fprintf(stderr, ": continuing...\n");
}

E 19

kvm_read(loc, buf, len)
D 16
	unsigned long loc;
	char *buf;
E 16
I 16
	void *loc;
	void *buf;
E 16
{
I 2
	if (kvmfilesopen == 0 && kvm_openfiles(NULL, NULL, NULL) == -1)
		return (-1);
E 2
D 8
	if (loc & KERNBASE) {
E 8
I 8
	if (iskva(loc)) {
E 8
D 17
		klseek(kmem, loc, 0);
E 17
I 17
D 20
		klseek(kmem, (off_t) loc, 0);
E 20
I 20
		if (klseek(kmem, (off_t) loc, 0) == -1)
			return -1;
E 20
E 17
		if (read(kmem, buf, len) != len) {
D 14
			seterr("error reading kmem at %x\n", loc);
E 14
I 14
			seterr("error reading kmem at %x", loc);
E 14
			return (-1);
		}
	} else {
D 17
		lseek(mem, loc, 0);
E 17
I 17
		lseek(mem, (off_t) loc, 0);
E 17
		if (read(mem, buf, len) != len) {
D 14
			seterr("error reading mem at %x\n", loc);
E 14
I 14
			seterr("error reading mem at %x", loc);
E 14
			return (-1);
		}
	}
	return (len);
}

D 13
static
E 13
I 13
D 20
static void
E 20
I 20
static
E 20
E 13
klseek(fd, loc, off)
	int fd;
D 2
	long loc;
E 2
I 2
	off_t loc;
E 2
	int off;
{
I 2

E 2
	if (deadkernel) {
I 2
D 13
		off_t vtophys();

E 13
E 2
		if ((loc = vtophys(loc)) == -1)
D 20
			return;
E 20
I 20
			return -1;
E 20
	}
D 2
	(void) lseek(fd, (long)loc, off);
E 2
I 2
D 20
	(void) lseek(fd, (off_t)loc, off);
E 20
I 20
	(void)lseek(fd, (off_t)loc, off);
E 23
I 23
D 28
	if (va >= KERNBASE)
		return (_kvm_vatop(kd, (u_long)kd->vmst->Sysseg, va, pa));
	_kvm_err(kd, 0, "invalid address (%x)", va);
E 23
	return (0);
E 28
I 28
	return (_kvm_vatop(kd, (u_long)kd->vmst->Sysseg, va, pa));
E 28
E 20
E 2
}

I 14
D 23
#ifndef NEWVM
E 23
E 14
/*
D 23
 * Given a base/size pair in virtual swap area,
 * return a physical base/size pair which is the
 * (largest) initial, physically contiguous block.
E 23
I 23
 * Translate a user virtual address to a physical address.
E 23
 */
D 13
static
E 13
I 13
D 23
static void
E 13
vstodb(vsbase, vssize, dmp, dbp, rev)
	register int vsbase;
	int vssize;
	struct dmap *dmp;
	register struct dblock *dbp;
E 23
I 23
int
_kvm_uvatop(kd, p, va, pa)
	kvm_t *kd;
	const struct proc *p;
	u_long va;
	u_long *pa;
E 23
{
D 23
	register int blk = dmmin;
	register swblk_t *ip = dmp->dm_map;
E 23
I 23
	register struct vmspace *vms = p->p_vmspace;
	int kva;
E 23

I 28
	/*
	 * If this is a live kernel we just look it up in the kernel
	 * virtually allocated flat 4mb page table (i.e. let the kernel
	 * do the table walk).  In this way, we avoid needing to know
	 * the MMU type.
	 */
	if (ISALIVE(kd)) {
		struct pte *ptab;
		int pte, offset;

		kva = (int)&vms->vm_pmap.pm_ptab;
		if (KREAD(kd, kva, &ptab)) {
			_kvm_err(kd, 0, "invalid address (%x)", va);
			return (0);
		}
		kva = (int)&ptab[btop(va)];
		if (KREAD(kd, kva, &pte) || (pte & PG_V) == 0) {
			_kvm_err(kd, 0, "invalid address (%x)", va);
			return (0);
		}
		offset = va & PGOFSET;
		*pa = (pte & PG_FRAME) | offset;
		return (NBPG - offset);
	}
	/*
	 * Otherwise, we just walk the table ourself.
	 */
E 28
D 23
	vsbase = ctod(vsbase);
	vssize = ctod(vssize);
	if (vsbase < 0 || vsbase + vssize > dmp->dm_size)
		/*panic("vstodb")*/;
	while (vsbase >= blk) {
		vsbase -= blk;
		if (blk < dmmax)
			blk *= 2;
		ip++;
E 23
I 23
	kva = (int)&vms->vm_pmap.pm_stab;
D 28
	if (kvm_read(kd, kva, (char *)&kva, 4) != 4) {
E 28
I 28
	if (KREAD(kd, kva, &kva)) {
E 28
		_kvm_err(kd, 0, "invalid address (%x)", va);
		return (0);
E 23
	}
D 23
	if (*ip <= 0 || *ip + blk > nswap)
		/*panic("vstodb")*/;
	dbp->db_size = MIN(vssize, blk - vsbase);
	dbp->db_base = *ip + (rev ? blk - (vsbase + dbp->db_size) : vsbase);
}
I 14
#endif
E 14

I 14
#ifdef NEWVM
E 14
D 8
/*
 * This routine was stolen from adb to simulate memory management
 * on the VAX.
 */
E 8
static off_t
vtophys(loc)
I 14
	long	loc;
{
	off_t newloc = (off_t) -1;
#ifdef hp300
	int p, ste, pte;

	ste = *(int *)&Sysseg[loc >> SG_ISHIFT];
	if ((ste & SG_V) == 0) {
D 20
		seterr("vtophys: segment not valid");
E 20
I 20
		seterr("vtophys: segment not valid (%x)", ste);
E 20
		return((off_t) -1);
	}
	p = btop(loc & SG_PMASK);
	newloc = (ste & SG_FRAME) + (p * sizeof(struct pte));
	(void) lseek(kmem, (long)(newloc-(off_t)ptob(lowram)), 0);
	if (read(kmem, (char *)&pte, sizeof pte) != sizeof pte) {
		seterr("vtophys: cannot locate pte");
		return((off_t) -1);
	}
	newloc = pte & PG_FRAME;
	if (pte == PG_NV || newloc < (off_t)ptob(lowram)) {
		seterr("vtophys: page not valid");
		return((off_t) -1);
	}
	newloc = (newloc - (off_t)ptob(lowram)) + (loc & PGOFSET);
#endif
	return((off_t) newloc);
}
#else
static off_t
vtophys(loc)
E 14
	long loc;
{
D 8
	register p;
E 8
I 8
	int p;
E 8
	off_t newloc;
I 8
	register struct pte *pte;
E 8

	newloc = loc & ~KERNBASE;
	p = btop(newloc);
I 8
#if defined(vax) || defined(tahoe)
E 8
	if ((loc & KERNBASE) == 0) {
		seterr("vtophys: translating non-kernel address");
		return((off_t) -1);
	}
I 8
#endif
E 8
	if (p >= Syssize) {
		seterr("vtophys: page out of bound (%d>=%d)", p, Syssize);
		return((off_t) -1);
	}
D 8
	if (Sysmap[p].pg_v == 0 &&
	    (Sysmap[p].pg_fod || Sysmap[p].pg_pfnum == 0)) {
E 8
I 8
	pte = &Sysmap[p];
	if (pte->pg_v == 0 && (pte->pg_fod || pte->pg_pfnum == 0)) {
E 8
		seterr("vtophys: page not valid");
		return((off_t) -1);
	}
D 8
	loc = (long) (ptob(Sysmap[p].pg_pfnum) + (loc & PGOFSET));
E 8
I 8
#if defined(hp300)
	if (pte->pg_pfnum < lowram) {
		seterr("vtophys: non-RAM page (%d<%d)", pte->pg_pfnum, lowram);
		return((off_t) -1);
	}
#endif
	loc = (long) (ptob(pftoc(pte->pg_pfnum)) + (loc & PGOFSET));
E 8
	return(loc);
}
I 14
#endif
E 14

#include <varargs.h>
D 9
static char errbuf[LINE_MAX];
E 9
I 9
D 10
static char errbuf[_BSD_LINE_MAX];
E 10
I 10
static char errbuf[_POSIX2_LINE_MAX];
E 10
E 9

D 13
static
E 13
I 13
static void
E 13
seterr(va_alist)
	va_dcl
{
	char *fmt;
	va_list ap;

	va_start(ap);
	fmt = va_arg(ap, char *);
D 16
	(void) vsprintf(errbuf, fmt, ap);
E 16
I 16
	(void) vsnprintf(errbuf, _POSIX2_LINE_MAX, fmt, ap);
E 16
	va_end(ap);
}

D 13
static
E 13
I 13
static void
E 13
setsyserr(va_alist)
	va_dcl
{
	char *fmt, *cp;
	va_list ap;
D 8
	extern errno;
E 8
I 8
	extern int errno;
E 8

	va_start(ap);
	fmt = va_arg(ap, char *);
D 16
	(void) vsprintf(errbuf, fmt, ap);
E 16
I 16
	(void) vsnprintf(errbuf, _POSIX2_LINE_MAX, fmt, ap);
E 16
	for (cp=errbuf; *cp; cp++)
		;
D 16
	sprintf(cp, ": %s", strerror(errno));
E 16
I 16
	snprintf(cp, _POSIX2_LINE_MAX - (cp - errbuf), ": %s", strerror(errno));
E 16
	va_end(ap);
}

char *
kvm_geterr()
{
D 8

E 8
	return (errbuf);
E 23
I 23
	return (_kvm_vatop(kd, kva, va, pa));
E 23
}
E 1
