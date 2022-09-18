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
 * $Log:	defs.h,v $
 * Revision 2.6  89/03/09  22:16:58  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  20:21:22  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  88/08/10  10:26:12  rvb
 * kdb_define.h now needs the label_t type defined before it.
 * 
 *
 *  3-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Removed some lint.
 *
 * 31-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Don't include features.h here!
 *
 *  1-Jan-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Revamped for compilation under KERNEL switch.
 *
 */

/*
 * adb - vax string table version; common definitions
 */

/*	defs.h	4.3	82/12/19	*/

#include <vax/kdb/kdbdefine.h>

#include <machine/psl.h>
#include <machine/pte.h>
#include <sys/param.h>
#include <sys/dir.h>
#include <sys/user.h>

#include <ctype.h>
#include <a.out.h>

#define ADB
#define MULD2

#undef	TRUE
#undef	FALSE
#undef	MAXFILE

#include <vm/vm_map.h>

#include <vax/kdb/mac.h>
#include <vax/kdb/mode.h>
#include <vax/kdb/head.h>

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

#define USERPS	PSL
#define USERPC	PC
#define BPT	03
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

/* the quantities involving ctob() are located in the kernel stack. */
/* the others are in the pcb. */
#define KSP	0
#define ESP	4
#define SSP	8
#define USP	(ctob(UPAGES)-5*sizeof(int))
#define R0	(ctob(UPAGES)-18*sizeof(int))
#define R1	(ctob(UPAGES)-17*sizeof(int))
#define R2	(ctob(UPAGES)-16*sizeof(int))
#define R3	(ctob(UPAGES)-15*sizeof(int))
#define R4	(ctob(UPAGES)-14*sizeof(int))
#define R5	(ctob(UPAGES)-13*sizeof(int))
#define R6	(ctob(UPAGES)-12*sizeof(int))
#define R7	(ctob(UPAGES)-11*sizeof(int))
#define R8	(ctob(UPAGES)-10*sizeof(int))
#define R9	(ctob(UPAGES)-9*sizeof(int))
#define R10	(ctob(UPAGES)-8*sizeof(int))
#define R11	(ctob(UPAGES)-7*sizeof(int))
#define AP	(ctob(UPAGES)-21*sizeof(int))
#define FP	(ctob(UPAGES)-20*sizeof(int))
#define PC	(ctob(UPAGES)-2*sizeof(int))
#define PSL	(ctob(UPAGES)-1*sizeof(int))
#define P0BR	80
#define P0LR	84
#define P1BR	88
#define P1LR	92

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
