h33550
s 00002/00002/00231
d D 8.6 95/04/26 13:09:04 mckusick 8 7
c update for new kernel filesystem structure (vfsconf)
e
s 00002/00004/00231
d D 8.5 94/06/14 16:43:50 mkm 7 6
c misc bug fixes (from mycroft)
e
s 00000/00003/00235
d D 8.4 94/03/27 13:45:27 pendry 6 5
c now launch a sub-process to deal with each request.
e
s 00001/00001/00237
d D 8.3 94/03/27 11:45:12 bostic 5 4
c forgot to change the argument
e
s 00055/00038/00183
d D 8.2 94/03/27 11:43:24 bostic 4 3
c Jan-Simon Pendry's and my new mount code
e
s 00002/00002/00219
d D 8.1 93/06/05 11:03:52 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00221
d D 5.1 92/07/13 15:47:26 pendry 2 1
c move to rev 5
e
s 00221/00000/00000
d D 1.1 92/07/09 14:47:41 pendry 1 0
c date and time created 92/07/09 14:47:41 by pendry
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 3
I 3
D 4
 * Copyright (c) 1992, 1993
E 4
I 4
 * Copyright (c) 1992, 1993, 1994
E 4
 *	The Regents of the University of California.  All rights reserved.
E 3
D 4
 * All rights reserved.
E 4
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
D 4
 *
 *	%W% (Berkeley) %G%
 *
 * $Id: portald.c,v 1.3 1992/05/27 07:09:27 jsp Exp jsp $
E 4
 */

D 4
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
E 4
I 4
#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1992, 1993, 1994\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 4
#include <sys/param.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/syslog.h>
#include <sys/mount.h>

I 4
#include <err.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mntopts.h"
E 4
#include "pathnames.h"
#include "portald.h"

I 4
struct mntopt mopts[] = {
	MOPT_STDOPTS,
	{ NULL }
};

static void usage __P((void));

E 4
static sig_atomic_t readcf;	/* Set when SIGHUP received */

static void sigchld(sig)
int sig;
{
	pid_t pid;

	while ((pid = waitpid((pid_t) -1, (int *) 0, WNOHANG)) > 0)
		;
D 7
	if (pid < 0)
E 7
I 7
	if (pid < 0 && errno != ECHILD)
E 7
		syslog(LOG_WARNING, "waitpid: %s", strerror(errno));
}

D 4
int main(c, v)
int c;
char *v[];
E 4
I 4
int
D 5
main(c, argv)
E 5
I 5
main(argc, argv)
E 5
	int argc;
	char *argv[];
E 4
{
	struct portal_args args;
	struct sockaddr_un un;
	char *conf;
	char *mountpt;
	int mntflags = 0;
D 4
	int usage = 0;
E 4
	char tag[32];

	qelem q;
	int rc;
	int so;
I 4
	int error = 0;
E 4

	/*
	 * Crack command line args
	 */
	int ch;

D 4
	while ((ch = getopt(c, v, "F:")) != EOF) {
E 4
I 4
	while ((ch = getopt(argc, argv, "o:")) != EOF) {
E 4
		switch (ch) {
D 4
		case 'F':
			mntflags = atoi(optarg);
E 4
I 4
		case 'o':
D 8
			getmntopts(optarg, mopts, &mntflags);
E 8
I 8
			getmntopts(optarg, mopts, &mntflags, 0);
E 8
E 4
			break;
		default:
D 4
			usage = 1;
E 4
I 4
			error = 1;
E 4
			break;
		}
	}

D 4
	if (optind != (c - 2))
		usage = 1;
E 4
I 4
	if (optind != (argc - 2))
		error = 1;
E 4

D 4
	if (usage) {
		fprintf(stderr, "Usage: mount_portal [ fsoptions ] config mount-point\n");
		exit(1);
	}
E 4
I 4
	if (error)
		usage();
E 4

	/*
	 * Get config file and mount point
	 */
D 4
	conf = v[optind];
	mountpt = v[optind+1];
E 4
I 4
	conf = argv[optind];
	mountpt = argv[optind+1];
E 4

	/*
	 * Construct the listening socket
	 */
	un.sun_family = AF_UNIX;
	if (sizeof(_PATH_TMPPORTAL) >= sizeof(un.sun_path)) {
		fprintf(stderr, "mount_portal: portal socket name too long\n");
		exit(1);
	}
	strcpy(un.sun_path, _PATH_TMPPORTAL);
	mktemp(un.sun_path);
	un.sun_len = strlen(un.sun_path);

	so = socket(AF_UNIX, SOCK_STREAM, 0);
	if (so < 0) {
		fprintf(stderr, "mount_portal: socket: %s\n", strerror(errno));
		exit(1);
	}
	(void) unlink(un.sun_path);
D 4
	if (bind(so, (struct sockaddr *) &un, sizeof(un)) < 0) {
		fprintf(stderr, "mount_portal: bind: %s\n", strerror(errno));
		exit(1);
	}
	(void) unlink(un.sun_path);
E 4
I 4
	if (bind(so, (struct sockaddr *) &un, sizeof(un)) < 0)
		err(1, NULL);
	(void) unlink(un.sun_path);
E 4

	(void) listen(so, 5);

	args.pa_socket = so;
	sprintf(tag, "portal:%d", getpid());
	args.pa_config = tag;

D 8
	rc = mount(MOUNT_PORTAL, mountpt, mntflags, &args);
E 8
I 8
	rc = mount("portal", mountpt, mntflags, &args);
E 8
D 4
	if (rc < 0) {
		fprintf(stderr, "mount_portal: mount: %s\n", strerror(errno));
		exit(1);
	}
E 4
I 4
	if (rc < 0)
		err(1, NULL);
E 4

D 7
#ifdef notdef
E 7
	/*
	 * Everything is ready to go - now is a good time to fork
	 */
	daemon(0, 0);
D 7
#endif
E 7

	/*
	 * Start logging (and change name)
	 */
	openlog("portald", LOG_CONS|LOG_PID, LOG_DAEMON);

	q.q_forw = q.q_back = &q;
	readcf = 1;

	signal(SIGCHLD, sigchld);

	/*
	 * Just loop waiting for new connections and activating them
	 */
	for (;;) {
		struct sockaddr_un un2;
		int len2 = sizeof(un2);
		int so2;
		pid_t pid;
		fd_set fdset;
		int rc;

		/*
		 * Check whether we need to re-read the configuration file
		 */
		if (readcf) {
			readcf = 0;
			conf_read(&q, conf);
			continue;
		}
	
		/*
		 * Accept a new connection
		 * Will get EINTR if a signal has arrived, so just
		 * ignore that error code
		 */
		FD_SET(so, &fdset);
		rc = select(so+1, &fdset, (void *) 0, (void *) 0, (void *) 0);
		if (rc < 0) {
			if (errno == EINTR)
				continue;
			syslog(LOG_ERR, "select: %s", strerror(errno));
			exit(1);
		}
		if (rc == 0)
			break;
		so2 = accept(so, (struct sockaddr *) &un2, &len2);
		if (so2 < 0) {
			/*
			 * The unmount function does a shutdown on the socket
			 * which will generated ECONNABORTED on the accept.
			 */
			if (errno == ECONNABORTED)
				break;
			if (errno != EINTR) {
				syslog(LOG_ERR, "accept: %s", strerror(errno));
				exit(1);
			}
			continue;
		}

		/*
		 * Now fork a new child to deal with the connection
		 */
D 6
#ifdef notdef
E 6
	eagain:;
		switch (pid = fork()) {
		case -1:
			if (errno == EAGAIN) {
				sleep(1);
				goto eagain;
			}
			syslog(LOG_ERR, "fork: %s", strerror(errno));
			break;
		case 0:
			(void) close(so);
			activate(&q, so2);
D 7
			break;
E 7
I 7
			exit(0);
E 7
		default:
			(void) close(so2);
			break;
		}
D 6
#endif
		activate(&q, so2);
E 6
	}
	syslog(LOG_INFO, "%s unmounted", mountpt);
	exit(0);
I 4
}

static void
usage()
{
	(void)fprintf(stderr,
		"usage: mount_portal [-o options] config mount-point\n");
	exit(1);
E 4
}
E 1
