/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	machdep.c,v $
 * Revision 2.24  91/10/29  14:09:47  mja
 * 	Added a check of mp->m_bufp in guard around dounmount() in
 * 	boot().
 * 	[91/09/25            berman]
 * 
 * Revision 2.23  91/04/11  10:05:27  mbj
 * 	Conditionalized changes since non-VFS case doesn't have
 * 	dounmount().
 * 	[91/04/11            berman]
 * 	Added some code in boot() to take care of unmounting all the
 * 	filesystems when shutting down.
 * 	[91/02/15            berman]
 * 
 * Revision 2.22  90/12/18  12:59:34  berman
 * 	Moved actual declaration of iopbmap to here from mbvar.h.
 * 	[90/12/18            berman]
 * 
 * Revision 2.21  90/07/03  16:48:04  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:13:55  mrt]
 * 
 * Revision 2.20  90/04/28  00:03:03  jjc
 * 	Modified code in startup() that gives back frame buffer memory
 * 	to work for the SunOS 4.0 boot program which loads big kernels
 * 	around the frame buffer.
 * 	Moved warning that kernel overlaps frame buffer and changed it
 * 	to panic if the frame buffer is really going to be used and the
 * 	kernel has been loaded on top of it.
 * 	[90/04/23            jjc]
 * 
 * Revision 2.19  90/03/30  16:33:18  rpd
 * 	Updated ether_kmem_suballoc to use vm_submap_object.
 * 	[90/03/30            rpd]
 * 
 * Revision 2.18  89/10/11  14:49:52  dlb
 * 	New vm_map_pageable calling sequence.
 * 	[89/10/07            dlb]
 * 
 * Revision 2.17  89/06/03  15:41:47  jsb
 * 	If NBC then only allocate a few (16) buffers.
 * 	[89/06/03  12:27:27  jsb]
 * 
 * 	For NFS, allocate buffer pool data in ethernet-accessable space so
 * 	that file data can be passed over the wire without copying.
 * 	Replaced my_kmem_suballoc with ether_kmem_suballoc which hides
 * 	placement details (since it is called from mfs_init as well).
 * 	[89/06/02  18:33:31  jsb]
 * 
 * Revision 2.16  89/05/11  14:42:32  gm0w
 * 	Changed size of bufpages from 10% of first 4 meg to 10% of first
 * 	8 meg and 20% of remaining memory. Also removed final unused arg
 * 	from the kmem_alloc call in zmemall.
 * 	[89/05/09            mrt]
 * 
 * Revision 2.15  89/03/16  12:21:13  gm0w
 * 	try again
 * 
 * Revision 2.14  89/03/16  00:33:45  mrt
 * 	Changed include of sys/rfs.h to rfs/rfs.h
 * 	[89/03/16            mrt]
 * 
 * Revision 2.13  89/03/09  21:36:18  rpd
 * 	More cleanup.
 * 
 * Revision 2.12  89/02/25  19:44:32  gm0w
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 * Revision 2.11  89/01/31  17:29:10  rpd
 * 	Added boothowto, maxmem declarations.
 * 	(The ones in sys/systm.h are "extern" now.)
 * 
 * Revision 2.10  89/01/17  02:11:25  rpd
 * 	Changed file buffers from 10% to 5% of memory
 * 	due to popular demand.
 * 	[89/01/16            mrt]
 * 
 * Revision 2.9  88/12/19  02:49:40  mwyoung
 * 	Remove lint.
 * 	[88/12/17            mwyoung]
 * 	
 * 	Use unclaimed frame buffer physical memory.
 * 	[88/12/15            mwyoung]
 * 	
 * 	Account for screen memory reservation in <sun3/pmap.c>.
 * 	Currently, reserved pages that are not used (e.g., because
 * 	no screen is present, or it doesn't use the memory) are
 * 	not placed on the free list.
 * 	[88/12/13  03:26:49  mwyoung]
 * 
 * Revision 2.8  88/12/08  15:36:59  mikeg
 * 	Changed startup() such that the priority is not dropped
 * 	at the end of the routine.  This change is necessary to
 * 	run the new SCSI drivers from SunOS 3.5 according to
 * 	Jonathan Chew.
 * 	[88/11/30  15:51:55  mikeg]
 * 
 * Revision 2.6  88/11/21  16:57:32  rvb
 * 	Make sentinel entry a non_reserved pmeg (iff one has to be
 * 	allocated).
 * 	[88/11/11            rvb]
 * 
 * Revision 2.5  88/09/27  17:31:19  rvb
 * 	Fixed Log
 * 
 * Revision 2.4  88/09/27  16:07:38  rvb
 * 	23-Sep-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	valloc arptab
 * 	[88/09/27  15:54:24  rvb]
 * 
 * 17-May-88  David Golub (dbg) at Carnegie-Mellon University
 *	Change frame-buffer loop to check for permanently allocated
 *	pages (we have really BIG kernels(!)).
 *
 * 12-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Free FPA context of current thread in setregs().
 *	Changed setregs() to test FPA_USED bit in pcb_fpa_flags to
 *	see if FPA is being used.
 *
 * 11-Feb-88  David Golub (dbg) at Carnegie-Mellon University
 *	Fix loop to remove/restore frame buffer pages to account for any
 *	pages that may already be in use.
 *
 *  5-Feb-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Revised for new pmap.[ch]:
 *		struct pte-> struct pme
 *
 * 27-Jan-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Initialize Sun kernel memory allocator after setting up
 *	mbuf map.
 *
 * 15-Dec-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Changes to buffer allocation:
 *		1) nbuf == bufpages since MAXBSIZE == hardware size
 *		2) bufpages = 10% to 4 meg then 20% because of 1) [ie.
 *			frags take full buffers]
 *
 * 04-Oct-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added changes for Sun 3/{60,110}.
 *
 *  3-Sep-87  David Golub (dbg) at Carnegie-Mellon University
 *	Removed arg_zone and user_pt_map.  Removed obsolete options:
 *	CS_COMPAT, CS_IPC, MACH_MP without MACH_VM, MACH_TIME, MACH_REMOTE.
 *	Removed allocation of swapmap and swbuf for MACH.
 *	Converted includes to new naming scheme.
 *
 * 24-Aug-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Drop priority at end of startup().
 * 
 * 26-Jun-87  William Bolosky (bolosky) at Carnegie-Mellon University
 *	Made QUOTA a #if-type option.
 *
 * 25-Jun-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added code for Sun 3/260 to deal with cache and ecc memory.
 *	Made sure to set context before flushing so the right
 *	memory is flushed.
 *
 * 10-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Flush pages from the virtual cache as necessary in physstrat.
 *
 * 26-Mar-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Created my own version of kmem_suballoc() that allows you
 *	to specify the lower bound of the submap and used it to
 *	set up mbuf map somewhere after 0x0F000000 so the Lance
 *	ethernet chip can get at mbufs.
 *	[ V5.1(F8) ]
 *
 * 25-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	No longer try clearing the object cache in boot, this is done
 *	automatically by vm_object_shutdown.
 *
 * 24-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Enable cache on Sun-3/2xx.
 *
 * 23-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Removed cpu_number routine... it is now a macro.
 *
 * 22-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Flushed MACH_ACC.
 *
 * 28-Jan-87  David Golub (dbg) and Jonathan J. Chew (jjc)
 *		at Carnegie-Mellon University
 *	Update "vm_page_free_count" when pulling off or putting
 *	back frame buffer pages.
 *	
 * 14-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Flushed MACH_SEM.
 *
 *  8-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Flushed mpq stuff.
 *
 * 29-Oct-86  David Golub (dbg) at Carnegie-Mellon University
 *	Made sure that memory allocated for IOPB isn't part of
 *	managed physical memory.
 *
 * 24-Oct-86  David Golub (dbg) at Carnegie-Mellon University
 *	Merged in changes from VAX version:
 *	Removed MACH_SHM, WB_ML, thread_table, task_table
 *	call vm_object_cache_clear at reboot (before syncing disks)
 *	Remove MACH_ACC conditional on splitting the user-readable
 *	portion of the valloc'd structures.
 *	Define fp_threads here rather than in machine-independent
 *	code.
 *	Added microtime() routine.
 *
 * 21-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Moved uniqtime() from sys/kern_clock.c.
 *
 * 30-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Allocated 1 megabyte for "user_pt_map".
 *
 * 11-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Rewrote "buscheck" routine to use Mach VM.
 *	Added "sigreturn" routine which just calls "sigcleanup".
 *	Use "phys_map_vaddr1" as a temporary place to make things in instead
 *	of "CADDR1".
 *
 *  4-Aug-86  David Golub (dbg) at Carnegie-Mellon University
 *	Modified "icode" routine to use Mach vm routines to create user stack.
 *
 *  4-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Replaced all occurences of "romp" with "sunromp" to avoid
 *	name conflict with IBM PC RT "romp".
 *
 * 31-Jul-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added code to reserve pages for frame buffer which lies in the middle
 *	of physical memory.
 *
 * 17-Jun-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Modified for Mach.
 *
 */

#ifndef	lint
static	char sccsid[] = "@(#)machdep.c 1.1 86/02/03 Copyr 1986 Sun Micro";
#endif	lint

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

#include <cputypes.h>
#include <mach_kdb.h>
#include <mach_rfs.h>
#include <mach_nfs.h>
#include <mach_nbc.h>
#include <mach_load.h>
#include <quota.h>

#include <cpus.h>
#include <fpa.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
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
#include <sys/socket.h>
#include <sys/kernel.h>

#include <net/if.h>
#include <sys/quota.h>
#include <sun/consdev.h>
#include <sun/frame.h>
#include <sundev/mbvar.h>

#include <sun3/psl.h>
#include <sun3/reg.h>
#include <sun3/clock.h>
#include <sun3/scb.h>
#include <sun3/mmu.h>
#include <sun3/cpu.h>
#include <sun3/eeprom.h>
#include <sun3/interreg.h>
#include <sun3/memerr.h>
#include <sun3/eccreg.h>

#if	MACH_RFS
#include <rfs/rfs.h>
#endif	MACH_RFS

#include <kern/thread.h>
#include <kern/lock.h>

#if	NFPA > 0
#include <sundev/fpareg.h>
#endif	NFPA > 0

#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <vm/vm_object.h>
#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#include <vm/vm_page.h>
#include <mach/vm_prot.h>
#include <kern/zalloc.h>
vm_map_t		buffer_map;
extern vm_offset_t	phys_map_vaddr1, phys_map_vaddr2;

/*
 *	Pointer to thread which owns FP state.
 */
thread_t	fp_threads[NCPUS];

int boothowto;
int maxmem;
struct map *iopbmap;
/*
 * Declare these as initialized data so we can patch them.
 */
int nbuf = 0;
int bufpages = 0;
int physmem = 0;	/* memory size in pages, patch if you want less */
int kernprot = 1;	/* write protect kernel text */
int msgbufinit = 0;	/* message buffer has been initialized, ok to printf */

int	msgbuf_init = FALSE;

int (*exit_vector)() = (int (*)())0;	/* Where to go when halting UNIX */

#define TESTVAL	0xA55A	/* memory test value */

u_char	getsegmap(), pmegallocres();
long	getpgmap();

#ifdef	SUN3_260
/*
 * Since there is no implied ordering of the memory cards, we store
 * a zero terminated list of pointers to eccreg's that are active so
 * that we only look at existent memory cards during softecc() handling.
 */
struct eccreg *ecc_alive[MAX_ECC+1];
int	vac;
#endif	SUN3_260

/*
 *  Allocate a submap in space accessable by the sun ethernet interfaces.
 */
vm_map_t ether_kmem_suballoc(parent, min, max, size, pageable)
	vm_map_t	parent;
	vm_offset_t	*min, *max;
	vm_size_t	size;
	boolean_t	pageable;
{
	kern_return_t	ret;
	vm_map_t	result;

	size = round_page(size);

	vm_object_reference(vm_submap_object);
	*min = (vm_offset_t)0x0f000000;
	ret = vm_map_find(parent, vm_submap_object, (vm_offset_t) 0,
				min, size, TRUE);
	if (ret != KERN_SUCCESS) {
		printf("kmem_suballoc: bad status return of %d.\n", ret);
		panic("kmem_suballoc");
	}
	*max = *min + size;
	if ((unsigned long)*max > 0x10000000)
		printf("ether_kmem_suballoc: warning: %s\n",
			"submap not entirely in ethernet-accessible space!");
	pmap_reference(vm_map_pmap(parent));
	result = vm_map_create(vm_map_pmap(parent), *min, *max, pageable);
	if (result == VM_MAP_NULL)
		panic("kmem_suballoc: cannot create submap");
	if ((ret = vm_map_submap(parent, *min, *max, result)) != KERN_SUCCESS)
		panic("kmem_suballoc: unable to change range to submap");
	return(result);
}

/*
 * We make use of CMAPn (the pte address)
 * and CADDRn (the virtual address)
 * which are both temporaries defined in locore.s,
 * not preserved across context switches,
 * and not to be used in interrupt routines
 */

/*
 * Machine-dependent startup code
 */
int fbobmemavail;
int	show_space	= 0;		/* initialize to make patchable */

startup(firstaddr)
caddr_t firstaddr;
{
	register int dvmapage;
	register unsigned i;
	register caddr_t v;
	int base, residual;
	extern char start[], end[];
	caddr_t zmemall();
	void v_handler();
	vm_size_t	size;
	kern_return_t	ret;
	vm_offset_t	trash_offset;
	vm_offset_t	phys;
	unsigned int	pme;
#if	MACH_KDB
	extern char		*esym;
#define END	esym
#else	MACH_KDB
#define END	end
#endif	MACH_KDB


	/*
	 * Determine if anything lives in DVMA bus space.
	 * We're paranoid and go through both the 16 bit
	 * and 32 bit device types.
 	 */
	phys = kmem_alloc_pageable(kernel_map, PAGE_SIZE);
	if (!phys)
		panic("dvma_probe: no space");
	disable_dvma();
        /* Access VME addresses, don't worry about cache here. */
	for (dvmapage = 0; dvmapage < btoc(dvmasize); dvmapage++) {
		pmap_enter(kernel_pmap, phys,
				       EPA_VME_D16+dvmapage,
				       VM_PROT_READ|VM_PROT_WRITE, FALSE);
		if (poke((short *)phys, TESTVAL) == 0)
			break;
		pmap_enter(kernel_pmap, phys,
				       EPA_VME_D32+dvmapage,
				       VM_PROT_READ|VM_PROT_WRITE, FALSE);
		if (poke((short *)phys, TESTVAL) == 0)
			break;
	}
	enable_dvma();
	kmem_free(kernel_map, phys, PAGE_SIZE);

#if	MACH_KDB
	/*
	 *	Initialize the kernel debugger.
	 *	Pretend we always have KDB (until we fix the boot
	 *	program?)
	 */
	boothowto |= RB_NOSYNC;	/* KDB needs this */
	kdb_init();
#endif	MACH_KDB
	/*
	 * Good {morning,afternoon,evening,night}.
	 * When printing memory, use the total including
	 * those hidden by the monitor (mon_mem).
	 */
	printf(version);
#define MEG	(1024*1024)
	printf("physical memory = %d.%d%d megabytes.\n", mem_size/MEG,
		((mem_size%MEG)*10)/MEG,
		((mem_size%(MEG/10))*100)/MEG);

	if (dvmapage < btoc(dvmasize)) {
		printf("CAN'T HAVE PERIPHERALS IN RANGE 0 - %dKB\n",
		    ctob(dvmasize) / 1024);
		panic("dvma collision");
	}

	/*
	 *	It is possible that someone has allocated some stuff
	 *	before here, (like vcons_init allocates the unibus map),
	 *	so, we look for enough space to put the dynamic data
	 *	structures, then free it with the assumption that we
	 *	can just get it back later (at the same address).
	 */
	firstaddr = (caddr_t) round_page(firstaddr);
	/*
	 *	Between the following find, and the next one below
	 *	we can't cause any other memory to be allocated.  Since
	 *	below is the first place we really need an object, it
	 *	will cause the object zone to be expanded, and will
	 *	use our memory!  Therefore we allocate a dummy object
	 *	here.  This is all a hack of course.
	 */

	ret = vm_map_find(kernel_map, vm_object_allocate(0), (vm_offset_t) 0,
		&firstaddr, 8*1024*1024, TRUE);
			/* size big enough for worst case */
	if (ret != KERN_SUCCESS) {
		printf("startup: no space for dynamic structures.\n");
		panic("startup");
	}
	vm_map_remove(kernel_map, firstaddr, firstaddr + 8*1024*1024);
	v = firstaddr;
#define valloc(name, type, num) \
	(name) = (type *)(v); (v) = (caddr_t)((name)+(num));\
	if (show_space) \
		printf("name = %d(0x%x) bytes @%x, %d cells @ %d bytes\n",\
		 num*sizeof(type), num*sizeof(type), name, num, sizeof (type))
#define valloclim(name, type, num, lim) \
	(name) = (type *)(v); (v) = (caddr_t)((lim) = ((name)+(num)));\
	if (show_space) \
		printf("name = %d(0x%x) bytes @%x, %d cells @ %d bytes\n",\
		 num*sizeof(type), num*sizeof(type), name, num, sizeof (type))
#define vround() (v = (caddr_t) ( ( ((int) v) + (NBPG-1)) & ~(NBPG-1)))
#define vquadround() (v = (caddr_t) ( ( ((int) v) + (8-1)) & ~(8-1)))

	printf("SPACE FREE: before valloc = %x[%d]\n",
		vm_page_free_count, vm_page_free_count);

#if	MACH_RFS
	valloc(rfsProcessTable, struct rfsProcessEntry, nproc);
#endif	MACH_RFS

	valloclim(inode, struct inode, ninode, inodeNINODE);
	valloclim(file, struct file, nfile, fileNFILE);
	valloclim(proc, struct proc, nproc, procNPROC);
	valloc(cfree, struct cblock, nclist);
	valloc(callout, struct callout, ncallout);
	valloc(namecache, struct namecache, nchsize);
	valloc(iopbmap, struct map, IOPBMAPSIZE);
	valloc(mb_hd.mh_map, struct map, DVMAMAPSIZE);
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
	 * Determine how many buffers to allocate.
	 * Use 10% of memory for the first 8 Meg, 20% of the remaining
	 * memory. Insure a minimum of 16 buffers.
	 * We allocate 1/2 as many swap buffer headers as file i/o buffers.
	 * If NBC, then allocate the minimum number of buffers (16).
	 */
	if (bufpages == 0) {
#if	MACH_NBC
		bufpages = 16;
#else	MACH_NBC
		bufpages = atop(mem_size / 10);
		if (mem_size > (8 * 1024 * 1024))
			bufpages += atop( (mem_size - (8 * 1024 * 1024)) / 10);
#endif	MACH_NBC
	}
	if (bufpages < 16) {
		bufpages = 16;
	}
	if (nbuf == 0)
		nbuf = bufpages;

	/*
	 * Now the amount of virtual memory remaining for buffers
	 * can be calculated, estimating needs for the cmap.
	 */
	valloc(buf, struct buf, nbuf);
	/*
	 * Done with dynamic allocations, except for buffers and
	 * mbufs.
	 */
	if (show_space)
		printf("limit of valloc'd space at %x\n", v);

	/*
	 * Clear allocated space, and make r/w entries
	 * for the space in the kernel map.
	 */
	v = (caddr_t) round_page(v);
	size = (vm_size_t) (v - firstaddr);
	ret = vm_map_find(kernel_map, vm_object_allocate(size), (vm_offset_t) 0,
				&firstaddr, size, FALSE);
	if (ret != KERN_SUCCESS) {
		panic("startup: unable to allocate kernel data structures");
	}
	vm_map_pageable(kernel_map, firstaddr, v, VM_PROT_READ|VM_PROT_WRITE);
	/* set firstaddr to the next address to be allocated */
	firstaddr = v;

	/*
	 * Allocate virtual memory for mbufs in ethernet-accessable space.
	 */
	mb_map = ether_kmem_suballoc(kernel_map, &mbutl, &embutl, ptoa((nmbclusters)), FALSE);
	if (show_space)
		printf("mbufs: %d bytes at kernel virtual address %x\n",
						ptoa((nmbclusters)), mb_map);

	/*
	 * Allocate virtual memory for buffer pool.
	 * For NFS, allocate buffers in ethernet-accessable space so
	 * that file data can be passed over the wire without copying.
	 */
	base = bufpages / nbuf;
	residual = bufpages % nbuf;
	size = MAXBSIZE * nbuf;
#if	MACH_NFS
	buffer_map = ether_kmem_suballoc(kernel_map, &buffers, &trash_offset,
					 size, TRUE);
#else	MACH_NFS
	buffer_map = kmem_suballoc(kernel_map, &buffers, &trash_offset,
				   size, TRUE);
#endif	MACH_NFS
	ret = vm_map_find(buffer_map, vm_object_allocate(size),
			  (vm_offset_t) 0, &buffers, size, FALSE);
	if (ret != KERN_SUCCESS) {
		panic("startup: unable to allocate buffer pool");
	}
	if (show_space)
		printf("buffers: %d bytes at kernel virtual address %x\n",
								size, buffers);

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
		vm_map_pageable(buffer_map, curbuf, curbuf+thisbsize,
				VM_PROT_READ|VM_PROT_WRITE);
	}


	/*
	 * Initialize callouts.
	 */
	callfree = callout;
	for (i = 1; i < ncallout; i++)
		callout[i-1].c_next = &callout[i];

	/*
	 * Initialize memory allocator and swap
	 * and user page table maps.
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
	sun_kmem_init();	/* initialize Sun's kernel memory allocator */
	rminit(iopbmap, (long)ctob(IOPBMEM), (long)DVMA, 
	    "IOPB space", IOPBMAPSIZE);
	rminit(mb_hd.mh_map, (long)(dvmasize - IOPBMEM), (long)IOPBMEM,
	    "DVMA map space", DVMAMAPSIZE);

	/*
	 * Set up buffers, so they can be used to read disk labels.
	 */
	bhinit();
	binit();

	/*
	 * Configure the system.
	 */
	bootflags();		/* get the boot options */
	configure();		/* set up devices */

	/*
	 * Figure out where the last page of the kernel was loaded in
	 * physical memory
	 */
	pme = getpgmap(trunc_page(END));
	phys = (pme & PG_PFNUM) << PGSHIFT;
	if (!fbobmemavail) {
		/*
		 * Frame buffer is in use, so check to make sure that the
		 * kernel was not loaded on top of it.
		 */
		if (phys >= trunc_page(OBFBADDR) 
		    && phys < round_page(OBFBADDR + FBSIZE))
			panic("kernel overlaps frame buffer");
	}
	else {
		u_int	old_firstaddr;

		/*
		 * The onboard frame buffer memory is still
		 * available, so use it as generic physical memory.
		 */

		old_firstaddr = round_page((int)END - KERNELBASE);

		/*
		 * The kernel may overlap the frame buffer depending
		 * which boot program was used.  The SunOS 4.0 boot
		 * puts the kernel below and above the frame buffer
		 * whereas older boots will load the kernel on top of
		 * the frame buffer.
		 *
		 * If end of kernel is below the frame buffer, then give
		 * back everything from the end of the kernel up to the
		 * end of the frame buffer.  Otherwise, we need to figure
		 * out which boot program was used, so we know what
		 * memory to give back.
		 */
		if (old_firstaddr < OBFBADDR)
			vm_page_create(
				old_firstaddr,
				(round_page(OBFBADDR+FBSIZE) - old_firstaddr),
				(boolean_t (*)()) 0
			 );
		else {
			/*
			 * If the last physical page of the kernel lies outside
			 * the frame buffer, then the new boot program was 
			 * used and we just give back the frame buffer memory.
			 * Otherwise, the old boot program was used and we need
			 * to give back a chunk of memory the size of the frame
			 * buffer starting from the end of the kernel which is
			 * right in the middle of the frame buffer.
			 */
			if (phys < trunc_page(OBFBADDR) 
			    || phys >= round_page(OBFBADDR + FBSIZE))
				vm_page_create(
					trunc_page(OBFBADDR),
					(round_page(OBFBADDR+FBSIZE) - trunc_page(OBFBADDR)),
					(boolean_t (*)()) 0
				 );
			else
				vm_page_create(
					old_firstaddr,
					round_page(FBSIZE),
					(boolean_t (*)()) 0
			 	);
		}

		fbobmemavail = 0;
	}
#ifdef	SUN3_260
	/*
	 *	Enable cache if appropriate.
	 */
	if (cpu == CPU_SUN3_260) {
		setcacheenable(1);
		vac = 1;
	}
#endif	SUN3_260
/*	(void) spl0();		/* drop priority */
}


struct	bootf {
	char	let;
	short	bit;
} bootf[] = {
	'a',	RB_ASKNAME,
	's',	RB_SINGLE,
	'i',	RB_INITNAME,
	'h',	RB_HALT,
	'b',	RB_NOBOOTRC,
	'n',	RB_NOSYNC,
#if	MACH_KDB
	'k',	RB_KDB,
#endif	MACH_KDB
	0,	0,
};
char *initname = "/etc/init";

/*
 * Parse the boot line to determine boot flags .
 */
bootflags()
{
	register struct bootparam *bp = (*sunromp->v_bootparam);
	register char *cp;
	register int i;

	cp = bp->bp_argv[1];
	if (cp && *cp++ == '-')
		do {
			for (i = 0; bootf[i].let; i++) {
				if (*cp == bootf[i].let) {
					boothowto |= bootf[i].bit;
					break;
				}
			}
			cp++;
		} while (bootf[i].let && *cp);
	if (boothowto & RB_INITNAME)
		initname = bp->bp_argv[2];
	if (boothowto & RB_HALT)
		halt("bootflags");

#if	MACH_KDB
	boothowto |= RB_NOSYNC;	/* temp */
#endif	MACH_KDB
}


#ifdef	PGINPROF
/*
 * Return the difference (in microseconds)
 * between the current time and a previous
 * time as represented by the arguments.
 */
vmtime(otime, olbolt)
	register int otime, olbolt;
{

	return (((time-otime)*HZ + lbolt-olbolt)*(1000000/HZ));
}
#endif	PGINPROF

/*
 * Send an interrupt to process.
 *
 * When using new signals user code must do a
 * sys #139 to return from the signal, which
 * calls sigcleanup below, which resets the
 * signal mask and the notion of onsigstack,
 * and returns from the signal handler.
 */
sendsig(p, sig, sigmsk)
	int (*p)(), sig, sigmsk;
{
	register int usp, *regs, scp;
	struct nframe {
		int	sig;
		int	code;
		int	scp;
	} frame;
	struct sigcontext sc;
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
		usp = (int)u.u_sigsp;
		u.u_onstack = 1;
	} else
		usp = regs[SP];
	usp -= sizeof (struct sigcontext);
	scp = usp;
	usp -= sizeof (frame);
	if (!u.u_onstack && usp <= USRSTACK - ctob(u.u_ssize))
		(void) grow((unsigned)usp);
	if (useracc((caddr_t)usp, sizeof (frame) + sizeof (sc), B_WRITE) == 0) {
		/*
		 * Process has trashed its stack; give it an illegal
		 * instruction to halt it in its tracks.
		 */
printf("sendsig: bad user stack pid=%d, sig=%d\n", u.u_procp->p_pid, sig);
printf("usp is %x, action is %x, upc is %x\n", usp, p, regs[PC]);
		u.u_signal[SIGILL] = SIG_DFL;
		sig = sigmask(SIGILL);
		u.u_procp->p_sigignore &= ~sig;
		u.u_procp->p_sigcatch &= ~sig;
		u.u_procp->p_sigmask &= ~sig;
		psignal(u.u_procp, SIGILL);
		return;
	}
	/*
	 * push sigcontext structure.
	 */
	sc.sc_onstack = oonstack;
	sc.sc_mask = sigmsk;
	sc.sc_sp = regs[SP];
	sc.sc_pc = regs[PC];
	sc.sc_ps = regs[PS];
	/*
	 * If trace mode was on for the user process
	 * when we came in here, it may have been because
	 * of an ast-induced trace on a trap instruction,
	 * in which case we do not want to restore the
	 * trace bit in the status register later on
	 * in sigcleanup().  If we were to restore it
	 * and another ast trap had been posted, we would
	 * end up marking the trace trap as a user-requested
	 * real trace trap and send a bogus "Trace/BPT" signal.
	 */
	if ((sc.sc_ps & PSL_T) && (current_thread()->pcb->pcb_flag
	    & TRACE_AST))
		sc.sc_ps &= ~PSL_T;
	(void) copyout((caddr_t)&sc, (caddr_t)scp, sizeof (sc));
	/*
	 * push call frame.
	 */
	frame.sig = sig;
	if (sig == SIGILL || sig == SIGFPE || sig == SIGEMT) {
		frame.code = u.u_code;
		u.u_code = 0;
	} else
		frame.code = 0;
	frame.scp = scp;
	(void) copyout((caddr_t)&frame, (caddr_t)usp, sizeof (frame));
	regs[SP] = usp;
	regs[PC] = (int)p;
}

/*
 * Routine to cleanup state after a signal
 * has been taken.  Reset signal mask and
 * notion of on signal stack from context
 * left there by sendsig (above).  Pop these
 * values and perform rti.
 */
/*
 *	Now called osigcleanup since 4.3 has a new 'sigreturn' call.
 *	On the SUN, the calling sequences for the two routines are
 *	the same (I think).
 */
sigreturn()
{
	osigcleanup();
}

osigcleanup()
{
	struct sigcontext *scp, sc;

	scp = (struct sigcontext *)fuword((caddr_t)u.u_ar0[SP] + sizeof(int));
	if ((int)scp == -1)
		return;
	if (copyin((caddr_t)scp, (caddr_t)&sc, sizeof (sc)))
		return;
	u.u_onstack = sc.sc_onstack & 01;
	u.u_procp->p_sigmask =
	    sc.sc_mask &~ (sigmask(SIGKILL)|sigmask(SIGCONT)|sigmask(SIGSTOP));
	u.u_ar0[SP] = sc.sc_sp;
	u.u_ar0[PC] = sc.sc_pc;
	u.u_ar0[PS] = sc.sc_ps;
	u.u_ar0[PS] &= ~PSL_USERCLR;
	u.u_ar0[PS] |= PSL_USERSET;
	u.u_eosys = JUSTRETURN;
}

#include <sys/mount.h>
int	waittime = -1;

boot(paniced, howto)
	int paniced, howto;
{
	static int prevflag = 0;
	register struct buf *bp;
	struct mount *mp;
	int iter, nbusy;
	int s;

	consdev = 0;
	startnmi();
#if	MACH_RFS
	rfs_boot(paniced, howto);
#endif	MACH_RFS
	if ((howto&RB_NOSYNC)==0 && waittime < 0 && bfreelist[0].b_forw) {
		syncdisk();
		waittime = 0;

#if	MACH_VFS
		if(paniced != RB_PANIC) {
		    printf("unmounting file systems... ");
		    for(mp = &mount[NMOUNT - 1]; mp >= mount; mp--) {
			if(mp->m_vfsp && mp->m_bufp && mp->m_dev != rootdev)
			    (void) dounmount(mp->m_vfsp);
		    }
		    printf("done\n");
		}
#endif	MACH_VFS
	}
	s = spl7();				/* extreme priority */
	if (howto & RB_HALT) {
		halt((char *)NULL);
		/* MAYBE REACHED */
	} else {
		if (paniced == RB_PANIC && prevflag == 0) {
			prevflag = 1;		/* prevent panic recursion */
			dumpsys();
		}
		printf("Rebooting Mach...\n");
		(*sunromp->v_boot_me)(howto & RB_SINGLE ? "-s" : "");
		/*NOTREACHED*/
	}
	(void) splx(s);
}

long	dumpmag = 0x8FCA0101;	/* magic number for savecore(8) */
long	dumpsize = 0;		/* also for savecore */

/*
 * Dump the system:
 * Map in memory page by page and call the dump device driver
 * to write it out.
 */
dumpsys()
{
	caddr_t addr;
	int pg;
	int bn = dumplo;
	int err = 0;
	int (*dumper)();

#ifdef	notdef
	if ((minor(dumpdev)&07) != 1)
		return;
#endif	notdef
	printf("\ndumping to dev %x, offset %d\n", dumpdev, dumplo);

	addr = &DVMA[ctob(dvmasize-1)];
	dumper = bdevsw[major(dumpdev)].d_dump;
	setcontext(KCONTEXT);
#ifdef	SUN3_260
	vac_flushall(); /* make physical memory consistent with the cache */
#endif	SUN3_260
	for (pg = 0; pg < physmem && !err; pg++) {
		setpgmap(addr, (long)(pg | PG_V | PG_KW));
		err = (*dumper)(dumpdev, addr, bn, ctod(1));
		bn += ctod(1);
#ifdef	SUN3_260
		vac_pageflush(addr);
#endif	SUN3_260
	}

	printf("dump ");
	switch (err) {

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
		printf("failed: unknown error\n");
		break;
	}
}

/*
 * Initialize UNIX's vector table:
 * Vectors are copied from protoscb unless
 * they are zero; zero means preserve whatever the
 * monitor put there.  If the protoscb is zero,
 * then the original contents are copied into
 * the scb we are setting up.
 */
initscb()
{
	register int *s, *p, *f;
	register int n;
	struct scb *orig, *getvbr();

	orig = getvbr();
	exit_vector = orig->scb_trap[14];
	s = (int *)&scb;
	p = (int *)&protoscb;
	f = (int *)orig;
	for (n = sizeof (struct scb)/sizeof (int); n--; s++, p++, f++) {
		if (*p) 
			*s = *p;
		else
			*s = *f;
	}
	setvbr(&scb);
}


/*
 * Handle "physical" block transfers.
 */
physstrat(bp, strat, pri)
	register struct buf *bp;
	int (*strat)();
	int pri;
{
	vm_offset_t	user_buffer;	/* start of user buffer */
	register vm_offset_t	va;	/* start of user buffer, at page bdy */
	vm_offset_t	offset;		/* byte offset within page */
	int		num_pages;	/* number of pages in buffer, + 1 */
	kern_return_t	result;
	pmap_t		pmap;		/* pmap for buffer */
	
	vm_offset_t	kernel_buffer;	/* buffer in kernel space */
	register vm_offset_t	ka, pa;
	register int	i;
	int		s;

	/*
	 *	Grab a portion of kernel address space, and remap
	 *	the virtual memory for the IO (possibly in user space)
	 *	into that kernel address space.  Then do the IO on the
	 *	kernel address space (the drivers like this).
	 */

	user_buffer = (vm_offset_t) bp->b_un.b_addr;	/* save for later */

	va = trunc_page(user_buffer);
	offset = user_buffer & page_mask;
	/*
	 *	we want one spare page
	 */
	num_pages = atop(round_page(bp->b_bcount + offset)) + 1;
	/*
	 *	allocate some virtual space in the kernel
	 */
	result = vm_allocate(kernel_map, &kernel_buffer, ptoa(num_pages),
				TRUE);
	if (result != KERN_SUCCESS)
		panic("physstrat: no kernel virtual memory!");

	/*
	 *	Get the map for the buffer
	 */
	if ((bp->b_flags & B_PHYS) == 0)
		pmap = kernel_pmap;
	else
		pmap = vm_map_pmap(bp->b_proc->task->map);
	/*
	 *	Map each page into the kernel address space
	 */
	ka = kernel_buffer;
	for (i = 0; i < num_pages-1; i++, va += page_size, ka += page_size) {

		pa = pmap_extract(pmap, va);
#ifdef	SUN3_260
		/*
		 *	Set context and then flush page from cache
		 */
		if (vac) {
			cache_flush_page(pmap->context->num, (caddr_t) va);
		}
#endif	SUN3_260
		pmap_enter(kernel_pmap, ka, pa, VM_PROT_READ|VM_PROT_WRITE,
				TRUE);
	}
	/*
	 *	make the last mapping 0 (keeps the drivers happy?)
	 *	(anyway, SUN does it...)
	 */
	pme_zero(ka, ka+PAGE_SIZE, FALSE);

	/*
	 *	Now point the buffer at the kernel address space
	 */
	bp->b_un.b_addr = (caddr_t) (kernel_buffer | offset);
	(*strat)(bp);
	if (bp->b_flags & B_DIRTY)
		return;
	s = spl6();
	while ((bp->b_flags & B_DONE) == 0)
		sleep((caddr_t)bp, pri);
	(void) splx(s);
	/*
	 *	Get rid of the kernel address space.
	 */
	vm_map_remove(kernel_map, kernel_buffer,
			kernel_buffer + ptoa(num_pages));
	/*
	 *	And restore the original buffer address.
	 */
	bp->b_un.b_addr = (caddr_t) user_buffer;
}

/*
 * Halt the machine and return to the monitor
 */
halt(s)
	char *s;
{
	extern struct scb *getvbr();

	if (s)
		(*sunromp->v_printf)("(%s) ", s);
	(*sunromp->v_printf)("Mach Halted\n\n");
	startnmi();
	if (exit_vector)
		getvbr()->scb_trap[14] = exit_vector;
	asm("trap #14");
	if (exit_vector)
		getvbr()->scb_trap[14] = protoscb.scb_trap[14];
	stopnmi();
}

/*
 * Print out a traceback for the caller - can be called anywhere
 * within the kernel or from the monitor by typing "g4" (for sun-2
 * compatibility) or "w trace".  This causes the monitor to call
 * the v_handler() routine which will call tracedump() for these cases.
 */
/*VARARGS0*/
tracedump(x1)
	caddr_t x1;
{
	struct frame *fp = (struct frame *)(&x1 - 2);
	u_int tospage = btoc(fp);

	(*sunromp->v_printf)("Begin traceback...fp = %x\n", fp);
	while (btoc(fp) == tospage) {
		if (fp == fp->fr_savfp) {
			(*sunromp->v_printf)("FP loop at %x", fp);
			break;
		}
		(*sunromp->v_printf)("Called from %x, fp=%x, args=%x %x %x %x\n",
		    fp->fr_savpc, fp->fr_savfp,
		    fp->fr_arg[0], fp->fr_arg[1], fp->fr_arg[2], fp->fr_arg[3]);
		fp = fp->fr_savfp;
	}
	(*sunromp->v_printf)("End traceback...\n");
}

/*
 * if a() calls b() calls caller(),
 * caller() returns return address in a().
 */
int
(*caller())()
{

#ifdef	lint
	return ((int (*)())0);
#else
	asm("   movl    a6@,a0");
	asm("   movl    a0@(4),d0");
#endif
}

/*
 * if a() calls callee(), callee() returns the
 * return address in a();
 */
int
(*callee())()
{

#ifdef	lint
	return ((int (*)())0);
#else
	asm("   movl    a6@(4),d0");
#endif
}

/*
 * Buscheck is called by mbsetup to check to see it the requested
 * setup is a valid busmem type (i.e. VMEbus).  Returns 1 if ok
 * busmem type, returns 0 if not busmem type.  This routine
 * make checks and panic's if an illegal busmem type request is detected.
 */
buscheck(bufaddr, npf)
	register caddr_t bufaddr;
	register int npf;
{
	int origctx;
	register int i, pf;
	register int pt;
	long pme;
	register struct pme *pte;

	pme = getpgmap(bufaddr);
	pte = (struct pme *)&pme;
	pt = pme & PGT_MASK;
	if (pt == PGT_VME_D16 || pt == PGT_VME_D32) {
		pf = pte->pfn;
		if (pf < btoc(DVMASIZE))
			panic("buscheck: busmem in DVMA range");
		for (i = 0; i < npf; i++, pf++) {
			pme = getpgmap(bufaddr);
			pte = (struct pme *)&pme;
			if ((*(int *)pte & PGT_MASK) != pt || pte->pfn != pf)
				panic("buscheck: request not contiguous");
			bufaddr += NBPG;
		}
		return (1);
	}
	return (0);
}

/* 
 * Compute the address of an I/O device within standard address
 * ranges and return the result.  This is used by DKIOCINFO
 * ioctl to get the best guess possible for the actual address
 * set on the card.
 */
getdevaddr(addr)
	caddr_t addr;
{
	int off = (int)addr & PGOFSET;
	int pte = getkpgmap(addr);
	int physaddr = ((pte & PG_PFNUM) & ~PGT_MASK) * NBPG;

	switch (pte & PGT_MASK) {
	case PGT_VME_D16:
	case PGT_VME_D32:
		if (physaddr > VME16_BASE) {
			/* 16 bit VMEbus address */
			physaddr -= VME16_BASE;
		} else if (physaddr > VME24_BASE) {
			/* 24 bit VMEbus address */
			physaddr -= VME24_BASE;
		}
		/*
		 * else 32 bit VMEbus address,
		 * physaddr doesn't require adjustments
		 */
		break;

	case PGT_OBMEM:
	case PGT_OBIO:
		/* physaddr doesn't require adjustments */
		break;
	}

	return (physaddr + off);
}

static int (*mon_nmi)();		/* monitor's level 7 nmi routine */
static u_char mon_mem;			/* monitor memory register setting */
extern int level7();			/* Unix's level 7 nmi routine */

stopnmi()
{
	struct scb *vbr, *getvbr();

	vbr = getvbr();
	if (vbr->scb_autovec[7 - 1] != level7) {
#ifndef	GPROF
		set_clk_mode(0, IR_ENA_CLK7);	/* disable level 7 clk intr */
#endif	!GPROF
		mon_nmi = vbr->scb_autovec[7 - 1];	/* save mon vec */
		vbr->scb_autovec[7 - 1] = level7;	/* install Unix vec */
#ifdef	SUN3_260
		if (cpu == CPU_SUN3_260) {
			mon_mem = MEMREG->mr_eer;
			MEMREG->mr_eer = EER_INTENA | EER_CE_ENA;
		}
#endif	SUN3_260
#if	defined(SUN3_160) || defined(SUN3_50) || defined(SUN3_110) || defined(SUN3_60)
		if (cpu == CPU_SUN3_160 || cpu == CPU_SUN3_50 ||
		    cpu == CPU_SUN3_110 || cpu == CPU_SUN3_60)
			mon_mem = MEMREG->mr_per;
#endif	defined(SUN3_160) || defined(SUN3_50) || defined(SUN3_110) || defined(SUN3_60)
	}
}

startnmi()
{
	struct scb *getvbr();

	if (mon_nmi) {
		getvbr()->scb_autovec[7 - 1] = mon_nmi;	/* install mon vec */
#ifndef	GPROF
		set_clk_mode(IR_ENA_CLK7, 0);	/* enable level 7 clk intr */
#endif	!GPROF
#ifdef	SUN3_260
		if (cpu == CPU_SUN3_260)
			MEMREG->mr_eer = mon_mem;
#endif	SUN3_260
#if	defined(SUN3_160) || defined(SUN3_50) || defined(SUN3_110) || defined(SUN3_60)
		if (cpu == CPU_SUN3_160 || cpu == CPU_SUN3_50 ||
		    cpu == CPU_SUN3_110 || cpu == CPU_SUN3_60)
			MEMREG->mr_per = mon_mem;
#endif	defined(SUN3_160) || defined(SUN3_50) || defined(SUN3_110) || defined(SUN3_60)
	}
}

/*
 * Handler for monitor vector cmd -
 * For now we just implement the old "g0" and "g4"
 * commands and a printf hack.
 */
void
v_handler(addr, str)
	int addr;
	char *str;
{

	switch (*str) {
	case '\0':
		/*
		 * No (non-hex) letter was specified on
		 * command line, use only the number given
		 */
		switch (addr) {
		case 0:		/* old g0 */
		case 0xd:	/* 'd'ump short hand */
			panic("zero");
			/*NOTREACHED*/
		
		case 4:		/* old g4 */
			tracedump();
			break;

		default:
			goto err;
		}
		break;

	case 'p':		/* 'p'rint string command */
	case 'P':
		(*sunromp->v_printf)("%s\n", (char *)addr);
		break;

	case '%':		/* p'%'int anything a la printf */
		(*sunromp->v_printf)(str, addr);
		(*sunromp->v_printf)("\n");
		break;

	case 't':		/* 't'race kernel stack */
	case 'T':
		tracedump();
		break;

	case 'u':		/* d'u'mp hack ('d' look like hex) */
	case 'U':
		if (addr == 0xd) {
			panic("zero");
		} else
			goto err;
		break;

	default:
	err:
		(*sunromp->v_printf)("Don't understand 0x%x '%s'\n", addr, str);
	}
}

/*
 * Handle parity/ECC memory errors.  XXX - use something like
 * vax to only look for soft ecc errors periodically?
 */
memerr()
{
	u_char per, eer;
	char *mess = 0;
	int c;
	long pme;

	eer = per = MEMREG->mr_er;
#ifdef	SUN3_260
	if (cpu == CPU_SUN3_260 && (eer & EER_ERR) == EER_CE) {
		MEMREG->mr_eer = ~EER_CE_ENA;
		softecc();
		MEMREG->mr_dvma = 1;	/* clear latching */
		MEMREG->mr_eer |= EER_CE_ENA;
		return;
	} 
#endif	SUN3_260

	/*
	 * Since we are going down in flames, disable further
	 * memory error interrupts to prevent confusion.
	 */
	MEMREG->mr_er &= ~ER_INTENA;

#if	defined(SUN3_160) || defined(SUN3_50) || defined(SUN3_110) || defined(SUN3_60)
	if ((cpu == CPU_SUN3_160 || cpu == CPU_SUN3_50 ||
	    cpu == CPU_SUN3_110 || cpu == CPU_SUN3_60) &&
	    (per & PER_ERR) != 0) {
		printf("Parity Error Register %b\n", per, PARERR_BITS);
		mess = "parity error";
	}
#endif	defined(SUN3_160) || defined(SUN3_50) || defined(SUN3_110) || defined(SUN3_60)


#ifdef	SUN3_260
	if ((cpu == CPU_SUN3_260) && (eer & EER_ERR) != 0) {
		printf("ECC Error Register %b\n", eer, ECCERR_BITS);
		if (eer & EER_TIMEOUT)
			mess = "memory timeout error";
		if (eer & EER_UE)
			mess = "uncorrectable ECC error";
		if (eer & EER_WBACKERR)
			mess = "writeback  error";
	}
#endif	SUN3_260

	if (!mess) {
		printf("Memory Error Register %b %b\n",
		    per, PARERR_BITS, eer, ECCERR_BITS);
		mess = "unknown memory error";
	}

	printf("DVMA = %x, context = %x, virtual address = %x\n",
		MEMREG->mr_dvma, MEMREG->mr_ctx, MEMREG->mr_vaddr);

	pme = getpagemap((int)MEMREG->mr_ctx, (caddr_t)MEMREG->mr_vaddr);
	printf("pme = %x, physical address = %x\n", pme,
	    ptob(((struct pme *)&pme)->pfn) + (MEMREG->mr_vaddr&PGOFSET));

	/*
	 * Clear the latching by writing to the top
	 * nibble of the memory address register
	 */
	MEMREG->mr_dvma = 1;

	panic(mess);
	/*NOTREACHED*/
}

#ifdef	SUN3_260
int prtsoftecc = 1;
int memintvl = MEMINTVL;

/* 
 * Routine to turn on correctable error reporting.
 */
ce_enable(ecc)
register struct eccreg *ecc;
{
	ecc->eccena |= ENA_BUSENA_MASK;
}

/*
 * Probe memory cards to find which one(s) had ecc error(s).
 * If prtsoftecc is non-zero, log messages regarding the failing
 * syndrome.  Then clear the latching on the memory card.
 */
softecc()
{
	register struct eccreg **ecc_nxt, *ecc;

	for (ecc_nxt = ecc_alive; *ecc_nxt != (struct eccreg *)0; ecc_nxt++) {
		ecc = *ecc_nxt;
		if (ecc->syndrome & SY_CE_MASK) {
			if (prtsoftecc) {
				printf("mem%d: soft ecc addr %x+%x=%x syn %b\n",
				    ecc - ECCREG,
				    (ecc->eccena & ENA_ADDR_MASK) <<
					ENA_ADDR_SHIFT,
				    (ecc->syndrome & SY_ADDR_MASK) <<
					SY_ADDR_SHIFT,
				    ((ecc->eccena & ENA_ADDR_MASK) <<
					ENA_ADDR_SHIFT) +
					((ecc->syndrome & SY_ADDR_MASK) <<
					SY_ADDR_SHIFT),
				    (ecc->syndrome & SY_SYND_MASK) >>
					SY_SYND_SHIFT, SYNDERR_BITS);
			}
			ecc->syndrome |= SY_CE_MASK;	/* clear latching */
			ecc->eccena &= ~ENA_BUSENA_MASK;/* disable board */
			timeout(ce_enable, (caddr_t)ecc, memintvl*hz);
		}
	}
}
#endif	SUN3_260



/*
 * Clear registers on exec
 */
setregs(entry)
u_long	entry;
{
	register int i;
#ifdef	mc68000
	{
		register struct regs *r = (struct regs *)u.u_ar0;

		for (i = 0; i < 8; i++) {
			r->r_dreg[i] = 0;
			if (&r->r_areg[i] != &r->r_sp)
				r->r_areg[i] = 0;
		}
		r->r_ps = PSL_USERSET;
		r->r_pc = entry;
	}
	/*
	 *	don't pop syscall number off stack-
	 *	it's not there!
	 */
	u.u_eosys = JUSTRETURN;	/* ucb's name for this */
#endif	mc68000
#ifdef	sun3
	/*
	 * Clear any external and internal fpp state.
	 * If this thread was the last one to load its
	 * external fpp state, erase that fact also.
	 */
	{
		int	currcpu = cpu_number();

		bzero((caddr_t)&(current_thread()->pcb->pcb_fp_status),
			sizeof (struct fp_status));
		bzero((caddr_t)&(current_thread()->pcb->pcb_fp_istate),
			sizeof (struct fp_istate));
		if (current_thread() == fp_threads[currcpu])
			fp_threads[currcpu] = (thread_t)0;
	}
#if	NFPA > 0
	if (current_thread()->pcb->pcb_fpa_flags & FPA_USED)
		fpaclose_thread(current_thread());
#endif	NFPA > 0
#endif	sun3
}

caddr_t zmemall(f, size)
int		(*f)();
vm_size_t	size;
{
	return((caddr_t)kmem_alloc(kernel_map, size));
}

int memall()
{
}

/*
 *	This is used by the mouse.
 */
uniqtime(tv)
	register struct timeval *tv;
{
	static struct timeval last;
	static int uniq;
			
	while (last.tv_usec != time.tv_usec || last.tv_sec != time.tv_sec) {
		last = time;
		uniq = 0;
	}
	*tv = last;
	tv->tv_usec += uniq++;
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
 * NOTE:  Sun doesn't have interval count register.
 */
microtime(tvp)
	register struct timeval *tvp;
{
	int s = splhigh();
	static struct timeval lasttime;
	register long t;

	*tvp = time;
	if (tvp->tv_sec == lasttime.tv_sec &&
	    tvp->tv_usec <= lasttime.tv_usec &&
	    (tvp->tv_usec = lasttime.tv_usec + 1) > 1000000) {
		tvp->tv_sec++;
		tvp->tv_usec -= 1000000;
	}
	lasttime = *tvp;
	splx(s);
}
