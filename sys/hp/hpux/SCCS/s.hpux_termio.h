h24346
s 00002/00002/00162
d D 8.1 93/06/10 21:24:50 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00027/00000/00137
d D 7.4 92/08/03 14:13:11 hibler 4 3
c termios support
e
s 00001/00001/00136
d D 7.3 90/10/24 15:09:43 mckusick 3 2
c update Utah source identifier
e
s 00078/00078/00059
d D 7.2 90/06/27 18:44:24 hibler 2 1
c convert numbers to hex for easy comparison with termios.h
e
s 00137/00000/00000
d D 7.1 90/05/08 22:18:37 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 3
 * from: Utah $Hdr: hpux.h 1.15 89/09/25$
E 3
I 3
 * from: Utah $Hdr: hpux_termio.h 1.1 90/07/09$
E 3
 *
 *	%W% (Berkeley) %G%
 */

/* HP-UX termio stuff */

#define	HPUXNCC	8

/* control characters */
#define	HPUXVINTR	0
#define	HPUXVQUIT	1
#define	HPUXVERASE	2
#define	HPUXVKILL	3
#define	HPUXVEOF	4
#define	HPUXVEOL	5
#define	HPUXVMIN	4
#define	HPUXVTIME	5
I 4
#define HPUXVEOL2	6
#define HPUXVSWTCH	7
E 4

/* input modes */
D 2
#define	TIO_IGNBRK	0000001
#define	TIO_BRKINT	0000002
#define	TIO_IGNPAR	0000004
#define	TIO_PARMRK	0000010
#define	TIO_INPCK	0000020
#define	TIO_ISTRIP	0000040
#define	TIO_INLCR	0000100
#define	TIO_IGNCR	0000200
#define	TIO_ICRNL	0000400
#define	TIO_IUCLC	0001000
#define	TIO_IXON	0002000
#define	TIO_IXANY	0004000
#define	TIO_IXOFF	0010000
#define	TIO_IENQAK	0020000
E 2
I 2
#define	TIO_IGNBRK	0x00000001	/* 0000001 */
#define	TIO_BRKINT	0x00000002	/* 0000002 */
#define	TIO_IGNPAR	0x00000004	/* 0000004 */
#define	TIO_PARMRK	0x00000008	/* 0000010 */
#define	TIO_INPCK	0x00000010	/* 0000020 */
#define	TIO_ISTRIP	0x00000020	/* 0000040 */
#define	TIO_INLCR	0x00000040	/* 0000100 */
#define	TIO_IGNCR	0x00000080	/* 0000200 */
#define	TIO_ICRNL	0x00000100	/* 0000400 */
#define	TIO_IUCLC	0x00000200	/* 0001000 */
#define	TIO_IXON	0x00000400	/* 0002000 */
#define	TIO_IXANY	0x00000800	/* 0004000 */
#define	TIO_IXOFF	0x00001000	/* 0010000 */
#define	TIO_IENQAK	0x00002000	/* 0020000 */
E 2

/* output modes */
D 2
#define	TIO_OPOST	0000001
#define	TIO_OLCUC	0000002
#define	TIO_ONLCR	0000004
#define	TIO_OCRNL	0000010
#define	TIO_ONOCR	0000020
#define	TIO_ONLRET	0000040
#define	TIO_OFILL	0000100
#define	TIO_OFDEL	0000200
#define	TIO_NLDLY	0000400
E 2
I 2
#define	TIO_OPOST	0x00000001	/* 0000001 */
#define	TIO_OLCUC	0x00000002	/* 0000002 */
#define	TIO_ONLCR	0x00000004	/* 0000004 */
#define	TIO_OCRNL	0x00000008	/* 0000010 */
#define	TIO_ONOCR	0x00000010	/* 0000020 */
#define	TIO_ONLRET	0x00000020	/* 0000040 */
#define	TIO_OFILL	0x00000040	/* 0000100 */
#define	TIO_OFDEL	0x00000080	/* 0000200 */
#define	TIO_NLDLY	0x00000100	/* 0000400 */
E 2
#define	TIO_NL0		0
D 2
#define	TIO_NL1		0000400
#define	TIO_CRDLY	0003000
E 2
I 2
#define	TIO_NL1		0x00000100	/* 0000400 */
#define	TIO_CRDLY	0x00000600	/* 0003000 */
E 2
#define	TIO_CR0		0
D 2
#define	TIO_CR1		0001000
#define	TIO_CR2		0002000
#define	TIO_CR3		0003000
#define	TIO_TABDLY	0014000
E 2
I 2
#define	TIO_CR1		0x00000200	/* 0001000 */
#define	TIO_CR2		0x00000400	/* 0002000 */
#define	TIO_CR3		0x00000600	/* 0003000 */
#define	TIO_TABDLY	0x00001800	/* 0014000 */
E 2
#define	TIO_TAB0	0
D 2
#define	TIO_TAB1	0004000
#define	TIO_TAB2	0010000
#define	TIO_TAB3	0014000
#define	TIO_BSDLY	0020000
E 2
I 2
#define	TIO_TAB1	0x00000800	/* 0004000 */
#define	TIO_TAB2	0x00001000	/* 0010000 */
#define	TIO_TAB3	0x00001800	/* 0014000 */
#define	TIO_BSDLY	0x00002000	/* 0020000 */
E 2
#define	TIO_BS0		0
D 2
#define	TIO_BS1		0020000
#define	TIO_VTDLY	0040000
E 2
I 2
#define	TIO_BS1		0x00002000	/* 0020000 */
#define	TIO_VTDLY	0x00004000	/* 0040000 */
E 2
#define	TIO_VT0		0
D 2
#define	TIO_VT1		0040000
#define	TIO_FFDLY	0100000
E 2
I 2
#define	TIO_VT1		0x00004000	/* 0040000 */
#define	TIO_FFDLY	0x00008000	/* 0100000 */
E 2
#define	TIO_FF0		0
D 2
#define	TIO_FF1		0100000
E 2
I 2
#define	TIO_FF1		0x00008000	/* 0100000 */
E 2

/* control modes */
D 2
#define	TIO_CBAUD	0000037
E 2
I 2
#define	TIO_CBAUD	0x0000001f	/* 0000037 */
E 2
#define	TIO_B0		0
D 2
#define	TIO_B50		0000001
#define	TIO_B75		0000002
#define	TIO_B110	0000003
#define	TIO_B134	0000004
#define	TIO_B150	0000005
#define	TIO_B200	0000006
#define	TIO_B300	0000007
#define	TIO_B600	0000010
#define	TIO_B900	0000011
#define	TIO_B1200	0000012
#define	TIO_B1800	0000013
#define	TIO_B2400	0000014
#define	TIO_B3600	0000015
#define	TIO_B4800	0000016
#define	TIO_B7200	0000017
#define	TIO_B9600	0000020
#define	TIO_B19200	0000021
#define	TIO_B38400	0000022
#define	TIO_EXTA	0000036
#define	TIO_EXTB	0000037
#define	TIO_CSIZE	0000140
E 2
I 2
#define	TIO_B50		0x00000001	/* 0000001 */
#define	TIO_B75		0x00000002	/* 0000002 */
#define	TIO_B110	0x00000003	/* 0000003 */
#define	TIO_B134	0x00000004	/* 0000004 */
#define	TIO_B150	0x00000005	/* 0000005 */
#define	TIO_B200	0x00000006	/* 0000006 */
#define	TIO_B300	0x00000007	/* 0000007 */
#define	TIO_B600	0x00000008	/* 0000010 */
#define	TIO_B900	0x00000009	/* 0000011 */
#define	TIO_B1200	0x0000000a	/* 0000012 */
#define	TIO_B1800	0x0000000b	/* 0000013 */
#define	TIO_B2400	0x0000000c	/* 0000014 */
#define	TIO_B3600	0x0000000d	/* 0000015 */
#define	TIO_B4800	0x0000000e	/* 0000016 */
#define	TIO_B7200	0x0000000f	/* 0000017 */
#define	TIO_B9600	0x00000010	/* 0000020 */
#define	TIO_B19200	0x00000011	/* 0000021 */
#define	TIO_B38400	0x00000012	/* 0000022 */
#define	TIO_EXTA	0x0000001e	/* 0000036 */
#define	TIO_EXTB	0x0000001f	/* 0000037 */
#define	TIO_CSIZE	0x00000060	/* 0000140 */
E 2
#define	TIO_CS5		0
D 2
#define	TIO_CS6		0000040
#define	TIO_CS7		0000100
#define	TIO_CS8		0000140
#define	TIO_CSTOPB	0000200
#define	TIO_CREAD	0000400
#define	TIO_PARENB	0001000
#define	TIO_PARODD	0002000
#define	TIO_HUPCL	0004000
#define	TIO_CLOCAL	0010000
#define TIO_CRTS   	0020000 /* Obsolete */
E 2
I 2
#define	TIO_CS6		0x00000020	/* 0000040 */
#define	TIO_CS7		0x00000040	/* 0000100 */
#define	TIO_CS8		0x00000060	/* 0000140 */
#define	TIO_CSTOPB	0x00000080	/* 0000200 */
#define	TIO_CREAD	0x00000100	/* 0000400 */
#define	TIO_PARENB	0x00000200	/* 0001000 */
#define	TIO_PARODD	0x00000400	/* 0002000 */
#define	TIO_HUPCL	0x00000800	/* 0004000 */
#define	TIO_CLOCAL	0x00001000	/* 0010000 */
#define TIO_CRTS   	0x00002000	/* 0020000 */ /* Obsolete */
E 2

/* line discipline 0 modes */
D 2
#define	TIO_ISIG	0000001
#define	TIO_ICANON	0000002
#define	TIO_XCASE	0000004
#define	TIO_ECHO	0000010
#define	TIO_ECHOE	0000020
#define	TIO_ECHOK	0000040
#define	TIO_ECHONL	0000100
#define	TIO_NOFLSH	0000200
E 2
I 2
#define	TIO_ISIG	0x00000001	/* 0000001 */
#define	TIO_ICANON	0x00000002	/* 0000002 */
#define	TIO_XCASE	0x00000004	/* 0000004 */
#define	TIO_ECHO	0x00000008	/* 0000010 */
#define	TIO_ECHOE	0x00000010	/* 0000020 */
#define	TIO_ECHOK	0x00000020	/* 0000040 */
#define	TIO_ECHONL	0x00000040	/* 0000100 */
#define	TIO_NOFLSH	0x00000080	/* 0000200 */
E 2

struct hpuxtermio {
	u_short	c_iflag;	/* input modes */
	u_short	c_oflag;	/* output modes */
	u_short	c_cflag;	/* control modes */
	u_short	c_lflag;	/* line discipline modes */
	char    c_line;		/* line discipline */
	u_char	c_cc[HPUXNCC];	/* control chars */
};

#define	HPUXTCGETA	_IOR('T', 1, struct hpuxtermio)
#define	HPUXTCSETA	_IOW('T', 2, struct hpuxtermio)
#define	HPUXTCSETAW	_IOW('T', 3, struct hpuxtermio)
#define	HPUXTCSETAF	_IOW('T', 4, struct hpuxtermio)
I 4

/* HP-UX termios stuff */

#define	HPUXNCCS	16

/* control characters */
#define	HPUXVMINS	11	/* different than termio */
#define	HPUXVTIMES	12	/* different than termio */
#define	HPUXVSUSP	13
#define	HPUXVSTART	14
#define	HPUXVSTOP	15

struct hpuxtermios {
	u_int	c_iflag;	/* input modes */
	u_int	c_oflag;	/* output modes */
	u_int	c_cflag;	/* control modes */
	u_int	c_lflag;	/* line discipline modes */
	u_int	c_reserved;	/* future use */
	u_char	c_cc[HPUXNCCS];	/* control chars */
};

#define	HPUXTCGETATTR	_IOR('T', 16, struct hpuxtermios)
#define	HPUXTCSETATTR	_IOW('T', 17, struct hpuxtermios)
#define	HPUXTCSETATTRD	_IOW('T', 18, struct hpuxtermios)
#define	HPUXTCSETATTRF	_IOW('T', 19, struct hpuxtermios)
E 4
E 1
