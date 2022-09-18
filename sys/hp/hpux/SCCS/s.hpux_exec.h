h16200
s 00002/00002/00033
d D 8.1 93/06/10 21:24:37 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00006/00035
d D 7.4 92/12/27 09:06:20 hibler 4 3
c latest Utah version
e
s 00006/00002/00035
d D 7.3 92/06/05 15:22:17 hibler 3 2
c merge latest Utah hp300 code including 68040 support
e
s 00001/00001/00036
d D 7.2 90/10/24 14:55:57 mckusick 2 1
c update Utah source identifier
e
s 00037/00000/00000
d D 7.1 90/05/08 22:18:37 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: Utah $Hdr: hpux_exec.h 1.4 88/05/24$
E 2
I 2
D 3
 * from: Utah $Hdr: hpux_exec.h 1.1 90/07/09$
E 3
I 3
 * from: Utah $Hdr: hpux_exec.h 1.6 92/01/20$
E 3
E 2
 *
 *	%W% (Berkeley) %G%
 */

/*
 * HPUX a.out header format
 */
struct hpux_exec {
	long	ha_magic;	/* magic number */
	short	ha_version;	/* version ID */
	short	ha_pad0;	/* doesn't matter */
D 3
	long	ha_pad1;	/* ditto */
E 3
I 3
	long	ha_misc;	/* misc. info */
E 3
unsigned long	ha_text;	/* size of text segment */
unsigned long	ha_data;	/* size of initialized data */
unsigned long	ha_bss;		/* size of uninitialized data */
unsigned long	ha_pad2[5];	/* doesn't matter */
unsigned long	ha_entry;	/* entry point */
unsigned long	ha_pad3[4];	/* doesn't matter */
};
I 3

#define	HPUXM_VALID	0x00000001
#define HPUXM_STKWT	0x02000000
#define HPUXM_DATAWT	0x04000000
E 3
D 4

/*
 * If the HPUX object file version number is BSDVNUM the file was built
 * with the HPUX SGS but linked with the BSD libraries.
 */
#define BSDVNUM		0x2BAD
E 4
E 1
