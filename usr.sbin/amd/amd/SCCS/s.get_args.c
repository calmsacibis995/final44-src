h60765
s 00002/00002/00308
d D 8.1 93/06/06 11:39:50 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00309
d D 5.4 92/02/09 08:48:05 pendry 4 3
c merge in new release
e
s 00003/00002/00307
d D 5.3 91/05/12 15:55:24 pendry 3 2
c checkpoint for network tape
e
s 00008/00209/00301
d D 5.2 91/03/17 13:33:05 pendry 2 1
c from amd5.3 alpha11
e
s 00510/00000/00000
d D 5.1 90/06/29 12:01:02 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: get_args.c,v 5.2 90/06/23 22:19:24 jsp Rel $
E 2
I 2
D 3
 * $Id: get_args.c,v 5.2.1.4 91/03/17 17:48:02 jsp Alpha $
E 2
 *
E 3
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
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
 * $Id: get_args.c,v 5.2.1.5 91/05/07 22:17:52 jsp Alpha $
E 4
I 4
 * $Id: get_args.c,v 5.2.2.1 1992/02/09 15:08:23 jsp beta $
E 4
 *
E 3
 */

/*
 * Argument decode
 */

#include "am.h"
#ifdef HAS_SYSLOG
#include <syslog.h>
#endif /* HAS_SYSLOG */
#include <sys/stat.h>

extern int optind;
extern char *optarg;

#if defined(DEBUG) && defined(PARANOID)
char **gargv;
#endif /* defined(DEBUG) && defined(PARANOID) */
int restart_existing_mounts;
int print_pid;
int normalize_hosts;
char *karch;			/* Kernel architecture */
char *cluster;			/* Cluster name */
#ifdef HAS_NIS_MAPS
char *domain;			/* YP domain */
#endif /* HAS_NIS_MAPS */
#ifdef UPDATE_MTAB
char *mtab;
#endif /* UPDATE_MTAB */
D 2
FILE *logfp = stderr;		/* Log errors to stderr initially */
#ifdef HAS_SYSLOG
int syslogging;
#endif /* HAS_SYSLOG */
E 2
int afs_timeo = -1;
int afs_retrans = -1;
int am_timeo = AM_TTL;
int am_timeo_w = AM_TTL_W;
D 2
int xlog_level = 0;
int xlog_level_init = ~0;
E 2

D 2
/*
 * List of log options
 */
static struct opt_tab xlog_opt[] = {
	{ "all", XLOG_ALL },		/* All messages */
E 2
#ifdef DEBUG
D 2
	{ "debug", XLOG_DEBUG },	/* Debug messages */
#endif /* DEBUG */
	{ "error", XLOG_ERROR },	/* Non-fatal system errors */
	{ "fatal", XLOG_FATAL },	/* Fatal errors */
	{ "info", XLOG_INFO },		/* Information */
	{ "map", XLOG_MAP },		/* Map errors */
	{ "stats", XLOG_STATS },	/* Additional statistical information */
	{ "user", XLOG_USER },		/* Non-fatal user errors */
	{ "warn", XLOG_WARNING },	/* Warnings */
	{ "warning", XLOG_WARNING },	/* Warnings */
	{ 0, 0 }
};

#ifdef DEBUG
E 2
/*
 * List of debug options.
 */
static struct opt_tab dbg_opt[] = {
	{ "all", D_ALL },		/* All */
	{ "amq", D_AMQ },		/* Register for AMQ program */
	{ "daemon", D_DAEMON },		/* Enter daemon mode */
	{ "full", D_FULL },		/* Program trace */
	{ "mem", D_MEM },		/* Trace memory allocations */
	{ "mtab", D_MTAB },		/* Use local mtab file */
	{ "str", D_STR },		/* Debug string munging */
	{ "test", D_TEST },		/* Full debug - but no daemon */
	{ "trace", D_TRACE },		/* Protocol trace */
	{ 0, 0 }
};

int debug_flags = D_AMQ			/* Register AMQ */
		 |D_DAEMON		/* Enter daemon mode */
		 ;
D 2
#endif /* DEBUG */
E 2

D 2
void show_opts(ch, opts)
int ch;
struct opt_tab *opts;
{
	/*
	 * Display current debug options
	 */
	int i;
	int s = '{';
	fprintf(stderr, "\t[-%c {no}", ch);
	for (i = 0; opts[i].opt; i++) {
		fprintf(stderr, "%c%s", s, opts[i].opt);
		s = ',';
	}
	fputs("}]\n", stderr);
}

static int option(s, optb, flags)
char *s;
struct opt_tab *optb;
int *flags;
{
	char *p = s;
	int errs = 0;

	while (p && *p) {
		int neg;
		char *opt;
		struct opt_tab *dp;

		s = p;
		p = strchr(p, ',');
		if (p)
			*p = '\0';

		if (s[0] == 'n' && s[1] == 'o') {
			opt = s + 2;
			neg = 1;
		} else {
			opt = s;
			neg = 0;
		}

		/*
		 * Scan the array of debug options to find the
		 * corresponding flag value.  If it is found
		 * then set (or clear) the flag (depending on
		 * whether the option was prefixed with "no").
		 */
		for (dp = optb; dp->opt; dp++) {
			if (strcmp(opt, dp->opt) == 0) {
				if (neg)
					*flags &= ~dp->flag;
				else
					*flags |= dp->flag;
				break;
			}
		}

		if (dp->opt == 0) {
			/*
			 * This will log to stderr when parsing the command line
			 * since any -l option will not yet have taken effect.
			 */
			plog(XLOG_USER, "option \"%s\" not recognised", s);
			errs++;
		}
		/*
		 * Put the comma back
		 */
		if (p)
			*p++ = ',';
	}

	return errs;
}

E 2
/*
D 2
 * Switch on/off logging options
 */
int switch_option(opt)
char *opt;
{
	int xl = xlog_level;
	int rc = option(opt, xlog_opt, &xl);
	if (rc) {
		rc = EINVAL;
	} else {
		/*
		 * Keep track of initial log level, and
		 * don't allow options to be turned off.
		 */
		if (xlog_level_init == ~0)
			xlog_level_init = xl;
		else
			xl |= xlog_level_init;
		xlog_level = xl;
	}
	return rc;
}

#ifdef DEBUG
/*
E 2
 * Switch on/off debug options
 */
int debug_option(opt)
char *opt;
{
D 2
	return option(opt, dbg_opt, &debug_flags);
E 2
I 2
	return cmdoption(opt, dbg_opt, &debug_flags);
E 2
}
#endif /* DEBUG */

D 2
/*
 * Change current logfile
 */
int switch_to_logfile(logfile)
char *logfile;
{
	FILE *new_logfp = stderr;

	if (logfile) {
#ifdef HAS_SYSLOG
		syslogging = 0;
#endif /* HAS_SYSLOG */
		if (strcmp(logfile, "/dev/stderr") == 0)
			new_logfp = stderr;
		else if (strcmp(logfile, "syslog") == 0) {
#ifdef HAS_SYSLOG
			syslogging = 1;
			new_logfp = stderr;
#ifdef LOG_CONS
			openlog(progname, LOG_PID|LOG_CONS|LOG_NOWAIT,
				LOG_DAEMON);
#else
			/* 4.2 compat mode - XXX */
			openlog(progname, LOG_PID);
#endif /* LOG_CONS */
#else
			plog(XLOG_WARNING, "syslog option not supported, logging unchanged");
#endif /* HAS_SYSLOG */
		} else {
			(void) umask(orig_umask);
			new_logfp = fopen(logfile, "a");
			umask(0);
		}
	}

	/*
	 * If we couldn't open a new file, then continue using the old.
	 */
	if (!new_logfp && logfile) {
		plog(XLOG_USER, "%s: Can't open logfile: %m", logfile);
		return 1;
	}
	/*
	 * Close the previous file
	 */
	if (logfp && logfp != stderr)
		(void) fclose(logfp);
	logfp = new_logfp;
	return 0;
}

E 2
void get_args(c, v)
int c;
char *v[];
{
	int opt_ch;
	int usage = 0;
	char *logfile = 0;
	char *sub_domain = 0;

D 2
#if defined(DEBUG) && defined(PARANOID)
	gargv = v;
	progname = v[0];		/* Use argv[0] to try to solve Piete's problem */
#else
	if (v[0]) {
		progname = strrchr(v[0], '/');
		if (progname && progname[1])
			progname++;
		else
			progname = v[0];
	}
#endif /* defined(DEBUG) && defined(PARANOID) */
	if (!progname)
		progname = "amd";

E 2
	while ((opt_ch = getopt(c, v, "mnprva:c:d:h:k:l:t:w:x:y:C:D:")) != EOF)
	switch (opt_ch) {
	case 'a':
		if (*optarg != '/') {
			fprintf(stderr, "%s: -a option must begin with a '/'\n",
					progname);
			exit(1);
		}
		auto_dir = optarg;
		break;

	case 'c':
		am_timeo = atoi(optarg);
		if (am_timeo <= 0)
			am_timeo = AM_TTL;
		break;

	case 'd':
		sub_domain = optarg;
		break;

	case 'h':
#if defined(HAS_HOST) && defined(HOST_EXEC)
		host_helper = optarg;
#else
		plog(XLOG_USER, "-h: option ignored.  HOST_EXEC is not enabled.");
		break;
#endif /* defined(HAS_HOST) && defined(HOST_EXEC) */

	case 'k':
		karch = optarg;
		break;

	case 'l':
		logfile = optarg;
		break;

	case 'm':
		plog(XLOG_USER, "The -m option is no longer supported.");
		plog(XLOG_USER, "... Use `ypcat -k am.master` on the command line instead");
		break;

	case 'n':
		normalize_hosts = 1;
		break;

	case 'p':
		print_pid = 1;
		break;

	case 'r':
		restart_existing_mounts = 1;
		break;

	case 't':
		/* timeo.retrans */
		{ char *dot = strchr(optarg, '.');
		  if (dot) *dot = '\0';
		  if (*optarg) {
			afs_timeo = atoi(optarg);
		  }
		  if (dot) {
		  	afs_retrans = atoi(dot+1);
			*dot = '.';
		  }
		}
		break;

	case 'v':
D 2
		{ char buf[256];
		  show_rcs_info(version, buf);
		  fputs(buf, stderr);
		}
		fprintf(stderr,
			" for a%s %s running %s (%s-endian)\n",
					strchr("aeiou", arch[0]) ? "n" : "",
					arch, op_sys, endian);
E 2
I 2
		fprintf(stderr, "%s%s (%s-endian).\n", copyright, version, endian);
E 2
		fputs("Map support for: ", stderr);
		mapc_showtypes(stderr);
I 2
		fputs(".\nFS: ", stderr);
		ops_showfstypes(stderr);
E 2
		fputs(".\n", stderr);
I 2
		fprintf(stderr, "Primary network is %s.\n", wire);
E 2
		exit(0);
		break;

	case 'w':
		am_timeo_w = atoi(optarg);
		if (am_timeo_w <= 0)
			am_timeo_w = AM_TTL_W;
		break;

	case 'x':
		usage += switch_option(optarg);
		break;

	case 'y':
#ifdef HAS_NIS_MAPS
		domain = optarg;
#else
		plog(XLOG_USER, "-y: option ignored.  No NIS support available.");
#endif /* HAS_NIS_MAPS */
		break;

	case 'C':
		cluster = optarg;
		break;

	case 'D':
#ifdef DEBUG
		usage += debug_option(optarg);
#else
		fprintf(stderr, "%s: not compiled with DEBUG option -- sorry.\n", progname);
#endif /* DEBUG */
		break;

	default:
		usage = 1;
		break;
	}

D 2
	if (xlog_level == 0) {
		/* Take copy to avoid writable-strings problem */
		char *dfstr = strdup(XLOG_DEFSTR);
		usage += switch_option(dfstr);
		free((voidp) dfstr);
E 2
I 2
	if (xlog_level_init == ~0) {
		(void) switch_option("");
E 2
#ifdef DEBUG
		usage += switch_option("debug");
#endif /* DEBUG */
	} else {
#ifdef DEBUG
		usage += switch_option("debug");
#endif /* DEBUG */
	}

	if (usage)
		goto show_usage;

	while (optind <= c-2) {
		char *dir = v[optind++];
		char *map = v[optind++];
		char *opts = "";
		if (v[optind] && *v[optind] == '-')
			opts = &v[optind++][1];

		root_newmap(dir, opts, map);
	}

	if (optind == c) {
#ifdef hpux
		/*
		 * HP-UX can't handle ./mtab
		 * That system is sick - really.
		 */
#ifdef	DEBUG
		debug_option("nomtab");
#endif	/* DEBUG */
#endif	/* hpux */

		/*
		 * Append domain name to hostname.
		 * sub_domain overrides hostdomain
		 * if given.
		 */
		if (sub_domain)
			hostdomain = sub_domain;
		if (*hostdomain == '.')
			hostdomain++;
		strcat(hostd,  ".");
		strcat(hostd, hostdomain);

#ifdef UPDATE_MTAB
#ifdef DEBUG
		if (debug_flags & D_MTAB)
			mtab = DEBUG_MTAB;
		else
#endif /* DEBUG */
		mtab = MOUNTED;
#else
#ifdef DEBUG
		{ if (debug_flags & D_MTAB) {
			dlog("-D mtab option ignored");
		} }
#endif /* DEBUG */
#endif /* UPDATE_MTAB */

		if (switch_to_logfile(logfile) != 0)
			plog(XLOG_USER, "Cannot switch logfile");

		/*
		 * If the kernel architecture was not specified
		 * then use the machine architecture.
		 */
		if (karch == 0)
			karch = arch;

		if (cluster == 0)
			cluster = hostdomain;

		if (afs_timeo <= 0)
			afs_timeo = AFS_TIMEO;
		if (afs_retrans <= 0)
			afs_retrans = AFS_RETRANS;
		if (afs_retrans <= 0)
			afs_retrans = 3;	/* XXX */
		return;
	}

show_usage:
	fprintf(stderr,
"Usage: %s [-mnprv] [-a mnt_point] [-c cache_time] [-d domain]\n\
\t[-k kernel_arch] [-l logfile|\"syslog\"] [-t afs_timeout]\n\
\t[-w wait_timeout] [-C cluster_name]", progname);

#if defined(HAS_HOST) && defined(HOST_EXEC)
	fputs(" [-h host_helper]\n", stderr);
#endif /* defined(HAS_HOST) && defined(HOST_EXEC) */

#ifdef HAS_NIS_MAPS
	fputs(" [-y nis-domain]\n", stderr);
#else
	fputc('\n', stderr);
#endif /* HAS_NIS_MAPS */

	show_opts('x', xlog_opt);
#ifdef DEBUG
	show_opts('D', dbg_opt);
#endif /* DEBUG */
	fprintf(stderr, "\t{directory mapname [-map_options]} ...\n");
	exit(1);
}
E 1
