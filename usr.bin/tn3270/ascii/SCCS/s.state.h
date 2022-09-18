h22441
s 00002/00002/00022
d D 8.1 93/06/06 16:38:10 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00021
d D 4.2 91/04/26 15:38:12 bostic 8 7
c new copyright; att/bsd/shared
e
s 00000/00000/00034
d D 4.1 88/12/04 15:11:28 minshall 7 6
c Release 4.1
e
s 00010/00005/00024
d D 3.3 88/06/29 20:00:12 bostic 6 5
c install approved copyright notice
e
s 00011/00001/00018
d D 3.2 88/03/28 12:54:47 bostic 5 4
c add Berkeley specific header
e
s 00000/00000/00019
d D 3.1 87/08/11 10:18:21 minshall 4 3
c New version numbering.
e
s 00001/00001/00018
d D 1.3 87/07/17 10:02:17 minshall 3 2
c Install sccs headers and copyright notices.
e
s 00004/00000/00015
d D 1.2 87/05/31 17:09:52 minshall 2 1
c Version without termcodes.m4.
e
s 00015/00000/00000
d D 1.1 87/05/10 11:35:13 minshall 1 0
c date and time created 87/05/10 11:35:13 by minshall
e
u
U
t
T
I 1
D 8
/*
D 3
 *	@(#)state.h	3.1  10/29/86
E 3
I 3
D 5
 * %W% (Berkeley) %G%
E 5
I 5
 * Copyright (c) 1988 Regents of the University of California.
E 8
I 8
/*-
D 9
 * Copyright (c) 1988 The Regents of the University of California.
E 8
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 8
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 6
 *
 *	%W% (Berkeley) %G%
E 5
E 3
 */

#define	INCLUDED_STATE

/* this defines the state structure used by the key mapping routines */

I 2

#define	STATE_NULL	-1		/* Falls off edge */
#define	STATE_GOTO	-2		/* GOTO internal state */

E 2
#define state	struct State
struct State {
    int		match;		/* character to match */
    int		result;		/* 3270 control code */
    state	*next;		/* next entry in this same state */
    state	*address;	/* if goto, where is next state */
};
E 1
