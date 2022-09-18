h59094
s 00002/00002/00027
d D 8.1 93/06/04 19:06:59 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00002/00023
d D 5.6 93/04/05 16:48:20 dab 6 5
c Fix gcc2 warnings.
c Add ENV_HACK stuff to deal with telnet clients that
c have the wrong definitions for ENV_VAR and ENV_VALUE.
c Fix up the flow-control processing to work on systems
c that don't use Linemode in the server.
e
s 00004/00000/00021
d D 5.5 90/06/28 13:06:04 borman 5 4
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00001/00011/00020
d D 5.4 90/06/01 15:55:48 bostic 4 3
c new copyright notice
e
s 00011/00002/00020
d D 5.3 89/09/01 15:16:36 borman 3 2
c New telnetd, with LINEMODE support
e
s 00003/00001/00019
d D 5.2 89/05/11 14:34:04 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00020/00000/00000
d D 5.1 89/04/02 15:36:52 bostic 1 0
c date and time created 89/04/02 15:36:52 by bostic
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */

D 2
#define	_PATH_LOGIN	"/bin/login"
E 2
I 2
D 3
#include <paths.h>
E 3
I 3
#if BSD > 43
E 3

D 3
#define	_PATH_LOGIN	"/usr/bin/login"
E 3
I 3
# include <paths.h>

D 6
# define	_PATH_LOGIN	"/usr/bin/login"
E 6
I 6
# ifndef _PATH_LOGIN
#  define	_PATH_LOGIN	"/usr/bin/login"
# endif
E 6

#else
 
# define	_PATH_TTY	"/dev/tty"
D 6
# define	_PATH_LOGIN	"/bin/login"
E 6
I 6
# ifndef _PATH_LOGIN
#  define	_PATH_LOGIN	"/bin/login"
# endif
E 6

#endif
I 5

#ifdef BFTPDAEMON
#define		BFTPPATH	"/usr/ucb/bftp"
#endif  /* BFTPDAEMON */
E 5
E 3
E 2
E 1
