/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	ubavar.h,v $
 * Revision 2.5  89/03/09  22:40:23  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/26  11:09:27  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  88/08/24  03:09:03  mwyoung
 * 	Corrected conditionals, include file references.
 * 	[88/08/22  23:15:00  mwyoung]
 * 
 * 17-Sep-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	NET_UDA:  install updates for new uda driver from Chris Torek
 *	at UMD.
 *	[ V5.1(XF16) ]
 *
 *  5-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Replace the dwbua flag in the ubahd structure with a "unibus
 *	type."  This will generalize for other devices which can be
 *	treated like a "fake" unibus.
 *
 * 19-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Flush CS_NEWCPU.
 *
 * 26-Feb-86  David Golub (dbg) at Carnegie-Mellon University
 *	Converted to new virtual memory code.
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 17-Jun-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_NEWCPU:  Added UBAMAPANYWAY definition (a la ULTRIX-32).
 *	[V1(1)].
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)ubavar.h	7.1 (Berkeley) 6/5/86
 */

/*
 * This file contains definitions related to the kernel structures
 * for dealing with the unibus adapters.
 *
 * Each uba has a uba_hd structure.
 * Each unibus controller which is not a device has a uba_ctlr structure.
 * Each unibus device has a uba_device structure.
 */
 
#ifdef	KERNEL
#ifdef	MACH
#include <cputypes.h>
#endif	MACH
#include <bi.h>
#include <net_uda.h>
 
#include <uba.h>
#endif	KERNEL

#ifndef	LOCORE
/*
 * Per-uba structure.
 *
 * This structure holds the interrupt vector for the uba,
 * and its address in physical and virtual space.  At boot time
 * we determine the devices attached to the uba's and their
 * interrupt vectors, filling in uh_vec.  We free the map
 * register and bdp resources of the uba into the structures
 * defined here.
 *
 * During normal operation, resources are allocated and returned
 * to the structures here.  We watch the number of passive releases
 * on each uba, and if the number is excessive may reset the uba.
 * 
 * When uba resources are needed and not available, or if a device
 * which can tolerate no other uba activity (rk07) gets on the bus,
 * then device drivers may have to wait to get to the bus and are
 * queued here.  It is also possible for processes to block in
 * the unibus driver in resource wait (mrwant, bdpwant); these
 * wait states are also recorded here.
 */
struct	uba_hd {
	struct	uba_regs *uh_uba;	/* virt addr of uba */
	struct	uba_regs *uh_physuba;	/* phys addr of uba */
	int	(**uh_vec)();		/* interrupt vector */
	struct	uba_device *uh_actf;	/* head of queue to transfer */
	struct	uba_device *uh_actl;	/* tail of queue to transfer */
	short	uh_mrwant;		/* someone is waiting for map reg */
	short	uh_bdpwant;		/* someone awaits bdp's */
	int	uh_bdpfree;		/* free bdp's */
	int	uh_hangcnt;		/* number of ticks hung */
	int	uh_zvcnt;		/* number of recent 0 vectors */
	long	uh_zvtime;		/* time over which zvcnt accumulated */
	int	uh_zvtotal;		/* total number of 0 vectors */
	int	uh_errcnt;		/* number of errors */
	int	uh_lastiv;		/* last free interrupt vector */
	short	uh_users;		/* transient bdp use count */
	short	uh_xclu;		/* an rk07 is using this uba! */
	int	uh_lastmem;		/* limit of any unibus memory */
#ifdef	CMUCS
	int	uh_type;		/* type of uba */
#endif	CMUCS
#define UAMSIZ	100
	struct	map *uh_map;		/* buffered data path regs free */
};
#ifdef	CMUCS
#define UBATYPE_UBA	0		/* Normal (?) UBA */
#define UBATYPE_DWBUA	1		/* BI to Unibus Adaptor */
#define UBATYPE_KDB50	2		/* KDB50 pretenting to be Unibus */
#endif	CMUCS

#ifndef	LOCORE
/*
 * Per-controller structure.
 * (E.g. one for each disk and tape controller, and other things
 * which use and release buffered data paths.)
 *
 * If a controller has devices attached, then there are
 * cross-referenced uba_drive structures.
 * This structure is the one which is queued in unibus resource wait,
 * and saves the information about unibus resources which are used.
 * The queue of devices waiting to transfer is also attached here.
 */
struct uba_ctlr {
	struct	uba_driver *um_driver;
	short	um_ctlr;	/* controller index in driver */
	short	um_ubanum;	/* the uba it is on */
	short	um_alive;	/* controller exists */
	int	(**um_intr)();	/* interrupt handler(s) */
	caddr_t	um_addr;	/* address of device in i/o space */
	struct	uba_hd *um_hd;
/* the driver saves the prototype command here for use in its go routine */
	int	um_cmd;		/* communication to dgo() */
	int	um_ubinfo;	/* save unibus registers, etc */
#if	NET_UDA
	int	um_bdp;		/* for controllers that hang on to bdp's */
#endif	NET_UDA
	struct	buf um_tab;	/* queue of devices for this controller */
};

/*
 * Per ``device'' structure.
 * (A controller has devices or uses and releases buffered data paths).
 * (Everything else is a ``device''.)
 *
 * If a controller has many drives attached, then there will
 * be several uba_device structures associated with a single uba_ctlr
 * structure.
 *
 * This structure contains all the information necessary to run
 * a unibus device such as a dz or a dh.  It also contains information
 * for slaves of unibus controllers as to which device on the slave
 * this is.  A flags field here can also be given in the system specification
 * and is used to tell which dz lines are hard wired or other device
 * specific parameters.
 */
struct uba_device {
	struct	uba_driver *ui_driver;
	short	ui_unit;	/* unit number on the system */
	short	ui_ctlr;	/* mass ctlr number; -1 if none */
	short	ui_ubanum;	/* the uba it is on */
	short	ui_slave;	/* slave on controller */
	int	(**ui_intr)();	/* interrupt handler(s) */
	caddr_t	ui_addr;	/* address of device in i/o space */
	short	ui_dk;		/* if init 1 set to number for iostat */
	int	ui_flags;	/* parameter from system specification */
	short	ui_alive;	/* device exists */
	short	ui_type;	/* driver specific type information */
	caddr_t	ui_physaddr;	/* phys addr, for standalone (dump) code */
/* this is the forward link in a list of devices on a controller */
	struct	uba_device *ui_forw;
/* if the device is connected to a controller, this is the controller */
	struct	uba_ctlr *ui_mi;
	struct	uba_hd *ui_hd;
};
#endif

/*
 * Per-driver structure.
 *
 * Each unibus driver defines entries for a set of routines
 * as well as an array of types which are acceptable to it.
 * These are used at boot time by the configuration program.
 */
struct uba_driver {
	int	(*ud_probe)();		/* see if a driver is really there */
	int	(*ud_slave)();		/* see if a slave is there */
	int	(*ud_attach)();		/* setup driver for a slave */
	int	(*ud_dgo)();		/* fill csr/ba to start transfer */
	u_short	*ud_addr;		/* device csr addresses */
	char	*ud_dname;		/* name of a device */
	struct	uba_device **ud_dinfo;	/* backpointers to ubdinit structs */
	char	*ud_mname;		/* name of a controller */
	struct	uba_ctlr **ud_minfo;	/* backpointers to ubminit structs */
	short	ud_xclu;		/* want exclusive use of bdp's */
#if	NET_UDA
	short	ud_keepbdp;		/* hang on to bdp's once allocated */
#endif	NET_UDA
	int	(*ud_ubamem)();		/* see if dedicated memory is present */
};
#endif

/*
 * Flags to UBA map/bdp allocation routines
 */
#define UBA_NEEDBDP	0x01		/* transfer needs a bdp */
#define UBA_CANTWAIT	0x02		/* don't block me */
#define UBA_NEED16	0x04		/* need 16 bit addresses only */
#define UBA_HAVEBDP	0x08		/* use bdp specified in high bits */
#if	VAX820 || VAX1
#define UBA_MAPANYWAY	0x10		/* map anyway on MicroVax I or 8200 */
#endif	VAX820 || VAX1

/*
 * Macros to bust return word from map allocation routines.
 */
#define UBAI_BDP(i)	((int)(((unsigned)(i))>>28))
#define UBAI_NMR(i)	((int)((i)>>18)&0x3ff)
#define UBAI_MR(i)	((int)((i)>>9)&0x1ff)
#define UBAI_BOFF(i)	((int)((i)&0x1ff))
#define UBAI_ADDR(i)	((int)((i)&0x3ffff))	/* uba addr (boff+mr) */

#ifndef	LOCORE
#ifdef	KERNEL
#if	NET_UDA
#define ubago(ui)	ubaqueue(ui, 0)

#endif	NET_UDA
/*
 * UBA related kernel variables
 */
int	numuba;					/* number of uba's */
struct	uba_hd uba_hd[];

/*
 * Ubminit and ubdinit initialize the mass storage controller and
 * device tables specifying possible devices.
 */
extern	struct	uba_ctlr ubminit[];
extern	struct	uba_device ubdinit[];

#ifdef	MACH
/* 
 *	Unibus memory is mapped between unibus_start and unibus_end,
 *	which are dynamically determined in autoconf (or qv).
 */
extern	vm_offset_t	unibus_start[], unibus_end[];
#else	MACH
/*
 * UNIbus device address space is mapped by UMEMmap
 * into virtual address umem[][].
 */
extern	struct pte UMEMmap[][512];	/* uba device addr pte's */
extern	char umem[][512*NBPG];		/* uba device addr space */
#endif	MACH

/*
 * Since some VAXen vector their unibus interrupts
 * just adjacent to the system control block, we must
 * allocate space there when running on ``any'' cpu.  This space is
 * used for the vectors for uba0 and uba1 on all cpu's.
 */
extern	int (*UNIvec[])();			/* unibus vec for uba0 */
#if	NUBA > 1
extern	int (*UNI1vec[])();			/* unibus vec for uba1 */
#endif

#if	defined(VAX780) || defined(VAX8600)
/*
 * On 780's, we must set the scb vectors for the nexus of the
 * UNIbus adaptors to vector to locore unibus adaptor interrupt dispatchers
 * which make 780's look like the other VAXen.
 */
extern	Xua0int(), Xua1int(), Xua2int(), Xua3int();
#endif	VAX780
#endif	KERNEL
#endif	!LOCORE
