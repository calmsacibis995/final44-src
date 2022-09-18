h03887
s 00011/00001/00117
d D 7.1 90/12/06 13:37:52 bostic 3 2
c add Berkeley specific copyright notice
e
s 00001/00001/00117
d D 1.2 90/12/04 22:40:23 bostic 2 1
c /sys/tahoealign -> /sys/tahoe/align
e
s 00118/00000/00000
d D 1.1 86/07/20 11:13:48 sam 1 0
c date and time created 86/07/20 11:13:48 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*-
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 3

D 2
#include "../tahoe/psl.h"
E 2
I 2
#include "../include/psl.h"
E 2

/************************************************/
/*	Basic 6/32 machine definitions 		*/
/************************************************/

#define	FALSE	0
#define	TRUE	(~FALSE)
#define READ	0
#define WRITE	1

/*
 * Some floatng point stuff.
 */

#define exp(x)		( (x) & 0x7f800000 )
#define reserved(x) 	( (x) < 0  && (exp(x) == 0) )

/************************************************/
/*						*/
/*	Opcodes description table stuff		*/
/*						*/
/************************************************/

struct	operand_des	{		/* Operand descriptor in great table */
		int	add_modes;	/* Allowed addressing modes */
		int	length;		/* Length of this data (bytes) */
};

#define	Add	1	/* Any address except PC relative & ablsolute */
#define	Dir	2	/* Direct register */
#define	Imm	4	/* Immediate datum */
#define	Lit	8	/* Short literal */
#define	Brd	0x10	/* Branch displacement */
#define	Pcrel	0x20	/* PC relative allowed */
#define	Abs	0x40	/* Absolute address allowed */
#define	SPmode	0x80	/* The stack pointer was involved , -(sp) or (sp)+ */
#define	ADDFIELD 0xff	/* Allowed addressing modes */

#define	W	0x100	/* Access is write */
#define R	0x200	/* Access is 'read' */
#define	Indx	0x400	/* Indexable base address */
#define	NOVF	0x800	/* Inhibit overflow check when writing byte/word */
#define FLP	0x1000	/* Floating point operand */

#define	M	(R|W)	/* Access is 'modify' */
#define PR	(Pcrel|Abs)
#define ADDR	(PR|Add)
#define	ADI	(ADDR|Dir|Imm|Lit)
#define	AD	(ADDR|Dir)
#define	MAD	(M|ADDR|Dir)
#define	WAD	(W|ADDR|Dir)
#define WD	(W|Dir)
#define NWAD	(NOVF|WAD)
#define	NMAD	(NOVF|MAD)
#define	RADI	(R|ADI)	/* Readable datum */
#define RAD	(R|AD)	/* Modify type access for destinations */
#define RADF	(RAD|FLP)
#define WADF	(WAD|FLP)




struct	opcode_des	{	/* One line in the big table */
	int 	(*routine) 	();		/* Handler for this opcode */
	struct 	operand_des operand[4];		/* Up to 4 operands */
};

/************************************************/
/*						*/
/*	Operand descriptor as returned		*/
/*	by the address mode decoder 		*/
/*						*/
/************************************************/

struct	oprnd {
	long	mode;			/* Add, Imm, Dir or Brd */
	long	reg_number;		/* returned for Dir mode */
	long	address;		/* Relevant for Add or Brd */
	long	data;
	long	data2;			/* Up to 8 bytes returned */
	long	length;			/* Length of data manipulated */
};

/************************************************/
/*						*/
/*	Some PSL macros (usefull)		*/
/*						*/
/************************************************/
#define	carry		(psl & PSL_C)
#define	negative	(psl & PSL_N)
#define overflow	(psl & PSL_V)
#define zero		(psl & PSL_Z)

#define carry_1		psl |= PSL_C
#define negative_1	psl |= PSL_N
#define overflow_1	psl |= PSL_V
#define zero_1		psl |= PSL_Z

#define carry_0		psl &= ~PSL_C
#define negative_0	psl &= ~PSL_N
#define overflow_0	psl &= ~PSL_V
#define zero_0		psl &= ~PSL_Z


struct	oprnd		*operand ();
struct	opcode_des 	Table[];

struct double_length
{
	int	low;
	int	high;
};

typedef	struct	double_length	quadword;

E 1
