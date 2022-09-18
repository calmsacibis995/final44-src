h50597
s 00006/00002/00016
d D 4.3 91/04/18 16:44:04 bostic 3 2
c new copyright; att/bsd/shared
e
s 00002/00001/00016
d D 4.2 89/05/11 10:04:34 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00017/00000/00000
d D 4.1 83/05/06 23:47:06 tut 1 0
c date and time created 83/05/06 23:47:06 by tut
e
u
U
t
T
I 3
/*-
 * %sccs.include.proprietary.c%
 */

E 3
I 1
#ifndef lint
D 3
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

I 2
#include "pathnames.h"
E 2
char refdir[50];

savedir()
{
	if (refdir[0]==0)
D 2
		corout ("", refdir, "/bin/pwd", "", 50);
E 2
I 2
		corout ("", refdir, _PATH_PWD, "", 50);
E 2
	trimnl(refdir);
}

restodir()
{
	chdir(refdir);
}
E 1
