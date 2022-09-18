/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	i386_init.c,v $
 * Revision 1.5.1.9  90/07/10  11:41:49  rvb
 * 	iPSC2: capture boot info
 * 	EXL:   flush
 * 	[90/06/16            rvb]
 * 
 * Revision 1.5.1.8  90/05/14  13:17:49  rvb
 * 	Bring kdb up to Mach 2.5 production quality.
 * 	[90/05/10            rvb]
 * 
 * 	Add play back buf for kdb at end of phys memory.
 * 	[90/05/01            rvb]
 * 
 * 	boottype & boothowto -> machdep.c
 * 	[90/04/23            rvb]
 * 
 * Revision 1.5.1.7  90/03/22  18:14:28  rvb
 * 	Let maxmem be the TOTAL memory size; it makes more sense.
 * 	[90/03/22            rvb]
 * 
 * Revision 1.5.1.6  90/03/10  00:27:16  rvb
 * 	You can use maxmem to constrain memory to maxmem bytes.
 * 	[90/03/10            rvb]
 * 
 * Revision 1.5.1.5  90/02/27  08:47:26  rvb
 * 	Set first_addr to 0x1000 and let pmap_valid_page decide whether
 * 	each page is useable or not.  From cnvmem to esym will not be
 * 	useable, but below cnvmem and above esym is
 * 	[90/02/19            rvb]
 * 
 * Revision 1.5.1.4  90/02/01  13:36:37  rvb
 * 	esym must always be defined.  This is as good a place as any.
 * 	[90/01/31            rvb]
 * 
 * Revision 1.5.1.3  89/12/28  12:43:10  rvb
 * 	Fix av_start & esym initialization, esp for MACH_KDB.
 * 	[89/12/26            rvb]
 * 
 * Revision 1.5.1.2  89/12/21  17:59:49  rvb
 * 	enable esym processing.
 * 
 * 
 * Revision 1.5.1.1  89/10/22  11:30:41  rvb
 * 	Setup of rootdevice should not be here.  And it was wrong.
 * 	[89/10/17            rvb]
 * 
 * 	Scary!  We've changed sbss to edata.  AND the coff loader
 * 	following the vuifile spec was actually aligning the bss 
 * 	on 4k boundaries.
 * 	[89/10/16            rvb]
 * 
 * Revision 1.5  89/04/05  12:57:39  rvb
 * 	Move extern out of function scope for gcc.
 * 	[89/03/04            rvb]
 * 
 * Revision 1.4  89/02/26  12:31:25  gm0w
 * 	Changes for cleanup.
 * 
 * 31-Dec-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Derived from MACH2.0 vax release.
 *
 */

/*
 *	File:	i386_init.c
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1986, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Basic initialization for I386
 */

#include <cputypes.h>
#include <mach_kdb.h>

#include <sys/types.h>
#include <sys/systm.h>
#include <i386/cpu.h>
#include <i386/pcb.h>
#include <mach/i386/vm_param.h>

#include <mach/vm_param.h>
#include <mach/vm_prot.h>
#include <vm/vm_page.h>

int		loadpt;

vm_size_t	mem_size;
vm_size_t	rawmem_size;
vm_offset_t	first_addr;
vm_offset_t	last_addr;

vm_offset_t	avail_start, avail_end;
vm_offset_t	virtual_avail, virtual_end;

/* parameters passed from bootstrap loader */
char end;
int cnvmem = 0;		/* must be in .data section */
int extmem = 0;
#ifdef	wheeze
#else	wheeze
char *esym = &end;
#endif	wheeze

#ifdef	iPSC2
/*
 * Node information is placed in the nxinfo structure by the NX
 * bootstrap loader. This is loacted at the address NXINFO_ADDR.
 * We extract the interesting information into globals for other
 * modules to use.
 */
#define NXINFO_ADDR (0x1100)

typedef struct nxinfo {
        unsigned long   node;           /* logical node number */
        unsigned long   num_nodes;      /* number of nodes in logical cube */
        unsigned long   dummy1;
        unsigned long   dummy2;
        unsigned long   physnode;       /* physical node slot number */
        unsigned long   basemem;        /* bytes of memory in node */
} *NXP;  

static NXP      nxp;
 
int ipsc2_this_node = 0;        /* must be in .data section */
int ipsc2_physnode = 0;
int ipsc2_num_nodes = 1;
int ipsc2_basemem = 0;
#endif	iPSC2

extern char	edata, end;

char *system_name;

i386_init()
{
#ifdef	iPSC2
	system_name = "iPSC2";
        /* Get nxinfo before it is wiped out by the stack */
        nxp = (NXP) NXINFO_ADDR;
        printf("node = %d, physnode = %d, numnodes = %d, basemem = %d\n",
                nxp->node, nxp->physnode, nxp->num_nodes, nxp->basemem);
        ipsc2_this_node = nxp->node;
        ipsc2_physnode = nxp->physnode;
        ipsc2_num_nodes = nxp->num_nodes;
        ipsc2_basemem = nxp->basemem;
#endif	iPSC2

#ifdef	AT386
	system_name = "AT386";
#endif	AT386
	/*
	 *	We won't really know our cpu number till after
	 *	we configure... but we still need to have a valid
	 *	cpu number for routines that use it.  Fortunately,
	 *	set_cpu_number will do the right thing for us here
	 *	because cpu_number doesn't know we have multi-port
	 *	memory yet.
	 */
	set_cpu_number();

/*
 *	bzero can't be called at this time since the pmap
 *	system is not initialized yet
 *
 *	bzero((caddr_t)&edata,(unsigned)(&end - &edata));
 */
 	bclear((caddr_t)&edata,(unsigned)(&end - &edata));

/*
 * Initialize the pic prior to any possible call to an spl.
 */
	picinit();
	size_memory();


	/*
	 *	Initialize kernel physical map, mapping the
	 *	region from loadpt to avail_start.
	 *	Kernel virtual address starts at VM_KERNEL_MIN_ADDRESS.
	 */

	avail_start = first_addr;
	avail_end = last_addr;
	printf("%s boot: memory from 0x%x to 0x%x\n",
		system_name, avail_start, avail_end);

	pmap_bootstrap(loadpt, &avail_start, &avail_end, &virtual_avail,
				&virtual_end);
	printf("i386_init: virtual_avail = %x, virtual_end = %x\n",
		virtual_avail, virtual_end);


}


int maxmem = 0;
size_memory()
{
	register vm_offset_t	look;


#ifdef	AT386
	look = 1024*1024 + extmem*1024;    /* extend memory starts at 1MB */
#endif	AT386

#ifdef	iPSC2
        look = ipsc2_basemem;
#endif	iPSC2

	if (maxmem)
		look = maxmem;
#if	MACH_KDB
	if (esym < &end)
		esym = &end;
	{extern char *play_back_buf;
	 extern char *play_back_ptr;
	 extern int   play_back_size;
	 look -= play_back_size;
	}
#else	MACH_KDB
	esym = &end;
#endif	MACH_KDB
	mem_size = look - loadpt;

	vm_set_page_size();
	first_addr = 0x1000;		/* bios leaves some stuff in low address */
	last_addr = trunc_page(look);
}		 	
