h31771
s 00001/00001/00057
d D 4.7 91/04/11 11:51:32 sklower 7 6
c optab include .c file with another sccsid.
e
s 00009/00002/00049
d D 4.6 91/04/04 17:56:44 bostic 6 5
c new copyright; att/bsd/shared
e
s 00039/00120/00012
d D 4.5 89/01/16 20:43:38 bostic 5 4
c new version from Chris Torek
e
s 00004/00004/00128
d D 4.4 88/01/10 15:40:30 bostic 4 3
c fix #endif's for ANSI C
e
s 00042/00030/00090
d D 4.3 82/10/27 14:38:14 rrh 3 2
c Complete reworking of opset.c to make its operation understandable
c Allow 2 byte opcodes for extended VAX architecture (G and H numbers).
c Opset.c is shared between adb and sdb.  Use a common instruction data base
c with adb, sdb, as and c2
e
s 00001/00001/00119
d D 4.2 82/05/07 19:12:54 mckusick 2 1
c keep usable copy of instrs for optab.c
e
s 00120/00000/00000
d D 4.1 81/05/14 15:19:51 root 1 0
c date and time created 81/05/14 15:19:51 by root
e
u
U
t
T
I 6
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

E 6
I 3
#ifndef lint
D 5
static	char optab_sccsid[] = "%Z%%M% %I% %G%";
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4
#ifdef ADB
E 3
I 1
#include "defs.h"
D 3
static	char sccsid[] = "%Z%%M% %I% %G%";
/*
 * Argument access types
 */
#define ACCA	(8<<3)	/* address only */
#define ACCR	(1<<3)	/* read */
#define ACCW	(2<<3)	/* write */
#define ACCM	(3<<3)	/* modify */
#define ACCB	(4<<3)	/* branch displacement */
#define ACCI	(5<<3)	/* XFC code */
E 3
I 3
D 4
#endif ADB
E 4
I 4
#endif /* ADB */
E 4
#ifdef SDB
#include "defs.h"
D 4
#endif SDB
E 4
I 4
#endif /* SDB */
E 5
I 5
D 6
static char optab_sccsid[] = "%W% (Berkeley) %G%";
#endif
E 6
I 6
D 7
static char sccsid[] = "%W% (Berkeley) %G%";
E 7
I 7
static char optab_sccsid[] = "%W% (Berkeley) %G%";
E 7
#endif /* not lint */
E 6
E 5
E 4
E 3

I 5
/*
 * adb - (read-only) tables for VAX instruction decoding
 */

#define	ADB
E 5
D 3
/*
 * Argument data types
 */
#define TYPB	0	/* byte */
#define TYPW	1	/* word */
#define TYPL	2	/* long */
#define TYPQ	3	/* quad */
#define TYPF	4	/* floating */
#define TYPD	5	/* double floating */
E 3
I 3
#undef INSTTAB
E 3

I 5
/*
 * Pick up definitions for insttab from the assembler, and also
 * the arrays ty_NORELOC and ty_nbyte (and soon ty_float);
 * then, make insttab.
 */
#include <sys/types.h>
E 5
I 3
#include "instrs.h"
I 5
#include "assizetab.c"
E 5
E 3

D 3
TYPE	struct optab	*OPTAB;
struct optab {
	char *iname;
	char val;
	char nargs;
	char argtype[6];
} optab[] = {
#define OP(a,b,c,d,e,f,g,h,i) {a,b,c,d,e,f,g,h,i}
D 2
#include "../as/instrs"
E 2
I 2
#include "instrs"
E 3
I 3
struct insttab insttab[] = {
#include "instrs.adb"
E 3
E 2
D 5
0};
I 3
#include "assizetab.c"
#undef ADB
E 3

#define SYSTAB struct systab
SYSTAB {
	int	argc;
	char	*sname;
} systab[] = {
	1, "indir",
	0, "exit",
	0, "fork",
	2, "read",
	2, "write",
	2, "open",
	0, "close",
	0, "wait",
	2, "creat",
	2, "link",
	1, "unlink",
	2, "exec",
	1, "chdir",
	0, "time",
	3, "mknod",
	2, "chmod",
	2, "chown",
	1, "break",
	2, "stat",
	2, "seek",
	0, "getpid",
	3, "mount",
	1, "umount",
	0, "setuid",
	0, "getuid",
	0, "stime",
	3, "ptrace",
	0, "alarm",
	1, "fstat",
	0, "pause",
	1, "30",
	1, "stty",
	1, "gtty",
	0, "access",
	0, "nice",
	0, "sleep",
	0, "sync",
	1, "kill",
	0, "csw",
	0, "setpgrp",
	0, "tell",
	0, "dup",
	0, "pipe",
	1, "times",
	4, "profil",
	0, "tiu",
	0, "setgid",
	0, "getgid",
	2, "signal",
	0, "49",
	0, "50",
	0, "51",
	0, "52",
	0, "53",
	0, "54",
	0, "55",
	0, "56",
	0, "57",
	0, "58",
	0, "59",
	0, "60",
	0, "61",
	0, "62",
	0, "63",
E 5
I 5
	0
E 5
};

D 5
STRING	regname[] = { "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
					"r8", "r9", "r10","r11","ap", "fp", "sp", "pc"};
STRING	fltimm[] = {
"0.5", "0.5625", "0.625", "0.6875", "0.75", "0.8125", "0.875", "0.9375",
"1.0", "1.125", "1.25", "1.375", "1.5", "1.625", "1.75", "1.875",
"2.0", "2.25", "2.5", "2.75", "3.0", "3.25", "3.5", "3.75",
"4.0", "4.5", "5.0", "5.5", "6.0", "6.5", "7.0", "7.5",
"8.0", "9.0", "10.0", "11.0", "12.0", "13.0", "14.0", "15.0",
"16.0", "18.0", "20.0", "22.0", "24.0", "26.0", "28.0", "30.0",
"32.0", "36.0", "40.0", "44.0", "48.0", "52.0", "56.0", "60.0",
"64.0", "72.0", "80.0", "88.0", "96.0", "104.0", "112.0", "120.0"
E 5
I 5
/*
 * Register names, and floating point immediate constants.
 * The f.p. constants can be derived from the expression
 *
 *	fp = (.5 + (n & 7) / 16.0) x (2 ^ (n >> 3))
 *
 * or, alternatively,
 *
 *	union { int i; float f; } u; u.i = (n << 3) | (1 << 14); u.f
 *
 * but there are only 64 of them, and this is simpler.
 */
char *regname[16] = {
	"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
	"r8", "r9", "r10","r11","ap", "fp", "sp", "pc"
E 5
};
D 5

D 3
char *fmtr = {"%r"};
char *fmtR = {"%R"};
E 3
I 3
#ifdef SDB
REGLIST reglist [] = {
		"p1lr", P1LR,
		"p1br",P1BR,
		"p0lr", P0LR,
		"p0br",P0BR,
		"ksp",KSP,
		"esp",ESP,
		"ssp",SSP,
		"psl", PSL,
		"pc", PC,
		"usp",USP,
		"fp", FP,
		"ap", AP,
		"r11", R11,
		"r10", R10,
		"r9", R9,
		"r8", R8,
		"r7", R7,
		"r6", R6,
		"r5", R5,
		"r4", R4,
		"r3", R3,
		"r2", R2,
		"r1", R1,
		"r0", R0,
E 5
I 5
char *fltimm[64] = {
	"0.5", "0.5625", "0.625", "0.6875", "0.75", "0.8125", "0.875", "0.9375",
	"1.0", "1.125", "1.25", "1.375", "1.5", "1.625", "1.75", "1.875",
	"2.0", "2.25", "2.5", "2.75", "3.0", "3.25", "3.5", "3.75",
	"4.0", "4.5", "5.0", "5.5", "6.0", "6.5", "7.0", "7.5",
	"8.0", "9.0", "10.0", "11.0", "12.0", "13.0", "14.0", "15.0",
	"16.0", "18.0", "20.0", "22.0", "24.0", "26.0", "28.0", "30.0",
	"32.0", "36.0", "40.0", "44.0", "48.0", "52.0", "56.0", "60.0",
	"64.0", "72.0", "80.0", "88.0", "96.0", "104.0", "112.0", "120.0"
E 5
};
D 4
#endif SDB
E 4
I 4
D 5
#endif /* SDB */
E 5
E 4
E 3
E 1
