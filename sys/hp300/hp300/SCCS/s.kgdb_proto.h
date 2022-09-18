h23070
s 00002/00002/00040
d D 8.1 93/06/10 21:40:57 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00002/00034
d D 7.2 92/12/16 17:31:19 mckusick 5 4
c proper acknowledgement
e
s 00000/00000/00036
d D 7.1 91/05/08 13:55:51 bostic 4 3
c yank to 7.1
e
s 00009/00015/00027
d D 1.3 91/05/08 13:55:26 bostic 3 2
c new copyright; att/bsd/shared
e
s 00003/00002/00039
d D 1.2 91/04/20 17:35:57 karels 2 1
c add KGDB_EXEC, KGDB_SEQ
e
s 00041/00000/00000
d D 1.1 91/03/16 19:33:06 karels 1 0
c new protocol for kgdb
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
D 6
 * Copyright (c) 1991 The Regents of the University of California.
E 3
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
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
D 5
 * This code is derived from software contributed to Berkeley by
 * Steven McCanne of Lawrence Berkeley Laboratory.
E 5
I 5
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratories.
E 5
E 3
 *
D 2
 * @(#) $Header: kgdb_proto.h,v 1.1 91/01/10 16:49:43 mccanne Exp $ (LBL)
E 2
I 2
D 3
 * @(#) $Header: kgdb_proto.h,v 1.3 91/03/12 22:06:43 mccanne Exp $ (LBL)
E 3
I 3
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * $Header: kgdb_proto.h,v 1.3 91/03/12 22:06:43 mccanne Exp $ (LBL)
E 3
E 2
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
I 2
#define KGDB_EXEC	0x09
E 2

#define KGDB_CMD(x) ((x) & 0x0f)

/*
 * Message flags.
 */
#define KGDB_ACK	0x80
#define KGDB_DELTA	0x40
#define KGDB_MORE	0x20
D 2

E 2
I 2
#define KGDB_SEQ	0x10
E 2
E 1
