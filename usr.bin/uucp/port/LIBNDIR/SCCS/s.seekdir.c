h61976
s 00000/00000/00031
d D 8.1 93/06/06 22:11:50 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00031/00000/00000
d D 5.1 91/04/24 17:37:43 bostic 1 0
c date and time created 91/04/24 17:37:43 by bostic
e
u
U
t
T
I 1
static char sccsid[] = "@(#)seekdir.c 4.6 9/12/82";

#include <sys/param.h>
#include <ndir.h>

/*
 * seek to an entry in a directory.
 * Only values returned by "telldir" should be passed to seekdir.
 */
void
seekdir(dirp, loc)
	register DIR *dirp;
	long loc;
{
	long base, offset;
	struct direct *dp;

/* rti!trt: Always seek.  Slower, but safer. This may even fix a bug.
	if (loc == telldir(dirp))
		return;
 */
	base = loc & ~(DIRBLKSIZ - 1);
	offset = loc & (DIRBLKSIZ - 1);
	lseek(dirp->dd_fd, base, 0);
	dirp->dd_loc = 0;
	while (dirp->dd_loc < offset) {
		dp = readdir(dirp);
		if (dp == NULL)
			return;
	}
}
E 1
