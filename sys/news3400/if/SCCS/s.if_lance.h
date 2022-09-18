h45060
s 00002/00002/00060
d D 8.1 93/06/11 14:57:07 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00062/00000/00000
d D 7.1 92/06/04 15:59:12 mckusick 1 0
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
 * from: $Hdr: if_lance.h,v 4.300 91/06/09 06:25:59 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

#undef VOLATILE
#ifdef mips
#define VOLATILE volatile
#else
#define VOLATILE
#endif

typedef VOLATILE struct lance Lance_reg;
typedef VOLATILE struct recv_msg_desc recv_msg_desc;
typedef VOLATILE struct xmit_msg_desc xmit_msg_desc;

/*
 * Structure of statistics record
 */
struct en_stats {
	u_char	ens_addr[8];		/* Ethernet Address */
	int	ens_frames;		/* Number of Frames Received */
	int	ens_xmit;		/* Number of Frames Transmitted */
	int	ens_xcollis;		/* Number of Excess Collisions */
	int	ens_frag;		/* Number of Fragments Received */
	int	ens_lost;		/* Number of Times Frames Lost */
	int	ens_crc;		/* Number of CRC Errors */
	int	ens_align;		/* Number of Alignment Errors */
	int	ens_collis;		/* Number of Collisions */
	int	ens_owcollis;		/* Number of Out-of-window Collisions */
};

/*
 *	LANCE control block
 */
typedef	VOLATILE struct lance_chan {
	Lance_reg	*lance_addr;	/* LANCE port address		*/
	caddr_t 	lance_memory;	/* LANCE memory address		*/
	caddr_t		lance_rom;	/* Ethernet address ROM		*/
	struct init_block *lance_ib;	/* initialization block address	*/
	int		lance_flags;	/* LANCE active flag		*/
	recv_msg_desc	*lance_rmd;	/* recv. message desc. address	*/
	xmit_msg_desc	*lance_tmd;	/* xmit. message desc. address	*/
	recv_msg_desc	*lance_last_rmd;	/* last rmd		*/
	xmit_msg_desc	*lance_last_tmd;	/* last tmd		*/
	struct en_stats	lance_stats;	/* LANCE statistics		*/
} Lance_chan;

#undef VOLATILE

#define	LANCE_ACTIVE	1
#define	LANCE_PROM	2
#define	LANCE_IDON	8
E 1
