h60384
s 00002/00002/00024
d D 8.1 93/06/06 16:33:54 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00026
d D 5.1 90/09/14 10:42:10 borman 5 4
c Bump the sccs id to 5.1
e
s 00001/00011/00025
d D 1.4 90/06/01 17:46:54 bostic 4 3
c new copyright notice
e
s 00010/00005/00026
d D 1.3 88/06/29 20:15:41 bostic 3 2
c install approved copyright notice
e
s 00014/00000/00017
d D 1.2 88/03/08 10:31:23 bostic 2 1
c add Berkeley specific copyright
e
s 00017/00000/00000
d D 1.1 87/09/11 15:40:35 minshall 1 0
c date and time created 87/09/11 15:40:35 by minshall
e
u
U
t
T
I 2
/*
D 6
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 4
 * Redistribution and use in source and binary forms are permitted
D 3
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 3
I 3
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 3
 *
 *	%W% (Berkeley) %G%
 */

E 2
I 1
typedef struct {
    char *modedescriptions;
    char modetype;
} Modelist;

extern Modelist modelist[];

typedef struct {
    int
	system,			/* what the current time is */
	echotoggle,		/* last time user entered echo character */
	modenegotiated,		/* last time operating mode negotiated */
	didnetreceive,		/* last time we read data from network */
	gotDM;			/* when did we last see a data mark */
} Clocks;

extern Clocks clocks;
E 1
