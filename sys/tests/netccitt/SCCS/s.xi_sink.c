h30747
s 00020/00015/00222
d D 7.6 91/07/15 20:52:00 sklower 6 5
c first, copy actual data to send back rather than garbage;
c secondly, sendmsg seems fussy about 0 length name or controllen;
c third, minor tweaks for gcc (#s instead of "s", and pointer casts).
e
s 00038/00025/00199
d D 7.5 91/07/15 18:22:14 sklower 5 4
c funny echo mode
e
s 00012/00003/00212
d D 7.4 91/05/07 13:28:52 bostic 4 3
c new copyright; att/bsd/shared
e
s 00004/00006/00211
d D 7.3 91/05/07 13:16:49 sklower 3 2
c Revise copyright notice
e
s 00001/00001/00216
d D 7.2 90/11/13 14:34:15 sklower 2 1
c initial working version of test programs
e
s 00217/00000/00000
d D 7.1 90/10/30 16:32:15 sklower 1 0
c date and time created 90/10/30 16:32:15 by sklower
e
u
U
t
T
I 1
D 3
/*
E 3
I 3
/*-
E 3
D 4
 * Copyright (c) 1988, 1990 Regents of the University of California.
E 4
I 4
 * Copyright (c) 1988, 1991 The Regents of the University of California.
E 4
 * All rights reserved.
 *
 * %sccs.include.redist.c%
I 3
D 4
 *
 * %W% (Berkeley) %G%
E 4
E 3
 */
I 4

#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1988, 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 4
D 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 3
/*
D 3
 * This is a test program to be a sink for TP4 connections.
E 3
I 3
 * This is a test program to be a sink for X.25 connections.
E 3
 */
#include <sys/param.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/route.h>
#include <net/if.h>
#include <netccitt/x25.h>

#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <netdb.h>


#define dbprintf if(verbose)printf
I 6
#ifdef __STDC__
#define try(a,b,c) {x = (a b); dbprintf("%s%s returns %d\n",c,#a,x);\
		if(x<0) {perror(#a); myexit(0);}}
#else
E 6
#define try(a,b,c) {x = (a b); dbprintf("%s%s returns %d\n",c,"a",x);\
		if(x<0) {perror("a"); myexit(0);}}
I 6
#endif
E 6


struct  ifreq ifr;
short port = 3000;
struct  sockaddr_x25 faddr, laddr = { sizeof(laddr), AF_CCITT };
struct  sockaddr_x25 *sx25 = &laddr;
char **xenvp;

D 5
long size, count = 10, forkp, confp, echop, mynamep, verbose = 1, playtag = 0;
long records, intercept = 0, isode_mode;
E 5
I 5
long size, count = 10, forkp, echop = 0, mynamep, verbose = 1, playtag = 0;
long records, intercept = 0, confp;
void savedata();
E 5

char buf[2048];
char your_it[] = "You're it!";

char *Servername;

main(argc, argv, envp)
int argc;
char *argv[];
char *envp[];
{
	register char **av = argv;
	register char *cp;

	xenvp = envp;
	while(--argc > 0) {
		av++;
		if (strcmp(*av,"host")==0) {
			av++;
			ccitt_addr(*av, sx25);
			argc--;
		} else if (strcmp(*av,"count")==0) {
			av++;
			sscanf(*av,"%ld",&count);
			argc--;
		} else if (strcmp(*av,"size")==0) {
			av++;
			sscanf(*av,"%ld",&size);
			argc--;
		} else if (strcmp(*av, "intercept")==0) {
			intercept++;
		}
	}
D 6
	tisink();
E 6
I 6
	xisink();
E 6
}
#define BIG 2048
#define MIDLIN 512
char readbuf[BIG];
D 6
struct iovec iov[1] = {
	readbuf,
	sizeof readbuf,
};
E 6
char name[MIDLIN];
I 6
struct iovec iov[1];
E 6
union {
    struct {
	    struct cmsghdr	cmhdr;
	    char		cmdata[128 - sizeof(struct cmsghdr)];
    } cm;
    char data[128];
} cbuf;
#define control cbuf.data
struct msghdr msghdr = {
D 6
	name, sizeof(name),
E 6
I 6
	0, 0,
E 6
	iov, sizeof(iov)/sizeof(iov[1]),
D 5
	control, sizeof control,
E 5
I 5
D 6
	control, sizeof(control),
E 5
	0 /* flags */
E 6
I 6
	0, 0, 0
E 6
};

D 6
tisink()
E 6
I 6
xisink()
E 6
{
	int x, s, pid, on = 1, loop = 0, n;
	extern int errno;

D 2
	try(socket, (AF_ISO, SOCK_SEQPACKET, 0),"");
E 2
I 2
	try(socket, (AF_CCITT, SOCK_STREAM, 0),"");
E 2

	s = x;

	sx25->x25_opts.op_flags |= X25_MQBIT;
	try(bind, (s, (struct sockaddr *) sx25, sx25->x25_len), "");

	/*try(setsockopt, (s, SOL_SOCKET, SO_DEBUG, &on, sizeof (on)), ""); */

	try(listen, (s, 5), "");
	for(;;) {
		int child, ns;
		int addrlen = sizeof(faddr);
		char childname[50];

D 6
		try (accept, (s, &faddr, &addrlen), "");
E 6
I 6
		try (accept, (s, (struct sockaddr *)&faddr, &addrlen), "");
E 6
		ns = x;
		dumpit("connection from:", &faddr, sizeof faddr);
		if (mynamep || intercept) {
			addrlen = sizeof(faddr);
D 6
			try (getsockname, (ns, &faddr, &addrlen), "");
E 6
I 6
			try (getsockname, (ns, (struct sockaddr *)&faddr,
				&addrlen), "");
E 6
			dumpit("connected as:", &faddr, addrlen);
		}
		loop++;
		if (loop > 3) myexit(0);
		if (forkp) {
			try(fork, (), "");
		} else
			x = 0;
		if (x == 0)  {
		    long n, count = 0, cn, flags;
		    records = 0;
D 5
#ifdef ISODE_MODE
		    if (isode_mode) {
			static char fdbuf[10];
			static char *nargv[4] =
			    {"/usr/sbin/isod.tsap", fdbuf, "", 0};
			sprintf(fdbuf, "Z%d", ns);
			old_isod_main(3, nargv, xenvp);
		    } else
#endif
E 5
		    for (;;) {
D 6
			msghdr.msg_iovlen = 1;
E 6
			msghdr.msg_controllen = sizeof(control);
I 6
			msghdr.msg_control = control;
E 6
			iov->iov_len = sizeof(readbuf);
I 6
			iov->iov_base = readbuf;
E 6
			n = recvmsg(ns, &msghdr, 0);
			flags = msghdr.msg_flags;
			count++;
			dbprintf("recvmsg from child %d got %d ctl %d flags %x\n",
				    getpid(), n, (cn = msghdr.msg_controllen),
					flags);
			fflush(stdout);
			if (cn && verbose)
				dumpit("control data:\n", control, cn);
			if (n < 0) {
				fprintf(stderr, "errno is %d\n", errno);
				perror("recvmsg");
				/*sleep (10);*/
				break;
			} else {
				if (verbose)
					dumpit("data:\n", readbuf, n);
			}
D 5
			if (echop) {
				n = answerback(flags, n, ns);
			}
E 5
I 5
			if (echop)
				savedata(n);
E 5
			if (flags & MSG_EOR)
				records++;
D 5
			if (playtag && n == sizeof(your_it) && (flags & MSG_EOR)
			    && bcmp(readbuf, your_it, n) == 0) {
				printf("Answering back!!!!\n");
				answerback(flags, n, ns);
				answerback(flags, n, ns);
E 5
I 5
			if (echop && (readbuf[0] & 0x80)) {
				dbprintf("Answering back!!!!\n");
				answerback(ns);
E 5
			}
			errno = 0;
		    }
		}
		myexit(0);
	}
}
D 5
answerback(flags, n, ns)
E 5
I 5

struct savebuf {
	struct savebuf *s_next;
	struct savebuf *s_prev;
	int	s_n;
	int	s_flags;
} savebuf = {&savebuf, &savebuf};

void
D 6
savedata(n, flags)
E 6
I 6
savedata(n)
E 6
int n;
E 5
{
I 5
	register struct savebuf *s = (struct savebuf *)malloc(n + sizeof *s);
	if (s == 0)
		return;
	insque(s, savebuf.s_prev);
	s->s_n = n;
D 6
	s->s_flags = flags;
E 6
I 6
	s->s_flags = msghdr.msg_flags;
	bcopy(readbuf, (char *)(s + 1), n);
E 6
}

answerback(ns)
{
	int n;
	register struct savebuf *s = savebuf.s_next, *t;
E 5
	msghdr.msg_controllen = 0;
D 6
	msghdr.msg_iovlen = 1;
E 6
I 6
	msghdr.msg_control = 0;
E 6
D 5
	iov->iov_len = n;
	n = sendmsg(ns, &msghdr, flags);
	dbprintf("echoed %d\n", n);
	return n;
E 5
I 5
	while (s != &savebuf) {
		iov->iov_len = s->s_n;
I 6
		iov->iov_base = (char *)(s + 1);
E 6
		n = sendmsg(ns, &msghdr, s->s_flags);
		dbprintf("echoed %d\n", n);
		t = s; s = s->s_next; remque(t); free((char *)t);
	}
E 5
}

dumpit(what, where, n)
char *what; unsigned short *where; int n;
{
	unsigned short *s = where;
	unsigned short *z = where + (n+1)/2;
	int count = 0;
	printf(what);
	while(s < z) {
		count++;
		printf("%x ",*s++);
		if ((count & 15) == 0)
			putchar('\n');
	}
	if (count & 15)
		putchar('\n');
	fflush(stdout);
}
myexit(n)
{
	fflush(stderr);
	printf("got %d records\n", records);
	fflush(stdout);
	exit(n);
}
E 1
