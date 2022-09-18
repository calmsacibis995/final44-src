h09697
s 00002/00002/00460
d D 8.1 93/06/06 14:09:49 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00249/00230/00213
d D 5.1 93/05/11 11:51:15 bostic 19 18
c new version from Vernon Schryver (vjs@sgi.com); see ../timed/CHANGES for details
e
s 00008/00007/00435
d D 2.13 91/03/02 17:36:04 bostic 18 17
c ANSI
e
s 00001/00011/00441
d D 2.12 90/06/01 19:04:10 bostic 17 16
c new copyright notice
e
s 00010/00005/00442
d D 2.11 88/06/18 14:08:21 bostic 16 15
c install approved copyright notice
e
s 00009/00003/00438
d D 2.10 87/12/23 14:30:14 bostic 15 14
c append Berkeley header; NASA wants a copy
e
s 00063/00004/00378
d D 2.9 86/06/05 14:12:09 bloom 14 13
c some packets may come from the local machine on ignored networks,
c check version numbers
e
s 00001/00001/00381
d D 2.8 86/06/02 11:41:58 bloom 13 12
c fix reference through null pointer
e
s 00050/00049/00332
d D 2.7 86/06/01 20:48:43 bloom 12 11
c plug memory leak, drop packets from permanently ignored networks, cleanup
e
s 00001/00000/00380
d D 2.6 86/05/20 12:09:06 karels 11 10
c yow!
e
s 00018/00002/00362
d D 2.5 86/05/16 00:38:05 bloom 10 9
c only print the interesting fields in all messages
e
s 00020/00008/00344
d D 2.4 86/05/15 08:49:33 bloom 9 8
c print LOOP packet differently, drop some loop packets
e
s 00002/00002/00350
d D 2.3 86/04/21 15:55:12 bloom 8 7
c date now passes off an absolute time, packet types changed
e
s 00022/00012/00330
d D 2.2 86/04/11 18:16:35 bloom 7 6
c major work on multiple network code (Kirk Smith, ks@ef.purdue.edu)
e
s 00024/00030/00318
d D 2.1 85/12/10 13:07:17 bloom 6 5
c Multi network support
e
s 00005/00004/00343
d D 1.5 85/11/20 18:45:47 bloom 5 4
c select has changed
e
s 00000/00002/00347
d D 1.4 85/11/16 18:32:24 bloom 4 3
c use line buffering for traces instead of explicit calls to fflush
e
s 00001/00000/00348
d D 1.3 85/11/16 17:46:46 bloom 3 2
c should ack QUIT's as well
e
s 00050/00026/00298
d D 1.2 85/09/18 19:52:34 bloom 2 1
c move constants, macros shouldn't contain local variables, syslog message fixes
c Only handle packets from "your" network, tracing and misc cleanup
e
s 00324/00000/00000
d D 1.1 85/06/27 01:13:16 gusella 1 0
c date and time created 85/06/27 01:13:16 by gusella
e
u
U
t
T
I 1
D 19
/*
 * Copyright (c) 1983 Regents of the University of California.
E 19
I 19
/*-
D 20
 * Copyright (c) 1985, 1993 The Regents of the University of California.
E 19
D 15
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 15
I 15
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
D 17
 * Redistribution and use in source and binary forms are permitted
D 16
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 16
I 16
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
E 17
I 17
 * %sccs.include.redist.c%
E 17
E 16
E 15
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 15
#endif not lint
E 15
I 15
#endif /* not lint */
E 15

I 19
#ifdef sgi
#ident "$Revision: 1.17 $"
#endif

E 19
#include "globals.h"
D 19
#include <protocols/timed.h>
E 19

D 2
#define SLAVE 	0
#define MASTER	1
E 2
I 2
extern char *tsptype[];
E 2

/*
 * LOOKAT checks if the message is of the requested type and comes from
D 19
 * the right machine, returning 1 in case of affirmative answer 
E 19
I 19
 * the right machine, returning 1 in case of affirmative answer
E 19
 */
D 19

E 19
D 2
#define LOOKAT(msg) \
	((((type == TSP_ANY) || (type == (msg).tsp_type)) && \
	((machfrom == NULL) || (strcmp(machfrom, (msg).tsp_name) == 0))) \
E 2
I 2
D 6
#define LOOKAT(msg, mtype, mfrom) \
E 6
I 6
#define LOOKAT(msg, mtype, mfrom, netp, froms) \
E 6
D 19
	(((((mtype) == TSP_ANY) || ((mtype) == (msg).tsp_type)) && \
D 6
	(((mfrom) == NULL) || (strcmp((mfrom), (msg).tsp_name) == 0))) \
E 6
I 6
	(((mfrom) == NULL) || (strcmp((mfrom), (msg).tsp_name) == 0)) && \
	(((netp) == NULL) || \
	(((netp)->mask & (froms).sin_addr.s_addr) == (netp)->net))) \
E 6
E 2
	? 1 : 0)
E 19
I 19
	(((mtype) == TSP_ANY || (mtype) == (msg).tsp_type) &&		\
	 ((mfrom) == 0 || !strcmp((mfrom), (msg).tsp_name)) &&		\
	 ((netp) == 0 || 						\
	  ((netp)->mask & (froms).sin_addr.s_addr) == (netp)->net.s_addr))
E 19

D 2
#define ISTOUTOFF \
	((rtime.tv_sec > rtout.tv_sec || (rtime.tv_sec == rtout.tv_sec && \
				rtime.tv_usec >= rtout.tv_usec)) \
E 2
I 2
D 12
#define ISTOUTOFF(rtime, rtout) \
E 12
I 12
D 19
#define MORETIME(rtime, rtout) \
E 12
	(((rtime).tv_sec > (rtout).tv_sec || \
	    ((rtime).tv_sec == (rtout).tv_sec && \
		(rtime).tv_usec >= (rtout).tv_usec)) \
E 2
D 12
	? 1 : 0)
E 12
I 12
	? 0 : 1)
E 12

E 19
struct timeval rtime, rwait, rtout;
struct tsp msgin;
static struct tsplist {
	struct tsp info;
I 19
	struct timeval when;
E 19
	struct sockaddr_in addr;
	struct tsplist *p;
} msgslist;
D 6
struct tsplist *ptr, *prev;
E 6
struct sockaddr_in from;
I 7
struct netinfo *fromnet;
I 19
struct timeval from_when;
E 19
E 7
D 6
extern int trace;
extern int sock;
extern char hostname[];
extern FILE *fd;
E 6

/*
D 19
 * `readmsg' returns message `type' sent by `machfrom' if it finds it 
 * either in the receive queue, or in a linked list of previously received 
E 19
I 19
 * `readmsg' returns message `type' sent by `machfrom' if it finds it
 * either in the receive queue, or in a linked list of previously received
E 19
 * messages that it maintains.
 * Otherwise it waits to see if the appropriate message arrives within
 * `intvl' seconds. If not, it returns NULL.
 */

D 6
struct tsp *readmsg(type, machfrom, intvl)
E 6
I 6
struct tsp *
readmsg(type, machfrom, intvl, netfrom)
D 19

E 6
int type;
char *machfrom;
struct timeval *intvl;
I 6
struct netinfo *netfrom;
E 19
I 19
	int type;
	char *machfrom;
	struct timeval *intvl;
	struct netinfo *netfrom;
E 19
E 6
{
	int length;
D 5
	int ready, found;
E 5
I 5
	fd_set ready;
E 5
D 2
	static struct tsp *ret;
E 2
I 2
D 12
	struct tsp *ret = NULL;
E 12
E 2
D 6
	extern int status;
E 6
	static struct tsplist *head = &msgslist;
	static struct tsplist *tail = &msgslist;
I 19
	static int msgcnt = 0;
E 19
D 12
	int inet_netof();
D 6
	char *malloc(), *strcpy();
E 6
	int bytenetorder(), bytehostorder();
E 12
I 6
	struct tsplist *prev;
	register struct netinfo *ntp;
	register struct tsplist *ptr;
E 6

D 2
	ret = NULL;

E 2
	if (trace) {
I 2
D 19
		fprintf(fd, "looking for %s from %s\n",
D 13
			tsptype[type], machfrom);
E 13
I 13
			tsptype[type], machfrom == NULL ? "ANY" : machfrom);
E 13
E 2
		ptr = head->p;
		fprintf(fd, "msgqueue:\n");
		while (ptr != NULL) {
			fprintf(fd, "\t");
D 7
			print(&ptr->info);
E 7
I 7
			print(&ptr->info, &ptr->addr);
E 7
			ptr = ptr->p;
E 19
I 19
		fprintf(fd, "readmsg: looking for %s from %s, %s\n",
			tsptype[type], machfrom == NULL ? "ANY" : machfrom,
			netfrom == NULL ? "ANYNET" : inet_ntoa(netfrom->net));
		if (head->p != 0) {
			length = 1;
			for (ptr = head->p; ptr != 0; ptr = ptr->p) {
				/* do not repeat the hundreds of messages */
				if (++length > 3) {
					if (ptr == tail) {
						fprintf(fd,"\t ...%d skipped\n",
							length);
					} else {
						continue;
					}
				}
				fprintf(fd, length > 1 ? "\t" : "queue:\t");
				print(&ptr->info, &ptr->addr);
			}
E 19
		}
	}

	ptr = head->p;
	prev = head;

	/*
D 19
	 * Look for the requested message scanning through the 
	 * linked list. If found, return it and free the space 
E 19
I 19
	 * Look for the requested message scanning through the
	 * linked list. If found, return it and free the space
E 19
	 */

	while (ptr != NULL) {
D 2
		if (LOOKAT(ptr->info)) {
E 2
I 2
D 6
		if (LOOKAT(ptr->info, type, machfrom)) {
E 6
I 6
		if (LOOKAT(ptr->info, type, machfrom, netfrom, ptr->addr)) {
I 19
again:
E 19
E 6
E 2
D 12
			ret = (struct tsp *)malloc(sizeof(struct tsp)); 
			*ret = ptr->info;
E 12
I 12
			msgin = ptr->info;
E 12
			from = ptr->addr;
I 19
			from_when = ptr->when;
E 19
			prev->p = ptr->p;
D 19
			if (ptr == tail) 
E 19
I 19
			if (ptr == tail)
E 19
				tail = prev;
			free((char *)ptr);
I 14
			fromnet = NULL;
E 14
D 12
			break;
E 12
I 12
			if (netfrom == NULL)
			    for (ntp = nettab; ntp != NULL; ntp = ntp->next) {
				    if ((ntp->mask & from.sin_addr.s_addr) ==
D 19
					ntp->net) {
E 19
I 19
					ntp->net.s_addr) {
E 19
					    fromnet = ntp;
					    break;
				    }
			    }
			else
			    fromnet = netfrom;
			if (trace) {
D 19
				fprintf(fd, "readmsg: ");
E 19
I 19
				fprintf(fd, "readmsg: found ");
E 19
				print(&msgin, &from);
			}
I 19

/* The protocol can get far behind.  When it does, it gets
 *	hopelessly confused.  So delete duplicate messages.
 */
			for (ptr = prev; (ptr = ptr->p) != NULL; prev = ptr) {
				if (ptr->addr.sin_addr.s_addr
					== from.sin_addr.s_addr
				    && ptr->info.tsp_type == msgin.tsp_type) {
					if (trace)
						fprintf(fd, "\tdup ");
					goto again;
				}
			}
			msgcnt--;
E 19
			return(&msgin);
E 12
		} else {
			prev = ptr;
			ptr = ptr->p;
		}
	}

D 12
	if (ret != NULL)
		goto out;

E 12
	/*
	 * If the message was not in the linked list, it may still be
D 19
	 * coming from the network. Set the timer and wait 
E 19
I 19
	 * coming from the network. Set the timer and wait
E 19
	 * on a select to read the next incoming message: if it is the
	 * right one, return it, otherwise insert it in the linked list.
	 */

D 19
	(void)gettimeofday(&rtime, (struct timezone *)0);
	rtout.tv_sec = rtime.tv_sec + intvl->tv_sec;
	rtout.tv_usec = rtime.tv_usec + intvl->tv_usec;
	if (rtout.tv_usec > 1000000) {
		rtout.tv_usec -= 1000000;
		rtout.tv_sec++;
	}

E 19
I 19
	(void)gettimeofday(&rtout, 0);
	timevaladd(&rtout, intvl);
E 19
I 6
	FD_ZERO(&ready);
E 6
D 12
	for (;;) {
E 12
I 12
D 19
	for (; MORETIME(rtime, rtout);
	    (void)gettimeofday(&rtime, (struct timezone *)0)) {
E 12
		rwait.tv_sec = rtout.tv_sec - rtime.tv_sec;
		rwait.tv_usec = rtout.tv_usec - rtime.tv_usec;
		if (rwait.tv_usec < 0) {
			rwait.tv_usec += 1000000;
			rwait.tv_sec--;
		}
		if (rwait.tv_sec < 0) 
E 19
I 19
	for (;;) {
		(void)gettimeofday(&rtime, 0);
		timevalsub(&rwait, &rtout, &rtime);
		if (rwait.tv_sec < 0)
E 19
			rwait.tv_sec = rwait.tv_usec = 0;
I 19
		else if (rwait.tv_sec == 0
			 && rwait.tv_usec < 1000000/CLK_TCK)
			rwait.tv_usec = 1000000/CLK_TCK;
E 19

		if (trace) {
D 19
			fprintf(fd, "readmsg: wait: (%d %d)\n", 
						rwait.tv_sec, rwait.tv_usec);
E 19
I 19
			fprintf(fd, "readmsg: wait %ld.%6ld at %s\n",
				rwait.tv_sec, rwait.tv_usec, date());
			/* Notice a full disk, as we flush trace info.
			 * It is better to flush periodically than at
			 * every line because the tracing consists of bursts
			 * of many lines.  Without care, tracing slows
			 * down the code enough to break the protocol.
			 */
			if (rwait.tv_sec != 0
			    && EOF == fflush(fd))
				traceoff("Tracing ended for cause at %s\n");
E 19
D 4
			(void)fflush(fd);
E 4
		}
I 19

E 19
D 5
		ready = 1<<sock;
		found = select(20, &ready, (int *)0, (int *)0, &rwait);
		if (found) {
E 5
I 5
D 6
		FD_ZERO(&ready);
E 6
		FD_SET(sock, &ready);
D 19
		if (select(FD_SETSIZE, &ready, (fd_set *)0, (fd_set *)0,
		    &rwait)) {
E 5
			length = sizeof(struct sockaddr_in);
			if (recvfrom(sock, (char *)&msgin, sizeof(struct tsp), 
D 18
						0, &from, &length) < 0) {
D 2
				syslog(LOG_ERR, "timed: receiving datagram packet: %m");
E 2
I 2
				syslog(LOG_ERR, "receiving datagram packet: %m");
E 18
I 18
			    0, (struct sockaddr *)&from, &length) < 0) {
				syslog(LOG_ERR,
				    "receiving datagram packet: %m");
E 18
E 2
				exit(1);
			}
E 19
I 19
		if (!select(sock+1, &ready, (fd_set *)0, (fd_set *)0,
			   &rwait)) {
			if (rwait.tv_sec == 0 && rwait.tv_usec == 0)
				return(0);
			continue;
		}
		length = sizeof(from);
		if (recvfrom(sock, (char *)&msgin, sizeof(struct tsp), 0,
			     (struct sockaddr*)&from, &length) < 0) {
			syslog(LOG_ERR, "recvfrom: %m");
			exit(1);
		}
		(void)gettimeofday(&from_when, (struct timezone *)0);
		bytehostorder(&msgin);
E 19

D 19
			bytehostorder(&msgin);

I 14
			if (msgin.tsp_vers > TSPVERSION) {
				if (trace) {
				    fprintf(fd, "readmsg: version mismatch\n");
				    /* should do a dump of the packet, but... */
				}
				continue;
E 19
I 19
		if (msgin.tsp_vers > TSPVERSION) {
			if (trace) {
			    fprintf(fd,"readmsg: version mismatch\n");
			    /* should do a dump of the packet */
E 19
			}
I 19
			continue;
		}
E 19

E 14
I 12
D 19
			fromnet = NULL;
			for (ntp = nettab; ntp != NULL; ntp = ntp->next)
				if ((ntp->mask & from.sin_addr.s_addr) ==
				    ntp->net) {
					fromnet = ntp;
					break;
				}

E 12
D 2
/*
 * Should check here to see if message comes from local net.
 * Until done, master cannot run on gateway conneting
 * two subnets each with running timedaemons.
 */
E 2
I 2
D 6
			if ((from.sin_addr.s_addr & netmask) != mynet) {
				if (trace) {
					fprintf(fd, "readmsg: wrong network: ");
					print(&msgin);
				}
				(void)gettimeofday(&rtime,(struct timezone *)0);
				if (ISTOUTOFF(rtime, rtout))
					break;
				else
					continue;
			}
E 6
E 2
			/*
I 12
			 * drop packets from nets we are ignoring permanently
			 */
			if (fromnet == NULL) {
D 14
				if (trace) {
					fprintf(fd, "readmsg: discarded: ");
					print(&msgin, &from);
E 14
I 14
				/* 
				 * The following messages may originate on
				 * this host with an ignored network address
				 */
				if (msgin.tsp_type != TSP_TRACEON &&
				    msgin.tsp_type != TSP_SETDATE &&
				    msgin.tsp_type != TSP_MSITE &&
#ifdef	TESTING
				    msgin.tsp_type != TSP_TEST &&
#endif
				    msgin.tsp_type != TSP_TRACEOFF) {
					if (trace) {
					    fprintf(fd, "readmsg: discarded: ");
					    print(&msgin, &from);
					}
					continue;
E 14
				}
E 19
I 19
		fromnet = NULL;
		for (ntp = nettab; ntp != NULL; ntp = ntp->next)
			if ((ntp->mask & from.sin_addr.s_addr) ==
			    ntp->net.s_addr) {
				fromnet = ntp;
				break;
E 19
D 14
				continue;
E 14
			}

I 19
		/*
		 * drop packets from nets we are ignoring permanently
		 */
		if (fromnet == NULL) {
E 19
			/*
E 12
D 19
			 * Throw away messages coming from this machine, unless
			 * they are of some particular type.
			 * This gets rid of broadcast messages and reduces
			 * master processing time.
E 19
I 19
			 * The following messages may originate on
			 * this host with an ignored network address
E 19
			 */
D 19
			if ( !(strcmp(msgin.tsp_name, hostname) != 0 ||
D 8
					msgin.tsp_type == TSP_DATE ||
E 8
I 8
					msgin.tsp_type == TSP_SETDATE ||
E 8
#ifdef TESTING
					msgin.tsp_type == TSP_TEST ||
#endif
					msgin.tsp_type == TSP_MSITE ||
I 9
					(msgin.tsp_type == TSP_LOOP &&
					msgin.tsp_hopcnt != 10) ||
E 9
					msgin.tsp_type == TSP_TRACEON ||
					msgin.tsp_type == TSP_TRACEOFF)) {
E 19
I 19
			if (msgin.tsp_type != TSP_TRACEON &&
			    msgin.tsp_type != TSP_SETDATE &&
			    msgin.tsp_type != TSP_MSITE &&
			    msgin.tsp_type != TSP_TEST &&
			    msgin.tsp_type != TSP_TRACEOFF) {
E 19
				if (trace) {
D 19
					fprintf(fd, "readmsg: discarded: ");
D 7
					print(&msgin);
E 7
I 7
					print(&msgin, &from);
E 19
I 19
				    fprintf(fd,"readmsg: discard null net ");
				    print(&msgin, &from);
E 19
E 7
				}
D 12
				(void)gettimeofday(&rtime,(struct timezone *)0);
D 2
				if (ISTOUTOFF)
E 2
I 2
				if (ISTOUTOFF(rtime, rtout))
E 2
					break;
				else
					continue;
E 12
I 12
				continue;
E 12
			}
I 19
		}
E 19

D 19
			/*
			 * Send acknowledgements here; this is faster and avoids
			 * deadlocks that would occur if acks were sent from a 
			 * higher level routine.  Different acknowledgements are
			 * necessary, depending on status.
			 */
D 6
			if (status == MASTER)
				masterack();
			else 
				slaveack();
E 6
I 6
D 12
			for (ntp = nettab; ntp != NULL; ntp = ntp->next) {
				if ((ntp->mask & from.sin_addr.s_addr) ==
				    ntp->net) {
					if (ntp->status == MASTER)
						masterack();
D 7
					else 
E 7
I 7
					else
E 7
						slaveack();
					break;
				}
			}
E 12
I 12
			if (fromnet->status == MASTER)
				masterack();
			else if (fromnet->status == SLAVE)
				slaveack();
I 14
			else
				ignoreack();
				
E 14
E 12
E 6
D 7

E 7
D 2
			if (LOOKAT(msgin)) {
E 2
I 2
D 6
			if (LOOKAT(msgin, type, machfrom)) {
E 6
I 6
			if (LOOKAT(msgin, type, machfrom, netfrom, from)) {
E 6
E 2
D 12
				ret = &msgin;
				break;
E 12
I 12
				if (trace) {
					fprintf(fd, "readmsg: ");
					print(&msgin, &from);
				}
				return(&msgin);
E 12
			} else {
				tail->p = (struct tsplist *)
						malloc(sizeof(struct tsplist)); 
				tail = tail->p;
				tail->p = NULL;
				tail->info = msgin;
				tail->addr = from;
E 19
I 19
		/*
		 * Throw away messages coming from this machine,
		 * unless they are of some particular type.
		 * This gets rid of broadcast messages and reduces
		 * master processing time.
		 */
		if (!strcmp(msgin.tsp_name, hostname)
		    && msgin.tsp_type != TSP_SETDATE
		    && msgin.tsp_type != TSP_TEST
		    && msgin.tsp_type != TSP_MSITE
		    && msgin.tsp_type != TSP_TRACEON
		    && msgin.tsp_type != TSP_TRACEOFF
		    && msgin.tsp_type != TSP_LOOP) {
			if (trace) {
				fprintf(fd, "readmsg: discard own ");
				print(&msgin, &from);
E 19
			}
I 19
			continue;
		}

		/*
		 * Send acknowledgements here; this is faster and
		 * avoids deadlocks that would occur if acks were
		 * sent from a higher level routine.  Different
		 * acknowledgements are necessary, depending on
		 * status.
		 */
		if (fromnet == NULL)	/* do not de-reference 0 */
			ignoreack();
		else if (fromnet->status == MASTER)
			masterack();
		else if (fromnet->status == SLAVE)
			slaveack();
		else
			ignoreack();

		if (LOOKAT(msgin, type, machfrom, netfrom, from)) {
			if (trace) {
				fprintf(fd, "readmsg: ");
				print(&msgin, &from);
			}
			return(&msgin);
		} else if (++msgcnt > NHOSTS*3) {

/* The protocol gets hopelessly confused if it gets too far
*	behind.  However, it seems able to recover from all cases of lost
*	packets.  Therefore, if we are swamped, throw everything away.
*/
			if (trace)
				fprintf(fd,
					"readmsg: discarding %d msgs\n",
					msgcnt);
			msgcnt = 0;
			while ((ptr=head->p) != NULL) {
				head->p = ptr->p;
				free((char *)ptr);
			}
			tail = head;
E 19
D 12

			(void)gettimeofday(&rtime, (struct timezone *)0);
D 2
			if (ISTOUTOFF)
E 2
I 2
			if (ISTOUTOFF(rtime, rtout))
E 2
				break;
E 12
		} else {
D 19
			break;
E 19
I 19
			tail->p = (struct tsplist *)
				    malloc(sizeof(struct tsplist));
			tail = tail->p;
			tail->p = NULL;
			tail->info = msgin;
			tail->addr = from;
			/* timestamp msgs so SETTIMEs are correct */
			tail->when = from_when;
E 19
		}
	}
D 12
out:
	if (ret != NULL) {
		if (trace) {
			fprintf(fd, "readmsg: ");
D 7
			print(ret);
E 7
I 7
			print(ret, &from);
E 7
		}
I 7
		fromnet = NULL;
		for (ntp = nettab; ntp != NULL; ntp = ntp->next) {
			if ((ntp->mask & from.sin_addr.s_addr) ==
			    ntp->net) {
				fromnet = ntp;
				break;
			}
		}
E 7
	}
	return(ret);
E 12
I 12
D 19
	return((struct tsp *)NULL);
E 19
E 12
}

/*
D 19
 * `slaveack' sends the necessary acknowledgements: 
 * only the type ACK is to be sent by a slave 
E 19
I 19
 * Send the necessary acknowledgements:
 * only the type ACK is to be sent by a slave
E 19
 */
D 19

E 19
I 19
void
E 19
slaveack()
{
D 19
	int length;
	struct tsp resp;

	length = sizeof(struct sockaddr_in);
E 19
	switch(msgin.tsp_type) {

	case TSP_ADJTIME:
	case TSP_SETTIME:
	case TSP_ACCEPT:
	case TSP_REFUSE:
	case TSP_TRACEON:
	case TSP_TRACEOFF:
I 3
	case TSP_QUIT:
E 3
D 19
		resp = msgin;
		resp.tsp_type = TSP_ACK;
		resp.tsp_vers = TSPVERSION;
		(void)strcpy(resp.tsp_name, hostname);
E 19
I 2
		if (trace) {
			fprintf(fd, "Slaveack: ");
I 14
D 19
			print(&resp, &from);
E 19
I 19
			print(&msgin, &from);
E 19
		}
D 19
		bytenetorder(&resp);     /* this is not really necessary here */
		if (sendto(sock, (char *)&resp, sizeof(struct tsp), 0, 
D 18
						&from, length) < 0) {
E 18
I 18
		    (struct sockaddr *)&from, length) < 0) {
E 18
			syslog(LOG_ERR, "sendto: %m");
			exit(1);
		}
E 19
I 19
		xmit(TSP_ACK,msgin.tsp_seq, &from);
E 19
		break;
I 19

E 19
	default:
I 19
		if (trace) {
			fprintf(fd, "Slaveack: no ack: ");
			print(&msgin, &from);
		}
E 19
		break;
	}
}

/*
 * Certain packets may arrive from this machine on ignored networks.
 * These packets should be acknowledged.
 */
D 19

E 19
I 19
void
E 19
ignoreack()
{
D 19
	int length;
	struct tsp resp;

	length = sizeof(struct sockaddr_in);
E 19
	switch(msgin.tsp_type) {

	case TSP_TRACEON:
	case TSP_TRACEOFF:
D 19
		resp = msgin;
		resp.tsp_type = TSP_ACK;
		resp.tsp_vers = TSPVERSION;
		(void)strcpy(resp.tsp_name, hostname);
E 19
I 19
	case TSP_QUIT:
E 19
		if (trace) {
			fprintf(fd, "Ignoreack: ");
E 14
D 7
			print(&resp);
E 7
I 7
D 19
			print(&resp, &from);
E 19
I 19
			print(&msgin, &from);
E 19
E 7
		}
E 2
D 19
		bytenetorder(&resp);     /* this is not really necessary here */
		if (sendto(sock, (char *)&resp, sizeof(struct tsp), 0, 
D 18
						&from, length) < 0) {
E 18
I 18
		    (struct sockaddr *)&from, length) < 0) {
E 18
D 2
			syslog(LOG_ERR, "timed: sendto: %m");
E 2
I 2
			syslog(LOG_ERR, "sendto: %m");
E 2
			exit(1);
		}
E 19
I 19
		xmit(TSP_ACK,msgin.tsp_seq, &from);
E 19
		break;
I 19

E 19
	default:
I 19
		if (trace) {
			fprintf(fd, "Ignoreack: no ack: ");
			print(&msgin, &from);
		}
E 19
		break;
	}
}

/*
D 19
 * `masterack' sends the necessary acknowledgments 
 * to the messages received by a master 
E 19
I 19
 * `masterack' sends the necessary acknowledgments
 * to the messages received by a master
E 19
 */
D 19

E 19
I 19
void
E 19
masterack()
{
D 19
	int length;
E 19
	struct tsp resp;

D 19
	length = sizeof(struct sockaddr_in);

E 19
	resp = msgin;
	resp.tsp_vers = TSPVERSION;
	(void)strcpy(resp.tsp_name, hostname);
D 2
	bytenetorder(&resp); 	     /* this is not really necessary here */
E 2

	switch(msgin.tsp_type) {

	case TSP_QUIT:
	case TSP_TRACEON:
	case TSP_TRACEOFF:
D 19
	case TSP_MSITE:
E 19
	case TSP_MSITEREQ:
D 19
		resp.tsp_type = TSP_ACK;
I 2
		bytenetorder(&resp);
E 19
		if (trace) {
			fprintf(fd, "Masterack: ");
D 7
			print(&resp);
E 7
I 7
D 19
			print(&resp, &from);
E 19
I 19
			print(&msgin, &from);
E 19
E 7
		}
E 2
D 19
		if (sendto(sock, (char *)&resp, sizeof(struct tsp), 0, 
D 18
						&from, length) < 0) {
E 18
I 18
		    (struct sockaddr *)&from, length) < 0) {
E 18
D 2
			syslog(LOG_ERR, "timed: sendto: %m");
E 2
I 2
			syslog(LOG_ERR, "sendto: %m");
E 2
			exit(1);
		}
E 19
I 19
		xmit(TSP_ACK,msgin.tsp_seq, &from);
E 19
		break;
I 19

E 19
	case TSP_RESOLVE:
	case TSP_MASTERREQ:
D 19
		resp.tsp_type = TSP_MASTERACK;
I 2
		bytenetorder(&resp);
E 19
		if (trace) {
			fprintf(fd, "Masterack: ");
D 7
			print(&resp);
E 7
I 7
D 19
			print(&resp, &from);
E 19
I 19
			print(&msgin, &from);
E 19
E 7
		}
E 2
D 19
		if (sendto(sock, (char *)&resp, sizeof(struct tsp), 0, 
D 18
						&from, length) < 0) {
E 18
I 18
		    (struct sockaddr *)&from, length) < 0) {
E 18
D 2
			syslog(LOG_ERR, "timed: sendto: %m");
E 2
I 2
			syslog(LOG_ERR, "sendto: %m");
E 2
			exit(1);
		}
E 19
I 19
		xmit(TSP_MASTERACK,msgin.tsp_seq, &from);
E 19
		break;
D 8
	case TSP_DATEREQ:
E 8
I 8
D 19
	case TSP_SETDATEREQ:
E 8
		resp.tsp_type = TSP_DATEACK;
I 2
		bytenetorder(&resp);
E 19
I 19

	default:
E 19
		if (trace) {
D 19
			fprintf(fd, "Masterack: ");
D 7
			print(&resp);
E 7
I 7
			print(&resp, &from);
E 19
I 19
			fprintf(fd,"Masterack: no ack: ");
			print(&msgin, &from);
E 19
E 7
		}
E 2
D 19
		if (sendto(sock, (char *)&resp, sizeof(struct tsp), 0, 
D 18
						&from, length) < 0) {
E 18
I 18
		    (struct sockaddr *)&from, length) < 0) {
E 18
D 2
			syslog(LOG_ERR, "timed: sendto: %m");
E 2
I 2
			syslog(LOG_ERR, "sendto: %m");
E 2
			exit(1);
		}
E 19
		break;
D 19
	default:
		break;
E 19
	}
}

/*
D 19
 * Print a TSP message 
E 19
I 19
 * Print a TSP message
E 19
 */
I 19
void
E 19
D 7
print(msg)
E 7
I 7
print(msg, addr)
E 7
D 19
struct tsp *msg;
I 7
struct sockaddr_in *addr;
E 19
I 19
	struct tsp *msg;
	struct sockaddr_in *addr;
E 19
E 7
{
I 19
	char tm[26];
E 19
D 6
	extern char *tsptype[];

E 6
D 7
 	fprintf(fd, "%s %d %d (%d, %d) %s\n",
E 7
I 7
D 9
 	fprintf(fd, "%s %d %d (%d, %d) %s %s\n",
E 7
		tsptype[msg->tsp_type],
		msg->tsp_vers,
		msg->tsp_seq,
		msg->tsp_time.tv_sec, 
		msg->tsp_time.tv_usec, 
D 7
		msg->tsp_name);
E 7
I 7
		msg->tsp_name,
		inet_ntoa(addr->sin_addr));
E 9
I 9
D 10
	if (msg->tsp_type == TSP_LOOP) {
E 10
I 10
	switch (msg->tsp_type) {

	case TSP_LOOP:
E 10
D 19
		fprintf(fd, "%s %d %d (#%d) %s %s\n",
E 19
I 19
		fprintf(fd, "%s %d %-6u #%d %-15s %s\n",
E 19
			tsptype[msg->tsp_type],
			msg->tsp_vers,
			msg->tsp_seq,
			msg->tsp_hopcnt,
D 19
			msg->tsp_name,
			inet_ntoa(addr->sin_addr));
E 19
I 19
			inet_ntoa(addr->sin_addr),
			msg->tsp_name);
E 19
D 10
	} else {
E 10
I 10
		break;

I 11
	case TSP_SETTIME:
E 11
D 19
	case TSP_ADJTIME:
E 19
	case TSP_SETDATE:
	case TSP_SETDATEREQ:
E 10
D 19
		fprintf(fd, "%s %d %d (%d, %d) %s %s\n",
E 19
I 19
#ifdef sgi
		(void)cftime(tm, "%D %T", &msg->tsp_time.tv_sec);
#else
		strncpy(tm, ctime(&msg->tsp_time.tv_sec)+3+1, sizeof(tm));
		tm[15] = '\0';		/* ugh */
#endif /* sgi */
		fprintf(fd, "%s %d %-6u %s %-15s %s\n",
E 19
			tsptype[msg->tsp_type],
			msg->tsp_vers,
			msg->tsp_seq,
D 19
			msg->tsp_time.tv_sec, 
			msg->tsp_time.tv_usec, 
			msg->tsp_name,
			inet_ntoa(addr->sin_addr));
E 19
I 19
			tm,
			inet_ntoa(addr->sin_addr),
			msg->tsp_name);
E 19
I 10
		break;

I 19
	case TSP_ADJTIME:
		fprintf(fd, "%s %d %-6u (%ld,%ld) %-15s %s\n",
			tsptype[msg->tsp_type],
			msg->tsp_vers,
			msg->tsp_seq,
			msg->tsp_time.tv_sec,
			msg->tsp_time.tv_usec,
			inet_ntoa(addr->sin_addr),
			msg->tsp_name);
		break;

E 19
	default:
D 19
		fprintf(fd, "%s %d %d %s %s\n",
E 19
I 19
		fprintf(fd, "%s %d %-6u %-15s %s\n",
E 19
			tsptype[msg->tsp_type],
			msg->tsp_vers,
			msg->tsp_seq,
D 19
			msg->tsp_name,
			inet_ntoa(addr->sin_addr));
E 19
I 19
			inet_ntoa(addr->sin_addr),
			msg->tsp_name);
E 19
		break;
E 10
	}
E 9
E 7
D 4
	(void)fflush(fd);
E 4
}
E 1
