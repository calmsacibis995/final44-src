h56206
s 00002/00000/00039
d D 8.4 95/01/09 18:26:50 cgd 18 17
c add register_t for impending syscall args changes
e
s 00001/00001/00038
d D 8.3 94/01/05 12:35:47 bostic 17 16
c use latest BSDI version of <sys/cdefs.h>, change to __keyword
e
s 00002/00002/00037
d D 8.2 94/01/04 15:15:01 bostic 16 15
c u_long isn't available if _POSIX_SOURCE is defined
e
s 00002/00002/00037
d D 8.1 93/06/10 21:45:29 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00008/00029
d D 7.13 93/04/30 14:04:35 bostic 14 12
c integral types: one more time, with feeling
e
s 00008/00008/00029
d R 7.13 93/04/30 14:02:55 bostic 13 12
c integral types: one more time, with feeling
e
s 00005/00001/00032
d D 7.12 93/04/30 09:55:34 bostic 12 11
c int8: char -> signed char
e
s 00008/00012/00025
d D 7.11 93/04/29 15:56:28 bostic 11 10
c Use Paul Vixie's versions of basic integral data types
e
s 00014/00001/00023
d D 7.10 92/07/14 14:21:34 bostic 10 9
c add basic data types list
e
s 00003/00020/00021
d D 7.9 91/03/09 18:03:11 bostic 9 8
c create {hp300,i386,tahoe,vax}/include/ansi.h
e
s 00001/00001/00040
d D 7.8 91/01/28 21:41:35 mckusick 8 7
c label_t must be defined even if not just kernel
e
s 00003/00003/00038
d D 7.7 91/01/15 21:00:00 bostic 7 6
c until proven otherwise, this stuff is kernel specific
e
s 00002/00002/00039
d D 7.6 91/01/15 20:57:22 bostic 6 5
c stdio has to include this file, don't require types.h
e
s 00002/00000/00039
d D 7.5 90/12/05 19:30:26 mckusick 5 4
c update from Mike Hibler for new VM and other machine support
e
s 00006/00005/00033
d D 7.4 90/06/25 00:49:26 bostic 4 3
c sys/types.h includes this, so can't export anything but *_t to POSIX
e
s 00003/00001/00035
d D 7.3 90/06/23 12:13:43 bostic 3 2
c add _CLOCK_T, _TIME_T for time.h
e
s 00010/00003/00026
d D 7.2 90/05/17 09:29:42 bostic 2 1
c move to machtypes.h; include label_t
e
s 00029/00000/00000
d D 7.1 90/05/15 19:06:01 bostic 1 0
c date and time created 90/05/15 19:06:01 by bostic
e
u
U
t
T
I 1
/*-
D 15
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 2
#ifndef	_X3J11_H_
#define	_X3J11_H_
E 2
I 2
#ifndef	_MACHTYPES_H_
#define	_MACHTYPES_H_
E 2

I 14
#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
E 14
D 9
/*
 * Types which are fundamental to the implementation and may appear in
 * more than one standard header are defined here.  Standard headers
 * then use:
 *	#ifdef	_SIZE_T_
 *	typedef	_SIZE_T_ size_t;
 *	#undef	_SIZE_T_
 *	#endif
 *
 * Thanks, ANSI!
 */
I 3
#define	_CLOCK_T_	unsigned long		/* clock() */
E 3
#define	_PTRDIFF_T_	int			/* ptr1 - ptr2 */
I 3
#define	_SIZE_T_	unsigned int		/* sizeof() */
#define	_TIME_T_	long			/* time() */
E 3
#define	_VA_LIST_	char *			/* va_list */
#define	_WCHAR_T_	unsigned short		/* wchar_t */
D 3
#define	_SIZE_T_	unsigned int		/* sizeof() */
E 3

D 2
#endif	/* _X3J11_H_ */
E 2
I 2
D 4
#ifndef _ANSI_SOURCE
typedef	struct	_physadr { short r[1]; } *physadr;
typedef	struct	label_t	{
	int	val[15];	/* consistent with HP-UX */
E 4
I 4
D 7
#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
E 7
I 7
D 8
#if defined(KERNEL)
E 8
I 8
#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
E 9
E 8
E 7
typedef struct _physadr {
	short r[1];
} *physadr;
I 9

E 9
D 10
typedef struct label_t {		/* consistent with HP-UX */
E 10
I 10
typedef struct label_t {			/* Consistent with HP-UX. */
E 10
	int val[15];
E 4
} label_t;
I 14
#endif
E 14
I 9

E 9
I 5
D 6
typedef	u_long	vm_offset_t;
typedef	u_long	vm_size_t;
E 6
I 6
D 7
typedef	unsigned long	vm_offset_t;
typedef	unsigned long	vm_size_t;
E 7
I 7
D 16
typedef	u_long	vm_offset_t;
typedef	u_long	vm_size_t;
E 16
I 16
typedef	unsigned long	vm_offset_t;
typedef	unsigned long	vm_size_t;
E 16
I 10

D 11
#ifdef	__GNUC__
typedef	char			s1byte_t;	/* Basic data types. */
typedef	unsigned char		u1byte_t;
typedef	short			s2byte_t;
typedef	unsigned short		u2byte_t;
typedef	long			s4byte_t;
typedef	unsigned long		u4byte_t;
typedef	long long		s8byte_t;
typedef	unsigned long long	u8byte_t;
typedef	float			f4byte_t;
typedef	double			f8byte_t;
#endif
E 11
I 11
D 12
typedef	char			   int8;	/* Basic integral types. */
E 12
I 12
/*
 * Basic integral types.  Omit the typedef if
 * not possible for a machine/compiler combination.
 */
D 14
typedef	signed char		   int8;
E 12
typedef	unsigned char		 u_int8;
typedef	short			  int16;
typedef	unsigned short		u_int16;
typedef	int			  int32;
typedef	unsigned int		u_int32;
typedef	long long		  int64;
typedef	unsigned long long	u_int64;
E 14
I 14
D 17
typedef	signed char		   int8_t;
E 17
I 17
typedef	__signed char		   int8_t;
E 17
typedef	unsigned char		 u_int8_t;
typedef	short			  int16_t;
typedef	unsigned short		u_int16_t;
typedef	int			  int32_t;
typedef	unsigned int		u_int32_t;
typedef	long long		  int64_t;
typedef	unsigned long long	u_int64_t;
E 14
E 11
E 10
E 7
E 6
E 5
D 9
#endif
E 9
I 9

I 18
typedef	int32_t			register_t;

E 18
E 9
D 4

E 4
#endif	/* _MACHTYPES_H_ */
E 2
E 1
