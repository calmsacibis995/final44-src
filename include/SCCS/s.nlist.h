h05053
s 00005/00000/00054
d D 8.2 94/01/21 16:53:04 bostic 9 8
c add USL's copyright notice
e
s 00002/00002/00052
d D 8.1 93/06/02 20:06:07 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00037/00035/00017
d D 5.6 91/04/04 13:44:37 bostic 7 6
c from scratch, add Berkeley copyright; change to be included by a.out.h
e
s 00005/00005/00047
d D 5.5 91/02/05 17:10:57 bostic 6 5
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00001/00051
d D 5.4 90/05/29 19:26:50 bostic 5 4
c C++ wants the prototypes, too
e
s 00006/00000/00046
d D 5.3 90/03/06 15:54:06 bostic 4 3
c add ANSI C prototypes
e
s 00001/00001/00045
d D 5.2 87/04/07 13:22:28 bostic 3 2
c change N_FN to 0x1e
e
s 00007/00001/00039
d D 5.1 85/05/30 09:38:50 dist 2 1
c Add copyright
e
s 00040/00000/00000
d D 4.1 83/05/03 13:48:07 sam 1 0
c date and time created 83/05/03 13:48:07 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
D 7
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
D 8
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
I 9
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 9
E 8
E 7
 *
I 7
 * %sccs.include.redist.c%
 *
E 7
 *	%W% (Berkeley) %G%
 */
E 2

D 7
/*
 * Format of a symbol table entry; this file is included by <a.out.h>
 * and should be used if you aren't interested the a.out header
 * or relocation information.
 */
struct	nlist {
	char	*n_name;	/* for use when in-core */
	unsigned char n_type;	/* type flag, i.e. N_TEXT etc; see below */
	char	n_other;	/* unused */
	short	n_desc;		/* see <stab.h> */
	unsigned long n_value;	/* value of this symbol (or sdb offset) */
};
#define	n_hash	n_desc		/* used internally by ld */
E 7
I 7
#ifndef _NLIST_H_
#define	_NLIST_H_
E 7

/*
D 7
 * Simple values for n_type.
E 7
I 7
 * Symbol table entry format.  The #ifdef's are so that programs including
 * nlist.h can initialize nlist structures statically.
E 7
 */
D 7
#define	N_UNDF	0x0		/* undefined */
#define	N_ABS	0x2		/* absolute */
#define	N_TEXT	0x4		/* text */
#define	N_DATA	0x6		/* data */
#define	N_BSS	0x8		/* bss */
#define	N_COMM	0x12		/* common (internal to ld) */
D 3
#define	N_FN	0x1f		/* file name symbol */
E 3
I 3
#define	N_FN	0x1e		/* file name symbol */
E 7
I 7
struct nlist {
#ifdef _AOUT_INCLUDE_
	union {
		char *n_name;	/* symbol name (in memory) */
		long n_strx;	/* file string table offset (on disk) */
	} n_un;
#else
	char *n_name;		/* symbol name (in memory) */
#endif
E 7
E 3

D 7
#define	N_EXT	01		/* external bit, or'ed in */
E 7
I 7
#define	N_UNDF	0x00		/* undefined */
#define	N_ABS	0x02		/* absolute address */
#define	N_TEXT	0x04		/* text segment */
#define	N_DATA	0x06		/* data segment */
#define	N_BSS	0x08		/* bss segment */
#define	N_COMM	0x12		/* common reference */
#define	N_FN	0x1e		/* file name */

#define	N_EXT	0x01		/* external (global) bit, OR'ed in */
E 7
#define	N_TYPE	0x1e		/* mask for all the type bits */
I 7
	unsigned char n_type;	/* type defines */
E 7

D 7
/*
 * Sdb entries have some of the N_STAB bits set.
 * These are given in <stab.h>
 */
#define	N_STAB	0xe0		/* if any of these bits set, a SDB entry */
E 7
I 7
	char n_other;		/* spare */
#define	n_hash	n_desc		/* used internally by ld(1); XXX */
	short n_desc;		/* used by stab entries */
	unsigned long n_value;	/* address/value of the symbol */
};
E 7

D 7
/*
 * Format for namelist values.
 */
#define	N_FORMAT	"%08x"
E 7
I 7
#define	N_FORMAT	"%08x"	/* namelist value format; XXX */
#define	N_STAB		0x0e0	/* mask for debugger symbols -- stab(5) */
E 7
I 4

D 5
#ifdef __STDC__
E 5
I 5
D 6
#if __STDC__ || c_plusplus
E 5
extern int nlist(const char *, struct nlist *);
#else
extern int nlist();
#endif
E 6
I 6
#include <sys/cdefs.h>

__BEGIN_DECLS
int nlist __P((const char *, struct nlist *));
__END_DECLS
I 7

#endif /* !_NLIST_H_ */
E 7
E 6
E 4
E 1
