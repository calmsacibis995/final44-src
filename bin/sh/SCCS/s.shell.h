h14181
s 00000/00000/00058
d D 8.2 95/05/04 18:00:10 christos 8 7
c 
e
s 00002/00002/00056
d D 8.1 93/05/31 15:20:39 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00055
d D 5.6 92/07/15 09:11:13 marc 6 5
c remove some configuration parameters
e
s 00000/00004/00058
d D 5.5 92/04/30 15:05:11 marc 5 4
c remove UDIR (we now have tilde)
e
s 00009/00008/00053
d D 5.4 91/04/12 18:19:34 marc 4 3
c cleanups
e
s 00003/00002/00058
d D 5.3 91/03/08 16:46:24 bostic 3 2
c make the world safe for pcc
e
s 00000/00002/00060
d D 5.2 91/03/07 21:09:37 bostic 2 1
c handle const, volatile in <sys/cdefs.h>
e
s 00062/00000/00000
d D 5.1 91/03/07 20:27:59 bostic 1 0
c date and time created 91/03/07 20:27:59 by bostic
e
u
U
t
T
I 1
/*-
D 7
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * The follow should be set to reflect the type of system you have:
 *	JOBS -> 1 if you have Berkeley job control, 0 otherwise.
 *	SYMLINKS -> 1 if your system includes symbolic links, 0 otherwise.
D 6
 *	DIRENT -> 1 if your system has the SVR3 directory(3X) routines.
E 6
D 5
 *	UDIR -> 1 if you want the shell to simulate the /u directory.
I 4
 *	ATTY -> 1 to include code for atty(1).
E 5
E 4
 *	SHORTNAMES -> 1 if your linker cannot handle long names.
 *	define BSD if you are running 4.2 BSD or later.
 *	define SYSV if you are running under System V.
D 4
 *	define DEBUG to turn on debugging.
E 4
I 4
 *	define DEBUG=1 to compile in debugging (set global "debug" to turn on)
 *	define DEBUG=2 to compile in and turn on debugging.
E 4
 *
 * When debugging is on, debugging info will be written to $HOME/trace and
 * a quit signal will generate a core dump.
 */

I 3
D 4
#include <sys/cdefs.h>
E 4
E 3

#define JOBS 1
#define SYMLINKS 1
D 6
#define DIRENT 1
D 5
#define UDIR 0
#define ATTY 0
E 5
D 4
#define SHORTNAMES 0
E 4
#define BSD
E 6
I 6
#ifndef BSD
#define BSD 1
#endif
E 6
D 4
/* #define SYSV */
/* #define DEBUG */
E 4
I 4
#define DEBUG 1
E 4

D 3
#ifdef __STDC__
E 3
D 4
typedef void *pointer;
I 3

E 4
#ifdef __STDC__
I 4
typedef void *pointer;
E 4
E 3
#ifndef NULL
#define NULL (void *)0
#endif
#else /* not __STDC__ */
I 4
typedef char *pointer;
E 4
D 2
#define const
#define volatile
E 2
D 3
typedef char *pointer;
E 3
#ifndef NULL
#define NULL 0
#endif
D 4
#endif /* __STDC__ */
E 4
I 4
#endif /*  not __STDC__ */
E 4
#define STATIC	/* empty */
#define MKINIT	/* empty */
I 4

#include <sys/cdefs.h>
E 4

extern char nullstr[1];		/* null string */


#ifdef DEBUG
#define TRACE(param)	trace param
#else
#define TRACE(param)
#endif
E 1
