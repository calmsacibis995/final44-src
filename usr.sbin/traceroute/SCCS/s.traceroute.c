h40829
s 00005/00005/00804
d D 8.1 93/06/06 14:11:28 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00807
d D 5.7 93/04/25 23:27:16 sklower 7 6
c recent changes to kernel require you to fill in more of raw ip header
e
s 00003/00000/00804
d D 5.6 93/04/09 19:24:26 andrew 6 5
c must initialize more IP header fields due to change in IP_HDRINCL semantics.
e
s 00044/00024/00760
d D 5.5 92/05/26 15:47:24 bostic 5 4
c display usecs, ANSI C cleanups; from Craig Leres
e
s 00005/00005/00779
d D 5.4 90/05/15 20:03:13 bostic 4 3
c string.h is ANSI C include file
e
s 00097/00097/00687
d D 5.3 90/04/28 17:01:31 bostic 3 2
c add getopt(3)
e
s 00018/00018/00766
d D 5.2 90/04/28 16:32:20 bostic 2 1
c add Berkeley copyright notice
e
s 00784/00000/00000
d D 5.1 90/04/28 16:30:20 bostic 1 0
c date and time created 90/04/28 16:30:20 by bostic
e
u
U
t
T
I 2
/*-
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
 * Van Jacobson.
 *
 * %sccs.include.redist.c%
 */

E 2
I 1
#ifndef lint
D 2
static char *rcsid =
	"@(#)$Header: traceroute.c,v 1.17 89/02/28 21:01:13 van Exp $ (LBL)";
#endif
E 2
I 2
D 8
char copyright[] =
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
E 8
I 8
static char copyright[] =
"%Z% Copyright (c) 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 8
#endif /* not lint */
E 2

I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
/*
 * traceroute host  - trace the route ip packets follow going to "host".
 *
 * Attempt to trace the route an ip packet would follow to some
 * internet host.  We find out intermediate hops by launching probe
 * packets with a small ttl (time to live) then listening for an
 * icmp "time exceeded" reply from a gateway.  We start our probes
 * with a ttl of one and increase by one until we get an icmp "port
 * unreachable" (which means we got to "host") or hit a max (which
 * defaults to 30 hops & can be changed with the -m flag).  Three
 * probes (change with -q flag) are sent at each ttl setting and a
 * line is printed showing the ttl, address of the gateway and
 * round trip time of each probe.  If the probe answers come from
 * different gateways, the address of each responding system will
 * be printed.  If there is no response within a 5 sec. timeout
 * interval (changed with the -w flag), a "*" is printed for that
 * probe.
 *
 * Probe packets are UDP format.  We don't want the destination
 * host to process them so the destination port is set to an
 * unlikely value (if some clod on the destination is using that
 * value, it can be changed with the -p flag).
 *
 * A sample use might be:
 *
 *     [yak 71]% traceroute nis.nsf.net.
 *     traceroute to nis.nsf.net (35.1.1.48), 30 hops max, 56 byte packet
 *      1  helios.ee.lbl.gov (128.3.112.1)  19 ms  19 ms  0 ms
 *      2  lilac-dmc.Berkeley.EDU (128.32.216.1)  39 ms  39 ms  19 ms
 *      3  lilac-dmc.Berkeley.EDU (128.32.216.1)  39 ms  39 ms  19 ms
 *      4  ccngw-ner-cc.Berkeley.EDU (128.32.136.23)  39 ms  40 ms  39 ms
 *      5  ccn-nerif22.Berkeley.EDU (128.32.168.22)  39 ms  39 ms  39 ms
 *      6  128.32.197.4 (128.32.197.4)  40 ms  59 ms  59 ms
 *      7  131.119.2.5 (131.119.2.5)  59 ms  59 ms  59 ms
 *      8  129.140.70.13 (129.140.70.13)  99 ms  99 ms  80 ms
 *      9  129.140.71.6 (129.140.71.6)  139 ms  239 ms  319 ms
 *     10  129.140.81.7 (129.140.81.7)  220 ms  199 ms  199 ms
 *     11  nic.merit.edu (35.1.1.48)  239 ms  239 ms  239 ms
 *
 * Note that lines 2 & 3 are the same.  This is due to a buggy
 * kernel on the 2nd hop system -- lbl-csam.arpa -- that forwards
 * packets with a zero ttl.
 *
 * A more interesting example is:
 *
 *     [yak 72]% traceroute allspice.lcs.mit.edu.
 *     traceroute to allspice.lcs.mit.edu (18.26.0.115), 30 hops max
 *      1  helios.ee.lbl.gov (128.3.112.1)  0 ms  0 ms  0 ms
 *      2  lilac-dmc.Berkeley.EDU (128.32.216.1)  19 ms  19 ms  19 ms
 *      3  lilac-dmc.Berkeley.EDU (128.32.216.1)  39 ms  19 ms  19 ms
 *      4  ccngw-ner-cc.Berkeley.EDU (128.32.136.23)  19 ms  39 ms  39 ms
 *      5  ccn-nerif22.Berkeley.EDU (128.32.168.22)  20 ms  39 ms  39 ms
 *      6  128.32.197.4 (128.32.197.4)  59 ms  119 ms  39 ms
 *      7  131.119.2.5 (131.119.2.5)  59 ms  59 ms  39 ms
 *      8  129.140.70.13 (129.140.70.13)  80 ms  79 ms  99 ms
 *      9  129.140.71.6 (129.140.71.6)  139 ms  139 ms  159 ms
 *     10  129.140.81.7 (129.140.81.7)  199 ms  180 ms  300 ms
 *     11  129.140.72.17 (129.140.72.17)  300 ms  239 ms  239 ms
 *     12  * * *
 *     13  128.121.54.72 (128.121.54.72)  259 ms  499 ms  279 ms
 *     14  * * *
 *     15  * * *
 *     16  * * *
 *     17  * * *
 *     18  ALLSPICE.LCS.MIT.EDU (18.26.0.115)  339 ms  279 ms  279 ms
 *
 * (I start to see why I'm having so much trouble with mail to
 * MIT.)  Note that the gateways 12, 14, 15, 16 & 17 hops away
 * either don't send ICMP "time exceeded" messages or send them
 * with a ttl too small to reach us.  14 - 17 are running the
 * MIT C Gateway code that doesn't send "time exceeded"s.  God
 * only knows what's going on with 12.
 *
 * The silent gateway 12 in the above may be the result of a bug in
 * the 4.[23]BSD network code (and its derivatives):  4.x (x <= 3)
 * sends an unreachable message using whatever ttl remains in the
 * original datagram.  Since, for gateways, the remaining ttl is
 * zero, the icmp "time exceeded" is guaranteed to not make it back
 * to us.  The behavior of this bug is slightly more interesting
 * when it appears on the destination system:
 *
 *      1  helios.ee.lbl.gov (128.3.112.1)  0 ms  0 ms  0 ms
 *      2  lilac-dmc.Berkeley.EDU (128.32.216.1)  39 ms  19 ms  39 ms
 *      3  lilac-dmc.Berkeley.EDU (128.32.216.1)  19 ms  39 ms  19 ms
 *      4  ccngw-ner-cc.Berkeley.EDU (128.32.136.23)  39 ms  40 ms  19 ms
 *      5  ccn-nerif35.Berkeley.EDU (128.32.168.35)  39 ms  39 ms  39 ms
 *      6  csgw.Berkeley.EDU (128.32.133.254)  39 ms  59 ms  39 ms
 *      7  * * *
 *      8  * * *
 *      9  * * *
 *     10  * * *
 *     11  * * *
 *     12  * * *
 *     13  rip.Berkeley.EDU (128.32.131.22)  59 ms !  39 ms !  39 ms !
 *
 * Notice that there are 12 "gateways" (13 is the final
 * destination) and exactly the last half of them are "missing".
 * What's really happening is that rip (a Sun-3 running Sun OS3.5)
 * is using the ttl from our arriving datagram as the ttl in its
 * icmp reply.  So, the reply will time out on the return path
 * (with no notice sent to anyone since icmp's aren't sent for
 * icmp's) until we probe with a ttl that's at least twice the path
 * length.  I.e., rip is really only 7 hops away.  A reply that
 * returns with a ttl of 1 is a clue this problem exists.
 * Traceroute prints a "!" after the time if the ttl is <= 1.
 * Since vendors ship a lot of obsolete (DEC's Ultrix, Sun 3.x) or
 * non-standard (HPUX) software, expect to see this problem
 * frequently and/or take care picking the target host of your
 * probes.
 *
 * Other possible annotations after the time are !H, !N, !P (got a host,
 * network or protocol unreachable, respectively), !S or !F (source
 * route failed or fragmentation needed -- neither of these should
 * ever occur and the associated gateway is busted if you see one).  If
 * almost all the probes result in some kind of unreachable, traceroute
 * will give up and exit.
 *
 * Notes
 * -----
 * This program must be run by root or be setuid.  (I suggest that
 * you *don't* make it setuid -- casual use could result in a lot
 * of unnecessary traffic on our poor, congested nets.)
 *
 * This program requires a kernel mod that does not appear in any
 * system available from Berkeley:  A raw ip socket using proto
 * IPPROTO_RAW must interpret the data sent as an ip datagram (as
 * opposed to data to be wrapped in a ip datagram).  See the README
 * file that came with the source to this program for a description
 * of the mods I made to /sys/netinet/raw_ip.c.  Your mileage may
 * vary.  But, again, ANY 4.x (x < 4) BSD KERNEL WILL HAVE TO BE
 * MODIFIED TO RUN THIS PROGRAM.
 *
 * The udp port usage may appear bizarre (well, ok, it is bizarre).
 * The problem is that an icmp message only contains 8 bytes of
 * data from the original datagram.  8 bytes is the size of a udp
 * header so, if we want to associate replies with the original
 * datagram, the necessary information must be encoded into the
 * udp header (the ip id could be used but there's no way to
 * interlock with the kernel's assignment of ip id's and, anyway,
 * it would have taken a lot more kernel hacking to allow this
 * code to set the ip id).  So, to allow two or more users to
 * use traceroute simultaneously, we use this task's pid as the
 * source port (the high bit is set to move the port number out
 * of the "likely" range).  To keep track of which probe is being
 * replied to (so times and/or hop counts don't get confused by a
 * reply that was delayed in transit), we increment the destination
 * port number before each probe.
 *
 * Don't use this as a coding example.  I was trying to find a
 * routing problem and this code sort-of popped out after 48 hours
 * without sleep.  I was amazed it ever compiled, much less ran.
 *
 * I stole the idea for this program from Steve Deering.  Since
 * the first release, I've learned that had I attended the right
 * IETF working group meetings, I also could have stolen it from Guy
 * Almes or Matt Mathis.  I don't know (or care) who came up with
 * the idea first.  I envy the originators' perspicacity and I'm
 * glad they didn't keep the idea a secret.
 *
 * Tim Seaver, Ken Adelman and C. Philip Wood provided bug fixes and/or
 * enhancements to the original distribution.
 *
 * I've hacked up a round-trip-route version of this that works by
 * sending a loose-source-routed udp datagram through the destination
 * back to yourself.  Unfortunately, SO many gateways botch source
 * routing, the thing is almost worthless.  Maybe one day...
 *
 *  -- Van Jacobson (van@helios.ee.lbl.gov)
 *     Tue Dec 20 03:50:13 PST 1988
D 2
 *
 * Copyright (c) 1988 Regents of the University of California.
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
E 2
 */

D 4
#include <stdio.h>
#include <errno.h>
#include <strings.h>
#include <sys/time.h>

E 4
#include <sys/param.h>
I 4
#include <sys/time.h>
E 4
#include <sys/socket.h>
#include <sys/file.h>
#include <sys/ioctl.h>

#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
D 5
#include <netdb.h>
E 5
I 4

I 5
#include <arpa/inet.h>

#include <netdb.h>
E 5
#include <stdio.h>
#include <errno.h>
I 5
#include <stdlib.h>
E 5
#include <string.h>
I 5
#include <unistd.h>
E 5
E 4

#define	MAXPACKET	65535	/* max ip packet size */
#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN	64
#endif

#ifndef FD_SET
#define NFDBITS         (8*sizeof(fd_set))
#define FD_SETSIZE      NFDBITS
#define FD_SET(n, p)    ((p)->fds_bits[(n)/NFDBITS] |= (1 << ((n) % NFDBITS)))
#define FD_CLR(n, p)    ((p)->fds_bits[(n)/NFDBITS] &= ~(1 << ((n) % NFDBITS)))
#define FD_ISSET(n, p)  ((p)->fds_bits[(n)/NFDBITS] & (1 << ((n) % NFDBITS)))
#define FD_ZERO(p)      bzero((char *)(p), sizeof(*(p)))
#endif

#define Fprintf (void)fprintf
#define Sprintf (void)sprintf
#define Printf (void)printf
D 5
extern	int errno;
extern  char *malloc();
extern  char *inet_ntoa();
extern  u_long inet_addr();
E 5

/*
 * format of a (udp) probe packet.
 */
struct opacket {
	struct ip ip;
	struct udphdr udp;
	u_char seq;		/* sequence number of this packet */
	u_char ttl;		/* ttl packet left with */
	struct timeval tv;	/* time packet left */
};

u_char	packet[512];		/* last inbound (icmp) packet */
struct opacket	*outpacket;	/* last output (udp) packet */
D 5
char *inetname();
E 5

I 5
int wait_for_reply __P((int, struct sockaddr_in *));
void send_probe __P((int, int));
double deltaT __P((struct timeval *, struct timeval *));
int packet_ok __P((u_char *, int, struct sockaddr_in *, int));
void print __P((u_char *, int, struct sockaddr_in *));
void tvsub __P((struct timeval *, struct timeval *));
char *inetname __P((struct in_addr));
void usage __P(());

E 5
int s;				/* receive (icmp) socket file descriptor */
int sndsock;			/* send (udp) socket file descriptor */
struct timezone tz;		/* leftover */

struct sockaddr whereto;	/* Who to try to reach */
int datalen;			/* How much data */

char *source = 0;
char *hostname;
D 3
char hnamebuf[MAXHOSTNAMELEN];
E 3

int nprobes = 3;
int max_ttl = 30;
u_short ident;
u_short port = 32768+666;	/* start udp dest port # for probe packets */
D 3

E 3
int options;			/* socket options */
int verbose;
int waittime = 5;		/* time to wait for response (in seconds) */
int nflag;			/* print addresses numerically */

I 5
int
E 5
D 3
char usage[] =
 "Usage: traceroute [-dnrv] [-w wait] [-m max_ttl] [-p port#] [-q nqueries] [-t tos] [-s src_addr] host [data size]\n";


E 3
main(argc, argv)
I 5
	int argc;
E 5
	char *argv[];
{
D 3
	struct sockaddr_in from;
	char **av = argv;
	struct sockaddr_in *to = (struct sockaddr_in *) &whereto;
	int on = 1;
	struct protoent *pe;
	int ttl, probe, i;
	int seq = 0;
	int tos = 0;
E 3
I 3
	extern char *optarg;
	extern int optind;
E 3
	struct hostent *hp;
I 3
	struct protoent *pe;
	struct sockaddr_in from, *to;
	int ch, i, on, probe, seq, tos, ttl;
E 3

D 3
	argc--, av++;
	while (argc && *av[0] == '-')  {
		while (*++av[0])
			switch (*av[0]) {
			case 'd':
				options |= SO_DEBUG;
				break;
			case 'm':
				argc--, av++;
				max_ttl = atoi(av[0]);
				if (max_ttl <= 1) {
					Fprintf(stderr, "max ttl must be >1\n");
					exit(1);
				}
				goto nextarg;
			case 'n':
				nflag++;
				break;
			case 'p':
				argc--, av++;
				port = atoi(av[0]);
				if (port < 1) {
					Fprintf(stderr, "port must be >0\n");
					exit(1);
				}
				goto nextarg;
			case 'q':
				argc--, av++;
				nprobes = atoi(av[0]);
				if (nprobes < 1) {
					Fprintf(stderr, "nprobes must be >0\n");
					exit(1);
				}
				goto nextarg;
			case 'r':
				options |= SO_DONTROUTE;
				break;
			case 's':
				/*
				 * set the ip source address of the outbound
				 * probe (e.g., on a multi-homed host).
				 */
				argc--, av++;
				source = av[0];
				goto nextarg;
			case 't':
				argc--, av++;
				tos = atoi(av[0]);
				if (tos < 0 || tos > 255) {
					Fprintf(stderr, "tos must be 0 to 255\n");
					exit(1);
				}
				goto nextarg;
			case 'v':
				verbose++;
				break;
			case 'w':
				argc--, av++;
				waittime = atoi(av[0]);
				if (waittime <= 1) {
					Fprintf(stderr, "wait must be >1 sec\n");
					exit(1);
				}
				goto nextarg;
E 3
I 3
	on = 1;
	seq = tos = 0;
	to = (struct sockaddr_in *)&whereto;
	while ((ch = getopt(argc, argv, "dm:np:q:rs:t:w:v")) != EOF)
		switch(ch) {
		case 'd':
			options |= SO_DEBUG;
			break;
		case 'm':
			max_ttl = atoi(optarg);
			if (max_ttl <= 1) {
				Fprintf(stderr,
				    "traceroute: max ttl must be >1.\n");
				exit(1);
E 3
			}
D 3
	nextarg:
		argc--, av++;
	}
	if (argc < 1)  {
		Printf(usage);
		exit(1);
	}
E 3
I 3
			break;
		case 'n':
			nflag++;
			break;
		case 'p':
			port = atoi(optarg);
			if (port < 1) {
				Fprintf(stderr,
				    "traceroute: port must be >0.\n");
				exit(1);
			}
			break;
		case 'q':
			nprobes = atoi(optarg);
			if (nprobes < 1) {
				Fprintf(stderr,
				    "traceroute: nprobes must be >0.\n");
				exit(1);
			}
			break;
		case 'r':
			options |= SO_DONTROUTE;
			break;
		case 's':
			/*
			 * set the ip source address of the outbound
			 * probe (e.g., on a multi-homed host).
			 */
			source = optarg;
			break;
		case 't':
			tos = atoi(optarg);
			if (tos < 0 || tos > 255) {
				Fprintf(stderr,
				    "traceroute: tos must be 0 to 255.\n");
				exit(1);
			}
			break;
		case 'v':
			verbose++;
			break;
		case 'w':
			waittime = atoi(optarg);
			if (waittime <= 1) {
				Fprintf(stderr,
				    "traceroute: wait must be >1 sec.\n");
				exit(1);
			}
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

D 5
	if (argc < 1) 
E 5
I 5
	if (argc < 1)
E 5
		usage();

E 3
	setlinebuf (stdout);

	(void) bzero((char *)&whereto, sizeof(struct sockaddr));
	to->sin_family = AF_INET;
D 3
	to->sin_addr.s_addr = inet_addr(av[0]);
	if (to->sin_addr.s_addr != -1) {
		(void) strcpy(hnamebuf, av[0]);
		hostname = hnamebuf;
	} else {
		hp = gethostbyname(av[0]);
E 3
I 3
	to->sin_addr.s_addr = inet_addr(*argv);
D 5
	if (to->sin_addr.s_addr != -1) 
E 5
I 5
	if (to->sin_addr.s_addr != -1)
E 5
		hostname = *argv;
	else {
		hp = gethostbyname(*argv);
E 3
		if (hp) {
			to->sin_family = hp->h_addrtype;
			bcopy(hp->h_addr, (caddr_t)&to->sin_addr, hp->h_length);
			hostname = hp->h_name;
		} else {
D 3
			Printf("%s: unknown host %s\n", argv[0], av[0]);
E 3
I 3
			(void)fprintf(stderr,
			    "traceroute: unknown host %s\n", *argv);
E 3
			exit(1);
		}
	}
D 3

	if (argc >= 2)
		datalen = atoi(av[1]);
E 3
I 3
D 5
	if (*++argv) 
E 5
I 5
	if (*++argv)
E 5
		datalen = atoi(*argv);
E 3
	if (datalen < 0 || datalen >= MAXPACKET - sizeof(struct opacket)) {
D 3
		Fprintf(stderr, "traceroute: packet size must be 0 <= s < %ld\n",
			MAXPACKET - sizeof(struct opacket));
E 3
I 3
		Fprintf(stderr,
		    "traceroute: packet size must be 0 <= s < %ld.\n",
		    MAXPACKET - sizeof(struct opacket));
E 3
		exit(1);
	}
	datalen += sizeof(struct opacket);
	outpacket = (struct opacket *)malloc((unsigned)datalen);
	if (! outpacket) {
		perror("traceroute: malloc");
		exit(1);
	}
	(void) bzero((char *)outpacket, datalen);
	outpacket->ip.ip_dst = to->sin_addr;
	outpacket->ip.ip_tos = tos;
I 6
	outpacket->ip.ip_v = IPVERSION;
	outpacket->ip.ip_id = 0;
E 6

	ident = (getpid() & 0xffff) | 0x8000;

	if ((pe = getprotobyname("icmp")) == NULL) {
		Fprintf(stderr, "icmp: unknown protocol\n");
		exit(10);
	}
	if ((s = socket(AF_INET, SOCK_RAW, pe->p_proto)) < 0) {
		perror("traceroute: icmp socket");
		exit(5);
	}
	if (options & SO_DEBUG)
		(void) setsockopt(s, SOL_SOCKET, SO_DEBUG,
				  (char *)&on, sizeof(on));
	if (options & SO_DONTROUTE)
		(void) setsockopt(s, SOL_SOCKET, SO_DONTROUTE,
				  (char *)&on, sizeof(on));

	if ((sndsock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
		perror("traceroute: raw socket");
		exit(5);
	}
#ifdef SO_SNDBUF
	if (setsockopt(sndsock, SOL_SOCKET, SO_SNDBUF, (char *)&datalen,
		       sizeof(datalen)) < 0) {
		perror("traceroute: SO_SNDBUF");
		exit(6);
	}
#endif SO_SNDBUF
#ifdef IP_HDRINCL
	if (setsockopt(sndsock, IPPROTO_IP, IP_HDRINCL, (char *)&on,
		       sizeof(on)) < 0) {
		perror("traceroute: IP_HDRINCL");
		exit(6);
	}
#endif IP_HDRINCL
	if (options & SO_DEBUG)
		(void) setsockopt(sndsock, SOL_SOCKET, SO_DEBUG,
				  (char *)&on, sizeof(on));
	if (options & SO_DONTROUTE)
		(void) setsockopt(sndsock, SOL_SOCKET, SO_DONTROUTE,
				  (char *)&on, sizeof(on));

	if (source) {
		(void) bzero((char *)&from, sizeof(struct sockaddr));
		from.sin_family = AF_INET;
		from.sin_addr.s_addr = inet_addr(source);
		if (from.sin_addr.s_addr == -1) {
			Printf("traceroute: unknown host %s\n", source);
			exit(1);
		}
		outpacket->ip.ip_src = from.sin_addr;
#ifndef IP_HDRINCL
		if (bind(sndsock, (struct sockaddr *)&from, sizeof(from)) < 0) {
			perror ("traceroute: bind:");
			exit (1);
		}
#endif IP_HDRINCL
	}

	Fprintf(stderr, "traceroute to %s (%s)", hostname,
		inet_ntoa(to->sin_addr));
	if (source)
		Fprintf(stderr, " from %s", source);
	Fprintf(stderr, ", %d hops max, %d byte packets\n", max_ttl, datalen);
	(void) fflush(stderr);

	for (ttl = 1; ttl <= max_ttl; ++ttl) {
		u_long lastaddr = 0;
		int got_there = 0;
		int unreachable = 0;

		Printf("%2d ", ttl);
		for (probe = 0; probe < nprobes; ++probe) {
			int cc;
D 5
			struct timeval tv;
E 5
I 5
			struct timeval t1, t2;
			struct timezone tz;
E 5
			struct ip *ip;

D 5
			(void) gettimeofday(&tv, &tz);
E 5
I 5
			(void) gettimeofday(&t1, &tz);
E 5
			send_probe(++seq, ttl);
			while (cc = wait_for_reply(s, &from)) {
I 5
				(void) gettimeofday(&t2, &tz);
E 5
				if ((i = packet_ok(packet, cc, &from, seq))) {
D 5
					int dt = deltaT(&tv);
E 5
					if (from.sin_addr.s_addr != lastaddr) {
						print(packet, cc, &from);
						lastaddr = from.sin_addr.s_addr;
					}
D 5
					Printf("  %d ms", dt);
E 5
I 5
					Printf("  %g ms", deltaT(&t1, &t2));
E 5
					switch(i - 1) {
					case ICMP_UNREACH_PORT:
#ifndef ARCHAIC
						ip = (struct ip *)packet;
						if (ip->ip_ttl <= 1)
							Printf(" !");
#endif ARCHAIC
						++got_there;
						break;
					case ICMP_UNREACH_NET:
						++unreachable;
						Printf(" !N");
						break;
					case ICMP_UNREACH_HOST:
						++unreachable;
						Printf(" !H");
						break;
					case ICMP_UNREACH_PROTOCOL:
						++got_there;
						Printf(" !P");
						break;
					case ICMP_UNREACH_NEEDFRAG:
						++unreachable;
						Printf(" !F");
						break;
					case ICMP_UNREACH_SRCFAIL:
						++unreachable;
						Printf(" !S");
						break;
					}
					break;
				}
			}
			if (cc == 0)
				Printf(" *");
			(void) fflush(stdout);
		}
		putchar('\n');
		if (got_there || unreachable >= nprobes-1)
			exit(0);
	}
}

I 5
int
E 5
wait_for_reply(sock, from)
	int sock;
	struct sockaddr_in *from;
{
	fd_set fds;
	struct timeval wait;
	int cc = 0;
	int fromlen = sizeof (*from);

	FD_ZERO(&fds);
	FD_SET(sock, &fds);
	wait.tv_sec = waittime; wait.tv_usec = 0;

	if (select(sock+1, &fds, (fd_set *)0, (fd_set *)0, &wait) > 0)
		cc=recvfrom(s, (char *)packet, sizeof(packet), 0,
			    (struct sockaddr *)from, &fromlen);

	return(cc);
}


I 5
void
E 5
send_probe(seq, ttl)
I 5
	int seq, ttl;
E 5
{
	struct opacket *op = outpacket;
	struct ip *ip = &op->ip;
	struct udphdr *up = &op->udp;
	int i;

	ip->ip_off = 0;
I 6
	ip->ip_hl = sizeof(*ip) >> 2;
E 6
	ip->ip_p = IPPROTO_UDP;
	ip->ip_len = datalen;
	ip->ip_ttl = ttl;
I 7
	ip->ip_v = IPVERSION;
	ip->ip_id = htons(ident+seq);
E 7

	up->uh_sport = htons(ident);
	up->uh_dport = htons(port+seq);
	up->uh_ulen = htons((u_short)(datalen - sizeof(struct ip)));
	up->uh_sum = 0;

	op->seq = seq;
	op->ttl = ttl;
	(void) gettimeofday(&op->tv, &tz);

	i = sendto(sndsock, (char *)outpacket, datalen, 0, &whereto,
		   sizeof(struct sockaddr));
	if (i < 0 || i != datalen)  {
		if (i<0)
			perror("sendto");
		Printf("traceroute: wrote %s %d chars, ret=%d\n", hostname,
			datalen, i);
		(void) fflush(stdout);
	}
}


D 5
deltaT(tp)
	struct timeval *tp;
E 5
I 5
double
deltaT(t1p, t2p)
	struct timeval *t1p, *t2p;
E 5
{
D 5
	struct timeval tv;
E 5
I 5
	register double dt;
E 5

D 5
	(void) gettimeofday(&tv, &tz);
	tvsub(&tv, tp);
	return (tv.tv_sec*1000 + (tv.tv_usec + 500)/1000);
E 5
I 5
	dt = (double)(t2p->tv_sec - t1p->tv_sec) * 1000.0 +
	     (double)(t2p->tv_usec - t1p->tv_usec) / 1000.0;
	return (dt);
E 5
}


/*
 * Convert an ICMP "type" field to a printable string.
 */
char *
pr_type(t)
	u_char t;
{
	static char *ttab[] = {
	"Echo Reply",	"ICMP 1",	"ICMP 2",	"Dest Unreachable",
	"Source Quench", "Redirect",	"ICMP 6",	"ICMP 7",
	"Echo",		"ICMP 9",	"ICMP 10",	"Time Exceeded",
	"Param Problem", "Timestamp",	"Timestamp Reply", "Info Request",
	"Info Reply"
	};

	if(t > 16)
		return("OUT-OF-RANGE");

	return(ttab[t]);
}


I 5
int
E 5
packet_ok(buf, cc, from, seq)
	u_char *buf;
	int cc;
	struct sockaddr_in *from;
	int seq;
{
	register struct icmp *icp;
	u_char type, code;
	int hlen;
#ifndef ARCHAIC
	struct ip *ip;

	ip = (struct ip *) buf;
	hlen = ip->ip_hl << 2;
	if (cc < hlen + ICMP_MINLEN) {
		if (verbose)
			Printf("packet too short (%d bytes) from %s\n", cc,
				inet_ntoa(from->sin_addr));
		return (0);
	}
	cc -= hlen;
	icp = (struct icmp *)(buf + hlen);
#else
	icp = (struct icmp *)buf;
#endif ARCHAIC
	type = icp->icmp_type; code = icp->icmp_code;
	if ((type == ICMP_TIMXCEED && code == ICMP_TIMXCEED_INTRANS) ||
	    type == ICMP_UNREACH) {
		struct ip *hip;
		struct udphdr *up;

		hip = &icp->icmp_ip;
		hlen = hip->ip_hl << 2;
		up = (struct udphdr *)((u_char *)hip + hlen);
		if (hlen + 12 <= cc && hip->ip_p == IPPROTO_UDP &&
		    up->uh_sport == htons(ident) &&
		    up->uh_dport == htons(port+seq))
			return (type == ICMP_TIMXCEED? -1 : code+1);
	}
#ifndef ARCHAIC
	if (verbose) {
		int i;
		u_long *lp = (u_long *)&icp->icmp_ip;

		Printf("\n%d bytes from %s to %s", cc,
			inet_ntoa(from->sin_addr), inet_ntoa(ip->ip_dst));
		Printf(": icmp type %d (%s) code %d\n", type, pr_type(type),
		       icp->icmp_code);
		for (i = 4; i < cc ; i += sizeof(long))
			Printf("%2d: x%8.8lx\n", i, *lp++);
	}
#endif ARCHAIC
	return(0);
}


I 5
void
E 5
print(buf, cc, from)
	u_char *buf;
	int cc;
	struct sockaddr_in *from;
{
	struct ip *ip;
	int hlen;

	ip = (struct ip *) buf;
	hlen = ip->ip_hl << 2;
	cc -= hlen;

	if (nflag)
		Printf(" %s", inet_ntoa(from->sin_addr));
	else
		Printf(" %s (%s)", inetname(from->sin_addr),
		       inet_ntoa(from->sin_addr));

	if (verbose)
		Printf (" %d bytes to %s", cc, inet_ntoa (ip->ip_dst));
}


#ifdef notyet
/*
 * Checksum routine for Internet Protocol family headers (C Version)
 */
I 5
u_short
E 5
in_cksum(addr, len)
D 5
u_short *addr;
int len;
E 5
I 5
	u_short *addr;
	int len;
E 5
{
	register int nleft = len;
	register u_short *w = addr;
	register u_short answer;
	register int sum = 0;

	/*
	 *  Our algorithm is simple, using a 32 bit accumulator (sum),
	 *  we add sequential 16 bit words to it, and at the end, fold
	 *  back all the carry bits from the top 16 bits into the lower
	 *  16 bits.
	 */
	while (nleft > 1)  {
		sum += *w++;
		nleft -= 2;
	}

	/* mop up an odd byte, if necessary */
	if (nleft == 1)
		sum += *(u_char *)w;

	/*
	 * add back carry outs from top 16 bits to low 16 bits
	 */
	sum = (sum >> 16) + (sum & 0xffff);	/* add hi 16 to low 16 */
	sum += (sum >> 16);			/* add carry */
	answer = ~sum;				/* truncate to 16 bits */
	return (answer);
}
#endif notyet

/*
 * Subtract 2 timeval structs:  out = out - in.
 * Out is assumed to be >= in.
 */
I 5
void
E 5
tvsub(out, in)
D 5
register struct timeval *out, *in;
E 5
I 5
	register struct timeval *out, *in;
E 5
{
	if ((out->tv_usec -= in->tv_usec) < 0)   {
		out->tv_sec--;
		out->tv_usec += 1000000;
	}
	out->tv_sec -= in->tv_sec;
}


/*
 * Construct an Internet address representation.
D 5
 * If the nflag has been supplied, give 
E 5
I 5
 * If the nflag has been supplied, give
E 5
 * numeric value, otherwise try for symbolic name.
 */
char *
inetname(in)
	struct in_addr in;
{
	register char *cp;
	static char line[50];
	struct hostent *hp;
	static char domain[MAXHOSTNAMELEN + 1];
	static int first = 1;

	if (first && !nflag) {
		first = 0;
		if (gethostname(domain, MAXHOSTNAMELEN) == 0 &&
		    (cp = index(domain, '.')))
			(void) strcpy(domain, cp + 1);
		else
			domain[0] = 0;
	}
	cp = 0;
	if (!nflag && in.s_addr != INADDR_ANY) {
		hp = gethostbyaddr((char *)&in, sizeof (in), AF_INET);
		if (hp) {
			if ((cp = index(hp->h_name, '.')) &&
			    !strcmp(cp + 1, domain))
				*cp = 0;
			cp = hp->h_name;
		}
	}
	if (cp)
		(void) strcpy(line, cp);
	else {
		in.s_addr = ntohl(in.s_addr);
#define C(x)	((x) & 0xff)
		Sprintf(line, "%lu.%lu.%lu.%lu", C(in.s_addr >> 24),
			C(in.s_addr >> 16), C(in.s_addr >> 8), C(in.s_addr));
	}
	return (line);
I 3
}

I 5
void
E 5
usage()
{
D 5
	(void)fprintf(stderr, 
E 5
I 5
	(void)fprintf(stderr,
E 5
"usage: traceroute [-dnrv] [-m max_ttl] [-p port#] [-q nqueries]\n\t\
[-s src_addr] [-t tos] [-w wait] host [data size]\n");
	exit(1);
E 3
}
E 1
