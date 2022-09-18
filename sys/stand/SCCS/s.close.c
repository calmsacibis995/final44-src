h33385
s 00002/00002/00062
d D 8.1 93/06/11 16:00:45 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00064/00000/00000
d D 7.1 93/06/11 14:35:12 mckusick 1 0
c date and time created 93/06/11 14:35:12 by mckusick
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

close(fd)
	int fd;
{
	register struct open_file *f = &files[fd];
	int err1, err2;

	if ((unsigned)fd >= SOPEN_MAX || f->f_flags == 0) {
		errno = EBADF;
		return (-1);
	}
	if (!(f->f_flags & F_RAW))
		err1 = (f->f_ops->close)(f);
	err2 = (f->f_dev->dv_close)(f);
	f->f_flags = 0;
	if (err1) {
		errno = err1;
		return (-1);
	}
	if (err2) {
		errno = err2;
		return (-1);
	}
	return (0);
}
E 1
