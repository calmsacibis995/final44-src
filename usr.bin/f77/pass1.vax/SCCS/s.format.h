h56977
s 00005/00004/00064
d D 5.2 91/04/12 16:08:49 bostic 2 1
c new copyright; att/bsd/shared
e
s 00068/00000/00000
d D 5.1 85/06/07 21:34:32 mckusick 1 0
c 4.3BSD beta release version
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

/*
 * format parser definitions
 */

struct syl
{
	short op,p1,p2,rpcnt;
};

/*	do NOT change this defines or add new ones without
 *	changing the value of the following define for OP_TYPE_TAB.
 *	change format.h both in the compiler and libI77 simultaneously.
 */


#define RET	1
#define REVERT 	2
#define GOTO 	3
#define X 	4
#define SLASH 	5
#define STACK 	6
#define I 	7
#define ED 	8
#define NED 	9
#define IM 	10
#define APOS 	11
#define H 	12
#define TL 	13
#define TR 	14
#define T 	15
#define COLON 	16
#define S 	17
#define SP 	18
#define SS 	19
#define P 	20
#define BNZ 	21
#define B 	22
#define F 	23
#define E 	24
#define EE 	25
#define D 	26
#define DE	27		/*** NOT STANDARD FORTRAN ***/
#define G 	28
#define GE 	29
#define L 	30
#define A 	31
#define AW	32
#define R	33		/*** NOT STANDARD FORTRAN ***/
#define DOLAR	34		/*** NOT STANDARD FORTRAN ***/
#define SU	35		/*** NOT STANDARD FORTRAN ***/

#define	FMTUNKN	-1
#define FMTOK	1
#define FMTERR	0

#define FMT_COMP 0x101		/* indicates pre-compiled formats */

extern struct syl syl[];
extern int parenlvl,revloc;
extern short pc;
E 1
