/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	sw.c,v $
 * Revision 2.5  89/07/11  17:08:16  jjc
 * 	Modified for Mach.
 * 	[89/06/30            jjc]
 * 
 * Revision 2.4  89/03/09  21:47:13  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:56:19  gm0w
 * 	Changes for cleanup.
 * 
 */
/* @(#)sw.c       1.14 87/11/05 Copyr 1987 Sun Micro */
#include <sw.h>
#if	NSW > 0

#ifndef	lint
static  char sccsid[] = "@(#)sw.c       1.14 87/11/05 Copyr 1987 Sun Micro";
#endif	lint

/* #define SCSI_DEBUG			/* turn on debugging code */
#define REL4				/* enable release 4.00 mods */

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
#else	MACH
#include <machine/pte.h>
#endif	MACH
#include <machine/psl.h>
#include <machine/mmu.h>
#include <machine/cpu.h>
#include <machine/scb.h>
#include <machine/enable.h>

#include <sun/dklabel.h>
#include <sun/dkio.h>

#include <sundev/mbvar.h>
#include <sundev/swreg.h>
#include <sundev/scsi.h>

#else	REL4
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dk.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/user.h>
#include <sys/dir.h>
#include <sys/map.h>
#include <sys/vmmac.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <sys/dkbad.h>

#ifdef	MACH
#else	MACH
#include <machine/pte.h>
#endif	MACH
#include <machine/psl.h>
#include <machine/mmu.h>
#include <machine/cpu.h>
#include <machine/scb.h>
#include <machine/enable.h>

#include <sun/dklabel.h>
#include <sun/dkio.h>

#include <sundev/mbvar.h>
#include <sundev/swreg.h>
#include <sundev/scsi.h>
#endif	REL4

#ifdef	MACH
/* arbitrate retry count */
#define SI_NUM_RETRIES		10
#endif	MACH

/* Shorthand, to make the code look a bit cleaner. */
#define SWNUM(sw)	(sw - swctlrs)
#define SWUNIT(dev)     (minor(dev) & 0x03)

int	swprobe(), swslave(), swattach(), swgo(), sw_done(), swpoll();
int	swustart(), swstart(), sw_getstatus(), sw_reconnect(), sw_deque();
int	sw_off(), sw_cmd(), sw_cmdwait(), sw_reset(), sw_dmacnt();

struct	scsi_ctlr swctlrs[NSW];			/* per controller structs */
struct	mb_ctlr *swinfo[NSW];
extern struct mb_device *sdinfo[];
struct	mb_driver swdriver = {
	swprobe, swslave, swattach, swgo, sw_done, swpoll,
	sizeof (struct scsi_sw_reg), "sd", sdinfo, "sw", swinfo, MDR_BIODMA,
};

/* routines available to devices specific portion of scsi driver */
struct scsi_ctlr_subr swsubr = {
	swustart, swstart, sw_done, sw_cmd, sw_getstatus, sw_cmdwait,
	sw_off, sw_reset, sw_dmacnt, swgo, sw_deque,
};

extern int scsi_ntype;
extern short scsi_disre_enable;		/* enable disconnect/reconnects */
extern struct scsi_unit_subr scsi_unit_subr[];


/*
 * Patchable delays for debugging.
 */
static u_char junk;
int sw_udc_wait = SI_UDC_WAIT;
int sw_arbitration_delay = SI_ARBITRATION_DELAY;
int sw_bus_clear_delay = SI_BUS_CLEAR_DELAY;
int sw_bus_settle_delay = SI_BUS_SETTLE_DELAY;

/*
 * possible return values from sw_arb_sel, sw_cmd, 
 * sw_putdata, sw_putcmd, and sw_reconnect.
 */
#define OK		0	/* successful */ 
#define FAIL		1	/* failed maybe recoverable */ 
#define HARD_FAIL	2	/* failed not recoverable */ 
#define SCSI_FAIL	3	/* failed due to scsi bus fault */ 
#define RESEL_FAIL	4	/* failed due to target reselection */ 

/* possible return values from sw_process_complete_msg() */
#define CMD_CMPLT_DONE	0	/* cmd processing done */ 
#define CMD_CMPLT_WAIT	1	/* cmd processing waiting
				 * on sense cmd complete
				 */
/*
 * possible argument values for sw_reset
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

int sw_dis_debug = 0;	/* disconnect debug info */
u_int sw_winner  = 0;	/* # of times we had an intr at end of swintr */
u_int sw_loser   = 0;	/* # of times we didn't have an intr at end */

#define SW_WIN		sw_winner++
#define SW_LOSE		sw_loser++

/* Check for possible illegal SCSI-3 register access. */
#define SW_VME_OK(c, swr, str)	{\
	if ((IS_VME(c))  &&  (swr->csr & SI_CSR_DMA_EN)) \
		printf("sw%d:  reg access during dma <%s>, csr 0x%x\n", \
			SWNUM(c), str, swr);\
}
#define SW_DMA_OK(c, swr, str)  {\
	if (IS_VME(c)) { \
		if (swr->csr & SI_CSR_DMA_EN) \
			printf("%s: DMA DISABLED\n", str); \
		if (swr->csr & SI_CSR_DMA_CONFLICT) { \
			printf("%s: invalid reg access during dma\n", str); \
			DELAY(50000000); \
		} \
		swr->csr &= ~SI_CSR_DMA_EN; \
	} \
}
#define SCSI_TRACE(where, swr, un) \
	if (scsi_debug)		scsi_trace(where, swr, un)
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
#define SW_WIN
#define SW_LOSE
#define SW_VME_OK(c, swr, str)
#define SW_DMA_OK(c, swr, str)
#define DEBUG_DELAY(cnt)
#define DPRINTF(str) 
#define DPRINTF1(str, arg2) 
#define DPRINTF2(str, arg1, arg2) 
#define EPRINTF(str) 
#define EPRINTF1(str, arg2) 
#define EPRINTF2(str, arg1, arg2) 
#define SCSI_TRACE(where, swr, un)
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
	u_long csr;
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
int sw_stbi = 0;
struct trace_buf sw_trace_buf[TRBUF_LEN];

/* disconnect/reconnect trace buffer */
int sw_strbi = 0;
struct disre_trace_buf sw_recon_trace_buf[TRBUF_LEN];

static
scsi_trace(where, swr, un)
	register char where;
	register struct scsi_sw_reg *swr;
	struct scsi_unit *un;
{
	register u_char *r = &(SBC_RD.cdr);
	register u_int i;
	register struct trace_buf *tb = &(sw_trace_buf[sw_stbi]);
#ifdef	lint
	un= un;
#endif	lint

	tb->wh[0] = tb->wh[1] = where;
	for (i = 0; i < 6; i++)
		tb->r[i] = *r++;
	tb->csr = swr->csr;
	tb->dma_addr  = GET_DMA_ADDR(swr);
	tb->dma_count = GET_DMA_COUNT(swr);

	if (++sw_stbi >= TRBUF_LEN)
		sw_stbi = 0;

	sw_trace_buf[sw_stbi].wh[0] = '?';		/* mark end */
}


static
scsi_recon_trace(where, c, data0, data1, data2)
	char where;
	register struct scsi_ctlr *c;
	register int data0, data1, data2;
{
	register struct scsi_unit *un = c->c_un;
	register struct disre_trace_buf *tb = 
		 &(sw_recon_trace_buf[sw_strbi]);

	tb->wh[0] = tb->wh[1] = where;
	tb->cdb = c->c_cdb;
	tb->target = un->un_target;
	tb->lun = un->un_lun;
	tb->data[0] = data0;
	tb->data[1] = data1;
	tb->data[2] = data2;

	if (++sw_strbi >= TRBUF_LEN)
		sw_strbi = 0;

	sw_recon_trace_buf[sw_strbi].wh[0] = '?';	/* mark end */
}
#endif	SCSI_DEBUG

/*
 * Print out the cdb.
 */
static
sw_print_cdb(c)
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
 * returns string corresponding to the phase
 */
static char *
sw_str_phase(phase)
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
 * returns string corresponding to the last phase.
 * Note, also encoded are internal messages in
 * addition to the last bus phase.  
 */
static char *
sw_str_lastphase(phase)
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
		return(sw_str_phase(phase));
	}
}


/*
 * print out the current hardware state
 */
static
sw_print_state(swr, c)
	register struct scsi_sw_reg *swr;
	register struct scsi_ctlr *c;
{
	register struct scsi_unit *un = c->c_un;
	register short flag = 0;

	if ((swr->csr & SI_CSR_DMA_EN)) {
		swr->csr &= ~SI_CSR_DMA_EN;
		flag = 1;
	}


	printf("\tlast phase= 0x%x (%s)\n",
		c->c_last_phase, sw_str_lastphase(c->c_last_phase));
	printf("\tcsr= 0x%x  bcr= %d  tcr= 0x%x\n",
			swr->csr, swr->bcr, SBC_RD.tcr);
	printf("\tcbsr= 0x%x (%s)  cdr= 0x%x  mr= 0x%x  bsr= 0x%x\n",
			SBC_RD.cbsr, sw_str_phase(SBC_RD.cbsr), SBC_RD.cdr,
			SBC_RD.mr, SBC_RD.bsr);
	if (flag) {
		swr->csr |= SI_CSR_DMA_EN;
	}
#ifdef	SCSI_DEBUG
	printf("\tdriver wins= %d  loses= %d\n", sw_winner, sw_loser);
#endif	SCSI_DEBUG

	if (un != NULL) {
		printf("\ttarget= %d, lun= %d    ", un->un_target, un->un_lun);
		printf("DMA addr= 0x%x  count= %d (%d)\n",
			   un->un_dma_curaddr, un->un_dma_curcnt,
			   un->un_dma_count);
		printf("\tcdb=  ");
		sw_print_cdb(c);
	}
}



/*
 * Determine existence of SCSI host adapter.
 * Returns 0 for failure, size of sw data structure if ok.
 */
swprobe(swr, ctlr)
	register struct scsi_sw_reg *swr;
	register int ctlr;
{
	register struct scsi_ctlr *c;
	int val;
	c = &swctlrs[ctlr];

	/* 
	 * Check for sbc - NCR 5380 Scsi Bus Ctlr chip.
	 * sbc is common to sun3/50 onboard scsi and vme
	 * scsi board.
	 */
	if (peekc((char *)&swr->sbc_rreg.cbsr) == -1) {
		return (0);
	}

	/*
	 * Determine whether the host adaptor interface is onboard or vme.
	 */
	if (cpu == CPU_SUN4_110) {
		/* probe for 4/110 dma interface */
		if (peekl((u_int *)&swr->dma_addr, &val) == -1) {
			return (0);
		}
		c->c_flags = SCSI_COBRA;
	} 

	/* probe for different scsi host adaptor interfaces */
	EPRINTF2("sw%d:  swprobe: swr= 0x%x,  ", ctlr, (u_int)swr);
	EPRINTF1("c= 0x%x\n", (u_int)c );

	/* init controller information */
	if (scsi_disre_enable) {
		/* DPRINTF("swprobe:  disconnects enabled\n"); */
		c->c_flags |= SCSI_EN_DISCON;
	} else {
		EPRINTF("swprobe:  all disconnects disabled\n");
	}

	c->c_flags |= SCSI_PRESENT;
	c->c_last_phase = PHASE_CMD_CPLT;
	c->c_reg = (int)swr;
	c->c_ss = &swsubr;
	sw_reset(c, NO_MSG);			/* quietly reset the scsi bus */
	return (sizeof (struct scsi_sw_reg));
}


/*
 * See if a slave exists.
 * Since it may exist but be powered off, we always say yes.
 */
/*ARGSUSED*/
swslave(md, swr)
	register struct mb_device *md;
	register struct scsi_sw_reg *swr;
{
	register struct scsi_unit *un;
	register int type;

#ifdef	lint
	swr = swr;
	junk = junk;
#endif	lint

	/*
	 * This kludge allows autoconfig to print out "sd" for
	 * disks and "st" for tapes.  The problem is that there
	 * is only one md_driver for scsi devices.
	 */
	type = TYPE(md->md_flags);
	if (type >= scsi_ntype) {
		panic("swslave:  unknown type in md_flags\n");
	}

	/* link unit to its controller */
	un = (struct scsi_unit *)(*scsi_unit_subr[type].ss_unit_ptr)(md);
	if (un == 0) {
		panic("swslave:  md_flags scsi type not configured\n");
	}
	un->un_c = &swctlrs[md->md_ctlr];
	md->md_driver->mdr_dname = scsi_unit_subr[type].ss_devname;
	return (1);
}


/*
 * Attach device (boot time).
 */
swattach(md)
	register struct mb_device *md;
{
	register int type = TYPE(md->md_flags);
	register struct scsi_ctlr *c = &swctlrs[md->md_ctlr];
	register struct scsi_sw_reg *swr;

	(int)swr = c->c_reg;

	/* DPRINTF("swattach:\n"); */
#ifdef	SCSI_DEBUG
	if ((scsi_disre_enable != 0)  &&  scsi_debug)
		printf("sw%d:  swattach: disconnects disabled\n", SWNUM(c));
#endif	SCSI_DEBUG

	if (type >= scsi_ntype) {
		panic("swattach:  unknown type in md_flags\n");
	}
	(*scsi_unit_subr[type].ss_attach)(md);

	/*
	 * Make sure dma enable bit is off or 
	 * SI_CSR_DMA_CONFLICT will occur when 
	 * the iv_am register is accessed.
	 */
	swr->csr &= ~SI_CSR_DMA_EN;
        return;
}


/*
 * SCSI unit start routine.
 * Called by SCSI device drivers.
 * Does not actually start any I/O - just puts the device
 * on the ready queue for the bus.
 */
swustart(un)
	register struct scsi_unit *un;			/* our unit */
{
	register struct buf *dp;
	register struct mb_ctlr *mc;			/* unit's ctlr */

	/* DPRINTF("swustart:\n"); */
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
swstart(un)
	register struct scsi_unit *un;		/* our unit */
{

	register struct mb_ctlr *mc;		/* unit's ctlr */
	register struct buf *bp, *dp;

	/* DPRINTF("swstart:\n"); */
	mc = un->un_mc;
	dp = mc->mc_tab.b_actf;		  	/* != NULL guaranteed by caller */
	un = (struct scsi_unit *) dp->b_un.b_addr;
	bp = dp->b_actf;
	for (;;) {
		if (bp == NULL) {		/* no more blocks for this device */
			un->un_utab.b_active = 0;
			dp = mc->mc_tab.b_actf = dp->b_forw;
			if (dp == NULL) {	/* no more devices for this ctlr */
				sw_idle(un->un_c);
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
					swgo(mc);
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
swgo(mc)
	register struct mb_ctlr *mc;		/* fire up this mb ctlr */
{
	register struct scsi_unit *un;		/* our scsi unit */
	register struct scsi_ctlr *c;		/* our scsi ctlr */
	register struct buf *bp, *dp;
	register int unit;			/* unit for stat purposes */
	register int err;

	/* DPRINTF("swgo:\n"); */
	c = &swctlrs[mc->mc_ctlr];
	dp = mc->mc_tab.b_actf;

	if (dp == NULL  ||  dp->b_actf == NULL) {
		panic("swgo:  queueing error1\n");
	}

	bp = dp->b_actf;
	un = c->c_un;

	if (dp != &un->un_utab) {
		panic("swgo:  queueing error2\n");
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
	if ((err=sw_cmd(c, un, 1)) != OK) {
		if (err == FAIL) {
			/* DPRINTF("swgo:  sw_cmd FAILED\n"); */
			(*un->un_ss->ss_intr)(c, 0, SE_RETRYABLE);

		} else if (err == HARD_FAIL) {
			EPRINTF("swgo:  sw_cmd hard FAIL\n");
			(*un->un_ss->ss_intr)(c, 0, SE_FATAL);
			sw_off(c, un);
		}
	}
}


/*
 * Handle a polling SCSI bus interrupt.
 */
swpoll()
{
	register struct scsi_ctlr *c;
	register struct scsi_sw_reg *swr;
	register int serviced = 0;

	/* DPRINTF("swpoll:\n"); */
	for (c = swctlrs; c < &swctlrs[NSW]; c++) {
		if ((c->c_flags & SCSI_PRESENT) == 0)
			continue;
		(int)swr = c->c_reg;
		if ((swr->csr & (SI_CSR_SBC_IP | SI_CSR_DMA_IP
			| SI_CSR_DMA_CONFLICT | SI_CSR_DMA_BUS_ERR)) == 0) {
			continue;
		}
		serviced = 1;
		swintr(c);
	}
	return (serviced);
}


/*
 * Clean up queues, free resources, and start next I/O
 * all done after I/O finishes
 * Called by mbdone after moving read data from Mainbus
 */
sw_done(mc)
	register struct mb_ctlr *mc;
{
	register struct buf *bp, *dp;
	register struct scsi_unit *un;
	register struct scsi_ctlr *c;
	register int err;

	/* DPRINTF("scwdone:\n"); */
	bp = mc->mc_tab.b_actf->b_actf;
	c = &swctlrs[mc->mc_ctlr];
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
		swustart(un);

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
			DPRINTF1("sw_done: doing preempted, tgt= %x\n",
				un->un_target);
			un->un_flags &= ~SC_UNF_PREEMPT;
			c->c_un = un;
			c->c_cdb = un->un_saved_cmd.saved_cdb;
			mc->mc_tab.b_active = 1;
			if (un->un_dma_curdir != SI_NO_DATA) {
				mc->mc_mbinfo = un->un_baddr;
			}
			if ((err=sw_cmd(c, un, 1)) != OK) {
				if (err == FAIL) {
					/* DPRINTF("scwdone:  sw_cmd FAILED\n"); */
					(*un->un_ss->ss_intr)(c, 0, SE_RETRYABLE);

				} else if (err == HARD_FAIL) {
					EPRINTF("sw_done:  sw_cmd hard FAIL\n");
					(*un->un_ss->ss_intr)(c, 0, SE_FATAL);
					sw_off(c, un);
				}
			}
		} else if (un->un_flags & SC_UNF_GET_SENSE) {
			swgo(mc);
		} else {
			swstart(un);
		}
	} else {
		c->c_un = NULL;
		sw_idle(c);
	}
}


/*
 * Bring a unit offline.
 */
/*ARGSUSED*/
sw_off(c, un)
	register struct scsi_ctlr *c;
	register struct scsi_unit *un;
{
	register struct mb_device *md;
	md = un->un_md;

	/*
	 * Be warned, if you take the root device offline,
	 * the system is going to have a heartattack !
	 */
	printf("sw%d:  %s%d, unit offline\n", SWNUM(c),
		scsi_unit_subr[md->md_flags].ss_devname, SWUNIT(un->un_unit));
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
sw_cmd(c, un, intr)
	register struct scsi_ctlr *c;
	register struct scsi_unit *un;
	register int intr;		/* if 0, run cmd to completion
					 *       in polled mode
					 * if 1, allow disconnects
					 *       if enabled and use
					 *       interrupts
					 */
{
	register struct scsi_sw_reg *swr;
	register int err;
	register int i;
	register u_char size;
	u_char id;
	u_char msg;
	int s;

	(int)swr = c->c_reg;

	/* disallow disconnects if waiting for command completion */
	DPRINTF("sw_cmd:\n"); 
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
		printf("sw%d:  illegal odd byte DMA, address= 0x%x\n",
			SWNUM(c), un->un_dma_curaddr);
		return(HARD_FAIL);
	}


#ifdef	SCSI_DEBUG
	/*
	 * Synchronize sw_cmd to swintr operations to prevent
	 * possible lost interrupts.  It does this by waiting
	 * until siintr reaches either a command complete or 
	 * command disconnect state.
	 */
	for (i = 0; i < SI_WAIT_COUNT; i++) {
		if (c->c_last_phase == PHASE_CMD_CPLT  ||
		    c->c_last_phase == PHASE_DISCONNECT)
			break;
		EPRINTF2("sw_cmd:  synchronizing, last phase= 0x%x (%s)\n",
			  c->c_last_phase, sw_str_lastphase(c->c_last_phase));
		DELAY(10);
	}
#endif	SCSI_DEBUG


	/*
	 * For vme host adaptor interface, dma enable bit may
	 * be set to allow reconnect interrupts to come in.
	 * This must be disabled before arbitration/selection
	 * of target is done. Don't worry about re-enabling
	 * dma. If arb/sel fails, then sw_idle will re-enable.
	 * If arb/sel succeeds then handling of command will
	 * re-enable.
	 *
	 * Also, disallow sbc to accept reconnect attempts.
	 * Again, sw_idle will re-enable this if arb/sel fails.
	 * If arb/sel succeeds then we do not want to allow
	 * reconnects anyway.
	 */
	s = spl7();	/* time critical */
	swr->csr &= ~SI_CSR_DMA_EN;

	SW_VME_OK(c, swr, "start of sw_cmd");
	SCSI_TRACE('c', swr, un);
	un->un_flags &= ~SC_UNF_DMA_INITIALIZED;

	/* performing target selection */
	if ((err = sw_arb_sel(c, swr, un)) != OK) {
		/* 
		 * May not be able to execute this command at this time due
		 * to a target reselecting us. Indicate this in the unit
		 * structure for when we perform this command later.
		 */
		SW_VME_OK(c, swr, "sw_cmd: arb_sel_fail");

		if (err == RESEL_FAIL) {
			DPRINTF1("sw_cmd:  preempted, tgt= %x\n",
				 un->un_target);
			un->un_saved_cmd.saved_cdb = c->c_cdb;
			un->un_flags |= SC_UNF_PREEMPT;
			err = OK;		/* not an error */

			/* Check for lost reselect interrupt */
		    	if ( !(SBC_RD.bsr & SBC_BSR_INTR)) {
				printf("sw_cmd:  reselect failure\n");
				swintr(c);
				}
		}
		un->un_wantint = 0;
		swr->csr |= SI_CSR_DMA_EN;
		(void) splx(s);
		return (err);
	}

	/*
	 * We need to send out an identify message to target.
	 */
	SBC_WR.ser = 0;			/* clear (re)sel int */
	SBC_WR.mr &= ~SBC_MR_DMA;	/* clear phase int */
	(void) splx(s);
	SW_VME_OK(c, swr, "sw_cmd: before msg out");
	if (c->c_flags & SCSI_EN_DISCON) {

		/* Tell target we do disconnects */
		/* DPRINTF("sw_cmd:  disconnects ENABLED\n"); */
		id = SC_DR_IDENTIFY | c->c_cdb.lun;
		SBC_WR.tcr = TCR_MSG_OUT;
 		if (sw_wait_phase(swr, PHASE_MSG_OUT) == OK) {
			if (sw_putdata(c, PHASE_MSG_OUT, &id, 1) != OK) {
				EPRINTF1("sw%d:  sw_cmd: id msg failed\n",
					SWNUM(c));
               			sw_idle(c);
               		        return(HARD_FAIL);
			}
		}
	} else {
		/*
		 * Since we didn't raise ATN, the target knows we
		 * don't do disconnects and won't bother asking us.
		 */
		DPRINTF("sw_cmd:  NO disconnect\n");
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

		if (un->un_flags & SC_UNF_RECV_DATA) {
			un->un_dma_curdir = SI_RECV_DATA;
			swr->csr &= ~SI_CSR_SEND;
		} else {
			un->un_dma_curdir = SI_SEND_DATA;
			swr->csr |= SI_CSR_SEND;
		}
		/* save current dma info for disconnect.  Note,
		 * address tweak for cobra.
		 */
 		un->un_dma_curaddr = un->un_dma_addr | 0xf00000;
		un->un_dma_curcnt = un->un_dma_count;
		un->un_dma_curbcr = 0;

		/* DPRINTF1("csr after resetting fifo 0x%x\n", swr->csr); */
	        /* 
	         * Currently we don't use all 24 bits of the
	         * count register on the vme interface. To do
		 * this changes are required other places, e.g.
		 * in the scsi_unit structure the fields
		 * un_dma_curcnt and un_dma_count would need to
		 * be changed.
		 */
		swr->dma_count = 0;

		/*
		 * New: we set up everything we can here, rather
		 * than wait until data phase.
		 */
		SW_VME_OK(c, swr, "sw_cmd: before cmd phase");
		sw_dma_setup(c, un);

	} else {
		un->un_dma_curdir = SI_NO_DATA;
		un->un_dma_curaddr = 0;
		un->un_dma_curcnt = 0;
	}
	SW_VME_OK(c, swr, "sw_cmd: before cmd phase");
	SCSI_TRACE('C', swr, un);

RETRY_CMD_PHASE:
	if (sw_wait_phase(swr, PHASE_COMMAND) != OK) {
		/*
		 * Handle synchronous messages (6 bytes) and other
		 * unknown messages.  Note, all messages will be
		 * rejected.  It would be nice someday to figure
		 * out what to do with them; but not today.
		 */
		register u_char *icrp = &SBC_WR.icr;

		if ((SBC_RD.cbsr & CBSR_PHASE_BITS) == PHASE_MSG_IN) {
			*icrp = SBC_ICR_ATN;
			msg = sw_getdata(c, PHASE_MSG_IN);
			EPRINTF1("sw_cmd:  rejecting msg 0x%x\n", msg);

			i = 128; /* accept 128 message bytes (overkill) */
			while((sw_getdata(c, PHASE_MSG_IN) != -1)  &&  --i);

			if ((SBC_RD.cbsr & CBSR_PHASE_BITS) == PHASE_MSG_OUT) {
				msg = SC_MSG_REJECT;
				*icrp = 0;		/* turn off ATN */
				(void) sw_putdata(c, PHASE_MSG_OUT, &msg, 1);
			}
			/* Should never fail this check. */
			if (i > 0)
				goto RETRY_CMD_PHASE;
		}
		/* we've had a target failure, report it and quit */
		printf("sw%d:  sw_cmd: no command phase\n", SWNUM(c));
		sw_reset(c, PRINT_MSG);
		return (SCSI_FAIL);

	}

	/*
	 * Determine size of the cdb.  Since we're smart, we
	 * look at group code and guess.  If we don't
	 * recognize the group id, we use the specified
	 * cdb length.  If both are zero, use max. size
	 * of data structure.
	 */
	if ((size = cdb_size[CDB_GROUPID(c->c_cdb.cmd)]) == 0  &&
	    (size = c->c_un->un_cmd_len) == 0) {
		printf("sw%d:  invalid cdb size, using size= %d\n",
			SWNUM(c), sizeof (struct scsi_cdb));
		size = sizeof (struct scsi_cdb);
	}
	c->c_last_phase = PHASE_COMMAND;
	s = spl7();			/* time critical */
	SBC_WR.ser = SI_HOST_ID;	/* enable (re)sel int */
	if (sw_putcmd(c, (u_char *)&c->c_cdb, size, intr) != OK) {
		printf("sw%d:  sw_cmd: put cmd failed\n", SWNUM(c));
		sw_print_state(swr, c);
		sw_idle(c);
		(void) splx(s);
		return(HARD_FAIL);
	}

	/* If not polled I/O mode, we're done */
	if (intr)  {
		/* Check for lost phase change interrupt */
		if ((SBC_RD.cbsr & SBC_CBSR_REQ)  &&
	 	    !(SBC_RD.bsr & SBC_BSR_INTR)) {
				printf("sw_cmd:  interrupt failure\n");
				swintr(c);
		}
		swr->csr |= SI_CSR_DMA_EN;
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

		SW_VME_OK(c, swr, "sw_cmd: before data xfer, sync");
		/*
		 * Check if we have a problem with the command
		 * not going into data phase.  If we do,
		 * then we'll skip down and get any status.
		 * Of course, this means that the command
		 * failed.
		 */
		if (sw_wait_phase(swr, phase) == OK) {
			/*
			 * Must actually start DMA xfer here - setup
			 * has already been done.  So, put sbc in dma
			 * mode and start dma transfer.
			 */
			sw_sbc_dma_setup(c, swr, (int)un->un_dma_curdir);

			/*
			 * Wait for DMA to finish.  If it fails,
			 * attempt to get status and report failure.
			 */
			if ((err=sw_cmdwait(c)) != OK) {
				EPRINTF("sw_cmd:  cmdwait failed\n");
				if (err != SCSI_FAIL)
					msg = sw_getstatus(un);
				return (err);
			}
		} else {
			EPRINTF("sw_cmd:  skipping data phase\n");
		}
	}

	/*
	 * Get completion status for polled command.
	 * Note, if <0, it's retryable; if 0, it's fatal.
	 * Someday I should give polled status results
	 * more options.  For now, everything is FATAL.
	 */
	c->c_last_phase = PHASE_CMD_CPLT;
	if ((err=sw_getstatus(un)) <= 0) {
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
sw_arb_sel(c, swr, un)
	register struct scsi_ctlr *c;
	register struct scsi_sw_reg *swr;
	register struct scsi_unit *un;
{
	register u_char *icrp = &SBC_WR.icr;
	register u_char *mrp = &SBC_WR.mr;
	register u_char icr;
	int ret_val;
	int j;

	DPRINTF("sw_arb_sel:\n");
	SW_VME_OK(c, swr, "sw_arb_sel");

	/* 
	 * It seems that the tcr must be 0 for arbitration to work.
	 */
	SBC_WR.tcr = 0;
	*mrp &= ~SBC_MR_ARB;	/* turn off arb */
	*icrp = 0;

#ifdef	SCSI_DEBUG
	if (scsi_debug > 2)
		sw_print_state(swr, c);
#endif	SCSI_DEBUG

	/* arbitrate for the scsi bus */
	for (j = 0; j < SI_NUM_RETRIES; j++) {

	/* wait for scsi bus to become free */
	if (sw_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_BSY,
	    SI_WAIT_COUNT, 0) != OK) {
		printf("sw%d:  sw_arb_sel: scsi bus continuously busy\n", SWNUM(c));
		sw_reset(c, PRINT_MSG);
		ret_val = SCSI_FAIL;
		goto SW_ARB_SEL_EXIT;
	}

		/* wait for sbc to begin arbitration */
		*mrp |= SBC_MR_ARB;		/* turn on arb */
		if (sw_sbc_wait((caddr_t)icrp, SBC_ICR_AIP, SI_WAIT_COUNT, 1)
		    != OK) {
			/*
			 * sbc may never begin arbitration due to a
			 * target reselecting us, the initiator.
			 */
			*mrp &= ~SBC_MR_ARB;	/* turn off arb */
			if (((SBC_RD.cbsr & SBC_CBSR_RESEL)  == SBC_CBSR_RESEL) && 
			    (SBC_RD.cdr & SI_HOST_ID)) {
				DPRINTF("sw_arb_sel:  recon1\n");
				ret_val = RESEL_FAIL;
				goto SW_ARB_SEL_EXIT;
			}
			EPRINTF1("sw_arb_sel:  AIP never set, cbsr= 0x%x\n",
				 SBC_RD.cbsr);
#ifdef	SCSI_DEBUG
			sw_print_state(swr, c);
#endif	SCSI_DEBUG
			goto SW_ARB_SEL_RETRY;
		}

		/* check to see if we won arbitration */
		DELAY(sw_arbitration_delay);
                icr = *icrp & ~SBC_ICR_AIP;
		if ( (*icrp & SBC_ICR_LA) == 0  && 
		    	((SBC_RD.cdr & ~SI_HOST_ID) < SI_HOST_ID) ) {

			/*
			 * WON ARBITRATION!  Perform selection.
			 * If disconnect/reconnect enabled, set ATN.
			 * If not, skip ATN so target won't do disconnects.
			 */
			/* DPRINTF("sw_arb_sel:  won arb\n"); */
			icr = SBC_ICR_SEL | SBC_ICR_BUSY | SBC_ICR_DATA;
			if (c->c_flags & SCSI_EN_DISCON) {
				icr |= SBC_ICR_ATN;
			}
			SBC_WR.odr = (1 << un->un_target) | SI_HOST_ID;
			*icrp = icr;
			*mrp &= ~SBC_MR_ARB;	/* turn off arb */
			DELAY(sw_bus_clear_delay + sw_bus_settle_delay);
			goto SW_ARB_SEL_WON;
		}

SW_ARB_SEL_RETRY:
		/* Lost arb, try again */
		*mrp &= ~SBC_MR_ARB;	/* turn off arb */
		if (((SBC_RD.cbsr & SBC_CBSR_RESEL)  == SBC_CBSR_RESEL) && 
		    (SBC_RD.cdr & SI_HOST_ID)) {
			DPRINTF("sw_arb_sel:  recon2\n");
			ret_val = RESEL_FAIL;
			goto SW_ARB_SEL_EXIT;
		}
		EPRINTF("sw_arb_sel:  lost arbitration\n");
	}
	/*
	 * FAILED ARBITRATION even with retries.
	 * This shouldn't ever happen since
	 * we have the highest priority id on the scsi bus.
	 */
	*icrp = 0;
	printf("sw%d:  sw_arb_sel: never won arbitration\n", SWNUM(c));
	sw_print_state(swr, c);
	ret_val = HARD_FAIL;

SW_ARB_SEL_EXIT:
	return(ret_val);


SW_ARB_SEL_WON:
	/* wait for target to acknowledge selection */
	*icrp &= ~SBC_ICR_BUSY;
	DELAY(1);
	if (sw_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_BSY,
	    SI_SHORT_WAIT, 1) != OK) {
		EPRINTF("sw_arb_sel:  busy never set\n");
#ifdef	SCSI_DEBUG
		if (scsi_debug > 2)
			sw_print_state(swr, c);
#endif	SCSI_DEBUG

		*icrp = 0;
		ret_val = HARD_FAIL;
		goto SW_ARB_SEL_EXIT;
	}
	/* DPRINTF("sw_arb_sel:  selected\n"); */
	*icrp &= ~(SBC_ICR_SEL | SBC_ICR_DATA);
	c->c_last_phase = PHASE_ARBITRATION;
	return (OK);
}


/*
 * Set up the SCSI control logic for a dma transfer for vme host adaptor.
 */
static
sw_dma_setup(c, un)
	register struct scsi_ctlr *c;
	register struct scsi_unit *un;
{
	register struct scsi_sw_reg *swr;
	(int)swr = c->c_reg;

	SW_VME_OK(c, swr, "sw_dma_setup");
	SCSI_RECON_TRACE('v', c, un->un_dma_curaddr, (int)un->un_dma_curcnt,
				(int)un->un_dma_curbcr);

	/* DPRINTF2("sw_dma_setup:  after fifo reset, csr 0x%x, bcr 0x%x\n",
	 *	swr->csr, swr->bcr);
	 */

	/* Check for odd-byte boundary buffer */
	/* NEED BETTER STRATEGY!! */
	if ((u_int)(un->un_dma_curaddr) & 0x1) {
		printf("sw%d:  illegal odd byte DMA address= 0x%x\n",
			SWNUM(c), un->un_dma_curaddr);
		/* sw_reset(c, PRINT_MSG); */
		/* return; */
	}

	/*
	 * setup starting dma address and number bytes to dma
	 * Note, the dma count is set to zero to prevent it from
	 * starting up.  It will be set later in sw_sbc_dma_setup
	 */
	swr->dma_addr = un->un_dma_curaddr;
	swr->dma_count = 0;

        /* set up byte packing control info */
	if (swr->dma_addr & 0x2) {
		if (un->un_dma_curdir == SI_RECV_DATA) {
			EPRINTF2("sw_dma_setup:  word transfer --  %X %X\n",
				 un->un_dma_curaddr, un->un_dma_count);
			un->un_flags |= SC_UNF_WORD_XFER;
		}
	}

	/*
	 * junk = GET_DMA_ADDR(swr);
	 * DPRINTF1("sw_dma_setup:  addr= 0x%x", junk);
	 * junk = GET_DMA_COUNT(swr);
	 * DPRINTF1("  count= %d ", junk);
	 * DPRINTF2("csr= 0x%x  bcr= 0x%x\n", swr->csr, swr->bcr);
	 */
}

/*
 * Setup and start the sbc for a dma operation.
 */
static
sw_sbc_dma_setup(c, swr, dir)
	register struct scsi_ctlr *c;
	register struct scsi_sw_reg *swr;
	register int dir;
{
	register struct scsi_unit *un = c->c_un;
	register int s;


	SCSI_TRACE('G', swr, un);
	SW_VME_OK(c, swr, "sw_sbc_dma_setup");
	un->un_flags |= SC_UNF_DMA_INITIALIZED;

	if (un->un_flags & SC_UNF_WORD_XFER) {
		char *cp;

		cp = (char *)swr->dma_addr;
		*cp++ = sw_getdata(c, PHASE_DATA_IN);
		*cp++ = sw_getdata(c, PHASE_DATA_IN);
		swr->dma_addr = (int)cp;
	}
	un->un_flags |= SC_UNF_DMA_INITIALIZED;

	if (dir == SI_RECV_DATA) {
		/* DPRINTF("sw_sbc_dma_setup:  RECEIVE DMA\n"); */
		c->c_last_phase = PHASE_DATA_IN;
		s = spl7();	/* time critical */
		SBC_WR.tcr = TCR_DATA_IN;
		junk = SBC_RD.clr;      /* clear intr */
		SBC_WR.mr |= SBC_MR_DMA;
		SBC_WR.ircv = 0;
		(void) splx(s);
	} else {
		/* DPRINTF("sw_sbc_dma_setup:  XMIT DMA\n"); */
		c->c_last_phase = PHASE_DATA_OUT;
		s = spl7();	/* time critical */
		SBC_WR.tcr = TCR_DATA_OUT;
		junk = SBC_RD.clr;      /* clear intr */
		SBC_WR.mr |= SBC_MR_DMA;
		SBC_WR.icr = SBC_ICR_DATA;
		SBC_WR.send = 0;
		(void) splx(s);
	}

	if (un->un_flags & SC_UNF_WORD_XFER) {
		un->un_flags &= ~SC_UNF_WORD_XFER;
		swr->dma_count = un->un_dma_curcnt - 2;
	} else {
		swr->dma_count = un->un_dma_curcnt;
	}
	swr->csr |= SI_CSR_DMA_EN;
}


/*
 * Cleanup up the SCSI control logic after a dma transfer.
 */
static
sw_dma_cleanup(c)
	register struct scsi_ctlr *c;
{
	register struct scsi_sw_reg *swr;
	(int)swr = c->c_reg;

	/* DPRINTF("sw_dma_cleanup:\n"); */

	/* disable dma controller */
	swr->dma_addr = 0;
	swr->dma_count = 0;
}

/*
 * Handle special dma receive situations, e.g. an odd number of bytes 
 * in a dma transfer.
 * The Sun3/50 onboard interface has different situations which
 * must be handled than the vme interface.
 * Returns OK if sucessful; Otherwise FAIL.
 */
static
sw_dma_recv(c) 
	register struct scsi_ctlr *c;
{
	register struct scsi_sw_reg *swr;
	register struct scsi_unit *un = c->c_un;
	register int offset, addr;
	(int)swr = c->c_reg;

#ifdef	lint
	un = un;
#endif	lint

	/* DPRINTF("sw_dma_recv:\n"); */
	SCSI_RECON_TRACE('R', c, un->un_dma_curaddr, (int)un->un_dma_curcnt,
			 offset);
	SCSI_TRACE('u', swr, un);
    	    /*
	     * Grabs last few bytes which may not have been dma'd.
	     * Worst case is when longword dma transfers are being done
	     * and there are 3 bytes leftover.
	     * If BPCON bit is set then longword dmas were being done,
	     * otherwise word dmas were being done.
	     */
	addr = swr->dma_addr;
	offset = (addr - (int)DVMA) & 0xFFFFFC;
	switch (swr->dma_addr & 0x3) {
	case 3:			/* three bytes left */
		DVMA[offset] = (swr->bpr & 0xff000000) >> 24;
		DVMA[offset + 1] = (swr->bpr & 0x00ff0000) >> 16;
		DVMA[offset + 2] = (swr->bpr & 0x0000ff00) >> 8;
		break;

	case 2:			/* two bytes left */
		DVMA[offset] = (swr->bpr & 0xff000000) >> 24;
		DVMA[offset + 1] = (swr->bpr & 0x00ff0000) >> 16;
		break;

	case 1:			/* one byte left */
		DVMA[offset] = (swr->bpr & 0xff000000) >> 24;
		break;
	}
	return (OK);

}


/*
 * Handle a scsi interrupt.
 */
swintr(c)
	register struct scsi_ctlr *c;
{
	register struct scsi_sw_reg *swr;
	register struct scsi_unit *un;
	register u_char *cp;
	register int resid;
	int status;
	u_int lun;
	u_short bcr;	/* get it for discon stuff BEFORE we clr int */
	u_char msg;

	(int)swr = c->c_reg;

	/* 
	 * For vme host adaptor interface, must disable dma before
	 * accessing any registers other than the csr or the 
	 * SI_CSR_DMA_CONFLICT bit in the csr will be set.
	 */
	/* DPRINTF("swintr:\n"); */ 
HEAD_SWINTR:
	un = c->c_un;

	if (swr->csr & SI_CSR_DMA_CONFLICT)
		printf("swintr: head CSR %X\n", swr->csr);
	swr->csr &= ~SI_CSR_DMA_EN;
	SW_VME_OK(c, swr, "top of swintr");

	/*
	 * We need to store the contents of the byte count register
	 * before we change the state of the 5380.  The 5380 has
	 * a habit of prefetching data before it knows whether it
	 * needs it or not, and this can throw off the bcr.
	 * Note: Cobra does not have a bcr so we must figure
	 * this out from the dma_addr register.  Also un could be zero
	 * coming into the interrupt routine so we need to check it
	 * and not use it if it is (will this cause problems later?)
	 */
	resid = 0;
	bcr = 0;
	SCSI_TRACE('i', swr, un);

	if (un != NULL) {	/* prepare for a disconnect */
		if (un->un_dma_curdir != SI_NO_DATA) {
			bcr = un->un_dma_curcnt - 
			      (swr->dma_addr - un->un_dma_curaddr);
			DPRINTF2("swintr:  bcr= %X   tcr= %X  ",
				 bcr, SBC_RD.tcr);
			DPRINTF2("dma addr= %X   cur addr= %X  ",
				 swr->dma_addr, un->un_dma_curaddr);
			DPRINTF1("count= %X\n", un->un_dma_curcnt );

			if ((swr->dma_addr - un->un_dma_curaddr) && 
			       !(SBC_RD.tcr & SBC_TCR_LAST) && 
			       (un->un_dma_curdir == SI_SEND_DATA))
				bcr++;
		}
	}

	/*
	 * Determine source of interrupt.
	 */
	if (swr->csr & (SI_CSR_DMA_CONFLICT | SI_CSR_DMA_BUS_ERR)) {
		/*
		 * DMA related error.
		 */
		if (swr->csr & SI_CSR_DMA_BUS_ERR) {
			printf("sw%d:  swintr: bus error during dma\n",
				SWNUM(c));
			/* goto RESET_AND_LEAVE; */

		} else if (swr->csr & SI_CSR_DMA_CONFLICT) {
			printf("sw%d:  swintr: invalid reg access during dma\n",
				SWNUM(c));
		} else {
				/*
				 * I really think that this is also DMA
				 * in progress.
				 */
				printf("sw%d:  swintr: dma overrun\n", SWNUM(c));
		}
		junk = SBC_RD.clr;	/* clear int, if any */
		sw_print_state(swr, c);

		/*
		 * Either we were waiting for an interrupt on a phase change 
		 * on the scsi bus, an interrupt on a reconnect attempt,
		 * or an interrupt upon completion of a real dma operation.
		 * Each of these situations must be handled appropriately.
		 */
		if (un == NULL) {
			/* Spurious reconnect. */
			printf("sw%d:  swintr: illegal reconnection for DMA\n",
				SWNUM(c));
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
			sw_dma_cleanup(c);
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
		/* CRITICAL CODE SECTION DON'T TOUCH */
		junk = SBC_RD.clr;		 /* clear int */
		/*SBC_WR.ser = 0;			/* clear (re)sel int */
		cdr = SBC_RD.cdr & ~SI_HOST_ID;

		/* make sure there are only 2 scsi id's set */
		DPRINTF1("swintr:  reconnecting, cdr 0x%x\n", cdr); 
		for (i=0; i < 8; i++) {
			if (cdr & (1<<i))
				break;
		}
		/* CRITICAL CODE SECTION DON'T TOUCH */
		SBC_WR.ser = 0;			/* clear (re)sel int */
		cdr &= ~(1<<i);
		if (cdr != 0) {
			printf("sw%d:  swintr: >2 scsi reselection ids, cdr 0x%x\n",
				SWNUM(c), SBC_RD.cdr);
			SBC_WR.ser = SI_HOST_ID; /* enable (re)sel int */
			goto SET_UP_FOR_NEXT_INTR_AND_LEAVE;
		}

		/* acknowledge reselection */
#ifdef	SCSI_DEBUG
		if (scsi_debug > 2) {
			printf("swintr:  before resel ack\n");
			sw_print_state(swr, c);
		}
#endif	SCSI_DEBUG
		SBC_WR.icr |= SBC_ICR_BUSY;
		c->c_recon_target = i;		/* save for reconnect */
#ifdef	SCSI_DEBUG
		if (scsi_debug > 2) {
			printf("swintr:  after resel ack\n");
			sw_print_state(swr, c);
		}
#endif	SCSI_DEBUG

		/*
		 * If reselection ok, target should drop select.
		 * Otherwise, we took too long.  It would be nice
		 * to wait for next resel attempt...someday.
		 */
		if (sw_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_SEL,
		    SI_WAIT_COUNT, 0) != OK) {
			printf("sw%d:  swintr: SEL not released\n",
				SWNUM(c));
			SBC_WR.ser = SI_HOST_ID; /* enable (re)sel int */
			goto SET_UP_FOR_NEXT_INTR_AND_LEAVE;
		}
		SBC_WR.icr &= ~SBC_ICR_BUSY;
#ifdef	SCSI_DEBUG
		if (scsi_debug > 2) {
			printf("swintr:  reconnecting\n");
			sw_print_state(swr, c);
		}
#endif	SCSI_DEBUG

		/*
		 * If reselection ok, then target should go into MSG_IN
		 * phase to identify.  If not, die.
		 */
		if (sw_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ,
		    SI_WAIT_COUNT, 1) != OK) {
			printf("sw%d:  swintr: no MSG_IN req\n", SWNUM(c));
			SBC_WR.ser = SI_HOST_ID; /* enable (re)sel int */
			/* goto RESET_AND_LEAVE; */
			goto SET_UP_FOR_NEXT_INTR_AND_LEAVE;
		}
		SBC_WR.ser = 0;			/* clear (re)sel int */
		SBC_WR.ser = SI_HOST_ID;	/* enable (re)sel int */
		/* FALL THROUGH INTO SYNCHRONIZE_PHASE */
	}
	SBC_WR.tcr = TCR_UNSPECIFIED;


SYNCHRONIZE_PHASE:
	/*
	 * We know that we have a new phase we have to handle.
	 */
	DPRINTF("swintr: synch\n");
	if (sw_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ, SI_PHASE_WAIT, 1)
	    != OK) {
		/* DPRINTF("swintr:  phase timeout\n"); */
		goto HANDLE_SPURIOUS_AND_LEAVE;
	}
	SW_WIN;
	junk = SBC_RD.clr;		 /* clear any pending sbc interrupt */
	switch (SBC_RD.cbsr & CBSR_PHASE_BITS) {

	case PHASE_DATA_IN:
	case PHASE_DATA_OUT:
		DPRINTF("  DATA\n");

#ifdef	SCSI_DEBUG
		if (scsi_debug > 2)
			sw_print_state(swr, c);
#endif	SCSI_DEBUG
		SW_VME_OK(c, swr, "swintr: data_out");
		SBC_WR.mr &= ~SBC_MR_DMA;	/* clear phase int */

		if (un == NULL) {
			printf("sw%d:  swintr: no unit expecting DATA phase\n",
				SWNUM(c));
			goto RESET_AND_LEAVE;
		}

		if (un->un_dma_curcnt <= 0  ||  un->un_dma_curdir == SI_NO_DATA) {
			printf("sw%d:  swintr: unexpected DATA phase, curcnt %d, curdir 0x%x\n",
				SWNUM(c), un->un_dma_curcnt, un->un_dma_curdir);
			goto RESET_AND_LEAVE;
		}

		/* data is expected, start dma data transfer and exit */
		sw_sbc_dma_setup(c, swr, (int)un->un_dma_curdir);
		goto LEAVE;


	case PHASE_MSG_IN:
		DPRINTF("  MSG");	
#ifdef	SCSI_DEBUG
		if (scsi_debug > 2)
			sw_print_state(swr, c);
#endif	SCSI_DEBUG
		SW_VME_OK(c, swr, "swintr: msg_in");

		msg = SBC_RD.cdr;		/* peek at message */
		lun = msg & 0x07;
		msg &= 0xf0;			/* mask off unit number */

		/* DPRINTF2("swintr:  msg 0x%x, lun %d\n", msg, lun); */
		if ((msg == SC_IDENTIFY)  ||  (msg == SC_DR_IDENTIFY)) {
			/*
			 * If we have a reconnect, we want to do our
			 * DMA setup before we go into DATA phase.
			 * This is why we peek at the message via the cdr
			 * rather than doing an sw_getdata from the start.
			 * sw_reconnect acknowledges the reconnect message.
			 */
			/* EPRINTF("swintr:  msg= identify\n"); */
			if (sw_reconnect(c, c->c_recon_target, lun) != OK){
				printf("sw$d:  swintr:  reconnection failure\n",
					SWNUM(c));
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
				(int)un->un_dma_curbcr, (int)swr->bcr);
			}
		}

		c->c_last_phase = PHASE_MSG_IN;
		msg = sw_getdata(c, PHASE_MSG_IN);
		switch (msg) {

		case SC_COMMAND_COMPLETE:
			/* DPRINTF("swintr:  msg= command complete\n"); */
			c->c_last_phase = PHASE_CMD_CPLT;
			cp = (u_char *) &c->c_scb;
			if (cp[0] & SCB_STATUS_MASK)
				status = SE_RETRYABLE;
			else
				status = SE_NO_ERROR;
			goto HAND_OFF_INTR;

		case SC_DISCONNECT:
			DPRINTF("swintr:  msg= disconnect\n");
			c->c_last_phase = PHASE_DISCONNECT;
			if ((un->un_flags & SC_UNF_DMA_INITIALIZED) == 0  &&
			    (un->un_dma_curdir == SI_SEND_DATA) &&
			    (un->un_dma_curcnt != un->un_dma_count)) {
				EPRINTF("swintr:  Warning, write disconnect w/o DMA\n");
				EPRINTF2("\tcnt= %d (%d)  ",
					 un->un_dma_curcnt, un->un_dma_count);
				EPRINTF2("bcr= %d  tgt= %d  ",
					 un->un_dma_curbcr, un->un_target);
				EPRINTF1("lun= %d  cdb =", un->un_lun);
#ifdef	SCSI_DEBUG
				if (scsi_debug)
					sw_print_cdb(c);
#endif	SCSI_DEBUG
			}
			if (sw_disconnect(c) != OK) {
				printf("sw%d:  swintr: disconnect failure\n",
					SWNUM(c));
				goto RESET_AND_LEAVE;
			}
			goto START_NEXT_COMMAND_AND_LEAVE;

		case SC_RESTORE_PTRS:
			/* these messages are noise  - ignore them */
			DPRINTF("swintr:  msg= restore pointer\n");
			c->c_last_phase = PHASE_RESTORE_PTR;
			goto SYNCHRONIZE_PHASE;

		case SC_SAVE_DATA_PTR:
			/* save the bcr before the bastard pre-fetches again */
			DPRINTF("swintr:  msg= save pointer\n");
			un->un_dma_curbcr = bcr;
			c->c_last_phase = PHASE_SAVE_PTR;
			goto SYNCHRONIZE_PHASE;

		case SC_NO_OP:
			EPRINTF("swintr:  msg= no op\n");
			goto SYNCHRONIZE_PHASE;

		case SC_PARITY:
			EPRINTF("swintr:  msg= parity error\n");
			goto SYNCHRONIZE_PHASE;

		case SC_ABORT:
			EPRINTF("swintr:  msg= abort\n");
			goto SET_UP_FOR_NEXT_INTR_AND_LEAVE;

		case SC_DEVICE_RESET:
			EPRINTF("swintr:  msg= reset device\n");
			goto SET_UP_FOR_NEXT_INTR_AND_LEAVE;

		default:
			printf("sw%d:  swintr: ignoring unknown message= 0x%x\n",
				SWNUM(c), msg);
			goto HANDLE_SPURIOUS_AND_LEAVE;
		}


	case PHASE_STATUS:
		DPRINTF("  STATUS");

#ifdef	SCSI_DEBUG
		if (scsi_debug > 2)
			sw_print_state(swr, c);
#endif	SCSI_DEBUG
		SW_VME_OK(c, swr, "swintr: status");
		if ((un->un_dma_curdir == SI_RECV_DATA)  &&
		    (sw_dma_recv(c) != OK)) {
			/* DMA failure, time to reset SCSI bus */
			printf("sw%d:  swintr: DMA failure\n", SWNUM(c));
			goto RESET_AND_LEAVE;
		}

		/* DPRINTF("swintr:  getting status bytes\n"); */
		if (! sw_status_bytes(un)) {
			/* status failure, time to reset SCSI bus */
			printf("sw%d:  swintr: no status\n", SWNUM(c));
			goto RESET_AND_LEAVE;
		}
		SCSI_TRACE('s', swr, un);
		c->c_last_phase = PHASE_STATUS;
		goto SYNCHRONIZE_PHASE;


	default:
		printf("sw%d:  swintr: ignoring spurious phase\n", SWNUM(c));
		sw_print_state(swr, c);
		c->c_last_phase = PHASE_SPURIOUS;
		goto HANDLE_SPURIOUS_AND_LEAVE;
}


HAND_OFF_INTR:
	DPRINTF("hand_off_intr:\n"); 
	SW_VME_OK(c, swr, "swintr: hand off intr");
	swr->csr &= ~SI_CSR_DMA_EN;


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
			printf("swintr:  residue error\n");
			sw_print_state(swr, c);
		}
#endif	SCSI_DEBUG


		/* call high-level scsi device interrupt handler to finish */
		(*un->un_ss->ss_intr)(c, resid, status);
		swr->csr &= ~SI_CSR_DMA_EN;
	}

	/* fall through to start_next_command_and_leave */


START_NEXT_COMMAND_AND_LEAVE:

	/* start next I/O activity on controller */
	DPRINTF("swintr:  start_next_command\n");
	SW_VME_OK(c, swr, "swintr: start next command");
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
		msg = SBC_RD.cbsr;
		if (((msg & SBC_CBSR_RESEL)  == SBC_CBSR_RESEL) && 
		    (SBC_RD.cdr & SI_HOST_ID)) {
			DPRINTF1("swintr:  recon1, cbsr= 0x%x\n", msg);
			goto HANDLE_RECONNECT;
		}
		/* 
		 * If this activity was preempted due to a 
		 * reselection coming in, much of the setup has 
		 * already taken place and must not be redone.
		 */
		if (un->un_flags & SC_UNF_PREEMPT) {

			DPRINTF1("swintr:  doing preempted, tgt= %x\n",
				 un->un_target);
			un->un_flags &= ~SC_UNF_PREEMPT;
			c->c_cdb = un->un_saved_cmd.saved_cdb;
			c->c_un = un;
			un->un_mc->mc_tab.b_active = 1;
			if (un->un_dma_curdir != SI_NO_DATA) {
				un->un_mc->mc_mbinfo = un->un_baddr;
			}

			if (sw_cmd(c, un, 1) == FAIL) {
				/*
				 * Command startup failed.
				 */
				EPRINTF1("swintr:  preempted FAILED, tgt= %x\n",
					 un->un_target);
				(*un->un_ss->ss_intr)(c, 0, SE_FATAL);
				sw_off(c, un);
			}
		} else {
			DPRINTF("swintr:  swstart\n");
			swstart(un);
		}
	}
	/*
	 * Either we've started a command or there weren't any to start.
	 * In any case, we're done...
	 */
	goto SET_UP_FOR_NEXT_INTR_AND_LEAVE;


RESET_AND_LEAVE:
	EPRINTF1("swintr:  reset_and_leave: RESET to state 0x%x\n",sw_stbi);
	sw_reset(c, PRINT_MSG);
	goto SET_UP_FOR_NEXT_INTR_AND_LEAVE;


HANDLE_SPURIOUS_AND_LEAVE:
	SBC_WR.mr |= SBC_MR_DMA;
	/* FALL THROUGH */


SET_UP_FOR_NEXT_INTR_AND_LEAVE:
	DPRINTF("swintr:  set_up_for_next_intr\n");
	swr->csr &= ~SI_CSR_DMA_EN;
	junk = SBC_RD.clr;		/* clear int */
	SW_VME_OK(c, swr, "swintr: setup for next intr");

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
			SW_WIN;
			/* DPRINTF("swintr:  recon2\n"); */
			goto HEAD_SWINTR;
		} else {
			SW_LOSE;
			/* EPRINTF("  lose2"); */
		}
	} else {
		/* Check for phase change.  */
		/*s = spl7();	/* time critical */
		msg = SBC_RD.cbsr;
		if (msg & SBC_CBSR_REQ) {
			/* (void) splx(s); */
			SW_WIN;
			/* EPRINTF("swintr:  recon3\n"); */
			goto HEAD_SWINTR;
		} else {
			SW_LOSE;
			/* EPRINTF("  lose3"); */
		}
	}
        /* Enable interrupts and DMA. */
	swr->csr |= SI_CSR_DMA_EN;

LEAVE:
	DPRINTF("\n");
	return;
}


/*
 * Handle target disconnecting.
 * Returns true if all was OK, false otherwise.
 */
static
sw_disconnect(c) 
	register struct scsi_ctlr *c;
{
	register struct scsi_sw_reg *swr;
	register struct scsi_unit *un = c->c_un;
	register struct mb_ctlr *mc = un->un_mc;
	register struct buf *dp;
	register u_short bcr;

	(int)swr = c->c_reg;
	bcr = un->un_dma_curbcr;

	/* DPRINTF("sw_disconnect:\n"); */
	SCSI_RECON_TRACE('d', c, un->un_dma_curaddr, (int) un->un_dma_curbcr,
				(int) bcr);

	/*
	 * If command doen't require dma, don't save dma info.
	 * for reconnect.  If it does, but data phase was missing,
	 * don't update dma info.
	 */
	if ((un->un_dma_curdir != SI_NO_DATA)  &&
	    (un->un_flags & SC_UNF_DMA_INITIALIZED)) {

		if ((un->un_dma_curdir == SI_RECV_DATA)  &&
		    (sw_dma_recv(c) != OK)) {
			printf("sw%d:  sw_disconnect: DMA bogosity\n",SWNUM(c));
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
			printf("sw_disconnect:  bcr is 1\n");
		if (sw_dis_debug) {
		    printf("sw_disconnect:  addr= 0x%x  count= %d  bcr= 0x%x  ",
			   un->un_dma_curaddr, un->un_dma_curcnt,  bcr);
		    printf("sr= 0x%x  baddr= 0x%x\n", swr->csr, un->un_baddr);
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
	SW_VME_OK(c, swr, "sw_disconnect");

	swr->dma_count = 0;

	/* DPRINTF("sw_disconnect:  done\n"); */
	return (OK);
}


/*
 * Complete reselection phase and reconnect to target.
 *
 * Return OK if sucessful, FAIL if not.
 *
 * NOTE: this routine cannot use sw_getdata to get identify msg
 * from reconnecting target due to sun3/50 scsi interface. The bcr
 * must be setup before the target changes scsi bus to data phase
 * if the command being reconnected involves dma (which we do not
 * know until we get the identify msg). Thus we cannot acknowledge
 * the identify msg until some setup of the host adaptor registers 
 * is done.
 */
sw_reconnect(c, target, lun)
	register struct scsi_ctlr *c;
	register u_int target;
	register u_int lun;
{
	register struct scsi_sw_reg *swr;
	register struct scsi_unit *un;
	register struct buf *dp;
	register struct buf *pdp;
	(int)swr = c->c_reg;

	/* search disconnect queue for reconnecting task */
	/* DPRINTF2("sw_reconnect:  target %d lun %d\n", target, lun); */
	DPRINTF("  disconnect que:\n");
	for (dp = c->c_disqh, pdp = NULL; dp; pdp = dp, dp = dp->b_forw) {
		un = (struct scsi_unit *)dp->b_un.b_addr;
		DPRINTF1("\tbp = 0x%x  ---  ", dp);
		DPRINTF2("target= %d,  lun= %d\n", un->un_target, un->un_lun);
		if ((un->un_target == target)  &&  (un->un_lun == lun))
			break;
	}

	if (dp == NULL) {
		printf("sw%d:  sw_reconnect: can't find dis unit: target %d lun %d\n",
			SWNUM(c), target, lun);
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
		SW_VME_OK(c, swr, "sw_reconnect: dp == NULL");
		return (FAIL);
	}

	/* disable other reconnection attempts */
	SW_VME_OK(c, swr, "sw_reconnect: wser = 0");

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

		/* do initial dma setup */
		swr->dma_count = 0;
		if (un->un_dma_curdir == SI_RECV_DATA)
			swr->csr &= ~SI_CSR_SEND;
		else
			swr->csr |= SI_CSR_SEND;

		/*
		 * New: we set up everything we can here, rather
		 * than wait until data phase.
		 */
		swr->csr &= ~SI_CSR_DMA_EN;
		sw_dma_setup(c, un);

#ifdef	SCSI_DEBUG
		if (sw_dis_debug) {
		    printf("sw_reconnect:  addr= 0x%x  count= 0x%x  bcr= 0x%x",
			  un->un_dma_curaddr, un->un_dma_curcnt, swr->bcr); 
		    printf("  sr= 0x%x  baddr= 0x%x\n", swr->csr, un->un_baddr);
		}
#endif	SCSI_DEBUG
	}

	/* we can finally acknowledge identify message */
	SBC_WR.icr = SBC_ICR_ACK;

	if (sw_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ,
	    SI_WAIT_COUNT, 0) != OK) {
		printf("sw%d:  sw_reconnect: REQ not INactive\n", SWNUM(c));
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
sw_deque(c, un)
	register struct scsi_ctlr *c;
	register struct scsi_unit *un;
{
	register struct scsi_sw_reg *swr;
	register u_int target;
	register u_int lun;
	register struct buf *bp;
	register struct buf *pbp;
	int s;

	(int)swr = c->c_reg;

	/* Lock out the rest of sw till we've finished the dirty work. */
	/* DPRINTF("sw_deque:\n"); */
	target = un->un_target;
	lun = un->un_lun;
	sw_print_state(swr, c);
	s = splx(pritospl(un->un_mc->mc_intpri));
	un = c->c_un;			/* get current unit */

	/*
	 * If current SCSI I/O request is the one that timed out. Kill it.
	 */
	if ((int)un != NULL  &&
	    un->un_mc->mc_tab.b_active != 0  &&
	    un->un_target == target  &&
	    un->un_lun == lun) {
		EPRINTF("sw_deque:  failed request at top of que\n");
		(*un->un_ss->ss_intr)(c, un->un_dma_count, SE_TIMEOUT);
		(void) splx(s);
		return(OK);
	}

	/* Search disconnect que for reconnecting task */
	/* DPRINTF2("sw_deque:  searching for target %d,  lun %d\n  que:\n",
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
		printf("sw_deque:  can't find: target %d, lun %d\n  que:\n",
			target, lun);
		for (bp = c->c_disqh,pbp = NULL; bp; pbp = bp,bp = bp->b_forw) {
			un = (struct scsi_unit *)bp->b_un.b_addr;
			printf("\tbp = 0x%x  ---  target = %d,  lun = %d\n",
				bp, un->un_target, un->un_lun == lun);
		}
		EPRINTF("sw_deque:  entry not found\n");
		(void) splx(s);
		return(FAIL);
	}

	/* Remove entity from disconnect que */
	/* DPRINTF2("sw_deque:  bp= 0x%x,  pbp= 0x%x\n", bp, pbp); */
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
		EPRINTF("sw_deque:  reactivating request\n");
		if (un->un_mc->mc_tab.b_active != 0) {
			EPRINTF("sw_deque:  we have a reactivate problem\n");
		}
		un->un_mc->mc_tab.b_actf = bp;
		un->un_mc->mc_tab.b_actl = bp;
		un->un_mc->mc_tab.b_active = 1;
		c->c_un = un;
		(*un->un_ss->ss_intr)(c, un->un_dma_count, SE_TIMEOUT);
	} else {
		EPRINTF("sw_deque:  can't reactive request\n");
		sw_reset(c, PRINT_MSG);
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
sw_idle(c)
	register struct scsi_ctlr *c;
{
	register struct scsi_sw_reg *swr;
	register struct buf *dp;
	register struct scsi_unit *un;
	register int resid;
	(int)swr = c->c_reg;

	/* DPRINTF("sw_idle:\n"); */
	if (c->c_flags & SCSI_FLUSHING) {
		EPRINTF1("sw_idle:  flushing, flags 0x%x\n", c->c_flags);
		return;
	}

	/* flush disconnect tasks if a reconnect will never occur */
	if (c->c_flags & SCSI_FLUSH_DISQ) {
		EPRINTF("sw_idle:  flushing disconnect que\n"); 

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
			swustart(un);
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
			sw_off(c, un);		/* unit is going offline */
		}
		if (c->c_disqh == NULL) {
			c->c_disqt = NULL;
		}
		c->c_flags &= ~SCSI_FLUSHING;
		return;
	}

	/* enable reconnect attempts */
	swr->csr &= ~SI_CSR_DMA_EN;	/* turn off before SBC access */

	swr->dma_count = 0;
	swr->csr &= ~SI_CSR_SEND;
	swr->csr |= SI_CSR_DMA_EN;
}


/*
 * Get status bytes from scsi bus.
 * Returns number of status bytes read if no error.
 * If error, returns -1.
 * If scsi bus error, returns 0.
 */
sw_getstatus(un)
	register struct scsi_unit *un;
{
	register struct scsi_sw_reg *swr;
	register struct scsi_ctlr *c = un->un_c;
	register u_char *cp;
	register int i;
	register u_char msg;
	(int)swr = c->c_reg;

	/* DPRINTF("sw_getstatus:\n"); */
	SW_VME_OK(c, swr, "sw_getstatus:");

	if (sw_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ,
	    SI_LONG_WAIT, 1) != OK) {
		printf("sw%d:  sw_getstatus: REQ inactive\n", SWNUM(c));
		sw_print_state(swr, c);
		return (0);
	}

	if (sw_wait_phase(swr, PHASE_STATUS) != OK) {
		printf("sw%d:  sw_getstatus: no STATUS phase\n", SWNUM(c));
		sw_print_state(swr, c);
		return (0);
	}
	i = sw_status_bytes(un);

#ifdef	SCSI_DEBUG
	if (scsi_debug > 2) {
		int x;
		register u_char *p = (u_char *)&c->c_scb;

		printf("sw_getstatus:  %d status bytes", i);
		for (x = 0; x < i; x++)
			printf("  %x", *p++);
		printf("\n");
	}
#endif	SCSI_DEBUG

	if (sw_wait_phase(swr, PHASE_MSG_IN) != OK) {
		printf("sw%d:  sw_getstatus: no MSG_IN phase\n", SWNUM(c));
		sw_print_state(swr, c);
		return (0);
	}

	SW_VME_OK(c, swr, "sw_getstatus: msg_in");
	msg = sw_getdata(c, PHASE_MSG_IN);
	if (msg != SC_COMMAND_COMPLETE) {
		EPRINTF1("sw_getstatus:  bogus msg_in 0x%x\n", msg);
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
sw_status_bytes(un)
	struct scsi_unit *un;
{
	register struct scsi_ctlr *c = un->un_c;
	register u_char *cp = (u_char *)&c->c_scb;
	register int i;
	register int b;

	/* DPRINTF("sw_status_bytes:\n"); */
	/* get all the status byte(s) */
	for (i = 0;;) {

		b = sw_getdata(c, PHASE_STATUS);

		if (b < 0)
			break;
		if (i < STATUS_LEN)
			cp[i++] = b;
	}

#ifdef	SCSI_DEBUG
	/* set status to reflect whether SCSI operation was ok. */
	if (cp[0] & SCB_STATUS_MASK)
		DPRINTF1("sw_status_bytes:  cmd failed, scb= 0x%x\n", cp[0]);
#endif	SCSI_DEBUG


	return (i);
}


/* 
 * Wait for a scsi dma request to complete.
 * Disconnects were disabled in sw_cmd when polling for command completion.
 * Called by drivers in order to poll on command completion.
 */
sw_cmdwait(c)
	register struct scsi_ctlr *c;
{
	register struct scsi_sw_reg *swr;
	register struct scsi_unit *un = c->c_un;
	register int ret_val;
	(int)swr = c->c_reg;

	DPRINTF("sw_cmdwait:\n");

	/* if command does not involve dma activity, then we are finished */
	if (un->un_dma_curdir == SI_NO_DATA) {
		return (OK);
	}

	/* wait for indication of dma completion */
	if (sw_wait((u_int *)&swr->csr, 
	    (SI_CSR_SBC_IP | SI_CSR_DMA_CONFLICT | SI_CSR_DMA_BUS_ERR), 1) != OK) {
		printf("sw%d:  sw_cmdwait: dma never completed\n", SWNUM(c));
		sw_reset(c, PRINT_MSG);
		ret_val = SCSI_FAIL;
		goto SW_CMDWAIT_EXIT;
	}

	/* 
	 * Early Cobra units have a faulty gate array.
	 * It can cause an illegal memory access if full
	 * page DMA is being used.  For less than a full
	 * page, no problem.  This problem typically shows
	 * up when dumping core.  The following code fixes
	 * this problem.
	 */
	swr->csr &= ~SI_CSR_DMA_EN;
	if(swr->csr & SI_CSR_DMA_BUS_ERR){
		(void) sw_dma_recv(c);
		junk = SBC_RD.clr;
		ret_val = OK;
		goto SW_CMDWAIT_EXIT;
	}

	/* handle special dma recv situations */
	if ((un->un_dma_curdir == SI_RECV_DATA)  &&  (sw_dma_recv(c) != OK)) {
		printf("sw%d:  sw_cmdwait: special DMA failure\n", SWNUM(c));
		sw_reset(c, PRINT_MSG);
		ret_val = SCSI_FAIL;
		goto SW_CMDWAIT_EXIT;
	}

	/* ack sbc interrupt and cleanup */
	junk = SBC_RD.clr;
	sw_dma_cleanup(c);
	ret_val = OK;

SW_CMDWAIT_EXIT:
	if (swr->csr & SI_CSR_SBC_IP) {
		junk = SBC_RD.clr;	/* clear sbc int */
	}
	swr->csr &= ~SI_CSR_DMA_EN;	/* turn it off to be sure */
	return(ret_val);

}


/*
 * Wait for a condition to be (de)asserted on the scsi bus.
 * Returns OK for successful.  Otherwise, returns
 * FAIL.
 */
static
sw_sbc_wait(reg, cond, wait_count, set)
	register caddr_t reg;
	register u_char cond;
	register int wait_count;
	register int set;
{
	register int i;
	register u_char regval;

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
	DPRINTF("sw_sbc_wait:  timeout\n");
	return (FAIL);
}


/*
 * Wait for a condition to be (de)asserted.
 * Used for monitor DMA controller.
 * Returns OK for successful.  Otherwise,
 * returns FAIL.
 */
static
sw_wait(reg, cond, set)
	register u_int *reg;
	register u_int cond;
	register int set;
{
	register int i;
	register u_int regval;

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
sw_wait_phase(swr, phase)
	register struct scsi_sw_reg *swr;
	register u_char phase;
{
	register int i;

	DPRINTF2("sw_wait_phase:  %s phase (0x%x)\n",sw_str_phase(phase),phase);
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
sw_putdata(c, phase, data, num)
	register struct scsi_ctlr *c;
	register u_short phase;
	register u_char *data;
	register int num;
{
	register struct scsi_sw_reg *swr;
	register int i;
	(int)swr = c->c_reg;

	DPRINTF2("sw_putdata:  %s phase (0x%x) ", sw_str_phase(phase), phase);
	/* DPRINTF1("num %d\n", num); */
	SW_VME_OK(c, swr, "sw_putdata");

	/* 
	 * Set up tcr so we can transmit data.
	 */
	SBC_WR.tcr = phase >> 2;

	/* put all desired bytes onto scsi bus */
	for (i = 0; i < num; i++ ) {

		/* wait for target to request a byte */
		SBC_WR.icr = 0;			/* clear ack */
		if (sw_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ, 
		    SI_WAIT_COUNT, 1) != OK) {
			printf("sw%d:  putdata, REQ not active\n", SWNUM(c));
			return (HARD_FAIL);
		}

		/* load data */
		/* DPRINTF2("putting byte # %d, = 0x%x\n", i, *data); */
		SBC_WR.odr = *data++;
		SBC_WR.icr = SBC_ICR_DATA;

		/* complete req/ack handshake */
		SBC_WR.icr |= SBC_ICR_ACK;
		if (sw_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ,
		    SI_WAIT_COUNT, 0) != OK) {
			printf("sw%d:  putdata, req not INactive\n", SWNUM(c));
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
sw_putcmd(c, data, num, want_intr)
	register struct scsi_ctlr *c;
	register u_char *data;
	register u_char num;
	register int want_intr;
{
	register struct scsi_sw_reg *swr;
	register u_char i;
	(int)swr = c->c_reg;

	SW_VME_OK(c, swr, "sw_putcmd");
	SBC_WR.tcr = TCR_COMMAND;

	/* put all desired bytes onto scsi bus */
	for (i = 0; i < num; i++ ) {

		SBC_WR.icr = SBC_ICR_DATA;	/* clear ack, enable data bus */

		/* wait for target to request a byte */
		if (sw_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ,
		    SI_WAIT_COUNT, 1) != OK) {
			printf("sw%d:  sw_putcmd, REQ not active\n", SWNUM(c));
			return (FAIL);
		}

		/* load data */
		DPRINTF2("putting byte # %d, = 0x%x\n", i, *data);
		SBC_WR.odr = *data++;

		/* complete req/ack handshake */
		SBC_WR.icr |= SBC_ICR_ACK;
		if (sw_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ, 
		    SI_WAIT_COUNT, 0) != OK) {
			printf("sw%d:  sw_putdata, req not INactive\n", SWNUM(c));
			return (FAIL);
		}
	}
	junk = SBC_RD.clr;			/* clear int */
	if (want_intr) {

		/* CRITICAL CODE SECTION DON'T TOUCH */
		SBC_WR.tcr = TCR_UNSPECIFIED;
		junk = SBC_RD.clr;		/* clear int */
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
sw_getdata(c, phase)
	register struct scsi_ctlr *c;
	register u_short phase;
{
	register struct scsi_sw_reg *swr;
	register u_char data;
	register u_char icr;
	(int)swr = c->c_reg;

	DPRINTF2("sw_getdata: %s phase (0x%x)",sw_str_phase(phase),phase);
	SW_VME_OK(c, swr, "sw_getdata");

	/* wait for target request */
	if (sw_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ, 
	    SI_WAIT_COUNT, 1) != OK) {
		printf("sw%d:  getdata, REQ not active, cbsr 0x%x\n",
			SWNUM(c), SBC_RD.cbsr);
		sw_print_state(swr, c);
		return (-1);
	}

	if ((SBC_RD.cbsr & CBSR_PHASE_BITS) != phase) {
		/* not the phase we expected */
		DPRINTF1("sw_getdata:  unexpected phase, expecting %s\n",
			sw_str_phase(phase));
		return (-1);
	}

	/* grab data and complete req/ack handshake */
	data = SBC_RD.cdr;
	icr = SBC_WR.icr;
	DPRINTF1("  icr= %x  ", icr);
	SBC_WR.icr = icr | SBC_ICR_ACK;

	if (sw_sbc_wait((caddr_t)&SBC_RD.cbsr, SBC_CBSR_REQ, 
	    SI_WAIT_COUNT, 0) != OK) {
		printf("sw%d:  getdata, REQ not inactive\n", SWNUM(c));
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
sw_reset(c, msg_enable)
	register struct scsi_ctlr *c;
	register int msg_enable;
{
	register struct scsi_sw_reg *swr;
	(int)swr = c->c_reg;

	if (msg_enable) {
		printf("sw%d:  resetting scsi bus\n", SWNUM(c));
		sw_print_state(swr, c);
		DEBUG_DELAY(100000);
	}

	/* reset scsi control logic */
	swr->csr = 0;
	DELAY(10);
	swr->csr = SI_CSR_SCSI_RES;
	swr->dma_addr = 0;
	swr->dma_count = 0;

	/* issue scsi bus reset (make sure interrupts from sbc are disabled) */
	SBC_WR.icr = SBC_ICR_RST;
	DELAY(1000);
	SBC_WR.icr = 0;				/* clear reset */

	/* give reset scsi devices time to recover (> 2 Sec) */
	DELAY(SI_RESET_DELAY);
	junk = SBC_RD.clr;

	/* Disable sbc interrupts.  Reconnects enabled by si_cmd. */	
	SBC_WR.mr &= ~SBC_MR_DMA;	/* clear phase int */
	swr->csr |= SI_CSR_INTR_EN;

	/* disconnect queue needs to be flushed */
	if (c->c_disqh != NULL) {
		c->c_flags |= SCSI_FLUSH_DISQ;
		c->c_flush = c->c_disqt;
		sw_idle(c);
	}
}


/*
 * Return residual count for a dma.
 */
sw_dmacnt(c)
	register struct scsi_ctlr *c;
{
#ifdef	lint
	c = c;
#endif	lint
	return(0);
}

#endif	NSW > 0
