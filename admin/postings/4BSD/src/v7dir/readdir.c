/*
 * Copyright (c) 1987 Regents of the University of California.
 * This file may be freely redistributed provided that this
 * notice remains attached.
 */

#include <sys/param.h>
#include <ndir.h>

/*
 * read a V7 directory entry and present it as a BSD4.X entry.
 */

/*
 * get next entry in a directory.
 */
struct direct *
readdir(dirp)
	register DIR *dirp;
{
	register struct v7direct *dp;

	for (;;) {
		if (dirp->dd_loc == 0) {
			dirp->dd_size = read(dirp->dd_fd, dirp->dd_buf, 
			    DIRBLKSIZ);
			if (dirp->dd_size <= 0)
				return NULL;
		}
		if (dirp->dd_loc >= dirp->dd_size) {
			dirp->dd_loc = 0;
			continue;
		}
		dp = (struct v7direct *)(dirp->dd_buf + dirp->dd_loc);
		dirp->dd_loc += sizeof(struct v7direct);
		if (dp->d_ino == 0)
			continue;
		/*
		 * format V7 directory structure into BSD4.X
		 */
		dirp->dd_cur.d_ino = dp->d_ino;
		bcopy(dp->d_name, dirp->dd_cur.d_name, MAXNAMLEN);
						/* insure null termination */
		dirp->dd_cur.d_name[MAXNAMLEN] = '\0';
		dirp->dd_cur.d_namlen = strlen(dirp->dd_cur.d_name);
		dirp->dd_cur.d_reclen = DIRBLKSIZ;
		return (&dirp->dd_cur);
	}
}
