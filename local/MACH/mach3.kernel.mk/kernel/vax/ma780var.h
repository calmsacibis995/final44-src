/*
 ****************************************************************
 * Mach Operating System
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 ****************************************************************
 */
/*
 * HISTORY
 * $Log:	ma780var.h,v $
 * Revision 2.2  93/03/11  13:47:05  danner
 * 	u_long -> u_int
 * 	[93/03/09            danner]
 * 
 * Revision 2.1  89/08/03  16:26:58  rwd
 * Created.
 * 
 * 26-Aug-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Remove declaration of CPU_NUMBER.  It is defined in cpu.h.
 *	Automatically include cpu.h to pick up this definition.
 *
 */


#ifdef	KERNEL
#include <mach_mpm.h>
#else	KERNEL
#include <sys/features.h>
#endif	KERNEL

#include <vax/cpu_number.h>

/*
 * This file contains definitions related to the kernel structures
 * for dealing with the multiport memory.
 *
 * Each mpm has a mpm_hd structure.
 */

/*
 *	Per-mpm structure.
 */

struct	mpm_hd {
	short	ph_active;		/* set if mpm is active */
	struct	mpm_regs *ph_mpm;	/* virt addr of mpm */
	struct	mpm_regs *ph_physmpm;	/* phys addr of mpm */
};


#define MPMEM_ORIGIN	0x10000000
#define MPMEM_END	0x10800000


#define MP_TO_ME	0x1234
#define MP_FROM_ME	0x5678

		/* interrupt request/status */


#define MPISTAT_TO0	0x0000000f
#define MPISTAT_TO1	0x000000f0
#define MPISTAT_TO2	0x00000f00
#define MPISTAT_TO3	0x0000f000
#define MPISTAT_FROM0	0x00001111
#define MPISTAT_FROM1	0x00002222
#define MPISTAT_FROM2	0x00004444
#define MPISTAT_FROM3	0x00008888
#define MPISTAT_ALL	0x0000ffff
#define MPISTAT_TOME	(MPISTAT_to[cpu_number()])
#define MPISTAT_FROMME	(MPISTAT_from[cpu_number()])

#define MPIR_TO0	0x11110000
#define MPIR_TO1	0x22220000
#define MPIR_TO2	0x44440000
#define MPIR_TO3	0x88880000
#define MPIR_FROM0	0x000f0000
#define MPIR_FROM1	0x00f00000
#define MPIR_FROM2	0x0f000000
#define MPIR_FROM3	0xf0000000
#define MPIR_ALL	0xffff0000
#define MPIR_TOME	(MPIR_to[cpu_number()])
#define MPIR_FROMME	(MPIR_from[cpu_number()])

		/* interrupt request/status */


#define MPESTAT_TO0	0x0000000f
#define MPESTAT_TO1	0x000000f0
#define MPESTAT_TO2	0x00000f00
#define MPESTAT_TO3	0x0000f000
#define MPESTAT_FROM0	0x00001111
#define MPESTAT_FROM1	0x00002222
#define MPESTAT_FROM2	0x00004444
#define MPESTAT_FROM3	0x00008888
#define MPESTAT_ALL	0x0000ffff
#define MPESTAT_TOME	(MPESTAT_to[cpu_number()])
#define MPESTAT_FROMME	(MPESTAT_from[cpu_number()])

#define MPEN_TO0	0x000f0000
#define MPEN_TO1	0x00f00000
#define MPEN_TO2	0x0f000000
#define MPEN_TO3	0xf0000000
#define MPEN_FROM0	0x11110000
#define MPEN_FROM1	0x22220000
#define MPEN_FROM2	0x44440000
#define MPEN_FROM3	0x88880000
#define MPEN_ALL	0xffff0000
#define MPEN_TOME	(MPEN_to[cpu_number()])
#define MPEN_FROMME	(MPEN_from[cpu_number()])


/*
 * Kernel definitions related to mpm.
 */
#ifdef KERNEL
#if	NMACH_MPM > 0
int	nummpm;
int	*mpm_port_addr;
struct	mpm_hd mpm_hd[NMACH_MPM];
u_int MPISTAT_to[], MPISTAT_from[], MPIR_to[], MPIR_from[] ;
u_int MPESTAT_to[], MPESTAT_from[], MPEN_to[], MPEN_from[] ;
#endif	NMACH_MPM > 0
#endif
