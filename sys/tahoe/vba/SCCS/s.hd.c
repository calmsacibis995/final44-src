h55182
s 00020/00020/00884
d D 7.12 90/12/16 16:46:59 bostic 12 11
c kernel reorg
e
s 00001/00011/00903
d D 7.11 90/06/28 22:27:10 bostic 11 10
c new copyright notice
e
s 00005/00001/00909
d D 7.10 90/04/03 22:20:42 karels 10 9
c new tsleep; unwind when signal interrupts; close routines must return values
e
s 00000/00001/00910
d D 7.9 90/02/17 10:42:26 mckusick 9 8
c get rid of dir.h
e
s 00001/00003/00910
d D 7.8 89/08/23 18:01:29 bostic 8 7
c be silent if controller absent
e
s 00002/00001/00911
d D 7.7 89/08/23 17:24:20 bostic 7 6
c type mistake; include standard address array
e
s 00001/00001/00911
d D 7.6 89/08/10 10:23:11 bostic 6 5
c lint; pass structure pointer, not structure itself
e
s 00002/00002/00910
d D 7.5 89/05/29 13:45:03 mckusick 5 4
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00071/00087/00841
d D 7.4 89/05/01 10:04:22 bostic 4 3
c fix cylinder calculation; remove error codes, add disk labels
e
s 00783/01298/00145
d D 7.3 89/03/07 14:59:37 bostic 3 2
c first working version
e
s 00027/00084/01416
d D 7.2 88/01/06 18:21:23 bostic 2 1
c swapped mtpr args, started reformatting
e
s 01500/00000/00000
d D 7.1 87/12/28 14:01:57 bostic 1 0
c original Harris source code
e
u
U
t
T
I 1
/*
D 3
 *  Driver for HCX Disk Controller (HDC)
E 3
I 3
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 3
 *
I 3
 * This code is derived from software contributed to Berkeley by
 * Harris Corp.
 *
D 11
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
D 4
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 4
 *
E 3
 *	%W% (Berkeley) %G%
 */

D 3
#include <sys/types.h>
#include <ctype.h>
#include "../sys/param.h"
#include "../sys/buf.h"
#include "../sys/conf.h"
#include "../sys/dir.h"
#include "../sys/dk.h"
#include "../ml/mtpr.h"
#include "../sys/systm.h"
#include "../sys/vbavar.h"
#include "../sys/user.h"
#include "../sys/vmmac.h"
#include "../sys/uio.h"
#include "../sys/elog.h"
#include "../sys/iobuf.h"
#include "../sys/kernel.h"
#include "../sys/reboot.h"
#include "../sys/ioctl.h"
#define DSKGENDATA
#include "../sys/dsk.h"
#undef DSKGENDATA
#include "../sys/dskio.h"
#include "../sys/hdc.h"
#include "../sys/proc.h"
E 3
I 3
#include "hd.h"
E 3

I 3
#if NHD > 0
D 12
#include "param.h"
#include "buf.h"
#include "conf.h"
D 9
#include "dir.h"
E 9
#include "dkstat.h"
#include "disklabel.h"
#include "file.h"
#include "systm.h"
#include "vmmac.h"
#include "time.h"
#include "proc.h"
#include "uio.h"
#include "syslog.h"
#include "kernel.h"
#include "ioctl.h"
#include "stat.h"
#include "errno.h"
E 12
I 12
#include "sys/param.h"
#include "sys/buf.h"
#include "sys/conf.h"
#include "sys/dkstat.h"
#include "sys/disklabel.h"
#include "sys/file.h"
#include "sys/systm.h"
#include "sys/vmmac.h"
#include "sys/time.h"
#include "sys/proc.h"
#include "sys/uio.h"
#include "sys/syslog.h"
#include "sys/kernel.h"
#include "sys/ioctl.h"
#include "sys/stat.h"
#include "sys/errno.h"
E 12

D 12
#include "../tahoe/cpu.h"
#include "../tahoe/mtpr.h"
E 12
I 12
#include "../include/cpu.h"
#include "../include/mtpr.h"
E 12

D 12
#include "../tahoevba/vbavar.h"
#include "../tahoevba/hdreg.h"
E 12
I 12
#include "../vba/vbavar.h"
#include "../vba/hdreg.h"
E 12

#define	b_cylin	b_resid

#define	hdunit(dev)		(minor(dev)>>3)
#define	hdpart(dev)		(minor(dev)&0x07)
#define	hdminor(unit, part)	(((unit)<<3)|(part))

struct vba_ctlr *hdcminfo[NHDC];
struct vba_device *hddinfo[NHD];
int hdcprobe(), hdslave(), hdattach(), hddgo(), hdstrategy();
I 7
long hdstd[] = { 0 };
E 7
struct vba_driver hdcdriver =
D 7
    { hdcprobe, hdslave, hdattach, hddgo, 0L, "hd", hddinfo, "hdc", hdcminfo };
E 7
I 7
    { hdcprobe, hdslave, hdattach, hddgo, hdstd, "hd", hddinfo, "hdc", hdcminfo };
E 7

E 3
/*
D 3
 * External data.
E 3
I 3
 * Per-controller state.
E 3
 */
I 3
struct hdcsoftc {
	u_short	hdc_flags;
#define	HDC_INIT	0x01	/* controller initialized */
#define	HDC_STARTED	0x02	/* start command issued */
#define	HDC_LOCKED	0x04	/* locked for direct controller access */
#define	HDC_WAIT	0x08	/* someone needs direct controller access */
	u_short	hdc_wticks;		/* timeout */
	struct master_mcb *hdc_mcbp;	/* address of controller mcb */
	struct registers *hdc_reg;	/* base address of i/o regs */
	struct vb_buf hdc_rbuf;		/* vba resources */
	struct master_mcb hdc_mcb;	/* controller mcb */
} hdcsoftc[NHDC];
E 3

D 3
extern unsigned int		blkacty;	/* for error logging      */
extern hdc_ctlr_type		hdc_ctlrs[];	/* hdc controller info    */
extern hdc_unit_type		hdc_units[];	/* hdc unit info          */
extern struct vba_ctlr		*hdminfo[];	/* vba controller info    */
extern struct vba_device	*vddinfo[];	/* vba device info        */
extern struct iotime		vdstat[];	/* for disk activity info */
extern struct iobuf		vdtab[];	/* for disk activity info */
extern int			maxfree;	/* no. of blocks for dump */
E 3
I 3
#define	HDCMAXTIME	20		/* max time for operation, sec. */
#define	HDCINTERRUPT	0xf0		/* interrupt vector */
E 3

/*
D 3
 * Procedure forward references.
E 3
I 3
 * Per-drive state; probably everything should be "hd_", not "dk_",
 * but it's not worth it, and dk is a better mnemonic for disk anyway.
E 3
 */
I 3
struct dksoftc {
#ifdef COMPAT_42
	u_short	dk_def_cyl;	/* definition track cylinder address */
#endif
	int	dk_state;	/* open fsm */
	u_short	dk_bshift;	/* shift for * (DEV_BSIZE / sectorsize) XXX */
	int	dk_wlabel;	/* if label sector is writeable */
	u_long	dk_copenpart;	/* character units open on this drive */
	u_long	dk_bopenpart;	/* block units open on this drive */
	u_long	dk_openpart;	/* all units open on this drive */
	int	dk_unit;	/* unit# */
	int	dk_ctlr;	/* controller# */
	int	dk_format;	/* if format program is using disk */
	struct buf dk_utab;		/* i/o queue header */
	struct disklabel dk_label;	/* disklabel for this disk */
	struct mcb dk_mcb;		/* disk mcb */
} dksoftc[NHD];
E 3

D 3
int  hdprobe();
int  hdslave();
int  hdstrategy();
int  hdattach();

E 3
/*
D 3
 * Driver structure.
E 3
I 3
 * Drive states.  Used during steps of open/initialization.
 * States < OPEN (> 0) are transient, during an open operation.
 * OPENRAW is used for unlabeled disks, to allow format operations.
E 3
 */
I 3
#define	CLOSED		0		/* disk is closed */
#define	WANTOPEN	1		/* open requested, not started */
#define	WANTOPENRAW	2		/* open requested, no label */
#define	RDLABEL		3		/* reading pack label */
#define	OPEN		4		/* intialized and ready */
#define	OPENRAW		5		/* open, no label */
E 3

D 3
struct  vba_driver hddriver = {
	hdprobe,		/* handler probe routine        */
	hdslave,		/* handler slave routine        */
	hdattach,		/* handler attach routine       */
	0,			/* handler go routine           */
	0,			/*                              */
	"dsk",			/* name of the device           */
	vddinfo,		/* table of unit info           */
	"HDC Controller #",	/* name of the controller       */
	hdminfo,		/* table of ctlr info           */
	HDC_MID,		/* controller's module id       */
	0			/* no exclusive use of bdp's    */
};
E 3
I 3
int hdcwstart, hdcwatch();
E 3

D 3
#ifdef HDCLOG
/*************************************************************************
*  Procedure:	hdlog
*
*  Description: logs mcb's, master mcb's, etc.
*
*  Returns:
**************************************************************************/

#define ENT_SIZE 16
#define ENT_COUNT 256
static int  hdclog_index = 0;
static unsigned int  hdclog[ ENT_SIZE * ENT_COUNT ];

hdlog(ptr,id)
register unsigned int   *ptr;
register unsigned int   id;
E 3
I 3
/* see if the controller is really there, if so, init it. */
/* ARGSUSED */
hdcprobe(reg, vm)
	caddr_t reg;
	/* register */ struct vba_ctlr *vm;
E 3
{
D 3
	int i;
E 3
I 3
	register int br, cvec;		/* must be r12, r11 */
	register struct hdcsoftc *hdc;
	static struct module_id id;
	struct pte *dummypte;
	caddr_t putl;
E 3

D 3
	hdclog[hdclog_index++] = id;
	hdclog[hdclog_index++] = time.tv_sec;
	hdclog[hdclog_index++] = time.tv_usec;
	for (i=3; i<ENT_SIZE; i++) {
		hdclog[hdclog_index++] = *ptr;
		ptr++;
E 3
I 3
	/* initialize the hdc controller structure. */
	hdc = &hdcsoftc[vm->um_ctlr];
	if (!vbmemalloc(1, reg, &dummypte, &putl)) {
		printf("hdc%d: vbmemalloc failed.\n", vm->um_ctlr);
		return(0);
E 3
	}
D 3
	if (hdclog_index >= ENT_SIZE * ENT_COUNT) hdclog_index=0;
}
#endif
E 3
I 3
	hdc->hdc_reg = (struct registers *)putl;
E 3

D 3
/*************************************************************************
*  Procedure:	hdattach
*
*  Description: "hdattach" does device-dependent initialization of
* 		hdc drives. It is called during the configuration phase
*               of a reboot for each disk device on an hdc controller.
*               Note that most things get initialized in "hdslave",
*               because "slave" initializes what it needs to determine
*               whether the drive is ready (which turns out to be a lot).
*
*  Returns:
**************************************************************************/

hdattach(vba_unit)

register struct vba_device *vba_unit;	/* Pointer to vba drive info
					 */
{
	register hdc_unit_type	*hu;	/* hdc unit info
					 */
	register int		unit;	/* drive's unit# (0-31)
					 */
	unit = vba_unit->ui_unit;
	hu = &hdc_units[ unit ];

E 3
	/*
D 3
	 * Initialize the hdc unit information structure.
	 * A lot of this is done in "hdslave".
E 3
I 3
	 * try and ping the MID register; side effect of wbadaddr is to read
	 * the module id; the controller is bad if it's not an hdc, the hdc's
	 * writeable control store is not loaded, or the hdc failed the
	 * functional integrity test;
E 3
	 */
I 3
	if (wbadaddr(&hdc->hdc_reg->module_id, 4,
D 8
	    vtoph((struct process *)NULL, &id))) {
		printf("hdc%d: can't access module register.\n", vm->um_ctlr);
E 8
I 8
	    vtoph((struct process *)NULL, &id)))
E 8
		return(0);
D 8
	}
E 8
	DELAY(10000);
	mtpr(PADC, 0);
	if (id.module_id != (u_char)HDC_MID) {
		printf("hdc%d: bad module id; id = %x.\n",
		    vm->um_ctlr, id.module_id);
		return(0);
	}
	if (id.code_rev == (u_char)0xff) {
		printf("hdc%d: micro-code not loaded.\n", vm->um_ctlr);
		return(0);
	}
	if (id.fit != (u_char)0xff) {
		printf("hdc%d: FIT test failed.\n", vm->um_ctlr);
		return(0);
	}
E 3

D 3
	hu->spc = hu->heads * hu->sectors;
E 3
I 3
	/* reset that pup; flag as inited */
	hdc->hdc_reg->soft_reset = 0;
	DELAY(1000000);
	hdc->hdc_flags |= HDC_INIT;
E 3

D 3
	/*
	 * bytes per second:
	 *      (number of sectors per track) * (bytes per sector) * rpm / 60
 	 */
E 3
I 3
	/* allocate page tables and i/o buffer. */
	if (!vbainit(&hdc->hdc_rbuf, MAXPHYS, VB_32BIT|VB_SCATTER)) {
		printf("hdc%d: vbainit failed\n", vm->um_ctlr);
		return (0);
	}
E 3

D 3
	dk_bps[unit] = hu->sectors * BPS * hu->rpm / 60;
E 3
I 3
	/* set pointer to master control block */
	hdc->hdc_mcbp =
	    (struct master_mcb *)vtoph((struct proc *)NULL, &hdc->hdc_mcb);

	br = 0x17, cvec = HDCINTERRUPT + vm->um_ctlr;		/* XXX */
	return(sizeof(struct registers));
E 3
}

D 3
/*************************************************************************
*  Procedure:	hddump
*
*  Description: Dump system memory to disk. The hdc controller is reset.
*               After this call, queued operations on this hdc are no
*               longer possible until the next reboot.
*
*  Returns:     ENXIO    the dump was truncated for some reason.
*               EIO      there were controller problems
*               0        normal
**************************************************************************/

int
hddump(dev)

int	dev;		/* the major/minor device number.
			 */
E 3
I 3
/* ARGSUSED */
hdslave(vi, vdaddr)
	struct vba_device *vi;
	struct vddevice *vdaddr;
E 3
{
D 3
	register hdc_unit_type	*hu;		/* hdc unit info            */
	register hdc_ctlr_type	*hc;		/* hdc controller info      */
	register mcb_type	*mcb;		/* hdc controller info      */
	register int		current_block;	/* next disk block to write */
	register int		block_count;	/* #blocks to dump total    */
	register int		blocks;		/* #blocks to dump at a time*/
	register int		mem_addr;	/* memory address to dump   */
	int			sector;		/* sector to write to       */
	int			par;		/* disk partition number    */
	int			parlen;		/* disk partition # blocks  */
	int			dump_short;	/* TRUE= dump was truncated */
	int			chn;		/* temporary data chain no. */
	int			bc;		/* temporary byte count     */
E 3
I 3
	register struct mcb *mcb;
	register struct disklabel *lp;
	register struct dksoftc *dk;
	static struct status status;
E 3

I 3
	dk = &dksoftc[vi->ui_unit];
	dk->dk_unit = vi->ui_unit;
	dk->dk_ctlr = vi->ui_ctlr;
E 3

D 3
	mem_addr = 0;
	dump_short = FALSE;
	par = HDC_PARTITION(dev);
	hu = &hdc_units[ HDC_UNIT(dev) ];
	hc = &hdc_ctlrs[hu->ctlr];
	mcb = &hu->phio_mcb;
	parlen = hu->partition[par].length;
	printf("\nhdc: resetting controller #%d.\n", hc->ctlr);
	HDC_REGISTER(soft_reset_reg) = 0;
	DELAY(1000000);
D 2
	mtpr(0,PADC);
E 2
I 2
	mtpr(PADC, 0);
E 2

	/*
	 * If the drive has not been initialized yet, abort the dump.
	 * Set dump limits. The dump must fit in the partition.
	 */

	if (hu->sectors <= 0 || hu->heads <= 0 || hu->cylinders <= 0 ) {
		printf("\nhdc: dump device is not initialized - no dump!\n");
		return EIO;
E 3
I 3
	mcb = &dk->dk_mcb;
	mcb->command = HCMD_STATUS;
	mcb->chain[0].wcount = sizeof(struct status) / sizeof(long);
	mcb->chain[0].memadr  = (u_long)vtoph((struct process *)0, &status);
	if (hdimcb(dk)) {
		printf(" (no status)\n");
		return(0);
E 3
	}
D 3
	block_count = dumpsize;
	if ((dumplo + block_count) > parlen) {
		block_count = parlen - dumplo;
		dumpsize = block_count;  /* let savecore know */
		printf("\nhdc: only dumping first %dmb of memory!\n",
		    block_count/1024);
		dump_short = TRUE;
	}
	current_block = hu->partition[par].start + dumplo;
E 3

	/*
D 3
	 * Dump memory to disk. For each disk transfer, fill in the
	 * mcb with information describing the transfer, then send
	 * the mcb to the hdc controller.
E 3
I 3
	 * Report the drive down if anything in the drive status looks bad.
	 * If the drive is offline and it is not on cylinder, then the drive
	 * is not there.  If there is a fault condition, the hdc will try to
	 * clear it when we read the disklabel information.
E 3
	 */
D 3

	while (block_count > 0) {
		blocks = MIN(block_count, HDC_DUMPSIZE);
		sector = HDC_SPB * current_block;
		mcb->command   = HCMD_WRITE;
		mcb->cyl = sector/hu->spc;
		mcb->head = (sector/hu->sectors) % hu->heads;
		mcb->sector = sector % hu->sectors;
	        chn = 0;
	        bc = blocks * DEV_BSIZE;
	        while (bc > 0) {
	        	mcb->chain[chn].ta  = mem_addr;
	        	mcb->chain[chn].lwc = (bc > HDC_MAXBC) ?
        			(LWC_DATA_CHAIN | (HDC_MAXBC/4)) : bc/4;
	        	mem_addr += ((bc > HDC_MAXBC) ? HDC_MAXBC : bc);
	        	chn++;
	        	bc -= HDC_MAXBC;
		}
		if (!hdimcb(hu,mcb))
			return EIO;
		block_count -= blocks;
		current_block += blocks;
E 3
I 3
	if (!(status.drs&DRS_ONLINE)) {
		if (status.drs&DRS_ON_CYLINDER)
			printf(" (not online)\n");
		return(0);
E 3
	}
D 3
	return (dump_short ? ENXIO : 0);
}

/*************************************************************************
*  Procedure:	hddumpmcb
*
*  Description: Dumps a single mcb to the console - up to the last
*               active data chain lword.
*
*  Returns:
**************************************************************************/

hddumpmcb(mcb)

register mcb_type *mcb; /* the mcb pointer
			 */
{
	unsigned int *ptr,i;

	printf("mcb: ");
	ptr = (unsigned int *) &mcb->forw_phaddr;
	for (i=0; i<6; i++)
		printf(" %x",ptr[i]);
	for (i=6; i<72; i+=2) {
		printf("  %x %x", ptr[i], ptr[i+1]);
		if ( !(ptr[i] & 0x80000000)) break;
	}
E 3
I 3
	if (status.drs&DRS_FAULT)
		printf(" (clearing fault)");
E 3
D 4
	printf("\n");
E 4
I 3

	lp = &dk->dk_label;
#ifdef RAW_SIZE
	lp->d_secsize = status.bytes_per_sec;
#else
	lp->d_secsize = 512;
#endif
	lp->d_nsectors = status.max_sector + 1;
	lp->d_ntracks = status.max_head + 1;
	lp->d_ncylinders = status.max_cyl + 1;
	lp->d_secpercyl = lp->d_ntracks * lp->d_nsectors;
	lp->d_npartitions = 1;
	lp->d_partitions[0].p_offset = 0;
	lp->d_partitions[0].p_size = LABELSECTOR + 1;
	lp->d_rpm = status.rpm;
	lp->d_typename[0] = 'h';
	lp->d_typename[1] = 'd';
	lp->d_typename[2] = '\0';
#ifdef COMPAT_42
	dk->dk_def_cyl = status.def_cyl;
#endif
	return(1);
E 3
}

D 3
/*************************************************************************
*  Procedure:	hddumpmmcb
*
*  Description: dumps the master mcb on the console up to the
*               last non-zero byte of the extended status.
*
*  Returns:
**************************************************************************/

hddumpmmcb(master)

register master_mcb_type *master; /* the master mcb pointer
				   */
E 3
I 3
hdattach(vi)
	register struct vba_device *vi;
E 3
{
D 3
	unsigned int *ptr,i,end;
E 3
I 3
	register struct dksoftc *dk;
	register struct disklabel *lp;
	register int unit;
E 3

D 3
	printf("mmcb:  ");
	ptr = (unsigned int *) master;
	for (i=0;i<8;i++)
		printf("%x ",ptr[i]);
	for (i=7+HDC_XSTAT_SIZE; i>7; i--) {
		end = i;
		if (ptr[i] != 0) break;
E 3
I 3
	unit = vi->ui_unit;
	if (hdinit(hdminor(unit, 0), 0)) {
		printf(": unknown drive type");
		return;
E 3
	}
D 3
	for (i=8;i<=end;i++)
		printf(" %x",ptr[i]);
	printf("\n");
};
E 3
I 3
	dk = &dksoftc[unit];
	lp = &dk->dk_label;
	hd_setsecsize(dk, lp);
	if (dk->dk_state == OPEN)
		printf(": %s <secsize %d, ntrak %d, ncyl %d, nsec %d>",
		    lp->d_typename, lp->d_secsize, lp->d_ntracks,
		    lp->d_ncylinders, lp->d_nsectors);
E 3

D 3
/*************************************************************************
*  Procedure:	hdimcb
*
*  Description: "hdc immediate mcb" sends an mcb to the hdc and returns
*               when the hdc has completed the operation (polled io).
*               "hdimcb" is called during system configuration or
*               when the system is being dumped after a fatal error.
*
*  Entry:       o  There is no active process.
*
*               o  "hdimcb" cannot be called from interrupt level.
*
*               o  There can be no queued operations pending; i.e.
*                  this routine assumes exclusive use of the hdc.
*                  Note: a soft reset will terminate queued operations.
*
*  Returns:     Returns FALSE if a controller error occurred.
**************************************************************************/
E 3
I 3
	/*
	 * (60 / rpm) / (sectors per track * (bytes per sector / 2))
	 */
	if (vi->ui_dk >= 0)
D 5
		dk_mspw[vi->ui_dk] = 120.0 /
		    (lp->d_rpm * lp->d_nsectors * lp->d_secsize);
E 5
I 5
		dk_wpms[vi->ui_dk] =
		    (lp->d_rpm * lp->d_nsectors * lp->d_secsize) / 120;
E 5
#ifdef notyet
	addswap(makedev(HDMAJOR, hdminor(unit, 0)), lp);
#endif
}
E 3

D 3
int
hdimcb(hu,mcb)

register hdc_unit_type	*hu;		/* unit information
					 */
register mcb_type	*mcb;		/* mcb to send to the hdc
					 */
E 3
I 3
hdopen(dev, flags, fmt)
	dev_t dev;
	int flags, fmt;
E 3
{
D 3
	register hdc_ctlr_type	 *hc;		/* controller information   */
	register master_mcb_type *master;	/* the hdc's master mcb     */
	register int		 timeout;	/* used to timeout the mcb  */
	register int		 ctlr;		/* controller number        */
	int	 i,ok;
	unsigned int *ptr;
E 3
I 3
	register struct disklabel *lp;
	register struct dksoftc *dk;
	register struct partition *pp;
	register int unit;
	struct vba_device *vi;
	int s, error, part = hdpart(dev), mask = 1 << part;
	daddr_t start, end;
E 3

I 3
	unit = hdunit(dev);
	if (unit >= NHD || (vi = hddinfo[unit]) == 0 || vi->ui_alive == 0)
		return(ENXIO);
	dk = &dksoftc[unit];
	lp = &dk->dk_label;
	s = spl7();
	while (dk->dk_state != OPEN && dk->dk_state != OPENRAW &&
	    dk->dk_state != CLOSED)
D 10
		sleep((caddr_t)dk, PZERO+1);
E 10
I 10
		if (error = tsleep((caddr_t)dk, (PZERO+1) | PCATCH,
		    devopn, 0)) {
			splx(s);
			return (error);
		}
E 10
	splx(s);
	if (dk->dk_state != OPEN && dk->dk_state != OPENRAW)
		if (error = hdinit(dev, flags))
			return(error);
E 3

D 3
	ok = TRUE;
	ctlr = hu->ctlr;
	hc = &hdc_ctlrs[ctlr];
	master = &hc->master_mcb;

E 3
I 3
	if (hdcwstart == 0) {
		timeout(hdcwatch, (caddr_t)0, hz);
		hdcwstart++;
	}
E 3
	/*
D 3
	 * Complete the setup of the mcb and master mcb.
E 3
I 3
	 * Warn if a partion is opened that overlaps another partition
	 * which is open unless one is the "raw" partition (whole disk).
E 3
	 */
D 3

	mcb->priority   = 0;
	mcb->interrupt  = FALSE;
	mcb->drive      = hu->slave;
	mcb->forw_phaddr= 0;
	mcb->context	= 0;
	mcb->reserved[0]= 0;
	mcb->reserved[1]= 0;
	master->forw_phaddr = (long) vtoph(0,&mcb->forw_phaddr);
	master->mcs = 0;
	master->reserve1 = 0;
	master->reserve2 = 0;
	master->context = 0;
	master->cmcb_phaddr = 0;
	master->mcl = MCL_IMMEDIATE;
	bzero( (caddr_t)&master->xstatus[0], HDC_XSTAT_SIZE );

	/*
	 * Tell hdc to xqt the mcb; wait for completion.
	 * If a controller error or timeout occurs, print
	 * out the mcb and master mcb on the console.
	 */

	HDC_REGISTER(master_mcb_reg) = hc->master_phaddr;
	timeout = 15000;
	while (TRUE) {
		DELAY(1000);
D 2
		mtpr(0,PADC);
E 2
I 2
		mtpr(PADC, 0);
E 2
		if ( (master->mcs & MCS_DONE) &&
		    !(master->mcs & MCS_FATALERROR ) ) break;
		timeout--;
		if ( timeout > 0   &&
			!(master->mcs & MCS_FATALERROR) ) continue;
		if ( master->mcs & MCS_FATALERROR )
			printf("hdc: controller %d fatal error\n",ctlr);
		else
			printf("hdc: controller %d timed out\n",ctlr);
	        hddumpmcb(mcb);
	        hddumpmmcb(master);
		ok = FALSE;
E 3
I 3
#define	RAWPART		8		/* 'x' partition */	/* XXX */
	if ((dk->dk_openpart & mask) == 0 && part != RAWPART) {
		pp = &lp->d_partitions[part];
		start = pp->p_offset;
		end = pp->p_offset + pp->p_size;
		for (pp = lp->d_partitions;
		     pp < &lp->d_partitions[lp->d_npartitions]; pp++) {
			if (pp->p_offset + pp->p_size <= start ||
			    pp->p_offset >= end)
				continue;
			if (pp - lp->d_partitions == RAWPART)
				continue;
			if (dk->dk_openpart & (1 << (pp - lp->d_partitions)))
				log(LOG_WARNING,
				    "hd%d%c: overlaps open partition (%c)\n",
				    unit, part + 'a',
				    pp - lp->d_partitions + 'a');
		}
	}
	if (part >= lp->d_npartitions)
		return(ENXIO);
	dk->dk_openpart |= mask;
	switch (fmt) {
	case S_IFCHR:
		dk->dk_copenpart |= mask;
E 3
		break;
I 3
	case S_IFBLK:
		dk->dk_bopenpart |= mask;
		break;
E 3
	}
D 3
	master->mcl = MCL_QUEUED;
	return(ok);
E 3
I 3
	return(0);
E 3
}

D 3
/*************************************************************************
*  Procedure:	hdintr
*
*  Description: The hdc interrupt routine.
*
*  Returns:
**************************************************************************/

hdintr(ctlr)

int	ctlr;		/* the hdc controller number.
			 */
E 3
I 3
/* ARGSUSED */
hdclose(dev, flags, fmt)
	dev_t dev;
	int flags, fmt;
E 3
{
D 3
	register master_mcb_type *master;	/* master mcb for this hdc  */
	register mcb_type	 *mcb;		/* the mcb just completed   */
	register struct buf	 *bp;		/* buf for the completed mcb*/
	register hdc_ctlr_type   *hc;		/* info for this controller */
	register struct iobuf    *iobp;		/* iobuf for this unit      */
	register int		 unit;		/* unit# of the hdc drive   */
	register int		 i;		/* temporary                */
E 3
I 3
	register struct dksoftc *dk;
	int mask;
E 3

D 3

	hc = &hdc_ctlrs[ctlr];
	master = &hc->master_mcb;
	uncache( &master->mcs );
	uncache( &master->context );
#ifdef HDCLOG
	hdlog(master,1 + 16*hc->ctlr);
#endif
	if ( !(master->mcs & MCS_DONE) ) {
	        printf("\nhdc: spurious interrupt from controller #%d\n",ctlr);
	        return;
E 3
I 3
	dk = &dksoftc[hdunit(dev)];
	mask = 1 << hdpart(dev);
	switch (fmt) {
	case S_IFCHR:
		dk->dk_copenpart &= ~mask;
		break;
	case S_IFBLK:
		dk->dk_bopenpart &= ~mask;
		break;
E 3
	}
D 3
	mcb = (mcb_type *) master->context;
	bp = mcb->buf_ptr;
	unit = HDC_UNIT(bp->b_dev);
	iobp = &vdtab[unit];

E 3
I 3
	if (((dk->dk_copenpart | dk->dk_bopenpart) & mask) == 0)
		dk->dk_openpart &= ~mask;
E 3
	/*
D 3
	 * Error log and system activity.
	 *
	 * Turn off the activity bit for this device.
	 * Record the time required to process the buf.
	 * If there is no more activity on this unit, record the
	 * amount of time that the unit was active.
	 * Update dkprf and lastcyl for "sadp".
E 3
I 3
	 * Should wait for i/o to complete on this partition
	 * even if others are open, but wait for work on blkflush().
E 3
	 */
D 3

	blkacty &= ~(1 << major(bp->b_dev));
	if (iobp->b_active) {
		vdstat[unit].io_resp += (time.tv_sec - bp->b_start);
		if (--iobp->b_active == 0)
			vdstat[unit].io_act += (time.tv_sec - iobp->io_start);
E 3
I 3
	if (dk->dk_openpart == 0) {
		int s = spl7();
		while (dk->dk_utab.b_actf)
			sleep((caddr_t)dk, PZERO-1);
		splx(s);
		dk->dk_state = CLOSED;
		dk->dk_wlabel = 0;
E 3
	}
D 3
	i = mcb->cyl;
	dkprf[unit][i >> 3]++;
	i -= lastcyl[unit];
	if (i < 0) i = -i;
	skprf[unit][i >> 3]++;
	lastcyl[unit] = mcb->cyl;
	dk_busy &= ~(1 << unit);
	dk_seek[unit]++;
	dk_xfer[unit]++;
E 3
I 3
	return(0);
}
E 3

D 3
	/*
	 * If there are no free mcb's, wake up anyone that might
	 * be waiting for one.  Remove the completed mcb from the
	 * queue of active mcb's and add it to the free-mcb queue.
	 */
E 3
I 3
hdinit(dev, flags)
	dev_t dev;
	int flags;
{
	register struct dksoftc *dk;
	register struct disklabel *lp;
	struct vba_device *vi;
	int error, unit;
	char *msg, *readdisklabel();
	extern int cold;
E 3

D 3
	if (hc->forw_free == (mcb_type *)&hc->forw_free)
		wakeup(hc);
	remque(mcb);
	insque(mcb,&hc->forw_free);
E 3
I 3
	vi = hddinfo[unit = hdunit(dev)];
	dk = &dksoftc[unit];
	dk->dk_unit = vi->ui_slave;
	dk->dk_ctlr = vi->ui_ctlr;
E 3

D 3
	/*
	 * If there was a fatal error, dump the mcb and master mcb on the
	 * console, then halt if the system was booted with the debug option.
	 *
	 * Record fatal and soft errors in the error log.
	 */
E 3
I 3
	if (flags & O_NDELAY) {
		dk->dk_state = OPENRAW;
		return(0);
	}
E 3

D 3
	bp->b_resid = 0;
	if (master->mcs & (MCS_SOFTERROR | MCS_FATALERROR) ) {
D 2
		mtpr( (caddr_t) master, P1DC );
		mtpr( (caddr_t) &master->xstatus[HDC_XSTAT_SIZE]-1, P1DC );
E 2
I 2
		mtpr(P1DC, (caddr_t)master);
		mtpr(P1DC, (caddr_t)&master->xstatus[HDC_XSTAT_SIZE]-1);
E 2
		if (master->mcs & MCS_FATALERROR) {
			bp->b_flags |= B_ERROR;
			bp->b_error = EIO;
			harderr(bp,"hdc");
			printf("\nhdc:  fatal error on controller #%d\n",ctlr);
			hddumpmmcb(master);
			hddumpmcb(mcb);
			if (boothowto & RB_DEBUG) asm("halt");
		};
		vdstat[unit].ios.io_misc++ ;
		iobp->io_erec = 0;
		iobp->io_addr = (caddr_t) hc->registers;
		iobp->io_stp  = &vdstat[unit].ios;
		iobp->io_nreg = HDC_XSTAT_SIZE;
		for (i=HDC_XSTAT_SIZE-1; i>0; i--) {
			if (master->xstatus[i] != 0) break;
			iobp->io_nreg--;
E 3
I 3
	error = 0;
	lp = &dk->dk_label;
	dk->dk_state = RDLABEL;
	if (msg = readdisklabel(dev, hdstrategy, lp)) {
		if (cold) {
			printf(": %s\n", msg);
			dk->dk_state = CLOSED;
		} else {
			log(LOG_ERR, "hd%d: %s\n", unit, msg);
			dk->dk_state = OPENRAW;
E 3
		}
D 3
		iobp->b_actf  = bp;
		iobp->b_dev   = bp->b_dev;
		fmtberr( iobp, mcb->cyl, &master->xstatus[0] );
		logberr(iobp, master->mcs & MCS_FATALERROR);
		bzero( (caddr_t)&master->xstatus[0], HDC_XSTAT_SIZE );
	}
E 3
I 3
#ifdef COMPAT_42
		hdclock(vi->ui_ctlr);
		if (!(error = hdreadgeometry(dk)))
			dk->dk_state = OPEN;
		hdcunlock(vi->ui_ctlr);
#endif
	} else
		dk->dk_state = OPEN;
	wakeup((caddr_t)dk);
	return(error);
}
E 3

I 3
hd_setsecsize(dk, lp)
	register struct dksoftc *dk;
	struct disklabel *lp;
{
	register int mul;

E 3
	/*
D 3
	 * If there are any waiting mcb's, move them to the active queue.
	 * Physically link the new mcb's from the master mcb.
E 3
I 3
	 * Calculate scaling shift for mapping
	 * DEV_BSIZE blocks to drive sectors.
E 3
	 */
I 3
	mul = DEV_BSIZE / lp->d_secsize;
	dk->dk_bshift = 0;
	while ((mul >>= 1) > 0)
		dk->dk_bshift++;
}
E 3

D 3
	master->forw_phaddr = 0;
next:   mcb = hc->forw_wait;
	remque(mcb);
	asm(" bvs done");
	insque(mcb,&hc->forw_active);
	mcb->forw_phaddr = master->forw_phaddr;
#ifdef HDCLOG
	hdlog(mcb,2 + 16*hc->ctlr);
#endif
	master->forw_phaddr = mcb->mcb_phaddr;
	goto next;
done:   asm("done:");
E 3
I 3
/* ARGSUSED */
hddgo(vm)
	struct vba_device *vm;
{}
E 3

D 3
	/*
	 * If there are any mcb's active, initialize the master mcb
	 * and tell the hdc to continue queued operation.
	 * New mcb's (if any) are linked off of "forw_phaddr".
	 */
E 3
I 3
extern int name_ext;
hdstrategy(bp)
	register struct buf *bp;
{
	register struct vba_device *vi;
	register struct disklabel *lp;
	register struct dksoftc *dk;
	struct buf *dp;
	register int unit;
	daddr_t sn, sz, maxsz;
	int part, s;
E 3

D 3
	if (hc->forw_active != (mcb_type *) &hc->forw_active) {
		master->mcs = 0;
#ifdef HDCLOG
		hdlog(master,3 + 16*hc->ctlr);
E 3
I 3
	vi = hddinfo[unit = hdunit(bp->b_dev)];
	if (unit >= NHD || vi == 0 || vi->ui_alive == 0) {
		bp->b_error = ENXIO;
		goto bad;
	}
	dk = &dksoftc[unit];
	if (dk->dk_state < OPEN)
		goto q;
	if (dk->dk_state != OPEN && (bp->b_flags & B_READ) == 0) {
		bp->b_error = EROFS;
		goto bad;
	}
	part = hdpart(bp->b_dev);
	if ((dk->dk_openpart & (1 << part)) == 0) {
		bp->b_error = ENODEV;
		goto bad;
	}
	lp = &dk->dk_label;
	sz = (bp->b_bcount + lp->d_secsize - 1) / lp->d_secsize;
	maxsz = lp->d_partitions[part].p_size;
	sn = bp->b_blkno << dk->dk_bshift;
	if (sn + lp->d_partitions[part].p_offset <= LABELSECTOR &&
#if LABELSECTOR != 0
	    sn + lp->d_partitions[part].p_offset + sz > LABELSECTOR &&
E 3
#endif
D 3
		HDC_REGISTER(master_mcb_reg)= hc->master_phaddr;
E 3
I 3
	    (bp->b_flags & B_READ) == 0 && dk->dk_wlabel == 0) {
		bp->b_error = EROFS;
		goto bad;
E 3
	}
I 3
	if (sn < 0 || sn + sz > maxsz) {
		if (sn == maxsz) {
			bp->b_resid = bp->b_bcount;
			goto done;
		}
		sz = maxsz - sn;
		if (sz <= 0) {
			bp->b_error = EINVAL;
			goto bad;
		}
		bp->b_bcount = sz * lp->d_secsize;
	}
	bp->b_cylin = (sn + lp->d_partitions[part].p_offset) / lp->d_secpercyl;
E 3

D 3
	/*
	 * Return the buf for the completed operation.
	 */

	iodone(bp);
E 3
I 3
q:	s = spl7();
	dp = &dk->dk_utab;
	disksort(dp, bp);
	if (!dp->b_active) {
		(void)hdustart(vi);
		if (!vi->ui_mi->um_tab.b_active)
			hdcstart(vi->ui_mi);
	}
	splx(s);
E 3
	return;
I 3
bad:
	bp->b_flags |= B_ERROR;
done:
	biodone(bp);
E 3
}

D 3
/*************************************************************************
*  Procedure:	hdioctl
*
*  Description: Character device ioctl routine.
*
*  Returns:     EACCES    formatting is active on the drive
*                         (or) function is valid only for the format program
*                         (or) formatting ioctl's must be done on partition 7
*               EIO       controller error occurred
*               ENXIO     invalid parameter value
*               0         normal
**************************************************************************/

int
hdioctl(dev, command, arg, flag)

dev_t		dev ; 		/* Device type. Major/minor dev#.
				 */
int		command ;	/* The ioctl commmand.
				 */
int		*arg ; 		/* Data. Format depends on ioctl.
				 */
int		flag ;		/* Not used.
				 */
E 3
I 3
hdustart(vi)
	register struct vba_device *vi;
E 3
{
D 3
	register hdc_unit_type	*hu;		/* unit information        */
	int			formatok;	/* TRUE= it's ok to format */
	register int		i;
E 3
I 3
	register struct buf *bp, *dp;
	register struct vba_ctlr *vm;
	register struct dksoftc *dk;
E 3

D 3
	hu = &hdc_units[ HDC_UNIT(dev) ];
	formatok = ( HDC_PARTITION(dev)==7  &&  hu->format );
	switch (command) {
E 3
I 3
	dk = &dksoftc[vi->ui_unit];
	dp = &dk->dk_utab;
E 3

D 3
	case DSKIOCFORMAT: {
E 3
I 3
	/* if queue empty, nothing to do.  impossible? */
	if (dp->b_actf == NULL)
		return;
E 3

D 3
		/*
		 * Format a disk track. The received argument is a pointer
		 * to a "formatop" structure describing the track to format.
		 *
		 * Set up a buffer with each longword corresponding to a
		 * sector on the track; a 1 means no flaw, a 0 means a flaw.
		 * Call hdphysio to send the data from the phio_data buffer
		 * to the hdc to format the track.
		 */
E 3
I 3
	/* place on controller transfer queue */
	vm = vi->ui_mi;
	if (vm->um_tab.b_actf == NULL)
		vm->um_tab.b_actf = dp;
	else
		vm->um_tab.b_actl->b_forw = dp;
	vm->um_tab.b_actl = dp;
	dp->b_forw = NULL;
	dp->b_active++;
}
E 3

D 3
		register struct formatop *track;
E 3
I 3
hdcstart(vm)
	register struct vba_ctlr *vm;
{
	register struct buf *bp;
	register struct dksoftc *dk;
	register struct disklabel *lp;
	register struct master_mcb *master;
	register struct mcb *mcb;
	struct vba_device *vi;
	struct hdcsoftc *hdc;
	struct buf *dp;
	int sn;
E 3

D 3
		if (!formatok) return EACCES;
		track = (struct formatop *) arg;
		for (i=0; i<hu->phys_sectors; i++)
			hu->phio_data[i] = 1;
		for (i=0; i<track->flaw_count; i++)
			hu->phio_data[track->flaw[i]] = 0;
		if (!hdphysio(
			dev,
			HCMD_FORMAT,
			track->cylinder,
			track->head,
			0,
			hu->phio_data,
			hu->phys_sectors * 4) )
			   return EIO;
		break;
E 3
I 3
	/* pull a request off the controller queue */
	for (;;) {
		if ((dp = vm->um_tab.b_actf) == NULL)
			return;
		if (bp = dp->b_actf)
			break;
		vm->um_tab.b_actf = dp->b_forw;
E 3
	}

D 3
	case DSKIOCCERTIFY: {
E 3
I 3
	/* mark controller active */
	vm->um_tab.b_active++;
E 3

D 3
		/*
		 * Certify a disk track. The received argument is a pointer
		 * to a "formatop" structure describing the track to certify.
		 *
		 * Call hdphysio to read data into the phio_data buffer.
		 * The controller returns data in which each longword
		 * corresponds to a sector on the track; a 1 means no flaw,
		 * a 0 means a flaw.
		 */
E 3
I 3
	vi = hddinfo[hdunit(bp->b_dev)];
	dk = &dksoftc[vi->ui_unit];
	lp = &dk->dk_label;
	sn = bp->b_blkno << dk->dk_bshift;
E 3

D 3
		register struct formatop *track;
E 3
I 3
	/* fill in mcb */
	mcb = &dk->dk_mcb;
	mcb->forw_phaddr = 0;
	/* mcb->priority = 0; */
	mcb->interrupt = 1;
	mcb->command = (bp->b_flags & B_READ) ? HCMD_READ:HCMD_WRITE;
D 4
	mcb->cyl = sn / lp->d_secpercyl;
E 4
I 4
	mcb->cyl = bp->b_cylin;
/* assumes partition starts on cylinder boundary */
E 4
	mcb->head = (sn / lp->d_nsectors) % lp->d_ntracks;
	mcb->sector = sn % lp->d_nsectors;
	mcb->drive = vi->ui_slave;
	/* mcb->context = 0;		/* what do we want on interrupt? */
E 3

D 3
		if (!formatok) return EACCES;
		track = (struct formatop *) arg;
		if (!hdphysio(
			dev,
			HCMD_CERTIFY,
			track->cylinder,
			track->head,
			0,
			hu->phio_data,
			hu->phys_sectors * 4) )
			   return EIO;
		track->flaw_count = 0;
		for (i=0; i<hu->phys_sectors; i++) {
			if (track->flaw_count >= MAXVFLAW) break;
			if (hu->phio_data[i]==0) {
				track->flaw[track->flaw_count] = i;
				track->flaw_count++;
			}
		}
		break;
E 3
I 3
	hdc = &hdcsoftc[vm->um_ctlr];
D 6
	if (!hd_sgsetup(bp, hdc->hdc_rbuf, mcb->chain)) {
E 6
I 6
	if (!hd_sgsetup(bp, &hdc->hdc_rbuf, mcb->chain)) {
E 6
		mcb->chain[0].wcount = (bp->b_bcount+3) >> 2;
		mcb->chain[0].memadr =
		    vbasetup(bp, &hdc->hdc_rbuf, (int)lp->d_secsize);
E 3
	}

D 3
	case DSKIOCVERIFY: {
E 3
I 3
	if (vi->ui_dk >= 0) {
		dk_busy |= 1<<vi->ui_dk;
		dk_xfer[vi->ui_dk]++;
		dk_wds[vi->ui_dk] += bp->b_bcount>>6;
	}
E 3

D 3
		/*
		 * Verify a disk track. The received argument is a pointer
		 * to a "formatop" structure describing the track to verify.
		 */
E 3
I 3
	master = &hdc->hdc_mcb;
	master->mcw = MCL_QUEUED;
	master->interrupt = HDCINTERRUPT + vm->um_ctlr;
	master->forw_phaddr = (u_long)vtoph((struct proc *)NULL, mcb);
	hdc->hdc_reg->master_mcb = (u_long)hdc->hdc_mcbp;
}
E 3

D 3
		register struct formatop *track;
E 3
I 3
/*
 * Wait for controller to finish current operation
 * so that direct controller accesses can be done.
 */
hdclock(ctlr)
	int ctlr;
{
	register struct vba_ctlr *vm = hdcminfo[ctlr];
	register struct hdcsoftc *hdc;
	int s;
E 3

D 3
		if (!formatok) return EACCES;
		track = (struct formatop *) arg;
		if (!hdphysio(
			dev,
			HCMD_VERIFY,
			track->cylinder,
			track->head,
			0,
			0,
			0) )
				return EIO;
		break;
E 3
I 3
	hdc = &hdcsoftc[ctlr];
	s = spl7();
	while (vm->um_tab.b_active || hdc->hdc_flags & HDC_LOCKED) {
		hdc->hdc_flags |= HDC_WAIT;
		sleep((caddr_t)hdc, PRIBIO);
E 3
	}
I 3
	hdc->hdc_flags |= HDC_LOCKED;
	splx(s);
}
E 3

D 3
	case DSKIOCFORMATCTL: {
E 3
I 3
/*
 * Continue normal operations after pausing for 
 * munging the controller directly.
 */
hdcunlock(ctlr)
	int ctlr;
{
	register struct vba_ctlr *vm;
	register struct hdcsoftc *hdc = &hdcsoftc[ctlr];
E 3

D 3
		/*
		 * This ioctl provides special format control.
		 *
		 * Currently the valid arguments are:
		 * arg= 0  disable formatting;
		 * arg= 1  enable formatting (allow privileged access);
		 *
		 * Partition must be the disk definition tracks of
		 * the raw device.
		 */

	        if (HDC_PARTITION(dev) != HDC_DEFPART )
	                return EACCES;
		switch (*arg) {

	        case 0: hu->format = FALSE;
	                break;

	        case 1: if (hu->format)
				return EACCES;
	        	hu->format = TRUE;
	                break;

	        default: return ENXIO;
		}
		break;
E 3
I 3
	hdc->hdc_flags &= ~HDC_LOCKED;
	if (hdc->hdc_flags & HDC_WAIT) {
		hdc->hdc_flags &= ~HDC_WAIT;
		wakeup((caddr_t)hdc);
	} else {
		vm = hdcminfo[ctlr];
		if (vm->um_tab.b_actf)
			hdcstart(vm);
E 3
	}
I 3
}
E 3

D 3
	case DSKIOCGEOMETRY: {
E 3
I 3
hdintr(ctlr)
	int ctlr;
{
	register struct buf *bp, *dp;
	register struct vba_ctlr *vm;
	register struct vba_device *vi;
	register struct hdcsoftc *hdc;
	register struct mcb *mcb;
	struct master_mcb *master;
	register int status;
	int timedout;
	struct dksoftc *dk;
E 3

D 3
		/*
		 * Return info about disk geometry (partitions).
		 * Caller's parameter is a pointer to a geometry
		 * status structure.
		 */
E 3
I 3
	hdc = &hdcsoftc[ctlr];
	master = &hdc->hdc_mcb;
	uncache(&master->mcs);
	uncache(&master->context);
E 3

D 3
		register geometry_status *geo_status;

		geo_status = (geometry_status *) arg;
		for (i=0; i<GB_MAXPART; i++) {
			geo_status->partition[i].start = hu->partition[i].start;
			geo_status->partition[i].length=hu->partition[i].length;
		}
		break;
E 3
I 3
	vm = hdcminfo[ctlr];
	if (!vm->um_tab.b_active || !(master->mcs&MCS_DONE)) {
		printf("hd%d: stray interrupt\n", ctlr);
		return;
E 3
	}

D 3
	case DSKIOCSETGEOMETRY: {
E 3
I 3
	dp = vm->um_tab.b_actf;
	bp = dp->b_actf;
	vi = hddinfo[hdunit(bp->b_dev)];
	dk = &dksoftc[vi->ui_unit];
	if (vi->ui_dk >= 0)
		dk_busy &= ~(1<<vi->ui_dk);
	timedout = (hdc->hdc_wticks >= HDCMAXTIME);
E 3

D 3
		/*
		 * Set new geometry - new partition sizes.
		 * Caller must have formatting privilege.
		 * Caller's parameter is a pointer to a geometry
		 * status structure containing the new geometries.
		 * The disk definition partition cannot be changed.
		 */
E 3
I 3
	mcb = &dk->dk_mcb;
E 3

D 3
		register geometry_status *geo_status;

		if (!formatok) return EACCES;
		geo_status = (geometry_status *) arg;
		for (i=0; i<GB_MAXPART; i++) {
			if (i==HDC_DEFPART) continue;
			hu->partition[i].start = geo_status->partition[i].start;
			hu->partition[i].length=geo_status->partition[i].length;
E 3
I 3
	if (master->mcs & (MCS_SOFTERROR | MCS_FATALERROR) || timedout)
		hdcerror(ctlr, *(u_long *)master->xstatus);
D 4
	else {
E 4
I 4
	else 
E 4
		hdc->hdc_wticks = 0;
D 4
		if (vm->um_tab.b_active) {
			vm->um_tab.b_active = 0;
			vm->um_tab.b_actf = dp->b_forw;
			dp->b_active = 0;
			dp->b_errcnt = 0;
			dp->b_actf = bp->av_forw;
			bp->b_resid = 0;
			vbadone(bp, &hdc->hdc_rbuf);
			biodone(bp);
			/* start up now, if more work to do */
			if (dp->b_actf)
				hdustart(vi);
			else if (dk->dk_openpart == 0)
				wakeup((caddr_t)dk);
E 3
		}
E 4
I 4
	if (vm->um_tab.b_active) {
		vm->um_tab.b_active = 0;
		vm->um_tab.b_actf = dp->b_forw;
		dp->b_active = 0;
		dp->b_errcnt = 0;
		dp->b_actf = bp->av_forw;
		bp->b_resid = 0;
		vbadone(bp, &hdc->hdc_rbuf);
		biodone(bp);
		/* start up now, if more work to do */
		if (dp->b_actf)
			hdustart(vi);
		else if (dk->dk_openpart == 0)
			wakeup((caddr_t)dk);
E 4
D 3
		break;
E 3
	}
I 3
	/* if there are devices ready to transfer, start the controller. */
	if (hdc->hdc_flags & HDC_WAIT) {
		hdc->hdc_flags &= ~HDC_WAIT;
		wakeup((caddr_t)hdc);
	} else if (vm->um_tab.b_actf)
		hdcstart(vm);
}
E 3

D 3
	case DSKIOCSTATUS: {
E 3
I 3
D 4
hdioctl(dev, command, data, flag)
E 4
I 4
hdioctl(dev, cmd, data, flag)
E 4
	dev_t dev;
D 4
	int command, flag;
E 4
I 4
	int cmd, flag;
E 4
	caddr_t data;
{
I 4
	register int unit;
	register struct dksoftc *dk;
	register struct disklabel *lp;
E 4
	int error;
E 3

D 3
		/*
		 * Return info about the disk. Caller's parameter is a
		 * pointer to a dsk_status structure.
		 */
E 3
I 3
D 4
	switch (command) {
E 4
I 4
	unit = hdunit(dev);
	dk = &dksoftc[unit];
	lp = &dk->dk_label;
	error = 0;
	switch (cmd) {
	case DIOCGDINFO:
		*(struct disklabel *)data = *lp;
		break;
	case DIOCGPART:
		((struct partinfo *)data)->disklab = lp;
		((struct partinfo *)data)->part =
		    &lp->d_partitions[hdpart(dev)];
		break;
	case DIOCSDINFO:
		if ((flag & FWRITE) == 0)
			error = EBADF;
		else
			error = setdisklabel(lp, (struct disklabel *)data,
			    (dk->dk_state == OPENRAW) ? 0 : dk->dk_openpart);
		if (error == 0 && dk->dk_state == OPENRAW)
			dk->dk_state = OPEN;
		break;
	case DIOCWLABEL:
		if ((flag & FWRITE) == 0)
			error = EBADF;
		else
			dk->dk_wlabel = *(int *)data;
		break;
	case DIOCWDINFO:
		if ((flag & FWRITE) == 0)
			error = EBADF;
		else if ((error = setdisklabel(lp, (struct disklabel *)data,
		    (dk->dk_state == OPENRAW) ? 0 : dk->dk_openpart)) == 0) {
			int wlab;
E 4
E 3

I 4
			if (error == 0 && dk->dk_state == OPENRAW)
				dk->dk_state = OPEN;
			/* simulate opening partition 0 so write succeeds */
			dk->dk_openpart |= (1 << 0);		/* XXX */
			wlab = dk->dk_wlabel;
			dk->dk_wlabel = 1;
			error = writedisklabel(dev, hdstrategy, lp);
			dk->dk_openpart = dk->dk_copenpart | dk->dk_bopenpart;
			dk->dk_wlabel = wlab;
		}
		break;
E 4
D 3
		register dsk_status *status;

		status = (dsk_status *) arg;
		status->id =		hu->id;
		status->rpm =		hu->rpm;
		status->bytes_per_sec=	hu->bytes_per_sec;
		status->cylinders =	hu->cylinders;
		status->heads =		hu->heads;
		status->sectors =	hu->sectors;
		status->phys_cylinders=	hu->phys_cylinders;
		status->phys_heads =	hu->phys_heads;
		status->phys_sectors =	hu->phys_sectors;
		status->diag_cyl =	hu->diag_cyl;
		status->diag_cylinders=	hu->diag_cyl_count;
		status->def_cyl =	hu->def_cyl;
		status->def_cylinders =	hu->def_cyl_count;
E 3
I 3
	default:
		error = ENOTTY;
E 3
		break;
	}
I 3
D 4
	return(error);
E 4
I 4
	return (error);
E 4
}
E 3

D 3
	case DSKIOCVENDORFLAW: {
E 3
I 3
/*
 * Watch for lost interrupts.
 */
hdcwatch()
{
	register struct hdcsoftc *hdc;
	register struct vba_ctlr **vmp;
	register int ctlr;
	int s;
E 3

D 3
		/*
		 * Return vendor flaw info.
		 *
		 * Read in the vendor data from relative sector 0 of
		 * the track to the phio_data buffer; then copy the
		 * vendor flaw data to the caller's buffer.
		 */

		register vflaw_type *vflaw;
		register struct flaw *vendor;

		if (!formatok) return EACCES;
		vflaw = (vflaw_type *) arg;
		if (!hdphysio(
			dev,
			HCMD_VENDOR,
			vflaw->cylinder,
			vflaw->head,
			0,
			hu->phio_buf,
			HDC_VDATA_SIZE << 2 ))
 				return EIO;
		vendor = (struct flaw *) &hu->phio_data[0];
		for (i=0; i<MAXVFLAW; i++) {
			vflaw->flaw[i].offset = vendor[i].offset;
			vflaw->flaw[i].length = vendor[i].length;
E 3
I 3
	timeout(hdcwatch, (caddr_t)0, hz);
	for (vmp = hdcminfo, hdc = hdcsoftc, ctlr = 0; ctlr < NHDC;
	    ++ctlr, ++vmp, ++hdc) {
		if (*vmp == 0 || (*vmp)->um_alive == 0)
			continue;
		s = spl7();
		if ((*vmp)->um_tab.b_active &&
		    hdc->hdc_wticks++ >= HDCMAXTIME) {
			printf("hd%d: lost interrupt\n", ctlr);
			hdintr(ctlr);
E 3
		}
D 3
		break;
E 3
I 3
		splx(s);
E 3
	}
D 3

	default: return ENXIO;

	}
	return 0;
E 3
}

D 3
/*************************************************************************
*  Procedure:	hdopen
*
*  Description: The character device and block device open routine.
*
*  Returns:     ENXIO     the partition or device isn't defined
*               EACCES    Formatting is active on this drive
*               0         normal
**************************************************************************/

int
hdopen(dev, flag)

dev_t		dev ; 		/* Device type. Major/minor dev#.
				 */
int		flag ;		/* Not used.
				 */
E 3
I 3
hddump(dev)
	dev_t dev;
E 3
{
D 3
	register int			unit;		/* hdc unit#  (0-31)*/
	register int			par;		/* partition# (0-7) */
	register struct vba_device	*vba_unit;	/* vba unit info    */
	register hdc_unit_type		*hu;		/* hdc unit info    */


	unit = HDC_UNIT(dev);
	par = HDC_PARTITION(dev);
	vba_unit = vddinfo[unit];
	hu = &hdc_units[unit];
	if ( !vba_unit->ui_alive || hu->partition[par].length == 0)
	      return ENXIO;
	if (hu->format)
	      return EACCES;
	vdtab[unit].io_stp  = &vdstat[unit].ios;
	return 0;
E 3
I 3
	return(ENXIO);
E 3
}

D 3
/*************************************************************************
*  Procedure:	hdphysio
*
*  Description: "hdphysio" does the physical i/o initiated by this
*               handler. It does the things which "physio" does for
*               raw read/writes; i.e. it provides an interface to the
*               hdstrategy routine.
*
*               hdphysio assumes that it has exclusive access to the
*               drive; it uses the drive's phio buf.
*
*  Returns:     FALSE     an i/o error occurred.
*               0         normal; data is in phio_data if read was done
**************************************************************************/

int
hdphysio(dev,command,cylinder,head,sector,ta,bc)

dev_t	dev;			/*  major/minor device number
				 */
int	command;		/*  the hdc command to execute
				 */
int	cylinder;		/*  disk cylinder address
				 */
int	head;			/*  disk head address
				 */
int	sector;			/*  disk sector address
				 */
int	ta;			/*  memory transfer address
				 */
int	bc;			/*  byte count
				 */
E 3
I 3
hdsize(dev)
	dev_t dev;
E 3
{
D 3
	register struct buf	*bp;	/* buf structure built here */
	hdc_unit_type		*hu;	/* hdc device unit info     */
	int			s;	/* processor level save     */
E 3
I 3
	register int unit = hdunit(dev);
	register struct dksoftc *dk;
	struct vba_device *vi;
	struct disklabel *lp;
E 3

D 3
	hu = &hdc_units[ HDC_UNIT(dev) ];
	bp = (struct buf *) &hu->phio_buf;
	bp->b_error = 0;
	bp->b_proc = u.u_procp;
	bp->b_un.b_addr = (caddr_t) ta;
	bp->b_flags = B_BUSY | B_PHYS | B_READ | B_LOCALIO;
	bp->b_dev = dev;
	bp->b_blkno = 0;
	bp->b_hdccommand = command;
	bp->b_cyl = cylinder;
	bp->b_head = head;
	bp->b_sector = sector;
	bp->b_bcount = bc;
	hdstrategy(bp);
	s = spl8();
	while ((bp->b_flags & B_DONE) == 0)
		slumber((caddr_t)bp, 0, iocomboost);
	splx(s);
	bp->b_flags &= ~(B_BUSY | B_PHYS | B_WANTED | B_LOCALIO);
	if (bp->b_error != 0)
		return FALSE;
	return TRUE;
E 3
I 3
	if (unit >= NHD || (vi = hddinfo[unit]) == 0 || vi->ui_alive == 0 ||
	    (dk = &dksoftc[unit])->dk_state != OPEN)
		return (-1);
	lp = &dk->dk_label;
	return ((int)lp->d_partitions[hdpart(dev)].p_size >> dk->dk_bshift);
E 3
}

D 3
/*************************************************************************
*  Procedure:	hdprobe
*
*  Description: "hdprobe" verifies that an hdc controller is really
*               there and then initializes the controller. It is called
*		during the configuration phase of a reboot for each
*		hdc controller in the configuration.
*
*  Returns:	TRUE means the controller is ready.
**************************************************************************/

int
hdprobe(vba_ctlr)

register struct vba_ctlr	*vba_ctlr;	/* vba controller information
						 */
E 3
I 3
hdimcb(dk)
	register struct dksoftc *dk;
E 3
{
D 3
	register hdc_ctlr_type	*hc;		/* hdc controller info      */
	register hdc_mid_type	*id;		/* returned module id word  */
	register int		ctlr;		/* the controller number    */
	register int		i;		/* temporary                */
	mcb_type		*mcb;		/* temporary mcb pointer    */
	extern	int		Xhdintr0, Xhdintr1, Xhdintr2, Xhdintr3,
				Xhdintr4, Xhdintr5, Xhdintr6, Xhdintr7 ;
	static  int		hd_proc[] = {
					(int)& Xhdintr0, (int)& Xhdintr1,
					(int)& Xhdintr2, (int)& Xhdintr3,
					(int)& Xhdintr4, (int)& Xhdintr5,
					(int)& Xhdintr6, (int)& Xhdintr7
	} ;
E 3
I 3
	register struct master_mcb *master;
	register struct mcb *mcb;
	register struct hdcsoftc *hdc;
	int timeout;
E 3

I 3
	/* fill in mcb */
	mcb = &dk->dk_mcb;
	mcb->interrupt = 0;
	mcb->forw_phaddr = 0;
	mcb->drive = dk->dk_unit;
E 3

D 3
	ctlr = vba_ctlr->um_ctlr;
	hc = &hdc_ctlrs[ctlr];
	/*
	 * Initialize the hdc controller structure.
	 * Initially all mcb's are in the free-mcb list.
	 * The interrupt acknowledge word is the vector offset
	 * for this controller's interrupts.
	 */
E 3
I 3
	hdc = &hdcsoftc[dk->dk_ctlr];
	master = &hdc->hdc_mcb;
E 3

D 3
	hc->ctlr = ctlr;
	hc->registers = (hdc_regs_type *) vba_ctlr->um_addr;
	id = &hc->mid;
	if (badaddr(&hc->registers->module_id_reg,4,vtoph(0,id)))
                return FALSE;
	hc->forw_active = (mcb_type *) &hc->forw_active;
	hc->back_active = (mcb_type *) &hc->forw_active;
	hc->forw_wait   = (mcb_type *) &hc->forw_wait;
	hc->back_wait   = (mcb_type *) &hc->forw_wait;
	hc->forw_free   = (mcb_type *) &hc->forw_free;
	hc->back_free   = (mcb_type *) &hc->forw_free;
	for (i=HDC_MAXMCBS-1; i>=0; i--) {
		mcb = &hc->mcbs[i];
		mcb->mcb_phaddr = vtoph( 0, &mcb->forw_phaddr);
		insque( mcb, &hc->forw_free);
	}
	vba_ctlr -> um_ivct = get_ivct( 0, 1 ) ;
	if ( vba_ctlr -> um_ivct == (-1) )
		return FALSE ;
	init_ivct( vba_ctlr -> um_ivct, hd_proc[ vba_ctlr -> um_ctlr ] ) ;
	hc->master_mcb.interrupt = vba_ctlr -> um_ivct ;
	hc->master_phaddr = (u_long) vtoph( 0, &hc->master_mcb) ;
E 3
I 3
	/* fill in master mcb */
	master->mcw = MCL_IMMEDIATE;
	master->forw_phaddr = (u_long)vtoph((struct proc *)NULL, mcb);
	master->mcs = 0;
E 3

D 3
	/*
	 * Read in the hdc module id word.
	 */

	HDC_REGISTER(module_id_reg) = (unsigned long) vtoph(0,id);
	DELAY(10000);
D 2
	mtpr(0,PADC);
E 2
I 2
	mtpr(PADC, 0);
E 2

	/*
	 * hdc's are reset and downloaded by the console processor.
	 * Check the module id; the controller is bad if:
	 * 1) it is not an hdc;
	 * 2) the hdc's writeable control store is not loaded;
	 * 3) the hdc failed the functional integrity test;
	 */

	printf("hdc controller %d module id is %x\n", ctlr, *id);
	if (id->module_id != (unsigned char) HDC_MID) {
		printf("hdc:  controller #%d bad module id.\n",ctlr);
		return FALSE;
E 3
I 3
	/* kick controller and wait */
	hdc->hdc_reg->master_mcb = (u_long)hdc->hdc_mcbp;
	for (timeout = 15000; timeout; --timeout) {
		DELAY(1000);
		mtpr(PADC, 0);
		if (master->mcs&MCS_FATALERROR) {
			printf("hdc%d: fatal error\n", dk->dk_ctlr);
			hdcerror(dk->dk_ctlr, *(u_long *)master->xstatus);
			return(1);
		}
		if (master->mcs&MCS_DONE)
			return(0);
E 3
	}
D 3
	if (id->code_rev == (unsigned char) 0xFF ) {
		printf("hdc:  controller #%d micro-code not loaded.\n",ctlr);
		return FALSE;
	}
	if (id->fit != (unsigned char) 0xFF ) {
		printf("hdc:  controller #%d FIT test failed.\n",ctlr);
		return FALSE;
	}
	/*
	 * Reset the hdc in case it still has queued mcb's.
	 */

	HDC_REGISTER(soft_reset_reg) = 0;
	DELAY(1000000);
	return TRUE;
E 3
I 3
	printf("hdc%d: timed out\n", dk->dk_ctlr);
	return(1);
E 3
}

D 3
/*************************************************************************
D 2
*  Procedure:	hdread
*
*  Description: Character read routine. This procedure is called by the
*               inode read/write routine 'ino_rw'.
*
*  Returns:     Error status returned by 'physio'.
**************************************************************************/

int
hdread(dev, uio)

dev_t		dev;	/* Device type. Major/minor dev#.
			 */
int		*uio;	/* Pointer to a uio structure describing
			 * a read request: buffer address;
			 * sector offset; no. of sectors; etc.
			 */
{
	hdc_unit_type	*hu;	/* hdc unit information   */

	hu = &hdc_units[ HDC_UNIT(dev) ];

	/*
	 * 'physio' builds the buf structure, locks the user pages, calls
	 * 'hdstrategy' to do the read, waits until i/o is complete (iodone),
	 * then deallocates the buf structure and unlocks the pages.
	 */

	return physio(
		hdstrategy,	/* hdc's strategy routine	    */
		&hu->raw_buf,	/* physio builds a buf struct here  */
		dev,		/* major/minor device number	    */
		B_READ,		/* read the buffer 		    */
		minphys,	/* routine to set max transfer size */
		uio);		/* describes the transfer request   */
}

/*************************************************************************
E 2
*  Procedure:	hdsize
*
*  Description: Return the partition size for a specified partition.
*
*  Returns:     Partition size in blocks.
*               -1 means the device isn't there
**************************************************************************/

int
hdsize(dev)

register dev_t	dev ; 		/* Major/minor dev#.
				 */
E 3
I 3
hdcerror(ctlr, code)
	int ctlr;
	u_long code;
E 3
{
D 3
	int			unit;		/* hdc unit#  (0-31)  */
	int			par;		/* partition# (0-7)   */
	struct vba_device	*vba_unit;	/* vba unit info      */
	hdc_unit_type		*hu;		/* hdc unit info      */

	unit = HDC_UNIT(dev);
	par = HDC_PARTITION(dev);
	vba_unit = vddinfo[unit];
	hu = &hdc_units[unit];
	if (vba_unit==0 || !vba_unit->ui_alive) return -1;
	return (hu->partition[par].length);
}

/*************************************************************************
*  Procedure:	hdslave
*
*  Description: "hdslave" verifies that an hdc drive is really there.
*               It is called during the configuration phase of a reboot
*               for each drive on an hdc.
*
*               Note: a lot of device initialization is done here, which
*               should normally be done in hdattach; however, it is
*               done here since it is info needed to determine whether
*               the drive is really there and is functional.
*
*  Returns:	TRUE means the drive is there.
**************************************************************************/

int
hdslave(vba_unit,regs)

struct vba_device	*vba_unit;		/* vba drive info
						 */
hdc_regs_type		*regs;			/* hdc io address (not used)
						 */
{
	register hdc_ctlr_type	*hc;		/* hdc ctlr info            */
	register hdc_unit_type	*hu;		/* hdc unit info            */
	register mcb_type	*mcb;		/* mcb to send to the hdc   */
	register int		unit;		/* hdc unit# (0-31)         */
	register int		ctlr;		/* hdc ctlr# (0-15)         */
	register int		i;		/* temp                     */
	geometry_block		*geo;		/* ptr to the geometry block*/
	drive_stat_type		*drive_status;	/* status returned by hdc   */

	ctlr = vba_unit->ui_ctlr;
	hc = &hdc_ctlrs[ctlr];
	unit = vba_unit->ui_unit;
	hu = &hdc_units[unit];
	mcb = (mcb_type *) &hu->phio_mcb;

	/*
	 * Initialize things in the hdc unit structure which are used
	 * by this routine. The rest is initialized by hdattach.
	 */

	hu->ctlr = ctlr;
	hu->unit = unit;
	hu->slave = vba_unit->ui_slave;

	/*
	 * Read the drive status and keep a permanent copy of the
	 * info in the hdc unit structure.
	 */

	drive_status = (drive_stat_type *) hu->phio_data;
	mcb->command = HCMD_STATUS;
	mcb->chain[0].lwc = sizeof(drive_stat_type) / 4;
	mcb->chain[0].ta  = (u_long) vtoph(0,drive_status);
	if (!hdimcb(hu,mcb))
		return FALSE;
	hu->id =		drive_status->id;
	hu->cylinders =		drive_status->max_cyl+1;
	hu->heads =		drive_status->max_head+1;
	hu->sectors =		drive_status->max_sector+1;
	hu->phys_cylinders =	drive_status->max_phys_cyl+1;
	hu->phys_heads =	drive_status->max_phys_head+1;
	hu->phys_sectors =	drive_status->max_phys_sector+1;
	hu->def_cyl =		drive_status->def_cyl;
	hu->def_cyl_count =	drive_status->def_cyl_count;
	hu->diag_cyl =		drive_status->diag_cyl;
	hu->diag_cyl_count =	drive_status->diag_cyl_count;
	hu->bytes_per_sec =	drive_status->bytes_per_sec;
	hu->rpm =		drive_status->rpm;
	hu->partition[HDC_DEFPART].start  =
		hu->def_cyl * hu->sectors * hu->heads / HDC_SPB;
	hu->partition[HDC_DEFPART].length =
		hu->def_cyl_count * hu->sectors * hu->heads / HDC_SPB;

	/*
	 * Report the drive down if anything in the drive status
	 * looks bad.  If the drive is offline and it is not on
	 * cylinder, then the drive is not there.
	 * If there is a fault condition, the hdc will try to clear
	 * it when we read the geometry block.
	 */

	if (drive_status->drs & DRS_FAULT)
		printf("hdc: clearing fault on unit #%d.\n",unit);
	if ( !(drive_status->drs  &  DRS_ONLINE)) {
		if ( drive_status->drs  &  DRS_ON_CYLINDER )
			printf("hdc: unit #%d is not online.\n",unit);
	        return FALSE;
E 3
I 3
D 4
	printf("hd%d: ", ctlr);
	switch(code) {
#define	P(op, msg)	case op: printf("%s\n", msg); return;
	P(0x0100, "Invalid command code")
	P(0x0221, "Total longword count too large")
	P(0x0222, "Total longword count incorrect")
	P(0x0223, "Longword count of zero not permitted")
	P(0x0231, "Too many data chained items")
	P(0x0232, "Data chain not permitted for this command")
	P(0x0341, "Maximum logical cylinder address exceeded")
	P(0x0342, "Maximum logical head address exceeded")
	P(0x0343, "Maximum logical sectoraddress exceeded")
	P(0x0351, "Maximum physical cylinder address exceeded")
	P(0x0352, "Maximum physical head address exceeded")
	P(0x0353, "Maximum physical sectoraddress exceeded")
	P(0x0621, "Control store PROM revision incorrect")
	P(0x0642, "Power fail detected")
	P(0x0721, "Sector count test failed")
	P(0x0731, "First access test failed")
	P(0x0811, "Drive not online")
	P(0x0812, "Drive not ready")
	P(0x0813, "Drive seek error")
	P(0x0814, "Drive faulted")
	P(0x0815, "Drive reserved")
	P(0x0816, "Drive write protected")
	P(0x0841, "Timeout waiting for drive to go on-cylinder")
	P(0x0851, "Timeout waiting for a specific sector address")
	P(0x0921, "Correctable ECC error")
	P(0x0A11, "Attempt to spill-off of physical boundary")
	P(0x0A21, "Attempt to spill-off of logical boundary")
	P(0x0A41, "Unknown DDC status (PSREAD)")
	P(0x0A42, "Unknown DDC status (PSWRITE)")
	P(0x0A51, "Track relocation limit exceeded")
	P(0x0C00, "HFASM")
	P(0x0C01, "data field error")
	P(0x0C02, "sector not found")
	P(0x0C03, "sector overrun")
	P(0x0C04, "no data sync")
	P(0x0C05, "FIFO data lost")
	P(0x0C06, "correction failed")
	P(0x0C07, "late interlock")
	P(0x0D21, "Output data buffer parity error")
	P(0x0D31, "Input data transfer FIFO indicates overflow")
	P(0x0D32, "Input data buffer FIFO indicates overflow")
	P(0x0D41, "Longword count != 0 indicates underflow")
	P(0x0D42, "Output data buffer FIFO indicates underflow")
	P(0x0E01, "FT timeout -- DDC interrupt")
	P(0x0E02, "RDDB timeout -- IDTFINRDY -- and DDC interrupt")
	P(0x0E03, "RDDB timeout -- DDC interrupt")
	P(0x0E04, "RDDB timeout -- writing ZERO's to IDTF")
	P(0x0E05, "RDDB timeout -- IDTFINRDY -- and IDBFEMPTY+")
	P(0x0E06, "WRDB timeout -- ODTFOUTRDT -- and DDC interrupt")
	P(0x0E07, "WRDB timeout -- ODTFOUTRDT -- and DDC interrupt")
	P(0x0E08, "WRDB timeout -- DDC interrupt")
	P(0x0E09, "WRDB timeout -- ODBFFULL+ and DDC interrupt")
	P(0x0E0A, "VLT timeout -- DDC interrupt")
	P(0x0E0B, "WRBA timeout -- ODTFOUTRDY-")
	P(0x0F00, "Error log full")
	default:
		if (code >= 0x0B00 && code <= 0x0BFF)
			printf("Unknown DDC status type 0x%x.", code&0xff);
		else
			printf("Unknown error %lx\n", code);
E 3
	}
E 4
I 4
	printf("hd%d: error %lx\n", ctlr, code);
E 4
D 3

	/*
	 * Read the geometry block from the start of the drive
	 * definition cylinder, validate it (must have the correct
	 * header and checksum), and set partition starts and sizes
	 * (definition partition has already been set above).
	 */

 	geo = (geometry_block *) hu->phio_data;
	mcb->command      = HCMD_READ;
	mcb->cyl          = hu->def_cyl;
	mcb->head         = 0;
	mcb->sector       = 0;
	mcb->chain[0].lwc = sizeof(geometry_sector) / 4;
	mcb->chain[0].ta  = (unsigned long) vtoph(0,geo);
	if (!hdimcb(hu,mcb))
		goto badgeo;
 	if ( geo->version > 64000  ||  geo->version < 0 ) {
 		printf("hdc: bad geometry block version# on unit #%d\n",unit);
		goto badgeo;
	}
	if (strcmp(&geo->id[0],GB_ID) != 0) {
		printf("hdc: bad geometry block header on unit #%d\n",unit);
		goto badgeo;
	}
 	GB_CHECKSUM( geo, i );
 	if ( ((geometry_sector *)geo)->checksum != i) {
 		printf("hdc: bad geometry block checksum on unit #%d\n",unit);
 		goto badgeo;
	}
	for (i=0; i<GB_MAXPART; i++) {
		if (i==HDC_DEFPART) continue;
		hu->partition[i].start  = geo->partition[i].start;
		hu->partition[i].length = geo->partition[i].length;
	}
	return TRUE;

	/*
	 * If the geometry block is bad, return ok status so that
	 * the disk can be formatted etc, but zero the partitions
	 * so that no one except "format" can read/write the disk.
	 */

badgeo: for (i=0; i<GB_MAXPART; i++) {
		if (i==HDC_DEFPART) continue;
		hu->partition[i].start  = 0;
		hu->partition[i].length = 0;
	}
	return TRUE;
E 3
}

D 3
/*************************************************************************
*  Procedure:	hdstrategy
*
*  Description: The hdc strategy routine. It is called by the kernel
*               to do a disk operation  ('physio' if raw i/o, the block
*               i/o routines if block i/o); i.e. this is the point where
*               raw i/o and block i/o merge. This routine is also called
*               internally by this handler to do misc disk operations.
*
*  Returns:
**************************************************************************/

hdstrategy(bp)

register struct buf *bp;	/* This buf structure contains info
       				 * describing the requested disk xfer.
				 */
E 3
I 3
#ifdef COMPAT_42
hdreadgeometry(dk)
	struct dksoftc *dk;
E 3
{
D 3
	register hdc_unit_type	 *hu;	   /* hdc device unit info     */
	register mcb_type	 *mcb;	   /* the mcb built here       */
	register int		 vaddr;    /* virtual address of data  */
	hdc_ctlr_type		 *hc;	   /* hdc controller info      */
	int			 sector;   /* absolute sector number   */
	int			 unit;	   /* minor device unit#       */
	int			 par;	   /* disk partition number    */
	int			 blocks;   /* number of blocks to xfer */
	int			 priority; /* processor level save     */
	int			 bytes;	   /* bytecount requested      */
	int			 i;	   /* temporary                */
E 3
I 3
	static geometry_sector geometry;
	register struct mcb *mcb;
	register struct disklabel *lp;
	geometry_block *geo;
	int cnt;
E 3

	/*
D 3
	 * Initialize pointers and data.
E 3
I 3
	 * Read the geometry block (at head = 0 sector = 0 of the drive
	 * definition cylinder), validate it (must have the correct version
	 * number, header, and checksum).
E 3
	 */
D 3

	unit = HDC_UNIT(bp->b_dev);
	par = HDC_PARTITION(bp->b_dev);
	hu = &hdc_units[unit];
	hc = &hdc_ctlrs[hu->ctlr];
	bytes = bp->b_bcount;
	vaddr = (int) bp->b_un.b_addr;

	/*
	 * Make some preliminary checks of the i/o request.
	 * Terminate the i/o immediately if: the request is for zero
	 * bytes or more than 32k bytes; the xfer does not start or
	 * end on a longword boundary.
	 * "format" sometimes requires bytes=0; e.g. for verify and
	 * format ioctls.
	 */

	if (bytes==0 || bytes>32*1024)
		if (!hu->format) goto enxio;
	if ( (bytes&3) || (vaddr&3) )
		goto efault;

	/*
	 * Round up requested byte count to a multiple of the block size.
	 * If the transfer would exceed the end of the partition,
	 * truncate the byte count at the partition boundary (except that
	 * the format program is allowed to access the entire disk).
	 * Determine absolute sector number of the start of the transfer
	 * (requested start plus the start of the partition).
	 */

	{
		register int par_start;  /* partition start blk */
		register int par_length; /* partition blk count */

		par_start = hu->partition[par].start;
		par_length= hu->partition[par].length;
		blocks = (bytes + DEV_BSIZE - 1) >> DEV_BSHIFT;
		if ( par_length < (bp->b_blkno + blocks) )
			if ( !hu->format) {
				blocks = par_length - bp->b_blkno;
				if(blocks <= 0) goto enxio;
				bytes = blocks * DEV_BSIZE;
			}
		sector = HDC_SPB * (bp->b_blkno + par_start);
E 3
I 3
	mcb = &dk->dk_mcb;
	mcb->command = HCMD_READ;
	mcb->cyl = dk->dk_def_cyl;
	mcb->head = 0;
	mcb->sector = 0;
	mcb->chain[0].wcount = sizeof(geometry_sector) / sizeof(long);
	mcb->chain[0].memadr  = (u_long)vtoph((struct process *)0, &geometry);
	/* mcb->chain[0].memadr = (long)&geometry; */
	if (hdimcb(dk)) {
 		printf("hd%d: can't read default geometry.\n", dk->dk_unit);
		return(1);
E 3
	}
D 3

	/*
	 * Insure that nobody except the format program writes to
	 * the drive definition tracks in partition 7.
	 * Note: they may access other tracks in partition 7
	 * (i.e. diagnostic tracks).
	 */

	if (par==HDC_DEFPART)
		if (!hu->format && !(bp->b_flags & B_READ))
		{
			register int defs;  /* definition cyl start */
			register int defe;  /* (def cylinder end)+1 */

			defs = hu->def_cyl * hu->spc;
			defe = defs + hu->def_cyl_count * hu->spc;
	        	if (sector < defe && (sector + blocks * HDC_SPB) > defs)
				goto eacces;
		}

	/*
	 * Get a free mcb. Wait if no mcb's are available
	 */

	priority = spl7();
get:	mcb = hc->forw_free;
	remque(mcb);
	asm(" bvc got");
	slumber(hc, 0, iocomboost);
	goto get;
got:    asm("got:");
	splx(priority);

	/*
	 * Fill in the mcb with information about the xfer.
	 *
	 * Currently everything is given equal priority.
	 * Keep a pointer to the buf associated with the mcb.
	 * Add virtual address of this mcb to the software context
	 * word of the mcb; the hdc firmware copies this word to
	 * the master mcb when the mcb is complete.
	 *
	 * If the buf was sent locally by this handler (via 'hdphysio')
	 * then there may be commands other than just read or write.
	 * 'hdphysio' also provides a cylinder/head/sector address.
	 */

	{
		/*
		 * The following priority calculation is based on the
		 * real time functional specification.
		 */
		register struct  proc *p = u.u_procp;
		mcb->priority = 0;
		if ((p->p_ppid) &&	/* not a system process */
		    ((p->p_nice < MIN_NON_RT_NICE_VAL) ||
                     (rt_disk_scheduling))) {
			mcb->priority = 32 - p->p_basepri;
		}
E 3
I 3
	geo = &geometry.geometry_block;
 	if (geo->version > 64000  ||  geo->version < 0) {
 		printf("hd%d: bad default geometry version#.\n", dk->dk_unit);
		return(1);
E 3
	}
D 3

	mcb->interrupt = TRUE;
	mcb->drive     = hu->slave;
	mcb->buf_ptr   = bp;
	mcb->context   = (unsigned long) mcb;
	if (bp->b_flags & B_LOCALIO) {
 		mcb->command = bp->b_hdccommand;
		mcb->cyl     = bp->b_cyl;
		mcb->head    = bp->b_head;
		mcb->sector  = bp->b_sector;
E 3
I 3
 	if (bcmp(&geo->id[0], GB_ID, GB_ID_LEN)) {
 		printf("hd%d: bad default geometry header.\n", dk->dk_unit);
		return(1);
E 3
	}
D 3
	else {
		mcb->command = (bp->b_flags & B_READ) ? HCMD_READ:HCMD_WRITE;
		mcb->cyl     = sector/hu->spc;
		mcb->head    = (sector/hu->sectors) % hu->heads;
		mcb->sector  = sector % hu->sectors;
E 3
I 3
	GB_CHECKSUM(geo, cnt);
	if (geometry.checksum != cnt) {
		printf("hd%d: bad default geometry checksum.\n", dk->dk_unit);
		return(1);
E 3
	}
D 3

	/*
	 * Build the data chain - address/count pairs for each page.
	 * The first transfer might not start on a page boundary.
	 * Purge the data cache for pages to be dma'd into.
	 *
	 * There is no attempt to combine physically contiguous
	 * pages into the same data chain, since it is faster
	 * to just dma the extra data chain into the controller
	 * than it is to combine the pages;
	 */

	{
		register struct  proc *procp;	 /* process structure   */
		register int	 bc;		 /* bytecount this page */
		register int	 bcremain=bytes; /* bytecount remaining */

		if ( bp->b_flags & B_DIRTY )
			procp = (struct proc *) &proc[2] ;
		else
			procp = bp->b_proc;
D 2
		if (bp->b_flags & B_READ) mtpr(vaddr,P1DC);
E 2
I 2
		if (bp->b_flags & B_READ)
			mtpr(P1DC, vaddr);
E 2
		bc = min( bcremain, (NBPG-(vaddr&(NBPG-1))) );
		mcb->chain[0].ta = vtoph(procp,vaddr);
		mcb->chain[0].lwc = bc/4;
D 2
		bcremain -= bc;
		i = 0;
		while (bcremain>0) {
	        	vaddr += bc;
			if (bp->b_flags & B_READ) mtpr(vaddr,P1DC);
			bc = min(bcremain,NBPG);
E 2
I 2
		for (bcremain -= bc, i = 0; bcremain > 0;) {
			vaddr += bc;
			if (bp->b_flags & B_READ)
				mtpr(P1DC, vaddr);
			bc = min(bcremain, NBPG);
E 2
			mcb->chain[i].lwc |= LWC_DATA_CHAIN;
			i++;
			mcb->chain[i].ta = vtoph(procp,vaddr);
			mcb->chain[i].lwc= bc/4;
D 2
	        	bcremain -= bc;
E 2
I 2
			bcremain -= bc;
E 2
		}
E 3
I 3
	lp = &dk->dk_label;
I 4

E 4
	/* 1K block in Harris geometry; convert to sectors for disklabels */
	for (cnt = 0; cnt < GB_MAXPART; cnt++) {
		lp->d_partitions[cnt].p_offset =
		    geo->partition[cnt].start * (1024 / lp->d_secsize);
		lp->d_partitions[cnt].p_size =
		    geo->partition[cnt].length * (1024 / lp->d_secsize);
E 3
	}
D 3

	/*
	 * Set up information for error logging and system activity
	 * for programs such as iostat, sadp, sadc, sar, sag.
	 * Time-stamp the buf (and the unit if it is just becoming busy).
	 * Record the total number of transfer operations and the total
	 * no. of 512-byte blocks xferred.
	 * Turn on the activity bit for this device - for error logging.
	 */

	bp->b_start = time.tv_sec;
	if (vdtab[unit].b_active++ == 1)
		vdtab[unit].io_start = time.tv_sec;
	vdstat[unit].io_cnt++;
	vdstat[unit].io_bcnt += blocks * HDC_SPB;
	blkacty |= (1 << major(bp->b_dev));
	dk_wds[unit] += bytes/32;
  	dk_busy |= 1 << unit;

	/*
	 * If the controller has active mcb's:
	 *    don't send this mcb until the next interrupt occurs.
	 *
	 * Otherwise:
	 *    1) add the mcb to the active queue;
	 *    2) physically link the mcb from the master mcb;
	 *    3) fill in the master mcb;
	 *    4) tell the hdc to scan the new mcb.
	 */

	{
		register master_mcb_type *master; /* hdc's master mcb */

		master= &hc->master_mcb;
		priority = spl7();
		if ( hc->forw_active != (mcb_type *) &hc->forw_active ) {
	        	insque(mcb, &hc->forw_wait);
#ifdef HDCLOG
			hdlog(mcb,4 + 16*hc->ctlr);
#endif
		}
		else
		{
			insque(mcb, &hc->forw_active);
			master->forw_phaddr = mcb->mcb_phaddr;
			mcb->forw_phaddr = 0;
			master->mcs = 0;
#ifdef HDCLOG
			hdlog(mcb,5 + 16*hc->ctlr);
#endif
			HDC_REGISTER(master_mcb_reg) = hc->master_phaddr;
		}
		splx(priority);
	}

	/*
	 * Returns.
	 */

	return;
eacces:	bp->b_error = EACCES;
	goto errcom;
efault:	bp->b_error = EFAULT;
	goto errcom;
enxio:	bp->b_error = ENXIO;
errcom:	bp->b_flags |= B_ERROR;
	bp->b_resid = bytes;
	iodone(bp);
E 3
I 3
	lp->d_npartitions = GB_MAXPART;
	return(0);
E 3
}
D 3

D 2
/*************************************************************************
*  Procedure:	hdwrite
*
*  Description:	Character device write routine. It is called by the
*               inode read/write routine 'ino_rw'.
*
*  Returns:     The error status returned by 'physio'.
**************************************************************************/
E 2
I 2
hdread(dev, uio)
	dev_t dev;
	int *uio;
{
	hdc_unit_type	*hu;
E 2

D 2
int
hdwrite(dev, uio)
E 2
I 2
	hu = &hdc_units[HDC_UNIT(dev)];
	return(physio(hdstrategy, &hu->raw_buf, dev, B_READ, minphys, uio));
}
E 2

D 2

dev_t		dev;	/* Device type. Major/minor dev#.
			 */
int		*uio;	/* Pointer to a uio structure describing
			 * a write request: buffer address;
			 * sector offset; no. of sectors; etc.
			 */
E 2
I 2
hdwrite(dev, uio)
	dev_t dev;
	int *uio;
E 2
{
D 2
	hdc_unit_type	*hu;	/* hdc unit information   */
E 2
I 2
	hdc_unit_type	*hu;
E 2

D 2
	hu = &hdc_units[ HDC_UNIT(dev) ];

	/*
	 * 'physio' builds the buf structure, locks the user pages, calls
	 * 'hdstrategy' to do the write, waits until i/o is complete
	 * (iodone), deallocates the buf structure, and unlocks the pages.
	 */

	return physio(
		hdstrategy,	/* hdc's strategy routine	    */
		&hu->raw_buf,	/* physio builds a buf struct here  */
		dev,		/* major/minor device number	    */
		B_WRITE,	/* write the buffer		    */
		minphys,	/* routine to set max transfer size */
		uio);		/* describes the transfer request   */
E 2
I 2
	hu = &hdc_units[HDC_UNIT(dev)];
	return(physio(hdstrategy, &hu->raw_buf, dev, B_WRITE, minphys, uio));
E 2
}
E 3
I 3
#endif /* COMPAT_42 */
#endif /* NHD */
E 3
E 1
