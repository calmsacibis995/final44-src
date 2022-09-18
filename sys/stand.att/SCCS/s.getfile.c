h14974
s 00002/00002/00024
d D 8.1 93/06/11 16:01:44 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00025
d D 7.8 93/05/24 22:44:00 mckusick 8 7
c new include location
e
s 00001/00001/00025
d D 7.7 92/10/11 10:01:03 bostic 7 6
c make kernel includes standard
e
s 00002/00002/00024
d D 7.6 91/05/05 14:27:11 bostic 6 5
c fix includes
e
s 00001/00011/00025
d D 7.5 90/06/28 21:56:25 bostic 5 4
c new copyright notice
e
s 00000/00003/00036
d D 7.4 90/04/04 16:23:08 mckusick 4 3
c delete unneeded header files
e
s 00005/00003/00034
d D 7.3 90/03/15 19:54:17 root 3 2
c update location of include files
e
s 00010/00005/00027
d D 7.2 88/06/29 18:19:14 bostic 2 1
c install approved copyright notice
e
s 00027/00000/00000
d D 7.1 88/02/05 16:58:19 bostic 1 0
c date and time created 88/02/05 16:58:19 by bostic
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 2
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 2
I 2
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 2
 *
 *	%W% (Berkeley) %G%
 */

D 3
#include "param.h"
#include "inode.h"
#include "fs.h"
E 3
I 3
D 6
#include "sys/param.h"
#include "sys/time.h"
E 6
I 6
#include <sys/param.h>
#include <sys/time.h>
E 6
D 4
#include "sys/vnode.h"
#include "ufs/inode.h"
#include "ufs/fs.h"
E 4
E 3
D 7
#include "saio.h"
E 7
I 7
D 8
#include <stand/saio.h>
E 8
I 8
#include <stand.att/saio.h>
E 8
E 7

getfile(prompt, mode)
	char *prompt;
	int mode;
{
	int fd;
	char buf[100];

	do {
		printf("%s: ", prompt);
		gets(buf);
	} while ((fd = open(buf, mode)) <= 0);
	return(fd);
}
E 1
