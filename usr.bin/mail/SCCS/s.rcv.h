h34644
s 00002/00002/00016
d D 8.1 93/06/06 15:08:37 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00018
d D 5.6 92/06/26 12:03:24 bostic 10 9
c quad's broke it -- prototyped it rather than figure out the problem
e
s 00001/00011/00017
d D 5.5 90/06/01 17:00:10 bostic 9 8
c new copyright notice
e
s 00010/00005/00018
d D 5.4 88/06/29 21:02:03 bostic 8 7
c install approved copyright notice
e
s 00008/00002/00015
d D 5.3 88/02/18 17:04:19 bostic 7 6
c written by Kurt Shoens; added Berkeley specific header
e
s 00000/00003/00017
d D 5.2 87/05/18 12:28:45 edward 6 5
c major rework: made faster, cleaned up, obsolete code removed,
c the whole thing should be chucked and written from scratch
e
s 00007/00001/00013
d D 5.1 85/06/06 10:48:18 dist 5 4
c Add copyright
e
s 00001/00005/00013
d D 2.3 83/08/11 22:19:31 sam 4 3
c standardize sccs keyword lines
e
s 00003/00000/00015
d D 2.2 82/10/21 04:43:25 carl 3 2
c Added ``#include <whoami.h>'' if pdp11 is defined.
e
s 00000/00000/00015
d D 2.1 81/07/01 11:11:29 kurt 2 1
c Release to Heidi Stettner
e
s 00015/00000/00000
d D 1.1 80/10/08 09:53:49 kas 1 0
c date and time created 80/10/08 09:53:49 by kas
e
u
U
f b 
t
T
I 1
D 4
#
E 4
I 4
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*
D 11
 * Copyright (c) 1980 Regents of the University of California.
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 9
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 8
E 7
 *
 *	%W% (Berkeley) %G%
 */
E 5
E 4

/*
 * Mail -- a mail program
 *
 * This file is included by normal files which want both
 * globals and declarations.
D 4
 */

/*
 * Sccs Id = "%W% %G%";
E 4
 */

I 3
D 6
#ifdef	pdp11
#include <whoami.h>
#endif
E 6
E 3
#include "def.h"
#include "glob.h"
E 1
