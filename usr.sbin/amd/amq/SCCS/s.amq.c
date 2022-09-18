h09097
s 00004/00004/00636
d D 8.1 93/06/07 20:16:20 bostic 8 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00636
d R 5.6 93/06/06 12:05:27 bostic 7 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00635
d R 8.1 93/06/06 11:47:20 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00636
d D 5.5 93/06/01 03:15:14 pendry 5 4
c fix compile-time warning
e
s 00017/00010/00619
d D 5.4 92/02/09 08:40:49 pendry 4 3
c merge in new release
e
s 00015/00006/00614
d D 5.3 91/05/12 15:59:36 pendry 3 2
c checkpoint for network tape
e
s 00121/00021/00499
d D 5.2 91/03/17 13:42:14 pendry 2 1
c from amd5.3 alpha11
e
s 00520/00000/00000
d D 5.1 90/06/29 12:10:03 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: amq.c,v 5.2 90/06/23 22:20:07 jsp Rel $
E 2
I 2
D 3
 * $Id: amq.c,v 5.2.1.3 91/03/17 17:33:42 jsp Alpha $
E 2
 *
E 3
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 8
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
I 3
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * $Id: amq.c,v 5.2.1.5 91/05/07 22:18:45 jsp Alpha $
E 4
I 4
 * $Id: amq.c,v 5.2.2.1 1992/02/09 15:09:16 jsp beta $
E 4
 *
E 3
 */

/*
 * Automounter query tool
 */

#ifndef lint
char copyright[] = "\
@(#)Copyright (c) 1990 Jan-Simon Pendry\n\
@(#)Copyright (c) 1990 Imperial College of Science, Technology & Medicine\n\
D 8
@(#)Copyright (c) 1990 The Regents of the University of California.\n\
@(#)All rights reserved.\n";
E 8
I 8
@(#)Copyright (c) 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 8
#endif /* not lint */

#ifndef lint
D 2
static char rcsid[] = "$Id: amq.c,v 5.2 90/06/23 22:20:07 jsp Rel $";
E 2
I 2
D 3
static char rcsid[] = "$Id: amq.c,v 5.2.1.3 91/03/17 17:33:42 jsp Alpha $";
E 3
I 3
D 4
static char rcsid[] = "$Id: amq.c,v 5.2.1.5 91/05/07 22:18:45 jsp Alpha $";
E 4
I 4
static char rcsid[] = "$Id: amq.c,v 5.2.2.1 1992/02/09 15:09:16 jsp beta $";
E 4
E 3
E 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "am.h"
#include "amq.h"
#include <stdio.h>
#include <fcntl.h>
#include <netdb.h>

I 2
static int privsock();

E 2
char *progname;
static int flush_flag;
static int minfo_flag;
static int unmount_flag;
static int stats_flag;
I 2
static int getvers_flag;
E 2
static char *debug_opts;
static char *logfile;
D 2
static char *xlog_opt;
E 2
I 2
static char *mount_map;
static char *xlog_optstr;
E 2
static char localhost[] = "localhost";
static char *def_server = localhost;

extern int optind;
extern char *optarg;

static struct timeval tmo = { 10, 0 };
#define	TIMEOUT tmo

enum show_opt { Full, Stats, Calc, Short, ShowDone };

/*
 * If (e) is Calc then just calculate the sizes
 * Otherwise display the mount node on stdout
 */
static void show_mti(mt, e, mwid, dwid, twid)
amq_mount_tree *mt;
enum show_opt e;
int *mwid;
int *dwid;
int *twid;
{
	switch (e) {
	case Calc: {
		int mw = strlen(mt->mt_mountinfo);
		int dw = strlen(mt->mt_directory);
		int tw = strlen(mt->mt_type);
		if (mw > *mwid) *mwid = mw;
		if (dw > *dwid) *dwid = dw;
		if (tw > *twid) *twid = tw;
	} break;

	case Full: {
D 2
		struct tm *tp = localtime(&mt->mt_mounttime);
E 2
I 2
		struct tm *tp = localtime((time_t *) &mt->mt_mounttime);
E 2
printf("%-*.*s %-*.*s %-*.*s %s\n\t%-5d %-7d %-6d %-7d %-7d %-6d %02d/%02d/%02d %02d:%02d:%02d\n",
			*dwid, *dwid,
			*mt->mt_directory ? mt->mt_directory : "/",	/* XXX */
			*twid, *twid,
			mt->mt_type,
			*mwid, *mwid, 
			mt->mt_mountinfo,
			mt->mt_mountpoint,

			mt->mt_mountuid,
			mt->mt_getattr,
			mt->mt_lookup,
			mt->mt_readdir,
			mt->mt_readlink,
			mt->mt_statfs,

			tp->tm_year > 99 ? tp->tm_year - 100 : tp->tm_year,
			tp->tm_mon+1, tp->tm_mday,
			tp->tm_hour, tp->tm_min, tp->tm_sec);
	} break;

	case Stats: {
D 2
		struct tm *tp = localtime(&mt->mt_mounttime);
E 2
I 2
		struct tm *tp = localtime((time_t *) &mt->mt_mounttime);
E 2
printf("%-*.*s %-5d %-7d %-6d %-7d %-7d %-6d %02d/%02d/%02d %02d:%02d:%02d\n",
			*dwid, *dwid,
			*mt->mt_directory ? mt->mt_directory : "/",	/* XXX */

			mt->mt_mountuid,
			mt->mt_getattr,
			mt->mt_lookup,
			mt->mt_readdir,
			mt->mt_readlink,
			mt->mt_statfs,

			tp->tm_year > 99 ? tp->tm_year - 100 : tp->tm_year,
			tp->tm_mon+1, tp->tm_mday,
			tp->tm_hour, tp->tm_min, tp->tm_sec);
	} break;

	case Short: {
		printf("%-*.*s %-*.*s %-*.*s %s\n",
			*dwid, *dwid,
			*mt->mt_directory ? mt->mt_directory : "/",
			*twid, *twid,
			mt->mt_type,
			*mwid, *mwid,
			mt->mt_mountinfo,
			mt->mt_mountpoint);
	} break;
	}
}

/*
 * Display a mount tree.
 */
static void show_mt(mt, e, mwid, dwid, pwid)
amq_mount_tree *mt;
enum show_opt e;
int *mwid;
int *dwid;
int *pwid;
{
	while (mt) {
		show_mti(mt, e, mwid, dwid, pwid);
		show_mt(mt->mt_next, e, mwid, dwid, pwid);
		mt = mt->mt_child;
	}
}

static void show_mi(ml, e, mwid, dwid, twid)
amq_mount_info_list *ml;
enum show_opt e;
int *mwid;
int *dwid;
int *twid;
{
	int i;
	switch (e) {
	case Calc: {
		for (i = 0; i < ml->amq_mount_info_list_len; i++) {
			amq_mount_info *mi = &ml->amq_mount_info_list_val[i];
			int mw = strlen(mi->mi_mountinfo);
			int dw = strlen(mi->mi_mountpt);
			int tw = strlen(mi->mi_type);
			if (mw > *mwid) *mwid = mw;
			if (dw > *dwid) *dwid = dw;
			if (tw > *twid) *twid = tw;
		}
	} break;

	case Full: {
		for (i = 0; i < ml->amq_mount_info_list_len; i++) {
			amq_mount_info *mi = &ml->amq_mount_info_list_val[i];
			printf("%-*.*s %-*.*s %-*.*s %-3d %s is %s",
						*mwid, *mwid, mi->mi_mountinfo,
						*dwid, *dwid, mi->mi_mountpt,
						*twid, *twid, mi->mi_type,
						mi->mi_refc, mi->mi_fserver,
						mi->mi_up > 0 ? "up" :
						mi->mi_up < 0 ? "starting" : "down");
			if (mi->mi_error > 0) {
I 5
#ifdef HAS_STRERROR
				printf(" (%s)", strerror(mi->mi_error));
#else
E 5
				extern char *sys_errlist[];
				extern int sys_nerr;
				if (mi->mi_error < sys_nerr)
					printf(" (%s)", sys_errlist[mi->mi_error]);
				else
					printf(" (Error %d)", mi->mi_error);
I 5
#endif
E 5
			} else if (mi->mi_error < 0) {
				fputs(" (in progress)", stdout);
			}
			fputc('\n', stdout);
		}
	} break;
	}
}

/*
 * Display general mount statistics
 */
static void show_ms(ms)
amq_mount_stats *ms;
{
	printf("\
requests  stale     mount     mount     unmount\n\
deferred  fhandles  ok        failed    failed\n\
%-9d %-9d %-9d %-9d %-9d\n",
	ms->as_drops, ms->as_stale, ms->as_mok, ms->as_merr, ms->as_uerr);
}

static bool_t
xdr_pri_free(xdr_args, args_ptr)
xdrproc_t xdr_args;
caddr_t args_ptr;
{
	XDR xdr;
	xdr.x_op = XDR_FREE;
	return ((*xdr_args)(&xdr, args_ptr));
}

#ifdef hpux
#include <cluster.h>
static char *cluster_server()
{
	struct cct_entry *cp;

	if (cnodeid() == 0) {
		/*
		 * Not clustered
		 */
		return def_server;
	}

	while (cp = getccent())
		if (cp->cnode_type == 'r')
			return cp->cnode_name;


	return def_server;
}
#endif /* hpux */

/*
 * MAIN
 */
main(argc, argv)
int argc;
char *argv[];
{
	int opt_ch;
	int errs = 0;
	char *server;
	struct sockaddr_in server_addr;
D 2
	int s = RPC_ANYSOCK;
E 2
I 2

	/* In order to pass the Amd security check, we must use a priv port. */
	int s;

E 2
	CLIENT *clnt;
	struct hostent *hp;
	int nodefault = 0;

	/*
	 * Compute program name
	 */
	if (argv[0]) {
		progname = strrchr(argv[0], '/');
		if (progname && progname[1])
			progname++;
		else
			progname = argv[0];
	}
	if (!progname)
		progname = "amq";

	/*
	 * Parse arguments
	 */
D 2
	while ((opt_ch = getopt(argc, argv, "fh:l:msux:D:")) != EOF)
E 2
I 2
	while ((opt_ch = getopt(argc, argv, "fh:l:msuvx:D:M:")) != EOF)
E 2
	switch (opt_ch) {
	case 'f':
		flush_flag = 1;
I 2
		nodefault = 1;
E 2
		break;

	case 'h':
		def_server = optarg;
		break;

	case 'l':
		logfile = optarg;
		nodefault = 1;
		break;

	case 'm':
		minfo_flag = 1;
		nodefault = 1;
		break;

	case 's':
		stats_flag = 1;
I 2
		nodefault = 1;
E 2
		break;

	case 'u':
		unmount_flag = 1;
I 2
		nodefault = 1;
E 2
		break;

I 2
	case 'v':
		getvers_flag = 1;
		nodefault = 1;
		break;

E 2
	case 'x':
D 2
		xlog_opt = optarg;
E 2
I 2
		xlog_optstr = optarg;
E 2
		nodefault = 1;
		break;

	case 'D':
		debug_opts = optarg;
		nodefault = 1;
		break;

I 2
	case 'M':
		mount_map = optarg;
		nodefault = 1;
		break;

E 2
	default:
		errs = 1;
		break;
	}

I 2
	if (optind == argc) {
		if (unmount_flag)
			errs = 1;
	}
	
E 2
	if (errs) {
show_usage:
		fprintf(stderr, "\
D 2
Usage: %s [-h host] [[-f] [-m] | | [-s] | [[-u] directory ...]] |\n\
\t[-l logfile|\"syslog\"] [-x log_flags] [-D dbg_opts]\n", progname);
E 2
I 2
Usage: %s [-h host] [[-f] [-m] [-v] [-s]] | [[-u] directory ...]] |\n\
\t[-l logfile|\"syslog\"] [-x log_flags] [-D dbg_opts] [-M mapent]\n", progname);
E 2
		exit(1);
	}

#ifdef hpux
	/*
	 * Figure out root server of cluster
	 */
	if (def_server == localhost)
		server = cluster_server();
	else
#endif /* hpux */
	server = def_server;

	/*
	 * Get address of server
	 */
D 3
	if ((hp = gethostbyname(server)) == 0) {
E 3
I 3
	if ((hp = gethostbyname(server)) == 0 && strcmp(server, localhost) != 0) {
E 3
		fprintf(stderr, "%s: Can't get address of %s\n", progname, server);
		exit(1);
	}
	bzero(&server_addr, sizeof server_addr);
	server_addr.sin_family = AF_INET;
D 2
	server_addr.sin_addr = *(struct in_addr *) hp->h_addr;
E 2
I 2
D 3
	bcopy((voidp) hp->h_addr, (voidp) &server_addr.sin_addr, sizeof(server_addr.sin_addr));
E 3
I 3
	if (hp) {
		bcopy((voidp) hp->h_addr, (voidp) &server_addr.sin_addr,
			sizeof(server_addr.sin_addr));
	} else {
		/* fake "localhost" */
		server_addr.sin_addr.s_addr = htonl(0x7f000001);
	}
E 3
E 2

	/*
	 * Create RPC endpoint
	 */
I 2
D 4
	s = privsock();
E 2
	clnt = clntudp_create(&server_addr, AMQ_PROGRAM, AMQ_VERSION, TIMEOUT, &s);
E 4
I 4
	s = privsock(SOCK_STREAM);
	clnt = clnttcp_create(&server_addr, AMQ_PROGRAM, AMQ_VERSION, &s, 0, 0);
E 4
	if (clnt == 0) {
I 4
		close(s);
		s = privsock(SOCK_DGRAM);
		clnt = clntudp_create(&server_addr, AMQ_PROGRAM, AMQ_VERSION, TIMEOUT, &s);
	}
	if (clnt == 0) {
E 4
		fprintf(stderr, "%s: ", progname);
		clnt_pcreateerror(server);
		exit(1);
	}

	/*
	 * Control debugging
	 */
	if (debug_opts) {
		int *rc;
		amq_setopt opt;
		opt.as_opt = AMOPT_DEBUG;
		opt.as_str = debug_opts;
		rc = amqproc_setopt_1(&opt, clnt);
		if (rc && *rc < 0) {
			fprintf(stderr, "%s: daemon not compiled for debug", progname);
			errs = 1;
		} else if (!rc || *rc > 0) {
			fprintf(stderr, "%s: debug setting for \"%s\" failed\n", progname, debug_opts);
			errs = 1;
		}
	}

	/*
	 * Control logging
	 */
D 2
	if (xlog_opt) {
E 2
I 2
	if (xlog_optstr) {
E 2
		int *rc;
		amq_setopt opt;
		opt.as_opt = AMOPT_XLOG;
D 2
		opt.as_str = xlog_opt;
E 2
I 2
		opt.as_str = xlog_optstr;
E 2
		rc = amqproc_setopt_1(&opt, clnt);
		if (!rc || *rc) {
D 2
			fprintf(stderr, "%s: setting log level to \"%s\" failed\n", progname, xlog_opt);
E 2
I 2
			fprintf(stderr, "%s: setting log level to \"%s\" failed\n", progname, xlog_optstr);
E 2
			errs = 1;
		}
	}

	/*
	 * Control log file
	 */
	if (logfile) {
		int *rc;
		amq_setopt opt;
		opt.as_opt = AMOPT_LOGFILE;
		opt.as_str = logfile;
		rc = amqproc_setopt_1(&opt, clnt);
		if (!rc || *rc) {
			fprintf(stderr, "%s: setting logfile to \"%s\" failed\n", progname, logfile);
			errs = 1;
		}
	}

	/*
	 * Flush map cache
	 */
D 2
	if (logfile) {
E 2
I 2
	if (flush_flag) {
E 2
		int *rc;
		amq_setopt opt;
		opt.as_opt = AMOPT_FLUSHMAPC;
		opt.as_str = "";
		rc = amqproc_setopt_1(&opt, clnt);
		if (!rc || *rc) {
			fprintf(stderr, "%s: amd on %s cannot flush the map cache\n", progname, server);
			errs = 1;
		}
	}

	/*
	 * Mount info
	 */
	if (minfo_flag) {
		int dummy;
		amq_mount_info_list *ml = amqproc_getmntfs_1(&dummy, clnt);
		if (ml) {
			int mwid = 0, dwid = 0, twid = 0;
			show_mi(ml, Calc, &mwid, &dwid, &twid);
			mwid++; dwid++; twid++;
			show_mi(ml, Full, &mwid, &dwid, &twid);

		} else {
			fprintf(stderr, "%s: amd on %s cannot provide mount info\n", progname, server);
		}
	}

	/*
I 2
	 * Mount map
	 */
	if (mount_map) {
		int *rc;
		do {
			rc = amqproc_mount_1(&mount_map, clnt);
		} while (rc && *rc < 0);
		if (!rc || *rc > 0) {
			if (rc)
				errno = *rc;
			else
				errno = ETIMEDOUT;
			fprintf(stderr, "%s: could not start new ", progname);
			perror("autmount point");
		}
	}

	/*
	 * Get Version
	 */
	if (getvers_flag) {
		amq_string *spp = amqproc_getvers_1((voidp) 0, clnt);
		if (spp && *spp) {
			printf("%s.\n", *spp);
			free(*spp);
		} else {
D 3
			fprintf(stderr, "%s: failed to get version infromation\n", progname);
E 3
I 3
			fprintf(stderr, "%s: failed to get version information\n", progname);
E 3
			errs = 1;
		}
	}

	/*
E 2
	 * Apply required operation to all remaining arguments
	 */
	if (optind < argc) {
		do {
			char *fs = argv[optind++];
			if (unmount_flag) {
				/*
				 * Unmount request
				 */
				amqproc_umnt_1(&fs, clnt);
			} else {
				/*
				 * Stats request
				 */
				amq_mount_tree_p *mtp = amqproc_mnttree_1(&fs, clnt);
				if (mtp) {
					amq_mount_tree *mt = *mtp;
					if (mt) {
						int mwid = 0, dwid = 0, twid = 0;
						show_mt(mt, Calc, &mwid, &dwid, &twid);
						mwid++; dwid++, twid++;
D 2
#ifdef notdef
		printf("\t%s\n%-*.*s %-*.*s %-*.*s %s\n",
		"Uid   Getattr Lookup RdDir   RdLnk   Statfs Mounted@",
		      dwid, dwid, "What", twid, twid, "Type", mwid, mwid, "Info", "Where");
						show_mt(mt, Full, &mwid, &dwid, &twid);
#endif /* notdef */
E 2
		printf("%-*.*s Uid   Getattr Lookup RdDir   RdLnk   Statfs Mounted@\n",
			dwid, dwid, "What");
						show_mt(mt, Stats, &mwid, &dwid, &twid);
					} else {
						fprintf(stderr, "%s: %s not automounted\n", progname, fs);
					}
					xdr_pri_free(xdr_amq_mount_tree_p, (caddr_t) mtp);
				} else {
					fprintf(stderr, "%s: ", progname);
					clnt_perror(clnt, server);
					errs = 1;
				}
			}
		} while (optind < argc);
	} else if (unmount_flag) {
		goto show_usage;
	} else if (stats_flag) {
		amq_mount_stats *ms = amqproc_stats_1((voidp) 0, clnt);
		if (ms) {
			show_ms(ms);
		} else {
			fprintf(stderr, "%s: ", progname);
			clnt_perror(clnt, server);
			errs = 1;
		}
	} else if (!nodefault) {
		amq_mount_tree_list *mlp = amqproc_export_1((voidp) 0, clnt);
		if (mlp) {
			enum show_opt e = Calc;
			int mwid = 0, dwid = 0, pwid = 0;
			while (e != ShowDone) {
				int i;
				for (i = 0; i < mlp->amq_mount_tree_list_len; i++) {
					show_mt(mlp->amq_mount_tree_list_val[i],
						 e, &mwid, &dwid, &pwid);
				}
				mwid++; dwid++, pwid++;
				if (e == Calc) e = Short;
				else if (e == Short) e = ShowDone;
			}
		} else {
			fprintf(stderr, "%s: ", progname);
			clnt_perror(clnt, server);
			errs = 1;
		}
	}

	exit(errs);
I 2
}

/*
 * udpresport creates a datagram socket and attempts to bind it to a 
 * secure port.
 * returns: The bound socket, or -1 to indicate an error.
 */
D 4
static int udpresport()
E 4
I 4
static int inetresport(ty)
int ty;
E 4
{
	int alport;
	struct sockaddr_in addr;
	int sock;

	/* Use internet address family */
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
D 4
	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
E 4
I 4
	if ((sock = socket(AF_INET, ty, 0)) < 0)
E 4
		return -1;
	for (alport = IPPORT_RESERVED-1; alport > IPPORT_RESERVED/2 + 1; alport--) {
		addr.sin_port = htons((u_short)alport);
		if (bind(sock, (struct sockaddr *)&addr, sizeof (addr)) >= 0)
			return sock;
		if (errno != EADDRINUSE) {
			close(sock);
			return -1;
		}
	}
	close(sock);
	errno = EAGAIN;
	return -1;
}

/*
D 4
 * Privsock() calls udpresport() to attempt to bind a socket to a secure
 * port.  If udpresport() fails, privsock returns a magic socket number which
E 4
I 4
 * Privsock() calls inetresport() to attempt to bind a socket to a secure
 * port.  If inetresport() fails, privsock returns a magic socket number which
E 4
 * indicates to RPC that it should make its own socket.
 * returns: A privileged socket # or RPC_ANYSOCK.
 */
D 4
static int privsock()
E 4
I 4
static int privsock(ty)
int ty;
E 4
{
D 4
	int sock = udpresport();
E 4
I 4
	int sock = inetresport(ty);
E 4

	if (sock < 0) {
		errno = 0;
		/* Couldn't get a secure port, let RPC make an insecure one */
		sock = RPC_ANYSOCK;
	}
	return sock;
E 2
}

#ifdef DEBUG
xfree(f, l, p)
char *f, *l;
voidp p;
{
	free(p);
}
#endif /* DEBUG */
E 1
