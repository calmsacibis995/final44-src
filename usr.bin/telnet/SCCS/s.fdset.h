h57362
s 00002/00002/00021
d D 8.1 93/06/06 16:32:53 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00023
d D 5.1 90/09/14 10:42:02 borman 6 5
c Bump the sccs id to 5.1
e
s 00001/00011/00022
d D 1.5 90/06/01 17:45:12 bostic 5 4
c new copyright notice
e
s 00010/00005/00023
d D 1.4 88/06/29 20:15:18 bostic 4 3
c install approved copyright notice
e
s 00014/00000/00014
d D 1.3 88/03/08 10:30:48 bostic 3 2
c add Berkeley specific copyright
e
s 00000/00000/00014
d D 1.2 87/11/23 11:15:40 minshall 2 1
c Add in some changes from Dave Borman (borman@monet).
e
s 00014/00000/00000
d D 1.1 87/11/23 11:14:09 minshall 1 0
c date and time created 87/11/23 11:14:09 by minshall
e
u
U
t
T
I 1
/*
I 3
D 7
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
 *
 *	%W% (Berkeley) %G%
 */

/*
E 3
 * The following is defined just in case someone should want to run
 * this telnet on a 4.2 system.
 *
 */

#ifndef	FD_SETSIZE

#define	FD_SET(n, p)	((p)->fds_bits[0] |= (1<<(n)))
#define	FD_CLR(n, p)	((p)->fds_bits[0] &= ~(1<<(n)))
#define	FD_ISSET(n, p)	((p)->fds_bits[0] & (1<<(n)))
#define FD_ZERO(p)	((p)->fds_bits[0] = 0)

#endif
E 1
