h16326
s 00002/00002/00022
d D 8.1 93/06/04 16:51:47 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00024
d D 5.2 92/07/03 00:23:50 christos 2 1
c Up-to-date with cornell's last RCS version
e
s 00024/00000/00000
d D 5.1 92/06/22 18:08:28 bostic 1 0
c date and time created 92/06/22 18:08:28 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Christos Zoulas of Cornell University.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * el.parse.h: Parser functions
 */
#ifndef _h_el_parse
#define _h_el_parse

protected int		 parse_line	__P((EditLine *, const char *)); 
protected int		 parse__escape	__P((const char ** const));
protected char *	 parse__string	__P((char *, const char *));
protected int		 parse_cmd	__P((EditLine *, const char *));

#endif /* _h_el_parse */
E 1
