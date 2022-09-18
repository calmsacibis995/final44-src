h32596
s 00000/00000/00017
d D 8.1 93/06/06 22:11:45 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00017/00000/00000
d D 5.1 91/04/24 17:37:40 bostic 1 0
c date and time created 91/04/24 17:37:40 by bostic
e
u
U
t
T
I 1
static char sccsid[] = "@(#)closedir.c 4.2 3/10/82";

#include <sys/types.h>
#include <ndir.h>

/*
 * close a directory.
 */
void
closedir(dirp)
	register DIR *dirp;
{
	close(dirp->dd_fd);
	dirp->dd_fd = -1;
	dirp->dd_loc = 0;
	free(dirp);
}
E 1
