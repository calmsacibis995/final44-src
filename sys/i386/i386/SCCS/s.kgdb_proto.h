h09604
s 00002/00002/00040
d D 8.1 93/06/11 15:34:49 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00000/00033
d D 7.4 92/12/16 17:30:12 mckusick 4 3
c proper acknowledgement
e
s 00004/00013/00029
d D 7.3 92/01/14 16:32:37 mckusick 3 2
c fix copyright notice; add SCCS keywords
e
s 00000/00000/00042
d D 7.2 91/05/13 01:11:24 william 2 1
c last whacks, numerious bugs and cleanups, sizing disabled due to
c bug I don't care to chase now, other nicer code withdrawn due to bugs
e
s 00042/00000/00000
d D 7.1 91/05/12 22:30:33 william 1 0
c date and time created 91/05/12 22:30:33 by william
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1990 Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
I 4
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratories.
 *
E 4
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
 * %sccs.include.redist.c%
E 3
 *
D 3
 * @(#) $Header: kgdb_proto.h,v 1.3 91/03/12 22:06:43 mccanne Exp $ (LBL)
E 3
I 3
 * from: @(#) $Header: kgdb_proto.h,v 1.3 91/03/12 22:06:43 mccanne Exp $ (LBL)
 *
 *	%W% (Berkeley) %G%
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
