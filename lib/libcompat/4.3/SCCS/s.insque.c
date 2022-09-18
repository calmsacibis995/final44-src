h52297
s 00002/00002/00028
d D 8.1 93/06/04 16:25:04 bostic 6 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00002/00026
d R 5.5 91/03/19 19:18:44 bostic 5 4
c define the structures, no longer defined in unistd.h
e
s 00008/00010/00020
d R 5.4 91/02/23 19:49:51 donn 4 3
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00029
d D 5.3 90/06/01 14:11:58 bostic 3 2
c new copyright notice
e
s 00014/00003/00026
d D 5.2 88/07/21 11:31:59 bostic 2 1
c add Berkeley specific copyright; written by Robert Elz
e
s 00029/00000/00000
d D 5.1 87/01/27 16:07:57 mckusick 1 0
c add to portability library
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1987 Regents of the University of California.
D 2
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 3
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif LIBC_SCCS and not lint
E 2
I 2
#endif /* LIBC_SCCS and not lint */
E 2

/*
 * insque -- vax insque instruction
 *
 * NOTE: this implementation is non-atomic!!
 */

struct vaxque {		/* queue format expected by VAX queue instructions */
	struct vaxque	*vq_next;
	struct vaxque	*vq_prev;
};

insque(e, prev)
	register struct vaxque *e, *prev;
{
	e->vq_prev = prev;
	e->vq_next = prev->vq_next;
	prev->vq_next->vq_prev = e;
	prev->vq_next = e;
}
E 1
