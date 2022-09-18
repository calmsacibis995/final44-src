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
 * $Log:	head.h,v $
 * Revision 1.4.1.2  90/05/14  13:18:22  rvb
 * 	Bring kdb up to Mach 2.5 production quality.
 * 	[90/05/10            rvb]
 * 
 * Revision 1.4.1.1  90/01/08  13:27:51  rvb
 * 	Code cleanup -- flush dead code.
 * 	[90/01/08            rvb]
 * 
 * Revision 1.4  89/03/09  20:00:42  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/27  21:32:31  mrt
 * 	We will minimally sanitize this kdb till something better comes
 * 	along.
 * 	[89/02/27            rvb]
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
