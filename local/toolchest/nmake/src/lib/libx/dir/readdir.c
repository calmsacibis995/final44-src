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
 * readdir
 *
 * read from directory stream
 *
 * NOTE: directory entries must fit within DIRBLKSIZ boundaries
 */

#include <sys/types.h>
#include <directory.h>

#if BSD
static int symbol;
#else
#undef	direct

extern int	read();
extern int	strlen();
extern char	*strncpy();

struct DIRECT*
readdir(dirp)
register DIR	*dirp;
{
	register struct DIRECT	*up;	/* user */
	register struct direct	*dp;	/* system */

	up = &dirp->dd_entry;
	for (;;)
	{
		if (dirp->dd_loc >= dirp->dd_size)
			dirp->dd_loc = dirp->dd_size = 0;
		if (!dirp->dd_size &&
		   (dirp->dd_size = read(dirp->dd_fd, dirp->dd_buf, DIRBLKSIZ)) <= 0)
			return((struct DIRECT*)0);
		dp = (struct direct*)&dirp->dd_buf[dirp->dd_loc];
		dirp->dd_loc += sizeof(struct direct);
		if (dp->d_ino)
		{
			up->d_ino = dp->d_ino;
			(void)strncpy(up->d_name, dp->d_name, MAXNAMLEN);
			up->d_name[MAXNAMLEN] = '\0';
			up->d_namlen = strlen(up->d_name);
			up->d_reclen = sizeof(struct DIRECT);
			return(up);
		}
	}
}
#endif
