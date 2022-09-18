h46206
s 00002/00002/00157
d D 8.1 93/06/11 15:54:24 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00012/00146
d D 7.5 92/10/11 10:20:11 bostic 9 8
c make kernel includes standard
e
s 00032/00065/00126
d D 7.4 92/05/20 16:54:31 bostic 8 7
c Really set the CR0_EM bit as the comments suggested (from 386bsd).
c Delete npxload and npxunload, which are not used.  Change npxintr to deliver
c a floating point exception vi psignal, rather than a recursive call to trap.
c This is important since we may have context switched away from the current
c owner of the npx.  A recent set of changes in locore.s and isu.s guarantee
c that this signal will be delivered before executing any more user code in
c the affected process, even if it is the current process.  Also rearranged
c npxdna a little and removed dead code; from Pace Willisson (pace@blitz.com)
e
s 00015/00005/00176
d D 7.3 91/11/16 14:05:01 william 7 6
c fixes for fp context switching
e
s 00030/00028/00151
d D 7.2 91/05/12 17:48:23 william 6 5
c handle npxdna's correctly, call trap on exceptions, prepare for lazy
c context switch (now that we have curpcb)
e
s 00010/00004/00169
d D 7.1 91/05/09 23:32:53 bostic 5 4
c new copyright; att/bsd/shared
e
s 00049/00020/00124
d D 1.4 91/05/09 20:35:55 william 4 3
c interim version, changes for net2 tape
e
s 00000/00000/00144
d D 1.3 91/01/08 19:14:45 william 3 2
c reno changes
e
s 00037/00027/00107
d D 1.2 90/11/18 11:32:05 bill 2 1
c auto conf, bus control, conventions, interrupt control, per host config
e
s 00134/00000/00000
d D 1.1 90/11/08 20:01:31 bill 1 0
c date and time created 90/11/08 20:01:31 by bill
e
u
U
t
T
I 1
D 5
/*
D 2
 * 387 and 287 Numeric Coprocessor Extension (NPX) Driver.
E 2
I 2
 * Copyright (c) 1990 W. Jolitz
E 2
 * %W% (Berkeley) %G%
E 5
I 5
/*-
 * Copyright (c) 1990 William Jolitz.
D 10
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
E 5
 */
I 5
D 6

E 6
E 5
I 2
#include "npx.h"
D 5
#if	NNPX > 0
E 5
I 5
#if NNPX > 0
E 5
E 2

I 2
D 9
#include "param.h"
#include "systm.h"
#include "conf.h"
#include "file.h"
D 4
#include "dir.h"
#include "user.h"
#include "ioctl.h"
#include "vm.h"
E 4
I 4
#include "proc.h"
I 6
#include "machine/cpu.h"
E 6
D 7
#include "machine/pcb.h"
E 7
I 7
#include "user.h"
E 7
E 4
D 6
#include "machine/pte.h"
E 6
I 6
#include "machine/trap.h"
E 6
D 4
#include "machine/isa/isa_device.h"
E 4
I 4
#include "ioctl.h"
#include "machine/specialreg.h"
#include "i386/isa/isa_device.h"
E 4
#include "icu.h"
E 9
I 9
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/conf.h>
#include <sys/file.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/ioctl.h>

#include <machine/cpu.h>
#include <machine/trap.h>
#include <machine/specialreg.h>
#include <i386/isa/isa_device.h>
#include <i386/isa/icu.h>
E 9
/*
 * 387 and 287 Numeric Coprocessor Extension (NPX) Driver.
 */

E 2
int	npxprobe(), npxattach(), npxintr();
D 2
struct	driver npxdriver = {
E 2
I 2
struct	isa_driver npxdriver = {
E 2
	npxprobe, npxattach, "npx",
};

D 4
struct proc	*npxproc;	/* process who owns device, otherwise zero */
E 4
I 4
D 6
static struct proc *npxproc;	/* process who owns device, otherwise zero */
E 4
D 2
struct user	*npxutl;	/* owners user structure */
struct pte	*Npxmap;	/* kernel ptes mapping owner's user structure */
E 2
I 2
extern struct user npxutl;	/* owners user structure */
extern struct pte Npxmap[];	/* kernel ptes mapping owner's user structure */
E 6
I 6
struct proc *npxproc;	/* process who owns device, otherwise zero */
struct pcb *npxpcb;	/* owners context structure */
E 6
I 4
static npxexists;
extern long npx0mask;
E 4
E 2

/*
 * Probe routine - look device, otherwise set emulator bit
 */
npxprobe(dvp)
D 2
	struct device *dvp;
{
	register status;
E 2
I 2
	struct isa_device *dvp;
{	static status, control;
E 2

#ifdef lint
	npxintr();
#endif
D 2
/* insure EM bit off */
	asm("	fninit");	/* put device in known state */
E 2

I 2
	/* insure EM bit off */
I 8
	load_cr0(rcr0() & ~CR0_EM);

E 8
	asm("	fninit ");	/* put device in known state */

E 2
	/* check for a proper status of zero */
	status = 0xa5a5;	
D 2
	asm("	movw	%1,%%ax ; fnstsw %%ax ;  movw %%ax, %0"
		: "=g" (status) : "g" (status) : "ax");
E 2
I 2
	asm ("	fnstsw	%0 " : "=m" (status) : "m" (status) );
E 2

	if (status == 0) {
D 2
		register control;
E 2

		/* good, now check for a proper control word */
		control = 0xa5a5;	
D 2
		asm("	movw	%1,%%ax ; fnstcw %%ax ;  movw %%ax, %0"
			: "=g" (control) : "g" (control) : "ax");
E 2
I 2
		asm ("	fnstcw %0 " : "=m" (control) : "m" (control));
E 2

D 2
		if (control&0x103f == 0x3f) {
E 2
I 2
		if ((control&0x103f) == 0x3f) {
E 2
			/* then we have a numeric coprocessor */
		/* XXX should force an exception here to generate an intr */
			return (1);
		}
	}

D 8
/* insure EM bit on */
E 8
I 8
	/* insure EM bit on */
	load_cr0(rcr0() | CR0_EM);
E 8
	return (0);
}

/*
 * Attach routine - announce which it is, and wire into system
 */
npxattach(dvp)
D 2
	struct device *dvp;
E 2
I 2
	struct isa_device *dvp;
E 2
{
D 2
	int unit = dvp->unit;
E 2

D 2
	npxinit();
E 2
I 2
	npxinit(0x262);
E 2
	/* check for ET bit to decide 387/287 */
D 2
	INTREN(IRQ13);
E 2
D 8
	/*outb(0xb1,0);		/* reset processor */
E 8
I 4
	npxexists++;
	npx0mask = dvp->id_irq;
E 4
}

/*
 * Initialize floating point unit, usually after an error
 */
D 2
npxinit() {
	register control;
E 2
I 2
npxinit(control) {
E 2

D 4
	asm ("	fninit");
E 4
I 4
	if (npxexists == 0) return;

D 8

E 8
	load_cr0(rcr0() & ~CR0_EM);	/* stop emulating */
#ifdef INTEL_COMPAT
	asm ("	finit");
E 4
D 2
	control = XXX;
	asm("	movw	%0,%%ax ; fldcw %%ax "
			: "g" (control) : "ax");
E 2
I 2
	asm("	fldcw %0" : : "g" (control));
I 4
D 6
	asm("	fnsave %0 " : : "g"
		(((struct pcb *)curproc->p_addr)->pcb_savefpu) );
E 6
I 6
	asm("	fnsave %0 " : : "g" (curpcb->pcb_savefpu) );
E 6
#else
	asm("fninit");
D 6
	asm("fnsave %0" : : "g"
		(((struct pcb *)curproc->p_addr)->pcb_savefpu) );
E 6
I 6
	asm("	fnsave %0 " : : "g" (curpcb->pcb_savefpu) );
E 6
#endif
	load_cr0(rcr0() | CR0_EM);	/* start emulating */
E 4
E 2

}

I 4
D 6
#ifdef notyet
E 6
E 4
/*
D 8
 * Load floating point context and record ownership to suite
 */
npxload() {

	if (npxproc) panic ("npxload");
D 4
	npxproc = u.u_procp;
E 4
I 4
	npxproc = curproc;
E 4
D 6
	uaccess(npxproc, Npxmap, &npxutl);
D 2
	asm("	frstor %0 " : "g" (u.u_pcb.pcb_savefpu) );
E 2
I 2
D 4
	asm("	frstor %0 " : : "g" (u.u_pcb.pcb_savefpu) );
E 4
I 4
	asm("	frstor %0 " : : "g"
		(((struct pcb *)curproc->p_addr)->pcb_savefpu) );
E 6
I 6
	npxpcb = curpcb;
	asm("	frstor %0 " : : "g" (curpcb->pcb_savefpu) );
E 6
E 4
E 2
}

/*
 * Unload floating point context and relinquish ownership
 */
npxunload() {

	if (npxproc == 0) panic ("npxunload");
D 2
	asm("	fsave %0 " : "g" (npxutl.u_pcb.pcb_savefpu) );
E 2
I 2
D 6
	asm("	fsave %0 " : : "g" (npxutl.u_pcb.pcb_savefpu) );
E 6
I 6
	asm("	fsave %0 " : : "g" (npxpcb->pcb_savefpu) );
E 6
E 2
	npxproc = 0 ;
}

I 4
D 6
#endif
E 6
E 4
/*
E 8
 * Record information needed in processing an exception and clear status word
 */
D 4
npxexcept() {
E 4
I 4
D 6
npxintr() {
E 6
I 6
D 8
npxintr(frame) struct intrframe frame; {
	struct trapframe tf;
E 8
I 8
npxintr(frame)
	struct intrframe frame;
{
	if (npxexists == 0) {
		printf ("stray npxintr\n");
		return;
	}
E 8
E 6
E 4

I 4
D 8
	outb(0xf0,0);		/* reset processor */
E 8
I 8
	outb(0xf0,0);		/* reset coprocessor */
E 8

E 4
D 6
	/* save state in appropriate user structure */
E 6
I 6
D 8
	/* sync state in process context structure, in advance of debugger/process looking for it */
E 6
D 4
	if (npxproc == 0) panic ("npxexcept");
D 2
	asm ("	fsave %0 " : "g" (npxutl.u_pcb.pcb_savefpu) );
E 2
I 2
	asm ("	fsave %0 " : : "g" (npxutl.u_pcb.pcb_savefpu) );
E 4
I 4
	if (npxproc == 0 || npxexists == 0) panic ("npxintr");
I 6
D 7
	asm ("	fnsave %0 " : : "g" (npxpcb->pcb_savefpu) );
E 7
I 7
	asm ("	fnsave %0 " : : "g" (npxproc->p_addr->u_pcb.pcb_savefpu) );
E 7

E 8
	/*
D 8
	 * Prepair a trap frame for our generic exception processing routine, trap()
E 8
I 8
	 * npxproc may be NULL, if this is a delayed interrupt from
	 * a process that just exited.
E 8
	 */
D 8
	bcopy(&frame.if_es, &tf, sizeof(tf));
	tf.tf_trapno = T_ARITHTRAP;
E 6
#ifdef notyet
D 6
	asm ("	fnsave %0 " : : "g" (npxutl.u_pcb.pcb_savefpu) );
E 6
I 6
	/* encode the appropriate code for detailed information on this exception */
	tf.tf_err = ???;
E 6
#endif
I 6
	trap(tf);
E 8
I 8
	if (npxproc) {
		/*
		 * sync state in process context structure, in advance 
		 * of debugger/process looking for it.
		 */
		asm("fnsave %0" :: "g" (npxproc->p_addr->u_pcb.pcb_savefpu));
		psignal(npxproc, SIGFPE);
E 8
E 6
E 4
E 2

D 8
	/*
D 6
	 * encode the appropriate u_code for detailed information
         * on this exception
E 6
I 6
	 * Restore with any changes to superior frame
E 6
	 */
I 6
	bcopy(&tf, &frame.if_es, sizeof(tf));
E 6

D 6
	/* signal appropriate process */
	psignal (npxproc, SIGFPE);

E 6
	/* clear the exception so we can catch others like it */
	asm ("	fnclex");
E 8
I 8
		/* clear the exception so we can catch others like it */
		asm ("	fnclex");
	}
E 8
}

/*
D 4
 * Catch AT/386 interrupt used to signal exception, and simulate trap()
 */
npxintr() {
	outb(0xf0,0);
	pg("npxintr");
}

/*
E 4
 * Implement device not available (DNA) exception
 */
D 8
npxdna() {
E 8
I 8
npxdna()
{
	if (npxexists == 0)
		return(0);
E 8
I 4

D 8
	if (npxexists == 0) return(0);
I 7
	if (npxproc == curproc)
		load_cr0(rcr0() & ~CR0_EM);	/* stop emulating */
	else {
		load_cr0(rcr0() & ~CR0_EM);	/* stop emulating */
E 8
I 8
	load_cr0(rcr0() & ~CR0_EM);	/* stop emulating */
	if (npxproc != curproc) {
E 8
		if (npxproc)
D 8
			asm(" fnsave %0 "::"g" (npxproc->p_addr->u_pcb.pcb_savefpu));
E 8
I 8
			asm(" fnsave %0 "::"g"
			    (npxproc->p_addr->u_pcb.pcb_savefpu));
E 8
		asm("	frstor %0 " : : "g" (curpcb->pcb_savefpu));
		npxproc = curproc;
	}
D 8
#ifdef garbage
E 7
D 6
	if (!(((struct pcb *) curproc->p_addr)->pcb_flags & FP_WASUSED)
	    ||(((struct pcb *) curproc->p_addr)->pcb_flags & FP_NEEDSRESTORE)) {
E 6
I 6
	if (!(curpcb->pcb_flags & FP_WASUSED)
	    ||(curpcb->pcb_flags & FP_NEEDSRESTORE)) {
E 6
		load_cr0(rcr0() & ~CR0_EM);	/* stop emulating */
D 6
		asm("	frstor %0 " : : "g" (((struct pcb *) curproc->p_addr)->pcb_savefpu) );
		((struct pcb *) curproc->p_addr)->pcb_flags |= FP_WASUSED | FP_NEEDSSAVE;
		((struct pcb *) curproc->p_addr)->pcb_flags &= ~FP_NEEDSRESTORE;
E 6
I 6
		asm("	frstor %0 " : : "g" (curpcb->pcb_savefpu));
		curpcb->pcb_flags |= FP_WASUSED | FP_NEEDSSAVE;
		curpcb->pcb_flags &= ~FP_NEEDSRESTORE;
E 6
		npxproc = curproc;
I 6
		npxpcb = curpcb;
E 6
D 7
		
		return(1);
E 7
	}
D 7
	return (0);
E 7
I 7
	load_cr0(rcr0() & ~CR0_EM);	/* stop emulating */
#endif
E 8
	return (1);
E 7
E 4
}
I 2
#endif
E 2
E 1
