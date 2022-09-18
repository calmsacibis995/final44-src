h39265
s 00002/00002/00019
d D 8.1 93/06/06 22:29:10 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00018
d D 3.9 90/06/06 21:43:58 bostic 9 8
c fix contrib notice (Edward Wang)
e
s 00001/00011/00017
d D 3.8 90/06/02 15:20:34 bostic 8 7
c new copyright notice
e
s 00000/00001/00028
d D 3.7 89/10/13 17:19:59 edward 7 6
c include cleanup
e
s 00010/00005/00019
d D 3.6 88/06/29 21:36:15 bostic 6 5
c install approved copyright notice
e
s 00011/00007/00013
d D 3.5 88/02/21 13:37:12 bostic 5 4
c written by Edward Wang; attach Berkeley specific copyright
e
s 00006/00000/00014
d D 3.4 85/04/24 16:19:58 edward 4 3
c copyright messages
e
s 00001/00001/00013
d D 3.3 84/05/23 02:00:04 edward 3 2
c new sccs id
e
s 00000/00002/00014
d D 3.2 84/01/13 12:08:10 edward 2 1
c include var.h and lcmd.c only in some of the parser?.c
e
s 00016/00000/00000
d D 3.1 84/01/12 12:42:55 edward 1 0
c date and time created 84/01/12 12:42:55 by edward
e
u
U
t
T
I 1
/*
D 3
 *	%W% %E%
E 3
I 3
D 5
 * %W% %G%
E 3
 */

I 4
/*
 * Copyright (c) 1983 Regents of the University of California,
 * All rights reserved.  Redistribution permitted subject to
 * the terms of the Berkeley Software License Agreement.
E 5
I 5
D 10
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
I 9
 * This code is derived from software contributed to Berkeley by
 * Edward Wang at The University of California, Berkeley.
 *
E 9
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
E 5
 */

E 4
D 7
#include <stdio.h>
E 7
#include "value.h"
#include "context.h"
#include "token.h"
#include "string.h"
D 2
#include "lcmd.h"
#include "var.h"
E 2

#define p_erred()	(cx.x_erred)
#define p_synerred()	(cx.x_synerred)
#define p_clearerr()	(cx.x_erred = cx.x_synerred = 0)
#define p_abort()	(cx.x_abort)
E 1
