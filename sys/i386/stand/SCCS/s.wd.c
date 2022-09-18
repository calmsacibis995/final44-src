h26046
s 00002/00002/00407
d D 8.1 93/06/11 15:58:11 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00006/00402
d D 7.4 92/10/11 10:22:58 bostic 4 3
c make kernel includes standard
e
s 00002/00002/00406
d D 7.3 91/05/04 15:30:39 bostic 3 2
c READ, WRITE -> F_READ, F_WRITE
e
s 00139/00125/00269
d D 7.2 91/04/28 17:38:33 william 2 1
c 
e
s 00394/00000/00000
d D 7.1 90/04/24 19:57:26 william 1 0
c date and time created 90/04/24 19:57:26 by william
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 2
 * %sccs.include.noredist.c%
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

/*  device driver for winchester disk  */

D 2
#include "../h/param.h"
#include "../h/inode.h"
#include "../h/fs.h"
#include "../h/dkbad.h"
#include "../h/disk.h"
#include "../isa/atio.h"
#include "../isa/wdreg.h"
E 2
I 2
D 4
#include "param.h"
#include "dkbad.h"
#include "disklabel.h"
#include "i386/isa/isa.h"
#include "i386/isa/wdreg.h"
E 2
#include "saio.h"
E 4
I 4
#include <sys/param.h>
#include <sys/dkbad.h>
#include <sys/disklabel.h>

#include <i386/isa/isa.h>
#include <i386/isa/wdreg.h>
#include <stand/saio.h>
E 4

#define	NWD		2	/* number of hard disk units supported, max 2 */
#define	RETRIES		5	/* number of retries before giving up */

D 2
int noretries = 0;
int wdquiet = 0;
#ifdef	WDDEBUG
int wdinfoflag = 0;
#endif
E 2
I 2
int noretries, wdquiet;
/*#define WDDEBUG*/
E 2

#ifdef	SMALL
extern struct disklabel disklabel;
#else
struct disklabel wdsizes[NWD];
D 2
extern struct disklabel *dlp;
E 2
#endif
D 2
int cyloffset;
E 2

I 2
extern cyloffset ;		/* bootstrap's idea of cylinder for disklabel */

E 2
/*
 * Record for the bad block forwarding code.
 * This is initialized to be empty until the bad-sector table
 * is read from the disk.
 */
#define TRKSEC(trk,sec)	((trk << 8) + sec)

struct	dkbad	dkbad[NWD];
I 2
static wdcport;
E 2

wdopen(io)
	register struct iob *io;
{
        register struct disklabel *dd;
D 2
	int unit, partition;
E 2

D 2
	unit = minor_unit(minor(io->i_ino.i_dev));
	partition = minor_partition(minor(io->i_ino.i_dev));
E 2
I 2
#ifdef WDDEBUG
	printf("wdopen ");
#endif
E 2
#ifdef SMALL
        dd = &disklabel;
#else
D 2
        dd = &wdsizes[unit];
	if (partition >= 8)
E 2
I 2
        dd = &wdsizes[io->i_unit];
	if (io->i_part > 8)
E 2
                _stop("Invalid partition number");
I 2
	if(io->i_ctlr > 1)
                _stop("Invalid controller number");
E 2
#endif
        if (wdinit(io))
                _stop("wd initialization error");
I 2
	io->i_boff = dd->d_partitions[io->i_part].p_offset ;
	return(0);
E 2
}

wdstrategy(io,func)
	register struct iob *io;
{
	register int iosize;    /* number of sectors to do IO for this loop */
	register daddr_t sector;
	int nblocks, cyloff;
	int unit, partition;
	char *address;
	register struct disklabel *dd;

D 2
	unit = minor_unit(minor(io->i_ino.i_dev));
	partition = minor_partition(minor(io->i_ino.i_dev));
	if ((unsigned)unit >= NWD) {
		printf("wd: unit %d\n", unit);
		return(-1);
	}
E 2
I 2
	unit = io->i_unit;
	partition = io->i_part;
#ifdef WDDEBUG
	printf("wdstrat %d %d ", unit, partition);
#endif
E 2
#ifdef	SMALL
	dd = &disklabel;
#else
	dd = &wdsizes[unit];
#endif
D 2
        iosize = io->i_cc / dd->dk_secsize;
E 2
I 2
        iosize = io->i_cc / dd->d_secsize;
E 2
	/*
	 * Convert PGSIZE "blocks" to sectors.
	 * Note: doing the conversions this way limits the partition size
	 * to about 8 million sectors (1-8 Gb).
	 */
D 2
	sector = (unsigned long) io->i_bn * DEV_BSIZE / dd->dk_secsize;
	nblocks = dd->dk_partition[partition].nblocks;
	cyloff = dd->dk_partition[partition].cyloff;
E 2
I 2
	sector = (unsigned long) io->i_bn * DEV_BSIZE / dd->d_secsize;
	nblocks = dd->d_partitions[partition].p_size;
#ifndef SMALL
E 2
        if (iosize < 0 || sector + iosize > nblocks || sector < 0) {
#ifdef WDDEBUG
		printf("bn = %d; sectors = %d; partition = %d; fssize = %d\n",
			io->i_bn, iosize, partition, nblocks);
#endif
                printf("wdstrategy - I/O out of filesystem boundaries\n");
		return(-1);
	}
D 2
	if (io->i_bn * DEV_BSIZE % dd->dk_secsize) {
E 2
I 2
	if (io->i_bn * DEV_BSIZE % dd->d_secsize) {
E 2
		printf("wdstrategy - transfer starts in midsector\n");
		return(-1);
	}
D 2
        if (io->i_cc % dd->dk_secsize) {
E 2
I 2
        if (io->i_cc % dd->d_secsize) {
E 2
		printf("wd: transfer of partial sector\n");
		return(-1);
	}
I 2
#endif
E 2

	address = io->i_ma;
D 2
	sector += cyloff * dd->dk_secpercyl;
E 2
        while (iosize > 0) {
                if (wdio(func, unit, sector, address))
                        return(-1);
		iosize--;
		sector++;
D 2
                address += dd->dk_secsize;
E 2
I 2
                address += dd->d_secsize;
E 2
        }
        return(io->i_cc);
}

/* 
 * Routine to do a one-sector I/O operation, and wait for it
 * to complete.
 */
wdio(func, unit, blknm, addr)
        short *addr;
{
	struct disklabel *dd;
D 2
	int wdc = IO_WD0;
E 2
I 2
	register wdc = wdcport;
E 2
	struct bt_bad *bt_ptr;
        int    i;
	int retries = 0;
        long    cylin, head, sector;
D 2
        u_char opcode;
E 2
I 2
        u_char opcode, erro;
E 2

#ifdef	SMALL
	dd = &disklabel;
#else
	dd = &wdsizes[unit];
#endif
D 3
        if (func == WRITE)
E 3
I 3
        if (func == F_WRITE)
E 3
                opcode = WDCC_WRITE;
        else
                opcode = WDCC_READ;

        /* Calculate data for output.           */
D 2
        cylin = blknm / dd->dk_secpercyl;
        head = (blknm % dd->dk_secpercyl) / dd->dk_nsectors;
        sector = blknm % dd->dk_nsectors + 1;
E 2
I 2
        cylin = blknm / dd->d_secpercyl;
        head = (blknm % dd->d_secpercyl) / dd->d_nsectors;
        sector = blknm % dd->d_nsectors;
E 2

D 2
#ifdef notyet
E 2
	/* 
	 * See if the current block is in the bad block list.
	 */
D 2
	if (blknm > 7)	/* should be BBSIZE */
E 2
I 2
	if (blknm > BBSIZE/DEV_BSIZE)	/* should be BBSIZE */
E 2
	    for (bt_ptr = dkbad[unit].bt_bad; bt_ptr->bt_cyl != -1; bt_ptr++) {
		if (bt_ptr->bt_cyl > cylin)
			/* Sorted list, and we passed our cylinder. quit. */
			break;
		if (bt_ptr->bt_cyl == cylin &&
			bt_ptr->bt_trksec == (head << 8) + sector) {
			/*
			 * Found bad block.  Calculate new block addr.
			 * This starts at the end of the disk (skip the
			 * last track which is used for the bad block list),
			 * and works backwards to the front of the disk.
			 */
#ifdef WDDEBUG
D 2
			if (wdinfoflag)
E 2
			    printf("--- badblock code -> Old = %d; ",
				blknm);
#endif
D 2
			blknm = dd->dk_secperunit - dd->dk_nsectors
E 2
I 2
			blknm = dd->d_secperunit - dd->d_nsectors
E 2
				- (bt_ptr - dkbad[unit].bt_bad) - 1;
D 2
			cylin = blknm / dd->dk_secpercyl;
			head = (blknm % dd->dk_secpercyl) / dd->dk_nsectors;
			sector = blknm % dd->dk_nsectors;
E 2
I 2
			cylin = blknm / dd->d_secpercyl;
			head = (blknm % dd->d_secpercyl) / dd->d_nsectors;
			sector = blknm % dd->d_nsectors;
E 2
#ifdef WDDEBUG
D 2
			if (wdinfoflag)
E 2
			    printf("new = %d\n", blknm);
#endif
			break;
		}
	}

D 2
#endif
E 2
I 2
        sector += 1;
E 2
retry:
D 2
printf("sec %d sdh %x cylin %d\n", sector
	, WDSD_IBM | (unit<<4) | (head & 0xf), cylin);
E 2
I 2
#ifdef WDDEBUG
	printf("sec %d sdh %x cylin %d ", sector,
		WDSD_IBM | (unit<<4) | (head & 0xf), cylin);
#endif
E 2
	outb(wdc+wd_precomp, 0xff);
	outb(wdc+wd_seccnt, 1);
	outb(wdc+wd_sector, sector);
	outb(wdc+wd_cyl_lo, cylin);
	outb(wdc+wd_cyl_hi, cylin >> 8);

	/* Set up the SDH register (select drive).     */
	outb(wdc+wd_sdh, WDSD_IBM | (unit<<4) | (head & 0xf));
D 2
	while ((inb(wdc+wd_altsts) & WDCS_READY) == 0) ;
E 2
I 2
	while ((inb(wdc+wd_status) & WDCS_READY) == 0) ;
E 2

	outb(wdc+wd_command, opcode);
D 2
	while (opcode == WDCC_READ && (inb(wdc+wd_altsts) & WDCS_BUSY))
E 2
I 2
	while (opcode == WDCC_READ && (inb(wdc+wd_status) & WDCS_BUSY))
E 2
		;
	/* Did we get an error?         */
D 2
	if (opcode == WDCC_READ && (inb(wdc+wd_altsts) & WDCS_ERR))
E 2
I 2
	if (opcode == WDCC_READ && (inb(wdc+wd_status) & WDCS_ERR))
E 2
		goto error;

	/* Ready to remove data?        */
D 2
	while ((inb(wdc+wd_altsts) & WDCS_DRQ) == 0) ;
E 2
I 2
	while ((inb(wdc+wd_status) & WDCS_DRQ) == 0) ;
E 2

	if (opcode == WDCC_READ)
		insw(wdc+wd_data,addr,256);
	else	outsw(wdc+wd_data,addr,256);

	/* Check data request (should be done).         */
D 2
	if (inb(wdc+wd_altsts) & WDCS_DRQ) goto error;
E 2
I 2
	if (inb(wdc+wd_status) & WDCS_DRQ) goto error;
E 2

D 2
	while (opcode == WDCC_WRITE && (inb(wdc+wd_altsts) & WDCS_BUSY)) ;
E 2
I 2
	while (opcode == WDCC_WRITE && (inb(wdc+wd_status) & WDCS_BUSY)) ;
E 2

D 2
	if (inb(wdc+wd_altsts) & WDCS_ERR) goto error;
E 2
I 2
	if (inb(wdc+wd_status) & WDCS_ERR) goto error;
E 2

D 2
/*for (i=0; i < 256 ; i++){
	if((i%20) == 0) printf("\n");
	printf("%x ", addr[i]);
}
i=getchar();*/

E 2
I 2
#ifdef WDDEBUG
printf("+");
#endif
E 2
        return (0);
error:
D 2
	wddumpregs(wdc);
E 2
I 2
	erro = inb(wdc+wd_error);
E 2
	if (++retries < RETRIES)
		goto retry;
	if (!wdquiet)
D 2
	    printf("wd%d: hard %s error: sector %d, status %b error %b\n", unit,
E 2
I 2
#ifdef	SMALL
	    printf("wd%d: hard error: sector %d status %x error %x\n", unit,
		blknm, inb(wdc+wd_status), erro);
#else
	    printf("wd%d: hard %s error: sector %d status %b error %b\n", unit,
E 2
		opcode == WDCC_READ? "read" : "write", blknm, 
D 2
		inb(wdc+wd_status), WDCS_BITS, inb(wdc+wd_error), WDERR_BITS);
E 2
I 2
		inb(wdc+wd_status), WDCS_BITS, erro, WDERR_BITS);
#endif
E 2
	return (-1);
}

wdinit(io)
	struct iob *io;
{
D 2
	int wdc = IO_WD0;
E 2
I 2
	register wdc;
E 2
	struct disklabel *dd;
        unsigned int   unit;
	struct dkbad *db;
	int i, errcnt = 0;
	char buf[512];
	static open[NWD];

D 2
	/* reset controller */
	outb(wdc+wd_ctlr, 4); wait(10); outb(wdc+wd_ctlr, 0);
	wdwait();
E 2
I 2
	unit = io->i_unit;
	if (open[unit]) return(0);
E 2

D 2
	unit = minor_unit(minor(io->i_ino.i_dev));
E 2
I 2
	wdcport = io->i_ctlr ? IO_WD2 : IO_WD1;
	wdc = wdcport;

E 2
#ifdef	SMALL
	dd = &disklabel;
D 2
	outb(wdc+wd_command, WDCC_RESTORE | WD_STEP);
	wdwait();
E 2
#else
I 2
	/* reset controller */
	outb(wdc+wd_ctlr, 12); wait(10); outb(wdc+wd_ctlr, 8);
	wdwait();

E 2
	dd = &wdsizes[unit];
D 2
	if (open[unit]) return(0);
/*
code to tell disk controller geometry of disk
not currently used
E 2

D 2
	outb(wdc+wd_sdh, 0xa7);
wdwait();
	outb(wdc+wd_seccnt, 17);
	outb(wdc+wd_cyl_lo, 0);
	outb(wdc+wd_command, 0x91);
	wdwait();*/

E 2
tryagainrecal:
D 2
	/* set SDH, step rate, do restore */
E 2
I 2
	/* set SDH, step rate, do restore to recalibrate drive */
E 2
	outb(wdc+wd_sdh, WDSD_IBM | (unit << 4));
	wdwait();
	outb(wdc+wd_command, WDCC_RESTORE | WD_STEP);
	wdwait();
	if ((i = inb(wdc+wd_status)) & WDCS_ERR) {
I 2
/*#ifdef SMALL
		printf("wd%d: recal status %x error %x\n",
			unit, i, inb(wdc+wd_error));
#else*/
E 2
		printf("wd%d: recal status %b error %b\n",
			unit, i, WDCS_BITS, inb(wdc+wd_error), WDERR_BITS);
D 2
		wddumpregs(wdc);
E 2
I 2
/*#endif*/
E 2
		if (++errcnt < 10)
			goto tryagainrecal;
		return(-1);
	}
D 2
#endif	SMALL
#ifndef	SMALL
E 2
I 2

	/*
	 * Some controllers require this (after a recal they
	 * revert to a logical translation mode to compensate for
	 * dos limitation on 10-bit cylinders -- *shudder* -wfj)
	 * note: cylinders *must* be fewer than or equal to 8 to
	 * compensate for some IDE drives that latch this for all time.
	 */
	outb(wdc+wd_sdh, WDSD_IBM | (unit << 4) + 8 -1);
	outb(wdc+wd_seccnt, 35 );
	outb(wdc+wd_cyl_lo, 1224);
	outb(wdc+wd_cyl_hi, 1224/256);
	outb(wdc+wd_command, 0x91);
	while (inb(wdc+wd_status) & WDCS_BUSY) ;

E 2
	errcnt = 0;
retry:
D 2
cyloffset = 290;
E 2
	/*
D 2
	 * Read in sector 0 to get the pack label and geometry.
E 2
I 2
	 * Read in LABELSECTOR to get the pack label and geometry.
E 2
	 */
	outb(wdc+wd_precomp, 0xff);	/* sometimes this is head bit 3 */
	outb(wdc+wd_seccnt, 1);
D 2
	outb(wdc+wd_sector, 1);
E 2
I 2
	outb(wdc+wd_sector, LABELSECTOR + 1);
E 2
	outb(wdc+wd_cyl_lo, (cyloffset & 0xff));
	outb(wdc+wd_cyl_hi, (cyloffset >> 8));
	outb(wdc+wd_sdh, WDSD_IBM | (unit << 4));
	wdwait();
	outb(wdc+wd_command, WDCC_READ);
	wdwait();
	if ((i = inb(wdc+wd_status)) & WDCS_ERR) {
D 2
		wddumpregs(wdc);
E 2
I 2
		int err;

		err = inb(wdc+wd_error);
E 2
		if (++errcnt < RETRIES)
			goto retry;
		if (!wdquiet)
I 2
/*#ifdef SMALL
		    printf("wd%d: reading label, status %x error %x\n",
			unit, i, err);
#else*/
E 2
		    printf("wd%d: reading label, status %b error %b\n",
D 2
			unit, i, WDCS_BITS, inb(wdc+wd_error), WDERR_BITS);
E 2
I 2
			unit, i, WDCS_BITS, err, WDERR_BITS);
/*#endif*/
E 2
		return(-1);
	}

	/* Ready to remove data?        */
D 2
	while ((inb(wdc+wd_altsts) & WDCS_DRQ) == 0) ;
E 2
I 2
	while ((inb(wdc+wd_status) & WDCS_DRQ) == 0) ;
E 2

	i = insw(wdc+wd_data, buf, 256);

D 2
	/*printf("magic %x,insw %x, %x\n",
	((struct disklabel *) (buf + LABELOFFSET))->dk_magic, i, buf);*/
	if (((struct disklabel *) (buf + LABELOFFSET))->dk_magic == DISKMAGIC) {
E 2
I 2
#ifdef WDDEBUG
	printf("magic %x,insw %x, %x\n",
	((struct disklabel *) (buf + LABELOFFSET))->d_magic, i, buf);
#endif
	if (((struct disklabel *) (buf + LABELOFFSET))->d_magic == DISKMAGIC) {
E 2
		*dd = * (struct disklabel *) (buf + LABELOFFSET);
		open[unit] = 1;
	} else {
		if (!wdquiet)
			printf("wd%d: bad disk label\n", unit);
		if (io->i_flgs & F_FILE) return(-1);
		dkbad[unit].bt_bad[0].bt_cyl = -1;
D 2
		dd->dk_secpercyl = 1999999 ; dd->dk_nsectors = 17 ;
		dd->dk_secsize = 512;
E 2
I 2
		dd->d_secpercyl = 1999999 ; dd->d_nsectors = 17 ;
		dd->d_secsize = 512;
E 2
		outb(wdc+wd_precomp, 0xff);	/* force head 3 bit off */
D 2
/**dd = *dlp;
open[unit] = 1;*/
E 2
		return (0) ;
	}
D 2
	dkbad[unit].bt_bad[0].bt_cyl = -1;
	outb(wdc+wd_precomp, dd->dk_precompcyl / 4);
E 2
I 2
#endif SMALL
#ifdef SMALL
#ifdef WDDEBUG
	printf("magic %x sect %d\n", dd->d_magic, dd->d_nsectors);
#endif
E 2
#endif	SMALL

D 2
#ifdef notyet
E 2
I 2

	/* now that we know the disk geometry, tell the controller */
	outb(wdc+wd_cyl_lo, dd->d_ncylinders);
	outb(wdc+wd_cyl_hi, (dd->d_ncylinders)>>8);
	outb(wdc+wd_sdh, WDSD_IBM | (unit << 4) + dd->d_ntracks-1);
	outb(wdc+wd_seccnt, dd->d_nsectors);
	outb(wdc+wd_command, 0x91);
	while (inb(wdc+wd_status) & WDCS_BUSY) ;

	dkbad[unit].bt_bad[0].bt_cyl = -1;
	outb(wdc+wd_precomp, dd->d_precompcyl / 4);

E 2
	/*
	 * Read bad sector table into memory.
	 */
	i = 0;
	do {
D 2
		int blknm = dd->dk_secperunit - dd->dk_nsectors + i;
E 2
I 2
		int blknm = dd->d_secperunit - dd->d_nsectors + i;
E 2
D 3
		errcnt = wdio(READ, unit, blknm, buf);
E 3
I 3
		errcnt = wdio(F_READ, unit, blknm, buf);
E 3
D 2
	} while (errcnt && (i += 2) < 10 && i < dd->dk_nsectors);
E 2
I 2
	} while (errcnt && (i += 2) < 10 && i < dd->d_nsectors);
E 2
	db = (struct dkbad *)(buf);
I 2
#define DKBAD_MAGIC 0x4321
E 2
	if (errcnt == 0 && db->bt_mbz == 0 && db->bt_flag == DKBAD_MAGIC)
		dkbad[unit] = *db;
	else {
		if (!wdquiet)
			printf("wd%d: error in bad-sector file\n", unit);
		dkbad[unit].bt_bad[0].bt_cyl = -1;
	}
D 2
#endif
E 2
	return(0);
}

wdwait()
{
D 2
	register wdc = IO_WD0;
E 2
I 2
	register wdc = wdcport;
E 2
	register i = 0;
	
D 2
	while (inb(wdc+wd_altsts) & WDCS_BUSY)
E 2
I 2
	while (inb(wdc+wd_status) & WDCS_BUSY)
E 2
		;
D 2
	while ((inb(wdc+wd_altsts) & WDCS_READY) == 0)
E 2
I 2
	while ((inb(wdc+wd_status) & WDCS_READY) == 0)
E 2
		if (i++ > 100000)
			return(-1);
	return(0);
D 2
}


wddumpregs(wdc){

printf("err %x ", inb(wdc+wd_error));
printf("seccnt %d ", inb(wdc+wd_seccnt));
printf("sector %d ", inb(wdc+wd_sector));
printf("cyl %d:", inb(wdc+wd_cyl_lo));
printf("%d ", inb(wdc+wd_cyl_hi));
printf("sdh %x ", inb(wdc+wd_sdh));
printf("sts %x ", inb(wdc+wd_status));
printf("alt %x ", inb(wdc+wd_altsts));
printf("dig %x\n", inb(wdc+wd_digin));

E 2
}
E 1
