h54501
s 00002/00002/00266
d D 8.1 93/06/06 14:09:13 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00229/00101/00039
d D 5.1 93/05/11 11:51:10 bostic 11 10
c new version from Vernon Schryver (vjs@sgi.com); see ../timed/CHANGES for details
e
s 00001/00011/00139
d D 2.6 90/06/01 19:03:21 bostic 10 9
c new copyright notice
e
s 00010/00005/00140
d D 2.5 88/06/18 14:08:13 bostic 9 8
c install approved copyright notice
e
s 00009/00003/00136
d D 2.4 87/12/23 14:30:07 bostic 8 7
c append Berkeley header; NASA wants a copy
e
s 00001/00002/00138
d D 2.3 86/05/28 09:40:53 bloom 7 6
c finish up for Mike
e
s 00027/00010/00113
d D 2.2 86/05/27 15:35:02 karels 6 5
c use settimeofday if it's too large a change
e
s 00002/00009/00121
d D 2.1 85/12/10 13:06:49 bloom 5 4
c Multi network support
e
s 00000/00001/00130
d D 1.4 85/11/16 18:32:12 bloom 4 3
c use line buffering for traces instead of explicit calls to fflush
e
s 00002/00001/00129
d D 1.3 85/09/18 19:43:23 bloom 3 2
c fix syslog messages
e
s 00001/00001/00129
d D 1.2 85/09/17 21:04:38 eric 2 1
c facilities in syslog
e
s 00130/00000/00000
d D 1.1 85/06/22 22:07:51 gusella 1 0
c date and time created 85/06/22 22:07:51 by gusella
e
u
U
t
T
I 1
D 11
/*
D 6
 * Copyright (c) 1983 Regents of the University of California.
E 6
I 6
 * Copyright (c) 1985 Regents of the University of California.
E 11
I 11
/*-
D 12
 * Copyright (c) 1985, 1993 The Regents of the University of California.
E 11
E 6
D 8
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
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

I 11
#ifdef sgi
#ident "$Revision: 1.16 $"
#endif

E 11
#include "globals.h"
D 11
#include <protocols/timed.h>
E 11
I 11
#include <math.h>
#include <sys/types.h>
#include <sys/times.h>
#ifdef sgi
#include <sys/syssgi.h>
#endif /* sgi */
E 11

D 5
extern int slvcount;
extern struct host hp[];
extern char hostname[];
extern struct sockaddr_in server;
E 5
D 11
#ifdef MEASURE
extern FILE *fp;
#endif
E 11
I 11
static void adjclock __P((struct timeval *));
E 11

D 11
/* 
 * `correct' sends to the slaves the corrections for their clocks
E 11
I 11
/*
 * sends to the slaves the corrections for their clocks after fixing our
 * own
E 11
 */
D 11

E 11
I 11
void
E 11
correct(avdelta)
D 11
long avdelta;
E 11
I 11
	long avdelta;
E 11
{
D 11
	int i;
E 11
I 11
	struct hosttbl *htp;
E 11
	int corr;
D 5
	char *strcpy();
E 5
	struct timeval adjlocal;
D 11
	struct tsp msgs;
	struct timeval mstotvround();
	struct tsp *answer, *acksend();
E 11
I 11
	struct tsp to;
	struct tsp *answer;
E 11

D 11
#ifdef MEASURE
	for(i=0; i<slvcount; i++) {
		if (hp[i].delta == HOSTDOWN)
			fprintf(fp, "%s\t", "down");
		else { 
			fprintf(fp, "%d\t", hp[i].delta);
		}
	}
	fprintf(fp, "\n");
#endif
	corr = avdelta - hp[0].delta;
	adjlocal = mstotvround(&corr);
	adjclock(&adjlocal);
#ifdef MEASURE
	fprintf(fp, "%d\t", corr);
#endif
E 11
I 11
	mstotvround(&adjlocal, avdelta);
E 11

D 11
	for(i=1; i<slvcount; i++) {
		if (hp[i].delta != HOSTDOWN)  {
D 5
			bcopy((char *)&hp[i].addr, 
					(char *)&(server.sin_addr.s_addr),
						hp[i].length);
E 5
			corr = avdelta - hp[i].delta;
			msgs.tsp_time = mstotvround(&corr);
			msgs.tsp_type = (u_char)TSP_ADJTIME;
			(void)strcpy(msgs.tsp_name, hostname);
D 5
			answer = acksend(&msgs, hp[i].name, TSP_ACK);
E 5
I 5
			answer = acksend(&msgs, &hp[i].addr, hp[i].name,
			    TSP_ACK, (struct netinfo *)NULL);
E 5
			if (answer == NULL) {
				hp[i].delta = HOSTDOWN;
#ifdef MEASURE
				fprintf(fp, "%s\t", "down");
E 11
I 11
	for (htp = self.l_fwd; htp != &self; htp = htp->l_fwd) {
		if (htp->delta != HOSTDOWN)  {
			corr = avdelta - htp->delta;
/* If the other machine is off in the weeds, set its time directly.
 *	If a slave gets the wrong day, the original code would simply
 *	fix the minutes.  If you fix a network partition, you can get
 *	into such situations.
 */
			if (htp->need_set
			    || corr >= MAXADJ*1000
			    || corr <= -MAXADJ*1000) {
				htp->need_set = 0;
				(void)gettimeofday(&to.tsp_time,0);
				timevaladd(&to.tsp_time, &adjlocal);
				to.tsp_type = TSP_SETTIME;
E 11
			} else {
D 11
				fprintf(fp, "%d\t", corr);
#endif
E 11
I 11
				mstotvround(&to.tsp_time, corr);
				to.tsp_type = TSP_ADJTIME;
E 11
			}
D 11
		} else {
#ifdef MEASURE
			fprintf(fp, "%s\t", "down");
#endif
E 11
I 11
			(void)strcpy(to.tsp_name, hostname);
			answer = acksend(&to, &htp->addr, htp->name,
					 TSP_ACK, 0, 0);
			if (!answer) {
				htp->delta = HOSTDOWN;
				syslog(LOG_WARNING,
				       "no reply to time correction from %s",
				       htp->name);
				if (++htp->noanswer >= LOSTHOST) {
					if (trace) {
						fprintf(fd,
					     "purging %s for not answering\n",
							htp->name);
						(void)fflush(fd);
					}
					htp = remmach(htp);
				}
			}
E 11
		}
	}
D 11
#ifdef MEASURE
	fprintf(fp, "\n");
D 4
	(void)fflush(fp);
E 4
#endif
}
E 11

D 11
/* 
 * `mstotvround' rounds up the value of the argument to the 
 * nearest multiple of five, and converts it into a timeval 
 */
 
struct timeval mstotvround(x)
int *x;
{
	int temp;
	struct timeval adj;

	temp = *x % 5;
	if (temp >= 3)
		*x = *x-temp+5;
	else {
		if (temp <= -3)
			*x = *x - temp -5;
		else 
			*x = *x-temp;
	}
	adj.tv_sec = *x/1000;
	adj.tv_usec = (*x-adj.tv_sec*1000)*1000;
	if (adj.tv_usec < 0) {
		adj.tv_usec += 1000000;
		adj.tv_sec--;
	}
	return(adj);
E 11
I 11
	/*
	 * adjust our own clock now that we are not sending it out
	 */
	adjclock(&adjlocal);
E 11
}

I 11

static void
E 11
adjclock(corr)
D 11
struct timeval *corr;
E 11
I 11
	struct timeval *corr;
E 11
{
I 11
	static int passes = 0;
	static int smoother = 0;
	long delta;			/* adjustment in usec */
	long ndelta;
E 11
I 6
	struct timeval now;
I 11
	struct timeval adj;
E 11

E 6
D 11
	if (timerisset(corr)) {
D 6
		if (corr->tv_sec < SAMPLEINTVL/10 && 
					corr->tv_sec > - SAMPLEINTVL/10) {
E 6
I 6
D 7
		if (corr->tv_sec < MAXADJ && corr->tv_sec > - MAXADJ)
E 7
I 7
		if (corr->tv_sec < MAXADJ && corr->tv_sec > - MAXADJ) {
E 7
E 6
			(void)adjtime(corr, (struct timeval *)0);
		} else {
E 11
I 11
	if (!timerisset(corr))
		return;

	adj = *corr;
	if (adj.tv_sec < MAXADJ && adj.tv_sec > - MAXADJ) {
		delta = adj.tv_sec*1000000 + adj.tv_usec;
		/* If the correction is less than the minimum round
		 *	trip time for an ICMP packet, and thus
		 *	less than the likely error in the measurement,
		 *	do not do the entire correction.  Do half
		 *	or a quarter of it.
		 */

		if (delta > -MIN_ROUND*1000
		    && delta < MIN_ROUND*1000) {
			if (smoother <= 4)
				smoother++;
			ndelta = delta >> smoother;
			if (trace)
				fprintf(fd,
					"trimming delta %ld usec to %ld\n",
					delta, ndelta);
			adj.tv_usec = ndelta;
			adj.tv_sec = 0;
		} else if (smoother > 0) {
			smoother--;
		}
		if (0 > adjtime(corr, 0)) {
			syslog(LOG_ERR, "adjtime: %m");
		}
		if (passes > 1
		    && (delta < -BIG_ADJ || delta > BIG_ADJ)) {
			smoother = 0;
			passes = 0;
E 11
D 6
			corr->tv_usec = 0;
			if (corr->tv_sec > 0)
				corr->tv_sec = SAMPLEINTVL/10 - 2;
			else
				corr->tv_sec = - SAMPLEINTVL/10 + 2;
			(void)adjtime(corr, (struct timeval *)0);
E 6
D 2
			syslog(LOG_WARNING, "timed: adjclock called with too large a parameter\n");
E 2
I 2
D 3
			syslog(LOG_WARNING, "timed: adjclock called with too large a parameter");
E 3
I 3
			syslog(LOG_WARNING,
D 6
			    "adjclock called with too large a parameter");
E 6
I 6
D 11
			    "clock correction too large to adjust (%d sec)",
			    corr->tv_sec);
			(void) gettimeofday(&now, (struct timezone *)0);
			timevaladd(&now, corr);
			if (settimeofday(&now, (struct timezone *)0) < 0)
				syslog(LOG_ERR, "can't set time");
E 11
I 11
			       "large time adjustment of %+.3f sec",
			       delta/1000000.0);
E 11
E 6
E 3
E 2
		}
I 11
	} else {
		syslog(LOG_WARNING,
		       "clock correction %d sec too large to adjust",
		       adj.tv_sec);
		(void) gettimeofday(&now, 0);
		timevaladd(&now, corr);
		if (settimeofday(&now, 0) < 0)
			syslog(LOG_ERR, "settimeofday: %m");
E 11
I 6
D 7
		first = 0;
E 7
	}
I 11

#ifdef sgi
	/* Accumulate the total change, and use it to adjust the basic
	 * clock rate.
	 */
	if (++passes > 2) {
#define F_USEC_PER_SEC	(1000000*1.0)	/* reduce typos */
#define F_NSEC_PER_SEC	(F_USEC_PER_SEC*1000.0)

		extern char *timetrim_fn;
		extern char *timetrim_wpat;
		extern long timetrim;
		extern double tot_adj, hr_adj;	/* totals in nsec */
		extern double tot_ticks, hr_ticks;

		static double nag_tick;
		double cur_ticks, hr_delta_ticks, tot_delta_ticks;
		double tru_tot_adj, tru_hr_adj; /* nsecs of adjustment */
		double tot_trim, hr_trim;   /* nsec/sec */
		struct tms tm;
		FILE *timetrim_st;

		cur_ticks = times(&tm);
		tot_adj += delta*1000.0;
		hr_adj += delta*1000.0;

		tot_delta_ticks = cur_ticks-tot_ticks;
		if (tot_delta_ticks >= 16*SECDAY*CLK_TCK) {
			tot_adj -= rint(tot_adj/16);
			tot_ticks += rint(tot_delta_ticks/16);
			tot_delta_ticks = cur_ticks-tot_ticks;
		}
		hr_delta_ticks = cur_ticks-hr_ticks;

		tru_hr_adj = hr_adj + timetrim*rint(hr_delta_ticks/CLK_TCK);
		tru_tot_adj = (tot_adj
			       + timetrim*rint(tot_delta_ticks/CLK_TCK));

		if (hr_delta_ticks >= SECDAY*CLK_TCK
		    || (tot_delta_ticks < 4*SECDAY*CLK_TCK
			&& hr_delta_ticks >= SECHR*CLK_TCK)
		    || (trace && hr_delta_ticks >= (SECHR/10)*CLK_TCK)) {

			tot_trim = rint(tru_tot_adj*CLK_TCK/tot_delta_ticks);
			hr_trim = rint(tru_hr_adj*CLK_TCK/hr_delta_ticks);

			if (trace
			    || (abs(timetrim - hr_trim) > 100000.0
				&& 0 == timetrim_fn
				&& ((cur_ticks - nag_tick)
				    >= 24*SECDAY*CLK_TCK))) {
				nag_tick = cur_ticks;
				syslog(LOG_NOTICE,
		   "%+.3f/%.2f or %+.3f/%.2f sec/hr; timetrim=%+.0f or %+.0f",
				       tru_tot_adj/F_NSEC_PER_SEC,
				       tot_delta_ticks/(SECHR*CLK_TCK*1.0),
				       tru_hr_adj/F_NSEC_PER_SEC,
				       hr_delta_ticks/(SECHR*CLK_TCK*1.0),
				       tot_trim,
				       hr_trim);
			}

			if (tot_trim < -MAX_TRIM || tot_trim > MAX_TRIM) {
				tot_ticks = hr_ticks;
				tot_adj = hr_adj;
			} else if (0 > syssgi(SGI_SETTIMETRIM,
					      (long)tot_trim)) {
				syslog(LOG_ERR, "SETTIMETRIM(%d): %m",
				       (long)tot_trim);
			} else {
				if (0 != timetrim_fn) {
				    timetrim_st = fopen(timetrim_fn, "w");
				    if (0 == timetrim_st) {
					syslog(LOG_ERR, "fopen(%s): %m",
					       timetrim_fn);
				    } else {
					if (0 > fprintf(timetrim_st,
							timetrim_wpat,
							(long)tot_trim,
							tru_tot_adj,
							tot_delta_ticks)) {
						syslog(LOG_ERR,
						       "fprintf(%s): %m",
						       timetrim_fn);
					}
					(void)fclose(timetrim_st);
				    }
				}

				tot_adj -= ((tot_trim - timetrim)
					    * rint(tot_delta_ticks/CLK_TCK));
				timetrim = tot_trim;
			}

			hr_ticks = cur_ticks;
			hr_adj = 0;
		}
	}
#endif /* sgi */
E 11
}

D 11
timevaladd(tv1, tv2)
	register struct timeval *tv1, *tv2;
E 11
I 11

/* adjust the time in a message by the time it
 *	spent in the queue
 */
void
adj_msg_time(msg, now)
	struct tsp *msg;
	struct timeval *now;
E 11
{
D 11
	
	tv1->tv_sec += tv2->tv_sec;
	tv1->tv_usec += tv2->tv_usec;
	if (tv1->tv_usec >= 1000000) {
		tv1->tv_sec++;
		tv1->tv_usec -= 1000000;
E 11
I 11
	msg->tsp_time.tv_sec += (now->tv_sec - from_when.tv_sec);
	msg->tsp_time.tv_usec += (now->tv_usec - from_when.tv_usec);

	while (msg->tsp_time.tv_usec < 0) {
		msg->tsp_time.tv_sec--;
		msg->tsp_time.tv_usec += 1000000;
E 11
	}
D 11
	if (tv1->tv_usec < 0) {
		tv1->tv_sec--;
		tv1->tv_usec += 1000000;
E 11
I 11
	while (msg->tsp_time.tv_usec >= 1000000) {
		msg->tsp_time.tv_sec++;
		msg->tsp_time.tv_usec -= 1000000;
E 11
E 6
	}
}
E 1
