h13048
s 00002/00000/00050
d D 8.4 95/04/02 23:46:26 mckusick 11 10
c add register_t
e
s 00001/00001/00049
d D 8.3 94/01/05 12:37:03 bostic 10 9
c use latest BSDI version of <sys/cdefs.h>, change to __keyword
e
s 00002/00002/00048
d D 8.2 94/01/04 15:43:05 bostic 9 8
c u_long isn't available if _POSIX_SOURCE is defined
e
s 00002/00002/00048
d D 8.1 93/06/11 15:12:55 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00008/00040
d D 7.7 93/04/30 14:06:01 bostic 7 6
c integral types: one more time, with feeling
e
s 00005/00001/00043
d D 7.6 93/04/30 09:56:39 bostic 6 5
c int8: char -> signed char
e
s 00008/00012/00036
d D 7.5 93/04/29 15:59:54 bostic 5 4
c Use Paul Vixie's versions of basic integral data types
e
s 00002/00002/00046
d D 7.4 93/04/20 18:56:40 torek 4 3
c spelling
e
s 00005/00000/00043
d D 7.3 92/07/21 16:41:41 bostic 3 2
c update the contribution notice; LBL requires acknowledgement
e
s 00015/00000/00028
d D 7.2 92/07/14 14:25:47 bostic 2 1
c add basic data types
e
s 00028/00000/00000
d D 7.1 92/07/13 00:43:08 torek 1 0
c date and time created 92/07/13 00:43:08 by torek
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 3
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 3
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: types.h,v 1.4 92/06/17 06:10:30 torek Exp $ (LBL)
E 4
I 4
 * from: $Header: types.h,v 1.5 92/11/26 02:00:07 torek Exp $ (LBL)
E 4
 */

#ifndef	_MACHTYPES_H_
#define	_MACHTYPES_H_

I 7
#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
E 7
typedef struct _physadr {
	short r[1];
} *physadr;
I 2

E 2
typedef struct label_t {
	int val[2];
} label_t;
I 7
#endif
E 7
I 2

E 2
D 9
typedef	u_long	vm_offset_t;
typedef	u_long	vm_size_t;
E 9
I 9
typedef	unsigned long	vm_offset_t;
typedef	unsigned long	vm_size_t;
E 9
I 2

D 5
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
E 5
I 5
D 6
typedef	char			   int8;	/* Basic integral types. */
E 6
I 6
/*
 * Basic integral types.  Omit the typedef if
 * not possible for a machine/compiler combination.
 */
D 7
typedef	signed char		   int8;
E 6
typedef	unsigned char		 u_int8;
typedef	short			  int16;
typedef	unsigned short		u_int16;
typedef	int			  int32;
typedef	unsigned int		u_int32;
typedef	long long		  int64;
typedef	unsigned long long	u_int64;
E 7
I 7
D 10
typedef	signed char		   int8_t;
E 10
I 10
typedef	__signed char		   int8_t;
E 10
typedef	unsigned char		 u_int8_t;
typedef	short			  int16_t;
typedef	unsigned short		u_int16_t;
typedef	int			  int32_t;
typedef	unsigned int		u_int32_t;
typedef	long long		  int64_t;
typedef	unsigned long long	u_int64_t;
E 7
E 5
E 2

I 11
typedef	int32_t			register_t;

E 11
#endif	/* _MACHTYPES_H_ */
E 1
