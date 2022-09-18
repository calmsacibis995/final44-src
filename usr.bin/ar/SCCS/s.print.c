h34591
s 00001/00001/00063
d D 8.3 94/04/02 10:04:09 pendry 9 8
c add 1994 copyright
e
s 00008/00008/00056
d D 8.2 94/04/01 04:59:39 pendry 8 7
c prettyness police
e
s 00002/00002/00062
d D 8.1 93/06/06 14:19:45 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00061
d D 5.6 91/03/12 09:07:44 bostic 6 5
c make archive routine naming consistent
e
s 00010/00010/00054
d D 5.5 91/03/11 21:18:58 bostic 5 4
c make ORPHANS a subroutine; files() bug fix
c add externals, minor cleanups
e
s 00010/00004/00054
d D 5.4 91/03/11 14:31:21 bostic 4 3
c change so that the command line file name is used for error/info messages
e
s 00002/00001/00056
d D 5.3 91/03/10 15:37:38 bostic 3 2
c SKIP -> skipobj
e
s 00001/00000/00056
d D 5.2 91/01/21 00:41:25 torek 2 1
c the ORPHANS macro sets eval on error, but does not clear it on success,
c so we must clear it before invoking ORPHANS lest we return a random value
e
s 00056/00000/00000
d D 5.1 91/01/17 18:24:01 bostic 1 0
c date and time created 91/01/17 18:24:01 by bostic
e
u
U
t
T
I 1
/*-
D 7
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
D 9
 * Copyright (c) 1990, 1993
E 9
I 9
 * Copyright (c) 1990, 1993, 1994
E 9
 *	The Regents of the University of California.  All rights reserved.
E 7
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
D 8
#include <fcntl.h>
#include <unistd.h>
E 8
I 8

E 8
#include <dirent.h>
I 8
#include <fcntl.h>
E 8
#include <stdio.h>
I 8
#include <unistd.h>

E 8
#include "archive.h"
I 5
#include "extern.h"
E 5

D 8
extern CHDR chdr;			/* converted header */
extern char *archive;			/* archive name */

E 8
/*
 * print --
 *	Prints archive members on stdout - if member names given only
 *	print those members, otherwise print all members.
 */
I 8
int
E 8
print(argv)
	char **argv;
{
	CF cf;
D 8
	register int afd, all;
E 8
I 8
	int afd, all;
E 8
D 5
	int eval;
E 5
I 4
	char *file;
E 4

	afd = open_archive(O_RDONLY);

I 3
	/* Read from an archive, write to stdout; pad on read. */
E 3
	SETCF(afd, archive, STDOUT_FILENO, "stdout", RPAD);
D 6
	for (all = !*argv; get_header(afd);) {
E 6
I 6
	for (all = !*argv; get_arobj(afd);) {
E 6
D 4
		if (!all && !files(argv)) {
D 3
			SKIP(afd, chdr.size, archive);
E 3
I 3
			skipobj(afd);
E 3
			continue;
E 4
I 4
		if (all)
			file = chdr.name;
D 5
		else {
			file = *argv;
			if (!files(argv)) {
				skipobj(afd);
				continue;
			}
E 5
I 5
		else if (!(file = files(argv))) {
D 6
			skipobj(afd);
E 6
I 6
			skip_arobj(afd);
E 6
			continue;
E 5
E 4
		}
		if (options & AR_V) {
D 4
			(void)printf("\n<%s>\n\n", chdr.name);
E 4
I 4
			(void)printf("\n<%s>\n\n", file);
E 4
			(void)fflush(stdout);
		}
D 6
		copyfile(&cf, chdr.size);
E 6
I 6
		copy_ar(&cf, chdr.size);
E 6
		if (!all && !*argv)
			break;
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
D 8
		return(1);
E 8
I 8
		return (1);
E 8
	}
D 8
	return(0);
E 8
I 8
	return (0);
E 8
E 5
}
E 1
