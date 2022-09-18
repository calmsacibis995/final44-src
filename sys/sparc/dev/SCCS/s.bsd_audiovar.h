h25743
s 00002/00002/00065
d D 8.1 93/06/11 15:08:05 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00002/00061
d D 7.3 93/04/20 05:46:21 torek 3 2
c van's changes (const for SunOS; add backlog control)
e
s 00005/00000/00058
d D 7.2 92/07/21 16:37:55 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00058/00000/00000
d D 7.1 92/07/13 00:41:27 torek 1 0
c date and time created 92/07/13 00:41:27 by torek
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 3
 *	California, Lawrence Berkeley Laboratories.
E 3
I 3
 *	California, Lawrence Berkeley Laboratory.
E 3
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: bsd_audiovar.h,v 1.4 92/07/03 23:23:12 mccanne Exp $ (LBL)
E 3
I 3
 * from: $Header: bsd_audiovar.h,v 1.6 92/11/21 20:46:49 van Exp $ (LBL)
E 3
 */

#define AUCB_SIZE 4096
#define AUCB_MOD(k)	((k) & (AUCB_SIZE - 1))

#define AUCB_INIT(cb)	((cb)->cb_head = (cb)->cb_tail = (cb)->cb_drops = \
			 (cb)->cb_pdrops = 0)

#define AUCB_EMPTY(cb)	((cb)->cb_head == (cb)->cb_tail)
#define AUCB_FULL(cb)	(AUCB_MOD((cb)->cb_tail + 1) == (cb)->cb_head)
#define AUCB_LEN(cb)	(AUCB_MOD((cb)->cb_tail - (cb)->cb_head))

#define MAXBLKSIZE (AUCB_SIZE / 2)
#define DEFBLKSIZE 128

#ifndef LOCORE
/*
 * aucb's are used for communication between the trap handler and
 * the software interrupt.
 */
struct aucb {
	int	cb_head;		/* queue head */
	int	cb_tail;		/* queue tail */
	int	cb_thresh;		/* threshold for wakeup */
	u_short	cb_waking;		/* needs wakeup at softint level */
	u_short	cb_pause;		/* io paused */
	u_long	cb_drops;		/* missed samples from over/underrun */
	u_long	cb_pdrops;		/* sun compat -- paused samples */
	u_char	cb_data[AUCB_SIZE];	/* data buffer */
};

#if !defined(__STDC__) && !defined(volatile)
#define volatile
#endif
I 3
#if !defined(__STDC__) && !defined(const)
#define const
#endif
E 3

struct auio {
	volatile struct amd7930 *au_amd;/* chip registers */
	u_long	au_stamp;		/* time stamp */
	int	au_lowat;		/* xmit low water mark (for wakeup) */
	int	au_hiwat;		/* xmit high water mark (for wakeup) */
	int	au_blksize;		/* recv block (chunk) size */
I 3
	int	au_backlog;		/* # samples of xmit backlog to gen. */
E 3
	struct	aucb au_rb;		/* read (recv) buffer */
	struct	aucb au_wb;		/* write (xmit) buffer */
};
#endif
E 1
