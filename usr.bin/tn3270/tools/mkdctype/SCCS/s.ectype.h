h26947
s 00002/00002/00024
d D 8.1 93/06/06 16:49:57 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00023
d D 4.2 91/04/26 16:05:58 bostic 7 6
c new copyright; att/bsd/shared
e
s 00000/00000/00036
d D 4.1 88/12/04 15:13:06 minshall 6 5
c Release 4.1
e
s 00010/00005/00026
d D 3.3 88/06/29 20:04:45 bostic 5 4
c install approved copyright notice
e
s 00011/00001/00020
d D 3.2 88/03/28 12:08:13 bostic 4 3
c add Berkeley specific headers
e
s 00000/00000/00021
d D 3.1 87/08/11 10:20:39 minshall 3 2
c New version numbering.
e
s 00001/00001/00020
d D 1.2 87/07/17 10:05:59 minshall 2 1
c Install sccs headers and copyright notices.
e
s 00021/00000/00000
d D 1.1 86/11/12 16:44:13 minshall 1 0
c date and time created 86/11/12 16:44:13 by minshall
e
u
U
t
T
I 1
D 7
/*
D 2
 *	@(#)ectype.h	3.1  10/29/86
E 2
I 2
D 4
 * %W% (Berkeley) %G%
E 4
I 4
 * Copyright (c) 1988 Regents of the University of California.
E 7
I 7
/*-
D 8
 * Copyright (c) 1988 The Regents of the University of California.
E 7
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
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
E 4
E 2
 */

#define	INCLUDED_ECTYPE

#define	E_UPPER	0x01
#define	E_LOWER	0x02
#define	E_DIGIT	0x04
#define	E_SPACE	0x08
#define	E_PUNCT	0x10
#define	E_PRINT 0x20

#define	Eisalpha(c)	(ectype[(c)&0xff]&(E_UPPER|E_LOWER))
#define	Eisupper(c)	(ectype[(c)&0xff]&E_UPPER)
#define	Eislower(c)	(ectype[(c)&0xff]&E_LOWER)
#define	Eisdigit(c)	(ectype[(c)&0xff]&E_DIGIT)
#define	Eisalnum(c)	(ectype[(c)&0xff]&(E_UPPER|E_LOWER|E_DIGIT))
#define	Eisspace(c)	(ectype[(c)&0xff]&E_SPACE)	/* blank or null */
#define	Eispunct(c)	(ectype[(c)&0xff]&E_PUNCT)
#define	Eisprint(c)	(ectype[(c)&0xff]&E_PRINT)
E 1
