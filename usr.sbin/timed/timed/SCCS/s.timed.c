h53704
s 00042/00039/00915
d D 8.2 95/03/26 14:25:38 vjs 28 27
c fix initialization of socket
e
s 00005/00005/00949
d D 8.1 93/06/06 14:10:02 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00660/00321/00294
d D 5.1 93/05/11 11:51:19 bostic 26 25
c new version from Vernon Schryver (vjs@sgi.com); see ../timed/CHANGES for details
e
s 00004/00002/00611
d D 2.21 91/03/02 17:36:07 bostic 25 24
c ANSI
e
s 00001/00014/00612
d D 2.20 90/06/29 20:45:12 karels 24 23
c use daemon() call
e
s 00000/00004/00626
d D 2.19 90/06/27 14:20:05 sklower 23 22
c tested wrong thing to decide if new or old sockaddrs; just do new.
e
s 00011/00003/00619
d D 2.18 90/06/26 15:57:49 sklower 22 21
c revise parse of information obtained via SIOCGCONF
e
s 00001/00011/00621
d D 2.17 90/06/01 19:04:33 bostic 21 20
c new copyright notice
e
s 00002/00002/00630
d D 2.16 89/05/11 14:14:02 bostic 20 19
c file reorg, pathnames.h, paths.h
e
s 00002/00001/00630
d D 2.15 89/04/02 15:44:51 bostic 19 18
c add pathnames.h
e
s 00010/00005/00621
d D 2.14 88/06/18 14:08:27 bostic 18 17
c install approved copyright notice
e
s 00010/00004/00616
d D 2.13 87/12/23 14:30:19 bostic 17 16
c append Berkeley header; NASA wants a copy
e
s 00001/00001/00619
d D 2.12 87/04/06 11:48:33 bostic 16 15
c printf format/argument mismatch
e
s 00018/00008/00602
d D 2.11 87/03/04 15:56:19 karels 15 14
c don't hold icmp socket open when not using it
e
s 00005/00007/00605
d D 2.10 86/06/02 10:58:15 bloom 14 13
x 11
c move fork back -- closed file descriptors that should be open
e
s 00013/00014/00597
d D 2.9 86/05/28 20:10:07 bloom 13 12
c lint cleanup (fix sequence number problem)
e
s 00004/00005/00607
d D 2.8 86/05/27 15:58:21 karels 12 11
c toss MAXSEQ
e
s 00021/00022/00591
d D 2.7 86/05/27 15:36:11 karels 11 10
c delay fork until set up
e
s 00004/00002/00609
d D 2.6 86/05/15 08:47:17 bloom 10 9
c only one call to openlog needed, need to know if we just received a quit
e
s 00058/00014/00553
d D 2.5 86/04/26 22:46:25 bloom 9 8
c allow multiple -n flags, add -i flag from Kirk Smith (ks@ef.purdue.edu)
e
s 00208/00141/00359
d D 2.4 86/04/11 18:17:00 bloom 8 7
c major work on multiple network code (Kirk Smith, ks@ef.purdue.edu)
e
s 00001/00000/00499
d D 2.3 86/02/17 13:18:11 bloom 7 6
c clean hostlist when going from master to slave (from ks@purdue)
e
s 00001/00001/00498
d D 2.2 86/02/05 18:30:22 bloom 6 5
c fix typo
e
s 00198/00106/00301
d D 2.1 85/12/10 13:07:34 bloom 5 4
c Multi network support
e
s 00002/00006/00405
d D 1.4 85/10/29 11:44:18 bloom 4 3
c simplify code for getting date string
e
s 00002/00002/00409
d D 1.3 85/10/05 22:18:41 bloom 3 2
c fix bug that caused -M to be ignored
e
s 00103/00070/00308
d D 1.2 85/09/18 19:58:18 bloom 2 1
c move constants, fix syslog messages, fix nflag code, detach from terminal,
c fix bug which allowed a slave to respond as master in certain circumstances,
c fix casual (by gusella)
e
s 00378/00000/00000
d D 1.1 85/06/22 22:08:00 gusella 1 0
c date and time created 85/06/22 22:08:00 by gusella
e
u
U
t
T
I 1
D 26
/*
D 11
D 14
 * Copyright (c) 1983 Regents of the University of California.
E 14
I 14
 * Copyright (c) 1985 Regents of the University of California.
E 26
I 26
/*-
D 27
 * Copyright (c) 1985, 1993 The Regents of the University of California.
E 26
E 14
E 11
I 11
 * Copyright (c) 1985 Regents of the University of California.
E 11
D 17
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 17
I 17
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
 *
D 21
 * Redistribution and use in source and binary forms are permitted
D 18
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 18
I 18
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 21
I 21
 * %sccs.include.redist.c%
E 21
E 18
E 17
 */

#ifndef lint
D 27
char copyright[] =
D 11
D 14
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 14
I 14
D 26
"%Z% Copyright (c) 1985 Regents of the University of California.\n\
E 26
I 26
"%Z% Copyright (c) 1985, 1993 The Regents of the University of California.\n\
E 26
E 14
E 11
I 11
"@(#) Copyright (c) 1985 Regents of the University of California.\n\
E 11
 All rights reserved.\n";
E 27
I 27
static char copyright[] =
"%Z% Copyright (c) 1985, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 27
D 17
#endif not lint
E 17
I 17
#endif /* not lint */
E 17

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 17
#endif not lint
E 17
I 17
#endif /* not lint */
E 17

D 26
#include "globals.h"
E 26
I 26
#ifdef sgi
#ident "$Revision: 1.25 $"
#endif /* sgi */

E 26
#define TSPTYPES
D 26
#include <protocols/timed.h>
E 26
I 26
#include "globals.h"
E 26
#include <net/if.h>
I 25
D 26
#include <arpa/inet.h>
E 26
E 25
#include <sys/file.h>
#include <sys/ioctl.h>
#include <setjmp.h>
I 19
#include "pathnames.h"
I 26
#include <math.h>
#include <sys/types.h>
#include <sys/times.h>
#ifdef sgi
#include <unistd.h>
#include <sys/syssgi.h>
#include <sys/schedctl.h>
#endif /* sgi */
E 26
E 19

D 2
#define OFF		0
#define ON		1
#define SLAVE		0
#define MASTER		1
#define MAXRANDOM	2147483648	/* 2**31, max random number */

E 2
D 26
int id;
int trace;
E 26
I 26
int trace = 0;
E 26
D 15
int sock, sock_raw;
E 15
I 15
int sock, sock_raw = -1;
E 15
D 5
int status;     			/* either MASTER or SLAVE */
E 5
I 5
int status = 0;
E 5
D 26
int backoff;
int slvcount;				/* no. of slaves controlled by master */
int machup;
E 26
u_short sequence;			/* sequence number */
long delay1;
long delay2;
I 13
D 26
long random();
E 13
D 2
char hostname[32];
E 2
I 2
char hostname[MAXHOSTNAMELEN];
E 2
D 5
struct in_addr broadcastaddr;		/* local net broadcast address */
I 2
u_long netmask, mynet = 0;		/* my network number & netmask */
E 2
struct sockaddr_in server;
E 5
struct host hp[NHOSTS];
D 5
char *fj;
E 5
I 5
D 19
char tracefile[] = "/usr/adm/timed.log";
E 19
I 19
char tracefile[] = _PATH_TIMEDLOG;
E 19
E 5
FILE *fd;
E 26
I 26

int nslavenets;				/* nets were I could be a slave */
int nmasternets;			/* nets were I could be a master */
int nignorednets;			/* ignored nets */
int nnets;				/* nets I am connected to */

FILE *fd;				/* trace file FD */

E 26
jmp_buf jmpenv;
I 5
D 26
struct netinfo *nettab = NULL;
I 8
int nslavenets;		/* Number of networks were I could be a slave */
int nmasternets;	/* Number of networks were I could be a master */
int nignorednets;	/* Number of ignored networks */
int nnets;		/* Number of networks I am connected to */
E 26
I 26

struct netinfo *nettab = 0;
E 26
struct netinfo *slavenet;
D 26
struct netinfo *firstslavenet();
E 26
int Mflag;
I 10
int justquit = 0;
I 26
int debug;
E 26

E 10
I 9
D 26
struct nets {
	char *name;
	long net;
E 26
I 26
static struct nets {
	char	*name;
	long	net;
E 26
	struct nets *next;
D 26
} *nets = (struct nets *)0;
E 26
I 26
} *nets = 0;
E 26
E 9
E 8
E 5

I 26
struct hosttbl hosttbl[NHOSTS+1];	/* known hosts */

static struct goodhost {		/* hosts that we trust */
	char	name[MAXHOSTNAMELEN+1];
	struct goodhost *next;
	char	perm;
} *goodhosts;

static char *goodgroup;			/* net group of trusted hosts */
static void checkignorednets __P((void));
static void pickslavenet __P((struct netinfo *));
static void add_good_host __P((char *, int));

#ifdef sgi
char *timetrim_fn;
char *timetrim_wpat = "long timetrim = %ld;\ndouble tot_adj = %.0f;\ndouble tot_ticks = %.0f;\n/* timed version 2 */\n";
char *timetrim_rpat = "long timetrim = %ld;\ndouble tot_adj = %lf;\ndouble tot_ticks = %lf;";
long timetrim;
double tot_adj, hr_adj;			/* totals in nsec */
double tot_ticks, hr_ticks;

int bufspace = 60*1024;
#endif


E 26
D 5
extern struct sockaddr_in from;

E 5
/*
 * The timedaemons synchronize the clocks of hosts in a local area network.
 * One daemon runs as master, all the others as slaves. The master
 * performs the task of computing clock differences and sends correction
D 26
 * values to the slaves. 
 * Slaves start an election to choose a new master when the latter disappears 
E 26
I 26
 * values to the slaves.
 * Slaves start an election to choose a new master when the latter disappears
E 26
 * because of a machine crash, network partition, or when killed.
 * A resolution protocol is used to kill all but one of the masters
D 26
 * that happen to exist in segments of a partitioned network when the 
E 26
I 26
 * that happen to exist in segments of a partitioned network when the
E 26
 * network partition is fixed.
 *
 * Authors: Riccardo Gusella & Stefano Zatti
I 26
 *
 * overhauled at Silicon Graphics
E 26
D 5
 *
 * For problems and suggestions, please send mail to gusella@BERKELEY
E 5
 */
D 26

E 26
I 26
int
E 26
main(argc, argv)
D 26
int argc;
char **argv;
E 26
I 26
	int argc;
	char *argv[];
E 26
{
	int on;
	int ret;
D 26
	long seed;
E 26
D 8
	int Mflag;
E 8
D 9
	int nflag;
D 2
	char mastername[32];
E 2
I 2
D 8
	char mastername[MAXHOSTNAMELEN];
E 8
E 2
	char *netname;
E 9
I 9
	int nflag, iflag;
E 9
D 26
	struct timeval time;
E 26
I 26
	struct timeval ntime;
E 26
	struct servent *srvp;
D 9
	struct netent *getnetent();
	struct netent *localnet;
E 9
D 8
	struct sockaddr_in masteraddr;
E 8
D 13
	struct tsp resp, conflict, *answer, *readmsg(), *acksend();
E 13
D 26
	long casual();
D 5
	char *malloc(), *strcpy();
E 5
	char *date();
D 2
	struct in_addr inet_makeaddr();
E 2
I 2
	int n;
D 5
	int n_addrlen;
	char *n_addr;
E 5
I 5
	int flag;
E 26
E 5
D 22
	char buf[BUFSIZ];
E 22
I 22
	char buf[BUFSIZ], *cp, *cplim;
E 22
	struct ifconf ifc;
D 26
	struct ifreq ifreq, *ifr;
E 26
I 26
	struct ifreq ifreq, ifreqf, *ifr;
E 26
D 5
	struct sockaddr_in *sin;
E 5
I 5
	register struct netinfo *ntp;
	struct netinfo *ntip;
I 8
	struct netinfo *savefromnet;
I 26
	struct netent *nentp;
	struct nets *nt;
E 26
E 8
D 28
	struct sockaddr_in server;
E 28
I 28
	static struct sockaddr_in server;
E 28
	u_short port;
D 13
	int havemaster = 0;
E 13
I 13
D 26
	uid_t getuid();
E 26
I 26
	char c;
	extern char *optarg;
	extern int optind, opterr;
#ifdef sgi
	FILE *timetrim_st;
#endif
E 26
E 13
E 5
D 8
	
E 8
I 8

I 26
#define	IN_MSG "timed: -i and -n make no sense together\n"
#ifdef sgi
	struct tms tms;
#define USAGE "timed: [-dtM] [-i net|-n net] [-F host1 host2 ...] [-G netgp] [-P trimfile]\n"
#else
#ifdef HAVENIS
#define USAGE "timed: [-dtM] [-i net|-n net] [-F host1 host2 ...] [-G netgp]\n"
#else
#define USAGE "timed: [-dtM] [-i net|-n net] [-F host1 host2 ...]\n"
#endif /* HAVENIS */
#endif /* sgi */

E 26
E 8
I 5
#ifdef lint
	ntip = NULL;
#endif
E 5
E 2

D 3
	Mflag = SLAVE;
E 3
I 3
D 26
	Mflag = 0;
E 26
E 3
	on = 1;
D 26
	backoff = 1;
D 5
	fj = "/usr/adm/timed.log";
E 5
	trace = OFF;
E 26
	nflag = OFF;
I 9
	iflag = OFF;
E 9
I 2
D 10
	openlog("timed", LOG_ODELAY, LOG_DAEMON);
E 10
I 10
D 26
	openlog("timed", LOG_CONS|LOG_PID, LOG_DAEMON);
E 26
E 10
E 2

D 26
	if (getuid() != 0) {
D 2
		printf("Sorry: need to be root\n");
E 2
I 2
		fprintf(stderr, "Timed: not superuser\n");
E 2
		exit(1);
E 26
I 26
#ifdef sgi
	if (0 > syssgi(SGI_GETTIMETRIM, &timetrim)) {
		perror("timed: syssgi(GETTIMETRIM)");
		timetrim = 0;
E 26
	}
I 26
	tot_ticks = hr_ticks = times(&tms);
#endif /* sgi */
E 26

D 26
	while (--argc > 0 && **++argv == '-') {
		(*argv)++;
		do {
			switch (**argv) {
E 26
I 26
	opterr = 0;
	while ((c = getopt(argc, argv, "Mtdn:i:F:G:P:")) != EOF) {
		switch (c) {
		case 'M':
			Mflag = 1;
			break;
E 26

D 26
			case 'M':
D 3
				Mflag = MASTER; 
E 3
I 3
				Mflag = 1; 
E 3
				break;
			case 't':
				trace = ON; 
D 2
				fd = fopen(fj, "w");
				fprintf(fd, "Tracing started on: %s\n\n", 
							date());
				(void)fflush(fd);
E 2
				break;
			case 'n':
				argc--, argv++;
D 9
				nflag = ON;
				netname = *argv;
E 9
I 9
				if (iflag) {
					fprintf(stderr,
				    "timed: -i and -n make no sense together\n");
				} else {
					nflag = ON;
D 13
					addnetname(*argv, &nets);
E 13
I 13
					addnetname(*argv);
E 26
I 26
		case 't':
			trace = 1;
			break;

		case 'n':
			if (iflag) {
				fprintf(stderr, IN_MSG);
				exit(1);
			} else {
				nflag = ON;
				addnetname(optarg);
			}
			break;

		case 'i':
			if (nflag) {
				fprintf(stderr, IN_MSG);
				exit(1);
			} else {
				iflag = ON;
				addnetname(optarg);
			}
			break;

		case 'F':
			add_good_host(optarg,1);
			while (optind < argc && argv[optind][0] != '-')
				add_good_host(argv[optind++], 1);
			break;

		case 'd':
			debug = 1;
			break;
		case 'G':
			if (goodgroup != 0) {
				fprintf(stderr,"timed: only one net group\n");
				exit(1);
			}
			goodgroup = optarg;
			break;
#ifdef sgi
		case 'P':
			timetrim_fn = optarg;
D 28
			timetrim_st = fopen(timetrim_fn, "r+");
			if (0 == timetrim_st) {
				if (errno != ENOENT) {
					(void)fprintf(stderr,"timed: ");
					perror(timetrim_fn);
					timetrim_fn = 0;
E 26
E 13
				}
E 9
D 26
				while (*(++(*argv)+1)) ;
				break;
I 9
			case 'i':
				argc--, argv++;
				if (nflag) {
					fprintf(stderr,
				    "timed: -i and -n make no sense together\n");
E 26
I 26
			} else {
				int i;
				long trim;
				double adj, ticks;

				i = fscanf(timetrim_st, timetrim_rpat,
					   &trim, &adj, &ticks);
				if (i < 1
				    || trim > MAX_TRIM
				    || trim < -MAX_TRIM
				    || i == 2
				    || (i == 3
					&& trim != rint(adj*CLK_TCK/ticks))) {
					if (trace && i != EOF)
						(void)fprintf(stderr,
				    "timed: unrecognized contents in %s\n",
							      timetrim_fn);
E 26
				} else {
D 26
					iflag = ON;
D 13
					addnetname(*argv, &nets);
E 13
I 13
					addnetname(*argv);
E 26
I 26
					if (0 > syssgi(SGI_SETTIMETRIM,
						       trim)) {
					 perror("timed: syssgi(SETTIMETRIM)");
					} else {
						timetrim = trim;
					}
					if (i == 3) {
						tot_adj = adj;
						tot_ticks -= ticks;
					}
E 26
E 13
				}
D 26
				while (*(++(*argv)+1)) ;
				break;
E 9
			default:
				fprintf(stderr, "timed: -%c: unknown option\n", 
							**argv);
				break;
E 26
I 26
				(void)fclose(timetrim_st);
E 26
			}
E 28
D 26
		} while (*++(*argv));
E 26
I 26
			break;
#endif /* sgi */

		default:
			fprintf(stderr, USAGE);
			exit(1);
			break;
		}
E 26
	}
I 26
	if (optind < argc) {
		fprintf(stderr, USAGE);
		exit(1);
	}
E 26

I 28
#ifdef sgi
	if (timetrim_fn == 0) {
		;
	} else if (0 == (timetrim_st = fopen(timetrim_fn, "r+"))) {
		if (errno != ENOENT) {
			(void)fprintf(stderr,"timed: ");
			perror(timetrim_fn);
			timetrim_fn = 0;
		}
	} else {
		int i;
		long trim;
		double adj, ticks;

		i = fscanf(timetrim_st, timetrim_rpat,
			   &trim, &adj, &ticks);
		if (i < 1
		    || trim > MAX_TRIM
		    || trim < -MAX_TRIM
		    || i == 2
		    || (i == 3
			&& trim != rint(adj*CLK_TCK/ticks))) {
			if (trace && i != EOF)
				(void)fprintf(stderr,
		    "timed: unrecognized contents in %s\n",
					      timetrim_fn);
		} else {
			if (0 > syssgi(SGI_SETTIMETRIM,
				       trim)) {
			 perror("timed: syssgi(SETTIMETRIM)");
			} else {
				timetrim = trim;
			}
			if (i == 3)
				tot_ticks -= ticks;
		}
		(void)fclose(timetrim_st);
	}
#endif /* sgi */

E 28
I 2
D 11
D 26
#ifndef DEBUG
D 24
	if (fork())
		exit(0);
	{ int s;
D 5
	  for (s = 0; s < 10; s++)
E 5
I 5
	  for (s = getdtablesize(); s >= 0; --s)
E 5
		(void) close(s);
D 5
	  (void) open("/", 0);
E 5
I 5
D 20
	  (void) open("/dev/null", 0);
E 20
I 20
	  (void) open(_PATH_DEVNULL, 0);
E 20
E 5
	  (void) dup2(0, 1);
	  (void) dup2(0, 2);
D 20
	  s = open("/dev/tty", 2);
E 20
I 20
	  s = open(_PATH_TTY, 2);
E 20
	  if (s >= 0) {
D 14
		(void) ioctl(s, (int)TIOCNOTTY, (char *)0);
E 14
I 14
		(void) ioctl(s, TIOCNOTTY, (char *)0);
E 14
		(void) close(s);
	  }
	}
E 24
I 24
	daemon(0, 0);
E 24
#endif
E 26
I 26
	/* If we care about which machine is the master, then we must
	 *	be willing to be a master
	 */
	if (0 != goodgroup || 0 != goodhosts)
		Mflag = 1;
E 26

E 11
D 26
	if (trace == ON) {
D 5
		fd = fopen(fj, "w");
E 5
I 5
		fd = fopen(tracefile, "w");
		setlinebuf(fd);
E 5
		fprintf(fd, "Tracing started on: %s\n\n", 
					date());
E 26
I 26
	if (gethostname(hostname, sizeof(hostname) - 1) < 0) {
		perror("gethostname");
		exit(1);
E 26
D 5
		(void)fflush(fd);
E 5
	}
I 26
	self.l_bak = &self;
	self.l_fwd = &self;
	self.h_bak = &self;
	self.h_fwd = &self;
	self.head = 1;
	self.good = 1;
E 26
D 10
	openlog("timed", LOG_ODELAY|LOG_CONS, LOG_DAEMON);
E 10

I 26
	if (goodhosts != 0)		/* trust ourself */
		add_good_host(hostname,1);

E 26
E 2
	srvp = getservbyname("timed", "udp");
	if (srvp == 0) {
D 2
		syslog(LOG_ERR, "udp/timed: unknown service\n");
E 2
I 2
D 26
		syslog(LOG_CRIT, "unknown service 'timed/udp'");
E 26
I 26
		fprintf(stderr, "unknown service 'timed/udp'\n");
E 26
E 2
		exit(1);
	}
I 5
	port = srvp->s_port;
I 28
	server.sin_addr.s_addr = INADDR_ANY;
E 28
E 5
	server.sin_port = srvp->s_port;
	server.sin_family = AF_INET;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
D 2
		syslog(LOG_ERR, "timed: opening socket\n");
E 2
I 2
D 26
		syslog(LOG_ERR, "socket: %m");
E 26
I 26
		perror("socket");
E 26
E 2
		exit(1);
	}
D 26
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&on, 
E 26
I 26
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&on,
E 26
							sizeof(on)) < 0) {
D 2
		syslog(LOG_ERR, "timed: setsockopt");
E 2
I 2
D 26
		syslog(LOG_ERR, "setsockopt: %m");
E 26
I 26
		perror("setsockopt");
E 26
E 2
		exit(1);
	}
D 25
	if (bind(sock, &server, sizeof(server))) {
E 25
I 25
D 26
	if (bind(sock, (struct sockaddr *)&server, sizeof(server))) {
E 26
I 26
	if (bind(sock, (struct sockaddr*)&server, sizeof(server))) {
E 26
E 25
		if (errno == EADDRINUSE)
D 2
			fprintf(stderr, "timed already running\n");
E 2
I 2
D 26
		        syslog(LOG_ERR, "server already running");
E 26
I 26
			fprintf(stderr,"timed: time daemon already running\n");
E 26
E 2
		else
D 2
			syslog(LOG_ERR, "timed: bind");
E 2
I 2
D 26
		        syslog(LOG_ERR, "bind: %m");
E 26
I 26
			perror("bind");
E 26
E 2
		exit(1);
	}
I 26
#ifdef sgi
	/*
	 * handle many slaves with our buffer
	 */
	if (0 > setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&bufspace,
			 sizeof(bufspace))) {
		perror("setsockopt");
		exit(1);
	}
#endif /* sgi */
E 26

	/* choose a unique seed for random number generation */
D 26
	(void)gettimeofday(&time, (struct timezone *)0);
	seed = time.tv_sec + time.tv_usec;
	srandom(seed);
E 26
I 26
	(void)gettimeofday(&ntime, 0);
	srandom(ntime.tv_sec + ntime.tv_usec);
E 26

D 12
	sequence = casual((long)1, (long)MAXSEQ);     /* initial seq number */
E 12
I 12
	sequence = random();     /* initial seq number */
E 12

I 26
#ifndef sgi
E 26
	/* rounds kernel variable time to multiple of 5 ms. */
D 26
	time.tv_sec = 0;
	time.tv_usec = -((time.tv_usec/1000) % 5) * 1000;
	(void)adjtime(&time, (struct timeval *)0);
E 26
I 26
	ntime.tv_sec = 0;
	ntime.tv_usec = -((ntime.tv_usec/1000) % 5) * 1000;
	(void)adjtime(&ntime, (struct timeval *)0);
#endif /* sgi */
E 26

D 26
	id = getpid();
E 26
I 26
	for (nt = nets; nt; nt = nt->next) {
		nentp = getnetbyname(nt->name);
		if (nentp == 0) {
			nt->net = inet_network(nt->name);
			if (nt->net != INADDR_NONE)
				nentp = getnetbyaddr(nt->net, AF_INET);
		}
		if (nentp != 0) {
			nt->net = nentp->n_net;
		} else if (nt->net == INADDR_NONE) {
			fprintf(stderr, "timed: unknown net %s\n", nt->name);
			exit(1);
		} else if (nt->net == INADDR_ANY) {
			fprintf(stderr, "timed: bad net %s\n", nt->name);
			exit(1);
		} else {
			fprintf(stderr,
				"timed: warning: %s unknown in /etc/networks\n",
				nt->name);
		}
E 26

D 26
	if (gethostname(hostname, sizeof(hostname) - 1) < 0) {
D 2
		syslog(LOG_ERR, "timed: gethostname: %m");
E 2
I 2
		syslog(LOG_ERR, "gethostname: %m");
E 2
		exit(1);
E 26
I 26
		if (0 == (nt->net & 0xff000000))
		    nt->net <<= 8;
		if (0 == (nt->net & 0xff000000))
		    nt->net <<= 8;
		if (0 == (nt->net & 0xff000000))
		    nt->net <<= 8;
E 26
	}
D 26
	hp[0].name = hostname;

D 9
	if (nflag) {
		localnet = getnetbyname(netname);
		if (localnet == NULL) {
D 2
			syslog(LOG_ERR, "timed: getnetbyname: %m");
E 2
I 2
			syslog(LOG_ERR, "getnetbyname: unknown net %s",
				netname);
E 2
			exit(1);
E 9
I 9
	if (nflag || iflag) {
		struct netent *getnetent();
		struct netent *n;
		struct nets *np;
		for ( np = nets ; np ; np = np->next) {
			n = getnetbyname(np->name);
			if (n == NULL) {
				syslog(LOG_ERR, "getnetbyname: unknown net %s",
					np->name);
				exit(1);
			}
			np->net = n->n_net;
E 9
		}
D 2
		if (localnet == NULL) {
			syslog(LOG_ERR, "timed: no network: %m");
			exit(1);
E 2
I 2
	}
E 26
	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = buf;
D 13
	if (ioctl(sock, (int)SIOCGIFCONF, (char *)&ifc) < 0) {
E 13
I 13
	if (ioctl(sock, SIOCGIFCONF, (char *)&ifc) < 0) {
E 13
D 26
		syslog(LOG_ERR, "get interface configuration: %m");
E 26
I 26
		perror("timed: get interface configuration");
E 26
		exit(1);
	}
D 5
	ifr = ifc.ifc_req;
	for (n = ifc.ifc_len/sizeof(struct ifreq); n > 0; n--, ifr++) {
E 5
I 5
D 22
	n = ifc.ifc_len/sizeof(struct ifreq);
E 22
	ntp = NULL;
D 22
	for (ifr = ifc.ifc_req; n > 0; n--, ifr++) {
E 22
I 22
D 23
#ifdef RTM_ADD
E 23
D 26
#define max(a, b) (a > b ? a : b)
E 26
I 26
#ifdef sgi
#define size(p)	(sizeof(*ifr) - sizeof(ifr->ifr_name))  /* XXX hack. kludge */
#else
E 26
#define size(p)	max((p).sa_len, sizeof(p))
I 26
#endif
E 26
D 23
#else
#define size(p) (sizeof (p))
#endif
E 23
	cplim = buf + ifc.ifc_len; /*skip over if's with big ifr_addr's */
	for (cp = buf; cp < cplim;
			cp += sizeof (ifr->ifr_name) + size(ifr->ifr_addr)) {
		ifr = (struct ifreq *)cp;
E 22
		if (ifr->ifr_addr.sa_family != AF_INET)
			continue;
I 26
		if (!ntp)
			ntp = (struct netinfo*)malloc(sizeof(struct netinfo));
		bzero(ntp,sizeof(*ntp));
		ntp->my_addr=((struct sockaddr_in *)&ifr->ifr_addr)->sin_addr;
		ntp->status = NOMASTER;
E 26
E 5
		ifreq = *ifr;
I 5
D 26
		if (ntp == NULL)
			ntp = (struct netinfo *)malloc(sizeof(struct netinfo));
		ntp->my_addr = 
			((struct sockaddr_in *)&ifreq.ifr_addr)->sin_addr;
E 5
D 13
		if (ioctl(sock, (int)SIOCGIFFLAGS, 
E 13
I 13
		if (ioctl(sock, SIOCGIFFLAGS, 
E 13
					(char *)&ifreq) < 0) {
			syslog(LOG_ERR, "get interface flags: %m");
E 26
I 26
		ifreqf = *ifr;

		if (ioctl(sock, SIOCGIFFLAGS, (char *)&ifreqf) < 0) {
			perror("get interface flags");
E 26
			continue;
E 2
		}
D 2
		broadcastaddr = inet_makeaddr(localnet->n_net,INADDR_BROADCAST);
	} else {
		int n;
		int n_addrlen;
		char *n_addr;
		char buf[BUFSIZ];
		struct ifconf ifc;
		struct ifreq ifreq, *ifr;
		struct sockaddr_in *sin;
	
		ifc.ifc_len = sizeof(buf);
		ifc.ifc_buf = buf;
		if (ioctl(sock, (int)SIOCGIFCONF, (char *)&ifc) < 0) {
			syslog(LOG_ERR, "timed: (get interface configuration)");
			exit(1);
E 2
I 2
D 26
		if ((ifreq.ifr_flags & IFF_UP) == 0 ||
D 5
			(ifreq.ifr_flags & IFF_BROADCAST) == 0) {
E 5
I 5
			((ifreq.ifr_flags & IFF_BROADCAST) == 0 &&
			(ifreq.ifr_flags & IFF_POINTOPOINT) == 0)) {
E 26
I 26
		if ((ifreqf.ifr_flags & IFF_UP) == 0)
E 26
E 5
			continue;
I 26
		if ((ifreqf.ifr_flags & IFF_BROADCAST) == 0 &&
		    (ifreqf.ifr_flags & IFF_POINTOPOINT) == 0) {
			continue;
E 26
E 2
		}
I 5
D 26
		if (ifreq.ifr_flags & IFF_BROADCAST)
			flag = 1;
		else
			flag = 0;
E 5
D 2
		ifr = ifc.ifc_req;
		for (n = ifc.ifc_len/sizeof(struct ifreq); n > 0; n--, ifr++) {
			ifreq = *ifr;
			if (ioctl(sock, (int)SIOCGIFFLAGS, 
						(char *)&ifreq) < 0) {
				syslog(LOG_ERR, "timed: (get interface flags)");
				continue;
E 2
I 2
D 13
		if (ioctl(sock, (int)SIOCGIFNETMASK, 
E 13
I 13
		if (ioctl(sock, SIOCGIFNETMASK, 
E 13
					(char *)&ifreq) < 0) {
D 5
			syslog(LOG_ERR, "get broadaddr: %m");
E 5
I 5
			syslog(LOG_ERR, "get netmask: %m");
E 26
I 26


		if (ioctl(sock, SIOCGIFNETMASK, (char *)&ifreq) < 0) {
			perror("get netmask");
E 26
E 5
			continue;
		}
D 5
		netmask = ((struct sockaddr_in *)
E 5
I 5
		ntp->mask = ((struct sockaddr_in *)
E 5
			&ifreq.ifr_addr)->sin_addr.s_addr;
D 5
		if (ioctl(sock, (int)SIOCGIFBRDADDR, 
					(char *)&ifreq) < 0) {
			syslog(LOG_ERR, "get broadaddr: %m");
			continue;
E 5
I 5
D 26
		if (flag) {
D 13
			if (ioctl(sock, (int)SIOCGIFBRDADDR, 
E 13
I 13
			if (ioctl(sock, SIOCGIFBRDADDR, 
E 13
						(char *)&ifreq) < 0) {
				syslog(LOG_ERR, "get broadaddr: %m");
E 26
I 26

		if (ifreqf.ifr_flags & IFF_BROADCAST) {
			if (ioctl(sock, SIOCGIFBRDADDR, (char *)&ifreq) < 0) {
				perror("get broadaddr");
E 26
				continue;
			}
			ntp->dest_addr = *(struct sockaddr_in *)&ifreq.ifr_broadaddr;
I 26
			/* What if the broadcast address is all ones?
			 * So we cannot just mask ntp->dest_addr.  */
			ntp->net = ntp->my_addr;
			ntp->net.s_addr &= ntp->mask;
E 26
		} else {
D 13
			if (ioctl(sock, (int)SIOCGIFDSTADDR, 
E 13
I 13
D 26
			if (ioctl(sock, SIOCGIFDSTADDR, 
E 26
I 26
			if (ioctl(sock, SIOCGIFDSTADDR,
E 26
E 13
						(char *)&ifreq) < 0) {
D 26
				syslog(LOG_ERR, "get destaddr: %m");
E 26
I 26
				perror("get destaddr");
E 26
				continue;
			}
			ntp->dest_addr = *(struct sockaddr_in *)&ifreq.ifr_dstaddr;
I 26
			ntp->net = ntp->dest_addr.sin_addr;
E 26
E 5
		}
I 26

E 26
D 5
		n_addrlen = sizeof(ifr->ifr_addr);
		n_addr = (char *)malloc((unsigned)n_addrlen);
		bcopy((char *)&ifreq.ifr_broadaddr, n_addr, n_addrlen);
		sin = (struct sockaddr_in *)n_addr;
		broadcastaddr = sin->sin_addr;
E 5
I 5
		ntp->dest_addr.sin_port = port;
E 5
D 9
		if (nflag) {
E 9
I 9
D 26
		if (nflag || iflag) {
E 9
			u_long addr, mask;
I 9
			struct nets *n;
E 26
E 9

D 5
			addr = ntohl(broadcastaddr.s_addr);
			mask = ntohl(netmask);
E 5
I 5
D 26
			addr = ntohl(ntp->dest_addr.sin_addr.s_addr);
			mask = ntohl(ntp->mask);
E 5
			while ((mask & 1) == 0) {
				addr >>= 1;
				mask >>= 1;
E 2
			}
D 2
			if ((ifreq.ifr_flags & IFF_UP) == 0 ||
		    		(ifreq.ifr_flags & IFF_BROADCAST) == 0) {
E 2
I 2
D 9
			if (addr != localnet->n_net)
E 9
I 9
			for (n = nets ; n ; n = n->next)
				if (addr == n->net)
					break;
			if (nflag && !n || iflag && n)
E 9
E 2
				continue;
E 26
I 26
		for (nt = nets; nt; nt = nt->next) {
			if (ntp->net.s_addr == nt->net)
				break;
E 26
D 2
			}
			if (ioctl(sock, (int)SIOCGIFBRDADDR, 
						(char *)&ifreq) < 0) {
				syslog(LOG_ERR, "timed: (get broadaddr)");
				continue;
			}
			n_addrlen = sizeof(ifr->ifr_addr);
			n_addr = (char *)malloc((unsigned)n_addrlen);
			bcopy((char *)&ifreq.ifr_broadaddr, n_addr, n_addrlen);
			sin = (struct sockaddr_in *)n_addr;
			broadcastaddr = sin->sin_addr;
			break;
E 2
		}
I 2
D 5
		mynet = netmask & broadcastaddr.s_addr;
		break;
E 5
I 5
D 26
		ntp->net = ntp->mask & ntp->dest_addr.sin_addr.s_addr;
E 26
I 26
		if (nflag && !nt || iflag && nt)
			continue;

E 26
		ntp->next = NULL;
		if (nettab == NULL) {
			nettab = ntp;
		} else {
			ntip->next = ntp;
		}
		ntip = ntp;
		ntp = NULL;
E 5
E 2
	}
I 2
D 5
	if (!mynet) {
E 5
I 5
	if (ntp)
		(void) free((char *)ntp);
	if (nettab == NULL) {
E 5
D 26
		syslog(LOG_ERR, "No network usable");
E 26
I 26
		fprintf(stderr, "timed: no network usable\n");
E 26
		exit(1);
	}
E 2

I 5
D 8
	for(ntp = nettab; ntp != NULL; ntp = ntp->next) {
		/* look for master */
		resp.tsp_type = TSP_MASTERREQ;
		(void)strcpy(resp.tsp_name, hostname);
		answer = acksend(&resp, &ntp->dest_addr, (char *)ANYADDR, 
		    TSP_MASTERACK, ntp);
		if (answer == NULL) {
			/*
			 * Various conditions can cause conflict: race between
			 * two just started timedaemons when no master is
			 * present, or timedaemon started during an election.
			 * Conservative approach is taken: give up and became a
			 * slave postponing election of a master until first
			 * timer expires.
			 */
			time.tv_sec = time.tv_usec = 0;
			answer = readmsg(TSP_MASTERREQ, (char *)ANYADDR,
			    &time, ntp);
			if (answer != NULL) {
				if (!havemaster) {
					ntp->status = SLAVE;
					status |= SLAVE;
					havemaster++;
				} else
					ntp->status = IGNORE;
				continue;
			}
	
			time.tv_sec = time.tv_usec = 0;
			answer = readmsg(TSP_MASTERUP, (char *)ANYADDR,
			    &time, ntp);
			if (answer != NULL) {
				if (!havemaster) {
					ntp->status = SLAVE;
					status |= SLAVE;
					havemaster++;
				} else
					ntp->status = IGNORE;
				continue;
			}
	
			time.tv_sec = time.tv_usec = 0;
			answer = readmsg(TSP_ELECTION, (char *)ANYADDR,
			    &time, ntp);
			if (answer != NULL) {
				if (!havemaster) {
					ntp->status = SLAVE;
					status |= SLAVE;
					havemaster++;
				} else
					ntp->status = IGNORE;
				continue;
			}
			ntp->status = MASTER;
			status |= MASTER;
		} else {
			if (!havemaster) {
				ntp->status = SLAVE;
				status |= SLAVE;
				havemaster++;
			} else
				ntp->status = IGNORE;
			(void)strcpy(mastername, answer->tsp_name);
			masteraddr = from;

			/*
			 * If network has been partitioned, there might be other
			 * masters; tell the one we have just acknowledged that 
			 * it has to gain control over the others. 
			 */
			time.tv_sec = 0;
			time.tv_usec = 300000;
			answer = readmsg(TSP_MASTERACK, (char *)ANYADDR, &time,
			    ntp);
			/*
			 * checking also not to send CONFLICT to ack'ed master
			 * due to duplicated MASTERACKs
			 */
			if (answer != NULL && 
			    strcmp(answer->tsp_name, mastername) != 0) {
				conflict.tsp_type = TSP_CONFLICT;
				(void)strcpy(conflict.tsp_name, hostname);
				if (acksend(&conflict, &masteraddr, mastername,
				    TSP_ACK, (struct netinfo *)NULL) == NULL) {
					syslog(LOG_ERR, 
					    "error on sending TSP_CONFLICT");
					exit(1);
				}
			}
		}
	}
E 8
I 8
D 26
	for (ntp = nettab; ntp != NULL; ntp = ntp->next)
		lookformaster(ntp);
	setstatus();
	/*
	 * Take care of some basic initialization.
	 */
E 8
E 5
	/* us. delay to be used in response to broadcast */
	delay1 = casual((long)10000, 200000);	
E 26

I 26
#ifdef sgi
	(void)schedctl(RENICE,0,10);	   /* run fast to get good time */

	/* ticks to delay before responding to a broadcast */
	delay1 = casual(0, CLK_TCK/10);
#else

	/* microseconds to delay before responding to a broadcast */
	delay1 = casual(1, 100*1000);
#endif /* sgi */

E 26
	/* election timer delay in secs. */
D 26
	delay2 = casual((long)MINTOUT, (long)MAXTOUT);
E 26
I 26
	delay2 = casual(MINTOUT, MAXTOUT);
E 26
I 11
#ifndef DEBUG
	if (fork())
		exit(0);
	{ int s;
	  for (s = getdtablesize(); s >= 0; --s)
		(void) close(s);
	  (void) open("/dev/null", 0);
	  (void) dup2(0, 1);
	  (void) dup2(0, 2);
	  s = open("/dev/tty", 2);
	  if (s >= 0) {
D 13
		(void) ioctl(s, (int)TIOCNOTTY, (char *)0);
E 13
I 13
D 14
		(void) ioctl(s, TIOCNOTTY, (char *)0);
E 14
E 13
		(void) close(s);
	  }
	}
#endif
E 11

I 11

E 11
D 5
	/* look for master */
	resp.tsp_type = TSP_MASTERREQ;
	(void)strcpy(resp.tsp_name, hostname);
	answer = acksend(&resp, (char *)ANYADDR, TSP_MASTERACK);
	if (answer == NULL) {
		status = MASTER;
	} else {
		status = SLAVE;
		(void)strcpy(mastername, answer->tsp_name);
		masteraddr = from;

		/*
		 * If network has been partitioned, there might be other
		 * masters; tell the one we have just acknowledged that 
		 * it has to gain control over the others. 
		 */
		time.tv_sec = 0;
		time.tv_usec = 300000;
		answer = readmsg(TSP_MASTERACK, (char *)ANYADDR, &time);
		/*
		 * checking also not to send CONFLICT to ack'ed master
		 * due to duplicated MASTERACKs
		 */
		if (answer != NULL && 
				strcmp(answer->tsp_name, mastername) != 0) {
			conflict.tsp_type = TSP_CONFLICT;
			(void)strcpy(conflict.tsp_name, hostname);
			server = masteraddr;
			if (acksend(&conflict, (char *)mastername, 
							TSP_ACK) == NULL) {
D 2
				syslog(LOG_ERR, "timed: error on sending TSP_CONFLICT\n");
E 2
I 2
				syslog(LOG_ERR, "error on sending TSP_CONFLICT");
E 2
				exit(1);
			}
		}
	}
E 5
D 26
	if (Mflag) {
D 15
		/* open raw socket used to measure time differences */
		sock_raw = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP); 
		if (sock_raw < 0)  {
D 2
			fprintf(stderr, "timed: opening raw socket");
E 2
I 2
			syslog(LOG_ERR, "opening raw socket: %m");
E 2
			exit (1);
		}

E 15
		/*
		 * number (increased by 1) of slaves controlled by master: 
		 * used in master.c, candidate.c, networkdelta.c, and 
		 * correct.c 
		 */
		slvcount = 1;
D 8

E 8
D 5
		/*
		 * Various conditions can cause conflict: race between
		 * two just started timedaemons when no master is present,
		 * or timedaemon started during an election.
		 * Conservative approach is taken: give up and became a
		 * slave postponing election of a master until first
		 * timer expires.
		 */
		if (status == MASTER) {
			time.tv_sec = time.tv_usec = 0;
			answer = readmsg(TSP_MASTERREQ, (char *)ANYADDR, &time);
			if (answer != NULL) {
				status = SLAVE;
				goto startd;
			}
	
			time.tv_sec = time.tv_usec = 0;
			answer = readmsg(TSP_MASTERUP, (char *)ANYADDR, &time);
			if (answer != NULL) {
				status = SLAVE;
				goto startd;
			}
	
			time.tv_sec = time.tv_usec = 0;
			answer = readmsg(TSP_ELECTION, (char *)ANYADDR, &time);
			if (answer != NULL) 
				status = SLAVE;
		}
startd:
E 5
		ret = setjmp(jmpenv);
E 26
I 8

I 26
#ifdef sgi
	(void)_daemonize(debug ? _DF_NOFORK|_DF_NOCHDIR : 0, sock, -1, -1);
#else
	if (!debug)
		daemon(debug, 0);
#endif /* sgi */

	if (trace)
		traceon();
	openlog("timed", LOG_CONS|LOG_PID, LOG_DAEMON);

	/*
	 * keep returning here
	 */
	ret = setjmp(jmpenv);
	savefromnet = fromnet;
	setstatus();

	if (Mflag) {
E 26
E 8
		switch (ret) {

D 26
		case 0: 
I 8
			makeslave(firstslavenet());
			setstatus();
E 26
I 26
		case 0:
			checkignorednets();
			pickslavenet(0);
E 26
E 8
			break;
D 26
		case 1: 
E 26
I 26
		case 1:
E 26
D 8
			/* from slave */
D 5
			status = election();
E 5
I 5
			for (ntp = nettab; ntp != NULL; ntp = ntp->next) {
D 6
				if (ntp->status = SLAVE)
E 6
I 6
				if (ntp->status == SLAVE)
E 6
					break;
			}
			ntp->status = election(ntp);
			status = 0;
			for (ntp = nettab; ntp != NULL; ntp = ntp->next) {
				status |= ntp->status;
			}
			status &= ~IGNORE;
E 8
I 8
			/* Just lost our master */
D 26
			setstatus();
			slavenet->status = election(slavenet);
			checkignorednets();
			setstatus();
			if (slavenet->status == MASTER)
				makeslave(firstslavenet());
			else
				makeslave(slavenet);
			setstatus();
E 26
I 26
			if (slavenet != 0)
				slavenet->status = election(slavenet);
			if (!slavenet || slavenet->status == MASTER) {
				checkignorednets();
				pickslavenet(0);
			} else {
				makeslave(slavenet);	/* prune extras */
			}
E 26
E 8
E 5
			break;
I 26

E 26
		case 2:
D 8
			/* from master */
D 5
			status = SLAVE;
E 5
I 5
			havemaster = 0;
			for (ntp = nettab; ntp != NULL; ntp = ntp->next) {
				if ((from.sin_addr.s_addr & ntp->mask) ==
				    ntp->net) {
					ntp->status = SLAVE;
I 7
					rmnetmachs(ntp);
E 7
					break;
				}
			}
			status = 0;
			for (ntp = nettab; ntp != NULL; ntp = ntp->next) {
				status |= ntp->status;
			}
			status &= ~IGNORE;
E 8
I 8
			/* Just been told to quit */
D 26
			fromnet->status = SLAVE;
			setstatus();
			savefromnet = fromnet;
			rmnetmachs(fromnet);
			checkignorednets();
			if (slavenet)
				makeslave(slavenet);
			else
				makeslave(savefromnet);
			setstatus();
E 26
I 10
			justquit = 1;
I 26
			pickslavenet(savefromnet);
E 26
E 10
E 8
E 5
			break;
I 8
D 26
			
E 8
		default:
			/* this should not happen */
D 2
			syslog(LOG_ERR, 
				"timed: error on return from longjmp\n");
E 2
I 2
			syslog(LOG_ERR, "Attempt to enter invalid state");
E 2
			break;
E 26
		}
D 26
			
I 15
		if (status & MASTER) {
			/* open raw socket used to measure time differences */
			if (sock_raw == -1) {
			    sock_raw = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP); 
			    if (sock_raw < 0)  {
				    syslog(LOG_ERR, "opening raw socket: %m");
				    exit (1);
			    }
			}
		} else {
E 26
I 26

		setstatus();
		if (!(status & MASTER) && sock_raw != -1) {
E 26
			/* sock_raw is not being used now */
D 26
			if (sock_raw != -1) {
			    (void)close(sock_raw);
			    sock_raw = -1;
			}
E 26
I 26
			(void)close(sock_raw);
			sock_raw = -1;
E 26
		}

E 15
D 2
		if (status) 
E 2
I 2
D 26
		if (status == MASTER) 
E 26
I 26
		if (status == MASTER)
E 26
E 2
			master();
D 26
		else 
E 26
I 26
		else
E 26
			slave();
I 26

E 26
	} else {
I 2
D 5
		status = SLAVE;
E 5
E 2
D 26
		/* if Mflag is not set timedaemon is forced to act as a slave */
I 5
		status = SLAVE;
D 8
		ntip = NULL;
		for(ntp = nettab; ntp != NULL; ntp = ntp->next) {
			if (ntp->status & (SLAVE|MASTER)) {
				if (ntip == NULL) {
					ntip = ntp;
					ntp->status = SLAVE;
				} else {
					ntp->status = IGNORE;
				}
			}
		}
E 8
I 8
D 11
D 14
		makeslave(firstslavenet());
E 14
E 11
E 8
E 5
		if (setjmp(jmpenv)) {
D 8
			resp.tsp_type = TSP_SLAVEUP;
I 5
			resp.tsp_vers = TSPVERSION;
E 5
			(void)strcpy(resp.tsp_name, hostname);
D 5
			broadcast(&resp);
E 5
I 5
			bytenetorder(&resp);
			if (sendto(sock, (char *)&resp, sizeof(struct tsp), 0,
			    &ntip->dest_addr, sizeof(struct sockaddr_in)) < 0) {
				syslog(LOG_ERR, "sendto: %m");
E 8
I 8
			setstatus();
			checkignorednets();
E 26
I 26
		if (sock_raw != -1) {
			(void)close(sock_raw);
			sock_raw = -1;
E 26
D 11
D 14
			makeslave(firstslavenet());
E 14
E 11
		}
I 14
D 26
		makeslave(firstslavenet());
E 14
I 11
		makeslave(firstslavenet());
E 11
		for (ntp = nettab; ntp != NULL; ntp = ntp->next)
E 26
I 26

		if (ret) {
			/* we just lost our master or were told to quit */
			justquit = 1;
		}
		for (ntp = nettab; ntp != NULL; ntp = ntp->next) {
E 26
			if (ntp->status == MASTER)
D 26
				ntp->status = IGNORE;
E 26
I 26
				rmnetmachs(ntp);
				ntp->status = NOMASTER;
		}
		checkignorednets();
		pickslavenet(0);
E 26
		setstatus();
I 26

E 26
		slave();
	}
I 26
	/* NOTREACHED */
#ifdef lint
	return(0);
#endif
E 26
}

/*
D 26
 * Try to become master over ignored nets..
E 26
I 26
 * suppress an upstart, untrustworthy, self-appointed master
E 26
 */
D 26
checkignorednets()
E 26
I 26
void
suppress(addr, name,net)
	struct sockaddr_in *addr;
	char *name;
	struct netinfo *net;
E 26
{
D 26
	register struct netinfo *ntp;
	for (ntp = nettab; ntp != NULL; ntp = ntp->next)
		if (ntp->status == IGNORE)
			lookformaster(ntp);
E 26
I 26
	struct sockaddr_in tgt;
	char tname[MAXHOSTNAMELEN];
	struct tsp msg;
	static struct timeval wait;

	if (trace)
		fprintf(fd, "suppress: %s\n", name);
	tgt = *addr;
	(void)strcpy(tname, name);

	while (0 != readmsg(TSP_ANY, ANYADDR, &wait, net)) {
		if (trace)
			fprintf(fd, "suppress:\tdiscarded packet from %s\n",
				    name);
	}

	syslog(LOG_NOTICE, "suppressing false master %s", tname);
	msg.tsp_type = TSP_QUIT;
	(void)strcpy(msg.tsp_name, hostname);
	(void)acksend(&msg, &tgt, tname, TSP_ACK, 0, 1);
E 26
}

I 26
void
E 26
lookformaster(ntp)
D 26
	register struct netinfo *ntp;
E 26
I 26
	struct netinfo *ntp;
E 26
{
D 26
	struct tsp resp, conflict, *answer, *readmsg(), *acksend();
	struct timeval time;
E 26
I 26
	struct tsp resp, conflict, *answer;
	struct timeval ntime;
E 26
	char mastername[MAXHOSTNAMELEN];
	struct sockaddr_in masteraddr;

I 26
	get_goodgroup(0);
E 26
	ntp->status = SLAVE;
I 26

E 26
	/* look for master */
	resp.tsp_type = TSP_MASTERREQ;
	(void)strcpy(resp.tsp_name, hostname);
D 26
	answer = acksend(&resp, &ntp->dest_addr, (char *)ANYADDR, 
	    TSP_MASTERACK, ntp);
	if (answer == NULL) {
E 26
I 26
	answer = acksend(&resp, &ntp->dest_addr, ANYADDR,
			 TSP_MASTERACK, ntp, 0);
	if (answer != 0 && !good_host_name(answer->tsp_name)) {
		suppress(&from, answer->tsp_name, ntp);
		ntp->status = NOMASTER;
		answer = 0;
	}
	if (answer == 0) {
E 26
		/*
D 26
		 * Various conditions can cause conflict: race between
E 26
I 26
		 * Various conditions can cause conflict: races between
E 26
		 * two just started timedaemons when no master is
D 26
		 * present, or timedaemon started during an election.
		 * Conservative approach is taken: give up and became a
		 * slave postponing election of a master until first
E 26
I 26
		 * present, or timedaemons started during an election.
		 * A conservative approach is taken.  Give up and became a
		 * slave, postponing election of a master until first
E 26
		 * timer expires.
		 */
D 26
		time.tv_sec = time.tv_usec = 0;
		answer = readmsg(TSP_MASTERREQ, (char *)ANYADDR,
		    &time, ntp);
		if (answer != NULL) {
			ntp->status = SLAVE;
E 26
I 26
		ntime.tv_sec = ntime.tv_usec = 0;
		answer = readmsg(TSP_MASTERREQ, ANYADDR, &ntime, ntp);
		if (answer != 0) {
			if (!good_host_name(answer->tsp_name)) {
				suppress(&from, answer->tsp_name, ntp);
				ntp->status = NOMASTER;
			}
E 26
			return;
		}

D 26
		time.tv_sec = time.tv_usec = 0;
		answer = readmsg(TSP_MASTERUP, (char *)ANYADDR,
		    &time, ntp);
		if (answer != NULL) {
			ntp->status = SLAVE;
E 26
I 26
		ntime.tv_sec = ntime.tv_usec = 0;
		answer = readmsg(TSP_MASTERUP, ANYADDR, &ntime, ntp);
		if (answer != 0) {
			if (!good_host_name(answer->tsp_name)) {
				suppress(&from, answer->tsp_name, ntp);
				ntp->status = NOMASTER;
			}
E 26
			return;
		}

D 26
		time.tv_sec = time.tv_usec = 0;
		answer = readmsg(TSP_ELECTION, (char *)ANYADDR,
		    &time, ntp);
		if (answer != NULL) {
			ntp->status = SLAVE;
E 26
I 26
		ntime.tv_sec = ntime.tv_usec = 0;
		answer = readmsg(TSP_ELECTION, ANYADDR, &ntime, ntp);
		if (answer != 0) {
			if (!good_host_name(answer->tsp_name)) {
				suppress(&from, answer->tsp_name, ntp);
				ntp->status = NOMASTER;
			}
E 26
			return;
		}
D 26
		ntp->status = MASTER;
	} else {
		(void)strcpy(mastername, answer->tsp_name);
		masteraddr = from;
E 26

D 26
		/*
		 * If network has been partitioned, there might be other
		 * masters; tell the one we have just acknowledged that 
		 * it has to gain control over the others. 
		 */
		time.tv_sec = 0;
		time.tv_usec = 300000;
		answer = readmsg(TSP_MASTERACK, (char *)ANYADDR, &time,
		    ntp);
		/*
		 * checking also not to send CONFLICT to ack'ed master
		 * due to duplicated MASTERACKs
		 */
		if (answer != NULL && 
		    strcmp(answer->tsp_name, mastername) != 0) {
			conflict.tsp_type = TSP_CONFLICT;
			(void)strcpy(conflict.tsp_name, hostname);
			if (acksend(&conflict, &masteraddr, mastername,
			    TSP_ACK, (struct netinfo *)NULL) == NULL) {
				syslog(LOG_ERR, 
				    "error on sending TSP_CONFLICT");
E 8
				exit(1);
			}
E 26
I 26
		if (Mflag)
			ntp->status = MASTER;
		else
			ntp->status = NOMASTER;
		return;
	}

	ntp->status = SLAVE;
	(void)strcpy(mastername, answer->tsp_name);
	masteraddr = from;

	/*
	 * If network has been partitioned, there might be other
	 * masters; tell the one we have just acknowledged that
	 * it has to gain control over the others.
	 */
	ntime.tv_sec = 0;
	ntime.tv_usec = 300000;
	answer = readmsg(TSP_MASTERACK, ANYADDR, &ntime, ntp);
	/*
	 * checking also not to send CONFLICT to ack'ed master
	 * due to duplicated MASTERACKs
	 */
	if (answer != NULL &&
	    strcmp(answer->tsp_name, mastername) != 0) {
		conflict.tsp_type = TSP_CONFLICT;
		(void)strcpy(conflict.tsp_name, hostname);
		if (!acksend(&conflict, &masteraddr, mastername,
			     TSP_ACK, 0, 0)) {
			syslog(LOG_ERR,
			       "error on sending TSP_CONFLICT");
E 26
E 5
		}
D 8
		slave();
E 8
	}
I 8
}
I 26

E 26
/*
 * based on the current network configuration, set the status, and count
 * networks;
 */
I 26
void
E 26
setstatus()
{
D 26
	register struct netinfo *ntp;
E 26
I 26
	struct netinfo *ntp;
E 26

	status = 0;
	nmasternets = nslavenets = nnets = nignorednets = 0;
	if (trace)
		fprintf(fd, "Net status:\n");
	for (ntp = nettab; ntp != NULL; ntp = ntp->next) {
D 13
		switch (ntp->status) {
E 13
I 13
		switch ((int)ntp->status) {
E 13
D 26
		  case MASTER:
E 26
I 26
		case MASTER:
E 26
			nmasternets++;
			break;
D 26
		  case SLAVE:
E 26
I 26
		case SLAVE:
E 26
			nslavenets++;
			break;
D 26
		  case IGNORE:
E 26
I 26
		case NOMASTER:
		case IGNORE:
E 26
			nignorednets++;
			break;
		}
		if (trace) {
D 25
			fprintf(fd, "\t%-16s", inet_ntoa(ntp->net));
E 25
I 25
D 26
			fprintf(fd, "\t%-16s",
			    inet_ntoa(inet_makeaddr(ntp->net, 0)));
E 26
I 26
			fprintf(fd, "\t%-16s", inet_ntoa(ntp->net));
E 26
E 25
D 13
			switch (ntp->status) {
E 13
I 13
			switch ((int)ntp->status) {
E 13
D 26
			  case MASTER:
E 26
I 26
			case NOMASTER:
				fprintf(fd, "NOMASTER\n");
				break;
			case MASTER:
E 26
				fprintf(fd, "MASTER\n");
				break;
D 26
			  case SLAVE:
E 26
I 26
			case SLAVE:
E 26
				fprintf(fd, "SLAVE\n");
				break;
D 26
			  case IGNORE:
E 26
I 26
			case IGNORE:
E 26
				fprintf(fd, "IGNORE\n");
				break;
D 26
			  default:
D 16
				fprintf(fd, "invalid state %d\n");
E 16
I 16
				fprintf(fd, "invalid state %d\n",(int)ntp->status);
E 26
I 26
			default:
				fprintf(fd, "invalid state %d\n",
					(int)ntp->status);
E 26
E 16
				break;
			}
		}
		nnets++;
		status |= ntp->status;
	}
	status &= ~IGNORE;
	if (trace)
		fprintf(fd,
D 26
		      "\tnets = %d, masters = %d, slaves = %d, ignored = %d\n",
		      nnets, nmasternets, nslavenets, nignorednets);
E 26
I 26
			"\tnets=%d masters=%d slaves=%d ignored=%d delay2=%d\n",
			nnets, nmasternets, nslavenets, nignorednets, delay2);
E 26
}

I 26
void
E 26
makeslave(net)
	struct netinfo *net;
{
	register struct netinfo *ntp;

D 26
	for (ntp = nettab; ntp != NULL; ntp = ntp->next)
E 26
I 26
	for (ntp = nettab; ntp != NULL; ntp = ntp->next) {
E 26
		if (ntp->status == SLAVE && ntp != net)
			ntp->status = IGNORE;
I 26
	}
E 26
	slavenet = net;
}
D 26
	
struct netinfo *
firstslavenet()
E 26
I 26

/*
 * Try to become master over ignored nets..
 */
static void
checkignorednets()
E 26
{
	register struct netinfo *ntp;

D 26
	for (ntp = nettab; ntp != NULL; ntp = ntp->next)
		if (ntp->status == SLAVE)
			return (ntp);
	return ((struct netinfo *)0);
E 26
I 26
	for (ntp = nettab; ntp != NULL; ntp = ntp->next) {
		if (!Mflag && ntp->status == SLAVE)
			break;

		if (ntp->status == IGNORE || ntp->status == NOMASTER) {
			lookformaster(ntp);
			if (!Mflag && ntp->status == SLAVE)
				break;
		}
	}
E 26
E 8
}

D 11
D 14
/* 
E 14
I 14
/*
E 14
E 11
I 11
/*
E 11
D 26
 * `casual' returns a random number in the range [inf, sup]
E 26
I 26
 * choose a good network on which to be a slave
 *	The ignored networks must have already been checked.
 *	Take a hint about for a good network.
E 26
 */
I 26
static void
pickslavenet(ntp)
	struct netinfo *ntp;
{
	if (slavenet != 0 && slavenet->status == SLAVE) {
		makeslave(slavenet);		/* prune extras */
		return;
	}
E 26

I 26
	if (ntp == 0 || ntp->status != SLAVE) {
		for (ntp = nettab; ntp != 0; ntp = ntp->next) {
			if (ntp->status == SLAVE)
				break;
		}
	}
	makeslave(ntp);
}

/*
 * returns a random number in the range [inf, sup]
 */
E 26
D 5
long casual(inf, sup)
E 5
I 5
long
casual(inf, sup)
E 5
D 26
long inf;
long sup;
E 26
I 26
	long inf, sup;
E 26
{
D 26
	float value;
E 26
I 26
	double value;
E 26
D 13
	long random();
E 13

D 2
	value = (float)random();
	value /= MAXRANDOM;
	if (value < 0) 
		value = -value;
E 2
I 2
D 26
	value = (float)(random() & 0x7fffffff) / 0x7fffffff;
E 2
	return(inf + (sup - inf) * value);
E 26
I 26
	value = ((double)(random() & 0x7fffffff)) / (0x7fffffff*1.0);
	return(inf + (sup - inf)*value);
E 26
}

D 2
char *date()
E 2
I 2
char *
date()
E 2
{
D 12
	char	*ret;
E 12
D 4
	char    *asctime();
E 4
I 4
D 26
	char    *ctime();
E 26
I 26
#ifdef sgi
E 26
E 4
	struct	timeval tv;
I 26
	static char tm[32];
E 26
D 4
	struct	tm *localtime();
	struct  tm *tp;
E 4

	(void)gettimeofday(&tv, (struct timezone *)0);
I 26
	(void)cftime(tm, "%D %T", &tv.tv_sec);
	return (tm);
#else
	struct	timeval tv;

	(void)gettimeofday(&tv, (struct timezone *)0);
E 26
D 4
	tp = localtime((time_t *)&tv.tv_sec);
	ret = asctime(tp);
	ret[19] = '\0';
E 4
I 4
D 12
	ret = ctime(&tv.tv_sec);
E 4
	return(ret);
E 12
I 12
	return (ctime(&tv.tv_sec));
I 26
#endif /* sgi */
E 26
E 12
I 9
}

I 26
void
E 26
addnetname(name)
	char *name;
{
D 12
	struct nets **netlist = &nets;
E 12
I 12
	register struct nets **netlist = &nets;

E 12
	while (*netlist)
		netlist = &((*netlist)->next);
	*netlist = (struct nets *)malloc(sizeof **netlist);
D 26
	if (*netlist == (struct nets *)0) {
		syslog(LOG_ERR, "malloc failed");
E 26
I 26
	if (*netlist == 0) {
		fprintf(stderr,"malloc failed\n");
E 26
		exit(1);
	}
D 13
	bzero(*netlist, sizeof(**netlist));
E 13
I 13
	bzero((char *)*netlist, sizeof(**netlist));
E 13
	(*netlist)->name = name;
I 26
}

/* note a host as trustworthy */
static void
add_good_host(name, perm)
	char *name;
	int perm;			/* 1=not part of the netgroup */
{
	register struct goodhost *ghp;
	register struct hostent *hentp;

	ghp = (struct goodhost*)malloc(sizeof(*ghp));
	if (!ghp) {
		syslog(LOG_ERR, "malloc failed");
		exit(1);
	}

	bzero((char*)ghp, sizeof(*ghp));
	(void)strncpy(&ghp->name[0], name, sizeof(ghp->name));
	ghp->next = goodhosts;
	ghp->perm = perm;
	goodhosts = ghp;

	hentp = gethostbyname(name);
	if (0 == hentp && perm)
		(void)fprintf(stderr, "unknown host %s\n", name);
}


/* update our image of the net-group of trustworthy hosts
 */
void
get_goodgroup(force)
	int force;
{
# define NG_DELAY (30*60*CLK_TCK)	/* 30 minutes */
	static unsigned long last_update = -NG_DELAY;
	unsigned long new_update;
	struct hosttbl *htp;
	struct goodhost *ghp, **ghpp;
	char *mach, *usr, *dom;
	struct tms tm;


	/* if no netgroup, then we are finished */
	if (goodgroup == 0 || !Mflag)
		return;

	/* Do not chatter with the netgroup master too often.
	 */
	new_update = times(&tm);
	if (new_update < last_update + NG_DELAY
	    && !force)
		return;
	last_update = new_update;

	/* forget the old temporary entries */
	ghpp = &goodhosts;
	while (0 != (ghp = *ghpp)) {
		if (!ghp->perm) {
			*ghpp = ghp->next;
			free((char*)ghp);
		} else {
			ghpp = &ghp->next;
		}
	}

#ifdef HAVENIS
	/* quit now if we are not one of the trusted masters
	 */
	if (!innetgr(goodgroup, &hostname[0], 0,0)) {
		if (trace)
			(void)fprintf(fd, "get_goodgroup: %s not in %s\n",
				      &hostname[0], goodgroup);
		return;
	}
	if (trace)
		(void)fprintf(fd, "get_goodgroup: %s in %s\n",
				  &hostname[0], goodgroup);

	/* mark the entire netgroup as trusted */
	(void)setnetgrent(goodgroup);
	while (getnetgrent(&mach,&usr,&dom)) {
		if (0 != mach)
			add_good_host(mach,0);
	}
	(void)endnetgrent();

	/* update list of slaves */
	for (htp = self.l_fwd; htp != &self; htp = htp->l_fwd) {
		htp->good = good_host_name(&htp->name[0]);
	}
#endif /* HAVENIS */
}


/* see if a machine is trustworthy
 */
int					/* 1=trust hp to change our date */
good_host_name(name)
	char *name;
{
	register struct goodhost *ghp = goodhosts;
	register char c;

	if (!ghp || !Mflag)		/* trust everyone if no one named */
		return 1;

	c = *name;
	do {
		if (c == ghp->name[0]
		    && !strcasecmp(name, ghp->name))
			return 1;	/* found him, so say so */
	} while (0 != (ghp = ghp->next));

	if (!strcasecmp(name,hostname))	/* trust ourself */
		return 1;

	return 0;			/* did not find him */
E 26
E 9
}
E 1
