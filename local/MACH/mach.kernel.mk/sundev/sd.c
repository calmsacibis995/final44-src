/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	sd.c,v $
 * Revision 2.12  90/07/03  16:49:02  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:15:25  mrt]
 * 
 * Revision 2.11  89/07/11  17:39:30  jjc
 * 	Changed to include machine dependent header files from machine/ not sun3/ because the Sun 4 uses this device driver too.
 * 	[89/07/06  16:54:57  jjc]
 * 
 * Revision 2.10  89/03/09  21:45:11  rpd
 * 	More cleanup.
 * 
 * Revision 2.9  89/02/25  19:54:24  gm0w
 * 	Added new copyright and fixed includes as part of kernel
 * 	cleanup.
 * 	[89/02/10            jjc]
 * 
 * Revision 2.8  89/01/24  12:24:23  af
 * 	Fix for GCC -- pass2.
 * 	[89/01/24            rvb]
 * 
 * Revision 2.7  89/01/23  15:29:17  rvb
 * 	Forward declarations for GCC.
 * 	[89/01/22            rvb]
 * 
 * Revision 2.6  88/12/21  14:22:52  mja
 * 	Split up expression assignment to bit field in sdintr_adaptec()
 * 	to bypass compiler bug (under BUG).
 * 	[88/12/21            rvb]
 * 
 * Revision 2.5  88/12/07  17:21:05  mikeg
 * 	Entered this new sd driver from SunOS 3.5 in the
 * 	kernel source tree.
 * 	[88/12/01  14:16:43  mikeg]
 * 
 * 05-Aug-88  Jonathan J. Chew (jjc) at Carngie-Mellon University
 *	Upgraded to SunOS 3.5 with some help from Jon Hale at Mt. Xinu.
 *	Removed old history that doesn't apply anymore.
 *
 * 31-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Deleted use of dk_bps.
 *
 * 25-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Converted to use Mach VM.
 *
 */
/* @(#)sd.c       1.1 87/12/21 Copyr 1987 Sun Micro */
#include <sd.h>
#if	NSD > 0

#ifndef	lint
static	char sccsid[] = "@(#)sd.c       1.1 87/12/21 Copyr 1987 Sun Micro";
#endif	lint

#define SDDEBUG 		/* Allow compiling of debug code */
/* #define REL4			/* enable release 4.00 mods */

/*
 * SCSI driver for SCSI disks.
 */
#ifndef	REL4
#include <sd.h>
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
#include <sys/fcntl.h>
#endif	MACH
#include <sys/file.h>
#include <sys/proc.h>
#include <sys/disklabel.h>
#include <sys/syslog.h>
#include <sys/stat.h>

#ifdef	MACH
#include <vm/vm_kern.h>
#else	MACH
#include <machine/pte.h>
#endif	MACH
#include <machine/psl.h>
#include <machine/mmu.h>
#include <machine/cpu.h>

#include <sun/dkio.h>

#include <sundev/mbvar.h>
#include <sundev/screg.h>
#include <sundev/sireg.h>
#include <sundev/scsi.h>
#include <sundev/sdreg.h>

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
#include <sys/fcntl.h>
#endif	MACH
#include <sys/file.h>
#include <sys/disklabel.h>
#include <sys/syslog.h>
#include <sys/stat.h>

#ifdef	MACH
#include <vm/vm_kern.h>
#else	MACH
#include <machine/pte.h>
#endif	MACH
#include <machine/psl.h>
#include <machine/mmu.h>
#include <machine/cpu.h>

#include <sun/dkio.h>

#include <sundev/mbvar.h>
#include <sundev/screg.h>
#include <sundev/sireg.h>
#include <sundev/scsi.h>
#include <sundev/sdreg.h>
#endif	REL4


#define MAX_RETRIES 		4	/* retry limit */
#define MAX_RESTORES 		4	/* rezero unit limit (after retries) */
#define MAX_FAILS 		15 	/* soft errors before reassign */
#define MAX_LABEL_RETRIES  	2
#define MAX_LABEL_RESTORES 	1
#define MAX_BUSY		10
#define EL_RETRY		0	/* Error msg threshold, retries */
#define EL_REST			0	/* Error msg threshold, restores */
#define EL_FAILS 		5 	/* Error msg threshold, soft errors */


#define	UNITSHIFT		3
#define LPART(dev)		(dev & (NLPART -1))
#define SDUNIT(dev)		((dev >> UNITSHIFT) & (NUNIT -1))
#define SDNUM(un)		(un - sdunits)


#ifdef	SDDEBUG
short sd_debug = 0;		/*
				 * 0 = normal operation
				 * 1 = extended error info only
				 * 2 = debug and error info
				 * 3 = all status info
				 */
/* Handy debugging 0, 1, and 2 argument printfs */
#define DPRINTF(str) \
	if (sd_debug > 1) printf(str)
#define DPRINTF1(str, arg1) \
	if (sd_debug > 1) printf(str,arg1)
#define DPRINTF2(str, arg1, arg2) \
	if (sd_debug > 1) printf(str,arg1,arg2)
#define DPRINTF3(str,arg1,arg2,arg3) \
	if (sd_debug > 1) printf(str,arg1,arg2,arg3)
#define DPRINTF4(str,arg1,arg2,arg3,arg4) \
	if (sd_debug > 1) printf(str,arg1,arg2,arg3,arg4)

/* Handy extended error reporting 0, 1, and 2 argument printfs */
#define EPRINTF(str) \
	if (sd_debug) printf(str)
#define EPRINTF1(str, arg1) \
	if (sd_debug) printf(str,arg1)
#define EPRINTF2(str, arg1, arg2) \
	if (sd_debug) printf(str,arg1,arg2)
#define DEBUG_DELAY(cnt) \
	if (sd_debug)  DELAY(cnt)

#else	SDDEBUG
#define DPRINTF(str)
#define DPRINTF1(str, arg2)
#define DPRINTF2(str, arg1, arg2)
#define EPRINTF(str)
#define EPRINTF1(str, arg2)
#define EPRINTF2(str, arg1, arg2)
#define DEBUG_DELAY(cnt)
#endif	SDDEBUG

extern char *strncpy();
int	sdstrategy();

extern struct scsi_unit sdunits[];
extern struct scsi_unit_subr scsi_unit_subr[];
extern struct scsi_disk sdisk[];
extern int nsdisk;

extern	int	cold;

short sd_retry = EL_RETRY;	/*
				 * Error message threshold, retries.
				 * Make it global so manufacturing can
				 * override setting.
				 */

#ifdef	SDDEBUG
sd_print_buffer(y, count)
	register u_char *y;
	register int count;
{
	register int x;

	for (x = 0; x < count; x++)
		printf("%x  ", *y++);
	printf("\n");
}
#endif	SDDEBUG

#ifdef	__GNU__
static int simple();
static int sdintr_sense();
static int sdintr_ran_sense();
static int sd_fix_block();
static int sdintr_ran_reassign();
static int sdintr_adaptec();
static int sd_error_message();
static int sd_print_cmd();
static int sderrmsg();
#endif	__GNU__

/*
 * Return a pointer to this unit's unit structure.
 */
sdunitptr(md)
	register struct mb_device *md;
{
	return ((int)&sdunits[md->md_unit]);
}


static
sdtimer(dev)
	register dev_t dev;
{
	register struct scsi_disk *dsi;
	register struct scsi_unit *un;
	register struct scsi_ctlr *c;
	register u_int	unit;

	unit = SDUNIT(dev);
	un = &sdunits[unit];
	dsi = &sdisk[unit];
	c = un->un_c;
#ifdef	lint
	c = c;
#endif	lint

	DPRINTF("sdtimer:\n");
	if (dsi->un_openf >= OPENING) {
#ifdef	SD_TIMEOUT
		if ((dsi->un_timeout > 0)  &&  (--dsi->un_timeout == 0)) {

			/* Process command timeout for normal I/O operations */
			log(LOG_ERR, "sd%d:  sdtimer: I/O request timeout\n",
									 unit);
			if ((*c->c_ss->scs_deque)(c, un)) {
				/* Can't Find CDB I/O request to kill, help! */
				log(LOG_ERR,
					"sd%d:  sdtimer: can't abort request\n",
					unit);
				(*un->un_c->c_ss->scs_reset)(un->un_c, 0);
			}
		} else if (dsi->un_timeout != 0) {
			DPRINTF2("sdtimer:  running, open= %d, timeout= %d\n",
				 dsi->un_openf, dsi->un_timeout);
		}
#endif	SD_TIMEOUT

	/* Process opening delay timeout */
	} else if ((dsi->un_timeout > 0)  &&  (--dsi->un_timeout == 0)) {
		DPRINTF("sdtimer:  running...\n");
		wakeup((caddr_t)dev);
	}
	timeout(sdtimer, (caddr_t)dev, 30*hz);
}


/*
 * Attach device (boot time).
 */
sdattach(md)
	register struct mb_device *md;
{
	register struct scsi_unit *un;
	register struct scsi_disk *dsi;
	struct scsi_inquiry_data *sid;
	int i;

	dsi = &sdisk[md->md_unit];
	un = &sdunits[md->md_unit];

	/*
	 * link in, fill in unit struct.
	 */
	un->un_md = md;
	un->un_mc = md->md_mc;
	un->un_unit = md->md_unit;
	un->un_target = TARGET(md->md_slave);
	un->un_lun = LUN(md->md_slave);
	un->un_ss = &scsi_unit_subr[TYPE(md->md_flags)];
	un->un_present = 0;

	dsi->un_openf = OPENING;
	dsi->un_flags = 0;
	dsi->un_timeout = 0;
	dsi->un_timer = 0;
	dsi->un_bad_index = 0;
	dsi->un_status = 0;
	dsi->un_retries = 0;
	dsi->un_restores = 0;
	dsi->un_sec_left = 0;
	dsi->un_total_errors = 0;
	dsi->un_err_resid = 0;
	dsi->un_err_blkno = 0;
	dsi->un_cyl_start = 0;
	dsi->un_cyl_end = 0;
	dsi->un_cylin_last = 0;
	dsi->un_lp1 = NULL;
	dsi->un_lp2 = NULL;
	dsi->un_ctype = CTYPE_UNKNOWN;

	/*
	 * Allocate space for request sense/inquiry buffer in
	 * Multibus memory.  Align it to a longword boundary.
	 */
	sid = (struct scsi_inquiry_data *)rmalloc(iopbmap,
		(long)(sizeof (struct scsi_inquiry_data) +4));
	if (sid == NULL) {
		printf(": sdattach: no space for inquiry data");
		return;
	}

	while ((u_int)sid & 0x03)
		((u_int)sid)++;
	dsi->un_sense = (int)sid;

	EPRINTF2("sd%d:  sdattach: buffer= 0x%x, ", SDNUM(un), (int)sid);
	EPRINTF2("dsi= 0x%x, un= 0x%x\n", dsi, un);
	DPRINTF2("sdattach: looking for lun %d on target %d\n",
		 LUN(md->md_slave), TARGET(md->md_slave));

	/*
	 * Test for unit ready.  The first test checks
	 * for a non-existant device.  The other tests
	 * wait for the drive to get ready.
	 */
	if (simple(un, SC_TEST_UNIT_READY, 0, 0, 0) > 1) {
		DPRINTF("sdattach:  unit offline\n");
		printf(": off line");
		return;
	}
	for (i = 0; i < MAX_BUSY; i++) {
		if (simple(un, SC_TEST_UNIT_READY, 0, 0, 0) == 0) {
			goto SDATTACH_UNIT;

		} else if (un->un_c->c_scb.chk) {
			goto SDATTACH_UNIT;

		} else if (un->un_c->c_scb.busy  &&  !un->un_c->c_scb.is) {
			EPRINTF("sdattach:  unit busy\n");
			DELAY(4000000);		/* Wait 4 Sec. */

		} else if (un->un_c->c_scb.is) {
			EPRINTF("sdattach:  reservation conflict\n");
			break;
		}
	}
	DPRINTF("sdattach:  unit offline\n");
	printf(": off line");
	return;

SDATTACH_UNIT:
	if (simple(un, SC_TEST_UNIT_READY, 0, 0, 0) != 0) {
		DPRINTF("sdattach:  unit failed\n");
		printf(": not ready");
		return;
	}

	bzero((caddr_t)sid, (u_int)sizeof (struct scsi_inquiry_data));
	if (simple(un, SC_INQUIRY, (char *) sid - DVMA, 0,
			(int)sizeof (struct scsi_inquiry_data)) == 0) {
		/* Only CCS controllers support Inquiry command */
#ifdef	SDDEBUG
		if (sd_debug > 2)
			sd_print_buffer((u_char *)sid, 32);
#endif	SDDEBUG
		if (bcmp(sid->vid, "EMULEX", 6) == 0) {
			EPRINTF("sdattach:  Emulex found\n");
			dsi->un_ctype = CTYPE_MD21;
			dsi->un_flags = 0;
		} else {
			EPRINTF("sdattach:  CCS found\n");
			dsi->un_ctype = CTYPE_CCS;
			dsi->un_flags = 0;
		}
	} else {
		/* non-CCS, assume Adaptec ACB-4000 */
		EPRINTF("sdattach:  Adaptec found\n");
		dsi->un_ctype = CTYPE_ACB4000;
		dsi->un_flags = SC_UNF_NO_DISCON;
	}
	if (sd_getlabel(un) == 0)
		dsi->un_openf = OPENING_RAW;
}

/*
 * Get the disk label; return TRUE if there was one
 */

#define SDMINOR(u, p)  (((u) << UNITSHIFT) | (p))

sd_getlabel(un)
	register struct scsi_unit *un;
{
	register struct disklabel *lp;
	register char *msg;
	register int intrlv;
	char *readdisklabel();

	/*
	 * Read label from pack.
	 */
	lp = &sdisk[un->un_unit].un_label;
	/*
	 * Set up enough of a label to read the real label.
	 */
	lp->d_secsize = DEV_BSIZE;
	lp->d_secperunit = 1000;	/* large enough to read label */
	lp->d_secpercyl = 32;		/* won't work if label > cylinder */
	lp->d_npartitions = 1;
	lp->d_partitions[0].p_size = lp->d_secperunit;
	lp->d_partitions[0].p_offset = 0;
	DPRINTF4("sd%d: sd_getlabel about to readdisklabel(%d, %x, %x)\n", 
			un->un_unit, SDMINOR(un->un_unit, 0), sdstrategy, lp);
	if ((msg = readdisklabel(SDMINOR(un->un_unit, 0), sdstrategy, lp))
								!= NULL) {
		if (cold)
			printf(": %s", msg);
		else
			log(LOG_ERR, "sd%d: %s\n", un->un_unit, msg);
		return(0);
	}
	DPRINTF("done\n");
	if (cold)
		printf(": %s, size = %d sectors", lp->d_typename,
							lp->d_secperunit);
	else
		log(LOG_NOTICE, "sd%d: %s, size = %d sectors\n", un->un_unit,
					 lp->d_typename, lp->d_secperunit);

	un->un_present = 1;			/* "it's here..." */
#ifdef	MACH
#else	MACH
	/*
	 * Diddle stats if neccessary.
	 */
	if (un->un_md->md_dk >= 0) {
		intrlv = lp->d_interleave;
		if (intrlv <= 0  ||  intrlv >= lp->d_nsectors) {
			intrlv = 1;
		}
		dk_bps[un->un_md->md_dk] =
			(DEV_BSIZE * 60 * dsi->un_g.dkg_nsect) / intrlv;
	}
#endif	MACH
	return (1);
}


/*
 * Run a command in polled mode.
 * Return true if successful, false otherwise.
 */
static
simple(un, cmd, dma_addr, secno, nsect)
	register struct scsi_unit *un;
	register int cmd, dma_addr, secno, nsect;
{
	register volatile struct scsi_cdb *cdb;
	register struct scsi_ctlr *c;
	register int err;

	/*
	 * Grab and clear the command block.
	 */
	c = un->un_c;
	cdb = &c->c_cdb;
	bzero((caddr_t)cdb, CDB_GROUP0);

	/*
	 * Plug in command block values.
	 */
	cdb->cmd = cmd;
	if (SCSI_RECV_DATA_CMD(cmd))
		un->un_flags |= SC_UNF_RECV_DATA;
	else
		un->un_flags &= ~SC_UNF_RECV_DATA;

	c->c_un = un;
	cdb->lun = un->un_lun;
	FORMG0ADDR(cdb, secno);
	FORMG0COUNT(cdb, nsect);
	un->un_dma_addr = dma_addr;
	if (cmd == SC_INQUIRY)
		un->un_dma_count = nsect;
	else
		un->un_dma_count = nsect << DEV_BSHIFT;

	/*
	 * Fire up the pup.
	 */
	if (err = (*c->c_ss->scs_cmd)(c, un, 0)) {
		if (err > 1) {
			return (2);	/* Hard failure */
		} else {
			return (1);	/* Recoverable failure */
		}
	}
	return (0);			/* No failure */
}


/*
 * This routine opens a disk.  Note that we can handle disks
 * that make an appearance after boot time.
 */
/*ARGSUSED*/
sdopen(dev, flag, newdev, fmt)
	dev_t dev;
	int flag;
	dev_t *newdev;
	int fmt;
{
	register struct scsi_unit *un;
	register struct disklabel *dlp;
	register int unit;
	register struct scsi_disk *dsi;
	register struct scsi_inquiry_data *sid;
	int part;
	int mask;
	int i;
	int s;
	struct partition *pp;
	daddr_t start;
	daddr_t end;

	unit = SDUNIT(dev);
	if (unit >= nsdisk) {
		EPRINTF("sdopen:  illegal unit\n");
		return (ENXIO);
	}

	un = &sdunits[unit];
	dsi = &sdisk[unit];
	if (un->un_mc == 0) {
		EPRINTF("sdopen:  disk not atached\n");
		return (ENXIO);
	}

	/*
	 * If command timeouts not activated yet, switch it on.
	 */
#ifdef	SD_TIMEOUT
	if (dsi->un_timer == 0) {
		EPRINTF("sdopen:  starting timer\n");
		dsi->un_timer++;
		timeout(sdtimer, (caddr_t)dev, 30*hz);
	}
#endif	SD_TIMEOUT

#ifdef	notdef
	/*
	 * Wait for the state to settle
	 */
	s = splr(pritospl(un->un_mc->mc_intpri));
	while(dsi->un_openf != OPEN && dsi->un_openf != OPENRAW &&
	      dsi->un_openf != CLOSED)
		sleep((caddr_t)dsi, PZERO + 1);
	splx(s);
#endif
	if (un->un_present == 0) {
	/*
	 * Didn't see it at autoconfig time?   Let's look again..
	 */

		EPRINTF("sdopen:  opening device\n");

		dsi->un_openf = OPENING;
		dsi->un_flags = SC_UNF_NO_DISCON;	/* no disconnects */
		if (sdcmd(dev, SC_TEST_UNIT_READY, 0, 0, (caddr_t)0)  &&
		    dsi->un_openf == CLOSED) {
			DPRINTF("sdopen:  not ready\n");
			dsi->un_timer = 0;
			untimeout(sdtimer, (caddr_t)dev);
			return (ENXIO);
		}

		dsi->un_openf = OPENING;
		(void) sdcmd(dev, SC_TEST_UNIT_READY, 0, 0, (caddr_t)0);
		dsi->un_openf = OPENING;
		if (sdcmd(dev, SC_TEST_UNIT_READY, 0, 0, (caddr_t)0)) {
			EPRINTF("sdopen:  not ready\n");
			dsi->un_timer = 0;
			untimeout(sdtimer, (caddr_t)dev);
			return (ENXIO);
		}
		dsi->un_openf = OPENING;
		(int)sid = dsi->un_sense;
		bzero((caddr_t)sid, (u_int)sizeof (struct scsi_inquiry_data));
		if (sdcmd(dev, SC_INQUIRY, 0,
		    sizeof (struct scsi_inquiry_data), (caddr_t)sid)) {
			/* non-CCS, assume Adaptec */
			EPRINTF("sdopen:  Adaptec found\n");
			dsi->un_ctype = CTYPE_ACB4000;
			dsi->un_flags = SC_UNF_NO_DISCON;
		} else {
#ifdef	SDDEBUG
			if (sd_debug > 2)
				sd_print_buffer((u_char *)sid, 32);
#endif	SDDEBUG
			dsi->un_flags = 0;
			if (bcmp(sid->vid, "EMULEX", 6) == 0) {
				EPRINTF("sdopen:  Emulex found\n");
				dsi->un_ctype = CTYPE_MD21;
			} else {
				EPRINTF("sdopen:  CCS found\n");
				dsi->un_ctype = CTYPE_CCS;
			}
		}
		if (sd_getlabel(un) == 0)
			dsi->un_openf = OPENRAW;
	}
	part = LPART(dev);
	dlp = &dsi->un_label;
	if (part >= dlp->d_npartitions) {
		EPRINTF2("sdopen: partition %d >= limit %d\n", part,
							dlp->d_npartitions);
		return (ENXIO);
	}
	/*
	 * Warn if a partition is opened that overlaps one
	 * that is already open, unless one of them is the "raw"
	 * partition (whole disk)
	 */
#define	RAWPART	2		/* 'c' partition */
	mask = 1 << part;
	if ((dsi->un_openpart & mask) == 0 && part != RAWPART) {
		pp = &dlp->d_partitions[part];
		start = pp->p_offset;
		end = pp->p_offset + pp->p_size;
		for(pp = dlp->d_partitions, i = 0;
		    i < dlp->d_npartitions; pp++, i++) {
			if(pp->p_offset + pp->p_size <= start ||
			    pp->p_offset >= end || i == RAWPART)
				continue;
			if (dsi->un_openpart & (1 << i))
				log(LOG_WARNING,
				    "sd%d%c: overlaps open partition sd%d%c\n",
				    un->un_unit, part+'a', un->un_unit, i+'a');
		}
	}
	switch(fmt) {

	case S_IFCHR:
		dsi->un_copenpart |= mask;
		break;

	case S_IFBLK:
		dsi->un_bopenpart |= mask;
		break;
	}
	dsi->un_openpart |= mask;
	DPRINTF4("sd%d: open %x (raw %x, block %x)\n", un->un_unit,
			dsi->un_openpart, dsi->un_copenpart, dsi->un_bopenpart);
	return (0);
}

sdclose(dev, flags, fmt)
	dev_t dev;
	int flags;
	int fmt;
{
	int mask;
	int unit;
	register struct scsi_disk *dsi;

#ifdef	lint
	flags = flags;
#endif
	unit = SDUNIT(dev);
	dsi = &sdisk[unit];
	mask = 1 << LPART(dev);
	switch(fmt) {

	case S_IFCHR:
		dsi->un_copenpart &= ~mask;
		break;

	case S_IFBLK:
		dsi->un_bopenpart &= ~mask;
		break;
	}
	dsi->un_openpart = dsi->un_copenpart | dsi->un_bopenpart;
	if (dsi->un_openpart == 0) {
		/*
		 * XXX should wait here for I/O completion
		 */
		dsi->un_wlabel = 0;
	}
	DPRINTF4("sd%d: sdclose: open %x (raw %x, block %x)\n", unit,
			dsi->un_openpart, dsi->un_copenpart, dsi->un_bopenpart);
	return(0);
}

/*
 * This routine returns the size of a logical partition.  It is called
 * from the device switch at normal priority.
 */
sdsize(dev)
	register dev_t dev;
{
	register struct scsi_unit *un;
	register struct partition *pp;

	un = &sdunits[SDUNIT(dev)];
	DPRINTF("sdsize:\n");

	if (un->un_present) {
		DPRINTF("sdsize:  getting info\n");
		pp = &sdisk[SDUNIT(dev)].un_label.d_partitions[LPART(dev)];
		return(pp->p_size);
	} else {
		EPRINTF("sdsize:  unit not present\n");
		return (-1);
	}
}


/*
 * This routine is the focal point of internal commands to the controller.
 * NOTE: this routine assumes that all operations done before the disk's
 * geometry is defined.
 */
sdcmd(dev, cmd, block, count, addr)
	dev_t dev;
	int cmd, block, count;
	caddr_t addr;
{
	register struct scsi_disk *dsi;
	register struct scsi_unit *un;
	register struct buf *bp;
	register int s;

	DPRINTF("sdcmd:\n");
	un = &sdunits[SDUNIT(dev)];
	bp = &un->un_sbuf;
	dsi = &sdisk[dkunit(bp)];
#ifdef	lint
	dsi = dsi;
	if (dsi->un_options)
		goto SDCMD_EXIT;
#endif	lint

	s = splx(pritospl(un->un_mc->mc_intpri));
	while (bp->b_flags & B_BUSY) {
		bp->b_flags |= B_WANTED;
		DPRINTF1("sdcmd:  sleeping...,  bp= 0x%x\n", bp);
		(void) sleep((caddr_t) bp, PRIBIO);
	}

	DPRINTF1("sdcmd:  waking...,  bp= 0x%x\n", bp);
	bp->b_flags = B_BUSY | B_READ | B_WANTED;
	(void) splx(s);

	un->un_scmd = cmd;
	bp->b_dev = dev;
	bp->b_bcount = count;
	bp->b_blkno = block;
	(caddr_t)bp->b_un.b_addr = addr;
	un->un_sbuf.b_un.b_addr = addr;

#ifdef	FORMAT
	if (dsi->un_options & (SD_DVMA_IN | SD_DVMA_OUT)) {

		bp->b_flags |= B_PHYS;
		bp->b_proc = u.u_procp;
		u.u_procp->p_flag |= SPHYSIO;
		/*
		 * Fault lock the address range of the buffer.
		 */
		if (as_fault(u.u_procp->p_as, bp->b_un.b_addr,
		   	     (u_int)bp->b_bcount, F_SOFTLOCK,
		   	     (dsi->un_options & SD_DVMA_OUT)) {

			EPRINTF1("sdcmd:  dvma error, bp= 0x%x\n", bp);
			bp->b_flags = B_ERROR;
			goto SDCMD_EXIT;
		}
		/*
		 * Make sure the address range has legal
		 * properties for the mb routines.
		 */
		if (buscheck(bp) < 0) {
			EPRINTF1("sdcmd:  buscheck error, bp= 0x%x\n", bp);
			bp->b_flags = B_ERROR;
			goto SDCMD_EXIT;
		}
	}
#endif	FORMAT

	sdstrategy(bp);
	iowait(bp);
	bp->b_flags &= ~B_BUSY;
	if (bp->b_flags & B_WANTED) {
		DPRINTF1("sdcmd:  waking...,  bp= 0x%x\n", bp);
		wakeup((caddr_t)bp);
	}

SDCMD_EXIT:
	return (bp->b_flags & B_ERROR);
}


/*
 * This routine is the high level interface to the disk.  It performs
 * reads and writes on the disk using the buf as the method of communication.
 * It is called from the device switch for block operations and via physio()
 * for raw operations.  It is called at normal priority.
 */
sdstrategy(bp)
	register struct buf *bp;
{
	register struct scsi_unit *un;
	register struct disklabel *lp;
	register struct partition *pp;
	register daddr_t bn;
	register u_int cyl;
	register struct buf *dp;
	register struct scsi_disk *dsi;
	register int s;
	int unit;
	daddr_t sz;
	daddr_t maxsz;

	DPRINTF("sdstrategy:\n");
	unit = dkunit(bp);
	if (unit >= nsdisk) {
		EPRINTF("sdstrategy: invalid unit\n");
		bp->b_error = ENXIO;
		bp->b_flags |= B_ERROR;
		iodone(bp);
		return;
	}
	un = &sdunits[unit];
	dsi = &sdisk[unit];
	lp = &dsi->un_label;
	pp = &lp->d_partitions[LPART(bp->b_dev)];
	bn = bp->b_blkno;

	if (cold) {
		int retries;
		int restores;
		int nblk;
		caddr_t tb;

		DPRINTF2("cold-start bp %x b_addr %x\n", bp, bp->b_un.b_addr);
		/*
		 * The I/O system may not be set up yet, and all
		 * we should be doing at this time is reading the disk
		 * label.  Use polled I/O.
		 */
		if ((bp->b_flags & (B_READ|B_WRITE)) != B_READ) {
			EPRINTF("sdstrategy: cold-start write\n");
			bp->b_error = ENODEV;
			goto bad;
		}
		nblk = (bp->b_bcount + (DEV_BSIZE - 1)) >> DEV_BSHIFT;
		tb = (caddr_t) rmalloc(iopbmap, (long) nblk << DEV_BSHIFT);
		if (tb == NULL) {
			printf("sd%d: no space for cold I/O buffer\n", unit);
			bp->b_error = ENOBUFS;
			goto bad;
		}
		DPRINTF3("reading %d blocks at block %d, addr %x\n", nblk, bn,
						tb - DVMA);
		for(restores = 0; restores < MAX_LABEL_RESTORES; restores++) {
			for(retries = 0; retries < MAX_LABEL_RETRIES; retries++)
				DPRINTF2("retry %d, restore %d\n", retries,
								restores);
				if (simple(un, SC_READ, tb - DVMA,
							bn, nblk) == 0) {
					bcopy(tb, bp->b_un.b_addr,
						bp->b_bcount);
					rmfree(iopbmap, (long)nblk<<DEV_BSHIFT,
						(long)tb);
					biodone(bp);
					DPRINTF("success\n");
					return;
				}
			(void) simple(un, SC_REZERO_UNIT, 0, 0, 0);
		}
		rmfree(iopbmap, (long)nblk << DEV_BSHIFT, (long)tb);
		DPRINTF("failed\n");
		bp->b_error = EIO;
		goto bad;
	}

	if (bp != &un->un_sbuf)  {
		if ((un->un_present == 0)  ||  (pp->p_size == 0)) {
			EPRINTF("sdstrategy:  unit not present\n");
			EPRINTF2("sdstrategy:  bn= 0x%x  nblk= 0x%x\n",
				bn, pp->p_size);
			bp->b_error = ENXIO;
			goto bad;
		}
		maxsz = pp->p_size;
		if (pp->p_offset + pp->p_size > lp->d_secperunit)
			maxsz = lp->d_secperunit - pp->p_offset;
		sz = (bp->b_bcount + DEV_BSIZE - 1) >> DEV_BSHIFT;
		if (bn + pp->p_offset <= LABELSECTOR &&
#if LABELSECTOR != 0
		    bn + pp->p_offset + sz > LABELSECTOR &&
#endif
		    (bp->b_flags & B_READ) == 0 && dsi->un_wlabel == 0) {
			bp->b_error = EROFS;
			goto bad;
		}
		if (bn < 0 || bn + sz > maxsz) {
			/* if exactly at end of disk, return an EOF */
			if (bn == maxsz) {
				bp->b_resid = bp->b_bcount;
				biodone(bp);
				return;
			}
			/* or truncate if part of it fits */
			sz = maxsz - bn;
			if (sz <= 0) {
				bp->b_error = EINVAL;   /* or hang it up */
				goto bad;
			}
			bp->b_bcount = sz << DEV_BSHIFT;
		}
	}

	/* could overflow with disks larger than 2 Tbytes */
	bp->b_cylin = (bn + pp->p_offset) / lp->d_secpercyl;
	s = splx(pritospl(un->un_mc->mc_intpri));
	dp = &un->un_utab;
	disksort((struct diskhd *)dp, bp);

	if (dp->b_active == 0) {
		(*un->un_c->c_ss->scs_ustart)(un);
		bp = &un->un_mc->mc_tab;
		if (bp->b_actf  &&  bp->b_active == 0) {
			(*un->un_c->c_ss->scs_start)(un);
		}
	}
	(void) splx(s);
	return;
bad:
	bp->b_flags |= B_ERROR;
	biodone(bp);
	return;
}


/*
 * Set up a transfer for the controller
 */
sdstart(bp, un)
	register struct buf *bp;
	register struct scsi_unit *un;
{
	register struct partition *pp;
	register struct scsi_disk *dsi;
	register int nblk;

	DPRINTF("sdstart:\n");

	dsi = &sdisk[dkunit(bp)];
	pp = &dsi->un_label.d_partitions[LPART(bp->b_dev)];

	/* Process internal I/O requests */
	if (bp == &un->un_sbuf) {
		EPRINTF("sdstart:  internal I/O\n");
		un->un_cmd = un->un_scmd;
		un->un_count = bp->b_bcount;
		un->un_blkno = bp->b_blkno;
		bp->b_resid = 0;
		un->un_flags = 0;
		if (dsi->un_options & (SD_DVMA_IN | SD_DVMA_OUT)) {
			EPRINTF("sdstart:  DVMA enabled\n");
			un->un_flags = SC_UNF_DVMA;
		}
		return (1);
	}

	/* Process file system I/O requests */
	if (bp->b_flags & B_READ) {
		DPRINTF("sdstart:  read\n");
		un->un_cmd = SC_READ;
	} else {
		DPRINTF("sdstart:  write\n");
		un->un_cmd = SC_WRITE;
	}

	/* Compute absolute block location */
	un->un_blkno = bp->b_blkno + pp->p_offset;

	/* Finish processing read/write request */
	nblk = (bp->b_bcount + (DEV_BSIZE - 1)) >> DEV_BSHIFT;
	un->un_count = MIN(nblk, (pp->p_size - bp->b_blkno));
	bp->b_resid = bp->b_bcount - (un->un_count << DEV_BSHIFT);
	un->un_flags = SC_UNF_DVMA;
	return (1);
}


/*
 * Make a cdb for disk I/O.
 */
sdmkcdb(c, un)
	register struct scsi_ctlr *c;
	struct scsi_unit *un;
{
	register volatile struct scsi_cdb *cdb;
	register struct scsi_disk *dsi;
	register struct scsi_reassign_blk *srb;
	register struct scsi_format_params *sf;

	DPRINTF("sdmkcdb:\n");

	dsi = &sdisk[un->un_unit];
	cdb = &c->c_cdb;
	bzero((caddr_t)cdb, CDB_GROUP0);
	cdb->cmd = un->un_cmd;
	cdb->lun = un->un_lun;

	switch (un->un_cmd) {
	case SC_READ:
		DPRINTF("sdmkcdb:  read\n");
		dsi->un_timeout = 2;
		un->un_flags |= (SC_UNF_RECV_DATA | dsi->un_flags);
		FORMG0ADDR(cdb, un->un_blkno);
		FORMG0COUNT(cdb, un->un_count);
		un->un_dma_addr = un->un_baddr;
		un->un_dma_count = un->un_count << DEV_BSHIFT;
		break;

	case SC_WRITE:
		DPRINTF("sdmkcdb:  write\n");
		dsi->un_timeout = 2;
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				dsi->un_flags;
		FORMG0ADDR(cdb, un->un_blkno);
		FORMG0COUNT(cdb, un->un_count);
		un->un_dma_addr = un->un_baddr;
		un->un_dma_count = un->un_count << DEV_BSHIFT;
		break;

	case SC_WRITE_VERIFY:
		DPRINTF("sdmkcdb:  write verify\n");
		dsi->un_timeout = 3;
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				dsi->un_flags;
		FORMG1ADDR(cdb, un->un_blkno);
		FORMG1COUNT(cdb, un->un_count);
		un->un_dma_addr = un->un_baddr;
		un->un_dma_count = un->un_count << DEV_BSHIFT;
		break;

	case SC_REQUEST_SENSE:
		EPRINTF("sdmkcdb:  request sense\n");
		dsi->un_timeout = 2;
		un->un_flags |= (SC_UNF_RECV_DATA | dsi->un_flags);
		FORMG0COUNT(cdb,  sizeof (struct scsi_sense));
		un->un_dma_addr = (int)dsi->un_sense - (int)DVMA;
		un->un_dma_count = sizeof (struct scsi_sense);
		bzero((caddr_t)(dsi->un_sense), sizeof (struct scsi_sense));
		return;

	case SC_READ_LABEL:
		EPRINTF("sdmkcdb:  read label\n");
		dsi->un_timeout = 2;
		un->un_flags |= (SC_UNF_RECV_DATA | dsi->un_flags);
		cdb->cmd = SC_READ;
		FORMG0ADDR(cdb, un->un_blkno);
		FORMG0COUNT(cdb,  1);
		un->un_dma_addr = (int)un->un_sbuf.b_un.b_addr - (int)DVMA;
		un->un_dma_count = DEV_BSIZE;
		break;

	case SC_REZERO_UNIT:
		EPRINTF("sdmkcdb:  rezero unit\n");
		dsi->un_timeout = 2;
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				dsi->un_flags;
		un->un_dma_addr = 0;
		un->un_dma_count = 0;
		return;

	case SC_TEST_UNIT_READY:
		DPRINTF("sdmkcdb:  test unit ready\n");
		dsi->un_timeout = 2;
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				dsi->un_flags;
		un->un_dma_addr = 0;
		un->un_dma_count = 0;
		break;

	case SC_INQUIRY:
		DPRINTF("sdmkcdb:  inquiry\n");
		dsi->un_timeout = 2;
		un->un_flags |= (SC_UNF_RECV_DATA | dsi->un_flags);
		FORMG0COUNT(cdb, sizeof (struct scsi_inquiry_data));
		un->un_dma_addr = (int)dsi->un_sense - (int)DVMA;
		un->un_dma_count = sizeof (struct scsi_inquiry_data);
		bzero((caddr_t)(dsi->un_sense), sizeof (struct scsi_inquiry_data));
		break;

	case SC_REASSIGN_BLOCK:
		EPRINTF("sdmkcdb:  reassign block\n");
		dsi->un_timeout = 4;
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				dsi->un_flags;
		un->un_dma_addr = (int)dsi->un_sense - (int)DVMA;
		un->un_dma_count = sizeof (struct scsi_reassign_blk);
		(int)srb = dsi->un_sense;
		srb->reserved = 0;
		srb->length = 1;		/* Only 1 defect */
		srb->defect = un->un_blkno;
		return;

	case SC_FORMAT:
		EPRINTF("sdmkcdb:  format\n");
		dsi->un_timeout = 60;
		un->un_dma_addr = un->un_baddr;
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				dsi->un_flags;
		sf = (struct scsi_format_params *)un->un_sbuf_buffer;
		if (dsi->un_ctype == CTYPE_ACB4000  &&  sf->length == 0) {
			/* No data, but tell it we are sending it a list.  */
			cdb->fmt_parm_bits = FPB_CMPLT;
			un->un_dma_count = 0;
		} else {
			/* Data in BFI format. */
			cdb->fmt_parm_bits = FPB_DATA | FPB_CMPLT | FPB_BFI;
			un->un_dma_count = sf->length + 4;
		}
		cdb->fmt_interleave = 1;
		break;

	case SC_READ_DEFECT_LIST:
		EPRINTF("sdmkcdb:  read defect list\n");
		dsi->un_timeout = 2;
		bzero((caddr_t)cdb + CDB_GROUP0, CDB_GROUP1 - CDB_GROUP0);
		un->un_flags |= (SC_UNF_RECV_DATA | dsi->un_flags);
		FORMG1COUNT(cdb, un->un_count);
		/* cdb->defect_list_descrip = sd->descriptor; */
		un->un_dma_addr = un->un_baddr;
		un->un_dma_count = un->un_count;
		break;

	case SC_MODE_SELECT:
		EPRINTF("sdmkcdb:  mode select\n");
		dsi->un_timeout = 2;
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				dsi->un_flags;
		FORMG0COUNT(cdb, un->un_count);
		un->un_dma_addr = un->un_baddr;
		un->un_dma_count = un->un_count;
		break;

	default:
		EPRINTF("sdmkcdb:  unknown command\n");
		dsi->un_timeout = 2;
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				dsi->un_flags;
		break;
	}
	dsi->un_last_cmd = un->un_cmd;
	return;
}


/*
 * This routine handles controller interrupts.
 * It is always called at disk interrupt priority.
 */
typedef enum sdintr_error_resolution {	
	real_error, 		/* Hard error */
	psuedo_error, 		/* What looked like an error is actually OK */
	more_processing 	/* Recoverable error */
} sdintr_error_resolution;
#ifdef	__GNU__
static sdintr_error_resolution sderror();
#else	__GNU__
sdintr_error_resolution sderror();
#endif	__GNU__

sdintr(c, resid, error)
	register struct scsi_ctlr *c;
	u_int resid;
	int error;
{
	register struct scsi_unit *un;
	register struct scsi_disk *dsi;
	register struct buf *bp;
	register struct mb_device *md;
	int status = 0;

	DPRINTF("sdintr:\n");
	un = c->c_un;
	md = un->un_md;
	bp = un->un_mc->mc_tab.b_actf->b_actf;
	dsi = &sdisk[SDUNIT(bp->b_dev)];
	dsi->un_timeout = 0;		/* turn off time-outs */
#ifdef	lint
	un = un;
#endif	lint

	if (md->md_dk >= 0) {
		dk_busy &= ~(1 << md->md_dk);
	}

	/*
	 * Check for error or special operation states and process.
	 * Otherwise, it was a normal I/O command which was successful.
	 */
	if (dsi->un_openf < OPEN  ||  error  ||  resid ) {

		/*
		 * Special processing for SCSI bus failures.
		 */
		if (error == SE_FATAL) {
			log(LOG_ERR, "sd%d:  scsi bus failure\n", SDNUM(un));
			dsi->un_retries = dsi->un_restores = 0;
			un->un_present = 0;
			dsi->un_openf = CLOSED;
			bp->b_flags |= B_ERROR;
			goto SDINTR_WRAPUP;
		}

		/*
		 * Opening disk, check if command failed.  If it failed
		 * close device.  Otherwise, it's open.
		 */
		if (dsi->un_openf == OPENING || dsi->un_openf == OPENING_RAW) {
			if (error == SE_NO_ERROR) {
				dsi->un_openf =
				     dsi->un_openf == OPENING ? OPEN : OPENRAW;
				goto SDINTR_SUCCESS;
			} else if (error == SE_RETRYABLE) {
				DPRINTF("sdintr:  open failed\n");
				dsi->un_openf = OPEN_FAILED;
				bp->b_flags |= B_ERROR;
				goto SDINTR_WRAPUP;
			} else {
				EPRINTF("sdintr:  hardware failure\n");
				dsi->un_openf = CLOSED;
				bp->b_flags |= B_ERROR;
				goto SDINTR_WRAPUP;
			}
		}

		/*
		 * Rezero for failed command done, retry failed command
		 */
		if ((dsi->un_openf == RETRYING)  &&
		    (c->c_cdb.cmd == SC_REZERO_UNIT)) {

			if (error)
				log(LOG_ERR, "sd%d:  rezero failed\n",
								SDNUM(un));

			DPRINTF("sdintr:  rezero done\n");
			un->un_flags &= ~SC_UNF_GET_SENSE;
			un->un_cmd = dsi->un_last_cmd;
			sdmkcdb(c, un);
			(*c->c_ss->scs_cmd)(c, un, 1);
			return;
		}


		/*
		 * Command failed, need to run request sense command.
		 */
		if ((dsi->un_openf >= OPEN)  &&  error) {
			sdintr_sense(c, dsi, un, resid);
			return;
		}

		/*
		 * Request sense command done, restore failed command.
		 */
		if (dsi->un_openf == SENSING) {
			DPRINTF("sdintr:  restoring sense\n");
			sdintr_ran_sense(c, dsi, un, &resid);
		}

		/*
		 * Reassign done, restore original state
		 */
		if (dsi->un_openf == MAPPING) {
			DPRINTF("sdintr:  restoring state\n");
			sdintr_ran_reassign(c, dsi, un, &resid);
		}

		EPRINTF2("sdintr:  retries= %d  restores= %d  ",
			 dsi->un_retries, dsi->un_restores);
		EPRINTF1("total= %d\n", dsi->un_total_errors);
		if ((dsi->un_openf == RETRYING)  &&  (error == 0)) {

			EPRINTF("sdintr:  ok\n\n");
			dsi->un_openf = OPEN;
			dsi->un_retries = dsi->un_restores = 0;
			goto SDINTR_SUCCESS;
		}

		/*
		 * Process all other errors here
		 */
		EPRINTF2("sdintr:  processing error,  error= %x  chk= %x",
			error, c->c_scb.chk);
		EPRINTF1("  busy= %x", c->c_scb.busy);
		EPRINTF2("  resid= %d (%d)\n", resid, un->un_dma_count);
		switch (sderror(c, un, dsi, bp, resid, error)) {
		case real_error:
			/* This error is FATAL ! */
			DPRINTF("sdintr:  real error\n");
			dsi->un_retries = dsi->un_restores = 0;
			bp->b_flags |= B_ERROR;
			goto SDINTR_WRAPUP;

		case psuedo_error:
			/* A psuedo-error:  soft error reported by ctlr */
			DPRINTF("sdintr:  psuedo error\n");
			status = dsi->un_status;
			dsi->un_retries = dsi->un_restores = 0;
			goto SDINTR_SUCCESS;

		case more_processing:
			/* real error requiring error recovery */
			DPRINTF("stintr:  more processing\n");
			return;
		}
	}


	/*
	 * Handle successful Transfer.  Also, take care of ACB-4000
	 * seek error problem by doing single sector I/O.
	 */
SDINTR_SUCCESS:
	dsi->un_status = status;
	if (dsi->un_sec_left) {
		EPRINTF("sdintr:  single sector writes\n");
		dsi->un_sec_left--;
		un->un_baddr += DEV_BSIZE;
		un->un_blkno++;
		sdmkcdb(c, un);
		if ((*c->c_ss->scs_cmd)(c, un, 1) != 0)
			log(LOG_ERR, "sd%d:  single sector I/O failed\n",
								SDNUM(un));
	}


	/*
	 * Handle I/O request completion (both sucessful and failed).
	 */
SDINTR_WRAPUP:
	if (bp == &un->un_sbuf  &&
	    ((un->un_flags & SC_UNF_DVMA) == 0)) {
		(*c->c_ss->scs_done)(un->un_mc);
	} else {
		mbdone(un->un_mc);
		un->un_flags &= ~SC_UNF_DVMA;
	}
}


/*
 * Disk error decoder/handler.
 */
static sdintr_error_resolution
sderror(c, un, dsi, bp, resid, error)
	register struct scsi_ctlr *c;
	register struct scsi_unit *un;
	register struct scsi_disk *dsi;
	struct buf *bp;
	u_int resid;
	int error;
{
	register struct scsi_ext_sense *ssd;

	DPRINTF("sderror:\n");
	ssd = (struct scsi_ext_sense *)dsi->un_sense;

	/*
	 * Special processing for driver command timeout errors.
	 */
	if (error == SE_TIMEOUT) {
		EPRINTF("sderror:  command timeout error\n");
		dsi->un_status = SC_TIMEOUT;
		goto SDERROR_RETRY;
	}

	/*
	 * Check for Adaptec ACB-4000 seek error problem.  If found,
	 * transfer data one sector at a time.
	 */
	if (dsi->un_ctype == CTYPE_ACB4000  &&  c->c_scb.chk  &&
	    ssd->error_code == 15  &&  un->un_count > 1) {
		EPRINTF("sderror:  seek error\n");
		dsi->un_sec_left = un->un_count - 1;
		un->un_count = 1;
		sdmkcdb(c, un);
		if ((*c->c_ss->scs_cmd)(c, un, 1) != 0) {
			log(LOG_ERR,
				"sd%d:  sderror: single sector I/O failed\n",
			       SDNUM(un));
			return (real_error);
		}
		return (more_processing);
	}

	/*
	 * Check for various check condition errors.
	 */
	dsi->un_total_errors++;
	if (c->c_scb.chk) {

		switch (ssd->key) {
		case SC_RECOVERABLE_ERROR:
			if (sd_retry == 0) {
				sderrmsg(c, un, bp, "recoverable");
			}
			sd_fix_block(c, dsi, un, SE_RETRYABLE);
			return (psuedo_error);

		case SC_MEDIUM_ERROR:
			EPRINTF("sderror:  medium error\n");
			/* sd_fix_block(c, dsi, un, SE_HARD_ERROR); */
			goto SDERROR_RETRY;

		case SC_HARDWARE_ERROR:
			EPRINTF("sderror:  hardware error\n");
			goto SDERROR_RETRY;

		case SC_UNIT_ATTENTION:
			EPRINTF("sderror:  unit attention error\n");
			goto SDERROR_RETRY;

		case SC_NOT_READY:
			EPRINTF("sderror:  not ready\n");
			return (real_error);

		case SC_ILLEGAL_REQUEST:
			EPRINTF("sderror:  illegal request\n");
			return (real_error);

		case SC_VOLUME_OVERFLOW:
			EPRINTF("sderror:  volume overflow\n");
			return (real_error);

		case SC_WRITE_PROTECT:
			EPRINTF("sderror:  write protected\n");
			return (real_error);

		case SC_BLANK_CHECK:
			EPRINTF("sderror:  blank checkt\n");
			return (real_error);

		default:
			/*
			 * Undecoded sense key.  Try retries and hope
			 * that will fix the problem.  Otherwise, we're
			 * dead.
			 */
			EPRINTF("sderror:  undecoded sense key error\n");
			sd_print_cmd(c, un);
			sd_error_message(c, dsi);
			goto SDERROR_RETRY;
		}

	/*
	 * Process busy error.  Try retries and hope that
	 * it'll be ready soon.
	 */
	} else if (c->c_scb.busy) {
		log(LOG_ERR, "sd%d:  sderror: busy error\n", SDNUM(un));
		sd_print_cmd(c, un);
		sd_error_message(c, dsi);
		goto SDERROR_RETRY;

	/*
	 * Process reservation error.  Abort operation.
	 */
	} else if (c->c_scb.busy  &&  c->c_scb.is) {
		log(LOG_ERR, "sd%d:  sderror: reservation conflict error\n",
			SDNUM(un));
		sd_print_cmd(c, un);
		sd_error_message(c, dsi);
		return (real_error);

	/*
	 * Have left over residue data from last command.
	 * Do retries and hope this fixes it...
	 */
	} else  if (resid != 0) {
		EPRINTF1("sderror:  residue error, residue= %d\n", resid);
		sd_print_cmd(c, un);
		sd_error_message(c, dsi);
		goto SDERROR_RETRY;

	/*
	 * Have an unknown error.  Don't know what went wrong.
	 * Do retries and hope this fixes it...
	 */
	} else {
		EPRINTF("sderror:  unknown error\n");
		sd_print_cmd(c, un);
		sd_error_message(c, dsi);
		goto SDERROR_RETRY;
	}

	/*
	 * Process command retries and rezeros here.
	 * Do retries first.
	 */
SDERROR_RETRY:
	if (dsi->un_retries++ < MAX_RETRIES) {
		if ((dsi->un_retries + dsi->un_restores) > sd_retry)
			sderrmsg(c, un, bp, "retry");

		DPRINTF1("sderror:  un_cmd= 0x%x  ", un->un_cmd);
		/* sd_print_cmd(c, un); */

		dsi->un_openf = RETRYING;
		sdmkcdb(c, un);
		if ((*c->c_ss->scs_cmd)(c, un, 1) != 0) {
			log(LOG_ERR, "sd%d:  sderror: retry failed\n",
								SDNUM(un));
			return (real_error);
		}
		return (more_processing);

	/*
	 * Retries exhausted, try restore
	 */
	} else if (++dsi->un_restores < MAX_RESTORES) {
		if (dsi->un_restores > EL_REST)
			sderrmsg(c, un, bp, "restore");

		DPRINTF1("sderror:  un_cmd= 0x%x", un->un_cmd);
		/* sd_print_cmd(c, un); */

		dsi->un_openf = RETRYING;
		dsi->un_retries = 0;
		un->un_cmd = SC_REZERO_UNIT;
		sdmkcdb(c, un);
		(void) (*c->c_ss->scs_cmd)(c, un, 1);
		return (more_processing);

	/*
	 * Restores and retries exhausted, die!
	 */
	} else {
		/* complete failure */
		sderrmsg(c, un, bp, "failed");
		dsi->un_openf = OPEN;
		return (real_error);
	}
}


/*
 * Command failed, need to run a request sense command to determine why.
 */
static
sdintr_sense(c, dsi, un, resid)
	register struct scsi_ctlr *c;
	register struct scsi_disk *dsi;
	register struct scsi_unit *un;
	register u_int resid;
{

	/*
	 * Save away old command state.
	 */
	un->un_saved_cmd.saved_scb = c->c_scb;
	un->un_saved_cmd.saved_cdb = c->c_cdb;
	un->un_saved_cmd.saved_resid = resid;
	un->un_saved_cmd.saved_dma_addr = un->un_dma_addr;
	un->un_saved_cmd.saved_dma_count = un->un_dma_count;
	/*
	 * Note that s?start will call sdmkcdb, which
	 * will notice that the flag is set and not do
	 * the copy of the cdb, doing a request sense
	 * rather than the normal command.
	 */
	DPRINTF("sdintr:  getting sense\n");
	un->un_flags |= SC_UNF_GET_SENSE;
	dsi->un_openf = SENSING;
	un->un_cmd = SC_REQUEST_SENSE;
	(*un->un_c->c_ss->scs_go)(un->un_mc);
}


/*
 * Cleanup after running request sense command to see why the real
 * command failed.
 */
static
sdintr_ran_sense(c, dsi, un, resid_ptr)
	register struct scsi_ctlr *c;
	register struct scsi_disk *dsi;
	register struct scsi_unit *un;
	register u_int *resid_ptr;
{
	register struct scsi_ext_sense *ssd;

	/*
	 * Check if request sense command failed.  This should
	 * never happen!
	 */
	un->un_flags &= ~SC_UNF_GET_SENSE;
	dsi->un_openf = OPEN;
	if (c->c_scb.chk) {
		log(LOG_ERR, "sd%d:  request sense failed\n",
		       SDNUM(un));
	}

	c->c_scb = un->un_saved_cmd.saved_scb;
	c->c_cdb = un->un_saved_cmd.saved_cdb;
	*resid_ptr = un->un_saved_cmd.saved_resid;
	un->un_dma_addr = un->un_saved_cmd.saved_dma_addr;
	un->un_dma_count = un->un_saved_cmd.saved_dma_count;
	un->un_flags &= ~SC_UNF_GET_SENSE;
	un->un_cmd = dsi->un_last_cmd;
	dsi->un_openf = OPEN;

	/*
	 * Special processing for Adaptec ACB-4000 disk controller.
	 */
	if (dsi->un_ctype == CTYPE_ACB4000) {
		sdintr_adaptec(dsi);
	}

	/*
	 * Log error information.
	 */
	ssd = (struct scsi_ext_sense *)dsi->un_sense;
	dsi->un_err_resid = *resid_ptr;
	dsi->un_status = ssd->key;

	dsi->un_err_blkno = (ssd->info_1 << 24) | (ssd->info_2 << 16) |
			    (ssd->info_3 << 8)  | ssd->info_4;
	if (dsi->un_err_blkno == 0  ||  !ssd->adr_val) {
		/* No supplied block number, use original value */
		EPRINTF("sdintr_ran_sense:  synthesizing block number\n");
		dsi->un_err_blkno = un->un_blkno;
	}

#ifdef	SDDEBUG
	/* dump sense info on screen */
	if (sd_debug > 1) {
		sd_error_message(c, dsi);
	}
#endif	SDDEBUG
}


/*
 * Cleanup after running request sense command to see why the real
 * command failed.
 */
static
sd_fix_block(c, dsi, un, type)
	register struct scsi_ctlr *c;
	register struct scsi_disk *dsi;
	register struct scsi_unit *un;
	short type;
{
	register int i;
#ifdef	lint
	c = c;
	dsi = dsi;
#endif	lint

	if (type == SE_RETRYABLE) {
		if (dsi->un_bad_index == 0)
			goto SD_SAVE;

		/*
		 * Search bad block log for match.  If found,
		 * increment counter.  If reporting theshold passed,
		 * inform user.  If remap threshold passed, reassign
		 * block.  Otherwise, just log it.
		 */
		for (i=0; i < dsi->un_bad_index; i++) {

			/* Didn't find it, try next entry */
			if (dsi->un_bad[i].block != dsi->un_err_blkno)
				continue;

			/* Found it, check if we need to reassign the block */
			if ((dsi->un_bad[i].retries)++ >= MAX_FAILS) {

				log(LOG_ERR,
					"sd%d:  block 0x%x needs mapping\n",
					SDNUM(un), dsi->un_bad[i].block);
				type = SE_FATAL;
			}
			goto SD_FIX_BLK;
		}
SD_SAVE:
		if (dsi->un_bad_index == NBAD) {
			EPRINTF1("sd%d:  no storage for error logging\n",
			   	 SDNUM(un));
			return;
		}
		EPRINTF("si_fix_block:  logging marginal block\n");
		i = dsi->un_bad_index++;
		dsi->un_bad[i].block = dsi->un_err_blkno;
		dsi->un_bad[i].retries = 1;
	}


SD_FIX_BLK:
	/* Check if need to warn user */
	if (dsi->un_bad[i].retries > EL_FAILS) {
		log(LOG_ERR, "sd%d:  warning, block 0x%x has failed %d times\n",
			SDNUM(un), dsi->un_bad[i].block,
			dsi->un_bad[i].retries);
	}

	/* if hard failure, reassign bad block */
	if ((type == SE_FATAL)  &&  (dsi->un_ctype != CTYPE_ACB4000)) {
		EPRINTF("sd_fix_block:  reassign\n");

#ifdef	SD_REASSIGN
		log(LOG_ERR, "sd%d:  reassigning defective block %d\n",
		       SDNUM(un), dsi->un_bad[i].block);
		dsi->un_bad[i].retry) = 0;	/* reset retry count */
		/*
		 * Save away old command state.
		 */
		un->un_saved_cmd.saved_scb = c->c_scb;
		un->un_saved_cmd.saved_cdb = c->c_cdb;
		un->un_saved_cmd.saved_resid = resid;
		un->un_saved_cmd.saved_dma_addr = un->un_dma_addr;
		un->un_saved_cmd.saved_dma_count = un->un_dma_count;
		/*
		 * Note that s?start will call sdmkcdb, which
		 * will notice that the flag is set and not do
		 * the copy of the cdb, doing a request sense
		 * rather than the normal command.
		 */
		un->un_flags |= SC_UNF_GET_SENSE;
		dsi->un_openf = MAPPING;
		un->un_cmd = SC_REASSIGN_BLOCK;
		un->un_blkno = dsi->un_bad[i].block;
		sdmkcdb(c, un);
		(void) (*c->c_ss->scs_cmd)(c, un, 1);
		return (more_processing);
#endif	SD_REASSIGN
	}
}


/*
 * Cleanup after running reassign block command.
 */
static
sdintr_ran_reassign(c, dsi, un, resid_ptr)
	register struct scsi_ctlr *c;
	register struct scsi_disk *dsi;
	register struct scsi_unit *un;
	register u_int *resid_ptr;
{
	/*
	 * Check if reassign command failed.
	 */
	un->un_flags &= ~SC_UNF_GET_SENSE;
	dsi->un_openf = OPEN;
	if (c->c_scb.chk)
		log(LOG_ERR, "sd%d:  reassign block failed\n", SDNUM(un));

	c->c_scb = un->un_saved_cmd.saved_scb;
	c->c_cdb = un->un_saved_cmd.saved_cdb;
	*resid_ptr = un->un_saved_cmd.saved_resid;
	un->un_dma_addr = un->un_saved_cmd.saved_dma_addr;
	un->un_dma_count = un->un_saved_cmd.saved_dma_count;
	un->un_flags &= ~SC_UNF_GET_SENSE;
	un->un_cmd = dsi->un_last_cmd;
	dsi->un_openf = OPEN;
}


/*
 * This routine performs raw read operations.  It is called from the
 * device switch at normal priority.  It uses a per-unit buffer for the
 * operation.
 */
sdread(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	register struct scsi_unit *un;
	register int unit;

	DPRINTF("sdread:\n");
	unit = SDUNIT(dev);
	if (unit >= nsdisk) {
		EPRINTF("sdread:  invalid unit\n");
		return (ENXIO);
	}
	/*
	 * The following tests assume a block size which is power of 2.
	 * This allows a bit mask operation to be used instead of a
	 * divide operation thus saving considerable time.
	 */
	if (uio->uio_offset & (DEV_BSIZE -1)) {
		EPRINTF1("sdread:  block address not modulo %d\n",
			DEV_BSIZE);
		return (EINVAL);
	}
	if (uio->uio_iov->iov_len & (DEV_BSIZE -1)) {
		EPRINTF1("sdread:  block length not modulo %d\n",
			DEV_BSIZE);
		return (EINVAL);
	}
	un = &sdunits[unit];
	return (physio(sdstrategy, &un->un_rbuf, dev, B_READ, minphys, uio));
}


/*
 * This routine performs raw write operations.  It is called from the
 * device switch at normal priority.  It uses a per-unit buffer for the
 * operation.
 */
sdwrite(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	register struct scsi_unit *un;
	register int unit;

	DPRINTF("sdwrite:\n");
	unit = SDUNIT(dev);
	if (unit >= nsdisk) {
		EPRINTF("sdwrite:  invalid unit\n");
		return (ENXIO);
	}
	/*
	 * The following tests assume a block size which is power of 2.
	 * This allows a bit mask operation to be used instead of a
	 * divide operation thus saving considerable time.
	 */
	if (uio->uio_offset & (DEV_BSIZE -1)) {
		EPRINTF1("sdwrite:  block address not modulo %d\n",
			DEV_BSIZE);
		return (EINVAL);
	}
	if (uio->uio_iov->iov_len & (DEV_BSIZE -1)) {
		EPRINTF1("sdwrite:  block length not modulo %d\n",
			DEV_BSIZE);
		return (EINVAL);
	}
	un = &sdunits[unit];
	return (physio(sdstrategy, &un->un_rbuf, dev, B_WRITE, minphys, uio));
}


/*
 * This routine implements the ioctl calls.  It is called
 * from the device switch at normal priority.
 */
/*ARGSUSED*/
sdioctl(dev, cmd, data, flag)
	dev_t dev;
	register int cmd;
	register caddr_t data;
	int flag;
{
	register struct scsi_unit *un;
	register struct scsi_disk *dsi;
	register struct disklabel *lp;
	register struct dk_info *inf;
	register struct dk_conf *conf;
	register struct dk_diag *diag;
	register int unit;
	register int i;
	int error = 0;
	int s;

	DPRINTF("sdioctl:\n");
	unit = SDUNIT(dev);
	if (unit >= nsdisk) {
		EPRINTF("sdioctl:  invalid unit\n");
		return (ENXIO);
	}
	un = &sdunits[unit];
	dsi = &sdisk[unit];
	lp = &dsi->un_label;
	switch (cmd) {

	/*
	 * Return info concerning the controller.
	 */
	case DKIOCINFO:
		EPRINTF("sdioctl:  get info\n");
		inf = (struct dk_info *)data;
		inf->dki_ctlr = getdevaddr(un->un_mc->mc_addr);
		inf->dki_unit = un->un_md->md_slave;

		switch (dsi->un_ctype) {
		case CTYPE_MD21:
			inf->dki_ctype = DKC_MD21;
			break;
		case CTYPE_ACB4000:
			inf->dki_ctype = DKC_ACB4000;
			break;
		default:
			inf->dki_ctype = DKC_MD21;
			break;
		}

		inf->dki_flags = DKI_FMTVOL;
		break;

	/*
	 * Return configuration info
	 */
	case DKIOCGCONF:
		EPRINTF("sdioctl:  get configuration info\n");
		conf = (struct dk_conf *)data;
		switch (dsi->un_ctype) {
		case CTYPE_MD21:
			conf->dkc_ctype = DKC_MD21;
			break;
		case CTYPE_ACB4000:
			conf->dkc_ctype = DKC_ACB4000;
			break;
		default:
			conf->dkc_ctype = DKC_MD21;
			break;
		}
		(void) strncpy(conf->dkc_dname, "sd", DK_DEVLEN);
		conf->dkc_flags = DKI_FMTVOL;
		conf->dkc_cnum = un->un_mc->mc_ctlr;
		/* conf->dkc_addr = getdevaddr(un->un_mc->mc_addr); */
		conf->dkc_space = un->un_mc->mc_space;
		conf->dkc_prio = un->un_mc->mc_intpri;
		if (un->un_mc->mc_intr)
			conf->dkc_vec = un->un_mc->mc_intr->v_vec;
		else
			conf->dkc_vec = 0;
		/* (void) strncpy(conf->dkc_cname, un->un_c->c_name, DK_DEVLEN); */
		conf->dkc_unit = un->un_md->md_unit;
		conf->dkc_slave = un->un_md->md_slave;
		break;

	/*
	 * Get error status from last command.
	 */
	case DKIOCGDIAG:
		diag = (struct dk_diag *) data;
		diag->dkd_errcmd  = dsi->un_last_cmd;
		diag->dkd_errsect = dsi->un_err_blkno;
		diag->dkd_errno    = dsi->un_status;
		diag->dkd_errtype  = dsi->un_status;
		diag->dkd_errlevel = dsi->un_status;
		break;

	/*
	 * Run a generic command.
	 */
	case DKIOCSCMD:
#ifdef	FORMAT
		EPRINTF("sdioctl:  run special command\n");
		error = sdioctl_cmd(dev, un, dsi, data);
#endif	FORMAT
		break;

	case DIOCGDINFO:
		*(struct disklabel *)data = *lp;
		break;

	case DIOCGPART:
		((struct partinfo *)data)->disklab = lp;
		((struct partinfo *)data)->part =
			&lp->d_partitions[LPART(dev)];
		break;

	case DIOCSDINFO:
		if ((flag & FWRITE) == 0)
			error = EBADF;
		else
			error = setdisklabel(lp, (struct disklabel *)data,
			    (dsi->un_openf == OPENRAW) ? 0 : dsi->un_openpart);
		break;

	case DIOCWLABEL:
		if ((flag & FWRITE) == 0)
			error = EBADF;
		else
			dsi->un_wlabel = *(int *)data;
		break;


	case DIOCWDINFO:
		if ((flag & FWRITE) == 0)
			error = EBADF;
		else if ((error = setdisklabel(lp, (struct disklabel *)data,
		    (dsi->un_openf == OPENRAW) ? 0 : dsi->un_openpart)) == 0) {
			int wlab;

			dsi->un_openf = OPEN;
			/* simulate opening partition 0 so write succeeds */
			dsi->un_openpart |= (1 << 0);		/* XXX */
			wlab = dsi->un_wlabel;
			dsi->un_wlabel = 1;
			error = writedisklabel(dev, sdstrategy, lp);
			dsi->un_openpart = dsi->un_copenpart|dsi->un_bopenpart;
			dsi->un_wlabel = wlab;
		}
		break;

	/*
	 * Handle unknown ioctls here.
	 */
	default:
		EPRINTF("sdioctl:  unknown ioctl\n");
		error = ENOTTY;
		break;
	}
	return(error);
}


/*
 * Run a command for sdioctl.
 */
#ifdef	FORMAT
static
sdioctl_cmd(dev, un, dsi, data)
	dev_t dev;
	register struct scsi_unit *un;
	register struct scsi_disk *dsi;
	caddr_t data;
{
	register struct dk_cmd *com;
	int err;
	int s;

	EPRINTF("sdioctl_cmd:\n");

	com = (struct dk_cmd *)data;
#ifdef	SDDEBUG
	if (sd_debug) {
		printf("sdioctl_cmd:  cmd= %x  blk= %x  cnt= %x  "
				com->dkc_cmd, com->dkc_blkno, com->dkc_secnt);
		printf("buf addr= %x  buflen= 0x%x\n",
				com->dkc_bufaddr, com->dkc_buflen);
	}
#endif	SDDEBUG
	/*
	 * Check the parameters.
	 */
	switch (com->dkc_cmd) {
	case SC_READ:
		EPRINTF("sdioctl_cmd:  read\n");
		dsi->un_options = SD_SILENT | SD_DVMA_IN;
		s = splx(pritospl(un->un_mc->mc_intpri));
		err = sdcmd(dev, SC_SPECIAL_READ, com->dkc_blkno,
			    (int)com->dkc_buflen, (caddr_t)com->dkc_bufaddr);
		(void) splx(s);
		dsi->un_options &= ~(SD_SILENT | SD_DVMA_IN);
		return (err);

	case SC_WRITE:
		EPRINTF("sdioctl_cmd:  write\n");
		dsi->un_options = SD_SILENT | SD_DVMA_OUT;
		s = splx(pritospl(un->un_mc->mc_intpri));
		err = sdcmd(dev, SC_SPECIAL_WRITE, com->dkc_blkno,
			    (int)com->dkc_buflen, (caddr_t)com->dkc_bufaddr);
		(void) splx(s);
		dsi->un_options &= ~(SD_SILENT | SD_DVMA_OUT);
		return (err);

	case SC_MODE_SELECT:
		EPRINTF("sdioctl_cmd:  mode select\n");
		dsi->un_options = SD_SILENT | SD_DVMA_OUT;
		s = splx(pritospl(un->un_mc->mc_intpri));
		err = sdcmd(dev, SC_MODE_SELECT, com->dkc_blkno,
			    (int)com->dkc_buflen, (caddr_t)com->dkc_bufaddr);
		(void) splx(s);
		dsi->un_options &= ~(SD_SILENT | SD_DVMA_OUT);
		return (err);

	case SC_FORMAT:
		EPRINTF("sdioctl_cmd:  format\n");
		dsi->un_options = SD_SILENT | SD_DVMA_OUT;
		s = splx(pritospl(un->un_mc->mc_intpri));
		err = sdcmd(dev, SC_FORMAT, com->dkc_blkno,
			    (int)com->dkc_buflen, (caddr_t)com->dkc_bufaddr);
		(void) splx(s);
		dsi->un_options &= ~(SD_SILENT | SD_DVMA_OUT);
		return (err);

	case SC_READ_DEFECT_LIST:
		EPRINTF("sdioctl_cmd:  read defect list\n");
		dsi->un_options = SD_SILENT | SD_DVMA_IN;
		s = splx(pritospl(un->un_mc->mc_intpri));
		err = sdcmd(dev, SC_SPECIAL_READ, com->dkc_blkno,
			    (int)com->dkc_buflen, (caddr_t)com->dkc_bufaddr);
		(void) splx(s);
		dsi->un_options &= ~(SD_SILENT | SD_DVMA_IN);
		return (err);

	case SC_REASSIGN_BLOCK:
		EPRINTF("sdioctl_cmd:  reassign block\n");
		err = sdcmd(dev, com->dkc_cmd, com->dkc_blkno, 0, (caddr_t)0 );
		return (err);

	case SC_REZERO_UNIT:
		EPRINTF("sdioctl_cmd:  rezero or test_unit_ready\n");
		/* err = sdcmd(dev, com->dkc_cmd, 0, 0, (caddr_t)0 ); */
		/* return (err); */
		return (0);

	default:
		EPRINTF1("sdioctl:  unknown command %x\n", com->dkc_cmd);
		return (EINVAL);
	}
}
#endif	FORMAT


 /*
  * This routine dumps memory to the disk.  It assumes that the memory has
  * already been mapped into mainbus space.  It is called at disk interrupt
  * priority when the system is in trouble.
  */
sddump(dev, addr, blkno, nblk)
	register dev_t dev;
	register caddr_t addr;
	register daddr_t blkno, nblk;
{
	register struct scsi_unit *un;
	register struct partition *pp;
	static int first_time = 1;
	register struct scsi_disk *dsi;

	un = &sdunits[SDUNIT(dev)];

	/*
	 * Check for device online.  Note, if a SCSI bus reset occurred,
	 * all devices are now offline.  Thus, we do a test unit ready.
	 * If it gets a fatal error, it really is offline.
	 */
	if ((un->un_present == 0)  &&
	    (simple(un, SC_TEST_UNIT_READY, 0, 0, 0) > 1))  {
		EPRINTF("sddump:  dump device offline\n");
		return (ENXIO);
	}

	dsi = &sdisk[SDUNIT(dev)];
	pp = &dsi->un_label.d_partitions[LPART(dev)];
	if (blkno >= pp->p_size  ||  (blkno + nblk) > pp->p_size) {
		EPRINTF("sddump:  no place to dump\n");
		return (EINVAL);
	}

	blkno += pp->p_offset;
	if (first_time) {
		/*
		 * After scsi bus reset, it is necessary to
		 * handle a unit attention error.  If the device
		 * fails after that, we assume it's dead and
		 * abort dump.
		 */
		(*un->un_c->c_ss->scs_reset)(un->un_c, 0);
		if (simple(un, SC_TEST_UNIT_READY, 0, 0, 0)  &&
		    simple(un, SC_TEST_UNIT_READY, 0, 0, 0)) {
			EPRINTF("sddump:  disk drive not ready\n");
			return (EIO);
		}
		first_time = 0;
	}
	/*
	 * If write fails, try again.  After two failures,
	 * report failure which kills dump.
	 */
	if (simple(un, SC_WRITE, (int)(addr-DVMA), (int)blkno, (int)nblk)  &&
	    simple(un, SC_WRITE, (int)(addr-DVMA), (int)blkno, (int)nblk)) {
		EPRINTF("sddump:  write failed\n");
		return (EIO);
	}
	return (0);
}


static u_char sd_adaptec_keys[] = {
	0, 4, 4, 4,  2, 4, 4, 4,	/* 0x00-0x07 */
	4, 4, 4, 4,  4, 4, 4, 4,	/* 0x08-0x0f */
	3, 3, 3, 3,  3, 3, 3, 1,	/* 0x10-0x17 */
	1, 1, 5, 5,  1, 1, 1, 1,	/* 0x18-0x1f */
	5, 5, 5, 5,  5, 5, 5, 5,	/* 0x20-0x27 */
	6, 6, 6, 6,  6, 6, 6, 6,	/* 0x28-0x30 */
};
#define MAX_ADAPTEC_KEYS \
	(sizeof(sd_adaptec_keys))


static char *sd_adaptec_error_str[] = {
	"no sense",			/* 0x00 */
	"no index",			/* 0x01 */
	"no seek complete",		/* 0x02 */
	"write fault",			/* 0x03 */
	"drive not ready",		/* 0x04 */
	"drive not selected",		/* 0x05 */
	"no track 00",			/* 0x06 */
	"multiple drives selected",	/* 0x07 */
	"no address",			/* 0x08 */
	"no media loaded",		/* 0x09 */
	"end of media",			/* 0x0a */
	"",				/* 0x0b */
	"",				/* 0x0c */
	"",				/* 0x0d */
	"",				/* 0x0e */
	"",				/* 0x0f */
	"I.D. CRC error",		/* 0x10 */
	"hard data error",		/* 0x11 */
	"no I.D. address mark",		/* 0x12 */
	"no data address mark",		/* 0x13 */
	"record not found",		/* 0x14 */
	"seek error",			/* 0x15 */
	"DMA timeout error",		/* 0x16 */
	"write protected",		/* 0x17 */
	"correctable data error",	/* 0x18 */
	"bad block",			/* 0x19 */
	"interleave error",		/* 0x1a */
	"data transfer failed",		/* 0x1b */
	"bad format",			/* 0x1c */
	"self test failed",		/* 0x1d */
	"defective track",		/* 0x1e */
	"",				/* 0x1f */
	"invalid command",		/* 0x20 */
	"illegal block address",	/* 0x21 */
	"aborted",			/* 0x22 */
	"volume overflow",		/* 0x23 */
	0
};
#define MAX_ADAPTEC_ERROR_STR \
	(sizeof(sd_adaptec_error_str)/sizeof(sd_adaptec_error_str[0]))


static char *sd_emulex_error_str[] = {
	"",				/* 0x00 */
	"",				/* 0x01 */
	"seek incomplete",		/* 0x02 */
	"write fault",			/* 0x03 */
	"drive not ready",		/* 0x04 */
	"drive not selected",		/* 0x05 */
	"no track 0",			/* 0x06 */
	"",				/* 0x07 */
	"",				/* 0x08 */
	"no tape",			/* 0x09 */
	"tape too short",		/* 0x0a */
	"drive timeout",		/* 0x0b */
	"",				/* 0x0c */
	"",				/* 0x0d */
	"",				/* 0x0e */
	"",				/* 0x0f */
	"ID error",			/* 0x10 */
	"hard data error",		/* 0x11 */
	"no address mark",		/* 0x12 */
	"no data field addr mark",	/* 0x13 */
	"block not found",		/* 0x14 */
	"seek error",			/* 0x15 */
	"dma timeout",			/* 0x16 */
	"recoverable error",		/* 0x17 */
	"soft data error",		/* 0x18 */
	"bad block",			/* 0x19 */
	"",				/* 0x1a */
	"",				/* 0x1b */
	"file mark detected",		/* 0x1c */
	"compare error",		/* 0x1d */
	"",				/* 0x1e */
	"",				/* 0x1f */
	"invalid command",		/* 0x20 */
	"invalid address",		/* 0x21 */
	"illegal command",		/* 0x22 */
	"",				/* 0x23 */
	"invalid cdb",			/* 0x24 */
	"invalid lun",			/* 0x25 */
	"",				/* 0x26 */
	"write protected",		/* 0x27 */
	"",				/* 0x28 */
	"reset",			/* 0x29 */
	"mode select changed",		/* 0x2a */
	0
};
#define MAX_EMULEX_ERROR_STR \
	(sizeof(sd_emulex_error_str)/sizeof(sd_emulex_error_str[0]))


static char *sd_key_error_str[] = {
	"no sense",			/* 0x00 */
	"soft error",			/* 0x01 */
	"not ready",			/* 0x02 */
	"medium error",			/* 0x03 */
	"hardware error",		/* 0x04 */
	"illegal request",		/* 0x05 */
	"unit attention",		/* 0x06 */
	"write protected",		/* 0x07 */
	"blank check",			/* 0x08 */
	"vendor unique",		/* 0x09 */
	"copy aborted",			/* 0x0a */
	"aborted command",		/* 0x0b */
	"equal error",			/* 0x0c */
	"volume overflow",		/* 0x0d */
	"miscompare error",		/* 0x0e */
	"reserved",			/* 0x0f */
	0
};
#define MAX_KEY_ERROR_STR \
	(sizeof(sd_key_error_str)/sizeof(sd_key_error_str[0]))


static char *sd_cmds[] = {
	"test unit ready",		/* 0x00 */
	"rezero",			/* 0x01 */
	"<bad cmd>",			/* 0x02 */
	"request sense",		/* 0x03 */
	"format",			/* 0x04 */
	"<bad cmd>",			/* 0x05 */
	"<bad cmd>",			/* 0x06 */
	"reassign>",			/* 0x07 */
	"read",				/* 0x08 */
	"<bad cmd>",			/* 0x09 */
	"write",			/* 0x0a */
	"seek",				/* 0x0b */
};
#define MAX_SD_CMDS \
	(sizeof(sd_cmds)/sizeof(sd_cmds[0]))


/*
 * Translate Adaptec non-extended sense status in to
 * extended sense format.  In other words, generate
 * sense key.
 */
static
sdintr_adaptec(dsi)
	register struct scsi_disk *dsi;
{
	register struct scsi_sense *s;
	register struct scsi_ext_sense *ssd;
	(u_int)ssd = (u_int)s = dsi->un_sense;

	EPRINTF("sdintr_adaptec\n");

	/* Reposition failed block number for extended sense. */
	ssd->info_1 = 0;
	ssd->info_2 = s->high_addr;
	ssd->info_3 = s->mid_addr;
	ssd->info_4 = s->low_addr;

	/* Reposition error code for extended sense. */
	ssd->error_code = s->code;

	/* Synthesize sense key for extended sense. */
	if (s->code < MAX_ADAPTEC_KEYS) {
#ifdef	BUG
		ssd->key = sd_adaptec_keys[s->code];
#else	BUG
		u_char tmp = sd_adaptec_keys[s->code];
		ssd->key = tmp;
#endif	BUG
	}
}


/*
 * Return the text string associated with the sense key value.
 */
static char *
sd_print_key(key_code)
	register u_char key_code;
{
	static char *unknown_key = "unknown key";
	if ((key_code > MAX_KEY_ERROR_STR -1)  ||
	     sd_key_error_str[key_code] == NULL) {

		return (unknown_key);
	}
	return (sd_key_error_str[key_code]);
}


/*
 * Return the text string associated with the secondary
 * error code, if availiable.
 */
static char *
sd_print_error(dsi, error_code)
	register struct scsi_disk *dsi;
	register u_char error_code;
{
	static char *unknown_error = "unknown error";
	switch (dsi->un_ctype) {
	case CTYPE_MD21:
	case CTYPE_CCS:
		if ((MAX_EMULEX_ERROR_STR > error_code)  &&
		    sd_emulex_error_str[error_code] != NULL)
			return (sd_emulex_error_str[error_code]);
		break;

	case CTYPE_ACB4000:
		if (MAX_ADAPTEC_ERROR_STR > error_code  &&
		    sd_adaptec_error_str[error_code] != NULL)
			return (sd_adaptec_error_str[error_code]);
		break;
	}
	return (unknown_error);
}


/*
 * Print the sense key and secondary error codes
 * and dump out the sense bytes.
 */
static
sd_error_message(c, dsi)
	register struct scsi_ctlr *c;
	register struct scsi_disk *dsi;
{
	register struct scsi_ext_sense *ssd;
	register u_char   *cp;
	register int i;
	register u_char error_code;
	struct scsi_unit *un = c->c_un;

	ssd = (struct scsi_ext_sense *)cp = (
		struct scsi_ext_sense *)dsi->un_sense;
	error_code = ssd->error_code;
	log(LOG_ERR, "sd%d error:  sense key(0x%x): %s",
		un - sdunits, ssd->key, sd_print_key(ssd->key));
	if (error_code != 0) {
		addlog(",  error code(0x%x): %s",
		       error_code, sd_print_error(dsi, error_code));
	}

	addlog("\n           sense = ");
	for (i=0; i < sizeof (struct scsi_ext_sense); i++)
		addlog("%x  ", *cp++);
	addlog("\n");
}


static
sd_print_cmd(c, un)
	register struct scsi_ctlr *c;
	register struct scsi_unit *un;
{
	register int x;
	register u_char *y = (u_char *)&(c->c_cdb);
#ifdef	lint
	un = un;
#endif	lint

	log(LOG_ERR, "sd%d:  failed cmd =  ", SDUNIT(un->un_unit));
	for (x = 0; x < CDB_GROUP0; x++)
		addlog("%x  ", *y++);
	addlog("\n");
}


static
sderrmsg(c, un, bp, action)
	register struct scsi_ctlr *c;
	struct scsi_unit *un;
	struct buf *bp;
	char *action;
{
	register volatile struct scsi_ext_sense *ssd;
	register struct scsi_disk *dsi;
	register struct partition *pp;
	char *cmdname;
	u_char error_code;
	u_int blkno;
	int blkno_flag = 1;		/* if false, blkno is meaningless */


	dsi = &sdisk[dkunit(bp)];
	ssd = (struct scsi_ext_sense *)dsi->un_sense;
	pp = &dsi->un_label.d_partitions[LPART(bp->b_dev)];

	/* Decode command name */
	if (un->un_cmd < MAX_SD_CMDS) {
		cmdname = sd_cmds[un->un_cmd];
	} else {
		cmdname = "unknown cmd";
	}

	/* If not a check condition error, block number is invalid */
	if (! c->c_scb.chk)
		blkno_flag = 0;


	/* Compute relative position of bad block */
	blkno = dsi->un_err_blkno - pp->p_offset;

	log(LOG_ERR, "sd%d%c:  %s %s",
		SDNUM(un), LPART(bp->b_dev) + 'a', cmdname, action);
	if (blkno_flag  &&  (dsi->un_err_blkno == 0))
		addlog("\n");
	else
		addlog(",  blk %d  (abs blk %d)\n", blkno, dsi->un_err_blkno);

	error_code = ssd->error_code;
	addlog("       sense key(0x%x): %s",
	       ssd->key, sd_print_key(ssd->key));
	if (error_code != 0) {
		addlog(",  error code(0x%x): %s\n",
		       error_code, sd_print_error(dsi, error_code));
	} else {
		addlog("\n");
	}

}
#endif	NSD > 0
