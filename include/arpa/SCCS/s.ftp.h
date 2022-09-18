h43310
s 00002/00002/00081
d D 8.1 93/06/02 20:01:27 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00004/00077
d D 5.6 91/04/03 16:06:57 bostic 8 7
c protect all user-level include files against reinclusion
e
s 00001/00011/00080
d D 5.5 90/06/01 14:02:05 bostic 7 6
c new copyright notice
e
s 00014/00001/00077
d D 5.4 89/02/21 21:28:31 karels 6 4
c add printable names for type, mode, etc
e
s 00014/00001/00077
d R 5.4 89/02/21 21:26:56 karels 5 4
c add printable names for types, modes, etc
e
s 00013/00002/00065
d D 5.3 88/06/27 16:37:41 bostic 4 3
c install approved copyright notice
e
s 00002/00004/00065
d D 5.2 85/05/30 09:48:06 dist 3 2
c Add copyright
e
s 00010/00001/00059
d D 5.1 85/05/30 09:46:26 dist 2 1
c Add copyright
e
s 00060/00000/00000
d D 4.1 83/01/13 23:57:58 sam 1 0
c date and time created 83/01/13 23:57:58 by sam
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
/*
D 6
 * Copyright (c) 1983 Regents of the University of California.
E 6
I 6
D 9
 * Copyright (c) 1983, 1989 Regents of the University of California.
E 6
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1983, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 7
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 4
I 3
 *
 *	%W% (Berkeley) %G%
E 3
 */
D 3

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 3

E 2
D 8
/*
 * Definitions for FTP
 * See RFC-765
 */
E 8
I 8
#ifndef _FTP_H_
#define	_FTP_H_
E 8

I 8
/* Definitions for FTP; see RFC-765. */

E 8
/*
 * Reply codes.
 */
#define PRELIM		1	/* positive preliminary */
#define COMPLETE	2	/* positive completion */
#define CONTINUE	3	/* positive intermediate */
#define TRANSIENT	4	/* transient negative completion */
#define ERROR		5	/* permanent negative completion */

/*
 * Type codes
 */
#define	TYPE_A		1	/* ASCII */
#define	TYPE_E		2	/* EBCDIC */
#define	TYPE_I		3	/* image */
#define	TYPE_L		4	/* local byte size */

I 6
#ifdef FTP_NAMES
char *typenames[] =  {"0", "ASCII", "EBCDIC", "Image", "Local" };
#endif

E 6
/*
 * Form codes
 */
#define	FORM_N		1	/* non-print */
#define	FORM_T		2	/* telnet format effectors */
#define	FORM_C		3	/* carriage control (ASA) */
I 6
#ifdef FTP_NAMES
char *formnames[] =  {"0", "Nonprint", "Telnet", "Carriage-control" };
#endif
E 6

/*
 * Structure codes
 */
#define	STRU_F		1	/* file (no record structure) */
#define	STRU_R		2	/* record structure */
#define	STRU_P		3	/* page structure */
I 6
#ifdef FTP_NAMES
char *strunames[] =  {"0", "File", "Record", "Page" };
#endif
E 6

/*
 * Mode types
 */
#define	MODE_S		1	/* stream */
#define	MODE_B		2	/* block */
#define	MODE_C		3	/* compressed */
I 6
#ifdef FTP_NAMES
char *modenames[] =  {"0", "Stream", "Block", "Compressed" };
#endif
E 6

/*
 * Record Tokens
 */
#define	REC_ESC		'\377'	/* Record-mode Escape */
#define	REC_EOR		'\001'	/* Record-mode End-of-Record */
#define REC_EOF		'\002'	/* Record-mode End-of-File */

/*
 * Block Header
 */
#define	BLK_EOR		0x80	/* Block is End-of-Record */
#define	BLK_EOF		0x40	/* Block is End-of-File */
#define BLK_ERRORS	0x20	/* Block is suspected of containing errors */
#define	BLK_RESTART	0x10	/* Block is Restart Marker */

#define	BLK_BYTECOUNT	2	/* Bytes in this block */
I 8

#endif /* !_FTP_H_ */
E 8
E 1
