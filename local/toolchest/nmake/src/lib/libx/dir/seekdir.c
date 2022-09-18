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
 * seekdir
 *
 * seek on directory stream
 */

#include <sys/types.h>
#include <directory.h>

#if BSD
static int symbol;
#else
#undef	direct

extern long	lseek();

void
seekdir(dirp, loc)
register DIR	*dirp;
long		loc;
{
	long	base;		/* file location of block */
	long	offset; 	/* offset within block */

	if (telldir(dirp) != loc)
	{
		offset = loc % DIRBLKSIZ;
		base = loc - offset;
		(void)lseek(dirp->dd_fd, base, 0);
		dirp->dd_loc = dirp->dd_size = 0;

		/*
		 * skip some entries
		 */

		while (dirp->dd_loc < offset)
			if (!readdir(dirp))
				break; 	/* "can't happen" */
	}
}
#endif
