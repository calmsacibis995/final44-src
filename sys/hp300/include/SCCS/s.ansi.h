h24298
s 00000/00002/00046
d D 8.2 94/01/04 15:45:48 bostic 6 5
c delete completely appropriate, correct and reasonable nastiness
e
s 00002/00002/00046
d D 8.1 93/06/10 21:44:30 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00001/00031
d D 7.4 93/05/26 14:00:39 bostic 4 3
c rune support from Paul Borman
e
s 00010/00010/00022
d D 7.3 92/06/22 21:28:08 bostic 3 2
c prefix all ANSI #define's with BSD_ so don't collide with other vendors
e
s 00001/00000/00031
d D 7.2 91/12/06 14:07:02 bostic 2 1
c add _SSIZE_T_
e
s 00031/00000/00000
d D 7.1 91/03/09 18:05:32 bostic 1 0
c date and time created 91/03/09 18:05:32 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef	_ANSI_H_
#define	_ANSI_H_

/*
 * Types which are fundamental to the implementation and may appear in
 * more than one standard header are defined here.  Standard headers
 * then use:
D 3
 *	#ifdef	_SIZE_T_
 *	typedef	_SIZE_T_ size_t;
 *	#undef	_SIZE_T_
E 3
I 3
 *	#ifdef	_BSD_SIZE_T_
 *	typedef	_BSD_SIZE_T_ size_t;
 *	#undef	_BSD_SIZE_T_
E 3
 *	#endif
D 6
 *
 * Thanks, ANSI!
E 6
 */
D 3
#define	_CLOCK_T_	unsigned long		/* clock() */
#define	_PTRDIFF_T_	int			/* ptr1 - ptr2 */
#define	_SIZE_T_	unsigned int		/* sizeof() */
I 2
#define	_SSIZE_T_	int			/* byte count or error */
E 2
#define	_TIME_T_	long			/* time() */
#define	_VA_LIST_	char *			/* va_list */
#define	_WCHAR_T_	unsigned short		/* wchar_t */
E 3
I 3
#define	_BSD_CLOCK_T_	unsigned long		/* clock() */
#define	_BSD_PTRDIFF_T_	int			/* ptr1 - ptr2 */
#define	_BSD_SIZE_T_	unsigned int		/* sizeof() */
#define	_BSD_SSIZE_T_	int			/* byte count or error */
#define	_BSD_TIME_T_	long			/* time() */
#define	_BSD_VA_LIST_	char *			/* va_list */
D 4
#define	_BSD_WCHAR_T_	unsigned short		/* wchar_t */
E 4
I 4

/*
 * Runes (wchar_t) is declared to be an ``int'' instead of the more natural
 * ``unsigned long'' or ``long''.  Two things are happening here.  It is not
 * unsigned so that EOF (-1) can be naturally assigned to it and used.  Also,
 * it looks like 10646 will be a 31 bit standard.  This means that if your
 * ints cannot hold 32 bits, you will be in trouble.  The reason an int was
 * chosen over a long is that the is*() and to*() routines take ints (says
 * ANSI C), but they use _RUNE_T_ instead of int.  By changing it here, you
 * lose a bit of ANSI conformance, but your programs will still work.
 *    
 * Note that _WCHAR_T_ and _RUNE_T_ must be of the same type.  When wchar_t
 * and rune_t are typedef'd, _WCHAR_T_ will be undef'd, but _RUNE_T remains
 * defined for ctype.h.
 */
#define	_BSD_WCHAR_T_	int			/* wchar_t */
#define	_BSD_RUNE_T_	int			/* rune_t */
E 4
E 3

#endif	/* _ANSI_H_ */
E 1
