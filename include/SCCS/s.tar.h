h60002
s 00001/00002/00046
d D 8.2 94/01/04 13:50:59 bostic 2 1
c update the copyright notice
e
s 00048/00000/00000
d D 8.1 94/01/04 13:49:51 bostic 1 0
c date and time created 94/01/04 13:49:51 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1994
D 2
 *	The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Chuck Karish of Mindcraft, Inc.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef _TAR_H
#define _TAR_H

#define	TMAGIC		"ustar"	/* ustar and a null */
#define	TMAGLEN		6
#define	TVERSION	"00"	/* 00 and no null */
#define	TVERSLEN	2

/* Values used in typeflag field */
#define	REGTYPE		'0'	/* Regular file */
#define	AREGTYPE	'\0'	/* Regular file */
#define	LNKTYPE		'1'	/* Link */
#define	SYMTYPE		'2'	/* Reserved */
#define	CHRTYPE		'3'	/* Character special */
#define	BLKTYPE		'4'	/* Block special */
#define	DIRTYPE		'5'	/* Directory */
#define	FIFOTYPE	'6'	/* FIFO special */
#define	CONTTYPE	'7'	/* Reserved */

/* Bits used in the mode field - values in octal */
#define	TSUID		04000	/* Set UID on execution */
#define	TSGID		02000	/* Set GID on execution */
#define	TSVTX		01000	/* Reserved */
				/* File permissions */
#define	TUREAD		00400	/* Read by owner */
#define	TUWRITE		00200	/* Write by owner */
#define	TUEXEC		00100	/* Execute/Search by owner */
#define	TGREAD		00040	/* Read by group */
#define	TGWRITE		00020	/* Write by group */
#define	TGEXEC		00010	/* Execute/Search by group */
#define	TOREAD		00004	/* Read by other */
#define	TOWRITE		00002	/* Write by other */
#define	TOEXEC		00001	/* Execute/Search by other */

#endif
E 1
