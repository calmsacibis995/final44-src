/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	sd.c,v $
 * Revision 2.2  89/07/12  00:20:21  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 * @(#)sd.c 1.7 88/02/08 Copyright (c) 1985 by Sun Microsystems, Inc.
 */
#include <stand/saio.h>
#include <stand/param.h>
#include <sun/dklabel.h>
#include <sun/dkio.h>
#include <sys/buf.h>
#include <stand/screg.h>
#include <stand/sireg.h>
#include <stand/scsi.h>
#include <mon/sunromvec.h>
#include <mon/idprom.h>

/* For RAM-based code, print detailed error messages */
#if !defined(SDBOOT) && !defined(BOOTBLOCK)
#define SDERRORS
#endif

/*
 * Scsi disk parameter block
 */
struct sdparam {
	int	sd_target;
	int	sd_unit;
	int	sd_boff;		/* block offset of the partition */
	int	sd_nblk;		/* number of blocks in the partition */
#if defined(sun3) || defined(sun4)
	int	sd_ha_type;
#endif sun3 || sun4
	struct saioreq subsip[1];	/* Sip for host adapter */
};

/*
 * Record an error message from scsi
 */
#define DEBUG FIXME

#if (!defined(SDBOOT)) & !defined(STBOOT) & !defined(DEBUG)

#define	sc_error(msg)	scerrmsg = msg
#define DEFERRED_ERRORS
extern char *scerrmsg;

#else

extern sc_error();	/* It's in sc.c */
#undef DEFERRED_ERRORS

#endif

/*
 * Our DMA space
 */
struct sddma {
	char	buffer[MAXBSIZE];
	struct dk_label xlabel[1];
};

#define SDBUF		(((struct sddma *)sip->si_dmaaddr)->buffer)
#define label		(((struct sddma *)sip->si_dmaaddr)->xlabel)

/*
 * What resources we need to run
 */
struct devinfo sdinfo = {
	0,				/* No device to map in */
	sizeof (struct sddma),
	sizeof (struct sdparam),
	0,				/* Dummy devices */
	0,				/* Dummy devices */
	MAP_MAINMEM,
	MAXBSIZE,			/* transfer size */
};

/*
 * The interfaces we export
 */
extern int xxprobe(), xxboot();
int sdopen(), sdclose(), sdstrategy();

struct boottab sddriver = {
	"sd",	xxprobe, xxboot,
	 sdopen, sdclose, sdstrategy,
	"sd: Adaptec SCSI disk", &sdinfo
};

#ifndef BOOTBLOCK

/*
 * Test routine for isspinning() to see if SCSI disk is running.
 */
/*ARGSUSED*/
int
sdspin(sip, dummy)
	struct saioreq *sip;
	int dummy;
{
	int retval;

	sip->si_bn = 0;
	sip->si_cc = 0;
	sip->si_ma = 0;

	retval = sdcmd(SC_TEST_UNIT_READY, sip, 0);
	/* some esdi controllers need to be told twice.. */
	return (retval <= 0 ? sdcmd(SC_TEST_UNIT_READY, sip, 0) : retval);
}
#endif BOOTBLOCK

#if defined(sun3) || defined(sun4)
/*
 * Determine type of host adaptor interface, si or sc.
 * Returns 1 if si host adaptor and 0 if sc host adaptor.
 */
sd_probe(sip)
	struct saioreq *sip;
{
#ifndef sun4
	if (se_probe(sip)) {
		return (2);
	} else 
#endif
	if (siprobe(sip)) {
		return (1);
	} else {
		return (0);
	}
}
#endif sun3 || sun4

/*
 * Open the SCSI Disk controller
 */
sdopen(sip)
	register struct saioreq *sip;
{
	register struct sdparam *sdp;
	register int r;

	sdp = (struct sdparam *)sip->si_devdata;
	bzero( (char *)sdp, (sizeof (struct sdparam)));

	/*
	 * Open the host adapter
	 */
	*sdp->subsip = *sip;		/* Initialize sub-sip */
#if defined(sun3) || defined(sun4)
	{
		extern struct boottab scdriver;
		extern struct boottab sidriver;
		extern struct boottab se_driver;

		/* FIXME, find out which scsi interface to use */
		if (sd_probe(sip) == 2) {
			sdp->sd_ha_type = 2;

			/* FIXME, must vector thru table */
			sdp->subsip->si_boottab = &se_driver;
		} else if (sd_probe(sip) == 1) {
			sdp->sd_ha_type = 1;

			/* FIXME, must vector thru table */
			sdp->subsip->si_boottab = &sidriver;	
		} else {
			sdp->sd_ha_type = 0;

			/* FIXME, must vector thru table */
			sdp->subsip->si_boottab = &scdriver;	
		}

	}
#endif sun3 || sun4
#ifdef sun2
	{
		extern struct boottab scdriver;

		sdp->subsip->si_boottab = &scdriver;	
	}
#endif sun2
	sdp->subsip->si_unit = sip->si_unit >> 2;	/* Target number */
	r = devopen(sdp->subsip);
	if (r < 0) return r;

	sdp->sd_unit = sip->si_unit & 0x03;	/* Logical unit number */

#ifndef BOOTBLOCK
	/*
	 * Check that the disk is up and running...
	 */
	switch (isspinning(sdspin, (char *)sip, 0)) {

	default:	/* Error from sdspin */
	case 0:		/* Disk still not ready */
		/* isspinning has already printed "Giving up..." */
		return (-1);

	case 1:
		break;

	case 2:
		DELAY(1000000);  /* one second delay after spinup */
		break;
	}
#endif BOOTBLOCK

	/*
	 * Actually read the label
	 */
	label->dkl_magic = 0;
	sip->si_ma = (char *)label;
	sip->si_cc = SECSIZE;
	sip->si_bn = 0;		/* Read block #0 */
	if (sdcmd(SC_READ, sip, 1) <= 0) {
		return (-1);
	}
	if (chklabel(label))
		return -1;
	sdp->sd_boff = (unsigned short)(label->dkl_map[sip->si_boff].dkl_cylno)
	    * (unsigned short)(label->dkl_nhead * label->dkl_nsect);
	sdp->sd_nblk = (unsigned short) label->dkl_map[sip->si_boff].dkl_nblk;
	return (0);
}

/*
 * Execute reads or writes for the outside world.
 */
sdstrategy(sip, rw)
	struct saioreq *sip;
	register int rw;
{
	register struct sdparam *sdp = (struct sdparam *)sip->si_devdata;

	if (sip->si_cc > sdp->sd_nblk * SECSIZE) {
		sip->si_cc = sdp->sd_nblk * SECSIZE; 	/* request too big */
	}

	if (sip->si_cc <= 0)				/* request too small */
		return(0);

	rw = sdcmd(rw == WRITE ? SC_WRITE : SC_READ, sip, 1);
	if (rw < 0)
		rw = 0;
	return rw;
}

/*
 * Internal interface to the disk command set
 *
 * Returns the character count read (or 1 if count==0) for success,
 * returns 0 for failure, or -1 for severe unretryable failure.
 */
int
sdcmd(cmd, sip, errprint)
	int cmd;
	register struct saioreq *sip;
	int errprint;
{
	int blkno, acount;
	register char *buf;
	register struct sdparam *sdp;
	struct scsi_cdb cdb, scdb;
	struct scsi_scb scb, sscb;
	register int retry;
	register short r, i, count;

	blkno = sip->si_bn;
	acount = sip->si_cc;
	buf = sip->si_ma;
	sdp = (struct sdparam *)sip->si_devdata;

	if (cmd == SC_WRITE)
		bcopy(buf, SDBUF, (unsigned)acount);

	/* set up cdb */
	bzero((char *) &cdb, SC_GROUP_0_SIZE);
	cdb.scc_cmd = cmd;
	cdb.scc_lun = sdp->sd_unit;
	blkno += sdp->sd_boff;
	FORMG0ADDR(&cdb, blkno);
	count = (acount + SECSIZE -1) & ~(SECSIZE-1);
	cdb.scc0_count = count / SECSIZE;
	retry = 0;
	do {
		sdp->subsip->si_cc = count;
		sdp->subsip->si_ma = SDBUF;
#if defined(sun3) || defined(sun4)
		if (sdp->sd_ha_type == 2)
			r = se_doit(&cdb, &scb, sdp->subsip);
		else if (sdp->sd_ha_type == 1)
			r = sidoit(&cdb, &scb, sdp->subsip);
		else
#endif sun3 || sun4
			r = scdoit(&cdb, &scb, sdp->subsip);
		if (r < 0) 
			return -1; /* Major SCSI bus error, already printed */
		if (scb.chk) {
			bzero((char *) &scdb, SC_GROUP_0_SIZE);
			scdb.scc_cmd = SC_REQUEST_SENSE;
			scdb.scc_lun = sdp->sd_unit;
			scdb.scc0_count = sizeof (struct scsi_sense);
			sdp->subsip->si_cc = scdb.scc0_count;
			sdp->subsip->si_ma = SDBUF;
#if defined(sun3) || defined(sun4)
			if (sdp->sd_ha_type == 2)
				i = se_doit(&scdb, &sscb, sdp->subsip);
			else if (sdp->sd_ha_type == 1)
				i = sidoit(&scdb, &sscb, sdp->subsip);
			else
#endif sun3 || sun4
				i = scdoit(&scdb, &sscb, sdp->subsip);
			if (i >= 4) {	/* all the sense Adaptec gives us */
#ifndef DEFERRED_ERRORS
				if (errprint) sd_pr_sense(SDBUF, i);
#endif  DEFERRED_ERRORS
				continue;
			} else {	/* can't get sense, give up */
				if (errprint) {
					printf("sd: scsi %s\n",
#ifdef DEFERRED_ERRORS
					scerrmsg ? scerrmsg :
#endif DEFERRED_ERRORS
					"sense failed");
				}
				return (0);
			}
		} else if (scb.busy) {
			sc_error("disk busy");
			DELAY(100000);
			continue;
		}
		if (r != count) {
#ifndef DEFERRED_ERRORS
			if (errprint)
				printf("sd: dma count is %d wanted %d\n",
				    r, count);
#endif  DEFERRED_ERRORS
			continue;
		}
		if (cmd == SC_READ)
			bcopy(SDBUF, buf, (unsigned)acount);
#ifdef DEFERRED_ERRORS
		scerrmsg = 0;
#endif DEFERRED_ERRORS
		return (count ? count : 1);
	} while (retry++ < 16);
#ifdef DEFERRED_ERRORS
	if (errprint) {
		if (scb.chk) {
			sd_pr_sense(SDBUF, i);
		} else if (scerrmsg) {
			printf("sd: scsi %s\n", scerrmsg);
		} else if (r != count) {
			printf("sd: dma count is %d wanted %d\n", r, count);
		} else {
			/* we should never get this far */
			printf("sd: retry count exceeded\n");
		}
	}
#endif DEFERRED_ERRORS
	return (0);
}

#ifdef SDERRORS
char	*class_00_errors[] = {
	"No sense",
	"No index signal",
	"No seek complete",
	"Write fault",
	"Drive not ready",
	"Drive not selected",
	"No track 00",
	"Multiple drives selected",
	"No address acknowledged",
	"Media not loaded",
	"Insufficient capacity",
};

char	*class_01_errors[] = {
	"I.D. CRC error",
	"Unrecoverable data error",
	"I.D. address mark not found",
	"Data address mark not found",
	"Record not found",
	"Seek error",
	"DMA timeout error",
	"Write protected",
	"Correctable data check",
	"Bad block found",
	"Interleave error",
	"Data transfer incomplete",
	"Unformatted or bad format on drive",
	"Self test failed",
	"Defective track (media errors)",
};

char	*class_02_errors[] = {
	"Invalid command",
	"Illegal block address",
	"Aborted",
	"Volume overflow",
};

char	**sc_errors[] = {
	class_00_errors,
	class_01_errors,
	class_02_errors,
	0, 0, 0, 0,
};

int	sc_errct[] = {
	sizeof class_00_errors / sizeof (char *),
	sizeof class_01_errors / sizeof (char *),
	sizeof class_02_errors / sizeof (char *),
	0, 0, 0, 0,
};

char	*sc_sense7_keys [] = {
	"No sense",
	"Recoverable error",
	"Not ready",
	"Media error",
	"Hardware error",
	"Illegal request",
	"Media change",
	"Write protect",
	"Diagnostic unique",
	"Vendor unique",
	"Power up failed",
	"Aborted command",
	"Equal",
	"Volume overflow",
};
#endif SDERRORS

/*
 * Print out sense info.
 */
sd_pr_sense(sp, len)
	register unsigned char *sp;
	register int len;
{

#ifndef SDERRORS
	printf("sd: error");
	while (--len >= 0) {
		printf(" %x", *sp++);
	}
	printf("\n");
#else  SDERRORS
#ifdef lint
	len = len;	/* Avoid spurious "len unused" messages */
#endif lint
	printf("sd: ");
	if (((struct scsi_sense *)sp)->class <= 6) {
		register struct scsi_sense *sense;

		sense = (struct scsi_sense *) sp;
		if (sense->code < sc_errct[sense->class]) {
			printf("%s", sc_errors[sense->class][sense->code]);
		} else {
			printf("error %x", *sp);
		}
		if (sense->adr_val) {
			printf("- block no. %d", (sense->high_addr << 16) |
			    (sense->mid_addr << 8) | sense->low_addr);
		}
	} else {	/* Sense class 7: the standardized one */
		register struct scsi_ext_sense *sense7;

		sense7 = (struct scsi_ext_sense *) sp;
		if (sense7->fil_mk) {
			printf("file mark ");
		}
		if (sense7->eom) {
			printf("end of medium ");
		}
		if (sense7->key 
		    < sizeof (sc_sense7_keys) / sizeof (sc_sense7_keys[0])) {
			printf("%s", sc_sense7_keys[sense7->key]);
		} else {
			printf("sense key %x", sense7->key);
		}
		printf(" block no. %x", (sense7->info_1 << 24) |
		    (sense7->info_2 << 16) | (sense7->info_3 << 8) |
		    sense7->info_4);
	}
	printf("\n");
#endif SDERRORS
}


/*
 * Close scsi disk
 *
 * We must close the host adapter too.
 */
int
sdclose(sip)
	struct saioreq *sip;
{
	devclose(((struct sdparam *)sip->si_devdata)->subsip);
}
