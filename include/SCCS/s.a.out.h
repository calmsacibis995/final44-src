h10427
s 00002/00002/00018
d D 8.1 93/06/02 20:04:51 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00019
d D 5.11 92/04/22 17:17:23 mckusick 13 12
c need types.h
e
s 00002/00045/00017
d D 5.10 92/03/18 16:32:15 bostic 12 11
c break up a.out.h into <machine/exec.h>, <machine/reloc.h>
e
s 00000/00007/00062
d D 5.9 92/02/15 21:37:25 mckusick 11 10
c __LDPGSZ moves out to <sys/exec.h>
e
s 00005/00001/00064
d D 5.8 91/09/06 17:53:43 ralph 10 9
c added pmax/mips changes
e
s 00001/00001/00064
d D 5.7 91/07/23 14:41:34 bostic 9 8
c typo
e
s 00021/00009/00044
d D 5.6 91/04/30 12:40:12 bostic 8 7
c add N_TXTADDR, N_DATADDR, use __LDPGSZ as page size #define
e
s 00034/00072/00019
d D 5.5 91/04/04 13:45:46 bostic 7 6
c from scratch, add Berkeley copyright; change to include nlist.h
e
s 00002/00002/00089
d D 5.4 90/12/17 16:40:06 william 6 5
c fix TXTOFF for 386 pagesize (like hp300)
e
s 00010/00001/00081
d D 5.3 90/06/24 12:20:47 bostic 5 4
c 4K pages on the HP's -- should be handled somewhere else?
e
s 00001/00001/00081
d D 5.2 87/04/07 13:22:29 bostic 4 3
c change N_FN to 0x1e
e
s 00007/00001/00075
d D 5.1 85/05/30 09:34:33 dist 3 2
c Add copyright
e
s 00004/00015/00072
d D 4.2 84/07/21 16:05:52 sam 2 1
c move definitions used by the kernel to separate include file
e
s 00087/00000/00000
d D 4.1 83/05/03 13:47:49 sam 1 0
c date and time created 83/05/03 13:47:49 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
D 7
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
D 14
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
E 7
 *
I 7
 * %sccs.include.redist.c%
 *
E 7
 *	%W% (Berkeley) %G%
 */
E 3

D 7
/*
D 2
 * Header prepended to each a.out file.
E 2
I 2
 * Definitions of the a.out header
 * and magic numbers are shared with
 * the kernel.
E 2
 */
E 7
I 7
#ifndef	_AOUT_H_
#define	_AOUT_H_

I 13
#include <sys/types.h>
E 13
E 7
D 2
struct exec {
	long	a_magic;	/* magic number */
unsigned long	a_text;		/* size of text segment */
unsigned long	a_data;		/* size of initialized data */
unsigned long	a_bss;		/* size of uninitialized data */
unsigned long	a_syms;		/* size of symbol table */
unsigned long	a_entry;	/* entry point */
unsigned long	a_trsize;	/* size of text relocation */
unsigned long	a_drsize;	/* size of data relocation */
};

#define	OMAGIC	0407		/* old impure format */
#define	NMAGIC	0410		/* read-only text */
#define	ZMAGIC	0413		/* demand load format */
E 2
I 2
D 12
#include <sys/exec.h>
E 2

I 8
D 10
#if defined(hp300) || defined(i386)
E 10
I 10
D 11
#if defined(hp300) || defined(i386) || defined(mips)
E 10
#define	__LDPGSZ	4096
#endif
#if defined(tahoe) || defined(vax)
#define	__LDPGSZ	1024
#endif

E 11
E 8
D 7
/*
 * Macros which take exec structures as arguments and tell whether
 * the file has a reasonable magic number or offsets to text|symbols|strings.
 */
#define	N_BADMAG(x) \
    (((x).a_magic)!=OMAGIC && ((x).a_magic)!=NMAGIC && ((x).a_magic)!=ZMAGIC)
E 7
I 7
/* Valid magic number check. */
#define	N_BADMAG(ex) \
	((ex).a_magic != NMAGIC && (ex).a_magic != OMAGIC && \
	    (ex).a_magic != ZMAGIC)
E 7

I 8
/* Address of the bottom of the text segment. */
I 10
#ifndef mips
E 10
#define N_TXTADDR(X)	0

/* Address of the bottom of the data segment. */
#define N_DATADDR(ex) \
	(N_TXTADDR(ex) + ((ex).a_magic == OMAGIC ? (ex).a_text \
	: __LDPGSZ + ((ex).a_text - 1 & ~(__LDPGSZ - 1))))

E 8
I 7
/* Text segment offset. */
E 7
I 5
D 8
#if defined(vax) || defined(tahoe)
E 8
E 5
D 7
#define	N_TXTOFF(x) \
D 5
	((x).a_magic==ZMAGIC ? 1024 : sizeof (struct exec))
E 5
I 5
	((x).a_magic == ZMAGIC ? 1024 : sizeof (struct exec))
E 7
I 7
#define	N_TXTOFF(ex) \
D 8
	((ex).a_magic == ZMAGIC ? 1024 : sizeof(struct exec))
E 7
#endif
E 8
I 8
	((ex).a_magic == ZMAGIC ? __LDPGSZ : sizeof(struct exec))
E 8

D 6
#if defined(hp300)
E 6
I 6
D 8
#if defined(hp300) || defined(i386)
E 6
D 7
#define	N_TXTOFF(x) \
D 6
	((x).a_magic == ZMAGIC ? 4096 : sizeof (struct exec))
E 6
I 6
	((x).a_magic == ZMAGIC ? 4096 : sizeof (struct exec)) 
E 7
I 7
#define	N_TXTOFF(ex) \
	((ex).a_magic == ZMAGIC ? 4096 : sizeof(struct exec)) 
E 7
E 6
#endif
E 8
I 8
/* Data segment offset. */
#define	N_DATOFF(ex) \
	(N_TXTOFF(ex) + ((ex).a_magic != ZMAGIC ? (ex).a_text : \
D 9
	: __LDPGSZ + ((ex).a_text - 1 & ~(__LDPGSZ - 1))))
E 9
I 9
	__LDPGSZ + ((ex).a_text - 1 & ~(__LDPGSZ - 1))))
E 9
E 8

E 5
D 7
#define N_SYMOFF(x) \
	(N_TXTOFF(x) + (x).a_text+(x).a_data + (x).a_trsize+(x).a_drsize)
E 7
I 7
/* Symbol table offset. */
#define N_SYMOFF(ex) \
	(N_TXTOFF(ex) + (ex).a_text + (ex).a_data + (ex).a_trsize + \
	    (ex).a_drsize)
E 7
I 5

E 5
D 7
#define	N_STROFF(x) \
	(N_SYMOFF(x) + (x).a_syms)
E 7
I 7
/* String table offset. */
D 8
#define	N_STROFF(ex) \
	(N_SYMOFF(ex) + (ex).a_syms)
E 8
I 8
#define	N_STROFF(ex) 	(N_SYMOFF(ex) + (ex).a_syms)
E 8
E 7

D 7
/*
 * Format of a relocation datum.
 */
E 7
I 7
/* Relocation format. */
E 7
struct relocation_info {
D 7
	int	r_address;	/* address which is relocated */
unsigned int	r_symbolnum:24,	/* local symbol ordinal */
		r_pcrel:1, 	/* was relocated pc relative already */
		r_length:2,	/* 0=byte, 1=word, 2=long */
		r_extern:1,	/* does not include value of sym referenced */
		:4;		/* nothing, yet */
E 7
I 7
	int r_address;			/* offset in text or data segment */
	unsigned int r_symbolnum : 24,	/* ordinal number of add symbol */
			 r_pcrel :  1,	/* 1 if value should be pc-relative */
			r_length :  2,	/* log base 2 of value's width */
			r_extern :  1,	/* 1 if need to add symbol to value */
				 :  4;	/* reserved */
E 7
};
I 10
#else /* mips */
#define N_TXTADDR(X)	0x400000
#endif /* mips */
E 12
I 12
#include <machine/exec.h>
#include <machine/reloc.h>
E 12
E 10

D 7
/*
 * Format of a symbol table entry; this file is included by <a.out.h>
 * and should be used if you aren't interested the a.out header
 * or relocation information.
 */
struct	nlist {
	union {
		char	*n_name;	/* for use when in-core */
		long	n_strx;		/* index into file string table */
	} n_un;
unsigned char	n_type;		/* type flag, i.e. N_TEXT etc; see below */
	char	n_other;	/* unused */
	short	n_desc;		/* see <stab.h> */
unsigned long	n_value;	/* value of this symbol (or sdb offset) */
};
#define	n_hash	n_desc		/* used internally by ld */
E 7
I 7
#define _AOUT_INCLUDE_
#include <nlist.h>
E 7

D 7
/*
 * Simple values for n_type.
 */
#define	N_UNDF	0x0		/* undefined */
#define	N_ABS	0x2		/* absolute */
#define	N_TEXT	0x4		/* text */
#define	N_DATA	0x6		/* data */
#define	N_BSS	0x8		/* bss */
#define	N_COMM	0x12		/* common (internal to ld) */
D 4
#define	N_FN	0x1f		/* file name symbol */
E 4
I 4
#define	N_FN	0x1e		/* file name symbol */
E 4

#define	N_EXT	01		/* external bit, or'ed in */
#define	N_TYPE	0x1e		/* mask for all the type bits */

/*
 * Sdb entries have some of the N_STAB bits set.
 * These are given in <stab.h>
 */
#define	N_STAB	0xe0		/* if any of these bits set, a SDB entry */

/*
 * Format for namelist values.
 */
#define	N_FORMAT	"%08x"
E 7
I 7
#endif /* !_AOUT_H_ */
E 7
E 1
