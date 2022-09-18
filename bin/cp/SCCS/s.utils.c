h64940
s 00111/00099/00148
d D 8.3 94/04/01 10:17:41 bostic 11 10
c POSIX 1003.2B/D9 symbolic links
c make cp use err/warn, and pass errors back to the calling routine
c clean up fts_read() usage, fix errno calls
c make file-copy failed error clean up after itself immediately
e
s 00003/00000/00244
d D 8.2 93/11/16 12:20:14 bostic 10 9
c If you cp many files the system can run out of something
c (I haven't investigated exactly what).  The problem is
c that cp mmaps the source file, but it's never unmapped.
c From: Lennart Augustsson <augustss@cs.chalmers.se>
e
s 00002/00002/00242
d D 8.1 93/05/31 14:18:51 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00243
d D 5.8 93/04/28 16:12:25 bostic 8 7
c lint
e
s 00007/00005/00236
d D 5.7 92/12/02 19:14:11 bostic 7 6
c use <sys/time.h> macros to convert timespec to timeval
e
s 00004/00001/00237
d D 5.6 92/08/21 08:32:57 bostic 6 5
c don't use mmap until the buffer cache and VM are in sync
e
s 00003/00000/00235
d D 5.5 92/06/28 14:56:19 bostic 5 4
c -p option should preserve file flags as well
e
s 00001/00001/00234
d D 5.4 92/06/23 16:54:30 bostic 4 3
c MAP_FILE disappears
e
s 00001/00001/00234
d D 5.3 92/06/21 13:44:22 bostic 3 2
c second arg to mmap is a size_t
e
s 00035/00093/00200
d D 5.2 92/06/01 10:58:00 elan 2 1
c Added -Hh flags and -H
e
s 00293/00000/00000
d D 5.1 92/05/15 17:22:10 elan 1 0
c date and time created 92/05/15 17:22:10 by elan
e
u
U
t
T
I 2
/*-
D 9
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
D 11
 * Copyright (c) 1991, 1993
E 11
I 11
 * Copyright (c) 1991, 1993, 1994
E 11
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h>
D 7
#include <fcntl.h>
E 7
I 7

I 11
#include <err.h>
E 11
E 7
#include <errno.h>
D 7
#include <unistd.h>
E 7
I 7
#include <fcntl.h>
#include <fts.h>
E 7
E 2
I 1
#include <stdio.h>
D 2
#include <fts.h>
E 2
#include <stdlib.h>
I 8
#include <string.h>
E 8
I 2
D 7
#include <fts.h>
E 7
I 7
#include <unistd.h>

E 7
#include "extern.h"
E 2

D 2

E 2
D 11
void
E 11
I 11
int
E 11
D 2
copy_file(fs, dne)
	struct stat *fs;
E 2
I 2
copy_file(entp, dne)
	FTSENT *entp;
E 2
	int dne;
{
	static char buf[MAXBSIZE];
D 11
	register int from_fd, to_fd, rcount, wcount;
E 11
D 2
	struct stat to_stat;
E 2
I 2
	struct stat to_stat, *fs;
I 11
	int ch, checkch, from_fd, rcount, rval, to_fd, wcount;
#ifdef VM_AND_BUFFER_CACHE_SYNCHRONIZED
E 11
E 2
	char *p;
I 11
#endif
E 11
I 2
	
E 2
D 11

E 11
D 2
	if ((from_fd = open(from.p_path, O_RDONLY, 0)) == -1) {
		err("%s: %s", from.p_path, strerror(errno));
E 2
I 2
	if ((from_fd = open(entp->fts_path, O_RDONLY, 0)) == -1) {
D 11
		err("%s: %s", entp->fts_path, strerror(errno));
E 2
		return;
E 11
I 11
		warn("%s", entp->fts_path);
		return (1);
E 11
	}

I 2
	fs = entp->fts_statp;

E 2
	/*
	 * If the file exists and we're interactive, verify with the user.
	 * If the file DNE, set the mode to be the from file, minus setuid
	 * bits, modified by the umask; arguably wrong, but it makes copying
	 * executables work right and it's been that way forever.  (The
	 * other choice is 666 or'ed with the execute bits on the from file
	 * modified by the umask.)
	 */
	if (!dne) {
		if (iflag) {
D 11
			int checkch, ch;

E 11
			(void)fprintf(stderr, "overwrite %s? ", to.p_path);
			checkch = ch = getchar();
			while (ch != '\n' && ch != EOF)
				ch = getchar();
			if (checkch != 'y') {
				(void)close(from_fd);
D 11
				return;
E 11
I 11
				return (0);
E 11
			}
		}
D 11
		to_fd = open(to.p_path, O_WRONLY|O_TRUNC, 0);
E 11
I 11
		to_fd = open(to.p_path, O_WRONLY | O_TRUNC, 0);
E 11
	} else
D 11
		to_fd = open(to.p_path, O_WRONLY|O_CREAT|O_TRUNC,
		    fs->st_mode & ~(S_ISUID|S_ISGID));
E 11
I 11
		to_fd = open(to.p_path, O_WRONLY | O_TRUNC | O_CREAT,
		    fs->st_mode & ~(S_ISUID | S_ISGID));
E 11

	if (to_fd == -1) {
D 11
		err("%s: %s", to.p_path, strerror(errno));
E 11
I 11
		warn("%s", to.p_path);
E 11
		(void)close(from_fd);
D 11
		return;
E 11
I 11
		return (1);;
E 11
	}

I 11
	rval = 0;

E 11
	/*
	 * Mmap and write if less than 8M (the limit is so we don't totally
	 * trash memory on big files.  This is really a minor hack, but it
	 * wins some CPU back.
	 */
I 6
D 11
#ifdef VM_AND_BUFFER_CACHE_FIXED
E 11
I 11
#ifdef VM_AND_BUFFER_CACHE_SYNCHRONIZED
E 11
E 6
	if (fs->st_size <= 8 * 1048576) {
D 3
		if ((p = mmap(NULL, fs->st_size, PROT_READ,
E 3
I 3
		if ((p = mmap(NULL, (size_t)fs->st_size, PROT_READ,
E 3
D 4
		    MAP_FILE, from_fd, (off_t)0)) == (char *)-1)
E 4
I 4
D 11
		    0, from_fd, (off_t)0)) == (char *)-1)
E 4
D 2
			err("%s: %s", from.p_path, strerror(errno));
E 2
I 2
			err("%s: %s", entp->fts_path, strerror(errno));
E 2
		if (write(to_fd, p, fs->st_size) != fs->st_size)
			err("%s: %s", to.p_path, strerror(errno));
I 10
		/* Some systems don't unmap on close(2). */
		if (munmap(p, fs->st_size) < 0)
			err("%s: %s", entp->fts_path, strerror(errno));
E 11
I 11
		    0, from_fd, (off_t)0)) == (char *)-1) {
			warn("%s", entp->fts_path);
			rval = 1;
		} else {
			if (write(to_fd, p, fs->st_size) != fs->st_size) {
				warn("%s", to.p_path);
				rval = 1;
			}
			/* Some systems don't unmap on close(2). */
			if (munmap(p, fs->st_size) < 0) {
				warn("%s", entp->fts_path);
				rval = 1;
			}
		}
E 11
E 10
D 6
	} else {
E 6
I 6
	} else
#endif
	{
E 6
		while ((rcount = read(from_fd, buf, MAXBSIZE)) > 0) {
			wcount = write(to_fd, buf, rcount);
			if (rcount != wcount || wcount == -1) {
D 11
				err("%s: %s", to.p_path, strerror(errno));
E 11
I 11
				warn("%s", to.p_path);
				rval = 1;
E 11
				break;
			}
		}
D 11
		if (rcount < 0)
D 2
			err("%s: %s", from.p_path, strerror(errno));
E 2
I 2
			err("%s: %s", entp->fts_path, strerror(errno));
E 11
I 11
		if (rcount < 0) {
			warn("%s", entp->fts_path);
			rval = 1;
		}
E 11
E 2
	}
D 11
	if (pflag)
		setfile(fs, to_fd);
E 11
I 11

	/* If the copy went bad, lose the file. */
	if (rval == 1) {
		(void)unlink(to.p_path);
		(void)close(from_fd);
		(void)close(to_fd);
		return (1);
	}

	if (pflag && setfile(fs, to_fd))
		rval = 1;
E 11
	/*
	 * If the source was setuid or setgid, lose the bits unless the
	 * copy is owned by the same user and group.
	 */
D 11
	else if (fs->st_mode & (S_ISUID|S_ISGID) && fs->st_uid == myuid)
		if (fstat(to_fd, &to_stat))
			err("%s: %s", to.p_path, strerror(errno));
#define	RETAINBITS	(S_ISUID|S_ISGID|S_ISVTX|S_IRWXU|S_IRWXG|S_IRWXO)
		else if (fs->st_gid == to_stat.st_gid && fchmod(to_fd,
		    fs->st_mode & RETAINBITS & ~myumask))
			err("%s: %s", to.p_path, strerror(errno));
E 11
I 11
#define	RETAINBITS \
	(S_ISUID | S_ISGID | S_ISVTX | S_IRWXU | S_IRWXG | S_IRWXO)
	else if (fs->st_mode & (S_ISUID | S_ISGID) && fs->st_uid == myuid)
		if (fstat(to_fd, &to_stat)) {
			warn("%s", to.p_path);
			rval = 1;
		} else if (fs->st_gid == to_stat.st_gid &&
		    fchmod(to_fd, fs->st_mode & RETAINBITS & ~myumask)) {
			warn("%s", to.p_path);
			rval = 1;
		}
E 11
	(void)close(from_fd);
D 11
	if (close(to_fd))
		err("%s: %s", to.p_path, strerror(errno));
E 11
I 11
	if (close(to_fd)) {
		warn("%s", to.p_path);
		rval = 1;
	}
	return (rval);
E 11
}

D 11
void
E 11
I 11
int
E 11
D 2
copy_dir()
{
	struct stat from_stat;
	struct dirent *dp, **dir_list;
	register int dir_cnt, i;
	char *old_from, *old_to;

	register FTS *ftsp;
	register FTSENT *p;

	dir_cnt = scandir(from.p_path, &dir_list, NULL, NULL);
	if (dir_cnt == -1) {
		(void)fprintf(stderr, "%s: can't read directory %s.\n",
		    progname, from.p_path);
		exit_val = 1;
	}

	/*
	 * Instead of handling directory entries in the order they appear
	 * on disk, do non-directory files before directory files.
	 * There are two reasons to do directories last.  The first is
	 * efficiency.  Files tend to be in the same cylinder group as
	 * their parent, whereas directories tend not to be.  Copying files
	 * all at once reduces seeking.  Second, deeply nested tree's
	 * could use up all the file descriptors if we didn't close one
	 * directory before recursivly starting on the next.
	 */
	/* copy files */
	for (i = 0; i < dir_cnt; ++i) {
		dp = dir_list[i];
		if (dp->d_namlen <= 2 && dp->d_name[0] == '.'
		    && (dp->d_name[1] == NULL || dp->d_name[1] == '.'))
			goto done;
		if (!(old_from =
		    path_append(&from, dp->d_name, (int)dp->d_namlen)))
			goto done;

		if (statfcn(from.p_path, &from_stat) < 0) {
			err("%s: %s", dp->d_name, strerror(errno));
			path_restore(&from, old_from);
			goto done;
		}
		if (S_ISDIR(from_stat.st_mode)) {
			path_restore(&from, old_from);
			continue;
		}
		if (old_to = path_append(&to, dp->d_name, (int)dp->d_namlen)) {
			copy();
			path_restore(&to, old_to);
		}
		path_restore(&from, old_from);
done:		dir_list[i] = NULL;
		free(dp);
	}

	/* copy directories */
	for (i = 0; i < dir_cnt; ++i) {
		dp = dir_list[i];
		if (!dp)
			continue;
		if (!(old_from =
		    path_append(&from, dp->d_name, (int)dp->d_namlen))) {
			free(dp);
			continue;
		}
		if (!(old_to =
		    path_append(&to, dp->d_name, (int)dp->d_namlen))) {
			free(dp);
			path_restore(&from, old_from);
			continue;
		}
		copy();
		free(dp);
		path_restore(&from, old_from);
		path_restore(&to, old_to);
	}
	free(dir_list);
}

void
copy_link(exists)
E 2
I 2
copy_link(p, exists)
	FTSENT *p;
E 2
	int exists;
{
	int len;
	char link[MAXPATHLEN];

D 2
	if ((len = readlink(from.p_path, link, sizeof(link))) == -1) {
		err("readlink: %s: %s", from.p_path, strerror(errno));
E 2
I 2
	if ((len = readlink(p->fts_path, link, sizeof(link))) == -1) {
D 11
		err("readlink: %s: %s", p->fts_path, strerror(errno));
E 2
		return;
E 11
I 11
		warn("readlink: %s", p->fts_path);
		return (1);
E 11
	}
	link[len] = '\0';
	if (exists && unlink(to.p_path)) {
D 11
		err("unlink: %s: %s", to.p_path, strerror(errno));
		return;
E 11
I 11
		warn("unlink: %s", to.p_path);
		return (1);
E 11
	}
	if (symlink(link, to.p_path)) {
D 11
		err("symlink: %s: %s", link, strerror(errno));
		return;
E 11
I 11
		warn("symlink: %s", link);
		return (1);
E 11
	}
I 11
	return (0);
E 11
}

D 11
void
E 11
I 11
int
E 11
copy_fifo(from_stat, exists)
	struct stat *from_stat;
	int exists;
{
	if (exists && unlink(to.p_path)) {
D 11
		err("unlink: %s: %s", to.p_path, strerror(errno));
		return;
E 11
I 11
		warn("unlink: %s", to.p_path);
		return (1);
E 11
	}
	if (mkfifo(to.p_path, from_stat->st_mode)) {
D 11
		err("mkfifo: %s: %s", to.p_path, strerror(errno));
		return;
E 11
I 11
		warn("mkfifo: %s", to.p_path);
		return (1);
E 11
	}
D 11
	if (pflag)
		setfile(from_stat, 0);
E 11
I 11
	return (pflag ? setfile(from_stat, 0) : 0);
E 11
}

D 11
void
E 11
I 11
int
E 11
copy_special(from_stat, exists)
	struct stat *from_stat;
	int exists;
{
	if (exists && unlink(to.p_path)) {
D 11
		err("unlink: %s: %s", to.p_path, strerror(errno));
		return;
E 11
I 11
		warn("unlink: %s", to.p_path);
		return (1);
E 11
	}
D 11
	if (mknod(to.p_path, from_stat->st_mode,  from_stat->st_rdev)) {
		err("mknod: %s: %s", to.p_path, strerror(errno));
		return;
E 11
I 11
	if (mknod(to.p_path, from_stat->st_mode, from_stat->st_rdev)) {
		warn("mknod: %s", to.p_path);
		return (1);
E 11
	}
D 11
	if (pflag)
		setfile(from_stat, 0);
E 11
I 11
	return (pflag ? setfile(from_stat, 0) : 0);
E 11
}


D 11
void
E 11
I 11
int
E 11
setfile(fs, fd)
	register struct stat *fs;
	int fd;
{
	static struct timeval tv[2];
I 11
	int rval;
E 11

D 11
	fs->st_mode &= S_ISUID|S_ISGID|S_IRWXU|S_IRWXG|S_IRWXO;
E 11
I 11
	rval = 0;
	fs->st_mode &= S_ISUID | S_ISGID | S_IRWXU | S_IRWXG | S_IRWXO;
E 11

D 7
	tv[0].tv_sec = fs->st_atime;
	tv[1].tv_sec = fs->st_mtime;
E 7
I 7
	TIMESPEC_TO_TIMEVAL(&tv[0], &fs->st_atimespec);
	TIMESPEC_TO_TIMEVAL(&tv[1], &fs->st_mtimespec);
E 7
D 11
	if (utimes(to.p_path, tv))
		err("utimes: %s: %s", to.p_path, strerror(errno));
E 11
I 11
	if (utimes(to.p_path, tv)) {
		warn("utimes: %s", to.p_path);
		rval = 1;
	}
E 11
	/*
	 * Changing the ownership probably won't succeed, unless we're root
	 * or POSIX_CHOWN_RESTRICTED is not set.  Set uid/gid before setting
	 * the mode; current BSD behavior is to remove all setuid bits on
	 * chown.  If chown fails, lose setuid/setgid bits.
	 */
	if (fd ? fchown(fd, fs->st_uid, fs->st_gid) :
	    chown(to.p_path, fs->st_uid, fs->st_gid)) {
D 11
		if (errno != EPERM)
			err("chown: %s: %s", to.p_path, strerror(errno));
		fs->st_mode &= ~(S_ISUID|S_ISGID);
E 11
I 11
		if (errno != EPERM) {
			warn("chown: %s", to.p_path);
			rval = 1;
		}
		fs->st_mode &= ~(S_ISUID | S_ISGID);
E 11
	}
D 11
	if (fd ? fchmod(fd, fs->st_mode) : chmod(to.p_path, fs->st_mode))
		err("chown: %s: %s", to.p_path, strerror(errno));
E 11
I 11
	if (fd ? fchmod(fd, fs->st_mode) : chmod(to.p_path, fs->st_mode)) {
		warn("chown: %s", to.p_path);
		rval = 1;
	}
E 11
I 5

D 11
	if (fd ? fchflags(fd, fs->st_flags) : chflags(to.p_path, fs->st_flags))
		err("chflags: %s: %s", to.p_path, strerror(errno));
E 11
I 11
	if (fd ?
	    fchflags(fd, fs->st_flags) : chflags(to.p_path, fs->st_flags)) {
		warn("chflags: %s", to.p_path);
		rval = 1;
	}
	return (rval);
E 11
E 5
}

void
usage()
{
D 11
	(void)fprintf(stderr,
D 2
"usage: cp [-Rfhip] src target;\n       cp [-Rfhip] src1 ... srcN directory\n");
E 2
I 2
"usage: cp [-HRfhip] src target;\n       cp [-HRfhip] src1 ... srcN directory\n");
E 11
I 11
	(void)fprintf(stderr, "%s\n%s\n",
"usage: cp [-R [-H | -L | -P] [-fip] src target",
"       cp [-R [-H | -L | -P] [-fip] src1 ... srcN directory");
E 11
E 2
	exit(1);
D 11
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
        va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "%s: ", progname);
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit_val = 1;
E 11
}
E 1
