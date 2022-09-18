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
 * $Log:	ioctl.h,v $
 * Revision 2.15  89/07/12  01:27:56  jjc
 * 	Defined NTABLDISC for Sun.
 * 	[89/07/05  21:14:36  jjc]
 * 
 * Revision 2.14  89/05/03  14:58:31  mikeg
 * 	Defined TIOCGSIZE and TIOCSSIZE to be TIOCGWINSZ and
 * 	TIOCSWINSZ respectively and made other modifications
 * 	to the TIOC[GS]SIZE family of ioctl's so that both X
 * 	and Suntools will run correctly on Sun's.
 * 	[89/04/12  12:08:28  mikeg]
 * 
 * Revision 2.13  89/03/09  22:05:08  rpd
 * 	More cleanup.
 * 
 * Revision 2.12  89/02/25  17:54:17  gm0w
 * 	Made all code that depended on CMUCS unconditional
 * 	except for ttyloc stuff.
 * 	[89/02/14            mrt]
 * 
 * Revision 2.11  89/01/23  22:26:42  af
 * 	Added a bunch of Mips-specific ioctls.
 * 	[89/01/04            af]
 * 
 * Revision 2.10  88/12/13  13:19:29  mikeg
 * 	Enclosed new Sun specific ioctl's I added previously
 * 	in "#ifdef sun" conditional.
 * 
 * Revision 2.9  88/12/08  15:36:01  mikeg
 * 	Added the Sun ioctl's TIOCSSIZE, _O_TIOCSSIZE,
 * 	_N_TIOCSSIZE, TIOCGSIZE, _O_TIOCGSIZE, and _N_TIOCGSIZE
 * 	to allow Suntools to run on Mach.
 * 	[88/11/30  12:16:14  mikeg]
 * 
 * Revision 2.7  88/11/14  14:34:08  gm0w
 * 	Added CSNET DialupIP support.
 * 	[88/11/14            gm0w]
 * 
 * Revision 2.6  88/09/27  17:31:58  rvb
 * 	Fixed Log
 * 
 * Revision 2.5  88/09/27  16:08:19  rvb
 * 	QIOCCIFNCTRS: Clear interface counters.
 * 	[88/09/23            rvb]
 * 
 * Revision 2.4  88/08/24  02:29:23  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:13:38  mwyoung]
 *
 * Revision 2.3  88/08/22  21:29:21  mja
 * 	Flush obsolete SIOCBROAD definition.
 * 	[88/08/09  09:54:45  mja]
 * 	
 * 	Delete obsolete TIOCSCONS definition;  add TIOCVCONS and
 * 	TIOCGCONS definitions;  coalesce CMUCS conditionsals.
 * 	[88/08/04  17:59:21  mja]
 * 
 * 10-Nov-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fix to conditionalize all local exported names on only CMU or
 *	CMUCS and retain special purpose kernel conditionals as
 *	comments only; define TIOCCONS on all architectures.
 *	[ V5.1(XF21) ]
 *
 * 17-Mar-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Added TIOCSLOC definition.
 *	[ V5.1(F7) ]
 *
 *  7-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merge VICE changes -- include vice.h and change to #if VICE.
 *	The ioctl's for console munging should be consolidated.
 *
 * 30-Jan-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS: Added TIOCLOGINDEV definition;
 *	CMUCS: Added FIOCNOSPC definition.
 *	[ V5.1(F1) ]
 *
 * 29-Jan-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE:  restored 4.2 manifest TIOCSCONS.
 *
 * 24-Dec-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	romp: Added TIOCCONS ioctl for RT console silliness.
 *
 * 19-Nov-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Added FIOCFSPARAM.
 *	[ V5.1(F1) ]
 *
 *  5-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added for Sun:
 *	1) Added mouse and keyboard disciplines for Sun
 *
 * 22-Feb-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Fix incorrect read/write sense in TIOCCSET,
 *	TIOCCLOG, TIOCCHECK, and TIOCATTACH definitions.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 09-May-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded from 4.1BSD.  Carried over changes below.
 *	CMUCS:  Added new TIOCCSET call and CDETHUP and CBRKINH
 *	mode bits; added new TIOCCLOG, TIOCCHECK and TIOCATTACH calls;
 *	CMUCS:  Fixed to include sgtty.h from kernel area.
 *	[V1(1)]
 *
 * 28-Mar-83  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Added TIOCGLOC definition (V3.06h).
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)ioctl.h	7.1 (Berkeley) 6/4/86
 */
/*
 * Ioctl definitions
 */

#ifndef	_SYS_IOCTL_H_
#define _SYS_IOCTL_H_

#include <sys/ttychars.h>
#include <sys/ttydev.h>
#include <sys/types.h>
#ifdef	CMUCS
#include <sys/ttyloc.h>
#endif	CMUCS

struct tchars {
	char	t_intrc;	/* interrupt */
	char	t_quitc;	/* quit */
	char	t_startc;	/* start output */
	char	t_stopc;	/* stop output */
	char	t_eofc;		/* end-of-file */
	char	t_brkc;		/* input delimiter (like nl) */
};
struct ltchars {
	char	t_suspc;	/* stop process signal */
	char	t_dsuspc;	/* delayed stop process signal */
	char	t_rprntc;	/* reprint line */
	char	t_flushc;	/* flush output (toggles) */
	char	t_werasc;	/* word erase */
	char	t_lnextc;	/* literal next character */
};

/*
 * Structure for TIOCGETP and TIOCSETP ioctls.
 */

#ifndef	_SGTTYB_
#define _SGTTYB_
struct sgttyb {
	char	sg_ispeed;		/* input speed */
	char	sg_ospeed;		/* output speed */
	char	sg_erase;		/* erase character */
	char	sg_kill;		/* kill character */
	short	sg_flags;		/* mode flags */
};
#endif	_SGTTYB_

/*
 * Window/terminal size structure.
 * This information is stored by the kernel
 * in order to provide a consistent interface,
 * but is not used by the kernel.
 */
struct winsize {
	unsigned short	ws_row;			/* rows, in characters */
	unsigned short	ws_col;			/* columns, in characters */
	unsigned short	ws_xpixel;		/* horizontal size, pixels */
	unsigned short	ws_ypixel;		/* vertical size, pixels */
};

/*
 * Pun for SUN.
 */
struct ttysize {
	unsigned short	ts_lines;
	unsigned short	ts_cols;
	unsigned short	ts_xxx;
	unsigned short	ts_yyy;
};
#define	TIOCGSIZE	TIOCGWINSZ
#define	TIOCSSIZE	TIOCSWINSZ

#ifdef	KERNEL
#ifdef	sun

/*
 * The following structure and ioctl's have been added to allow
 * Suntools to run under Mach.
 */

/*
 * Sun version of the winsize struct.
 */
struct swsize {
	int	ts_lines;	/* number of lines on terminal */
	int	ts_cols;	/* number of columns on terminal */
};

/*
 * These ioctl's are used in Suntools.  Although they may seem to conflict
 * with existing 4.3 ioctl's, either the resulting value is different 
 * from the other ioctl with the same number or there is code in the 
 * appropriate driver to distinguish between them.
 */
#define	_O_TIOCSSIZE	_IOW(t,103,struct swsize)	/* set tty size */
#define	_O_TIOCGSIZE	_IOR(t,102,struct swsize)	/* get tty size */
#define	_N_TIOCSSIZE	_IOW(t,37,struct swsize)	/* set tty size */
#define	_N_TIOCGSIZE	_IOR(t,38,struct swsize)	/* get tty size */

#endif	sun
#endif	KERNEL


#ifndef	_IO
/*
 * Ioctl's have the command encoded in the lower word,
 * and the size of any in or out parameters in the upper
 * word.  The high 2 bits of the upper word are used
 * to encode the in/out status of the parameter; for now
 * we restrict parameters to at most 128 bytes.
 */
#define IOCPARM_MASK	0x7f		/* parameters must be < 128 bytes */
#define IOC_VOID	0x20000000	/* no parameters */
#define IOC_OUT		0x40000000	/* copy out parameters */
#define IOC_IN		0x80000000	/* copy in parameters */
#define IOC_INOUT	(IOC_IN|IOC_OUT)
/* the 0x20000000 is so we can distinguish new ioctl's from old */
#define _IO(x,y)	(IOC_VOID|('x'<<8)|y)
#define _IOR(x,y,t)	(IOC_OUT|((sizeof(t)&IOCPARM_MASK)<<16)|('x'<<8)|y)
#define _IOW(x,y,t)	(IOC_IN|((sizeof(t)&IOCPARM_MASK)<<16)|('x'<<8)|y)
/* this should be _IORW, but stdio got there first */
#define _IOWR(x,y,t)	(IOC_INOUT|((sizeof(t)&IOCPARM_MASK)<<16)|('x'<<8)|y)
#endif	_IO

/*
 * tty ioctl commands
 */
#define TIOCGETD	_IOR(t, 0, int)		/* get line discipline */
#define TIOCSETD	_IOW(t, 1, int)		/* set line discipline */
#define TIOCHPCL	_IO(t, 2)		/* hang up on last close */
#define TIOCMODG	_IOR(t, 3, int)		/* get modem control state */
#define TIOCMODS	_IOW(t, 4, int)		/* set modem control state */
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
#define TIOCGETP	_IOR(t, 8,struct sgttyb)/* get parameters -- gtty */
#define TIOCSETP	_IOW(t, 9,struct sgttyb)/* set parameters -- stty */
#define TIOCSETN	_IOW(t,10,struct sgttyb)/* as above, but no flushtty */
#define TIOCEXCL	_IO(t, 13)		/* set exclusive use of tty */
#define TIOCNXCL	_IO(t, 14)		/* reset exclusive use of tty */
#define TIOCFLUSH	_IOW(t, 16, int)	/* flush buffers */
#define TIOCSETC	_IOW(t,17,struct tchars)/* set special characters */
#define TIOCGETC	_IOR(t,18,struct tchars)/* get special characters */
#define		TANDEM		0x00000001	/* send stopc on out q full */
#define		CBREAK		0x00000002	/* half-cooked mode */
#define		LCASE		0x00000004	/* simulate lower case */
#define		ECHO		0x00000008	/* echo input */
#define		CRMOD		0x00000010	/* map \r to \r\n on output */
#define		RAW		0x00000020	/* no i/o processing */
#define		ODDP		0x00000040	/* get/send odd parity */
#define		EVENP		0x00000080	/* get/send even parity */
#define		ANYP		0x000000c0	/* get any parity/send none */
#define		NLDELAY		0x00000300	/* \n delay */
#define			NL0	0x00000000
#define			NL1	0x00000100	/* tty 37 */
#define			NL2	0x00000200	/* vt05 */
#define			NL3	0x00000300
#define		TBDELAY		0x00000c00	/* horizontal tab delay */
#define			TAB0	0x00000000
#define			TAB1	0x00000400	/* tty 37 */
#define			TAB2	0x00000800
#define		XTABS		0x00000c00	/* expand tabs on output */
#define		CRDELAY		0x00003000	/* \r delay */
#define			CR0	0x00000000
#define			CR1	0x00001000	/* tn 300 */
#define			CR2	0x00002000	/* tty 37 */
#define			CR3	0x00003000	/* concept 100 */
#define		VTDELAY		0x00004000	/* vertical tab delay */
#define			FF0	0x00000000
#define			FF1	0x00004000	/* tty 37 */
#define		BSDELAY		0x00008000	/* \b delay */
#define			BS0	0x00000000
#define			BS1	0x00008000
#define		ALLDELAY	(NLDELAY|TBDELAY|CRDELAY|VTDELAY|BSDELAY)
#define		CRTBS		0x00010000	/* do backspacing for crt */
#define		PRTERA		0x00020000	/* \ ... / erase */
#define		CRTERA		0x00040000	/* " \b " to wipe out char */
#define		TILDE		0x00080000	/* hazeltine tilde kludge */
#define		MDMBUF		0x00100000	/* start/stop output on carrier intr */
#define		LITOUT		0x00200000	/* literal output */
#define		TOSTOP		0x00400000	/* SIGSTOP on background output */
#define		FLUSHO		0x00800000	/* flush output to terminal */
#define		NOHANG		0x01000000	/* no SIGHUP on carrier drop */
#define		L001000		0x02000000
#define		CRTKIL		0x04000000	/* kill line with " \b " */
#define		PASS8		0x08000000
#define		CTLECH		0x10000000	/* echo control chars as ^X */
#define		PENDIN		0x20000000	/* tp->t_rawq needs reread */
#define		DECCTQ		0x40000000	/* only ^Q starts after ^S */
#define		NOFLSH		0x80000000	/* no output flush on signal */
/* locals, from 127 down */
#ifdef	CMUCS
#define TIOCGLOC	_IOR (t, 255, struct ttyloc) /* get terminal location */
#define TIOCSLOC	_IOW (t, 249, struct ttyloc) /* set terminal location */
#endif	CMUCS
#define TIOCCSET	_IOW (t, 254, int)
#define		CDETHUP	0000001
#define		CBRKINH	0000002
#define TIOCCLOG	_IOW (t, 253, int)
#define TIOCCHECK	_IOW (t, 252, int)
#define TIOCATTACH	_IOW (t, 251, int)
#define TIOCLOGINDEV	_IO  (t, 250)

#define TIOCVCONS	_IOW (t, 248, int)
#define		TIOCVCONS_DISABLE  0
#define		TIOCVCONS_ENABLE   1
#define		TIOCVCONS_DEASSIGN 2
#define		TIOCVCONS_ASSIGN   3
#define TIOCGCONS	_IOR (t, 247, struct tiocgcons)
struct tiocgcons {
    dev_t tgc_dev;	/* enabled on device */
    uid_t tgc_uid;	/* assigned to user ID */
};
#define		TIOCGCONS_NODEV ((dev_t)-1)	/* same as NODEV */
#define		TIOCGCONS_NOUID ((uid_t)-1)

#define TIOCLBIS	_IOW(t, 127, int)	/* bis local mode bits */
#define TIOCLBIC	_IOW(t, 126, int)	/* bic local mode bits */
#define TIOCLSET	_IOW(t, 125, int)	/* set entire local mode word */
#define TIOCLGET	_IOR(t, 124, int)	/* get local modes */
#define		LCRTBS		(CRTBS>>16)
#define		LPRTERA		(PRTERA>>16)
#define		LCRTERA		(CRTERA>>16)
#define		LTILDE		(TILDE>>16)
#define		LMDMBUF		(MDMBUF>>16)
#define		LLITOUT		(LITOUT>>16)
#define		LTOSTOP		(TOSTOP>>16)
#define		LFLUSHO		(FLUSHO>>16)
#define		LNOHANG		(NOHANG>>16)
#define		LCRTKIL		(CRTKIL>>16)
#define		LPASS8		(PASS8>>16)
#define		LCTLECH		(CTLECH>>16)
#define		LPENDIN		(PENDIN>>16)
#define		LDECCTQ		(DECCTQ>>16)
#define		LNOFLSH		(NOFLSH>>16)
#define TIOCSBRK	_IO(t, 123)		/* set break bit */
#define TIOCCBRK	_IO(t, 122)		/* clear break bit */
#define TIOCSDTR	_IO(t, 121)		/* set data terminal ready */
#define TIOCCDTR	_IO(t, 120)		/* clear data terminal ready */
#define TIOCGPGRP	_IOR(t, 119, int)	/* get pgrp of tty */
#define TIOCSPGRP	_IOW(t, 118, int)	/* set pgrp of tty */
#define TIOCSLTC	_IOW(t,117,struct ltchars)/* set local special chars */
#define TIOCGLTC	_IOR(t,116,struct ltchars)/* get local special chars */
#define TIOCOUTQ	_IOR(t, 115, int)	/* output queue size */
#define TIOCSTI		_IOW(t, 114, char)	/* simulate terminal input */
#define TIOCNOTTY	_IO(t, 113)		/* void tty association */
#define TIOCPKT		_IOW(t, 112, int)	/* pty: set/clear packet mode */
#define		TIOCPKT_DATA		0x00	/* data packet */
#define		TIOCPKT_FLUSHREAD	0x01	/* flush packet */
#define		TIOCPKT_FLUSHWRITE	0x02	/* flush packet */
#define		TIOCPKT_STOP		0x04	/* stop output */
#define		TIOCPKT_START		0x08	/* start output */
#define		TIOCPKT_NOSTOP		0x10	/* no more ^S, ^Q */
#define		TIOCPKT_DOSTOP		0x20	/* now do ^S ^Q */
#define TIOCSTOP	_IO(t, 111)		/* stop output, like ^S */
#define TIOCSTART	_IO(t, 110)		/* start output, like ^Q */
#define TIOCMSET	_IOW(t, 109, int)	/* set all modem bits */
#define TIOCMBIS	_IOW(t, 108, int)	/* bis modem bits */
#define TIOCMBIC	_IOW(t, 107, int)	/* bic modem bits */
#define TIOCMGET	_IOR(t, 106, int)	/* get all modem bits */
#define TIOCREMOTE	_IOW(t, 105, int)	/* remote input editing */

#define TIOCGWINSZ	_IOR(t, 104, struct winsize)	/* get window size */
#define TIOCSWINSZ	_IOW(t, 103, struct winsize)	/* set window size */
#define TIOCUCNTL	_IOW(t, 102, int)	/* pty: set/clr usr cntl mode */

#define		UIOCCMD(n)	_IO(u, n)		/* usr cntl op "n" */

#define TIOCCONS	_IO(t, 64)		/* Select console line */

#define OTTYDISC	0		/* old, v7 std tty driver */
#define NETLDISC	1		/* line discip for berk net */
#define NTTYDISC	2		/* new tty discipline */
#define TABLDISC	3		/* tablet discipline */
#define SLIPDISC	4		/* serial IP discipline */
#ifdef	sun
#define MOUSELDISC      5               /* mouse discipline */
#define KBDLDISC        6               /* up/down keyboard trans (console) */
#define NTABLDISC	7		/* gtco tablet discipline */
#endif	sun
#define DUDISC		7		/* Dialup IP discipline */


#define FIOCLEX		_IO(f, 1)		/* set exclusive use on fd */
#define FIONCLEX	_IO(f, 2)		/* remove exclusive use */

struct fsparam
{
    long fsp_free;		/* free 1K blocks */
    long fsp_ifree;		/* free inodes */
    long fsp_size;		/* total 1K fragments */
    long fsp_isize;		/* total inodes */
    long fsp_minfree;		/* minimum free block percentage */
    long fsp_unused[3];		/* currently unused */
};
#define FIOCFSPARAM	_IOR(f, 105, struct fsparam)
/* Disk space resource pause per-file control */
#define FIOCNOSPC	_IOWR(f, 106, int)
#define FIOCNOSPC_SAME	0			/* no change */
#define FIOCNOSPC_ERROR	1			/* prohibit pause */
#define FIOCNOSPC_PAUSE	2			/* allow pause */

/* another local */
#define FIONREAD	_IOR(f, 127, int)	/* get # bytes to read */
#define FIONBIO		_IOW(f, 126, int)	/* set/clear non-blocking i/o */
#define FIOASYNC	_IOW(f, 125, int)	/* set/clear async i/o */
#define FIOSETOWN	_IOW(f, 124, int)	/* set owner */
#define FIOGETOWN	_IOR(f, 123, int)	/* get owner */

/* socket i/o controls */
#define SIOCSHIWAT	_IOW(s,  0, int)		/* set high watermark */
#define SIOCGHIWAT	_IOR(s,  1, int)		/* get high watermark */
#define SIOCSLOWAT	_IOW(s,  2, int)		/* set low watermark */
#define SIOCGLOWAT	_IOR(s,  3, int)		/* get low watermark */
#define SIOCATMARK	_IOR(s,  7, int)		/* at oob mark? */
#define SIOCSPGRP	_IOW(s,  8, int)		/* set process group */
#define SIOCGPGRP	_IOR(s,  9, int)		/* get process group */

#define SIOCADDRT	_IOW(r, 10, struct rtentry)	/* add route */
#define SIOCDELRT	_IOW(r, 11, struct rtentry)	/* delete route */

#define SIOCSIFADDR	_IOW(i, 12, struct ifreq)	/* set ifnet address */
#define SIOCGIFADDR	_IOWR(i,13, struct ifreq)	/* get ifnet address */
#define SIOCSIFDSTADDR	_IOW(i, 14, struct ifreq)	/* set p-p address */
#define SIOCGIFDSTADDR	_IOWR(i,15, struct ifreq)	/* get p-p address */
#define SIOCSIFFLAGS	_IOW(i, 16, struct ifreq)	/* set ifnet flags */
#define SIOCGIFFLAGS	_IOWR(i,17, struct ifreq)	/* get ifnet flags */
#define SIOCGIFBRDADDR	_IOWR(i,18, struct ifreq)	/* get broadcast addr */
#define SIOCSIFBRDADDR	_IOW(i,19, struct ifreq)	/* set broadcast addr */
#define SIOCGIFCONF	_IOWR(i,20, struct ifconf)	/* get ifnet list */
#define SIOCGIFNETMASK	_IOWR(i,21, struct ifreq)	/* get net addr mask */
#define SIOCSIFNETMASK	_IOW(i,22, struct ifreq)	/* set net addr mask */
#define SIOCGIFMETRIC	_IOWR(i,23, struct ifreq)	/* get IF metric */
#define SIOCSIFMETRIC	_IOW(i,24, struct ifreq)	/* set IF metric */
#ifdef	mips
#define SIOCSIFMEM	_IOW(i, 25, struct ifreq)	/* set interface mem */
#define SIOCGIFMEM	_IOWR(i,26, struct ifreq)	/* get interface mem */
#define SIOCSIFMTU      _IOW(i, 27, struct ifreq)       /* set if_mtu */
#define SIOCGIFMTU      _IOWR(i,28, struct ifreq)       /* get if_mtu */
#define SIOCGIFSTATS	_IOWR(i, 29, struct ifreq)	/* get enp stats */
#endif	mips

#define SIOCSARP	_IOW(i, 30, struct arpreq)	/* set arp entry */
#define SIOCGARP	_IOWR(i,31, struct arpreq)	/* get arp entry */
#define SIOCDARP	_IOW(i, 32, struct arpreq)	/* delete arp entry */
#ifdef	mips
#define SIOCUPPER       _IOW(i, 40, struct ifreq)       /* attach upper layer */
#define SIOCLOWER       _IOW(i, 41, struct ifreq)       /* attach lower layer */

/* protocol i/o controls */
#define SIOCSNIT        _IOW(p,  0, struct nit_ioc)     /* set nit modes */
#define SIOCGNIT        _IOWR(p, 1, struct nit_ioc)     /* get nit modes */

#endif	mips


/* dialup interface ioctls */
#define SIOCSATIMEO	_IOWR(i,33, struct ifreq)  /* Set the Active timer */
#define SIOCGATIMEO	_IOWR(i,34, struct ifreq)  /* Get the Active timer */
#define SIOCSWTIMEO	_IOWR(i,35, struct ifreq)  /* Set the Wait timer */
#define SIOCGWTIMEO	_IOWR(i,36, struct ifreq)  /* Get the Wait timer */
#define SIOCCLEARQ	_IOWR(i,37, struct ifreq)  /* Clear the interface queue */
#define SIOCPREVENTPROTO _IOWR(i,38,struct ifreq)  /* prevent a protocol */
#define SIOCSSOFTFLAGS	_IOWR(i,39, struct ifreq)  /* Set the soft flags */
#define SIOCSSOFTTIMER	_IOWR(i,40, struct ifreq)  /* Set the soft timer */
#define SIOCFAILCALL	_IOWR(i,41, struct ifreq)  /* Mark a failed call */


#define SIOCCIFCNTRS _IOW(i, 128, struct ifreq) /* flush stat buffers */

#endif	_SYS_IOCTL_H_
