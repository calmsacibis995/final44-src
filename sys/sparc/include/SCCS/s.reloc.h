h49928
s 00002/00002/00075
d D 8.1 93/06/11 15:12:39 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00075
d D 7.3 93/04/20 18:54:40 torek 3 2
c spelling
e
s 00005/00000/00072
d D 7.2 92/07/21 16:41:38 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00072/00000/00000
d D 7.1 92/07/13 00:43:06 torek 1 0
c date and time created 92/07/13 00:43:06 by torek
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 3
 *	California, Lawrence Berkeley Laboratories.
E 3
I 3
 *	California, Lawrence Berkeley Laboratory.
E 3
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: reloc.h,v 1.6 92/06/20 09:59:37 torek Exp $
E 3
I 3
 * from: $Header: reloc.h,v 1.7 92/11/26 02:04:45 torek Exp $
E 3
 */

/*
 * SPARC relocations.  The linker has, unfortunately, a large number
 * of link types.  We do not do dynamic linking (yet?) but we define
 * the dynamic link types.
 */
enum reloc_type {
		/* architecturally-required types */
	RELOC_8,		/*  8-bit absolute */
	RELOC_16,		/* 16-bit absolute */
	RELOC_32,		/* 32-bit absolute */
	RELOC_DISP8,		/*  8-bit pc-relative */
	RELOC_DISP16,		/* 16-bit pc-relative */
	RELOC_DISP32,		/* 32-bit pc-relative */
	RELOC_WDISP30,		/* 30-bit pc-relative signed word */
	RELOC_WDISP22,		/* 22-bit pc-relative signed word */
	RELOC_HI22,		/* 22-bit `%hi' (ie, sethi %hi(X),%l0) */
	RELOC_22,		/* 22-bit non-%hi (i.e., sethi X,%l0) */
	RELOC_13,		/* 13-bit absolute */
	RELOC_LO10,		/* 10-bit `%lo' */

		/* gnu ld understands some of these, but I do not */
	RELOC_SFA_BASE,		/* ? */
	RELOC_SFA_OFF13,	/* ? */
	RELOC_BASE10,		/* ? */
	RELOC_BASE13,		/* ? */
	RELOC_BASE22,		/* ? */

		/* gnu ld does not use these but Sun linker does */
		/* we define them anyway (note that they are included
		   in the freely-available gas sources!) */
	RELOC_PC10,		/* ? */
	RELOC_PC22,		/* ? */
	RELOC_JMP_TBL,		/* ? */
	RELOC_SEGOFF16,		/* ? */
	RELOC_GLOB_DAT,		/* ? */
	RELOC_JMP_SLOT,		/* ? */
	RELOC_RELATIVE,		/* ? */
};

/*
 * SPARC relocation info.
 *
 * Symbol-relative relocation is done by:
 *	1. locating the appropriate symbol
 *	2. if defined, adding (value + r_addend), subtracting pc if pc-rel,
 *	   and then shifting down 2 or 10 or 13 if necessary.
 * The resulting value is then to be stuffed into the appropriate bits
 * in the object (the low 22, or the high 30, or ..., etc).
 */
struct reloc_info_sparc {
	u_long	r_address;	/* relocation addr (offset in segment) */
	u_int	r_index:24,	/* segment (r_extern==0) or symbol index */
		r_extern:1,	/* if set, r_index is symbol index */
		:2;		/* unused */
	enum reloc_type r_type:5; /* relocation type, from above */
	long	r_addend;	/* value to add to symbol value */
};
E 1
