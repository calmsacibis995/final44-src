h56476
s 00005/00005/00508
d D 8.1 93/06/06 14:05:30 bostic 61 60
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00511
d D 5.27 93/05/26 18:52:57 torek 60 59
c sysctl arg 4 is size_t *, not int *
e
s 00014/00040/00498
d D 5.26 93/05/21 18:34:17 mckusick 59 58
c use sysctl rather than nlist
e
s 00033/00030/00505
d D 5.25 93/05/18 14:04:27 torek 58 57
c `sin' is a reserved ANSI name; bcopy,bcmp,bzero => mem*
e
s 00014/00007/00521
d D 5.24 93/04/01 13:40:50 mckusick 57 56
c convert kinfo to sysctl
e
s 00042/00029/00486
d D 5.23 93/01/30 14:13:46 bostic 56 55
c lint/ANSI C
e
s 00003/00003/00512
d D 5.22 93/01/29 14:18:21 sklower 55 54
c yet another call to lseek requiring change
e
s 00085/00076/00430
d D 5.21 92/02/19 11:47:42 sklower 54 53
c use new getkerninfo to configure list of neighbors
e
s 00007/00006/00499
d D 5.20 91/03/02 16:57:41 bostic 53 52
c ANSI
e
s 00001/00014/00504
d D 5.19 90/06/29 20:51:44 karels 52 51
c use daemon() call
e
s 00001/00001/00517
d D 5.18 90/06/27 14:22:02 sklower 51 50
c tested wrong thing to see if new or old sockaddrs.
e
s 00011/00003/00507
d D 5.17 90/06/26 16:00:11 sklower 50 49
c skip over big sockaddrs obtained by SIOCGIFCONF
e
s 00001/00011/00509
d D 5.16 90/06/01 18:55:25 bostic 49 48
c new copyright notice
e
s 00005/00011/00515
d D 5.15 90/05/21 15:57:44 karels 48 47
c get with the times: MAXHOSTNAMELEN, new sockaddrs, and not #ifdef vax
e
s 00002/00005/00524
d D 5.14 89/05/29 16:02:40 mckusick 47 46
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00004/00004/00525
d D 5.13 89/05/11 14:12:08 bostic 46 45
c file reorg, pathnames.h, paths.h
e
s 00023/00026/00506
d D 5.12 89/04/02 15:01:13 bostic 45 44
c add pathnames.h
e
s 00017/00006/00515
d D 5.11 88/08/25 12:18:49 bostic 44 43
c add Berkeley specific header
e
s 00001/00001/00520
d D 5.10 87/10/22 10:44:51 bostic 43 42
c ANSI C; sprintf now returns an int.
e
s 00016/00005/00505
d D 5.9 86/03/05 19:18:28 mckusick 42 41
c more minor tweeks from Torek
e
s 00008/00007/00502
d D 5.8 86/02/01 13:49:21 karels 41 40
c perhaps a bit less inelegant (and someone has to use the 4.2-style syscalls!)
e
s 00015/00004/00494
d D 5.7 86/01/31 13:43:07 mckusick 40 39
c reduce number of creat's and length of pathnames (from speck@csvax.caltech.edu)
e
s 00000/00007/00498
d D 5.6 85/10/25 13:55:54 bloom 39 38
c Why try to be intelligent about address families too late
e
s 00001/00001/00504
d D 5.5 85/09/17 19:15:45 eric 38 37
c facilities in syslog
e
s 00004/00000/00501
d D 5.4 85/09/15 14:24:23 bloom 37 35
c strip domain part of hostname
e
s 00009/00003/00498
d R 5.4 85/09/15 00:09:44 bloom 36 35
c strip domain from hostname, servent will not stay around after gethostbyname()
e
s 00000/00026/00501
d D 5.3 85/06/19 08:31:35 karels 35 34
c remove old, unused subnet code
e
s 00001/00001/00526
d D 5.2 85/06/18 19:09:06 mckusick 34 33
c rwhod.h moves to /usr/include/protocols
e
s 00014/00002/00513
d D 5.1 85/06/06 14:19:27 dist 33 32
c Add copyright
e
s 00016/00004/00499
d D 4.30 85/06/06 13:57:24 bloom 32 31
c dynamically configure utmp size
e
s 00009/00006/00494
d D 4.29 85/06/03 09:52:14 karels 31 30
c use GIFBRDADDR instead of trying to figure it out by hand
e
s 00002/00001/00498
d D 4.28 85/02/25 14:15:03 karels 30 29
c increase max size of utmp examined, make it a #define
e
s 00001/00000/00498
d D 4.27 84/10/23 09:27:33 tef 29 28
c utmptime tested but never set, caused /etc/utmp to get read everytime
e
s 00002/00002/00496
d D 4.26 84/09/04 21:35:09 sam 28 27
c changeover to new socketopt interface
e
s 00004/00000/00494
d D 4.25 84/08/29 15:13:28 karels 27 25
c add SO_BROADCAST flag on socket
e
s 00004/00000/00494
d R 4.25 84/08/29 15:07:03 karels 26 25
c add SO_BROADCAST flag on socket
e
s 00024/00029/00470
d D 4.24 84/07/06 10:34:18 ralph 25 24
c use syslog routines.
e
s 00012/00000/00487
d D 4.23 84/07/04 12:08:59 sam 24 23
c don't nlist /vmunix unless file changes (from dpk@brl)
e
s 00030/00002/00457
d D 4.22 84/05/11 16:40:23 karels 23 22
c determine correct broadcast address on subnets
e
s 00007/00001/00452
d D 4.21 83/11/14 15:54:58 ralph 22 21
c broadcast status info less often.
e
s 00001/00001/00452
d D 4.20 83/10/11 16:00:43 leres 21 20
c Fix from Wayne@lbl-csam, allow ispunct() characters in host names.
e
s 00001/00001/00452
d D 4.19 83/07/01 04:18:06 sam 20 19
c rwhod.h no longer in /usr/include
e
s 00002/00001/00451
d D 4.18 83/06/30 12:24:25 sam 19 17
c avoid losing alarm clock
e
s 00003/00001/00451
d R 4.18 83/06/30 12:23:16 sam 18 17
c avoid losing alarm clock
e
s 00000/00001/00452
d D 4.17 83/06/24 11:47:26 sam 17 16
c delte extra signal clal
e
s 00021/00018/00432
d D 4.16 83/06/18 13:06:02 sam 16 15
c one bug fix and a number of cleanups
e
s 00001/00001/00449
d D 4.15 83/06/12 01:46:58 sam 15 14
c new signals
e
s 00001/00001/00449
d D 4.14 83/06/02 10:41:07 sam 14 13
c double != long
e
s 00002/00002/00448
d D 4.13 83/06/02 10:20:08 sam 13 12
c typo
e
s 00002/00023/00448
d D 4.12 83/06/01 16:21:08 sam 12 11
c notyet is here
e
s 00095/00016/00376
d D 4.11 83/05/28 11:16:41 sam 11 10
c prepare for switchover
e
s 00002/00000/00390
d D 4.10 83/05/09 22:01:30 sam 10 9
c ignore old packets 
e
s 00133/00022/00257
d D 4.9 83/05/05 13:19:57 sam 9 8
c use ioctl's to configure networks; change protocol to include 
c version stamp and type fields (allows expansion to handle multi-net 
c environment)
e
s 00033/00001/00246
d D 4.8 83/04/04 07:39:48 sam 8 7
c do byte swapping (from shannon@sun)
e
s 00001/00002/00246
d D 4.7 82/12/24 21:05:18 sam 7 6
c port not byte swapped; no more asm.sed; 
c move spool area to /usr/spool/rwho so /etc is always changing
e
s 00001/00001/00247
d D 4.6 82/11/15 18:33:56 sam 6 5
c add domain specification
e
s 00025/00022/00223
d D 4.5 82/11/14 15:17:42 sam 5 4
c convert to 4.1c sys calls and directory layout
e
s 00052/00020/00193
d D 4.4 82/10/10 19:43:15 sam 4 3
c convert to new data base and add sanity check on file creation
e
s 00005/00002/00208
d D 4.3 82/04/20 18:35:16 sam 3 2
c missing bounds check
e
s 00001/00001/00209
d D 4.2 82/04/15 16:28:08 sam 2 1
c makes ernie happy
e
s 00210/00000/00000
d D 4.1 82/04/02 10:29:11 wnj 1 0
c date and time created 82/04/02 10:29:11 by wnj
e
u
U
t
T
I 33
/*
D 44
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 44
I 44
D 61
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 61
I 61
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 61
 *
D 49
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 49
I 49
 * %sccs.include.redist.c%
E 49
E 44
 */

E 33
I 1
#ifndef lint
D 8
static char sccsid[] = "%W% %E%";
E 8
I 8
D 9
static char sccsid[] = "%W% %G%";
E 9
I 9
D 11
static char sccsid[] = "%W% %E%";
E 11
I 11
D 33
static char sccsid[] = "%W% (Berkeley) %E%";
E 11
E 9
E 8
#endif
E 33
I 33
D 61
char copyright[] =
D 44
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 44
I 44
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 44
 All rights reserved.\n";
E 61
I 61
static char copyright[] =
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 61
D 44
#endif not lint
E 44
I 44
#endif /* not lint */
E 44

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 44
#endif not lint
E 44
I 44
#endif /* not lint */
E 44
E 33

D 5
#include <stdio.h>
#include <signal.h>
E 5
D 48
#include <sys/types.h>
E 48
I 48
#include <sys/param.h>
E 48
D 5
#include <net/in.h>
E 5
#include <sys/socket.h>
D 5
#include <errno.h>
#include <utmp.h>
#include "rwhod.h"
E 5
#include <sys/stat.h>
I 45
#include <sys/signal.h>
E 45
D 5
#include <nlist.h>
E 5
#include <sys/ioctl.h>
I 54
D 57
#include <sys/kinfo.h>
E 57
I 57
#include <sys/sysctl.h>
E 57
E 54
I 16
D 56
#include <sys/file.h>
E 56
E 16
I 5

I 9
#include <net/if.h>
I 54
#include <net/if_dl.h>
#include <net/route.h>
E 54
E 9
#include <netinet/in.h>
I 56
#include <protocols/rwhod.h>
E 56

D 56
#include <nlist.h>
D 45
#include <stdio.h>
#include <signal.h>
E 45
#include <errno.h>
#include <utmp.h>
E 56
E 5
I 4
#include <ctype.h>
I 56
#include <errno.h>
#include <fcntl.h>
E 56
#include <netdb.h>
I 25
D 56
#include <syslog.h>
E 25
I 9
D 20
#include <rwhod.h>
E 20
I 20
D 34
#include "rwhod.h"
E 34
I 34
#include <protocols/rwhod.h>
E 56
I 56
D 59
#include <nlist.h>
E 59
#include <paths.h>
E 56
I 45
#include <stdio.h>
I 56
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
E 56
I 55
#include <unistd.h>
E 55
D 46
#include "pathnames.h"
E 46
I 46
D 56
#include <paths.h>
E 56
I 56
#include <utmp.h>
E 56
E 46
E 45
E 34
E 20
E 9
E 4

I 22
/*
 * Alarm interval. Don't forget to change the down time check in ruptime
 * if this is changed.
 */
D 25
#define AL_INTERVAL (5 * 60)
E 25
I 25
#define AL_INTERVAL (3 * 60)
I 30
D 32
#define	MAXTTYS	256			/* Max # of utmp entries examined */
E 32
E 30
E 25

E 22
I 5
D 9
#include "rwhod.h"

E 9
E 5
D 4
struct	sockaddr_in sin = { AF_INET, IPPORT_WHOSERVER };
E 4
I 4
D 48
struct	sockaddr_in sin = { AF_INET };
E 48
I 48
D 58
struct	sockaddr_in sin;
E 48
E 4

E 58
D 45
extern	errno;

E 45
D 9
char	*localnet = "localnet";
char	*myname = "myname";
E 9
I 9
D 48
char	myname[32];
E 48
I 48
char	myname[MAXHOSTNAMELEN];
E 48
E 9

D 59
struct	nlist nl[] = {
D 47
#define	NL_AVENRUN	0
	{ "_avenrun" },
D 5
#define	NL_BOOTIME	1
	{ "_bootime" },
E 5
I 5
#define	NL_BOOTTIME	1
E 47
I 47
#define	NL_BOOTTIME	0
E 47
	{ "_boottime" },
E 5
D 58
	0
E 58
I 58
	{ 0 }
E 58
};

E 59
I 9
/*
D 56
 * We communicate with each neighbor in
 * a list constructed at the time we're
 * started up.  Neighbors are currently
 * directly connected via a hardware interface.
E 56
I 56
 * We communicate with each neighbor in a list constructed at the time we're
 * started up.  Neighbors are currently directly connected via a hardware
 * interface.
E 56
 */
struct	neighbor {
	struct	neighbor *n_next;
	char	*n_name;		/* interface name */
D 54
	char	*n_addr;		/* who to send to */
E 54
I 54
	struct	sockaddr *n_addr;		/* who to send to */
E 54
	int	n_addrlen;		/* size of address */
	int	n_flags;		/* should forward?, interface flags */
};

struct	neighbor *neighbors;
E 9
struct	whod mywd;
I 9
struct	servent *sp;
E 9
D 59
int	s, utmpf, kmemf = -1;
E 59
I 59
int	s, utmpf;
E 59

I 8
D 9
#define	WHDRSIZE	(sizeof (wd) - sizeof (wd.wd_we))
E 9
I 9
D 58
#define	WHDRSIZE	(sizeof (mywd) - sizeof (mywd.wd_we))
E 58
I 58
#define	WHDRSIZE	(sizeof(mywd) - sizeof(mywd.wd_we))
E 58
D 45
#define	RWHODIR		"/usr/spool/rwho"
E 45
E 9

I 45
D 56
extern int errno;
E 45
E 8
D 53
int	onalrm();
E 53
D 9
char	*strcpy(), *sprintf();
E 9
I 9
D 43
char	*strcpy(), *sprintf(), *malloc();
E 43
I 43
char	*strcpy(), *malloc();
E 43
E 9
D 55
long	lseek();
E 55
D 53
int	getkmem();
E 53
I 53
void	getkmem(), onalrm();
E 53
I 9
struct	in_addr inet_makeaddr();
E 56
I 56
int	 configure __P((int));
D 59
void	 getkmem __P((int));
E 59
I 59
void	 getboottime __P((int));
E 59
void	 onalrm __P((int));
void	 quit __P((char *));
void	 rt_xaddrs __P((caddr_t, caddr_t, struct rt_addrinfo *));
int	 verify __P((char *));
#ifdef DEBUG
char	*interval __P((int, char *));
D 58
void	 sendto __P((int, char *, int, int, char *, int));
E 58
I 58
void	 Sendto __P((int, char *, int, int, char *, int));
#define	 sendto Sendto
E 58
#endif
E 56
E 9

D 56
main()
E 56
I 56
int
main(argc, argv)
	int argc;
	char argv[];
E 56
{
	struct sockaddr_in from;
I 41
	struct stat st;
E 41
	char path[64];
D 28
	int addr;
E 28
I 28
D 42
	int addr, on = 1;
E 42
I 42
	int on = 1;
E 42
E 28
I 4
D 9
	struct servent *sp;
E 9
I 9
D 39
	struct hostent *hp;
E 39
I 37
D 45
	char *cp;
	extern char *index();
E 45
I 45
D 56
	char *cp, *index(), *strerror();
E 56
I 56
	char *cp;
I 58
	struct sockaddr_in sin;
E 58
E 56
E 45
E 37
E 9
E 4

I 25
	if (getuid()) {
		fprintf(stderr, "rwhod: not super user\n");
		exit(1);
	}
E 25
I 4
	sp = getservbyname("who", "udp");
D 56
	if (sp == 0) {
E 56
I 56
	if (sp == NULL) {
E 56
		fprintf(stderr, "rwhod: udp/who: unknown service\n");
		exit(1);
	}
D 5
#if vax || pdp11
E 5
D 7
	sp->s_port = htons(sp->s_port);
E 7
D 5
#endif
	sin.sin_port = sp->s_port;
E 5
E 4
#ifndef DEBUG
D 52
	if (fork())
		exit(0);
	{ int s;
	  for (s = 0; s < 10; s++)
		(void) close(s);
	  (void) open("/", 0);
	  (void) dup2(0, 1);
	  (void) dup2(0, 2);
D 46
	  s = open("/dev/tty", 2);
E 46
I 46
	  s = open(_PATH_TTY, 2);
E 46
	  if (s >= 0) {
		ioctl(s, TIOCNOTTY, 0);
		(void) close(s);
	  }
	}
E 52
I 52
	daemon(1, 0);
E 52
#endif
D 40
	(void) chdir("/dev");
E 40
I 40
D 45
	if (chdir(RWHODIR) < 0) {
		perror(RWHODIR);
E 45
I 45
	if (chdir(_PATH_RWHODIR) < 0) {
		(void)fprintf(stderr, "rwhod: %s: %s\n",
		    _PATH_RWHODIR, strerror(errno));
E 45
		exit(1);
	}
E 40
D 59
	(void) signal(SIGHUP, getkmem);
E 59
I 59
	(void) signal(SIGHUP, getboottime);
E 59
D 25
	if (getuid()) {
D 4
		fprintf(stderr, "not super user\n");
E 4
I 4
		fprintf(stderr, "rwhod: not super user\n");
E 4
		exit(1);
	}
E 25
I 25
D 38
	openlog("rwhod", LOG_PID, 0);
E 38
I 38
	openlog("rwhod", LOG_PID, LOG_DAEMON);
E 38
E 25
D 9
	addr = rhost(&localnet);
	if (addr == -1) {
D 4
		fprintf(stderr, "no localnet for whod\n");
E 4
I 4
		fprintf(stderr, "rwhod: no localnet\n");
E 9
I 9
	/*
	 * Establish host name as returned by system.
	 */
D 58
	if (gethostname(myname, sizeof (myname) - 1) < 0) {
E 58
I 58
	if (gethostname(myname, sizeof(myname) - 1) < 0) {
E 58
D 25
		perror("gethostname");
E 25
I 25
		syslog(LOG_ERR, "gethostname: %m");
E 25
E 9
E 4
		exit(1);
	}
I 37
	if ((cp = index(myname, '.')) != NULL)
		*cp = '\0';
E 37
D 9
	sin.sin_addr.s_addr = addr;
	if (rhost(&myname) == -1) {
D 4
		fprintf(stderr, "don't know my name\n");
E 4
I 4
		fprintf(stderr, "rwhod: don't know \"myname\"\n");
E 4
		exit(1);
	}
	strncpy(mywd.wd_hostname, myname, sizeof (mywd.wd_hostname) - 1);
E 9
I 9
D 58
	strncpy(mywd.wd_hostname, myname, sizeof (myname) - 1);
E 58
I 58
	strncpy(mywd.wd_hostname, myname, sizeof(myname) - 1);
E 58
E 9
D 16
	utmpf = open("/etc/utmp", 0);
E 16
I 16
D 45
	utmpf = open("/etc/utmp", O_RDONLY);
E 45
I 45
	utmpf = open(_PATH_UTMP, O_RDONLY|O_CREAT, 0644);
E 45
E 16
	if (utmpf < 0) {
D 45
		(void) close(creat("/etc/utmp", 0644));
D 16
		utmpf = open("/etc/utmp", 0);
E 16
I 16
		utmpf = open("/etc/utmp", O_RDONLY);
E 16
	}
	if (utmpf < 0) {
D 4
		perror("/etc/utmp");
E 4
I 4
D 25
		perror("rwhod: /etc/utmp");
E 25
I 25
		syslog(LOG_ERR, "/etc/utmp: %m");
E 45
I 45
		syslog(LOG_ERR, "%s: %m", _PATH_UTMP);
E 45
E 25
E 4
		exit(1);
	}
I 5
D 9
	sin.sin_port = sp->s_port;
E 9
E 5
D 56
	getkmem();
E 56
I 56
D 59
	getkmem(0);
E 59
I 59
	getboottime(0);
E 59
E 56
D 4
#ifdef vax
	sin.sin_port = htons(sin.sin_port);
#endif
E 4
D 5
again:
	if ((s = socket(SOCK_DGRAM, 0, &sin, 0)) < 0) {
E 5
I 5
D 6
	if ((s = socket(0, SOCK_DGRAM, 0, 0)) < 0) {
E 6
I 6
D 16
	if ((s = socket(AF_INET, SOCK_DGRAM, 0, 0)) < 0) {
E 16
I 16
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
E 16
E 6
E 5
D 4
		perror("socket");
E 4
I 4
D 25
		perror("rwhod: socket");
E 25
I 25
		syslog(LOG_ERR, "socket: %m");
E 25
E 4
D 5
		sleep(5);
		goto again;
E 5
I 5
		exit(1);
E 5
	}
I 27
D 28
	if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, 0, 0) < 0) {
E 28
I 28
D 58
	if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, &on, sizeof (on)) < 0) {
E 58
I 58
	if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)) < 0) {
E 58
E 28
		syslog(LOG_ERR, "setsockopt SO_BROADCAST: %m");
		exit(1);
	}
I 58
	memset(&sin, 0, sizeof(sin));
E 58
I 48
	sin.sin_family = AF_INET;
E 48
E 27
I 9
D 39
	hp = gethostbyname(myname);
	if (hp == NULL) {
D 25
		fprintf(stderr, "%s: don't know my own name\n", myname);
E 25
I 25
		syslog(LOG_ERR, "%s: don't know my own name", myname);
E 25
		exit(1);
	}
	sin.sin_family = hp->h_addrtype;
E 39
	sin.sin_port = sp->s_port;
E 9
I 5
D 16
	if (bind(s, &sin, sizeof (sin), 0) < 0) {
E 16
I 16
D 53
	if (bind(s, &sin, sizeof (sin)) < 0) {
E 53
I 53
D 58
	if (bind(s, (struct sockaddr *)&sin, sizeof (sin)) < 0) {
E 58
I 58
	if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
E 58
E 53
E 16
D 25
		perror("rwhod: bind");
E 25
I 25
		syslog(LOG_ERR, "bind: %m");
E 25
		exit(1);
	}
I 9
	if (!configure(s))
		exit(1);
E 9
E 5
D 15
	sigset(SIGALRM, onalrm);
E 15
I 15
	signal(SIGALRM, onalrm);
E 15
D 56
	onalrm();
E 56
I 56
	onalrm(0);
E 56
	for (;;) {
		struct whod wd;
D 5
		int cc, whod;
E 5
I 5
D 9
		int cc, whod, len=sizeof (from);
E 9
I 9
D 58
		int cc, whod, len = sizeof (from);
E 58
I 58
		int cc, whod, len = sizeof(from);
E 58
E 9
E 5

D 5
		cc = receive(s, &from, (char *)&wd, sizeof (struct whod));
E 5
I 5
D 9
		cc = recvfrom(s, (char *)&wd, sizeof (struct whod), 0, &from, &len);
E 9
I 9
D 58
		cc = recvfrom(s, (char *)&wd, sizeof (struct whod), 0,
E 58
I 58
		cc = recvfrom(s, (char *)&wd, sizeof(struct whod), 0,
E 58
D 53
			&from, &len);
E 53
I 53
			(struct sockaddr *)&from, &len);
E 53
E 9
E 5
		if (cc <= 0) {
			if (cc < 0 && errno != EINTR)
D 4
				perror("receive");
E 4
I 4
D 5
				perror("rwhod: receive");
E 5
I 5
D 25
				perror("rwhod: recv");
E 25
I 25
				syslog(LOG_WARNING, "recv: %m");
E 25
E 5
E 4
			continue;
		}
D 4
#ifdef vax
		from.sin_port = ntohs(from.sin_port);
#endif
		if (from.sin_port != IPPORT_WHOSERVER) {
			printf("bad from port %d\n", from.sin_port);
E 4
I 4
		if (from.sin_port != sp->s_port) {
D 25
			fprintf(stderr, "rwhod: %d: bad from port\n",
E 25
I 25
			syslog(LOG_WARNING, "%d: bad from port",
E 25
				ntohs(from.sin_port));
E 4
			continue;
		}
D 4
/*
		if (rhost(&wd.wd_hostname) == -1) {
			printf("unknown host %s\n", wd.wd_hostname);
E 4
I 4
D 48
#ifdef notdef
		if (gethostbyname(wd.wd_hostname) == 0) {
D 25
			fprintf(stderr, "rwhod: %s: unknown host\n",
E 25
I 25
			syslog(LOG_WARNING, "%s: unknown host",
E 25
				wd.wd_hostname);
E 4
			continue;
		}
D 4
*/
E 4
I 4
#endif
E 48
I 11
D 12
#ifdef notyet
E 12
E 11
I 10
		if (wd.wd_vers != WHODVERSION)
			continue;
E 10
I 9
		if (wd.wd_type != WHODTYPE_STATUS)
			continue;
I 11
D 12
#endif
E 12
E 11
E 9
		if (!verify(wd.wd_hostname)) {
D 25
			fprintf(stderr, "rwhod: malformed host name from %x\n",
E 25
I 25
			syslog(LOG_WARNING, "malformed host name from %x",
E 25
				from.sin_addr);
			continue;
		}
E 4
D 7
		(void) sprintf(path, "/etc/whod.%s", wd.wd_hostname);
E 7
I 7
D 40
		(void) sprintf(path, "%s/whod.%s", RWHODIR, wd.wd_hostname);
E 7
		whod = creat(path, 0666);
E 40
I 40
		(void) sprintf(path, "whod.%s", wd.wd_hostname);
D 41
		whod = open(path, O_WRONLY);	/* much faster than creat() */
		{	struct stat s;
			if (whod < 0 || fstat(whod, &s) < 0 || s.st_size > cc) {
				(void) close(whod);
				whod = creat(path, 0666);
			}
		}
E 41
I 41
		/*
		 * Rather than truncating and growing the file each time,
		 * use ftruncate if size is less than previous size.
		 */
		whod = open(path, O_WRONLY | O_CREAT, 0644);
E 41
E 40
		if (whod < 0) {
D 4
			printf("can't create %s\n", path);
E 4
I 4
D 25
			fprintf(stderr, "rwhod: ");
			perror(path);
E 25
I 25
			syslog(LOG_WARNING, "%s: %m", path);
E 25
E 4
			continue;
		}
I 11
D 12
#ifdef notyet
E 12
E 11
I 8
D 48
#if vax || pdp11
E 48
I 48
#if ENDIAN != BIG_ENDIAN
E 48
		{
D 16
			int i, n = (cc - WHDRSIZE)/sizeof(struct utmp);
E 16
I 16
			int i, n = (cc - WHDRSIZE)/sizeof(struct whoent);
E 16
			struct whoent *we;

			/* undo header byte swapping before writing to file */
			wd.wd_sendtime = ntohl(wd.wd_sendtime);
			for (i = 0; i < 3; i++)
				wd.wd_loadav[i] = ntohl(wd.wd_loadav[i]);
			wd.wd_boottime = ntohl(wd.wd_boottime);
			we = wd.wd_we;
			for (i = 0; i < n; i++) {
				we->we_idle = ntohl(we->we_idle);
D 12
				we->we_utmp.ut_time = ntohl(we->we_utmp.ut_time);
E 12
I 12
D 13
				we->we_utmp.ut_time =
				    ntohl(we->we_utmp.ut_time);
E 13
I 13
				we->we_utmp.out_time =
				    ntohl(we->we_utmp.out_time);
E 13
E 12
				we++;
			}
		}
#endif
I 11
D 12
#endif
E 12
E 11
E 8
D 53
		(void) time(&wd.wd_recvtime);
E 53
I 53
		(void) time((time_t *)&wd.wd_recvtime);
E 53
		(void) write(whod, (char *)&wd, cc);
I 41
		if (fstat(whod, &st) < 0 || st.st_size > cc)
			ftruncate(whod, cc);
E 41
		(void) close(whod);
	}
I 4
}

/*
 * Check out host name for unprintables
 * and other funnies before allowing a file
 * to be created.  Sorry, but blanks aren't allowed.
 */
I 56
int
E 56
verify(name)
	register char *name;
{
	register int size = 0;

	while (*name) {
D 21
		if (!isascii(*name) || !isalnum(*name))
E 21
I 21
		if (!isascii(*name) || !(isalnum(*name) || ispunct(*name)))
E 21
			return (0);
		name++, size++;
	}
	return (size > 0);
E 4
}

int	utmptime;
int	utmpent;
D 2
struct	utmp utmp[100];
E 2
I 2
D 3
struct	utmp utmp[500];
E 3
I 3
D 30
struct	utmp utmp[100];
E 30
I 30
D 32
struct	utmp utmp[MAXTTYS];
E 32
I 32
int	utmpsize = 0;
struct	utmp *utmp;
E 32
E 30
E 3
E 2
int	alarmcount;

I 53
void
E 53
D 56
onalrm()
E 56
I 56
onalrm(signo)
	int signo;
E 56
{
I 45
	register struct neighbor *np;
	register struct whoent *we = mywd.wd_we, *wlast;
E 45
	register int i;
	struct stat stb;
D 3
	register struct whoent *we = mywd.wd_we;
E 3
I 3
D 45
	register struct whoent *we = mywd.wd_we, *wlast;
E 45
E 3
D 56
	int cc;
E 56
	double avenrun[3];
D 45
	time_t now = time(0);
I 9
	register struct neighbor *np;
E 45
I 45
D 56
	time_t now = time((time_t *)NULL);
	char *strerror();
E 56
I 56
	time_t now;
	int cc;
E 56
E 45
E 9

I 56
	now = time(NULL);
E 56
	if (alarmcount % 10 == 0)
D 56
		getkmem();
E 56
I 56
D 59
		getkmem(0);
E 59
I 59
		getboottime(0);
E 59
E 56
	alarmcount++;
	(void) fstat(utmpf, &stb);
D 32
	if (stb.st_mtime != utmptime) {
E 32
I 32
	if ((stb.st_mtime != utmptime) || (stb.st_size > utmpsize)) {
E 32
I 29
		utmptime = stb.st_mtime;
I 32
		if (stb.st_size > utmpsize) {
			utmpsize = stb.st_size + 10 * sizeof(struct utmp);
			if (utmp)
				utmp = (struct utmp *)realloc(utmp, utmpsize);
			else
				utmp = (struct utmp *)malloc(utmpsize);
			if (! utmp) {
				fprintf(stderr, "rwhod: malloc failed\n");
				utmpsize = 0;
				goto done;
			}
		}
E 32
E 29
D 16
		(void) lseek(utmpf, (long)0, 0);
E 16
I 16
D 55
		(void) lseek(utmpf, (long)0, L_SET);
E 55
I 55
		(void) lseek(utmpf, (off_t)0, L_SET);
E 55
E 16
D 32
		cc = read(utmpf, (char *)utmp, sizeof (utmp));
E 32
I 32
		cc = read(utmpf, (char *)utmp, stb.st_size);
E 32
		if (cc < 0) {
D 45
			perror("/etc/utmp");
E 45
I 45
			fprintf(stderr, "rwhod: %s: %s\n",
			    _PATH_UTMP, strerror(errno));
E 45
D 19
			return;
E 19
I 19
			goto done;
E 19
		}
I 3
D 9
		wlast = &mywd.wd_we[(1024 / sizeof (struct whoent)) - 1];
E 9
I 9
D 58
		wlast = &mywd.wd_we[1024 / sizeof (struct whoent) - 1];
E 9
E 3
		utmpent = cc / sizeof (struct utmp);
E 58
I 58
		wlast = &mywd.wd_we[1024 / sizeof(struct whoent) - 1];
		utmpent = cc / sizeof(struct utmp);
E 58
		for (i = 0; i < utmpent; i++)
			if (utmp[i].ut_name[0]) {
D 11
				we->we_utmp = utmp[i];
E 11
I 11
D 58
				bcopy(utmp[i].ut_line, we->we_utmp.out_line,
				   sizeof (utmp[i].ut_line));
				bcopy(utmp[i].ut_name, we->we_utmp.out_name,
				   sizeof (utmp[i].ut_name));
E 58
I 58
				memcpy(we->we_utmp.out_line, utmp[i].ut_line,
				   sizeof(utmp[i].ut_line));
				memcpy(we->we_utmp.out_name, utmp[i].ut_name,
				   sizeof(utmp[i].ut_name));
E 58
D 12
#ifdef notyet
E 12
				we->we_utmp.out_time = htonl(utmp[i].ut_time);
D 12
#else
				we->we_utmp.out_time = utmp[i].ut_time;
#endif
E 12
E 11
I 3
				if (we >= wlast)
					break;
E 3
				we++;
			}
		utmpent = we - mywd.wd_we;
	}
I 42

	/*
	 * The test on utmpent looks silly---after all, if no one is
	 * logged on, why worry about efficiency?---but is useful on
	 * (e.g.) compute servers.
	 */
D 46
	if (utmpent && chdir("/dev")) {
		syslog(LOG_ERR, "chdir(/dev): %m");
E 46
I 46
	if (utmpent && chdir(_PATH_DEV)) {
		syslog(LOG_ERR, "chdir(%s): %m", _PATH_DEV);
E 46
		exit(1);
	}
E 42
	we = mywd.wd_we;
	for (i = 0; i < utmpent; i++) {
D 11
		if (stat(we->we_utmp.ut_line, &stb) >= 0)
E 11
I 11
D 40
		if (stat(we->we_utmp.out_line, &stb) >= 0)
E 40
I 40
D 42
		char path[64];
		(void) sprintf(path, "/dev/%s", we->we_utmp.out_line);
		if (stat(path, &stb) >= 0)
E 42
I 42
		if (stat(we->we_utmp.out_line, &stb) >= 0)
E 42
E 40
D 12
#ifdef notyet
E 12
			we->we_idle = htonl(now - stb.st_atime);
D 12
#else
E 11
			we->we_idle = now - stb.st_atime;
I 11
#endif
E 12
E 11
		we++;
	}
D 16
	(void) lseek(kmemf, (long)nl[NL_AVENRUN].n_value, 0);
E 16
I 16
D 47
	(void) lseek(kmemf, (long)nl[NL_AVENRUN].n_value, L_SET);
E 16
	(void) read(kmemf, (char *)avenrun, sizeof (avenrun));
E 47
I 47
D 58
	(void) getloadavg(avenrun, sizeof(avenrun)/sizeof(avenrun[0]));
E 58
I 58
	(void)getloadavg(avenrun, sizeof(avenrun)/sizeof(avenrun[0]));
E 58
E 47
	for (i = 0; i < 3; i++)
I 11
D 12
#ifdef notyet
E 12
D 14
		mywd.wd_loadav[i] = htonl(avenrun[i] * 100);
E 14
I 14
		mywd.wd_loadav[i] = htonl((u_long)(avenrun[i] * 100));
E 14
D 12
#else
E 11
		mywd.wd_loadav[i] = avenrun[i] * 100;
D 11
	cc = (char *)we - (char *)&mywd;
	(void) time(&mywd.wd_sendtime);
I 8
#if vax || pdp11
	mywd.wd_sendtime = htonl(mywd.wd_sendtime);
	for (i = 0; i < 3; i++)
		mywd.wd_loadav[i] = htonl(mywd.wd_loadav[i]);
	mywd.wd_boottime = htonl(mywd.wd_boottime);
	we = mywd.wd_we;
	for (i = 0; i < utmpent; i++) {
		we->we_idle = htonl(we->we_idle);
		we->we_utmp.ut_time = htonl(we->we_utmp.ut_time);
		we++;
	}
E 11
#endif
E 12
I 11
	cc = (char *)we - (char *)&mywd;
D 12
#ifdef notyet
E 12
	mywd.wd_sendtime = htonl(time(0));
E 11
E 8
D 5
	send(s, &sin, (char *)&mywd, cc);
E 5
I 5
D 9
	(void) sendto(s, (char *)&mywd, cc, 0, &sin, sizeof (sin));
E 9
I 9
	mywd.wd_vers = WHODVERSION;
	mywd.wd_type = WHODTYPE_STATUS;
I 11
D 12
#else
	mywd.wd_sendtime = time(0);
#endif
E 12
E 11
	for (np = neighbors; np != NULL; np = np->n_next)
D 58
		(void) sendto(s, (char *)&mywd, cc, 0,
E 58
I 58
		(void)sendto(s, (char *)&mywd, cc, 0,
E 58
D 53
			np->n_addr, np->n_addrlen);
E 53
I 53
D 54
			(struct sockaddr *)np->n_addr, np->n_addrlen);
E 54
I 54
				np->n_addr, np->n_addrlen);
E 54
E 53
I 42
D 45
	if (utmpent && chdir(RWHODIR)) {
		syslog(LOG_ERR, "chdir(%s): %m", RWHODIR);
E 45
I 45
	if (utmpent && chdir(_PATH_RWHODIR)) {
		syslog(LOG_ERR, "chdir(%s): %m", _PATH_RWHODIR);
E 45
		exit(1);
	}
E 42
I 19
done:
E 19
E 9
E 5
D 22
	(void) alarm(60);
E 22
I 22
	(void) alarm(AL_INTERVAL);
E 22
}

I 53
void
E 53
D 56
getkmem()
E 56
I 56
D 59
getkmem(signo)
E 59
I 59
getboottime(signo)
E 59
	int signo;
E 56
{
D 42
	struct nlist *nlp;
E 42
I 24
D 59
	static ino_t vmunixino;
	static time_t vmunixctime;
	struct stat sb;
E 59
I 59
D 60
	int mib[2], size;
E 60
I 60
	int mib[2];
	size_t size;
E 60
	struct timeval tm;
E 59
E 24

I 24
D 45
	if (stat("/vmunix", &sb) < 0) {
E 45
I 45
D 59
	if (stat(_PATH_UNIX, &sb) < 0) {
E 45
		if (vmunixctime)
			return;
	} else {
		if (sb.st_ctime == vmunixctime && sb.st_ino == vmunixino)
			return;
		vmunixctime = sb.st_ctime;
D 58
		vmunixino= sb.st_ino;
E 58
I 58
		vmunixino = sb.st_ino;
E 58
	}
E 24
D 17
	signal(SIGHUP, getkmem);
E 17
	if (kmemf >= 0)
D 58
		(void) close(kmemf);
E 58
I 58
		(void)close(kmemf);
E 58
loop:
D 25
	for (nlp = &nl[sizeof (nl) / sizeof (nl[0])]; --nlp >= nl; ) {
		nlp->n_value = 0;
		nlp->n_type = 0;
	}
	nlist("/vmunix", nl);
	if (nl[0].n_value == 0) {
		fprintf(stderr, "/vmunix namelist botch\n");
E 25
I 25
D 45
	if (nlist("/vmunix", nl)) {
		syslog(LOG_WARNING, "/vmunix namelist botch");
E 45
I 45
	if (nlist(_PATH_UNIX, nl)) {
		syslog(LOG_WARNING, "%s: namelist botch", _PATH_UNIX);
E 45
E 25
		sleep(300);
		goto loop;
	}
D 16
	kmemf = open("/dev/kmem", 0);
E 16
I 16
D 45
	kmemf = open("/dev/kmem", O_RDONLY);
E 45
I 45
	kmemf = open(_PATH_KMEM, O_RDONLY, 0);
E 45
E 16
	if (kmemf < 0) {
D 25
		perror("/dev/kmem");
		sleep(300);
		goto loop;
E 25
I 25
D 45
		syslog(LOG_ERR, "/dev/kmem: %m");
E 45
I 45
		syslog(LOG_ERR, "%s: %m", _PATH_KMEM);
E 59
I 59
	mib[0] = CTL_KERN;
	mib[1] = KERN_BOOTTIME;
	size = sizeof(tm);
	if (sysctl(mib, 2, &tm, &size, NULL, 0) == -1) {
		syslog(LOG_ERR, "cannot get boottime: %m");
E 59
E 45
		exit(1);
E 25
	}
D 5
	(void) lseek(kmemf, (long)nl[NL_BOOTIME].n_value, 0);
	(void) read(kmemf, (char *)&mywd.wd_bootime, sizeof (mywd.wd_bootime));
E 5
I 5
D 16
	(void) lseek(kmemf, (long)nl[NL_BOOTTIME].n_value, 0);
	(void) read(kmemf, (char *)&mywd.wd_boottime, sizeof (mywd.wd_boottime));
E 16
I 16
D 55
	(void) lseek(kmemf, (long)nl[NL_BOOTTIME].n_value, L_SET);
E 55
I 55
D 59
	(void) lseek(kmemf, (off_t)nl[NL_BOOTTIME].n_value, L_SET);
E 55
	(void) read(kmemf, (char *)&mywd.wd_boottime,
D 58
	    sizeof (mywd.wd_boottime));
E 58
I 58
	    sizeof(mywd.wd_boottime));
E 58
E 16
I 11
D 12
#ifdef notyet
E 12
	mywd.wd_boottime = htonl(mywd.wd_boottime);
E 59
I 59
	mywd.wd_boottime = htonl(tm.tv_sec);
E 59
D 12
#endif
E 12
E 11
I 9
}

I 54
void
quit(msg)
D 56
char *msg;
E 56
I 56
	char *msg;
E 56
{
	syslog(LOG_ERR, msg);
	exit(1);
}

#define ROUNDUP(a) \
	((a) > 0 ? (1 + (((a) - 1) | (sizeof(long) - 1))) : sizeof(long))
#define ADVANCE(x, n) (x += ROUNDUP((n)->sa_len))

void
rt_xaddrs(cp, cplim, rtinfo)
	register caddr_t cp, cplim;
	register struct rt_addrinfo *rtinfo;
{
	register struct sockaddr *sa;
	register int i;

D 58
	bzero(rtinfo->rti_info, sizeof(rtinfo->rti_info));
E 58
I 58
	memset(rtinfo->rti_info, 0, sizeof(rtinfo->rti_info));
E 58
	for (i = 0; (i < RTAX_MAX) && (cp < cplim); i++) {
		if ((rtinfo->rti_addrs & (1 << i)) == 0)
			continue;
		rtinfo->rti_info[i] = sa = (struct sockaddr *)cp;
		ADVANCE(cp, sa);
	}
}

E 54
/*
 * Figure out device configuration and select
 * networks which deserve status information.
 */
I 56
int
E 56
configure(s)
	int s;
{
D 50
	char buf[BUFSIZ];
E 50
I 50
D 54
	char buf[BUFSIZ], *cp, *cplim;
E 50
	struct ifconf ifc;
	struct ifreq ifreq, *ifr;
D 16
	int n;
E 16
	struct sockaddr_in *sin;
E 54
	register struct neighbor *np;
I 54
	register struct if_msghdr *ifm;
	register struct ifa_msghdr *ifam;
D 56
	struct sockaddr_in *sin;
E 56
	struct sockaddr_dl *sdl;
D 57
	int needed, rlen = 0, flags = 0, len;
E 57
I 57
	size_t needed;
	int mib[6], flags = 0, len;
E 57
	char *buf, *lim, *next;
	struct rt_addrinfo info;
E 54
I 16
D 50
	int n;
E 50
E 16

D 54
	ifc.ifc_len = sizeof (buf);
	ifc.ifc_buf = buf;
	if (ioctl(s, SIOCGIFCONF, (char *)&ifc) < 0) {
D 25
		perror("rwhod: ioctl (get interface configuration)");
E 25
I 25
		syslog(LOG_ERR, "ioctl (get interface configuration)");
E 25
		return (0);
	}
	ifr = ifc.ifc_req;
D 50
	for (n = ifc.ifc_len / sizeof (struct ifreq); n > 0; n--, ifr++) {
E 50
I 50
D 51
#ifdef RTM_ADD
E 51
I 51
#ifdef AF_LINK
E 51
#define max(a, b) (a > b ? a : b)
#define size(p)	max((p).sa_len, sizeof(p))
#else
#define size(p) (sizeof (p))
#endif
	cplim = buf + ifc.ifc_len; /*skip over if's with big ifr_addr's */
	for (cp = buf; cp < cplim;
			cp += sizeof (ifr->ifr_name) + size(ifr->ifr_addr)) {
		ifr = (struct ifreq *)cp;
E 50
		for (np = neighbors; np != NULL; np = np->n_next)
			if (np->n_name &&
			    strcmp(ifr->ifr_name, np->n_name) == 0)
				break;
		if (np != NULL)
E 54
I 54
D 57
	if ((needed = getkerninfo(KINFO_RT_IFLIST, 0, 0, 0)) < 0)
		quit("route-getkerninfo-estimate");
E 57
I 57
	mib[0] = CTL_NET;
	mib[1] = PF_ROUTE;
	mib[2] = 0;
	mib[3] = AF_INET;
	mib[4] = NET_RT_IFLIST;
	mib[5] = 0;
	if (sysctl(mib, 6, NULL, &needed, NULL, 0) < 0)
		quit("route-sysctl-estimate");
E 57
	if ((buf = malloc(needed)) == NULL)
		quit("malloc");
D 57
	if ((rlen = getkerninfo(KINFO_RT_IFLIST, buf, &needed, 0)) < 0)
E 57
I 57
	if (sysctl(mib, 6, buf, &needed, NULL, 0) < 0)
E 57
		quit("actual retrieval of interface table");
D 57
	lim = buf + rlen;
E 57
I 57
	lim = buf + needed;
E 57

I 58
	sdl = NULL;		/* XXX just to keep gcc -Wall happy */
E 58
	for (next = buf; next < lim; next += ifm->ifm_msglen) {
		ifm = (struct if_msghdr *)next;
		if (ifm->ifm_type == RTM_IFINFO) {
			sdl = (struct sockaddr_dl *)(ifm + 1);
			flags = ifm->ifm_flags;
E 54
			continue;
D 54
		ifreq = *ifr;
		np = (struct neighbor *)malloc(sizeof (*np));
		if (np == NULL)
			continue;
		np->n_name = malloc(strlen(ifr->ifr_name) + 1);
		if (np->n_name == NULL) {
			free((char *)np);
			continue;
E 54
		}
D 54
		strcpy(np->n_name, ifr->ifr_name);
		np->n_addrlen = sizeof (ifr->ifr_addr);
		np->n_addr = malloc(np->n_addrlen);
		if (np->n_addr == NULL) {
			free(np->n_name);
			free((char *)np);
E 54
I 54
		if ((flags & IFF_UP) == 0 ||
		    (flags & (IFF_BROADCAST|IFF_POINTOPOINT)) == 0)
E 54
			continue;
D 54
		}
		bcopy((char *)&ifr->ifr_addr, np->n_addr, np->n_addrlen);
		if (ioctl(s, SIOCGIFFLAGS, (char *)&ifreq) < 0) {
D 25
			perror("rwhod: ioctl (get interface flags)");
E 25
I 25
			syslog(LOG_ERR, "ioctl (get interface flags)");
E 25
			free((char *)np);
E 54
I 54
		if (ifm->ifm_type != RTM_NEWADDR)
D 57
			quit("out of sync parsing KINFO_RT_IFLIST");
E 57
I 57
			quit("out of sync parsing NET_RT_IFLIST");
E 57
		ifam = (struct ifa_msghdr *)ifm;
		info.rti_addrs = ifam->ifam_addrs;
		rt_xaddrs((char *)(ifam + 1), ifam->ifam_msglen + (char *)ifam,
			&info);
		/* gag, wish we could get rid of Internet dependencies */
#define dstaddr	info.rti_info[RTAX_BRD]
#define IPADDR_SA(x) ((struct sockaddr_in *)(x))->sin_addr.s_addr
#define PORT_SA(x) ((struct sockaddr_in *)(x))->sin_port
		if (dstaddr == 0 || dstaddr->sa_family != AF_INET)
E 54
			continue;
D 54
		}
D 31
		if ((ifreq.ifr_flags & (IFF_BROADCAST|IFF_POINTOPOINT)) == 0) {
E 31
I 31
		if ((ifreq.ifr_flags & IFF_UP) == 0 ||
		    (ifreq.ifr_flags & (IFF_BROADCAST|IFF_POINTOPOINT)) == 0) {
E 31
			free((char *)np);
E 54
I 54
		PORT_SA(dstaddr) = sp->s_port;
		for (np = neighbors; np != NULL; np = np->n_next)
D 58
			if (bcmp(sdl->sdl_data, np->n_name, sdl->sdl_nlen) == 0
			    && IPADDR_SA(np->n_addr) == IPADDR_SA(dstaddr))
E 58
I 58
			if (memcmp(sdl->sdl_data, np->n_name,
				   sdl->sdl_nlen) == 0 &&
			    IPADDR_SA(np->n_addr) == IPADDR_SA(dstaddr))
E 58
				break;
		if (np != NULL)
E 54
			continue;
D 54
		}
		np->n_flags = ifreq.ifr_flags;
		if (np->n_flags & IFF_POINTOPOINT) {
			if (ioctl(s, SIOCGIFDSTADDR, (char *)&ifreq) < 0) {
D 25
				perror("rwhod: ioctl (get dstaddr)");
E 25
I 25
				syslog(LOG_ERR, "ioctl (get dstaddr)");
E 25
				free((char *)np);
				continue;
			}
			/* we assume addresses are all the same size */
			bcopy((char *)&ifreq.ifr_dstaddr,
			  np->n_addr, np->n_addrlen);
		}
		if (np->n_flags & IFF_BROADCAST) {
I 31
			if (ioctl(s, SIOCGIFBRDADDR, (char *)&ifreq) < 0) {
				syslog(LOG_ERR, "ioctl (get broadaddr)");
				free((char *)np);
				continue;
			}
E 31
			/* we assume addresses are all the same size */
D 31
			sin = (struct sockaddr_in *)np->n_addr;
D 23
			sin->sin_addr =
			  inet_makeaddr(inet_netof(sin->sin_addr), INADDR_ANY);
E 23
I 23
			sin->sin_addr = inet_makeaddr((np->n_flags & IFF_LOCAL)?
				inet_subnetof(sin->sin_addr) :
				inet_netof(sin->sin_addr),
				INADDR_ANY);
E 31
I 31
			bcopy((char *)&ifreq.ifr_broadaddr,
			  np->n_addr, np->n_addrlen);
E 31
E 23
		}
		/* gag, wish we could get rid of Internet dependencies */
		sin = (struct sockaddr_in *)np->n_addr;
		sin->sin_port = sp->s_port;
E 54
I 54
		len = sizeof(*np) + dstaddr->sa_len + sdl->sdl_nlen + 1;
		np = (struct neighbor *)malloc(len);
		if (np == NULL)
			quit("malloc of neighbor structure");
D 58
		bzero((char *)np, len);
E 58
I 58
		memset(np, 0, len);
E 58
		np->n_flags = flags;
		np->n_addr = (struct sockaddr *)(np + 1);
		np->n_addrlen = dstaddr->sa_len;
		np->n_name = np->n_addrlen + (char *)np->n_addr;
E 54
		np->n_next = neighbors;
		neighbors = np;
I 54
D 58
		bcopy((char *)dstaddr, (char *)np->n_addr, np->n_addrlen);
		bcopy(sdl->sdl_data, np->n_name, sdl->sdl_nlen);
E 58
I 58
		memcpy((char *)np->n_addr, (char *)dstaddr, np->n_addrlen);
		memcpy(np->n_name, sdl->sdl_data, sdl->sdl_nlen);
E 58
E 54
	}
I 54
	free(buf);
E 54
	return (1);
I 23
}

D 35
/*
 * Return the possible subnetwork number from an internet address.
 * If the address is of the form of a subnet address (most significant
 * bit of the host part is set), believe the subnet exists.
 * Otherwise, return the network number.  Any subnet number is only valid
 * if this is a ``local'' net.
 */
inet_subnetof(in)
	struct in_addr in;
{
	register u_long i = ntohl(in.s_addr);

	if (IN_CLASSA(i)) {
		if (IN_SUBNETA(i))
			return ((i & IN_CLASSA_SUBNET) >> IN_CLASSA_SUBNSHIFT);
		else
			return ((i & IN_CLASSA_NET) >> IN_CLASSA_NSHIFT);
	} else if (IN_CLASSB(i)) {
		if (IN_SUBNETB(i))
			return ((i & IN_CLASSB_SUBNET) >> IN_CLASSB_SUBNSHIFT);
		else
			return ((i & IN_CLASSB_NET) >> IN_CLASSB_NSHIFT);
	} else
		return ((i & IN_CLASSC_NET) >> IN_CLASSC_NSHIFT);
E 23
E 9
E 5
}
I 11

E 35
#ifdef DEBUG
I 56
void
E 56
D 58
sendto(s, buf, cc, flags, to, tolen)
E 58
I 58
Sendto(s, buf, cc, flags, to, tolen)
E 58
	int s;
	char *buf;
	int cc, flags;
	char *to;
	int tolen;
{
	register struct whod *w = (struct whod *)buf;
	register struct whoent *we;
	struct sockaddr_in *sin = (struct sockaddr_in *)to;
D 56
	char *interval();
E 56

	printf("sendto %x.%d\n", ntohl(sin->sin_addr), ntohs(sin->sin_port));
	printf("hostname %s %s\n", w->wd_hostname,
D 16
	   interval(w->wd_sendtime - w->wd_boottime, "  up"));
E 16
I 16
	   interval(ntohl(w->wd_sendtime) - ntohl(w->wd_boottime), "  up"));
E 16
	printf("load %4.2f, %4.2f, %4.2f\n",
D 16
	    w->wd_loadav[0] / 100.0, w->wd_loadav[1] / 100.0,
	    w->wd_loadav[2] / 100.0);
E 16
I 16
	    ntohl(w->wd_loadav[0]) / 100.0, ntohl(w->wd_loadav[1]) / 100.0,
	    ntohl(w->wd_loadav[2]) / 100.0);
E 16
	cc -= WHDRSIZE;
D 58
	for (we = w->wd_we, cc /= sizeof (struct whoent); cc > 0; cc--, we++) {
E 58
I 58
	for (we = w->wd_we, cc /= sizeof(struct whoent); cc > 0; cc--, we++) {
E 58
I 16
		time_t t = ntohl(we->we_utmp.out_time);
E 16
		printf("%-8.8s %s:%s %.12s",
D 16
			 we->we_utmp.out_name,
			 w->wd_hostname, we->we_utmp.out_line,
			ctime((time_t *)&we->we_utmp.out_time)+4);
		we->we_idle /= 60;
E 16
I 16
			we->we_utmp.out_name,
			w->wd_hostname, we->we_utmp.out_line,
			ctime(&t)+4);
		we->we_idle = ntohl(we->we_idle) / 60;
E 16
		if (we->we_idle) {
			if (we->we_idle >= 100*60)
				we->we_idle = 100*60 - 1;
			if (we->we_idle >= 60)
				printf(" %2d", we->we_idle / 60);
			else
				printf("   ");
			printf(":%02d", we->we_idle % 60);
		}
		printf("\n");
	}
}

char *
interval(time, updown)
	int time;
	char *updown;
{
	static char resbuf[32];
	int days, hours, minutes;

	if (time < 0 || time > 3*30*24*60*60) {
		(void) sprintf(resbuf, "   %s ??:??", updown);
		return (resbuf);
	}
	minutes = (time + 59) / 60;		/* round to minutes */
	hours = minutes / 60; minutes %= 60;
	days = hours / 24; hours %= 24;
	if (days)
		(void) sprintf(resbuf, "%s %2d+%02d:%02d",
		    updown, days, hours, minutes);
	else
		(void) sprintf(resbuf, "%s    %2d:%02d",
		    updown, hours, minutes);
	return (resbuf);
}
#endif
E 11
E 1
