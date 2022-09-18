h16669
s 00001/00000/00143
d D 8.7 95/03/29 00:35:27 mckusick 80 79
c add einval function
e
s 00004/00001/00139
d D 8.6 95/02/19 07:47:56 cgd 79 78
c sysent struct also include argument size.  define SCARG macro.
e
s 00001/00000/00139
d D 8.5 95/01/09 18:16:27 cgd 78 77
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00002/00002/00137
d D 8.4 94/02/23 06:34:36 bostic 77 76
c first argument of bcopy is a const
e
s 00005/00000/00134
d D 8.3 94/01/21 17:25:20 bostic 76 75
c add USL's copyright notice
e
s 00001/00001/00133
d D 8.2 93/09/03 16:10:26 mckusick 75 74
c curpri => more descriptive curpriority
e
s 00000/00000/00134
d D 8.1 93/06/11 00:45:56 bostic 74 73
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00132
d D 7.28 93/06/02 19:57:17 bostic 73 71
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00129
d R 8.1 93/06/02 19:55:42 bostic 72 71
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00028/00001/00106
d D 7.27 93/03/03 15:04:17 mckusick 71 70
c add comment describing secure levels
e
s 00001/00000/00106
d D 7.26 93/02/28 23:24:00 mckusick 70 69
c add securelevel
e
s 00001/00000/00105
d D 7.25 92/07/19 23:42:12 mckusick 69 68
c add prototype for hashinit
e
s 00016/00000/00089
d D 7.24 92/07/08 00:45:20 torek 68 67
c add some time related prototypes
e
s 00001/00006/00088
d D 7.23 92/06/21 10:36:29 bostic 67 66
c libkern has its own include file with prototypes
e
s 00001/00001/00093
d D 7.22 92/06/19 22:55:53 mckusick 66 65
c GCC 2.X grot
e
s 00001/00001/00093
d D 7.21 92/05/27 07:12:32 bostic 65 64
c strlen returns a size_t
e
s 00000/00003/00094
d D 7.20 92/03/01 20:57:59 ralph 64 63
c remove unused KADB external decl.
e
s 00005/00001/00092
d D 7.19 92/02/05 19:25:57 torek 63 62
c fix up prototypes
e
s 00002/00002/00091
d D 7.18 91/11/01 16:31:23 bostic 62 61
c make panic take printf(3) style arguments
e
s 00001/00000/00092
d D 7.17 91/05/25 15:33:17 bostic 61 60
c add sprintf to kern/subr_prf.c
e
s 00000/00002/00092
d D 7.16 91/05/07 09:45:17 hibler 60 59
c get rid of kmapwnt
e
s 00019/00026/00075
d D 7.15 91/05/06 11:08:08 karels 59 58
c prettiness patrol II: I like function grouping better than alphabetical;
c remove intstack, argdev, icode, other old/grotty stuff
e
s 00051/00058/00050
d D 7.14 91/05/05 17:44:39 bostic 58 57
c The prettiness patrol...
e
s 00035/00004/00073
d D 7.13 91/05/04 19:57:11 karels 57 56
c add prototypes for locore, etc
e
s 00002/00006/00075
d D 7.12 91/04/20 11:20:44 karels 56 55
c rm unused; add enoioctl
e
s 00011/00010/00070
d D 7.11 91/03/17 15:34:11 karels 55 54
c more-or-less working with new proc & user structs
e
s 00001/00001/00079
d D 7.10 91/01/09 19:37:23 william 54 53
c trivial 386 ifdefs added
e
s 00001/00001/00079
d D 7.9 90/12/05 15:52:30 mckusick 53 52
c update for new VM
e
s 00001/00001/00079
d D 7.8 90/05/10 12:42:21 mckusick 52 51
c merge in support for hp300
e
s 00003/00004/00077
d D 7.7 89/05/09 16:13:58 mckusick 51 50
c merge in vnodes
e
s 00002/00001/00079
d D 7.6 88/05/26 09:02:36 karels 50 49
c lint
e
s 00000/00001/00080
d D 7.5 87/06/06 15:11:13 mckusick 49 48
c calloc is gone
e
s 00002/00007/00079
d D 7.4 87/01/08 12:08:30 bostic 48 47
c comment fix
e
s 00001/00000/00085
d D 7.3 86/11/25 16:40:55 sam 47 46
c kdb additions
e
s 00001/00001/00084
d D 7.2 86/10/13 23:02:24 karels 46 45
c merge in tahoe system
e
s 00001/00001/00084
d D 7.1 86/06/04 23:28:50 mckusick 45 44
c 4.3BSD release version
e
s 00000/00003/00085
d D 6.5 86/02/23 23:01:03 karels 44 43
c lint
e
s 00000/00002/00088
d D 6.4 86/01/05 18:28:59 mckusick 43 42
c get rid of unused queue() and dequeue() (from sun!shannon)
e
s 00007/00001/00083
d D 6.3 85/06/08 15:09:04 mckusick 42 41
c Add copyright
e
s 00000/00001/00084
d D 6.2 85/03/01 17:57:16 karels 41 40
c hand not global now
e
s 00000/00000/00085
d D 6.1 83/07/29 06:14:12 sam 40 39
c 4.2 distribution
e
s 00000/00004/00085
d D 4.35 83/05/22 17:22:22 sam 39 38
c purge mush; make quota's permanent
e
s 00000/00001/00089
d D 4.34 83/03/31 18:16:57 sam 38 37
c getmdev no more dev_t
e
s 00000/00001/00090
d D 4.33 83/02/10 16:09:29 sam 37 36
c hz already defined in kernel.h
e
s 00003/00002/00088
d D 4.32 82/11/15 12:30:12 sam 36 35
c extern's added for fsck
e
s 00002/00002/00088
d D 4.31 82/10/31 16:36:13 root 35 34
c drop umbabeg,end and catcher
e
s 00002/00000/00088
d D 4.30 82/10/20 01:57:09 root 34 33
c lint
e
s 00000/00003/00088
d D 4.29 82/10/20 01:16:27 root 33 32
c lint
e
s 00000/00000/00091
d D 4.28 82/09/08 08:11:50 root 32 31
c label_t now a structure; other misc changes
e
s 00000/00001/00091
d D 4.27 82/09/06 23:01:25 root 31 30
c more timer stuff
e
s 00000/00003/00092
d D 4.26 82/09/04 09:29:20 root 30 29
c being breakup into kernel.h sanely
e
s 00002/00000/00093
d D 4.25 82/07/16 17:05:18 kre 29 28
c added defn of mcode (&szmcode) - /etc/mush startup code
e
s 00001/00003/00092
d D 4.24 82/06/14 22:54:38 root 28 27
c declare wmemall
e
s 00001/00000/00094
d D 4.23 82/06/07 22:07:51 mckusick 27 26
c calculate size for read ahead block
e
s 00002/00000/00092
d D 4.22 81/11/26 11:54:24 wnj 26 25
c before carry to arpavax
e
s 00002/00000/00090
d D 4.21 81/11/20 14:28:00 wnj 25 24
c more lint
e
s 00000/00001/00090
d D 4.20 81/11/18 15:47:09 wnj 24 23
c more cleanup
e
s 00005/00001/00086
d D 4.19 81/11/16 14:24:55 wnj 23 22
c more lint
e
s 00001/00000/00086
d D 4.18 81/10/17 16:14:35 wnj 22 21
c cleanup (mpx removal, old tty removal, beginnings of select)
e
s 00001/00000/00085
d D 4.17 81/05/05 21:54:44 wnj 21 20
c add global boothowto, the reboot flags from console subsystem
e
s 00001/00000/00084
d D 4.16 81/04/28 03:02:09 root 20 19
c char *wmemall
e
s 00001/00000/00083
d D 4.15 81/04/18 11:33:36 wnj 19 18
c add variable for communications between swap and wakeup
e
s 00000/00003/00083
d D 4.14 81/03/09 00:27:27 wnj 18 17
c lint
e
s 00001/00000/00085
d D 4.13 81/02/28 18:01:33 wnj 17 16
c fixups for rm* routines
e
s 00003/00000/00082
d D 4.12 81/02/27 00:03:43 wnj 16 15
c add hz, timezone and dstflag
e
s 00001/00001/00081
d D 4.11 81/02/19 21:42:17 wnj 15 14
c %G%->%E%
e
s 00001/00000/00081
d D 4.10 81/02/19 21:30:33 wnj 14 13
c added catcher
e
s 00001/00001/00080
d D 4.9 81/02/19 11:52:02 wnj 13 12
c dont specify size of intstack
e
s 00000/00002/00081
d D 4.8 81/02/15 12:14:17 wnj 12 11
c bootable autoconf version
e
s 00001/00001/00082
d D 4.7 81/02/08 18:38:35 wnj 11 10
c cpusid->cpu
e
s 00001/00002/00082
d D 4.6 81/02/08 01:30:01 wnj 10 9
c misc
e
s 00001/00000/00083
d D 4.5 81/02/07 15:55:07 wnj 9 8
c 
e
s 00003/00001/00080
d D 4.4 81/02/04 01:34:40 wnj 8 7
c added dumpdev dumplo
e
s 00001/00001/00080
d D 4.3 81/01/26 22:32:05 kre 7 6
c added defn of 'schar()' as external fn
e
s 00000/00001/00081
d D 4.2 81/01/15 19:40:09 wnj 6 5
c remove msgbuf declaration
e
s 00000/00000/00082
d D 4.1 80/11/09 17:01:44 bill 5 4
c stamp for 4bsd
e
s 00002/00010/00080
d D 3.4 80/07/01 08:17:09 bill 4 3
c various minor fixups pre-split to dev dir
e
s 00001/00001/00089
d D 3.3 80/06/07 03:00:54 bill 3 2
c %H%->%G%
e
s 00001/00001/00089
d D 3.2 80/05/03 17:20:22 bill 2 1
c speeling error
e
s 00090/00000/00000
d D 3.1 80/04/09 16:25:25 bill 1 0
c date and time created 80/04/09 16:25:25 by bill
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%H%	*/
E 3
I 3
D 15
/*	%M%	%I%	%G%	*/
E 15
I 15
D 42
/*	%M%	%I%	%E%	*/
E 42
I 42
D 58
/*
D 45
 * Copyright (c) 1982 Regents of the University of California.
E 45
I 45
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 45
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 58
I 58
/*-
D 73
 * Copyright (c) 1982, 1988, 1991 The Regents of the University of California.
 * All rights reserved.
E 73
I 73
 * Copyright (c) 1982, 1988, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
I 76
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 76
E 73
E 58
 *
I 58
 * %sccs.include.redist.c%
 *
E 58
 *	%W% (Berkeley) %G%
 */
E 42
E 15
E 3

I 71
/*
 * The `securelevel' variable controls the security level of the system.
 * It can only be decreased by process 1 (/sbin/init).
 *
 * Security levels are as follows:
 *   -1	permannently insecure mode - always run system in level 0 mode.
 *    0	insecure mode - immutable and append-only flags make be turned off.
 *	All devices may be read or written subject to permission modes.
 *    1	secure mode - immutable and append-only flags may not be changed;
 *	raw disks of mounted filesystems, /dev/mem, and /dev/kmem are
 *	read-only.
 *    2	highly secure mode - same as (1) plus raw disks are always
 *	read-only whether mounted or not. This level precludes tampering 
 *	with filesystems by unmounting them, but also inhibits running
 *	newfs while the system is secured.
 *
 * In normal operation, the system runs in level 0 mode while single user
 * and in level 1 mode while multiuser. If level 2 mode is desired while
 * running multiuser, it can be set in the multiuser startup script
 * (/etc/rc.local) using sysctl(1). If it is desired to run the system
 * in level 0 mode while multiuser, initialize the variable securelevel
 * in /sys/kern/kern_sysctl.c to -1. Note that it is NOT initialized to
 * zero as that would allow the vmunix binary to be patched to -1.
 * Without initialization, securelevel loads in the BSS area which only
 * comes into existence when the kernel is loaded and hence cannot be
 * patched by a stalking hacker.
 */
extern int securelevel;		/* system security level */
E 71
D 58
/*
D 56
 * Random set of variables
 * used by more than one
 * routine.
E 56
I 56
 * Random set of variables used by more than one routine.
E 56
 */
I 16
D 37
int	hz;			/* frequency of the clock */
E 37
D 33
int	timezone;		/* minutes west from greenwich */
int	dstflag;		/* daylight savings time in effect? */
E 33
E 16
D 24
char	canonb[CANBSIZ];	/* buffer for erase and kill (#@) */
E 24
D 11
int	cpusid;			/* cpu SID register */
E 11
I 11
D 12
int	cpu;			/* cpu SID register */
E 12
E 11
D 36
char	version[];		/* system version */
E 36
D 31
int	lbolt;			/* time of day in 60th not in time */
E 31
D 30
time_t	time;			/* time in sec from 1970 */
time_t	bootime;		/* time at which booted */

E 30
D 41
int	hand;			/* current index into coremap used by daemon */
E 41
I 36
extern	char version[];		/* system version */
E 58
I 58
D 62
extern char *panicstr;		/* panic message */
E 62
I 62
extern const char *panicstr;	/* panic message */
E 62
D 59
extern char *version;		/* system version */
E 59
I 59
extern char version[];		/* system version */
extern char copyright[];	/* system copyright */
I 70
D 71
extern int securelevel;		/* system security level */
E 71
E 70
E 59
E 58
E 36

D 58
/*
D 48
 * Nblkdev is the number of entries
 * (rows) in the block switch. It is
 * set in binit/bio.c by making
 * a pass over the switch.
 * Used in bounds checking on major
 * device numbers.
E 48
I 48
 * Nblkdev is the number of entries (rows) in the block switch.
 * Used in bounds checking on major device numbers.
E 48
 */
int	nblkdev;
E 58
I 58
extern int nblkdev;		/* number of entries in bdevsw */
extern int nchrdev;		/* number of entries in cdevsw */
extern int nswdev;		/* number of swap devices */
extern int nswap;		/* size of swap space */
E 58

D 58
/*
 * Number of character switch entries.
D 2
 * Set by cinit/tty.c
E 2
I 2
D 48
 * Set by cinit/prim.c
E 48
E 2
 */
int	nchrdev;
E 58
I 58
extern int selwait;		/* select timeout address */
E 58

I 4
D 58
int	nswdev;			/* number of swap devices */
E 4
D 55
int	mpid;			/* generic for unique process id's */
char	runin;			/* scheduling flag */
char	runout;			/* scheduling flag */
int	runrun;			/* scheduling flag */
E 55
char	kmapwnt;		/* kernel map want flag */
D 55
char	curpri;			/* more scheduling */
E 55
I 55
u_char	curpri;			/* priority of current process */
E 58
I 58
D 60
extern char kmapwnt;		/* kernel map want flag */
E 58
E 55

E 60
D 58
int	maxmem;			/* actual max memory per process */
int	physmem;		/* physical memory on this CPU */
E 58
I 58
D 75
extern u_char curpri;		/* priority of current process */
E 75
I 75
extern u_char curpriority;	/* priority of current process */
E 75
E 58

D 4
daddr_t	swplo;			/* block number of swap space */
E 4
D 58
int	nswap;			/* size of swap space */
D 51
int	updlock;		/* lock for sync */
daddr_t	rablock;		/* block to be read ahead */
I 27
int	rasize;			/* size of block in rablock */
E 51
E 27
D 6
char	msgbuf[MSGBUFS];	/* saved "printf" characters */
E 6
D 13
int	intstack[512];		/* stack for interrupts */
E 13
I 13
extern	int intstack[];		/* stack for interrupts */
E 13
dev_t	rootdev;		/* device of the root */
I 51
struct	vnode *rootvp;		/* vnode of root filesystem */
E 51
I 8
dev_t	dumpdev;		/* device to take dumps on */
long	dumplo;			/* offset into dumpdev */
E 8
dev_t	swapdev;		/* swapping device */
I 51
struct	vnode *swapdev_vp;	/* vnode equivalent to above */
E 51
I 4
D 8
dev_t	argdev;
E 8
I 8
dev_t	argdev;			/* device for argument lists */
I 51
struct	vnode *argdev_vp;	/* vnode equivalent to above */
E 58
I 58
extern int maxmem;		/* max memory per process */
extern int physmem;		/* physical memory */
E 58
E 51
E 8
E 4
D 33
dev_t	pipedev;		/* pipe device */
E 33

I 35
D 46
#ifdef vax
E 46
I 46
D 52
#if defined(vax) || defined(tahoe)
E 52
I 52
D 54
#if defined(vax) || defined(tahoe) || defined(hp300)
E 54
I 54
D 55
#if defined(vax) || defined(tahoe) || defined(hp300) || defined(i386)
E 55
E 54
E 52
E 46
E 35
D 58
extern	int icode[];		/* user init code */
extern	int szicode;		/* its size */
E 58
I 58
D 59
extern int intstack[];		/* interrupt stack */
E 58
I 35
D 55
#endif
E 55
E 35
I 34
D 39
#ifdef MUSH
E 34
I 29
extern	int mcode[];		/* MUSH: startup code */
extern	int szmcode;		/* & its size */
I 34
#endif
E 39
E 34
E 29

D 18
extern	int printsw;		/* debug print switch */
extern	int coresw;		/* switch to force action on core dumps */

E 18
D 38
dev_t	getmdev();
E 38
D 51
daddr_t	bmap();
E 51
I 9
D 49
caddr_t	calloc();
E 49
E 9
D 44
unsigned max();
unsigned min();
E 44
D 57
int	memall();
D 7
int	uchar();
E 7
I 7
D 44
int	uchar(), schar();
E 44
E 7
int	vmemall();
I 25
D 28
#if 0
E 25
I 20
char	*wmemall();
I 25
#endif
E 28
I 28
D 50
caddr_t	wmemall();
E 50
E 28
E 25
E 20
swblk_t	vtod();
D 4
/*
 * Instrumentation
 */
int	dk_busy;
long	dk_time[32];
long	dk_numb[3];
long	dk_wds[3];
long	tk_nin;
long	tk_nout;
E 4

E 57
D 58
/*
 * Structure of the system-entry table
 */
D 55
extern struct sysent
{
E 55
I 55
extern struct sysent {
E 55
D 10
	char	sy_narg;		/* total number of arguments */
	char	sy_nrarg;		/* number of args in registers */
E 10
I 10
	int	sy_narg;		/* total number of arguments */
E 10
	int	(*sy_call)();		/* handler */
E 58
I 58
extern int icode[];		/* user init code */
extern int szicode;		/* size of icode */

E 59
extern dev_t dumpdev;		/* dump device */
extern long dumplo;		/* offset into dumpdev */

extern dev_t rootdev;		/* root device */
extern struct vnode *rootvp;	/* vnode equivalent to above */

extern dev_t swapdev;		/* swapping device */
extern struct vnode *swapdev_vp;/* vnode equivalent to above */

D 59
extern dev_t argdev;		/* argument lists device */
extern struct vnode *argdev_vp;	/* vnode equivalent to above */

E 59
extern struct sysent {		/* system call table */
D 59
	int sy_narg;		/* number of arguments */
	int (*sy_call)();	/* implementing function */
E 59
I 59
D 79
	int	sy_narg;	/* number of arguments */
E 79
I 79
	short	sy_narg;	/* number of args */
	short	sy_argsize;	/* total size of arguments */
E 79
	int	(*sy_call)();	/* implementing function */
E 59
E 58
} sysent[];
I 79
extern int nsysent;
#define	SCARG(p,k)	((p)->k.datum)	/* get arg from args pointer */
E 79

I 59
extern int boothowto;		/* reboot flags, from console subsystem */
E 59
D 36
char	vmmap[];		/* poor name! */
E 36
D 12
int	mcr[3];			/* memory controller registers */
E 12
D 35
int	umbabeg,umbaend;	/* where sensitive vm begins/ends */
E 35
D 56
int	noproc;			/* no one is running just now */
E 56
I 14
D 35
extern	int catcher[256];
E 35
I 17
D 58
char	*panicstr;
I 19
D 55
int	wantin;
E 55
I 21
int	boothowto;		/* reboot flags, from console subsystem */
E 58
I 50
D 64
#ifdef	KADB
E 50
I 47
D 58
char	*bootesym;		/* end of symbol info from boot */
E 58
I 58
extern char *bootesym;		/* end of symbol info from boot */
E 58
I 50
#endif
E 64
E 50
E 47
I 22
D 23
int	select();
E 23
I 23
D 58
int	selwait;
E 58
I 58
D 59
extern int boothowto;		/* reboot flags, from console subsystem */
E 59
E 58
I 36

D 53
extern	char vmmap[];		/* poor name! */
E 53
I 53
D 56
extern	char *vmmap;		/* poor name! */
E 53
E 36

E 56
/* casts to keep lint happy */
#define	insque(q,p)	_insque((caddr_t)q,(caddr_t)p)
#define	remque(q)	_remque((caddr_t)q)
I 55

/*
D 58
 * General function declarations
E 58
I 58
D 59
 * General function prototypes.
E 59
I 59
 * General function declarations.
E 59
E 58
 */
I 59
int	nullop __P((void));
E 59
D 58
int	nullop __P((void));
E 58
int	enodev __P((void));
I 56
int	enoioctl __P((void));
E 56
int	enxio __P((void));
int	eopnotsupp __P((void));
I 80
int	einval __P((void));
E 80
I 58
D 59
int	nullop __P((void));
E 59
E 58
int	seltrue __P((dev_t dev, int which, struct proc *p));
I 69
void	*hashinit __P((int count, int type, u_long *hashmask));
I 78
int	nosys __P((struct proc *, void *, register_t *));
E 78
E 69
I 57

I 63
#ifdef __GNUC__
volatile void	panic __P((const char *, ...));
#else
E 63
I 59
D 62
void	panic __P((char *));
E 62
I 62
void	panic __P((const char *, ...));
E 62
D 63
void	tablefull __P((char *));
E 63
I 63
#endif
void	tablefull __P((const char *));
E 63
E 59
D 58
void	panic __P((char *));
void	tablefull __P((char *));
E 58
void	addlog __P((const char *, ...));
void	log __P((int, const char *, ...));
I 58
D 59
void	panic __P((char *));
E 59
E 58
void	printf __P((const char *, ...));
I 61
int	sprintf __P((char *buf, const char *, ...));
E 61
I 58
D 59
void	tablefull __P((char *));
E 59
E 58
void	ttyprintf __P((struct tty *, const char *, ...));

I 58
D 59
int	bcmp __P((void *str1, void *str2, u_int len));
E 59
E 58
D 77
void	bcopy __P((void *from, void *to, u_int len));
D 58
void	ovbcopy __P((void *from, void *to, u_int len));
E 58
D 59
void	bzero __P((void *buf, u_int len));
E 59
D 58
int	bcmp __P((void *str1, void *str2, u_int len));
E 58
I 58
void	ovbcopy __P((void *from, void *to, u_int len));
E 77
I 77
void	bcopy __P((const void *from, void *to, u_int len));
void	ovbcopy __P((const void *from, void *to, u_int len));
E 77
I 59
void	bzero __P((void *buf, u_int len));
D 67
int	bcmp __P((void *str1, void *str2, u_int len));
E 59
E 58
D 65
int	strlen __P((char *string));
E 65
I 65
D 66
size_t	strlen __P((char *string));
E 66
I 66
size_t	strlen __P((const char *string));
E 67
E 66
E 65

D 58
int	copystr __P((void *kfaddr, void *kdaddr, u_int len, u_int *done));
int	copyinstr __P((void *udaddr, void *kaddr, u_int len, u_int *done));
int	copyoutstr __P((void *kaddr, void *udaddr, u_int len, u_int *done));
E 58
D 59
int	copyin __P((void *udaddr, void *kaddr, u_int len));
E 59
I 59
int	copystr __P((void *kfaddr, void *kdaddr, u_int len, u_int *done));
E 59
I 58
int	copyinstr __P((void *udaddr, void *kaddr, u_int len, u_int *done));
E 58
D 59
int	copyout __P((void *kaddr, void *udaddr, u_int len));
E 59
I 58
int	copyoutstr __P((void *kaddr, void *udaddr, u_int len, u_int *done));
D 59
int	copystr __P((void *kfaddr, void *kdaddr, u_int len, u_int *done));
E 59
I 59
int	copyin __P((void *udaddr, void *kaddr, u_int len));
int	copyout __P((void *kaddr, void *udaddr, u_int len));
E 59
E 58

int	fubyte __P((void *base));
#ifdef notdef
int	fuibyte __P((void *base));
#endif
I 58
D 59
int	fuiword __P((void *base));
int	fuword __P((void *base));
E 59
E 58
int	subyte __P((void *base, int byte));
int	suibyte __P((void *base, int byte));
D 58
int	fuword __P((void *base));
int	fuiword __P((void *base));
int	suword __P((void *base, int word));
E 58
D 59
int	suiword __P((void *base, int word));
E 59
I 59
int	fuword __P((void *base));
int	fuiword __P((void *base));
E 59
I 58
int	suword __P((void *base, int word));
I 59
int	suiword __P((void *base, int word));
E 59
E 58

I 68
int	hzto __P((struct timeval *tv));
void	timeout __P((void (*func)(void *), void *arg, int ticks));
void	untimeout __P((void (*func)(void *), void *arg));
void	realitexpire __P((void *));

struct clockframe;
void	hardclock __P((struct clockframe *frame));
void	softclock __P((void));
void	statclock __P((struct clockframe *frame));

void	initclocks __P((void));

void	startprofclock __P((struct proc *));
void	stopprofclock __P((struct proc *));
void	setstatclockrate __P((int hzrate));

E 68
I 58
D 59
int	ffs __P((long value));
int	locc __P((int mask, char *cp, unsigned size));
E 59
E 58
D 67
int	scanc __P((unsigned size, u_char *cp, u_char *table, int mask));
int	skpc __P((int mask, int size, char *cp));
I 59
int	locc __P((int mask, char *cp, unsigned size));
int	ffs __P((long value));
E 67
I 67
#include <libkern/libkern.h>
E 67
E 59
D 58
int	locc __P((int mask, char *cp, unsigned size));
int	ffs __P((long value));
E 58
E 57
E 55
I 26
D 43
#define	queue(q,p)	_queue((caddr_t)q,(caddr_t)p)
#define	dequeue(q)	_dequeue((caddr_t)q)
E 43
E 26
E 23
E 22
E 21
E 19
E 17
E 14
E 1
