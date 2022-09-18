h22431
s 00022/00011/02088
d D 8.5 95/06/02 17:25:16 ralph 28 27
c final changes for pmax 4.4-Lite II release
e
s 00005/00000/02094
d D 8.4 95/05/09 12:11:34 mckusick 27 26
c put in request to unmount all filesystems when rebooting
e
s 00001/00001/02093
d D 8.3 94/01/12 14:28:31 hibler 26 25
c entries_pageable set TRUE for buffer map (set vm_map.c change).
e
s 00011/00004/02083
d D 8.2 94/01/11 16:06:13 mckusick 25 24
c fix msgbuf so printfs from a panic will get logged to /var/adm/messages (from ralph)
e
s 00002/00002/02085
d D 8.1 93/06/16 18:27:34 bostic 24 23
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/02086
d D 7.22 93/06/16 18:26:15 mckusick 23 21
c final update from Ralph
e
s 00002/00002/02085
d R 8.1 93/06/10 23:07:29 bostic 22 21
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00030/00000/02057
d D 7.21 93/05/24 18:24:52 ralph 21 20
c added cpu_sysctl support for console
e
s 00006/00019/02051
d D 7.20 93/05/09 17:39:54 ralph 20 19
c new improved pmap changes
e
s 00001/00002/02069
d D 7.19 93/04/05 21:40:48 ralph 19 18
c allow auto reboot to work.
e
s 00013/00002/02058
d D 7.18 93/03/23 18:55:41 ralph 18 17
c changes from Rick Macklem
e
s 00005/00000/02055
d D 7.17 93/02/26 19:15:19 ralph 17 16
c added limited stacktrace for panics.
e
s 00009/00000/02046
d D 7.16 93/02/20 19:06:35 ralph 16 15
c added support for sysctl_hw()
e
s 00012/00001/02034
d D 7.15 93/02/15 11:04:00 ralph 15 14
c fix booting from disk boot program and memory mini-root.
e
s 00007/00007/02028
d D 7.14 93/02/04 19:56:55 ralph 14 13
c minor format cleanup
e
s 00195/00049/01840
d D 7.13 92/12/20 11:46:42 ralph 13 12
c changes from Rick Macklem
e
s 00857/00212/01032
d D 7.12 92/11/15 16:30:27 ralph 12 11
c updates from Rick Macklem for maxine.
e
s 00038/00043/01206
d D 7.11 92/10/24 14:12:18 ralph 11 10
c changed signals to use user stack.
e
s 00028/00028/01221
d D 7.10 92/10/11 11:23:15 bostic 10 9
c make kernel includes standard
e
s 00004/00003/01245
d D 7.9 92/07/10 18:10:26 torek 9 8
c ANSIfy syscall args
e
s 00003/00003/01245
d D 7.8 92/06/20 12:03:11 ralph 8 7
c fix minor typos.
e
s 00012/00006/01236
d D 7.7 92/04/20 23:57:02 mckusick 7 6
c add functionality for sigaltstack
e
s 00001/00000/01241
d D 7.6 92/04/14 14:42:30 mckusick 6 5
c null terminate the callout list
e
s 00036/00020/01205
d D 7.5 92/03/22 20:43:26 ralph 5 4
c added memory mini-root support.
e
s 00000/00005/01225
d D 7.4 92/03/15 19:16:58 ralph 4 3
c remove debug stuff
e
s 00003/00000/01227
d D 7.3 92/03/14 13:50:23 ralph 3 2
c fix FP initialization in setregs().
e
s 00492/00058/00735
d D 7.2 92/03/07 09:55:12 ralph 2 1
c chages for ds5000
e
s 00793/00000/00000
d D 7.1 92/01/07 17:29:20 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 24
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 24
I 24
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 24
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
D 2
 * Science Department and Ralph Campbell.
E 2
I 2
 * Science Department, The Mach Operating System project at
 * Carnegie-Mellon University and Ralph Campbell.
E 2
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: Utah $Hdr: machdep.c 1.63 91/04/24$
 *
E 2
 *	%W% (Berkeley) %G%
 */

I 2
/* from: Utah $Hdr: machdep.c 1.63 91/04/24$ */

E 2
D 10
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
E 10
I 10
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
I 21
#include <sys/ioctl.h>
#include <sys/tty.h>
E 21
#include <sys/user.h>
I 11
#include <sys/exec.h>
I 21
#include <sys/sysctl.h>
I 28
#include <sys/mount.h>
#include <sys/syscallargs.h>
E 28
E 21
E 11
E 10
#ifdef SYSVSHM
D 10
#include "shm.h"
E 10
I 10
#include <sys/shm.h>
E 10
#endif

D 10
#include "vm/vm.h"
#include "vm/vm_kern.h"
#include "vm/vm_page.h"
E 10
I 10
D 20
#include <vm/vm.h>
E 20
#include <vm/vm_kern.h>
D 20
#include <vm/vm_page.h>
E 20
E 10

D 10
#include "../include/cpu.h"
#include "../include/reg.h"
#include "../include/psl.h"
#include "../include/machMon.h"
D 2
#include "clockreg.h"
#include "pte.h"
E 2
I 2
#include "../include/pte.h"
E 10
I 10
#include <machine/cpu.h>
#include <machine/reg.h>
#include <machine/psl.h>
D 12
#include <machine/machMon.h>
E 12
#include <machine/pte.h>
I 12
#include <machine/dc7085cons.h>
E 12
E 10
E 2

I 12
#include <pmax/stand/dec_prom.h>

E 12
D 2
#define	MAXMEM	24*1024*CLSIZE	/* XXX - from cmap.h */
E 2
I 2
D 10
#include "../dev/device.h"
E 10
I 10
#include <pmax/dev/device.h>
I 12
#include <pmax/dev/sccreg.h>
I 13
#include <pmax/dev/ascreg.h>
E 13
E 12
E 10
E 2

I 2
D 10
#include "clockreg.h"
E 10
I 10
#include <pmax/pmax/clockreg.h>
I 12
#include <pmax/pmax/kn01.h>
#include <pmax/pmax/kn02.h>
#include <pmax/pmax/kmin.h>
#include <pmax/pmax/maxine.h>
I 13
#include <pmax/pmax/kn03.h>
E 13
#include <pmax/pmax/asic.h>
#include <pmax/pmax/turbochannel.h>
#include <pmax/pmax/pmaxtype.h>
#include <pmax/pmax/cons.h>
E 12
E 10

I 12
#include <pm.h>
#include <cfb.h>
#include <mfb.h>
#include <xcfb.h>
#include <dc.h>
#include <dtop.h>
#include <scc.h>
#include <le.h>
I 13
#include <asc.h>
E 13

#if NDC > 0
extern int dcGetc(), dcparam();
extern void dcPutc();
#endif
#if NDTOP > 0
extern int dtopKBDGetc();
#endif
#if NSCC > 0
extern int sccGetc(), sccparam();
extern void sccPutc();
#endif
extern int KBDGetc();
extern void fbPutc();
extern struct consdev cn_tab;

/* Will scan from max to min, inclusive */
static int tc_max_slot = KN02_TC_MAX;
static int tc_min_slot = KN02_TC_MIN;
I 13
static u_int tc_slot_phys_base [TC_MAX_SLOTS] = {
	/* use 3max for default values */
	KN02_PHYS_TC_0_START, KN02_PHYS_TC_1_START,
	KN02_PHYS_TC_2_START, KN02_PHYS_TC_3_START,
	KN02_PHYS_TC_4_START, KN02_PHYS_TC_5_START,
	KN02_PHYS_TC_6_START, KN02_PHYS_TC_7_START
};
E 13

I 16
/* the following is used externally (sysctl_hw) */
char	machine[] = "DEC";	/* cpu "architecture" */
char	cpu_model[30];

E 16
D 13

E 13
E 12
E 2
vm_map_t buffer_map;

/*
 * Declare these as initialized data so we can patch them.
 */
int	nswbuf = 0;
#ifdef	NBUF
int	nbuf = NBUF;
#else
D 12
int	nbuf = 0;
E 12
I 12
D 13
int	nbuf = 1024;
E 13
I 13
int	nbuf = 0;
E 13
E 12
#endif
#ifdef	BUFPAGES
int	bufpages = BUFPAGES;
#else
D 12
int	bufpages = 0;
E 12
I 12
D 13
int	bufpages = 1024;
E 13
I 13
int	bufpages = 0;
E 13
E 12
#endif
D 12
int	msgbufmapped;		/* set when safe to use msgbuf */
E 12
I 12
int	msgbufmapped = 0;	/* set when safe to use msgbuf */
E 12
int	maxmem;			/* max memory per process */
D 2
int	physmem = MAXMEM;	/* max supported memory, changes to actual */
E 2
I 2
int	physmem;		/* max supported memory, changes to actual */
I 12
int	pmax_boardtype;		/* Mother board type */
u_long	le_iomem;		/* 128K for lance chip via. ASIC */
I 13
u_long	asc_iomem;		/* and 7 * 8K buffers for the scsi */
u_long	asic_base;		/* Base address of I/O asic */
E 13
const	struct callback *callv;	/* pointer to PROM entry points */

void	(*tc_enable_interrupt)();
extern	int (*pmax_hardware_intr)();
void	pmax_slot_hand_fill();
int	kn02_intr(), kmin_intr(), xine_intr(), pmax_intr();
I 13
#ifdef DS5000_240
int	kn03_intr();
#endif
E 13
extern	int Mach_spl0(), Mach_spl1(), Mach_spl2(), Mach_spl3(), splhigh();
int	(*Mach_splnet)() = splhigh;
int	(*Mach_splbio)() = splhigh;
int	(*Mach_splimp)() = splhigh;
int	(*Mach_spltty)() = splhigh;
int	(*Mach_splclock)() = splhigh;
int	(*Mach_splstatclock)() = splhigh;
void	(*tc_slot_hand_fill)();
extern	volatile struct chiptime *Mach_clock_addr;
u_long	kmin_tc3_imask, xine_tc3_imask;
I 13
#ifdef DS5000_240
u_long	kn03_tc3_imask;
#endif
E 13
tc_option_t tc_slot_info[TC_MAX_LOGICAL_SLOTS];
static	void asic_init();
extern	void RemconsInit();
#ifdef DS5000
void	kn02_enable_intr(), kn02_slot_hand_fill(),
	kmin_enable_intr(), kmin_slot_hand_fill(),
	xine_enable_intr(), xine_slot_hand_fill(),
	tc_find_all_options();
I 13
#ifdef DS5000_240
void	kn03_enable_intr(), kn03_slot_hand_fill();
#endif
E 13
#endif /* DS5000 */

E 12
E 2
/*
 * safepri is a safe priority for sleep to set for a spin-wait
 * during autoconfiguration or after a panic.
 */
int	safepri = PSL_LOWIPL;

struct	user *proc0paddr;
struct	proc nullproc;		/* for use by swtch_exit() */

/*
 * Do all the stuff that locore normally does before calling main().
 * Process arguments passed to us by the prom monitor.
 * Return the first page address following the system.
 */
D 12
mach_init(argc, argv)
E 12
I 12
mach_init(argc, argv, code, cv)
E 12
	int argc;
	char *argv[];
I 12
	u_int code;
	const struct callback *cv;
E 12
{
	register char *cp;
	register int i;
	register unsigned firstaddr;
	register caddr_t v;
I 5
	caddr_t start;
E 5
	extern char edata[], end[];
	extern char MachUTLBMiss[], MachUTLBMissEnd[];
	extern char MachException[], MachExceptionEnd[];
D 20
#ifdef ATTR
	extern char *pmap_attributes;
#endif
E 20

D 5
	/* clear BSS segment, pages for u, and proc[0] page table */
	v = (caddr_t)pmax_round_page(end) + 2 * UPAGES * NBPG;
E 5
I 5
	/* clear the BSS segment */
	v = (caddr_t)pmax_round_page(end);
E 5
	bzero(edata, v - edata);

I 2
D 12
#ifdef DS5000
E 12
	/* check for direct boot from DS5000 PROM */
	if (argc > 0 && strcmp(argv[0], "boot") == 0) {
		argc--;
		argv++;
	}
D 12
#endif
E 12

E 2
	/* look at argv[0] and compute bootdev */
	makebootdev(argv[0]);

	/*
	 * Look at arguments passed to us and compute boothowto.
	 */
#ifdef GENERIC
	boothowto = RB_SINGLE | RB_ASKNAME;
#else
D 5
	boothowto = RB_SINGLE | RB_DFLTROOT;
E 5
I 5
	boothowto = RB_SINGLE;
E 5
#endif
I 2
#ifdef KADB
	boothowto |= RB_KDB;
#endif
E 2
	if (argc > 1) {
		for (i = 1; i < argc; i++) {
			for (cp = argv[i]; *cp; cp++) {
				switch (*cp) {
D 5
				case '-':
					continue;

E 5
D 2
				case '0': /* XXX */
				case '1': /* XXX */
				case '2': /* XXX */
				case '3': /* XXX */
				case '4': /* XXX */
				case '5': /* XXX */
				case '6': /* XXX */
				    {
					extern int sii_debug;

					sii_debug = *cp - '0';
					break;
				    }

E 2
				case 'a': /* autoboot */
					boothowto &= ~RB_SINGLE;
					break;

I 5
				case 'd': /* use compiled in default root */
					boothowto |= RB_DFLTROOT;
					break;

				case 'm': /* mini root present in memory */
					boothowto |= RB_MINIROOT;
					break;

E 5
				case 'n': /* ask for names */
					boothowto |= RB_ASKNAME;
D 5
					boothowto &= ~RB_DFLTROOT;
E 5
					break;

				case 'N': /* don't ask for names */
					boothowto &= ~RB_ASKNAME;
D 5
					boothowto |= RB_DFLTROOT;
E 5
				}
			}
		}
	}

I 5
#ifdef MFS
E 5
	/*
I 5
	 * Check to see if a mini-root was loaded into memory. It resides
	 * at the start of the next page just after the end of BSS.
	 */
D 15
	if (boothowto & RB_MINIROOT)
E 15
I 15
	if (boothowto & RB_MINIROOT) {
		boothowto |= RB_DFLTROOT;
E 15
		v += mfs_initminiroot(v);
I 15
	}
E 15
#endif

	/*
E 5
	 * Init mapping for u page(s) for proc[0], pm_tlbpid 1.
	 */
D 2
	firstaddr = pmax_round_page(end);
	curproc->p_addr = proc0paddr = (struct user *)firstaddr;
	curproc->p_regs = proc0paddr->u_pcb.pcb_regs;
E 2
I 2
D 5
	firstaddr = MACH_CACHED_TO_PHYS(pmax_round_page(end));
	curproc->p_addr = proc0paddr = (struct user *)
		MACH_PHYS_TO_CACHED(firstaddr);
E 5
I 5
	start = v;
	curproc->p_addr = proc0paddr = (struct user *)v;
E 5
	curproc->p_md.md_regs = proc0paddr->u_pcb.pcb_regs;
I 5
	firstaddr = MACH_CACHED_TO_PHYS(v);
E 5
E 2
	for (i = 0; i < UPAGES; i++) {
		MachTLBWriteIndexed(i,
			(UADDR + (i << PGSHIFT)) | (1 << VMMACH_TLB_PID_SHIFT),
			curproc->p_md.md_upte[i] = firstaddr | PG_V | PG_M);
		firstaddr += NBPG;
	}
I 5
	v += UPAGES * NBPG;
E 5
	MachSetPID(1);

	/*
	 * init nullproc for swtch_exit().
	 * init mapping for u page(s), pm_tlbpid 0
	 * This could be used for an idle process.
	 */
D 2
	nullproc.p_regs = ((struct user *)firstaddr)->u_pcb.pcb_regs;
E 2
I 2
D 5
	nullproc.p_md.md_regs =
		((struct user *)MACH_PHYS_TO_CACHED(firstaddr))->u_pcb.pcb_regs;
E 5
I 5
	nullproc.p_addr = (struct user *)v;
D 20
	nullproc.p_md.md_regs = ((struct user *)v)->u_pcb.pcb_regs;
E 20
I 20
	nullproc.p_md.md_regs = nullproc.p_addr->u_pcb.pcb_regs;
	bcopy("nullproc", nullproc.p_comm, sizeof("nullproc"));
E 20
E 5
E 2
	for (i = 0; i < UPAGES; i++) {
		nullproc.p_md.md_upte[i] = firstaddr | PG_V | PG_M;
		firstaddr += NBPG;
	}
I 5
	v += UPAGES * NBPG;
E 5

I 5
	/* clear pages for u areas */
	bzero(start, v - start);

E 5
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
D 2
	 * Find out how much memory is available.
E 2
I 2
	 * Determine what model of computer we are running on.
E 2
	 */
D 2
	physmem = btoc(v - KERNBASE);
	cp = (char *)(MACH_UNCACHED_MEMORY_ADDR + (physmem << PGSHIFT));
	while (cp < (char *)MACH_UNCACHED_FRAME_BUFFER_ADDR) {
		if (badaddr(cp, 4))
			break;
		cp += NBPG;
		physmem++;
E 2
I 2
D 12
	{
		char *(*f)() = (char *(*)())MACH_MON_GETENV2;

		if (cp = (*f)("systype"))
E 12
I 12
	if (code == DEC_PROM_MAGIC) {
		callv = cv;
		i = (*cv->getsysid)();
		cp = "";
	} else {
		callv = &callvec;
		if (cp = (*callv->getenv)("systype"))
E 12
			i = atoi(cp);
D 12
		else
E 12
I 12
		else {
E 12
			cp = "";
D 12

		/* check for MIPS based platform */
		if (((i >> 24) & 0xFF) != 0x82) {
			printf("Unknown System type '%s'\n", cp);
			boot(RB_HALT | RB_NOSYNC);
E 12
I 12
			i = 0;
E 12
		}
E 2
	}
I 12
	/* check for MIPS based platform */
	if (((i >> 24) & 0xFF) != 0x82) {
D 14
		printf("Unknown System type '%s'\n", cp);
E 14
I 14
		printf("Unknown System type '%s' 0x%x\n", cp, i);
E 14
		boot(RB_HALT | RB_NOSYNC);
	}
E 12
D 2
	maxmem = physmem + btoc(KERNBASE);
E 2

I 2
	/* check what model platform we are running on */
D 12
	switch ((i >> 16) & 0xFF) {
#ifdef DS3100
	case 1:	/* DS3100 Pmax */
E 12
I 12
	pmax_boardtype = ((i >> 16) & 0xff);
	switch (pmax_boardtype) {
	case DS_PMAX:	/* DS3100 Pmax */
E 12
		/*
D 12
		 * Find out how much memory is available.
E 12
I 12
		 * Set up interrupt handling and I/O addresses.
E 12
		 */
D 12
		physmem = btoc(v - KERNBASE);
		cp = (char *)MACH_PHYS_TO_UNCACHED(physmem << PGSHIFT);
		while (cp < (char *)MACH_MAX_MEM_ADDR) {
			if (badaddr(cp, 4))
				break;
			cp += NBPG;
			physmem++;
		}
E 12
I 12
		pmax_hardware_intr = pmax_intr;
		Mach_splnet = Mach_spl1;
		Mach_splbio = Mach_spl0;
		Mach_splimp = Mach_spl1;
		Mach_spltty = Mach_spl2;
		Mach_splclock = Mach_spl3;
		Mach_splstatclock = Mach_spl3;
		Mach_clock_addr = (volatile struct chiptime *)
			MACH_PHYS_TO_UNCACHED(KN01_SYS_CLOCK);
		pmax_slot_hand_fill();
I 16
		strcpy(cpu_model, "3100");
E 16
E 12
		break;
D 12
#endif
E 12

#ifdef DS5000
D 12
	case 2:	/* DS5000 3max */
	    {
		extern void tc_find_all_options();
E 12
I 12
	case DS_3MAX:	/* DS5000/200 3max */
		{
		volatile int *csr_addr =
			(volatile int *)MACH_PHYS_TO_UNCACHED(KN02_SYS_CSR);
E 12

D 25
		/* disable all TURBOchannel interrupts */
E 25
I 25
		/*
		 * Enable ECC memory correction, turn off LEDs, and
		 * disable all TURBOchannel interrupts.
		 */
E 25
D 12
		i = *(volatile int *)MACH_SYS_CSR_ADDR;
		*(volatile int *)MACH_SYS_CSR_ADDR = i & ~(MACH_CSR_MBZ | 0xFF);
E 12
I 12
		i = *csr_addr;
D 25
		*csr_addr = i & ~(KN02_CSR_WRESERVED | 0xFF);
E 25
I 25
		*csr_addr = (i & ~(KN02_CSR_WRESERVED | KN02_CSR_IOINTEN)) |
			KN02_CSR_CORRECT | 0xff;
E 25
E 12

I 12
		tc_slot_hand_fill = kn02_slot_hand_fill;
		pmax_hardware_intr = kn02_intr;
		tc_enable_interrupt = kn02_enable_intr;
		Mach_splnet = Mach_spl0;
		Mach_splbio = Mach_spl0;
		Mach_splimp = Mach_spl0;
		Mach_spltty = Mach_spl0;
		Mach_splclock = Mach_spl1;
		Mach_splstatclock = Mach_spl1;
		Mach_clock_addr = (volatile struct chiptime *)
			MACH_PHYS_TO_UNCACHED(KN02_SYS_CLOCK);

E 12
		/*
		 * Probe the TURBOchannel to see what controllers are present.
		 */
		tc_find_all_options();

		/* clear any memory errors from probes */
D 12
		*(unsigned *)MACH_ERROR_ADDR = 0;
E 12
I 12
		*(unsigned *)MACH_PHYS_TO_UNCACHED(KN02_SYS_ERRADR) = 0;
		}
I 16
		strcpy(cpu_model, "5000/200");
E 16
		break;
E 12

I 12
	case DS_3MIN:	/* DS5000/1xx 3min */
		tc_max_slot = KMIN_TC_MAX;
		tc_min_slot = KMIN_TC_MIN;
I 13
		tc_slot_phys_base[0] = KMIN_PHYS_TC_0_START;
		tc_slot_phys_base[1] = KMIN_PHYS_TC_1_START;
		tc_slot_phys_base[2] = KMIN_PHYS_TC_2_START;
		asic_base = MACH_PHYS_TO_UNCACHED(KMIN_SYS_ASIC);
E 13
		tc_slot_hand_fill = kmin_slot_hand_fill;
		pmax_hardware_intr = kmin_intr;
		tc_enable_interrupt = kmin_enable_intr;
I 18
		kmin_tc3_imask = (KMIN_INTR_CLOCK | KMIN_INTR_PSWARN |
			KMIN_INTR_TIMEOUT);
E 18

E 12
		/*
D 12
		 * Find out how much memory is available.
E 12
I 12
		 * Since all the motherboard interrupts come through the
		 * I/O ASIC, it has to be turned off for all the spls and
		 * since we don't know what kinds of devices are in the
		 * turbochannel option slots, just splhigh().
E 12
		 */
D 12
		physmem = btoc(v - KERNBASE);
		cp = (char *)MACH_PHYS_TO_UNCACHED(physmem << PGSHIFT);
		while (cp < (char *)MACH_MAX_MEM_ADDR) {
			if (badaddr(cp, 4))
				break;
			*(int *)cp = 0xa5a5a5a5;
			/*
			 * Data will persist on the bus if we read it right
			 * away. Have to be tricky here.
			 */
			((int *)cp)[4] = 0x5a5a5a5a;
			MachEmptyWriteBuffer();
			if (*(int *)cp != 0xa5a5a5a5)
				break;
			cp += NBPG;
			physmem++;
		}
E 12
I 12
		Mach_splnet = splhigh;
		Mach_splbio = splhigh;
		Mach_splimp = splhigh;
		Mach_spltty = splhigh;
		Mach_splclock = splhigh;
		Mach_splstatclock = splhigh;
		Mach_clock_addr = (volatile struct chiptime *)
			MACH_PHYS_TO_UNCACHED(KMIN_SYS_CLOCK);

		/*
		 * Probe the TURBOchannel to see what controllers are present.
		 */
		tc_find_all_options();

		/*
		 * Initialize interrupts.
		 */
D 13
		*(u_int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_IMSK) = KMIN_IM0;
		*(u_int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_INTR) = 0;
E 13
I 13
		*(u_int *)ASIC_REG_IMSK(asic_base) = KMIN_IM0;
		*(u_int *)ASIC_REG_INTR(asic_base) = 0;
E 13
		/* clear any memory errors from probes */
		*(unsigned *)MACH_PHYS_TO_UNCACHED(KMIN_REG_TIMEOUT) = 0;
I 16
		strcpy(cpu_model, "5000/1xx");
E 16
E 12
		break;
D 12
	    }
#endif DS5000
E 12

D 12
	case 5:	/* DS5800 Isis */
	case 6:	/* DS5400 MIPSfair */
E 12
I 12
	case DS_MAXINE:	/* DS5000/xx maxine */
		tc_max_slot = XINE_TC_MAX;
		tc_min_slot = XINE_TC_MIN;
I 13
		tc_slot_phys_base[0] = XINE_PHYS_TC_0_START;
		tc_slot_phys_base[1] = XINE_PHYS_TC_1_START;
		asic_base = MACH_PHYS_TO_UNCACHED(XINE_SYS_ASIC);
E 13
		tc_slot_hand_fill = xine_slot_hand_fill;
		pmax_hardware_intr = xine_intr;
		tc_enable_interrupt = xine_enable_intr;
		Mach_splnet = Mach_spl3;
		Mach_splbio = Mach_spl3;
		Mach_splimp = Mach_spl3;
		Mach_spltty = Mach_spl3;
		Mach_splclock = Mach_spl1;
		Mach_splstatclock = Mach_spl1;
		Mach_clock_addr = (volatile struct chiptime *)
			MACH_PHYS_TO_UNCACHED(XINE_SYS_CLOCK);

		/*
		 * Probe the TURBOchannel to see what controllers are present.
		 */
		tc_find_all_options();

		/*
		 * Initialize interrupts.
		 */
D 13
		*(u_int *)MACH_PHYS_TO_UNCACHED(XINE_REG_IMSK) = XINE_IM0;
		*(u_int *)MACH_PHYS_TO_UNCACHED(XINE_REG_INTR) = 0;
E 13
I 13
		*(u_int *)ASIC_REG_IMSK(asic_base) = XINE_IM0;
		*(u_int *)ASIC_REG_INTR(asic_base) = 0;
E 13
		/* clear any memory errors from probes */
		*(unsigned *)MACH_PHYS_TO_UNCACHED(XINE_REG_TIMEOUT) = 0;
I 16
		strcpy(cpu_model, "5000/25");
E 16
		break;
I 13

#ifdef DS5000_240
	case DS_3MAXPLUS:	/* DS5000/240 3max+ UNTESTED!! */
		tc_max_slot = KN03_TC_MAX;
		tc_min_slot = KN03_TC_MIN;
		tc_slot_phys_base[0] = KN03_PHYS_TC_0_START;
		tc_slot_phys_base[1] = KN03_PHYS_TC_1_START;
		tc_slot_phys_base[2] = KN03_PHYS_TC_2_START;
		asic_base = MACH_PHYS_TO_UNCACHED(KN03_SYS_ASIC);
		tc_slot_hand_fill = kn03_slot_hand_fill;
		pmax_hardware_intr = kn03_intr;
		tc_enable_interrupt = kn03_enable_intr;
I 18
		kn03_tc3_imask = KN03_INTR_PSWARN;
E 18

		Mach_splnet = Mach_spl0;
		Mach_splbio = Mach_spl0;
		Mach_splimp = Mach_spl0;
		Mach_spltty = Mach_spl0;
		Mach_splclock = Mach_spl1;
		Mach_splstatclock = Mach_spl1;
		Mach_clock_addr = (volatile struct chiptime *)
			MACH_PHYS_TO_UNCACHED(KN03_SYS_CLOCK);

		/*
		 * Probe the TURBOchannel to see what controllers are present.
		 */
		tc_find_all_options();

		/*
		 * Initialize interrupts.
		 */
		*(u_int *)ASIC_REG_IMSK(asic_base) = KN03_IM0;
		*(u_int *)ASIC_REG_INTR(asic_base) = 0;
		/* clear any memory errors from probes */
		*(unsigned *)MACH_PHYS_TO_UNCACHED(KN03_SYS_ERRADR) = 0;
I 16
		strcpy(cpu_model, "5000/240");
E 16
		break;
#endif /* DS5000_240 */
E 13
#endif /* DS5000 */

E 12
	default:
D 5
		printf("Unknown Box: systype 0x%x\n", i);
E 5
I 5
		printf("kernel not configured for systype 0x%x\n", i);
E 5
		boot(RB_HALT | RB_NOSYNC);
	}

I 12
	/*
	 * Find out how much memory is available.
I 25
	 * Be careful to save and restore the original contents for msgbuf.
E 25
	 */
	physmem = btoc(v - KERNBASE);
	cp = (char *)MACH_PHYS_TO_UNCACHED(physmem << PGSHIFT);
	while (cp < (char *)MACH_MAX_MEM_ADDR) {
		if (badaddr(cp, 4))
			break;
I 25
		i = *(int *)cp;
E 25
		*(int *)cp = 0xa5a5a5a5;
		/*
D 25
		 * Data will persist on the bus if we read it right
		 * away. Have to be tricky here.
E 25
I 25
		 * Data will persist on the bus if we read it right away.
		 * Have to be tricky here.
E 25
		 */
		((int *)cp)[4] = 0x5a5a5a5a;
		MachEmptyWriteBuffer();
		if (*(int *)cp != 0xa5a5a5a5)
			break;
I 25
		*(int *)cp = i;
E 25
		cp += NBPG;
		physmem++;
	}

E 12
	maxmem = physmem;

I 12
#if NLE > 0
E 12
E 2
	/*
I 12
	 * Grab 128K at the top of physical memory for the lance chip
	 * on machines where it does dma through the I/O ASIC.
I 13
	 * It must be physically contiguous and aligned on a 128K boundary.
E 13
	 */
D 13
	if (pmax_boardtype == DS_3MIN || pmax_boardtype == DS_MAXINE) {
E 13
I 13
	if (pmax_boardtype == DS_3MIN || pmax_boardtype == DS_MAXINE ||
		pmax_boardtype == DS_3MAXPLUS) {
E 13
		maxmem -= btoc(128 * 1024);
		le_iomem = (maxmem << PGSHIFT);
	}
#endif /* NLE */
I 13
#if NASC > 0
	/*
	 * Ditto for the scsi chip. There is probably a way to make asc.c
	 * do dma without these buffers, but it would require major
	 * re-engineering of the asc driver.
	 * They must be 8K in size and page aligned.
	 */
	if (pmax_boardtype == DS_3MIN || pmax_boardtype == DS_MAXINE ||
		pmax_boardtype == DS_3MAXPLUS) {
		maxmem -= btoc(ASC_NCMD * 8192);
		asc_iomem = (maxmem << PGSHIFT);
	}
#endif /* NASC */
E 13

	/*
E 12
	 * Initialize error message buffer (at end of core).
	 */
	maxmem -= btoc(sizeof (struct msgbuf));
D 2
	msgbufp = (struct msgbuf *)(maxmem << PGSHIFT);
E 2
I 2
	msgbufp = (struct msgbuf *)(MACH_PHYS_TO_CACHED(maxmem << PGSHIFT));
E 2
	msgbufmapped = 1;

	/*
	 * Allocate space for system data structures.
D 2
	 * The first available real memory address is in "firstaddr".
E 2
	 * The first available kernel virtual address is in "v".
	 * As pages of kernel virtual memory are allocated, "v" is incremented.
D 2
	 * As pages of memory are allocated and cleared,
	 * "firstaddr" is incremented.
	 */
	/*
E 2
I 2
	 *
E 2
	 * These data structures are allocated here instead of cpu_startup()
	 * because physical memory is directly addressable. We don't have
	 * to map these into virtual address space.
	 */
D 2
	firstaddr = (unsigned)v;
E 2
I 2
D 5
	cp = (char *)v;
E 5
I 5
	start = v;
E 5
E 2

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
D 20
#ifdef ATTR
	/* this is allocated here just to save a few bytes */
	valloc(pmap_attributes, char, physmem);
#endif
E 20

	/*
	 * Determine how many buffers to allocate.
	 * We allocate more buffer space than the BSD standard of
	 * using 10% of memory for the first 2 Meg, 5% of remaining.
D 28
	 * We just allocate a flat 10%.  Insure a minimum of 16 buffers.
E 28
I 28
	 * We just allocate a flat 10%.  Ensure a minimum of 16 buffers.
E 28
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
D 20
	v = (caddr_t)pmax_round_page(v);
E 20
D 2
	bzero((caddr_t)firstaddr, (unsigned)v - firstaddr);
E 2
I 2
D 5
	bzero((caddr_t)cp, v - (caddr_t)cp);
E 5
I 5
	bzero(start, v - start);
E 5
E 2

	/*
	 * Initialize the virtual memory system.
	 */
D 2
	pmap_bootstrap((vm_offset_t)v);
E 2
I 2
D 20
	pmap_bootstrap((vm_offset_t)MACH_CACHED_TO_PHYS(v));
E 20
I 20
	pmap_bootstrap((vm_offset_t)v);
E 20
E 2
}

/*
 * Console initialization: called early on from main,
 * before vm init or startup.  Do enough configuration
 * to choose and initialize a console.
I 2
D 12
 * XXX need something better here.
E 12
E 2
 */
consinit()
{
I 12
	register int kbd, crt;
	register char *oscon;
E 12

D 12
#include "pm.h"
#if NPM > 0
D 2
	/*
	 * Initialize the console before we print anything out.
	 */
	pminit();
E 2
I 2
	if (pminit())
		return;
E 2
#endif
E 12
I 12
	/*
	 * First get the "osconsole" environment variable.
	 */
	oscon = (*callv->getenv)("osconsole");
	crt = kbd = -1;
	if (oscon && *oscon >= '0' && *oscon <= '9') {
		kbd = *oscon - '0';
		cn_tab.cn_screen = 0;
		while (*++oscon) {
			if (*oscon == ',')
				cn_tab.cn_screen = 1;
			else if (cn_tab.cn_screen &&
			    *oscon >= '0' && *oscon <= '9') {
				crt = kbd;
				kbd = *oscon - '0';
				break;
			}
		}
	}
	if (pmax_boardtype == DS_PMAX && kbd == 1)
		cn_tab.cn_screen = 1;
I 15
	/*
	 * The boot program uses PMAX ROM entrypoints so the ROM sets
	 * osconsole to '1' like the PMAX.
	 */
	if (pmax_boardtype == DS_3MAX && crt == -1 && kbd == 1) {
		cn_tab.cn_screen = 1;
		crt = 0;
		kbd = 7;
	}
E 15
E 12
I 2

D 12
#include "cfb.h"
#if NCFB > 0
	{
		register struct pmax_ctlr *cp;
		register struct driver *drp;
E 12
I 12
	/*
	 * First try the keyboard/crt cases then fall through to the
	 * remote serial lines.
	 */
	if (cn_tab.cn_screen) {
	    switch (pmax_boardtype) {
	    case DS_PMAX:
#if NDC > 0 && NPM > 0
		if (pminit()) {
			cn_tab.cn_dev = makedev(DCDEV, DCKBD_PORT);
			cn_tab.cn_getc = KBDGetc;
			cn_tab.cn_kbdgetc = dcGetc;
			cn_tab.cn_putc = fbPutc;
			cn_tab.cn_disabled = 0;
			return;
		}
#endif /* NDC and NPM */
		goto remcons;
E 12

D 12
		for (cp = pmax_cinit; drp = cp->pmax_driver; cp++) {
			if (strcmp(drp->d_name, "cfb"))
				continue;
			if (cfb_init(cp))
				return;
E 12
I 12
	    case DS_MAXINE:
#if NDTOP > 0
		if (kbd == 3) {
			cn_tab.cn_dev = makedev(DTOPDEV, 0);
			cn_tab.cn_getc = dtopKBDGetc;
			cn_tab.cn_putc = fbPutc;
		} else
#endif /* NDTOP */
			goto remcons;
#if NXCFB > 0
		if (crt == 3 && xcfbinit()) {
			cn_tab.cn_disabled = 0;
			return;
E 12
		}
I 12
#endif /* XCFB */
		break;

	    case DS_3MAX:
#if NDC > 0
		if (kbd == 7) {
			cn_tab.cn_dev = makedev(DCDEV, DCKBD_PORT);
			cn_tab.cn_getc = KBDGetc;
			cn_tab.cn_kbdgetc = dcGetc;
			cn_tab.cn_putc = fbPutc;
		} else
#endif /* NDC */
			goto remcons;
		break;

	    case DS_3MIN:
I 13
	    case DS_3MAXPLUS:
E 13
#if NSCC > 0
		if (kbd == 3) {
			cn_tab.cn_dev = makedev(SCCDEV, SCCKBD_PORT);
			cn_tab.cn_getc = KBDGetc;
			cn_tab.cn_kbdgetc = sccGetc;
			cn_tab.cn_putc = fbPutc;
		} else
#endif /* NSCC */
			goto remcons;
		break;

	    default:
		goto remcons;
	    };

	    /*
	     * Check for a suitable turbochannel frame buffer.
	     */
	    if (tc_slot_info[crt].driver_name) {
#if NMFB > 0
		if (strcmp(tc_slot_info[crt].driver_name, "mfb") == 0 &&
		    mfbinit(tc_slot_info[crt].k1seg_address)) {
			cn_tab.cn_disabled = 0;
			return;
		}
#endif /* NMFB */
#if NCFB > 0
		if (strcmp(tc_slot_info[crt].driver_name, "cfb") == 0 &&
		    cfbinit(tc_slot_info[crt].k1seg_address)) {
			cn_tab.cn_disabled = 0;
			return;
		}
#endif /* NCFB */
		printf("crt: %s not supported as console device\n",
			tc_slot_info[crt].driver_name);
	    } else
		printf("No crt console device in slot %d\n", crt);
E 12
	}
D 12
#endif
E 12
I 12
remcons:
	/*
	 * Configure a serial port as a remote console.
	 */
	cn_tab.cn_screen = 0;
	switch (pmax_boardtype) {
	case DS_PMAX:
#if NDC > 0
		if (kbd == 4)
			cn_tab.cn_dev = makedev(DCDEV, DCCOMM_PORT);
		else
			cn_tab.cn_dev = makedev(DCDEV, DCPRINTER_PORT);
		cn_tab.cn_getc = dcGetc;
		cn_tab.cn_putc = dcPutc;
#endif /* NDC */
		break;

	case DS_3MAX:
#if NDC > 0
		cn_tab.cn_dev = makedev(DCDEV, DCPRINTER_PORT);
		cn_tab.cn_getc = dcGetc;
		cn_tab.cn_putc = dcPutc;
#endif /* NDC */
		break;

	case DS_3MIN:
I 13
	case DS_3MAXPLUS:
E 13
#if NSCC > 0
		cn_tab.cn_dev = makedev(SCCDEV, SCCCOMM3_PORT);
		cn_tab.cn_getc = sccGetc;
		cn_tab.cn_putc = sccPutc;
#endif /* NSCC */
		break;

	case DS_MAXINE:
#if NSCC > 0
		cn_tab.cn_dev = makedev(SCCDEV, SCCCOMM2_PORT);
		cn_tab.cn_getc = sccGetc;
		cn_tab.cn_putc = sccPutc;
#endif /* NSCC */
		break;
	};
	if (cn_tab.cn_dev == NODEV)
		printf("Can't configure console!\n");
E 12
E 2
}

/*
 * cpu_startup: allocate memory for variable-sized tables,
 * initialize cpu, and do autoconfiguration.
 */
cpu_startup()
{
	register unsigned i;
D 2
	register caddr_t v, firstaddr;
E 2
I 2
	register caddr_t v;
E 2
	int base, residual;
D 20
	extern long Usrptsize;
	extern struct map *useriomap;
E 20
I 20
	vm_offset_t minaddr, maxaddr;
	vm_size_t size;
E 20
#ifdef DEBUG
	extern int pmapdebug;
	int opmapdebug = pmapdebug;
D 20
#endif
	vm_offset_t minaddr, maxaddr;
	vm_size_t size;
E 20

D 20
#ifdef DEBUG
E 20
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
D 8
	buffer_map = kmem_suballoc(kernel_map, (vm_offset_t)&buffers,
E 8
I 8
	buffer_map = kmem_suballoc(kernel_map, (vm_offset_t *)&buffers,
E 8
D 26
				   &maxaddr, size, FALSE);
E 26
I 26
				   &maxaddr, size, TRUE);
E 26
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
D 20
				 16*NCARGS, TRUE);
E 20
I 20
				 16 * NCARGS, TRUE);
E 20
	/*
	 * Allocate a submap for physio
	 */
	phys_map = kmem_suballoc(kernel_map, &minaddr, &maxaddr,
				 VM_PHYS_SIZE, TRUE);

	/*
	 * Finally, allocate mbuf pool.  Since mclrefcnt is an off-size
	 * we use the more space efficient malloc in place of kmem_alloc.
	 */
	mclrefcnt = (char *)malloc(NMBCLUSTERS+CLBYTES/MCLBYTES,
				   M_MBUF, M_NOWAIT);
	bzero(mclrefcnt, NMBCLUSTERS+CLBYTES/MCLBYTES);
D 8
	mb_map = kmem_suballoc(kernel_map, (vm_offset_t)&mbutl, &maxaddr,
E 8
I 8
	mb_map = kmem_suballoc(kernel_map, (vm_offset_t *)&mbutl, &maxaddr,
E 8
			       VM_MBUF_SIZE, FALSE);
	/*
	 * Initialize callouts
	 */
	callfree = callout;
	for (i = 1; i < ncallout; i++)
		callout[i-1].c_next = &callout[i];
I 6
	callout[i-1].c_next = NULL;
E 6

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
I 21
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

	/* all sysctl names at this level are terminal */
	if (namelen != 1)
		return (ENOTDIR);		/* overloaded */

	switch (name[0]) {
	case CPU_CONSDEV:
		return (sysctl_rdstruct(oldp, oldlenp, newp, &cn_tab.cn_dev,
		    sizeof cn_tab.cn_dev));
	default:
		return (EOPNOTSUPP);
	}
	/* NOTREACHED */
E 21
}

/*
 * Set registers on exec.
 * Clear all registers except sp, pc.
 */
setregs(p, entry, retval)
	register struct proc *p;
	u_long entry;
D 28
	int retval[2];
E 28
I 28
	register_t retval[2];
E 28
{
D 2
	int sp = p->p_regs[SP];
E 2
I 2
	int sp = p->p_md.md_regs[SP];
I 3
	extern struct proc *machFPCurProcPtr;
E 3
E 2

D 2
	bzero((caddr_t)p->p_regs, (FSR + 1) * sizeof(int));
	p->p_regs[SP] = sp;
	p->p_regs[PC] = entry;
	p->p_regs[PS] = PSL_USERSET;
E 2
I 2
	bzero((caddr_t)p->p_md.md_regs, (FSR + 1) * sizeof(int));
	p->p_md.md_regs[SP] = sp;
D 11
	p->p_md.md_regs[PC] = entry;
E 11
I 11
	p->p_md.md_regs[PC] = entry & ~3;
E 11
	p->p_md.md_regs[PS] = PSL_USERSET;
E 2
	p->p_md.md_flags & ~MDP_FPUSED;
I 3
	if (machFPCurProcPtr == p)
D 5
		machFPCurProcPtr == (struct proc *)0;
E 5
I 5
		machFPCurProcPtr = (struct proc *)0;
E 5
E 3
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
I 11
	struct	sigcontext sf_sc;	/* actual context */
E 11
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
D 28
	unsigned code;
E 28
I 28
	u_long code;
E 28
{
	register struct proc *p = curproc;
	register struct sigframe *fp;
D 7
	register struct sigacts *ps = p->p_sigacts;
E 7
I 7
D 11
	register struct sigacts *psp = p->p_sigacts;
E 7
	register struct sigcontext *scp;
E 11
	register int *regs;
I 11
	register struct sigacts *psp = p->p_sigacts;
E 11
	int oonstack, fsize;
	struct sigcontext ksc;
I 11
	extern char sigcode[], esigcode[];
E 11

D 2
	regs = p->p_regs;
E 2
I 2
	regs = p->p_md.md_regs;
E 2
D 7
	oonstack = ps->ps_onstack;
E 7
I 7
	oonstack = psp->ps_sigstk.ss_flags & SA_ONSTACK;
E 7
	/*
	 * Allocate and validate space for the signal handler
	 * context. Note that if the stack is in data space, the
	 * call to grow() is a nop, and the copyout()
	 * will fail if the process has not already allocated
	 * the space with a `brk'.
	 */
I 11
	fsize = sizeof(struct sigframe);
E 11
D 7
	if (!ps->ps_onstack && (ps->ps_sigonstack & sigmask(sig))) {
		scp = (struct sigcontext *)ps->ps_sigsp - 1;
		ps->ps_onstack = 1;
E 7
I 7
	if ((psp->ps_flags & SAS_ALTSTACK) &&
	    (psp->ps_sigstk.ss_flags & SA_ONSTACK) == 0 &&
	    (psp->ps_sigonstack & sigmask(sig))) {
D 11
		scp = (struct sigcontext *)(psp->ps_sigstk.ss_base +
D 8
		    psp->ps_sigstk.ss_size - 1;
E 8
I 8
		    psp->ps_sigstk.ss_size) - 1;
E 11
I 11
		fp = (struct sigframe *)(psp->ps_sigstk.ss_base +
					 psp->ps_sigstk.ss_size - fsize);
E 11
E 8
		psp->ps_sigstk.ss_flags |= SA_ONSTACK;
E 7
	} else
D 11
		scp = (struct sigcontext *)regs[SP] - 1;
	fp = (struct sigframe *)scp - 1;
E 11
I 11
		fp = (struct sigframe *)(regs[SP] - fsize);
E 11
	if ((unsigned)fp <= USRSTACK - ctob(p->p_vmspace->vm_ssize)) 
		(void)grow(p, (unsigned)fp);
I 11
#ifdef DEBUG
	if ((sigdebug & SDB_FOLLOW) ||
	    (sigdebug & SDB_KSTACK) && p->p_pid == sigpid)
		printf("sendsig(%d): sig %d ssp %x usp %x scp %x\n",
		       p->p_pid, sig, &oonstack, fp, &fp->sf_sc);
#endif
E 11
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
D 5
		if (p == machFPCurProcPtr) {
E 5
I 5
		if (p == machFPCurProcPtr)
E 5
			MachSaveCurFPState(p);
D 5
			machFPCurProcPtr = (struct proc *)0;
		}
E 5
D 2
		bcopy((caddr_t)&p->p_regs[F0], (caddr_t)ksc.sc_fpregs,
E 2
I 2
		bcopy((caddr_t)&p->p_md.md_regs[F0], (caddr_t)ksc.sc_fpregs,
E 2
			sizeof(ksc.sc_fpregs));
	}
D 11
	if (copyout((caddr_t)&ksc, (caddr_t)scp, sizeof(ksc))) {
E 11
I 11
	if (copyout((caddr_t)&ksc, (caddr_t)&fp->sf_sc, sizeof(ksc))) {
E 11
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
D 11
	regs[A2] = (int)scp;
E 11
I 11
	regs[A2] = (int)&fp->sf_sc;
E 11
	regs[A3] = (int)catcher;

	regs[PC] = (int)catcher;
	regs[SP] = (int)fp;
D 11
	regs[RA] = KERNBASE;	/* this causes a trap which we interpret as
				 * meaning "do a sigreturn". */
E 11
I 11
	/*
	 * Signal trampoline code is at base of user stack.
	 */
	regs[RA] = (int)PS_STRINGS - (esigcode - sigcode);
E 11
#ifdef DEBUG
D 11
	if ((sigdebug & SDB_KSTACK) && p->p_pid == sigpid)
		printf("sendsig(%d): sig %d ssp %x usp %x scp %x\n",
		       p->p_pid, sig, &oonstack, fp, fp->sf_scp);
E 11
I 11
	if ((sigdebug & SDB_FOLLOW) ||
	    (sigdebug & SDB_KSTACK) && p->p_pid == sigpid)
		printf("sendsig(%d): sig %d returns\n",
		       p->p_pid, sig);
E 11
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
I 9
D 28
struct sigreturn_args {
	struct sigcontext *sigcntxp;
};
E 28
E 9
/* ARGSUSED */
sigreturn(p, uap, retval)
	struct proc *p;
D 9
	struct args {
		struct sigcontext *sigcntxp;
	} *uap;
E 9
I 9
D 28
	struct sigreturn_args *uap;
E 9
	int *retval;
E 28
I 28
	struct sigreturn_args /* {
		syscallarg(struct sigcontext *) sigcntxp;
	} */ *uap;
	register_t *retval;
E 28
{
	register struct sigcontext *scp;
	register int *regs;
	struct sigcontext ksc;
	int error;

D 11
	register struct frame *frame;
	register int rf;
	struct sigcontext tsigc;
	int flags;

E 11
D 28
	scp = uap->sigcntxp;
E 28
I 28
	scp = SCARG(uap, sigcntxp);
E 28
#ifdef DEBUG
	if (sigdebug & SDB_FOLLOW)
		printf("sigreturn: pid %d, scp %x\n", p->p_pid, scp);
#endif
D 2
	regs = p->p_regs;
E 2
I 2
	regs = p->p_md.md_regs;
E 2
	/*
	 * Test and fetch the context structure.
	 * We grab it all at once for speed.
	 */
	error = copyin((caddr_t)scp, (caddr_t)&ksc, sizeof(ksc));
D 11
	if (error != 0 || ksc.sc_regs[ZERO] != 0xACEDBADE ||
	    (unsigned)ksc.sc_regs[SP] < (unsigned)regs[SP]) {
E 11
I 11
	if (error || ksc.sc_regs[ZERO] != 0xACEDBADE) {
E 11
#ifdef DEBUG
		if (!(sigdebug & SDB_FOLLOW))
			printf("sigreturn: pid %d, scp %x\n", p->p_pid, scp);
		printf("  old sp %x ra %x pc %x\n",
			regs[SP], regs[RA], regs[PC]);
		printf("  new sp %x ra %x pc %x err %d z %x\n",
			ksc.sc_regs[SP], ksc.sc_regs[RA], ksc.sc_regs[PC],
			error, ksc.sc_regs[ZERO]);
#endif
D 11
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
E 11
		return (EINVAL);
	}
I 11
	scp = &ksc;
E 11
	/*
	 * Restore the user supplied information
	 */
D 7
	p->p_sigacts->ps_onstack = scp->sc_onstack & 01;
E 7
I 7
	if (scp->sc_onstack & 01)
		p->p_sigacts->ps_sigstk.ss_flags |= SA_ONSTACK;
	else
		p->p_sigacts->ps_sigstk.ss_flags &= ~SA_ONSTACK;
E 7
	p->p_sigmask = scp->sc_mask &~ sigcantmask;
D 11
	regs[PC] = ksc.sc_pc;
	bcopy((caddr_t)&ksc.sc_regs[1], (caddr_t)&regs[1],
		sizeof(ksc.sc_regs) - sizeof(int));
	ksc.sc_fpused = p->p_md.md_flags & MDP_FPUSED;
	if (ksc.sc_fpused)
D 2
		bcopy((caddr_t)ksc.sc_fpregs, (caddr_t)&p->p_regs[F0],
E 2
I 2
		bcopy((caddr_t)ksc.sc_fpregs, (caddr_t)&p->p_md.md_regs[F0],
E 2
			sizeof(ksc.sc_fpregs));
E 11
I 11
	regs[PC] = scp->sc_pc;
	bcopy((caddr_t)&scp->sc_regs[1], (caddr_t)&regs[1],
		sizeof(scp->sc_regs) - sizeof(int));
	if (scp->sc_fpused)
		bcopy((caddr_t)scp->sc_fpregs, (caddr_t)&p->p_md.md_regs[F0],
			sizeof(scp->sc_fpregs));
E 11
	return (EJUSTRETURN);
}

int	waittime = -1;

boot(howto)
	register int howto;
{
I 28
	struct proc *p = curproc;	/* XXX */
E 28

D 2
	trapDump("boot"); /* XXX */
E 2
	/* take a snap shot before clobbering any registers */
	if (curproc)
		savectx(curproc->p_addr, 0);

I 17
#ifdef DEBUG
	if (panicstr)
		stacktrace();
#endif

E 17
D 19
	howto |= RB_HALT; /* XXX */
E 19
	boothowto = howto;
D 11
	if ((howto&RB_NOSYNC) == 0 && waittime < 0 && bfreelist[0].b_forw) {
E 11
I 11
D 19
	if ((howto&RB_NOSYNC) == 0 && waittime < 0) {
E 19
I 19
	if ((howto & RB_NOSYNC) == 0 && waittime < 0) {
E 19
E 11
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
#ifdef notdef
#include "fd.h"
#if NFD > 0
		fdshutdown();
#endif
#endif
D 28
		sync(&proc0, (void *)NULL, (int *)NULL);
E 28
I 28
		sync(p, (void *)NULL, (int *)NULL);
E 28
I 27
		/*
		 * Unmount filesystems
		 */
		if (panicstr == 0)
			vfs_unmountall();
E 27

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
D 12
	if (howto & RB_HALT) {
D 4
#ifdef DEBUG
		void (*f)() = (void (*)())MACH_MON_RESTART;
#else
E 4
		void (*f)() = (void (*)())MACH_MON_REINIT;
E 12
I 12
	if (callv != &callvec) {
		if (howto & RB_HALT)
			(*callv->rex)('h');
		else {
			if (howto & RB_DUMP)
				dumpsys();
			(*callv->rex)('b');
		}
	} else if (howto & RB_HALT) {
		volatile void (*f)() = (volatile void (*)())DEC_PROM_REINIT;
E 12
D 4
#endif
E 4

I 2
D 4
		trapDump("boot"); /* XXX */
E 4
E 2
		(*f)();	/* jump back to prom monitor */
	} else {
D 12
		void (*f)() = (void (*)())MACH_MON_AUTOBOOT;
E 12
I 12
		volatile void (*f)() = (volatile void (*)())DEC_PROM_AUTOBOOT;
E 12

		if (howto & RB_DUMP)
			dumpsys();
		(*f)();	/* jump back to prom monitor and do 'auto' cmd */
D 12
		/*NOTREACHED*/
E 12
	}
	/*NOTREACHED*/
}

D 23
int	dumpmag = 0x8fca0101;	/* magic number for savecore */
E 23
I 23
int	dumpmag = (int)0x8fca0101;	/* magic number for savecore */
E 23
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
}

/*
 * Return the best possible estimate of the time in the timeval
 * to which tvp points.  Unfortunately, we can't read the hardware registers.
 * We guarantee that the time will be greater than the value obtained by a
 * previous call.
 */
I 28
void
E 28
microtime(tvp)
D 28
	register struct timeval *tvp;
E 28
I 28
	struct timeval *tvp;
E 28
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
	register volatile struct chiptime *c;
	int i;

	/* disable clock interrupts (until startrtclock()) */
D 12
	c = (volatile struct chiptime *)MACH_CLOCK_ADDR;
E 12
I 12
	c = Mach_clock_addr;
E 12
	c->regb = REGB_DATA_MODE | REGB_HOURS_FORMAT;
	i = c->regc;
	spl0();		/* safe to turn interrupts on now */
	return (i);
}
I 2

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
D 12
			break;
E 12
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

I 12
/*
 * Fill in the pmax addresses by hand.
 */
static struct pmax_address {
	char	*pmax_name;
	char	*pmax_addr;
	int	pmax_pri;
} pmax_addresses[] = {
	{ "pm",	(char *)MACH_PHYS_TO_CACHED(KN01_PHYS_FBUF_START),	3 },
	{ "dc",	(char *)MACH_PHYS_TO_UNCACHED(KN01_SYS_DZ),		2 },
	{ "le",	(char *)MACH_PHYS_TO_UNCACHED(KN01_SYS_LANCE),		1 },
	{ "sii",(char *)MACH_PHYS_TO_UNCACHED(KN01_SYS_SII),		0 },
	{ (char *)0, },
};

void
pmax_slot_hand_fill()
{
	register struct pmax_ctlr *cp;
	register struct driver *drp;
	register struct pmax_address *pmap;

	/*
	 * Find the device driver entry and fill in the address.
	 */
	for (cp = pmax_cinit; drp = cp->pmax_driver; cp++) {
		for (pmap = pmax_addresses; pmap->pmax_name; pmap++) {
			if (strcmp(drp->d_name, pmap->pmax_name))
				continue;
			if (cp->pmax_addr == (char *)QUES) {
				cp->pmax_addr = pmap->pmax_addr;
				cp->pmax_pri = pmap->pmax_pri;
				continue;
			}
		}
	}
}

E 12
#ifdef DS5000
/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS 
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
 */

D 10
#include "turbochannel.h"
E 10
I 10
D 12
#include <pmax/pmax/turbochannel.h>
E 12
E 10

/*
 * Driver map: associates a device driver to an option type.
 * Drivers name are (arbitrarily) defined in each driver and
 * used in the various config tables.
 */
struct drivers_map {
	char	module_name[TC_ROM_LLEN];	/* from ROM, literally! */
	char	*driver_name;			/* in bus_??_init[] tables */
} tc_drivers_map[] = {
D 12
	{ "KN02    ",	"dc"},		/* system board, serial I/O */
E 12
I 12
	{ "KN02    ",	"dc"},		/* (*) 3max system board (with DC) */
E 12
	{ "PMAD-AA ",	"le"},		/* Ether */
	{ "PMAZ-AA ",	"asc"},		/* SCSI */
I 12
	{ "PMAG-AA ",	"mfb"},		/* Mono Frame Buffer */
E 12
	{ "PMAG-BA ",	"cfb"},		/* Color Frame Buffer */
I 28
	{ "PMAGB-BA",	"sfb"},		/* Smart Frame Buffer */
E 28
	{ "PMAG-CA ",	"ga"},		/* 2D graphic board */
	{ "PMAG-DA ",	"gq"},		/* 3D graphic board (LM) */
	{ "PMAG-FA ",	"gq"},		/* 3D graphic board (HE) */
D 12

E 12
I 12
	{ "PMAG-DV ",	"xcfb"},	/* (*) maxine Color Frame Buffer */
	{ "Z8530   ",	"scc"},		/* (*) 3min/maxine serial lines */
	{ "ASIC    ",	"asic"},	/* (*) 3min/maxine DMA controller */
	{ "XINE-FDC",	"fdc"},		/* (*) maxine floppy controller */
	{ "DTOP    ",	"dtop"},	/* (*) maxine desktop bus */
	{ "AMD79c30",	"isdn"},	/* (*) maxine ISDN chip */
	{ "XINE-FRC",	"frc"},		/* (*) maxine free-running counter */
I 28
	{ "PMAF-AA ",   "fza"},		/* slow FDDI */
	{ "T3PKT   ",   "tt"},		/* DECWRL turbochannel T3 */
	{ "T1D4PKT ",   "ds"},		/* DECWRL turbochannel T1 */
	{ "FORE_ATM",   "fa"},		/* Fore t??-100 ATM */
	{ "LoFi    ",	"lofi"},	/* DEC audio board */
	{ "AV01A-AA",	"lofi"},	/* DEC audio board */
	{ "AV01B-AA",	"lofi"},	/* DEC audio board */
E 28
E 12
	{ "", 0}			/* list end */
};

I 12
/*
 * Identify an option on the TC.  Looks at the mandatory
 * info in the option's ROM and checks it.
 */
E 12
#ifdef DEBUG
int tc_verbose = 0;
#endif

I 12
static int
D 14
tc_identify_option( addr, slot, complain)
E 14
I 14
tc_identify_option(addr, slot, complain)
E 14
	tc_rommap_t	*addr;
	tc_option_t	*slot;
	int		complain;
{
	register int	i;
	unsigned char   width;
	char            firmwr[TC_ROM_LLEN+1], vendor[TC_ROM_LLEN+1],
			module[TC_ROM_LLEN+1], host_type[TC_ROM_SLEN+1];

	/*
	 * We do not really use the 'width' info, but take advantage
	 * of the restriction that the spec impose on the portion
	 * of the ROM that maps between +0x3e0 and +0x470, which
	 * is the only piece we need to look at.
	 */
	width = addr->rom_width.value;
	switch (width) {
	case 1:
	case 2:
	case 4:
		break;

	default:
#ifdef DEBUG
		if (tc_verbose && complain)
			printf("%s (x%x) at x%x\n", "Invalid ROM width",
			       width, addr);
#endif
		return (0);
	}

	if (addr->rom_stride.value != 4) {
#ifdef DEBUG
		if (tc_verbose && complain)
			printf("%s (x%x) at x%x\n", "Invalid ROM stride",
			       addr->rom_stride.value, addr);
#endif
		return (0);
	}

	if ((addr->test_data[0] != 0x55) ||
	    (addr->test_data[4] != 0x00) ||
	    (addr->test_data[8] != 0xaa) ||
	    (addr->test_data[12] != 0xff)) {
#ifdef DEBUG
		if (tc_verbose && complain)
			printf("%s x%x\n", "Test pattern failed, option at",
			       addr);
#endif
		return (0);
	}

	for (i = 0; i < TC_ROM_LLEN; i++) {
		firmwr[i] = addr->firmware_rev[i].value;
		vendor[i] = addr->vendor_name[i].value;
		module[i] = addr->module_name[i].value;
		if (i >= TC_ROM_SLEN)
			continue;
		host_type[i] = addr->host_firmware_type[i].value;
	}
	firmwr[TC_ROM_LLEN] = vendor[TC_ROM_LLEN] =
	module[TC_ROM_LLEN] = host_type[TC_ROM_SLEN] = '\0';

#ifdef DEBUG
	if (tc_verbose)
D 14
		printf("%s %s '%s' at x%x\n %s %s %s '%s'\n %s %d %s %d %s\n",
E 14
I 14
		printf("%s %s '%s' at 0x%x\n %s %s %s '%s'\n %s %d %s %d %s\n",
E 14
		"Found a", vendor, module, addr,
		"Firmware rev.", firmwr,
		"diagnostics for a", host_type,
		"ROM size is", addr->rom_size.value << 3,
		"Kbytes, uses", addr->slot_size.value, "TC slot(s)");
#endif

	bcopy(module, slot->module_name, TC_ROM_LLEN);
D 14
	bcopy(vendor,  slot->module_id, TC_ROM_LLEN);
E 14
I 14
	bcopy(vendor, slot->module_id, TC_ROM_LLEN);
E 14
	bcopy(firmwr, &slot->module_id[TC_ROM_LLEN], TC_ROM_LLEN);
	slot->slot_size = addr->slot_size.value;
	slot->rom_width = width;

	return (1);
}

E 12
/*
D 12
 * TURBOchannel autoconf procedure. Finds in one sweep what is
E 12
I 12
 * TURBOchannel autoconf procedure.  Finds in one sweep what is
E 12
 * hanging on the bus and fills in the tc_slot_info array.
 * This is only the first part of the autoconf scheme, at this
D 12
 * time we are basically only looking for a graphics board and
 * serial port to use as system console (all workstations).
 *
 * XXX Someday make number of slots dynamic too.
E 12
I 12
 * time we are basically only looking for a graphics board to
 * use as system console (all workstations).
E 12
 */

D 12
#define KN02_TC_NSLOTS	8

tc_option_t	tc_slot_info[KN02_TC_NSLOTS];

caddr_t	tc_slot_virt_addr[] = {
	(caddr_t)0xbe000000,	/* TURBOchannel, slot 0 */
	(caddr_t)0xbe400000,	/* TURBOchannel, slot 1 */
	(caddr_t)0xbe800000,	/* TURBOchannel, slot 2 */
	(caddr_t)0xbec00000,	/* TURBOchannel, slot 3 */
	(caddr_t)0xbf000000,	/* TURBOchannel, slot 4 */
	(caddr_t)0xbf400000,	/* TURBOchannel, slot 5 */
	(caddr_t)0xbf800000,	/* TURBOchannel, slot 6 */
/*	(caddr_t)0xbfc00000,	   TURBOchannel, slot 7 */
E 12
I 12
D 13
unsigned int	tc_slot_phys_base [TC_MAX_SLOTS] = {
	/* use 3max for default values */
	KN02_PHYS_TC_0_START, KN02_PHYS_TC_1_START,
	KN02_PHYS_TC_2_START, KN02_PHYS_TC_3_START,
	KN02_PHYS_TC_4_START, KN02_PHYS_TC_5_START,
	KN02_PHYS_TC_6_START, KN02_PHYS_TC_7_START
E 12
};
E 13
D 14

E 14
void
tc_find_all_options()
{
	register int i;
D 12
	caddr_t addr;
E 12
I 12
	u_long addr;
	int found;
E 12
	register tc_option_t *sl;
D 12
	register struct drivers_map *map;
E 12
I 12
	struct drivers_map *map;
E 12
	register struct pmax_ctlr *cp;
	register struct driver *drp;

	/*
D 12
	 * Look for all controllers on the bus.
E 12
I 12
	 * Take a look at the bus
E 12
	 */
D 12
	i = sizeof(tc_slot_virt_addr) / sizeof(tc_slot_virt_addr[0]) - 1;
	while (i >= 0) {
		addr = tc_slot_virt_addr[i];
		if (tc_probe_slot(addr, &tc_slot_info[i])) {
E 12
I 12
	bzero(tc_slot_info, sizeof(tc_slot_info));
	for (i = tc_max_slot; i >= tc_min_slot;) {
		addr = MACH_PHYS_TO_UNCACHED(tc_slot_phys_base[i]);
		found = tc_probe_slot(addr, &tc_slot_info[i]);

		if (found) {
E 12
			/*
			 * Found a slot, make a note of it 
			 */
			tc_slot_info[i].present = 1;
D 12
			tc_slot_info[i].module_address = addr;
E 12
I 12
			tc_slot_info[i].k1seg_address = addr;
E 12
		}

		i -= tc_slot_info[i].slot_size;
	}

	/*
D 12
	 * Now for each slot found, see if we have a device driver that
	 * handles it.
E 12
I 12
	 * Some slots (e.g. the system slot on 3max) might require
	 * hand-filling.  If so, do it now. 
E 12
	 */
D 12
	for (i = 0, sl = tc_slot_info; i < KN02_TC_NSLOTS; i++, sl++) {
E 12
I 12
	if (tc_slot_hand_fill)
		(*tc_slot_hand_fill) (tc_slot_info);

	/*
	 * Now for each alive slot see if we have a device driver that
	 * handles it.  This is done in "priority order", meaning that
	 * always present devices are at higher slot numbers on all
	 * current TC machines, and option slots are at lowest numbers.
	 */
	for (i = TC_MAX_LOGICAL_SLOTS - 1; i >= 0; i--) {
		sl = &tc_slot_info[i];
E 12
		if (!sl->present)
			continue;
D 12
		/*
		 * Look for mapping between the module name and
		 * the device driver name.
		 */
E 12
I 12
		found = FALSE;
E 12
		for (map = tc_drivers_map; map->driver_name; map++) {
			if (bcmp(sl->module_name, map->module_name, TC_ROM_LLEN))
				continue;
D 12
			goto fnd_map;
E 12
I 12
			sl->driver_name = map->driver_name;
			found = TRUE;
			break;
E 12
		}
I 11
D 12
#ifdef DEBUG
E 11
		if (tc_verbose)
			printf("Cannot associate a device driver to %s\n",
				sl->module_name);
I 11
#endif
E 11
		sl->present = 0;
		continue;
E 12
I 12
		if (!found) {
D 14
			printf("%s %s %s\n", "Cannot associate a device driver to",
			       sl->module_name, ". Will (try to) ignore it.");
E 14
I 14
			printf("%s %s %s\n",
				"Cannot associate a device driver to",
				sl->module_name, ". Will (try to) ignore it.");
E 14
			sl->present = 0;
			continue;
		}
E 12

		/*
		 * Find the device driver entry and fill in the address.
		 */
D 12
	fnd_map:
E 12
		for (cp = pmax_cinit; drp = cp->pmax_driver; cp++) {
			if (strcmp(drp->d_name, map->driver_name))
				continue;
I 18
			if (cp->pmax_alive)
				continue;
E 18
			if (cp->pmax_addr == (char *)QUES) {
D 12
				cp->pmax_addr = sl->module_address;
E 12
I 12
				cp->pmax_addr = (char *)sl->k1seg_address;
E 12
				cp->pmax_pri = i;
I 12
				/*
				 * Only enable interrupts if there is an
				 * interrupt handler for it. (e.g., PMAG-BA 
				 * can't disable the vertical retrace interrupt
				 * and we might want to ignore it).
				 */
				if (drp->d_intr)
					(*tc_enable_interrupt)(i, 1);
E 12
D 18
				continue;
E 18
I 18
				cp->pmax_alive = 1;
				break;
E 18
			}
D 12
			if (cp->pmax_addr != sl->module_address) {
E 12
I 12
			if (cp->pmax_addr != (char *)sl->k1seg_address) {
E 12
				cp->pmax_addr = (char *)QUES;
				printf("%s: device not at configued address (expected at %x, found at %x)\n",
					drp->d_name,
D 12
					cp->pmax_addr, sl->module_address);
E 12
I 12
					cp->pmax_addr, sl->k1seg_address);
E 12
			}
		}
	}
}

/*
 * Probe a slot in the TURBOchannel. Return TRUE if a valid option
 * is present, FALSE otherwise. A side-effect is to fill the slot
 * descriptor with the size of the option, whether it is
 * recognized or not.
 */
int
tc_probe_slot(addr, slot)
	caddr_t addr;
	tc_option_t *slot;
{
	int i;
	static unsigned tc_offset_rom[] = {
		TC_OFF_PROTO_ROM, TC_OFF_ROM
	};
#define TC_N_OFFSETS	sizeof(tc_offset_rom)/sizeof(unsigned)

	slot->slot_size = 1;

	for (i = 0; i < TC_N_OFFSETS; i++) {
		if (badaddr(addr + tc_offset_rom[i], 4))
			continue;
		/* complain only on last chance */
		if (tc_identify_option((tc_rommap_t *)(addr + tc_offset_rom[i]),
		    slot, i == (TC_N_OFFSETS-1)))
			return (1);
	}
	return (0);
#undef TC_N_OFFSETS
}

/*
D 12
 * Identify an option on the TURBOchannel.  Looks at the mandatory
 * info in the option's ROM and checks it.
E 12
I 12
 * Enable/Disable interrupts for a TURBOchannel slot.
E 12
 */
D 12
int
tc_identify_option(addr, slot, complain)
	tc_rommap_t *addr;
	tc_option_t *slot;
	int complain;
E 12
I 12
void
kn02_enable_intr(slotno, on)
	register int slotno;
	int on;
E 12
{
D 12
	register int i;
	unsigned char width;
	char firmwr[TC_ROM_LLEN+1];
	char vendor[TC_ROM_LLEN+1];
	char module[TC_ROM_LLEN+1];
	char host_type[TC_ROM_SLEN+1];
E 12
I 12
	register volatile int *p_csr =
		(volatile int *)MACH_PHYS_TO_UNCACHED(KN02_SYS_CSR);
	int csr;
	int s;
E 12

D 12
	/*
	 * We do not really use the 'width' info, but take advantage
	 * of the restriction that the spec impose on the portion
	 * of the ROM that maps between +0x3e0 and +0x470, which
	 * is the only piece we need to look at.
	 */
	width = addr->rom_width.value;
	switch (width) {
E 12
I 12
	slotno = 1 << (slotno + KN02_CSR_IOINTEN_SHIFT);
	s = Mach_spl0();
	csr = *p_csr & ~(KN02_CSR_WRESERVED | 0xFF);
	if (on)
		*p_csr = csr | slotno;
	else
		*p_csr = csr & ~slotno;
	splx(s);
}

/*
 *	Object:
 *		kmin_enable_intr		EXPORTED function
 *
 *	Enable/Disable interrupts from a TURBOchannel slot.
 *
 *	We pretend we actually have 8 slots even if we really have
 *	only 4: TCslots 0-2 maps to slots 0-2, TCslot3 maps to
 *	slots 3-7 (see kmin_slot_hand_fill).
 */
void
kmin_enable_intr(slotno, on)
	register unsigned int slotno;
	int on;
{
	register unsigned mask;

	switch (slotno) {
	case 0:
E 12
	case 1:
	case 2:
D 12
	case 4:
E 12
I 12
		return;
	case KMIN_SCSI_SLOT:
		mask = (KMIN_INTR_SCSI | KMIN_INTR_SCSI_PTR_LOAD |
			KMIN_INTR_SCSI_OVRUN | KMIN_INTR_SCSI_READ_E);
E 12
		break;
D 12

E 12
I 12
	case KMIN_LANCE_SLOT:
		mask = KMIN_INTR_LANCE;
		break;
	case KMIN_SCC0_SLOT:
		mask = KMIN_INTR_SCC_0;
		break;
	case KMIN_SCC1_SLOT:
		mask = KMIN_INTR_SCC_1;
		break;
	case KMIN_ASIC_SLOT:
		mask = KMIN_INTR_ASIC;
		break;
E 12
	default:
D 12
		if (complain)
			printf("Invalid ROM width (0x%x) at x%x\n",
			       width, addr);
		return (0);
E 12
I 12
		return;
E 12
	}
I 12
	if (on)
		kmin_tc3_imask |= mask;
	else
		kmin_tc3_imask &= ~mask;
}
E 12

D 12
	if (addr->rom_stride.value != 4) {
		if (complain)
			printf("Invalid ROM stride (0x%x) at x%x\n",
			       addr->rom_stride.value, addr);
		return (0);
	}
E 12
I 12
/*
 *	Object:
 *		xine_enable_intr		EXPORTED function
 *
 *	Enable/Disable interrupts from a TURBOchannel slot.
 *
 *	We pretend we actually have 11 slots even if we really have
 *	only 3: TCslots 0-1 maps to slots 0-1, TCslot 2 is used for
 *	the system (TCslot3), TCslot3 maps to slots 3-10
 *	(see xine_slot_hand_fill).
 *	Note that all these interrupts come in via the IMR.
 */
void
xine_enable_intr(slotno, on)
	register unsigned int slotno;
	int on;
{
	register unsigned mask;
E 12

D 12
	if (addr->test_data[0] != 0x55 ||
	    addr->test_data[4] != 0x00 ||
	    addr->test_data[8] != 0xaa ||
	    addr->test_data[12] != 0xff) {
		if (complain)
			printf("Test pattern failed, option at x%x\n",
			       addr);
		return (0);
E 12
I 12
	switch (slotno) {
	case 0:			/* a real slot, but  */
		mask = XINE_INTR_TC_0;
		break;
	case 1:			/* a real slot, but */
		mask = XINE_INTR_TC_1;
		break;
	case XINE_FLOPPY_SLOT:
		mask = XINE_INTR_FLOPPY;
		break;
	case XINE_SCSI_SLOT:
		mask = (XINE_INTR_SCSI | XINE_INTR_SCSI_PTR_LOAD |
			XINE_INTR_SCSI_OVRUN | XINE_INTR_SCSI_READ_E);
		break;
	case XINE_LANCE_SLOT:
		mask = XINE_INTR_LANCE;
		break;
	case XINE_SCC0_SLOT:
		mask = XINE_INTR_SCC_0;
		break;
	case XINE_DTOP_SLOT:
		mask = XINE_INTR_DTOP_RX;
		break;
	case XINE_ISDN_SLOT:
		mask = XINE_INTR_ISDN;
		break;
	case XINE_ASIC_SLOT:
		mask = XINE_INTR_ASIC;
		break;
	default:
		return;/* ignore */
E 12
	}
I 12
	if (on)
		xine_tc3_imask |= mask;
	else
		xine_tc3_imask &= ~mask;
}
E 12

I 13
#ifdef DS5000_240
E 13
D 12
	for (i = 0; i < TC_ROM_LLEN; i++) {
		firmwr[i] = addr->firmware_rev[i].value;
		vendor[i] = addr->vendor_name[i].value;
		module[i] = addr->module_name[i].value;
		if (i >= TC_ROM_SLEN)
			continue;
		host_type[i] = addr->host_firmware_type[i].value;
	}
E 12
I 12
/*
I 13
 * UNTESTED!!
E 13
 *	Object:
I 13
 *		kn03_enable_intr		EXPORTED function
 *
 *	Enable/Disable interrupts from a TURBOchannel slot.
 *
 *	We pretend we actually have 8 slots even if we really have
 *	only 4: TCslots 0-2 maps to slots 0-2, TCslot3 maps to
 *	slots 3-7 (see kn03_slot_hand_fill).
 */
void
kn03_enable_intr(slotno, on)
	register unsigned int slotno;
	int on;
{
	register unsigned mask;

	switch (slotno) {
	case 0:
I 18
		mask = KN03_INTR_TC_0;
		break;
E 18
	case 1:
I 18
		mask = KN03_INTR_TC_1;
		break;
E 18
	case 2:
D 18
		return;
E 18
I 18
		mask = KN03_INTR_TC_2;
		break;
E 18
	case KN03_SCSI_SLOT:
		mask = (KN03_INTR_SCSI | KN03_INTR_SCSI_PTR_LOAD |
			KN03_INTR_SCSI_OVRUN | KN03_INTR_SCSI_READ_E);
		break;
	case KN03_LANCE_SLOT:
		mask = KN03_INTR_LANCE;
		break;
	case KN03_SCC0_SLOT:
		mask = KN03_INTR_SCC_0;
		break;
	case KN03_SCC1_SLOT:
		mask = KN03_INTR_SCC_1;
		break;
	case KN03_ASIC_SLOT:
		mask = KN03_INTR_ASIC;
		break;
	default:
		return;
	}
	if (on)
		kn03_tc3_imask |= mask;
	else
		kn03_tc3_imask &= ~mask;
}
#endif /* DS5000_240 */

/*
 *	Object:
E 13
 *		kn02_slot_hand_fill		EXPORTED function
 *
 *	Fill in by hand the info for TC slots that are non-standard.
 *	This is basically just the system slot on a 3max, it does not
 *	look to me like it follows the TC rules although some of the
 *	required info is indeed there.
 *
 */
void
kn02_slot_hand_fill(slot)
	tc_option_t *slot;
{
	slot[7].present = 1;
	slot[7].slot_size = 1;
	slot[7].rom_width = 1;
#if unsafe
	bcopy(0xbffc0410, slot[7].module_name, TC_ROM_LLEN+1);
#endif
	bcopy("KN02    ", slot[7].module_name, TC_ROM_LLEN+1);
	bcopy("DEC xxxx", slot[7].module_id, TC_ROM_LLEN+1);
	slot[7].k1seg_address = MACH_PHYS_TO_UNCACHED(KN02_SYS_DZ);
}
E 12

I 11
D 12
#ifdef DEBUG
E 11
	if (tc_verbose) {
		firmwr[TC_ROM_LLEN] = '\0';
		vendor[TC_ROM_LLEN] = '\0';
		module[TC_ROM_LLEN] = '\0';
		host_type[TC_ROM_SLEN] = '\0';
		printf("%s %s '%s' at x%x\n %s %s %s '%s'\n %s %d %s %d %s\n",
		       "Found a", vendor, module, addr,
		       "Firmware rev.", firmwr,
		       "diagnostics for a", host_type,
		       "ROM size is", addr->rom_size.value << 3,
		       "Kbytes, uses", addr->slot_size.value, "TC slot(s)");
E 12
I 12
/*
 *	Object:
 *		kmin_slot_hand_fill		EXPORTED function
 *
 *	Fill in by hand the info for TC slots that are non-standard.
 *	This is the system slot on a 3min, which we think of as a
 *	set of non-regular size TC slots.
 *
 */
void
kmin_slot_hand_fill(slot)
	tc_option_t *slot;
{
	register int i;

	for (i = KMIN_SCSI_SLOT; i < KMIN_ASIC_SLOT+1; i++) {
		slot[i].present = 1;
		slot[i].slot_size = 1;
		slot[i].rom_width = 1;
		slot[i].unit = 0;
		bcopy("DEC KMIN", slot[i].module_id, TC_ROM_LLEN+1);
E 12
	}
I 11
D 12
#endif
E 12
E 11

D 12
	bcopy(module, slot->module_name, TC_ROM_LLEN);
	bcopy(vendor, slot->module_id, TC_ROM_LLEN);
	bcopy(firmwr, &slot->module_id[TC_ROM_LLEN], TC_ROM_LLEN);
	slot->slot_size = addr->slot_size.value;
	slot->rom_width = width;
E 12
I 12
	/* scsi */
	bcopy("PMAZ-AA ", slot[KMIN_SCSI_SLOT].module_name, TC_ROM_LLEN+1);
	slot[KMIN_SCSI_SLOT].k1seg_address =
		MACH_PHYS_TO_UNCACHED(KMIN_SYS_SCSI);
E 12

D 12
	return (1);
E 12
I 12
	/* lance */
	bcopy("PMAD-AA ", slot[KMIN_LANCE_SLOT].module_name, TC_ROM_LLEN+1);
	slot[KMIN_LANCE_SLOT].k1seg_address = 0;

	/* scc */
	bcopy("Z8530   ", slot[KMIN_SCC0_SLOT].module_name, TC_ROM_LLEN+1);
	slot[KMIN_SCC0_SLOT].k1seg_address =
		MACH_PHYS_TO_UNCACHED(KMIN_SYS_SCC_0);

	slot[KMIN_SCC1_SLOT].unit = 1;
	bcopy("Z8530   ", slot[KMIN_SCC1_SLOT].module_name, TC_ROM_LLEN+1);
	slot[KMIN_SCC1_SLOT].k1seg_address =
		MACH_PHYS_TO_UNCACHED(KMIN_SYS_SCC_1);

	/* asic */
	bcopy("ASIC    ", slot[KMIN_ASIC_SLOT].module_name, TC_ROM_LLEN+1);
	slot[KMIN_ASIC_SLOT].k1seg_address =
		MACH_PHYS_TO_UNCACHED(KMIN_SYS_ASIC);
D 13
	asic_init(TRUE);
E 13
I 13
	asic_init(0);
E 13
E 12
}

/*
D 12
 * Enable/Disable interrupts for a TURBOchannel slot.
E 12
I 12
 *	Object:
 *		xine_slot_hand_fill		EXPORTED function
 *
 *	Fill in by hand the info for TC slots that are non-standard.
 *	This is the system slot on a 3min, which we think of as a
 *	set of non-regular size TC slots.
 *
E 12
 */
D 12
tc_enable_interrupt(slotno, on)
	register int slotno;
	int on;
E 12
I 12
void
xine_slot_hand_fill(slot)
	tc_option_t *slot;
E 12
{
D 12
	register volatile int *p_csr = (volatile int *)MACH_SYS_CSR_ADDR;
	int csr;
	int s;
E 12
I 12
	register int i;
E 12

D 12
	slotno = 1 << (slotno + MACH_CSR_IOINTEN_SHIFT);
	s = Mach_spl0();
	csr = *p_csr & ~(MACH_CSR_MBZ | 0xFF);
	if (on)
		*p_csr = csr | slotno;
	else
		*p_csr = csr & ~slotno;
	splx(s);
E 12
I 12
	for (i = XINE_FLOPPY_SLOT; i < XINE_FRC_SLOT+1; i++) {
		slot[i].present = 1;
		slot[i].slot_size = 1;
		slot[i].rom_width = 1;
		slot[i].unit = 0;
		bcopy("DEC XINE", slot[i].module_id, TC_ROM_LLEN+1);
	}

	/* floppy */
	bcopy("XINE-FDC", slot[XINE_FLOPPY_SLOT].module_name, TC_ROM_LLEN+1);
	slot[XINE_FLOPPY_SLOT].k1seg_address =
		MACH_PHYS_TO_UNCACHED(XINE_SYS_FLOPPY);

	/* scsi */
	bcopy("PMAZ-AA ", slot[XINE_SCSI_SLOT].module_name, TC_ROM_LLEN+1);
	slot[XINE_SCSI_SLOT].k1seg_address =
		MACH_PHYS_TO_UNCACHED(XINE_SYS_SCSI);

	/* lance */
	bcopy("PMAD-AA ", slot[XINE_LANCE_SLOT].module_name, TC_ROM_LLEN+1);
	slot[XINE_LANCE_SLOT].k1seg_address =
		MACH_PHYS_TO_UNCACHED(XINE_SYS_LANCE);

	/* scc */
	bcopy("Z8530   ", slot[XINE_SCC0_SLOT].module_name, TC_ROM_LLEN+1);
	slot[XINE_SCC0_SLOT].k1seg_address =
		MACH_PHYS_TO_UNCACHED(XINE_SYS_SCC_0);

	/* Desktop */
	bcopy("DTOP    ", slot[XINE_DTOP_SLOT].module_name, TC_ROM_LLEN+1);
	slot[XINE_DTOP_SLOT].k1seg_address =
		MACH_PHYS_TO_UNCACHED(XINE_SYS_DTOP+0x20000); /* why? */

	/* ISDN */
	bcopy("AMD79c30", slot[XINE_ISDN_SLOT].module_name, TC_ROM_LLEN+1);
	slot[XINE_ISDN_SLOT].k1seg_address =
		MACH_PHYS_TO_UNCACHED(XINE_SYS_ISDN);

	/* Video */
	bcopy("PMAG-DV ", slot[XINE_CFB_SLOT].module_name, TC_ROM_LLEN+1);
	slot[XINE_CFB_SLOT].k1seg_address =
		MACH_PHYS_TO_CACHED(XINE_PHYS_CFB_START);

	/* asic */
	bcopy("ASIC    ", slot[XINE_ASIC_SLOT].module_name, TC_ROM_LLEN+1);
	slot[XINE_ASIC_SLOT].k1seg_address =
		MACH_PHYS_TO_UNCACHED(XINE_SYS_ASIC);

	/* free-running counter (high resolution mapped time) */
	bcopy("XINE-FRC", slot[XINE_FRC_SLOT].module_name, TC_ROM_LLEN+1);
	slot[XINE_FRC_SLOT].k1seg_address =
		MACH_PHYS_TO_UNCACHED(XINE_REG_FCTR);
D 13
	asic_init(FALSE);
E 13
I 13
	asic_init(1);
E 13
E 12
}

I 13
#ifdef DS5000_240
E 13
I 12
/*
D 13
 * Initialize the I/O asic
E 13
I 13
 * UNTESTED!!
 *	Object:
 *		kn03_slot_hand_fill		EXPORTED function
 *
 *	Fill in by hand the info for TC slots that are non-standard.
 *	This is the system slot on a 3max+, which we think of as a
 *	set of non-regular size TC slots.
 *
E 13
 */
D 13
static void
asic_init(isa_3min)
	int isa_3min;
E 13
I 13
void
kn03_slot_hand_fill(slot)
	tc_option_t *slot;
E 13
{
D 13
	volatile u_int *ssr, *decoder;
E 13
I 13
	register int i;
E 13

D 13
	/* These are common between 3min and maxine */
	decoder = (volatile u_int *)
		MACH_PHYS_TO_UNCACHED(KMIN_REG_LANCE_DECODE);
	*decoder = KMIN_LANCE_CONFIG;
#ifdef notdef
	decoder = (volatile u_int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_SCSI_DECODE);
	*decoder = KMIN_SCSI_CONFIG;
	decoder = (volatile u_int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_SCC0_DECODE);
	*decoder = KMIN_SCC0_CONFIG;
E 13
I 13
	for (i = KN03_SCSI_SLOT; i < KN03_ASIC_SLOT+1; i++) {
		slot[i].present = 1;
		slot[i].slot_size = 1;
		slot[i].rom_width = 1;
		slot[i].unit = 0;
		bcopy("DEC KN03", slot[i].module_id, TC_ROM_LLEN+1);
	}
E 13

D 13
	ssr = (volatile u_int *)MACH_PHYS_TO_UNCACHED(KMIN_REG_CSR);
E 13
I 13
	/* scsi */
	bcopy("PMAZ-AA ", slot[KN03_SCSI_SLOT].module_name, TC_ROM_LLEN+1);
	slot[KN03_SCSI_SLOT].k1seg_address =
		MACH_PHYS_TO_UNCACHED(KN03_SYS_SCSI);
E 13

D 13
	if (isa_3min) {
		decoder = (volatile u_int *)
			MACH_PHYS_TO_UNCACHED(KMIN_REG_SCC1_DECODE);
		*decoder = KMIN_SCC1_CONFIG;
E 13
I 13
	/* lance */
	bcopy("PMAD-AA ", slot[KN03_LANCE_SLOT].module_name, TC_ROM_LLEN+1);
	slot[KN03_LANCE_SLOT].k1seg_address = 0;
E 13

D 13
		/* take all chips out of reset now */
		*ssr = 0x00000f00;
E 13
I 13
	/* scc */
	bcopy("Z8530   ", slot[KN03_SCC0_SLOT].module_name, TC_ROM_LLEN+1);
	slot[KN03_SCC0_SLOT].k1seg_address =
		MACH_PHYS_TO_UNCACHED(KN03_SYS_SCC_0);
E 13

D 13
	} else {
		decoder = (volatile u_int *)
			MACH_PHYS_TO_UNCACHED(XINE_REG_DTOP_DECODE);
		*decoder = XINE_DTOP_CONFIG;
		decoder = (volatile u_int *)
			MACH_PHYS_TO_UNCACHED(XINE_REG_FLOPPY_DECODE);
		*decoder = XINE_FLOPPY_CONFIG;
E 13
I 13
	slot[KN03_SCC1_SLOT].unit = 1;
	bcopy("Z8530   ", slot[KN03_SCC1_SLOT].module_name, TC_ROM_LLEN+1);
	slot[KN03_SCC1_SLOT].k1seg_address =
		MACH_PHYS_TO_UNCACHED(KN03_SYS_SCC_1);
E 13

D 13
		/* take all chips out of reset now */
		*ssr = 0x00001fc1;
	}
#endif
E 13
I 13
	/* asic */
	bcopy("ASIC    ", slot[KN03_ASIC_SLOT].module_name, TC_ROM_LLEN+1);
	slot[KN03_ASIC_SLOT].k1seg_address =
		MACH_PHYS_TO_UNCACHED(KN03_SYS_ASIC);
	asic_init(0);
}
#endif /* DS5000_240 */

/*
 * Initialize the I/O asic
 */
static void
asic_init(isa_maxine)
	int isa_maxine;
{
	volatile u_int *decoder;

	/* These are common between 3min and maxine */
	decoder = (volatile u_int *)ASIC_REG_LANCE_DECODE(asic_base);
	*decoder = KMIN_LANCE_CONFIG;
E 13
}
E 12
#endif /* DS5000 */
E 2
E 1
