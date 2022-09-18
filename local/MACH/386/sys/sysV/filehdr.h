/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	filehdr.h,v $
 * Revision 2.5  89/05/30  13:28:48  rvb
 * 	Various additions, most important the Mips magic numbers.
 * 	[89/04/20            af]
 * 
 * Revision 2.4  89/03/09  22:11:34  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  20:09:43  gm0w
 * 	Changes for cleanup.
 * 
 */
/*	5.2 SID filehdr.h	2.3 1/19/83 */

struct filehdr {
	unsigned short	f_magic;	/* magic number */
	unsigned short	f_nscns;	/* number of sections */
	long		f_timdat;	/* time & date stamp */
	long		f_symptr;	/* file pointer to symtab */
	long		f_nsyms;	/* number of symtab entries */
	unsigned short	f_opthdr;	/* sizeof(optional hdr) */
	unsigned short	f_flags;	/* flags */
	};

#define FILHDR	struct filehdr
#define FILHSZ	sizeof(FILHDR)
#define N16FILHSZ	(FILHSZ+8)

/*
 *   Bits for f_flags:
 *
 *	F_RELFLG	relocation info stripped from file
 *	F_EXEC		file is executable  (i.e. no unresolved
 *				externel references)
 *	F_LNNO		line nunbers stripped from file
 *	F_LSYMS		local symbols stripped from file
 *	F_MINMAL	this is a minimal object file (".m") output of fextract
 *	F_UPDATE	this is a fully bound update file, output of ogen
 *	F_SWABD		this file has had its bytes swabbed (in names)
 *	F_AR16WR	this file has the byte ordering of an AR16WR (e.g. 11/70) machine
 *				(it was created there, or was produced by conv)
 *	F_AR32WR	this file has the byte ordering of an AR32WR machine(e.g. vax)
 *	F_AR32W		this file has the byte ordering of an AR32W machine (e.g. 3b,maxi)
 *	F_PATCH		file contains "patch" list in optional header
 *	F_NODF		(minimal file only) no decision functions for
 *				replaced functions
 */

#define  F_RELFLG	0000001
#define  F_EXEC		0000002
#define  F_LNNO		0000004
#define  F_LSYMS	0000010
#define  F_MINMAL	0000020
#define  F_UPDATE	0000040
#define  F_SWABD	0000100
#define  F_AR16WR	0000200
#define  F_AR32WR	0000400
#define  F_AR32W	0001000
#define  F_PATCH	0002000
#define  F_NODF		0002000

/*
 *	Flags for the INTEL chips.  If the magic number of the object file
 *	is IAPX16 or IAPX16TV or IAPX20 or IAPX20TV then if F_80186
 *	is set, there are some 80186 instructions in the code, and hence
 *	and 80186 or 80286 chip must be used to run the code.
 *	If F_80286 is set, then the code has to be run on an 80286 chip.
 *	And if neither are set, then the code can run on an 8086, 80186, or
 *	80286 chip.
 *	
 */

#define F_80186		010000
#define F_80286		020000


/*
 *   Magic Numbers
 */

	/* Basic-16 */

#define  B16MAGIC	0502
#define  BTVMAGIC	0503

	/* Intel */

#define  IAPX16		0504
#define  IAPX16TV	0505
#define  IAPX20		0506
#define  IAPX20TV	0507
/* 0514, 0516 and 0517 reserved for Intel */

	/* x86 */

#define  X86MAGIC	0510
#define  XTVMAGIC	0511


	/* Intel 286 */
#define I286SMAGIC	0512
#define I286LMAGIC	0522	/* used by mc68000 (UNIX PC) and iAPX 286 */

	/* Intel 386 */

#define  I386MAGIC	0514
	/* n3b */
/*
 *   NOTE:   For New 3B, the old values of magic numbers
 *		will be in the optional header in the structure
 *		"aouthdr" (identical to old 3B aouthdr).
 */
#define  N3BMAGIC	0550
#define  NTVMAGIC	0551

	/*  XL  */
#define	 XLMAGIC	0540

	/* Mips */

#define  MIPSEBMAGIC	0540	/* BE byte order */
#define  MIPSELMAGIC	0542	/* LE byte order */

	/*  MAC-32   3b-5  */

#define  FBOMAGIC	0560
#define  RBOMAGIC	0562
#define  MTVMAGIC	0561


	/* VAX 11/780 and VAX 11/750 */

			/* writeable text segments */
#define VAXWRMAGIC	0570
			/* readonly sharable text segments */
#define VAXROMAGIC	0575

	/* National Semiconductor NS16000 (becoming obsolete) */
#define N16WRMAGIC	0510
#define N16ROMAGIC	0515

	/* National Semiconductor NS32000 */
#define NS32GMAGIC	0524
#define NS32SMAGIC	0525

	/* Motorola 68000/68008/68010/68020 */
#define	MC68MAGIC	0520
#define MC68KWRMAGIC	0520	/* writeable text segments */
#define	MC68TVMAGIC	0521
#define MC68KROMAGIC	0521	/* readonly shareable text segments */
#define MC68KPGMAGIC	0522	/* demand paged text segments */
#define	M68MAGIC	0210
#define	M68TVMAGIC	0211

	/* IBM 370 */
#define U370WRMAGIC	0530	/* writeble text segments	*/
#define U370ROMAGIC	0535	/* readonly sharable text segments	*/
/* 0532 and 0533 reserved for u370 */

	/* Amdahl 470/580 */
#define AMDWRMAGIC	0531	/* writable text segments */
#define AMDROMAGIC	0534	/* readonly sharable text segments */

	/* NSC */
/* 0524 and 0525 reserved for NSC */

	/* Zilog */
/* 0544 and 0545 reserved for Zilog */


