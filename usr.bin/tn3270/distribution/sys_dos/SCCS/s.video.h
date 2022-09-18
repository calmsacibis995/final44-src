h50530
s 00002/00002/00047
d D 8.1 93/06/06 16:46:11 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00046
d D 4.2 91/04/26 15:46:43 bostic 8 7
c new copyright; att/bsd/shared
e
s 00000/00000/00059
d D 4.1 88/12/04 15:12:43 minshall 7 6
c Release 4.1
e
s 00010/00005/00049
d D 3.3 88/06/29 19:57:28 bostic 6 5
c install approved copyright notice
e
s 00014/00002/00040
d D 3.2 88/03/28 12:23:56 bostic 5 4
c add Berkeley specific header
e
s 00000/00000/00042
d D 3.1 87/08/11 10:20:25 minshall 4 3
c New version numbering.
e
s 00002/00000/00040
d D 1.3 87/07/17 10:05:05 minshall 3 2
c Install sccs headers and copyright notices.
e
s 00002/00002/00038
d D 1.2 87/05/13 11:35:05 minshall 2 1
c Fixes (oops).
e
s 00040/00000/00000
d D 1.1 87/05/13 11:32:57 minshall 1 0
c date and time created 87/05/13 11:32:57 by minshall
e
u
U
t
T
I 1
D 8
/*
I 5
 * Copyright (c) 1988 Regents of the University of California.
E 8
I 8
/*-
D 9
 * Copyright (c) 1988 The Regents of the University of California.
E 8
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 8
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 6
 *
 *	%W% (Berkeley) %G%
 */

/*
E 5
 * This is a header file describing the interface via int 10H to the
 * video subsystem.
I 3
D 5
 *
 * %W% (Berkeley) %G%
E 5
E 3
 */

#define	BIOS_VIDEO	0x10

typedef enum {
    SetMode = 0,
    SetCursorType,
    SetCursorPosition,
    ReadCursorPosition,
    ReadLightPenPosition,
    SelectActiveDisplayPage,
    ScrollActivePageUp,
    ScrollActivePageDown,
    ReadAttribute_Character,
D 2
    ReadAttribute_Character,
    ReadCharacterOnly,
E 2
I 2
    WriteAttribute_Character,
    WriteCharacterOnly,
E 2
    SetColorPalette,
    WriteDot,
    ReadDot,
    WriteTeletypeToActivePage,
    CurrentVideoState,
    Reserved16,
    Reserved17,
    Reserved18,
    WriteString
} VideoOperationsType;

typedef enum {
    bw_40x25 = 0,
    color_40x25,
    bw_80x25,
    color_80x25,
    color_320x200,
    bw_320x200,
    bw_640x200,
    internal_bw_80x25
} VideoModeType;
E 1
