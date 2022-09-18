/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	autoconf.h,v $
 * Revision 2.5  91/08/29  22:39:07  berman
 * 	Upgraded some definitions and added openprom declarations.
 * 	[91/06/11            berman]
 * 
 * Revision 2.4  90/12/17  17:16:24  berman
 * 	Added in sunOS 4.0.3c definitions for Sparcstation port.
 * 	[90/09/10            berman]
 * 
 * Revision 2.3  89/03/09  21:29:08  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:27:11  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
/* @(#)autoconf.h 1.1 86/09/25 SMI */

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */
#ifndef	AUTOCONF_H_
#define AUTOCONF_H_
#if	MACH
#define addr_t caddr_t
#endif	MACH

/*
 * Defines for bus types.  These are magic cookies passed between config
 * and the kernel to tell what bus each device is on.
 */
#define SP_BUSMASK	0x0000FFFF	/* mask for bus type */
#define SP_VIRTUAL	0x0001		/* virtual address */
#define SP_OBMEM	0x0002		/* on board memory */
#define SP_OBIO		0x0004		/* on board i/o */
#define SP_MBMEM	0x0010		/* multibus memory (sun2 only) */
#define SP_MBIO		0x0020		/* multibus i/o (sun2 only) */
#define SP_ATMEM	0x0040		/* atbus memory (sun386 only) */
#define SP_ATIO		0x0080		/* atbus i/o (sun386 only) */
#define SP_VME16D16	0x0100		/* vme 16/16 */
#define SP_VME24D16	0x0200		/* vme 24/16 */
#define SP_VME32D16	0x0400		/* vme 32/16 (sun3 only) */
#define SP_VME16D32	0x1000		/* vme 16/32 (sun3 only) */
#define SP_VME24D32	0x2000		/* vme 24/32 (sun3 only) */
#define SP_VME32D32	0x4000		/* vme 32/32 (sun3 only) */
#define	SP_IPI		0x8000		/* IPI channel address */

/*
 * Defines for encoding the machine type in the space field of
 * each device.
 */
#define SP_MACHMASK	0xFFFF0000	/* space mask for machine type */
#define MAKE_MACH(m)	((m)<<16)
#define SP_MACH_ALL	MAKE_MACH(0)	/* 0 implies all machines */

#ifdef OPENPROMS

/*
 * OPENPROM autoconfiguration goodies
 * These structures are NOT exported to the world!
 * They are defined here ONLY as a service to device driver writers
 * who would prefer to create (at least some of) the
 * PROM internal structures in C.
 */

/*
 * As far as the external world (clients of the ROMvec) is concerned,
 * device nodes are "magic cookies" of type "int".  We assume here that
 * an int is capable of representing an opaque pointer.
 */
typedef struct dev_element {
	struct dev_element *next;
	struct dev_element *slaves;
	struct property *props;
} devnode_t;

struct property {
	char *name;
	int size;
	caddr_t value;
};

#define SPO_VIRTUAL	-1	/* virtual address (not used?) */

/*
 * Other legal values are OBMEM and OBIO from machine/pte.h, because
 * the space identifier is identical to the "type" bits from the MMU.  
 * The space identifier should be thought of as simply some extra
 * physical address bits.
 */

/*
 * These are service routines in openprom_util.c
 */
struct dev_info *path_to_devi(/* char *path */);
int get_part_from_path(/* char *path */);
u_int atou(/* char *s */);
int (*path_getdecodefunc(/* struct devinfo *dip */))();
char *(*path_getencodefunc(/* struct devinfo *dip */))();
int (*path_getmatchfunc(/* struct devinfo *dip */))();

/*
 * Structures and service routines from machine/openprom_xxx.c.
 */
struct dev_path_ops {
	char *devp_name;		/* driver name */
	int (*devp_decode_regprop)();	/* decode reg property to reg struct */
	char *(*devp_encode_reg)();	/* encode reg struct to address */
	int (*devp_match_addr)();	/* does this node match this address? */
};

extern struct dev_path_ops dev_path_opstab[];
int obio_decode_regprop(/* struct dev_info *dip, int nodeid */);
char *obio_encode_reg(/* struct dev_info *dip, char *addrspec */);
int obio_match(/* struct dev_info *dip, char *addrspec */);

#endif OPENPROMS

#ifdef i386

/* maximum number of interrupt request channels (irq's) */
#ifdef SUN386 
#define NVECT	24
#else  SUN386
#define NVECT	72
#endif SUN386

#else  i386

/* maximum number of autovectored interrupts at a given priority */
#define	NVECT	10

#endif i386

/*
 * An array of these structures will replace the three "levelN_*" arrays
 * used by older architectures.
 */
struct autovec {
	int (*av_vector)();	/* interrupt handler */
	int av_intcnt;		/* interrupt counter */
	char *av_name;		/* pointer to driver name */
	int av_devcnt;		/* number of devices driver handles */
};

#if	defined(sun4c) && defined(KERNEL)
/*
 * These are service routines in autoconf.c that device drivers
 * can call.
 */

addr_t map_regs(/* (addr_t)addr, (u_int)size, (int)space */);
void unmap_regs(/* (addr_t)addr, (u_int)size */);
int walk_devs(/* (struct dev_info *)dev_info, (int (*)())f, (caddr_t)arg */);
void report_dev(/* (struct dev_info) dev */);

#endif /* defined(sun4c) && defined(KERNEL)*/

#endif	AUTOCONF_H_

