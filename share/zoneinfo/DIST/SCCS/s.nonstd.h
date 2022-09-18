h59468
s 00001/00002/00068
d D 5.2 90/02/20 16:24:55 donn 2 1
c dump the damned prototypes when using traditional C
e
s 00070/00000/00000
d D 5.1 90/02/02 17:24:07 bostic 1 0
c date and time created 90/02/02 17:24:07 by bostic
e
u
U
t
T
I 1
#ifndef NONSTD_H

#define NONSTD_H

#ifndef lint
#ifndef NOID
static char	nonstdhid[] = "@(#)nonstd.h	4.2";
#endif /* !defined NOID */
#endif /* !defined lint */

#ifdef __STDC__

#define P(s)		s

#ifdef __TURBOC__
/*
** Cover for stupid Turbo C
*/
#define genericptr_t	void *
#else /* !defined __TURBOC__ */
typedef void *		genericptr_t;
#endif /* !defined __TURBOC__ */

#define alloc_size_t	size_t
#define qsort_size_t	size_t
#define fread_size_t	size_t
#define fwrite_size_t	size_t

#else /* !defined __STDC__ */

D 2
#define ASTERISK	*
#define P(s)		(/ASTERISK s ASTERISK/)
E 2
I 2
#define P(s)		()
E 2

#ifndef genericptr_t
typedef char *		genericptr_t;
#endif /* !defined genericptr_t */

#ifndef alloc_size_t
typedef unsigned	alloc_size_t;
#endif /* !defined alloc_size_t */

#ifndef qsort_size_t
#ifdef unix
#include "sys/param.h"
#endif /* defined unix */
#ifdef BSD
typedef int		qsort_size_t;
#else /* !defined BSD */
typedef unsigned	qsort_size_t;
#endif /* !defined BSD */
#endif /* !defined qsort_size_t */

#ifndef fread_size_t
typedef int		fread_size_t;
#endif /* !defined fread_size_t */

#ifndef fwrite_size_t
typedef int		fwrite_size_t;
#endif /* !defined fwrite_size_t */

#define const
#define volatile

#endif /* !defined __STDC__ */

#endif /* !defined NONSTD_H */

/*
** UNIX is a registered trademark of AT&T.
*/
E 1
