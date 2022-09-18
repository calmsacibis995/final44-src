h44947
s 00002/00002/00023
d D 8.1 93/06/02 20:07:10 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00020
d D 5.2 91/04/03 16:28:25 bostic 3 2
c protect all user-level include files against reinclusion
e
s 00018/00007/00002
d D 5.1 91/01/20 14:11:45 bostic 2 1
c Berkeley specific copyright, document each #define
e
s 00009/00000/00000
d D 4.1 83/05/03 13:48:20 sam 1 0
c date and time created 83/05/03 13:48:20 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/

/*
 * access to information relating to the fields of a structure
E 2
I 2
/*-
D 4
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
E 2
 */

I 3
#ifndef _STRUCT_H_
#define	_STRUCT_H_

E 3
D 2
#define	fldoff(str, fld)	((int)&(((struct str *)0)->fld))
#define	fldsiz(str, fld)	(sizeof(((struct str *)0)->fld))
#define	strbase(str, ptr, fld)	((struct str *)((char *)(ptr)-fldoff(str, fld)))
E 2
I 2
/* Offset of the field in the structure. */
#define	fldoff(name, field) \
	((int)&(((struct name *)0)->field))

/* Size of the field in the structure. */
#define	fldsiz(name, field) \
	(sizeof(((struct name *)0)->field))

/* Address of the structure from a field. */
#define	strbase(name, addr, field) \
	((struct name *)((char *)(addr) - fldoff(name, field)))
I 3

#endif /* !_STRUCT_H_ */
E 3
E 2
E 1
