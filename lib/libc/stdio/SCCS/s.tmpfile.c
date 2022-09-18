h58315
s 00002/00002/00051
d D 8.1 93/06/04 13:09:57 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00050
d D 5.5 93/03/04 15:36:36 torek 5 4
c bcopy => memcpy (safe in all these cases) for ANSI (sigh)
e
s 00005/00009/00048
d D 5.4 91/05/27 11:08:57 bostic 4 3
c block every signal that we can block
e
s 00001/00000/00056
d D 5.3 91/02/24 13:30:23 bostic 3 2
c Add include files to get prototype declarations, and fix bugs found.
e
s 00034/00011/00022
d D 5.2 91/02/22 16:59:57 bostic 2 1
c cleanup, update, reimplement to work as correctly as possible
e
s 00033/00000/00000
d D 5.1 91/01/20 21:35:02 bostic 1 0
c new stdio
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 2
#include <sys/param.h>
#include <stdio.h>
E 2
I 2
#include <sys/types.h>
#include <signal.h>
I 3
#include <unistd.h>
E 3
E 2
#include <errno.h>
I 2
#include <stdio.h>
#include <paths.h>
E 2

FILE *
tmpfile()
{
I 2
	sigset_t set, oset;
E 2
	FILE *fp;
D 2
	int e;
	char *f, buf[MAXPATHLEN];
E 2
I 2
	int fd, sverrno;
#define	TRAILER	"tmp.XXXXXX"
	char buf[sizeof(_PATH_TMP) + sizeof(TRAILER)];
E 2

D 2
	if ((f = tmpnam(buf)) == NULL)
		return (NULL);
	fp = fopen(f, "w+");
	e = errno;
	(void) unlink(f);
	errno = e;
	return (fp);
E 2
I 2
D 5
	bcopy(_PATH_TMP, buf, sizeof(_PATH_TMP) - 1);
	bcopy(TRAILER, buf + sizeof(_PATH_TMP) - 1, sizeof(TRAILER));
E 5
I 5
	(void)memcpy(buf, _PATH_TMP, sizeof(_PATH_TMP) - 1);
	(void)memcpy(buf + sizeof(_PATH_TMP) - 1, TRAILER, sizeof(TRAILER));
E 5

D 4
	sigemptyset(&set);
	sigaddset(&set, SIGHUP);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	sigaddset(&set, SIGTERM);
E 4
I 4
	sigfillset(&set);
E 4
	(void)sigprocmask(SIG_BLOCK, &set, &oset);

	fd = mkstemp(buf);
	if (fd != -1)
		(void)unlink(buf);

D 4
	(void)sigprocmask(SIG_SETMASK, &oset, (sigset_t *)NULL);
E 4
I 4
	(void)sigprocmask(SIG_SETMASK, &oset, NULL);
E 4

	if (fd == -1)
D 4
		return(NULL);
E 4
I 4
		return (NULL);
E 4

D 5
	if (!(fp = fdopen(fd, "w+"))) {
E 5
I 5
	if ((fp = fdopen(fd, "w+")) == NULL) {
E 5
		sverrno = errno;
		(void)close(fd);
		errno = sverrno;
D 4
		return(NULL);
E 4
I 4
		return (NULL);
E 4
	}
D 4
	return(fp);
E 4
I 4
	return (fp);
E 4
E 2
}
E 1
