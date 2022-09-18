h43697
s 00002/00002/00030
d D 8.1 93/06/06 16:36:42 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00029
d D 4.2 91/04/26 15:32:21 bostic 9 8
c new copyright; att/bsd/shared
e
s 00000/00000/00042
d D 4.1 88/12/04 15:11:01 minshall 8 7
c Release 4.1
e
s 00010/00005/00032
d D 3.3 88/06/29 19:55:28 bostic 7 6
c install approved copyright notice
e
s 00014/00002/00023
d D 3.2 88/03/28 13:46:48 bostic 6 5
c add Berkeley specific header
e
s 00000/00000/00025
d D 3.1 87/08/11 10:17:39 minshall 5 4
c New version numbering.
e
s 00002/00000/00023
d D 1.4 87/07/17 10:01:31 minshall 4 3
c Install sccs headers and copyright notices.
e
s 00002/00000/00021
d D 1.3 87/06/19 12:37:39 minshall 3 2
c Add declaration of astosc[].
e
s 00001/00000/00020
d D 1.2 87/05/31 17:09:57 minshall 2 1
c Version without termcodes.m4.
e
s 00020/00000/00000
d D 1.1 87/05/31 14:34:19 minshall 1 0
c date and time created 87/05/31 14:34:19 by minshall
e
u
U
t
T
I 1
D 9
/*
I 6
 * Copyright (c) 1988 Regents of the University of California.
E 9
I 9
/*-
D 10
 * Copyright (c) 1988 The Regents of the University of California.
E 9
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 9
 * Redistribution and use in source and binary forms are permitted
D 7
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 7
I 7
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 7
 *
 *	%W% (Berkeley) %G%
 */

/*
E 6
 * This defines the structure used to translate:
 *
 *	ascii name ==> (scancode, shiftstate)
 *
 * (Actually, map3270 does "ascii name ==> index", and
 * termin does "index ==> (scancode, shiftstate)".  Both
 * mappings use this structure.)
I 4
D 6
 *
 * %W% (Berkeley) %G%
E 6
E 4
 */

#define	INCLUDED_ASTOSC

struct astosc {
    unsigned char
	scancode,		/* Scan code for this function */
	shiftstate;		/* Shift state for this function */
I 2
    enum ctlrfcn function;	/* Internal function identifier */
E 2
    char *name;			/* Name of this function */
};

int ascii_to_index();		/* Function to feed InitControl() */
I 3

extern struct astosc astosc[256];
E 3
E 1
