/* 
 * Mach Operating System
 * Copyright (c) 1991,1990 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

/*
 * HISTORY
 * $Log:	db_disasm.c,v $
 * Revision 2.4  91/05/14  17:42:33  mrt
 * 	Correcting copyright
 * 
 * Revision 2.3  91/05/08  13:16:01  dbg
 * 	Re-fetch base register from operand specifier after finding
 * 	index register.
 * 	[91/04/25            dbg]
 * 
 * Revision 2.2  90/08/27  22:13:27  dbg
 * 	Use new symbol table declarations.  Change calling sequence
 * 	of db_disasm.
 * 	[90/08/20            dbg]
 * 	Fix type declarations.
 * 	[90/08/10  14:37:11  dbg]
 * 
 * 	Created.
 * 	[90/07/25            dbg]
 * 
 */

/*
 * Disassembler for VAX.
 */
#include <mach/boolean.h>
#include <machine/db_machdep.h>

#include <ddb/db_access.h>
#include <ddb/db_sym.h>

#define	get_value_inc(value, loc, size, is_signed) \
	{ (value) = db_get_value((loc), (size), (is_signed)); \
	  (loc) += (size); }

/*
 * Operand type codes
 */
#define	T_B	1	/* byte */
#define	T_W	2	/* word (16 bits) */
#define	T_L	3	/* longword (32 bits) */
#define	T_Q	4	/* quadword (64 bits) */
#define	T_O	5	/* octaword (128 bits) */
#define	T_F	6	/* F float (32 bits) */
#define	T_D	7	/* D float (64 bits) */
#define	T_G	8	/* G float (64 bits) */
#define	T_H	9	/* H float (128 bits) */

#define	T_X	0xf	/* extra (for casew) */
/*
 * Access type codes
 */
#define	A_A	1	/* address */
#define	A_B	2	/* branch displacment */
#define	A_M	3	/* modify */
#define	A_R	4	/* read */
#define	A_V	5	/* field */
#define	A_W	6	/* write */

#define	maketype(a,b)	(((a)<<4)|(b))
#define	opnd_type(o)	((o)&0xF)
#define	opnd_acc(o)	((o)>>4)

/*
 * Combined types
 */
#define	AB	maketype(A_A,T_B)
#define	AW	maketype(A_A,T_W)
#define	AL	maketype(A_A,T_L)
#define	AQ	maketype(A_A,T_Q)
#define	AO	maketype(A_A,T_O)
#define	AF	maketype(A_A,T_F)
#define	AD	maketype(A_A,T_D)
#define	AG	maketype(A_A,T_G)
#define	AH	maketype(A_A,T_H)

#define	BB	maketype(A_B,T_B)
#define	BW	maketype(A_B,T_W)

#define	CASEW	maketype(A_B,T_X)	/* case table */

#define	MB	maketype(A_M,T_B)
#define	MW	maketype(A_M,T_W)
#define	ML	maketype(A_M,T_L)
#define	MQ	maketype(A_M,T_Q)
#define	MO	maketype(A_M,T_O)
#define	MF	maketype(A_M,T_F)
#define	MD	maketype(A_M,T_D)
#define	MG	maketype(A_M,T_G)
#define	MH	maketype(A_M,T_H)

#define	RB	maketype(A_R,T_B)
#define	RW	maketype(A_R,T_W)
#define	RL	maketype(A_R,T_L)
#define	RQ	maketype(A_R,T_Q)
#define	RO	maketype(A_R,T_O)
#define	RF	maketype(A_R,T_F)
#define	RD	maketype(A_R,T_D)
#define	RG	maketype(A_R,T_G)
#define	RH	maketype(A_R,T_H)

#define	WB	maketype(A_W,T_B)
#define	WW	maketype(A_W,T_W)
#define	WL	maketype(A_W,T_L)
#define	WQ	maketype(A_W,T_Q)
#define	WO	maketype(A_W,T_O)
#define	WF	maketype(A_W,T_F)
#define	WD	maketype(A_W,T_D)
#define	WG	maketype(A_W,T_G)
#define	WH	maketype(A_W,T_H)

#define	VB	maketype(A_V,T_B)
#define	VW	maketype(A_V,T_W)
#define	VL	maketype(A_V,T_L)

#define	MAXNARGS	6

struct inst {
	char	*opcode;
	int	fmt[MAXNARGS+1];
};

struct inst	inst_table[256] = {
/*00*/	{ "halt",	{0}},
/*01*/	{ "nop",	{0}},
/*02*/	{ "rei",	{0}},
/*03*/	{ "bpt",	{0}},
/*04*/	{ "ret",	{0}},
/*05*/	{ "rsb",	{0}},
/*06*/	{ "ldpctx",	{0}},
/*07*/	{ "svpctx",	{0}},
/*08*/	{ "cvtps",	{ RW, AB, RW, AB }},
/*09*/	{ "cvtsp",	{ RW, AB, RW, AB }},
/*0a*/	{ "index",	{ RL, RL, RL, RL, RL, WL }},
/*0b*/	{ "crc",	{ AB, RL, RW, AB }},
/*0c*/	{ "prober",	{ RB, RW, AB }},
/*0d*/	{ "probew",	{ RB, RW, AB }},
/*0e*/	{ "insque",	{ AB, AB }},
/*0f*/	{ "remque",	{ AB, WL }},

/*10*/	{ "bsbb",	{ BB }},
/*11*/	{ "brb",	{ BB }},
/*12*/	{ "bneq",	{ BB }},
/*13*/	{ "beql",	{ BB }},
/*14*/	{ "bgtr",	{ BB }},
/*15*/	{ "bleq",	{ BB }},
/*16*/	{ "jsb",	{ AB }},
/*17*/	{ "jmp",	{ AB }},
/*18*/	{ "bgeq",	{ BB }},
/*19*/	{ "blss",	{ BB }},
/*1a*/	{ "bgtru",	{ BB }},
/*1b*/	{ "blequ",	{ BB }},
/*1c*/	{ "bvc",	{ BB }},
/*1d*/	{ "bvs",	{ BB }},
/*1e*/	{ "bgequ",	{ BB }},
/*1f*/	{ "blssu",	{ BB }},

/*20*/	{ "addp4",	{ RW, AB, RW, AB }},
/*21*/	{ "addp6",	{ RW, AB, RW, AB, RW, AB }},
/*22*/	{ "subp4",	{ RW, AB, RW, AB }},
/*23*/	{ "subp6",	{ RW, AB, RW, AB, RW, AB }},
/*24*/	{ "cvtpt",	{ RW, AB, AB, RW, AB }},
/*25*/	{ "mulp",	{ RW, AB, RW, AB, RW, AB }},
/*26*/	{ "cvttp",	{ RW, AB, AB, RW, AB }},
/*27*/	{ "divp",	{ RW, AB, RW, AB, RW, AB }},
/*28*/	{ "movc3",	{ RW, AB, AB }},
/*29*/	{ "cmpc3",	{ RW, AB, AB }},
/*2a*/	{ "scanc",	{ RW, AB, AB, RB }},
/*2b*/	{ "spanc",	{ RW, AB, AB, RB }},
/*2c*/	{ "movc5",	{ RW, AB, RB, RW, AB }},
/*2d*/	{ "cmpc5",	{ RW, AB, RB, RW, AB }},
/*2e*/	{ "movtc",	{ RW, AB, RB, AB, RW, AB }},
/*2f*/	{ "movtuc",	{ RW, AB, RB, AB, RW, AB }},

/*30*/	{ "bsbw",	{ BW }},
/*31*/	{ "brw",	{ BW }},
/*32*/	{ "cvtwl",	{ RW, WL }},
/*33*/	{ "cvtwb",	{ RW, WB }},
/*34*/	{ "movp",	{ RW, AB, AB }},
/*35*/	{ "cmpp3",	{ RW, AB, AB }},
/*36*/	{ "cvtpl",	{ RW, AB, WL }},
/*37*/	{ "cmpp4",	{ RW, AB, RW, AB }},
/*38*/	{ "editpc",	{ RW, AB, AB, AB }},
/*39*/	{ "matchc",	{ RW, AB, RW, AB }},
/*3a*/	{ "locc",	{ RB, RW, AB }},
/*3b*/	{ "skpc",	{ RB, RW, AB }},
/*3c*/	{ "movzwl",	{ RW, WL }},
/*3d*/	{ "acbw",	{ RW, RW, MW, BW }},
/*3e*/	{ "movaw",	{ AW, WL }},
/*3f*/	{ "pushaw",	{ AW }},

/*40*/	{ "addf2",	{ RF, MF }},
/*41*/	{ "addf3",	{ RF, RF, WF }},
/*42*/	{ "subf2",	{ RF, MF }},
/*43*/	{ "subf3",	{ RF, RF, WF }},
/*44*/	{ "mulf2",	{ RF, MF }},
/*45*/	{ "mulf3",	{ RF, RF, WF }},
/*46*/	{ "divf2",	{ RF, MF }},
/*47*/	{ "divf3",	{ RF, RF, WF }},
/*48*/	{ "cvtfb",	{ RF, WB }},
/*49*/	{ "cvtfw",	{ RF, WW }},
/*4a*/	{ "cvtfl",	{ RF, WL }},
/*4b*/	{ "cvtrfl",	{ RF, WL }},
/*4c*/	{ "cvtbf",	{ RB, WF }},
/*4d*/	{ "cvtwf",	{ RW, WF }},
/*4e*/	{ "cvtlf",	{ RL, WF }},
/*4f*/	{ "acbf",	{ RF, RF, MF, BW }},

/*50*/	{ "movf",	{ RF, WF }},
/*51*/	{ "cmpf",	{ RF, RF }},
/*52*/	{ "mnegf",	{ RF, WF }},
/*53*/	{ "tstf",	{ RF }},
/*54*/	{ "emodf",	{ RF, RB, RF, WL, WF }},
/*55*/	{ "polyf",	{ RF, RW, AB }},
/*56*/	{ "cvtfd",	{ RF, WD }},
/*57*/	{ 0,		},
/*58*/	{ "adawi",	{ RW, MW }},
/*59*/	{ 0,		},
/*5a*/	{ 0,		},
/*5b*/	{ 0,		},
/*5c*/	{ "insqhi",	{ AB, AQ }},
/*5d*/	{ "insqti",	{ AB, AQ }},
/*5e*/	{ "remqhi",	{ AQ, WL }},
/*5f*/	{ "remqti",	{ AQ, WL }},

/*60*/	{ "addd2",	{ RD, MD }},
/*61*/	{ "addd3",	{ RD, RD, WD }},
/*62*/	{ "subd2",	{ RD, MD }},
/*63*/	{ "subd3",	{ RD, RD, WD }},
/*64*/	{ "muld2",	{ RD, MD }},
/*65*/	{ "muld3",	{ RD, RD, WD }},
/*66*/	{ "divd2",	{ RD, MD }},
/*67*/	{ "divd3",	{ RD, RD, WD }},
/*68*/	{ "cvtdb",	{ RD, WB }},
/*69*/	{ "cvtdw",	{ RD, WW }},
/*6a*/	{ "cvtdl",	{ RD, WL }},
/*6b*/	{ "cvtrdl",	{ RD, WL }},
/*6c*/	{ "cvtbd",	{ RB, WD }},
/*6d*/	{ "cvtwd",	{ RW, WD }},
/*6e*/	{ "cvtld",	{ RL, WD }},
/*6f*/	{ "acbd",	{ RD, RD, MD, BW }},

/*70*/	{ "movd",	{ RD, WD }},
/*71*/	{ "cmpd",	{ RD, RD }},
/*72*/	{ "mnegd",	{ RD, WD }},
/*73*/	{ "tstd",	{ RD }},
/*74*/	{ "emodd",	{ RD, RB, RD, WL, WD }},
/*75*/	{ "polyd",	{ RD, RW, AB }},
/*76*/	{ "cvtdf",	{ RD, WF }},
/*77*/	{ 0,		},
/*78*/	{ "ashl",	{ RB, RL, WL }},
/*79*/	{ "ashq",	{ RB, RQ, WQ }},
/*7a*/	{ "emul",	{ RL, RL, RL, WQ }},
/*7b*/	{ "ediv",	{ RL, RQ, WL, WL }},
/*7c*/	{ "clrq",	{ WQ }},
/*7d*/	{ "movq",	{ RQ, WQ }},
/*7e*/	{ "movaq",	{ AQ, WL }},
/*7f*/	{ "pushaq",	{ AQ }},

/*80*/	{ "addb2",	{ RB, MB }},
/*81*/	{ "addb3",	{ RB, RB, WB }},
/*82*/	{ "subb2",	{ RB, MB }},
/*83*/	{ "subb3",	{ RB, RB, WB }},
/*84*/	{ "mulb2",	{ RB, MB }},
/*85*/	{ "mulb3",	{ RB, RB, WB }},
/*86*/	{ "divb2",	{ RB, MB} },
/*87*/	{ "divb3",	{ RB, RB, WB }},
/*88*/	{ "bisb2",	{ RB, MB }},
/*89*/	{ "bisb3",	{ RB, RB, WB }},
/*8a*/	{ "bicb2",	{ RB, MB }},
/*8b*/	{ "bicb3",	{ RB, RB, WB }},
/*8c*/	{ "xorb2",	{ RB, MB }},
/*8d*/	{ "xorb3",	{ RB, RB, WB }},
/*8e*/	{ "mnegb",	{ RB, WB }},
/*8f*/	{ "caseb",	{ RB, RB, RB, CASEW }},

/*90*/	{ "movb",	{ RB, WB }},
/*91*/	{ "cmpb",	{ RB, RB }},
/*92*/	{ "mcomb",	{ RB, WB }},
/*93*/	{ "bitb",	{ RB, RB }},
/*94*/	{ "clrb",	{ WB }},
/*95*/	{ "tstb",	{ RB }},
/*96*/	{ "incb",	{ MB }},
/*97*/	{ "decb",	{ MB }},
/*98*/	{ "cvtbl",	{ RB, WL }},
/*99*/	{ "cvtbw",	{ RB, WW }},
/*9a*/	{ "movzbl",	{ RB, WL }},
/*9b*/	{ "movzbw",	{ RB, WW }},
/*9c*/	{ "rotl",	{ RB, RL, WL }},
/*9d*/	{ "acbb",	{ RB, RB, MB, BW }},
/*9e*/	{ "movab",	{ AB, WL }},
/*9f*/	{ "pushab",	{ AB }},

/*a0*/	{ "addw2",	{ RW, MW }},
/*a1*/	{ "addw3",	{ RW, RW, WW }},
/*a2*/	{ "subw2",	{ RW, MW }},
/*a3*/	{ "subw3",	{ RW, RW, WW }},
/*a4*/	{ "mulw2",	{ RW, MW }},
/*a5*/	{ "mulw3",	{ RW, RW, WW }},
/*a6*/	{ "divw2",	{ RW, MW }},
/*a7*/	{ "divw3",	{ RW, RW, WW }},
/*a8*/	{ "bisw2",	{ RW, MW }},
/*a9*/	{ "bisw3",	{ RW, RW, WW }},
/*aa*/	{ "bicw2",	{ RW, MW }},
/*ab*/	{ "bicw3",	{ RW, RW, WW }},
/*ac*/	{ "xorw2",	{ RW, MW }},
/*ad*/	{ "xorw3",	{ RW, RW, WW }},
/*ae*/	{ "mnegw",	{ RW, WW }},
/*af*/	{ "casew",	{ RW, RW, RW, CASEW }},

/*b0*/	{ "movw",	{ RW, WW }},
/*b1*/	{ "cmpw",	{ RW, RW }},
/*b2*/	{ "mcomw",	{ RW, WW }},
/*b3*/	{ "bitw",	{ RW, RW }},
/*b4*/	{ "clrw",	{ WW }},
/*b5*/	{ "tstw",	{ RW }},
/*b6*/	{ "incw",	{ MW }},
/*b7*/	{ "decw",	{ MW }},
/*b8*/	{ "bispsw",	{ RW }},
/*b9*/	{ "bicpsw",	{ RW }},
/*ba*/	{ "popr",	{ RW }},
/*bb*/	{ "pushr",	{ RW }},
/*bc*/	{ "chmk",	{ RW }},
/*bd*/	{ "chme",	{ RW }},
/*be*/	{ "chms",	{ RW }},
/*bf*/	{ "chmu",	{ RW }},

/*c0*/	{ "addl2",	{ RL, ML }},
/*c1*/	{ "addl3",	{ RL, RL, WL }},
/*c2*/	{ "subl2",	{ RL, ML }},
/*c3*/	{ "subl3",	{ RL, RL, WL }},
/*c4*/	{ "mull2",	{ RL, ML }},
/*c5*/	{ "mull3",	{ RL, RL, WL }},
/*c6*/	{ "divl2",	{ RL, ML }},
/*c7*/	{ "divl3",	{ RL, RL, WL }},
/*c8*/	{ "bisl2",	{ RL, ML }},
/*c9*/	{ "bisl3",	{ RL, RL, WL }},
/*ca*/	{ "bicl2",	{ RL, ML }},
/*cb*/	{ "bicl3",	{ RL, RL, WL }},
/*cc*/	{ "xorl2",	{ RL, ML }},
/*cd*/	{ "xorl3",	{ RL, RL, WL }},
/*ce*/	{ "mnegl",	{ RL, WL }},
/*cf*/	{ "casel",	{ RL, RL, RL, CASEW }},

/*d0*/	{ "movl",	{ RL, WL }},
/*d1*/	{ "cmpl",	{ RL, RL }},
/*d2*/	{ "mcoml",	{ RL, WL }},
/*d3*/	{ "bitl",	{ RL, RL }},
/*d4*/	{ "clrl",	{ WL }},
/*d5*/	{ "tstl",	{ RL }},
/*d6*/	{ "incl",	{ ML }},
/*d7*/	{ "decl",	{ ML }},
/*d8*/	{ "adwc",	{ RL, ML }},
/*d9*/	{ "sbwc",	{ RL, ML }},
/*da*/	{ "mtpr",	{ RL, RL }},
/*db*/	{ "mfpr",	{ RL, WL }},
/*dc*/	{ "movpsl",	{ WL }},
/*dd*/	{ "pushl",	{ RL }},
/*de*/	{ "moval",	{ AL, WL }},
/*df*/	{ "pushal",	{ AL }},

/*e0*/	{ "bbs",	{ RL, VB, BB }},
/*e1*/	{ "bbc",	{ RL, VB, BB }},
/*e2*/	{ "bbss",	{ RL, VB, BB }},
/*e3*/	{ "bbcs",	{ RL, VB, BB }},
/*e4*/	{ "bbsc",	{ RL, VB, BB }},
/*e5*/	{ "bbcc",	{ RL, VB, BB }},
/*e6*/	{ "bbssi",	{ RL, VB, BB }},
/*e7*/	{ "bbcci",	{ RL, VB, BB }},
/*e8*/	{ "blbs",	{ RL, BB }},
/*e9*/	{ "blbc",	{ RL, BB }},
/*ea*/	{ "ffs",	{ RL, RB, VL, WL }},
/*eb*/	{ "ffc",	{ RL, RB, VL, WL }},
/*ec*/	{ "cmpv",	{ RL, RB, VB, RL }},
/*ed*/	{ "cmpzv",	{ RL, RB, VB, RL }},
/*ee*/	{ "extv",	{ RL, RB, VB, WL }},
/*ef*/	{ "extzv",	{ RL, RB, VB, WL }},

/*f0*/	{ "insv",	{ RL, RL, RB, VB }},
/*f1*/	{ "acbl",	{ RL, RL, ML, BW }},
/*f2*/	{ "aoblss",	{ RL, ML, BB }},
/*f3*/	{ "aobleq",	{ RL, ML, BB }},
/*f4*/	{ "sobgeq",	{ ML, BB }},
/*f5*/	{ "sobgtr",	{ ML, BB }},
/*f6*/	{ "cvtlb",	{ RL, WB }},
/*f7*/	{ "cvtlw",	{ RL, WW }},
/*f8*/	{ "ashp",	{ RB, RW, AB, RB, RW, AB }},
/*f9*/	{ "cvtlp",	{ RL, RW, AB }},
/*fa*/	{ "callg",	{ AB, AB }},
/*fb*/	{ "calls",	{ RL, AB }},
/*fc*/	{ "xfc",	{0}},
/*fd*/	{ 0,		},	/* extended ops */
/*fe*/	{ 0,		},
/*ff*/	{ 0,		},
};

struct inst	ext_inst_table[256] = {
/*00*/	{ 0, },
/*01*/	{ 0, },
/*02*/	{ 0, },
/*03*/	{ 0, },
/*04*/	{ 0, },
/*05*/	{ 0, },
/*06*/	{ 0, },
/*07*/	{ 0, },
/*08*/	{ 0, },
/*09*/	{ 0, },
/*0a*/	{ 0, },
/*0b*/	{ 0, },
/*0c*/	{ 0, },
/*0d*/	{ 0, },
/*0e*/	{ 0, },
/*0f*/	{ 0, },

/*10*/	{ 0, },
/*11*/	{ 0, },
/*12*/	{ 0, },
/*13*/	{ 0, },
/*14*/	{ 0, },
/*15*/	{ 0, },
/*16*/	{ 0, },
/*17*/	{ 0, },
/*18*/	{ 0, },
/*19*/	{ 0, },
/*1a*/	{ 0, },
/*1b*/	{ 0, },
/*1c*/	{ 0, },
/*1d*/	{ 0, },
/*1e*/	{ 0, },
/*1f*/	{ 0, },

/*20*/	{ 0, },
/*21*/	{ 0, },
/*22*/	{ 0, },
/*23*/	{ 0, },
/*24*/	{ 0, },
/*25*/	{ 0, },
/*26*/	{ 0, },
/*27*/	{ 0, },
/*28*/	{ 0, },
/*29*/	{ 0, },
/*2a*/	{ 0, },
/*2b*/	{ 0, },
/*2c*/	{ 0, },
/*2d*/	{ 0, },
/*2e*/	{ 0, },
/*2f*/	{ 0, },

/*30*/	{ 0, },
/*31*/	{ 0, },
/*32*/	{ "cvtdh",	{ RD, WH }},
/*33*/	{ "cvtgf",	{ RG, WF }},
/*34*/	{ 0, },
/*35*/	{ 0, },
/*36*/	{ 0, },
/*37*/	{ 0, },
/*38*/	{ 0, },
/*39*/	{ 0, },
/*3a*/	{ 0, },
/*3b*/	{ 0, },
/*3c*/	{ 0, },
/*3d*/	{ 0, },
/*3e*/	{ 0, },
/*3f*/	{ 0, },

/*40*/	{ "addg2",	{ RG, MG }},
/*41*/	{ "addg3",	{ RG, RG, WG }},
/*42*/	{ "subg2",	{ RG, MG }},
/*43*/	{ "subg3",	{ RG, RG, WG }},
/*44*/	{ "mulg2",	{ RG, MG }},
/*45*/	{ "mulg3",	{ RG, RG, WG }},
/*46*/	{ "divg2",	{ RG, MG }},
/*47*/	{ "divg3",	{ RG, RG, WG }},
/*48*/	{ "cvtgb",	{ RG, WB }},
/*49*/	{ "cvtgw",	{ RG, WW }},
/*4a*/	{ "cvtgl",	{ RG, WL }},
/*4b*/	{ "cvtrgl",	{ RG, WL }},
/*4c*/	{ "cvtbg",	{ RB, WG }},
/*4d*/	{ "cvtwg",	{ RW, WG }},
/*4e*/	{ "cvtlg",	{ RL, WG }},
/*4f*/	{ "acbg",	{ RG, RG, MG, BW }},

/*50*/	{ "movg",	{ RG, WG }},
/*51*/	{ "cmpg",	{ RG, RG }},
/*52*/	{ "mnegg",	{ RG, WG }},
/*53*/	{ "tstg",	{ RG }},
/*54*/	{ "emodg",	{ RG, RW, RG, WL, WG }},
/*55*/	{ "polyg",	{ RG, RW, AB }},
/*56*/	{ "cvtgh",	{ RG, WH }},
/*57*/	{ 0, },
/*58*/	{ 0, },
/*59*/	{ 0, },
/*5a*/	{ 0, },
/*5b*/	{ 0, },
/*5c*/	{ 0, },
/*5d*/	{ 0, },
/*5e*/	{ 0, },
/*5f*/	{ 0, },

/*60*/	{ "addh2",	{ RH, MH }},
/*61*/	{ "addh3",	{ RH, RH, WH }},
/*62*/	{ "subh2",	{ RH, MH }},
/*63*/	{ "subh3",	{ RH, RH, WH }},
/*64*/	{ "mulh2",	{ RH, MH }},
/*65*/	{ "mulh3",	{ RH, RH, WH }},
/*66*/	{ "divh2",	{ RH, MH }},
/*67*/	{ "divh3",	{ RH, RH, WH }},
/*68*/	{ "cvthb",	{ RH, WB }},
/*69*/	{ "cvthw",	{ RH, WW }},
/*6a*/	{ "cvthl",	{ RH, WL }},
/*6b*/	{ "cvtrhl",	{ RH, WL }},
/*6c*/	{ "cvtbh",	{ RB, WH }},
/*6d*/	{ "cvtwh",	{ RW, WH }},
/*6e*/	{ "cvtlh",	{ RL, WH }},
/*6f*/	{ "acbh",	{ RH, RH, MH, BW }},

/*70*/	{ "movh",	{ RH, WH }},
/*71*/	{ "cmph",	{ RH, RH }},
/*72*/	{ "mnegh",	{ RH, WH }},
/*73*/	{ "tsth",	{ RH }},
/*74*/	{ "emodh",	{ RH, RW, RH, WL, WH }},
/*75*/	{ "polyh",	{ RH, RW, AB }},
/*76*/	{ "cvthg",	{ RH, WG }},
/*77*/	{ 0, },
/*78*/	{ 0, },
/*79*/	{ 0, },
/*7a*/	{ 0, },
/*7b*/	{ 0, },
/*7c*/	{ "clro",	{ WO }},
/*7d*/	{ "movo",	{ RO, WO }},
/*7e*/	{ "movao",	{ AO, WL }},
/*7f*/	{ "pushao",	{ AO }},

/*80*/	{ 0, },
/*81*/	{ 0, },
/*82*/	{ 0, },
/*83*/	{ 0, },
/*84*/	{ 0, },
/*85*/	{ 0, },
/*86*/	{ 0, },
/*87*/	{ 0, },
/*88*/	{ 0, },
/*89*/	{ 0, },
/*8a*/	{ 0, },
/*8b*/	{ 0, },
/*8c*/	{ 0, },
/*8d*/	{ 0, },
/*8e*/	{ 0, },
/*8f*/	{ 0, },

/*90*/	{ 0, },
/*91*/	{ 0, },
/*92*/	{ 0, },
/*93*/	{ 0, },
/*94*/	{ 0, },
/*95*/	{ 0, },
/*96*/	{ 0, },
/*97*/	{ 0, },
/*98*/	{ "cvtfh",	{ RF, WH }},
/*99*/	{ "cvtfg",	{ RF, WG }},
/*9a*/	{ 0, },
/*9b*/	{ 0, },
/*9c*/	{ 0, },
/*9d*/	{ 0, },
/*9e*/	{ 0, },
/*9f*/	{ 0, },

/*a0*/	{ 0, },
/*a1*/	{ 0, },
/*a2*/	{ 0, },
/*a3*/	{ 0, },
/*a4*/	{ 0, },
/*a5*/	{ 0, },
/*a6*/	{ 0, },
/*a7*/	{ 0, },
/*a8*/	{ 0, },
/*a9*/	{ 0, },
/*aa*/	{ 0, },
/*ab*/	{ 0, },
/*ac*/	{ 0, },
/*ad*/	{ 0, },
/*ae*/	{ 0, },
/*af*/	{ 0, },

/*b0*/	{ 0, },
/*b1*/	{ 0, },
/*b2*/	{ 0, },
/*b3*/	{ 0, },
/*b4*/	{ 0, },
/*b5*/	{ 0, },
/*b6*/	{ 0, },
/*b7*/	{ 0, },
/*b8*/	{ 0, },
/*b9*/	{ 0, },
/*ba*/	{ 0, },
/*bb*/	{ 0, },
/*bc*/	{ 0, },
/*bd*/	{ 0, },
/*be*/	{ 0, },
/*bf*/	{ 0, },

/*c0*/	{ 0, },
/*c1*/	{ 0, },
/*c2*/	{ 0, },
/*c3*/	{ 0, },
/*c4*/	{ 0, },
/*c5*/	{ 0, },
/*c6*/	{ 0, },
/*c7*/	{ 0, },
/*c8*/	{ 0, },
/*c9*/	{ 0, },
/*ca*/	{ 0, },
/*cb*/	{ 0, },
/*cc*/	{ 0, },
/*cd*/	{ 0, },
/*ce*/	{ 0, },
/*cf*/	{ 0, },

/*d0*/	{ 0, },
/*d1*/	{ 0, },
/*d2*/	{ 0, },
/*d3*/	{ 0, },
/*d4*/	{ 0, },
/*d5*/	{ 0, },
/*d6*/	{ 0, },
/*d7*/	{ 0, },
/*d8*/	{ 0, },
/*d9*/	{ 0, },
/*da*/	{ 0, },
/*db*/	{ 0, },
/*dc*/	{ 0, },
/*dd*/	{ 0, },
/*de*/	{ 0, },
/*df*/	{ 0, },

/*e0*/	{ 0, },
/*e1*/	{ 0, },
/*e2*/	{ 0, },
/*e3*/	{ 0, },
/*e4*/	{ 0, },
/*e5*/	{ 0, },
/*e6*/	{ 0, },
/*e7*/	{ 0, },
/*e8*/	{ 0, },
/*e9*/	{ 0, },
/*ea*/	{ 0, },
/*eb*/	{ 0, },
/*ec*/	{ 0, },
/*ed*/	{ 0, },
/*ee*/	{ 0, },
/*ef*/	{ 0, },

/*f0*/	{ 0, },
/*f1*/	{ 0, },
/*f2*/	{ 0, },
/*f3*/	{ 0, },
/*f4*/	{ 0, },
/*f5*/	{ 0, },
/*f6*/	{ "cvthf",	{ RF, WH }},
/*f7*/	{ "cvthd",	{ RF, WD }},
/*f8*/	{ 0, },
/*f9*/	{ 0, },
/*fa*/	{ 0, },
/*fb*/	{ 0, },
/*fc*/	{ 0, },
/*fd*/	{ 0, },
/*fe*/	{ 0, },
/*ff*/	{ 0, },

};

char *	fp_literal[64] = {
 "0.5",  "0.5625", "0.625", "0.6875", "0.75",  "0.8125", "0.875", "0.9375",
 "1.0",  "1.125",  "1.25",  "1.375",  "1.5",   "1.625",  "1.75",  "1.875",
 "2.0",  "2.25",   "2.5",   "2.75",   "3.0",   "3.25",   "3.5",   "3.75",
 "4.0",  "4.5",    "5.0",   "5.5",    "6.0",   "6.5",    "7.0",   "7.5",
 "8.0",  "9.0",   "10.0",  "11.0",   "12.0",  "13.0",   "14.0",  "15.0",
"16.0", "18.0",   "20.0",  "22.0",   "24.0",  "26.0",   "28.0",  "30.0",
"32.0", "36.0",   "40.0",  "44.0",   "48.0",  "52.0",   "56.0",  "60.0",
"64.0", "72.0",   "80.0",  "88.0",   "96.0", "104.0",  "112.0", "120.0"
};

char *	db_reg_name[16] = {
"r0",  "r1",  "r2",  "r3",  "r4",  "r5",  "r6",  "r7",
"r8",  "r9",  "r10", "r11", "ap",  "fp",  "sp",  "pc"
};

db_addr_t
imm_operand(fmt, loc, valuep)
	int	fmt;
	db_addr_t	loc;
	db_expr_t	*valuep;	/* out */
{
	int	value[4];
	int	i, size;

	db_printf("$");
	switch (opnd_type(fmt)) {
	    case T_B:
		get_value_inc(value[0], loc, 1, TRUE);
		db_printf("%#r", value[0]);
		break;
	    case T_W:
		get_value_inc(value[0], loc, 2, TRUE);
		db_printf("%#r", value[0]);
		break;
	    case T_L:
		get_value_inc(value[0], loc, 4, TRUE);
		db_printsym((db_addr_t)value[0], DB_STGY_ANY);
		break;
	    case T_Q:
		size = 2;
		db_printf("0x");
		goto imm_long;
	    case T_O:
		size = 4;
		db_printf("0x");
	    imm_long:
		for (i = 0; i < size; i++) {
		    get_value_inc(value[i], loc, 4, TRUE);
		}
		for (; i >= 0; i--) {
		    if (value[i])
			break;
		}
		if (i < 0)
		    db_printf("0");
		else {
		    for (; i >= 0; i--)
			db_printf("%08x", value[i]);
		}
		break;
	    case T_F:
		size = 1;
		db_printf("0f::");
		goto imm_long;
	    case T_D:
		db_printf("0d::");
		size = 2;
		goto imm_long;
	    case T_G:
		db_printf("0g::");
		size = 2;
		goto imm_long;
	    case T_H:
		db_printf("0h::");
		size = 4;
		goto imm_long;
	}
	*valuep = value[0];
	return (loc);
}

db_addr_t
db_disasm(loc, altfmt)
	db_addr_t	loc;
	boolean_t	altfmt;	/* if TRUE, don`t do entry masks */
{
	int		inst;
	register struct inst *ip;
	register int	fmt;
	register int	opnd;
	int		i;
	char *		reg;
	char *		index_reg;
	db_expr_t	disp;
	db_expr_t	op_value[MAXNARGS];

	if (!altfmt) {
	    /*
	     * Check for entry mask.
	     */
	    char	*namep;
	    db_expr_t	offset;

	    db_find_sym_and_offset(loc, &namep, &offset);
	    if (offset == 0 && namep[0] == '_') {
		db_printf("%#x\n", db_get_value(loc, 2, FALSE));
		return (loc + 2);
	    }
	}

	get_value_inc(inst, loc, 1, FALSE);

	if (inst == 0xFD) {
	    /* extension */
	    get_value_inc(inst, loc, 1, FALSE);
	    ip = &ext_inst_table[inst];
	}
	else {
	    ip = &inst_table[inst];
	}
	if (ip->opcode == 0) {
	    db_printf("<undefined opcode byte 0x%x>\n", inst);
	    return (loc);
	}

	db_printf("%s\t", ip->opcode);
	i = 0;
	while ((fmt = ip->fmt[i]) != 0) {
	    if (i > 0)
		db_printf(",");
	    op_value[i] = 0;
	    switch (fmt) {
		case BB:
		    /* byte displacement */
		    get_value_inc(disp, loc, 1, TRUE);	/* sign-extend */
		    db_printsym(disp + loc, DB_STGY_ANY);
		    break;
		case BW:
		    /* word displacement */
		    get_value_inc(disp, loc, 2, TRUE);	/* sign-extend */
		    db_printsym(disp + loc, DB_STGY_ANY);
		    break;
		case CASEW:
		{
		    /* case table */
		    db_addr_t	base_loc;
		    register int j;

		    base_loc = loc;
		    for (j = 0; j <= op_value[2]; j++) {
			printf("\n%#8r:\t", j + op_value[1]);
			get_value_inc(disp, loc, 2, TRUE);
							/* sign-extend */
			db_printsym(disp + base_loc, DB_STGY_ANY);
		    }
		    break;
		}
		default:
		{
		    register int size;

		    get_value_inc(opnd, loc, 1, FALSE);
		    index_reg = 0;
		    reg = db_reg_name[opnd & 0xF];
		    if ((opnd >> 4) == 4) {
			/* index register preceding operand */
			index_reg = reg;
			get_value_inc(opnd, loc, 1, FALSE);
			reg = db_reg_name[opnd & 0xF];
		    }
		    switch (opnd >> 4) {
			case 0:
			case 1:
			case 2:
			case 3:
			{
			    /* literal */
			    size = opnd_type(fmt);
			    if (size == T_F ||
				size == T_D ||
				size == T_G ||
				size == T_H)
				db_printf("%s", fp_literal[opnd]);
			    else {
				db_printf("$%#r",opnd);
				op_value[i] = opnd;
			    }
			    break;
			}
			case 4:
			    /* index - already parsed */
			    db_printf("?[%s]", reg);
			    break;
			case 5:
			    /* register */
			    db_printf("%s", reg);
			    break;
			case 6:
			    /* register indirect */
			    db_printf("(%s)", reg);
			    break;
			case 7:
			    /* auto-decrement */
			    db_printf("-(%s)", reg);
			    break;
			case 9:
			    /* auto-increment indirect*/
			    db_printf("*");
			    fmt = RL;	/* indirect reads longword */
			    /* fall through */
			case 8:
			    /* auto-increment */
			    if ((opnd & 0xF) == 0xF) {
				/* immediate */
				loc = imm_operand(fmt, loc, &op_value[i]);
			    }
			    else {
				db_printf("(%s)+", reg);
			    }
			    break;
			case 11:
			    /* byte displacement indirect */
			    db_printf("*");
			    /* fall through */
			case 10:
			    /* byte displacement */
			    size = 1;
			    goto disp_reg;
			case 13:
			    /* word displacement indirect */
			    db_printf("*");
			    /* fall through */
			case 12:
			    /* word displacement */
			    size = 2;
			    goto disp_reg;
			case 15:
			    /* longword displacement indirect */
			    db_printf("*");
			    /* fall through */
			case 14:
			    /* longword displacement */
			    size = 4;
			    /* fall through */
			  disp_reg:
			    get_value_inc(disp, loc, size, TRUE);
			    if ((opnd & 0xF) == 0xF) {
				/* PC-relative */
				db_printsym(disp + loc, DB_STGY_ANY);
			    }
			    else {
				extern unsigned int db_maxoff;

				if (disp > db_maxoff ||
				    disp < -((int)db_maxoff) ) {
				    db_printsym((db_addr_t)disp, DB_STGY_ANY);
				}
				else {
				    db_printf("%#r", disp);
				}
				db_printf("(%s)", reg);
			    }
			    break;
		    }
		    if (index_reg)
			db_printf("[%s]", index_reg);
		    break;
		}
	    }
	    i++;
	}
	db_printf("\n");
	return (loc);
}

