h61803
s 00002/00002/00879
d D 8.1 93/06/06 14:09:29 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00695/00350/00186
d D 5.1 93/05/11 11:51:11 bostic 26 25
c new version from Vernon Schryver (vjs@sgi.com); see ../timed/CHANGES for details
e
s 00006/00003/00530
d D 2.20 91/03/02 17:36:02 bostic 25 24
c ANSI
e
s 00001/00011/00532
d D 2.19 90/06/01 19:03:38 bostic 24 23
c new copyright notice
e
s 00002/00001/00541
d D 2.18 89/04/02 15:44:45 bostic 23 22
c add pathnames.h
e
s 00004/00026/00538
d D 2.17 88/09/20 15:47:49 bostic 22 21
c use logwtmp
e
s 00010/00005/00554
d D 2.16 88/06/18 14:08:15 bostic 21 20
c install approved copyright notice
e
s 00009/00003/00550
d D 2.15 87/12/23 14:30:09 bostic 20 19
c append Berkeley header; NASA wants a copy
e
s 00009/00006/00544
d D 2.14 86/06/05 14:56:22 bloom 19 18
c be careful with measure file pointer, multiple quits can cause problems
e
s 00003/00003/00547
d D 2.13 86/06/03 14:58:25 lepreau 18 17
c check for equality after rounding; typo
e
s 00002/00006/00548
d D 2.12 86/06/03 10:25:13 bloom 17 16
c round times now that microseconds are propogated for logwtmp()
e
s 00002/00001/00552
d D 2.11 86/05/28 20:09:41 bloom 16 15
c lint cleanup (fix sequence number problem)
e
s 00002/00008/00551
d D 2.10 86/05/28 10:21:33 bloom 15 14
c preserve microseconds
e
s 00001/00003/00558
d D 2.9 86/05/27 15:58:01 karels 14 13
c toss MAXSEQ
e
s 00010/00010/00551
d D 2.8 86/05/27 15:34:32 karels 13 12
c syslog priorities
e
s 00032/00000/00529
d D 2.7 86/05/17 21:09:14 lepreau 12 11
c log date changes to wtmp.  no rounding cause timed zeroes tv_usec
e
s 00034/00000/00495
d D 2.6 86/05/15 09:18:37 bloom 11 10
c add loop detection
e
s 00002/00002/00493
d D 2.5 86/05/01 09:46:30 bloom 10 9
c correct expected response to a QUIT
e
s 00008/00008/00487
d D 2.4 86/04/21 15:57:05 bloom 9 8
c date now sends absolute time, measure lost an arg, fix problem with 
c deleting a host
e
s 00046/00044/00449
d D 2.3 86/04/11 18:16:20 bloom 8 7
c major work on multiple network code (Kirk Smith, ks@ef.purdue.edu)
e
s 00033/00000/00460
d D 2.2 86/02/17 13:18:18 bloom 7 6
c clean hostlist when going from master to slave (from ks@purdue)
e
s 00080/00074/00380
d D 2.1 85/12/10 13:06:56 bloom 6 5
c Multi network support
e
s 00001/00000/00453
d D 1.5 85/11/16 19:07:59 bloom 5 4
c make sure bytenetorder not called multiple times per packet
e
s 00002/00003/00451
d D 1.4 85/11/16 18:32:16 bloom 4 3
c use line buffering for traces instead of explicit calls to fflush
e
s 00011/00003/00443
d D 1.3 85/10/29 11:49:35 bloom 3 2
c syslog clobbers the date returned by ctime()
e
s 00028/00029/00418
d D 1.2 85/09/18 19:48:26 bloom 2 1
c fix syslog messages, move constants, print changed from time, close trace file
c misc. other cleanup
e
s 00447/00000/00000
d D 1.1 85/06/22 22:07:53 gusella 1 0
c date and time created 85/06/22 22:07:53 by gusella
e
u
U
t
T
I 1
D 26
/*
D 13
 * Copyright (c) 1983 Regents of the University of California.
E 13
I 13
 * Copyright (c) 1985 Regents of the University of California.
E 26
I 26
/*-
D 27
 * Copyright (c) 1985, 1993 The Regents of the University of California.
E 26
E 13
D 20
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 20
I 20
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
 *
D 24
 * Redistribution and use in source and binary forms are permitted
D 21
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 21
I 21
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
E 24
I 24
 * %sccs.include.redist.c%
E 24
E 21
E 20
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 20
#endif not lint
E 20
I 20
#endif /* not lint */
E 20

I 26
#ifdef sgi
#ident "$Revision: 1.21 $"
#endif

E 26
#include "globals.h"
D 26
#include <protocols/timed.h>
E 26
I 12
#include <sys/file.h>
I 26
#include <sys/types.h>
#include <sys/times.h>
E 26
E 12
#include <setjmp.h>
I 26
#ifdef sgi
#include <sys/schedctl.h>
#endif /* sgi */
E 26
I 12
#include <utmp.h>
I 23
#include "pathnames.h"
E 23
E 12

D 2
#define OFF	0
#define ON	1

E 2
D 6
extern struct sockaddr_in from;
extern struct sockaddr_in server;

extern int trace;
E 6
D 26
extern int machup;
E 26
D 6
extern int slvcount;
E 6
extern int measure_delta;
D 6
extern int sock;
extern char hostname[];
extern struct host hp[];
extern char *fj;
extern FILE *fd;
E 6
I 6
extern jmp_buf jmpenv;
I 26
extern int Mflag;
extern int justquit;
E 26
E 6

I 11
D 16
extern short sequence;
E 16
I 16
D 26
extern u_short sequence;
E 26
I 26
static int dictate;
static int slvcount;			/* slaves listening to our clock */
E 26
E 16

E 11
D 26
#ifdef MEASURE
int header;
D 19
char *fi;
FILE *fp;
E 19
I 19
FILE *fp = NULL;
E 19
#endif
E 26
I 26
static void mchgdate __P((struct tsp *));
E 26

I 26
#ifdef sgi
extern void logwtmp __P((struct timeval *, struct timeval *));
#else
extern void logwtmp __P((char *, char *, char *));
#endif /* sgi */

E 26
/*
D 26
 * The main function of `master' is to periodically compute the differences 
 * (deltas) between its clock and the clocks of the slaves, to compute the 
 * network average delta, and to send to the slaves the differences between 
E 26
I 26
 * The main function of `master' is to periodically compute the differences
 * (deltas) between its clock and the clocks of the slaves, to compute the
 * network average delta, and to send to the slaves the differences between
E 26
 * their individual deltas and the network delta.
 * While waiting, it receives messages from the slaves (i.e. requests for
 * master's name, remote requests to set the network time, ...), and
 * takes the appropriate action.
 */
D 26

E 26
I 26
int
E 26
master()
{
D 26
	int ind;
E 26
I 26
	struct hosttbl *htp;
E 26
D 6
	int length;
E 6
	long pollingtime;
D 26
	struct timeval wait;
	struct timeval time;
I 12
D 22
	struct timeval otime;
E 22
E 12
	struct timezone tzone;
D 8
	struct timeval mytime;
E 8
	struct tsp *msg, to;
	struct sockaddr_in saveaddr;
D 6
	extern jmp_buf jmpenv;
E 6
	int findhost();
	char *date();
D 6
	char *strcpy();
E 6
	struct tsp *readmsg();
	struct tsp *answer, *acksend();
I 2
D 3
	char *olddate;
E 3
I 3
	char olddate[32];
I 6
	struct sockaddr_in server;
	register struct netinfo *ntp;
E 26
I 26
#define POLLRATE 4
	int polls;
	struct timeval wait, ntime;
	struct tsp *msg, *answer, to;
	char newdate[32];
	struct sockaddr_in taddr;
	char tname[MAXHOSTNAMELEN];
	struct netinfo *ntp;
	int i;
E 26
E 6
E 3
E 2

D 26
#ifdef MEASURE
D 19
	fi = "/usr/adm/timed.masterlog";
	fp = fopen(fi, "w");
I 4
	setlinebuf(fp);
E 19
I 19
	if (fp == NULL) {
D 23
		fp = fopen("/usr/adm/timed.masterlog", "w");
E 23
I 23
		fp = fopen(_PATH_MASTERLOG, "w");
E 23
		setlinebuf(fp);
	}
E 19
E 4
#endif

D 2
	syslog(LOG_ERR, "timed: THIS MACHINE IS MASTER\n");
E 2
I 2
D 13
	syslog(LOG_INFO, "THIS MACHINE IS MASTER");
E 13
I 13
	syslog(LOG_INFO, "This machine is master");
E 26
I 26
	syslog(LOG_NOTICE, "This machine is master");
E 26
E 13
E 2
	if (trace)
D 26
		fprintf(fd, "THIS MACHINE IS MASTER\n");

D 6
	masterup();
E 6
I 6
	for (ntp = nettab; ntp != NULL; ntp = ntp->next)
E 26
I 26
		fprintf(fd, "This machine is master\n");
	for (ntp = nettab; ntp != NULL; ntp = ntp->next) {
E 26
		if (ntp->status == MASTER)
			masterup(ntp);
E 6
D 26
	pollingtime = 0;
E 26
I 26
	}
	(void)gettimeofday(&ntime, 0);
	pollingtime = ntime.tv_sec+3;
	if (justquit)
		polls = 0;
	else
		polls = POLLRATE-1;
E 26

I 26
/* Process all outstanding messages before spending the long time necessary
 *	to update all timers.
 */
E 26
loop:
D 26
	(void)gettimeofday(&time, (struct timezone *)0);
	if (time.tv_sec >= pollingtime) {
		pollingtime = time.tv_sec + SAMPLEINTVL;
D 6
		synch();
E 6
I 6
		synch(0L);
E 26
I 26
	(void)gettimeofday(&ntime, 0);
	wait.tv_sec = pollingtime - ntime.tv_sec;
	if (wait.tv_sec < 0)
		wait.tv_sec = 0;
	wait.tv_usec = 0;
	msg = readmsg(TSP_ANY, ANYADDR, &wait, 0);
	if (!msg) {
		(void)gettimeofday(&ntime, 0);
		if (ntime.tv_sec >= pollingtime) {
			pollingtime = ntime.tv_sec + SAMPLEINTVL;
			get_goodgroup(0);
E 26
I 11

D 26
		for (ntp = nettab; ntp != NULL; ntp = ntp->next) {
			to.tsp_type = TSP_LOOP;
			to.tsp_vers = TSPVERSION;
D 14
			to.tsp_seq = sequence;
E 14
I 14
			to.tsp_seq = sequence++;
E 14
			to.tsp_hopcnt = 10;
			(void)strcpy(to.tsp_name, hostname);
			bytenetorder(&to);
			if (sendto(sock, (char *)&to, sizeof(struct tsp), 0,
D 25
			    &ntp->dest_addr, sizeof(struct sockaddr_in)) < 0) {
E 25
I 25
			    (struct sockaddr *)&ntp->dest_addr,
			    sizeof(struct sockaddr_in)) < 0) {
E 25
				syslog(LOG_ERR, "sendto: %m");
				exit(1);
E 26
I 26
/* If a bogus master told us to quit, we can have decided to ignore a
 * network.  Therefore, periodically try to take over everything.
 */
			polls = (polls + 1) % POLLRATE;
			if (0 == polls && nignorednets > 0) {
				trace_msg("Looking for nets to re-master\n");
				for (ntp = nettab; ntp; ntp = ntp->next) {
					if (ntp->status == IGNORE
					    || ntp->status == NOMASTER) {
						lookformaster(ntp);
						if (ntp->status == MASTER) {
							masterup(ntp);
							polls = POLLRATE-1;
						}
					}
					if (ntp->status == MASTER
					    && --ntp->quit_count < 0)
						ntp->quit_count = 0;
				}
				if (polls != 0)
					setstatus();
E 26
D 14
			if (++sequence > MAXSEQ)
				sequence = 1;
E 14
			}
I 26

			synch(0L);

			for (ntp = nettab; ntp != NULL; ntp = ntp->next) {
				to.tsp_type = TSP_LOOP;
				to.tsp_vers = TSPVERSION;
				to.tsp_seq = sequence++;
				to.tsp_hopcnt = MAX_HOPCNT;
				(void)strcpy(to.tsp_name, hostname);
				bytenetorder(&to);
				if (sendto(sock, (char *)&to,
					   sizeof(struct tsp), 0,
					   (struct sockaddr*)&ntp->dest_addr,
					   sizeof(ntp->dest_addr)) < 0) {
				   trace_sendto_err(ntp->dest_addr.sin_addr);
				}
			}
E 26
		}
E 11
E 6
D 26
	}
E 26

D 26
	wait.tv_sec = pollingtime - time.tv_sec;
	wait.tv_usec = 0;
D 6
	msg = readmsg(TSP_ANY, (char *)ANYADDR, &wait);
E 6
I 6
	msg = readmsg(TSP_ANY, (char *)ANYADDR, &wait, (struct netinfo *)NULL);
E 6
	if (msg != NULL) {
E 26
I 26

	} else {
E 26
		switch (msg->tsp_type) {

		case TSP_MASTERREQ:
D 6
			ind = addmach(msg->tsp_name);
E 6
I 6
D 8
			ind = addmach(msg->tsp_name, &from);
E 6
			if (trace)
				prthp();
			if (hp[ind].seq !=  msg->tsp_seq) {
				hp[ind].seq = msg->tsp_seq;
D 6
				bcopy((char *)&hp[ind].addr, 
					    (char *)&(server.sin_addr.s_addr),
					    hp[ind].length);
E 6
				to.tsp_type = TSP_SETTIME;
				(void)strcpy(to.tsp_name, hostname);
				/*
				 * give the upcoming slave the time
				 * to check its input queue before
				 * setting the time
				 */
				sleep(1);
				to.tsp_time.tv_usec = 0;
D 6
				(void)gettimeofday(&mytime, (struct timezone *)0);
E 6
I 6
				(void) gettimeofday(&mytime,
				    (struct timezone *)0);
E 6
				to.tsp_time.tv_sec = mytime.tv_sec;
D 6
				answer = acksend(&to, hp[ind].name, TSP_ACK);
E 6
I 6
				answer = acksend(&to, &hp[ind].addr,
				    hp[ind].name, TSP_ACK,
				    (struct netinfo *)NULL);
E 6
				if (answer == NULL) {
D 2
					syslog(LOG_ERR, "timed: ERROR ON SETTIME machine: %s\n", hp[ind].name);
E 2
I 2
D 6
					syslog(LOG_ERR, "ERROR ON SETTIME machine: %s", hp[ind].name);
E 6
I 6
					syslog(LOG_ERR,
					    "ERROR ON SETTIME machine: %s",
					    hp[ind].name);
E 6
E 2
					slvcount--;
				}
D 2
				pollingtime = 0;
E 2
			}
E 8
			break;
I 26

E 26
		case TSP_SLAVEUP:
D 6
			(void) addmach(msg->tsp_name);
E 6
I 6
D 8
			(void) addmach(msg->tsp_name, &from);
E 8
I 8
D 26
			ind = addmach(msg->tsp_name, &from);
			newslave(ind, msg->tsp_seq);
E 26
I 26
			newslave(msg);
E 26
E 8
E 6
D 2
			pollingtime = 0;
E 2
			break;
I 26

E 26
D 9
		case TSP_DATE:
E 9
I 9
		case TSP_SETDATE:
E 9
D 26
			saveaddr = from;
E 26
D 15
			msg->tsp_time.tv_usec = 0;
E 15
I 2
D 3
			olddate = date();
E 3
I 3
			/*
D 26
			 * the following line is necessary due to syslog
			 * calling ctime() which clobbers the static buffer
E 26
I 26
			 * XXX check to see it is from ourself
E 26
			 */
D 26
			(void)strcpy(olddate, date());
E 3
E 2
			(void)gettimeofday(&time, &tzone);
I 12
D 22
			otime = time;
E 22
E 12
D 9
			time.tv_sec += msg->tsp_time.tv_sec;
E 9
I 9
			time.tv_sec = msg->tsp_time.tv_sec;
			time.tv_usec = msg->tsp_time.tv_usec;
I 22
			logwtmp("|", "date", "");
E 22
E 9
D 13
			time.tv_sec++;
E 13
			(void)settimeofday(&time, &tzone);
I 22
			logwtmp("}", "date", "");
E 22
D 2
			syslog(LOG_ERR, "timed: date changed to: %s\n", date());
E 2
I 2
			syslog(LOG_NOTICE, "date changed from: %s", olddate);
I 12
D 22
			logwtmp(otime, time);
E 22
E 12
E 2
			msg->tsp_type = TSP_DATEACK;
			msg->tsp_vers = TSPVERSION;
			(void)strcpy(msg->tsp_name, hostname);
			bytenetorder(msg);
D 6
			length = sizeof(struct sockaddr_in);
E 6
			if (sendto(sock, (char *)msg, sizeof(struct tsp), 0,
D 6
						&saveaddr, length) < 0) {
E 6
I 6
D 25
			    &saveaddr, sizeof(struct sockaddr_in)) < 0) {
E 25
I 25
			    (struct sockaddr *)&saveaddr,
			    sizeof(struct sockaddr_in)) < 0) {
E 25
E 6
D 2
				syslog(LOG_ERR, "timed: sendto: %m");
E 2
I 2
				syslog(LOG_ERR, "sendto: %m");
E 2
				exit(1);
E 26
I 26
#ifdef sgi
			(void)cftime(newdate, "%D %T", &msg->tsp_time.tv_sec);
#else
			(void)strcpy(newdate, ctime(&msg->tsp_time.tv_sec));
#endif /* sgi */
			if (!good_host_name(msg->tsp_name)) {
				syslog(LOG_NOTICE,
				       "attempted date change by %s to %s",
				       msg->tsp_name, newdate);
				spreadtime();
				break;
E 26
			}
D 26
			spreadtime();
			pollingtime = 0;
E 26
I 26

			mchgdate(msg);
			(void)gettimeofday(&ntime, 0);
			pollingtime = ntime.tv_sec + SAMPLEINTVL;
E 26
			break;
I 26

E 26
D 9
		case TSP_DATEREQ:
E 9
I 9
		case TSP_SETDATEREQ:
E 9
D 26
			ind = findhost(msg->tsp_name);
			if (ind < 0) { 
D 2
				syslog(LOG_ERR, "timed: error on DATEREQ\n");
				break;
E 2
I 2
D 13
			    syslog(LOG_ERR,
E 13
I 13
			    syslog(LOG_WARNING,
E 13
				"DATEREQ from uncontrolled machine");
			    break;
E 26
I 26
			if (!fromnet || fromnet->status != MASTER)
				break;
#ifdef sgi
			(void)cftime(newdate, "%D %T", &msg->tsp_time.tv_sec);
#else
			(void)strcpy(newdate, ctime(&msg->tsp_time.tv_sec));
#endif /* sgi */
			htp = findhost(msg->tsp_name);
			if (htp == 0) {
				syslog(LOG_ERR,
				       "attempted SET DATEREQ by uncontrolled %s to %s",
				       msg->tsp_name, newdate);
				break;
E 26
E 2
			}
D 26
			if (hp[ind].seq !=  msg->tsp_seq) {
				hp[ind].seq = msg->tsp_seq;
D 15
				msg->tsp_time.tv_usec = 0;
E 15
I 2
D 3
				olddate = date();
E 3
I 3
				/*
				 * the following line is necessary due to syslog
				 * calling ctime() which clobbers the static buffer
				 */
				(void)strcpy(olddate, date());
E 3
E 2
				(void)gettimeofday(&time, &tzone);
I 12
D 22
				otime = time;
E 22
E 12
D 9
				time.tv_sec += msg->tsp_time.tv_sec;
E 9
I 9
				time.tv_sec = msg->tsp_time.tv_sec;
				time.tv_usec = msg->tsp_time.tv_usec;
I 22
				logwtmp("|", "date", "");
E 22
E 9
D 13
				time.tv_sec++;
E 13
				(void)settimeofday(&time, &tzone);
I 22
				logwtmp("{", "date", "");
E 26
I 26
			if (htp->seq == msg->tsp_seq)
				break;
			htp->seq = msg->tsp_seq;
			if (!htp->good) {
E 26
E 22
D 2
				syslog(LOG_ERR, "timed: date changed to: %s\n", date());
E 2
I 2
				syslog(LOG_NOTICE,
D 26
				    "date changed by %s from: %s",
				    msg->tsp_name, olddate);
E 26
I 26
				"attempted SET DATEREQ by untrusted %s to %s",
				       msg->tsp_name, newdate);
E 26
I 12
D 22
				logwtmp(otime, time);
E 22
E 12
E 2
				spreadtime();
D 26
				pollingtime = 0;
E 26
I 26
				break;
E 26
			}
I 26

			mchgdate(msg);
			(void)gettimeofday(&ntime, 0);
			pollingtime = ntime.tv_sec + SAMPLEINTVL;
E 26
			break;
I 26

E 26
		case TSP_MSITE:
I 26
			xmit(TSP_ACK, msg->tsp_seq, &from);
			break;

E 26
D 6
			msg->tsp_type = TSP_ACK;
			msg->tsp_vers = TSPVERSION;
			(void)strcpy(msg->tsp_name, hostname);
			bytenetorder(msg);
			length = sizeof(struct sockaddr_in);
			if (sendto(sock, (char *)msg, sizeof(struct tsp), 0,
						&from, length) < 0) {
D 2
				syslog(LOG_ERR, "timed: sendto: %m");
E 2
I 2
				syslog(LOG_ERR, "sendto: %m");
E 2
				exit(1);
			}
			break;
E 6
		case TSP_MSITEREQ:
			break;
I 26

E 26
		case TSP_TRACEON:
D 26
			if (!(trace)) {
D 6
				fd = fopen(fj, "w");
E 6
I 6
				fd = fopen(tracefile, "w");
E 6
I 4
				setlinebuf(fd);
E 4
				fprintf(fd, "Tracing started on: %s\n\n", 
							date());
D 4
				(void)fflush(fd);
E 4
			}
			trace = ON;
E 26
I 26
			traceon();
E 26
			break;
I 26

E 26
		case TSP_TRACEOFF:
D 26
			if (trace) {
				fprintf(fd, "Tracing ended on: %s\n", date());
D 4
				(void)fflush(fd);
E 4
D 2
				(void)close((int)fd);
E 2
I 2
				(void)fclose(fd);
E 2
			}
I 6
#ifdef GPROF
			moncontrol(0);
			_mcleanup();
			moncontrol(1);
#endif
E 6
			trace = OFF;
E 26
I 26
			traceoff("Tracing ended at %s\n");
E 26
			break;
I 26

E 26
		case TSP_ELECTION:
I 26
			if (!fromnet)
				break;
			if (fromnet->status == MASTER) {
				pollingtime = 0;
				(void)addmach(msg->tsp_name, &from,fromnet);
			}
			taddr = from;
			(void)strcpy(tname, msg->tsp_name);
E 26
			to.tsp_type = TSP_QUIT;
			(void)strcpy(to.tsp_name, hostname);
D 26
			server = from;
D 6
			answer = acksend(&to, msg->tsp_name, TSP_ACK);
E 6
I 6
			answer = acksend(&to, &server, msg->tsp_name, TSP_ACK,
			    (struct netinfo *)NULL);
E 26
I 26
			answer = acksend(&to, &taddr, tname,
					 TSP_ACK, 0, 1);
E 26
E 6
			if (answer == NULL) {
D 2
				syslog(LOG_ERR, "timed: election error\n");
E 2
I 2
D 26
				syslog(LOG_ERR, "election error");
E 2
			} else {
D 6
				(void) addmach(msg->tsp_name);
E 6
I 6
				(void) addmach(msg->tsp_name, &from);
E 26
I 26
				syslog(LOG_ERR, "election error by %s",
				       tname);
E 26
E 6
			}
D 26
			pollingtime = 0;
E 26
			break;
I 26

E 26
		case TSP_CONFLICT:
			/*
D 26
			 * After a network partition, there can be 
			 * more than one master: the first slave to 
E 26
I 26
			 * After a network partition, there can be
			 * more than one master: the first slave to
E 26
			 * come up will notify here the situation.
			 */
D 26

E 26
I 26
			if (!fromnet || fromnet->status != MASTER)
				break;
E 26
			(void)strcpy(to.tsp_name, hostname);

I 6
D 8
			for (ntp = nettab; ntp != NULL; ntp = ntp->next) {
				if ((ntp->mask & from.sin_addr.s_addr) ==
				    ntp->net)
					break;
			}
			if (ntp == NULL)
E 8
I 8
D 26
			if (fromnet == NULL)
E 8
				break;
E 6
			for(;;) {
E 26
I 26
			/* The other master often gets into the same state,
			 * with boring results if we stay at it forever.
			 */
			ntp = fromnet;	/* (acksend() can leave fromnet=0 */
			for (i = 0; i < 3; i++) {
E 26
				to.tsp_type = TSP_RESOLVE;
D 6
				answer = acksend(&to, (char *)ANYADDR, 
								TSP_MASTERACK);
E 6
I 6
D 8
				answer = acksend(&to, &ntp->dest_addr,
				    (char *)ANYADDR, TSP_MASTERACK, ntp);
E 8
I 8
D 26
				answer = acksend(&to, &fromnet->dest_addr,
				    (char *)ANYADDR, TSP_MASTERACK, fromnet);
E 8
E 6
				if (answer == NULL)
E 26
I 26
				(void)strcpy(to.tsp_name, hostname);
				answer = acksend(&to, &ntp->dest_addr,
						 ANYADDR, TSP_MASTERACK,
						 ntp, 0);
				if (!answer)
E 26
					break;
I 26
				htp = addmach(answer->tsp_name,&from,ntp);
E 26
D 2
				(void) addmach(answer->tsp_name);
E 2
				to.tsp_type = TSP_QUIT;
D 26
				server = from;
D 6
				msg = acksend(&to, answer->tsp_name, 
								TSP_MASTERACK);
E 6
I 6
D 10
				msg = acksend(&to, &server, answer->tsp_name, 
				    TSP_MASTERACK, (struct netinfo *)NULL);
E 10
I 10
				msg = acksend(&to, &server, answer->tsp_name,
				    TSP_ACK, (struct netinfo *)NULL);
E 26
I 26
				msg = acksend(&to, &htp->addr, htp->name,
					      TSP_ACK, 0, htp->noanswer);
E 26
E 10
E 6
				if (msg == NULL) {
D 2
					syslog(LOG_ERR, "timed: error on sending QUIT\n");
E 2
I 2
D 26
					syslog(LOG_ERR, "error on sending QUIT");
				} else {
D 6
					(void) addmach(answer->tsp_name);
E 6
I 6
					(void) addmach(answer->tsp_name, &from);
E 26
I 26
					syslog(LOG_ERR,
				    "no response from %s to CONFLICT-QUIT",
					       htp->name);
E 26
E 6
E 2
				}
			}
D 6
			masterup();
E 6
I 6
D 8
			masterup(ntp);
E 8
I 8
D 26
			masterup(fromnet);
E 26
I 26
			masterup(ntp);
E 26
E 8
E 6
			pollingtime = 0;
			break;
I 26

E 26
		case TSP_RESOLVE:
I 26
			if (!fromnet || fromnet->status != MASTER)
				break;
E 26
			/*
			 * do not want to call synch() while waiting
			 * to be killed!
			 */
D 26
			(void)gettimeofday(&time, (struct timezone *)0);
			pollingtime = time.tv_sec + SAMPLEINTVL;
E 26
I 26
			(void)gettimeofday(&ntime, (struct timezone *)0);
			pollingtime = ntime.tv_sec + SAMPLEINTVL;
E 26
			break;
I 26

E 26
		case TSP_QUIT:
D 26
			/* become slave */
#ifdef MEASURE
D 2
			(void)close((int)fp);
E 2
I 2
D 19
			(void)fclose(fp);
E 19
I 19
			if (fp != NULL) {
				(void)fclose(fp);
				fp = NULL;
			}
E 19
E 2
#endif
			longjmp(jmpenv, 2);
E 26
I 26
			doquit(msg);		/* become a slave */
E 26
			break;
I 26

E 26
I 11
		case TSP_LOOP:
I 26
			if (!fromnet || fromnet->status != MASTER
			    || !strcmp(msg->tsp_name, hostname))
				break;
E 26
			/*
			 * We should not have received this from a net
D 26
			 * we are master on.  There must be two masters
			 * in this case.
E 26
I 26
			 * we are master on.  There must be two masters.
E 26
			 */
I 26
			htp = addmach(msg->tsp_name, &from,fromnet);
E 26
			to.tsp_type = TSP_QUIT;
			(void)strcpy(to.tsp_name, hostname);
D 26
			server = from;
			answer = acksend(&to, &server, msg->tsp_name, TSP_ACK,
				(struct netinfo *)NULL);
			if (answer == NULL) {
E 26
I 26
			answer = acksend(&to, &htp->addr, htp->name,
					 TSP_ACK, 0, 1);
			if (!answer) {
E 26
D 13
				syslog(LOG_ERR, "election error");
E 13
I 13
				syslog(LOG_WARNING,
D 26
				    "loop breakage: no reply to QUIT");
E 13
			} else {
				(void)addmach(msg->tsp_name, &from);
E 26
I 26
				"loop breakage: no reply from %s=%s to QUIT",
				    htp->name, inet_ntoa(htp->addr.sin_addr));
				(void)remmach(htp);
E 26
			}
I 26

		case TSP_TEST:
			if (trace) {
				fprintf(fd,
		"\tnets = %d, masters = %d, slaves = %d, ignored = %d\n",
		nnets, nmasternets, nslavenets, nignorednets);
				setstatus();
			}
			pollingtime = 0;
			polls = POLLRATE-1;
			break;

E 26
E 11
		default:
			if (trace) {
D 26
				fprintf(fd, "garbage: ");
E 26
I 26
				fprintf(fd, "garbage message: ");
E 26
D 8
				print(msg);
E 8
I 8
				print(msg, &from);
E 8
			}
			break;
		}
	}
	goto loop;
}

I 26

E 26
/*
D 26
 * `synch' synchronizes all the slaves by calling measure, 
 * networkdelta and correct 
E 26
I 26
 * change the system date on the master
E 26
 */
I 26
static void
mchgdate(msg)
	struct tsp *msg;
{
	char tname[MAXHOSTNAMELEN];
	char olddate[32];
	struct timeval otime, ntime;
E 26

I 26
	(void)strcpy(tname, msg->tsp_name);

	xmit(TSP_DATEACK, msg->tsp_seq, &from);

	(void)strcpy(olddate, date());

	/* adjust time for residence on the queue */
	(void)gettimeofday(&otime, 0);
	adj_msg_time(msg,&otime);

	timevalsub(&ntime, &msg->tsp_time, &otime);
	if (ntime.tv_sec < MAXADJ && ntime.tv_sec > -MAXADJ) {
		/*
		 * do not change the clock if we can adjust it
		 */
		dictate = 3;
		synch(tvtomsround(ntime));
	} else {
#ifdef sgi
		if (0 > settimeofday(&msg->tsp_time, 0)) {
			syslog(LOG_ERR, "settimeofday(): %m");
		}
		logwtmp(&otime, &msg->tsp_time);
#else
		logwtmp("|", "date", "");
		(void)settimeofday(&msg->tsp_time, 0);
		logwtmp("}", "date", "");
#endif /* sgi */
		spreadtime();
	}

	syslog(LOG_NOTICE, "date changed by %s from %s",
	       tname, olddate);
}


/*
 * synchronize all of the slaves
 */
void
E 26
D 6
synch()
E 6
I 6
synch(mydelta)
D 26
long mydelta;
E 26
I 26
	long mydelta;
E 26
E 6
{
D 26
	int i;
E 26
I 26
	struct hosttbl *htp;
E 26
	int measure_status;
D 26
	long netdelta;
	struct timeval tack;
#ifdef MEASURE
#define MAXLINES	8
D 2
	static int lines;
E 2
I 2
	static int lines = 1;
E 2
	struct timeval start, end;
#endif
	int measure();
	int correct();
	long networkdelta();
	char *date();
E 26
I 26
	struct timeval check, stop, wait;
#ifdef sgi
	int pri;
#endif /* sgi */
E 26

D 26
	if (slvcount > 1) {
#ifdef MEASURE
		(void)gettimeofday(&start, (struct timezone *)0);
		if (header == ON || --lines == 0) {
			fprintf(fp, "%s\n", date());
			for (i=0; i<slvcount; i++)
				fprintf(fp, "%.7s\t", hp[i].name);
			fprintf(fp, "\n");
			lines = MAXLINES;
			header = OFF;
		}
#endif
		machup = 1;
		hp[0].delta = 0;
		for(i=1; i<slvcount; i++) {
D 6
			bcopy((char *)&hp[i].addr, 
					(char *)&(server.sin_addr.s_addr), 
					hp[i].length); 
E 6
			tack.tv_sec = 0;
D 9
			tack.tv_usec = 100000;
D 6
			if ((measure_status = measure(&tack, ON)) < 0) {
E 6
I 6
			if ((measure_status = measure(&tack, &hp[i].addr,
			    ON)) < 0) {
E 9
I 9
			tack.tv_usec = 500000;
			if ((measure_status = measure(&tack, &hp[i].addr)) <0) {
E 9
E 6
D 2
				syslog(LOG_ERR, "timed: measure: %m\n");
E 2
I 2
				syslog(LOG_ERR, "measure: %m");
E 2
				exit(1);
E 26
I 26
	if (slvcount > 0) {
		if (trace)
			fprintf(fd, "measurements starting at %s\n", date());
		(void)gettimeofday(&check, 0);
#ifdef sgi
		/* run fast to get good time */
		pri = schedctl(NDPRI,0,NDPHIMIN);
		if (pri < 0)
			syslog(LOG_ERR, "schedctl(): %m");
#endif /* sgi */
		for (htp = self.l_fwd; htp != &self; htp = htp->l_fwd) {
			if (htp->noanswer != 0) {
				measure_status = measure(500, 100,
							 htp->name,
							 &htp->addr,0);
			} else {
				measure_status = measure(3000, 100,
							 htp->name,
							 &htp->addr,0);
E 26
			}
D 26
			hp[i].delta = measure_delta;
			if (measure_status == GOOD)
				machup++;
		}
D 6
		if (machup > 1) {
			netdelta = networkdelta();
			correct(netdelta);
E 6
I 6
		if (status & SLAVE) {
			/* called by a submaster */
			if (trace)
				fprintf(fd, "submaster correct: %d ms.\n",
				    mydelta);
			correct(mydelta);	
		} else {
			if (machup > 1) {
				netdelta = networkdelta();
E 26
I 26
			if (measure_status != GOOD) {
				/* The slave did not respond.  We have
				 * just wasted lots of time on it.
				 */
				htp->delta = HOSTDOWN;
				if (++htp->noanswer >= LOSTHOST) {
					if (trace) {
						fprintf(fd,
					"purging %s for not answering ICMP\n",
							htp->name);
						(void)fflush(fd);
					}
					htp = remmach(htp);
				}
			} else {
				htp->delta = measure_delta;
			}
			(void)gettimeofday(&stop, 0);
			timevalsub(&stop, &stop, &check);
			if (stop.tv_sec >= 1) {
E 26
				if (trace)
D 26
					fprintf(fd,
					    "master correct: %d ms.\n",
					    mydelta);
				correct(netdelta);
E 26
I 26
					(void)fflush(fd);
				/*
				 * ack messages periodically
				 */
				wait.tv_sec = 0;
				wait.tv_usec = 0;
				if (0 != readmsg(TSP_TRACEON,ANYADDR,
						 &wait,0))
					traceon();
				(void)gettimeofday(&check, 0);
E 26
			}
E 6
		}
D 26
#ifdef MEASURE
		gettimeofday(&end, 0);
		end.tv_sec -= start.tv_sec;
		end.tv_usec -= start.tv_usec;
		if (end.tv_usec < 0) {
			end.tv_sec -= 1;
			end.tv_usec += 1000000;
E 26
I 26
#ifdef sgi
		if (pri >= 0)
			(void)schedctl(NDPRI,0,pri);
#endif /* sgi */
		if (trace)
			fprintf(fd, "measurements finished at %s\n", date());
	}
	if (!(status & SLAVE)) {
		if (!dictate) {
			mydelta = networkdelta();
		} else {
			dictate--;
E 26
		}
D 26
		fprintf(fp, "%d ms.\n", (end.tv_sec*1000+end.tv_usec/1000));
D 4
		(void)fflush(fp);
E 4
#endif
		for(i=1; i<slvcount; i++) {
			if (hp[i].delta == HOSTDOWN) {
D 8
				free((char *)hp[i].name);
E 8
I 8
				rmmach(i);
E 8
D 9
				hp[i] = hp[--slvcount];
E 9
#ifdef MEASURE
				header = ON;
#endif
			}
		}
I 6
	} else {
		if (status & SLAVE) {
			correct(mydelta);
		}
E 26
E 6
	}
I 26
	if (trace && (mydelta != 0 || (status & SLAVE)))
		fprintf(fd,"local correction of %ld ms.\n", mydelta);
	correct(mydelta);
E 26
}

/*
D 26
 * 'spreadtime' sends the time to each slave after the master
 * has received the command to set the network time 
E 26
I 26
 * sends the time to each slave after the master
 * has received the command to set the network time
E 26
 */
D 26

E 26
I 26
void
E 26
spreadtime()
{
D 26
	int i;
E 26
I 26
	struct hosttbl *htp;
E 26
D 2
	struct timeval mytime;
E 2
	struct tsp to;
D 26
	struct tsp *answer, *acksend();
E 26
I 26
	struct tsp *answer;
E 26

D 26
	for(i=1; i<slvcount; i++) {
E 26
I 26
/* Do not listen to the consensus after forcing the time.  This is because
 *	the consensus takes a while to reach the time we are dictating.
 */
	dictate = 2;
	for (htp = self.l_fwd; htp != &self; htp = htp->l_fwd) {
E 26
D 6
		bcopy((char *)&hp[i].addr, (char *)&(server.sin_addr.s_addr), 
						hp[i].length); 
E 6
		to.tsp_type = TSP_SETTIME;
D 2
		to.tsp_time.tv_usec = 0;
E 2
		(void)strcpy(to.tsp_name, hostname);
D 2
		(void)gettimeofday(&mytime, (struct timezone *)0);
		to.tsp_time.tv_sec = mytime.tv_sec;
E 2
I 2
D 26
		(void)gettimeofday(&to.tsp_time, (struct timezone *)0);
E 2
D 6
		answer = acksend(&to, hp[i].name, TSP_ACK);
E 6
I 6
		answer = acksend(&to, &hp[i].addr, hp[i].name, TSP_ACK,
		    (struct netinfo *)NULL);
E 6
		if (answer == NULL) {
E 26
I 26
		(void)gettimeofday(&to.tsp_time, 0);
		answer = acksend(&to, &htp->addr, htp->name,
				 TSP_ACK, 0, htp->noanswer);
		if (answer == 0) {
			/* We client does not respond, then we have
			 * just wasted lots of time on it.
			 */
E 26
D 2
			syslog(LOG_ERR, "timed: ERROR ON SETTIME machine: %s\n", hp[i].name);
E 2
I 2
D 13
			syslog(LOG_ERR, "ERROR ON SETTIME machine: %s", hp[i].name);
E 13
I 13
			syslog(LOG_WARNING,
D 26
			    "no reply to SETTIME from: %s", hp[i].name);
E 26
I 26
			       "no reply to SETTIME from %s", htp->name);
			if (++htp->noanswer >= LOSTHOST) {
				if (trace) {
					fprintf(fd,
					     "purging %s for not answering",
						htp->name);
					(void)fflush(fd);
				}
				htp = remmach(htp);
			}
E 26
E 13
E 2
		}
	}
}

D 26
findhost(name)
char *name;
E 26
I 26
void
prthp(delta)
	clock_t delta;
E 26
{
I 26
	static time_t next_time;
	time_t this_time;
	struct tms tm;
	struct hosttbl *htp;
	int length, l;
E 26
	int i;
D 26
	int ind;
E 26

D 26
	ind = -1;
	for (i=1; i<slvcount; i++) {
		if (strcmp(name, hp[i].name) == 0) {
			ind = i;
			break;
E 26
I 26
	if (!fd)			/* quit if tracing already off */
		return;

	this_time = times(&tm);
	if (this_time + delta < next_time)
		return;
	next_time = this_time + CLK_TCK;

	fprintf(fd, "host table: %d entries at %s\n", slvcount, date());
	htp = self.l_fwd;
	length = 1;
	for (i = 1; i <= slvcount; i++, htp = htp->l_fwd) {
		l = strlen(htp->name) + 1;
		if (length+l >= 80) {
			fprintf(fd, "\n");
			length = 0;
E 26
		}
I 26
		length += l;
		fprintf(fd, " %s", htp->name);
E 26
	}
D 26
	return(ind);
E 26
I 26
	fprintf(fd, "\n");
E 26
}

I 26

static struct hosttbl *newhost_hash;
static struct hosttbl *lasthfree = &hosttbl[0];


struct hosttbl *			/* answer or 0 */
findhost(name)
	char *name;
{
	int i, j;
	struct hosttbl *htp;
	char *p;

	j= 0;
	for (p = name, i = 0; i < 8 && *p != '\0'; i++, p++)
		j = (j << 2) ^ *p;
	newhost_hash = &hosttbl[j % NHOSTS];

	htp = newhost_hash;
	if (htp->name[0] == '\0')
		return(0);
	do {
		if (!strcmp(name, htp->name))
			return(htp);
		htp = htp->h_fwd;
	} while (htp != newhost_hash);
	return(0);
}

E 26
/*
D 26
 * 'addmach' adds a host to the list of controlled machines
 * if not already there 
E 26
I 26
 * add a host to the list of controlled machines if not already there
E 26
 */
D 26

D 6
addmach(name)
E 6
I 6
addmach(name, addr)
E 6
char *name;
I 6
struct sockaddr_in *addr;
E 26
I 26
struct hosttbl *
addmach(name, addr, ntp)
	char *name;
	struct sockaddr_in *addr;
	struct netinfo *ntp;
E 26
E 6
{
D 26
	int ret;
	int findhost();
E 26
I 26
	struct hosttbl *ret, *p, *b, *f;
E 26
D 6
	char *malloc();
	struct hostent *hptmp, *gethostbyname();
E 6

	ret = findhost(name);
D 26
	if (ret < 0) {
D 6
		hptmp = gethostbyname(name);
		if (hptmp == NULL) {
D 2
			syslog(LOG_ERR, "timed: gethostbyname: %m\n");
E 2
I 2
			syslog(LOG_ERR, "gethostbyname: %m");
E 2
			exit(1);
		}
		hp[slvcount].length = hptmp->h_length;
		bcopy((char *)hptmp->h_addr, (char *)&hp[slvcount].addr, 
						hptmp->h_length); 
E 6
I 6
		hp[slvcount].addr = *addr;
E 6
D 2
		hp[slvcount].name = (char *)malloc(32);
		(void)strcpy(hp[slvcount].name, hptmp->h_name);
E 2
I 2
		hp[slvcount].name = (char *)malloc(MAXHOSTNAMELEN);
		(void)strcpy(hp[slvcount].name, name);
E 2
		hp[slvcount].seq = 0;
		ret = slvcount;
		if (slvcount < NHOSTS)
			slvcount++;
		else {
E 26
I 26
	if (ret == 0) {
		if (slvcount >= NHOSTS) {
			if (trace) {
				fprintf(fd, "no more slots in host table\n");
				prthp(CLK_TCK);
			}
E 26
D 2
			syslog(LOG_EMERG, "timed: no more slots in host table\n");
E 2
I 2
D 13
			syslog(LOG_ALERT, "no more slots in host table");
E 13
I 13
			syslog(LOG_ERR, "no more slots in host table");
I 26
			Mflag = 0;
			longjmp(jmpenv, 2); /* give up and be a slave */
E 26
E 13
E 2
		}
I 26

		/* if our home hash slot is occupied, find a free entry
		 * in the hash table
		 */
		if (newhost_hash->name[0] != '\0') {
			do {
				ret = lasthfree;
				if (++lasthfree > &hosttbl[NHOSTS])
					lasthfree = &hosttbl[1];
			} while (ret->name[0] != '\0');

			if (!newhost_hash->head) {
				/* Move an interloper using our home.  Use
				 * scratch pointers in case the new head is
				 * pointing to itself.
				 */
				f = newhost_hash->h_fwd;
				b = newhost_hash->h_bak;
				f->h_bak = ret;
				b->h_fwd = ret;
				f = newhost_hash->l_fwd;
				b = newhost_hash->l_bak;
				f->l_bak = ret;
				b->l_fwd = ret;
				bcopy(newhost_hash,ret,sizeof(*ret));
				ret = newhost_hash;
				ret->head = 1;
				ret->h_fwd = ret;
				ret->h_bak = ret;
			} else {
				/* link to an existing chain in our home
				 */
				ret->head = 0;
				p = newhost_hash->h_bak;
				ret->h_fwd = newhost_hash;
				ret->h_bak = p;
				p->h_fwd = ret;
				newhost_hash->h_bak = ret;
			}
		} else {
			ret = newhost_hash;
			ret->head = 1;
			ret->h_fwd = ret;
			ret->h_bak = ret;
		}
		ret->addr = *addr;
		ret->ntp = ntp;
		(void)strncpy(ret->name, name, sizeof(ret->name));
		ret->good = good_host_name(name);
		ret->l_fwd = &self;
		ret->l_bak = self.l_bak;
		self.l_bak->l_fwd = ret;
		self.l_bak = ret;
		slvcount++;

		ret->noanswer = 0;
		ret->need_set = 1;

E 26
	} else {
D 26
		/* need to clear sequence number anyhow */
		hp[ret].seq = 0;
E 26
I 26
		ret->noanswer = (ret->noanswer != 0);
E 26
	}
D 26
#ifdef MEASURE
	header = ON;
#endif
E 26
I 26

	/* need to clear sequence number anyhow */
	ret->seq = 0;
E 26
	return(ret);
}

I 7
/*
I 26
 * remove the machine with the given index in the host table.
 */
struct hosttbl *
remmach(htp)
	struct hosttbl *htp;
{
	struct hosttbl *lprv, *hnxt, *f, *b;

	if (trace)
		fprintf(fd, "remove %s\n", htp->name);

	/* get out of the lists */
	htp->l_fwd->l_bak = lprv = htp->l_bak;
	htp->l_bak->l_fwd = htp->l_fwd;
	htp->h_fwd->h_bak = htp->h_bak;
	htp->h_bak->h_fwd = hnxt = htp->h_fwd;

	/* If we are in the home slot, pull up the chain */
	if (htp->head && hnxt != htp) {
		if (lprv == hnxt)
			lprv = htp;

		/* Use scratch pointers in case the new head is pointing to
		 * itself.
		 */
		f = hnxt->h_fwd;
		b = hnxt->h_bak;
		f->h_bak = htp;
		b->h_fwd = htp;
		f = hnxt->l_fwd;
		b = hnxt->l_bak;
		f->l_bak = htp;
		b->l_fwd = htp;
		hnxt->head = 1;
		bcopy(hnxt, htp, sizeof(*htp));
		lasthfree = hnxt;
	} else {
		lasthfree = htp;
	}

	lasthfree->name[0] = '\0';
	lasthfree->h_fwd = 0;
	lasthfree->l_fwd = 0;
	slvcount--;

	return lprv;
}


/*
E 26
 * Remove all the machines from the host table that exist on the given
 * network.  This is called when a master transitions to a slave on a
 * given network.
 */
D 26

E 26
I 26
void
E 26
rmnetmachs(ntp)
D 26
	register struct netinfo *ntp;
E 26
I 26
	struct netinfo *ntp;
E 26
{
D 26
	int i;
E 26
I 26
	struct hosttbl *htp;
E 26

	if (trace)
D 26
		prthp();
	for (i = 1; i < slvcount; i++)
		if ((hp[i].addr.sin_addr.s_addr & ntp->mask) == ntp->net)
			rmmach(i--);
E 26
I 26
		prthp(CLK_TCK);
	for (htp = self.l_fwd; htp != &self; htp = htp->l_fwd) {
		if (ntp == htp->ntp)
			htp = remmach(htp);
	}
E 26
	if (trace)
D 26
		prthp();
E 26
I 26
		prthp(CLK_TCK);
E 26
}

D 26
/*
 * remove the machine with the given index in the host table.
 */
rmmach(ind)
	int ind;
E 26
I 26
void
masterup(net)
	struct netinfo *net;
E 26
{
D 26
	if (trace)
		fprintf(fd, "rmmach: %s\n", hp[ind].name);
D 8
	if (slvcount-ind-1 > 0)
		bcopy(&hp[ind+1], &hp[ind], (slvcount-ind-1)*sizeof(hp[ind]));
	slvcount--;
E 8
I 8
	free(hp[ind].name);
	hp[ind] = hp[--slvcount];
E 26
I 26
	xmit(TSP_MASTERUP, 0, &net->dest_addr);

	/*
	 * Do not tell new slaves our time for a while.  This ensures
	 * we do not tell them to start using our time, before we have
	 * found a good master.
	 */
	(void)gettimeofday(&net->slvwait, 0);
E 26
E 8
}

E 7
D 26
prthp()
E 26
I 26
void
newslave(msg)
	struct tsp *msg;
E 26
{
D 26
	int i;
E 26
I 26
	struct hosttbl *htp;
	struct tsp *answer, to;
	struct timeval now;
E 26

D 26
	fprintf(fd, "host table:");
	for (i=1; i<slvcount; i++)
		fprintf(fd, " %s", hp[i].name);
	fprintf(fd, "\n");
E 26
I 26
	if (!fromnet || fromnet->status != MASTER)
		return;

	htp = addmach(msg->tsp_name, &from,fromnet);
	htp->seq = msg->tsp_seq;
	if (trace)
		prthp(0);

	/*
	 * If we are stable, send our time to the slave.
	 * Do not go crazy if the date has been changed.
	 */
	(void)gettimeofday(&now, 0);
	if (now.tv_sec >= fromnet->slvwait.tv_sec+3
	    || now.tv_sec < fromnet->slvwait.tv_sec) {
		to.tsp_type = TSP_SETTIME;
		(void)strcpy(to.tsp_name, hostname);
		(void)gettimeofday(&to.tsp_time, 0);
		answer = acksend(&to, &htp->addr,
				 htp->name, TSP_ACK,
				 0, htp->noanswer);
		if (answer) {
			htp->need_set = 0;
		} else {
			syslog(LOG_WARNING,
			       "no reply to initial SETTIME from %s",
			       htp->name);
			htp->noanswer = LOSTHOST;
		}
	}
E 26
}

D 6
masterup()
E 6
I 6
D 26
masterup(net)
struct netinfo *net;
E 26
I 26

/*
 * react to a TSP_QUIT:
 */
void
doquit(msg)
	struct tsp *msg;
E 26
E 6
{
D 26
	struct timeval wait;
D 6
	char *strcpy();
E 6
	struct tsp to, *msg, *readmsg();
E 26
I 26
	if (fromnet->status == MASTER) {
		if (!good_host_name(msg->tsp_name)) {
			if (fromnet->quit_count <= 0) {
				syslog(LOG_NOTICE,"untrusted %s told us QUIT",
				       msg->tsp_name);
				suppress(&from, msg->tsp_name, fromnet);
				fromnet->quit_count = 1;
				return;
			}
			syslog(LOG_NOTICE, "untrusted %s told us QUIT twice",
			       msg->tsp_name);
			fromnet->quit_count = 2;
			fromnet->status = NOMASTER;
		} else {
			fromnet->status = SLAVE;
		}
		rmnetmachs(fromnet);
		longjmp(jmpenv, 2);		/* give up and be a slave */
E 26
I 8
D 15
	int ind;
E 15
E 8

D 26
	to.tsp_type = TSP_MASTERUP;
I 6
	to.tsp_vers = TSPVERSION;
E 6
	(void)strcpy(to.tsp_name, hostname);
I 5
D 6
	bytenetorder(&msg);
E 5
	broadcast(&to);
E 6
I 6
	bytenetorder(&to);
D 25
	if (sendto(sock, (char *)&to, sizeof(struct tsp), 0, &net->dest_addr,
E 25
I 25
	if (sendto(sock, (char *)&to, sizeof(struct tsp), 0,
	    (struct sockaddr *)&net->dest_addr,
E 25
	    sizeof(struct sockaddr_in)) < 0) {
		syslog(LOG_ERR, "sendto: %m");
		exit(1);
E 26
I 26
	} else {
		if (!good_host_name(msg->tsp_name)) {
			syslog(LOG_NOTICE, "untrusted %s told us QUIT",
			       msg->tsp_name);
			fromnet->quit_count = 2;
		}
E 26
	}
I 26
}
E 26
E 6

D 26
	for (;;) {
		wait.tv_sec = 1;
		wait.tv_usec = 0;
D 6
		msg = readmsg(TSP_SLAVEUP, (char *)ANYADDR, &wait);
E 6
I 6
		msg = readmsg(TSP_SLAVEUP, (char *)ANYADDR, &wait, net);
E 6
		if (msg != NULL) {
D 6
			(void) addmach(msg->tsp_name);
E 6
I 6
D 8
			(void) addmach(msg->tsp_name, &from);
E 8
I 8
D 15
			ind = addmach(msg->tsp_name, &from);
E 15
I 15
			(void) addmach(msg->tsp_name, &from);
E 15
E 8
E 6
		} else
			break;
E 26
I 26
void
traceon()
{
	if (!fd) {
		fd = fopen(_PATH_TIMEDLOG, "w");
		if (!fd) {
			trace = 0;
			return;
		}
		fprintf(fd,"Tracing started at %s\n", date());
E 26
I 8
	}
I 26
	trace = 1;
	get_goodgroup(1);
	setstatus();
	prthp(CLK_TCK);
E 26
}

D 26
newslave(ind, seq)
I 16
u_short seq;
E 26
I 26

void
traceoff(msg)
	char *msg;
E 26
E 16
{
D 26
	struct tsp to;
	struct tsp *answer, *acksend();
E 26
I 26
	get_goodgroup(1);
	setstatus();
	prthp(CLK_TCK);
	if (trace) {
		fprintf(fd, msg, date());
		(void)fclose(fd);
		fd = 0;
	}
#ifdef GPROF
	moncontrol(0);
	_mcleanup();
	moncontrol(1);
#endif
	trace = OFF;
}
E 26
D 15
	struct timeval mytime;
E 15

D 26
	if (trace)
		prthp();
	if (seq == 0 || hp[ind].seq !=  seq) {
		hp[ind].seq = seq;
		to.tsp_type = TSP_SETTIME;
		(void)strcpy(to.tsp_name, hostname);
		/*
		 * give the upcoming slave the time
		 * to check its input queue before
		 * setting the time
		 */
		sleep(1);
D 15
		to.tsp_time.tv_usec = 0;
		(void) gettimeofday(&mytime,
E 15
I 15
		(void) gettimeofday(&to.tsp_time,
E 15
		    (struct timezone *)0);
D 15
		to.tsp_time.tv_sec = mytime.tv_sec;
E 15
		answer = acksend(&to, &hp[ind].addr,
		    hp[ind].name, TSP_ACK,
		    (struct netinfo *)NULL);
		if (answer == NULL) {
D 13
			syslog(LOG_ERR,
			    "ERROR ON SETTIME machine: %s",
E 13
I 13
			syslog(LOG_WARNING,
			    "no reply to initial SETTIME from: %s",
E 13
			    hp[ind].name);
			rmmach(ind);
		}
E 26
I 26

#ifdef sgi
void
logwtmp(otime, ntime)
	struct timeval *otime, *ntime;
{
	static struct utmp wtmp[2] = {
		{"","",OTIME_MSG,0,OLD_TIME,0,0,0},
		{"","",NTIME_MSG,0,NEW_TIME,0,0,0}
	};
	static char *wtmpfile = WTMP_FILE;
	int f;

	wtmp[0].ut_time = otime->tv_sec + (otime->tv_usec + 500000) / 1000000;
	wtmp[1].ut_time = ntime->tv_sec + (ntime->tv_usec + 500000) / 1000000;
	if (wtmp[0].ut_time == wtmp[1].ut_time)
		return;

	setutent();
	(void)pututline(&wtmp[0]);
	(void)pututline(&wtmp[1]);
	endutent();
	if ((f = open(wtmpfile, O_WRONLY|O_APPEND)) >= 0) {
		(void) write(f, (char *)wtmp, sizeof(wtmp));
		(void) close(f);
E 26
I 12
D 22
	}
}

char *wtmpfile = "/usr/adm/wtmp";
struct utmp wtmp[2] = {
	{ "|", "", "", 0 },
	{ "{", "", "", 0 }
};

D 17
/*
 * Rounding doesn't work well because new time is always
 * truncated, but oldtime is normally distributed.
 */
E 17
logwtmp(otime, ntime)
struct timeval otime, ntime;
{
	int f;

D 18
	if (otime.tv_sec == ntime.tv_sec)
E 18
I 18
	wtmp[0].ut_time = otime.tv_sec + (otime.tv_usec + 500000) / 1000000;
	wtmp[1].ut_time = ntime.tv_sec + (ntime.tv_usec + 500000) / 1000000;
	if (wtmp[0].ut_time == wtmp[1].ut_time)
E 18
		return;
D 17
	wtmp[0].ut_time = otime.tv_sec; /* +(otime.tv_usec + 500000)/1000000;*/
	wtmp[1].ut_time = ntime.tv_sec; /* +(ntime.tv_usec + 500000)/1000000;*/
E 17
I 17
D 18
	wtmp[0].ut_time = otime.tv_sec; + (otime.tv_usec + 500000) / 1000000;
	wtmp[1].ut_time = ntime.tv_sec; + (ntime.tv_usec + 500000) / 1000000;
E 18
E 17
	if ((f = open(wtmpfile, O_WRONLY|O_APPEND)) >= 0) {
		(void) write(f, (char *)wtmp, sizeof(wtmp));
		(void) close(f);
E 22
E 12
E 8
	}
}
I 26
#endif /* sgi */
E 26
E 1
