/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	process.h,v $
 * Revision 2.6  89/03/09  21:35:23  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  19:42:22  gm0w
 * 	Changes for cleanup.
 * 
 * 08-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Removed else leg of MACH conditionals as part of kernel
 *	cleanup.
 *
 *  5-Feb-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Revised for new pmap.[ch]:
 *		struct pte -> struct pme
 *
 * 29-Apr-87  David Golub (dbg) at Carnegie-Mellon University
 *	Removed u area for MACH.
 *
 */
/*	@(#)process.h 1.1 86/02/03 SMI	*/


addr_t	userpc;
struct	pme *sbr;
int	kernel;
int	kcore;
int	slr;
#ifdef	vax
int	masterpcbb;
struct	pcb pcb;
#endif
#ifdef	sun
int	masterprocp;
struct pme umap[UPAGES];
int	upage;
int	physmem;
#endif
int	dot;
int	dotinc;
int	pid;
int	executing;
int	fcor;
int	fsym;
int	signo;
int	sigcode;

struct	exec filhdr;

char	*corfil, *symfil;

/* file address maps */
struct map {
	unsigned	b1,e1,f1;
	unsigned	b2,e2,f2;
	unsigned	ufd;
} txtmap, datmap;

#define BKPTSET		1
#define BKPTEXEC	2

#define MAXCOM	64

struct	bkpt {
	addr_t	loc;
	addr_t	ins;
	int	count;
	int	initcnt;
	int	flag;
	char	comm[MAXCOM];
	struct	bkpt *nxtbkpt;
};
struct	bkpt *bkptlookup();
