h23331
s 00000/00009/00036
d D 8.4 95/02/19 07:48:27 cgd 18 17
c execve_args now goes in auto-generated syscallargs.h file.
e
s 00005/00000/00040
d D 8.3 94/01/21 17:25:08 bostic 17 16
c add USL's copyright notice
e
s 00009/00000/00031
d D 8.2 93/09/21 07:14:38 mckusick 16 15
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00029
d D 8.1 93/06/02 19:53:24 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00021/00001/00010
d D 7.11 92/03/18 18:04:57 mckusick 14 13
c add structure to locate ps straings
e
s 00003/00153/00008
d D 7.10 92/03/18 16:32:44 bostic 13 12
c break up exec.h into <machine/exec.h>, <machine/reloc.h>
e
s 00007/00000/00154
d D 7.9 92/02/15 21:36:58 mckusick 12 11
c __LDPGSZ moves in from a.out.h
e
s 00008/00000/00146
d D 7.8 92/02/05 19:48:09 torek 11 10
c sparc header stuff
e
s 00000/00000/00146
d D 7.7 91/11/20 17:04:25 marc 10 8
i 9
c merge in 7.5.1.1 (ralphs 3100 changes -- COFF)
e
s 00099/00000/00045
d D 7.5.1.1 91/11/20 17:03:05 marc 9 7
c ralphs 3100 changes (COFF support)
e
s 00002/00000/00045
d D 7.6 91/11/13 09:45:57 bostic 8 7
c don't add MID #defines unless structure is there
e
s 00016/00017/00029
d D 7.5 91/02/15 14:31:03 bostic 7 6
c add Berkeley specific copyright notice
e
s 00005/00000/00041
d D 7.4 91/02/05 17:03:59 bostic 6 5
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00001/00040
d D 7.3 91/01/09 19:37:21 william 5 4
c trivial 386 ifdefs added
e
s 00017/00001/00024
d D 7.2 90/05/09 10:46:48 mckusick 4 3
c update for hp300 merge
e
s 00001/00001/00024
d D 7.1 86/06/04 23:22:21 mckusick 3 2
c 4.3BSD release version
e
s 00007/00001/00018
d D 1.2 85/06/08 14:56:54 mckusick 2 1
c Add copyright
e
s 00019/00000/00000
d D 1.1 84/07/21 16:04:07 sam 1 0
c date and time created 84/07/21 16:04:07 by sam
e
u
U
f b 
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
D 7
/*
D 3
 * Copyright (c) 1982 Regents of the University of California.
E 3
I 3
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
D 13
 * Copyright (c) 1982, 1986 The Regents of the University of California.
E 13
I 13
D 15
 * Copyright (c) 1992 The Regents of the University of California.
E 13
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
I 17
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 17
E 15
E 7
 *
I 7
 * %sccs.include.redist.c%
 *
E 7
 *	%W% (Berkeley) %G%
 */
E 2

I 6
D 7
#ifndef _EXEC_H_
E 7
I 7
D 13
#ifndef	_EXEC_H_
E 7
#define	_EXEC_H_

I 12
#if defined(hp300) || defined(i386) || defined(mips)
#define	__LDPGSZ	4096
#endif
#if defined(tahoe) || defined(vax)
#define	__LDPGSZ	1024
#endif

E 12
I 9
#ifndef COFF
E 9
E 6
D 7
/*
 * Header prepended to each a.out file.
 */
E 7
I 7
/* Header prepended to each a.out file. */
E 7
struct exec {
I 11
#ifdef sparc
unsigned char	a_dynamic:1;	/* dynamically linked */
unsigned char	a_toolversion:7;/* Sun toolset version  XXX */
unsigned char	a_mid;		/* machine ID */
unsigned short	a_magic;	/* magic number */
#else
E 11
D 4
	long	a_magic;	/* magic number */
E 4
I 4
D 5
#if !defined(vax) && !defined(tahoe)
E 5
I 5
#if !defined(vax) && !defined(tahoe) && !defined(i386)
E 5
unsigned short	a_mid;		/* machine ID */
unsigned short	a_magic;	/* magic number */
#else
	 long	a_magic;	/* magic number */
#endif
I 11
#endif
E 11
E 4
D 7
unsigned long	a_text;		/* size of text segment */
unsigned long	a_data;		/* size of initialized data */
unsigned long	a_bss;		/* size of uninitialized data */
unsigned long	a_syms;		/* size of symbol table */
E 7
I 7
unsigned long	a_text;		/* text segment size */
unsigned long	a_data;		/* initialized data size */
unsigned long	a_bss;		/* uninitialized data size */
unsigned long	a_syms;		/* symbol table size */
E 7
unsigned long	a_entry;	/* entry point */
D 7
unsigned long	a_trsize;	/* size of text relocation */
unsigned long	a_drsize;	/* size of data relocation */
E 7
I 7
unsigned long	a_trsize;	/* text relocation size */
unsigned long	a_drsize;	/* data relocation size */
E 7
};
I 4
#define	a_machtype	a_mid	/* SUN compatibility */
I 9
#endif /* COFF */
E 9
E 4

I 4
/* a_magic */
E 4
D 7
#define	OMAGIC	0407		/* old impure format */
#define	NMAGIC	0410		/* read-only text */
#define	ZMAGIC	0413		/* demand load format */
E 7
I 7
#define	OMAGIC		0407	/* old impure format */
#define	NMAGIC		0410	/* read-only text */
#define	ZMAGIC		0413	/* demand load format */
E 7
I 4

I 8
#if !defined(vax) && !defined(tahoe) && !defined(i386)
E 8
/* a_mid */
#define	MID_ZERO	0	/* unknown - implementation dependent */
#define	MID_SUN010	1	/* sun 68010/68020 binary */
#define	MID_SUN020	2	/* sun 68020-only binary */
I 11
#define	MID_SUN_SPARC	3	/* sparc binary */
E 11
#define	MID_HP200	200	/* hp200 (68010) BSD binary */
#define	MID_HP300	300	/* hp300 (68020+68881) BSD binary */
#define	MID_HPUX	0x20C	/* hp200/300 HP-UX binary */
#define	MID_HPUX800     0x20B   /* hp800 HP-UX binary */
I 8
#endif
E 8
I 6

I 9
#ifdef COFF
/*
 * procAOUT.h --
 *
 *	The a.out format for an object file.
 *
 * Copyright (C) 1989 Digital Equipment Corporation.
 * Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appears in all copies.  
 * Digital Equipment Corporation makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * $Header: /sprite/src/kernel/proc/ds3100.md/RCS/procMach.h,v 9.3 90/02/20 15:35:50 shirriff Exp $ SPRITE (Berkeley)
 */

/*
 * File header magic number.
 */
#define	COFF_MAGIC	0x0162

/*
 * Description of the file.
 */
typedef struct {
    unsigned short	magic;		/* The magic number. */
    unsigned short	numSections;	/* The number of sections. */
    long		timeDateStamp;	/* Time and date stamp. */		
    long		symPtr;		/* File pointer to symbolic header. */	
    long		numSyms;	/* Size of symbolic header. */
    unsigned short	optHeader;	/* Size of optional header. */
    unsigned short	flags;		/* Flags. */
} ProcFileHeader;

/*
 * A.out header.
 */
typedef struct {
    short		magic;		/* Magic number. */
    short		verStamp;	/* Version stamp. */
    long		codeSize;	/* Code size in bytes. */
    long		heapSize;	/* Initialized data size in bytes. */
    long		bssSize;	/* Uninitialized data size in bytes. */
    long		entry;		/* Entry point. */
    long		codeStart;	/* Base of code used for this file. */
    long		heapStart;	/* Base of heap used for this file. */
    long		bssStart;	/* Base of bss used for this file. */
    long		gprMask;	/* General purpose register mask. */
    long		cprMask[4];	/* Co-processor register masks. */
    long		gpValue;	/* The gp value for this object. */
} ProcAOUTHeader;

/*
 * Section header.
 */
typedef struct {
    char		name[8];	/* Section name. */
    long		physAddr;	/* Section physical address. */
    long		virtAddr;	/* Section virtual address. */
    long		size;		/* Section size. */
    long		sectionPtr;	/* File pointer to section data.  */
    long		relocPtr;	/* File pointer to relocation data.  */
    long		lnnoPtr;	/* File pointer to gp tables. */
    unsigned short	numReloc;	/* Number of relocation entries. */
    unsigned short	numLnno;	/* Numberof gp tables. */
    long		flags;		/* Section flags. */
} ProcSectionHeader;

/*
 * The header at the beginning of each file.
 */
struct exec {
    ProcFileHeader	ex_fhdr;
    ProcAOUTHeader	ex_aout;
};
#define a_magic	ex_aout.magic
#define a_text	ex_aout.codeSize
#define a_data	ex_aout.heapSize
#define a_bss	ex_aout.bssSize
#define a_entry	ex_aout.entry

/*
 * Determine the offset of the text segment in the file, given the header.
 * (This is the same function as N_TXTOFF)
 */
#define N_TXTOFF(hdr) \
    ( ((hdr).ex_aout.magic == ZMAGIC) ? 0 : \
	((sizeof(struct exec) + \
	    (hdr).ex_fhdr.numSections*sizeof(ProcSectionHeader) + \
	    ((hdr).ex_aout.verStamp < 23 ? 7 : 15)) & \
		~((long)(((hdr).ex_aout.verStamp < 23 ? 7 : 15))) ) )

#define N_DATAOFF(x) \
    (N_TXTOFF(x) + (x).ex_aout.codeSize)

#endif /* COFF */
E 9
#endif /* !_EXEC_H_ */
E 13
I 13
D 14
/* Compatibility file only. */
E 14
#include <machine/exec.h>
I 14

/*
 * The following structure is found at the top of the user stack of each
 * user process. The ps program uses it to locate argv and environment
 * strings. Programs that wish ps to display other information may modify
 * it; normally ps_argvstr points to the text for argv[0], and ps_nargvstr
 * is the same as the program's argc. The fields ps_envstr and ps_nenvstr
 * are the equivalent for the environment.
 */
struct ps_strings {
	char	*ps_argvstr;	/* first of 0 or more argument strings */
	int	ps_nargvstr;	/* the number of argument strings */
	char	*ps_envstr;	/* first of 0 or more environment strings */
	int	ps_nenvstr;	/* the number of environment strings */
};

/*
 * Address of ps_strings structure (in user space).
 */
#define	PS_STRINGS \
	((struct ps_strings *)(USRSTACK - sizeof(struct ps_strings)))
I 16
D 18

/*
 * Arguments to the exec system call.
 */
struct execve_args {
	char	*fname;
	char	**argp;
	char	**envp;
};
E 18
E 16
E 14
E 13
E 6
E 4
E 1
