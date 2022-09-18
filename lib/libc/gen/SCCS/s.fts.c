h31381
s 00002/00008/00967
d D 8.6 94/08/14 21:17:16 mckusick 48 47
c DT_WHTD is gone
e
s 00032/00002/00943
d D 8.5 94/07/28 03:38:31 pendry 47 46
c changes for whiteouts and union filesystem
e
s 00008/00008/00937
d D 8.4 94/04/16 07:36:15 bostic 46 45
c ANSI C cleanups
e
s 00011/00006/00934
d D 8.3 94/04/16 07:30:40 bostic 45 44
c Fix obscure bug where the working directory would not be restored to its
c proper place (occurs if one of fts_open()'s arguments is a relative path
c to a empty directory).
c From: conklin@ngai.kaleida.com (J.T. Conklin)
e
s 00002/00001/00938
d D 8.2 94/01/02 18:13:01 bostic 44 43
c don't increment a void *, it's not healthy
e
s 00002/00002/00937
d D 8.1 93/06/04 12:01:59 bostic 43 42
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00019/00009/00920
d D 5.42 93/04/26 22:42:32 bostic 42 41
c check file type on new file systems, eliminate more stat calls
e
s 00010/00004/00919
d D 5.41 93/03/07 12:34:18 bostic 41 40
c if reach the root directory, have to cd to the original directory
c when load the paths for the next root.  test case is "du d1/d1d1 d2/d2d1",
c the second root will not be in the right directory.
e
s 00023/00012/00900
d D 5.40 92/07/23 11:56:20 bostic 40 39
c have to set maxlen before allocate the path, have to use the path
c before calculate maxlen; do two passes through argv.
e
s 00035/00028/00877
d D 5.39 92/06/02 13:51:24 bostic 39 38
c fix allocated stat structure alignment
e
s 00002/00003/00903
d D 5.38 92/05/05 14:33:59 bostic 38 37
c set no chdir bit no matter where fts_build called from
e
s 00005/00002/00901
d D 5.37 92/05/05 14:13:19 bostic 37 36
c don't chdir after unexecutable directory
e
s 00000/00003/00903
d D 5.36 92/03/30 17:47:57 bostic 36 35
c don't close fts_rfd if can't get back, fts_close will try again
e
s 00018/00024/00888
d D 5.35 92/03/30 17:44:16 bostic 35 34
c don't bother to cd if didn't successfully build the child (not a bug
c but not necessary); check FTS_NOCHDIR on up-to-parent FCHDIR; don't close the
c file descriptor on successful return to root directory; set FTS_DP in fts_build
e
s 00012/00008/00900
d D 5.34 92/03/20 17:01:53 bostic 34 33
c fix post-order visit to empty directories to not close fts_rfd
c save errno across close of failed chdir's; set FTS_DP in fts_read, not
c fts_build
e
s 00000/00002/00908
d D 5.33 92/03/05 16:33:29 elan 33 32
c Made fts_pointer and fts_number fields separate fields.
e
s 00042/00007/00868
d D 5.32 92/03/01 13:26:28 bostic 32 31
c add FTS_NAMEONLY flag to fts_children; check options for validity
e
s 00002/00002/00873
d D 5.31 92/02/19 12:57:55 bostic 31 30
c align the allocated stat structure correctly
e
s 00001/00001/00874
d D 5.30 92/02/04 16:49:08 bostic 30 29
c add FTS_COMFOLLOW flag
e
s 00084/00046/00791
d D 5.29 92/02/03 16:45:55 bostic 29 28
c fix FTS_FOLLOW so fts can actually return; add flags to FTS struct for
c symbolic link follow and chdir errors; close symbolic link file descriptors;
c nlink and cderror fixes in fts_build to make ls work; link directories in
c forward order for ls -f; minor fixes
e
s 00033/00026/00804
d D 5.28 92/01/31 13:36:06 bostic 28 27
c rework errno processing to be more consistent and to set in the correct
c node; don't chdir back up if unable to chdir down; preserve the cd error
c value to set in each node of the directory that is read
e
s 00001/00001/00829
d D 5.27 92/01/17 12:37:52 bostic 27 26
c see accpath, used by fts_stat
e
s 00130/00069/00700
d D 5.26 92/01/15 17:58:40 bostic 26 25
c adjust tree pointers when realloc space; add FTS_DOT; don't allocate
c stat structures unless user needs them;
e
s 00003/00001/00766
d D 5.25 92/01/14 20:21:46 bostic 25 24
c set errno on FTS_DNR
e
s 00036/00025/00731
d D 5.24 92/01/09 17:28:20 bostic 24 23
c fts_children needs to return user's logical hierarchy;
c change fts_cderr to fts_errno; change fts_children to recognize call before
c fts_read called; change fts_stat to set fts_errno on error
e
s 00009/00009/00747
d D 5.23 92/01/09 16:20:16 bostic 23 22
c KNF
e
s 00045/00045/00711
d D 5.22 92/01/08 18:12:15 bostic 22 21
c lint and KNF
e
s 00002/00009/00754
d D 5.21 91/12/30 17:41:41 bostic 21 20
c weren't checking high enough in the tree for cycles; get rid of the
c savelink stuff and just add another pointer field to the FTSENT structure
e
s 00007/00005/00756
d D 5.20 91/12/23 17:48:19 bostic 20 19
c prototype internal routines
e
s 00002/00002/00759
d D 5.19 91/05/09 17:14:43 bostic 19 18
c set level before calling fts_stat during fts_open, cycle detection uses it
e
s 00003/00006/00758
d D 5.18 91/03/14 11:22:43 bostic 18 17
c fts_load no longer has any return value
e
s 00001/00001/00763
d D 5.17 91/03/14 11:19:29 bostic 17 16
c don't set XDEV dev_t until have stat'd the root of the tree
e
s 00044/00035/00720
d D 5.16 91/03/11 18:25:03 bostic 16 15
c change to return to starting node before postorder return of root
c nodes; move chdir calls from fts_load to fts_read.  Nasty.
e
s 00010/00019/00745
d D 5.15 91/03/11 09:27:31 bostic 15 14
c #define root and root's parent fts_level values in <fts.h>
c delete hack to make root DNE error FTS_ERR instead of FTS_NS, the usual return
e
s 00282/00259/00482
d D 5.14 91/03/10 12:25:43 bostic 14 13
c rework to set errno on fts_info error cases, return names from unsearchable
c directories
e
s 00016/00009/00725
d D 5.13 91/03/08 07:34:23 bostic 13 12
c ANSI; #ifdef out code to delete trailing slashes from user path
e
s 00006/00005/00728
d D 5.12 90/11/18 13:00:54 bostic 12 11
c wasn't resetting errno for fts_children call of fts_build for
c unsearchable directories
e
s 00219/00188/00514
d D 5.11 90/11/14 17:28:57 bostic 11 10
c use macros to set/read options
c rename functions/fields to POSIX names
c make comments consistently use capital letters
c get rid of global variable stream and pass around current stream pointer
c don't cast free to void
c add FTS__NOINSTR flag, instead of using 0 as "no user instructions"
c allow fts_children call for FTS_{D,DNR,DNX} instead of just FTS_D
c change fts_build so that fts_children can read FTS_DNX directories
c make fts_stat return FTS_NS on stat failure, not FTS_ERR
c make fts_stat unset errno on FTS_{NS,SLNONE} conditions
e
s 00002/00001/00700
d D 5.10 90/06/09 18:32:43 bostic 10 9
c don't bother stating the root paths, if FTS_NOSTAT set
e
s 00026/00035/00675
d D 5.9 90/06/09 16:33:36 bostic 9 8
c delete FTS_MULTIPLE
e
s 00004/00003/00706
d D 5.8 90/05/24 08:50:35 bostic 8 7
c do post-order visit if FTS_SKIP or FTS_XDEV apply to preorder visit
e
s 00141/00089/00568
d D 5.7 90/05/23 19:26:37 bostic 7 6
c FTS_LOGICAL sets FTS_NOCHDIR; otherwise have to save full path each time
c it indirects through a symlink.  Instead of doing getwd/chdir's, open an fd
c and do an fchdir; wastes an fd per open stream.  Fix ftschildren() -- redid
c most of the directory handling logic, special case first node in case it gets
c called before ftsread does a chdir to the subdirectory.  Minor changes to path
c handling in fts_build.
e
s 00037/00038/00620
d D 5.6 90/05/22 19:15:53 bostic 6 5
c redo the way the initial linked list of "roots" is set up; broke
c if you called ftsread multiple times in the same program.
e
s 00003/00001/00655
d D 5.5 90/05/22 18:57:47 bostic 5 4
c add FTS_XDEV; don't cross mount points
e
s 00170/00173/00486
d D 5.4 90/05/22 13:10:02 bostic 4 3
c change the names from foo to fts_foo
e
s 00009/00036/00650
d D 5.3 90/04/16 12:48:42 bostic 3 2
c remove permissions checking code, let the kernel do it.  This means
c that FTS_{DNR,DNX} are not returned until post-order directory visit.
e
s 00030/00040/00656
d D 5.2 90/01/31 08:31:09 bostic 2 1
c add fchdir; reduce number of cd's, do all cd's in fts_build
e
s 00696/00000/00000
d D 5.1 89/12/30 15:55:11 bostic 1 0
c date and time created 89/12/30 15:55:11 by bostic
e
u
U
t
T
I 1
D 4
/*
 * Copyright (c) 1989 The Regents of the University of California.
E 4
I 4
/*-
D 43
 * Copyright (c) 1990 The Regents of the University of California.
E 4
 * All rights reserved.
E 43
I 43
D 45
 * Copyright (c) 1990, 1993
E 45
I 45
 * Copyright (c) 1990, 1993, 1994
E 45
 *	The Regents of the University of California.  All rights reserved.
E 43
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 14
D 20
#include <sys/cdefs.h>
E 20
E 14
#include <sys/param.h>
#include <sys/stat.h>
I 7
D 45
#include <fcntl.h>
E 45
I 45

E 45
E 7
#include <dirent.h>
#include <errno.h>
I 45
#include <fcntl.h>
E 45
D 14
#include <fts.h>
D 4
#include <strings.h>
E 4
I 4
#include <string.h>
E 14
I 14
D 26
#include "fts.h"
E 26
I 26
#include <fts.h>
E 26
E 14
I 6
#include <stdlib.h>
I 14
#include <string.h>
E 14
I 13
#include <unistd.h>
E 13
E 6
E 4

D 7
extern int errno;

E 7
D 11
FTSENT *fts_alloc(), *fts_build(), *fts_cycle(), *fts_sort(), *fts_root();
short fts_stat();
E 11
I 11
D 13
FTSENT *fts_alloc(), *fts_build(), *fts_cycle(), *fts_root(), *fts_sort();
void fts_lfree(), fts_load();
u_short fts_stat();
E 13
I 13
D 14
static FTSENT *fts_alloc(), *fts_build(), *fts_cycle(), *fts_root(),
	*fts_sort();
static void fts_lfree(), fts_load();
E 14
I 14
D 20
static FTSENT *fts_alloc(), *fts_build(), *fts_sort();
D 18
static void fts_lfree();
static int fts_load();
E 18
I 18
static void fts_load(), fts_lfree();
E 18
E 14
static u_short fts_stat();
static char *fts_path();
E 20
I 20
static FTSENT	*fts_alloc __P((FTS *, char *, int));
static FTSENT	*fts_build __P((FTS *, int));
static void	 fts_lfree __P((FTSENT *));
static void	 fts_load __P((FTS *, FTSENT *));
I 40
static size_t	 fts_maxarglen __P((char * const *));
E 40
D 26
static char	*fts_path __P((FTS *, int));
E 26
I 26
static void	 fts_padjust __P((FTS *, void *));
D 39
static int	 fts_palloc __P((FTS *, int));
E 39
I 39
static int	 fts_palloc __P((FTS *, size_t));
E 39
E 26
static FTSENT	*fts_sort __P((FTS *, FTSENT *, int));
static u_short	 fts_stat __P((FTS *, FTSENT *, int));
E 20
E 13
E 11
D 6
char *malloc(), *realloc();
E 6

I 26
#define	ISDOT(a)	(a[0] == '.' && (!a[1] || a[1] == '.' && !a[2]))

E 26
D 14
/*
 * Special case a root of "/" so that slashes aren't appended causing
 * paths to be written as "//foo".
 */
#define	NAPPEND(p) \
D 4
	(p->level == ROOTLEVEL && p->pathlen == 1 && \
	    p->path[0] == '/' ? 0 : p->pathlen)
E 4
I 4
	(p->fts_level == ROOTLEVEL && p->fts_pathlen == 1 && \
	    p->fts_path[0] == '/' ? 0 : p->fts_pathlen)
E 4

E 14
D 4
#define	CHDIR(sp, path)	(!(sp->options & FTS_NOCHDIR) && chdir(path))
I 2
#define	FCHDIR(sp, fd)	(!(sp->options & FTS_NOCHDIR) && fchdir(fd))
E 4
I 4
D 11
#define	CHDIR(sp, path)	(!(sp->fts_options & FTS_NOCHDIR) && chdir(path))
#define	FCHDIR(sp, fd)	(!(sp->fts_options & FTS_NOCHDIR) && fchdir(fd))
E 11
I 11
#define	ISSET(opt)	(sp->fts_options & opt)
#define	SET(opt)	(sp->fts_options |= opt)
E 11
E 4
E 2

D 11
#define	ROOTLEVEL	0
#define	ROOTPARENTLEVEL	-1
E 11
I 11
#define	CHDIR(sp, path)	(!ISSET(FTS_NOCHDIR) && chdir(path))
#define	FCHDIR(sp, fd)	(!ISSET(FTS_NOCHDIR) && fchdir(fd))
E 11

I 7
/* fts_build flags */
D 11
#define	BCHILD		1		/* from ftschildren */
#define	BREAD		2		/* from ftsread */
E 11
I 11
D 32
#define	BCHILD		1		/* from fts_children */
#define	BREAD		2		/* from fts_read */
E 32
I 32
#define	BCHILD		1		/* fts_children */
#define	BNAMES		2		/* fts_children, names only */
#define	BREAD		3		/* fts_read */
E 32
E 11

E 7
D 11
static FTS *stream;			/* current stream pointer */
E 11
I 11
D 15
/* fts_level values */
D 14
#define	ROOTLEVEL	0
E 14
I 14
#define	ROOTLEVEL	 0
E 14
#define	ROOTPARENTLEVEL	-1
E 11

E 15
FTS *
D 11
ftsopen(argv, options, compar)
E 11
I 11
fts_open(argv, options, compar)
E 11
D 13
	char *argv[];
E 13
I 13
	char * const *argv;
E 13
	register int options;
D 13
	int (*compar)();
E 13
I 13
D 14
	int (*compar) __P((const FTSENT *, const FTSENT *));
E 14
I 14
	int (*compar)();
E 14
E 13
{
	register FTS *sp;
	register FTSENT *p, *root;
D 40
	register int nitems, maxlen;
E 40
I 40
	register int nitems;
E 40
	FTSENT *parent, *tmp;
I 14
	int len;
E 14
D 7
	char wd[MAXPATHLEN], *getwd(), *strdup();
E 7
I 7
D 13
	char *fts_path();
E 13
E 7

I 32
	/* Options check. */
	if (options & ~FTS_OPTIONMASK) {
		errno = EINVAL;
		return (NULL);
	}

E 32
D 11
	/* allocate/initialize the stream */
	if (!(stream = sp = (FTS *)malloc((u_int)sizeof(FTS))))
E 11
I 11
	/* Allocate/initialize the stream */
D 22
	if (!(sp = (FTS *)malloc((u_int)sizeof(FTS))))
E 11
		return(NULL);
E 22
I 22
	if ((sp = malloc((u_int)sizeof(FTS))) == NULL)
		return (NULL);
E 22
D 46
	bzero(sp, sizeof(FTS));
E 46
I 46
	memset(sp, 0, sizeof(FTS));
E 46
D 4
	sp->compar = compar;
	sp->options = options;
E 4
I 4
	sp->fts_compar = compar;
I 7
D 11

	/*
	 * logical walks turn on NOCHDIR; symbolic links are just too
	 * hard to deal with.
	 */
E 11
E 7
	sp->fts_options = options;
I 7
D 11
	if (options & FTS_LOGICAL)
		sp->fts_options |= FTS_NOCHDIR;
E 11
E 7
E 4

D 11
	/* allocate/initialize root's parent */
	if (!(parent = fts_alloc("", 0)))
E 11
I 11
	/* Logical walks turn on NOCHDIR; symbolic links are too hard. */
	if (ISSET(FTS_LOGICAL))
		SET(FTS_NOCHDIR);

I 39
	/*
D 40
	 * Start out with more than 1K of path space, and enough, in any
	 * case, to hold the user's paths.
E 40
I 40
	 * Start out with 1K of path space, and enough, in any case,
	 * to hold the user's paths.
E 40
	 */
D 40
	if (fts_palloc(sp, MAX(maxlen, MAXPATHLEN)))
E 40
I 40
	if (fts_palloc(sp, MAX(fts_maxarglen(argv), MAXPATHLEN)))
E 40
		goto mem1;

E 39
	/* Allocate/initialize root's parent. */
D 23
	if (!(parent = fts_alloc(sp, "", 0)))
E 23
I 23
	if ((parent = fts_alloc(sp, "", 0)) == NULL)
E 23
E 11
D 39
		goto mem1;
E 39
I 39
		goto mem2;
E 39
D 4
	parent->level = ROOTPARENTLEVEL;
E 4
I 4
D 15
	parent->fts_level = ROOTPARENTLEVEL;
E 15
I 15
	parent->fts_level = FTS_ROOTPARENTLEVEL;
E 15
E 4

D 11
	/* allocate/initialize root(s) */
E 11
I 11
	/* Allocate/initialize root(s). */
E 11
D 9
	if (options & FTS_MULTIPLE) {
		maxlen = -1;
		for (root = NULL, nitems = 0; *argv; ++argv, ++nitems) {
			if (!(p = fts_root(*argv)))
				goto mem2;
D 4
			if (maxlen < p->namelen)
				maxlen = p->namelen;
E 4
I 4
			if (maxlen < p->fts_namelen)
				maxlen = p->fts_namelen;
E 4
			/*
			 * if comparison routine supplied, traverse in sorted
			 * order; otherwise traverse in the order specified.
			 */
			if (compar) {
D 4
				p->link = root;
E 4
I 4
				p->fts_link = root;
E 4
				root = p;
D 4
				p->accpath = p->name;
				p->info = fts_stat(p, 0);
E 4
I 4
				p->fts_accpath = p->fts_name;
				p->fts_info = fts_stat(p, 0);
E 4
			} else {
D 4
				p->link = NULL;
E 4
I 4
				p->fts_link = NULL;
E 4
				if (!root)
					tmp = root = p;
				else {
D 4
					tmp->link = p;
E 4
I 4
					tmp->fts_link = p;
E 4
					tmp = p;
				}
E 9
I 9
D 24
	maxlen = -1;
	for (root = NULL, nitems = 0; *argv; ++argv, ++nitems) {
E 24
I 24
D 40
	for (root = NULL, maxlen = nitems = 0; *argv; ++argv, ++nitems) {
E 40
I 40
	for (root = NULL, nitems = 0; *argv; ++argv, ++nitems) {
E 40
		/* Don't allow zero-length paths. */
E 24
D 11
		if (!(p = fts_root(*argv)))
E 11
I 11
D 14
		if (!(p = fts_root(sp, *argv)))
E 14
I 14
D 26
		if (!(len = strlen(*argv))) {
E 26
I 26
		if ((len = strlen(*argv)) == 0) {
E 26
			errno = ENOENT;
E 14
E 11
D 39
			goto mem2;
E 39
I 39
			goto mem3;
E 39
D 14
		if (maxlen < p->fts_namelen)
			maxlen = p->fts_namelen;
E 14
I 14
		}
D 40
		if (maxlen < len)
			maxlen = len;
E 40
I 26

E 26
		p = fts_alloc(sp, *argv, len);
I 19
		p->fts_level = FTS_ROOTLEVEL;
		p->fts_parent = parent;
I 27
		p->fts_accpath = p->fts_name;
E 27
I 26
D 30
		p->fts_info = fts_stat(sp, p, 0);
E 30
I 30
		p->fts_info = fts_stat(sp, p, ISSET(FTS_COMFOLLOW));
E 30

		/* Command-line "." and ".." are real directories. */
D 27
		p->fts_accpath = p->fts_name;
E 27
		if (p->fts_info == FTS_DOT)
			p->fts_info = FTS_D;

E 26
E 19
E 14
		/*
D 11
		 * if comparison routine supplied, traverse in sorted
E 11
I 11
		 * If comparison routine supplied, traverse in sorted
E 11
		 * order; otherwise traverse in the order specified.
		 */
		if (compar) {
			p->fts_link = root;
			root = p;
D 26
			p->fts_accpath = p->fts_name;
D 10
			p->fts_info = fts_stat(p, 0);
E 10
I 10
			if (!(options & FTS_NOSTAT))
D 11
				p->fts_info = fts_stat(p, 0);
E 11
I 11
				p->fts_info = fts_stat(sp, p, 0);
E 26
E 11
E 10
		} else {
			p->fts_link = NULL;
D 23
			if (!root)
E 23
I 23
			if (root == NULL)
E 23
				tmp = root = p;
			else {
				tmp->fts_link = p;
				tmp = p;
E 9
			}
D 4
			p->level = ROOTLEVEL;
			p->parent = parent;
E 4
I 4
D 9
			p->fts_level = ROOTLEVEL;
			p->fts_parent = parent;
E 9
E 4
		}
D 9
		if (compar && nitems > 1)
			root = fts_sort(root, nitems);
	} else {
		if (!(root = fts_root((char *)argv)))
			goto mem2;
D 4
		maxlen = root->namelen;
		root->link = NULL;
		root->level = ROOTLEVEL;
		root->parent = parent;
E 4
I 4
		maxlen = root->fts_namelen;
		root->fts_link = NULL;
		root->fts_level = ROOTLEVEL;
		root->fts_parent = parent;
E 9
I 9
D 15
		p->fts_level = ROOTLEVEL;
E 15
I 15
D 19
		p->fts_level = FTS_ROOTLEVEL;
E 15
		p->fts_parent = parent;
E 19
E 9
E 4
	}
I 9
	if (compar && nitems > 1)
D 11
		root = fts_sort(root, nitems);
E 11
I 11
		root = fts_sort(sp, root, nitems);
E 11
E 9

I 6
	/*
D 11
	 * allocate a dummy pointer and make ftsread think that we've just
E 11
I 11
	 * Allocate a dummy pointer and make fts_read think that we've just
E 11
D 24
	 * finished the node before the root(s); set p->fts_info to FTS_NS
E 24
I 24
	 * finished the node before the root(s); set p->fts_info to FTS_INIT
E 24
	 * so that everything about the "current" node is ignored.
	 */
D 11
	if (!(sp->fts_cur = fts_alloc("", 0)))
E 11
I 11
D 23
	if (!(sp->fts_cur = fts_alloc(sp, "", 0)))
E 23
I 23
	if ((sp->fts_cur = fts_alloc(sp, "", 0)) == NULL)
E 23
E 11
D 39
		goto mem2;
E 39
I 39
		goto mem3;
E 39
	sp->fts_cur->fts_link = root;
D 24
	sp->fts_cur->fts_info = FTS_NS;
E 24
I 24
	sp->fts_cur->fts_info = FTS_INIT;
E 24

E 6
D 11
	/* start out with at least 1K+ of path space */
	if (!fts_path(MAX(maxlen, MAXPATHLEN)))
E 11
I 11
D 24
	/* Start out with at least 1K+ of path space. */
	if (!fts_path(sp, MAX(maxlen, MAXPATHLEN)))
E 24
I 24
	/*
D 26
	 * Start out with at least 1K+ of path space, but enough, in any
E 26
I 26
D 39
	 * Start out with more than 1K of path space, and enough, in any
E 26
	 * case, to hold the user's paths.
	 */
D 26
	if (!fts_path(sp, MAX(maxlen + 1, MAXPATHLEN)))
E 26
I 26
	if (fts_palloc(sp, MAX(maxlen, MAXPATHLEN)))
E 26
E 24
E 11
D 6
		goto mem2;
E 6
I 6
		goto mem3;
E 6

	/*
E 39
D 6
	 * some minor trickiness.  Set the pointers so that ftsread thinks
D 4
	 * we've just finished the node before the root(s); set p->info to
	 * FTS_NS so that everything about the "current" node is ignored.
E 4
I 4
	 * we've just finished the node before the root(s); set p->fts_info
	 * to FTS_NS so that everything about the "current" node is ignored.
E 4
	 * Rather than allocate a dummy node use the root's parent's link
	 * pointer.  This is handled specially in ftsclose() as well.
	 */
D 4
	sp->cur = parent;
	parent->link = root;
	parent->info = FTS_NS;
E 4
I 4
	sp->fts_cur = parent;
	parent->fts_link = root;
	parent->fts_info = FTS_NS;
E 4

	/*
E 6
D 7
	 * if using chdir(2), do a getwd() to insure that we can get back
	 * here; this could be avoided for some paths, but probably not
	 * worth the effort.  Slashes, symbolic links, and ".." are all
	 * fairly nasty problems.  Note, if we can't get the current
	 * working directory we run anyway, just more slowly.
E 7
I 7
D 11
	 * if using chdir(2), grab a file descriptor pointing to dot to insure
E 11
I 11
	 * If using chdir(2), grab a file descriptor pointing to dot to insure
E 11
	 * that we can get back here; this could be avoided for some paths,
	 * but almost certainly not worth the effort.  Slashes, symbolic links,
	 * and ".." are all fairly nasty problems.  Note, if we can't get the
	 * descriptor we run anyway, just more slowly.
E 7
	 */
D 4
	if (!(options & FTS_NOCHDIR) && (!getwd(wd) || !(sp->wd = strdup(wd))))
		sp->options |= FTS_NOCHDIR;
E 4
I 4
D 11
	if (!(options & FTS_NOCHDIR) &&
D 7
	    (!getwd(wd) || !(sp->fts_wd = strdup(wd))))
E 7
I 7
	    (sp->fts_sd = open(".", O_RDONLY, 0)) < 0)
E 7
		sp->fts_options |= FTS_NOCHDIR;
E 11
I 11
D 14
	if (!ISSET(FTS_NOCHDIR) && (sp->fts_sd = open(".", O_RDONLY, 0)) < 0)
E 14
I 14
	if (!ISSET(FTS_NOCHDIR) && (sp->fts_rfd = open(".", O_RDONLY, 0)) < 0)
E 14
		SET(FTS_NOCHDIR);
E 11
E 4

D 22
	return(sp);
E 22
I 22
	return (sp);
E 22

I 6
D 7
mem3:	(void)free((char *)sp->fts_cur);
E 7
I 7
D 11
mem3:	(void)free((void *)sp->fts_cur);
E 11
I 11
D 14
mem3:	free((void *)sp->fts_cur);
E 14
I 14
D 39
mem3:	free(sp->fts_cur);
E 14
E 11
E 7
E 6
mem2:	fts_lfree(root);
E 39
I 39
mem3:	fts_lfree(root);
E 39
D 7
	(void)free((char *)parent);
mem1:	(void)free((char *)sp);
E 7
I 7
D 11
	(void)free((void *)parent);
mem1:	(void)free((void *)sp);
E 11
I 11
D 14
	free((void *)parent);
mem1:	free((void *)sp);
E 14
I 14
	free(parent);
I 39
mem2:	free(sp->fts_path);
E 39
mem1:	free(sp);
E 14
E 11
E 7
D 22
	return(NULL);
E 22
I 22
	return (NULL);
E 22
}

D 11
static
fts_load(p)
E 11
I 11
D 14
static void
E 14
I 14
D 18
static
E 18
I 18
static void
E 18
E 14
fts_load(sp, p)
	FTS *sp;
E 11
	register FTSENT *p;
{
I 14
D 16
	static int need_to_cd;
E 16
E 14
	register int len;
	register char *cp;

	/*
D 11
	 * load the stream structure for the next traversal; set the
	 * accpath field specially so the chdir gets done to the right
	 * place and the user can access the first node.
E 11
I 11
D 14
	 * Load the stream structure for the next traversal; set the
	 * fts_accpath field specially so the chdir gets done to the
	 * right place and the user can access the first node.
E 14
I 14
D 16
	 * If changing the root level node, load the stream structure for the
	 * next traversal; set the fts_accpath field specially so the chdir
	 * gets done to the right place and the user can access the first node.
E 16
I 16
	 * Load the stream structure for the next traversal.  Since we don't
	 * actually enter the directory until after the preorder visit, set
	 * the fts_accpath field specially so the chdir gets done to the right
D 26
	 * place and the user can access the first node.
E 26
I 26
	 * place and the user can access the first node.  From fts_open it's
	 * known that the path will fit.
E 26
E 16
E 14
E 11
	 */
D 4
	len = p->pathlen = p->namelen;
	bcopy(p->name, stream->path, len + 1);
	if ((cp = rindex(p->name, '/')) && (cp != p->name || cp[1])) {
E 4
I 4
	len = p->fts_pathlen = p->fts_namelen;
D 11
	bcopy(p->fts_name, stream->fts_path, len + 1);
E 11
I 11
D 46
	bcopy(p->fts_name, sp->fts_path, len + 1);
E 11
	if ((cp = rindex(p->fts_name, '/')) && (cp != p->fts_name || cp[1])) {
E 46
I 46
	memmove(sp->fts_path, p->fts_name, len + 1);
	if ((cp = strrchr(p->fts_name, '/')) && (cp != p->fts_name || cp[1])) {
E 46
E 4
		len = strlen(++cp);
D 4
		bcopy(cp, p->name, len + 1);
		p->namelen = len;
E 4
I 4
D 46
		bcopy(cp, p->fts_name, len + 1);
E 46
I 46
		memmove(p->fts_name, cp, len + 1);
E 46
		p->fts_namelen = len;
E 4
	}
D 4
	p->accpath = p->path = stream->path;
E 4
I 4
D 11
	p->fts_accpath = p->fts_path = stream->fts_path;
E 11
I 11
	p->fts_accpath = p->fts_path = sp->fts_path;
I 14
D 26

D 17
	sp->rdev = p->fts_statb.st_dev;
E 17
D 16

	/*
	 * If not the first time, and it's not an absolute pathname, get back
	 * to starting directory.  If that fails, we're dead.
	 */
	if (need_to_cd && p->fts_path[0] != '/' && FCHDIR(sp, sp->fts_rfd))
		return(0);
	need_to_cd = 1;

E 16
D 15
	/*
	 * Special case error condition -- if we can't find the root of the
	 * traversal, make sure the user notices the error.
	 */
	if ((p->fts_info = fts_stat(sp, p, 0)) == FTS_NS)
		p->fts_info = FTS_ERR;
E 15
I 15
	p->fts_info = fts_stat(sp, p, 0);
I 17
	sp->rdev = p->fts_statb.st_dev;
E 26
I 26
	sp->fts_dev = p->fts_dev;
E 26
E 17
E 15
D 18
	return(1);
E 18
E 14
E 11
E 4
}

I 26
int
E 26
I 13
D 14
int
E 14
E 13
D 11
ftsclose(sp)
E 11
I 11
fts_close(sp)
E 11
	FTS *sp;
{
	register FTSENT *freep, *p;
	int saved_errno;

I 26
	/*
	 * This still works if we haven't read anything -- the dummy structure
	 * points to the root list, so we step through to the end of the root
	 * list which has a valid parent pointer.
	 */
E 26
D 4
	if (sp->cur)
E 4
I 4
D 6
	if (sp->fts_cur)
E 4
		/* check for never having read anything */
D 4
		if (sp->cur->level == ROOTPARENTLEVEL)
			fts_lfree(sp->cur);
E 4
I 4
		if (sp->fts_cur->fts_level == ROOTPARENTLEVEL)
			fts_lfree(sp->fts_cur);
E 4
		else {
D 4
			for (p = sp->cur; p->level > ROOTPARENTLEVEL;) {
E 4
I 4
			for (p = sp->fts_cur; p->fts_level > ROOTPARENTLEVEL;) {
E 4
				freep = p;
D 4
				p = p->link ? p->link : p->parent;
E 4
I 4
				p = p->fts_link ? p->fts_link : p->fts_parent;
E 4
				(void)free((char *)freep);
			}
			(void)free((char *)p);
E 6
I 6
	if (sp->fts_cur) {
D 26
		/*
D 11
		 * this still works if we haven't read anything -- the dummy
E 11
I 11
		 * This still works if we haven't read anything -- the dummy
E 11
		 * structure points to the root list, so we step through to
		 * the end of the root list which has a valid parent pointer.
		 */
D 15
		for (p = sp->fts_cur; p->fts_level > ROOTPARENTLEVEL;) {
E 15
I 15
		for (p = sp->fts_cur; p->fts_level > FTS_ROOTPARENTLEVEL;) {
E 26
I 26
		for (p = sp->fts_cur; p->fts_level >= FTS_ROOTLEVEL;) {
E 26
E 15
			freep = p;
			p = p->fts_link ? p->fts_link : p->fts_parent;
D 7
			(void)free((char *)freep);
E 7
I 7
D 11
			(void)free((void *)freep);
E 11
I 11
D 14
			free((void *)freep);
E 14
I 14
			free(freep);
E 14
E 11
E 7
E 6
		}
I 6
D 7
		(void)free((char *)p);
E 7
I 7
D 11
		(void)free((void *)p);
E 11
I 11
D 14
		free((void *)p);
E 14
I 14
		free(p);
E 14
E 11
E 7
	}
E 6

D 11
	/* free up child linked list, sort array, path buffer */
E 11
I 11
	/* Free up child linked list, sort array, path buffer. */
E 11
D 4
	if (sp->child)
		fts_lfree(sp->child);
	if (sp->array)
		(void)free((char *)sp->array);
	(void)free((char *)sp->path);
E 4
I 4
	if (sp->fts_child)
		fts_lfree(sp->fts_child);
	if (sp->fts_array)
D 7
		(void)free((char *)sp->fts_array);
E 7
I 7
D 11
		(void)free((void *)sp->fts_array);
E 7
	(void)free((char *)sp->fts_path);
E 11
I 11
D 14
		free((void *)sp->fts_array);
	free((char *)sp->fts_path);
E 14
I 14
		free(sp->fts_array);
	free(sp->fts_path);
E 14
E 11
E 4

D 14
	/*
D 11
	 * return to original directory, save errno if necessary;
	 * free up the directory buffer
E 11
I 11
	 * Return to original directory, save errno if necessary; free up
	 * the directory buffer.
E 11
	 */
E 14
I 14
	/* Return to original directory, save errno if necessary. */
E 14
D 4
	if (!(sp->options & FTS_NOCHDIR)) {
		saved_errno = chdir(sp->wd) ? errno : 0;
		(void)free(sp->wd);
E 4
I 4
D 11
	if (!(sp->fts_options & FTS_NOCHDIR)) {
E 11
I 11
	if (!ISSET(FTS_NOCHDIR)) {
E 11
D 7
		saved_errno = chdir(sp->fts_wd) ? errno : 0;
		(void)free(sp->fts_wd);
E 7
I 7
D 14
		saved_errno = fchdir(sp->fts_sd) ? errno : 0;
		(void)close(sp->fts_sd);
E 14
I 14
		saved_errno = fchdir(sp->fts_rfd) ? errno : 0;
		(void)close(sp->fts_rfd);
E 14
E 7
E 4
	}

D 11
	/* free up the stream pointer */
D 7
	(void)free((char *)sp);
E 7
I 7
	(void)free((void *)sp);
E 11
I 11
	/* Free up the stream pointer. */
D 14
	free((void *)sp);
E 14
I 14
	free(sp);
E 14
E 11
E 7

D 11
	/* set errno and return */
D 4
	if (!(sp->options & FTS_NOCHDIR) && saved_errno) {
E 4
I 4
	if (!(sp->fts_options & FTS_NOCHDIR) && saved_errno) {
E 11
I 11
	/* Set errno and return. */
	if (!ISSET(FTS_NOCHDIR) && saved_errno) {
E 11
E 4
		errno = saved_errno;
D 22
		return(-1);
E 22
I 22
		return (-1);
E 22
	}
D 22
	return(0);
E 22
I 22
	return (0);
E 22
}

I 14
/*
D 24
 * Special case a root of "/" so that slashes aren't appended causing
 * paths to be written as "//foo".
E 24
I 24
 * Special case a root of "/" so that slashes aren't appended which would
 * cause paths to be written as "//foo".
E 24
 */
D 40
#define	NAPPEND(p) \
D 15
	(p->fts_level == ROOTLEVEL && p->fts_pathlen == 1 && \
E 15
I 15
	(p->fts_level == FTS_ROOTLEVEL && p->fts_pathlen == 1 && \
E 40
I 40
#define	NAPPEND(p)							\
	(p->fts_level == FTS_ROOTLEVEL && p->fts_pathlen == 1 &&	\
E 40
E 15
	    p->fts_path[0] == '/' ? 0 : p->fts_pathlen)

E 14
FTSENT *
D 11
ftsread(sp)
E 11
I 11
fts_read(sp)
E 11
	register FTS *sp;
{
D 7
	register FTSENT *p;
E 7
I 7
	register FTSENT *p, *tmp;
E 7
	register int instr;
I 7
D 14
	register char *cp;
E 7
	static int cd;
E 14
I 14
	register char *t;
I 34
	int saved_errno;
E 34
E 14
D 7
	FTSENT *tmp;
	char *cp;
E 7

D 11
	/* if finished or unrecoverable error, return NULL */
D 4
	if (!sp->cur || sp->options & FTS__STOP)
E 4
I 4
	if (!sp->fts_cur || sp->fts_options & FTS__STOP)
E 11
I 11
	/* If finished or unrecoverable error, return NULL. */
D 14
	if (!sp->fts_cur || ISSET(FTS__STOP))
E 14
I 14
D 23
	if (!sp->fts_cur || ISSET(FTS_STOP))
E 23
I 23
	if (sp->fts_cur == NULL || ISSET(FTS_STOP))
E 23
E 14
E 11
E 4
D 22
		return(NULL);
E 22
I 22
		return (NULL);
E 22

D 11
	/* set global stream pointer, and current node pointer */
	stream = sp;
E 11
I 11
	/* Set current node pointer. */
E 11
D 4
	p = sp->cur;
E 4
I 4
	p = sp->fts_cur;
E 4

D 11
	/* save and zero out user instructions */
E 11
I 11
	/* Save and zero out user instructions. */
E 11
D 4
	instr = p->instr;
	p->instr = 0;
E 4
I 4
	instr = p->fts_instr;
D 11
	p->fts_instr = 0;
E 11
I 11
D 14
	p->fts_instr = FTS__NOINSTR;
E 14
I 14
	p->fts_instr = FTS_NOINSTR;
E 14
E 11
E 4

D 11
	/* if used link pointer for cycle detection, restore it */
E 11
I 11
D 21
	/* If used fts_link pointer for cycle detection, restore it. */
E 11
D 4
	if (sp->savelink) {
		p->link = sp->savelink;
		sp->savelink = NULL;
E 4
I 4
	if (sp->fts_savelink) {
		p->fts_link = sp->fts_savelink;
		sp->fts_savelink = NULL;
E 4
	}

E 21
D 11
	/* any type of file may be re-visited; re-stat and return */
E 11
I 11
D 14
	/* Any type of file may be re-visited; re-stat and return. */
E 14
I 14
	/* Any type of file may be re-visited; re-stat and re-turn. */
E 14
E 11
	if (instr == FTS_AGAIN) {
D 4
		p->info = fts_stat(p, 0);
E 4
I 4
D 11
		p->fts_info = fts_stat(p, 0);
E 11
I 11
		p->fts_info = fts_stat(sp, p, 0);
E 11
E 4
D 22
		return(p);
E 22
I 22
		return (p);
E 22
	}

D 4
	if (p->info == FTS_D)
E 4
I 4
D 7
	if (p->fts_info == FTS_D)
E 7
I 7
D 11
	/* following a symbolic link */
E 11
I 11
D 14
	/* Following a symbolic link. */
E 11
	if (p->fts_info == FTS_SL && instr == FTS_FOLLOW) {
E 14
I 14
	/*
	 * Following a symlink -- SLNONE test allows application to see
D 29
	 * SLNONE and recover.
I 28
	 *
	 * XXX
	 * Have to open a file descriptor to '.' so we can get back.
E 29
I 29
	 * SLNONE and recover.  If indirecting through a symlink, have
	 * keep a pointer to current location.  If unable to get that
	 * pointer, follow fails.
E 29
E 28
	 */
	if (instr == FTS_FOLLOW &&
	    (p->fts_info == FTS_SL || p->fts_info == FTS_SLNONE)) {
E 14
D 11
		p->fts_info = fts_stat(p, 1);
E 11
I 11
		p->fts_info = fts_stat(sp, p, 1);
I 29
		if (p->fts_info == FTS_D && !ISSET(FTS_NOCHDIR))
			if ((p->fts_symfd = open(".", O_RDONLY, 0)) < 0) {
				p->fts_errno = errno;
				p->fts_info = FTS_ERR;
			} else
				p->fts_flags |= FTS_SYMFOLLOW;
E 29
E 11
D 22
		return(p);
E 22
I 22
		return (p);
E 22
	}

D 11
	/* directory in pre-order */
E 11
I 11
	/* Directory in pre-order. */
E 11
	if (p->fts_info == FTS_D) {
D 8
		/* may have been skipped or crossed mount point */
E 8
I 8
D 11
		/* if skipped or crossed mount point, do post-order visit */
E 8
E 7
E 4
D 5
		if (instr == FTS_SKIP) {
E 5
I 5
		if (instr == FTS_SKIP || sp->fts_options & FTS_XDEV &&
E 11
I 11
		/* If skipped or crossed mount point, do post-order visit. */
D 14
		if (instr == FTS_SKIP || ISSET(FTS_XDEV) &&
E 11
		    p->fts_statb.st_dev != sp->sdev) {
E 14
I 14
		if (instr == FTS_SKIP ||
D 26
		    ISSET(FTS_XDEV) && p->fts_statb.st_dev != sp->rdev) {
E 26
I 26
		    ISSET(FTS_XDEV) && p->fts_dev != sp->fts_dev) {
I 29
			if (p->fts_flags & FTS_SYMFOLLOW)
				(void)close(p->fts_symfd);
E 29
E 26
E 14
E 5
D 4
			if (sp->child) {
				fts_lfree(sp->child);
				sp->child = NULL;
E 4
I 4
			if (sp->fts_child) {
				fts_lfree(sp->fts_child);
				sp->fts_child = NULL;
E 4
			}
D 7
		} else {
D 2
			if (sp->child) {
				/* cd into child directory */
				if (CHDIR(sp, p->accpath)) {
					sp->options |= FTS__STOP;
					p->info = FTS_ERR;
					return(p);
				}
			} else if (!(sp->child = fts_build(sp, 1)))
E 2
I 2
D 4
			if (!sp->child && (!(sp->child = fts_build(sp, 1))))
E 4
I 4
			if (!sp->fts_child &&
			    (!(sp->fts_child = fts_build(sp, 1))))
E 7
I 7
D 8
			goto next;
E 8
I 8
			p->fts_info = FTS_DP;
D 22
			return(p);
E 22
I 22
			return (p);
E 22
E 8
		} 

I 32
D 35
		/* Rebuild if only got the names and now traversing. */
E 35
I 35
		/* Rebuild if only read the names and now traversing. */
E 35
		if (sp->fts_child && sp->fts_options & FTS_NAMEONLY) {
			sp->fts_options &= ~FTS_NAMEONLY;
			fts_lfree(sp->fts_child);
			sp->fts_child = NULL;
		}

E 32
D 11
		/* read the directory if necessary, and return first entry */
E 11
I 11
D 14
		/* Read the directory if necessary, and return first entry. */
E 11
		if (sp->fts_child) 
E 14
I 14
		/*
D 35
		 * Cd to the subdirectory, reading it if haven't already.  If
		 * the read fails for any reason, or the directory is empty,
		 * the fts_info field of the current node is set by fts_build.
E 35
I 35
		 * Cd to the subdirectory.
		 *
E 35
D 16
		 * If have already read and fail to chdir, do some quick
		 * whacking to make the names come out right, and set the
		 * parent state so the application will eventually get an
		 * error condition.
E 16
I 16
		 * If have already read and now fail to chdir, whack the list
D 35
		 * to make the names come out right, and set the parent state
E 35
I 35
		 * to make the names come out right, and set the parent errno
E 35
		 * so the application will eventually get an error condition.
D 35
		 * If haven't read and fail to chdir, check to see if we're
		 * at the root node -- if so, we have to get back or the root
		 * node may be inaccessible.
E 35
I 35
		 * Set the FTS_DONTCHDIR flag so that when we logically change
		 * directories back to the parent we don't do a chdir.
		 *
		 * If haven't read do so.  If the read fails, fts_build sets
		 * FTS_STOP or the fts_info field of the node.
E 35
E 16
		 */
		if (sp->fts_child) {
E 14
			if (CHDIR(sp, p->fts_accpath)) {
D 14
				fts_lfree(sp->fts_child);
				p->fts_info = FTS_DNX;
			} else {
				p = sp->fts_child;
				cp = sp->fts_path + NAPPEND(p->fts_parent);
				*cp++ = '/';
				bcopy(p->fts_name, cp, p->fts_namelen + 1);
E 14
I 14
D 24
				p->fts_parent->fts_cderr = errno;
E 24
I 24
D 28
				p->fts_parent->fts_errno = errno;
E 28
I 28
				p->fts_errno = errno;
I 29
				p->fts_flags |= FTS_DONTCHDIR;
E 29
E 28
E 24
				for (p = sp->fts_child; p; p = p->fts_link)
					p->fts_accpath =
					    p->fts_parent->fts_accpath;
E 14
			}
D 14
		else {
			if (!(sp->fts_child = fts_build(sp, BREAD)))
E 7
E 4
E 2
				return(p);
D 4
			p = sp->child;
			sp->child = NULL;
D 2
			cp = sp->path + NAPPEND(p->parent);
			*cp++ = '/';
			bcopy(p->name, cp, p->namelen + 1);
E 2
			return(sp->cur = p);
E 4
I 4
			p = sp->fts_child;
D 7
			sp->fts_child = NULL;
			return(sp->fts_cur = p);
E 7
E 4
		}
E 14
I 14
D 16
		} else if (!(sp->fts_child = fts_build(sp, BREAD)))
			return(ISSET(FTS_STOP) ? NULL : p);
E 16
I 16
D 23
		} else if (!(sp->fts_child = fts_build(sp, BREAD))) {
E 23
I 23
		} else if ((sp->fts_child = fts_build(sp, BREAD)) == NULL) {
E 23
D 29
			if ISSET(FTS_STOP)
E 29
I 29
D 34
			p->fts_flags |= FTS_DONTCHDIR;
E 34
			if (ISSET(FTS_STOP))
E 29
D 22
				return(NULL);
E 22
I 22
				return (NULL);
E 22
D 35
			if (p->fts_level == FTS_ROOTLEVEL &&
D 34
			    FCHDIR(sp, sp->fts_rfd)) {
E 34
I 34
			    !ISSET(FTS_NOCHDIR) && FCHDIR(sp, sp->fts_rfd)) {
				saved_errno = errno;
E 34
I 29
				(void)close(sp->fts_rfd);
I 34
				errno = saved_errno;
E 34
E 29
				SET(FTS_STOP);
D 22
				return(NULL);
E 22
I 22
				return (NULL);
E 22
			}
I 29
D 34
			(void)close(sp->fts_rfd);
E 34
I 34
			p->fts_flags |= FTS_DONTCHDIR;
			p->fts_info = FTS_DP;
E 35
E 34
E 29
D 22
			return(p);
E 22
I 22
			return (p);
E 22
		}
E 16
		p = sp->fts_child;
E 14
D 4
	else if (p->info == FTS_SL && instr == FTS_FOLLOW) {
		p->info = fts_stat(p, 1);
E 4
I 4
D 7
	else if (p->fts_info == FTS_SL && instr == FTS_FOLLOW) {
		p->fts_info = fts_stat(p, 1);
E 4
		return(p);
E 7
I 7
		sp->fts_child = NULL;
D 14
		return(sp->fts_cur = p);
E 14
I 14
		goto name;
E 14
E 7
	}

D 7
	/*
D 6
	 * user may have called ftsset on pointer returned by
	 * ftschildren; handle it here.
E 6
I 6
	 * user may have called ftsset on pointer returned by ftschildren;
	 * handle it here.
E 6
	 */
D 4
	for (p = p->link; p;) {
		instr = p->instr;
E 4
I 4
	for (p = p->fts_link; p;) {
		instr = p->fts_instr;
E 4
		if (instr == FTS_FOLLOW) {
D 4
			p->info = fts_stat(p, 1);
			p->instr = 0;
E 4
I 4
			p->fts_info = fts_stat(p, 1);
			p->fts_instr = 0;
E 4
			break;
		}
		if (instr == FTS_SKIP) {
			tmp = p;
D 4
			p = p->link;
E 4
I 4
			p = p->fts_link;
E 4
			(void)free((char *)tmp);
			continue;
		}
D 4
		p->instr = 0;
E 4
I 4
		p->fts_instr = 0;
E 4
		break;
	}

	/* go to next node on this level */
	if (p) {
E 7
I 7
D 11
	/* move to next node on this level */
E 11
I 11
D 28
	/* Move to next node on this level. */
E 28
I 28
	/* Move to the next node on this level. */
E 28
E 11
next:	tmp = p;
	if (p = p->fts_link) {
E 7
D 14
		/*
D 11
		 * if root level node, set up paths and return.  If not the
E 11
I 11
		 * If root level node, set up paths and return.  If not the
E 11
		 * first time, and it's not an absolute pathname, get back
D 7
		 * to wherever we started from.
E 7
I 7
D 11
		 * to starting directory.
E 11
I 11
		 * to starting directory.  If that fails, we're dead.
E 11
E 7
		 */
D 4
		if (p->level == ROOTLEVEL) {
E 4
I 4
		if (p->fts_level == ROOTLEVEL) {
E 4
D 11
			fts_load(p);
D 6
			if (cd) {
D 4
				(void)free((char *)sp->cur);
				if (p->path[0] != '/' && CHDIR(sp, sp->wd)) {
E 4
I 4
				(void)free((char *)sp->fts_cur);
				if (p->fts_path[0] != '/' &&
				    CHDIR(sp, sp->fts_wd)) {
E 4
					/* return target path for error msg */
D 4
					p->path = sp->wd;
					p->info = FTS_ERR;
					sp->options |= FTS__STOP;
					return(sp->cur = p);
E 4
I 4
					p->fts_path = sp->fts_wd;
					p->fts_info = FTS_ERR;
					sp->fts_options |= FTS__STOP;
					return(sp->fts_cur = p);
E 4
				}
			} else
				cd = 1;
E 6
I 6
D 7
			(void)free((char *)sp->fts_cur);
E 7
I 7
			(void)free((void *)tmp);
E 11
I 11
			fts_load(sp, p);
			free((void *)tmp);
E 11
E 7
			if (cd &&
D 7
			    p->fts_path[0] != '/' && CHDIR(sp, sp->fts_wd)) {
				/* return target path for error msg */
				p->fts_path = sp->fts_wd;
E 7
I 7
			    p->fts_path[0] != '/' && FCHDIR(sp, sp->fts_sd)) {
D 11
				/* should never happen... */
E 11
I 11
				/* Can't get back to start; we're dead. */
E 11
				p->fts_path = "starting directory";
E 7
				p->fts_info = FTS_ERR;
D 11
				sp->fts_options |= FTS__STOP;
E 11
I 11
				SET(FTS__STOP);
E 11
				return(sp->fts_cur = p);
D 7
			}
E 7
I 7
			} 
E 7
			cd = 1;
E 6
D 4
			p->info = fts_stat(p, 0);
E 4
I 4
D 11
			p->fts_info = fts_stat(p, 0);
E 11
I 11
			p->fts_info = fts_stat(sp, p, 0);
E 11
I 5
			sp->sdev = p->fts_statb.st_dev;
E 5
E 4
		} else {
D 4
			(void)free((char *)sp->cur);
			cp = sp->path + NAPPEND(p->parent);
E 4
I 4
D 7
			(void)free((char *)sp->fts_cur);
E 7
I 7
D 11
			(void)free((void *)tmp);
E 11
I 11
			free((void *)tmp);
E 14
I 14
		free(tmp);
E 14
E 11

D 11
			/* user may have called ftsset on node */
E 11
I 11
D 14
			/* User may have called fts_set on node. */
E 11
			if (p->fts_instr == FTS_SKIP)
				goto next;
			if (p->fts_instr == FTS_FOLLOW) {
D 11
				p->fts_info = fts_stat(p, 1);
				p->fts_instr = 0;
E 11
I 11
				p->fts_info = fts_stat(sp, p, 1);
				p->fts_instr = FTS__NOINSTR;
E 14
I 14
D 41
		/* If reached the top, load the paths for the next root. */
E 41
I 41
		/*
		 * If reached the top, return to the original directory, and
		 * load the paths for the next root.
		 */
E 41
D 15
		if (p->fts_level == ROOTLEVEL) {
E 15
I 15
		if (p->fts_level == FTS_ROOTLEVEL) {
I 41
			if (!ISSET(FTS_NOCHDIR) && FCHDIR(sp, sp->fts_rfd)) {
				SET(FTS_STOP);
				return (NULL);
			}
E 41
E 15
D 16
			if (!fts_load(sp, p)) {
				SET(FTS_STOP);
E 16
I 16
D 18
			if (!fts_load(sp, p))
E 16
				return(NULL);
E 18
I 18
			fts_load(sp, p);
E 18
E 14
E 11
D 16
			}
E 16
I 14
D 22
			return(sp->fts_cur = p);
E 22
I 22
			return (sp->fts_cur = p);
E 22
		}
E 14

D 11
			/* fill in the paths */
E 11
I 11
D 14
			/* Fill in the paths. */
E 11
E 7
			cp = sp->fts_path + NAPPEND(p->fts_parent);
E 4
			*cp++ = '/';
D 4
			bcopy(p->name, cp, p->namelen + 1);
			if (p->info == FTS_D && (tmp = fts_cycle(p))) {
				sp->savelink = p->link;
				p->link = tmp;
E 4
I 4
			bcopy(p->fts_name, cp, p->fts_namelen + 1);
I 7

D 11
			/* check for directory cycles */
E 11
I 11
			/* Check for directory cycles. */
E 11
E 7
			if (p->fts_info == FTS_D && (tmp = fts_cycle(p))) {
				sp->fts_savelink = p->fts_link;
				p->fts_link = tmp;
I 7
				p->fts_info = FTS_DC;
E 7
E 4
			}
E 14
I 14
D 29
		/* User may have called fts_set on the node. */
		if (p->fts_instr == FTS_SKIP)
			goto next;
E 29
I 28
		/*
D 29
		 * XXX
		 * This may not be able to return to the current directory.
E 29
I 29
		 * User may have called fts_set on the node.  If skipped,
		 * ignore.  If followed, get a file descriptor so we can
		 * get back if necessary.
E 29
		 */
I 29
		if (p->fts_instr == FTS_SKIP)
			goto next;
E 29
E 28
		if (p->fts_instr == FTS_FOLLOW) {
			p->fts_info = fts_stat(sp, p, 1);
I 29
			if (p->fts_info == FTS_D && !ISSET(FTS_NOCHDIR))
				if ((p->fts_symfd =
				    open(".", O_RDONLY, 0)) < 0) {
					p->fts_errno = errno;
					p->fts_info = FTS_ERR;
				} else
					p->fts_flags |= FTS_SYMFOLLOW;
E 29
			p->fts_instr = FTS_NOINSTR;
E 14
		}
I 14

name:		t = sp->fts_path + NAPPEND(p->fts_parent);
		*t++ = '/';
D 46
		bcopy(p->fts_name, t, p->fts_namelen + 1);
E 46
I 46
		memmove(t, p->fts_name, p->fts_namelen + 1);
E 46
E 14
D 4
		return(sp->cur = p);
E 4
I 4
D 22
		return(sp->fts_cur = p);
E 22
I 22
		return (sp->fts_cur = p);
E 22
E 4
	}

D 7
	/* go to parent */
D 4
	p = sp->cur->parent;
	(void)free((char *)sp->cur);
	if (p->level == ROOTPARENTLEVEL) {
E 4
I 4
	p = sp->fts_cur->fts_parent;
	(void)free((char *)sp->fts_cur);
E 7
I 7
D 11
	/* move to parent */
E 11
I 11
D 16
	/* Move to parent. */
E 16
I 16
	/* Move up to the parent node. */
E 16
E 11
	p = tmp->fts_parent;
D 11
	(void)free((void *)tmp);
E 11
I 11
D 14
	free((void *)tmp);
E 14
I 14
	free(tmp);
E 14
E 11

E 7
D 15
	if (p->fts_level == ROOTPARENTLEVEL) {
E 15
I 15
	if (p->fts_level == FTS_ROOTPARENTLEVEL) {
E 15
E 4
		/*
D 11
		 * done; free everything up and set errno to 0 so the user
E 11
I 11
		 * Done; free everything up and set errno to 0 so the user
E 11
		 * can distinguish between error and EOF.
		 */
D 7
		(void)free((char *)p);
E 7
I 7
D 11
		(void)free((void *)p);
E 11
I 11
D 14
		free((void *)p);
E 14
I 14
		free(p);
E 14
E 11
E 7
		errno = 0;
D 4
		return(sp->cur = NULL);
E 4
I 4
D 22
		return(sp->fts_cur = NULL);
E 22
I 22
		return (sp->fts_cur = NULL);
E 22
E 4
	}

I 35
	/* Nul terminate the pathname. */
E 35
D 4
	sp->path[p->pathlen] = '\0';
E 4
I 4
	sp->fts_path[p->fts_pathlen] = '\0';
E 4
D 14
	if (CHDIR(sp, "..")) {
D 4
		sp->options |= FTS__STOP;
		p->info = FTS_ERR;
E 4
I 4
D 11
		sp->fts_options |= FTS__STOP;
E 11
I 11
		SET(FTS__STOP);
E 14
I 14

	/*
D 16
	 * If had a chdir error, set the info field to reflect this, and
	 * restore errno.  The error indicator has to be reset to 0 so that
	 * if the user does an FTS_AGAIN, it all works.  Can't cd up on
	 * the post-order visit to the root node, otherwise will be in the
	 * wrong directory.
E 16
I 16
D 28
	 * Cd back up to the parent directory.  If at a root node, have to cd
	 * back to the original place, otherwise may not be able to access the
	 * original node on post-order.
E 28
I 28
D 29
	 * If at a root node, have to cd back to the starting point, otherwise
	 * may not be able to access the original node on post-order.  If not
	 * a root node, cd up to the parent directory.  Note that errors are
	 * assumed to be caused by an inability to cd to the directory in the
	 * first place.
E 29
I 29
D 35
	 * Change to starting directory.  If at a root node or came through a
	 * symlink, go back through the file descriptor.  Otherwise, just cd
	 * up one directory.
E 35
I 35
	 * Return to the parent directory.  If at a root node or came through
	 * a symlink, go back through the file descriptor.  Otherwise, cd up
	 * one directory.
E 35
E 29
E 28
E 16
	 */
I 16
	if (p->fts_level == FTS_ROOTLEVEL) {
D 35
		if (FCHDIR(sp, sp->fts_rfd)) {
E 35
I 35
		if (!ISSET(FTS_NOCHDIR) && FCHDIR(sp, sp->fts_rfd)) {
E 35
I 34
D 36
			saved_errno = errno;
E 34
I 29
			(void)close(sp->fts_rfd);
I 34
			errno = saved_errno;
E 36
E 34
E 29
			SET(FTS_STOP);
D 22
			return(NULL);
E 22
I 22
			return (NULL);
E 22
		}
D 28
	}
	else if (CHDIR(sp, "..")) {
		SET(FTS_STOP);
D 22
		return(NULL);
E 22
I 22
		return (NULL);
E 22
	}

	/* 
	 * If had a chdir error when trying to get into the directory, set the
	 * info field to reflect this, and restore errno.  The error indicator
	 * has to be reset to 0 so that if the user does an FTS_AGAIN, it all
	 * works.
	 */
E 16
D 24
	if (p->fts_cderr) {
		errno = p->fts_cderr;
		p->fts_cderr = 0;
E 24
I 24
	if (p->fts_errno) {
		errno = p->fts_errno;
		p->fts_errno = 0;
E 28
I 28
D 29
		p->fts_info = FTS_DP;
	} else if (p->fts_errno)
E 28
E 24
E 14
E 11
		p->fts_info = FTS_ERR;
E 4
D 14
	} else
E 14
I 14
D 16
	} else {
D 15
		if (p->fts_level != ROOTLEVEL && CHDIR(sp, "..")) {
E 15
I 15
		if (p->fts_level != FTS_ROOTLEVEL && CHDIR(sp, "..")) {
E 15
			SET(FTS_STOP);
			return(NULL);
		}
E 16
I 16
D 28
	} else
E 28
I 28
	else {
E 29
I 29
D 35
		(void)close(sp->fts_rfd);
E 35
	} else if (p->fts_flags & FTS_SYMFOLLOW) {
		if (FCHDIR(sp, p->fts_symfd)) {
I 34
			saved_errno = errno;
E 34
			(void)close(p->fts_symfd);
I 34
			errno = saved_errno;
E 34
			SET(FTS_STOP);
			return (NULL);
		}
		(void)close(p->fts_symfd);
	} else if (!(p->fts_flags & FTS_DONTCHDIR)) {
E 29
		if (CHDIR(sp, "..")) {
			SET(FTS_STOP);
			return (NULL);
		}
E 28
E 16
E 14
D 4
		p->info = FTS_DP;
	return(sp->cur = p);
E 4
I 4
D 29
		p->fts_info = FTS_DP;
E 29
I 28
	}
I 29
	p->fts_info = p->fts_errno ? FTS_ERR : FTS_DP;
E 29
E 28
I 14
D 16
	}
E 16
E 14
D 22
	return(sp->fts_cur = p);
E 22
I 22
	return (sp->fts_cur = p);
E 22
E 4
}

/*
D 11
 * ftsset takes the stream as an argument although it's not used in this
E 11
I 11
D 16
 * fts_set takes the stream as an argument although it's not used in this
E 16
I 16
 * Fts_set takes the stream as an argument although it's not used in this
E 16
E 11
 * implementation; it would be necessary if anyone wanted to add global
D 11
 * semantics to fts using ftsset.  A possible error return is allowed for
 * similar reasons.
E 11
I 11
 * semantics to fts using fts_set.  An error return is allowed for similar
 * reasons.
E 11
 */
/* ARGSUSED */
I 26
int
E 26
I 13
D 14
int
E 14
E 13
D 11
ftsset(sp, p, instr)
E 11
I 11
fts_set(sp, p, instr)
E 11
	FTS *sp;
	FTSENT *p;
	int instr;
{
I 32
	if (instr && instr != FTS_AGAIN && instr != FTS_FOLLOW &&
	    instr != FTS_NOINSTR && instr != FTS_SKIP) {
		errno = EINVAL;
		return (1);
	}
E 32
D 4
	p->instr = instr;
E 4
I 4
	p->fts_instr = instr;
E 4
D 22
	return(0);
E 22
I 22
	return (0);
E 22
}

FTSENT *
D 11
ftschildren(sp)
E 11
I 11
D 32
fts_children(sp)
E 32
I 32
fts_children(sp, instr)
E 32
E 11
	register FTS *sp;
I 32
	int instr;
E 32
{
I 7
	register FTSENT *p;
	int fd;

I 32
	if (instr && instr != FTS_NAMEONLY) {
		errno = EINVAL;
		return (NULL);
	}

E 32
I 11
	/* Set current node pointer. */
	p = sp->fts_cur;

E 11
E 7
	/*
D 11
	 * set errno to 0 so that user can tell the difference between an
E 11
I 11
D 24
	 * Set errno to 0 so that user can tell the difference between an
E 11
D 14
	 * error and a directory without entries.
E 14
I 14
	 * error and a directory without entries.  If not a directory being
	 * visited in *pre-order*, or we've already had fatal errors, return
	 * immediately.
E 24
I 24
	 * Errno set to 0 so user can distinguish empty directory from
	 * an error.
E 24
E 14
	 */
	errno = 0;
D 4
	if (sp->cur->info != FTS_D || sp->options & FTS__STOP)
E 4
I 4
D 7
	if (sp->fts_cur->fts_info != FTS_D || sp->fts_options & FTS__STOP)
E 7
I 7
D 11
	p = sp->fts_cur;
	if (p->fts_info != FTS_D || sp->fts_options & FTS__STOP)
E 11
I 11
D 14
	if (ISSET(FTS__STOP) ||
	    p->fts_info != FTS_D && p->fts_info != FTS_DNX &&
	    p->fts_info != FTS_DNR)
E 14
I 14
D 24
	if (ISSET(FTS_STOP) || p->fts_info != FTS_D && p->fts_info != FTS_DNR)
E 24
I 24

	/* Fatal errors stop here. */
	if (ISSET(FTS_STOP))
E 24
E 14
E 11
E 7
E 4
D 22
		return(NULL);
E 22
I 22
		return (NULL);
E 22
I 11

I 24
	/* Return logical hierarchy of user's arguments. */
	if (p->fts_info == FTS_INIT)
		return (p->fts_link);

I 28
D 29
/* XXX why FTS_DNR?? */
E 28
	 /* If not a directory being visited in pre-order, stop here. */
	if (p->fts_info != FTS_D && p->fts_info != FTS_DNR)
E 29
I 29
	/*
	 * If not a directory being visited in pre-order, stop here.  Could
	 * allow FTS_DNR, assuming the user has fixed the problem, but the
	 * same effect is available with FTS_AGAIN.
	 */
	if (p->fts_info != FTS_D /* && p->fts_info != FTS_DNR */)
E 29
		return (NULL);

E 24
	/* Free up any previous child list. */
E 11
D 4
	if (sp->child)
		fts_lfree(sp->child);
D 2
	if (sp->child = fts_build(sp, 0)) {
		/*
		 * have to cd up so that the fields of the current node
		 * as returned from readfts will be correct.
		 */
		if (CHDIR(sp, "..")) {
			sp->options |= FTS__STOP;
			return(NULL);
		}
	}
	return(sp->child);
E 2
I 2
	return(sp->child = fts_build(sp, 0));
E 4
I 4
	if (sp->fts_child)
		fts_lfree(sp->fts_child);
D 7
	return(sp->fts_child = fts_build(sp, 0));
E 7
I 7

I 32
	if (instr == FTS_NAMEONLY) {
		sp->fts_options |= FTS_NAMEONLY;
		instr = BNAMES;
	} else 
		instr = BCHILD;

E 32
	/*
D 11
	 * if using chdir on a relative path and called BEFORE ftsread on the
	 * root of a traversal, we can lose because we need to chdir into the
	 * subdirectory, and we don't know where the current directory is to
	 * get back so that the upcoming chdir by ftsread will work.
E 11
I 11
	 * If using chdir on a relative path and called BEFORE fts_read does
D 14
	 * its chdir to the root of a traversal, we can lose because we need
	 * to chdir into the subdirectory, and we don't know where the current
	 * directory is to get back so that the upcoming chdir by fts_read
	 * will work.
E 14
I 14
	 * its chdir to the root of a traversal, we can lose -- we need to
	 * chdir into the subdirectory, and we don't know where the current
	 * directory is, so we can't get back so that the upcoming chdir by
	 * fts_read will work.
E 14
E 11
	 */
D 15
	if (p->fts_level != ROOTLEVEL || p->fts_accpath[0] == '/' ||
E 15
I 15
	if (p->fts_level != FTS_ROOTLEVEL || p->fts_accpath[0] == '/' ||
E 15
D 11
	    sp->fts_options & FTS_NOCHDIR)
E 11
I 11
	    ISSET(FTS_NOCHDIR))
E 11
D 22
		return(sp->fts_child = fts_build(sp, BCHILD));
E 22
I 22
D 32
		return (sp->fts_child = fts_build(sp, BCHILD));
E 32
I 32
		return (sp->fts_child = fts_build(sp, instr));
E 32
E 22

	if ((fd = open(".", O_RDONLY, 0)) < 0)
D 22
		return(NULL);
E 22
I 22
		return (NULL);
E 22
D 32
	sp->fts_child = fts_build(sp, BCHILD);
E 32
I 32
	sp->fts_child = fts_build(sp, instr);
E 32
	if (fchdir(fd))
D 22
		return(NULL);
E 22
I 22
		return (NULL);
E 22
	(void)close(fd);
D 22
	return(sp->fts_child);
E 22
I 22
	return (sp->fts_child);
E 22
E 7
E 4
E 2
}

I 14
/*
 * This is the tricky part -- do not casually change *anything* in here.  The
 * idea is to build the linked list of entries that are used by fts_children
 * and fts_read.  There are lots of special cases.
 *
 * The real slowdown in walking the tree is the stat calls.  If FTS_NOSTAT is
 * set and it's a physical walk (so that symbolic links can't be directories),
D 42
 * we assume that the number of subdirectories in a node is equal to the number
 * of links to the parent.  This allows stat calls to be skipped in any leaf
 * directories and for any nodes after the directories in the parent node have
 * been found.  This empirically cuts the stat calls by about 2/3.
E 42
I 42
 * we can do things quickly.  First, if it's a 4.4BSD file system, the type
 * of the file is in the directory entry.  Otherwise, we assume that the number
 * of subdirectories in a node is equal to the number of links to the parent.
 * The former skips all stat calls.  The latter skips stat calls in any leaf
 * directories and for any files after the subdirectories in the directory have
 * been found, cutting the stat calls by about 2/3.
E 42
 */
E 14
D 26
#define	ISDOT(a)	(a[0] == '.' && (!a[1] || a[1] == '.' && !a[2]))

E 26
D 7
static FTSENT *
D 2
fts_build(sp, set_node_errors)
E 2
I 2
fts_build(sp, set_node)
E 7
I 7
D 13
FTSENT *
E 13
I 13
static FTSENT *
E 13
fts_build(sp, type)
E 7
E 2
	register FTS *sp;
D 2
	int set_node_errors;
E 2
I 2
D 7
	int set_node;
E 7
I 7
	int type;
E 7
E 2
{
	register struct dirent *dp;
	register FTSENT *p, *head;
	register int nitems;
I 14
D 29
	FTSENT *cur;
E 29
I 29
	FTSENT *cur, *tail;
E 29
E 14
	DIR *dirp;
I 26
	void *adjaddr;
E 26
D 2
	int len, level, maxlen, nlinks, saved_errno;
E 2
I 2
D 14
	int descend, len, level, maxlen, nlinks, saved_errno;
E 14
I 14
D 28
	int cderr, descend, len, level, maxlen, nlinks, saved_errno;
E 28
I 28
D 47
	int cderrno, descend, len, level, maxlen, nlinks, saved_errno;
E 47
I 47
	int cderrno, descend, len, level, maxlen, nlinks, oflag, saved_errno;
E 47
E 28
E 14
E 2
	char *cp;

I 11
	/* Set current node pointer. */
E 11
D 4
	p = sp->cur;
	if (!(dirp = opendir(p->accpath))) {
E 4
I 4
D 14
	p = sp->fts_cur;
E 14
I 14
	cur = sp->fts_cur;
E 14
I 11

E 11
D 14
	if (!(dirp = opendir(p->fts_accpath))) {
E 4
D 2
		if (set_node_errors) {
E 2
I 2
D 7
		if (set_node) {
E 7
I 7
		if (type == BREAD) {
E 7
E 2
D 11
			errno = 0;
E 11
D 4
			p->info = FTS_DNR;
E 4
I 4
			p->fts_info = FTS_DNR;
I 11
			errno = 0;
E 11
E 4
		}
E 14
I 14
	/*
	 * Open the directory for reading.  If this fails, we're done.
	 * If being called from fts_read, set the fts_info field.
	 */
D 23
	if (!(dirp = opendir(cur->fts_accpath))) {
E 23
I 23
D 47
	if ((dirp = opendir(cur->fts_accpath)) == NULL) {
E 47
I 47
#ifdef FTS_WHITEOUT
	if (ISSET(FTS_WHITEOUT))
		oflag = DTF_NODUP|DTF_REWIND;
	else
		oflag = DTF_HIDEW|DTF_NODUP|DTF_REWIND;
#else
#define __opendir2(path, flag) opendir(path)
#endif
	if ((dirp = __opendir2(cur->fts_accpath, oflag)) == NULL) {
E 47
E 23
D 25
		if (type == BREAD)
E 25
I 25
		if (type == BREAD) {
E 25
			cur->fts_info = FTS_DNR;
I 25
			cur->fts_errno = errno;
		}
E 25
E 14
D 22
		return(NULL);
E 22
I 22
		return (NULL);
E 22
	}
D 2
	if (CHDIR(sp, p->accpath)) {
		if (set_node_errors) {
			errno = 0;
			p->info = FTS_DNX;
		}
		return(NULL);
	}
E 2

	/*
D 11
	 * the real slowdown in walking the tree is the stat calls.  If
E 11
I 11
D 14
	 * The real slowdown in walking the tree is the stat calls.  If
E 11
	 * FTS_NOSTAT is set and it's a physical walk (so that symbolic
	 * links can't be directories), fts assumes that the number of
	 * subdirectories in a node is equal to the number of links to
	 * the parent.  This allows stat calls to be skipped in any leaf
	 * directories and for any nodes after the directories in the
	 * parent node have been found.  This empirically cuts the stat
	 * calls by about 2/3.
E 14
I 14
	 * Nlinks is the number of possible entries of type directory in the
	 * directory if we're cheating on stat calls, 0 if we're not doing
	 * any stat calls at all, -1 if we're doing stats on everything.
E 14
	 */
D 4
	nlinks = sp->options & FTS_NOSTAT && sp->options & FTS_PHYSICAL ?
	    p->statb.st_nlink - (sp->options & FTS_SEEDOT ? 0 : 2) : -1;
E 4
I 4
D 29
	nlinks =
D 11
	    sp->fts_options & FTS_NOSTAT && sp->fts_options & FTS_PHYSICAL ?
	    p->fts_statb.st_nlink - (sp->fts_options & FTS_SEEDOT ? 0 : 2) : -1;
E 11
I 11
	    ISSET(FTS_NOSTAT) && ISSET(FTS_PHYSICAL) ?
E 29
I 29
D 32
	nlinks = ISSET(FTS_NOSTAT) && ISSET(FTS_PHYSICAL) ?
E 29
D 14
	    p->fts_statb.st_nlink - (ISSET(FTS_SEEDOT) ? 0 : 2) : -1;
E 14
I 14
D 26
	    cur->fts_statb.st_nlink - (ISSET(FTS_SEEDOT) ? 0 : 2) : -1;
E 26
I 26
	    cur->fts_nlink - (ISSET(FTS_SEEDOT) ? 0 : 2) : -1;
E 32
I 32
	if (type == BNAMES)
		nlinks = 0;
	else if (ISSET(FTS_NOSTAT) && ISSET(FTS_PHYSICAL))
		nlinks = cur->fts_nlink - (ISSET(FTS_SEEDOT) ? 0 : 2);
	else
		nlinks = -1;
E 32
E 26
E 14
E 11
E 4

I 29
#ifdef notdef
	(void)printf("nlinks == %d (cur: %d)\n", nlinks, cur->fts_nlink);
	(void)printf("NOSTAT %d PHYSICAL %d SEEDOT %d\n",
	    ISSET(FTS_NOSTAT), ISSET(FTS_PHYSICAL), ISSET(FTS_SEEDOT));
#endif
E 29
D 3
	/* get max file name length that can be stored in current path */
	maxlen = sp->pathlen - p->pathlen - 1;

	cp = sp->path + (len = NAPPEND(p));
	*cp++ = '/';

	level = p->level + 1;

E 3
I 2
D 7
	if (nlinks || set_node) {
E 7
I 7
D 11
	/* if told to descend or found links and not told not to descend. */
	if (nlinks || type == BREAD) {
E 7
		if (FCHDIR(sp, dirfd(dirp))) {
E 11
I 11
D 14
	/* If told to descend or found links and not told not to descend. */
	descend = 0;
E 14
I 14
	/*
	 * If we're going to need to stat anything or we want to descend
D 37
	 * and stay in the directory, chdir.  If this fails we keep going.
E 37
I 37
	 * and stay in the directory, chdir.  If this fails we keep going,
	 * but set a flag so we don't chdir after the post-order visit.
E 37
	 * We won't be able to stat anything, but we can still return the
	 * names themselves.  Note, that since fts_read won't be able to
	 * chdir into the directory, it will have to return different path
	 * names than before, i.e. "a/b" instead of "b".  Since the node
	 * has already been visited in pre-order, have to wait until the
D 29
	 * post-order visit to return the error.  This is all fairly nasty.
	 * If a program needed sorted entries or stat information, they had
	 * better be checking FTS_NS on the returned nodes.
E 29
I 29
	 * post-order visit to return the error.  There is a special case
	 * here, if there was nothing to stat then it's not an error to
	 * not be able to stat.  This is all fairly nasty.  If a program
	 * needed sorted entries or stat information, they had better be
	 * checking FTS_NS on the returned nodes.
E 29
	 */
I 41
	cderrno = 0;
E 41
E 14
	if (nlinks || type == BREAD)
D 14
		if (!FCHDIR(sp, dirfd(dirp))) 
E 14
I 14
		if (FCHDIR(sp, dirfd(dirp))) {
D 29
			if (type == BREAD)
E 29
I 29
D 37
			if (nlinks && type == BREAD)
E 37
I 37
D 38
			if (nlinks && type == BREAD) {
				cur->fts_flags |= FTS_DONTCHDIR;
E 38
I 38
			if (nlinks && type == BREAD)
E 38
E 37
E 29
D 24
				cur->fts_cderr = errno;
E 24
I 24
				cur->fts_errno = errno;
I 37
D 38
			}
E 38
I 38
			cur->fts_flags |= FTS_DONTCHDIR;
E 38
E 37
E 24
D 29
			descend = nlinks = 0;
E 29
I 29
			descend = 0;
E 29
D 28
			cderr = 1;
E 28
I 28
			cderrno = errno;
E 28
D 41
		} else {
E 41
I 41
		} else
E 41
E 14
			descend = 1;
D 14
		/*
D 12
		 * Return all the information possible; fts_read doing a
		 * relative walk of the tree will have to descend, so it
		 * can't succeed.  Fts_children or absolute walks of the
		 * tree can succeed, but no stat information will be available.
E 12
I 12
		 * Return all the information possible; an fts_read doing a
		 * relative walk of the tree will have to descend, so it can't
		 * succeed.  Fts_children or absolute walks of the tree can
		 * succeed, but no stat information will be available.  Reset
		 * errno as necessary.
E 12
		 */
		else {
I 12
			errno = 0;
E 12
E 11
D 7
			if (set_node) {
E 7
I 7
			if (type == BREAD) {
E 7
D 11
				errno = 0;
E 11
I 11
				(void)closedir(dirp);
E 11
D 4
				p->info = FTS_DNX;
E 4
I 4
				p->fts_info = FTS_DNX;
I 11
D 12
				errno = 0;
E 12
				return(NULL);
E 11
E 4
			}
I 7
D 11
			(void)closedir(dirp);
E 7
			return(NULL);
E 11
I 11
			nlinks = 0;
E 14
I 14
D 28
			cderr = 0;
E 28
I 28
D 41
			cderrno = 0;
E 28
E 14
E 11
		}
E 41
I 14
	else
		descend = 0;
E 14
D 11
		descend = 1;
	} else
		descend = 0;
E 11

I 3
D 11
	/* get max file name length that can be stored in current path */
E 11
I 11
D 14
	/* Get max file name length that can be stored in current path. */
E 11
D 4
	maxlen = sp->pathlen - p->pathlen - 1;
E 4
I 4
	maxlen = sp->fts_pathlen - p->fts_pathlen - 1;
E 14
I 14
	/*
	 * Figure out the max file name length that can be stored in the
	 * current path -- the inner loop allocates more path as necessary.
	 * We really wouldn't have to do the maxlen calculations here, we
	 * could do them in fts_read before returning the path, but it's a
	 * lot easier here since the length is part of the dirent structure.
	 *
D 26
	 * If not changing directories set a pointer so that we can just
	 * append each new name into the path.
E 26
I 26
	 * If not changing directories set a pointer so that can just append
	 * each new name into the path.
E 26
	 */
	maxlen = sp->fts_pathlen - cur->fts_pathlen - 1;
	len = NAPPEND(cur);
	if (ISSET(FTS_NOCHDIR)) {
		cp = sp->fts_path + len;
		*cp++ = '/';
	}
E 14
E 4

D 4
	cp = sp->path + (len = NAPPEND(p));
E 4
I 4
D 14
	cp = sp->fts_path + (len = NAPPEND(p));
E 4
	*cp++ = '/';
E 14
I 14
	level = cur->fts_level + 1;
E 14

D 4
	level = p->level + 1;
E 4
I 4
D 14
	level = p->fts_level + 1;
E 4

E 3
E 2
D 11
	/* read the directory, attching each new entry to the `link' pointer */
E 11
I 11
	/* Read the directory, attching each new entry to the `link' pointer. */
E 14
I 14
	/* Read the directory, attaching each entry to the `link' pointer. */
I 26
	adjaddr = NULL;
E 26
E 14
E 11
D 29
	for (head = NULL, nitems = 0; dp = readdir(dirp);) {
E 29
I 29
	for (head = tail = NULL, nitems = 0; dp = readdir(dirp);) {
E 29
D 4
		if (ISDOT(dp->d_name) && !(sp->options & FTS_SEEDOT))
E 4
I 4
D 11
		if (ISDOT(dp->d_name) && !(sp->fts_options & FTS_SEEDOT))
E 11
I 11
D 14
		if (ISDOT(dp->d_name) && !ISSET(FTS_SEEDOT))
E 14
I 14
		if (!ISSET(FTS_SEEDOT) && ISDOT(dp->d_name))
E 14
E 11
E 4
			continue;

D 11
		if (!(p = fts_alloc(dp->d_name, dp->d_namlen))) {
E 11
I 11
D 14
		if (!(p = fts_alloc(sp, dp->d_name, (int)dp->d_namlen))) {
E 11
			saved_errno = errno;
E 14
I 14
D 23
		if (!(p = fts_alloc(sp, dp->d_name, (int)dp->d_namlen)))
E 23
I 23
		if ((p = fts_alloc(sp, dp->d_name, (int)dp->d_namlen)) == NULL)
E 23
E 14
			goto mem1;
D 14
		}
E 14
		if (dp->d_namlen > maxlen) {
D 11
			if (!fts_path((int)dp->d_namlen)) {
				/* quit: this stream no longer has a path */
D 4
				sp->options |= FTS__STOP;
E 4
I 4
				sp->fts_options |= FTS__STOP;
E 11
I 11
D 26
			if (!fts_path(sp, (int)dp->d_namlen)) {
E 26
I 26
D 39
			if (fts_palloc(sp, (int)dp->d_namlen)) {
E 39
I 39
			if (fts_palloc(sp, (size_t)dp->d_namlen)) {
E 39
E 26
D 14
				/* Quit: this stream no longer has a path. */
				SET(FTS__STOP);
E 11
E 4
				saved_errno = errno;
D 7
				(void)free((char *)p);
E 7
I 7
D 11
				(void)free((void *)p);
E 11
I 11
				free((void *)p);
E 11
E 7
mem1:				fts_lfree(head);
D 2
				if (set_node_errors)
E 2
I 2
D 7
				if (set_node)
E 7
I 7
				if (type == BREAD)
E 7
E 2
D 4
					p->info = FTS_ERR;
E 4
I 4
					p->fts_info = FTS_ERR;
E 4
D 2
				if (CHDIR(sp, "..")) {
E 2
I 2
				if (descend && CHDIR(sp, "..")) {
I 11
					/*
					 * chdir error is more interesting
					 * than memory error, since it stops
					 * everything.
					 */
E 11
E 2
					saved_errno = errno;
D 4
					sp->options |= FTS__STOP;
E 4
I 4
D 11
					sp->fts_options |= FTS__STOP;
E 11
I 11
					SET(FTS__STOP);
E 11
E 4
				}
				errno = saved_errno;
E 14
I 14
				/*
				 * No more memory for path or structures.  Save
				 * errno, free up the current structure and the
				 * structures already allocated.
				 */
mem1:				saved_errno = errno;
				if (p)
					free(p);
				fts_lfree(head);
E 14
I 7
				(void)closedir(dirp);
I 14
				errno = saved_errno;
				cur->fts_info = FTS_ERR;
				SET(FTS_STOP);
E 14
E 7
D 22
				return(NULL);
E 22
I 22
				return (NULL);
E 22
			}
I 26
			adjaddr = sp->fts_path;
E 26
D 4
			maxlen = sp->pathlen - sp->cur->pathlen - 1;
E 4
I 4
			maxlen = sp->fts_pathlen - sp->fts_cur->fts_pathlen - 1;
E 4
		}

D 4
		p->pathlen = len + dp->d_namlen + 1;
		p->accpath = sp->options & FTS_NOCHDIR ? p->path : p->name;
E 4
I 4
		p->fts_pathlen = len + dp->d_namlen + 1;
D 11
		p->fts_accpath =
		    sp->fts_options & FTS_NOCHDIR ? p->fts_path : p->fts_name;
E 11
I 11
D 14
		p->fts_accpath = ISSET(FTS_NOCHDIR) ? p->fts_path : p->fts_name;
E 11
E 4

E 14
D 4
		p->parent = sp->cur;
		p->level = level;
E 4
I 4
		p->fts_parent = sp->fts_cur;
		p->fts_level = level;
E 4

I 47
#ifdef FTS_WHITEOUT
D 48
		switch (dp->d_type) {
		case DT_WHT:
E 48
I 48
		if (dp->d_type == DT_WHT)
E 48
			p->fts_flags |= FTS_ISW;
D 48
			break;
		case DT_WHTD:
			p->fts_flags |= FTS_ISWD;
			break;
		}
E 48
#endif

E 47
D 29
		if (nlinks) {
E 29
I 29
		if (cderrno) {
			if (nlinks) {
				p->fts_info = FTS_NS;
				p->fts_errno = cderrno;
			} else
				p->fts_info = FTS_NSOK;
			p->fts_accpath = cur->fts_accpath;
D 42
		} else if (nlinks) {
E 42
I 42
		} else if (nlinks == 0
#ifdef DT_DIR
		    || nlinks > 0 && 
		    dp->d_type != DT_DIR && dp->d_type != DT_UNKNOWN
#endif
		    ) {
			p->fts_accpath =
			    ISSET(FTS_NOCHDIR) ? p->fts_path : p->fts_name;
			p->fts_info = FTS_NSOK;
		} else {
E 42
E 29
D 11
			/* make sure fts_stat has a filename to stat */
D 4
			if (sp->options & FTS_NOCHDIR)
				bcopy(p->name, cp, p->namelen + 1);
			p->info = fts_stat(p, 0);
			if (nlinks > 0 && (p->info == FTS_D ||
			    p->info == FTS_DNR || p->info == FTS_DNX))
E 4
I 4
			if (sp->fts_options & FTS_NOCHDIR)
E 11
I 11
D 14
			/* Make sure fts_stat has a filename to stat. */
			if (ISSET(FTS_NOCHDIR))
E 14
I 14
			/* Build a file name for fts_stat to stat. */
			if (ISSET(FTS_NOCHDIR)) {
				p->fts_accpath = p->fts_path;
E 14
E 11
D 46
				bcopy(p->fts_name, cp, p->fts_namelen + 1);
E 46
I 46
				memmove(cp, p->fts_name, p->fts_namelen + 1);
E 46
I 14
			} else
				p->fts_accpath = p->fts_name;
I 42
			/* Stat it. */
E 42
E 14
D 11
			p->fts_info = fts_stat(p, 0);
E 11
I 11
			p->fts_info = fts_stat(sp, p, 0);
I 42

			/* Decrement link count if applicable. */
E 42
E 11
D 14
			if (nlinks > 0 && (p->fts_info == FTS_D ||
			    p->fts_info == FTS_DNR || p->fts_info == FTS_DNX))
E 14
I 14
D 26
			if (nlinks > 0 && p->fts_info == FTS_D)
E 26
I 26
			if (nlinks > 0 && (p->fts_info == FTS_D ||
			    p->fts_info == FTS_DC || p->fts_info == FTS_DOT))
E 26
E 14
E 4
				--nlinks;
D 14
		} else
D 4
			p->info = FTS_NS;
E 4
I 4
			p->fts_info = FTS_NS;
E 14
I 14
D 28
		} else if (cderr) {
			p->fts_info = ISSET(FTS_NOSTAT) ? FTS_NSOK : FTS_NS;
E 28
I 28
D 29
		} else if (cderrno) {
			if (ISSET(FTS_NOSTAT))
				p->fts_info = FTS_NSOK;
		        else {
				p->fts_info = FTS_NS;
				p->fts_errno = cderrno;
			}
E 28
			p->fts_accpath = cur->fts_accpath;
E 29
D 42
		} else {
			p->fts_accpath =
			    ISSET(FTS_NOCHDIR) ? p->fts_path : p->fts_name;
			p->fts_info = FTS_NSOK;
E 42
		}
E 14
E 4

D 4
		p->link = head;
E 4
I 4
D 29
		p->fts_link = head;
E 4
		head = p;
E 29
I 29
		/* We walk in directory order so "ls -f" doesn't get upset. */
		p->fts_link = NULL;
		if (head == NULL)
			head = tail = p;
		else {
			tail->fts_link = p;
			tail = p;
		}
E 29
		++nitems;
	}
	(void)closedir(dirp);

I 2
D 7
	if (descend && (!nitems || !set_node) && CHDIR(sp, "..")) {
E 7
I 7
D 11
	/* reset the path */
E 11
I 11
D 14
	/* Reset the path. */
E 11
	if (cp - 1 > sp->fts_path)
		--cp;
	*cp = '\0';
E 14
I 14
	/*
I 26
	 * If had to realloc the path, adjust the addresses for the rest
	 * of the tree.
	 */
	if (adjaddr)
		fts_padjust(sp, adjaddr);

	/*
E 26
	 * If not changing directories, reset the path back to original
	 * state.
	 */
	if (ISSET(FTS_NOCHDIR)) {
		if (cp - 1 > sp->fts_path)
			--cp;
		*cp = '\0';
	}
E 14

	/*
D 11
	 * if descended: if were called from ftsread and didn't find anything,
	 * or were called from ftschildren, get back.
E 11
I 11
D 14
	 * If descended: if were called from fts_read and didn't find anything,
	 * or were called from fts_children, get back.
E 14
I 14
D 45
	 * If descended after called from fts_children or called from
	 * fts_read and didn't find anything, get back.  If can't get
D 26
	 * back, we're done.
E 26
I 26
	 * back, done.
E 45
I 45
	 * If descended after called from fts_children or after called from
	 * fts_read and nothing found, get back.  At the root level we use
	 * the saved fd; if one of fts_open()'s arguments is a relative path
	 * to an empty directory, we wind up here with no other way back.  If
	 * can't get back, we're done.
E 45
E 26
E 14
E 11
	 */
D 45
	if (descend && (!nitems || type == BCHILD) && CHDIR(sp, "..")) {
E 45
I 45
	if (descend && (type == BCHILD || !nitems) &&
	    (cur->fts_level == FTS_ROOTLEVEL ?
	    FCHDIR(sp, sp->fts_rfd) : CHDIR(sp, ".."))) {
E 45
E 7
D 4
		sp->options |= FTS__STOP;
		p->info = FTS_ERR;
E 4
I 4
D 11
		sp->fts_options |= FTS__STOP;
E 11
I 11
D 14
		SET(FTS__STOP);
E 11
		p->fts_info = FTS_ERR;
E 14
I 14
		cur->fts_info = FTS_ERR;
		SET(FTS_STOP);
E 14
E 4
D 7
		*--cp = '\0';
E 7
D 22
		return(NULL);
E 22
I 22
		return (NULL);
E 22
	}

I 14
D 26
	/* If we didn't find anything, just do the post-order visit */
E 26
I 26
D 34
	/* If didn't find anything, just do the post-order visit */
E 26
E 14
E 2
	if (!nitems) {
D 2
		if (CHDIR(sp, "..")) {
			sp->options |= FTS__STOP;
			p->info = FTS_ERR;
		} else if (set_node_errors)
E 2
I 2
D 7
		if (set_node)
E 7
I 7
		if (type == BREAD)
E 7
E 2
D 4
			p->info = FTS_DP;
E 4
I 4
D 14
			p->fts_info = FTS_DP;
E 14
I 14
			cur->fts_info = FTS_DP;
E 34
I 34
	/* If didn't find anything, return NULL. */
D 35
	if (!nitems)
E 35
I 35
	if (!nitems) {
		if (type == BREAD)
			cur->fts_info = FTS_DP;
E 35
E 34
E 14
E 4
D 7
		*--cp = '\0';
E 7
D 22
		return(NULL);
E 22
I 22
		return (NULL);
I 35
	}
E 35
E 22
D 34
	}
E 34

I 14
	/* Sort the entries. */
E 14
D 4
	if (sp->compar && nitems > 1)
E 4
I 4
	if (sp->fts_compar && nitems > 1)
E 4
D 11
		head = fts_sort(head, nitems);
E 11
I 11
		head = fts_sort(sp, head, nitems);
E 11
D 14

D 2
	if (set_node_errors)
E 2
I 2
D 7
	if (set_node)
E 2
D 4
		bcopy(head->name, cp, head->namelen + 1);
E 4
I 4
		bcopy(head->fts_name, cp, head->fts_namelen + 1);
E 4
	else
		*--cp = '\0';
E 7
I 7
	if (type == BREAD) {
		*cp = '/';
		bcopy(head->fts_name, cp + 1, head->fts_namelen + 1);
	}
E 14
E 7
D 22
	return(head);
E 22
I 22
	return (head);
E 22
}

D 11
static short
fts_stat(p, symflag)
E 11
I 11
static u_short
fts_stat(sp, p, follow)
	FTS *sp;
E 11
	register FTSENT *p;
D 11
	int symflag;
E 11
I 11
	int follow;
E 11
{
I 24
	register FTSENT *t;
	register dev_t dev;
	register ino_t ino;
I 26
	struct stat *sbp, sb;
E 26
E 24
I 14
	int saved_errno;

I 26
	/* If user needs stat info, stat buffer already allocated. */
	sbp = ISSET(FTS_NOSTAT) ? &sb : p->fts_statp;
I 47

#ifdef FTS_WHITEOUT
	/* check for whiteout */
D 48
	if (p->fts_flags & (FTS_ISW|FTS_ISWD)) {
E 48
I 48
	if (p->fts_flags & FTS_ISW) {
E 48
		if (sbp != &sb) {
			memset(sbp, '\0', sizeof (*sbp));
			sbp->st_mode = S_IFWHT;
		}
		return (FTS_W);
	}
#endif
E 47
	
E 26
E 14
D 3
	register int ngroups, *gp;
	int gidset[NGROUPS];

E 3
	/*
D 11
	 * detection of symbolic links w/o targets.  If FTS_FOLLOW is set,
	 * the symlink structure is overwritten with the stat structure of
	 * the target.
E 11
I 11
	 * If doing a logical walk, or application requested FTS_FOLLOW, do
D 14
	 * a stat(2).  If that fails, either fail or do an lstat(2) for a
	 * non-existent symlink.  (The check has to be done, or we wouldn't
	 * detect a symlink being deleted.)
	 *
	 * Don't leave errno set for FTS_NS cases.		XXX
E 14
I 14
	 * a stat(2).  If that fails, check for a non-existent symlink.  If
D 24
	 * fail, return the errno from the stat call.
E 24
I 24
	 * fail, set the errno from the stat call.
E 24
E 14
E 11
	 */
D 4
	if (stream->options & FTS_LOGICAL || symflag) {
		if (stat(p->accpath, &p->statb))
			return(symflag || !lstat(p->accpath, &p->statb) ?
			    FTS_SLNONE : FTS_ERR);
	} else if (lstat(p->accpath, &p->statb))
E 4
I 4
D 11
	if (stream->fts_options & FTS_LOGICAL || symflag) {
		if (stat(p->fts_accpath, &p->fts_statb))
			return(symflag || !lstat(p->fts_accpath,
			    &p->fts_statb) ? FTS_SLNONE : FTS_ERR);
	} else if (lstat(p->fts_accpath, &p->fts_statb))
E 4
		return(FTS_ERR);
E 11
I 11
	if (ISSET(FTS_LOGICAL) || follow) {
D 26
		if (stat(p->fts_accpath, &p->fts_statb)) {
E 26
I 26
		if (stat(p->fts_accpath, sbp)) {
E 26
D 14
			errno = 0;
			if (follow && !lstat(p->fts_accpath, &p->fts_statb))
				return(FTS_SLNONE);
			else {
E 14
I 14
			saved_errno = errno;
D 26
			if (!lstat(p->fts_accpath, &p->fts_statb)) {
E 26
I 26
			if (!lstat(p->fts_accpath, sbp)) {
E 26
E 14
				errno = 0;
D 14
				return(FTS_NS);
			}
E 14
I 14
D 22
				return(FTS_SLNONE);
E 22
I 22
				return (FTS_SLNONE);
E 22
			} 
D 24
			errno = saved_errno;
E 24
I 24
			p->fts_errno = saved_errno;
E 24
D 26
			bzero(&p->fts_statb, sizeof(struct stat));
D 22
			return(FTS_NS);
E 22
I 22
			return (FTS_NS);
E 26
I 26
			goto err;
E 26
E 22
E 14
		}
D 26
	} else if (lstat(p->fts_accpath, &p->fts_statb)) {
E 26
I 26
	} else if (lstat(p->fts_accpath, sbp)) {
E 26
I 24
		p->fts_errno = errno;
E 24
D 14
		errno = 0;
E 14
I 14
D 26
		bzero(&p->fts_statb, sizeof(struct stat));
E 26
I 26
D 46
err:		bzero(sbp, sizeof(struct stat));
E 46
I 46
err:		memset(sbp, 0, sizeof(struct stat));
E 46
E 26
E 14
D 22
		return(FTS_NS);
E 22
I 22
		return (FTS_NS);
E 22
	}
E 11

D 4
	switch(p->statb.st_mode&S_IFMT) {
E 4
I 4
D 11
	switch(p->fts_statb.st_mode&S_IFMT) {
E 4
	case S_IFDIR:
E 11
I 11
D 14
	if (S_ISDIR(p->fts_statb.st_mode))
E 14
I 14
D 26
	/*
	 * Cycle detection is done as soon as we find a directory.  Detection
	 * is by brute force; if the tree gets deep enough or the number of
	 * symbolic links to directories high enough something faster might
	 * be worthwhile.
	 */
	if (S_ISDIR(p->fts_statb.st_mode)) {
D 24
		register FTSENT *t;
		register dev_t dev;
		register ino_t ino;

E 24
		dev = p->fts_statb.st_dev;
		ino = p->fts_statb.st_ino;
D 15
		for (t = p->fts_parent; t->fts_level > ROOTLEVEL;
E 15
I 15
D 21
		for (t = p->fts_parent; t->fts_level > FTS_ROOTLEVEL;
E 21
I 21
		for (t = p->fts_parent; t->fts_level >= FTS_ROOTLEVEL;
E 21
E 15
		    t = t->fts_parent)
			if (ino == t->fts_statb.st_ino &&
			    dev == t->fts_statb.st_dev) {
E 26
I 26
	if (S_ISDIR(sbp->st_mode)) {
D 29
		if (ISDOT(p->fts_name))
			return (FTS_DOT);
E 29
		/*
		 * Set the device/inode.  Used to find cycles and check for
		 * crossing mount points.  Also remember the link count, used
		 * in fts_build to limit the number of stat calls.  It is
		 * understood that these fields are only referenced if fts_info
		 * is set to FTS_D.
		 */
		dev = p->fts_dev = sbp->st_dev;
		ino = p->fts_ino = sbp->st_ino;
		p->fts_nlink = sbp->st_nlink;

I 29
		if (ISDOT(p->fts_name))
			return (FTS_DOT);

E 29
		/*
		 * Cycle detection is done by brute force when the directory
		 * is first encountered.  If the tree gets deep enough or the
		 * number of symbolic links to directories is high enough,
		 * something faster might be worthwhile.
		 */
		for (t = p->fts_parent;
		    t->fts_level >= FTS_ROOTLEVEL; t = t->fts_parent)
			if (ino == t->fts_ino && dev == t->fts_dev) {
E 26
D 21
				sp->fts_savelink = p->fts_link;
				p->fts_link = t;
E 21
I 21
				p->fts_cycle = t;
E 21
D 22
				return(FTS_DC);
E 22
I 22
				return (FTS_DC);
E 22
			}
E 14
E 11
D 3
		/* get new uid/groups each time, they may have changed */
		if (getuid() == p->statb.st_uid) {
			if (!(p->statb.st_mode&S_IRUSR))
				return(FTS_DNR);
			if (!(p->statb.st_mode&S_IXUSR))
				return(FTS_DNX);
			return(FTS_D);
		}
		if ((ngroups = getgroups(NGROUPS, gidset)) == -1)
			return(FTS_ERR);
		for (gp = gidset; ngroups--;)
			if (*gp++ == p->statb.st_gid) {
				if (!(p->statb.st_mode&S_IRGRP))
					return(FTS_DNR);
				if (!(p->statb.st_mode&S_IXGRP))
					return(FTS_DNX);
				return(FTS_D);
			}
		if (!(p->statb.st_mode&S_IROTH))
			return(FTS_DNR);
		if (!(p->statb.st_mode&S_IXOTH))
			return(FTS_DNX);
E 3
D 22
		return(FTS_D);
E 22
I 22
		return (FTS_D);
E 22
I 14
	}
E 14
D 11
	case S_IFLNK:
E 11
I 11
D 26
	if (S_ISLNK(p->fts_statb.st_mode))
E 26
I 26
	if (S_ISLNK(sbp->st_mode))
E 26
E 11
D 22
		return(FTS_SL);
E 22
I 22
		return (FTS_SL);
E 22
D 11
	case S_IFREG:
E 11
I 11
D 26
	if (S_ISREG(p->fts_statb.st_mode))
E 26
I 26
	if (S_ISREG(sbp->st_mode))
E 26
E 11
D 22
		return(FTS_F);
D 3
	default:
		return(FTS_DEFAULT);
E 3
D 11
	}
E 11
D 3
	/* NOTREACHED */
E 3
I 3
	return(FTS_DEFAULT);
E 22
I 22
		return (FTS_F);
	return (FTS_DEFAULT);
E 22
E 3
}

D 14
static FTSENT *
fts_cycle(p)
	register FTSENT *p;
{
	register dev_t dev;
	register ino_t ino;

	/*
D 11
	 * cycle detection is brute force; if the tree gets deep enough or
E 11
I 11
	 * Cycle detection is brute force; if the tree gets deep enough or
E 11
	 * the number of symbolic links to directories is really high
	 * something faster might be worthwhile.
	 */
D 4
	dev = p->statb.st_dev;
	ino = p->statb.st_ino;
	for (p = p->parent; p->level > ROOTLEVEL; p = p->parent)
		if (ino == p->statb.st_ino && dev == p->statb.st_dev)
E 4
I 4
	dev = p->fts_statb.st_dev;
	ino = p->fts_statb.st_ino;
	for (p = p->fts_parent; p->fts_level > ROOTLEVEL; p = p->fts_parent)
		if (ino == p->fts_statb.st_ino && dev == p->fts_statb.st_dev)
E 4
			return(p);
	return(NULL);
}

E 14
D 26
#define	R(type, nelem, ptr) \
D 7
	(type *)realloc((char *)ptr, (u_int)((nelem) * sizeof(type)))
E 7
I 7
D 22
	(type *)realloc((void *)ptr, (u_int)((nelem) * sizeof(type)))
E 22
I 22
	realloc((void *)ptr, (u_int)((nelem) * sizeof(type)))
E 22
E 7

E 26
static FTSENT *
D 11
fts_sort(head, nitems)
E 11
I 11
fts_sort(sp, head, nitems)
	FTS *sp;
E 11
	FTSENT *head;
	register int nitems;
{
	register FTSENT **ap, *p;

	/*
D 11
	 * construct an array of pointers to the structures and call qsort(3).
E 11
I 11
	 * Construct an array of pointers to the structures and call qsort(3).
E 11
	 * Reassemble the array in the order returned by qsort.  If unable to
	 * sort for memory reasons, return the directory entries in their
	 * current order.  Allocate enough space for the current needs plus
D 26
	 * 40 so we don't realloc one entry at a time.
E 26
I 26
	 * 40 so don't realloc one entry at a time.
E 26
	 */
D 4
	if (nitems > stream->nitems) {
		stream->nitems = nitems + 40;
		if (!(stream->array =
		    R(FTSENT *, stream->nitems, stream->array))) {
			stream->nitems = 0;
E 4
I 4
D 11
	if (nitems > stream->fts_nitems) {
		stream->fts_nitems = nitems + 40;
		if (!(stream->fts_array =
		    R(FTSENT *, stream->fts_nitems, stream->fts_array))) {
			stream->fts_nitems = 0;
E 11
I 11
	if (nitems > sp->fts_nitems) {
		sp->fts_nitems = nitems + 40;
D 23
		if (!(sp->fts_array =
		    R(FTSENT *, sp->fts_nitems, sp->fts_array))) {
E 23
I 23
D 26
		if ((sp->fts_array =
		    R(FTSENT *, sp->fts_nitems, sp->fts_array)) == NULL) {
E 26
I 26
		if ((sp->fts_array = realloc(sp->fts_array,
		    (size_t)(sp->fts_nitems * sizeof(FTSENT *)))) == NULL) {
E 26
E 23
			sp->fts_nitems = 0;
E 11
E 4
D 22
			return(head);
E 22
I 22
			return (head);
E 22
		}
	}
D 4
	for (ap = stream->array, p = head; p; p = p->link)
E 4
I 4
D 11
	for (ap = stream->fts_array, p = head; p; p = p->fts_link)
E 11
I 11
	for (ap = sp->fts_array, p = head; p; p = p->fts_link)
E 11
E 4
		*ap++ = p;
D 4
	qsort((char *)stream->array, nitems, sizeof(FTSENT *), stream->compar);
	for (head = *(ap = stream->array); --nitems; ++ap)
		ap[0]->link = ap[1];
	ap[0]->link = NULL;
E 4
I 4
D 7
	qsort((char *)stream->fts_array, nitems, sizeof(FTSENT *),
E 7
I 7
D 11
	qsort((void *)stream->fts_array, nitems, sizeof(FTSENT *),
E 7
	    stream->fts_compar);
	for (head = *(ap = stream->fts_array); --nitems; ++ap)
E 11
I 11
	qsort((void *)sp->fts_array, nitems, sizeof(FTSENT *), sp->fts_compar);
	for (head = *(ap = sp->fts_array); --nitems; ++ap)
E 11
		ap[0]->fts_link = ap[1];
	ap[0]->fts_link = NULL;
E 4
D 22
	return(head);
E 22
I 22
	return (head);
E 22
}

static FTSENT *
D 11
fts_alloc(name, len)
E 11
I 11
D 39
fts_alloc(sp, name, len)
E 39
I 39
fts_alloc(sp, name, namelen)
E 39
	FTS *sp;
E 11
	char *name;
D 39
	register int len;
E 39
I 39
	register int namelen;
E 39
{
	register FTSENT *p;
I 26
D 39
	int needstat;
E 39
I 39
	size_t len;
E 39
E 26

	/*
D 11
	 * variable sized structures; the name is the last element so
E 11
I 11
D 26
	 * Variable sized structures; the name is the last element so
E 11
D 14
	 * allocate enough extra space after the structure to hold it.
E 14
I 14
	 * we allocate enough extra space after the structure to store
	 * it.
E 26
I 26
D 39
	 * Variable sized structures.  The stat structure isn't necessary
	 * if the user doesn't need it, and the name is variable length.
	 * Allocate enough extra space after the structure to store them.
E 39
I 39
	 * The file name is a variable length array and no stat structure is
	 * necessary if the user has set the nostat bit.  Allocate the FTSENT
	 * structure, the file name and the stat structure in one chunk, but
	 * be careful that the stat structure is reasonably aligned.  Since the
	 * fts_name field is declared to be of size 1, the fts_name pointer is
	 * namelen + 2 before the first possible address of the stat structure.
E 39
E 26
E 14
	 */
D 7
	if (!(p = (FTSENT *)malloc((u_int)(sizeof(FTSENT) + len))))
E 7
I 7
D 22
	if (!(p = (FTSENT *)malloc((size_t)(sizeof(FTSENT) + len))))
E 7
		return(NULL);
E 22
I 22
D 26
	if ((p = malloc((size_t)(sizeof(FTSENT) + len))) == NULL)
E 26
I 26
D 31
	needstat = ISSET(FTS_NOSTAT) ? 0 : sizeof(struct stat);
E 31
I 31
D 39
	needstat = ISSET(FTS_NOSTAT) ? 0 : ALIGN(sizeof(struct stat));
E 31
	if ((p = malloc((size_t)(sizeof(FTSENT) + len + 1 + needstat))) == NULL)
E 39
I 39
	len = sizeof(FTSENT) + namelen;
	if (!ISSET(FTS_NOSTAT))
		len += sizeof(struct stat) + ALIGNBYTES;
	if ((p = malloc(len)) == NULL)
E 39
E 26
		return (NULL);
E 22
D 4
	bcopy(name, p->name, len + 1);
	p->namelen = len;
	p->path = stream->path;
	p->instr = 0;
	p->local.number = 0;
	p->local.pointer = NULL;
E 4
I 4
D 39
	bcopy(name, p->fts_name, len + 1);
I 26
	if (needstat)
D 31
		p->fts_statp = (struct stat *)(p->fts_name + len + 1);
E 31
I 31
		p->fts_statp = (struct stat *)ALIGN(p->fts_name + len + 1);
E 31
E 26
	p->fts_namelen = len;
E 39
I 39

	/* Copy the name plus the trailing NULL. */
D 46
	bcopy(name, p->fts_name, namelen + 1);
E 46
I 46
	memmove(p->fts_name, name, namelen + 1);
E 46

	if (!ISSET(FTS_NOSTAT))
		p->fts_statp = (struct stat *)ALIGN(p->fts_name + namelen + 2);
	p->fts_namelen = namelen;
E 39
D 11
	p->fts_path = stream->fts_path;
	p->fts_instr = 0;
	p->fts_local.number = 0;
	p->fts_local.pointer = NULL;
E 11
I 11
	p->fts_path = sp->fts_path;
D 14
	p->fts_instr = FTS__NOINSTR;
E 14
I 14
D 29
	p->fts_instr = FTS_NOINSTR;
E 29
D 24
	p->fts_cderr = 0;
E 24
I 24
	p->fts_errno = 0;
I 29
	p->fts_flags = 0;
	p->fts_instr = FTS_NOINSTR;
E 29
E 24
E 14
	p->fts_number = 0;
I 26
D 33
#ifdef NOT_NECESSARY
E 33
E 26
	p->fts_pointer = NULL;
I 26
D 33
#endif
E 33
E 26
E 11
E 4
D 22
	return(p);
E 22
I 22
	return (p);
E 22
}

D 11
static
E 11
I 11
static void
E 11
fts_lfree(head)
	register FTSENT *head;
{
	register FTSENT *p;

I 11
	/* Free a linked list of structures. */
E 11
	while (p = head) {
D 4
		head = head->link;
E 4
I 4
		head = head->fts_link;
E 4
D 7
		(void)free((char *)p);
E 7
I 7
D 11
		(void)free((void *)p);
E 11
I 11
D 14
		free((void *)p);
E 14
I 14
		free(p);
E 14
E 11
E 7
	}
}

/*
D 11
 * allow essentially unlimited paths; certain programs (find, remove, ls)
 * need to work on any tree.  Most systems will allow creation of paths
 * much longer than MAXPATHLEN, even though the kernel won't resolve them.
 * Add an extra 128 bytes to the requested size so that we don't realloc
 * the path 2 bytes at a time.
E 11
I 11
D 26
 * Allow essentially unlimited paths; certain programs (find, rm, ls) need to
 * work on any tree.  Most systems will allow creation of paths much longer
 * than MAXPATHLEN, even though the kernel won't resolve them.  Add an extra
 * 128 bytes to the requested size so that we don't realloc the path 2 bytes
 * at a time.
E 26
I 26
 * Allow essentially unlimited paths; find, rm, ls should all work on any tree.
 * Most systems will allow creation of paths much longer than MAXPATHLEN, even
 * though the kernel won't resolve them.  Add the size (not just what's needed)
 * plus 256 bytes so don't realloc the path 2 bytes at a time. 
E 26
E 11
 */
D 7
static
E 7
I 7
D 26
static char *
E 7
D 11
fts_path(size)
E 11
I 11
fts_path(sp, size)
E 26
I 26
static int
fts_palloc(sp, more)
E 26
	FTS *sp;
E 11
D 26
	int size;
E 26
I 26
D 39
	int more;
E 39
I 39
	size_t more;
E 39
E 26
{
D 4
	stream->pathlen += size + 128;
	return((int)(stream->path = R(char, stream->pathlen, stream->path)));
E 4
I 4
D 11
	stream->fts_pathlen += size + 128;
D 7
	return((int)(stream->fts_path =
	    R(char, stream->fts_pathlen, stream->fts_path)));
E 7
I 7
	return(stream->fts_path =
	    R(char, stream->fts_pathlen, stream->fts_path));
E 7
E 4
}
E 11
I 11
D 26
	sp->fts_pathlen += size + 128;
D 13
	return(sp->fts_path = R(char, sp->fts_pathlen, sp->fts_path)); }
E 13
I 13
D 22
	return(sp->fts_path = R(char, sp->fts_pathlen, sp->fts_path));
E 22
I 22
	return (sp->fts_path = R(char, sp->fts_pathlen, sp->fts_path));
E 26
I 26
D 39

E 39
	sp->fts_pathlen += more + 256;
	sp->fts_path = realloc(sp->fts_path, (size_t)sp->fts_pathlen);
	return (sp->fts_path == NULL);
}

/*
 * When the path is realloc'd, have to fix all of the pointers in structures
 * already returned.
 */
static void
fts_padjust(sp, addr)
	FTS *sp;
	void *addr;
{
	FTSENT *p;

D 40
#define	ADJUST(p) { \
	(p)->fts_accpath = addr + ((p)->fts_accpath - (p)->fts_path); \
	(p)->fts_path = addr; \
E 40
I 40
#define	ADJUST(p) {							\
D 44
	(p)->fts_accpath = addr + ((p)->fts_accpath - (p)->fts_path);	\
E 44
I 44
	(p)->fts_accpath =						\
	    (char *)addr + ((p)->fts_accpath - (p)->fts_path);		\
E 44
	(p)->fts_path = addr;						\
E 40
}
	/* Adjust the current set of children. */
	for (p = sp->fts_child; p; p = p->fts_link)
		ADJUST(p);

	/* Adjust the rest of the tree. */
	for (p = sp->fts_cur; p->fts_level >= FTS_ROOTLEVEL;) {
		ADJUST(p);
		p = p->fts_link ? p->fts_link : p->fts_parent;
	}
I 40
}

static size_t
fts_maxarglen(argv)
	char * const *argv;
{
	size_t len, max;

	for (max = 0; *argv; ++argv)
		if ((len = strlen(*argv)) > max)
			max = len;
	return (max);
E 40
E 26
E 22
D 14
}
E 13
E 11

static FTSENT *
D 11
fts_root(name)
E 11
I 11
fts_root(sp, name)
	FTS *sp;
E 11
	register char *name;
{
	register char *cp;

	/*
D 11
	 * rip trailing slashes; it's somewhat unclear in POSIX 1003.1 what
E 11
I 11
	 * Rip trailing slashes; it's somewhat unclear in POSIX 1003.1 what
E 11
	 * /a/b/ really is, they don't talk about what a null path component
	 * resolves to.  This hopefully does what the user intended.  Don't
	 * allow null pathnames.
	 */
	for (cp = name; *cp; ++cp);
	if (cp == name) {
		errno = ENOENT;
		return(NULL);
	}
I 13
#ifdef notdef
E 13
	while (--cp > name && *cp == '/');
	*++cp = '\0';
D 11
	return(fts_alloc(name, cp - name));
E 11
I 11
D 13
	return(fts_alloc(sp, name, cp - name));
E 13
I 13
#endif
	return(fts_alloc(sp, name, cp - name + 1));
E 14
E 13
E 11
}
E 1
