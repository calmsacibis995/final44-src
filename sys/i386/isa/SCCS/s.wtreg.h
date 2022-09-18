h63105
s 00002/00002/00067
d D 8.1 93/06/11 15:54:45 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00036/00006/00033
d D 7.1 91/05/09 23:33:01 bostic 3 2
c new copyright; att/bsd/shared
e
s 00001/00001/00038
d D 1.2 91/05/09 20:36:02 william 2 1
c interim version, changes for net2 tape
e
s 00039/00000/00000
d D 1.1 90/11/08 20:14:43 bill 1 0
c date and time created 90/11/08 20:14:43 by bill
e
u
U
t
T
I 1
D 3
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
D 2
 *	%W% (Berkeley) %G%
E 2
I 2
 *	@(#)wtreg.h	1.1 (Berkeley) 11/8/90
E 3
I 3
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
E 3
E 2
 */
I 3

/*
 *
 * Copyright (c) 1989 Carnegie-Mellon University.
 * All rights reserved.
 *
 * Authors: Robert Baron
 * 
 * Permission to use, copy, modify and distribute this software and
 * its documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" 
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND 
 * FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
 */

E 3
/* 
 * HISTORY
 * $Log:	wtreg.h,v $
 * Revision 2.2.1.1  90/01/08  13:29:25  rvb
 * 	Add Intel copyright.
 * 	[90/01/08            rvb]
 * 
 * Revision 2.2  89/09/25  12:33:09  rvb
 * 	Driver was provided by Intel 9/18/89.
 * 	[89/09/23            rvb]
 * 
 */

/*
 *
 *  Copyright 1988, 1989 by Intel Corporation
 *
 */

/*
 *  wtioctl.h
 *   defines ioctl parameters for direct QIC commands
 */

#define	WTIOC	('W'<<8)
#define	WTQICMD	(WTIOC|0)

/* QIC commands allowed */
#define	SELECT	0x01
#define	REWIND	0x21
#define	ERASE	0x22
#define	RETENS	0x24
E 1
