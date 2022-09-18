h43143
s 00002/00002/00062
d D 8.1 93/06/11 16:01:58 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00064/00000/00000
d D 7.1 93/06/11 14:35:23 mckusick 1 0
c date and time created 93/06/11 14:35:23 by mckusick
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * The Mach Operating System project at Carnegie-Mellon University.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *  
 *
 * Copyright (c) 1989, 1990, 1991 Carnegie Mellon University
 * All Rights Reserved.
 *
 * Author: Alessandro Forin
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
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

#include <stand/stand.h>

write(fd, dest, bcount)
	int fd;
	char *dest;
	u_int bcount;
{
	register struct open_file *f = &files[fd];
	u_int resid;

	if ((unsigned)fd >= SOPEN_MAX || !(f->f_flags & F_WRITE)) {
		errno = EBADF;
		return (-1);
	}
	if (f->f_flags & F_RAW) {
		errno = (f->f_dev->dv_strategy)(f->f_devdata, F_WRITE,
			(daddr_t)0, bcount, dest, &resid);
		if (errno)
			return (-1);
		return (resid);
	}
	resid = bcount;
	if (errno = (f->f_ops->write)(f, dest, bcount, &resid))
		return (-1);
	return (0);
}
E 1
