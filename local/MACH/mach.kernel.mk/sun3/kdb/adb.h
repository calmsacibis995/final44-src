/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	adb.h,v $
 * Revision 2.5  89/03/09  21:33:49  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  19:35:18  gm0w
 * 	Changes for cleanup.
 * 
 * 08-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Removed else leg of KERNEL conditionals and fixed 
 *	includes as part of kernel cleanup.
 *
 * 29-Jan-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Conditionalized kdb code under KERNEL and changed pathnames
 *	of include files to kernel relative ones in order to make
 *	kdb part of the kernel rather than a separate library.
 *
 * 24-Nov-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added defintions of "CONTIN" and "SINGLE".
 *
 *  5-Sep-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Modified for kernel debugger, "kdb".
 *
 */
/*	@(#)adb.h 1.1 86/02/03 SMI	*/


/*
 * adb - a debugger
 *
 * symbolic and kernel enhanced 4.2bsd version.
 *
 * this is a 32 bit machine version of this program.
 * it keeps large data structures in core, and expects
 * in several places that an int can represent 32 integers
 * and file indices.
 */

#include <sun3/kdb/kdbdefine.h>
#include <a.out.h>
#include <stab.h>
#include <sys/param.h>
#include <sys/dir.h>
#include <sun3/psl.h>
#include <sys/types.h>
#include <vm/vm_map.h>
#include <sys/user.h>
#include <ctype.h>

#undef NFILE    /* from sys/param.h */

typedef	unsigned	addr_t;
#define NSIG	32

#define BUFSIZ	1024	/* was in stdio.h */

#include <setjmp.h>
jmp_buf exitbuffer;
#define setexit() setjmp(exitbuffer)
#define reset(i)   longjmp_rval(exitbuffer,(i))

#ifdef	vax
#include <vax.h>
#endif
#ifdef	sun
#include <sun3/kdb/sun.h>
#endif

#include <sun3/kdb/process.h>

#define DBNAME	kdb
#define CONTIN	7
#define SINGLE	9

#define NSP	0		/* = */
#define ISP	1		/* ? */
#define DSP	2		/* / */
#define SSP	3		/* @ */

#define STAR	4

#define NSYM	0		/* no symbol space */
#define ISYM	1		/* symbol in I space */
#define DSYM	1		/* symbol in D space (== I space on VAX) */

/* result type declarations */
char	*exform();
/* VARARGS */
extern char	*strcpy();


/* miscellaneous globals */
char	*errflg;	/* error message, synchronously set */
char	*lp;		/* input buffer pointer */
int	interrupted;	/* was command interrupted ? */
int	ditto;		/* last address expression */
int	lastcom;	/* last command (=, /, ? or @) */
int	var[36];	/* variables, 0-9 and a-z */
int	expv;		/* expression value from last expr() call */
char	sigpass[NSIG];	/* pass-signal-to-subprocess flags	  */
int	adb_pgrpid;	/* used by SIGINT and SIGQUIT signal handlers */

extern	errno;

int	hadaddress;	/* command had an address ? */
int	address;	/* address on command */
int	hadcount;	/* command had a count ? */
int	count;		/* count on command */

int	radix;		/* radix for output */
int	maxoff;

char	peekc;		/* next character for input */
char	lastc;		/* previous input character */

int	xargc;		/* externally available argc */
int	wtflag;		/* -w flag ? */

vm_map_t	*curmap;	/* vm map for selected process */
struct  pcb     *curpcb;        /* pcb for selected process */
int             curpid;         /* process id when entering debugger */
struct  pcb     pcb;

addr_t		localval;
struct nlist	*cursym;		/* current symbol */
struct nlist 	*symtab, *esymtab;	/* begin. and end of symbol table */

extern struct nlist	*lookup();

int	(*sigint)();
int	(*sigqit)();
int	(*signal())();
