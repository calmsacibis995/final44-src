h07233
s 00002/00002/01387
d D 8.6 95/04/28 14:22:09 bostic 70 69
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00008/00008/01381
d D 8.5 95/04/28 10:58:32 bostic 69 68
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00002/00002/01387
d D 8.4 94/12/23 23:29:34 sklower 68 67
c minor bug reported by cgd that doesn't affect operation of command
e
s 00003/00000/01386
d D 8.3 94/03/19 19:38:49 sklower 67 66
c keeping up with recent flags, and documenting them
e
s 00021/00015/01365
d D 8.2 94/01/02 20:33:18 bostic 66 65
c Set errno before calling quit() when not root. Cleanup whitespace
c and unused variables.
c From: Craig Leres <leres@ee.lbl.gov>
e
s 00005/00005/01375
d D 8.1 93/06/05 11:12:54 bostic 65 64
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00026/00012/01354
d D 5.47 93/04/01 14:11:54 mckusick 64 63
c convert from kinfo to sysctl
e
s 00003/00003/01363
d D 5.46 93/04/01 13:44:01 sklower 63 62
c multicast addition (checked in for sklower by mckusick)
e
s 00002/00002/01364
d D 5.45 92/03/02 22:26:55 ralph 62 61
c fix missing argument to usage().
e
s 00001/00001/01365
d D 5.44 92/02/20 15:32:11 sklower 61 60
c report metric on ifaddr structures
e
s 00028/00003/01338
d D 5.43 92/02/18 15:19:38 sklower 60 59
c fix minor bug in routename() for generic, try out interface list code.
c (not for general publication, and may be ripped out again).
e
s 00069/00028/01272
d D 5.42 92/02/18 12:43:55 sklower 59 58
c be able to print RTM_{IFINFO,{NEW,DEL}ADDR}
e
s 00018/00005/01282
d D 5.41 92/02/14 15:00:05 sklower 58 57
c incorporate fix from dkhusema
e
s 00020/00006/01267
d D 5.40 91/08/20 10:09:45 sklower 57 56
c add -static and -nostatic flags, amend mike's changes for route get
e
s 00001/00004/01272
d D 5.39 91/07/30 10:00:02 karels 56 55
c missed one
e
s 00095/00062/01181
d D 5.38 91/07/30 09:55:27 karels 55 54
c request & print ifp on route get; more cleanups
e
s 00108/00057/01135
d D 5.37 91/07/28 19:04:11 karels 54 53
c fix format of "route get", remove compat code, a bit of KNF
e
s 00003/00002/01189
d D 5.36 91/07/14 20:06:48 sklower 53 52
c bugs in specifying arbitrary sockaddr
e
s 00111/00004/01080
d D 5.35 91/06/27 15:02:26 sklower 52 51
c add x25 addressing, ability to spell arbitrary sockaddrs.
e
s 00007/00001/01077
d D 5.34 91/04/25 20:03:36 sklower 51 50
c add two potentially protocol specific flags
e
s 00052/00030/01026
d D 5.33 91/04/24 15:25:54 karels 50 49
c concatenation problems; use quit rather than usage to complain that user
c isn't root; KNF; output format for "route get" (changed by sklower)
e
s 00031/00024/01025
d D 5.32 91/02/03 12:37:47 bostic 49 48
c add getopt(3), minor cleanups -- could use a lot more...
e
s 00198/00187/00851
d D 5.31 91/02/03 02:47:22 torek 48 47
c lint; KNF; make gcc -Wall happy
e
s 00023/00013/01015
d D 5.30 90/11/29 17:03:26 sklower 47 46
c allow for default sockaddrs in any position of message;
c protect against non-roots altering routing table when running suid(0)
e
s 00128/00057/00900
d D 5.29 90/09/03 14:14:29 sklower 46 45
c make sure that route ``get'' works
e
s 00005/00009/00952
d D 5.28 90/07/26 16:54:21 sklower 45 44
c fix bug in printing routes when flushing them;
c permit access to new RTF_REJECT flag.
e
s 00002/00028/00959
d D 5.27 90/06/22 15:41:19 sklower 44 43
c Don't bother to read echoed messages to rtsock; failures will be
c noted via normal errno mechanism, and this is run on the local system anyway for now.
e
s 00001/00126/00986
d D 5.26 90/06/01 16:27:41 bostic 43 42
c move linkaddr() to lib/libc/net/linkaddr.c
e
s 00001/00011/01111
d D 5.25 90/06/01 16:20:51 bostic 42 41
c new copyright notice
e
s 00004/00000/01118
d D 5.24 90/05/24 15:08:11 sklower 41 40
c forgot to set bit vector of which values were being changed or set.
e
s 00060/00005/01058
d D 5.23 90/05/23 15:50:33 sklower 40 39
c provide way to specify and lock metrics, alias interface for iface
c provide way to set cloning and external resolution flags.
e
s 00039/00024/01024
d D 5.22 90/05/21 17:51:31 sklower 39 38
c previous version of route breaks default routes
e
s 00007/00006/01041
d D 5.21 90/05/02 17:10:47 sklower 38 36
c fix problem that -net caused gateways to be ignored
e
s 00002/00001/01046
d R 5.21 90/05/02 16:32:40 sklower 37 36
c fix bug in not converting gateway if -net specified.
e
s 00392/00292/00655
d D 5.20 90/04/16 12:58:29 sklower 36 35
c check in for alpha-2 tape to wisconsin, honig, nbs, cray
e
s 00016/00011/00931
d D 5.19 90/03/23 15:22:56 sklower 35 34
c This works with new routing message headers.
e
s 00055/00089/00887
d D 5.18 90/03/12 11:24:19 sklower 34 33
c this version works with getkerninfo call.
e
s 00015/00003/00961
d D 5.17 89/09/29 19:07:12 sklower 33 32
c got cold feet, using old style ioctls for alpha release
e
s 00074/00048/00890
d D 5.16 89/08/21 13:55:33 sklower 32 31
c interim support for ISO
e
s 00081/00067/00857
d D 5.15 89/08/17 00:29:09 sklower 31 30
c this version sent to NIST
e
s 00340/00073/00584
d D 5.14 88/12/07 16:55:56 sklower 30 29
c new version distinguishing struct rtentry and ortentry
e
s 00046/00038/00611
d D 5.13 88/12/07 16:39:49 sklower 29 27
c two pass tree walk to free all routes.
e
s 00000/00000/00649
d R 5.13 88/12/07 16:32:31 karels 28 27
c 5.12 was actually not the n^2 tree walk, 5.13 is; checking in
c for historical reasons; will be immediately overwritten.
e
s 00011/00002/00638
d D 5.12 88/11/10 15:32:50 karels 27 26
c working simple-minded (n^2 alg) tree version.
e
s 00125/00031/00515
d D 5.11 88/11/07 18:18:25 karels 26 25
c compiles with xns and tree changes
e
s 00017/00006/00529
d D 5.10 88/09/19 21:50:34 bostic 25 24
c Berkeley specific header
e
s 00011/00004/00524
d D 5.9 87/12/26 12:44:01 bostic 24 23
c fix external declarations for ANSI C; minor reformats
e
s 00014/00014/00514
d D 5.8 87/10/22 10:44:21 bostic 23 22
c ANSI C; sprintf now returns an int.
e
s 00002/00002/00526
d D 5.7 87/09/11 10:24:34 bostic 22 21
c initialize variable "i"; bug report tahoe/ucb/4
e
s 00169/00069/00359
d D 5.6 86/06/05 22:34:12 karels 21 20
c print ns routes sensibly
e
s 00113/00044/00315
d D 5.5 86/04/24 12:43:29 karels 20 19
c new -n flag (as expected this time), allow subnet names
c to be found, new syntax for forcing host or net, take net numbers
c without trailing 0's
e
s 00020/00003/00339
d D 5.4 86/02/18 16:28:29 karels 19 17
c minor cleanups
e
s 00002/00001/00341
d R 5.4 86/02/18 14:31:01 karels 18 17
c minor fixes
e
s 00012/00012/00330
d D 5.3 86/02/13 11:26:46 karels 17 16
c hacks to avoid calling nameserver if not running
e
s 00059/00023/00283
d D 5.2 86/01/30 19:41:23 karels 16 15
c try alternate addresses if primaries fail; explain as needed
e
s 00014/00002/00292
d D 5.1 85/06/04 16:44:59 dist 15 14
c Add copyright
e
s 00030/00049/00264
d D 4.14 85/06/03 09:33:59 karels 14 13
c remove broken subnet stuff, allow specification of host or net instead
e
s 00017/00007/00296
d D 4.13 84/10/31 11:19:41 karels 13 12
c get rthashsize from kernel
e
s 00003/00002/00300
d D 4.12 84/10/15 14:56:53 karels 12 11
c watch those null pointers
e
s 00003/00000/00299
d D 4.11 84/05/17 11:20:00 karels 11 10
c subnet fix
e
s 00006/00006/00293
d D 4.10 84/05/16 16:31:45 karels 10 9
c use net rather than host if both named the same
e
s 00069/00020/00230
d D 4.9 84/05/11 12:31:27 karels 9 8
c grok subnets
e
s 00006/00001/00244
d D 4.8 83/08/21 16:10:13 sam 8 7
c add pseudonym for default
e
s 00129/00012/00116
d D 4.7 83/05/05 11:09:23 sam 7 6
c add -f flag to flush tables of all gateway entries
e
s 00025/00009/00103
d D 4.6 83/01/06 23:56:19 sam 6 5
c fix it up for real
e
s 00002/00002/00110
d D 4.5 82/11/15 18:32:18 sam 5 4
c convert socket call to 4.1c
e
s 00004/00002/00108
d D 4.4 82/11/14 15:09:55 sam 4 3
c convert to 4.1c sys calls and directory layout
e
s 00014/00030/00096
d D 4.3 82/10/07 23:54:31 sam 3 2
c convert to new data base routines
e
s 00030/00008/00096
d D 4.2 82/08/19 17:38:05 sam 2 1
c update 
e
s 00104/00000/00000
d D 4.1 82/04/02 10:29:02 wnj 1 0
c date and time created 82/04/02 10:29:02 by wnj
e
u
U
t
T
I 15
/*
I 60
 *
E 60
D 25
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 25
I 25
D 33
 * Copyright (c) 1983 The Regents of the University of California.
E 33
I 33
D 54
 * Copyright (c) 1983, 1989 The Regents of the University of California.
E 54
I 54
D 65
 * Copyright (c) 1983, 1989, 1991 The Regents of the University of California.
E 54
E 33
 * All rights reserved.
E 65
I 65
 * Copyright (c) 1983, 1989, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 65
 *
D 42
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
E 42
I 42
 * %sccs.include.redist.c%
E 42
E 25
 */

E 15
I 1
#ifndef lint
D 8
static char sccsid[] = "%W% %E%";
E 8
I 8
D 15
static char sccsid[] = "%W% (Berkeley) %E%";
E 8
#endif
E 15
I 15
D 65
char copyright[] =
D 25
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 25
I 25
D 31
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 31
I 31
D 32
"%Z% Copyright (c) 1983, 1989  The Regents of the University of California.\n\
E 32
I 32
D 54
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 54
I 54
"%Z% Copyright (c) 1983, 1989, 1991 The Regents of the University of California.\n\
E 54
E 32
E 31
E 25
 All rights reserved.\n";
E 65
I 65
static char copyright[] =
"%Z% Copyright (c) 1983, 1989, 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 65
D 25
#endif not lint
E 25
I 25
#endif /* not lint */
E 25

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 25
#endif not lint
E 25
I 25
#endif /* not lint */
E 25
E 15

I 32
D 43
#include <paths.h>
E 43
E 32
D 4
#include <stdio.h>
E 4
D 20
#include <sys/types.h>
E 20
I 20
#include <sys/param.h>
I 52
#include <sys/file.h>
E 52
E 20
#include <sys/socket.h>
#include <sys/ioctl.h>
I 31
D 50
#include <sys/file.h>
E 50
E 31
I 7
#include <sys/mbuf.h>
I 34
D 64
#include <sys/kinfo.h>
E 64
I 64
#include <sys/sysctl.h>
E 64
E 34
E 7
I 4

I 59
#include <net/if.h>
E 59
I 7
D 13
#define	KERNEL
E 13
E 7
E 4
#include <net/route.h>
I 36
#include <net/if_dl.h>
E 36
I 26
D 30
#include <net/radix.h>
E 30
E 26
D 4
#include <net/in.h>
E 4
I 4
#include <netinet/in.h>
I 21
#include <netns/ns.h>
I 32
#include <netiso/iso.h>
I 52
#include <netccitt/x25.h>
E 52
E 32
E 21
D 50

E 50
I 50
#include <arpa/inet.h>
E 50
I 31
#include <netdb.h>
I 50

E 50
E 31
D 48
#include <stdio.h>
E 48
E 4
#include <errno.h>
D 50
#include <ctype.h>
E 50
I 50
#include <unistd.h>
E 50
I 48
#include <stdio.h>
I 50
#include <ctype.h>
E 50
#include <stdlib.h>
#include <string.h>
E 48
I 43
#include <paths.h>
E 43
I 3
D 31
#include <netdb.h>
E 31
I 31
D 32
#include <paths.h>
E 32
E 31
E 3

I 36
struct keytab {
	char	*kt_cp;
	int	kt_i;
} keywords[] = {
#include "keywords.h"
D 55
{0, 0}
E 55
I 55
	{0, 0}
E 55
};

E 36
D 30
struct	rtentry route;
E 30
I 30
struct	ortentry route;
D 32
struct	sockaddr_in sockmask;
E 32
I 32
D 36
union	{
E 36
I 36
union	sockunion {
E 36
	struct	sockaddr sa;
	struct	sockaddr_in sin;
	struct	sockaddr_ns sns;
	struct	sockaddr_iso siso;
D 36
} so_dst, so_gate, so_mask; 
E 36
I 36
	struct	sockaddr_dl sdl;
I 52
	struct	sockaddr_x25 sx25;
E 52
D 50
} so_dst, so_gate, so_mask, so_genmask, so_ifa, so_ifp, *so_addrs[] =
D 46
{ &so_dst, &so_gate, &so_mask, &so_genmask, &so_ifa, &so_ifp, 0}; 
E 46
I 46
{ &so_dst, &so_gate, &so_mask, &so_genmask, &so_ifp, &so_ifa, 0}; 
E 50
I 50
} so_dst, so_gate, so_mask, so_genmask, so_ifa, so_ifp;

D 56
union sockunion *so_addrs[] =
	{ &so_dst, &so_gate, &so_mask, &so_genmask, &so_ifp, &so_ifa, 0}; 

E 56
E 50
E 46
typedef union sockunion *sup;
D 47
int	pid, rtm_addrs;
E 47
I 47
int	pid, rtm_addrs, uid;
E 47
E 36
E 32
E 30
D 14
int	options;
E 14
int	s;
I 14
D 20
int	forcehost, forcenet;
E 20
I 20
D 26
int	forcehost, forcenet, doflush, nflag;
E 20
E 14
struct	sockaddr_in sin = { AF_INET };
E 26
I 26
D 29
int	forcehost, forcenet, doflush, nflag, xnsflag;
E 29
I 29
D 30
int	forcehost, forcenet, doflush, nflag, xnsflag, qflag;
E 30
I 30
D 31
int	forcehost, forcenet, doflush, nflag, xnsflag, qflag, sflag;
E 31
I 31
D 33
int	forcehost, forcenet, doflush, nflag, xnsflag, qflag, Cflag;
E 33
I 33
D 34
int	forcehost, forcenet, doflush, nflag, xnsflag, qflag, Cflag = 1;
E 34
I 34
D 36
int	forcehost, forcenet, doflush, nflag, xnsflag, qflag, Cflag;
E 34
E 33
E 31
D 32
int	iflag;
E 32
I 32
int	iflag, osiflag, verbose;
E 32
int	pid;
E 36
I 36
D 52
int	forcehost, forcenet, doflush, nflag, af, qflag, Cflag, keyword();
E 52
I 52
D 54
int	forcehost, forcenet, doflush, nflag, af, qflag, tflag, Cflag, keyword();
E 54
I 54
int	forcehost, forcenet, doflush, nflag, af, qflag, tflag, keyword();
E 54
E 52
D 39
int	iflag, verbose;
E 39
I 39
int	iflag, verbose, aflen = sizeof (struct sockaddr_in);
I 40
int	locking, lockrest, debugonly;
E 40
E 39
E 36
E 30
E 29
D 63
struct	sockaddr_in sin = { sizeof(sin), AF_INET };
E 63
I 40
struct	rt_metrics rt_metrics;
I 41
u_long  rtm_inits;
E 41
E 40
E 26
I 6
struct	in_addr inet_makeaddr();
I 19
D 26
char	*malloc();
E 26
I 26
D 31
char	*malloc(), *vmunix = "/vmunix";
E 31
I 31
D 36
char	*malloc(), *vmunix = _PATH_UNIX;
E 36
I 36
D 48
char	*malloc(), *routename(), *netname();
extern	char *iso_ntoa(), *link_ntoa();
E 48
I 48
char	*routename(), *netname();
D 52
void	flushroutes(), newroute(), monitor();
E 52
I 52
D 59
void	flushroutes(), newroute(), monitor(), sockaddr();
E 52
void	print_getmsg(), print_rtmsg(), pmsg_common(), sodump(), bprintf();
E 59
I 59
void	flushroutes(), newroute(), monitor(), sockaddr(), sodump(), bprintf();
D 66
void	print_getmsg(), print_rtmsg(), pmsg_common(), pmsg_addrs();
E 66
I 66
void	print_getmsg(), print_rtmsg(), pmsg_common(), pmsg_addrs(), mask_addr();
E 66
E 59
D 58
int	getaddr(), rtmsg();
E 58
I 58
int	getaddr(), rtmsg(), x25_makemask();
E 58
extern	char *inet_ntoa(), *iso_ntoa(), *link_ntoa();
E 48
E 36
E 31
D 46
#define kget(p, d) \
	(lseek(kmem, (off_t)(p), 0), read(kmem, (char *)&(d), sizeof (d)))
E 46
E 26
E 19
E 6

I 48
D 66
void
E 66
I 66
__dead void
E 66
E 48
I 36
usage(cp)
D 48
char *cp;
E 48
I 48
	char *cp;
E 48
{
D 48
	fprintf(stderr,
	    "usage: route [ -nqCv ]  cmd [[ -<qualifers> ] args ]\n");
	if (cp) fprintf(stderr, "(botched keyword: %s)\n", cp);
E 48
I 48
D 49
	(void) fprintf(stderr,
	    "usage: route [ -nqCv ] cmd [[ -<qualifers> ] args ]\n");
E 49
	if (cp)
D 49
		(void) fprintf(stderr, "(botched keyword: %s)\n", cp);
E 49
I 49
		(void) fprintf(stderr, "route: botched keyword: %s\n", cp);
	(void) fprintf(stderr,
D 54
	    "usage: route [ -Cnqv ] cmd [[ -<qualifers> ] args ]\n");
E 54
I 54
	    "usage: route [ -nqv ] cmd [[ -<qualifers> ] args ]\n");
E 54
E 49
	exit(1);
	/* NOTREACHED */
}
E 48

I 48
void
quit(s)
	char *s;
{
	int sverrno = errno;

	(void) fprintf(stderr, "route: ");
	if (s)
		(void) fprintf(stderr, "%s: ", s);
	(void) fprintf(stderr, "%s\n", strerror(sverrno));
E 48
	exit(1);
I 48
	/* NOTREACHED */
E 48
}
I 41

I 47
#define ROUNDUP(a) \
	((a) > 0 ? (1 + (((a) - 1) | (sizeof(long) - 1))) : sizeof(long))
#define ADVANCE(x, n) (x += ROUNDUP((n)->sa_len))

I 66
int
E 66
I 48
D 49
int
E 49
E 48
E 47
E 41
E 36
main(argc, argv)
	int argc;
D 49
	char *argv[];
E 49
I 49
	char **argv;
E 49
{
I 49
	extern int optind;
	int ch;
E 49
D 47

E 47
I 26
D 66
	char *argvp;
E 66
I 48

E 48
E 26
	if (argc < 2)
I 31
D 36
	usage:
E 31
D 7
		printf("usage: route [ cmd ] [ args ]\n"), exit(1);
E 7
I 7
D 14
		printf("usage: route [ -f ] [ cmd args ]\n"), exit(1);
E 14
I 14
D 20
		printf("usage: route [ -f ] [ [ -h ] [ -n ] cmd args ]\n"),
E 20
I 20
D 26
		printf("usage: route [ -n ] [ -f ] [ cmd [ net | host ] args ]\n"),
E 26
I 26
		fprintf(stderr,
		    "usage: route [ -n ] [ -f ] [ cmd [ net | host ] args ]\n"),
E 26
E 20
		exit(1);
E 36
I 36
D 48
		usage((char *)0);
E 48
I 48
		usage((char *)NULL);
E 48
E 36
E 14
E 7
D 5
	s = socket(SOCK_RAW, 0, 0, options);
E 5
I 5
D 13
	s = socket(AF_INET, SOCK_RAW, 0, 0);
E 13
I 13
D 30
	s = socket(AF_INET, SOCK_RAW, 0);
E 13
E 5
	if (s < 0) {
D 5
		perror("socket");
E 5
I 5
		perror("route: socket");
E 5
		exit(1);
	}
E 30
D 49
	argc--, argv++;
D 7
	if (strcmp(*argv, "add") == 0)
		newroute(argc, argv);
	else if (strcmp(*argv, "delete") == 0)
		newroute(argc, argv);
	else if (strcmp(*argv, "change") == 0)
		changeroute(argc-1, argv+1);
	else
		printf("%s: huh?\n", *argv);
E 7
I 7
D 14
	if (strcmp(*argv, "-f") == 0) {
		argc--, argv++;
		flushroutes();
E 14
I 14
	for (; argc >  0 && argv[0][0] == '-'; argc--, argv++) {
D 26
		for (argv[0]++; *argv[0]; argv[0]++)
E 26
I 26
		for (argvp = argv[0]++; *argvp; argvp++)
E 26
			switch (*argv[0]) {
D 36
			case 'f':
D 20
				flushroutes();
E 20
I 20
				doflush++;
E 20
				break;
E 36
D 20
			case 'h':
				forcehost++;
				break;
E 20
			case 'n':
D 20
				forcenet++;
E 20
I 20
				nflag++;
E 20
				break;
I 26
D 36
			case 'x':
				xnsflag++;
				break;
E 36
I 29
			case 'q':
				qflag++;
				break;
I 30
D 31
			case 's':
				sflag++; /* Use new routing socket */
				pid = getpid();
E 31
I 31
			case 'C':
				Cflag++; /* Use old ioctls */
E 31
				break;
E 30
E 29
D 36
			case 'k':
				vmunix = *++argv;
				argc--;
				break;
I 30
			case 'i':
				iflag++;
				break;
I 32
			case 'o':
				osiflag++;
				break;
E 36
			case 'v':
				verbose++;
D 34
				break;
I 33

			case 'N':
				Cflag = 0; /* Use routing socket */
E 34
E 33
E 32
E 30
E 26
			}
E 14
	}
E 49
I 49

D 52
	while ((ch = getopt(argc, argv, "Cnqv")) != EOF)
E 52
I 52
D 54
	while ((ch = getopt(argc, argv, "Cnqtv")) != EOF)
E 54
I 54
D 59
	while ((ch = getopt(argc, argv, "nqtv")) != EOF)
E 59
I 59
	while ((ch = getopt(argc, argv, "nqdtv")) != EOF)
E 59
E 54
E 52
		switch(ch) {
D 54
		case 'C':
			Cflag = 1;	/* Use old ioctls. */
			break;
E 54
		case 'n':
			nflag = 1;
			break;
		case 'q':
			qflag = 1;
			break;
		case 'v':
			verbose = 1;
			break;
I 52
		case 't':
			tflag = 1;
			break;
I 59
		case 'd':
			debugonly = 1;
			break;
E 59
E 52
		case '?':
		default:
D 62
			usage();
E 62
I 62
			usage((char *)NULL);
E 62
		}
	argc -= optind;
	argv += optind;

E 49
I 14
D 20
	if (forcehost && forcenet) {
		fprintf(stderr, "-n and -h are incompatible\n");
		exit(1);
	}
E 20
I 20
D 30
	if (doflush)
E 30
I 30
D 31
	if (sflag)
		s = socket(PF_ROUTE, SOCK_RAW, 0);
	else
E 31
I 31
	pid = getpid();
I 47
	uid = getuid();
E 47
D 52
	if (Cflag)
E 52
I 52
	if (tflag)
		s = open("/dev/null", O_WRONLY, 0);
D 54
	else if (Cflag)
E 52
E 31
		s = socket(AF_INET, SOCK_RAW, 0);
E 54
I 31
	else
		s = socket(PF_ROUTE, SOCK_RAW, 0);
E 31
D 48
	if (s < 0) {
		perror("route: socket");
		exit(1);
	}
E 48
I 48
	if (s < 0)
		quit("socket");
E 48
D 36
	if (doflush) {
E 30
		flushroutes();
I 30
		exit(0);
	}
E 30
E 20
E 14
	if (argc > 0) {
		if (strcmp(*argv, "add") == 0)
E 36
I 36
D 49
	if (argc > 0) switch (keyword(*argv)) {
E 49
I 49
	if (*argv)
D 50
		switch(keyword(*argv)) {
E 50
I 50
		switch (keyword(*argv)) {
E 50
E 49
I 46
		case K_GET:
E 46
D 47
		case K_ADD:
E 47
I 47
			uid = 0;
			/* FALLTHROUGH */
I 50

E 50
E 47
		case K_CHANGE:
I 47
D 54
			if (Cflag)
				usage("change or get with -C");
			/* FALLTHROUGH */
I 50

E 54
E 50
		case K_ADD:
E 47
		case K_DELETE:
E 36
			newroute(argc, argv);
I 50
			exit(0);
			/* NOTREACHED */

E 50
D 36
		else if (strcmp(*argv, "delete") == 0)
			newroute(argc, argv);
		else if (strcmp(*argv, "change") == 0)
			changeroute(argc-1, argv+1);
I 31
		else if (strcmp(*argv, "monitor") == 0)
E 36
I 36
		case K_MONITOR:
E 36
			monitor();
I 50
			/* NOTREACHED */

E 50
E 31
D 36
		else
D 26
			printf("%s: huh?\n", *argv);
E 26
I 26
			fprintf(stderr, "%s: huh?\n", *argv);
E 26
D 30
	}
E 30
I 30
	} else 
D 31
		monitor();
E 31
I 31
		goto usage;
E 36
I 36
		case K_FLUSH:
			flushroutes(argc, argv);
I 50
			exit(0);
			/* NOTREACHED */
E 50
D 49
	}
E 49
I 49
		}
E 49
	usage(*argv);
I 48
	/* NOTREACHED */
E 48
E 36
E 31
E 30
E 7
}

I 7
/*
 * Purge all entries in the routing tables not
 * associated with network interfaces.
 */
I 48
void
E 48
D 36
#include <nlist.h>

struct nlist nl[] = {
#define	N_RTHOST	0
	{ "_rthost" },
#define	N_RTNET		1
	{ "_rtnet" },
I 13
#define N_RTHASHSIZE	2
	{ "_rthashsize" },
I 26
#define N_RTREE		3
	{ "_radix_node_head" },
E 26
E 13
	"",
};

I 26
int kmem;
E 26
flushroutes()
E 36
I 36
flushroutes(argc, argv)
D 48
char *argv[];
E 48
I 48
	int argc;
	char *argv[];
E 48
E 36
{
D 31
	struct mbuf mb;
E 31
I 31
D 36
	extern int errno;
E 31
D 30
	register struct rtentry *rt;
E 30
I 30
	register struct ortentry *rt;
E 30
	register struct mbuf *m;
D 13
	struct mbuf *routehash[RTHASHSIZ];
	int i, doinghost = 1, kmem;
E 13
I 13
D 31
	struct mbuf **routehash;
E 31
I 31
	struct mbuf mb, **routehash;
E 31
D 26
	int rthashsize, i, doinghost = 1, kmem;
E 26
I 26
	int rthashsize, i, doinghost = 1;
E 26
E 13
D 20
	char *routename();
E 20
I 20
D 31
	char *routename(), *netname();
E 31
I 31
	char *routename(), *netname(), *strerror();
E 31
E 20

D 26
	nlist("/vmunix", nl);
E 26
I 26
	nlist(vmunix, nl);
D 31
	kmem = open("/dev/kmem", 0);
E 31
I 31
	kmem = open(_PATH_KMEM, O_RDONLY, 0);
E 31
	if (kmem < 0) {
D 31
		perror("route: /dev/kmem");
E 31
I 31
		(void)fprintf(stderr,
		    "route: %s: %s\n", _PATH_KMEM, strerror(errno));
E 31
		exit(1);
	}
	if (nl[N_RTREE].n_value)
D 34
		return (treestuff(nl[N_RTREE].n_value));
E 34
I 34
		return (treefree());
E 34
E 26
	if (nl[N_RTHOST].n_value == 0) {
D 26
		printf("route: \"rthost\", symbol not in namelist\n");
E 26
I 26
		fprintf(stderr,
		    "route: \"rthost\", symbol not in namelist\n");
E 26
		exit(1);
	}
	if (nl[N_RTNET].n_value == 0) {
D 26
		printf("route: \"rtnet\", symbol not in namelist\n");
E 26
I 26
		fprintf(stderr,
		    "route: \"rtnet\", symbol not in namelist\n");
E 26
		exit(1);
	}
I 13
	if (nl[N_RTHASHSIZE].n_value == 0) {
D 26
		printf("route: \"rthashsize\", symbol not in namelist\n");
E 26
I 26
		fprintf(stderr,
		    "route: \"rthashsize\", symbol not in namelist\n");
E 26
		exit(1);
	}
E 13
D 26
	kmem = open("/dev/kmem", 0);
	if (kmem < 0) {
		perror("route: /dev/kmem");
		exit(1);
	}
I 13
	lseek(kmem, nl[N_RTHASHSIZE].n_value, 0);
	read(kmem, &rthashsize, sizeof (rthashsize));
E 26
I 26
	kget(nl[N_RTHASHSIZE].n_value, rthashsize);
E 26
	routehash = (struct mbuf **)malloc(rthashsize*sizeof (struct mbuf *));

E 13
	lseek(kmem, nl[N_RTHOST].n_value, 0);
D 13
	read(kmem, routehash, sizeof (routehash));
E 13
I 13
	read(kmem, routehash, rthashsize*sizeof (struct mbuf *));
E 13
	printf("Flushing routing tables:\n");
again:
D 13
	for (i = 0; i < RTHASHSIZ; i++) {
E 13
I 13
	for (i = 0; i < rthashsize; i++) {
E 13
		if (routehash[i] == 0)
			continue;
		m = routehash[i];
		while (m) {
D 26
			lseek(kmem, m, 0);
			read(kmem, &mb, sizeof (mb));
			rt = mtod(&mb, struct rtentry *);
			if (rt->rt_flags & RTF_GATEWAY) {
D 21
				struct sockaddr_in *sin;

				sin = (struct sockaddr_in *)&rt->rt_dst;
D 20
				printf("%-15.15s ", routename(sin->sin_addr));
E 20
I 20
				printf("%-15.15s ", doinghost ?
				    routename(sin->sin_addr) :
				    netname(sin->sin_addr));
E 20
				sin = (struct sockaddr_in *)&rt->rt_gateway;
				printf("%-15.15s ", routename(sin->sin_addr));
E 21
I 21
				printf("%-20.20s ", doinghost ?
				    routename(&rt->rt_dst) :
				    netname(&rt->rt_dst));
				printf("%-20.20s ", routename(&rt->rt_gateway));
E 21
				if (ioctl(s, SIOCDELRT, (caddr_t)rt) < 0)
					error("delete");
				else
					printf("done\n");
			}
E 26
I 26
			kget(m, mb);
D 30
			d_rtentry((struct rtentry *)(mb.m_dat), doinghost);
E 30
I 30
			d_ortentry((struct ortentry *)(mb.m_dat), doinghost);
E 30
E 26
			m = mb.m_next;
		}
	}
	if (doinghost) {
		lseek(kmem, nl[N_RTNET].n_value, 0);
D 13
		read(kmem, routehash, sizeof (routehash));
E 13
I 13
		read(kmem, routehash, rthashsize*sizeof (struct mbuf *));
E 13
		doinghost = 0;
		goto again;
	}
	close(kmem);
I 13
	free(routehash);
I 26
	return;
E 26
E 13
}
I 30
D 34
typedef u_char	blob[128];
E 34
E 30

I 29
D 34
struct rtbatch {
	struct	rtbatch *nb;
	int	ifree;
D 30
	struct	rtentry rt[100];
E 30
I 30
	struct	x {
		struct	rtentry rt;
E 34
I 34
treefree()
{
E 36
D 48
	int bufsize, needed, seqno, rlen;
E 48
I 48
D 64
	int needed, seqno, rlen;
E 64
I 64
	size_t needed;
	int mib[6], rlen, seqno;
E 64
E 48
	char *buf, *next, *lim;
	register struct rt_msghdr *rtm;
D 45
	struct {
		struct rt_msghdr m_rtm;
E 34
		union {
D 34
			struct sockaddr sa;
			blob data;
		} dst, gate, mask;
	} x[100];
E 30
} firstbatch, *curbatch = &firstbatch;
E 34
I 34
			char u_saddrs[200];
			struct sockaddr u_sa;
		} m_u;
	} m;
E 45
E 34

I 47
D 66
	if (uid)
E 66
I 66
	if (uid) {
		errno = EACCES;
E 66
D 50
		usage("must be root to alter routing table");
E 50
I 50
		quit("must be root to alter routing table");
I 66
	}
E 66
E 50
E 47
I 44
	shutdown(s, 0); /* Don't want to read back our messages */
E 44
I 36
	if (argc > 1) {
		argv++;
D 39
		if (argc == 1 && **argv == '-') switch (keyword(1 + *argv)) {
			case K_INET: af = AF_INET; break;
			case K_XNS: af = AF_NS; break;
			case K_LINK: af = AF_LINK; break;
			case K_OSI: af = AF_ISO; break;
E 39
I 39
D 50
		if (argc == 2 && **argv == '-') switch (keyword(1 + *argv)) {
			case K_INET:	af = AF_INET;	break;
			case K_XNS:	af = AF_NS;	break;
			case K_LINK:	af = AF_LINK;	break;
			case K_ISO: case K_OSI:	af = AF_ISO; break;
E 39
			default: goto bad;
E 50
I 50
		if (argc == 2 && **argv == '-')
		    switch (keyword(*argv + 1)) {
			case K_INET:
				af = AF_INET;
				break;
			case K_XNS:
				af = AF_NS;
				break;
			case K_LINK:
				af = AF_LINK;
				break;
			case K_ISO:
			case K_OSI:
				af = AF_ISO;
				break;
I 52
			case K_X25:
				af = AF_CCITT;
E 52
			default:
				goto bad;
E 50
		} else
D 50
			bad: usage(*argv);
E 50
I 50
bad:			usage(*argv);
E 50
	}
E 36
E 29
I 26
D 30
treestuff(rtree)
off_t rtree;
{
	struct radix_node_head *rnh, head;
I 29
	register struct rtbatch *b;
	register int i;
E 29
	    
	for (kget(rtree, rnh); rnh; rnh = head.rnh_next) {
		kget(rnh, head);
		if (head.rnh_af) {
D 29
			printf("\nFlushing routes for protocol family %d:\n",
								head.rnh_af);
			f_tree(head.rnh_treetop);
E 29
I 29
			w_tree(head.rnh_treetop);
E 29
		}
	}
I 29
	for (b = &firstbatch; b; b = b->nb)
		for (i = 0; i < b->ifree; i++)
			d_rtentry(b->rt + i);
E 29
}

E 30
D 29
/*
 * This is not a simple tree walk
 * because the deleting a leaf may change the value of pointers
 * up the tree from us.
 */

f_tree(rn)
E 29
I 29
D 34
w_tree(rn)
E 29
struct radix_node *rn;
{
D 29
	struct radix_node rnode, *found;
	struct nrtentry nrtentry;
	int doinghost;
E 29

D 29
	while (find1(rn, &found)) {
		kget(found, nrtentry);
		doinghost = nrtentry.nrt_nodes[0].rn_mask ? 0 : 1;
		d_rtentry(&nrtentry.nrt_rt, doinghost);
	}
}

find1(rn, rnp)
struct radix_node *rn, **rnp;
{
E 29
	struct radix_node rnode;
I 27
D 30
	struct nrtentry nrtentry;
E 30
I 30
	register struct rtentry *rt;
	struct sockaddr *dst;
	register struct x *x;
E 30

E 27
	kget(rn, rnode);
	if (rnode.rn_b < 0) {
D 29
		if (rnode.rn_dupedkey && find1(rnode.rn_dupedkey, rnp))
			return 1;
E 29
		if ((rnode.rn_flags & RNF_ROOT) == 0) {
I 29
			register struct rtbatch *b = curbatch;
E 29
D 27
			*rnp = rn;
			return 1;
E 27
I 27
			if ((rnode.rn_flags & RNF_ACTIVE) == 0) {
				printf("Dead entry in tree: %x\n", rn);
				exit(1);
			}
D 30
			kget(rn, nrtentry);
E 30
D 29
			if (nrtentry.nrt_rt.rt_flags & RTF_GATEWAY) {
				*rnp = rn;
				return 1;
E 29
I 29
			if (b->ifree >= 100) {
D 30
				Malloc(b->nb, struct rtbatch *,
E 30
I 30
				R_Malloc(b->nb, struct rtbatch *,
E 30
						sizeof (*b));
				if (b->nb) {
					b = b->nb;
					Bzero(b, sizeof(*b));
					curbatch = b;
				} else {
					printf("out of space\n");
					exit(1);
				}
E 29
			}
I 29
D 30
			b->rt[b->ifree++] = nrtentry.nrt_rt;
E 30
I 30
			x = b->x + b->ifree;
			rt = &x->rt;
			kget(rn, *rt);
			dst = &x->dst.sa;
			kget(rt_key(rt), *dst);
			if (dst->sa_len > sizeof (*dst))
				kget(rt_key(rt), x->dst);
			rt->rt_nodes->rn_key = (char *)dst;
			kget(rt->rt_gateway, x->gate.sa);
			if (x->gate.sa.sa_len > sizeof (*dst))
				kget(rt->rt_gateway, x->gate);
			rt->rt_gateway = &x->gate.sa;
D 31
			if (sflag) {
E 31
I 31
			if (Cflag == 0) {
E 31
			    kget(rt_mask(rt), x->mask.sa);
			    if (x->mask.sa.sa_len > sizeof(x->mask.sa))
				kget(rt_mask(rt), x->mask);
			    rt->rt_nodes->rn_mask = (char *)&x->mask.sa;
			}
			b->ifree++;
E 34
I 34
D 64
	if ((needed = getkerninfo(KINFO_RT_DUMP, 0, 0, 0)) < 0)
D 48
		{ perror("route-getkerninfo-estimate"); exit(1);}
	if ((buf = malloc(needed)) == 0)
		{ printf("out of space\n");; exit(1);}
E 48
I 48
		quit("route-getkerninfo-estimate");
E 64
I 64
	mib[0] = CTL_NET;
	mib[1] = PF_ROUTE;
	mib[2] = 0;		/* protocol */
	mib[3] = 0;		/* wildcard address family */
	mib[4] = NET_RT_DUMP;
	mib[5] = 0;		/* no flags */
	if (sysctl(mib, 6, NULL, &needed, NULL, 0) < 0)
		quit("route-sysctl-estimate");
E 64
	if ((buf = malloc(needed)) == NULL)
		quit("malloc");
E 48
D 64
	if ((rlen = getkerninfo(KINFO_RT_DUMP, buf, &needed, 0)) < 0)
E 64
I 64
	if (sysctl(mib, 6, buf, &needed, NULL, 0) < 0)
E 64
D 48
		{ perror("actual retrieval of routing table"); exit(1);}
E 48
I 48
		quit("actual retrieval of routing table");
E 48
D 64
	lim = buf + rlen;
E 64
I 64
	lim = buf + needed;
E 64
I 59
	if (verbose)
D 64
		(void) printf("Examining routing table from getkerninfo\n");
E 64
I 64
		(void) printf("Examining routing table from sysctl\n");
E 64
E 59
I 48
	seqno = 0;		/* ??? */
E 48
	for (next = buf; next < lim; next += rtm->rtm_msglen) {
		rtm = (struct rt_msghdr *)next;
I 59
		if (verbose)
			print_rtmsg(rtm, rtm->rtm_msglen);
E 59
D 39
		if ((rtm->rtm_flags & (RTF_GATEWAY|RTF_HOST)) == 0)
E 39
I 39
		if ((rtm->rtm_flags & RTF_GATEWAY) == 0)
E 39
			continue;
I 36
		if (af) {
			struct sockaddr *sa = (struct sockaddr *)(rtm + 1);
I 50

E 50
			if (sa->sa_family != af)
				continue;
		}
I 59
		if (debugonly)
			continue;
E 59
E 36
		rtm->rtm_type = RTM_DELETE;
		rtm->rtm_seq = seqno;
D 46
		if ((rlen = write(s, next, rtm->rtm_msglen)) < 0) {
E 46
I 46
		rlen = write(s, next, rtm->rtm_msglen);
		if (rlen < (int)rtm->rtm_msglen) {
E 46
D 48
			perror("writing to routing socket");
			printf("got only %d for rlen\n", rlen);
E 48
I 48
			(void) fprintf(stderr,
			    "route: write to routing socket: %s\n",
			    strerror(errno));
			(void) printf("got only %d for rlen\n", rlen);
E 48
D 36
			return (-1);
E 36
I 36
			break;
E 36
E 34
E 30
E 29
E 27
		}
I 29
D 34
		if (rnode.rn_dupedkey)
			w_tree(rnode.rn_dupedkey);
E 29
	} else {
D 29
		if (rnode.rn_l && find1(rnode.rn_l, rnp))
			return 1;
		if (rnode.rn_r && find1(rnode.rn_r, rnp))
			return 1;
E 29
I 29
		rn = rnode.rn_r;
		w_tree(rnode.rn_l);
		w_tree(rn);
E 29
	}
D 29
	return 0;
E 29
}

D 29
d_rtentry(rt, doinghost)
E 29
I 29
D 30
d_rtentry(rt)
E 29
register struct rtentry *rt;
E 30
I 30
treestuff(rtree)
off_t rtree;
E 30
{
I 30
	struct radix_node_head *rnh, head;
	register struct rtbatch *b;
	register int i;
	    
	for (kget(rtree, rnh); rnh; rnh = head.rnh_next) {
		kget(rnh, head);
		if (head.rnh_af) {
			w_tree(head.rnh_treetop);
E 34
I 34
D 44
	again:
		if ((rlen = read(s, (char *)&m, sizeof (m))) < 0) {
			perror("reading from routing socket");
			printf("got only %d for rlen\n", rlen);
D 36
			return (-1);
E 36
I 36
			break;
E 36
E 34
		}
I 34
		if ((m.m_rtm.rtm_pid != pid) || (m.m_rtm.rtm_seq != seqno)) {
			printf("Got response for somebody else's request");
			goto again;
		}
E 44
		seqno++;
		if (qflag)
			continue;
D 48
		if (verbose) {
E 48
I 48
		if (verbose)
E 48
D 36
			print_rtmsg(rtm);
E 36
I 36
			print_rtmsg(rtm, rlen);
E 36
D 48
		} else {
E 48
I 48
		else {
E 48
D 45
			struct sockaddr *sa = &m.m_u.u_sa;
E 45
I 45
			struct sockaddr *sa = (struct sockaddr *)(rtm + 1);
E 45
D 48
			printf("%-20.20s ", (rtm->rtm_flags & RTF_HOST) ?
E 48
I 48
			(void) printf("%-20.20s ", rtm->rtm_flags & RTF_HOST ?
E 48
			    routename(sa) : netname(sa));
			sa = (struct sockaddr *)(sa->sa_len + (char *)sa);
D 48
			printf("%-20.20s ", routename(sa));
			printf("done\n");
E 48
I 48
			(void) printf("%-20.20s ", routename(sa));
			(void) printf("done\n");
E 48
		}
E 34
	}
I 36
D 50
	exit(0);
I 48
	/* NOTREACHED */
E 50
E 48
E 36
D 34
	for (b = &firstbatch; b; b = b->nb)
		for (i = 0; i < b->ifree; i++)
			d_rtentry(&(b->x[i].rt));
E 34
}
D 34

E 34
I 34
D 66
	
E 66
I 66

E 66
E 34
D 36
d_ortentry(rt)
register struct ortentry *rt;
{
E 30
I 29
	int doinghost = rt->rt_flags & RTF_HOST;

E 29
	if (rt->rt_flags & RTF_GATEWAY) {
I 29
	   if (qflag == 0) {
E 29
		printf("%-20.20s ", doinghost ?
		    routename(&rt->rt_dst) :
		    netname(&rt->rt_dst));
		printf("%-20.20s ", routename(&rt->rt_gateway));
		if (ioctl(s, SIOCDELRT, (caddr_t)rt) < 0) {
			fflush(stdout);
			error("delete");
		} else
			printf("done\n");
I 29
	    } else
		(void) ioctl(s, SIOCDELRT, (caddr_t)rt);
E 29
	}
}

I 30
struct ortentry ortentry;
d_rtentry(rt)
register struct rtentry *rt;
{
	int doinghost = rt->rt_flags & RTF_HOST;
I 32
	int result;
E 32

	ortentry.rt_flags = rt->rt_flags;
	ortentry.rt_dst = *(rt_key(rt));
	ortentry.rt_gateway = *(rt->rt_gateway);
	if (rt->rt_flags & RTF_GATEWAY) {
D 31
	   if (sflag) {
E 31
I 31
D 32
	   if (Cflag == 0) {
E 31
		rtmsg('d', rt_key(rt), rt->rt_gateway, rt_mask(rt),
			rt->rt_flags);
		return;
	   }
	   if (qflag == 0) {
		printf("%-20.20s ", doinghost ?
		    routename(rt_key(rt)) :
		    netname(rt_key(rt)));
		printf("%-20.20s ", routename(rt->rt_gateway));
		if (ioctl(s, SIOCDELRT, (caddr_t)&ortentry) < 0) {
			fflush(stdout);
			error("delete");
		} else
			printf("done\n");
	    } else
		(void) ioctl(s, SIOCDELRT, (caddr_t)&ortentry);
E 32
I 32
	       if (Cflag == 0)
		       result = rtmsg('d', rt_key(rt), rt->rt_gateway,
					rt_mask(rt), rt->rt_flags);
	       else
			result = ioctl(s, SIOCDELRT, (caddr_t)&ortentry);
	       if (qflag == 0) {
			printf("%-20.20s ", doinghost ?
				routename(rt_key(rt)) : netname(rt_key(rt)));
			printf("%-20.20s ", routename(rt->rt_gateway));
			if (result < 0) {
				fflush(stdout);
				error("delete");
			} else
				printf("done\n");
		}
E 32
	}
}

E 36
E 30
E 26
char *
D 21
routename(in)
	struct in_addr in;
E 21
I 21
routename(sa)
	struct sockaddr *sa;
E 21
{
D 20
	char *cp = 0;
E 20
I 20
	register char *cp;
E 20
	static char line[50];
D 9
	int lna, net;
E 9
I 9
	struct hostent *hp;
D 20
	struct netent *np;
D 14
	int lna, net, subnet;
E 14
I 14
	int lna, net;
I 17
	static int bynumber;
E 20
I 20
	static char domain[MAXHOSTNAMELEN + 1];
	static int first = 1;
D 48
	char *index();
E 48
I 21
	char *ns_print();
E 21
E 20
E 17
E 14
E 9

D 20
	net = inet_netof(in);
I 9
D 14
	subnet = inet_subnetof(in);
E 14
E 9
	lna = inet_lnaof(in);
E 20
I 20
	if (first) {
		first = 0;
		if (gethostname(domain, MAXHOSTNAMELEN) == 0 &&
D 69
		    (cp = index(domain, '.')))
E 69
I 69
		    (cp = strchr(domain, '.')))
E 69
			(void) strcpy(domain, cp + 1);
		else
			domain[0] = 0;
	}
D 21
	cp = 0;
E 20
D 14
	if (lna == INADDR_ANY) {
E 14
I 14
	if (in.s_addr == INADDR_ANY)
		cp = "default";
D 20
	if (cp == 0 && (lna == INADDR_ANY || forcenet)) {
E 14
D 9
		struct netent *np = getnetbyaddr(net, AF_INET);

E 9
I 9
		np = getnetbyaddr(net, AF_INET);
E 9
		if (np)
			cp = np->n_name;
D 9
	} else {
		struct hostent *hp;
E 9
I 9
D 14
		else if (net == 0)
			cp = "default";
	} else if ((subnet != net) && ((lna & 0xff) == 0) &&
	    (np = getnetbyaddr(subnet, AF_INET))) {
		struct in_addr subnaddr, inet_makeaddr();
E 9

D 9
		hp = gethostbyaddr(&in, sizeof (struct in_addr),
			AF_INET);
E 9
I 9
		subnaddr = inet_makeaddr(subnet, INADDR_ANY);
		if (bcmp(&in, &subnaddr, sizeof(in)) == 0)
			cp = np->n_name;
I 11
		else
			goto host;
E 11
	} else {
I 11
host:
E 14
I 14
	}
D 17
	if (cp == 0) {
E 17
I 17
	if (cp == 0 && bynumber == 0) {
E 17
E 14
E 11
		hp = gethostbyaddr(&in, sizeof (struct in_addr), AF_INET);
E 9
		if (hp)
E 20
I 20
	if (cp == 0 && !nflag) {
		hp = gethostbyaddr(&in, sizeof (struct in_addr),
			AF_INET);
		if (hp) {
			if ((cp = index(hp->h_name, '.')) &&
			    !strcmp(cp + 1, domain))
				*cp = 0;
E 20
			cp = hp->h_name;
E 21
I 21
D 57
	switch (sa->sa_family) {
E 57

I 57
	if (sa->sa_len == 0)
		strcpy(line, "default");
	else switch (sa->sa_family) {

E 57
	case AF_INET:
	    {	struct in_addr in;
		in = ((struct sockaddr_in *)sa)->sin_addr;

		cp = 0;
D 57
		if (in.s_addr == INADDR_ANY)
E 57
I 57
		if (in.s_addr == INADDR_ANY || sa->sa_len < 4)
E 57
			cp = "default";
		if (cp == 0 && !nflag) {
D 50
			hp = gethostbyaddr(&in, sizeof (struct in_addr),
E 50
I 50
			hp = gethostbyaddr((char *)&in, sizeof (struct in_addr),
E 50
				AF_INET);
			if (hp) {
D 69
				if ((cp = index(hp->h_name, '.')) &&
E 69
I 69
				if ((cp = strchr(hp->h_name, '.')) &&
E 69
				    !strcmp(cp + 1, domain))
					*cp = 0;
				cp = hp->h_name;
			}
E 21
I 17
D 20
		else if (h_errno == TRY_AGAIN)
			bynumber = 1;
E 20
I 20
		}
E 20
E 17
D 21
	}
	if (cp)
		strcpy(line, cp);
	else {
E 21
I 21
		if (cp)
			strcpy(line, cp);
		else {
E 21
D 20
		u_char *ucp = (u_char *)&in;
		if (lna == INADDR_ANY)
			sprintf(line, "%u.%u.%u", ucp[0], ucp[1], ucp[2]);
		else
			sprintf(line, "%u.%u.%u.%u", ucp[0], ucp[1],
				ucp[2], ucp[3]);
E 20
I 20
#define C(x)	((x) & 0xff)
D 21
		in.s_addr = ntohl(in.s_addr);
		sprintf(line, "%u.%u.%u.%u", C(in.s_addr >> 24),
			C(in.s_addr >> 16), C(in.s_addr >> 8), C(in.s_addr));
E 21
I 21
			in.s_addr = ntohl(in.s_addr);
D 23
			sprintf(line, "%u.%u.%u.%u", C(in.s_addr >> 24),
E 23
I 23
D 48
			(void)sprintf(line, "%u.%u.%u.%u", C(in.s_addr >> 24),
E 48
I 48
			(void) sprintf(line, "%u.%u.%u.%u", C(in.s_addr >> 24),
E 48
E 23
			   C(in.s_addr >> 16), C(in.s_addr >> 8), C(in.s_addr));
		}
		break;
	    }

	case AF_NS:
		return (ns_print((struct sockaddr_ns *)sa));

I 36
	case AF_LINK:
		return (link_ntoa((struct sockaddr_dl *)sa));

	case AF_ISO:
		(void) sprintf(line, "iso %s",
		    iso_ntoa(&((struct sockaddr_iso *)sa)->siso_addr));
		break;

E 36
	default:
D 60
	    {	u_short *s = (u_short *)sa->sa_data;
E 60
I 60
	    {	u_short *s = (u_short *)sa;
E 60
I 36
D 48
		u_short *slim = s + ((sa->sa_len + 1)>>1);
E 48
I 48
		u_short *slim = s + ((sa->sa_len + 1) >> 1);
E 48
		char *cp = line + sprintf(line, "(%d)", sa->sa_family);
D 48
		int n;
E 48
E 36

D 23
		sprintf(line, "af %d: %x %x %x %x %x %x %x", sa->sa_family,
			s[0], s[1], s[2], s[3], s[4], s[5], s[6]);
E 23
I 23
D 30
		(void)sprintf(line, "af %d: %x %x %x %x %x %x %x",
E 30
I 30
D 36
		(void)sprintf(line, "(%d) %x %x %x %x %x %x %x",
E 30
		    sa->sa_family, s[0], s[1], s[2], s[3], s[4], s[5], s[6]);
E 36
I 36
D 48
		while (s < slim) {
			n = sprintf(cp, " %x", *s);
			s++; cp += n;
		}
E 48
I 48
D 60
		while (s < slim)
			cp += sprintf(cp, " %x", *s++);
E 60
I 60
		while (++s < slim) /* start with sa->sa_data */
			cp += sprintf(cp, " %x", *s);
E 60
E 48
E 36
E 23
		break;
	    }
E 21
E 20
	}
	return (line);
}

I 20
/*
 * Return the name of the network whose address is given.
 * The address is assumed to be that of a net or subnet, not a host.
 */
char *
D 21
netname(in)
	struct in_addr in;
E 21
I 21
netname(sa)
	struct sockaddr *sa;
E 21
{
	char *cp = 0;
	static char line[50];
	struct netent *np = 0;
	u_long net, mask;
D 22
	register i;
E 22
I 22
	register u_long i;
E 22
	int subnetshift;
I 24
	char *ns_print();
E 24

D 21
	in.s_addr = ntohl(in.s_addr);
	if (in.s_addr == 0)
		cp = "default";
	else if (!nflag) {
		if (IN_CLASSA(i)) {
			mask = IN_CLASSA_NET;
			subnetshift = 8;
		} else if (IN_CLASSB(i)) {
			mask = IN_CLASSB_NET;
			subnetshift = 8;
		} else {
			mask = IN_CLASSC_NET;
			subnetshift = 4;
E 21
I 21
	switch (sa->sa_family) {

	case AF_INET:
	    {	struct in_addr in;
		in = ((struct sockaddr_in *)sa)->sin_addr;

D 22
		in.s_addr = ntohl(in.s_addr);
E 22
I 22
		i = in.s_addr = ntohl(in.s_addr);
E 22
		if (in.s_addr == 0)
			cp = "default";
		else if (!nflag) {
			if (IN_CLASSA(i)) {
				mask = IN_CLASSA_NET;
				subnetshift = 8;
			} else if (IN_CLASSB(i)) {
				mask = IN_CLASSB_NET;
				subnetshift = 8;
			} else {
				mask = IN_CLASSC_NET;
				subnetshift = 4;
			}
			/*
			 * If there are more bits than the standard mask
			 * would suggest, subnets must be in use.
			 * Guess at the subnet mask, assuming reasonable
			 * width subnet fields.
			 */
			while (in.s_addr &~ mask)
				mask = (long)mask >> subnetshift;
			net = in.s_addr & mask;
			while ((mask & 1) == 0)
				mask >>= 1, net >>= 1;
			np = getnetbyaddr(net, AF_INET);
			if (np)
				cp = np->n_name;
E 21
		}
D 21
		/*
		 * If there are more bits than the standard mask
		 * would suggest, subnets must be in use.
		 * Guess at the subnet mask, assuming reasonable
		 * width subnet fields.
		 */
		while (in.s_addr &~ mask)
			mask = (long)mask >> subnetshift;
		net = in.s_addr & mask;
		while ((mask & 1) == 0)
			mask >>= 1, net >>= 1;
		np = getnetbyaddr(net, AF_INET);
		if (np)
			cp = np->n_name;
E 21
I 21
		if (cp)
			strcpy(line, cp);
		else if ((in.s_addr & 0xffffff) == 0)
D 23
			sprintf(line, "%u", C(in.s_addr >> 24));
E 23
I 23
D 48
			(void)sprintf(line, "%u", C(in.s_addr >> 24));
E 48
I 48
			(void) sprintf(line, "%u", C(in.s_addr >> 24));
E 48
E 23
		else if ((in.s_addr & 0xffff) == 0)
D 23
			sprintf(line, "%u.%u", C(in.s_addr >> 24),
E 23
I 23
D 48
			(void)sprintf(line, "%u.%u", C(in.s_addr >> 24),
E 48
I 48
			(void) sprintf(line, "%u.%u", C(in.s_addr >> 24),
E 48
E 23
			    C(in.s_addr >> 16));
		else if ((in.s_addr & 0xff) == 0)
D 23
			sprintf(line, "%u.%u.%u", C(in.s_addr >> 24),
E 23
I 23
D 48
			(void)sprintf(line, "%u.%u.%u", C(in.s_addr >> 24),
E 48
I 48
			(void) sprintf(line, "%u.%u.%u", C(in.s_addr >> 24),
E 48
E 23
			    C(in.s_addr >> 16), C(in.s_addr >> 8));
		else
D 23
			sprintf(line, "%u.%u.%u.%u", C(in.s_addr >> 24),
E 23
I 23
D 48
			(void)sprintf(line, "%u.%u.%u.%u", C(in.s_addr >> 24),
E 48
I 48
			(void) sprintf(line, "%u.%u.%u.%u", C(in.s_addr >> 24),
E 48
E 23
			    C(in.s_addr >> 16), C(in.s_addr >> 8),
			    C(in.s_addr));
		break;
	    }

	case AF_NS:
		return (ns_print((struct sockaddr_ns *)sa));
		break;

I 36
	case AF_LINK:
		return (link_ntoa((struct sockaddr_dl *)sa));

	case AF_ISO:
		(void) sprintf(line, "iso %s",
		    iso_ntoa(&((struct sockaddr_iso *)sa)->siso_addr));
		break;

E 36
	default:
	    {	u_short *s = (u_short *)sa->sa_data;
I 36
		u_short *slim = s + ((sa->sa_len + 1)>>1);
		char *cp = line + sprintf(line, "af %d:", sa->sa_family);
D 48
		int n;
E 48
E 36

D 23
		sprintf(line, "af %d: %x %x %x %x %x %x %x", sa->sa_family,
			s[0], s[1], s[2], s[3], s[4], s[5], s[6]);
E 23
I 23
D 36
		(void)sprintf(line, "af %d: %x %x %x %x %x %x %x",
		    sa->sa_family, s[0], s[1], s[2], s[3], s[4], s[5], s[6]);
E 36
I 36
D 48
		while (s < slim) {
			n = sprintf(cp, " %x", *s);
			s++; cp += n;
		}
E 48
I 48
		while (s < slim)
			cp += sprintf(cp, " %x", *s++);
E 48
E 36
E 23
		break;
	    }
E 21
	}
D 21
	if (cp)
		strcpy(line, cp);
	else if ((in.s_addr & 0xffffff) == 0)
		sprintf(line, "%u", C(in.s_addr >> 24));
	else if ((in.s_addr & 0xffff) == 0)
		sprintf(line, "%u.%u", C(in.s_addr >> 24) , C(in.s_addr >> 16));
	else if ((in.s_addr & 0xff) == 0)
		sprintf(line, "%u.%u.%u", C(in.s_addr >> 24),
			C(in.s_addr >> 16), C(in.s_addr >> 8));
	else
		sprintf(line, "%u.%u.%u.%u", C(in.s_addr >> 24),
			C(in.s_addr >> 16), C(in.s_addr >> 8), C(in.s_addr));
E 21
	return (line);
}

I 48
void
E 48
I 40
set_metric(value, key)
D 48
char *value;
E 48
I 48
	char *value;
	int key;
E 48
{
D 66
	int flag = 0; 
E 66
I 66
	int flag = 0;
E 66
	u_long noval, *valp = &noval;

	switch (key) {
#define caseof(x, y, z)	case x: valp = &rt_metrics.z; flag = y; break
	caseof(K_MTU, RTV_MTU, rmx_mtu);
	caseof(K_HOPCOUNT, RTV_HOPCOUNT, rmx_hopcount);
	caseof(K_EXPIRE, RTV_EXPIRE, rmx_expire);
	caseof(K_RECVPIPE, RTV_RPIPE, rmx_recvpipe);
	caseof(K_SENDPIPE, RTV_SPIPE, rmx_sendpipe);
	caseof(K_SSTHRESH, RTV_SSTHRESH, rmx_ssthresh);
	caseof(K_RTT, RTV_RTT, rmx_rtt);
	caseof(K_RTTVAR, RTV_RTTVAR, rmx_rttvar);
	}
I 41
	rtm_inits |= flag;
E 41
	if (lockrest || locking)
		rt_metrics.rmx_locks |= flag;
	if (locking)
		locking = 0;
	*valp = atoi(value);
}

I 48
void
E 48
E 40
E 20
E 7
newroute(argc, argv)
	int argc;
D 36
	char *argv[];
E 36
I 36
	register char **argv;
E 36
{
D 48
	struct sockaddr_in *sin;
D 16
	char *cmd;
I 9
D 12
	int ishost;
E 12
I 12
	int ishost, metric = 0;
E 16
I 16
D 30
	char *cmd, *dest, *gateway;
E 30
I 30
	char *cmd, *dest, *gateway, *mask;
E 30
D 32
	int ishost, metric = 0, ret, attempts, oerrno;
E 32
I 32
D 36
	int ishost, metric = 0, ret, attempts, oerrno, flags = 0;
E 32
	struct hostent *hp;
E 36
I 36
	int ishost, metric = 0, ret, attempts, oerrno, flags = 0, next;
E 48
I 48
	char *cmd, *dest = "", *gateway = "", *err;
D 57
	int ishost = 0, ret, attempts, oerrno, flags = 0;
E 57
I 57
	int ishost = 0, ret, attempts, oerrno, flags = RTF_STATIC;
E 57
E 48
I 40
	int key;
E 40
	struct hostent *hp = 0;
E 36
D 48
	extern int errno;
E 48
E 16
E 12
E 9

I 47
D 66
	if (uid)
E 66
I 66
	if (uid) {
		errno = EACCES;
E 66
D 50
		usage("must be root to alter routing table");
E 50
I 50
		quit("must be root to alter routing table");
I 66
	}
E 66
E 50
E 47
I 44
D 46
	shutdown(s, 0); /* Don't want to read back our messages */
E 46
E 44
D 2
	if (argc < 3) {
		printf("usage: %s destination gateway\n", argv[0]);
E 2
I 2
D 9
	if (argc < 3 || argc > 4) {
		printf("usage: %s destination gateway [ metric ]\n", argv[0]);
E 2
		return;
	}
E 9
D 2
	cmd = *argv++;
	getaddr(*argv++, &route.rt_dst);
	getaddr(*argv, &route.rt_gateway);
E 2
I 2
	cmd = argv[0];
I 46
	if (*cmd != 'g')
		shutdown(s, 0); /* Don't want to read back our messages */
E 46
I 20
D 36
	if ((strcmp(argv[1], "host")) == 0) {
		forcehost++;
		argc--, argv++;
	} else if ((strcmp(argv[1], "net")) == 0) {
		forcenet++;
		argc--, argv++;
E 36
I 36
	while (--argc > 0) {
		if (**(++argv)== '-') {
D 40
			switch(keyword(1 + *argv)) {
E 40
I 40
D 48
			switch(key = keyword(1 + *argv)) {
E 48
I 48
			switch (key = keyword(1 + *argv)) {
E 48
E 40
			case K_LINK:
				af = AF_LINK;
I 39
				aflen = sizeof(struct sockaddr_dl);
E 39
				break;
			case K_OSI:
I 39
			case K_ISO:
E 39
				af = AF_ISO;
I 39
				aflen = sizeof(struct sockaddr_iso);
E 39
				break;
			case K_INET:
				af = AF_INET;
I 39
				aflen = sizeof(struct sockaddr_in);
E 39
				break;
I 52
			case K_X25:
				af = AF_CCITT;
				aflen = sizeof(struct sockaddr_x25);
				break;
			case K_SA:
D 53
				af = 0;
E 53
I 53
				af = PF_ROUTE;
E 53
				aflen = sizeof(union sockunion);
				break;
E 52
			case K_XNS:
				af = AF_NS;
I 39
				aflen = sizeof(struct sockaddr_ns);
E 39
				break;
			case K_IFACE:
I 40
			case K_INTERFACE:
E 40
				iflag++;
I 57
			case K_NOSTATIC:
				flags &= ~RTF_STATIC;
E 57
				break;
I 40
			case K_LOCK:
				locking = 1;
				break;
			case K_LOCKREST:
				lockrest = 1;
				break;
E 40
			case K_HOST:
				forcehost++;
				break;
D 39
			case K_NET:
				forcenet++;
				break;
E 39
D 46
			case K_NETMASK:
				argc--;
				(void) getaddr(RTA_NETMASK, *++argv, 0);
I 39
				/* FALLTHROUGH */
			case K_NET:
				forcenet++;
E 39
				break;
E 46
I 45
			case K_REJECT:
				flags |= RTF_REJECT;
				break;
I 67
			case K_BLACKHOLE:
				flags |= RTF_BLACKHOLE;
				break;
E 67
I 51
			case K_PROTO1:
				flags |= RTF_PROTO1;
				break;
			case K_PROTO2:
				flags |= RTF_PROTO2;
				break;
E 51
E 45
I 40
			case K_CLONING:
				flags |= RTF_CLONING;
				break;
			case K_XRESOLVE:
				flags |= RTF_XRESOLVE;
				break;
I 57
			case K_STATIC:
				flags |= RTF_STATIC;
				break;
E 57
I 46
			case K_IFA:
				argc--;
				(void) getaddr(RTA_IFA, *++argv, 0);
				break;
			case K_IFP:
				argc--;
				(void) getaddr(RTA_IFP, *++argv, 0);
				break;
E 46
E 40
			case K_GENMASK:
				argc--;
				(void) getaddr(RTA_GENMASK, *++argv, 0);
				break;
I 46
			case K_GATEWAY:
				argc--;
				(void) getaddr(RTA_GATEWAY, *++argv, 0);
				break;
			case K_DST:
				argc--;
				ishost = getaddr(RTA_DST, *++argv, &hp);
				dest = *argv;
				break;
			case K_NETMASK:
				argc--;
				(void) getaddr(RTA_NETMASK, *++argv, 0);
				/* FALLTHROUGH */
			case K_NET:
				forcenet++;
				break;
E 46
I 40
			case K_MTU:
			case K_HOPCOUNT:
			case K_EXPIRE:
			case K_RECVPIPE:
			case K_SENDPIPE:
			case K_SSTHRESH:
			case K_RTT:
			case K_RTTVAR:
				argc--;
				set_metric(*++argv, key);
				break;
E 40
			default:
				usage(1+*argv);
			}
		} else {
			if ((rtm_addrs & RTA_DST) == 0) {
				dest = *argv;
				ishost = getaddr(RTA_DST, *argv, &hp);
			} else if ((rtm_addrs & RTA_GATEWAY) == 0) {
				gateway = *argv;
				(void) getaddr(RTA_GATEWAY, *argv, &hp);
			} else {
				int ret = atoi(*argv);
I 54

E 54
				if (ret == 0) {
D 54
				    printf("%s,%s", "old usage of trailing 0",
					   "assuming route to if\n");
E 54
I 54
				    if (strcmp(*argv, "0") == 0)
				        printf("%s,%s",
					    "old usage of trailing 0",
					    "assuming route to if\n");
				    else
D 62
					usage(NULL);
E 62
I 62
					usage((char *)NULL);
E 62
E 54
				    iflag = 1;
				    continue;
				} else if (ret > 0 && ret < 10) {
				    printf("old usage of trailing digit, ");
				    printf("assuming route via gateway\n");
				    iflag = 0;
				    continue;
				}
				(void) getaddr(RTA_NETMASK, *argv, 0);
			}
		}
E 36
	}
E 20
D 9
	getaddr(argv[1], &route.rt_dst);
	getaddr(argv[2], &route.rt_gateway);
E 9
I 9
D 30
	if (*cmd == 'a') {
		if (argc != 4) {
			printf("usage: %s destination gateway metric\n", cmd);
			printf("(metric of 0 if gateway is this host)\n");
			return;
		}
I 12
		metric = atoi(argv[3]);
E 12
	} else {
D 19
		if (argc != 3) {
E 19
I 19
		if (argc < 3) {
E 19
			printf("usage: %s destination gateway\n", cmd);
			return;
		}
	}
E 30
D 16
	ishost = getaddr(argv[1], &route.rt_dst);
E 16
I 16
D 32
	sin = (struct sockaddr_in *)&route.rt_dst;
D 17
	ishost = getaddr(argv[1], &route.rt_dst, &hp);
	if (hp)
		dest = hp->h_name;
	else
		dest = routename(sin->sin_addr);
E 17
I 17
D 20
	ishost = getaddr(argv[1], &route.rt_dst, &hp, &dest);
E 20
I 20
D 30
	ishost = getaddr(argv[1], &route.rt_dst, &hp, &dest, forcenet);
E 30
I 30
	ishost = getaddr(argv[1], &route.rt_dst, &sockmask,
E 32
I 32
D 36
	ishost = getaddr(argv[1], &so_dst.sa, &so_mask.sa,
E 32
						&hp, &dest, forcenet);
E 36
E 30
E 20
E 17
E 16
I 14
	if (forcehost)
		ishost = 1;
	if (forcenet)
		ishost = 0;
E 14
D 16
	(void) getaddr(argv[2], &route.rt_gateway);
E 9
E 2
	sin = (struct sockaddr_in *)&route.rt_dst;
E 16
I 16
D 32
	sin = (struct sockaddr_in *)&route.rt_gateway;
D 17
	(void) getaddr(argv[2], &route.rt_gateway, &hp);
	if (hp)
		gateway = hp->h_name;
	else
		gateway = routename(sin->sin_addr);
E 17
I 17
D 20
	(void) getaddr(argv[2], &route.rt_gateway, &hp, &gateway);
E 20
I 20
D 30
	(void) getaddr(argv[2], &route.rt_gateway, &hp, &gateway, 0);
E 30
I 30
	(void) getaddr(argv[2], &route.rt_gateway, 0, &hp, &gateway, 0);
E 32
I 32
D 36
	(void) getaddr(argv[2], &so_gate.sa, 0, &hp, &gateway, 0);
E 32
D 31
	if (sflag && argc == 4) {
		getaddr(argv[3], &sockmask, 0, &hp, &mask, 0);
E 31
I 31
	if ((Cflag == 0) && argc == 4) {
D 32
		(void) getaddr(argv[3], &sockmask, 0, &hp, &mask, 0);
E 32
I 32
D 33
		(void) getaddr(argv[3], &so_mask.sa, 0, &hp, &mask, 0);
E 33
I 33
		ret = atoi(argv[3]);
		if (ret == 0) {
		    printf("old usage of trailing 0, assuming route to if\n");
		    iflag = 1;
		} else if (ret > 0 && ret < 10) {
		    printf("old usage of trailing digit, ");
		    printf("assuming route via gateway\n");
		    iflag = 0;
		} else
		    (void) getaddr(argv[3], &so_mask.sa, 0, &hp, &mask, 0);
E 33
E 32
E 31
	}
E 36
E 30
E 20
E 17
E 16
D 32
	route.rt_flags = RTF_UP;
E 32
I 32
D 40
	flags = RTF_UP;
E 40
I 40
	flags |= RTF_UP;
E 40
E 32
D 2
	if (sin->sin_addr.s_host || sin->sin_addr.s_imp)
E 2
I 2
D 3
	if (in_lnaof(sin->sin_addr) != 0)
E 3
I 3
D 9
	if (inet_lnaof(sin->sin_addr) != 0)
E 9
I 9
	if (ishost)
E 9
E 3
E 2
D 32
		route.rt_flags |= RTF_HOST;
E 32
I 32
		flags |= RTF_HOST;
E 32
D 2
	printf("%s %x: gateway %x\n", cmd, sin->sin_addr,
		((struct sockaddr_in *)&route.rt_gateway)->sin_addr);
E 2
I 2
D 9
	if (argc > 3 && atoi(argv[3]) > 0)
E 9
I 9
D 12
	if (atoi(argv[3]) > 0)
E 12
I 12
D 30
	if (metric > 0)
E 30
I 30
	if (iflag == 0)
E 30
E 12
E 9
D 32
		route.rt_flags |= RTF_GATEWAY;
E 32
I 32
		flags |= RTF_GATEWAY;
E 32
D 7
	printf("%s %x: gateway %x, flags %x\n", cmd, sin->sin_addr,
		((struct sockaddr_in *)&route.rt_gateway)->sin_addr,
		route.rt_flags);
E 7
I 7
D 16
	printf("%s %s: gateway ", cmd, routename(sin->sin_addr));
	sin = (struct sockaddr_in *)&route.rt_gateway;
	printf("%s, flags %x\n", routename(sin->sin_addr), route.rt_flags);
E 7
E 2
	if (ioctl(s, *cmd == 'a' ? SIOCADDRT : SIOCDELRT, (caddr_t)&route))
		error(cmd);
E 16
I 16
	for (attempts = 1; ; attempts++) {
		errno = 0;
D 30
		if ((ret = ioctl(s, *cmd == 'a' ? SIOCADDRT : SIOCDELRT,
		     (caddr_t)&route)) == 0)
			break;
E 30
I 30
D 31
		if (sflag == 0) {
E 31
I 31
D 36
		if (Cflag) {
E 36
I 36
D 54
		if (Cflag && (af == AF_INET || af == AF_NS)) {
E 36
I 32
			route.rt_flags = flags;
			route.rt_dst = so_dst.sa;
			route.rt_gateway = so_gate.sa;
E 32
E 31
			if ((ret = ioctl(s, *cmd == 'a' ? SIOCADDRT : SIOCDELRT,
			     (caddr_t)&route)) == 0)
				break;
		} else {
D 32
		    if ((ret = rtmsg(*cmd, &route.rt_dst, &route.rt_gateway,
			    (ishost ? 0 : &sockmask), route.rt_flags)) == 0)
E 32
I 32
D 36
		    if ((ret = rtmsg(*cmd, &so_dst.sa, &so_gate.sa,
			    (ishost ? 0 : &so_mask.sa), flags)) == 0)
E 36
I 36
D 46
		    if ((ret = rtmsg(*cmd, flags)) == 0);
E 46
I 46
		    if ((ret = rtmsg(*cmd, flags)) == 0)
E 46
E 36
E 32
				break;
		}
E 54
I 54
		if ((ret = rtmsg(*cmd, flags)) == 0)
			break;
E 54
E 30
		if (errno != ENETUNREACH && errno != ESRCH)
			break;
D 46
		if (hp && hp->h_addr_list[1]) {
E 46
I 46
D 54
		if (af == AF_INET && hp && hp->h_addr_list[1]) {
E 54
I 54
		if (af == AF_INET && *gateway && hp && hp->h_addr_list[1]) {
E 54
E 46
			hp->h_addr_list++;
D 32
			bcopy(hp->h_addr_list[0], (caddr_t)&sin->sin_addr,
E 32
I 32
D 54
			bcopy(hp->h_addr_list[0], (caddr_t)&so_dst.sin.sin_addr,
E 54
I 54
D 69
			bcopy(hp->h_addr_list[0], &so_gate.sin.sin_addr,
E 69
I 69
			memmove(&so_gate.sin.sin_addr, hp->h_addr_list[0],
E 69
E 54
E 32
			    hp->h_length);
		} else
			break;
	}
I 46
	if (*cmd == 'g')
		exit(0);
E 46
	oerrno = errno;
D 48
	printf("%s %s %s: gateway %s", cmd, ishost? "host" : "net",
E 48
I 48
D 54
	(void) printf("%s %s %s: gateway %s", cmd, ishost? "host" : "net",
E 48
		dest, gateway);
	if (attempts > 1 && ret == 0)
D 48
	    printf(" (%s)",
E 48
I 48
	    (void) printf(" (%s)",
E 48
		inet_ntoa(((struct sockaddr_in *)&route.rt_gateway)->sin_addr));
E 54
I 54
	(void) printf("%s %s %s", cmd, ishost? "host" : "net", dest);
	if (*gateway) {
		(void) printf(": gateway %s", gateway);
		if (attempts > 1 && ret == 0 && af == AF_INET)
		    (void) printf(" (%s)",
			inet_ntoa(((struct sockaddr_in *)&route.rt_gateway)->sin_addr));
	}
E 54
	if (ret == 0)
D 48
		printf("\n");
E 48
I 48
		(void) printf("\n");
E 48
	else {
D 48
		printf(": ");
		fflush(stdout);
		errno = oerrno;
D 36
		error(0);
E 36
I 36
		error("");
E 48
I 48
		switch (oerrno) {
		case ESRCH:
			err = "not in table";
			break;
		case EBUSY:
			err = "entry in use";
			break;
		case ENOBUFS:
			err = "routing table overflow";
			break;
		default:
			err = strerror(oerrno);
			break;
		}
		(void) printf(": %s\n", err);
E 48
E 36
	}
I 36
D 50
	exit(0);
I 48
	/* NOTREACHED */
E 50
E 48
E 36
E 16
}

D 36
changeroute(argc, argv)
	int argc;
	char *argv[];
{
	printf("not supported\n");
}

E 36
D 48
error(cmd)
	char *cmd;
{
I 24
	extern int errno;
E 24
D 16
	extern int errno;
E 16

D 24
	if (errno == ESRCH)
E 24
I 24
	switch(errno) {
	case ESRCH:
E 24
D 29
		fprintf(stderr, "not in table\n");
E 29
I 29
		printf("not in table\n");
E 29
D 24
	else if (errno == EBUSY)
E 24
I 24
		break;
	case EBUSY:
E 24
D 29
		fprintf(stderr, "entry in use\n");
E 29
I 29
		printf("entry in use\n");
E 29
D 24
	else if (errno == ENOBUFS)
E 24
I 24
		break;
	case ENOBUFS:
E 24
D 29
		fprintf(stderr, "routing table overflow\n");
E 29
I 29
		printf("routing table overflow\n");
E 29
D 24
	else
E 24
I 24
		break;
	default:
I 30
		printf("ioctl returns %d\n", errno);
E 30
E 24
		perror(cmd);
I 24
	}
I 29
	fflush(stdout);
	errno = 0;
E 29
E 24
}

I 19
char *
savestr(s)
	char *s;
{
	char *sav;

	sav = malloc(strlen(s) + 1);
	if (sav == NULL) {
		fprintf("route: out of memory\n");
		exit(1);
	}
	strcpy(sav, s);
	return (sav);
}

E 48
I 48
void
E 48
I 30
D 31
u_long
inet_makenetandmask(net, mask)
u_long net, *mask;
E 31
I 31
D 36
inet_makenetandmask(net, sin, sockmask)
E 36
I 36
inet_makenetandmask(net, sin)
E 36
D 48
u_long net;
D 36
struct sockaddr_in *sin, *sockmask;
E 36
I 36
register struct sockaddr_in *sin;
E 48
I 48
	u_long net;
	register struct sockaddr_in *sin;
E 48
E 36
E 31
{
D 48
	u_long addr;
I 31
	u_long mask = 0;
E 48
I 48
	u_long addr, mask = 0;
E 48
I 36
	register char *cp;
E 36
E 31

I 36
	rtm_addrs |= RTA_NETMASK;
E 36
	if (net == 0)
D 31
		*mask = addr = 0;
E 31
I 31
		mask = addr = 0;
E 31
	else if (net < 128) {
		addr = net << IN_CLASSA_NSHIFT;
D 31
		*mask = IN_CLASSA_NET;
E 31
I 31
		mask = IN_CLASSA_NET;
E 31
	} else if (net < 65536) {
		addr = net << IN_CLASSB_NSHIFT;
D 31
		*mask = IN_CLASSB_NET;
E 31
I 31
		mask = IN_CLASSB_NET;
E 31
	} else if (net < 16777216L) {
		addr = net << IN_CLASSC_NSHIFT;
D 31
		*mask = IN_CLASSC_NET;
E 31
I 31
		mask = IN_CLASSC_NET;
E 31
	} else {
		addr = net;
		if ((addr & IN_CLASSA_HOST) == 0)
D 31
			*mask =  IN_CLASSA_NET;
E 31
I 31
			mask =  IN_CLASSA_NET;
E 31
		else if ((addr & IN_CLASSB_HOST) == 0)
D 31
			*mask =  IN_CLASSB_NET;
E 31
I 31
			mask =  IN_CLASSB_NET;
E 31
		else if ((addr & IN_CLASSC_HOST) == 0)
D 31
			*mask =  IN_CLASSC_NET;
E 31
I 31
			mask =  IN_CLASSC_NET;
E 31
		else
D 31
			*mask = -1;
E 31
I 31
			mask = -1;
E 31
	}
D 31
	*mask = htonl(*mask);
	return (htonl(addr));
E 31
I 31
D 36
	sin->sin_addr.s_addr = (htonl(addr));
	if (sockmask) {
D 32
		register char *cp = (char *)(sockmask->sin_zero);
E 32
I 32
		register char *cp = (char *)&(sockmask->sin_port);
E 32
		register char *cpbase = (char *)&(sockmask->sin_addr);

		sockmask->sin_addr.s_addr = htonl(mask);
		sockmask->sin_len = 0;
		sockmask->sin_family = 0;
		while (--cp >= cpbase)
			if (*cp) {
				sockmask->sin_len = 1 + cp - (caddr_t)sockmask;
				break;
			}
	}
E 36
I 36
	sin->sin_addr.s_addr = htonl(addr);
	sin = &so_mask.sin;
	sin->sin_addr.s_addr = htonl(mask);
	sin->sin_len = 0;
	sin->sin_family = 0;
D 48
	cp = (char *)(1 + &(sin->sin_addr));
E 48
I 48
	cp = (char *)(&sin->sin_addr + 1);
E 48
	while (*--cp == 0 && cp > (char *)sin)
		;
	sin->sin_len = 1 + cp - (char *)sin;
E 36
E 31
}

E 30
E 19
I 9
/*
 * Interpret an argument as a network address of some kind,
 * returning 1 if a host address, 0 if a network address.
 */
I 48
int
E 48
E 9
D 16
getaddr(s, sin)
E 16
I 16
D 17
getaddr(s, sin, hpp)
E 17
I 17
D 20
getaddr(s, sin, hpp, name)
E 20
I 20
D 30
getaddr(s, sin, hpp, name, isnet)
E 30
I 30
D 36
getaddr(s, sin, sockmask, hpp, name, isnet)
E 36
I 36
getaddr(which, s, hpp)
I 48
	int which;
E 48
E 36
E 30
E 20
E 17
E 16
	char *s;
D 30
	struct sockaddr_in *sin;
E 30
I 30
D 36
	struct sockaddr_in *sin, *sockmask;
E 36
E 30
I 16
	struct hostent **hpp;
I 17
D 36
	char **name;
I 20
	int isnet;
E 36
E 20
E 17
E 16
{
I 26
D 36
	struct sockaddr_ns *sns = (struct sockaddr_ns *)sin;
E 36
I 36
D 46
	register union sockunion *su;
E 46
I 46
	register sup su;
E 46
E 36
D 48
	struct	ns_addr ns_addr();
E 48
I 48
	struct ns_addr ns_addr();
E 48
I 36
D 39
	struct iso_addr iso_addr();
E 39
I 39
	struct iso_addr *iso_addr();
E 39
E 36
E 26
D 3
	sin->sin_family = AF_INET;
	if ((sin->sin_addr.s_addr = rhost(&s)) != -1)
E 3
I 3
	struct hostent *hp;
I 6
	struct netent *np;
D 30
	u_long val;
E 30
I 30
D 31
	u_long val, mask = 0;
E 31
I 31
D 32
	u_long val;
E 32
I 32
D 36
	u_long val = 1;
E 36
I 36
	u_long val;
E 36
E 32
E 31
E 30
E 6

I 36
D 39
	if (af == 0)
E 39
I 39
	if (af == 0) {
E 39
		af = AF_INET;
I 39
		aflen = sizeof(struct sockaddr_in);
	}
	rtm_addrs |= which;
E 39
	switch (which) {
D 39
	case RTA_DST:		su = so_addrs[0]; break;
	case RTA_GATEWAY:	su = so_addrs[1]; break;
	case RTA_NETMASK:		su = so_addrs[2]; break;
E 39
I 39
D 55
	case RTA_DST:		su = so_addrs[0]; su->sa.sa_family = af; break;
	case RTA_GATEWAY:	su = so_addrs[1]; su->sa.sa_family = af; break;
	case RTA_NETMASK:	su = so_addrs[2]; break;
E 39
	case RTA_GENMASK:	su = so_addrs[3]; break;
I 46
	case RTA_IFP:		su = so_addrs[4]; su->sa.sa_family = af; break;
	case RTA_IFA:		su = so_addrs[5]; su->sa.sa_family = af; break;
E 46
	default:		usage("Internal Error"); /*NOTREACHED*/
E 55
I 55
	case RTA_DST:
		su = &so_dst;
		su->sa.sa_family = af;
		break;
	case RTA_GATEWAY:
		su = &so_gate;
		su->sa.sa_family = af;
		break;
	case RTA_NETMASK:
		su = &so_mask;
		break;
	case RTA_GENMASK:
		su = &so_genmask;
		break;
	case RTA_IFP:
		su = &so_ifp;
		su->sa.sa_family = af;
		break;
	case RTA_IFA:
		su = &so_ifa;
		su->sa.sa_family = af;
		break;
	default:
		usage("Internal Error");
		/*NOTREACHED*/
E 55
	}
D 39
	rtm_addrs |= which;
	su->sa.sa_family = af;
E 39
I 39
	su->sa.sa_len = aflen;
E 39
E 36
I 32
	if (strcmp(s, "default") == 0) {
D 36
		val = 0;
		*name = "default";
E 36
I 36
D 39
		su->sa.sa_len = 0;
		if (which == RTA_DST)
E 39
I 39
		switch (which) {
		case RTA_DST:
			forcenet++;
E 39
D 48
			getaddr(RTA_NETMASK, s, 0);
E 48
I 48
			(void) getaddr(RTA_NETMASK, s, 0);
E 48
I 39
			break;
		case RTA_NETMASK:
		case RTA_GENMASK:
			su->sa.sa_len = 0;
		}
E 39
D 55
		return 0;
E 55
I 55
		return (0);
E 55
E 36
	}
E 32
I 26
D 36
	if (xnsflag)
E 36
I 36
D 55
	if (af == AF_NS)
E 36
		goto do_xns;
E 26
I 16
D 32
	*hpp = 0;
E 32
I 32
D 36
	if (osiflag)
E 36
I 36
	if (af == AF_OSI)
E 36
		goto do_osi;
E 32
I 30
D 36
	sin->sin_family = AF_INET;
	sin->sin_len = sizeof(*sin);
E 30
E 16
I 8
D 32
	if (strcmp(s, "default") == 0) {
D 30
		sin->sin_family = AF_INET;
		sin->sin_addr = inet_makeaddr(0, INADDR_ANY);
E 30
I 30
D 31
		sin->sin_addr.s_addr = 0;
E 31
I 31
		val = 0;
E 31
E 30
I 19
		*name = "default";
E 32
I 32
	if (val == 0)
E 32
E 19
D 9
		return;
E 9
I 9
D 30
		return(0);
E 30
I 30
D 31
		isnet = 0;
E 31
		goto out;
E 36
I 36
	if (af == AF_LINK)
		goto do_link;
I 52
	if (af == AF_CCITT)
		goto do_ccitt;
D 53
	if (af == 0)
E 53
I 53
	if (af == PF_ROUTE)
E 53
		goto do_sa;
E 55
I 55
	switch (af) {
	case AF_NS:
		if (which == RTA_DST) {
			extern short ns_bh[3];
			struct sockaddr_ns *sms = &(so_mask.sns);
D 69
			bzero((char *)sms, sizeof(*sms));
E 69
I 69
			memset(sms, 0, sizeof(*sms));
E 69
			sms->sns_family = 0;
			sms->sns_len = 6;
			sms->sns_addr.x_net = *(union ns_net *)ns_bh;
			rtm_addrs |= RTA_NETMASK;
		}
		su->sns.sns_addr = ns_addr(s);
		return (!ns_nullhost(su->sns.sns_addr));

	case AF_OSI:
		su->siso.siso_addr = *iso_addr(s);
		if (which == RTA_NETMASK || which == RTA_GENMASK) {
			register char *cp = (char *)TSEL(&su->siso);
			su->siso.siso_nlen = 0;
			do {--cp ;} while ((cp > (char *)su) && (*cp == 0));
			su->siso.siso_len = 1 + cp - (char *)su;
		}
		return (1);

	case AF_LINK:
		link_addr(s, &su->sdl);
		return (1);

	case AF_CCITT:
		ccitt_addr(s, &su->sx25);
D 58
		return (1);
E 58
I 58
		return (which == RTA_DST ? x25_makemask() : 1);
E 58

	case PF_ROUTE:
		su->sa.sa_len = sizeof(*su);
		sockaddr(s, &su->sa);
		return (1);

	case AF_INET:
	default:
		break;
	}

E 55
E 52
D 39
	su->sin.sin_len = sizeof(su->sin);
E 39
D 48
	if (hpp == 0) hpp = &hp;
E 36
E 30
E 9
D 32
	}
E 32
I 32
	*hpp = 0;
E 48
I 48
	if (hpp == NULL)
		hpp = &hp;
	*hpp = NULL;
E 48
E 32
I 16
D 30
	sin->sin_family = AF_INET;
E 30
D 20
	val = inet_addr(s);
	if (val != -1) {
		sin->sin_addr.s_addr = val;
I 17
		*name = s;
E 17
		return(inet_lnaof(sin->sin_addr) != INADDR_ANY);
E 20
I 20
D 36
	if (isnet == 0) {
		val = inet_addr(s);
		if (val != -1) {
			sin->sin_addr.s_addr = val;
			*name = s;
D 30
			return(inet_lnaof(sin->sin_addr) != INADDR_ANY);
E 30
I 30
			if (inet_lnaof(sin->sin_addr) != INADDR_ANY)
				return (1);
			else
				goto out;
E 36
I 36
D 38
	if (forcenet == 0 && (val = inet_addr(s)) != -1) {
E 38
I 38
	if (((val = inet_addr(s)) != -1) &&
	    (which != RTA_DST || forcenet == 0)) {
E 38
		su->sin.sin_addr.s_addr = val;
		if (inet_lnaof(su->sin.sin_addr) != INADDR_ANY)
			return (1);
		else {
			val = ntohl(val);
D 55
		out:	if (which == RTA_DST)
				inet_makenetandmask(val, &su->sin);
			return (0);
E 55
I 55
			goto netdone;
E 55
E 36
E 30
		}
E 20
	}
D 58
	val = inet_network(s);
D 55
	if (val != -1) {
D 30
		sin->sin_addr = inet_makeaddr(val, INADDR_ANY);
E 30
I 30
D 31
		sin->sin_addr.s_addr = inet_makenetandmask(val, &mask);
E 31
E 30
I 17
D 36
		*name = s;
E 36
E 17
D 30
		return(0);
E 30
I 30
D 31
		goto gotmask;
E 31
I 31
		goto out;
E 31
E 30
	}
E 16
E 8
D 10
	hp = gethostbyname(s);
D 6
	if (hp == 0) {
		sin->sin_addr.s_addr = inet_addr(s);
		if (sin->sin_addr.s_addr == -1) {
			fprintf(stderr, "%s: bad value\n", s);
			exit(1);
		}
		sin->sin_family = AF_INET;
E 6
I 6
	if (hp) {
		sin->sin_family = hp->h_addrtype;
		bcopy(hp->h_addr, &sin->sin_addr, hp->h_length);
E 6
E 3
D 9
		return;
E 9
I 9
		return(1);
E 9
D 3
	if (!isdigit(*s)) {
		fprintf(stderr, "%s: unknown host\n", s);
		exit(1);
E 3
	}
E 10
D 3
	sin->sin_addr.s_addr = atoi(s);
	if (sin->sin_addr.s_addr == -1) {
		fprintf(stderr, "%s: bad value\n", s);
		exit(1);
	}
I 2
}

/*
 * Return the local network address portion of an
 * internet address; handles class a/b/c network
 * number formats.
 */
in_lnaof(in)
	struct in_addr in;
{
#if vax || pdp11
#define	IN_LNAOF(in) \
	(((in).s_addr&IN_CLASSA) == 0 ? (in).s_addr&IN_CLASSA_LNA : \
		((in).s_addr&IN_CLASSB) == 0 ? (in).s_addr&IN_CLASSB_LNA : \
			(in).s_addr&IN_CLASSC_LNA)
	return ((int)htonl((u_long)IN_LNAOF(in)));
#else
	return (IN_LNAOF(in));
#endif
E 3
I 3
D 6
	sin->sin_family = hp->h_addrtype;
	bcopy(hp->h_addr, &sin->sin_addr, hp->h_length);
E 6
I 6
	np = getnetbyname(s);
	if (np) {
E 55
I 55
	if (val == -1 && (np = getnetbyname(s)) != NULL) {
E 55
D 30
		sin->sin_family = np->n_addrtype;
		sin->sin_addr = inet_makeaddr(np->n_net, INADDR_ANY);
E 30
I 30
D 31
		sin->sin_addr.s_addr = inet_makenetandmask(np->n_net, &mask);
E 31
I 31
		val = np->n_net;
E 58
I 58
	if ((val = inet_network(s)) != -1 ||
	    ((np = getnetbyname(s)) != NULL && (val = np->n_net) != 0)) {
E 58
E 31
E 30
I 17
D 19
		*name = np->n_name;
E 19
I 19
D 36
		*name = savestr(np->n_name);
E 36
E 19
E 17
D 9
		return;
E 9
I 9
D 30
		return(0);
E 30
I 30
D 31
		goto gotmask;
E 31
I 31
D 55
		goto out;
E 55
I 55
netdone:
		if (which == RTA_DST)
			inet_makenetandmask(val, &su->sin);
		return (0);
E 55
E 31
E 30
I 10
	}
	hp = gethostbyname(s);
	if (hp) {
I 16
		*hpp = hp;
E 16
D 36
		sin->sin_family = hp->h_addrtype;
		bcopy(hp->h_addr, &sin->sin_addr, hp->h_length);
I 17
D 19
		*name = hp->h_name;
E 19
I 19
		*name = savestr(hp->h_name);
E 36
I 36
		su->sin.sin_family = hp->h_addrtype;
D 48
		bcopy(hp->h_addr, &su->sin.sin_addr, hp->h_length);
E 48
I 48
D 69
		bcopy(hp->h_addr, (char *)&su->sin.sin_addr, hp->h_length);
E 69
I 69
		memmove(&su->sin.sin_addr, hp->h_addr, hp->h_length);
E 69
E 48
E 36
E 19
E 17
D 30
		return(1);
E 30
I 30
		return (1);
E 30
E 10
E 9
D 16
	}
	sin->sin_family = AF_INET;
	val = inet_addr(s);
	if (val != -1) {
		sin->sin_addr.s_addr = val;
D 9
		return;
E 9
I 9
		return(inet_lnaof(sin->sin_addr) != INADDR_ANY);
E 9
	}
	val = inet_network(s);
	if (val != -1) {
		sin->sin_addr = inet_makeaddr(val, INADDR_ANY);
D 9
		return;
E 9
I 9
		return(0);
E 16
E 9
	}
D 48
	fprintf(stderr, "%s: bad value\n", s);
E 48
I 48
	(void) fprintf(stderr, "%s: bad value\n", s);
E 48
	exit(1);
I 58
}

I 66
int
E 66
x25_makemask()
{
	register char *cp;

	if ((rtm_addrs & RTA_NETMASK) == 0) {
		rtm_addrs |= RTA_NETMASK;
		for (cp = (char *)&so_mask.sx25.x25_net;
		     cp < &so_mask.sx25.x25_opts.op_flags; cp++)
			*cp = -1;
		so_mask.sx25.x25_len = (u_char)&(((sup)0)->sx25.x25_opts);
	}
	return 0;
E 58
I 30
D 31
out:	if (mask == 0)
		(void) inet_makenetandmask(sin->sin_addr.s_addr, &mask);
gotmask:if (sockmask) {
		sockmask->sin_family = 0;
		sockmask->sin_len = 8;
		sockmask->sin_addr.s_addr = mask;
	}
	return (mask == -1L ? 1 : 0);
E 31
I 31
D 36
out:
	inet_makenetandmask(val, sin, sockmask);
	return (0);
E 36
E 31
E 30
I 26
D 55
do_xns:
D 30
	bzero((char *)sns, sizeof (*sns));
E 30
I 30
D 36
	bzero((char *)sns, sizeof(*sns));
E 30
	sns->sns_family = AF_NS;
I 30
	sns->sns_len = sizeof (*sns);
E 36
I 36
D 39
	su->sns.sns_len = sizeof (su->sns);
E 39
E 36
I 32
D 47
	if (val == 0)
		return(0);
E 47
E 32
D 36
	if (sockmask) {
E 36
I 36
	if (which == RTA_DST) {
E 36
		extern short ns_bh[3];
D 31
		struct sockaddr_ns *sms = (struct sockaddr_ns *)&sockmask;
E 31
I 31
D 36
		struct sockaddr_ns *sms = (struct sockaddr_ns *)sockmask;
E 31
		bzero((char *)sms, sizeof(*sns));
E 36
I 36
		struct sockaddr_ns *sms = &(so_mask.sns);
		bzero((char *)sms, sizeof(*sms));
E 36
		sms->sns_family = 0;
		sms->sns_len = 6;
		sms->sns_addr.x_net = *(union ns_net *)ns_bh;
I 36
		rtm_addrs |= RTA_NETMASK;
E 36
	}
E 30
D 32
	if (strcmp(s, "default") == 0) {
		*name = "default";
I 31
		if (sockmask)
			sockmask->sin_len = 0;
E 31
		return(0);
	}
E 32
I 30
D 36
	*name = s;
E 30
	sns->sns_addr = ns_addr(s);
	return (!ns_nullhost(sns->sns_addr));
E 36
I 36
	su->sns.sns_addr = ns_addr(s);
	return (!ns_nullhost(su->sns.sns_addr));
E 36
I 32
do_osi:
D 36
    {
	struct sockaddr_iso *siso = (struct sockaddr_iso *)sin;
	struct iso_addr iso_addr();

	siso->siso_family = AF_ISO;
	siso->siso_len = sizeof(*siso);
	if (val == 0)
		return (0);
	*name = s;
	siso->siso_addr = iso_addr(s);
E 36
I 36
D 39
	su->siso.siso_len = sizeof(su->siso);
	su->siso.siso_addr = iso_addr(s);
E 39
I 39
	su->siso.siso_addr = *iso_addr(s);
	if (which == RTA_NETMASK || which == RTA_GENMASK) {
		register char *cp = (char *)TSEL(&su->siso);
		su->siso.siso_nlen = 0;
		do {--cp ;} while ((cp > (char *)su) && (*cp == 0));
		su->siso.siso_len = 1 + cp - (char *)su;
	}
E 39
E 36
	return (1);
I 52
do_ccitt:
	ccitt_addr(s, &su->sx25);
	return (1);
E 52
D 36
    }
E 36
I 36
do_link:
D 39
	su->sdl.sdl_len = sizeof(su->sdl);
E 39
	link_addr(s, &su->sdl);
	return (1);
I 52
do_sa:
	su->sa.sa_len = sizeof(*su);
	sockaddr(s, &su->sa);
	return (1);
E 55
E 52
E 36
E 32
E 26
I 21
}

short ns_nullh[] = {0,0,0};
short ns_bh[] = {-1,-1,-1};

char *
ns_print(sns)
D 48
struct sockaddr_ns *sns;
E 48
I 48
	struct sockaddr_ns *sns;
E 48
{
	struct ns_addr work;
	union { union ns_net net_e; u_long long_e; } net;
	u_short port;
	static char mybuf[50], cport[10], chost[25];
	char *host = "";
D 48
	register char *p; register u_char *q; u_char *q_lim;
E 48
I 48
	register char *p;
	register u_char *q;
E 48

	work = sns->sns_addr;
	port = ntohs(work.x_port);
	work.x_port = 0;
	net.net_e  = work.x_net;
	if (ns_nullhost(work) && net.long_e == 0) {
D 48
		if (port ) {
D 23
			sprintf(mybuf, "*.%xH", port);
E 23
I 23
			(void)sprintf(mybuf, "*.%xH", port);
E 23
			upHex(mybuf);
		} else
D 23
			sprintf(mybuf, "*.*");
E 23
I 23
			(void)sprintf(mybuf, "*.*");
E 48
I 48
		if (!port)
			return ("*.*");
		(void) sprintf(mybuf, "*.%XH", port);
E 48
E 23
		return (mybuf);
	}

D 48
	if (bcmp(ns_bh, work.x_host.c_host, 6) == 0) { 
E 48
I 48
D 66
	if (bcmp((char *)ns_bh, (char *)work.x_host.c_host, 6) == 0) 
E 66
I 66
D 70
	if (bcmp((char *)ns_bh, (char *)work.x_host.c_host, 6) == 0)
E 70
I 70
	if (memcmp(ns_bh, work.x_host.c_host, 6) == 0)
E 70
E 66
E 48
		host = "any";
D 48
	} else if (bcmp(ns_nullh, work.x_host.c_host, 6) == 0) {
E 48
I 48
D 70
	else if (bcmp((char *)ns_nullh, (char *)work.x_host.c_host, 6) == 0)
E 70
I 70
	else if (memcmp(ns_nullh, work.x_host.c_host, 6) == 0)
E 70
E 48
		host = "*";
D 48
	} else {
E 48
I 48
	else {
E 48
		q = work.x_host.c_host;
D 23
		sprintf(chost, "%02x%02x%02x%02x%02x%02xH",
E 23
I 23
D 48
		(void)sprintf(chost, "%02x%02x%02x%02x%02x%02xH",
E 48
I 48
		(void) sprintf(chost, "%02X%02X%02X%02X%02X%02XH",
E 48
E 23
			q[0], q[1], q[2], q[3], q[4], q[5]);
D 48
		for (p = chost; *p == '0' && p < chost + 12; p++);
E 48
I 48
		for (p = chost; *p == '0' && p < chost + 12; p++)
			/* void */;
E 48
		host = p;
	}
	if (port)
D 23
		sprintf(cport, ".%xH", htons(port));
E 23
I 23
D 48
		(void)sprintf(cport, ".%xH", htons(port));
E 48
I 48
		(void) sprintf(cport, ".%XH", htons(port));
E 48
E 23
	else
		*cport = 0;

D 23
	sprintf(mybuf,"%xH.%s%s", ntohl(net.long_e), host, cport);
E 23
I 23
D 48
	(void)sprintf(mybuf,"%xH.%s%s", ntohl(net.long_e), host, cport);
E 23
	upHex(mybuf);
	return(mybuf);
E 48
I 48
	(void) sprintf(mybuf,"%XH.%s%s", ntohl(net.long_e), host, cport);
	return (mybuf);
E 48
}

D 48
upHex(p0)
char *p0;
{
	register char *p = p0;
	for (; *p; p++) switch (*p) {

	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
		*p += ('A' - 'a');
	}
I 30
}

E 48
I 48
void
I 60
interfaces()
{
D 64
	int needed, rlen, af;
E 64
I 64
	size_t needed;
D 66
	int mib[6], af;
E 66
I 66
	int mib[6];
E 66
E 64
	char *buf, *lim, *next;
	register struct rt_msghdr *rtm;

D 64
	if ((needed = getkerninfo(KINFO_RT_IFLIST, 0, 0, 0)) < 0)
		quit("route-getkerninfo-estimate");
E 64
I 64
	mib[0] = CTL_NET;
	mib[1] = PF_ROUTE;
	mib[2] = 0;		/* protocol */
	mib[3] = 0;		/* wildcard address family */
	mib[4] = NET_RT_IFLIST;
	mib[5] = 0;		/* no flags */
	if (sysctl(mib, 6, NULL, &needed, NULL, 0) < 0)
		quit("route-sysctl-estimate");
E 64
	if ((buf = malloc(needed)) == NULL)
		quit("malloc");
D 64
	if ((rlen = getkerninfo(KINFO_RT_IFLIST, buf, &needed, 0)) < 0)
E 64
I 64
	if (sysctl(mib, 6, buf, &needed, NULL, 0) < 0)
E 64
		quit("actual retrieval of interface table");
D 64
	lim = buf + rlen;
E 64
I 64
	lim = buf + needed;
E 64
	for (next = buf; next < lim; next += rtm->rtm_msglen) {
		rtm = (struct rt_msghdr *)next;
		print_rtmsg(rtm, rtm->rtm_msglen);
	}
}

void
E 60
E 48
monitor()
{
	int n;
	char msg[2048];
I 48

E 48
I 34
	verbose = 1;
I 60
	if (debugonly) {
		interfaces();
		exit(0);
	}
E 60
E 34
	for(;;) {
		n = read(s, msg, 2048);
D 48
		printf("got message of size %d\n", n);
E 48
I 48
		(void) printf("got message of size %d\n", n);
E 48
D 36
		print_rtmsg((struct rt_msghdr *)msg, n);
E 36
I 36
D 59
		print_rtmsg((struct rt_msghdr *)msg);
E 59
I 59
		print_rtmsg((struct rt_msghdr *)msg, n);
E 59
E 36
	}
}

struct {
	struct	rt_msghdr m_rtm;
D 36
	struct	sockaddr_in m_dst, m_gateway, m_mask;
E 36
I 36
D 48
	char m_space[512];
E 48
I 48
	char	m_space[512];
E 48
E 36
} m_rtmsg;

I 48
int
E 48
D 36
rtmsg(cmd, dst, gateway, mask, flags)
struct sockaddr_in *dst, *gateway, *mask;
E 36
I 36
rtmsg(cmd, flags)
I 48
	int cmd, flags;
E 48
E 36
{
	static int seq;
D 38
	int len = sizeof(m_rtmsg), rlen;
E 38
I 38
	int rlen;
E 38
D 48
	extern int errno;
E 48
I 36
	register char *cp = m_rtmsg.m_space;
	register int l;
E 36

I 46
D 47
#define ROUND(a) (1 + (((a) - 1) | (sizeof(long) - 1)))
#define NEXTADDR(w, u) { if (rtm_addrs & (w)) {l = (u).sa.sa_len;\
	if(verbose)sodump(&(u),"u");if(l == 0) l = sizeof(int); l = ROUND(l);\
		bcopy((char *)&(u), cp, l); cp += l;}}
E 47
I 47
#define NEXTADDR(w, u) \
	if (rtm_addrs & (w)) {\
D 69
	    l = ROUNDUP(u.sa.sa_len); bcopy((char *)&(u), cp, l); cp += l;\
E 69
I 69
	    l = ROUNDUP(u.sa.sa_len); memmove(cp, &(u), l); cp += l;\
E 69
	    if (verbose) sodump(&(u),"u");\
	}
E 47

E 46
	errno = 0;
D 69
	bzero((char *)&m_rtmsg, sizeof(m_rtmsg));
E 69
I 69
	memset(&m_rtmsg, 0, sizeof(m_rtmsg));
E 69
	if (cmd == 'a')
		cmd = RTM_ADD;
	else if (cmd == 'c')
		cmd = RTM_CHANGE;
I 46
D 55
	else if (cmd == 'g')
E 55
I 55
	else if (cmd == 'g') {
E 55
		cmd = RTM_GET;
E 46
D 55
	else
E 55
I 55
		if (so_ifp.sa.sa_family == 0) {
D 68
			so_ifp.sa.sa_family == AF_LINK;
			so_ifp.sa.sa_len == sizeof(struct sockaddr_dl);
E 68
I 68
			so_ifp.sa.sa_family = AF_LINK;
			so_ifp.sa.sa_len = sizeof(struct sockaddr_dl);
E 68
			rtm_addrs |= RTA_IFP;
		}
	} else
E 55
		cmd = RTM_DELETE;
D 46
	m_rtmsg.m_rtm.rtm_flags = flags;
D 35
	m_rtmsg.m_rtm.rtm_version = 1;
E 35
I 35
	m_rtmsg.m_rtm.rtm_version = RTM_VERSION;
E 35
	m_rtmsg.m_rtm.rtm_seq = ++seq;
D 36
	m_rtmsg.m_dst = *dst;
	m_rtmsg.m_gateway = *gateway;
I 35
	m_rtmsg.m_rtm.rtm_addrs = RTA_DST | RTA_GATEWAY;
E 35
	if (mask) {
		m_rtmsg.m_mask = *mask;
D 35
		m_rtmsg.m_rtm.rtm_count = 3;
E 35
I 35
		m_rtmsg.m_rtm.rtm_addrs = RTA_NETMASK;
E 35
	} else {
		len -= sizeof (*mask);
D 35
		m_rtmsg.m_rtm.rtm_count = 2;
E 35
	}
	m_rtmsg.m_rtm.rtm_msglen = len;
E 36
I 36
	m_rtmsg.m_rtm.rtm_addrs = rtm_addrs;
I 40
	m_rtmsg.m_rtm.rtm_rmx = rt_metrics;
I 41
	m_rtmsg.m_rtm.rtm_inits = rtm_inits;
E 46
I 46
#define rtm m_rtmsg.m_rtm
	rtm.rtm_type = cmd;
	rtm.rtm_flags = flags;
	rtm.rtm_version = RTM_VERSION;
	rtm.rtm_seq = ++seq;
	rtm.rtm_addrs = rtm_addrs;
	rtm.rtm_rmx = rt_metrics;
	rtm.rtm_inits = rtm_inits;
E 46
E 41
E 40

I 52
	if (rtm_addrs & RTA_NETMASK)
		mask_addr();
E 52
D 46
#define ROUND(a) (1 + (((a) - 1) | (sizeof(long) - 1)))
#define NEXTADDR(w, u) { if (rtm_addrs & (w)) {l = (u).sa.sa_len;\
	if(verbose)sodump(&(u),"u");if(l == 0) l = sizeof(int); l = ROUND(l);\
		bcopy((char *)&(u), cp, l); cp += l;}}

E 46
	NEXTADDR(RTA_DST, so_dst);
	NEXTADDR(RTA_GATEWAY, so_gate);
	NEXTADDR(RTA_NETMASK, so_mask);
	NEXTADDR(RTA_GENMASK, so_genmask);
D 38
	m_rtmsg.m_rtm.rtm_msglen = cp - (char *)&m_rtmsg;
E 38
I 38
D 46
	m_rtmsg.m_rtm.rtm_msglen = l = cp - (char *)&m_rtmsg;
E 38
E 36
	m_rtmsg.m_rtm.rtm_type = cmd;
E 46
I 46
	NEXTADDR(RTA_IFP, so_ifp);
	NEXTADDR(RTA_IFA, so_ifa);
	rtm.rtm_msglen = l = cp - (char *)&m_rtmsg;
E 46
I 36
	if (verbose)
D 38
		print_rtmsg(&m_rtmsg.m_rtm, len);
E 36
	if ((rlen = write(s, (char *)&m_rtmsg, len)) < 0) {
E 38
I 38
D 46
		print_rtmsg(&m_rtmsg.m_rtm, l);
E 46
I 46
		print_rtmsg(&rtm, l);
E 46
I 40
	if (debugonly)
D 54
		return 0;
E 54
I 54
		return (0);
E 54
E 40
	if ((rlen = write(s, (char *)&m_rtmsg, l)) < 0) {
E 38
		perror("writing to routing socket");
D 46
		printf("got only %d for rlen\n", rlen);
E 46
D 32
		return (rlen);
E 32
I 32
D 44
		return (-1);
E 32
	}
again:
D 38
	if ((rlen = read(s, (char *)&m_rtmsg, len)) < 0) {
E 38
I 38
	if ((rlen = read(s, (char *)&m_rtmsg, l)) < 0) {
E 38
		perror("reading from routing socket");
		printf("got only %d for rlen\n", rlen);
D 32
		return (rlen);
E 32
I 32
		return (-1);
E 32
	}
	if ((m_rtmsg.m_rtm.rtm_pid != pid) ||
	    (m_rtmsg.m_rtm.rtm_seq != seq)) {
		printf("Got response for somebody else's request");
		goto again;
	}
	if (qflag == 0)
		print_rtmsg( &m_rtmsg.m_rtm, rlen);
	if ((m_rtmsg.m_rtm.rtm_flags & RTF_DONE) == 0) {
		errno = m_rtmsg.m_rtm.rtm_errno;
		perror("response from routing socket turned down");
E 44
		return (-1);
	}
I 46
	if (cmd == RTM_GET) {
		do {
			l = read(s, (char *)&m_rtmsg, sizeof(m_rtmsg));
		} while (l > 0 && (rtm.rtm_seq != seq || rtm.rtm_pid != pid));
		if (l < 0)
D 48
			perror("reading from routing socket");
E 48
I 48
			(void) fprintf(stderr,
			    "route: read from routing socket: %s\n",
			    strerror(errno));
E 48
		else
			print_getmsg(&rtm, l);
	}
#undef rtm
E 46
	return (0);
}

I 66
void
E 66
I 52
D 54
mask_addr() {
E 54
I 54
mask_addr()
{
E 54
D 57
	register char *cp1, *cp2;
	int olen;
E 57
I 57
	int olen = so_mask.sa.sa_len;
	register char *cp1 = olen + (char *)&so_mask, *cp2;
E 57

I 57
	for (so_mask.sa.sa_len = 0; cp1 > (char *)&so_mask; )
		if (*--cp1 != 0) {
			so_mask.sa.sa_len = 1 + cp1 - (char *)&so_mask;
			break;
		}
E 57
	if ((rtm_addrs & RTA_DST) == 0)
		return;
D 54
	switch(so_dst.sa.sa_family) {
	case AF_NS: case AF_INET: case 0:
E 54
I 54
	switch (so_dst.sa.sa_family) {
	case AF_NS:
	case AF_INET:
I 57
	case AF_CCITT:
E 57
	case 0:
E 54
		return;
	case AF_ISO:
D 63
		olen = MIN(so_dst.siso.siso_nlen, so_mask.sa.sa_len - 6);
E 63
I 63
		olen = MIN(so_dst.siso.siso_nlen,
			   MAX(so_mask.sa.sa_len - 6, 0));
E 63
I 54
		break;
E 54
	}
	cp1 = so_mask.sa.sa_len + 1 + (char *)&so_dst;
	cp2 = so_dst.sa.sa_len + 1 + (char *)&so_dst;
	while (cp2 > cp1)
		*--cp2 = 0;
	cp2 = so_mask.sa.sa_len + 1 + (char *)&so_mask;
	while (cp1 > so_dst.sa.sa_data)
		*--cp1 &= *--cp2;
D 54
	switch(so_dst.sa.sa_family) {
E 54
I 54
	switch (so_dst.sa.sa_family) {
E 54
	case AF_ISO:
		so_dst.siso.siso_nlen = olen;
I 54
		break;
E 54
	}
}

E 52
char *msgtypes[] = {
D 48
"",
"RTM_ADD: Add Route",
"RTM_DELETE: Delete Route",
"RTM_CHANGE: Change Metrics or flags",
"RTM_GET: Report Metrics",
"RTM_LOSING: Kernel Suspects Partitioning",
"RTM_REDIRECT: Told to use different route",
"RTM_MISS: Lookup failed on this address",
"RTM_LOCK: fix specified metrics",
"RTM_OLDADD: caused by SIOCADDRT",
"RTM_OLDDEL: caused by SIOCDELRT",
0, };
E 48
I 48
	"",
	"RTM_ADD: Add Route",
	"RTM_DELETE: Delete Route",
	"RTM_CHANGE: Change Metrics or flags",
	"RTM_GET: Report Metrics",
	"RTM_LOSING: Kernel Suspects Partitioning",
	"RTM_REDIRECT: Told to use different route",
	"RTM_MISS: Lookup failed on this address",
	"RTM_LOCK: fix specified metrics",
	"RTM_OLDADD: caused by SIOCADDRT",
	"RTM_OLDDEL: caused by SIOCDELRT",
I 59
	"RTM_RESOLVE: Route created by cloning",
	"RTM_NEWADDR: address being added to iface",
	"RTM_DELADDR: address being removed from iface",
	"RTM_IFINFO: iface status change",
E 59
	0,
};
E 48

char metricnames[] =
D 40
"\010rttvar\7rtt\6ssthresh\7sendpipe\4recvpipe\3expire\2hopcount\1mtu";
E 40
I 40
D 59
"\010rttvar\7rtt\6ssthresh\5sendpipe\4recvpipe\3expire\2hopcount\1mtu";
E 59
I 59
"\011pksent\010rttvar\7rtt\6ssthresh\5sendpipe\4recvpipe\3expire\2hopcount\1mtu";
E 59
D 66
char routeflags[] = 
E 66
I 66
char routeflags[] =
E 66
D 45
"\1UP\2GATEWAY\3HOST\5DYNAMIC\6MODIFIED\7DONE\010MASK_PRESENT\011CLONING\012XRESOLVE";
E 45
I 45
D 51
"\1UP\2GATEWAY\3HOST\4REJECT\5DYNAMIC\6MODIFIED\7DONE\010MASK_PRESENT\011CLONING\012XRESOLVE";
E 51
I 51
D 57
"\1UP\2GATEWAY\3HOST\4REJECT\5DYNAMIC\6MODIFIED\7DONE\010MASK_PRESENT\011CLONING\012XRESOLVE\013LLINFO\017PROTO2\020PROTO1";
E 57
I 57
"\1UP\2GATEWAY\3HOST\4REJECT\5DYNAMIC\6MODIFIED\7DONE\010MASK_PRESENT\011CLONING\012XRESOLVE\013LLINFO\014STATIC\017PROTO2\020PROTO1";
I 59
D 66
char ifnetflags[] = 
E 66
I 66
char ifnetflags[] =
E 66
D 63
"\1UP\2BROADCAST\3DEBUG\4LOOPBACK\5PTP\6NOTRAILERS\7RUNNING\010NOARP\011PPROMISC\012ALLMULTI\013OACTIVE\014SIMPLEX\015LINK0\016LINK1\017LINK2";
E 63
I 63
"\1UP\2BROADCAST\3DEBUG\4LOOPBACK\5PTP\6NOTRAILERS\7RUNNING\010NOARP\011PPROMISC\012ALLMULTI\013OACTIVE\014SIMPLEX\015LINK0\016LINK1\017LINK2\020MULTICAST";
E 63
char addrnames[] =
"\1DST\2GATEWAY\3NETMASK\4GENMASK\5IFP\6IFA\7AUTHOR\010BRD";
E 59
E 57
E 51
E 45
E 40

D 47
#define ROUNDUP(a) ((char *)(1 + (((((int)a)) - 1) | (sizeof(long) - 1))))
E 47
D 59

E 59
I 48
void
E 48
D 46
print_rtmsg(rtm, n)
E 46
I 46
print_rtmsg(rtm, msglen)
E 46
D 48
register struct rt_msghdr *rtm;
E 48
I 48
	register struct rt_msghdr *rtm;
	int msglen;
E 48
{
I 59
	struct if_msghdr *ifm;
	struct ifa_msghdr *ifam;

E 59
D 46
	char *cp;
	register struct sockaddr *sa;
D 35
	int i = rtm->rtm_count;
E 35
I 35
	int i;
E 35

E 46
I 32
	if (verbose == 0)
		return;
E 32
D 35
	if (rtm->rtm_version != 1) {
E 35
I 35
	if (rtm->rtm_version != RTM_VERSION) {
E 35
D 31
		printf("routing message version %d not understood\n",
E 31
I 31
D 48
	    printf("routing message version %d not understood\n",
E 31
							rtm->rtm_version);
D 31
		return;
E 31
I 31
D 46
	} else {
	    printf("%s\npid: %d, len %d, seq %d, errno %d, flags:",
		    msgtypes[rtm->rtm_type], rtm->rtm_pid, rtm->rtm_msglen,
		    rtm->rtm_seq, rtm->rtm_errno); 
D 40
	    bprintf(stdout, rtm->rtm_flags,
		"\1UP\2GATEWAY\3HOST\5DYNAMIC\6MODIFIED\7DONE\010MASK_PRESENT");
E 40
I 40
	    bprintf(stdout, rtm->rtm_flags, routeflags);
E 40
D 35
	    printf("\nlocks: "); bprintf(stdout, rtm->rtm_locks, metricnames);
E 35
I 35
	    printf("\nlocks: "); bprintf(stdout, rtm->rtm_rmx.rmx_locks, metricnames);
E 35
	    printf(" inits: "); bprintf(stdout, rtm->rtm_inits, metricnames);
D 36
	    printf("\n%d sockaddrs: ", i);
E 36
I 36
	    printf("\nsockaddrs: ");
E 36
I 35
	    bprintf(stdout, rtm->rtm_addrs,
		"\1DST\2GATEWAY\3NETMASK\4GENMASK\5IFP\6IFA\7AUTHOR");
	    putchar('\n');
E 35
	    cp = ((char *)(rtm + 1));
D 35
	    while (i-- > 0) {
		    sa = (struct sockaddr *)cp;
		    printf(" %s", routename(sa));
		    cp = ROUNDUP(cp + sa->sa_len);
	    }
E 35
I 35
	    if (rtm->rtm_addrs)
		for (i = 1; i; i <<= 1)
		    if (i & rtm->rtm_addrs) {
			    sa = (struct sockaddr *)cp;
			    printf(" %s", routename(sa));
			    cp = ROUNDUP(cp + sa->sa_len);
		    }
E 35
	    putchar('\n');
E 46
I 46
	    return;
E 48
I 48
		(void) printf("routing message version %d not understood\n",
		    rtm->rtm_version);
		return;
E 48
E 46
E 31
	}
I 46
D 48
	printf("%s\npid: %d, len %d, seq %d, errno %d, flags:",
E 48
I 48
D 59
	(void) printf("%s\npid: %d, len %d, seq %d, errno %d, flags:",
E 48
		msgtypes[rtm->rtm_type], rtm->rtm_pid, rtm->rtm_msglen,
		rtm->rtm_seq, rtm->rtm_errno); 
	bprintf(stdout, rtm->rtm_flags, routeflags);
	pmsg_common(rtm);
E 59
I 59
	(void)printf("%s: len %d, ", msgtypes[rtm->rtm_type], rtm->rtm_msglen);
	switch (rtm->rtm_type) {
	case RTM_IFINFO:
		ifm = (struct if_msghdr *)rtm;
		(void) printf("if# %d, flags:", ifm->ifm_index);
		bprintf(stdout, ifm->ifm_flags, ifnetflags);
		pmsg_addrs((char *)(ifm + 1), ifm->ifm_addrs);
		break;
	case RTM_NEWADDR:
	case RTM_DELADDR:
D 61
		(void) printf("flags:");
E 61
		ifam = (struct ifa_msghdr *)rtm;
I 61
		(void) printf("metric %d, flags:", ifam->ifam_metric);
E 61
		bprintf(stdout, ifam->ifam_flags, routeflags);
		pmsg_addrs((char *)(ifam + 1), ifam->ifam_addrs);
		break;
	default:
		(void) printf("pid: %d, seq %d, errno %d, flags:",
D 66
			rtm->rtm_pid, rtm->rtm_seq, rtm->rtm_errno); 
E 66
I 66
			rtm->rtm_pid, rtm->rtm_seq, rtm->rtm_errno);
E 66
		bprintf(stdout, rtm->rtm_flags, routeflags);
		pmsg_common(rtm);
	}
E 59
}

I 48
void
E 48
print_getmsg(rtm, msglen)
D 48
register struct rt_msghdr *rtm;
E 48
I 48
	register struct rt_msghdr *rtm;
	int msglen;
E 48
{
I 54
	struct sockaddr *dst = NULL, *gate = NULL, *mask = NULL;
I 55
	struct sockaddr_dl *ifp = NULL;
E 55
	register struct sockaddr *sa;
	register char *cp;
	register int i;

D 56
	(void) printf("   route to: %s\n", routename(so_addrs[0]));
E 56
I 56
	(void) printf("   route to: %s\n", routename(&so_dst));
E 56
E 54
	if (rtm->rtm_version != RTM_VERSION) {
D 48
		printf("routing message version %d not understood\n",
							    rtm->rtm_version);
E 48
I 48
D 54
		(void)printf("routing message version %d not understood\n",
E 54
I 54
		(void)fprintf(stderr,
		    "routing message version %d not understood\n",
E 54
		    rtm->rtm_version);
E 48
		return;
	}
D 47
	if (rtm->rtm_msglen != msglen) {
E 47
I 47
	if (rtm->rtm_msglen > msglen) {
E 47
D 48
		printf("get length mismatch, in packet %d, returned %d\n",
			rtm->rtm_msglen, msglen);
E 48
I 48
D 54
		(void)printf("get length mismatch, in packet %d, returned %d\n",
E 54
I 54
		(void)fprintf(stderr,
		    "message length mismatch, in packet %d, returned %d\n",
E 54
		    rtm->rtm_msglen, msglen);
E 48
D 47
		return;
E 47
	}
D 48
	printf("RTM_GET: errno %d, flags:", rtm->rtm_errno); 
E 48
I 48
D 54
	(void) printf("RTM_GET: errno %d, flags:", rtm->rtm_errno); 
E 54
I 54
	if (rtm->rtm_errno)  {
		(void) fprintf(stderr, "RTM_GET: %s (errno %d)\n",
		    strerror(rtm->rtm_errno), rtm->rtm_errno);
		return;
	}
	cp = ((char *)(rtm + 1));
	if (rtm->rtm_addrs)
		for (i = 1; i; i <<= 1)
			if (i & rtm->rtm_addrs) {
				sa = (struct sockaddr *)cp;
				switch (i) {
				case RTA_DST:
					dst = sa;
					break;
				case RTA_GATEWAY:
					gate = sa;
					break;
				case RTA_NETMASK:
					mask = sa;
					break;
I 55
				case RTA_IFP:
					if (sa->sa_family == AF_LINK &&
					   ((struct sockaddr_dl *)sa)->sdl_nlen)
						ifp = (struct sockaddr_dl *)sa;
					break;
E 55
				}
				ADVANCE(cp, sa);
			}
	if (dst && mask)
		mask->sa_family = dst->sa_family;	/* XXX */
	if (dst)
		(void)printf("destination: %s\n", routename(dst));
	if (mask) {
		int savenflag = nflag;

		nflag = 1;
		(void)printf("       mask: %s\n", routename(mask));
		nflag = savenflag;
	}
	if (gate && rtm->rtm_flags & RTF_GATEWAY)
		(void)printf("    gateway: %s\n", routename(gate));
I 55
	if (ifp)
		(void)printf("  interface: %.*s\n",
		    ifp->sdl_nlen, ifp->sdl_data);
E 55
	(void)printf("      flags: ");
E 54
E 48
	bprintf(stdout, rtm->rtm_flags, routeflags);
D 48
	printf("\nmetric values:\n\n");
E 48
I 48
D 50
	(void) printf("\nmetric values:\n\n");
E 48
#define metric(f, e) printf("\t%s:\t%d\n", "f", rtm->rtm_rmx.e)
	metric(RTV_RPIPE, rmx_recvpipe);
	metric(RTV_SPIPE, rmx_sendpipe);
	metric(RTV_SSTHRESH, rmx_ssthresh);
	metric(RTV_RTT, rmx_rtt);
	metric(RTV_RTTVAR, rmx_rttvar);
	metric(RTV_HOPCOUNT, rmx_hopcount);
	metric(RTV_MTU, rmx_mtu);
	metric(RTV_EXPIRE, rmx_expire);
E 50
I 50
D 54
	(void) printf("\nmetric values:\n  ");
#define metric(f, e)\
    printf("%s: %d%s", __STRING(f), rtm->rtm_rmx.__CONCAT(rmx_,f), e)
	metric(recvpipe, ", ");
	metric(sendpipe, ", ");
	metric(ssthresh, ", ");
	metric(rtt, "\n  ");
	metric(rttvar, ", ");
	metric(hopcount, ", ");
	metric(mtu, ", ");
	metric(expire, "\n");
E 50
#undef metric
	pmsg_common(rtm);
E 54
I 54

#define lock(f)	((rtm->rtm_rmx.rmx_locks & __CONCAT(RTV_,f)) ? 'L' : ' ')
#define msec(u)	(((u) + 500) / 1000)		/* usec to msec */

	(void) printf("\n%s\n", "\
 recvpipe  sendpipe  ssthresh  rtt,msec    rttvar  hopcount      mtu     expire");
	printf("%8d%c ", rtm->rtm_rmx.rmx_recvpipe, lock(RPIPE));
	printf("%8d%c ", rtm->rtm_rmx.rmx_sendpipe, lock(SPIPE));
	printf("%8d%c ", rtm->rtm_rmx.rmx_ssthresh, lock(SSTHRESH));
	printf("%8d%c ", msec(rtm->rtm_rmx.rmx_rtt), lock(RTT));
	printf("%8d%c ", msec(rtm->rtm_rmx.rmx_rttvar), lock(RTTVAR));
	printf("%8d%c ", rtm->rtm_rmx.rmx_hopcount, lock(HOPCOUNT));
	printf("%8d%c ", rtm->rtm_rmx.rmx_mtu, lock(MTU));
	if (rtm->rtm_rmx.rmx_expire)
		rtm->rtm_rmx.rmx_expire -= time(0);
	printf("%8d%c\n", rtm->rtm_rmx.rmx_expire, lock(EXPIRE));
#undef lock
#undef msec
I 55
D 59
#define	RTA_IGN	(RTA_DST|RTA_GATEWAY|RTA_NETMASK|RTA_IFP|RTA_IFA)
E 59
I 59
#define	RTA_IGN	(RTA_DST|RTA_GATEWAY|RTA_NETMASK|RTA_IFP|RTA_IFA|RTA_BRD)
E 59
E 55
	if (verbose)
		pmsg_common(rtm);
D 55
	else if (rtm->rtm_addrs &~ (RTA_DST|RTA_GATEWAY|RTA_NETMASK)) {
E 55
I 55
	else if (rtm->rtm_addrs &~ RTA_IGN) {
E 55
		(void) printf("sockaddrs: ");
D 59
		bprintf(stdout, rtm->rtm_addrs,
		    "\1DST\2GATEWAY\3NETMASK\4GENMASK\5IFP\6IFA\7AUTHOR");
E 59
I 59
		bprintf(stdout, rtm->rtm_addrs, addrnames);
E 59
I 55
		putchar('\n');
E 55
	}
I 55
#undef	RTA_IGN
E 55
E 54
}

I 48
void
E 48
pmsg_common(rtm)
D 48
register struct rt_msghdr *rtm;
E 48
I 48
	register struct rt_msghdr *rtm;
E 48
{
D 59
	char *cp;
	register struct sockaddr *sa;
	int i;

E 59
D 48
	printf("\nlocks: "); bprintf(stdout, rtm->rtm_rmx.rmx_locks, metricnames);
	printf(" inits: "); bprintf(stdout, rtm->rtm_inits, metricnames);
	printf("\nsockaddrs: ");
E 48
I 48
	(void) printf("\nlocks: ");
	bprintf(stdout, rtm->rtm_rmx.rmx_locks, metricnames);
	(void) printf(" inits: ");
	bprintf(stdout, rtm->rtm_inits, metricnames);
I 59
	pmsg_addrs(((char *)(rtm + 1)), rtm->rtm_addrs);
}

void
pmsg_addrs(cp, addrs)
	char	*cp;
	int	addrs;
{
	register struct sockaddr *sa;
	int i;
D 66
	 
E 66
I 66

E 66
	if (addrs == 0)
		return;
E 59
	(void) printf("\nsockaddrs: ");
E 48
D 59
	bprintf(stdout, rtm->rtm_addrs,
	    "\1DST\2GATEWAY\3NETMASK\4GENMASK\5IFP\6IFA\7AUTHOR");
E 59
I 59
	bprintf(stdout, addrs, addrnames);
E 59
D 48
	putchar('\n');
E 48
I 48
	(void) putchar('\n');
E 48
D 59
	cp = ((char *)(rtm + 1));
	if (rtm->rtm_addrs)
D 48
	    for (i = 1; i; i <<= 1)
		if (i & rtm->rtm_addrs) {
			sa = (struct sockaddr *)cp;
			printf(" %s", routename(sa));
D 47
			cp = ROUNDUP(cp + sa->sa_len);
E 47
I 47
			ADVANCE(cp, sa);
E 47
		}
	putchar('\n');
E 46
D 31
	printf("%s\npid: %d, len %d, seq %d, errno %d, flags:",
		msgtypes[rtm->rtm_type], rtm->rtm_pid, rtm->rtm_msglen,
		rtm->rtm_seq, rtm->rtm_errno); 
	bprintf(stdout, rtm->rtm_flags,
		 "\1UP\2GATEWAY\3HOST\5DYNAMIC\6MODIFIED\7DONE\010MASK_PRESENT");
	printf("\nlocks: "); bprintf(stdout, rtm->rtm_locks, metricnames);
	printf(" inits: "); bprintf(stdout, rtm->rtm_locks, metricnames);
	printf("\n%d sockaddrs: ", i);
	cp = ((char *)(rtm + 1));
	while (i-- > 0) {
		sa = (struct sockaddr *)cp;
		printf(" %s", routename(sa));
		cp = ROUNDUP(cp + sa->sa_len);
	}
	putchar('\n');
E 31
	fflush(stdout);
E 48
I 48
		for (i = 1; i; i <<= 1)
			if (i & rtm->rtm_addrs) {
				sa = (struct sockaddr *)cp;
				(void) printf(" %s", routename(sa));
				ADVANCE(cp, sa);
			}
E 59
I 59
	for (i = 1; i; i <<= 1)
		if (i & addrs) {
			sa = (struct sockaddr *)cp;
			(void) printf(" %s", routename(sa));
			ADVANCE(cp, sa);
		}
E 59
	(void) putchar('\n');
	(void) fflush(stdout);
E 48
}

I 48
void
E 48
bprintf(fp, b, s)
D 48
register FILE *fp;
register int b;
register u_char *s;
E 48
I 48
	register FILE *fp;
	register int b;
	register u_char *s;
E 48
{
	register int i;
	int gotsome = 0;

	if (b == 0)
		return;
	while (i = *s++) {
		if (b & (1 << (i-1))) {
D 48
			if (gotsome == 0) i = '<'; else i = ',';
			putc(i, fp);
E 48
I 48
			if (gotsome == 0)
				i = '<';
			else
				i = ',';
			(void) putc(i, fp);
E 48
			gotsome = 1;
			for (; (i = *s) > 32; s++)
D 48
				putc(i, fp);
E 48
I 48
				(void) putc(i, fp);
E 48
		} else
			while (*s > 32)
				s++;
	}
	if (gotsome)
D 48
		putc('>', fp);
E 48
I 48
		(void) putc('>', fp);
E 48
I 36
}
I 48

E 48
int
keyword(cp)
D 48
char *cp;
E 48
I 48
	char *cp;
E 48
{
	register struct keytab *kt = keywords;
I 48

E 48
	while (kt->kt_cp && strcmp(kt->kt_cp, cp))
		kt++;
	return kt->kt_i;
}

I 48
void
E 48
sodump(su, which)
D 46
register union sockunion *su;
E 46
I 46
D 48
register sup su;
E 46
char *which;
E 48
I 48
	register sup su;
	char *which;
E 48
{
	switch (su->sa.sa_family) {
	case AF_LINK:
D 48
		printf("%s: link %s; ", which, link_ntoa(&su->sdl));
E 48
I 48
		(void) printf("%s: link %s; ",
		    which, link_ntoa(&su->sdl));
E 48
		break;
	case AF_ISO:
D 48
		printf("%s: iso %s; ", which, iso_ntoa(&su->siso.siso_addr));
E 48
I 48
		(void) printf("%s: iso %s; ",
		    which, iso_ntoa(&su->siso.siso_addr));
E 48
		break;
	case AF_INET:
D 48
		printf("%s: inet %s; ", which, inet_ntoa(su->sin.sin_addr));
E 48
I 48
		(void) printf("%s: inet %s; ",
		    which, inet_ntoa(su->sin.sin_addr));
E 48
		break;
	case AF_NS:
D 46
		printf("%s: xns %s; ", which, ns_ntoa(&su->sns.sns_addr));
E 46
I 46
D 48
		printf("%s: xns %s; ", which, ns_ntoa(su->sns.sns_addr));
E 48
I 48
		(void) printf("%s: xns %s; ",
		    which, ns_ntoa(su->sns.sns_addr));
E 48
E 46
		break;
	}
D 48
	fflush(stdout);
E 48
I 48
	(void) fflush(stdout);
I 52
}
I 54

E 54
/* States*/
#define VIRGIN	0
#define GOTONE	1
#define GOTTWO	2
/* Inputs */
#define	DIGIT	(4*0)
#define	END	(4*1)
#define DELIM	(4*2)

void
sockaddr(addr, sa)
D 54
register char *addr;
register struct sockaddr *sa;
E 54
I 54
	register char *addr;
	register struct sockaddr *sa;
E 54
{
	register char *cp = (char *)sa;
	int size = sa->sa_len;
	char *cplim = cp + size;
	register int byte = 0, state = VIRGIN, new;

D 69
	bzero(cp, size);
E 69
I 69
	memset(cp, 0, size);
E 69
I 53
	cp++;
E 53
	do {
		if ((*addr >= '0') && (*addr <= '9')) {
			new = *addr - '0';
		} else if ((*addr >= 'a') && (*addr <= 'f')) {
			new = *addr - 'a' + 10;
		} else if ((*addr >= 'A') && (*addr <= 'F')) {
			new = *addr - 'A' + 10;
D 66
		} else if (*addr == 0) 
E 66
I 66
		} else if (*addr == 0)
E 66
			state |= END;
		else
			state |= DELIM;
		addr++;
		switch (state /* | INPUT */) {
		case GOTTWO | DIGIT:
			*cp++ = byte; /*FALLTHROUGH*/
		case VIRGIN | DIGIT:
			state = GOTONE; byte = new; continue;
		case GOTONE | DIGIT:
			state = GOTTWO; byte = new + (byte << 4); continue;
		default: /* | DELIM */
			state = VIRGIN; *cp++ = byte; byte = 0; continue;
		case GOTONE | END:
		case GOTTWO | END:
			*cp++ = byte; /* FALLTHROUGH */
		case VIRGIN | END:
			break;
		}
		break;
D 66
	} while (cp < cplim); 
E 66
I 66
	} while (cp < cplim);
E 66
	sa->sa_len = cp - (char *)sa;
E 52
E 48
D 43
}

/*
 * Copyright (c) 1990 Regents of the University of California.
 * All rights reserved.
 *
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
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)linkaddr.c	5.1 (Berkeley) 4/1/90";
#endif /* LIBC_SCCS and not lint */

#ifndef AF_LINK
#include <sys/param.h>
#include <sys/socket.h>
#include <net/if_dl.h>
#endif
/* States*/
#define NAMING	0
#define GOTONE	1
#define GOTTWO	2
#define RESET	3
/* Inputs */
#define	DIGIT	(4*0)
#define	END	(4*1)
#define DELIM	(4*2)
#define LETTER	(4*3)

link_addr(addr, sdl)
register char *addr;
register struct sockaddr_dl *sdl;
{
	register char *cp = sdl->sdl_data;
	char *cplim = sdl->sdl_len + (char *)sdl;
	register int byte = 0, state = NAMING, new;

	bzero((char *)&sdl->sdl_family, sdl->sdl_len - 1);
	sdl->sdl_family = AF_LINK;
	do {
		state &= ~LETTER;
		if ((*addr >= '0') && (*addr <= '9')) {
			new = *addr - '0';
		} else if ((*addr >= 'a') && (*addr <= 'f')) {
			new = *addr - 'a' + 10;
		} else if ((*addr >= 'A') && (*addr <= 'F')) {
			new = *addr - 'A' + 10;
		} else if (*addr == 0) {
			state |= END;
		} else if (state == NAMING &&
			   (((*addr >= 'A') && (*addr <= 'Z')) ||
			   ((*addr >= 'a') && (*addr <= 'z'))))
			state |= LETTER;
		else
			state |= DELIM;
		addr++;
		switch (state /* | INPUT */) {
		case NAMING | DIGIT:
		case NAMING | LETTER:
			*cp++ = addr[-1]; continue;
		case NAMING | DELIM:
			state = RESET; sdl->sdl_nlen = cp - sdl->sdl_data; continue;
		case GOTTWO | DIGIT:
			*cp++ = byte; /*FALLTHROUGH*/
		case RESET | DIGIT:
			state = GOTONE; byte = new; continue;
		case GOTONE | DIGIT:
			state = GOTTWO; byte = new + (byte << 4); continue;
		default: /* | DELIM */
			state = RESET; *cp++ = byte; byte = 0; continue;
		case GOTONE | END:
		case GOTTWO | END:
			*cp++ = byte; /* FALLTHROUGH */
		case RESET | END:
			break;
		}
		break;
	} while (cp < cplim); 
	sdl->sdl_alen = cp - LLADDR(sdl);
	new = cp - (char *)sdl;
	if (new > sizeof(*sdl))
		sdl->sdl_len = new;
	return;
}
static char hexlist[] = "0123456789abcdef";

char *
link_ntoa(sdl)
register struct sockaddr_dl *sdl;
{
	static char obuf[64];
	register char *out = obuf; 
	register int i;
	register u_char *in = (u_char *)LLADDR(sdl);
	u_char *inlim = in + sdl->sdl_nlen;
	int firsttime = 1;

	if (sdl->sdl_nlen) {
		bcopy(sdl->sdl_data, obuf, sdl->sdl_nlen);
		out += sdl->sdl_nlen;
		*out++ = ':';
	}
	while (in < inlim) {
		if (firsttime) firsttime = 0; else *out++ = '.';
		i = *in++;
		if (i > 0xf) {
			out[1] = hexlist[i & 0xf];
			i >>= 4;
			out[0] = hexlist[i];
			out += 2;
		} else
			*out++ = hexlist[i];
	}
	*out = 0;
	return(obuf);
E 43
E 36
E 30
E 21
I 9
D 14
}

/*
 * Return the possible subnetwork number from an internet address.
 * If the address is of the form of a subnet address (most significant
 * bit of the host part is set), believe the subnet exists.
 * Otherwise, return the network number.
 * SHOULD FIND OUT WHETHER THIS IS A LOCAL NETWORK BEFORE LOOKING
 * INSIDE OF THE HOST PART.  We can only believe this if we have other
 * information (e.g., we can find a name for this number).
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
E 14
E 9
E 6
E 3
E 2
}
E 1
