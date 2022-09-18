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
 * $Log:	machdep.c,v $
 * Revision 2.16  89/03/15  17:34:26  gm0w
 * 	Changed include of sys/rfs.h to rfs/rfs.h
 * 	[89/03/15            gm0w]
 * 
 * Revision 2.15  89/03/09  04:50:40  rpd
 * 	More cleanup.  Ripped out MACH_TIME.
 * 
 * Revision 2.14  89/02/25  20:24:58  gm0w
 * 	Is tocons correct for VAX8800???
 * 	And check out the msgbuf stuff.
 * 	[89/02/07            rvb]
 * 
 * Revision 2.13  89/01/31  17:30:08  rpd
 * 	Added physmem declaration.  (The one in sys/systm.h is "extern" now.)
 * 
 * Revision 2.12  88/12/19  02:54:32  mwyoung
 * 	Remove yet more lint.
 * 	[88/12/17            mwyoung]
 * 
 * Revision 2.11  88/10/18  03:40:27  mwyoung
 * 	Remove lint.  Move inclusion of BI files outside wtime() routine.
 * 	[88/10/06            mwyoung]
 * 	
 * Revision 2.10  88/10/11  13:03:34  rpd
 * 	cca_snarf now takes a verbose switch.
 * 	[88/10/10            rvb]
 * 	
 * 	VAX6200: Try ssc timer chip.
 * 	[88/10/08            rvb]
 * 	
 * 	We must do a ka650_init() very early in startup so that we have
 * 	cpmbx for console type testing.
 * 	[88/10/03            rvb]
 * 
 * Revision 2.9  88/09/27  17:32:34  rvb
 * 	Fixed Log
 * 
 * Revision 2.8  88/09/27  16:09:00  rvb
 * 	valloc arptab
 * 	[88/09/23            rvb]
 * Revision 2.7  88/09/07  15:14:24  berman
 * 	Removed case VAX630 printout of registers at boot time.
 * 	[88/09/06            berman]
 * 
 * Revision 2.6  88/08/23  23:01:32  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Moved code that reduced useable physical memory for 630 to
 * 	memory sizing.
 * 	[88/08/22            mrt]
 * 
 * Revision 2.5  88/08/10  10:29:29  rvb
 *  19-Jul-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Not all machine checks are fatal.  Let mchk_ka62a decide for
 * 	that machine. and mchk_ka88 for 8800
 * 
 *  12-Jul-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Move register printout to after (650, 630) console is initialized.
 * 
 *  30-Jun-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Allocate correct amount of vm for nmbclusters.
 * 
 *   8-Jun-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	For VAX6200, try to reboot master vs halt and try to never
 * 	restart slave.
 * 
 *   7-Jun-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Print out a message by slave when it is halting.
 * 
 *  27-May-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Moved out interrupt_processor to vaxmp.c.
 * 	And flushed old cpu_number() fn.
 * 
 *  27-May-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Changed splx(0x1f) to splhigh().  (which no longer is 0x1f).
 * 
 *  10-May-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Define ka820_csr to map port controller.
 * 
 *   2-May-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	VAX820: halt_cpu must turn off mapping, so that "s 10" will
 * 	work.  So we look like the other vaxen.  Apparently the prom
 * 	monitor leaves the mapping unchanged (which would have been
 * 	virtual.)
 * 
 *  25-Apr-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	wtime outs (vector 0x60) are not necessarily fatal on a 6200.
 * 
 *
 * 10-Apr-88  David Golub (dbg) at Carnegie-Mellon University
 *	Don't allocate user_pt_map here.  Pmap module now allocates and
 *	manages the space for user page tables.
 *
 *  8-Apr-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Since the 6200 has a cVax (#10) cpu, we must now switch on 
 *	machine vs cpu.
 *
 * 31-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Eliminate use of "freemem".
 *
 * 29-Feb-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Eliminate use of silly pcb field to get size of signal trampoline
 *	code.
 *
 * 11-Feb-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 12-May-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Integrated fix from Rick Rashid to use only 5% of memory for
 *	buffers instead of 10%.
 *	[ V5.1(XF24) ]
 *
 * 29-Feb-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Eliminate use of silly pcb field to get size of signal trampoline
 *	code.
 *
 * 11-Feb-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 11-Dec-87  Stephen Schwab (schwab) at Carnegie-Mellon University
 *	For 650, use ssc timer 0 vs uVax clock (in microtime)(
 *
 *  5-Dec-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Condensed buffer size calculations.  Use one buffer per page,
 *	since pages are virtual-size.
 *	[Also, removed some meaningless history.]
 *
 * 18-Nov-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	OOPS -- lost the VAX_630 case in the boot().
 *
 * 26-Oct-87  Robert Baron (rvb) at Carnegie-Mellon University
 * 26-Oct-87  Stephen Schwab (schwab) at Carnegie-Mellon University
 * 	Changes for 650:
 *		Generalize Console Program Mail BoX (cpmbx) to work
 *		for both 650 and 630.  (effects reboot, ...)
 *		Added support for memenable and memerror for 650.
 *		Added machine check support.
 *		And otherwise made a 650 be treated as a 630.
 *	NOTE: we don't handle MAYFAIR with qdss and qvss yet
 *
 * 14-Sep-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added call to panic_init(), as directed by David Black.
 *
 *  4-Sep-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	CS_BUGFIX: Correct calculation of second-boundary rollover
 *	in microtime().
 *
 * 28-Aug-87  David Golub (dbg) at Carnegie-Mellon University
 *	Remove arg_zone - exec now uses kernel_pageable_map (allocated
 *	in init_main).  Removed swapmap for MACH.  Turn off cpu_number()
 *	routine for NCPUS == 1; it becomes a macro instead.
 *
 * 27-Aug-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Fixes for MA780 ecc errors on slaves processors.
 *
 *  5-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Support for 8800 in cpu_number and interrupt_processor.
 *
 *  1-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Updated for latest u-area hacks.
 *
 * 26-Feb-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added interrupt_processor as model-independent dispatch routine.
 *
 * 17-Dec-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fix to correctly initialize watch chip pointer without MACH.
 *	[ V5.1(F1) ]
 *
 * 16-Dec-86  David Golub (dbg) at Carnegie-Mellon University
 *	Moved definition of Mbmap to ../vaxif/if_uba.h to
 *	keep it in machine-dependent code.  Removed include of
 *	text.h and allocation of text table for MACH.
 *
 * 30-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Set watch_chip pointer and Microvax console reboot flags before
 *	setting up console.
 *
 * 30-Sep-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Set the PC correctly for executing the signal trampoline code
 *	when MACH is turned on.
 *
 * 13-Aug-86  David Golub (dbg) at Carnegie-Mellon University
 *	Timing code is now initialized in locore.
 *
 * 19-Jun-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS: fixed to use physical address for uVax-II mail-box
 *	in dumpsys().
 *
 * 10-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	More VAX820 support: halt, reboot, cache enable and other random
 *	things.
 *
 *  9-May-86  Robert V. Baron (rvb) at Carnegie-Mellon University
 *	Extended memory error code to handle mpm controller.
 *
 *  5-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	VAX820 support for machine checks.
 *
 * 25-Feb-86  David Golub (dbg) at Carnegie-Mellon University
 *	Converted to new virtual memory code.
 *
 * 20-Dec-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	MACH_RFS:  Added rfs_boot() hook in boot().
 *
 *  7-Dec-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Set the msgbuf_mapped flag after mapping the message buffer.
 *	This is used by putchar.
 *
 *  8-Sep-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added support for kernel debugger.
 *
 * 18-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS: force update of root file system super-block on
 *	crash to help keep the time recorded there more up to date
 *	across crashes.
 *
 * 26-Aug-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	When halting (or rebooting), cause all slave processors to exit.
 *	Fix message printed out for halt on MicroVAX I.
 *
 * 25-Aug-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Add allocation of thread table.  Added cpu_number() routine.
 *
 * 25-May-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded to 4.2BSD.  Carried over changes below.
 *
 * 20-Aug-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Separate the accounting for physical pages from system pte
 *	slots.  Also add on demand printout of table sizes. And
 *	don't SHM_FREE() and IPC_FREE() on a panic.
 *
 * 20-Aug-85  David L. Black (dlb) at CMU.  added miscellaneous init code
 *	(kernel timing structures and cpu number) for timing
 *
 * 28-Aug-84  Andy Gruss (gruss) at Carnegie-Mellon University
 *	NGFB:  Installed hooks to enable reporting of parity
 *	errors from a Gruss frame buffer interface.  For a GFB, all
 *	parity errors will be reported on the console if GFB error
 *	reporting has been enabled (with the appropriate 'ioctl' call).
 *
 *  2-Aug-85  David L. Black (dlb) at CMU.  added allocation for uproc table
 *
 * 26-Jun-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	MACH_KDB: changed startup() to initialize kernel debugger on
 *	boot.
 *	[V1(1)]
 *
 * 22-Jun-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Reboot/halt code for MicroVAX II ala Ultrix.
 *
 * 15-Jun-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added support for new mcrdata structure, setcache function
 *	and better machine check handling (all from Ultrix).
 *
 * 16-Feb-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	MACH_RFS:  Added dynamic allocation of remote file
 *	mechanism process table (V3.04b).
 *
 */
 
#include <cpus.h>
#include <confdep.h>
#include <cputypes.h>

#include <mach_kdb.h>
#include <mach_rfs.h>
#include <mach_load.h>
#include <mach_mpm.h>
#include <quota.h>
 
#include <gfb.h>

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)machdep.c	7.1 (Berkeley) 6/5/86
 */

#include <vax/reg.h>
#include <vax/pte.h>
#include <vax/psl.h>

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
#include <sys/cmap.h>
#include <sys/mbuf.h>
#include <sys/msgbuf.h>
#include <sys/quota.h>
#include <sys/mount.h>
#include <sys/fs.h>
#if	MACH_RFS
#include <rfs/rfs.h>
#endif	MACH_RFS

#if	NGFB > 0
#include <vax/gfbreg.h>
#endif	NGFB
#include <vax/frame.h>
#include <vax/clock.h>
#include <vax/cons.h>
#include <vax/cpu.h>
#include <vax/mem.h>
#include <vax/mtpr.h>
#include <vax/rpb.h>
#if	VAX650 || VAX630
#include <vax/uvax.h>
#endif	VAX650 || VAX630
#include <vax/ka630.h>
#if	VAX650
#include <vax/ka650.h>
#endif	VAX650
#if	VAX6200
#include <vaxnb/ka62a.h>
#include <vaxnb/cca.h>
#endif	VAX6200
#include <vaxuba/ubavar.h>
#include <vaxuba/ubareg.h>

#include <kern/thread.h>
#include <kern/lock.h>
#include <vm/vm_kern.h>
#include <mach/vm_param.h>
#include <kern/zalloc.h>
#include <machine/vmparam.h>
struct pte 	*Sysmap;
vm_offset_t	Sysbase;
long		Syssize;
#include <vax/watch_chip.h>

/*
 *	For arptab:
 */
#include <netinet/in.h>
/*
#include <netinet/in_systm.h>
#include <netinet/ip.h>
 */
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/if_ether.h>

int physmem;

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
#define SHOW_SPACE	0

#if	SHOW_SPACE
int	show_space = 1;
#endif	SHOW_SPACE

int	msgbuf_mapped = FALSE;
vm_map_t	buffer_map;
#include <vaxif/if_uba.h>	/* definition of Mbmap */

extern int	loadpt, loadpg;

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

#if	VAX6200
	if (cpu == VAX_6200) {

		printf("Startup: ka62a_csr1 V/P %x/%x",
			ka62a_csr1, pmap_extract(kernel_pmap, ka62a_csr1));

		printf(" ka62a_ssc V/P %x/%x\n",
			ka62a_ssc, pmap_extract(kernel_pmap, ka62a_ssc));

		printf("Startup: cca V/P/P %x/%x/",
			cca, pmap_extract(kernel_pmap, cca));

		printf("%x L%x bitmap V/P xxxx/%x L%x\n",
			cca->base, cca->size,
			cca->bitmap, cca->bitmap_sz);

	}
#endif	VAX6200
#if	VAX820
	if (cpu == VAX_820) {
#include <vaxnb/ka820.h>
		printf("Startup: ka820_csr V/P %x/%x\n",
			ka820_csr, pmap_extract(kernel_pmap, ka820_csr));
	}
#endif	VAX820
#ifdef	XXX
	/* XXX - need to handle message buffer */
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
#endif	XXX

	/*
	 * Good {morning,afternoon,evening,night}.
	 */
#if	defined(VAX650) || defined(VAX630) || defined(VAX1)
	switch (cpu) {
#if	VAX650
	    case VAX_650:
	    	ka650_init();
		break;
		/*
		 * yes,  this implies that initcpu() should be done here.
		 * But I don't have the time to test to see if it breaks
		 * anything on any of the architectures so I will just do
		 * this for uVaxIII since I need it.
		 */
#endif	VAX650
#if	VAX630
	    case VAX_630: {

		/*
		 *  Map the watch chip as early as possible since the
		 *  QVSS driver will need to look at its RAM to determine
		 *  the console type.
		 */
		cldevice = (struct cldevice *)kmem_alloc_pageable(kernel_map,
				round_page(NBPG));
		ioaccess((caddr_t)0x200b8000, (vm_offset_t)cldevice, NBPG);
		watch_chip = (struct watch_chip *)cldevice;
		cpmbx = (char *)&cldevice->cpmbx;
		break;
	    }
	}
#endif	VAX630
	switch (cpu) {
#if	VAX1
	    case VAX_1:
#endif	VAX1
#if	VAX630
	    case VAX_630:
#endif	VAX630
#if	VAX650
	    case VAX_650:
#endif	VAX650
		/*
		 *	Setup the virtual console in case we have qvss or
		 *	qdss.
		 */
		qvcons_init();
		qdcons_init();
		break;
	}
#endif	defined(VAX650) || defined(VAX630) || defined(VAX1)
	panic_init();
	/*
	 *	The following constants are set to keep a bunch
	 *	of Unix code happy, all uses of these should eventually
	 *	be fixed.
	 */
	Sysmap = (struct pte *) vm_map_pmap(kernel_map)->p0br;	/* XXX */
	Sysbase = (vm_offset_t) 0x80000000;		/* XXX */
	Syssize = mfpr(SLR);				/* XXX */
	physmem = atop(mem_size);			/* XXX */
#if	MACH_KDB
	/*
	 *  Initialize the kernel debugger.  Cause a breakpoint trap to the
	 *  debugger before proceding any further if the proper option bit was
	 *  specified in the boot flags.
	 */
	kdb_init();
	if (boothowto&RB_HALT && boothowto&RB_KDB)
	    asm("bpt");
#endif	MACH_KDB
	switch (cpu) {
	extern long boot_regs[];

	case VAX_6200:
	case VAX_820:
	case VAX_650:
		printf("R0 .. R3:   %x %x %x %x\n",
			boot_regs[0], boot_regs[1], boot_regs[2], boot_regs[3]);
		printf("R4 .. R7:   %x %x %x %x\n",
			boot_regs[4], boot_regs[5], boot_regs[6], boot_regs[7]);
		printf("R8 .. RB:   %x %x %x %x\n",
			boot_regs[8], boot_regs[9], boot_regs[0xa], boot_regs[0xb]);
		printf("RC .. RF:   %x %x %x %x\n",
			boot_regs[0xc], boot_regs[0xd], boot_regs[0xe], boot_regs[0xf]);
		break;
	}
	printf(version);
#define MEG	(1024*1024)
	printf("physical memory = %d.%d%d megabytes.\n", mem_size/MEG,
		((mem_size%MEG)*10)/MEG,
		((mem_size%(MEG/10))*100)/MEG);

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
	 *	Since the virtual memory system has already been set up,
	 *	we cannot bypass it to allocate memory as the old code
	 *	does.  We therefore make two passes over the table
	 *	allocation code.  The first pass merely calculates the
	 *	size needed for the various data structures.  The
	 *	second pass allocates the memory and then sets the
	 *	actual addresses.  The code must not change any of
	 *	the allocated sizes between the two passes.
	 */
	firstaddr = 0;
	for (;;) {
	    v = firstaddr;	    
#if	SHOW_SPACE
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
#else	SHOW_SPACE
#define valloc(name, type, num) \
	    (name) = (type *)v; v = (caddr_t)((name)+(num))
#define valloclim(name, type, num, lim) \
	    (name) = (type *)v; v = (caddr_t)((lim) = ((name)+(num)))
#endif	SHOW_SPACE
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
	{
	extern struct arptab *arptab;
	extern int arptab_size, arptab_bsiz, arptab_nb;
		arptab_size = arptab_bsiz * arptab_nb;
		valloc(arptab, struct arptab, arptab_size);
	}

	/* 
	 *	Use 5% of memory for buffers, regardless.
	 *	Since these pages are virtual-size pages (larger
	 *	than physical page size), use only one page
	 *	per buffer.
	 */
 	if (bufpages == 0)
		bufpages = atop(mem_size / 20);
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
		 *	Size has been calculated; allocate memory.
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
#if	SHOW_SPACE
	if (show_space)
		printf("bufpages = %d, nbuf = %d, base = %d, residual = %d\n",
				bufpages, nbuf, base, residual);
#endif	SHOW_SPACE

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

	if (ret != KERN_SUCCESS)
		panic("startup: unable to allocate buffer pool");

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
		vm_map_pageable(buffer_map, curbuf, curbuf+thisbsize, FALSE);
	}


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
		extern int	vm_page_free_count;

		nbytes = ptoa(vm_page_free_count);
		printf("available memory = %d.%d%d megabytes.\n", nbytes/MEG,
			((nbytes%MEG)*10)/MEG,
			((nbytes%(MEG/10))*100)/MEG);
		nbytes = ptoa(bufpages);
		printf("using %d buffers containing %d.%d%d megabytes of memory\n",
			nbuf,
			nbytes/MEG,
			((nbytes%MEG)*10)/MEG,
			((nbytes%(MEG/10))*100)/MEG);
	}
	mb_map = kmem_suballoc(kernel_map,
			(vm_offset_t *) &mbutl,
			(vm_offset_t *) &embutl,
			(vm_size_t) (nmbclusters * CLBYTES),
/*			(vm_size_t) (ptoa(nmbclusters)),*/
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

	/*
	 * Clear restart inhibit flags.
	 */
	tocons(TXDB_CWSI);
	tocons(TXDB_CCSI);
#if	VAX6200
	cca->hflag &= ~HFLAG_BOOTIP;	/* reboot in progress */
#endif	VAX6200
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
#if	VAX650 || VAX6200
 	if (cpu == VAX_650 || cpu == VAX_6200) {
 		if (ssclock->ssc_tcr0 & ICCS_INT)
 			return(-1);
 		else
 			return(((time.tv_sec-otime)*60 + lbolt-olbolt)*16667
 			+ ssclock->ssc_tir0 - oicr);
 	} 
#endif	VAX650 || VAX6200

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
	u.u_ar0[PC] = entry + 2;
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
sendsig(p, sig, mask)
	int (*p)(), sig, mask;
{
	register struct sigcontext *scp;
	register int *regs;
	register struct sigframe {
		int	sf_signum;
		int	sf_code;
		struct	sigcontext *sf_scp;
		int	(*sf_handler)();
		int	sf_argcount;
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
	fp->sf_signum = sig;
	if (sig == SIGILL || sig == SIGFPE) {
		fp->sf_code = u.u_code;
		u.u_code = 0;
	} else
		fp->sf_code = 0;
	fp->sf_scp = scp;
	fp->sf_handler = p;
	/*
	 * Build the calls argument frame to be used to call sigreturn
	 */
	fp->sf_argcount = 1;
	fp->sf_scpcopy = scp;
	/*
	 * Build the signal context to be used by sigreturn.
	 */
	scp->sc_onstack = oonstack;
	scp->sc_mask = mask;
	scp->sc_sp = regs[SP];
	scp->sc_fp = regs[FP];
	scp->sc_ap = regs[AP];
	scp->sc_pc = regs[PC];
	scp->sc_ps = regs[PS];
	regs[SP] = (int)fp;
	regs[PS] &= ~(PSL_CM|PSL_FPD);
	regs[PC] = (int)VM_MAX_ADDRESS-SIGCODE_SIZE;
	return;
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
sigreturn()
{
	struct a {
		struct sigcontext *sigcntxp;
	};
	register struct sigcontext *scp;
	register int *regs = u.u_ar0;

	scp = ((struct a *)(u.u_ap))->sigcntxp;
	if (useracc((caddr_t)scp, sizeof (*scp), B_WRITE) == 0)
		return;
	if ((scp->sc_ps & (PSL_MBZ|PSL_IPL|PSL_IS)) != 0 ||
	    (scp->sc_ps & (PSL_PRVMOD|PSL_CURMOD)) != (PSL_PRVMOD|PSL_CURMOD) ||
	    ((scp->sc_ps & PSL_CM) &&
	     (scp->sc_ps & (PSL_FPD|PSL_DV|PSL_FU|PSL_IV)) != 0)) {
		u.u_error = EINVAL;
		return;
	}
	u.u_eosys = JUSTRETURN;
	u.u_onstack = scp->sc_onstack & 01;
	u.u_procp->p_sigmask = scp->sc_mask &~
	    (sigmask(SIGKILL)|sigmask(SIGCONT)|sigmask(SIGSTOP));
	regs[FP] = scp->sc_fp;
	regs[AP] = scp->sc_ap;
	regs[SP] = scp->sc_sp;
	regs[PC] = scp->sc_pc;
	regs[PS] = scp->sc_ps;
}

/* XXX - BEGIN 4.2 COMPATIBILITY */
/*
 * Compatibility with 4.2 chmk $139 used by longjmp()
 */
osigcleanup()
{
	register struct sigcontext *scp;
	register int *regs = u.u_ar0;

	scp = (struct sigcontext *)fuword((caddr_t)regs[SP]);
	if ((int)scp == -1)
		return;
	if (useracc((caddr_t)scp, 3 * sizeof (int), B_WRITE) == 0)
		return;
	u.u_onstack = scp->sc_onstack & 01;
	u.u_procp->p_sigmask = scp->sc_mask &~
	    (sigmask(SIGKILL)|sigmask(SIGCONT)|sigmask(SIGSTOP));
	regs[SP] = scp->sc_sp;
}
/* XXX - END 4.2 COMPATIBILITY */

#ifdef	notdef
dorti()
{
	struct frame frame;
	register int sp;
	register int reg, mask;
	extern int ipcreg[];

	(void) copyin((caddr_t)u.u_ar0[FP], (caddr_t)&frame, sizeof (frame));
	sp = u.u_ar0[FP] + sizeof (frame);
	u.u_ar0[PC] = frame.fr_savpc;
	u.u_ar0[FP] = frame.fr_savfp;
	u.u_ar0[AP] = frame.fr_savap;
	mask = frame.fr_mask;
	for (reg = 0; reg <= 11; reg++) {
		if (mask&1) {
			u.u_ar0[ipcreg[reg]] = fuword((caddr_t)sp);
			sp += 4;
		}
		mask >>= 1;
	}
	sp += frame.fr_spa;
	u.u_ar0[PS] = (u.u_ar0[PS] & 0xffff0000) | frame.fr_psw;
	if (frame.fr_s)
		sp += 4 + 4 * (fuword((caddr_t)sp) & 0xff);
	/* phew, now the rei */
	u.u_ar0[PC] = fuword((caddr_t)sp);
	sp += 4;
	u.u_ar0[PS] = fuword((caddr_t)sp);
	sp += 4;
	u.u_ar0[PS] |= PSL_USERSET;
	u.u_ar0[PS] &= ~PSL_USERCLR;
	u.u_ar0[SP] = (int)sp;
}
#endif

/*
 * Memenable enables the memory controlle corrected data reporting.
 * This runs at regular intervals, turning on the interrupt.
 * The interrupt is turned off, per memory controller, when error
 * reporting occurs.  Thus we report at most once per memintvl.
 */
int	memintvl = MEMINTVL;

memenable()
{
	register struct mcr *mcr;
	register int m;

#if	VAX650 && MACH
	if (cpu == VAX_650) {
		struct ka650_mem *mp = (struct ka650_mem *)mcraddr[0];

		mtpr(MSER, mfpr(MSER) & MSER_ERR);	/* c1 cache & parity */

		c2cntl->cacr |= c2cntl->cacr & CACR_ERR;/* c2 cache parity error */

		mp->mem_csr16 = mp->mem_csr16 & M16_ERR;/* clear memory errors */
		mp->mem_csr17 |= M17_CRD;		/* enable crd */

		mp->mem_dser = mp->mem_dser & DSER_ERR;/* clear qbus nxm's ... */
		return;
	}
#endif	VAX650 && MACH
#if	VAX630
	if (cpu == VAX_630)
	{
		struct ka630cpu *ka630addr = ka630cpu;

		/*
		 *  Simply enable parity on the MicroVax-2 and return.
		 */
		ka630addr->ka630_mser = KA630MSER_PAREN;
 		return;
	}
#endif
#ifdef	VAX8600
	if (cpu == VAX_8600) {
		M8600_ENA;
	} else
#endif
	for (m = 0; m < nmcr; m++) {
		mcr = mcraddr[m];
		switch (mcrtype[m]) {
#if	VAX780
#if	NMACH_MPM > 0
		case M780MA:
			M780MA_ENA(mcr);
			break;
#endif	NMACH_MPM > 0
		case M780C:
			M780C_ENA(mcr);
			break;
		case M780EL:
			M780EL_ENA(mcr);
			break;
		case M780EU:
			M780EU_ENA(mcr);
			break;
#endif
#if	VAX750
		case M750:
			M750_ENA(mcr);
			break;
#endif
#if	VAX730
		case M730:
			M730_ENA(mcr);
			break;
#endif
		}
	}
	if (memintvl > 0)
		timeout(memenable, (caddr_t)0, memintvl*hz);
}

/*
 * Memerr is the interrupt routine for corrected read data
 * interrupts.  It looks to see which memory controllers have
 * unreported errors, reports them, and disables further
 * reporting for a time on those controller.
 */
#if	NMACH_MPM > 0
int	mcrcount = 0;
#endif	NMACH_MPM > 0
memerr()
{
#ifdef	VAX8600
	register int reg11;	/* known to be r11 below */
#endif
	register struct mcr *mcr;
	register int m;

		/* one invocation for all memory controllers */
	switch (cpu) {
#if	VAX630
	case VAX_630:
		return;
#endif
#if	VAX820
	case VAX_820:
		crd_ka820();
		return;
#endif	VAX820
#if	VAX880
	case VAX_880:
		crd_ka88();
		return;
#endif	VAX8800
#if	VAX650
	case VAX_650:
		crd_ka650();
		return;
#endif	VAX650
#if	VAX6200
	case VAX_6200:
		crd_ka62a();
		return;
#endif	VAX6200
#ifdef	VAX8600
	case VAX_8600: {
		int mdecc, mear, mstat1, mstat2, array;

		/*
		 * Scratchpad registers in the Ebox must be read by
		 * storing their ID number in ESPA and then immediately
		 * reading ESPD's contents with no other intervening
		 * machine instructions!
		 *
		 * The asm's below have a number of constants which
		 * are defined correctly in mem.h and mtpr.h.
		 */
#ifdef	lint
		reg11 = 0;
#else
		asm("mtpr $0x27,$0x4e; mfpr $0x4f,r11");
#endif
		mdecc = reg11;	/* must acknowledge interrupt? */
		if (M8600_MEMERR(mdecc)) {
			asm("mtpr $0x2a,$0x4e; mfpr $0x4f,r11");
			mear = reg11;
			asm("mtpr $0x25,$0x4e; mfpr $0x4f,r11");
			mstat1 = reg11;
			asm("mtpr $0x26,$0x4e; mfpr $0x4f,r11");
			mstat2 = reg11;
			array = M8600_ARRAY(mear);

			printf("mcr0: ecc error, addr %x (array %d) syn %x\n",
				M8600_ADDR(mear), array, M8600_SYN(mdecc));
			printf("\tMSTAT1 = %b\n\tMSTAT2 = %b\n",
				    mstat1, M8600_MSTAT1_BITS,
				    mstat2, M8600_MSTAT2_BITS);
			M8600_INH;
		}
	}
	return;
#endif
	}
#if	NMACH_MPM
	mcrcount++;
#endif	NMACH_MPM
		/* one invocation per memory controllers */
	for (m = 0; m < nmcr; m++) {
		mcr = mcraddr[m];
		switch (mcrtype[m]) {
#if	VAX780
#if	NMACH_MPM > 0
		case M780MA:
			if (!m)
				printf("memerr: #%d: SBIER = %x\n", mcrcount, mfpr(SBIER));

			if (M780MA_ERR(mcr)) {
				int		m780ma_addr;
				int		m780ma_syn;

				printf("mcr%d: %s error",
				    m, (mfpr(SBIER)&(1<<14)) ? "soft ecc" : "parity");
				m780ma_addr = M780MA_ADDR(mcr);
				m780ma_syn = M780MA_SYN(mcr);
				printf(" addr %x syn %x\n", m780ma_addr, m780ma_syn);
				if (mfpr(SBIER) & (1 << 13)) {
					printf("double bit memory error\n");
					asm("halt");
				}
				/*
				 * but what is the right thing to do for slaves
				 * since the time out code can not enable the
				 * error reporting again so ...
				 */
#if	0
				M780MA_INH(mcr);
#endif	0
			}
			break;

#endif	NMACH_MPM > 0
		case M780C:
			if (M780C_ERR(mcr)) {
				printf("mcr%d: soft ecc addr %x syn %x\n",
				    m, M780C_ADDR(mcr), M780C_SYN(mcr));
#ifdef	TRENDATA
				memlog(m, mcr);
#endif
				M780C_INH(mcr);
			}
			break;

		case M780EL:
			if (M780EL_ERR(mcr)) {
				printf("mcr%d: soft ecc addr %x syn %x\n",
				    m, M780EL_ADDR(mcr), M780EL_SYN(mcr));
				M780EL_INH(mcr);
			}
			break;

		case M780EU:
			if (M780EU_ERR(mcr)) {
				printf("mcr%d: soft ecc addr %x syn %x\n",
				    m, M780EU_ADDR(mcr), M780EU_SYN(mcr));
				M780EU_INH(mcr);
			}
			break;
#endif
#if	VAX750
		case M750:
			if (M750_ERR(mcr)) {
				struct mcr amcr;
				amcr.mc_reg[0] = mcr->mc_reg[0];
				printf("mcr%d: %s",
				    m, (amcr.mc_reg[0] & M750_UNCORR) ?
				    "hard error" : "soft ecc");
				printf(" addr %x syn %x\n",
				    M750_ADDR(&amcr), M750_SYN(&amcr));
				M750_INH(mcr);
			}
#if	NGFB > 0
			if (numgfb && gfb_preg->csr&GFB_PERR) {
				printf("gfb0: frame parity err, csr = 0x%x\n",
					gfb_preg->csr);
				gfb_preg->csr |= GFB_PERR; /* Clear it */
			}
#endif	NGFB
			break;
#endif
#if	VAX730
		case M730: {
			struct mcr amcr;

			/*
			 * Must be careful on the 730 not to use invalid
			 * instructions in I/O space, so make a copy;
			 */
			amcr.mc_reg[0] = mcr->mc_reg[0];
			amcr.mc_reg[1] = mcr->mc_reg[1];
			if (M730_ERR(&amcr)) {
				printf("mcr%d: %s",
				    m, (amcr.mc_reg[1] & M730_UNCORR) ?
				    "hard error" : "soft ecc");
				printf(" addr %x syn %x\n",
				    M730_ADDR(&amcr), M730_SYN(&amcr));
				M730_INH(mcr);
			}
			break;
		}
#endif
		}
	}
}

#ifdef	TRENDATA
/*
 * Figure out what chip to replace on Trendata boards.
 * Assumes all your memory is Trendata or the non-Trendata
 * memory never fails..
 */
struct {
	u_char	m_syndrome;
	char	m_chip[4];
} memlogtab[] = {
	0x01,	"C00",	0x02,	"C01",	0x04,	"C02",	0x08,	"C03",
	0x10,	"C04",	0x19,	"L01",	0x1A,	"L02",	0x1C,	"L04",
	0x1F,	"L07",	0x20,	"C05",	0x38,	"L00",	0x3B,	"L03",
	0x3D,	"L05",	0x3E,	"L06",	0x40,	"C06",	0x49,	"L09",
	0x4A,	"L10",	0x4c,	"L12",	0x4F,	"L15",	0x51,	"L17",
	0x52,	"L18",	0x54,	"L20",	0x57,	"L23",	0x58,	"L24",
	0x5B,	"L27",	0x5D,	"L29",	0x5E,	"L30",	0x68,	"L08",
	0x6B,	"L11",	0x6D,	"L13",	0x6E,	"L14",	0x70,	"L16",
	0x73,	"L19",	0x75,	"L21",	0x76,	"L22",	0x79,	"L25",
	0x7A,	"L26",	0x7C,	"L28",	0x7F,	"L31",	0x80,	"C07",
	0x89,	"U01",	0x8A,	"U02",	0x8C,	"U04",	0x8F,	"U07",
	0x91,	"U09",	0x92,	"U10",	0x94,	"U12",	0x97, 	"U15",
	0x98,	"U16",	0x9B,	"U19",	0x9D,	"U21",	0x9E, 	"U22",
	0xA8,	"U00",	0xAB,	"U03",	0xAD,	"U05",	0xAE,	"U06",
	0xB0,	"U08",	0xB3,	"U11",	0xB5,	"U13",	0xB6,	"U14",
	0xB9,	"U17",	0xBA,	"U18",	0xBC,	"U20",	0xBF,	"U23",
	0xC1,	"U25",	0xC2,	"U26",	0xC4,	"U28",	0xC7,	"U31",
	0xE0,	"U24",	0xE3,	"U27",	0xE5,	"U29",	0xE6,	"U30"
};

memlog (m, mcr)
	int m;
	struct mcr *mcr;
{
	register i;

	switch (mcrtype[m]) {

#if	VAX780
	case M780C:
	for (i = 0; i < (sizeof (memlogtab) / sizeof (memlogtab[0])); i++)
		if ((u_char)(M780C_SYN(mcr)) == memlogtab[i].m_syndrome) {
			printf (
	"mcr%d: replace %s chip in %s bank of memory board %d (0-15)\n",
				m,
				memlogtab[i].m_chip,
				(M780C_ADDR(mcr) & 0x8000) ? "upper" : "lower",
				(M780C_ADDR(mcr) >> 16));
			return;
		}
	printf ("mcr%d: multiple errors, not traceable\n", m);
	break;
#endif
	}
}
#endif

#include <mach/machine.h>
halt_cpu()
{
int cpun = cpu_number();

	machine_slot[cpun].running = FALSE;
	switch (cpu) {
#if	VAX6200
	case VAX_6200:
		cca_halt(cpun);
		break;
#endif	VAX6200
#if	VAX820
	case VAX_820:
		ka820_halt(cpun);
		break;
#endif	VAX820
	default:
		asm("halt");
		break;
	}
}

int	waittime = -1;

boot(paniced, arghowto)
	int paniced, arghowto;
{
	register int howto;		/* r11 == how to boot */
	register int devtype;		/* r10 == major of root dev */
#if	MACH_RFS
	extern void	rfs_boot();
#endif	MACH_RFS
	register int i;
	extern	should_exit[];
	extern	HIGH;

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
		/*
		 * If we've been adjusting the clock, the todr
		 * will be out of synch; adjust it now.
		 */
		resettodr();
	}
	splhigh();			/* extreme priority */
	devtype = major(rootdev);
	for (i = 0; i < NCPUS; i++) {
		struct machine_slot *mp = &machine_slot[i];
		if (!mp->running)
			continue;
		if (i == master_cpu)
			continue;
		should_exit[i] = TRUE;
#if	VAX6200
		if (cpu == VAX_6200) {
			cca_snarf(i, 0);
			cca_snarf(i, 0);
			printf("Processor %d Halted.\n", i);
		}
#endif	VAX6200
	}
	if (howto&RB_HALT) {
		switch (cpu)
		{
#if	VAX650 || VAX630
		    case VAX_650:
		    case VAX_630:
			set_cpmbx(CPMBX_HALT);
			printf("\nHalting...\n");
			for (;;)
				asm("halt");
			/*NOTREACHED*/
#endif	VAX650 || VAX630
#if	VAX6200
		    case VAX_6200:
			printf("\nHalting...\n");
			for (;;)
				cca_halt(master_cpu);
#endif	VAX6200
		    default:
			printf("halting (in tight loop); hit");
#if	VAX1
			if (cpu == VAX_1)
				printf(" HALT button\n\n");
			else
#endif	VAX1
				printf("\n\t^P\n\tHALT\n\n");
			break;
		}
		for (;;)
			;
	} else {
		if (paniced == RB_PANIC) {
			doadump();		/* TXDB_BOOT's itself */
			/*NOTREACHED*/
		}
		tocons(TXDB_BOOT);
	}
#if	VAX750 || VAX730 || VAX650 || VAX630
	if (cpu != VAX_780)
 		{ asm("movl r11,r5"); }		/* boot flags go in r5 */
#if	VAX650 || VAX630
	if (cpu == VAX_650 || cpu == VAX_630)
		set_cpmbx(CPMBX_REBOOT);
#endif	VAX650 || VAX630
#endif	VAX750 || VAX730 || VAX650 || VAX630
#if	VAX820
	if (cpu == VAX_820)
		ka820_reboot(master_cpu);
#endif	VAX820
#if	VAX6200
	if (cpu == VAX_6200)
		cca_reboot(master_cpu);
#endif	VAX6200
	for (;;)
		asm("halt");
	/*NOTREACHED*/
}

tocons(c)
{
	register oldmask;

	while (((oldmask = mfpr(TXCS)) & TXCS_RDY) == 0)
		continue;

	switch (cpu) {

	default:
		c |= TXDB_CONS;
		break;

#if	VAX8600
	case VAX_8600:
		mtpr(TXCS, TXCS_LCONS | TXCS_WMASK);
		while ((mfpr(TXCS) & TXCS_RDY) == 0)
			continue;
		break;
#endif
	}

	mtpr(TXDB, c);

#if	VAX8600
	switch (cpu) {

	case VAX_8600:
		while ((mfpr(TXCS) & TXCS_RDY) == 0)
			continue;
		mtpr(TXCS, oldmask | TXCS_WMASK);
		break;
	}
#endif
}

int	dumpmag = 0x8fca0101;	/* magic number for savecore */
int	dumpsize = 0;		/* also for savecore */
/*
 * Doadump comes here after turning off memory management and
 * getting on the dump stack, either when called above, or by
 * the auto-restart code.
 */
dumpsys()
{
#if	MACH_LOAD
	struct bdevsw *physbdevsw;
#define phys(t,a) ((t) ( ( ((int)(a)) & 0x7fffffff) + loadpt))
 
	physbdevsw = phys(struct bdevsw *, bdevsw);
#endif	MACH_LOAD

	rpb.rp_flag = 1;
#ifdef	notdef
	if ((minor(dumpdev)&07) != 1)
		return;
#endif
	dumpsize = btoc(mem_size);
	printf("\ndumping to dev %x, offset %d\n", dumpdev, dumplo);
	printf("dump ");
#if	MACH_LOAD
	switch ((*phys(int (*)(),physbdevsw[major(dumpdev)].d_dump))(dumpdev)) {
#else	MACH_LOAD
	switch ((*bdevsw[major(dumpdev)].d_dump)(dumpdev)) {
#endif	MACH_LOAD

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
		printf("i/o error");
		break;

	default:
		printf("succeeded");
		break;
	}
#if	VAX630
	/*
	 *	This doesn't really belong here, but if we are called
	 *	from the autorestart it is inconvienent to do this
	 *	in locore (and it doesn't hurt to do it here).
	 *
	 *	Perhaps this could be hacked into tocons.
	 */
	if (cpu == VAX_630)
		*((short *)0x200B801C) = CPMBX_REBOOT;
#endif	VAX630
#if	VAX650
	if (cpu == VAX_650)
		*cpmbx = CPMBX_REBOOT;
#endif	VAX650
}

/*
 * Machine check error recovery code.
 * Print out the machine check frame and then give up.
 */
#if	VAX8600
#define NMC8600	7
char *mc8600[] = {
	"unkn type",	"fbox error",	"ebox error",	"ibox error",
	"mbox error",	"tbuf error",	"mbox 1D error"
};
/* codes for above */
#define MC_FBOX		1
#define MC_EBOX		2
#define MC_IBOX		3
#define MC_MBOX		4
#define MC_TBUF		5
#define MC_MBOX1D	6

/* error bits */
#define MBOX_FE		0x8000		/* Mbox fatal error */
#define FBOX_SERV	0x10000000	/* Fbox service error */
#define IBOX_ERR	0x2000		/* Ibox error */
#define EBOX_ERR	0x1e00		/* Ebox error */
#define MBOX_1D		0x81d0000	/* Mbox 1D error */
#define EDP_PE		0x200
#endif

#if	defined(VAX780) || defined(VAX750)
char *mc780[] = {
	"cp read",	"ctrl str par",	"cp tbuf par",	"cp cache par",
	"cp rdtimo", 	"cp rds",	"ucode lost",	0,
	0,		0,		"ib tbuf par",	0,
	"ib rds",	"ib rd timo",	0,		"ib cache par"
};
#define MC750_TBERR	2		/* type code of cp tbuf par */
#define MC750_TBPAR	4		/* tbuf par bit in mcesr */
#endif

#if	VAX730
#define NMC730	12
char *mc730[] = {
	"tb par",	"bad retry",	"bad intr id",	"cant write ptem",
	"unkn mcr err",	"iib rd err",	"nxm ref",	"cp rds",
	"unalgn ioref",	"nonlw ioref",	"bad ioaddr",	"unalgn ubaddr",
};
#endif
#if	VAX650
#endif	VAX650
#if	VAX630
#define NMC630	10
#endif

/*
 * Frame for each cpu
 */
struct mc780frame {
	int	mc8_bcnt;		/* byte count == 0x28 */
	int	mc8_summary;		/* summary parameter (as above) */
	int	mc8_cpues;		/* cpu error status */
	int	mc8_upc;		/* micro pc */
	int	mc8_vaviba;		/* va/viba register */
	int	mc8_dreg;		/* d register */
	int	mc8_tber0;		/* tbuf error reg 0 */
	int	mc8_tber1;		/* tbuf error reg 1 */
	int	mc8_timo;		/* timeout address divided by 4 */
	int	mc8_parity;		/* parity */
	int	mc8_sbier;		/* sbi error register */
	int	mc8_pc;			/* trapped pc */
	int	mc8_psl;		/* trapped psl */
};
struct mc750frame {
	int	mc5_bcnt;		/* byte count == 0x28 */
	int	mc5_summary;		/* summary parameter (as above) */
	int	mc5_va;			/* virtual address register */
	int	mc5_errpc;		/* error pc */
	int	mc5_mdr;
	int	mc5_svmode;		/* saved mode register */
	int	mc5_rdtimo;		/* read lock timeout */
	int	mc5_tbgpar;		/* tb group parity error register */
	int	mc5_cacherr;		/* cache error register */
	int	mc5_buserr;		/* bus error register */
	int	mc5_mcesr;		/* machine check status register */
	int	mc5_pc;			/* trapped pc */
	int	mc5_psl;		/* trapped psl */
};
struct mc730frame {
	int	mc3_bcnt;		/* byte count == 0xc */
	int	mc3_summary;		/* summary parameter */
	int	mc3_parm[2];		/* parameter 1 and 2 */
	int	mc3_pc;			/* trapped pc */
	int	mc3_psl;		/* trapped psl */
};
struct mc630frame {
	int	mc63_bcnt;		/* byte count == 0xc */
	int	mc63_summary;		/* summary parameter */
	int	mc63_mrvaddr;		/* most recent vad */
	int	mc63_istate;		/* internal state */
	int	mc63_pc;			/* trapped pc */
	int	mc63_psl;		/* trapped psl */
};
#if	VAX1
struct mc1frame {
	int	mc1_bcnt;		/* byte count == 0xc */
	int	mc1_summary;		/* summary parameter */
	int	mc1_parm[2];		/* parameter 1 and 2 */
	int	mc1_pc;			/* trapped pc */
	int	mc1_psl;		/* trapped psl */
};
#endif	VAX1
struct mc8600frame {
	int	mc6_bcnt;		/* byte count == 0x58 */
	int	mc6_ehmsts;
	int	mc6_evmqsav;
	int	mc6_ebcs;
	int	mc6_edpsr;
	int	mc6_cslint;
	int	mc6_ibesr;
	int	mc6_ebxwd1;
	int	mc6_ebxwd2;
	int	mc6_ivasav;
	int	mc6_vibasav;
	int	mc6_esasav;
	int	mc6_isasav;
	int	mc6_cpc;
	int	mc6_mstat1;
	int	mc6_mstat2;
	int	mc6_mdecc;
	int	mc6_merg;
	int	mc6_cshctl;
	int	mc6_mear;
	int	mc6_medr;
	int	mc6_accs;
	int	mc6_cses;
	int	mc6_pc;			/* trapped pc */
	int	mc6_psl;		/* trapped psl */
};

machinecheck(cmcf)
	caddr_t cmcf;
{
	register u_int type = ((struct mc780frame *)cmcf)->mc8_summary;

	printf("machine check %x: ", type);
	switch (cpu) {
#if	VAX8600
	case VAX_8600: {
		register struct mc8600frame *mcf = (struct mc8600frame *)cmcf;

		if (mcf->mc6_ebcs & MBOX_FE)
			mcf->mc6_ehmsts |= MC_MBOX;
		else if (mcf->mc6_ehmsts & FBOX_SERV)
			mcf->mc6_ehmsts |= MC_FBOX;
		else if (mcf->mc6_ebcs & EBOX_ERR) {
			if (mcf->mc6_ebcs & EDP_PE)
				mcf->mc6_ehmsts |= MC_MBOX;
			else
				mcf->mc6_ehmsts |= MC_EBOX;
		} else if (mcf->mc6_ehmsts & IBOX_ERR)
			mcf->mc6_ehmsts |= MC_IBOX;
		else if (mcf->mc6_mstat1 & M8600_TB_ERR)
			mcf->mc6_ehmsts |= MC_TBUF;
		else if ((mcf->mc6_cslint & MBOX_1D) == MBOX_1D)
			mcf->mc6_ehmsts |= MC_MBOX1D;

		type = mcf->mc6_ehmsts & 0x7;
		if (type < NMC8600)
			printf("machine check %x: %s", type, mc8600[type]);
		printf("\n");
		printf("\tehm.sts %x evmqsav %x ebcs %x edpsr %x cslint %x\n",
		    mcf->mc6_ehmsts, mcf->mc6_evmqsav, mcf->mc6_ebcs,
		    mcf->mc6_edpsr, mcf->mc6_cslint);
		printf("\tibesr %x ebxwd %x %x ivasav %x vibasav %x\n",
		    mcf->mc6_ibesr, mcf->mc6_ebxwd1, mcf->mc6_ebxwd2,
		    mcf->mc6_ivasav, mcf->mc6_vibasav);
		printf("\tesasav %x isasav %x cpc %x mstat %x %x mdecc %x\n",
		    mcf->mc6_esasav, mcf->mc6_isasav, mcf->mc6_cpc,
		    mcf->mc6_mstat1, mcf->mc6_mstat2, mcf->mc6_mdecc);
		printf("\tmerg %x cshctl %x mear %x medr %x accs %x cses %x\n",
		    mcf->mc6_merg, mcf->mc6_cshctl, mcf->mc6_mear,
		    mcf->mc6_medr, mcf->mc6_accs, mcf->mc6_cses);
		printf("\tpc %x psl %x\n", mcf->mc6_pc, mcf->mc6_psl);
		mtpr(EHSR, 0);
		break;
	};
#endif
#if	VAX780
	case VAX_780: {
		register struct mc780frame *mcf = (struct mc780frame *)cmcf;

		register int sbifs;
		printf("%s%s\n", mc780[type&0xf],
		    (type&0xf0) ? " abort" : " fault"); 
		printf("\tcpues %x upc %x va/viba %x dreg %x tber %x %x\n",
		   mcf->mc8_cpues, mcf->mc8_upc, mcf->mc8_vaviba,
		   mcf->mc8_dreg, mcf->mc8_tber0, mcf->mc8_tber1);
		sbifs = mfpr(SBIFS);
		printf("\ttimo %x parity %x sbier %x pc %x psl %x sbifs %x\n",
		   mcf->mc8_timo*4, mcf->mc8_parity, mcf->mc8_sbier,
		   mcf->mc8_pc, mcf->mc8_psl, sbifs);
		/* THE FUNNY BITS IN THE FOLLOWING ARE FROM THE ``BLACK */
		/* BOOK'' AND SHOULD BE PUT IN AN ``sbi.h'' */
		mtpr(SBIFS, sbifs &~ 0x2000000);
		mtpr(SBIER, mfpr(SBIER) | 0x70c0);
		break;
	}
#endif
#if	VAX750
	case VAX_750: {
		register struct mc750frame *mcf = (struct mc750frame *)cmcf;

		int mcsr = mfpr(MCSR);
		printf("%s%s\n", mc780[type&0xf],
		    (type&0xf0) ? " abort" : " fault"); 
		mtpr(TBIA, 0);
		mtpr(MCESR, 0xf);
		printf("\tva %x errpc %x mdr %x smr %x rdtimo %x tbgpar %x cacherr %x\n",
		    mcf->mc5_va, mcf->mc5_errpc, mcf->mc5_mdr, mcf->mc5_svmode,
		    mcf->mc5_rdtimo, mcf->mc5_tbgpar, mcf->mc5_cacherr);
		printf("\tbuserr %x mcesr %x pc %x psl %x mcsr %x\n",
		    mcf->mc5_buserr, mcf->mc5_mcesr, mcf->mc5_pc, mcf->mc5_psl,
		    mcsr);
		if (type == MC750_TBERR && (mcf->mc5_mcesr&0xe) == MC750_TBPAR){
			printf("tbuf par: flushing and returning\n");
			return;
		}
		break;
		}
#endif
#if	VAX730
	case VAX_730: {
		register struct mc730frame *mcf = (struct mc730frame *)cmcf;

		if (type < NMC730)
			printf("%s", mc730[type]);
		printf("\n");
		printf("params %x,%x pc %x psl %x mcesr %x\n",
		    mcf->mc3_parm[0], mcf->mc3_parm[1],
		    mcf->mc3_pc, mcf->mc3_psl, mfpr(MCESR));
		mtpr(MCESR, 0xf);
		break;
		}
#endif
#if	VAX630
	case VAX_630: {
		register struct ka630cpu *ka630addr = ka630cpu;
		register struct mc630frame *mcf = (struct mc630frame *)cmcf;
		printf("vap %x istate %x pc %x psl %x\n",
		    mcf->mc63_mrvaddr, mcf->mc63_istate,
		    mcf->mc63_pc, mcf->mc63_psl);
		if (ka630addr->ka630_mser & KA630MSER_MERR) {
			printf("mser=0x%x ",ka630addr->ka630_mser);
			if (ka630addr->ka630_mser & KA630MSER_CPUER)
				printf("page=%d",ka630addr->ka630_cear);
			if (ka630addr->ka630_mser & KA630MSER_DQPE)
				printf("page=%d",ka630addr->ka630_dear);
			printf("\n");
		}
		break;
		}
#endif
#if	VAX1
	case VAX_1: {
		register struct mc1frame *mcf = (struct mc1frame *)cmcf;
		printf("params %x,%x pc %x psl %x mcesr %x\n",
		    mcf->mc1_parm[0], mcf->mc1_parm[1],
		    mcf->mc1_pc, mcf->mc1_psl, mfpr(MCESR));
		mtpr(MCESR, 0xf);
		break;
		}
#endif	VAX1
#if	VAX650
	case VAX_650:
		mchk_ka650(cmcf);
		break;
#endif
#if	VAX820
	case VAX_820:
		mchk_ka820(cmcf);
		break;
#endif	VAX820
#if	VAX8800
	case VAX_8800:
		mchk_ka88(cmcf);
		return;
#endif	VAX8800
#if	VAX6200
	case VAX_6200:
		mchk_ka62a(cmcf);
		return;			/* suprise -- not all mchks are fatal */
#endif	VAX6200
	}
	memerr();
	panic("mchk");
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
#if	VAX650 || VAX6200
	if (cpu == VAX_650 || cpu == VAX_6200) {
 		t = ssclock->ssc_tir0;
 		if (t < -tick / 2 && (ssclock->ssc_tcr0 & ICCS_INT))
 			t += tick;
	} else {
#endif	VAX650 || VAX6200
	t =  mfpr(ICR);
	if (t < -tick / 2 && (mfpr(ICCS) & ICCS_INT))
		t += tick;
#if	VAX650 || VAX6200
	}
#endif	VAX650 || VAX6200
	tvp->tv_usec += tick + t;
	if (tvp->tv_usec >= 1000000) {
		tvp->tv_sec++;
		tvp->tv_usec -= 1000000;
	}
	if (tvp->tv_sec == lasttime.tv_sec &&
	    tvp->tv_usec <= lasttime.tv_usec &&
	    (tvp->tv_usec = lasttime.tv_usec + 1) >= 1000000) {
		tvp->tv_sec++;
		tvp->tv_usec -= 1000000;
	}
	lasttime = *tvp;
	splx(s);
}

physstrat(bp, strat, prio)
	struct buf *bp;
	int (*strat)(), prio;
{
	int s;

	(*strat)(bp);
	/* pageout daemon doesn't wait for pushed pages */
	if (bp->b_flags & B_DIRTY)
		return;
	s = splbio();
	while ((bp->b_flags & B_DONE) == 0)
		sleep((caddr_t)bp, prio);
	splx(s);
}

initcpu()
{
	/*
	 * Enable cache.
	 */
	switch (cpu) {

#if	VAX780
	case VAX_780:
		mtpr(SBIMT, 0x200000);
		break;
#endif
#if	VAX750
	case VAX_750:
		mtpr(CADR, 0);
		return;
#endif
#if	VAX8600
	case VAX_8600:
		mtpr(CSWP, 3);
		break;
#endif
#if	VAX650
	case VAX_650:
/*
 * ka650_init();
 * is done above.  See the comment.
 */
		return;
#endif
#if	VAX820
	case VAX_820:
		ka820_init();
		return;
#endif	VAX820
#if	VAX8800
	case VAX_8800:
		ka88_init();
		return;
#endif	VAX8800
#if	VAX6200
	case VAX_6200:
		ka62a_init();
		return;
#endif	VAX6200
	default:
		break;
	}

	/*
	 * Enable floating point accelerator if it exists
	 * and has control register.
	 */
	switch(cpu) {

#if	VAX8600 || VAX780
	case VAX_780:
	case VAX_8600:
		if ((mfpr(ACCS) & 0xff) != 0) {
			printf("Enabling FPA\n");
			mtpr(ACCS, 0x8000);
		}
#endif
	default:
		break;
	}
}

#if	VAX6200
#include <vax/bi_node.h>
#include <vaxnb/node.h>
#endif	VAX6200

wtime(pc, psl, pcbp)
int (*pc)();
struct pcb *pcbp;
{
#if	VAX6200
	register struct ka62a *cpp = cpunode[cpu_number()].addr62;
	extern int bi_badaddr(), bi_badaddr_end();
	if (cpu == VAX_6200) {
		if (cpp->ber & XMIBER_WEI) {
			cpp->ber = (cpp->ber & XMIBER_ERR) | XMIBER_WEI;
			slave_attn(pc, psl, pcbp);
			return;
		} else if ((u_long) pc < (u_long) bi_badaddr_end &&
			   (u_long) pc > (u_long) bi_badaddr) {
			cpp->ber = cpp->ber & XMIBER_ERR;
			return;
		} else {
			printf("real timeout\n");
			pka62a(cpp);
			cpp->ber = cpp->ber & XMIBER_ERR;
		}
	}
#endif	VAX6200
	printf("write timeout pc %x, psl %x\n", pc, psl);
	panic("wtimo");
}
