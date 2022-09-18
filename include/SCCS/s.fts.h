h19266
s 00000/00001/00102
d D 8.3 94/08/14 21:19:58 mckusick 27 26
c FTS_ISWD is gone
e
s 00007/00003/00096
d D 8.2 94/07/28 03:38:27 pendry 26 25
c changes for whiteouts and union filesystem
e
s 00002/00002/00097
d D 8.1 93/06/02 20:05:29 bostic 25 24
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00098
d D 5.24 92/05/05 11:52:28 bostic 24 23
c typo
e
s 00002/00006/00097
d D 5.23 92/03/05 16:33:02 elan 23 22
c Made fts_pointer and fts_number fields separate fields.
e
s 00007/00004/00096
d D 5.22 92/03/01 13:24:18 bostic 22 21
c add options arg to fts_children, add FTS_NAMEONLY flag
e
s 00008/00007/00092
d D 5.21 92/02/04 16:48:44 bostic 21 20
c add FTS_COMFOLLOW flag
e
s 00005/00000/00094
d D 5.20 92/02/03 16:46:41 bostic 20 19
c add fts_symfd so can return after FTS_FOLLOW of a symlink; add flags
c field in FTSENT struct for chdir errors and symlink traversal
e
s 00017/00012/00077
d D 5.19 92/01/15 17:18:25 bostic 19 18
c add inode/dev and nlink count, make statb a pointer so don't have to
c allocate stat structure; add FTS_DOT back in; minor lint
e
s 00002/00001/00087
d D 5.18 92/01/09 17:26:09 bostic 18 17
c fts_children needs to return user's logical hierarchy;
c make fts_errno visible to the user and add FTS_INIT state
e
s 00002/00002/00086
d D 5.17 91/12/30 17:42:12 bostic 17 16
c get rid of the savelink stuff and just add another pointer field
c to the FTSENT structure
e
s 00000/00001/00088
d D 5.16 91/12/23 17:24:16 bostic 16 15
c fts_dfd unused
e
s 00002/00002/00087
d D 5.15 91/11/28 13:56:42 bostic 15 14
c pointers to pointers, not pointers
e
s 00005/00000/00084
d D 5.14 91/04/03 16:11:27 bostic 14 13
c protect all user-level include files against reinclusion
e
s 00003/00000/00081
d D 5.13 91/03/11 09:14:12 bostic 13 12
c add #defines for root and root parent -- used by applications
e
s 00027/00021/00054
d D 5.12 91/03/09 18:08:53 bostic 12 11
c return errno consistently, return directory contents if not searchable
e
s 00001/00001/00074
d D 5.11 91/02/22 19:50:29 donn 11 10
c const char ** => char * const *
e
s 00010/00011/00065
d D 5.10 91/02/12 20:14:41 bostic 10 9
c add cdefs.h, redo the function prototypes
e
s 00026/00023/00050
d D 5.9 90/11/15 13:29:13 bostic 9 8
c change routine names, lots of wording changes, add FTS__NOINSTR
e
s 00001/00001/00072
d D 5.8 90/07/01 15:32:34 bostic 8 7
c typo
e
s 00005/00006/00068
d D 5.7 90/06/09 16:26:23 bostic 7 6
c remove FTS_MULTIPLE
e
s 00001/00011/00073
d D 5.6 90/06/01 14:00:42 bostic 6 5
c new copyright notice
e
s 00001/00001/00083
d D 5.5 90/05/29 19:26:46 bostic 5 4
c C++ wants the prototypes, too
e
s 00001/00001/00083
d D 5.4 90/05/23 19:29:13 bostic 4 3
c use a file descriptor open to ".", not a full path buffer
e
s 00001/00000/00082
d D 5.3 90/05/22 13:11:17 bostic 3 2
c add FTS_XDEV
e
s 00033/00025/00049
d D 5.2 90/05/15 13:18:43 bostic 2 1
c rename a la POSIX 1003.1, STDC cleanup
e
s 00074/00000/00000
d D 5.1 89/12/30 15:57:56 bostic 1 0
c date and time created 89/12/30 15:57:56 by bostic
e
u
U
t
T
I 1
/*
D 25
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 25
I 25
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 25
 *
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
 *
 *	%W% (Berkeley) %G%
 */

I 14
#ifndef	_FTS_H_
#define	_FTS_H_

E 14
D 9
typedef struct fts {
D 2
	struct ftsent *cur;		/* current node */
	struct ftsent *child;		/* linked list of children */
	struct ftsent *savelink;	/* saved link if node had a cycle */
	struct ftsent **array;		/* sort array */
	char *path;			/* path for this descent */
	char *wd;			/* starting directory */
	int pathlen;			/* sizeof(path) */
	int nitems;			/* elements in the sort array */
	int (*compar)();		/* compare function */
E 2
I 2
	struct ftsent *fts_cur;		/* current node */
	struct ftsent *fts_child;	/* linked list of children */
	struct ftsent *fts_savelink;	/* saved link if node had a cycle */
	struct ftsent **fts_array;	/* sort array */
E 9
I 9
typedef struct {
	struct _ftsent *fts_cur;	/* current node */
	struct _ftsent *fts_child;	/* linked list of children */
D 17
	struct _ftsent *fts_savelink;	/* saved link if node had a cycle */
E 17
	struct _ftsent **fts_array;	/* sort array */
E 9
I 3
D 12
	dev_t sdev;			/* starting device # */
E 12
I 12
D 19
	dev_t rdev;			/* starting device # */
E 19
I 19
	dev_t fts_dev;			/* starting device # */
E 19
E 12
E 3
	char *fts_path;			/* path for this descent */
D 4
	char *fts_wd;			/* starting directory */
E 4
I 4
D 9
	int fts_sd;			/* starting directory */
E 9
I 9
D 12
	int fts_sd;			/* fd for root */
E 12
I 12
D 16
	int fts_dfd;			/* fd for directories */
E 16
	int fts_rfd;			/* fd for root */
E 12
E 9
E 4
	int fts_pathlen;		/* sizeof(path) */
	int fts_nitems;			/* elements in the sort array */
	int (*fts_compar)();		/* compare function */
E 2
D 12
#define	FTS__STOP	0x001		/* private: unrecoverable error */
#define	FTS_LOGICAL	0x002		/* user: use stat(2) */
D 7
#define	FTS_MULTIPLE	0x004		/* user: multiple args */
#define	FTS_NOCHDIR	0x008		/* user: don't use chdir(2) */
#define	FTS_NOSTAT	0x010		/* user: don't require stat info */
#define	FTS_PHYSICAL	0x020		/* user: use lstat(2) */
#define	FTS_SEEDOT	0x040		/* user: return dot and dot-dot */
I 3
#define	FTS_XDEV	0x080		/* user: don't cross devices */
E 7
I 7
#define	FTS_NOCHDIR	0x004		/* user: don't use chdir(2) */
#define	FTS_NOSTAT	0x008		/* user: don't require stat info */
#define	FTS_PHYSICAL	0x010		/* user: use lstat(2) */
#define	FTS_SEEDOT	0x020		/* user: return dot and dot-dot */
#define	FTS_XDEV	0x040		/* user: don't cross devices */
E 12
I 12

D 21
#define	FTS_LOGICAL	0x001		/* logical walk */
#define	FTS_NOCHDIR	0x002		/* don't change directories */
#define	FTS_NOSTAT	0x004		/* don't get stat info */
#define	FTS_PHYSICAL	0x008		/* physical walk */
#define	FTS_SEEDOT	0x010		/* return dot and dot-dot */
#define	FTS_STOP	0x020		/* (private) unrecoverable error */
#define	FTS_XDEV	0x040		/* don't cross devices */
E 21
I 21
#define	FTS_COMFOLLOW	0x001		/* follow command line symlinks */
#define	FTS_LOGICAL	0x002		/* logical walk */
#define	FTS_NOCHDIR	0x004		/* don't change directories */
#define	FTS_NOSTAT	0x008		/* don't get stat info */
#define	FTS_PHYSICAL	0x010		/* physical walk */
#define	FTS_SEEDOT	0x020		/* return dot and dot-dot */
D 22
#define	FTS_STOP	0x040		/* (private) unrecoverable error */
#define	FTS_XDEV	0x080		/* don't cross devices */
E 21
E 12
E 7
E 3
D 2
	int options;			/* openfts() options */
E 2
I 2
	int fts_options;		/* openfts() options */
E 22
I 22
#define	FTS_XDEV	0x040		/* don't cross devices */
D 26
#define	FTS_OPTIONMASK	0x07f		/* valid user option mask */
E 26
I 26
#define	FTS_WHITEOUT	0x080		/* return whiteout information */
#define	FTS_OPTIONMASK	0x0ff		/* valid user option mask */
E 26

D 26
#define	FTS_NAMEONLY	0x080		/* (private) child names only */
#define	FTS_STOP	0x100		/* (private) unrecoverable error */
E 26
I 26
#define	FTS_NAMEONLY	0x100		/* (private) child names only */
#define	FTS_STOP	0x200		/* (private) unrecoverable error */
E 26
	int fts_options;		/* fts_open options, global flags */
E 22
E 2
} FTS;

D 9
typedef struct ftsent {
D 2
	struct ftsent *parent;		/* parent directory */
	struct ftsent *link;		/* next/cycle node */
E 2
I 2
	struct ftsent *fts_parent;	/* parent directory */
	struct ftsent *fts_link;	/* next/cycle node */
E 9
I 9
typedef struct _ftsent {
I 17
	struct _ftsent *fts_cycle;	/* cycle node */
E 17
	struct _ftsent *fts_parent;	/* parent directory */
D 17
	struct _ftsent *fts_link;	/* cycle or next file structure */
E 17
I 17
	struct _ftsent *fts_link;	/* next file in directory */
E 17
E 9
E 2
D 23
	union {
		long number;		/* local numeric value */
		void *pointer;		/* local address value */
D 2
	} local;
	char *accpath;			/* path from current directory */
	char *path;			/* path from starting directory */
	short pathlen;			/* strlen(path) */
	short namelen;			/* strlen(name) */
	short level;			/* depth (-1 to N) */
E 2
I 2
	} fts_local;
D 9
	char *fts_accpath;		/* path from current directory */
	char *fts_path;			/* path from starting directory */
	short fts_pathlen;		/* strlen(path) */
	short fts_namelen;		/* strlen(name) */
E 9
I 9
#define	fts_number	fts_local.number
#define	fts_pointer	fts_local.pointer
E 23
I 23
	long fts_number;	        /* local numeric value */
	void *fts_pointer;	        /* local address value */
E 23
	char *fts_accpath;		/* access path */
	char *fts_path;			/* root path */
I 12
D 18
	int fts_cderr;			/* chdir failed -- errno */
E 18
I 18
	int fts_errno;			/* errno for this node */
I 20
	int fts_symfd;			/* fd for symlink */
E 20
E 18
E 12
D 19
	short fts_pathlen;		/* strlen(fts_path) */
	short fts_namelen;		/* strlen(fts_name) */
E 19
I 19
	u_short fts_pathlen;		/* strlen(fts_path) */
	u_short fts_namelen;		/* strlen(fts_name) */
E 19
I 13

I 19
	ino_t fts_ino;			/* inode */
	dev_t fts_dev;			/* device */
	nlink_t fts_nlink;		/* link count */

E 19
#define	FTS_ROOTPARENTLEVEL	-1
#define	FTS_ROOTLEVEL		 0
E 13
E 9
	short fts_level;		/* depth (-1 to N) */
I 12

E 12
E 2
#define	FTS_D		 1		/* preorder directory */
#define	FTS_DC		 2		/* directory that causes cycles */
D 12
#define	FTS_DNR		 3		/* unreadable directory */
#define	FTS_DNX		 4		/* unsearchable directory */
E 12
I 12
#define	FTS_DEFAULT	 3		/* none of the above */
#define	FTS_DNR		 4		/* unreadable directory */
E 12
D 19
#define	FTS_DP		 5		/* postorder directory */
#define	FTS_ERR		 6		/* error; errno is set */
#define	FTS_F		 7		/* regular file */
I 18
#define	FTS_INIT	 8		/* initialized only */
E 18
D 12
#define	FTS_NS		 8		/* no stat(2) information */
#define	FTS_SL		 9		/* symbolic link */
#define	FTS_SLNONE	10		/* symbolic link without target */
#define	FTS_DEFAULT	11		/* none of the above */
D 2
	u_short	info;			/* file information */
E 2
I 2
D 9
	u_short fts_info;		/* file information */
E 9
I 9
	u_short fts_info;		/* flags for FTSENT structure */
#define	FTS__NOINSTR	 0		/* private: no instructions */
E 9
E 2
#define	FTS_AGAIN	 1		/* user: read node again */
#define	FTS_SKIP	 2		/* user: discard node */
#define	FTS_FOLLOW	 3		/* user: follow symbolic link */
D 2
	short instr;			/* setfts() instructions */
	struct stat statb;		/* stat(2) information */
	char name[1];			/* file name */
E 2
I 2
D 9
	short fts_instr;		/* setfts() instructions */
E 9
I 9
	short fts_instr;		/* private: fts_set() instructions */
E 12
I 12
#define	FTS_NS		 8		/* stat(2) failed */
#define	FTS_NSOK	 9		/* no stat(2) requested */
#define	FTS_SL		10		/* symbolic link */
#define	FTS_SLNONE	11		/* symbolic link without target */
E 19
I 19
#define	FTS_DOT		 5		/* dot or dot-dot */
#define	FTS_DP		 6		/* postorder directory */
#define	FTS_ERR		 7		/* error; errno is set */
#define	FTS_F		 8		/* regular file */
#define	FTS_INIT	 9		/* initialized only */
#define	FTS_NS		10		/* stat(2) failed */
#define	FTS_NSOK	11		/* no stat(2) requested */
#define	FTS_SL		12		/* symbolic link */
#define	FTS_SLNONE	13		/* symbolic link without target */
I 26
#define	FTS_W		14		/* whiteout object */
E 26
E 19
	u_short fts_info;		/* user flags for FTSENT structure */
I 20

#define	FTS_DONTCHDIR	 0x01		/* don't chdir .. to the parent */
D 24
#define	FTS_SYMFOLLOW	 0x01		/* followed a symlink to get here */
E 24
I 24
#define	FTS_SYMFOLLOW	 0x02		/* followed a symlink to get here */
I 26
#define	FTS_ISW		 0x04		/* this is a whiteout object */
D 27
#define	FTS_ISWD	 0x08		/* this is a whiteout dir object */
E 27
E 26
E 24
	u_short fts_flags;		/* private flags for FTSENT structure */
E 20

#define	FTS_AGAIN	 1		/* read node again */
#define	FTS_FOLLOW	 2		/* follow symbolic link */
#define	FTS_NOINSTR	 3		/* no instructions */
#define	FTS_SKIP	 4		/* discard node */
	u_short fts_instr;		/* fts_set() instructions */

E 12
E 9
D 19
	struct stat fts_statb;		/* stat(2) information */
E 19
I 19
	struct stat *fts_statp;		/* stat(2) information */
E 19
	char fts_name[1];		/* file name */
E 2
} FTSENT;

D 2
FTS *ftsopen();
FTSENT *ftschildren(), *ftsread();
int ftsclose(), ftsset();
E 2
I 2
D 5
#ifdef __STDC__
E 5
I 5
D 10
#if __STDC__ || c_plusplus
E 5
D 8
extern FTS *ftsopen(const char **, int, int (*)(const FTSENT *, const FTSENT *);
E 8
I 8
D 9
extern FTS *ftsopen(const char **, int, int (*)(const FTSENT *, const FTSENT *));
E 8
extern FTSENT *ftsread(FTS *);
extern FTSENT *ftschildren(FTS *);
extern int ftsset(FTS *, FTSENT *, int);
extern int ftsclose(FTS *);
E 9
I 9
extern FTS *fts_open(const char **, int, int (*)(const FTSENT *, const FTSENT *));
extern FTSENT *fts_read(FTS *);
extern FTSENT *fts_children(FTS *);
extern int fts_set(FTS *, FTSENT *, int);
extern int fts_close(FTS *);
E 9
#else
D 9
extern FTS *ftsopen();
extern FTSENT *ftschildren(), *ftsread();
extern int ftsclose(), ftsset();
E 9
I 9
extern FTS *fts_open();
extern FTSENT *fts_children(), *fts_read();
extern int fts_close(), fts_set();
E 9
#endif
E 10
I 10
#include <sys/cdefs.h>

__BEGIN_DECLS
D 22
FTSENT	*fts_children __P((FTS *));
E 22
I 22
FTSENT	*fts_children __P((FTS *, int));
E 22
int	 fts_close __P((FTS *));
D 15
FTS	*fts_open
D 11
	    __P((const char **, int, int (*)(const FTSENT *, const FTSENT *)));
E 11
I 11
	    __P((char * const *, int, int (*)(const FTSENT *, const FTSENT *)));
E 15
I 15
FTS	*fts_open __P((char * const *, int,
	    int (*)(const FTSENT **, const FTSENT **)));
E 15
E 11
FTSENT	*fts_read __P((FTS *));
int	 fts_set __P((FTS *, FTSENT *, int));
__END_DECLS
I 14

#endif /* !_FTS_H_ */
E 14
E 10
E 2
E 1
