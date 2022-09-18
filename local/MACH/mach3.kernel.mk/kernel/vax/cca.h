/* 
 * Mach Operating System
 * Copyright (c) 1991,1989,1988 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

/*
 * HISTORY
 * $Log:	cca.h,v $
 * Revision 2.3  91/05/14  17:41:49  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/05/08  13:14:11  dbg
 * 	Changed to new copyright.
 * 	[91/04/26  15:13:40  dbg]
 * 
 * Revision 2.1  89/08/03  16:38:29  rwd
 * Created.
 * 
 * Revision 2.2  88/08/10  10:46:30  rvb
 * Created.  Week of 4/4.
 * 
 */

/*
 *	File:	cca.h
 *	Author:	Robert V. Baron, 1988.
 *
 *	CCA structures and bitfields
 *
 */

#ifndef	_VAX_CCA_H_
#define	_VAX_CCA_H_

struct hw_revision {
	unsigned char	cvax_rev;
	unsigned char	ssc_rev;
	unsigned char	fpa_rev;
	unsigned char	com_grp;
	unsigned long	mod_rev;
};

#define HWREV_MDIE	0x00000080
#define HWREV_COPR	0x00000040
#define HWREV_COM_GRP	0x0000000f
#define HWREV	"\20\10MDIE\07COPR\04\01COM_GRP"

struct com_buf {
	unsigned char	flags;
	unsigned char	zdest;
	unsigned char	zsrc;
	unsigned char	spare;
	unsigned char	txlen;
	unsigned char	rxlen;
	unsigned short	zrxcd;
	unsigned char	tx[80];
	unsigned char	rx[80];
};

#define XCBUF_ZALT	0x00000008
#define XCBUF_ZARC	0x00000004
#define XCBUF_ZDEST	0x00000002
#define XCBUF_RXRDY	0x00000001
#define XCBUF	"\20\04ZALT\03ZARC\02ZDEST\01RXRDY"

struct cca {
	unsigned long	base;
	unsigned short	size;
	unsigned short	ident;
	unsigned char	nproc;
	unsigned char	chksum;
	unsigned char	hflag;
	unsigned char	revision;
	unsigned long	ready[2];		/* 0x00c */
	unsigned long	console[2];
	unsigned long	enabled[2];
	unsigned long	bitmap_sz;
	unsigned long	bitmap;
	unsigned long	bitmap_cksum;
	unsigned long	tk50_node;
	unsigned long	secstart[2];
	unsigned long	restartip[2];
	unsigned long	fill[3];
	unsigned long	user_halted[2];
	unsigned long	serialnum[2];
	struct	hw_revision
			hw_revision[16];	/* 0x060 */
	unsigned char	fill2[0x120];		/* 0x0e0 */
	struct	com_buf				/* 0x200 */
			buf[16];
};

#define HFLAG_CON_REBOOT	0x00000040
#define HFLAG_REPROMPT		0x00000020
#define HFLAG_REBOOT		0x00000010
#define HFLAG_ECCLEAR		0x00000008
#define HFLAG_EXCACHE		0x00000004
#define HFLAG_INCACHE		0x00000002
#define HFLAG_BOOTIP		0x00000001

#define HFLAG	"\20\07CON_REBOOT\06REPROMPT\05REBOOT\04ECCLEAR\03EXCACHE\02INCACHE\01BOOTIP"

#ifdef	KERNEL
#ifndef	ASSEMBLER
extern struct cca *ccap;	/* physical address */
extern struct cca *cca;		/* virtual address */
#endif	ASSEMBLER
#endif	KERNEL

#endif	/* _VAX_CCA_H_ */
