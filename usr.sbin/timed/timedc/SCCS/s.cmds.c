h36964
s 00001/00001/00499
d D 8.2 95/03/26 14:21:38 vjs 13 12
c fix check for EINTR
e
s 00002/00002/00498
d D 8.1 93/06/06 14:09:16 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00273/00143/00227
d D 5.1 93/05/11 11:49:32 bostic 11 10
c new version from Vernon Schryver (vjs@sgi.com); see ../timed/CHANGES for details
e
s 00005/00005/00365
d D 2.8 91/03/02 17:37:30 bostic 10 9
c ANSI
e
s 00001/00011/00369
d D 2.7 90/06/01 19:03:04 bostic 9 8
c new copyright notice
e
s 00008/00005/00372
d D 2.6 88/10/11 12:20:18 bostic 8 7
c use herror
e
s 00010/00005/00367
d D 2.5 88/06/18 14:08:09 bostic 7 6
c install approved copyright notice
e
s 00009/00003/00363
d D 2.4 87/12/23 14:30:03 bostic 6 5
c append Berkeley header; NASA wants a copy
e
s 00001/00001/00365
d D 2.3 86/11/18 20:13:45 bostic 5 4
c bug report 4.3BSD/etc/15
e
s 00003/00003/00363
d D 2.2 86/04/21 15:42:14 bloom 4 3
c delete arg from measure(), change timeout for measure()
e
s 00011/00009/00355
d D 2.1 85/12/10 13:06:32 bloom 3 2
c Multi network support
e
s 00001/00022/00363
d D 1.2 85/09/18 10:15:27 bloom 2 1
c wrong way to determine if timed is running, use MAXHOSTNAMELEN constant, 
c move other constants to header file
e
s 00385/00000/00000
d D 1.1 85/06/27 13:18:18 gusella 1 0
c date and time created 85/06/27 13:18:18 by gusella
e
u
U
t
T
I 1
D 11
/*
 * Copyright (c) 1983 Regents of the University of California.
E 11
I 11
/*-
D 12
 * Copyright (c) 1985, 1993 The Regents of the University of California.
E 11
D 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
D 9
 * Redistribution and use in source and binary forms are permitted
D 7
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 7
I 7
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 7
E 6
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6

I 11
#ifdef sgi
#ident "$Revision: 1.10 $"
#endif

E 11
#include "timedc.h"
I 11
#include <sys/file.h>

E 11
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
I 11

#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

E 11
#define TSPTYPES
#include <protocols/timed.h>
D 11
#include <sys/file.h>
E 11

D 2
#define OFF	0
#define ON	1

E 2
D 11
int id;
E 11
I 11
#ifdef sgi
#include <bstring.h>
#include <sys/clock.h>
#else
#define	SECHR	(60*60)
#define	SECDAY	(24*SECHR)
#endif /* sgi */

# define DATE_PROTO "udp"
# define DATE_PORT "time"


E 11
int sock;
int sock_raw;
D 2
char hostname[32];
E 2
I 2
D 11
char hostname[MAXHOSTNAMELEN];
E 2
struct hostent *hp, *gethostbyname();
E 11
I 11
char myname[MAXHOSTNAMELEN];
struct hostent *hp;
E 11
struct sockaddr_in server;
I 11
struct sockaddr_in dayaddr;
E 11
extern int measure_delta;
D 11
int bytenetorder(), bytehostorder();
char *strcpy();
E 11

I 11
void bytenetorder(struct tsp *);
void bytehostorder(struct tsp *);


#define BU ((unsigned long)2208988800)	/* seconds before UNIX epoch */


/* compute the difference between our date and another machine
 */
static int				/* difference in days from our time */
daydiff(hostname)
	char *hostname;
{
	int i;
	int trials;
	struct timeval tout, now;
	fd_set ready;
	struct sockaddr from;
	int fromlen;
	unsigned long sec;


	/* wait 2 seconds between 10 tries */
	tout.tv_sec = 2;
	tout.tv_usec = 0;
	for (trials = 0; trials < 10; trials++) {
		/* ask for the time */
		sec = 0;
		if (sendto(sock, &sec, sizeof(sec), 0,
			   (struct sockaddr*)&dayaddr, sizeof(dayaddr)) < 0) {
			perror("sendto(sock)");
			return 0;
		}

		for (;;) {
			FD_ZERO(&ready);
			FD_SET(sock, &ready);
			i = select(sock+1, &ready, (fd_set *)0,
				   (fd_set *)0, &tout);
			if (i < 0) {
D 13
				if (errno = EINTR)
E 13
I 13
				if (errno == EINTR)
E 13
					continue;
				perror("select(date read)");
				return 0;
			}
			if (0 == i)
				break;

			fromlen = sizeof(from);
			if (recvfrom(sock,&sec,sizeof(sec),0,
				     &from,&fromlen) < 0) {
				perror("recvfrom(date read)");
				return 0;
			}

			sec = ntohl(sec);
			if (sec < BU) {
				fprintf(stderr,
					"%s says it is before 1970: %lu",
					hostname, sec);
				return 0;
			}
			sec -= BU;

			(void)gettimeofday(&now, (struct timezone*)0);
			return (sec - now.tv_sec);
		}
	}

	/* if we get here, we tried too many times */
	fprintf(stderr,"%s will not tell us the date\n", hostname);
	return 0;
}


E 11
/*
D 11
 * Clockdiff computes the difference between the time of the machine on 
E 11
I 11
 * Clockdiff computes the difference between the time of the machine on
E 11
 * which it is called and the time of the machines given as argument.
 * The time differences measured by clockdiff are obtained using a sequence
 * of ICMP TSTAMP messages which are returned to the sender by the IP module
 * in the remote machine.
D 11
 * In order to compare clocks of machines in different time zones, the time 
 * is transmitted (as a 32-bit value) in milliseconds since midnight UT. 
E 11
I 11
 * In order to compare clocks of machines in different time zones, the time
 * is transmitted (as a 32-bit value) in milliseconds since midnight UT.
E 11
 * If a hosts uses a different time format, it should set the high order
 * bit of the 32-bit quantity it transmits.
 * However, VMS apparently transmits the time in milliseconds since midnight
D 11
 * local time (rather than GMT) without setting the high order bit. 
 * Furthermore, it does not understand daylight-saving time.  This makes 
E 11
I 11
 * local time (rather than GMT) without setting the high order bit.
 * Furthermore, it does not understand daylight-saving time.  This makes
E 11
 * clockdiff behaving inconsistently with hosts running VMS.
 *
D 11
 * In order to reduce the sensitivity to the variance of message transmission 
 * time, clockdiff sends a sequence of messages.  Yet, measures between 
 * two `distant' hosts can be affected by a small error. The error can, however,
 * be reduced by increasing the number of messages sent in each measurement.
E 11
I 11
 * In order to reduce the sensitivity to the variance of message transmission
 * time, clockdiff sends a sequence of messages.  Yet, measures between
 * two `distant' hosts can be affected by a small error. The error can,
 * however, be reduced by increasing the number of messages sent in each
 * measurement.
E 11
 */
D 11

E 11
I 11
void
E 11
clockdiff(argc, argv)
D 11
int argc;
char *argv[];
E 11
I 11
	int argc;
	char *argv[];
E 11
{
	int measure_status;
D 11
	struct timeval ack;
	int measure();
E 11
I 11
	extern int measure(u_long, u_long, char *, struct sockaddr_in*, int);
	register int avg_cnt;
	register long avg;
	struct servent *sp;
E 11

D 11
	if(argc < 2)  {
E 11
I 11
	if (argc < 2)  {
E 11
		printf("Usage: clockdiff host ... \n");
		return;
	}

D 11
	id = getpid();
	(void)gethostname(hostname,sizeof(hostname));
E 11
I 11
	(void)gethostname(myname,sizeof(myname));
E 11

I 11
	/* get the address for the date ready */
	sp = getservbyname(DATE_PORT, DATE_PROTO);
	if (!sp) {
		(void)fprintf(stderr, "%s/%s is an unknown service\n",
			      DATE_PORT, DATE_PROTO);
		dayaddr.sin_port = 0;
	} else {
		dayaddr.sin_port = sp->s_port;
	}

E 11
	while (argc > 1) {
		argc--; argv++;
		hp = gethostbyname(*argv);
		if (hp == NULL) {
D 8
			printf("%s: unknown host\n", *argv);
E 8
I 8
D 11
			fprintf(stderr, "timed: %s: ", *argv);
			herror((char *)NULL);
E 11
I 11
			fprintf(stderr, "timedc: %s: ", *argv);
			herror(0);
E 11
E 8
			continue;
		}
I 11

E 11
		server.sin_family = hp->h_addrtype;
D 11
		bcopy(hp->h_addr, &(server.sin_addr.s_addr), hp->h_length); 
D 4
		ack.tv_sec = 1;
		ack.tv_usec = 500000;
D 3
		if ((measure_status = measure(&ack, OFF)) < 0) {
E 3
I 3
		if ((measure_status = measure(&ack, &server, OFF)) < 0) {
E 4
I 4
		ack.tv_sec = 10;
		ack.tv_usec = 0;
		if ((measure_status = measure(&ack, &server)) < 0) {
E 4
E 3
			perror("measure");
			return;
E 11
I 11
		bcopy(hp->h_addr, &server.sin_addr.s_addr, hp->h_length);
		for (avg_cnt = 0, avg = 0; avg_cnt < 16; avg_cnt++) {
			measure_status = measure(10000,100, *argv, &server, 1);
			if (measure_status != GOOD)
				break;
			avg += measure_delta;
E 11
		}
D 11
		switch (measure_status) {
E 11
I 11
		if (measure_status == GOOD)
			measure_delta = avg/avg_cnt;
E 11

I 11
		switch (measure_status) {
E 11
		case HOSTDOWN:
			printf("%s is down\n", hp->h_name);
			continue;
D 11
			break;
E 11
		case NONSTDTIME:
D 11
			printf("%s time transmitted in a non-standard format\n",						 hp->h_name);
E 11
I 11
			printf("%s transmitts a non-standard time format\n",
			       hp->h_name);
E 11
			continue;
D 11
			break;
E 11
		case UNREACHABLE:
			printf("%s is unreachable\n", hp->h_name);
			continue;
D 11
			break;
		default:
			break;
E 11
		}

D 11
		if (measure_delta > 0)
			printf("time on %s is %d ms. ahead of time on %s\n", 
						hp->h_name, measure_delta,
						hostname);
		else
			if (measure_delta == 0)
		      		printf("%s and %s have the same time\n", 
						hp->h_name, hostname);
			else
		      	     printf("time on %s is %d ms. behind time on %s\n",
					hp->h_name, -measure_delta, hostname);
E 11
I 11
		/*
		 * Try to get the date only after using ICMP timestamps to
		 * get the time.  This is because the date protocol
		 * is optional.
		 */
		if (dayaddr.sin_port != 0) {
			dayaddr.sin_family = hp->h_addrtype;
			bcopy(hp->h_addr, &dayaddr.sin_addr.s_addr,
			      hp->h_length);
			avg = daydiff(*argv);
			if (avg > SECDAY) {
				printf("time on %s is %ld days ahead %s\n",
				       hp->h_name, avg/SECDAY, myname);
				continue;
			} else if (avg < -SECDAY) {
				printf("time on %s is %ld days behind %s\n",
				       hp->h_name, -avg/SECDAY, myname);
				continue;
			}
		}

		if (measure_delta > 0) {
			printf("time on %s is %d ms. ahead of time on %s\n",
			       hp->h_name, measure_delta, myname);
		} else if (measure_delta == 0) {
			printf("%s and %s have the same time\n",
			       hp->h_name, myname);
		} else {
			printf("time on %s is %d ms. behind time on %s\n",
			       hp->h_name, -measure_delta, myname);
		}
E 11
	}
	return;
}
I 11


E 11
/*
 * finds location of master timedaemon
 */
D 11

msite(argc)
int argc;
E 11
I 11
void
msite(argc, argv)
	int argc;
	char *argv[];
E 11
{
D 11
	int length;
E 11
D 3
	int cc, ready, found;
E 3
I 3
	int cc;
	fd_set ready;
E 3
	struct sockaddr_in dest;
I 11
	int i, length;
	struct sockaddr from;
E 11
	struct timeval tout;
D 11
	struct sockaddr_in from;
E 11
	struct tsp msg;
	struct servent *srvp;
I 11
	char *tgtname;
E 11

D 11
	if (argc != 1) {
		printf("Usage: msite\n");
E 11
I 11
	if (argc < 1) {
		printf("Usage: msite [hostname]\n");
E 11
		return;
	}

D 2
	(void) open("/etc/timed", O_WRONLY, 01700);
	if (errno != ETXTBSY) {
		printf("No timed on this machine\n");
		return;
	}

E 2
	srvp = getservbyname("timed", "udp");
	if (srvp == 0) {
		fprintf(stderr, "udp/timed: unknown service\n");
		return;
D 8
	}	
E 8
I 8
	}
E 8
	dest.sin_port = srvp->s_port;
	dest.sin_family = AF_INET;

D 8
	(void)gethostname(hostname,sizeof(hostname));
E 8
I 8
D 11
	(void)gethostname(hostname, sizeof(hostname));
E 8
	hp = gethostbyname(hostname);
	if (hp == NULL) {
D 8
		perror("gethostbyname");
E 8
I 8
		fprintf(stderr, "timed: %s: ", hostname);
		herror((char *)NULL);
E 8
		return;
	}
	bcopy(hp->h_addr, &dest.sin_addr.s_addr, hp->h_length);
E 11
I 11
	(void)gethostname(myname, sizeof(myname));
	i = 1;
	do {
		tgtname = (i >= argc) ? myname : argv[i];
		hp = gethostbyname(tgtname);
		if (hp == 0) {
			fprintf(stderr, "timedc: %s: ", tgtname);
			herror(0);
			continue;
		}
		bcopy(hp->h_addr, &dest.sin_addr.s_addr, hp->h_length);
E 11

D 11
	(void)strcpy(msg.tsp_name, hostname);
	msg.tsp_type = TSP_MSITE;
	msg.tsp_vers = TSPVERSION;
	bytenetorder(&msg);
	length = sizeof(struct sockaddr_in);
	if (sendto(sock, (char *)&msg, sizeof(struct tsp), 0, 
D 10
						&dest, length) < 0) {
E 10
I 10
	    (struct sockaddr *)&dest, length) < 0) {
E 10
		perror("sendto");
		return;
	}
E 11
I 11
		(void)strcpy(msg.tsp_name, myname);
		msg.tsp_type = TSP_MSITE;
		msg.tsp_vers = TSPVERSION;
		bytenetorder(&msg);
		if (sendto(sock, &msg, sizeof(struct tsp), 0,
			   (struct sockaddr*)&dest,
			   sizeof(struct sockaddr)) < 0) {
			perror("sendto");
			continue;
		}
E 11

D 11
	tout.tv_sec = 15;
	tout.tv_usec = 0;
D 3
	ready = 1<<sock;
	found = select(20, &ready, (int *)0, (int *)0, &tout);
	if (found) {
E 3
I 3
	FD_ZERO(&ready);
	FD_SET(sock, &ready);
	if (select(FD_SETSIZE, &ready, (fd_set *)0, (fd_set *)0, &tout)) {
E 3
		length = sizeof(struct sockaddr_in);
		cc = recvfrom(sock, (char *)&msg, sizeof(struct tsp), 0, 
D 10
							&from, &length);
E 10
I 10
		    (struct sockaddr *)&from, &length);
E 10
		if (cc < 0) {
			perror("recvfrom");
			return;
E 11
I 11
		tout.tv_sec = 15;
		tout.tv_usec = 0;
		FD_ZERO(&ready);
		FD_SET(sock, &ready);
		if (select(FD_SETSIZE, &ready, (fd_set *)0, (fd_set *)0,
			   &tout)) {
			length = sizeof(struct sockaddr);
			cc = recvfrom(sock, &msg, sizeof(struct tsp), 0,
				      &from, &length);
			if (cc < 0) {
				perror("recvfrom");
				continue;
			}
			bytehostorder(&msg);
			if (msg.tsp_type == TSP_ACK) {
				printf("master timedaemon at %s is %s\n",
				       tgtname, msg.tsp_name);
			} else {
				printf("received wrong ack: %s\n",
				       tsptype[msg.tsp_type]);
			}
		} else {
			printf("communication error with %s\n", tgtname);
E 11
		}
D 11
		bytehostorder(&msg);
		if (msg.tsp_type == TSP_ACK)
			printf("master timedaemon runs on %s\n", msg.tsp_name);
		else
			printf("received wrong ack: %s\n", 
						tsptype[msg.tsp_type]);
	} else
		printf("communication error\n");
E 11
I 11
	} while (++i < argc);
E 11
}

/*
 * quits timedc
 */
D 11

E 11
I 11
void
E 11
quit()
{
	exit(0);
}

D 11
#define MAXH	4	/* max no. of hosts where election can occur */
E 11

/*
 * Causes the election timer to expire on the selected hosts
 * It sends just one udp message per machine, relying on
 * reliability of communication channel.
 */
D 11

E 11
I 11
void
E 11
testing(argc, argv)
D 11
int argc;
char *argv[];
E 11
I 11
	int argc;
	char *argv[];
E 11
{
D 11
	int length;
	int nhosts;
E 11
	struct servent *srvp;
D 11
	struct sockaddr_in sin[MAXH];
E 11
I 11
	struct sockaddr_in sin;
E 11
	struct tsp msg;

D 11
	if(argc < 2)  {
		printf("Usage: testing host ...\n");
E 11
I 11
	if (argc < 2)  {
		printf("Usage: election host1 [host2 ...]\n");
E 11
		return;
	}

D 2
	(void) open("/etc/timed", O_WRONLY, 01700);
	if (errno != ETXTBSY) {
		printf("No timed on this machine\n");
		return;
	}

E 2
	srvp = getservbyname("timed", "udp");
	if (srvp == 0) {
		fprintf(stderr, "udp/timed: unknown service\n");
		return;
D 11
	}	
E 11
I 11
	}
E 11

D 11
	nhosts = 0;
E 11
	while (argc > 1) {
		argc--; argv++;
		hp = gethostbyname(*argv);
		if (hp == NULL) {
D 5
			printf("%s: unknown host %s\n", *argv);
E 5
I 5
D 8
			printf("%s: unknown host\n", *argv);
E 8
I 8
D 11
			fprintf(stderr, "timed: %s: ", *argv);
			herror((char *)NULL);
E 11
I 11
			fprintf(stderr, "timedc: %s: ", *argv);
			herror(0);
E 11
E 8
E 5
			argc--; argv++;
			continue;
		}
D 11
		sin[nhosts].sin_port = srvp->s_port;
		sin[nhosts].sin_family = hp->h_addrtype;
		bcopy(hp->h_addr, &(sin[nhosts].sin_addr.s_addr), hp->h_length);
		if (++nhosts == MAXH)
			break;
	}
E 11
I 11
		sin.sin_port = srvp->s_port;
		sin.sin_family = hp->h_addrtype;
		bcopy(hp->h_addr, &sin.sin_addr.s_addr, hp->h_length);
E 11

D 11
	msg.tsp_type = TSP_TEST;
	msg.tsp_vers = TSPVERSION;
	(void)gethostname(hostname, sizeof(hostname));
	(void)strcpy(msg.tsp_name, hostname);
	bytenetorder(&msg);	/* it is not really necessary here */
	while (nhosts-- > 0) {
		length = sizeof(struct sockaddr_in);
		if (sendto(sock, (char *)&msg, sizeof(struct tsp), 0, 
D 10
						&sin[nhosts], length) < 0) {
E 10
I 10
		    (struct sockaddr *)&sin[nhosts], length) < 0) {
E 11
I 11
		msg.tsp_type = TSP_TEST;
		msg.tsp_vers = TSPVERSION;
		(void)gethostname(myname, sizeof(myname));
		(void)strncpy(msg.tsp_name, myname, sizeof(msg.tsp_name));
		bytenetorder(&msg);
		if (sendto(sock, &msg, sizeof(struct tsp), 0,
			   (struct sockaddr*)&sin,
			   sizeof(struct sockaddr)) < 0) {
E 11
E 10
			perror("sendto");
D 11
			return;
E 11
		}
	}
}

I 11

E 11
/*
 * Enables or disables tracing on local timedaemon
 */
D 11

E 11
I 11
void
E 11
tracing(argc, argv)
D 11
int argc;
char *argv[];
E 11
I 11
	int argc;
	char *argv[];
E 11
{
	int onflag;
	int length;
D 3
	int cc, ready, found;
E 3
I 3
	int cc;
	fd_set ready;
E 3
	struct sockaddr_in dest;
I 11
	struct sockaddr from;
E 11
	struct timeval tout;
D 11
	struct sockaddr_in from;
E 11
	struct tsp msg;
	struct servent *srvp;

	if (argc != 2) {
		printf("Usage: tracing { on | off }\n");
D 2
		return;
	}

	(void) open("/etc/timed", O_WRONLY, 01700);
	if (errno != ETXTBSY) {
		printf("No timed on this machine\n");
E 2
		return;
	}

	srvp = getservbyname("timed", "udp");
	if (srvp == 0) {
		fprintf(stderr, "udp/timed: unknown service\n");
		return;
D 11
	}	
E 11
I 11
	}
E 11
	dest.sin_port = srvp->s_port;
	dest.sin_family = AF_INET;

D 11
	(void)gethostname(hostname,sizeof(hostname));
	hp = gethostbyname(hostname);
E 11
I 11
	(void)gethostname(myname,sizeof(myname));
	hp = gethostbyname(myname);
E 11
	bcopy(hp->h_addr, &dest.sin_addr.s_addr, hp->h_length);

	if (strcmp(argv[1], "on") == 0) {
		msg.tsp_type = TSP_TRACEON;
		onflag = ON;
	} else {
		msg.tsp_type = TSP_TRACEOFF;
		onflag = OFF;
	}

D 11
	(void)strcpy(msg.tsp_name, hostname);
E 11
I 11
	(void)strcpy(msg.tsp_name, myname);
E 11
	msg.tsp_vers = TSPVERSION;
	bytenetorder(&msg);
D 11
	length = sizeof(struct sockaddr_in);
	if (sendto(sock, (char *)&msg, sizeof(struct tsp), 0, 
D 10
						&dest, length) < 0) {
E 10
I 10
	    (struct sockaddr *)&dest, length) < 0) {
E 11
I 11
	if (sendto(sock, &msg, sizeof(struct tsp), 0,
		   (struct sockaddr*)&dest, sizeof(struct sockaddr)) < 0) {
E 11
E 10
		perror("sendto");
		return;
	}

	tout.tv_sec = 5;
	tout.tv_usec = 0;
D 3
	ready = 1<<sock;
	found = select(20, &ready, (int *)0, (int *)0, &tout);
	if (found) {
E 3
I 3
	FD_ZERO(&ready);
	FD_SET(sock, &ready);
	if (select(FD_SETSIZE, &ready, (fd_set *)0, (fd_set *)0, &tout)) {
E 3
D 11
		length = sizeof(struct sockaddr_in);
		cc = recvfrom(sock, (char *)&msg, sizeof(struct tsp), 0, 
D 10
							&from, &length);
E 10
I 10
		    (struct sockaddr *)&from, &length);
E 11
I 11
		length = sizeof(struct sockaddr);
		cc = recvfrom(sock, &msg, sizeof(struct tsp), 0,
			      &from, &length);
E 11
E 10
		if (cc < 0) {
			perror("recvfrom");
			return;
		}
		bytehostorder(&msg);
		if (msg.tsp_type == TSP_ACK)
			if (onflag)
				printf("timed tracing enabled\n");
			else
				printf("timed tracing disabled\n");
		else
D 11
			printf("wrong ack received: %s\n", 
E 11
I 11
			printf("wrong ack received: %s\n",
E 11
						tsptype[msg.tsp_type]);
	} else
		printf("communication error\n");
}

I 11
int
E 11
priv_resources()
{
	int port;
	struct sockaddr_in sin;

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		perror("opening socket");
		return(-1);
	}

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	for (port = IPPORT_RESERVED - 1; port > IPPORT_RESERVED / 2; port--) {
		sin.sin_port = htons((u_short)port);
D 11
		if (bind(sock, (struct sockaddr *)&sin, sizeof (sin)) >= 0)
E 11
I 11
		if (bind(sock, (struct sockaddr*)&sin, sizeof (sin)) >= 0)
E 11
			break;
		if (errno != EADDRINUSE && errno != EADDRNOTAVAIL) {
			perror("bind");
			(void) close(sock);
			return(-1);
		}
	}
	if (port == IPPORT_RESERVED / 2) {
		fprintf(stderr, "all reserved ports in use\n");
		(void) close(sock);
		return(-1);
	}

D 11
	sock_raw = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP); 
E 11
I 11
	sock_raw = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
E 11
	if (sock_raw < 0)  {
		perror("opening raw socket");
D 11
		(void) close(sock_raw);
E 11
I 11
		(void) close(sock);
E 11
		return(-1);
	}
	return(1);
}
E 1
