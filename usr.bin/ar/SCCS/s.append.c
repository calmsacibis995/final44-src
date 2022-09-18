h19777
s 00001/00001/00062
d D 8.3 94/04/02 10:03:26 pendry 9 8
c add 1994 copyright
e
s 00009/00010/00054
d D 8.2 94/04/01 04:59:44 pendry 8 7
c prettyness police
e
s 00002/00002/00062
d D 8.1 93/06/06 14:18:47 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00060
d D 5.6 91/03/12 09:54:02 bostic 6 5
c exit status cleanup
e
s 00001/00001/00063
d D 5.5 91/03/12 09:07:36 bostic 5 4
c make archive routine naming consistent
e
s 00002/00001/00062
d D 5.4 91/03/11 21:15:01 bostic 4 3
c add externals, minor cleanups
e
s 00001/00001/00062
d D 5.3 91/03/11 14:31:14 bostic 3 2
c change so that the command line file name is used for error/info messages
e
s 00002/00002/00061
d D 5.2 91/03/10 15:34:43 bostic 2 1
c cleanup, get padding and archive creation right
e
s 00063/00000/00000
d D 5.1 91/01/17 18:16:40 bostic 1 0
c date and time created 91/01/17 18:16:40 by bostic
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
#include <sys/stat.h>
D 8
#include <sys/errno.h>
E 8
I 8

#include <err.h>
E 8
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
I 4
#include <string.h>
I 8

E 8
E 4
#include "archive.h"
I 4
#include "extern.h"
E 4

D 8
extern char *archive;			/* archive name */

E 8
/*
 * append --
 *	Append files to the archive - modifies original archive or creates
 *	a new archive if named archive does not exist.
 */
I 8
int
E 8
append(argv)
	char **argv;
{
D 8
	register int fd, afd;
	register char *file;
	struct stat sb;
E 8
I 8
	int afd, fd, eval;
	char *file;
E 8
	CF cf;
D 6
	int rval;
E 6
I 6
D 8
	int eval;
E 8
I 8
	struct stat sb;
E 8
E 6
D 4
	char *rname();
E 4

	afd = open_archive(O_CREAT|O_RDWR);
	if (lseek(afd, (off_t)0, SEEK_END) == (off_t)-1)
		error(archive);

I 2
	/* Read from disk, write to an archive; pad on write. */
E 2
	SETCF(0, 0, afd, archive, WPAD);
D 6
	while (file = *argv++) {
E 6
I 6
	for (eval = 0; file = *argv++;) {
E 6
		if ((fd = open(file, O_RDONLY)) < 0) {
D 8
			(void)fprintf(stderr,
			    "ar: %s: %s.\n", file, strerror(errno));
E 8
I 8
			warn("%s", file);
E 8
D 6
			rval = 1;
E 6
I 6
			eval = 1;
E 6
			continue;
		}
		if (options & AR_V)
D 3
			(void)printf("q - %s\n", rname(file));
E 3
I 3
			(void)printf("q - %s\n", file);
E 3
		cf.rfd = fd;
		cf.rname = file;
D 2
		put_header(&cf, &sb);
		copyfile(&cf, sb.st_size);
E 2
I 2
D 5
		put_object(&cf, &sb);
E 5
I 5
		put_arobj(&cf, &sb);
E 5
E 2
		(void)close(fd);
	}
	close_archive(afd);
D 6
	return(rval);	
E 6
I 6
D 8
	return(eval);	
E 8
I 8
	return (eval);	
E 8
E 6
}
E 1
