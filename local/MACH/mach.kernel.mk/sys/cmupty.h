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
 * $Log:	cmupty.h,v $
 * Revision 2.5  90/08/30  11:49:47  bohman
 * 	Ioctl changes for STDC.
 * 	[90/08/28            bohman]
 * 
 * Revision 2.4  89/03/09  22:02:55  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  17:52:28  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/08/24  02:24:32  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:10:39  mwyoung]
 *
 * 31-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Include types.h.
 *
 * 09-Sep-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added new fields and flags to support select() on control
 *	files;  added PTYNOIOCTL mode bit definition and new PIOCDGET
 *	definition.
 *
 * 02-May-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Move NPTY definition into code file to avoid conflicts with
 *	the configuration symbol in the "other" pty driver.
 *
 * 15-May-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded to 4.2BSD.  Fixed bug which omitted ATTACHFLG from
 *	ptynread() macro.
 *	[V1(1)]
 *
 * 19-Nov-84  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added new definitions to support detaching of pseudo-
 *	terminals: ATTACHMSG, and ATTACHFLG to implement new control
 *	message, PTYLOGGEDIN, PTYDETACHED, and PTYDETHUP to record this
 *	status for a pseudo terminal, and new pt_ldev field in the
 *	control structure as a back link to the index of the logical
 *	control file mapping table; added new PIOCMGET definition
 *	(V3.07l).
 *
 * 10-May-83  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added ptioctlbuf_t definition for the ioctl reply buffer (V3.06j).
 *
 * 28-Mar-83  Mike Accetta (mja) at Carnegie-Mellon University
 *	Removed defunct PIOCGLOC definition;  added new PIOCSLOC definition
 *	(V3.06h).
 *
 * 10-Aug-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added PIOCMBIS and PIOCMBIC definitions, new PTYNOBLOCK,
 *	PTYNEWSIG and PTYHOLDSIG mode bits and PTYPRIVMODES definitions;
 *	made the non-privileged mode bit definitions accessible outside
 *	of the KERNEL conditional (V3.05e).
 *
 * 10-Jul-82  David Nichols (nichols) at Carnegie-Mellon University
 *	Changed ptynread() macro to check tp->t_state as well as
 *	tp->t_outq.c_cc to tell if a WRITEMSG would be given to a
 *	reader of the control pty (V3.05c).
 *
 * 07-Jul-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added PIOCGLOC call (currently unused by kernel) for returning
 *	terminal connection location information from servers running
 *	pseudo terminals (V3.05c).
 *
 * 29-Jun-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added fields for signal processing to control structure, PIOCENBS
 *	definition and ptynread() macro to test if input is pending on
 *	the control pty; increased NPTY from 20 to 26 (V3.05b).
 *
 * 15-Oct-80  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added message types and structure definitions for multiple control and
 *	new ioctl fetatures (V1.09h).
 *
 * 03-Jul-80  Mike Accetta (mja) at Carnegie-Mellon University
 *	Created (V1.08).
 *
 */

#ifndef	_SYS_CMUPTY_H_
#define _SYS_CMUPTY_H_

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/ttyloc.h>

#define NPTYL	5		/* maximum of 16 (4-bit mask) */

#define OPENMSG	  1
#define CLOSEMSG  2
#define STATEMSG  3
#define IOCTLMSG  4
#define WRITEMSG  5
#define CCMSG	  6
#define ATTACHMSG 7

#define OPENREPLY  50
#define CLOSEREPLY 51
#define IOCTLREPLY 52

#define IOCTLDATA  75
#define READDATA   76

struct ptymsg
{
    unsigned char pt_msg;		/* message identifier */
    unsigned char pt_arg;		/* message argument */
    unsigned char pt_aux;		/* auxiliary message argument */
    unsigned char pt_line;		/* line generating message */
};

struct ptyreply
{
    unsigned char pt_reply;		/* reply identifier */
    unsigned char pt_error;		/* reply error code */
    unsigned char pt_len;		/* reply non-data length */
    unsigned char pt_line;		/* line to receive reply */
};


#define PTYLBITS	(4)		/* bits in ioctl line */
#define PTYLMASK	(017)		/* PTYLBITS of line mask */

/*
 *  Note: The PTYLBITS definition above limits the number of PTY
 *  ioctl calls to 16 (the remaining 4 bits in the low byte of
 *  the code).
 */
#ifdef	__STDC__
#define PIOCXIOC	_IO  ('P', ( 0<<PTYLBITS))
#define PIOCSEOF	_IO  ('P', ( 1<<PTYLBITS))
#define PIOCSSIG	_IOW ('P', ( 3<<PTYLBITS), int)
#define PIOCCONN	_IOR ('P', ( 4<<PTYLBITS), struct ptymsg)
#define PIOCSIM		_IO  ('P', ( 5<<PTYLBITS))	/* obsolete */
#define PIOCNOSIM	_IO  ('P', ( 6<<PTYLBITS))	/* obsolete */
#define PIOCCCMSG	_IO  ('P', ( 7<<PTYLBITS))	/* obsolete */
#define PIOCNOCCMSG	_IO  ('P', ( 8<<PTYLBITS))	/* obsolete */
#define PIOCENBS	_IOW ('P', ( 9<<PTYLBITS), int)
#define PIOCMBIS	_IOW ('P', (10<<PTYLBITS), int)
#define PIOCMBIC	_IOW ('P', (11<<PTYLBITS), int)
#define PIOCSLOC	_IOW ('P', (12<<PTYLBITS), struct ttyloc)
#define PIOCMGET	_IOR ('P', (13<<PTYLBITS), int)
#define PIOCDGET	_IOR ('P', (14<<PTYLBITS), int)
#else
#define PIOCXIOC	_IO  (P, ( 0<<PTYLBITS))
#define PIOCSEOF	_IO  (P, ( 1<<PTYLBITS))
#define PIOCSSIG	_IOW (P, ( 3<<PTYLBITS), int)
#define PIOCCONN	_IOR (P, ( 4<<PTYLBITS), struct ptymsg)
#define PIOCSIM		_IO  (P, ( 5<<PTYLBITS))	/* obsolete */
#define PIOCNOSIM	_IO  (P, ( 6<<PTYLBITS))	/* obsolete */
#define PIOCCCMSG	_IO  (P, ( 7<<PTYLBITS))	/* obsolete */
#define PIOCNOCCMSG	_IO  (P, ( 8<<PTYLBITS))	/* obsolete */
#define PIOCENBS	_IOW (P, ( 9<<PTYLBITS), int)
#define PIOCMBIS	_IOW (P, (10<<PTYLBITS), int)
#define PIOCMBIC	_IOW (P, (11<<PTYLBITS), int)
#define PIOCSLOC	_IOW (P, (12<<PTYLBITS), struct ttyloc)
#define PIOCMGET	_IOR (P, (13<<PTYLBITS), int)
#define PIOCDGET	_IOR (P, (14<<PTYLBITS), int)
#endif

#ifdef	KERNEL
typedef struct sgttyb	ptioctlbuf_t;

struct ptyctrl
{
    int pt_state;			/* pty control state bits */
    int pt_ostate;			/* previous tty state bits */
    int pt_orcc;			/* previous raw character count */
    char pt_openbuf;			/* open reply buffer */
    char pt_closebuf;			/* close reply buffer */
    short pt_buflen;			/* ioctl reply length */
    int pt_cmdbuf;			/* ioctl cmd word (must be here) */
    ptioctlbuf_t pt_ioctlbuf;		/* ioctl reply buffer */
    struct ptyctrl *pt_cpty;		/* master multiplex pty */
    struct ptyctrl *pt_ctrl[NPTYL];	/* multiplex line pointers */
    struct proc *pt_sigp;		/* signal process pointer */ 
    u_short pt_pid;			/* PID of signal process */
    u_short pt_sign;			/* signal number to send */
    unsigned char pt_next;		/* next line for multiplex read */
    unsigned char pt_high;		/* highest line assigned */
    dev_t pt_mdev;			/* device number of pty */
    dev_t pt_ldev;			/* device number of control file */
    struct proc *pt_rselp;		/* read select process */
    struct proc *pt_wselp;		/* write select process */
};

#define OPENFLG	    0x1			/* waiting for open reply */
#define OPENINPROG  0x2			/* open in progress */
#define CLOSEFLG    0x4			/* waiting for close reply */
#define CLOSEINPROG 0x8			/* close in progress */
#define IOCTLFLG    0x10		/* waiting for ioctl reply */
#define IOCTLINPROG 0x20		/* ioctl in progress */
#define CCFLG	    0x40		/* character count */
#define ATTACHFLG   0x80		/* newly attached */
#define PTYRSELCOLL 0x100		/* read select collision */
#define PTYWSELCOLL 0x200		/* write select collision */
#endif	KERNEL

#define PTYNOIOCTL  0x100000		/* disable all ioctl() forwarding */
#define PTYDETHUP   0x200000		/* send HANGUP on detach condition */
#define PTYLOGGEDIN 0x400000		/* application terminal "logged-in" */
#define PTYDETACHED 0x800000		/* application terminal "detached" */
#define PTYNEWSIG   0x1000000		/* return 1 byte on new signals */
#define PTYHOLDSIG  0x2000000		/* keep signal enabled after sending */
#define PTYNOBLOCK  0x4000000		/* do not block on control reads */
#define PTYCCMSG    0x8000000		/* generate character count messages */
#define PTYSIM	    0x10000000		/* force read to fill buffer */

#ifdef	KERNEL
#define PTYEOF	    0x20000000		/* force read to return EOF */
#define OUTPUTWAIT  0x40000000		/* pty output wait */
#define PTYINUSE    0x80000000		/* pty control in use */

/*
 *  State (mode) bit masks.
 *
 *  RW (read/write) can be examined and changed by the control process.
 *  RO (read-only) can only be examined by the control process.
 */
#define PTYRWMODES (PTYNEWSIG|PTYHOLDSIG|PTYNOBLOCK|PTYCCMSG|PTYSIM|PTYDETHUP|PTYNOIOCTL)
#define PTYROMODES (PTYLOGGEDIN)


/*
 *  Read will return control or data information.
 */

#define ptywread(cp, tp)	\
	(ptywxread(cp, tp) || ptywdread(tp))

/*
 *  Read will return control information.
 */

#define ptywxread(cp, tp)	\
	((cp)->pt_state&(ATTACHFLG|OPENFLG|IOCTLFLG|CLOSEFLG|CCFLG) || \
	 ((tp)->t_state != (cp)->pt_ostate))

/*
 *  Read will return data bytes.
 */
#define ptywdread(tp)		\
	(((tp)->t_outq.c_cc > 0) && \
	 !((tp)->t_state&(TS_TIMEOUT|TS_BUSY|TS_TTSTOP)))

#endif	KERNEL
#endif	_SYS_CMUPTY_H_
