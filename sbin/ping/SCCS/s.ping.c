h08231
s 00001/00001/00959
d D 8.3 95/04/28 14:19:37 bostic 30 29
c bcmp is obsolete
e
s 00003/00003/00957
d D 8.2 95/04/28 10:55:42 bostic 29 28
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00005/00005/00955
d D 8.1 93/06/05 11:09:27 bostic 28 27
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00957
d D 5.11 93/02/20 14:02:42 bostic 27 26
c fill pattern overwrites end of output[]; bug report net2/sbin/1
c from Rich Stevens
e
s 00017/00011/00941
d D 5.10 92/05/26 15:49:21 bostic 26 25
c display usecs; from Craig Leres
e
s 00002/00002/00950
d D 5.9 91/05/12 14:52:34 bostic 25 24
c error message cleanup, make -q apply to -f; bug report 4.3BSD-reno/usr.bin/17
e
s 00001/00002/00951
d D 5.8 91/03/05 12:03:58 bostic 24 23
c hlen was going to -1 and doing an unsigned comparison
e
s 00004/00003/00949
d D 5.7 91/02/27 17:00:25 bostic 23 21
c ANSI fixes
e
s 00004/00003/00949
d R 5.7 91/02/26 15:43:37 bostic 22 21
c ANSI fixes
e
s 00001/00011/00951
d D 5.6 90/06/01 16:19:29 bostic 21 20
c new copyright notice
e
s 00001/00001/00961
d D 5.5 90/05/15 19:53:50 bostic 20 19
c string.h is ANSI C include file
e
s 00001/00001/00961
d D 5.4 89/08/17 17:48:07 bostic 19 18
c sequence numbers should start at 0
e
s 00006/00007/00956
d D 5.3 89/08/17 15:59:46 karels 18 17
c need to init mask each time for select
e
s 00003/00016/00960
d D 5.2 89/08/16 14:23:24 bostic 17 16
c don't wait for packets on SIGINTR, just die
e
s 00558/00511/00418
d D 5.1 89/08/16 14:13:09 bostic 16 15
c reformat/cleanup mostly, but a few bugs
e
s 00635/00185/00294
d D 4.13 89/08/16 13:52:45 bostic 15 14
c from Cliff Frost
e
s 00002/00001/00477
d D 4.12 89/08/15 21:27:09 karels 14 13
c need init of fromlen once per loop
e
s 00020/00012/00458
d D 4.11 89/05/16 13:32:42 karels 13 12
c start adding burst, don't print negative losses
e
s 00007/00007/00463
d D 4.10 88/10/10 21:41:46 bostic 12 11
c use herror
e
s 00010/00005/00460
d D 4.9 88/06/18 14:34:37 bostic 11 10
c install approved copyright notice
e
s 00019/00001/00446
d D 4.8 88/03/07 21:01:26 bostic 10 9
c add Berkeley specific header
e
s 00005/00002/00442
d D 4.7 87/09/16 17:35:54 bostic 9 8
c fix for big endians; bug report 4.3BSD/etc/30
e
s 00008/00002/00436
d D 4.6 86/10/30 21:32:03 karels 8 6
c print "to" address in case dest. multihomed
e
s 00008/00002/00436
d R 4.6 86/10/30 21:28:16 karels 7 6
c print "to" address in case multihomed
e
s 00017/00004/00421
d D 4.5 86/04/14 09:22:44 karels 6 5
c ICMP raw now passes back IP header
e
s 00003/00002/00422
d D 4.4 85/10/21 17:45:12 karels 5 4
c handle (rare) carry bug
e
s 00055/00088/00369
d D 4.3 85/08/06 19:31:37 karels 4 2
c miscellaneous cleanups; changes from Muus
e
s 00052/00088/00369
d R 4.3 85/08/06 19:29:15 karels 3 2
c cleanups and mods from Muus
e
s 00088/00040/00369
d D 4.2 85/04/29 13:31:25 karels 2 1
c local mods
e
s 00409/00000/00000
d D 4.1 85/04/29 12:20:39 karels 1 0
c from Mike Muus
e
u
U
t
T
I 10
/*
I 16
D 28
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 28
I 28
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 28
 *
 * This code is derived from software contributed to Berkeley by
 * Mike Muuss.
 *
D 21
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
E 21
I 21
 * %sccs.include.redist.c%
E 21
 */

#ifndef lint
D 28
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 28
I 28
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 28
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
E 16
D 13
 * Copyright (c) 1987 Regents of the University of California.
E 13
I 13
D 15
 * Copyright (c) 1987, 1988 Regents of the University of California.
E 13
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
D 11
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 11
I 11
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
E 11
 */

E 10
I 2
#ifndef lint
I 10
char copyright[] =
D 13
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 13
I 13
"%Z% Copyright (c) 1987, 1988 Regents of the University of California.\n\
E 13
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
E 10
static char sccsid[] = "%W% (Berkeley) %G%";
D 10
#endif
E 10
I 10
#endif /* not lint */
E 10

E 2
I 1
/*
E 15
 *			P I N G . C
 *
 * Using the InterNet Control Message Protocol (ICMP) "ECHO" facility,
 * measure round-trip-delays and packet loss across network paths.
 *
 * Author -
 *	Mike Muuss
 *	U. S. Army Ballistic Research Laboratory
 *	December, 1983
I 2
D 16
 * Modified at Uc Berkeley
I 15
 * Record Route and verbose headers - Phil Dykstra, BRL, March 1988.
 * ttl, duplicate detection - Cliff Frost, UCB, April 1989
 * Pad pattern - Cliff Frost (from Tom Ferrin, UCSF), April 1989
 * Wait for dribbles, option decoding, pkt compare - vjs@sgi.com, May 1989
E 16
E 15
E 2
 *
D 2
 * Target System -
 *	4.2 BSD with MIT and BRL fixes to /sys/netinet/ip_icmp.c et.al.
 *
E 2
 * Status -
 *	Public Domain.  Distribution Unlimited.
D 16
 *
E 16
 * Bugs -
D 2
 *	Divide by zero if no packets return.
E 2
 *	More statistics could always be gathered.
 *	This program has to run SUID to ROOT to access the ICMP socket.
 */

D 16
#include <stdio.h>
#include <errno.h>
#include <sys/time.h>
I 15
#include <sys/signal.h>
E 15

E 16
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/file.h>
I 16
#include <sys/time.h>
#include <sys/signal.h>
E 16

#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
I 15
#include <netinet/ip_var.h>
D 16
#include <ctype.h>
E 16
E 15
#include <netdb.h>
I 16
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
D 20
#include <strings.h>
E 20
I 20
#include <string.h>
E 20
E 16

I 2
D 16
#define	MAXWAIT		10	/* max time to wait for response, sec. */
E 2
D 4
char	ttyobuf[4096];
E 4
I 4
D 15
#define	MAXPACKET	4096	/* max packet size */
E 15
I 15
#define	MAXPACKET	(65536-60-8)	/* max packet size */
#define VERBOSE		1	/* verbose flag */
#define QUIET		2	/* quiet flag */
#define FLOOD		4	/* floodping flag */
#define	RROUTE		8	/* record route flag */
#define PING_FILLED     16      /* is buffer filled? */
#define	NUMERIC		32	/* don't do gethostbyaddr() calls */
#define	INTERVAL	64	/* did user specify interval? */
#define	NROUTES		9	/* number of record route slots */
E 15
#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN	64
#endif
E 16
I 16
#define	DEFDATALEN	(64 - 8)	/* default data length */
#define	MAXIPLEN	60
#define	MAXICMPLEN	76
#define	MAXPACKET	(65536 - 60 - 8)/* max packet size */
#define	MAXWAIT		10		/* max seconds to wait for response */
#define	NROUTES		9		/* number of record route slots */
E 16
E 4

I 2
D 15
int	verbose;
E 2
D 4
u_char	packet[1024];
E 4
I 4
u_char	packet[MAXPACKET];
E 4
int	options;
E 15
I 15
D 16
/* MAX_DUP_CHK is the number of bits in received table, ie the */
/*      maximum number of received sequence numbers we can keep track of. */
/*      Change 128 to 8192 for complete accuracy... */
E 16
I 16
#define	A(bit)		rcvd_tbl[(bit)>>3]	/* identify byte in array */
#define	B(bit)		(1 << ((bit) & 0x07))	/* identify bit in byte */
#define	SET(bit)	(A(bit) |= B(bit))
#define	CLR(bit)	(A(bit) &= (~B(bit)))
#define	TST(bit)	(A(bit) & B(bit))
E 16

D 16
#define MAX_DUP_CHK     8 * 128
int     mx_dup_ck = MAX_DUP_CHK;
char    rcvd_tbl[ MAX_DUP_CHK / 8 ];
int     nrepeats = 0;
E 16
I 16
/* various options */
int options;
#define	F_FLOOD		0x001
#define	F_INTERVAL	0x002
#define	F_NUMERIC	0x004
#define	F_PINGFILLED	0x008
#define	F_QUIET		0x010
#define	F_RROUTE	0x020
#define	F_SO_DEBUG	0x040
#define	F_SO_DONTROUTE	0x080
#define	F_VERBOSE	0x100
E 16

D 16
#define A(bit)          rcvd_tbl[ (bit>>3) ]    /* identify byte in array */
#define B(bit)          ( 1 << (bit & 0x07) )   /* identify bit in byte */
#define SET(bit)        A(bit) |= B(bit)
#define CLR(bit)        A(bit) &= (~B(bit))
#define TST(bit)        (A(bit) & B(bit))
E 16
I 16
/*
 * MAX_DUP_CHK is the number of bits in received table, i.e. the maximum
 * number of received sequence numbers we can keep track of.  Change 128
 * to 8192 for complete accuracy...
 */
#define	MAX_DUP_CHK	(8 * 128)
int mx_dup_ck = MAX_DUP_CHK;
char rcvd_tbl[MAX_DUP_CHK / 8];
E 16

D 16

char	*malloc();

u_char	*packet;
int	packlen;
int	i, pingflags = 0, options;
E 15
extern	int errno;

int s;			/* Socket file descriptor */
struct hostent *hp;	/* Pointer to host info */
struct timezone tz;	/* leftover */

D 15
struct sockaddr whereto;/* Who to ping */
int datalen;		/* How much data */
E 15
I 15
struct sockaddr whereto;	/* Who to ping */
int datalen = 64-8;		/* How much data */
E 15

D 2
char usage[] = "Usage:  ping [-d] host [data size]\n";
E 2
I 2
D 4
char usage[] = "Usage:  ping [-drv] host [data size]\n";
E 4
I 4
D 15
char usage[] = "Usage:  ping [-drv] host [data size] [npackets]\n";
E 15
I 15
char usage[] =
"Usage:  ping [-dfnqrvR][-c count][-i wait][-l preload][-p pattern][-s packetsize][-h] host \n";
E 15
E 4
E 2

E 16
I 16
struct sockaddr whereto;	/* who to ping */
int datalen = DEFDATALEN;
int s;				/* socket file descriptor */
u_char outpack[MAXPACKET];
char BSPACE = '\b';		/* characters written for flood */
char DOT = '.';
E 16
char *hostname;
D 4
char hnamebuf[64];
E 4
I 4
D 16
char hnamebuf[MAXHOSTNAMELEN];
E 16
I 16
int ident;			/* process id to identify our packets */
E 16
I 8
D 15
char *inet_ntoa();
E 15
E 8
E 4

D 2
int ntransmitted = 1;		/* sequence # for outbound packets = #sent */
E 2
I 2
D 15
int npackets;
I 13
int burst = 1;
E 15
I 15
D 16
static u_char outpack[MAXPACKET];
E 16
I 16
/* counters */
long npackets;			/* max packets to transmit */
long nreceived;			/* # of packets we got back */
long nrepeats;			/* number of duplicates */
long ntransmitted;		/* sequence # for outbound packets = #sent */
int interval = 1;		/* interval between packets */
E 16

D 16
int npackets=0;
int preload = 0;		/* number of packets to "preload" */
E 15
E 13
int ntransmitted = 0;		/* sequence # for outbound packets = #sent */
E 2
int ident;
I 15
unsigned interval=1;		/* interval between packets */
E 16
I 16
/* timing */
int timing;			/* flag to do timing */
D 26
long tmin = LONG_MAX;		/* minimum round trip time */
long tmax;			/* maximum round trip time */
u_long tsum;			/* sum of all times, for doing average */
E 26
I 26
double tmin = 999999999.0;	/* minimum round trip time */
double tmax = 0.0;		/* maximum round trip time */
double tsum = 0.0;		/* sum of all times, for doing average */
E 26
E 16
E 15

D 16
int nreceived = 0;		/* # of packets we got back */
I 2
int timing = 0;
E 2
int tmin = 999999999;
int tmax = 0;
int tsum = 0;			/* sum of all times, for doing average */
D 2
int finish();
E 2
I 2
int finish(), catcher();
I 15
int bufspace = 48*1024;
int prefinish();
char *inet_ntoa(),*strcpy(),*strncpy(),*sprintf();
char *pr_addr();
E 16
D 23
u_long inet_addr();
D 16
char rspace[3+4*NROUTES+1];	/* record route space */
E 16
I 16
char *inet_ntoa(), *pr_addr();
D 17
int catcher(), finish(), prefinish();
E 17
I 17
int catcher(), finish();
E 23
I 23
char *pr_addr();
void catcher(), finish();
E 23
E 17
E 16
E 15
E 2

D 16
/*
 * 			M A I N
 */
E 16
main(argc, argv)
D 16
char *argv[];
E 16
I 16
	int argc;
	char **argv;
E 16
{
D 16
	struct sockaddr_in from;
D 15
	char **av = argv;
I 8
	char *toaddr = NULL;
E 15
I 15
/*	char **av = argv; */
E 15
E 8
	struct sockaddr_in *to = (struct sockaddr_in *) &whereto;
I 2
D 15
	int on = 1;
E 15
I 15
	int c, k, on = 1, hostind = 0;
E 15
I 4
	struct protoent *proto;
I 15
	static u_char *datap = &outpack[8+sizeof(struct timeval)];
	extern int optind;
E 16
I 16
	extern int errno, optind;
E 16
	extern char *optarg;
I 16
	struct timeval timeout;
	struct hostent *hp;
	struct sockaddr_in *to;
	struct protoent *proto;
	register int i;
	int ch, fdmask, hold, packlen, preload;
	u_char *datap, *packet;
	char *target, hnamebuf[MAXHOSTNAMELEN], *malloc();
#ifdef IP_OPTIONS
	char rspace[3 + 4 * NROUTES + 1];	/* record route space */
#endif
E 16
E 15
E 4
E 2

D 2
	if (argc > 0 && !strcmp(argv[0], "-d"))  {
		options |= SO_DEBUG;
E 2
I 2
D 15
	argc--, av++;
	while (argc > 0 && *av[0] == '-') {
		while (*++av[0]) switch (*av[0]) {
E 15
I 15
D 16
	while ((c = getopt(argc, argv, "c:dfh:i:l:np:qrs:vR")) != EOF)
		switch(c) {
			case 'c':
				npackets = atoi(optarg);
E 16
I 16
	preload = 0;
	datap = &outpack[8 + sizeof(struct timeval)];
	while ((ch = getopt(argc, argv, "Rc:dfh:i:l:np:qrs:v")) != EOF)
		switch(ch) {
		case 'c':
			npackets = atoi(optarg);
			if (npackets <= 0) {
				(void)fprintf(stderr,
				    "ping: bad number of packets to transmit.\n");
				exit(1);
			}
			break;
		case 'd':
			options |= F_SO_DEBUG;
			break;
		case 'f':
			if (getuid()) {
				(void)fprintf(stderr,
D 25
				    "ping: you must be root to use the -f option.\n");
E 25
I 25
				    "ping: %s\n", strerror(EPERM));
E 25
				exit(1);
			}
			options |= F_FLOOD;
			setbuf(stdout, (char *)NULL);
			break;
		case 'i':		/* wait between sending packets */
			interval = atoi(optarg);
			if (interval <= 0) {
				(void)fprintf(stderr,
				    "ping: bad timing interval.\n");
				exit(1);
			}
			options |= F_INTERVAL;
			break;
		case 'l':
			preload = atoi(optarg);
			if (preload < 0) {
				(void)fprintf(stderr,
				    "ping: bad preload value.\n");
				exit(1);
			}
			break;
		case 'n':
			options |= F_NUMERIC;
			break;
		case 'p':		/* fill buffer with user pattern */
			options |= F_PINGFILLED;
			fill((char *)datap, optarg);
E 16
				break;
E 15
D 16
			case 'd':
				options |= SO_DEBUG;
				break;
I 15
			case 'f':
				pingflags |= FLOOD;
				break;
			case 'h':
				hostind = optind-1;
				break;
                        case 'i':       /* wait between sending packets */
				interval = atoi(optarg);
				if (interval == 0) 
					interval = 1;
				pingflags |= INTERVAL;
                                break;
			case 'l':
				preload = atoi(optarg);
				break;
			case 'n':
				pingflags |= NUMERIC;
				break;
                        case 'p':       /* fill buffer with user pattern */
                                pingflags |= PING_FILLED;
				fill((char *)datap, optarg);
                                break;
			case 'q':
				pingflags |= QUIET;
				break;
E 15
			case 'r':
				options |= SO_DONTROUTE;
				break;
I 15
                        case 's':       /* size of packet to send */
				datalen = atoi(optarg);
                                break;
E 15
			case 'v':
D 15
				verbose++;
E 15
I 15
				pingflags |= VERBOSE;
E 15
				break;
I 15
			case 'R':
				pingflags |= RROUTE;
				break;
			default:
				printf(usage);
E 16
I 16
		case 'q':
			options |= F_QUIET;
			break;
		case 'R':
			options |= F_RROUTE;
			break;
		case 'r':
			options |= F_SO_DONTROUTE;
			break;
		case 's':		/* size of packet to send */
			datalen = atoi(optarg);
			if (datalen > MAXPACKET) {
				(void)fprintf(stderr,
				    "ping: packet size too large.\n");
E 16
				exit(1);
I 16
			}
			if (datalen <= 0) {
				(void)fprintf(stderr,
				    "ping: illegal packet size.\n");
				exit(1);
			}
			break;
		case 'v':
			options |= F_VERBOSE;
			break;
		default:
			usage();
E 16
E 15
		}
I 16
	argc -= optind;
	argv += optind;
E 16
E 2
D 15
		argc--, av++;
E 15
I 15

D 16
	if (hostind == 0) {
		if (optind != argc-1) {
			fprintf(stderr, usage);
			exit(1);
		} else hostind = optind;
E 15
	}
E 16
I 16
	if (argc != 1)
		usage();
	target = *argv;
E 16
D 2
	
	if( argc < 2 || argc > 3 )  {
E 2
I 2
D 15
	if( argc < 1)  {
E 2
		printf(usage);
		exit(1);
	}
E 15

D 15
	bzero( (char *)&whereto, sizeof(struct sockaddr) );
E 15
I 15
D 16
	bzero((char *)&whereto, sizeof(struct sockaddr) );
E 16
I 16
D 29
	bzero((char *)&whereto, sizeof(struct sockaddr));
E 29
I 29
	memset(&whereto, 0, sizeof(struct sockaddr));
E 29
	to = (struct sockaddr_in *)&whereto;
E 16
E 15
D 2
	hp = gethostbyname(av[1]);
E 2
I 2
D 4
	hp = gethostbyname(av[0]);
E 2
	if (hp) {
		to->sin_family = hp->h_addrtype;
		bcopy(hp->h_addr, (caddr_t)&to->sin_addr, hp->h_length);
		hostname = hp->h_name;
E 4
I 4
	to->sin_family = AF_INET;
D 15
	to->sin_addr.s_addr = inet_addr(av[0]);
	if (to->sin_addr.s_addr != -1) {
		strcpy(hnamebuf, av[0]);
E 15
I 15
D 16
	to->sin_addr.s_addr = inet_addr(argv[hostind]);
	if(to->sin_addr.s_addr != (unsigned)-1) {
		strcpy(hnamebuf, argv[hostind]);
E 15
		hostname = hnamebuf;
E 4
	} else {
D 4
		to->sin_family = AF_INET;
		to->sin_addr.s_addr = inet_addr(av[1]);
		if (to->sin_addr.s_addr == -1) {
			printf("%s: unknown host %s\n", argv[0], av[1]);
			return;
E 4
I 4
D 15
		hp = gethostbyname(av[0]);
D 12
		if (hp) {
			to->sin_family = hp->h_addrtype;
			bcopy(hp->h_addr, (caddr_t)&to->sin_addr, hp->h_length);
			hostname = hp->h_name;
I 8
			toaddr = inet_ntoa(to->sin_addr.s_addr);
E 8
		} else {
			printf("%s: unknown host %s\n", argv[0], av[0]);
E 12
I 12
		if (!hp) {
			fprintf(stderr, "ping: %s: ", av[0]);
			herror((char *)NULL);
E 15
I 15
		hp = gethostbyname(argv[hostind]);
		if (hp) {
			to->sin_family = hp->h_addrtype;
			bcopy(hp->h_addr, (caddr_t)&to->sin_addr, hp->h_length);
			strncpy( hnamebuf, hp->h_name, sizeof(hnamebuf)-1 );
			hostname = hnamebuf;
		} else {
			printf("%s: unknown host %s\n", argv[0], argv[hostind]);
E 16
I 16
	to->sin_addr.s_addr = inet_addr(target);
	if (to->sin_addr.s_addr != (u_int)-1)
		hostname = target;
	else {
		hp = gethostbyname(target);
		if (!hp) {
			(void)fprintf(stderr,
			    "ping: unknown host %s\n", target);
E 16
E 15
E 12
			exit(1);
E 4
		}
I 16
		to->sin_family = hp->h_addrtype;
D 29
		bcopy(hp->h_addr, (caddr_t)&to->sin_addr, hp->h_length);
E 29
I 29
		memmove(&to->sin_addr, hp->h_addr, hp->h_length);
E 29
		(void)strncpy(hnamebuf, hp->h_name, sizeof(hnamebuf) - 1);
		hostname = hnamebuf;
E 16
I 12
D 15
		to->sin_family = hp->h_addrtype;
		bcopy(hp->h_addr, (caddr_t)&to->sin_addr, hp->h_length);
		hostname = hp->h_name;
		toaddr = inet_ntoa(to->sin_addr.s_addr);
E 15
E 12
D 2
		strcpy(hnamebuf, argv[1]);
E 2
I 2
D 4
		strcpy(hnamebuf, av[1]);
E 2
		hostname = hnamebuf;
E 4
	}

D 2
	if( argc == 3 )
		datalen = atoi( argv[2] );
E 2
I 2
D 15
	if( argc >= 2 )
		datalen = atoi( av[1] );
E 2
	else
		datalen = 64-8;
E 15
I 15
D 16
	if ( (pingflags & FLOOD) && (pingflags & INTERVAL) ) {
		fprintf(stderr, "ping: -f and -i incompatible options\n");
E 16
I 16
	if (options & F_FLOOD && options & F_INTERVAL) {
		(void)fprintf(stderr,
		    "ping: -f and -i incompatible options.\n");
E 16
		exit(1);
	}

E 15
I 4
D 16
	if (datalen > MAXPACKET) {
		fprintf(stderr, "ping: packet size too large\n");
		exit(1);
	}
E 4
I 2
D 15
	if (datalen >= sizeof(struct timeval))
E 15
I 15
	if (datalen >= sizeof(struct timeval))	/* can we time 'em? */
E 16
I 16
	if (datalen >= sizeof(struct timeval))	/* can we time transfer */
E 16
E 15
		timing = 1;
D 15
	if (argc > 2)
		npackets = atoi(av[2]);
E 15
I 15
D 16
	packlen = datalen + 60 + 76;	/* MAXIP + MAXICMP */
	if( (packet = (u_char *)malloc((unsigned)packlen)) == NULL ) {
		fprintf( stderr, "ping: malloc failed\n" );
E 16
I 16
	packlen = datalen + MAXIPLEN + MAXICMPLEN;
	if (!(packet = (u_char *)malloc((u_int)packlen))) {
		(void)fprintf(stderr, "ping: out of memory.\n");
E 16
		exit(1);
	}
I 16
	if (!(options & F_PINGFILLED))
		for (i = 8; i < datalen; ++i)
			*datap++ = i;
E 16
E 15
E 2

I 15
D 16
	if (!(pingflags & PING_FILLED)) {
                for( k=8; k<datalen; k++) *datap++ = k;
        }

E 16
E 15
	ident = getpid() & 0xFFFF;

D 2
	while ((s = socket(AF_INET, SOCK_RAW, 0, 0)) < 0) {
E 2
I 2
D 4
	if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
E 4
I 4
D 16
	if ((proto = getprotobyname("icmp")) == NULL) {
		fprintf(stderr, "icmp: unknown protocol\n");
		exit(10);
E 16
I 16
	if (!(proto = getprotobyname("icmp"))) {
		(void)fprintf(stderr, "ping: unknown protocol icmp.\n");
		exit(1);
E 16
	}
	if ((s = socket(AF_INET, SOCK_RAW, proto->p_proto)) < 0) {
E 4
E 2
		perror("ping: socket");
D 2
		sleep(5);
E 2
I 2
D 16
		exit(5);
E 16
I 16
		exit(1);
E 16
E 2
	}
I 2
D 15
	if (options & SO_DEBUG)
		setsockopt(s, SOL_SOCKET, SO_DEBUG, &on, sizeof(on));
	if (options & SO_DONTROUTE)
		setsockopt(s, SOL_SOCKET, SO_DONTROUTE, &on, sizeof(on));
E 15
I 15
D 16
	if (options & SO_DEBUG) {
		(void)setsockopt(s, SOL_SOCKET, SO_DEBUG, &on, sizeof(on));
	}
	if (options & SO_DONTROUTE) {
		(void)setsockopt(s, SOL_SOCKET, SO_DONTROUTE, &on, sizeof(on));
	}
	/* Record Route option */
	if( pingflags & RROUTE ) {
E 16
I 16
	hold = 1;
	if (options & F_SO_DEBUG)
		(void)setsockopt(s, SOL_SOCKET, SO_DEBUG, (char *)&hold,
		    sizeof(hold));
	if (options & F_SO_DONTROUTE)
		(void)setsockopt(s, SOL_SOCKET, SO_DONTROUTE, (char *)&hold,
		    sizeof(hold));

	/* record route option */
	if (options & F_RROUTE) {
E 16
#ifdef IP_OPTIONS
		rspace[IPOPT_OPTVAL] = IPOPT_RR;
		rspace[IPOPT_OLEN] = sizeof(rspace)-1;
		rspace[IPOPT_OFFSET] = IPOPT_MINOFF;
D 16
		if( setsockopt(s, IPPROTO_IP, IP_OPTIONS, rspace, sizeof(rspace)) < 0 ) {
			perror( "Record route" );
			exit( 42 );
E 16
I 16
		if (setsockopt(s, IPPROTO_IP, IP_OPTIONS, rspace,
		    sizeof(rspace)) < 0) {
			perror("ping: record route");
			exit(1);
E 16
		}
#else
D 16
		fprintf( stderr, "ping: record route not available on this machine.\n" );
		exit( 42 );
#endif IP_OPTIONS
E 16
I 16
		(void)fprintf(stderr,
		  "ping: record route not available in this implementation.\n");
		exit(1);
#endif /* IP_OPTIONS */
E 16
	}
E 15
E 2

D 8
	printf("PING %s: %d data bytes\n", hostname, datalen );
E 8
I 8
D 15
	printf("PING %s", hostname);
	if (toaddr)
		printf(" (%s)", toaddr);
	printf(": %d data bytes\n", datalen);
				
E 15
I 15
D 16
	if(to->sin_family == AF_INET) {
		printf("PING %s (%s): %d data bytes\n", hostname,
		  inet_ntoa(*(struct in_addr *)&to->sin_addr.s_addr), datalen);
	} else {
		printf("PING %s: %d data bytes\n", hostname, datalen );
	}
	/* When pinging the broadcast address, you can get a lot
	 * of answers.  Doing something so evil is useful if you
	 * are trying to stress the ethernet, or just want to
	 * fill the arp cache to get some stuff for /etc/ethers.
E 16
I 16
	/*
	 * When pinging the broadcast address, you can get a lot of answers.
	 * Doing something so evil is useful if you are trying to stress the
	 * ethernet, or just want to fill the arp cache to get some stuff for
	 * /etc/ethers.
E 16
	 */
D 16
	(void)setsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*)&bufspace,
			 sizeof(bufspace));
E 16
I 16
	hold = 48 * 1024;
	(void)setsockopt(s, SOL_SOCKET, SO_RCVBUF, (char *)&hold,
	    sizeof(hold));
E 16
E 15
E 8

D 4
	setbuffer( stdout, ttyobuf, sizeof(ttyobuf) );
E 4
I 4
D 15
	setlinebuf( stdout );
E 4

	signal( SIGINT, finish );
E 15
I 15
D 16
	signal( SIGINT, prefinish );
E 15
I 2
	signal(SIGALRM, catcher);
E 16
I 16
	if (to->sin_family == AF_INET)
		(void)printf("PING %s (%s): %d data bytes\n", hostname,
		    inet_ntoa(*(struct in_addr *)&to->sin_addr.s_addr),
		    datalen);
	else
		(void)printf("PING %s: %d data bytes\n", hostname, datalen);
E 16
E 2

D 15
	catcher();	/* start things going */
E 15
I 15
D 16
	/* fire off them quickies */
	for(i=0; i < preload; i++)
E 16
I 16
D 17
	(void)signal(SIGINT, prefinish);
E 17
I 17
	(void)signal(SIGINT, finish);
E 17
	(void)signal(SIGALRM, catcher);

	while (preload--)		/* fire off them quickies */
E 16
		pinger();
E 15

I 15
D 16
	if(!(pingflags & FLOOD))
		catcher();	/* start things going */

E 15
	for (;;) {
D 15
		int len = sizeof (packet);
D 14
		int fromlen = sizeof (from);
E 14
I 14
		int fromlen;
E 15
I 15
		int fromlen = sizeof (from);
E 15
E 14
		int cc;
I 15
		struct timeval timeout;
		int fdmask = 1 << s;
E 15

E 16
I 16
D 18
	if (options & F_FLOOD) {
E 16
I 14
D 15
		fromlen = sizeof (from);
E 14
D 2
		/* cc = recvfrom(s, buf, len, flags, from, fromlen) */
		if ( (cc=recvfrom(s, packet, len, 0, &from, fromlen)) < 0) {
E 2
I 2
		if ( (cc=recvfrom(s, packet, len, 0, &from, &fromlen)) < 0) {
E 15
I 15
		timeout.tv_sec = 0;
		timeout.tv_usec = 10000;
I 16
		fdmask = 1 << s;
	} else
E 18
I 18
	if ((options & F_FLOOD) == 0)
E 18
		catcher();		/* start things going */
E 16

D 16
		if(pingflags & FLOOD) {
E 16
I 16
	for (;;) {
		struct sockaddr_in from;
		register int cc;
		int fromlen;

		if (options & F_FLOOD) {
E 16
			pinger();
D 16
			if( select(32, (fd_set *)&fdmask, (fd_set *)0, (fd_set *)0, &timeout) == 0)
E 16
I 16
D 18
			if (!select(32, (fd_set *)&fdmask, (fd_set *)NULL,
			    (fd_set *)NULL, &timeout))
E 18
I 18
			timeout.tv_sec = 0;
			timeout.tv_usec = 10000;
			fdmask = 1 << s;
			if (select(s + 1, (fd_set *)&fdmask, (fd_set *)NULL,
			    (fd_set *)NULL, &timeout) < 1)
E 18
E 16
				continue;
		}
D 16
		if ( (cc=recvfrom(s, (char *)packet, packlen, 0, (struct sockaddr *)&from, &fromlen)) < 0) {
E 15
E 2
			if( errno == EINTR )
E 16
I 16
		fromlen = sizeof(from);
		if ((cc = recvfrom(s, (char *)packet, packlen, 0,
		    (struct sockaddr *)&from, &fromlen)) < 0) {
			if (errno == EINTR)
E 16
				continue;
			perror("ping: recvfrom");
			continue;
		}
D 15
		pr_pack( packet, cc, &from );
E 15
I 15
D 16
		pr_pack( (char *)packet, cc, &from );
E 16
I 16
		pr_pack((char *)packet, cc, &from);
E 16
E 15
I 2
		if (npackets && nreceived >= npackets)
D 16
			finish();
E 16
I 16
			break;
E 16
E 2
	}
D 16
	/*NOTREACHED*/
E 16
I 16
	finish();
	/* NOTREACHED */
E 16
}

/*
D 16
 * 			C A T C H E R
 * 
 * This routine causes another PING to be transmitted, and then
E 16
I 16
 * catcher --
 *	This routine causes another PING to be transmitted, and then
E 16
 * schedules another SIGALRM for 1 second from now.
D 26
 * 
E 26
I 26
 *
E 26
D 16
 * Bug -
 * 	Our sense of time will slowly skew (ie, packets will not be launched
 * 	exactly at 1-second intervals).  This does not affect the quality
 *	of the delay and loss statistics.
E 16
I 16
 * bug --
 *	Our sense of time will slowly skew (i.e., packets will not be
 * launched exactly at 1-second intervals).  This does not affect the
 * quality of the delay and loss statistics.
E 16
 */
I 23
void
E 23
catcher()
{
D 2
	signal( SIGALRM, catcher );
E 2
I 2
	int waittime;

E 2
	pinger();
I 15
D 16
	signal(SIGALRM, catcher);
E 15
D 2
	alarm(1);
E 2
I 2
	if (npackets == 0 || ntransmitted < npackets)
D 15
		alarm(1);
E 15
I 15
		alarm(interval);
E 16
I 16
	(void)signal(SIGALRM, catcher);
	if (!npackets || ntransmitted < npackets)
		alarm((u_int)interval);
E 16
E 15
	else {
		if (nreceived) {
			waittime = 2 * tmax / 1000;
D 16
			if (waittime == 0)
E 16
I 16
			if (!waittime)
E 16
				waittime = 1;
		} else
			waittime = MAXWAIT;
D 16
		signal(SIGALRM, finish);
D 15
		alarm(waittime);
E 15
I 15
		alarm((unsigned)waittime);
E 16
I 16
		(void)signal(SIGALRM, finish);
		(void)alarm((u_int)waittime);
E 16
E 15
	}
E 2
}

/*
D 16
 * 			P I N G E R
 * 
 * Compose and transmit an ICMP ECHO REQUEST packet.  The IP packet
E 16
I 16
 * pinger --
D 26
 * 	Compose and transmit an ICMP ECHO REQUEST packet.  The IP packet
E 26
I 26
 *	Compose and transmit an ICMP ECHO REQUEST packet.  The IP packet
E 26
E 16
 * will be added on by the kernel.  The ID field is our UNIX process ID,
 * and the sequence number is an ascending integer.  The first 8 bytes
 * of the data portion are used to hold a UNIX "timeval" struct in VAX
 * byte-order, to compute the round-trip time.
 */
pinger()
{
D 4
	static u_char outpack[1024];
E 4
I 4
D 15
	static u_char outpack[MAXPACKET];
E 15
E 4
D 16
	register struct icmp *icp = (struct icmp *) outpack;
D 13
	int i, cc;
E 13
I 13
D 15
	int i, cc, n;
E 15
I 15
	int i, cc;
E 15
E 13
	register struct timeval *tp = (struct timeval *) &outpack[8];
E 16
I 16
	register struct icmp *icp;
	register int cc;
	int i;
E 16
D 15
	register u_char *datap = &outpack[8+sizeof(struct timeval)];
E 15

I 16
	icp = (struct icmp *)outpack;
E 16
	icp->icmp_type = ICMP_ECHO;
	icp->icmp_code = 0;
	icp->icmp_cksum = 0;
D 16
	icp->icmp_seq = ntransmitted++;
	icp->icmp_id = ident;		/* ID */
E 16
I 16
D 19
	icp->icmp_seq = ++ntransmitted;
E 19
I 19
	icp->icmp_seq = ntransmitted++;
E 19
	icp->icmp_id = ident;			/* ID */
E 16

I 15
D 16
        CLR( icp->icmp_seq % mx_dup_ck );
E 16
I 16
	CLR(icp->icmp_seq % mx_dup_ck);
E 16

E 15
D 16
	cc = datalen+8;			/* skips ICMP portion */

E 16
D 2
	gettimeofday( tp, &tz );
E 2
I 2
	if (timing)
D 16
		gettimeofday( tp, &tz );
E 16
I 16
		(void)gettimeofday((struct timeval *)&outpack[8],
		    (struct timezone *)NULL);
E 16
E 2

D 15
	for( i=8; i<datalen; i++)	/* skip 8 for time */
		*datap++ = i;

E 15
D 16
	/* Compute ICMP checksum here */
D 15
	icp->icmp_cksum = in_cksum( icp, cc );
E 15
I 15
	icp->icmp_cksum = in_cksum( (u_short *)icp, cc );
E 16
I 16
	cc = datalen + 8;			/* skips ICMP portion */
E 16
E 15

D 16
	/* cc = sendto(s, msg, len, flags, to, tolen) */
D 13
	i = sendto( s, outpack, cc, 0, &whereto, sizeof(struct sockaddr) );
E 13
I 13
D 15
	for (n = 0; n < burst; n++) {
		i = sendto(s, outpack, cc, 0, &whereto, sizeof(whereto));
E 15
I 15
	i = sendto( s, (char *)outpack, cc, 0, &whereto, sizeof(struct sockaddr) );
E 16
I 16
	/* compute ICMP checksum here */
	icp->icmp_cksum = in_cksum((u_short *)icp, cc);
E 16
E 15
E 13

D 13
	if( i < 0 || i != cc )  {
		if( i<0 )  perror("sendto");
		printf("ping: wrote %s %d chars, ret=%d\n",
			hostname, cc, i );
		fflush(stdout);
E 13
I 13
D 15
		if( i < 0 || i != cc )  {
			if( i<0 )  perror("sendto");
			printf("ping: wrote %s %d chars, ret=%d\n",
				hostname, cc, i );
			fflush(stdout);
		}
E 15
I 15
D 16
	if( i < 0 || i != cc )  {
		if( i<0 )  perror("sendto");
		printf("ping: wrote %s %d chars, ret=%d\n",
			hostname, cc, i );
		fflush(stdout);
E 16
I 16
	i = sendto(s, (char *)outpack, cc, 0, &whereto,
	    sizeof(struct sockaddr));

	if (i < 0 || i != cc)  {
		if (i < 0)
			perror("ping: sendto");
		(void)printf("ping: wrote %s %d chars, ret=%d\n",
		    hostname, cc, i);
E 16
E 15
E 13
	}
I 15
D 16
	if( pingflags & FLOOD ) {
		putchar('.');
		fflush(stdout);
	}
E 16
I 16
D 25
	if (options & F_FLOOD)
E 25
I 25
	if (!(options & F_QUIET) && options & F_FLOOD)
E 25
		(void)write(STDOUT_FILENO, &DOT, 1);
E 16
E 15
}

/*
D 15
 * 			P R _ T Y P E
 *
 * Convert an ICMP "type" field to a printable string.
 */
char *
pr_type( t )
register int t;
{
	static char *ttab[] = {
		"Echo Reply",
		"ICMP 1",
		"ICMP 2",
		"Dest Unreachable",
		"Source Quence",
		"Redirect",
		"ICMP 6",
		"ICMP 7",
		"Echo",
		"ICMP 9",
		"ICMP 10",
		"Time Exceeded",
		"Parameter Problem",
		"Timestamp",
		"Timestamp Reply",
		"Info Request",
		"Info Reply"
	};

	if( t < 0 || t > 16 )
		return("OUT-OF-RANGE");

	return(ttab[t]);
}

/*
E 15
D 16
 *			P R _ P A C K
 *
 * Print out the packet, if it came from us.  This logic is necessary
E 16
I 16
 * pr_pack --
 *	Print out the packet, if it came from us.  This logic is necessary
E 16
 * because ALL readers of the ICMP socket get a copy of ALL ICMP packets
 * which arrive ('tis only fair).  This permits multiple copies of this
 * program to be run without having intermingled output (or statistics!).
 */
D 6
pr_pack( icp, cc, from )
register struct icmp *icp;
E 6
I 6
D 16
pr_pack( buf, cc, from )
char *buf;
E 6
int cc;
struct sockaddr_in *from;
E 16
I 16
pr_pack(buf, cc, from)
	char *buf;
	int cc;
	struct sockaddr_in *from;
E 16
{
I 6
D 16
	struct ip *ip;
E 16
	register struct icmp *icp;
I 16
	register u_long l;
E 16
E 6
D 15
	register long *lp = (long *) packet;
	register int i;
E 15
I 15
	register int i, j;
	register u_char *cp,*dp;
	static int old_rrlen;
	static char old_rr[MAX_IPOPTLEN];
E 15
D 16
	struct timeval tv;
D 6
	struct timeval *tp = (struct timeval *) &packet[8];
	int triptime;
E 6
I 6
	struct timeval *tp;
D 15
	int hlen, triptime;
E 15
I 15
	int hlen, triptime, dupflag;
E 16
I 16
	struct ip *ip;
	struct timeval tv, *tp;
D 26
	long triptime;
E 26
I 26
	double triptime;
E 26
	int hlen, dupflag;
E 16
E 15
E 6
I 4
D 8
	char *inet_ntoa();
E 8
E 4

D 15
	from->sin_addr.s_addr = ntohl( from->sin_addr.s_addr );
E 15
D 16
	gettimeofday( &tv, &tz );
E 16
I 16
	(void)gettimeofday(&tv, (struct timezone *)NULL);
E 16

I 15
	/* Check the IP header */
E 15
I 6
D 16
	ip = (struct ip *) buf;
E 16
I 16
	ip = (struct ip *)buf;
E 16
	hlen = ip->ip_hl << 2;
D 15
	if (cc < hlen + ICMP_MINLEN) {
		if (verbose)
E 15
I 15
D 16
	if( cc < hlen + ICMP_MINLEN ) {
		if( pingflags & VERBOSE )
E 15
			printf("packet too short (%d bytes) from %s\n", cc,
D 15
				inet_ntoa(ntohl(from->sin_addr.s_addr)));
E 15
I 15
				inet_ntoa(*(struct in_addr *)&from->sin_addr.s_addr));
			fflush(stdout);
E 16
I 16
	if (cc < hlen + ICMP_MINLEN) {
		if (options & F_VERBOSE)
			(void)fprintf(stderr,
			  "ping: packet too short (%d bytes) from %s\n", cc,
			  inet_ntoa(*(struct in_addr *)&from->sin_addr.s_addr));
E 16
E 15
		return;
	}
I 15

	/* Now the ICMP part */
E 15
	cc -= hlen;
	icp = (struct icmp *)(buf + hlen);
E 6
D 15
	if( icp->icmp_type != ICMP_ECHOREPLY )  {
D 2
		printf("%d bytes from x%x: ", cc, from->sin_addr.s_addr);
		printf("icmp_type=%d (%s)\n",
			icp->icmp_type, pr_type(icp->icmp_type) );
		for( i=0; i<12; i++)
E 2
I 2
		if (verbose) {
D 4
			printf("%d bytes from x%x: ", cc, from->sin_addr.s_addr);
E 4
I 4
			printf("%d bytes from %s: ", cc,
				inet_ntoa(ntohl(from->sin_addr.s_addr)));
E 4
			printf("icmp_type=%d (%s)\n",
				icp->icmp_type, pr_type(icp->icmp_type) );
			for( i=0; i<12; i++)
E 2
D 4
			printf("x%2.2x: x%8.8x\n", i*sizeof(long), *lp++ );
E 4
I 4
			    printf("x%2.2x: x%8.8x\n", i*sizeof(long), *lp++ );
E 4
D 2
		printf("icmp_code=%d\n", icp->icmp_code );
E 2
I 2
			printf("icmp_code=%d\n", icp->icmp_code );
E 15
I 15
D 16
	if( icp->icmp_type == ICMP_ECHOREPLY ) {
		if( icp->icmp_id != ident )
E 16
I 16
	if (icp->icmp_type == ICMP_ECHOREPLY) {
		if (icp->icmp_id != ident)
E 16
			return;			/* 'Twas not our ECHO */
D 16

		nreceived++;
E 16
I 16
		++nreceived;
E 16
		if (timing) {
#ifndef icmp_data
			tp = (struct timeval *)&icp->icmp_ip;
#else
D 16
			tp = (struct timeval *)&icp->icmp_data[0];
E 16
I 16
			tp = (struct timeval *)icp->icmp_data;
E 16
#endif
D 16
			tvsub( &tv, tp );
			triptime = tv.tv_sec*1000+(tv.tv_usec/1000);
E 16
I 16
			tvsub(&tv, tp);
D 26
			triptime = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
E 26
I 26
			triptime = ((double)tv.tv_sec) * 1000.0 +
			    ((double)tv.tv_usec) / 1000.0;
E 26
E 16
			tsum += triptime;
D 16
			if( triptime < tmin )
E 16
I 16
			if (triptime < tmin)
E 16
				tmin = triptime;
D 16
			if( triptime > tmax )
E 16
I 16
			if (triptime > tmax)
E 16
				tmax = triptime;
E 15
D 4
			fflush(stdout);
E 4
		}
D 15
		return;
E 15
I 15

D 16
                if ( TST(icp->icmp_seq%mx_dup_ck) ) {
                       	nrepeats++, nreceived--;
			dupflag=1;
                } else {
			SET(icp->icmp_seq%mx_dup_ck);
			dupflag=0;
E 16
I 16
		if (TST(icp->icmp_seq % mx_dup_ck)) {
			++nrepeats;
			--nreceived;
			dupflag = 1;
		} else {
			SET(icp->icmp_seq % mx_dup_ck);
			dupflag = 0;
E 16
		}

D 16
		if( pingflags & QUIET )
E 16
I 16
		if (options & F_QUIET)
E 16
			return;

D 16
		if( pingflags & FLOOD ) {
			putchar('\b');
			fflush(stdout);
		} else {
			printf("%d bytes from %s: icmp_seq=%d", cc,
			  inet_ntoa(*(struct in_addr *)&from->sin_addr.s_addr),
			  icp->icmp_seq );
			if ( dupflag ) printf(" DUP!");
			printf(" ttl=%d", ip->ip_ttl);
E 16
I 16
		if (options & F_FLOOD)
			(void)write(STDOUT_FILENO, &BSPACE, 1);
		else {
			(void)printf("%d bytes from %s: icmp_seq=%u", cc,
			   inet_ntoa(*(struct in_addr *)&from->sin_addr.s_addr),
			   icp->icmp_seq);
			(void)printf(" ttl=%d", ip->ip_ttl);
E 16
			if (timing)
D 16
				printf(" time=%d ms", triptime );
E 16
I 16
D 26
				(void)printf(" time=%ld ms", triptime);
E 26
I 26
				(void)printf(" time=%g ms", triptime);
E 26
			if (dupflag)
				(void)printf(" (DUP!)");
E 16
			/* check the data */
			cp = (u_char*)&icp->icmp_data[8];
D 16
			dp = &outpack[8+sizeof(struct timeval)];
			for (i=8; i<datalen; i++, cp++, dp++) {
E 16
I 16
			dp = &outpack[8 + sizeof(struct timeval)];
			for (i = 8; i < datalen; ++i, ++cp, ++dp) {
E 16
				if (*cp != *dp) {
D 16
		    printf("\nwrong data byte #%d should be 0x%x but was 0x%x",
						i, *dp, *cp);
E 16
I 16
	(void)printf("\nwrong data byte #%d should be 0x%x but was 0x%x",
	    i, *dp, *cp);
E 16
					cp = (u_char*)&icp->icmp_data[0];
D 16
					for (i=8; i<datalen; i++, cp++) {
						if ((i%32) == 8)
							printf("\n\t");
						printf("%x ", *cp);
E 16
I 16
					for (i = 8; i < datalen; ++i, ++cp) {
						if ((i % 32) == 8)
							(void)printf("\n\t");
						(void)printf("%x ", *cp);
E 16
					}
					break;
				}
			}
D 16

E 16
		}
	} else {
		/* We've got something other than an ECHOREPLY */
D 16
		if( !(pingflags & VERBOSE) )
E 16
I 16
		if (!(options & F_VERBOSE))
E 16
			return;
D 16

		printf("%d bytes from %s: ",
		  cc, pr_addr(from->sin_addr.s_addr) );
		pr_icmph( icp );
E 16
I 16
		(void)printf("%d bytes from %s: ", cc,
		    pr_addr(from->sin_addr.s_addr));
		pr_icmph(icp);
E 16
E 15
E 2
	}
D 15
	if( icp->icmp_id != ident )
		return;			/* 'Twas not our ECHO */
E 15

I 6
D 15
	tp = (struct timeval *)&icp->icmp_data[0];
E 6
D 4
	printf("%d bytes from x%x: ", cc, from->sin_addr.s_addr);
E 4
I 4
	printf("%d bytes from %s: ", cc,
		inet_ntoa(ntohl(from->sin_addr.s_addr)));
E 4
	printf("icmp_seq=%d. ", icp->icmp_seq );
D 2
	tvsub( &tv, tp );
	triptime = tv.tv_sec*1000+(tv.tv_usec/1000);
	printf("time=%d. ms\n", triptime );
E 2
I 2
	if (timing) {
		tvsub( &tv, tp );
		triptime = tv.tv_sec*1000+(tv.tv_usec/1000);
		printf("time=%d. ms\n", triptime );
		tsum += triptime;
		if( triptime < tmin )
			tmin = triptime;
		if( triptime > tmax )
			tmax = triptime;
	} else
E 15
I 15
	/* Display any IP options */
	cp = (u_char *)buf + sizeof(struct ip);
D 16
	while (hlen > sizeof(struct ip) & (hlen >= 0)) { /* !ANSI C will  */
		register unsigned long l;		 /* force hlen to */
		switch (*cp) {				 /* unsigned!     */
E 16
I 16

D 24
	/* ANSI C will force hlen to unsigned! */
	for (; hlen > sizeof(struct ip); --hlen, ++cp)
E 24
I 24
	for (; hlen > (int)sizeof(struct ip); --hlen, ++cp)
E 24
		switch (*cp) {
E 16
		case IPOPT_EOL:
			hlen = 0;
			break;
		case IPOPT_LSRR:
D 16
			printf("\nLSRR: ");
E 16
I 16
			(void)printf("\nLSRR: ");
E 16
			hlen -= 2;
			j = *++cp;
			++cp;
D 16
			if (j > IPOPT_MINOFF) for (;;) {
				l = *++cp;
				l = (l<<8) + *++cp;
				l = (l<<8) + *++cp;
				l = (l<<8) + *++cp;
				if (l == 0)
					printf("\t0.0.0.0");
E 16
I 16
			if (j > IPOPT_MINOFF)
				for (;;) {
					l = *++cp;
					l = (l<<8) + *++cp;
					l = (l<<8) + *++cp;
					l = (l<<8) + *++cp;
					if (l == 0)
						(void)printf("\t0.0.0.0");
E 16
				else
D 16
					printf("\t%s", pr_addr(ntohl(l)));
E 16
I 16
					(void)printf("\t%s", pr_addr(ntohl(l)));
E 16
				hlen -= 4;
				j -= 4;
				if (j <= IPOPT_MINOFF)
					break;
D 16
				putchar('\n');
E 16
I 16
				(void)putchar('\n');
E 16
			}
			break;
		case IPOPT_RR:
D 16
			j = *++cp;	/* get length */
			i = *++cp;	/* and pointer */
E 16
I 16
			j = *++cp;		/* get length */
			i = *++cp;		/* and pointer */
E 16
			hlen -= 2;
D 16
			if (i > j) i = j;
E 16
I 16
			if (i > j)
				i = j;
E 16
			i -= IPOPT_MINOFF;
			if (i <= 0)
				continue;
			if (i == old_rrlen
			    && cp == (u_char *)buf + sizeof(struct ip) + 2
D 30
			    && !bcmp((char *)cp, old_rr, i)
E 30
I 30
			    && !memcmp(cp, old_rr, i)
E 30
D 16
			    && !(pingflags & FLOOD)) {
				printf("\t(same route)");
				i = ((i+3)/4)*4;
E 16
I 16
			    && !(options & F_FLOOD)) {
				(void)printf("\t(same route)");
				i = ((i + 3) / 4) * 4;
E 16
				hlen -= i;
				cp += i;
				break;
			}
			old_rrlen = i;
D 29
			bcopy((char *)cp, old_rr, i);
E 29
I 29
			memmove(old_rr, cp, i);
E 29
D 16
			printf("\nRR: ");
E 16
I 16
			(void)printf("\nRR: ");
E 16
			for (;;) {
				l = *++cp;
				l = (l<<8) + *++cp;
				l = (l<<8) + *++cp;
				l = (l<<8) + *++cp;
				if (l == 0)
D 16
					printf("\t0.0.0.0");
E 16
I 16
					(void)printf("\t0.0.0.0");
E 16
				else
D 16
					printf("\t%s", pr_addr(ntohl(l)));
E 16
I 16
					(void)printf("\t%s", pr_addr(ntohl(l)));
E 16
				hlen -= 4;
				i -= 4;
				if (i <= 0)
					break;
D 16
				putchar('\n');
E 16
I 16
				(void)putchar('\n');
E 16
			}
			break;
		case IPOPT_NOP:
D 16
			printf("\nNOP");
E 16
I 16
			(void)printf("\nNOP");
E 16
			break;
		default:
D 16
			printf("\nunknown option %x", *cp);
E 16
I 16
			(void)printf("\nunknown option %x", *cp);
E 16
			break;
		}
D 16
		hlen--;
		cp++;
E 16
I 16
	if (!(options & F_FLOOD)) {
		(void)putchar('\n');
		(void)fflush(stdout);
E 16
	}
D 16
	if (!(pingflags & FLOOD))
E 15
		putchar('\n');
E 2
D 15
	nreceived++;
E 15
I 15
	fflush(stdout);
E 16
E 15
D 2
	tsum += triptime;
	if( triptime < tmin )
		tmin = triptime;
	if( triptime > tmax )
		tmax = triptime;
E 2
D 4
	fflush(stdout);
E 4
}

D 15

E 15
/*
D 16
 *			I N _ C K S U M
 *
D 4
 * Checksum routine for Internet Protocol family headers (VAX Version).
E 4
I 4
 * Checksum routine for Internet Protocol family headers (C Version)
E 4
 *
E 16
I 16
 * in_cksum --
 *	Checksum routine for Internet Protocol family headers (C Version)
E 16
D 4
 * Shamelessly pilfered from /sys/vax/in_cksum.c, with all the MBUF stuff
 * ripped out.
E 4
 */
I 2
D 4
#if vax
E 4
E 2
in_cksum(addr, len)
D 16
u_short *addr;
int len;
E 16
I 16
	u_short *addr;
	int len;
E 16
{
D 4
	register int nleft = len;	/* on vax, (user mode), r11 */
	register int xxx;		/* on vax, (user mode), r10 */
	register u_short *w = addr;	/* on vax, known to be r9 */
	register int sum = 0;		/* on vax, known to be r8 */
E 4
I 4
	register int nleft = len;
	register u_short *w = addr;
D 15
	register u_short answer;
E 15
	register int sum = 0;
I 9
D 15
	u_short odd_byte = 0;
E 15
I 15
	u_short answer = 0;
E 15
E 9
E 4

D 4

E 4
	/*
D 4
	 * Force to long boundary so we do longword aligned
	 * memory operations.  It is too hard to do byte
	 * adjustment, do only word adjustment.
E 4
I 4
D 16
	 *  Our algorithm is simple, using a 32 bit accumulator (sum),
	 *  we add sequential 16 bit words to it, and at the end, fold
	 *  back all the carry bits from the top 16 bits into the lower
	 *  16 bits.
E 16
I 16
	 * Our algorithm is simple, using a 32 bit accumulator (sum), we add
	 * sequential 16 bit words to it, and at the end, fold back all the
	 * carry bits from the top 16 bits into the lower 16 bits.
E 16
E 4
	 */
D 4
	if (((int)w&0x2) && nleft >= 2) {
E 4
I 4
D 16
	while( nleft > 1 )  {
E 16
I 16
	while (nleft > 1)  {
E 16
E 4
		sum += *w++;
		nleft -= 2;
	}
D 4
	/*
	 * Do as much of the checksum as possible 32 bits at at time.
	 * In fact, this loop is unrolled to make overhead from
	 * branches &c small.
	 *
	 * We can do a 16 bit ones complement sum 32 bits at a time
	 * because the 32 bit register is acting as two 16 bit
	 * registers for adding, with carries from the low added
	 * into the high (by normal carry-chaining) and carries
	 * from the high carried into the low on the next word
	 * by use of the adwc instruction.  This lets us run
	 * this loop at almost memory speed.
	 *
	 * Here there is the danger of high order carry out, and
	 * we carefully use adwc.
	 */
	while ((nleft -= 32) >= 0) {
#undef ADD
		asm("clrl r0");		/* clears carry */
#define ADD		asm("adwc (r9)+,r8;");
		ADD; ADD; ADD; ADD; ADD; ADD; ADD; ADD;
		asm("adwc $0,r8");
	}
	nleft += 32;
	while ((nleft -= 8) >= 0) {
		asm("clrl r0");
		ADD; ADD;
		asm("adwc $0,r8");
	}
	nleft += 8;
	/*
	 * Now eliminate the possibility of carry-out's by
	 * folding back to a 16 bit number (adding high and
	 * low parts together.)  Then mop up trailing words
	 * and maybe an odd byte.
	 */
	{ asm("ashl $-16,r8,r0; addw2 r0,r8");
	  asm("adwc $0,r8; movzwl r8,r8"); }
	while ((nleft -= 2) >= 0) {
		asm("movzwl (r9)+,r0; addl2 r0,r8");
	}
	if (nleft == -1) {
E 4
I 4

	/* mop up an odd byte, if necessary */
D 9
	if( nleft == 1 )
E 4
		sum += *(u_char *)w;
E 9
I 9
D 16
	if( nleft == 1 ) {
E 16
I 16
	if (nleft == 1) {
E 16
D 15
		*(u_char *)(&odd_byte) = *(u_char *)w;
		sum += odd_byte;
E 15
I 15
		*(u_char *)(&answer) = *(u_char *)w ;
		sum += answer;
E 15
	}
E 9
D 4
	}
E 4

D 16
	/*
D 4
	 * Add together high and low parts of sum
	 * and carry to get cksum.
	 * Have to be careful to not drop the last
	 * carry here.
E 4
I 4
	 * add back carry outs from top 16 bits to low 16 bits
E 4
	 */
E 16
I 16
	/* add back carry outs from top 16 bits to low 16 bits */
E 16
D 4
	{ asm("ashl $-16,r8,r0; addw2 r0,r8; adwc $0,r8");
	  asm("mcoml r8,r8; movzwl r8,r8"); }
	return (sum);
E 4
I 4
D 5
	sum += (sum >> 16);	/* add hi 16 to low 16 */
	answer = ~sum;		/* truncate to 16 bits */
E 5
I 5
	sum = (sum >> 16) + (sum & 0xffff);	/* add hi 16 to low 16 */
	sum += (sum >> 16);			/* add carry */
	answer = ~sum;				/* truncate to 16 bits */
E 5
D 16
	return (answer);
E 16
I 16
	return(answer);
E 16
E 4
}
I 2
D 4
#endif vax
E 4
E 2

/*
D 16
 * 			T V S U B
 * 
 * Subtract 2 timeval structs:  out = out - in.
 * 
 * Out is assumed to be >= in.
E 16
I 16
 * tvsub --
 *	Subtract 2 timeval structs:  out = out - in.  Out is assumed to
 * be >= in.
E 16
 */
D 16
tvsub( out, in )
register struct timeval *out, *in;
E 16
I 16
tvsub(out, in)
	register struct timeval *out, *in;
E 16
{
D 16
	if( (out->tv_usec -= in->tv_usec) < 0 )   {
		out->tv_sec--;
E 16
I 16
	if ((out->tv_usec -= in->tv_usec) < 0) {
		--out->tv_sec;
E 16
		out->tv_usec += 1000000;
	}
	out->tv_sec -= in->tv_sec;
}

I 15
D 16
/* On the first SIGINT, allow any outstanding packets to dribble in */
E 16
I 16
/*
D 17
 * prefinish --
 *	On the first SIGINT, allow any outstanding packets to dribble in.
 */
E 16
prefinish()
{
D 16
	if (nreceived >= ntransmitted	/* quit now if caught up */
	    || nreceived == 0)		/* or if remote is dead */
E 16
I 16
	/* quit now if caught up or if remote is dead */
	if (!nreceived || nreceived >= ntransmitted)
E 16
		finish();
D 16
	signal(SIGINT, finish);		/* do this only the 1st time */
	npackets = ntransmitted+1;	/* let the normal limit work */
E 16
I 16

	/* do this only the 1st time, let the normal limit work */
	(void)signal(SIGINT, finish);
	npackets = ntransmitted + 1;
E 16
}
E 15
/*
E 17
D 16
 *			F I N I S H
 *
 * Print out statistics, and give up.
 * Heavily buffered STDIO is used here, so that all the statistics
 * will be written with 1 sys-write call.  This is nice when more
 * than one copy of the program is running on a terminal;  it prevents
 * the statistics output from becomming intermingled.
E 16
I 16
 * finish --
 *	Print out statistics, and give up.
E 16
 */
I 23
void
E 23
finish()
{
I 26
	register int i;

E 26
I 17
	(void)signal(SIGINT, SIG_IGN);
E 17
I 15
D 16
	putchar('\n');
	fflush(stdout);
E 15
D 2
	ntransmitted--;		/* we will never hear the last one */

E 2
	printf("\n----%s PING Statistics----\n", hostname );
	printf("%d packets transmitted, ", ntransmitted );
	printf("%d packets received, ", nreceived );
D 2
	printf("%d%% packet loss\n",
E 2
I 2
D 13
	if (ntransmitted)
	    printf("%d%% packet loss",
E 2
		(int) (((ntransmitted-nreceived)*100) / ntransmitted ) );
E 13
I 13
D 15
	if (ntransmitted) {
		if (nreceived <= ntransmitted)
		    printf("%d%% packet loss",
			(int) (((ntransmitted-nreceived)*100) / ntransmitted));
E 15
I 15
        if (nrepeats) printf("+%d duplicates, ", nrepeats );
E 16
I 16
	(void)putchar('\n');
	(void)fflush(stdout);
	(void)printf("--- %s ping statistics ---\n", hostname);
	(void)printf("%ld packets transmitted, ", ntransmitted);
	(void)printf("%ld packets received, ", nreceived);
	if (nrepeats)
		(void)printf("+%ld duplicates, ", nrepeats);
E 16
	if (ntransmitted)
D 16
		if( nreceived > ntransmitted)
			printf("-- somebody's printing up packets!");
E 16
I 16
		if (nreceived > ntransmitted)
			(void)printf("-- somebody's printing up packets!");
E 16
E 15
		else
D 15
		    printf("%.2f responses per request",
			(float) nreceived / (float) ntransmitted);
	}
E 15
I 15
D 16
			printf("%d%% packet loss", 
			  (int) (((ntransmitted-nreceived)*100) /
			  ntransmitted));
E 15
E 13
D 2
	printf("round-trip (ms)  min/avg/max = %d/%d/%d\n",
E 2
I 2
	printf("\n");
E 16
I 16
			(void)printf("%d%% packet loss",
			    (int) (((ntransmitted - nreceived) * 100) /
			    ntransmitted));
	(void)putchar('\n');
E 16
D 26
	if (nreceived && timing)
D 16
	    printf("round-trip (ms)  min/avg/max = %d/%d/%d\n",
E 2
		tmin,
D 15
		tsum / nreceived,
E 15
I 15
		tsum / (nreceived + nrepeats),
E 15
		tmax );
	fflush(stdout);
E 16
I 16
		(void)printf("round-trip min/avg/max = %ld/%lu/%ld ms\n",
		    tmin, tsum / (nreceived + nrepeats), tmax);
E 26
I 26
	if (nreceived && timing) {
		/* Only display average to microseconds */
		i = 1000.0 * tsum / (nreceived + nrepeats);
		(void)printf("round-trip min/avg/max = %g/%g/%g ms\n",
		    tmin, ((double)i) / 1000.0, tmax);
	}
E 26
E 16
	exit(0);
I 15
}

D 16
#if 0
E 16
I 16
#ifdef notdef
E 16
static char *ttab[] = {
	"Echo Reply",		/* ip + seq + udata */
	"Dest Unreachable",	/* net, host, proto, port, frag, sr + IP */
	"Source Quench",	/* IP */
	"Redirect",		/* redirect type, gateway, + IP  */
	"Echo",
	"Time Exceeded",	/* transit, frag reassem + IP */
	"Parameter Problem",	/* pointer + IP */
	"Timestamp",		/* id + seq + three timestamps */
	"Timestamp Reply",	/* " */
	"Info Request",		/* id + sq */
	"Info Reply"		/* " */
};
D 16
#endif	/* 0 */
E 16
I 16
#endif
E 16

/*
D 16
 *  Print a descriptive string about an ICMP header.
E 16
I 16
 * pr_icmph --
 *	Print a descriptive string about an ICMP header.
E 16
 */
D 16
pr_icmph( icp )
struct icmp *icp;
E 16
I 16
pr_icmph(icp)
	struct icmp *icp;
E 16
{
D 16
	switch( icp->icmp_type ) {
E 16
I 16
	switch(icp->icmp_type) {
E 16
	case ICMP_ECHOREPLY:
D 16
		printf("Echo Reply\n");
E 16
I 16
		(void)printf("Echo Reply\n");
E 16
		/* XXX ID + Seq + Data */
		break;
	case ICMP_UNREACH:
D 16
		switch( icp->icmp_code ) {
E 16
I 16
		switch(icp->icmp_code) {
E 16
		case ICMP_UNREACH_NET:
D 16
			printf("Destination Net Unreachable\n");
E 16
I 16
			(void)printf("Destination Net Unreachable\n");
E 16
			break;
		case ICMP_UNREACH_HOST:
D 16
			printf("Destination Host Unreachable\n");
E 16
I 16
			(void)printf("Destination Host Unreachable\n");
E 16
			break;
		case ICMP_UNREACH_PROTOCOL:
D 16
			printf("Destination Protocol Unreachable\n");
E 16
I 16
			(void)printf("Destination Protocol Unreachable\n");
E 16
			break;
		case ICMP_UNREACH_PORT:
D 16
			printf("Destination Port Unreachable\n");
E 16
I 16
			(void)printf("Destination Port Unreachable\n");
E 16
			break;
		case ICMP_UNREACH_NEEDFRAG:
D 16
			printf("frag needed and DF set\n");
E 16
I 16
			(void)printf("frag needed and DF set\n");
E 16
			break;
		case ICMP_UNREACH_SRCFAIL:
D 16
			printf("Source Route Failed\n");
E 16
I 16
			(void)printf("Source Route Failed\n");
E 16
			break;
		default:
D 16
			printf("Dest Unreachable, Bad Code: %d\n", icp->icmp_code );
E 16
I 16
			(void)printf("Dest Unreachable, Bad Code: %d\n",
			    icp->icmp_code);
E 16
			break;
		}
		/* Print returned IP header information */
#ifndef icmp_data
D 16
		pr_retip( &icp->icmp_ip );
E 16
I 16
		pr_retip(&icp->icmp_ip);
E 16
#else
D 16
		pr_retip( (struct ip *)icp->icmp_data );
E 16
I 16
		pr_retip((struct ip *)icp->icmp_data);
E 16
#endif
		break;
	case ICMP_SOURCEQUENCH:
D 16
		printf("Source Quench\n");
E 16
I 16
		(void)printf("Source Quench\n");
E 16
#ifndef icmp_data
D 16
		pr_retip( &icp->icmp_ip );
E 16
I 16
		pr_retip(&icp->icmp_ip);
E 16
#else
D 16
		pr_retip( (struct ip *)icp->icmp_data );
E 16
I 16
		pr_retip((struct ip *)icp->icmp_data);
E 16
#endif
		break;
	case ICMP_REDIRECT:
D 16
		switch( icp->icmp_code ) {
E 16
I 16
		switch(icp->icmp_code) {
E 16
		case ICMP_REDIRECT_NET:
D 16
			printf("Redirect Network");
E 16
I 16
			(void)printf("Redirect Network");
E 16
			break;
		case ICMP_REDIRECT_HOST:
D 16
			printf("Redirect Host");
E 16
I 16
			(void)printf("Redirect Host");
E 16
			break;
		case ICMP_REDIRECT_TOSNET:
D 16
			printf("Redirect Type of Service and Network");
E 16
I 16
			(void)printf("Redirect Type of Service and Network");
E 16
			break;
		case ICMP_REDIRECT_TOSHOST:
D 16
			printf("Redirect Type of Service and Host");
E 16
I 16
			(void)printf("Redirect Type of Service and Host");
E 16
			break;
		default:
D 16
			printf("Redirect, Bad Code: %d", icp->icmp_code );
E 16
I 16
			(void)printf("Redirect, Bad Code: %d", icp->icmp_code);
E 16
			break;
		}
D 16
		printf(" (New addr: 0x%08x)\n", icp->icmp_hun.ih_gwaddr );
E 16
I 16
		(void)printf("(New addr: 0x%08lx)\n", icp->icmp_gwaddr.s_addr);
E 16
#ifndef icmp_data
D 16
		pr_retip( &icp->icmp_ip );
E 16
I 16
		pr_retip(&icp->icmp_ip);
E 16
#else
D 16
		pr_retip( (struct ip *)icp->icmp_data );
E 16
I 16
		pr_retip((struct ip *)icp->icmp_data);
E 16
#endif
		break;
	case ICMP_ECHO:
D 16
		printf("Echo Request\n");
E 16
I 16
		(void)printf("Echo Request\n");
E 16
		/* XXX ID + Seq + Data */
		break;
	case ICMP_TIMXCEED:
D 16
		switch( icp->icmp_code ) {
E 16
I 16
		switch(icp->icmp_code) {
E 16
		case ICMP_TIMXCEED_INTRANS:
D 16
			printf("Time to live exceeded\n");
E 16
I 16
			(void)printf("Time to live exceeded\n");
E 16
			break;
		case ICMP_TIMXCEED_REASS:
D 16
			printf("Frag reassembly time exceeded\n");
E 16
I 16
			(void)printf("Frag reassembly time exceeded\n");
E 16
			break;
		default:
D 16
			printf("Time exceeded, Bad Code: %d\n", icp->icmp_code );
E 16
I 16
			(void)printf("Time exceeded, Bad Code: %d\n",
			    icp->icmp_code);
E 16
			break;
		}
#ifndef icmp_data
D 16
		pr_retip( &icp->icmp_ip );
E 16
I 16
		pr_retip(&icp->icmp_ip);
E 16
#else
D 16
		pr_retip( (struct ip *)icp->icmp_data );
E 16
I 16
		pr_retip((struct ip *)icp->icmp_data);
E 16
#endif
		break;
	case ICMP_PARAMPROB:
D 16
		printf("Parameter problem: pointer = 0x%02x\n",
			icp->icmp_hun.ih_pptr );
E 16
I 16
		(void)printf("Parameter problem: pointer = 0x%02x\n",
		    icp->icmp_hun.ih_pptr);
E 16
#ifndef icmp_data
D 16
		pr_retip( &icp->icmp_ip );
E 16
I 16
		pr_retip(&icp->icmp_ip);
E 16
#else
D 16
		pr_retip( (struct ip *)icp->icmp_data );
E 16
I 16
		pr_retip((struct ip *)icp->icmp_data);
E 16
#endif
		break;
	case ICMP_TSTAMP:
D 16
		printf("Timestamp\n");
E 16
I 16
		(void)printf("Timestamp\n");
E 16
		/* XXX ID + Seq + 3 timestamps */
		break;
	case ICMP_TSTAMPREPLY:
D 16
		printf("Timestamp Reply\n");
E 16
I 16
		(void)printf("Timestamp Reply\n");
E 16
		/* XXX ID + Seq + 3 timestamps */
		break;
	case ICMP_IREQ:
D 16
		printf("Information Request\n");
E 16
I 16
		(void)printf("Information Request\n");
E 16
		/* XXX ID + Seq */
		break;
	case ICMP_IREQREPLY:
D 16
		printf("Information Reply\n");
E 16
I 16
		(void)printf("Information Reply\n");
E 16
		/* XXX ID + Seq */
		break;
#ifdef ICMP_MASKREQ
	case ICMP_MASKREQ:
D 16
		printf("Address Mask Request\n");
E 16
I 16
		(void)printf("Address Mask Request\n");
E 16
		break;
#endif
#ifdef ICMP_MASKREPLY
	case ICMP_MASKREPLY:
D 16
		printf("Address Mask Reply\n");
E 16
I 16
		(void)printf("Address Mask Reply\n");
E 16
		break;
#endif
	default:
D 16
		printf("Bad ICMP type: %d\n", icp->icmp_type);
E 16
I 16
		(void)printf("Bad ICMP type: %d\n", icp->icmp_type);
E 16
	}
}

/*
D 16
 *  Print an IP header with options.
E 16
I 16
 * pr_iph --
 *	Print an IP header with options.
E 16
 */
D 16
pr_iph( ip )
struct ip *ip;
E 16
I 16
pr_iph(ip)
	struct ip *ip;
E 16
{
D 16
	int	hlen;
	unsigned char *cp;
E 16
I 16
	int hlen;
	u_char *cp;
E 16

	hlen = ip->ip_hl << 2;
D 16
	cp = (unsigned char *)ip + 20;	/* point to options */
E 16
I 16
	cp = (u_char *)ip + 20;		/* point to options */
E 16

D 16
	printf("Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src      Dst Data\n");
	printf(" %1x  %1x  %02x %04x %04x",
		ip->ip_v, ip->ip_hl, ip->ip_tos, ip->ip_len, ip->ip_id );
	printf("   %1x %04x", ((ip->ip_off)&0xe000)>>13, (ip->ip_off)&0x1fff );
	printf("  %02x  %02x %04x", ip->ip_ttl, ip->ip_p, ip->ip_sum );
	printf(" %s ", inet_ntoa(*(struct in_addr *)&ip->ip_src.s_addr));
	printf(" %s ", inet_ntoa(*(struct in_addr *)&ip->ip_dst.s_addr));
E 16
I 16
	(void)printf("Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src      Dst Data\n");
	(void)printf(" %1x  %1x  %02x %04x %04x",
	    ip->ip_v, ip->ip_hl, ip->ip_tos, ip->ip_len, ip->ip_id);
	(void)printf("   %1x %04x", ((ip->ip_off) & 0xe000) >> 13,
	    (ip->ip_off) & 0x1fff);
	(void)printf("  %02x  %02x %04x", ip->ip_ttl, ip->ip_p, ip->ip_sum);
	(void)printf(" %s ", inet_ntoa(*(struct in_addr *)&ip->ip_src.s_addr));
	(void)printf(" %s ", inet_ntoa(*(struct in_addr *)&ip->ip_dst.s_addr));
E 16
	/* dump and option bytes */
D 16
	while( hlen-- > 20 ) {
		printf( "%02x", *cp++ );
E 16
I 16
	while (hlen-- > 20) {
		(void)printf("%02x", *cp++);
E 16
	}
D 16
	printf("\n");
E 16
I 16
	(void)putchar('\n');
E 16
}

/*
D 16
 *  Return an ascii host address
 *  as a dotted quad and optionally with a hostname
E 16
I 16
 * pr_addr --
 *	Return an ascii host address as a dotted quad and optionally with
 * a hostname.
E 16
 */
char *
D 16
pr_addr( l )
unsigned long l;
E 16
I 16
pr_addr(l)
	u_long l;
E 16
{
D 16
	struct	hostent	*hp;
	static	char	buf[80];
E 16
I 16
	struct hostent *hp;
	static char buf[80];
E 16

D 16
	if( (pingflags & NUMERIC) || (hp = gethostbyaddr((char *)&l, 4, AF_INET)) == NULL )
		sprintf( buf, "%s", inet_ntoa(*(struct in_addr *)&l) );
E 16
I 16
	if ((options & F_NUMERIC) ||
	    !(hp = gethostbyaddr((char *)&l, 4, AF_INET)))
		(void)sprintf(buf, "%s", inet_ntoa(*(struct in_addr *)&l));
E 16
	else
D 16
		sprintf( buf, "%s (%s)", hp->h_name, inet_ntoa(*(struct in_addr *)&l) );

	return( buf );
E 16
I 16
		(void)sprintf(buf, "%s (%s)", hp->h_name,
		    inet_ntoa(*(struct in_addr *)&l));
	return(buf);
E 16
}

/*
D 16
 *  Dump some info on a returned (via ICMP) IP packet.
E 16
I 16
 * pr_retip --
 *	Dump some info on a returned (via ICMP) IP packet.
E 16
 */
D 16
pr_retip( ip )
struct ip *ip;
E 16
I 16
pr_retip(ip)
	struct ip *ip;
E 16
{
D 16
	int	hlen;
	unsigned char	*cp;
E 16
I 16
	int hlen;
	u_char *cp;
E 16

D 16
	pr_iph( ip );
E 16
I 16
	pr_iph(ip);
E 16
	hlen = ip->ip_hl << 2;
D 16
	cp = (unsigned char *)ip + hlen;
E 16
I 16
	cp = (u_char *)ip + hlen;
E 16

D 16
	if( ip->ip_p == 6 ) {
		printf( "TCP: from port %d, to port %d (decimal)\n",
			(*cp*256+*(cp+1)), (*(cp+2)*256+*(cp+3)) );
	} else if( ip->ip_p == 17 ) {
		printf( "UDP: from port %d, to port %d (decimal)\n",
			(*cp*256+*(cp+1)), (*(cp+2)*256+*(cp+3)) );
	}
E 16
I 16
	if (ip->ip_p == 6)
		(void)printf("TCP: from port %u, to port %u (decimal)\n",
		    (*cp * 256 + *(cp + 1)), (*(cp + 2) * 256 + *(cp + 3)));
	else if (ip->ip_p == 17)
		(void)printf("UDP: from port %u, to port %u (decimal)\n",
			(*cp * 256 + *(cp + 1)), (*(cp + 2) * 256 + *(cp + 3)));
E 16
}

fill(bp, patp)
D 16
char *bp, *patp;
E 16
I 16
	char *bp, *patp;
E 16
{
D 16
        register int ii,jj,kk;
        char *cp;
        int pat[16];
E 16
I 16
	register int ii, jj, kk;
	int pat[16];
	char *cp;
E 16

D 16
        for (cp=patp; *cp; cp++)
                if (!isxdigit(*cp)) {
                        printf("\"-p %s\" ???: ", patp);
                        printf("patterns must be specified as hex digits\n");
                        exit(1);
                }
E 16
I 16
	for (cp = patp; *cp; cp++)
		if (!isxdigit(*cp)) {
			(void)fprintf(stderr,
			    "ping: patterns must be specified as hex digits.\n");
			exit(1);
		}
	ii = sscanf(patp,
	    "%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x",
	    &pat[0], &pat[1], &pat[2], &pat[3], &pat[4], &pat[5], &pat[6],
	    &pat[7], &pat[8], &pat[9], &pat[10], &pat[11], &pat[12],
	    &pat[13], &pat[14], &pat[15]);

	if (ii > 0)
D 27
		for (kk = 0; kk <= MAXPACKET - (8 + ii); kk += ii)
E 27
I 27
		for (kk = 0;
		    kk <= MAXPACKET - (8 + sizeof(struct timeval) + ii);
		    kk += ii)
E 27
			for (jj = 0; jj < ii; ++jj)
				bp[jj + kk] = pat[jj];
	if (!(options & F_QUIET)) {
		(void)printf("PATTERN: 0x");
		for (jj = 0; jj < ii; ++jj)
			(void)printf("%02x", bp[jj] & 0xFF);
		(void)printf("\n");
	}
}
E 16

D 16
        ii = sscanf(patp,
                "%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x",
                &pat[0], &pat[1], &pat[2], &pat[3],
                &pat[4], &pat[5], &pat[6], &pat[7],
                &pat[8], &pat[9], &pat[10], &pat[11],
                &pat[12], &pat[13], &pat[14], &pat[15]);

        if (ii > 0)
                for (kk=0; kk<=MAXPACKET-(8+ii); kk+=ii)
                for (jj=0; jj<ii; jj++)
                        bp[jj+kk] = pat[jj];

        if (!(pingflags & QUIET)) {
                printf("PATTERN: 0x");
                for (jj=0; jj<ii; jj++)
                        printf("%02x", bp[jj]&0xFF);
                printf("\n");
        }

E 16
I 16
usage()
{
	(void)fprintf(stderr,
	    "usage: ping [-Rdfnqrv] [-c count] [-i wait] [-l preload]\n\t[-p pattern] [-s packetsize] host\n");
	exit(1);
E 16
E 15
}
D 2

E 2
E 1
