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

#if	defined(sun3) || defined(sun4)
	unsigned short  a_machtype;     /* machine type */
	unsigned short  a_magic;        /* magic number */
#else	defined(sun3) || defined(sun4)
	long	a_magic;	/* magic number */
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

/*
 * for compatibility
 */
#define a_data	ex_o.dsize
#define a_text	ex_o.tsize
#define a_bss	ex_o.bsize
#define a_entry	ex_o.entry
#define a_magic	ex_o.magic	/* Will be [ONZ]MAGIC */

#endif	mips

#if	defined(sun3) || defined(sun4)
/* Sun machine types */

#define M_OLDSUN2	0	/* old sun-2 executable files */
#define M_68010		1	/* runs on either 68010 or 68020 */
#define M_68020		2	/* runs only on 68020 */
#endif	defined(sun3) || defined(sun4)

#endif	_SYS_EXEC_H_
