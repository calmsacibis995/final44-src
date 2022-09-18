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
 * $Log:	subr_prf.c,v $
 * Revision 2.24  91/04/10  16:34:06  mbj
 * 	Made addlog() varargs for sun4 as well as mips.
 * 	[91/03/18            berman]
 * 
 * Revision 2.23  91/04/03  13:00:37  mbj
 * 	Make Omron change conditional on omron
 * 	[91/04/02  18:30:49  rvb]
 * 
 * 	Fix the bug with field size printout.
 * 	[91/03/07  14:08:41  rvb]
 * 
 * 	Omron changes[sic]
 * 
 * Revision 2.22  91/04/02  11:04:59  mbj
 * 	Allow logwakeup for logging.
 * 	[90/09/08            rvb]
 * 	kdb(0, 0, 0) -> Bpt()
 * 	[90/05/17            rvb]
 * 
 * Revision 2.21  91/01/22  17:28:43  mja
 * 	Use LOG_NOTICE rather than LOG_WARNING as the lower bound on
 * 	console printouts in the absence of syslog().
 * 	[90/11/15  19:28:59  mja]
 * 
 * Revision 2.20  90/08/30  10:58:55  bohman
 * 	Changes for mac2.
 * 	[90/08/28            bohman]
 * 
 * Revision 2.19  90/07/03  16:32:31  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  17:49:21  mrt]
 * 
 * Revision 2.18  90/03/08  23:10:37  af
 * 	Removed MIPSCo's %R additions, they overlapped the %b
 * 	options and I got rid of all the code that used them.
 * 	[89/11/10            af]
 * 
 * Revision 2.17  89/10/10  10:47:13  mwyoung
 * 	Add patch to allow panic() to return, for kernel debugging.
 * 	[89/07/28  17:15:13  mwyoung]
 * 
 * Revision 2.16  89/09/09  15:18:30  rvb
 * 	i386: make panic call to kdb() dependent on MACH_KDB
 * 	[89/09/09            rvb]
 * 
 * Revision 2.15  89/07/11  13:09:08  jjc
 * 	Added support for SPARC.
 * 	[89/06/06            jjc]
 * 
 * Revision 2.14  89/05/30  10:35:16  rvb
 * 	Needs xpr.h for the mips features.
 * 	[89/04/20            af]
 * 
 * Revision 2.13  89/04/05  12:55:26  rvb
 * 	Fix up machine number printout for MP systems.
 * 	[89/03/21            rvb]
 * 
 * Revision 2.12  89/03/09  19:30:47  rpd
 * 	More cleanup.
 * 
 * Revision 2.11  89/02/25  14:45:47  gm0w
 * 	Removed included of seg.h as it no longer exists
 * 	[89/02/18            mrt]
 * 
 * Revision 2.10  89/02/09  04:32:55  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.9  89/01/31  01:20:46  rpd
 * 	Delete printf_cpu_number in favor of new_printf_cpu_number.
 * 	[89/01/25            dlb]
 * 
 * 	Fix bogus cpu number printing code to print numbers instead of
 * 	characters.  [You too can be executing on processor <}>].
 * 	Put cpu numbers in [] to avoid confusing syslogd.
 * 	[88/10/14            dlb]
 * 
 * Revision 2.8  89/01/23  22:06:48  af
 * 	Added Mips changes.  Uses varargs, has a couple of new things.
 * 	Also attempted to shrink and clean up a bit the mess (why
 * 	can't everybody use varargs ?).
 * 	[89/01/09            af]
 * 	
 * 	Changes for I386: kdb() call in panic AND we don't support logwakeup
 * 	[89/01/09            rvb]
 * 
 * Revision 2.7  89/01/15  16:18:31  rpd
 * 	Use decl_simple_lock_data.
 * 	[89/01/15  14:49:38  rpd]
 * 
 * Revision 2.6  88/12/19  02:34:23  mwyoung
 * 	Fix include file references.
 * 	[88/12/19            mwyoung]
 * 	
 * 	romp: Remove lint.
 * 	[88/12/17            mwyoung]
 * 
 * Revision 2.5  88/10/18  03:15:29  mwyoung
 * 	Start printing "<cpu_number>" before printf messages only once
 * 	a non-master processor has tried to print.
 * 	[88/09/13            mwyoung]
 * 
 * Revision 2.4  88/08/09  17:51:36  rvb
 * Use printf_lock so that multiple processors sharing the same
 * physical terminal don't garble their output.
 * Also: printf_cpu controls whether to printout the cpu number
 * before the print string and at each internal \n.
 * Bug fixes to %b printf mode for handling of "fields".
 * 
 *
 * 29-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH: Removed use of "sys/vm.h".
 *
 * 13-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Reduce the number of errors flagged by HC.
 *
 * 29-Feb-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	On sun3, panic early in boot just halts.
 *
 * 10-Nov-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Redirect all console output through putchar() to output through
 *	the `xcons_tp' terminal when it is defined rather than to the
 *	physical console.
 *	[ V5.1(XF21) ]
 *
 * 30-Sep-87  Richard Sanzi (sanzi) at Carnegie-Mellon University
 *	Added include of "machine/cpu.h" for the definition of
 *	cpu_number() (for non-multiprocessor systems).
 *
 * 31-Aug-87  David Black (dlb) at Carnegie-Mellon University
 *	MACH: multiprocessor panic logic.  If a second panic occurs
 *	on a different cpu, immediately stop that cpu.
 *
 * 27-Apr-87  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Changed dependency on command-line defined symbol RDB to
 *	include file symbol ROMP_RDB.  Include romp_rdb.h if compiling
 *	for romp.
 *
 * 27-Mar-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	allow a field size spec after the % for numeric fields
 *
 * 30-Jan-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Changed log() in the absence of a syslog daemon to
 *	only log messages on the console which are LOG_WARNING or
 *	higher priority (this requires a companion change to the syslog
 *	configuration file in order to have the same effect when syslog
 *	is running).
 *	[ V5.1(F1) ]
 *
 * 08-Jan-87  Robert Beck (beck) at Sequent Computer Systems, Inc.
 *	Add BALANCE case to panic().
 *
 * 21-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Merged in change for Sun to trap into kdb in panic().
 *
 *  7-Oct-86  David L. Black (dlb) at Carnegie-Mellon University
 *	Merged in Multimax changes; mostly due to register parameter passing.
 *
 * 13-Apr-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	CMUCS:  print table full messages on console in addition to
 *	loging them.
 *
 * 15-Feb-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Added different definitions of the parameter list for printf and
 *	uprintf under the assumption that the Sailboat c compiler needs
 *	them.  Switched on by romp.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 *  8-Sep-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	On a panic, issue a break point trap if kernel debugger present
 *	(and active).
 *
 * 26-Jun-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Modified panic() to generate a breakpoint trap
 *	before rebooting.
 *	[V1(1)]
 *
 * 14-Jun-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added (and modified) mprintf from Ultrix.
 *
 * 15-Sep-84  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Spiffed up printf b format. you can also give an entry of the form
 *	\#1\#2Title
 *	will print Title then extract the bits from #1 to #2 as a field and
 *	print it -- some devices have fields in their csr. consider
 *	vaxmpm/mpmreg.h as an example.
 *
 */

#include <cpus.h>
#include <cputypes.h>

#ifdef	ibmrt
#include <romp_rdb.h>
#endif	ibmrt

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)subr_prf.c	7.1 (Berkeley) 6/5/86
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/reboot.h>
#include <sys/msgbuf.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/syslog.h>
#ifdef	mips
#include <mips/varargs.h>
#endif	mips

#include <kern/lock.h>

#include <machine/cpu.h>	/* for cpu_number() */
#ifdef	vax
#include <vax/mtpr.h>
#endif

#define TOCONS	0x1
#define TOTTY	0x2
#define TOLOG	0x4
#ifdef	mips
#define TOPROM	0x8
#endif	mips

/*
 * In case console is off,
 * panicstr contains argument to last
 * call to panic.
 */
char	*panicstr;

/*
 *	Record cpu that panic'd and lock around panic data
 */
decl_simple_lock_data(,panic_lock)
int paniccpu;

/*
 *	For kernel debugging, allow panic() to return if
 *	so elected.
 */
int panic_return = 0;

/*
 * Scaled down version of C Library printf.
 * Used to print diagnostic information directly on console tty.
 * Since it is not interrupt driven, all system activities are
 * suspended.  Printf should not be used for chit-chat.
 *
 * One additional format: %b is supported to decode error registers.
 * Usage is:
 *	printf("reg=%b\n", regval, "<base><arg>*");
 * Where <base> is the output base expressed as a control character,
 * e.g. \10 gives octal; \20 gives hex.  Each arg is a sequence of
 * characters, the first of which gives the bit number to be inspected
 * (origin 1), and the next characters (up to a control character, i.e.
 * a character <= 32), give the name of the register.  Thus
 *	printf("reg=%b\n", 3, "\10\2BITTWO\1BITONE\n");
 * would produce output:
 *	reg=3<BITTWO,BITONE>
 *
 */
#ifdef	sparc
/*
 *	Taken from /usr/include/varargs.h
 */
typedef char *va_list;
# define va_alist __builtin_va_alist
# define va_dcl int va_alist;
# define va_start(list) list = (char *) &va_alist
# define va_end(list)
# define va_arg(list,mode) ((mode *)(list += sizeof(mode)))[-1]
#endif	sparc

/*VARARGS1*/
#if	defined(mips) || defined(sparc)
printf(fmt, va_alist)
 char *fmt;
 va_dcl
{
	va_list ap;

	va_start(ap);
	prf(fmt, ap, TOCONS | TOLOG, (struct tty *)0);
	va_end(ap);

	logwakeup();
}
#else	mips||sparc

#ifdef  luna88k
#include "varargs.h"
printf(fmt, va_alist)
char *fmt;
va_dcl
{
    va_list     ap;
    va_start(ap);
    {
	int s;
	s = spl6();
	prf(fmt, ap.__va_reg + 1, TOCONS | TOLOG, (struct tty *)0);
	splx(s);
    }
}
#else   !luna88k

#if	defined(multimax) || defined(ibmrt)
printf(fmt, x1, x2)
	register char *fmt; /* REGISTER for locore */
	unsigned x1, x2;
	/*
	 * This is needed on the MM since the first 2 parameters are in regs.
	 * Therefore x1 and x2 are not contiguous and prf cannot point at x2
	 * by incrementing a pointer to x1.
	 */
	/* I am including this on the assumption that x2 is necessary on
	 * the ibmrt due to lossage on the part of the ibmrt c compiler.
	 * -BJB
	 */
#else	defined(multimax) || defined(ibmrt)
printf(fmt, x1)
	char *fmt;
	unsigned x1;
#endif	defined(multimax) || defined(ibmrt)
{
#if	defined(ibmrt) && defined(lint)
	x2++;				/* Can't you just drop it ? */
#endif	defined(ibmrt) && defined(lint)

#ifdef	multimax
	prf(fmt, &x1, TOCONS | TOLOG, (struct tty *)0, &x2);
#else	multimax
	prf(fmt, &x1, TOCONS | TOLOG, (struct tty *)0);
#endif	multimax
	logwakeup();
}
#endif luna88k

#endif	mips||sparc

/*
 * Uprintf prints to the current user's terminal.
 * It may block if the tty queue is overfull.
 * Should determine whether current terminal user is related
 * to this process.
 */
/*VARARGS1*/
#if	defined(mips) || defined(sparc)
uprintf(fmt, va_alist)
	char *fmt;
	va_dcl
{
	register struct tty *tp;
	va_list ap;

	if ((tp = u.u_ttyp) == NULL)
		return;
	(void)ttycheckoutq(tp, 1);
	va_start(ap);
	prf(fmt, ap, TOTTY, tp);
	va_end(ap);
}
#else	mips || sparc
#ifdef  luna88k
uprintf(fmt, va_alist)
        char *fmt;
va_dcl
{
#ifdef notdef
    register struct proc *p;
#endif
    register struct tty *tp;
    va_list ap;

    va_start(ap);
    if ((tp = u.u_ttyp) == NULL)
	return;
#ifdef notdef
    if (tp->t_pgrp && (p = pfind(tp->t_pgrp)))
	if (p->p_uid != u.u_uid)        /* doesn't account for setuid */
	    return;
#endif
    (void)ttycheckoutq(tp, 1);
    prf(fmt, ap.__va_reg + 1, TOTTY, tp);
}
#else   luna88k
#if	defined(multimax) || defined(ibmrt)
uprintf(fmt, x1, x2)
	char *fmt;
	unsigned x1, x2;
	/*
	 * Ditto.
	 */
#else	defined(multimax) || defined(ibmrt)
uprintf(fmt, x1)
	char *fmt;
	unsigned x1;
#endif	defined(multimax) || defined(ibmrt)
{
	register struct tty *tp;

#if	defined(ibmrt) && defined(lint)
	x2++;
#endif	defined(ibmrt) && defined(lint)

	if ((tp = u.u_ttyp) == NULL)
		return;
	(void)ttycheckoutq(tp, 1);
#ifdef	multimax
	prf(fmt, &x1, TOTTY, tp, &x2);
#else	multimax
	prf(fmt, &x1, TOTTY, tp);
#endif	multimax
}
#endif	mips || sparc
#endif luna88k

/*
 * tprintf prints on the specified terminal (console if none)
 * and logs the message.  It is designed for error messages from
 * single-open devices, and may be called from interrupt level
 * (does not sleep).
 */
/*VARARGS2*/
#ifdef	mips
tprintf(tp, fmt, va_alist)
	register struct tty *tp;
	char *fmt;
	va_dcl
{
	int flags = TOTTY | TOLOG;
	extern struct tty cons[];
	va_list(ap);

	logpri(LOG_INFO);
	if (tp == (struct tty *)NULL)
		tp = cons;
	if (ttycheckoutq(tp, 0) == 0)
		flags = TOLOG;
	va_start(ap);
	prf(fmt, ap, flags, tp);
	va_end(ap);
	logwakeup();
}
#else	mips
#ifdef  luna88k
tprintf(tp, fmt, va_alist)
        register struct tty *tp;
        char *fmt;
        va_dcl
#else   luna88k
#ifdef	multimax
tprintf(tp, fmt, x1, x2)
	struct tty *tp;
	char *fmt;
	unsigned x1, x2;
/*
 * This is needed on the MM in order to be compat with printf.
 */
#else	multimax
tprintf(tp, fmt, x1)
	register struct tty *tp;
	char *fmt;
	unsigned x1;
#endif	multimax
#endif  luna88k
{
	int flags = TOTTY | TOLOG;

/* Multimax console is just another tty, nothing special */
#ifdef	multimax
extern	struct	tty slc_tty[];
#define cons	(slc_tty[0])
#else	multimax
#ifdef  luna88k
    va_list ap;
    extern  struct tty cons_tty[];
#define cons    (cons_tty[0]);
#else   luna88k
	extern struct tty cons;
#endif  luna88k
#endif	multimax

#ifdef  luna88k
    va_start(ap);
    flags = TOTTY | TOLOG;
#endif  luna88k

	logpri(LOG_INFO);
	if (tp == (struct tty *)NULL)
		tp = &cons;
	if (ttycheckoutq(tp, 0) == 0)
		flags = TOLOG;
#ifdef  luna88k
    prf(fmt, ap.__va_reg + 1, flags, tp);
#else   luna88k
#ifdef	multimax
	prf(fmt, &x1, flags, tp, &x2);
#else	multimax
	prf(fmt, &x1, flags, tp);
#endif	multimax
#endif  luna88k
	logwakeup();
}
#endif	mips

/*
 * make an additional log entry at the sape priority
 */

#if	defined(mips) || defined(sparc)
addlog(fmt, va_alist)
	char *fmt;
	va_dcl
{
	register s = splhigh();
	extern int log_open;
	va_list(ap);

	va_start(ap);
	prf(fmt, ap, TOLOG, (struct tty *)0);
	splx(s);
	if (!log_open)
		prf(fmt, ap, TOCONS, (struct tty *)0);
	logwakeup();
	va_end(ap);
}
#else	/* mips || sparc */
#ifdef  luna88k
addlog(fmt, va_alist)
      char *fmt;
      va_dcl
#else   luna88k
#ifdef	multimax
addlog(fmt, x1, x2)
	char *fmt;
	unsigned int x1, x2;
#else	/* multimax */
addlog(fmt, x1)
	char *fmt;
	unsigned int x1;
#endif	/* multimax */
#endif  /* luna88k */
{
#ifdef  luna88k
    register s;
    extern int log_open;
    va_list ap;
    va_start(ap);
    s = splhigh();
#else   luna88k
	register s = splhigh();
	extern int log_open;
#endif luna88k

#ifdef  luna88k
    prf(fmt, ap.__va_reg + 2, TOLOG, (struct tty *)0);
#else   luna88k
#ifdef	multimax
	prf(fmt, &x1, TOLOG, (struct tty *)0, &x2);
#else	multimax
	prf(fmt, &x1, TOLOG, (struct tty *)0);
#endif	multimax
#endif  luna88k
	splx(s);
	if (!log_open)
#ifdef  luna88k
		/*  Changed from "+ 1" to  "+ 2"     K.Inui 02/16/90' */
		prf(fmt, ap.__va_reg + 2, TOCONS, (struct tty *)0);
#else   luna88k
#ifdef	multimax
		prf(fmt, &x1, TOCONS, (struct tty *)0, &x2);
#else	multimax
		prf(fmt, &x1, TOCONS, (struct tty *)0);
#endif	multimax
#endif  luna88k
	logwakeup();
}
#endif	/* mips */

/*
 * Log writes to the log buffer,
 * and guarantees not to sleep (so can be called by interrupt routines).
 * If there is no process reading the log yet, it writes to the console also.
 */
/*VARARGS2*/
#if	defined(mips) || defined(sparc)
log(level, fmt, va_alist)
	char *fmt;
	va_dcl
{
	register s = splhigh();
	extern int log_open;
	va_list ap;

	logpri(level);
	va_start(ap);
	prf(fmt, ap, TOLOG, (struct tty *)0);
	splx(s);
	if (!log_open)
	    if ((level&LOG_PRIMASK) <= LOG_NOTICE)
		prf(fmt, ap, TOCONS, (struct tty *)0);
	va_end(ap);
	logwakeup();
}
#else	mips||sparc
#ifdef  luna88k
log(level, fmt, va_alist)
      char *fmt;
      va_dcl
#else   luna88k
#ifdef	multimax
log(level, fmt, x1, x2)
	char *fmt;
	unsigned int	x1, x2;
/*
 * This is needed on the MM in order to be compat with printf.
 */
#else	multimax
log(level, fmt, x1)
	char *fmt;
	unsigned x1;
#endif	multimax
#endif  luna88k
{
#ifdef  luna88k
    register s;
    extern int log_open;
    va_list ap;
    va_start(ap);
    s = splhigh();
#else   luna88k
	register s = splhigh();
	extern int log_open;
#endif  luna88k

	logpri(level);
#ifdef  luna88k
    prf(fmt, ap.__va_reg + 2, TOLOG, (struct tty *)0);
#else   luna88k
#ifdef	multimax
	prf(fmt, &x1, TOLOG, (struct tty *)0, &x2);
#else	multimax
	prf(fmt, &x1, TOLOG, (struct tty *)0);
#endif	multimax
#endif  luna88k
	splx(s);
	if (!log_open)
#ifdef  luna88k
	    if ((level&LOG_PRIMASK) <= LOG_WARNING)
		/*  Changed from "+ 1" to  "+ 2"     K.Inui 02/16/90' */
		prf(fmt, ap.__va_reg + 2, TOCONS, (struct tty *)0);
#else   luna88k
	    if ((level&LOG_PRIMASK) <= LOG_NOTICE)
#ifdef	multimax
		prf(fmt, &x1, TOCONS, (struct tty *)0, &x2);
#else	multimax
		prf(fmt, &x1, TOCONS, (struct tty *)0);
#endif	multimax
#endif  luna88k
	logwakeup();
}
#endif	mips||sparc

logpri(level)
	int level;
{

	putchar('<', TOLOG, (struct tty *)0);
	printn((u_long)level, 10, TOLOG, (struct tty *)0, 0, 0);
	putchar('>', TOLOG, (struct tty *)0);
}

#if	NCPUS > 1
boolean_t	new_printf_cpu_number = FALSE;
decl_simple_lock_data(,printf_lock)
#endif	NCPUS > 1
#ifdef	multimax
prf(fmt, adx1, flags, ttyp, adx2)
	register char *fmt;
	struct tty *ttyp;
	u_int *adx1,*adx2;
#else	multimax
prf(fmt, adx, flags, ttyp)
	register char *fmt;
	struct tty *ttyp;
	u_int *adx;
#endif	multimax
{
#ifdef	multimax
	register u_int *adx = adx1;
#endif	multimax
	register int b, c, i;
	char *s;
	int any;
	int base;
	int zf, fld_size;

#if	NCPUS > 1
	int cpun = cpu_number();

	simple_lock(&printf_lock);
#if	VAX6200
	if (cpu == VAX_6200) {
		extern int printing_cpu;
		if (printing_cpu != cpun)
			acquire_console(cpun);
	}
#endif	VAX6200
	if (cpun != master_cpu)
		new_printf_cpu_number = TRUE;

	if (new_printf_cpu_number) {
		putchar('{', flags, ttyp);
		printn(cpun, 10, flags, ttyp, 0, 0);
		putchar('}', flags, ttyp);
	}
#endif	NCPUS > 1
loop:
	while ((c = *fmt++) != '%') {
		if (c == '\0') {
#if	NCPUS > 1
			simple_unlock(&printf_lock);
#endif	NCPUS > 1
			return;
		}
		putchar(c, flags, ttyp);
	}
again:
	zf = 0; fld_size = 0;
	c = *fmt++;
	if (c == '0')
		zf = '0';
	for (;c <= '9' && c >= '0'; c = *fmt++)
		fld_size = fld_size * 10 + c - '0';
	
	/* THIS CODE IS VAX DEPENDENT IN HANDLING %l? AND %c */
	switch (c) {

	case 'l':
		goto again;
	case 'x': case 'X':
		b = 16;
		goto number;
	case 'd': case 'D':
	case 'u':		/* what a joke */
		b = 10;
		goto number;
	case 'o': case 'O':
		b = 8;
number:
		printn((u_long)*adx, b, flags, ttyp, zf, fld_size);
		break;
	case 'c':
		b = *adx;
		for (i = 24; i >= 0; i -= 8)
			if (c = (b >> i) & 0x7f)
				putchar(c, flags, ttyp);
		break;
	case 'b':
#ifdef	multimax
		b = *adx;
		/* Take care of noncontiguous args */
		adx = adx == adx1 ? adx2 : adx + 1;
#else	multimax
		b = *adx++;
#endif	multimax
		s = (char *)*adx;
		base = *s++;
		printn((u_long)b, base, flags, ttyp, 0, 0);
		any = 0;
		if (b) {
			while (i = *s++) {
				if (*s <= 32) {
					register int j;
					register int fld;

					j = *s++;
					fld = ( (b >> (j-1)) & ( (2 << (i-j)) -1));
					if (fld) {
						putchar(any++? ',' : '<', flags, ttyp);
						for (; (c = *s) > 32 ; s++)
							putchar(c, flags, ttyp);
						putchar('=', flags, ttyp);
						printn( (u_long) fld, base, flags, ttyp, 0, 0);
					} else
						for (; (c = *s) > 32 ; s++) /* skip name */;
				} else if (b & (1 << (i-1))) {
					putchar(any? ',' : '<', flags, ttyp);
					any = 1;
					for (; (c = *s) > 32; s++)
						putchar(c, flags, ttyp);
				} else
					for (; *s > 32; s++)
						;
			}
				putchar('>', flags, ttyp);
		}
		break;

	case 's':
		s = (char *)*adx;
		while (c = *s++)
			putchar(c, flags, ttyp);
		break;

	case '%':
		putchar('%', flags, ttyp);
		break;

	}
#ifdef	multimax
	/* Take care of noncontiguous args */
	adx = adx == adx1 ? adx2 : adx + 1;
#else	multimax
	adx++;
#endif	multimax
	goto loop;
}

/*
 * Printn prints a number n in base b.
 * We don't use recursion to avoid deep kernel stacks.
 */
printn(n, b, flags, ttyp, zf, fld_size)
	u_long n;
	struct tty *ttyp;
{
	char prbuf[11];
	register char *cp;

	if (b == 10 && (int)n < 0) {
		putchar('-', flags, ttyp);
		n = (unsigned)(-(int)n);
	}
	cp = prbuf;
	do {
		*cp++ = "0123456789abcdef"[n%b];
		n /= b;
	} while (n);
	if (fld_size) {
		for (fld_size -= cp - prbuf; fld_size > 0; fld_size--)
			if (zf)
				putchar('0', flags, ttyp);
			else
				putchar(' ', flags, ttyp);
	}
	do
		putchar(*--cp, flags, ttyp);
	while (cp > prbuf);
}

panic_init()
{
  simple_lock_init(&panic_lock);
}

/*
 * Panic is called on unresolvable fatal errors.
 * It prints "panic: mesg", and then reboots.
 * If we are called twice, then we avoid trying to
 * sync the disks as this often leads to recursive panics.
 */
panic(s)
	char *s;
{
	int bootopt = RB_AUTOBOOT;

	simple_lock(&panic_lock);
	if (panicstr) {
	    if (cpu_number() == paniccpu) {
		bootopt |= RB_NOSYNC;
	    }
	    else {
		simple_unlock(&panic_lock);
		halt_cpu();
		/* NOTREACHED */
	    }
	}
	else {
	    panicstr = s;
	    paniccpu = cpu_number();
	}
	simple_unlock(&panic_lock);
#if	defined(mac2)
	spl7();
	{
	  extern struct tty *xcons_tp;

	  xcons_tp = 0;
	}
#endif	defined(mac2)
#if	NCPUS > 1
	printf("panic: (Cpu %d) %s\n", (unsigned) paniccpu, s);
#else	NCPUS > 1
	printf("panic: %s\n", s);
#endif	NCPUS > 1

#ifdef	i386
#include <mach_kdb.h>
#if	MACH_KDB > 0
	Bpt();
#endif	MACH_KDB > 0
#endif	i386
#ifdef	vax
	if (boothowto&RB_KDB)
	    asm("bpt");
#endif	vax
#if	defined(sun3)
	if (!current_thread())
		halt("panic");
	if (boothowto & RB_KDB)
	    asm("trap #15");
#endif	sun3
#ifdef	sun4
	if (!current_thread())
		halt("panic");
	if (boothowto & RB_KDB)
	    asm("ta 0x81");
#endif	sun4
#ifdef	multimax
	if (boothowto&RB_DEBUG)
	    bpt("panic");
#endif	multimax
#if	ROMP_RDB
	Debugger("panic");
	printf("panic: calling boot...", (unsigned) 0, (unsigned) 0);
#endif	ROMP_RDB
#ifdef	balance
	sqtpanic(s);
#endif	balance
#ifdef	mips
	Debugger("panic");
#endif	mips

	if (panic_return)
		return;

	boot(RB_PANIC, bootopt);
}

/*
 * Warn that a system table is full.
 */
tablefull(tab)
	char *tab;
{

	printf("%s: table is full\n", (unsigned) tab);
	log(LOG_ERR, "%s: table is full\n", (unsigned) tab);
}

/*
 * Hard error is the preface to plaintive error messages
 * about failing disk transfers.
 */
harderr(bp, cp)
	struct buf *bp;
	char *cp;
{
#ifdef	mips
	printf("%s%d%c: hard error sn%d ", cp,
	    minor(bp->b_dev) >> 4, 'a'+(minor(bp->b_dev)&0xf), bp->b_blkno);
#else	mips
#if	CS_GENERIC
	printf("%s%d%c: hard error sn%d ", (unsigned) cp,
	    (unsigned) minor(bp->b_dev) >> 3, 'a'+(minor(bp->b_dev)&07), bp->b_blkno);
#else	CS_GENERIC
	printf("%s%d%c: hard error sn%d ", cp,
	    minor(bp->b_dev) >> 3, 'a'+(minor(bp->b_dev)&07), bp->b_blkno);
#endif	CS_GENERIC
#endif	mips
}

/*
 * Print a character on console or users terminal.
 * If destination is console then the last MSGBUFS characters
 * are saved in msgbuf for inspection later.
 */
/*ARGSUSED*/
putchar(c, flags, tp)
	register int c;
	struct tty *tp;
{
#ifdef	mips
#define msgbuf (*pmsgbuf)

	if (flags & TOPROM) {
		prom_putchar(c);
	}
#endif	mips
totty:
	if (flags & TOTTY) {
		register s = spltty();

		if (tp && (tp->t_state & (TS_CARR_ON | TS_ISOPEN)) ==
		    (TS_CARR_ON | TS_ISOPEN)) {
			if (c == '\n')
				(void) ttyoutput('\r', tp);
			(void) ttyoutput(c, tp);
			ttstart(tp);
		}
		splx(s);
	}
	if ((flags & TOLOG) && c != '\0' && c != '\r' && c != 0177
#ifdef	vax
	    && mfpr(MAPEN)
#endif
	    ) {
		if (msgbuf.msg_magic != MSG_MAGIC) {
			register int i;

			msgbuf.msg_magic = MSG_MAGIC;
			msgbuf.msg_bufx = msgbuf.msg_bufr = 0;
			for (i=0; i < MSG_BSIZE; i++)
				msgbuf.msg_bufc[i] = 0;
		}
		msgbuf.msg_bufc[msgbuf.msg_bufx++] = c;
		if (msgbuf.msg_bufx < 0 || msgbuf.msg_bufx >= MSG_BSIZE)
			msgbuf.msg_bufx = 0;
	}
	if ((flags & TOCONS) && c != '\0') {
		extern struct tty *xcons_tp;

		if (xcons_tp == 0)
			cnputc(c);
		else
		{
			flags = TOTTY;
			tp = xcons_tp;
			goto totty;
		}
	}
}

#ifdef	mips
/*
 *	dprintf uses the prom code to get to the console,
 *	presumably to the debugger's remote console
 */
/*VARARGS*/
dprintf(fmt, va_alist)
 char *fmt;
 va_dcl
{

	va_list(ap);
	va_start(ap);
	prf(fmt, ap, TOPROM, (struct tty *)0);
	va_end(ap);
}


puts(s, flags, ttyp)
	register char *s;
	int flags;
	struct tty *ttyp;
{
	while (*s)
		putchar(*s++, flags, ttyp);
}

#endif	mips
