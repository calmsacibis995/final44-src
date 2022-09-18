h04885
s 00002/00002/00068
d D 8.1 93/06/10 23:31:20 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00010/00068
d D 7.2 93/02/15 11:13:11 ralph 2 1
c fix copyright and comments.
e
s 00078/00000/00000
d D 7.1 93/02/15 11:10:55 ralph 1 0
c date and time created 93/02/15 11:10:55 by ralph
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1992 Regents of the University of California.
E 2
I 2
/*-
D 3
 * Copyright (c) 1993 Regents of the University of California.
E 2
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
D 2
 *
 * devDiskLabel.h --
 *
 *      This defines the disk label that Sun writes on the 0'th sector of
 *      the 0'th cylinder of its SMD disks.  The disk label contains some
 *      geometry information and also the division of the disk into a
 *      number of partitions.  Each partition is identified to the drive
 *      by a different unit number.
E 2
 */

/*
 * Portions of this file are subject to the following copyright notice:
 *
 * Copyright (C) 1989 Digital Equipment Corporation.
 * Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appears in all copies.  
 * Digital Equipment Corporation makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 */

/*
 * /sprite/src/kernel/proc/ds3100.md/RCS/procMach.h,v 9.3 90/02/20 15:35:50
 * shirriff Exp $ SPRITE (Berkeley)
 */

/* Description of the COFF section. */
struct coff_exec {
#define	COFF_MAGIC	0x0162
	u_short	magic;		/* The magic number. */

	u_short	numSections;	/* The number of sections. */
	long	timeDateStamp;	/* Time and date stamp. */		
	long	symPtr;		/* File pointer to symbolic header. */	
	long	numSyms;	/* Size of symbolic header. */
	u_short	optHeader;	/* Size of optional header. */
	u_short	flags;		/* Flags. */

/* Description of the a.out section. */
	short	aout_magic;	/* Magic number. */

	short	verStamp;	/* Version stamp. */
	long	codeSize;	/* Code size in bytes. */
	long	heapSize;	/* Initialized data size in bytes. */
	long	bssSize;	/* Uninitialized data size in bytes. */
	long	entry;		/* Entry point. */
	long	codeStart;	/* Base of code used for this file. */
	long	heapStart;	/* Base of heap used for this file. */
	long	bssStart;	/* Base of bss used for this file. */
	long	gprMask;	/* General purpose register mask. */
	long	cprMask[4];	/* Co-processor register masks. */
	long	gpValue;	/* The gp value for this object. */
};

/* Section header. */
typedef struct {
	char	name[8];	/* Section name. */
	long	physAddr;	/* Section physical address. */
	long	virtAddr;	/* Section virtual address. */
	long	size;		/* Section size. */
	long	sectionPtr;	/* File pointer to section data. */
	long	relocPtr;	/* File pointer to relocation data. */
	long	lnnoPtr;	/* File pointer to gp tables. */
	u_short	numReloc;	/* Number of relocation entries. */
	u_short	numLnno;	/* Numberof gp tables. */
	long	flags;		/* Section flags. */
} ProcSectionHeader;
E 1
