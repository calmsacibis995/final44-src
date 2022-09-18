/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	adaptec.c,v $
 * Revision 2.1.1.2  91/05/03  10:58:09  rvb
 * 	Lengthen probe timeout. And for now reduce physio buff size to
 * 	one page.
 * 	[91/05/03            rvb]
 * 
 * Revision 2.1.1.1  91/03/28  08:45:03  rvb
 * 	Acquired from osf.
 * 	[91/03/25            rvb]
 * 
 */

/*
 * Adaptec AHA-1542A SCSI driver
 * Copyright (c) 1990 OSF Research Institute 
 */

/*
 * Copyright 1990 by Open Software Foundation,
 * Grenoble, FRANCE
 *
 * 		All Rights Reserved
 * 
 *   Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appears in all copies and
 * that both the copyright notice and this permission notice appear in
 * supporting documentation, and that the name of OSF or Open Software
 * Foundation not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior
 * permission.
 * 
 *   OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
 * IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
 * NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/types.h>

#ifdef	MACH_KERNEL
#include <device/buf.h>
#include <device/errno.h>
#include <device/dev_master.h>
#else	MACH_KERNEL
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <sys/buf.h>
#include <sys/user.h>
#include <sys/systm.h>
#include <sys/reboot.h>
#endif	MACH_KERNEL
#include <i386at/atbus.h>
#include <i386at/scsi.h>
#include <i386at/adaptec.h>
#include <i386at/disk.h>

#ifdef	MACH_KERNEL
struct buf *geteblk();
#define PRIBIO	20
#define PWAIT	30
#endif	MACH_KERNEL


#ifdef	CBUS
#include <cbus/cbus.h>
#define KVTOPHYS(x)	(cbus2at(kvtophys(x)))
#define PHYSTOKV(x)	(phystokv(at2cbus(x)))
#else	CBUS
#define PHYSTOKV(x)	phystokv(x)
#define KVTOPHYS(x)	kvtophys(x)
#endif	CBUS
#define	AHA_DMA_PAGES	AHA_NSEG

#define PAGESIZ 	4096
#define SECSIZE 512
#define PDLOCATION	29	
#define BOOTRECORDSIGNATURE			(0x55aa & 0x00ff)

#define AHA_NOSLEEP	1
#define AHA_NOMASK	2
#define AHA_NOSTART	3

struct aha_mbx aha_mbx;
struct aha_ccb *aha_ccb_free;
struct aha_ccb aha_ccb[AHA_MBX_SIZE];
u_char ccb_data[256];
struct alt_info		aha_alt_info[NTARGET];
#ifndef	MACH_KERNEL
struct buf ahabuf[AHA_MBX_SIZE]; 	/* buffer for raw io */
struct buf *ahabuf_free; 	/* queue of free buffers for raw io */
#endif	MACH_KERNEL
struct buf ahaunit[NTARGET];
extern ahastrategy();
extern ahaminphys();
partition_t	aha_partition_struct[NTARGET][V_NUMPAR];
unsigned int	aha_start_of_unix[NTARGET];	/* unix vs dos partitions */
struct isa_dev *ahainfo[NTARGET];
int	aha_sec_sz[NTARGET];
#ifdef	MACH_KERNEL
decl_simple_lock_data(, aha_queue_lock[NTARGET]);
decl_simple_lock_data(, aha_ccb_lock);
#endif	MACH_KERNEL
struct aha_ccb *aha_get_ccb();
int curtarget;

int	aha_initialized = 0;
int	aha_debug = 0;

int ahaprobe(), ahaslave(), ahaattach();
int ahaintr();
struct	isa_driver	ahadriver = {
	ahaprobe, ahaslave, ahaattach, "aha", 0, 0, 0};

int (*ahaintrs[])() = {ahaintr, 0};

#define aha_startmbx(mbx) \
	mbx->cmd = AHA_MBO_START; \
	outb(AHA_CMD_DATA_PORT, AHA_START_SCSI);
/*
 * aha_cmd(icnt, ocnt, retval, opcode, args)
 * Activate Adapter command
 *	icnt:	number of args (outbound bytes written after opcode)
 *	ocnt:	number of expected returned bytes
 *	retval:	buffer where to place returned bytes
 *	opcode:	opcode AHA_NOP, AHA_MBX_INIT, AHA_START_SCSI ...
 *	args:	parameters
 *
 */

#define AHA_CMD_TIMEOUT	10000000

aha_cmd(icnt, ocnt, retval, opcode, args)

u_char *retval;
unsigned opcode;
u_char args;
{
	unsigned *ic = &opcode;
	u_char oc;
	register i;

	if (opcode != AHA_MBX_INIT && opcode != AHA_START_SCSI) {
		for (i=0; i<AHA_CMD_TIMEOUT; i++)
			if (inb(AHA_CTRL_STAT_PORT) & AHA_IDLE)
				break;
		if (i >= AHA_CMD_TIMEOUT) {
			printf("aha_cmd: Adaptec host not idle\n");
			return(ENXIO);
		}
	}
	if (ocnt)
		while(inb(AHA_CTRL_STAT_PORT) & AHA_DF)
			inb(AHA_CMD_DATA_PORT);
			
	icnt++;
	while (icnt--) {
		for (i=0; i<AHA_CMD_TIMEOUT; i++)
			if (!(inb(AHA_CTRL_STAT_PORT) & AHA_CDF))
				break;
		if (i >= AHA_CMD_TIMEOUT) {
			printf("aha_cmd: Adaptec cmd/data port full\n");
			outb(AHA_CTRL_STAT_PORT, AHA_SRST); 
			return(ENXIO);
		}
		outb(AHA_CMD_DATA_PORT, *ic++);
	}
	while (ocnt--) {
		for (i=0; i<AHA_CMD_TIMEOUT; i++)
			if (inb(AHA_CTRL_STAT_PORT) & AHA_DF)
				break;
		if (i >= AHA_CMD_TIMEOUT) {
			printf("aha_cmd: Adaptec cmd/data port empty\n");
			return(ENXIO);
		}
		oc = inb(AHA_CMD_DATA_PORT);
		if (retval)
			*retval++ = oc;
	}
	return(0);
}

ahaprobe(ctlr)
struct isa_ctlr *ctlr;
{
	if (aha_init() != 0)
		return(0);
	take_ctlr_irq(ctlr);
	printf("ahac%d:port = %x, spl = %d, pic = %d.\n",
	   ctlr->ctlr_ctlr, ctlr->ctlr_addr, ctlr->ctlr_spl, ctlr->ctlr_pic);
	return(1);
}

ahaslave(dev)
struct isa_dev		*dev;
{
	if (aha_req_sense(dev->dev_unit, AHA_NOSLEEP | AHA_NOMASK) != 0)
		return(0);
	else
		return(1);
}

ahaattach(dev)
struct	isa_dev	*dev;
{
	int	unit = dev->dev_unit;
	unsigned long n;
	unsigned char *tbl;
	struct disk_parms ahaparams;

	ahainfo[unit] = dev;

	aha_get_parms(unit, &ahaparams, AHA_NOSLEEP | AHA_NOMASK);
	printf("aha%d: stat = %x, spl = %d, pic = %d. (controller %d, slave %d)\n",
		unit, dev->dev_addr, dev->dev_spl, dev->dev_pic,
		dev->dev_ctlr, dev->dev_slave);
	printf("aha%d: %d Mb, cyls %d, heads %d, secs %d, bytes/sec %d\n",
		unit,
		ahaparams.dp_cyls*ahaparams.dp_heads*ahaparams.dp_sectors/
		(1024*1024),
		ahaparams.dp_cyls, ahaparams.dp_heads, ahaparams.dp_sectors,
		ahaparams.dp_secsiz);
	ahaunit[unit].b_active = 0;
	ahaunit[unit].b_actf = ahaunit[unit].b_actl = 0;
	return;

}

ahaintr()
{
	unsigned char stat;
	register i;

	stat = inb(AHA_INTR_PORT);
	outb(AHA_CTRL_STAT_PORT, AHA_IRST);
	if (! (stat & AHA_MBIF))
		return;
	for (i = 0; i < AHA_MBX_SIZE; i++)
		if (aha_mbx.mbi[i].stat != AHA_MBI_FREE) {
			if (aha_debug && aha_mbx.mbi[i].stat != AHA_MBI_OK)
				printf("stat %x for mbi[%d]\n", aha_mbx.mbi[i].stat, i);
			aha_mbx.mbi[i].stat = AHA_MBI_FREE;
			aha_done(PHYSTOKV(_3btol(aha_mbx.mbi[i].ccb_addr)));
		}
}

aha_free_ccb(ccb, flags)
struct aha_ccb *ccb;
{
	unsigned int opri;
	
	if (!(flags & AHA_NOMASK)) 
	  	opri = spl5();

#ifdef	MACH_KERNEL
	simple_lock(&aha_ccb_lock);
#endif	MACH_KERNEL
	ccb->next = aha_ccb_free;
	aha_ccb_free = ccb;
	curtarget = (curtarget+1) % NTARGET;
#ifdef	MACH_KERNEL
	simple_unlock(&aha_ccb_lock);
#endif	MACH_KERNEL
	if (!ccb->next) {
		if (!(flags & AHA_NOSTART)) {
		  	spl5();
			ahastart();
	        }
		wakeup(&aha_ccb_free);
	}
	if (!(flags & AHA_NOMASK)) 
		splx(opri);
}

struct aha_ccb *
aha_get_ccb(flags)
{
	unsigned opri;
	struct aha_ccb *rc;

	if (!(flags & AHA_NOMASK)) 
	  	opri = spl5();
#ifdef	MACH_KERNEL
	simple_lock(&aha_ccb_lock);
#endif	MACH_KERNEL
	while (!(rc = aha_ccb_free) && !(flags & AHA_NOSLEEP)) {
#ifdef	MACH_KERNEL
		simple_unlock(&aha_ccb_lock);
#endif	MACH_KERNEL
		sleep(&aha_ccb_free, PRIBIO);
#ifdef	MACH_KERNEL
		simple_lock(&aha_ccb_lock);
#endif	MACH_KERNEL
	}
	if (rc) 
		aha_ccb_free = aha_ccb_free->next;
#ifdef	MACH_KERNEL
	simple_unlock(&aha_ccb_lock);
#endif	MACH_KERNEL
	if (!(flags & AHA_NOMASK)) 
		splx(opri);
	return(rc);
}
		

aha_done(ccb)
struct aha_ccb *ccb;
{

	if (!ccb->bp) {
		wakeup(ccb);
		return;
	}
	if (ccb->host_stat != AHA_OK || ccb->target_stat != SCSI_OK) {
		if (aha_debug) {
			printf("host_stat %x, target_stat %x\n",
				ccb->host_stat, ccb->target_stat);
			if (ccb->target_stat == SCSI_CHECK)
				printf("sense key %x\n",
					((struct scsi_data *) &ccb->scsi_cmd.cmd.test_unit_ready.sense[0])->data.extended_sense.sense_key);
		}
		ccb->bp->b_error = EIO;
		ccb->bp->b_flags |= B_ERROR;
	}
	ccb->bp->b_resid = 0;
	iodone(ccb->bp);
	aha_free_ccb(ccb, 0);
}

/*
 * convert a physical address to 3 bytes, MSB at the lowest address,
 * LSB at the highest.
 */

lto3b(val, bytes)
u_char *bytes;
{
	*bytes++ = (val&0xff0000)>>16;
	*bytes++ = (val&0xff00)>>8;
	*bytes = val&0xff;
}

_3btol(bytes)
u_char *bytes;
{
	int rc;
	rc = (*bytes++ << 16);
	rc += (*bytes++ << 8);
	rc += *bytes;
	return(rc);
}

aha_init()
{
	unsigned char ad[3];
	int i;

	/* reset board */

	outb(AHA_CTRL_STAT_PORT, AHA_HRST|AHA_SRST);

	for (i=0; i < AHA_CMD_TIMEOUT; i++)
		if (inb(AHA_CTRL_STAT_PORT) == (AHA_INIT|AHA_IDLE))
			break;

	if (i >= AHA_CMD_TIMEOUT) {
		if (aha_debug)
			printf("aha_init: No answer from adaptec board\n");
		return(ENXIO);
	}

	/* Initialize mail box */

	lto3b(KVTOPHYS(&aha_mbx), ad);

	aha_cmd(4, 0, 0, AHA_MBX_INIT, AHA_MBX_SIZE, ad[0], ad[1], ad[2]);

	/* setup dma for channel 5 */

	outb(0xd6, 0xc1);
	outb(0xd4, 0x01);

	for (i=0; i < AHA_MBX_SIZE; i++) {
		aha_ccb[i].next = aha_ccb_free;
		aha_ccb_free = &aha_ccb[i];
		aha_ccb_free->mbx = &aha_mbx.mbo[i];
		lto3b(KVTOPHYS(aha_ccb_free), aha_mbx.mbo[i].ccb_addr);
#ifdef	CBUS
		/* allocate cbus  windows */
		aha_ccb_free->window = cbus_alloc_win(AHA_DMA_PAGES);
#endif	CBUS
#ifndef	MACH_KERNEL
		ahabuf[i].b_forw =  ahabuf_free;
		ahabuf_free = &ahabuf[i];
#endif	MACH_KERNEL
	}

	aha_initialized++;
	return(0);
}

ahaopen(dev)
{
	int errcode = 0;
	int unit, part;
	struct disk_parms disk_parms;

	unit = UNIT(dev);

	if (!aha_initialized)
		aha_init();
	if (!aha_initialized)
		return(ENXIO);
	if (aha_req_sense(unit, 0) != 0) {
		errcode = ENXIO;
		goto open1;
	}
	aha_start_unit(unit);
	aha_get_parms(unit, &disk_parms, 0);
	if (aha_sec_sz[unit] != SECSIZE) {
		printf("aha: Dont know how to deal with %d bytes logical blocks for SCSI unit %d\n", aha_sec_sz[unit], unit);
		Debugger();
		errcode = ENXIO;
		goto open1;
	}

	ahagetvtoc(unit);

	part = PARTITION(dev);

	if ( part >= V_NUMPAR  || unit >= NTARGET ) {
		errcode = ENXIO;
		goto open1;
	}

	if ( aha_partition_struct[unit][part].p_flag & V_VALID )
		aha_partition_struct[unit][part].p_flag |= V_OPEN;
	else	errcode = ENXIO;

open1:
	return(errcode);
}

#ifdef	MACH_KERNEL
/*
 *	No need to limit IO size to 4096 bytes.
 */
int aharead(dev, ior) 
	dev_t	dev;
	io_req_t ior;
{
	return (block_io(ahastrategy, minphys, ior));
}

int ahawrite(dev, ior)
	dev_t	dev;
	io_req_t ior;
{
	return (block_io(ahastrategy, minphys, ior));
}

#else	MACH_KERNEL
struct buf *
aha_get_buf() {
	struct buf *rc;

	while (!(rc = ahabuf_free))
		sleep((caddr_t)&ahabuf_free, PRIBIO+1);
	ahabuf_free = ahabuf_free->b_forw;
	return(rc);
}

aha_free_buf(bp)
struct buf *bp;
{
	if (!ahabuf_free)
		wakeup((caddr_t)&ahabuf_free);
	bp->b_forw = ahabuf_free;
	ahabuf_free = bp;
}
	

aharead(dev,uio)
register short  dev;
struct uio 	*uio;
{
	struct buf *bp = aha_get_buf();
	int rc;
	rc = physio(ahastrategy, bp, dev, B_READ, ahaminphys, uio);
	aha_free_buf(bp);
	return(rc);
}

ahawrite(dev,uio)
dev_t	 	dev;
struct uio	*uio;
{
	struct buf *bp = aha_get_buf();
	int rc;

	rc = physio(ahastrategy, bp, dev, B_WRITE, ahaminphys, uio);
	aha_free_buf(bp);
	return(rc);
}

#endif	MACH_KERNEL

#ifdef	MACH_KERNEL
min(x, y)
{
	return (x < y ? x : y);
}
#endif	MACH_KERNEL

/* Trim buffer length if buffer-size is bigger than page size */
ahaminphys(bp)
struct buf	*bp;
{
#if	1
	if (bp->b_bcount > PAGESIZ)
		bp->b_bcount = PAGESIZ;
#else	1
	if ((unsigned)bp->b_un.b_addr & (PAGESIZ-1))
		bp->b_bcount = min(bp->b_bcount, (AHA_DMA_PAGES-1)*PAGESIZ);
	else
		bp->b_bcount = min(bp->b_bcount, AHA_DMA_PAGES*PAGESIZ);
#endif	1
}

ahastrategy(bp)
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

	partition_p= &(aha_partition_struct[unit][partition]);

#ifdef	MACH_KERNEL
	if ( !(partition_p->p_flag & V_VALID) ||
	     !(bp->b_flags & B_READ) &&
	     (partition_p->p_flag & V_RONLY)
	   )
#else	MACH_KERNEL
	if ( !(partition_p->p_flag & V_VALID) ||
	     !(bp->b_flags & B_READ) &&
	     (partition_p->p_flag & V_RONLY) &&
	     (u.u_uid != 0))
#endif	MACH_KERNEL
	{
		bp->b_error = ENXIO;
		goto bad;
	}

	/* if request is off the end or trying to write last block on out */

	if (bp->b_flags & B_MD1) {
		if (bp->b_blkno > aha_partition_struct[unit][PART_DISK].p_start +
				  aha_partition_struct[unit][PART_DISK].p_size - 1) {
			bp->b_error = ENXIO;
			goto bad;
		}
	} else {
		if ( (bp->b_blkno >  partition_p->p_size) ||
		     (bp->b_blkno == partition_p->p_size & !(bp->b_flags & B_READ))) {
			bp->b_error = ENXIO;
			goto bad;
		}
		if (bp->b_blkno == partition_p->p_size) {
		/* indicate (read) EOF by setting b_resid to b_bcount on last block */ 
			bp->b_resid = bp->b_bcount;
			goto done;
		}
	}

	opri = spl5();
	dp = &ahaunit[unit];

#ifdef	MACH_KERNEL
	simple_lock(&aha_queue_lock[unit]);
#endif	MACH_KERNEL
	disksort(dp, bp);
#ifdef	MACH_KERNEL
	simple_unlock(&aha_queue_lock[unit]);
#endif	MACH_KERNEL

	ahastart();

	splx(opri);
	return;
bad:
	bp->b_flags |= B_ERROR;
done:
	iodone(bp);
	return;
}

/* ahastart() is called at spl5 */
ahastart()
{
	partition_t	*partition_p;
	int drivecount;
	register struct buf *bp = 0;
	register struct buf *dp;
	struct aha_ccb *ccb;
	int blkno, nblk;
	register pg_off, pg_cnt, i;
	int unit;

#ifdef	MACH_KERNEL
#if	NCPUS > 1 && defined(CBUS)
	int is_locked = cpu_number();
#endif	NCPUS > 1 && defined(CBUS)
#endif	MACH_KERNEL
	if (!(ccb = aha_get_ccb(AHA_NOSLEEP)))
		return;

	for (drivecount = 0, unit = curtarget; drivecount < NTARGET; drivecount++) {
		dp = &ahaunit[unit];
		if (dp->b_actf) {
#ifdef	MACH_KERNEL
			simple_lock(&aha_queue_lock[unit]);
#endif	MACH_KERNEL
			if ((bp = dp->b_actf) != NULL)
				break;
#ifdef	MACH_KERNEL
			simple_unlock(&aha_queue_lock[unit]);
#endif	MACH_KERNEL
		}
		unit = (unit + 1) % NTARGET;
	}
	if (!bp) {
		aha_free_ccb(ccb, AHA_NOSTART);
		return;
	}

	dp->b_actf = bp->av_forw;
#ifdef	MACH_KERNEL
	simple_unlock(&aha_queue_lock[unit]);
#endif	MACH_KERNEL
	ccb->bp = bp;

	ccb->lun = 0;
	ccb->data_out = 0;
	ccb->data_in = 0;
	ccb->target = unit;
	if (bp->b_flags & B_READ)
		ccb->scsi_cmd.opcode = READ_COMMAND;
	else
		ccb->scsi_cmd.opcode = WRITE_COMMAND;
	
	ccb->scsi_cmd_length = sizeof(struct scsi_rw);
	ccb->req_sense_length = sizeof(ccb->scsi_cmd.sense);

	nblk = (bp->b_bcount + 511) >> 9;

	partition_p = &aha_partition_struct[UNIT(bp->b_dev)][PARTITION(bp->b_dev)];
	
	/* see V_RDABS and V_WRABS in ahaioctl() */
	if (bp->b_flags & B_MD1) {
		int end = aha_partition_struct[unit][PART_DISK].p_start +
				  aha_partition_struct[unit][PART_DISK].p_size - 1;

		blkno = bp->b_blkno;
		if ((bp->b_blkno + nblk ) > end)
			nblk = end - bp->b_blkno + 1;
	} else {
 		blkno = partition_p->p_start + bp->b_blkno;
		if ((bp->b_blkno + nblk ) > partition_p->p_size)
			nblk = partition_p->p_size - bp->b_blkno + 1;
	}

	ccb->scsi_cmd.cmd.rw.addr_2 = (blkno & 0xff0000) >> 16;
	ccb->scsi_cmd.cmd.rw.addr_1 = (blkno & 0xff00) >> 8;
	ccb->scsi_cmd.cmd.rw.addr_0 = blkno & 0xff;
	ccb->scsi_cmd.cmd.rw.length = nblk;
	lto3b(0, ccb->link_addr );
	pg_cnt = ((unsigned)(bp->b_un.b_addr + (nblk << 9) - 1) >> I386_PGSHIFT )
		  - ((unsigned)bp->b_un.b_addr >> I386_PGSHIFT) + 1;
	if (pg_cnt <= 0 || pg_cnt > AHA_DMA_PAGES) {
		printf("ahastart: bad io length: %d\n", pg_cnt);
		panic("");
	}
	pg_off = (int)bp->b_un.b_addr & (PAGESIZ-1);
#if	defined(MACH_KERNEL) && defined(CBUS) && NCPUS > 1
	io_lock();
#endif	defined(MACH_KERNEL) && defined(CBUS) && NCPUS > 1
#ifdef	CBUS
	lto3b(bp->b_bcount, ccb->data_length );
	lto3b(KVTOPHYS(cbus_get_win_add(ccb->window)+pg_off), ccb->data_addr);
	for (i=0; i < pg_cnt; i++)
		cbus_set_win(ccb->window+i, kvtophys(bp->b_un.b_addr+(i*PAGESIZ)));
	ccb->opcode = AHA_INITIATOR_CCB;
#else	CBUS
	if (pg_cnt == 1) {
		lto3b(bp->b_bcount, ccb->data_length );
		lto3b(KVTOPHYS(bp->b_un.b_addr), ccb->data_addr );
		ccb->opcode = AHA_INITIATOR_CCB;
	} else {
		register resid = bp->b_bcount;
		register caddr_t addr = bp->b_un.b_addr;

		lto3b(KVTOPHYS(ccb->scat_gath), ccb->data_addr);
		lto3b(sizeof(struct aha_scat_gath)*pg_cnt, ccb->data_length);
		for (i=0; i<pg_cnt; i++) {
			int count = min(resid, PAGESIZ-pg_off);
			lto3b(KVTOPHYS(addr), ccb->scat_gath[i].seg_addr);	    
			lto3b(count, ccb->scat_gath[i].seg_len);
			pg_off = 0;
			resid -= count;
			addr += count;
		}
		ccb->opcode = AHA_INIT_SCAT_GATH_CCB;
	}
#endif	CBUS
	aha_startmbx(ccb->mbx);
#if	defined(MACH_KERNEL) && defined(CBUS) && NCPUS > 1
	if (is_locked)
		io_unlock();
#endif	defined(MACH_KERNEL) && defined(CBUS) && NCPUS > 1
}

#ifndef	MACH_KERNEL
ahaioctl(dev, cmd, arg, mode)
dev_t dev;
int cmd;
caddr_t arg;
{
	struct aha_cmd_buf *args;
	struct scsi_cmd *scsi_cmd;
	register i,j;
	unsigned int opri;
	int errcode = 0;
	unsigned char unit, part;
	struct absio *absio_kernel;
	unsigned snum;
	int xcount;
	union vfy_io *vfy_io_kernel;
	struct buf *aha_bp1, *aha_bp2;

	unit = UNIT(dev);
	part = PARTITION(dev);

	switch(cmd) {
	case A_CMD:
		args = (struct aha_cmd_buf *) arg;
		aha_cmd(args->byte[0], args->byte[1], args->byte, args->byte[3], args->byte[4], args->byte[5], args->byte[6], args->byte[7]);
		break;
	case A_SCSI: 
		errcode = aha_scsi_start(UNIT(dev), arg, sizeof(ccb_data), ccb_data, 0);
		break;
	case V_RDABS:
		/* V_RDABS is relative to head 0, sector 0, cylinder 0 */
		if (u.u_uid != 0) {
			errcode = ENXIO;
			break;
		}
		aha_bp1 = geteblk(SECSIZE);
		absio_kernel = (struct absio *)arg;
		aha_bp1->b_flags = B_READ | B_MD1;	/* MD1 is be absolute */
		aha_bp1->b_blkno = absio_kernel->abs_sec;
		aha_bp1->b_dev = WHOLE_DISK(unit);	/* 4 lsb's = 0 = partit 0 = RDABS */	
		aha_bp1->b_bcount = SECSIZE;
		/* no badblock_mapping(), no offset by partition_p->p_start */
		ahastrategy(aha_bp1);
		biowait(aha_bp1);
		aha_bp1->b_flags &= ~B_MD1;
		if (aha_bp1->b_flags & B_ERROR) {
			printf("aha: read failure on ioctl\n");
			errcode = ENXIO;
			brelse(aha_bp1);
			break;
		}
		if ( copyout( (caddr_t)paddr(aha_bp1), absio_kernel->abs_buf, 
				SECSIZE) !=0 ) {
			errcode = ENXIO;
		}
		brelse(aha_bp1);
		break;

	case V_WRABS:

		/* V_WRABS is relative to head 0, sector 0, cylinder 0 */
		if (u.u_uid != 0) {
			errcode = ENXIO;
			break;
		}
		aha_bp1 = geteblk(SECSIZE);
		absio_kernel = (struct absio *)arg;
		if ( copyin( absio_kernel->abs_buf, (caddr_t)paddr(aha_bp1), 
				SECSIZE) !=0 ) {
			/* u.u_error =ENXIO; */
			errcode = ENXIO;
			brelse(aha_bp1);
			break;
		}
		aha_bp1->b_flags = B_WRITE | B_MD1;	/* MD1 is be absolute */
		aha_bp1->b_blkno = absio_kernel->abs_sec;
		aha_bp1->b_dev = WHOLE_DISK(unit);	/* 4 lsb's = 0 = partit 0 = RDABS */	
		aha_bp1->b_bcount = SECSIZE;
		/* no badblock_mapping(), no offset by partition_p->p_start */
		ahastrategy(aha_bp1);
		biowait(aha_bp1);
		aha_bp1->b_flags &= ~B_MD1;
		if (aha_bp1->b_flags & B_ERROR) {
			printf("aha: write failure on ioctl\n");
			/* u.u_error =ENXIO; */
			errcode = ENXIO;
		}
		brelse(aha_bp1);
		break;

	case V_REMOUNT:
		ahagetvtoc(unit);	
		break;

	/*
	 *	This part has to be fixed, to read the parameters from
	 *	the controller, need mor time.
	 */

	case V_GETPARMS:
		{
		struct disk_parms *disk_parms = (struct disk_parms *)arg;
		
		aha_get_parms(unit, disk_parms, 0);


		disk_parms->dp_type = DPT_WINI;
		disk_parms->dp_dosheads = disk_parms->dp_heads;
		disk_parms->dp_doscyls = disk_parms->dp_cyls;
		disk_parms->dp_dossectors = disk_parms->dp_sectors;
		disk_parms->dp_secsiz = disk_parms->dp_secsiz;
		disk_parms->dp_ptag = aha_partition_struct[unit][part].p_tag;
		disk_parms->dp_pflag = aha_partition_struct[unit][part].p_flag;
		disk_parms->dp_pstartsec = aha_partition_struct[unit][part].p_start;
		disk_parms->dp_pnumsec = aha_partition_struct[unit][part].p_size;
		break;

	case V_VERIFY:

		if (u.u_uid != 0) {
			errcode = ENXIO;
			break;
		}

		aha_bp1 = geteblk(PAGESIZ);
		vfy_io_kernel = (union vfy_io *)arg;
		aha_bp1->b_flags = B_READ;
		aha_bp1->b_blkno = vfy_io_kernel->vfy_in.abs_sec;
		aha_bp1->b_dev = WHOLE_DISK(unit);	/* 4 lsb's = 0 = partit 0 = RDABS */	
		xcount = vfy_io_kernel->vfy_in.num_sec;
		vfy_io_kernel->vfy_out.err_code = 0;
		snum = PAGESIZ >> 9;
		while (xcount > 0) {
			i = (xcount > snum) ? snum : xcount;
			aha_bp1->b_bcount = i << 9;
			aha_bp1->b_flags |= B_MD1;
			ahastrategy(aha_bp1);
			biowait(aha_bp1);
			aha_bp1->b_flags &= ~B_MD1;
			if (aha_bp1->b_flags & B_ERROR) {
				vfy_io_kernel->vfy_out.err_code = BAD_BLK;
				break;
			}
			xcount -= i;
			aha_bp1->b_blkno += i;
			aha_bp1->b_flags &= ~B_DONE;
		}
		brelse(aha_bp1);
		break;
		}
	}
	return(errcode);
}
#endif	MACH_KERNEL

ahagetvtoc(unit)
unsigned char	unit;
{
	unsigned char *c_p;
	unsigned int n, m;
	char *pt1, *pt2;
	struct boot_record *boot_record_p;
	struct evtoc *evp;
	struct buf *aha_bp1, *aha_bp2;

	aha_bp1= geteblk(SECSIZE);		/* for evtoc */
	aha_bp2 = geteblk(SECSIZE);		/* for alt_info */

	/* make partition 0 the whole disk in case of failure
  	   then get pdinfo 
	*/
	aha_partition_struct[unit][PART_DISK].p_tag = V_BACKUP;
	aha_partition_struct[unit][PART_DISK].p_flag = V_OPEN|V_UNMNT|V_VALID;
	aha_partition_struct[unit][PART_DISK].p_start = 0; 
	aha_partition_struct[unit][PART_DISK].p_size = aha_size(unit, 0);

	/* get active partition */
	aha_bp1->b_flags = B_READ | B_MD1;
	aha_bp1->b_blkno = 0;
	aha_bp1->b_dev = WHOLE_DISK(unit);		/* partition is bottom 4 bits */
	aha_bp1->b_bcount = SECSIZE;
	ahastrategy(aha_bp1);
	biowait(aha_bp1);
	aha_bp1->b_flags &= ~B_MD1;
	if (aha_bp1->b_flags & B_ERROR) {
		printf("aha: can not read sector 0 on drive %d, the boot record partition (see AT Tech. Ref.)\n", unit);
		return;
	}
	c_p = (unsigned char *)(paddr(aha_bp1)) + 511;
	if ( *c_p != BOOTRECORDSIGNATURE) {
		printf("aha: sector 0 signature bad, can not read active partition on drive %d\n", unit);
		return;	
	}
	c_p = (unsigned char *)(paddr(aha_bp1)) + 446;
	boot_record_p = (struct boot_record *)(c_p);
	for (n=0; n<4; n++, boot_record_p++)
		if (boot_record_p->boot_ind == 0x80) break;

	if (boot_record_p->boot_ind != 0x80) {
		printf("aha: no active partition on drive %d\n", unit);
		return;
	}
	aha_start_of_unix[unit] = boot_record_p->rel_sect;	
	
	/* set correct partition information */

	aha_partition_struct[unit][PART_DISK].p_start = boot_record_p->rel_sect; 
	aha_partition_struct[unit][PART_DISK].p_size = aha_size(unit, 0) -
		   aha_start_of_unix[unit];

	/* get evtoc out of active unix partition */
	aha_bp1->b_flags = B_READ;
	aha_bp1->b_blkno = PDLOCATION;
	aha_bp1->b_dev = WHOLE_DISK(unit);		/* partition is bottom 4 bits */
	aha_bp1->b_bcount = SECSIZE;
	ahastrategy(aha_bp1);
	biowait(aha_bp1);
	if (aha_bp1->b_flags & B_ERROR) {
		printf("aha: can not read evtoc on drive %d\n", unit);
		return;
	}
	evp = (struct evtoc *)aha_bp1->b_un.b_addr;

	if (evp->sanity != VTOC_SANE) {
		printf("aha: evtoc invalid on drive %d\n",unit);
		return;
	}
		
	/* copy info on all valid partition, zero the others */
	for (n = 0; n < evp->nparts; n++) {
		if (n == PART_DISK)
			continue;
		/* this is a STRUCTURE copy */
		aha_partition_struct[unit][n] = evp->part[n];
	}
	for ( ; n < V_NUMPAR; n++) {
		if (n == PART_DISK)
			continue;
		aha_partition_struct[unit][n].p_flag = 0;
		aha_partition_struct[unit][n].p_size = 0;
	}	
	/* leave partition 0 "open" for raw I/O */
	aha_partition_struct[unit][PART_DISK].p_flag |= V_OPEN;

	/* get alternate sectors out of active unix partition */
	pt1 = (char *)&aha_alt_info[unit];
	for (n = 0; n < 4; n++) {
		aha_bp2->b_flags = B_READ;
		aha_bp2->b_blkno = evp->alt_ptr/SECSIZE + n;
		aha_bp2->b_dev = WHOLE_DISK(unit);	/* partition is bottom 4 bits */
		aha_bp2->b_bcount = SECSIZE;
		ahastrategy(aha_bp2);
		biowait(aha_bp2);
		if (aha_bp2->b_flags & B_ERROR) {
			printf("aha: can not read alternate sectors on drive %d\n", unit);
			return;
		}
		/* since struct altinfo is split over 4 bufs, can't do 
		   struct copy */
		pt2 = (char *)aha_bp2->b_un.b_addr;
		for (m = 0; m < SECSIZE; m++, pt1++, pt2++)
			*pt1 = *pt2; 
	}

	if (aha_alt_info[unit].alt_sanity != ALT_SANITY) {
		printf("aha: alternate sectors corrupted on drive %d\n", unit);
		return;
	}

	if (aha_bp1 != NULL)
		brelse(aha_bp1);
	if (aha_bp2 != NULL)
		brelse(aha_bp2);
}

aha_size(target, flags)
{
	struct scsi_read_cap_data rdcap;
	struct scsi_cmd scsi_cmd;
	int size;

	bzero(&scsi_cmd, sizeof(scsi_cmd));
	scsi_cmd.opcode = READ_CAPACITY;

	if (aha_scsi_start(target, &scsi_cmd, sizeof(rdcap), &rdcap, flags) != 0) {
		printf("could not get size of target %d\n", target);
		return(0);
	} else {
		size = rdcap.addr_0 + 1 ;
		size += rdcap.addr_1 << 8;
		size += rdcap.addr_2 << 16;
		size += rdcap.addr_3 << 24;
	}
	return(size);
}
	
aha_req_sense(target, flags)
{
	char out_buf[18];
	struct scsi_cmd scsi_cmd;

	bzero(&scsi_cmd, sizeof(scsi_cmd));
	scsi_cmd.opcode = REQUEST_SENSE;
	scsi_cmd.cmd.sense.length = 18;

	if (aha_scsi_start(target, &scsi_cmd, 18, out_buf, flags) != 0) {
		return(ENXIO);
	} else 
		return(0);
}

aha_start_unit(target)
{
	struct scsi_cmd scsi_cmd;

	bzero(&scsi_cmd, sizeof(scsi_cmd));
	scsi_cmd.opcode = START_STOP;
	scsi_cmd.cmd.start_stop.start = 1;

	if (aha_scsi_start(target, &scsi_cmd, sizeof(ccb_data), ccb_data, 0) != 0) {
		return(ENXIO);
	} else 
		return(0);
}

aha_scsi_start(target, scsi_cmd, scsi_dat_sz, scsi_dat, flags)
struct scsi_cmd *scsi_cmd;
char *scsi_dat;
{
	struct aha_ccb *ccb;
	int i;
	int rc = 0;

	if (!(ccb = aha_get_ccb(flags)))
		panic("aha: aha_scsi_start with nosleep fails");

	if (ccb->mbx->cmd != AHA_MBO_FREE)
		printf("MBO not free\n");

	ccb->bp = 0;
	ccb->opcode = AHA_INITIATOR_CCB;
	ccb->target = target;
	ccb->data_out = 0;
	ccb->data_in = 0;
	ccb->lun = 0;
	switch(scsi_cmd->opcode) {
	case TEST_UNIT_READY:
		ccb->scsi_cmd_length = sizeof(struct scsi_test_unit_ready);
		break;
	case READ_COMMAND:
	case WRITE_COMMAND:
		ccb->scsi_cmd_length = sizeof(struct scsi_rw);
		break;
	case REQUEST_SENSE:
	case MODE_SENSE:
		ccb->scsi_cmd_length = sizeof(struct scsi_sense);
		break;
	case READ_CAPACITY:
		ccb->scsi_cmd_length = sizeof(struct scsi_read_capacity);
		break;
	case START_STOP:
		ccb->scsi_cmd_length = sizeof(struct scsi_start_stop);
		break;
	}
	ccb->req_sense_length = sizeof(ccb->scsi_cmd.sense);
	lto3b(scsi_dat_sz, ccb->data_length );
#if	defined(MACH_KERNEL) && defined(CBUS) && NCPUS > 1
	io_lock();
#endif	defined(MACH_KERNEL) && defined(CBUS) && NCPUS > 1
#ifdef	CBUS
	cbus_set_win(ccb->window, kvtophys(scsi_dat));
	cbus_set_win(ccb->window+1, kvtophys(((int)scsi_dat+PAGESIZ)));
	lto3b(KVTOPHYS(cbus_get_win_add(ccb->window)+((int)scsi_dat&(PAGESIZ-1))), ccb->data_addr);
#else	CBUS
	lto3b(KVTOPHYS(scsi_dat), ccb->data_addr );
#endif	CBUS
	lto3b(0, ccb->link_addr );
	bcopy(scsi_cmd, &ccb->scsi_cmd, ccb->scsi_cmd_length);
	aha_startmbx(ccb->mbx);
#if	defined(MACH_KERNEL) && defined(CBUS) && NCPUS > 1
	io_unlock();
#endif	defined(MACH_KERNEL) && defined(CBUS) && NCPUS > 1
	if (flags & AHA_NOSLEEP) {
		int done = 0;
		while(!done) for (i=0; (!done) && i<AHA_MBX_SIZE; i++)
			if (aha_mbx.mbi[i].stat != AHA_MBI_FREE &&
			  PHYSTOKV(_3btol(aha_mbx.mbi[i].ccb_addr)) == (int)ccb) {
				aha_mbx.mbi[i].stat = AHA_MBI_FREE;
				done++;
				ahaintr();
			}
	} else
		sleep(ccb, PWAIT); 
	if (aha_debug) {
		if (ccb->host_stat != AHA_OK || ccb->target_stat != SCSI_OK)
			printf("host stat: %x, target_stat %x\n",
				ccb->host_stat, ccb->target_stat);
		if (ccb->target_stat == SCSI_CHECK)
			printf("sense key %x\n",
				((struct scsi_data *) &ccb->scsi_cmd.cmd.test_unit_ready.sense[0])->data.extended_sense.sense_key);
	}
	rc = (ccb->host_stat << 8) | ccb->target_stat;
	aha_free_ccb(ccb, flags);
	return(rc);
}

#define b2tol(a)	(((unsigned)(a/**/_1) << 8) + (unsigned)a/**/_0 )

aha_get_parms(unit, disk_parms, flags)
struct disk_parms *disk_parms;
{
	struct scsi_cmd scsi_cmd;
	struct scsi_mode_sense scsi_sense;
	int sectors;

	bzero(&scsi_cmd, sizeof(scsi_cmd));
	scsi_cmd.opcode = MODE_SENSE;
	scsi_cmd.cmd.sense.page_code = 3;
	scsi_cmd.cmd.sense.length = 0x24;
	if (aha_scsi_start(unit, &scsi_cmd, 0x24, &scsi_sense, flags) != 0) {
		printf("could not mode sense for target %d\n", unit);
		return(ENXIO);
	} 
	if (aha_debug) {
		printf("unit %d: %d trk/zone, %d alt_sec/zone, %d alt_trk/zone, %d alt_trk/lun\n",
			unit,
			b2tol(scsi_sense.params.pgcode_3.trk_z),
			b2tol(scsi_sense.params.pgcode_3.alt_sec),
			b2tol(scsi_sense.params.pgcode_3.alt_trk_z),
			b2tol(scsi_sense.params.pgcode_3.alt_trk_v));
		printf("         %d sec/trk, %d bytes/sec, %d interleave, %d %d bytes/log_blk\n",
			b2tol(scsi_sense.params.pgcode_3.ph_sec_t),
			b2tol(scsi_sense.params.pgcode_3.bytes_s),
			b2tol(scsi_sense.params.pgcode_3.interleave),
			aha_size(unit, flags),
			_3btol(&scsi_sense.blksz_2));
	}


	bzero(&scsi_cmd, sizeof(scsi_cmd));
	scsi_cmd.opcode = MODE_SENSE;
	scsi_cmd.cmd.sense.page_code = 4;
	scsi_cmd.cmd.sense.length = 0x20;
	if (aha_scsi_start(unit, &scsi_cmd, 0x20, &scsi_sense, flags) != 0) {
		printf("could not mode sense for target %d\n", unit);
		return(ENXIO);
	} 

	if (aha_debug)
		printf("         %d cyls, %d heads, %d precomp, %d red_write, %d land_zone\n",
			_3btol(&scsi_sense.params.pgcode_4.ncyl_2),
			scsi_sense.params.pgcode_4.nheads,
			b2tol(scsi_sense.params.pgcode_4.st_cyl_wp),
			b2tol(scsi_sense.params.pgcode_4.st_cyl_rwc),
			b2tol(scsi_sense.params.pgcode_4.land_zone));

	disk_parms->dp_heads = scsi_sense.params.pgcode_4.nheads;
	disk_parms->dp_cyls = _3btol(&scsi_sense.params.pgcode_4.ncyl_2);

	aha_sec_sz[unit] = _3btol(&scsi_sense.blksz_2);	/* logical block size */

	/* give a number of sectors so that sec * trks * cyls is <= disk_size */

	sectors = aha_size(unit, flags) * aha_sec_sz[unit];
	sectors /= SECSIZE;
	sectors /= disk_parms->dp_cyls;
	sectors /= disk_parms->dp_heads;
	disk_parms->dp_sectors = sectors;
	disk_parms->dp_secsiz = SECSIZE;

}

ahaclose(dev)
{
	unsigned char unit, part;
	unsigned int old_priority;

	unit = UNIT(dev);
	part = PARTITION(dev);

	aha_partition_struct[unit][part].p_flag &= ~V_OPEN;
}

