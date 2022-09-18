h15607
s 00002/00002/00042
d D 8.1 93/06/10 23:02:57 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00033/00001/00011
d D 7.2 93/02/04 19:40:31 ralph 2 1
c real reloc.h for a.out format and gcc.
e
s 00012/00000/00000
d D 7.1 92/03/18 16:34:25 bostic 1 0
c date and time created 92/03/18 16:34:25 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
I 2
 *
 * from: $Header: reloc.h,v 1.6 92/06/20 09:59:37 torek Exp $
E 2
 */

/*
D 2
 * There is currently no relocation information for the MIPS.
E 2
I 2
 * MIPS relocation types.
E 2
 */
I 2
enum reloc_type {
	MIPS_RELOC_32,		/* 32-bit absolute */
	MIPS_RELOC_JMP,		/* 26-bit absolute << 2 | high 4 bits of pc */
	MIPS_RELOC_WDISP16,	/* 16-bit signed pc-relative << 2 */
	MIPS_RELOC_HI16,	/* 16-bit absolute << 16 */
	MIPS_RELOC_HI16_S,	/* 16-bit absolute << 16 (+1 if needed) */
	MIPS_RELOC_LO16,	/* 16-bit absolute */
};

/*
 * MIPS relocation info.
 *
 * Symbol-relative relocation is done by:
 *	1. start with the value r_addend,
 *	2. locate the appropriate symbol and if defined, add symbol value,
 *	3. if pc relative, subtract pc,
 *	4. if the reloc_type is MIPS_RELOC_HI16_S and the result bit 15 is set,
 *		add 0x00010000,
 *	5. shift down 2 or 16 if necessary.
 * The resulting value is then to be stuffed into the appropriate bits
 * in the object (the low 16, or the low 26 bits).
 */
struct reloc_info_mips {
	u_long	r_address;	/* relocation addr (offset in segment) */
	u_int	r_index:24,	/* segment (r_extern==0) or symbol index */
		r_extern:1,	/* if set, r_index is symbol index */
		:2;		/* unused */
	enum reloc_type r_type:5; /* relocation type, from above */
	long	r_addend;	/* value to add to symbol value */
};
E 2
E 1
