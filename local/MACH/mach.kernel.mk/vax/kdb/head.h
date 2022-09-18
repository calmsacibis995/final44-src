/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	head.h,v $
 * Revision 2.3  89/02/25  20:21:50  gm0w
 * 	Changes for cleanup.
 * 
 *  3-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Removed more definitions unused in kernel.
 *
 * 31-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Don't define u if compiling in the kernel.
 *
 */

/*	head.h	4.1	81/05/14	*/

long	maxoff;
long	localval;

struct	nlist *symtab, *esymtab;
struct	nlist *cursym;
struct	nlist *lookup();

long	var[36];

map	txtmap;
map	datmap;
INT	wtflag;
INT	fcor;
INT	fsym;
INT	signo;


char	*corfil, *symfil;

