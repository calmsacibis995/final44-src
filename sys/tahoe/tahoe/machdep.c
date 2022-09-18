/*
 * Copyright (c) 1982,1987,1988 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)machdep.c	7.16 (Berkeley) 7/12/92
 */

#include "sys/param.h"
#include "sys/systm.h"
#include "sys/user.h"
#include "sys/kernel.h"
#include "sys/map.h"
#include "sys/vm.h"
#include "sys/proc.h"
#include "sys/buf.h"
#include "sys/reboot.h"
#include "sys/conf.h"
#include "sys/file.h"
#include "sys/text.h"
#include "sys/clist.h"
#include "sys/callout.h"
#include "sys/cmap.h"
#include "sys/malloc.h"
#include "sys/mbuf.h"
#include "sys/msgbuf.h"
#ifdef SYSVSHM
#include "sys/shm.h"
#endif

#include "../include/cpu.h"
#include "../include/reg.h"
#include "../include/pte.h"
#include "../include/psl.h"
#include "mem.h"
#include "../include/mtpr.h"
#include "cp.h"

#include "../vba/vbavar.h"

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
#include "yc.h"
#if NCY > 0
#include "../vba/cyreg.h"
#endif
int	msgbufmapped;		/* set when safe to use msgbuf */
int	physmem = MAXMEM;	/* max supported memory, changes to actual */
/*
 * safepri is a safe priority for sleep to set for a spin-wait
 * during autoconfiguration or after a panic.  On the tahoe, this must
 * be > 0 so that we can take interrupts after a panic while on the interrupt
 * stack.  Otherwise, we will get a illegal instruction trap when we return
 * from any interrupt that comes in.
 */
int	safepri = 1;

/*
 * Machine-dependent startup code
 */
startup(firstaddr)
	int firstaddr;
{
	register int unixsize;
	register unsigned i;
	register struct pte *pte;
	int mapaddr, j;
	register caddr_t v;
	int maxbufs, base, residual;

	/*
	 * Initialize error message buffer (at end of core).
	 */
	maxmem = physmem - btoc(sizeof (struct msgbuf));
	pte = msgbufmap;
	for (i = 1; i < btoc(sizeof (struct msgbuf)) + 1; i++)
		*(int *)pte++ = PG_V | PG_KW | (physmem - i);
	mtpr(TBIA, 1);
	msgbufmapped = 1;
#ifdef KADB
	kdb_init();			/* startup kernel debugger */
	(void) cnopen(makedev(0, 1), 0);	/* open console XXX */
#endif
	/*
	 * Good {morning,afternoon,evening,night}.
	 */
	printf(version);
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
	v = (caddr_t)(0xc0000000 | (firstaddr * NBPG));
#define	valloc(name, type, num) \
	    (name) = (type *)v; v = (caddr_t)((name)+(num))
#define	valloclim(name, type, num, lim) \
	    (name) = (type *)v; v = (caddr_t)((lim) = ((name)+(num)))
#if NCY > 0
	/*
	 * Allocate raw buffers for tapemaster controllers
	 * first, as they need buffers in the first megabyte.
	 */
	valloc(cybuf, char, NCY * CYMAXIO);
#endif
	valloclim(file, struct file, nfile, fileNFILE);
	valloclim(proc, struct proc, nproc, procNPROC);
	valloclim(text, struct text, ntext, textNTEXT);
	valloc(cfree, struct cblock, nclist);
	valloc(callout, struct callout, ncallout);
	valloc(swapmap, struct map, nswapmap = nproc * 2);
	valloc(argmap, struct map, ARGMAPSIZE);
	valloc(kernelmap, struct map, nproc);
	valloc(mbmap, struct map, nmbclusters/4);
	valloc(kmemmap, struct map, ekmempt - kmempt);
	valloc(kmemusage, struct kmemusage, ekmempt - kmempt);
#ifdef SYSVSHM
	valloc(shmsegs, struct shmid_ds, shminfo.shmmni);
#endif
	
	/*
	 * Determine how many buffers to allocate.
	 * Use 10% of memory for the first 2 Meg, 5% of the remaining
	 * memory. Insure a minimum of 16 buffers.
	 * We allocate 1/2 as many swap buffer headers as file i/o buffers.
	 */
	if (bufpages == 0)
		if (physmem < (2 * 1024 * 1024))
			bufpages = physmem / 10 / CLSIZE;
		else
			bufpages = ((2 * 1024 * 1024 + physmem) / 20) / CLSIZE;
	if (nbuf == 0) {
		nbuf = bufpages / 2;
		if (nbuf < 16)
			nbuf = 16;
	}
	if (nswbuf == 0) {
		nswbuf = (nbuf / 2) &~ 1;	/* force even */
		if (nswbuf > 256)
			nswbuf = 256;		/* sanity */
	}
	valloc(swbuf, struct buf, nswbuf);

	/*
	 * Now the amount of virtual memory remaining for buffers
	 * can be calculated, estimating needs for the cmap.
	 */
	ncmap = (maxmem*NBPG - ((int)v &~ 0xc0000000)) /
		(CLBYTES + sizeof(struct cmap)) + 2;
	maxbufs = ((SYSPTSIZE * NBPG) -
	    ((int)(v + ncmap * sizeof(struct cmap)) - 0xc0000000)) /
		(MAXBSIZE + sizeof(struct buf));
	if (maxbufs < 16)
		panic("sys pt too small");
	if (nbuf > maxbufs) {
		printf("SYSPTSIZE limits number of buffers to %d\n", maxbufs);
		nbuf = maxbufs;
	}
	if (bufpages > nbuf * (MAXBSIZE / CLBYTES))
		bufpages = nbuf * (MAXBSIZE / CLBYTES);
	valloc(buf, struct buf, nbuf);

	/*
	 * Allocate space for core map.
	 * Allow space for all of phsical memory minus the amount 
	 * dedicated to the system. The amount of physical memory
	 * dedicated to the system is the total virtual memory of
	 * the system thus far, plus core map, buffer pages,
	 * and buffer headers not yet allocated.
	 * Add 2: 1 because the 0th entry is unused, 1 for rounding.
	 */
	ncmap = (maxmem*NBPG - ((int)(v + bufpages*CLBYTES) &~ 0xc0000000)) /
		(CLBYTES + sizeof(struct cmap)) + 2;
	valloclim(cmap, struct cmap, ncmap, ecmap);

	/*
	 * Clear space allocated thus far, and make r/w entries
	 * for the space in the kernel map.
	 */
	unixsize = btoc((int)v &~ 0xc0000000);
	while (firstaddr < unixsize) {
		*(int *)(&Sysmap[firstaddr]) = PG_V | PG_KW | firstaddr;
		clearseg((unsigned)firstaddr);
		firstaddr++;
	}

	/*
	 * Now allocate buffers proper.  They are different than the above
	 * in that they usually occupy more virtual memory than physical.
	 */
	v = (caddr_t) ((int)(v + PGOFSET) &~ PGOFSET);
	valloc(buffers, char, MAXBSIZE * nbuf);
	base = bufpages / nbuf;
	residual = bufpages % nbuf;
	mapaddr = firstaddr;
	for (i = 0; i < residual; i++) {
		for (j = 0; j < (base + 1) * CLSIZE; j++) {
			*(int *)(&Sysmap[mapaddr+j]) = PG_V | PG_KW | firstaddr;
			clearseg((unsigned)firstaddr);
			firstaddr++;
		}
		mapaddr += MAXBSIZE / NBPG;
	}
	for (i = residual; i < nbuf; i++) {
		for (j = 0; j < base * CLSIZE; j++) {
			*(int *)(&Sysmap[mapaddr+j]) = PG_V | PG_KW | firstaddr;
			clearseg((unsigned)firstaddr);
			firstaddr++;
		}
		mapaddr += MAXBSIZE / NBPG;
	}

	unixsize = btoc((int)v &~ 0xc0000000);
	if (firstaddr >= physmem - 8*UPAGES)
		panic("no memory");
	mtpr(TBIA, 1);			/* After we just cleared it all! */

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
	meminit(firstaddr, maxmem);
	maxmem = freemem;
	printf("avail mem = %d\n", ctob(maxmem));
	printf("using %d buffers containing %d bytes of memory\n",
		nbuf, bufpages * CLBYTES);
	rminit(kernelmap, (long)USRPTSIZE, (long)1,
	    "usrpt", nproc);
	rminit(mbmap, (long)(nmbclusters * CLSIZE), (long)CLSIZE,
	    "mbclusters", nmbclusters/4);
	kmeminit();		/* now safe to do malloc/free */
	intenable = 1;		/* Enable interrupts from now on */

	/*
	 * Set up CPU-specific registers, cache, etc.
	 */
	initcpu();

	/*
	 * Set up buffers, so they can be used to read disk labels.
	 */
	bhinit();
	binit();

	/*
	 * Configure the system.
	 */
	configure();
}

#ifdef PGINPROF
/*
 * Return the difference (in microseconds)
 * between the  current time and a previous
 * time as represented  by the arguments.
 * If there is a pending clock interrupt
 * which has not been serviced due to high
 * ipl, return error code.
 */
/*ARGSUSED*/
vmtime(otime, olbolt, oicr)
	register int otime, olbolt, oicr;
{

	return (((time.tv_sec-otime)*60 + lbolt-olbolt)*16667);
}
#endif

/*
 * Send an interrupt to process.
 *
 * Stack is set up to allow sigcode stored
 * in u. to call routine, followed by kcall
 * to sigreturn routine below.  After sigreturn
 * resets the signal mask, the stack, and the
 * frame pointer, it returns to the user
 * specified pc, psl.
 */
sendsig(catcher, sig, mask, code)
	sig_t catcher;
	int sig, mask;
	unsigned code;
{
	register struct sigcontext *scp;
	register struct proc *p = u.u_procp;
	register int *regs;
	register struct sigframe {
		int	sf_signum;
		int	sf_code;
		struct	sigcontext *sf_scp;
		sig_t	sf_handler;
		int	sf_regs[6];		/* r0-r5 */
		struct	sigcontext *sf_scpcopy;
	} *fp;
	int oonstack;

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
		scp = (struct sigcontext *)u.u_sigsp - 1;
		u.u_onstack = 1;
	} else
		scp = (struct sigcontext *)regs[SP] - 1;
	fp = (struct sigframe *)scp - 1;
	if ((int)fp <= USRSTACK - ctob(u.u_ssize)) 
		(void) grow((unsigned)fp);
	if (useracc((caddr_t)fp, sizeof (*fp) + sizeof (*scp), B_WRITE) == 0) {
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
	fp->sf_signum = sig;
	fp->sf_code = code;
	fp->sf_scp = scp;
	fp->sf_handler = catcher;
	/*
	 * Build the callf argument frame to be used to call sigreturn.
	 */
	fp->sf_scpcopy = scp;
	/*
	 * Build the signal context to be used by sigreturn.
	 */
	scp->sc_onstack = oonstack;
	scp->sc_mask = mask;
	scp->sc_sp = regs[SP];
	scp->sc_fp = regs[FP];
	scp->sc_pc = regs[PC];
	scp->sc_ps = regs[PS];
	regs[SP] = (int)fp;
	regs[PC] = (int)u.u_pcb.pcb_sigc;
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
struct sigreturn_args {
	struct sigcontext *sigcntxp;
};
/* ARGSUSED */
sigreturn(p, uap, retval)
	struct proc *p;
	struct sigreturn_args *uap;
	int *retval;
{
	register struct sigcontext *scp;
	register int *regs = u.u_ar0;

	scp = uap->sigcntxp;
	if (useracc((caddr_t)scp, sizeof (*scp), 0) == 0)
		return (EINVAL);
	if ((scp->sc_ps & (PSL_MBZ|PSL_IPL|PSL_IS)) != 0 ||
	    (scp->sc_ps & (PSL_PRVMOD|PSL_CURMOD)) != (PSL_PRVMOD|PSL_CURMOD))
		return (EINVAL);
	u.u_onstack = scp->sc_onstack & 01;
	p->p_sigmask = scp->sc_mask &~ sigcantmask;
	regs[FP] = scp->sc_fp;
	regs[SP] = scp->sc_sp;
	regs[PC] = scp->sc_pc;
	regs[PS] = scp->sc_ps;
	return (EJUSTRETURN);
}

int	waittime = -1;

boot(arghowto)
	int arghowto;
{
	register long dummy;		/* r12 is reserved */
	register int howto;		/* r11 == how to boot */
	register int devtype;		/* r10 == major of root dev */
	extern char *panicstr;

	howto = arghowto;
	if ((howto&RB_NOSYNC) == 0 && waittime < 0 && bfreelist[0].b_forw) {
		register struct buf *bp;
		int iter, nbusy;

		waittime = 0;
		(void) splnet();
		printf("syncing disks... ");
		/*
		 * Release vnodes held by texts before update.
		 */
		if (panicstr == 0)
			xumount(NULL);
		sync();

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
		DELAY(10000);			/* wait for printf to finish */
	}
	mtpr(IPL, 0x1f);			/* extreme priority */
	devtype = major(rootdev);
	*(int *)CPBFLG = howto;
	if (howto&RB_HALT) {
		printf("halting (in tight loop); hit ~h\n\n");
		mtpr(IPL, 0x1f);
		for (;;)
			;
	} else {
		if (howto & RB_DUMP) {
			doadump();		/* CPBOOT's itsself */
			/*NOTREACHED*/
		}
		tocons(CPBOOT);
	}
#ifdef lint
	dummy = 0; dummy = dummy;
	printf("howto %d, devtype %d\n", arghowto, devtype);
#endif
	for (;;)
		asm("halt");
	/*NOTREACHED*/
}

struct	cpdcb_o cpcontrol;

/*
 * Send the given comand ('c') to the console processor.
 * Assumed to be one of the last things the OS does before
 *  halting or rebooting.
 */
tocons(c)
{
	register timeout;

	cpcontrol.cp_hdr.cp_unit = CPUNIT;
	cpcontrol.cp_hdr.cp_comm =  (char)c;
	if (c != CPBOOT) 
		cpcontrol.cp_hdr.cp_count = 1;	/* Just for sanity */
	else {
		cpcontrol.cp_hdr.cp_count = 4;
		*(int *)cpcontrol.cp_buf = 0;	/* r11 value for reboot */
	}
	timeout = 100000;				/* Delay loop */
	while (timeout-- && (cnlast->cp_unit&CPDONE) == 0)
		uncache(&cnlast->cp_unit);
	/* give up, force it to listen */
	mtpr(CPMDCB, vtoph((struct proc *)0, (unsigned)&cpcontrol));
}

#if CLSIZE != 1
/*
 * Invalidate single all pte's in a cluster
 */
tbiscl(v)
	unsigned v;
{
	register caddr_t addr;		/* must be first reg var */
	register int i;

	addr = ptob(v);
	for (i = 0; i < CLSIZE; i++) {
		mtpr(TBIS, addr);
		addr += NBPG;
	}
}
#endif

int	dumpmag = 0x8fca0101;	/* magic number for savecore */
int	dumpsize = 0;		/* also for savecore */

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
	 * Don't dump on the first CLSIZE pages,
	 * in case the dump device includes a disk label.
	 */
	if (dumplo < CLSIZE)
		dumplo = CLSIZE;
}

/*
 * Doadump comes here after turning off memory management and
 * getting on the dump stack, either when called above, or by
 * the auto-restart code.
 */
dumpsys()
{

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
	printf("\n\n");
	DELAY(1000);
	tocons(CPBOOT);
}

/*
 * Bus error 'recovery' code.
 * Print out the buss frame and then give up.
 * (More information from special registers can be printed here.)
 */

/*
 * Frame for bus error
 */
struct buserframe {
	int	which_bus;		/* primary or secondary */
	int	memerreg;		/* memory error register */
	int	trp_pc;			/* trapped pc */
	int	trp_psl;		/* trapped psl */
};

char	*mem_errcd[8] = {
	"Unknown error code 0",
	"Address parity error",		/* APE */
	"Data parity error",		/* DPE */
	"Data check error",		/* DCE */
	"Versabus timeout",		/* VTO */
	"Versabus error",		/* VBE */
	"Non-existent memory",		/* NEM */
	"Unknown error code 7",
};

buserror(v)
	caddr_t v;
{
	register struct buserframe *busef = (struct buserframe *)v;
	register long reg;

	printf("bus error, address %x, psl %x\n",
	    busef->trp_pc, busef->trp_psl);
	reg =  busef->memerreg;
	printf("mear %x %s\n",
	    ((reg&MEAR)>>16)&0xffff, mem_errcd[reg & ERRCD]);
	if (reg&AXE)
		printf("adapter external error\n");
	printf("error master: %s\n", reg&ERM ? "versabus" : "tahoe");
	if (reg&IVV)
		printf("illegal interrupt vector from ipl %d\n", (reg>>2)&7);
	reg = busef->which_bus;
	printf("mcbr %x versabus type %x\n",
	    ((reg&MCBR)>>16)&0xffff, reg & 0xffc3);
	if ((busef->memerreg&IVV) == 0)
		panic("buserror");
}

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

initcpu()
{
	register struct proc *p;

	p = &proc[0];
#define	initkey(which, p, index) \
    which/**/_cache[index] = 1, which/**/_cnt[index] = 1; \
    p->p_/**/which = index;
	initkey(ckey, p, MAXCKEY);
	initkey(dkey, p, MAXDKEY);
}

/*
 * Clear registers on exec
 */
/* ARGSUSED */
setregs(entry, retval)
	u_long entry;
	int *retval;
{

#ifdef notdef
	/* should pass args to init on the stack */
	for (rp = &u.u_ar0[0]; rp < &u.u_ar0[16];)
		*rp++ = 0;
#endif
	u.u_ar0[FP] = 0;	/* bottom of the fp chain */
	u.u_ar0[PC] = entry + 2;
}
