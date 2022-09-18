h29796
s 00002/00002/00021
d D 8.1 93/06/06 15:36:17 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00012/00022
d D 5.7 90/06/01 17:03:48 bostic 7 6
c new copyright notice
e
s 00002/00002/00032
d D 5.6 89/05/11 13:36:50 bostic 6 5
c file reorg, pathnames.h, paths.h
e
s 00005/00015/00029
d D 5.5 88/11/22 16:51:22 bostic 5 4
c less -> more
e
s 00002/00004/00042
d D 5.4 88/07/25 12:04:38 bostic 4 3
c update copyright notice
e
s 00000/00001/00046
d D 5.3 88/07/22 13:13:15 bostic 3 2
c don't pause after exiting from help file
e
s 00002/00002/00045
d D 5.2 88/07/22 12:04:24 bostic 2 1
c FILENAME is wrong, use MAXPATHLEN
e
s 00047/00000/00000
d D 5.1 88/07/21 18:52:42 bostic 1 0
c distribution by Mark Nudleman
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Mark Nudleman
D 8
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 4
 * This code is derived from software contributed to Berkeley by
 * Mark Nudleman.
 * 
E 4
D 7
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
D 4
 * by the University of California, Berkeley.  The name of the
E 4
I 4
 * by Mark Nudleman and the University of California, Berkeley.  The
 * name of Mark Nudleman or the
E 4
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 5
#include  "less.h"
E 5
I 5
#include <sys/param.h>
#include <less.h>
I 6
#include "pathnames.h"
E 6
E 5

D 5
/*
 * Display some help.
 * Just invoke another "less" to display the help file.
 *
 * {{ This makes this function very simple, and makes changing the
 *    help file very easy, but it may present difficulties on
 *    (non-Unix) systems which do not supply the "system()" function. }}
 */

	public void
E 5
I 5
D 6
#define	HELPFILE	"/usr/lib/more.help"
E 6
E 5
help()
{
D 2
	char cmd[FILENAME+100];
E 2
I 2
D 5
	char cmd[MAXPATHLEN+100];
E 5
I 5
	char cmd[MAXPATHLEN + 20];
E 5
E 2

D 2
	sprintf(cmd, 
E 2
I 2
D 5
	(void)sprintf(cmd,
E 2
	 "-less -m '-PmHELP -- ?eEND -- Press g to see it again:Press RETURN for more., or q when done ' %s",
	 HELPFILE);
E 5
I 5
D 6
	(void)sprintf(cmd, "-more %s", HELPFILE);
E 6
I 6
	(void)sprintf(cmd, "-more %s", _PATH_HELPFILE);
E 6
E 5
	lsystem(cmd);
D 3
	error("End of help");
E 3
}
E 1
