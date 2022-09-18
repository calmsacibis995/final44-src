/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	st.c,v $
 * Revision 2.2  89/07/12  00:20:46  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 * @(#)st.c 1.13 88/04/06 Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#include <stand/saio.h>
#include <stand/param.h>
#include <sys/buf.h>
#include <sun/dklabel.h>
#include <sun/dkio.h>
#include <stand/screg.h>
#include <stand/sireg.h>
#include <stand/scsi.h>
#include <stand/streg.h>
#include <mon/idprom.h>

/*
 * Driver for Sysgen SC4000 and EMULEX MT-02 SCSI tape controllers.
 * Supports qic11 format only.
 */
extern int scdoit();
#if defined(sun3) || defined(sun4)
extern int sidoit();
#endif sun3 || sun4

#define min(a,b)	((a)<(b)? (a): (b))

#define NSD 1
unsigned long staddrs[NSD] = { 0x0, };

extern int xxprobe(), xxboot();
int stopen(), stclose(), ststrategy();


struct stparam {
	int		st_target;
	int		st_unit;
	int		st_eof;
	int		st_lastcmd;
	int		st_ctype;
#if defined(sun3) || defined(sun4)
	int		st_ha_type;
#endif sun3 || sun4
	struct 		saioreq subsip[1];	/* sip for host adapter */
};

/*
 * DMA-able buffers
 */
#ifdef sun2
/* virtual addresses are precious on Sun-2 */
#define	MAXSTBSIZE	(20*1024)	
#endif
#if defined(sun3) || defined(sun4)
#define	MAXSTBSIZE	(127*512)	
#endif sun3 || sun4
struct stdma {
	char	sbuffer[SENSE_LENGTH];
	char	databuffer[MAXSTBSIZE];
};

#define STSBUF		(((struct stdma *)sip->si_dmaaddr)->sbuffer)
#define STBUF		(((struct stdma *)sip->si_dmaaddr)->databuffer)

#define ISAEMULEX(stp)	(stp->st_ctype == ST_TYPE_EMULEX ? 1 : 0)

/*
 * What resources we need to run
 */
struct devinfo stinfo = {
	0,				/* No device to map in */
	sizeof (struct stdma),
	sizeof (struct stparam),
	NSD,				/* Dummy devices */
	staddrs,			/* Dummy devices */
	MAP_MAINMEM,
	MAXSTBSIZE,			/* transfer size */
};

struct boottab stdriver = {
	"st",	xxprobe, xxboot,
	stopen, stclose, ststrategy,
	"st: SCSI tape", &stinfo
};

#define	TAPE_TARGET		4	/* default SCSI target # for tape */

#define SENSELOC	4	/* sysgen returns sense at this offset */

#define	ROUNDUP(x)	((x + DEV_BSIZE - 1) & ~(DEV_BSIZE - 1))

#if defined(sun3) || defined(sun4)
/*
 * Determine type of host adaptor interface, si or sc.
 * Returns 1 if si host adaptor and 0 if sc host adaptor.
 */
st_probe(sip)
	struct saioreq *sip;
{
	if (se_probe(sip)) {
		return (2);
	} else if (siprobe(sip)) {
		return (1);
	} else {
		return (0);
	}
}
#endif sun3 || sun4

/*
 * Open the SCSI Tape controller
 */
int
stopen(sip)
	register struct saioreq *sip;
{
	register struct stparam *stp;
	register short r;
	register int skip;
	register int i;
	struct scsi_cdb cdb;
	struct scsi_scb scb;

	stp = (struct stparam *) sip->si_devdata;
	bzero( (char *)stp, (sizeof (struct stparam)));

	*stp->subsip = *sip;	/* initialize subsip */

#if defined(sun3) || defined(sun4)
	{
		extern struct boottab scdriver;
		extern struct boottab sidriver;
		extern struct boottab se_driver;

		/* FIXME, find out which scsi interface to use */
		if (st_probe(sip) == 2) {
			stp->st_ha_type = 2;

			/* FIXME, must vector thru table */
			stp->subsip->si_boottab = &se_driver;
		} else if (st_probe(sip) == 1) {
			stp->st_ha_type = 1;

			/* FIXME, must vector thru table */
			stp->subsip->si_boottab = &sidriver;
		} else {
			stp->st_ha_type = 0;

			/* FIXME, must vector thru table */
			stp->subsip->si_boottab = &scdriver;
		}
	}
#endif sun3 || sun4
#ifdef sun2
	{
		extern struct boottab scdriver;

		stp->subsip->si_boottab = &scdriver;	
	}
#endif sun2

	stp->subsip->si_unit = sip->si_unit >> 3;       /* Target number */
	if (stp->subsip->si_unit == 0) {
		stp->subsip->si_unit = TAPE_TARGET;
	}

	r = devopen(stp->subsip);
	if (r < 0) return r;

	/* Logical unit number */
	stp->st_unit = sip->si_unit & 0x07;

	/*
	 * Must wait for tape controller to become ready.
	 * This takes about 10 seconds for the Emulex.
	 */
	/*
	 * Test for the controller being ready. First test will fail if
	 * the SCSI bus is permanently busy or if a previous op was 
	 * interrupted in mid-transfer. Second one should work.
	 */
	for (i = 0; i < 2; i++) {
		bzero((char *) &scb, sizeof scb);
		bzero((char *) &cdb, SC_GROUP_0_SIZE);
		cdb.scc_cmd = SC_TEST_UNIT_READY;
		cdb.scc0_count = 0;
		stp->subsip->si_cc = 0;
		stp->subsip->si_ma = 0;
#if defined(sun3) || defined(sun4)
		if (stp->st_ha_type == 2)
			r = se_doit(&cdb, &scb, stp->subsip);
		else if (stp->st_ha_type == 1)
			r = sidoit(&cdb, &scb, stp->subsip);
		else
#endif sun3 || sun4
			r = scdoit(&cdb, &scb, stp->subsip);
	}

	/* 
	 * To figure out what type of tape controller is out there we send 
	 * a REQUEST_SENSE command and see how much sense data comes back.  
	 */
	bzero((char *) &scb, sizeof scb);
	bzero((char *) &cdb, SC_GROUP_0_SIZE);
	stp->st_ctype = ST_TYPE_EMULEX;
	cdb.scc_cmd = SC_REQUEST_SENSE;
	stp->subsip->si_cc = cdb.scc0_count = ST_EMULEX_SENSE_LEN;
	stp->subsip->si_ma = STSBUF;
#if defined(sun3) || defined(sun4)
	if (stp->st_ha_type == 2)
		r = se_doit(&cdb, &scb, stp->subsip);
	else if (stp->st_ha_type == 1)
		r = sidoit(&cdb, &scb, stp->subsip);
	else
#endif sun3 || sun4
		r = scdoit(&cdb, &scb, stp->subsip);
	if (r != ST_EMULEX_SENSE_LEN) {
		bzero((char *) &cdb, SC_GROUP_0_SIZE);
		bzero((char *) &scb, sizeof scb);
	        stp->st_ctype = ST_TYPE_SYSGEN;
		cdb.scc_cmd = SC_REQUEST_SENSE;
		stp->subsip->si_cc = cdb.scc0_count = ST_SYSGEN_SENSE_LEN;
		stp->subsip->si_ma = STSBUF;
#if defined(sun3) || defined(sun4)
		if (stp->st_ha_type == 2)
			r = se_doit(&cdb, &scb, stp->subsip);
		else if (stp->st_ha_type == 1)
			r = sidoit(&cdb, &scb, stp->subsip);
		else
#endif sun3 || sun4
			r = scdoit(&cdb, &scb, stp->subsip);
		if (r == -1) {
			printf("stopen: cannot get sense, %d\n", r);
			return (-1);
		}
	} 

	/* 
	 * Default format mode for emulex is qic24.
	 * Needs to be qic11.
	 */
	if (ISAEMULEX(stp)) {
		sip->si_cc = EM_MS_PL_LEN;
		if (stcmd(SC_QIC11, sip, 1) == 0) {
			printf("stopen: mode select command fail");
			return (-1);
		}
	}

	/*
	 * Rewind a few times until it works.  First one will fail if
	 * the SCSI bus is permanently busy if a previous op was interrupted
	 * in mid-transfer.  Second one will fail with POR status, after
	 * the scsi bus is reset from the busy.  Third one should work.  
	 */
	sip->si_cc = 0;
	if (stcmd(SC_REWIND, sip, 0) == 0 &&
	    stcmd(SC_REWIND, sip, 0) == 0 &&
	    stcmd(SC_REWIND, sip, 1) == 0) {
		return (-1);
	}
	sip->si_cc = 512;
	sip->si_ma = STSBUF;
	if (stcmd(SC_READ, sip, 0) == -2) {
		sip->si_cc = 0;
		stcmd(SC_QIC24, sip, 1);
	}
	sip->si_cc = 0;
	stcmd(SC_REWIND, sip, 1); /* rewind again to be safe */
	skip = sip->si_boff;
	while (skip--) {
		sip->si_cc = 0;
		if (stcmd(SC_SPACE_FILE, sip, 1) == 0) {
			return (-1);
		}
	}
	stp->st_eof = 0;
	stp->st_lastcmd = 0;
	return (0);
}

/*
 * Close the tape drive.
 */
stclose(sip)
	register struct saioreq *sip;
{
	register struct stparam *stp;

	stp = (struct stparam *) sip->si_devdata;
	if (stp->st_lastcmd == SC_WRITE) {
		(void) stcmd(SC_WRITE_FILE_MARK, sip, 0);
	}
	(void) stcmd(SC_REWIND, sip, 0);
	if (ISAEMULEX(stp)) {
		sip->si_cc = EM_MS_PL_LEN;
		if (stcmd(SC_QIC11, sip, 1) == 0) {
			printf("stclose: mode select command fail");
			return (-1);
		}
	} else {
		/* it seems stupid to do a mode select when we close! */
		sip->si_cc = 0;
#ifdef NOTDEF
		if (stcmd(SC_QIC11, sip, 1) == 0) {
			printf("stclose: mode select command fail");
			return (-1);
		}
#endif NOTDEF
	}
	return (0);
}


/*
 * Perform a read or write of the SCSI tape.
 */
int
ststrategy(sip, rw)
	register struct saioreq *sip;
	int rw;
{
	register struct stparam *stp;

	stp = (struct stparam *) sip->si_devdata;
	if (stp->st_eof) {
		stp->st_eof = 0;
		return (0);
	}
	return (stcmd(rw == WRITE ? SC_WRITE : SC_READ, sip, 1));
}

/*
 * Execute a scsi tape command
 */
int
stcmd(cmd, sip, errprint)
	int cmd;
	register struct saioreq *sip;
	int errprint;
{
	static char pass = 0;
	register struct st_emulex_mspl *mode;
	register int r, i, c;
	register char *buf;
	register struct stparam *stp;
	struct scsi_cdb cdb, scdb;
	struct scsi_scb scb, sscb;
	int count;
	int qic;
	int sense_length;
	struct st_emulex_sense *ems;
	struct st_sysgen_sense *scs;

#ifdef	DEBUG
	{
		if ( cmd == SC_QIC11 )
			buf = "qic11";
		else if (cmd == SC_REWIND )
			buf = "rewind";
		else if ( cmd == SC_QIC24 )
			buf = "qic24";
		else if ( cmd == SC_READ )
			buf = "read";
		else if ( cmd == SC_WRITE )
			buf = "write";
		else if ( cmd == SC_SPACE_FILE )
			buf = "space file";
		else
			buf = "???";
		printf("stcmd: %s (%x) (%d,%d,%d) bn %d ma %x cc %d flgs %o\n",
			buf,cmd,sip->si_ctlr,sip->si_unit,sip->si_boff,
			sip->si_bn,sip->si_ma,sip->si_cc,sip->si_flgs&0xff);
	}
#endif
again:
	count = sip->si_cc;
#ifdef sun4
	count &= 0xffff;
#endif
	stp = (struct stparam *)sip->si_devdata;
	buf =  sip->si_ma;

	if (cmd == SC_WRITE && buf != STBUF) {
		bcopy(buf, STBUF, (unsigned)count);
	}

	/* set up cdb */
	bzero((char *) &scb, sizeof scb);
	bzero((char *) &cdb, SC_GROUP_0_SIZE);
	cdb.scc_cmd = cmd;
	cdb.scc_lun = stp->st_unit;
	c = ROUNDUP(count) / DEV_BSIZE;
	cdb.high_count = c >> 16;
	cdb.mid_count = (c >> 8) & 0xFF;
	cdb.low_count = c & 0xFF;
	stp->subsip->si_ma = STBUF;
	stp->subsip->si_cc = ROUNDUP(count);

	/* some fields in the cdb are command specific */
	switch (cmd) {

	case SC_QIC11:
	        stp->subsip->si_ma = 0;
	        stp->subsip->si_cc = 0; 
		if (ISAEMULEX(stp)) {
			qic = ST_EMULEX_QIC11;
			cdb.scc_cmd = SC_MODE_SELECT;
			goto MODE;
		} else {
			cdb.scc_cmd = SC_QIC02;
			cdb.high_count = ST_SYSGEN_QIC11;
			break;
		}
		/* NOTREACHED */

	case SC_QIC24:
	        stp->subsip->si_ma = 0;
	        stp->subsip->si_cc = 0; 
		if (ISAEMULEX(stp)) {
			qic = ST_EMULEX_QIC24;
			cdb.scc_cmd = SC_MODE_SELECT;
			goto MODE;
		} else {
			cdb.scc_cmd = SC_QIC02;
			cdb.high_count = ST_SYSGEN_QIC24;
			break;
		}
		/* NOTREACHED */
MODE:
	case SC_MODE_SELECT:
 		mode = (struct st_emulex_mspl *)STSBUF;
		bzero(mode, sizeof(*mode));
		mode->hdr.bufm = 1;
		mode->bd.density = qic;
		mode->hdr.bd_len = EM_MS_BD_LEN;
		stp->subsip->si_ma = (char *)mode;
		stp->subsip->si_cc = cdb.scc0_count = EM_MS_PL_LEN;
		break;

	case SC_SPACE_FILE:
		cdb.scc_cmd = SC_SPACE;	/* the real SCSI cmd */
		cdb.t_code = 1;		/* space file, not rec */
		cdb.low_count = 1;	/* space 1 file, not 0 */
		stp->subsip->si_ma = 0;
		stp->subsip->si_cc = 0;
		break;

	case SC_WRITE_FILE_MARK:
		cdb.scc0_count = 1;	
		/* fall through... */

	case SC_TEST_UNIT_READY:
	case SC_REWIND:
	case SC_LOAD:
		stp->subsip->si_ma = 0;
		stp->subsip->si_cc = 0;
		break;

	case SC_READ:
	case SC_WRITE:
 		if (ISAEMULEX(stp)) {
		        cdb.t_code = 1;
		}
		break;

	default:
		if (errprint)
			printf("st: unknown command\n");
		return (0);
	}

#ifdef	DEBUG
	printf("stcmd: doit, ma %x\n",stp->subsip->si_ma);
#endif

	/* execute the command */
#if defined(sun3) || defined(sun4)
	if (stp->st_ha_type == 2)
		r = se_doit(&cdb, &scb, stp->subsip);
	else if (stp->st_ha_type)
		r = sidoit(&cdb, &scb, stp->subsip);
	else
#endif sun3 || sun4
		r = scdoit(&cdb, &scb, stp->subsip);

#ifdef sun4
	r &= 0xffff;
#endif

#ifdef	DEBUG
	printf("stcmd: r = %d\n",r);
#endif
	/* allow for tape blocking */
	if (r > count) {
#ifdef	DEBUG
		printf("stcmd: round down to %d\n",count);
#endif
		r = count;
	}
	if(scb.busy) {
		if(pass++ < 30) {
			DELAY(5*100000);
			goto again;	
		} else {
			printf("st: unit busy too long - probable MHFU\n");
			return(0);
		}
	}

	/* error */
	if (r == -1) {
#ifdef	DEBUG
		printf("stcmd: r == -1\n");
#endif
		return (0);
	}

	if (cmd == SC_READ) {
#ifdef	DEBUG
		if(min(count,r))
			printf("stcmd: bcopying %d\n",(unsigned)(min(count,r)));
#endif
		if (min(count, r))
			bcopy(STBUF, buf, (unsigned)(min(count, r)));
	}

	/* we may need to get sense data */
	if (scb.chk) {
#ifdef	DEBUG
		printf("st: chk\n");
#endif
		bzero((char *) &sscb, sizeof sscb);
		bzero((char *) &scdb, SC_GROUP_0_SIZE);
		scdb.scc_cmd = SC_REQUEST_SENSE;
		scdb.scc_lun = stp->st_unit;
		if (ISAEMULEX(stp)) {
			sense_length = stp->subsip->si_cc =
			    scdb.scc0_count = ST_EMULEX_SENSE_LEN;
		} else {
			sense_length = stp->subsip->si_cc = 
			    scdb.scc0_count = ST_SYSGEN_SENSE_LEN;
		}
		stp->subsip->si_ma = STSBUF;
#if defined(sun3) || defined(sun4)
		if (stp->st_ha_type == 2)
			i = se_doit(&scdb, &sscb, stp->subsip );
		else if (stp->st_ha_type == 1)
			i = sidoit(&scdb, &sscb, stp->subsip );
		else
#endif sun3 || sun4
			i = scdoit(&scdb, &sscb, stp->subsip );
#ifdef sun4
i &= 0xffff;
#endif
		if (i != sense_length) {
			if (errprint) {
				printf("st: sense error i %d sense_length %d\n",
					i, sense_length);
			}
			stp->st_eof = 1;
			return (0);
		} 
		if (ISAEMULEX(stp)) {
			ems = (struct st_emulex_sense *)STSBUF;
			if ((ems->ext_sense.key == 0x8) &&
			       (ems->error == 0x34)) {
				stp->st_eof = 1;
				return(-2);
			} else if ((ems->ext_sense.key == 0x1) &&
			       (ems->error == 0x18)) {
				if(errprint)
					printf("st: soft data error\n");
			} else if(ems->ext_sense.key==0x0 && ems->error==0x1c) {
				/* eof */
				stp->st_eof = 1;
				return(r);
			} else if(errprint) {
				stp->st_eof = 1;
				printf("st: error:\n");
				printf("\tsense key is %x", 
				    ems->ext_sense.key);
				printf("\terror is %x\n",
				    ems->error);
				return(-1);
			}
			/* another way of catching a file mark...*/
			if (ems->ext_sense.fil_mk) {
				stp->st_eof = 1;
				return(r);
			}
		} else  {
			scs = (struct st_sysgen_sense *)STSBUF;
			stp->st_eof = 1;
			if ((*(unsigned short *)&STSBUF[SENSELOC] & 0xEFF0)
				== 0x86a0)
				return(-2);
			if ((scs->qic_sense.file_mark == 0) && errprint) {
				printf("st: error %x\n", 
					*(unsigned short *)&STSBUF[SENSELOC]);
			}
			return (r);
		}
	}
	if (r >= count) {
#ifdef	DEBUG
		printf("stcmd: returning %d\n",count?count:1);
#endif
		return (count ? count : 1);
	} else {
		if (errprint) {
			printf("st: short transfer\n");
		}
#ifdef	DEBUG
		printf("stcmd: returning %d\n",r);
#endif
		return (r);
	}
}
