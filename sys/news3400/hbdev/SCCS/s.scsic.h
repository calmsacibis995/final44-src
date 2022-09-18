h30080
s 00002/00002/00073
d D 8.1 93/06/11 14:55:18 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00075/00000/00000
d D 7.1 92/06/04 15:58:41 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Sony Corp. and Kazumasa Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: $Hdr: scsic.h,v 4.300 91/06/09 06:22:24 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Copyright (c) 1987- by SONY Corporation.
 */

/*
 *	scsic.h	ver 1.1		
 *
 *		Header file for scsi.c.
 */

#define SCSI_NOTWAIT	0x2		/* don't wait cmd completion */

#define	splhi		spl7		/* IPL 7  Be careful to use this.*/

/*
 * Delay units are in microseconds.
 *
 *	1ms = 1000  on news800
 *	so 1ms = 1500 on 25MHz
 */
#define HDELAY(n)				\
	{					\
		register int N = (n)*1500 ;	\
		while(--N > 0);			\
	}

struct scsi_stat {
	int	wbc;	/* # of channel that is waiting for scsi bus free */	
	int	wrc;	/* # of channel that is waiting for reselection */	
	struct sc_chan_stat *ip;
			/* In progress channel. Same as ISTAT.IP */
	int	ipc;		/* number of in progress channel. */
	int	dma_stat;	/* OFF = DMAC is not used */
#define SC_DMAC_RD	1
#define SC_DMAC_WR	2
};

#undef VOLATILE
#ifdef mips
#define VOLATILE volatile
#else
#define VOLATILE
#endif

struct sc_chan_stat {
	struct scsi	*sc ;		/* scsi struct address */
	u_char		comflg;		/* flag for save comand pointer */
	u_int		stcnt;		/* save transfer count */
	u_char		*spoint;	/* save transfer point */
	u_int		stag;		/* save tag register */
	u_int		soffset;	/* save offset register */
	u_char		intr_flg;	/* interrupt flag. SCSI_INTEN/INTDIS */
	int		chan_num;	/* channel NO. */
	VOLATILE struct sc_chan_stat *wb_next;	/* wait bus channel queue */
};

#undef VOLATILE

extern struct scintsw scintsw[];

extern struct scsi_stat scsi_stat;
E 1
