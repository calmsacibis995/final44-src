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
 * $Log:	defs.h,v $
 * Revision 1.4.1.5  90/05/14  13:18:07  rvb
 * 	Bring kdb up to Mach 2.5 production quality.
 * 	[90/05/10            rvb]
 * 
 * Revision 1.4.1.4  90/01/08  13:28:14  rvb
 * 	Code cleanup -- flush dead code.
 * 	[90/01/08            rvb]
 * 
 * Revision 1.4.1.3  89/12/21  17:56:27  rvb
 * 	a.out/coff'ized
 * 
 * Revision 1.4.1.2  89/10/30  12:25:16  rvb
 * 	Clean up double log
 * 
 * 
 * Revision 1.4.1.1  89/10/30  11:35:08  rvb
 * 	Revision 1.4  89/10/16  16:24:45  kupfer
 * 	Put back single-step fixes & minor cleanups (lost some formatting changes,
 * 	though).
 * 
 * 	Revision 1.3  89/09/21  12:03:47  lance
 * 	X108 checkin
 * 
 * 	Revision 1.2  89/08/07  17:29:19  kupfer
 * 	Better handling of single-step traps.  Added some debugging hacks
 * 	to deal with non-debuggable GP faults.  Some reformatting.
 * 
 * Revision 1.4  89/03/09  20:00:10  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/27  21:31:20  mrt
 * 	We will minimally sanitize this kdb till something better comes
 * 	along.
 * 	[89/02/27            rvb]
 * 
 * 31-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Don't include features.h here!
 *
 *  1-Jan-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Revamped for compilation under KERNEL switch.
 *
 */

#ifdef	notdef
#endif	notdef

/*	defs.h	4.3	82/12/19	*/

/*
 * adb - vax string table version; common definitions
 */

#include "kdbdefine.h"

#include <i386/psl.h>
#include <i386/debug.h>
#include <mach/i386/vm_param.h>
#include <sys/param.h>
#include <sys/dir.h>
#include <sys/user.h>

#ifdef	wheeze
#include "structs.h"
struct pte {
	int x;
};
#else	wheeze
#include </usr/include/a.out.h>
#endif	wheeze

#define ADB
#define MULD2

#undef	TRUE
#undef	FALSE
#undef	MAXFILE

#include <i386/reg.h>
#include <i386/trap.h>
#include <vm/vm_map.h>

#include "mac.h"
#include "mode.h"
#include "head.h"

/* access modes */
#define RD	0
#define WT	1

#define NSP	0
#define ISP	1
#define DSP	2
#define STAR	4
#define STARCOM 0200

/*
 * Symbol types, used internally in calls to findsym routine.
 * One the VAX this all degenerates since I & D symbols are indistinct.
 * Basically we get NSYM==0 for `=' command, ISYM==DSYM otherwise.
 */
#define NSYM	0
#define DSYM	1		/* Data space symbol */
#define ISYM	DSYM		/* Instruction space symbol == DSYM on VAX */

#define BKPTSET	1
#define BKPTEXEC 2
#define BKPTTMP	4

#define USERPS	PSL
#define USERPC	PC
#define BPT	0xcc
#define TBIT	020
#define FD	0200
#define SETTRC	0
#define RDUSER	2
#define RIUSER	1
#define WDUSER	5
#define WIUSER	4
#define RUREGS	3
#define WUREGS	6
#define CONTIN	7
#define EXIT	8
#define SINGLE	9


#define MAXOFF	0x1000

#define MAXPOS	80
#define MAXLIN	128
#define EOF	0
#define EOR	'\n'
#define QUOTE	0200
#define EVEN	-2

/* long to ints and back (puns) */
union {
	INT	I[2];
	long	L;
}
itolws;

#define leng(a)		itol(0,a)
#define shorten(a)	((short)(a))
#define itol(a,b)	(itolws.I[0]=(b), itolws.I[1]=(a), itolws.L)

/* result type declarations */
long		inkdot();
unsigned	get();
unsigned	chkget();
string_t	exform();
long		round();
bkpt_t		scanbkpt();
VOID		fault();

struct	pcb	pcb;
int	kernel;
int	kcore;

struct	pcb	*curpcb;	/* pcb for selected process */
vm_map_t	curmap;		/* vm map for selected process */
int		curpid;		/* process id when entering debugger */
