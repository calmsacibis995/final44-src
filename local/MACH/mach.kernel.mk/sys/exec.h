/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	exec.h,v $
 * Revision 2.9  91/04/03  13:14:57  mbj
 * 	Omron changes[sic]
 * 
 * Revision 2.8  90/08/30  11:50:02  bohman
 * 	Changes for mac2.
 * 	[90/08/28            bohman]
 * 
 * Revision 2.7  90/04/26  15:10:13  mja
 * 	Picked up changes for exec header for Suns, splitting machine type
 * 	short field into two character fields.
 * 	[90/04/17  21:11:41  jjc]
 * 
 * 	Added definition of M_SPARC.
 * 	[90/04/17            jjc]
 * 
 * Revision 2.6  90/03/09  13:09:48  af
 * 	Added (optional) definition of the coff_exec structure and
 * 	related definitions to help porting BSD user programs to
 * 	coff-based architectures.
 * 	[90/03/09            af]
 * 
 * Revision 2.5  89/05/30  10:42:59  rvb
 * 	Keyed byteorder dependencies on BYTE_MFS.
 * 	[89/05/18            af]
 * 
 * Revision 2.4  89/03/09  22:03:50  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  17:53:12  gm0w
 * 	Changed #ifdef sun to #if defined(sun3) || defined(sun4)
 * 	[89/02/13            mrt]
 * 
 * Revision 2.2  89/01/23  22:25:47  af
 * 	Added definitions for Mips.  Might be extended to cover all COFF
 * 	based systems.
 * 	[89/01/09            af]
 * 
 * 12-Sep-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Changed first long word to two shorts for the Sun to give
 *	the machine type along with the magic number.
 *	Added machine types for Sun.
 *	Made file includable more than once.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)exec.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_SYS_EXEC_H_
#define _SYS_EXEC_H_

/*
 * Header prepended to each a.out file.
 */

#if	!defined(mips)

struct exec {

#if	defined(sun3) || defined(sun4) || defined(luna)
	unsigned char	a_dynamic:1;	/* has a __DYNAMIC */
	unsigned char	a_toolversion:7;/* version of toolset used to create this file */
	unsigned char	a_machtype;     /* machine type */
	unsigned short  a_magic;        /* magic number */
#else	defined(sun3) || defined(sun4)
#if	defined(mac2)
	unsigned short	a_machtype,	/* machine type and magic number */
			a_magic;
#else	defined(mac2)
	long	a_magic;	/* magic number */
#endif	defined(mac2)
#endif	defined(sun3) || defined(sun4)
	unsigned long	a_text;		/* size of text segment */
	unsigned long	a_data;		/* size of initialized data */
	unsigned long	a_bss;		/* size of uninitialized data */
	unsigned long	a_syms;		/* size of symbol table */
	unsigned long	a_entry;	/* entry point */
	unsigned long	a_trsize;	/* size of text relocation */
	unsigned long	a_drsize;	/* size of data relocation */
};
#endif	!defined(mips)


#define OMAGIC	0407		/* old impure format */
#define NMAGIC	0410		/* read-only text */
#define ZMAGIC	0413		/* demand load format */


#ifdef	mips

#if	BYTE_MSF
#define MIPSMAGIC	MIPSEBMAGIC
#else
#define MIPSMAGIC	MIPSELMAGIC
#endif
/*
 * The macro N_TXTOFF() takes pointers to file header
 * [struct filehdr*] and optional header [struct aouthdr *] and returns
 * the file offset to the start of the raw data for the .text section.
 * The raw data for the three data sections follows the start of the .text
 * section by the value of tsize in the optional header.
 */
/* SCNROUND is the size that section headers are rounded off to */
#define SCNROUND ((long)16)
#define OSCNRND  ((long)8)

#define N_TXTOFF(f, a) \
 ((a).magic == ZMAGIC ? 0 : \
  ((a).vstamp < 23 ? \
   ((FILHSZ + AOUTHSZ + (f).f_nscns * SCNHSZ + OSCNRND-1) & ~(OSCNRND-1)) : \
   ((FILHSZ + AOUTHSZ + (f).f_nscns * SCNHSZ + SCNROUND-1) & ~(SCNROUND-1))))

#endif	mips

#ifdef	COFF_EXEC
/*
 * for compatibility
 */
struct coff_exec {
	struct filehdr	f;
	struct aouthdr	a;
};
#define a_magic	a.magic	/* Will be [ONZ]MAGIC */
#define a_text	a.tsize
#define a_data	a.dsize
#define a_bss	a.bsize
#define a_entry	a.entry
#define a_syms	f.f_nsyms

#endif	COFF_EXEC

#if	defined(sun3) || defined(sun4)
/* Sun machine types */

#define M_OLDSUN2	0	/* old sun-2 executable files */
#define M_68010		1	/* runs on either 68010 or 68020 */
#define M_68020		2	/* runs only on 68020 */
#define M_SPARC		3	/* runs only on SPARC */
#endif	defined(sun3) || defined(sun4)

#if	defined(mac2)
#define M_68020		2	/* sun compatable: 68020/30 */
#endif	defined(mac2)

#ifdef luna
#define M_68010		0x0000		/* 68010 image */
#define M_68020		0x0001		/* 68020 image */
#define M_68881		0x0002		/* 68881 image */
#define M_88000		0x0004		/* 88000 image */
#endif luna

#endif	_SYS_EXEC_H_
