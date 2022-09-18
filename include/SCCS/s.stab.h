h42010
s 00002/00002/00039
d D 8.1 93/06/02 20:06:48 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00035/00007
d D 5.2 91/04/04 14:09:45 bostic 3 2
c from scratch -- superset of Berkeley and GNU symbols
e
s 00007/00001/00035
d D 5.1 85/05/30 09:40:23 dist 2 1
c Add copyright
e
s 00036/00000/00000
d D 4.1 83/05/03 13:48:19 sam 1 0
c date and time created 83/05/03 13:48:19 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
D 3
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
E 3
 *
I 3
 * %sccs.include.redist.c%
 *
E 3
 *	%W% (Berkeley) %G%
 */
E 2

D 3
/* IF YOU ADD DEFINITIONS, ADD THEM TO nm.c as well */
E 3
/*
D 3
 * This file gives definitions supplementing <a.out.h>
 * for permanent symbol table entries.
 * These must have one of the N_STAB bits on,
 * and are subject to relocation according to the masks in <a.out.h>.
E 3
I 3
 * The following are symbols used by various debuggers and by the Pascal
 * compiler.  Each of them must have one (or more) of the bits defined by
 * the N_STAB mask set.
E 3
 */
D 3
/*
 * for symbolic debugger, sdb(1):
 */
#define	N_GSYM	0x20		/* global symbol: name,,0,type,0 */
#define	N_FNAME	0x22		/* procedure name (f77 kludge): name,,0 */
#define	N_FUN	0x24		/* procedure: name,,0,linenumber,address */
#define	N_STSYM	0x26		/* static symbol: name,,0,type,address */
#define	N_LCSYM	0x28		/* .lcomm symbol: name,,0,type,address */
#define	N_RSYM	0x40		/* register sym: name,,0,type,register */
#define	N_SLINE	0x44		/* src line: 0,,0,linenumber,address */
#define	N_SSYM	0x60		/* structure elt: name,,0,type,struct_offset */
#define	N_SO	0x64		/* source file name: name,,0,0,address */
#define	N_LSYM	0x80		/* local sym: name,,0,type,offset */
#define	N_SOL	0x84		/* #included file name: name,,0,0,address */
#define	N_PSYM	0xa0		/* parameter: name,,0,type,offset */
#define	N_ENTRY	0xa4		/* alternate entry: name,linenumber,address */
#define	N_LBRAC	0xc0		/* left bracket: 0,,0,nesting level,address */
#define	N_RBRAC	0xe0		/* right bracket: 0,,0,nesting level,address */
#define	N_BCOMM	0xe2		/* begin common: name,, */
#define	N_ECOMM	0xe4		/* end common: name,, */
#define	N_ECOML	0xe8		/* end common (local name): ,,address */
#define	N_LENG	0xfe		/* second stab entry with length information */
E 3

D 3
/*
 * for the berkeley pascal compiler, pc(1):
 */
#define	N_PC	0x30		/* global pascal symbol: name,,0,subtype,line */
E 3
I 3
#define	N_GSYM		0x20	/* global symbol */
#define	N_FNAME		0x22	/* F77 function name */
#define	N_FUN		0x24	/* procedure name */
#define	N_STSYM		0x26	/* data segment variable */
#define	N_LCSYM		0x28	/* bss segment variable */
#define	N_MAIN		0x2a	/* main function name */
#define	N_PC		0x30	/* global Pascal symbol */
#define	N_RSYM		0x40	/* register variable */
#define	N_SLINE		0x44	/* text segment line number */
#define	N_DSLINE	0x46	/* data segment line number */
#define	N_BSLINE	0x48	/* bss segment line number */
#define	N_SSYM		0x60	/* structure/union element */
#define	N_SO		0x64	/* main source file name */
#define	N_LSYM		0x80	/* stack variable */
#define	N_BINCL		0x82	/* include file beginning */
#define	N_SOL		0x84	/* included source file name */
#define	N_PSYM		0xa0	/* parameter variable */
#define	N_EINCL		0xa2	/* include file end */
#define	N_ENTRY		0xa4	/* alternate entry point */
#define	N_LBRAC		0xc0	/* left bracket */
#define	N_EXCL		0xc2	/* deleted include file */
#define	N_RBRAC		0xe0	/* right bracket */
#define	N_BCOMM		0xe2	/* begin common */
#define	N_ECOMM		0xe4	/* end common */
#define	N_ECOML		0xe8	/* end common (local name) */
#define	N_LENG		0xfe	/* length of preceding entry */
E 3
E 1
