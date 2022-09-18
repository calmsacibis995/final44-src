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
 * $Log:	Locore.c,v $
 * Revision 2.6  89/03/09  22:12:28  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  20:10:54  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  88/08/30  00:11:15  mwyoung
 * 	Corrected include file references.
 * 
 * 22-Aug-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Corrected include file references.
 *
 *  3-Apr-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH: Provide some new declarations, remove unused ones.
 *	There's still lots of work to do to this file.
 *
 * 13-Mar-87  David Golub (dbg) at Carnegie-Mellon University
 *	More delinting, for MACH and MACH.
 *
 *  2-Jan-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Delinting, for MACH.
 *
 */ 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)Locore.c	7.1 (Berkeley) 6/5/86
 */
 
#include <cputypes.h>

#include <dz.h>
#include <mba.h>
#include <uba.h>

#include <vax/pte.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/vm.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/msgbuf.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/domain.h>
#include <sys/map.h>

#include <vax/nexus.h>
#include <vax/ioa.h>
#include <vax/ka630.h>
#include <vaxuba/ubavar.h>
#include <vaxuba/ubareg.h>

/*
 * Pseudo file for lint to show what is used/defined in locore.s.
 */

struct	scb scb;
int	(*UNIvec[128])();
#if	NUBA > 1
int	(*UNI1vec[128])();
#endif
struct	rpb rpb;
int	dumpflag;
int	intstack[3*NBPG];
int	masterpaddr;		/* p_addr of current process on master cpu */
/*
 * Variables declared for savecore, or
 * implicitly, such as by config or the loader.
 */
char	version[] = "4.2 BSD UNIX ....";
int	etext;

doadump() { dumpsys(); }

Xmba3int() { }
Xmba2int() { }
Xmba1int() { }
Xmba0int() { }

lowinit()
{
#if	!defined(GPROF)
	caddr_t cp;
#endif
	extern int dumpmag;
	extern int rthashsize;
	extern int arptab_size;
	extern int dk_ndrive;
	extern struct domain unixdomain;
#ifdef	PUP
	extern struct domain pupdomain;
#endif
#ifdef	INET
	extern struct domain inetdomain;
#endif
#include <imp.h>
#if	NIMP > 0
	extern struct domain impdomain;
#endif
#ifdef	NS
	extern struct domain nsdomain;
#endif

	/* cpp messes these up for lint so put them here */
	unixdomain.dom_next = domains;
	domains = &unixdomain;
#ifdef	PUP
	pupdomain.dom_next = domains;
	domains = &pupdomain;
#endif
#ifdef	INET
	inetdomain.dom_next = domains;
	domains = &inetdomain;
#endif
#if	NIMP > 0
	impdomain.dom_next = domains;
	domains = &impdomain;
#endif
#ifdef	NS
	nsdomain.dom_next = domains;
	domains = &nsdomain;
#endif
	dumpmag = 0;			/* used only by savecore */
	rthashsize = rthashsize;	/* used by netstat, etc. */
	arptab_size = arptab_size;	/* used by arp command */
	dk_ndrive = dk_ndrive;		/* used by vmstat, iostat, etc. */

	/*
	 * Pseudo-uses of globals.
	 */
	lowinit();
	intstack[0] = intstack[1];
	rpb = rpb;
	scb = scb;
	maxmem = physmem = 0;
	fixctlrmask();
	main(0);
	Xustray();

	/*
	 * Routines called from interrupt vectors.
	 */
	panic("Machine check");
	printf("Write timeout");
	(*UNIvec[0])();
#if	NUBA > 1
	(*UNI1vec[0])();
#endif
	ubaerror(0, (struct uba_hd *)0, 0, 0, (struct uba_regs *)0);
	cnrint(0);
	cnxint(0);
	consdin();
	consdout();
#if	NDZ > 0
	dzdma();
#endif
#if	NMBA > 0
	mbintr(0);
#endif
	hardclock((caddr_t)0, 0);
	softclock((caddr_t)0, 0);
	trap(0, 0, (unsigned)0, 0, 0);
	syscall(0, 0, (unsigned)0, 0, 0);
	rawintr();
#ifdef	INET
	ipintr();
#endif
#ifdef	NS
	nsintr();
#endif

	machinecheck((caddr_t)0);
	memerr();
	boothowto = 0;
	dumpflag = 0; dumpflag = dumpflag;
#if	!defined(GPROF)
	cp = (caddr_t)&etext;
	cp = cp;
#endif
}

consdin() { }
consdout() { }
#if	NDZ > 0
dzdma() { dzxint((struct tty *)0); }
#endif

int	catcher[256];
int	cold = 1;

Xustray() { }

/*
 *	Would you believe that none of this is in locore.s for Mach?
 */

/*ARGSUSED*/
badaddr(addr, len) caddr_t addr; int len; { return (0); }

/*ARGSUSED*/
ovbcopy(from, to, len) caddr_t from, to; unsigned len; { }
copyinstr(udaddr, kaddr, maxlength, lencopied)
    caddr_t udaddr, kaddr; u_int maxlength, *lencopied;
{ *kaddr = *udaddr; *lencopied = maxlength; return (0); }
copyoutstr(kaddr, udaddr, maxlength, lencopied)
    caddr_t kaddr, udaddr; u_int maxlength, *lencopied;
{ *udaddr = *kaddr; *lencopied = maxlength; return (0); }
copystr(kfaddr, kdaddr, maxlength, lencopied)
    caddr_t kfaddr, kdaddr; u_int maxlength, *lencopied;
{ *kdaddr = *kfaddr; *lencopied = maxlength; return (0); }

/*ARGSUSED*/
copyin(udaddr, kaddr, n) caddr_t udaddr, kaddr; u_int n; { return (0); }
/*ARGSUSED*/
copyout(kaddr, udaddr, n) caddr_t kaddr, udaddr; u_int n; { return (0); }

/*ARGSUSED*/
longjmp(lp) label_t *lp; { /*NOTREACHED*/ }


/*ARGSUSED*/
addupc(pc, prof, counts) int pc; struct uprof *prof; int counts; { }

/*
 * Routines expanded by inline.
 */
spl0() { }
splsoftclock() { return (0); }
splnet() { return (0); }
spl4() { return (0); }
spl5() { return (0); }
splbio() { return (0); }
spltty() { return (0); }
#ifdef	notdef
spl6() { return (0); }		/* not currently used */
#endif
splclock() { return (0); }
spl7() { return (0); }
splhigh() { return (0); }

/*ARGSUSED*/
splx(s) int s; { }

/*ARGSUSED*/
bcopy(from, to, len) caddr_t from, to; unsigned len; { }
/*ARGSUSED*/
bzero(base, count) caddr_t base; unsigned count; { }
/*ARGSUSED*/
blkclr(base, count) caddr_t base; unsigned count; { }

/*ARGSUSED*/
/*VARARGS1*/
mtpr(reg, v) int reg; { }
/*ARGSUSED*/
mfpr(reg) int reg; { return (0); }

/*ARGSUSED*/
setjmp(lp) label_t *lp; { return (0); }

#ifdef	notdef
/*ARGSUSED*/
scanc(size, cp, table, mask)
    unsigned size; char *cp, table[]; int mask;
{ return (0); }
#endif	notdef

/*ARGSUSED*/
skpc(mask, size, cp) int mask; int size; char *cp; { return (0); }

#ifdef	notdef
/*ARGSUSED*/
locc(mask, size, cp) int mask; char *cp; unsigned size; { return (0); }
#endif

/*ARGSUSED*/
_insque(p, q) caddr_t p, q; { }
/*ARGSUSED*/
_remque(p) caddr_t p; { }

/*ARGSUSED*/
ffs(v) long v; { return (0); }

#ifdef	notdef
imin(a, b) int a, b; { return (a < b ? a : b); }
imax(a, b) int a, b; { return (a > b ? a : b); }
unsigned min(a, b) u_int a, b; { return (a < b ? a : b); }
unsigned max(a, b) u_int a, b; { return (a > b ? a : b); }
#endif
u_short ntohs(s) u_short s; { return ((u_short)s); }
u_short htons(s) u_short s; { return ((u_short)s); }
u_long ntohl(l) u_long l; { return ((u_long)l); }
u_long htonl(l) u_long l; { return ((u_long)l); }

/*
 *	Code addresses where faulting can occur; declared as "int"
 *	for simplicity.
 */

int	ALLOW_FAULT_START;
int	ALLOW_FAULT_END;
int	FAULT_ERROR;
