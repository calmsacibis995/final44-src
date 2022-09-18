/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*
 * directory stream access definitions
 *
 * BSD and ATT handle directories differently
 * the following determines the correct struct's
 *
 * NB: the preprocessor symbol DIRECT is a magic cookie
 */

#include <sys/dir.h>

#ifdef MAXNAMLEN

#ifndef BSD
#define BSD	1
#endif

#else

#define DIRBLKSIZ	(sizeof(sys_direct)*32) /* size of directory block */
#define	MAXNAMLEN	DIRSIZ		/* maximum filename length */

typedef struct direct sys_direct;	/* system directory entry */

#undef	direct
#define direct		DIRECT

struct direct				/* data from readdir() */
{
	long		d_ino;		/* inode number of entry */
	unsigned short	d_reclen;	/* length of this record */
	unsigned short	d_namlen;	/* length of string in d_name */
	char		d_name[MAXNAMLEN+1];	/* name of file */
};

typedef struct
{
	int		dd_fd;		/* file descriptor */
	int		dd_loc;		/* offset in block */
	int		dd_size;	/* amount of valid data */
	struct direct	dd_entry;	/* current system directory entry */
	char		dd_buf[DIRBLKSIZ]; /* directory block */
} DIR;					/* stream data from opendir() */

extern DIR		*opendir();
extern struct direct	*readdir();
extern long		telldir();
extern void		seekdir();
extern void		closedir();

#define rewinddir(dirp)	seekdir(dirp, 0L)
#ifndef DIRSIZ
#define DIRSIZ	14
#endif
#endif
