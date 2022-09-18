h57843
s 00002/00002/00104
d D 8.1 93/06/06 14:09:01 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00070/00047/00036
d D 5.1 93/05/11 11:51:07 bostic 12 11
c new version from Vernon Schryver (vjs@sgi.com); see ../timed/CHANGES for details
e
s 00002/00002/00081
d D 2.8 91/03/02 17:36:00 bostic 11 10
c ANSI
e
s 00001/00011/00082
d D 2.7 90/06/01 19:02:45 bostic 10 9
c new copyright notice
e
s 00010/00005/00083
d D 2.6 88/06/18 14:08:00 bostic 9 8
c install approved copyright notice
e
s 00009/00003/00079
d D 2.5 87/12/23 14:29:55 bostic 8 7
c append Berkeley header; NASA wants a copy
e
s 00002/00003/00080
d D 2.4 86/05/27 15:57:56 karels 7 6
c toss MAXSEQ
e
s 00001/00001/00082
d D 2.3 86/04/11 18:16:02 bloom 6 5
c major work on multiple network code (Kirk Smith, ks@ef.purdue.edu)
e
s 00006/00000/00077
d D 2.2 86/04/11 16:35:29 bloom 5 4
c check sequence number
e
s 00010/00017/00067
d D 2.1 85/12/10 13:06:17 bloom 4 3
c Multi network support
e
s 00014/00005/00070
d D 1.3 85/11/16 19:07:49 bloom 3 2
c make sure bytenetorder not called multiple times per packet
e
s 00001/00001/00074
d D 1.2 85/09/18 19:43:10 bloom 2 1
c fix syslog messages
e
s 00075/00000/00000
d D 1.1 85/06/22 22:07:44 gusella 1 0
c date and time created 85/06/22 22:07:44 by gusella
e
u
U
t
T
I 1
D 12
/*
D 7
 * Copyright (c) 1983 Regents of the University of California.
E 7
I 7
 * Copyright (c) 1985 Regents of the University of California.
E 12
I 12
/*-
D 13
 * Copyright (c) 1985, 1993 The Regents of the University of California.
E 12
E 7
D 8
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 10
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 9
E 8
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 8
#endif not lint
E 8
I 8
#endif /* not lint */
E 8

I 12
#ifdef sgi
#ident "$Revision: 1.6 $"
#endif

E 12
#include "globals.h"
D 12
#include <protocols/timed.h>
E 12

D 12
#define RECEIVED	0
#define LOST	 	1
#define SECFORACK	1	/* seconds */
#define USECFORACK	0	/* microseconds */
#define MAXCOUNT	5

E 12
struct tsp *answer;
D 4
extern int sock;
extern struct sockaddr_in server;
I 3
extern int trace;
extern FILE *fd;
E 4
E 3

I 12
extern u_short sequence;

void
xmit(type, seq, addr)
	int type;
	u_int seq;
	struct sockaddr_in *addr;
{
	static struct tsp msg;

	msg.tsp_type = type;
	msg.tsp_seq = seq;
	msg.tsp_vers = TSPVERSION;
	(void)strcpy(msg.tsp_name, hostname);
	bytenetorder(&msg);
	if (sendto(sock, (char *)&msg, sizeof(struct tsp), 0,
		   (struct sockaddr*)addr, sizeof(struct sockaddr)) < 0) {
		trace_sendto_err(addr->sin_addr);
	}
}


E 12
/*
D 12
 * Acksend implements reliable datagram transmission by using sequence 
E 12
I 12
 * Acksend implements reliable datagram transmission by using sequence
E 12
 * numbers and retransmission when necessary.
D 4
 * `name' is set to name of destination whose address is in global 
 * variable `server'.
E 4
I 4
D 12
 * `name' is the name of the destination
 * `addr' is the address to send to
E 12
E 4
 * If `name' is ANYADDR, this routine implements reliable broadcast.
I 12
 *
 * Because this function calls readmsg(), none of its args may be in
 *	a message provided by readmsg().
E 12
 */
D 12

D 4
struct tsp *acksend(message, name, ack)
E 4
I 4
struct tsp *acksend(message, addr, name, ack, net)
E 4
struct tsp *message;
I 4
struct sockaddr_in *addr;
E 4
char *name;
int ack;
I 4
struct netinfo *net;
E 12
I 12
struct tsp *
acksend(message, addr, name, ack, net, bad)
	struct tsp *message;			/* this message */
	struct sockaddr_in *addr;		/* to here */
	char *name;
	int ack;				/* look for this ack */
	struct netinfo *net;			/* receive from this network */
	int bad;				/* 1=losing patience */
E 12
E 4
{
I 12
	struct timeval twait;
E 12
	int count;
D 12
	int flag;
	extern u_short sequence;
	struct timeval tout;
	struct tsp *readmsg();
E 12
I 12
	long msec;
E 12
D 3
	int bytenetorder();
E 3

D 12
	count = 0;

E 12
I 3
	message->tsp_vers = TSPVERSION;
	message->tsp_seq = sequence;
	if (trace) {
D 12
		fprintf(fd, "acksend: ");
		if (name == ANYADDR)
			fprintf(fd, "broadcast: ");
		else
			fprintf(fd, "%s: ", name);
E 12
I 12
		fprintf(fd, "acksend: to %s: ",
			(name == ANYADDR ? "broadcast" : name));
E 12
D 6
		print(message);
E 6
I 6
		print(message, addr);
E 6
	}
	bytenetorder(message);
I 12

	msec = 200;
	count = bad ? 1 : 5;	/* 5 packets in 6.4 seconds */
	answer = 0;
E 12
E 3
	do {
D 3
		message->tsp_seq = sequence;
E 3
D 4
		if (name == ANYADDR) {
			broadcast(message);
		} else {
D 3
			message->tsp_vers = TSPVERSION;
			bytenetorder(message);
E 3
			if (sendto(sock, (char *)message, sizeof(struct tsp),
					0, &server, 
					sizeof(struct sockaddr_in)) < 0) {
D 2
				syslog(LOG_ERR, "timed: sendto: %m");
E 2
I 2
D 3
				syslog(LOG_ERR, "sendto: %m");
E 3
I 3
				syslog(LOG_ERR, "acksend: sendto: %m");
E 3
E 2
				exit(1);
			}
E 4
I 4
D 11
		if (sendto(sock, (char *)message, sizeof(struct tsp), 0, addr,
		    sizeof(struct sockaddr_in)) < 0) {
E 11
I 11
D 12
		if (sendto(sock, (char *)message, sizeof(struct tsp), 0,
		    (struct sockaddr *)addr, sizeof(struct sockaddr_in)) < 0) {
E 11
			syslog(LOG_ERR, "acksend: sendto: %m");
			exit(1);
E 12
I 12
		if (!answer) {
			/* do not go crazy transmitting just because the
			 * other guy cannot keep our sequence numbers
			 * straight.
			 */
			if (sendto(sock, (char *)message, sizeof(struct tsp),
				   0, (struct sockaddr*)addr,
				   sizeof(struct sockaddr)) < 0) {
				trace_sendto_err(addr->sin_addr);
				break;
			}
E 12
E 4
		}
D 12
		tout.tv_sec = SECFORACK;
		tout.tv_usec = USECFORACK;
D 4
		answer  = readmsg(ack, name, &tout);
E 4
I 4
		answer  = readmsg(ack, name, &tout, net);
E 4
		if (answer != NULL) {
E 12
I 12

		mstotvround(&twait, msec);
		answer  = readmsg(ack, name, &twait, net);
		if (answer != 0) {
E 12
I 5
			if (answer->tsp_seq != sequence) {
				if (trace)
D 12
					fprintf(fd, "acksend: seq # %d != %d\n",
					    answer->tsp_seq, sequence);
E 12
I 12
					fprintf(fd,"acksend: seq # %u!=%u\n",
						answer->tsp_seq, sequence);
E 12
				continue;
			}
E 5
D 12
			flag = RECEIVED;
		} else {
			flag = LOST;
			if (++count == MAXCOUNT) {
				break;
			}
E 12
I 12
			break;
E 12
		}
D 12
	} while (flag != RECEIVED);
E 12
I 12

		msec *= 2;
	} while (--count > 0);
E 12
D 7
	if (++sequence > MAXSEQ)
		sequence = 1;
E 7
I 7
	sequence++;
I 12

E 12
E 7
	return(answer);
}
E 1
