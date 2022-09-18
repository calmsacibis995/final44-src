h45547
s 00018/00009/00069
d D 8.2 94/04/18 14:02:22 bostic 4 3
c new version from Keith Muller (muller@sdcc3.ucsd.edu)
e
s 00002/00002/00076
d D 8.1 93/05/31 14:52:59 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00011/00065
d D 1.2 93/01/14 15:17:55 muller 2 1
c added support for -D and -Y
e
s 00076/00000/00000
d D 1.1 92/12/13 22:51:35 muller 1 0
c date and time created 92/12/13 22:51:35 by muller
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 Keith Muller.
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Keith Muller of the University of California, San Diego.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
I 4
 * argv[0] names. Used for tar and cpio emulation
 */

#define NM_TAR  "tar"
#define NM_CPIO "cpio"
#define NM_PAX  "pax"

/*
E 4
 * Constants used to specify the legal sets of flags in pax. For each major
 * operation mode of pax, a set of illegal flags is defined. If any one of
 * those illegal flags are found set, we scream and exit
 */
#define NONE	"none"

/*
 * flags (one for each option).
 */
#define	AF	0x00000001
#define	BF	0x00000002
#define	CF	0x00000004
#define	DF	0x00000008
#define	FF	0x00000010
#define	IF	0x00000020
#define	KF	0x00000040
#define	LF	0x00000080
#define	NF	0x00000100
#define	OF	0x00000200
#define	PF	0x00000400
#define	RF	0x00000800
#define	SF	0x00001000
#define	TF	0x00002000
#define	UF	0x00004000
#define	VF	0x00008000
#define	WF	0x00010000
#define	XF	0x00020000
#define	CBF	0x00040000	/* nonstandard extension */
D 2
#define	CEF	0x00080000	/* nonstandard extension */
#define	CGF	0x00100000	/* nonstandard extension */
#define	CHF	0x00200000	/* nonstandard extension */
#define	CLF	0x00400000
#define	CTF	0x00800000	/* nonstandard extension */
#define	CUF	0x01000000	/* nonstandard extension */
#define	CXF	0x02000000
#define	CZF	0x04000000	/* nonstandard extension */
E 2
I 2
#define	CDF	0x00080000	/* nonstandard extension */
#define	CEF	0x00100000	/* nonstandard extension */
#define	CGF	0x00200000	/* nonstandard extension */
#define	CHF	0x00400000	/* nonstandard extension */
D 4
#define	CLF	0x00800000
#define	CTF	0x01000000	/* nonstandard extension */
#define	CUF	0x02000000	/* nonstandard extension */
#define	CXF	0x04000000
#define	CYF	0x08000000	/* nonstandard extension */
#define	CZF	0x10000000	/* nonstandard extension */
E 4
I 4
#define	CLF	0x00800000	/* nonstandard extension */
#define	CPF	0x01000000	/* nonstandard extension */
#define	CTF	0x02000000	/* nonstandard extension */
#define	CUF	0x04000000	/* nonstandard extension */
#define	CXF	0x08000000
#define	CYF	0x10000000	/* nonstandard extension */
#define	CZF	0x20000000	/* nonstandard extension */
E 4
E 2

/*
 * ascii string indexed by bit position above (alter the above and you must
 * alter this string) used to tell the user what flags caused us to complain
 */
D 2
#define FLGCH	"abcdfiklnoprstuvwxBEGHLTUXZ"
E 2
I 2
D 4
#define FLGCH	"abcdfiklnoprstuvwxBDEGHLTUXYZ"
E 4
I 4
#define FLGCH	"abcdfiklnoprstuvwxBDEGHLPTUXYZ"
E 4
E 2

/*
 * legal pax operation bit patterns
 */

#define ISLIST(x)	(((x) & (RF|WF)) == 0)
#define	ISEXTRACT(x)	(((x) & (RF|WF)) == RF)
#define ISARCHIVE(x)	(((x) & (AF|RF|WF)) == WF)
#define ISAPPND(x)	(((x) & (AF|RF|WF)) == (AF|WF))
#define	ISCOPY(x)	(((x) & (RF|WF)) == (RF|WF))
#define	ISWRITE(x)	(((x) & (RF|WF)) == WF)

/*
 * Illegal option flag subsets based on pax operation
 */

D 2
#define	BDLIST	(AF|BF|IF|KF|LF|OF|PF|RF|TF|UF|WF|XF|CBF|CHF|CLF|CXF|CZF)
E 2
D 4
#define	BDEXTR	(AF|BF|LF|TF|WF|XF|CBF|CHF|CLF|CXF)
E 4
I 4
#define	BDEXTR	(AF|BF|LF|TF|WF|XF|CBF|CHF|CLF|CPF|CXF)
E 4
D 2
#define	BDARCH	(CF|KF|LF|NF|PF|RF|CEF|CZF)
E 2
I 2
#define	BDARCH	(CF|KF|LF|NF|PF|RF|CDF|CEF|CYF|CZF)
E 2
#define	BDCOPY	(AF|BF|FF|OF|XF|CBF|CEF)
I 2
D 4
#define	BDLIST (AF|BF|IF|KF|LF|OF|PF|RF|TF|UF|WF|XF|CBF|CDF|CHF|CLF|CXF|CYF|CZF)
E 4
I 4
#define	BDLIST (AF|BF|IF|KF|LF|OF|PF|RF|TF|UF|WF|XF|CBF|CDF|CHF|CLF|CPF|CXF|CYF|CZF)
E 4
E 2
E 1
