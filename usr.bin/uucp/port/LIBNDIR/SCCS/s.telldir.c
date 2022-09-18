h37777
s 00000/00000/00016
d D 8.1 93/06/06 22:11:52 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00016/00000/00000
d D 5.1 91/04/24 17:37:44 bostic 1 0
c date and time created 91/04/24 17:37:44 by bostic
e
u
U
t
T
I 1
static char sccsid[] = "@(#)telldir.c 4.1 2/21/82";

#include <sys/types.h>
#include <ndir.h>

extern	long	lseek();	/* needed for pdp 11s -- ikonas!mcm */

/*
 * return a pointer into a directory
 */
long
telldir(dirp)
	DIR *dirp;
{
	return (lseek(dirp->dd_fd, 0L, 1) - dirp->dd_size + dirp->dd_loc);
}
E 1
