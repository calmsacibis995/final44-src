/*
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1985 Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "globals.h"
#define TSPTYPES
#include <protocols/timed.h>
#include <net/if.h>
#include <net/if_dl.h>
#include <net/route.h>
#include <arpa/inet.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <setjmp.h>
#include "pathnames.h"

int id;
int trace;
int sock, sock_raw = -1;
int status = 0;
int backoff;
int slvcount;				/* no. of slaves controlled by master */
int machup;
int nflag;
int iflag;
u_short sequence;			/* sequence number */
struct sockaddr_in server;
long delay1;
long delay2;
long random();
char *ifa_walk();
void configure();
char hostname[MAXHOSTNAMELEN];
struct host hp[NHOSTS];
char tracefile[] = _PATH_TIMEDLOG;
FILE *fd;
jmp_buf jmpenv;
struct netinfo *nettab = NULL;
static struct netinfo **ntpp = &nettab;
int nslavenets;		/* Number of networks were I could be a slave */
int nmasternets;	/* Number of networks were I could be a master */
int nignorednets;	/* Number of ignored networks */
int nnets;		/* Number of networks I am connected to */
struct netinfo *slavenet;
struct netinfo *firstslavenet();
int Mflag;
int justquit = 0;

struct nets {
	char *name;
	long net;
	struct nets *next;
} *nets = (struct nets *)0;

/*
 * The timedaemons synchronize the clocks of hosts in a local area network.
 * One daemon runs as master, all the others as slaves. The master
 * performs the task of computing clock differences and sends correction
 * values to the slaves. 
 * Slaves start an election to choose a new master when the latter disappears 
 * because of a machine crash, network partition, or when killed.
 * A resolution protocol is used to kill all but one of the masters
 * that happen to exist in segments of a partitioned network when the 
 * network partition is fixed.
 *
 * Authors: Riccardo Gusella & Stefano Zatti
 */
void
configure(ifam, ifm, info, walk_arg)
	struct ifa_msghdr *ifam;
	struct if_msghdr *ifm;
	register struct rt_addrinfo *info;
	void *walk_arg;
{
	register struct sockaddr_in *sin;
	register struct netinfo *ntp;
	int flags = ifm->ifm_flags;
	u_long my_mask, my_addr;

	if ((flags & IFF_UP) == 0 ||
		(flags & (IFF_POINTOPOINT | IFF_BROADCAST)) == 0)
		return;
	sin = (struct sockaddr_in *)info->rti_info[RTAX_IFA];
	if (sin == NULL || sin->sin_family != AF_INET)
		return;
	my_addr = sin->sin_addr.s_addr;
	sin = (struct sockaddr_in *)info->rti_info[RTAX_NETMASK];
	if (sin == 0) {
		syslog(LOG_ERR, "get netmask: %m");
		return;
	}
	my_mask = sin->sin_addr.s_addr;
	sin = (struct sockaddr_in *)info->rti_info[RTAX_BRD];
	if (sin == 0) {
		syslog(LOG_ERR, "no dst or broadcast addr: %m");
		return;
	}
	if (nflag || iflag) {
		u_long	addr, mask;
		struct	nets *n;

		addr = ntohl(sin->sin_addr.s_addr);
		for (mask = ntohl(my_mask); mask && !(mask & 1); mask >>= 1)
			addr >>= 1;
		for (n = nets ; n; n = n->next)
			if (addr == n->net)
				break;
		if (nflag && !n || iflag && n)
			return;
	}
	if (ntp = (struct netinfo *)malloc(sizeof(struct netinfo))) {
		ntp->my_addr.s_addr = my_addr;
		ntp->mask = my_mask;
		ntp->dest_addr.sin_port = server.sin_port;
		ntp->dest_addr = *sin;
		ntp->net = my_mask & sin->sin_addr.s_addr;
		ntp->next = NULL;
		*ntpp = ntp;
		ntpp = &(ntp->next);
	}
}

main(argc, argv)
int argc;
char **argv;
{
	int on;
	int ret;
	long seed;
	struct timeval time;
	struct servent *srvp;
	long casual();
	char *date();
	int n;
	int flag;
	register struct netinfo *ntp;
	struct netinfo *savefromnet;
	uid_t getuid();

	Mflag = 0;
	on = 1;
	backoff = 1;
	trace = OFF;
	nflag = OFF;
	iflag = OFF;
	openlog("timed", LOG_CONS|LOG_PID, LOG_DAEMON);

	if (getuid() != 0) {
		fprintf(stderr, "Timed: not superuser\n");
		exit(1);
	}

	while (--argc > 0 && **++argv == '-') {
		(*argv)++;
		do {
			switch (**argv) {

			case 'M':
				Mflag = 1; 
				break;
			case 't':
				trace = ON; 
				break;
			case 'n':
				argc--, argv++;
				if (iflag) {
					fprintf(stderr,
				    "timed: -i and -n make no sense together\n");
				} else {
					nflag = ON;
					addnetname(*argv);
				}
				while (*(++(*argv)+1)) ;
				break;
			case 'i':
				argc--, argv++;
				if (nflag) {
					fprintf(stderr,
				    "timed: -i and -n make no sense together\n");
				} else {
					iflag = ON;
					addnetname(*argv);
				}
				while (*(++(*argv)+1)) ;
				break;
			default:
				fprintf(stderr, "timed: -%c: unknown option\n", 
							**argv);
				break;
			}
		} while (*++(*argv));
	}

#ifndef DEBUG
	daemon(0, 0);
#endif

	if (trace == ON) {
		fd = fopen(tracefile, "w");
		setlinebuf(fd);
		fprintf(fd, "Tracing started on: %s\n\n", 
					date());
	}

	srvp = getservbyname("timed", "udp");
	if (srvp == 0) {
		syslog(LOG_CRIT, "unknown service 'timed/udp'");
		exit(1);
	}
	server.sin_port = srvp->s_port;
	server.sin_family = AF_INET;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		syslog(LOG_ERR, "socket: %m");
		exit(1);
	}
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&on, 
							sizeof(on)) < 0) {
		syslog(LOG_ERR, "setsockopt: %m");
		exit(1);
	}
	if (bind(sock, (struct sockaddr *)&server, sizeof(server))) {
		if (errno == EADDRINUSE)
		        syslog(LOG_ERR, "server already running");
		else
		        syslog(LOG_ERR, "bind: %m");
		exit(1);
	}

	/* choose a unique seed for random number generation */
	(void)gettimeofday(&time, (struct timezone *)0);
	seed = time.tv_sec + time.tv_usec;
	srandom(seed);

	sequence = random();     /* initial seq number */

	/* rounds kernel variable time to multiple of 5 ms. */
	time.tv_sec = 0;
	time.tv_usec = -((time.tv_usec/1000) % 5) * 1000;
	(void)adjtime(&time, (struct timeval *)0);

	id = getpid();

	if (gethostname(hostname, sizeof(hostname) - 1) < 0) {
		syslog(LOG_ERR, "gethostname: %m");
		exit(1);
	}
	hp[0].name = hostname;

	if (nflag || iflag) {
		struct netent *getnetent();
		struct netent *n;
		struct nets *np;
		for ( np = nets ; np ; np = np->next) {
			n = getnetbyname(np->name);
			if (n == NULL) {
				syslog(LOG_ERR, "getnetbyname: unknown net %s",
					np->name);
				exit(1);
			}
			np->net = n->n_net;
		}
	}

	ifa_walk(configure, (void *)0);

	if (nettab == NULL) {
		syslog(LOG_ERR, "No network usable");
		exit(1);
	}

	for (ntp = nettab; ntp != NULL; ntp = ntp->next)
		lookformaster(ntp);
	setstatus();
	/*
	 * Take care of some basic initialization.
	 */
	/* us. delay to be used in response to broadcast */
	delay1 = casual((long)10000, 200000);	

	/* election timer delay in secs. */
	delay2 = casual((long)MINTOUT, (long)MAXTOUT);

	if (Mflag) {
		/*
		 * number (increased by 1) of slaves controlled by master: 
		 * used in master.c, candidate.c, networkdelta.c, and 
		 * correct.c 
		 */
		slvcount = 1;
		ret = setjmp(jmpenv);

		switch (ret) {

		case 0: 
			makeslave(firstslavenet());
			setstatus();
			break;
		case 1: 
			/* Just lost our master */
			setstatus();
			slavenet->status = election(slavenet);
			checkignorednets();
			setstatus();
			if (slavenet->status == MASTER)
				makeslave(firstslavenet());
			else
				makeslave(slavenet);
			setstatus();
			break;
		case 2:
			/* Just been told to quit */
			fromnet->status = SLAVE;
			setstatus();
			savefromnet = fromnet;
			rmnetmachs(fromnet);
			checkignorednets();
			if (slavenet)
				makeslave(slavenet);
			else
				makeslave(savefromnet);
			setstatus();
			justquit = 1;
			break;
			
		default:
			/* this should not happen */
			syslog(LOG_ERR, "Attempt to enter invalid state");
			break;
		}
			
		if (status & MASTER) {
			/* open raw socket used to measure time differences */
			if (sock_raw == -1) {
			    sock_raw = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP); 
			    if (sock_raw < 0)  {
				    syslog(LOG_ERR, "opening raw socket: %m");
				    exit (1);
			    }
			}
		} else {
			/* sock_raw is not being used now */
			if (sock_raw != -1) {
			    (void)close(sock_raw);
			    sock_raw = -1;
			}
		}

		if (status == MASTER) 
			master();
		else 
			slave();
	} else {
		/* if Mflag is not set timedaemon is forced to act as a slave */
		status = SLAVE;
		if (setjmp(jmpenv)) {
			setstatus();
			checkignorednets();
		}
		makeslave(firstslavenet());
		for (ntp = nettab; ntp != NULL; ntp = ntp->next)
			if (ntp->status == MASTER)
				ntp->status = IGNORE;
		setstatus();
		slave();
	}
}

/*
 * Try to become master over ignored nets..
 */
checkignorednets()
{
	register struct netinfo *ntp;
	for (ntp = nettab; ntp != NULL; ntp = ntp->next)
		if (ntp->status == IGNORE)
			lookformaster(ntp);
}

lookformaster(ntp)
	register struct netinfo *ntp;
{
	struct tsp resp, conflict, *answer, *readmsg(), *acksend();
	struct timeval time;
	char mastername[MAXHOSTNAMELEN];
	struct sockaddr_in masteraddr;

	ntp->status = SLAVE;
	/* look for master */
	resp.tsp_type = TSP_MASTERREQ;
	(void)strcpy(resp.tsp_name, hostname);
	answer = acksend(&resp, &ntp->dest_addr, (char *)ANYADDR, 
	    TSP_MASTERACK, ntp);
	if (answer == NULL) {
		/*
		 * Various conditions can cause conflict: race between
		 * two just started timedaemons when no master is
		 * present, or timedaemon started during an election.
		 * Conservative approach is taken: give up and became a
		 * slave postponing election of a master until first
		 * timer expires.
		 */
		time.tv_sec = time.tv_usec = 0;
		answer = readmsg(TSP_MASTERREQ, (char *)ANYADDR,
		    &time, ntp);
		if (answer != NULL) {
			ntp->status = SLAVE;
			return;
		}

		time.tv_sec = time.tv_usec = 0;
		answer = readmsg(TSP_MASTERUP, (char *)ANYADDR,
		    &time, ntp);
		if (answer != NULL) {
			ntp->status = SLAVE;
			return;
		}

		time.tv_sec = time.tv_usec = 0;
		answer = readmsg(TSP_ELECTION, (char *)ANYADDR,
		    &time, ntp);
		if (answer != NULL) {
			ntp->status = SLAVE;
			return;
		}
		ntp->status = MASTER;
	} else {
		(void)strcpy(mastername, answer->tsp_name);
		masteraddr = from;

		/*
		 * If network has been partitioned, there might be other
		 * masters; tell the one we have just acknowledged that 
		 * it has to gain control over the others. 
		 */
		time.tv_sec = 0;
		time.tv_usec = 300000;
		answer = readmsg(TSP_MASTERACK, (char *)ANYADDR, &time,
		    ntp);
		/*
		 * checking also not to send CONFLICT to ack'ed master
		 * due to duplicated MASTERACKs
		 */
		if (answer != NULL && 
		    strcmp(answer->tsp_name, mastername) != 0) {
			conflict.tsp_type = TSP_CONFLICT;
			(void)strcpy(conflict.tsp_name, hostname);
			if (acksend(&conflict, &masteraddr, mastername,
			    TSP_ACK, (struct netinfo *)NULL) == NULL) {
				syslog(LOG_ERR, 
				    "error on sending TSP_CONFLICT");
				exit(1);
			}
		}
	}
}
/*
 * based on the current network configuration, set the status, and count
 * networks;
 */
setstatus()
{
	register struct netinfo *ntp;

	status = 0;
	nmasternets = nslavenets = nnets = nignorednets = 0;
	if (trace)
		fprintf(fd, "Net status:\n");
	for (ntp = nettab; ntp != NULL; ntp = ntp->next) {
		switch ((int)ntp->status) {
		  case MASTER:
			nmasternets++;
			break;
		  case SLAVE:
			nslavenets++;
			break;
		  case IGNORE:
			nignorednets++;
			break;
		}
		if (trace) {
			fprintf(fd, "\t%-16s",
			    inet_ntoa(inet_makeaddr(ntp->net, 0)));
			switch ((int)ntp->status) {
			  case MASTER:
				fprintf(fd, "MASTER\n");
				break;
			  case SLAVE:
				fprintf(fd, "SLAVE\n");
				break;
			  case IGNORE:
				fprintf(fd, "IGNORE\n");
				break;
			  default:
				fprintf(fd, "invalid state %d\n",(int)ntp->status);
				break;
			}
		}
		nnets++;
		status |= ntp->status;
	}
	status &= ~IGNORE;
	if (trace)
		fprintf(fd,
		      "\tnets = %d, masters = %d, slaves = %d, ignored = %d\n",
		      nnets, nmasternets, nslavenets, nignorednets);
}

makeslave(net)
	struct netinfo *net;
{
	register struct netinfo *ntp;

	for (ntp = nettab; ntp != NULL; ntp = ntp->next)
		if (ntp->status == SLAVE && ntp != net)
			ntp->status = IGNORE;
	slavenet = net;
}
	
struct netinfo *
firstslavenet()
{
	register struct netinfo *ntp;

	for (ntp = nettab; ntp != NULL; ntp = ntp->next)
		if (ntp->status == SLAVE)
			return (ntp);
	return ((struct netinfo *)0);
}

/*
 * `casual' returns a random number in the range [inf, sup]
 */

long
casual(inf, sup)
long inf;
long sup;
{
	float value;

	value = (float)(random() & 0x7fffffff) / 0x7fffffff;
	return(inf + (sup - inf) * value);
}

char *
date()
{
	char    *ctime();
	struct	timeval tv;

	(void)gettimeofday(&tv, (struct timezone *)0);
	return (ctime(&tv.tv_sec));
}

addnetname(name)
	char *name;
{
	register struct nets **netlist = &nets;

	while (*netlist)
		netlist = &((*netlist)->next);
	*netlist = (struct nets *)malloc(sizeof **netlist);
	if (*netlist == (struct nets *)0) {
		syslog(LOG_ERR, "malloc failed");
		exit(1);
	}
	bzero((char *)*netlist, sizeof(**netlist));
	(*netlist)->name = name;
}
