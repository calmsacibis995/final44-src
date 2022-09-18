h07319
s 00002/00002/00420
d D 8.5 95/04/29 10:02:07 bostic 57 56
c cp -R didn't work correctly for FIFO's (programmer head space error)
c From: "Charles M. Hannum" <mycroft@gnu.ai.mit.edu>
e
s 00001/00001/00421
d D 8.4 95/04/28 17:16:53 bostic 56 55
c too many arguments to err() function
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00008/00001/00414
d D 8.3 95/04/28 09:34:03 bostic 55 54
c don't overwrite a directory with some other type of file, i.e.
c don't attempt to unlink a directory
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00123/00134/00292
d D 8.2 94/04/01 10:17:38 bostic 54 53
c POSIX 1003.2B/D9 symbolic links
c make cp use err/warn, and pass errors back to the calling routine
c clean up fts_read() usage, fix errno calls
c make file-copy failed error clean up after itself immediately
e
s 00005/00005/00421
d D 8.1 93/05/31 14:18:41 bostic 53 52
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00424
d D 5.36 92/07/22 12:11:03 bostic 52 51
c don't descend below identical directories
e
s 00001/00000/00423
d D 5.35 92/07/22 12:00:18 bostic 51 50
c don't descend below skipped directories
e
s 00001/00001/00422
d D 5.34 92/07/22 11:38:27 elan 50 49
c fixed bug in directory copying errors.
e
s 00092/00112/00331
d D 5.33 92/06/08 16:19:39 bostic 49 48
c whitespace cleanups, no real changes
e
s 00070/00012/00373
d D 5.32 92/06/04 15:41:31 elan 48 47
c Fixed bug in name concatenation. 
c Made handling ".." directories work the way it should, not like it used to.
e
s 00003/00002/00382
d D 5.31 92/06/03 12:25:23 elan 47 46
c Fixed error message bug and made error handling more robust.
e
s 00021/00013/00363
d D 5.30 92/06/02 13:23:33 elan 46 45
c Changed symlink behavior on the command line to logical. 
c Fixed bug in special file copying ('return' --> 'break').
e
s 00002/00000/00374
d D 5.29 92/06/01 17:46:12 elan 45 44
c Fixed bug in fts loop that caused specials not to be copied.
e
s 00005/00005/00369
d D 5.28 92/06/01 11:13:22 elan 44 43
c Fixed bug of concatenation of path names.
e
s 00199/00379/00175
d D 5.27 92/06/01 10:56:17 elan 43 42
c Revised to use fts(3) library.
e
s 00001/00001/00553
d D 5.26 91/10/27 14:28:26 bostic 42 41
c typo when going to POSIX stat.h; test case was "cp -r . /tmp" failed
e
s 00109/00079/00445
d D 5.25 91/10/27 08:57:27 bostic 41 40
c use mmap on files smaller than 8M; function prototypes for local
c functions; lots of minor cleanup/formatting
e
s 00002/00001/00522
d D 5.24 91/05/06 10:25:18 bostic 40 39
c check for close failure -- it may be an NFS file system
e
s 00005/00004/00518
d D 5.23 91/04/03 11:25:16 bostic 39 38
c ANSI include files, struct direct -> struct dirent
e
s 00034/00168/00488
d D 5.22 91/04/03 11:23:21 bostic 38 37
c break up in anticipation of sharing source with mv
c minor cleanups, ismember() routine wasn't being used
e
s 00014/00006/00642
d D 5.21 91/03/03 18:30:44 bostic 37 36
c error messages should report system call that failed
e
s 00047/00036/00601
d D 5.20 90/06/29 16:40:54 bostic 36 35
c make consistent with POSIX 1003.2, draft 10.  Now have two recursive
c flags, -r and -R; -r is unchanged and deprecated; -R is recursive done right.
c Add ability to do FIFO's in recursive copies.  Disallow any setuid/gid bits
c if either owner or group has changed.
e
s 00021/00024/00616
d D 5.19 90/06/28 17:28:03 bostic 35 34
c rename flags; lint cleanups; make -f/-i just toggle
e
s 00008/00017/00632
d D 5.18 90/06/08 08:46:02 bostic 34 33
c try setuid bits for -p again -- lose bits if chown/chgrp fails
e
s 00001/00011/00648
d D 5.17 90/05/31 20:28:40 bostic 33 32
c new copyright notice
e
s 00001/00001/00658
d D 5.16 90/05/15 19:40:48 bostic 32 31
c string.h is ANSI C include file
e
s 00002/00004/00657
d D 5.15 90/03/05 11:14:10 bostic 31 30
c fix errno for ANSI C variable scoping
e
s 00005/00004/00656
d D 5.14 89/10/02 07:55:07 bostic 30 29
c missed one of the cases of using st_ino to store DNE flag
e
s 00024/00016/00636
d D 5.13 89/10/01 17:04:59 bostic 29 28
c mv(1) uses cp -- print out the "called as" program name, except for
c usage statements
e
s 00014/00018/00638
d D 5.12 89/10/01 16:55:08 bostic 28 27
c better initialization, capitalize typedef's, correct usage message
e
s 00025/00022/00631
d D 5.11 89/09/11 18:10:50 bostic 27 26
c revise copying setuid files
e
s 00103/00051/00550
d D 5.10 89/09/10 12:19:17 bostic 26 25
c fixes for copying setuid files
e
s 00003/00001/00598
d D 5.9 89/08/29 16:58:06 bostic 25 24
c NUL terminate the readlink buffer
e
s 00008/00006/00591
d D 5.8 89/08/24 16:42:44 bostic 24 23
c if -r and not -h use lstat on recursive descent; Harry Rubin
e
s 00006/00004/00591
d D 5.7 89/08/24 13:40:53 bostic 23 22
c set directory modes/permissions/etc. on -p -r; Harry Rubin
e
s 00134/00101/00461
d D 5.6 89/08/13 13:18:11 bostic 22 21
c fix umask manipulation (make it like old cp) -- a little tricky.
c created directories are same as source, created files are source - umask.
c don't use st_ino to store directory DNE flag; use fchmod/fchown if possible
c some minor reorganization and whacks
e
s 00085/00054/00477
d D 5.5 89/05/19 18:11:48 bostic 21 20
c POSIX.2 compliance: set uid/gid for -p, add -f.
c on -r, recreate special files
e
s 00042/00013/00489
d D 5.4 89/05/08 21:27:06 bostic 20 19
c don't follow symlinks on -r; add -h flag to force symlink follow
e
s 00014/00011/00488
d D 5.3 89/01/16 21:35:05 bostic 19 18
c don't use scanf to read single char; don't quote file names in
c error messages; make error messages consistent
e
s 00350/00403/00149
d D 5.2 89/01/04 15:26:23 bostic 18 17
c reformat; add Berkeley copyright
e
s 00506/00199/00046
d D 5.1 89/01/04 15:25:42 bostic 17 16
c new version from Dave Hitz of Auspex
e
s 00004/00001/00241
d D 4.14 86/12/02 10:02:26 bostic 16 15
c made I/O buffer long-word aligned for Power 6/32.
e
s 00014/00002/00228
d D 4.13 85/10/11 17:58:40 mckusick 15 14
c add copyright
e
s 00008/00002/00222
d D 4.12 85/10/09 11:09:38 bloom 14 13
c now allows recursive copies of non-writable directories (chris@maryland)
e
s 00014/00007/00210
d D 4.11 85/06/08 01:45:37 lepreau 13 11
c overload -p to also mean preserve modes/ignore umask
e
s 00000/00000/00217
d R 4.11 85/06/08 01:42:20 lepreau 12 11
c overload -p to also mean preserve modes/ignore umask
e
s 00033/00005/00184
d D 4.10 85/06/08 00:47:18 lepreau 11 10
c add -p to preserve file and dir mtimes (& atimes prior to access)
e
s 00019/00012/00170
d D 4.9 85/06/07 01:47:19 serge 10 9
c allow "cp -r dir non-existent-dir"
e
s 00001/00001/00181
d D 4.8 83/07/01 23:57:18 wnj 9 8
c include problems
e
s 00021/00009/00161
d D 4.7 83/06/20 20:50:22 sam 8 7
c missing close's (from bill@dagobah.UUCP)
e
s 00003/00033/00167
d D 4.6 82/12/21 22:05:38 sam 7 5
c replace mkdir with sys call
e
s 00040/00042/00158
d R 4.6 82/12/21 16:18:38 sam 6 5
c use mkdir sys call and buffer writes according to st_blksize
e
s 00003/00003/00197
d D 4.5 82/05/07 16:16:36 mckusick 5 4
c update to new fs
e
s 00003/00001/00197
d D 4.4 82/04/28 16:45:14 mckusick 4 3
c close directories after use
e
s 00004/00004/00194
d D 4.3 82/03/31 11:29:55 root 3 2
c get rid of lstat
e
s 00158/00083/00040
d D 4.2 82/03/31 11:21:47 wnj 2 1
c cp -r
e
s 00123/00000/00000
d D 4.1 80/10/01 17:25:52 bill 1 0
c date and time created 80/10/01 17:25:52 by bill
e
u
U
t
T
I 15
/*
D 17
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 17
I 17
D 18
 * Cp copies source files to target files.
E 18
I 18
D 53
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 53
I 53
D 54
 * Copyright (c) 1988, 1993
E 54
I 54
 * Copyright (c) 1988, 1993, 1994
E 54
 *	The Regents of the University of California.  All rights reserved.
E 53
 *
 * This code is derived from software contributed to Berkeley by
 * David Hitz of Auspex Systems Inc.
 *
D 33
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
E 33
I 33
 * %sccs.include.redist.c%
E 33
 */

#ifndef lint
D 53
char copyright[] =
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
 All rights reserved.\n";
E 53
I 53
static char copyright[] =
D 54
"%Z% Copyright (c) 1988, 1993\n\
E 54
I 54
"%Z% Copyright (c) 1988, 1993, 1994\n\
E 54
	The Regents of the University of California.  All rights reserved.\n";
E 53
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
D 49
 * cp copies source files to target files.
E 49
I 49
 * Cp copies source files to target files.
E 49
E 18
 * 
D 28
 * The global path_t structures "to" and "from" always contain paths to the
E 28
I 28
D 43
 * The global PATH_T structures "to" and "from" always contain paths to the
E 28
D 18
 * current source and target files, respectively.  Since cp does not
 * change directories, these paths can be either absolute or
 * dot-realative.
E 18
I 18
 * current source and target files, respectively.  Since cp does not change
 * directories, these paths can be either absolute or dot-realative.
E 43
I 43
D 49
 * The global PATH_T structures "to" always containa the path to the
 * current target file, respectively.  Since fts(3) does not change
 * directories, this path can be either absolute or dot-realative.
E 49
I 49
 * The global PATH_T structure "to" always contains the path to the
 * current target file.  Since fts(3) does not change directories,
D 55
 * this path can be either absolute or dot-realative.
E 55
I 55
 * this path can be either absolute or dot-relative.
E 55
E 49
E 43
E 18
 * 
D 43
 * The basic algorithm is to initialize "to" and "from", and then call the
 * recursive copy() function to do the actual work.  If "from" is a file,
 * copy copies the data.  If "from" is a directory, copy creates the
 * corresponding "to" directory, and calls itself recursively on all of
 * the entries in the "from" directory.
E 43
I 43
 * The basic algorithm is to initialize "to" and use fts(3) to traverse
 * the file hierarchy rooted in the argument list.  A trivial case is the
D 49
 * case of 'cp file1 file2'. The more interesing case is the case of
E 49
I 49
 * case of 'cp file1 file2'.  The more interesting case is the case of
E 49
 * 'cp file1 file2 ... fileN dir' where the hierarchy is traversed and the
D 49
 * path (relative to the root of the traversal) is appended to dir 
 * (stored in "to") to form the final target path.
E 49
I 49
 * path (relative to the root of the traversal) is appended to dir (stored
 * in "to") to form the final target path.
E 49
E 43
D 22
 * 
D 18
 * Instead of handling directory entires in the order they appear one disk,
E 18
I 18
 * Instead of handling directory entries in the order they appear on disk,
E 18
 * copy() does non-directory files before directory files.
 * 
D 18
 * There are two reasons to do directories last. The first is efficiency.
E 18
I 18
 * There are two reasons to do directories last.  The first is efficiency.
E 18
 * Files tend to be in the same cylinder group as their parent, whereas
 * directories tend not to be. Copying files all at once reduces seeking.
 * 
 * Second, deeply nested tree's could use up all the file descriptors if we
 * didn't close one directory before recursivly starting on the next.
E 22
E 17
 */

E 15
I 1
D 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
I 2
D 17
#ifndef lint
D 11
static char *sccsid = "%W% %E%";
E 11
I 11
D 13
static char *sccsid = "%W% %G%";
E 13
I 13
D 15
static char *sccsid = "%W% (Berkeley) %G%";
E 13
E 11
#endif
E 15
I 15
char copyright[] =
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
 All rights reserved.\n";
#endif not lint

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 15

E 2
/*
D 2
 * cp oldfile newfile
E 2
I 2
 * cp
E 2
 */
E 17
D 2

#define	BSIZE	1024
E 2
D 18
#include <stdio.h>
D 5
#include <sys/types.h>
E 5
I 5
D 17
#include <sys/param.h>
E 17
I 17
#include <errno.h>
#include <strings.h>

#include <sys/types.h>
E 18
I 18
#include <sys/param.h>
E 18
E 17
E 5
#include <sys/stat.h>
I 41
#include <sys/mman.h>
E 41
I 17
D 39
#include <sys/file.h>
E 17
D 2
struct	stat	stbuf1, stbuf2;
char	iobuf[BSIZE];
int	iflag = 0;	/* interactive flag. If this flag is set,
			 * the user is queried before files are
			 * destroyed by cp.
			 */
E 2
I 2
D 5
#include <ndir.h>
E 5
I 5
D 9
#include <dir.h>
E 9
I 9
#include <sys/dir.h>
E 39
I 11
#include <sys/time.h>
I 49

E 49
E 11
E 9
E 5
E 2
D 28

E 28
I 2
D 5
#define	BSIZE	1024
E 5
I 5
D 10
#define	BSIZE	8192
E 5

E 10
D 17
int	iflag;
int	rflag;
D 11
char	*rindex(), *sprintf();
E 11
I 11
int	pflag;
char	*rindex();
E 17
I 17
D 18
#include <sys/param.h>
E 18
I 18
D 39
#include <stdio.h>
E 39
I 39
#include <dirent.h>
D 54
#include <fcntl.h>
E 54
I 54
#include <err.h>
E 54
E 39
#include <errno.h>
I 39
D 54
#include <unistd.h>
E 54
I 54
#include <fcntl.h>
#include <fts.h>
E 54
#include <stdio.h>
E 39
I 35
#include <stdlib.h>
E 35
D 32
#include <strings.h>
E 32
I 32
#include <string.h>
I 43
D 54
#include <fts.h>
E 54
I 54
#include <unistd.h>

E 54
E 43
I 38
D 41
#include "cp.h"
E 41
I 41
#include "extern.h"
E 41
E 38
E 32
E 18
E 17
E 11

I 49
#define	STRIP_TRAILING_SLASH(p) {					\
        while ((p).p_end > (p).p_path && (p).p_end[-1] == '/')		\
                *--(p).p_end = 0;					\
}
E 49
I 41
D 43
static void copy __P((void));
static void copy_dir __P((void));
static void copy_fifo __P((struct stat *, int));
static void copy_file __P((struct stat *, int));
static void copy_link __P((int));
static void copy_special __P((struct stat *, int));
static void setfile __P((struct stat *, int));
static void usage __P((void));
E 43

E 41
I 28
D 38
#define	type(st)	((st).st_mode & S_IFMT)
E 38
I 38
D 43
PATH_T from = { from.p_path, "" };
E 43
I 43
D 49
#define FILE_TO_FILE 1
#define FILE_TO_DIR  2
I 48
#define DIR_TO_DNE  3
E 49
I 49
D 54
static void	copy __P((FTS *));
static int	mastercmp __P((const FTSENT **, const FTSENT **));
E 49
E 48

E 54
D 49
#define STRIP_TRAILING_SLASH(p) { \
        while ((p).p_end > (p).p_path && (p).p_end[-1] == '/') \
                *--(p).p_end = 0; \
		}

static void copy __P((int, FTS *));
static int mastercmp __P((const FTSENT **, const FTSENT **));
E 49
E 43
PATH_T to = { to.p_path, "" };
E 38

E 28
I 17
D 18

#define TRUE	(1)
#define FALSE	(0)

E 18
D 38
typedef struct {
D 18
    char           *p_path;		/* Pointer to the start of a path. */
    char           *p_end;		/* Pointer to NULL at end of path. */
}               path_t;
E 18
I 18
D 21
	char	*p_path;	/* Pointer to the start of a path. */
	char	*p_end;		/* Pointer to NULL at end of path. */
E 21
I 21
D 28
	char	*p_path;	/* pointer to the start of a path. */
	char	*p_end;		/* pointer to NULL at end of path. */
E 21
} path_t;
E 28
I 28
	char	p_path[MAXPATHLEN + 1];	/* pointer to the start of a path. */
	char	*p_end;			/* pointer to NULL at end of path. */
} PATH_T;
E 28
E 18

I 21
D 26
#define	type(st)	((st).st_mode&S_IFMT)
E 26
I 26
D 28
#define	type(st)	((st).st_mode & S_IFMT)
E 28
I 28
PATH_T from = { "", from.p_path };
PATH_T to = { "", to.p_path };
E 28
E 26

E 38
I 31
D 35
extern int errno;
E 35
E 31
E 21
D 18
int             path_set();
char           *path_append();
char           *path_basename();
void		path_restore();
E 18
I 18
D 26
char *path_append(), *path_basename();
void path_restore();
E 18

I 18
D 20
int exit_val, my_umask;
E 20
I 20
D 22
int exit_val, symfollow, my_umask;
E 22
I 22
D 24
int exit_val, symfollow;
E 24
I 24
int exit_val;
E 26
I 26
uid_t myuid;
D 54
int exit_val, myumask;
E 26
E 24
E 22
E 20
D 35
int interactive_flag, preserve_flag, recursive_flag;
E 35
I 35
D 36
int iflag, pflag, rflag;
E 36
I 36
D 43
int iflag, pflag, orflag, rflag;
E 36
E 35
I 24
D 29
int (*statfcn)();			/* stat function to use */
E 24
char *buf;				/* I/O; malloc for best alignment. */
E 29
I 29
int (*statfcn)();
E 43
I 43
D 49
int iflag, pflag;
E 49
I 49
int iflag, orflag, pflag, rflag;
E 49
E 43
D 38
char *buf, *pname;
E 29
D 22
char from_buf[MAXPATHLEN + 1],		/* Source path buffer. */
     to_buf[MAXPATHLEN + 1];		/* Target path buffer. */
E 22
I 22
D 26
char from_buf[MAXPATHLEN + 1],		/* source path buffer */
     to_buf[MAXPATHLEN + 1];		/* target path buffer */
E 26
I 26
D 28
void path_restore();
E 28
char *path_append(), *path_basename();
E 38
I 38
D 41
char *buf, *progname;
E 41
I 41
char *progname;
E 54
I 54
int Rflag, iflag, pflag, rflag;
int myumask;
E 54
E 41
E 38

I 43
D 49
static int rflag, orflag;
E 49
I 49
D 54
static enum { FILE_TO_FILE, FILE_TO_DIR, DIR_TO_DNE } type;
E 54
I 54
enum op { FILE_TO_FILE, FILE_TO_DIR, DIR_TO_DNE };
E 54

I 54
int copy __P((char *[], enum op, int));
int mastercmp __P((const FTSENT **, const FTSENT **));

E 54
E 49
int
E 43
D 28
char from_buf[MAXPATHLEN + 1], to_buf[MAXPATHLEN + 1];
E 26
E 22
path_t from = {from_buf, from_buf};
path_t to = {to_buf, to_buf};
E 18

E 28
D 18
int             exit_val;
int             my_umask;
int             interactive_flag,
                preserve_flag,
                recursive_flag;

char           *buf;		/* I/O buffer -- malloc for best alignment. */

char            from_buf[MAXPATHLEN + 1],	/* Source path buffer. */
                to_buf[MAXPATHLEN + 1];		/* Target path buffer. */

path_t          from = {from_buf, from_buf};
path_t          to = {to_buf, to_buf};



usage()
{
    (void) fprintf(stderr,
		   "usage: cp [-irp] f1 f2; or: cp [-irp] f1 ... fn d\n");
    exit(1);
}



E 18
E 17
E 2
main(argc, argv)
D 2
char *argv[];
E 2
I 2
D 17
	int argc;
	char **argv;
E 17
I 17
D 18
    int             argc;
    char          **argv;
E 18
I 18
	int argc;
D 49
	char **argv;
E 49
I 49
	char *argv[];
E 49
E 18
E 17
E 2
{
D 2
	register i, r;
E 2
I 2
D 17
	struct stat stb;
	int rc, i;
E 17
I 17
D 18
    extern int      optind;
    extern int      opterr;
    extern char    *optarg;
    struct stat     to_stat;
    char           *old_to;
    int             c;
    int             r;
E 18
I 18
D 31
	extern int optind, errno;
E 31
I 31
D 49
	extern int optind;
E 49
E 31
D 48
	struct stat to_stat;
E 48
I 48
	struct stat to_stat, tmp_stat;
E 48
D 49
	register int c, r;
I 21
D 24
	int force_flag;
E 24
I 24
D 35
	int force_flag, symfollow, lstat(), stat();
E 24
E 21
D 29
	char *old_to, *malloc();
E 29
I 29
	char *old_to, *p, *malloc();
E 35
I 35
D 43
	int symfollow, lstat(), stat();
	char *old_to, *p;
E 43
I 43
	char *p;
	char *target;
	int fts_options;
	int type;
E 49
D 54
	FTS *ftsp;
I 46
D 48
	int hflag;
E 48
I 48
D 49
	int hflag, Hflag;
E 49
I 49
	register int c, r;
	int fts_options, Hflag, hflag;
	char *p, *target;
E 54
I 54
	enum op type;
	int Hflag, Lflag, Pflag, ch, fts_options, r;
	char *target;
E 54
E 49
E 48
E 46
E 43
E 35
E 29
E 18
E 17
E 2

I 29
D 54
	/*
D 38
	 * cp is used by mv(1) -- except for usage statements, print
	 * the "called as" program name.
E 38
I 38
	 * The utility cp(1) is used by mv(1) -- except for usage statements,
	 * print the "called as" program name.
E 38
	 */
D 38
	pname = (p = rindex(*argv,'/')) ? ++p : *argv;
E 38
I 38
	progname = (p = rindex(*argv,'/')) ? ++p : *argv;
E 38

E 29
D 2
	/* get the flag(s) */
E 2
I 2
D 17
	argc--, argv++;
	while (argc > 0 && **argv == '-') {
		(*argv)++;
		while (**argv) switch (*(*argv)++) {
E 17
I 17
D 18
    opterr = 0;
    while ((c = getopt(argc, argv, "Ripr")) != EOF) {
E 18
I 18
D 20
	while ((c = getopt(argc, argv, "Ripr")) != EOF) {
E 20
I 20
D 21
	while ((c = getopt(argc, argv, "Rhipr")) != EOF) {
E 20
E 18
	switch ((char) c) {
E 21
I 21
D 24
	force_flag = 0;
E 24
I 24
D 35
	force_flag = symfollow = 0;
E 35
I 35
D 43
	symfollow = 0;
E 35
E 24
	while ((c = getopt(argc, argv, "Rfhipr")) != EOF) {
	switch ((char)c) {
E 43
I 43
D 49

E 49
	/*
         * Symbolic link handling is as follows:
         * 1.  Follow all symbolic links on the argument line.
         * 2.  Otherwise, don't follow symbolic links UNLESS options -h 
         *     (in conjuction with -R) or -r (for backward compatibility) are 
D 46
         *     set.
E 46
I 46
         *     set, in which case follow all symbolic links, or when the -H
         *     option is set (in conjuction with -R), in which case follow 
         *     all symbolic links on the command line.
         * 
E 46
         */
D 46
	rflag = orflag = 0;
	fts_options = FTS_NOCHDIR | FTS_PHYSICAL;
E 46
I 46
D 48
	hflag = rflag = orflag = 0;
E 48
I 48
D 49
	Hflag = hflag = rflag = orflag = 0;
E 49
I 49
	Hflag = hflag = 0;
E 49
E 48
	fts_options = FTS_NOCHDIR | FTS_LOGICAL;
E 46
	while ((c = getopt(argc, argv, "HRfhipr")) != EOF) 
		switch ((char)c) {
E 54
I 54
	Hflag = Lflag = Pflag = Rflag = 0;
	while ((ch = getopt(argc, argv, "HLPRfipr")) != EOF) 
		switch (ch) {
E 54
		case 'H':
I 48
			Hflag = 1;
E 48
D 54
			fts_options |= FTS_COMFOLLOW;
E 54
I 54
			Lflag = Pflag = 0;
E 54
			break;
I 54
		case 'L':
			Lflag = 1;
			Hflag = Pflag = 0;
			break;
		case 'P':
			Pflag = 1;
			Hflag = Lflag = 0;
			break;
		case 'R':
			Rflag = 1;
			break;
E 54
E 43
		case 'f':
D 35
			force_flag = 1;
E 35
I 35
			iflag = 0;
E 35
			break;
E 21
I 20
D 54
		case 'h':
D 43
			symfollow = 1;
E 43
I 43
D 46
			fts_options &= ~FTS_PHYSICAL;
			fts_options |= FTS_LOGICAL;
E 46
I 46
			hflag = 1;
E 46
E 43
			break;
E 54
E 20
D 18
	case 'i':
	    interactive_flag = isatty(fileno(stdin));
	    break;
	case 'p':
	    preserve_flag = 1;
	    (void) umask(0);
	    break;
	case 'R':
	case 'r':
	    recursive_flag = 1;
	    break;
	case '?':
	default:
	    usage();
	    break;
E 18
I 18
		case 'i':
D 35
			interactive_flag = isatty(fileno(stdin));
E 35
I 35
			iflag = isatty(fileno(stdin));
E 35
			break;
		case 'p':
D 35
			preserve_flag = 1;
E 35
I 35
			pflag = 1;
E 35
D 26
			(void)umask(0);
E 26
			break;
D 36
		case 'r':
E 36
D 54
		case 'R':
I 46
			fts_options &= ~FTS_LOGICAL;
			fts_options |= FTS_PHYSICAL;
E 54
I 54
		case 'r':
E 54
E 46
D 35
			recursive_flag = 1;
E 35
I 35
			rflag = 1;
E 35
			break;
I 36
D 54
		case 'r':
			orflag = 1;
I 43
			fts_options &= ~FTS_PHYSICAL;
			fts_options |= FTS_LOGICAL;
E 43
			break;
E 54
E 36
		case '?':
		default:
			usage();
			break;
		}
E 18
D 43
	}
E 43
D 18
    }
E 18
I 18
D 20
	argc -= optind;		/* argc is count of remaining arguments. */
	argv += optind;		/* argv[0] is first remaining argument. */
E 20
I 20
	argc -= optind;
	argv += optind;
E 20
E 18
E 17
E 2

D 2
	if (argc < 2)
		goto usage;
	if (*argv[1] == '-') {
		argc--;
		while (*++argv[1] != '\0')
			switch (*argv[1]) {
E 2
I 2
D 17
		case 'i':
			iflag++; break;
E 17
I 17
D 18
    argc -= optind;		/* argc is count of remaining arguments. */
    argv += optind;		/* argv[0] is first remaining argument. */
E 18
I 18
	if (argc < 2)
		usage();
E 18
E 17
E 2

I 49
D 54
	if (orflag) {
		if (rflag) {
			(void)fprintf(stderr,
	    "cp: the -R and -r options are mutually exclusive.\n");
			exit(1);
		}
		if (Hflag || hflag) {
			(void)fprintf(stderr,
	    "cp: the -r and the -H and -h options are mutually exclusive.\n");
			exit(1);
		}
E 54
I 54
	fts_options = FTS_NOCHDIR | FTS_PHYSICAL;
	if (rflag) {
		if (Rflag)
			errx(1,
		    "the -R and -r options may not be specified together.");
		if (Hflag || Lflag || Pflag)
			errx(1,
	"the -H, -L, and -P options may not be specified with the -r option.");
		fts_options &= ~FTS_PHYSICAL;
		fts_options |= FTS_LOGICAL;
E 54
	}
D 54

E 49
I 46
	if (hflag) {
E 54
I 54
	if (Rflag) {
		if (Hflag)
			fts_options |= FTS_COMFOLLOW;
		if (Lflag) {
			fts_options &= ~FTS_PHYSICAL;
			fts_options |= FTS_LOGICAL;
		}
	} else {
E 54
		fts_options &= ~FTS_PHYSICAL;
		fts_options |= FTS_LOGICAL;
	}

E 46
I 36
D 49
	if (rflag && orflag) {
		(void)fprintf(stderr,
		    "cp: the -R and -r options are mutually exclusive.\n");
		exit(1);
	}

E 49
E 36
I 21
D 35
	if (force_flag)
		interactive_flag = 0;

E 35
E 21
I 10
D 17
		case 'R':
E 10
D 2
			/* interactive mode */
			case 'i':
				iflag++;
				break;
E 2
I 2
		case 'r':
			rflag++; break;
E 17
I 17
D 18
    if (argc < 2) {
	usage();
    }
E 18
I 18
D 22
	my_umask = umask(0);
	(void)umask(my_umask);
E 18
E 17
E 2

E 22
I 11
D 13
		case 'p':	/* preserve mtimes and atimes */
			pflag++; break;
E 13
I 13
D 17
		case 'p':	/* preserve mtimes, atimes, and modes */
			pflag++;
			(void) umask(0);
			break;
E 17
I 17
D 18
    my_umask = umask(0);
    (void) umask(my_umask);
E 17
E 13

E 11
D 2
			/* don't live with bad options */
			default:
				goto usage;
			}
		argv++;
E 2
I 2
D 17
		default:
			goto usage;
		}
		argc--; argv++;
E 17
I 17
    buf = (char *) malloc(MAXBSIZE);
    if (!buf) {
	fprintf(stderr, "cp: Can't allocate memory for I/O buffer.\n");
	exit(1);
    }

    /*
     * Consume last argument first.
     */
    if ( !path_set(&to, argv[--argc]) )
	exit(exit_val);

    /*
     * Cp has two distinct cases:
     * 
     * Case (1)	  $ cp [-rip] source target
     * 
     * Case (2)	  $ cp [-rip] source1 ... directory
     * 
     * In both cases, source can be either a file or a directory.
     * 
     * In (1), the target becomes a copy of the source. That is, if the
     * source is a file, the target will be a file, and likewise for
     * directories.
     * 
     * In (2), the real target is not directory, but "directory/source".
     */
    r = stat(to.p_path, &to_stat);
    if (r == -1 && errno != ENOENT) {
	error(to.p_path);
	exit(1);
    }

    if (r == -1 || (to_stat.st_mode & S_IFMT) != S_IFDIR) {
	 /*
	  * Case (1).  Target is not a directory.
	  */
	if (argc > 1) {
	    usage();
	    exit(1);
E 18
I 18
D 41
	buf = (char *)malloc(MAXBSIZE);
	if (!buf) {
D 20
		fprintf(stderr, "cp: out of space.\n");
E 20
I 20
D 29
		(void)fprintf(stderr, "cp: out of space.\n");
E 29
I 29
D 38
		(void)fprintf(stderr, "%s: out of space.\n", pname);
E 38
I 38
		(void)fprintf(stderr, "%s: out of space.\n", progname);
E 38
E 29
E 20
		exit(1);
E 18
E 17
E 2
	}
D 2
	if (argc < 3) 
E 2
I 2
D 17
	if (argc < 2) 
E 2
		goto usage;
D 2
	if (argc > 3) {
		if (stat(argv[argc-1], &stbuf2) < 0)
E 2
I 2
D 10
	if (argc > 2 || rflag) {
E 10
I 10
	if (argc > 2) {
E 10
D 3
		if (lstat(argv[argc-1], &stb) < 0)
E 3
I 3
		if (stat(argv[argc-1], &stb) < 0)
E 3
E 2
			goto usage;
D 2
		if ((stbuf2.st_mode&S_IFMT) != S_IFDIR) 
E 2
I 2
		if ((stb.st_mode&S_IFMT) != S_IFDIR) 
E 2
			goto usage;
E 17
I 17

E 41
I 26
	myuid = getuid();

D 49
	/* copy the umask for explicit mode setting */
E 49
I 49
	/* Copy the umask for explicit mode setting. */
E 49
	myumask = umask(0);
	(void)umask(myumask);

E 26
D 18
	if ( !path_set(&from, *argv))
	    exit(exit_val);
E 18
I 18
D 22
	/* Consume last argument first. */
E 22
I 22
D 43
	/* consume last argument first. */
E 22
	if (!path_set(&to, argv[--argc]))
E 43
I 43
D 49
	/* Save the target base in "to" */
E 49
I 49
	/* Save the target base in "to". */
E 49
	target = argv[--argc];
D 54
	if (strlen(target) > MAXPATHLEN) {
		err("%s: name too long", target);
E 43
D 38
		exit(exit_val);
E 38
I 38
		exit(1);
I 43
	}
E 54
I 54
	if (strlen(target) > MAXPATHLEN)
		errx(1, "%s: name too long", target);
E 54
	(void)strcpy(to.p_path, target);
	to.p_end = to.p_path + strlen(to.p_path);
        if (to.p_path == to.p_end) {
		*to.p_end++ = '.';
		*to.p_end = 0;
	}
        STRIP_TRAILING_SLASH(to);
	to.target_end = to.p_end;
E 43
E 38
E 18

I 24
D 35
	statfcn = symfollow || !recursive_flag ? stat : lstat;
E 35
I 35
D 43
	statfcn = symfollow || !rflag ? stat : lstat;
E 35

E 43
I 43
D 49
	/* Want to know when end of list for fts. */
E 49
I 49
	/* Set end of argument list for fts(3). */
E 49
	argv[argc] = NULL;     
	
E 43
E 24
D 18
	copy();
    }
    else {
E 18
	/*
D 18
	 * Case (2).  Target is a directory.
E 18
I 18
	 * Cp has two distinct cases:
	 *
D 38
	 * Case (1)	  $ cp [-rip] source target
E 38
I 38
D 49
	 * % cp [-rip] source target
	 * % cp [-rip] source1 ... directory
E 49
I 49
	 * cp [-R] source target
	 * cp [-R] source1 ... sourceN directory
E 49
E 38
	 *
D 38
	 * Case (2)	  $ cp [-rip] source1 ... directory
	 *
E 38
	 * In both cases, source can be either a file or a directory.
	 *
	 * In (1), the target becomes a copy of the source. That is, if the
	 * source is a file, the target will be a file, and likewise for
	 * directories.
	 *
	 * In (2), the real target is not directory, but "directory/source".
E 18
	 */
D 18
	for (; argc; --argc, ++argv) {
	    if ( !path_set(&from, *argv) )
		continue;
E 18
D 49

E 49
D 18
	    old_to = path_append(&to, path_basename(&from), -1);
	    if ( !old_to )
		continue;

	    copy();
	    path_restore(&to, old_to);
E 18
I 18
	r = stat(to.p_path, &to_stat);
D 54
	if (r == -1 && errno != ENOENT) {
D 21
		error(to.p_path);
E 21
I 21
D 22
		error(to.p_path, "stat");
E 22
I 22
D 41
		error(to.p_path);
E 41
I 41
		err("%s: %s", to.p_path, strerror(errno));
E 41
E 22
E 21
		exit(1);
E 18
E 17
	}
E 54
I 54
	if (r == -1 && errno != ENOENT)
		err(1, "%s", to.p_path);
E 54
D 2
	r = 0;
	for(i=1; i<argc-1;i++)
		r |= copy(argv[i], argv[argc-1]);
	exit(r);
E 2
I 2
D 17
	rc = 0;
	for (i = 0; i < argc-1; i++)
		rc |= copy(argv[i], argv[argc-1]);
	exit(rc);
E 2
usage:
D 2
	fprintf(stderr, "Usage: cp: f1 f2; or cp f1 ... fn d2\n");
E 2
I 2
	fprintf(stderr,
D 11
	    "Usage: cp f1 f2; or cp [ -r ] f1 ... fn d2\n");
E 11
I 11
D 13
	    "Usage: cp [-ip] f1 f2; or: cp [-irp] f1 ... fn d2");
E 13
I 13
	    "Usage: cp [-ip] f1 f2; or: cp [-irp] f1 ... fn d2\n");
E 13
E 11
E 2
	exit(1);
E 17
I 17
D 18
    }
    exit(exit_val);
E 18
I 18
D 21
	if (r == -1 || (to_stat.st_mode & S_IFMT) != S_IFDIR) {
E 21
I 21
D 38
	if (r == -1 || type(to_stat) != S_IFDIR) {
E 38
I 38
	if (r == -1 || !S_ISDIR(to_stat.st_mode)) {
E 38
E 21
		/*
		 * Case (1).  Target is not a directory.
D 48
		 */
E 48
I 48
		 */ 
E 48
		if (argc > 1) {
			usage();
			exit(1);
		}
D 43
		if (!path_set(&from, *argv))
D 38
			exit(exit_val);
E 38
I 38
			exit(1);
E 38
		copy();
E 43
I 43
D 48
		type = FILE_TO_FILE;
E 48
I 48
		/*
		 * Need to detect the case:
D 49
		 * % cp -R dir foo
		 * Where dir is a directory and foo does not exist, because 
		 * in this special case we want pathname concatenations
		 * turned on but not for the initial mkdir().
E 49
I 49
		 *	cp -R dir foo
		 * Where dir is a directory and foo does not exist, where
		 * we want pathname concatenations turned on but not for
		 * the initial mkdir().
E 49
		 */
		if (r == -1) {
D 54
			if (orflag || (rflag && (hflag || Hflag)))
E 54
I 54
			if (rflag || (Rflag && (Lflag || Hflag)))
E 54
				stat(*argv, &tmp_stat);
			else
				lstat(*argv, &tmp_stat);
			
D 54
			if (S_ISDIR(tmp_stat.st_mode) && (rflag || orflag))
E 54
I 54
			if (S_ISDIR(tmp_stat.st_mode) && (Rflag || rflag))
E 54
				type = DIR_TO_DNE;
			else
				type = FILE_TO_FILE;
		} else
			type = FILE_TO_FILE;
E 48
E 43
D 49
	}
D 43
	else {
E 43
I 43
	else
E 49
I 49
	} else
E 49
E 43
		/*
		 * Case (2).  Target is a directory.
		 */
D 22
		for (; argc; --argc, ++argv) {
E 22
I 22
D 43
		for (;; ++argv) {
E 22
D 38
			if (!path_set(&from, *argv))
E 38
I 38
D 41
			if (!path_set(&from, *argv)) {
				exit_val = 1;
E 41
I 41
			if (!path_set(&from, *argv))
E 41
E 38
				continue;
I 38
D 41
			}
E 38
			old_to = path_append(&to, path_basename(&from), -1);
D 38
			if (!old_to)
E 38
I 38
			if (!old_to) {
				exit_val = 1;
E 41
I 41
			if (!(old_to =
			    path_append(&to, path_basename(&from), -1)))
E 41
E 38
				continue;
I 38
D 41
			}
E 41
E 38
			copy();
I 22
			if (!--argc)
				break;
E 22
			path_restore(&to, old_to);
		}
E 43
I 43
		type = FILE_TO_DIR;

D 54
	if ((ftsp = fts_open(argv, fts_options, mastercmp)) == NULL) {
		err("%s", strerror(errno)); 
	        exit(1);
E 43
	}
I 43
D 49
	copy(type, ftsp);
E 49
I 49
	copy(ftsp);
E 49
	fts_close(ftsp);

E 43
	exit(exit_val);
E 54
I 54
	exit (copy(argv, type, fts_options));
E 54
E 18
E 17
}

I 16
D 17
			/* I/O buffer; guarantee long-word alignment */
static char	buf[MAXBSIZE];
E 17
D 18

E 16
D 17
copy(from, to)
D 2
char *from, *to;
E 2
I 2
	char *from, *to;
E 17
I 17

E 18
D 21
/*
 * Copy file or directory at "from" to "to".
 */
E 21
I 21
D 43
/* copy file or directory at "from" to "to". */
E 43
I 41
D 54
static void
E 41
E 21
D 43
copy()
E 43
I 43
D 49
copy(type, ftsp)
	int type;
E 49
I 49
copy(ftsp)
E 49
	FTS *ftsp;
E 54
I 54
int
copy(argv, type, fts_options)
	char *argv[];
	enum op type;
	int fts_options;
E 54
E 43
E 17
E 2
{
D 13
	int fold, fnew, n;
E 13
I 13
D 17
	int fold, fnew, n, exists;
E 13
D 2
	register char *p1, *p2, *bp;
	int mode;
	char c,i;
	if ((fold = open(from, 0)) < 0) {
		fprintf(stderr, "cp: cannot open %s\n", from);
		return(1);
E 2
I 2
D 10
	char *last, destname[BSIZE], buf[BSIZE];
E 10
I 10
D 16
	char *last, destname[MAXPATHLEN + 1], buf[MAXBSIZE];
E 16
I 16
	char *last, destname[MAXPATHLEN + 1];
E 16
E 10
	struct stat stfrom, stto;
E 17
I 17
D 18
    struct stat     from_stat;
    struct stat     to_stat;
    int             new_target_dir = 0;
E 18
I 18
D 43
	struct stat from_stat, to_stat;
D 20
	int new_target_dir = 0;
E 20
I 20
D 21
	int new_target_dir, statval;
E 21
I 21
D 22
	int statval;
E 22
I 22
	int dne, statval;
E 22
E 21
E 20
E 18
E 17

D 17
	fold = open(from, 0);
	if (fold < 0) {
D 8
		fprintf(stderr, "cp: "); perror(from);
E 8
I 8
		Perror(from);
E 8
		return (1);
E 17
I 17
D 18
    if (stat(from.p_path, &from_stat) == -1) {
	error(from.p_path);
	return;
    }

    if (stat(to.p_path, &to_stat) == -1) {
E 18
I 18
D 20
	if (stat(from.p_path, &from_stat) == -1) {
E 20
I 20
D 24
	statval = symfollow || !recursive_flag ?
	    stat(from.p_path, &from_stat) : lstat(from.p_path, &from_stat);
E 24
I 24
	statval = statfcn(from.p_path, &from_stat);
E 24
	if (statval == -1) {
E 20
D 21
		error(from.p_path);
E 21
I 21
D 22
		error(from.p_path, "stat");
E 22
I 22
D 41
		error(from.p_path);
E 41
I 41
		err("%s: %s", from.p_path, strerror(errno));
E 41
E 22
E 21
		return;
	}
E 18
D 20
	/*
	 * This is not an error, but we need to remember that it happened.
	 */
E 20
I 20

	/* not an error, but need to remember it happened */
E 20
D 18
	to_stat.st_ino = -1;
    }
    else {
	if (to_stat.st_dev == from_stat.st_dev && 
		to_stat.st_ino == from_stat.st_ino) {
	    fprintf(stderr, 
		"cp: \"%s\" and \"%s\" are identical (not copied).\n",
		to.p_path, from.p_path);
	    exit_val = 1;
	    return;
E 18
I 18
	if (stat(to.p_path, &to_stat) == -1)
D 22
		to_stat.st_ino = -1;
	else if (to_stat.st_dev == from_stat.st_dev &&
	    to_stat.st_ino == from_stat.st_ino) {
D 20
		fprintf(stderr,
E 20
I 20
		(void)fprintf(stderr,
E 20
D 19
		    "cp: \"%s\" and \"%s\" are identical (not copied).\n",
E 19
I 19
		    "cp: %s and %s are identical (not copied).\n",
E 19
		    to.p_path, from.p_path);
		exit_val = 1;
		return;
E 22
I 22
		dne = 1;
	else {
		if (to_stat.st_dev == from_stat.st_dev &&
		    to_stat.st_ino == from_stat.st_ino) {
			(void)fprintf(stderr,
D 29
			    "cp: %s and %s are identical (not copied).\n",
			    to.p_path, from.p_path);
E 29
I 29
			    "%s: %s and %s are identical (not copied).\n",
D 38
			    pname, to.p_path, from.p_path);
E 38
I 38
			    progname, to.p_path, from.p_path);
E 43
I 43
D 49
	struct stat to_stat;
	int dne;
E 49
D 54
	register FTSENT *curr;
D 48
	
E 48
I 48
D 49
	char *c;
	char *n;
E 49
	register int base, nlen;
E 54
I 49
	struct stat to_stat;
D 54
	int dne;
	char *c, *n;
E 54
I 54
	FTS *ftsp;
	FTSENT *curr;
	int base, dne, nlen, rval;
	char *p;
E 54
E 49

E 48
D 49
	while(curr = fts_read(ftsp)) {
		if (curr->fts_info == FTS_ERR || curr->fts_info == FTS_NS) {
D 47
			err("%s:%s", curr->fts_path, curr->fts_errno);
E 47
I 47
			err("%s: %s", curr->fts_path, 
			    strerror(curr->fts_errno));
E 49
I 49
D 54
	while (curr = fts_read(ftsp)) {
		switch(curr->fts_info) {
E 54
I 54
	if ((ftsp = fts_open(argv, fts_options, mastercmp)) == NULL)
		err(1, NULL);
	for (rval = 0; (curr = fts_read(ftsp)) != NULL;) {
		switch (curr->fts_info) {
E 54
		case FTS_NS:
		case FTS_ERR:
D 54
			err("%s: %s",
E 54
I 54
			warnx("%s: %s",
E 54
			    curr->fts_path, strerror(curr->fts_errno));
E 49
E 47
E 43
E 38
E 29
D 54
			exit_val = 1;
E 54
I 54
			rval = 1;
E 54
D 47
			return;
E 47
I 47
			continue;
E 47
D 49
		}
D 43
		dne = 0;
E 22
E 18
E 17
E 2
	}
D 2
	fstat(fold, &stbuf1);
	mode = stbuf1.st_mode;
	/* is target a directory? */
	if (stat(to, &stbuf2) >=0 &&
	   (stbuf2.st_mode&S_IFMT) == S_IFDIR) {
		p1 = from;
		p2 = to;
		bp = iobuf;
		while(*bp++ = *p2++)
			;
		bp[-1] = '/';
		p2 = bp;
		while(*bp = *p1++)
			if (*bp++ == '/')
				bp = p2;
		to = iobuf;
E 2
I 2
D 17
	if (fstat(fold, &stfrom) < 0) {
D 8
		fprintf(stderr, "cp: "); perror(from);
E 8
I 8
		Perror(from);
		(void) close(fold);
E 8
		return (1);
E 17
I 17
D 18
    }
E 18

I 20
D 21
	if ((from_stat.st_mode & S_IFMT) == S_IFLNK) {
E 21
I 21
D 38
	switch(type(from_stat)) {
E 38
I 38
	switch(from_stat.st_mode & S_IFMT) {
E 38
	case S_IFLNK:
E 21
D 22
		copy_link(to_stat.st_ino != -1);
E 22
I 22
		copy_link(!dne);
E 22
		return;
D 21
	}

	new_target_dir = 0;
E 20
D 18
    if ((from_stat.st_mode & S_IFMT) != S_IFDIR) {
	if (!copy_file(from_stat.st_mode))
	    return;
    }
    else {
	if (!recursive_flag) {
	    (void) fprintf(stderr, 
E 18
I 18
	if ((from_stat.st_mode & S_IFMT) != S_IFDIR) {
		if (!copy_file(from_stat.st_mode))
			return;
	}
	else {
E 21
I 21
	case S_IFDIR:
E 21
D 35
		if (!recursive_flag) {
E 35
I 35
D 36
		if (!rflag) {
E 36
I 36
		if (!rflag && !orflag) {
E 36
E 35
			(void)fprintf(stderr,
E 18
D 21
			   "cp: \"%s\" is a directory (not copied).\n",
			   from.p_path);
E 21
I 21
D 29
			    "cp: %s is a directory (not copied).\n",
			    from.p_path);
E 29
I 29
			    "%s: %s is a directory (not copied).\n",
D 38
			    pname, from.p_path);
E 38
I 38
			    progname, from.p_path);
E 43
I 43
		if (curr->fts_info == FTS_DP)
			continue;
		if (curr->fts_info == FTS_DC) {
E 49
I 49
D 54
		case FTS_DC:
E 49
			err("%s: directory causes a cycle", curr->fts_path);
E 43
E 38
E 29
E 21
D 18
	    exit_val = 1;
	    return;
E 17
E 2
	}
D 2
	if (stat(to, &stbuf2) >= 0) {
		if (stbuf1.st_dev == stbuf2.st_dev &&
		   stbuf1.st_ino == stbuf2.st_ino) {
			fprintf(stderr, "cp: cannot copy file to itself.\n");
E 2
I 2
D 3
	if (lstat(to, &stto) >= 0 &&
E 3
I 3
D 17
	if (stat(to, &stto) >= 0 &&
E 3
	   (stto.st_mode&S_IFMT) == S_IFDIR) {
		last = rindex(from, '/');
		if (last) last++; else last = from;
D 10
		if (strlen(to) + strlen(last) >= BSIZE - 1) {
E 10
I 10
		if (strlen(to) + strlen(last) >= sizeof destname - 1) {
E 10
			fprintf(stderr, "cp: %s/%s: Name too long", to, last);
I 8
			(void) close(fold);
E 8
E 2
			return(1);
D 2
		} else if (iflag) {
E 2
I 2
		}
		(void) sprintf(destname, "%s/%s", to, last);
		to = destname;
E 17
I 17

	if (to_stat.st_ino == -1) {
	    if (mkdir(to.p_path, 0777) < 0) {
		error(to.p_path);
		return;
	    }
	    new_target_dir = TRUE;
E 17
	}
D 17
	if (rflag && (stfrom.st_mode&S_IFMT) == S_IFDIR) {
I 14
		int fixmode = 0;	/* cleanup mode after rcopy */
E 17
I 17
	else if ((to_stat.st_mode & S_IFMT) != S_IFDIR) {
	    (void) fprintf(stderr, 
E 18
I 18
			exit_val = 1;
E 54
I 54
		case FTS_DC:			/* Warn, continue. */
			warnx("%s: directory causes a cycle", curr->fts_path);
			rval = 1;
E 54
D 49
			return;
E 49
I 49
			continue;
D 54
		case FTS_DP:
E 54
I 54
		case FTS_DP:			/* Ignore, continue. */
E 54
			continue;
E 49
		}
D 22
		if (to_stat.st_ino == -1) {
			if (mkdir(to.p_path, 0777) < 0) {
D 21
				error(to.p_path);
E 21
I 21
				error(to.p_path, "mkdir");
E 22
I 22
D 43
		if (dne) {
E 43
I 43

		/*
D 48
		 * If we are in case(2) above, we need to append the 
E 48
I 48
		 * If we are in case (2) or (3) above, we need to append the 
E 48
                 * source name to the target name.  
                 */
D 48
		if (type == FILE_TO_DIR) {
E 48
I 48
		if (type != FILE_TO_FILE) {
E 48
D 44
			if ((curr->fts_pathlen + to.target_end - to.p_path + 1)
E 44
I 44
D 49
			if ((curr->fts_namelen + to.target_end - to.p_path + 1)
E 44
			    > MAXPATHLEN) {
E 49
I 49
			if ((curr->fts_namelen +
			    to.target_end - to.p_path + 1) > MAXPATHLEN) {
E 49
D 54
				err("%s/%s: name too long (not copied)", 
E 54
I 54
				warnx("%s/%s: name too long (not copied)", 
E 54
D 44
				    to.p_path, curr->fts_path);
E 44
I 44
				    to.p_path, curr->fts_name);
I 54
				rval = 1;
E 54
E 44
				continue;
			}
I 48

			/*
D 49
			 * We need to remember roots of traversals so we can
			 * create correct pathnames.  In the case where
			 * we have a directory copied to a non-existent one:
			 * % cp -R a/dir noexist
			 * we want the path names to be noexist/foo rather than
			 * noexist/dir/foo, where foo is a file in dir, as 
			 * opposed to the case where the target exists.
E 49
I 49
			 * Need to remember the roots of traversals to create
			 * correct pathnames.  If there's a directory being
			 * copied to a non-existent directory, e.g.
			 *	cp -R a/dir noexist
			 * the resulting path name should be noexist/foo, not
			 * noexist/dir/foo (where foo is a file in dir), which
			 * is the case where the target exists.
			 *
			 * Also, check for "..".  This is for correct path
			 * concatentation for paths ending in "..", e.g.
			 *	cp -R .. /tmp
			 * Paths ending in ".." are changed to ".".  This is
			 * tricky, but seems the easiest way to fix the problem.
I 54
			 *
			 * XXX
			 * Since the first level MUST be FTS_ROOTLEVEL, base
			 * is always initialized.
E 54
E 49
			 */
D 49
			if (curr->fts_level == FTS_ROOTLEVEL) {
E 49
I 49
			if (curr->fts_level == FTS_ROOTLEVEL)
E 49
				if (type != DIR_TO_DNE) {
D 54
					c = rindex(curr->fts_path, '/');
D 49
					base = (c == NULL)? 0 : 
E 49
I 49
					base = (c == NULL) ? 0 : 
E 49
						(int) (c - curr->fts_path + 1);
E 54
I 54
					p = strrchr(curr->fts_path, '/');
					base = (p == NULL) ? 0 : 
					    (int)(p - curr->fts_path + 1);
E 54

D 49
				/*
				 * This is necessary to assure that
				 * correct concatentation of paths ending
				 * in ".." occurs.  This is somewhat
				 * tricky.  Note that the old
				 * cp(1) did not handle these cases 
				 * correctly.  This is sort of a hack
				 * but it is the easiest way to
				 * fix the problem.
				 */
E 49
					if (!strcmp(&curr->fts_path[base], 
					    ".."))
						base += 1;
				} else
					base = curr->fts_pathlen;
D 49
			}
E 49

E 48
			if (to.target_end[-1] != '/') {
				*to.target_end = '/';
				*(to.target_end + 1) = 0;
			}
D 44
			(void)strncat(to.target_end + 1, curr->fts_path, 
                            curr->fts_pathlen);
			to.p_end = to.target_end + curr->fts_pathlen + 1;
E 44
I 44
D 48
			(void)strncat(to.target_end + 1, curr->fts_name, 
                            curr->fts_namelen);
			to.p_end = to.target_end + curr->fts_namelen + 1;
E 48
I 48
D 54
			n = &curr->fts_path[base];
E 54
I 54
			p = &curr->fts_path[base];
E 54
			nlen = curr->fts_pathlen - base;

D 54
			(void)strncat(to.target_end + 1, n, nlen);
E 54
I 54
			(void)strncat(to.target_end + 1, p, nlen);
E 54
			to.p_end = to.target_end + nlen + 1;
E 48
E 44
			*to.p_end = 0;
			STRIP_TRAILING_SLASH(to);
		}

		/* Not an error but need to remember it happened */
		if (stat(to.p_path, &to_stat) == -1)
			dne = 1;
		else {
			if (to_stat.st_dev == curr->fts_statp->st_dev &&
			    to_stat.st_ino == curr->fts_statp->st_ino) {
D 54
				(void)fprintf(stderr,
D 49
			            "%s: %s and %s are identical (not copied).\n",
E 49
I 49
			    "%s: %s and %s are identical (not copied).\n",
E 49
				    progname, to.p_path, curr->fts_path);
				exit_val = 1;
E 54
I 54
				warnx("%s and %s are identical (not copied).",
				    to.p_path, curr->fts_path);
				rval = 1;
E 54
I 52
				if (S_ISDIR(curr->fts_statp->st_mode))
					(void)fts_set(ftsp, curr, FTS_SKIP);
I 55
				continue;
			}
			if (!S_ISDIR(curr->fts_statp->st_mode) &&
			    S_ISDIR(to_stat.st_mode)) {
		warnx("cannot overwrite directory %s with non-directory %s",
				    to.p_path, curr->fts_path);
				rval = 1;
E 55
E 52
D 48
				return;
E 48
I 48
				continue;
E 48
			}
			dne = 0;
		}

D 49
		switch(curr->fts_statp->st_mode & S_IFMT) {
E 49
I 49
		switch (curr->fts_statp->st_mode & S_IFMT) {
E 49
		case S_IFLNK:
D 54
			copy_link(curr, !dne);
E 54
I 54
			if (copy_link(curr, !dne))
				rval = 1;
E 54
			break;
		case S_IFDIR:
D 54
			if (!rflag && !orflag) {
				(void)fprintf(stderr,
				    "%s: %s is a directory (not copied).\n",
				    progname, curr->fts_path);
E 54
I 54
			if (!Rflag && !rflag) {
				warnx("%s is a directory (not copied).",
				    curr->fts_path);
E 54
I 51
				(void)fts_set(ftsp, curr, FTS_SKIP);
E 51
D 54
				exit_val = 1;
E 54
I 54
				rval = 1;
E 54
D 50
				return;
E 50
I 50
				break;
E 50
			}
D 54
			if (dne) {
E 54
E 43
			/*
			 * If the directory doesn't exist, create the new
			 * one with the from file mode plus owner RWX bits,
			 * modified by the umask.  Trade-off between being
			 * able to write the directory (if from directory is
			 * 555) and not causing a permissions race.  If the
D 54
			 * umask blocks owner writes cp fails.
E 54
I 54
			 * umask blocks owner writes, we fail..
E 54
			 */
I 54
			if (dne) {
E 54
D 43
			if (mkdir(to.p_path, from_stat.st_mode|S_IRWXU) < 0) {
D 41
				error(to.p_path);
E 41
I 41
				err("%s: %s", to.p_path, strerror(errno));
E 43
I 43
				if (mkdir(to.p_path, 
D 54
				    curr->fts_statp->st_mode|S_IRWXU) < 0) {
					err("%s: %s", to.p_path, 
					    strerror(errno));
					return;
		                }
E 54
I 54
				    curr->fts_statp->st_mode | S_IRWXU) < 0)
					err(1, "%s", to.p_path);
E 54
D 49
			}
			else if (!S_ISDIR(to_stat.st_mode)) {
E 49
I 49
			} else if (!S_ISDIR(to_stat.st_mode)) {
E 49
D 54
				(void)fprintf(stderr, 
				    "%s: %s: not a directory.\n", progname, 
				    to.p_path);
E 43
E 41
E 22
E 21
				return;
E 54
I 54
				errno = ENOTDIR;
D 56
				err(1, "%s: %s", to.p_path);
E 56
I 56
				err(1, "%s", to.p_path);
E 56
E 54
			}
D 21
			new_target_dir = 1;
E 21
I 21
D 22
			from_stat.st_mode &= ~my_umask;
E 22
E 21
D 43
		}
D 21
		else if ((to_stat.st_mode & S_IFMT) != S_IFDIR) {
			(void)fprintf(stderr,
E 18
D 19
			   "cp: \"%s\": not a directory.\n",
E 19
I 19
			   "cp: %s: not a directory.\n",
E 19
			   to.p_path);
E 21
I 21
D 38
		else if (type(to_stat) != S_IFDIR) {
E 38
I 38
D 42
		else if (!S_ISDIR(to_stat.st_mode) != S_IFDIR) {
E 42
I 42
		else if (!S_ISDIR(to_stat.st_mode)) {
E 42
E 38
D 29
			(void)fprintf(stderr, "cp: %s: not a directory.\n",
			    to.p_path);
E 29
I 29
			(void)fprintf(stderr, "%s: %s: not a directory.\n",
D 38
			    pname, to.p_path);
E 38
I 38
			    progname, to.p_path);
E 38
E 29
E 21
D 18
	    return;
E 18
I 18
			return;
		}
		copy_dir();
I 22
		/*
D 23
		 * If directory didn't exist, set it to be the same as
		 * the from directory, umodified by the umask; arguably
		 * wrong, but it's been that way forever.
E 23
I 23
		 * If not -p and directory didn't exist, set it to be the
		 * same as the from directory, umodified by the umask;
		 * arguably wrong, but it's been that way forever.
E 23
		 */
D 23
		if (dne && !preserve_flag)
E 23
I 23
D 35
		if (preserve_flag)
E 35
I 35
		if (pflag)
E 35
			setfile(&from_stat, 0);
		else if (dne)
E 23
			(void)chmod(to.p_path, from_stat.st_mode);
E 22
I 21
D 36
		break;
E 36
I 36
		return;
E 36
	case S_IFCHR:
	case S_IFBLK:
I 22
D 36
		/*
		 * if recursive flag on, try and create the special device
		 * otherwise copy the contents.
		 */
E 36
E 22
D 35
		if (recursive_flag) {
E 35
I 35
		if (rflag) {
E 35
D 30
			copy_special(&from_stat, &to_stat);
E 30
I 30
			copy_special(&from_stat, !dne);
E 30
D 35
			if (preserve_flag)
E 35
I 35
D 36
			if (pflag)
E 35
D 22
				setfile(&from_stat);
E 22
I 22
				setfile(&from_stat, 0);
E 36
E 22
			return;
		}
D 36
		/* FALLTHROUGH */
	default:
D 22
		if (!copy_file(from_stat.st_mode))
			return;
E 22
I 22
D 26
		copy_file(&from_stat);
E 26
I 26
		copy_file(&from_stat, dne);
E 36
I 36
		break;
	case S_IFIFO:
		if (rflag) {
			copy_fifo(&from_stat, !dne);
			return;
		}
		break;
E 36
E 26
E 22
E 21
E 18
	}
I 36
	copy_file(&from_stat, dne);
E 36
I 18
D 21
	/* Preserve old times/modes if necessary. */
E 21
D 22
	if (preserve_flag)
D 21
		(void)chmod(to.p_path, (int) from_stat.st_mode);
	else if (new_target_dir)
		(void)chmod(to.p_path, (int) from_stat.st_mode & ~my_umask);
	if (preserve_flag || new_target_dir) {
		static struct timeval tv[2];
E 18
E 17

E 14
D 17
		(void) close(fold);
D 3
		if (lstat(to, &stto) < 0) {
E 3
I 3
		if (stat(to, &stto) < 0) {
E 3
D 7
			if (mkdir(to, (int)stfrom.st_mode) < 0)
E 7
I 7
D 10
			if (mkdir(to, (int)stfrom.st_mode) < 0) {
E 10
I 10
D 14
			if (mkdir(to, stfrom.st_mode & 07777) < 0) {
E 14
I 14
			if (mkdir(to, (stfrom.st_mode & 07777) | 0700) < 0) {
E 14
E 10
D 8
				fprintf(stderr, "cp: "); perror(to);
E 8
I 8
				Perror(to);
E 8
E 7
				return (1);
I 7
			}
I 14
			fixmode = 1;
E 14
E 7
		} else if ((stto.st_mode&S_IFMT) != S_IFDIR) {
			fprintf(stderr, "cp: %s: Not a directory.\n", to);
			return (1);
D 13
		}
E 13
I 13
		} else if (pflag)
I 14
			fixmode = 1;
		n = rcopy(from, to);
		if (fixmode)
E 14
			(void) chmod(to, stfrom.st_mode & 07777);
E 13
D 14
		return (rcopy(from, to));
E 14
I 14
		return (n);
E 17
I 17
D 18
	copy_dir();
    }


    /*
     * Preserve old times/modes if necessary.
     */
    if (preserve_flag)
	(void) chmod(to.p_path, (int) from_stat.st_mode);
    else if (new_target_dir)
	(void) chmod(to.p_path, (int) from_stat.st_mode & ~my_umask);

    if (preserve_flag || new_target_dir) {
	static struct timeval tv[2];

	tv[0].tv_sec = from_stat.st_atime;
	tv[1].tv_sec = from_stat.st_mtime;
	if (utimes(to.p_path, tv)) {
	    error(to.p_path);
E 18
I 18
		tv[0].tv_sec = from_stat.st_atime;
		tv[1].tv_sec = from_stat.st_mtime;
		if (utimes(to.p_path, tv))
			error(to.p_path);
E 18
E 17
E 14
	}
E 21
I 21
		setfile(&from_stat);
E 22
E 21
I 17
D 18
    }
E 18
}
E 17
I 10

I 41
static void
E 41
D 17
	if ((stfrom.st_mode&S_IFMT) == S_IFDIR)
		fprintf(stderr,
			"cp: %s: Is a directory (copying as plain file).\n",
				from);
E 17
D 18

E 10
D 3
	if (lstat(to, &stto) >= 0) {
E 3
I 3
D 13
	if (stat(to, &stto) >= 0) {
E 13
I 13
D 17
	exists = stat(to, &stto) == 0;
	if (exists) {
E 13
E 3
		if (stfrom.st_dev == stto.st_dev &&
		   stfrom.st_ino == stto.st_ino) {
D 10
			fprintf(stderr, "cp: Cannot copy file to itself.\n");
E 10
I 10
			fprintf(stderr,
				"cp: %s and %s are identical (not copied).\n",
					from, to);
E 10
I 8
			(void) close(fold);
E 8
			return (1);
		}
D 10
		if (iflag) {
E 10
I 10
		if (iflag && isatty(fileno(stdin))) {
E 10
			int i, c;
E 17

E 18
E 2
D 17
			fprintf (stderr, "overwrite %s? ", to);
			i = c = getchar();
			while (c != '\n' && c != EOF)
				c = getchar();
D 8
			if (i != 'y')
E 8
I 8
			if (i != 'y') {
				(void) close(fold);
E 8
				return(1);
I 8
			}
E 8
		}
E 17
I 17
D 22
copy_file(mode)
D 18
    u_short         mode;	/* Permissions for new file. */
E 18
I 18
D 21
	u_short mode;			/* Permissions for new file. */
E 21
I 21
	u_short mode;			/* permissions for new file. */
E 22
I 22
D 26
copy_file(fs)
E 26
I 26
copy_file(fs, dne)
E 26
	struct stat *fs;
I 26
	int dne;
E 26
E 22
E 21
E 18
{
I 41
	static char buf[MAXBSIZE];
E 41
D 18
    int             from_fd;
    int             to_fd;
    int             rcount;
    int             wcount;
    int             r;
    char            c;
E 18
I 18
D 19
	int from_fd, to_fd, rcount, wcount, r;
	char c;
E 19
I 19
D 21
	int from_fd, to_fd, rcount, wcount;
E 21
I 21
	register int from_fd, to_fd, rcount, wcount;
I 26
	struct stat to_stat;
I 41
	char *p;
E 41
E 26
E 21
E 19
E 18

D 18
    from_fd = open(from.p_path, O_RDONLY, 0);
    if (from_fd == -1) {
	error(from.p_path);
	(void) close(from_fd);
	return 0;
    }
E 18
I 18
D 22
	from_fd = open(from.p_path, O_RDONLY, 0);
	if (from_fd == -1) {
D 21
		error(from.p_path);
E 21
I 21
		error(from.p_path, "open");
E 21
		(void)close(from_fd);
		return(0);
E 22
I 22
	if ((from_fd = open(from.p_path, O_RDONLY, 0)) == -1) {
D 41
		error(from.p_path);
E 41
I 41
		err("%s: %s", from.p_path, strerror(errno));
E 41
		return;
E 22
	}
E 18

D 18
    /*
     * In the interactive case, use O_EXCL to notice existing files. If
     * the file exists, verify with the user.
     */
    to_fd = open(to.p_path,
E 18
I 18
	/*
D 22
	 * In the interactive case, use O_EXCL to notice existing files. If
	 * the file exists, verify with the user.
E 22
I 22
D 26
	 * In the interactive case, use O_EXCL to notice existing files.
	 * If the file exists, verify with the user.
	 *
	 * If the file DNE, create it with the mode of the from file modified
	 * by the umask; arguably wrong but it makes copying executables work
	 * right and it's been that way forever.  The other choice is 666
	 * or'ed with the execute bits on the from file modified by the umask.
E 26
I 26
	 * If the file exists and we're interactive, verify with the user.
	 * If the file DNE, set the mode to be the from file, minus setuid
	 * bits, modified by the umask; arguably wrong, but it makes copying
	 * executables work right and it's been that way forever.  (The
	 * other choice is 666 or'ed with the execute bits on the from file
	 * modified by the umask.)
E 26
E 22
	 */
D 26
	to_fd = open(to.p_path,
E 18
D 20
	     (interactive_flag ? O_EXCL : 0) | O_WRONLY | O_CREAT | O_TRUNC,
		 mode);
E 20
I 20
	    (interactive_flag ? O_EXCL : 0) | O_WRONLY | O_CREAT | O_TRUNC,
D 22
	    mode);
E 22
I 22
	    fs->st_mode);
E 26
I 26
	if (!dne) {
D 35
		if (interactive_flag) {
E 35
I 35
		if (iflag) {
E 35
			int checkch, ch;
E 26
E 22
E 20

D 18
    if (to_fd == -1 && errno == EEXIST && interactive_flag) {
	(void) fprintf(stderr, "overwrite \"%s\"? ", to.p_path);
	r = scanf("%1s", &c);
	if (r != 1 || c != 'y')
	    return FALSE;
E 18
I 18
D 26
	if (to_fd == -1 && errno == EEXIST && interactive_flag) {
D 19
		(void)fprintf(stderr, "overwrite \"%s\"? ", to.p_path);
		r = scanf("%1s", &c);
		if (r != 1 || c != 'y')
E 19
I 19
		int checkch, ch;
E 26
I 26
			(void)fprintf(stderr, "overwrite %s? ", to.p_path);
			checkch = ch = getchar();
			while (ch != '\n' && ch != EOF)
				ch = getchar();
			if (checkch != 'y') {
				(void)close(from_fd);
E 43
I 43
			/*
			 * If not -p and directory didn't exist, set it to be
			 * the same as the from directory, umodified by the 
                         * umask; arguably wrong, but it's been that way 
                         * forever.
			 */
D 54
			if (pflag)
				setfile(curr->fts_statp, 0);
E 54
I 54
			if (pflag && setfile(curr->fts_statp, 0))
				rval = 1;
E 54
			else if (dne)
				(void)chmod(to.p_path, 
				    curr->fts_statp->st_mode);
			break;
D 54
		case S_IFCHR:
E 54
		case S_IFBLK:
D 46
			if (rflag) {
E 46
I 46
D 54
			if (rflag)
E 46
				copy_special(curr->fts_statp, !dne);
E 43
D 46
				return;
			}
I 45
			copy_file(curr, dne);
E 46
I 46
			else
				copy_file(curr, dne);
E 54
I 54
		case S_IFCHR:
			if (Rflag) {
				if (copy_special(curr->fts_statp, !dne))
					rval = 1;
			} else
				if (copy_file(curr, dne))
					rval = 1;
E 54
E 46
E 45
D 43
		}
		to_fd = open(to.p_path, O_WRONLY|O_TRUNC, 0);
	} else
		to_fd = open(to.p_path, O_WRONLY|O_CREAT|O_TRUNC,
		    fs->st_mode & ~(S_ISUID|S_ISGID));
E 26

D 26
		(void)fprintf(stderr, "overwrite %s? ", to.p_path);
		checkch = ch = getchar();
		while (ch != '\n' && ch != EOF)
			ch = getchar();
		if (checkch != 'y')
E 19
D 22
			return(0);
E 22
I 22
			return;
E 22
D 19
		/* Try again. */
E 19
I 19
		/* try again. */
E 19
D 22
		to_fd = open(to.p_path, O_WRONLY | O_CREAT | O_TRUNC, mode);
E 22
I 22
		to_fd = open(to.p_path, O_WRONLY | O_CREAT | O_TRUNC,
		    fs->st_mode);
E 22
	}
E 18

E 26
D 18
	/* Try again. */
	to_fd = open(to.p_path, O_WRONLY | O_CREAT | O_TRUNC, mode);
    }

    if (to_fd == -1) {
	error(to.p_path);
	(void) close(from_fd);
	return FALSE;
    }

    while ((rcount = read(from_fd, buf, MAXBSIZE)) > 0) {
	wcount = write(to_fd, buf, rcount);
	if (rcount != wcount || wcount == -1) {
	    error(from.p_path);
	    break;
E 18
I 18
	if (to_fd == -1) {
D 21
		error(to.p_path);
E 21
I 21
D 22
		error(to.p_path, "open");
E 22
I 22
D 41
		error(to.p_path);
E 41
I 41
		err("%s: %s", to.p_path, strerror(errno));
E 41
E 22
E 21
		(void)close(from_fd);
D 22
		return(0);
E 22
I 22
		return;
E 22
E 18
E 17
	}
D 2
	if ((fnew = creat(to, mode)) < 0) {
		fprintf(stderr, "cp: cannot create %s\n", to);
		close(fold);
		return(1);
E 2
I 2
D 10
	fnew = creat(to, (int)stfrom.st_mode);
E 10
I 10
D 17
	fnew = creat(to, stfrom.st_mode & 07777);
E 10
	if (fnew < 0) {
D 8
		fprintf(stderr, "cp: ");
		perror(to);
E 8
I 8
		Perror(to);
E 8
		(void) close(fold); return(1);
E 2
	}
I 13
	if (exists && pflag)
		(void) fchmod(fnew, stfrom.st_mode & 07777);
			
E 13
D 2
	while(n = read(fold,  iobuf,  BSIZE)) {
E 2
I 2
	for (;;) {
D 10
		n = read(fold, buf, BSIZE);
E 10
I 10
		n = read(fold, buf, sizeof buf);
E 10
		if (n == 0)
			break;
E 2
		if (n < 0) {
D 2
			perror("cp: read");
			close(fold);
			close(fnew);
			return(1);
		} else
			if (write(fnew, iobuf, n) != n) {
				perror("cp: write");
				close(fold);
				close(fnew);
				return(1);
E 2
I 2
D 8
			fprintf(stderr, "cp: "); perror(from);
E 8
I 8
			Perror(from);
E 8
			(void) close(fold); (void) close(fnew); return (1);
		}
		if (write(fnew, buf, n) != n) {
D 8
			fprintf(stderr, "cp: "); perror(to);
E 8
I 8
			Perror(to);
E 8
			(void) close(fold); (void) close(fnew); return (1);
		}
	}
D 11
	(void) close(fold); (void) close(fnew); return (0);
E 11
I 11
	(void) close(fold); (void) close(fnew); 
	if (pflag)
		return (setimes(to, &stfrom));
	return (0);
E 17
I 17
D 18
    }
E 18

D 18
    (void) close(from_fd);
    (void) close(to_fd);
    return TRUE;
E 18
I 18
D 41
	while ((rcount = read(from_fd, buf, MAXBSIZE)) > 0) {
		wcount = write(to_fd, buf, rcount);
		if (rcount != wcount || wcount == -1) {
D 21
			error(from.p_path);
E 21
I 21
D 22
			error(from.p_path, "write");
E 22
I 22
			error(to.p_path);
E 22
E 21
			break;
E 41
I 41
	/*
	 * Mmap and write if less than 8M (the limit is so we don't totally
	 * trash memory on big files.  This is really a minor hack, but it
	 * wins some CPU back.
	 */
	if (fs->st_size <= 8 * 1048576) {
		if ((p = mmap(NULL, fs->st_size, PROT_READ,
		    MAP_FILE, from_fd, (off_t)0)) == (char *)-1)
			err("%s: %s", from.p_path, strerror(errno));
		if (write(to_fd, p, fs->st_size) != fs->st_size)
			err("%s: %s", to.p_path, strerror(errno));
	} else {
		while ((rcount = read(from_fd, buf, MAXBSIZE)) > 0) {
			wcount = write(to_fd, buf, rcount);
			if (rcount != wcount || wcount == -1) {
				err("%s: %s", to.p_path, strerror(errno));
				break;
E 43
I 43
			break;
		case S_IFIFO:
D 46
			if (rflag) {
E 46
I 46
D 54
			if (rflag)
E 46
				copy_fifo(curr->fts_statp, !dne);
E 54
I 54
D 57
			if (Rflag)
E 57
I 57
			if (Rflag) {
E 57
				if (copy_fifo(curr->fts_statp, !dne))
					rval = 1;
E 54
D 46
				return;
E 43
			}
I 45
			copy_file(curr, dne);
E 46
I 46
D 57
			else 
E 57
I 57
			} else 
E 57
D 54
				copy_file(curr, dne);
E 54
I 54
				if (copy_file(curr, dne))
					rval = 1;
E 54
E 46
E 45
I 43
			break;
		default:
D 54
			copy_file(curr, dne);
E 54
I 54
			if (copy_file(curr, dne))
				rval = 1;
E 54
			break;
E 43
E 41
		}
I 41
D 43
		if (rcount < 0)
			err("%s: %s", from.p_path, strerror(errno));
E 43
E 41
	}
I 54
	if (errno)
		err(1, "fts_read");
	return (rval);
E 54
I 22
D 41
	if (rcount < 0)
		error(from.p_path);
E 41
D 35
	if (preserve_flag)
E 35
I 35
D 43
	if (pflag)
E 35
		setfile(fs, to_fd);
I 26
	/*
D 36
	 * If the source was setuid, set the bits on the copy if the copy
	 * was created and is owned by the same uid.  If the source was
	 * setgid, set the bits on the copy if the copy was created and is
	 * owned by the same gid and the user is a member of that group.
I 27
	 * If both setuid and setgid, lose both bits unless all the above
	 * conditions are met.
E 36
I 36
	 * If the source was setuid or setgid, lose the bits unless the
	 * copy is owned by the same user and group.
E 36
E 27
	 */
D 36
	else if (fs->st_mode & (S_ISUID|S_ISGID)) {
D 27
		if (fs->st_mode&S_ISUID && myuid != fs->st_uid)
			fs->st_mode &= ~S_ISUID;
E 27
I 27
		if (fs->st_mode & S_ISUID && myuid != fs->st_uid)
			fs->st_mode &= ~(S_ISUID|S_ISGID);
E 27
		if (fs->st_mode & S_ISGID) {
			if (fstat(to_fd, &to_stat)) {
				error(to.p_path);
D 27
				fs->st_mode &= ~S_ISGID;
E 27
I 27
				fs->st_mode &= ~(S_ISUID|S_ISGID);
E 27
			}
			else if (fs->st_gid != to_stat.st_gid ||
			    !ismember(fs->st_gid))
D 27
				fs->st_mode &= ~S_ISGID;
E 27
I 27
				fs->st_mode &= ~(S_ISUID|S_ISGID);
E 27
		}
		if (fs->st_mode & (S_ISUID|S_ISGID) && fchmod(to_fd,
		    fs->st_mode & (S_ISUID|S_ISGID|S_IRWXU|S_IRWXG|S_IRWXO) &
		    ~myumask))
E 36
I 36
	else if (fs->st_mode & (S_ISUID|S_ISGID) && fs->st_uid == myuid)
		if (fstat(to_fd, &to_stat))
E 36
D 41
			error(to.p_path);
E 41
I 41
			err("%s: %s", to.p_path, strerror(errno));
E 41
D 36
	}
E 36
I 36
#define	RETAINBITS	(S_ISUID|S_ISGID|S_ISVTX|S_IRWXU|S_IRWXG|S_IRWXO)
		else if (fs->st_gid == to_stat.st_gid && fchmod(to_fd,
		    fs->st_mode & RETAINBITS & ~myumask))
D 41
			error(to.p_path);
E 41
I 41
			err("%s: %s", to.p_path, strerror(errno));
E 41
E 36
E 26
E 22
	(void)close(from_fd);
D 40
	(void)close(to_fd);
E 40
I 40
	if (close(to_fd))
D 41
		error(to.p_path);
E 41
I 41
		err("%s: %s", to.p_path, strerror(errno));
E 43
E 41
E 40
D 22
	return(1);
E 22
E 18
E 17
E 11
}

I 41
D 43
static void
E 41
D 17
rcopy(from, to)
	char *from, *to;
E 17
I 17
D 18


E 18
copy_dir()
E 17
{
D 17
	DIR *fold = opendir(from);
	struct direct *dp;
I 11
	struct stat statb;
E 11
	int errs = 0;
D 10
	char fromname[BUFSIZ];
E 10
I 10
	char fromname[MAXPATHLEN + 1];
E 17
I 17
D 18
    struct stat     from_stat;
    char           *old_from;
    char           *old_to;
    struct direct  *dp;
    struct direct **dir_list;
    int             dir_cnt;
    int             i;
E 18
I 18
	struct stat from_stat;
D 22
	char *old_from, *old_to;
E 22
D 39
	struct direct *dp, **dir_list;
E 39
I 39
	struct dirent *dp, **dir_list;
E 39
D 22
	int dir_cnt, i;
E 22
I 22
	register int dir_cnt, i;
	char *old_from, *old_to;
E 43
I 43
/*
D 49
 * Mastercmp() is the comparison function for the copy order.  The order is
 * to copy non-directory files before directory files.  There are two reasons
 * to do directories last.  The first is efficiency.  Files tend to be in the 
 * same cylinder group as their parent, whereas directories tend not to be.
 * Copying files all at once reduces seeking.  Second, deeply nested trees
 * could use up all the file descriptors if we didn't close one directory 
 * before recursively starting on the next.
E 49
I 49
 * mastercmp --
 *	The comparison function for the copy order.  The order is to copy
 *	non-directory files before directory files.  The reason for this
 *	is because files tend to be in the same cylinder group as their
 *	parent directory, whereas directories tend not to be.  Copying the
 *	files first reduces seeking.
E 49
 */
E 43
E 22
E 18
E 17
E 10
D 49

E 49
D 11
	if (fold == 0) {
E 11
I 11
D 17
	if (fold == 0 || (pflag && fstat(fold->dd_fd, &statb) < 0)) {
E 11
D 8
		perror(from);
E 8
I 8
		Perror(from);
E 8
		return (1);
E 17
I 17
D 18
    dir_cnt = scandir(from.p_path, &dir_list, NULL, NULL);
    if (dir_cnt == -1) {
	(void) fprintf(stderr, "cp: Can't read directory \"%s\".\n",
		       from.p_path);
	exit_val = 1;
    }

    /*
     * Copy files first.
     */
    for (i = 0; i < dir_cnt; ++i) {
	dp = dir_list[i];

	if (dp->d_namlen <= 2 && dp->d_name[0] == '.'
	    && (dp->d_name[1] == NULL || dp->d_name[1] == '.')) {
	    free((char *) dp);
	    dir_list[i] = NULL;
	    continue;
E 18
I 18
D 43
	dir_cnt = scandir(from.p_path, &dir_list, NULL, NULL);
	if (dir_cnt == -1) {
D 19
		(void)fprintf(stderr, "cp: Can't read directory \"%s\".\n",
E 19
I 19
D 29
		(void)fprintf(stderr, "cp: can't read directory %s.\n",
E 19
		    from.p_path);
E 29
I 29
		(void)fprintf(stderr, "%s: can't read directory %s.\n",
D 38
		    pname, from.p_path);
E 38
I 38
		    progname, from.p_path);
E 38
E 29
		exit_val = 1;
E 18
E 17
	}
D 17
	for (;;) {
		dp = readdir(fold);
D 4
		if (dp == 0)
E 4
I 4
		if (dp == 0) {
			closedir(fold);
I 11
			if (pflag)
				return (setimes(to, &statb) + errs);
E 11
E 4
			return (errs);
I 4
		}
E 4
		if (dp->d_ino == 0)
			continue;
		if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
			continue;
D 10
		if (strlen(from) + 1 + strlen(dp->d_name) >= BUFSIZ - 1) {
E 10
I 10
		if (strlen(from)+1+strlen(dp->d_name) >= sizeof fromname - 1) {
E 10
			fprintf(stderr, "cp: %s/%s: Name too long.\n",
			    from, dp->d_name);
			errs++;
			continue;
		}
		(void) sprintf(fromname, "%s/%s", from, dp->d_name);
		errs += copy(fromname, to);
E 17
I 17

D 18
	old_from = path_append(&from, dp->d_name, (int) dp->d_namlen);
	if ( !old_from ) {
	    dir_list[i] = NULL;
	    free((char *) dp);
	    continue;
E 17
	}
E 18
I 18
D 22
	/* Copy files first. */
E 22
I 22
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
E 22
	for (i = 0; i < dir_cnt; ++i) {
		dp = dir_list[i];
		if (dp->d_namlen <= 2 && dp->d_name[0] == '.'
D 22
		    && (dp->d_name[1] == NULL || dp->d_name[1] == '.')) {
			(void)free((char *)dp);
			dir_list[i] = NULL;
			continue;
		}
E 22
I 22
		    && (dp->d_name[1] == NULL || dp->d_name[1] == '.'))
			goto done;
E 22
D 41
		old_from = path_append(&from, dp->d_name, (int)dp->d_namlen);
D 22
		if (!old_from) {
			dir_list[i] = NULL;
			(void)free((char *)dp);
			continue;
		}
E 22
I 22
D 38
		if (!old_from)
E 38
I 38
		if (!old_from) {
			exit_val = 1;
E 41
I 41
		if (!(old_from =
		    path_append(&from, dp->d_name, (int)dp->d_namlen)))
E 41
E 38
			goto done;
I 38
D 41
		}
E 41
E 38
E 22
E 18
I 17

D 18
	if (stat(from.p_path, &from_stat) < 0) {
	    error(dp->d_name);
	    path_restore(&from, old_from);
	    continue;
	}
E 18
I 18
D 24
		if (stat(from.p_path, &from_stat) < 0) {
E 24
I 24
		if (statfcn(from.p_path, &from_stat) < 0) {
E 24
D 21
			error(dp->d_name);
E 21
I 21
D 22
			error(dp->d_name, "stat");
E 22
I 22
D 41
			error(dp->d_name);
E 41
I 41
			err("%s: %s", dp->d_name, strerror(errno));
E 41
E 22
E 21
			path_restore(&from, old_from);
I 22
			goto done;
		}
D 38
		if (type(from_stat) == S_IFDIR) {
E 38
I 38
		if (S_ISDIR(from_stat.st_mode)) {
E 38
			path_restore(&from, old_from);
E 22
			continue;
		}
E 18
D 22

D 18
	if ((from_stat.st_mode & S_IFMT) != S_IFDIR) {
	    old_to = path_append(&to, dp->d_name, (int) dp->d_namlen);
	    if ( !old_to ) {
		dir_list[i] = NULL;
		free((char *) dp);
		continue;
	    }

	    copy();

	    path_restore(&to, old_to);

	    dir_list[i] = NULL;
	    free((char *) dp);
E 18
I 18
D 21
		if ((from_stat.st_mode & S_IFMT) != S_IFDIR) {
E 21
I 21
		if (type(from_stat) != S_IFDIR) {
E 21
			old_to = path_append(&to, dp->d_name,
			    (int)dp->d_namlen);
			if (!old_to) {
				dir_list[i] = NULL;
				(void)free((char *)dp);
				continue;
			}
E 22
I 22
D 41
		old_to = path_append(&to, dp->d_name, (int)dp->d_namlen);
		if (old_to) {
E 41
I 41
		if (old_to = path_append(&to, dp->d_name, (int)dp->d_namlen)) {
E 41
E 22
			copy();
			path_restore(&to, old_to);
D 22
			dir_list[i] = NULL;
			(void)free((char *)dp);
E 22
D 38
		}
E 38
I 38
D 41
		} else
			exit_val = 1;
E 41
I 41
		}
E 41
E 38
		path_restore(&from, old_from);
I 22
done:		dir_list[i] = NULL;
D 35
		(void)free((char *)dp);
E 35
I 35
D 41
		(void)free((void *)dp);
E 41
I 41
		free(dp);
E 41
E 35
E 22
E 18
	}
D 18
	path_restore(&from, old_from);
    }
E 18

D 18
    /*
     * Then copy directories.
     */
    for (i = 0; i < dir_cnt; ++i) {
	dp = dir_list[i];
	if (!dp)
	    continue;

	old_from = path_append(&from, dp->d_name, (int) dp->d_namlen);
	if ( !old_from ) {
	    free((char *) dp);
	    continue;
E 18
I 18
D 21
	/* Then copy directories. */
E 21
I 21
D 22
	/* then copy directories. */
E 22
I 22
	/* copy directories */
E 22
E 21
	for (i = 0; i < dir_cnt; ++i) {
		dp = dir_list[i];
		if (!dp)
			continue;
D 41
		old_from = path_append(&from, dp->d_name, (int) dp->d_namlen);
		if (!old_from) {
I 38
			exit_val = 1;
E 38
D 35
			(void)free((char *)dp);
E 35
I 35
			(void)free((void *)dp);
E 41
I 41
		if (!(old_from =
		    path_append(&from, dp->d_name, (int)dp->d_namlen))) {
			free(dp);
E 41
E 35
			continue;
		}
D 41
		old_to = path_append(&to, dp->d_name, (int) dp->d_namlen);
		if (!old_to) {
I 38
			exit_val = 1;
E 38
D 35
			(void)free((char *)dp);
E 35
I 35
			(void)free((void *)dp);
E 41
I 41
		if (!(old_to =
		    path_append(&to, dp->d_name, (int)dp->d_namlen))) {
			free(dp);
E 41
E 35
			path_restore(&from, old_from);
			continue;
		}
		copy();
D 35
		free((char *)dp);
E 35
I 35
D 41
		free((void *)dp);
E 41
I 41
		free(dp);
E 41
E 35
		path_restore(&from, old_from);
		path_restore(&to, old_to);
E 18
	}
D 18

	old_to = path_append(&to, dp->d_name, (int) dp->d_namlen);
	if ( !old_to ) {
	    free((char *) dp);
	    path_restore(&from, old_from);
	    continue;
	}

	copy();
	free((char *) dp);

	path_restore(&from, old_from);
	path_restore(&to, old_to);
    }

    free((char *) dir_list);
E 18
I 18
D 35
	free((char *)dir_list);
E 35
I 35
D 41
	free((void *)dir_list);
E 41
I 41
	free(dir_list);
E 41
E 35
I 20
}

I 41
static void
E 41
copy_link(exists)
	int exists;
E 43
I 43
D 54
static int
E 54
I 54
int
E 54
mastercmp(a, b)
	const FTSENT **a, **b;
E 43
{
I 25
D 43
	int len;
E 25
	char link[MAXPATHLEN];
E 43
I 43
D 49
	int a_info, b_info;
E 49
I 49
D 54
	register int a_info, b_info;
E 54
I 54
	int a_info, b_info;
E 54
E 49
E 43

D 25
	if (readlink(from.p_path, link, sizeof(link)) == -1) {
E 25
I 25
D 43
	if ((len = readlink(from.p_path, link, sizeof(link))) == -1) {
E 25
D 21
		error(from.p_path);
E 21
I 21
D 22
		error(from.p_path, "readlink");
E 22
I 22
D 41
		error(from.p_path);
E 41
I 41
		err("readlink: %s: %s", from.p_path, strerror(errno));
E 41
E 22
E 21
		return;
	}
I 25
	link[len] = '\0';
E 25
	if (exists && unlink(to.p_path)) {
D 21
		error(to.p_path);
E 21
I 21
D 22
		error(to.p_path, "unlink");
E 22
I 22
D 41
		error(to.p_path);
E 41
I 41
		err("unlink: %s: %s", to.p_path, strerror(errno));
E 41
E 22
E 21
		return;
	}
	if (symlink(link, to.p_path)) {
D 21
		error(link);
E 21
I 21
D 22
		error(link, "symlink");
E 22
I 22
D 41
		error(link);
E 41
I 41
		err("symlink: %s: %s", link, strerror(errno));
E 41
E 22
E 21
		return;
	}
E 20
E 18
E 17
I 11
}
E 43
I 43
	a_info = (*a)->fts_info;
	if (a_info == FTS_ERR || a_info == FTS_NS || a_info == FTS_DNR)
D 49
		return 0;
E 49
I 49
		return (0);
E 49
	b_info = (*b)->fts_info;
	if (b_info == FTS_ERR || b_info == FTS_NS || b_info == FTS_DNR)
D 49
		return 0;
E 43

E 49
I 49
		return (0);
E 49
I 41
D 43
static void
E 41
I 36
copy_fifo(from_stat, exists)
	struct stat *from_stat;
	int exists;
{
	if (exists && unlink(to.p_path)) {
D 41
		error(to.p_path);
E 41
I 41
		err("unlink: %s: %s", to.p_path, strerror(errno));
E 41
		return;
	}
	if (mkfifo(to.p_path, from_stat->st_mode)) {
D 41
		error(to.p_path);
E 41
I 41
		err("mkfifo: %s: %s", to.p_path, strerror(errno));
E 41
		return;
	}
	if (pflag)
		setfile(from_stat, 0);
E 43
I 43
	if (a_info == FTS_D)
D 49
		return -1;
E 49
I 49
		return (-1);
E 49
	if (b_info == FTS_D)
D 49
		return 1;
	
	return 0;
E 49
I 49
		return (1);
	return (0);
E 49
E 43
}
D 49

I 41
D 43
static void
E 41
E 36
D 17
int
setimes(path, statp)
	char *path;
	struct stat *statp;
E 17
I 17
D 18


E 18
D 21
error(s)
D 18
    char           *s;
E 18
I 18
	char *s;
E 21
I 21
D 30
copy_special(from_stat, to_stat)
	struct stat *from_stat, *to_stat;
E 30
I 30
copy_special(from_stat, exists)
	struct stat *from_stat;
	int exists;
E 30
E 21
E 18
E 17
{
I 21
D 30
	if (to_stat->st_ino != -1 && unlink(to.p_path)) {
E 30
I 30
	if (exists && unlink(to.p_path)) {
E 30
D 22
		error(to.p_path, "unlink");
E 22
I 22
D 41
		error(to.p_path);
E 41
I 41
		err("unlink: %s: %s", to.p_path, strerror(errno));
E 41
E 22
		return;
	}
	if (mknod(to.p_path, from_stat->st_mode,  from_stat->st_rdev)) {
D 22
		error(to.p_path, "mknod");
E 22
I 22
D 41
		error(to.p_path);
E 41
I 41
		err("mknod: %s: %s", to.p_path, strerror(errno));
E 41
E 22
		return;
	}
I 36
	if (pflag)
		setfile(from_stat, 0);
E 36
}
E 43

I 41
D 43
static void
E 41
D 22
setfile(fs)
	struct stat *fs;
E 22
I 22
setfile(fs, fd)
	register struct stat *fs;
	int fd;
E 22
{
	static struct timeval tv[2];
E 43
I 37
D 41
	char path[100];
E 41
E 37
I 22
D 26
	static int dochown = 1;
E 26
I 26
D 27
	static enum { SUCCEEDED, FAILED, PERMFAIL } dochown = SUCCEEDED;
E 27
E 26
E 22

I 34
D 43
	fs->st_mode &= S_ISUID|S_ISGID|S_IRWXU|S_IRWXG|S_IRWXO;
E 43

E 34
D 22
	if (chown(to.p_path, fs->st_uid, fs->st_gid))
		error(to.p_path, "chown");
	if (chmod(to.p_path, fs->st_mode))
		error(to.p_path, "chmod");
E 22
D 43
	tv[0].tv_sec = fs->st_atime;
	tv[1].tv_sec = fs->st_mtime;
D 37
	if (utimes(to.p_path, tv))
D 22
		error(to.p_path, "utimes");
E 22
I 22
		error(to.p_path);
E 37
I 37
D 41
	if (utimes(to.p_path, tv)) {
		(void)snprintf(path, sizeof(path), "utimes: %s", to.p_path);
		error(path);
	}
E 41
I 41
	if (utimes(to.p_path, tv))
		err("utimes: %s: %s", to.p_path, strerror(errno));
E 41
E 37
	/*
D 26
	 * Changing the ownership probably won't succeed, unless we're
	 * root or POSIX_CHOWN_RESTRICTED is not set.  Try it last so
	 * everything else gets set first.
E 26
I 26
D 27
	 * Changing the ownership probably won't succeed, unless we're root or
	 * POSIX_CHOWN_RESTRICTED is not set.  Set uid before setting the mode;
	 * current BSD behavior is to remove all setuid bits on chown.  If the
	 * chown doesn't succeed, turn off all setuid bits.
E 27
I 27
	 * Changing the ownership probably won't succeed, unless we're root
D 34
	 * or POSIX_CHOWN_RESTRICTED is not set.  Set uid before setting the
	 * mode; current BSD behavior is to remove all setuid bits on chown.
	 * If setuid, lose the bits if chown fails.
	 * If setgid, lose the bits if chgrp fails.
	 * If both, lose the bits if either fails.
E 34
I 34
	 * or POSIX_CHOWN_RESTRICTED is not set.  Set uid/gid before setting
	 * the mode; current BSD behavior is to remove all setuid bits on
	 * chown.  If chown fails, lose setuid/setgid bits.
E 34
E 27
E 26
	 */
D 26
	if (fd) {
		if (fchmod(fd, fs->st_mode))
			error(to.p_path);
		if (dochown && fchown(fd, fs->st_uid, fs->st_gid) == -1)
E 26
I 26
D 27
	if (dochown != PERMFAIL) {
		if ((fd ? fchown(fd, fs->st_uid, fs->st_gid) :
		    chown(to.p_path, fs->st_uid, fs->st_gid)))
E 26
			if (errno == EPERM)
D 26
				dochown = 0;
			else
E 26
I 26
				dochown = PERMFAIL;
			else {
				dochown = FAILED;
E 26
				error(to.p_path);
D 26
	} else {
		if (chmod(to.p_path, fs->st_mode))
			error(to.p_path);
		if (dochown && chown(to.p_path, fs->st_uid, fs->st_gid) == -1)
			if (errno == EPERM)
				dochown = 0;
			else
				error(to.p_path);
E 26
I 26
			}
		else
			dochown = SUCCEEDED;
E 27
I 27
D 34
	if ((fd ?
	    fchown(fd, fs->st_uid, -1) : chown(to.p_path, fs->st_uid, -1))) {
E 34
I 34
	if (fd ? fchown(fd, fs->st_uid, fs->st_gid) :
	    chown(to.p_path, fs->st_uid, fs->st_gid)) {
E 34
D 37
		if (errno != EPERM)
			error(to.p_path);
E 37
I 37
D 41
		if (errno != EPERM) {
			(void)snprintf(path, sizeof(path),
			    "chown: %s", to.p_path);
			error(path);
		}
E 41
I 41
		if (errno != EPERM)
			err("chown: %s: %s", to.p_path, strerror(errno));
E 41
E 37
D 34
		if (fs->st_mode & S_ISUID)
			fs->st_mode &= ~(S_ISUID|S_ISGID);
E 34
I 34
		fs->st_mode &= ~(S_ISUID|S_ISGID);
E 34
E 27
E 26
	}
I 26
D 27
	if (dochown != SUCCEEDED)
		fs->st_mode &= ~(S_ISUID|S_ISGID);
E 27
I 27
D 34
	if ((fd ?
	    fchown(fd, -1, fs->st_gid) : chown(to.p_path, -1, fs->st_gid))) {
		if (errno != EPERM)
			error(to.p_path);
		if (fs->st_mode & S_ISGID)
			fs->st_mode &= ~(S_ISUID|S_ISGID);
	}
E 27
	fs->st_mode &= S_ISUID|S_ISGID|S_IRWXU|S_IRWXG|S_IRWXO;
E 34
D 37
	if (fd ? fchmod(fd, fs->st_mode) : chmod(to.p_path, fs->st_mode))
		error(to.p_path);
E 37
I 37
D 41
	if (fd ? fchmod(fd, fs->st_mode) : chmod(to.p_path, fs->st_mode)) {
		(void)snprintf(path, sizeof(path), "chown: %s", to.p_path);
		error(path);
	}
E 41
I 41
	if (fd ? fchmod(fd, fs->st_mode) : chmod(to.p_path, fs->st_mode))
		err("chown: %s: %s", to.p_path, strerror(errno));
E 41
E 37
}
E 43

D 38
ismember(gid)
	gid_t gid;
{
D 31
	extern int errno;
E 31
	register int cnt;
	static int ngroups, groups[NGROUPS];

	if (!ngroups) {
		ngroups = getgroups(NGROUPS, groups);
		if (ngroups == -1) {
			ngroups = 0;
			exit_val = 1;
D 29
			(void)fprintf(stderr, "cp: %s\n", strerror(errno));
E 29
I 29
			(void)fprintf(stderr, "%s: %s\n",
			    pname, strerror(errno));
E 29
			return(0);
		}
	}
	for (cnt = ngroups; cnt--;)
		if (gid == groups[cnt])
			return(1);
	return(0);
E 26
E 22
}

E 38
D 22
error(s, call)
	char *s, *call;
E 22
I 22
D 41
error(s)
	char *s;
E 22
{
E 21
D 17
	struct timeval tv[2];
	
	tv[0].tv_sec = statp->st_atime;
	tv[1].tv_sec = statp->st_mtime;
	tv[0].tv_usec = tv[1].tv_usec = 0;
	if (utimes(path, tv) < 0) {
		Perror(path);
		return (1);
	}
	return (0);
E 17
I 17
D 18
    exit_val = 1;
    (void) fprintf(stderr, "cp: ");
    perror(s);
E 18
I 18
D 31
	extern int errno;

E 31
	exit_val = 1;
D 21
	(void)fprintf(stderr, "cp: %s: %s\n", s, strerror(errno));
E 21
I 21
D 22
	(void)fprintf(stderr, "cp: %s: %s: %s\n", call, s, strerror(errno));
E 22
I 22
D 29
	(void)fprintf(stderr, "cp: %s: %s\n", s, strerror(errno));
E 29
I 29
D 38
	(void)fprintf(stderr, "%s: %s: %s\n", pname, s, strerror(errno));
E 29
E 22
E 21
E 18
E 17
E 11
I 8
}

D 17
Perror(s)
	char *s;
E 17
I 17
D 18


E 18
/********************************************************************
 * Path Manipulation Routines.
 ********************************************************************/

/*
D 28
 * These functions manipulate paths in "path_t" structures.
E 28
I 28
 * These functions manipulate paths in PATH_T structures.
E 28
 * 
 * They eliminate multiple slashes in paths when they notice them, and keep
 * the path non-slash terminated.
 *
D 18
 * Both path_set() and path_append() return FALSE if the requested name
E 18
I 18
 * Both path_set() and path_append() return 0 if the requested name
E 18
 * would be too long.
 */

D 18
#define STRIP_TRAILING_SLASH(p) \
    while ((p)->p_end > (p)->p_path && (p)->p_end[-1] == '/') \
	{ *--(p)->p_end = 0; };
E 18
I 18
#define	STRIP_TRAILING_SLASH(p) { \
	while ((p)->p_end > (p)->p_path && (p)->p_end[-1] == '/') \
		*--(p)->p_end = 0; \
	}
E 18

/*
 * Move specified string into path.  Convert "" to "." to handle BSD
 * semantics for a null path.  Strip trailing slashes.
 */
path_set(p, string)
D 18
    path_t         *p;
    char           *string;
E 18
I 18
D 28
	register path_t *p;
E 28
I 28
	register PATH_T *p;
E 28
	char *string;
E 18
E 17
{
I 17
D 18
    int len;
E 18
I 18
	if (strlen(string) > MAXPATHLEN) {
D 19
		fprintf(stderr, "cp: \"%s\": Name too long.\n", string);
E 19
I 19
D 22
		fprintf(stderr, "cp: %s: name too long.\n", string);
E 22
I 22
D 29
		(void)fprintf(stderr, "cp: %s: name too long.\n", string);
E 29
I 29
		(void)fprintf(stderr, "%s: %s: name too long.\n",
		    pname, string);
E 29
E 22
E 19
		exit_val = 1;
		return(0);
	}
E 18
E 17

D 17
	fprintf(stderr, "cp: ");
	perror(s);
E 17
I 17
D 18
    if (strlen(string) > MAXPATHLEN) {
	fprintf(stderr, "cp: \"%s\": Name too long.\n", string);
	exit_val = 1;
	return FALSE;
    }
E 18
I 18
	(void)strcpy(p->p_path, string);
	p->p_end = p->p_path + strlen(p->p_path);
E 18

D 18
    (void) strcpy(p->p_path, string);
    p->p_end = p->p_path + strlen(p->p_path);
E 18
I 18
	if (p->p_path == p->p_end) {
		*p->p_end++ = '.';
		*p->p_end = 0;
	}
E 18

D 18
    if (p->p_path == p->p_end) {
	*p->p_end++ = '.';
	*p->p_end = 0;
    }

    STRIP_TRAILING_SLASH(p);
    
    return TRUE;
E 18
I 18
	STRIP_TRAILING_SLASH(p);
	return(1);
E 18
}

/*
 * Append specified string to path, inserting '/' if necessary.  Return a
 * pointer to the old end of path for restoration.
 */
D 18
char           *
E 18
I 18
char *
E 18
path_append(p, name, len)
D 18
    path_t         *p;
    char           *name;
    int             len;
E 18
I 18
D 28
	register path_t *p;
E 28
I 28
	register PATH_T *p;
E 28
	char *name;
	int len;
E 18
{
D 18
    char           *old;
E 18
I 18
	char *old;
E 18

D 18
    old = p->p_end;
E 18
I 18
	old = p->p_end;
	if (len == -1)
		len = strlen(name);
E 18

D 18
    if (len == -1)
	len = strlen(name);
E 18
I 18
	/*
	 * The final "+ 1" accounts for the '/' between old path and name.
	 */
	if ((len + p->p_end - p->p_path + 1) > MAXPATHLEN) {
D 22
		fprintf(stderr,
E 22
I 22
		(void)fprintf(stderr,
E 22
D 19
		    "cp: \"%s/%s\": Name too long.\n", p->p_path, name);
E 19
I 19
D 29
		    "cp: %s/%s: name too long.\n", p->p_path, name);
E 29
I 29
		    "%s: %s/%s: name too long.\n", pname, p->p_path, name);
E 29
E 19
		exit_val = 1;
		return(0);
	}
E 18

D 18
    /*
     * The final "+ 1" accounts for the '/' between old path and name.
     */
    if ( (len + p->p_end - p->p_path + 1) > MAXPATHLEN ) {
	fprintf(stderr, "cp: \"%s/%s\": Name too long.\n", p->p_path, name);
	exit_val = 1;
	return FALSE;
    }
E 18
I 18
	/*
	 * This code should always be executed, since paths shouldn't
	 * end in '/'.
	 */
	if (p->p_end[-1] != '/') {
		*p->p_end++ = '/';
		*p->p_end = 0;
	}
E 18

D 18
    /*
     * This code should always be executed, since paths shouldn't
     * end in '/'.
     */
    if (p->p_end[-1] != '/') {
	*p->p_end++ = '/';
E 18
I 18
	(void)strncat(p->p_end, name, len);
	p->p_end += len;
E 18
	*p->p_end = 0;
D 18
    }
E 18

D 18
    (void) strncat(p->p_end, name, len);
    p->p_end += len;
    *p->p_end = 0;

    STRIP_TRAILING_SLASH(p);

    return old;
E 18
I 18
	STRIP_TRAILING_SLASH(p);
	return(old);
E 18
}

D 18

E 18
/*
 * Restore path to previous value.  (As returned by path_append.)
 */
D 28
void
E 28
path_restore(p, old)
D 18
    path_t         *p;
    char           *old;
E 18
I 18
D 28
	path_t *p;
E 28
I 28
	PATH_T *p;
E 28
	char *old;
E 18
{
D 18
    p->p_end = old;
    *p->p_end = 0;
E 18
I 18
	p->p_end = old;
	*p->p_end = 0;
E 18
}

D 18

E 18
/*
 * Return basename of path.  (Like basename(1).)
 */
D 18
char           *
E 18
I 18
char *
E 18
path_basename(p)
D 18
    path_t         *p;
E 18
I 18
D 28
	path_t *p;
E 28
I 28
	PATH_T *p;
E 28
E 18
{
D 18
    char           *basename;
E 18
I 18
	char *basename;
E 18

D 18
    basename = rindex(p->p_path, '/');
E 18
I 18
	basename = rindex(p->p_path, '/');
D 22
	if (!basename)
		basename = p->p_path;
	return(basename);
E 22
I 22
	return(basename ? ++basename : p->p_path);
E 38
I 38
	(void)fprintf(stderr, "%s: %s: %s\n", progname, s, strerror(errno));
E 38
E 22
}
E 18

E 41
I 41
D 43
static void
E 41
D 18
    if (!basename)
	basename = p->p_path;

    return basename;
E 18
I 18
usage()
{
	(void)fprintf(stderr,
D 28
	   "usage: cp [-ip] f1 f2; or: cp [-irp] f1 ... fn directory\n");
E 28
I 28
D 36
"usage: cp [-fhipr] src target;\n   or: cp [-fhipr] src1 ... srcN directory\n");
E 36
I 36
D 41
"usage: cp [-Rfhip] src target;\n   or: cp [-Rfhip] src1 ... srcN directory\n");
E 41
I 41
"usage: cp [-Rfhip] src target;\n       cp [-Rfhip] src1 ... srcN directory\n");
E 41
E 36
E 28
	exit(1);
I 41
}
E 43

D 43
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
E 43

E 49
D 43
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
E 41
E 18
E 17
E 8
D 7
}

mkdir(name, mode)
	char *name;
	int mode;
{
	char *argv[4];
	int pid, rc;

	argv[0] = "mkdir";
	argv[1] = name;
	argv[2] = 0;
	pid = fork();
	if (pid < 0) {
		perror("cp");
		return (1);
	}
	if (pid) {
		while (wait(&rc) != pid)
			continue;
		if (rc == 0)
			if (chmod(name, mode) < 0) {
				perror(name);
				rc = 1;
E 2
			}
I 2
		return (rc);
E 2
	}
D 2
	close(fold);
	close(fnew);
	return(0);
E 2
I 2
	execv("/bin/mkdir", argv);
	execv("/usr/bin/mkdir", argv);
	perror("mkdir");
	_exit(1);
	/*NOTREACHED*/
E 7
E 2
}
E 43
E 1
