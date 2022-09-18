/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ild.h,v $
 * Revision 2.3  89/03/09  22:04:50  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  17:54:04  gm0w
 * 	Changes for cleanup.
 * 
 */
/*	vmunix device driver for the /dev/lock -- 
 *	an in core device used as a Lock table
 */

#ifndef	_SYS_ILD_H_
#define _SYS_ILD_H_

/* Only the parameters NLOCKS, PLOCKS, RLOCKS and DLOCKS
 * may be changed by an INGRES installation.  See 
 * 'HOW TO INSTALL CONCURRENCY DEVICE' for details.
 * The file can be printed by "nroff .../doc/other/lockdev.nr"
 */

#define DLOCKS	10	/* max number of data base locks (limits # of ingreses */
#define RLOCKS	(2*DLOCKS + 6)
#define PLOCKS	(RLOCKS + 3)
#define NLOCKS	(PLOCKS + 1)
#define KEYSIZE	12

#define M_EMTY		0
#define M_SHARE		2
#define M_EXCL		1

#define T_CS		0
#define T_PAGE		1
#define T_REL		2
#define T_DB		3

#define A_RTN		1
#define A_SLP		2
#define A_RLS1		3
#define A_RLSA		4
#define A_ABT		5

#define W_ON		1
#define W_OFF		0

struct Lockreq
			/* Lock Request */
{
	char	lr_act;		/* requested action:
				 *	=1 request lock, err return
				 *	=2 request lock, sleep
				 *	=3 release lock
				 *	=4 release all locks for pid
				 */
	char	lr_type;	/* same as Locktab l_type */
	char	lr_mod;		/* same as Locktab l_mod */
	char	lr_key[KEYSIZE];/* requested key	*/
};

#ifdef	KERNEL

#define LOCKPRI	(PZERO+1)	/* sleep priority */

/*
 *	data structure for Lock table
 */
struct	Lockform
{
	int	l_pid;
	char	l_wflag;	/* wait flag: = 1 a process is waiting*/
	char	l_type;		/* type of lock:
					= 0 for critical section
					= 1 for page
					= 2 for logical
					= 3 for data base
				*/
	char	l_mod;		/* mod of Lock or lock action requested 
				 *	= 0 slot empty
				 *	= 1 exclusive lock
				 *	= 2 shared lock
				 */
	char 	l_key[KEYSIZE];
};

extern struct Lockform Locktab[NLOCKS];
extern int Lockset[];

#endif	KERNEL
#endif	_SYS_ILD_H_
