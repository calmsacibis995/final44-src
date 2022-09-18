h29691
s 00001/00001/00069
d D 8.3 94/04/02 10:03:42 pendry 10 9
c add 1994 copyright
e
s 00011/00011/00059
d D 8.2 94/04/01 04:59:40 pendry 9 8
c prettyness police
e
s 00002/00002/00068
d D 8.1 93/06/06 14:19:16 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00069
d D 5.7 93/04/10 00:24:38 torek 7 6
c off_t's are quad, use %qd not %ld
e
s 00002/00002/00068
d D 5.6 91/03/12 09:07:39 bostic 6 5
c make archive routine naming consistent
e
s 00011/00010/00059
d D 5.5 91/03/11 21:16:44 bostic 5 4
c make ORPHANS a subroutine; files() routine bugfix
c add externals, minor cleanups
e
s 00019/00015/00050
d D 5.4 91/03/11 14:31:17 bostic 4 3
c change so that the command line file name is used for error/info messages
e
s 00001/00001/00064
d D 5.3 91/03/10 15:36:29 bostic 3 2
c SKIP -> skipobj
e
s 00002/00002/00063
d D 5.2 91/01/21 00:41:22 torek 2 1
c the ORPHANS macro sets eval on error, but does not clear it on success,
c so we must clear it before invoking ORPHANS lest we return a random value
e
s 00065/00000/00000
d D 5.1 91/01/17 18:23:38 bostic 1 0
c date and time created 91/01/17 18:23:38 by bostic
e
u
U
t
T
I 1
/*-
D 8
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
D 10
 * Copyright (c) 1990, 1993
E 10
I 10
 * Copyright (c) 1990, 1993, 1994
E 10
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * Hugh Smith at The University of Guelph.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/stat.h>
#include <sys/time.h>
D 9
#include <fcntl.h>
#include <unistd.h>
#include <tzfile.h>
#include <dirent.h>
E 9
I 9

E 9
D 5
#include <stdio.h>
E 5
#include <ar.h>
I 9
#include <dirent.h>
#include <fcntl.h>
E 9
I 5
#include <stdio.h>
#include <string.h>
I 9
#include <tzfile.h>
#include <unistd.h>

E 9
E 5
#include "archive.h"
I 5
#include "extern.h"
E 5

D 9
extern CHDR chdr;			/* converted header */
extern char *archive;			/* archive name */

E 9
/*
 * contents --
 *	Handles t[v] option - opens the archive and then reads headers,
D 2
 *	skipping member contents.  If verbose option set, calls verbose
 *	to do ls -l style display.
E 2
I 2
 *	skipping member contents.
E 2
 */
I 9
int
E 9
contents(argv)
D 9
	register char **argv;
E 9
I 9
	char **argv;
E 9
{
D 9
	register int afd, all;
E 9
I 9
	int afd, all;
E 9
D 5
	int eval;
E 5
	struct tm *tp;
D 4
	char buf[25];
E 4
I 4
	char *file, buf[25];
E 4
	
	afd = open_archive(O_RDONLY);

D 6
	for (all = !*argv; get_header(afd);) {
E 6
I 6
	for (all = !*argv; get_arobj(afd);) {
E 6
D 4
		if (all || files(argv)) {
			if (options & AR_V) {
				(void)strmode(chdr.mode, buf);
				(void)printf("%s %6d/%-6d %8ld ",
				    buf + 1, chdr.uid, chdr.gid, chdr.size);
				tp = localtime(&chdr.date);
				(void)strftime(buf, sizeof(buf),
				    "%b %e %H:%M %Y", tp);
				(void)printf("%s %s\n", buf, chdr.name);
			} else
				(void)printf("%s\n", chdr.name);
			if (!all && !*argv)
				break;
E 4
I 4
		if (all)
			file = chdr.name;
D 5
		else {
			file = *argv;
			if (!files(argv))
				goto next;
E 4
		}
E 5
I 5
		else if (!(file = files(argv)))
			goto next;
E 5
D 3
		SKIP(afd, chdr.size, archive);
E 3
I 3
D 4
		skipobj(afd);
E 4
I 4
		if (options & AR_V) {
			(void)strmode(chdr.mode, buf);
D 7
			(void)printf("%s %6d/%-6d %8ld ",
E 7
I 7
			(void)printf("%s %6d/%-6d %8qd ",
E 7
			    buf + 1, chdr.uid, chdr.gid, chdr.size);
			tp = localtime(&chdr.date);
			(void)strftime(buf, sizeof(buf), "%b %e %H:%M %Y", tp);
			(void)printf("%s %s\n", buf, file);
		} else
			(void)printf("%s\n", file);
		if (!all && !*argv)
			break;
D 6
next:		skipobj(afd);
E 6
I 6
next:		skip_arobj(afd);
E 6
E 4
E 3
	} 
I 2
D 5
	eval = 0;
E 2
	ORPHANS;
E 5
	close_archive(afd);
D 5
	return(eval);
E 5
I 5

	if (*argv) {
		orphans(argv);
D 9
		return(1);
E 9
I 9
		return (1);
E 9
	}
D 9
	return(0);
E 9
I 9
	return (0);
E 9
E 5
}
E 1
