h26091
s 00000/00000/00048
d D 8.1 93/06/06 22:11:49 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00048/00000/00000
d D 5.1 91/04/24 17:37:42 bostic 1 0
c date and time created 91/04/24 17:37:42 by bostic
e
u
U
t
T
I 1
static char sccsid[] = "@(#)readdir.c 4.3 8/8/82";

#include <sys/types.h>
#include <ndir.h>

/*
 * read an old stlye directory entry and present it as a new one
 */
#define	ODIRSIZ	14

struct	olddirect {
	ino_t	od_ino;
	char	od_name[ODIRSIZ];
};

/*
 * get next entry in a directory.
 */
struct direct *
readdir(dirp)
	register DIR *dirp;
{
	register struct olddirect *dp;
	static struct direct dir;

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
		dp = (struct olddirect *)(dirp->dd_buf + dirp->dd_loc);
		dirp->dd_loc += sizeof(struct olddirect);
		if (dp->od_ino == 0)
			continue;
		dir.d_ino = dp->od_ino;
		strncpy(dir.d_name, dp->od_name, ODIRSIZ);
		dir.d_name[ODIRSIZ] = '\0'; /* insure null termination */
		dir.d_namlen = strlen(dir.d_name);
		dir.d_reclen = DIRBLKSIZ;
		return (&dir);
	}
}
E 1
