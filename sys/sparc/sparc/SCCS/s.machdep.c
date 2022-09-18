h11160
s 00005/00000/00843
d D 8.8 95/05/09 12:11:49 mckusick 14 13
c put in request to unmount all filesystems when rebooting
e
s 00001/00001/00842
d D 8.7 95/04/03 09:05:19 mckusick 13 12
c lint
e
s 00001/00002/00842
d D 8.6 94/01/14 10:06:05 bostic 12 11
c The test for rootfs (now mountlist) is to avoid panic'ing in sync().
c Now that rootfs is not special, it should not be needed anymore.  You
c never saw this on HP300s because there, *(foo *)NULL succeeds in the
c kernel....; From: Chris Torek <torek@BSDI.COM>
e
s 00002/00001/00842
d D 8.5 94/01/13 14:42:51 bostic 11 10
c rootfs is gone, use mountlist instead
e
s 00001/00001/00842
d D 8.4 94/01/12 14:22:10 hibler 10 9
c entries_pageable set TRUE for buffer map (set vm_map.c change).
e
s 00004/00002/00839
d D 8.3 93/10/30 22:33:20 torek 9 8
c work around ss1+ hardware bug by moving cache enable to after autoconfig
e
s 00002/00008/00839
d D 8.2 93/09/30 15:41:38 torek 8 7
c 1.42: move cache enable into cpu configuration to save one output line and
c to make booting go a bit faster.
e
s 00002/00002/00845
d D 8.1 93/06/11 15:17:02 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00026/00001/00821
d D 7.6 93/05/26 21:41:07 torek 6 5
c 1.41: add cpu_sysctl stub
e
s 00007/00010/00815
d D 7.5 93/04/20 23:34:29 torek 5 4
c update from elf
e
s 00027/00027/00798
d D 7.4 92/10/11 12:57:20 bostic 4 3
c make kernel includes standard
e
s 00013/00006/00812
d D 7.3 92/08/10 14:59:20 torek 3 2
c need to thread the signal stack back to the previous stack, for
c gdb and for _longjmp
e
s 00005/00000/00813
d D 7.2 92/07/21 16:54:35 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00813/00000/00000
d D 7.1 92/07/13 00:44:39 torek 1 0
c date and time created 92/07/13 00:44:39 by torek
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 5
 *	California, Lawrence Berkeley Laboratories.
E 5
I 5
 *	California, Lawrence Berkeley Laboratory.
E 5
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: machdep.c,v 1.32 92/07/13 01:41:14 torek Exp $
E 3
I 3
D 5
 * from: $Header: machdep.c,v 1.33 92/08/05 04:20:03 torek Exp $
E 5
I 5
D 6
 * from: $Header: machdep.c,v 1.40 93/04/20 11:16:12 torek Exp $
E 6
I 6
D 8
 * from: $Header: machdep.c,v 1.41 93/05/27 04:39:05 torek Exp $
E 8
I 8
D 9
 * from: $Header: machdep.c,v 1.42 93/09/29 05:40:34 torek Exp $
E 9
I 9
 * from: $Header: machdep.c,v 1.44 93/10/31 05:28:36 torek Exp $
E 9
E 8
E 6
E 5
E 3
 */

D 4
#include "param.h"
#include "proc.h"
#include "user.h"
#include "map.h"
#include "buf.h"
#include "device.h"
#include "reboot.h"
#include "systm.h"
#include "conf.h"
#include "file.h"
#include "clist.h"
#include "callout.h"
#include "malloc.h"
#include "mbuf.h"
#include "mount.h"
#include "msgbuf.h"
E 4
I 4
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/map.h>
#include <sys/buf.h>
#include <sys/device.h>
#include <sys/reboot.h>
#include <sys/systm.h>
#include <sys/conf.h>
#include <sys/file.h>
#include <sys/clist.h>
#include <sys/callout.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/mount.h>
#include <sys/msgbuf.h>
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
#include "exec.h"
E 4
I 4
#include <sys/exec.h>
I 6
#include <sys/sysctl.h>
E 6
E 4

D 4
#include "machine/autoconf.h"
#include "machine/frame.h"
#include "machine/cpu.h"
E 4
I 4
#include <machine/autoconf.h>
#include <machine/frame.h>
#include <machine/cpu.h>
E 4

D 4
#include "vm/vm_kern.h"
#include "vm/vm_page.h"
E 4
I 4
#include <vm/vm_kern.h>
#include <vm/vm_page.h>
E 4

D 4
#include "asm.h"
#include "cache.h"
#include "vaddrs.h"
E 4
I 4
#include <sparc/sparc/asm.h>
#include <sparc/sparc/cache.h>
#include <sparc/sparc/vaddrs.h>
E 4

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

int	physmem;

extern struct msgbuf msgbuf;
struct	msgbuf *msgbufp = &msgbuf;
int	msgbufmapped = 1;	/* message buffer is always mapped */

/*
 * safepri is a safe priority for sleep to set for a spin-wait
 * during autoconfiguration or after a panic.
 */
int   safepri = 0;

caddr_t allocsys();

/*
 * Machine-dependent startup code
 */
cpu_startup()
{
	register unsigned i;
	register caddr_t v;
	register int sz;
	int base, residual;
#ifdef DEBUG
	extern int pmapdebug;
	int opmapdebug = pmapdebug;
#endif
	vm_offset_t minaddr, maxaddr;
	vm_size_t size;

#ifdef DEBUG
	pmapdebug = 0;
#endif

	/*
	 * Good {morning,afternoon,evening,night}.
	 */
	printf(version);
	/*identifycpu();*/
	physmem = btoc(avail_end);
	printf("real mem = %d\n", avail_end);

	/*
	 * Find out how much space we need, allocate it,
	 * and then give everything true virtual addresses.
	 */
	sz = (int)allocsys((caddr_t)0);
	if ((v = (caddr_t)kmem_alloc(kernel_map, round_page(sz))) == 0)
		panic("startup: no room for tables");
	if (allocsys(v) - v != sz)
		panic("startup: table size inconsistency");

	/*
	 * Now allocate buffers proper.  They are different than the above
	 * in that they usually occupy more virtual memory than physical.
	 */
	size = MAXBSIZE * nbuf;
	buffer_map = kmem_suballoc(kernel_map, (vm_offset_t *)&buffers,
D 10
	    &maxaddr, size, FALSE);
E 10
I 10
	    &maxaddr, size, TRUE);
E 10
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
	 * Allocate a map for physio.  Others use a submap of the kernel
	 * map, but we want one completely separate, even though it uses
	 * the same pmap.
	 */
	phys_map = vm_map_create(kernel_pmap, DVMA_BASE, DVMA_END, 1);
	if (phys_map == NULL)
		panic("unable to create DVMA map");

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
	 * Set up buffers, so they can be used to read disk labels.
	 */
	bufinit();

	/*
D 8
	 * Configure the system.
E 8
I 8
D 9
	 * Configure the system.  The cpu code will turn on the cache.
E 9
I 9
	 * Configure the system, then turn on the cache.  Should be able
	 * to do this earlier, but then esp.c fails on SS1+ boxes (??).
E 9
E 8
	 */
	configure();
I 9
	cache_enable();
E 9
D 8

	/*
	 * Turn on the cache (do after configuration due to a bug in
	 * some versions of the SPARC chips -- this info from Gilmore).
	 */
	cache_enable();
E 8
}

/*
 * Allocate space for system data structures.  We are given
 * a starting virtual address and we return a final virtual
 * address; along the way we set each data structure pointer.
 *
 * You call allocsys() with 0 to find out how much space we want,
 * allocate that much and fill it with zeroes, and then call
 * allocsys() again with the correct base virtual address.
 */
caddr_t
allocsys(v)
	register caddr_t v;
{

#define	valloc(name, type, num) \
	    v = (caddr_t)(((name) = (type *)v) + (num))
	valloc(cfree, struct cblock, nclist);
	valloc(callout, struct callout, ncallout);
	valloc(swapmap, struct map, nswapmap = maxproc * 2);
#ifdef SYSVSHM
	valloc(shmsegs, struct shmid_ds, shminfo.shmmni);
#endif
	
	/*
	 * Determine how many buffers to allocate (enough to
	 * hold 5% of total physical memory, but at least 16).
	 * Allocate 1/2 as many swap buffer headers as file i/o buffers.
	 */
	if (bufpages == 0)
		bufpages = (physmem / 20) / CLSIZE;
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
	return (v);
}

/*
 * Set up registers on exec.
 *
 * XXX this entire mess must be fixed
 */
/* ARGSUSED */
setregs(p, entry, retval)
	register struct proc *p;
	u_long entry;
	int retval[2];
{
	register struct trapframe *tf = p->p_md.md_tf;
	register struct fpstate *fs;
	register int psr, sp;

	/*
	 * The syscall will ``return'' to npc or %g7 or %g2; set them all.
	 * Set the rest of the registers to 0 except for %o6 (stack pointer,
	 * built in exec()) and psr (retain CWP and PSR_S bits).
	 */
	psr = tf->tf_psr & (PSR_S | PSR_CWP);
	sp = tf->tf_out[6];
	if ((fs = p->p_md.md_fpstate) != NULL) {
		/*
		 * We hold an FPU state.  If we own *the* FPU chip state
		 * we must get rid of it, and the only way to do that is
		 * to save it.  In any case, get rid of our FPU state.
		 */
		if (p == fpproc) {
			savefpstate(fs);
			fpproc = NULL;
		}
		free((void *)fs, M_SUBPROC);
		p->p_md.md_fpstate = NULL;
	}
	bzero((caddr_t)tf, sizeof *tf);
	tf->tf_psr = psr;
	tf->tf_global[2] = tf->tf_global[7] = tf->tf_npc = entry & ~3;
	tf->tf_out[6] = sp;
	retval[1] = 0;
}

#ifdef DEBUG
int sigdebug = 0;
int sigpid = 0;
#define SDB_FOLLOW	0x01
#define SDB_KSTACK	0x02
#define SDB_FPSTATE	0x04
#endif

struct sigframe {
	int	sf_signo;		/* signal number */
	int	sf_code;		/* code */
#ifdef COMPAT_SUNOS
	struct	sigcontext *sf_scp;	/* points to user addr of sigcontext */
#else
	int	sf_xxx;			/* placeholder */
#endif
	int	sf_addr;		/* SunOS compat, always 0 for now */
	struct	sigcontext sf_sc;	/* actual sigcontext */
};
I 6

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

	/* all sysctl names are this level are terminal */
	if (namelen != 1)
		return (ENOTDIR);	/* overloaded */

	switch (name[0]) {
	default:
		return (EOPNOTSUPP);
	}
	/* NOTREACHED */
}
E 6

/*
 * Send an interrupt to process.
 */
void
sendsig(catcher, sig, mask, code)
	sig_t catcher;
	int sig, mask;
D 13
	unsigned code;
E 13
I 13
	u_long code;
E 13
{
	register struct proc *p = curproc;
	register struct sigacts *psp = p->p_sigacts;
	register struct sigframe *fp;
	register struct trapframe *tf;
D 3
	register int addr, oonstack;
E 3
I 3
	register int addr, oonstack, oldsp, newsp;
E 3
	struct sigframe sf;
	extern char sigcode[], esigcode[];
#define	szsigcode	(esigcode - sigcode)

	tf = p->p_md.md_tf;
I 3
	oldsp = tf->tf_out[6];
E 3
	oonstack = psp->ps_sigstk.ss_flags & SA_ONSTACK;
	/*
	 * Compute new user stack addresses, subtract off
	 * one signal frame, and align.
	 */
	if ((psp->ps_flags & SAS_ALTSTACK) && !oonstack &&
	    (psp->ps_sigonstack & sigmask(sig))) {
		fp = (struct sigframe *)(psp->ps_sigstk.ss_base +
					 psp->ps_sigstk.ss_size);
		psp->ps_sigstk.ss_flags |= SA_ONSTACK;
	} else
D 3
		fp = (struct sigframe *)tf->tf_out[6];
E 3
I 3
		fp = (struct sigframe *)oldsp;
E 3
	fp = (struct sigframe *)((int)(fp - 1) & ~7);

#ifdef DEBUG
	if ((sigdebug & SDB_KSTACK) && p->p_pid == sigpid)
		printf("sendsig: %s[%d] sig %d newusp %x scp %x\n",
		    p->p_comm, p->p_pid, sig, fp, &fp->sf_sc);
#endif
	/* 
	 * Now set up the signal frame.  We build it in kernel space
	 * and then copy it out.  We probably ought to just build it
	 * directly in user space....
	 */
	sf.sf_signo = sig;
	sf.sf_code = code;
#ifdef COMPAT_SUNOS
	sf.sf_scp = &fp->sf_sc;
#endif
	sf.sf_addr = 0;			/* XXX */

	/*
	 * Build the signal context to be used by sigreturn.
	 */
	sf.sf_sc.sc_onstack = oonstack;
	sf.sf_sc.sc_mask = mask;
D 3
	sf.sf_sc.sc_sp = tf->tf_out[6];
E 3
I 3
	sf.sf_sc.sc_sp = oldsp;
E 3
	sf.sf_sc.sc_pc = tf->tf_pc;
	sf.sf_sc.sc_npc = tf->tf_npc;
	sf.sf_sc.sc_psr = tf->tf_psr;
	sf.sf_sc.sc_g1 = tf->tf_global[1];
	sf.sf_sc.sc_o0 = tf->tf_out[0];

	/*
	 * Put the stack in a consistent state before we whack away
	 * at it.  Note that write_user_windows may just dump the
	 * registers into the pcb; we need them in the process's memory.
I 3
	 * We also need to make sure that when we start the signal handler,
	 * its %i6 (%fp), which is loaded from the newly allocated stack area,
	 * joins seamlessly with the frame it was in when the signal occurred,
	 * so that the debugger and _longjmp code can back up through it.
E 3
	 */
I 3
	newsp = (int)fp - sizeof(struct rwindow);
E 3
	write_user_windows();
D 3
	if (rwindow_save(p) || copyout((caddr_t)&sf, (caddr_t)fp, sizeof sf)) {
E 3
I 3
	if (rwindow_save(p) || copyout((caddr_t)&sf, (caddr_t)fp, sizeof sf) ||
	    suword(&((struct rwindow *)newsp)->rw_in[6], oldsp)) {
E 3
		/*
		 * Process has trashed its stack; give it an illegal
		 * instruction to halt it in its tracks.
		 */
#ifdef DEBUG
		if ((sigdebug & SDB_KSTACK) && p->p_pid == sigpid)
			printf("sendsig: window save or copyout error\n");
#endif
		sigexit(p, SIGILL);
		/* NOTREACHED */
	}
#ifdef DEBUG
	if (sigdebug & SDB_FOLLOW)
		printf("sendsig: %s[%d] sig %d scp %x\n",
		       p->p_comm, p->p_pid, sig, &fp->sf_sc);
#endif
	/*
	 * Arrange to continue execution at the code copied out in exec().
	 * It needs the function to call in %g1, and a new stack pointer.
	 */
#ifdef COMPAT_SUNOS
	if (psp->ps_usertramp & sigmask(sig)) {
		addr = (int)catcher;	/* user does his own trampolining */
	} else
#endif
	{
		addr = USRSTACK - sizeof(struct ps_strings) - szsigcode;
		tf->tf_global[1] = (int)catcher;
	}
	tf->tf_pc = addr;
	tf->tf_npc = addr + 4;
D 3
	tf->tf_out[6] = (int)fp - sizeof(struct rwindow);
E 3
I 3
	tf->tf_out[6] = newsp;
E 3
#ifdef DEBUG
	if ((sigdebug & SDB_KSTACK) && p->p_pid == sigpid)
		printf("sendsig: about to return to catcher\n");
#endif
}

/*
 * System call to cleanup state after a signal
 * has been taken.  Reset signal mask and
 * stack state from context left by sendsig (above),
 * and return to the given trap frame (if there is one).
 * Check carefully to make sure that the user has not
 * modified the state to gain improper privileges or to cause
 * a machine fault.
 */
/* ARGSUSED */
struct sigreturn_args {
	struct sigcontext *scp;
};
sigreturn(p, uap, retval)
	register struct proc *p;
	struct sigreturn_args *uap;
	int *retval;
{
	register struct sigcontext *scp;
	register struct trapframe *tf;

	/* First ensure consistent stack state (see sendsig). */
	write_user_windows();
	if (rwindow_save(p))
		sigexit(p, SIGILL);
#ifdef DEBUG
	if (sigdebug & SDB_FOLLOW)
		printf("sigreturn: %s[%d], scp %x\n",
		    p->p_comm, p->p_pid, uap->scp);
#endif
	scp = uap->scp;
	if ((int)scp & 3 || useracc((caddr_t)scp, sizeof *scp, B_WRITE) == 0)
		return (EINVAL);
	tf = p->p_md.md_tf;
	/*
	 * Only the icc bits in the psr are used, so it need not be
	 * verified.  pc and npc must be multiples of 4.  This is all
	 * that is required; if it holds, just do it.
	 */
	if (((scp->sc_pc | scp->sc_npc) & 3) != 0)
		return (EINVAL);
	/* take only psr ICC field */
	tf->tf_psr = (tf->tf_psr & ~PSR_ICC) | (scp->sc_psr & PSR_ICC);
	tf->tf_pc = scp->sc_pc;
	tf->tf_npc = scp->sc_npc;
	tf->tf_global[1] = scp->sc_g1;
	tf->tf_out[0] = scp->sc_o0;
	tf->tf_out[6] = scp->sc_sp;
	if (scp->sc_onstack & 1)
		p->p_sigacts->ps_sigstk.ss_flags |= SA_ONSTACK;
	else
		p->p_sigacts->ps_sigstk.ss_flags &= ~SA_ONSTACK;
	p->p_sigmask = scp->sc_mask & ~sigcantmask;
	return (EJUSTRETURN);
}

int	waittime = -1;

boot(howto)
	register int howto;
{
	int i;
	static char str[4];	/* room for "-sd\0" */
	extern volatile void romhalt(void);
	extern volatile void romboot(char *);

	fb_unblank();
	boothowto = howto;
D 11
	if ((howto & RB_NOSYNC) == 0 && waittime < 0 && rootfs) {
E 11
I 11
D 12
	if ((howto & RB_NOSYNC) == 0 &&
	    waittime < 0 && mountlist.tqh_first != NULL) {
E 12
I 12
	if ((howto & RB_NOSYNC) == 0 && waittime < 0) {
E 12
E 11
		register struct buf *bp;
		int iter, nbusy;
#if 1
		extern struct proc proc0;

		/* protect against curproc->p_stats.foo refs in sync()   XXX */
		if (curproc == NULL)
			curproc = &proc0;
#endif
		waittime = 0;
		(void) spl0();
		printf("syncing disks... ");
		/*
		 * Release vnodes held by texts before sync.
		 */
		if (panicstr == 0)
			vnode_pager_umount((struct mount *)NULL);
D 5
#include "fd.h"
#if NFD > 0
		fdshutdown();
#endif
		sync((struct proc *)NULL, (void *)NULL, (int *)NULL);
E 5
I 5
		sync(&proc0, (void *)NULL, (int *)NULL);
I 14
		/*
		 * Unmount filesystems
		 */
		if (panicstr == 0)
			vfs_unmountall();
E 14
E 5

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
	(void) splhigh();		/* ??? */
	if (howto & RB_HALT) {
		printf("halted\n\n");
		romhalt();
	}
	if (howto & RB_DUMP)
		dumpsys();
	printf("rebooting\n\n");
	i = 1;
	if (howto & RB_SINGLE)
		str[i++] = 's';
	if (howto & RB_KDB)
		str[i++] = 'd';
	if (i > 1) {
		str[0] = '-';
		str[i] = 0;
	} else
		str[0] = 0;
	romboot(str);
	/*NOTREACHED*/
}

int	dumpmag = 0x8fca0101;	/* magic number for savecore */
int	dumpsize = 0;		/* also for savecore */
long	dumplo = 0;

dumpconf()
{
	int nblks;

	dumpsize = physmem;
#define DUMPMMU
#ifdef DUMPMMU
#define NPMEG 128
	/*
	 * savecore views the image in units of pages (i.e., dumpsize is in
	 * pages) so we round the two mmu entities into page-sized chunks.
	 * The PMEGs (32kB) and the segment table (512 bytes plus padding)
	 * are appending to the end of the crash dump.
	 */
	dumpsize += btoc(sizeof(((struct kpmap *)0)->pm_rsegmap)) +
		btoc(NPMEG * NPTESG * sizeof(int));
#endif
	if (dumpdev != NODEV && bdevsw[major(dumpdev)].d_psize) {
		nblks = (*bdevsw[major(dumpdev)].d_psize)(dumpdev);
		/*
		 * Don't dump on the first CLBYTES (why CLBYTES?)
		 * in case the dump device includes a disk label.
		 */
		if (dumplo < btodb(CLBYTES))
			dumplo = btodb(CLBYTES);

		/*
		 * If dumpsize is too big for the partition, truncate it.
		 * Otherwise, put the dump at the end of the partition
		 * by making dumplo as large as possible.
		 */
		if (dumpsize > btoc(dbtob(nblks - dumplo)))
			dumpsize = btoc(dbtob(nblks - dumplo));
		else if (dumplo + ctod(dumpsize) > nblks)
			dumplo = nblks - ctod(dumpsize);
	}
}

#ifdef DUMPMMU
/* XXX */
D 4
#include "ctlreg.h"
E 4
I 4
D 5
#include <sparc/sparc/ctlreg.h>
E 5
I 5
#include <machine/ctlreg.h>
E 5
E 4
#define	getpte(va)		lda(va, ASI_PTE)
#define	setsegmap(va, pmeg)	stba(va, ASI_SEGMAP, pmeg)

/*
 * Write the mmu contents to the dump device.
 * This gets appended to the end of a crash dump since
 * there is no in-core copy of kernel memory mappings.
 */
int
dumpmmu(blkno)
	register daddr_t blkno;
{
	register int (*dump)(/*dev_t, daddr_t, caddr_t, int*/);
	register int pmeg;
	register int addr;	/* unused kernel virtual address */
	register int i;
	register int *pte, *ptend;
	register int error;
	register struct kpmap *kpmap = &kernel_pmap_store;
	int buffer[dbtob(1) / sizeof(int)];
	extern int seginval;	/* from pmap.c */
	

	dump = bdevsw[major(dumpdev)].d_dump;

	/*
	 * dump page table entries
	 *
	 * We dump each pmeg in order (by segment number).  Since the MMU
	 * automatically maps the given virtual segment to a pmeg we must
	 * iterate over the segments by incrementing an unused segment slot
	 * in the MMU.  This fixed segment number is used in the virtual
	 * address argument to getpte().
	 */

	/* First find an unused virtual segment. */
	i = NKSEG;
	while (kpmap->pm_rsegmap[--i] != seginval)
		if (i <= 0)
			return (-1);
	/*
	 * Compute the base address corresponding to the unused segment.
	 * Note that the kernel segments start after all the user segments
	 * so we must account for this offset.
	 */
	addr = VSTOVA(i + NUSEG);
	/*
	 * Go through the pmegs and dump each one.
	 */
	pte = buffer;
	ptend = &buffer[sizeof(buffer) / sizeof(buffer[0])];
	for (pmeg = 0; pmeg < NPMEG; ++pmeg) {
		register int va = addr;

		setsegmap(addr, pmeg);
		i = NPTESG;
		do {
			*pte++ = getpte(va);
			if (pte >= ptend) {
				/*
				 * Note that we'll dump the last block
				 * the last time through the loops because
				 * all the PMEGs occupy 32KB which is 
				 * a multiple of the block size.
				 */
				error = (*dump)(dumpdev, blkno,
						(caddr_t)buffer,
						dbtob(1));
				if (error != 0)
					return (error);
				++blkno;
				pte = buffer;
			}
			va += NBPG;
		} while (--i > 0);
	}
	setsegmap(addr, seginval);

	/*
	 * dump (512 byte) segment map 
	 * XXX assume it's a multiple of the block size
	 */
	error = (*dump)(dumpdev, blkno, (caddr_t)kpmap->pm_rsegmap,
D 5
			sizeof(kpmap->pm_rsegmap), 0);
E 5
I 5
			sizeof(kpmap->pm_rsegmap));
E 5
	return (error);
}
#endif

#define	BYTES_PER_DUMP	(32 * 1024)	/* must be a multiple of pagesize */
static vm_offset_t dumpspace;

caddr_t
reserve_dumppages(p)
	caddr_t p;
{

	dumpspace = (vm_offset_t)p;
	return (p + BYTES_PER_DUMP);
}

/*
 * Write a crash dump.
 */
dumpsys()
{
	register unsigned bytes, i, n;
	register int maddr, psize;
	register daddr_t blkno;
	register int (*dump)(/*dev_t, daddr_t, caddr_t, int, int*/);
	int error = 0;

	if (dumpdev == NODEV)
		return;
	/* copy registers to memory */
	snapshot(cpcb);
	/*
	 * For dumps during autoconfiguration,
	 * if dump device has already configured...
	 */
	if (dumpsize == 0)
		dumpconf();
	if (dumplo < 0)
		return;
	printf("\ndumping to dev %x, offset %d\n", dumpdev, dumplo);

	psize = (*bdevsw[major(dumpdev)].d_psize)(dumpdev);
	printf("dump ");
	if (psize == -1) {
		printf("area unavailable\n");
		return;
	}
	bytes = physmem << PGSHIFT;
	maddr = 0;
	blkno = dumplo;
	dump = bdevsw[major(dumpdev)].d_dump;
	for (i = 0; i < bytes; i += n) {
		n = bytes - i;
		if (n > BYTES_PER_DUMP)
			 n = BYTES_PER_DUMP;
#ifdef DEBUG
		/* print out how many MBs we have dumped */
		if (i && (i % (1024*1024)) == 0)
			printf("%d ", i / (1024*1024));
#endif
		(void) pmap_map(dumpspace, maddr, maddr + n, VM_PROT_READ);
		error = (*dump)(dumpdev, blkno, (caddr_t)dumpspace, (int)n);
		if (error)
			break;
		maddr += n;
		blkno += btodb(n);
	}
#ifdef DUMPMMU
	if (!error)
		error = dumpmmu(blkno);
#endif
	switch (error) {

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

	case 0:
		printf("succeeded\n");
		break;

	default:
		printf("error %d\n", error);
		break;
	}
}

/*
 * Map an I/O device given physical address and size in bytes, e.g.,
 *
 *	mydev = (struct mydev *)mapdev(myioaddr, 0, sizeof(struct mydev));
 *
 * See also machine/autoconf.h.
 */
void *
mapdev(phys, virt, size)
	register void *phys;
	register int virt, size;
{
	register vm_offset_t v;
	register void *ret;
	static vm_offset_t iobase = IODEV_BASE;

	size = round_page(size);
	if (virt)
D 5
		v = virt;
E 5
I 5
		v = trunc_page(virt);
E 5
	else {
		v = iobase;
		iobase += size;
		if (iobase > IODEV_END)	/* unlikely */
			panic("mapiodev");
	}
	ret = (void *)v;
I 5
	phys = (void *)trunc_page(phys);
E 5
	do {
		pmap_enter(kernel_pmap, v,
		    (vm_offset_t)phys | PMAP_OBIO | PMAP_NC,
		    VM_PROT_READ | VM_PROT_WRITE, 1);
		v += PAGE_SIZE;
		phys += PAGE_SIZE;
	} while ((size -= PAGE_SIZE) > 0);
	return (ret);
}
E 1
