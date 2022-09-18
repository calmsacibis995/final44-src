h52877
s 00003/00002/00297
d D 8.4 95/04/27 16:32:40 bostic 13 12
c warnx will add a <newline> for us
c bug in long archive member names
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00001/00001/00298
d D 8.3 94/04/02 10:03:33 pendry 12 11
c add 1994 copyright
e
s 00026/00024/00273
d D 8.2 94/04/01 04:59:45 pendry 11 10
c prettyness police
e
s 00002/00002/00295
d D 8.1 93/06/06 14:19:09 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00295
d D 5.9 92/10/24 15:16:26 ralph 9 8
c fix gcc2 warning about register char array.
e
s 00009/00007/00287
d D 5.8 92/06/19 15:15:05 bostic 8 7
c st_size is now a quad, st_mtime is now a timespec
e
s 00001/00001/00293
d D 5.7 91/03/21 12:16:01 bostic 7 6
c rename -s option to -T (Sys V. compatibility)
e
s 00009/00009/00285
d D 5.6 91/03/12 09:07:37 bostic 6 5
c make archive routine naming consistent
e
s 00008/00004/00286
d D 5.5 91/03/11 21:14:45 bostic 5 4
c add externs, minor cleanup
e
s 00012/00010/00278
d D 5.4 91/03/11 10:27:45 bostic 4 3
c get truncated names right -- it's 15 chars, not 16
e
s 00014/00002/00274
d D 5.3 91/03/10 16:26:02 bostic 3 2
c add -s option which inserts/matches truncated member names
e
s 00172/00029/00104
d D 5.2 91/03/10 15:35:44 bostic 2 1
c fold header.c routines in; add skipobj routine instead of using a macro
c cleanup, get padding and archive creation right
e
s 00133/00000/00000
d D 5.1 91/01/17 18:23:32 bostic 1 0
c date and time created 91/01/17 18:23:32 by bostic
e
u
U
t
T
I 1
/*-
D 10
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
D 12
 * Copyright (c) 1990, 1993
E 12
I 12
 * Copyright (c) 1990, 1993, 1994
E 12
 *	The Regents of the University of California.  All rights reserved.
E 10
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
D 2
#include <sys/errno.h>
E 2
#include <sys/stat.h>
D 11
#include <fcntl.h>
#include <unistd.h>
I 2
#include <errno.h>
E 2
#include <dirent.h>
E 11
I 11

E 11
D 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
E 2
#include <ar.h>
I 11
#include <dirent.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
E 11
I 2
#include <stdio.h>
I 5
#include <stdlib.h>
#include <string.h>
I 11
#include <unistd.h>

E 11
E 5
E 2
#include "archive.h"
I 5
#include "extern.h"
E 5

I 2
D 11
extern CHDR chdr;			/* converted header */
E 2
extern char *archive;			/* archive name */

E 11
I 2
typedef struct ar_hdr HDR;
static char hb[sizeof(HDR) + 1];	/* real header */

I 11
int
E 11
E 2
open_archive(mode)
	int mode;
{
	int created, fd, nr;
	char buf[SARMAG];
	
	created = 0;
	if (mode & O_CREAT) {
		mode |= O_EXCL;
		if ((fd = open(archive, mode, DEFFILEMODE)) >= 0) {
			/* POSIX.2 puts create message on stderr. */
			if (!(options & AR_C))
D 11
				(void)fprintf(stderr,
				    "ar: creating archive %s.\n", archive);
E 11
I 11
				warnx("creating archive %s", archive);
E 11
			created = 1;
			goto opened;
		}
		if (errno != EEXIST)
			error(archive);
		mode &= ~O_EXCL;
	}
	if ((fd = open(archive, mode, DEFFILEMODE)) < 0)
		error(archive);

	/* 
	 * Attempt to place a lock on the opened file - if we get an 
D 2
	 * error then someone is already working on this library.
E 2
I 2
	 * error then someone is already working on this library (or
	 * it's going across NFS).
E 2
	 */
D 2
opened:	if (flock(fd, LOCK_EX|LOCK_NB))
E 2
I 2
opened:	if (flock(fd, LOCK_EX|LOCK_NB) && errno != EOPNOTSUPP)
E 2
		error(archive);
	
	/*
	 * If not created, O_RDONLY|O_RDWR indicates that it has to be
	 * in archive format.
	 */
	if (!created &&
	    ((mode & O_ACCMODE) == O_RDONLY || (mode & O_ACCMODE) == O_RDWR)) {
		if ((nr = read(fd, buf, SARMAG) != SARMAG)) {
			if (nr >= 0)
				badfmt();
			error(archive);
		} else if (bcmp(buf, ARMAG, SARMAG))
			badfmt();
	} else if (write(fd, ARMAG, SARMAG) != SARMAG)
		error(archive);
D 11
	return(fd);
E 11
I 11
	return (fd);
E 11
}

I 5
void
E 5
close_archive(fd)
	int fd;
{
I 11

E 11
D 5
	(void)flock(fd, LOCK_UN);
	(void)close(fd);
E 5
I 5
	(void)close(fd);			/* Implicit unlock. */
E 5
}

I 2
/* Convert ar header field to an integer. */
#define	AR_ATOI(from, to, len, base) { \
D 11
	bcopy(from, buf, len); \
E 11
I 11
	memmove(buf, from, len); \
E 11
	buf[len] = '\0'; \
	to = strtol(buf, (char **)NULL, base); \
}

E 2
/*
I 2
D 6
 * get_header --
E 6
I 6
 * get_arobj --
E 6
 *	read the archive header for this member
 */
I 11
int
E 11
D 6
get_header(fd)
E 6
I 6
get_arobj(fd)
E 6
	int fd;
{
	struct ar_hdr *hdr;
D 11
	register int len, nr;
D 9
	register char *p, buf[20];
E 9
I 9
	register char *p;
	char buf[20];
E 11
I 11
	int len, nr;
	char *p, buf[20];
E 11
E 9

	nr = read(fd, hb, sizeof(HDR));
	if (nr != sizeof(HDR)) {
		if (!nr)
D 11
			return(0);
E 11
I 11
			return (0);
E 11
		if (nr < 0)
			error(archive);
		badfmt();
	}

	hdr = (struct ar_hdr *)hb;
	if (strncmp(hdr->ar_fmag, ARFMAG, sizeof(ARFMAG) - 1))
		badfmt();

	/* Convert the header into the internal format. */
#define	DECIMAL	10
#define	OCTAL	 8

	AR_ATOI(hdr->ar_date, chdr.date, sizeof(hdr->ar_date), DECIMAL);
	AR_ATOI(hdr->ar_uid, chdr.uid, sizeof(hdr->ar_uid), DECIMAL);
	AR_ATOI(hdr->ar_gid, chdr.gid, sizeof(hdr->ar_gid), DECIMAL);
	AR_ATOI(hdr->ar_mode, chdr.mode, sizeof(hdr->ar_mode), OCTAL);
	AR_ATOI(hdr->ar_size, chdr.size, sizeof(hdr->ar_size), DECIMAL);

	/* Leading spaces should never happen. */
	if (hdr->ar_name[0] == ' ')
		badfmt();

	/*
	 * Long name support.  Set the "real" size of the file, and the
	 * long name flag/size.
	 */
	if (!bcmp(hdr->ar_name, AR_EFMT1, sizeof(AR_EFMT1) - 1)) {
		chdr.lname = len = atoi(hdr->ar_name + sizeof(AR_EFMT1) - 1);
		if (len <= 0 || len > MAXNAMLEN)
			badfmt();
		nr = read(fd, chdr.name, len);
		if (nr != len) {
			if (nr < 0)
				error(archive);
			badfmt();
		}
		chdr.name[len] = 0;
		chdr.size -= len;
	} else {
		chdr.lname = 0;
D 11
		bcopy(hdr->ar_name, chdr.name, sizeof(hdr->ar_name));
E 11
I 11
		memmove(chdr.name, hdr->ar_name, sizeof(hdr->ar_name));
E 11

		/* Strip trailing spaces, null terminate. */
		for (p = chdr.name + sizeof(hdr->ar_name) - 1; *p == ' '; --p);
		*++p = '\0';
	}
D 11
	return(1);
E 11
I 11
	return (1);
E 11
}

static int already_written;

/*
D 6
 * put_object --
E 6
I 6
 * put_arobj --
E 6
 *	Write an archive member to a file.
 */
I 11
void
E 11
D 6
put_object(cfp, sb)
E 6
I 6
put_arobj(cfp, sb)
E 6
	CF *cfp;
	struct stat *sb;
{
D 11
	register int lname;
	register char *name;
E 11
I 11
	int lname;
	char *name;
E 11
	struct ar_hdr *hdr;
	off_t size;
D 5
	char *rname();
E 5

	/*
	 * If passed an sb structure, reading a file from disk.  Get stat(2)
	 * information, build a name and construct a header.  (Files are named
	 * by their last component in the archive.)  If not, then just write
	 * the last header read.
	 */
	if (sb) {
		name = rname(cfp->rname);
		(void)fstat(cfp->rfd, sb);

D 3
		if ((lname = strlen(name)) > sizeof(hdr->ar_name) ||
		    index(name, ' ')) {
E 3
I 3
		/*
		 * If not truncating names and the name is too long or contains
		 * a space, use extended format 1.
		 */
		lname = strlen(name);
D 4
		if (!(options & AR_S) && (lname > sizeof(hdr->ar_name) ||
		    index(name, ' '))) {
E 3
			(void)sprintf(hb, HDR1, AR_EFMT1, lname, sb->st_mtime,
			    sb->st_uid, sb->st_gid, sb->st_mode,
			    sb->st_size + lname, ARFMAG);
		} else {
I 3
			if (lname > sizeof(hdr->ar_name)) {
				(void)fflush(stdout);
				(void)fprintf(stderr,
E 4
I 4
D 7
		if (options & AR_S) {
E 7
I 7
		if (options & AR_TR) {
E 7
			if (lname > OLDARMAXNAME) {
D 5
				(void)fflush(stdout); (void)fprintf(stderr,
E 5
I 5
				(void)fflush(stdout);
D 11
				(void)fprintf(stderr,
E 5
E 4
				    "ar: warning: %s truncated to %.*s\n",
E 11
I 11
D 13
				warnx("warning: %s truncated to %.*s\n",
E 13
I 13
				warnx("warning: %s truncated to %.*s",
E 13
E 11
D 4
				    name, sizeof(hdr->ar_name), name);
E 4
I 4
				    name, OLDARMAXNAME, name);
E 4
				(void)fflush(stderr);
			}
I 4
D 8
			(void)sprintf(hb, HDR3, name, sb->st_mtime, sb->st_uid,
			    sb->st_gid, sb->st_mode, sb->st_size, ARFMAG);
E 8
I 8
			(void)sprintf(hb, HDR3, name, sb->st_mtimespec.ts_sec,
			    sb->st_uid, sb->st_gid, sb->st_mode, sb->st_size,
			    ARFMAG);
E 8
			lname = 0;
D 11
		} else if (lname > sizeof(hdr->ar_name) || index(name, ' '))
E 11
I 11
		} else if (lname > sizeof(hdr->ar_name) || strchr(name, ' '))
E 11
D 8
			(void)sprintf(hb, HDR1, AR_EFMT1, lname, sb->st_mtime,
			    sb->st_uid, sb->st_gid, sb->st_mode,
			    sb->st_size + lname, ARFMAG);
E 8
I 8
			(void)sprintf(hb, HDR1, AR_EFMT1, lname,
			    sb->st_mtimespec.ts_sec, sb->st_uid, sb->st_gid,
			    sb->st_mode, sb->st_size + lname, ARFMAG);
E 8
		else {
E 4
E 3
			lname = 0;
D 8
			(void)sprintf(hb, HDR2, name, sb->st_mtime, sb->st_uid,
			    sb->st_gid, sb->st_mode, sb->st_size, ARFMAG);
E 8
I 8
			(void)sprintf(hb, HDR2, name, sb->st_mtimespec.ts_sec,
			    sb->st_uid, sb->st_gid, sb->st_mode, sb->st_size,
			    ARFMAG);
E 8
		}
		size = sb->st_size;
	} else {
		lname = chdr.lname;
		name = chdr.name;
		size = chdr.size;
	}

	if (write(cfp->wfd, hb, sizeof(HDR)) != sizeof(HDR))
		error(cfp->wname);
	if (lname) {
		if (write(cfp->wfd, name, lname) != lname)
			error(cfp->wname);
		already_written = lname;
	}
D 6
	copyfile(cfp, size);
E 6
I 6
	copy_ar(cfp, size);
E 6
	already_written = 0;
}

/*
E 2
D 6
 * copyfile --
E 6
I 6
 * copy_ar --
E 6
 *	Copy size bytes from one file to another - taking care to handle the
D 2
 *	extra byte (for odd size files) when reading archives and tmpfiles
 *	and writing an extra byte if necessary when adding files to archive.
E 2
I 2
 *	extra byte (for odd size files) when reading archives and writing an
 *	extra byte if necessary when adding files to archive.  The length of
 *	the object is the long name plus the object itself; the variable
 *	already_written gets set if a long name was written.
E 2
 *
 *	The padding is really unnecessary, and is almost certainly a remnant
 *	of early archive formats where the header included binary data which
D 2
 *	a PDP-11 required to start on an even byte boundary.  It should have
 *	been ripped out when the format changed.
E 2
I 2
 *	a PDP-11 required to start on an even byte boundary.  (Or, perhaps,
 *	because 16-bit word addressed copies were faster?)  Anyhow, it should
 *	have been ripped out long ago.
E 2
 */
I 11
void
E 11
D 6
copyfile(cfp, size)
E 6
I 6
copy_ar(cfp, size)
E 6
	CF *cfp;
D 2
	register off_t size;
E 2
I 2
	off_t size;
E 2
{
I 2
	static char pad = '\n';
D 11
	register off_t sz;
E 2
	register int from, nr, nw, off, to;
E 11
I 11
	off_t sz;
	int from, nr, nw, off, to;
E 11
D 2
	char pad, buf[8*1024];
E 2
I 2
	char buf[8*1024];
E 2
	
D 2
	if (!size)
E 2
I 2
	if (!(sz = size))
E 2
		return;

D 2
	pad = size & 1;
E 2
	from = cfp->rfd;
	to = cfp->wfd;
D 2
	while (size &&
	    (nr = read(from, buf, MIN(size, sizeof(buf)))) > 0) {
		size -= nr;
E 2
I 2
	sz = size;
	while (sz && (nr = read(from, buf, MIN(sz, sizeof(buf)))) > 0) {
		sz -= nr;
E 2
		for (off = 0; off < nr; nr -= off, off += nw)
			if ((nw = write(to, buf + off, nr)) < 0)
				error(cfp->wname);
	}
D 2
	if (size) {
E 2
I 2
	if (sz) {
E 2
		if (nr == 0)
			badfmt();
		error(cfp->rname);
	}

D 2
	if (pad) {
		if (cfp->flags & RPAD && (nr = read(from, buf, 1)) != 1) {
			if (nr == 0)
				badfmt();
			error(cfp->rname);
		}
		if (cfp->flags & WPAD) {
			pad = '\n';
			if (write(to, &pad, 1) != 1)
				error(cfp->wname);
		}
E 2
I 2
D 13
	if (cfp->flags & RPAD && size & 1 && (nr = read(from, buf, 1)) != 1) {
E 13
I 13
	if (cfp->flags & RPAD && (size + chdr.lname) & 1 &&
	    (nr = read(from, buf, 1)) != 1) {
E 13
		if (nr == 0)
			badfmt();
		error(cfp->rname);
E 2
	}
I 2
	if (cfp->flags & WPAD && (size + already_written) & 1 &&
	    write(to, &pad, 1) != 1)
		error(cfp->wname);
}

/*
D 6
 * skipobj -
E 6
I 6
 * skip_arobj -
E 6
 *	Skip over an object -- taking care to skip the pad bytes.
 */
I 5
void
E 5
D 6
skipobj(fd)
E 6
I 6
skip_arobj(fd)
E 6
	int fd;
{
	off_t len;

	len = chdr.size + (chdr.size + chdr.lname & 1);
	if (lseek(fd, len, SEEK_CUR) == (off_t)-1)
		error(archive);
E 2
}
E 1
