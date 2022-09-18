h44091
s 00001/00001/00101
d D 8.3 94/04/02 10:03:57 pendry 8 7
c add 1994 copyright
e
s 00013/00017/00089
d D 8.2 94/04/01 04:59:42 pendry 7 6
c prettyness police
e
s 00002/00002/00104
d D 8.1 93/06/06 14:19:31 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00102
d D 5.5 91/03/12 09:07:42 bostic 5 4
c make archive routine naming consistent
e
s 00012/00009/00094
d D 5.4 91/03/11 21:17:34 bostic 4 3
c make ORPHANS a function; files() bug fix
c add externals, minor cleanups
e
s 00002/00002/00101
d D 5.3 91/03/11 14:31:19 bostic 3 2
c change so that the command line file name is used for error/info messages
e
s 00004/00003/00099
d D 5.2 91/03/10 15:36:56 bostic 2 1
c SKIP -> skipobj
e
s 00102/00000/00000
d D 5.1 91/01/17 18:23:46 bostic 1 0
c date and time created 91/01/17 18:23:46 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
D 8
 * Copyright (c) 1990, 1993
E 8
I 8
 * Copyright (c) 1990, 1993, 1994
E 8
 *	The Regents of the University of California.  All rights reserved.
E 6
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
#include <sys/time.h>
#include <sys/stat.h>
D 2
#include <sys/errno.h>
E 2
D 7
#include <fcntl.h>
I 2
#include <errno.h>
E 7
I 7

E 7
E 2
D 4
#include <unistd.h>
E 4
#include <dirent.h>
I 4
D 7
#include <unistd.h>
E 7
I 7
#include <err.h>
#include <fcntl.h>
E 7
E 4
#include <stdio.h>
I 4
#include <string.h>
I 7
#include <unistd.h>

E 7
E 4
#include "archive.h"
I 4
#include "extern.h"
E 4

D 7
extern CHDR chdr;			/* converted header */
extern char *archive;			/* archive name */

E 7
/*
 * extract --
 *	Extract files from the named archive - if member names given only
 *	extract those members otherwise extract all members.  If 'o' option
 *	selected modify date of newly created file to be same as archive
 *	members date otherwise date is time of extraction.  Does not modify
 *	archive.
 */
I 7
int
E 7
extract(argv)
	char **argv;
{
D 7
	register int afd, all, tfd;
E 7
I 7
	char *file;
	int afd, all, eval, tfd;
E 7
	struct timeval tv[2];
	struct stat sb;
	CF cf;
D 7
	int eval;
D 3
	char *file, *rname();
E 3
I 3
	char *file;
E 7
E 3

	eval = 0;
	tv[0].tv_usec = tv[1].tv_usec = 0;

	afd = open_archive(O_RDONLY);

I 2
	/* Read from an archive, write to disk; pad on read. */
E 2
	SETCF(afd, archive, 0, 0, RPAD);
D 5
	for (all = !*argv; get_header(afd);) {
E 5
I 5
	for (all = !*argv; get_arobj(afd);) {
E 5
		if (all)
			file = chdr.name;
D 4
		else {
			file = *argv;
			if (!files(argv)) {
D 2
				SKIP(afd, chdr.size, archive);
E 2
I 2
				skipobj(afd);
E 2
				continue;
			}
E 4
I 4
		else if (!(file = files(argv))) {
D 5
			skipobj(afd);
E 5
I 5
			skip_arobj(afd);
E 5
			continue;
E 4
		}

		if (options & AR_U && !stat(file, &sb) &&
		    sb.st_mtime > chdr.date)
			continue;

		if ((tfd = open(file, O_WRONLY|O_CREAT|O_TRUNC, S_IWUSR)) < 0) {
D 7
			(void)fprintf(stderr, "ar: %s: %s.\n",
			    file, strerror(errno));
E 7
I 7
			warn("%s", file);
E 7
D 2
			SKIP(afd, chdr.size, archive);
E 2
I 2
D 5
			skipobj(afd);
E 5
I 5
			skip_arobj(afd);
E 5
E 2
			eval = 1;
			continue;
		}

		if (options & AR_V)
D 3
			(void)printf("x - %s\n", rname(file));
E 3
I 3
			(void)printf("x - %s\n", file);
E 3

		cf.wfd = tfd;
		cf.wname = file;
D 5
		copyfile(&cf, chdr.size);
E 5
I 5
		copy_ar(&cf, chdr.size);
E 5

		if (fchmod(tfd, (short)chdr.mode)) {
D 7
			(void)fprintf(stderr, "ar: %s: chmod: %s\n",
			    file, strerror(errno));
E 7
I 7
			warn("chmod: %s", file);
E 7
			eval = 1;
		}
		if (options & AR_O) {
			tv[0].tv_sec = tv[1].tv_sec = chdr.date;
			if (utimes(file, tv)) {
D 7
				(void)fprintf(stderr, "ar: %s: utimes: %s\n",
				    file, strerror(errno));
E 7
I 7
				warn("utimes: %s", file);
E 7
				eval = 1;
			}
		}
		(void)close(tfd);
		if (!all && !*argv)
			break;
	}
D 4
	ORPHANS;
E 4
	close_archive(afd);
D 4
	return(eval);
E 4
I 4

	if (*argv) {
		orphans(argv);
D 7
		return(1);
E 7
I 7
		return (1);
E 7
	}
D 7
	return(0);
E 7
I 7
	return (0);
E 7
E 4
}	
E 1
