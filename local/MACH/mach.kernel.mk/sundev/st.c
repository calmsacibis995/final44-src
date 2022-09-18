/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	st.c,v $
 * Revision 2.8  89/07/11  17:40:16  jjc
 * 	Changed to include machine dependent header files from machine/ not sun3/ because the Sun 4 uses this device driver too.
 * 	[89/07/06  16:56:08  jjc]
 * 
 * Revision 2.7  89/03/09  21:46:40  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/25  19:55:47  gm0w
 * 	Added new copyright and fixed includes as part of kernel
 * 	cleanup.
 * 	[89/02/10            jjc]
 * 
 * Revision 2.5  89/01/23  15:30:45  rvb
 * 	Forward declarations for GCC.
 * 	[89/01/22            rvb]
 * 
 * Revision 2.4  88/12/13  13:27:51  mikeg
 * 	In stmkcdb() disallowed disconnects on any SCSI command
 * 	involving a DMA transfer.  This change fixes the 
 * 	odd-byte DMA problem with the Exabyte drives.
 * 
 * Revision 2.3  88/12/07  17:23:49  mikeg
 * 	Entered new st driver from SunOS 3.5 into the Mach
 * 	kernel source tree.  This new driver supports the
 * 	Exabyte 8mm tape drive.
 * 	[88/12/01  14:50:11  mikeg]
 * 
 */
/* @(#)st.c	1.1 87/12/21	Copyr 1987 Sun Micro */


#include <st.h>
#if	NST > 0

#ifndef	lint
static	char sccsid[] = "@(#)st.c       1.1 87/12/21	Copyr 1987 Sun Micro";
#endif

/* #define STDEBUG 			/* Allow compiling of debug code */
/* #define REL4				/* enable release 4.00 mods */

/*
 * Generic Driver for 1/2-inch reel, 1/2-inch cartridge,
 * and 1/4-inch cartridge embedded SCSI tape drives.
 */
#ifndef	REL4
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/dir.h>
#include <sys/conf.h>
#include <sys/user.h>
#include <sys/file.h>
#include <sys/map.h>
#include <sys/vm.h>
#include <sys/mtio.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <sys/kernel.h>

#include <sun/dklabel.h>
#include <sun/dkio.h>

#include <machine/psl.h>
#include <machine/mmu.h>
#include <machine/cpu.h>

#include <sundev/mbvar.h>
#include <sundev/screg.h>
#include <sundev/sireg.h>
#include <sundev/scsi.h>
#include <sundev/streg.h>

#else	REL4
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/user.h>
#include <sys/file.h>
#include <sys/map.h>
#include <sys/vm.h>
#include <sys/mtio.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <sys/types.h>

#include <sun/dklabel.h>
#include <sun/dkio.h>
#include <machine/psl.h>
#include <machine/mmu.h>
#include <machine/cpu.h>
#include <sundev/mbvar.h>
#include <sundev/screg.h>
#include <sundev/sireg.h>
#include <sundev/scsi.h>
#include <sundev/streg.h>
#endif	REL4


extern struct scsi_unit stunits[];
extern struct scsi_unit_subr scsi_unit_subr[];
extern struct scsi_tape stape[];
extern int nstape;
#ifdef	lint
extern int cpu;
#endif	lint


#ifdef	STDEBUG
short st_debug = 3;			/*
					 * 0 = normal operation
					 * 1 = extended error info only
					 * 2 = debug and error info
					 * 3 = all status info
					 */
/* Handy debugging 0, 1, and 2 argument printfs */
#define DPRINTF(str) \
	if (st_debug > 1) printf(str)
#define DPRINTF1(str, arg1) \
	if (st_debug > 1) printf(str,arg1)
#define DPRINTF2(str, arg1, arg2) \
	if (st_debug > 1) printf(str,arg1,arg2)

/* Handy extended error reporting 0, 1, and 2 argument printfs */
#define EPRINTF(str) \
	if (st_debug) printf(str)
#define EPRINTF1(str, arg1) \
	if (st_debug) printf(str,arg1)
#define EPRINTF2(str, arg1, arg2) \
	if (st_debug) printf(str,arg1,arg2)

#else	STDEBUG
#define DPRINTF(str)
#define DPRINTF1(str, arg2)
#define DPRINTF2(str, arg1, arg2)
#define EPRINTF(str)
#define EPRINTF1(str, arg2)
#define EPRINTF2(str, arg1, arg2)
#endif	STDEBUG



/*
 * NOTES:
 *    This device driver supports both fixed length block I/O or
 * variable length block I/O.  Fixed length I/O is common for
 * 1/4-inch tape drives.  Variable length is common for 1/2-inch
 * reel (Pertec) tapes.  For HI/TC no standard exists as of this time.
 *
 *   Command timeouts don't work 100% of the time.  Si raises
 * it's interrupt priority so high that timeouts are blocked.
 * Unfortunately, this is usually triggered by spurious phase changes
 * and it doesn't appear to ever lower it.  Under these conditions,
 * the whole system will hang.
 *
 *    Generic tape device operation assumes the device is capable
 * of fixed-length I/O.  A mode sense is done to obtain the device's
 * physical record size.  If the record size is zero, the default
 * physical record size (512 bytes/record) will be used.  This
 * will be checked at mode select time.  Also, only one density/format
 * is supported, density 0.
 *
 *    Be careful when modifying the following variables as these
 * are used throughout this driver:  dsi->un_lastiow, dsi->next_block,
 * dsi->un_last_block, dsi->un_openf, dsi->un_ctype, dsi->un_eof,
 * un->un_last_bcount, un->un_last_count, dsi->un_offset,
 * and dsi->un_iovlen.
 */


/*
 * Bits in minor device.
 */
#define STUNIT(dev)	(minor(dev) & 0x03)
#define T_NOREWIND	0x04
#define DENSITY_6250	0x08

#define MAXSTBUF	3		/* Max outstanding buffers per unit */
#define INF		1000000000


/*
 * Return a pointer to this unit's unit structure.
 */
stunitptr(md)
	register struct mb_device *md;
{
	return ((int) &stunits[md->md_unit]);
}


static
sttimer(dev)
	register dev_t dev;
{
	register struct scsi_tape *dsi;
	register struct scsi_unit *un;
	register struct scsi_ctlr *c;
	register u_int	unit;

	unit = STUNIT(dev);
	un = &stunits[unit];
	dsi = &stape[unit];
	c = un->un_c;

	if (dsi->un_openf >= OPENING) {
#ifdef	ST_TIMEOUT
		if ((dsi->un_timeout > 0)  &&  (--dsi->un_timeout == 0)) {

			/* Process command timeout for normal I/O operations */
			printf("st%d:  sttimer: I/O request timeout\n", unit);
			if ((*c->c_ss->scs_deque)(c, un)) {
				/* Can't Find CDB I/O request to kill, help! */
				printf("st%d:  sttimer: can't abort request\n",
					unit);
				(*un->un_c->c_ss->scs_reset)(un->un_c, 0);
				dsi->un_openf = CLOSED;
			}
		} else {
			timeout(sttimer, (caddr_t)dev, 60*hz);
			EPRINTF2("sttimer:  running, open= %d,  timeout= %d\n",
				 dsi->un_openf, dsi->un_timeout);
		}
#endif	ST_TIMEOUT

	} else {
		/* Process tape opening delay timeout */
		DPRINTF("sttimer:  running...\n");
		wakeup((caddr_t)dev);
	}
}


/*
 * Attach device (boot time).  Initialize data structures and
 * allocate inquiry/mode_select/mode_sense/sense buffer.
 */
stattach(md)
	register struct mb_device *md;
{
	register struct scsi_unit *un;
	register struct scsi_tape *dsi;
	register struct scsi_inquiry_data *sid;
	DPRINTF("stattach:\n");

	un = &stunits[md->md_unit];
	dsi = &stape[md->md_unit];
	un->un_md = md;
	un->un_mc = md->md_mc;
	un->un_unit = md->md_unit;
	un->un_target = TARGET(md->md_slave);
	un->un_lun = LUN(md->md_slave);
	un->un_ss = &scsi_unit_subr[TYPE(md->md_flags)];
	un->un_blkno = 0;
	un->un_count = 0;
	un->un_last_count = 1;			/* Must not match un_count */
	un->un_last_bcount = 0;
	un->un_present = 0;

	dsi->un_bufcnt =0;			/* No I/O request in que */
	dsi->un_iovlen =0;			/* Guarantee block size check */
	dsi->un_offset =0;
	dsi->un_dev_bsize = 0;
	dsi->un_lastior = 0;
	dsi->un_lastiow = 0;
	dsi->un_next_block = 0;			/* Assume file #0, Blk #0 */
	dsi->un_last_block = INF;
	dsi->un_fileno = 0;
	dsi->un_eof = ST_NO_EOF;

	dsi->un_timeout = 0;			/* Disable timeouts */
	dsi->un_reset_occurred = 1;		/* Force init */
	dsi->un_density = SC_DEN6250;
	dsi->un_openf = CLOSED;
	dsi->un_ctype = ST_TYPE_INVALID;	/* Set drive defaults */
	dsi->un_flags = 0;			/* Special un->un_flags copy */
	dsi->un_cipher = 0;			/* For Sun-2 Cipher */


	/*
	 * Allocate space for mode_select/inquiry/request_sense data in
	 * data in Multibus memory.  Be sure to allocate sufficient space
	 * to force word alignment in case it's not there already.
	 */
	sid = (struct scsi_inquiry_data *)rmalloc(iopbmap,
		(long)(sizeof(struct scsi_inquiry_data) +4));
	if (sid == NULL) {
		printf("st%d:  stattach: no space for inquiry data\n",
			STUNIT(un->un_unit));
		return;
	}
	while ((u_int)sid & 0x03)
		((u_int)sid)++;			/* Align it */
	dsi->un_mspl = (int)sid;

	/*
	 * Each tape unit will have its own DVMA buffer.  The
	 * buffer is used to hold inquiry data, mode select/sense,
	 * and request sense info.  Needless to say we keep this
	 * buffer forever.
	 */
	EPRINTF2("st%d:  stattach: buffer= 0x%x", STUNIT(un->un_unit),sid);
	EPRINTF2(", dsi= 0x%x, un= 0x%x\n", dsi, un);
}

/*
 * Initialize tape device (called by stopen).
 * Check if device on-line and identify who it is.
 */
static
stinit(dev)
	dev_t dev;
{
	register u_int unit;
	register struct scsi_tape *dsi;
	register struct scsi_unit *un;
	register struct scsi_inquiry_data *sid;
	struct st_sense *ssd;
	register int i;
	register u_char flags;

	unit = STUNIT(dev);
	un = &stunits[unit];
	dsi = &stape[unit];
	flags = dsi->un_flags;			/* save current settings */

	/* DPRINTF("stinit:\n"); */
	/* DPRINTF2("      un= 0x%x, un->un_c= 0x%x\n", un, un->un_c); */

	(int)ssd = (int)sid = dsi->un_mspl;
#ifdef	lint
	(int)sid = (int)ssd;
	(int)sid = (int)un;
#endif	lint

	/*
	 * If first time for drive or after it had a SE_FATAL error
	 * to a full initialization pass to check it out.  Otherwise,
	 * if we already know who it is, use the short check.
	 */
	if ((dsi->un_ctype <= ST_TYPE_DEFAULT)  ||  ! un->un_present) {
		bzero((caddr_t)sid, sizeof (struct scsi_inquiry_data));
		un->un_present = 1;
		dsi->un_ctype = ST_TYPE_DEFAULT;	/* Set drive defaults */
	}

#ifdef	STDEBUG
	if (st_debug > 2)
		st_print_sid_buffer(sid, 32);
#endif	STDEBUG

	/*
	 * Check if the tape drive is ready.  If it's not ready then
	 * either the tape has been changed, or it's offline, or maybe
	 * it's not there (offline).  Note, this also catches power-on reset
	 * and tape change conditions as they both generate unit attention
	 * check condition status.  If the drive is auto-loading, we'll
	 * get a busy indication until it's done.  In any case, it
	 * probably would be a good idea to set the reset occurred
	 * indicator.
	 */
#ifdef	ST_SYSGEN
	if (IS_SYSGEN(dsi)  &&  dsi->un_lastior) {
			EPRINTF("stinit:  Sysgen found in read mode\n\n");
			goto STINIT_EXIT;
	}
#endif	ST_SYSGEN

	dsi->un_flags = SC_UNF_NO_DISCON;	/* no disconnects */
	dsi->un_openf = OPENING;		/* special error handling */
	if (stcmd(dev, SC_TEST_UNIT_READY, 0) == 0) {

		/* Major SCSI device failure, stop! */
		EPRINTF("stinit:  check condition\n");
		if (dsi->un_openf == CLOSED) {
			uprintf("st%d:  hardware failure, check drive\n", unit);
			dsi->un_flags = flags;	/* restore saved flags */
			return (EIO);
		}
		/*
		 * Last chance -- If this is the first command after
		 * a SCSI reset, we'll always get a unit attention error
		 * the first time.  Giving it one more chance neatly
		 * hides it.  By the way retrying this command also
		 * provides the necessary delay if you just inserted
		 * the tape and tried to access it.  Don't change the
		 * number of test unit ready retries!
		 *
		 * Note, if sysgen support is enabled, we'll have to do
		 * a request sense after the first test unit ready or
		 * the dumb sysgen won't ever clear its check condition.
		 */
#ifdef	ST_SYSGEN
		if (IS_SYSGEN(dsi)  ||  IS_DEFAULT(dsi)) {
			dsi->un_openf = OPENING;
			if (stcmd(dev, SC_REQUEST_SENSE, 0) == 0  &&
			    dsi->un_openf == OPENING_SYSGEN) {
				EPRINTF("stinit:  Sysgen tape drive found\n\n");
				dsi->un_flags = SC_UNF_NO_DISCON;
				goto STINIT_EXIT;
			}
		}
#endif	ST_SYSGEN

		/*
		 * Auto-loading tape drives need a few seconds
		 * after tape insertion to figure out that a tape
		 * has been inserted.
		 */
		dsi->un_reset_occurred = 1;

		dsi->un_openf = OPENING_DELAY;
		timeout(sttimer, (caddr_t)dev, 3*hz);
		(void) sleep((caddr_t) dev, PRIBIO);
		untimeout(sttimer, (caddr_t)dev);

		/*
		 * Do 2 test unit readys to survive the case of
		 * the tape drive finish auto-loading between the
		 * first test unit ready and here.  We have to do it
		 * twice to get both the unit attention and the
		 * drive not ready errors.  If this fails, then
		 * either we're not finished auto-loading or
		 * the drive really is offline.
		 */
		 dsi->un_openf = OPENING;
		(void) stcmd(dev, SC_TEST_UNIT_READY, 0);
		dsi->un_openf = OPENING;
		(void) stcmd(dev, SC_TEST_UNIT_READY, 0);

		if (dsi->un_openf == OPEN_FAILED_LOADING) {
			/*
			 * This takes care of auto-load busy status until the
			 * tape drive is ready.  Each loop sleeps for 2 Sec.
			 * to reduce CPU loading as this process can take
			 * quite a while.
			 */
			i=MAX_AUTOLOAD_DELAY;
			dsi->un_openf = OPENING;
			while((stcmd(dev, SC_TEST_UNIT_READY, 0) == 0)  &&
			      (i-- > 0))  {
				dsi->un_openf = OPENING_DELAY;
				timeout(sttimer, (caddr_t)dev, 2*hz);
				(void) sleep((caddr_t) dev, PRIBIO);
			}
			untimeout(sttimer, (caddr_t)dev);
		}
		bzero((caddr_t)sid, sizeof (struct scsi_inquiry_data));
		if (dsi->un_openf == OPEN_FAILED_LOADING) {
			uprintf("st%d:  loading tape, try again...\n", unit);
			dsi->un_err_resid = 0;
			dsi->un_err_fileno = dsi->un_fileno;
			dsi->un_err_blkno = dsi->un_next_block;
			dsi->un_status = SC_NOT_READY;

			dsi->un_reset_occurred = 1;
			dsi->un_openf = CLOSED;
			dsi->un_flags = flags;	/* restore saved flags */
			return (EIO);
		} else if (dsi->un_openf == OPEN_FAILED_TAPE) {
			uprintf("st%d:  no tape loaded or drive offline\n", unit);
			dsi->un_err_resid = 0;
			dsi->un_err_fileno = dsi->un_fileno;
			dsi->un_err_blkno = dsi->un_next_block;
			dsi->un_status = SC_NOT_READY;

			dsi->un_reset_occurred = 1;
			dsi->un_openf = CLOSED;
			dsi->un_flags = flags;	/* restore saved flags */
			return (EIO);
		}

		/*
		 * If we had a check condition on the initial test unit
		 * ready we may have had a media change error.  Do a
		 * mode sense to check.  Note, if this is the first
		 * time or a Sysgen controller, don't do it!
		 * Note, this will set a read-only bit via
		 * stintr_opening routine which can be checked in stopen.
		 */
		EPRINTF("stinit:  after check condition\n");
		if (dsi->un_ctype != ST_TYPE_DEFAULT  &&
		    dsi->un_ctype !=  ST_TYPE_SYSGEN) {
			EPRINTF("stinit:  doing mode sense\n");
			dsi->un_openf = OPENING;
			(void) stcmd(dev, SC_MODE_SENSE, 0);
		}
	}
	/*
	 * If this is the first time that this device has been opened,
	 * we'll need to figure out what type of tape drive it is.  After
	 * that we'll always remember it.
	 */
	if (dsi->un_ctype != ST_TYPE_DEFAULT) {
		EPRINTF("stinit:  quick exit\n");
		dsi->un_openf = OPEN;		/* normal error handling */
		dsi->un_flags = flags;		/* restore saved flags */
		return (0);
	}

	EPRINTF("stinit:  doing inquiry\n");
	dsi->un_openf = OPENING;
	if (stcmd(dev, SC_INQUIRY, 0) == 0) {
#ifdef	ST_SYSGEN
		/*
		 * Check for Sysgen tape controller.  This is done by
		 * doing a mode sense followed by a request sense after
		 * it fails.  If the error code is 0x20, then we're
		 * talking to a sysgen.  Otherwise, it's a non-CCS tape
		 * controller.  Also, make sure there is a tape loaded
		 * in the tape drive, or else !
		 */
		dsi->un_openf = OPENING;
		if (stcmd(dev, SC_REQUEST_SENSE, 0) != 0) {
			if (dsi->un_openf == OPENING_SYSGEN) {
#ifdef	sun2
				/*
				* Check for a cipher tape drive if we're on
				* a Sun-2/120 system.  A cipher tape driver
				* can be recognized by issuing the vendor
				* unique read extended status command.  Note,
				* that afterwards that a SCSI bus reset will
				* be required to reset the QIC-02 bus.  This
				* is necessary because it does not support the
				* QIC-24 format (it erases the tape instead).
				*
				* Do a cipher read status command to see
				* if it's an old QIC-11 drive.  If command
				* works, we'll have to reset the bus to
				* continue.  And of course, we have to
				* do a test unit ready to get rid of reset
				* status.
				*/
				dsi->un_cipher = 0;
				if ((cpu == CPU_SUN2_120)  &&
				    (stcmd(dev, SC_READ_XSTATUS_CIPHER, 0) != 0)) {
					EPRINTF("stinit:  Sun2 Cipher drive found\n");
					dsi->un_cipher = 1;
					(*un->un_c->c_ss->scs_reset)(un->un_c, 0);
					dsi->un_openf = OPENING;
					(void) stcmd(dev, SC_TEST_UNIT_READY, 0);
					dsi->un_openf = OPENING;
					(void) stcmd(dev, SC_REQUEST_SENSE, 0);
				} else if ((cpu == CPU_SUN2_120)  &&  
				    (stcmd(dev, SC_REQUEST_SENSE, 0) != 0)) {
					EPRINTF("stinit:  Sun2 tape drive found\n");
				}
#endif	sun2
				EPRINTF("stinit:  Sysgen tape controller found\n\n");
				dsi->un_ctype = ST_TYPE_SYSGEN;
				dsi->un_options = ST_SYSGEN_OPTIONS;
				dsi->un_dev_bsize = ST_SYSGEN_BSIZE;
				goto STINIT_EXIT;

			} else if (dsi->un_openf == OPEN_FAILED_TAPE) {
				uprintf("st%d:  no tape loaded\n", unit);
				dsi->un_err_resid = 0;
				dsi->un_err_fileno = dsi->un_fileno;
				dsi->un_err_blkno = dsi->un_next_block;
				dsi->un_status = SC_NOT_READY;
				dsi->un_options = 0;
				dsi->un_ctype = ST_TYPE_INVALID;
				dsi->un_openf = CLOSED;
				dsi->un_flags = flags;	/* restore saved flags */
				return (EIO);
			}
		}
#endif	ST_SYSGEN
		/* Handle non-CCS tape drive types */
		printf("st%d:  unknown SCSI device found\n", unit);
		dsi->un_err_resid = 0;
		dsi->un_err_fileno = dsi->un_fileno;
		dsi->un_err_blkno = dsi->un_next_block;
		dsi->un_status = SC_NOT_READY;
		dsi->un_ctype = ST_TYPE_INVALID;
		dsi->un_openf = CLOSED;
		dsi->un_flags = flags;			/* restore saved flags */
		return (EIO);
	}
	/*
	 * Determine type of tape controller.  Type is determined by
	 * performing an inquiry command and checking vendor ids.
	 * The following vendor ids are supported:
	 *
	 *	ID  		Type
	 *	----		--------
	 *	8124 		Kennedy 9600 drive (reel)
	 *	HP   		HP 88780A drive (reel)
	 *	LMS  		CDC Patriot drive (HI/TC)
	 *	ARCHIVE		Archive QIC-120 drive
	 *	WANGTEK		Wangtek QIC-120 drive
	 *	EXABYTE		Exabyte 8mm tape drive
	 *	  ADAPT		Adaptec ACB-3530A controller
	 *	0x0000		Emulex MT-02 controller
	 *	0x3E00		Fujitsu Comet drive
	 *	--		Generic tape drive/controller
	 */
#ifdef	STDEBUG
	if (st_debug > 2)
		st_print_sid_buffer(sid, 32);
#endif	STDEBUG
	EPRINTF("stinit: checking inquiry data\n");
	if (bcmp(sid->vid, "\000\000", 2) == 0) {
		EPRINTF("stinit:  Emulex tape controller found\n\n");
		dsi->un_ctype = ST_TYPE_EMULEX;
		dsi->un_dev_bsize = ST_EMULEX_BSIZE;
		dsi->un_options = ST_EMULEX_OPTIONS;

	} else  if (bcmp(sid->vid, "HP", 2) == 0) {
		EPRINTF("stinit:  HP tape drive found\n\n");
		dsi->un_ctype = ST_TYPE_HP;
		dsi->un_dev_bsize = ST_HP_BSIZE;
		dsi->un_options = ST_HP_OPTIONS;

	} else  if (bcmp(sid->vid, "8124", 4) == 0) {
		EPRINTF("stinit:  Kennedy tape drive found\n\n");
		dsi->un_ctype = ST_TYPE_KENNEDY;
		dsi->un_dev_bsize = ST_KENNEDY_BSIZE;
		dsi->un_options = ST_KENNEDY_OPTIONS;

	} else  if (bcmp(sid->vid, "LMS", 3) == 0) {
		EPRINTF("stinit:  CDC tape drive found\n\n");
		dsi->un_ctype = ST_TYPE_CDC;
		dsi->un_dev_bsize = ST_CDC_BSIZE;
		dsi->un_options = ST_CDC_OPTIONS;

	} else  if (bcmp(sid->vid, "ARCHIVE", 7) == 0) {
		EPRINTF("stinit:  Archive tape drive found\n\n");
		dsi->un_ctype = ST_TYPE_ARCHIVE;
		dsi->un_dev_bsize = ST_ARCHIVE_BSIZE;
		dsi->un_options = ST_ARCHIVE_OPTIONS;

	} else  if (bcmp(sid->vid, "WANGTEK", 7) == 0) {
		EPRINTF("stinit:  Wangtek tape drive found\n\n");
		dsi->un_ctype = ST_TYPE_ARCHIVE;
		dsi->un_dev_bsize = ST_ARCHIVE_BSIZE;
		dsi->un_options = ST_ARCHIVE_OPTIONS;

	} else  if (bcmp(&sid->vid[2], "ADAPT", 5) == 0) {
		EPRINTF("stinit:  Adaptec tape controller found\n\n");
		dsi->un_ctype = ST_TYPE_ADAPTEC;
		dsi->un_dev_bsize = ST_ADAPTEC_BSIZE;
		dsi->un_options = ST_ADAPTEC_OPTIONS;

	} else  if (bcmp(sid->vid, "\076\000", 2) == 0) {
		EPRINTF("stinit:  Fujitsu Comet tape drive found\n\n");
		dsi->un_ctype = ST_TYPE_FUJI;
		dsi->un_dev_bsize = ST_FUJI_BSIZE;
		dsi->un_options = ST_FUJI_OPTIONS;

	} else  if (bcmp(sid->vid, "EXABYTE", 7) == 0) {
		EPRINTF("stinit:  Exabyte tape drive found\n\n");
		dsi->un_ctype = ST_TYPE_EXABYTE;
		dsi->un_dev_bsize = ST_EXABYTE_BSIZE;
		dsi->un_options = ST_EXABYTE_OPTIONS;

	} else {
		/*
		 * Don't know anything about this tape drive.
		 * Use at your own risk !!
		 */
		printf("st%d:  warning, unknown tape drive found\n\n", unit);
		dsi->un_ctype = ST_TYPE_DEFAULT;
		dsi->un_dev_bsize = ST_DEFAULT_BSIZE;
		dsi->un_options = ST_DEFAULT_OPTIONS;
	}
	/* Do mode sense to check for write protected tape */
	EPRINTF("stinit:  doing mode sense\n");
	dsi->un_openf = OPENING;
	(void) stcmd(dev, SC_MODE_SENSE, 0);

STINIT_EXIT:
	/* Check if disconnects disabled */
	if (dsi->un_options & ST_NODISCON) {
		EPRINTF("stinit:  disconnects disabled\n");
		flags = SC_UNF_NO_DISCON;
	} else {
		EPRINTF("stinit:  disconnects enabled\n");
		flags = 0;
	}

	/*
	 * If we haven't got a DVMA buffer by now
	 * we're in serious trouble!
	 */
	if (sid == NULL) {
		printf("st%d:  no iopb memory for mode sense\n", unit);
		dsi->un_err_resid = 0;
		dsi->un_err_fileno = dsi->un_fileno;
		dsi->un_err_blkno = dsi->un_next_block;
		dsi->un_status = SC_NOT_READY;
		dsi->un_openf = CLOSED;
		dsi->un_ctype = ST_TYPE_INVALID;
		dsi->un_flags = flags;			/* restore saved flags */
		return (EIO);
	}

	/*
	 * Tape is ready to go.  Set mode to OPEN to signify the
	 * fact.  Return successful status to stopen.
	 */
	dsi->un_openf = OPEN;
	dsi->un_flags = flags;			/* restore saved flags */
	return (0);
}

stopen(dev, flag)
	register dev_t dev;
	int flag;
{
	register struct scsi_unit *un;
	register u_int unit;
	register int s;
	register int status;
	register struct scsi_tape *dsi;

	unit = STUNIT(dev);
	if (unit > nstape) {
		EPRINTF2("st%d:  stopen: invalid unit %d\n", unit, unit);
		return (ENXIO);
	}
	un = &stunits[unit];
	dsi = &stape[unit];
	/* DPRINTF("stopen:\n"); */
	/* DPRINTF2("      un= 0x%x, un->un_c= 0x%x\n", un, un->un_c); */

	if (un->un_mc == 0  ||  un->un_c == 0) {
		EPRINTF2("st%d:  stopen: never attached unit %d\n", unit, unit);
		return (ENXIO);
	}

	/*
	 * Can't open a drive that's already open.  If closing
	 * or closed, go ahead with open.  If open, return busy
	 * Note, raise interrupt priority high enough to prevent
	 * I/O requestor from being swapped while we're checking.
	 */
	/* s = spl6(); */
	s = splx(pritospl(un->un_mc->mc_intpri));
	if (dsi->un_openf > CLOSING) {
		(void) splx(s);
		EPRINTF1("stopen:  open state= %d\n", dsi->un_openf);
		return (EBUSY);
	}
	dsi->un_openf = OPENING;
	(void) splx(s);

	/*
	 * Open tape drive. Also, make sure it's online.
	 * Note, this will also set stintr state machine to open
	 * state.
	 */
	if ((status=stinit(dev)) != 0) {
		return (status);
	}
	/* dsi->un_openf = OPEN; */

	/*
	 * While we're opening the tape, check for
	 * write protect.  If it is and we're opening
	 * the tape for write operations, you're dead.
	 * Note, this error will also force the tape drive
	 * to be reinitialized via stinit.  Also, log stats
	 * for 'mt status'.
	 */
	if ((flag & FWRITE)  &&  dsi->un_read_only) {
		uprintf("st%d:  tape is write protected\n", unit);
		dsi->un_err_resid = 0;
		dsi->un_err_fileno = dsi->un_fileno;
		dsi->un_err_blkno = dsi->un_next_block;
		dsi->un_status = SC_WRITE_PROTECT;
		dsi->un_ctype = ST_TYPE_INVALID;
		dsi->un_openf = CLOSED;
		return (EIO);
	}

	/*
	 * If a device reset occurred, the mode select information
	 * should be given to the tape device again just to be safe.
	 */
	if (dsi->un_reset_occurred) {
		EPRINTF("stopen:  resetting tape device\n");
		dsi->un_reset_occurred = 0;
		dsi->un_readmode = 0;
		dsi->un_eof = ST_NO_EOF;
		dsi->un_density = 0;		/* force mode select */
		dsi->un_fileno = 0;		/* suppress rewinding msg */
		dsi->un_next_block = 0;
	}

#ifdef	sun2
	/*
	 * If this system is a Sun-2/120 with a Cipher tape drive,
	 * there is no QIC-24 format support.  If QIC-24 format
	 * selection is attempted, the tape will be erased.
	 */
	if (dsi->un_cipher) {
		if (minor(dev) & DENSITY_6250) {
			uprintf("st%d:  warning, only QIC-11 format available\n",
				unit);
		}
		dsi->un_density = SC_DEN1600;
		goto STOPEN_EXIT;
	}
#endif	sun2

	/* Check for need to convert to hi-density (e.g. 6250 bpi or QIC-24) */
	if (minor(dev) & DENSITY_6250) {
		if (dsi->un_density != SC_DEN6250) {
			if (dsi->un_fileno != 0  ||  dsi->un_next_block != 0)
				uprintf("st%d:  warning, rewinding tape\n", unit);
			(void) stcmd(dev, SC_REWIND, 0);
			if (stcmd(dev, SC_DEN6250, 0) == 0) {
				printf("st%d:  format change failed\n", unit);
				dsi->un_ctype = ST_TYPE_INVALID;
				dsi->un_openf = CLOSED;
				return (EIO);
			}
			dsi->un_density = SC_DEN6250;
		}

	/* Check for need to convert to low-density (e.g. 1600 bpi or QIC-11) */
	} else if (dsi->un_density != SC_DEN1600) {
		if (dsi->un_fileno != 0  ||  dsi->un_next_block != 0)
			uprintf("st%d:  warning, rewinding tape\n", unit);
		(void) stcmd(dev, SC_REWIND, 0);
		if (stcmd(dev, SC_DEN1600, 0) == 0) {
			printf("st%d:  format change failed\n", unit);
			dsi->un_status = SC_NOT_READY;
			dsi->un_ctype = ST_TYPE_INVALID;
			dsi->un_openf = CLOSED;
			return (EIO);
		}
		dsi->un_density = SC_DEN1600;
	}

	/*
	 * If closed after hitting eof, on open allow reading of next file.
	 */
STOPEN_EXIT:
	if (dsi->un_eof  == ST_EOF) {
		dsi->un_eof = ST_NO_EOF;
	}
	return (0);
}

/*ARGSUSED*/
stclose(dev, flag)
	register dev_t dev;
	register int flag;
{
	register struct scsi_unit *un;
	register struct scsi_tape *dsi;
	un = &stunits[STUNIT(dev)];
	dsi = &stape[STUNIT(dev)];

#ifdef	lint
	flag = flag;
#endif	lint

	/*
	 * If we exit here, something majorly wrong ha
	 * occurred in SCSI land.
	 */
	if (dsi->un_openf == CLOSED) {
		return;
	}

	/*
	 * If the last I/O to the tape drive is complete,  write a
	 * filemark before closing.  Note, for 1/2-inch reel tape
	 * two filemarks will be written for Pertec compatibility.
	 */
	if (dsi->un_lastiow) {
		dsi->un_lastiow = 0;
		if (dsi->un_options & ST_REEL) {
			if (stcmd(dev, SC_WRITE_FILE_MARK, 0) == 0) {
				printf("st%d:  file mark write failed\n",
					un - stunits);
			}
		}
		if (stcmd(dev, SC_WRITE_FILE_MARK, 0) == 0) {
			printf("st%d:  file mark write failed\n",
				un - stunits);
		}
	}

	/*
	 * If rewind on close, set closing driver state and allow
	 * stintr to close the driver down.  Otherwise, now
	 * close the driver down.
	 */
	if ((minor(dev) & T_NOREWIND) == 0) {
		DPRINTF("stclose:  rewinding...\n");
		dsi->un_openf = CLOSING;
		(void) stcmd(dev, SC_REWIND, -1);
	} else {
		dsi->un_openf = CLOSED;
	}

	EPRINTF2("stclose:  retries= %d,   underruns= %d",
		 dsi->un_retry_ct, dsi->un_underruns);
	EPRINTF2(",    file= %d,   block= %d\n",
		 dsi->un_fileno, dsi->un_next_block);
}


stcmd(dev, cmd, count)
	dev_t dev;
	u_int cmd;
	int count;
{
	register struct buf *bp;
	register int s;
	register int error;
	register struct scsi_unit *un;
	register struct scsi_tape *dsi;
	register u_int unit;

	unit = STUNIT(dev);
	un = &stunits[unit];
	dsi = &stape[unit];
	bp = &un->un_sbuf;
#ifdef	lint
	dsi = dsi;
#endif	lint

	s = splx(pritospl(un->un_mc->mc_intpri));
	while (bp->b_flags & B_BUSY) {
		/*
		 * Special test because B_BUSY never gets cleared in
		 * the non-waiting rewind case.
		 */
		if ((bp->b_bcount == -1)  &&  (bp->b_flags & B_DONE)) {
			break;
		}
		bp->b_flags |= B_WANTED;
		/* DPRINTF1("stcmd:  sleeping...,  bp= 0x%x\n", bp); */
		timeout(sttimer, (caddr_t)dev, 60*hz);
		(void) sleep((caddr_t) bp, PRIBIO);
	}

	untimeout(sttimer, (caddr_t)dev);
	/* DPRINTF1("stcmd:  waking...,  bp= 0x%x\n", bp); */
	bp->b_flags = B_BUSY | B_READ | B_WANTED;
	(void) splx(s);

	bp->b_dev = dev;
	bp->b_bcount = count;
	un->un_scmd = cmd;
	ststrategy(bp);

	/*
	 * In case of rewind on close, don't wait.
	 */
	if (cmd == SC_REWIND  &&  count == -1) {
		return (1);
	}
	s = splx(pritospl(un->un_mc->mc_intpri));
	while ((bp->b_flags & B_DONE) == 0) {
		/* DPRINTF1("stcmd:  still sleeping..., bp= 0x%x\n", bp); */
		timeout(sttimer, (caddr_t)dev, 60*hz);
		(void) sleep((caddr_t) bp, PRIBIO);
	}
	untimeout(sttimer, (caddr_t)dev);
	(void) splx(s);

	/* DPRINTF1("stcmd:  waking...,  bp= 0x%x\n", bp); */
	error = geterror(bp);
	if (bp->b_flags & B_WANTED) {
		wakeup((caddr_t) bp);
	}
	bp->b_flags &= B_ERROR;			/* Clears B_BUSY */
	return (error == 0);
}

ststrategy(bp)
	register struct buf *bp;
{
	register struct scsi_unit *un;
	register u_int unit;
	register int s;
	register struct buf *ap;
	register struct scsi_tape *dsi;
	unit = STUNIT(bp->b_dev);

#ifdef	STDEBUG
	if (unit > nstape) {
		printf("st%d:  ststrategy: invalid unit %d\n", unit, unit);
		bp->b_flags |= B_ERROR;
		iodone(bp);
		return;
	}
#endif	STDEBUG

	un = &stunits[unit];
	dsi = &stape[unit];
	/* DPRINTF1("ststrategy:  bp= 0x%x\n", bp); */
	/* DPRINTF2("             un= 0x%x, un->un_c= 0x%x\n", un, un->un_c); */

	if (dsi->un_openf != OPEN  &&  bp != &un->un_sbuf) {
		EPRINTF("ststrategy:  device not open\n");
		bp->b_flags |= B_ERROR;
		iodone(bp);
		return;
	}
	s = splx(pritospl(un->un_mc->mc_intpri));
	while (dsi->un_bufcnt >= MAXSTBUF) {
		DPRINTF1("ststrategy:  too busy, sleeping on bp= 0x%x\n", bp);
		(void) sleep((caddr_t) &dsi->un_bufcnt, PRIBIO);
	}
	dsi->un_bufcnt++;

	/*
	 * Put the block at the end of the queue.
	 * Should probably have a pointer to the end of
	 * the queue, but the queue can't get too long,
	 * so the added code complexity probably isn't
	 * worth it.
	 */
	/* DPRINTF1("ststrategy:  queing bp= 0x%x\n", bp); */
	ap = &un->un_utab;
	while (ap->b_actf != NULL) {
		ap = ap->b_actf;
	}
	ap->b_actf = bp;
	bp->b_actf = NULL;

	/* If tape drive is idle, start it up. */
	if (un->un_utab.b_active == 0) {
		(*un->un_c->c_ss->scs_ustart)(un);
		bp = &un->un_mc->mc_tab;
		if (bp->b_actf  &&  bp->b_active == 0) {
			/* Controller start */
			(*un->un_c->c_ss->scs_start)(un);
		}
	}
	(void) splx(s);
}

/*
 * Start the operation.
 */
/*ARGSUSED*/
ststart(bp, un)
	register struct buf *bp;
	register struct scsi_unit *un;
{
	register struct scsi_tape *dsi;

	dsi = &stape[STUNIT(bp->b_dev)];
	/* DPRINTF("ststart:\n"); */
	/* DPRINTF2("       un= 0x%x, un->un_c= 0x%x\n", un, un->un_c); */

	/*
	 * Process raw I/O tape commands.
	 */
	if (bp == &un->un_rbuf) {
		/* DPRINTF("ststart:  raw I/O\n"); */
		/* Check for read operation */
		if (bp->b_flags & B_READ) {
			/*
			 * Can't read past EOF.  Note, if at EOF,
			 * we'll return 0 bytes.
			 */
			if (dsi->un_eof != ST_NO_EOF) {
				EPRINTF("ststart:  can't read past eof\n");
#ifdef	ST_SYSGEN
				if (dsi->un_eof == ST_EOF_PENDING) {
					DPRINTF("ststart:  logging eof stats\n");
					dsi->un_eof = ST_EOF;
					dsi->un_next_block = 0;
					dsi->un_last_block = INF;
					dsi->un_fileno++;
					dsi->un_lastior = 0;

				}
#endif	ST_SYSGEN
				dsi->un_status = SC_EOF;
				dsi->un_err_blkno = dsi->un_next_block;
				dsi->un_err_fileno = dsi->un_fileno;
				dsi->un_err_resid = bp->b_resid = bp->b_bcount;
				iodone(bp);
				if (dsi->un_bufcnt-- >= MAXSTBUF) {
					wakeup((caddr_t) &dsi->un_bufcnt);
				}
				return (0);
			}
			un->un_cmd = SC_READ;
		} else {
			if (dsi->un_eof != ST_NO_EOF) {
				EPRINTF("ststart:  can't write past eot\n");
				dsi->un_status = SC_EOT;
				dsi->un_err_fileno = dsi->un_fileno;
				dsi->un_err_blkno = dsi->un_next_block;
				dsi->un_err_resid = bp->b_resid = bp->b_bcount;
				iodone(bp);
				if (dsi->un_bufcnt-- >= MAXSTBUF) {
					wakeup((caddr_t) &dsi->un_bufcnt);
				}
				return (0);
			}
			un->un_cmd = SC_WRITE;
		}
		un->un_count = bp->b_bcount;
		un->un_flags = SC_UNF_DVMA;
		bp->b_resid = 0;
		return (1);



	/*
	 * Process internal I/O tape commands using our internal buffer.
	 */
	} else if (bp == &un->un_sbuf) {
		/* DPRINTF("ststart:  internal I/O\n"); */
		un->un_cmd = un->un_scmd;
		un->un_count = bp->b_bcount;
		un->un_flags = 0;
		bp->b_resid = 0;
		return (1);



	/*
	 * Process block I/O tape commands.
	 */
	} else {
		DPRINTF("ststart:  block mode I/O\n");
		if (bp->b_flags & B_READ) {
			/*
			 * Can't read past EOF.  Note, if at EOF,
			 * we'll return 0 bytes.
			 */
			if (dsi->un_eof != ST_NO_EOF) {
				EPRINTF("ststart:  can't read past eof\n");
#ifdef	ST_SYSGEN
				if (dsi->un_eof == ST_EOF_PENDING) {
					DPRINTF("ststart:  logging eof stats\n");
					dsi->un_eof = ST_EOF;
					dsi->un_fileno++;
					dsi->un_next_block = 0;
					dsi->un_last_block = INF;
					dsi->un_lastior = 0;
				}
#endif	ST_SYSGEN
				dsi->un_status = SC_EOF;
				dsi->un_err_fileno = dsi->un_fileno;
				dsi->un_err_blkno = dsi->un_next_block;
				dsi->un_err_resid = bp->b_resid = bp->b_bcount;
				iodone(bp);
				if (dsi->un_bufcnt-- >= MAXSTBUF) {
					wakeup((caddr_t) &dsi->un_bufcnt);
				}
				return (0);
			}
			un->un_cmd = SC_READ;

		/* Must be block mode write operation */
		} else {
			if (dsi->un_eof != ST_NO_EOF) {
				EPRINTF("ststart:  can't write past eot\n");
				dsi->un_status = SC_EOT;
				dsi->un_err_fileno = dsi->un_fileno;
				dsi->un_err_blkno = dsi->un_next_block;
				dsi->un_err_resid = bp->b_resid = bp->b_bcount;
				iodone(bp);
				if (dsi->un_bufcnt-- >= MAXSTBUF) {
					wakeup((caddr_t) &dsi->un_bufcnt);
				}
				return (0);
			}
			un->un_cmd = SC_WRITE;
		}
		un->un_count = bp->b_bcount;
		un->un_flags = SC_UNF_DVMA;
		bp->b_resid = 0;
		return (1);
	}
}

/*
 * Make a command description block.
 */
stmkcdb(c, un)
	register struct scsi_ctlr *c;
	register struct scsi_unit *un;
{
	register struct scsi_cdb6 *cdb;
	register struct scsi_tape *dsi;
	register struct st_sense *ssd;
	register struct st_ms_mspl *em;
	u_int count, density, speed, blk_size;

	dsi = &stape[un->un_unit];
	cdb = (struct scsi_cdb6 *)&c->c_cdb;
	bzero((caddr_t)cdb, sizeof (struct scsi_cdb6));
	cdb->cmd = un->un_cmd;
	cdb->lun = un->un_lun;
#ifdef	lint
	(int)ssd = 0;
	(int)c = (int)ssd;
#endif	lint

	switch (un->un_cmd) {
	case SC_READ:
		/* DPRINTF("stmkcdb:  read command\n"); */
#ifdef	MACH
		un->un_flags |= (SC_UNF_RECV_DATA | SC_UNF_NO_DISCON | dsi->un_flags);
#else	MACH
		un->un_flags |= (SC_UNF_RECV_DATA | dsi->un_flags);
#endif	MACH
		un->un_dma_addr = un->un_baddr;
		dsi->un_timeout = 2;
		if (dsi->un_options & ST_VARIABLE) {
			/* cdb->t_code = 0; */
			count = un->un_dma_count = un->un_count;
			cdb->mid_count = (un->un_count >> 8) & 0xff;
			cdb->low_count = count & 0xff;
		} else {
			cdb->t_code = 1;
			if (un->un_count != un->un_last_count) {
				count = un->un_count / dsi->un_dev_bsize;
			} else {
				count = un->un_last_bcount;
			}
			un->un_last_count = un->un_dma_count = un->un_count;
			un->un_last_bcount = count;
			cdb->mid_count = (count >> 8) & 0xff;
			cdb->low_count = count & 0xff;
		}
		break;


	case SC_WRITE:
		/* DPRINTF("stmkcdb:  write command\n"); */
#ifdef	MACH
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				SC_UNF_NO_DISCON | dsi->un_flags;
#else	MACH
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				dsi->un_flags;
#endif	MACH
		un->un_dma_addr = un->un_baddr;
		dsi->un_timeout = 2;
		if (dsi->un_options & ST_VARIABLE) {
			/* cdb->t_code = 0; */
			count = un->un_dma_count = un->un_count;
			cdb->mid_count = (un->un_count >> 8) & 0xff;
			cdb->low_count = count & 0xff;
		} else {
			cdb->t_code = 1;
			if (un->un_count != un->un_last_count) {
				count = un->un_count / dsi->un_dev_bsize;
			} else {
				count = un->un_last_bcount;
			}
			un->un_last_count = un->un_dma_count = un->un_count;
			un->un_last_bcount = count;
			cdb->mid_count = (count >> 8) & 0xff;
			cdb->low_count = count & 0xff;
		}
		break;


	case SC_WRITE_FILE_MARK:
	case SC_LOAD:
		DPRINTF("stmkcdb:  write file mark command\n");
		cdb->low_count = 1;
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				dsi->un_flags;
		un->un_dma_addr = un->un_dma_count = 0;
		dsi->un_timeout = 1;
		break;


	case SC_BSPACE_FILE:
		/* DPRINTF("stmkcdb:  backspace command\n"); */
		un->un_count = - un->un_count;
		/* Fall through to sc_space_file... */

	case SC_SPACE_FILE:
		DPRINTF("stmkcdb:  space file command\n");
		cdb->t_code = 1;	/* Space files, not records */
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				dsi->un_flags;
		cdb->cmd = SC_SPACE_REC;
		cdb->mid_count = (un->un_count >> 8) & 0xff;
		cdb->low_count = un->un_count & 0xff;
		un->un_dma_addr = un->un_dma_count = 0;
		dsi->un_timeout = 30;
		break;


	case SC_SPACE_REC:
		DPRINTF("stmkcdb:  space command\n");
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				dsi->un_flags;
		cdb->cmd = SC_SPACE_REC;
		cdb->mid_count = (un->un_count >> 8) & 0xff;
		cdb->low_count = un->un_count & 0xff;
		un->un_dma_addr = un->un_dma_count = 0;
		dsi->un_timeout = 2;
		break;

	case SC_REQUEST_SENSE:
		EPRINTF("stmkcdb:  request sense command\n");
		dsi->un_timeout = 1;
#ifdef	MACH
		un->un_flags |= (SC_UNF_RECV_DATA | SC_UNF_NO_DISCON | dsi->un_flags);
#else	MACH
		un->un_flags |= (SC_UNF_RECV_DATA | dsi->un_flags);
#endif	MACH
		un->un_dma_addr = (int)dsi->un_mspl - (int)DVMA;
		un->un_dma_count = cdb->low_count =
				sizeof (struct st_sense);
		bzero((caddr_t)(dsi->un_mspl), sizeof (struct st_sense));
#ifdef	ST_SYSGEN
		if (IS_SYSGEN(dsi)  ||  dsi->un_openf == OPENING) {
			un->un_dma_count = cdb->low_count =
				sizeof (struct sysgen_sense);
		}
#endif	ST_SYSGEN
		return;
		/* break; */

	case SC_READ_APPEND:
		/* Special read command for write append. */
		DPRINTF("stmkcdb:  read append command\n");
		cdb->cmd = SC_READ;
#ifdef	MACH
		un->un_flags |= (SC_UNF_RECV_DATA | SC_UNF_NO_DISCON | dsi->un_flags);
#else	MACH
		un->un_flags |= (SC_UNF_RECV_DATA | dsi->un_flags);
#endif	MACH
		un->un_dma_addr = (int)un->un_sbuf.b_un.b_addr - (int)DVMA;
		un->un_dma_count = dsi->un_dev_bsize;
		dsi->un_timeout = 1;
		if (dsi->un_options & ST_VARIABLE) {
			/* cdb->t_code = 0; */
			cdb->mid_count = (dsi->un_dev_bsize >> 8) & 0xff;
			cdb->low_count = dsi->un_dev_bsize & 0xff;
		} else {
			cdb->t_code = 1;
			cdb->mid_count = 0;
			cdb->low_count = 1;
		}
		return;
		/* break; */

	/* case SC_RETENSION: */
	case SC_REWIND:
		DPRINTF("stmkcdb:  rewind command\n");
		if (dsi->un_reten_rewind  &&  (dsi->un_options & ST_QIC)) {

			/* If QIC tape, allow retensioning */
			cdb->cmd = un->un_cmd = SC_LOAD;
			cdb->low_count = 3;
#ifdef	ST_SYSGEN
			if (IS_SYSGEN(dsi)) {
				cdb->cmd = un->un_cmd = SC_REWIND;
				cdb->low_count = 0;
				cdb->vu_57 = 1;
			}
#endif	ST_SYSGEN
		}
		dsi->un_reten_rewind = 0;
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				dsi->un_flags;
		un->un_dma_addr = un->un_dma_count = 0;
		dsi->un_timeout = 6;
		break;

	case SC_UNLOAD:
		DPRINTF("stmkcdb:  unload command\n");
		cdb->cmd = un->un_cmd = SC_LOAD;
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				dsi->un_flags;
		un->un_dma_addr = un->un_dma_count = 0;
		dsi->un_timeout = 5;
		break;


	case SC_TEST_UNIT_READY:
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				dsi->un_flags;
		un->un_dma_addr = un->un_dma_count = 0;
		dsi->un_timeout = 1;
		break;

	case SC_INQUIRY:
		DPRINTF("stmkcdb:  inquiry\n");
#ifdef	MACH
		un->un_flags |= (SC_UNF_RECV_DATA | SC_UNF_NO_DISCON | dsi->un_flags);
#else	MACH
		un->un_flags |= (SC_UNF_RECV_DATA | dsi->un_flags);
#endif	MACH
		un->un_dma_addr = (int)dsi->un_mspl - (int)DVMA;
		un->un_dma_count = cdb->low_count =
				sizeof (struct scsi_inquiry_data);
		dsi->un_timeout = 1;
		break;

	case SC_ERASE_TAPE:
		DPRINTF("stmkcdb:  erase tape\n");
		cdb->t_code = 1;
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				dsi->un_flags;
		un->un_dma_addr = un->un_dma_count = 0;
		dsi->un_timeout = 8;
		if (IS_CDC(dsi)  ||  IS_DEFAULT(dsi)  ||  IS_FUJI(dsi)) {
			dsi->un_timeout = 20;
		}
		break;

	case SC_MODE_SENSE:
		EPRINTF("stmkcdb:  mode sense\n");
		dsi->un_timeout = 1;
#ifdef	MACH
		un->un_flags |= (SC_UNF_RECV_DATA | SC_UNF_NO_DISCON | dsi->un_flags);
#else	MACH
		un->un_flags |= (SC_UNF_RECV_DATA | dsi->un_flags);
#endif	MACH
		em = (struct st_ms_mspl *)dsi->un_mspl;
		if (em == NULL) {
			EPRINTF("stmkcdb:  no DVMA buffer\n");
			break;
		}
		bzero((caddr_t)em, sizeof (struct st_ms_mspl));
		un->un_dma_addr = (int)dsi->un_mspl - (int)DVMA;
		un->un_dma_count = cdb->low_count =
				sizeof (struct st_ms_mspl);
		break;

	case SC_DEN1600:
		switch (dsi->un_ctype) {
		case ST_TYPE_EMULEX:
			EPRINTF2("st%d:  %s format selected\n",
					un-stunits, "QIC-11");
			density = ST_EMULEX_DEN1600;
			speed = ST_EMULEX_SPEED;
			blk_size = ST_EMULEX_BSIZE;
			break;
		case ST_TYPE_HP:
			EPRINTF2("st%d:  %s format selected\n",
					un-stunits, "1600 BPI");
			density = ST_HP_DEN1600;
			speed = ST_HP_SPEED;
			blk_size = ST_HP_BSIZE;
			break;
		case ST_TYPE_KENNEDY:
			EPRINTF2("st%d:  %s format selected\n",
					un-stunits, "1600 BPI");
			density = ST_KENNEDY_DEN1600;
			speed = ST_KENNEDY_SPEED;
			blk_size = ST_KENNEDY_BSIZE;
			break;
		case ST_TYPE_CDC:
			EPRINTF2("st%d:  %s format selected\n",
					un-stunits, "Low Density");
			density = ST_CDC_DEN1600;
			speed = ST_CDC_SPEED;
			blk_size = ST_CDC_BSIZE;
			break;
		case ST_TYPE_ARCHIVE:
			EPRINTF2("st%d:  %s format selected\n",
					un-stunits, "QIC-120");
			density = ST_ARCHIVE_DEN1600;
			speed = ST_ARCHIVE_SPEED;
			blk_size = ST_ARCHIVE_BSIZE;
			break;
		case ST_TYPE_SYSGEN:
			EPRINTF2("st%d:  %s format selected\n",
					un-stunits, "QIC-11");
			density = ST_SYSGEN_DEN1600;
			speed = ST_SYSGEN_SPEED;
			blk_size = ST_SYSGEN_BSIZE;
			break;
		case ST_TYPE_ADAPTEC:
			EPRINTF2("st%d:  %s format selected\n",
					un-stunits, "QIC-11");
			density = ST_ADAPTEC_DEN1600;
			speed = ST_ADAPTEC_SPEED;
			blk_size = ST_ADAPTEC_BSIZE;
			break;
		case ST_TYPE_FUJI:
			EPRINTF2("st%d:  %s format selected\n",
					un-stunits,"Low Density");
			density = ST_FUJI_DEN1600;
			speed = ST_FUJI_SPEED;
			blk_size = ST_FUJI_BSIZE;
			break;
		case ST_TYPE_EXABYTE:
			EPRINTF2("st%d:  %s format selected\n",
					un-stunits, "Default");
			density = ST_EXABYTE_DEN1600;
			speed = ST_EXABYTE_SPEED;
			blk_size = ST_EXABYTE_BSIZE;
			break;
		case ST_TYPE_DEFAULT:
			EPRINTF2("st%d:  %s format selected\n",
					un-stunits, "Default");
			density = ST_DEFAULT_DEN1600;
			speed = ST_DEFAULT_SPEED;
			blk_size = dsi->un_dev_bsize;
			if (dsi->un_dev_bsize == 0) {
				dsi->un_dev_bsize = blk_size = ST_DEFAULT_BSIZE;
				EPRINTF1("stmkcdb:  using block size= %d\n",
					 blk_size);
			}
			break;
		}
		goto MODE;			 /* goto SC_MODE_SELECT... */
		/* break; */

	case SC_DEN6250:
		switch (dsi->un_ctype) {
		case ST_TYPE_EMULEX:
			EPRINTF2("st%d:  %s format selected\n",
					un-stunits, "QIC-24");
			density = ST_EMULEX_DEN6250;
			speed = ST_EMULEX_SPEED;
			blk_size = ST_EMULEX_BSIZE;
			break;
		case ST_TYPE_HP:
			EPRINTF2("st%d:  %s format selected\n",
					un-stunits, "6250 BPI");
			density = ST_HP_DEN6250;
			speed = ST_HP_SPEED;
			blk_size = ST_HP_BSIZE;
			break;
		case ST_TYPE_KENNEDY:
			EPRINTF2("st%d:  %s format selected\n",
					un-stunits, "6250 BPI");
			density = ST_KENNEDY_DEN6250;
			speed = ST_KENNEDY_SPEED;
			blk_size = ST_KENNEDY_BSIZE;
			break;
		case ST_TYPE_CDC:
			EPRINTF2("st%d:  %s format selected\n",
				 un-stunits, "Low Density");
			density = ST_CDC_DEN6250;
			speed = ST_CDC_SPEED;
			blk_size = ST_CDC_BSIZE;
			break;
		case ST_TYPE_ARCHIVE:
			EPRINTF2("st%d:  %s format selected\n",
					un-stunits, "QIC-120");
			density = ST_ARCHIVE_DEN6250;
			speed = ST_ARCHIVE_SPEED;
			blk_size = ST_ARCHIVE_BSIZE;
			break;
		case ST_TYPE_SYSGEN:
			EPRINTF2("st%d:  %s format selected\n",
					un-stunits, "QIC-24");
			density = ST_SYSGEN_DEN6250;
			speed = ST_SYSGEN_SPEED;
			blk_size = ST_SYSGEN_BSIZE;
			break;
		case ST_TYPE_ADAPTEC:
			EPRINTF2("st%d:  %s format selected\n",
					un-stunits, "QIC-24");
			density = ST_ADAPTEC_DEN6250;
			speed = ST_ADAPTEC_SPEED;
			blk_size = ST_ADAPTEC_BSIZE;
			break;
		case ST_TYPE_FUJI:
			EPRINTF2("st%d:  %s format selected\n",
					 un-stunits,"Low Density");
			density = ST_FUJI_DEN6250;
			speed = ST_FUJI_SPEED;
			blk_size = ST_FUJI_BSIZE;
			break;
		case ST_TYPE_EXABYTE:
			EPRINTF2("st%d:  %s format selected\n",
					un-stunits, "Default");
			density = ST_EXABYTE_DEN6250;
			speed = ST_EXABYTE_SPEED;
			blk_size = ST_EXABYTE_BSIZE;
			break;
		case ST_TYPE_DEFAULT:
			EPRINTF2("st%d:  %s format selected\n",
					un-stunits, "Default");
			density = ST_DEFAULT_DEN6250;
			speed = ST_DEFAULT_SPEED;
			blk_size = dsi->un_dev_bsize;
			if (dsi->un_dev_bsize == 0) {
				dsi->un_dev_bsize = blk_size = ST_DEFAULT_BSIZE;
				EPRINTF1("stmkcdb:  using block size= %d\n",
					 blk_size);
			}
			break;
		}
		/* Fall through into SC_MODE_SELECT... */


	case SC_MODE_SELECT:
MODE:
		dsi->un_timeout = 1;
		un->un_cmd = cdb->cmd = SC_MODE_SELECT;
		em = (struct st_ms_mspl *)dsi->un_mspl;
		if (em == NULL) {
			EPRINTF("stmkcdb:  no DVMA buffer\n");
			break;
		}
		bzero((caddr_t)em, sizeof (struct scsi_inquiry_data));
#ifdef	MACH
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				SC_UNF_NO_DISCON | dsi->un_flags;
#else	MACH
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				dsi->un_flags;
#endif	MACH
		un->un_dma_addr = (int)dsi->un_mspl - (int)DVMA;
		un->un_dma_count = cdb->low_count =
				sizeof (struct st_ms_mspl);
		em->bufm = 1;
		em->bd_len = MS_BD_LEN;
		em->density = density;
		em->speed  =  speed;
		if (dsi->un_options & ST_VARIABLE) {
			EPRINTF("stmkcdb:  Variable length I/O selected\n");
		} else {
			EPRINTF("stmkcdb:  Fixed length I/O selected\n");
			em->mid_bl =  (blk_size >> 8) & 0xff;
			em->low_bl =  blk_size & 0xff;
#ifdef	ST_SYSGEN
			if (IS_SYSGEN(dsi)) {
				un->un_flags = dsi->un_flags |
					(un->un_flags & ~SC_UNF_RECV_DATA);
				cdb->cmd = SC_QIC02;
				cdb->high_count = density;
				un->un_dma_count = 0;
			}
#endif	ST_SYSGEN
		}
		break;

#ifdef	sun2
	case SC_READ_XSTATUS_CIPHER:
		DPRINTF("stmkcdb:  read cipher status\n");
		dsi->un_timeout = 1;
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				dsi->un_flags;
		cdb->cmd = un->un_cmd = SC_QIC02;
		cdb->high_count = SC_READ_XSTATUS_CIPHER;
		un->un_dma_addr = un->un_dma_count = 0;
		break;
#endif	sun2

	default:
		dsi->un_timeout = 1;
		un->un_flags = (un->un_flags & ~SC_UNF_RECV_DATA) |
				dsi->un_flags;
		printf("st%d:  stmkcdb: invalid command %x\n", un - stunits,
			un->un_cmd);
		break;

	}
	/* Save last command for stintr error recovery */
	dsi->un_last_cmd = un->un_cmd;
}


typedef enum stintr_error_resolution {
	real_error, 		/* We found a genuine error */
	psuedo_error, 		/* What looked like an error is actually OK */
	more_processing 	/* We need to run another command */
} stintr_error_resolution;

#ifdef	__GNU__
static int stintr_silent_failure();
static int stintr_opening();
static int stintr_sense();
static int stintr_ran_sense();
static int stintr_sysgen();
static int st_print_cmd();
static int st_error_message();
static stintr_error_resolution stintr_handle_error(),
	stintr_ran_append(), stintr_append_error(),
	stintr_file_mark_detected(), stintr_end_of_tape();
#else	__GNU__
stintr_error_resolution stintr_handle_error(),
	stintr_ran_append(), stintr_append_error(),
	stintr_file_mark_detected(), stintr_end_of_tape();
#endif	__GNU__

stintr(c, resid, error)
	register struct scsi_ctlr *c;
	register u_int error;
	u_int resid;
{
	register struct scsi_unit *un;
	register struct buf *bp;
	register struct scsi_tape *dsi;
	register struct st_sense *ssd;
	register u_char status;

	un = c->c_un;
	bp = un->un_mc->mc_tab.b_actf->b_actf;
	dsi = &stape[STUNIT(bp->b_dev)];
	status = 0;
	/* DPRINTF2("stintr:  c= 0x%x, un= 0x%x, ", c, un); */
	/* DPRINTF1("bp= 0x%x\n", bp); */

#ifdef	STDEBUG
	if (st_debug > 2)
		st_print_cmd_status(c, dsi);
#endif	STDEBUG

	/*
	 * Since si now sets error to a nonzero value if the scb
	 * status bits are non-zero, the following checks aren't
	 * needed:
	 *	c->c_scb.chk  ||  c->c_scb.busy
	 */
#ifdef	REL4
	if (c->c_scb.chk  ||  c->c_scb.busy)
		error = 1;
#endif	REL4
	if (error  ||  (dsi->un_openf < OPEN)  ||  resid)  {

		/*
		 * Special processing for driver command timeout errors.
		 * Also, log location tape died at.
		 */
		if (error == SE_TIMEOUT) {
			EPRINTF("stintr:  command timeout error\n");
			if (dsi->un_openf == CLOSING) {
				DPRINTF("stintr:  closing tape device\n");
				dsi->un_openf = CLOSED;
			}
			dsi->un_status = SC_TIMEOUT;
			dsi->un_err_resid = resid;
			dsi->un_err_fileno = dsi->un_fileno;
			dsi->un_err_blkno = dsi->un_next_block;
			dsi->un_reset_occurred = 1;
			bp->b_flags |= B_ERROR;
			goto STINTR_WRAPUP;
		}
		/*
		 * Special processing for scsi bus failures.
		 * Note, this error is implies a SCSI bus
		 * handshake failure.  SCSI may now be dead
		 * too.
		 */
		if (error == SE_FATAL) {
			EPRINTF("stintr:  scsi bus failure\n");
			dsi->un_openf = CLOSED;
			dsi->un_status = SC_FATAL;
			dsi->un_reset_occurred = 1;
			dsi->un_err_resid = resid;
			dsi->un_err_fileno = dsi->un_fileno;
			dsi->un_err_blkno = dsi->un_next_block;
			bp->b_flags |= B_ERROR;
			goto STINTR_WRAPUP;
		}

		/*
		 * Check if we're closing the tape device.
		 */
		if (dsi->un_openf <= CLOSING) {
			if (dsi->un_openf == CLOSED) {
				DPRINTF("stintr:  warning, already closed\n");
			}
			DPRINTF("stintr:  closing tape device\n");
			dsi->un_openf = CLOSED;
			goto STINTR_SUCCESS;
		}
		/*
		 * Special processing for opening the tape.
		 */
		ssd = (struct st_sense *)dsi->un_mspl;
		if (dsi->un_openf <= OPENING) {
			stintr_opening(c, dsi, bp, ssd);
			goto STINTR_WRAPUP;
		}

		DPRINTF2("stintr:  dma count= %d   blk count= %d  ",
			 un->un_dma_count, un->un_count);
		DPRINTF2("error= %d   resid= %d\n", error, resid);

		/*
		 * Processing for failed command -- do a request sense.
		 */
		 if (c->c_scb.chk  &&  (dsi->un_openf == OPEN)) {
			stintr_sense(c, dsi, un, resid);
			return;
		}
		/*
		 * Finished running request sense, verify that it
		 * worked and restore state variable.  Actual error
		 * processing will be done by stintr_handle_error.
		 */
		 if (dsi->un_openf == SENSING) {
			stintr_ran_sense(c, dsi, un, &resid);
		}
		/*
		 * Special processing retrying failed commands.
		 */
		if (dsi->un_openf == RETRYING_CMD) {
			if (c->c_scb.chk  ||  c->c_scb.busy) {
				EPRINTF("stintr:  retried cmd failed\n");
				bp->b_flags |= B_ERROR;
				dsi->un_openf = OPEN;
				goto STINTR_WRAPUP;
			} else {
				/* DPRINTF("stintr:  retried cmd worked\n"); */
				dsi->un_openf = OPEN;
				goto STINTR_SUCCESS;
			}

		}

		/*
		 * Process all other errors here
		 */
		switch (stintr_handle_error(c, un, bp, dsi, &resid, error)) {
		case real_error:
			/* This error is FATAL ! */
			/* DPRINTF("stintr:  real error handling\n"); */
			bp->b_flags |= B_ERROR;
			goto STINTR_WRAPUP;

		case psuedo_error:
			/* This error really isn't an error. */
			/* DPRINTF("stintr:  psuedo error handling\n"); */
			status = dsi->un_status;
			goto STINTR_SUCCESS;

		case more_processing:
			/* DPRINTF("stintr:  more processing\n"); */
			return;
		}
	} else {

STINTR_SUCCESS:
		/*
		 * Process all successful commands with driver in
		 * OPEN state here.
		 */
		switch (un->un_cmd) {
		case SC_READ:
			dsi->un_status = status;
			dsi->un_lastior = 1;
			if (dsi->un_options & ST_VARIABLE) {
				dsi->un_next_block++;
			} else {
				dsi->un_next_block += un->un_count;
			}
			break;

		case SC_WRITE:
			dsi->un_status = status;
			dsi->un_lastiow = 1;
			if (dsi->un_options & ST_VARIABLE) {
				dsi->un_next_block++;
			} else {
				dsi->un_next_block += un->un_count;
			}
			break;

		case SC_WRITE_FILE_MARK:
			dsi->un_lastiow = 0;
			dsi->un_offset = 0;
			dsi->un_next_block = 0;
			dsi->un_last_block = 0;		/* i.e. no reads allowed */
			dsi->un_fileno++;
			break;

		case SC_SPACE_FILE:
		case SC_BSPACE_FILE:
			dsi->un_lastior = 0;
			dsi->un_lastiow = 0;
			dsi->un_offset = 0;
			dsi->un_next_block = 0;
			dsi->un_last_block = INF;
			dsi->un_eof = ST_NO_EOF;
			dsi->un_fileno += un->un_count;
			break;

		case SC_SPACE_REC:
			dsi->un_lastior = 1;
			if (dsi->un_options & ST_VARIABLE) {
				dsi->un_next_block++;
			} else {
				dsi->un_next_block += un->un_count;
			}
			break;

		case SC_REWIND:
			dsi->un_lastior = 0;
			dsi->un_lastiow = 0;
			dsi->un_offset = 0;
			dsi->un_next_block = 0;
			dsi->un_last_block = INF;
			dsi->un_fileno = 0;
			dsi->un_eof = ST_NO_EOF;
			break;

		case SC_ERASE_TAPE:
		case SC_LOAD:
		case SC_MODE_SELECT:
		case SC_QIC02:
			dsi->un_lastiow = 0;
			dsi->un_lastior = 0;
			dsi->un_offset = 0;
			dsi->un_next_block = 0;
			dsi->un_last_block = INF;
			dsi->un_fileno = 0;
			dsi->un_eof = ST_NO_EOF;
			dsi->un_retry_ct = 0;
			dsi->un_underruns = 0;
			break;

		case SC_REQUEST_SENSE:
		case SC_INQUIRY:
		case SC_MODE_SENSE:
#ifdef	sun2
		case SC_READ_XSTATUS_CIPHER:
#endif	sun2
			break;

		default:
			/* If you get here, there's a bug in the driver */
			printf("st%d:  stintr: invalid command %x\n",
			        un - stunits, un->un_cmd);
			break;
		}


STINTR_WRAPUP:
		/*
		 * Wrap up command processing for a command that has run
		 * to completion (successfully or otherwise).
		 */
		if (bp == &un->un_sbuf  &&
		    ((un->un_flags & SC_UNF_DVMA) == 0)) {
			(*c->c_ss->scs_done)(un->un_mc);
		} else {
			mbdone(un->un_mc);
			un->un_flags &= ~SC_UNF_DVMA;
		}
		if (dsi->un_bufcnt-- >= MAXSTBUF) {
			wakeup((caddr_t) &dsi->un_bufcnt);
		}
	}
}


/*
 * Handle a possible tape error.
 */
static stintr_error_resolution
stintr_handle_error(c, un, bp, dsi, resid, error)
	register struct scsi_ctlr *c;
	register struct scsi_unit *un;
	register struct buf *bp;
	register struct scsi_tape *dsi;
	u_int *resid;
	u_int error;
{
	register struct st_sense *ssd;
	ssd = (struct st_sense *)dsi->un_mspl;

	/* Log error info for "mt status" (ioctl) error reporting */
	dsi->un_err_resid = *resid;
	dsi->un_err_fileno = dsi->un_fileno;
	dsi->un_err_blkno = dsi->un_next_block;
	dsi->un_status = ssd->key;

	if (c->c_scb.chk) {
		/*
		 * Check for tape write append error.  Note, only available
		 * for QIC tapes.
		 */
		if (ST_ILLEGAL(dsi,ssd)  &&  SC_IS_WRITE_COMMAND(un->un_cmd)  &&
		    (dsi->un_options & ST_QIC)) {
			DPRINTF("stintr_handle_error:  write append error\n");
			return (stintr_append_error(c, dsi, un, *resid));

		/*
		 * Special processing for tape write append.
		 */
		} else if (dsi->un_openf == APPEND_TESTING) {
			DPRINTF("stintr_handle_error:  checking write append test\n");
			return (stintr_ran_append(c, dsi, un, resid));

		/*
		 * Check for special errors which need to be suppressed.
		 */
		} else if (stintr_silent_failure(un, dsi)) {
			return (psuedo_error);

		} else if (ST_NO_CART(dsi, ssd)) {
			uprintf("st%d:  no tape loaded\n", un - stunits);
			dsi->un_reset_occurred = 1;
			return (real_error);

		} else if (ST_FILE_MARK(dsi, ssd)) {
			EPRINTF("stintr_handle_error:  file mark\n");
			dsi->un_status = SC_EOF;
			return (stintr_file_mark_detected(un, bp, dsi, *resid));

		} else if (ST_END_OF_TAPE(dsi, ssd)) {
			EPRINTF("stintr_handle_error:  eot\n");
			dsi->un_status = SC_EOT;
			return (stintr_end_of_tape(un, bp, dsi));

		} else if (ST_WRITE_PROT(dsi, ssd)  &&
			   SC_IS_WRITE_COMMAND(un->un_cmd)) {
			uprintf("st%d:  tape is write protected\n", un - stunits);
			dsi->un_read_only = 1;
			return (real_error);


		/*
		 * A block had to be read/written more than
		 * once but was successfully read/written.
		 * Just bump stats and consider the operation a
		 * success.
		 */
		} else if (ST_CORRECTABLE(dsi, ssd)) {
			EPRINTF("stintr_handle_error:  soft error\n");
			dsi->un_retry_ct ++;
			return (psuedo_error);

		} else if (ST_RESET(dsi, ssd)) {
			EPRINTF("stintr_handle_error:  reset\n");
			dsi->un_reset_occurred = 1;
			return (real_error);

		} else if (ST_LENGTH(dsi, ssd)) {
			EPRINTF("stintr_handle_error:  length error\n");
			st_print_cmd(c, un);
			st_error_message(c, dsi);
			printf("\n");
			goto RESIDUE_ERROR;
			/* return (real_error); */

		} else if (ST_ILLEGAL(dsi, ssd)) {
			printf("st%d:  illegal command\n", un-stunits);
			st_print_cmd(c, un);
			st_error_message(c, dsi);
			printf("\n");
			return (real_error);

		/*
		 * Have an sense key error we aren't decoding.
		 */
		} else if (ssd->key != 0) {
			EPRINTF("stintr_handle_error:  undecoded sense key error\n");
			st_print_cmd(c, un);
			st_error_message(c, dsi);
			printf("\n");
			return (real_error);

		/*
		 * Have a check condition error which we aren't decoding.
		 */
		} else {
			EPRINTF("stintr_handle_error:  unknown check condition error\n");
			st_print_cmd(c, un);
			st_error_message(c, dsi);
			printf("\n");
			return (real_error);
		}


	/*
	 * Process busy and reservation errors.
	 */
	} else if (c->c_scb.busy) {

#ifdef	STDEBUG
		if (st_debug  &&  c->c_scb.is) {
			printf("stintr:  reservation conflict error\n");
		} else {
			printf("stintr:  busy error\n");
		}
#endif	STDEBUG

		st_error_message(c, dsi);
		return (real_error);


	/*
	 * Check for host adapter error.
	 */
	} else  if (error != 0) {
		EPRINTF1("stintr:  host adapter error, error= %d\n", error);
		return (real_error);


	/*
	 * Have left over residue data from last command.
	 */
	} else  if (resid != 0) {

RESIDUE_ERROR:
		EPRINTF1("stintr:  residue error, residue= %d\n", *resid);
		return (real_error);


	/*
	 * Have an unknown error.  Don't know what went wrong.
	 */
	} else {
		EPRINTF("stintr_handle_error:  unknown error\n");
		st_print_cmd(c, un);
		st_error_message(c, dsi);
		printf("\n");
		return (real_error);
	}

}


/*
 * Test for special cases where the error is noted but we don't want
 * to print an error message.
 */
static
stintr_silent_failure(un, dsi)
	register struct scsi_unit *un;
	register struct scsi_tape *dsi;
{
	register struct st_sense *ssd;
	ssd = (struct st_sense *)dsi->un_mspl;

	/*
	 * Suppress printing error messages on failed FSFs if we are
	 * at EOM.  This allows the user to use FSF to get to the
	 * EOM by doing mt fsf <bignum>.
	 */
	if ((dsi->un_last_cmd == SC_SPACE_FILE)  &&
	    (dsi->un_options & ST_QIC)  &&
	    (ssd->key == SC_BLANK_CHECK)) {
			DPRINTF("stintr_silent_failure:  suppressing fsf error\n");
			dsi->un_fileno -= un->un_count;
			return (1);
	/*
	 * Suppress printing error messages if we are spacing over EOF
	 * after backspacing over it.  This allows backspacing of the
	 * tape via bsf <num>.
	 */
	} else  if ((dsi->un_last_cmd == SC_SPACE_REC)  &&
		    (dsi->un_options & ST_BSF)  &&  ssd->fil_mk) {
		DPRINTF("stintr_silent_failure:  suppressing eof error\n");
		dsi->un_eof = ST_NO_EOF;
		dsi->un_next_block = 0;
		dsi->un_last_block = INF;
		dsi->un_fileno++;
		dsi->un_lastior = 0;
		dsi->un_lastiow = 0;
		return (1);
	}
	/*
	 * The default is there are no suppressed errors.
	 */
	return (0);
}


/*
 * Special processing for opening and closing the tape drive.
 * Note, no request sense is performed until the device is open.
 */
static
stintr_opening(c, dsi, bp, ssd)
	register struct scsi_ctlr *c;
	register struct scsi_tape *dsi;
	register struct buf *bp;
	register struct st_sense *ssd;
{
	register struct sysgen_sense *sgs;
	register struct scsi_cdb6 *cdb;
	register struct st_ms_mspl *smsd;
	cdb = (struct scsi_cdb6 *)&c->c_cdb;
	smsd = (struct st_ms_mspl *)ssd;
	sgs = (struct sysgen_sense *)ssd;

	/* Intermediate status & reservation conflict (no hope) */
	if (c->c_scb.is){
		EPRINTF("stintr_opening:  reservation/intermediate error\n");
		dsi->un_openf = OPEN_FAILED;
		bp->b_flags |= B_ERROR;
		return;

#ifdef	ST_SYSGEN
	/*
	 * Since the sysgen will always return an illegal command
	 * error if the tape is not rewound, we have to handle this
	 * special case here during opening.
	 */
	} else if ((IS_SYSGEN(dsi)  ||  IS_DEFAULT(dsi))  &&
	    (cdb->cmd == SC_REQUEST_SENSE)  &&  sgs->illegal) {
		EPRINTF("stintr_opening:  sysgen found\n");
		dsi->un_openf = OPENING_SYSGEN;
		bp->b_flags |= B_ERROR;
		return;
#endif	ST_SYSGEN

	/* Check condition error (maybe recoverable) */
	} else if (c->c_scb.chk) {
		DPRINTF("stintr_opening:  check condition\n");
		dsi->un_openf = OPEN_FAILED_TAPE;
		bp->b_flags |= B_ERROR;
		return;

	/* Busy error (recoverable) */
	} else if (c->c_scb.busy) {
		DPRINTF("stintr_opening:  busy\n");
		dsi->un_openf = OPEN_FAILED_LOADING;
		bp->b_flags |= B_ERROR;
		return;
	}

	/*
	 * If we were closing the tape then opened it before it was
	 * done, we've screwed up handling the rewind command.  This
	 * is fixed here.
	 */
	if (cdb->cmd == SC_REWIND) {
		DPRINTF("stintr_opening:  rewind done\n");
		dsi->un_lastior = 0;
		dsi->un_lastiow = 0;
		dsi->un_offset = 0;
		dsi->un_next_block = 0;
		dsi->un_last_block = INF;
		dsi->un_fileno = 0;
		dsi->un_eof = ST_NO_EOF;
	}
	/*
	 * If running mode_sense, check if tape is write protected.
	 * Note, using mode_sense during normal operation will
	 * cause a fault condition.
	 */
	if (cdb->cmd == SC_MODE_SENSE) {
		dsi->un_read_only = 0;
		if (smsd->wp) {
			DPRINTF("stintr_opening:  CCS read only\n");
			dsi->un_read_only = 1;
		}
		if (IS_DEFAULT(dsi)) {
			dsi->un_dev_bsize = (smsd->high_bl <<16) +
			    (smsd->mid_bl <<8) + (smsd->low_bl);
			DPRINTF1("stintr_opening:  default block size= %d\n",
			dsi->un_dev_bsize);
		}
	}
#ifdef	ST_SYSGEN
	/*
	 * Since a request sense is issued after an inquiry cmd, this
	 * will cause a fault condition.  Thus the first byte of status
	 * should be 0x20 if it's a sysgen controller; otherwise it's
	 * some other drive.  Also, verify that tape is loaded in drive
	 * and check if it's write protected.
	 */
	if ((cdb->cmd == SC_REQUEST_SENSE)  &&  (sgs->disk_sense[0] == 0x20)) {
		dsi->un_openf = OPENING_SYSGEN;
		dsi->un_read_only = 0;
		if (sgs->write_prot) {
			DPRINTF("stintr_opening:  sysgen read only\n");
			dsi->un_read_only = 1;
		}
		if (sgs->no_cart) {
			dsi->un_openf = OPEN_FAILED_TAPE;
		}
	}
#endif	ST_SYSGEN
}
/*
 * Command failed, need to run a request sense command to determine why.
 */
static
stintr_sense(c, dsi, un, resid)
	register struct scsi_ctlr *c;
	register struct scsi_tape *dsi;
	register struct scsi_unit *un;
	register u_int resid;
{

	/*
	 * Save away old command state.
	 */
	un->un_saved_cmd.saved_cmd = un->un_cmd;
	un->un_saved_cmd.saved_scb = c->c_scb;
	un->un_saved_cmd.saved_cdb = c->c_cdb;
	un->un_saved_cmd.saved_resid = resid;
	un->un_saved_cmd.saved_dma_addr = un->un_dma_addr;
	un->un_saved_cmd.saved_dma_count = un->un_dma_count;

	/*
	 * Note that ststart will call stmkcdb, which will notice
	 * that the flag is set and not do the copy of the cdb,
	 * doing a request sense rather than the normal command.
	 */
	dsi->un_timeout = 0;
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
stintr_ran_sense(c, dsi, un, resid_ptr)
	register struct scsi_ctlr *c;
	register struct scsi_tape *dsi;
	register struct scsi_unit *un;
	register u_int *resid_ptr;
{

	/*
	 * Check if request sense command failed.  This should
	 * never happen!
	 */
	un->un_flags &= ~SC_UNF_GET_SENSE;
	dsi->un_openf = OPEN;
	if (c->c_scb.chk  ||  c->c_scb.busy  ||  c->c_scb.is) {
		DPRINTF("stintr_ran_sense:  request sense failed\n");
	}

	/* Restore failed command which caused request sense to be run */
	st_restore_cmd_state(c, un, resid_ptr);

#ifdef	ST_SYSGEN
	/*
	 * Special processing for sysgen tape controller.
	 */
	if (IS_SYSGEN(dsi)) {
		stintr_sysgen(dsi, un);
	}
#endif	ST_SYSGEN
}

#ifdef	ST_SYSGEN
/*
 * Translate Sysgen QIC-02 status in SCSI status that the
 * error handler can understand.  In other words, map
 * QIC-02 sense status into SCSI sense key info.
 */
static
stintr_sysgen(dsi, un)
	register struct scsi_tape *dsi;
	register struct scsi_unit *un;
{
	register struct sysgen_sense *sgs;
	register struct st_sense *ssd;

	sgs = (struct sysgen_sense *) dsi->un_mspl;
	ssd = (struct st_sense *) dsi->un_mspl;
	sgs->disk_sense[2] = 0;		/* sense key = no sense */

	if (sgs->bot  &&  (dsi->un_fileno != 0)  &&  (dsi->un_next_block != 0)) {
		uprintf("st%d:  warning, tape rewound\n", un - stunits);
		dsi->un_reset_occurred = 1;
		ssd->key = SC_NOT_READY;
	}

	if (sgs->file_mark) {
		EPRINTF("stintr_sysgen:  file mark\n");
		dsi->un_eof = ST_EOF_PENDING;
		ssd->fil_mk = 1;
	}
	if (sgs->eot) {
		EPRINTF("stintr_sysgen:  eot\n");
		ssd->eom = 1;
	}
	if (sgs->write_prot) {
		/* DPRINTF("stintr_sysgen:  write protected\n"); */
		dsi->un_read_only =1;
		ssd->key = SC_WRITE_PROTECT;
	}


	if (sgs->disk_sense[0] == 0x20  ||  sgs->illegal) {
		EPRINTF("stintr_sysgen:  illegal request\n");
		ssd->key = SC_ILLEGAL_REQUEST;

	} else  if (sgs->not_ready  ||  sgs->reset  ||  sgs->no_cart) {
		EPRINTF("stintr_sysgen:  not ready\n");
		ssd->key = SC_NOT_READY;

	} else  if (sgs->no_data) {
		EPRINTF("stintr_sysgen:  no data\n");
		ssd->key = SC_BLANK_CHECK;

	} else  if (sgs->write_prot) {
		EPRINTF("stintr_sysgen:  write protected\n");
		ssd->key = SC_WRITE_PROTECT;

	} else  if (sgs->data_err) {
		EPRINTF("stintr_sysgen:  hardware error\n");
		ssd->key = SC_HARDWARE_ERROR;

	} else  if (sgs->retries) {
		EPRINTF("stintr_sysgen:  soft error\n");
		ssd->key = SC_RECOVERABLE_ERROR;
	}
}
#endif	ST_SYSGEN


/*
 * A file mark was detected.  Normally, no error is returned;
 * but a non-zero residue transfer count is returned to signal
 * the error.
 */
static stintr_error_resolution
stintr_file_mark_detected(un, bp, dsi, resid)
	register struct scsi_unit *un;
	register struct buf *bp;
	register struct scsi_tape *dsi;
	register u_int resid;
{
	switch (dsi->un_last_cmd) {
	case SC_READ:
		if (dsi->un_options & ST_VARIABLE) {
			dsi->un_next_block++;	/* A little high */
		} else {
			dsi->un_next_block += un->un_count -
				(resid / dsi->un_dev_bsize);
		}
		dsi->un_last_block = dsi->un_next_block;
		break;

	case SC_SPACE_REC:
		dsi->un_next_block += un->un_count;	/* A little high */
		dsi->un_last_block = dsi->un_next_block;
		break;

	default:
		printf("st%d:  scsi tape hit eof on cmd %x\n",
			un - stunits, un->un_cmd);
		break;
	}
	bp->b_resid = resid;

	/*
	 * If any device but Sysgen, bump file position status.
	 * For Sysgen, we'll have to do it later since it gives
	 * advanced file mark errors.
	 */
#ifdef	ST_SYSGEN
	if (IS_SYSGEN(dsi)) {
		dsi->un_eof = ST_EOF_PENDING;
		return (psuedo_error);
	} else {
		dsi->un_eof = ST_EOF;
		dsi->un_fileno++;
		dsi->un_next_block = 0;
		dsi->un_last_block = INF;
		dsi->un_lastior = 0;
		dsi->un_lastiow = 0;
		return (psuedo_error);
	}
#else	ST_SYSGEN
	dsi->un_eof = ST_EOF;
	dsi->un_fileno++;
	dsi->un_next_block = 0;
	dsi->un_last_block = INF;
	dsi->un_lastior = 0;
	dsi->un_lastiow = 0;
	return (psuedo_error);
#endif	ST_SYSGEN
}

/*
 * End of tape.  Note, due to buffered mode I/O, there's
 * no telling where you really died from eot.  We trust
 * that the tape drive takes care of these little details.
 * Normally no error condition is returned; however, a
 * non-zero residue is returned to indicate eot for writes.
 * No further writing will be allowed until the tape is
 * changed.
 */
static stintr_error_resolution
stintr_end_of_tape(un, bp, dsi)
	register struct scsi_unit *un;
	register struct buf *bp;
	register struct scsi_tape *dsi;
{
	bp->b_resid = bp->b_bcount;
	if (un->un_cmd == SC_WRITE) {
		/*
		 * Setting this flag makes stclose
		 * write a file mark before closing.
		 * Until a file mark is written, the
		 * tape will return invalid command
		 * indications and not respond to
		 * rewinds.
		 */
		dsi->un_eof = ST_EOT;	/* no more writes */
		dsi->un_lastiow = 1;
	}
	return (psuedo_error);
}

/*
 * Handle an append error.
 * If we are at the end of the tape, this error indication is spurious.
 * If we are in the middle of the tape, it is quite legitimate.
 * We determine where we are by trying to run a read command.
 * This problem is caused by QIC tapes being at the end of data
 * and not knowing it???
 */
static stintr_error_resolution
stintr_append_error(c, dsi, un, resid)
	register struct scsi_ctlr *c;
	register struct scsi_tape *dsi;
	register struct scsi_unit *un;
	register u_int resid;
{
	register caddr_t *sbuf;

	/*
	 * Append errors are fun!
	 * They can result from either being positioned
	 * in the middle of the tape (in which case the
	 * request to write is illegal) or from being positioned
	 * at the end of tape (which is legal, but the
	 * controller doesn't know it).
	 *
	 * The way to differentiate these two cases is by
	 * trying to read.  If the read works, we must have
	 * been in the middle of the tape, so we report the
	 * append error.  If the read fails, we were at the
	 * end of the tape, so we retry the write.  Easy, huh?
	 *
	 * Allocate a scratch buffer for the read.
	 * We appropriate the sbuf for this.
	 */
	sbuf = (caddr_t *)rmalloc(iopbmap, (long)(dsi->un_dev_bsize +4));

	if ((int)sbuf == NULL) {
		printf("st%d:  can't alloc scratch buffer\n", un - stunits);
		return (real_error);
	}

	/*
	 * Save the original address for rmfree and word align buffer.
	 */
	un->un_scratch_addr = (caddr_t)sbuf;
	while ((u_int)sbuf & 0x03)
		((u_int)sbuf)++;		/* Align it */
	un->un_sbuf.b_un.b_addr = (caddr_t)sbuf;

	/*
	 * Save away old command state.
	 */
	un->un_saved_cmd.saved_cmd = un->un_cmd;
	un->un_saved_cmd.saved_scb = c->c_scb;
	un->un_saved_cmd.saved_cdb = c->c_cdb;
	un->un_saved_cmd.saved_resid = resid;
	un->un_saved_cmd.saved_dma_addr = un->un_dma_addr;
	un->un_saved_cmd.saved_dma_count = un->un_dma_count;

	/*
	 * s?start will call s?mkcdb, which will notice
	 * that we are using a special readp command and
	 * not do the copy of the cdb.
	 */
	dsi->un_openf = APPEND_TESTING;
	un->un_cmd = SC_READ_APPEND;
	(*un->un_c->c_ss->scs_go)(un->un_mc);
	return (more_processing);
}

/*
 * Cleanup after running a read command on behalf of append error
 * evaluation.
 */
static stintr_error_resolution
stintr_ran_append(c, dsi, un, resid_ptr)
	register struct scsi_ctlr *c;
	register struct scsi_tape *dsi;
	register struct scsi_unit *un;
	register u_int *resid_ptr;
{
	rmfree(iopbmap, (long) (dsi->un_dev_bsize +4),
		 (u_long) (un->un_scratch_addr));

	if (c->c_scb.chk) {
		/*
		 * Read failed, thus we are at EOM,
		 * so retry write command.
		 */
		DPRINTF("stintr_ran_append:  retrying write append\n");
		st_restore_cmd_state(c, un, resid_ptr);
		dsi->un_openf = RETRYING_CMD;
		(*un->un_c->c_ss->scs_go)(un->un_mc);
		return (more_processing);


	} else {
		/*
		 * Read worked, which means we are not
		 * at EOM.  Thus the controller
		 * legitimately reported the append error.
		 */
		DPRINTF("stintr_ran_append:  cannot write append\n");
		st_restore_cmd_state(c, un, resid_ptr);
		dsi->un_openf = OPEN;
		return (real_error);
	}
}

static
st_print_cmd(c, un)
	register struct scsi_ctlr *c;
	register struct scsi_unit *un;
{
	register int x;
	register u_char *y = (u_char *)&(c->c_cdb);
#ifdef	lint
	un = un;
#endif	lint


	printf("st%d:  failed cmd =  ", STUNIT(un->un_unit));
	for (x = 0; x < sizeof (struct scsi_cdb6); x++)
		printf("%x  ", *y++);
	printf("\n");
}

#ifdef	STDEBUG
st_print_sid_buffer(sid, count)
	register struct scsi_inquiry_data *sid;
	register int count;
{
	register int x;
	register u_char *y = (u_char *)sid;

	printf("sid buffer:  ");
	for (x = 0; x < count; x++)
		printf("%x  ", *y++);
	printf("\n");
}


st_print_cmd_status(c, dsi)
	register struct scsi_ctlr *c;
	register struct scsi_tape *dsi;
{
	register int x;
	register u_char *y = (u_char *)&(c->c_cdb);

	/* Driver open, no error */
	if (!(c->c_scb.chk)  &&  (dsi->un_openf == OPEN)) {
		printf("stcmd worked: ");
		for (x = 0; x < sizeof (struct scsi_cdb6); x++)
			printf("%x  ", *y++);
		printf("\n");

	/* Driver open, error */
	} else if (c->c_scb.chk  &&  (dsi->un_openf == OPEN)) {
		printf("stcmd failed: ");
		for (x = 0; x < sizeof (struct scsi_cdb6); x++)
			printf("%x  ", *y++);
		printf("\n");

	/* Driver not open, error */
	} else if (c->c_scb.chk  &&  (dsi->un_openf != OPEN)) {
		printf("stcmd failed (no sense): ");
		for (x = 0; x < sizeof (struct scsi_cdb6); x++)
			printf("%x  ", *y++);
		printf("\n\n");

	/* Dump Sense data for failed cmd */
	} else if (!c->c_scb.chk  &&  (dsi->un_openf == SENSING)) {
		st_error_message(c, dsi);
		printf("\n");
	}
}
#endif	STDEBUG

/*
 * Restore old command state after running request sense command.
 */
st_restore_cmd_state(c, un, resid_ptr)
	register struct scsi_ctlr *c;
	register struct scsi_unit *un;
	register u_int *resid_ptr;
{
	un->un_cmd = un->un_saved_cmd.saved_cmd;
	c->c_scb = un->un_saved_cmd.saved_scb;
	c->c_cdb = un->un_saved_cmd.saved_cdb;
	*resid_ptr = un->un_saved_cmd.saved_resid;
	un->un_dma_addr = un->un_saved_cmd.saved_dma_addr;
	un->un_dma_count = un->un_saved_cmd.saved_dma_count;
}

static char *st_key_error_str[] = {
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
	(sizeof(st_key_error_str)/sizeof(st_key_error_str[0]))

static char *st_hp_error_str[] = {
	"",				/* 0x00 */
	"",				/* 0x01 */
	"",				/* 0x02 */
	"write fault",			/* 0x03 */
	"drive not ready",		/* 0x04 */
	"drive not selected",		/* 0x05 */
	"",				/* 0x06 */
	"",				/* 0x07 */
	"logical unit fault",		/* 0x08 */
	"",				/* 0x09 */
	"error log overflow",		/* 0x0a */
	"time-out error",		/* 0x0b */
	"",				/* 0x0c */
	"soft write error",		/* 0x0d */
	"soft interface error",		/* 0x0e */
	"",				/* 0x0f */
	"",				/* 0x10 */
	"hard read error",		/* 0x11 */
	"",				/* 0x12 */
	"space command error",		/* 0x13 */
	"no record found",		/* 0x14 */
	"locate error",			/* 0x15 */
	"",				/* 0x16 */
	"soft read error",		/* 0x17 */
	"soft write error",		/* 0x18 */
	"",				/* 0x19 */
	"parameter overrun",		/* 0x1a */
	"synch. xfer error",		/* 0x1b */
	"",				/* 0x1c */
	"verify error",			/* 0x1d */
	"",				/* 0x1e */
	"hard write error",		/* 0x1f */
	"invalid command",		/* 0x20 */
	"invalid block address",	/* 0x21 */
	"",				/* 0x22 */
	"space cmd error",		/* 0x23 */
	"",				/* 0x24 */
	"invalid cdb lun",		/* 0x25 */
	"invalid cdb field",		/* 0x26 */
	"write protected",		/* 0x27 */
	"media changed",		/* 0x28 */
	"drive reset",			/* 0x29 */
	"mode select changed",		/* 0x2a */
	"block length error",		/* 0x2b */
	"cmd sequence error",		/* 0x2c */
	"overwrite error",		/* 0x2d */
	"blank tape error",		/* 0x2e */
	"",				/* 0x2f */
	"unknown tape format",		/* 0x30 */
	"format failed",		/* 0x31 */
	"",				/* 0x32 */
	"tape length error",		/* 0x33 */
	"invalid cdb",			/* 0x34 */
	"undetected ecc error",		/* 0x35 */
	"no gap found",			/* 0x36 */
	"miscorrected error",		/* 0x37 */
	"block sequence error",		/* 0x38 */
	"tape not ready",		/* 0x39 */
	"no tape installed",		/* 0x3a */
	"tape position error",		/* 0x3b */
	0
};
#define MAX_HP_ERROR_STR \
	(sizeof(st_hp_error_str)/sizeof(st_hp_error_str[0]))


static char *st_cdc_error_str[] = {
	"",				/* 0x00 */
	"illegal command",		/* 0x20 */
	"",				/* 0x21 */
	"illegal density",		/* 0x22 */
	"power-up failure",		/* 0x4b */
	"",				/* 0x4c */
	"",				/* 0x4d */
	"",				/* 0x4e */
	"",				/* 0x4f */
	"no data detected",		/* 0x50 */
	"timeout error",		/* 0x51 */
	"no BOT",			/* 0x52 */
	"",				/* 0x53 */
	"",				/* 0x54 */
	"length error",			/* 0x55 */
	"host xfer error",		/* 0x56 */
	"target xfer error",		/* 0x57 */
	"",				/* 0x58 */
	"cannot space blocks",		/* 0x59 */
	"",				/* 0x5a */
	"illegal block length",		/* 0x5b */
	"",				/* 0x5c */
	"",				/* 0x5d */
	"",				/* 0x5e */
	"cmd parameter error",		/* 0x5f */
	"",				/* 0x60 */
	"",				/* 0x61 */
	"",				/* 0x62 */
	"parity error",			/* 0x63 */
	"soft error",			/* 0x64 */
	"",				/* 0x65 */
	"hard error",			/* 0x66 */
	0
};
#define MAX_CDC_ERROR_STR \
	(sizeof(st_cdc_error_str)/sizeof(st_cdc_error_str[0]))



static char *st_emulex_error_str[] = {
	"",				/* 0x00 */
	"",				/* 0x01 */
	"",				/* 0x02 */
	"",				/* 0x03 */
	"drive not ready",		/* 0x04 */
	"",				/* 0x05 */
	"",				/* 0x06 */
	"",				/* 0x07 */
	"",				/* 0x08 */
	"no tape",			/* 0x09 */
	"tape too short",		/* 0x0a */
	"drive timeout",		/* 0x0b */
	"",				/* 0x0c */
	"",				/* 0x0d */
	"",				/* 0x0e */
	"",				/* 0x0f */
	"",				/* 0x10 */
	"hard data error",		/* 0x11 */
	"",				/* 0x12 */
	"",				/* 0x13 */
	"block not found",		/* 0x14 */
	"",				/* 0x15 */
	"dma timeout",			/* 0x16 */
	"write protected",		/* 0x17 */
	"soft data error",		/* 0x18 */
	"bad block",			/* 0x19 */
	"",				/* 0x1a */
	"",				/* 0x1b */
	"file mark detected",		/* 0x1c */
	"compare error",		/* 0x1d */
	"",				/* 0x1e */
	"",				/* 0x1f */
	"invalid command",		/* 0x20 */
	"",				/* 0x21 */
	"",				/* 0x22 */
	"",				/* 0x23 */
	"",				/* 0x24 */
	"",				/* 0x25 */
	"",				/* 0x26 */
	"",				/* 0x27 */
	"",				/* 0x28 */
	"",				/* 0x29 */
	"",				/* 0x2a */
	"",				/* 0x2b */
	"",				/* 0x2c */
	"",				/* 0x2d */
	"",				/* 0x2e */
	"",				/* 0x2f */
	"unit attention",		/* 0x30 */
	"command timeout",		/* 0x31 */
	"",				/* 0x32 */
	"append error",			/* 0x33 */
	"end-of-media",			/* 0x34 */
	0
};
#define MAX_EMULEX_ERROR_STR \
	(sizeof(st_emulex_error_str)/sizeof(st_emulex_error_str[0]))


/*
 * Return the secondary error code, if available.
 */
static u_char
st_get_error_code(dsi, ssd)
	register struct scsi_tape *dsi;
	register struct st_sense *ssd;
{
	switch (dsi->un_ctype) {

	case ST_TYPE_EMULEX:
		return (ssd->optional_8);
		/* break; */

	case ST_TYPE_HP:
	case ST_TYPE_CDC:
	case ST_TYPE_KENNEDY:
		return (ssd->error);
		/* break; */
	}
	/* The default case is there is no secondary error code */
	return (0);
}


/*
 * Return the text string associated with the sense key value.
 */
static char *
st_print_key(key_code)
	register u_char key_code;
{
	static char *unknown_key = "unknown key";
	if ((key_code > MAX_KEY_ERROR_STR -1)  ||
	    st_key_error_str[key_code] == NULL) {

		return (unknown_key);
	}
	return (st_key_error_str[key_code]);
}

/*
 * Return the text string associated with the secondary
 * error code, if availiable.
 */
static char *
st_print_error(dsi, error_code)
	register struct scsi_tape *dsi;
	register u_char error_code;
{
	static char *unknown_error = "unknown error";
	switch (dsi->un_ctype) {

	case ST_TYPE_HP:
	case ST_TYPE_KENNEDY:
		if (MAX_HP_ERROR_STR < error_code  && 
	    	st_hp_error_str[error_code] != NULL)
			return (st_hp_error_str[error_code]);
		break;

	case ST_TYPE_CDC:
		if (error_code == 0) {
 			return (st_cdc_error_str[0]);
		} else if (error_code == 0x20) {
 			return (st_cdc_error_str[1]);
		} else if (error_code == 0x21) {
 			return (st_cdc_error_str[2]);
		} else if (error_code == 0x22) {
 			return (st_cdc_error_str[3]);
		} else if ((MAX_CDC_ERROR_STR +0x4b -4) > error_code  &&
	    	           st_cdc_error_str[error_code -0x4b +4] != NULL) {
 			return (st_cdc_error_str[error_code -0x4b +4]);
		}
		break;


	case ST_TYPE_EMULEX:
		if ((MAX_EMULEX_ERROR_STR > error_code)  && 
	    	st_emulex_error_str[error_code] != NULL)
			return (st_emulex_error_str[error_code]);
		break;
	}
	return (unknown_error);
}


/*
 * Print the sense key and secondary error codes
 * and dump out the sense bytes.
 */
static
st_error_message(c, dsi)
	register struct scsi_ctlr *c;
	register struct scsi_tape *dsi;
{
	register struct st_sense *ssd;
	register u_char   *cp;
	register int i;
	register u_char error_code;
	struct scsi_unit *un = c->c_un;

	ssd = (struct st_sense *)cp = (struct st_sense *)dsi->un_mspl;
	error_code = st_get_error_code(dsi, ssd);
	printf("st%d error:  sense key(0x%x): %s",
		un - stunits, ssd->key, st_print_key(ssd->key));
	if (error_code != 0) {
		printf(",  error code(0x%x): %s",
		       error_code, st_print_error(dsi, error_code));
	}

	printf("\n           sense = ");
	for (i=0; i < sizeof (struct st_sense); i++)
		printf("%x  ", *cp++);
	printf("\n");
}



stread(dev, uio)
	register dev_t dev;
	register struct uio *uio;
{
	register struct scsi_unit *un;
	register u_int resid;
	register u_int unit;
	register struct scsi_tape *dsi;
	u_int r;

	/* DPRINTF("stread:\n"); */
	unit = STUNIT(dev);
	if (unit > nstape) {
		EPRINTF2("st%d:  stread: invalid unit %d\n", unit, unit);
		return (ENXIO);
	}
	un = &stunits[unit];
	dsi = &stape[unit];

	if (dsi->un_options & ST_VARIABLE) {
		/*
		 * For variable length I/O, if read data is not
		 * less than 64 KB, we won't let you read.  Also,
		 * set device block size to record size so we can
		 * later reposition tape (if enabled).
		 */
		if (MAX_ST_DEV_SIZE < uio->uio_iov->iov_len) {
			printf("st%d:  stread: record size must be < %d KB\n",
			unit, (MAX_ST_DEV_SIZE / 1024));
			return (EIO);
		}

#ifdef	ST_AUTOPOSITION
		/*
		 * Position the tape to the desired record.  Note,
		 * no repositioning will take place if the request
		 * count is not the same as the device block size.
		 * The device block size is the request size of block 0.
		 */
		if (uio->uio_offset != dsi->un_offset) {

			un->un_blkno = uio->uio_offset / dsi->un_dev_bsize;
			EPRINTF2("stread:  want blk= %d, at blk= %d\n",
				 un->un_blkno, dsi->un_next_block);
			if(uio->uio_iov->iov_len != dsi->un_dev_bsize  ||
			   stposition_block(dev, dsi, un->un_blkno)) {
				EPRINTF("stread:  warning, tape not repositioned\n");
				EPRINTF1("stread:  block size= %d\n",
					 dsi->un_dev_bsize);
			} else {
				DPRINTF("stread:  tape repositioned\n");
				dsi->un_dev_bsize = uio->uio_iov->iov_len;
				EPRINTF1("stread:  block size= %d\n",
					 dsi->un_dev_bsize);
			}
		} else {
			if (uio->uio_offset == 0) {
				dsi->un_dev_bsize = uio->uio_iov->iov_len;
				EPRINTF1("stread:  block size= %d\n",
					 dsi->un_dev_bsize);
			}
		}
		dsi->un_offset = uio->uio_offset + uio->uio_iov->iov_len;
#endif	ST_AUTOPOSITION

	/* HANDLE FIXED LENGTH BLOCK CASE */
	} else {
		/*
		 * If read data is not a multiple of our block size,
		 * we won't let you read.
		 */
		if (dsi->un_iovlen != uio->uio_iov->iov_len) {
			DPRINTF("stread:  checking block size\n");
			dsi->un_iovlen = uio->uio_iov->iov_len;
			if (uio->uio_iov->iov_len % dsi->un_dev_bsize) {
				printf("st%d:  stread: not modulo %d block size\n",
				unit, dsi->un_dev_bsize);
				return (EIO);
			}
		}
#ifdef	ST_AUTOPOSITION
		/*
		 * Position the tape to the desired record.
		 */
		if (uio->uio_offset != dsi->un_offset) {

			un->un_blkno = uio->uio_offset / dsi->un_dev_bsize;
			EPRINTF2("stread:  repositioning, want blk= %d, at blk= %d\n",
				 (int)un->un_blkno, dsi->un_next_block);
			if (stposition_block(dev, dsi, un->un_blkno)) {
				EPRINTF("stread:  repositioning failure\n");
				return (EIO);
			}
		}
		dsi->un_offset = uio->uio_offset + uio->uio_iov->iov_len;
#endif	ST_AUTOPOSITION
	}

	resid = uio->uio_resid;
#ifdef	lint
	resid = resid;
#endif	lint
	r = physio(ststrategy, &un->un_rbuf, dev, B_READ, minphys, uio);
	return (r);
}



stwrite(dev, uio)
	register dev_t dev;
	register struct uio *uio;
{
	register struct scsi_unit *un;
	register struct scsi_tape *dsi;
	register u_int unit;

	/* DPRINTF("stwrite:\n"); */
	unit = STUNIT(dev);
	if (unit > nstape) {
		EPRINTF2("st%d:  stwrite: invalid unit %d\n", unit, unit);
		return (ENXIO);
	}
	un = &stunits[unit];
	dsi = &stape[unit];

	if (dsi->un_options & ST_VARIABLE) {
		/*
		 * For variable length I/O, if read data is not
		 * less than 64 KB, we won't let you write.  Also,
		 * set device block size to record size so we can
		 * later reposition tape (if enabled).
		 */
		if (MAX_ST_DEV_SIZE < uio->uio_iov->iov_len) {
			printf("st%d:  sstwrite: record size must be < %d KB\n",
			unit, (MAX_ST_DEV_SIZE / 1024));
			return (EIO);
		}
#ifdef	ST_AUTOPOSITION
		/*
		 * Check tape position. Only allow repositioning to the
		 * beginning of a file.  Do not allow positioning within
		 * a file.  Note, if this is a QIC tape you'll die later
		 * since overwriting is prohibited.
		 */
		if (uio->uio_offset != dsi->un_offset) {

			if (uio->uio_offset != 0  ||  stposition_block(dev, dsi, 0)) {
				EPRINTF("stwrite:  warning, tape not repositioned\n");
				EPRINTF2("stwrite:  want blk= %d, at blk=%d\n",
					 (uio->uio_offset / dsi->un_dev_bsize),
					 dsi->un_next_block);
			} else {
				DPRINTF("stwrite:  tape repositioned\n");
				dsi->un_dev_bsize = uio->uio_iov->iov_len;
			}
		} else {
			dsi->un_dev_bsize = uio->uio_iov->iov_len;
		}
		dsi->un_offset = uio->uio_offset + uio->uio_iov->iov_len;
#endif	ST_AUTOPOSITION

	/* HANDLE FIXED LENGTH BLOCK CASE */
	} else {
		/*
		 * If write data is not a multiple of our block size,
		 * we won't let you write.
		 */
		if (dsi->un_iovlen != uio->uio_iov->iov_len) {
			DPRINTF("stwrite:  checking block size\n");
			dsi->un_iovlen = uio->uio_iov->iov_len;
			if (uio->uio_iov->iov_len % dsi->un_dev_bsize) {
				printf("st%d:  stwrite: not modulo %d block size\n",
				unit, dsi->un_dev_bsize);
				return (EIO);
			}
		}
#ifdef	ST_AUTOPOSITION
		/*
		 * Check tape position. Only allow repositioning to the
		 * beginning of a file.  Do not allow positioning within
		 * a file.  Note, if this is a QIC tape you'll die later
		 * since overwriting is prohibited.
		 */
		if (uio->uio_offset != dsi->un_offset) {

			if (uio->uio_offset != 0  ||  stposition_block(dev, dsi, 0)) {
				EPRINTF("stwrite:  warning, tape not repositioned\n");
				EPRINTF2("stwrite:  want blk= %d, at blk= %d\n",
					 (uio->uio_offset / dsi->un_dev_bsize),
					 dsi->un_next_block);
			}
		}
		dsi->un_offset = uio->uio_offset + uio->uio_iov->iov_len;
#endif	ST_AUTOPOSITION
	}
	return (physio(ststrategy, &un->un_rbuf, dev, B_WRITE, minphys, uio));
}


/*
 * Position_file - position the tape to the specified absolute file number.
 * Returns 0 (success) or 1 (failure).
 */
static
stposition_file(dev, dsi, fileno)
	register dev_t dev;
	register struct scsi_tape *dsi;
	register int fileno;
{
	register u_int unit;
	unit = STUNIT(dev);

	/*
	 * If the file number is negative or zero,
	 * just rewind the tape and assume he wants
	 * file 0.
	 */
	if (fileno <= 0) {
		EPRINTF("stposition_file:  back spacing to BOT...\n");
		if (stcmd(dev, SC_REWIND, 0) == 0)
			goto ST_FILE_ERROR;

	/*
	 * If the file number is less than our current file
	 * position, then we'll have to backspace some files.
	 * Note, for dumb QIC drives, we'll have to rewind
	 * and space forward since they can't backspace files.
	 */
	} else  if (fileno < dsi->un_fileno)	{
		EPRINTF("stposition_file:  back spacing...\n");
		if (dsi->un_options & ST_BSF) {
			fileno = dsi->un_fileno - fileno +1;
			if (stcmd(dev, SC_BSPACE_FILE, fileno) == 0  ||
			    stcmd(dev, SC_SPACE_REC, 1) == 0)
				goto ST_FILE_ERROR;
		} else {
			if (stcmd(dev, SC_REWIND, 0) == 0  ||
			    stcmd(dev, SC_SPACE_FILE, fileno) == 0)
				goto ST_FILE_ERROR;
		}

	/*
	 * If the file number is greater than the current file
	 * position, then we'll have to forward space some files.
	 */
	} else  if (fileno > dsi->un_fileno) {
		EPRINTF("stposition_file:  forward spacing...\n");
		fileno = fileno - dsi->un_fileno;
		if (stcmd(dev, SC_SPACE_FILE, fileno) == 0) {
ST_FILE_ERROR:
			printf("st%d:  file positioning error\n", unit);
			return (1);
		}
	/*
	 * If the file number is the same as the current file
	 * position, then we'll just sit here.
	 */
	 } else  if ((fileno == dsi->un_fileno)  &&  (dsi->un_next_block != 0)) {
		EPRINTF("stposition_file:  begining of file...\n");
		if (dsi->un_options & ST_BSF) {
			if (stcmd(dev, SC_BSPACE_FILE, 1) == 0  ||
			    stcmd(dev, SC_SPACE_REC, 1) == 0)
				goto ST_FILE_ERROR;
		} else {
			if (stcmd(dev, SC_REWIND, 0) == 0 ||
			    stcmd(dev, SC_SPACE_FILE, fileno) == 0)
				goto ST_FILE_ERROR;
		}
	}
	dsi->un_next_block = 0;
	return (0);
}

/*
 * Position_tape - position the tape at the requested block from
 * the begining of the current tape file.  Returns 0 (success) or
 * 1 (failure).
 *	 After positioning the tape, dsi->un_next_block reflects the
 * new position.
 *	 Note, this routine does not support writing; only reading.
 * For writes, you should pad with null blocks and only fail on
 * backward motion.
 */
/*ARGSUSED*/
static
stposition_block(dev, dsi, block)
	register dev_t dev;
	register struct scsi_tape *dsi;
	register int block;
{
	register int delta;

	if (block < 0)
		block = 0;
	/*
	 * If record is behind us, space backward to it.
	 */
	delta = block - dsi->un_next_block;
	if (delta < 0) {
		EPRINTF1("stposition_block:  space backward %d blocks\n",
			 delta);
		if (dsi->un_options & ST_BSR) {
			if (stcmd(dev, SC_SPACE_REC, delta) == 0)
				return (1);
		} else {
			if (stposition_file(dev, dsi, dsi->un_fileno)  ||
			    stcmd(dev, SC_SPACE_REC, block) == 0)
				return (1);
		}

	/*
	 * If record is ahead of us, space forward to it.
	 */
	} else  if (delta > 0) {
		EPRINTF1("stposition_tape:  space forward %d blocks\n",
			 delta);
		if (stcmd(dev, SC_SPACE_REC, delta) == 0)
			return (1);
	}
	/* Handle delta = 0 case here */
	/* DPRINTF("stposition_block:  position ok\n"); */
	return (0);
}


/*ARGSUSED*/
stioctl(dev, cmd, data, flag)
	dev_t dev;
	register u_int cmd;
	register caddr_t data;
	int flag;
{
	register struct mtop *mtop;
	register int callcount, fcount;
	register struct mtget *mtget;
	register u_int unit;
	register struct scsi_tape *dsi;
	static u_int ops[] = {
		SC_WRITE_FILE_MARK,	/* write tape mark */
		SC_SPACE_FILE,		/* forward space file */
		SC_BSPACE_FILE,		/* backspace file */
		SC_SPACE_REC,		/* forward space record */
		SC_SPACE_REC,		/* backspace record */
		SC_REWIND,		/* rewind tape */
		SC_UNLOAD,		/* unload */
		SC_REQUEST_SENSE,	/* get status */
		SC_REWIND,		/* retension  */
		SC_ERASE_TAPE,		/* erase entire tape */
	};

	unit = STUNIT(dev);
	if (unit > nstape) {
		EPRINTF2("st%d:  stioctl: invalid unit %d\n", unit, unit);
		return (ENXIO);
	}
	dsi = &stape[unit];
	switch (cmd) {
	case MTIOCTOP:			/* Tape operation */
		mtop = (struct mtop *) data;
		switch (mtop->mt_op) {

		case MTBSF:
			/*
			 * If we were writing on a 1/2-inch tape.  Make sure
			 * a second file mark is put on the tape before
			 * rewinding.  Note, compute absolute file position
			 * BEFORE writing second file mark to avoid			 * having to compensate for additional file mark.
			 */
			fcount = dsi->un_fileno - mtop->mt_count;
#ifdef	ST_SYSGEN
			if (dsi->un_eof == ST_EOF_PENDING) {
				dsi->un_eof = ST_NO_EOF;
				dsi->un_fileno++;
				dsi->un_next_block = 0;
				dsi->un_last_block = INF;
				dsi->un_lastior = 0;
			}
#endif	ST_SYSGEN
			DPRINTF2("MTBSF:  file= %d, delta= %d\n",
				dsi->un_fileno, fcount);
			if (dsi->un_lastiow  &&  (dsi->un_options & ST_REEL)) {
				DPRINTF("stioctl:  writing second file mark\n");
				(void) stcmd(dev, SC_WRITE_FILE_MARK, 1);
				dsi->un_lastiow = 0;
			}
			if (stposition_file(dev, dsi, fcount))
				return (EIO);
			return (0);
			/* break; */

		case MTFSF:
			fcount = dsi->un_fileno + mtop->mt_count;
#ifdef	ST_SYSGEN
			if (dsi->un_eof == ST_EOF_PENDING) {
				dsi->un_eof = ST_NO_EOF;
				dsi->un_fileno++;
				dsi->un_next_block = 0;
				dsi->un_last_block = INF;
				dsi->un_lastior = 0;
			}
#endif	ST_SYSGEN
			if (stposition_file(dev, dsi, fcount))
				return (EIO);
			return (0);
			/* break; */

		case MTBSR:
			fcount = dsi->un_next_block - mtop->mt_count;
			if (stposition_block(dev, dsi, fcount))
				return (EIO);
			return (0);
			/* break; */

		case MTFSR:
			fcount = dsi->un_next_block + mtop->mt_count;
			if (stposition_block(dev, dsi, fcount))
				return (EIO);
			return (0);
			/* break; */

		case MTRETEN:
			dsi->un_reten_rewind = 1;
			/* Fall through into MTREW... */

		case MTREW:
			/*
			 * If we were writing on a 1/2-inch tape.  Make sure
			 * a second file mark is put on the tape before
			 * rewinding.
			 */
			if (dsi->un_lastiow  &&  (dsi->un_options & ST_REEL)) {
				DPRINTF("stioctl:  writing second file mark\n");
				(void) stcmd(dev, SC_WRITE_FILE_MARK, 1);
				dsi->un_lastiow = 0;
			}
			callcount = 1;
			fcount = 1;
			break;

		case MTWEOF:
			if (dsi->un_read_only) {
				uprintf("st%d:  tape is write protected\n", unit);
				dsi->un_err_resid = 0;
				dsi->un_err_fileno = dsi->un_fileno;
				dsi->un_err_blkno = dsi->un_next_block;
				dsi->un_status = SC_WRITE_PROTECT;
				return (ENXIO);
			}
			callcount = mtop->mt_count;
			fcount = 1;
			break;

		case MTERASE:
			DPRINTF("stioctl:  erase\n");
			if (dsi->un_read_only) {
				uprintf("st%d:  tape is write protected\n", unit);
				dsi->un_err_resid = 0;
				dsi->un_err_fileno = dsi->un_fileno;
				dsi->un_err_blkno = dsi->un_next_block;
				dsi->un_status = SC_WRITE_PROTECT;
				return (ENXIO);
			}
			(void) stcmd(dev, SC_REWIND, 0);
			callcount = 1;
			fcount = 1;
			break;

		case MTOFFL:
			/*
			 * If we were writing on a 1/2-inch tape.  Make sure
			 * a second file mark is put on the tape before
			 * going offline.
			 */
			DPRINTF("stioctl:  offline\n");
			if (dsi->un_lastiow  &&  (dsi->un_options & ST_REEL)) {
				DPRINTF("stioctl:  writing second file mark\n");
				(void) stcmd(dev, SC_WRITE_FILE_MARK, 1);
				dsi->un_lastiow = 0;
			}
			(void) stcmd(dev, SC_REWIND, 0);
			callcount = 1;
			fcount = 1;
			break;

		case MTNOP:
			return (0);
			/* break; */

		default:
			EPRINTF("stioctl:  illegal command\n");
			return (ENXIO);
			/* break; */
		}


		if (callcount <= 0  ||  fcount <= 0) {
			EPRINTF("stioctl:  invalid parameters\n");
			return (ENXIO);
		}
		while (--callcount >= 0) {
			if (stcmd(dev, ops[mtop->mt_op], fcount) == 0) {
				EPRINTF("stioctl:  command failed\n");
				return (EIO);
			}
		}
		if ((mtop->mt_op == MTERASE)  &&
		    (dsi->un_options & ST_REEL)  &&
		    (minor(dev) & T_NOREWIND)) {
			DPRINTF("stioctl:  rewinding after erase\n");
			(void) stcmd(dev, SC_REWIND, 0);
		}
		return (0);



	case MTIOCGET:				/* Get tape status */
		DPRINTF("stioctl:  get tape status\n");
		mtget = (struct mtget *) data;
		mtget->mt_type = MT_ISSC;
		mtget->mt_erreg = dsi->un_status;
		mtget->mt_resid = dsi->un_err_resid;
		mtget->mt_dsreg = dsi->un_retry_ct;
		mtget->mt_fileno = dsi->un_err_fileno;
		mtget->mt_blkno = dsi->un_err_blkno;
		dsi->un_status = 0;		/* Reset status */
		return (0);


	default:
		EPRINTF("stioctl:  illegal command\n");
		return (ENXIO);
	}
}
#endif	NST > 0
