/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	dklabel.h,v $
 * Revision 2.2  89/07/11  23:28:27  jjc
 * 	     Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)dklabel.h 5.8 88/02/08 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */
#ifndef _DKLABEL_
#define _DKLABEL_

/*
 * Miscellaneous defines
 */
#define	DKL_MAGIC	0xDABE	/* magic number */
#define	NDKMAP	8		/* # of logical partitions */

/*
 * Format of a Sun SMD disk label.
 * Resides in cylinder 0, head 0, sector 0.
 *
 * sizeof(struct dk_label) should be 512 (sector size)
 */
struct dk_label {
	char	dkl_asciilabel[128];	/* for compatibility */
	char	dkl_pad[512-(128+NDKMAP*8+14*2)];
	unsigned short	dkl_rpm;	/* rotations per minute */
	unsigned short	dkl_pcyl;	/* # physical cylinders */
	unsigned short	dkl_apc;	/* alternates per cylinder */
	unsigned short	dkl_obs1;	/* obsolete */
	unsigned short	dkl_obs2;	/* obsolete */
	unsigned short	dkl_intrlv;	/* interleave factor */
	unsigned short	dkl_ncyl;	/* # of data cylinders */
	unsigned short	dkl_acyl;	/* # of alternate cylinders */
	unsigned short	dkl_nhead;	/* # of heads in this partition */
	unsigned short	dkl_nsect;	/* # of 512 byte sectors per track */
	unsigned short	dkl_obs3;	/* obsolete */
	unsigned short	dkl_obs4;	/* obsolete */
	/* */
	struct dk_map {			/* logical partitions */
		daddr_t	dkl_cylno;	/* starting cylinder */
		daddr_t dkl_nblk;	/* number of blocks */
	} dkl_map[NDKMAP];
	unsigned short	dkl_magic;	/* identifies this label format */
	unsigned short	dkl_cksum;	/* xor checksum of sector */
};

/*
 * These defines are for historic compatibility with old drivers.
 */
#define	dkl_gap1	dkl_obs1	/* used to be gap1 */
#define	dkl_gap2	dkl_obs2	/* used to be gap2 */
#define	dkl_bhead	dkl_obs3	/* used to be label head offset */
#define	dkl_ppart	dkl_obs4	/* used to by physical partition */

#endif !_DKLABEL_
