h07187
s 00002/00002/00198
d D 8.1 93/06/11 14:58:49 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00200/00000/00000
d D 7.1 92/06/04 16:03:07 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Define the instruction formats and opcode values for the
 * MIPS instruction set.
 */

/*
 * Define the instruction formats.
 */
typedef union {
	unsigned word;

#if BYTE_ORDER == LITTLE_ENDIAN
	struct {
		unsigned imm: 16;
		unsigned rt: 5;
		unsigned rs: 5;
		unsigned op: 6;
	} IType;

	struct {
		unsigned target: 26;
		unsigned op: 6;
	} JType;

	struct {
		unsigned func: 6;
		unsigned shamt: 5;
		unsigned rd: 5;
		unsigned rt: 5;
		unsigned rs: 5;
		unsigned op: 6;
	} RType;

	struct {
		unsigned func: 6;
		unsigned fd: 5;
		unsigned fs: 5;
		unsigned ft: 5;
		unsigned fmt: 4;
		unsigned : 1;		/* always '1' */
		unsigned op: 6;		/* always '0x11' */
	} FRType;
#endif
#if BYTE_ORDER == BIG_ENDIAN
	struct {
		unsigned op: 6;
		unsigned rs: 5;
		unsigned rt: 5;
		unsigned imm: 16;
	} IType;

	struct {
		unsigned op: 6;
		unsigned target: 26;
	} JType;

	struct {
		unsigned op: 6;
		unsigned rs: 5;
		unsigned rt: 5;
		unsigned rd: 5;
		unsigned shamt: 5;
		unsigned func: 6;
	} RType;

	struct {
		unsigned op: 6;		/* always '0x11' */
		unsigned : 1;		/* always '1' */
		unsigned fmt: 4;
		unsigned ft: 5;
		unsigned fs: 5;
		unsigned fd: 5;
		unsigned func: 6;
	} FRType;
#endif
} InstFmt;

/*
 * Values for the 'op' field.
 */
#define OP_SPECIAL	000
#define OP_BCOND	001
#define OP_J		002
#define	OP_JAL		003
#define OP_BEQ		004
#define OP_BNE		005
#define OP_BLEZ		006
#define OP_BGTZ		007

#define OP_ADDI		010
#define OP_ADDIU	011
#define OP_SLTI		012
#define OP_SLTIU	013
#define OP_ANDI		014
#define OP_ORI		015
#define OP_XORI		016
#define OP_LUI		017

#define OP_COP0		020
#define OP_COP1		021
#define OP_COP2		022
#define OP_COP3		023

#define OP_LB		040
#define OP_LH		041
#define OP_LWL		042
#define OP_LW		043
#define OP_LBU		044
#define OP_LHU		045
#define OP_LWR		046

#define OP_SB		050
#define OP_SH		051
#define OP_SWL		052
#define OP_SW		053
#define OP_SWR		056

#define OP_LWC0		060
#define OP_LWC1		061
#define OP_LWC2		062
#define OP_LWC3		063

#define OP_SWC0		070
#define OP_SWC1		071
#define OP_SWC2		072
#define OP_SWC3		073

/*
 * Values for the 'func' field when 'op' == OP_SPECIAL.
 */
#define OP_SLL		000
#define OP_SRL		002
#define OP_SRA		003
#define OP_SLLV		004
#define OP_SRLV		006
#define OP_SRAV		007

#define OP_JR		010
#define OP_JALR		011
#define OP_SYSCALL	014
#define OP_BREAK	015

#define OP_MFHI		020
#define OP_MTHI		021
#define OP_MFLO		022
#define OP_MTLO		023

#define OP_MULT		030
#define OP_MULTU	031
#define OP_DIV		032
#define OP_DIVU		033

#define OP_ADD		040
#define OP_ADDU		041
#define OP_SUB		042
#define OP_SUBU		043
#define OP_AND		044
#define OP_OR		045
#define OP_XOR		046
#define OP_NOR		047

#define OP_SLT		052
#define OP_SLTU		053

/*
 * Values for the 'func' field when 'op' == OP_BCOND.
 */
#define OP_BLTZ		000
#define OP_BGEZ		001
#define OP_BLTZAL	020
#define OP_BGEZAL	021

/*
 * Values for the 'rs' field when 'op' == OP_COPz.
 */
#define OP_MF		000
#define OP_MT		004
#define OP_BCx		010
#define OP_BCy		014
#define OP_CF		002
#define OP_CT		006

/*
 * Values for the 'rt' field when 'op' == OP_COPz.
 */
#define COPz_BC_TF_MASK	0x01
#define COPz_BC_TRUE	0x01
#define COPz_BC_FALSE	0x00
E 1
