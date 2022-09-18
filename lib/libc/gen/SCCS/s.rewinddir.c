h15512
s 00002/00002/00020
d D 8.1 93/06/08 17:57:08 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00003/00020
d D 5.2 93/06/08 17:46:00 mckusick 3 1
c global _rewinddir moves to structure dd_rewind
e
s 00002/00002/00021
d R 8.1 93/06/04 12:04:42 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00023/00000/00000
d D 5.1 90/05/25 17:34:21 bostic 1 0
c date and time created 90/05/25 17:34:21 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <dirent.h>

void
rewinddir(dirp)
	DIR *dirp;
{
D 3
	extern long _rewinddir;
E 3

D 3
	_seekdir((dirp), _rewinddir);
	_rewinddir = telldir(dirp);
E 3
I 3
	_seekdir(dirp, dirp->dd_rewind);
	dirp->dd_rewind = telldir(dirp);
E 3
}
E 1
