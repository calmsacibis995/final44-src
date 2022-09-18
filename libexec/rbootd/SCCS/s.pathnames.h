h04248
s 00002/00002/00023
d D 8.1 93/06/04 19:02:25 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00024
d D 5.3 93/06/04 19:02:15 bostic 4 2
c put the Regents copyright last so 44yank works
e
s 00002/00002/00023
d R 8.1 93/06/04 18:58:28 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00005/00021
d D 5.2 92/07/23 15:45:09 bostic 2 1
c integrate into BSD
e
s 00026/00000/00000
d D 5.1 92/07/23 14:59:11 bostic 1 0
c date and time created 92/07/23 14:59:11 by bostic
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 Regents of the University of California.
E 4
 * Copyright (c) 1988, 1992 The University of Utah and the Center
 *	for Software Science (CSS).
I 4
D 5
 * Copyright (c) 1992 Regents of the University of California.
E 4
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * the Center for Software Science of the University of Utah Computer
 * Science Department.  CSS requests users of this software to return
 * to css-dist@cs.utah.edu any improvements that they make and grant
 * CSS redistribution rights.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * Utah $Hdr: pathnames.h 3.1 92/07/06$
 * Author: Jeff Forys, University of Utah CSS
 */

D 2
#define	_PATH_RBOOTDCONF	"/etc/rbootd.conf"
#define	_PATH_RBOOTDPID		"/etc/rbootd.pid"
#define	_PATH_RBOOTDLIB		"/usr/lib/rbootd"
#define	_PATH_RBOOTDDBG		"/usr/tmp/rbootd.dbg"

E 2
#define	_PATH_BPF		"/dev/bpf%d"
I 2
#define	_PATH_RBOOTDCONF	"/etc/rbootd.conf"
#define	_PATH_RBOOTDDBG		"/tmp/rbootd.dbg"
#define	_PATH_RBOOTDLIB		"/usr/mdec/rbootd"
#define	_PATH_RBOOTDPID		"/var/run/rbootd.pid"
E 2
E 1
