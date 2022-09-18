h64280
s 00003/00001/00087
d D 8.2 95/05/04 17:59:52 christos 5 4
c 
e
s 00002/00002/00086
d D 8.1 93/05/31 15:44:36 bostic 4 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00088
d R 8.2 93/05/31 15:25:25 bostic 3 2
c add copyright notices, SCCS headers, yank to 8.1
e
s 00002/00002/00086
d R 8.1 93/05/31 15:19:29 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00088/00000/00000
d D 5.1 91/03/07 20:27:37 bostic 1 0
c date and time created 91/03/07 20:27:37 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * Routines to check for mail.  (Perhaps make part of main.c?)
 */

#include "shell.h"
#include "exec.h"	/* defines padvance() */
#include "var.h"
#include "output.h"
#include "memalloc.h"
#include "error.h"
#include <sys/types.h>
#include <sys/stat.h>


#define MAXMBOXES 10


STATIC int nmboxes;			/* number of mailboxes */
STATIC time_t mailtime[MAXMBOXES];	/* times of mailboxes */



/*
 * Print appropriate message(s) if mail has arrived.  If the argument is
 * nozero, then the value of MAIL has changed, so we just update the
 * values.
 */

void
D 5
chkmail(silent) {
E 5
I 5
chkmail(silent)
	int silent;
{
E 5
	register int i;
	char *mpath;
	char *p;
	register char *q;
	struct stackmark smark;
	struct stat statb;

	if (silent)
		nmboxes = 10;
	if (nmboxes == 0)
		return;
	setstackmark(&smark);
	mpath = mpathset()? mpathval() : mailval();
	for (i = 0 ; i < nmboxes ; i++) {
		p = padvance(&mpath, nullstr);
		if (p == NULL)
			break;
		if (*p == '\0')
			continue;
		for (q = p ; *q ; q++);
		if (q[-1] != '/')
			abort();
		q[-1] = '\0';			/* delete trailing '/' */
#ifdef notdef /* this is what the System V shell claims to do (it lies) */
		if (stat(p, &statb) < 0)
			statb.st_mtime = 0;
		if (statb.st_mtime > mailtime[i] && ! silent) {
			out2str(pathopt? pathopt : "you have mail");
			out2c('\n');
		}
		mailtime[i] = statb.st_mtime;
#else /* this is what it should do */
		if (stat(p, &statb) < 0)
			statb.st_size = 0;
		if (statb.st_size > mailtime[i] && ! silent) {
			out2str(pathopt? pathopt : "you have mail");
			out2c('\n');
		}
		mailtime[i] = statb.st_size;
#endif
	}
	nmboxes = i;
	popstackmark(&smark);
}
E 1
