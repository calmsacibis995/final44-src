/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	machdep.c,v $
 * Revision 1.11.1.13  91/07/15  00:15:53  rvb
 * 	Flush dump code -- mach doesn't dump
 * 	[91/06/27            mg32]
 * 
 * Revision 1.11.1.12  91/05/03  10:57:29  rvb
 * 	Reapply boot() changes to sync with X135:
 * 		Conditionalized changes since non-VFS case doesn't have
 * 		dounmount().
 * 		[91/04/11            berman]
 * 		Added some code in boot() to take care of unmounting all the
 * 		filesystems when shutting down.
 * 		[91/02/15            berman]
 * 
 * Revision 1.11.1.11  91/03/28  08:44:14  rvb
 * 	For X134
 * 		Kill EXL conditionals
 * 			Replace should_exit with processor shutdown logic.
 * 			New calling sequence for vm_map_pageable.
 * 			above to from [89/02/02            dlb]
 * 	Add aha support.
 * 	[91/03/20            rvb]
 * 
 * Revision 1.11.1.10  90/05/22  08:19:51  rvb
 * 	C version of ovbcopy.
 * 	[90/05/21            rvb]
 * 
 * Revision 1.11.1.9  90/04/24  08:09:47  rvb
 * 	Debugging printout for T5200/reboot problem.
 * 
 * Revision 1.11.1.8  90/04/15  11:45:55  rvb
 * 	maptss should use sizeof struct tss vs sizeof struct tss - 1
 * 	[90/04/10            rvb]
 * 
 * Revision 1.11.1.7  90/03/07  13:27:04  rvb
 * 		Fix CMU log entries.	[kupfer]
 * 		I386e- merge.		[kupfer]
 * 	Make U_ADDRESS on by default.
 * 	[90/03/01            rvb]
 * 
 * Revision 1.11.1.6  90/02/28  15:48:07  rvb
 * 	ORC=>M380 [kupfer]
 * 	engineer the i386_coproc_hang to run on timeout()
 * 	started in start_init [rvb]
 * 
 * Revision 1.11.1.5  90/02/01  13:36:18  rvb
 * 	You don't need arp's if NINET == 0
 * 	[90/01/31            rvb]
 * 
 * Revision 1.11.1.4  90/01/02  13:49:10  rvb
 * 	Flush MACH_TIME, dorti, tbiscl
 * 	Move copystr, copyinstr and copyoutstr to copy.c, anticipating
 * 	rewrite.
 * 
 * Revision 1.11.1.3  89/12/21  17:13:51  rvb
 * 	Revision 1.16  89/11/16  16:24:20  kupfer
 * 	Add workaround for Errata 17 for B1 step 80386s (coprocessor
 * 	instruction that spans page boundary).
 * 	Fix physstrat() to make sure address is aligned (for dma io
 * 	m765 and wt)			[lin]
 * 
 * Revision 1.11.1.2  89/11/21  12:45:19  rvb
 * 	NOTE: on the T5200 this optimization is detremental (to getpid())
 * 	but generally it is a win, so it is conditonal on NO_U_ADDRESS
 * 	Rather than have "u" expand to current_thread()->u_address, have
 * 	it expand to the constant U_ADDRESS which is updated by load_context
 * 	when the thread changes.  If "u" is defined then user.h won't define
 * 	it.
 * 	[88/01/25            rvb]
 * 
 * Revision 1.11.1.1  89/10/22  11:31:03  rvb
 * 	Revision 1.15  89/10/11  12:33:34  lance
 * 	removed spurious `register' declaration for global structure.
 * 
 * Revision 1.11  89/09/25  12:25:03  rvb
 * 	seg_desc -> fakedesc
 * 	[89/09/23            rvb]
 * 
 * Revision 1.10  89/09/20  17:26:33  rvb
 * 	Olivetti Cache Disable code
 * 	[89/09/20            rvb]
 * 
 * Revision 1.9  89/09/11  08:01:11  rvb
 * 	Apportion number of buffers bases on amount of memory available.
 * 
 * 
 * Revision 1.8  89/09/09  15:19:53  rvb
 * 	Print out vm_page_free_count during bootstrap.
 * 	Make copyXstr return ENOENT at overrun.
 * 	[89/09/07            rvb]
 * 
 * Revision 1.7  89/07/17  10:38:04  rvb
 * 	Olivetti Changes to X79 upto 5/12/89:
 * 		Signals
 * 		& Physio now maps user pages to kernel space for AT disk transactions.
 * 	[89/07/11            rvb]
 * 
 * Revision 1.6  89/04/05  12:58:45  rvb
 * 	X78: rfs moved and mach_time when away.
 * 	[89/03/24            rvb]
 * 
 * 	Forward declaration of should_exit() as boolean_t.
 * 	[89/03/21            rvb]
 * 
 * Revision 1.5  89/03/09  20:03:04  rpd
 * 	More cleanup.
 * 
 * Revision 1.4  89/02/26  12:32:25  gm0w
 * 	Changes for cleanup.
 * 
 * 16-Feb-89  Robert Baron (rvb) at Carnegie-Mellon University
 *	doadump has been flushed forever.  And halt becomes effectively
 *	a reboot since I don't believe there is a prom monitor that it
 *	would be interresting to return to  (and I am getting tired of
 *	sticking the spoon into the reset button).
 *
 * 31-Dec-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Derived from MACH2.0 vax release.
 *
 * 11-Dec-87  Stephen Schwab (schwab) at Carnegie-Mellon University
 *	For 650, use ssc timer 0 vs uVax clock (in microtime)(
 *
 */
 
#ifdef	M380
#define COPROC_SPANPAGE_BUG	1
#endif	M380

#include <cpus.h>
#include <aha.h>
#include <confdep.h>
#include <cputypes.h>

#include <mach_kdb.h>
#include <mach_rfs.h>
#include <mach_load.h>
#include <mach_directory.h>
#include <quota.h>
 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)machdep.c	7.1 (Berkeley) 6/5/86
 */

#include <i386/reg.h>
#include <i386/psl.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/kernel.h>
#include <sys/map.h>
#include <sys/vm.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/reboot.h>
#include <sys/conf.h>
#include <sys/inode.h>
#include <sys/file.h>
#include <sys/clist.h>
#include <sys/callout.h>
#include <sys/mbuf.h>
#include <sys/msgbuf.h>
#include <sys/quota.h>
#include <sys/mount.h>
#include <sys/fs.h>
#if	MACH_RFS
#include <rfs/rfs.h>
#endif	MACH_RFS

#include <i386/clock.h>
#include <i386/cpu.h>

#include <kern/thread.h>
#include <kern/lock.h>
#include <vm/vm_kern.h>
#include <mach/vm_param.h>
#include <kern/zalloc.h>
#include <i386/vmparam.h>
struct pte 	*Sysmap;
vm_offset_t	Sysbase;
long		Syssize;

/*
 * Declare these as initialized data so we can patch them.
 */
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
int	show_space = 0;

#ifdef	AT386
#define PHYSBUFS 32
#define PHYSBUFSIZE (2*I386_PGBYTES)
typedef char physbuf_t[PHYSBUFSIZE];
physbuf_t *physbufs;
unsigned long physbufmap;
vm_offset_t kmem_alloc_pageable();
#endif	AT386

int	msgbuf_mapped = FALSE;
vm_map_t	buffer_map;

extern int	loadpt, loadpg;
struct pte	*Mbmap;

/*
 * Machine-dependent startup code
 */
startup(firstaddr)
	caddr_t	firstaddr;
{
	register unsigned int i;
	register caddr_t v;
	vm_size_t	size;
	kern_return_t	ret;
	vm_offset_t	trash_offset;
	int		base, residual;
	vm_offset_t	tmp_addr;
	extern int	vm_page_free_count;

#ifdef	MACH
	/* XXX - need to handle message buffer */
#else	MACH
	/*
	 * Initialize error message buffer (at end of core).
	 */
	maxmem -= btoc(sizeof (struct msgbuf));
	pte = msgbufmap;
	for (i = 0; i < btoc(sizeof (struct msgbuf)); i++)
#if	MACH_LOAD
		*(int *)pte++ = PG_V | PG_KW | (loadpg + maxmem + i) ;
#else	MACH_LOAD
		*(int *)pte++ = PG_V | PG_KW | (maxmem + i);
#endif	MACH_LOAD
	mtpr(TBIA, 0);
	msgbuf_mapped = TRUE;
#endif	MACH

	/*
	 * Good {morning,afternoon,evening,night}.
	 */
	panic_init();

	/*
	 *	The following constants are set to keep a bunch
	 *	of Unix code happy, all uses of these should eventually
	 *	be fixed.
	 */
	Sysmap = (struct pte *) vm_map_pmap(kernel_map)->cr3;	/* XXX */
	Sysbase = (vm_offset_t) VM_MIN_KERNEL_ADDRESS;	/* XXX */
/*	Syssize = mfpr(SLR);				/* XXX */
#if	MACH_KDB
	/*
	 *  Initialize the kernel debugger.  Cause a breakpoint trap to the
	 *  debugger before proceding any further if the proper option bit was
	 *  specified in the boot flags.
	 */
	kdb_init();
#endif	MACH_KDB
	printf(version);
#define MEG	(1024*1024)

	printf("physical memory = %d.%d%d megabytes.  vm_page_free_count = %x\n",
		mem_size/MEG,
		((mem_size%MEG)*10)/MEG,
		((mem_size%(MEG/10))*100)/MEG,
		vm_page_free_count);

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
	 *	Since the virtaul memory system has already been set up,
	 *	we cannot bypass it to allocate memory as the old code
	 *	DOES.  we therefore make two passes over the table
	 *	allocation code.  The first pass merely calculates the
	 *	size needed for the various data structures.  The
	 *	second pass allocates the memory and then sets the
	 *	actual addresses.  The code must not change any of
	 *	the allocated sizes between the two passes.
	 */
	firstaddr = 0;
	for (;;) {
		v = firstaddr;

#define valloc(name, type, num)	\
	(name) = (type *)(v); (v) = (caddr_t)((name)+(num));\
	if (show_space) \
		printf("name = %d(0x%x) bytes @%x, %d cells @ %d bytes\n",\
		 num*sizeof(type), num*sizeof(type), name, num, sizeof (type))
#define valloclim(name, type, num, lim)	\
	(name) = (type *)(v); (v) = (caddr_t)((lim) = ((name)+(num)));\
	if (show_space) \
		printf("name = %d(0x%x) bytes @%x, %d cells @ %d bytes\n",\
		 num*sizeof(type), num*sizeof(type), name, num, sizeof (type))
#if	MACH_RFS
	valloc(rfsProcessTable, struct rfsProcessEntry, nproc);
#endif	MACH_RFS
	valloclim(inode, struct inode, ninode, inodeNINODE);
	valloclim(file, struct file, nfile, fileNFILE);
	valloclim(proc, struct proc, nproc, procNPROC);
	valloc(cfree, struct cblock, nclist);
	valloc(callout, struct callout, ncallout);
#if	MACH_DIRECTORY
#else	MACH_DIRECTORY
	valloc(namecache, struct namecache, nchsize);
#endif	MACH_DIRECTORY
#if	QUOTA
	valloclim(quota, struct quota, nquota, quotaNQUOTA);
	valloclim(dquot, struct dquot, ndquot, dquotNDQUOT);
#endif	QUOTA
#include <inet.h>
#if	NINET > 0
	{
#include <netinet/in.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/if_ether.h>
	extern struct arptab *arptab;
	extern int arptab_size, arptab_bsiz, arptab_nb;
		arptab_size = arptab_bsiz * arptab_nb;
		valloc(arptab, struct arptab, arptab_size);
	}
#endif	NINET > 0	
	/*
	 *	Use 5% of memory for buffers.
	 *	Since these pages are virtual-size pages (larger
	 *	than physical page size), use only one page
	 *	per buffer.
	 */
 	if (bufpages == 0) {
		bufpages = atop(mem_size / 20);
		if (mem_size > 0x300000)
			bufpages += atop(mem_size / 20);
		if (mem_size > 0x800000)
			bufpages += atop(mem_size / 15);
	}
	if (nbuf == 0) {
		if ((nbuf = bufpages) < 16)
			nbuf = 16;
	}
	if (bufpages > nbuf * (MAXBSIZE / page_size))
		bufpages = nbuf * (MAXBSIZE / page_size);
	valloc(buf, struct buf, nbuf);


	/*
	 * Clear space allocated thus far, and make r/w entries
	 * for the space in the kernel map.
	 */
	    if (firstaddr == 0) {
		/*
		 *	Size has been calculated; allocate memory
		 */
		size = (vm_size_t)(v - firstaddr);
		tmp_addr = kmem_alloc(kernel_map, round_page(size));
		if (tmp_addr == 0)
		    panic("startup: no room for tables");
		firstaddr = (caddr_t)tmp_addr;
	    }
	    else {
		/*
		 *	Memory has been allocated.  Make sure that
		 *	table size has not changed.
		 */
		if ((vm_size_t)(v - firstaddr) != size)
		    panic("startup: table size inconsistent");
		break;
	    }
	}

	/*
	 * Now allocate buffers proper.  They are different than the above
	 * in that they usually occupy more virtual memory than physical.
	 */
	v = 0;	/* use the same trick */
	valloc(buffers, char, MAXBSIZE * nbuf);
	base = bufpages / nbuf;
	residual = bufpages % nbuf;
	if (show_space)
		printf("bufpages = %d, nbuf = %d, base = %d, residual = %d\n",
				bufpages, nbuf, base, residual);

	/*
	 *	Allocate virtual memory for buffer pool.
	 */
	size = round_page((vm_size_t)v);
	buffer_map = kmem_suballoc(kernel_map,
					&tmp_addr,
					&trash_offset /* max */,
					size,
					TRUE);
	buffers = (char *)tmp_addr;
	ret = vm_map_find(buffer_map, vm_object_allocate(size), (vm_offset_t) 0,
				&tmp_addr, size, FALSE);
	if (ret != KERN_SUCCESS) {
		panic("startup: unable to allocate buffer pool");
	}

	for (i = 0; i < nbuf; i++) {
		vm_size_t	thisbsize;
		vm_offset_t	curbuf;

		/*
		 * First <residual> buffers get (base+1) physical pages
		 * allocated for them.  The rest get (base) physical pages.
		 *
		 * The rest of each buffer occupies virtual space,
		 * but has no physical memory allocated for it.
		 */

		thisbsize = page_size*(i < residual ? base+1 : base);
		curbuf = (vm_offset_t)buffers + i * MAXBSIZE;
#ifdef	THREAD_EXIT
		vm_map_pageable(buffer_map, curbuf, curbuf+thisbsize, FALSE);
#else	THREAD_EXIT
		vm_map_pageable(buffer_map, curbuf, curbuf+thisbsize,
			VM_PROT_READ|VM_PROT_WRITE);
#endif	THREAD_EXIT
	}

#ifdef	AT386
	physbufs = (physbuf_t *)
	  kmem_alloc_pageable( kernel_map, PHYSBUFS * PHYSBUFSIZE );
	physbufmap = 0;
#endif	AT386

	/*
	 * Initialize callouts
	 */
	callfree = callout;
	for (i = 1; i < ncallout; i++)
		callout[i-1].c_next = &callout[i];

	/*
	 * Initialize memory allocator and swap
	 * and user page table maps.
	 *
	 * THE USER PAGE TABLE MAP IS CALLED ``kernelmap''
	 * WHICH IS A VERY UNDESCRIPTIVE AND INCONSISTENT NAME.
	 */
	{
		register int	nbytes;

		nbytes = ptoa(bufpages);
		printf("using %d buffers containing %d.%d%d megabytes of memory\n",
			nbuf,
			nbytes/MEG,
			((nbytes%MEG)*10)/MEG,
			((nbytes%(MEG/10))*100)/MEG);

		nbytes = ptoa(vm_page_free_count);
		printf("available memory = %d.%d%d megabytes. vm_page_free_count = %x\n",
			nbytes/MEG,
			((nbytes%MEG)*10)/MEG,
			((nbytes%(MEG/10))*100)/MEG,
			vm_page_free_count);
	}

	mb_map = kmem_suballoc(kernel_map,
				(vm_offset_t *) &mbutl,
				(vm_offset_t *) &embutl,
				(vm_size_t) (nmbclusters * CLBYTES),
/*				(vm_size_t) (ptoa(nmbclusters)),*/
				FALSE);
	Mbmap = (struct pte *) pmap_pte(pmap_kernel(), (vm_offset_t)mbutl);

	/*
	 * Set up CPU-specific registers, cache, etc.
	 */
	initcpu();

	/*
	 * Configure the system.
	 */
	configure();
}

#ifdef	PGINPROF
/*
 * Return the difference (in microseconds)
 * between the  current time and a previous
 * time as represented  by the arguments.
 * If there is a pending clock interrupt
 * which has not been serviced due to high
 * ipl, return error code.
 */
vmtime(otime, olbolt, oicr)
	register int otime, olbolt, oicr;
{
	if (mfpr(ICCS)&ICCS_INT)
		return(-1);
	else
		return(((time.tv_sec-otime)*60 + lbolt-olbolt)*16667 + mfpr(ICR)-oicr);
}
#endif	PGINPROF

/*
 * Clear registers on exec
 */
setregs(entry)
	u_long entry;
{
#ifdef	notdef
	register int *rp;

	/* should pass args to init on the stack */
	/* should also fix this code before using it, it's wrong */
	/* wanna clear the scb? */
	for (rp = &u.u_ar0[0]; rp < &u.u_ar0[16];)
		*rp++ = 0;
#endif
	u.u_ar0[EIP] = entry;
}

/*
 * Send an interrupt to process.
 *
 * Stack is set up to allow sigcode stored
 * in u. to call routine, followed by chmk
 * to sigreturn routine below.  After sigreturn
 * resets the signal mask, the stack, the frame 
 * pointer, and the argument pointer, it returns
 * to the user specified pc, psl.
 */

struct sigframe {
	int	(*sf_retadr)();
	int	sf_signum;
	int	sf_code;
	struct	sigcontext *sf_scp;
        struct  sigcontext *sf_scpcopy; /* used when returning */
};
sendsig(p, sig, mask)
	int (*p)(), sig, mask;
{
	struct sigcontext sigcon, *scp;
	struct sigframe frame, *fp;
	int oonstack;

	/* The following kludge detects when we're executing an old binary
	 * that was linked with the original signal implementation. Once the
	 * world is relinked this check and the routines osendsig() and
	 * osigreturn() should be removed and the library code in sigvec()
	 * should be fixed to not set the high order bit.
	 * -- lance & tommy 15-mar-89
	 */
	if (((unsigned long) u.u_sigreturn & 0x80000000) == 0) {
	  osendsig(p, sig, mask);
	  return;
	}

	oonstack = u.u_onstack;
	/*
	 * Allocate and validate space for the signal handler
	 * context. Note that if the stack is in P0 space, the
	 * call to grow() is a nop, and the useracc() check
	 * will fail if the process has not already allocated
	 * the space with a `brk'.
	 */
	if (!u.u_onstack && (u.u_sigonstack & sigmask(sig))) {
		scp = (struct sigcontext *)u.u_sigsp - 1;
		u.u_onstack = 1;
	} else
		scp = (struct sigcontext *)u.u_ar0[UESP] - 1;
	fp = (struct sigframe *)scp - 1;
	if ((int)fp <= USRSTACK - ctob(u.u_ssize)) 
		(void)grow((unsigned)fp);

	if (useracc((caddr_t)fp, sizeof (*fp) + sizeof (*scp), B_WRITE) == 0) {
		/*
		 * Process has trashed its stack; give it an illegal
		 * instruction to halt it in its tracks.
		 */
		u.u_signal[SIGILL] = SIG_DFL;
		sig = sigmask(SIGILL);
		u.u_procp->p_sigignore &= ~sig;
		u.u_procp->p_sigcatch &= ~sig;
		u.u_procp->p_sigmask &= ~sig;
		psignal(u.u_procp, SIGILL);
		return;
	}

	/* 
	 * Build the argument list for the signal handler.
	 */
	frame.sf_signum = sig;
	if (sig == SIGILL || sig == SIGFPE) {
		frame.sf_code = u.u_code;
		u.u_code = 0;
	} else
		frame.sf_code = 0;
	frame.sf_scp = scp;
	/*
	 * Build the stack frame to be used to call sigreturn
	 */
	frame.sf_scpcopy = scp;
	/* KLUDGE KLUDGE KLUDGE (see above) */
	frame.sf_retadr = (int (*)())
		((unsigned long) u.u_sigreturn & (~0x80000000));

	/*
	 * Build the signal context to be used by sigreturn.
	 */
	sigcon.sc_onstack = oonstack;
	sigcon.sc_mask = mask;
	bcopy(u.u_ar0, &sigcon.sc_gs, MAXSIGREGS * sizeof(int));

	copyout(&frame, fp, sizeof(struct sigframe));
	copyout(&sigcon,scp,sizeof(struct sigcontext));
	u.u_ar0[EIP]  = (unsigned int) p;
	u.u_ar0[UESP] = (unsigned int)fp;
}

/*
 * System call to restore state after either a longjump or returning
 * from a signal invocation (or longjumping out of a signal invocation).
 * Reset signal mask and stack state from context left by sendsig (above)
 * or setjump. Restore register back to prious saved state. Make sure that
 * the user hasn't modified the saved state in such a way as to give greater
 * privilege upon return.
 */
sigreturn()
{
	thread_t	t = current_thread();
	register struct uthread	*uthread = t->u_address.uthread;
	unsigned int *r0ptr = (unsigned int *)uthread->uu_ar0;
	register struct sigcontext *scp;
	struct sigcontext sigcon;
	int iopl = r0ptr[EFL] & EFL_IOPL;

	scp = (struct sigcontext *)uthread->uu_arg[0];
	copyin(scp, &sigcon, sizeof(struct sigcontext));

#ifdef	undef
printf("sigreturn sp: 0x%x scp: 0x%x\n\n", r0ptr[UESP], scp);
printsigcontext( &sigcon );
printsigcontext( r0ptr - 2 );
printf("real onstack, mask: %x, %x\n", sigcon.sc_onstack, sigcon.sc_mask);
kdb(0,0,0);
#endif	undef

	bcopy(&sigcon.sc_gs, r0ptr, sizeof(int) * MAXSIGREGS);

	/* Make sure that the user didn't diddle the saved state to
         * gain special privilige during the signal execution.
	 */
	if (!iopl)
		r0ptr[EFL] &= ~EFL_IOPL;	/* IO priv. level to zero */
	r0ptr[EFL] |= PS_IE;	/* Make sure interrupts are enabled */
	/* set TI bit in user CS for LDT access */
	r0ptr[CS] |= 4;

	u.u_eosys = JUSTRETURN;
	u.u_onstack = sigcon.sc_onstack & 01;
	u.u_procp->p_sigmask = sigcon.sc_mask &~
	    (sigmask(SIGKILL)|sigmask(SIGCONT)|sigmask(SIGSTOP));
}

#ifdef undef
printsigcontext(ptr)
struct sigcontext *ptr;
{
printf("sc_onstack %5x ", ptr->sc_onstack);
printf("sc_mask\t%8x\n", ptr->sc_mask);
printf("sc_gs\t%8x ", ptr->sc_gs);
printf("sc_fs\t%8x ", ptr->sc_fs);
printf("sc_es\t%8x ", ptr->sc_es);
printf("sc_ds\t%8x\n", ptr->sc_ds);
printf("sc_edi\t%8x ", ptr->sc_edi);
printf("sc_esi\t%8x ", ptr->sc_esi);
printf("sc_ebp\t%8x ", ptr->sc_ebp);
printf("sc_esp\t%8x\n", ptr->sc_esp);
printf("sc_ebx\t%8x ", ptr->sc_ebx);
printf("sc_edx\t%8x ", ptr->sc_edx);
printf("sc_ecx\t%8x ", ptr->sc_ecx);
printf("sc_eax\t%8x\n", ptr->sc_eax);
printf("sc_trapno %6x ", ptr->sc_trapno);
printf("sc_err\t%8x ", ptr->sc_err);
printf("sc_eip\t%8x ", ptr->sc_eip);
printf("sc_cs\t%8x\n", ptr->sc_cs);
printf("sc_efl\t%8x ", ptr->sc_efl);
printf("sc_uesp\t%8x ", ptr->sc_uesp);
printf("sc_ss\t%8x\n", ptr->sc_ss);
}
#endif undef

/* The following are compatibility routines for programs linked with
 * the original (broken) version of signals.
 */

struct osigcontext {
    int   sc_onstack;
    int   sc_mask;
    int   sc_sp;
    int   sc_fp;
    int   sc_ap;
    int   sc_pc;
    int   sc_ps;
};

struct osigframe {
	int	(*sf_retadr)();
	int	sf_signum;
	int	sf_code;
	struct	osigcontext *sf_scp;
	struct	osigcontext *sf_scpcopy;
	unsigned int sf_regs[SS+1];
};

osendsig(p, sig, mask)
	int (*p)(), sig, mask;
{
	register struct osigcontext *scp;
	struct osigcontext sigcon;
	register int *regs;
	int oonstack;
	struct osigframe frame;
	struct osigframe *fp;

	regs = u.u_ar0;
	oonstack = u.u_onstack;
	/*
	 * Allocate and validate space for the signal handler
	 * context. Note that if the stack is in P0 space, the
	 * call to grow() is a nop, and the useracc() check
	 * will fail if the process has not already allocated
	 * the space with a `brk'.
	 */
	if (!u.u_onstack && (u.u_sigonstack & sigmask(sig))) {
		scp = (struct osigcontext *)u.u_sigsp - 1;
		u.u_onstack = 1;
	} else
		scp = (struct osigcontext *)regs[UESP] - 1;
	fp = (struct osigframe *)scp - 1;
	if ((int)fp <= USRSTACK - ctob(u.u_ssize)) 
		(void)grow((unsigned)fp);

	if (useracc((caddr_t)fp, sizeof (*fp) + sizeof (*scp), B_WRITE) == 0) {
		/*
		 * Process has trashed its stack; give it an illegal
		 * instruction to halt it in its tracks.
		 */
		u.u_signal[SIGILL] = SIG_DFL;
		sig = sigmask(SIGILL);
		u.u_procp->p_sigignore &= ~sig;
		u.u_procp->p_sigcatch &= ~sig;
		u.u_procp->p_sigmask &= ~sig;
		psignal(u.u_procp, SIGILL);
		return;
	}

	/* 
	 * Build the argument list for the signal handler.
	 */
	frame.sf_signum = sig;
	if (sig == SIGILL || sig == SIGFPE) {
		frame.sf_code = u.u_code;
		u.u_code = 0;
	} else
		frame.sf_code = 0;
	frame.sf_scp = scp;
	/*
	 * Build the calls argument frame to be used to call sigreturn
	 */
	frame.sf_scpcopy = scp;
	frame.sf_retadr = u.u_sigreturn;
	bcopy(u.u_ar0,frame.sf_regs,sizeof(frame.sf_regs));
	/*
	 * Build the signal context to be used by sigreturn.
	 */
	sigcon.sc_onstack = oonstack;
	sigcon.sc_mask = mask;
	sigcon.sc_sp = regs[ESP];
	sigcon.sc_fp = regs[EBP];
	sigcon.sc_ap = regs[EBP];
	sigcon.sc_pc = regs[EIP];
	sigcon.sc_ps = regs[EFL];

	copyout(&frame, fp, sizeof(struct osigframe));
	copyout(&sigcon,scp,sizeof(struct osigcontext));
	u.u_ar0[EIP]  = (unsigned int) p;
	u.u_ar0[UESP] = (unsigned int)fp;
	return;
}

osigreturn(r0ptr)
unsigned int r0ptr[];
{
	struct a {
		struct osigcontext *sigcntxp;
	};
	register    unsigned int    *sp;
	register    struct  osigframe  *frame;
	register struct osigcontext *scp;
	struct osigcontext sigcon;
	register int *regs = u.u_ar0;
	int iopl = r0ptr[EFL] & EFL_IOPL;

	sp = (unsigned int *)r0ptr[UESP];/* points to stackframe.regs on the
				  * user stack.
				  */
	sp--;sp--;		/* Now points to retadr
				 * on the user stack
				 */
	frame = (struct osigframe *)sp;
	scp = (struct osigcontext *)((unsigned char)sp + sizeof(struct osigframe));
	

	copyin(frame->sf_regs, r0ptr, sizeof(frame->sf_regs));
	copyin(scp,&sigcon,sizeof(struct osigcontext));
		
	if (!iopl)
		r0ptr[EFL] &= ~EFL_IOPL;	/* IO priv. level to zero */
	/* set interrupt enable flag */
	r0ptr[EFL] |= PS_IE;

	/* set TI bit in user CS for LDT access */
	r0ptr[CS] |= 4;

	u.u_eosys = JUSTRETURN;
	u.u_onstack = sigcon.sc_onstack & 01;
	u.u_procp->p_sigmask = sigcon.sc_mask &~
	    (sigmask(SIGKILL)|sigmask(SIGCONT)|sigmask(SIGSTOP));
}

/* XXX - BEGIN 4.2 COMPATIBILITY */
/*
 * Compatibility with 4.2 chmk $139 used by longjmp()
 */
osigcleanup()
{
	register struct osigcontext *scp;
	register int *regs = u.u_ar0;

	scp = (struct osigcontext *)fuword((caddr_t)regs[UESP]);
	if ((int)scp == -1)
		return;
	if (useracc((caddr_t)scp, 3 * sizeof (int), B_WRITE) == 0)
		return;
	u.u_onstack = scp->sc_onstack & 01;
	u.u_procp->p_sigmask = scp->sc_mask &~
	    (sigmask(SIGKILL)|sigmask(SIGCONT)|sigmask(SIGSTOP));
	regs[UESP] = scp->sc_sp;
}
/* XXX - END 4.2 COMPATIBILITY */
  
#include <mach/machine.h>
halt_cpu()
{
	machine_slot[cpu_number()].running = FALSE;
}

int	waittime = -1;

#ifdef	AT386
int	rebootflag = 0;
#endif	At386

boot(paniced, arghowto)
	int paniced, arghowto;
{
	register int howto;		/* r11 == how to boot */
	register int devtype;		/* r10 == major of root dev */
#ifndef	THREAD_EXIT
	struct mount *mp;
#endif	THREAD_EXIT

	register int i;
#ifdef	THREAD_EXIT
	extern	boolean_t should_exit[];
#endif	THREAD_EXIT

#ifdef	lint
	howto = 0; devtype = 0;
	printf("howto %d, devtype %d\n", arghowto, devtype);
#endif
#if	MACH_RFS
	rfs_boot(paniced, arghowto);
#endif	MACH_RFS
	howto = arghowto;
	if ((howto&RB_NOSYNC)==0 && waittime < 0 && bfreelist[0].b_forw) {
		/*
		 *  Force an accurate time into the root file system super-
		 *  block.
		 */
#ifdef	THREAD_EXIT
		mount[0].m_bufp->b_un.b_fs->fs_fmod = 1;
		waittime = 0;
		(void) splnet();
		printf("syncing disks... ");
		/*
		 * Release inodes held by texts before update.
		 */
		update();
		{ register struct buf *bp;
		  int iter, nbusy;
		  int obusy = 0;

		  for (iter = 0; iter < 20; iter++) {
			nbusy = 0;
			for (bp = &buf[nbuf]; --bp >= buf; )
				if ((bp->b_flags & (B_BUSY|B_INVAL)) == B_BUSY)
					nbusy++;
			if (nbusy == 0)
				break;
			printf("%d ", nbusy);
		        if (nbusy != obusy)
				iter = 0;
			obusy = nbusy;
			DELAY(40000 * iter);
		  }
		}
		printf("done\n");
#else	THREAD_EXIT
		syncdisk();
		waittime = 0;

#if	MACH_VFS
		if(paniced != RB_PANIC) {
		    printf("unmounting file systems... ");
		    for(mp = &mount[NMOUNT - 1]; mp >= mount; mp--) {
			if(mp->m_vfsp && mp->m_dev != rootdev)
			    (void) dounmount(mp->m_vfsp);
		    }
		    printf("done\n");
		}
#endif	MACH_VFS
#endif	THREAD_EXIT
		/*
		 * If we've been adjusting the clock, the todr
		 * will be out of synch; adjust it now.
		 */
		resettodr();
		DELAY(1000000);
	}
	splhi();
	devtype = major(rootdev);

#ifdef	THREAD_EXIT
	for (i = 0; i < NCPUS; i++) {
		should_exit[i] = TRUE;
	}
#endif	THREAD_EXIT
#ifdef	AT386
	rebootflag = 1;		/* if rebootflag is on, keyboard driver will
				 * send a CPU_RESET command to the keyboard
				 * controller to reset the system */
	if (howto&RB_HALT) {
		printf("In tight loop: ctl-alt-del to reboot\n\n");
		spl0();
		while (1);
	}

	if (paniced == RB_PANIC) {
		printf("Waiting for ctl-alt-del to reboot\n\n");
		spl0();
		while (1);
	}

printf("boot: kdreboot()\n");
	kdreboot();
printf("boot: loop()\n");
#endif	AT386

	for (;;)
		;
	/*NOTREACHED*/
}

/*
 * Return the best possible estimate of the time in the timeval
 * to which tvp points.  We do this by reading the interval count
 * register to determine the time remaining to the next clock tick.
 * We must compensate for wraparound which is not yet reflected in the time
 * (which happens when the ICR hits 0 and wraps after the splhigh(),
 * but before the mfpr(ICR)).  Also check that this time is no less than
 * any previously-reported time, which could happen around the time
 * of a clock adjustment.  Just for fun, we guarantee that the time
 * will be greater than the value obtained by a previous call.
 */
microtime(tvp)
	register struct timeval *tvp;
{
	int s = splhigh();
	static struct timeval lasttime;
	register long t;

	*tvp = time;
/*	This code takes advantage of having a clock register that has
	finer resolution than the system clock interrupt. We should look
	into whether or not the AT has something like this.

	t =  mfpr(ICR);
	if (t < -tick / 2 && (mfpr(ICCS) & ICCS_INT))
		t += tick;
	tvp->tv_usec += tick + t;
	if (tvp->tv_usec >= 1000000) {
		tvp->tv_sec++;
		tvp->tv_usec -= 1000000;
	}
*/
	if (tvp->tv_sec == lasttime.tv_sec &&
	    tvp->tv_usec <= lasttime.tv_usec &&
	    (tvp->tv_usec = lasttime.tv_usec + 1) >= 1000000) {
		tvp->tv_sec++;
		tvp->tv_usec -= 1000000;
	}
	lasttime = *tvp;
	splx(s);
}

#if	NAHA
extern	ahastrategy();
#endif	NAHA

physstrat(bp, strat, prio)
	struct buf *bp;
	int (*strat)(), prio;
{
	int s;

#ifdef	AT386
	caddr_t kvtophys();
	vm_offset_t pmap_map_bd();
	unsigned usraddr, addr, eaddr, physaddr, kvaddr, offset, bufnum;
	unsigned long bufmask;

	/* Disk access is faster via programmed I/O than by DMA on
	 * the AT. We map the user's pages into kernel space because
	 * we don't know what context we'll be running in when the
	 * disk operation completed interrupt occurs.
	 */
	if (bp->b_bcount > (PHYSBUFSIZE/2)) {
		uprintf("phystrat: byte count %d too large\n", bp->b_bcount );
		return;
	}
	usraddr = (unsigned) bp->b_un.b_addr;
#define NBPSEC	512
	/* Need sector alignment for hd & fd, not scsi */
#if	NAHA > 0	
	if (strat != ahastrategy && usraddr < VM_MIN_KERNEL_ADDRESS && usraddr & (NBPSEC - 1))
#else	NAHA > 0
	if (usraddr < VM_MIN_KERNEL_ADDRESS && usraddr & (NBPSEC - 1))
#endif	NAHA > 0
	{
		/* if not on sector boundary */
		kvaddr = kmem_alloc(kernel_map, I386_PGBYTES);
		bp->b_un.b_addr = (caddr_t) kvaddr;
		if (bp->b_flags & B_READ) {
			(*strat)(bp);
			s = splbio();
			while ((bp->b_flags & B_DONE) == 0)
				sleep((caddr_t)bp, prio);
			splx(s);
			copyout(kvaddr, usraddr, bp->b_bcount - bp->b_resid);
		} else {  /* B_WRITE */
			copyin(usraddr, kvaddr, bp->b_bcount);
			(*strat)(bp);
			s = splbio();
			while ((bp->b_flags & B_DONE) == 0)
				sleep((caddr_t)bp, prio);
			splx(s);
		}
		bp->b_un.b_addr = (caddr_t) usraddr;
		kmem_free(kernel_map, kvaddr, I386_PGBYTES);
		return;
	}
	if (usraddr < VM_MIN_KERNEL_ADDRESS) {
		bufnum = 0;
		s = spl5();
		for (bufmask = 1; physbufmap & bufmask; bufmask <<= 1) {
			bufnum++;
			if (bufnum == PHYSBUFS) {
				splx(s);
				panic("physstrat: out of physical buffers\n");
			}
		}
		physbufmap |= bufmask;
		splx(s);

		kvaddr = (unsigned) &physbufs[bufnum];
		bp->b_un.b_addr = (caddr_t) (kvaddr + (usraddr & page_mask));
		addr = trunc_page(usraddr);
		eaddr = round_page(usraddr + bp->b_bcount);

		while ( addr < eaddr ) {
			physaddr = (unsigned) pmap_extract(
				current_thread()->task->map->pmap, addr);
			pmap_map_bd(kvaddr, physaddr, round_page(physaddr + 1),
				    VM_PROT_READ | VM_PROT_WRITE);
			addr += I386_PGBYTES;
			kvaddr += I386_PGBYTES;
		}
	}
	else
		bufmask = 0;

#endif	AT386

	(*strat)(bp);

	/* pageout daemon doesn't wait for pushed pages */
	if (bp->b_flags & B_DIRTY) {
		return;
	}
	s = splbio();
	while ((bp->b_flags & B_DONE) == 0)
		sleep((caddr_t)bp, prio);
	splx(s);

#ifdef	AT386
	if ( bufmask != 0 ) {
		s = spl5();
		physbufmap &= ~bufmask;
		splx( s );
		bp->b_un.b_addr = (caddr_t) usraddr;
	}
#endif	AT386
}

maptss(tssp)
struct tss386 *tssp;
{
	extern struct fakedesc gdt[];
	register struct fakedesc *dp;
	
	dp = &gdt[seltoi(JTSSSEL)];
	sdbase(dp, tssp);
	sdlimit(dp, sizeof(struct tss386));
	sdaccess(dp, TSS3_KACC1, TSS_ACC2);
	return(JTSSSEL);
}

sdbase(dp, addr)
struct desc *dp;
struct {
	unsigned int	low:16,
			mid:8,
			high:8;
} addr;
{

	dp->d_base2431 = addr.high;
	dp->d_base1623 = addr.mid;
	dp->d_base0015 = addr.low;
	return;
}

sdlimit(dp, lim)
struct desc *dp;
struct {
	unsigned int	low:16,
			high:4,
			:12;
} lim;
{

	dp->d_lim1619 = lim.high;
	dp->d_lim0015 = lim.low;
	return;
}

sdaccess(dp, acc1, acc2)
struct desc *dp;
unsigned int acc1, acc2;
{

	dp->d_acc0007 = acc1;
	dp->d_acc0811 = acc2;
	return;
}

initcpu()
{
}

/*
 * Floating point code fix, moved in from "old" machdep.c, prior to
 * CMU integration 1/31/89 - eugene
 *
 */

int
test_fps_valid()
{
	register thread_t th;

	return(current_thread()->pcb->pcb_fpvalid);
}

struct fpstate *
get_pcb_fps()
{
	register thread_t th;
	return(&current_thread()->pcb->pcb_fps);
}

int *
get_pcb_context()
{
	register thread_t th;

	return(current_thread()->pcb->pcb_context);
}

load_context(th)
thread_t th;
{
	extern struct fakedesc gdt[];
	register struct tss386 *tssp;
	register struct fakedesc *gdtp, *ldtp;

#ifndef	NO_U_ADDRESS
	load_context_data();
#endif	NO_U_ADDRESS
	ldtp = th->task->map->pmap->ldt;
	gdtp = &gdt[seltoi(LDTSEL)];
	sdbase(gdtp, ldtp);
	/*
	 *	when task have varying ldt's (286 emulation) will need
	 *
	 *	sdlimit(gdtp, LDTSZ * sizeof(*ldtp) - 1);
	 */
	tssp = &th->pcb->pcb_tss;
	sdbase(&gdt[seltoi(JTSSSEL)], tssp);
	sdaccess(&gdt[seltoi(JTSSSEL)], TSS3_KACC1, TSS_ACC2);
	loadtr(JTSSSEL);
	set_ldt(LDTSEL);
	set_cr3(kvtophys(th->task->map->pmap->cr3));
/*
prframe(16, th->pcb->pcb_context);
*/
	setts();
	longjmp(th->pcb->pcb_context, 1);
}

#define NPRFBUF	100

struct prf_buf{
	int	type;
	int	cr3;
	int	*ar0;
	int	cs;
	int	ss;
	int	regs[SS + 1];
} prf_buf[NPRFBUF];

struct prf_buf *prf_ptr = &prf_buf[NPRFBUF];
struct prf_buf *prf_end = &prf_buf[NPRFBUF];

prframe(no, gs)
int no, gs;
{
	register int *prf_ar0;

	if (--prf_ptr < prf_buf)
		prf_ptr = &prf_buf[NPRFBUF - 1];
	prf_ar0 = &gs;
	prf_ptr->type = no;
	prf_ptr->cr3 = get_cr3();
	prf_ptr->ar0 = prf_ar0;
	if (no == 16) {
		prf_ptr->cs = gs;
		return;
	}
	prf_ptr->cs = prf_ar0[CS] & 0xffff;
	prf_access(prf_ar0[CS], prf_ar0[EIP]);
	if (prf_ptr->cs & 3) {
		prf_access(prf_ar0[SS], prf_ar0[UESP]);
		prf_ptr->ss = prf_ar0[SS] & 0xffff;
		bcopy(prf_ar0, prf_ptr->regs, (SS + 1)*sizeof(int));
	} else {
		prf_ptr->ss = 0x160;
		bcopy(prf_ar0, prf_ptr->regs, UESP*sizeof(int));
	}
	if ((prf_ptr->cs == 0x17 || prf_ptr->cs == 0x158) && (prf_ptr->ss == 0x1f || prf_ptr->ss == 0x160))
		return;
	printf("iret:sp, cs - %x %x:%x", prf_ar0, prf_ptr->cs, prf_ar0[EIP]);
	if (prf_ptr->cs & 03)
		printf(" %x:%x", prf_ptr->ss, prf_ar0[UESP]);
	printf("\n");
	return;
}

#ifdef OLIVETTI_CACHE

/* Disable cache on Olivetti XP7 and XP9 boxes. Not used currently */

#define	OPORT_CACHE	0x5478
#define IPORT_CACHE	0x6a

cache_disable()
{
	unsigned char	work;

	work = (inb(IPORT_CACHE) | 0x01);
	outb(OPORT_CACHE, work);
	outb(IPORT_CACHE, work);
	return;

}

#endif OLIVETTI_CACHE

#ifdef	COPROC_SPANPAGE_BUG

/* 
 * Errata #17 for B1-step '386s.  If the first byte of a coprocessor 
 * instruction is the last byte of a page and the next page is 
 * inaccessible (e.g., paged out), the processor will hang until the 
 * next interrupt.  So, every so often we check whether we've hit this 
 * bug.  
 * 
 * This code could also be called by the scheduler, but it's cleaner 
 * to use timeout() to schedule regularly occurring actions.
 */
/* ARGSUSED */
i386_coproc_hang(timeout_arg)
	int timeout_arg;
{
	extern int *intrlocr0;
	int ip = intrlocr0[EIP];
	struct pcb *mypcb = current_thread()->pcb;
	static boolean_t suspicious();

	/* 
	 * The way locore currently sets intrlocr0, it seems possible 
	 * for another interrupt to come along after the clock 
	 * interrupt and clobber intrlocr0.
	 * However, if that happens, then the IP will refer to a 
	 * kernel address, so we'll just punt until the next time the 
	 * scheduler runs.
	 */
	if (ip >= VM_MIN_KERNEL_ADDRESS)
		goto resched;
	
	/* 
	 * The heuristic for detecting the bug is to see whether we've 
	 * been at the same suspicious IP 5 times in a row.  This 
	 * could be made more precise by adding code to trap() to, 
	 * e.g., set pcb_ip_same back to 0, but I'd like to avoid yet 
	 * another hack if I can avoid it.
	 * 
	 * If we satisfy the heuristic, then we warn the user and read 
	 * the first byte of the next page, in an attempt to force the 
	 * entire instruction to be in core.  If this fails, the user 
	 * can always kill the process.
	 * Note: we use tprintf() because uprintf() might block.
	 */
	
	if (suspicious(ip) && mypcb->pcb_last_uip == ip)
		++mypcb->pcb_ip_same;
	else {
		mypcb->pcb_last_uip = ip;
		mypcb->pcb_ip_same = 0;
		goto resched;
	}

	if (mypcb->pcb_ip_same >= 5) {
		tprintf(u.u_ttyp,
			"Kicking process %d (it appears stuck at 0x%x).\n",
			u.u_procp->p_pid, ip);
		mypcb->pcb_ip_same = 0;
		(void)fubyte(ip+1);	/* try to unwedge it */
	}
resched:
	timeout(i386_coproc_hang, (caddr_t) 0, hz);	/* once a second */
}

/* 
 * A suspicious IP is one at the end of a page, pointing to a
 * coprocessor escape (opcode 0xd8-0xdf).
 */

static boolean_t
suspicious(ip)
	int ip;
{
	u_char opcode;

	if ((ip & page_mask) == page_mask) {
		opcode = fubyte(ip);
		if (opcode >= 0xd8 && opcode <= 0xdf)
			return(TRUE);
	}
	return(FALSE);
}
#endif	COPROC_SPANPAGE_BUG

ovbcopy(from, to, bytes)
	char *from, *to;
	int bytes;			/* num bytes to copy */
{
	/* Assume that bcopy copies left-to-right (low addr first). */
	if (from + bytes <= to || to + bytes <= from || to == from)
		bcopy(from, to, bytes);	/* non-overlapping or no-op*/
	else if (from > to)
		bcopy(from, to, bytes);	/* overlapping but OK */
	else {
		/* to > from: overlapping, and must copy right-to-left. */
		from += bytes - 1;
		to += bytes - 1;
		while (bytes-- > 0)
			*to-- = *from--;
	}
}
