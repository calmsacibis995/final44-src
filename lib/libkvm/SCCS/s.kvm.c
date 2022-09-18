h18683
s 00008/00000/00506
d D 8.2 94/02/13 11:09:38 hibler 36 35
c break out of kvm_read loop if read syscall returns 0
e
s 00002/00002/00504
d D 8.1 93/06/04 16:53:16 bostic 35 34
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00013/00491
d D 5.33 93/04/27 15:27:35 bostic 34 33
c kinfo_proc moved into sysctl.h; minor cleanups, don't use ANSI C!!
e
s 00003/00002/00501
d D 5.32 92/10/17 15:15:30 bostic 33 32
c snprintf returns printed length, not actual length
e
s 00001/00000/00502
d D 5.31 92/05/28 16:09:34 mckusick 32 31
c need unistd.h
e
s 00005/00005/00497
d D 5.30 92/05/26 18:43:44 bostic 31 30
c kvm_read, kvm_write now take void *'s, not char *'s
e
s 00001/00001/00501
d D 5.29 92/05/26 14:40:18 bostic 30 29
c update copyright year
e
s 00004/00000/00498
d D 5.28 92/05/26 14:37:29 bostic 29 28
c add LBL credit line
e
s 00034/00012/00464
d D 5.27 92/05/18 20:58:48 torek 28 27
c make kvm_write work
e
s 00052/00026/00424
d D 5.26 92/04/29 12:09:20 bostic 27 26
c use standard C declarations, use strerror
e
s 00028/00025/00422
d D 5.25 92/04/29 11:41:35 bostic 26 24
c update from LBL (Chris, Craig and Steve)
e
s 00001/00001/00446
d R 5.25 92/04/24 15:08:44 bostic 25 24
c move the kernel file to /var/db
e
s 00002/00000/00445
d D 5.24 92/04/08 03:02:35 torek 24 23
c notice dbm_open failures rather than blindly using NULL
e
s 00341/00975/00104
d D 5.23 92/04/03 14:53:48 mckusick 23 22
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
D 30
 * Copyright (c) 1989 The Regents of the University of California.
E 30
I 30
D 35
 * Copyright (c) 1989, 1992 The Regents of the University of California.
E 30
 * All rights reserved.
E 35
I 35
 * Copyright (c) 1989, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 35
 *
I 29
 * This code is derived from software developed by the Computer Systems
 * Engineering group at Lawrence Berkeley Laboratory under DARPA contract
 * BG 91-66 and contributed to Berkeley.
 *
E 29
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
#include <sys/ioctl.h>
I 12
D 23
#include <sys/kinfo.h>
E 12
#include <sys/tty.h>
E 23
I 23
#include <sys/stat.h>
I 34
#include <sys/sysctl.h>

#include <vm/vm.h>
#include <vm/vm_param.h>
#include <vm/swap_pager.h>

E 34
E 23
I 14
#include <machine/vmparam.h>
I 34

#include <ctype.h>
#include <db.h>
E 34
E 14
I 12
#include <fcntl.h>
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
D 34
#include <nlist.h>
E 34
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
D 26
#include <ndbm.h>
E 26
I 26
D 34
#include <db.h>
E 34
I 34
#include <limits.h>
#include <nlist.h>
E 34
E 26
D 23
#include <limits.h>
E 23
#include <paths.h>
I 2
#include <stdio.h>
I 12
D 34
#include <string.h>
E 34
I 27
#include <stdlib.h>
I 34
#include <string.h>
E 34
I 32
#include <unistd.h>
E 32
E 27
I 23
D 34
#include <ctype.h>
E 34
E 23
E 12
E 2

I 14
D 23
#ifdef SPPWAIT
#define NEWVM
#endif

#ifdef NEWVM
#define	btop(x)		(((unsigned)(x)) >> PGSHIFT)	/* XXX */
#define	ptob(x)		((caddr_t)((x) << PGSHIFT))	/* XXX */
E 23
D 34
#include <vm/vm.h>	/* ??? kinfo_proc currently includes this*/
I 23
#include <vm/vm_param.h>
#include <vm/swap_pager.h>
E 23
#include <sys/kinfo_proc.h>
D 16
#else
E 16
I 16
D 23
#ifdef hp300
#include <hp300/hp300/pte.h>
#endif
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
E 23
I 23
#include <limits.h>
E 23
E 8
E 2

E 34
D 2
#define KVMDBDIR	"/var/run"
E 2
I 2
D 23
#define basename(cp)	((tmp=rindex((cp), '/')) ? tmp+1 : (cp))
E 2
#define	MAXSYMSIZE	256
E 23
I 23
#include "kvm_private.h"
E 23
D 2
#define	KVMDB_NLIST	1
#define	KVMDB_DEVS	2
E 2

I 8
D 23
#if defined(hp300)
#define pftoc(f)	((f) - lowram)
#define iskva(v)	(1)
#endif
E 23
I 23
D 27
#include <stdarg.h>
E 23

E 27
D 23
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
E 23
I 23
D 34
static int kvm_dbopen(kvm_t *, const char *);
E 34
I 34
static int kvm_dbopen __P((kvm_t *, const char *));
E 34
E 23

E 8
D 23
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
};
E 23
I 23
char *
D 34
kvm_geterr(kvm_t *kd)
E 34
I 34
kvm_geterr(kd)
	kvm_t *kd;
E 34
{
	return (kd->errbuf);
}
E 23

I 27
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

E 27
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
E 20

E 23
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
/*
D 23
 * returns 	0 if files were opened now,
 * 		1 if files were already opened,
 *		-1 if files could not be opened.
E 23
I 23
 * Report an error using printf style arguments.  "program" is kd->program
 * on hard errors, and 0 on soft errors, so that under sun error emulation,
 * only hard errors are printed out (otherwise, programs like gdb will
 * generate tons of error messages when trying to access bogus pointers).
E 23
 */
E 2
D 23
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
I 27
#if __STDC__
E 27
_kvm_err(kvm_t *kd, const char *program, const char *fmt, ...)
I 27
#else
_kvm_err(kd, program, fmt, va_alist)
	kvm_t *kd;
	char *program, *fmt;
	va_dcl
#endif
E 27
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
E 23
I 23
	va_list ap;
E 23

I 27
#ifdef __STDC__
E 27
D 23
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
	va_start(ap, fmt);
D 27
	if (program != 0) {
		fprintf(stderr, "%s: ", program);
		vfprintf(stderr, fmt, ap);
		fputc('\n', stderr);
E 27
I 27
#else
	va_start(ap);
#endif
	if (program != NULL) {
		(void)fprintf(stderr, "%s: ", program);
		(void)vfprintf(stderr, fmt, ap);
		(void)fputc('\n', stderr);
E 27
	} else
D 27
		vsnprintf(kd->errbuf, sizeof(kd->errbuf), (char *)fmt, ap);
E 27
I 27
		(void)vsnprintf(kd->errbuf,
		    sizeof(kd->errbuf), (char *)fmt, ap);
E 27

	va_end(ap);
E 23
}

I 2
D 23
static
kvm_init(uf, mf, sf)
	char *uf, *mf, *sf;
E 23
I 23
void
I 27
#if __STDC__
E 27
_kvm_syserr(kvm_t *kd, const char *program, const char *fmt, ...)
I 27
#else
_kvm_syserr(kd, program, fmt, va_alist)
	kvm_t *kd;
	char *program, *fmt;
	va_dcl
#endif
E 27
E 23
{
D 23
	if (kvmfilesopen == 0 && kvm_openfiles(NULL, NULL, NULL) == -1)
		return (-1);
	if (getkvars() == -1)
		return (-1);
	kvminit = 1;
E 23
I 23
	va_list ap;
	register int n;
E 23

I 27
#if __STDC__
E 27
D 23
	return (0);
}
E 23
I 23
	va_start(ap, fmt);
D 27
	if (program != 0) {
		fprintf(stderr, "%s: ", program);
		vfprintf(stderr, fmt, ap);
		fprintf(stderr, ": ");
		perror((char *)0);
E 27
I 27
#else
	va_start(ap);
#endif
	if (program != NULL) {
		(void)fprintf(stderr, "%s: ", program);
		(void)vfprintf(stderr, fmt, ap);
		(void)fprintf(stderr, ": %s\n", strerror(errno));
E 27
	} else {
		register char *cp = kd->errbuf;
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
D 27
		vsnprintf(cp, sizeof(kd->errbuf), (char *)fmt, ap);
		n = strlen(cp);
		snprintf(&cp[n], sizeof(kd->errbuf) - n, ": %s",
E 27
I 27
D 33
		n = vsnprintf(cp, sizeof(kd->errbuf), (char *)fmt, ap);
E 33
I 33
		(void)vsnprintf(cp, sizeof(kd->errbuf), (char *)fmt, ap);
		n = strlen(cp);
E 33
		(void)snprintf(&cp[n], sizeof(kd->errbuf) - n, ": %s",
E 27
D 33
			 strerror(errno));
E 33
I 33
		    strerror(errno));
E 33
E 23
	}
D 23
	if (kmem != -1) {
		if (kmem != mem)
			close(kmem);
		/* otherwise kmem is a copy of mem, and will be closed below */
		kmem = -1;
	}
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
	}
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
	va_end(ap);
E 23
E 16
E 2
}

D 23
kvm_nlist(nl)
	struct nlist *nl;
E 23
I 23
void *
_kvm_malloc(kd, n)
	register kvm_t *kd;
	register size_t n;
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
D 27
	void *p = (void *)malloc(n);
E 27
I 27
	void *p;
E 27
E 23

D 23
	if (kvmfilesopen == 0 && kvm_openfiles(NULL, NULL, NULL) == -1)
		return (-1);
	if (deadkernel)
		goto hard2;
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
	 * initialize key datum
E 2
	 */
	key.dptr = symbuf;
D 12
	symbuf[0] = KVMDB_NLIST;
E 12
I 2

	if (db != NULL)
		goto win;	/* off to the races */
E 2
	/*
D 2
	 * read version string from database
E 2
I 2
	 * open database
E 2
	 */
I 2
D 11
	sprintf(dbname, "%s/kvm_%s", KVMDBDIR, basename(unixf));
E 11
I 11
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
	}
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
E 23
I 23
D 27
	if (p == 0)
		_kvm_err(kd, kd->program, "out of memory");
E 27
I 27
	if ((p = malloc(n)) == NULL)
		_kvm_err(kd, kd->program, strerror(errno));
E 27
	return (p);
E 23
E 16
E 2
}

D 23
kvm_getprocs(what, arg)
I 13
	int what, arg;
E 23
I 23
static kvm_t *
_kvm_open(kd, uf, mf, sf, flag, errout)
	register kvm_t *kd;
	const char *uf;
	const char *mf;
	const char *sf;
	int flag;
	char *errout;
E 23
E 13
{
I 2
D 23
	if (kvminit == 0 && kvm_init(NULL, NULL, NULL, 0) == -1)
		return (NULL);
E 2
	if (!deadkernel) {
		int ret, copysize;
E 23
I 23
	struct stat st;
E 23

D 23
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
E 23
I 23
	kd->vmfd = -1;
	kd->pmfd = -1;
	kd->swfd = -1;
	kd->nlfd = -1;
	kd->vmst = 0;
	kd->db = 0;
	kd->procbase = 0;
	kd->argspc = 0;
	kd->argv = 0;
E 23
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
D 23
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
E 23
I 23
	if (uf == 0)
		uf = _PATH_UNIX;
	else if (strlen(uf) >= MAXPATHLEN) {
		_kvm_err(kd, kd->program, "exec file name too long");
		goto failed;
E 23
	}
D 23
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
E 23
I 23
	if (flag & ~O_RDWR) {
		_kvm_err(kd, kd->program, "bad flags arg");
		goto failed;
E 23
	}
I 23
	if (mf == 0)
		mf = _PATH_MEM;
	if (sf == 0)
		sf = _PATH_DRUM;
E 23

D 23
again:
	for (; p; p = proc.p_nxt) {
		if (kvm_read(p, &proc, sizeof (struct proc)) !=
		    sizeof (struct proc)) {
			seterr("can't read proc at %x", p);
			return (-1);
E 23
I 23
	if ((kd->pmfd = open(mf, flag, 0)) < 0) {
		_kvm_syserr(kd, kd->program, "%s", mf);
		goto failed;
	}
	if (fstat(kd->pmfd, &st) < 0) {
		_kvm_syserr(kd, kd->program, "%s", mf);
		goto failed;
	}
	if (S_ISCHR(st.st_mode)) {
		/*
		 * If this is a character special device, then check that
		 * it's /dev/mem.  If so, open kmem too.  (Maybe we should
		 * make it work for either /dev/mem or /dev/kmem -- in either
		 * case you're working with a live kernel.)
		 */
		if (strcmp(mf, _PATH_MEM) != 0) {	/* XXX */
			_kvm_err(kd, kd->program,
				 "%s: not physical memory device", mf);
			goto failed;
E 23
		}
I 14
D 23
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
E 23
I 23
		if ((kd->vmfd = open(_PATH_KMEM, flag)) < 0) {
			_kvm_syserr(kd, kd->program, "%s", _PATH_KMEM);
			goto failed;
E 23
		}
D 23
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
E 23
I 23
		if ((kd->swfd = open(sf, flag, 0)) < 0) {
			_kvm_syserr(kd, kd->program, "%s", sf);
			goto failed;
E 23
		}
I 14
D 23
#endif
E 23
E 14
		/*
D 23
		 * gather eproc
E 23
I 23
		 * Open kvm nlist database.  We go ahead and do this
		 * here so that we don't have to hold on to the vmunix
		 * path name.  Since a kvm application will surely do
		 * a kvm_nlist(), this probably won't be a wasted effort.
		 * If the database cannot be opened, open the namelist
		 * argument so we revert to slow nlist() calls.
E 23
		 */
D 23
		eproc.e_paddr = p;
		if (kvm_read(proc.p_pgrp, &pgrp, sizeof (struct pgrp)) !=
	            sizeof (struct pgrp)) {
			seterr("can't read pgrp at %x", proc.p_pgrp);
			return (-1);
E 23
I 23
		if (kvm_dbopen(kd, uf) < 0 && 
		    (kd->nlfd = open(uf, O_RDONLY, 0)) < 0) {
			_kvm_syserr(kd, kd->program, "%s", uf);
			goto failed;
E 23
		}
D 23
		eproc.e_sess = pgrp.pg_session;
		eproc.e_pgid = pgrp.pg_id;
		eproc.e_jobc = pgrp.pg_jobc;
		if (kvm_read(pgrp.pg_session, &sess, sizeof (struct session))
		   != sizeof (struct session)) {
			seterr("can't read session at %x", pgrp.pg_session);
			return (-1);
E 23
I 23
	} else {
		/*
		 * This is a crash dump.
		 * Initalize the virtual address translation machinery,
		 * but first setup the namelist fd.
		 */
		if ((kd->nlfd = open(uf, O_RDONLY, 0)) < 0) {
			_kvm_syserr(kd, kd->program, "%s", uf);
			goto failed;
E 23
		}
D 23
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
E 14

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
E 23
I 23
		if (_kvm_initvtop(kd) < 0)
			goto failed;
E 23
	}
D 23
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
E 23
I 23
	return (kd);
failed:
	/*
	 * Copy out the error if doing sane error semantics.
	 */
	if (errout != 0)
		strcpy(errout, kd->errbuf);
	(void)kvm_close(kd);
	return (0);
E 23
}
D 8
	
E 8

D 23
struct proc *
kvm_nextproc()
E 23
I 23
kvm_t *
kvm_openfiles(uf, mf, sf, flag, errout)
	const char *uf;
	const char *mf;
	const char *sf;
	int flag;
	char *errout;
E 23
{
I 23
D 27
	register kvm_t *kd = (kvm_t *)malloc(sizeof(*kd));
E 27
I 27
	register kvm_t *kd;
E 27
E 23

D 23
	if (!kvmprocbase && kvm_getprocs(0, 0) == -1)
		return (NULL);
	if (kvmprocptr >= (kvmprocbase + kvmnprocs)) {
		seterr("end of proc list");
		return (NULL);
E 23
I 23
D 27
	if (kd == 0) {
		strcpy(errout, "out of memory");
E 27
I 27
	if ((kd = malloc(sizeof(*kd))) == NULL) {
		(void)strcpy(errout, strerror(errno));
E 27
		return (0);
E 23
	}
D 23
	return((struct proc *)(kvmprocptr++));
E 23
I 23
	kd->program = 0;
D 27
	return _kvm_open(kd, uf, mf, sf, flag, errout);
E 27
I 27
	return (_kvm_open(kd, uf, mf, sf, flag, errout));
E 27
E 23
}

D 23
struct eproc *
kvm_geteproc(p)
D 13
	struct proc *p;
E 13
I 13
	const struct proc *p;
E 23
I 23
kvm_t *
kvm_open(uf, mf, sf, flag, program)
	const char *uf;
	const char *mf;
	const char *sf;
	int flag;
	const char *program;
E 23
E 13
{
D 23
	return ((struct eproc *)(((char *)p) + sizeof (struct proc)));
}
E 23
I 23
D 27
	register kvm_t *kd = (kvm_t *)malloc(sizeof(*kd));
E 27
I 27
	register kvm_t *kd;
E 27
E 23

D 23
kvm_setproc()
{
D 13

E 13
	kvmprocptr = kvmprocbase;
E 23
I 23
D 27
	if (kd == 0 && program != 0) {
		fprintf(stderr, "%s: out of memory", program);
E 27
I 27
	if ((kd = malloc(sizeof(*kd))) == NULL && program != NULL) {
		(void)fprintf(stderr, "%s: %s\n", strerror(errno));
E 27
		return (0);
	}
	kd->program = program;
D 27
	return _kvm_open(kd, uf, mf, sf, flag, (char *)0);
E 27
I 27
	return (_kvm_open(kd, uf, mf, sf, flag, NULL));
E 27
E 23
}

D 23
kvm_freeprocs()
E 23
I 23
int
kvm_close(kd)
	kvm_t *kd;
E 23
{
I 23
	register int error = 0;
E 23

D 23
	if (kvmprocbase) {
		free(kvmprocbase);
		kvmprocbase = NULL;
	}
E 23
I 23
	if (kd->pmfd >= 0)
		error |= close(kd->pmfd);
	if (kd->vmfd >= 0)
		error |= close(kd->vmfd);
	if (kd->nlfd >= 0)
		error |= close(kd->nlfd);
	if (kd->swfd >= 0)
		error |= close(kd->swfd);
	if (kd->db != 0)
D 26
		dbm_close(kd->db);
E 26
I 26
		error |= (kd->db->close)(kd->db);
E 26
	if (kd->vmst)
		_kvm_freevtop(kd);
	if (kd->procbase != 0)
		free((void *)kd->procbase);
	if (kd->argv != 0)
		free((void *)kd->argv);
	free((void *)kd);

	return (0);
E 23
}

I 14
D 23
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
E 23
I 23
/*
 * Set up state necessary to do queries on the kernel namelist
 * data base.  If the data base is out-of-data/incompatible with 
 * given executable, set up things so we revert to standard nlist call.
 * Only called for live kernels.  Return 0 on success, -1 on failure.
 */
static int
kvm_dbopen(kd, uf)
	kvm_t *kd;
	const char *uf;
E 23
E 16
{
D 23
	register struct kinfo_proc *kp = (struct kinfo_proc *)p;
	register int i;
	register char *up;
E 23
I 23
	char *cp;
D 26
	datum rec;
E 26
I 26
	DBT rec;
E 26
	int dbversionlen;
	struct nlist nitem;
	char dbversion[_POSIX2_LINE_MAX];
	char kversion[_POSIX2_LINE_MAX];
	char dbname[MAXPATHLEN];
E 23
D 16
	struct pte pte[CLSIZE*2];
E 16

D 23
	if (kvminit == 0 && kvm_init(NULL, NULL, NULL, 0) == -1)
		return (NULL);
	if (p->p_stat == SZOMB) {
		seterr("zombie process");
		return (NULL);
	}
E 23
I 23
	if ((cp = rindex(uf, '/')) != 0)
		uf = cp + 1;

D 26
	sprintf(dbname, "%skvm_%s", _PATH_VARRUN, uf);
	kd->db = dbm_open(dbname, O_RDONLY, 0);
E 26
I 26
	(void)snprintf(dbname, sizeof(dbname), "%skvm_%s.db", _PATH_VARDB, uf);
	kd->db = dbopen(dbname, O_RDONLY, 0, DB_HASH, NULL);
E 26
I 24
	if (kd->db == 0)
		return (-1);
E 24
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
	 * read version out of database
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
	}
	pcbpf = (int) btop(p->p_addr);	/* what should this be really? */
E 23
I 23
D 26
	rec.dptr = VRS_KEY;
	rec.dsize = sizeof(VRS_KEY) - 1;
	rec = dbm_fetch(kd->db, rec);
	if (rec.dptr == 0 || rec.dsize > sizeof(dbversion))
E 26
I 26
	rec.data = VRS_KEY;
	rec.size = sizeof(VRS_KEY) - 1;
	if ((kd->db->get)(kd->db, (DBT *)&rec, (DBT *)&rec, 0))
E 26
		goto close;
I 26
	if (rec.data == 0 || rec.size > sizeof(dbversion))
		goto close;
E 26

D 26
	bcopy(rec.dptr, dbversion, rec.dsize);
	dbversionlen = rec.dsize;
E 26
I 26
	bcopy(rec.data, dbversion, rec.size);
	dbversionlen = rec.size;
E 26
E 23
	/*
D 23
	 * Conjure up a physical address for the arguments.
E 23
I 23
	 * Read version string from kernel memory.
	 * Since we are dealing with a live kernel, we can call kvm_read()
	 * at this point.
E 23
	 */
D 23
	argaddr0 = argaddr1 = 0;
#ifdef hp300
	if (kp->kp_eproc.e_vm.vm_pmap.pm_ptab) {
I 16
		struct pte pte[CLSIZE*2];
E 23
I 23
D 26
	rec.dptr = VRS_SYM;
	rec.dsize = sizeof(VRS_SYM) - 1;
	rec = dbm_fetch(kd->db, rec);
	if (rec.dptr == 0 || rec.dsize != sizeof(struct nlist))
E 26
I 26
	rec.data = VRS_SYM;
	rec.size = sizeof(VRS_SYM) - 1;
	if ((kd->db->get)(kd->db, (DBT *)&rec, (DBT *)&rec, 0))
E 26
		goto close;
D 26
	bcopy((char *)rec.dptr, (char *)&nitem, sizeof(nitem));
E 26
I 26
	if (rec.data == 0 || rec.size != sizeof(struct nlist))
		goto close;
	bcopy((char *)rec.data, (char *)&nitem, sizeof(nitem));
E 26
	if (kvm_read(kd, (u_long)nitem.n_value, kversion, dbversionlen) != 
	    dbversionlen)
		goto close;
	/*
	 * If they match, we win - otherwise clear out kd->db so
	 * we revert to slow nlist().
	 */
	if (bcmp(dbversion, kversion, dbversionlen) == 0)
		return (0);
close:
D 26
	dbm_close(kd->db);
E 26
I 26
	(void)(kd->db->close)(kd->db);
E 26
	kd->db = 0;
E 23

E 16
D 20
		klseek(kmem,
E 20
I 20
D 23
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
E 23
I 23
	return (-1);
E 23
}
D 23
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
E 23

D 23
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
E 23
I 23
int
kvm_nlist(kd, nl)
	kvm_t *kd;
	struct nlist *nl;
E 23
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
D 23
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
E 23
I 23
	register struct nlist *p;
	register int nvalid;
E 23
E 14

I 14
D 23
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
E 23
I 23
	/*
	 * If we can't use the data base, revert to the 
	 * slow library call.
	 */
	if (kd->db == 0)
		return (__fdnlist(kd->nlfd, nl));
E 23

D 23
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
E 23
I 23
	/*
	 * We can use the kvm data base.  Go through each nlist entry
D 26
	 * and look it up with a dbm query.
E 26
I 26
	 * and look it up with a db query.
E 26
	 */
	nvalid = 0;
	for (p = nl; p->n_name && p->n_name[0]; ++p) {
		register int len;
D 26
		datum rec;
E 26
I 26
		DBT rec;
E 26
E 23

D 23

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
E 23
I 23
		if ((len = strlen(p->n_name)) > 4096) {
			/* sanity */
			_kvm_err(kd, kd->program, "symbol too large");
E 23
			return (-1);
		}
D 23
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
E 23
I 23
D 26
		rec.dptr = p->n_name;
		rec.dsize = len;
		rec = dbm_fetch(kd->db, rec);
		if (rec.dptr == 0 || rec.dsize != sizeof(struct nlist))
E 26
I 26
		rec.data = p->n_name;
		rec.size = len;
		if ((kd->db->get)(kd->db, (DBT *)&rec, (DBT *)&rec, 0))
E 26
			continue;
I 26
		if (rec.data == 0 || rec.size != sizeof(struct nlist))
			continue;
E 26
		++nvalid;
		/*
		 * Avoid alignment issues.
		 */
D 26
		bcopy((char *)&((struct nlist *)rec.dptr)->n_type,
E 26
I 26
		bcopy((char *)&((struct nlist *)rec.data)->n_type,
E 26
		      (char *)&p->n_type, 
		      sizeof(p->n_type));
D 26
		bcopy((char *)&((struct nlist *)rec.dptr)->n_value,
E 26
I 26
		bcopy((char *)&((struct nlist *)rec.data)->n_value,
E 26
		      (char *)&p->n_value, 
		      sizeof(p->n_value));
E 23
E 8
	}
I 22
D 23
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
E 22
	return (0);
E 23
I 23
	/*
	 * Return the number of entries that weren't found.
	 */
	return ((p - nl) - nvalid);
E 23
}
I 19

D 23
static
nlisterr(nl)
	struct nlist nl[];
E 23
I 23
ssize_t
D 28
kvm_write(kd, kva, buf, len)
	kvm_t *kd;
	register u_long kva;
	register const char *buf;
	register size_t len;
E 23
{
D 23
	int i;

	fprintf(stderr, "kvm_nlist: can't find following names:");
	for (i = 0; nl[i].n_name[0] != '\0'; i++)
		if (nl[i].n_value == 0)
			fprintf(stderr, " %s", nl[i].n_name);
	fprintf(stderr, ": continuing...\n");
E 23
I 23
	_kvm_err(kd, kd->program, "kvm_write not implemented");
	return (ssize_t)(0);
E 23
}

E 19
D 23

kvm_read(loc, buf, len)
D 16
	unsigned long loc;
	char *buf;
E 16
I 16
	void *loc;
	void *buf;
E 23
I 23
ssize_t
E 28
kvm_read(kd, kva, buf, len)
	kvm_t *kd;
	register u_long kva;
D 31
	register char *buf;
E 31
I 31
	register void *buf;
E 31
	register size_t len;
E 23
E 16
{
I 2
D 23
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
E 23
I 23
	register int cc;
D 31
	register char *cp;
E 31
I 31
	register void *cp;
E 31

	if (ISALIVE(kd)) {
		/*
		 * We're using /dev/kmem.  Just read straight from the
		 * device and let the active kernel do the address translation.
		 */
		errno = 0;
		if (lseek(kd->vmfd, (off_t)kva, 0) == -1 && errno != 0) {
			_kvm_err(kd, 0, "invalid address (%x)", kva);
			return (0);
E 23
		}
I 23
		cc = read(kd->vmfd, buf, len);
		if (cc < 0) {
			_kvm_syserr(kd, 0, "kvm_read");
			return (0);
		} else if (cc < len)
			_kvm_err(kd, kd->program, "short read");
D 28
		return (ssize_t)(cc);
E 28
I 28
		return (cc);
E 28
E 23
	} else {
D 17
		lseek(mem, loc, 0);
E 17
I 17
D 23
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
E 23
I 23
		cp = buf;
		while (len > 0) {
			u_long pa;
		
			cc = _kvm_kvatop(kd, kva, &pa);
			if (cc == 0)
				return (0);
			if (cc > len)
				cc = len;
			errno = 0;
			if (lseek(kd->pmfd, (off_t)pa, 0) == -1 && errno != 0) {
				_kvm_syserr(kd, 0, _PATH_MEM);
				break;
			}
			cc = read(kd->pmfd, cp, cc);
			if (cc < 0) {
				_kvm_syserr(kd, kd->program, "kvm_read");
				break;
			}
I 36
			/*
			 * If kvm_kvatop returns a bogus value or our core
			 * file is truncated, we might wind up seeking beyond
			 * the end of the core file in which case the read will
			 * return 0 (EOF).
			 */
			if (cc == 0)
				break;
E 36
D 31
			cp += cc;
E 31
I 31
			(char *)cp += cc;
E 31
			kva += cc;
			len -= cc;
E 23
		}
I 23
D 31
		return (cp - buf);
E 31
I 31
		return ((char *)cp - (char *)buf);
E 31
I 28
	}
	/* NOTREACHED */
}

ssize_t
kvm_write(kd, kva, buf, len)
	kvm_t *kd;
	register u_long kva;
D 31
	register const char *buf;
E 31
I 31
	register const void *buf;
E 31
	register size_t len;
{
	register int cc;

	if (ISALIVE(kd)) {
		/*
		 * Just like kvm_read, only we write.
		 */
		errno = 0;
		if (lseek(kd->vmfd, (off_t)kva, 0) == -1 && errno != 0) {
			_kvm_err(kd, 0, "invalid address (%x)", kva);
			return (0);
		}
		cc = write(kd->vmfd, buf, len);
		if (cc < 0) {
			_kvm_syserr(kd, 0, "kvm_write");
			return (0);
		} else if (cc < len)
			_kvm_err(kd, kd->program, "short write");
		return (cc);
	} else {
		_kvm_err(kd, kd->program,
		    "kvm_write not implemented for dead kernels");
		return (0);
E 28
E 23
	}
D 23
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
	return (0);
E 20
E 2
}

I 14
#ifndef NEWVM
E 14
/*
 * Given a base/size pair in virtual swap area,
 * return a physical base/size pair which is the
 * (largest) initial, physically contiguous block.
 */
D 13
static
E 13
I 13
static void
E 13
vstodb(vsbase, vssize, dmp, dbp, rev)
	register int vsbase;
	int vssize;
	struct dmap *dmp;
	register struct dblock *dbp;
{
	register int blk = dmmin;
	register swblk_t *ip = dmp->dm_map;

	vsbase = ctod(vsbase);
	vssize = ctod(vssize);
	if (vsbase < 0 || vsbase + vssize > dmp->dm_size)
		/*panic("vstodb")*/;
	while (vsbase >= blk) {
		vsbase -= blk;
		if (blk < dmmax)
			blk *= 2;
		ip++;
	}
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
	/* NOTREACHED */
E 23
}
E 1
