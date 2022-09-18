h25297
s 00003/00001/00149
d D 8.4 95/04/27 16:33:20 bostic 12 11
c file descriptor leak
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00001/00001/00149
d D 8.3 94/04/02 10:04:13 pendry 11 10
c add 1994 copyright
e
s 00017/00024/00133
d D 8.2 94/04/01 04:59:46 pendry 10 9
c prettyness police
e
s 00002/00002/00155
d D 8.1 93/06/06 14:19:48 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00155
d D 5.8 91/03/15 15:41:11 bostic 8 7
c err not getting set early enough
e
s 00008/00008/00148
d D 5.7 91/03/12 09:07:45 bostic 7 6
c make archive routine naming consistent
e
s 00003/00001/00153
d D 5.6 91/03/11 21:19:14 bostic 6 5
c files() bug fix; add externals, minor cleanups
e
s 00004/00004/00150
d D 5.5 91/03/11 14:31:22 bostic 5 4
c change so that the command line file name is used for error/info messages
e
s 00012/00012/00142
d D 5.4 91/03/10 15:38:01 bostic 4 3
c SKIP -> skipobj, cleanup, get padding and archive creation right
e
s 00001/00001/00153
d D 5.3 91/01/21 00:43:06 torek 3 2
c temporary files are already padded: do not pad them again
e
s 00003/00003/00151
d D 5.2 91/01/18 18:31:28 bostic 2 1
c the position of new files depends on the [-abi] flags
e
s 00154/00000/00000
d D 5.1 91/01/17 18:24:03 bostic 1 0
c date and time created 91/01/17 18:24:03 by bostic
e
u
U
t
T
I 1
/*-
D 9
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
D 11
 * Copyright (c) 1990, 1993
E 11
I 11
 * Copyright (c) 1990, 1993, 1994
E 11
 *	The Regents of the University of California.  All rights reserved.
E 9
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
D 4
#include <sys/errno.h>
E 4
D 10
#include <fcntl.h>
D 4
#include <unistd.h>
E 4
#include <dirent.h>
I 4
#include <errno.h>
#include <unistd.h>
E 10
I 10

E 10
E 4
#include <ar.h>
I 10
#include <dirent.h>
#include <err.h>
#include <fcntl.h>
E 10
#include <stdio.h>
I 6
#include <string.h>
I 10
#include <unistd.h>

E 10
E 6
#include "archive.h"
I 6
#include "extern.h"
E 6

D 10
extern CHDR chdr;			/* converted header */
extern char *archive;			/* archive name */
extern char *tname;                     /* temporary file "name" */

E 10
/*
 * replace --
 *	Replace or add named members to archive.  Entries already in the
 *	archive are swapped in place.  Others are added before or after 
 *	the key entry, based on the a, b and i options.  If the u option
 *	is specified, modification dates select for replacement.
 */
I 10
int
E 10
replace(argv)
	char **argv;
{
D 5
	extern char *posname;		/* positioning file name */
E 5
I 5
D 10
	extern char *posarg, *posname;	/* positioning file name */
E 5
	register char *file;
	register int afd, curfd, mods, sfd;
E 10
I 10
	char *file;
	int afd, curfd, errflg, exists, mods, sfd, tfd1, tfd2;
E 10
	struct stat sb;
	CF cf;
	off_t size, tsize;
D 10
	int err, exists, tfd1, tfd2;
	char *rname();
E 10

I 8
D 10
	err = 0;
E 10
I 10
	errflg = 0;
E 10
E 8
	/*
	 * If doesn't exist, simply append to the archive.  There's
	 * a race here, but it's pretty short, and not worth fixing.
	 */
	exists = !stat(archive, &sb);
	afd = open_archive(O_CREAT|O_RDWR);

	if (!exists) {
		tfd1 = -1;
		tfd2 = tmp();
		goto append;
	} 

	tfd1 = tmp();			/* Files before key file. */
	tfd2 = tmp();			/* Files after key file. */
D 2
	
	mods = (options & (AR_A|AR_B));
E 2

	/*
	 * Break archive into two parts -- entries before and after the key
	 * entry.  If positioning before the key, place the key at the
	 * beginning of the after key entries and if positioning after the
	 * key, place the key at the end of the before key entries.  Put it
	 * all back together at the end.
	 */
I 2
	mods = (options & (AR_A|AR_B));
E 2
D 7
	for (err = 0, curfd = tfd1; get_header(afd);) {
E 7
I 7
D 8
	for (err = 0, curfd = tfd1; get_arobj(afd);) {
E 8
I 8
	for (curfd = tfd1; get_arobj(afd);) {
E 8
E 7
D 6
		if ((file = *argv) && files(argv)) {
E 6
I 6
		if (*argv && (file = files(argv))) {
E 6
			if ((sfd = open(file, O_RDONLY)) < 0) {
D 10
				err = 1;
				(void)fprintf(stderr, "ar: %s: %s.\n",
				    file, strerror(errno));
E 10
I 10
				errflg = 1;
				warn("%s", file);
E 10
				goto useold;
			}
			(void)fstat(sfd, &sb);
D 12
			if (options & AR_U && sb.st_mtime <= chdr.date)
E 12
I 12
			if (options & AR_U && sb.st_mtime <= chdr.date) {
				(void)close(sfd);
E 12
				goto useold;
I 12
			}
E 12

			if (options & AR_V)
D 5
			     (void)printf("r - %s\n", chdr.name);
E 5
I 5
			     (void)printf("r - %s\n", file);
E 5

I 4
			/* Read from disk, write to an archive; pad on write */
E 4
			SETCF(sfd, file, curfd, tname, WPAD);
D 4
			put_header(&cf, &sb);
			copyfile(&cf, sb.st_size);
E 4
I 4
D 7
			put_object(&cf, &sb);
E 7
I 7
			put_arobj(&cf, &sb);
E 7
E 4
			(void)close(sfd);
D 4
			SKIP(afd, chdr.size, archive);
E 4
I 4
D 7
			skipobj(afd);
E 7
I 7
			skip_arobj(afd);
E 7
E 4
			continue;
		}

		if (mods && compare(posname)) {
			mods = 0;
			if (options & AR_B)
				curfd = tfd2;
I 4
			/* Read and write to an archive; pad on both. */
E 4
			SETCF(afd, archive, curfd, tname, RPAD|WPAD);
D 4
			put_header(&cf, (struct stat *)NULL);
			copyfile(&cf, chdr.size);
E 4
I 4
D 7
			put_object(&cf, (struct stat *)NULL);
E 7
I 7
			put_arobj(&cf, (struct stat *)NULL);
E 7
E 4
			if (options & AR_A)
				curfd = tfd2;
		} else {
I 4
			/* Read and write to an archive; pad on both. */
E 4
useold:			SETCF(afd, archive, curfd, tname, RPAD|WPAD);
D 4
			put_header(&cf, (struct stat *)NULL);
			copyfile(&cf, chdr.size);
E 4
I 4
D 7
			put_object(&cf, (struct stat *)NULL);
E 7
I 7
			put_arobj(&cf, (struct stat *)NULL);
E 7
E 4
		}
	}

	if (mods) {
D 10
		(void)fprintf(stderr, "ar: %s: archive member not found.\n",
D 5
		    posname);
E 5
I 5
		    posarg);
E 10
I 10
		warnx("%s: archive member not found", posarg);
E 10
E 5
                close_archive(afd);
D 10
                return(1);
E 10
I 10
                return (1);
E 10
        }

	/* Append any left-over arguments to the end of the after file. */
append:	while (file = *argv++) {
		if (options & AR_V)
D 5
			(void)printf("a - %s\n", rname(file));
E 5
I 5
			(void)printf("a - %s\n", file);
E 5
		if ((sfd = open(file, O_RDONLY)) < 0) {
D 10
			err = 1;
			(void)fprintf(stderr, "ar: %s: %s.\n",
			    file, strerror(errno));
E 10
I 10
			errflg = 1;
			warn("%s", file);
E 10
			continue;
		}
		(void)fstat(sfd, &sb);
I 4
		/* Read from disk, write to an archive; pad on write. */
E 4
D 2
		SETCF(sfd, file, tfd2, tname, WPAD);
E 2
I 2
		SETCF(sfd, file,
		    options & (AR_A|AR_B) ? tfd1 : tfd2, tname, WPAD);
E 2
D 4
		put_header(&cf, &sb);
		copyfile(&cf, sb.st_size);
E 4
I 4
D 7
		put_object(&cf, &sb);
E 7
I 7
		put_arobj(&cf, &sb);
E 7
E 4
		(void)close(sfd);
	}
	
	(void)lseek(afd, (off_t)SARMAG, SEEK_SET);

D 3
	SETCF(tfd1, tname, afd, archive, RPAD|WPAD);
E 3
I 3
D 4
	SETCF(tfd1, tname, afd, archive, 0);
E 4
I 4
	SETCF(tfd1, tname, afd, archive, NOPAD);
E 4
E 3
	if (tfd1 != -1) {
		tsize = size = lseek(tfd1, (off_t)0, SEEK_CUR);
		(void)lseek(tfd1, (off_t)0, SEEK_SET);
D 7
		copyfile(&cf, size);
E 7
I 7
		copy_ar(&cf, size);
E 7
	} else
		tsize = 0;

	tsize += size = lseek(tfd2, (off_t)0, SEEK_CUR);
	(void)lseek(tfd2, (off_t)0, SEEK_SET);
	cf.rfd = tfd2;
D 7
	copyfile(&cf, size);
E 7
I 7
	copy_ar(&cf, size);
E 7

	(void)ftruncate(afd, tsize + SARMAG);
	close_archive(afd);
D 10
	return(err);
E 10
I 10
	return (errflg);
E 10
}	
E 1
