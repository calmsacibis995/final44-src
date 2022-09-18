h01440
s 00003/00003/00032
d D 8.2 94/01/04 16:16:26 bostic 5 4
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00002/00002/00033
d D 8.1 93/06/02 19:52:58 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00032
d D 7.3 91/02/05 17:03:34 bostic 3 2
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00011/00033
d D 7.2 90/06/28 21:58:21 bostic 2 1
c new copyright notice
e
s 00044/00000/00000
d D 7.1 90/02/15 13:12:56 mckusick 1 0
c temporary holdover for backward compatibility
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1982, 1986, 1989 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
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

/*
 * The information in this file should be obtained from <dirent.h>
 * and is provided solely (and temporarily) for backward compatibility.
 */

D 3
#ifndef _DIRENT_
E 3
I 3
D 5
#ifndef _DIR_H_
#define	_DIR_H_
E 5
I 5
#ifndef _SYS_DIR_H_
#define	_SYS_DIR_H_
E 5
E 3

#include <dirent.h>

/*
 * Backwards compatibility.
 */
#define direct dirent

/*
 * The DIRSIZ macro gives the minimum record length which will hold
 * the directory entry.  This requires the amount of space in struct direct
 * without the d_name field, plus enough space for the name with a terminating
 * null byte (dp->d_namlen+1), rounded up to a 4 byte boundary.
 */
#undef DIRSIZ
#define DIRSIZ(dp) \
    ((sizeof (struct direct) - (MAXNAMLEN+1)) + (((dp)->d_namlen+1 + 3) &~ 3))

D 3
#endif /* _DIRENT_ */
E 3
I 3
D 5
#endif /* !_DIR_H_ */
E 5
I 5
#endif /* !_SYS_DIR_H_ */
E 5
E 3
E 1
