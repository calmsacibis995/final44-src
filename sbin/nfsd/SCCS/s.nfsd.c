h54824
s 00003/00002/00615
d R 8.10 95/04/28 14:47:40 bostic 24 22
c nfsd(8) wasn't dealing with the death of a child correctly.
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00004/00001/00616
d R 8.10 95/04/28 14:44:49 bostic 23 22
c nfsd(8) wasn't dealing with the death of a child correctly.
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00079/00025/00538
d D 8.9 95/03/29 22:12:56 mckusick 22 21
c update for version 3 from Rick Macklem
e
s 00001/00001/00562
d D 8.8 95/02/14 12:09:14 mckusick 21 20
c Use nulls to pad proctitle rather than spaces...makes ps(1) 
c output more readable (from David Greenman <davidg@Root.COM>)
e
s 00002/00002/00561
d D 8.7 94/02/22 15:41:22 bostic 20 19
c don't set SIGSYS if debugging
e
s 00002/00002/00561
d D 8.6 94/02/22 15:37:14 bostic 19 18
c forgot to change the argument parsing for -n
e
s 00009/00000/00554
d D 8.5 94/02/22 14:56:33 bostic 18 17
c don't drop core if NFS isn't compiled into the kernel
e
s 00023/00009/00531
d D 8.4 94/02/22 14:44:24 bostic 17 16
c replace trailing number with -n plus argument
e
s 00002/00002/00538
d D 8.3 94/02/22 14:12:56 bostic 16 15
c get the usage statement right
e
s 00214/00184/00326
d D 8.2 94/02/22 14:11:49 bostic 15 14
c major cleanup, make it pass lint so I can leave the include files
c the way I want to, KNF, reasonable error messages
e
s 00005/00005/00505
d D 8.1 93/06/05 11:07:42 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00509
d D 5.13 93/02/03 10:48:47 mckusick 13 12
c cleanup from Rick Macklem
e
s 00003/00001/00507
d D 5.12 92/12/10 23:42:42 mckusick 12 11
c have to zero out unused part of address on return from accept
e
s 00337/00165/00171
d D 5.11 92/02/15 17:11:31 mckusick 11 10
c update from Rick Maclem for leases
e
s 00101/00027/00235
d D 5.10 91/04/24 15:19:38 karels 10 9
c add -r to re-register with portmap; setproctitle to mark daemons
c as to client for tcp; still needs more work
e
s 00002/00002/00260
d D 5.9 90/09/26 09:43:00 mckusick 9 8
c exit needs status
e
s 00001/00019/00261
d D 5.8 90/06/29 20:03:12 karels 8 7
c use daemon() call
e
s 00002/00001/00278
d D 5.7 90/06/19 19:25:08 mckusick 7 6
c make connection reset a notice, not an error
e
s 00001/00011/00278
d D 5.6 90/06/01 16:18:52 bostic 6 5
c new copyright notice
e
s 00005/00005/00284
d D 5.5 90/05/15 19:51:42 bostic 5 4
c string.h is ANSI C include file
e
s 00193/00039/00096
d D 5.4 90/05/14 15:27:14 mckusick 4 3
c update to add TCP support from Rick Macklem
e
s 00000/00003/00135
d D 5.3 90/05/04 22:42:50 mckusick 3 2
c delete unneeded headers
e
s 00019/00005/00119
d D 5.2 90/01/04 15:08:57 mckusick 2 1
c update from Rick Macklem
e
s 00124/00000/00000
d D 5.1 89/07/16 17:36:17 mckusick 1 0
c original code from Rick Macklem
e
u
U
t
T
I 1
/*
D 14
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
D 15
 * Copyright (c) 1989, 1993
E 15
I 15
 * Copyright (c) 1989, 1993, 1994
E 15
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 6
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
 */

#ifndef lint
D 14
char copyright[] =
"%Z% Copyright (c) 1989 Regents of the University of California.\n\
 All rights reserved.\n";
E 14
I 14
static char copyright[] =
D 15
"%Z% Copyright (c) 1989, 1993\n\
E 15
I 15
"%Z% Copyright (c) 1989, 1993, 1994\n\
E 15
	The Regents of the University of California.  All rights reserved.\n";
E 14
#endif not lint

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint

I 11
D 15
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <strings.h>
#include <pwd.h>
#include <grp.h>
E 11
D 5
#include <stdio.h>
#include <syslog.h>
#include <signal.h>
#include <fcntl.h>
I 4
#include <strings.h>
E 5
E 4
#include <sys/types.h>
I 5
D 11
#include <sys/signal.h>
E 11
I 11
#include <sys/syslog.h>
E 15
#include <sys/param.h>
D 15
#include <sys/errno.h>
E 15
I 15
#include <sys/syslog.h>
E 15
E 11
E 5
#include <sys/ioctl.h>
#include <sys/stat.h>
I 4
#include <sys/wait.h>
I 11
#include <sys/uio.h>
D 15
#include <sys/namei.h>
E 15
#include <sys/ucred.h>
E 11
E 4
D 3
#include <sys/dir.h>
#include <sys/uio.h>
#include <sys/namei.h>
E 3
#include <sys/mount.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
I 15

E 15
I 5
D 11
#include <stdio.h>
#include <syslog.h>
#include <fcntl.h>
#include <string.h>
E 5
#include <netdb.h>
E 11
#include <rpc/rpc.h>
#include <rpc/pmap_clnt.h>
#include <rpc/pmap_prot.h>
I 15

E 15
I 11
#ifdef ISO
#include <netiso/iso.h>
#endif
E 11
#include <nfs/rpcv2.h>
D 22
#include <nfs/nfsv2.h>
E 22
I 22
#include <nfs/nfsproto.h>
E 22
I 11
#include <nfs/nfs.h>
I 15

E 15
D 22
#ifdef KERBEROS
E 22
I 22
#ifdef NFSKERB
E 22
I 13
#include <kerberosIV/des.h>
E 13
#include <kerberosIV/krb.h>
#endif
E 11

I 15
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

E 15
/* Global defs */
#ifdef DEBUG
#define	syslog(e, s)	fprintf(stderr,(s))
D 10
int debug = 1;
E 10
I 10
int	debug = 1;
E 10
#else
D 10
int debug = 0;
E 10
I 10
int	debug = 0;
E 10
#endif
I 15

E 15
I 4
D 11
struct hadr {
	u_long	ha_sad;
	struct hadr *ha_next;
};
D 10
struct hadr hphead;
E 10
I 10
struct	hadr hphead;
E 11
I 11
struct	nfsd_srvargs nsd;
D 15
extern	int errno;
E 15
E 11
char	**Argv = NULL;		/* pointer to argument vector */
char	*LastArg = NULL;	/* end of argv */
D 15
void	reapchild();
E 15
E 10
E 4

I 11
D 22
#ifdef KERBEROS
E 22
I 22
#ifdef NFSKERB
E 22
char		lnam[ANAME_SZ];
KTEXT_ST	kt;
D 22
AUTH_DAT	auth;
E 22
I 22
AUTH_DAT	kauth;
E 22
char		inst[INST_SZ];
I 22
struct nfsrpc_fullblock kin, kout;
struct nfsrpc_fullverf kverf;
NFSKERBKEY_T	kivec;
struct timeval	ktv;
NFSKERBKEYSCHED_T kerb_keysched;
E 22
D 15
#endif /* KERBEROS */
E 15
I 15
#endif
E 15

I 18
void	nonfs __P((int));
E 18
I 15
void	reapchild __P((int));
void	setproctitle __P((char *));
void	usage __P((void));

E 15
E 11
/*
 * Nfs server daemon mostly just a user context for nfssvc()
I 15
 *
E 15
 * 1 - do file descriptor and signal cleanup
D 11
 * 2 - create server socket
 * 3 - register socket with portmap
D 4
 * 4 - nfssvc(sock)
E 4
I 4
 * For SOCK_DGRAM, just fork children and send them into the kernel
 * by calling nfssvc()
E 11
I 11
 * 2 - fork the nfsd(s)
 * 3 - create server socket(s)
 * 4 - register socket with portmap
I 15
 *
E 15
 * For connectionless protocols, just pass the socket into the kernel via.
 * nfssvc().
E 11
D 15
 * For connection based sockets, loop doing accepts. When you get a new socket
D 11
 * from accept, fork a child that drops into the kernel via. nfssvc.
 * This child will return from nfssvc when the connection is closed, so
 * just shutdown() and exit().
E 11
I 11
 * from accept, pass the msgsock into the kernel via. nfssvc().
E 15
I 15
 * For connection based sockets, loop doing accepts. When you get a new
 * socket from accept, pass the msgsock into the kernel via. nfssvc().
E 15
E 11
 * The arguments are:
D 11
 * -t - support tcp nfs clients
E 11
D 15
 * -u - support udp nfs clients
I 11
 * -t - support tcp nfs clients
 * -c - support iso cltp clients
 * -r - reregister with portmapper
E 15
I 15
 *	-c - support iso cltp clients
 *	-r - reregister with portmapper
 *	-t - support tcp nfs clients
 *	-u - support udp nfs clients
E 15
 * followed by "n" which is the number of nfsds' to fork off
E 11
E 4
 */
I 15
int
E 15
D 10
main(argc, argv)
E 10
I 10
main(argc, argv, envp)
E 10
	int argc;
D 4
	char *argv[];
E 4
I 4
D 10
	char **argv;
E 10
I 10
	char *argv[], *envp[];
E 10
E 4
{
D 15
	register int i;
D 4
	int cnt, sock;
	struct sockaddr_in saddr;
I 2
	u_long msk, mtch;
E 4
I 4
D 11
	register char *cp, *cp2;
	register struct hadr *hp;
	int udpcnt, sock, msgsock, tcpflag = 0, udpflag = 0, ret, len;
I 10
	int reregister = 0;
E 10
	char opt;
E 11
I 11
	register char *cp, **cpp;
	register struct ucred *cr = &nsd.nsd_cr;
	struct passwd *pwd;
E 15
I 15
	extern int optind;
E 15
	struct group *grp;
D 15
	int sock, msgsock, tcpflag = 0, udpflag = 0, ret, len;
	int cltpflag = 0, tp4flag = 0, tpipflag = 0, connect_type_cnt = 0;
	int maxsock, tcpsock, tp4sock, tpipsock, nfsdcnt = 4;
	int nfssvc_flag, opt, on = 1, reregister = 0;
E 15
I 15
	struct nfsd_args nfsdargs;
	struct passwd *pwd;
	struct ucred *cr;
E 15
	struct sockaddr_in inetaddr, inetpeer;
#ifdef ISO
	struct sockaddr_iso isoaddr, isopeer;
#endif
I 22
	struct timeval ktv;
E 22
D 15
	struct nfsd_args nfsdargs;
E 15
	fd_set ready, sockbits;
E 11
D 10
	union wait chldstat;
E 10
D 15
	extern int optind;
	extern char *optarg;
E 15
I 15
	int ch, cltpflag, connect_type_cnt, i, len, maxsock, msgsock;
	int nfsdcnt, nfssvc_flag, on, reregister, sock, tcpflag, tcpsock;
	int tp4cnt, tp4flag, tp4sock, tpipcnt, tpipflag, tpipsock, udpflag;
	char *cp, **cpp;
E 15
D 11
	struct sockaddr_in saddr, msk, mtch, peername;
E 11
E 4
E 2

I 4
D 10
	while ((opt = getopt(argc, argv, "t:u:")) != EOF)
E 10
I 10
D 11

E 11
D 15
	/*
	 *  Save start and extent of argv for setproctitle.
	 */
E 15
I 15
	/* Save start and extent of argv for setproctitle. */
E 15
D 11

E 11
	Argv = argv;
	if (envp == 0 || *envp == 0)
		envp = argv;
	while (*envp)
		envp++;
	LastArg = envp[-1] + strlen(envp[-1]);
D 11
	while ((opt = getopt(argc, argv, "rt:u:")) != EOF)
E 11
I 11
D 15
	while ((opt = getopt(argc, argv, "utcr")) != EOF)
E 11
E 10
		switch (opt) {
I 10
D 11
		case 'r':
			reregister++;
E 11
I 11
		case 'u':
			udpflag++;
E 15
I 15

D 17
	nfsdcnt = 4;
E 17
I 17
#define	MAXNFSDCNT	20
#define	DEFNFSDCNT	 4
	nfsdcnt = DEFNFSDCNT;
E 17
	cltpflag = reregister = tcpflag = tp4cnt = tp4flag = tpipcnt = 0;
	tpipflag = udpflag = 0;
#ifdef ISO
D 16
#define	FLAGS	"crtu"
E 16
I 16
D 17
#define	FLAGS	"-crtu"
E 17
I 17
#define	GETOPT	"cn:rtu"
#define	USAGE	"[-crtu] [-n num_servers]"
E 17
E 16
#else
D 16
#define	FLAGS	"rtu"
E 16
I 16
D 17
#define	FLAGS	"-rtu"
E 17
I 17
#define	GETOPT	"n:rtu"
#define	USAGE	"[-rtu] [-n num_servers]"
E 17
E 16
#endif
D 17
	while ((ch = getopt(argc, argv, &FLAGS[1])) != EOF)
E 17
I 17
	while ((ch = getopt(argc, argv, GETOPT)) != EOF)
E 17
		switch (ch) {
I 17
		case 'n':
D 19
			nfsdcnt = atoi(argv[optind]);
E 19
I 19
			nfsdcnt = atoi(optarg);
E 19
			if (nfsdcnt < 1 || nfsdcnt > MAXNFSDCNT) {
				warnx("nfsd count %d; reset to %d", DEFNFSDCNT);
				nfsdcnt = DEFNFSDCNT;
			}
			break;
E 17
		case 'r':
			reregister = 1;
E 15
E 11
			break;
E 10
		case 't':
D 15
			tcpflag++;
E 15
I 15
			tcpflag = 1;
E 15
D 11
			if (cp = index(optarg, ',')) {
				*cp++ = '\0';
				msk.sin_addr.s_addr = inet_addr(optarg);
				if (msk.sin_addr.s_addr == -1)
					usage();
				if (cp2 = index(cp, ','))
					*cp2++ = '\0';
				mtch.sin_addr.s_addr = inet_addr(cp);
				if (mtch.sin_addr.s_addr == -1)
					usage();
				cp = cp2;
				hphead.ha_next = (struct hadr *)0;
				while (cp) {
					if (cp2 = index(cp, ','))
						*cp2++ = '\0';
					hp = (struct hadr *)
						malloc(sizeof (struct hadr));
					hp->ha_sad = inet_addr(cp);
					if (hp->ha_sad == -1)
						usage();
					hp->ha_next = hphead.ha_next;
					hphead.ha_next = hp;
					cp = cp2;
				}
			} else
				usage();
E 11
			break;
D 11
		case 'u':
			udpflag++;
			if (cp = index(optarg, ',')) {
				*cp++ = '\0';
				msk.sin_addr.s_addr = inet_addr(optarg);
				if (msk.sin_addr.s_addr == -1)
					usage();
				if (cp2 = index(cp, ','))
					*cp2++ = '\0';
				mtch.sin_addr.s_addr = inet_addr(cp);
				if (mtch.sin_addr.s_addr == -1)
					usage();
				if (cp2)
					udpcnt = atoi(cp2);
				if (udpcnt < 1 || udpcnt > 20)
					udpcnt = 1;
			} else
				usage();
E 11
I 11
D 15
		case 'r':
			reregister++;
E 15
I 15
		case 'u':
			udpflag = 1;
E 15
E 11
			break;
I 11
#ifdef ISO
		case 'c':
D 15
			cltpflag++;
E 15
I 15
			cltpflag = 1;
E 15
			break;
#ifdef notyet
		case 'i':
D 15
			tp4cnt++;
E 15
I 15
			tp4cnt = 1;
E 15
			break;
		case 'p':
D 15
			tpipcnt++;
E 15
I 15
			tpipcnt = 1;
E 15
			break;
#endif /* notyet */
D 15
#endif	/* ISO */
E 15
I 15
#endif /* ISO */
E 15
E 11
		default:
		case '?':
			usage();
D 10
		};
	if (optind == 1) {
E 10
I 10
D 11
		}
E 11
I 11
		};
D 15
	if (optind < argc)
E 15
I 15
	argv += optind;
	argc -= optind;

D 17
	/* Trailing number is the count of daemons. */
E 17
I 17
	/*
	 * XXX
	 * Backward compatibility, trailing number is the count of daemons.
	 */
E 17
	if (argc > 1)
		usage();
	if (argc == 1) {
E 15
D 19
		nfsdcnt = atoi(argv[optind]);
E 19
I 19
		nfsdcnt = atoi(argv[0]);
E 19
D 15
	if (nfsdcnt < 1 || nfsdcnt > 20)
		nfsdcnt = 4;
E 15
I 15
D 17
		if (nfsdcnt < 1 || nfsdcnt > 20) {
			warnx("nfsd count %d; reset to 4", nfsdcnt);
			nfsdcnt = 4;
E 17
I 17
		if (nfsdcnt < 1 || nfsdcnt > MAXNFSDCNT) {
			warnx("nfsd count %d; reset to %d", DEFNFSDCNT);
			nfsdcnt = DEFNFSDCNT;
E 17
		}
	}
E 15
E 11

D 11
	/*
	 * Default, if neither UDP nor TCP is specified,
	 * is to support UDP only; a numeric argument indicates
	 * the number of server daemons to run.
	 */
	if (udpflag == 0 && tcpflag == 0) {
E 10
		if (argc > 1)
			udpcnt = atoi(*++argv);
		if (udpcnt < 1 || udpcnt > 20)
			udpcnt = 1;
		msk.sin_addr.s_addr = mtch.sin_addr.s_addr = 0;
		udpflag++;
	}
I 10

E 11
E 10
E 4
	if (debug == 0) {
D 8
		if (fork())
			exit(0);
		{ int s;
		for (s = 0; s < 10; s++)
			(void) close(s);
		}
D 2
		(void) open("/", O_RDONLY);
		(void) dup2(0, 1);
		(void) dup2(0, 2);
E 2
I 2
		(void) open("/dev/null", O_RDONLY);
		(void) open("/dev/null", O_WRONLY);
		(void) dup2(1, 2);
E 2
		{ int tt = open("/dev/tty", O_RDWR);
		  if (tt > 0) {
			ioctl(tt, TIOCNOTTY, (char *)0);
			close(tt);
		  }
		}
		(void) setpgrp(0, 0);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
E 8
I 8
		daemon(0, 0);
I 20
		(void)signal(SIGHUP, SIG_IGN);
E 20
E 8
D 15
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
		signal(SIGHUP, SIG_IGN);
E 15
I 15
		(void)signal(SIGINT, SIG_IGN);
		(void)signal(SIGQUIT, SIG_IGN);
I 20
		(void)signal(SIGSYS, nonfs);
E 20
		(void)signal(SIGTERM, SIG_IGN);
D 20
		(void)signal(SIGHUP, SIG_IGN);
E 20
E 15
	}
I 18
D 20
	(void)signal(SIGSYS, nonfs);
E 20
E 18
I 10
D 15
	signal(SIGCHLD, reapchild);
E 15
I 15
	(void)signal(SIGCHLD, reapchild);
E 15

	if (reregister) {
D 15
		if (udpflag && !pmap_set(RPCPROG_NFS, NFS_VER2, IPPROTO_UDP,
		    NFS_PORT)) {
			fprintf(stderr,
			    "Can't register with portmap for UDP\n");
			exit(1);
		}
		if (tcpflag && !pmap_set(RPCPROG_NFS, NFS_VER2, IPPROTO_TCP,
		    NFS_PORT)) {
			fprintf(stderr,
			    "Can't register with portmap for TCP\n");
			exit(1);
		}
E 15
I 15
		if (udpflag &&
D 22
		    !pmap_set(RPCPROG_NFS, NFS_VER2, IPPROTO_UDP, NFS_PORT))
E 22
I 22
		    (!pmap_set(RPCPROG_NFS, 2, IPPROTO_UDP, NFS_PORT) ||
		     !pmap_set(RPCPROG_NFS, 3, IPPROTO_UDP, NFS_PORT)))
E 22
			err(1, "can't register with portmap for UDP.");
		if (tcpflag &&
D 22
		    !pmap_set(RPCPROG_NFS, NFS_VER2, IPPROTO_TCP, NFS_PORT))
E 22
I 22
		    (!pmap_set(RPCPROG_NFS, 2, IPPROTO_TCP, NFS_PORT) ||
		     !pmap_set(RPCPROG_NFS, 3, IPPROTO_TCP, NFS_PORT)))
E 22
			err(1, "can't register with portmap for TCP.");
E 15
		exit(0);
	}
E 10
	openlog("nfsd:", LOG_PID, LOG_DAEMON);
I 10
D 11
#ifdef notdef
	/* why? unregisters both protocols even if we restart only one */
E 10
D 4
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		syslog(LOG_ERR, "Can't create socket");
		exit(1);
	}
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = INADDR_ANY;
	saddr.sin_port = htons(NFS_PORT);
	if (bind(sock, &saddr, sizeof(saddr)) < 0) {
		syslog(LOG_ERR, "Can't bind addr");
		exit(1);
	}
E 4
	pmap_unset(RPCPROG_NFS, NFS_VER2);
E 11
I 11

D 15
	for (i = 0; i < nfsdcnt; i++)
	    if (fork() == 0) {
E 15
I 15
	for (i = 0; i < nfsdcnt; i++) {
		switch (fork()) {
		case -1:
			syslog(LOG_ERR, "fork: %m");
			exit (1);
		case 0:
			break;
		default:
			continue;
		}

E 15
D 22
		setproctitle("nfsd-srv");
E 22
I 22
		setproctitle("server");
E 22
		nfssvc_flag = NFSSVC_NFSD;
D 15
		nsd.nsd_nfsd = (struct nfsd *)0;
E 15
I 15
		nsd.nsd_nfsd = NULL;
E 15
D 22
#ifdef KERBEROS
		nsd.nsd_authstr = (char *)kt.dat;
E 22
I 22
#ifdef NFSKERB
		if (sizeof (struct nfsrpc_fullverf) != RPCX_FULLVERF ||
		    sizeof (struct nfsrpc_fullblock) != RPCX_FULLBLOCK)
		    syslog(LOG_ERR, "Yikes NFSKERB structs not packed!");
		nsd.nsd_authstr = (u_char *)&kt;
		nsd.nsd_authlen = sizeof (kt);
		nsd.nsd_verfstr = (u_char *)&kverf;
		nsd.nsd_verflen = sizeof (kverf);
E 22
E 11
I 10
#endif
I 11
D 15
		while (nfssvc(nfssvc_flag, (caddr_t)&nsd) < 0) {
		    if (errno == ENEEDAUTH) {
			nfssvc_flag = (NFSSVC_NFSD | NFSSVC_AUTHINFAIL);
E 15
I 15
		while (nfssvc(nfssvc_flag, &nsd) < 0) {
			if (errno != ENEEDAUTH) {
				syslog(LOG_ERR, "nfssvc: %m");
				exit(1);
			}
			nfssvc_flag = NFSSVC_NFSD | NFSSVC_AUTHINFAIL;
E 15
D 22
#ifdef KERBEROS
			kt.length = nsd.nsd_authlen;
			kt.mbz = 0;
D 15
			strcpy(inst, "*");
			if (krb_rd_req(&kt, "rcmd", inst, nsd.nsd_haddr,
			    &auth, "") == RD_AP_OK &&
E 15
I 15
			(void)strcpy(inst, "*");
			if (krb_rd_req(&kt, "rcmd",
			    inst, nsd.nsd_haddr, &auth, "") == RD_AP_OK &&
E 15
			    krb_kntoln(&auth, lnam) == KSUCCESS &&
D 15
			    (pwd = getpwnam(lnam))) {
			    cr->cr_uid = pwd->pw_uid;
			    cr->cr_groups[0] = pwd->pw_gid;
			    cr->cr_ngroups = 1;
			    setgrent();
			    while (grp = getgrent()) {
				if (grp->gr_gid == cr->cr_groups[0])
				    continue;
				cpp = grp->gr_mem;
				while (*cpp) {
				    if (!strcmp(*cpp, lnam))
					break;
				    cpp++;
E 15
I 15
			    (pwd = getpwnam(lnam)) != NULL) {
E 22
I 22
#ifdef NFSKERB
			/*
			 * Get the Kerberos ticket out of the authenticator
			 * verify it and convert the principal name to a user
			 * name. The user name is then converted to a set of
			 * user credentials via the password and group file.
			 * Finally, decrypt the timestamp and validate it.
			 * For more info see the IETF Draft "Authentication
			 * in ONC RPC".
			 */
			kt.length = ntohl(kt.length);
			if (gettimeofday(&ktv, (struct timezone *)0) == 0 &&
			    kt.length > 0 && kt.length <=
			    (RPCAUTH_MAXSIZ - 3 * NFSX_UNSIGNED)) {
			    kin.w1 = NFS_KERBW1(kt);
			    kt.mbz = 0;
			    (void)strcpy(inst, "*");
			    if (krb_rd_req(&kt, NFS_KERBSRV,
				inst, nsd.nsd_haddr, &kauth, "") == RD_AP_OK &&
				krb_kntoln(&kauth, lnam) == KSUCCESS &&
				(pwd = getpwnam(lnam)) != NULL) {
E 22
				cr = &nsd.nsd_cr;
				cr->cr_uid = pwd->pw_uid;
				cr->cr_groups[0] = pwd->pw_gid;
				cr->cr_ngroups = 1;
				setgrent();
				while ((grp = getgrent()) != NULL) {
					if (grp->gr_gid == cr->cr_groups[0])
						continue;
					for (cpp = grp->gr_mem;
					    *cpp != NULL; ++cpp)
						if (!strcmp(*cpp, lnam))
							break;
					if (*cpp == NULL)
						continue;
					cr->cr_groups[cr->cr_ngroups++]
					    = grp->gr_gid;
					if (cr->cr_ngroups == NGROUPS)
						break;
E 15
				}
D 15
				if (*cpp) {
				    cr->cr_groups[cr->cr_ngroups++] = grp->gr_gid;
				    if (cr->cr_ngroups == NGROUPS)
					break;
				}
			    }
			    endgrent();
			    nfssvc_flag = (NFSSVC_NFSD | NFSSVC_AUTHIN);
E 15
I 15
				endgrent();
D 22
				nfssvc_flag = NFSSVC_NFSD | NFSSVC_AUTHIN;
E 22
I 22

				/*
				 * Get the timestamp verifier out of the
				 * authenticator and verifier strings.
				 */
				kin.t1 = kverf.t1;
				kin.t2 = kverf.t2;
				kin.w2 = kverf.w2;
				bzero((caddr_t)kivec, sizeof (kivec));
				bcopy((caddr_t)kauth.session,
				    (caddr_t)nsd.nsd_key,sizeof(kauth.session));

				/*
				 * Decrypt the timestamp verifier in CBC mode.
				 */
				XXX

				/*
				 * Validate the timestamp verifier, to
				 * check that the session key is ok.
				 */
				nsd.nsd_timestamp.tv_sec = ntohl(kout.t1);
				nsd.nsd_timestamp.tv_usec = ntohl(kout.t2);
				nsd.nsd_ttl = ntohl(kout.w1);
				if ((nsd.nsd_ttl - 1) == ntohl(kout.w2))
				    nfssvc_flag = NFSSVC_NFSD | NFSSVC_AUTHIN;
E 22
E 15
			}
D 15
#endif	/* KERBEROS */
		    } else {
D 13
fprintf(stderr, "errno=%d\n",errno);
E 13
			syslog(LOG_ERR, "Nfsd died %m");
			exit(1);
		    }
E 15
I 15
D 22
#endif /* KERBEROS */
E 22
I 22
#endif /* NFSKERB */
E 22
E 15
		}
D 15
		exit();
	    }
E 15
I 15
		exit(0);
	}
E 15

D 15
	/*
	 * If we are serving udp, set up the socket.
	 */
E 15
I 15
	/* If we are serving udp, set up the socket. */
E 15
E 11
E 10
D 4
	if (!pmap_set(RPCPROG_NFS, NFS_VER2, IPPROTO_UDP, NFS_PORT)) {
		syslog(LOG_ERR, "Can't register with portmap");
		exit(1);
E 4
I 4
	if (udpflag) {
		if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
D 11
			syslog(LOG_ERR, "Can't create socket");
E 11
I 11
D 15
			syslog(LOG_ERR, "Can't create udp socket");
E 15
I 15
			syslog(LOG_ERR, "can't create udp socket");
E 15
E 11
			exit(1);
		}
D 11
		saddr.sin_family = AF_INET;
		saddr.sin_addr.s_addr = INADDR_ANY;
		saddr.sin_port = htons(NFS_PORT);
D 10
		if (bind(sock, &saddr, sizeof(saddr)) < 0) {
E 10
I 10
		if (bind(sock, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
E 10
			syslog(LOG_ERR, "Can't bind addr");
E 11
I 11
		inetaddr.sin_family = AF_INET;
		inetaddr.sin_addr.s_addr = INADDR_ANY;
		inetaddr.sin_port = htons(NFS_PORT);
		inetaddr.sin_len = sizeof(inetaddr);
D 15
		if (bind(sock, (struct sockaddr *)&inetaddr, sizeof(inetaddr)) < 0) {
			syslog(LOG_ERR, "Can't bind udp addr");
E 15
I 15
		if (bind(sock,
		    (struct sockaddr *)&inetaddr, sizeof(inetaddr)) < 0) {
			syslog(LOG_ERR, "can't bind udp addr");
E 15
E 11
			exit(1);
		}
D 22
		if (!pmap_set(RPCPROG_NFS, NFS_VER2, IPPROTO_UDP, NFS_PORT)) {
E 22
I 22
		if (!pmap_set(RPCPROG_NFS, 2, IPPROTO_UDP, NFS_PORT) ||
		    !pmap_set(RPCPROG_NFS, 3, IPPROTO_UDP, NFS_PORT)) {
E 22
D 11
			syslog(LOG_ERR, "Can't register with portmap");
E 11
I 11
D 15
			syslog(LOG_ERR, "Can't register with udp portmap");
E 15
I 15
			syslog(LOG_ERR, "can't register with udp portmap");
E 15
E 11
			exit(1);
		}
D 11
	
E 11
I 11
		nfsdargs.sock = sock;
D 15
		nfsdargs.name = (caddr_t)0;
E 15
I 15
		nfsdargs.name = NULL;
E 15
		nfsdargs.namelen = 0;
		if (nfssvc(NFSSVC_ADDSOCK, &nfsdargs) < 0) {
D 15
			syslog(LOG_ERR, "Can't Add UDP socket");
E 15
I 15
			syslog(LOG_ERR, "can't Add UDP socket");
E 15
			exit(1);
		}
D 15
		close(sock);
E 15
I 15
		(void)close(sock);
E 15
	}

D 15
	/*
	 * If we are serving cltp, set up the socket.
	 */
E 15
#ifdef ISO
I 15
	/* If we are serving cltp, set up the socket. */
E 15
	if (cltpflag) {
		if ((sock = socket(AF_ISO, SOCK_DGRAM, 0)) < 0) {
D 15
			syslog(LOG_ERR, "Can't create cltp socket");
E 15
I 15
			syslog(LOG_ERR, "can't create cltp socket");
E 15
			exit(1);
		}
D 15
		bzero((caddr_t)&isoaddr, sizeof (isoaddr));
E 15
I 15
		memset(&isoaddr, 0, sizeof(isoaddr));
E 15
		isoaddr.siso_family = AF_ISO;
		isoaddr.siso_tlen = 2;
		cp = TSEL(&isoaddr);
		*cp++ = (NFS_PORT >> 8);
		*cp = (NFS_PORT & 0xff);
		isoaddr.siso_len = sizeof(isoaddr);
D 15
		if (bind(sock, (struct sockaddr *)&isoaddr, sizeof(isoaddr)) < 0) {
			syslog(LOG_ERR, "Can't bind cltp addr");
E 15
I 15
		if (bind(sock,
		    (struct sockaddr *)&isoaddr, sizeof(isoaddr)) < 0) {
			syslog(LOG_ERR, "can't bind cltp addr");
E 15
			exit(1);
		}
#ifdef notyet
E 11
		/*
I 15
		 * XXX
E 15
D 10
		 * Send the nfs datagram servers right down into the kernel
E 10
I 10
D 11
		 * Send the nfs datagram servers
		 * right down into the kernel
E 11
I 11
		 * Someday this should probably use "rpcbind", the son of
		 * portmap.
E 11
E 10
		 */
D 11
		for (i = 0; i < udpcnt; i++)
			if (fork() == 0) {
I 10
				setproctitle("nfsd-udp",
				    (struct sockaddr_in *)NULL);
E 10
				ret = nfssvc(sock, &msk, sizeof(msk),
						&mtch, sizeof(mtch));
				if (ret < 0)
					syslog(LOG_ERR, "nfssvc() failed %m");
D 9
				exit();
E 9
I 9
				exit(1);
E 9
			}
E 11
I 11
		if (!pmap_set(RPCPROG_NFS, NFS_VER2, IPPROTO_UDP, NFS_PORT)) {
D 15
			syslog(LOG_ERR, "Can't register with udp portmap");
E 15
I 15
			syslog(LOG_ERR, "can't register with udp portmap");
E 15
			exit(1);
		}
#endif /* notyet */
		nfsdargs.sock = sock;
D 15
		nfsdargs.name = (caddr_t)0;
E 15
I 15
		nfsdargs.name = NULL;
E 15
		nfsdargs.namelen = 0;
		if (nfssvc(NFSSVC_ADDSOCK, &nfsdargs) < 0) {
D 15
			syslog(LOG_ERR, "Can't Add UDP socket");
			exit();
E 15
I 15
			syslog(LOG_ERR, "can't add UDP socket");
			exit(1);
E 15
		}
E 11
		close(sock);
E 4
	}
I 11
D 15
#endif	/* ISO */
E 15
I 15
#endif /* ISO */
E 15
E 11
D 2
	if (argc != 2 || (cnt = atoi(argv[1])) <= 0 || cnt > 20)
E 2
I 2
D 4
	if (argc == 2) {
		if ((cnt = atoi(argv[1])) <= 0 || cnt > 20)
			cnt = 1;
		msk = 0;
		mtch = 0;
	} else if (argc == 4) {
		if ((cnt = atoi(argv[1])) <= 0 || cnt > 20)
			cnt = 1;
		msk = inet_addr(argv[2]);
		mtch = inet_addr(argv[3]);
	} else {
E 2
		cnt = 1;
I 2
		msk = 0;
		mtch = 0;
E 4
I 4

D 15
	/*
D 11
	 * Now set up the master STREAM server waiting for tcp connections.
E 11
I 11
	 * Now set up the master server socket waiting for tcp connections.
E 11
	 */
E 15
I 15
	/* Now set up the master server socket waiting for tcp connections. */
	on = 1;
E 15
I 11
	FD_ZERO(&sockbits);
I 15
	connect_type_cnt = 0;
E 15
E 11
	if (tcpflag) {
I 10
D 11
		int on = 1;
E 11
I 11
		if ((tcpsock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
D 15
			syslog(LOG_ERR, "Can't create tcp socket");
E 15
I 15
			syslog(LOG_ERR, "can't create tcp socket");
E 15
			exit(1);
		}
D 15
		if (setsockopt(tcpsock, SOL_SOCKET, SO_REUSEADDR,
		    (char *) &on, sizeof(on)) < 0)
E 15
I 15
		if (setsockopt(tcpsock,
		    SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) < 0)
E 15
			syslog(LOG_ERR, "setsockopt SO_REUSEADDR: %m");
		inetaddr.sin_family = AF_INET;
		inetaddr.sin_addr.s_addr = INADDR_ANY;
		inetaddr.sin_port = htons(NFS_PORT);
D 15
		inetaddr.sin_len = sizeof (inetaddr);
		if (bind(tcpsock, (struct sockaddr *)&inetaddr, sizeof (inetaddr)) < 0) {
			syslog(LOG_ERR, "Can't bind tcp addr");
E 15
I 15
		inetaddr.sin_len = sizeof(inetaddr);
		if (bind(tcpsock,
		    (struct sockaddr *)&inetaddr, sizeof (inetaddr)) < 0) {
			syslog(LOG_ERR, "can't bind tcp addr");
E 15
			exit(1);
		}
		if (listen(tcpsock, 5) < 0) {
D 15
			syslog(LOG_ERR, "Listen failed");
E 15
I 15
			syslog(LOG_ERR, "listen failed");
E 15
			exit(1);
		}
D 22
		if (!pmap_set(RPCPROG_NFS, NFS_VER2, IPPROTO_TCP, NFS_PORT)) {
E 22
I 22
		if (!pmap_set(RPCPROG_NFS, 2, IPPROTO_TCP, NFS_PORT) ||
		    !pmap_set(RPCPROG_NFS, 3, IPPROTO_TCP, NFS_PORT)) {
E 22
D 15
			syslog(LOG_ERR, "Can't register tcp with portmap");
E 15
I 15
			syslog(LOG_ERR, "can't register tcp with portmap");
E 15
			exit(1);
		}
		FD_SET(tcpsock, &sockbits);
		maxsock = tcpsock;
		connect_type_cnt++;
	}
E 11

E 10
D 11
		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			syslog(LOG_ERR, "Can't create socket");
E 11
I 11
#ifdef notyet
D 15
	/*
	 * Now set up the master server socket waiting for tp4 connections.
	 */
E 15
I 15
	/* Now set up the master server socket waiting for tp4 connections. */
E 15
	if (tp4flag) {
		if ((tp4sock = socket(AF_ISO, SOCK_SEQPACKET, 0)) < 0) {
D 15
			syslog(LOG_ERR, "Can't create tp4 socket");
E 15
I 15
			syslog(LOG_ERR, "can't create tp4 socket");
E 15
E 11
			exit(1);
		}
I 10
D 11
		if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
E 11
I 11
D 15
		if (setsockopt(tp4sock, SOL_SOCKET, SO_REUSEADDR,
E 11
		    (char *) &on, sizeof(on)) < 0)
E 15
I 15
		if (setsockopt(tp4sock,
		    SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) < 0)
E 15
			syslog(LOG_ERR, "setsockopt SO_REUSEADDR: %m");
E 10
D 11
		saddr.sin_family = AF_INET;
		saddr.sin_addr.s_addr = INADDR_ANY;
		saddr.sin_port = htons(NFS_PORT);
D 10
		if (bind(sock, &saddr, sizeof(saddr)) < 0) {
E 10
I 10
		if (bind(sock, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
E 10
			syslog(LOG_ERR, "Can't bind addr");
E 11
I 11
D 15
		bzero((caddr_t)&isoaddr, sizeof (isoaddr));
E 15
I 15
		memset(&isoaddr, 0, sizeof(isoaddr));
E 15
		isoaddr.siso_family = AF_ISO;
		isoaddr.siso_tlen = 2;
		cp = TSEL(&isoaddr);
		*cp++ = (NFS_PORT >> 8);
		*cp = (NFS_PORT & 0xff);
		isoaddr.siso_len = sizeof(isoaddr);
D 15
		if (bind(tp4sock, (struct sockaddr *)&isoaddr, sizeof (isoaddr)) < 0) {
			syslog(LOG_ERR, "Can't bind tp4 addr");
E 15
I 15
		if (bind(tp4sock,
		    (struct sockaddr *)&isoaddr, sizeof (isoaddr)) < 0) {
			syslog(LOG_ERR, "can't bind tp4 addr");
E 15
E 11
			exit(1);
		}
D 11
		if (listen(sock, 5) < 0) {
E 11
I 11
		if (listen(tp4sock, 5) < 0) {
E 11
D 15
			syslog(LOG_ERR, "Listen failed");
E 15
I 15
			syslog(LOG_ERR, "listen failed");
E 15
			exit(1);
		}
I 11
		/*
D 15
		 * Someday this should probably use "rpcbind".
E 15
I 15
		 * XXX
		 * Someday this should probably use "rpcbind", the son of
		 * portmap.
E 15
		 */
E 11
		if (!pmap_set(RPCPROG_NFS, NFS_VER2, IPPROTO_TCP, NFS_PORT)) {
D 11
			syslog(LOG_ERR, "Can't register with portmap");
E 11
I 11
D 15
			syslog(LOG_ERR, "Can't register tcp with portmap");
E 15
I 15
			syslog(LOG_ERR, "can't register tcp with portmap");
E 15
E 11
			exit(1);
		}
I 10
D 11
		setproctitle("nfsd-listen", (struct sockaddr_in *)NULL);
E 11
I 11
		FD_SET(tp4sock, &sockbits);
		maxsock = tp4sock;
		connect_type_cnt++;
	}

D 15
	/*
	 * Now set up the master server socket waiting for tpip connections.
	 */
E 15
I 15
	/* Now set up the master server socket waiting for tpip connections. */
E 15
	if (tpipflag) {
		if ((tpipsock = socket(AF_INET, SOCK_SEQPACKET, 0)) < 0) {
D 15
			syslog(LOG_ERR, "Can't create tpip socket");
E 15
I 15
			syslog(LOG_ERR, "can't create tpip socket");
E 15
			exit(1);
		}
D 15
		if (setsockopt(tpipsock, SOL_SOCKET, SO_REUSEADDR,
		    (char *) &on, sizeof(on)) < 0)
E 15
I 15
		if (setsockopt(tpipsock,
		    SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) < 0)
E 15
			syslog(LOG_ERR, "setsockopt SO_REUSEADDR: %m");
		inetaddr.sin_family = AF_INET;
		inetaddr.sin_addr.s_addr = INADDR_ANY;
		inetaddr.sin_port = htons(NFS_PORT);
D 15
		inetaddr.sin_len = sizeof (inetaddr);
		if (bind(tpipsock, (struct sockaddr *)&inetaddr, sizeof (inetaddr)) < 0) {
			syslog(LOG_ERR, "Can't bind tcp addr");
E 15
I 15
		inetaddr.sin_len = sizeof(inetaddr);
		if (bind(tpipsock,
		    (struct sockaddr *)&inetaddr, sizeof (inetaddr)) < 0) {
			syslog(LOG_ERR, "can't bind tcp addr");
E 15
			exit(1);
		}
		if (listen(tpipsock, 5) < 0) {
D 15
			syslog(LOG_ERR, "Listen failed");
E 15
I 15
			syslog(LOG_ERR, "listen failed");
E 15
			exit(1);
		}
E 11
E 10
		/*
D 11
		 * Loop forever accepting connections and sending the children
		 * into the kernel to service the mounts.
E 11
I 11
D 15
		 * Someday this should use "rpcbind"
E 15
I 15
		 * XXX
		 * Someday this should probably use "rpcbind", the son of
		 * portmap.
E 15
E 11
		 */
D 11
		for (;;) {
D 10
			if ((msgsock = accept(sock, (struct sockaddr *)0,
				(int *)0)) < 0) {
E 10
I 10
			len = sizeof(peername);
			if ((msgsock = accept(sock,
			    (struct sockaddr *)&peername, &len)) < 0) {
E 11
I 11
		if (!pmap_set(RPCPROG_NFS, NFS_VER2, IPPROTO_TCP, NFS_PORT)) {
D 15
			syslog(LOG_ERR, "Can't register tcp with portmap");
E 15
I 15
			syslog(LOG_ERR, "can't register tcp with portmap");
E 15
			exit(1);
		}
		FD_SET(tpipsock, &sockbits);
		maxsock = tpipsock;
		connect_type_cnt++;
	}
D 15
#endif	/* notyet */
E 15
I 15
#endif /* notyet */
E 15

	if (connect_type_cnt == 0)
D 15
		exit();
E 15
I 15
		exit(0);

E 15
D 22
	setproctitle("nfsd-master");
E 22
I 22
	setproctitle("master");
E 22
I 15

E 15
	/*
	 * Loop forever accepting connections and passing the sockets
	 * into the kernel for the mounts.
	 */
	for (;;) {
		ready = sockbits;
		if (connect_type_cnt > 1) {
D 15
			if (select(maxsock + 1, &ready, (fd_set *)0,
				(fd_set *)0, (struct timeval *)0) < 1) {
				syslog(LOG_ERR, "Select failed");
E 15
I 15
			if (select(maxsock + 1,
			    &ready, NULL, NULL, NULL) < 1) {
				syslog(LOG_ERR, "select failed: %m");
E 15
				exit(1);
			}
		}
		if (tcpflag && FD_ISSET(tcpsock, &ready)) {
			len = sizeof(inetpeer);
			if ((msgsock = accept(tcpsock,
			    (struct sockaddr *)&inetpeer, &len)) < 0) {
E 11
E 10
D 15
				syslog(LOG_ERR, "Accept failed: %m");
E 15
I 15
				syslog(LOG_ERR, "accept failed: %m");
E 15
				exit(1);
			}
I 12
D 15
			bzero((char *)inetpeer.sin_zero,
			    sizeof(inetpeer.sin_zero));
E 15
I 15
			memset(inetpeer.sin_zero, 0, sizeof(inetpeer.sin_zero));
E 15
E 12
D 10
			/*
			 * Grab child termination status' just so defuncts
			 * are not left lying about.
			 */
			while (wait3(&chldstat, WNOHANG, (struct rusage *)0))
				;
			len = sizeof(peername);
			if (getsockname(msgsock, &peername, &len) < 0) {
				syslog(LOG_ERR, "Getsockname failed\n");
				exit(1);
			}
			if ((peername.sin_addr.s_addr & msk.sin_addr.s_addr)
				!= mtch.sin_addr.s_addr) {
E 10
I 10
D 11
			if ((peername.sin_addr.s_addr & msk.sin_addr.s_addr) !=
			   mtch.sin_addr.s_addr) {
E 10
				hp = hphead.ha_next;
				while (hp) {
					if (peername.sin_addr.s_addr ==
						hp->ha_sad)
						break;
					hp = hp->ha_next;
				}
				if (hp == NULL) {
					shutdown(msgsock, 2);
					close(msgsock);
					continue;
				}
E 11
I 11
			if (setsockopt(msgsock, SOL_SOCKET,
D 15
			    SO_KEEPALIVE, (char *) &on, sizeof(on)) < 0)
E 15
I 15
			    SO_KEEPALIVE, (char *)&on, sizeof(on)) < 0)
E 15
				syslog(LOG_ERR,
				    "setsockopt SO_KEEPALIVE: %m");
			nfsdargs.sock = msgsock;
			nfsdargs.name = (caddr_t)&inetpeer;
D 12
			nfsdargs.namelen = len;
E 12
I 12
			nfsdargs.namelen = sizeof(inetpeer);
E 12
			nfssvc(NFSSVC_ADDSOCK, &nfsdargs);
D 15
			close(msgsock);
E 15
I 15
			(void)close(msgsock);
E 15
		}
#ifdef notyet
		if (tp4flag && FD_ISSET(tp4sock, &ready)) {
			len = sizeof(isopeer);
			if ((msgsock = accept(tp4sock,
			    (struct sockaddr *)&isopeer, &len)) < 0) {
D 15
				syslog(LOG_ERR, "Accept failed: %m");
E 15
I 15
				syslog(LOG_ERR, "accept failed: %m");
E 15
				exit(1);
E 11
			}
D 11
			if (fork() == 0) {
				close(sock);
I 10
				setproctitle("nfsd-tcp", &peername);
				if (setsockopt(msgsock, SOL_SOCKET,
				    SO_KEEPALIVE, (char *) &on, sizeof(on)) < 0)
					syslog(LOG_ERR,
					    "setsockopt SO_KEEPALIVE: %m");
E 10
				ret = nfssvc(msgsock, &msk, sizeof(msk),
						&mtch, sizeof(mtch));
				shutdown(msgsock, 2);
				if (ret < 0)
D 7
					syslog(LOG_ERR, "Nfssvc STREAM Failed");
E 7
I 7
					syslog(LOG_NOTICE,
					    "Nfssvc STREAM Failed");
E 11
I 11
			if (setsockopt(msgsock, SOL_SOCKET,
D 15
			    SO_KEEPALIVE, (char *) &on, sizeof(on)) < 0)
E 15
I 15
			    SO_KEEPALIVE, (char *)&on, sizeof(on)) < 0)
E 15
				syslog(LOG_ERR,
				    "setsockopt SO_KEEPALIVE: %m");
			nfsdargs.sock = msgsock;
			nfsdargs.name = (caddr_t)&isopeer;
			nfsdargs.namelen = len;
			nfssvc(NFSSVC_ADDSOCK, &nfsdargs);
D 15
			close(msgsock);
E 15
I 15
			(void)close(msgsock);
E 15
		}
		if (tpipflag && FD_ISSET(tpipsock, &ready)) {
			len = sizeof(inetpeer);
			if ((msgsock = accept(tpipsock,
			    (struct sockaddr *)&inetpeer, &len)) < 0) {
				syslog(LOG_ERR, "Accept failed: %m");
E 11
E 7
D 9
				exit();
E 9
I 9
				exit(1);
E 9
			}
I 11
			if (setsockopt(msgsock, SOL_SOCKET,
D 15
			    SO_KEEPALIVE, (char *) &on, sizeof(on)) < 0)
				syslog(LOG_ERR,
				    "setsockopt SO_KEEPALIVE: %m");
E 15
I 15
			    SO_KEEPALIVE, (char *)&on, sizeof(on)) < 0)
				syslog(LOG_ERR, "setsockopt SO_KEEPALIVE: %m");
E 15
			nfsdargs.sock = msgsock;
			nfsdargs.name = (caddr_t)&inetpeer;
			nfsdargs.namelen = len;
			nfssvc(NFSSVC_ADDSOCK, &nfsdargs);
E 11
D 15
			close(msgsock);
E 15
I 15
			(void)close(msgsock);
E 15
		}
I 11
D 15
#endif	/* notyet */
E 15
I 15
#endif /* notyet */
E 15
E 11
E 4
	}
E 2
D 4
	for (i = 1; i < cnt; i++)
		if (fork() == 0)
			break;
D 2
	if (nfssvc(sock) < 0)		/* Only returns on error */
E 2
I 2
	if (nfssvc(sock, msk, mtch) < 0)	/* Only returns on error */
E 2
		syslog(LOG_ERR, "nfssvc() failed %m");
	exit();
E 4
I 4
}

I 15
void
E 15
usage()
{
D 11
	fprintf(stderr, "nfsd [-t msk,mtch[,addrs]] [-u msk,mtch,numprocs]\n");
E 11
I 11
D 15
	fprintf(stderr, "nfsd [-u] [-t] [-c] [-r] [num_nfsds]\n");
E 15
I 15
D 17
	(void)fprintf(stderr, "nfsd [%s] [num_nfsds]\n", FLAGS);
E 17
I 17
D 22
	(void)fprintf(stderr, "nfsd %s\n", USAGE);
E 22
I 22
	(void)fprintf(stderr, "usage: nfsd %s\n", USAGE);
E 22
E 17
E 15
E 11
	exit(1);
I 18
}

void
nonfs(signo)
	int signo;
{
	syslog(LOG_ERR, "missing system call: NFS not available.");
E 18
I 10
}

void
D 15
reapchild()
E 15
I 15
reapchild(signo)
	int signo;
E 15
{

D 15
	while (wait3((int *) NULL, WNOHANG, (struct rusage *) NULL))
		;
E 15
I 15
D 22
	while (wait3(NULL, WNOHANG, NULL));
E 22
I 22
	while (wait3(NULL, WNOHANG, NULL) > 0);
E 22
E 15
}

I 15
void
E 15
D 11
setproctitle(a, sin)
E 11
I 11
setproctitle(a)
E 11
	char *a;
D 11
	struct sockaddr_in *sin;
E 11
{
	register char *cp;
	char buf[80];

	cp = Argv[0];
D 11
	if (sin)
		(void) sprintf(buf, "%s [%s]", a, inet_ntoa(sin->sin_addr));
	else
		(void) sprintf(buf, "%s", a);
E 11
I 11
D 15
	(void) sprintf(buf, "%s", a);
E 11
	(void) strncpy(cp, buf, LastArg - cp);
E 15
I 15
D 22
	(void)snprintf(buf, sizeof(buf), "%s", a);
E 22
I 22
	(void)snprintf(buf, sizeof(buf), "nfsd-%s", a);
E 22
	(void)strncpy(cp, buf, LastArg - cp);
E 15
	cp += strlen(cp);
	while (cp < LastArg)
D 21
		*cp++ = ' ';
E 21
I 21
		*cp++ = '\0';
E 21
E 10
E 4
}
E 1
