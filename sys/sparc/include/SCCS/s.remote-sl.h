h46399
s 00002/00002/00040
d D 8.1 93/06/11 15:12:42 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00040
d D 7.3 93/04/20 18:54:41 torek 3 2
c spelling
e
s 00005/00000/00037
d D 7.2 92/07/21 16:41:38 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00037/00000/00000
d D 7.1 92/07/13 00:43:06 torek 1 0
c date and time created 92/07/13 00:43:06 by torek
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
 * from: $Header: remote-sl.h,v 1.5 92/06/17 06:10:27 torek Exp $ (LBL)
E 3
I 3
 * from: $Header: remote-sl.h,v 1.6 92/11/26 02:04:45 torek Exp $ (LBL)
E 3
 */

/*
 * These definitions are factored out into an include file so
 * the kernel stub has access to them.
 */
#define FRAME_START		0xc1		/* Frame End */
#define FRAME_END		0xc0		/* Frame End */
#define FRAME_ESCAPE		0xdb		/* Frame Esc */
#define TRANS_FRAME_START	0xde		/* transposed frame start */
#define TRANS_FRAME_END		0xdc		/* transposed frame esc */
#define TRANS_FRAME_ESCAPE	0xdd		/* transposed frame esc */

/*
 * Message limits. SL_MAXDATA is the maximum number of bytes that can
 * be read or written. SL_BUFSIZE is the maximum amount of data that
 * can be passed across the serial link. The actual MTU is two times
 * the max message (since each byte might be escaped), plus the two
 * framing bytes. We add two to the message length to account for the
 * type byte and checksum.
 */
#define SL_MAXDATA 62			/* max data that can be read */
#define SL_RPCSIZE (1 + SL_MAXDATA)	/* errno byte + data */
#define SL_MTU ((2 * (SL_RPCSIZE + 2) + 2))
E 1
