h18789
s 00018/00008/00234
d D 8.3 94/03/28 07:33:27 bostic 27 26
c break termios.h, ioctl.h up into filio.h, sockio.h, ttycom.h
c termios.h, ioccom.h and ioctl.h, a la SunOS
e
s 00004/00004/00238
d D 8.2 94/01/04 16:16:51 bostic 26 25
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00002/00002/00240
d D 8.1 93/06/02 19:55:48 bostic 25 24
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00013/00229
d D 7.24 92/03/07 11:08:39 bostic 24 23
c fix C library prototypes
e
s 00001/00001/00241
d D 7.23 91/07/29 14:03:03 marc 23 22
c oops.  someone ifdef'ed NCCS out if POSIX_SOURCE is defined.
e
s 00008/00000/00234
d D 7.22 91/05/07 20:12:02 marc 22 21
c add TCI* defines for POSIX conformance
e
s 00026/00000/00208
d D 7.21 91/02/22 12:07:40 donn 21 20
c Prototype declarations.
e
s 00003/00003/00205
d D 7.20 91/02/05 17:04:17 bostic 20 19
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00000/00002/00208
d D 7.19 90/12/16 10:59:33 karels 19 18
c posix has HUPCL
e
s 00001/00011/00209
d D 7.18 90/06/28 22:01:09 bostic 18 17
c new copyright notice
e
s 00001/00001/00219
d D 7.17 90/06/28 15:46:28 karels 17 16
c remove second erase character for correctness
e
s 00003/00000/00217
d D 7.16 90/06/26 14:29:24 marc 16 15
c put back TCSASOFT - flag to inhibit updating cflag
e
s 00001/00002/00216
d D 7.15 90/06/20 18:43:08 marc 15 14
c secondary erase character for good PR
e
s 00003/00003/00215
d D 7.14 90/06/20 18:22:59 marc 14 13
c VINFO -> VSTATUS
e
s 00003/00002/00215
d D 7.13 90/06/19 16:45:55 marc 13 12
c size of cc array is NCCS
e
s 00000/00004/00217
d D 7.12 90/06/14 13:28:38 marc 12 11
c remove alternate names for flags
e
s 00002/00003/00219
d D 7.11 90/06/14 13:23:32 marc 11 10
c VFLUSHO -> VDISCARD
e
s 00002/00001/00220
d D 7.10 90/06/07 16:41:22 marc 10 9
c damn.  TCSAFLUSH was misspelled as TCSADFLUSH and got propagated
e
s 00010/00009/00211
d D 7.9 90/05/18 14:17:15 marc 9 8
c line mode telnet mods
e
s 00001/00002/00219
d D 7.8 90/05/16 15:54:50 marc 8 7
c remove NOHANG - not to be done in kernel
e
s 00043/00009/00178
d D 7.7 90/04/04 22:15:23 karels 7 6
c ifdef for _POSIX_SOURCE; add NOKERNINFO, sep. RTS/CTS flow;
c move MDMBUF to cflags
e
s 00048/00027/00139
d D 7.6 89/11/20 18:13:28 marc 6 5
c more posix
e
s 00004/00004/00162
d D 7.5 89/08/13 18:20:01 marc 5 4
c move IEXTEN to the lflag
e
s 00000/00001/00166
d D 7.4 88/12/12 14:55:18 marc 4 3
c remove VQUOTE
e
s 00014/00003/00153
d D 7.3 88/11/15 12:50:02 bostic 3 2
c Berkeley specific copyright
e
s 00031/00023/00125
d D 7.2 88/10/18 15:23:58 marc 2 1
c new terminal driver
e
s 00148/00000/00000
d D 7.1 88/03/27 19:27:18 marc 1 0
c date and time created 88/03/27 19:27:18 by marc
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
D 7
 * Copyright (c) 1988 The Regents of the University of California.
E 7
I 7
D 25
 * Copyright (c) 1988, 1989 The Regents of the University of California.
E 7
 * All rights reserved.
E 25
I 25
D 27
 * Copyright (c) 1988, 1989, 1993
E 27
I 27
 * Copyright (c) 1988, 1989, 1993, 1994
E 27
 *	The Regents of the University of California.  All rights reserved.
E 25
 *
D 18
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 18
I 18
 * %sccs.include.redist.c%
E 18
E 3
 *
 *	%W% (Berkeley) %G%
 */

D 27
/*
D 2
 *  posix termios structure
E 2
I 2
 *  termios structure
E 2
 */
E 27
D 20
#ifndef _TERMIOS_
#define _TERMIOS_
E 20
I 20
D 26
#ifndef _TERMIOS_H_
#define _TERMIOS_H_
E 26
I 26
#ifndef _SYS_TERMIOS_H_
#define _SYS_TERMIOS_H_
E 26
E 20

D 6
#ifdef KERNEL
#include "ioctl.h"
#else
#include <sys/ioctl.h>
#endif


E 6
/* 
 * Special Control Characters 
 *
 * Index into c_cc[] character array.
 *
 *	Name	     Subscript	Enabled by 
 */
#define	VEOF		0	/* ICANON */
#define	VEOL		1	/* ICANON */
I 7
#ifndef _POSIX_SOURCE
E 7
#define	VEOL2		2	/* ICANON */
I 7
D 9
#endif  /*_POSIX_SOURCE */
E 9
I 9
#endif
E 9
E 7
#define	VERASE		3	/* ICANON */
I 7
#ifndef _POSIX_SOURCE
E 7
I 2
D 6
#define	VERASE2		18	/* ICANON */
E 6
E 2
#define VWERASE 	4	/* ICANON */
I 7
D 9
#endif  /*_POSIX_SOURCE */
E 9
I 9
#endif 
E 9
E 7
#define VKILL		5	/* ICANON */
I 7
#ifndef _POSIX_SOURCE
E 7
#define	VREPRINT 	6	/* ICANON */
I 7
D 9
#endif  /*_POSIX_SOURCE */
E 9
I 9
#endif
E 9
E 7
I 6
/*			7	   spare 1 */
E 6
D 4
#define VQUOTE		7	/* ICANON */
E 4
#define VINTR		8	/* ISIG */
#define VQUIT		9	/* ISIG */
#define VSUSP		10	/* ISIG */
I 7
#ifndef _POSIX_SOURCE
E 7
#define VDSUSP		11	/* ISIG */
I 7
D 9
#endif  /*_POSIX_SOURCE */
E 9
I 9
#endif
E 9
E 7
#define VSTART		12	/* IXON, IXOFF */
#define VSTOP		13	/* IXON, IXOFF */
I 7
#ifndef _POSIX_SOURCE
E 7
#define	VLNEXT		14	/* IEXTEN */
D 11
#define	VFLUSHO		15	/* IEXTEN */
#define	VFLUSH		VFLUSHO	/* for sun */
E 11
I 11
#define	VDISCARD	15	/* IEXTEN */
E 11
I 7
D 9
#endif  /*_POSIX_SOURCE */
E 9
I 9
#endif
E 9
E 7
#define VMIN		16	/* !ICANON */
#define VTIME		17	/* !ICANON */
I 7
#ifndef _POSIX_SOURCE
E 7
I 6
D 8
#define VINFO		18	/* ISIG */
E 8
I 8
D 14
#define VINFO		18	/* ICANON */
E 14
I 14
#define VSTATUS		18	/* ICANON */
E 14
E 8
D 13
/*			19	   spare 2 */
#define	NCC		20
E 13
I 13
D 15
/*			19	   spare */
E 15
I 15
D 17
#define VERASE2		19	/* ICANON */
E 17
I 17
/*			19	   spare 2 */
E 17
E 15
D 23
#define	NCCS		20
E 23
D 15
#define	NCC		NCCS
E 15
E 13
I 7
D 9
#endif  /*_POSIX_SOURCE */
E 9
I 9
#endif
I 23
#define	NCCS		20
E 23
E 9
E 7
E 6

D 6
#define	NCC		20	/* two spares */

E 6
D 2
#define POSIX_V_DISABLE	((unsigned char)'\377')
#define _POSIX_V_DISABLE POSIX_V_DISABLE
E 2
I 2
#define _POSIX_VDISABLE	((unsigned char)'\377')
E 2

I 6
#ifndef _POSIX_SOURCE
#define CCEQ(val, c)	(c == val ? val != _POSIX_VDISABLE : 0)
#endif

E 6
/*
 * Input flags - software input processing
 */
#define	IGNBRK		0x00000001	/* ignore BREAK condition */
#define	BRKINT		0x00000002	/* map BREAK to SIGINTR */
D 2
#define	IGNPAR		0x00000004	/* ignore (throw out) parity errors */
E 2
I 2
#define	IGNPAR		0x00000004	/* ignore (discard) parity errors */
E 2
#define	PARMRK		0x00000008	/* mark parity and framing errors */
D 7
#define	INPCK		0x00000010	/* disable checking of parity errors */
E 7
I 7
#define	INPCK		0x00000010	/* enable checking of parity errors */
E 7
#define	ISTRIP		0x00000020	/* strip 8th bit off chars */
#define	INLCR		0x00000040	/* map NL into CR */
#define	IGNCR		0x00000080	/* ignore CR */
#define	ICRNL		0x00000100	/* map CR to NL (ala CRMOD) */
#define	IXON		0x00000200	/* enable output flow control */
D 7
#define	IFLOW		IXON		/* "" */
E 7
#define	IXOFF		0x00000400	/* enable input flow control */
D 7
#define	ITANDEM		IXOFF		/* "" */
E 7
I 7
#ifndef _POSIX_SOURCE
D 12
#define	IFLOW		IXON		/* enable output flow control */
#define	ITANDEM		IXOFF		/* enable input flow control */
E 12
E 7
#define	IXANY		0x00000800	/* any char will restart after stop */
D 5
#define	IEXTEN		0x00001000	/* enable FLUSHO and LNEXT */
E 5
#define IMAXBEL		0x00002000	/* ring bell on input queue full */
I 7
#endif  /*_POSIX_SOURCE */
E 7

/*
 * Output flags - software output processing
 */
D 2
#define	OPOST		0x00000001	/* enable output processing */
E 2
I 2
#define	OPOST		0x00000001	/* enable following output processing */
I 7
#ifndef _POSIX_SOURCE
E 7
E 2
#define ONLCR		0x00000002	/* map NL to CR-NL (ala CRMOD) */
I 2
D 12
#define ONLCRNL		ONLCR
E 12
E 2
#define OXTABS		0x00000004	/* expand tabs to spaces */
I 2
#define ONOEOT		0x00000008	/* discard EOT's (^D) on output) */
I 7
#endif  /*_POSIX_SOURCE */
E 7
E 2

/*
 * Control flags - hardware control of terminal
 */
I 7
#ifndef _POSIX_SOURCE
E 7
I 6
#define	CIGNORE		0x00000001	/* ignore control flags */
I 7
D 9
#endif  /*_POSIX_SOURCE */
E 9
I 9
#endif
E 9
E 7
E 6
#define CSIZE		0x00000300	/* character size mask */
D 5
#define     CS5		    0x00000000	    /* 5 bits - pseudo */
E 5
I 5
#define     CS5		    0x00000000	    /* 5 bits (pseudo) */
E 5
#define     CS6		    0x00000100	    /* 6 bits */
#define     CS7		    0x00000200	    /* 7 bits */
#define     CS8		    0x00000300	    /* 8 bits */
#define CSTOPB		0x00000400	/* send 2 stop bits */
#define CREAD		0x00000800	/* enable receiver */
#define PARENB		0x00001000	/* parity enable */
#define PARODD		0x00002000	/* odd parity, else even */
I 7
D 19
#ifndef _POSIX_SOURCE
E 19
E 7
#define HUPCL		0x00004000	/* hang up on last close */
I 7
D 9
#endif  /*_POSIX_SOURCE */
E 9
I 9
D 19
#endif
E 19
E 9
E 7
D 2
#define CLOCAL		0x00008000	/* ignore mode status lines */
E 2
I 2
#define CLOCAL		0x00008000	/* ignore modem status lines */
E 2
D 7
#define CRTSCTS		0x00010000	/* RTS/CTS flow control */
E 7
I 7
#ifndef _POSIX_SOURCE
#define CCTS_OFLOW	0x00010000	/* CTS flow control of output */
#define CRTSCTS		CCTS_OFLOW	/* ??? */
#define CRTS_IFLOW	0x00020000	/* RTS flow control of input */
#define	MDMBUF		0x00100000	/* flow control output via Carrier */
D 9
#endif  /*_POSIX_SOURCE */
E 9
I 9
#endif
E 9
E 7


/* 
 * "Local" flags - dumping ground for other state
 *
D 2
 *  Note presence of ISIG and ICANON.  Its not *our* fault.
E 2
I 2
 * Warning: some flags in this structure begin with
 * the letter "I" and look like they belong in the
D 5
 * input flag.  Isn't history fun.
E 5
I 5
 * input flag.
E 5
E 2
 */

I 7
#ifndef _POSIX_SOURCE
E 7
D 2
#define ECHO		0x00000001	/* enable echoing */
E 2
I 2
#define	ECHOKE		0x00000001	/* visual erase for line kill */
I 7
#endif  /*_POSIX_SOURCE */
E 7
E 2
#define	ECHOE		0x00000002	/* visually erase chars */
#define	ECHOK		0x00000004	/* echo NL after line kill */
I 6
#define ECHO		0x00000008	/* enable echoing */
E 6
D 2
#define	ECHOKE		0x00000008	/* visual erase for line kill */
E 2
#define	ECHONL		0x00000010	/* echo NL even if ECHO is off */
I 7
#ifndef _POSIX_SOURCE
E 7
#define	ECHOPRT		0x00000020	/* visual erase mode for hardcopy */
#define ECHOCTL  	0x00000040	/* echo control chars as ^(Char) */
I 7
#endif  /*_POSIX_SOURCE */
E 7
#define	ISIG		0x00000080	/* enable signals INTR, QUIT, [D]SUSP */
#define	ICANON		0x00000100	/* canonicalize input lines */
I 7
#ifndef _POSIX_SOURCE
E 7
D 2
#define	NOFLSH		0x00000200	/* don't flush after interrupt */
#define TOSTOP		0x00000400	/* stop background jobs from output */
#define	MDMBUF		0x00000800	/* flow control output via Carrier */
#define	NOHANG		0x00001000	/* XXX this should go away */
#define FLUSHO		0x00002000	/* output being flushed (state) */
#define PENDIN		0x00004000	/* retype pending input (state) */
E 2
I 2
#define ALTWERASE	0x00000200	/* use alternate WERASE algorithm */
I 7
#endif  /*_POSIX_SOURCE */
E 7
I 5
D 11
#define	IEXTEN		0x00000400	/* enable FLUSHO and LNEXT */
E 11
I 11
#define	IEXTEN		0x00000400	/* enable DISCARD and LNEXT */
E 11
I 9
#define EXTPROC         0x00000800      /* external processing */
E 9
E 5
D 6
#ifdef notdef	/* XXX already defined in ioctl.h */
#define ECHO		0x00000008	/* enable echoing */
E 6
D 7
#define	MDMBUF		0x00100000	/* flow control output via Carrier */
E 7
#define TOSTOP		0x00400000	/* stop background jobs from output */
I 7
#ifndef _POSIX_SOURCE
E 7
#define FLUSHO		0x00800000	/* output being flushed (state) */
D 8
#define	NOHANG		0x01000000	/* XXX this should go away */
E 8
D 7
#define PENDIN		0x20000000	/* retype pending input (state) */
E 7
I 7
D 14
#define	NOKERNINFO	0x02000000	/* no kernel output from VINFO */
E 14
I 14
#define	NOKERNINFO	0x02000000	/* no kernel output from VSTATUS */
E 14
#define PENDIN		0x20000000	/* XXX retype pending input (state) */
#endif  /*_POSIX_SOURCE */
E 7
#define	NOFLSH		0x80000000	/* don't flush after interrupt */
D 6
#endif /*notdef*/
E 6
E 2

I 6
typedef unsigned long	tcflag_t;
typedef unsigned char	cc_t;
I 21
typedef long		speed_t;
E 21

E 6
struct termios {
D 6
	unsigned long	c_iflag;	/* input flags */
	unsigned long	c_oflag;	/* output flags */
	unsigned long	c_cflag;	/* control flags */
	unsigned long	c_lflag;	/* local flags */
	unsigned char	c_cc[NCC];	/* control chars */
E 6
I 6
	tcflag_t	c_iflag;	/* input flags */
	tcflag_t	c_oflag;	/* output flags */
	tcflag_t	c_cflag;	/* control flags */
	tcflag_t	c_lflag;	/* local flags */
D 14
	cc_t		c_cc[NCC];	/* control chars */
E 14
I 14
	cc_t		c_cc[NCCS];	/* control chars */
E 14
E 6
	long		c_ispeed;	/* input speed */
	long		c_ospeed;	/* output speed */
};

/* 
D 2
 * Flags to tcsetattr(), for setting the termios structure.
 * 
 * If TCSASOFT is or'ed in with one of the first three, then
 * only the software processing flags in the termios structure
 * are set.  That is, the settings of the cflag and speeds
 * are ignored.
E 2
I 2
 * Commands passed to tcsetattr() for setting the termios structure.
E 2
 */
#define	TCSANOW		0		/* make change immediate */
#define	TCSADRAIN	1		/* drain output, then change */
D 10
#define	TCSADFLUSH	2		/* drain output, flush input */
E 10
I 10
#define	TCSAFLUSH	2		/* drain output, flush input */
I 16
#ifndef _POSIX_SOURCE
#define TCSASOFT	0x10		/* flag - don't alter h.w. state */
#endif
E 16
D 12
#define	TCSADFLUSH	TCSAFLUSH	/* XXX (was a typo, to be removed) */
E 12
E 10
I 6

E 6
I 2
/*
D 6
 * TCSASOFT is a flag which can be or'ed in with a command.
 * If set, only the software processing flags in the termios 
 * structure are altered.  That is, the settings of the cflag and 
 * speeds are ignored.
E 6
I 6
 * Standard speeds
E 6
 */
E 2
D 6
#define TCSASOFT	0x80000000	/* but ignore hardware settings */

E 6
I 6
#define B0	0
#define B50	50
#define B75	75
#define B110	110
#define B134	134
#define B150	150
#define B200	200
#define B300	300
#define B600	600
#define B1200	1200
#define	B1800	1800
#define B2400	2400
#define B4800	4800
#define B9600	9600
#define B19200	19200
#define B38400	38400
I 7
#ifndef _POSIX_SOURCE
I 27
#define B7200	7200
#define B14400	14400
#define B28800	28800
#define B57600	57600
#define B76800	76800
#define B115200	115200
#define B230400	230400
E 27
E 7
#define EXTA	19200
#define EXTB	38400
I 7
D 24
#endif  /*_POSIX_SOURCE */
E 24
I 24
#endif  /* !_POSIX_SOURCE */
E 24
I 21

#ifndef KERNEL

I 24
#define	TCIFLUSH	1
#define	TCOFLUSH	2
#define TCIOFLUSH	3
#define	TCOOFF		1
#define	TCOON		2
#define TCIOFF		3
#define TCION		4

E 24
#include <sys/cdefs.h>

__BEGIN_DECLS
speed_t	cfgetispeed __P((const struct termios *));
speed_t	cfgetospeed __P((const struct termios *));
int	cfsetispeed __P((struct termios *, speed_t));
int	cfsetospeed __P((struct termios *, speed_t));
I 24
int	tcgetattr __P((int, struct termios *));
int	tcsetattr __P((int, int, const struct termios *));
E 24
int	tcdrain __P((int));
int	tcflow __P((int, int));
int	tcflush __P((int, int));
D 24
int	tcgetattr __P((int, struct termios *));
E 24
int	tcsendbreak __P((int, int));
D 24
int	tcsetattr __P((int, int, const struct termios *));
E 24

I 22
D 24
#define	TCIFLUSH	1
#define	TCOFLUSH	2
#define TCIOFLUSH	3
#define	TCOOFF		1
#define	TCOON		2
#define TCIOFF		3
#define TCION		4

E 24
E 22
#ifndef _POSIX_SOURCE
void	cfmakeraw __P((struct termios *));
D 24
void	cfsetspeed __P((struct termios *, speed_t));
#endif /* !POSIX */
E 24
I 24
int	cfsetspeed __P((struct termios *, speed_t));
#endif /* !_POSIX_SOURCE */
E 24
__END_DECLS

#endif /* !KERNEL */

I 27
#ifndef _POSIX_SOURCE

E 27
E 21
E 7
E 6
/*
I 27
 * Include tty ioctl's that aren't just for backwards compatibility
 * with the old tty driver.  These ioctl definitions were previously
 * in <sys/ioctl.h>.
 */
#include <sys/ttycom.h>
#endif

/*
E 27
D 2
 * Is c equal to control character val?  XXX - should reverse val and c
E 2
I 2
D 6
 * Is c equal to control character val?
E 6
I 6
 * END OF PROTECTED INCLUDE.
E 6
E 2
 */
D 2
#define CCEQ(val, c)	(c == val ? val != POSIX_V_DISABLE : 0)
E 2
I 2
D 5
#define CCEQ(val, c)	(c == val ? val != _POSIX_VDISABLE : 0)
E 5
I 5
D 6
#define CCEQ(val, c)	((c) == (val) ? (val) != _POSIX_VDISABLE : 0)
E 6
I 6
D 20
#endif /* _TERMIOS_ */
E 20
I 20
D 26
#endif /* !_TERMIOS_H_ */
E 26
I 26
#endif /* !_SYS_TERMIOS_H_ */
E 26
E 20
E 6
E 5
E 2

D 6
#endif _TERMIOS_
E 6
I 6
#ifndef _POSIX_SOURCE
D 27
#ifdef KERNEL
#include "ttydefaults.h"
#else
E 27
#include <sys/ttydefaults.h>
D 27
#endif
E 27
D 7
#endif 

E 7
I 7
D 26
#endif  /*_POSIX_SOURCE */
E 26
I 26
#endif
E 26
E 7
E 6
E 1
