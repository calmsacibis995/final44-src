h17881
s 00001/00001/00250
d D 7.11 91/05/04 16:21:04 bostic 12 11
c READ, WRITE -> F_READ, F_WRITE
e
s 00003/00003/00248
d D 7.10 90/12/16 16:44:51 bostic 11 10
c kernel reorg
e
s 00000/00003/00251
d D 7.9 90/06/30 23:48:30 karels 10 9
c make it compile again
e
s 00001/00011/00253
d D 7.8 90/06/28 22:24:48 bostic 9 8
c new copyright notice
e
s 00010/00008/00254
d D 7.7 90/06/22 18:48:20 root 8 7
c "root" has had these files checked out forever; seem to all be include
c file changes. -- TK
e
s 00002/00002/00260
d D 7.6 89/05/01 10:06:23 bostic 7 6
c label offset calculation incorrect
e
s 00182/00511/00080
d D 7.5 88/11/01 16:54:58 bostic 6 5
c this works with our kernel, probably won't have to change too
c much more
e
s 00124/00161/00467
d D 7.4 87/12/28 13:58:44 bostic 5 3
c final reformatting
e
s 00107/00141/00487
d R 7.4 87/12/28 13:52:13 bostic 4 3
c more reformatting
e
s 00210/00237/00418
d D 7.3 87/10/28 10:44:17 bostic 3 2
c reformat, supply error codes to hdopen, stylistic changes
e
s 00063/00052/00592
d D 7.2 87/10/27 18:49:12 bostic 2 1
c version that compiles with our standalone routines and reads 
c the Harris disk geometry
e
s 00644/00000/00000
d D 7.1 87/10/23 12:39:36 bostic 1 0
c date and time created 87/10/23 12:39:36 by bostic
c original Harris source code
e
u
U
t
T
I 1
/*
D 6
 * Stand alone driver for the HDC controller
E 6
I 6
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 6
I 2
 *
I 6
 * This code is derived from software contributed to Berkeley by
 * Harris Corp.
 *
D 9
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 9
I 9
 * %sccs.include.redist.c%
E 9
 *
E 6
 *	%W% (Berkeley) %G%
E 2
 */
I 2
D 6
#define	KERNEL
E 6
E 2

D 2
#define KERNEL
E 2
I 2
D 6
#include "machine/mtpr.h"
I 5

E 6
E 5
D 8
#include "param.h"
D 5
#include "systm.h"
#include "buf.h"
#include "time.h"
E 5
#include "inode.h"
#include "fs.h"
I 5
#include "buf.h"
E 5
#include "ioctl.h"
D 5
#include "tahoevba/dsk.h"
#include "tahoevba/dskio.h"
#include "tahoevba/hdc.h"
E 5
I 5
#include "disklabel.h"
E 8
I 8
#include "sys/param.h"
#include "sys/time.h"
D 10
#include "sys/vnode.h"
#include "ufs/inode.h"
#include "ufs/fs.h"
E 10
#include "sys/buf.h"
#include "sys/ioctl.h"
#include "sys/disklabel.h"
E 8
E 5
D 11
#include "saio.h"
I 6
D 8
#include "../tahoe/mtpr.h"
#include "../tahoevba/hdreg.h"
E 8
I 8
#include "tahoe/mtpr.h"
#include "tahoevba/hdreg.h"
E 11
I 11
#include "stand/saio.h"
#include "../include/mtpr.h"
#include "../vba/hdreg.h"
E 11
E 8
E 6
E 2

I 5
D 6
#include "../tahoevba/dsk.h"
#include "../tahoevba/dskio.h"
#include "../tahoevba/hdc.h"
E 6
I 6
static struct registers *hdc_regs[HDC_MAXCTLR][HDC_MAXBUS];
static struct disklabel dklabel[HDC_MAXDRIVE][HDC_MAXCTLR][HDC_MAXBUS];
E 6

E 5
D 2
#include "../uts/machine/ml/mtpr.h"
#include "../uts/machine/sys/param.h"
#include "../uts/machine/sys/systm.h"
#include "../uts/machine/sys/buf.h"
#include "../uts/machine/sys/time.h"
#include "../uts/machine/sys/vnode.h"
#include "../uts/machine/ufs/inode.h"
#include "../uts/machine/ufs/fs.h"
#include "../uts/machine/sys/vbavar.h"
#include "../uts/machine/sys/ioctl.h"
#include "../uts/machine/sys/dsk.h"
#include "../uts/machine/sys/dskio.h"
#include "../uts/machine/sys/hdc.h"
#include "../stand/saio.h"
E 2
I 2
D 6
#define	NHD		4
#define	NDRIVE		8		/* drives per controller */
#define	HDSLAVE(x)	((x) % NDRIVE)
#define	HDCTLR(x)	((x) / NDRIVE)
E 2

I 5
#define	HDC_DEFBUS	0		/* we only handle bus zero, for now */
E 5
D 2
#define HDREG(x)	(ctlr_addr->x)	/* standalone io to an hdc register */
E 2
I 2
#define	HDREG(x)	(ctlr_addr->x)	/* standalone io to an hdc register */
#define	HID_HDC		0x01		/* hvme_id for HDC */
E 2

/*
 * hdc controller table. It contains information about the hdc controller.
 */
D 3

E 3
typedef struct {
D 5
	int		ctlr;		/* controller number (0-15)         */
E 5
I 5
	int		ctlr;		/* controller number (0-15) */
E 5
	hdc_regs_type	*registers;	/* base address of hdc io registers */
D 5
	hdc_mid_type	mid;		/* the module id is read to here    */
D 3
	master_mcb_type master_mcb;	/* the master mcb for this hdc      */
E 3
I 3
	master_mcb_type	master_mcb;	/* the master mcb for this hdc      */
E 5
I 5
	hdc_mid_type	mid;		/* the module id is read to here */
	master_mcb_type	master_mcb;	/* the master mcb for this hdc */
E 5
E 3
	mcb_type	mcb;		/* an mcb for i/o to the controller */
} hdctlr_type;

hdctlr_type hdc_ctlr[HDC_MAXCTLR][HDC_MAXBUS];

/*
 * hdc unit table. It contains information about the hdc drive.
 * Some information is obtained from the profile prom and geometry block.
 */
D 3

E 3
typedef struct {
D 3
	par_tab		partition[GB_MAXPART]; /* partition definitions     */
	int		ctlr;		/* the controller number (0-15)     */
	int		slave;		/* the slave number (0-4)           */
	int		unit;		/* the unit number (0-31)           */
	int		id;		/* identifies the disk model        */
 	int		cylinders;	/* number of logical cylinders      */
	int		heads;		/* number of logical heads          */
	int		sectors;	/* number of logical sectors/track  */
	int		phys_cylinders;	/* number of physical cylinders     */
	int		phys_heads;	/* number of physical heads         */
	int		phys_sectors;	/* number of physical sectors/track */
	int		def_cyl;	/* logical cylinder of drive def    */
	int		def_cyl_count;	/* number of logical def cylinders  */
	int		diag_cyl;	/* logical cylinder of diag area    */
	int		diag_cyl_count;	/* number of logical diag cylinders */
	int		rpm;		/* disk rpm                         */
	int		bytes_per_sec;	/* bytes/sector -vendorflaw conversn*/
	int		format;		/* format program is active         */
	unsigned long	phio_data[HDC_PHIO_SIZE]; /* data for physical io   */
E 3
I 3
D 5
	par_tab	partition[GB_MAXPART];	/* partition definitions            */
	int	ctlr;			/* the controller number (0-15)     */
	int	slave;			/* the slave number (0-4)           */
	int	unit;			/* the unit number (0-31)           */
	int	id;			/* identifies the disk model        */
 	int	cylinders;		/* number of logical cylinders      */
	int	heads;			/* number of logical heads          */
	int	sectors;		/* number of logical sectors/track  */
	int	phys_cylinders;		/* number of physical cylinders     */
	int	phys_heads;		/* number of physical heads         */
E 5
I 5
	par_tab	partition[GB_MAXPART];	/* partition definitions */
	int	ctlr;			/* the controller number (0-15) */
	int	slave;			/* the slave number (0-4) */
	int	unit;			/* the unit number (0-31) */
	int	id;			/* identifies the disk model */
 	int	cylinders;		/* number of logical cylinders */
	int	heads;			/* number of logical heads */
	int	sectors;		/* number of logical sectors/track */
	int	phys_cylinders;		/* number of physical cylinders */
	int	phys_heads;		/* number of physical heads */
E 5
	int	phys_sectors;		/* number of physical sectors/track */
D 5
	int	def_cyl;		/* logical cylinder of drive def    */
	int	def_cyl_count;		/* number of logical def cylinders  */
	int	diag_cyl;		/* logical cylinder of diag area    */
E 5
I 5
	int	def_cyl;		/* logical cylinder of drive def */
	int	def_cyl_count;		/* number of logical def cylinders */
	int	diag_cyl;		/* logical cylinder of diag area */
E 5
	int	diag_cyl_count;		/* number of logical diag cylinders */
D 5
	int	rpm;			/* disk rpm                         */
	int	bytes_per_sec;		/* bytes/sector -vendorflaw conversn*/
	int	format;			/* format program is active         */
	u_long	phio_data[HDC_PHIO_SIZE];	/* data for physical io     */
E 5
I 5
	int	rpm;			/* disk rpm */
	int	bytes_per_sec;		/* bytes/sector -vendorflaw conversn */
	int	format;			/* format program is active */
	u_long	phio_data[HDC_PHIO_SIZE];	/* data for physical io */
E 5
E 3
} hdunit_type;

D 3
hdunit_type hdc_unit [HDC_MAXDRIVE] [HDC_MAXCTLR] [HDC_MAXBUS] ;
E 3
I 3
D 5
hdunit_type hdc_unit [HDC_MAXDRIVE] [HDC_MAXCTLR] [HDC_MAXBUS];
E 5
I 5
hdunit_type	hdc_unit [HDC_MAXDRIVE] [HDC_MAXCTLR] [HDC_MAXBUS];
E 5
E 3

D 5
/*************************************************************************
*  Procedure:	hdopen
*
D 3
*  Description: The hdc open routine. Initializes the hdc and reads the
*               hdc status and the geometry block.
E 3
I 3
*  Description:	The hdc open routine. Initializes the hdc and reads the
*		hdc status and the geometry block.
E 3
*
D 3
*  Returns:     0   open was not successful
*               1   open was successful
*               -1  this is not an hdc controller
E 3
I 3
*  Returns:	 0  open was successful
*		-1  this is not an hdc controller
E 3
**************************************************************************/
E 5
I 5
/*
 * hdopen --
 *	initialize the hdc and read the disk label
 */
E 6
E 5
D 3

E 3
hdopen(io)
D 3

register struct iob	*io ;	/* i/o block
				 */
E 3
I 3
D 6
	register struct iob	*io;	/* i/o block */
E 6
I 6
	register struct iob *io;
E 6
E 3
{
D 5
	mcb_type	*mcb;		/* an mcb to send commands to hdc   */
	hdunit_type	*hu;		/* disk unit information table      */
	hdctlr_type	*hc;		/* hdc ctlr information table       */
	hdc_mid_type	*id;		/* the hdc module id                */
D 3
	geometry_sector geometry;	/* the geometry block sector        */
E 3
I 3
	geometry_sector	geometry;	/* the geometry block sector        */
E 3
	geometry_block	*geo;		/* the geometry block               */
	drive_stat_type	status;		/* the hdc status is read to here   */
D 3
	int		par;		/* partition number                 */
	int	        ctlr;		/* the controller number            */
	int	        drive;		/* the drive number                 */
	int	        bus;		/* the bus number                   */
	int		unit;		/* the unit number		    */
	int	        i;		/* temp                             */
E 3
I 3
	long		ctlr;		/* the controller number            */
E 3
I 2
	long		junk;		/* badaddr will write junk here     */
I 3
	int		par;		/* partition number                 */
	int		drive;		/* the drive number                 */
	int		bus;		/* the bus number                   */
	int		i;		/* temp                             */
E 3
E 2
	hdc_regs_type	*ctlr_addr;	/* hdc i/o registers                */
E 5
I 5
D 6
	drive_stat_type	status;		/* the hdc status is read to here */
	hdc_mid_type	*id;		/* the hdc module id */
	hdc_regs_type	*ctlr_addr;	/* hdc i/o registers */
	hdctlr_type	*hc;		/* hdc ctlr information table */
	hdunit_type	*hu;		/* disk unit information table */
	geometry_sector	geometry;	/* the geometry block sector */
	geometry_block	*geo;		/* the geometry block */
	mcb_type	*mcb;		/* an mcb to send commands to hdc */
	long	junk = 0;		/* badaddr will write junk here */
	int	par;			/* partition number */
	int	bus, ctlr, drive, error, i, unit;
E 6
I 6
	register struct disklabel *dlp;
	struct status status;
	struct module_id id;
	struct registers *hr;
	struct mcb mcb;
	long junk, dlbuf[DEV_BSIZE/sizeof(long)];
E 6
E 5
D 2
	int		junk;		/* badaddr will write junk here     */
E 2

D 2
	par = io->i_part;
	bus = io->i_bus;
	ctlr = io->i_ctlr;
	drive = io->i_drive;
E 2
I 2
D 3
	par = io->i_boff;		/* io->i_part; */
	bus = 0;			/* io->i_bus; */
	ctlr = HDCTLR(io->i_unit);	/* io->i_ctlr; */
	drive = HDSLAVE(io->i_unit);	/* io->i_drive; */
E 3
I 3
D 5
	par = io->i_boff;		/* io->i_part;	*/
	bus = 0;			/* io->i_bus;	*/
	ctlr = HDCTLR(io->i_unit);	/* io->i_ctlr;	*/
	drive = HDSLAVE(io->i_unit);	/* io->i_drive;	*/
E 3
E 2
	hu = &hdc_unit[drive][ctlr][bus];
	hc = &hdc_ctlr[ctlr][bus];
	mcb = &hc->mcb;

	/*
	 * Validate the device specification
	 */
D 3

E 3
D 2
	if (ctlr < 1 || ctlr > HDC_MAXCTLR)
		return( -1 );
E 2
I 2
	if (ctlr >= HDC_MAXCTLR) {
E 5
I 5
	/* validate the device specification */
D 6
	if ((ctlr = HDCTLR(io->i_unit)) >= HDC_MAXCTLR) {
E 5
		printf("invalid controller number\n");
D 3
		return (ENXIO);
E 3
I 3
		return(ENXIO);
E 3
	}
E 2
D 3
	if (drive < 0 || drive > (HDC_MAXDRIVE-1)) {
E 3
I 3
D 5
	if (drive < 0 || drive > HDC_MAXDRIVE - 1) {
E 5
I 5
	if ((drive = HDSLAVE(io->i_unit)) < 0 || drive > HDC_MAXDRIVE - 1) {
E 5
E 3
		printf("hdc: bad drive number.\n");
E 6
I 6
	if ((u_int)io->i_bus >= HDC_MAXBUS)
		return(EADAPT);
	if ((u_int)io->i_ctlr >= HDC_MAXCTLR)
		return(ECTLR);
	if ((u_int)io->i_unit >= HDC_MAXDRIVE)
E 6
D 2
		return( 0 );
E 2
I 2
D 3
		return( 1 );
E 3
I 3
		return(EUNIT);
E 3
E 2
D 6
	}
D 5
	if (par < 0 || par > 7) {
E 5
I 5
	if ((par = io->i_boff) < 0 || par > 7) {
E 5
		printf("hdc: bad partition number.\n");
D 2
		return( 0 );
E 2
I 2
D 3
		return( 1 );
E 3
I 3
		return(EUNIT);
E 3
E 2
	}
D 2
	io->i_ctlr_addr =    bus == 0 ?
E 2
I 2
D 5
	ctlr_addr = (hdc_regs_type *)(bus == 0 ?
E 2
		0xC0000000 | ctlr << 24 | HDC_MID << 16  :
D 2
		0x80000000 | ctlr << 24 | HDC_MID << 16;
	ctlr_addr = (hdc_regs_type *) io->i_ctlr_addr;
E 2
I 2
		0x80000000 | ctlr << 24 | HDC_MID << 16);
E 5
I 5
	bus = HDC_DEFBUS;
E 6
I 6
	if ((u_int)io->i_part > 7)
		return(EPART);
E 6
E 5
D 3
	/* ctlr_addr = (hdc_regs_type *) io->i_ctlr_addr; */
E 3
E 2

D 5
	/*
	 * Init drive structure.
	 */
E 5
I 5
D 6
	ctlr_addr = (hdc_regs_type *)(bus ?
		0x80000000 | ctlr << 24 | HDC_MID << 16 :
		0xC0000000 | ctlr << 24 | HDC_MID << 16);

	hu = &hdc_unit[drive][ctlr][bus];
	hc = &hdc_ctlr[ctlr][bus];
	mcb = &hc->mcb;

E 6
	/* init drive structure. */
E 5
D 3

E 3
D 6
	hu->slave = drive;
	hc->registers = ctlr_addr;
E 6
I 6
	hdc_regs[io->i_ctlr][io->i_bus] = hr = (struct registers *)(io->i_bus ?
	    0x80000000 | io->i_ctlr << 24 | HDC_MID << 16 :
	    0xC0000000 | io->i_ctlr << 24 | HDC_MID << 16);
E 6

D 5
	/*
	 * Insure that this is an hdc, then reset the hdc.
	 */
D 2

	if (badaddr(&ctlr_addr->module_id_reg,4,&junk))
  		return( -1 );
E 2
I 2
	junk = 0;
E 5
I 5
	/* insure that this is an hdc, then reset the hdc. */
E 5
D 6
	if (wbadaddr(&ctlr_addr->module_id_reg, 4, &junk)) {
D 3
		printf("hd%d: %x: invalid csr\n", ctlr, ctlr_addr);
		return (ENXIO);
E 3
I 3
		printf("hd%d: %x: invalid csr\n", ctlr, (u_int)ctlr_addr);
E 6
I 6
	if (wbadaddr(&hr->module_id, 4, &junk)) {
		printf("hd%d: %x: invalid csr\n", io->i_ctlr, (u_int)hr);
E 6
		return(ENXIO);
E 3
	}
E 2
D 6
	HDREG(soft_reset_reg) = 0;
E 6
I 6
	hr->soft_reset = 0;
E 6
	DELAY(1000000);

	/*
D 3
	 * Read in the hdc module id word.
	 * The controller is bad if the hdc's writeable control
	 * store is not loaded or if the hdc failed the
	 * functional integrity test for any reason.
E 3
I 3
D 6
	 * Read in the hdc module id word.  The controller is bad if the
E 6
I 6
	 * read in the hdc module id word.  The controller is bad if the
E 6
	 * hdc's writeable control store is not loaded or if the hdc failed
	 * the functional integrity test for any reason.
E 3
	 */
D 3

E 3
D 6
	id = &hc->mid;
D 3
	HDREG(module_id_reg) = (unsigned long) id;
E 3
I 3
	HDREG(module_id_reg) = (u_long)id;
E 6
I 6
	hr->module_id = (u_long)&id;
E 6
E 3
	DELAY(10000);
D 2
	mtpr(0,PADC);
E 2
I 2
	mtpr(PADC, 0);
I 5
D 6

E 5
E 2
D 3
	if (id->module_id != (unsigned char) HDC_MID) {
		printf("hdc: Controller bad module id: id= %x\n",id->module_id);
		return( -1 );
E 3
I 3
	if (id->module_id != (u_char)HDC_MID) {
		printf("hdc: Controller bad module id: id = %x\n",
		    id->module_id);
E 6
I 6
	if (id.module_id != (u_char)HDC_MID) {
		printf("hdc: controller bad module id: id = %x\n",
		    id.module_id);
E 6
D 5
		return(-1);
E 5
I 5
		return(ENXIO);
E 5
E 3
	}
D 3
	if (id->code_rev == (unsigned char) 0xFF ) {
		printf("hdc:  Controller micro-code is not loaded.\n");
D 2
		return( 0 );
E 2
I 2
		return( 1 );
E 3
I 3
D 6
	if (id->code_rev == (u_char)0xFF) {
		printf("hdc: Controller micro-code is not loaded.\n");
E 6
I 6
	if (id.code_rev == (u_char)0xff) {
		printf("hdc: controller micro-code is not loaded.\n");
E 6
		return(ENXIO);
E 3
E 2
	}
D 3
	if (id->fit != (unsigned char) 0xFF ) {
		printf("hdc:  Controller FIT test failed: error= %x\n",id->fit);
D 2
		return( 0 );
E 2
I 2
		return( 1 );
E 3
I 3
D 6
	if (id->fit != (u_char)0xFF) {
		printf("hdc:  Controller FIT test failed: error= %x\n",
		    id->fit);
E 6
I 6
	if (id.fit != (u_char)0xff) {
		printf("hdc: controller FIT test failed: error= %x\n",
		    id.fit);
E 6
		return(ENXIO);
E 3
E 2
	}

D 5
	/*
	 * Read the drive status. Save important info.
	 */
E 5
I 5
D 6
	/* Read the drive status. Save important info. */
E 5
D 3

E 3
	mcb->command = HCMD_STATUS;
	mcb->drive = drive;
	mcb->cyl = 0;
	mcb->head = 0;
	mcb->sector = 0;
D 3
	mcb->chain[0].lwc = (long) sizeof(drive_stat_type) / 4;
	mcb->chain[0].ta  = (long) &status;
E 3
I 3
D 5
	mcb->chain[0].lwc = (long)sizeof(drive_stat_type) / 4;
E 5
I 5
	mcb->chain[0].lwc = (long)sizeof(drive_stat_type) / sizeof(long);
E 5
	mcb->chain[0].ta  = (long)&status;
E 3
	if (hdmcb(mcb, io))
E 6
I 6
	/* read the drive status */
	mcb.command = HCMD_STATUS;
	mcb.drive = io->i_unit;
	mcb.cyl = 0;
	mcb.head = 0;
	mcb.sector = 0;
	mcb.chain[0].wcount = (long)(sizeof(struct status) / sizeof(long));
	mcb.chain[0].memadr = (long)&status;
	if (hdimcb(&mcb, io))
E 6
D 2
		return( 0 );
E 2
I 2
D 3
		return( 1 );
E 3
I 3
		return(EIO);
I 5

	/*
	 * Report drive down if anything in the drive status is bad.
	 * If fault condition, reading will try to clear the fault.
	 */
D 6
	if (status.drs & DRS_FAULT)
E 6
I 6
	if (status.drs&DRS_FAULT)
E 6
		printf("hdc: clearing drive fault.\n");
D 6
	if (!(status.drs & DRS_ONLINE)) {
E 6
I 6
	if (!(status.drs&DRS_ONLINE)) {
E 6
		printf("hdc: drive is not online.\n");
		return(EIO);
	}

E 5
E 3
E 2
D 6
	hu->cylinders = status.max_cyl+1;
	hu->heads = status.max_head+1;
	hu->sectors = status.max_sector+1;
	hu->def_cyl = status.def_cyl;
	hu->def_cyl_count = status.def_cyl_count;
	hu->diag_cyl = status.diag_cyl;
	hu->diag_cyl_count = status.diag_cyl_count;
	hu->phys_cylinders = status.max_phys_cyl+1;
	hu->phys_heads = status.max_phys_head+1;
	hu->phys_sectors = status.max_phys_sector+1;
	hu->bytes_per_sec = status.bytes_per_sec;
	hu->id = status.id;
	hu->rpm = status.rpm;
	hu->partition[HDC_DEFPART].start=
		hu->def_cyl * hu->sectors * hu->heads / HDC_SPB;
	hu->partition[HDC_DEFPART].length =
		hu->def_cyl_count * hu->sectors * hu->heads / HDC_SPB;
E 6
I 6
	/* read in the pack label */
	mcb.command = HCMD_READ;
	mcb.drive = io->i_unit;
	mcb.cyl = 0;
	mcb.head = 0;
	mcb.sector = LABELSECTOR;
	mcb.chain[0].wcount = (long)(DEV_BSIZE / sizeof(long));
	mcb.chain[0].memadr = (long)dlbuf;
	if (hdimcb(&mcb, io))
		return(ERDLAB);
D 7
	dlp = (struct disklabel *)(dlbuf + LABELOFFSET);
E 7
I 7
	dlp = (struct disklabel *)(dlbuf + (LABELOFFSET / sizeof(long)));
E 7
	if (dlp->d_magic != DISKMAGIC || dlp->d_magic2 != DISKMAGIC)
#ifdef COMPAT_42
	{
		int error;
E 6
D 3
	io->i_boff = hu->partition[HDC_DEFPART].start; /* default */
E 3
I 3
D 5
	io->i_boff = hu->partition[HDC_DEFPART].start;	/* default */
E 5
E 3

D 6
	/*
D 5
	 * Report drive down if anything in the drive status is bad.
	 * If fault condition, reading geo will try to clear the fault.
	 */
D 3

E 3
	if (status.drs & DRS_FAULT)
		printf("hdc: clearing drive fault.\n");
D 3
	if ( !(status.drs & DRS_ONLINE)) {
E 3
I 3
	if (!(status.drs & DRS_ONLINE)) {
E 3
		printf("hdc: drive is not online.\n");
D 2
		return( 0 );
E 2
I 2
D 3
		return( 1 );
E 3
I 3
		return(EIO);
E 3
E 2
	}

	/*
E 5
	 * Read the geometry block (at head=0 sector=0 of the drive
	 * definition cylinder), validate it (must have the correct
	 * version number, header, and checksum).
	 */
D 3

E 3
	geo = &geometry.geometry_block;
	mcb->command = HCMD_READ;
	mcb->drive = drive;
D 5
	mcb->cyl = status.def_cyl;
E 5
I 5
	mcb->cyl = hu->def_cyl;
E 5
	mcb->head = 0;
	mcb->sector = 0;
D 5
	mcb->chain[0].lwc = sizeof(geometry_sector) / 4;
E 5
I 5
	mcb->chain[0].lwc = sizeof(geometry_sector) / sizeof(long);
E 5
D 3
	mcb->chain[0].ta  = (long) &geometry;
E 3
I 3
	mcb->chain[0].ta  = (long)&geometry;
I 5
	io->i_boff = hu->partition[HDC_DEFPART].start;		/* default */
E 5
E 3
	if (hdmcb(mcb, io)) {
 		printf("hdc: could not read geometry block\n");
D 3
		return( 1 );
E 3
I 3
		return(EIO);
E 6
I 6
		if (error = hdmaptype(io, dlp, &status, io->i_unit))
			return(error);
E 6
E 3
	}
D 6
	io->i_boff = 0;
D 3
 	if ( geo->version > 64000  ||  geo->version < 0 ) {
E 3
I 3
 	if (geo->version > 64000  ||  geo->version < 0) {
E 3
 		printf("hdc: bad geometry block version#\n");
D 3
		return( 1 );
E 3
I 3
		return(ENXIO);
E 3
	}
D 3
 	if (strcmp(&geo->id[0],GB_ID) != 0) {
E 3
I 3
 	if (strcmp(&geo->id[0], GB_ID) != 0) {
E 3
 		printf("hdc: bad geometry block header\n");
D 3
		return( 1 );
E 3
I 3
		return(ENXIO);
E 3
	}
D 3
	GB_CHECKSUM( geo, i );
E 3
I 3
	GB_CHECKSUM(geo, i);
E 3
	if (geometry.checksum != i) {
		printf("hdc: bad geometry block checksum\n");
D 3
		return( 1 );
E 3
I 3
		return(ENXIO);
E 3
	}

	/*
	 * Set the partition start/size info.
	 * Note: this info was already defaulted to be the disk
	 * definition partition.
	 */
D 3

	if (par != HDC_DEFPART) {
E 3
I 3
	if (par != HDC_DEFPART)
E 3
D 2
		if (geo->partition[par].length == 0)
E 2
I 2
D 5
		if (geo->partition[par].length == 0) {
E 2
			printf("hdc:  null partition\n");
E 5
I 5
		if (geo->partition[par].length == 0) {	/* XXX */
			printf("hdc: null partition\n");
E 5
I 2
D 3
			return ( 1 );
E 3
I 3
			return(ENXIO);
E 3
		}
E 2
		else {
			hu->partition[par].start  = geo->partition[par].start;
			hu->partition[par].length = geo->partition[par].length;
			io->i_boff = hu->partition[par].start;
		}
E 6
I 6
#else
		return(EUNLAB);
#endif
	dklabel[io->i_unit][io->i_ctlr][io->i_bus] = *dlp;
	if (io->i_part >= dlp->d_npartitions ||
	    dlp->d_partitions[io->i_part].p_size == 0)
		return(EPART);
	io->i_boff = (dlp->d_partitions[io->i_part].p_offset *
	    dlp->d_secsize) / DEV_BSIZE;
E 6
D 3
	}
D 2
	return( 1 ) ;
E 2
I 2
	return( 0 ) ;
E 3
I 3
	return(0);
E 3
E 2
}

D 5
/*************************************************************************
*  Procedure:	hdstrategy
*
D 3
*  Description: The hdc strategy routine. This routine does the disk
*               reads/writes. If this is the format program, read/writes
*               are forced to be within the disk definition partition.
E 3
I 3
*  Description:	The hdc strategy routine. This routine does the disk
*		reads/writes. If this is the format program, read/writes
*		are forced to be within the disk definition partition.
E 3
*
D 3
*  Returns:     The number of bytes transfered.
E 3
I 3
*  Returns:	The number of bytes transfered.
E 3
**************************************************************************/
E 5
I 5
D 6
/*
 * hdstrategy --
 *	The hdc strategy routine. This routine does the disk reads/writes. If
 *	this is the format program, read/writes are forced to be within the
 *	disk definition partition.  Returns the number of bytes transferred.
 */
E 6
E 5
D 3

hdstrategy(io,func)

register struct iob	*io ;	/* i/o block
				 */
long			func ;	/* i/o operation to perform
				 */
E 3
I 3
hdstrategy(io, cmd)
D 6
	register struct iob	*io;	/* i/o block */
	int	cmd;			/* i/o operation to perform */
E 6
I 6
	register struct iob *io;
	int cmd;
E 6
E 3
{
D 5
	mcb_type	*mcb;		/* mcb to send to the hdc           */
	hdunit_type	*hu;		/* disk unit information table      */
	hdctlr_type	*hc;		/* hdc ctlr information table       */
	long		err;		/* error code                       */
	long		sector;		/* sector number for i/o            */
D 3
	int		partstart;      /* block number of partition start  */
	int		partlen;        /* number of blocks in partition    */
	int		bytes;          /* number of bytes to transfer      */
E 3
I 3
	int		partstart;	/* block number of partition start  */
	int		partlen;	/* number of blocks in partition    */
	int		bytes;		/* number of bytes to transfer      */
E 3
	int		bus;		/* bus number	                    */
D 3
	int	        ctlr;		/* the controller number            */
	int	        drive;		/* the drive number                 */
E 3
I 3
	int		ctlr;		/* the controller number            */
	int		drive;		/* the drive number                 */
E 5
I 5
D 6
	mcb_type	*mcb;		/* mcb to send to the hdc */
	hdunit_type	*hu;		/* disk unit information table */
	hdctlr_type	*hc;		/* hdc ctlr information table */
	long		err;		/* error code */
	long		sector;		/* sector number for i/o */
	int		partstart;	/* block number of partition start */
	int		partlen;	/* number of blocks in partition */
	int		bytes;		/* number of bytes to transfer */
	int		bus, ctlr, drive;
E 6
I 6
	register struct disklabel *dlp;
	struct mcb mcb;
	long sector;
E 6
E 5
E 3

D 2
	bus = io->i_bus;
	ctlr = io->i_ctlr;
	drive = io->i_drive;
E 2
I 2
D 3
	bus = 0;			/* io->i_bus; */
	ctlr = HDCTLR(io->i_unit);	/* io->i_ctlr; */
	drive = HDSLAVE(io->i_unit);	/* io->i_drive; */
E 3
I 3
D 5
	bus = 0;			/* io->i_bus;	*/
	ctlr = HDCTLR(io->i_unit);	/* io->i_ctlr;	*/
	drive = HDSLAVE(io->i_unit);	/* io->i_drive;	*/
E 5
I 5
D 6
	bus = HDC_DEFBUS;
	ctlr = HDCTLR(io->i_unit);
	drive = HDSLAVE(io->i_unit);
E 5
E 3
E 2
	hu = &hdc_unit[drive][ctlr][bus];
	hc = &hdc_ctlr[ctlr][bus];

	/*
	 * Only the format program can access the disk definition tracks.
	 */
I 3
	if (io->i_boff == HDC_DEFPART && !hu->format) {
		printf("hdc: partition 7 is protected\n");
E 6
I 6
	if (io->i_cc&3) {
		printf("hd%d: i/o not a longword multiple.\n", io->i_unit);
E 6
		return(0);
	}
E 3
D 6

D 2
	if (io->i_part == HDC_DEFPART)
E 2
I 2
D 3
	if (io->i_boff == HDC_DEFPART)
E 2
		if (!hu->format) {
			printf("hdc: partition 7 is protected\n");
			return 0;
		};

E 3
	/*
	 * Insure the transfer fits in the partition.
	 * Set and validate transfer size.
	 */
D 3

D 2
	partstart = hu->partition[io->i_part].start ;
	partlen = hu->partition[io->i_part].length ;
E 2
I 2
	partstart = hu->partition[io->i_boff].start ;
	partlen = hu->partition[io->i_boff].length ;
E 2
	if ( (io->i_bn < partstart) || (io->i_bn >= partstart+partlen) )
		return( 0 ) ;
D 2
	bytes = min( io->i_cc, DEV_BSIZE*(partstart+partlen-io->i_bn) );
E 2
I 2
	bytes = MIN( io->i_cc, DEV_BSIZE*(partstart+partlen-io->i_bn) );
E 3
I 3
	partstart = hu->partition[io->i_boff].start;
	partlen = hu->partition[io->i_boff].length;
	if (io->i_bn < partstart || io->i_bn >= partstart + partlen)
		return(0);
	bytes = MIN(io->i_cc, DEV_BSIZE * (partstart + partlen-io->i_bn));
E 3
E 2
	if (io->i_cc & 3) {
D 3
		printf("hdc:  i/o not a longword multiple\n");
		return 0;
E 3
I 3
		printf("hdc: i/o not a longword multiple\n");
		return(0);
E 3
	}

	/*
	 * Set up the mcb and send it to the hdc.
	 */
D 3

E 3
	mcb = &hc->mcb;
E 6
I 6
	dlp = &dklabel[io->i_unit][io->i_ctlr][io->i_bus];
E 6
	sector = io->i_bn * HDC_SPB;
D 3
	mcb->command = (func == READ) ? HCMD_READ : HCMD_WRITE;
E 3
I 3
D 6
	mcb->command = (cmd == READ) ? HCMD_READ : HCMD_WRITE;
E 3
	mcb->drive = hu->slave;
	mcb->cyl = sector / (hu->sectors * hu->heads);
D 3
	mcb->head = (sector/hu->sectors) % hu->heads;
E 3
I 3
	mcb->head = (sector / hu->sectors) % hu->heads;
E 3
	mcb->sector = sector % hu->sectors;
D 3
	mcb->chain[0].ta  = (unsigned long) io->i_ma;
E 3
I 3
	mcb->chain[0].ta  = (u_long)io->i_ma;
E 3
D 5
	mcb->chain[0].lwc = (bytes + 3) / 4;
E 5
I 5
	mcb->chain[0].lwc = (bytes + 3) / sizeof(long);
E 5
	err = hdmcb(mcb, io);
	io->i_error = err;
D 3
	return (err ? 0 : bytes );
E 3
I 3
	return(err ? 0 : bytes);
E 6
I 6
D 12
	mcb.command = (cmd == READ) ? HCMD_READ : HCMD_WRITE;
E 12
I 12
	mcb.command = (cmd == F_READ) ? HCMD_READ : HCMD_WRITE;
E 12
	mcb.drive = io->i_unit;
	mcb.cyl = sector / dlp->d_secpercyl;
	mcb.head = (sector / dlp->d_nsectors) % dlp->d_ntracks;
	mcb.sector = sector % dlp->d_nsectors;
	mcb.chain[0].wcount = io->i_cc / sizeof(long);
	mcb.chain[0].memadr  = (u_long)io->i_ma;
	return(hdimcb(&mcb, io) ? -1 : io->i_cc);
E 6
E 3
}

D 5
/*************************************************************************
*  Procedure:	hdioctl
*
D 3
*  Description: ioctl routine.
E 3
I 3
*  Description:	ioctl routine.
E 3
*
D 3
*  Returns:     0       no errors
*               non-0    error
E 3
I 3
*  Returns:	0	no errors
*		non-0	error
E 3
**************************************************************************/
E 5
D 3

int
E 3
D 6
hdioctl(io, command, arg)
D 3

struct iob	*io ; 		/* i/o block.
				 */
int		command ;	/* The ioctl commmand.
				 */
int		arg ; 		/* Data. Format depends on ioctl.
				 */
E 3
I 3
	struct iob	*io; 		/* i/o block */
D 5
	int	command;		/* The ioctl commmand */
	int	arg;			/* Data.  Format depends on ioctl */
E 5
I 5
	int	command;		/* ioctl commmand */
	int	arg;			/* data; format depends on ioctl */
E 6
I 6
hdimcb(mcb, io)
	register struct mcb *mcb;
	register struct iob *io;
E 6
E 5
E 3
{
D 3
	mcb_type	*mcb;
	hdunit_type	*hu;		/* disk unit information table      */
	hdctlr_type	*hc;		/* hdc ctlr information table       */
E 3
D 6
	register int	i;
D 3
	int		bus;		/* bus number	                    */
	int	        ctlr;		/* the controller number            */
	int	        drive;		/* the drive number                 */
E 3
I 3
	mcb_type	*mcb;
D 5
	hdunit_type	*hu;		/* disk unit information table	*/
	hdctlr_type	*hc;		/* hdc ctlr information table	*/
	int		bus;		/* bus number			*/
	int		ctlr;		/* the controller number	*/
	int		drive;		/* the drive number		*/
E 5
I 5
	hdunit_type	*hu;		/* disk unit information table */
	hdctlr_type	*hc;		/* hdc ctlr information table */
	int	bus, ctlr, drive;
E 6
I 6
	struct master_mcb master;
	int timeout;
E 6
E 5
E 3

D 2
	bus = io->i_bus;
	ctlr = io->i_ctlr;
	drive = io->i_drive;
E 2
I 2
D 3
	bus = 0;			/* io->i_bus; */
	ctlr = HDCTLR(io->i_unit);	/* io->i_ctlr; */
	drive = HDSLAVE(io->i_unit);	/* io->i_drive; */
E 3
I 3
D 5
	bus = 0;			/* io->i_bus;	*/
	ctlr = HDCTLR(io->i_unit);	/* io->i_ctlr;	*/
	drive = HDSLAVE(io->i_unit);	/* io->i_drive;	*/
E 5
I 5
D 6
	bus = HDC_DEFBUS;
	ctlr = HDCTLR(io->i_unit);
	drive = HDSLAVE(io->i_unit);
E 5
E 3
E 2
	hu = &hdc_unit[drive][ctlr][bus];
	hc = &hdc_ctlr[ctlr][bus];
E 6
I 6
	/* fill in mcb */
	mcb->interrupt = 0;
	mcb->forw_phaddr = 0;
E 6

D 6
	switch (command) {
E 6
I 6
	/* fill in master mcb */
	master.mcw = MCL_IMMEDIATE;
	master.forw_phaddr = (u_long)mcb;
	master.mcs = 0;
E 6

D 6
	case DSKIOCFORMAT: {

		/*
		 * Format a disk track. The received argument is a pointer
		 * to a "formatop" structure describing the track to format.
		 *
		 * Set up a buffer with each longword corresponding to a
		 * sector on the track; a 1 means no flaw, a 0 means a flaw.
		 * Send an mcb to the hdc to format the track.
		 */

		register struct formatop *track;

		if (!hu->format)
E 6
I 6
	hdc_regs[io->i_ctlr][io->i_bus]->master_mcb = (u_long)&master;
	for (timeout = 15000; timeout; --timeout) {
		DELAY(1000);
		mtpr(PADC, 0);
		if (master.mcs&MCS_FATALERROR) {
			printf("hdc%d: fatal error.\n", io->i_ctlr);
E 6
			return(1);
D 3
		track = (struct formatop *) arg;
E 3
I 3
D 6
		track = (struct formatop *)arg;
E 3
		mcb = &hc->mcb;
D 3
		for (i=0; i<hu->phys_sectors; i++)
E 3
I 3
		for (i = 0; i < hu->phys_sectors; i++)
E 3
			hu->phio_data[i] = 1;
D 3
		for (i=0; i<track->flaw_count; i++)
			hu->phio_data[track->flaw[i]]=0;
E 3
I 3
		for (i = 0; i < track->flaw_count; i++)
			hu->phio_data[track->flaw[i]] = 0;
E 3
		mcb->command = HCMD_FORMAT;
		mcb->drive = hu->slave;
D 3
		mcb->chain[0].ta  = (unsigned long) hu->phio_data;
E 3
I 3
		mcb->chain[0].ta  = (u_long)hu->phio_data;
E 3
		mcb->chain[0].lwc = hu->phys_sectors;
		mcb->cyl = track->cylinder;
		mcb->head = track->head;
		mcb->sector = 0;
		if (hdmcb(mcb, io))
D 3
			return EIO;
E 3
I 3
			return(EIO);
E 3
		break;
	}

	case DSKIOCCERTIFY: {

		/*
		 * Certify a disk track. The received argument is a pointer
		 * to a "formatop" structure describing the track to certify.
		 *
		 * Send an mcb to the hdc to certify the track.
		 * The controller returns data in which each longword
		 * corresponds to a sector on the track; a 1 means no flaw,
		 * a 0 means a flaw.
		 */

		register struct formatop *track;

		if (!hu->format)
D 3
			return 1;
		track = (struct formatop *) arg;
E 3
I 3
			return(1);
		track = (struct formatop *)arg;
E 3
		mcb = &hc->mcb;
		mcb->command = HCMD_CERTIFY;
		mcb->drive = hu->slave;
D 3
		mcb->chain[0].ta  = (unsigned long) hu->phio_data;
E 3
I 3
		mcb->chain[0].ta  = (u_long)hu->phio_data;
E 3
		mcb->chain[0].lwc = hu->phys_sectors;
		mcb->cyl = track->cylinder;
		mcb->head = track->head;
		mcb->sector = 0;
		if (hdmcb(mcb, io))
D 3
			return EIO;
E 3
I 3
			return(EIO);
E 3
		track->flaw_count = 0;
D 3
		for (i=0; i<hu->phys_sectors; i++) {
			if (track->flaw_count >= MAXVFLAW) break;
			if (hu->phio_data[i]==0) {
E 3
I 3
		for (i = 0; i < hu->phys_sectors; i++) {
			if (track->flaw_count >= MAXVFLAW)
				break;
			if (hu->phio_data[i] == 0) {
E 3
				track->flaw[track->flaw_count] = i;
				track->flaw_count++;
			}
E 6
		}
D 6
		break;
E 6
I 6
		if (master.mcs&MCS_DONE)
			return(0);
E 6
	}
I 6
D 7
	printf("hdc: controller timed out.\n");
E 7
I 7
	printf("hdc%d: timed out.\n", io->i_ctlr);
E 7
	return(1);
}
E 6

D 6
	case DSKIOCVERIFY: {
E 6
I 6
#ifdef COMPAT_42
hdmaptype(io, dlp, status, unit)
	register struct iob *io;
	register struct disklabel *dlp;
	struct status *status;
	int unit;
{
	geometry_sector geometry;
	geometry_block *geo;
	struct mcb mcb;
	int cnt;
	char *strcpy();
E 6

D 6
		/*
		 * Verify a disk track. The received argument is a pointer
		 * to a "formatop" structure describing the track to verify.
		 */

		register struct formatop *track;

		if (!hu->format)
			return(1);
D 3
		track = (struct formatop *) arg;
E 3
I 3
		track = (struct formatop *)arg;
E 3
		mcb = &hc->mcb;
		mcb->command = HCMD_VERIFY;
		mcb->drive = hu->slave;
		mcb->chain[0].ta  = 0;
		mcb->chain[0].lwc = 0;
		mcb->cyl = track->cylinder;
		mcb->head = track->head;
		mcb->sector = 0;
		if (hdmcb(mcb, io))
D 3
			return EIO;
E 3
I 3
			return(EIO);
E 3
		break;
E 6
I 6
	printf("hd%d: unlabeled\n", unit);
	/*
	 * Read the geometry block (at head = 0 sector = 0 of the drive
	 * definition cylinder), validate it (must have the correct version
	 * number, header, and checksum).
	 */
	mcb.command = HCMD_READ;
	mcb.drive = unit;
	mcb.cyl = status->def_cyl;
	mcb.head = 0;
	mcb.sector = 0;
	mcb.chain[0].wcount = (long)(sizeof(geometry_sector) / sizeof(long));
	mcb.chain[0].memadr = (long)&geometry;
	if (hdimcb(&mcb, io)) {
 		printf("hd%d: can't read default geometry.\n", io->i_unit);
		return(ERDLAB);
E 6
	}
D 6

	case DSKIOCFORMATCTL: {

		/*
		 * This ioctl provides special format control.
		 * Currently the valid arguments are:
		 *
D 3
		 * arg= 0  disable formatting;
E 3
I 3
		 * arg = 0	disable formatting;
E 3
		 *
D 3
		 * arg= 1  enable formatting (allow privileged access);
		 *         formatting must not already be enabled;
		 *         For formatting, change to use partition 7.
E 3
I 3
		 * arg = 1	enable formatting (allow privileged access);
		 *		formatting must not already be enabled;
		 *		For formatting, change to use partition 7.
E 3
		 */

D 3
		if (arg<0 || arg>1)
			return (1);
		if (arg==1) {
			if (hu->format) return (1);
E 3
I 3
		if (arg < 0 || arg > 1)
			return(1);
		if (arg == 1) {
			if (hu->format)
				return(1);
E 3
			/* If not already formatting.... */
D 3
			hu->format = 1 ;
E 3
I 3
			hu->format = 1;
E 3
D 2
			io->i_part = HDC_DEFPART;
E 2
I 2
			/* io->i_part = HDC_DEFPART; */
E 2
			io->i_boff = hu->partition[HDC_DEFPART].start;
		}
		else
D 3
			hu->format = 0 ;
E 3
I 3
			hu->format = 0;
E 3
		break;
E 6
I 6
	geo = &geometry.geometry_block;
 	if (geo->version > 64000  ||  geo->version < 0) {
 		printf("hd%d: bad default geometry version#.\n", io->i_unit);
		return(ENXIO);
E 6
	}
D 6

	case DSKIOCSTATUS: {

		/*
		 * Return info about the disk. Caller's parameter is a
		 * pointer to a dsk_status structure.
		 */

		register dsk_status *status;

D 3
		status = (dsk_status *) arg;
		status->id =		hu->id;
		status->drive_status =	0;
		status->rpm =		hu->rpm;
E 3
I 3
		status = (dsk_status *)arg;
		status->id = hu->id;
		status->drive_status = 0;
		status->rpm = hu->rpm;
E 3
		status->bytes_per_sec = hu->bytes_per_sec;
D 3
		status->cylinders =	hu->cylinders;
		status->heads =		hu->heads;
		status->sectors =	hu->sectors;
		status->phys_cylinders= hu->phys_cylinders;
		status->phys_heads =	hu->phys_heads;
		status->phys_sectors =	hu->phys_sectors;
		status->diag_cyl =	hu->diag_cyl;
		status->diag_cylinders= hu->diag_cyl_count;
		status->def_cyl =	hu->def_cyl;
		status->def_cylinders =	hu->def_cyl_count;
E 3
I 3
		status->cylinders = hu->cylinders;
		status->heads = hu->heads;
		status->sectors = hu->sectors;
		status->phys_cylinders = hu->phys_cylinders;
		status->phys_heads = hu->phys_heads;
		status->phys_sectors = hu->phys_sectors;
		status->diag_cyl = hu->diag_cyl;
		status->diag_cylinders = hu->diag_cyl_count;
		status->def_cyl = hu->def_cyl;
		status->def_cylinders = hu->def_cyl_count;
E 3
		break;
E 6
I 6
 	if (strcmp(&geo->id[0], GB_ID)) {
 		printf("hd%d: bad default geometry header.\n", io->i_unit);
		return(ENXIO);
E 6
	}
D 6

	case DSKIOCVENDORFLAW: {

		/*
		 * Return vendor flaw info.
		 *
		 * Read in the vendor data (data for each track is at
		 * relative sector 0 of the track); then copy the
		 * vendor flaw data to the caller's buffer.
		 */

		register vflaw_type *vflaw;
		register struct flaw *vendor;

		if (!hu->format)
			return(1);
D 3
		vflaw = (vflaw_type *) arg;
E 3
I 3
		vflaw = (vflaw_type *)arg;
E 3
		mcb = &hc->mcb;
		mcb->command = HCMD_VENDOR;
		mcb->drive = hu->slave;
		mcb->chain[0].lwc = HDC_VDATA_SIZE;
D 3
		mcb->chain[0].ta  = (unsigned long) hu->phio_data;
E 3
I 3
		mcb->chain[0].ta  = (u_long)hu->phio_data;
E 3
		mcb->cyl = vflaw->cylinder;
		mcb->head = vflaw->head;
		mcb->sector = 0;
		if (hdmcb(mcb, io))
D 3
			return EIO;
		vendor = (struct flaw *) &hu->phio_data[0];
		for (i=0; i<MAXVFLAW; i++) {
E 3
I 3
			return(EIO);
		vendor = (struct flaw *)&hu->phio_data[0];
		for (i = 0; i < MAXVFLAW; i++) {
E 3
			vflaw->flaw[i].offset = vendor[i].offset;
			vflaw->flaw[i].length = vendor[i].length;
		}
		break;
E 6
I 6
	GB_CHECKSUM(geo, cnt);
	if (geometry.checksum != cnt) {
		printf("hd%d: bad default geometry checksum.\n", io->i_unit);
		return(ENXIO);
E 6
	}
I 6
	for (cnt = 0; cnt < GB_MAXPART; cnt++) {
		dlp->d_partitions[cnt].p_offset = geo->partition[cnt].start;
		dlp->d_partitions[cnt].p_size = geo->partition[cnt].length;
E 6
	}
I 6
#ifdef RAW_SIZE
	dlp->d_secsize = status->bytes_per_sec;
#else
	dlp->d_secsize = 512;
#endif
	dlp->d_nsectors = status->max_sector + 1;
	dlp->d_ncylinders = status->max_cyl + 1;
	dlp->d_ntracks = status->max_head + 1;
	dlp->d_secpercyl = dlp->d_ntracks * dlp->d_nsectors;
	dlp->d_npartitions = GB_MAXPART;
	dlp->d_rpm = status->rpm;
	(void)strcpy(dlp->d_typename, "hdc (prom)");
E 6
D 3
	return 0;
E 3
I 3
	return(0);
E 3
}
D 6

D 5
/*************************************************************************
*  Procedure:	hdmcb
*
D 3
*  Description: Internal routine used to send mcb's to the hdc.
E 3
I 3
*  Description:	Internal routine used to send mcb's to the hdc.
E 3
*
D 3
*  Returns:     0          normal
*               non-zero   error occurred
E 3
I 3
*  Returns:	0		normal
*		non-zero	error occurred
E 3
**************************************************************************/
E 5
I 5
/*
 * hdmcb --
 *	internal routine used to send mcb's to the hdc
 */
static
E 5
D 3

int
E 3
hdmcb(mcb, io)
D 3

register mcb_type	*mcb ;	/* mcb to send to the hdc		    */
register struct iob	*io ;	/* i/o block				    */

E 3
I 3
D 5
	register mcb_type	*mcb;	/* mcb to send to the hdc	*/
	register struct iob	*io;	/* i/o block			*/
E 5
I 5
	register mcb_type	*mcb;	/* mcb to send to the hdc */
	register struct iob	*io;	/* i/o block */
E 5
E 3
{
D 3
	master_mcb_type *master_mcb;	/* the hdc's master mcb             */
	hdctlr_type	*hc;		/* hdc ctlr information table       */
	hdc_regs_type	*ctlr_addr;	/* pointer to hdc i/o registers     */
	int		timeout;	/* used to timeout the mcb          */
	int		bus;		/* bus number	                    */
	int	        ctlr;		/* the controller number            */
	int		i,end;
	unsigned int	*ptr;
E 3
I 3
D 5
	master_mcb_type	*master_mcb;	/* the hdc's master mcb		*/
	hdctlr_type	*hc;		/* hdc ctlr information table	*/
	hdc_regs_type	*ctlr_addr;	/* pointer to hdc i/o registers	*/
	int		timeout;	/* used to timeout the mcb	*/
	int		bus;		/* bus number			*/
	int		ctlr;		/* the controller number	*/
	int		i, end;
	u_int		*ptr;
E 5
I 5
	register u_int	*ptr;
	master_mcb_type	*master_mcb;	/* the hdc's master mcb */
	hdctlr_type	*hc;		/* hdc ctlr information table */
	hdc_regs_type	*ctlr_addr;	/* pointer to hdc i/o registers */
	int	timeout;		/* used to timeout the mcb */
	int	bus, ctlr, i, end;
E 5
E 3

D 2
	bus = io->i_bus;
	ctlr = io->i_ctlr;
E 2
I 2
D 3
	bus = 0;			/* io->i_bus; */
	ctlr = HDCTLR(io->i_unit);	/* io->i_ctlr; */
E 3
I 3
D 5
	bus = 0;			/* io->i_bus;	*/
	ctlr = HDCTLR(io->i_unit);	/* io->i_ctlr;	*/
E 5
I 5
	bus = HDC_DEFBUS;
	ctlr = HDCTLR(io->i_unit);
E 5
E 3
E 2
	hc = &hdc_ctlr[ctlr][bus];

	mcb->interrupt = FALSE;
	mcb->priority = 0;
	mcb->forw_phaddr = 0;
	mcb->context = 0;
	mcb->reserved[0] = 0;
	mcb->reserved[1] = 0;
	master_mcb = &hc->master_mcb;
D 3
	master_mcb->forw_phaddr = (long) &mcb->forw_phaddr;
E 3
I 3
	master_mcb->forw_phaddr = (long)&mcb->forw_phaddr;
E 3
	master_mcb->mcs = 0;
	master_mcb->interrupt = 0;
D 3
	master_mcb->reserve1  = 0;
	master_mcb->reserve2  = 0;
	master_mcb->context   = 0;
E 3
I 3
	master_mcb->reserve1 = 0;
	master_mcb->reserve2 = 0;
	master_mcb->context = 0;
E 3
	master_mcb->mcl = MCL_IMMEDIATE;
D 3
	for (i=0;i<HDC_XSTAT_SIZE;i++) master_mcb->xstatus[i] = 0;
        ctlr_addr = hc->registers;
	HDREG(master_mcb_reg) = (unsigned long) master_mcb;
E 3
I 3
	for (i = 0; i < HDC_XSTAT_SIZE; i++)
		master_mcb->xstatus[i] = 0;
	ctlr_addr = hc->registers;
	HDREG(master_mcb_reg) = (u_long)master_mcb;
E 3
	timeout = 15000;
D 3
	while (TRUE) {
E 3
I 3
	for (;;) {
E 3
		DELAY(1000);
D 2
		mtpr(0,PADC);
E 2
I 2
		mtpr(PADC, 0);
E 2
D 3
		if ( (master_mcb->mcs & MCS_DONE) &&
			!(master_mcb->mcs & MCS_FATALERROR) ) return 0;
E 3
I 3
		if (master_mcb->mcs & MCS_DONE &&
		    !(master_mcb->mcs & MCS_FATALERROR))
			return(0);
E 3
D 5
		timeout--;
D 3
		if ( timeout > 0   &&
			!(master_mcb->mcs & MCS_FATALERROR) ) continue;
		if ( master_mcb->mcs & MCS_FATALERROR )
E 3
I 3
		if (timeout > 0   && !(master_mcb->mcs & MCS_FATALERROR))
E 5
I 5
		if (--timeout > 0 && !(master_mcb->mcs & MCS_FATALERROR))
E 5
			continue;
		if (master_mcb->mcs & MCS_FATALERROR)
E 3
			printf("hdc: controller fatal error\n");
		else
			printf("hdc: controller timed out\n");

		printf("mmcb: ");
D 3
		ptr = (unsigned int *) master_mcb;
		for (i=0;i<8;i++)
			printf(" %x",ptr[i]);
		for (i=7+HDC_XSTAT_SIZE; i>7; i--) {
E 3
I 3
		ptr = (u_int *)master_mcb;
		for (i = 0; i < 8; i++)
			printf(" %x", ptr[i]);
		for (i = 7 + HDC_XSTAT_SIZE; i > 7; i--) {
E 3
			end = i;
D 3
			if (ptr[i] != 0) break;
E 3
I 3
			if (ptr[i] != 0)
				break;
E 3
		}
D 3
		for (i=8;i<=end;i++)
			printf(" %x",ptr[i]);
E 3
I 3
		for (i = 8; i <= end; i++)
			printf(" %x", ptr[i]);
E 3
D 5
		printf("\n");
E 5

D 5
		printf("mcb:  ");
E 5
I 5
		printf("\nmcb:  ");
E 5
D 3
		ptr = (unsigned int *) &mcb->forw_phaddr;
		for (i=0; i<6; i++)
			printf(" %x",ptr[i]);
		for (i=6; i<72; i+=2) {
E 3
I 3
		ptr = (u_int *)&mcb->forw_phaddr;
		for (i = 0; i < 6; i++)
			printf(" %x", ptr[i]);
		for (i = 6; i < 72; i += 2) {
E 3
			printf("  %x %x", ptr[i], ptr[i+1]);
D 3
			if ( !(ptr[i] & 0x80000000)) break;
E 3
I 3
			if (!(ptr[i] & 0x80000000))
				break;
E 3
		}
		printf("\n");
		return(1);
	}
}
E 6
I 6
#endif /* COMPAT_42 */
E 6
E 1
