h13240
s 00002/00002/00023
d D 8.1 93/06/06 16:48:10 bostic 9 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00025
d R 8.1 93/06/06 16:47:58 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00013/00022
d D 4.2 91/04/26 15:55:55 bostic 7 6
c new copyright; att/bsd/shared
e
s 00000/00000/00035
d D 4.1 88/12/04 15:13:16 minshall 6 5
c Release 4.1
e
s 00010/00005/00025
d D 3.3 88/06/29 20:11:59 bostic 5 4
c install approved copyright notice
e
s 00014/00002/00016
d D 3.2 88/03/28 12:18:28 bostic 4 3
c add Berkeley specific headers
e
s 00000/00000/00018
d D 3.1 87/08/11 10:21:02 minshall 3 2
c New version numbering.
e
s 00002/00000/00016
d D 1.2 87/07/16 16:03:03 minshall 2 1
c Add sccs, copyrights.
e
s 00016/00000/00000
d D 1.1 87/06/19 09:34:23 minshall 1 0
c date and time created 87/06/19 09:34:23 by minshall
e
u
U
t
T
I 1
D 7
/*
I 4
 * Copyright (c) 1988 Regents of the University of California.
E 7
I 7
/*-
D 9
 * Copyright (c) 1988 The Regents of the University of California.
E 7
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 7
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 5
I 5
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 5
 *
 *	%W% (Berkeley) %G%
 */

/*
E 4
 * Where the fields fall on the formatted screen used by tncomp, tnrecv,
 * and tnsend.
I 2
D 4
 *
 * %W% (Berkeley) %G%
E 4
E 2
 */

#define	SEND_SEQUENCE		1
#define	SEND_SEQUENCE_LENGTH	23

#define	ACK_SEQUENCE	(SEND_SEQUENCE+SEND_SEQUENCE_LENGTH+1)
#define	ACK_SEQUENCE_LENGTH	22

#define	CHECKSUM	(ACK_SEQUENCE+ACK_SEQUENCE_LENGTH+1)
#define	CHECKSUM_LENGTH		32

#define	DATA		(CHECKSUM+CHECKSUM_LENGTH+1)
#define	DATA_LENGTH		((80*22)+79)
E 1
