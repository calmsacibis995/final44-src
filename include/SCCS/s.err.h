h42185
s 00002/00002/00032
d D 8.1 93/06/02 20:05:18 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00000/00000
d D 5.1 93/03/04 15:01:29 bostic 1 0
c date and time created 93/03/04 15:01:29 by bostic
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
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef _ERR_H_
#define	_ERR_H_

/*
 * Don't use va_list in the err/warn prototypes.   Va_list is typedef'd in two
 * places (<machine/varargs.h> and <machine/stdarg.h>), so if we include one
 * of them here we may collide with the utility's includes.  It's unreasonable
 * for utilities to have to include one of them to include err.h, so we get
 * _BSD_VA_LIST_ from <machine/ansi.h> and use it.
 */
#include <machine/ansi.h>
#include <sys/cdefs.h>

__BEGIN_DECLS
__dead void	err __P((int, const char *, ...));
__dead void	verr __P((int, const char *, _BSD_VA_LIST_));
__dead void	errx __P((int, const char *, ...));
__dead void	verrx __P((int, const char *, _BSD_VA_LIST_));
void		warn __P((const char *, ...));
void		vwarn __P((const char *, _BSD_VA_LIST_));
void		warnx __P((const char *, ...));
void		vwarnx __P((const char *, _BSD_VA_LIST_));
__END_DECLS

#endif /* !_ERR_H_ */
E 1
