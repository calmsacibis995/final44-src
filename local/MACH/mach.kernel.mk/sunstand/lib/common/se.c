/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	se.c,v $
 * Revision 2.2  89/07/12  00:20:28  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 * @(#)se.c 1.7 88/02/08 Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#include <sys/types.h>
#include <sys/buf.h>
#include <sun/dklabel.h>
#include <sun/dkio.h>
#include <stand/screg.h>
#include <stand/sereg.h>
#include <stand/scsi.h>
#include <stand/saio.h>
#include <mon/sunromvec.h>
#include <mon/idprom.h>

/*
 * Low-level routines common to all devices on the SCSI bus.
 */

/*
 * Interface to the routines in this module is via a second "se_p"
 * structure contained in the caller's local variables.
 *
 * This "se_p" must be initialized with se_p->si_boottab = se_driver
 * and must then be devopen()ed before any I/O can be done.
 *
 * The device must be closed with devclose().
 */


/* how si addresses look to the si vme scsi dma hardware */
#define	SI_VME_DMA_ADDR(x)	(((int)x)&0x000FFFFF)

/* how si addresses look to the sun3/50 scsi dma hardware */
#define	SI_OB_DMA_ADDR(x)	(((int)x)&0x00FFFFFF)
struct sidma {
	struct udc_table	udct;	/* dma information for udc */
};

/*
 * The interfaces we export
 */
extern char *devalloc();
extern char *resalloc();
extern int nullsys();
int se_open();

struct boottab se_driver =
	{ "sd",	nullsys,	nullsys,	se_open,	nullsys,
		nullsys,	"",	0};


#define	SE_VME_BASE	0x300000
#define	SE_BUFF_SIZE	0x00010000

/*
 * Probe for se host adaptor interface. 
 * Return 1 if found one, 0 otherwise.
 */
int
se_probe(se_p)
register struct saioreq	*se_p;
{
	register struct scsi_si_reg *se_r;
	struct idprom id;
	register int base;
	register int ctlr;
	enum MAPTYPES space;

	/* determine type of se interface */
	if (idprom(IDFORM_1, &id) == IDFORM_1) {
		base = SE_VME_BASE;
		space = MAP_VME24A16D;
	} else {
		return (0);
	}

	/* get base address of registers */
	ctlr = base;

	/* now map it in */
	if ((se_r = (struct scsi_si_reg *)devalloc(space, ctlr, 
	    sizeof(struct scsi_si_reg))) == 0) {
		return (0);
	}
	
	/*
	 * SE vme scsi host adaptor occupies 72K bytes in the vme 
	 * address space. SC vme scsi host adaptor occupies 4K 
	 * bytes in the vme address space.
	 * SE control/status register should always return 0x0402 after
	 * filling with zeroes.
	 */
	if (peek((short *)&se_r->csr) != -1) {
		se_r->csr = 0x0000;
		if (peek((short *)&se_r->csr) == 0x0402) {
			return(1);
		}
	}
	return (0);
}

/*
 * Open the SCSI host adapter.
 */
int
se_open(se_p)
register struct saioreq	*se_p;
{
	register struct scsi_si_reg *se_r;
	struct idprom id;
	register int base;
	enum MAPTYPES space;

	/* determine type of si interface */
	if (idprom(IDFORM_1, &id) == IDFORM_1) {
		base = SE_VME_BASE;
		space = MAP_VME24A16D;
	} else {
		return (-1);
	}

	/* get base address of registers */
	if (se_p->si_ctlr < 3) {
		se_p->si_ctlr = base;
	} else {
		return (-1);
	}

	/* now map it in */
	se_p->si_devaddr = devalloc(space, se_p->si_ctlr, 
	    sizeof(struct scsi_si_reg));
	if (se_p->si_devaddr == 0) {
		return (-1);
	}

	/* allocate dma resources */
	se_p->si_dmaaddr = 0;

	/* reset registers */
	se_r = (struct scsi_si_reg *) se_p->si_devaddr;
	se_r->csr = 0;
	DELAY(10);
	se_r->csr = SI_CSR_SCSI_RES;
	se_r->dma_cntr = 0;
	se_r->dma_addr = 0;
	return (0);
}

/*
 * Write a command to the SCSI bus.
 *
 * The supplied se_p is the one opened by se_open().
 * DMA is done based on se_p->si_ma and se_p->si_cc.
 *
 * Returns -1 for error, otherwise returns the residual count not DMAed
 * (zero for success).
 *
 * FIXME, this must be accessed via a boottab vector,
 * to allow host adap to switch.
 * Must pass cdb, scb in se_p somewhere...
 */
int
se_doit(cdb, scb, se_p)
struct scsi_cdb *cdb;
struct scsi_scb *scb;
register struct saioreq *se_p;
{
	register struct scsi_si_reg *se_r;
	register char *cp;
	register int i;
	register int b;
	register int ob;
	u_char junk;

	/* get to scsi control logic registers */
	se_r = (struct scsi_si_reg *) se_p->si_devaddr;
	if (se_p->si_dmaaddr) {
		ob = 1;
	} else {
		ob = 0;
	}

	i = 100000;
	for(;;) {
		if ((se_r->sbc_rreg.cbsr & SBC_CBSR_BSY) == 0) {
			break;
		}
		if (i-- <= 0) {
			se_reset(se_r);
			return (-1);
		}
	}

	/* select target */
	se_r->sbc_wreg.odr = (1 << se_p->si_unit) | SI_HOST_ID;
	se_r->sbc_wreg.icr = SBC_ICR_DATA;
	se_r->sbc_wreg.icr |= SBC_ICR_SEL;

	/* wait for target to acknowledge our selection */
	if (se_sbc_wait((caddr_t)&se_r->sbc_rreg.cbsr, SBC_CBSR_BSY, 1) == 0) {
		sc_error("sel, cbsr bsy never set");
		goto failed;
	}
	se_r->sbc_wreg.icr = 0;

	/* do initial dma setup - also reset dma_count for vme */
	se_r->dma_cntr = 0;
	if (se_p->si_cc > 0) {
		if ((cdb->scc_cmd == SC_READ) || 
		    (cdb->scc_cmd == SC_REQUEST_SENSE)) {
			se_r->csr &= ~SI_CSR_SEND;
		} else {
			se_r->csr |= SI_CSR_SEND;
			bcopy(se_p->si_ma,&se_r->dma_buf[0],se_p->si_cc);
		}
	}

	/* put command onto scsi bus */
	cp = (char *)cdb;
	if (se_putbyte((struct scsi_si_reg *)se_r, PHASE_COMMAND,
	    (u_char *)cp, SC_GROUP_0_SIZE) == 0) {
		sc_error("put of cmd onto scsi bus failed");
		goto failed;
	}

	/* finish dma setup and wait for dma completion */
	if (se_p->si_cc > 0) {
		se_r->dma_addr = 0;
		se_r->dma_cntr = se_p->si_cc;

	/* setup sbc and start dma */
		se_r->sbc_wreg.mr |= SBC_MR_DMA;
		if ((cdb->scc_cmd == SC_READ) || 
		    (cdb->scc_cmd == SC_REQUEST_SENSE)) {
			se_r->sbc_wreg.tcr = TCR_DATA_IN;
			se_r->sbc_wreg.ircv = 0;
		} else {
			se_r->sbc_wreg.tcr = TCR_DATA_OUT;
			se_r->sbc_wreg.icr = SBC_ICR_DATA;
			se_r->sbc_wreg.send = 0;
		}

	/* wait for dma completion */
		if (se_wait(&se_r->csr, SI_CSR_SBC_IP, 1) == 0) {
			sc_error("dma never completed");
			se_dma_cleanup(se_r);
			goto failed;
		}

	/* check reason for dma completion */
		if (se_r->csr & SI_CSR_SBC_IP) {
			/* dma operation should end with a phase mismatch */
			se_sbc_wait((caddr_t)&se_r->sbc_rreg.bsr,
			    SBC_BSR_PMTCH, 0);
		} else {
			sc_error("dma overrun");
			se_dma_cleanup(se_r);
			goto failed;
		}

		/* handle special dma recv situations */
		if ((cdb->scc_cmd == SC_READ) || 
		    (cdb->scc_cmd == SC_REQUEST_SENSE)) {
			bcopy(&se_r->dma_buf[0],se_p->si_ma,se_p->si_cc);
		}
		else {
			/* on writes counter off by one */
			se_r->dma_cntr++;
		}

		/* clear sbc interrupt */
		junk = se_r->sbc_rreg.clr;

		/* cleanup after a dma operation */
		se_dma_cleanup(se_r);
	}

	/* get status */
	cp = (char *)scb;
	for (i = 0;;) {
		b = se_getbyte(se_r, PHASE_STATUS);
		if (b == -1) {
			break;
		}
		if (i < STATUS_LEN) {
			cp[i++] = b;
		}
	}
	b = se_getbyte(se_r, PHASE_MSG_IN);
	if (b != SC_COMMAND_COMPLETE) {
		if (b >= 0) {
		/* if not, se_getbyte already printed msg */
			sc_error("invalid message");
		}
		goto failed;
	}
	return (se_p->si_cc - se_r->dma_cntr);

failed:
	se_reset(se_r);
	return (-1);
}

/*
 * Reset some register information after a dma operation.
 */
se_dma_cleanup(se_r)
register struct scsi_si_reg *se_r;
{
	se_r->dma_addr = 0;
	se_r->sbc_wreg.mr &= ~SBC_MR_DMA;
	se_r->sbc_wreg.icr = 0;
	se_r->sbc_wreg.tcr = 0;
}

/*
 * Wait for a condition to be (de)asserted.
 */
se_wait(reg, cond, set)
register u_short *reg;
register u_short cond;
register int set;
{
	register int i;
	register u_short regval;
	for (i = 0; i < 6000000; i++) {
		regval = *reg;
		if ((set == 1) && ((regval & cond) == cond)) {
			return (1);
		}
		if ((set == 0) && ((regval & cond) != cond) ){
			return (1);
		} 
		DELAY(100);
	}
	return (0);
}

/*
 * Wait for a condition to be (de)asserted on the scsi bus.
 */
se_sbc_wait(reg, cond, set)
register caddr_t reg;
register u_char cond;
register int set;
{
	register int i;
	register u_char regval;

	for (i = 0; i < 6000000; i++) {
		regval = *reg;
		if ((set == 1) && ((regval & cond) == cond)) {
			return (1);
		}
		if ((set == 0) && ((regval & cond) != cond)) {
			return (1);
		} 
		DELAY(100);
	}
	return (0);
}

/*
 * Put a byte onto the scsi bus.
 */
se_putbyte(se_r, phase, data, numbytes)
register struct scsi_si_reg *se_r;
register u_short phase;
register u_char *data;
register int numbytes;
{
	register int i;

	/* set up tcr so phase match will occur */
	if (phase == PHASE_COMMAND) {
		se_r->sbc_wreg.tcr = TCR_COMMAND;
	} else if (phase == PHASE_MSG_OUT) {
		se_r->sbc_wreg.tcr = TCR_MSG_OUT;
	} else {
		sc_error("putbyte, bad phase specified");
		return (0);
	}

	/* put all bytes onto scsi bus */
	for (i = 0; i < numbytes; i++) {
	/* wait for target to request a byte */
		if (se_sbc_wait((caddr_t)&se_r->sbc_rreg.cbsr,
					SBC_CBSR_REQ, 1) == 0) {
			sc_error("putbyte: target never set REQ");
			return (0);
		}

		/* load data for transfer */
		se_r->sbc_wreg.odr = *data++;
		se_r->sbc_wreg.icr = SBC_ICR_DATA;

		/* make sure phase match occurred */
		if ((se_r->sbc_rreg.bsr & SBC_BSR_PMTCH) == 0) {
			sc_error("putbyte: phase mismatch");
			return (0);
		}

		/* complete req/ack handshake */
		se_r->sbc_wreg.icr |= SBC_ICR_ACK;
		if (se_sbc_wait((caddr_t)&se_r->sbc_rreg.cbsr,
					 SBC_CBSR_REQ, 0) == 0) {
			sc_error("putbyte: target never released REQ");
			return (0);
		}
		se_r->sbc_wreg.icr = 0;
	}
	se_r->sbc_wreg.tcr = 0;
	return (1);
}

/*
 * Get a byte from the scsi bus.
 */
se_getbyte(se_r, phase)
register struct scsi_si_reg *se_r;
register u_short phase;
{
	register u_char data;

	/* set up tcr so a phase match will occur */
	if (phase == PHASE_STATUS) {
		se_r->sbc_wreg.tcr = TCR_STATUS;
	} else if (phase == PHASE_MSG_IN) {
		se_r->sbc_wreg.tcr = TCR_MSG_IN;
	} else {
		sc_error("getbyte, bad phase specified");
		return (-1);
	}

	/* wait for target request */
	if (se_sbc_wait((caddr_t)&se_r->sbc_rreg.cbsr, SBC_CBSR_REQ, 1) == 0) {
		sc_error("getbyte: target never set REQ");
		se_r->sbc_wreg.tcr = 0;
		return (-1);
	}

	/* check for correct information phase on scsi bus */
	if (phase != (se_r->sbc_rreg.cbsr & CBSR_PHASE_BITS)) {
		if (phase != PHASE_STATUS) {
			sc_error("getbyte: phase mismatch");
		}
		se_r->sbc_wreg.tcr = 0;
		return (-1);
	}

	/* grab data */
	data = se_r->sbc_rreg.cdr;
	se_r->sbc_wreg.icr = SBC_ICR_ACK;

	/* complete req/ack handshake */
	if (se_sbc_wait((caddr_t)&se_r->sbc_rreg.cbsr, SBC_CBSR_REQ, 0) == 0) {
		sc_error("getbyte: target never released REQ");
		se_r->sbc_wreg.icr = 0;
		se_r->sbc_wreg.tcr = 0;
		return (-1);
	}
	se_r->sbc_wreg.icr = 0;
	se_r->sbc_wreg.tcr = 0;
	return (data);
}

/*
 * Reset SCSI control logic.
 */
se_reset(se_r)
register struct scsi_si_reg *se_r;
{
	register u_char junk;

	/* issue scsi bus reset */
	se_r->sbc_wreg.icr = SBC_ICR_RST;
	DELAY(100);
	se_r->sbc_wreg.icr = 0;
	junk = se_r->sbc_rreg.clr;
	DELAY(1000);
}

