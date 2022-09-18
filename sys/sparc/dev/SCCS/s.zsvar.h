h20437
s 00002/00002/00117
d D 8.1 93/06/11 15:08:44 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00045/00028/00074
d D 7.3 93/04/20 06:06:41 torek 3 2
c update from elf: more stuff in ring, better packing, etc
e
s 00005/00000/00097
d D 7.2 92/07/21 16:38:04 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00097/00000/00000
d D 7.1 92/07/13 00:41:32 torek 1 0
c date and time created 92/07/13 00:41:32 by torek
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
 * from: $Header: zsvar.h,v 1.4 92/06/17 05:35:54 torek Exp $ (LBL)
E 3
I 3
 * from: $Header: zsvar.h,v 1.7 92/11/26 01:28:04 torek Exp $ (LBL)
E 3
 */

/*
 * Software state, per zs channel.
 *
D 3
 * The receive ring size and type are carefully chosen to make the
 * zs hardware interrupt handler go fast.  We need 8 bits for the
 * received character and 8 bits for the corresponding RR1 status.
 * The character is known to be in the upper byte of the pair.
E 3
I 3
 * The zs chip has insufficient buffering, so we provide a software
 * buffer using a two-level interrupt scheme.  The hardware (high priority)
 * interrupt simply grabs the `cause' of the interrupt and stuffs it into
 * a ring buffer.  It then schedules a software interrupt; the latter
 * empties the ring as fast as it can, hoping to avoid overflow.
 *
 * Interrupts can happen because of:
 *	- received data;
 *	- transmit pseudo-DMA done; and
 *	- status change.
 * These are all stored together in the (single) ring.  The size of the
 * ring is a power of two, to make % operations fast.  Since we need two
 * bits to distinguish the interrupt type, and up to 16 for the received
 * data plus RR1 status, we use 32 bits per ring entry.
 *
 * When the value is a character + RR1 status, the character is in the
 * upper 8 bits of the RR1 status.
E 3
 */
D 3
#define ZLRB_RING_SIZE 256
#define	ZLRB_RING_MASK 255
E 3
I 3
#define ZLRB_RING_SIZE 256		/* ZS line ring buffer size */
#define	ZLRB_RING_MASK 255		/* mask for same */
E 3

I 3
/* 0 is reserved (means "no interrupt") */
#define	ZRING_RINT	1		/* receive data interrupt */
#define	ZRING_XINT	2		/* transmit done interrupt */
#define	ZRING_SINT	3		/* status change interrupt */

#define	ZRING_TYPE(x)	((x) & 3)
#define	ZRING_VALUE(x)	((x) >> 8)
#define	ZRING_MAKE(t, v)	((t) | (v) << 8)

E 3
struct zs_chanstate {
	struct	zs_chanstate *cs_next;	/* linked list for zshard() */
	volatile struct zschan *cs_zc;	/* points to hardware regs */
	int	cs_unit;		/* unit number */
	struct	tty *cs_ttyp;		/* ### */

	/*
	 * We must keep a copy of the write registers as they are
	 * mostly write-only and we sometimes need to set and clear
	 * individual bits (e.g., in WR3).  Not all of these are
	 * needed but 16 bytes is cheap and this makes the addressing
	 * simpler.  Unfortunately, we can only write to some registers
	 * when the chip is not actually transmitting, so whenever
D 3
	 * we are expecting a `transmit done' interrupt the wreg array
E 3
I 3
	 * we are expecting a `transmit done' interrupt the preg array
E 3
	 * is allowed to `get ahead' of the current values.  In a
	 * few places we must change the current value of a register,
	 * rather than (or in addition to) the pending value; for these
	 * cs_creg[] contains the current value.
	 */
	u_char	cs_creg[16];		/* current values */
	u_char	cs_preg[16];		/* pending values */
	u_char	cs_heldchange;		/* change pending (creg != preg) */
I 3
	u_char	cs_rr0;			/* last rr0 processed */
E 3

I 3
	/* pure software data, per channel */
	char	cs_softcar;		/* software carrier */
	char	cs_conk;		/* is console keyboard, decode L1-A */
	char	cs_brkabort;		/* abort (as if via L1-A) on BREAK */
	char	cs_kgdb;		/* enter debugger on frame char */
	char	cs_consio;		/* port does /dev/console I/O */
	char	cs_xxx;			/* (spare) */
	int	cs_speed;		/* default baud rate (from ROM) */

E 3
	/*
	 * The transmit byte count and address are used for pseudo-DMA
	 * output in the hardware interrupt code.  PDMA can be suspended
	 * to get pending changes done; heldtbc is used for this.  It can
	 * also be stopped for ^S; this sets TS_TTSTOP in tp->t_state.
	 */
	int	cs_tbc;			/* transmit byte count */
	caddr_t	cs_tba;			/* transmit buffer address */
	int	cs_heldtbc;		/* held tbc while xmission stopped */

	/*
	 * Printing an overrun error message often takes long enough to
	 * cause another overrun, so we only print one per second.
	 */
	long	cs_rotime;		/* time of last ring overrun */
	long	cs_fotime;		/* time of last fifo overrun */

D 3
	/* pure software data, per channel */
	int	cs_speed;		/* default baud rate (from ROM) */
	char	cs_softcar;		/* software carrier */
	char	cs_conk;		/* is console keyboard, decode L1-A */
	char	cs_brkabort;		/* abort (as if via L1-A) on BREAK */
	char	cs_kgdb;		/* enter debugger on frame char */
	char	cs_consio;		/* port does /dev/console I/O */

E 3
	/*
D 3
	 * Status change interrupts merely copy the new status and
	 * schedule a software interrupt to deal with it.  To make
	 * checking easier, cs_rr0 is guaranteed nonzero on status
	 * changes.  cs_txint indicates a software transmit interrupt
	 * (a txint where cs_tbc was 0).  A software receive interrupt
	 * is implicit in cs_rbget != cs_rbput.
E 3
I 3
	 * The ring buffer.
E 3
	 */
D 3
	u_char	cs_txint;		/* software tx interrupt */
	u_short	cs_rr0;			/* rr0 | 0x100, after change */
	u_int	cs_rbget;		/* receive ring buffer `get' index */
	volatile u_int cs_rbput;	/* receive ring buffer `put' index */
	u_short	cs_rbuf[ZLRB_RING_SIZE];/* packed data: (char << 8) + rr1 */
E 3
I 3
	u_int	cs_rbget;		/* ring buffer `get' index */
	volatile u_int cs_rbput;	/* ring buffer `put' index */
	int	cs_rbuf[ZLRB_RING_SIZE];/* type, value pairs */
E 3
};

/*
 * Macros to read and write individual registers (except 0) in a channel.
 *
 * On the SparcStation the 1.6 microsecond recovery time is
 * handled in hardware.
 */
#define	ZS_READ(c, r)		((c)->zc_csr = (r), (c)->zc_csr)
#define	ZS_WRITE(c, r, v)	((c)->zc_csr = (r), (c)->zc_csr = (v))
E 1
