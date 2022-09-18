h04560
s 00009/00001/00230
d D 8.8 95/05/01 16:11:28 mckusick 29 28
c POSIX.1, section 5.1.2.4 states that NULL is to be returned from
c opendir() and errno is to be set to ENOTDIR if "A component of dirname
c is not a directory".  This requires the file descriptor to be stat'd
c to ensure that it is a directory. (from J.T. Conklin)
e
s 00004/00002/00227
d D 8.7 94/12/10 12:55:07 pendry 28 27
c don't run off end of union read-ahead buffer
e
s 00001/00001/00228
d D 8.6 94/08/14 21:17:18 mckusick 27 26
c DT_WHTD is gone
e
s 00053/00021/00176
d D 8.5 94/07/28 03:38:30 pendry 26 25
c changes for whiteouts and union filesystem
e
s 00002/00003/00195
d D 8.4 94/06/15 04:06:47 pendry 25 24
c use a stable sort funciton (mergesort).
e
s 00157/00020/00041
d D 8.3 94/05/07 14:25:26 mckusick 24 23
c merge in opendir that understands union mounts
e
s 00001/00000/00060
d D 8.2 94/02/12 08:47:12 bostic 23 22
c typo
e
s 00002/00002/00058
d D 8.1 93/06/08 17:57:26 bostic 22 21
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00003/00059
d D 5.14 93/06/08 17:45:59 mckusick 21 19
c global _rewinddir moves to structure dd_rewind
e
s 00002/00002/00060
d R 8.1 93/06/04 12:04:09 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00061
d D 5.13 93/02/04 18:47:56 ralph 19 18
c use symbolic constant FD_CLOEXEC.
e
s 00004/00004/00058
d D 5.12 92/03/14 13:54:29 ralph 18 17
c change CLSIZE to CLBYTES so the code will work (CLSIZE is # pages).
e
s 00003/00002/00059
d D 5.11 91/02/23 19:49:55 donn 17 16
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00060
d D 5.10 90/06/01 14:12:43 bostic 16 15
c new copyright notice
e
s 00000/00001/00071
d D 5.9 90/03/20 17:00:26 bostic 15 14
c lint fix
e
s 00005/00000/00067
d D 5.8 90/01/30 17:00:44 mckusick 14 13
c set up seek pointer for telldir
e
s 00003/00001/00064
d D 5.7 89/08/17 14:52:58 mckusick 13 12
c POSIX requires file descriptor to be close-on-exec
e
s 00000/00003/00065
d D 5.6 89/07/11 17:47:29 mckusick 12 11
c update for global telldir list
e
s 00024/00000/00044
d D 5.5 89/07/10 15:15:48 mckusick 11 10
c update to use getdirentries
e
s 00001/00001/00043
d D 5.4 89/01/11 16:44:39 mckusick 10 9
c modifications to use POSIX defined <dirent.h>
e
s 00014/00003/00030
d D 5.3 88/06/18 15:12:23 bostic 9 8
c install approved copyright notice
e
s 00002/00002/00031
d D 5.2 86/03/09 19:51:54 donn 8 7
c added LIBC_SCCS condition for sccs ids
e
s 00007/00001/00026
d D 5.1 85/05/30 10:47:02 dist 7 6
c Add copyright
e
s 00004/00004/00023
d D 4.5 83/07/01 18:32:40 sam 6 5
c include fixes
e
s 00003/00007/00024
d D 4.4 82/11/12 19:48:19 mckusick 5 4
c get rid of check for directory
e
s 00007/00008/00024
d D 4.3 82/08/04 22:39:18 mckusick 4 3
c open file before allocating buffer as per Ken Greer (hplabs!kg) suggestion
e
s 00008/00001/00024
d D 4.2 82/03/10 23:46:50 mckusic 3 2
c check that requested file is actually a directory
e
s 00000/00000/00025
d D 4.1 82/02/21 14:49:08 mckusic 2 1
c convert to version number 4.x
e
s 00025/00000/00000
d D 1.1 82/02/11 12:01:17 mckusick 1 0
c date and time created 82/02/11 12:01:17 by mckusick
e
u
U
t
T
I 7
/*
D 22
 * Copyright (c) 1983 Regents of the University of California.
D 9
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
 * All rights reserved.
E 22
I 22
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 22
 *
D 16
 * Redistribution and use in source and binary forms are permitted
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
E 16
I 16
 * %sccs.include.redist.c%
E 16
E 9
 */

E 7
I 1
D 6
/* Copyright (c) 1982 Regents of the University of California */
E 6
I 6
D 8
#ifndef lint
E 8
I 8
#if defined(LIBC_SCCS) && !defined(lint)
E 8
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif
E 7
I 7
D 8
#endif not lint
E 8
I 8
D 9
#endif LIBC_SCCS and not lint
E 9
I 9
#endif /* LIBC_SCCS and not lint */
E 9
E 8
E 7
E 6

D 6
static char sccsid[] = "%Z%%M% %I% %G%";

E 6
D 5
#include <sys/types.h>
I 3
#include <sys/stat.h>
E 3
#include <ndir.h>
E 5
I 5
#include <sys/param.h>
I 24
#include <sys/mount.h>
I 29
#include <sys/stat.h>
E 29
E 24
I 23

E 23
D 6
#include <dir.h>
E 6
I 6
D 10
#include <sys/dir.h>
E 10
I 10
#include <dirent.h>
I 29
#include <errno.h>
E 29
I 13
#include <fcntl.h>
I 17
#include <stdlib.h>
#include <unistd.h>
E 17
E 13
E 10
E 6
E 5

I 11
D 17
char *malloc();
E 17
I 14
D 21
long _rewinddir;
E 14

E 21
E 11
/*
D 24
 * open a directory.
E 24
I 24
 * Open a directory.
E 24
 */
DIR *
opendir(name)
D 17
	char *name;
E 17
I 17
	const char *name;
E 17
{
I 26

	return (__opendir2(name, DTF_HIDEW|DTF_NODUP));
}

DIR *
__opendir2(name, flags)
	const char *name;
	int flags;
{
E 26
D 3
	DIR *dirp;
E 3
I 3
D 24
	register DIR *dirp;
I 4
	register int fd;
E 24
I 24
	DIR *dirp;
	int fd;
	int incr;
D 26
	struct statfs sfb;
E 26
I 26
	int unionstack;
I 29
	struct stat statb;
E 29
E 26
E 24
I 11
D 15
	register int i;
E 15
E 11
E 4
D 5
	struct stat sbuf;
E 5
E 3

D 4
	dirp = (DIR *)malloc(sizeof(DIR));
	dirp->dd_fd = open(name, 0);
	if (dirp->dd_fd == -1) {
I 3
		free(dirp);
E 4
I 4
D 26
	if ((fd = open(name, 0)) == -1)
E 26
I 26
	if ((fd = open(name, O_RDONLY)) == -1)
E 26
E 4
D 24
		return NULL;
E 24
I 24
		return (NULL);
I 29
	if (fstat(fd, &statb) || !S_ISDIR(statb.st_mode)) {
		errno = ENOTDIR;
		close(fd);
		return (NULL);
	}
E 29
E 24
D 4
	}
	fstat(dirp->dd_fd, &sbuf);
	if ((sbuf.st_mode & S_IFDIR) == 0) {
E 3
		free(dirp);
E 4
I 4
D 5
	fstat(fd, &sbuf);
	if (((sbuf.st_mode & S_IFDIR) == 0) ||
	    ((dirp = (DIR *)malloc(sizeof(DIR))) == NULL)) {
E 5
I 5
D 13
	if ((dirp = (DIR *)malloc(sizeof(DIR))) == NULL) {
E 13
I 13
D 19
	if (fcntl(fd, F_SETFD, 1) == -1 ||
E 19
I 19
	if (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1 ||
E 19
	    (dirp = (DIR *)malloc(sizeof(DIR))) == NULL) {
E 13
E 5
D 24
		close (fd);
E 4
		return NULL;
E 24
I 24
		close(fd);
		return (NULL);
E 24
	}
I 24

E 24
I 11
	/*
D 18
	 * If CLSIZE is an exact multiple of DIRBLKSIZ, use a CLSIZE
E 18
I 18
	 * If CLBYTES is an exact multiple of DIRBLKSIZ, use a CLBYTES
E 18
	 * buffer that it cluster boundary aligned.
D 24
	 * Hopefully this can be a big win someday by allowing page trades
	 * to user space to be done by getdirentries()
E 24
I 24
	 * Hopefully this can be a big win someday by allowing page
	 * trades to user space to be done by getdirentries()
E 24
	 */
D 18
	if ((CLSIZE % DIRBLKSIZ) == 0) {
		dirp->dd_buf = malloc(CLSIZE);
		dirp->dd_len = CLSIZE;
E 18
I 18
D 24
	if ((CLBYTES % DIRBLKSIZ) == 0) {
		dirp->dd_buf = malloc(CLBYTES);
		dirp->dd_len = CLBYTES;
E 18
	} else {
		dirp->dd_buf = malloc(DIRBLKSIZ);
		dirp->dd_len = DIRBLKSIZ;
E 24
I 24
	if ((CLBYTES % DIRBLKSIZ) == 0)
		incr = CLBYTES;
	else
		incr = DIRBLKSIZ;

D 26
#ifdef MOUNT_UNION
E 26
	/*
	 * Determine whether this directory is the top of a union stack.
	 */
D 26
	if (fstatfs(fd, &sfb) < 0) {
		free(dirp);
		close(fd);
		return (NULL);
E 26
I 26
	if (flags & DTF_NODUP) {
		struct statfs sfb;

		if (fstatfs(fd, &sfb) < 0) {
			free(dirp);
			close(fd);
			return (NULL);
		}
D 29
		unionstack = (sfb.f_type == MOUNT_UNION);
E 29
I 29
		unionstack = !strcmp(sfb.f_fstypename, "union");
E 29
	} else {
		unionstack = 0;
E 26
E 24
	}
D 24
	if (dirp->dd_buf == NULL) {
		close (fd);
		return NULL;
E 24
I 24

D 26
	if (sfb.f_type == MOUNT_UNION) {
E 26
I 26
	if (unionstack) {
E 26
		int len = 0;
		int space = 0;
		char *buf = 0;
		char *ddptr = 0;
I 28
		char *ddeptr;
E 28
		int n;
		struct dirent **dpv;

		/*
		 * The strategy here is to read all the directory
		 * entries into a buffer, sort the buffer, and
		 * remove duplicate entries by setting the inode
		 * number to zero.
		 */

D 26
		/*
		 * Fixup dd_loc to be non-zero to fake out readdir
		 */
		dirp->dd_loc = sizeof(void *);

E 26
		do {
			/*
			 * Always make at least DIRBLKSIZ bytes
			 * available to getdirentries
			 */
			if (space < DIRBLKSIZ) {
				space += incr;
				len += incr;
				buf = realloc(buf, len);
				if (buf == NULL) {
					free(dirp);
					close(fd);
					return (NULL);
				}
D 26
				ddptr = buf + (len - space) + dirp->dd_loc;
E 26
I 26
				ddptr = buf + (len - space);
E 26
			}

			n = getdirentries(fd, ddptr, space, &dirp->dd_seek);
			if (n > 0) {
				ddptr += n;
				space -= n;
			}
		} while (n > 0);

I 28
		ddeptr = ddptr;
E 28
I 26
		flags |= __DTF_READALL;

E 26
		/*
I 26
		 * Re-open the directory.
		 * This has the effect of rewinding back to the
		 * top of the union stack and is needed by
		 * programs which plan to fchdir to a descriptor
		 * which has also been read -- see fts.c.
		 */
		if (flags & DTF_REWIND) {
			(void) close(fd);
			if ((fd = open(name, O_RDONLY)) == -1) {
				free(buf);
				free(dirp);
				return (NULL);
			}
		}

		/*
E 26
		 * There is now a buffer full of (possibly) duplicate
		 * names.
		 */
		dirp->dd_buf = buf;

		/*
		 * Go round this loop twice...
		 *
		 * Scan through the buffer, counting entries.
		 * On the second pass, save pointers to each one.
		 * Then sort the pointers and remove duplicate names.
		 */
		for (dpv = 0;;) {
			n = 0;
D 26
			ddptr = buf + dirp->dd_loc;
E 26
I 26
			ddptr = buf;
E 26
D 28
			while (ddptr < buf + len) {
E 28
I 28
			while (ddptr < ddeptr) {
E 28
				struct dirent *dp;

				dp = (struct dirent *) ddptr;
				if ((int)dp & 03)
					break;
				if ((dp->d_reclen <= 0) ||
D 28
				    (dp->d_reclen > (buf + len + 1 - ddptr)))
E 28
I 28
				    (dp->d_reclen > (ddeptr + 1 - ddptr)))
E 28
					break;
				ddptr += dp->d_reclen;
				if (dp->d_fileno) {
					if (dpv)
						dpv[n] = dp;
					n++;
				}
			}

			if (dpv) {
				struct dirent *xp;

				/*
D 25
				 * If and when whiteouts happen,
				 * this sort would need to be stable.
E 25
I 25
				 * This sort must be stable.
E 25
				 */
D 25
				heapsort(dpv, n, sizeof(*dpv), alphasort);
E 25
I 25
				mergesort(dpv, n, sizeof(*dpv), alphasort);
E 25

				dpv[n] = NULL;
				xp = NULL;

				/*
				 * Scan through the buffer in sort order,
				 * zapping the inode number of any
				 * duplicate names.
				 */
				for (n = 0; dpv[n]; n++) {
					struct dirent *dp = dpv[n];

					if ((xp == NULL) ||
D 26
					    strcmp(dp->d_name, xp->d_name))
E 26
I 26
					    strcmp(dp->d_name, xp->d_name)) {
E 26
						xp = dp;
D 26
					else
E 26
I 26
					} else {
E 26
						dp->d_fileno = 0;
I 26
					}
D 27
					if (DT_ISWHT(dp->d_type) &&
E 27
I 27
					if (dp->d_type == DT_WHT &&
E 27
					    (flags & DTF_HIDEW))
						dp->d_fileno = 0;
E 26
				}

				free(dpv);
				break;
			} else {
				dpv = malloc((n+1) * sizeof(struct dirent *));
				if (dpv == NULL)
					break;
			}
		}

		dirp->dd_len = len;
		dirp->dd_size = ddptr - dirp->dd_buf;
D 26
	} else
#endif /* MOUNT_UNION */
	{
E 26
I 26
	} else {
E 26
		dirp->dd_len = incr;
		dirp->dd_buf = malloc(dirp->dd_len);
		if (dirp->dd_buf == NULL) {
			free(dirp);
			close (fd);
			return (NULL);
		}
		dirp->dd_seek = 0;
D 26
		dirp->dd_loc = 0;
E 26
I 26
		flags &= ~DTF_REWIND;
E 26
E 24
	}
I 24

I 26
	dirp->dd_loc = 0;
E 26
E 24
E 11
I 4
	dirp->dd_fd = fd;
I 26
	dirp->dd_flags = flags;
E 26
E 4
D 24
	dirp->dd_loc = 0;
I 11
	dirp->dd_seek = 0;
E 24
I 24

E 24
I 14
	/*
	 * Set up seek point for rewinddir.
	 */
D 21
	_rewinddir = telldir(dirp);
E 21
I 21
	dirp->dd_rewind = telldir(dirp);
E 21
E 14
D 12
	dirp->dd_loccnt = 1;
	for (i = 0; i < NDIRHASH; i++)
		dirp->dd_hash[i] = NULL;
E 12
E 11
D 24
	return dirp;
E 24
I 24

	return (dirp);
E 24
}
E 1
