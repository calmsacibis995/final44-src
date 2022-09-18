/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	drreg.h,v $
 * Revision 2.3  89/03/09  22:33:16  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  11:01:50  gm0w
 * 	Changes for cleanup.
 * 
 * 08-Aug-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded from 4.1BSD.
 *	[V1(1)]
 *
 * 15-Dec-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	Corrected macro defining drer register (V3.06b).
 *
 * 23-Apr-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	Restructured for new DR11-B/W driver (V3.04g).
 *
 * 30-Nov-81  Mike Accetta (mja) at Carnegie-Mellon University
 *	Extracted from dr.c (V3.03d).
 *
 */

/*	drreg.h	CMU	11/30/81	*/

#ifdef	KERNEL

#define DRUNITBITS	3			/* number of low order */
						/*  minor device bits */
						/*  indicating physical */
						/*  unit number */
#define DRUNITMASK	((1<<DRUNITBITS)-1)	/* minor device unit */
						/*  number mask */
#define DRUNIT(dev)  	(minor(dev)&DRUNITMASK)	/* extract DR11 unit number */
						/*  from device number */

#define MAXDRDMA	(40*1024)		/* maximum number of bytes */
						/*  per UNIBUS DMA operation */
						/*  (split into multiple */
						/*  operations if exceeded) */


/*
 *  DR11 device register assignments
 */

struct drdevice
{
    short drwc;				/* word count */
    short drba;				/* unibus address */
    short drst;				/* control/status */
    short drdb;				/* data buffer */
};
#define drer	drst			/* error information (DR11-W) */

#define DRADDR	((struct drdevice *)ui->ui_addr)


/*
 *  dr_com()	uses the unused b_blkno field of the buffer head to store
 *		device function control bits
 *  dr_tout()	computes the number of seconds before a timeout based on
 *		the length of the transfer
 */
#define dr_com(bp)	((bp)->b_blkno)
#define dr_tout(bp)	(((bp)->b_bcount/8192)+15)

/*
 *  These macros are intended to insulate the user device interfaces
 *  from directly accessing the DR11 state structure.
 *
 *  dr_state()	 sets the device state for the unit as indicated
 *  dr_logunit() sets the device logical unit as indicated
 */
#define dr_state(unit)		drstat[unit].drs_state
#define dr_logunit(unit)	drstat[unit].drs_logunit

/*
 *  spl_dr()	raises IPL to the priority at which the specified unit
 *		interrupted at configuration time
 */
#define spl_dr(ui)	splx((int)drstat[ui->ui_unit].drs_ipl)


/*
 *  User device interface routine linkage structure
 */
struct drdevsw
{
	int	(*drsw_open)();
	int	(*drsw_close)();
	int	(*drsw_read)();
	int	(*drsw_write)();
	int	(*drsw_ioctl)();
	int	(*drsw_intr)();
	int	(*drsw_reset)();
	int	(*drsw_tout)();
	int	(*drsw_attach)();
};


/*  Bits in flags word (set during attach)  */
#define DR11B	040000			/* device is a DR11-B */
#define DR11W	0100000			/* device is a DR11-W */


/*  Unit state (index by unit number)  */
struct drstat
{
    struct buf	 drs_tab;	/* device queue header */
    struct proc *drs_sigp;	/* process to signal on interrupt */
    u_short	 drs_open;	/* open count */
    u_short	 drs_pid;	/* process ID */
    u_short	 drs_sign;	/* signal to send */
    u_short	 drs_csr;	/* software copy of csr bits (IE) */
    u_char	 drs_ipl;	/* interrupt priority level from drprobe() */
    u_char	 drs_state;	/* driver state (see below) */
    u_char	 drs_logunit;	/* user device logical unit number */
};
extern struct drstat drstat[];

/*  driver states  */
#define DRS_IDLE	00		/* not within driver */
#define DRS_DMA		01		/* performing DMA read */
#define DRS_TOUT	02		/* DMA timed out */
#define DRS_ERROR	03		/* fatal error (requires reset) */
#define DRS_IE		04		/* expecting spurious interrupt */
#endif	KERNEL


/*  bits in control/status word  */
#define DRCSR_ERR	0100000
#define DRCSR_NXM	040000
#define DRCSR_ATTN	020000
#define DRCSR_MAINT	010000
#define DRCSR_STATA	04000
#define DRCSR_STATB	02000
#define DRCSR_STATC	01000
#define DRCSR_CYCLE	0400
#define DRCSR_RDY	0200
#define DRCSR_IE	0100
#define DRCSR_XMEM	060
#define DRCSR_FUNC3	010
#define DRCSR_FUNC2	04
#define DRCSR_FUNC1	02
#define DRCSR_FUNC	(DRCSR_FUNC3|DRCSR_FUNC2|DRCSR_FUNC1)
#define DRCSR_GO	01

#define DRCSR_BITS "\10\20ERR\17NXM\16ATTN\15MAINT\14A\13B\12C\11\CYCLE\10RDY\7IE\6X17\5X16\4F3\3F2\2F1\1GO"

struct drreg
{
    u_short drr_wc;
    u_short drr_ba;
    u_short drr_st;
    u_short drr_db;
    u_short drr_er;
};

/*
 *  DR11 ioctl definitions needed by user process
 */

#define DRIOCENBS	_IOW (D, 255, int)
#define DRIOCGETR	_IOR (D, 254, struct drreg)
#define DRIOCSSTR	_IOW (D, 253, short)
#define DRIOCSDBR	_IOW (D, 252, short)
#define DRIOCASYNC	_IO  (D, 251)
