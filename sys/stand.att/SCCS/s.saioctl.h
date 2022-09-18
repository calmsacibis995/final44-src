h59542
s 00002/00002/00022
d D 8.1 93/06/11 16:02:23 bostic 6 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00022
d R 7.5 91/05/03 10:58:34 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00011/00023
d D 7.4 90/06/28 21:56:55 bostic 4 3
c new copyright notice
e
s 00010/00005/00024
d D 7.3 88/06/29 18:19:21 bostic 3 2
c install approved copyright notice
e
s 00008/00007/00021
d D 7.2 88/03/02 12:09:17 bostic 2 1
c add tahoe ioctl's
e
s 00028/00000/00000
d D 7.1 88/03/02 12:00:30 bostic 1 0
c split out from saio.h
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 4
 * Redistribution and use in source and binary forms are permitted
D 3
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 3
I 3
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 3
 *
 *	%W% (Berkeley) %G%
 */

/* ioctl's -- for disks just now */
#define	SAIOHDR		(('d'<<8)|1)	/* next i/o includes header */
#define	SAIOCHECK	(('d'<<8)|2)	/* next i/o checks data */
#define	SAIOHCHECK	(('d'<<8)|3)	/* next i/o checks header & data */
#define	SAIONOBAD	(('d'<<8)|4)	/* inhibit bad sector forwarding */
#define	SAIODOBAD	(('d'<<8)|5)	/* enable bad sector forwarding */
#define	SAIOECCLIM	(('d'<<8)|6)	/* set limit to ecc correction, bits */
D 2
#define	SAIORETRIES	(('d'<<8)|7)	/* set retry count for unit */
#define	SAIODEVDATA	(('d'<<8)|8)	/* get pointer to pack label */
#define	SAIOSSI		(('d'<<8)|9)	/* set skip sector inhibit */
#define	SAIONOSSI	(('d'<<8)|10)	/* inhibit skip sector handling */
#define	SAIOSSDEV	(('d'<<8)|11)	/* is device skip sector type? */
#define	SAIODEBUG	(('d'<<8)|12)	/* enable/disable debugging */
#define	SAIOGBADINFO	(('d'<<8)|13)	/* get bad-sector table */
E 2
I 2
#define	SAIOECCUNL	(('d'<<8)|7)	/* use standard ecc procedures */
#define	SAIORETRIES	(('d'<<8)|8)	/* set retry count for unit */
#define	SAIODEVDATA	(('d'<<8)|9)	/* get pointer to pack label */
#define	SAIOSSI		(('d'<<8)|10)	/* set skip sector inhibit */
#define	SAIONOSSI	(('d'<<8)|11)	/* inhibit skip sector handling */
#define	SAIOSSDEV	(('d'<<8)|12)	/* is device skip sector type? */
#define	SAIODEBUG	(('d'<<8)|13)	/* enable/disable debugging */
#define	SAIOGBADINFO	(('d'<<8)|14)	/* get bad-sector table */
E 2
E 1
