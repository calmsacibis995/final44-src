h50865
s 00005/00000/00116
d D 8.4 94/01/21 16:53:03 bostic 19 18
c add USL's copyright notice
e
s 00000/00002/00116
d D 8.3 94/01/04 15:44:27 bostic 18 17
c runetype.h is ANSI safe, need to include it so that __isctype works
e
s 00004/00004/00114
d D 8.2 94/01/03 17:48:18 bostic 17 16
c use latest BSDI version of <sys/cdefs.h>, change to __keyword
e
s 00002/00002/00116
d D 8.1 93/06/06 11:11:52 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00007/00111
d D 5.11 93/06/06 11:11:28 bostic 15 13
c delete extern declarations of sys_errlist, sys_nerr, sys_signame, and
c sys_siglist; they caused nothing but problems as they invariably clashed with
c declarations by the programs; delete unnecessary externs from ctype.h
e
s 00002/00002/00116
d R 8.1 93/06/02 20:05:04 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00023/00041/00095
d D 5.10 93/05/28 12:53:13 bostic 13 12
c don't typedef rune_t if _ANSI_SOURCE defined
c delete macro versions, they're not reentrant; this simplifies lots o' stuff
e
s 00004/00010/00132
d D 5.9 93/05/27 23:08:02 bostic 12 11
c have to use prototype notation so C++ will eat it
c pcc's not gonna handle the inline's anyway, so no big loss
e
s 00124/00026/00018
d D 5.8 93/05/26 20:06:43 bostic 11 10
c rune support from Paul Borman
e
s 00001/00001/00043
d D 5.7 92/03/13 14:06:37 pendry 10 9
c __ctype_ should be __ctype
e
s 00015/00015/00029
d D 5.6 92/03/12 17:33:10 bostic 9 8
c add upper/lower case maps, use double underscores for extern names
e
s 00006/00003/00038
d D 5.5 91/11/21 14:14:55 bostic 8 7
c isascii, isblank and toascii aren't in ANSI
e
s 00010/00009/00031
d D 5.4 91/10/23 17:02:34 bostic 7 6
c add isblank(c)
e
s 00005/00000/00035
d D 5.3 91/04/03 16:09:03 bostic 6 5
c protect all user-level include files against reinclusion
e
s 00001/00011/00034
d D 5.2 90/06/01 14:00:19 bostic 5 4
c new copyright notice
e
s 00042/00025/00003
d D 5.1 89/05/27 10:25:25 bostic 4 2
c reformat, add Berkeley copyright
e
s 00001/00001/00027
d R 4.3 87/04/11 16:24:21 bostic 3 2
c bug report 4.2BSD/lib/25
e
s 00003/00001/00025
d D 4.2 85/09/04 16:08:36 bloom 2 1
c isprint(space) shoudl be true and add isgraph
e
s 00026/00000/00000
d D 4.1 83/05/03 13:47:55 sam 1 0
c date and time created 83/05/03 13:47:55 by sam
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
D 16
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 19
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 19
E 16
 *
I 11
 * This code is derived from software contributed to Berkeley by
 * Paul Borman at Krystal Technologies.
 *
E 11
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */
E 4

I 6
D 11
#ifndef _CTYPE_H_
E 11
I 11
#ifndef	_CTYPE_H_
E 11
#define _CTYPE_H_

I 13
D 18
#ifndef _ANSI_SOURCE
E 18
E 13
E 6
D 4
#define	_U	01
#define	_L	02
#define	_N	04
#define	_S	010
#define _P	020
#define _C	040
#define _X	0100
I 2
#define	_B	0200
E 4
I 4
D 11
#define	_U	0x01
#define	_L	0x02
#define	_N	0x04
#define	_S	0x08
#define	_P	0x10
#define	_C	0x20
#define	_X	0x40
#define	_B	0x80
E 11
I 11
#include <runetype.h>
I 13
D 18
#endif
E 18
E 13
E 11
E 4
E 2

D 4
extern	char	_ctype_[];
E 4
I 4
D 9
extern char	_ctype_[];
E 9
I 9
D 10
extern char __ctype_[], __maplower[], __mapupper[];
E 10
I 10
D 11
extern char __ctype[], __maplower[], __mapupper[];
E 11
I 11
#define	_A	0x00000100L		/* Alpha */
#define	_C	0x00000200L		/* Control */
#define	_D	0x00000400L		/* Digit */
#define	_G	0x00000800L		/* Graph */
#define	_L	0x00001000L		/* Lower */
#define	_P	0x00002000L		/* Punct */
#define	_S	0x00004000L		/* Space */
#define	_U	0x00008000L		/* Upper */
#define	_X	0x00010000L		/* X digit */
#define	_B	0x00020000L		/* Blank */
#define	_R	0x00040000L		/* Print */
#define	_I	0x00080000L		/* Ideogram */
#define	_T	0x00100000L		/* Special */
#define	_Q	0x00200000L		/* Phonogram */
E 11
E 10
E 9
E 4

I 7
D 9
#define	isalnum(c)	((_ctype_ + 1)[c] & (_U|_L|_N))
#define	isalpha(c)	((_ctype_ + 1)[c] & (_U|_L))
D 8
#define	isascii(c)	((unsigned)(c) <= 0177)
#define	isblank(c)	((c) == '\t' || (c) == ' ')
E 8
#define	iscntrl(c)	((_ctype_ + 1)[c] & _C)
E 7
D 4
#define	isalpha(c)	((_ctype_+1)[c]&(_U|_L))
#define	isupper(c)	((_ctype_+1)[c]&_U)
#define	islower(c)	((_ctype_+1)[c]&_L)
#define	isdigit(c)	((_ctype_+1)[c]&_N)
#define	isxdigit(c)	((_ctype_+1)[c]&(_N|_X))
#define	isspace(c)	((_ctype_+1)[c]&_S)
#define ispunct(c)	((_ctype_+1)[c]&_P)
#define isalnum(c)	((_ctype_+1)[c]&(_U|_L|_N))
D 2
#define isprint(c)	((_ctype_+1)[c]&(_P|_U|_L|_N))
E 2
I 2
#define isprint(c)	((_ctype_+1)[c]&(_P|_U|_L|_N|_B))
#define isgraph(c)	((_ctype_+1)[c]&(_P|_U|_L|_N))
E 2
#define iscntrl(c)	((_ctype_+1)[c]&_C)
#define isascii(c)	((unsigned)(c)<=0177)
#define toupper(c)	((c)-'a'+'A')
#define tolower(c)	((c)-'A'+'a')
#define toascii(c)	((c)&0177)
E 4
I 4
#define	isdigit(c)	((_ctype_ + 1)[c] & _N)
I 7
#define	isgraph(c)	((_ctype_ + 1)[c] & (_P|_U|_L|_N))
E 7
#define	islower(c)	((_ctype_ + 1)[c] & _L)
D 7
#define	isspace(c)	((_ctype_ + 1)[c] & _S)
E 7
I 7
#define	isprint(c)	((_ctype_ + 1)[c] & (_P|_U|_L|_N|_B))
E 7
#define	ispunct(c)	((_ctype_ + 1)[c] & _P)
I 7
#define	isspace(c)	((_ctype_ + 1)[c] & _S)
E 7
#define	isupper(c)	((_ctype_ + 1)[c] & _U)
D 7
#define	isalpha(c)	((_ctype_ + 1)[c] & (_U|_L))
E 7
#define	isxdigit(c)	((_ctype_ + 1)[c] & (_N|_X))
D 7
#define	isalnum(c)	((_ctype_ + 1)[c] & (_U|_L|_N))
#define	isprint(c)	((_ctype_ + 1)[c] & (_P|_U|_L|_N|_B))
#define	isgraph(c)	((_ctype_ + 1)[c] & (_P|_U|_L|_N))
#define	iscntrl(c)	((_ctype_ + 1)[c] & _C)
#define	isascii(c)	((unsigned)(c) <= 0177)
#define	toupper(c)	((c) - 'a' + 'A')
#define	tolower(c)	((c) - 'A' + 'a')
E 7
D 8
#define	toascii(c)	((c) & 0177)
E 8
I 7
#define	tolower(c)	((c) - 'A' + 'a')
#define	toupper(c)	((c) - 'a' + 'A')
E 9
I 9
D 11
#define	isalnum(c)	((__ctype + 1)[c] & (_U|_L|_N))
#define	isalpha(c)	((__ctype + 1)[c] & (_U|_L))
#define	iscntrl(c)	((__ctype + 1)[c] & _C)
#define	isdigit(c)	((__ctype + 1)[c] & _N)
#define	isgraph(c)	((__ctype + 1)[c] & (_P|_U|_L|_N))
#define	islower(c)	((__ctype + 1)[c] & _L)
#define	isprint(c)	((__ctype + 1)[c] & (_P|_U|_L|_N|_B))
#define	ispunct(c)	((__ctype + 1)[c] & _P)
#define	isspace(c)	((__ctype + 1)[c] & _S)
#define	isupper(c)	((__ctype + 1)[c] & _U)
#define	isxdigit(c)	((__ctype + 1)[c] & (_N|_X))
#define	tolower(c)	((__maplower + 1)[c])
#define	toupper(c)	((__mapupper + 1)[c])
E 11
I 11
#define isalnum(c)      __istype((c), (_A|_D))
D 13
#define isalpha(c)      __istype((c), _A)
#define iscntrl(c)      __istype((c), _C)
#define isdigit(c)      __isctype((c), _D)	/* ANSI -- locale independent */
#define isgraph(c)      __istype((c), _G)
#define islower(c)      __istype((c), _L)
#define isprint(c)      __istype((c), _R)
#define ispunct(c)      __istype((c), _P)
#define isspace(c)      __istype((c), _S)
#define isupper(c)      __istype((c), _U)
#define isxdigit(c)     __isctype((c), _X)	/* ANSI -- locale independent */
E 13
I 13
#define isalpha(c)      __istype((c),     _A)
#define iscntrl(c)      __istype((c),     _C)
#define isdigit(c)      __isctype((c),    _D)	/* ANSI -- locale independent */
#define isgraph(c)      __istype((c),     _G)
#define islower(c)      __istype((c),     _L)
#define isprint(c)      __istype((c),     _R)
#define ispunct(c)      __istype((c),     _P)
#define isspace(c)      __istype((c),     _S)
#define isupper(c)      __istype((c),     _U)
#define isxdigit(c)     __isctype((c),    _X)	/* ANSI -- locale independent */
E 13
E 11
E 9
I 8

#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
D 9
#define	isascii(c)	((unsigned)(c) <= 0177)
E 9
I 9
D 11
#define	isascii(c)	((unsigned int)(c) <= 0177)
E 9
#define	isblank(c)	((c) == '\t' || (c) == ' ')
#define	toascii(c)	((c) & 0177)
E 11
I 11
#define	isascii(c)	((c & ~0x7F) == 0)
#define toascii(c)	((c) & 0x7F)
#define	digittoint(c)	__istype((c), 0xFF)
#define	isideogram(c)	__istype((c), _I)
#define	isphonogram(c)	__istype((c), _T)
#define	isspecial(c)	__istype((c), _Q)
#define isblank(c)	__istype((c), _B)
#define	isrune(c)	__istype((c),  0xFFFFFF00L)
#define	isnumber(c)	__istype((c), _D)
#define	ishexnumber(c)	__istype((c), _X)
E 11
#endif
I 11

I 13
/* See comments in <machine/ansi.h> about _BSD_RUNE_T_. */
E 13
__BEGIN_DECLS
D 15
extern unsigned long	___runetype __P((_BSD_RUNE_T_));
extern _BSD_RUNE_T_	___tolower __P((_BSD_RUNE_T_));
extern _BSD_RUNE_T_	___toupper __P((_BSD_RUNE_T_));
E 15
I 15
unsigned long	___runetype __P((_BSD_RUNE_T_));
_BSD_RUNE_T_	___tolower __P((_BSD_RUNE_T_));
_BSD_RUNE_T_	___toupper __P((_BSD_RUNE_T_));
E 15
__END_DECLS

/*
D 13
 * See comments in <machine/ansi.h> about _BSD_RUNE_T_.
 *
 * If your compiler supports inline functions, #define _USE_CTYPE_INLINE_.
 * Otherwise, if you want inline macros, #define _USE_CTYPE_MACROS_, else
 * #define _USE_CTYPE_CLIBRARY_ to call C library functions.
E 13
I 13
 * If your compiler supports prototypes and inline functions,
 * #define _USE_CTYPE_INLINE_.  Otherwise, use the C library
 * functions.
E 13
 */
D 13
#define	_USE_CTYPE_INLINE_			/* 4.4BSD */
E 13
I 13
#if !defined(_USE_CTYPE_CLIBRARY_) && defined(__GNUC__) || defined(__cplusplus)
#define	_USE_CTYPE_INLINE_	1
#endif
E 13

#if defined(_USE_CTYPE_INLINE_)
D 17
static inline int
E 17
I 17
static __inline int
E 17
D 12
__istype(c, f)
	_BSD_RUNE_T_ c;
	unsigned long f;
E 12
I 12
__istype(_BSD_RUNE_T_ c, unsigned long f)
E 12
{
	return((((c & _CRMASK) ? ___runetype(c) :
	    _CurrentRuneLocale->runetype[c]) & f) ? 1 : 0);
}

D 17
static inline int
E 17
I 17
static __inline int
E 17
D 12
__isctype(c, f)
	_BSD_RUNE_T_ c;
	unsigned long f;
E 12
I 12
__isctype(_BSD_RUNE_T_ c, unsigned long f)
E 12
{
	return((((c & _CRMASK) ? 0 :
	    _DefaultRuneLocale.runetype[c]) & f) ? 1 : 0);
}

D 13
#if !defined(_ANSI_LIBRARY)	/* _ANSI_LIBRARY: for lib/libc/gen/isctype.c. */
E 13
I 13
/* _ANSI_LIBRARY is defined by lib/libc/gen/isctype.c. */
#if !defined(_ANSI_LIBRARY)
E 13
D 17
static inline _BSD_RUNE_T_
E 17
I 17
static __inline _BSD_RUNE_T_
E 17
D 12
toupper(c)
	_BSD_RUNE_T_ c;
E 12
I 12
toupper(_BSD_RUNE_T_ c)
E 12
{
	return((c & _CRMASK) ?
	    ___toupper(c) : _CurrentRuneLocale->mapupper[c]);
}

D 17
static inline _BSD_RUNE_T_
E 17
I 17
static __inline _BSD_RUNE_T_
E 17
D 12
tolower(c)
	_BSD_RUNE_T_ c;
E 12
I 12
tolower(_BSD_RUNE_T_ c)
E 12
{
	return((c & _CRMASK) ?
	    ___tolower(c) : _CurrentRuneLocale->maplower[c]);
}
#endif /* !_ANSI_LIBRARY */
D 13
#endif /* _USE_CTYPE_INLINE_ */
E 13

D 13
#if defined(_USE_CTYPE_MACROS_)
static int ___ctype_junk;
#define __istype(c, f)							\
	(((((___ctype_junk = (c)) & _CRMASK) ?				\
	    ___runetype(___ctype_junk) :				\
	    _CurrentRuneLocale->runetype[___ctype_junk]) & f) ? 1 : 0)
E 13
I 13
#else /* !_USE_CTYPE_INLINE_ */
E 13

D 13
#define __isctype(c, f)							\
	(((((___ctype_junk = (c)) & _CRMASK) ? 0 :			\
	    _DefaultRuneLocale.runetype[___ctype_junk]) & f) ? 1 : 0)

#define	toupper(c)							\
	(((___ctype_junk = (c)) & _CRMASK) ?				\
	    ___toupper(___ctype_junk) :					\
	    _CurrentRuneLocale->mapupper[___ctype_junk])

#define	tolower(c)							\
	(((___ctype_junk = (c)) & _CRMASK) ?				\
	    ___tolower(___ctype_junk) :					\
	    _CurrentRuneLocale->maplower[___ctype_junk])
#endif /* _USE_CTYPE_MACROS_*/

#if defined(_USE_CTYPE_CLIBRARY_)
E 13
__BEGIN_DECLS
D 15
extern int		__istype __P((_BSD_RUNE_T_, unsigned long));
extern int		__isctype __P((_BSD_RUNE_T_, unsigned long));
extern _BSD_RUNE_T_	toupper __P((_BSD_RUNE_T_));
extern _BSD_RUNE_T_	tolower __P((_BSD_RUNE_T_));
E 15
I 15
int		__istype __P((_BSD_RUNE_T_, unsigned long));
int		__isctype __P((_BSD_RUNE_T_, unsigned long));
_BSD_RUNE_T_	toupper __P((_BSD_RUNE_T_));
_BSD_RUNE_T_	tolower __P((_BSD_RUNE_T_));
E 15
__END_DECLS
D 13
#endif /* _USE_CTYPE_CLIBRARY_ */
E 13
I 13
#endif /* _USE_CTYPE_INLINE_ */
E 13
E 11
E 8
E 7
I 6

#endif /* !_CTYPE_H_ */
E 6
E 4
E 1
