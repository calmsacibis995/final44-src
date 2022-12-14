h20844
s 00005/00000/01207
d D 8.4 95/05/09 12:11:04 mckusick 16 15
c put in request to unmount all filesystems when rebooting
e
s 00001/00001/01206
d D 8.3 94/01/12 14:29:18 hibler 15 14
c entries_pageable set TRUE for buffer map (set vm_map.c change).
e
s 00016/00001/01191
d D 8.2 93/12/06 20:22:39 akito 14 13
c 
e
s 00002/00002/01190
d D 8.1 93/06/10 22:26:26 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00003/01191
d D 7.12 93/06/02 09:59:39 akito 12 11
c fix stack frame format checking
e
s 00038/00002/01156
d D 7.11 93/05/25 13:13:13 akito 11 10
c added cpu_sysctl support for console
e
s 00017/00001/01141
d D 7.10 93/05/12 04:11:45 akito 10 9
c LUNA-II (68040 based LUNA) support
e
s 00003/00000/01139
d D 7.9 93/05/02 05:39:20 akito 9 8
c comment off kstackatbase related statment
e
s 00019/00006/01120
d D 7.8 93/03/10 15:41:29 akito 8 7
c sync up to hp300/hp300/machdep.c   7.36
e
s 00000/00001/01126
d D 7.7 93/02/02 10:53:16 akito 7 6
c remove #include <hp300/hp300/isr.h>
e
s 00043/00019/01084
d D 7.6 93/01/02 13:47:32 akito 6 5
c sync up to hp300/hp300/machdep.c        7.35
e
s 00006/00005/01097
d D 7.5 92/12/10 13:55:09 akito 5 4
c sync up from hp300/hp300/machdep.c 7.33
e
s 00026/00026/01076
d D 7.4 92/10/11 11:07:50 bostic 4 3
c make kernel includes standard
e
s 00006/00017/01096
d D 7.3 92/07/23 16:01:32 fujita 3 2
c update for 4.4BSD-alpha distribution
e
s 00002/00000/01111
d D 7.2 92/06/16 05:15:53 fujita 2 1
c support reboot
e
s 01111/00000/00000
d D 7.1 92/06/15 06:38:41 fujita 1 0
c date and time created 92/06/15 06:38:41 by fujita
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1992 OMRON Corporation.
D 13
 * Copyright (c) 1982, 1986, 1990, 1992 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1982, 1986, 1990, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: machdep.c 1.63 91/04/24$
D 6
 * OMRON: $Id: machdep.c,v 1.3 92/06/14 06:17:12 moti Exp $
E 6
I 6
D 8
 * from: hp300/hp300/machdep.c	7.35 (Berkeley) 12/28/92
E 8
I 8
D 11
 * from: hp300/hp300/machdep.c   7.36 (Berkeley) 2/10/93
E 11
I 11
D 14
 * from: hp300/hp300/machdep.c   7.37 (Berkeley) 5/20/93
E 14
I 14
 * from: hp300/hp300/machdep.c	8.3 (Berkeley) 11/14/93
E 14
E 11
E 8
E 6
 *
D 3
 * from: hp300/hp300/machdep.c	7.28 (Berkeley) 6/5/92
E 3
I 3
D 5
 * from: hp300/hp300/machdep.c  7.29 (Berkeley) 7/8/92
E 5
I 5
D 6
 * from: hp300/hp300/machdep.c  7.33 (Berkeley) 10/11/92
E 5
E 3
 *
E 6
 *	%W% (Berkeley) %G%
 */

D 4
#include "param.h"
#include "systm.h"
#include "signalvar.h"
#include "kernel.h"
#include "map.h"
#include "proc.h"
#include "buf.h"
#include "reboot.h"
#include "conf.h"
#include "file.h"
#include "clist.h"
#include "callout.h"
#include "malloc.h"
#include "mbuf.h"
#include "msgbuf.h"
#include "mount.h"
#include "user.h"
#include "exec.h"
E 4
I 4
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/signalvar.h>
#include <sys/kernel.h>
#include <sys/map.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/reboot.h>
#include <sys/conf.h>
#include <sys/file.h>
#include <sys/clist.h>
#include <sys/callout.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/msgbuf.h>
I 11
#include <sys/ioctl.h>
#include <sys/tty.h>
E 11
#include <sys/mount.h>
#include <sys/user.h>
#include <sys/exec.h>
I 11
#include <sys/sysctl.h>
E 11
E 4
#ifdef SYSVSHM
D 4
#include "shm.h"
E 4
I 4
#include <sys/shm.h>
E 4
#endif

D 4
#include "../include/cpu.h"
#include "../include/reg.h"
#include "../include/psl.h"
#include "isr.h"
#include "pte.h"
#include "net/netisr.h"
E 4
I 4
#include <machine/cpu.h>
#include <machine/reg.h>
#include <machine/psl.h>
I 11
#include <luna68k/luna68k/cons.h>
E 11
D 7
#include <hp300/hp300/isr.h>
E 7
#include <luna68k/luna68k/pte.h>
#include <net/netisr.h>
E 4

#define	MAXMEM	64*1024*CLSIZE	/* XXX - from cmap.h */
D 4
#include "vm/vm_kern.h"
E 4
I 4
#include <vm/vm_kern.h>
E 4

I 8
/* the following is used externally (sysctl_hw) */
char machine[] = "luna68k";		/* cpu "architecture" */

E 8
vm_map_t buffer_map;
extern vm_offset_t avail_end;

/*
 * Declare these as initialized data so we can patch them.
 */
int	nswbuf = 0;
#ifdef	NBUF
int	nbuf = NBUF;
#else
int	nbuf = 0;
#endif
#ifdef	BUFPAGES
int	bufpages = BUFPAGES;
#else
int	bufpages = 0;
#endif
int	msgbufmapped;		/* set when safe to use msgbuf */
int	maxmem;			/* max memory per process */
int	physmem = MAXMEM;	/* max supported memory, changes to actual */
/*
 * safepri is a safe priority for sleep to set for a spin-wait
 * during autoconfiguration or after a panic.
 */
int	safepri = PSL_LOWIPL;

extern	u_int lowram;
I 6
extern	short exframesize[];
E 6

#ifdef FPCOPROC
int	fpptype = -1;
#endif

/*
 * Console initialization: called early on from main,
 * before vm init or startup.  Do enough configuration
 * to choose and initialize a console.
 */
consinit()
{

	/*
	 * Set cpuspeed immediately since cninit() called routines
	 * might use delay.
	 */

	cpuspeed = MHZ_25;

	/*
         * Find what hardware is attached to this machine.
         */
	find_devs();

	/*
	 * Initialize the console before we print anything out.
	 */
	cninit();
}

/*
 * cpu_startup: allocate memory for variable-sized tables,
 * initialize cpu, and do autoconfiguration.
 */
cpu_startup()
{
	register unsigned i;
	register caddr_t v, firstaddr;
	int base, residual;
	vm_offset_t minaddr, maxaddr;
	vm_size_t size;
#ifdef DEBUG
	extern int pmapdebug;
	int opmapdebug = pmapdebug;

	pmapdebug = 0;
#endif
	/*
	 * Initialize error message buffer (at end of core).
	 */
	for (i = 0; i < btoc(sizeof (struct msgbuf)); i++)
		pmap_enter(kernel_pmap, (vm_offset_t)msgbufp,
		    avail_end + i * NBPG, VM_PROT_ALL, TRUE);
	msgbufmapped = 1;

	/*
	 * Good {morning,afternoon,evening,night}.
	 */
	printf(version);
	identifyfpu();
	printf("real mem = %d\n", ctob(physmem));

	/*
	 * Allocate space for system data structures.
	 * The first available real memory address is in "firstaddr".
	 * The first available kernel virtual address is in "v".
	 * As pages of kernel virtual memory are allocated, "v" is incremented.
	 * As pages of memory are allocated and cleared,
	 * "firstaddr" is incremented.
	 * An index into the kernel page table corresponding to the
	 * virtual memory address maintained in "v" is kept in "mapaddr".
	 */
	/*
	 * Make two passes.  The first pass calculates how much memory is
	 * needed and allocates it.  The second pass assigns virtual
	 * addresses to the various data structures.
	 */
	firstaddr = 0;
again:
	v = (caddr_t)firstaddr;

#define	valloc(name, type, num) \
	    (name) = (type *)v; v = (caddr_t)((name)+(num))
#define	valloclim(name, type, num, lim) \
	    (name) = (type *)v; v = (caddr_t)((lim) = ((name)+(num)))
	valloc(cfree, struct cblock, nclist);
	valloc(callout, struct callout, ncallout);
	valloc(swapmap, struct map, nswapmap = maxproc * 2);
#ifdef SYSVSHM
	valloc(shmsegs, struct shmid_ds, shminfo.shmmni);
#endif
	
	/*
	 * Determine how many buffers to allocate.
	 * Since HPs tend to be long on memory and short on disk speed,
	 * we allocate more buffer space than the BSD standard of
	 * use 10% of memory for the first 2 Meg, 5% of remaining.
	 * We just allocate a flat 10%.  Insure a minimum of 16 buffers.
	 * We allocate 1/2 as many swap buffer headers as file i/o buffers.
	 */
	if (bufpages == 0)
		bufpages = physmem / 10 / CLSIZE;
	if (nbuf == 0) {
		nbuf = bufpages;
		if (nbuf < 16)
			nbuf = 16;
	}
	if (nswbuf == 0) {
		nswbuf = (nbuf / 2) &~ 1;	/* force even */
		if (nswbuf > 256)
			nswbuf = 256;		/* sanity */
	}
	valloc(swbuf, struct buf, nswbuf);
	valloc(buf, struct buf, nbuf);
	/*
	 * End of first pass, size has been calculated so allocate memory
	 */
	if (firstaddr == 0) {
		size = (vm_size_t)(v - firstaddr);
		firstaddr = (caddr_t) kmem_alloc(kernel_map, round_page(size));
		if (firstaddr == 0)
			panic("startup: no room for tables");
		goto again;
	}
	/*
	 * End of second pass, addresses have been assigned
	 */
	if ((vm_size_t)(v - firstaddr) != size)
		panic("startup: table size inconsistency");
	/*
	 * Now allocate buffers proper.  They are different than the above
	 * in that they usually occupy more virtual memory than physical.
	 */
	size = MAXBSIZE * nbuf;
	buffer_map = kmem_suballoc(kernel_map, (vm_offset_t *)&buffers,
D 15
				   &maxaddr, size, FALSE);
E 15
I 15
				   &maxaddr, size, TRUE);
E 15
	minaddr = (vm_offset_t)buffers;
	if (vm_map_find(buffer_map, vm_object_allocate(size), (vm_offset_t)0,
			&minaddr, size, FALSE) != KERN_SUCCESS)
		panic("startup: cannot allocate buffers");
	base = bufpages / nbuf;
	residual = bufpages % nbuf;
	for (i = 0; i < nbuf; i++) {
		vm_size_t curbufsize;
		vm_offset_t curbuf;

		/*
		 * First <residual> buffers get (base+1) physical pages
		 * allocated for them.  The rest get (base) physical pages.
		 *
		 * The rest of each buffer occupies virtual space,
		 * but has no physical memory allocated for it.
		 */
		curbuf = (vm_offset_t)buffers + i * MAXBSIZE;
		curbufsize = CLBYTES * (i < residual ? base+1 : base);
		vm_map_pageable(buffer_map, curbuf, curbuf+curbufsize, FALSE);
		vm_map_simplify(buffer_map, curbuf);
	}
	/*
	 * Allocate a submap for exec arguments.  This map effectively
	 * limits the number of processes exec'ing at any time.
	 */
	exec_map = kmem_suballoc(kernel_map, &minaddr, &maxaddr,
				 16*NCARGS, TRUE);
	/*
	 * Allocate a submap for physio
	 */
	phys_map = kmem_suballoc(kernel_map, &minaddr, &maxaddr,
				 VM_PHYS_SIZE, TRUE);

	/*
	 * Finally, allocate mbuf pool.  Since mclrefcnt is an off-size
	 * we use the more space efficient malloc in place of kmem_alloc.
	 */
	mclrefcnt = (char *)malloc(NMBCLUSTERS+CLBYTES/MCLBYTES,
				   M_MBUF, M_NOWAIT);
	bzero(mclrefcnt, NMBCLUSTERS+CLBYTES/MCLBYTES);
	mb_map = kmem_suballoc(kernel_map, (vm_offset_t *)&mbutl, &maxaddr,
			       VM_MBUF_SIZE, FALSE);
	/*
	 * Initialize callouts
	 */
	callfree = callout;
	for (i = 1; i < ncallout; i++)
		callout[i-1].c_next = &callout[i];
	callout[i-1].c_next = NULL;

#ifdef DEBUG
	pmapdebug = opmapdebug;
#endif
	printf("avail mem = %d\n", ptoa(cnt.v_free_count));
	printf("using %d buffers containing %d bytes of memory\n",
		nbuf, bufpages * CLBYTES);
	/*
	 * Set up CPU-specific registers, cache, etc.
	 */
	initcpu();

	/*
	 * Set up buffers, so they can be used to read disk labels.
	 */
	bufinit();

	/*
	 * Configure the system.
	 */
	configure();
}

/*
 * Set registers on exec.
 * XXX Should clear registers except sp, pc,
 * but would break init; should be fixed soon.
 */
setregs(p, entry, retval)
	register struct proc *p;
	u_long entry;
	int retval[2];
{
D 6
	p->p_md.md_regs[PC] = entry & ~1;
E 6
I 6
	struct frame *frame = (struct frame *)p->p_md.md_regs;

	frame->f_pc = entry & ~1;
E 6
#ifdef FPCOPROC
	/* restore a null state frame */
	p->p_addr->u_pcb.pcb_fpregs.fpf_null = 0;
	m68881_restore(&p->p_addr->u_pcb.pcb_fpregs);
#endif
}

I 11
/*
 * Info for CTL_HW
 */
E 11
I 8
extern	char machine[];
char	cpu_model[120];
extern	char ostype[], osrelease[], version[];

E 8
identifyfpu()
{
I 10
#ifdef LUNA2
	if (machineid == LUNA_II) {
		sprintf(cpu_model, "LUNA-II (25MHz MC68040 CPU+MMU+FPU)");
		printf("%s\n", cpu_model);
		return;
	}
#endif
E 10
D 8
    if ( fpptype == -1 ) {
	printf("unknow FPU type \n");
	panic("startup");
    }
    printf("LUNA(20Mhz MC68030 CPU, 20Mhz MC6888%d FPU)\n",fpptype);
E 8
I 8
	if ( fpptype == -1 ) {
		printf("unknow FPU type \n");
		panic("startup");
	}
D 10

E 10
	sprintf(cpu_model, "LUNA-I (20MHz MC68030 CPU+MMU, 20MHz MC6888%d FPU)", fpptype);
	printf("%s\n", cpu_model);

/*
	printf("LUNA(20Mhz MC68030 CPU, 20Mhz MC6888%d FPU)\n",fpptype);
 */
E 8
}

#define SS_RTEFRAME	1
#define SS_FPSTATE	2
#define SS_USERREGS	4

struct sigstate {
	int	ss_flags;		/* which of the following are valid */
	struct	frame ss_frame;		/* original exception frame */
	struct	fpframe ss_fpstate;	/* 68881/68882 state info */
};

/*
 * WARNING: code in locore.s assumes the layout shown for sf_signum
 * thru sf_handler so... don't screw with them!
 */
struct sigframe {
	int	sf_signum;		/* signo for handler */
	int	sf_code;		/* additional info for handler */
	struct	sigcontext *sf_scp;	/* context ptr for handler */
	sig_t	sf_handler;		/* handler addr for u_sigc */
	struct	sigstate sf_state;	/* state of the hardware */
	struct	sigcontext sf_sc;	/* actual context */
};

#ifdef DEBUG
int sigdebug = 0;
int sigpid = 0;
#define SDB_FOLLOW	0x01
#define SDB_KSTACK	0x02
#define SDB_FPSTATE	0x04
#endif

/*
 * Send an interrupt to process.
 */
void
sendsig(catcher, sig, mask, code)
	sig_t catcher;
	int sig, mask;
	unsigned code;
{
	register struct proc *p = curproc;
	register struct sigframe *fp, *kfp;
	register struct frame *frame;
	register struct sigacts *psp = p->p_sigacts;
	register short ft;
	int oonstack, fsize;
D 6
	extern short exframesize[];
E 6
	extern char sigcode[], esigcode[];

	frame = (struct frame *)p->p_md.md_regs;
	ft = frame->f_format;
	oonstack = psp->ps_sigstk.ss_flags & SA_ONSTACK;
	/*
	 * Allocate and validate space for the signal handler
	 * context. Note that if the stack is in P0 space, the
	 * call to grow() is a nop, and the useracc() check
	 * will fail if the process has not already allocated
	 * the space with a `brk'.
	 */
	fsize = sizeof(struct sigframe);
	if ((psp->ps_flags & SAS_ALTSTACK) &&
	    (psp->ps_sigstk.ss_flags & SA_ONSTACK) == 0 &&
	    (psp->ps_sigonstack & sigmask(sig))) {
		fp = (struct sigframe *)(psp->ps_sigstk.ss_base +
					 psp->ps_sigstk.ss_size - fsize);
		psp->ps_sigstk.ss_flags |= SA_ONSTACK;
	} else
		fp = (struct sigframe *)(frame->f_regs[SP] - fsize);
	if ((unsigned)fp <= USRSTACK - ctob(p->p_vmspace->vm_ssize)) 
		(void)grow(p, (unsigned)fp);
#ifdef DEBUG
	if ((sigdebug & SDB_KSTACK) && p->p_pid == sigpid)
		printf("sendsig(%d): sig %d ssp %x usp %x scp %x ft %d\n",
		       p->p_pid, sig, &oonstack, fp, &fp->sf_sc, ft);
#endif
	if (useracc((caddr_t)fp, fsize, B_WRITE) == 0) {
#ifdef DEBUG
		if ((sigdebug & SDB_KSTACK) && p->p_pid == sigpid)
			printf("sendsig(%d): useracc failed on sig %d\n",
			       p->p_pid, sig);
#endif
		/*
		 * Process has trashed its stack; give it an illegal
		 * instruction to halt it in its tracks.
		 */
		SIGACTION(p, SIGILL) = SIG_DFL;
		sig = sigmask(SIGILL);
		p->p_sigignore &= ~sig;
		p->p_sigcatch &= ~sig;
		p->p_sigmask &= ~sig;
		psignal(p, SIGILL);
		return;
	}
	kfp = (struct sigframe *)malloc((u_long)fsize, M_TEMP, M_WAITOK);
	/* 
	 * Build the argument list for the signal handler.
	 */
	kfp->sf_signum = sig;
	kfp->sf_code = code;
	kfp->sf_scp = &fp->sf_sc;
	kfp->sf_handler = catcher;
	/*
	 * Save necessary hardware state.  Currently this includes:
	 *	- general registers
	 *	- original exception frame (if not a "normal" frame)
	 *	- FP coprocessor state
	 */
	kfp->sf_state.ss_flags = SS_USERREGS;
	bcopy((caddr_t)frame->f_regs,
	      (caddr_t)kfp->sf_state.ss_frame.f_regs, sizeof frame->f_regs);
	if (ft >= FMT7) {
#ifdef DEBUG
D 11
		if (ft != FMT9 && ft != FMTA && ft != FMTB)
E 11
I 11
D 12
		if (ft != FMT9 && ft != FMTA && ft != FMTB) {
			printf("sendsig: ft = 0x%x\n", ft);
E 12
I 12
		if (ft > 15 || exframesize[ft] < 0)
E 12
E 11
			panic("sendsig: bogus frame type");
I 11
D 12
		}
E 12
E 11
#endif
		kfp->sf_state.ss_flags |= SS_RTEFRAME;
		kfp->sf_state.ss_frame.f_format = frame->f_format;
		kfp->sf_state.ss_frame.f_vector = frame->f_vector;
		bcopy((caddr_t)&frame->F_u,
		      (caddr_t)&kfp->sf_state.ss_frame.F_u, exframesize[ft]);
		/*
		 * Leave an indicator that we need to clean up the kernel
		 * stack.  We do this by setting the "pad word" above the
		 * hardware stack frame to the amount the stack must be
		 * adjusted by.
		 *
		 * N.B. we increment rather than just set f_stackadj in
		 * case we are called from syscall when processing a
		 * sigreturn.  In that case, f_stackadj may be non-zero.
		 */
		frame->f_stackadj += exframesize[ft];
		frame->f_format = frame->f_vector = 0;
#ifdef DEBUG
		if (sigdebug & SDB_FOLLOW)
			printf("sendsig(%d): copy out %d of frame %d\n",
			       p->p_pid, exframesize[ft], ft);
#endif
	}
#ifdef FPCOPROC
	kfp->sf_state.ss_flags |= SS_FPSTATE;
	m68881_save(&kfp->sf_state.ss_fpstate);
#ifdef DEBUG
	if ((sigdebug & SDB_FPSTATE) && *(char *)&kfp->sf_state.ss_fpstate)
		printf("sendsig(%d): copy out FP state (%x) to %x\n",
		       p->p_pid, *(u_int *)&kfp->sf_state.ss_fpstate,
		       &kfp->sf_state.ss_fpstate);
#endif
#endif
	/*
	 * Build the signal context to be used by sigreturn.
	 */
	kfp->sf_sc.sc_onstack = oonstack;
	kfp->sf_sc.sc_mask = mask;
	kfp->sf_sc.sc_sp = frame->f_regs[SP];
	kfp->sf_sc.sc_fp = frame->f_regs[A6];
	kfp->sf_sc.sc_ap = (int)&fp->sf_state;
	kfp->sf_sc.sc_pc = frame->f_pc;
	kfp->sf_sc.sc_ps = frame->f_sr;
	(void) copyout((caddr_t)kfp, (caddr_t)fp, fsize);
	frame->f_regs[SP] = (int)fp;
#ifdef DEBUG
	if (sigdebug & SDB_FOLLOW)
		printf("sendsig(%d): sig %d scp %x fp %x sc_sp %x sc_ap %x\n",
		       p->p_pid, sig, kfp->sf_scp, fp,
		       kfp->sf_sc.sc_sp, kfp->sf_sc.sc_ap);
#endif
	/*
	 * Signal trampoline code is at base of user stack.
	 */
	frame->f_pc = (int)PS_STRINGS - (esigcode - sigcode);
#ifdef DEBUG
	if ((sigdebug & SDB_KSTACK) && p->p_pid == sigpid)
		printf("sendsig(%d): sig %d returns\n",
		       p->p_pid, sig);
#endif
	free((caddr_t)kfp, M_TEMP);
}

/*
 * System call to cleanup state after a signal
 * has been taken.  Reset signal mask and
 * stack state from context left by sendsig (above).
 * Return to previous pc and psl as specified by
 * context left by sendsig. Check carefully to
 * make sure that the user has not modified the
 * psl to gain improper priviledges or to cause
 * a machine fault.
 */
I 5
struct sigreturn_args {
	struct sigcontext *sigcntxp;
};
E 5
/* ARGSUSED */
sigreturn(p, uap, retval)
	struct proc *p;
D 5
	struct args {
		struct sigcontext *sigcntxp;
	} *uap;
E 5
I 5
	struct sigreturn_args *uap;
E 5
	int *retval;
{
	register struct sigcontext *scp;
	register struct frame *frame;
	register int rf;
	struct sigcontext tsigc;
	struct sigstate tstate;
	int flags;
D 6
	extern short exframesize[];
E 6

	scp = uap->sigcntxp;
#ifdef DEBUG
	if (sigdebug & SDB_FOLLOW)
		printf("sigreturn: pid %d, scp %x\n", p->p_pid, scp);
#endif
	if ((int)scp & 1)
		return (EINVAL);
	/*
	 * Test and fetch the context structure.
	 * We grab it all at once for speed.
	 */
	if (useracc((caddr_t)scp, sizeof (*scp), B_WRITE) == 0 ||
	    copyin((caddr_t)scp, (caddr_t)&tsigc, sizeof tsigc))
		return (EINVAL);
	scp = &tsigc;
	if ((scp->sc_ps & (PSL_MBZ|PSL_IPL|PSL_S)) != 0)
		return (EINVAL);
	/*
	 * Restore the user supplied information
	 */
	if (scp->sc_onstack & 01)
		p->p_sigacts->ps_sigstk.ss_flags |= SA_ONSTACK;
	else
		p->p_sigacts->ps_sigstk.ss_flags &= ~SA_ONSTACK;
	p->p_sigmask = scp->sc_mask &~ sigcantmask;
	frame = (struct frame *) p->p_md.md_regs;
	frame->f_regs[SP] = scp->sc_sp;
	frame->f_regs[A6] = scp->sc_fp;
	frame->f_pc = scp->sc_pc;
	frame->f_sr = scp->sc_ps;
	/*
	 * Grab pointer to hardware state information.
	 * If zero, the user is probably doing a longjmp.
	 */
	if ((rf = scp->sc_ap) == 0)
		return (EJUSTRETURN);
	/*
	 * See if there is anything to do before we go to the
	 * expense of copying in close to 1/2K of data
	 */
	flags = fuword((caddr_t)rf);
#ifdef DEBUG
	if (sigdebug & SDB_FOLLOW)
		printf("sigreturn(%d): sc_ap %x flags %x\n",
		       p->p_pid, rf, flags);
#endif
	/*
	 * fuword failed (bogus sc_ap value).
	 */
	if (flags == -1)
		return (EINVAL);
	if (flags == 0 || copyin((caddr_t)rf, (caddr_t)&tstate, sizeof tstate))
		return (EJUSTRETURN);
#ifdef DEBUG
	if ((sigdebug & SDB_KSTACK) && p->p_pid == sigpid)
		printf("sigreturn(%d): ssp %x usp %x scp %x ft %d\n",
		       p->p_pid, &flags, scp->sc_sp, uap->sigcntxp,
		       (flags&SS_RTEFRAME) ? tstate.ss_frame.f_format : -1);
#endif
	/*
	 * Restore most of the users registers except for A6 and SP
	 * which were handled above.
	 */
	if (flags & SS_USERREGS)
		bcopy((caddr_t)tstate.ss_frame.f_regs,
		      (caddr_t)frame->f_regs, sizeof(frame->f_regs)-2*NBPW);
	/*
	 * Restore long stack frames.  Note that we do not copy
	 * back the saved SR or PC, they were picked up above from
	 * the sigcontext structure.
	 */
	if (flags & SS_RTEFRAME) {
		register int sz;
		
		/* grab frame type and validate */
		sz = tstate.ss_frame.f_format;
		if (sz > 15 || (sz = exframesize[sz]) < 0)
			return (EINVAL);
		frame->f_stackadj -= sz;
		frame->f_format = tstate.ss_frame.f_format;
		frame->f_vector = tstate.ss_frame.f_vector;
		bcopy((caddr_t)&tstate.ss_frame.F_u, (caddr_t)&frame->F_u, sz);
#ifdef DEBUG
		if (sigdebug & SDB_FOLLOW)
			printf("sigreturn(%d): copy in %d of frame type %d\n",
			       p->p_pid, sz, tstate.ss_frame.f_format);
#endif
	}
#ifdef FPCOPROC
	/*
	 * Finally we restore the original FP context
	 */
	if (flags & SS_FPSTATE)
		m68881_restore(&tstate.ss_fpstate);
#ifdef DEBUG
	if ((sigdebug & SDB_FPSTATE) && *(char *)&tstate.ss_fpstate)
		printf("sigreturn(%d): copied in FP state (%x) at %x\n",
		       p->p_pid, *(u_int *)&tstate.ss_fpstate,
		       &tstate.ss_fpstate);
#endif
#endif
#ifdef DEBUG
	if ((sigdebug & SDB_FOLLOW) ||
	    ((sigdebug & SDB_KSTACK) && p->p_pid == sigpid))
		printf("sigreturn(%d): returns\n", p->p_pid);
#endif
	return (EJUSTRETURN);
}

int	waittime = -1;

boot(howto)
	register int howto;
{
	/* take a snap shot before clobbering any registers */
	if (curproc)
		savectx(curproc->p_addr, 0);

	boothowto = howto;
D 5
	if ((howto&RB_NOSYNC) == 0 && waittime < 0 && bfreelist[0].b_forw) {
E 5
I 5
	if ((howto&RB_NOSYNC) == 0 && waittime < 0) {
E 5
		register struct buf *bp;
		int iter, nbusy;

		waittime = 0;
		(void) spl0();
		printf("syncing disks... ");
		/*
		 * Release vnodes held by texts before sync.
		 */
		if (panicstr == 0)
			vnode_pager_umount(NULL);
#ifdef notdef
#include "fd.h"
#if NFD > 0
		fdshutdown();
#endif
#endif
		sync(&proc0, (void *)NULL, (int *)NULL);
I 16
		/*
		 * Unmount filesystems
		 */
		if (panicstr == 0)
			vfs_unmountall();
E 16

		for (iter = 0; iter < 20; iter++) {
			nbusy = 0;
			for (bp = &buf[nbuf]; --bp >= buf; )
				if ((bp->b_flags & (B_BUSY|B_INVAL)) == B_BUSY)
					nbusy++;
			if (nbusy == 0)
				break;
			printf("%d ", nbusy);
			DELAY(40000 * iter);
		}
		if (nbusy)
			printf("giving up\n");
		else
			printf("done\n");
I 2

E 2
		/*
		 * If we've been adjusting the clock, the todr
		 * will be out of synch; adjust it now.
		 */
		resettodr();
	}
	splhigh();			/* extreme priority */
	if (howto&RB_HALT) {
		printf("halted\n\n");
		asm("	stop	#0x2700");
	} else {
I 2
		printf("\r\n\n");
E 2
		if (howto & RB_DUMP)
			dumpsys();
		doboot();
		/*NOTREACHED*/
	}
	/*NOTREACHED*/
}

int	dumpmag = 0x8fca0101;	/* magic number for savecore */
int	dumpsize = 0;		/* also for savecore */
long	dumplo = 0;

dumpconf()
{
	int nblks;

	dumpsize = physmem;
	if (dumpdev != NODEV && bdevsw[major(dumpdev)].d_psize) {
		nblks = (*bdevsw[major(dumpdev)].d_psize)(dumpdev);
		if (dumpsize > btoc(dbtob(nblks - dumplo)))
			dumpsize = btoc(dbtob(nblks - dumplo));
		else if (dumplo == 0)
			dumplo = nblks - btodb(ctob(physmem));
	}
	/*
	 * Don't dump on the first CLBYTES (why CLBYTES?)
	 * in case the dump device includes a disk label.
	 */
	if (dumplo < btodb(CLBYTES))
		dumplo = btodb(CLBYTES);
}

/*
 * Doadump comes here after turning off memory management and
 * getting on the dump stack, either when called above, or by
 * the auto-restart code.
 */
dumpsys()
{

	msgbufmapped = 0;
	if (dumpdev == NODEV)
		return;
	/*
	 * For dumps during autoconfiguration,
	 * if dump device has already configured...
	 */
	if (dumpsize == 0)
		dumpconf();
	if (dumplo < 0)
		return;
	printf("\ndumping to dev %x, offset %d\n", dumpdev, dumplo);
	printf("dump ");
	switch ((*bdevsw[major(dumpdev)].d_dump)(dumpdev)) {

	case ENXIO:
		printf("device bad\n");
		break;

	case EFAULT:
		printf("device not ready\n");
		break;

	case EINVAL:
		printf("area improper\n");
		break;

	case EIO:
		printf("i/o error\n");
		break;

	default:
		printf("succeeded\n");
		break;
	}
I 11
}

/*
 * machine dependent system variables.
 */
cpu_sysctl(name, namelen, oldp, oldlenp, newp, newlen, p)
	int *name;
	u_int namelen;
	void *oldp;
	size_t *oldlenp;
	void *newp;
	size_t newlen;
	struct proc *p;
{

	/* all sysctl names at this level are terminal */
	if (namelen != 1)
		return (ENOTDIR);		/* overloaded */

	switch (name[0]) {
	case CPU_CONSDEV:
		return (sysctl_rdstruct(oldp, oldlenp, newp, &cn_tty->t_dev,
		    sizeof cn_tty->t_dev));
	default:
		return (EOPNOTSUPP);
	}
	/* NOTREACHED */
E 11
}

D 3
microtime(tvp)
	register struct timeval *tvp;
{
	int s = splhigh();

	*tvp = time;
	tvp->tv_usec += tick;
	while (tvp->tv_usec > 1000000) {
		tvp->tv_sec++;
		tvp->tv_usec -= 1000000;
	}
	splx(s);
}

E 3
initcpu()
{
I 14
#ifdef MAPPEDCOPY
	extern u_int mappedcopysize;

	/*
	 * Initialize lower bound for doing copyin/copyout using
	 * page mapping (if not already set).  We don't do this on
	 * VAC machines as it loses big time.
	 */
	if (mappedcopysize == 0) {
		if (ectype == EC_VIRT)
			mappedcopysize = (u_int) -1;
		else
			mappedcopysize = NBPG;
	}
#endif
E 14
	parityenable();
}

straytrap(pc, evec)
	int pc;
	u_short evec;
{
	printf("unexpected trap (vector offset %x) from %x\n",
	       evec & 0xFFF, pc);
}

int	*nofault;

badaddr(addr)
	register caddr_t addr;
{
	register int i;
	label_t	faultbuf;

#ifdef lint
	i = *addr; if (i) return(0);
#endif
	nofault = (int *) &faultbuf;
	if (setjmp((label_t *)nofault)) {
		nofault = (int *) 0;
		return(1);
	}
	i = *(volatile short *)addr;
	nofault = (int *) 0;
	return(0);
}

badbaddr(addr)
	register caddr_t addr;
{
	register int i;
	label_t	faultbuf;

#ifdef lint
	i = *addr; if (i) return(0);
#endif
	nofault = (int *) &faultbuf;
	if (setjmp((label_t *)nofault)) {
		nofault = (int *) 0;
		return(1);
	}
	i = *(volatile char *)addr;
	nofault = (int *) 0;
	return(0);
}

netintr()
{
#ifdef INET
	if (netisr & (1 << NETISR_ARP)) {
		netisr &= ~(1 << NETISR_ARP);
		arpintr();
	}
	if (netisr & (1 << NETISR_IP)) {
		netisr &= ~(1 << NETISR_IP);
		ipintr();
	}
#endif
#ifdef NS
	if (netisr & (1 << NETISR_NS)) {
		netisr &= ~(1 << NETISR_NS);
		nsintr();
	}
#endif
#ifdef ISO
	if (netisr & (1 << NETISR_ISO)) {
		netisr &= ~(1 << NETISR_ISO);
		clnlintr();
	}
#endif
I 6
#ifdef CCITT
	if (netisr & (1 << NETISR_CCITT)) {
		netisr &= ~(1 << NETISR_CCITT);
		ccittintr();
	}
#endif
E 6
}

#ifdef	notfdef
intrhand(sr)
	int sr;
{
	register struct isr *isr;
	register int found = 0;
	register int ipl;
	extern struct isr isrqueue[];

	ipl = (sr >> 8) & 7;
	switch (ipl) {

	case 3:
	case 4:
	case 5:
		ipl = ISRIPL(ipl);
		isr = isrqueue[ipl].isr_forw;
		for (; isr != &isrqueue[ipl]; isr = isr->isr_forw) {
			if ((isr->isr_intr)(isr->isr_arg)) {
				found++;
				break;
			}
		}
		if (found == 0)
			printf("stray interrupt, sr 0x%x\n", sr);
		break;

	case 0:
	case 1:
	case 2:
	case 6:
	case 7:
		printf("intrhand: unexpected sr 0x%x\n", sr);
		break;
	}
}
#endif

#if defined(DEBUG) && !defined(PANICBUTTON)
#define PANICBUTTON
#endif

#ifdef PANICBUTTON
int panicbutton = 1;	/* non-zero if panic buttons are enabled */
int crashandburn = 0;
int candbdelay = 50;	/* give em half a second */

D 3
candbtimer()
E 3
I 3
void
candbtimer(arg)
	void *arg;
E 3
{
I 3

E 3
	crashandburn = 0;
}
#endif

/*
 * Level 7 interrupts can be caused by the keyboard or parity errors.
 */
nmihand(frame)
	struct frame frame;
{
#ifdef PANICBUTTON
       	static int innmihand = 0;

       	/*
       	 * Attempt to reduce the window of vulnerability for recursive
       	 * NMIs (e.g. someone holding down the keyboard reset button).
       	 */
       	if (innmihand == 0) {
       		innmihand = 1;
       		printf("Got a keyboard NMI\n");
       		innmihand = 0;
       	}
       	if (panicbutton) {
       		if (crashandburn) {
       			crashandburn = 0;
       			panic(panicstr ?
       			      "forced crash, nosync" : "forced crash");
       		}
       		crashandburn++;
D 3
       		timeout(candbtimer, (caddr_t)0, candbdelay);
E 3
I 3
       		timeout(candbtimer, (void *)0, candbdelay);
E 3
       	}
#endif
       	return;
}

D 6
regdump(rp, sbytes)
  int *rp; /* must not be register */
  int sbytes;
E 6
I 6
regdump(fp, sbytes)
	struct frame *fp; /* must not be register */
	int sbytes;
E 6
{
	static int doingdump = 0;
	register int i;
	int s;
	extern char *hexstr();

	if (doingdump)
		return;
	s = splhigh();
	doingdump = 1;
D 6
	printf("pid = %d, pc = %s, ", curproc->p_pid, hexstr(rp[PC], 8));
	printf("ps = %s, ", hexstr(rp[PS], 4));
E 6
I 6
	printf("pid = %d, pc = %s, ",
	       curproc ? curproc->p_pid : -1, hexstr(fp->f_pc, 8));
	printf("ps = %s, ", hexstr(fp->f_sr, 4));
E 6
	printf("sfc = %s, ", hexstr(getsfc(), 4));
	printf("dfc = %s\n", hexstr(getdfc(), 4));
	printf("Registers:\n     ");
	for (i = 0; i < 8; i++)
		printf("        %d", i);
	printf("\ndreg:");
	for (i = 0; i < 8; i++)
D 6
		printf(" %s", hexstr(rp[i], 8));
E 6
I 6
		printf(" %s", hexstr(fp->f_regs[i], 8));
E 6
	printf("\nareg:");
	for (i = 0; i < 8; i++)
D 6
		printf(" %s", hexstr(rp[i+8], 8));
E 6
I 6
		printf(" %s", hexstr(fp->f_regs[i+8], 8));
E 6
	if (sbytes > 0) {
D 6
		if (rp[PS] & PSL_S) {
E 6
I 6
		if (fp->f_sr & PSL_S) {
E 6
			printf("\n\nKernel stack (%s):",
D 6
			       hexstr((int)(((int *)&rp)-1), 8));
			dumpmem(((int *)&rp)-1, sbytes, 0);
E 6
I 6
			       hexstr((int)(((int *)&fp)-1), 8));
			dumpmem(((int *)&fp)-1, sbytes, 0);
E 6
		} else {
D 6
			printf("\n\nUser stack (%s):", hexstr(rp[SP], 8));
			dumpmem((int *)rp[SP], sbytes, 1);
E 6
I 6
			printf("\n\nUser stack (%s):", hexstr(fp->f_regs[SP], 8));
			dumpmem((int *)fp->f_regs[SP], sbytes, 1);
E 6
		}
	}
	doingdump = 0;
	splx(s);
}

extern char kstack[];
#define KSADDR	((int *)&(kstack[(UPAGES-1)*NBPG]))

dumpmem(ptr, sz, ustack)
	register int *ptr;
	int sz;
{
	register int i, val;
	extern char *hexstr();

	for (i = 0; i < sz; i++) {
		if ((i & 7) == 0)
			printf("\n%s: ", hexstr((int)ptr, 6));
		else
			printf(" ");
		if (ustack == 1) {
			if ((val = fuword(ptr++)) == -1)
				break;
		} else {
			if (ustack == 0 &&
			    (ptr < KSADDR || ptr > KSADDR+(NBPG/4-1)))
				break;
			val = *ptr++;
		}
		printf("%s", hexstr(val, 8));
	}
	printf("\n");
}

char *
hexstr(val, len)
	register int val;
{
	static char nbuf[9];
	register int x, i;

	if (len > 8)
		return("");
	nbuf[len] = '\0';
	for (i = len-1; i >= 0; --i) {
		x = val & 0xF;
		if (x > 9)
			nbuf[i] = x - 10 + 'A';
		else
			nbuf[i] = x + '0';
		val >>= 4;
	}
	return(nbuf);
}

I 6
#ifdef DEBUG
char oflowmsg[] = "k-stack overflow";
char uflowmsg[] = "k-stack underflow";

badkstack(oflow, fr)
	int oflow;
	struct frame fr;
{
I 9
#ifdef	notdef
E 9
	extern char kstackatbase[];

	printf("%s: sp should be %x\n", 
	       oflow ? oflowmsg : uflowmsg,
	       kstackatbase - (exframesize[fr.f_format] + 8));
I 9
#endif
	printf("%s: sp should be ????????\n", oflow ? oflowmsg : uflowmsg);
E 9
	regdump(&fr, 0);
	panic(oflow ? oflowmsg : uflowmsg);
}
#endif

E 6
/* for LUNA */

/*
 * Enable parity detection
 */
#define PARREG		((volatile short *)0x49000003)
#define	PARITY_ENABLE	0xC
parityenable()
{
D 6
    *PARREG = PARITY_ENABLE;
E 6
I 6
	*PARREG = PARITY_ENABLE;
E 6
}

#ifdef FPCOPROC
#define EXT_FPP_ADDR		0x6F000000	/* External 68882 board  */
#define INT_FPP_ADDR		0x6B000000	/* Internal 68881 chip   */

#define FPP_ON			0x80		/* selected fpp on	 */
#define FPP_OFF			0x00		/* selected fpp off    	 */

#define	SET_INT_FPP	(*(char *)INT_FPP_ADDR = FPP_ON);(*(char *)EXT_FPP_ADDR = FPP_OFF)
#define	SET_EXT_FPP	(*(char *)INT_FPP_ADDR = FPP_OFF);(*(char *)EXT_FPP_ADDR = FPP_ON)

#define	FPP68881	1
#define	FPP68882	2

unsigned char fpp_svarea[212];

#ifndef	OLD_LUNA
/*
 * Check FPP type 68881/68882.
 */

void checkfpp()
{
I 10
#ifdef LUNA2
	if (machineid == LUNA_II) {
		return;
	}
#endif
E 10
    SET_INT_FPP;	/* internal = on, external = off */
    if( is_68882() )
      fpptype = FPP68882;
    else
      fpptype = FPP68881;
    return;
}
#else

/*
 * Check in/ex-ternal fpp, and determine which we use.
 * Also set fpp type(MC68881/68882).
 */

void checkfpp()
{
int	internal_exist,external_exist;
int	external_68882;
I 10
#ifdef LUNA2
	if (machineid == LUNA_II) {
		return;
	}
#endif
E 10

    SET_INT_FPP;	/* internal = on, external = off */
    if ( internal_exist = havefpp() && is_68882() ) {	/* internal = 68882 */
	fpptype = FPP68882;
	return;
    } else {		/* internal don't exist  or it is not 68882 */
        SET_EXT_FPP;	/* internal = off, external = on */
	if ( internal_exist && 	/* internal = 68882, external <> 68882 */
	     (!(external_exist = havefpp()) || !(external_68882 = is_68882())) ) {
	   SET_INT_FPP;	/* internal = on, external = off */
	   fpptype = FPP68881;
	   return;
        }
	if ( internal_exist ) { /* internal = 68881, external = 68882 */
	   fpptype = FPP68882;
	   return;
        }
	if ( external_exist )  /* internal not exist, external exist */
	    if ( external_68882 ) { 	/* external = 68882 */
		fpptype = FPP68882;
		return;
	    } else { 			/* external = 68881 */
		fpptype = FPP68881;
		return;
	    }
	else		/* in/ex-ternal non exist */
	    panic("fpp non-existence");
    }
}
#endif
#endif
E 1
