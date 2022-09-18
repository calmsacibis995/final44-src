h50226
s 00000/00000/00046
d D 8.1 93/06/06 22:30:14 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00040
d D 4.4 91/04/18 19:00:19 bostic 5 4
c new copyright; att/bsd/shared
e
s 00005/00003/00037
d D 4.3 89/05/11 13:35:29 bostic 4 3
c file reorg, pathnames.h, paths.h
e
s 00002/00002/00038
d D 4.2 83/05/19 09:38:28 ralph 3 1
c fixed perror message and getlogin assignment.
e
s 00001/00001/00039
d R 4.2 83/05/19 09:36:28 ralph 2 1
c fixed perror message.
e
s 00040/00000/00000
d D 4.1 83/03/30 12:08:42 sam 1 0
c date and time created 83/03/30 12:08:42 by sam
e
u
U
t
T
I 5
/*-
 * %sccs.include.proprietary.c%
 */

E 5
I 1
#ifndef lint
D 5
static char sccsid[] = "%W% %G%";
#endif
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

I 4
#include <sys/types.h>
#include <pwd.h>
E 4
#include "xmail.h"
D 4
#include "pwd.h"
#include "sys/types.h"
E 4
I 4
#include "pathnames.h"

E 4
MINT *a[42], *x, *b, *one, *c64, *t45, *z, *q, *r, *two, *t15;
char buf[256];
D 4
char maildir[] = { "/usr/spool/secretmail"};
E 4
I 4
char maildir[] = _PATH_SECRETMAIL;
E 4
main()
{
	int uid, i;
	FILE *fd;
	char *myname, fname[128];
	uid = getuid();
D 3
	myname = getlogin();
E 3
I 3
	myname = (char *) getlogin();
E 3
	if(myname == NULL)
		myname = getpwuid(uid)->pw_name;
	sprintf(fname, "%s/%s.key", maildir, myname);
	comminit();
	setup(getpass("Gimme key: "));
	mkb();
	mkx();
#ifdef debug
	omout(b);
	omout(x);
#endif
	mka();
	i = creat(fname, 0644);
	if(i<0)
D 3
	{	perror("fname");
E 3
I 3
	{	perror(fname);
E 3
		exit(1);
	}
	close(i);
	fd = fopen(fname, "w");
	for(i=0; i<42; i++)
		nout(a[i], fd);
	exit(0);
}
E 1
