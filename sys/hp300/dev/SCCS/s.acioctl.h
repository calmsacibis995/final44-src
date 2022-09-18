h28028
s 00002/00002/00058
d D 8.1 93/06/10 21:31:44 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00060/00000/00000
d D 7.1 92/06/05 15:33:07 hibler 1 0
c merge latest Utah hp300 code including 68040 support
e
u
U
t
T
I 1
/*
 * Copyright (c) 1991 University of Utah.
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: acioctl.h 1.1 91/06/19$
 *
 *	%W% (Berkeley) %G%
 */

struct acinfo {
	short	fmte;		/* 1st medium transport elt (picker) */
	short	nmte;		/* # medium transport elts */
	short	fse;		/* 1st storage elt (slot) */
	short	nse;		/* # storage elts */
	short	fiee;		/* 1st import/export elt (mailslot) */
	short	niee;		/* # import/export elts */
	short	fdte;		/* 1st data transport elt (drive) */
	short	ndte;		/* # data transport elts */
};

struct aceltstat {
	short	eaddr;		/* element adress */
	char	type;		/* type of element */
	char	flags;		/* flags */
};

/* types */
#define AC_MTE		0x01	/* picker */
#define AC_SE		0x02	/* slot */
#define AC_IEE		0x03	/* mailslot */
#define AC_DTE		0x04	/* drive */
/* flags */
#define AC_FULL		0x01	/* media present */
#define	AC_ERROR	0x04	/* error accessing element */
#define AC_ACCESS	0x08	/* element accessible */
#define AC_INVERT	0x80	/* media inverted prior to insertion */

struct acmove {
	short	srcelem;
	short	dstelem;
	short	flags;
};

struct acbuffer {
	char	*bufptr;
	int	buflen;
};

#define ACIOCINIT	_IO('A', 0x1)			/* init elt status */
#define ACIOCGINFO	_IOR('A', 0x2, struct acinfo)	/* mode sense */
#define ACIOCGSTAT	_IOW('A', 0x3, struct acbuffer)	/* read elem status */
#define ACIOCMOVE	_IOW('A', 0x4, struct acmove)	/* move elem */
#define ACIOCRAWES	_IOW('A', 0x5, struct acbuffer)	/* raw element stat */
E 1
