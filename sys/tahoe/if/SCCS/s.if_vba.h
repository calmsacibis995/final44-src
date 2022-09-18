h49172
s 00001/00011/00019
d D 1.2 90/06/28 22:24:40 bostic 2 1
c new copyright notice
e
s 00030/00000/00000
d D 1.1 89/03/09 11:20:07 sklower 1 0
c date and time created 89/03/09 11:20:07 by sklower
e
u
U
t
T
I 1
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
D 2
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

struct ifvba {
	struct	mbuf *iff_mbuf;	/* associated mbuf to free */
	caddr_t	iff_buffer;	/* contiguous memory for data, kernel address */
	u_long	iff_physaddr;	/* contiguous memory for data, phys address */
};

#define VIFF_16BIT 1		/* only allow two byte transfers */

#ifdef KERNEL
struct mbuf *if_vbaget();
#endif
E 1
