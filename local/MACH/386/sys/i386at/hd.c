/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	hd.c,v $
 * Revision 1.8.1.16  91/07/15  00:16:46  rvb
 * 	Rationalize p_flag
 * 	[91/07/10            rvb]
 * 
 * 	Kill nuisance print out.
 * 	[91/07/09            rvb]
 * 
 * 	Use BIOS magic to find number of drives.  CMOS RAM does not
 * 	always work.
 * 	[91/06/28            rvb]
 * 
 * Revision 1.8.1.15  90/11/27  13:42:04  rvb
 * 	Synched 2.5 & 3.0 at I386q (r1.8.1.15) & XMK35 (r2.4)
 * 	[90/11/15            rvb]
 * 
 * Revision 1.8.1.14  90/09/18  08:38:49  rvb
 * 	Typo & vs && at line 592.		[contrib]
 * 	Make Status printout on error only conditional on hd_print_error.
 * 	So we can get printout during clobber_my_disk.
 * 	[90/09/08            rvb]
 * 
 * Revision 1.8.1.13  90/08/25  15:44:38  rvb
 * 	Use take_<>_irq() vs direct manipulations of ivect and friends.
 * 	[90/08/20            rvb]
 * 
 * Revision 1.8.1.12  90/07/27  11:25:30  rvb
 * 	Fix Intel Copyright as per B. Davies authorization.
 * 	Let anyone who as opened the disk do absolute io.
 * 	[90/07/27            rvb]
 * 
 * Revision 1.8.1.11  90/07/10  11:43:22  rvb
 * 	Unbelievable bug in setcontroller.
 * 	New style probe/slave/attach.
 * 	[90/06/15            rvb]
 * 
 * Revision 1.8.1.10  90/03/29  19:00:00  rvb
 * 	Conditionally, print out state info for "state error".
 * 	[90/03/26            rvb]
 * 
 * Revision 1.8.1.8  90/03/10  00:27:20  rvb
 * 	Fence post error iff (bp->b_blkno + hh.blocktotal ) > partition_p->p_size)
 * 	[90/03/10            rvb]
 * 
 * Revision 1.8.1.7  90/02/28  15:49:35  rvb
 * 	Fix numerous typo's in Olivetti disclaimer.
 * 	[90/02/28            rvb]
 * 
 * Revision 1.8.1.6  90/01/16  15:54:14  rvb
 * 	FLush pdinfo/vtoc -> evtoc
 * 	[90/01/16            rvb]
 * 
 * 	Must be able to return "dos{cyl,head,sector}"
 * 	[90/01/12            rvb]
 * 
 * 	Be careful about p_size bound's checks if B_MD1 is true.
 * 	[90/01/12            rvb]
 * 
 * Revision 1.8.1.5  90/01/08  13:29:29  rvb
 * 	Add Intel copyright.
 * 	Add Olivetti copyright.
 * 	[90/01/08            rvb]
 * 
 * 	It is no longer possible to set the start and size of disk
 * 	partition "PART_DISK" -- it is always loaded from the DOS
 * 	partition data.
 * 	[90/01/08            rvb]
 * 
 * Revision 1.8.1.4  90/01/02  13:54:58  rvb
 * 	Temporarily regress driver to one that is known to work with Vectra's.
 * 
 */
 
/*
  Copyright 1988, 1989 by Intel Corporation, Santa Clara, California.

		All Rights Reserved

Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appears in all
copies and that both the copyright notice and this permission notice
appear in supporting documentation, and that the name of Intel
not be used in advertising or publicity pertaining to distribution
of the software without specific, written prior permission.

INTEL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
IN NO EVENT SHALL INTEL BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*
 *  AT Hard Disk Driver
 *  Copyright Ing. C. Olivetti & S.p.A. 1989
 *  All rights reserved.
 *
 */
/*
  Copyright 1988, 1989 by Olivetti Advanced Technology Center, Inc.,
Cupertino, California.

		All Rights Reserved

  Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appears in all
copies and that both the copyright notice and this permission notice
appear in supporting documentation, and that the name of Olivetti
not be used in advertising or publicity pertaining to distribution
of the software without specific, written prior permission.

  OLIVETTI DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
IN NO EVENT SHALL OLIVETTI BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUR OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/


typedef long paddr_t;

#include <hd.h>

#ifdef	MACH_KERNEL
#include <sys/types.h>
#include <device/buf.h>
#include <device/errno.h>
#else	MACH_KERNEL
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/buf.h>
#include <sys/errno.h>
#include <sys/user.h>
#include <sys/vmparam.h>
#include <sys/uio.h>
#endif	MACH_KERNEL

#include <i386/ipl.h>
#include <i386at/atbus.h>
#include <i386at/hdreg.h>
#include <i386at/disk.h>

#define WHOLE_DISK(unit) ( (unit << 4) + PART_DISK )

#define NOP_DELAY {asm("nop");}

#define PRIBIO	20
#define PAGESIZ 	4096

#define CMOS_ADDR	0x70	/* I/O port address for CMOS ram addr */
#define CMOS_DATA	0x71	/* I/O port address for CMOS ram data */
#define HDTBL		0x12	/* byte offset of the disk type in CMOS ram */

#ifndef	NULL
#define NULL	0
#endif

/* From sys/systm.h */
struct buf *geteblk();

#define paddr(X)	(paddr_t)(X->b_un.b_addr)
#define b_cylin b_resid

struct hh 				hh;
struct isa_dev *hdinfo[NHD];
struct alt_info 			alt_info[NDRIVES];
struct buf rhdbuf[NDRIVES];
struct buf hdbuf[NDRIVES]; 	/* buffer for raw io */
struct buf hdunit[NDRIVES];

struct buf *bp1, *bp2, *bp3;

partition_t	partition_struct[NDRIVES][V_NUMPAR];

typedef struct {

	unsigned short	ncylinders;
	unsigned short	nheads;
	unsigned short	precomp;
	unsigned short	landzone;
	unsigned short	nsecpertrack;
		} hdisk_t;
hdisk_t	hdparams[NDRIVES];	
hdisk_t rlparams[NDRIVES];

int ndrives = 1;

int domapping = 0;	/* handle bad block mapping or not */

unsigned hddebug = 0;
int	reset_requested = 0;

int hdstrategy(), hdminphys(), hdrawio();
int hdprobe(), hdslave(), hdattach();
int hdintr();

int (*hdintrs[])() = {hdintr, 0};

struct	isa_driver	hddriver = {
	hdprobe, hdslave, hdattach, "hd", 0, 0, 0};


hdprobe(ctlr)
struct isa_ctlr *ctlr;
{
	int port_status = (int)ctlr->ctlr_addr + (PORT_STATUS-PORT_DATA);
	u_char stat = inb(port_status);

	if ((stat & STAT_READY) == STAT_READY) {
		take_ctlr_irq(ctlr);
		printf("hdc%d: port = %x, spl = %d, pic = %d.\n",
			ctlr->ctlr_ctlr, ctlr->ctlr_addr, ctlr->ctlr_spl, ctlr->ctlr_pic);
		return 1;
	} else
		return 0;
}


/*
 * hdslave:
 *
 *	Actually should be thought of as a slave probe.  Since we are
 *	a driver for an AT, and only one ESDI controller lives in the
 *	normal AT, we assume the controller and check for one or two
 *	hard disks that may be attached.
 *
 */

hdslave(dev)
struct isa_dev		*dev;
{
	int slave = dev->dev_slave;
	uchar	*bios_magic = (uchar *)(0xc0000475);

	if (*bios_magic >= 1 + slave)
		return(1);

	return(0);
}

/*
 * hdattach:
 *
 *	Attach the drive unit that has been successfully probed.  For the
 *	AT ESDI drives we will initialize all driver specific structures
 *	and complete the controller attach of the drive.
 *
 */

hdattach(dev)
struct	isa_dev	*dev;
{
	int	unit = dev->dev_unit;
	unsigned long n;
	unsigned char *tbl;

	hdinfo[unit] = dev;

	ndrives = (ndrives >= unit + 1) ? ndrives : unit + 1;

	n = *(unsigned long *)phystokv(dev->dev_addr);
	tbl = (unsigned char *)(phystokv((n&0xffff) + ((n >> 12)&0xffff0) ));

	hdparams[unit].ncylinders = *tbl++;
	hdparams[unit].ncylinders |= *tbl++ << 8;
	hdparams[unit].nheads = *tbl++ & 0x00ff;
	tbl +=2;
	hdparams[unit].precomp = *tbl++;
	hdparams[unit].precomp |= *tbl++ << 8;
	tbl +=5;
	hdparams[unit].landzone = *tbl++;
	hdparams[unit].landzone |= *tbl++ << 8;
	hdparams[unit].nsecpertrack = *tbl;
	rlparams[unit] = hdparams[unit];
	printf("hd%d:  stat = %x, spl = %d, pic = %d. (controller %d, slave %d)\n",
		unit, dev->dev_addr, dev->dev_spl, dev->dev_pic,
		dev->dev_ctlr, dev->dev_slave);
	printf("hd%d:   %dMeg, cyls %d, heads %d, secs %d, precomp %d, landzone %d\n",
		unit,
		hdparams[unit].ncylinders*hdparams[unit].nheads*hdparams[unit].nsecpertrack*
		 512/1000000,
		hdparams[unit].ncylinders, hdparams[unit].nheads, hdparams[unit].nsecpertrack,
		hdparams[unit].precomp, hdparams[unit].landzone);
	hdunit[unit].b_active = 0;
	hdunit[unit].b_actf = hdunit[unit].b_actl = 0;
	setcontroller(unit);
	return;

}

hdopen(dev, flags)
{
	unsigned char unit, part, n;
	int	errcode = 0;

	unit = UNIT(dev);
	part = PARTITION(dev);

	if (unit >= ndrives || part >= V_NUMPAR || !hdinfo[unit] || !hdinfo[unit]->dev_alive)
		return(ENXIO);

	if (!partition_struct[unit][PART_DISK].p_size) {
		domapping = 0;
		getvtoc(unit);
		domapping = 1;
	}

	if (partition_struct[unit][part].p_flag & V_VALID)
		partition_struct[unit][part].p_flag |= V_OPEN;
	else
		errcode = ENXIO;

open1:
	return(errcode);
}


hdclose(dev)
{
	unsigned char unit, part;
	unsigned int old_priority;

	unit = UNIT(dev);
	part = PARTITION(dev);

	partition_struct[unit][part].p_flag &= ~V_OPEN;
}

#ifdef	MACH_KERNEL
/*
 *	No need to limit IO size to 4096 bytes.
 */
int hdread(dev, ior)
	dev_t	dev;
	io_req_t ior;
{
	return (block_io(hdstrategy, minphys, ior));
}

int hdwrite(dev, ior)
	dev_t	dev;
	io_req_t ior;
{
	return (block_io(hdstrategy, minphys, ior));
}

#else	MACH_KERNEL
hdread(dev,uio)
register short  dev;
struct uio 	*uio;
{
	return(physio(hdstrategy, &hdbuf[UNIT(dev)], dev, B_READ, hdminphys, uio));
}

hdwrite(dev,uio)
dev_t	 	dev;
struct uio	*uio;
{
	return(physio(hdstrategy, &hdbuf[UNIT(dev)], dev, B_WRITE, hdminphys, uio));
}
#endif	MACH_KERNEL

/* Trim buffer length if buffer-size is bigger than page size */
hdminphys(bp)
struct buf	*bp;
{
	if (bp->b_bcount > PAGESIZ)
		bp->b_bcount = PAGESIZ;
}

#ifdef	MACH_KERNEL
#else	MACH_KERNEL
hdioctl(dev, cmd, arg, mode)
dev_t dev;
int cmd;
caddr_t arg;
{
	unsigned char unit, part;
	union io_arg  *arg_kernel; 
	unsigned int i, snum, old_priority;
	struct absio *absio_kernel;
	union vfy_io *vfy_io_kernel;
	int xcount, errcode = 0;
	int intlv;

	unit = UNIT(dev);
	part = PARTITION(dev);

	switch (cmd) {
	case V_CONFIG:
		arg_kernel = (union io_arg *)arg;
		if (arg_kernel->ia_cd.secsiz != SECSIZE) {
			/* changing sector size NOT allowed */
			/* u.u_error = EINVAL; */ 
		  	errcode = EINVAL;
			break;
		}
		hdparams[unit].ncylinders=(unsigned short)arg_kernel->ia_cd.ncyl;
		hdparams[unit].nheads = (unsigned short)arg_kernel->ia_cd.nhead;
		hdparams[unit].nsecpertrack = (unsigned short)arg_kernel->ia_cd.nsec;
		setcontroller(unit);
		break;

	case V_REMOUNT:
		getvtoc(unit);	
		break;

	case V_ADDBAD:

		/* this adds a bad block to IN CORE alts table ONLY */
		arg_kernel = (union io_arg *)arg;
		alt_info[unit].alt_sec.alt_used++;
		alt_info[unit].alt_sec.alt_bad[
		alt_info[unit].alt_sec.alt_used]=  arg_kernel->ia_abs.bad_sector;
		break;

	case V_GETPARMS:
		{
		struct disk_parms *disk_parms = (struct disk_parms *)arg;
		
		disk_parms->dp_type = DPT_WINI;
		disk_parms->dp_heads = hdparams[unit].nheads;
		disk_parms->dp_cyls = hdparams[unit].ncylinders;
		disk_parms->dp_sectors  = hdparams[unit].nsecpertrack;
  		disk_parms->dp_dosheads = rlparams[unit].nheads;
		disk_parms->dp_doscyls = rlparams[unit].ncylinders;
		disk_parms->dp_dossectors  = rlparams[unit].nsecpertrack;
		disk_parms->dp_secsiz = SECSIZE;
		disk_parms->dp_ptag = 0;
		disk_parms->dp_pflag =partition_struct[unit][part].p_flag;
		disk_parms->dp_pstartsec = partition_struct[unit][part].p_start;
		disk_parms->dp_pnumsec =partition_struct[unit][part].p_size;
		break;
		}

	case V_FORMAT:
		arg_kernel = (union io_arg *)arg;
		hh.format_request = 1;		
		hh.controller_busy = 1;
		for (i =0; i < SECSIZE; i++) 
			hh.interleave_tab[i] = 0; /* 0 means not taken */

		/* start formatting at sector one, not sector zero */
		intlv = arg_kernel->ia_fmt.intlv;
		i = 0;
		snum = 1;
		hh.interleave_tab[i] = snum++;	
		do {
			i = (i + intlv) % hdparams[unit].nsecpertrack;
			while (hh.interleave_tab[i] != 0) { /* taken */
				i = (i + 1) % 
					(hdparams[unit].nsecpertrack );	
				if (snum > hdparams[unit].nsecpertrack)
					goto fmt1;
			}
			hh.interleave_tab[i] = snum++;	
		
		} while (snum <= hdparams[unit].nsecpertrack);
fmt1:
		/* format all tracks in request */

		hh.format_track = arg_kernel->ia_fmt.start_trk;
		hh.curdrive = unit;
		for (i=0; i <arg_kernel->ia_fmt.num_trks; i++,hh.format_track++ ) {
			hh.retry_count = 0;
			badblock_mapping();
			format_command();
			sleep(&hh.interleave_tab[0], PRIBIO);
		}
		hh.format_request = 0;	
		hh.controller_busy = 0;	
		break;

	case V_PDLOC:
		{
		unsigned int *pd_loc;
		
		pd_loc = (unsigned int *)arg;
		*pd_loc = (unsigned int)(hh.start_of_unix[unit]) + PDLOCATION; 
		break;
		}
	case V_RDABS:
		/* V_RDABS is relative to head 0, sector 0, cylinder 0 */
		bp1 = geteblk(SECSIZE);
		absio_kernel = (struct absio *)arg;
		bp1->b_flags = B_READ | B_MD1;	/* MD1 is be absolute */
		bp1->b_blkno = absio_kernel->abs_sec;
		bp1->b_dev = WHOLE_DISK(unit);	/* 4 lsb's = 0 = partit 0 = RDABS */	
		bp1->b_bcount = SECSIZE;
		/* no badblock_mapping(), no offset by partition_p->p_start */
		hdstrat2(bp1);
		biowait(bp1);
		bp1->b_flags &= ~B_MD1;
		if (bp1->b_flags & B_ERROR) {
			printf("hd: read failure on ioctl\n");
			errcode = ENXIO;
			brelse(bp1);
			break;
		}
		if ( copyout( (caddr_t)paddr(bp1), absio_kernel->abs_buf, 
				SECSIZE) !=0 ) {
			errcode = ENXIO;
		}
		brelse(bp1);
		break;

	case V_WRABS:

		/* V_WRABS is relative to head 0, sector 0, cylinder 0 */
		bp1 = geteblk(SECSIZE);
		absio_kernel = (struct absio *)arg;
		if ( copyin( absio_kernel->abs_buf, (caddr_t)paddr(bp1), 
				SECSIZE) !=0 ) {
			/* u.u_error =ENXIO; */
			errcode = ENXIO;
			brelse(bp1);
			break;
		}
		bp1->b_flags = B_WRITE | B_MD1;	/* MD1 is be absolute */
		bp1->b_blkno = absio_kernel->abs_sec;
		bp1->b_dev = WHOLE_DISK(unit);	/* 4 lsb's = 0 = partit 0 = RDABS */	
		bp1->b_bcount = SECSIZE;
		/* no badblock_mapping(), no offset by partition_p->p_start */
		hdstrat2(bp1);
		biowait(bp1);
		bp1->b_flags &= ~B_MD1;
		if (bp1->b_flags & B_ERROR) {
			printf("hd: write failure on ioctl\n");
			/* u.u_error =ENXIO; */
			errcode = ENXIO;
		}
		brelse(bp1);
		break;

	case V_VERIFY:

		if (u.u_uid != 0) {
			errcode = ENXIO;
			break;
		}

		bp1 = geteblk(PAGESIZ);
		vfy_io_kernel = (union vfy_io *)arg;
		bp1->b_flags = B_READ;
		bp1->b_blkno = vfy_io_kernel->vfy_in.abs_sec;
		bp1->b_dev = WHOLE_DISK(unit);	/* 4 lsb's = 0 = partit 0 = RDABS */	
		xcount = vfy_io_kernel->vfy_in.num_sec;
		vfy_io_kernel->vfy_out.err_code = 0;
		snum = PAGESIZ >> 9;
		while (xcount > 0) {
			i = (xcount > snum) ? snum : xcount;
			bp1->b_bcount = i << 9;
			bp1->b_flags |= B_MD1;
			hdstrat2(bp1);
			biowait(bp1);
			bp1->b_flags &= ~B_MD1;
			if (bp1->b_flags & B_ERROR) {
				vfy_io_kernel->vfy_out.err_code = BAD_BLK;
				break;
			}
			xcount -= i;
			bp1->b_blkno += i;
			bp1->b_flags &= ~B_DONE;
		}
		brelse(bp1);
		break;

	default:
		printf("hdioctl(): do not recognize ioctl of 0x%x \n", cmd);
		/* u.u_error = EINVAL; */
		errcode = EINVAL;
	}
	return(errcode);
}
#endif	MACH_KERNEL

hdstrategy(bp)
struct	buf	*bp;
{
	/* this will allow bufs to drain so that a close open or 
 	   ioctl can procede without interference from users of hdstrategy() 
	*/
	hdstrat2(bp);
}

hdstrat2(bp)
struct	buf	*bp;
{
	struct	buf	*dp;
	partition_t	*partition_p;
	unsigned char unit, partition;
	unsigned int opri;

	if (bp->b_bcount == 0) {
		goto done;
	}

	unit = UNIT((bp->b_dev));
	partition = PARTITION((bp->b_dev));

	partition_p= &(partition_struct[unit][partition]);

	if ( !(partition_p->p_flag & V_VALID))
	{
		bp->b_error = ENXIO;
		goto bad;
	}

	/* if request is off the end or trying to write last block on out */

	if (bp->b_flags & B_MD1) {
		if (bp->b_blkno > partition_struct[unit][PART_DISK].p_start +
				  partition_struct[unit][PART_DISK].p_size - 1) {
			bp->b_error = ENXIO;
			goto bad;
		}
	} else {
		if ( (bp->b_blkno >  partition_p->p_size) ||
		     (bp->b_blkno == partition_p->p_size && !(bp->b_flags & B_READ))) {
			bp->b_error = ENXIO;
			goto bad;
		}
		if (bp->b_blkno == partition_p->p_size) {
		/* indicate (read) EOF by setting b_resid to b_bcount on last block */ 
			bp->b_resid = bp->b_bcount;
			goto done;
		}
	}

	bp->b_cylin = ( ((bp->b_flags & B_MD1) ? 0 : partition_p->p_start) + bp->b_blkno) /
		      (hdparams[hh.curdrive].nsecpertrack * hdparams[hh.curdrive].nheads);

	opri = spl5();
	dp = &hdunit[unit];

	disksort(dp, bp);

	if (!hh.controller_busy)
		hdstart();

	splx(opri);
	return;
bad:
	bp->b_flags |= B_ERROR;
done:
	iodone(bp);
	return;
}

/* hdstart() is called at spl5 */
hdstart()
{
	partition_t	*partition_p;
	int drivecount;
	register struct buf *bp, *dp;

	if (hh.controller_busy) {
		return;
	}

	if(reset_requested) {
		reset_requested = 0;
		reset_controller();
	}
	
	for (drivecount = 0; drivecount < NDRIVES; drivecount++) {
		if ( hh.curdrive < (NDRIVES-1) )
			hh.curdrive++;
		else
			hh.curdrive = 0;

		dp = &hdunit[hh.curdrive];
		if ((bp = dp->b_actf) != NULL)
			break;
	}
	if (drivecount == NDRIVES) {
		return;
	}

	hh.controller_busy = 1;
	hh.blocktotal = (bp->b_bcount + 511) >> 9;

	partition_p = &partition_struct[UNIT(bp->b_dev)][PARTITION(bp->b_dev)];
	
	/* see V_RDABS and V_WRABS in hdioctl() */
	if (bp->b_flags & B_MD1) {
		int end = partition_struct[hh.curdrive][PART_DISK].p_start +
				  partition_struct[hh.curdrive][PART_DISK].p_size - 1;

		hh.physblock = bp->b_blkno;
		if ((bp->b_blkno + hh.blocktotal ) > end)
			hh.blocktotal = end - bp->b_blkno + 1;
	} else {
 		hh.physblock = partition_p->p_start + bp->b_blkno;
		if ((bp->b_blkno + hh.blocktotal ) > partition_p->p_size)
			hh.blocktotal = partition_p->p_size - bp->b_blkno + 1;
	}

	hh.blockcount = 0;
	hh.rw_addr = (paddr_t) bp->b_un.b_addr;
	hh.retry_count = 0;

if (hddebug & 1) printf("[");

	start_rw(bp->b_flags & B_READ); 
}


int hd_print_error = 0;
hdintr()
{
	register struct buf *bp, *dp;

	if (!hh.controller_busy) {
		if (hd_print_error)
			printf("hd: false interrupt\n");
		return;
	}
	waitcontroller();
	hh.status = inb(PORT_STATUS);	

	dp = &hdunit[hh.curdrive];
	bp = dp->b_actf;

	if (hh.restore_request == 1) { /* Restore command has completed */
		hh.restore_request = 0;
		if (hh.status & STAT_ERROR)
			hderror(bp);
		else {
			if (bp != NULL)	
				start_rw(bp->b_flags & B_READ);
			else {
				if (hh.format_request)	
					format_command(); 
			}
		}
		return;
	}

	if (hh.status & STAT_WRITEFAULT) {
		panic("hd: write fault\n");
	}

	if (hh.status & STAT_ERROR) {
		if (hd_print_error) {
			 printf("hdintr: state error %x, error = %x\n",
			 	hh.status, inb(PORT_ERROR));
			 printf("hdintr: state error. block %d, count %d, total %d\n",
			 	hh.physblock, hh.blockcount, hh.blocktotal);
			 printf("hdintr: state error. cyl %d, head %d, sector %d\n",
			 	hh.cylinder, hh.head, hh.sector);

		}
		hderror(bp);
		return;
	}

	if (hh.format_request) {
		printf("hdintr: format request\n");
		wakeup(&hh.interleave_tab[0]);
		return;
	}

	if (hh.status & STAT_ECC) 
		printf("hd: ECC soft error fixed, unit %d, partition %d, physical block %d \n",
			hh.curdrive, PARTITION(bp->b_dev), hh.physblock);

	if (bp == NULL ) {
		/* there should be a read/write buffer queued at this point */
		printf("hdintr: no bp buffer to read or write\n");
		return;	
	}

	if (bp->b_flags & B_READ) {
if (hddebug & 4) printf("hd.hdintr(): reading a sector into 0x%x\n", hh.rw_addr);
		while ((inb(PORT_STATUS) & STAT_DATAREQUEST) == 0) {
NOP_DELAY
		}
		linw(PORT_DATA, hh.rw_addr, SECSIZE/2); 
	}

	if ( ++hh.blockcount == hh.blocktotal ) {
		dp->b_actf = bp->av_forw;
		bp->b_resid = 0;
		iodone(bp);
		hh.controller_busy = 0;

if (hddebug & 1) printf("]");

		hdstart();
	} else {
		hh.rw_addr += SECSIZE;
		hh.physblock++;
		if (hh.single_mode)
			start_rw(bp->b_flags & B_READ);
		else if (!(bp->b_flags & B_READ)) {
			/* Load sector into controller for next write */
			waitcontroller();
			while ((inb(PORT_STATUS) & STAT_DATAREQUEST) == 0 ) {
NOP_DELAY
			}
			loutw(PORT_DATA, hh.rw_addr, SECSIZE/2);
		}
	}
}

hderror(bp)
struct buf *bp;
{

	if(++hh.retry_count > 3) {
		if(bp) {
			/************************************************
			* We have a problem with this block, set the	*
			* error flag, terminate the operation and move	*
			* on to the next request.			*
			* With every hard disk transaction error we set	*
			* the reset requested flag so that the contrlr	*
			* is reset before next operation is started.	*
			* A reset is a relatively long operation, the	*
			* upper level routines are better qualified for	*
			* such an operation than the interrupt service	*
			* routines.					*
			************************************************/

			hdunit[hh.curdrive].b_actf = bp->av_forw;
			bp->b_flags |= B_ERROR;
			bp->b_resid = 0;

			biodone(bp);
			hh.controller_busy = 0;
			reset_requested = 1;
			hdstart();
		}
		else {
			/* give up, its way beyond hope */
			if (hh.format_request) {
				printf("hd: can't format track number %d\n", hh.format_track);
				wakeup (&hh.interleave_tab[0]);
			}
		}
	}
	else {
		/* lets do a recalibration */
		waitcontroller();
		hh.restore_request = 1;
		outb(PORT_PRECOMP, hdparams[hh.curdrive].precomp >>2);
		outb(PORT_NSECTOR, hdparams[hh.curdrive].nsecpertrack);
		outb(PORT_SECTOR, hh.sector);
		outb(PORT_CYLINDERLOWBYTE, hh.cylinder & 0xff );
		outb(PORT_CYLINDERHIBYTE,  (hh.cylinder >> 8) & 0xff );
		outb(PORT_DRIVE_HEADREGISTER, 0);
		outb(PORT_COMMAND, CMD_RESTORE);
	}
}

getvtoc(unit)
unsigned char	unit;
{
	unsigned char *c_p;
	unsigned int n, m;
	char *pt1, *pt2;
	struct boot_record *boot_record_p;
	struct evtoc *evp;

	bp1= geteblk(SECSIZE);		/* for evtoc */
	bp2 = geteblk(SECSIZE);		/* for alt_info */

	/* make partition 0 the whole disk in case of failure
  	   then get pdinfo 
	*/
	partition_struct[unit][PART_DISK].p_flag = V_OPEN|V_VALID;
	partition_struct[unit][PART_DISK].p_start = 0; 
	partition_struct[unit][PART_DISK].p_size = hdparams[unit].ncylinders *
		   hdparams[unit].nheads * hdparams[unit].nsecpertrack;

	/* get active partition */
	bp1->b_flags = B_READ | B_MD1;
	bp1->b_blkno = 0;
	bp1->b_dev = WHOLE_DISK(unit);		/* partition is bottom 4 bits */
	bp1->b_bcount = SECSIZE;
	hdstrat2(bp1);
	biowait(bp1);
	bp1->b_flags &= ~B_MD1;
	if (bp1->b_flags & B_ERROR) {
		printf("hd: can not read sector 0 on drive %d, the boot record partition (see AT Tech. Ref.)\n", unit);
		return;
	}
	c_p = (unsigned char *)(paddr(bp1)) + 511;
	if ( *c_p != BOOTRECORDSIGNATURE) {
		printf("hd: sector 0 signature bad, can not read active partition on drive %d\n", unit);
		return;
	}
	c_p = (unsigned char *)(paddr(bp1)) + 446;
	boot_record_p = (struct boot_record *)(c_p);
	for (n=0; n<4; n++, boot_record_p++)
		if (boot_record_p->boot_ind == 0x80) break;

	if (boot_record_p->boot_ind != 0x80) {
		printf("hd: no active partition on drive %d\n", unit);
		return;
	}
	hh.start_of_unix[unit] = boot_record_p->rel_sect;	
	
	/* set correct partition information */

	partition_struct[unit][PART_DISK].p_start = boot_record_p->rel_sect; 
	partition_struct[unit][PART_DISK].p_size = hdparams[unit].ncylinders *
		   hdparams[unit].nheads * hdparams[unit].nsecpertrack - 
		   hh.start_of_unix[unit];

	/* get evtoc out of active unix partition */
	bp1->b_flags = B_READ;
	bp1->b_blkno = PDLOCATION;
	bp1->b_dev = WHOLE_DISK(unit);		/* partition is bottom 4 bits */
	bp1->b_bcount = SECSIZE;
	hdstrat2(bp1);
	biowait(bp1);
	if (bp1->b_flags & B_ERROR) {
		printf("hd: can not read evtoc on drive %d\n", unit);
		return;
	}
	evp = (struct evtoc *)bp1->b_un.b_addr;

	if (evp->sanity != VTOC_SANE) {
		printf("hd: evtoc invalid on drive %d\n",unit);
		return;
	}

	/* pd info from disk must be more accurate than that in cmos
	   thus override hdparams and re- setcontroller()
	*/			
	hdparams[unit].ncylinders = evp->cyls;
	hdparams[unit].nheads = evp->tracks;
	hdparams[unit].nsecpertrack = evp->sectors;
#ifdef	OOPS
	printf("cyl = %d, heads = %d, sectors = %d\n",
		evp->cyls, evp->tracks, evp->sectors);
#else	OOPS
	partition_struct[unit][PART_DISK].p_size = hdparams[unit].ncylinders *
		   hdparams[unit].nheads * hdparams[unit].nsecpertrack - 
		   hh.start_of_unix[unit];
	setcontroller(unit);
#endif	OOPS
		
	/* copy info on all valid partition, zero the others */
	for (n = 0; n < evp->nparts; n++) {
		if (n == PART_DISK)		/* "c" is sacred */
			continue;
		/* this is a STRUCTURE copy */
		partition_struct[unit][n] = evp->part[n];
		if (evp->part[n].p_start >= 0 && evp->part[n].p_size >= 0)
			partition_struct[unit][n].p_flag = V_VALID;
		else
			partition_struct[unit][n].p_flag = 0;
	}
	for ( ; n < V_NUMPAR; n++) {
		if (n == PART_DISK)
			continue;
		partition_struct[unit][n].p_flag = 0;
		partition_struct[unit][n].p_size = 0;
	}	
	/* leave partition 0 "open" for raw I/O */
	partition_struct[unit][PART_DISK].p_flag |= V_OPEN;

	/* get alternate sectors out of active unix partition */
	pt1 = (char *)&alt_info[unit];
	for (n = 0; n < 4; n++) {
		bp2->b_flags = B_READ;
		bp2->b_blkno = evp->alt_ptr/SECSIZE + n;
		bp2->b_dev = WHOLE_DISK(unit);	/* partition is bottom 4 bits */
		bp2->b_bcount = SECSIZE;
		hdstrat2(bp2);
		biowait(bp2);
		if (bp2->b_flags & B_ERROR) {
			printf("hd: can not read alternate sectors on drive %d\n", unit);
			return;
		}
		/* since struct altinfo is split over 4 bufs, can't do 
		   struct copy */
		pt2 = (char *)bp2->b_un.b_addr;
		for (m = 0; m < SECSIZE; m++, pt1++, pt2++)
			*pt1 = *pt2; 
	}

	if (alt_info[unit].alt_sanity != ALT_SANITY) {
		printf("hd: alternate sectors corrupted on drive %d\n", unit);
		return;
	}

	if (bp1 != NULL)
		brelse(bp1);
	if (bp2 != NULL)
		brelse(bp2);
}

format_command()
{
	unsigned int track;
		
	if ( hdparams[hh.curdrive].nheads > 8)
		outb(FIXED_DISK_REG, MORETHAN8HEADS);
	else
		outb(FIXED_DISK_REG, EIGHTHEADSORLESS);
	
	if (hh.block_is_bad)
		track = hh.substitutetrack;
	else
		track = hh.format_track;
	hh.head     = track   % hdparams[hh.curdrive].nheads; 
	hh.head = hh.head | (hh.curdrive << 4) | FIXEDBITS;
	hh.cylinder = track   / hdparams[hh.curdrive].nheads;

	waitcontroller();
	outb(PORT_PRECOMP, hdparams[hh.curdrive].precomp >>2);
	outb(PORT_NSECTOR, hdparams[hh.curdrive].nsecpertrack);
	/* Western Digital 1010 and 1005 want the following line */
	outb(PORT_SECTOR, 36);
	outb(PORT_CYLINDERLOWBYTE, hh.cylinder & 0xff );
	outb(PORT_CYLINDERHIBYTE,  (hh.cylinder >> 8) & 0xff );
	outb(PORT_DRIVE_HEADREGISTER, hh.head);
	outb(PORT_COMMAND, CMD_FORMAT);
	waitcontroller();
	loutw(PORT_DATA, hh.interleave_tab, SECSIZE/2);
}

reset_controller()
{
	int	i;

	outb(0x3F6, 4);
	for(i = 0; i < 10000; i++);
	outb(0x3F6, 0);
	waitcontroller();
	if(1 != (i = inb(0x1F1)))
		printf("reset_controller(): error code %d\n", i);
	setcontroller(0);
	if(ndrives > 1)
		setcontroller(1);
}

setcontroller(unit)
{
	unsigned char nheads;

	waitcontroller();
	nheads = FIXEDBITS | (hdparams[unit].nheads -1);
	nheads |= (unit << 4);
	outb(PORT_DRIVE_HEADREGISTER, nheads); 
	outb(PORT_NSECTOR, hdparams[unit].nsecpertrack);
	outb(PORT_COMMAND, CMD_SETPARAMETERS);
	waitcontroller();
}

waitcontroller()
{
	unsigned int n;

	for (n = 0; n < PATIENCE; n++) {
		if ((inb(PORT_STATUS) & STAT_BUSY) == 0)
			return;
NOP_DELAY
	}
	panic("hard disk drive: waitcontroller() times out");
}

start_rw(read)
{
	unsigned int track, disk_block, xblk;
	struct buf *bp = hdunit[hh.curdrive].b_actf;

	if ( hdparams[hh.curdrive].nheads > 8)
		outb(FIXED_DISK_REG, MORETHAN8HEADS);
	else
		outb(FIXED_DISK_REG, EIGHTHEADSORLESS);

	disk_block = hh.physblock;

	xblk = hh.blocktotal - hh.blockcount;	/* # of blks to transfer */

	if ( (bp->b_flags & B_MD1) == 0 ) {
		xfermode();	/* determine the transfer mode */
		if(hh.single_mode) {
			xblk = 1;
			badblock_mapping();
			if(hh.block_is_bad)
				disk_block = hh.substituteblock;
		}
	}

	/* disk is formatted starting sector 1, not sector 0 */
	hh.sector = (disk_block % hdparams[hh.curdrive].nsecpertrack) + 1;

	track = disk_block / hdparams[hh.curdrive].nsecpertrack;

	hh.head = track % hdparams[hh.curdrive].nheads; 
	hh.head = hh.head | (hh.curdrive << 4) | FIXEDBITS;
	hh.cylinder = track / hdparams[hh.curdrive].nheads;

	waitcontroller();
	outb(PORT_PRECOMP, hdparams[hh.curdrive].precomp >>2);
	outb(PORT_NSECTOR, xblk);
	outb(PORT_SECTOR, hh.sector);
	outb(PORT_CYLINDERLOWBYTE, hh.cylinder & 0xff );
	outb(PORT_CYLINDERHIBYTE,  (hh.cylinder >> 8) & 0xff );
	outb(PORT_DRIVE_HEADREGISTER, hh.head );
	if(read) 
		outb(PORT_COMMAND, CMD_READ);
 	else {
 		outb(PORT_COMMAND, CMD_WRITE); 
		waitcontroller();
		while ((inb(PORT_STATUS) & STAT_DATAREQUEST) == 0) {
NOP_DELAY
		}
		loutw(PORT_DATA, hh.rw_addr, SECSIZE/2);
	}

}

badblock_mapping()
{
	unsigned short n;
	unsigned int track;
	struct buf *bp = hdunit[hh.curdrive].b_actf;

	hh.block_is_bad = 0;

	if (!domapping)
		return;

	/* partition 0 is whole disk, bad blocks and all */
	if ( PARTITION(bp->b_dev) == PART_DISK)
		return;

	/* to support V_RDABS and V_WRABS in hdioctl() */
	if (bp->b_flags & B_MD1)
		return;

	/* BAD TRACK MAPPING */
	track = hh.physblock / hdparams[hh.curdrive].nsecpertrack;	
	
	for (n = 0; n < alt_info[hh.curdrive].alt_trk.alt_used; n++) {
		if (track == alt_info[hh.curdrive].alt_trk.alt_bad[n]) {
			hh.block_is_bad = 1;
			hh.substituteblock =  
				alt_info[hh.curdrive].alt_trk.alt_base + 
				hdparams[hh.curdrive].nsecpertrack * n +
				(hh.physblock % hdparams[hh.curdrive].nsecpertrack);	
			hh.substitutetrack = track;
			return;
		}	
	} 


	/* BAD BLOCK MAPPING */
	/* add do while if substituteblock is bad !!!!!!!!!!  */

	for (n = 0; n < alt_info[hh.curdrive].alt_sec.alt_used; n++) {
		if (hh.physblock == alt_info[hh.curdrive].alt_sec.alt_bad[n]) {
			hh.block_is_bad = 1;
			hh.substituteblock = 
				alt_info[hh.curdrive].alt_sec.alt_base + n;
			break;
		}	
	} 
}

dynamic_badblock()
{
	printf("dynamic_badblock()	--not implemented yet\n");
}

hdsize()
{
	printf("hdsize()	-- not implemented\n");
}

hddump()
{
	printf("hddump()	-- not implemented\n");
}

/*
 * get the disk type from CMOS ram
 */
unsigned char
disktype()
{
	outb(CMOS_ADDR, HDTBL);
	return inb(CMOS_DATA);
}

/*
 *  determine single block or multiple blocks transfer mode
 */
xfermode()
{
	int n, bblk, eblk, btrk, etrk;
	struct buf *bp = hdunit[hh.curdrive].b_actf;

	hh.single_mode = 0;	/* default is multiple mode */

	if (!domapping)		/* if mapping is not on */
		return;

	bblk = hh.physblock;
	eblk = bblk + hh.blocktotal - 1;

	btrk = bblk / hdparams[hh.curdrive].nsecpertrack;	
	etrk = eblk / hdparams[hh.curdrive].nsecpertrack;	
	
	for (n = 0; n < alt_info[hh.curdrive].alt_trk.alt_used; n++) {
		if ((btrk <= alt_info[hh.curdrive].alt_trk.alt_bad[n]) &&
		     (etrk >= alt_info[hh.curdrive].alt_trk.alt_bad[n])) {
			hh.single_mode = 1;
			return;
		}	
	} 


	for (n = 0; n < alt_info[hh.curdrive].alt_sec.alt_used; n++) {
		if ((bblk <= alt_info[hh.curdrive].alt_sec.alt_bad[n]) &&
		    (eblk >= alt_info[hh.curdrive].alt_sec.alt_bad[n])) {
			hh.single_mode = 1;
			break;
		}	
	} 
}

