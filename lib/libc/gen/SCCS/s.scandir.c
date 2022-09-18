h64342
s 00007/00006/00102
d D 8.3 94/01/02 13:08:39 bostic 16 15
c prettiness police
e
s 00001/00001/00107
d D 8.2 94/01/02 13:06:22 bostic 15 14
c Help scandir compile on systems such as SVR4 where "d_name[]", in
c "struct dirent", is declared as having one member rather than
c MAXNAMLEN+1 members.  (It still may require that an "__P()" macro be
c provided, but, once the last compiler that doesn't support prototypes
c dies, "__P()" can be nuked - SVR4's compilers should all support
c prototypes.)
c From: guy@auspex.com (Guy Harris)
e
s 00002/00002/00106
d D 8.1 93/06/04 12:04:48 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00004/00098
d D 5.10 91/02/23 19:50:01 donn 13 12
c Add include files to get prototype declarations, and fix bugs found.
e
s 00003/00002/00099
d D 5.9 90/06/24 12:04:15 bostic 12 11
c can be `char *' or `void *' according to ANSI C, but the types of
c scandir, qsort and alphasort should agree.
e
s 00001/00001/00100
d D 5.8 90/06/23 16:40:21 bostic 11 10
c syntactic sugar
e
s 00001/00011/00100
d D 5.7 90/06/01 14:13:59 bostic 10 9
c new copyright notice
e
s 00001/00002/00110
d D 5.6 89/02/05 15:45:58 bostic 9 8
c use bcopy to copy file names, we know the length
e
s 00010/00000/00102
d D 5.5 89/01/16 16:42:37 mckusick 8 7
c add DIRSIZ macro for internal use
e
s 00010/00010/00092
d D 5.4 89/01/11 16:44:42 mckusick 7 6
c modifications to use POSIX defined <dirent.h>
e
s 00014/00003/00088
d D 5.3 88/06/18 15:12:26 bostic 6 5
c install approved copyright notice
e
s 00002/00002/00089
d D 5.2 86/03/09 19:54:39 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00007/00001/00084
d D 5.1 85/05/30 10:50:04 dist 4 3
c Add copyright
e
s 00004/00001/00081
d D 4.3 83/12/05 15:24:31 ralph 3 2
c arraysz not recomputed if overflow.
e
s 00005/00002/00077
d D 4.2 83/07/01 18:32:50 sam 2 1
c include fixes
e
s 00079/00000/00000
d D 4.1 82/12/13 10:43:38 ralph 1 0
c date and time created 82/12/13 10:43:38 by ralph
e
u
U
t
T
I 4
/*
D 14
 * Copyright (c) 1983 Regents of the University of California.
D 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 10
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 6
 */

E 4
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
D 5
#ifndef lint
E 5
I 5
#if defined(LIBC_SCCS) && !defined(lint)
E 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif
E 4
I 4
D 5
#endif not lint
E 5
I 5
D 6
#endif LIBC_SCCS and not lint
E 6
I 6
#endif /* LIBC_SCCS and not lint */
E 6
E 5
E 4

E 2
/*
 * Scan the directory dirname calling select to make a list of selected
 * directory entries then sort using qsort and compare routine dcomp.
 * Returns the number of entries and a pointer to a list of pointers to
D 7
 * struct direct (through namelist). Returns -1 if there were any errors.
E 7
I 7
 * struct dirent (through namelist). Returns -1 if there were any errors.
E 7
 */

#include <sys/types.h>
#include <sys/stat.h>
D 2
#include <dir.h>
E 2
I 2
D 7
#include <sys/dir.h>
E 7
I 7
#include <dirent.h>
I 13
#include <stdlib.h>
#include <string.h>
E 13
E 7
E 2

I 8
/*
D 16
 * The DIRSIZ macro gives the minimum record length which will hold
 * the directory entry.  This requires the amount of space in struct dirent
 * without the d_name field, plus enough space for the name with a terminating
 * null byte (dp->d_namlen+1), rounded up to a 4 byte boundary.
E 16
I 16
 * The DIRSIZ macro is the minimum record length which will hold the directory
 * entry.  This requires the amount of space in struct dirent without the
 * d_name field, plus enough space for the name and a terminating nul byte
 * (dp->d_namlen + 1), rounded up to a 4 byte boundary.
E 16
 */
#undef DIRSIZ
D 16
#define DIRSIZ(dp) \
D 15
    ((sizeof (struct dirent) - (MAXNAMLEN+1)) + (((dp)->d_namlen+1 + 3) &~ 3))
E 15
I 15
    ((sizeof (struct dirent) - sizeof (dp)->d_name) + (((dp)->d_namlen+1 + 3) &~ 3))
E 16
I 16
#define DIRSIZ(dp)							\
	((sizeof(struct dirent) - sizeof(dp)->d_name) +			\
	    (((dp)->d_namlen + 1 + 3) &~ 3))
E 16
E 15

I 13
int
E 13
E 8
scandir(dirname, namelist, select, dcomp)
D 13
	char *dirname;
E 13
I 13
	const char *dirname;
E 13
D 7
	struct direct *(*namelist[]);
E 7
I 7
D 11
	struct dirent *(*namelist[]);
E 11
I 11
	struct dirent ***namelist;
E 11
E 7
D 13
	int (*select)(), (*dcomp)();
E 13
I 13
	int (*select) __P((struct dirent *));
	int (*dcomp) __P((const void *, const void *));
E 13
{
D 7
	register struct direct *d, *p, **names;
E 7
I 7
	register struct dirent *d, *p, **names;
E 7
D 13
	register int nitems;
E 13
I 13
	register size_t nitems;
E 13
D 9
	register char *cp1, *cp2;
E 9
	struct stat stb;
	long arraysz;
	DIR *dirp;

	if ((dirp = opendir(dirname)) == NULL)
		return(-1);
	if (fstat(dirp->dd_fd, &stb) < 0)
		return(-1);

	/*
	 * estimate the array size by taking the size of the directory file
	 * and dividing it by a multiple of the minimum size entry. 
	 */
	arraysz = (stb.st_size / 24);
D 7
	names = (struct direct **)malloc(arraysz * sizeof(struct direct *));
E 7
I 7
	names = (struct dirent **)malloc(arraysz * sizeof(struct dirent *));
E 7
	if (names == NULL)
		return(-1);

	nitems = 0;
	while ((d = readdir(dirp)) != NULL) {
		if (select != NULL && !(*select)(d))
			continue;	/* just selected names */
		/*
		 * Make a minimum size copy of the data
		 */
D 7
		p = (struct direct *)malloc(DIRSIZ(d));
E 7
I 7
		p = (struct dirent *)malloc(DIRSIZ(d));
E 7
		if (p == NULL)
			return(-1);
		p->d_ino = d->d_ino;
		p->d_reclen = d->d_reclen;
		p->d_namlen = d->d_namlen;
D 9
		for (cp1 = p->d_name, cp2 = d->d_name; *cp1++ = *cp2++; );
E 9
I 9
		bcopy(d->d_name, p->d_name, p->d_namlen + 1);
E 9
		/*
		 * Check to make sure the array has space left and
		 * realloc the maximum size.
		 */
		if (++nitems >= arraysz) {
I 3
			if (fstat(dirp->dd_fd, &stb) < 0)
				return(-1);	/* just might have grown */
			arraysz = stb.st_size / 12;
E 3
D 7
			names = (struct direct **)realloc((char *)names,
D 3
				(stb.st_size/12) * sizeof(struct direct *));
E 3
I 3
				arraysz * sizeof(struct direct *));
E 7
I 7
			names = (struct dirent **)realloc((char *)names,
				arraysz * sizeof(struct dirent *));
E 7
E 3
			if (names == NULL)
				return(-1);
		}
		names[nitems-1] = p;
	}
	closedir(dirp);
	if (nitems && dcomp != NULL)
D 7
		qsort(names, nitems, sizeof(struct direct *), dcomp);
E 7
I 7
		qsort(names, nitems, sizeof(struct dirent *), dcomp);
E 7
	*namelist = names;
	return(nitems);
}

/*
 * Alphabetic order comparison routine for those who want it.
 */
I 13
int
E 13
alphasort(d1, d2)
D 7
	struct direct **d1, **d2;
E 7
I 7
D 12
	struct dirent **d1, **d2;
E 12
I 12
D 13
	void *d1, *d2;
E 13
I 13
	const void *d1;
	const void *d2;
E 13
E 12
E 7
{
D 12
	return(strcmp((*d1)->d_name, (*d2)->d_name));
E 12
I 12
	return(strcmp((*(struct dirent **)d1)->d_name,
	    (*(struct dirent **)d2)->d_name));
E 12
}
E 1
