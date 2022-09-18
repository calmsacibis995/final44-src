h63238
s 00002/00002/00011
d D 8.1 93/06/02 20:06:41 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00013
d D 5.2 91/06/26 11:40:35 marc 9 8
c don't test for _IOCTL_H_
e
s 00002/00002/00013
d D 5.1 91/02/05 17:10:51 bostic 8 7
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00011/00014
d D 4.6 90/06/01 14:01:36 bostic 7 6
c new copyright notice
e
s 00002/00000/00023
d D 4.5 89/10/04 12:18:29 marc 6 5
c protect against redefining USE_OLD_TTY
e
s 00001/00000/00022
d D 4.4 89/08/24 11:13:32 karels 5 4
c they *must* want the old version
e
s 00018/00001/00004
d D 4.3 88/09/22 10:50:24 bostic 4 3
c Berkeley copyright notice
e
s 00000/00015/00005
d D 4.2 85/01/03 10:53:35 bloom 3 1
c get rid of circular dependencies
e
s 00004/00000/00020
d R 4.2 84/12/31 13:15:53 bloom 2 1
c ioctl.h now requires types.h
e
s 00020/00000/00000
d D 4.1 83/05/03 13:48:16 sam 1 0
c date and time created 83/05/03 13:48:16 by sam
e
u
U
t
T
I 1
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
/*
D 10
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 7
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
 *
 *	%W% (Berkeley) %G%
 */
E 4

D 3
/*
 * Structure for stty and gtty system calls.
 */

E 3
D 8
#ifndef	_IOCTL_
E 8
I 8
D 9
#ifndef	_IOCTL_H_
E 9
E 8
I 6
#ifndef USE_OLD_TTY
E 6
I 5
#define	USE_OLD_TTY
I 6
#endif
E 6
E 5
#include <sys/ioctl.h>
D 3
#endif

#ifndef _SGTTYB_
#define	_SGTTYB_
struct sgttyb {
	char	sg_ispeed;		/* input speed */
	char	sg_ospeed;		/* output speed */
	char	sg_erase;		/* erase character */
	char	sg_kill;		/* kill character */
	short	sg_flags;		/* mode flags */
};
E 3
D 8
#endif
E 8
I 8
D 9
#endif /* !_IOCTL_H_ */
E 9
E 8
E 1
