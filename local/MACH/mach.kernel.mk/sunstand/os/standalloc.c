/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	standalloc.c,v $
 * Revision 2.2  89/07/12  01:13:47  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	standalloc.c	1.22	88/02/08	*/

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

/*
 * standalloc.c
 *
 * ROM Monitor's routines for allocating resources needed on a temporary
 * basis (eg, for initialization or for boot drivers).
 *
 * Note, all requests are rounded up to fill a page.  This is not a
 * malloc() replacement!
 */

/* This flag causes printfs */
#undef PD

#ifdef sun4
#include <mon/cpu.map.h>
#else
#include <mon/cpu.map.h>
#endif
#include <mon/cpu.addrs.h>
#include <stand/saio.h>

/*
 * Artifice so standalone code uses same variable names as monitor's
 * for debugging.  FIXME?  Or leave this way?
 */
struct globram {
	char *g_nextrawvirt;
	char *g_nextdmaaddr;
	struct pgmapent g_nextmainmap;
} gp[1];


/*
 * Valid, supervisor-only, memory page's map entry.
 * (To be copied to a map entry and then modified.)
 */
#ifdef sun2
struct pgmapent mainmapinit =
	{1, PMP_SUP, VPM_MEMORY, 0, 0, 0, 0};
#else
struct pgmapent mainmapinit = 
	{1, PMP_SUP, VPM_MEMORY_NOCACHE, 0, 0, 0, 0};
#endif
#if defined (sun3) || defined (sun4)
extern	int	memory_avail;
#endif

/*
 * Say Something Here FIXME
 */
char *
resalloc(type, bytes)
	enum RESOURCES type;
	register unsigned bytes;
{
	register char *	addr;	/* Allocated address */
	register char *	raddr;	/* Running addr in loop */

	/* Initialize if needed. */
	if (gp->g_nextrawvirt == 0) {
#ifdef sun2
		reset_alloc(0x220000);
#endif
#if defined(sun3) || defined(sun4)
		reset_alloc(memory_avail);
#endif sun3 || sun4
	}

#ifdef PD
printf("resalloc(%x, %x) %x %x %x\n", type, bytes,
	gp->g_nextrawvirt, gp->g_nextdmaaddr,*(int*)&(gp->g_nextmainmap));
#endif PD
	if (bytes == 0)
		return (char *)0;

	bytes = (bytes + (BYTESPERPG - 1)) & ~(BYTESPERPG - 1);

	switch (type) {

	case RES_RAWVIRT:
		addr = gp->g_nextrawvirt;
		gp->g_nextrawvirt += bytes;
		return addr;

	case RES_DMAVIRT:
		addr = gp->g_nextdmaaddr;
		gp->g_nextdmaaddr += bytes;
		return addr;

	case RES_MAINMEM:
		addr = gp->g_nextrawvirt;
		gp->g_nextrawvirt += bytes;
		break;

	case RES_DMAMEM:
		addr = gp->g_nextdmaaddr;
		gp->g_nextdmaaddr += bytes;
		break;

	default:
		return (char *)0;
	}
	
	/*
	 * Now map in main memory.
	 * Note that this loop goes backwards!!
	 */
#ifdef PD
printf("mapping to %x returning %x gp %x\n", *(int*)&gp->g_nextmainmap, addr, gp);
#endif
	for (raddr = addr;
	     bytes > 0;
	     raddr += BYTESPERPG, bytes -= BYTESPERPG,
	      gp->g_nextmainmap.pm_page -= 1) {
		setpgmap(raddr, *(int *)&gp->g_nextmainmap);
		bzero((caddr_t)raddr, BYTESPERPG);
	} 

	return addr;
}

#ifdef sun2
struct pgmapent devmaps[] = {
/* MAINMEM */
	{1, PMP_SUP, MPM_MEMORY, 0, 0, 0, 0},		
/* OBIO */
	{1, PMP_SUP, MPM_IO, 0, 0, 0, 0},			
/* MBMEM */
	{1, PMP_SUP, VPM_VME0, 0, 0, 0, 0xFF000000 >> BYTES_PG_SHIFT},		
/* MBIO */
	{1, PMP_SUP, VPM_VME8, 0, 0, 0, 0xFFFF0000 >> BYTES_PG_SHIFT},		
/* VME16A16D */
	{1, PMP_SUP, VPM_VME8, 0, 0, 0, 0xFFFF0000 >> BYTES_PG_SHIFT},		
/* VME16A32D -- invalid */
	{0, PMP_SUP, VPM_VME8, 0, 0, 0, 0xFFFF0000 >> BYTES_PG_SHIFT},		
/* VME24A16D -- kludge low 8 megs only */
	{1, PMP_SUP, VPM_VME0, 0, 0, 0, 0xFF000000 >> BYTES_PG_SHIFT},		
/* VME24A32D -- invalid */
	{0, PMP_SUP, VPM_VME0, 0, 0, 0, 0xFF000000 >> BYTES_PG_SHIFT},		
/* VME32A16D -- invalid */
	{0, PMP_SUP, VPM_VME0, 0, 0, 0, 0x00000000 >> BYTES_PG_SHIFT},		
/* VME32A32D -- invalid */
	{0, PMP_SUP, VPM_VME0, 0, 0, 0, 0x00000000 >> BYTES_PG_SHIFT},		
};
#endif sun2

#ifdef sun3
struct pgmapent devmaps[] = {
/* MAINMEM */
	{1, PMP_SUP, VPM_MEMORY, 0, 0, 0, 0},		
/* OBIO */
	{1, PMP_SUP, VPM_IO, 0, 0, 0, 0},			
/* MBMEM */
	{1, PMP_SUP, VPM_VME16, 0, 0, 0, 0xFF000000 >> BYTES_PG_SHIFT},		
/* MBIO */
	{1, PMP_SUP, VPM_VME16, 0, 0, 0, 0xFFFF0000 >> BYTES_PG_SHIFT},		
/* VME16A16D */
	{1, PMP_SUP, VPM_VME16, 0, 0, 0, 0xFFFF0000 >> BYTES_PG_SHIFT},		
/* VME16A32D */
	{1, PMP_SUP, VPM_VME32, 0, 0, 0, 0xFFFF0000 >> BYTES_PG_SHIFT},		
/* VME24A16D */
	{1, PMP_SUP, VPM_VME16, 0, 0, 0, 0xFF000000 >> BYTES_PG_SHIFT},		
/* VME24A32D */
	{1, PMP_SUP, VPM_VME32, 0, 0, 0, 0xFF000000 >> BYTES_PG_SHIFT},		
/* VME32A16D */
	{1, PMP_SUP, VPM_VME16, 0, 0, 0, 0x00000000 >> BYTES_PG_SHIFT},		
/* VME32A32D */
	{1, PMP_SUP, VPM_VME32, 0, 0, 0, 0x00000000 >> BYTES_PG_SHIFT},		
};
#endif sun3

#ifdef sun4
struct pgmapent devmaps[] = {
/* MAINMEM */
	{1, PMP_SUP, VPM_MEMORY, 0, 0, 0, 0},		
/* OBIO */
	{1, PMP_SUP, VPM_IO, 0, 0, 0, 0},			
/* MBMEM */
	{1, PMP_SUP, VPM_VME16, 0, 0, 0, 0xFF000000 >> BYTES_PG_SHIFT},		
/* MBIO */
	{1, PMP_SUP, VPM_VME16, 0, 0, 0, 0xFFFF0000 >> BYTES_PG_SHIFT},		
/* VME16A16D */
	{1, PMP_SUP, VPM_VME16, 0, 0, 0, 0xFFFF0000 >> BYTES_PG_SHIFT},		
/* VME16A32D */
	{1, PMP_SUP, VPM_VME32, 0, 0, 0, 0xFFFF0000 >> BYTES_PG_SHIFT},		
/* VME24A16D */
	{1, PMP_SUP, VPM_VME16, 0, 0, 0, 0xFF000000 >> BYTES_PG_SHIFT},		
/* VME24A32D */
	{1, PMP_SUP, VPM_VME32, 0, 0, 0, 0xFF000000 >> BYTES_PG_SHIFT},		
/* VME32A16D */
	{1, PMP_SUP, VPM_VME16, 0, 0, 0, 0x00000000 >> BYTES_PG_SHIFT},		
/* VME32A32D */
	{1, PMP_SUP, VPM_VME32, 0, 0, 0, 0x00000000 >> BYTES_PG_SHIFT},		
};
#endif sun4

/*
 * devalloc() allocates virtual memory and maps it to a device
 * at a specific physical address.
 *
 * It returns the virtual address of that physical device.
 */
char *
devalloc(devtype, physaddr, bytes)
	enum MAPTYPES	devtype;
	register char *		physaddr;
	register unsigned	bytes;
{
	char *		addr;
	register char *	raddr;
	register int	pages;
	struct pgmapent	mapper;

#ifdef PD
printf("devalloc(%x, %x, %x) ", devtype, physaddr, bytes);
#endif
	if (!bytes)
		return (char *)0;

	pages = bytes + ((int)(physaddr) & (BYTESPERPG-1));
	addr = resalloc(RES_RAWVIRT, pages);
	if (!addr)
		return (char *)0;

	mapper = devmaps[(int)devtype];		/* Set it up first */
	mapper.pm_page += (int)(physaddr) >> BYTES_PG_SHIFT;

	for (raddr = addr;
	     pages > 0;
	     raddr += BYTESPERPG, pages -= BYTESPERPG,
	      mapper.pm_page += 1) {
#ifdef PD
printf("mapping to %x ", *(int *)&mapper);
#endif
		setpgmap(raddr, *(int *)&mapper);
	} 

#ifdef PD
printf("returns roughly %x\n", addr);
#endif
	return addr + ((int)(physaddr) & (BYTESPERPG-1));
}

/*
 * reset_alloc() does all the setup and all the releasing for the PROMs.
 */
reset_alloc(memsize)
	unsigned memsize;
{
#ifdef sun2
	int	i;
	struct bootparam *bp;
	int	*mem_p;
	int	memory_size;

	bp = *(romp->v_bootparam);
	mem_p = (int *)&(bp->bp_strings[96]);
	memory_size = *mem_p;
	if (memory_size)
		memsize = memory_size;
	*mem_p = memory_size + 0x20000;

	gp->g_nextrawvirt = (char *)0x160000;
#endif
#ifdef sun3
	int i, addr, pmeg;

	gp->g_nextrawvirt = (char *)0x200000;
	/*
	 * The monitor only allocates as many PMEGs as there is real
	 * memory so we have to set up more PMEGs for virtual memory
	 * on machines with only 2 megabytes.
	 */
	for (i=0; i < 0x100000; i += PGSPERSEG*BYTESPERPG) {	/* 1 Meg */
		addr = (int)gp->g_nextrawvirt + i;
		pmeg = addr / (PGSPERSEG*BYTESPERPG);
		setsegmap(addr, pmeg);
	}
#endif
#ifdef sun4
	/*
	 * The booter loads itself at 2 Meg so we add an extra Meg to
	 * get to a place to allocate virtual addresses and still have pmegs.
	 * This assumes that the minimum memory size for sun4 is 4 Meg.
	 */
	gp->g_nextrawvirt = (char *)0x300000;
#endif sun4
	gp->g_nextdmaaddr = DVMA_BASE;
	gp->g_nextmainmap = mainmapinit;
	gp->g_nextmainmap.pm_page = (memsize>>BYTES_PG_SHIFT) - 1;
#ifdef PD
printf("reset_alloc(%x) %x %x %x\n", memsize, *(int *)&mainmapinit, gp, *(int*)&gp->g_nextmainmap);
#endif
}
