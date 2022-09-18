h19084
s 00002/00000/00047
d D 8.3 94/09/29 08:12:02 pendry 21 20
c suppress whiteouts when reading a non-unioned directory.
e
s 00009/00008/00038
d D 8.2 94/07/28 03:38:34 pendry 20 19
c changes for whiteouts and union filesystem
e
s 00002/00002/00044
d D 8.1 93/06/04 12:04:40 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00045
d D 5.7 90/06/01 14:13:32 bostic 18 17
c new copyright notice
e
s 00003/00003/00053
d D 5.6 89/07/10 15:15:49 mckusick 17 16
c update to use getdirentries
e
s 00004/00004/00052
d D 5.5 89/01/11 16:44:40 mckusick 16 15
c modifications to use POSIX defined <dirent.h>
e
s 00014/00003/00042
d D 5.4 88/06/18 15:12:24 bostic 15 14
c install approved copyright notice
e
s 00002/00000/00043
d D 5.3 88/06/18 10:46:29 bostic 14 13
c ls -f /vmunix was dropping core
e
s 00002/00002/00041
d D 5.2 86/03/09 19:53:51 donn 13 12
c added LIBC_SCCS condition for sccs ids
e
s 00007/00001/00036
d D 5.1 85/05/30 10:49:05 dist 12 11
c Add copyright
e
s 00004/00004/00033
d D 4.5 83/07/01 18:32:44 sam 11 10
c include fixes
e
s 00008/00021/00029
d D 4.4 82/05/07 20:36:17 mckusick 10 9
c update to new fs
e
s 00001/00001/00049
d D 4.3 82/03/30 13:15:27 mckusic 9 8
c convert to DEV_BSIZE size directory blocks
e
s 00001/00000/00049
d D 4.2 82/03/12 10:37:04 mckusic 8 7
c insure null termination of directory name
e
s 00000/00000/00049
d D 4.1 82/02/21 14:49:20 mckusic 7 6
c convert to version number 4.x
e
s 00006/00013/00043
d D 1.5 82/02/16 20:42:28 mckusic 6 5
c changes to reflect new names in ndir.h
e
s 00012/00000/00044
d D 1.4 82/02/12 01:42:42 mckusic 5 4
c get rid of old style directory entries (known only in readdir.c)
e
s 00016/00005/00028
d D 1.3 82/02/12 01:25:00 mckusic 4 2
c convert to new style directory headers
e
s 00015/00004/00029
d R 1.3 82/02/12 00:37:25 mckusic 3 2
c convert to new style directory headers
e
s 00003/00002/00030
d D 1.2 82/02/11 23:32:31 mckusic 2 1
c fix () and sizeof errors
e
s 00032/00000/00000
d D 1.1 82/02/11 12:01:30 mckusick 1 0
c date and time created 82/02/11 12:01:30 by mckusick
e
u
U
t
T
I 12
/*
D 19
 * Copyright (c) 1983 Regents of the University of California.
D 15
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 15
I 15
 * All rights reserved.
E 19
I 19
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 19
 *
D 18
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
E 18
I 18
 * %sccs.include.redist.c%
E 18
E 15
 */

E 12
I 1
D 11
/* Copyright (c) 1982 Regents of the University of California */
E 11
I 11
D 13
#ifndef lint
E 13
I 13
#if defined(LIBC_SCCS) && !defined(lint)
E 13
static char sccsid[] = "%W% (Berkeley) %G%";
D 12
#endif
E 12
I 12
D 13
#endif not lint
E 13
I 13
D 15
#endif LIBC_SCCS and not lint
E 15
I 15
#endif /* LIBC_SCCS and not lint */
E 15
E 13
E 12
E 11

D 11
static char sccsid[] = "%Z%%M% %I% %G%";

E 11
D 9
#include <sys/types.h>
E 9
I 9
#include <sys/param.h>
E 9
D 10
#include <ndir.h>
E 10
I 10
D 11
#include <dir.h>
E 11
I 11
D 16
#include <sys/dir.h>
E 16
I 16
#include <dirent.h>
E 16
E 11
E 10

/*
I 5
D 10
 * read an old stlye directory entry and present it as a new one
 */
D 6
#ifndef	DIRSIZ
#define	DIRSIZ	14
#endif
E 6
I 6
#define	ODIRSIZ	14
E 6

struct	olddirect {
	ino_t	d_ino;
D 6
	char	d_name[DIRSIZ];
E 6
I 6
	char	d_name[ODIRSIZ];
E 6
};

/*
E 10
E 5
 * get next entry in a directory.
 */
D 16
struct direct *
E 16
I 16
struct dirent *
E 16
readdir(dirp)
	register DIR *dirp;
{
D 4
	struct direct *dp;
E 4
I 4
D 10
	register struct olddirect *dp;
D 6
	static union {
		struct direct un_dir;
		char pad[MAXDIRSIZ];
	} dirun;
#define dir dirun.un_dir
E 6
I 6
	static struct direct dir;
E 10
I 10
D 16
	register struct direct *dp;
E 16
I 16
	register struct dirent *dp;
E 16
E 10
E 6
E 4

	for (;;) {
D 20
		if (dirp->dd_loc == 0) {
E 20
I 20
		if (dirp->dd_loc >= dirp->dd_size) {
			if (dirp->dd_flags & __DTF_READALL)
				return (NULL);
			dirp->dd_loc = 0;
		}
		if (dirp->dd_loc == 0 && !(dirp->dd_flags & __DTF_READALL)) {
E 20
D 2
			dirp->dd_size = read(dirp->dd_fd, dirp->dd_buf, DIRSIZ);
E 2
I 2
D 17
			dirp->dd_size = read(dirp->dd_fd, dirp->dd_buf, 
D 6
			    MAXDIRSIZ);
E 6
I 6
			    DIRBLKSIZ);
E 17
I 17
			dirp->dd_size = getdirentries(dirp->dd_fd,
			    dirp->dd_buf, dirp->dd_len, &dirp->dd_seek);
E 17
E 6
E 2
			if (dirp->dd_size <= 0)
D 20
				return NULL;
E 20
I 20
				return (NULL);
E 20
		}
D 20
		if (dirp->dd_loc >= dirp->dd_size) {
			dirp->dd_loc = 0;
			continue;
		}
E 20
D 2
		dp = (struct direct *)dirp->dd_buf + dirp->dd_loc;
E 2
I 2
D 4
		dp = (struct direct *)(dirp->dd_buf + dirp->dd_loc);
E 2
		dirp->dd_loc += sizeof(struct direct);
		if (dp->d_ino != 0)
			return dp;
E 4
I 4
D 10
		dp = (struct olddirect *)(dirp->dd_buf + dirp->dd_loc);
		dirp->dd_loc += sizeof(struct olddirect);
E 10
I 10
D 16
		dp = (struct direct *)(dirp->dd_buf + dirp->dd_loc);
E 16
I 16
		dp = (struct dirent *)(dirp->dd_buf + dirp->dd_loc);
E 16
I 14
		if ((int)dp & 03)	/* bogus pointer check */
D 20
			return NULL;
E 20
I 20
			return (NULL);
E 20
E 14
		if (dp->d_reclen <= 0 ||
D 17
		    dp->d_reclen > DIRBLKSIZ + 1 - dirp->dd_loc)
E 17
I 17
		    dp->d_reclen > dirp->dd_len + 1 - dirp->dd_loc)
E 17
D 20
			return NULL;
E 20
I 20
			return (NULL);
E 20
		dirp->dd_loc += dp->d_reclen;
E 10
		if (dp->d_ino == 0)
			continue;
I 21
		if (dp->d_type == DT_WHT && (dirp->dd_flags & DTF_HIDEW))
			continue;
E 21
D 10
		dir.d_ino = dp->d_ino;
D 6
		strncpy(dir.d_name, dp->d_name, DIRSIZ);
E 6
I 6
		strncpy(dir.d_name, dp->d_name, ODIRSIZ);
I 8
		dir.d_name[ODIRSIZ] = '\0'; /* insure null termination */
E 8
E 6
		dir.d_namlen = strlen(dir.d_name);
D 6
		dir.d_reclen = ((sizeof(struct direct) + dir.d_namlen)
		    + 4) & ~03;
E 6
I 6
		dir.d_reclen = DIRSIZ(&dir);
E 6
		return (&dir);
E 10
I 10
		return (dp);
E 10
E 4
	}
}
E 1
