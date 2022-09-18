h24525
s 00005/00000/00960
d D 8.4 95/05/09 12:11:17 mckusick 17 16
c put in request to unmount all filesystems when rebooting
e
s 00001/00001/00959
d D 8.3 94/01/12 14:28:58 hibler 16 15
c entries_pageable set TRUE for buffer map (set vm_map.c change).
e
s 00002/00002/00958
d D 8.2 93/09/23 16:41:05 bostic 15 14
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00958
d D 8.1 93/06/11 15:02:56 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00956
d D 7.13 93/05/30 20:07:20 utashiro 13 12
c added CPU_CONSDEV sysctl
e
s 00025/00000/00931
d D 7.12 93/05/24 00:42:47 utashiro 12 11
c added cpu_sysctl().
e
s 00006/00019/00925
d D 7.11 93/05/13 19:49:59 utashiro 11 10
c change for new pmap interface.
e
s 00005/00000/00939
d D 7.10 93/04/08 02:37:20 utashiro 10 9
c added traceback becore panic
e
s 00007/00001/00932
d D 7.9 93/03/10 04:48:09 utashiro 9 8
c declare machine and cpu_model
e
s 00008/00012/00925
d D 7.8 93/03/09 23:55:55 utashiro 8 7
c make it rebootable
e
s 00038/00046/00899
d D 7.7 93/01/20 00:19:57 utashiro 7 6
c Same changes as pmax.
e
s 00025/00025/00920
d D 7.6 92/12/17 01:28:21 utashiro 6 5
c make kernel includes standard
e
s 00001/00001/00944
d D 7.5 92/12/16 20:53:22 utashiro 5 4
c Added news3400 code
e
s 00004/00003/00941
d D 7.4 92/07/10 18:07:14 torek 4 3
c ANSIfy syscall args
e
s 00004/00000/00940
d D 7.3 92/06/26 18:35:48 utashiro 3 2
c support non-display configuration
e
s 00015/00008/00925
d D 7.2 92/06/25 18:40:22 utashiro 2 1
c changes from pmax/machdep.c
e
s 00933/00000/00000
d D 7.1 92/06/04 16:06:56 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 14
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department, The Mach Operating System project at
 * Carnegie-Mellon University, Ralph Campbell, Sony Corp. and Kazumasa
 * Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* from: Utah $Hdr: machdep.c 1.63 91/04/24$ */

D 6
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
#include "user.h"
E 6
I 6
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
#include <sys/user.h>
I 7
#include <sys/exec.h>
I 12
#include <sys/sysctl.h>
E 12
E 7
E 6
#ifdef SYSVSHM
D 6
#include "shm.h"
E 6
I 6
#include <sys/shm.h>
E 6
#endif

D 6
#include "vm/vm.h"
#include "vm/vm_kern.h"
#include "vm/vm_page.h"
E 6
I 6
D 11
#include <vm/vm.h>
E 11
#include <vm/vm_kern.h>
D 11
#include <vm/vm_page.h>
E 11
E 6

D 6
#include "../include/cpu.h"
#include "../include/reg.h"
#include "../include/psl.h"
#include "../include/pte.h"
E 6
I 6
#include <machine/cpu.h>
#include <machine/reg.h>
#include <machine/psl.h>
#include <machine/pte.h>
E 6

D 6
#include "../include/adrsmap.h"
E 6
I 6
#include <machine/adrsmap.h>
E 6

vm_map_t buffer_map;

I 9
/* the following is used externally (sysctl_hw) */
char	machine[] = "SONY";	/* cpu "architecture" */
char	cpu_model[30];

E 9
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
D 7
int	msgbufmapped;		/* set when safe to use msgbuf */
E 7
I 7
int	msgbufmapped = 0;	/* set when safe to use msgbuf */
E 7
int	maxmem;			/* max memory per process */
int	physmem;		/* max supported memory, changes to actual */
/*
 * safepri is a safe priority for sleep to set for a spin-wait
 * during autoconfiguration or after a panic.
 */
int	safepri = PSL_LOWIPL;

struct	user *proc0paddr;
D 15
struct	proc nullproc;		/* for use by swtch_exit() */
E 15
I 15
struct	proc nullproc;		/* for use by switch_exit() */
E 15

/*
 * Do all the stuff that locore normally does before calling main().
 * Process arguments passed to us by the prom monitor.
 * Return the first page address following the system.
 */
mach_init(x_boothowto, x_unkown, x_bootdev, x_maxmem)
	int x_boothowto;
	int x_unkown;
	int x_bootdev;
	int x_maxmem;
{
	register char *cp;
	register int i;
	register unsigned firstaddr;
	register caddr_t v;
	caddr_t start;
	extern u_long bootdev;
	extern char edata[], end[];
	extern char MachUTLBMiss[], MachUTLBMissEnd[];
	extern char MachException[], MachExceptionEnd[];
D 11
#ifdef ATTR
	extern char *pmap_attributes;
#endif
E 11

I 8
	/*
	 * Save parameters into kernel work area.
	 */
	*(int *)(MACH_CACHED_TO_UNCACHED(MACH_MAXMEMSIZE_ADDR)) = x_maxmem;
	*(int *)(MACH_CACHED_TO_UNCACHED(MACH_BOOTDEV_ADDR)) = x_bootdev;
	*(int *)(MACH_CACHED_TO_UNCACHED(MACH_BOOTSW_ADDR)) = x_boothowto;

E 8
	/* clear the BSS segment */
	v = (caddr_t)pmax_round_page(end);
	bzero(edata, v - edata);

	boothowto = x_boothowto;
	bootdev = x_bootdev;
	maxmem = physmem = pmax_btop(x_maxmem);

	/*
	 * Look at arguments passed to us and compute boothowto.
	 */
#ifdef GENERIC
	boothowto |= RB_SINGLE | RB_ASKNAME;
#endif
#ifdef KADB
	boothowto |= RB_KDB;
#endif

#ifdef MFS
	/*
	 * Check to see if a mini-root was loaded into memory. It resides
	 * at the start of the next page just after the end of BSS.
	 */
D 9
	if (boothowto & RB_MINIROOT)
E 9
I 9
	if (boothowto & RB_MINIROOT) {
		boothowto |= RB_DFLTROOT;
E 9
		v += mfs_initminiroot(v);
I 9
	}
E 9
#endif

	/*
	 * Init mapping for u page(s) for proc[0], pm_tlbpid 1.
	 */
	start = v;
	curproc->p_addr = proc0paddr = (struct user *)v;
	curproc->p_md.md_regs = proc0paddr->u_pcb.pcb_regs;
	firstaddr = MACH_CACHED_TO_PHYS(v);
	for (i = 0; i < UPAGES; i++) {
		MachTLBWriteIndexed(i,
			(UADDR + (i << PGSHIFT)) | (1 << VMMACH_TLB_PID_SHIFT),
			curproc->p_md.md_upte[i] = firstaddr | PG_V | PG_M);
		firstaddr += NBPG;
	}
	v += UPAGES * NBPG;
	MachSetPID(1);

	/*
D 15
	 * init nullproc for swtch_exit().
E 15
I 15
	 * init nullproc for switch_exit().
E 15
	 * init mapping for u page(s), pm_tlbpid 0
	 * This could be used for an idle process.
	 */
	nullproc.p_addr = (struct user *)v;
D 11
	nullproc.p_md.md_regs = ((struct user *)v)->u_pcb.pcb_regs;
E 11
I 11
	nullproc.p_md.md_regs = nullproc.p_addr->u_pcb.pcb_regs;
	bcopy("nullproc", nullproc.p_comm, sizeof("nullproc"));
E 11
	for (i = 0; i < UPAGES; i++) {
		nullproc.p_md.md_upte[i] = firstaddr | PG_V | PG_M;
		firstaddr += NBPG;
	}
	v += UPAGES * NBPG;

	/* clear pages for u areas */
	bzero(start, v - start);

	/*
	 * Copy down exception vector code.
	 */
	if (MachUTLBMissEnd - MachUTLBMiss > 0x80)
		panic("startup: UTLB code too large");
	bcopy(MachUTLBMiss, (char *)MACH_UTLB_MISS_EXC_VEC,
		MachUTLBMissEnd - MachUTLBMiss);
	bcopy(MachException, (char *)MACH_GEN_EXC_VEC,
		MachExceptionEnd - MachException);

	/*
	 * Clear out the I and D caches.
	 */
	MachConfigCache();
	MachFlushCache();

	/*
	 * Initialize error message buffer (at end of core).
	 */
	maxmem -= btoc(sizeof (struct msgbuf));
	msgbufp = (struct msgbuf *)(MACH_PHYS_TO_CACHED(maxmem << PGSHIFT));
	msgbufmapped = 1;

	/*
	 * Allocate space for system data structures.
	 * The first available kernel virtual address is in "v".
	 * As pages of kernel virtual memory are allocated, "v" is incremented.
	 *
	 * These data structures are allocated here instead of cpu_startup()
	 * because physical memory is directly addressable. We don't have
	 * to map these into virtual address space.
	 */
	start = v;

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
D 11
#ifdef ATTR
	/* this is allocated here just to save a few bytes */
	valloc(pmap_attributes, char, physmem);
#endif
E 11

	/*
	 * Determine how many buffers to allocate.
	 * We allocate more buffer space than the BSD standard of
	 * using 10% of memory for the first 2 Meg, 5% of remaining.
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
	 * Clear allocated memory.
	 */
D 11
	v = (caddr_t)pmax_round_page(v);
E 11
	bzero(start, v - start);

	/*
	 * Initialize the virtual memory system.
	 */
D 11
	pmap_bootstrap((vm_offset_t)MACH_CACHED_TO_PHYS(v));
E 11
I 11
	pmap_bootstrap((vm_offset_t)v);
E 11
}

/*
 * Console initialization: called early on from main,
 * before vm init or startup.  Do enough configuration
 * to choose and initialize a console.
 * XXX need something better here.
 */
#define	SCC_CONSOLE	0
#define	SW_CONSOLE	0x07
#define	SW_NWB512	0x04
#define	SW_NWB225	0x01
#define	SW_FBPOP	0x02
#define	SW_FBPOP1	0x06
#define	SW_FBPOP2	0x03
#define	SW_AUTOSEL	0x07
consinit()
{
	extern dev_t consdev;
	extern struct tty *constty, *cn_tty, *rs_tty;
	int dipsw = (int)*(volatile u_char *)DIP_SWITCH;

#include "bm.h"
#if NBM > 0
D 5
#ifdef news3200
E 5
I 5
#if defined(news3200) || defined(news3400)	/* KU:XXX */
E 5
	fbbm_probe(dipsw|2);
#else
	fbbm_probe(dipsw);
#endif
	vt100_open();
	setup_fnt();
	setup_fnt24();
I 3
#else
	dipsw &= SW_CONSOLE;
E 3
#endif

	switch (dipsw & SW_CONSOLE) {
	    case 0:
		scc_open(SCC_CONSOLE);
		consdev = makedev(1, 0);
		constty = rs_tty;
		break;

	    default:
I 3
#if NBM > 0
E 3
		consdev = makedev(22, 0);
		constty = cn_tty;
I 3
#endif
E 3
		break;
	}
	return(0);
}

/*
 * cpu_startup: allocate memory for variable-sized tables,
 * initialize cpu, and do autoconfiguration.
 */
cpu_startup()
{
	register unsigned i;
	register caddr_t v;
	int base, residual;
D 11
	extern long Usrptsize;
	extern struct map *useriomap;
E 11
I 11
	vm_offset_t minaddr, maxaddr;
	vm_size_t size;
E 11
#ifdef DEBUG
	extern int pmapdebug;
	int opmapdebug = pmapdebug;
D 11
#endif
	vm_offset_t minaddr, maxaddr;
	vm_size_t size;
E 11

D 11
#ifdef DEBUG
E 11
	pmapdebug = 0;
#endif

	/*
	 * Good {morning,afternoon,evening,night}.
	 */
	printf(version);
	printf("real mem = %d\n", ctob(physmem));

	/*
	 * Allocate virtual address space for file I/O buffers.
	 * Note they are different than the array of headers, 'buf',
	 * and usually occupy more virtual memory than physical.
	 */
	size = MAXBSIZE * nbuf;
D 2
	buffer_map = kmem_suballoc(kernel_map, (vm_offset_t)&buffers,
E 2
I 2
	buffer_map = kmem_suballoc(kernel_map, (vm_offset_t *)&buffers,
E 2
D 16
				   &maxaddr, size, FALSE);
E 16
I 16
				   &maxaddr, size, TRUE);
E 16
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
D 11
				 16*NCARGS, TRUE);
E 11
I 11
				 16 * NCARGS, TRUE);
E 11
	/*
	 * Allocate a submap for physio
	 */
	phys_map = kmem_suballoc(kernel_map, &minaddr, &maxaddr,
				 VM_PHYS_SIZE, TRUE);

	/*
	 * Finally, allocate mbuf pool.  Since mclrefcnt is an off-size
	 * we use the more space efficient malloc in place of kmem_alloc.
	 */
D 7
	mclrefcnt = malloc(NMBCLUSTERS + CLBYTES/MCLBYTES, M_MBUF, M_NOWAIT);
	bzero(mclrefcnt, NMBCLUSTERS + CLBYTES/MCLBYTES);
E 7
I 7
	mclrefcnt = (char *)malloc(NMBCLUSTERS+CLBYTES/MCLBYTES,
				   M_MBUF, M_NOWAIT);
	bzero(mclrefcnt, NMBCLUSTERS+CLBYTES/MCLBYTES);
E 7
D 2
	mb_map = kmem_suballoc(kernel_map, (vm_offset_t)&mbutl, &maxaddr,
E 2
I 2
	mb_map = kmem_suballoc(kernel_map, (vm_offset_t *)&mbutl, &maxaddr,
E 2
			       VM_MBUF_SIZE, FALSE);
	/*
	 * Initialize callouts
	 */
	callfree = callout;
	for (i = 1; i < ncallout; i++)
		callout[i-1].c_next = &callout[i];
I 2
	callout[i-1].c_next = NULL;
E 2

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
 * Clear all registers except sp, pc.
 */
setregs(p, entry, retval)
	register struct proc *p;
	u_long entry;
	int retval[2];
{
	int sp = p->p_md.md_regs[SP];
	extern struct proc *machFPCurProcPtr;

	bzero((caddr_t)p->p_md.md_regs, (FSR + 1) * sizeof(int));
	p->p_md.md_regs[SP] = sp;
D 7
	p->p_md.md_regs[PC] = entry;
E 7
I 7
	p->p_md.md_regs[PC] = entry & ~3;
E 7
	p->p_md.md_regs[PS] = PSL_USERSET;
	p->p_md.md_flags & ~MDP_FPUSED;
	if (machFPCurProcPtr == p)
		machFPCurProcPtr = (struct proc *)0;
}

/*
 * WARNING: code in locore.s assumes the layout shown for sf_signum
 * thru sf_handler so... don't screw with them!
 */
struct sigframe {
	int	sf_signum;		/* signo for handler */
	int	sf_code;		/* additional info for handler */
	struct	sigcontext *sf_scp;	/* context ptr for handler */
	sig_t	sf_handler;		/* handler addr for u_sigc */
I 7
	struct	sigcontext sf_sc;	/* actual context */
E 7
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
	register struct sigframe *fp;
D 2
	register struct sigacts *ps = p->p_sigacts;
E 2
I 2
D 7
	register struct sigacts *psp = p->p_sigacts;
E 2
	register struct sigcontext *scp;
E 7
	register int *regs;
I 7
	register struct sigacts *psp = p->p_sigacts;
E 7
	int oonstack, fsize;
	struct sigcontext ksc;
I 7
	extern char sigcode[], esigcode[];
E 7

	regs = p->p_md.md_regs;
D 2
	oonstack = ps->ps_onstack;
E 2
I 2
	oonstack = psp->ps_sigstk.ss_flags & SA_ONSTACK;
E 2
	/*
	 * Allocate and validate space for the signal handler
	 * context. Note that if the stack is in data space, the
	 * call to grow() is a nop, and the copyout()
	 * will fail if the process has not already allocated
	 * the space with a `brk'.
	 */
I 7
	fsize = sizeof(struct sigframe);
E 7
D 2
	if (!ps->ps_onstack && (ps->ps_sigonstack & sigmask(sig))) {
		scp = (struct sigcontext *)ps->ps_sigsp - 1;
		ps->ps_onstack = 1;
E 2
I 2
	if ((psp->ps_flags & SAS_ALTSTACK) &&
	    (psp->ps_sigstk.ss_flags & SA_ONSTACK) == 0 &&
	    (psp->ps_sigonstack & sigmask(sig))) {
D 7
		scp = (struct sigcontext *)(psp->ps_sigstk.ss_base +
		    psp->ps_sigstk.ss_size) - 1;
E 7
I 7
		fp = (struct sigframe *)(psp->ps_sigstk.ss_base +
					 psp->ps_sigstk.ss_size - fsize);
E 7
		psp->ps_sigstk.ss_flags |= SA_ONSTACK;
E 2
	} else
D 7
		scp = (struct sigcontext *)regs[SP] - 1;
	fp = (struct sigframe *)scp - 1;
E 7
I 7
		fp = (struct sigframe *)(regs[SP] - fsize);
E 7
	if ((unsigned)fp <= USRSTACK - ctob(p->p_vmspace->vm_ssize)) 
		(void)grow(p, (unsigned)fp);
I 7
#ifdef DEBUG
	if ((sigdebug & SDB_FOLLOW) ||
	    (sigdebug & SDB_KSTACK) && p->p_pid == sigpid)
		printf("sendsig(%d): sig %d ssp %x usp %x scp %x\n",
		       p->p_pid, sig, &oonstack, fp, &fp->sf_sc);
#endif
E 7
	/*
	 * Build the signal context to be used by sigreturn.
	 */
	ksc.sc_onstack = oonstack;
	ksc.sc_mask = mask;
	ksc.sc_pc = regs[PC];
	ksc.sc_regs[ZERO] = 0xACEDBADE;		/* magic number */
	bcopy((caddr_t)&regs[1], (caddr_t)&ksc.sc_regs[1],
		sizeof(ksc.sc_regs) - sizeof(int));
	ksc.sc_fpused = p->p_md.md_flags & MDP_FPUSED;
	if (ksc.sc_fpused) {
		extern struct proc *machFPCurProcPtr;

		/* if FPU has current state, save it first */
		if (p == machFPCurProcPtr)
			MachSaveCurFPState(p);
		bcopy((caddr_t)&p->p_md.md_regs[F0], (caddr_t)ksc.sc_fpregs,
			sizeof(ksc.sc_fpregs));
	}
D 7
	if (copyout((caddr_t)&ksc, (caddr_t)scp, sizeof(ksc))) {
E 7
I 7
	if (copyout((caddr_t)&ksc, (caddr_t)&fp->sf_sc, sizeof(ksc))) {
E 7
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
	/* 
	 * Build the argument list for the signal handler.
	 */
	regs[A0] = sig;
	regs[A1] = code;
D 7
	regs[A2] = (int)scp;
E 7
I 7
	regs[A2] = (int)&fp->sf_sc;
E 7
	regs[A3] = (int)catcher;

	regs[PC] = (int)catcher;
	regs[SP] = (int)fp;
D 7
	regs[RA] = KERNBASE;	/* this causes a trap which we interpret as
				 * meaning "do a sigreturn". */
E 7
I 7
	/*
	 * Signal trampoline code is at base of user stack.
	 */
	regs[RA] = (int)PS_STRINGS - (esigcode - sigcode);
E 7
#ifdef DEBUG
D 7
	if ((sigdebug & SDB_KSTACK) && p->p_pid == sigpid)
		printf("sendsig(%d): sig %d ssp %x usp %x scp %x\n",
		       p->p_pid, sig, &oonstack, fp, fp->sf_scp);
E 7
I 7
	if ((sigdebug & SDB_FOLLOW) ||
	    (sigdebug & SDB_KSTACK) && p->p_pid == sigpid)
		printf("sendsig(%d): sig %d returns\n",
		       p->p_pid, sig);
E 7
#endif
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
I 4
struct sigreturn_args {
	struct sigcontext *sigcntxp;
};
E 4
/* ARGSUSED */
sigreturn(p, uap, retval)
	struct proc *p;
D 4
	struct args {
		struct sigcontext *sigcntxp;
	} *uap;
E 4
I 4
	struct sigreturn_args *uap;
E 4
	int *retval;
{
	register struct sigcontext *scp;
	register int *regs;
	struct sigcontext ksc;
	int error;

D 7
	register struct frame *frame;
	register int rf;
	struct sigcontext tsigc;
	int flags;

E 7
	scp = uap->sigcntxp;
#ifdef DEBUG
	if (sigdebug & SDB_FOLLOW)
		printf("sigreturn: pid %d, scp %x\n", p->p_pid, scp);
#endif
	regs = p->p_md.md_regs;
	/*
	 * Test and fetch the context structure.
	 * We grab it all at once for speed.
	 */
	error = copyin((caddr_t)scp, (caddr_t)&ksc, sizeof(ksc));
D 7
	if (error != 0 || ksc.sc_regs[ZERO] != 0xACEDBADE ||
	    (unsigned)ksc.sc_regs[SP] < (unsigned)regs[SP]) {
E 7
I 7
	if (error || ksc.sc_regs[ZERO] != 0xACEDBADE) {
E 7
#ifdef DEBUG
		if (!(sigdebug & SDB_FOLLOW))
			printf("sigreturn: pid %d, scp %x\n", p->p_pid, scp);
		printf("  old sp %x ra %x pc %x\n",
			regs[SP], regs[RA], regs[PC]);
		printf("  new sp %x ra %x pc %x err %d z %x\n",
			ksc.sc_regs[SP], ksc.sc_regs[RA], ksc.sc_regs[PC],
			error, ksc.sc_regs[ZERO]);
#endif
D 7
		if (regs[PC] == KERNBASE) {
			int sig;

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
		}
E 7
		return (EINVAL);
	}
I 7
	scp = &ksc;
E 7
	/*
	 * Restore the user supplied information
	 */
D 2
	p->p_sigacts->ps_onstack = scp->sc_onstack & 01;
E 2
I 2
	if (scp->sc_onstack & 01)
		p->p_sigacts->ps_sigstk.ss_flags |= SA_ONSTACK;
	else
		p->p_sigacts->ps_sigstk.ss_flags &= ~SA_ONSTACK;
E 2
	p->p_sigmask = scp->sc_mask &~ sigcantmask;
D 7
	regs[PC] = ksc.sc_pc;
	bcopy((caddr_t)&ksc.sc_regs[1], (caddr_t)&regs[1],
		sizeof(ksc.sc_regs) - sizeof(int));
	ksc.sc_fpused = p->p_md.md_flags & MDP_FPUSED;
	if (ksc.sc_fpused)
		bcopy((caddr_t)ksc.sc_fpregs, (caddr_t)&p->p_md.md_regs[F0],
			sizeof(ksc.sc_fpregs));
E 7
I 7
	regs[PC] = scp->sc_pc;
	bcopy((caddr_t)&scp->sc_regs[1], (caddr_t)&regs[1],
		sizeof(scp->sc_regs) - sizeof(int));
	if (scp->sc_fpused)
		bcopy((caddr_t)scp->sc_fpregs, (caddr_t)&p->p_md.md_regs[F0],
			sizeof(scp->sc_fpregs));
E 7
	return (EJUSTRETURN);
}

int	waittime = -1;

boot(howto)
	register int howto;
{

	/* take a snap shot before clobbering any registers */
	if (curproc)
		savectx(curproc->p_addr, 0);

I 10
#ifdef DEBUG
	if (panicstr)
		traceback();
#endif

E 10
D 8
	howto |= RB_HALT; /* XXX */
E 8
	boothowto = howto;
D 7
	if ((howto&RB_NOSYNC) == 0 && waittime < 0 && bfreelist[0].b_forw) {
E 7
I 7
D 8
	if ((howto&RB_NOSYNC) == 0 && waittime < 0) {
E 8
I 8
	if ((howto & RB_NOSYNC) == 0 && waittime < 0) {
E 8
E 7
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
#ifdef notyet
#include "fd.h"
#if NFD > 0
		fdshutdown();
#endif
#endif
		sync(&proc0, (void *)NULL, (int *)NULL);
I 17
		/*
		 * Unmount filesystems
		 */
		if (panicstr == 0)
			vfs_unmountall();
E 17

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
		/*
		 * If we've been adjusting the clock, the todr
		 * will be out of synch; adjust it now.
		 */
		resettodr();
	}
	(void) splhigh();		/* extreme priority */
	if (howto & RB_HALT) {
		halt(howto);
		/*NOTREACHED*/
	} else {
		if (howto & RB_DUMP)
			dumpsys();
		halt(howto);
		/*NOTREACHED*/
	}
	/*NOTREACHED*/
}

halt(howto)
	int howto;
{
	if (*(volatile u_char *)DIP_SWITCH & 0x20)
		howto |= RB_HALT;
	to_monitor(howto);
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
	int error;

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
	switch (error = (*bdevsw[major(dumpdev)].d_dump)(dumpdev)) {

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
		printf("error %d\n", error);
		break;

	case 0:
		printf("succeeded\n");
	}
I 12
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
I 13
	extern dev_t consdev;
E 13

	/* all sysctl names at this level are terminal */
	if (namelen != 1)
		return (ENOTDIR);		/* overloaded */

	switch (name[0]) {
I 13
	case CPU_CONSDEV:
		return (sysctl_rdstruct(oldp, oldlenp, newp, &consdev,
		    sizeof consdev));
E 13
	default:
		return (EOPNOTSUPP);
	}
	/* NOTREACHED */
E 12
}

/*
 * Return the best possible estimate of the time in the timeval
 * to which tvp points.  Unfortunately, we can't read the hardware registers.
 * We guarantee that the time will be greater than the value obtained by a
 * previous call.
 */
microtime(tvp)
	register struct timeval *tvp;
{
	int s = splclock();
	static struct timeval lasttime;

	*tvp = time;
#ifdef notdef
	tvp->tv_usec += clkread();
	while (tvp->tv_usec > 1000000) {
		tvp->tv_sec++;
		tvp->tv_usec -= 1000000;
	}
#endif
	if (tvp->tv_sec == lasttime.tv_sec &&
	    tvp->tv_usec <= lasttime.tv_usec &&
	    (tvp->tv_usec = lasttime.tv_usec + 1) > 1000000) {
		tvp->tv_sec++;
		tvp->tv_usec -= 1000000;
	}
	lasttime = *tvp;
	splx(s);
}

initcpu()
{

	/*
	 * clear LEDs
	 */
	*(char*)DEBUG_PORT = (char)DP_WRITE|DP_LED0|DP_LED1|DP_LED2|DP_LED3;

	/*
	 * clear all interrupts
	 */
	*(char*)INTCLR0 = 0;
	*(char*)INTCLR1 = 0;

	/*
	 * It's not a time to enable timer yet.
	 *
	 *	INTEN0:  PERR ABORT BERR TIMER KBD  MS    CFLT CBSY
	 *		  o     o    o     x    o    o     x    x
	 *	INTEN1:  BEEP SCC  LANCE DMA  SLOT1 SLOT3 EXT1 EXT3
	 *		  x     o    o     o    o    o     x    x
	 */

	*(char*)INTEN0 = (char) INTEN0_PERR|INTEN0_ABORT|INTEN0_BERR|
				INTEN0_KBDINT|INTEN0_MSINT;

	*(char*)INTEN1 = (char) INTEN1_SCC|INTEN1_LANCE|INTEN1_DMA|
				INTEN1_SLOT1|INTEN1_SLOT3;

	spl0();		/* safe to turn interrupts on now */
}

/*
 * Convert an ASCII string into an integer.
 */
int
atoi(s)
	char *s;
{
	int c;
	unsigned base = 10, d;
	int neg = 0, val = 0;

	if (s == 0 || (c = *s++) == 0)
		goto out;

	/* skip spaces if any */
	while (c == ' ' || c == '\t')
		c = *s++;

	/* parse sign, allow more than one (compat) */
	while (c == '-') {
		neg = !neg;
		c = *s++;
	}

	/* parse base specification, if any */
	if (c == '0') {
		c = *s++;
		switch (c) {
		case 'X':
		case 'x':
			base = 16;
			break;
		case 'B':
		case 'b':
			base = 2;
			break;
		default:
			base = 8;
			break;
		}
	}

	/* parse number proper */
	for (;;) {
		if (c >= '0' && c <= '9')
			d = c - '0';
		else if (c >= 'a' && c <= 'z')
			d = c - 'a' + 10;
		else if (c >= 'A' && c <= 'Z')
			d = c - 'A' + 10;
		else
			break;
		val *= base;
		val += d;
		c = *s++;
	}
	if (neg)
		val = -val;
out:
	return val;	
}

#ifdef CPU_SINGLE
/*
 * small ring buffers for keyboard/mouse
 */
struct ring_buf {
	u_char head;
	u_char tail;
	u_char count;
	u_char buf[13];
} ring_buf[2];

xputc(c, chan)
	u_char c;
	int chan;
{
	register struct ring_buf *p = &ring_buf[chan];
	int s = splhigh();

	if (p->count >= sizeof (p->buf)) {
		(void) splx(s);
		return (-1);
	}
	p->buf[p->head] = c;
	if (++p->head >= sizeof (p->buf))
		p->head = 0;
	p->count++;
	(void) splx(s);
	return (c);
}

xgetc(chan)
	int chan;
{
	register struct ring_buf *p = &ring_buf[chan];
	int c;
	int s = splhigh();

	if (p->count == 0) {
		(void) splx(s);
		return (-1);
	}
	c = p->buf[p->tail];
	if (++p->tail >= sizeof (p->buf))
		p->tail = 0;
	p->count--;
	(void) splx(s);
	return (c);
}
#endif /* CPU_SINGLE */
D 8

_delay(time)
	register int time;
{
	extern int cpuspeed;

	time *= cpuspeed;
	while(time--)
		;
}
E 8
E 1
