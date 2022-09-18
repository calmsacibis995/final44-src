h25458
s 00002/00002/00079
d D 8.1 93/06/10 23:02:03 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00044/00084/00037
d D 7.3 93/02/04 19:36:22 ralph 3 2
c real a.out header for MIPS
e
s 00001/00001/00120
d D 7.2 92/09/13 11:39:17 ralph 2 1
c fix N_DATOFF to correct name
e
s 00121/00000/00000
d D 7.1 92/03/18 16:34:24 bostic 1 0
c date and time created 92/03/18 16:34:24 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 3
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
E 3
I 3
#include <machine/endian.h>
E 3

D 3
/*
 * /sprite/src/kernel/proc/ds3100.md/RCS/procMach.h,v 9.3 90/02/20 15:35:50
 * shirriff Exp $ SPRITE (Berkeley)
 */

E 3
/* Size of a page in an object file. */
#define	__LDPGSZ	4096

/* Valid magic number check. */
#define	N_BADMAG(ex) \
	((ex).a_magic != NMAGIC && (ex).a_magic != OMAGIC && \
	    (ex).a_magic != ZMAGIC)

/* Address of the bottom of the text segment. */
D 3
#define N_TXTADDR(ex)	0x400000
E 3
I 3
#define N_TXTADDR(X)	__LDPGSZ
E 3

/* Address of the bottom of the data segment. */
D 3
/* NOT DEFINED FOR THE MIPS. */
E 3
I 3
#define N_DATADDR(ex) \
	(N_TXTADDR(ex) + ((ex).a_magic == OMAGIC ? (ex).a_text \
	: __LDPGSZ + ((ex).a_text - 1 & ~(__LDPGSZ - 1))))
E 3

/* Text segment offset. */
D 3
#define	__N_TXTOFF_ROUND(ex) \
	((ex).ex_aout.verStamp < 23 ? 7 : 15)
E 3
#define	N_TXTOFF(ex) \
D 3
	((ex).ex_aout.magic == ZMAGIC ? 0 : (sizeof(struct exec) + \
	    (ex).ex_fhdr.numSections * sizeof(ProcSectionHeader) + \
	    __N_TXTOFF_ROUND(ex)) & ~__N_TXTOFF_ROUND(ex))
E 3
I 3
	((ex).a_magic == ZMAGIC ? 0 : sizeof(struct exec))
E 3

/* Data segment offset. */
D 2
#define N_DATAOFF(ex) \
E 2
I 2
D 3
#define N_DATOFF(ex) \
E 2
	(N_TXTOFF(ex) + (ex).ex_aout.codeSize)
E 3
I 3
#define	N_DATOFF(ex) \
	(N_TXTOFF(ex) + ((ex).a_magic != ZMAGIC ? (ex).a_text : \
	__LDPGSZ + ((ex).a_text - 1 & ~(__LDPGSZ - 1))))
E 3

/* Symbol table offset. */
D 3
/* NOT DEFINED FOR THE MIPS. */
E 3
I 3
#define N_SYMOFF(ex) \
	(N_TXTOFF(ex) + (ex).a_text + (ex).a_data + (ex).a_trsize + \
	    (ex).a_drsize)
E 3

/* String table offset. */
D 3
/* NOT DEFINED FOR THE MIPS. */
E 3
I 3
#define	N_STROFF(ex) 	(N_SYMOFF(ex) + (ex).a_syms)
E 3

D 3
/*
 * XXX
 * The ProcFileHeader structure and the ProcAOUTHeader structure should be
 * folded together into a single struct exec.
 */
E 3
I 3
/* Description of the object file header (a.out format). */
struct exec {
#if BYTE_ORDER == BIG_ENDIAN
	u_short	a_mid;		/* machine ID */
	u_short	a_magic;	/* magic number */
#else
	u_short	a_magic;	/* magic number */
	u_short	a_mid;		/* machine ID */
#endif
E 3

D 3
/* Description of the COFF section. */
typedef struct {
#define	COFF_MAGIC	0x0162
	u_short	magic;		/* The magic number. */
E 3
I 3
	u_long	a_text;		/* text segment size */
	u_long	a_data;		/* initialized data size */
	u_long	a_bss;		/* uninitialized data size */
	u_long	a_syms;		/* symbol table size */
	u_long	a_entry;	/* entry point */
	u_long	a_trsize;	/* text relocation size */
	u_long	a_drsize;	/* data relocation size */
};
E 3

D 3
	u_short	numSections;	/* The number of sections. */
	long	timeDateStamp;	/* Time and date stamp. */		
	long	symPtr;		/* File pointer to symbolic header. */	
	long	numSyms;	/* Size of symbolic header. */
	u_short	optHeader;	/* Size of optional header. */
	u_short	flags;		/* Flags. */
} ProcFileHeader;
E 3
I 3
#define	a_machtype	a_mid	/* SUN compatibility */
E 3

D 3
/* Description of the a.out section. */
typedef struct {
E 3
I 3
#define	MID_ZERO	0	/* unknown - implementation dependent */
#define	MID_SUN010	1	/* sun 68010/68020 binary */
#define	MID_SUN020	2	/* sun 68020-only binary */
#define	MID_SUN_SPARC	3	/* sparc binary */
#define	MID_386		100	/* Intel 80386 binary */
#define	MID_29K		101	/* AMD 29000 binary */
#define	MID_MIPSI	151	/* MIPS R2000/R3000 binary */
#define	MID_MIPSII	152	/* MIPS R4000 binary */
#define	MID_HP200	200	/* hp200 (68010) BSD binary */
#define	MID_HP300	300	/* hp300 (68020+68881) BSD binary */
#define	MID_HPUX	0x20C	/* hp200/300 HP-UX binary */
#define	MID_HPUX800	0x20B	/* hp800 HP-UX binary */

E 3
#define	OMAGIC	0407		/* old impure format */
#define	NMAGIC	0410		/* read-only text */
#define	ZMAGIC	0413		/* demand load format */
D 3
	short	magic;		/* Magic number. */

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
} ProcAOUTHeader;

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

/* Description of the object file header. */
struct exec {
	ProcFileHeader	ex_fhdr;
	ProcAOUTHeader	ex_aout;
};
#define a_magic	ex_aout.magic
#define a_text	ex_aout.codeSize
#define a_data	ex_aout.heapSize
#define a_bss	ex_aout.bssSize
#define a_entry	ex_aout.entry
E 3
E 1
