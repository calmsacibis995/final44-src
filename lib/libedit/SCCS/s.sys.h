h05845
s 00002/00002/00085
d D 8.1 93/06/04 16:52:26 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00007/00077
d D 5.3 92/07/03 14:03:11 christos 3 2
c Removed #ifdef sun
e
s 00030/00000/00054
d D 5.2 92/07/03 00:23:58 christos 2 1
c Up-to-date with cornell's last RCS version
e
s 00054/00000/00000
d D 5.1 92/06/22 18:08:38 bostic 1 0
c date and time created 92/06/22 18:08:38 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Christos Zoulas of Cornell University.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * sys.h: Put all the stupid compiler and system dependencies here...
 */
#ifndef _h_sys
#define _h_sys

#ifndef public
# define public		/* Externally visible functions/variables */
#endif

#ifndef private
# define private	static	/* Always hidden internals */
#endif

#ifndef protected
# define protected	/* Redefined from elsewhere to "static" */
			/* When we want to hide everything	*/
#endif

#include <sys/cdefs.h>

#ifndef _PTR_T
# define _PTR_T
# if __STDC__
typedef void* ptr_t;
# else
typedef char* ptr_t;
# endif
#endif

#ifndef _IOCTL_T
# define _IOCTL_T
# if __STDC__
typedef void* ioctl_t;
# else
typedef char* ioctl_t;
# endif
#endif

#include <stdio.h>
I 3
#define REGEXP
E 3

I 2
D 3
#ifdef sun
E 3
I 3
#ifdef SUNOS
# undef REGEXP
# include <malloc.h>
E 3
typedef void (*sig_t)__P((int));
D 3
#ifdef __GNUC__
E 3
I 3
# ifdef __GNUC__
E 3
/*
 * Broken hdrs.
 */
extern char    *getenv		__P((const char *));
extern int	fprintf		__P((FILE *, const char *, ...));
extern int	sigsetmask	__P((int));
extern int	sigblock	__P((int));
extern int	ioctl		__P((int, int, void *));
extern int	fputc		__P((int, FILE *));
extern int	fgetc		__P((FILE *));
extern int	fflush		__P((FILE *));
extern int	tolower		__P((int));
extern int	toupper		__P((int));
extern int	errno, sys_nerr;
extern char	*sys_errlist[];
extern void	perror		__P((const char *));
extern int	read		__P((int, const char*, int));
D 3
#include <string.h>
#define strerror(e)	sys_errlist[e]
#endif
#ifdef SABER
E 3
I 3
#  include <string.h>
#  define strerror(e)	sys_errlist[e]
# endif
# ifdef SABER
E 3
extern ptr_t    memcpy		__P((ptr_t, const ptr_t, size_t));
extern ptr_t    memset		__P((ptr_t, int, size_t));
D 3
#endif
E 3
I 3
# endif
E 3
extern char    *fgetline	__P((FILE *, int *));
#endif

E 2
#endif /* _h_sys */
E 1
