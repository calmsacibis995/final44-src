h35074
s 00001/00002/00251
d D 8.4 95/05/09 15:45:11 mckusick 30 29
c check and act on the clean flag
e
s 00071/00007/00182
d D 8.3 95/04/27 11:33:06 mckusick 29 28
c add function prototypes
e
s 00019/00019/00170
d D 8.2 95/03/21 00:10:50 mckusick 28 27
c daddr_t => ufs_daddr_t
e
s 00002/00002/00187
d D 8.1 93/06/05 10:56:18 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00188
d D 5.20 93/06/04 11:42:13 bostic 26 25
c rename devname to cdevname, devname(3) now in the C library
e
s 00005/00001/00184
d D 5.19 92/06/26 10:12:58 mckusick 25 24
c add support for converting to and checking new inode format filesystems
e
s 00001/00001/00184
d D 5.18 92/03/16 20:41:28 mckusick 24 23
c file sizes are now 64-bits
e
s 00001/00001/00184
d D 5.17 90/07/27 14:44:10 mckusick 23 22
c add new fixstate to avoid asking questions
e
s 00001/00001/00184
d D 5.16 90/07/20 16:51:42 mckusick 22 21
c lint (from Torek)
e
s 00001/00011/00184
d D 5.15 90/06/01 16:16:28 bostic 21 20
c new copyright notice
e
s 00002/00000/00193
d D 5.14 90/03/27 18:06:07 mckusick 20 19
c add inode and directory buffer pointers
e
s 00000/00004/00193
d D 5.13 90/03/27 17:39:40 mckusick 19 18
c get rid of unused variables
e
s 00019/00004/00178
d D 5.12 90/02/07 00:17:01 mckusick 18 17
c add pass1 buffer constant; 
c add inoinfo structure to describe essential directory contents
e
s 00001/00000/00181
d D 5.11 90/02/01 23:36:23 mckusick 17 16
c save block pointers of directories as they are encountered in pass1
c so that they do not have to be reread when descending in pass2
e
s 00014/00003/00167
d D 5.10 90/02/01 17:17:41 mckusick 16 15
c convert to BSD only copyright
e
s 00036/00053/00134
d D 5.9 90/02/01 16:18:00 mckusick 15 14
c lint and other aesthetic cleanups
e
s 00001/00000/00186
d D 5.8 89/02/17 17:02:37 mckusick 14 13
c add -m flag to override default creation mode for lost+found
e
s 00025/00021/00161
d D 5.7 88/05/07 01:04:10 mckusick 13 12
c expand from three static buffer to a dynamic buffer pool;
c initial sizing of the buffer pool is 128K (For 8K fs == 16 buffers)
e
s 00001/00000/00181
d D 5.6 88/05/01 23:36:54 mckusick 12 11
c add -c flag (convert dynamic cylinder group format back to static format)
e
s 00001/00000/00180
d D 5.5 87/04/07 19:49:18 karels 11 10
c fix alternate superblock location again; don't offer to rewrite
c standard superblock if we haven't found a good one yet; standardize units
c for -b (sectors! as before); kernel may change fs_dbsize
e
s 00001/00000/00179
d D 5.4 87/03/11 20:06:24 karels 10 9
c use physical sector size for partial buffer reads;
c -n implies "yes" answer for "CONTINUE?"
e
s 00001/00000/00178
d D 5.3 87/02/18 18:14:41 mckusick 9 8
c intuit the appropriate DEV_BSIZE from fsbtodb macro
e
s 00001/00000/00177
d D 5.2 87/01/07 19:26:41 mckusick 8 7
c be more persistent in trying to read directories; 
c add FOUND return status for routines called from dirscan
e
s 00007/00001/00170
d D 5.1 85/06/05 08:59:36 dist 7 6
c Add copyright
e
s 00027/00004/00144
d D 3.6 85/06/02 16:46:58 mckusick 6 5
c dynamically allocate zero link count table
e
s 00009/00005/00139
d D 3.5 85/05/31 20:08:12 mckusick 5 4
c dynamically allocate the duplicate block table
e
s 00001/00000/00143
d D 3.4 85/05/31 00:19:24 mckusick 4 3
c check for improper directory offsets; recover gracefully from read errors
e
s 00006/00024/00137
d D 3.3 85/02/08 19:15:03 mckusick 3 2
c merge passes 5 and 6 into a single pass
e
s 00017/00016/00144
d D 3.2 85/02/07 17:51:32 mckusick 2 1
c code reorganization and cleanup
e
s 00160/00000/00000
d D 3.1 84/03/31 21:03:41 mckusick 1 0
c date and time created 84/03/31 21:03:41 by mckusick
e
u
U
t
T
I 1
D 7
/* %W% (Berkeley) %G% */
E 7
I 7
/*
D 16
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 16
I 16
D 27
 * Copyright (c) 1980, 1986 The Regents of the University of California.
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
 *
D 21
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
E 21
I 21
 * %sccs.include.redist.c%
E 21
E 16
 *
 *	%W% (Berkeley) %G%
 */
E 7

I 29
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

E 29
D 3
/* RECONSTRUCT ONLY BAD CG IN PASS 6 */

E 3
D 13
#define	MAXDUP		10	/* limit on dup blks (per inode) */
#define	MAXBAD		10	/* limit on bad blks (per inode) */
E 13
I 13
D 18
#define	MAXDUP		10	 /* limit on dup blks (per inode) */
#define	MAXBAD		10	 /* limit on bad blks (per inode) */
#define MAXBUFSPACE	128*1024 /* maximum space to allocate to buffers */
E 18
I 18
#define	MAXDUP		10	/* limit on dup blks (per inode) */
#define	MAXBAD		10	/* limit on bad blks (per inode) */
#define	MAXBUFSPACE	40*1024	/* maximum space to allocate to buffers */
#define	INOBUFSIZE	56*1024	/* size of buffer to read inodes in pass1 */
E 18
E 13
D 5
#define	DUPTBLSIZE	100	/* num of dup blocks to remember */
E 5
D 6
#define	MAXLNCNT	500	/* num zero link cnts to remember */
E 6

D 15
typedef	int	(*SIG_TYP)();

E 15
#ifndef BUFSIZ
#define BUFSIZ 1024
#endif

D 2
#define	MAXNINDIR	(MAXBSIZE / sizeof (daddr_t))
#define	MAXINOPB	(MAXBSIZE / sizeof (struct dinode))
#define	SPERB		(MAXBSIZE / sizeof(short))

E 2
D 3
#define	USTATE	0		/* inode not allocated */
#define	FSTATE	01		/* inode is file */
#define	DSTATE	02		/* inode is directory */
#define	CLEAR	03		/* inode is to be cleared */
E 3
I 3
#define	USTATE	01		/* inode not allocated */
#define	FSTATE	02		/* inode is file */
#define	DSTATE	03		/* inode is directory */
#define	DFOUND	04		/* directory found during descent */
#define	DCLEAR	05		/* directory is to be cleared */
#define	FCLEAR	06		/* file is to be cleared */
E 3

D 15
typedef struct dinode	DINODE;
typedef struct direct	DIRECT;

D 2
#define	ALLOC	((dp->di_mode & IFMT) != 0)
#define	DIRCT	((dp->di_mode & IFMT) == IFDIR)
#define	SPECIAL	((dp->di_mode & IFMT) == IFBLK || (dp->di_mode & IFMT) == IFCHR)
E 2
I 2
#define	ALLOC(dip)	(((dip)->di_mode & IFMT) != 0)
#define	DIRCT(dip)	(((dip)->di_mode & IFMT) == IFDIR)
#define	SPECIAL(dip) \
	(((dip)->di_mode & IFMT) == IFBLK || ((dip)->di_mode & IFMT) == IFCHR)
E 2

E 15
I 2
D 13
#define	MAXNINDIR	(MAXBSIZE / sizeof (daddr_t))
#define	MAXINOPB	(MAXBSIZE / sizeof (struct dinode))
#define	SPERB		(MAXBSIZE / sizeof(short))

E 13
I 13
/*
 * buffer cache structure.
 */
E 13
E 2
struct bufarea {
D 13
	struct bufarea	*b_next;		/* must be first */
E 13
I 13
D 28
	struct bufarea	*b_next;		/* free list queue */
	struct bufarea	*b_prev;		/* free list queue */
E 13
	daddr_t	b_bno;
	int	b_size;
I 4
	int	b_errs;
I 13
	int	b_flags;
E 28
I 28
	struct bufarea *b_next;		/* free list queue */
	struct bufarea *b_prev;		/* free list queue */
	ufs_daddr_t b_bno;
	int b_size;
	int b_errs;
	int b_flags;
E 28
E 13
E 4
	union {
D 13
		char	b_buf[MAXBSIZE];	/* buffer space */
		short	b_lnks[SPERB];		/* link counts */
		daddr_t	b_indir[MAXNINDIR];	/* indirect block */
		struct	fs b_fs;		/* super block */
		struct	cg b_cg;		/* cylinder group */
		struct dinode b_dinode[MAXINOPB]; /* inode block */
E 13
I 13
D 28
		char	*b_buf;			/* buffer space */
		daddr_t	*b_indir;		/* indirect block */
		struct	fs *b_fs;		/* super block */
		struct	cg *b_cg;		/* cylinder group */
D 15
		struct dinode *b_dinode;	/* inode block */
E 15
I 15
		struct	dinode *b_dinode;	/* inode block */
E 28
I 28
		char *b_buf;			/* buffer space */
		ufs_daddr_t *b_indir;		/* indirect block */
		struct fs *b_fs;		/* super block */
		struct cg *b_cg;		/* cylinder group */
		struct dinode *b_dinode;	/* inode block */
E 28
E 15
E 13
	} b_un;
D 28
	char	b_dirty;
E 28
I 28
	char b_dirty;
E 28
};

I 13
#define	B_INUSE 1
E 13
D 15
typedef struct bufarea BUFAREA;
E 15

D 13
BUFAREA	inoblk;			/* inode blocks */
BUFAREA	fileblk;		/* other blks in filesys */
E 13
I 13
#define	MINBUFS		5	/* minimum number of buffers required */
D 15
BUFAREA	bufhead;		/* head of list of other blks in filesys */
E 13
BUFAREA	sblk;			/* file system superblock */
BUFAREA	cgblk;			/* cylinder group blocks */
I 13
BUFAREA	*getdatablk();
E 15
I 15
struct bufarea bufhead;		/* head of list of other blks in filesys */
struct bufarea sblk;		/* file system superblock */
struct bufarea cgblk;		/* cylinder group blocks */
I 20
struct bufarea *pdirbp;		/* current directory contents */
struct bufarea *pbp;		/* current inode block */
E 20
D 30
struct bufarea *getdatablk();
E 30
E 15
E 13

D 13
#define	initbarea(x)	(x)->b_dirty = 0;(x)->b_bno = (daddr_t)-1
E 13
D 15
#define	dirty(x)	(x)->b_dirty = 1
D 13
#define	inodirty()	inoblk.b_dirty = 1
E 13
I 13
#define	initbarea(x) \
	(x)->b_dirty = 0; \
	(x)->b_bno = (daddr_t)-1; \
	(x)->b_flags = 0;
E 15
I 15
#define	dirty(bp)	(bp)->b_dirty = 1
#define	initbarea(bp) \
	(bp)->b_dirty = 0; \
D 28
	(bp)->b_bno = (daddr_t)-1; \
E 28
I 28
	(bp)->b_bno = (ufs_daddr_t)-1; \
E 28
	(bp)->b_flags = 0;
E 15

E 13
#define	sbdirty()	sblk.b_dirty = 1
#define	cgdirty()	cgblk.b_dirty = 1
D 13

#define	dirblk		fileblk.b_un
#define	sblock		sblk.b_un.b_fs
#define	cgrp		cgblk.b_un.b_cg
E 13
I 13
#define	sblock		(*sblk.b_un.b_fs)
#define	cgrp		(*cgblk.b_un.b_cg)
E 13

D 15
struct filecntl {
	int	rfdes;
	int	wfdes;
	int	mod;
} dfile;			/* file descriptors for filesys */

E 15
I 2
D 23
enum fixstate {DONTKNOW, NOFIX, FIX};
E 23
I 23
enum fixstate {DONTKNOW, NOFIX, FIX, IGNORE};
E 23

E 2
struct inodesc {
D 2
	char id_type;		/* type of descriptor, DATA or ADDR */
E 2
I 2
	enum fixstate id_fix;	/* policy on fixing errors */
E 2
	int (*id_func)();	/* function to be applied to blocks of inode */
	ino_t id_number;	/* inode number described */
	ino_t id_parent;	/* for DATA nodes, their parent */
D 28
	daddr_t id_blkno;	/* current block number being examined */
E 28
I 28
	ufs_daddr_t id_blkno;	/* current block number being examined */
E 28
	int id_numfrags;	/* number of frags contained in block */
D 24
	long id_filesize;	/* for DATA nodes, the size of the directory */
E 24
I 24
	quad_t id_filesize;	/* for DATA nodes, the size of the directory */
E 24
	int id_loc;		/* for DATA nodes, current location in dir */
	int id_entryno;		/* for DATA nodes, current entry number */
D 2
	DIRECT *id_dirp;	/* for data nodes, ptr to current entry */
	enum {DONTKNOW, NOFIX, FIX} id_fix; /* policy on fixing errors */
E 2
I 2
D 15
	DIRECT *id_dirp;	/* for DATA nodes, ptr to current entry */
E 15
I 15
	struct direct *id_dirp;	/* for DATA nodes, ptr to current entry */
E 15
	char *id_name;		/* for DATA nodes, name to find or enter */
	char id_type;		/* type of descriptor, DATA or ADDR */
E 2
};
/* file types */
#define	DATA	1
#define	ADDR	2

D 5

daddr_t	duplist[DUPTBLSIZE];	/* dup block table */
daddr_t	*enddup;		/* next entry in dup table */
daddr_t	*muldup;		/* multiple dups part of table */
E 5
I 5
/*
D 6
 * Linked list of duplicate blocks
E 6
I 6
 * Linked list of duplicate blocks.
 * 
 * The list is composed of two parts. The first part of the
 * list (from duplist through the node pointed to by muldup)
 * contains a single copy of each duplicate block that has been 
 * found. The second part of the list (from muldup to the end)
 * contains duplicate blocks that have been found more than once.
 * To check if a block has been found as a duplicate it is only
 * necessary to search from duplist through muldup. To find the 
 * total number of times that a block has been found as a duplicate
 * the entire list must be searched for occurences of the block
 * in question. The following diagram shows a sample list where
 * w (found twice), x (found once), y (found three times), and z
 * (found once) are duplicate block numbers:
 *
 *    w -> y -> x -> z -> y -> w -> y
 *    ^		     ^
 *    |		     |
 * duplist	  muldup
E 6
 */
struct dups {
	struct dups *next;
D 28
	daddr_t dup;
E 28
I 28
	ufs_daddr_t dup;
E 28
};
struct dups *duplist;		/* head of dup list */
struct dups *muldup;		/* end of unique duplicate dup block numbers */
E 5

D 6
ino_t	badlncnt[MAXLNCNT];	/* table of inos with zero link cnts */
ino_t	*badlnp;		/* next entry in table */
E 6
I 6
/*
 * Linked list of inodes with zero link counts.
 */
struct zlncnt {
	struct zlncnt *next;
	ino_t zlncnt;
};
struct zlncnt *zlnhead;		/* head of zero link count list */
E 6

I 18
/*
 * Inode cache data structures.
 */
struct inoinfo {
	struct	inoinfo *i_nexthash;	/* next entry in hash chain */
	ino_t	i_number;		/* inode number of this entry */
	ino_t	i_parent;		/* inode number of parent */
	ino_t	i_dotdot;		/* inode number of `..' */
	size_t	i_isize;		/* size of inode */
	u_int	i_numblks;		/* size of block array in bytes */
D 28
	daddr_t	i_blks[1];		/* actually longer */
E 28
I 28
	ufs_daddr_t i_blks[1];		/* actually longer */
E 28
} **inphead, **inpsort;
long numdirs, listmax, inplast;

E 18
D 15
char	rawflg;
char	*devname;
E 15
I 15
D 26
char	*devname;		/* name of device being checked */
E 26
I 26
char	*cdevname;		/* name of device being checked */
E 26
E 15
I 9
long	dev_bsize;		/* computed value of DEV_BSIZE */
I 10
long	secsize;		/* actual disk sector size */
E 10
E 9
char	nflag;			/* assume a no response */
char	yflag;			/* assume a yes response */
int	bflag;			/* location of alternate super block */
int	debug;			/* output debugging info */
I 12
D 25
int	cvtflag;		/* convert to old file system format */
E 25
I 25
int	cvtlevel;		/* convert to newer file system format */
int	doinglevel1;		/* converting to new cylinder group format */
int	doinglevel2;		/* converting to new inode format */
int	newinofmt;		/* filesystem has new inode format */
E 25
E 12
char	preen;			/* just fix normal inconsistencies */
D 2
char	rplyflag;		/* any questions asked? */
E 2
char	hotroot;		/* checking root device */
I 11
char	havesb;			/* superblock has been read */
I 15
int	fsmodified;		/* 1 => write done to file system */
int	fsreadfd;		/* file descriptor for reading file system */
int	fswritefd;		/* file descriptor for writing file system */
E 15
E 11
D 3
char	fixcg;			/* corrupted free list bit maps */
E 3

I 15
D 28
daddr_t	maxfsblock;		/* number of blocks in the file system */
E 28
I 28
ufs_daddr_t maxfsblock;		/* number of blocks in the file system */
E 28
E 15
char	*blockmap;		/* ptr to primary blk allocation map */
I 15
ino_t	maxino;			/* number of inodes in file system */
ino_t	lastino;		/* last inode in use */
E 15
D 3
char	*freemap;		/* ptr to secondary blk allocation map */
E 3
char	*statemap;		/* ptr to inode state table */
I 25
D 29
char	*typemap;		/* ptr to inode type table */
E 29
I 29
u_char	*typemap;		/* ptr to inode type table */
E 29
E 25
short	*lncntp;		/* ptr to link count table */

D 2
char	*srchname;		/* name being searched for in dir */
E 2
D 19
char	pathname[BUFSIZ];	/* current pathname */
D 15
char	*pathp;			/* pointer to pathname position */
char	*endpathname;
E 15
I 15
char	*pathp;			/* ptr to current position in pathname */
char	*endpathname;		/* ptr to current end of pathname */
E 15

E 19
D 2
char	*lfname;

E 2
I 2
D 15
daddr_t	fmax;			/* number of blocks in the volume */
E 2
ino_t	imax;			/* number of inodes */
ino_t	lastino;		/* hiwater mark of inodes */
E 15
D 2
ino_t	lfdir;			/* lost & found directory */
E 2
I 2
ino_t	lfdir;			/* lost & found directory inode number */
char	*lfname;		/* lost & found directory name */
I 14
int	lfmode;			/* lost & found directory creation mode */
E 14
E 2

D 15
off_t	maxblk;			/* largest logical blk in file */
off_t	bmapsz;			/* num chars in blockmap */
E 15
I 15
D 28
daddr_t	n_blks;			/* number of blocks in use */
daddr_t	n_files;		/* number of files in use */
E 28
I 28
ufs_daddr_t n_blks;		/* number of blocks in use */
ufs_daddr_t n_files;		/* number of files in use */
E 28
E 15

D 3
daddr_t	n_ffree;		/* number of small free blocks */
daddr_t	n_bfree;		/* number of large free blocks */
E 3
D 15
daddr_t	n_blks;			/* number of blocks used */
daddr_t	n_files;		/* number of files seen */
D 3
daddr_t	n_index;
daddr_t	n_bad;
E 3
D 2
daddr_t	fmax;			/* number of blocks in the volume */
E 2

D 3
daddr_t	badblk;
daddr_t	dupblk;

int	inosumbad;
int	offsumbad;
int	frsumbad;
int	sbsumbad;

E 3
#define	zapino(x)	(*(x) = zino)
E 15
I 15
#define	clearinode(dp)	(*(dp) = zino)
E 15
struct	dinode zino;

D 15
#define	setbmap(x)	setbit(blockmap, x)
#define	getbmap(x)	isset(blockmap, x)
#define	clrbmap(x)	clrbit(blockmap, x)
E 15
I 15
#define	setbmap(blkno)	setbit(blockmap, blkno)
#define	testbmap(blkno)	isset(blockmap, blkno)
#define	clrbmap(blkno)	clrbit(blockmap, blkno)
E 15
D 3

#define	setfmap(x)	setbit(freemap, x)
#define	getfmap(x)	isset(freemap, x)
#define	clrfmap(x)	clrbit(freemap, x)
E 3

I 8
D 15
#define	FOUND	020
E 8
#define	ALTERED	010
#define	KEEPON	04
#define	SKIP	02
#define	STOP	01
E 15
I 15
#define	STOP	0x01
#define	SKIP	0x02
#define	KEEPON	0x04
#define	ALTERED	0x08
#define	FOUND	0x10
E 15

D 15
time_t	time();
DINODE	*ginode();
BUFAREA	*getblk();
int	findino();
E 15
I 15
D 29
time_t time();
struct dinode *ginode();
I 17
D 18
struct dinode *getcacheino();
E 18
I 18
struct inoinfo *getinoinfo();
E 18
E 17
D 22
struct bufarea *getblk();
E 22
I 22
void getblk();
E 22
ino_t allocino();
int findino();
E 29
I 29
#define	EEXIT	8		/* Standard error exit. */

struct fstab;

void		adjust __P((struct inodesc *, int lcnt));
ufs_daddr_t	allocblk __P((long frags));
ino_t		allocdir __P((ino_t parent, ino_t request, int mode));
ino_t		allocino __P((ino_t request, int type));
void		blkerror __P((ino_t ino, char *type, ufs_daddr_t blk));
char	       *blockcheck __P((char *name));
int		bread __P((int fd, char *buf, ufs_daddr_t blk, long size));
void		bufinit __P((void));
void		bwrite __P((int fd, char *buf, ufs_daddr_t blk, long size));
void		cacheino __P((struct dinode *dp, ino_t inumber));
void		catch __P((int));
void		catchquit __P((int));
int		changeino __P((ino_t dir, char *name, ino_t newnum));
int		checkfstab __P((int preen, int maxrun,
			int (*docheck)(struct fstab *),
			int (*chkit)(char *, char *, long, int)));
int		chkrange __P((ufs_daddr_t blk, int cnt));
D 30
void		ckfini __P((void));
E 30
I 30
void		ckfini __P((int markclean));
E 30
int		ckinode __P((struct dinode *dp, struct inodesc *));
void		clri __P((struct inodesc *, char *type, int flag));
void		direrror __P((ino_t ino, char *errmesg));
int		dirscan __P((struct inodesc *));
int		dofix __P((struct inodesc *, char *msg));
void		ffs_clrblock __P((struct fs *, u_char *, ufs_daddr_t));
void		ffs_fragacct __P((struct fs *, int, int32_t [], int));
int		ffs_isblock __P((struct fs *, u_char *, ufs_daddr_t));
void		ffs_setblock __P((struct fs *, u_char *, ufs_daddr_t));
void		fileerror __P((ino_t cwd, ino_t ino, char *errmesg));
int		findino __P((struct inodesc *));
int		findname __P((struct inodesc *));
void		flush __P((int fd, struct bufarea *bp));
void		freeblk __P((ufs_daddr_t blkno, long frags));
void		freeino __P((ino_t ino));
void		freeinodebuf __P((void));
int		ftypeok __P((struct dinode *dp));
void		getblk __P((struct bufarea *bp, ufs_daddr_t blk, long size));
struct bufarea *getdatablk __P((ufs_daddr_t blkno, long size));
struct inoinfo *getinoinfo __P((ino_t inumber));
struct dinode  *getnextinode __P((ino_t inumber));
void		getpathname __P((char *namebuf, ino_t curdir, ino_t ino));
struct dinode  *ginode __P((ino_t inumber));
void		inocleanup __P((void));
void		inodirty __P((void));
int		linkup __P((ino_t orphan, ino_t parentdir));
int		makeentry __P((ino_t parent, ino_t ino, char *name));
void		panic __P((const char *fmt, ...));
void		pass1 __P((void));
void		pass1b __P((void));
int		pass1check __P((struct inodesc *));
void		pass2 __P((void));
void		pass3 __P((void));
void		pass4 __P((void));
int		pass4check __P((struct inodesc *));
void		pass5 __P((void));
void		pfatal __P((const char *fmt, ...));
void		pinode __P((ino_t ino));
void		propagate __P((void));
void		pwarn __P((const char *fmt, ...));
int		reply __P((char *question));
void		resetinodebuf __P((void));
int		setup __P((char *dev));
void		voidquit __P((int));
E 29
E 15
E 1
