h60267
s 00055/00055/00066
d D 8.2 94/07/10 22:58:39 bostic 19 18
c changes for 64-bit machines
e
s 00002/00002/00119
d D 8.1 93/06/02 19:56:57 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00039/00033/00082
d D 7.4 91/08/28 15:30:36 mckusick 17 16
c merge in vm_stat structure from vm_statistics.h
c update to reflect new statistics that are actually gathered
e
s 00005/00004/00110
d D 7.3 91/05/05 18:39:30 bostic 16 15
c new copyright; att/bsd/shared
e
s 00004/00000/00110
d D 7.2 86/10/13 23:01:51 karels 15 14
c merge in tahoe system
e
s 00001/00001/00109
d D 7.1 86/06/04 23:32:30 mckusick 14 13
c 4.3BSD release version
e
s 00009/00009/00101
d D 6.4 85/08/02 18:49:43 bloom 13 12
c vmtotal broke on a machine with 32M of mem
e
s 00007/00001/00103
d D 6.3 85/06/08 15:13:52 mckusick 12 11
c Add copyright
e
s 00001/00000/00103
d D 6.2 84/08/21 11:09:01 karels 11 10
c add v_soft for software interrupts
e
s 00000/00000/00103
d D 6.1 83/07/29 06:15:16 sam 10 9
c 4.2 distribution
e
s 00002/00002/00101
d D 4.7 83/05/30 18:21:20 sam 9 7
c add counter for fast reclaims done in locore
e
s 00001/00000/00103
d R 4.7 83/05/30 16:35:16 sam 8 7
c add counter for fast reclaims
e
s 00001/00000/00102
d D 4.6 81/04/24 11:19:10 wnj 7 6
c added v_seqfree
e
s 00002/00000/00100
d D 4.5 81/04/24 00:13:54 wnj 6 5
c added v_pgpgin v_pgpgout
e
s 00060/00000/00040
d D 4.4 81/04/23 01:25:30 wnj 5 4
c consolidate, and rearrange for new parameter determination stuff
e
s 00000/00002/00040
d D 4.3 81/02/26 04:30:20 wnj 4 3
c cosmetics
e
s 00000/00000/00042
d D 4.2 81/02/19 21:43:28 wnj 3 2
c %G%->%E%
e
s 00000/00000/00042
d D 4.1 80/11/09 17:02:28 bill 2 1
c stamp for 4bsd
e
s 00042/00000/00000
d D 3.1 80/09/27 20:56:15 bill 1 0
c date and time created 80/09/27 20:56:15 by bill
e
u
U
t
T
I 1
D 9

E 9
D 12
/*	%M%	%I%	%G%	*/
E 12
I 12
D 16
/*
D 14
 * Copyright (c) 1982 Regents of the University of California.
E 14
I 14
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 14
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 16
I 16
/*-
D 18
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
E 18
I 18
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 18
 *
 * %sccs.include.redist.c%
E 16
 *
 *	%W% (Berkeley) %G%
 */
E 12

/*
D 17
 * Virtual memory related instrumentation
E 17
I 17
 * System wide statistics counters.
E 17
D 4
 *
 * NB: THE OFFSETS IN THE vmmeter STRUCTURE ARE KNOWN IN vm.m.
E 4
 */
D 17
struct vmmeter
{
#define	v_first	v_swtch
E 17
I 17
struct vmmeter {
	/*
	 * General system activity.
	 */
E 17
D 19
	unsigned v_swtch;	/* context switches */
	unsigned v_trap;	/* calls to trap */
	unsigned v_syscall;	/* calls to syscall() */
	unsigned v_intr;	/* device interrupts */
I 11
	unsigned v_soft;	/* software interrupts */
E 11
D 17
	unsigned v_pdma;	/* pseudo-dma interrupts */
E 17
I 17
	unsigned v_faults;	/* total faults taken */
E 19
I 19
	u_int v_swtch;		/* context switches */
	u_int v_trap;		/* calls to trap */
	u_int v_syscall;	/* calls to syscall() */
	u_int v_intr;		/* device interrupts */
	u_int v_soft;		/* software interrupts */
	u_int v_faults;		/* total faults taken */
E 19
	/*
	 * Virtual memory activity.
	 */
D 19
	unsigned v_lookups;	/* object cache lookups */
	unsigned v_hits;	/* object cache hits */
	unsigned v_vm_faults;	/* number of address memory faults */
	unsigned v_cow_faults;	/* number of copy-on-writes */
	unsigned v_swpin;	/* swapins */
	unsigned v_swpout;	/* swapouts */
E 17
	unsigned v_pswpin;	/* pages swapped in */
	unsigned v_pswpout;	/* pages swapped out */
D 17
	unsigned v_pgin;	/* pageins */
	unsigned v_pgout;	/* pageouts */
E 17
I 17
	unsigned v_pageins;	/* number of pageins */
	unsigned v_pageouts;	/* number of pageouts */
E 17
I 6
	unsigned v_pgpgin;	/* pages paged in */
	unsigned v_pgpgout;	/* pages paged out */
E 6
	unsigned v_intrans;	/* intransit blocking page faults */
D 17
	unsigned v_pgrec;	/* total page reclaims */
	unsigned v_xsfrec;	/* found in free list rather than on swapdev */
	unsigned v_xifrec;	/* found in free list rather than in filsys */
	unsigned v_exfod;	/* pages filled on demand from executables */
	unsigned v_zfod;	/* pages zero filled on demand */
	unsigned v_vrfod;	/* fills of pages mapped by vread() */
	unsigned v_nexfod;	/* number of exfod's created */
	unsigned v_nzfod;	/* number of zfod's created */
	unsigned v_nvrfod;	/* number of vrfod's created */
	unsigned v_pgfrec;	/* page reclaims from free list */
	unsigned v_faults;	/* total faults taken */
	unsigned v_scan;	/* scans in page out daemon */
E 17
I 17
	unsigned v_reactivated;	/* number of pages reactivated from free list */
E 17
	unsigned v_rev;		/* revolutions of the hand */
I 7
D 17
	unsigned v_seqfree;	/* pages taken from sequential programs */
E 17
I 17
	unsigned v_scan;	/* scans in page out daemon */
E 17
E 7
	unsigned v_dfree;	/* pages freed by daemon */
D 9
#define	v_last v_dfree
E 9
I 9
D 17
	unsigned v_fastpgrec;	/* fast reclaims in locore */
I 15
#ifdef tahoe
	unsigned v_fpe;		/* floating point emulation traps */
	unsigned v_align;	/* alignment emulation traps */
#endif
E 15
#define	v_last v_fastpgrec
E 9
	unsigned v_swpin;	/* swapins */
	unsigned v_swpout;	/* swapouts */
E 17
I 17
	unsigned v_pfree;	/* pages freed by exiting processes */
	unsigned v_zfod;	/* pages zero filled on demand */
	unsigned v_nzfod;	/* number of zfod's created */
E 19
I 19
	u_int v_lookups;	/* object cache lookups */
	u_int v_hits;		/* object cache hits */
	u_int v_vm_faults;	/* number of address memory faults */
	u_int v_cow_faults;	/* number of copy-on-writes */
	u_int v_swpin;		/* swapins */
	u_int v_swpout;		/* swapouts */
	u_int v_pswpin;		/* pages swapped in */
	u_int v_pswpout;	/* pages swapped out */
	u_int v_pageins;	/* number of pageins */
	u_int v_pageouts;	/* number of pageouts */
	u_int v_pgpgin;		/* pages paged in */
	u_int v_pgpgout;	/* pages paged out */
	u_int v_intrans;	/* intransit blocking page faults */
	u_int v_reactivated;	/* number of pages reactivated from free list */
	u_int v_rev;		/* revolutions of the hand */
	u_int v_scan;		/* scans in page out daemon */
	u_int v_dfree;		/* pages freed by daemon */
	u_int v_pfree;		/* pages freed by exiting processes */
	u_int v_zfod;		/* pages zero filled on demand */
	u_int v_nzfod;		/* number of zfod's created */
E 19
	/*
	 * Distribution of page usages.
	 */
D 19
	unsigned v_page_size;	/* page size in bytes */
	unsigned v_kernel_pages;/* number of pages in use by kernel */
	unsigned v_free_target;	/* number of pages desired free */
	unsigned v_free_min;	/* minimum number of pages desired free */
	unsigned v_free_count;	/* number of pages free */
	unsigned v_wire_count;	/* number of pages wired down */
	unsigned v_active_count;/* number of pages active */
	unsigned v_inactive_target; /* number of pages desired inactive */
	unsigned v_inactive_count;  /* number of pages inactive */
E 19
I 19
	u_int v_page_size;	/* page size in bytes */
	u_int v_kernel_pages;	/* number of pages in use by kernel */
	u_int v_free_target;	/* number of pages desired free */
	u_int v_free_min;	/* minimum number of pages desired free */
	u_int v_free_count;	/* number of pages free */
	u_int v_wire_count;	/* number of pages wired down */
	u_int v_active_count;	/* number of pages active */
	u_int v_inactive_target; /* number of pages desired inactive */
	u_int v_inactive_count;  /* number of pages inactive */
E 19
E 17
};
#ifdef KERNEL
D 17
struct	vmmeter cnt, rate, sum;
E 17
I 17
struct	vmmeter cnt;
E 17
#endif
I 5

/* systemwide totals computed every five seconds */
struct vmtotal
{
D 19
	short	t_rq;		/* length of the run queue */
	short	t_dw;		/* jobs in ``disk wait'' (neg priority) */
	short	t_pw;		/* jobs in page wait */
	short	t_sl;		/* jobs sleeping in core */
	short	t_sw;		/* swapped out runnable/short block jobs */
D 13
	int	t_vm;		/* total virtual memory */
	int	t_avm;		/* active virtual memory */
	short	t_rm;		/* total real memory in use */
	short	t_arm;		/* active real memory */
	int	t_vmtxt;	/* virtual memory used by text */
	int	t_avmtxt;	/* active virtual memory used by text */
	short	t_rmtxt;	/* real memory used by text */
	short	t_armtxt;	/* active real memory used by text */
	short	t_free;		/* free memory pages */
E 13
I 13
	long	t_vm;		/* total virtual memory */
	long	t_avm;		/* active virtual memory */
	long	t_rm;		/* total real memory in use */
	long	t_arm;		/* active real memory */
D 17
	long	t_vmtxt;	/* virtual memory used by text */
	long	t_avmtxt;	/* active virtual memory used by text */
	long	t_rmtxt;	/* real memory used by text */
	long	t_armtxt;	/* active real memory used by text */
E 17
I 17
	long	t_vmshr;	/* shared virtual memory */
	long	t_avmshr;	/* active shared virtual memory */
	long	t_rmshr;	/* shared real memory */
	long	t_armshr;	/* active shared real memory */
E 17
	long	t_free;		/* free memory pages */
E 19
I 19
	int16_t	t_rq;		/* length of the run queue */
	int16_t	t_dw;		/* jobs in ``disk wait'' (neg priority) */
	int16_t	t_pw;		/* jobs in page wait */
	int16_t	t_sl;		/* jobs sleeping in core */
	int16_t	t_sw;		/* swapped out runnable/short block jobs */
	int32_t	t_vm;		/* total virtual memory */
	int32_t	t_avm;		/* active virtual memory */
	int32_t	t_rm;		/* total real memory in use */
	int32_t	t_arm;		/* active real memory */
	int32_t	t_vmshr;	/* shared virtual memory */
	int32_t	t_avmshr;	/* active shared virtual memory */
	int32_t	t_rmshr;	/* shared real memory */
	int32_t	t_armshr;	/* active shared real memory */
	int32_t	t_free;		/* free memory pages */
E 19
E 13
};
#ifdef KERNEL
struct	vmtotal total;
#endif

/*
 * Optional instrumentation.
 */
#ifdef PGINPROF

#define	NDMON	128
#define	NSMON	128

#define	DRES	20
#define	SRES	5

#define	PMONMIN	20
#define	PRES	50
#define	NPMON	64

#define	RMONMIN	130
#define	RRES	5
#define	NRMON	64

/* data and stack size distribution counters */
D 19
unsigned int	dmon[NDMON+1];
unsigned int	smon[NSMON+1];
E 19
I 19
u_int	dmon[NDMON+1];
u_int	smon[NSMON+1];
E 19

/* page in time distribution counters */
D 19
unsigned int	pmon[NPMON+2];
E 19
I 19
u_int	pmon[NPMON+2];
E 19

/* reclaim time distribution counters */
D 19
unsigned int	rmon[NRMON+2];
E 19
I 19
u_int	rmon[NRMON+2];
E 19

int	pmonmin;
int	pres;
int	rmonmin;
int	rres;

D 19
unsigned rectime;		/* accumulator for reclaim times */
unsigned pgintime;		/* accumulator for page in times */
E 19
I 19
u_int rectime;		/* accumulator for reclaim times */
u_int pgintime;		/* accumulator for page in times */
E 19
#endif
E 5
E 1
