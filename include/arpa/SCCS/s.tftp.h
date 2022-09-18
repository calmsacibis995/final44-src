h38504
s 00002/00002/00052
d D 8.1 93/06/02 20:01:41 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00049
d D 5.4 91/04/03 16:07:01 bostic 6 5
c protect all user-level include files against reinclusion
e
s 00001/00011/00048
d D 5.3 90/06/01 14:02:37 bostic 5 4
c new copyright notice
e
s 00013/00002/00046
d D 5.2 88/06/27 16:37:46 bostic 4 3
c install approved copyright notice
e
s 00007/00001/00041
d D 5.1 85/05/30 09:47:33 dist 3 2
c Add copyright
e
s 00000/00002/00042
d D 4.2 83/06/11 17:53:34 sam 2 1
c timeouts not part of protocol
e
s 00044/00000/00000
d D 4.1 82/08/16 22:20:28 sam 1 0
c date and time created 82/08/16 22:20:28 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*
D 7
 * Copyright (c) 1983 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
 *
 *	%W% (Berkeley) %G%
 */
E 3

I 6
#ifndef _TFTP_H_
#define	_TFTP_H_

E 6
/*
 * Trivial File Transfer Protocol (IEN-133)
 */
#define	SEGSIZE		512		/* data segment size */
D 2
#define	TIMEOUT		5		/* retransmits every 5 seconds */
#define	MAXTIMEOUT	(5*TIMEOUT)	/* abort if no success by then */
E 2

/*
 * Packet types.
 */
#define	RRQ	01			/* read request */
#define	WRQ	02			/* write request */
#define	DATA	03			/* data packet */
#define	ACK	04			/* acknowledgement */
#define	ERROR	05			/* error code */

struct	tftphdr {
	short	th_opcode;		/* packet type */
	union {
		short	tu_block;	/* block # */
		short	tu_code;	/* error code */
		char	tu_stuff[1];	/* request packet stuff */
	} th_u;
	char	th_data[1];		/* data or error string */
};

#define	th_block	th_u.tu_block
#define	th_code		th_u.tu_code
#define	th_stuff	th_u.tu_stuff
#define	th_msg		th_data

/*
 * Error codes.
 */
#define	EUNDEF		0		/* not defined */
#define	ENOTFOUND	1		/* file not found */
#define	EACCESS		2		/* access violation */
#define	ENOSPACE	3		/* disk full or allocation exceeded */
#define	EBADOP		4		/* illegal TFTP operation */
#define	EBADID		5		/* unknown transfer ID */
#define	EEXISTS		6		/* file already exists */
#define	ENOUSER		7		/* no such user */
I 6

#endif /* !_TFTP_H_ */
E 6
E 1
