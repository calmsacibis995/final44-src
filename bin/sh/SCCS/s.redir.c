h09392
s 00015/00015/00302
d D 8.2 95/05/04 18:00:08 christos 6 5
c 
e
s 00002/00002/00315
d D 8.1 93/05/31 15:20:27 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00002/00302
d D 5.4 93/05/24 15:40:02 marc 4 3
c fixes to support old style handling of ` ` (quoting), and "for var do"
e
s 00003/00001/00301
d D 5.3 92/06/23 18:09:47 marc 3 2
c lseek takes an off_t (which is now a quad, so 0L loses bigtime)
e
s 00001/00023/00301
d D 5.2 92/05/21 19:03:23 marc 2 1
c no dupfd? no play...
e
s 00324/00000/00000
d D 5.1 91/03/07 20:27:57 bostic 1 0
c date and time created 91/03/07 20:27:57 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 6
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

E 6
/*
 * Code for dealing with input/output redirection.
 */

#include "shell.h"
#include "nodes.h"
#include "jobs.h"
#include "expand.h"
#include "redir.h"
#include "output.h"
#include "memalloc.h"
#include "error.h"
I 3
D 6
#include <sys/types.h>
E 3
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
I 3
#include <unistd.h>
E 6
E 3


#define EMPTY -2		/* marks an unused slot in redirtab */
#define PIPESIZE 4096		/* amount of buffering in a pipe */


MKINIT
struct redirtab {
	struct redirtab *next;
	short renamed[10];
};


MKINIT struct redirtab *redirlist;

I 4
/* 
 * We keep track of whether or not fd0 has been redirected.  This is for
 * background commands, where we want to redirect fd0 to /dev/null only
 * if it hasn't already been redirected.  
*/
int fd0_redirected = 0;
E 4

D 6
#ifdef __STDC__
STATIC void openredirect(union node *, char *);
STATIC int openhere(union node *);
#else
STATIC void openredirect();
STATIC int openhere();
#endif
E 6
I 6
STATIC void openredirect __P((union node *, char[10 ]));
STATIC int openhere __P((union node *));
E 6


D 6

E 6
/*
 * Process a list of redirection commands.  If the REDIR_PUSH flag is set,
 * old file descriptors are stashed away so that the redirection can be
 * undone by calling popredir.  If the REDIR_BACKQ flag is set, then the
 * standard output, and the standard error if it becomes a duplicate of
 * stdout, is saved in memory.
 */

void
redirect(redir, flags)
	union node *redir;
	int flags;
	{
	union node *n;
	struct redirtab *sv;
	int i;
	int fd;
	char memory[10];		/* file descriptors to write to memory */

	for (i = 10 ; --i >= 0 ; )
		memory[i] = 0;
	memory[1] = flags & REDIR_BACKQ;
	if (flags & REDIR_PUSH) {
		sv = ckmalloc(sizeof (struct redirtab));
		for (i = 0 ; i < 10 ; i++)
			sv->renamed[i] = EMPTY;
		sv->next = redirlist;
		redirlist = sv;
	}
	for (n = redir ; n ; n = n->nfile.next) {
		fd = n->nfile.fd;
		if ((flags & REDIR_PUSH) && sv->renamed[fd] == EMPTY) {
			INTOFF;
			if ((i = copyfd(fd, 10)) != EMPTY) {
				sv->renamed[fd] = i;
				close(fd);
			}
			INTON;
			if (i == EMPTY)
				error("Out of file descriptors");
		} else {
			close(fd);
		}
I 4
                if (fd == 0)
                        fd0_redirected++;
E 4
		openredirect(n, memory);
	}
	if (memory[1])
		out1 = &memout;
	if (memory[2])
		out2 = &memout;
}


STATIC void
openredirect(redir, memory)
	union node *redir;
	char memory[10];
	{
	int fd = redir->nfile.fd;
	char *fname;
	int f;

	/*
	 * We suppress interrupts so that we won't leave open file
	 * descriptors around.  This may not be such a good idea because
	 * an open of a device or a fifo can block indefinitely.
	 */
	INTOFF;
	memory[fd] = 0;
	switch (redir->nfile.type) {
	case NFROM:
		fname = redir->nfile.expfname;
		if ((f = open(fname, O_RDONLY)) < 0)
			error("cannot open %s: %s", fname, errmsg(errno, E_OPEN));
movefd:
		if (f != fd) {
			copyfd(f, fd);
			close(f);
		}
		break;
	case NTO:
		fname = redir->nfile.expfname;
#ifdef O_CREAT
		if ((f = open(fname, O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0)
			error("cannot create %s: %s", fname, errmsg(errno, E_CREAT));
#else
		if ((f = creat(fname, 0666)) < 0)
			error("cannot create %s: %s", fname, errmsg(errno, E_CREAT));
#endif
		goto movefd;
	case NAPPEND:
		fname = redir->nfile.expfname;
#ifdef O_APPEND
		if ((f = open(fname, O_WRONLY|O_CREAT|O_APPEND, 0666)) < 0)
			error("cannot create %s: %s", fname, errmsg(errno, E_CREAT));
#else
		if ((f = open(fname, O_WRONLY)) < 0
		 && (f = creat(fname, 0666)) < 0)
			error("cannot create %s: %s", fname, errmsg(errno, E_CREAT));
D 3
		lseek(f, 0L, 2);
E 3
I 3
		lseek(f, (off_t)0, 2);
E 3
#endif
		goto movefd;
	case NTOFD:
	case NFROMFD:
		if (redir->ndup.dupfd >= 0) {	/* if not ">&-" */
			if (memory[redir->ndup.dupfd])
				memory[fd] = 1;
			else
				copyfd(redir->ndup.dupfd, fd);
		}
		break;
	case NHERE:
	case NXHERE:
		f = openhere(redir);
		goto movefd;
	default:
		abort();
	}
	INTON;
}


/*
 * Handle here documents.  Normally we fork off a process to write the
 * data to a pipe.  If the document is short, we can stuff the data in
 * the pipe without forking.
 */

STATIC int
openhere(redir)
	union node *redir;
	{
	int pip[2];
D 6
	int len;
E 6
I 6
	int len = 0;
E 6

	if (pipe(pip) < 0)
		error("Pipe call failed");
	if (redir->type == NHERE) {
		len = strlen(redir->nhere.doc->narg.text);
		if (len <= PIPESIZE) {
			xwrite(pip[1], redir->nhere.doc->narg.text, len);
			goto out;
		}
	}
	if (forkshell((struct job *)NULL, (union node *)NULL, FORK_NOJOB) == 0) {
		close(pip[0]);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGHUP, SIG_IGN);
#ifdef SIGTSTP
		signal(SIGTSTP, SIG_IGN);
#endif
		signal(SIGPIPE, SIG_DFL);
		if (redir->type == NHERE)
			xwrite(pip[1], redir->nhere.doc->narg.text, len);
		else
			expandhere(redir->nhere.doc, pip[1]);
		_exit(0);
	}
out:
	close(pip[1]);
	return pip[0];
}



/*
 * Undo the effects of the last redirection.
 */

void
popredir() {
	register struct redirtab *rp = redirlist;
	int i;

	for (i = 0 ; i < 10 ; i++) {
		if (rp->renamed[i] != EMPTY) {
I 4
                        if (i == 0)
                                fd0_redirected--;
E 4
			close(i);
			if (rp->renamed[i] >= 0) {
				copyfd(rp->renamed[i], i);
				close(rp->renamed[i]);
			}
		}
	}
	INTOFF;
	redirlist = rp->next;
	ckfree(rp);
	INTON;
}

D 4


E 4
/*
 * Undo all redirections.  Called on error or interrupt.
 */

#ifdef mkinit

INCLUDE "redir.h"

RESET {
	while (redirlist)
		popredir();
}

SHELLPROC {
	clearredir();
}

#endif

I 4
/* Return true if fd 0 has already been redirected at least once.  */
int
fd0_redirected_p () {
        return fd0_redirected != 0;
}
E 4

/*
 * Discard all saved file descriptors.
 */

void
clearredir() {
	register struct redirtab *rp;
	int i;

	for (rp = redirlist ; rp ; rp = rp->next) {
		for (i = 0 ; i < 10 ; i++) {
			if (rp->renamed[i] >= 0) {
				close(rp->renamed[i]);
			}
			rp->renamed[i] = EMPTY;
		}
	}
}



/*
D 2
 * Copy a file descriptor, like the F_DUPFD option of fcntl.  Returns -1
E 2
I 2
 * Copy a file descriptor to be >= to.  Returns -1
E 2
 * if the source file descriptor is closed, EMPTY if there are no unused
 * file descriptors left.
 */

int
D 6
copyfd(from, to) {
E 6
I 6
copyfd(from, to) 
	int from;
	int to;
{
E 6
D 2
#ifdef F_DUPFD
E 2
	int newfd;

	newfd = fcntl(from, F_DUPFD, to);
	if (newfd < 0 && errno == EMFILE)
		return EMPTY;
	return newfd;
D 2
#else
	char toclose[32];
	int i;
	int newfd;
	int e;

	for (i = 0 ; i < to ; i++)
		toclose[i] = 0;
	INTOFF;
	while ((newfd = dup(from)) >= 0 && newfd < to)
		toclose[newfd] = 1;
	e = errno;
	for (i = 0 ; i < to ; i++) {
		if (toclose[i])
			close(i);
	}
	INTON;
	if (newfd < 0 && e == EMFILE)
		return EMPTY;
	return newfd;
#endif
E 2
}
E 1
