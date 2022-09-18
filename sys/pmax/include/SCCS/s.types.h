h20893
s 00002/00000/00042
d D 8.4 95/06/02 17:24:24 ralph 9 8
c final changes for pmax 4.4-Lite II release
e
s 00001/00001/00041
d D 8.3 94/01/05 12:36:41 bostic 8 7
c use latest BSDI version of <sys/cdefs.h>, change to __keyword
e
s 00002/00002/00040
d D 8.2 94/01/04 15:26:42 bostic 7 6
c u_long isn't available if _POSIX_SOURCE is defined
e
s 00002/00002/00040
d D 8.1 93/06/10 23:03:08 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00008/00032
d D 7.5 93/04/30 14:05:22 bostic 5 4
c integral types: one more time, with feeling
e
s 00005/00001/00035
d D 7.4 93/04/30 09:56:17 bostic 4 3
c int8: char -> signed char
e
s 00008/00012/00028
d D 7.3 93/04/29 15:58:41 bostic 3 2
c Use Paul Vixie's versions of basic integral data types
e
s 00013/00000/00027
d D 7.2 92/07/14 14:25:19 bostic 2 1
c add basic data types
e
s 00027/00000/00000
d D 7.1 92/01/07 20:35:54 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef	_MACHTYPES_H_
#define	_MACHTYPES_H_

I 5
#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
E 5
typedef struct _physadr {
	int r[1];
} *physadr;

typedef struct label_t {
	int val[12];
} label_t;
I 5
#endif
E 5

D 7
typedef	u_long	vm_offset_t;
typedef	u_long	vm_size_t;
E 7
I 7
typedef	unsigned long	vm_offset_t;
typedef	unsigned long	vm_size_t;
E 7

I 2
D 3
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
E 3
I 3
D 4
typedef	char			   int8;	/* Basic integral types. */
E 4
I 4
/*
 * Basic integral types.  Omit the typedef if
 * not possible for a machine/compiler combination.
 */
D 5
typedef	signed char		   int8;
E 4
typedef	unsigned char		 u_int8;
typedef	short			  int16;
typedef	unsigned short		u_int16;
typedef	int			  int32;
typedef	unsigned int		u_int32;
typedef	long long		  int64;
typedef	unsigned long long	u_int64;
E 5
I 5
D 8
typedef	signed char		   int8_t;
E 8
I 8
typedef	__signed char		   int8_t;
E 8
typedef	unsigned char		 u_int8_t;
typedef	short			  int16_t;
typedef	unsigned short		u_int16_t;
typedef	int			  int32_t;
typedef	unsigned int		u_int32_t;
typedef	long long		  int64_t;
typedef	unsigned long long	u_int64_t;
E 5
E 3

I 9
typedef	int32_t			register_t;

E 9
E 2
#endif	/* _MACHTYPES_H_ */
E 1
