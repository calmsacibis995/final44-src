/*  
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * Copyright (c) 1986 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	dis_extra.c,v $
 * Revision 2.3  89/03/09  22:14:11  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  20:17:47  gm0w
 * 	Changes for cleanup.
 * 
 * 15-May-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	This file has been create from those pieces of the adb debugger
 *	that were necessary to make a disassembler module.  Opset.ce was
 *	copied en masse to dis_opset.c, then a few bits and pieces of
 *	routines and constants were needed.  They live in this module.
 *
 */

typedef char *string_t;
typedef unsigned char u_char;
/*
 *	from optab.c
 */
#undef INSTTAB
#ifdef	KERNEL
#define DIS 1
#endif	KERNEL

#include <instrs.h>

struct insttab dis_insttab[] = {
#include <instrs.adb>
	0};


string_t	dis_regname[] = {
	"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
	"r8", "r9", "r10","r11","ap", "fp", "sp", "pc"};

string_t	dis_fltimm[] = {
	"0.5", "0.5625", "0.625", "0.6875", "0.75", "0.8125", "0.875", "0.9375",
	"1.0", "1.125", "1.25", "1.375", "1.5", "1.625", "1.75", "1.875",
	"2.0", "2.25", "2.5", "2.75", "3.0", "3.25", "3.5", "3.75",
	"4.0", "4.5", "5.0", "5.5", "6.0", "6.5", "7.0", "7.5",
	"8.0", "9.0", "10.0", "11.0", "12.0", "13.0", "14.0", "15.0",
	"16.0", "18.0", "20.0", "22.0", "24.0", "26.0", "28.0", "30.0",
	"32.0", "36.0", "40.0", "44.0", "48.0", "52.0", "56.0", "60.0",
	"64.0", "72.0", "80.0", "88.0", "96.0", "104.0", "112.0", "120.0"
};

/*
 * 	from assizetab.c
 */

/*
 *	Convert TYP[BWLQOFDGH] into {1 if relocation not OK}
 */
int	dis_ty_NORELOC[] = {
	0,	/* TYPB */
	0,	/* TYPW */
	0,	/* TYPL */
	1,	/* TYPQ */
	1,	/* TYPO */
	1,	/* TYPF */
	1,	/* TYPD */
	1,	/* TYPG */
	1,	/* TYPH */
	1	/* TYPNONE */
};
/*
 *	Convert TYP[BWLQOFDGH] into {1 ... 16}
 */
int	dis_ty_nbyte[] = {
	1,	/* TYPB */
	2,	/* TYPW */
	4,	/* TYPL */
	8,	/* TYPQ */
	16,	/* TYPO */
	4,	/* TYPF */
	8,	/* TYPD */
	8,	/* TYPG */
	16,	/* TYPH */
	0	/* TYPNONE */
};
