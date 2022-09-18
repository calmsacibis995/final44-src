/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	cca.h,v $
 * Revision 2.3  89/02/26  10:58:16  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/08/10  10:46:30  rvb
 * Created.  Week of 4/4.
 * 
 */
/*
 *	File:	cca.h
 *	Author:	Robert V. Baron
 *
 *	CCA structures and bitfields
 */
struct hw_revision {
	u_char	cvax_rev;
	u_char	ssc_rev;
	u_char	fpa_rev;
	u_char	com_grp;
	u_int	mod_rev;
};

#define HWREV_MDIE	0x00000080
#define HWREV_COPR	0x00000040
#define HWREV_COM_GRP	0x0000000f
#define HWREV	"\20\10MDIE\07COPR\04\01COM_GRP"

struct com_buf {
	u_char	flags;
	u_char	zdest;
	u_char	zsrc;
	u_char	spare;
	u_char	txlen;
	u_char	rxlen;
	u_short	zrxcd;
	u_char	tx[80];
	u_char	rx[80];
};

#define XCBUF_ZALT	0x00000008
#define XCBUF_ZARC	0x00000004
#define XCBUF_ZDEST	0x00000002
#define XCBUF_RXRDY	0x00000001
#define XCBUF	"\20\04ZALT\03ZARC\02ZDEST\01RXRDY"

struct cca {
	u_int	base;
	u_short	size;
	u_short	ident;
	u_char	nproc;
	u_char	chksum;
	u_char	hflag;
	u_char	revision;
	u_int	ready[2];		/* 0x00c */
	u_int	console[2];
	u_int	enabled[2];
	u_int	bitmap_sz;
	u_int	bitmap;
	u_int	bitmap_cksum;
	u_int	tk50_node;
	u_int	secstart[2];
	u_int	restartip[2];
	u_int	fill[3];
	u_int	user_halted[2];
	u_int	serialnum[2];
	struct	hw_revision
		hw_revision[16];	/* 0x060 */
	u_char	fill2[0x120];		/* 0x0e0 */
	struct	com_buf		/* 0x200 */
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
extern struct cca *find_cca();
extern struct cca *cca;
#endif	ASSEMBLER
#endif	KERNEL
