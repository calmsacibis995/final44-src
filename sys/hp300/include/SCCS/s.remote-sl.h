h34062
s 00002/00002/00030
d D 8.1 93/06/10 21:45:17 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00018/00020
d D 7.4 92/07/24 15:33:56 mckusick 4 3
c update to latest revision of kgdb debugging protocol
e
s 00009/00015/00029
d D 7.3 91/05/08 14:04:12 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00004/00037
d D 7.2 91/04/20 16:44:31 karels 2 1
c update from lbl: add SL_BUFSIZE, with room for checksum
e
s 00041/00000/00000
d D 7.1 91/03/17 12:12:08 karels 1 0
c from LBL
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1990 Regents of the University of California.
E 3
I 3
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
E 3
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 3
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Lawrence Berkeley Laboratory,
 * Berkeley, CA.  The name of the University may not be used to
 * endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * This code is derived from software contributed to Berkeley by
 * Steven McCanne of Lawrence Berkeley Laboratory.
E 3
 *
D 2
 * @(#) $Header: remote-sl.h,v 1.1 91/01/13 13:18:27 mccanne Exp $ (LBL)
E 2
I 2
D 3
 * @(#) $Header: remote-sl.h,v 1.3 91/03/22 15:34:27 mccanne Exp $ (LBL)
E 3
I 3
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * $Header: remote-sl.h,v 1.3 91/03/22 15:34:27 mccanne Exp $ (LBL)
E 4
I 4
 * $Header: remote-sl.h,v 1.2 92/07/23 19:38:20 mccanne Exp $ (LBL)
E 4
E 3
E 2
 */

I 4
#define FRAME_START		0xc1		/* Frame End */
E 4
#define FRAME_END		0xc0		/* Frame End */
#define FRAME_ESCAPE		0xdb		/* Frame Esc */
D 4
#define TRANS_FRAME_END		0xdc		/* transposed frame end */
E 4
I 4
#define TRANS_FRAME_START	0xde		/* transposed frame start */
#define TRANS_FRAME_END		0xdc		/* transposed frame esc */
E 4
#define TRANS_FRAME_ESCAPE	0xdd		/* transposed frame esc */

/*
D 4
 * Error codes.
E 4
I 4
 * Message limits.  SL_MAXDATA is the maximum number of bytes that can
 * be read or written.  SL_RPCSIZE is the maximum message size for
 * the serial link.  The actual MTU is two times the max message (since
 * each byte might be escaped), plus the two framing bytes.  We add two 
 * to the message length to account for the type byte and checksum.
E 4
 */
D 4
#define EKGDB_CSUM	1
#define EKGDB_2BIG	2
#define EKGDB_RUNT	3

/*
 * Message limits.  SL_MAXMSG is the longest message that can be passed
 * down to the serial link.  The actual MTU is two times the max message
D 2
 * (since each byte might be escaped), plus the framing byte.  We add 2
 * to the message length to account for the type byte and check sum.
E 2
I 2
 * (since each byte might be escaped), plus the two framing bytes.  We add 
 * two to the message length to account for the type byte and check sum.
 * SL_BUFSIZE is one character larger than SL_MAXMSG so we can stuff
 * a checksum into the input buffer without special casing.
E 2
 */
#define SL_MAXMSG 64
D 2
#define SL_MTU ((2 * (SL_MAXMSG + 2) + 1))
E 2
I 2
#define SL_BUFSIZE (SL_MAXMSG + 1)
#define SL_MTU ((2 * (SL_MAXMSG + 2) + 2))
E 4
I 4
#define SL_MAXDATA 62			/* max data that can be read */
#define SL_RPCSIZE (1 + SL_MAXDATA)	/* errno byte + data */
#define SL_MTU ((2 * (SL_RPCSIZE + 2) + 2))
E 4
E 2

E 1
