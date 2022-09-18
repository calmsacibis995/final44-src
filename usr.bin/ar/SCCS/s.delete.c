h02041
s 00001/00001/00069
d D 8.3 94/04/02 10:03:48 pendry 9 8
c add 1994 copyright
e
s 00009/00010/00061
d D 8.2 94/04/01 04:59:42 pendry 8 7
c prettyness police
e
s 00002/00002/00069
d D 8.1 93/06/06 14:19:20 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00067
d D 5.6 91/03/12 09:07:40 bostic 6 5
c make archive routine naming consistent
e
s 00010/00006/00061
d D 5.5 91/03/11 21:17:06 bostic 5 4
c make ORPHANS a subroutine; files() bugfix
c add externals, minor cleanups
e
s 00003/00002/00064
d D 5.4 91/03/11 14:31:18 bostic 4 3
c change so that the command line file name is used for error/info messages
e
s 00004/00004/00062
d D 5.3 91/03/10 15:36:46 bostic 3 2
c SKIP -> skipobj, cleanup, get padding and archive creation right
e
s 00001/00000/00065
d D 5.2 91/01/21 00:41:23 torek 2 1
c the ORPHANS macro sets eval on error, but does not clear it on success,
c so we must clear it before invoking ORPHANS lest we return a random value
e
s 00065/00000/00000
d D 5.1 91/01/17 18:23:43 bostic 1 0
c date and time created 91/01/17 18:23:43 by bostic
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
#include <fcntl.h>
E 8
I 8

#include <ar.h>
E 8
D 5
#include <unistd.h>
E 5
#include <dirent.h>
I 5
D 8
#include <unistd.h>
E 8
I 8
#include <fcntl.h>
E 8
E 5
#include <stdio.h>
D 8
#include <ar.h>
E 8
I 8
#include <unistd.h>

E 8
#include "archive.h"
I 5
#include "extern.h"
E 5
#include "pathnames.h"

D 8
extern CHDR chdr;			/* converted header */
extern char *archive;			/* archive name */
extern char *tname;                     /* temporary file "name" */

E 8
/*-
 * delete --
 *	Deletes named members from the archive.
 */
I 8
int
E 8
delete(argv)
D 8
	register char **argv;
E 8
I 8
	char **argv;
E 8
{
	CF cf;
	off_t size;
D 5
	int afd, eval, tfd;
E 5
I 5
	int afd, tfd;
E 5
I 4
	char *file;
E 4

	afd = open_archive(O_RDWR);
	tfd = tmp();

I 3
	/* Read and write to an archive; pad on both. */
E 3
	SETCF(afd, archive, tfd, tname, RPAD|WPAD);
D 6
	while (get_header(afd)) {
E 6
I 6
	while (get_arobj(afd)) {
E 6
D 4
		if (*argv && files(argv)) {
E 4
I 4
D 5
		if ((file = *argv) && files(argv)) {
E 5
I 5
		if (*argv && (file = files(argv))) {
E 5
E 4
			if (options & AR_V)
D 4
				(void)printf("d - %s\n", chdr.name);
E 4
I 4
				(void)printf("d - %s\n", file);
E 4
D 3
			SKIP(afd, chdr.size, archive);
E 3
I 3
D 6
			skipobj(afd);
E 6
I 6
			skip_arobj(afd);
E 6
E 3
			continue;
		}
D 3
		put_header(&cf, (struct stat *)NULL);
		copyfile(&cf, chdr.size);
E 3
I 3
D 6
		put_object(&cf, (struct stat *)NULL);
E 6
I 6
		put_arobj(&cf, (struct stat *)NULL);
E 6
E 3
	}
I 2
D 5
	eval = 0;
E 2
	ORPHANS;
E 5

	size = lseek(tfd, (off_t)0, SEEK_CUR);
	(void)lseek(tfd, (off_t)0, SEEK_SET);
	(void)lseek(afd, (off_t)SARMAG, SEEK_SET);
D 3
	SETCF(tfd, tname, afd, archive, RPAD|WPAD);
E 3
I 3
	SETCF(tfd, tname, afd, archive, NOPAD);
E 3
D 6
	copyfile(&cf, size);
E 6
I 6
	copy_ar(&cf, size);
E 6
	(void)close(tfd);
	(void)ftruncate(afd, size + SARMAG);
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
