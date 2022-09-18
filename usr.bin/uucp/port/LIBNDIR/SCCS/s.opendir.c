h50151
s 00000/00000/00029
d D 8.1 93/06/06 22:11:48 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00029/00000/00000
d D 5.1 91/04/24 17:37:41 bostic 1 0
c date and time created 91/04/24 17:37:41 by bostic
e
u
U
t
T
I 1
static char sccsid[] = "@(#)opendir.c 4.3 8/4/82";

#include <sys/types.h>
#include <sys/stat.h>
#include <ndir.h>

/*
 * open a directory.
 */
DIR *
opendir(name)
	char *name;
{
	register DIR *dirp;
	register int fd;
	struct stat sbuf;

	if ((fd = open(name, 0)) == -1)
		return NULL;
	fstat(fd, &sbuf);
	if (((sbuf.st_mode & S_IFDIR) == 0) ||
	    ((dirp = (DIR *)malloc(sizeof(DIR))) == NULL)) {
		close (fd);
		return NULL;
	}
	dirp->dd_fd = fd;
	dirp->dd_loc = 0;
	return dirp;
}
E 1
