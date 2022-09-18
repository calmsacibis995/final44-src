h15971
s 00001/00001/00113
d D 8.3 94/04/02 10:04:05 pendry 9 8
c add 1994 copyright
e
s 00011/00013/00103
d D 8.2 94/04/01 04:59:41 pendry 8 7
c prettyness police
e
s 00002/00002/00114
d D 8.1 93/06/06 14:19:38 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00007/00109
d D 5.6 91/03/12 09:07:43 bostic 6 5
c make archive routine naming consistent
e
s 00009/00006/00107
d D 5.5 91/03/11 21:18:39 bostic 5 4
c make ORPHANS a function; files() bug fix
c add externals, minor cleanups
e
s 00005/00004/00108
d D 5.4 91/03/11 14:31:20 bostic 4 3
c change so that the command line file name is used for error/info messages
e
s 00007/00008/00105
d D 5.3 91/03/10 15:37:15 bostic 3 2
c cleanup, get padding and archive creation right
e
s 00001/00000/00112
d D 5.2 91/01/21 00:41:24 torek 2 1
c the ORPHANS macro sets eval on error, but does not clear it on success,
c so we must clear it before invoking ORPHANS lest we return a random value
e
s 00112/00000/00000
d D 5.1 91/01/17 18:23:57 bostic 1 0
c date and time created 91/01/17 18:23:57 by bostic
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
D 3
#include <unistd.h>
E 3
#include <dirent.h>
I 3
D 8
#include <unistd.h>
E 8
I 8
#include <err.h>
#include <fcntl.h>
E 8
E 3
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
/*
 * move --
 *	Change location of named members in archive - if 'b' or 'i' option
 *	selected then named members are placed before 'posname'.  If 'a'
 *	option selected members go after 'posname'.  If no options, members
 *	are moved to end of archive.
 */
I 8
int
E 8
move(argv)
	char **argv;
{
D 4
	extern char *posname;		/* positioning file name */
E 4
I 4
D 8
	extern char *posarg, *posname;	/* positioning file names */
E 8
E 4
	CF cf;
	off_t size, tsize;
D 5
	int afd, curfd, eval, mods, tfd1, tfd2, tfd3;
E 5
I 5
	int afd, curfd, mods, tfd1, tfd2, tfd3;
E 5
I 4
	char *file;
E 4

	afd = open_archive(O_RDWR);
	mods = options & (AR_A|AR_B);

	tfd1 = tmp();			/* Files before key file. */
	tfd2 = tmp();			/* Files selected by user. */
	tfd3 = tmp();			/* Files after key file. */

	/*
	 * Break archive into three parts -- selected entries and entries
	 * before and after the key entry.  If positioning before the key,
	 * place the key at the beginning of the after key entries and if
	 * positioning after the key, place the key at the end of the before
	 * key entries.  Put it all back together at the end.
	 */
I 3

	/* Read and write to an archive; pad on both. */
E 3
	SETCF(afd, archive, 0, tname, RPAD|WPAD);
D 6
	for (curfd = tfd1; get_header(afd);) {	
E 6
I 6
	for (curfd = tfd1; get_arobj(afd);) {	
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
				(void)printf("m - %s\n", chdr.name);
E 4
I 4
				(void)printf("m - %s\n", file);
E 4
			cf.wfd = tfd2;
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
			continue;
		}
		if (mods && compare(posname)) {
			mods = 0;
			if (options & AR_B)
				curfd = tfd3;
			cf.wfd = curfd;
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
			if (options & AR_A)
				curfd = tfd3;
		} else {
			cf.wfd = curfd;
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
	}

	if (mods) {
D 8
		(void)fprintf(stderr, "ar: %s: archive member not found.\n",
D 4
		    posname);
E 4
I 4
		    posarg);
E 8
I 8
		warnx("%s: archive member not found", posarg);
E 8
E 4
		close_archive(afd);
D 8
		return(1);
E 8
I 8
		return (1);
E 8
	}
	(void)lseek(afd, (off_t)SARMAG, SEEK_SET);

I 2
D 5
	eval = 0;
E 2
	ORPHANS;

E 5
D 3
	SETCF(tfd1, tname, afd, archive, RPAD|WPAD);
E 3
I 3
	SETCF(tfd1, tname, afd, archive, NOPAD);
E 3
	tsize = size = lseek(tfd1, (off_t)0, SEEK_CUR);
	(void)lseek(tfd1, (off_t)0, SEEK_SET);
D 6
	copyfile(&cf, size);
E 6
I 6
	copy_ar(&cf, size);
E 6

	tsize += size = lseek(tfd2, (off_t)0, SEEK_CUR);
	(void)lseek(tfd2, (off_t)0, SEEK_SET);
	cf.rfd = tfd2;
D 6
	copyfile(&cf, size);
E 6
I 6
	copy_ar(&cf, size);
E 6

	tsize += size = lseek(tfd3, (off_t)0, SEEK_CUR);
	(void)lseek(tfd3, (off_t)0, SEEK_SET);
	cf.rfd = tfd3;
D 6
	copyfile(&cf, size);
E 6
I 6
	copy_ar(&cf, size);
E 6

	(void)ftruncate(afd, tsize + SARMAG);
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
