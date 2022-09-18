h07986
s 00002/00002/00062
d D 8.1 93/06/02 20:05:32 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00036/00026/00028
d D 5.9 93/02/10 14:29:35 bostic 10 9
c add GLOB_BRACE, GLOB_TILDE; minor cleanup
e
s 00006/00000/00048
d D 5.8 92/12/02 01:00:52 mckusick 9 8
c add GLOB_ALTDIRFUNC to have glob use alternate directory access functions
e
s 00012/00012/00036
d D 5.7 91/07/15 14:39:01 bostic 8 6
c add GLOB_NOMAGIC
e
s 00011/00010/00038
d R 5.7 91/07/15 14:34:36 bostic 7 6
c add GLOB_NOMAGIC
e
s 00005/00000/00043
d D 5.6 91/04/03 16:10:59 bostic 6 5
c protect all user-level include files against reinclusion
e
s 00012/00009/00031
d D 5.5 91/03/19 19:24:21 bostic 5 4
c add gl_matchc, GLOB_MAGCHAR; sort flags
e
s 00001/00001/00039
d D 5.4 91/03/07 11:45:28 donn 4 3
c routine arg to glob(3) is a const
e
s 00006/00001/00034
d D 5.3 91/02/22 08:03:37 donn 3 2
c Added new prototype declarations and cleaned up.
e
s 00001/00011/00034
d D 5.2 90/06/01 14:00:48 bostic 2 1
c new copyright notice
e
s 00045/00000/00000
d D 5.1 90/02/15 10:57:58 bostic 1 0
c date and time created 90/02/15 10:57:58 by bostic
e
u
U
t
T
I 1
/*
D 11
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * Guido van Rossum.
 *
D 2
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

I 6
#ifndef _GLOB_H_
#define	_GLOB_H_

I 10
#include <sys/cdefs.h>

struct stat;
E 10
E 6
typedef struct {
D 5
	int gl_pathc;		/* count of paths matching pattern */
E 5
I 5
D 10
	int gl_pathc;		/* count of total paths so far */
	int gl_matchc;		/* count of paths matching pattern */
E 5
	int gl_offs;		/* reserved at beginning of gl_pathv */
	int gl_flags;		/* copy of flags parameter to glob() */
	int (*gl_errfunc)();	/* copy of errfunc parameter to glob() */
I 9
	void *(*gl_opendir)();	/* alternate opendir() function for glob() */
	struct dirent *(*gl_readdir)();	/* alternate readdir() function */
	void (*gl_closedir)();	/* alternate closedir() function for glob() */
	int (*gl_lstat)();	/* alternate lstat() function for glob() */
	int (*gl_stat)();	/* alternate stat() function for glob() */
E 9
	char **gl_pathv;	/* list of paths matching pattern */
E 10
I 10
	int gl_pathc;		/* Count of total paths so far. */
	int gl_matchc;		/* Count of paths matching pattern. */
	int gl_offs;		/* Reserved at beginning of gl_pathv. */
	int gl_flags;		/* Copy of flags parameter to glob. */
	char **gl_pathv;	/* List of paths matching pattern. */
				/* Copy of errfunc parameter to glob. */
	int (*gl_errfunc) __P((const char *, int));

	/*
	 * Alternate filesystem access methods for glob; replacement
	 * versions of closedir(3), readdir(3), opendir(3), stat(2)
	 * and lstat(2).
	 */
	void (*gl_closedir) __P((void *));
	struct dirent *(*gl_readdir) __P((void *));	
	void *(*gl_opendir) __P((const char *));
	int (*gl_lstat) __P((const char *, struct stat *));
	int (*gl_stat) __P((const char *, struct stat *));
E 10
} glob_t;

D 5
#define	GLOB_ERR	0x01	/* return on error */
#define	GLOB_MARK	0x02	/* append / to matching directories */
#define	GLOB_NOSORT	0x04	/* don't sort */
#define	GLOB_NOCHECK	0x08	/* return pattern itself if nothing matches */
#define	GLOB_DOOFFS	0x10	/* use gl_offs */
#define	GLOB_APPEND	0x20	/* append to output from previous call */

E 5
I 5
D 8
#define	GLOB_APPEND	0x01	/* append to output from previous call */
#define	GLOB_DOOFFS	0x02	/* use gl_offs */
#define	GLOB_ERR	0x04	/* return on error */
E 8
I 8
D 10
#define	GLOB_APPEND	0x001	/* append to output from previous call */
#define	GLOB_DOOFFS	0x002	/* use gl_offs */
#define	GLOB_ERR	0x004	/* return on error */
#define	GLOB_MARK	0x008	/* append / to matching directories */
#define	GLOB_NOCHECK	0x010	/* return pattern itself if nothing matches */
#define	GLOB_NOSORT	0x020	/* don't sort */
E 10
I 10
#define	GLOB_APPEND	0x0001	/* Append to output from previous call. */
#define	GLOB_DOOFFS	0x0002	/* Use gl_offs. */
#define	GLOB_ERR	0x0004	/* Return on error. */
#define	GLOB_MARK	0x0008	/* Append / to matching directories. */
#define	GLOB_NOCHECK	0x0010	/* Return pattern itself if nothing matches. */
#define	GLOB_NOSORT	0x0020	/* Don't sort. */
E 10

E 8
E 5
#ifndef _POSIX_SOURCE
D 5
#define	GLOB_QUOTE	0x40	/* quote special chars with \ */
E 5
I 5
D 8
#define	GLOB_MAGCHAR	0x08	/* pattern had globbing characters */
E 8
I 8
D 10
#define	GLOB_MAGCHAR	0x040	/* pattern had globbing characters */
#define	GLOB_NOMAGIC	0x080	/* GLOB_NOCHECK without magic chars (csh) */
#define	GLOB_QUOTE	0x100	/* quote special chars with \ */
I 9
#define	GLOB_ALTDIRFUNC	0x200	/* use alternately specified directory funcs */
E 10
I 10
#define	GLOB_ALTDIRFUNC	0x0040	/* Use alternately specified directory funcs. */
#define	GLOB_BRACE	0x0080	/* Expand braces ala csh. */
#define	GLOB_MAGCHAR	0x0100	/* Pattern had globbing characters. */
#define	GLOB_NOMAGIC	0x0200	/* GLOB_NOCHECK without magic chars (csh). */
#define	GLOB_QUOTE	0x0400	/* Quote special chars with \. */
#define	GLOB_TILDE	0x0800	/* Expand tilde names from the passwd file. */
E 10
E 9
E 8
#endif
D 8
#define	GLOB_MARK	0x10	/* append / to matching directories */
#define	GLOB_NOCHECK	0x20	/* return pattern itself if nothing matches */
#define	GLOB_NOSORT	0x40	/* don't sort */
#ifndef _POSIX_SOURCE
#define	GLOB_QUOTE	0x80	/* quote special chars with \ */
E 5
#endif
E 8

D 10
#define	GLOB_NOSPACE	(-1)	/* malloc call failed */
#define	GLOB_ABEND	(-2)	/* unignored error */
E 10
I 10
#define	GLOB_NOSPACE	(-1)	/* Malloc call failed. */
#define	GLOB_ABEND	(-2)	/* Unignored error. */
E 10

D 3
void globfree();
E 3
I 3
D 10
#include <sys/cdefs.h>

E 10
__BEGIN_DECLS
D 4
int glob __P((const char *, int, const int (*)(char *, int), glob_t *));
E 4
I 4
D 8
int glob __P((const char *, int, int (*)(char *, int), glob_t *));
E 4
void globfree __P((glob_t *));
E 8
I 8
D 10
int	glob __P((const char *, int, int (*)(char *, int), glob_t *));
E 10
I 10
int	glob __P((const char *, int, int (*)(const char *, int), glob_t *));
E 10
void	globfree __P((glob_t *));
E 8
__END_DECLS
I 6

#endif /* !_GLOB_H_ */
E 6
E 3
E 1
