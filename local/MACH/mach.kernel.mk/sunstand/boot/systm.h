/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	systm.h,v $
 * Revision 2.2  89/07/12  00:11:59  jjc
 * 	     Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*      @(#)systm.h 2.13 88/02/08 SMI; from UCB 4.35 83/05/22      */

/*
 * Random set of variables
 * used by more than one
 * routine.
 */
int	hand;			/* current index into coremap used by daemon */
extern	char version[];		/* system version */

#undef  NGROUPS
#define NGROUPS	8

/*
 * Nblkdev is the number of entries
 * (rows) in the block switch.
 * Used in bounds checking on major
 * device numbers.
 */
int	nblkdev;

/*
 * Number of character switch entries.
 */
int	nchrdev;

int	nswdev;			/* number of swap devices */
int	mpid;			/* generic for unique process id's */
char	runin;			/* scheduling flag */
char	runout;			/* scheduling flag */
int	runrun;			/* scheduling flag */
char	curpri;			/* more scheduling */

int	maxmem;			/* actual max memory per process */
int	physmem;		/* physical memory on this CPU */

int	nswap;			/* size of swap space */
int	updlock;		/* lock for sync */
daddr_t	rablock;		/* block to be read ahead */
int	rasize;			/* size of block in rablock */
extern	int intstack[];		/* stack for interrupts */
dev_t	rootdev;		/* device of the root */
struct vnode *rootvp;		/* vnode of root filesystem */
struct vnode	*dumpvp;	/* vnode to dump on */
long	dumplo;			/* offset into dumpvp */
dev_t	swapdev;		/* XXX */
struct vnode	*swapdev_vp;	/* vnode to swap on */
struct vnode	*argvp;		/* vnode to write args on */

#ifdef vax
extern	int icode[];		/* user init code */
extern	int szicode;		/* its size */
#endif

daddr_t	bmap();
unsigned max();
unsigned min();
int	memall();
int	vmemall();
caddr_t	wmemall();
caddr_t	kmem_alloc();
swblk_t	vtod();
struct vnode *bdevvp();
struct vnode *specvp();

/*
 * Structure of the system-entry table
 */
extern struct sysent
{
	short	sy_narg;		/* total number of arguments */
	int	(*sy_call)();		/* handler */
} sysent[];

int	noproc;			/* no one is running just now */
char	*panicstr;
int	wantin;
int	boothowto;		/* reboot flags, from console subsystem */
int	selwait;

extern	char vmmap[];		/* poor name! */

/* casts to keep lint happy */
#define	insque(q,p)	_insque((caddr_t)q,(caddr_t)p)
#define	remque(q)	_remque((caddr_t)q)
