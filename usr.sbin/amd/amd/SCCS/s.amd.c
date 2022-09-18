h33389
s 00005/00005/00313
d D 8.1 93/06/06 12:06:35 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00000/00312
d D 5.5 93/06/06 12:06:29 bostic 6 4
c it's a main, add a copyright string for the lawyers
e
s 00002/00002/00310
d R 8.1 93/06/06 11:39:37 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00311
d D 5.4 92/02/09 08:47:56 pendry 4 3
c merge in new release
e
s 00003/00002/00309
d D 5.3 91/05/12 15:54:59 pendry 3 2
c checkpoint for network tape
e
s 00051/00040/00260
d D 5.2 91/03/17 13:32:54 pendry 2 1
c from amd5.3 alpha11
e
s 00300/00000/00000
d D 5.1 90/06/29 12:00:59 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: amd.c,v 5.2 90/06/23 22:19:18 jsp Rel $
E 2
I 2
D 3
 * $Id: amd.c,v 5.2.1.4 91/03/17 17:48:40 jsp Alpha $
E 2
 *
E 3
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 7
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: amd.c,v 5.2.1.5 91/05/07 22:17:44 jsp Alpha $
E 4
I 4
 * $Id: amd.c,v 5.2.2.1 1992/02/09 15:08:15 jsp beta $
E 4
 *
E 3
 */

I 6
#ifndef lint
D 7
char copyright[] =
"%Z% Copyright (c) 1993 The Regents of the University of California.\n\
 All rights reserved.\n";
E 7
I 7
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 7
#endif /* not lint */

E 6
/*
 * Automounter
 */

#include "am.h"
#include <sys/signal.h>
D 2
#include <netdb.h>
E 2
#include <sys/ioctl.h>
#include <fcntl.h>
#include <setjmp.h>

char pid_fsname[16 + MAXHOSTNAMELEN];	/* "kiska.southseas.nz:(pid%d)" */
char *progname;				/* "amd" */
#ifdef HAS_HOST
I 2
#ifdef HOST_EXEC
E 2
char *host_helper;
I 2
#endif /* HOST_EXEC */
E 2
#endif /* HAS_HOST */
char *auto_dir = "/a";
char *hostdomain = "unknown.domain";
D 2
char hostname[MAXHOSTNAMELEN];		/* Hostname */
E 2
I 2
char hostname[MAXHOSTNAMELEN] = "localhost"; /* Hostname */
E 2
char hostd[2*MAXHOSTNAMELEN];		/* Host+domain */
char *op_sys = OS_REP;			/* Name of current op_sys */
char *arch = ARCH_REP;			/* Name of current architecture */
char *endian = ARCH_ENDIAN;		/* Big or Little endian */
I 2
char *wire;
E 2
int foreground = 1;			/* This is the top-level server */
int mypid;				/* Current process id */
int immediate_abort;			/* Should close-down unmounts be retried */
struct in_addr myipaddr;		/* (An) IP address of this host */
D 2
serv_state amd_state = Start;
E 2
I 2
serv_state amd_state;
E 2
struct amd_stats amd_stats;		/* Server statistics */
time_t do_mapc_reload = 0;		/* mapc_reload() call required? */
jmp_buf select_intr;
int select_intr_valid;
int orig_umask;

/*
 * Signal handler:
 * SIGINT - tells amd to do a full shutdown, including unmounting all filesystem.
 * SIGTERM - tells amd to shutdown now.  Just unmounts the automount nodes.
 */
static void sigterm(sig)
int sig;
{
#ifdef SYS5_SIGNALS
	signal(sig, sigterm);
D 2
#endif * SYS5_SIGNALS */
E 2
I 2
#endif /* SYS5_SIGNALS */
E 2

	switch (sig) {
	case SIGINT:
		immediate_abort = 15;
		break;

	case SIGTERM:
		immediate_abort = -1;
		/* fall through... */

	default:
		plog(XLOG_WARNING, "WARNING: automounter going down on signal %d", sig);
		break;
	}
	if (select_intr_valid)
		longjmp(select_intr, sig);
}

/*
 * Hook for cache reload.
 * When a SIGHUP arrives it schedules a call to mapc_reload
 */
I 2
/*ARGSUSED*/
E 2
static void sighup(sig)
int sig;
{
#ifdef SYS5_SIGNALS
	signal(sig, sighup);
D 2
#endif /* SUS5_SIGNALS */
E 2
I 2
#endif /* SYS5_SIGNALS */
E 2

#ifdef DEBUG
	if (sig != SIGHUP)
		dlog("spurious call to sighup");
#endif /* DEBUG */
	/*
	 * Force a reload by zero'ing the timer
	 */
	if (amd_state == Run)
		do_mapc_reload = 0;
}

I 2
/*ARGSUSED*/
E 2
static void parent_exit(sig)
int sig;
{
	exit(0);
}

static int daemon_mode(P_void)
{
D 2
	int bgpid = background();
E 2
I 2
	int bgpid;
E 2

I 2
	signal(SIGQUIT, parent_exit);
	bgpid = background();

E 2
	if (bgpid != 0) {
		if (print_pid) {
			printf("%d\n", bgpid);
			fflush(stdout);
		}
		/*
		 * Now wait for the automount points to
		 * complete.
		 */
D 2
		signal(SIGQUIT, parent_exit);
E 2
		for (;;)
			pause();
	}

I 2
	signal(SIGQUIT, SIG_DFL);

E 2
	/*
	 * Pretend we are in the foreground again
	 */
	foreground = 1;
I 2

E 2
#ifdef TIOCNOTTY
	{
		int t = open("/dev/tty", O_RDWR);
		if (t < 0) {
			if (errno != ENXIO)	/* not an error if already no controlling tty */
				plog(XLOG_WARNING, "Could not open controlling tty: %m");
D 2
		} else if (ioctl(t, TIOCNOTTY, 0) < 0) {
			plog(XLOG_WARNING, "Could not disassociate tty (TIOCNOTTY): %m");
E 2
I 2
		} else {
			if (ioctl(t, TIOCNOTTY, 0) < 0 && errno != ENOTTY)
				plog(XLOG_WARNING, "Could not disassociate tty (TIOCNOTTY): %m");
			(void) close(t);
E 2
		}
	}
#else
	(void) setpgrp();
#endif /* TIOCNOTTY */

	return getppid();
}

main(argc, argv)
int argc;
char *argv[];
{
D 2
	struct hostent *hp, *gethostbyname();
E 2
	char *domdot;
	int ppid = 0;
	int error;

	/*
	 * Make sure some built-in assumptions are true before we start
	 */
	assert(sizeof(nfscookie) >= sizeof (unsigned int));
	assert(sizeof(int) >= 4);

	/*
	 * Set processing status.
	 */
	amd_state = Start;

	/*
I 2
	 * Determine program name
	 */
	if (argv[0]) {
		progname = strrchr(argv[0], '/');
		if (progname && progname[1])
			progname++;
		else
			progname = argv[0];
	}

	if (!progname)
		progname = "amd";

	/*
	 * Initialise process id.  This is kept
	 * cached since it is used for generating
	 * and using file handles.
	 */
	mypid = getpid();

	/*
E 2
	 * Get local machine name
	 */
	if (gethostname(hostname, sizeof(hostname)) < 0) {
		plog(XLOG_FATAL, "gethostname: %m");
		going_down(1);
	}
	/*
	 * Check it makes sense
	 */
	if (!*hostname) {
		plog(XLOG_FATAL, "host name is not set");
		going_down(1);
	}
	/*
	 * Partially initialise hostd[].  This
	 * is completed in get_args().
	 */
	if (domdot = strchr(hostname, '.')) {
		/*
		 * Hostname already contains domainname.
		 * Split out hostname and domainname
		 * components
		 */
		*domdot++ = '\0';
		hostdomain = domdot;
	}
	strcpy(hostd, hostname);

	/*
	 * Trap interrupts for shutdowns.
	 */
	(void) signal(SIGINT, sigterm);

	/*
	 * Hangups tell us to reload the cache
	 */
	(void) signal(SIGHUP, sighup);

	/*
	 * Trap Terminate so that we can shutdown gracefully (some chance)
	 */
	(void) signal(SIGTERM, sigterm);
	/*
	 * Trap Death-of-a-child.  These allow us to
	 * pick up the exit status of backgrounded mounts.
	 * See "sched.c".
	 */
	(void) signal(SIGCHLD, sigchld);

	/*
D 2
	 * Initialise process id.  This is kept
	 * cached since it is used for generating
	 * and using file handles.
	 */
	mypid = getpid();

#ifdef notdef
/*
 * XXX - Doing this plugs most of a memory leak in
 * gethostbyname on SunOS 4.  I see no good reason
 * why the host database needs to grab 1.5K of
 * private data space...  However, for the moment,
 * I will take its word that it is a _good thing_
 * (jsp)
 */
	(void) sethostent(0);
#endif /* notdef */

	/*
E 2
	 * Fix-up any umask problems.  Most systems default
	 * to 002 which is not too convenient for our purposes
	 */
	orig_umask = umask(0);

	/*
I 2
	 * Figure out primary network name
	 */
	wire = getwire();

	/*
E 2
	 * Determine command-line arguments
	 */
	get_args(argc, argv);

	/*
	 * Get our own IP address so that we
D 2
	 * can mount the automounter.  There
	 * is probably a better way of doing
	 * this, but messing about with SIOCGIFCONF
	 * seems to be heading towards the non-portable
	 * arena.
E 2
I 2
	 * can mount the automounter.
E 2
	 */
D 2
	hp = gethostbyname(hostname);
	if (!hp || hp->h_addrtype != AF_INET) {
		plog(XLOG_FATAL, "Can't determine IP address of this host (%s)", hostname);
		going_down(1);
E 2
I 2
	{ struct sockaddr_in sin;
	  get_myaddress(&sin);
	  myipaddr.s_addr = sin.sin_addr.s_addr;
E 2
	}
D 2
	myipaddr = *(struct in_addr *) hp->h_addr;
E 2

	/*
	 * Now check we are root.
	 */
	if (geteuid() != 0) {
		plog(XLOG_FATAL, "Must be root to mount filesystems (euid = %d)", geteuid());
		going_down(1);
	}

#ifdef HAS_NIS_MAPS
	/*
	 * If the domain was specified then bind it here
	 * to circumvent any default bindings that may
	 * be done in the C library.
	 */
	if (domain && yp_bind(domain)) {
		plog(XLOG_FATAL, "Can't bind to domain \"%s\"", domain);
		going_down(1);
	}
#endif /* HAS_NIS_MAPS */

#ifdef DEBUG
	Debug(D_DAEMON)
#endif /* DEBUG */
	ppid = daemon_mode();

	sprintf(pid_fsname, "%s:(pid%d)", hostname, mypid);

	do_mapc_reload = clocktime() + ONE_HOUR;

	/*
	 * Register automounter with system
	 */
	error = mount_automounter(ppid);
	if (error && ppid)
		kill(SIGALRM, ppid);
	going_down(error);

	abort();
}
E 1
