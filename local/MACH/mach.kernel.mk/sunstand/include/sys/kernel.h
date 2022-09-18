/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	kernel.h,v $
 * Revision 2.2  89/07/12  00:12:54  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)kernel.h 2.10 88/02/08 SMI; from UCB 4.8 83/05/30	*/

/*
 * Global variables for the kernel
 */

u_long	rmalloc();

/* 1.1 */
char	hostname[MAXHOSTNAMELEN];
int	hostnamelen;
char	domainname[MAXHOSTNAMELEN];
int	domainnamelen;

/* 1.2 */
struct	timeval boottime;
struct	timeval time;
struct	timezone tz;			/* XXX */
int	hz;
int	phz;				/* alternate clock's frequency */
int	tick;				/* microseconds/tick; set in param.c */
int	lbolt;				/* awoken once a second */
int	realitexpire();

long	avenrun[3];			/* FSCALED average run queue lengths */

#ifdef GPROF
extern	int profiling;
extern	char *s_lowpc;
extern	u_long s_textsize;
extern	u_short *kcount;
#endif
