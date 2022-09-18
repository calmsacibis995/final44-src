h29055
s 00002/00002/00643
d D 8.1 93/06/11 15:53:39 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00011/00634
d D 7.8 92/10/11 10:20:03 bostic 13 12
c make kernel includes standard
e
s 00001/00000/00644
d D 7.7 92/05/20 16:51:49 bostic 12 11
c Make Fdclose return 0 (success); from Pace Willisson (pace@blitz.com)
e
s 00045/00025/00599
d D 7.6 92/02/05 10:58:25 bostic 11 10
c driver didn't work if compiled with NFD == 1, also memory corruption
c problems; from Christos Zoulas
e
s 00010/00007/00614
d D 7.5 91/11/16 14:05:46 william 10 9
c name change for seeley's conf.c file
e
s 00008/00008/00613
d D 7.4 91/05/25 15:26:07 bostic 9 8
c delete obsolete printf formats (%X -> %lx)
e
s 00003/00005/00618
d D 7.3 91/05/21 10:40:22 bostic 8 7
c format cleanup
e
s 00001/00001/00622
d D 7.2 91/05/09 22:42:35 william 7 6
c fixed copyright notice
e
s 00000/00001/00623
d D 7.1 91/05/09 22:41:30 william 6 5
c removed obselete include file
e
s 00012/00017/00612
d D 5.5 91/05/09 20:35:48 william 5 4
c interim version, changes for net2 tape
e
s 00000/00000/00629
d D 5.4 91/01/08 19:13:18 william 4 3
c  npx.c wd.c wt.c
e
s 00001/00001/00628
d D 5.3 90/11/18 11:31:58 bill 3 2
c auto conf, bus control, conventions, interrupt control, per host config
e
s 00163/00130/00466
d D 5.2 90/11/08 18:40:26 bill 2 1
c move dma code out of driver, improve autoconf code
e
s 00596/00000/00000
d D 5.1 90/06/23 19:05:34 donahn 1 0
c date and time created 90/06/23 19:05:34 by donahn
e
u
U
t
T
I 2
D 8
#include "fd.h"
#if NFD > 0
E 8
E 2
I 1
/*-
D 14
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * This code is derived from software contributed to Berkeley by
 * Don Ahn.
 *
D 7
 * %sccs.include.386.c%
E 7
I 7
 * %sccs.include.redist.c%
E 7
 *
 *	%W% (Berkeley) %G%
 */

D 8
/****************************************************************************/
/*                               fd driver                                  */
/****************************************************************************/
E 8
I 8
#include "fd.h"
#if NFD > 0
D 11

E 11
I 11
/*
 * This driver assumed that NFD == 2. Now it works for NFD == 1 or NFD == 2
 * It will probably not work for NFD > 2.
 */
E 11
E 8
D 13
#include "param.h"
#include "dkbad.h"
#include "systm.h"
#include "conf.h"
#include "file.h"
D 5
#include "dir.h"
#include "user.h"
E 5
#include "ioctl.h"
D 6
#include "disk.h"
E 6
#include "buf.h"
D 5
#include "vm.h"
E 5
#include "uio.h"
E 13
I 13
#include <sys/param.h>
#include <sys/dkbad.h>
#include <sys/systm.h>
#include <sys/conf.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/buf.h>
#include <sys/uio.h>
E 13
I 11

E 11
D 5
#include "machine/pte.h"
D 2
#include "machine/device.h"
E 2
I 2
D 3
#include "machine/isa/device.h"
E 3
I 3
#include "machine/isa/isa_device.h"
E 3
#include "machine/isa/fdreg.h"
E 2
#include "icu.h"
E 5
I 5
D 13
#include "i386/isa/isa_device.h"
#include "i386/isa/fdreg.h"
#include "i386/isa/icu.h"
E 13
I 13
#include <i386/isa/isa_device.h>
#include <i386/isa/fdreg.h>
#include <i386/isa/icu.h>
E 13
E 5

D 2
#define NFD 2
E 2
#define	FDUNIT(s)	((s)&1)
#define	FDTYPE(s)	(((s)>>1)&7)
I 11
#define FDMOTOR(u) 	(fd_unit[(u)].motor ? (1 << (4 + (u))) : 0)
E 11
I 2

E 2
#define b_cylin b_resid
I 2
#define b_step b_resid
E 2
#define FDBLK 512
#define NUMTYPES 4

struct fd_type {
	int	sectrac;		/* sectors per track         */
	int	secsize;		/* size code for sectors     */
	int	datalen;		/* data len when secsize = 0 */
	int	gap;			/* gap len between sectors   */
	int	tracks;			/* total num of tracks       */
	int	size;			/* size of disk in sectors   */
	int	steptrac;		/* steps per cylinder        */
	int	trans;			/* transfer speed code       */
};

struct fd_type fd_types[NUMTYPES] = {
D 2
	{ 18,2,0xFF,0x1B,80,2880,1,0 },	/* 1.44 meg HD 3.5in floppy    */
E 2
I 2
 	{ 18,2,0xFF,0x1B,80,2880,1,0 },	/* 1.44 meg HD 3.5in floppy    */
E 2
	{ 15,2,0xFF,0x1B,80,2400,1,0 },	/* 1.2 meg HD floppy           */
	{ 9,2,0xFF,0x23,40,720,2,1 },	/* 360k floppy in 1.2meg drive */
	{ 9,2,0xFF,0x2A,40,720,1,1 },	/* 360k floppy in DD drive     */
};

struct fd_u {
	int type;		/* Drive type (HD, DD     */
	int active;		/* Drive activity boolean */
	int motor;		/* Motor on flag          */
D 2
	int opencnt;		/* Num times open         */
E 2
	struct buf head;	/* Head of buf chain      */
	struct buf rhead;	/* Raw head of buf chain  */
I 2
	int reset;
E 2
} fd_unit[NFD];

I 2

E 2
extern int hz;

/* state needed for current transfer */
I 2
static fdc;	/* floppy disk controller io base register */
int	fd_dmachan = 2;
E 2
static int fd_skip;
static int fd_state;
static int fd_retry;
static int fd_drive;
I 2
static int fd_track = -1;
E 2
static int fd_status[7];
D 2
static char fdrawbuf[FDBLK];
E 2

D 2
/* stuff needed for virtual to physical calculations */
extern char Sysbase;
static unsigned long sbase = (unsigned long) &Sysbase;
E 2
I 2
/*
	make sure bounce buffer for DMA is aligned since the DMA chip
	doesn't roll over properly over a 64k boundary
*/
extern struct buf *dma_bounce[];
E 2

/****************************************************************************/
/*                      autoconfiguration stuff                             */
/****************************************************************************/
int fdprobe(), fdattach(), fd_turnoff();

D 2
struct	driver fddriver = {
E 2
I 2
struct	isa_driver fddriver = {
E 2
	fdprobe, fdattach, "fd",
};

fdprobe(dev)
D 2
struct device *dev;
E 2
I 2
struct isa_device *dev;
E 2
{
	return 1;
}

fdattach(dev)
D 2
struct device *dev;
E 2
I 2
struct isa_device *dev;
{	int	s;

	fdc = dev->id_iobase;
	/* Set transfer to 500kbps */
	outb(fdc+fdctl,0);
	fd_turnoff(0);
}

int
D 10
fdsize(dev)
E 10
I 10
Fdsize(dev)
E 10
dev_t	dev;
E 2
{
D 2
	INTREN(IRQ6);
E 2
I 2
	return(2400);
E 2
}

/****************************************************************************/
/*                               fdstrategy                                 */
/****************************************************************************/
D 10
fdstrategy(bp)
E 10
I 10
Fdstrategy(bp)
E 10
	register struct buf *bp;	/* IO operation to perform */
{
D 11
	register struct buf *dp,*dp0,*dp1;
E 11
I 11
	register struct buf *dp;
E 11
	long nblocks,blknum;
D 2
	int	unit, type, s;
E 2
I 2
 	int	unit, type, s;
E 2

D 2
	unit = FDUNIT(minor(bp->b_dev));
	type = FDTYPE(minor(bp->b_dev));
#ifdef FDOTHER
	printf("fdstrat: unit = %d, blkno = %d, bcount = %d\n",
		unit, bp->b_blkno, bp->b_bcount);
E 2
I 2
 	unit = FDUNIT(minor(bp->b_dev));
 	type = FDTYPE(minor(bp->b_dev));

#ifdef FDTEST
printf("fdstrat%d, blk = %d, bcount = %d, addr = %x|",
	unit, bp->b_blkno, bp->b_bcount,bp->b_un.b_addr);
E 2
#endif
	if ((unit >= NFD) || (bp->b_blkno < 0)) {
		printf("fdstrat: unit = %d, blkno = %d, bcount = %d\n",
			unit, bp->b_blkno, bp->b_bcount);
		pg("fd:error in fdstrategy");
		bp->b_error = EINVAL;
I 2
		bp->b_flags |= B_ERROR;
E 2
		goto bad;
	}
	/*
	 * Set up block calculations.
	 */
	blknum = (unsigned long) bp->b_blkno * DEV_BSIZE/FDBLK;
D 2
	nblocks = fd_types[type].size;
E 2
I 2
 	nblocks = fd_types[type].size;
E 2
	if (blknum + (bp->b_bcount / FDBLK) > nblocks) {
D 2
		if (blknum == nblocks) bp->b_resid = bp->b_bcount;
		else bp->b_error = ENOSPC;
E 2
I 2
		if (blknum == nblocks) {
			bp->b_resid = bp->b_bcount;
		} else {
			bp->b_error = ENOSPC;
			bp->b_flags |= B_ERROR;
		}
I 11
#ifdef FDTEST
printf("fdstrat%d, too big\n");
#endif 
E 11
E 2
		goto bad;
	}
D 2
	bp->b_cylin = blknum / (fd_types[type].sectrac * 2);
	bp->b_cylin *= (fd_types[type].steptrac);
E 2
I 2
 	bp->b_cylin = blknum / (fd_types[type].sectrac * 2);
E 2
	dp = &fd_unit[unit].head;
D 11
	dp0 = &fd_unit[0].head;
	dp1 = &fd_unit[1].head;
E 11
I 2
	dp->b_step = (fd_types[fd_unit[unit].type].steptrac);
E 2
	s = splbio();
	disksort(dp, bp);
D 11
	if ((dp0->b_active == 0)&&(dp1->b_active == 0)) {
E 11
I 11
	if ((fd_unit[0].head.b_active == 0)
#if NFD > 1
	    && (fd_unit[1].head.b_active == 0)
#endif
	    ) {
E 11
I 2
#ifdef FDDEBUG
printf("T|");
#endif
E 2
		dp->b_active = 1;
		fd_drive = unit;
I 2
		fd_track = -1;  /* force seek on first xfer */
E 2
		untimeout(fd_turnoff,unit);
		fdstart(unit);		/* start drive if idle */
	}
	splx(s);
	return;

bad:
D 2
	bp->b_flags |= B_ERROR;
E 2
	biodone(bp);
}

/****************************************************************************/
/*                            motor control stuff                           */
/****************************************************************************/
set_motor(unit,reset)
int unit,reset;
{
D 11
	int m0,m1;
	m0 = fd_unit[0].motor;
	m1 = fd_unit[1].motor;
D 2
	outb(0x3f2,unit | (reset ? 0 : 0xC)  | (m0 ? 16 : 0) | (m1 ? 32 : 0));
E 2
I 2
	outb(fdc+fdout,unit | (reset ? 0 : 0xC)  | (m0 ? 16 : 0) | (m1 ? 32 : 0));
E 11
I 11
	outb(fdc+fdout,unit | (reset ? 0 : 0xC)  | FDMOTOR(0) 
#if NFD > 1
	     | FDMOTOR(1)
#endif
	     );
E 11
E 2
}

fd_turnoff(unit)
int unit;
{
	fd_unit[unit].motor = 0;
	if (unit) set_motor(0,0);
	else set_motor(1,0);
}

fd_turnon(unit)
int unit;
{
	fd_unit[unit].motor = 1;
	set_motor(unit,0);
}

/****************************************************************************/
/*                             fdc in/out                                   */
/****************************************************************************/
int
in_fdc()
{
	int i;
D 2
	while ((i = inb(0x3f4) & 192) != 192) if (i == 128) return -1;
	return inb(0x3f5);
E 2
I 2
	while ((i = inb(fdc+fdsts) & (NE7_DIO|NE7_RQM)) != (NE7_DIO|NE7_RQM))
		if (i == NE7_RQM) return -1;
	return inb(fdc+fddata);
E 2
}

dump_stat()
{
	int i;
	for(i=0;i<7;i++) {
		fd_status[i] = in_fdc();
		if (fd_status[i] < 0) break;
	}
D 2
	printf("FD bad status :%X %X %X %X %X %X %X\n",
		fd_status[0], fd_status[1], fd_status[2], fd_status[3],
		fd_status[4], fd_status[5], fd_status[6] );
E 2
I 2
D 9
printf("FD bad status :%X %X %X %X %X %X %X\n",
E 9
I 9
printf("FD bad status :%lx %lx %lx %lx %lx %lx %lx\n",
E 9
	fd_status[0], fd_status[1], fd_status[2], fd_status[3],
	fd_status[4], fd_status[5], fd_status[6] );
E 2
}

out_fdc(x)
int x;
{
	int r,errcnt;
	static int maxcnt = 0;
	errcnt = 0;
	do {
D 2
		r = (inb(0x3f4) & 192);
		if (r==128) break;
		if (r==192) {
E 2
I 2
		r = (inb(fdc+fdsts) & (NE7_DIO|NE7_RQM));
		if (r== NE7_RQM) break;
		if (r==(NE7_DIO|NE7_RQM)) {
E 2
			dump_stat(); /* error: direction. eat up output */
#ifdef FDOTHER
D 2
			printf("%X\n",x);
E 2
I 2
D 9
printf("%X\n",x);
E 9
I 9
printf("%lx\n",x);
E 9
E 2
#endif
		}
		/* printf("Error r = %d:",r); */
		errcnt++;
	} while (1);
	if (errcnt > maxcnt) {
		maxcnt = errcnt;
#ifdef FDOTHER
D 2
		printf("New MAX = %d\n",maxcnt);
E 2
I 2
printf("New MAX = %d\n",maxcnt);
E 2
#endif
	}
D 2
	outb(0x3f5,x&0xFF);
E 2
I 2
	outb(fdc+fddata,x);
E 2
}

/* see if fdc responding */
int
check_fdc()
{
	int i;
	for(i=0;i<100;i++) {
D 2
		if (inb(0x3f4)&128) return 0;
E 2
I 2
		if (inb(fdc+fdsts)& NE7_RQM) return 0;
E 2
	}
	return 1;
}

/****************************************************************************/
/*                           fdopen/fdclose                                 */
/****************************************************************************/
D 5
fdopen(dev, flags)
E 5
I 5
Fdopen(dev, flags)
E 5
	dev_t	dev;
	int	flags;
{
D 2
	int unit = FDUNIT(minor(dev));
	int type = FDTYPE(minor(dev));
E 2
I 2
 	int unit = FDUNIT(minor(dev));
 	int type = FDTYPE(minor(dev));
E 2
	int s;

I 11
	printf("fdopen %x %d %d\n", minor(dev), unit, type);
E 11
	/* check bounds */
	if (unit >= NFD) return(ENXIO);
	if (type >= NUMTYPES) return(ENXIO);
I 2
/*
E 2
	if (check_fdc()) return(EBUSY);
I 2
*/
E 2

	/* Set proper disk type, only allow one type */
D 2
	s = splbio();
	splx(s);

E 2
	return 0;
}

D 5
fdclose(dev)
E 5
I 5
D 10
fdclose(dev, flags)
E 10
I 10
Fdclose(dev, flags)
E 10
E 5
	dev_t dev;
{
I 12
	return (0);
E 12
}

/****************************************************************************/
/*                            fdread/fdwrite                                */
/****************************************************************************/
/*
 * Routines to do raw IO for a unit.
 */
D 10
fdread(dev, uio)			/* character read routine */
E 10
I 10
Fdread(dev, uio)			/* character read routine */
E 10
dev_t dev;
struct uio *uio;
{
D 2
	int unit = FDUNIT(minor(dev)) ;
E 2
I 2
 	int unit = FDUNIT(minor(dev)) ;
E 2
	if (unit >= NFD) return(ENXIO);
D 10
	return(physio(fdstrategy,&fd_unit[unit].rhead,dev,B_READ,minphys,uio));
E 10
I 10
	return(physio(Fdstrategy,&fd_unit[unit].rhead,dev,B_READ,minphys,uio));
E 10
}

D 10
fdwrite(dev, uio)			/* character write routine */
E 10
I 10
Fdwrite(dev, uio)			/* character write routine */
E 10
dev_t dev;
struct uio *uio;
{
D 2
	int unit = FDUNIT(minor(dev));
E 2
I 2
 	int unit = FDUNIT(minor(dev)) ;
E 2
	if (unit >= NFD) return(ENXIO);
D 10
	return(physio(fdstrategy,&fd_unit[unit].rhead,dev,B_WRITE,minphys,uio));
E 10
I 10
	return(physio(Fdstrategy,&fd_unit[unit].rhead,dev,B_WRITE,minphys,uio));
E 10
}

/****************************************************************************/
/*                                 fdstart                                  */
/****************************************************************************/
fdstart(unit)
int unit;
{
	register struct buf *dp,*bp;
	int s;

I 2
#ifdef FDTEST
D 11
printf("st%d|",unit);
E 11
I 11
printf("fd%d|",unit);
E 11
#endif 
	s = splbio();
E 2
	if (!fd_unit[unit].motor) {
		fd_turnon(unit);
		/* Wait for 1 sec */
		timeout(fdstart,unit,hz);
D 2
	} else {
		s = splbio();
E 2
I 2
		/*DELAY(1000000);*/
	}else
		 {
		/* make sure drive is selected as well as on */
		/*set_motor(unit,0);*/

E 2
		dp = &fd_unit[unit].head;
		bp = dp->b_actf;
		fd_retry = 0;
D 2
		fd_state = 1;
E 2
I 2
		if (fd_unit[unit].reset) fd_state = 1;
		else {
			/* DO a RESET */
			fd_unit[unit].reset = 1;
			fd_state = 5;
		}
E 2
		fd_skip = 0;
I 2
#ifdef FDDEBUG
printf("Seek %d %d\n", bp->b_cylin, dp->b_step);
#endif
		if (bp->b_cylin != fd_track) {
E 2
		/* Seek necessary, never quite sure where head is at! */
		out_fdc(15);	/* Seek function */
		out_fdc(unit);	/* Drive number */
D 2
		out_fdc(bp->b_cylin);
		splx(s);
E 2
I 2
		out_fdc(bp->b_cylin * dp->b_step);
D 5
		} else fdintr(0);
E 5
I 5
		} else fdintr(0xff);
E 5
E 2
	}
I 2
	splx(s);
E 2
}

D 2
/* XXX temporary */
kernel_space(x)
unsigned long x;
{
	if ((x >= sbase) & (x < sbase + 0x800000)) return 1;
	else return 0;
}


/****************************************************************************/
/*                                 fd_dma                                   */
/* set up DMA read/write operation and virtual address addr for nbytes      */
/****************************************************************************/
fd_dma(read,addr,nbytes)
int read;
unsigned long addr;
int nbytes;
{
	unsigned long phys;
	int s,raw;

	if (kernel_space(addr)) raw = 0;
	else raw = 1;

	/* copy bounce buffer on write */
	if (raw && !read) bcopy(addr,fdrawbuf,FDBLK);

	/* Set read/write bytes */
	if (read) {
		outb(0xC,0x46); outb(0xB,0x46);
	} else {
		outb(0xC,0x4A); outb(0xB,0x4A);
	}
	/* Send start address */
	if (raw) phys = (unsigned long) &fdrawbuf[0];
	else phys = addr;
	/* translate to physical */
	phys = phys - sbase;
	outb(0x4,phys & 0xFF);
	outb(0x4,(phys>>8) & 0xFF);
	outb(0x81,(phys>>16) & 0xFF);
	/* Send count */
	nbytes--;
	outb(0x5,nbytes & 0xFF);
	outb(0x5,(nbytes>>8) & 0xFF);
	/* set channel 2 */
	outb(0x0A,2);
}

E 2
fd_timeout(x)
int x;
{
	int i,j;
	struct buf *dp,*bp;

	dp = &fd_unit[fd_drive].head;
	bp = dp->b_actf;

	out_fdc(0x4);
	out_fdc(fd_drive);
	i = in_fdc();
D 9
	printf("Timeout drive status %X\n",i);
E 9
I 9
	printf("Timeout drive status %lx\n",i);
E 9

	out_fdc(0x8);
	i = in_fdc();
	j = in_fdc();
D 9
	printf("ST0 = %X, PCN = %X\n",i,j);
E 9
I 9
	printf("ST0 = %lx, PCN = %lx\n",i,j);
E 9

	if (bp) badtrans(dp,bp);
}

/****************************************************************************/
/*                                 fdintr                                   */
/****************************************************************************/
D 5
fdintr(vec)
int vec;
E 5
I 5
fdintr(unit)
E 5
{
	register struct buf *dp,*bp;
	struct buf *dpother;
D 2
	int read,head,trac,sec,i,s,sectrac;
E 2
I 2
	int read,head,trac,sec,i,s,sectrac,cyl;
E 2
	unsigned long blknum;
	struct fd_type *ft;
D 2
	static int fd_track;
E 2

I 2
#ifdef FDTEST
D 5
	printf("state %d, vec %d, dr %d|",fd_state,vec,fd_drive);
E 5
I 5
	printf("state %d, unit %d, dr %d|",fd_state,unit,fd_drive);
E 5
#endif

E 2
	dp = &fd_unit[fd_drive].head;
	bp = dp->b_actf;
	read = bp->b_flags & B_READ;
D 2
	ft = &fd_types[FDTYPE(bp->b_dev)];
E 2
I 2
 	ft = &fd_types[FDTYPE(bp->b_dev)];
E 2

	switch (fd_state) {
	case 1 : /* SEEK DONE, START DMA */
D 2
#ifdef FDOTHER
		out_fdc(0x8);
		i = in_fdc();
		sec = in_fdc();
		printf("ST0 = %X, PCN = %X:",i,sec);
#endif
E 2
I 2
		/* Make sure seek really happened*/
D 5
		if (vec) {
E 5
I 5
		if (unit != 0xff) {
E 5
			out_fdc(0x8);
			i = in_fdc();
			cyl = in_fdc();
			if (!(i&0x20) || (cyl != bp->b_cylin*dp->b_step)) {
D 9
printf("Stray int ST0 = %X, PCN = %X:",i,cyl);
E 9
I 9
printf("Stray int ST0 = %lx, PCN = %lx:",i,cyl);
E 9
				return;
			}
		}

E 2
		fd_track = bp->b_cylin;
D 2
		fd_dma(read,bp->b_un.b_addr+fd_skip,FDBLK);
E 2
I 2
		at_dma(read,bp->b_un.b_addr+fd_skip,FDBLK, fd_dmachan);
E 2
		blknum = (unsigned long)bp->b_blkno*DEV_BSIZE/FDBLK
			+ fd_skip/FDBLK;
		sectrac = ft->sectrac;
		sec = blknum %  (sectrac * 2);
		head = sec / sectrac;
		sec = sec % sectrac + 1;

		if (read)  out_fdc(0xE6);	/* READ */
		else out_fdc(0xC5);		/* WRITE */
		out_fdc(head << 2 | fd_drive);	/* head & unit */
		out_fdc(fd_track);		/* track */
		out_fdc(head);
		out_fdc(sec);			/* sector XXX +1? */
		out_fdc(ft->secsize);		/* sector size */
		out_fdc(sectrac);		/* sectors/track */
		out_fdc(ft->gap);		/* gap size */
		out_fdc(ft->datalen);		/* data length */
		fd_state = 2;
		/* XXX PARANOIA */
		untimeout(fd_timeout,2);
		timeout(fd_timeout,2,hz);
		break;
	case 2 : /* IO DONE, post-analyze */
		untimeout(fd_timeout,2);
		for(i=0;i<7;i++) {
			fd_status[i] = in_fdc();
		}
		if (fd_status[0]&0xF8) {
#ifdef FDOTHER
D 2
			printf("status0 err %d:",fd_status[0]);
E 2
I 2
printf("status0 err %d:",fd_status[0]);
E 2
#endif
			goto retry;
		}
I 2
/*
E 2
		if (fd_status[1]){
			printf("status1 err %d:",fd_status[0]);
			goto retry;
		}
		if (fd_status[2]){
			printf("status2 err %d:",fd_status[0]);
			goto retry;
		}
I 2
*/
E 2
		/* All OK */
		if (!kernel_space(bp->b_un.b_addr+fd_skip)) {
			/* RAW transfer */
D 2
			if (read) bcopy(fdrawbuf,bp->b_un.b_addr+fd_skip,
					DEV_BSIZE);
E 2
I 2
			if (read) bcopy(dma_bounce[fd_dmachan]->b_un.b_addr,
				bp->b_un.b_addr+fd_skip, FDBLK);
E 2
		}
		fd_skip += FDBLK;
		if (fd_skip >= bp->b_bcount) {
I 2
#ifdef FDTEST
printf("DONE %d|", bp->b_blkno);
#endif
E 2
			/* ALL DONE */
			fd_skip = 0;
			bp->b_resid = 0;
			dp->b_actf = bp->av_forw;
			biodone(bp);
			nextstate(dp);

		} else {
I 2
#ifdef FDDEBUG
printf("next|");
#endif
E 2
			/* set up next transfer */
			blknum = (unsigned long)bp->b_blkno*DEV_BSIZE/FDBLK
				+ fd_skip/FDBLK;
			fd_state = 1;
			bp->b_cylin = (blknum / (ft->sectrac * 2));
D 2
			bp->b_cylin *= ft->steptrac;
E 2
			if (bp->b_cylin != fd_track) {
I 2
#ifdef FDTEST
printf("Seek|");
#endif
E 2
				/* SEEK Necessary */
				out_fdc(15);	/* Seek function */
				out_fdc(fd_drive);/* Drive number */
D 2
				out_fdc(bp->b_cylin);
E 2
I 2
				out_fdc(bp->b_cylin * dp->b_step);
E 2
				break;
D 2
			} else fdintr();
E 2
I 2
D 5
			} else fdintr(0);
E 5
I 5
			} else fdintr(0xff);
E 5
E 2
		}
		break;
	case 3:
I 2
#ifdef FDOTHER
printf("Seek %d %d\n", bp->b_cylin, dp->b_step);
#endif
E 2
		/* Seek necessary */
		out_fdc(15);	/* Seek function */
		out_fdc(fd_drive);/* Drive number */
D 2
		out_fdc(bp->b_cylin);
E 2
I 2
		out_fdc(bp->b_cylin * dp->b_step);
E 2
		fd_state = 1;
		break;
	case 4:
		out_fdc(3); /* specify command */
		out_fdc(0xDF);
		out_fdc(2);
		out_fdc(7);	/* Recalibrate Function */
		out_fdc(fd_drive);
		fd_state = 3;
		break;
I 2
	case 5:
#ifdef FDOTHER
		printf("**RESET**\n");
#endif
		/* Try a reset, keep motor on */
		set_motor(fd_drive,1);
		set_motor(fd_drive,0);
		outb(fdc+fdctl,ft->trans);
		fd_retry++;
		fd_state = 4;
		break;
E 2
	default:
D 2
#ifdef FDDEBUG
E 2
		printf("Unexpected FD int->");
		out_fdc(0x8);
		i = in_fdc();
		sec = in_fdc();
D 9
		printf("ST0 = %X, PCN = %X\n",i,sec);
E 9
I 9
		printf("ST0 = %lx, PCN = %lx\n",i,sec);
E 9
		out_fdc(0x4A); 
		out_fdc(fd_drive);
		for(i=0;i<7;i++) {
			fd_status[i] = in_fdc();
		}
D 9
	printf("intr status :%X %X %X %X %X %X %X ",
E 9
I 9
	printf("intr status :%lx %lx %lx %lx %lx %lx %lx ",
E 9
		fd_status[0], fd_status[1], fd_status[2], fd_status[3],
		fd_status[4], fd_status[5], fd_status[6] );
D 2
#endif
E 2
		break;
	}
	return;
retry:
	switch(fd_retry) {
	case 0: case 1:
I 2
	case 2: case 3:
E 2
		break;
D 2
	case 2:
#ifdef FDDEBUG
		printf("**RESET**\n");
#endif
		/* Try a reset, keep motor on */
		set_motor(fd_drive,1);
		set_motor(fd_drive,0);
		outb(0x3f7,ft->trans);
E 2
I 2
	case 4:
E 2
		fd_retry++;
D 2
		fd_state = 4;
E 2
I 2
		fd_state = 5;
D 5
		fdintr(0);
E 5
I 5
		fdintr(0xff);
E 5
E 2
		return;
D 2
	case 3: case 4:
	case 5: case 6:
E 2
I 2
	case 5: case 6: case 7:
E 2
		break;
	default:
D 9
		printf("FD err %X %X %X %X %X %X %X\n",
E 9
I 9
		printf("FD err %lx %lx %lx %lx %lx %lx %lx\n",
E 9
		fd_status[0], fd_status[1], fd_status[2], fd_status[3],
		fd_status[4], fd_status[5], fd_status[6] );
		badtrans(dp,bp);
		return;
	}
	fd_state = 1;
	fd_retry++;
D 2
	fdintr();
E 2
I 2
D 5
	fdintr(0);
E 5
I 5
	fdintr(0xff);
E 5
E 2
}

badtrans(dp,bp)
struct buf *dp,*bp;
{

	bp->b_flags |= B_ERROR;
	bp->b_error = EIO;
	bp->b_resid = bp->b_bcount - fd_skip;
	dp->b_actf = bp->av_forw;
	fd_skip = 0;
	biodone(bp);
	nextstate(dp);

}

/*
	nextstate : After a transfer is done, continue processing
	requests on the current drive queue.  If empty, go to
	the other drives queue.  If that is empty too, timeout
	to turn off the current drive in 5 seconds, and go
	to state 0 (not expecting any interrupts).
*/

nextstate(dp)
struct buf *dp;
{
D 11
	struct buf *dpother;
E 11
	
D 11
	dpother = &fd_unit[fd_drive ? 0 : 1].head;
	if (dp->b_actf) fdstart(fd_drive);
	else if (dpother->b_actf) {
E 11
I 11
	if (dp->b_actf) 
		fdstart(fd_drive);
	else {
#if NFD > 1
		struct buf *dpother;

		dpother = &fd_unit[fd_drive ? 0 : 1].head;

		if (dpother->b_actf) {
E 11
I 2
#ifdef FDTEST
printf("switch|");
#endif
D 11
		untimeout(fd_turnoff,fd_drive);
		timeout(fd_turnoff,fd_drive,5*hz);
		fd_drive = 1 - fd_drive;
E 2
		dp->b_active = 0;
D 2
		fdstart(fd_drive ? 0 : 1);
E 2
I 2
		dpother->b_active = 1;
		fdstart(fd_drive);
E 2
	} else {
E 11
I 11
			untimeout(fd_turnoff,fd_drive);
			timeout(fd_turnoff,fd_drive,5*hz);
			fd_drive = 1 - fd_drive;
			dp->b_active = 0;
			dpother->b_active = 1;
			fdstart(fd_drive);
		} else 
#endif
		{
E 11
I 2
#ifdef FDTEST
printf("off|");
#endif
E 2
D 11
		untimeout(fd_turnoff,fd_drive);
		timeout(fd_turnoff,fd_drive,5*hz);
		fd_state = 0;
		dp->b_active = 0;
E 11
I 11
			untimeout(fd_turnoff,fd_drive);
			timeout(fd_turnoff,fd_drive,5*hz);
			fd_state = 0;
			dp->b_active = 0;
		}
E 11
	}
}
I 10

Fdioctl() {}
Fddump() {}
E 10
I 2
#endif
E 2
E 1
