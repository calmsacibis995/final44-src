h24939
s 00002/00002/00158
d D 8.1 93/06/06 14:09:22 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00112/00042/00048
d D 5.1 93/05/11 11:51:10 bostic 10 9
c new version from Vernon Schryver (vjs@sgi.com); see ../timed/CHANGES for details
e
s 00001/00011/00089
d D 2.7 90/06/01 19:03:29 bostic 9 8
c new copyright notice
e
s 00010/00005/00090
d D 2.6 88/06/18 14:08:14 bostic 8 7
c install approved copyright notice
e
s 00010/00004/00085
d D 2.5 87/12/23 14:30:08 bostic 7 6
c append Berkeley header; NASA wants a copy
e
s 00019/00010/00070
d D 2.4 86/05/27 15:34:12 karels 6 5
c add MAXADJ, and some comments
e
s 00001/00001/00079
d D 2.3 86/04/21 15:16:14 bloom 5 4
c increase TRIALS since algorithm has been rewritten
e
s 00005/00000/00075
d D 2.2 86/04/11 18:16:16 bloom 4 3
c major work on multiple network code (Kirk Smith, ks@ef.purdue.edu)
e
s 00026/00003/00049
d D 2.1 85/12/10 13:06:53 bloom 3 2
c Multi network support
e
s 00021/00001/00031
d D 1.2 85/09/18 19:34:18 bloom 2 1
c shuffle constants between files, move host structure from timed.h, add some
c global vars
e
s 00032/00000/00000
d D 1.1 85/06/22 22:07:52 gusella 1 0
c date and time created 85/06/22 22:07:52 by gusella
e
u
U
t
T
I 1
D 10
/*
 * Copyright (c) 1983 Regents of the University of California.
E 10
I 10
/*-
D 11
 * Copyright (c) 1985 The Regents of the University of California.
E 10
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 9
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 8
 *
 *	%W% (Berkeley) %G%
E 7
 */
D 7

/*	%W%	(Berkeley)	%G%	*/
E 7

I 10
#ifdef sgi
#ident "$Revision: 1.15 $"
#endif

E 10
D 2
#include <sys/types.h>
E 2
I 2
#include <sys/param.h>
E 2
D 10
#include <stdio.h>
E 10
#include <sys/time.h>
D 10
#include <errno.h>
#include <syslog.h>
E 10
#include <sys/socket.h>
I 10

E 10
#include <netinet/in.h>
D 10
#include <netdb.h>
E 10
#include <arpa/inet.h>

I 10
#include <errno.h>
#include <limits.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <syslog.h>
#include <unistd.h>

#include <protocols/timed.h>
#ifdef sgi
#include <bstring.h>
#include <sys/clock.h>
/* use the constant HZ instead of the function CLK_TCK */
#undef CLK_TCK
#define CLK_TCK HZ
#else
#define	SECHR	(60*60)
#define	SECDAY	(24*SECHR)
#endif /* sgi */

E 10
extern int errno;
I 3
extern int sock;
E 3

D 6
#define RANGE		20
#define MSGS 		5
D 5
#define TRIALS		6
E 5
I 5
#define TRIALS		10
E 5
#define SAMPLEINTVL	240	
#define MAXSEQ 		30000
E 6
I 6
D 10
#define SAMPLEINTVL	240		/* synch() freq for master, sec */
#define	MAXADJ		20		/* max correction (sec) for adjtime */
/*
 * Parameters for network time measurement
 * of each host using ICMP timestamp requests.
E 10
I 10
/* Best expected round trip for a measurement.
 * This is essentially the number of milliseconds per CPU tick (CLK_TCK?).
 * All delays shorter than this are usually reported as 0.
E 10
 */
D 10
#define RANGE		20		/* best expected round-trip time, ms */
#define MSGS 		5		/* # of timestamp replies to average */
#define TRIALS		10		/* max # of timestamp echos sent */
E 10
I 10
#define MIN_ROUND ((1000-1)/CLK_TCK)
E 10

E 6
D 10
#define MINTOUT		360
E 10
I 10

#define SAMPLEINTVL	240		/* synch() freq for master in sec */
#define	MAXADJ		20		/* max adjtime() correction in sec */

#define MAX_TRIM	3000000		/* max drift in nsec/sec, 0.3% */
#define BIG_ADJ		(MAX_TRIM/1000*SAMPLEINTVL*2)	/* max good adj */

#define MINTOUT		360		/* election delays, 6-15 minutes */
E 10
#define MAXTOUT		900

I 10
#define BAD_STATUS	(-1)
E 10
#define GOOD		1
#define UNREACHABLE	2
#define NONSTDTIME	3
D 10
#define HOSTDOWN 	0x7fffffff
E 10
I 10
#define HOSTDOWN	0x7fffffff
E 10
I 2

D 10
#define OFF	0
#define ON	1
E 10
I 10
#define OFF		0
#define ON		1
E 10

I 10
#define MAX_HOPCNT	10		/* max value for tsp_hpcnt */

#define LOSTHOST	3		/* forget after this many failures */

#define VALID_RANGE (MAXADJ*1000)	/* good times in milliseconds */
#define GOOD_RANGE (MIN_ROUND*2)
#define VGOOD_RANGE (MIN_ROUND-1)


E 10
D 6
#define SLAVE 	1
#define MASTER	2
#define IGNORE	4
#define ALL	(SLAVE|MASTER|IGNORE)
E 6
I 6
/*
 * Global and per-network states.
 */
D 10
#define NOMASTER 	0		/* no master on any network */
#define SLAVE 		1
E 10
I 10
#define NOMASTER	0		/* no good master */
#define SLAVE		1
E 10
#define MASTER		2
#define IGNORE		4
#define ALL		(SLAVE|MASTER|IGNORE)
E 6
I 3
#define SUBMASTER	(SLAVE|MASTER)
E 3

D 6
#define NHOSTS		30	/* max number of hosts controlled by timed */
E 6
I 6
D 10
#define NHOSTS		100	/* max number of hosts controlled by timed */
E 6

struct host {
	char *name;
D 3
	char *addr;
	int length;
E 3
I 3
	struct sockaddr_in addr;
E 3
	long delta;
E 10
I 10
#define NHOSTS		1013		/* max of hosts controlled by timed
					 * This must be a prime number.
					 */
struct hosttbl {
	struct	hosttbl *h_bak;		/* hash chain */
	struct	hosttbl *h_fwd;
	struct  hosttbl *l_bak;		/* "sequential" list */
	struct  hosttbl *l_fwd;
	struct	netinfo *ntp;
	struct	sockaddr_in addr;
	char	name[MAXHOSTNAMELEN+1];
	u_char	head;			/* 1=head of hash chain */
	u_char	good;			/* 0=trusted host, for averaging */
	u_char	noanswer;		/* count of failures to answer */
	u_char	need_set;		/* need a SETTIME */
E 10
	u_short seq;
I 10
	long	delta;
E 10
};

I 10
/* closed hash table with internal chaining */
extern struct hosttbl hosttbl[NHOSTS+1];
#define self hosttbl[0]
#define hostname (self.name)


E 10
D 3
u_long	mynet, netmask;
E 3
I 3
struct netinfo {
D 10
	struct netinfo *next;
	u_long net;
	u_long mask;
	struct in_addr my_addr;
	struct sockaddr_in dest_addr;	/* broadcast addr or point-point */
	long status;
E 10
I 10
	struct	netinfo *next;
	struct	in_addr net;
	u_long	mask;
	struct	in_addr my_addr;
	struct	sockaddr_in dest_addr;	/* broadcast addr or point-point */
	long	status;
	struct timeval slvwait;		/* delay before sending our time */
	int	quit_count;		/* recent QUITs */
E 10
};

I 10
#include "extern.h"

#define tvtomsround(tv) ((tv).tv_sec*1000 + ((tv).tv_usec + 500)/1000)

E 10
extern struct netinfo *nettab;
extern int status;
extern int trace;
extern int sock;
extern struct sockaddr_in from;
I 10
extern struct timeval from_when;	/* when the last msg arrived */
extern u_short sequence;		/* TSP message sequence number */
E 10
I 4
extern struct netinfo *fromnet, *slavenet;
E 4
extern FILE *fd;
D 10
extern char hostname[];
extern char tracefile[];
extern struct host hp[];
extern int backoff;
E 10
extern long delay1, delay2;
D 10
extern int slvcount;
I 4
extern int nslavenets;		/* Number of nets were I could be a slave */
extern int nmasternets;		/* Number of nets were I could be a master */
extern int nignorednets;	/* Number of ignored nets */
extern int nnets;		/* Number of nets I am connected to */
E 10
I 10
extern int nslavenets;			/* nets were I could be a slave */
extern int nmasternets;			/* nets were I could be a master */
extern int nignorednets;		/* ignored nets */
extern int nnets;			/* nets I am connected to */
E 10
E 4

D 10
char *strcpy(), *malloc();
E 10
I 10

#define trace_msg(msg)		{if (trace) fprintf(fd, msg);}

#define trace_sendto_err(addr) {					\
	int st_errno = errno;						\
	syslog(LOG_ERR, "%s %d: sendto %s: %m",				\
		__FILE__, __LINE__, inet_ntoa(addr));			\
	if (trace)							\
		fprintf(fd, "%s %d: sendto %s: %d", __FILE__, __LINE__,	\
			inet_ntoa(addr), st_errno);			\
}


# define max(a,b) 	(a<b ? b : a)
# define min(a,b) 	(a>b ? b : a)
# define abs(x)		(x>=0 ? x : -(x))
E 10
E 3
E 2
E 1
