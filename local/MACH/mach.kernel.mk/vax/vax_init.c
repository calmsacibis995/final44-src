/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * Copyright (c) 1986 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vax_init.c,v $
 * Revision 2.8  89/03/09  22:22:54  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/26  10:49:47  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  89/01/15  16:38:09  rpd
 * 	Use decl_simple_lock_data.
 * 	[89/01/15  15:24:35  rpd]
 * 
 * Revision 2.5  88/08/23  23:02:30  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	For 630, go back to old memory sizing code and don't rely on
 * 	vmb.exe setting up the memory bitmap.  And move code from
 * 	machdep.c which stole space from the end of memory for 630
 * 	to same bit if code above.
 * 	[88/08/22            mrt]
 * 
 * Revision 2.4  88/08/09  17:24:28  rvb
 * 	No more rawmem_size for uVaxen.  We now use the data passed in
 * 	by VMB.
 * 12-Jul-88  Robert Baron (rvb) 
 * 	Move register printout to after (650, 630) console
 * 	is initialized.
 * 	Don't clobber memory bitmap on 650 and 630 (uVaxen).
 * 31-May-88  Robert Baron (rvb)
 * 	Initialize printf_lock.
 * 	Save boot_regs.
 * 10-May-88  Robert Baron (rvb)
 * 	Define ka820_csr to map port controller.
 *  8-Apr-88  Robert Baron (rvb)
 * 	New 6200 machine:
 * 	Define vax_6200 if appropriate
 * 	Pmap_enter for ka62a_csr1, cca, and ka62a_ssc.
 * 	Find and remember cca phys and size and don't clobber it.
 * 
 *
 * 29-Mar-88  David Golub (dbg) at Carnegie-Mellon University
 *	Leave last 32K for qbus mapping registers ONLY if actually ON a
 *	VAX650!
 *
 * 10-Oct-87  Robert V. Baron (rvb) at Carnegie-Mellon University
 *	Support for VAX650:
 *		remember true memory size
 *		leave last 32K for qbus mapping registers
 *
 *  3-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 18-Sep-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 22-Apr-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	MACH_LOAD:  Fixed to link without this option defined.
 *	[ V5.1(F10) ]
 *
 * 14-Jan-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH_TT: Fix up register save mask for load_init_program.
 *
 * 31-Dec-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Add register mask initialization for "main", which now looks
 *	a lot like a system call.
 *
 *  9-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted some... changed declaration of "loadpt" to "int".
 *
 *  1-Nov-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Don't depend on the boot program to tell us the size of memory
 *	for uVaxen.  Just size it the normal way and reduce by
 *	an appropriate amount on uVax II to allow for ROM usage.
 *
 * 19-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Eliminated CS_NEWCPU and reorganized size_memory() a bit.
 *
 * 11-Aug-86  David Golub (dbg) at Carnegie-Mellon University
 *	Converted to 4.3 machine names.
 *
 * 29-May-86  David Golub (dbg) at Carnegie-Mellon University
 *	Put RPB at local 0, not load-point.
 *
 * 21-May-86  David Golub (dbg) at Carnegie-Mellon University
 *	Call vm_set_page_size from size_memory.
 *
 * 15-Mar-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Set cpu number early for routines that need it before
 *	configuration.
 *
 */
/*
 *
 *	File:	vax/vax_init.c
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1986, Avadis Tevanian, Jr., Michael Wayne Young
 */
#include <mach_kdb.h>
#include <cputypes.h>
#include <mach_load.h>

#include <sys/types.h>
#include <vax/mtpr.h>
#include <vax/scb.h>
#include <vax/cpu.h>
#include <vax/pcb.h>
#if	VAX6200
#include <vaxnb/ka62a.h>
#include <vaxnb/cca.h>
#endif	VAX6200
#include <mach/vm_param.h>
#include <mach/vm_prot.h>
#include <vm/vm_page.h>
#include <vm/pmap.h>

#if	MACH_LOAD
extern int	loadpt;
#else	MACH_LOAD
#define loadpt	0
#endif	MACH_LOAD

#define SYSBASE		0x80000000
#define PHYS(addr)	((((unsigned)addr) & ~SYSBASE) + loadpt)

union cpusid	cpu_sid;
vm_size_t	mem_size;
vm_offset_t	first_addr;
vm_offset_t	last_addr;

vm_offset_t	avail_start, avail_end;
vm_offset_t	virtual_avail, virtual_end;

#if	VAX6200
struct	ka62a_ssc	*ka62a_ssc;
int			*ka62a_csr1;
struct cca		*cca;

int			cca_size;			/* only used by pmap.c */
static struct cca 	*ccap;
#endif	VAX6200

#if	VAX6200 || VAX650 || VAX630
int		mem_bitmap_size;
vm_offset_t	mem_bitmap;
#endif	VAX6200 || VAX650 || VAX630

int systype;
int cputype_sid;

vax_init()
{
	long		*p;
	extern char	edata, end;
	extern int	panic(), trap(), syscall(), main();
	extern int	load_init_program();
	decl_simple_lock_data(extern,printf_lock)

	mtpr(SCBB, PHYS(&scb));		/* set up SCB */
#if	MACH_KDB
	blkclr((caddr_t) PHYS(&edata), (unsigned) ((&end - &edata) - sizeof(int)));
#else	MACH_KDB
	blkclr((caddr_t) PHYS(&edata), (unsigned) (&end - &edata));
#if	NCPUS > 1
	simple_lock_init(&printf_lock);
#endif	NCPUS > 1
#endif	MACH_KDB
	/*
	 *	We won't really know our cpu number till after
	 *	we configure... but we still need to have a valid
	 *	cpu number for routines that use it.  Fortunately,
	 *	set_cpu_number will do the right thing for us here
	 *	because cpu_number doesn't know we have multi-port
	 *	memory yet.
	 */
	set_cpu_number();
	cpu_sid.cpusid = mfpr(SID);
	cpu = cpu_sid.cpuany.cp_type;	/* cpu type */
	cputype_sid = cpu;
	if (cpu == VAX_650 || cpu == VAX_630)
		systype = *SYSTYPE;
	else
		systype = -1;
	if (cpu == VAX_650) {
		/* we are running physical here so: */
		switch (systype >> 24) {
		case 1:
			break;
		case 2:
			cpu = VAX_6200;
			break;
		default:
			asm("halt");
		}
	}
	rpb_init();
	size_memory();
	/*
	 *	Fix up register masks for some routines
	 */

	p = (long *)PHYS(panic);
	*p |= 0xfff;
	p = (long *)PHYS(trap);
	*p |= 0xfff;
	p = (long *)PHYS(syscall);
	*p |= 0xfff;
	p = (long *)PHYS(main);
	*p |= 0xfff;
	p = (long *)PHYS(load_init_program);
	*p |= 0xfff;
	fixctlrmask();

	dfloat_test();

	/*
	 *	Initialize kernel physical map, mapping the
	 *	region from loadpt to avail_start.
	 *	Kernel virtual address starts at VM_KERNEL_MIN_ADDRESS.
	 */

	avail_start = first_addr;
	avail_end = last_addr;
	printf("Vax boot: memory from 0x%x to 0x%x\n", avail_start,
			avail_end);
	pmap_bootstrap(loadpt, &avail_start, &avail_end, &virtual_avail,
				&virtual_end);
#ifdef	VAX6200
		/* done here so we can have a cpu number before setup_main() */
	if (cpu == VAX_6200) {
		extern	pmap_t kernel_pmap;
#define CSR1	((caddr_t) 0x20000000)
#define SSCC	((caddr_t) 0x20140000)
		pmap_enter(kernel_pmap, ka62a_csr1, CSR1,
					VM_PROT_READ|VM_PROT_WRITE, FALSE);
		pmap_enter(kernel_pmap, cca, ccap,
					VM_PROT_READ|VM_PROT_WRITE, FALSE);
		pmap_enter(kernel_pmap, ka62a_ssc, SSCC,
					VM_PROT_READ|VM_PROT_WRITE, FALSE);
	}
#endif	VAX6200
#ifdef	VAX820
		/* done here so we can have a cpu number before setup_main() */
	if (cpu == VAX_820) {
		extern	pmap_t kernel_pmap;
#include <vaxnb/ka820.h>
#define CSR	((caddr_t) 0x20088000)
		pmap_enter(kernel_pmap, ka820_csr, CSR,
					VM_PROT_READ|VM_PROT_WRITE, FALSE);
#undef CSR
	}
#endif	VAX820
}

/*
 * Initialize the RPB (Restart Parameter Block)
 */

#include <vax/rpb.h>

rpb_init()
{
	struct rpb	*p;
	long		*q;
	int		i;
	extern		doadump();

#if	MACH_LOAD
	p = (struct rpb *) 0;	/* local memory */
#else	MACH_LOAD
	p = (struct rpb *) (((unsigned)&rpb) & ~SYSBASE);
#endif	MACH_LOAD
	p->rp_selfref = p;
	p->rp_dumprout = (int (*)()) PHYS(doadump);
	q = (long *) ((int) p->rp_dumprout);

	p->rp_checksum = 0;
	for (i = 0; i < 31; i++)
		p->rp_checksum += *q++;

	p->rp_flag = 0;
}

size_memory()
{
	register long	look, max;
	extern long	esym;

	switch (cpu) {
#if	VAX6200
	case VAX_6200:
	{
		extern long boot_regs[];
		struct cca *ccp = (struct cca *) boot_regs[7];

		cca_size = ccp->size;
		ccap = ccp;
		mem_bitmap_size = ccp->bitmap_sz;
		mem_bitmap = (vm_offset_t) ccp->bitmap;
		look = mem_bitmap;
		break;
	}
#endif	VAX6200
#if	VAX650
	case VAX_650:
	{
		extern long boot_regs[];

		mem_bitmap_size = boot_regs[7];
		mem_bitmap = (vm_offset_t) boot_regs[8];
		look = mem_bitmap;
		break;
	}
#endif	VAX650
	default:
		/*
		 * count it up.
		 */
		max = loadpt + 512*1024*1024;
		for (look = loadpt; look < max; look += 64*1024)
			if (badaddr((caddr_t) look, 4))
				break;
		break;
	}
#if	VAX630
	if (cpu == VAX_630) {
	/*
	 *	On uVax II allow 2 pages for ROM.  Note that we are
	 *	ignoring the bitmap of good memory (and even overwriting
	 *	it).
	 *	Beats me why we do this -- rvb.
	 */
		look -= 1024;
	/*
 	 * Leave memory for bit map for maximal 16Meg memory.
	 */
		look -= 4*1024;

	}
#endif	VAX630
	mem_size = look - loadpt;

#if	MACH_KDB
	first_addr = PHYS(esym);
#else	MACH_KDB
	first_addr = PHYS(&end);
#endif	MACH_KDB

	vm_set_page_size();

	first_addr = round_page(first_addr);
	last_addr = trunc_page(look);
}		 	
