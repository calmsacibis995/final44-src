/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	si.c,v $
 * Revision 2.11  89/10/11  14:51:08  dlb
 * 	New vm_map_pageable calling sequence.
 * 	[89/10/07            dlb]
 * 
 * Revision 2.10  89/07/11  17:39:53  jjc
 * 	Changed to include machine dependent header files from machine/ not sun3/ because the Sun 4 uses this device driver too.
 * 	[89/07/06  16:55:30  jjc]
 * 
 * Revision 2.9  89/03/09  21:45:51  rpd
 * 	More cleanup.
 * 
 * Revision 2.8  89/02/25  19:54:59  gm0w
 * 	Added new copyright and fixed includes as part of kernel
 * 	cleanup.
 * 	[89/02/10            jjc]
 * 
 * Revision 2.7  89/01/27  10:22:27  rvb
 * 	Made VOLATILE (again ... sigh )
 * 	[88/03/01            rvb]
 * 
 * Revision 2.6  89/01/23  15:29:59  rvb
 * 	Forward declarations for GCC.
 * 	[89/01/22            rvb]
 * 
 * Revision 2.5  88/12/07  17:22:17  mikeg
 * 	Entered new version of this program from SunOS 3.5
 * 	into the Mach kernel source tree.
 * 	[88/12/01  14:38:31  mikeg]
 * 
 * 14-Aug-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Upgraded to SunOS 3.5 with some help from Jon Hale at Mt. Xinu.
 *	Conditionalized allocation of SCSI controller table under
 *	DVMA_KLUGE instead of CS_GENERIC.
 *
 * 19-Mar-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Dynamically allocated SCSI controller table, "sictlrs", to
 *	insure that it is always in the F segment to keep this 
 *	device driver happy even if the kernel is moved.
 *	[ V5.1(F8) ]
 *
 * 22-Jan-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Conditionalized include of "pte.h" on whether MACH_VM is
 *	not defined.
 *
 */
/* @(#)si.c       1.1 87/12/21 Copyr 1987 Sun Micro */
#include <si.h>
#if	NSI > 0

#ifndef	lint
static	char sccsid[] = "@(#)si.c       1.1 87/12/21 Copyr 1987 Sun Micro";
#endif	lint

/* #define SCSI_DEBUG			/* turn on debugging code */
/* #define REL4				/* enable release 4.00 mods */

/*
 * Generic scsi routines.
 */
#ifndef	REL4
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dk.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/map.h>
#include <sys/vmmac.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <sys/dkbad.h>

#ifdef	MACH
#include <vm/vm_kern.h>
#include <mach/vm_prot.h>
#include <mach/vm_param.h>
#else	MACH
#include <machine/pte.h>
#endif	MACH
#include <machine/psl.h>
#include <machine/mmu.h>
#include <machine/cpu.h>
#include <machine/scb.h>

#include <sun/dklabel.h>
#include <sun/dkio.h>

#include <sundev/mbvar.h>
#include <sundev/sireg.h>
#include <sundev/scsi.h>

#else	REL4
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dk.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/user.h>
#include <sys/map.h>
#include <sys/vmmac.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <sys/dkbad.h>

#ifdef	MACH
#include <vm/vm_kern.h>
#include <mach/vm_param.h>
#else	MACH
#include <machine/pte.h>
#endif	MACH
#include <machine/psl.h>
#include <machine/mmu.h>
#include <machine/cpu.h>
#include <machine/scb.h>

#include <sun/dklabel.h>
#include <sun/dkio.h>

#include <sundev/mbvar.h>
#include <sundev/sireg.h>
#include <sundev/scsi.h>
#endif	REL4

/* Shorthand, to make the code look a bit cleaner. */
#define SINUM(si)	(si - sictlrs)
#define SIUNIT(dev)     (minor(dev) & 0x03)

int	siprobe(), sislave(), siattach(), sigo(), sidone(), sipoll();
int	siustart(), sistart(), si_getstatus(), si_reconnect(), si_deque();
int	si_off(), si_cmd(), si_cmdwait(), si_reset(), si_dmacnt();

#if	DVMA_KLUGE
/*
 *	Allocate this table dynamically to make sure that it's in 
 *	the F segment
 */
struct	scsi_ctlr *sictlrs = 0;
#else	DVMA_KLUGE
struct	scsi_ctlr sictlrs[NSI];			/* per controller structs */
#endif	DVMA_KLUGE
struct	mb_ctlr *siinfo[NSI];
extern struct mb_device *sdinfo[];
struct	mb_driver sidriver = {
	siprobe, sislave, siattach, sigo, sidone, sipoll,
	sizeof (struct scsi_si_reg), "sd", sdinfo, "si", siinfo, MDR_BIODMA,
};

/* routines available to devices specific portion of scsi driver */
struct scsi_ctlr_subr sisubr = {
	siustart, sistart, sidone, si_cmd, si_getstatus, si_cmdwait,
	si_off, si_reset, si_dmacnt, sigo, si_deque,
};
#ifdef	__GNU__
static char *si_str_phase();
static int si_arb_sel();
static int si_vme_dma_setup();
static int si_ob_dma_setup();
static int si_sbc_dma_setup();
static int si_disconnect();
static int si_status_bytes();
static int si_sbc_wait();
static int si_wait();
static int si_wait_phase();
static int si_putdata();
static int si_putcmd();
static int si_getdata();
#else	__GNU__
char *si_str_phase();
#endif	__GNU__

extern int scsi_ntype;
extern short scsi_disre_enable;		/* enable disconnect/reconnects */
extern struct scsi_unit_subr scsi_unit_subr[];

/*
 * Software copy of ser state (debug only)
 */
static u_char junk;

/*
 * Patchable delays for debugging.
 */
int si_udc_wait = SI_UDC_WAIT;
int si_arbitration_delay = SI_ARBITRATION_DELAY;
int si_bus_clear_delay = SI_BUS_CLEAR_DELAY;
int si_bus_settle_delay = SI_BUS_SETTLE_DELAY;

/*
 * possible return values from si_arb_sel, si_cmd, 
 * si_putdata, si_putcmd, and si_reconnect.
 */
#define OK		0	/* successful */ 
#define FAIL		1	/* failed maybe recoverable */ 
#define HARD_FAIL	2	/* failed not recoverable */ 
#define SCSI_FAIL	3	/* failed due to scsi bus fault */ 
#define RESEL_FAIL	4	/* failed due to target reselection */ 

/* possible return values from si_process_complete_msg() */
#define CMD_CMPLT_DONE	0	/* cmd processing done */ 
#define CMD_CMPLT_WAIT	1	/* cmd processing waiting
				 * on sense cmd complete
				 */
/*
 * possible argument values for si_reset
 */
#define NO_MSG		0	/* don't print reset warning message */ 
#define PRINT_MSG	1	/* print reset warning message */ 

/* 
 * scsi CDB op code to command length decode table.
 */
static u_char cdb_size[] = {
	CDB_GROUP0,		/* Group 0, 6 byte cdb */
	CDB_GROUP1,		/* Group 1, 10 byte cdb */
	CDB_GROUP2,		/* Group 2, ? byte cdb */
	CDB_GROUP3,		/* Group 3, ? byte cdb */
	CDB_GROUP4,		/* Group 4, ? byte cdb */
	CDB_GROUP5,		/* Group 5, ? byte cdb */
	CDB_GROUP6,		/* Group 6, ? byte cdb */
	CDB_GROUP7		/* Group 7, ? byte cdb */
};



#ifdef	SCSI_DEBUG
extern short scsi_debug;	/* 0 = normal operaion
				 * 1 = enable error logging and error msgs.
				 * 2 = as above + debug msgs.
				 * 3 = enable all info msgs.
				 */
int scsi_dis_debug   = 0;	/* disconnect debug info */
u_int si_winner  = 0;		/* # of times we had an intr at end of siintr */
u_int si_loser   = 0;		/* # of times we didn't have an intr at end */

#define SI_WIN		si_winner++
#define SI_LOSE		si_loser++

/* Check for possible illegal SCSI-3 register access. */
#define SI_VME_OK(c, sir, str)	{\
	if ((IS_VME(c))  &&  (sir->csr & SI_CSR_DMA_EN)) \
		printf("si%d:  reg access during dma <%s>, csr 0x%x\n", \
			SINUM(c), str, sir);\
}
#define SI_DMA_OK(c, sir, str)  {\
	if (IS_VME(c)) { \
		if (sir->csr & SI_CSR_DMA_EN) \
			printf("%s: DMA DISABLED\n", str); \
		if (sir->csr & SI_CSR_DMA_CONFLICT) { \
			printf("%s: invalid reg access during dma\n", str); \
			DELAY(50000000); \
		} \
		sir->csr &= ~SI_CSR_DMA_EN; \
	} \
}
#define SCSI_TRACE(where, sir, un) \
	if (scsi_debug)		scsi_trace(where, sir, un)
#define SCSI_RECON_TRACE(where, c, data0, data1, data2) \
	if (scsi_debug)		scsi_recon_trace(where, c, data0, data1, data2)
#define DEBUG_DELAY(cnt) \
	if (scsi_debug)  DELAY(cnt)

/* Handy debugging 0, 1, and 2 argument printfs */
#define DPRINTF(str) \
	if (scsi_debug > 1) printf(str)
#define DPRINTF1(str, arg1) \
	if (scsi_debug > 1) printf(str,arg1)
#define DPRINTF2(str, arg1, arg2) \
	if (scsi_debug > 1) printf(str,arg1,arg2)

/* Handy error reporting 0, 1, and 2 argument printfs */
#define EPRINTF(str) \
	if (scsi_debug) printf(str)
#define EPRINTF1(str, arg1) \
	if (scsi_debug) printf(str,arg1)
#define EPRINTF2(str, arg1, arg2) \
	if (scsi_debug) printf(str,arg1,arg2)

#else	SCSI_DEBUG
#define SI_WIN
#define SI_LOSE
#define SI_VME_OK(c, sir, str)
#define SI_DMA_OK(c, sir, str)
#define DEBUG_DELAY(cnt)
#define DPRINTF(str) 
#define DPRINTF1(str, arg2) 
#define DPRINTF2(str, arg1, arg2) 
#define EPRINTF(str) 
#define EPRINTF1(str, arg2) 
#define EPRINTF2(str, arg1, arg2) 
#define SCSI_TRACE(where, sir, un)
#define SCSI_RECON_TRACE(where, c, data0, data1, data2)
#endif	SCSI_DEBUG

#define CLEAR_INTERRUPT(msg) \
	if (SBC_RD.bsr & SBC_BSR_INTR) { \
		EPRINTF1("%s: int cleared\n", msg); \
		junk = SBC_RD.clr; \
	} else { \
		EPRINTF1("%s: no int\n", msg); \
	}





/*
 * trace buffer stuff.
 */
#ifdef	SCSI_DEBUG
#define TRBUF_LEN	64
struct trace_buf {
	u_char wh[2];		/* where in code */
	u_char r[6];		/* 5380 registers */
	u_short csr;
	u_short bcr;
	u_int dma_addr;
	u_int dma_count;
};

struct disre_trace_buf {
	u_char wh[2];
	struct scsi_cdb cdb;
	u_short target;
	u_short lun;
	u_int data[3];
	u_int dma_count;
};

/* trace buffer */
int si_stbi = 0;
struct trace_buf si_trace_buf[TRBUF_LEN];

/* disconnect/reconnect trace buffer */
int si_strbi = 0;
struct disre_trace_buf si_recon_trace_buf[TRBUF_LEN];

static
scsi_trace(where, sir, un)
	register char where;
	register volatile struct scsi_si_reg *sir;
	struct scsi_unit *un;
{
	register volatile u_char *r = &(SBC_RD.cdr);
	register u_int i;
	register struct trace_buf *tb = &(si_trace_buf[si_stbi]);
#ifdef	lint
	un= un;
#endif	lint

	tb->wh[0] = tb->wh[1] = where;
	for (i = 0; i < 6; i++)
		tb->r[i] = *r++;
	tb->csr = sir->csr;
	tb->bcr = sir->bcr;
	tb->dma_addr  = GET_DMA_ADDR(sir);
	tb->dma_count = GET_DMA_COUNT(sir);

	if (++si_stbi >= TRBUF_LEN)
		si_stbi = 0;

	si_trace_buf[si_stbi].wh[0] = '?';		/* mark end */
}


static
scsi_recon_trace(where, c, data0, data1, data2)
	char where;
	register struct scsi_ctlr *c;
	register int data0, data1, data2;
{
	register struct scsi_unit *un = c->c_un;
	register struct disre_trace_buf *tb = 
		&(si_recon_trace_buf[si_strbi]);

	tb->wh[0] = tb->wh[1] = where;
	tb->cdb = c->c_cdb;
	tb->target = un->un_target;
	tb->lun = un->un_lun;
	tb->data[0] = data0;
	tb->data[1] = data1;
	tb->data[2] = data2;

	if (++si_strbi >= TRBUF_LEN)
		si_strbi = 0;

	si_recon_trace_buf[si_strbi].wh[0] = '?';	/* mark end */
}
#endif	SCSI_DEBUG


/*
 * Print out the cdb.
 */
static
si_print_cdb(c)
	register struct scsi_ctlr *c;
{
	register u_char size;
	register u_char *cp;
	register u_char i;

	cp = (u_char *) &c->c_cdb;
	if ((size = cdb_size[CDB_GROUPID(*cp)]) == 0  &&
	    (size = c->c_un->un_cmd_len) == 0) {

		/* If all else fails, use structure size */
		size = sizeof (struct scsi_cdb);
	}

	for (i = 0; i < size; i++)
		printf("  %x", *cp++);
	printf("\n");
}


/*
 * returns string corresponding to the last phase.
 * Note, also encoded are internal messages in
 * addition to the last bus phase.  
 */
static char *
si_str_lastphase(phase)
	register u_char phase;
{
	static char *invalid_phase = "";
	static char *phase_strings[] = {
		"Spurious",		/* 0x80 */
		"Arbitration",		/* 0x81 */
		"Identify MSG",		/* 0x82 */
		"Save ptr MSG",		/* 0x83 */
		"Restore ptr MSG",	/* 0x84 */
		"Disconnect MSG",	/* 0x85 */
		"Cmd complete MSG",	/* 0x86 */
	};

	if (phase >= 0x80) {
		if (phase > 0x86)
			return(invalid_phase);
		return(phase_strings[phase - 0x80]);
	} else {
		return(si_str_phase(phase));
	}
}


/*
 * returns string corresponding to the phase
 */
static char *
si_str_phase(phase)
	register u_char phase;
{
	register int index = (phase & CBSR_PHASE_BITS) >> 2;
	static char *phase_strings[] = {
		"DATA_OUT/FREE",
		"DATA_IN",
		"COMMAND",
		"STATUS",
		"",
		"",
		"MSG_OUT",
		"MSG_IN"
	};

	return(phase_strings[index]);
}


/*
 * print out the current hardware state
 */
static
si_print_state(sir, c)
	register volatile struct scsi_si_reg *sir;
	register struct scsi_ctlr *c;
{
	register struct scsi_unit *un = c->c_un;
	register short flag = 0;

	if (IS_VME(c)  &&  (sir->csr & SI_CSR_DMA_EN)) {
		sir->csr &= ~SI_CSR_DMA_EN;
		flag = 1;
	}
	printf("\tlast phase= 0x%x (%s)\n",
		c->c_last_phase, si_str_lastphase(c->c_last_phase));
	printf("\tcsr= 0x%x  bcr= %d  tcr= 0x%x\n",
			sir->csr, sir->bcr, SBC_RD.tcr);
	printf("\tcbsr= 0x%x (%s)  cdr= 0x%x  mr= 0x%x  bsr= 0x%x\n",
			SBC_RD.cbsr, si_str_phase(SBC_RD.cbsr), SBC_RD.cdr,
			SBC_RD.mr, SBC_RD.bsr);
	if (flag) {
		sir->csr |= SI_CSR_DMA_EN;
	}
#ifdef	SCSI_DEBUG
	printf("\tdriver wins= %d  loses= %d\n", si_winner, si_loser);
#endif	SCSI_DEBUG

	if (un != NULL) {
		printf("\ttarget= %d, lun= %d    ", un->un_target, un->un_lun);
		printf("DMA addr= 0x%x  count= %d (%d)\n",
			   un->un_dma_curaddr, un->un_dma_curcnt,
			   un->un_dma_count);
		printf("\tcdb=  ");
		si_print_cdb(c);
	}
}



/*
 * Determine existence of SCSI host adapter.
 * Returns 0 for failure, size of si data structure if ok.
 */
siprobe(sir, ctlr)
	register volatile struct scsi_si_reg *sir;
	register int ctlr;
{
	register struct scsi_ctlr *c;
#if	DVMA_KLUGE
	if (sictlrs == 0)
	{
		caddr_t	va;
		kern_return_t	retval;
		vm_size_t	size;

		va = (caddr_t) 0x0F000000;
		size = round_page(NSI * sizeof(struct scsi_ctlr));
		retval = vm_map_find(kernel_map, VM_OBJECT_NULL, 0, &va,
				size, TRUE);
		if (retval == KERN_SUCCESS)
			(void)vm_map_pageable(kernel_map, va, va + size,
						VM_PROT_READ|VM_PROT_WRITE);
		else
			panic("Could not allocate SCSI controller table");
		sictlrs = (struct scsi_ctlr *)va;
	}
#endif	DVMA_KLUGE
	c = &sictlrs[ctlr];

	/* 
	 * Check for sbc - NCR 5380 Scsi Bus Ctlr chip.
	 * sbc is common to sun3/50 onboard scsi and vme
	 * scsi board.
	 */
	if (peekc((char *)&sir->sbc_rreg.cbsr) == -1) {
		return (0);
	}

	/*
	 * Determine whether the host adaptor interface is onboard or vme.
	 */
#ifdef	sun3
	if ((cpu == CPU_SUN3_50)  ||  (cpu == CPU_SUN3_60)) {
		/* probe for sun3/50 dma interface */
		if (peek((short *)&sir->udc_rdata) == -1)
{
			return (0);
}

		c->c_flags = SCSI_ONBOARD;
	} else {
		/*
		 * Probe for vme scsi card but make sure it is not
		 * the SC host adaptor interface. SI vme scsi host
		 * adaptor occupies 2K bytes in the vme address space. 
		 * SC vme scsi host adaptor occupies 4K bytes in the 
		 * vme address space. So, peek past 2K bytes to 
		 * determine which host adaptor is there.
		 */
		if ((peek((short *)&sir->dma_addr) == -1)  ||
		    (peek((short *)((int)sir + 0x800)) != -1))
			return (0);

		/* Check for obsolete SCSI-3 boards */
		if (!(sir->csr & SI_CSR_ID)) {
			printf("si%d:  UNMODIFIED SCSI-3 BOARD!  PLEASE UPGRADE!\n",
				SINUM(c));
			return (0);
		}
		c->c_flags = SCSI_VME;
	}
#endif	sun3
#ifdef	sun4
	if (cpu == CPU_SUN4_110) {
		/* probe for sun 4/110 dma interface */
		if (peek((short *)&sir->udc_rdata) == -1)
			return (0);
		c->c_flags = SCSI_ONBOARD;
	} else {
		/*
		 * Probe for vme scsi card but make sure it is not
		 * the SC host adaptor interface. SI vme scsi host
		 * adaptor occupies 2K bytes in the vme address space. 
		 * SC vme scsi host adaptor occupies 4K bytes in the 
		 * vme address space. So, peek past 2K bytes to 
		 * determine which host adaptor is there.
		 */
		if ((peek((short *)&sir->dma_addrl) == -1)  ||
		    (peek((short *)((int)sir + 0x800)) != -1))
			return (0);

		/* Check for obsolete SCSI-3 boards */
		if (!(sir->csr & SI_CSR_ID)) {
			printf("si%d:  UNMODIFIED SCSI-3 BOARD!  PLEASE UPGRADE!\n",
				SINUM(c));
			return (0);
		}
		c->c_flags = SCSI_VME;
	}
#endif	sun4

	/* probe for different scsi host adaptor interfaces */
	EPRINTF2("si%d:  siprobe: sir= 0x%x,  ", ctlr, (u_int)sir);
	EPRINTF1("c= 0x%x\n", (u_int)c );

	/* init controller information */
	if (scsi_disre_enable) {
		/* DPRINTF("siprobe:  disconnects enabled\n"); */
		c->c_flags |= SCSI_EN_DISCON;
	} else {
		EPRINTF("siprobe:  all disconnects disabled\n");
	}

	c->c_flags |= SCSI_PRESENT;
	c->c_last_phase = PHASE_CMD_CPLT;
	c->c_reg = (int)sir;
	c->c_ss = &sisubr;
	si_reset(c, NO_MSG);			/* quietly reset the scsi bus */
	return (sizeof (volatile struct scsi_si_reg));
}


/*
 * See if a slave exists.
 * Since it may exist but be powered off, we always say yes.
 */
/*ARGSUSED*/
sislave(md, reg)
	register struct mb_device *md;
	register volatile struct scsi_si_reg *reg;
{
	register struct scsi_unit *un;
	register int type;

#ifdef	lint
	reg = reg;
	junk = junk;
#endif	lint

	/*
	 * This kludge allows autoconfig to print out "sd" for
	 * disks and "st" for tapes.  The problem is that there
	 * is only one md_driver for scsi devices.
	 */
	type = TYPE(md->md_flags);
	if (type >= scsi_ntype) {
		panic("sislave:  unknown type in md_flags\n");
	}

	/* link unit to its controller */
	un = (struct scsi_unit *)(*scsi_unit_subr[type].ss_unit_ptr)(md);
	if (un == 0) {
		panic("sislave:  md_flags scsi type not configured\n");
	}
	un->un_c = &sictlrs[md->md_ctlr];
	md->md_driver->mdr_dname = scsi_unit_subr[type].ss_devname;
	return (1);
}


/*
 * Attach device (boot time).
 */
siattach(md)
	register struct mb_device *md;
{
	register int type = TYPE(md->md_flags);
	register struct mb_ctlr *mc = md->md_mc;
	register struct scsi_ctlr *c = &sictlrs[md->md_ctlr];
	register volatile struct scsi_si_reg *sir;

	(int)sir = c->c_reg;

	/* DPRINTF("siattach:\n"); */
#ifdef	SCSI_DEBUG
	if ((scsi_disre_enable != 0)  &&  scsi_debug)
		printf("si%d:  siattach: disconnects disabled\n", SINUM(c));
#endif	SCSI_DEBUG

	if (type >= scsi_ntype) {
		panic("siattach:  unknown type in md_flags\n");
	}
	(*scsi_unit_subr[type].ss_attach)(md);

	if (IS_ONBOARD(c))
		return;

	/* 
	 * it's a vme...
	 * Make sure dma enable bit is off or 
	 * SI_CSR_DMA_CONFLICT will occur when 
	 * the iv_am register is accessed.
	 */
	sir->csr &= ~SI_CSR_DMA_EN;

	/* 
	 * Initialize interrupt vector and address modifier register.
	 * Address modifier specifies standard supervisor data access
	 * with 24 bit vme addresses. May want to change this in the
	 * future to handle 32 bit vme addresses.
	 */
	if (mc->mc_intr) {
		/* setup for vectored interrupts - we will pass ctlr ptr */
		sir->iv_am = (mc->mc_intr->v_vec & 0xff) | 
		    VME_SUPV_DATA_24;
		(*mc->mc_intr->v_vptr) = (int)c;
	}
}


/*
 * SCSI unit start routine.
 * Called by SCSI device drivers.
 * Does not actually start any I/O - just puts the device
 * on the ready queue for the bus.
 */
siustart(un)
	register struct scsi_unit *un;			/* our unit */
{
	register struct buf *dp;
	register struct mb_ctlr *mc;			/* unit's ctlr */

	DPRINTF("siustart:\n");
	mc = un->un_mc;
	dp = &un->un_utab;

	/* 
	 * Caller guarantees: dp->b_actf != NULL  &&  dp->b_active == 0 
	 * Note: dp->b_active == 1 on a reconnect.
	 *
	 * Put device on ready queue for bus.
	 */
	if (mc->mc_tab.b_actf == NULL) {
		mc->mc_tab.b_actf = dp;
	} else {
		mc->mc_tab.b_actl->b_forw = dp;
	}

	dp->b_forw = NULL;
	mc->mc_tab.b_actl = dp;
	dp->b_active = 1;
	dp->b_un.b_addr = (caddr_t) un;
}


/*
 * Set up a scsi operation.
 */
sistart(un)
	register struct scsi_unit *un;		/* our unit */
{

	register struct mb_ctlr *mc;		/* unit's ctlr */
	register struct buf *bp, *dp;

	DPRINTF("sistart:\n");
	mc = un->un_mc;
	dp = mc->mc_tab.b_actf;		  	/* != NULL guaranteed by caller */
	un = (struct scsi_unit *) dp->b_un.b_addr;
	bp = dp->b_actf;
	for (;;) {
		if (bp == NULL) {		/* no more blocks for this device */
			un->un_utab.b_active = 0;
			dp = mc->mc_tab.b_actf = dp->b_forw;
			if (dp == NULL) {	/* no more devices for this ctlr */
				si_idle(un->un_c);
				return;		/* done - out we go! */
			}
			un = (struct scsi_unit *) dp->b_un.b_addr;
			bp = dp->b_actf;
		} else {
			/*
			 * We have something to do - call unit start routine.
			 */
			if ((*un->un_ss->ss_start)(bp, un)) {
				mc->mc_tab.b_active = 1;
				un->un_c->c_un = un;
				if (bp == &un->un_sbuf  &&
				    ((un->un_flags & SC_UNF_DVMA) == 0)) {
					/*
					 * special command, 
					 * doesn't need DVMA.
					 */
					sigo(mc);
				} else {
					/* do DVMA setup first */
					(void) mbgo(mc);
				}
				return;		/* done - out we go! */
			}
			dp->b_actf = bp = bp->av_forw;
		}
	}
}


/*
 * Start up a scsi operation.
 * Called via mbgo after buffer is in memory.
 */
sigo(mc)
	register struct mb_ctlr *mc;		/* fire up this mb ctlr */
{
	register struct scsi_unit *un;		/* our scsi unit */
	register struct scsi_ctlr *c;		/* our scsi ctlr */
	register struct buf *bp, *dp;
	register int unit;			/* unit for stat purposes */
	register int err;

	DPRINTF("sigo:\n");
	c = &sictlrs[mc->mc_ctlr];
	dp = mc->mc_tab.b_actf;

	if (dp == NULL  ||  dp->b_actf == NULL) {
		panic("sigo:  queueing error1\n");
	}

	bp = dp->b_actf;
	un = c->c_un;

	if (dp != &un->un_utab) {
		panic("sigo:  queueing error2\n");
	}

	un->un_baddr = MBI_ADDR(mc->mc_mbinfo);

	/*
	 * Diddle stats if necessary.
	 */
	if ((unit = un->un_md->md_dk) >= 0) {
		dk_busy |= 1<<unit;
		dk_xfer[unit]++;
		dk_wds[unit] += bp->b_bcount >> 6;
	}

	/*
	 * Make the command block and fire it up in interrupt mode.
	 * If it fails right off the bat, call the interrupt routine 
	 * to handle the failure.
	 */
	(*un->un_ss->ss_mkcdb)(c, un);
	if ((err=si_cmd(c, un, 1)) != OK) {
		if (err == FAIL) {
			/* DPRINTF("sigo:  si_cmd FAILED\n"); */
			(*un->un_ss->ss_intr)(c, 0, SE_RETRYABLE);

		} else if (err == HARD_FAIL) {
			EPRINTF("sigo:  si_cmd hard FAIL\n");
			(*un->un_ss->ss_intr)(c, 0, SE_FATAL);
			si_off(c, un);
		}
	}
}


/*
 * Handle a polling SCSI bus interrupt.
 */
sipoll()
{
	register struct scsi_ctlr *c;
	register volatile struct scsi_si_reg *sir;
	register int serviced = 0;

	DPRINTF("sipoll:\n");
	for (c = sictlrs; c < &sictlrs[NSI]; c++) {
		if ((c->c_flags & SCSI_PRESENT) == 0)
			continue;
		(int)sir = c->c_reg;
		if ((sir->csr & 
		   (SI_CSR_SBC_IP | SI_CSR_DMA_IP | SI_CSR_DMA_CONFLICT)) == 0) 
		{
			continue;
		}
		serviced = 1;
		siintr(c);
	}
	return (serviced);
}


/*
 * Clean up queues, free resources, and start next I/O
 * all done after I/O finishes
 * Called by mbdone after moving read data from Mainbus
 */
sidone(mc)
	register struct mb_ctlr *mc;
{
	register struct buf *bp, *dp;
	register struct scsi_unit *un;
	register struct scsi_ctlr *c;
	register int err;

	DPRINTF("sidone:\n");
	bp = mc->mc_tab.b_actf->b_actf;
	c = &sictlrs[mc->mc_ctlr];
	un = c->c_un;

	/* advance controller queue */
	dp = mc->mc_tab.b_actf;
	mc->mc_tab.b_active = 0;
	mc->mc_tab.b_actf = dp->b_forw;

	/* advance unit queue */
	dp->b_active = 0;
	dp->b_actf = bp->av_forw;

	iodone(bp);

	/* start next I/O on unit */
	if (dp->b_actf)
		siustart(un);

	/* start next I/O on controller */
	if (mc->mc_tab.b_actf  &&  mc->mc_tab.b_active == 0) {
		dp = mc->mc_tab.b_actf;
		un = (struct scsi_unit *)dp->b_un.b_addr;
		/* 
		 * If this activity was preempted due to a 
		 * reselection coming in, much of the setup has 
		 * already taken place and must not be redone.
		 */
		if (un->un_flags & SC_UNF_PREEMPT) {
			DPRINTF1("sidone: doing preempted, tgt= %x\n",
				un->un_target);
			un->un_flags &= ~SC_UNF_PREEMPT;
			c->c_un = un;
			c->c_cdb = un->un_saved_cmd.saved_cdb;
			mc->mc_tab.b_active = 1;
			if (un->un_dma_curdir != SI_NO_DATA) {
				mc->mc_mbinfo = un->un_baddr;
			}
			if ((err=si_cmd(c, un, 1)) != OK) {
				if (err == FAIL) {
					DPRINTF("sidone:  si_cmd FAILED\n");
					(*un->un_ss->ss_intr)(c, 0, SE_RETRYABLE);

				} else if (err == HARD_FAIL) {
					EPRINTF("sidone:  si_cmd hard FAIL\n");
					(*un->un_ss->ss_intr)(c, 0, SE_FATAL);
					si_off(c, un);
				}
			}
		} else if (un->un_flags & SC_UNF_GET_SENSE) {
			sigo(mc);
		} else {
			sistart(un);
		}
	} else {
		c->c_un = NULL;
		si_idle(c);
	}
}


/*
 * Bring a unit offline.
 */
/*ARGSUSED*/
si_off(c, un)
	register struct scsi_ctlr *c;
	register struct scsi_unit *un;
{
	register struct mb_device *md;
	md = un->un_md;

	/*
	 * Be warned, if you take the root device offline,
	 * the system is going to have a heartattack !
	 */
	printf("si%d:  %s%d, unit offline\n", SINUM(c),
		scsi_unit_subr[md->md_flags].ss_devname, SIUNIT(un->un_unit));
	un->un_present = 0;

#ifdef	notdef
	/*
	 * This really doesn't work.  It would be a nice idea to
	 * fix it sometime.
	 */
	if (md->md_dk > 0) {
		dk_mspw[md->md_dk]=0;
	}
#endif	notdef
}


/*
 * Pass a command to the SCSI bus.
 * OK if fully successful, 
 * Return FAIL on failure (may be retryable),
 * SCSI_FAIL if we failed due to timing problem with SCSI bus. (terminal)
 * RESEL_FAIL if we failed due to target being in process of reselecting us.
 * (posponed til after reconnect done)
 */
si_cmd(c, un, intr)
	register struct scsi_ctlr *c;
	register struct scsi_unit *un;
	register int intr;		/* if 0, run cmd to completion
					 *       in polled mode
					 * if 1, allow disconnects
					 *       if enabled and use
					 *       interrupts
					 */
{
	register volatile struct scsi_si_reg *sir;
	register int err;
	register int i;
	register u_char size;
	u_char id;
	u_char msg;
	int s;

	DPRINTF("si_cmd:\n");
	(int)sir = c->c_reg;

	/* disallow disconnects if waiting for command completion */
	if (intr == 0) {
		c->c_flags &= ~SCSI_EN_DISCON;
	} else {
		/*
		 * If disconnect/reconnect globally disabled or only
		 * disabled for this command set internal flag.
		 * Otherwise, we enable disconnects and reconnects.
		 */
		if ((scsi_disre_enable == 0)  ||  (un->un_flags & SC_UNF_NO_DISCON))
			c->c_flags &= ~SCSI_EN_DISCON;
		else
			c->c_flags |= SCSI_EN_DISCON;
		un->un_wantint = 1;
	}

	/* Check for odd-byte boundary buffer */
	if ((un->un_flags & SC_UNF_DVMA)  &&  (un->un_dma_addr & 0x1)) {
		printf("si%d:  illegal odd byte DMA, address= 0x%x\n",
			SINUM(c), un->un_dma_curaddr);
		return(HARD_FAIL);
	}

	/*
	 * For vme host adaptor interface, dma enable bit may
	 * be set to allow reconnect interrupts to come in.
	 * This must be disabled before arbitration/selection
	 * of target is done. Don't worry about re-enabling
	 * dma. If arb/sel fails, then si_idle will re-enable.
	 * If arb/sel succeeds then handling of command will
	 * re-enable.
	 *
	 * Also, disallow sbc to accept reconnect attempts.
	 * Again, si_idle will re-enable this if arb/sel fails.
	 * If arb/sel succeeds then we do not want to allow
	 * reconnects anyway.
	 */
	s = spl4();	/* time critical */
	if (IS_VME(c))
		sir->csr &= ~SI_CSR_DMA_EN;

	SI_VME_OK(c, sir, "start of si_cmd");
	SCSI_TRACE('c', sir, un);
	un->un_flags &= ~SC_UNF_DMA_INITIALIZED;

	/* performing target selection */
	if ((err = si_arb_sel(c, sir, un)) != OK) {
		/* 
		 * May not be able to execute this command at this time due
		 * to a target reselecting us. Indicate this in the unit
		 * structure for when we perform this command later.
		 */
		SI_VME_OK(c, sir, "si_cmd: arb_sel_fail");

		if (err == RESEL_FAIL) {
			DPRINTF1("si_cmd:  preempted, tgt= %x\n",
				 un->un_target);
			un->un_saved_cmd.saved_cdb = c->c_cdb;
			un->un_flags |= SC_UNF_PREEMPT;
			err = OK;		/* not an error */

			/* Check for lost reselect interrupt */
		    	if ( !(SBC_RD.bsr & SBC_BSR_INTR)) {
				printf("si_cmd:  reselect failure\n");
				siintr(c);
			}
		}
		un->un_wantint = 0;
		if (IS_VME(c))
			sir->csr |= SI_CSR_DMA_EN;
		(void) splx(s);
		return (err);
	}

	/*
	 * We need to send out an identify message to target.
	 */
	SBC_WR.ser = 0;			/* clear (re)sel int */
	SBC_WR.mr &= ~SBC_MR_DMA;	/* clear phase int */
	(void) splx(s);
	SI_VME_OK(c, sir, "si_cmd: before msg out");
	if (c->c_flags & SCSI_EN_DISCON) {

		/* Tell target we do disconnects */
		DPRINTF("si_cmd:  disconnects ENABLED\n");
		id = SC_DR_IDENTIFY | c->c_cdb.lun;
		SBC_WR.tcr = TCR_MSG_OUT;
 		if (si_wait_phase(sir, PHASE_MSG_OUT) == OK) {
			if (si_putdata(c, PHASE_MSG_OUT, &id, 1) != OK) {
				EPRINTF1("si%d:  si_cmd: id msg failed\n",
					SINUM(c));
               			si_idle(c);
               		        return(HARD_FAIL);
			}
		}
	} else {
		/*
		 * Since we didn't raise ATN, the target knows we
		 * don't do disconnects and won't bother asking us.
		 */
		DPRINTF("si_cmd:  NO disconnect\n");
	}

	/*
	 * Must split dma setup into 2 parts due to sun3/50
	 * which requires bcr to be set before target
	 * changes phase on scsi bus to data phase.
	 *
	 * Three fields in the per scsi unit structure
	 * hold information pertaining to the current dma
	 * operation: un_dma_curdir, un_dma_curaddr, and
	 * un_dma_curcnt. These fields are used to track
	 * the amount of data dma'd especially when disconnects 
	 * and reconnects occur.
	 * If the current command does not involve dma,
	 * these fields are set appropriately.
	 */
	if (un->un_dma_count > 0) {

		/* reset udc */
		if (IS_ONBOARD(c)) {
			DELAY(si_udc_wait);
			sir->udc_raddr = UDC_ADR_COMMAND;
			DELAY(si_udc_wait);
			sir->udc_rdata = UDC_CMD_RESET;;
			DELAY(si_udc_wait);
		}

		/* reset fifo */
		sir->csr &= ~SI_CSR_FIFO_RES;
		sir->csr |= SI_CSR_FIFO_RES;

		if (un->un_flags & SC_UNF_RECV_DATA) {
			un->un_dma_curdir = SI_RECV_DATA;
			sir->csr &= ~SI_CSR_SEND;
		} else {
			un->un_dma_curdir = SI_SEND_DATA;
			sir->csr |= SI_CSR_SEND;
		}

		/* save current dma info for disconnect */
		un->un_dma_curaddr = un->un_dma_addr;
		un->un_dma_curcnt = un->un_dma_count;
		un->un_dma_curbcr = 0;

		if (IS_ONBOARD(c))
			/* must init bcr before tgt goes into data phase */
			sir->bcr = un->un_dma_curcnt;
		else {
			/* 
			 * Currently we don't use all 24 bits of the
			 * count register on the vme interface. To do
			 * this changes are required other places, e.g.
			 * in the scsi_unit structure the fields
			 * un_dma_curcnt and un_dma_count would need to
			 * be changed.
			 */
			SET_DMA_COUNT(sir, 0);
			sir->bcr = sir->bcrh = 0;
		}

		/*
		 * New: we set up everything we can here, rather
		 * than wait until data phase.
		 */
		if (IS_ONBOARD(c))
			si_ob_dma_setup(c, un);
		else {
			SI_VME_OK(c, sir, "si_cmd: before cmd phase");
			si_vme_dma_setup(c, un);
		}
	} else {
		un->un_dma_curdir = SI_NO_DATA;
		un->un_dma_curaddr = 0;
		un->un_dma_curcnt = 0;
		sir->bcr = 0;
	}
	SI_VME_OK(c, sir, "si_cmd: before cmd phase");
	SCSI_TRACE('C', sir, un);

RETRY_CMD_PHASE:
	if (si_wait_phase(sir, PHASE_COMMAND) != OK) {
		/*
		 * Handle synchronous messages (6 bytes) and other
		 * unknown messages.  Note, all messages will be
		 * rejected.  It would be nice someday to figure
		 * out what to do with them; but not today.
		 */
		register volatile u_char *icrp = &SBC_WR.icr;

		if ((SBC_RD.cbsr & CBSR_PHASE_BITS) == PHASE_MSG_IN) {
			*icrp = SBC_ICR_ATN;
			msg = si_getdata(c, PHASE_MSG_IN);
			EPRINTF1("si_cmd:  rejecting msg 0x%x\n", msg);

			i = 128; /* accept 128 message bytes (overkill) */
			while((si_getdata(c, PHASE_MSG_IN) != -1)  &&  --i);

			if ((SBC_RD.cbsr & CBSR_PHASE_BITS) == PHASE_MSG_OUT) {
				msg = SC_MSG_REJECT;
				*icrp = 0;		/* turn off ATN */
				(void) si_putdata(c, PHASE_MSG_OUT, &msg, 1);
			}
			/* Should never fail this check. */
			if( i > 0 )
				goto RETRY_CMD_PHASE;
		}
		/* we've had a target failure, report it and quit */
		printf("si%d:  si_cmd: no command phase\n", SINUM(c));
		si_reset(c, PRINT_MSG);
		return (SCSI_FAIL);
	}

#ifdef	sun3
	/*
	 * In the Sparc case DVMA+un->un_dma_addr can be unaligned.
	 * Unfortunately, SCSI_RECON_TRACE wants an int so for now
	 * we just won't trace here.
	 */ 
    	SCSI_RECON_TRACE('c', c, *(int *)(DVMA + un->un_dma_addr), 0, 0);
#endif	sun3

	/*
	 * Determine size of the cdb.  Since we're smart, we
	 * look at group code and guess.  If we don't
	 * recognize the group id, we use the specified
	 * cdb length.  If both are zero, use max. size
	 * of data structure.
	 */
	if ((size = cdb_size[CDB_GROUPID(c->c_cdb.cmd)]) == 0  &&
	    (size = c->c_un->un_cmd_len) == 0) {
		printf("si%d:  invalid cdb size, using size= %d\n",
			SINUM(c), sizeof (struct scsi_cdb));
		size = sizeof (struct scsi_cdb);
	}
	c->c_last_phase = PHASE_COMMAND;
	s = spl4();			/* time critical */
	SBC_WR.ser = SI_HOST_ID;	/* enable (re)sel int */
	if (si_putcmd(c, (u_char *)&c->c_cdb, size, intr) != OK) {
		printf("si%d:  si_cmd: cmd put failed\n", SINUM(c));
		si_print_state(sir, c);
		si_idle(c);
		(void) splx(s);
		return(HARD_FAIL);
	}

	/* If not polled I/O mode, we're done */
	if (intr) {
		/* Check for lost phase change interrupt */
		if ((SBC_RD.cbsr & SBC_CBSR_REQ)  &&
	 	    !(SBC_RD.bsr & SBC_BSR_INTR)) {
				printf("si_cmd:  interrupt failure\n");
				siintr(c);
		}
		if (IS_VME(c))
			sir->csr |= SI_CSR_DMA_EN;
		(void) splx(s);
		return (OK);
	}
	(void) splx(s);


	/* 
	 * Polled SCSI data transfer mode.
	 */
	if (un->un_dma_curdir != SI_NO_DATA) {
		register u_char phase;

		if (un->un_dma_curdir == SI_RECV_DATA)
			phase = PHASE_DATA_IN;
		else
			phase = PHASE_DATA_OUT;

		SI_VME_OK(c, sir, "si_cmd: before data xfer, sync");
		/*
		 * Check if we have a problem with the command
		 * not going into data phase.  If we do,
		 * then we'll skip down and get any status.
		 * Of course, this means that the command
		 * failed.
		 */
		if (si_wait_phase(sir, phase) == OK) {
			/*
			 * Must actually start DMA xfer here - setup
			 * has already been done.  So, put sbc in dma
			 * mode and start dma transfer.
			 */
			si_sbc_dma_setup(c, sir, (int)un->un_dma_curdir);

			/*
			 * Wait for DMA to finish.  If it fails,
			 * attempt to get status and report failure.
			 */
			if ((err=si_cmdwait(c)) != OK) {
				EPRINTF("si_cmd:  cmdwait failed\n");
				if (err != SCSI_FAIL)
					msg = si_getstatus(un);
				return (err);
			}
		} else {
			EPRINTF("si_cmd:  skipping data phase\n");
		}
	}

	/*
	 * Get completion status for polled command.
	 * Note, if <0, it's retryable; if 0, it's fatal.
	 * Someday I should give polled status results
	 * more options.  For now, everything is FATAL.
	 */
	c->c_last_phase = PHASE_CMD_CPLT;
	if ((err=si_getstatus(un)) <= 0) {
		if (err == 0) 
			return (HARD_FAIL);
		else
			return (FAIL);
	}
	return (OK);
}


/*
 * Perform the SCSI arbitration and selection phases.
 * Returns FAIL if unsuccessful, 
 * returns RESEL_FAIL if unsuccessful due to target reselecting, 
 * returns OK if all was cool.
 */
static
si_arb_sel(c, sir, un)
	register struct scsi_ctlr *c;
	register volatile struct scsi_si_reg *sir;
	register struct scsi_unit *un;
{
	register volatile u_char *icrp = &SBC_WR.icr;
	register volatile u_char *mrp = &SBC_WR.mr;
	register u_char icr;
	int ret_val;
	int j;

	/* 
	 * It seems that the tcr must be 0 for arbitration to work.
	 */
	DPRINTF("si_arb_sel:\n");
	SI_VME_OK(c, sir, "si_arb_sel");
	SBC_WR.tcr = 0;
	*mrp &= ~SBC_MR_ARB;	/* turn off arb */
	*icrp = 0;
#ifdef	SCSI_DEBUG
	if (scsi_debug > 2)
		si_print_state(sir, c);
#endif	SCSI_DEBUG

	/* arbitrate for the scsi bus */
	for (j = 0; j < SI_NUM_RETRIES; j++) {

		/* wait for scsi bus to become free */
		if (si_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_BSY,
		    SI_WAIT_COUNT, 0) != OK) {
			printf("si%d:  si_arb_sel: scsi bus continuously busy\n",
				SINUM(c));
			si_reset(c, PRINT_MSG);
			ret_val = SCSI_FAIL;
			goto SI_ARB_SEL_EXIT;
		}

		/* wait for sbc to begin arbitration */
		*mrp |= SBC_MR_ARB;		/* turn on arb */
		if (si_sbc_wait((caddr_t)icrp, SBC_ICR_AIP, SI_ARB_WAIT, 1)
		    != OK) {
			/*
			 * sbc may never begin arbitration due to a
			 * target attempting a reselection.
			 */
			*mrp &= ~SBC_MR_ARB;	/* turn off arb */
			if (((SBC_RD.cbsr & SBC_CBSR_RESEL)  == SBC_CBSR_RESEL) && 
			    (SBC_RD.cdr & SI_HOST_ID)) {
				DPRINTF("si_arb_sel:  recon1\n");
				ret_val = RESEL_FAIL;
				goto SI_ARB_SEL_EXIT;
			}
			EPRINTF1("si_arb_sel:  AIP never set, cbsr= 0x%x\n",
				 SBC_RD.cbsr);
#ifdef	SCSI_DEBUG
			si_print_state(sir, c);
#endif	SCSI_DEBUG
			goto SI_ARB_SEL_RETRY;
		}

		/* check to see if we won arbitration */
		DELAY(si_arbitration_delay);
		if ((*icrp & SBC_ICR_LA) == 0  && 
		    ((SBC_RD.cdr & ~SI_HOST_ID) < SI_HOST_ID)) {
			/*
			 * WON ARBITRATION!  Perform selection.
			 * If disconnect/reconnect enabled, set ATN.
			 * If not, skip ATN so target won't do disconnects.
			 */
			/* DPRINTF("si_arb_sel:  won arb\n"); */
			icr = SBC_ICR_SEL | SBC_ICR_BUSY | SBC_ICR_DATA;
			if (c->c_flags & SCSI_EN_DISCON) {
				icr |= SBC_ICR_ATN;
			}
			SBC_WR.odr = (1 << un->un_target) | SI_HOST_ID;
			*icrp = icr;
			*mrp &= ~SBC_MR_ARB;	/* turn off arb */
			DELAY(si_bus_clear_delay + si_bus_settle_delay);
			goto SI_ARB_SEL_WON;
		}

SI_ARB_SEL_RETRY:
		/* Lost arb, try again */
		*mrp &= ~SBC_MR_ARB;	/* turn off arb */
		if (((SBC_RD.cbsr & SBC_CBSR_RESEL)  == SBC_CBSR_RESEL) && 
		    (SBC_RD.cdr & SI_HOST_ID)) {
			DPRINTF("si_arb_sel:  recon2\n");
			ret_val = RESEL_FAIL;
			goto SI_ARB_SEL_EXIT;
		}
		EPRINTF("si_arb_sel:  lost arbitration\n");
	}
	/*
	 * FAILED ARBITRATION even with retries.
	 * This shouldn't ever happen since
	 * we have the highest priority id on the scsi bus.
	 */
	*icrp = 0;
	printf("si%d:  si_arb_sel: never won arbitration, \n", SINUM(c));
	si_print_state(sir, c);
	ret_val = HARD_FAIL;

SI_ARB_SEL_EXIT:
	return(ret_val);


SI_ARB_SEL_WON:
	/* wait for target to acknowledge selection */
	*icrp &= ~SBC_ICR_BUSY;
	DELAY(1);
	if (si_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_BSY,
	    SI_SHORT_WAIT, 1) != OK) {
		EPRINTF("si_arb_sel:  busy never set\n");
#ifdef	SCSI_DEBUG
		if (scsi_debug > 2)
			si_print_state(sir, c);
#endif	SCSI_DEBUG
		*icrp = 0;
		ret_val = HARD_FAIL;
		goto SI_ARB_SEL_EXIT;
	}
	DPRINTF("si_arb_sel:  selected\n");
	*icrp &= ~(SBC_ICR_SEL | SBC_ICR_DATA);
	c->c_last_phase = PHASE_ARBITRATION;
	return (OK);
}


/*
 * Set up the SCSI control logic for a dma transfer for vme host adaptor.
 */
static
si_vme_dma_setup(c, un)
	register struct scsi_ctlr *c;
	register struct scsi_unit *un;
{
	register volatile struct scsi_si_reg *sir;
	(int)sir = c->c_reg;

	/* reset fifo */
	sir->csr &= ~SI_CSR_FIFO_RES;
	sir->csr |= SI_CSR_FIFO_RES;

	SI_VME_OK(c, sir, "si_vme_dma_setup");
	SCSI_RECON_TRACE('v', c, un->un_dma_curaddr, (int)un->un_dma_curcnt,
				(int)un->un_dma_curbcr);

	DPRINTF2("si_vme_dma_setup:  after fifo reset, csr 0x%x, bcr 0x%x\n",
	sir->csr, sir->bcr);
	

	/* Check for odd-byte boundary buffer */
	/* NEED BETTER STRATEGY!! */
	if ((u_int)(un->un_dma_curaddr) & 0x1) {
		printf("si%d:  illegal odd byte DMA, address= 0x%x\n",
			SINUM(c), un->un_dma_curaddr);
		/* si_reset(c, PRINT_MSG); */
		/* return; */
	}

	/*
	 * setup starting dma address and number bytes to dma
	 * Note, the dma count is set to zero to prevent it from
	 * starting up.  It will be set later in si_sbc_dma_setup
	 */
	SET_DMA_ADDR(sir, un->un_dma_curaddr);
	SET_DMA_COUNT(sir, 0);

	/* set up byte packing control info */
	if (un->un_dma_curaddr & 0x2) {
		/* setup word dma transfers across vme bus */
		DPRINTF("si_vme_dma_setup: word xfer\n");
		sir->csr |= SI_CSR_BPCON;
	} else {
		/* setup longword dma transfers across vme bus */
		DPRINTF("si_vme_dma_setup: long word xfer\n");
		sir->csr &= ~SI_CSR_BPCON;
	}

	/*
	 * junk = GET_DMA_ADDR(sir);
	 * DPRINTF1("si_vme_dma_setup:  addr= 0x%x", junk);
	 * junk = GET_DMA_COUNT(sir);
	 * DPRINTF1("  count= %d ", junk);
	 * DPRINTF2("csr= 0x%x  bcr= 0x%x\n", sir->csr, sir->bcr);
	 */
}


/*
 * Set up the SCSI control logic for a dma transfer for onboard host
 * adaptor.
 */
static
si_ob_dma_setup(c, un)
	register struct scsi_ctlr *c;
	register struct scsi_unit *un;
{
	register volatile struct scsi_si_reg *sir;
	register volatile struct udc_table *udct = &c->c_udct;
	register int addr;

	DPRINTF("si_ob_dma_setup\n");
	(int)sir = c->c_reg;

	/* reset udc */
	if (IS_ONBOARD(c)) {
		DELAY(si_udc_wait);
		sir->udc_raddr = UDC_ADR_COMMAND;
		DELAY(si_udc_wait);
		sir->udc_rdata = UDC_CMD_RESET;;
		DELAY(si_udc_wait);
	}

	/* reset fifo */
	sir->csr &= ~SI_CSR_FIFO_RES;
	sir->csr |= SI_CSR_FIFO_RES;

	/* Check for odd-byte boundary buffer */
	/* NEED BETTER STRATEGY!! */
	if ((u_int)(un->un_dma_curaddr) & 0x1) {
		printf("si%d:  illegal odd byte DMA, address= 0x%x\n",
			SINUM(c), un->un_dma_curaddr);
		/* si_reset(c, PRINT_MSG); */
		/* return; */
	}

	/* set up udc dma information */
	addr = un->un_dma_curaddr;
	if (addr < DVMA_OFFSET)
		addr += DVMA_OFFSET;

	udct->haddr = ((addr & 0xff0000) >> 8) | UDC_ADDR_INFO;
	udct->laddr = addr & 0xffff;
	udct->hcmr = UDC_CMR_HIGH;
	udct->count = un->un_dma_curcnt / 2; /* #bytes -> #words */

	if (un->un_dma_curdir == SI_RECV_DATA) {
		udct->rsel = UDC_RSEL_RECV;
		udct->lcmr = UDC_CMR_LRECV;
	} else {
		udct->rsel = UDC_RSEL_SEND;
		udct->lcmr = UDC_CMR_LSEND;
		if (un->un_dma_curcnt & 1) {
			udct->count++;
		}
	}

	/* initialize udc chain address register */
	sir->udc_raddr = UDC_ADR_CAR_HIGH;
	DELAY(si_udc_wait);
	sir->udc_rdata = ((int)udct & 0xff0000) >> 8;
	DELAY(si_udc_wait);
	sir->udc_raddr = UDC_ADR_CAR_LOW;
	DELAY(si_udc_wait);
	sir->udc_rdata = (int)udct & 0xffff;


	/*
	 * junk = GET_DMA_ADDR(sir);
	 * DPRINTF2("si_ob_dma_setup:  udct= 0x%x  addr= 0x%x", udct, junk);
	 * junk = GET_DMA_COUNT(sir);
	 * DPRINTF1("  count= %d\n", junk);
	 */

	/* initialize udc master mode register */
	DELAY(si_udc_wait);
	sir->udc_raddr = UDC_ADR_MODE;
	DELAY(si_udc_wait);
	sir->udc_rdata = UDC_MODE;

	/* issue channel interrupt enable command, in case of error, to udc */
	DELAY(si_udc_wait);
	sir->udc_raddr = UDC_ADR_COMMAND;
	DELAY(si_udc_wait);
	sir->udc_rdata = UDC_CMD_CIE;
}


/*
 * Setup and start the sbc for a dma operation.
 */
static
si_sbc_dma_setup(c, sir, dir)
	register struct scsi_ctlr *c;
	register volatile struct scsi_si_reg *sir;
	register int dir;
{
	register struct scsi_unit *un = c->c_un;
	register int s;

	DPRINTF("si_scb_dma_setup\n");
	SCSI_TRACE('G', sir, un);
	SI_VME_OK(c, sir, "si_sbc_dma_setup");
	un->un_flags |= SC_UNF_DMA_INITIALIZED;

	if (IS_ONBOARD(c)) {
		/* issue start chain command to udc */
		DELAY(si_udc_wait);
		sir->udc_rdata = UDC_CMD_STRT_CHN;
	} else {
		SET_DMA_COUNT(sir, un->un_dma_curcnt);
		sir->bcr = un->un_dma_curcnt;
	}

	if (dir == SI_RECV_DATA) {
		DPRINTF("si_sbc_dma_setup:  RECEIVE DMA\n");
		c->c_last_phase = PHASE_DATA_IN;
		s = spl4();		/* time critical */
		SBC_WR.tcr = TCR_DATA_IN;
		junk = SBC_RD.clr;      /* clear intr */
		SBC_WR.mr |= SBC_MR_DMA;
		SBC_WR.ircv = 0;
		(void) splx(s);
	} else {
		/* DPRINTF("si_sbc_dma_setup:  XMIT DMA\n"); */
		c->c_last_phase = PHASE_DATA_OUT;
		s = spl4();		/* time critical */
		SBC_WR.tcr = TCR_DATA_OUT;
		junk = SBC_RD.clr;      /* clear intr */
		SBC_WR.icr = SBC_ICR_DATA;
		SBC_WR.mr |= SBC_MR_DMA;
		SBC_WR.send = 0;
		(void) splx(s);
	}
	if (IS_VME(c))
		sir->csr |= SI_CSR_DMA_EN;
}


/*
 * Cleanup up the SCSI control logic after a dma transfer.
 */
static
si_dma_cleanup(c)
	register struct scsi_ctlr *c;
{
	register volatile struct scsi_si_reg *sir;
	(int)sir = c->c_reg;

	DPRINTF("si_dma_cleanup:\n");

	/* disable dma controller */
	if (IS_ONBOARD(c)) {
		DELAY(si_udc_wait);
		sir->udc_raddr = UDC_ADR_COMMAND;
		DELAY(si_udc_wait);
		sir->udc_rdata = UDC_CMD_RESET;
		DELAY(si_udc_wait);
	} else {
		SET_DMA_ADDR(sir, 0);
		SET_DMA_COUNT(sir, 0);
	}

	/* reset fifo */
	sir->csr &= ~SI_CSR_FIFO_RES;
	sir->csr |= SI_CSR_FIFO_RES;
	sir->bcr = 0;
}

/*
 * Handle special dma receive situations, e.g. an odd number of bytes 
 * in a dma transfer.
 * The Sun3/50 onboard interface has different situations which
 * must be handled than the vme interface.
 * Returns OK if sucessful; Otherwise FAIL.
 */
static
si_dma_recv(c) 
	register struct scsi_ctlr *c;
{
	register volatile struct scsi_si_reg *sir;
	register struct scsi_unit *un = c->c_un;
	register int offset;
	(int)sir = c->c_reg;

	DPRINTF("si_dma_recv:\n");
	offset = un->un_dma_curaddr + (un->un_dma_curcnt - sir->bcr);

	SCSI_RECON_TRACE('R', c, un->un_dma_curaddr, (int)un->un_dma_curcnt,
			 offset);
	SCSI_TRACE('u', sir, un);

	/* handle the onboard scsi situations */
	if (IS_ONBOARD(c)) {
		sir->udc_raddr = UDC_ADR_COUNT;

		/* wait for the fifo to empty */
		if (si_wait((u_short *)&sir->csr, SI_CSR_FIFO_EMPTY, 1) != OK) {
			EPRINTF("si_dma_recv:  fifo never emptied\n");
			return (FAIL);
		}

		/*
		 * Didn't transfer any data.
		 * "Just say no" and leave, rather than
		 * erroneously executing left over byte code.
		 * The bcr + 1 above wards against 5380 prefetch.
		 */
		if ((sir->bcr == un->un_dma_curcnt)  ||
		    (sir->bcr + 1 == un->un_dma_curcnt))
			return (OK);

		/* handle odd byte */
		if ((un->un_dma_curcnt - sir->bcr) & 1) {
			DVMA[offset - 1] = (sir->fifo_data & 0xff00) >> 8;

		/*
		 * The udc may not dma the last word from the fifo_data
		 * register into memory due to how the hardware turns
		 * off the udc at the end of the dma operation.
		 */
		} else if (((sir->udc_rdata*2) - sir->bcr) == 2) {
			DVMA[offset - 2] = (sir->fifo_data & 0xff00) >> 8;
			DVMA[offset - 1] = sir->fifo_data & 0x00ff;
		}

	/* handle the vme scsi situations */
	} else if ((sir->csr & SI_CSR_LOB) != 0) {
	    /*
	     * Grabs last few bytes which may not have been dma'd.
	     * Worst case is when longword dma transfers are being done
	     * and there are 3 bytes leftover.
	     * If BPCON bit is set then longword dmas were being done,
	     * otherwise word dmas were being done.
	     */
	    if ((sir->csr & SI_CSR_BPCON) == 0) {
		switch (sir->csr & SI_CSR_LOB) {
		case SI_CSR_LOB_THREE:
			DVMA[offset - 3] = (sir->bprh & 0xff00) >> 8;
			DVMA[offset - 2] = sir->bprh & 0x00ff;
			DVMA[offset - 1] = (sir->bprl & 0xff00) >> 8;
			break;

		case SI_CSR_LOB_TWO:
			DVMA[offset - 2] = (sir->bprh & 0xff00) >> 8;
			DVMA[offset - 1] = sir->bprh & 0x00ff;
			break;

		case SI_CSR_LOB_ONE:
			DVMA[offset - 1] = (sir->bprh & 0xff00) >> 8;
			break;
		}
	    } else {
		DVMA[offset - 1] = (sir->bprl & 0xff00) >> 8;
	    }
	}
	return (OK);
}


/*
 * Handle a scsi interrupt.
 */
siintr(c)
	register struct scsi_ctlr *c;
{
	register volatile struct scsi_si_reg *sir;
	register struct scsi_unit *un;
	register u_char *cp;
	register int resid;
	int status;
	u_int lun;
	u_short bcr;	/* get it for discon stuff BEFORE we clr int */
	u_char msg;

	DPRINTF("siintr:\n");
	(int)sir = c->c_reg;

	/* 
	 * For vme host adaptor interface, must disable dma before
	 * accessing any registers other than the csr or the 
	 * SI_CSR_DMA_CONFLICT bit in the csr will be set.
	 */
HEAD_SIINTR:
	un = c->c_un;
	if (IS_VME(c)) {
#ifdef	SCSI_DEBUG
		/* if (sir->csr & SI_CSR_DMA_EN)
		 *	printf("siintr:  DMA DISABLED\n");
		 */
#endif	SCSI_DEBUG
		sir->csr &= ~SI_CSR_DMA_EN;
	}

	/*
	 * We need to store the contents of the byte count register
	 * before we change the state of the 5380.  The 5380 has
	 * a habit of prefetching data before it knows whether it
	 * needs it or not, and this can throw off the bcr.
	 */
	resid = 0;
 	bcr = sir->bcr;
	/* SBC_WR.tcr = TCR_UNSPECIFIED; */
	SCSI_TRACE('i', sir, un);

	/*
	 * Determine source of interrupt.
	 */
	if (sir->csr & (SI_CSR_DMA_IP | SI_CSR_DMA_CONFLICT)) {
		/*
		 * DMA related error.
		 */
		if (sir->csr & SI_CSR_DMA_BUS_ERR) {
			printf("si%d:  siintr: bus error during dma\n",
				SINUM(c));
			/* goto RESET_AND_LEAVE; */

		} else if (sir->csr & SI_CSR_DMA_CONFLICT) {
			printf("si%d:  siintr: invalid reg access during dma\n",
				SINUM(c));
		} else {
			printf("si%d:  siintr: dma in progress\n", SINUM(c));
		}
		si_print_state(sir, c);
		junk = SBC_RD.clr;	/* clear int, if any */

		/*
		 * Either we were waiting for an interrupt on a phase change 
		 * on the scsi bus, an interrupt on a reconnect attempt,
		 * or an interrupt upon completion of a real dma operation.
		 * Each of these situations must be handled appropriately.
		 */
		if (un == NULL) {
			/* Waiting for reconnect. */
			printf("si%d:  siintr: illegal reconnection for DMA\n",
				SINUM(c));
			goto RESET_AND_LEAVE;

		} else if (un->un_flags & SC_UNF_DMA_ACTIVE) {
			/*
			 * Unit was DMAing, must clean up.
			 * This is a bit tricky.  The bcr is set to
			 * zero for the SCSI-3 host adaptor until we
			 * actually go into data phase.  If we run
			 * a data xfer command, but never go into
			 * data phase, the bcr will be zero.  We must
			 * guard against interpeting this as meaning
			 * that we have transferred all our data -
			 * in this instance, we have really transferred none.
			 * SC_UNF_DMA_INITIALIZED tells us (for SCSI-3)
			 * whether we have loaded the bcr.
			 */
			if (un->un_flags & SC_UNF_DMA_INITIALIZED) {
				resid = un->un_dma_curcnt = bcr;
			} else {
				resid = un->un_dma_curcnt;
			}
			si_dma_cleanup(c);
			un->un_flags &= ~SC_UNF_DMA_ACTIVE;
		}
		/*
		 * We have probably blew it on the DMA and should reset.
		 * But, let's pospone it until things really screw-up.
		 */
		goto HANDLE_SPURIOUS_AND_LEAVE;
	}

	/*
	 * We have an SBC interrupt due to a phase change on the bus
	 * or a reconnection attempt.  First, check for reconnect
	 * attempt.
	 */
	if (((SBC_RD.cbsr & SBC_CBSR_RESEL)  == SBC_CBSR_RESEL) && 
	    (SBC_RD.cdr & SI_HOST_ID)) {
		register u_char cdr;
		register int i;

HANDLE_RECONNECT:
		/* get reselecting target scsi id */
		cdr = SBC_RD.cdr & ~SI_HOST_ID;

		/* make sure there are only 2 scsi id's set */
		DPRINTF1("siintr:  reconnecting, cdr 0x%x\n", cdr);
		for (i=0; i < 8; i++) {
			if (cdr & (1<<i))
				break;
		}
		/* CRITICAL CODE SECTION DON'T TOUCH */
		SBC_WR.ser = 0;		 /* clear (re)sel int */
		cdr &= ~(1<<i);
		if (cdr != 0) {
			printf("si%d:  siintr: >2 scsi reselection ids, cdr 0x%x\n",
				SINUM(c), SBC_RD.cdr);
			SBC_WR.ser = SI_HOST_ID; /* enable (re)sel int */
			goto SET_UP_FOR_NEXT_INTR_AND_LEAVE;
		}

		/* acknowledge reselection */
		SBC_WR.icr |= SBC_ICR_BUSY;
		c->c_recon_target = i;		/* save for reconnect */

		/*
		 * If reselection ok, target should drop select.
		 * Otherwise, we took too long.  It would be nice
		 * to wait for next resel attempt...someday.
		 */
		if (si_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_SEL,
		    SI_WAIT_COUNT, 0) != OK) {
			printf("si%d:  siintr: SEL not released\n",
				SINUM(c));
			SBC_WR.ser = SI_HOST_ID; /* enable (re)sel int */
			goto SET_UP_FOR_NEXT_INTR_AND_LEAVE;
		}
		SBC_WR.icr &= ~SBC_ICR_BUSY;
#ifdef	SCSI_DEBUG
		if (scsi_debug > 2) {
			printf("siintr:  reconnecting\n");
			si_print_state(sir, c);
		}
#endif	SCSI_DEBUG

		/*
		 * If reselection ok, then target should go into MSG_IN
		 * phase to identify.  If not, die.
		 */
		if (si_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ,
		    SI_WAIT_COUNT, 1) != OK) {
			printf("si%d:  siintr: no MSG_IN req\n", SINUM(c));
			SBC_WR.ser = SI_HOST_ID; /* enable (re)sel int */
			goto SET_UP_FOR_NEXT_INTR_AND_LEAVE;
		}
		SBC_WR.ser = SI_HOST_ID;	/* enable (re)sel int */
		/* FALL THROUGH INTO SYNCHRONIZE_PHASE */
	}
	SBC_WR.tcr = TCR_UNSPECIFIED;


SYNCHRONIZE_PHASE:
	/*
	 * We know that we have a new phase we have to handle.
	 */
	DPRINTF("siintr: synch\n");
	if (si_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ, SI_PHASE_WAIT, 1)
	    != OK) {
		/* DPRINTF("siintr:  phase timeout\n"); */
		goto HANDLE_SPURIOUS_AND_LEAVE;
	}
	SI_WIN;
	junk = SBC_RD.clr;		 /* clear any pending sbc interrupt */
	switch (SBC_RD.cbsr & CBSR_PHASE_BITS) {

	case PHASE_DATA_IN:
	case PHASE_DATA_OUT:
		DPRINTF("  DATA\n");
#ifdef	SCSI_DEBUG
		if (scsi_debug > 2)
			si_print_state(sir, c);
#endif	SCSI_DEBUG
		SI_VME_OK(c, sir, "siintr: data_out");
		SBC_WR.mr &= ~SBC_MR_DMA;	/* clear phase int */

		if (un == NULL) {
			printf("si%d:  siintr: no unit expecting DATA phase\n",
				SINUM(c));
			goto RESET_AND_LEAVE;
		}

		if (un->un_dma_curcnt <= 0  ||  un->un_dma_curdir == SI_NO_DATA) {
			printf("si%d:  siintr: unexpected DATA phase, curcnt %d, curdir 0x%x\n",
				SINUM(c), un->un_dma_curcnt, un->un_dma_curdir);
			goto RESET_AND_LEAVE;
		}

		/* data is expected, start dma data transfer and exit */
		si_sbc_dma_setup(c, sir, (int)un->un_dma_curdir);
		goto LEAVE;


	case PHASE_MSG_IN:
		DPRINTF("  MSG");
#ifdef	SCSI_DEBUG
		if (scsi_debug > 2)
			si_print_state(sir, c);
#endif	SCSI_DEBUG
		SI_VME_OK(c, sir, "siintr: msg_in");

		msg = SBC_RD.cdr;		/* peek at message */
		lun = msg & 0x07;
		msg &= 0xf0;			/* mask off unit number */

		/* DPRINTF2("siintr:  msg 0x%x, lun %d\n", msg, lun); */
		if ((msg == SC_IDENTIFY)  ||  (msg == SC_DR_IDENTIFY)) {
			/*
			 * If we have a reconnect, we want to do our
			 * DMA setup before we go into DATA phase.
			 * This is why we peek at the message via the cdr
			 * rather than doing an si_getdata from the start.
			 * si_reconnect acknowledges the reconnect message.
			 */
			/* EPRINTF("siintr:  msg= identify\n"); */
			if (si_reconnect(c, c->c_recon_target, lun) != OK){
				printf("si$d:  siintr:  reconnection failure\n",
					SINUM(c));
				goto RESET_AND_LEAVE;
			}
			un = c->c_un;
			if ( un->un_dma_curdir == SI_SEND_DATA) {
				DPRINTF2("cnt= %d, dma= %d  ",
					un->un_dma_curcnt, un->un_dma_count);
				DPRINTF2("tgt= %d, lun= %d\n",
					un->un_target, un->un_lun);
			}
			/* DMA is setup, but NOT running */
			un->un_flags &= ~SC_UNF_DMA_INITIALIZED;
			c->c_last_phase = PHASE_MSG_IN;
			goto SYNCHRONIZE_PHASE;
		}

		if (SBC_RD.cdr == SC_DISCONNECT) {

			if (un->un_dma_curdir == SI_RECV_DATA) {
				un->un_dma_curbcr = bcr;

				SCSI_RECON_TRACE('a', c, (int)un->un_dma_curaddr, 
				(int)un->un_dma_curbcr, (int)sir->bcr);
			}
		}

		c->c_last_phase = PHASE_MSG_IN;
		msg = si_getdata(c, PHASE_MSG_IN);
		switch (msg) {

		case SC_COMMAND_COMPLETE:
			/* DPRINTF("siintr:  msg= command complete\n"); */
			c->c_last_phase = PHASE_CMD_CPLT;
			cp = (u_char *) &c->c_scb;
			if (cp[0] & SCB_STATUS_MASK)
				status = SE_RETRYABLE;
			else
				status = SE_NO_ERROR;
			goto HAND_OFF_INTR;

		case SC_DISCONNECT:
			DPRINTF("siintr:  msg= disconnect\n");
			c->c_last_phase = PHASE_DISCONNECT;
			if ((un->un_flags & SC_UNF_DMA_INITIALIZED) == 0  &&
			    (un->un_dma_curdir == SI_SEND_DATA) &&
			    (un->un_dma_curcnt != un->un_dma_count)) {
				EPRINTF("siintr:  Warning, write disconnect w/o DMA\n");
				EPRINTF2("\tcnt= %d (%d)  ",
					 un->un_dma_curcnt, un->un_dma_count);
				EPRINTF2("bcr= %d  tgt= %d  ",
					 un->un_dma_curbcr, un->un_target);
				EPRINTF1("lun= %d  cdb =", un->un_lun);
#ifdef	SCSI_DEBUG
				if (scsi_debug)
					si_print_cdb(c);
#endif	SCSI_DEBUG
			}
			if (si_disconnect(c) != OK) {
				printf("si%d:  siintr: disconnect failure\n",
					SINUM(c));
				goto RESET_AND_LEAVE;
			}
			goto START_NEXT_COMMAND_AND_LEAVE;

		case SC_RESTORE_PTRS:
			/* these messages are noise  - ignore them */
			DPRINTF("siintr:  msg= restore pointer\n");
			c->c_last_phase = PHASE_RESTORE_PTR;
			goto SYNCHRONIZE_PHASE;

		case SC_SAVE_DATA_PTR:
			/* save the bcr before the bastard pre-fetches again */
			DPRINTF("siintr:  msg= save pointer\n");
			un->un_dma_curbcr = bcr;
			c->c_last_phase = PHASE_SAVE_PTR;
			goto SYNCHRONIZE_PHASE;

		case SC_NO_OP:
			EPRINTF("siintr:  msg= no op\n");
			goto SYNCHRONIZE_PHASE;

		case SC_PARITY:
			EPRINTF("siintr:  msg= parity error\n");
			goto SYNCHRONIZE_PHASE;

		case SC_ABORT:
			EPRINTF("siintr:  msg= abort\n");
			goto SET_UP_FOR_NEXT_INTR_AND_LEAVE;

		case SC_DEVICE_RESET:
			EPRINTF("siintr:  msg= reset device\n");
			goto SET_UP_FOR_NEXT_INTR_AND_LEAVE;

		default:
			printf("si%d:  siintr: ignoring unknown message, 0x%x\n",
				SINUM(c), msg);
			goto HANDLE_SPURIOUS_AND_LEAVE;
		}


	case PHASE_STATUS:
		DPRINTF("  STATUS");
#ifdef	SCSI_DEBUG
		if (scsi_debug > 2)
			si_print_state(sir, c);
#endif	SCSI_DEBUG
		SI_VME_OK(c, sir, "siintr: status");
		if ((un->un_dma_curdir == SI_RECV_DATA)  &&
		    (si_dma_recv(c) != OK)) {
			/* DMA failure, time to reset SCSI bus */
			printf("si%d:  siintr: DMA failure\n", SINUM(c));
			goto RESET_AND_LEAVE;
		}

		/* DPRINTF("siintr:  getting status bytes\n"); */
		if (! si_status_bytes(un)) {
			/* status failure, time to reset SCSI bus */
			printf("si%d:  siintr: no status\n", SINUM(c));
			goto RESET_AND_LEAVE;
		}
		SCSI_TRACE('s', sir, un);
		c->c_last_phase = PHASE_STATUS;
		goto SYNCHRONIZE_PHASE;


	default:
		printf("si%d:  siintr: ignoring spurious phase\n", SINUM(c));
		si_print_state(sir, c);
		c->c_last_phase = PHASE_SPURIOUS;
		goto HANDLE_SPURIOUS_AND_LEAVE;
}


HAND_OFF_INTR:
	DPRINTF("hand_off_intr:\n");
	SI_VME_OK(c, sir, "siintr: hand off intr");
	if (IS_VME(c))
		sir->csr &= ~SI_CSR_DMA_EN;

	/* pass interrupt info to unit */
	if (un  &&  un->un_wantint) {
		un->un_wantint = 0;

		SCSI_RECON_TRACE('f', c, 0, 0, 0);
		if (un->un_dma_curdir != SI_NO_DATA) {
			if (bcr == 0xffff)	/* fix pre-fetch botch */
				bcr = 0;
			/*
			 * This is a bit tricky.  The bcr is set to
			 * zero for the SCSI-3 host adaptor until we
			 * actually go into data phase.  If we run
			 * a data xfer command, but never go into
			 * data phase, the bcr will be zero.  We must
			 * guard against interpeting this as meaning
			 * that we have transferred all our data -
			 * in this instance, we didn't really transfer any.
			 * SC_UNF_DMA_INITIALIZED is used to handle
			 * the problem.
			 */
			if (un->un_flags & SC_UNF_DMA_INITIALIZED) {
				/* bcr is valid */
				resid = un->un_dma_curcnt = bcr;
			} else {
				/* bcr is invalid */
				resid = un->un_dma_curcnt;
			}
		}
#ifdef	SCSI_DEBUG
		if ((scsi_debug > 2)  &&  resid) {
			printf("siintr:  residue error\n");
			si_print_state(sir, c);
		}
#endif	SCSI_DEBUG

		/* call high-level scsi device interrupt handler to finish */
		(*un->un_ss->ss_intr)(c, resid, status);
		if (IS_VME(c))
			sir->csr &= ~SI_CSR_DMA_EN;
	}
	/* fall through to start_next_command_and_leave */


START_NEXT_COMMAND_AND_LEAVE:

	/* start next I/O activity on controller */
	DPRINTF("siintr:  start_next_command\n");
	SI_VME_OK(c, sir, "siintr: start next command");
	if ((un->un_mc->mc_tab.b_actf)  &&  (un->un_mc->mc_tab.b_active == 0)) {

		/*
		 * We have things to do and the controller is not busy.
		 */
		register struct buf *dp = un->un_mc->mc_tab.b_actf;
		un = (struct scsi_unit *)dp->b_un.b_addr;

		/*
		 * Check if we have a reconnect pending already.
		 * This happens with some stupid SCSI controllers
		 * which automatically disconnect, even when
		 * they don't have to. Rather than field another
		 * interrupt, let's go handle it.
		 */
		if (((SBC_RD.cbsr & SBC_CBSR_RESEL)  == SBC_CBSR_RESEL) && 
		    (SBC_RD.cdr & SI_HOST_ID)) {
			EPRINTF("siintr:  recon1\n");
			goto HANDLE_RECONNECT;
		}
		/* 
		 * If this activity was preempted due to a 
		 * reselection coming in, much of the setup has 
		 * already taken place and must not be redone.
		 */
		if (un->un_flags & SC_UNF_PREEMPT) {

			DPRINTF1("siintr:  doing preempted, tgt= %x\n",
				 un->un_target);
			un->un_flags &= ~SC_UNF_PREEMPT;
			c->c_cdb = un->un_saved_cmd.saved_cdb;
			c->c_un = un;
			un->un_mc->mc_tab.b_active = 1;
			if (un->un_dma_curdir != SI_NO_DATA) {
				un->un_mc->mc_mbinfo = un->un_baddr;
			}

			if (si_cmd(c, un, 1) == FAIL) {
				/*
				 * Command startup failed.
				 */
				EPRINTF1("siintr:  preempted FAILED, tgt= %x\n",
					 un->un_target);
				(*un->un_ss->ss_intr)(c, 0, SE_FATAL);
				si_off(c, un);
			}
		} else {
			DPRINTF("siintr:  sistart\n");
			sistart(un);
		}
	}
	/*
	 * Either we've started a command or there weren't any to start.
	 * In any case, we're done...
	 */
	goto SET_UP_FOR_NEXT_INTR_AND_LEAVE;


RESET_AND_LEAVE:
	EPRINTF1("siintr:  reset_and_leave: RESET to state 0x%x\n",si_stbi);
	si_reset(c, PRINT_MSG);
	goto SET_UP_FOR_NEXT_INTR_AND_LEAVE;


HANDLE_SPURIOUS_AND_LEAVE:
	SBC_WR.mr |= SBC_MR_DMA;
	/* FALL THROUGH */


SET_UP_FOR_NEXT_INTR_AND_LEAVE:
	DPRINTF("siintr:  set_up_for_next_intr\n");
	if (IS_VME(c))
		sir->csr &= ~SI_CSR_DMA_EN;
	junk = SBC_RD.clr;		/* clear int */
	SI_VME_OK(c, sir, "siintr: setup for next intr");

	/*
	 * For depending on the last phase, we need to
	 * check either for target reselection or a
	 * SCSI bus phase change.
	 */
	if (c->c_last_phase == PHASE_CMD_CPLT  ||
	    c->c_last_phase == PHASE_DISCONNECT) {

		/* Check for reselection.  */
		/* register int s; */
		/* s = spl7();	/* time critical */
		msg = SBC_RD.cbsr;
		if (((msg & SBC_CBSR_RESEL)  == SBC_CBSR_RESEL) && 
		    (SBC_RD.cdr & SI_HOST_ID)) {
			/* (void) splx(s); */
			SI_WIN;
			/* EPRINTF("siintr:  recon2\n"); */
			goto HEAD_SIINTR;
		} else {
			SI_LOSE;
			/* EPRINTF("  lose2"); */
		}
	} else {
		/* Check for phase change.  */
		/*s = spl7();	/* time critical */
		msg = SBC_RD.cbsr;
		if (msg & SBC_CBSR_REQ) {
			/* (void) splx(s); */
			SI_WIN;
			/* EPRINTF("siintr:  recon3\n"); */
			goto HEAD_SIINTR;
		} else {
			SI_LOSE;
			/* EPRINTF("  lose3"); */
		}
	}

	/* Enable interrupts and DMA. */
	if (IS_VME(c)) {
		/* DPRINTF("siintr:  DMA ENABLED\n"); */
		sir->csr |= SI_CSR_DMA_EN;
	}

LEAVE:
	DPRINTF("\n");
	return;
}


/*
 * Handle target disconnecting.
 * Returns true if all was OK, false otherwise.
 */
static
si_disconnect(c) 
	register struct scsi_ctlr *c;
{
	register struct scsi_unit *un = c->c_un;
	register struct mb_ctlr *mc = un->un_mc;
	register struct buf *dp;
	register volatile struct scsi_si_reg *sir;
	register u_short bcr;

	DPRINTF("si_disconnect:\n");
	(int)sir = c->c_reg;
	bcr = sir->bcr;

	SCSI_RECON_TRACE('d', c, un->un_dma_curaddr, (int) un->un_dma_curbcr,
				(int) bcr);

	/*
	 * If command doen't require dma, don't save dma info.
	 * for reconnect.  If it does, but data phase was missing,
	 * don't update dma info.
	 */
	if ((un->un_dma_curdir != SI_NO_DATA)  &&
	    (un->un_flags & SC_UNF_DMA_INITIALIZED)) {

		if (IS_VME(c)) {
			/* 
			 * bcr does not reflect how many bytes were actually
			 * transferred for VME.
			 */
			SCSI_RECON_TRACE('D', c, un->un_dma_curaddr, 
					(int)un->un_dma_curcnt, (int)bcr);
			/*
			 * SCSI-3 VME interface is a little funny on 
			 * writes: if we have a disconnect, the dma 
			 * has overshot by one byte and needs to be 
			 * incremented.
			 * this is true if we have not transferred
			 * either all data or no data.
			 */
			if ((un->un_dma_curdir == SI_SEND_DATA) &&
			    (bcr != un->un_dma_curcnt) &&
			    (bcr != 0)) {

				if (un->un_dma_curbcr != 0) {
					bcr = un->un_dma_curbcr + 1;
					SCSI_RECON_TRACE('g', c, 
					un->un_dma_curaddr, 
					(int)un->un_dma_curcnt,
					(int) bcr);
				} else {
					bcr++;
					SCSI_RECON_TRACE('z', c, 
					un->un_dma_curaddr, 
					(int)un->un_dma_curcnt,
					(int) bcr);
				}
				SCSI_TRACE('g', sir, un);

			} else if (un->un_dma_curdir == SI_RECV_DATA) {
				/* 
				 * Use the bcr value we got before
				 * we pulled in the discon message.
				 */
				bcr = un->un_dma_curbcr;
				SCSI_RECON_TRACE('x', c, 
					un->un_dma_curaddr, 
					(int)un->un_dma_curcnt,
					(int)bcr);
			}
		} else {
			/* If no VME, it must be onboard (e.g. Sun 3/50) */
			bcr = sir->bcr;
			SCSI_RECON_TRACE('b', c, 
					un->un_dma_curaddr, 
					(int)un->un_dma_curcnt,
					(int)bcr);
		}

		if ((un->un_dma_curdir == SI_RECV_DATA)  &&
		    (si_dma_recv(c) != OK)) {
			printf("si%d:  si_disconnect: DMA bogosity\n",SINUM(c));
			return (FAIL);
		}

		/*
		 * Save dma information so dma can be restarted when
		 * a reconnect occurs.
		 */
		un->un_dma_curaddr += un->un_dma_curcnt - bcr;
		un->un_dma_curcnt = bcr;
		SCSI_RECON_TRACE('q', c, un->un_dma_curaddr, 
					(int)un->un_dma_curcnt, (int)bcr); 
#ifdef	SCSI_DEBUG
		if (bcr == 1)
			printf("si_disconnect:  bcr is 1\n");
		if (scsi_dis_debug) {
		    printf("si_disconnect:  addr= 0x%x  count= %d  bcr= 0x%x  ",
			   un->un_dma_curaddr, un->un_dma_curcnt,  bcr);
		    printf("sr= 0x%x  baddr= 0x%x\n", sir->csr, un->un_baddr);
		}
#endif	SCSI_DEBUG
	}


	/* 
	 * Remove this disconnected task from the ctlr ready queue and save 
	 * on disconnect queue until a reconnect is done.
	 * Advance controller queue. Remove mainbus resource alloc info.
	 */
	dp = mc->mc_tab.b_actf;
	mc->mc_tab.b_active = 0;
	mc->mc_tab.b_actf = dp->b_forw;
	mc->mc_mbinfo = 0;

	if (c->c_disqh == NULL) 
		c->c_disqh = dp;
	else
		c->c_disqt->b_forw = dp;

	dp->b_forw = NULL;
	c->c_disqt = dp;
	c->c_un = NULL;
	SI_VME_OK(c, sir, "si_disconnect");

	/* reset udc */
	if (IS_ONBOARD(c)) {
		DELAY(si_udc_wait);
		sir->udc_raddr = UDC_ADR_COMMAND;
		DELAY(si_udc_wait);
		sir->udc_rdata = UDC_CMD_RESET;;
		DELAY(si_udc_wait);
	} else {
		SET_DMA_COUNT(sir, 0);
		sir->bcr = sir->bcrh = 0;
	}

	/* clear FIFO */
	sir->csr &= ~SI_CSR_FIFO_RES;
	sir->csr |= SI_CSR_FIFO_RES;
	un->un_saved_cmd.saved_cdb = c->c_cdb;
	un->un_saved_cmd.saved_scb = c->c_scb;

	/* DPRINTF("si_disconnect:  done\n"); */
	return (OK);
}


/*
 * Complete reselection phase and reconnect to target.
 *
 * Return OK if sucessful, FAIL if not.
 *
 * NOTE: this routine cannot use si_getdata to get identify msg
 * from reconnecting target due to sun3/50 scsi interface. The bcr
 * must be setup before the target changes scsi bus to data phase
 * if the command being reconnected involves dma (which we do not
 * know until we get the identify msg). Thus we cannot acknowledge
 * the identify msg until some setup of the host adaptor registers 
 * is done.
 */
si_reconnect(c, target, lun)
	register struct scsi_ctlr *c;
	register u_int target;
	register u_int lun;
{
	register volatile struct scsi_si_reg *sir;
	register struct buf *dp;
	register struct buf *pdp;
	register struct scsi_unit *un;

	DPRINTF("si_reconnect\n");
	(int)sir = c->c_reg;

	/* search disconnect queue for reconnecting task */
	/* DPRINTF2("si_reconnect:  target %d lun %d\n", target, lun); */
	DPRINTF("  disconnect que:\n");
	for (dp = c->c_disqh, pdp = NULL; dp; pdp = dp, dp = dp->b_forw) {
		un = (struct scsi_unit *)dp->b_un.b_addr;
		DPRINTF1("\tdp = 0x%x  ---  ", dp);
		DPRINTF2("target= %d,  lun= %d\n", un->un_target, un->un_lun);
		if ((un->un_target == target)  &&  (un->un_lun == lun))
			break;
	}

	if (dp == NULL) {
		printf("si%d:  si_reconnect: can't find dis unit: target %d lun %d\n",
			SINUM(c), target, lun);
		/* dump out disconnnect queue */
		printf("  disconnect queue:\n");
		for (dp = c->c_disqh,pdp = NULL; dp; pdp = dp,dp = dp->b_forw) {
			un = (struct scsi_unit *)dp->b_un.b_addr;
			printf("\tdp = 0x%x  ---  target = %d,  lun = %d\n",
				dp, un->un_target, un->un_lun == lun);
		}

		/*
		 * If we got here, we're probably in deep yogurt.
		 * We should reset, but instead we'll pass the buck.
		 */
		SI_VME_OK(c, sir, "si_reconnect: dp == NULL");
		return (FAIL);
	}

	/* disable other reconnection attempts */
	SI_VME_OK(c, sir, "si_reconnect: ser = 0");

	/* remove entity from disconnect queue */
	if (dp == c->c_disqh)
		c->c_disqh = dp->b_forw;
	else
		pdp->b_forw = dp->b_forw;

	if (dp == c->c_disqt)
		c->c_disqt = pdp;
	dp->b_forw = NULL;

	/* requeue at front of controller queue */
	if (un->un_mc->mc_tab.b_actf == NULL) {
		un->un_mc->mc_tab.b_actf = dp;
		un->un_mc->mc_tab.b_actl = dp;
	} else {
		dp->b_forw = un->un_mc->mc_tab.b_actf;
		un->un_mc->mc_tab.b_actf = dp;
	}
	un->un_mc->mc_tab.b_active = 1;
	c->c_un = un;

	c->c_cdb = un->un_saved_cmd.saved_cdb;
	c->c_scb = un->un_saved_cmd.saved_scb;

	/* restart disconnect activity */
	SCSI_RECON_TRACE('r', c, 0, 0, 0); 
	if (un->un_dma_curdir != SI_NO_DATA) {
		/* restore mainbus resource allocation info */
		un->un_mc->mc_mbinfo = un->un_baddr;

		/* reset udc */
		if (IS_ONBOARD(c)) {
			DELAY(si_udc_wait);
			sir->udc_raddr = UDC_ADR_COMMAND;
			DELAY(si_udc_wait);
			sir->udc_rdata = UDC_CMD_RESET;;
			DELAY(si_udc_wait);
		}

		/* do initial dma setup */
		sir->csr &= ~SI_CSR_FIFO_RES;
		sir->csr |= SI_CSR_FIFO_RES;

		if (un->un_dma_curdir == SI_RECV_DATA)
			sir->csr &= ~SI_CSR_SEND;
		else
			sir->csr |= SI_CSR_SEND;

		/*
		 * New: we set up everything we can here, rather
		 * than wait until data phase.
		 */
		if (IS_ONBOARD(c)) {
			sir->bcr = un->un_dma_curcnt;
			si_ob_dma_setup(c, un);
		} else {
			SET_DMA_COUNT(sir, 0);
			sir->bcr = sir->bcrh = 0;
			sir->csr &= ~SI_CSR_DMA_EN;
			si_vme_dma_setup(c, un);
		}

#ifdef	SCSI_DEBUG
		if (scsi_dis_debug) {
		    printf("si_reconnect:  addr= 0x%x  count= 0x%x  bcr= 0x%x",
			  un->un_dma_curaddr, un->un_dma_curcnt, sir->bcr); 
		    printf("  sr= 0x%x  baddr= 0x%x\n", sir->csr, un->un_baddr);
		}
#endif	SCSI_DEBUG
	}

	/* we can finally acknowledge identify message */
	SBC_WR.icr = SBC_ICR_ACK;

	if (si_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ,
	    SI_WAIT_COUNT, 0) != OK) {
		printf("si%d:  si_reconnect: REQ not INactive\n", SINUM(c));
		return (FAIL);
	}
	SBC_WR.icr = 0;				/* clear ack */
	return (OK);
}



/*
 * Remove timed-out I/O request and report error to
 * it's interrupt handler.
 * Return OK if sucessful, FAIL if not.
 */
si_deque(c, un)
	register struct scsi_ctlr *c;
	register struct scsi_unit *un;
{
	register volatile struct scsi_si_reg *sir;
	register u_int target;
	register u_int lun;
	register struct buf *bp;
	register struct buf *pbp;
	int s;

	DPRINTF("si_deque:\n");
	(int)sir = c->c_reg;

	/* Lock out the rest of si till we've finished the dirty work. */
	target = un->un_target;
	lun = un->un_lun;
	si_print_state(sir, c);
	s = splx(pritospl(un->un_mc->mc_intpri));
	un = c->c_un;			/* get current unit */

	/*
	 * If current SCSI I/O request is the one that timed out. Kill it.
	 */
	if ((int)un != NULL  &&
	    un->un_mc->mc_tab.b_active != 0  &&
	    un->un_target == target  &&
	    un->un_lun == lun) {
		EPRINTF("si_deque:  failed request at top of que\n");
		(*un->un_ss->ss_intr)(c, un->un_dma_count, SE_TIMEOUT);
		(void) splx(s);
		return(OK);
	}

	/* Search disconnect que for reconnecting task */
	/* DPRINTF2("si_deque:  searching for target %d,  lun %d\n  que:\n",
	 *		target, lun);
	 */
	for (bp = c->c_disqh, pbp = NULL; bp; pbp = bp, bp = bp->b_forw) {
		un = (struct scsi_unit *)bp->b_un.b_addr;
		DPRINTF1("\tbp= 0x%x  ---  ", bp);
		DPRINTF2("target= %d,  lun= %d\n", un->un_target, un->un_lun);
		if ((un->un_target == target)  &&  (un->un_lun == lun))
			break;
	}

	/* Failed to find entry, dump out disconnnect queue */
	if (bp == NULL) {
		printf("si_deque:  can't find: target %d, lun %d\n  que:\n",
			target, lun);
		for (bp = c->c_disqh,pbp = NULL; bp; pbp = bp,bp = bp->b_forw) {
			un = (struct scsi_unit *)bp->b_un.b_addr;
			printf("\tbp = 0x%x  ---  target = %d,  lun = %d\n",
				bp, un->un_target, un->un_lun == lun);
		}
		EPRINTF("si_deque:  entry not found\n");
		(void) splx(s);
		return(FAIL);
	}

	/* Remove entity from disconnect que */
	/* DPRINTF2("si_deque:  bp= 0x%x,  pbp= 0x%x\n", bp, pbp); */
	if (bp == c->c_disqh)
		c->c_disqh = bp->b_forw;
	else
		pbp->b_forw = bp->b_forw;

	if (bp == c->c_disqt) {
		c->c_disqt = pbp;
	}
	bp->b_forw = NULL;

	/* Requeue at front of controller queue */
	if (un->un_mc->mc_tab.b_actf == NULL) {
		EPRINTF("si_deque:  reactivating request\n");
		if (un->un_mc->mc_tab.b_active != 0) {
			EPRINTF("si_deque:  we have a reactivate problem\n");
		}
		un->un_mc->mc_tab.b_actf = bp;
		un->un_mc->mc_tab.b_actl = bp;
		un->un_mc->mc_tab.b_active = 1;
		c->c_un = un;
		(*un->un_ss->ss_intr)(c, un->un_dma_count, SE_TIMEOUT);
	} else {
		EPRINTF("si_deque:  can't reactive request\n");
		si_reset(c, PRINT_MSG);
	}
	(void) splx(s);
	return (OK);
}



/*
 * No current activity for the scsi bus. May need to flush some
 * disconnected tasks if a scsi bus reset occurred before the
 * target reconnected, since a scsi bus reset causes targets to 
 * "forget" about any disconnected activity.
 * Also, enable reconnect attempts.
 */
si_idle(c)
	register struct scsi_ctlr *c;
{
	register volatile struct scsi_si_reg *sir;
	register struct buf *dp;
	register struct scsi_unit *un;
	register int resid;

	DPRINTF("si_idle:\n");
	(int)sir = c->c_reg;

	if (c->c_flags & SCSI_FLUSHING) {
		EPRINTF1("si_idle:  flushing, flags 0x%x\n", c->c_flags);
		return;
	}

	/* flush disconnect tasks if a reconnect will never occur */
	if (c->c_flags & SCSI_FLUSH_DISQ) {
		EPRINTF("si_idle:  flushing disconnect que\n"); 

		/* now in process of flushing tasks */
		c->c_flags &= ~SCSI_FLUSH_DISQ;
		c->c_flags |= SCSI_FLUSHING;

		for (dp = c->c_disqh; dp  &&  c->c_flush; dp = c->c_disqh) {
			/* keep track of last task to flush */
			if (c->c_flush == c->c_disqh) 
				c->c_flush = NULL;

			/* remove tasks from disconnect queue */
			un = (struct scsi_unit *)dp->b_un.b_addr;
			c->c_disqh = dp->b_forw;
			dp->b_forw = NULL;

			/* requeue on controller queue */
			siustart(un);
			un->un_mc->mc_tab.b_active = 1;
			c->c_un = un;

			/* inform device routines of error */
			if (un->un_dma_curdir != SI_NO_DATA) {
				un->un_mc->mc_mbinfo = un->un_baddr;
				resid = un->un_dma_curcnt;
			} else {
				resid = 0;
			}
			(*un->un_ss->ss_intr)(c, resid, SE_FATAL);
			si_off(c, un);		/* unit is going offline */
		}
		if (c->c_disqh == NULL) {
			c->c_disqt = NULL;
		}
		c->c_flags &= ~SCSI_FLUSHING;
		return;
	}

	/* enable reconnect attempts */
	if (IS_VME(c)) {
		sir->csr &= ~SI_CSR_DMA_EN;	/* turn off before SBC access */
		SET_DMA_COUNT(sir, 0);
		sir->bcrh = sir->bcr = 0;
		sir->csr &= ~SI_CSR_SEND;
		sir->csr |= SI_CSR_DMA_EN;
		/* DPRINTF("si_idle:  DMA ENABLED\n"); */
	}
}


/*
 * Get status bytes from scsi bus.
 * Returns number of status bytes read if no error.
 * If error, returns -1.
 * If scsi bus error, returns 0.
 */
si_getstatus(un)
	register struct scsi_unit *un;
{
	register struct scsi_ctlr *c = un->un_c;
	register volatile struct scsi_si_reg *sir;
	register u_char *cp;
	register int i;
	register u_char msg;

	DPRINTF("si_getstatus:\n");

	(int)sir = c->c_reg;

	SI_VME_OK(c, sir, "si_getstatus:");

	if (si_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ,
	    SI_LONG_WAIT, 1) != OK) {
		printf("si%d:  si_getstatus: REQ inactive\n", SINUM(c));
		si_print_state(sir, c);
		return (0);
	}

	if (si_wait_phase(sir, PHASE_STATUS) != OK) {
		printf("si%d:  si_getstatus: no STATUS phase\n", SINUM(c));
		si_print_state(sir, c);
		return (0);
	}
	i = si_status_bytes(un);

#ifdef	SCSI_DEBUG
	if (scsi_debug > 2) {
		int x;
		register u_char *p = (u_char *)&c->c_scb;

		printf("si_getstatus:  %d status bytes", i);
		for (x = 0; x < i; x++)
			printf("  %x", *p++);
		printf("\n");
	}
#endif	SCSI_DEBUG

	if (si_wait_phase(sir, PHASE_MSG_IN) != OK) {
		printf("si%d:  si_getstatus: no MSG_IN phase\n", SINUM(c));
		si_print_state(sir, c);
		return (0);
	}

	SI_VME_OK(c, sir, "si_getstatus: msg_in");
	msg = si_getdata(c, PHASE_MSG_IN);
	if (msg != SC_COMMAND_COMPLETE) {
		EPRINTF1("si_getstatus:  bogus msg_in 0x%x\n", msg);
	}
	SBC_WR.tcr = TCR_UNSPECIFIED;

	/*
	 * Check status for error condition, return -1 if error.
	 * Otherwise, return positive byte count for no error.
	 */
	cp = (u_char *) &c->c_scb;
	if (cp[0] & SCB_STATUS_MASK)
		return (-1);	/* retryable */

	return (i);	 	/* no error */
}


/*
 * Get status bytes from scsi bus.
 * Returns number of status bytes read.
 */
static
si_status_bytes(un)
	struct scsi_unit *un;
{
	register struct scsi_ctlr *c = un->un_c;
	register u_char *cp = (u_char *)&c->c_scb;
	register int i;
	register int b;

	DPRINTF("si_status_bytes:\n");
	/* get all the status byte(s) */
	for (i = 0;;) {

		b = si_getdata(c, PHASE_STATUS);

		if (b < 0)
			break;
		if (i < STATUS_LEN)
			cp[i++] = b;
	}

#ifdef	SCSI_DEBUG
	/* set status to reflect whether SCSI operation was ok. */
	if (cp[0] & SCB_STATUS_MASK)
		DPRINTF1("si_status_bytes:  cmd failed, scb= 0x%x\n", cp[0]);
#endif	SCSI_DEBUG

	return (i);
}


/* 
 * Wait for a scsi dma request to complete.
 * Disconnects were disabled in si_cmd when polling for command completion.
 * Called by drivers in order to poll on command completion.
 */
si_cmdwait(c)
	register struct scsi_ctlr *c;
{
	register volatile struct scsi_si_reg *sir;
	register struct scsi_unit *un = c->c_un;
	register int ret_val;

	DPRINTF("si_cmdwait:\n");

	(int)sir = c->c_reg;

	/* wait for dma transfer to complete */
	if (si_wait((u_short *)&sir->csr, SI_CSR_DMA_ACTIVE, 0) != OK) {
		printf("si%d:  si_cmdwait: DMA still ACTIVE\n", SINUM(c));
		si_reset(c, PRINT_MSG);
		return (SCSI_FAIL);
	}

	/* if command does not involve dma activity, then we are finished */
	if (un->un_dma_curdir == SI_NO_DATA) {
		return (OK);
	}

	/* wait for indication of dma completion */
	if (si_wait((u_short *)&sir->csr, 
	    SI_CSR_SBC_IP | SI_CSR_DMA_IP | SI_CSR_DMA_CONFLICT, 1) != OK) {
		printf("si%d:  si_cmdwait: dma never completed\n", SINUM(c));
		si_reset(c, PRINT_MSG);
		ret_val = SCSI_FAIL;
		goto SI_CMDWAIT_EXIT;
	}

	/* 
	 * For vme host adaptor interface, must disable dma before
	 * accessing any registers other than the csr or a dma
	 * conflict error will occur.
	 */
	if (IS_VME(c))
		sir->csr &= ~SI_CSR_DMA_EN;

	/* make sure dma completely complete */
	if ((sir->csr & SI_CSR_SBC_IP) == 0) {
		if (sir->csr & SI_CSR_DMA_BUS_ERR) {
			printf("si%d:  si_cmdwait: bus error during dma\n",
				SINUM(c));
		} else if (sir->csr & SI_CSR_DMA_CONFLICT) {
			printf("si%d:  si_cmdwait: reg access during dma\n",
				SINUM(c));
		} else {
			printf("si%d:  si_cmdwait: dma in progress\n",
				SINUM(c));
		}
		si_reset(c, PRINT_MSG);
		ret_val = SCSI_FAIL;
		goto SI_CMDWAIT_EXIT;
	}

	/* handle special dma recv situations */
	if ((un->un_dma_curdir == SI_RECV_DATA)  &&  (si_dma_recv(c) != OK)) {
		printf("si%d:  si_cmdwait: special DMA failure\n", SINUM(c));
		si_reset(c, PRINT_MSG);
		ret_val = SCSI_FAIL;
		goto SI_CMDWAIT_EXIT;
	}

	/* ack sbc interrupt and cleanup */
	junk = SBC_RD.clr;
	si_dma_cleanup(c);
	ret_val = OK;

SI_CMDWAIT_EXIT:
	if (sir->csr & SI_CSR_SBC_IP) {
		junk = SBC_RD.clr;	/* clear sbc int */
	}

	if (IS_VME(c))
		sir->csr &= ~SI_CSR_DMA_EN;	/* turn it off to be sure */
	return (ret_val);
}


/*
 * Wait for a condition to be (de)asserted on the scsi bus.
 * Returns OK for successful.  Otherwise, returns
 * FAIL.
 */
static
si_sbc_wait(reg, cond, wait_count, set)
	register volatile char *reg;
	register u_char cond;
	register int wait_count;
	register int set;
{
	register int i;
	register u_char regval;

	DPRINTF("si_scb_wait\n");
	for (i = 0; i < wait_count; i++) {
		regval = *reg;
		if ((set == 1)  &&  (regval & cond)) {
			return (OK);
		}
		if ((set == 0)  &&  !(regval & cond)) {
			return (OK);
		} 
		DELAY(10);
	}
	DPRINTF("si_sbc_wait:  timeout\n");
	return (FAIL);
}


/*
 * Wait for a condition to be (de)asserted.
 * Used for monitor DMA controller.
 * Returns OK for successful.  Otherwise,
 * returns FAIL.
 */
static
si_wait(reg, cond, set)
	register volatile u_short *reg;
	register u_short cond;
	register int set;
{
	register int i;
	register u_short regval;

	DPRINTF("si_wait\n");
	for (i = 0; i < SI_WAIT_COUNT; i++) {
		regval = *reg;
		if ((set == 1)  &&  (regval & cond)) {
			return (OK);
		}
		if ((set == 0)  &&  !(regval & cond)) {
			return (OK);
		} 
		DELAY(10);
	}
	return (FAIL);
}


/*
 * Wait for a phase on the SCSI bus.
 * Returns OK for successful.  Otherwise,
 * returns FAIL.
 */
static
si_wait_phase(sir, phase)
	register volatile struct scsi_si_reg *sir;
	register u_char phase;
{
	register int i;

	DPRINTF2("si_wait_phase:  %s phase (0x%x)\n",si_str_phase(phase),phase);
	for (i = 0; i < SI_WAIT_COUNT; i++) {
		if ((SBC_RD.cbsr & CBSR_PHASE_BITS) == phase)
			return (OK);
		DELAY(10);
	}
	return (FAIL);
}


/*
 * Put data onto the scsi bus.
 * Returns OK if successful, FAIL otherwise.
 */
static
si_putdata(c, phase, data, num)
	register struct scsi_ctlr *c;
	register u_short phase;
	register u_char *data;
	register int num;
{
	register volatile struct scsi_si_reg *sir;
	register int i;
	DPRINTF("si_putdata\n");

	(int)sir = c->c_reg;

	DPRINTF2("si_putdata:  %s phase (0x%x) ", si_str_phase(phase), phase);
	/* DPRINTF1("num %d\n", num); */
	SI_VME_OK(c, sir, "si_putdata");

	/* 
	 * Set up tcr so we can transmit data.
	 */
	SBC_WR.tcr = phase >> 2;

	/* put all desired bytes onto scsi bus */
	for (i = 0; i < num; i++ ) {

		/* wait for target to request a byte */
		SBC_WR.icr = 0;			/* clear ack */
		if (si_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ, 
		    SI_WAIT_COUNT, 1) != OK) {
			printf("si%d:  putdata, REQ not active\n", SINUM(c));
			return (HARD_FAIL);
		}

		/* load data */
		/* DPRINTF2("putting byte # %d, = 0x%x\n", i, *data); */
		SBC_WR.odr = *data++;
		SBC_WR.icr = SBC_ICR_DATA;

		/* complete req/ack handshake */
		SBC_WR.icr |= SBC_ICR_ACK;
		if (si_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ,
		    SI_WAIT_COUNT, 0) != OK) {
			printf("si%d:  putdata, req not INactive\n", SINUM(c));
			return (HARD_FAIL);
		}
	}
	SBC_WR.tcr = TCR_UNSPECIFIED;
	junk = SBC_RD.clr;		/* clear int */
	SBC_WR.icr = 0;			/* clear ack */
	return (OK);
}


/*
 * Put command onto the scsi bus.
 * Returns OK if successful, FAIL otherwise.
 */
static
si_putcmd(c, data, num, want_intr)
	register struct scsi_ctlr *c;
	register u_char *data;
	register u_char num;
	register int want_intr;
{
	register volatile struct scsi_si_reg *sir;
	register u_char i;

	DPRINTF("si_putcmd\n");

	(int)sir = c->c_reg;

	SI_VME_OK(c, sir, "si_putcmd");
	SBC_WR.tcr = TCR_COMMAND;

	/* put all desired bytes onto scsi bus */
	for (i = 0; i < num; i++ ) {

		SBC_WR.icr = SBC_ICR_DATA;	/* clear ack, enable data bus */

		/* wait for target to request a byte */
		if (si_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ,
		    SI_WAIT_COUNT, 1) != OK) {
			printf("si%d:  si_putcmd: REQ not active\n", SINUM(c));
			return (FAIL);
		}

		/* load data */
		DPRINTF2("putting byte # %d, = 0x%x\n", i, *data);
		SBC_WR.odr = *data++;

		/* complete req/ack handshake */
		SBC_WR.icr |= SBC_ICR_ACK;
		if (si_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ, 
		    SI_WAIT_COUNT, 0) != OK) {
			printf("si%d:  si_putcmd: req not INactive\n", SINUM(c));
			return (FAIL);
		}
	}
	junk = SBC_RD.clr;			/* clear int */
	if (want_intr) {

		/* CRITICAL CODE SECTION DON'T TOUCH */
		SBC_WR.tcr = TCR_UNSPECIFIED;
		SBC_WR.mr |= SBC_MR_DMA;
		SBC_WR.icr = 0;			/* ack last byte */

	} else {
		SBC_WR.icr = 0;			/* clear ack */
	}
	return (OK);
}


/*
 * Get data from the scsi bus.
 * Returns a single byte of data, -1 if unsuccessful.
 */
static
si_getdata(c, phase)
	register struct scsi_ctlr *c;
	register u_short phase;
{
	register volatile struct scsi_si_reg *sir;
	register u_char data;
	register u_char icr;

	DPRINTF("si_getdata\n");

	(int)sir = c->c_reg;

	DPRINTF2("si_getdata: %s phase (0x%x)",si_str_phase(phase),phase);
	SI_VME_OK(c, sir, "si_getdata");

	/* wait for target request */
	if (si_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ, 
	    SI_WAIT_COUNT, 1) != OK) {
		printf("si%d:  getdata, REQ not active, cbsr 0x%x\n",
			SINUM(c), SBC_RD.cbsr);
		si_print_state(sir, c);
		return (-1);
	}

	if ((SBC_RD.cbsr & CBSR_PHASE_BITS) != phase) {
		/* not the phase we expected */
		DPRINTF1("si_getdata:  unexpected phase, expecting %s\n",
			si_str_phase(phase));
		return (-1);
	}


	/* grab data and complete req/ack handshake */
	data = SBC_RD.cdr;
	icr = SBC_WR.icr;
	DPRINTF1("  icr= %x  ", icr);
	SBC_WR.icr = icr | SBC_ICR_ACK;

	if (si_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ, 
	    SI_WAIT_COUNT, 0) != OK) {
		printf("si%d:  getdata, REQ not inactive\n", SINUM(c));
		return (-1);
	}

	DPRINTF1("  data= 0x%x\n", data);
	if ((phase == PHASE_MSG_IN)  && 
	    ((data == SC_COMMAND_COMPLETE)  ||  (data == SC_DISCONNECT))) {

		/* CRITICAL CODE SECTION DON'T TOUCH */
		SBC_WR.tcr = TCR_UNSPECIFIED;
		SBC_WR.mr &= ~SBC_MR_DMA;	/* clear phase int */
		junk = SBC_RD.clr;		/* clear int */
		SBC_WR.icr = icr;		/* clear ack */
	} else {
		SBC_WR.icr = icr;		/* clear ack */
	}
	return (data);
}


/*
 * Reset SCSI control logic and bus.
 */
si_reset(c, msg_enable)
	register struct scsi_ctlr *c;
	register int msg_enable;
{
	register volatile struct scsi_si_reg *sir;
	DPRINTF("si_reset\n");

	(int)sir = c->c_reg;

	if (msg_enable) {
		printf("si%d:  resetting scsi bus\n", SINUM(c));
		si_print_state(sir, c);
		DEBUG_DELAY(10000000);
	}

	/* reset scsi control logic */
	sir->bcr = 0;
	sir->csr = 0;
	DELAY(10);
	sir->csr = SI_CSR_SCSI_RES | SI_CSR_FIFO_RES;

	if (IS_VME(c)) {
		SET_DMA_ADDR(sir, 0);
		SET_DMA_COUNT(sir, 0);
	}

	/* issue scsi bus reset (make sure interrupts from sbc are disabled) */
	SBC_WR.icr = SBC_ICR_RST;
	DELAY(1000);
	SBC_WR.icr = 0;				/* clear reset */

	/* give reset scsi devices time to recover (> 2 Sec) */
	DELAY(SI_RESET_DELAY);
	junk = SBC_RD.clr;

	/* Disable sbc interrupts.  Reconnects will be enabled by si_cmd. */
	SBC_WR.mr &= ~SBC_MR_DMA;	/* clear phase int */
	sir->csr |= SI_CSR_INTR_EN;

	/* disconnect queue needs to be flushed */
	if (c->c_disqh != NULL) {
		c->c_flags |= SCSI_FLUSH_DISQ;
		c->c_flush = c->c_disqt;
		si_idle(c);
	}
}


/*
 * Return residual count for a dma.
 */
si_dmacnt(c)
	register struct scsi_ctlr *c;
{
	register volatile struct scsi_si_reg *sir;
	(int)sir = c->c_reg;

	if (IS_ONBOARD(c)) {
		return (sir->bcr);
	} else {
		return ( ((sir->bcrh) << 16) | (sir->bcr) );
	}
}

#endif	NSI > 0
