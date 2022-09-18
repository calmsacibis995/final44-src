h11049
s 00048/00000/00000
d D 5.1 90/02/02 17:24:13 bostic 1 0
c date and time created 90/02/02 17:24:13 by bostic
e
u
U
t
T
I 1
#ifndef lint
#ifndef NOID
#ifndef TIME_H
#define TIME_H
static char	timehid[] = "@(#)time.h	4.2";
#endif /* !defined TIME_H */
#endif /* !defined NOID */
#endif /* !defined lint */

#ifdef TIME_RECURSING
#include "/usr/include/time.h"
#else /* !defined TIME_RECURSING */
#define TIME_RECURSING
#include <time.h>
#undef TIME_RECURSING
#endif /* !defined TIME_RECURSING */

#ifndef __STDC__

#ifndef time_t
#ifdef unix
#include <sys/types.h>
#else /* !defined unix */
typedef long	time_t;
#endif /* !defined unix */
#endif /* !defined time_t */

extern time_t	time();

#endif /* !defined __STDC__ */

#ifdef __GNUC__

#ifndef time_t
#ifdef unix
#include <sys/types.h>
#else /* !defined unix */
typedef long	time_t;
#endif /* !defined unix */
#endif /* !defined time_t */

extern time_t	time();

#endif /* defined __GNUC__ */

/*
** UNIX is a registered trademark of AT&T.
*/
E 1
