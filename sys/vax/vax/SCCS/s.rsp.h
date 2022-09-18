h42895
s 00005/00004/00081
d D 7.2 91/05/09 20:11:15 bostic 7 6
c new copyright; att/bsd/shared
e
s 00001/00001/00084
d D 7.1 86/06/05 00:47:44 mckusick 6 5
c 4.3BSD release version
e
s 00007/00001/00078
d D 6.2 85/06/08 13:45:38 mckusick 5 4
c Add copyright
e
s 00000/00000/00079
d D 6.1 83/07/29 07:21:08 sam 4 3
c 4.2 distribution
e
s 00003/00019/00076
d D 4.3 83/06/08 10:07:52 helge 3 2
c moved def of soft carrier back to the drivers, added some new states
e
s 00001/00001/00094
d D 4.2 83/06/01 13:18:02 helge 2 1
c ooooops
e
s 00095/00000/00000
d D 4.1 83/06/01 12:01:17 helge 1 0
c date and time created 83/06/01 12:01:17 by helge
e
u
U
t
T
I 1
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
D 7
/*
D 6
 * Copyright (c) 1982 Regents of the University of California.
E 6
I 6
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
E 7
 *
 *	%W% (Berkeley) %G%
 */
E 5

/*
 * TU58 transfer protocol constants and data structures
 */

/*
 * Structure of a command packet
 */
struct packet {
	u_char	pk_flag;	/* indicates packet type (cmd, data, etc.) */
	u_char	pk_mcount;	/* length of packet (bytes) */
	u_char	pk_op;		/* operation to perform (read, write, etc.) */
	u_char	pk_mod;		/* modifier for op or returned status */
	u_char	pk_unit;	/* unit number */
	u_char	pk_sw;		/* switches */
	u_short	pk_seq;		/* sequence number, always zero */
	u_short	pk_count;	/* requested byte count for read or write */
	u_short	pk_block;	/* block number for read, write, or seek */
	u_short	pk_chksum;	/* checksum, by words with end around carry */
};

/*
D 3
 * State information
 */
struct tu {
	u_char	*tu_rbptr;	/* pointer to buffer for read */
	int	tu_rcnt;	/* how much to read */
	u_char	*tu_wbptr;	/* pointer to buffer for write */
	int	tu_wcnt;	/* how much to write */
	int	tu_state;	/* current state of tansfer operation */
	int	tu_flag;	/* read in progress flag */
	char	*tu_addr;	/* real buffer data address */
	int	tu_count;	/* real requested count */
	int	tu_serrs;	/* count of soft errors */
	int	tu_cerrs;	/* count of checksum errors */
	int	tu_herrs;	/* count of hard errors */
	char    tu_dopen[2];	/* drive is open */
D 2
} tu;
E 2
I 2
};
E 2

/*
E 3
 * States
 */
#define	TUS_INIT1	0	/* sending nulls */
#define	TUS_INIT2	1	/* sending inits */
#define	TUS_IDLE	2	/* initialized, no transfer in progress */
#define	TUS_SENDH	3	/* sending header */
#define	TUS_SENDD	4	/* sending data */
#define	TUS_SENDC	5	/* sending checksum */
#define	TUS_SENDR	6	/* sending read command packet */
#define	TUS_SENDW	7	/* sending write command packet */
#define	TUS_GETH	8	/* reading header */
#define	TUS_GETD	9	/* reading data */
#define	TUS_GETC	10	/* reading checksum */
#define	TUS_GET		11	/* reading an entire packet */
#define	TUS_WAIT	12	/* waiting for continue */
I 3
#define	TUS_RCVERR	13	/* receiver error in pseudo DMA routine */
#define	TUS_CHKERR	14	/* checksum error in pseudo DMA routine */
E 3

D 3
#define	TUS_NSTATES	13
E 3
I 3
#define	TUS_NSTATES	15
E 3

#define	printstate(state) \
	if ((state) < TUS_NSTATES) \
		printf("%s", tustates[(state)]); \
	else \
		printf("%d", (state));

/*
 * Packet Flags
 */
#define	TUF_DATA	1		/* data packet */
#define	TUF_CMD		2		/* command packet */
#define	TUF_INITF	4		/* initialize */
#define	TUF_CONT	020		/* continue */
#define	TUF_XOFF	023		/* flow control */

/*
 * Op Codes
 */
#define	TUOP_NOOP	0		/* no operation */
#define	TUOP_INIT	1		/* initialize */
#define	TUOP_READ	2		/* read block */
#define	TUOP_WRITE	3		/* write block */
#define	TUOP_SEEK	5		/* seek to block */
#define TUOP_DIAGNOSE	7		/* run micro-diagnostics */
#define	TUOP_END	0100		/* end packet */

/*
 * Mod Flags
 */
#define TUMD_WRV        1               /* write with read verify */

/*
 * Switches
 */
#define	TUSW_MRSP	010		/* use Modified RSP */

E 1
