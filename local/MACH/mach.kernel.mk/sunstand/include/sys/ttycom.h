/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ttycom.h,v $
 * Revision 2.2  89/07/12  00:16:28  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)ttycom.h 1.5 88/02/08 SMI	*/

#ifndef _TTYCOM_
#define _TTYCOM_

/*
 * Window/terminal size structure.
 * This information is stored by the kernel
 * in order to provide a consistent interface,
 * but is not used by the kernel.
 *
 * Type must be "unsigned short" so that types.h not required.
 */
struct winsize {
	unsigned short	ws_row;		/* rows, in characters */
	unsigned short	ws_col;		/* columns, in characters */
	unsigned short	ws_xpixel;	/* horizontal size, pixels - not used */
	unsigned short	ws_ypixel;	/* vertical size, pixels - not used */
};

#define	TIOCGWINSZ	_IOR(t, 104, struct winsize)	/* get window size */
#define	TIOCSWINSZ	_IOW(t, 103, struct winsize)	/* set window size */

/*
 * Sun version of same.
 */
struct ttysize {
	int	ts_lines;	/* number of lines on terminal */
	int	ts_cols;	/* number of columns on terminal */
};

#define	TIOCSSIZE	_IOW(t,37,struct ttysize)/* set tty size */
#define	TIOCGSIZE	_IOR(t,38,struct ttysize)/* get tty size */

/*
 * 4.3BSD and SunOS terminal "ioctl"s with no "termios" equivalents.
 * This file is included by <sys/termios.h> and indirectly by <sys/ioctl.h>
 * so that programs that include either one have these "ioctl"s defined.
 */
#define	TIOCGPGRP	_IOR(t, 119, int)	/* get pgrp of tty */
#define	TIOCSPGRP	_IOW(t, 118, int)	/* set pgrp of tty */
#define	TIOCOUTQ	_IOR(t, 115, int)	/* output queue size */
#define	TIOCSTI		_IOW(t, 114, char)	/* simulate terminal input */
#define	TIOCNOTTY	_IO(t, 113)		/* void tty association */
#define	TIOCPKT		_IOW(t, 112, int)	/* pty: set/clear packet mode */
#define		TIOCPKT_DATA		0x00	/* data packet */
#define		TIOCPKT_FLUSHREAD	0x01	/* flush data not yet written to controller */
#define		TIOCPKT_FLUSHWRITE	0x02	/* flush data read from controller but not yet processed */
#define		TIOCPKT_STOP		0x04	/* stop output */
#define		TIOCPKT_START		0x08	/* start output */
#define		TIOCPKT_NOSTOP		0x10	/* no more ^S, ^Q */
#define		TIOCPKT_DOSTOP		0x20	/* now do ^S, ^Q */
#define		TIOCPKT_IOCTL		0x40	/* "ioctl" packet */
#define	TIOCMSET	_IOW(t, 109, int)	/* set all modem bits */
#define	TIOCMBIS	_IOW(t, 108, int)	/* bis modem bits */
#define	TIOCMBIC	_IOW(t, 107, int)	/* bic modem bits */
#define	TIOCMGET	_IOR(t, 106, int)	/* get all modem bits */
#define		TIOCM_LE	0001		/* line enable */
#define		TIOCM_DTR	0002		/* data terminal ready */
#define		TIOCM_RTS	0004		/* request to send */
#define		TIOCM_ST	0010		/* secondary transmit */
#define		TIOCM_SR	0020		/* secondary receive */
#define		TIOCM_CTS	0040		/* clear to send */
#define		TIOCM_CAR	0100		/* carrier detect */
#define		TIOCM_CD	TIOCM_CAR
#define		TIOCM_RNG	0200		/* ring */
#define		TIOCM_RI	TIOCM_RNG
#define		TIOCM_DSR	0400		/* data set ready */

#define	TIOCREMOTE	_IOW(t, 105, int)	/* remote input editing */
#define	TIOCUCNTL	_IOW(t, 102, int)	/* pty: set/clr usr cntl mode */

/*
 * Sun-specific ioctls with no "termios" equivalents.
 */
#define TIOCTCNTL	_IOW(t, 32, int)	/* pty: set/clr intercept ioctl mode */
#define TIOCSIGNAL	_IOW(t, 33, int)	/* pty: send signal to slave */
#define	TIOCCONS	_IO(t, 36)		/* get console I/O */
#define	TIOCSSOFTCAR	_IOW(t, 101, int)	/* set soft carrier flag */
#define	TIOCGSOFTCAR	_IOR(t, 100, int)	/* get soft carrier flag */

#endif
