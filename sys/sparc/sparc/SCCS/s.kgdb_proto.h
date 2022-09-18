h63783
s 00002/00002/00040
d D 8.1 93/06/11 15:16:38 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00040
d D 7.3 93/04/20 23:14:11 torek 3 2
c spelling
e
s 00005/00000/00037
d D 7.2 92/07/21 16:54:28 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00037/00000/00000
d D 7.1 92/07/13 00:44:36 torek 1 0
c date and time created 92/07/13 00:44:36 by torek
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
 * from: $Header: kgdb_proto.h,v 1.4 92/06/17 05:22:06 torek Exp $ (LBL)
E 3
I 3
 * from: $Header: kgdb_proto.h,v 1.5 92/11/26 03:04:54 torek Exp $ (LBL)
E 3
 */

/*
 * Message types.
 */
#define KGDB_MEM_R	0x01
#define KGDB_MEM_W	0x02
#define KGDB_REG_R	0x03
#define KGDB_REG_W	0x04
#define KGDB_CONT	0x05
#define KGDB_STEP	0x06
#define KGDB_KILL	0x07
#define KGDB_SIGNAL	0x08
#define KGDB_EXEC	0x09

#define KGDB_CMD(x) ((x) & 0x0f)

/*
 * Message flags.
 */
#define KGDB_ACK	0x80
#define KGDB_DELTA	0x40
#define KGDB_MORE	0x20
#define KGDB_SEQ	0x10
E 1
