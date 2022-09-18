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
 * telldir
 *
 * get offset of directory stream pointer
 */

#include <sys/types.h>
#include <directory.h>

#if BSD
static int symbol;
#else
#undef	direct

extern long	lseek();

long
telldir(dirp)
DIR	*dirp;
{
	return(lseek(dirp->dd_fd, 0L, 1) - (long)dirp->dd_size + (long)dirp->dd_loc);
}
#endif
