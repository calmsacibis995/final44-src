h03351
s 00002/00002/00038
d D 8.1 93/06/02 20:07:19 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00035
d D 5.7 91/04/03 16:40:43 bostic 10 9
c protect all user-level include files against reinclusion
e
s 00008/00011/00027
d D 5.6 91/02/05 17:10:52 bostic 9 8
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00011/00037
d D 5.5 90/06/01 14:01:57 bostic 8 7
c new copyright notice
e
s 00001/00001/00047
d D 5.4 90/05/29 19:26:57 bostic 7 6
c C++ wants the prototypes, too
e
s 00011/00001/00037
d D 5.3 90/03/06 17:00:11 bostic 6 5
c add ANSI C prototypes
e
s 00028/00012/00010
d D 5.2 89/09/19 11:39:59 bostic 5 4
c cleanup, add defines from libc/gen/getttyent.c, Berkeley copyright
e
s 00007/00001/00015
d D 5.1 85/05/30 09:41:50 dist 4 3
c Add copyright
e
s 00003/00002/00013
d D 4.2 85/01/30 11:34:20 ralph 3 1
c added support for windows
e
s 00003/00002/00013
d R 4.2 85/01/30 10:10:08 ralph 2 1
c support for window systems
e
s 00015/00000/00000
d D 4.1 84/04/27 10:34:35 ralph 1 0
c date and time created 84/04/27 10:34:35 by ralph
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
D 5
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
D 11
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
E 5
 *
I 5
D 8
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
 *
E 5
 *	%W% (Berkeley) %G%
 */
E 4

I 10
#ifndef	_TTYENT_H_
#define	_TTYENT_H_

E 10
D 5
struct	ttyent { /* see getttyent(3) */
E 5
I 5
#define	_PATH_TTYS	"/etc/ttys"

#define	_TTYS_OFF	"off"
#define	_TTYS_ON	"on"
#define	_TTYS_SECURE	"secure"
#define	_TTYS_WINDOW	"window"

struct ttyent {
E 5
	char	*ty_name;	/* terminal device name */
D 3
	char	*ty_getty;	/* name for gettytab (5) */
E 3
I 3
	char	*ty_getty;	/* command to execute, usually getty */
E 3
D 5
	char	*ty_type;	/* terminal type for termcap (3X) */
	int	ty_status;	/* status flags (see below for defines) */
E 5
I 5
	char	*ty_type;	/* terminal type for termcap */
#define	TTY_ON		0x01	/* enable logins (start ty_getty program) */
#define	TTY_SECURE	0x02	/* allow uid of 0 to login */
	int	ty_status;	/* status flags */
E 5
D 3
	char	*ty_comment;	/* unused - for comments */
E 3
I 3
	char 	*ty_window;	/* command to start up window manager */
D 5
	char	*ty_comment;	/* usually the location of the terminal */
E 5
I 5
	char	*ty_comment;	/* comment field */
E 5
E 3
};

D 5
#define TTY_ON		0x1	/* enable logins (startup getty) */
#define TTY_SECURE	0x2	/* allow root to login */

extern struct ttyent *getttyent();
extern struct ttyent *getttynam();
E 5
I 5
D 6
extern struct ttyent *getttyent(), *getttynam();
E 6
I 6
D 7
#ifdef __STDC__
E 7
I 7
D 9
#if __STDC__ || c_plusplus
E 7
extern struct ttyent *getttyent(void);
extern struct ttyent *getttynam(const char *);
extern int setttyent(void);
extern int endttyent(void);
#else
extern struct ttyent *getttyent();
extern struct ttyent *getttynam();
extern int setttyent();
extern int endttyent();
#endif
E 9
I 9
#include <sys/cdefs.h>

__BEGIN_DECLS
struct ttyent *getttyent __P((void));
struct ttyent *getttynam __P((const char *));
int setttyent __P((void));
int endttyent __P((void));
__END_DECLS
I 10

#endif /* !_TTYENT_H_ */
E 10
E 9
E 6
E 5
E 1
