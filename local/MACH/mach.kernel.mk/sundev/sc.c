/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	sc.c,v $
 * Revision 2.7  89/07/11  17:39:20  jjc
 * 	Changed to include machine dependent header files from machine/ not sun3/ because the Sun 4 uses this device driver too.
 * 	[89/07/06  16:54:40  jjc]
 * 
 * Revision 2.6  89/03/09  21:44:32  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  19:53:43  gm0w
 * 	Added new copyright and fixed includes as part of kernel
 * 	cleanup.
 * 	[89/02/10            jjc]
 * 
 * Revision 2.4  89/01/23  15:28:23  rvb
 * 	Forward declarations for GCC.
 * 	[89/01/22            rvb]
 * 
 * Revision 2.3  88/12/07  17:19:12  mikeg
 * 	Entered new version of this file from SunOS 3.5 into
 * 	the RCS kernel source tree.
 * 	[88/12/01  11:04:11  mikeg]
 * 
 * 14-Aug-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Upgraded to SunOS 3.5 with some help from Jon Hale at Mt. Xinu.
 *
 *  5-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Conditionalized include of "pte.h" on whether MACH_VM is
 *	not defined.
 *
 */
/* @(#)sc.c       1.1 87/12/21 Copyr 1987 Sun Micro */
#include <sc.h>
#if	NSC > 0

#ifndef	lint
static char sccsid[] = "@(#)sc.c       1.1 87/12/21 Copyr 1987 Sun Micro";
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
#include <sundev/screg.h>
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
#include <sundev/screg.h>
#include <sundev/scsi.h>
#endif	REL4



#define SCNUM(sc)	(sc - scctlrs)
#define SCUNIT(dev)     (minor(dev) & 0x03)

struct	scsi_ctlr scctlrs[NSC];
int	scprobe(), scslave(), scattach(), scgo(), scdone(), scpoll();
int	scustart(), scstart(), sc_cmd(), sc_getstatus(), sc_cmdwait();
int	sc_off(), sc_reset(), sc_dmacnt(), sc_deque();
#ifdef	__GNU__
static int sc_wait();
static int sc_putbyte();
static int sc_idle();
#endif	__GNU__

struct	mb_ctlr *scinfo[NSC];
extern struct mb_device *sdinfo[];
struct	mb_driver scdriver = {
	scprobe, scslave, scattach, scgo, scdone, scpoll,
	sizeof (struct scsi_ha_reg), "sd", sdinfo, "sc", scinfo, MDR_BIODMA,
};

/* routines available to devices for mainbus scsi host adaptor */
struct scsi_ctlr_subr scsubr = {
	scustart, scstart, scdone, sc_cmd, sc_getstatus, sc_cmdwait,
	sc_off, sc_reset, sc_dmacnt, scgo, sc_deque,
};

extern short scsi_debug;
extern int scsi_ntype;
extern struct scsi_unit_subr scsi_unit_subr[];



/*
 * possible return values from sc_cmd, sc_putdata and sc_putcmd.
 */
#define OK		0	/* successful */
#define FAIL		1	/* failed maybe recoverable */
#define HARD_FAIL	2	/* failed not recoverable */
#define SCSI_FAIL	3	/* failed due to scsi bus fault */

/*
 * possible argument values for sc_reset
 */
#define NO_MSG		0	/* don't print reset warning message */
#define PRINT_MSG	1	/* print reset warning message */



#ifdef	SCSI_DEBUG
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
#define DEBUG_DELAY(cnt)
#define DPRINTF(str) 
#define DPRINTF1(str, arg2) 
#define DPRINTF2(str, arg1, arg2) 
#define EPRINTF(str) 
#define EPRINTF1(str, arg2) 
#define EPRINTF2(str, arg1, arg2) 
#endif	SCSI_DEBUG


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



/*
 * Determine existence of SCSI host adapter.
 * Returns 0 for failure, size of sc data structure if ok.
 */
scprobe(reg, ctlr)
	register struct scsi_ha_reg *reg;
	register int ctlr;
{
	register struct scsi_ctlr *c;

	/* probe for different scsi host adaptor interfaces */
	c = &scctlrs[ctlr];
	if (peekc((char *)&reg->dma_count) == -1) {
		return (0);
	}
	reg->dma_count = 0x6789;
	if (reg->dma_count != 0x6789) {
		return (0);
	}
	EPRINTF2("sc%d:  scprobe: reg= 0x%x", ctlr, (u_int)reg);
	EPRINTF1(",  c= 0x%x\n", (u_int)c );

	/* init controller information */
	c->c_flags = SCSI_PRESENT;
	c->c_reg = (int)reg;
	c->c_ss = &scsubr;
	sc_reset(c, NO_MSG);
	return (sizeof (struct scsi_ha_reg));
}


/*
 * See if a slave exists.
 * Since it may exist but be powered off, we always say yes.
 */
/*ARGSUSED*/
scslave(md, reg)
	struct mb_device *md;
	register struct scsi_ha_reg *reg;
{
	register struct scsi_unit *un;
	register int type;
	/* DPRINTF("scslave:\n"); */

#ifdef	lint
	reg = reg;				/* use it or lose it */
#endif	lint

	/*
	 * This kludge allows autoconfig to print out "sd" for
	 * disks and "st" for tapes.  The problem is that there
	 * is only one md_driver for scsi devices.
	 */
	type = TYPE(md->md_flags);
	if (type >= scsi_ntype) {
		panic("scslave:  unknown type in md_flags\n");
	}

	/* link unit to its controller */
	un = (struct scsi_unit *)(*scsi_unit_subr[type].ss_unit_ptr)(md);
	if (un == 0) {
		panic("scslave:  md_flags scsi type not configured\n");
	}
	un->un_c = &scctlrs[md->md_ctlr];
	md->md_driver->mdr_dname = scsi_unit_subr[type].ss_devname;
	return (1);
}


/*
 * Attach device (boot time).
 */
scattach(md)
	register struct mb_device *md;
{
	register struct mb_ctlr *mc = md->md_mc;
	register struct scsi_ctlr *c = &scctlrs[md->md_ctlr];
	register int type = TYPE(md->md_flags);
	register struct scsi_ha_reg *reg;

	(int)reg = c->c_reg;

	/* DPRINTF("scattach:\n"); */
	if (type >= scsi_ntype) {
		panic("scattach:  unknown type in md_flags\n");
	}
	(*scsi_unit_subr[type].ss_attach)(md);

	/*
	 * Initialize interrupt register
	 */
	if (mc->mc_intr) {
		/* set up for vectored interrupts - we will pass ctlr ptr */
		reg->intvec = mc->mc_intr->v_vec;
		*(mc->mc_intr->v_vptr) = (int)c;
	} else {
		/* use auto-vectoring */
		reg->intvec = AUTOBASE + mc->mc_intpri;
	}
}


/*
 * SCSI unit start routine.
 * Called by SCSI device drivers.
 * Does not actually start any I/O - just puts the device
 * on the ready queue for the bus.
 */
scustart(un)
	register struct scsi_unit *un;
{
	register struct buf *dp;
	register struct mb_ctlr *mc;

	mc = un->un_mc;
	dp = &un->un_utab;
	/* DPRINTF("scustart:\n"); */

	/*
	 * Caller guarantees: dp->b_actf != NULL && dp->b_active == 0
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
scstart(un)
	register struct scsi_unit *un;
{
	register struct mb_ctlr *mc;
	register struct buf *bp, *dp;

	mc = un->un_mc;
	dp = mc->mc_tab.b_actf;	     /* != NULL guaranteed by caller */
	un = (struct scsi_unit *) dp->b_un.b_addr;
	bp = dp->b_actf;

	/* DPRINTF("scstart:\n"); */
	for (;;) {
		if (bp == NULL) {	  /* no more blocks for this device */
			un->un_utab.b_active = 0;
			dp = mc->mc_tab.b_actf = dp->b_forw;
			if (dp == NULL) {  /* no more devices for this ctlr */
				return;
			}
			un = (struct scsi_unit *) dp->b_un.b_addr;
			bp = dp->b_actf;
		} else {
			if ((*un->un_ss->ss_start)(bp, un)) {
				mc->mc_tab.b_active = 1;
				un->un_c->c_un = un;
				if (bp == &un->un_sbuf  &&
				    ((un->un_flags & SC_UNF_DVMA) == 0)) {
					scgo(mc);
				} else {
					(void) mbgo(mc);
				}
				return;
			}
			dp->b_actf = bp = bp->av_forw;
		}
	}
}


/*
 * Start up a transfer
 * Called via mbgo after buffer is in memory
 */
scgo(mc)
	register struct mb_ctlr *mc;
{
	register struct scsi_unit *un;
	register struct scsi_ctlr *c;
	register struct buf *bp, *dp;
	register int unit;
	register int err;

	c = &scctlrs[mc->mc_ctlr];
	dp = mc->mc_tab.b_actf;
	/* DPRINTF("scgo:\n"); */

	if (dp == NULL || dp->b_actf == NULL) {
		panic("scgo:  queueing error1/n");
	}
	bp = dp->b_actf;
	un = c->c_un;

	if (dp != &un->un_utab) {
		panic("scgo:  queueing error2/n");
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
	if ((err=sc_cmd(c, un, 1)) != OK) {
		if (err == FAIL) {
			EPRINTF("scgo:  sc_cmd FAILED\n");
			(*un->un_ss->ss_intr)(c, 0, SE_RETRYABLE);

		} else if (err == HARD_FAIL) {
			EPRINTF("scgo:  sc_cmd hard FAIL\n");
			(*un->un_ss->ss_intr)(c, 0, SE_FATAL);
			sc_off(c, un);
		}
	}
}


/*
 * Handle a polling SCSI bus interrupt.
 */
scpoll()
{
	register struct scsi_ctlr *c;
	register struct scsi_ha_reg *reg;
	register int serviced = 0;


	for (c = scctlrs; c < &scctlrs[NSC]; c++) {
		if ((c->c_flags & SCSI_PRESENT) == 0)
			continue;
		(int)reg = c->c_reg;
		if ((reg->icr & (ICR_INTERRUPT_REQUEST | ICR_BUS_ERROR)) == 0) {
			continue;
		}
		serviced = 1;
		scintr(c);
	}
	return (serviced);
}


/*
 * Clean up queues, free resources, and start next I/O
 * after I/O finishes.  Called by mbdone after moving
 * read data from Mainbus
 */
scdone(mc)
	register struct mb_ctlr *mc;
{
	register struct buf *bp, *dp;
	register struct scsi_unit *un;
	register struct scsi_ctlr *c;

	bp = mc->mc_tab.b_actf->b_actf;
	c = &scctlrs[mc->mc_ctlr];
	un = c->c_un;
	/* DPRINTF("scdone:\n"); */

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
		scustart(un);

	/* start next I/O on controller */
	if (mc->mc_tab.b_actf && mc->mc_tab.b_active == 0)
		scstart(un);
}


/*
 * Pass a command to the SCSI bus.
 * OK returned if successful.  Otherwise,
 * FAIL returned for recoverable error;
 * HARD_FAIL returned for non-recoverable error; and
 * SCSI_FAIL returned for SCSI bus timing failure.
 */
sc_cmd(c, un, intr)
	register struct scsi_ctlr *c;
	register struct scsi_unit *un;
	register int intr;
{
	register u_char *cp;
	register int i, errct = 0;
	register u_short icr_mode;
	register u_char size;
	register struct scsi_ha_reg *reg;

	(int)reg = c->c_reg;

	/* DPRINTF("sc_cmd:\n"); */
	do {
		/* make sure scsi bus is not continuously busy */
		for (i = SC_WAIT_COUNT; i > 0; i--) {
		        if (!(reg->icr & ICR_BUSY))
		                break;
		        DELAY(10);
		}
		if (i == 0) {
			printf("si%d:  sc_cmd:  scsi bus continuously busy\n",
				SCNUM(c));
			sc_reset(c, PRINT_MSG);
			sc_idle(c);
			return (SCSI_FAIL);
		}

		/* select target and wait for response */
		/*+++wmb (by mjacob) for bug #1004639 */

		reg->icr = 0; /* Make sure SECONDBYTE flag is clear */

		/* ---wmb	*/
		reg->data = (1 << un->un_target) | HOST_ADDR;
		reg->icr = ICR_SELECT;

		/* target never responded to selection */
		if (sc_wait(c, SC_SHORT_WAIT, ICR_BUSY) != OK) {
			reg->data = 0;
			reg->icr = 0;
			return (HARD_FAIL);
		}
		/*
		 * may need to map between the CPU's kernel context address
		 * and the device's DVMA bus address
		 */
		SET_DMA_ADDR(reg, un->un_dma_addr);
		reg->dma_count = ~un->un_dma_count; /* hardware is funny */
		icr_mode = ICR_DMA_ENABLE;
		if (intr) {
			icr_mode |= ICR_INTERRUPT_ENABLE;
			un->un_wantint = 1;
		}

		/* Allow either byte or word transfers.
		 * Note, we trust that DMA count is even.
		 * This seems safe enough since sd & st
		 * worry about this for us.
		 */
		if  ( !(un->un_dma_addr & 0x1)) {
			icr_mode |= ICR_WORD_MODE;
		} else {
			DPRINTF("sc_cmd:  odd byte DMA address\n");
		}
		reg->icr = icr_mode;

		/*
		 * Determine size of the cdb.  Since we're smart, we
		 * look at group code and guess.  If we don't
		 * recognize the group id, we use the specified
		 * cdb length.  If both are zero, use max. size
		 * of data structure.
		 */
		cp = (u_char *) &c->c_cdb;
		if ((size = cdb_size[CDB_GROUPID(c->c_cdb.cmd)]) == 0  &&
		    (size = c->c_un->un_cmd_len) == 0) {
			size = sizeof (struct scsi_cdb);
			printf("sc%d:  invalid cdb size, using size= %d\n",
				SCNUM(c), size);
		}

#ifdef	SCSI_DEBUG
		if (scsi_debug > 2) {
			printf("sc%d:  sc_cmd: target %d command=",
			    SCNUM(c), un->un_target);
			for (i = 0; i < size; i++) {
				printf("  %x", *cp++);
			}
			printf("\n");
			cp = (u_char *) &c->c_cdb;	/* restore cp */
		}
#endif	SCSI_DEBUG

		for (i = 0; i < size; i++) {
			if (sc_putbyte(c, ICR_COMMAND, *cp++) != OK) {
				errct++;
				break;
			}
		}

		if (i == size) {
			/* If not in polled I/O mode, we're done */
			if (intr != 0)
				return (OK);

			/*
			 * If in polled I/O mode, wait for cmd completion
			 * and get the result status, too.
			 */
			if ((sc_cmdwait(c) == OK)  &&
			    (sc_getstatus(c->c_un) == OK)) {
				/* DPRINTF("sc_cmd: cmd ok\n"); */
				return (OK);
			} else {
				EPRINTF("sc_cmd: cmd error\n");
				return (FAIL);
			}
		}

	} while (errct < 5);
	printf("sc%d:  sc_cmd: unrecoverable errors\n", SCNUM(c));
	return (HARD_FAIL);
}


/*
 * Handle a scsi bus interrupt.
 */
scintr(c)
	register struct scsi_ctlr *c;
{
	register int resid;
	register struct scsi_unit *un;
	register struct scsi_ha_reg *reg;

	(int)reg = c->c_reg;
	un = c->c_un;

	/* DPRINTF("scintr:\n"); */
	if (un->un_wantint == 0) {
		if (reg->icr & ICR_BUS_ERROR) {
			printf("sc%d:  scsi bus error (unwanted interrupt)\n",
				SCNUM(c));
		} else {
			printf("sc%d:  spurious interrupt\n", SCNUM(c));
		}
		sc_reset(c, PRINT_MSG);
		sc_idle(c);
		return;
	}
	un->un_wantint = 0;
	resid = (u_short) (~reg->dma_count);
	if (reg->icr & ICR_BUS_ERROR) {
		printf("sc%d:  scsi bus error. icr %x resid %d\n",
			SCNUM(c), (u_short)(reg->icr), resid);
		sc_reset(c, PRINT_MSG);
		sc_idle(c);
		return;
	}
	if (reg->icr & ICR_ODD_LENGTH) {
		if (SCSI_RECV_DATA_CMD(c->c_cdb.cmd)) {
			DVMA[un->un_baddr + un->un_dma_count - resid] =
			    reg->data;
			resid--;
		} else if (SCSI_RECV_DATA_CMD(c->c_cdb.cmd)) {
			resid++;
		} else {
			printf("sc%d:  scsi: odd length without xfer\n",
				SCNUM(c));
		}
	}

#ifdef	SCSI_DEBUG
	if (resid  < 0)
		EPRINTF("scintr:  scsi resid/n");
#endif	SCSI_DEBUG

	if (sc_getstatus(c->c_un) == OK) {
		/* DPRINTF("scintr: no error\n"); */
		(*c->c_un->un_ss->ss_intr)(c, resid, SE_NO_ERROR);
	} else {
		EPRINTF("scintr: error\n");
		(*c->c_un->un_ss->ss_intr)(c, resid, SE_RETRYABLE);
	}
}


/*
 * Bring a unit offline.
 */
/*ARGSUSED*/
sc_off(c, un)
	register struct scsi_ctlr *c;
	register struct scsi_unit *un;
{
	register struct mb_device *md;
	md = un->un_md;
	/* DPRINTF("sc_off:\n"); */

	/*
	 * Be warned, if you take the root device offline,
	 * the system is going to have a heartattack !
	 */
	printf("sc%d:  %s%d, unit offline\n", SCNUM(c),
		scsi_unit_subr[md->md_flags].ss_devname, SCUNIT(un->un_unit));
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
 * Wait for a condition to be (de)asserted on the scsi bus.
 * Returns OK if successful.  Otherwise, returns
 * FAIL.
 */
static
sc_wait(c, wait_count, cond)
	register struct scsi_ctlr *c;
	register int wait_count;
{
	register int i, icr;
	register struct scsi_ha_reg *reg;
	(int)reg = c->c_reg;

	/* DPRINTF("sc_wait:\n"); */

	for (i = 0; i < wait_count; i++) {
		icr = reg->icr;
		if ((icr & cond) == cond) {
			return (OK);
		}
		if (icr & ICR_BUS_ERROR) {
			break;
		}
		DELAY(10);
	}
	DPRINTF("sc_wait: failed\n");
	return (FAIL);
}


/*
 * Wait for a scsi dma request to complete.
 * Called by top level drivers in order to poll for
 * command completion.
 */
sc_cmdwait(c)
	register struct scsi_ctlr *c;
{
	/* DPRINTF("sc_cmdwait:\n"); */
	if (sc_wait(c, SC_WAIT_COUNT, ICR_INTERRUPT_REQUEST) != OK) {
		printf("sc%d:  sc_cmdwait: no interrupt request\n",
			SCNUM(c));
		sc_reset(c, PRINT_MSG);
		return (SCSI_FAIL);
	} else {
		return (OK);
	}
}


/*
 * Put data byte onto the scsi bus.
 * Returns OK if successful, FAIL otherwise.
 */
static
sc_putbyte(c, bits, data)
	register struct scsi_ctlr *c;
	register u_short bits;
	register u_char data;
{
	register int icr;
	register struct scsi_ha_reg *reg;
	(int)reg = c->c_reg;

	/* DPRINTF("sc_putbyte:\n"); */

	if (sc_wait(c, SC_WAIT_COUNT, ICR_REQUEST) != OK) {
		printf("sc%d:  sc_cmdwait: no REQ\n", SCNUM(c));
		return (FAIL);
	}
	icr = reg->icr;
	if ((icr & ICR_BITS) != bits) {
#ifdef	SCSI_DEBUG
		printf("sc_putbyte:  error\n");
		sc_pr_icr("icr is     ", icr);
		sc_pr_icr("waiting for", bits);
#endif	SCSI_DEBUG
		return (FAIL);
	}
	reg->cmd_stat = data;
	return (OK);
}


/*
 * Get data from the scsi bus.
 * Returns a single byte of data, -1 if unsuccessful.
 */
static
sc_getbyte(c, bits)
	register struct scsi_ctlr *c;
{
	register int icr;
	register struct scsi_ha_reg *reg;
	(int)reg = c->c_reg;

	/* DPRINTF("sc_getbyte:\n"); */

	if (sc_wait(c, SC_WAIT_COUNT, ICR_REQUEST) != OK) {
		printf("sc%d:  sc_cmdwait: no REQ\n", SCNUM(c));
		return (-1);
	}
	icr = reg->icr;
	if ((icr & ICR_BITS) != bits) {
		if (bits == ICR_STATUS) {
			return (-1);	/* no more status */
		}
#ifdef	SCSI_DEBUG
		printf("sc_getbyte:  error\n");
		sc_pr_icr("icr is     ", icr);
		sc_pr_icr("waiting for", bits);
#endif	SCSI_DEBUG
		return (-1);
	}
	return (reg->cmd_stat);
}


/*
 * Routine to handle abort SCSI commands which have timed out.
 */
sc_deque(c, un)
	register struct scsi_ctlr *c;
	register struct scsi_unit *un;
{
	register u_int target;
	register u_int lun;
	int s;

	/* Lock out the rest of sc till we've finished the dirty work. */
	target = un->un_target;
	lun = un->un_lun;
#ifdef	lint
	target = target;
	lun = lun;
#endif	lint

	s = splx(pritospl(un->un_mc->mc_intpri));
	un = c->c_un;			/* get current unit */

	/*
	 * If timeout didn't occur on current I/O request,
	 * we've got a problem.
	 */
	if (un->un_mc->mc_tab.b_active != 1 ) {
		EPRINTF("sc_deque:  entry not found\n");
		(void) splx(s);
		return (FAIL);
	}
	EPRINTF("sc_deque:  removing failed request\n");
	(*un->un_ss->ss_intr)(c, un->un_dma_count, SE_TIMEOUT);
	(void) splx(s);
	return (OK);
}


/*
 * Return residual count for dma.
 */
sc_dmacnt(c)
	register struct scsi_ctlr *c;
{
	register struct scsi_ha_reg *reg;
	(int)reg = c->c_reg;

	return ((u_short)(~reg->dma_count));
}


/*
 * Flush current I/O request after SCSI bus reset.
 * If no current I/O request, forget it.
 */
static
sc_idle(c)
	register struct scsi_ctlr *c;
{
	register struct scsi_unit *un;
	un = c->c_un;
	/* DPRINTF("sc_idle:\n"); */

	if (un->un_mc->mc_tab.b_active) {
		/*
		 * Since we reset the bus, we should inform
		 * the top level driver that it's dead.
		 */
		EPRINTF("sc_idle:  returning fatal error\n");
		(*c->c_un->un_ss->ss_intr)(c, 0, SE_FATAL);
	}
}


/*
 * Reset SCSI control logic and bus.
 */
sc_reset(c, msg_enable)
	register struct scsi_ctlr *c;
	register int msg_enable;
{
	register struct scsi_ha_reg *reg;

	(int)reg = c->c_reg;

	/* DPRINTF("sc_reset:\n"); */
	if (msg_enable) {
		printf("sc%d:  resetting scsi bus\n", SCNUM(c));
	}

	reg->icr = ICR_RESET;
	DELAY(50);
	reg->icr = 0;

	/* give reset scsi devices time to recover (> 2 Sec) */
	DELAY(SC_RESET_DELAY);
}


/*
 * Get status bytes from scsi bus.
 */
sc_getstatus(un)
	register struct scsi_unit *un;
{
	register struct scsi_ctlr *c = un->un_c;
	register u_char *cp = (u_char *)&c->c_scb;
	register int i;
	register int b;
	register short retval = OK;
	/* DPRINTF("sc_getstatus:\n"); */

	/* get all the status bytes */
	for (i = 0;;) {
		b = sc_getbyte(c, ICR_STATUS);
		if (b < 0) {
			break;
		}
		if (i < STATUS_LEN) {
			cp[i++] = b;
		}
	}
	/* If status anything but no error, report it. */
	if (cp[0] & SCB_STATUS_MASK)
		retval = FAIL;		/* cmd completed with error */

	/* get command complete message */
	b = sc_getbyte(c, ICR_MESSAGE_IN);
	if (b != SC_COMMAND_COMPLETE) {
#ifdef	SCSI_DEBUG
		if (scsi_debug) {
			printf("sc_getstatus:  Invalid SCSI message: %x\n", b);
			printf("  Status bytes= ");
			for (b = 0; b < i; b++) {
				printf(" %x", cp[b]);
			}
			printf("\n");
		}
#endif	SCSI_DEBUG
		return (FAIL);
	}

#ifdef	SCSI_DEBUG
	if (scsi_debug > 1) {
		printf("sc_getstatus:  status=");
		for (b = 0; b < i; b++) {
			printf(" %x", cp[b]);
		}
		printf("\n");
	}
#endif	SCSI_DEBUG
	return (retval);
}


#ifdef	SCSI_DEBUG
/*
 * Print out the scsi host adapter interface control register.
 */
static
sc_pr_icr(cp, i)
	register char *cp;
{
	printf("\t%s: %x ", cp, i);
	if (i & ICR_PARITY_ERROR)
		printf("Parity err ");
	if (i & ICR_BUS_ERROR)
		printf("Bus err ");
	if (i & ICR_ODD_LENGTH)
		printf("Odd len ");
	if (i & ICR_INTERRUPT_REQUEST)
		printf("Int req ");
	if (i & ICR_REQUEST) {
		printf("Req ");
		switch (i & ICR_BITS) {
		case 0:
			printf("Data out ");
			break;
		case ICR_INPUT_OUTPUT:
			printf("Data in ");
			break;
		case ICR_COMMAND_DATA:
			printf("Command ");
			break;
		case ICR_COMMAND_DATA | ICR_INPUT_OUTPUT:
			printf("Status ");
			break;
		case ICR_MESSAGE | ICR_COMMAND_DATA:
			printf("Msg out ");
			break;
		case ICR_MESSAGE | ICR_COMMAND_DATA | ICR_INPUT_OUTPUT:
			printf("Msg in ");
			break;
		default:
			printf("DCM: %x ", i & ICR_BITS);
			break;
		}
	}
	if (i & ICR_PARITY)
		printf("Parity ");
	if (i & ICR_BUSY)
		printf("Busy ");
	if (i & ICR_SELECT)
		printf("Sel ");
	if (i & ICR_RESET)
		printf("Reset ");
	if (i & ICR_PARITY_ENABLE)
		printf("Par ena ");
	if (i & ICR_WORD_MODE)
		printf("Word mode ");
	if (i & ICR_DMA_ENABLE)
		printf("Dma ena ");
	if (i & ICR_INTERRUPT_ENABLE)
		printf("Int ena ");
	printf("\n");
}


/*
 * Print out status completion block.
 */
static
sc_pr_scb(scbp)
	register struct scsi_scb *scbp;
{
	register u_char *cp;

	cp = (u_char *) scbp;
	printf("scb: %x", cp[0]);
	if (scbp->ext_st1) {
		printf(" %x", cp[1]);
		if (scbp->ext_st2) {
			printf(" %x", cp[2]);
		}
	}
	if (scbp->is) {
		printf(" intermediate status");
	}
	if (scbp->busy) {
		printf(" busy");
	}
	if (scbp->cm) {
		printf(" condition met");
	}
	if (scbp->chk) {
		printf(" check");
	}
	if (scbp->ext_st1 && scbp->ha_er) {
		printf(" host adapter detected error");
	}
	printf("\n");
}
#endif	SCSI_DEBUG
#endif	NSC > 0
