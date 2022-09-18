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
 * opendir, closedir
 *
 * open|close directory stream
 */

#include <sys/types.h>
#include <directory.h>

#if BSD

static int symbol;

#else

static char	stamp[] = "@(#)directory (AT&T Bell Laboratories) 03/06/85a";

#undef	direct
#include <sys/stat.h>

static DIR	*freedirp;		/* always keep one dirp */

extern char	*malloc();
extern void	free();
extern int	open(), close(), fstat();

DIR*
opendir(filename)
char	*filename;
{
	register DIR	*dirp;		/* -> malloc'ed storage */
	register int	fd;		/* file descriptor for read */
	struct stat	sbuf;		/* result of fstat() */

	if ((fd = open(filename, 0)) < 0) return((DIR*)0);
	if (fstat(fd, &sbuf) < 0 ||
	   (sbuf.st_mode & S_IFMT) != S_IFDIR ||
	   !(dirp = freedirp ? freedirp : (DIR*)malloc(sizeof(DIR))))
	{
		(void)close(fd);
		if (dirp)
		{
			if (!freedirp) freedirp = dirp;
			else free((char*)dirp);
		}
		return((DIR*)0);
	}
	freedirp = (DIR*)0;
	dirp->dd_fd = fd;
	dirp->dd_loc = dirp->dd_size = 0;	/* refill needed */
	return(dirp);
}

void
closedir(dirp)
register DIR	*dirp;
{
	if (dirp)
	{
		(void)close(dirp->dd_fd);
		if (!freedirp) freedirp = dirp;
		else free((char*)dirp);
	}
}

#endif
