h08139
s 00001/00011/00189
d D 7.3 90/06/28 22:27:04 bostic 6 5
c new copyright notice
e
s 00018/00000/00182
d D 7.2 88/09/16 09:37:22 bostic 5 4
c add appropriate copyright notices
e
s 00003/00001/00179
d D 7.1 88/05/21 18:32:58 karels 4 3
c bring up to revision 7 for tahoe release
e
s 00026/00026/00154
d D 1.3 87/12/22 12:31:07 bostic 3 2
c make ANSI C compatible
e
s 00002/00002/00178
d D 1.2 86/11/23 18:30:31 sam 2 1
c merge dr11 device ioctls into dr driver to save extra device
e
s 00180/00000/00000
d D 1.1 86/07/20 11:25:58 sam 1 0
c date and time created 86/07/20 11:25:58 by sam
e
u
U
t
T
I 1
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
/*
I 5
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
 *
E 5
 *	%W% (Berkeley) %G%
 */
E 4

/*
    ------------------------------------------
    Must include <h/types.h> and <h/buf.h>
    ------------------------------------------
*/

#define	DRINTV	0x9c		/* Has to match with ml/scb.s */
#define DRADDMOD 0x01		/* Addr modifier used to access TAHOE memory */
#define DR_ZERO 0
#define DRPRI	(PZERO+1)

#define DR_TICK 600		/* Default # of clock ticks between call
				   to local timer watchdog routine */
#define	DR_TOCK	2		/* default # of calls to local watch dog
				   before an IO or wait is determined to
				   have timeout */


struct rsdevice {
    ushort dr_cstat;		/* Control & status registers */
    ushort dr_data;		/* Input/Ouptut data registers */
    char dr_addmod;		/* Address modifier for DMA */
    char dr_intvect;		/* Interrupt vector */
    ushort dr_pulse;		/* Pulse command register */
    ushort dr_xx08;		/* Not used */
    ushort dr_xx0A;		/* Not used */
    ushort dr_xx0C;		/* Not used */
    ushort dr_xx0E;		/* Not used */
    ushort dr_xx10;		/* Not used */
    ushort dr_walo;		/* Low DMA address register --when written-- */
    ushort dr_range;		/* DMA range counter */
    ushort dr_ralo;		/* Low DMA address register --when read-- */
    ushort dr_xx18;		/* Not used */
    ushort dr_wahi;		/* High DMA address register --when written-- */
    ushort dr_xx1C;		/* Not used */
    ushort dr_rahi;		/* High DMA address register --when read-- */
};


struct dr_aux {
	struct rsdevice *dr_addr; /* Physical addr of currently active DR11 */
	struct buf *dr_actf;	/* Pointers to DR11's active buffers list */
	unsigned int dr_flags;	/* State: Hold open, active,... */
	ushort dr_cmd;		/* Hold cmd placed here by ioctl
				   for later execution by rsstrategy() */
	ushort dr_op;		/* Current operation: DR_READ/DR_WRITE */
	long   dr_bycnt;	/* Total byte cnt of current operation */
				/* decremented by completion interrupt */
	caddr_t dr_oba;		/* original xfer addr, count */
	long   dr_obc;
	unsigned long
		rtimoticks,	/* No of ticks before timing out on no stall
				   read */
		wtimoticks,	/* No of ticks before timing out on no stall
				   write */
		currenttimo;	/* the number of current timeout call to
				   omrwtimo() */
   	ushort dr_istat;	/* Latest interrupt status */
	struct buf dr_buf;

	/*ushort dr_time;		/* # of ticks until timeout */
	/*ushort dr_tock;		/* # of ticks accumulated */
	/*ushort dr_cseq;		/* Current sequence number */
	/*ushort dr_lseq;		/* Last sequence number */
};

/*	Command used by drioctl() 
*/
struct dr11io {
	ushort arg[8];
};

#define RSADDR(unit)    ((struct rsdevice *)drinfo[unit]->ui_addr)

/*	Control register bits */
#define	RDMA	0x8000		/* reset DMA end-of-range flag */
#define	RATN	0x4000		/* reset attention flag */
#define RPER	0x2000		/* reset device parity error flag */
#define MCLR	0x1000		/* master clear board and INT device */
#define CYCL	0x0100		/* forces DMA cycle if DMA enabled */
#define IENB	0x0040		/* enables interrupt */
#define FCN3	0x0008		/* func. bit 3 to device (FNCT3 H) */
#define FCN2	0x0004		/* func. bit 2 to device (FNCT2 H) */
				/* also asserts ACLO FCNT2 H to device */
#define FCN1	0x0002		/* func. bit 1 to device (FNCT1 H) */
#define GO	0x0001		/* enable DMA and pulse GO to device */

/*	Status register bits */
#define	DMAF	0x8000		/* indicates DMA end-of-range */
#define	ATTF	0x4000		/* indicates attention false-to-true */
#define ATTN	0x2000		/* current state of ATTENTION H input */
#define PERR	0x1000		/* Set by external parity error */
#define STTA	0x0800		/* STATUS A H input state */
#define STTB	0x0400		/* STATUS B H input state */
#define STTC	0x0200		/* STATUS C H input state */
#define REDY	0x0080		/* board ready for cmd (dma not on) */
#define IENF	0x0040		/* Interrupt enabled if on */
#define BERR	0x0020		/* Set if bus error during DMA */
#define TERR	0x0010		/* Set if bus timeout during DMA */
#define FC3S	0x0008		/* State of FCN3 latch */
#define FC2S	0x0004		/* State of FCN2 latch */
#define FC1S	0x0002		/* State of FCN1 latch */
#define DLFG	0x0001		/* 0 -> IKON-10083 *** 1 -> IKON-10077 */

/*	Pulse command register bits */
#define SMSK	0x0040		/* pulse interrupt mask on:  Set IENB */
#define RMSK	0x0020		/* pulse interrupt mask off: Reset IENB */


/*	
 * 	DR11 driver's internal flags -- to be stored in dr_flags 
*/
#define DR_FMSK		0x0000E	/* function bits mask */
#define	DR_OPEN		0x00001	/* This dr11 has been opened */
#define DR_PRES		0x00002	/* This dr11 is present */
#define DR_ACTV		0x00004	/* waiting for end-of-range */
#define DR_ATWT 	0x00008	/* waiting for attention interrupt */
#define DR_ATRX 	0x00010	/* attn received-resets when read */
#define DR_TMDM		0x00020	/* timeout waiting for end-of-range */
#define DR_TMAT		0x00040	/* timeout waiting for attention */
#define DR_DMAX		0x00080	/* end-of-range interrupt received */
#define DR_PCYL		0x00100	/* set cycle with next go */
#define DR_DFCN 	0x00200	/* donot update function bits until next  go */
#define DR_DACL		0x00400	/* defer alco pulse until go */
#define DR_LOOPTST 	0x02000	/* This dr11 is in loopback test mode */
#define DR_LNKMODE 	0x04000	/* This dr11 is in link mode */
#define	DR_NORSTALL	0x10000	/* Device is set to no stall mode for reads. */
#define	DR_NOWSTALL	0x20000	/* Device is set to no stall mode for writes. */
#define	DR_TIMEDOUT	0x40000	/* The device timed out on a stall mode R/W */

/*	
 * 	DR11 driver's internal flags -- to be stored in dr_op 
*/
#define	DR_READ		FCN1
#define DR_WRITE	0

/*
 *	Ioctl commands
*/
D 3
#define DRWAIT		_IOWR(d,1,long)
#define	DRPIOW		_IOWR(d,2,long)
#define DRPACL		_IOWR(d,3,long)
#define DRDACL		_IOWR(d,4,long)
#define DRPCYL		_IOWR(d,5,long)
#define DRDFCN 		_IOWR(d,6,long)
#define DRRPER 		_IOWR(d,7,long)
#define DRRATN		_IOWR(d,8,long)
#define DRRDMA 		_IOWR(d,9,long)
#define DRSFCN 		_IOWR(d,10,long)
E 3
I 3
#define DRWAIT		_IOWR('d',1,long)
#define	DRPIOW		_IOWR('d',2,long)
#define DRPACL		_IOWR('d',3,long)
#define DRDACL		_IOWR('d',4,long)
#define DRPCYL		_IOWR('d',5,long)
#define DRDFCN 		_IOWR('d',6,long)
#define DRRPER 		_IOWR('d',7,long)
#define DRRATN		_IOWR('d',8,long)
#define DRRDMA 		_IOWR('d',9,long)
#define DRSFCN 		_IOWR('d',10,long)
E 3

D 3
#define	DRSETRSTALL	_IOWR(d,13,long)
#define	DRSETNORSTALL	_IOWR(d,14,long)
#define	DRGETRSTALL	_IOWR(d,15,long)
#define	DRSETRTIMEOUT	_IOWR(d,16,long)
#define	DRGETRTIMEOUT	_IOWR(d,17,long)
#define	DRSETWSTALL	_IOWR(d,18,long)
#define	DRSETNOWSTALL	_IOWR(d,19,long)
#define	DRGETWSTALL	_IOWR(d,20,long)
#define	DRSETWTIMEOUT	_IOWR(d,21,long)
#define	DRGETWTIMEOUT	_IOWR(d,22,long)
#define	DRWRITEREADY	_IOWR(d,23,long)
#define	DRREADREADY	_IOWR(d,24,long)
#define	DRBUSY		_IOWR(d,25,long)
#define	DRRESET		_IOWR(d,26,long)
E 3
I 3
#define	DRSETRSTALL	_IOWR('d',13,long)
#define	DRSETNORSTALL	_IOWR('d',14,long)
#define	DRGETRSTALL	_IOWR('d',15,long)
#define	DRSETRTIMEOUT	_IOWR('d',16,long)
#define	DRGETRTIMEOUT	_IOWR('d',17,long)
#define	DRSETWSTALL	_IOWR('d',18,long)
#define	DRSETNOWSTALL	_IOWR('d',19,long)
#define	DRGETWSTALL	_IOWR('d',20,long)
#define	DRSETWTIMEOUT	_IOWR('d',21,long)
#define	DRGETWTIMEOUT	_IOWR('d',22,long)
#define	DRWRITEREADY	_IOWR('d',23,long)
#define	DRREADREADY	_IOWR('d',24,long)
#define	DRBUSY		_IOWR('d',25,long)
#define	DRRESET		_IOWR('d',26,long)
E 3

/* The block size for buffering and DMA transfers. */
/* OM_BLOCKSIZE must be even and <= 32768. Multiples of 512 are prefered. */
#define	OM_BLOCKSIZE	32768


/* --- Define ioctl call used by dr11 utility device --  */

D 2
#define DR11STAT	_IOWR(d,1,struct dr11io)   /* Get status dr11, unit 
E 2
I 2
D 3
#define DR11STAT	_IOWR(d,30,struct dr11io)   /* Get status dr11, unit 
E 3
I 3
#define DR11STAT	_IOWR('d',30,struct dr11io)   /* Get status dr11, unit 
E 3
E 2
						   number is dr11io.arg[0] */
D 2
#define DR11LOOP	_IOR(d,2,struct dr11io)   /* Perform loopback test */
E 2
I 2
D 3
#define DR11LOOP	_IOR(d,31,struct dr11io)   /* Perform loopback test */
E 3
I 3
#define DR11LOOP	_IOR('d',31,struct dr11io)   /* Perform loopback test */
E 3
E 2

/* ---------------------------------------------------- */

E 1
