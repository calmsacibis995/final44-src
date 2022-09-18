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
 * $Log:	subr_mcount.c,v $
 * Revision 2.7.1.1  90/02/27  08:47:06  rvb
 * 	Enable i386 profiling under gcc
 * 	[90/02/26            rvb]
 * 
 * Revision 2.7  89/03/09  19:30:38  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/25  14:45:40  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  89/02/09  04:32:50  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.4  89/01/23  22:06:26  af
 * 	Changes for I386.
 * 		(But is this correct -- rvb)
 * 	[89/01/09            rvb]
 * 	
 * 	Added Mips profiling code.
 * 	[89/01/08            af]
 * 
 * 29-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Sun must call mcount with frompc, and selfpc as args when we use
 *	gcc since regs get reorganized.  The compiler would emit mcount
 *	which would then call the "counting" code correctly.  BUT,
 *	gprof knows enough to only subtract out the time accumulated by
 *	mcount and not this new routine.  So for now I'll use pcc to build
 *	this file.  The "correct mcount" is found in vax.s
 *
 * 14-Dec-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Set up profiling for sun (68020) architecture.  And, 
 *	Fix splXXX calls so that we may call a special version, np_splXXX,
 *	tp be sure not to profile the calls to splXXX in mcount.  This
 *	is currently used only by the sun, and may go away totally some
 *	day when the sun uses inline.
 *
 * 31-Aug-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	1) The label overflow did not splx(s) before it exited
 *	2) "s=splhigh()" Does not work when s is static and the
 *	expansion of s=splhigh() is smart enough to store the spl
 *	directly into s.  An interrupt can now come and clobber s, before
 *	the spl is set high.  This happens on the sequent.  So s must
 *	either be a register (which we have no more of) or an automatic.
 *	Whether this problem happens for your machine depends on how
 *	s=splhigh() expands.
 *
 * 26-Jun-87  David Black (dlb) at Carnegie-Mellon University
 *	MULTIMAX: mcount --> mmax_mcount due to trampoline code.
 *
 *  2-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Fixed recent Sequent change to not return if we are not on the
 *	master, instead, we must goto out (to allow Vaxen to rsb).  Also
 *	moved the check for if we are profiling earlier in mcount to
 *	attempt to curtail problems trying to profile bootstrapping code
 *	(like trying to compare cpu_number against master_cpu before
 *	setting either of them!).
 *
 * 30-Mar-87  David Black (dlb) at Carnegie-Mellon University
 *	MULTIMAX changes -- a model for how to do this right.
 *
 * 20-Mar-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	munged to work on sequent.
 *
 * 27-Feb-87  Rich Sanzi (sanzi) at Carnegie-Mellon University
 *	Added additional RT support for profiling.  Changes included
 *	adding rt specific code under switch ibmrt and changing the value
 *	of s_lowpc.
 *
 * 29-May-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Initialize "s_lowpc" to "start" for Sun.
 *
 * 14-Feb-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Added different definition of s_lowpc for Sailboat under switch
 *	ibmrt.
 *
 */
#include <cputypes.h>

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)subr_mcount.c	7.1 (Berkeley) 6/5/86
 */

/* last integrated from: gmon.c	4.10 (Berkeley) 1/14/83 */

#ifdef	GPROF
#include <sys/gprof.h>
#include <sys/param.h>
#include <sys/systm.h>
#include <machine/cpu.h>

int profiling = 3;

#if	!defined(mips)

/*
 * Froms is actually a bunch of unsigned shorts indexing tos
 */
u_short *froms;
struct tostruct *tos = 0;
long tolimit = 0;

#ifdef	i386
char	*s_lowpc = (char *)0xc0000000;
#define TOSFRACTION	100
#endif

#ifdef	vax
char	*s_lowpc = (char *)0x80000000;
#define TOSFRACTION	100
#endif

#ifdef	ibmrt
char    *s_lowpc = (char *)0xe0000000;
#define TOSFRACTION	200
#endif	ibmrt

#ifdef	sun
char	*s_lowpc = (char *)0x0e000000;
#define TOSFRACTION	100
#endif	sun

#ifdef	ns32000
char 	*s_lowpc = (char *) 0x0;
#define TOSFRACTION	100

#include <vm/vm_kern.h>
#define calloc(size) ((caddr_t)kmem_alloc(kernel_map, size, TRUE))
#endif	ns32000

#if	defined(sun)
#define spl_high()	np_splhigh()
#define spl_x(x)	np_splx(x)
#else	defined(sun)
#if	defined(i386)
#define spl_high()	sploff()
#define spl_x(x)	splon(x)
#else	defined(i386)
#define spl_high() 	splhigh()
#define spl_x(x)	splx(x)
#endif	defined(i386)
#endif	defined(sun)

extern char etext;

char *s_highpc = &etext;
u_long	s_textsize = 0;

int ssiz;
u_short	*sbuf;
u_short	*kcount;

kmstartup()
{
	u_long	fromssize, tossize;

	/*
	 *	round lowpc and highpc to multiples of the density we're using
	 *	so the rest of the scaling (here and in gprof) stays in ints.
	 */
	s_lowpc = (char *)
	    ROUNDDOWN((unsigned)s_lowpc, HISTFRACTION*sizeof(HISTCOUNTER));
	s_highpc = (char *)
	    ROUNDUP((unsigned)s_highpc, HISTFRACTION*sizeof(HISTCOUNTER));
	s_textsize = s_highpc - s_lowpc;
	printf("Profiling kernel, s_textsize=%d [%x..%x]\n",
		s_textsize, s_lowpc, s_highpc);
	ssiz = (s_textsize / HISTFRACTION) + sizeof(struct phdr);
	sbuf = (u_short *)calloc(ssiz);
	if (sbuf == 0) {
		printf("No space for monitor buffer(s)\n");
		return;
	}
	blkclr((caddr_t)sbuf, ssiz);
	fromssize = s_textsize / HASHFRACTION;
	froms = (u_short *)calloc(fromssize);
	if (froms == 0) {
		printf("No space for monitor buffer(s)\n");
		cfreemem(sbuf, ssiz);
		sbuf = 0;
		return;
	}
	blkclr((caddr_t)froms, fromssize);
 
	tolimit = s_textsize * ARCDENSITY / TOSFRACTION;
	if (tolimit < MINARCS) {
		tolimit = MINARCS;
	} else if (tolimit > 65534) {
		tolimit = 65534;
	}
	tossize = tolimit * sizeof(struct tostruct);
	tos = (struct tostruct *)calloc(tossize);
	if (tos == 0) {
		printf("No space for monitor buffer(s)\n");
		cfreemem(sbuf, ssiz);
		sbuf = 0;
		cfreemem(froms, fromssize);
		froms = 0;
		return;
	}
	blkclr((caddr_t)tos, tossize);
	tos[0].link = 0;
	((struct phdr *)sbuf)->lpc = s_lowpc;
	((struct phdr *)sbuf)->hpc = s_highpc;
	((struct phdr *)sbuf)->ncnt = ssiz;
	kcount = (u_short *)(((int)sbuf) + sizeof(struct phdr));
#ifdef	notdef
	/*
	 *	profiling is what mcount checks to see if
	 *	all the data structures are ready!!!
	 */
	profiling = 0;		/* patch by hand when you're ready */
#endif
}

#if	defined(i386)
extern int mcount() __asm__ ("mcount");
#endif	defined(i386)

#if	defined(vax) || defined(balance) || defined(sun)
/*
 * This routine is massaged so that it may be jsb'ed to
 */
asm(".text");
asm("#the beginning of mcount()");
asm(".data");
#endif	defined(vax) || defined(balance) || defined(sun)

#if	defined(vax) || defined(ibmrt) || defined(ns32000) || defined(sun) || defined(i386)

#if	multimax
mmax_mcount(selfpc, frompcindex)
register char		*selfpc;
register unsigned short	*frompcindex;
{
	register struct tostruct	*top;
	register struct tostruct	*prevtop;
	register long			toindex;
#else	multimax
mcount()
{
	register char			*selfpc;	/* r11 => r5 */
	register unsigned short		*frompcindex;	/* r10 => r4 */
	register struct tostruct	*top;		/* r9  => r3 */
	register struct tostruct	*prevtop;	/* r8  => r2 */
	register long			toindex;	/* r7  => r1 */
#endif	multimax
#ifdef	balance
	int s;
#else	balance
	static int s;
#endif	balance

	if (profiling)
		goto out;
	if (cpu_number() != master_cpu)
		goto out;
#ifdef	lint
	selfpc = (char *)0;
	frompcindex = 0;
#else	not lint
	/*
	 *	find the return address for mcount,
	 *	and the return address for mcount's caller.
	 */
#ifdef	vax	 
	asm("	.text");		/* make sure we're in text space */
	asm("	movl (sp), r11");	/* selfpc = ... (jsb frame) */
	asm("	movl 16(fp), r10");	/* frompcindex =     (calls frame) */
#endif	vax	
#if	defined(balance)
	asm("	.text");		/* make sure we're in text space */
	asm("	movd 4(fp), r7");
	asm("	movd 4(0(fp)), r6");
#endif	defined(balance)
#if	defined(sun)
	asm("	.text");		/* make sure we're in text space */
	asm("	movl a6@(4), a5");	/* selfpc */
	asm("	movl a6@,a0");
	asm("	movl a0@(4), a4");	/* frompc */
#endif	defined(sun)
#if	defined(i386)
#define SelfPc() \
({ int _spl__, _tmp1__; \
	asm volatile("movl 4(%%ebp), %0" : "=r" (_spl__) : "r" (_tmp1__)); \
	_spl__; })
#define FromPc() \
({ int _spl__, _tmp1__; \
	asm volatile("movl (%%ebp), %0; movl 4(%0), %0" : "=r" (_spl__) : "r" (_tmp1__)); \
	_spl__; })

	selfpc = (char *)SelfPc();
	frompcindex = (unsigned short *)FromPc();
#endif	defined(i386)
#endif	not lint
	/*
	 *	Moved to above
	 */
#ifdef	ibmrt
	/*
	 *	and that we aren't recursively invoked.
	 */
	profiling++;
#endif	ibmrt	
	/*
	 *	insure that we cannot be recursively invoked.
	 *	this requires that splhigh() and splx() below
	 *	do NOT call mcount!
	 */
	s = spl_high();
	/*
	 *	check that frompcindex is a reasonable pc value.
	 *	for example:	signal catchers get called from the stack,
	 *			not from text space.  too bad.
	 */
	frompcindex = (unsigned short *)((long)frompcindex - (long)s_lowpc);
	if ((unsigned long)frompcindex > s_textsize) {
		goto done;
	}
	frompcindex =
	    &froms[((long)frompcindex) / (HASHFRACTION * sizeof(*froms))];
	toindex = *frompcindex;
	if (toindex == 0) {
		/*
		 *	first time traversing this arc
		 */
		toindex = ++tos[0].link;
		if (toindex >= tolimit) {
			goto overflow;
		}
		*frompcindex = toindex;
		top = &tos[toindex];
		top->selfpc = selfpc;
		top->count = 1;
		top->link = 0;
		goto done;
	}
	top = &tos[toindex];
	if (top->selfpc == selfpc) {
		/*
		 *	arc at front of chain; usual case.
		 */
		top->count++;
		goto done;
	}
	/*
	 *	have to go looking down chain for it.
	 *	top points to what we are looking at,
	 *	prevtop points to previous top.
	 *	we know it is not at the head of the chain.
	 */
	for (; /* goto done */; ) {
		if (top->link == 0) {
			/*
			 *	top is end of the chain and none of the chain
			 *	had top->selfpc == selfpc.
			 *	so we allocate a new tostruct
			 *	and link it to the head of the chain.
			 */
			toindex = ++tos[0].link;
			if (toindex >= tolimit) {
				goto overflow;
			}
			top = &tos[toindex];
			top->selfpc = selfpc;
			top->count = 1;
			top->link = *frompcindex;
			*frompcindex = toindex;
			goto done;
		}
		/*
		 *	otherwise, check the next arc on the chain.
		 */
		prevtop = top;
		top = &tos[top->link];
		if (top->selfpc == selfpc) {
			/*
			 *	there it is.
			 *	increment its count
			 *	move it to the head of the chain.
			 */
			top->count++;
			toindex = prevtop->link;
			prevtop->link = top->link;
			top->link = *frompcindex;
			*frompcindex = toindex;
			goto done;
		}

	}
done:
#ifdef	ibmrt
	profiling--;
#endif	ibmrt	
	spl_x(s);
	/* and fall through */
out:

#ifdef	vax
	asm("	rsb");
#endif	vax

#if	defined(ibmrt) || defined(ns32000) || defined(sun) || defined(i386)
	return;
#endif	defined(ibmrt) || defined(ns32000) || defined(sun) || defined(i386)

overflow:
	profiling = 3;
	printf("mcount: tos overflow\n");
	spl_x(s);
	goto out;
}
#if	defined(vax) || defined(balance) || defined(sun)
asm(".text");
asm("#the end of mcount()");
asm(".data");
#endif	defined(vax) || defined(balance) || defined(sun)
#endif	defined(vax) || defined(ibmrt) || defined(ns32000) || defined(sun) || defined(i386)
#endif	!defined(mips)
#ifdef	mips

#if	PROFTYPE != 1 && PROFTYPE != 2 && PROFTYPE != 3 && PROFTYPE != 4
#include "error: PROFTYPE incorrectly defined"
#endif

#include <sys/time.h>
#include <sys/kernel.h>

int profiling = 3;

unsigned int	*kcount;
char *s_lowpc;
u_long	s_textsize = 0;
struct phdr phdr;

extern char eprol[], etext[];

kmstartup()
{
	if (phdr.pc_buf == 0) {
		printf("No space for monitor buffer(s)\n");
		s_textsize = 0;
		return;
	}
	printf("pc_buf is at %x\n", phdr.pc_buf);
	bzero((caddr_t)phdr.pc_buf, phdr.pc_bytes);

	phdr.proftype = PC_SAMPLES;
	phdr.sample_hz = phz ? phz : hz;
	kcount = (unsigned int *)phdr.pc_buf;

#if	PROFTYPE == 1
	printf("Profiling type 1 (PC samples only)\n");
#endif	PROFTYPE == 1

#if	PROFTYPE == 2 || PROFTYPE == 3
	mipsprof_startup();
#endif	PROFTYPE == 2 || PROFTYPE == 3

#if	PROFTYPE == 4
	gprof_startup();
#endif	PROFTYPE == 4
}

#if	PROFTYPE == 2 || PROFTYPE == 3

/*
 * "_mcount" adds (return_address >> 1) to this to find the corresponding
 * counter within the array of counters. Don't set this nonzero till after
 * we've allocated storage for the counters, since it also prevents _mcount
 * from being called from within sbrk before we're ready.
 */
char * _mcountoff;

mipsprof_startup()
{
	if (phdr.bb_buf == 0) {
		printf("No space for bb counts\n");
		return;
	}
	printf("bb_buf is at %x\n", phdr.bb_buf);
	bzero((caddr_t)phdr.bb_buf, phdr.bb_bytes);

#if	PROFTYPE == 2
	printf("Profiling type 2 (Invocation counts)\n");
	phdr.proftype |= INV_COUNTS;
#else	PROFTYPE == 3
	printf("Profiling type 3 (Basic Block counts)\n");
	phdr.proftype |= BB_COUNTS;
#endif	PROFTYPE

	_mcountoff = 0;
	printf("bb_buf is at %x bb_buf[0] = %x\n", phdr.bb_buf, phdr.bb_buf[0]);
	_mcountoff = phdr.bb_buf/* - (((unsigned) phdr.lowpc) >> 1)*/; 
}
#endif	PROFTYPE == 2 || PROFTYPE == 3

#if	PROFTYPE == 4
/*
 * GPROF profiling initialization
 *
 * Froms is actually a bunch of unsigned shorts indexing tos
 */
u_short *froms;
struct tostruct *tos = 0;
long tolimit = 0;

gprof_startup(php)
struct phdr *php;
{
	u_long	fromssize, tossize;

	phdr.froms_bytes = s_textsize / HASHFRACTION;
	froms = (u_short *)(phdr.froms_buf = (char *)calloc(phdr.froms_bytes));
	if (froms == 0) {
		printf("No space for froms buffer\n");
		s_textsize = 0;
		return;
	}
	bzero((caddr_t)phdr.froms_buf, phdr.froms_bytes);
	tolimit = s_textsize * ARCDENSITY / 100;
	if (tolimit < MINARCS) {
		tolimit = MINARCS;
	} else if (tolimit > 65534) {
		tolimit = 65534;
	}
	phdr.tos_bytes = tolimit * sizeof(struct tostruct);
	tos = (struct tostruct *)(phdr.tos_buf=(char *)calloc(phdr.tos_bytes));
	if (tos == 0) {
		printf("No space for tos buffer(s)\n");
		cfreemem(froms, phdr.froms_bytes);
		s_textsize = 0;
		return;
	}
	bzero((caddr_t)phdr.tos_buf, phdr.tos_bytes);
	tos[0].link = 0;
	phdr.proftype |= GPROF_COUNTS;
	printf("Profiling type 4 (GPROF)\n");
	return;
}
#endif	PROFTYPE == 4

#endif	mips
#endif	GPROF
