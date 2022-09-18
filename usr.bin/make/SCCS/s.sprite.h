h57323
s 00004/00007/00081
d D 8.2 95/04/28 17:08:25 christos 8 7
c Updated to the latest version from the NetBSD source
e
s 00002/00002/00086
d D 8.1 93/06/06 15:17:01 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00087
d D 5.6 93/05/24 19:08:46 bostic 6 5
c merge in rev 5.3->5.4
e
s 00001/00001/00087
d D 5.5 93/05/24 14:45:58 bostic 5 4
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00001/00001/00087
d D 5.4 92/11/06 15:21:53 marc 4 3
c sprite braindeath.  NIL was hardcoded to 0xFFFFFFFF. broke on DEC alpha machine
e
s 00001/00011/00087
d D 5.3 90/06/01 17:09:35 bostic 3 2
c new copyright notice
e
s 00027/00005/00075
d D 5.2 90/03/11 15:55:18 bostic 2 1
c add Berkeley specific copyright notice
e
s 00080/00000/00000
d D 5.1 90/03/11 15:49:05 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
/*
D 2
 * sprite.h --
E 2
I 2
D 7
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
E 7
I 7
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
E 2
 *
D 2
 * Common constants and type declarations for Sprite.
E 2
I 2
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
E 2
 *
D 2
 * Copyright 1985 Regents of the University of California
 * All rights reserved.
E 2
I 2
D 3
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
E 2
 *
I 2
 *	%W% (Berkeley) %G%
 */

/*
 * sprite.h --
E 2
 *
D 2
 * $Id: sprite.h,v 2.1 89/07/03 15:57:45 adam Exp $ SPRITE (Berkeley)
E 2
I 2
 * Common constants and type declarations for Sprite.
E 2
 */

#ifndef _SPRITE
#define _SPRITE


/*
 * A boolean type is defined as an integer, not an enum. This allows a
 * boolean argument to be an expression that isn't strictly 0 or 1 valued.
 */

typedef int Boolean;
#ifndef TRUE
#define TRUE	1
#endif TRUE
#ifndef FALSE
#define FALSE	0
#endif FALSE

/*
 * Functions that must return a status can return a ReturnStatus to
 * indicate success or type of failure.
 */

typedef int  ReturnStatus;

/*
 * The following statuses overlap with the first 2 generic statuses 
 * defined in status.h:
 *
 * SUCCESS			There was no error.
 * FAILURE			There was a general error.
 */

#define	SUCCESS			0x00000000
#define	FAILURE			0x00000001


/*
 * A nil pointer must be something that will cause an exception if 
 * referenced.  There are two nils: the kernels nil and the nil used
 * by user processes.
 */

D 4
#define NIL 		0xFFFFFFFF
E 4
I 4
D 5
#define NIL 		(~0)
E 5
I 5
D 6
#define NIL 		0xFFFFFFFF
E 6
I 6
D 8
#define NIL 		(~0)
E 8
I 8
#define NIL 		~0
E 8
E 6
E 5
E 4
#define USER_NIL 	0
#ifndef NULL
#define NULL	 	0
#endif NULL

/*
 * An address is just a pointer in C.  It is defined as a character pointer
 * so that address arithmetic will work properly, a byte at a time.
 */

typedef char *Address;

/*
 * ClientData is an uninterpreted word.  It is defined as an int so that
 * kdbx will not interpret client data as a string.  Unlike an "Address",
 * client data will generally not be used in arithmetic.
I 8
 * But we don't have kdbx anymore so we define it as void (christos)
E 8
 */

D 8
typedef int *ClientData;
E 8
I 8
typedef void *ClientData;
E 8

D 8
#ifdef notdef
#include "status.h"
#endif

#endif _SPRITE
E 8
I 8
#endif /* _SPRITE */
E 8
E 1
