h08171
s 00002/00002/00323
d D 8.1 93/06/11 15:57:56 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00006/00318
d D 7.4 92/10/11 10:22:56 bostic 4 3
c make kernel includes standard
e
s 00002/00002/00322
d D 7.3 91/05/25 15:26:30 bostic 3 2
c delete obsolete printf formats (%X -> %lx)
e
s 00004/00004/00320
d D 7.2 91/05/04 15:30:08 bostic 2 1
c READ, WRITE -> F_READ, F_WRITE
e
s 00324/00000/00000
d D 7.1 91/04/28 17:13:32 william 1 0
c date and time created 91/04/28 17:13:32 by william
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
 * Don Ahn.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/****************************************************************************/
/*                        standalone fd driver                               */
/****************************************************************************/
D 4
#include "param.h"
#include "dkbad.h"
#include "i386/isa/disk.h"
#include "i386/isa/fdreg.h"
#include "i386/isa/isa.h"
#include "saio.h"
E 4
I 4
#include <sys/param.h>
#include <sys/dkbad.h>

#include <i386/isa/disk.h>
#include <i386/isa/fdreg.h>
#include <i386/isa/isa.h>
#include <stand/saio.h>
E 4

#define NUMRETRY 10
/*#define FDDEBUG*/

#define NFD 2
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
 	{ 18,2,0xFF,0x1B,80,2880,1,0 },	/* 1.44 meg HD 3.5in floppy    */
	{ 15,2,0xFF,0x1B,80,2400,1,0 },	/* 1.2 meg HD floppy           */
	{ 9,2,0xFF,0x23,40,720,2,1 },	/* 360k floppy in 1.2meg drive */
	{ 9,2,0xFF,0x2A,40,720,1,1 },	/* 360k floppy in DD drive     */
};


/* state needed for current transfer */
static int fd_type;
static int fd_motor;
static int fd_retry;
static int fd_drive;
static int fd_status[7];

static int fdc = IO_FD1;	/* floppy disk base */

/* Make sure DMA buffer doesn't cross 64k boundary */
char bounce[FDBLK];


/****************************************************************************/
/*                               fdstrategy                                 */
/****************************************************************************/
int
fdstrategy(io,func)
register struct iob *io;
int func;
{
	char *address;
	long nblocks,blknum;
 	int unit, iosize;

#ifdef FDDEBUG
printf("fdstrat ");
#endif
	unit = io->i_unit;
	fd_type = io->i_part;

	/*
	 * Set up block calculations.
	 */
        iosize = io->i_cc / FDBLK;
	blknum = (unsigned long) io->i_bn * DEV_BSIZE / FDBLK;
 	nblocks = fd_types[fd_type].size;
	if ((blknum + iosize > nblocks) || blknum < 0) {
#ifndef SMALL
		printf("bn = %d; sectors = %d; type = %d; fssize = %d ",
			blknum, iosize, fd_type, nblocks);
                printf("fdstrategy - I/O out of filesystem boundaries\n");
#endif
		return(-1);
	}

	address = io->i_ma;
        while (iosize > 0) {
                if (fdio(func, unit, blknum, address))
                        return(-1);
		iosize--;
		blknum++;
                address += FDBLK;
        }
        return(io->i_cc);
}

int
fdio(func, unit, blknum, address)
int func,unit,blknum;
char *address;
{
	int i,j,cyl,sectrac,sec,head,numretry;
	struct fd_type *ft;

 	ft = &fd_types[fd_type];
#ifdef FDDEBUG
printf("fdio ");
#endif

 	sectrac = ft->sectrac;
	cyl = blknum / (2 * sectrac);
	numretry = NUMRETRY;

D 2
	if (func == WRITE) bcopy(address,bounce,FDBLK);
E 2
I 2
	if (func == F_WRITE) bcopy(address,bounce,FDBLK);
E 2

retry:
	out_fdc(15);	/* Seek function */
	out_fdc(unit);	/* Drive number */
	out_fdc(cyl);

	waitio();

	out_fdc(0x8);
	i = in_fdc(); j = in_fdc();
	if (!(i&0x20) || (cyl != j)) {
		numretry--;
		if (numretry) goto retry;
#ifndef SMALL
		printf("Seek error %d, req = %d, at = %d\n",i,cyl,j);
		printf("unit %d, type %d, sectrac %d, blknum %d\n",
			unit,fd_type,sectrac,blknum);
#endif
		return -1;
	}

	/* set up transfer */
D 2
	fd_dma(func == READ,bounce,FDBLK);
E 2
I 2
	fd_dma(func == F_READ, bounce, FDBLK);
E 2
	sec = blknum %  (sectrac * 2);
	head = sec / sectrac;
	sec = sec % sectrac + 1;
#ifdef FDDEBUG
	printf("sec %d hd %d cyl %d ", sec, head, cyl);
#endif

D 2
	if (func == READ)  out_fdc(0xE6);/* READ */
E 2
I 2
	if (func == F_READ)  out_fdc(0xE6);/* READ */
E 2
	else out_fdc(0xC5);		/* WRITE */
	out_fdc(head << 2 | fd_drive);	/* head & unit */
	out_fdc(cyl);			/* track */
	out_fdc(head);
	out_fdc(sec);			/* sector XXX +1? */
	out_fdc(ft->secsize);		/* sector size */
	out_fdc(sectrac);		/* sectors/track */
	out_fdc(ft->gap);		/* gap size */
	out_fdc(ft->datalen);		/* data length */

	waitio();

	for(i=0;i<7;i++) {
		fd_status[i] = in_fdc();
	}
	if (fd_status[0]&0xF8) {
		numretry--;
		if (numretry) goto retry;
#ifndef SMALL
D 3
		printf("FD err %X %X %X %X %X %X %X\n",
E 3
I 3
		printf("FD err %lx %lx %lx %lx %lx %lx %lx\n",
E 3
		fd_status[0], fd_status[1], fd_status[2], fd_status[3],
		fd_status[4], fd_status[5], fd_status[6] );
#endif
		return -1;
	}
D 2
	if (func == READ) bcopy(bounce,address,FDBLK);
E 2
I 2
	if (func == F_READ) bcopy(bounce,address,FDBLK);
E 2
	return 0;
}

/****************************************************************************/
/*                             fdc in/out                                   */
/****************************************************************************/
int
in_fdc()
{
	int i;
	while ((i = inb(fdc+fdsts) & 192) != 192) if (i == 128) return -1;
	return inb(0x3f5);
}

dump_stat()
{
	int i;
	for(i=0;i<7;i++) {
		fd_status[i] = in_fdc();
		if (fd_status[i] < 0) break;
	}
#ifdef FDDEBUGx
D 3
printf("FD bad status :%X %X %X %X %X %X %X\n",
E 3
I 3
printf("FD bad status :%lx %lx %lx %lx %lx %lx %lx\n",
E 3
	fd_status[0], fd_status[1], fd_status[2], fd_status[3],
	fd_status[4], fd_status[5], fd_status[6] );
#endif
}

set_intr()
{
	/* initialize 8259's */
	outb(0x20,0x11);
	outb(0x21,32);
	outb(0x21,4);
	outb(0x21,1);
	outb(0x21,0x0f); /* turn on int 6 */

/*
	outb(0xa0,0x11);
	outb(0xa1,40);
	outb(0xa1,2);
	outb(0xa1,1);
	outb(0xa1,0xff); */

}



waitio()
{
char c;
int n;

	do
		outb(0x20,0xc); /* read polled interrupt */
	while ((c=inb(0x20))&0x7f != 6); /* wait for int */
	outb(0x20,0x20);
}

out_fdc(x)
int x;
{
	int r;
	do {
		r = (inb(fdc+fdsts) & 192);
		if (r==128) break;
		if (r==192) {
			dump_stat(); /* error: direction. eat up output */
		}
	} while (1);
	outb(0x3f5,x&0xFF);
}


/****************************************************************************/
/*                           fdopen/fdclose                                 */
/****************************************************************************/
fdopen(io)
	register struct iob *io;
{
	int unit, type, i;
	struct fd_type *ft;

	unit = io->i_unit;
	type = io->i_part;
	io->i_boff = 0;		/* no disklabels -- tar/dump wont work */
#ifdef FDDEBUG
	printf("fdopen %d %d ", unit, type);
#endif
 	ft = &fd_types[type];
	fd_drive = unit;

	set_intr(); /* init intr cont */

	/* Try a reset, keep motor on */
	outb(0x3f2,0);
	for(i=0; i < 100000; i++);
	outb(0x3f2,unit | (unit  ? 32 : 16) );
	for(i=0; i < 100000; i++);
	outb(0x3f2,unit | 0xC | (unit  ? 32 : 16) );
	outb(0x3f7,ft->trans);
	fd_motor = 1;

	waitio();

	out_fdc(3); /* specify command */
	out_fdc(0xDF);
	out_fdc(2);

	out_fdc(7);	/* Recalibrate Function */
	out_fdc(unit);

	waitio();
	return(0);
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
	/* Set read/write bytes */
	if (read) {
		outb(0xC,0x46); outb(0xB,0x46);
	} else {
		outb(0xC,0x4A); outb(0xB,0x4A);
	}
	/* Send start address */
	outb(0x4,addr & 0xFF);
	outb(0x4,(addr>>8) & 0xFF);
	outb(0x81,(addr>>16) & 0xFF);
	/* Send count */
	nbytes--;
	outb(0x5,nbytes & 0xFF);
	outb(0x5,(nbytes>>8) & 0xFF);
	/* set channel 2 */
	outb(0x0A,2);
}

E 1
