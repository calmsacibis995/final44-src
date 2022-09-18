h41504
s 00001/00001/00721
d D 8.3 95/05/02 14:48:32 mckusick 51 50
c update for NFS V3
e
s 00004/00002/00718
d D 8.2 95/04/28 15:18:29 bostic 50 49
c kvm_open should have been kvm_openfiles
c From: Chris Torek <torek@BSDI.COM>
e
s 00005/00005/00715
d D 8.1 93/06/06 14:40:32 bostic 49 48
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00720
d D 5.46 93/06/02 19:06:35 mckusick 48 47
c devname moves to libc
e
s 00016/00010/00705
d D 5.45 93/05/25 14:26:25 mckusick 47 45
c add field telling how descriptor is opened
e
s 00013/00007/00708
d R 5.45 93/05/25 14:16:32 mckusick 46 45
c output r/w access mode on files
e
s 00003/00004/00712
d D 5.44 93/04/27 18:16:37 bostic 45 44
c kinfo_proc.h gone, stuff moved to <sys/sysctl.h>
e
s 00004/00004/00712
d D 5.43 93/03/31 17:10:57 mckusick 44 43
c convert from kinfo to sysctl
e
s 00001/00002/00715
d D 5.42 93/02/10 17:03:50 bostic 43 42
c filename before error string
e
s 00004/00003/00713
d D 5.41 92/07/24 11:25:22 bostic 42 41
c fix vnode.h include problem.
e
s 00002/00002/00714
d D 5.40 92/06/08 13:53:02 bostic 41 40
c file system reorg
e
s 00026/00071/00690
d D 5.39 92/06/08 13:28:08 bostic 40 39
c make fstat work with new kvm interface; from Donn Seeley, BSDI
e
s 00016/00008/00745
d D 5.38 92/01/27 12:21:13 bostic 39 38
c don't let users create their own symbol table for the running kernel
e
s 00001/00000/00752
d D 5.37 92/01/13 14:35:21 marc 38 37
c nfs.h requires rpcv2.h (bletch)
e
s 00036/00018/00716
d D 5.36 92/01/09 17:13:00 marc 37 36
c vnode private data is now a kernel pointer - so fetch it by hand...
e
s 00005/00004/00729
d D 5.35 92/01/09 16:32:07 marc 36 35
c was missing last file (oops)
e
s 00002/00002/00731
d D 5.34 91/11/04 22:33:13 bostic 35 34
c break FFS into UFS/FFS/LFS; doesn't need -I/sys any more
e
s 00006/00004/00727
d D 5.33 91/08/09 13:07:03 marc 34 33
c fix off by one error on fd_lastfile.  error in classifying file type.
e
s 00000/00001/00731
d D 5.32 91/06/17 16:09:42 marc 33 32
c remove text.h
e
s 00010/00010/00722
d D 5.31 91/04/23 16:41:45 marc 32 31
c add -N and -M
e
s 00033/00025/00699
d D 5.30 91/04/23 16:15:46 bostic 31 30
c ANSI/lint
e
s 00043/00034/00681
d D 5.29 91/04/23 15:16:04 bostic 30 29
c (truly) minor cleanups -- reserve -M, -N, -c and -w for later use
e
s 00049/00019/00666
d D 5.28 91/04/18 10:57:47 marc 29 28
c new vm - dynamic files
e
s 00077/00043/00608
d D 5.27 91/03/05 18:55:19 marc 28 27
c dynamic allocted filedescs - version1 (version2 ifdef'd and waiting)
e
s 00001/00001/00650
d D 5.26 90/12/18 17:45:58 bostic 27 26
c update the usage statement
e
s 00105/00112/00546
d D 5.25 90/06/29 00:31:40 marc 26 25
c symbolic modes.  reorg code.
e
s 00009/00009/00649
d D 5.24 90/04/18 14:42:18 marc 25 24
c new calling convention for devname()
e
s 00002/00001/00656
d D 5.23 90/04/12 11:12:20 marc 24 23
c oops, error addressing structure element
e
s 00325/00336/00332
d D 5.22 90/04/09 17:53:47 marc 23 22
c vnodes.  re-work code.
e
s 00000/00001/00668
d D 5.21 90/02/20 16:14:12 bostic 22 21
c don't need dir.h anymore
e
s 00001/00001/00668
d D 5.20 89/08/16 19:08:52 mckusick 21 20
c have to check vnode type before interpreting it
e
s 00056/00033/00613
d D 5.19 89/08/15 16:03:59 mckusick 20 19
c convert to work in the precense of vnodes
e
s 00005/00005/00641
d D 5.18 89/05/11 09:41:30 bostic 19 18
c file reorg, pathnames.h, paths.h
e
s 00062/00053/00584
d D 5.17 89/04/11 09:03:21 bostic 18 17
c minor lint cleanups; fix read error reportage to be consistent
c KNF everywhere
e
s 00023/00023/00614
d D 5.16 89/04/02 12:43:33 bostic 17 16
c add pathnames.h, make errors more consistent
e
s 00001/00001/00636
d D 5.15 89/03/01 11:52:10 bostic 16 15
c if -v is undocumented, don't put it in the usage statement
e
s 00015/00004/00622
d D 5.14 88/12/20 19:38:07 kfall 15 14
c display major,minor dev #s for character special files
e
s 00010/00005/00616
d D 5.13 88/06/18 14:34:28 bostic 14 13
c install approved copyright notice
e
s 00018/00018/00603
d D 5.12 88/03/13 18:40:16 bostic 13 12
c put it all in "kernel normal"
e
s 00001/00001/00620
d D 5.11 88/02/22 11:57:04 bostic 12 11
c don't increment argv twice
e
s 00048/00039/00573
d D 5.10 87/12/26 12:59:51 bostic 11 10
c Berkeley header, minor cleanups
e
s 00008/00004/00604
d D 5.9 87/11/24 14:38:25 marc 10 9
c If multiple files are specified, don't bomb as long as at least
c one of them is accessable.  I.e. fstat /foo/* shouldn't crap out just 
c because one of those files can't be opened.
e
s 00017/00006/00591
d D 5.8 87/11/24 01:24:16 marc 9 8
c Print name of file if known (if matched by a -f entry).
e
s 00005/00002/00592
d D 5.7 87/11/17 13:34:37 marc 8 7
c fix -p arg handling
e
s 00254/00309/00340
d D 5.6 87/11/06 19:55:23 bostic 7 6
c more rape and pillage; no more single character reads for 
c domain names, no more multiple str{cpy,cat}'s to put single characters 
c into buffers, lots of general cleanup
e
s 00246/00333/00403
d D 5.5 87/11/05 19:09:50 bostic 6 4
c complete and total rape
e
s 00247/00333/00403
d R 5.5 87/11/05 19:06:41 bostic 5 4
c complete and total rape
e
s 00010/00004/00726
d D 5.4 87/10/22 10:34:23 bostic 4 3
c ANSI C; sprintf now returns an int.
e
s 00053/00064/00677
d D 5.3 87/10/11 00:02:03 marc 3 2
c multiple file args, point arrows in the right direction 
c for connected unixdomain sockets (pipes).
e
s 00001/00001/00740
d D 5.2 87/09/02 15:58:57 marc 2 1
c upcase title line
e
s 00741/00000/00000
d D 5.1 87/09/02 15:25:56 bostic 1 0
c date and time created 87/09/02 15:25:56 by bostic
e
u
U
t
T
I 1
D 26
/*
 * Copyright (c) 1987 Regents of the University of California.
E 26
I 26
/*-
D 49
 * Copyright (c) 1988 The Regents of the University of California.
E 26
D 11
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
 * All rights reserved.
E 49
I 49
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 49
 *
D 26
 * Redistribution and use in source and binary forms are permitted
D 14
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 14
I 14
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
E 26
I 26
 * %sccs.include.redist.c%
E 26
E 14
E 11
 */

#ifndef lint
D 49
char copyright[] =
D 26
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 26
I 26
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
E 26
 All rights reserved.\n";
E 49
I 49
static char copyright[] =
"%Z% Copyright (c) 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 49
D 6
#endif not lint
E 6
I 6
D 11
#endif /* !lint */
E 11
I 11
#endif /* not lint */
E 11
E 6

#ifndef lint
D 23
static char sccsid[] = "%W% (Berkeley) %G%";
E 23
I 23
D 26
char sccsid[] = "%W% (Berkeley) %G%";
E 26
I 26
static char sccsid[] = "%W% (Berkeley) %G%";
E 26
E 23
D 6
#endif not lint
E 6
I 6
D 11
#endif /* !lint */
E 11
I 11
#endif /* not lint */
E 11
E 6

D 40
/*
 *  fstat 
 */
E 40
D 6
#include <stdio.h>
#include <ctype.h>
#include <nlist.h>
#include <pwd.h>
E 6
I 6
D 7
#include <machine/pte.h> 
E 7
I 7
D 29
#include <machine/pte.h>
E 7

E 29
E 6
#include <sys/param.h>
D 7
#include <sys/ioctl.h>
#include <sys/tty.h>
E 7
D 22
#include <sys/dir.h>
E 22
D 28
#include <sys/user.h>
E 28
I 28
#include <sys/time.h>
E 28
#include <sys/proc.h>
I 29
#include <sys/user.h>
D 40
#ifdef SPPWAIT
#define NEWVM
#endif
#ifndef NEWVM
#include <machine/pte.h>
#include <sys/vmmac.h>
I 36
#include <sys/text.h>
E 36
#endif
E 40
E 29
D 6
#include <machine/pte.h> 
E 6
D 7
#include <sys/vm.h>
E 7
D 33
#include <sys/text.h>
E 33
#include <sys/stat.h>
D 6
#include <math.h>
E 6
D 7
#include <sys/vlimit.h>
E 7
D 20
#include <sys/inode.h>
E 20
I 20
D 28
#include <sys/time.h>
E 28
#include <sys/vnode.h>
E 20
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/domain.h>
#include <sys/protosw.h>
D 6
#include <net/route.h>
#include <netinet/in.h>
#include <netinet/in_pcb.h>
E 6
#include <sys/unpcb.h>
D 7
#define KERNEL
E 7
I 7
D 29
#include <sys/vmmac.h>
E 29
I 28
D 44
#include <sys/kinfo.h>
E 44
I 44
#include <sys/sysctl.h>
E 44
I 40
D 45
#include <sys/kinfo_proc.h>
E 45
E 40
D 29
#include <sys/namei.h>
E 29
#include <sys/filedesc.h>
E 28
#define	KERNEL
I 23
D 42
#define NFS
E 42
E 23
E 7
#include <sys/file.h>
D 7
#undef KERNEL
E 7
I 7
D 23
#undef	KERNEL
E 23
I 23
D 42
#include <sys/mount.h>
E 42
I 26
D 35
#include <ufs/quota.h>
E 26
E 23
I 20
#include <ufs/inode.h>
E 35
I 35
D 40
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
E 40
I 40
D 41
#include <ufs/quota.h>
#include <ufs/inode.h>
E 41
I 41
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
I 42
#undef KERNEL
#define NFS
#include <sys/mount.h>
E 42
E 41
E 40
E 35
I 23
D 51
#include <nfs/nfsv2.h>
E 51
I 51
#include <nfs/nfsproto.h>
E 51
I 38
#include <nfs/rpcv2.h>
E 38
#include <nfs/nfs.h>
#include <nfs/nfsnode.h>
D 42
#undef KERNEL
E 42
I 42
#undef NFS
E 42

E 23
E 20
E 7
I 6
#include <net/route.h>
#include <netinet/in.h>
I 23
#include <netinet/in_systm.h>
#include <netinet/ip.h>
E 23
#include <netinet/in_pcb.h>
D 23
#include <stdio.h>
E 23
I 23

I 45
#include <ctype.h>
E 45
I 30
#include <errno.h>
E 30
D 31
#include <kvm.h>
E 31
D 30
#include <paths.h>
E 23
I 8
#include <ctype.h>
E 30
E 8
D 7
#include <math.h>
E 7
D 45
#include <nlist.h>
E 45
I 31
#include <kvm.h>
I 50
#include <limits.h>
E 50
I 45
#include <nlist.h>
#include <paths.h>
E 45
E 31
#include <pwd.h>
I 18
D 26
#include <strings.h>
E 26
I 26
D 30
#include <string.h>
E 30
E 26
E 18
I 17
D 19
#include "pathnames.h"
E 19
I 19
D 23
#include <paths.h>
E 23
I 23
#include <stdio.h>
I 30
D 45
#include <paths.h>
#include <ctype.h>
E 45
I 31
#include <stdlib.h>
E 31
#include <string.h>
E 30
E 23
E 19
E 17
E 6

I 29
D 30

E 30
E 29
D 6
#ifdef ULTRIX	
   		/* UFS -> GFS */
E 6
I 6
D 20
#ifdef	ULTRIX
		/* UFS -> GFS */
E 6
#    define	inode	gnode
#    define	x_iptr	x_gptr
#    define	i_dev	g_dev
#    define	i_number g_number
#    define	i_mode	g_mode
#    define	i_size	g_size
D 6
#endif ULTRIX
E 6
I 6
D 7
#endif	/* ULTRIX */
E 7
I 7
#endif
E 7
E 6

E 20
I 7
D 17
#define	N_KMEM	"/dev/kmem"
#define	N_MEM	"/dev/mem"
#define	N_SWAP	"/dev/drum"
#define	N_UNIX	"/vmunix"

E 17
E 7
D 6
char *emalloc();
char *getinetproto();
E 6
I 6
D 23
#define	TEXT	-2
#define	WD	-1
E 23
I 23
#define	TEXT	-1
#define	CDIR	-2
#define	RDIR	-3
#define	TRACE	-4
E 23
I 7

I 18
D 23
#define	VP	if (vflg) (void)printf

E 23
E 18
E 7
D 11
#define	vprintf	if (vflg) printf
E 6

E 11
D 6
#define vprintf	if (vflg) printf
#define WD	-1
#define TEXT	-2

int	pcbpf, nswap, kmem, mem, swap, uid, pid;
D 3
int	uflg, fflg, inum, Mdev, mdev, special, vflg, nproc, pflg;
E 3
I 3
int	uflg, fflg, vflg, nproc, pflg;
E 3
int sflg, kflg; /*4.2*/
int argaddr; /*4.2*/

E 6
I 3
D 7
struct devs {
E 7
I 7
typedef struct devs {
E 7
D 6
	struct devs *next;
	dev_t dev;
	int inum;
E 6
I 6
D 13
	struct devs	*next;
	dev_t	dev;
	int	inum;
I 9
	char	*name;
E 13
I 13
D 23
	struct devs *next;
	dev_t dev;
	int inum;
	char *name;
E 23
I 23
	struct	devs *next;
D 26
	dev_t	dev;
E 26
I 26
	long	fsid;
E 26
	ino_t	ino;
	char	*name;
E 23
E 13
E 9
E 6
D 7
} devs;
E 7
I 7
} DEVS;
D 13
DEVS	*devs;
E 13
I 13
DEVS *devs;
E 13
E 7

E 3
D 6
#define clear(x) 	((int)x & 0x7fffffff)

struct pte *Sysmap = 0;

E 6
D 7
struct nlist nl[] = {
E 7
I 7
D 23
static struct nlist nl[] = {
E 7
	{ "_proc" },
#define	X_PROC		0
	{ "_Usrptmap" },
#define	X_USRPTMA	1
D 7
	{ "_usrpt" },
#define	X_USRPT		2
	{ "_nswap" },
#define	X_NSWAP		3
E 7
	{ "_nproc" },
D 7
#define	X_NPROC		4
E 7
I 7
#define	X_NPROC		2
	{ "_usrpt" },
#define	X_USRPT		3
I 20
	{ "_ufs_vnodeops" },
#define	X_UFSOPS	4
	{ "_blk_vnodeops" },
#define	X_BLKOPS	5
E 23
I 23
struct  filestat {
	long	fsid;
	long	fileid;
I 26
	mode_t	mode;
E 26
	u_long	size;
	dev_t	rdev;
};

I 26
#ifdef notdef
E 26
struct nlist nl[] = {
E 23
E 20
E 7
D 6
	{ "_Sysmap" },
#define SSYSMAP		5
	{ "_Syssize" },
#define SSYSSIZE	6
E 6
	{ "" },
};
I 26
#endif
E 26

D 6
char 	*stypename[] = {
	"unused",	/* 0 */
	"stream", 	/* 1 */
	"dgram",	/* 2 */
	"raw",		/* 3 */
	"rdm",		/* 4 */
	"seqpak"	/* 5 */
};
#define STYPEMAX 5

char	*uname;


E 6
D 7
struct	proc proc[8], *mproc;		/* 8 = a few, for less syscalls */
struct	pte *Usrptma, *usrpt;
E 7
I 7
D 13
struct proc	*mproc;
struct pte	*Usrptma, *usrpt;
E 13
I 13
D 23
struct proc *mproc;
struct pte *Usrptma, *usrpt;
E 23
I 23
int 	fsflg,	/* show files on same filesystem as file(s) argument */
	pflg,	/* show files open by a particular pid */
	uflg;	/* show files open by a particular (effective) user */
int 	checkfile; /* true if restricting to particular files or filesystems */
int	nflg;	/* (numerical) display f.s. and rdev as dev_t */
int	vflg;	/* display errors in locating kernel data objects etc... */
E 23
E 13

E 7
D 6

int	paduser1;		/* avoid hardware mem clobbering botch */
E 6
D 23
union {
D 13
	struct	user user;
	char	upages[UPAGES][NBPG];
E 13
I 13
	struct user user;
	char upages[UPAGES][NBPG];
E 13
} user;
E 23
I 23
#define dprintf	if (vflg) fprintf
E 23
D 6
int	paduser2;		/* avoid hardware mem clobbering botch */
#define u	user.user
E 6

I 28
struct file **ofiles;	/* buffer of pointers to file structures */
int maxfiles;
#define ALLOC_OFILES(d)	\
	if ((d) > maxfiles) { \
		free(ofiles); \
D 30
		ofiles = (struct file **)malloc((d) * sizeof(struct file *)); \
E 30
I 30
		ofiles = malloc((d) * sizeof(struct file *)); \
E 30
		if (ofiles == NULL) { \
D 30
			fprintf(stderr, "fstat: out of memory\n"); \
E 30
I 30
			fprintf(stderr, "fstat: %s\n", strerror(errno)); \
E 30
			exit(1); \
		} \
		maxfiles = (d); \
	}

/*
 * a kvm_read that returns true if everything is read 
 */
D 40
#define KVM_READ(kaddr, paddr, len) (kvm_read((kaddr), (paddr), (len)) == (len))
E 40
I 40
#define KVM_READ(kaddr, paddr, len) \
	(kvm_read(kd, (u_long)(kaddr), (char *)(paddr), (len)) == (len))
E 40

I 40
kvm_t *kd;

E 40
I 31
D 37
void dofiles(), getinetproto(), socktrans(), nfs_filestat(), ufs_filestat();
E 37
I 37
int ufs_filestat(), nfs_filestat();
void dofiles(), getinetproto(), socktrans();
E 37
void usage(), vtrans();

E 31
E 28
D 6
char	*kmemf, *memf, *swapf, *nlistf;
E 6
I 6
D 7
static int	nproc, nswap, kmem, mem, swap, uid, pid;
static int	uflg, fflg, vflg, pflg;
static char	*kmemf = "kmem",
		*memf = "mem",
		*swapf = "drum",
		*nlistf = "/vmunix",
		*uname;
E 6

E 7
D 13
extern int	errno;
I 7
D 11
static off_t	procp;
D 10
static int	fflg, vflg;
E 10
I 10
static int	fflg, hadfflg, vflg;
E 11
I 11
static int	fflg, vflg;
E 11
E 10
static int	kmem, mem, nproc, swap;
static char	*uname;
E 13
I 13
D 30
extern int errno;
D 23
static int fflg, vflg;
static int kmem, mem, nproc, swap;
static char *uname;
E 13
E 7
D 6
char	stdoutBuf[BUFSIZ];
E 6

E 23
I 6
D 13
off_t	lseek();
E 13
I 13
off_t lseek();
E 13
D 7
long	lgetw();
char	*emalloc(), *getinetproto();
E 7

I 28

E 30
E 28
E 6
main(argc, argv)
D 6
char **argv;
E 6
I 6
D 13
	int	argc;
	char	**argv;
E 13
I 13
	int argc;
	char **argv;
E 13
E 6
{
I 23
D 30
	register struct passwd *passwd;
	int what = KINFO_PROC_ALL, arg = 0;
D 29
	struct passwd *getpwnam(), *getpwuid();
E 29
	struct proc *p;
E 30
E 23
I 6
D 7
	extern char	*optarg;
	extern int	optind;
E 6
	register int i, j;
	off_t procp;
D 6
	dev_t	dev;
E 6
I 6
	int	ch;
E 7
I 7
	extern char *optarg;
	extern int optind;
D 23
	register struct passwd *passwd;
	register int pflg, pid, uflg, uid;
E 23
D 26
	int ch, size;
E 26
I 26
D 30
	int ch;
E 26
D 23
	struct passwd *getpwnam(), *getpwuid();
	long lgetw();
E 23
	char *malloc();
E 30
I 30
	register struct passwd *passwd;
D 40
	struct proc *p;
E 40
I 40
	struct kinfo_proc *p, *plast;
E 40
	int arg, ch, what;
I 32
D 39
	char *namelist = NULL, *memfile = NULL;
E 39
I 39
	char *memf, *nlistf;
I 50
	char buf[_POSIX2_LINE_MAX];
E 50
I 40
	int cnt;
E 40
E 39
E 32
E 30
E 7
E 6

D 6
	argv++;
D 3
	while (--argc > 0) {
E 3
I 3
	while (*argv) {
E 3
		if (strcmp(*argv, "-v") == 0) {
			vflg++;
			argv++;
			continue;
		} 
		if (strcmp(*argv, "-u") == 0) {
			if (uflg++)
E 6
I 6
D 7
	if (chdir("/dev") < 0) {
		perror("/dev");
		exit(1);
	}

E 7
I 7
D 23
	pflg = uflg = 0;
E 7
	while ((ch = getopt(argc, argv, "p:u:v")) != EOF)
E 23
I 23
D 30

	while ((ch = getopt(argc, argv, "p:u:fnv")) != EOF)
E 30
I 30
	arg = 0;
D 44
	what = KINFO_PROC_ALL;
E 44
I 44
	what = KERN_PROC_ALL;
E 44
I 39
	nlistf = memf = NULL;
E 39
D 32
	while ((ch = getopt(argc, argv, "fnp:u:v")) != EOF)
E 32
I 32
	while ((ch = getopt(argc, argv, "fnp:u:vNM")) != EOF)
E 32
E 30
E 23
		switch((char)ch) {
I 30
D 31
		case 'c':
			/* NOTYET: set count to optarg. */
			usage();
E 31
		case 'f':
			fsflg = 1;
			break;
I 39
		case 'M':
			memf = optarg;
			break;
		case 'N':
			nlistf = optarg;
			break;
E 39
D 32
		case 'M':
			/* NOTYET: set kernel to optarg. */
			usage();
		case 'N':
			/* NOTYET: set memory to optarg. */
			usage();
E 32
		case 'n':
			nflg = 1;
			break;
E 30
		case 'p':
D 7
			if (pflg++ || ((pid = atoi(optarg)) <= 0)) {
E 7
I 7
D 8
			if (pflg++) {
E 8
I 8
			if (pflg++)
E 8
E 7
E 6
				usage();
D 6
			if ((uid = getuname(*(++argv))) < 0) {
				fprintf(stderr, "%s: unknown user\n", *argv);
E 6
D 8
				exit(1);
E 8
I 8
			if (!isdigit(*optarg)) {
D 30
				fputs("fstat: -p option requires a process id.\n", stderr);
E 30
I 30
				fprintf(stderr,
				    "fstat: -p requires a process id\n");
E 30
				usage();
E 8
			}
I 7
D 23
			pid = atoi(optarg);
E 23
I 23
D 44
			what = KINFO_PROC_PID;
E 44
I 44
			what = KERN_PROC_PID;
E 44
			arg = atoi(optarg);
E 23
E 7
D 3
			--argc;
E 3
D 6
			argv++;
			continue;
		} 
		if (strcmp(*argv, "-f") == 0) {
D 3
			if (fflg++)
				usage();
			if ((dev = getfname(*(++argv))) < 0) {
E 3
I 3
			fflg++;
			if (getfname(*(++argv)) < 0) {
E 3
				perror(*argv);
				exit(1);
			}
D 3
			--argc;
E 3
			argv++;
			continue;
		}

		if (strcmp(*argv, "-p") == 0) {
			if (pflg++ || ((pid = Atoi(*(++argv))) <= 0)) {
E 6
I 6
			break;
		case 'u':
			if (uflg++)
E 6
				usage();
D 6
				perror(*argv);
E 6
I 6
D 7
			if ((uid = getuname(optarg)) < 0) {
				fprintf(stderr, "%s: unknown user\n", optarg);
E 7
I 7
			if (!(passwd = getpwnam(optarg))) {
D 18
				fprintf(stderr, "%s: unknown uid\n", optarg);
E 18
I 18
D 26
				(void)fprintf(stderr, "%s: unknown uid\n",
E 26
I 26
				fprintf(stderr, "%s: unknown uid\n",
E 26
				    optarg);
E 18
E 7
E 6
				exit(1);
			}
I 7
D 23
			uid = passwd->pw_uid;
			uname = passwd->pw_name;
E 23
I 23
D 44
			what = KINFO_PROC_UID;
E 44
I 44
			what = KERN_PROC_UID;
E 44
			arg = passwd->pw_uid;
E 23
E 7
D 3
			--argc;
E 3
D 6
			argv++;
			continue;
E 6
I 6
			break;
D 11
		case 'v':
E 11
I 11
D 23
		case 'v':	/* undocumented: print read error messages */
E 23
I 23
D 30
		case 'f':
			fsflg++;
			break;
		case 'n':
			nflg++;
			break;
E 30
		case 'v':
E 23
E 11
D 30
			vflg++;
E 30
I 30
			vflg = 1;
E 30
			break;
I 32
D 39
		case 'N':
			namelist = optarg;
			break;
		case 'M':
			memfile = optarg;
			break;
E 39
E 32
I 30
D 31
		case 'w':
			/* NOTYET: set wait interval to optarg. */
			usage();
E 31
E 30
		case '?':
		default:
			usage();
E 6
		}
D 3

		/* admit missing -u, -f, -p */
		/* it's an expert system! */
		if ((pid = Atoi(*argv)) > 0) {
			if (pflg++)
				usage();
			continue;
E 3
I 3
D 6
		/* otherwise its a file argument */
		fflg++;
		if (getfname(*argv) < 0) {
			perror(*argv);
			exit(1);
E 3
		}
D 3
		if (fflg && uflg)
			usage();
		if (uflg) {
			/* it must be a file */
			fflg++;
			if ((dev = getfname(*argv)) < 0) {
				perror(*argv);
				exit(1);
			}
			argv++;
			continue;
		}
		if (fflg) {
			/* it must be a user */
			uflg++;
			if ((uid = getuname(*argv)) < 0) {
				fprintf(stderr,
					"%s: unknown user\n", *argv);
				exit(1);
			}
			argv++;
			continue;
		}
		/* !uflg && !fflg -- which is it? */
		if ((dev = getfname(*argv)) >= 0)
			fflg++;		/* could be a file */
		if ((uid = getuname(*argv)) >= 0)
			uflg++;		/* could be a user */
		if ((!uflg ^ !fflg) == 0)
			usage();	/* could be either/neither */
E 3
		argv++;
		continue;
	}
E 6

D 3
	if (fflg) {
		Mdev = major(dev);
		mdev = minor(dev);
	}

E 3
D 6
	if (chdir("/dev") < 0) {
		perror("/dev");
		exit(1);
E 6
I 6
D 11
	for (argv += optind; *argv; ++argv) {
D 10
		fflg = 1;
		getfname(*argv);
E 10
I 10
		hadfflg = 1;
		if (getfname(*argv))
			fflg = 1;
E 11
I 11
	if (*(argv += optind)) {
D 12
		for (argv += optind; *argv; ++argv) {
E 12
I 12
		for (; *argv; ++argv) {
E 12
			if (getfname(*argv))
D 23
				fflg = 1;
E 23
I 23
				checkfile = 1;
E 23
		}
D 23
		if (!fflg)	/* file(s) specified, but none accessable */
E 23
I 23
		if (!checkfile)	/* file(s) specified, but none accessable */
E 23
			exit(1);
E 11
E 10
E 6
	}
I 28

D 30
	ALLOC_OFILES(256);	/* reverse space for file pointers */
E 30
I 30
	ALLOC_OFILES(256);	/* reserve space for file pointers */
E 30

E 28
I 23
	if (fsflg && !checkfile) {	
		/* -f with no files means use wd */
		if (getfname(".") == 0)
			exit(1);
		checkfile = 1;
	}
E 23
I 10
D 11
	if (hadfflg && !fflg)	/* file(s) specified, but none accessable */
		exit(1);
E 11
E 10

I 24
D 32
	/* modify the following to make work on dead kernels */
E 24
D 2
	printf("user\t cmd\t      pid    fd\tdevice\tinode\t  size\ttype\n");
E 2
I 2
D 9
	printf("USER\t CMD\t      PID    FD\tDEVICE\tINODE\t  SIZE\tTYPE\n");
E 9
I 9
D 11
	printf("USER\t CMD\t      PID    FD\tDEVICE\tINODE\t  SIZE TYPE");
	if (fflg)
		printf(" NAME\n");
	else
		printf("\n");

E 11
E 9
E 2
D 23
	openfiles();
D 7
	getkvars();
E 7
I 7

D 17
	if (nlist(N_UNIX, nl) == -1 || !nl[0].n_type) {
		fprintf(stderr, "%s: No namelist\n", N_UNIX);
E 17
I 17
	if (nlist(_PATH_UNIX, nl) == -1 || !nl[0].n_type) {
D 18
		fprintf(stderr, "%s: No namelist\n", _PATH_UNIX);
E 18
I 18
		(void)fprintf(stderr, "%s: no namelist\n", _PATH_UNIX);
E 23
I 23
	if (kvm_openfiles(NULL, NULL, NULL) == -1) {
E 32
I 32
D 39
	if (kvm_openfiles(namelist, memfile, NULL) == -1) {
E 39
I 39
	/*
	 * Discard setgid privileges if not the running kernel so that bad
	 * guys can't print interesting stuff from kernel memory.
	 */
	if (nlistf != NULL || memf != NULL)
		setgid(getgid());

D 40
	if (kvm_openfiles(nlistf, memf, NULL) == -1) {
E 39
E 32
		fprintf(stderr, "fstat: %s\n", kvm_geterr());
E 40
I 40
D 50
	if ((kd = kvm_open(nlistf, memf, NULL, O_RDONLY, NULL)) == NULL) {
		fprintf(stderr, "fstat: %s\n", kvm_geterr(kd));
E 50
I 50
	if ((kd = kvm_openfiles(nlistf, memf, NULL, O_RDONLY, buf)) == NULL) {
		fprintf(stderr, "fstat: %s\n", buf);
E 50
E 40
E 23
E 18
E 17
		exit(1);
	}
I 26
#ifdef notdef
E 26
D 23
	Usrptma = (struct pte *)nl[X_USRPTMA].n_value;
	usrpt = (struct pte *) nl[X_USRPT].n_value;
E 7
D 6
	procp = getw((off_t) nl[X_PROC].n_value);
	nproc = getw((off_t) nl[X_NPROC].n_value);
	for (i=0; i<nproc; i += 8) {
		lseek(kmem, (long) procp, 0);
		j = nproc - i;
		if (j > 8)
			j = 8;
		j *= sizeof (struct proc);
		if (read(kmem, (char *) proc, j) != j)
E 6
I 6
D 11
	procp = lgetw((off_t)nl[X_PROC].n_value);
E 11
	nproc = (int)lgetw((off_t)nl[X_NPROC].n_value);
D 7
	for (i = 0; i < nproc; i += 8) {
		(void)lseek(kmem, (off_t)procp, 0);
		j = MIN(nproc - i, 8);
		j *= sizeof(struct proc);
		if (read(kmem, (char *)proc, j) != j)
E 6
			cantread("proc table", kmemf);
		procp += j;
D 6
		for (j = j / sizeof (struct proc) - 1; j >= 0; j--) {
E 6
I 6
		for (j = j / sizeof(struct proc) - 1; j >= 0; j--) {
E 6
			mproc = &proc[j];
			if (mproc->p_stat == 0)
				continue;
			doproc();
		}
	}
	exit(0);
}
E 7

I 11
	(void)lseek(kmem, lgetw((off_t)nl[X_PROC].n_value), L_SET);
E 11
D 6
long
getw(loc)
E 6
I 6
D 7
static long
lgetw(loc)
E 6
	off_t loc;
{
	long word;

D 6
	lseek(kmem, (long) loc, 0);
	if (read(kmem, (char *) &word, sizeof (word)) != sizeof (word))
		vprintf("error reading kmem at %x\n", loc);
	return (word);
E 6
I 6
	(void)lseek(kmem, (off_t)loc, L_SET);
	if (read(kmem, (char *) &word, sizeof(word)) != sizeof(word))
		vprintf("error reading kmem at %lx\n", loc);
	return(word);
E 6
}

I 6
static
E 6
openfiles()
{
D 6

	kmemf = "kmem";
	kmem = open(kmemf, 0);
E 6
I 6
	kmem = open(kmemf, O_RDONLY, 0);
E 6
	if (kmem < 0) {
		perror(kmemf);
E 7
I 7
	size = nproc * sizeof(struct proc);
	if ((mproc = (struct proc *)malloc((u_int)size)) == NULL) {
D 18
		fprintf(stderr, "fstat: out of space.\n");
E 18
I 18
		(void)fprintf(stderr, "fstat: out of space.\n");
E 23
I 23
D 40
	if (kvm_nlist(nl) != 0) {
D 26
		(void)fprintf(stderr, "%s: no namelist: %s\n", kvm_geterr());
E 26
I 26
		fprintf(stderr, "fstat: no namelist: %s\n", kvm_geterr());
E 40
I 40
	if (kvm_nlist(kd, nl) != 0) {
		fprintf(stderr, "fstat: no namelist: %s\n", kvm_geterr(kd));
E 40
E 26
E 23
E 18
E 7
		exit(1);
	}
I 26
#endif
E 26
D 6
	memf = "mem";
	mem = open(memf, 0);
E 6
I 6
D 7
	mem = open(memf, O_RDONLY, 0);
E 6
	if (mem < 0) {
		perror(memf);
		exit(1);
	}
D 6
	swapf = "drum";
	swap = open(swapf, 0);
E 6
I 6
	swap = open(swapf, O_RDONLY, 0);
E 6
	if (swap < 0) {
		perror(swapf);
		exit(1);
	}
}
E 7
D 11

I 6
D 7
static
E 6
getkvars()
{
D 6
	nlistf = "/vmunix";
	nlist(nlistf, nl);
	if (nl[0].n_type == 0) {
E 6
I 6
	if (nlist(nlistf, nl) == -1 || !nl[0].n_type) {
E 6
		fprintf(stderr, "%s: No namelist\n", nlistf);
		exit(1);
E 7
I 7
	(void)lseek(kmem, (off_t)procp, L_SET);
E 11
D 23
	if (read(kmem, (char *)mproc, size) != size)
D 11
		cantread("proc table", N_KMEM);
E 11
I 11
D 17
		rerr1("proc table", N_KMEM);
E 17
I 17
		rerr1("proc table", _PATH_KMEM);
E 23
I 23
D 40
	if (kvm_getprocs(what, arg) == -1) {
		fprintf(stderr, "fstat: %s\n", kvm_geterr());
E 40
I 40
	if ((p = kvm_getprocs(kd, what, arg, &cnt)) == NULL) {
		fprintf(stderr, "fstat: %s\n", kvm_geterr(kd));
E 40
		exit(1);
	}
	if (nflg)
D 26
fputs("USER     CMD        PID   FD FST  DEV    INUM TYPE SZ|DV", stdout);
E 26
I 26
D 29
fputs("USER     CMD        PID   FD  DEV    INUM       MODE SZ|DV", stdout);
E 29
I 29
D 30
fputs("USER     CMD          PID   FD  DEV    INUM       MODE SZ|DV", stdout);
E 30
I 30
		printf("%s",
D 47
"USER     CMD          PID   FD  DEV    INUM       MODE SZ|DV");
E 47
I 47
"USER     CMD          PID   FD  DEV    INUM       MODE SZ|DV R/W");
E 47
E 30
E 29
E 26
	else
D 26
fputs("USER     CMD        PID   FD FST MNT        INUM TYPE SZ|DV", stdout);
E 26
I 26
D 29
fputs("USER     CMD        PID   FD MOUNT      INUM MODE         SZ|DV", stdout);
E 29
I 29
D 30
fputs("USER     CMD          PID   FD MOUNT      INUM MODE         SZ|DV",
	    stdout);
E 30
I 30
		printf("%s",
D 47
"USER     CMD          PID   FD MOUNT      INUM MODE         SZ|DV");
E 47
I 47
"USER     CMD          PID   FD MOUNT      INUM MODE         SZ|DV R/W");
E 47
E 30
E 29
E 26
	if (checkfile && fsflg == 0)
D 30
		fputs(" NAME\n", stdout);	
E 30
I 30
		printf(" NAME\n");
E 30
	else
		putchar('\n');
E 23
E 17

D 18
	printf("USER\t CMD\t      PID    FD\tDEVICE\tINODE\t  SIZE TYPE%s\n",
E 18
I 18
D 23
	(void)printf("USER\t CMD\t      PID    FD\tDEVICE\tINODE\t  SIZE TYPE%s\n",
E 18
	    fflg ? " NAME" : "");
E 11
	for (; nproc--; ++mproc) {
		if (mproc->p_stat == 0)
E 23
I 23
D 40
	while ((p = kvm_nextproc()) != NULL) {
		if (p->p_stat == SZOMB)
E 40
I 40
	for (plast = &p[cnt]; p < plast; ++p) {
		if (p->kp_proc.p_stat == SZOMB)
E 40
E 23
			continue;
D 23
		if (pflg && mproc->p_pid != pid)
			continue;
		if (uflg)  {
			if (mproc->p_uid != uid)
				continue;
		}
		else
			uname = (passwd = getpwuid(mproc->p_uid)) ?
			    passwd->pw_name : "unknown";
		if (mproc->p_stat != SZOMB && getu() == 0)
			continue;
		dotext();
		readf();
E 23
I 23
		dofiles(p);
E 23
E 7
	}
D 6
	Usrptma = (struct pte *) nl[X_USRPTMA].n_value;
	usrpt = (struct pte *) nl[X_USRPT].n_value;
	lseek(kmem, (long) nl[X_NSWAP].n_value, 0);
	if (read(kmem, (char *) &nswap, sizeof (nswap)) != sizeof (nswap)) {
E 6
I 6
D 7
	Usrptma = (struct pte *)nl[X_USRPTMA].n_value;
	usrpt = (struct pte *)nl[X_USRPT].n_value;
	(void)lseek(kmem, (off_t)nl[X_NSWAP].n_value, L_SET);
	if (read(kmem, (char *)&nswap, sizeof(nswap)) != sizeof(nswap)) {
E 6
		cantread("nswap", kmemf);
		exit(1);
	}
E 7
I 7
	exit(0);
E 7
}

I 6
D 23
static
E 6
D 7
cantread(what, fromwhat)
	char *what, *fromwhat;
{
D 6

E 6
	vprintf("fstat: error reading %s from %s", what, fromwhat);
}

I 6
static
E 6
doproc()
{
	struct passwd	*getpwuid();


	if (uflg && mproc->p_uid != uid)
		return;
	if (pflg && mproc->p_pid != pid)
		return;
	if (mproc->p_stat != SZOMB && getu() == 0)
		return;
	uname = getpwuid(mproc->p_uid)->pw_name;
	dotext();
	getf();
}

I 6
static
E 7
E 6
getu()
E 23
I 23
char	*Uname, *Comm;
int	Pid;

D 28
#define PREFIX(i) printf("%-8.8s %-8.8s %5d", Uname, Comm, Pid); \
E 28
I 28
D 29
#define PREFIX(i) printf("%-8.8s %-8s %5d", Uname, Comm, Pid); \
E 29
I 29
#define PREFIX(i) printf("%-8.8s %-10s %5d", Uname, Comm, Pid); \
E 29
E 28
	switch(i) { \
	case TEXT: \
D 30
		fputs(" text", stdout); \
E 30
I 30
		printf(" text"); \
E 30
		break; \
	case CDIR: \
D 30
		fputs("   wd", stdout); \
E 30
I 30
		printf("   wd"); \
E 30
		break; \
	case RDIR: \
D 30
		fputs(" root", stdout); \
E 30
I 30
		printf(" root"); \
E 30
		break; \
	case TRACE: \
D 30
		fputs("   tr", stdout); \
E 30
I 30
		printf("   tr"); \
E 30
		break; \
	default: \
		printf(" %4d", i); \
		break; \
	}

/*
 * print open files attributed to this process
 */
I 31
void
E 31
D 40
dofiles(p)
	struct proc *p;
E 40
I 40
dofiles(kp)
	struct kinfo_proc *kp;
E 40
E 23
{
D 23
	struct pte *pteaddr, apte;
	struct pte arguutl[UPAGES+CLSIZE];
	register int i;
D 7
	int ncl, size;
E 7
I 7
	int ncl;
E 23
I 23
D 28
	int i;
E 28
I 28
	int i, last;
E 28
D 26
	char *user_from_uid();
E 26
	struct file file;
I 29
D 40
#ifdef NEWVM
E 40
	struct filedesc0 filed0;
#define	filed	filed0.fd_fd
D 40
	struct eproc *ep;
#else
E 29
D 28
	struct user *up = kvm_getu(p);
	struct vnode *xvptr;
E 28
I 28
	struct filedesc filed;
I 29
#endif
E 40
I 40
	struct proc *p = &kp->kp_proc;
	struct eproc *ep = &kp->kp_eproc;
E 40
E 29

E 28
I 26
	extern char *user_from_uid();
I 28
D 29
#ifdef notdef
E 29
I 29
D 40
#ifndef NEWVM
E 29
	struct vnode *xvptr;
#endif
E 40
E 28
E 26
E 23
E 7

I 29
D 40
#ifdef NEWVM
	ep = kvm_geteproc(p);
E 40
	Uname = user_from_uid(ep->e_ucred.cr_uid, 0);
D 40
#else
E 29
D 6
	size = sizeof (struct user);
E 6
I 6
D 7
	size = sizeof(struct user);
E 7
E 6
D 23
	if ((mproc->p_flag & SLOAD) == 0) {
		if (swap < 0)
D 7
			return (0);
E 7
I 7
			return(0);
E 7
D 6
		(void) lseek(swap, (long)dtob(mproc->p_swaddr), 0);
E 6
I 6
		(void)lseek(swap, (off_t)dtob(mproc->p_swaddr), L_SET);
E 6
D 7
		if (read(swap, (char *)&user.user, size) != size) {
D 6
			fprintf(stderr, "ps: cant read u for pid %d from %s\n",
E 6
I 6
			fprintf(stderr, "fstat: cant read u for pid %d from %s\n",
E 6
			    mproc->p_pid, swapf);
E 7
I 7
		if (read(swap, (char *)&user.user, sizeof(struct user))
		    != sizeof(struct user)) {
D 17
			fprintf(stderr, "fstat: can't read u for pid %d from %s\n", mproc->p_pid, N_SWAP);
E 17
I 17
D 18
			fprintf(stderr, "fstat: can't read u for pid %d from %s\n", mproc->p_pid, _PATH_SWAP);
E 18
I 18
			VP("fstat: can't read u for pid %d from %s\n",
D 19
			    mproc->p_pid, _PATH_SWAP);
E 19
I 19
			    mproc->p_pid, _PATH_DRUM);
E 19
E 18
E 17
E 7
D 6
			return (0);
E 6
I 6
			return(0);
E 6
		}
D 6
		pcbpf = 0;
		argaddr = 0;
		return (1);
E 6
I 6
		return(1);
E 23
I 23
	Uname = user_from_uid(p->p_uid, 0);
I 29
#endif
E 40
E 29
	Pid = p->p_pid;
	Comm = p->p_comm;

D 28
	if (up == NULL) {
		dprintf(stderr, "can't read u for pid %d\n", Pid);
E 28
I 28
	if (p->p_fd == NULL)
E 28
		return;
I 28
D 29
	if (!KVM_READ(p->p_fd, &filed, sizeof (struct filedesc))) {
E 29
I 29
D 40
#ifdef NEWVM
E 40
	if (!KVM_READ(p->p_fd, &filed0, sizeof (filed0))) {
E 29
		dprintf(stderr, "can't read filedesc at %x for pid %d\n",
			p->p_fd, Pid);
		return;
E 28
E 23
E 6
	}
I 29
D 40
#else
	if (!KVM_READ(p->p_fd, &filed, sizeof (filed))) {
		dprintf(stderr, "can't read filedesc at %x for pid %d\n",
			p->p_fd, Pid);
		return;
	}
#endif
E 40
E 29
D 23
	pteaddr = &Usrptma[btokmx(mproc->p_p0br) + mproc->p_szpt - 1];
D 6
	klseek(kmem, (long)pteaddr, 0);
E 6
I 6
	(void)lseek(kmem, (off_t)pteaddr, L_SET);
E 6
	if (read(kmem, (char *)&apte, sizeof(apte)) != sizeof(apte)) {
D 7
		printf("fstat: cant read indir pte to get u for pid %d from %s\n",
		    mproc->p_pid, swapf);
E 7
I 7
D 17
		printf("fstat: can't read indir pte to get u for pid %d from %s\n", mproc->p_pid, N_SWAP);
E 17
I 17
D 18
		printf("fstat: can't read indir pte to get u for pid %d from %s\n", mproc->p_pid, _PATH_SWAP);
E 18
I 18
		VP("fstat: can't read indir pte to get u for pid %d from %s\n",
D 19
		    mproc->p_pid, _PATH_SWAP);
E 19
I 19
		    mproc->p_pid, _PATH_DRUM);
E 19
E 18
E 17
E 7
D 6
		return (0);
E 6
I 6
		return(0);
E 6
	}
D 6
	klseek(mem,
	    (long)ctob(apte.pg_pfnum+1) - (UPAGES+CLSIZE) * sizeof (struct pte),
		0);
E 6
I 6
	(void)lseek(mem, (off_t)ctob(apte.pg_pfnum+1) - (UPAGES+CLSIZE)
	    * sizeof(struct pte), L_SET);
E 6
	if (read(mem, (char *)arguutl, sizeof(arguutl)) != sizeof(arguutl)) {
D 7
		printf("fstat: cant read page table for u of pid %d from %s\n",
		    mproc->p_pid, kmemf);
E 7
I 7
D 17
		printf("fstat: can't read page table for u of pid %d from %s\n", mproc->p_pid, N_KMEM);
E 17
I 17
D 18
		printf("fstat: can't read page table for u of pid %d from %s\n", mproc->p_pid, _PATH_KMEM);
E 18
I 18
		VP("fstat: can't read page table for u of pid %d from %s\n",
		    mproc->p_pid, _PATH_KMEM);
E 18
E 17
E 7
D 6
		return (0);
E 6
I 6
		return(0);
E 6
	}
D 6
	if (arguutl[0].pg_fod == 0 && arguutl[0].pg_pfnum)
		argaddr = ctob(arguutl[0].pg_pfnum);
	else
		argaddr = 0;
	pcbpf = arguutl[CLSIZE].pg_pfnum;
E 6
D 7
	ncl = (size + NBPG*CLSIZE - 1) / (NBPG*CLSIZE);
E 7
I 7
	ncl = (sizeof(struct user) + NBPG*CLSIZE - 1) / (NBPG*CLSIZE);
E 7
	while (--ncl >= 0) {
		i = ncl * CLSIZE;
D 6
		klseek(mem, (long)ctob(arguutl[CLSIZE+i].pg_pfnum), 0);
E 6
I 6
		(void)lseek(mem, (off_t)ctob(arguutl[CLSIZE+i].pg_pfnum), L_SET);
E 6
		if (read(mem, user.upages[i], CLSIZE*NBPG) != CLSIZE*NBPG) {
D 6
			printf("fstat: cant read page %d of u of pid %d from %s\n",
E 6
I 6
D 7
			printf("fstat: cant read page %u of u of pid %d from %s\n",
E 6
			    arguutl[CLSIZE+i].pg_pfnum, mproc->p_pid, memf);
E 7
I 7
D 17
			printf("fstat: can't read page %u of u of pid %d from %s\n", arguutl[CLSIZE+i].pg_pfnum, mproc->p_pid, N_MEM);
E 17
I 17
D 18
			printf("fstat: can't read page %u of u of pid %d from %s\n", arguutl[CLSIZE+i].pg_pfnum, mproc->p_pid, _PATH_MEM);
E 18
I 18
			VP("fstat: can't read page %u of u of pid %d from %s\n",
			    arguutl[CLSIZE+i].pg_pfnum, mproc->p_pid,
			    _PATH_MEM);
E 18
E 17
E 7
			return(0);
E 23
I 23
	/*
	 * root directory vnode, if one
	 */
D 28
	if (up->u_rdir)
		vtrans(up->u_rdir, RDIR);
E 28
I 28
	if (filed.fd_rdir)
D 47
		vtrans(filed.fd_rdir, RDIR);
E 47
I 47
		vtrans(filed.fd_rdir, RDIR, FREAD);
E 47
D 29
#ifdef notdef
E 29
I 29
D 40
#ifndef NEWVM
E 40
E 29
E 28
	/*
D 40
	 * text vnode
	 */
	if (p->p_textp && 
D 24
	    kvm_read((int)p->p_textp+(int)&((struct text *)0)->x_vptr, &xvptr,
E 24
I 24
D 28
	    kvm_read(&(p->p_textp->x_vptr), &xvptr,
E 24
	    sizeof (struct vnode *)) == sizeof (struct vnode *) &&
E 28
I 28
	    KVM_READ(&(p->p_textp->x_vptr), &xvptr, sizeof (struct vnode *)) &&
E 28
	    xvptr != NULL)
		vtrans(xvptr, TEXT);
I 28
#endif
E 28
	/*
E 40
	 * current working directory vnode
	 */
D 28
	vtrans(up->u_cdir, CDIR);
E 28
I 28
D 47
	vtrans(filed.fd_cdir, CDIR);
E 47
I 47
	vtrans(filed.fd_cdir, CDIR, FREAD);
E 47
E 28
	/*
	 * ktrace vnode, if one
	 */
	if (p->p_tracep)
D 47
		vtrans(p->p_tracep, TRACE);
E 47
I 47
		vtrans(p->p_tracep, TRACE, FREAD|FWRITE);
E 47
	/*
	 * open files
	 */
D 28
	for (i = 0; i <= up->u_lastfile; i++) {
		if (up->u_ofile[i] == 0)
E 28
I 28
#define FPSIZE	(sizeof (struct file *))
D 29
	ALLOC_OFILES(last=filed.fd_lastfile);
#ifdef newvm
	if (!KVM_READ(filed.fd_ofiles, ofiles, filed.fd_lastfile * FPSIZE)) {
		dprintf(stderr, "can't read file structures at %x for pid %d\n",
			filed.fd_ofiles, Pid);
		return;
	}
E 29
I 29
D 36
	ALLOC_OFILES(filed.fd_lastfile);
E 36
I 36
	ALLOC_OFILES(filed.fd_lastfile+1);
E 36
D 40
#ifdef NEWVM
E 40
	if (filed.fd_nfiles > NDFILE) {
		if (!KVM_READ(filed.fd_ofiles, ofiles,
D 36
		    filed.fd_lastfile * FPSIZE)) {
E 36
I 36
		    (filed.fd_lastfile+1) * FPSIZE)) {
E 36
			dprintf(stderr,
			    "can't read file structures at %x for pid %d\n",
			    filed.fd_ofiles, Pid);
			return;
		}
	} else
D 36
		bcopy(filed0.fd_dfiles, ofiles, filed.fd_lastfile * FPSIZE);
E 36
I 36
		bcopy(filed0.fd_dfiles, ofiles, (filed.fd_lastfile+1) * FPSIZE);
E 36
E 29
D 40
#else
D 29
	bcopy(filed.fd_ofile, ofiles, NDFILE * FPSIZE);
E 29
I 29
	bcopy(filed.fd_ofile, ofiles, MIN(filed.fd_lastfile, NDFILE) * FPSIZE);
	last = filed.fd_lastfile;
E 29
	if ((last > NDFILE) && !KVM_READ(filed.fd_moreofiles, &ofiles[NDFILE],
	    (last - NDFILE) * FPSIZE)) {
		dprintf(stderr, "can't read rest of files at %x for pid %d\n",
			filed.fd_moreofiles, Pid);
		return;
	}
#endif
E 40
D 34
	for (i = 0; i <= filed.fd_lastfile; i++) {
E 34
I 34
D 36
	for (i = 0; i < filed.fd_lastfile; i++) {
E 36
I 36
	for (i = 0; i <= filed.fd_lastfile; i++) {
E 36
E 34
		if (ofiles[i] == NULL)
E 28
			continue;
D 28
		if (kvm_read(up->u_ofile[i], &file, sizeof (struct file)) !=
		    sizeof (struct file)) {
			dprintf(stderr, "can't read file %d for pid %d\n",
				i, Pid);
E 28
I 28
		if (!KVM_READ(ofiles[i], &file, sizeof (struct file))) {
			dprintf(stderr, "can't read file %d at %x for pid %d\n",
				i, ofiles[i], Pid);
E 28
			continue;
		}
		if (file.f_type == DTYPE_VNODE)
D 47
			vtrans((struct vnode *)file.f_data, i);
E 47
I 47
			vtrans((struct vnode *)file.f_data, i, file.f_flag);
E 47
D 34
		else if (file.f_type == DTYPE_SOCKET && checkfile == 0)
			socktrans((struct socket *)file.f_data, i);
E 34
I 34
		else if (file.f_type == DTYPE_SOCKET) {
			if (checkfile == 0)
				socktrans((struct socket *)file.f_data, i);
		}
E 34
		else {
			dprintf(stderr, 
				"unknown file type %d for file %d of pid %d\n",
				file.f_type, i, Pid);
E 23
		}
	}
D 6
	return (1);
E 6
I 6
D 23
	return(1);
E 23
E 6
}

I 31
void
E 31
D 6
#define	NMAX	8
#define	NUID	2048

E 6
I 6
D 23
static
E 6
dotext()
E 23
I 23
D 47
vtrans(vp, i)
E 47
I 47
vtrans(vp, i, flag)
E 47
	struct vnode *vp;
I 31
	int i;
I 47
	int flag;
E 47
E 31
E 23
{
I 31
D 48
	extern char *devname();
E 48
E 31
D 13
	struct text	text;
E 13
I 13
D 23
	struct text text;
E 23
I 23
	struct vnode vn;
	struct filestat fst;
D 31
	char *filename = NULL;
D 26
	char *fstype;
	char *getmnton(), *vtype();
	int nodata = 0;
E 26
I 26
	char *badtype = NULL;
	char *getmnton();
E 26
I 25
	extern char *devname();
E 31
I 26
D 47
	char mode[15];
E 47
I 47
	char rw[3], mode[15];
E 47
I 31
D 34
	char *badtype, *filename, *getmnton();
E 34
I 34
	char *badtype = NULL, *filename, *getmnton();
E 34
E 31
E 26
E 25
E 23
E 13

D 6
	lseek(kmem, (long) mproc->p_textp, 0);
E 6
I 6
D 23
	(void)lseek(kmem, (off_t)mproc->p_textp, L_SET);
E 6
	if (read(kmem, (char *) &text, sizeof(text)) != sizeof(text)) {
D 7
		cantread("text table", kmemf);
E 7
I 7
D 11
		cantread("text table", N_KMEM);
E 11
I 11
D 17
		rerr1("text table", N_KMEM);
E 17
I 17
		rerr1("text table", _PATH_KMEM);
E 23
I 23
D 28
	if (kvm_read((off_t)vp, &vn, sizeof (struct vnode)) != 
	    sizeof (struct vnode)) {
E 28
I 28
D 31
	if (!KVM_READ((off_t)vp, &vn, sizeof (struct vnode))) {
E 31
I 31
	filename = badtype = NULL;
	if (!KVM_READ(vp, &vn, sizeof (struct vnode))) {
E 31
E 28
		dprintf(stderr, "can't read vnode at %x for pid %d\n",
			vp, Pid);
E 23
E 17
E 11
E 7
		return;
	}
D 7
	if (text.x_flag == 0)
		return;
	itrans(DTYPE_INODE, text.x_iptr, TEXT);
E 7
I 7
D 23
	if (text.x_flag)
D 20
		itrans(DTYPE_INODE, text.x_iptr, TEXT);
E 20
I 20
		vtrans(DTYPE_VNODE, text.x_vptr, TEXT);
E 20
E 7
}
E 23
I 23
D 26
	switch (vn.v_tag) {
	case VT_NON:
		fstype = " non";
		nodata = 1;
		break;
	case VT_UFS:
		fstype = " ufs";
		ufs_filestat(&vn, &fst);
		break;
	case VT_MFS:
		fstype = " mfs";
		ufs_filestat(&vn, &fst);
		break;
	case VT_NFS:
		fstype = " nfs";
		nfs_filestat(&vn, &fst);
		break;
	default: {
		static char unknown[10];
		sprintf(fstype = unknown, " ?%d", vn.v_tag);
		nodata = 1;
		break;;
E 26
I 26
	if (vn.v_type == VNON || vn.v_tag == VT_NON)
		badtype = "none";
	else if (vn.v_type == VBAD)
		badtype = "bad";
	else
		switch (vn.v_tag) {
		case VT_UFS:
D 37
			ufs_filestat(&vn, &fst);
E 37
I 37
			if (!ufs_filestat(&vn, &fst))
				badtype = "error";
E 37
			break;
		case VT_MFS:
D 37
			ufs_filestat(&vn, &fst);
E 37
I 37
			if (!ufs_filestat(&vn, &fst))
				badtype = "error";
E 37
			break;
		case VT_NFS:
D 37
			nfs_filestat(&vn, &fst);
E 37
I 37
			if (!nfs_filestat(&vn, &fst))
				badtype = "error";
E 37
			break;
		default: {
			static char unknown[10];
			sprintf(badtype = unknown, "?(%x)", vn.v_tag);
			break;;
		}
E 26
	}
D 26
	}
E 26
	if (checkfile) {
		int fsmatch = 0;
		register DEVS *d;
E 23

D 6
char 	*itypename[] = {
E 6
I 6
D 7
char	*itypename[] = {
E 6
	"unk",
#define UNK 0	/* unknown */
	"chr",
#define CHR 1	
	"dir",
#define DIR 2
	"blk",
#define BLK 3
	"reg",
#define REG 4
	"lnk",
#define LNK 5
	"soc"
#define SOC 6
};

E 7
I 6
D 23
static
E 6
D 7
itype(mode)
I 6
	u_short mode;
E 6
{
	switch(mode&IFMT) {
	case IFCHR:
		return(CHR);
	case IFDIR:
		return(DIR);
	case IFBLK:
		return(BLK);
	case IFREG:
		return(REG);
	case IFLNK:
		return(LNK);
	case IFSOCK:
		return(SOC);
	default:
		return(0);
	}
}

I 6
static
E 7
E 6
D 20
itrans(ftype, g, fno)
E 20
I 20
vtrans(ftype, g, fno)
E 20
D 6
struct inode	*g;  /* if ftype is inode */
E 6
I 6
	int ftype, fno;
D 13
	struct inode	*g;		/* if ftype is inode */
E 13
I 13
D 20
	struct inode *g;		/* if ftype is inode */
E 20
I 20
	struct vnode *g;		/* if ftype is vnode */
E 20
E 13
E 6
{
I 20
	struct vnode vnode;
E 20
D 7
	struct inode	inode;
	dev_t	idev;
D 6
	int 	type;
	char 	*comm;
E 6
I 6
	int	type;
	char	*comm;
E 7
I 7
	struct inode inode;
	dev_t idev;
D 20
	char *comm, *itype();
E 20
I 20
	char *comm, *vtype();
E 20
I 9
	char *name = (char *)NULL;	/* set by devmatch() on a match */
E 9
E 7
E 6

D 6
	if (g == 0 && ! fflg) {
		goto skip;
E 6
I 6
D 21
	if (g || fflg) {
E 21
I 21
	if (ftype == DTYPE_VNODE && (g || fflg)) {
E 21
		(void)lseek(kmem, (off_t)g, L_SET);
D 20
		if (read(kmem, (char *)&inode, sizeof(inode)) != sizeof(inode)) {
D 11
			vprintf("error %d reading inode at %x from kmem\n", errno, (int)g);
E 11
I 11
D 18
			rerr2(errno, (int)g, "inode");
E 18
I 18
			rerr2((int)g, "inode");
E 20
I 20
		if (read(kmem, (char *)&vnode, sizeof(vnode)) != sizeof(vnode)) {
			rerr2((int)g, "vnode");
E 23
I 23
D 26
		if (nodata)
E 26
I 26
		if (badtype)
E 26
E 23
E 20
E 18
E 11
			return;
D 23
		}
D 20
		idev = inode.i_dev;
D 9
		if (fflg && !devmatch(idev, inode.i_number))
E 9
I 9
		if (fflg && !devmatch(idev, inode.i_number, &name))
E 9
			return;
E 20
I 20
		if (vnode.v_op != (struct vnodeops *)nl[X_UFSOPS].n_value &&
		    (vnode.v_op != (struct vnodeops *)nl[X_BLKOPS].n_value ||
		     vnode.v_data == (qaddr_t)0)) {
			if (fflg)
				return;
			ftype = -1;
		} else {
			(void)lseek(kmem, (off_t)vnode.v_data, L_SET);
			if (read(kmem, (char *)&inode, sizeof(inode))
			    != sizeof(inode)) {
				rerr2((int)vnode.v_data, "inode");
				return;
E 23
I 23
		for (d = devs; d != NULL; d = d->next)
D 26
			if (d->dev == fst.fsid) {
E 26
I 26
			if (d->fsid == fst.fsid) {
E 26
				fsmatch = 1;
				if (d->ino == fst.fileid) {
					filename = d->name;
					break;
				}
E 23
			}
D 23
			idev = inode.i_dev;
			if (fflg && !devmatch(idev, inode.i_number, &name))
				return;
		}
E 23
I 23
		if (fsmatch == 0 || (filename == NULL && fsflg == 0))
			return;
E 23
E 20
E 6
	}
D 6
	lseek(kmem, (long) g, 0);
	if (read(kmem, (char *) &inode, sizeof(inode))
					!= sizeof(inode)) {
		vprintf("error %d reading inode at %x from kmem\n", errno, g);
		return;
	}
D 3
	if (special)
		idev = inode.i_dev;
	else
		idev = inode.i_dev;
	if (fflg && major(idev) != Mdev)
		return;	
	if (fflg && minor(idev) != mdev)
		return;	
	if (inum && inode.i_number != inum)
E 3
I 3
	idev = inode.i_dev;
	if (fflg && !devmatch(idev, inode.i_number))
E 3
		return;
skip:
E 6
D 23
	if (mproc->p_pid == 0)
		comm = "swapper";
	else if (mproc->p_pid == 2)
		comm = "pagedaemon";
E 23
I 23
	PREFIX(i);
D 26
	fputs(fstype, stdout);
	if (nodata) {
		printf(" -       -    -    -\n");
E 26
I 26
	if (badtype) {
		(void)printf(" -         -  %10s    -\n", badtype);
E 26
		return;
	}
	if (nflg)
D 26
		printf(" %2d,%-2d", major(fst.fsid), minor(fst.fsid));
E 26
I 26
		(void)printf(" %2d,%-2d", major(fst.fsid), minor(fst.fsid));
E 26
E 23
	else
D 6
		comm = u.u_comm;
E 6
I 6
D 23
		comm = user.user.u_comm;
E 6
D 18
	printf("%-8.8s %-10.10s %5d  ", uname, comm, mproc->p_pid);
E 18
I 18
	(void)printf("%-8.8s %-10.10s %5d  ", uname, comm, mproc->p_pid);
E 18
D 7
	if (fno == WD)
		printf("  wd");
	else if (fno == TEXT)
		printf("text");
	else
E 7
I 7

	switch(fno) {
	case WD:
D 18
		printf("  wd"); break;
E 18
I 18
		(void)printf("  wd"); break;
E 18
	case TEXT:
D 18
		printf("text"); break;
E 18
I 18
		(void)printf("text"); break;
E 23
I 23
D 26
		printf(" %-8s", getmnton(vn.v_mount));
	printf(" %6d %3s", fst.fileid, vtype(vn.v_type));
E 26
I 26
		(void)printf(" %-8s", getmnton(vn.v_mount));
	if (nflg)
		(void)sprintf(mode, "%o", fst.mode);
	else
		strmode(fst.mode, mode);
	(void)printf(" %6d %10s", fst.fileid, mode);
E 26
	switch (vn.v_type) {
	case VBLK:
D 25
		if (nflg)
E 25
I 25
	case VCHR: {
		char *name;

		if (nflg || ((name = devname(fst.rdev, vn.v_type == VCHR ? 
		    S_IFCHR : S_IFBLK)) == NULL))
E 25
			printf("  %2d,%-2d", major(fst.rdev), minor(fst.rdev));
		else
D 25
			printf(" %-6s", devname(fst.rdev, 0));
E 25
I 25
			printf(" %6s", name);
E 25
		break;
D 25
	case VCHR:
		if (nflg)
			printf("  %2d/%-2d", major(fst.rdev), minor(fst.rdev));
		else
			printf(" %-6s", devname(fst.rdev, 1));
		break;
E 25
I 25
	}
E 25
E 23
E 18
	default:
E 7
D 18
		printf("%4d", fno);
E 18
I 18
D 23
		(void)printf("%4d", fno);
E 23
I 23
		printf(" %6d", fst.size);
E 23
E 18
I 7
	}
I 47
	rw[0] = '\0';
	if (flag & FREAD)
		strcat(rw, "r");
	if (flag & FWRITE)
		strcat(rw, "w");
	printf(" %2s", rw);
E 47
I 23
	if (filename && !fsflg)
D 47
		printf(" %s", filename);
		
E 47
I 47
		printf("  %s", filename);
E 47
	putchar('\n');
}
E 23
E 7

I 31
D 37
void
E 37
I 37
int
E 37
E 31
D 23
	if (g == 0) {
D 18
		printf("* (deallocated)\n");
E 18
I 18
		(void)printf("* (deallocated)\n");
E 18
		return;
	}
E 23
I 23
ufs_filestat(vp, fsp)
	struct vnode *vp;
	struct filestat *fsp;
{
D 37
	struct inode *ip = VTOI(vp);
E 37
I 37
	struct inode inode;
E 37
E 23

D 6
	if (ftype == DTYPE_INODE) {
		type = itype(inode.i_mode);  /* determine inode type */
		printf("\t%2d, %2d\t%5d\t%6d\t%3s\n", major(inode.i_dev), minor(inode.i_dev),
			inode.i_number, type == SOC?0:inode.i_size, itypename[type]);
	}
	else if (ftype == DTYPE_SOCKET) {
E 6
I 6
D 23
	switch(ftype) {
E 23
I 23
D 26
	fsp->fsid = (long)ip->i_dev;
E 26
I 26
D 37
	fsp->fsid = ip->i_dev & 0xffff;
E 26
	fsp->fileid = (long)ip->i_number;
I 26
	fsp->mode = (mode_t)ip->i_mode;
E 26
	fsp->size = (u_long)ip->i_size;
	fsp->rdev = ip->i_rdev;
E 37
I 37
	if (!KVM_READ(VTOI(vp), &inode, sizeof (inode))) {
		dprintf(stderr, "can't read inode at %x for pid %d\n",
			VTOI(vp), Pid);
		return 0;
	}
	fsp->fsid = inode.i_dev & 0xffff;
	fsp->fileid = (long)inode.i_number;
	fsp->mode = (mode_t)inode.i_mode;
	fsp->size = (u_long)inode.i_size;
	fsp->rdev = inode.i_rdev;

	return 1;
E 37
}
E 23
D 20
	case DTYPE_INODE:
E 20
I 20

I 31
D 37
void
E 37
I 37
int
E 37
E 31
D 23
	case DTYPE_VNODE:
E 20
D 7
		type = itype(inode.i_mode);	/* determine inode type */
E 7
D 9
		printf("\t%2d, %2d\t%5lu\t%6ld\t%3s\n", major(inode.i_dev),
E 9
I 9
D 15
		printf("\t%2d, %2d\t%5lu\t%6ld\t%3s %s\n", major(inode.i_dev),
E 9
		    minor(inode.i_dev), inode.i_number,
D 7
		    type == SOC ? 0 : inode.i_size, itypename[type]);
E 7
I 7
		    inode.i_mode == IFSOCK ? 0 : inode.i_size,
D 9
		    itype(inode.i_mode));
E 9
I 9
		    itype(inode.i_mode), name ? name : "");
E 15
I 15
D 18
		printf("\t%2d, %2d\t%5lu\t",
		    major(inode.i_dev),
		    minor(inode.i_dev), inode.i_number
		);
E 18
I 18
		(void)printf("\t%2d, %2d\t%5lu\t", major(inode.i_dev),
		    minor(inode.i_dev), inode.i_number);
E 18
		switch(inode.i_mode & IFMT) {
D 18
		case	IFSOCK:
			printf("     0\t");
E 18
I 18
		case IFSOCK:
			(void)printf("     0\t");
E 18
			break;
I 20
		case IFBLK:
E 20
D 18
		case	IFCHR:
			printf("%2d, %2d\t", major(inode.i_rdev), minor(inode.i_rdev));
E 18
I 18
		case IFCHR:
			(void)printf("%2d, %2d\t", major(inode.i_rdev),
			    minor(inode.i_rdev));
E 18
			break;
		default:
D 18
			printf("%6ld\t", inode.i_size);
E 18
I 18
			(void)printf("%6ld\t", inode.i_size);
E 18
		}
D 18
		printf("%3s %s\n", itype(inode.i_mode), name ? name : "");
E 18
I 18
D 20
		(void)printf("%3s %s\n", itype(inode.i_mode), name ? name : "");
E 20
I 20
		(void)printf("%3s %s\n", vtype(vnode.v_type), name ? name : "");
E 20
E 18
E 15
E 9
E 7
		break;
E 23
I 23
nfs_filestat(vp, fsp)
	struct vnode *vp;
	struct filestat *fsp;
{
D 26
	struct nfsnode *np = VTONFS(vp);
E 26
I 26
D 37
	register struct nfsnode *np = VTONFS(vp);
E 37
I 37
	struct nfsnode nfsnode;
E 37
	register mode_t mode;
E 26
E 23
I 20

D 23
	case -1: /* DTYPE_VNODE for a remote filesystem */
		(void)printf(" from remote filesystem\t");
		(void)printf("%3s %s\n", vtype(vnode.v_type), name ? name : "");
		break;
E 23
I 23
D 37
	fsp->fsid = np->n_vattr.va_fsid;
	fsp->fileid = np->n_vattr.va_fileid;
D 25
	fsp->size = np->n_vattr.va_size;
E 25
I 25
	fsp->size = np->n_size;
E 25
	fsp->rdev = np->n_vattr.va_rdev;
I 26
	mode = (mode_t)np->n_vattr.va_mode;
E 37
I 37
	if (!KVM_READ(VTONFS(vp), &nfsnode, sizeof (nfsnode))) {
		dprintf(stderr, "can't read nfsnode at %x for pid %d\n",
			VTONFS(vp), Pid);
		return 0;
	}
	fsp->fsid = nfsnode.n_vattr.va_fsid;
	fsp->fileid = nfsnode.n_vattr.va_fileid;
	fsp->size = nfsnode.n_size;
	fsp->rdev = nfsnode.n_vattr.va_rdev;
	mode = (mode_t)nfsnode.n_vattr.va_mode;
E 37
	switch (vp->v_type) {
	case VREG:
		mode |= S_IFREG;
		break;
	case VDIR:
		mode |= S_IFDIR;
		break;
	case VBLK:
		mode |= S_IFBLK;
		break;
	case VCHR:
		mode |= S_IFCHR;
		break;
	case VLNK:
		mode |= S_IFLNK;
		break;
	case VSOCK:
		mode |= S_IFSOCK;
		break;
	case VFIFO:
		mode |= S_IFIFO;
		break;
	};
	fsp->mode = mode;
I 37

	return 1;
E 37
E 26
}
E 23

E 20
D 23
	case DTYPE_SOCKET:
E 6
		socktrans((struct socket *)g);
D 6
	}
E 6
I 6
		break;
E 23
I 20

E 20
E 6
D 23
#ifdef DTYPE_PORT
D 6
	else if (ftype == DTYPE_PORT) {
E 6
I 6
	case DTYPE_PORT:
E 6
D 18
		printf("* (fifo / named pipe)\n");
E 18
I 18
		(void)printf("* (fifo / named pipe)\n");
E 18
D 6
	}
#endif DTYPE_PORT
	else {
E 6
I 6
		break;
#endif
E 23
I 23
char *
getmnton(m)
	struct mount *m;
{
	static struct mount mount;
	static struct mtab {
		struct mtab *next;
		struct mount *m;
		char mntonname[MNAMELEN];
	} *mhead = NULL;
	register struct mtab *mt;
E 23
I 20

E 20
D 23
	default:
E 6
D 18
		printf("* (unknown file type)\n");
E 18
I 18
		(void)printf("* (unknown file type)\n");
E 23
I 23
	for (mt = mhead; mt != NULL; mt = mt->next)
		if (m == mt->m)
			return (mt->mntonname);
D 28
	if (kvm_read((off_t)m, &mount, sizeof(struct mount)) != 
	    sizeof(struct mount)) {
E 28
I 28
D 31
	if (!KVM_READ((off_t)m, &mount, sizeof(struct mount))) {
E 31
I 31
	if (!KVM_READ(m, &mount, sizeof(struct mount))) {
E 31
E 28
		fprintf(stderr, "can't read mount table at %x\n", m);
		return (NULL);
E 23
E 18
	}
I 23
D 31
	if ((mt = (struct mtab *)malloc(sizeof (struct mtab))) == NULL) {
		fprintf(stderr, "out of memory\n");
E 31
I 31
	if ((mt = malloc(sizeof (struct mtab))) == NULL) {
		fprintf(stderr, "fstat: %s\n", strerror(errno));
E 31
		exit(1);
	}
	mt->m = m;
D 26
	bcopy(&mount.m_stat.f_mntonname[0], &mt->mntonname[0], MNAMELEN);
E 26
I 26
	bcopy(&mount.mnt_stat.f_mntonname[0], &mt->mntonname[0], MNAMELEN);
E 26
	mt->next = mhead;
	mhead = mt;
	return (mt->mntonname);
E 23
}
I 6

I 31
void
E 31
D 7
static
E 6
I 3
devmatch(idev, inum)
D 6
dev_t idev;
int inum;
E 6
I 6
	dev_t idev;
	ino_t inum;
E 7
I 7
D 23
static char *
E 23
I 23
D 26
char *
E 23
D 20
itype(mode)
	u_short mode;
E 20
I 20
vtype(type)
	enum vtype type;
E 20
E 7
E 6
{
I 23

E 23
D 7
	struct devs *d = &devs;
D 6
	for (d = d->next; d; d = d->next) {
		if (d->dev == idev) {
			if (d->inum == 0)
				return(1);
			if (d->inum == inum)
				return(1);
		}
	}
E 6
I 6

	for (d = d->next; d; d = d->next)
		if (d->dev == idev && (!d->inum || d->inum == inum))
			return(1);
E 6
	return(0);
E 7
I 7
D 20
	switch(mode & IFMT) {
	case IFCHR:
E 20
I 20
	switch(type) {
D 23
	case VCHR:
E 20
		return("chr");
E 23
I 23
	case VNON:
		return("non");
	case VREG:
		return("reg");
E 23
D 20
	case IFDIR:
E 20
I 20
	case VDIR:
E 20
		return("dir");
D 20
	case IFBLK:
E 20
I 20
	case VBLK:
E 20
		return("blk");
D 20
	case IFREG:
E 20
I 20
D 23
	case VREG:
E 20
		return("reg");
E 23
I 23
	case VCHR:
		return("chr");
E 23
D 20
	case IFLNK:
E 20
I 20
	case VLNK:
E 20
		return("lnk");
D 20
	case IFSOCK:
E 20
I 20
	case VSOCK:
E 20
		return("soc");
I 23
	case VFIFO:
		return("fif");
E 23
I 20
	case VBAD:
		return("bad");
E 20
D 23
	default:
		return("unk");
E 23
I 23
	default: {
		static char unknown[10];
		sprintf(unknown, "?%d", type);
		return(unknown);
E 23
	}
I 23
	}
E 23
	/*NOTREACHED*/
E 7
}
E 3

E 26
I 6
D 23
static
E 6
socktrans(sock)
E 23
I 23
socktrans(sock, i)
E 23
D 6
struct socket *sock;
E 6
I 6
	struct socket *sock;
I 31
	int i;
E 31
E 6
{
D 6
	struct socket 	so;
	struct protosw 	proto;
	struct domain 	dom;
	char	dname[32];	/* domain name, e.g. "inet" */
	char 	c;
	char 	*cp;
E 6
I 6
D 7
	static char	*stypename[] = {
E 7
I 7
	static char *stypename[] = {
E 7
		"unused",	/* 0 */
		"stream", 	/* 1 */
		"dgram",	/* 2 */
		"raw",		/* 3 */
		"rdm",		/* 4 */
		"seqpak"	/* 5 */
	};
#define	STYPEMAX 5
	struct socket	so;
	struct protosw	proto;
	struct domain	dom;
	struct inpcb	inpcb;
	struct unpcb	unpcb;
E 6
D 7
	int	i;
D 6
	char 	*stype;
	struct inpcb 	inpcb;
	struct unpcb 	unpcb;
E 6
I 6
	char	c, *cp, *stype, *strcpy(), *strcat();
	char	dname[32];	/* domain name, e.g. "inet" */
E 7
I 7
	int len;
	char dname[32], *strcpy();
E 7
E 6

I 23
	PREFIX(i);

E 23
	/* fill in socket */
D 6
	lseek(kmem, (long) sock, 0);
	if (read(kmem, (char *) &so, sizeof(struct socket)) 
	    != sizeof(struct socket)){
		vprintf("error %d reading socket at %x from kmem\n", errno, sock);
E 6
I 6
D 23
	(void)lseek(kmem, (off_t)sock, L_SET);
	if (read(kmem, (char *)&so, sizeof(struct socket))
E 23
I 23
D 28
	if (kvm_read((off_t)sock, (char *)&so, sizeof(struct socket))
E 23
	    != sizeof(struct socket)) {
E 28
I 28
	if (!KVM_READ(sock, &so, sizeof(struct socket))) {
E 28
D 11
		vprintf("error %d reading socket at %x from kmem\n", errno, (int)sock);
E 11
I 11
D 18
		rerr2(errno, (int)sock, "socket");
E 18
I 18
D 23
		rerr2((int)sock, "socket");
E 23
I 23
		dprintf(stderr, "can't read sock at %x\n", sock);
E 23
E 18
E 11
E 6
D 26
		return;
E 26
I 26
		goto bad;
E 26
	}

	/* fill in protosw entry */
D 6
	lseek(kmem, (long) so.so_proto, 0);
	if (read(kmem, (char *) &proto, sizeof(struct protosw)) 
	    != sizeof(struct protosw)){
		vprintf("error %d reading protosw at %x from kmem\n", errno, so.so_proto);
E 6
I 6
D 23
	(void)lseek(kmem, (off_t)so.so_proto, L_SET);
	if (read(kmem, (char *)&proto, sizeof(struct protosw))
E 23
I 23
D 28
	if (kvm_read((off_t)so.so_proto, (char *)&proto, sizeof(struct protosw))
E 23
	    != sizeof(struct protosw)) {
E 28
I 28
	if (!KVM_READ(so.so_proto, &proto, sizeof(struct protosw))) {
E 28
D 11
		vprintf("error %d reading protosw at %x from kmem\n", errno, (int)so.so_proto);
E 11
I 11
D 18
		rerr2(errno, (int)so.so_proto, "protosw");
E 18
I 18
D 23
		rerr2((int)so.so_proto, "protosw");
E 23
I 23
		dprintf(stderr, "can't read protosw at %x", so.so_proto);
E 23
E 18
E 11
E 6
D 26
		return;
E 26
I 26
		goto bad;
E 26
	}

	/* fill in domain */
D 6
	lseek(kmem, (long) proto.pr_domain, 0);
	if (read(kmem, (char *) &dom, sizeof(struct domain)) 
	    != sizeof(struct domain)){
		vprintf("error %d reading domain at %x from kmem\n", errno, proto.pr_domain);
E 6
I 6
D 23
	(void)lseek(kmem, (off_t)proto.pr_domain, L_SET);
	if (read(kmem, (char *)&dom, sizeof(struct domain))
E 23
I 23
D 28
	if (kvm_read((off_t)proto.pr_domain, (char *)&dom, sizeof(struct domain))
E 23
	    != sizeof(struct domain)) {
E 28
I 28
	if (!KVM_READ(proto.pr_domain, &dom, sizeof(struct domain))) {
E 28
D 11
		vprintf("error %d reading domain at %x from kmem\n", errno, (int)proto.pr_domain);
E 11
I 11
D 18
		rerr2(errno, (int)proto.pr_domain, "domain");
E 18
I 18
D 23
		rerr2((int)proto.pr_domain, "domain");
E 23
I 23
		dprintf(stderr, "can't read domain at %x\n", proto.pr_domain);
E 23
E 18
E 11
E 6
D 26
		return;
E 26
I 26
		goto bad;
E 26
	}

D 7
	/* Grab domain name */
D 6
	lseek(kmem, (long) dom.dom_name, 0);
	for (cp=dname, i=0; i < 30; i++, cp++) { /* 30 leaves room for null byte */
E 6
I 6
	(void)lseek(kmem, (off_t)dom.dom_name, L_SET);
	/* 30 leaves room for null byte */
	for (cp = dname, i = 0; i < 30; i++, cp++) {
E 6
		if (read(kmem, (char *)&c, sizeof(char)) != sizeof(char)) {
D 6
		    vprintf("error %d reading char at %x from kmem\n", errno, dom.dom_name+i);
E 6
I 6
		    vprintf("error %d reading char at %x from kmem\n", errno, (int)(dom.dom_name+i));
E 6
		    break;
		}
		if (c == '\0')
			break;
		*cp = c;
	}
D 6
	*cp='\0';
E 6
I 6
	*cp = '\0';
E 6
	/* kludge "internet" --> "inet" for brevity */
E 7
I 7
D 28
	/*
	 * grab domain name
	 * kludge "internet" --> "inet" for brevity
	 */
E 7
D 6
	if (dom.dom_family == AF_INET)	
		strcpy(dname, "inet");
E 6
I 6
	if (dom.dom_family == AF_INET)
D 26
		(void)strcpy(dname, "inet");
E 26
I 26
		strcpy(dname, "inet");
E 26
E 6
D 7

D 4
	if (so.so_type < 1 || so.so_type > STYPEMAX)
		stype = (char *)sprintf(emalloc(10),"unk%d", so.so_type);
	else
E 4
I 4
	if (so.so_type < 1 || so.so_type > STYPEMAX) {
D 6
		
E 6
		stype = emalloc(10);
D 6
		(void)sprintf(stype,"unk%d", so.so_type);
	} else
E 6
I 6
		(void)sprintf(stype, "unk%d", so.so_type);
E 7
I 7
	else {
D 23
		(void)lseek(kmem, (off_t)dom.dom_name, L_SET);
		if ((len = read(kmem, dname, sizeof(dname) - 1)) < 0) {
D 11
			vprintf("error %d reading char at %x from kmem\n", errno, (int)dom.dom_name);
E 11
I 11
D 18
			rerr2(errno, (int)dom.dom_name, "char");
E 18
I 18
			rerr2((int)dom.dom_name, "char");
E 23
I 23
		if ((len = kvm_read((off_t)dom.dom_name, dname, sizeof(dname) - 1)) < 0) {
			dprintf(stderr, "can't read domain name at %x\n",
				dom.dom_name);
E 23
E 18
E 11
			dname[0] = '\0';
		}
		else
			dname[len] = '\0';
E 28
I 28
D 31
	if ((len = kvm_read((off_t)dom.dom_name, dname, sizeof(dname) - 1)) < 0) {
E 31
I 31
D 40
	if ((len =
	    kvm_read(dom.dom_name, dname, sizeof(dname) - 1)) < 0) {
E 40
I 40
	if ((len = kvm_read(kd, (u_long)dom.dom_name, dname,
	    sizeof(dname) - 1)) < 0) {
E 40
E 31
		dprintf(stderr, "can't read domain name at %x\n",
			dom.dom_name);
		dname[0] = '\0';
E 28
E 7
	}
I 28
	else
		dname[len] = '\0';
E 28
I 7

	if ((u_short)so.so_type > STYPEMAX)
D 18
		printf("* (%s unk%d %x", dname, so.so_type, so.so_state);
E 18
I 18
D 23
		(void)printf("* (%s unk%d %x", dname, so.so_type, so.so_state);
E 23
I 23
D 26
		(void)printf("* %s ?%d", dname, so.so_type);
E 26
I 26
		printf("* %s ?%d", dname, so.so_type);
E 26
E 23
E 18
E 7
	else
E 6
E 4
D 7
		stype = stypename[so.so_type];
E 7
I 7
D 18
		printf("* (%s %s %x", dname, stypename[so.so_type],
E 18
I 18
D 23
		(void)printf("* (%s %s %x", dname, stypename[so.so_type],
E 18
		    so.so_state);
E 23
I 23
D 26
		(void)printf("* %s %s", dname, stypename[so.so_type]);
E 26
I 26
		printf("* %s %s", dname, stypename[so.so_type]);
E 26
E 23
E 7

D 7
	/* print sock type, sock state, and domain name */
	printf("* (%s %s %x", dname, stype, so.so_state);

E 7
	/* 
D 11
	 * protocol specific formating 
E 11
I 11
	 * protocol specific formatting
E 11
	 *
D 7
	 * Try to find interesting things to print.  For tcp, the
	 * interesting thing is the address of the tcpcb, for udp
	 * and others, just the inpcb (socket pcb).  For unix
	 * domain, its the address of the socket pcb and the address of
	 * the connected pcb (if connected).  Otherwise just print
	 * the protocol number and address of the socket itself. The
	 * idea is not to duplicate netstat, but to make available
	 * enough information for further analysis. 
E 7
I 7
	 * Try to find interesting things to print.  For tcp, the interesting
	 * thing is the address of the tcpcb, for udp and others, just the
	 * inpcb (socket pcb).  For unix domain, its the address of the socket
	 * pcb and the address of the connected pcb (if connected).  Otherwise
	 * just print the protocol number and address of the socket itself.
	 * The idea is not to duplicate netstat, but to make available enough
	 * information for further analysis.
E 7
	 */
D 7
	if (dom.dom_family == AF_INET) {
		/* print name of protocol number */
		printf(" %s", getinetproto(proto.pr_protocol));
E 7
I 7
	switch(dom.dom_family) {
	case AF_INET:
		getinetproto(proto.pr_protocol);
E 7
		if (proto.pr_protocol == IPPROTO_TCP ) {
			if (so.so_pcb) {
D 6
				lseek(kmem, (long) so.so_pcb, 0);
				if (read(kmem, (char *) &inpcb, sizeof(struct inpcb)) 
E 6
I 6
D 23
				(void)lseek(kmem, (off_t)so.so_pcb, L_SET);
				if (read(kmem, (char *)&inpcb, sizeof(struct inpcb))
E 23
I 23
D 31
				if (kvm_read((off_t)so.so_pcb, (char *)&inpcb, sizeof(struct inpcb))
E 23
E 6
				    != sizeof(struct inpcb)){
E 31
I 31
D 40
				if (kvm_read(so.so_pcb, &inpcb,
				    sizeof(struct inpcb))
E 40
I 40
				if (kvm_read(kd, (u_long)so.so_pcb,
				    (char *)&inpcb, sizeof(struct inpcb))
E 40
				    != sizeof(struct inpcb)) {
E 31
D 7
					vprintf("error %d reading inpcb at %x from kmem\n",
D 6
					     errno, so.so_pcb);
E 6
I 6
					     errno, (int)so.so_pcb);
E 7
I 7
D 11
					vprintf("error %d reading inpcb at %x from kmem\n", errno, (int)so.so_pcb);
E 11
I 11
D 18
					rerr2(errno, (int)so.so_pcb, "inpcb");
E 18
I 18
D 23
					rerr2((int)so.so_pcb, "inpcb");
E 23
I 23
					dprintf(stderr, 
D 31
					     "can't read inpcb at %x\n", so.so_pcb);
E 31
I 31
					    "can't read inpcb at %x\n",
					    so.so_pcb);
E 31
E 23
E 18
E 11
E 7
E 6
D 26
					return;
E 26
I 26
					goto bad;
E 26
				}
D 6
				printf(" %x", inpcb.inp_ppcb);
E 6
I 6
D 18
				printf(" %x", (int)inpcb.inp_ppcb);
E 18
I 18
D 26
				(void)printf(" %x", (int)inpcb.inp_ppcb);
E 26
I 26
				printf(" %x", (int)inpcb.inp_ppcb);
E 26
E 18
E 6
			}
D 6
		} else if (so.so_pcb) {
				printf(" %x", so.so_pcb);
E 6
		}
D 6
	} else if (dom.dom_family == AF_UNIX) {	
E 6
I 6
		else if (so.so_pcb)
D 18
			printf(" %x", (int)so.so_pcb);
E 18
I 18
D 26
			(void)printf(" %x", (int)so.so_pcb);
E 26
I 26
			printf(" %x", (int)so.so_pcb);
E 26
E 18
D 7
	}
	else if (dom.dom_family == AF_UNIX) {
E 7
I 7
		break;
	case AF_UNIX:
E 7
E 6
		/* print address of pcb and connected pcb */
		if (so.so_pcb) {
D 6
			printf(" %x", so.so_pcb);
			lseek(kmem, (long) so.so_pcb, 0);
			if (read(kmem, (char *) &unpcb, sizeof(struct unpcb)) 
E 6
I 6
D 18
			printf(" %x", (int)so.so_pcb);
E 18
I 18
D 26
			(void)printf(" %x", (int)so.so_pcb);
E 26
I 26
			printf(" %x", (int)so.so_pcb);
E 26
E 18
D 23
			(void)lseek(kmem, (off_t)so.so_pcb, L_SET);
			if (read(kmem, (char *)&unpcb, sizeof(struct unpcb))
E 23
I 23
D 31
			if (kvm_read((off_t)so.so_pcb, (char *)&unpcb, sizeof(struct unpcb))
E 23
E 6
			    != sizeof(struct unpcb)){
E 31
I 31
D 40
			if (kvm_read(so.so_pcb, &unpcb,
E 40
I 40
			if (kvm_read(kd, (u_long)so.so_pcb, (char *)&unpcb,
E 40
			    sizeof(struct unpcb)) != sizeof(struct unpcb)){
E 31
D 7
				vprintf("error %d reading unpcb at %x from kmem\n",
D 6
				     errno, so.so_pcb);
E 6
I 6
				     errno, (int)so.so_pcb);
E 7
I 7
D 11
				vprintf("error %d reading unpcb at %x from kmem\n", errno, (int)so.so_pcb);
E 11
I 11
D 18
				rerr2(errno, (int)so.so_pcb, "unpcb");
E 18
I 18
D 23
				rerr2((int)so.so_pcb, "unpcb");
E 23
I 23
				dprintf(stderr, "can't read unpcb at %x\n",
D 31
					so.so_pcb);
E 31
I 31
				    so.so_pcb);
E 31
E 23
E 18
E 11
E 7
E 6
D 26
				return;
E 26
I 26
				goto bad;
E 26
			}
D 3
			if (unpcb.unp_conn)
				printf(" -> %x", unpcb.unp_conn);
E 3
I 3
			if (unpcb.unp_conn) {
D 7
				char shoconn[4]; *shoconn = 0;
E 7
I 7
				char shoconn[4], *cp;
E 7
I 6

I 7
				cp = shoconn;
E 7
E 6
				if (!(so.so_state & SS_CANTRCVMORE))
D 6
					strcat(shoconn, "<");
				strcat(shoconn,"-");
E 6
I 6
D 7
					(void)strcat(shoconn, "<");
				(void)strcat(shoconn, "-");
E 7
I 7
					*cp++ = '<';
				*cp++ = '-';
E 7
E 6
				if (!(so.so_state & SS_CANTSENDMORE))
D 6
					strcat(shoconn, ">");
				printf(" %s %x", shoconn, unpcb.unp_conn);
E 6
I 6
D 7
					(void)strcat(shoconn, ">");
E 7
I 7
					*cp++ = '>';
				*cp = '\0';
E 7
D 18
				printf(" %s %x", shoconn, (int)unpcb.unp_conn);
E 18
I 18
D 26
				(void)printf(" %s %x", shoconn,
E 26
I 26
				printf(" %s %x", shoconn,
E 26
				    (int)unpcb.unp_conn);
E 18
E 6
			}
E 3
		}
D 6
	} else {
		/* print protocol number and socket address */
		printf(" %d %x", proto.pr_protocol, sock);
E 6
D 7
	}
I 6
	else		/* print protocol number and socket address */
E 7
I 7
		break;
	default:
		/* print protocol number and socket address */
E 7
D 18
		printf(" %d %x", proto.pr_protocol, (int)sock);
E 18
I 18
D 26
		(void)printf(" %d %x", proto.pr_protocol, (int)sock);
E 26
I 26
		printf(" %d %x", proto.pr_protocol, (int)sock);
E 26
E 18
I 7
	}
E 7
E 6
D 18
	printf(")\n");
E 18
I 18
D 23
	(void)printf(")\n");
E 23
I 23
D 26
	(void)printf("\n");
E 26
I 26
	printf("\n");
	return;
bad:
	printf("* error\n");
E 26
E 23
E 18
}

D 6
char *
E 6
I 6
D 7
static char *
E 7
I 7
/*
 * getinetproto --
 *	print name of protocol number
 */
I 31
void
E 31
D 23
static
E 23
E 7
E 6
getinetproto(number)
I 6
	int number;
E 6
{
I 4
D 6
	char	*cp;
E 6
I 6
	char *cp;
E 6

E 4
	switch(number) {
D 6
	case 0:	 return("ip");
	case 1:	 return("icmp");
	case 2:	 return("ggp");
	case 6:	 return("tcp");
	case 8:	 return("egp");
	case 12: return("pup");
	case 17: return("udp");
	case 22: return("idp");
E 6
I 6
D 7
	case 0:	  return("ip");
	case 1:	  return("icmp");
	case 2:	  return("ggp");
	case 6:	  return("tcp");
	case 8:	  return("egp");
	case 12:  return("pup");
	case 17:  return("udp");
	case 22:  return("idp");
E 6
	case 255: return("raw");
E 7
I 7
	case IPPROTO_IP:
		cp = "ip"; break;
	case IPPROTO_ICMP:
		cp ="icmp"; break;
	case IPPROTO_GGP:
		cp ="ggp"; break;
	case IPPROTO_TCP:
		cp ="tcp"; break;
	case IPPROTO_EGP:
		cp ="egp"; break;
	case IPPROTO_PUP:
		cp ="pup"; break;
	case IPPROTO_UDP:
		cp ="udp"; break;
	case IPPROTO_IDP:
		cp ="idp"; break;
	case IPPROTO_RAW:
		cp ="raw"; break;
E 7
D 4
	default: return((char *)sprintf(emalloc(16),"%d",number));
E 4
I 4
	default:
D 6
		(void)sprintf(emalloc(16),"%d",number);
E 6
I 6
D 7
		(void)sprintf(cp = emalloc(16), "%d", number);
E 6
		return(cp);
E 7
I 7
D 18
		printf(" %d", number);
E 18
I 18
D 26
		(void)printf(" %d", number);
E 26
I 26
		printf(" %d", number);
E 26
E 18
		return;
E 7
E 4
	}
I 7
D 18
	printf(" %s", cp);
E 18
I 18
D 26
	(void)printf(" %s", cp);
E 26
I 26
	printf(" %s", cp);
E 26
E 18
E 7
}
D 6
		
char *
E 6
I 6

D 7
static char *
E 6
emalloc(size)
I 6
	int size;
E 7
I 7
D 23
static
readf()
E 7
E 6
{
D 6
	char *cp;
	cp = (char *)malloc(size);
	if (cp < 0) {
		fprintf(stderr,"Out of space.\n");
E 6
I 6
D 7
	char *cp, *malloc();

	if (!(cp = (char *)malloc((u_int)size))) {
		fprintf(stderr, "fstat: out of space.\n");
E 6
		exit(1);
	}
	return(cp);
}

D 6
struct  file  *
E 6
I 6
static struct file *
E 6
getf()
{
D 6
	int	i;
	struct file	file;
E 6
I 6
	int i;
E 7
	struct file lfile;
I 7
	int i;
E 7
E 6

D 6
	itrans(DTYPE_INODE, u.u_cdir, WD);
E 6
I 6
D 20
	itrans(DTYPE_INODE, user.user.u_cdir, WD);
E 20
I 20
	vtrans(DTYPE_VNODE, user.user.u_cdir, WD);
E 20
E 6
	for (i = 0; i < NOFILE; i++) {
D 6
		if (u.u_ofile[i] == 0)
E 6
I 6
		if (user.user.u_ofile[i] == 0)
E 6
			continue;
D 6
		lseek(kmem, (long) u.u_ofile[i], 0);
		if (read(kmem, (char *) &file, sizeof(file)) != sizeof(file)) {
E 6
I 6
		(void)lseek(kmem, (off_t)user.user.u_ofile[i], L_SET);
		if (read(kmem, (char *)&lfile, sizeof(lfile))
		    != sizeof(lfile)) {
E 6
D 7
			cantread("file", kmemf);
E 7
I 7
D 11
			cantread("file", N_KMEM);
E 11
I 11
D 17
			rerr1("file", N_KMEM);
E 17
I 17
			rerr1("file", _PATH_KMEM);
E 17
E 11
E 7
			continue;
		}
D 6
		/*printf("flag: %x count: %x ",file.f_flag, file.f_count);
		/*fflush(stdout);
		 */
		itrans(file.f_type, file.f_data, i); 
E 6
I 6
D 20
		itrans(lfile.f_type, (struct inode *)lfile.f_data, i);
E 20
I 20
		vtrans(lfile.f_type, (struct vnode *)lfile.f_data, i);
E 20
E 6
	}
}

I 6
static
E 6
D 7
usage()
E 7
I 7
D 9
devmatch(idev, inum)
E 9
I 9
devmatch(idev, inum, name)
E 9
	dev_t idev;
	ino_t inum;
I 9
	char  **name;
E 9
E 7
{
D 6
	fputs("usage: fstat [-u user] [-f filename] [-p pid]\n", stderr);
E 6
I 6
D 7
	fputs("usage: fstat [-v] [-u user] [-p pid] [filename ...]\n", stderr);
E 6
	exit(1);
}
E 7
I 7
	register DEVS *d;
E 7

D 6
getuname(uname)
char	*uname;
E 6
I 6
D 7
static
getuname(arg_uname)
	char *arg_uname;
E 6
{
D 6
	struct passwd	*passwd, *getpwnam();
	
	if ((passwd = getpwnam(uname)) == NULL)
		return(-1);
	return(passwd->pw_uid);
E 6
I 6
	struct passwd *passwd, *getpwnam();

	return((passwd = getpwnam(arg_uname)) ? passwd->pw_uid : -1);
E 7
I 7
	for (d = devs; d; d = d->next)
D 9
		if (d->dev == idev && (!d->inum || d->inum == inum))
E 9
I 9
		if (d->dev == idev && (d->inum == 0 || d->inum == inum)) {
			*name = d->name;
E 9
			return(1);
I 9
		}
E 9
	return(0);
E 7
E 6
}

I 6
static
E 23
E 6
getfname(filename)
D 6
char	*filename;
E 6
I 6
	char *filename;
E 6
{
D 7
	struct	stat statbuf;
I 3
	struct devs *d, *oldd;
	dev_t dev;
	int inum;
E 7
I 7
	struct stat statbuf;
	DEVS *cur;
D 31
	char *malloc();
E 31
E 7
E 3

D 6
	if (stat(filename, &statbuf) != 0)
		return(-1);
E 6
I 6
	if (stat(filename, &statbuf)) {
D 17
		perror(filename);
E 17
I 17
D 18
		fprintf(stderr, "fstat: %s: %s\n", strerror(errno), filename);
E 18
I 18
D 26
		(void)fprintf(stderr, "fstat: %s: %s\n", strerror(errno),
E 26
I 26
D 43
		fprintf(stderr, "fstat: %s: %s\n", strerror(errno),
E 26
		    filename);
E 43
I 43
		fprintf(stderr, "fstat: %s: %s\n", filename, strerror(errno));
E 43
E 18
E 17
D 10
		exit(1);
E 10
I 10
		return(0);
E 10
	}
I 7
D 31
	if ((cur = (DEVS *)malloc(sizeof(DEVS))) == NULL) {
D 18
		fprintf(stderr, "fstat: out of space.\n");
E 18
I 18
D 26
		(void)fprintf(stderr, "fstat: out of space.\n");
E 26
I 26
		fprintf(stderr, "fstat: out of space.\n");
E 31
I 31
	if ((cur = malloc(sizeof(DEVS))) == NULL) {
		fprintf(stderr, "fstat: %s\n", strerror(errno));
E 31
E 26
E 18
		exit(1);
	}
	cur->next = devs;
	devs = cur;
E 7
E 6

D 7
	/*
D 6
	 *	if file is block special, look for open files on it
E 6
I 6
	 * if file is block special, look for open files on it
E 6
	 */
E 7
I 7
D 23
	/* if file is block special, look for open files on it */
E 7
	if ((statbuf.st_mode & S_IFMT) != S_IFBLK) {
D 7
		inum = statbuf.st_ino;
D 3
		return(statbuf.st_dev);
E 3
I 3
		dev = statbuf.st_dev;
E 7
I 7
		cur->inum = statbuf.st_ino;
		cur->dev = statbuf.st_dev;
E 7
E 3
D 6
	} else {
E 6
I 6
	}
	else {
E 6
D 3
		special++;
E 3
D 7
		inum = 0;
D 3
		return(statbuf.st_rdev);
E 3
I 3
		dev = statbuf.st_rdev;
E 7
I 7
		cur->inum = 0;
		cur->dev = statbuf.st_rdev;
E 7
E 3
	}
E 23
I 23
	cur->ino = statbuf.st_ino;
D 26
	cur->dev = statbuf.st_dev;
E 26
I 26
	cur->fsid = statbuf.st_dev & 0xffff;
E 26
E 23
I 9
	cur->name = filename;
I 10
	return(1);
E 10
E 9
I 3
D 7
	for (d = oldd = &devs; d; oldd = d, d = d->next)
		;
	d = (struct devs *)emalloc(sizeof(struct devs));
	oldd->next = d;
D 6
	d->next = 0;
E 6
I 6
	d->next = NULL;
E 6
	d->dev = dev;
	d->inum = inum;
E 7
I 7
}

I 31
void
E 31
D 23
static
openfiles()
{
D 17
	if ((kmem = open(N_KMEM, O_RDONLY, 0)) < 0) {
		perror(N_KMEM);
E 17
I 17
	if ((kmem = open(_PATH_KMEM, O_RDONLY, 0)) < 0) {
		(void)fprintf(stderr, "fstat: %s: %s\n",
		    strerror(errno), _PATH_KMEM);
E 17
		exit(1);
	}
D 17
	if ((mem = open(N_MEM, O_RDONLY, 0)) < 0) {
		perror(N_MEM);
E 17
I 17
	if ((mem = open(_PATH_MEM, O_RDONLY, 0)) < 0) {
		(void)fprintf(stderr, "fstat: %s: %s\n",
		    strerror(errno), _PATH_MEM);
E 17
		exit(1);
	}
D 17
	if ((swap = open(N_SWAP, O_RDONLY, 0)) < 0) {
		perror(N_SWAP);
E 17
I 17
D 19
	if ((swap = open(_PATH_SWAP, O_RDONLY, 0)) < 0) {
E 19
I 19
	if ((swap = open(_PATH_DRUM, O_RDONLY, 0)) < 0) {
E 19
		(void)fprintf(stderr, "fstat: %s: %s\n",
D 19
		    strerror(errno), _PATH_SWAP);
E 19
I 19
		    strerror(errno), _PATH_DRUM);
E 19
E 17
		exit(1);
	}
}

static
D 11
cantread(what, fromwhat)
E 11
I 11
rerr1(what, fromwhat)
E 11
	char *what, *fromwhat;
{
D 11
	vprintf("fstat: error reading %s from %s", what, fromwhat);
E 11
I 11
D 18
	if (vflg)
D 17
		printf("fstat: error reading %s from %s", what, fromwhat);
E 17
I 17
		printf("error reading %s from %s", what, fromwhat);
E 18
I 18
	VP("error reading %s from %s", what, fromwhat);
E 18
E 17
E 11
}

I 11
static
D 18
rerr2(err, address, what)
	int err, address;
E 18
I 18
rerr2(address, what)
	int address;
E 18
	char *what;
{
D 18
	if (vflg)
D 17
		printf("error %d reading %s at %x from kmem\n", errno, what, address);
E 17
I 17
		printf("error %d reading %s at %x from %s\n",
		    errno, what, address, _PATH_KMEM);
E 18
I 18
	VP("error %d reading %s at %x from %s\n", errno, what, address,
	    _PATH_KMEM);
E 18
E 17
}

E 11
static long
lgetw(loc)
	off_t loc;
{
	long word;

	(void)lseek(kmem, (off_t)loc, L_SET);
D 11
	if (read(kmem, (char *) &word, sizeof(word)) != sizeof(word))
		vprintf("error reading kmem at %lx\n", loc);
E 11
I 11
	if (read(kmem, (char *)&word, sizeof(word)) != sizeof(word))
D 18
		rerr2(errno, (int)loc, "word");
E 18
I 18
		rerr2((int)loc, "word");
E 18
E 11
	return(word);
}

static
E 23
usage()
{
D 16
	fputs("usage: fstat [-v] [-u user] [-p pid] [filename ...]\n", stderr);
E 16
I 16
D 18
	fputs("usage: fstat [-u user] [-p pid] [filename ...]\n", stderr);
E 18
I 18
	(void)fprintf(stderr,
D 27
	    "usage: fstat [-u user] [-p pid] [filename ...]\n");
E 27
I 27
D 32
	    "usage: fstat [-fnv] [-p pid] [-u user] [filename ...]\n");
E 32
I 32
 "usage: fstat [-fnv] [-p pid] [-u user] [-N system] [-M core] [file ...]\n");
E 32
E 27
E 18
E 16
	exit(1);
E 7
E 3
D 6
}

Atoi(p)
register char *p;
{
	register int n = 0;

	while(*p >= '0' && *p <= '9')
		n = n*10 + *p++ - '0';
	return(*p ? -n : n);
}

klseek(fd, loc, off)
	int fd;
	long loc;
	int off;
{
	static int	sizeSysmap;

	if( kflg && Sysmap == 0)
		{/* initialize Sysmap */

		sizeSysmap = nl[SSYSSIZE].n_value * sizeof( struct pte);
		Sysmap = (struct pte *)calloc( sizeSysmap, 1);
		lseek( kmem, clear( nl[SSYSMAP].n_value), 0);
		if( read( kmem, Sysmap, sizeSysmap) != sizeSysmap)
			{
			printf( "Cant read system page table\n");
			exit(1);
			}
		}
	if( kflg && (loc&0x80000000))
		{/* do mapping for kernel virtual addresses */
		struct pte *ptep;

		loc &= 0x7fffffff;
		ptep = &Sysmap[btop(loc)];
		if( (char *)ptep - (char *)Sysmap > sizeSysmap)
			{
			printf( "no system pte for %s\n", loc);
			exit(1);
			}
		if( ptep->pg_v == 0)
			{
			printf( "system pte invalid for %x\n", loc);
			exit(1);
			}
		loc = (off_t)((loc&PGOFSET) + ptob(ptep->pg_pfnum));
		}
	(void) lseek(fd, (long)loc, off);
E 6
}
E 1
