h07759
s 00004/00003/00339
d D 7.11 93/02/25 17:04:59 sklower 11 10
c tuba testing (TCP/CLNP)
e
s 00038/00004/00304
d D 7.10 92/07/23 16:54:33 sklower 10 9
c check in for distribution
e
s 00013/00007/00295
d D 7.9 91/08/22 17:40:52 sklower 9 8
c use #a under gcc, set echo mode from command line; make forp work;
c have semi-verbose mode -- dumpnodata, but report everything else.
e
s 00001/00001/00301
d D 7.8 91/07/24 19:52:55 sklower 8 7
c default for echoing should be off.
e
s 00045/00021/00257
d D 7.7 91/07/24 19:50:38 sklower 7 6
c test tp0 sockets, echoing a la xisoc tsap echo
e
s 00009/00002/00269
d D 7.6 91/05/07 13:27:00 bostic 6 5
c main programs, use main copyright stub
e
s 00020/00012/00251
d D 7.5 91/04/25 18:12:39 sklower 5 4
c include support for clnp testing
e
s 00014/00002/00249
d D 7.4 91/04/25 18:06:16 sklower 4 3
c final version of transport-sink, obsoleted by cisink.c
e
s 00004/00002/00247
d D 7.3 90/06/29 11:12:30 sklower 3 2
c put in code to test meta-listeners.
e
s 00005/00001/00244
d D 7.2 90/06/28 19:40:38 sklower 2 1
c check for duplicate CR's; allow intercepting all CR's to a given
c nsap; not yet tested, but check in for tape anyhow
e
s 00245/00000/00000
d D 7.1 90/06/27 12:13:36 sklower 1 0
c date and time created 90/06/27 12:13:36 by sklower
e
u
U
t
T
I 1
D 6
/*
 * Copyright (c) 1988, 1990 Regents of the University of California.
E 6
I 6
/*-
 * Copyright (c) 1988, 1990 The Regents of the University of California.
E 6
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 */
I 6

#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1988, 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

E 6
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
D 5
 * This is a test program to be a sink for TP4 connections.
E 5
I 5
 * This is a test program to be a sink for ISO packets.
E 5
 */
I 10
#include <unistd.h>
E 10
#include <sys/param.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
I 10
#include <sys/syscall.h>
E 10
#include <net/route.h>
#include <net/if.h>
#define  TCPT_NTIMERS 4
#include <netiso/iso.h>
#include <netiso/tp_param.h>
#include <netiso/tp_user.h>

#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <netdb.h>


#define dbprintf if(verbose)printf
I 9
#ifdef __STDC__
#define try(a,b,c) {x = (a b); dbprintf("%s%s returns %d\n",c,#a,x);\
		if (x<0) {perror(#a); myexit(0);}}
#else
E 9
#define try(a,b,c) {x = (a b); dbprintf("%s%s returns %d\n",c,"a",x);\
D 9
		if(x<0) {perror("a"); myexit(0);}}
E 9
I 9
		if (x<0) {perror("a"); myexit(0);}}
#endif
E 9


struct  ifreq ifr;
short port = 3000;
struct  sockaddr_iso faddr, laddr = { sizeof(laddr), AF_ISO };
struct  sockaddr_iso *siso = &laddr;
I 4
char **xenvp;
E 4

D 7
long size, count = 10, forkp, confp, echop, mynamep, verbose = 1, playtag = 0;
D 2
long records;
E 2
I 2
D 3
long records, intercept;
E 3
I 3
D 4
long records, intercept = 0;
E 4
I 4
D 5
long records, intercept = 0, isode_mode;
E 5
I 5
long records, intercept = 0, isode_mode = 0, dgramp = 0;
E 7
I 7
D 8
long size, count = 10, forkp, confp, mynamep, verbose = 1, playtag, echop = 1;
E 8
I 8
D 9
long size, count = 10, forkp, confp, mynamep, verbose = 1, playtag, echop = 0;
E 9
I 9
D 10
long size, forkp = 0, confp, mynamep, verbose = 1, echop = 0;
E 10
I 10
long size, forkp = 0, confp = 0, mynamep, verbose = 1, echop = 0;
E 10
E 9
E 8
long records, intercept = 0, isode_mode = 0, dgramp = 0, tp0mode = 0;
I 9
D 10
long dumpnodata = 0, playtag = 0;
E 10
I 10
D 11
long dumpnodata = 0, playtag = 0, select_mode = 0;
E 11
I 11
long dumpnodata = 0, playtag = 0, select_mode = 0, tuba = 0;
E 11
E 10
E 9
void savedata();
E 7
E 5
E 4
E 3
E 2

char buf[2048];
char your_it[] = "You're it!";
I 10
fd_set readfds, exceptfds;
E 10

char *Servername;

D 4
main(argc, argv)
E 4
I 4
main(argc, argv, envp)
E 4
int argc;
char *argv[];
I 4
char *envp[];
E 4
{
	register char **av = argv;
	register char *cp;
D 5
	struct iso_addr iso_addr();
E 5
I 5
	struct iso_addr *iso_addr();
E 5

I 4
	xenvp = envp;
E 4
	while(--argc > 0) {
		av++;
		if(strcmp(*av,"Servername")==0) {
			av++;
			Servername = *av;
			argc--;
		} else if (strcmp(*av,"host")==0) {
			av++;
D 5
			laddr.siso_addr = iso_addr(*av);
E 5
I 5
			laddr.siso_addr = *iso_addr(*av);
E 5
			argc--;
D 9
		} else if (strcmp(*av,"count")==0) {
			av++;
			sscanf(*av,"%ld",&count);
			argc--;
E 9
		} else if (strcmp(*av,"port")==0) {
			av++;
			sscanf(*av,"%hd",&port);
			argc--;
		} else if (strcmp(*av,"size")==0) {
			av++;
			sscanf(*av,"%ld",&size);
			argc--;
I 9
		} else if (strcmp(*av, "echo")==0) {
			echop++;
E 9
I 3
		} else if (strcmp(*av, "intercept")==0) {
			intercept++;
E 3
		}
	}
	if (Servername) {
		int tlen = laddr.siso_tlen = strlen(Servername);
		int len =  TSEL(siso) + tlen - (caddr_t) &siso;
		if (len > sizeof(*siso)) {
			siso = (struct sockaddr_iso *)malloc(len);
			*siso = laddr;
			siso->siso_len = len;
		}
		bcopy(Servername, TSEL(siso), tlen);
	} else {
		port = htons(port);
		laddr.siso_tlen = sizeof(port);
		bcopy((char *)&port, TSEL(siso), sizeof(port));
	}
	tisink();
}
#define BIG 2048
#define MIDLIN 512
char readbuf[BIG];
struct iovec iov[1] = {
	readbuf,
	sizeof readbuf,
};
char name[MIDLIN];
union {
    struct {
	    struct cmsghdr	cmhdr;
	    char		cmdata[128 - sizeof(struct cmsghdr)];
    } cm;
    char data[128];
} cbuf;
#define control cbuf.data
struct msghdr msghdr = {
	name, sizeof(name),
	iov, sizeof(iov)/sizeof(iov[1]),
	control, sizeof control,
	0 /* flags */
};

tisink()
{
D 5
	int x, s, pid, on = 1, loop = 0, n;
E 5
I 5
	int x, s, pid, on = 1, loop = 0, n, ns;
E 5
	extern int errno;
I 5
D 11
	int socktype = (dgramp ? SOCK_DGRAM : SOCK_SEQPACKET);
I 7
	int proto = (tp0mode ? ISOPROTO_TP0 : 0 );
E 11
I 11
	int socktype = (dgramp ? SOCK_DGRAM :
			(tuba ? SOCK_STREAM :SOCK_SEQPACKET));
	int proto = (tp0mode ? ISOPROTO_TP0 : (tuba ? ISOPROTO_TCP : 0 ));
E 11
E 7
	int addrlen = sizeof(faddr);
E 5

D 5
	try(socket, (AF_ISO, SOCK_SEQPACKET, 0),"");
E 5
I 5
D 7
	try(socket, (AF_ISO, socktype, 0),"");
E 7
I 7
	try(socket, (AF_ISO, socktype, proto),"");
E 7
E 5

	s = x;

	try(bind, (s, (struct sockaddr *) siso, siso->siso_len), "");

	/*try(setsockopt, (s, SOL_SOCKET, SO_DEBUG, &on, sizeof (on)), ""); */
I 5
	if (dgramp) {
		ns  =  s;
		goto dgram1;
	}
E 5

	try(listen, (s, 5), "");
I 2
	if (intercept) {
	    try(setsockopt,
		(s, SOL_TRANSPORT, TPOPT_INTERCEPT, &on, sizeof(on)), "");
	}
E 2
	for(;;) {
D 5
		int child, ns;
		int addrlen = sizeof(faddr);
E 5
I 5
		int child;
E 5
		char childname[50];

D 7
		try (accept, (s, &faddr, &addrlen), "");
E 7
I 7
		try (accept, (s, (struct sockaddr *)&faddr, &addrlen), "");
E 7
		ns = x;
		dumpit("connection from:", &faddr, sizeof faddr);
D 3
		if (mynamep) {
E 3
I 3
		if (mynamep || intercept) {
E 3
			addrlen = sizeof(faddr);
D 7
			try (getsockname, (ns, &faddr, &addrlen), "");
E 7
I 7
			try (getsockname,
			      (ns, (struct sockaddr *)&faddr, &addrlen), "");
E 7
			dumpit("connected as:", &faddr, addrlen);
		}
		loop++;
D 5
		if (loop > 3) myexit(0);
E 5
I 5
		if(loop > 3) myexit(0);
E 5
		if (forkp) {
			try(fork, (), "");
		} else
			x = 0;
		if (x == 0)  {
		    long n, count = 0, cn, flags;
		    records = 0;
		    if (confp) {
			msghdr.msg_iovlen = 0;
			msghdr.msg_namelen = 0;
			msghdr.msg_controllen = 
			    cbuf.cm.cmhdr.cmsg_len = sizeof (cbuf.cm.cmhdr);
			cbuf.cm.cmhdr.cmsg_level = SOL_TRANSPORT;
			cbuf.cm.cmhdr.cmsg_type = TPOPT_CFRM_DATA;
			n = sendmsg(ns, &msghdr, 0);
D 5
			if (n <= 0) {
E 5
I 5
			if (n < 0) {
E 5
				printf("confirm: errno is %d\n", errno);
				fflush(stdout);
				perror("Confirm error");
			} else {
				dbprintf("confim ok\n");
			}
D 10
			sleep(10);
E 10
I 10
			sleep(3);
E 10
		    }
I 4
#ifdef ISODE_MODE
		    if (isode_mode) {
			static char fdbuf[10];
			static char *nargv[4] =
			    {"/usr/sbin/isod.tsap", fdbuf, "", 0};
			sprintf(fdbuf, "Z%d", ns);
			old_isod_main(3, nargv, xenvp);
D 10
		    } else
E 10
I 10
			myexit(0);
		    }
E 10
#endif
E 4
		    for (;;) {
I 5
		    dgram1:
E 5
			msghdr.msg_iovlen = 1;
			msghdr.msg_controllen = sizeof(control);
I 5
			msghdr.msg_namelen = (dgramp ? (sizeof name) : 0);
E 5
			iov->iov_len = sizeof(readbuf);
I 10
			if (select_mode)
			    sel_recvwait(ns);
E 10
			n = recvmsg(ns, &msghdr, 0);
			flags = msghdr.msg_flags;
			count++;
			dbprintf("recvmsg from child %d got %d ctl %d flags %x\n",
D 5
				    getpid(), n, (cn = msghdr.msg_controllen),
					flags);
E 5
I 5
				getpid(), n, (cn = msghdr.msg_controllen), flags);
E 5
			fflush(stdout);
I 5
			if (dgramp && msghdr.msg_namelen && verbose)
				dumpit("from:\n", name, msghdr.msg_namelen);
E 5
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
D 7
			if (echop) {
				n = answerback(flags, n, ns);
			}
			if (flags & MSG_EOR)
E 7
I 7
			if (echop)
				savedata(n, flags);
			if (flags & MSG_EOR) {
E 7
				records++;
D 7
			if (playtag && n == sizeof(your_it) && (flags & MSG_EOR)
			    && bcmp(readbuf, your_it, n) == 0) {
				printf("Answering back!!!!\n");
				answerback(flags, n, ns);
				answerback(flags, n, ns);
E 7
I 7
				if (echop)
					answerback(ns);
E 7
			}
			errno = 0;
		    }
I 9
		    myexit(0);
E 9
		}
D 9
		myexit(0);
E 9
	}
}
D 7
answerback(flags, n, ns)
E 7
I 7
struct savebuf {
	struct savebuf *s_next;
	struct savebuf *s_prev;
	int	s_n;
	int	s_flags;
} savebuf = {&savebuf, &savebuf};

void
savedata(n, flags)
int n, flags;
E 7
{
D 7
	msghdr.msg_controllen = 0;
	msghdr.msg_iovlen = 1;
	iov->iov_len = n;
	n = sendmsg(ns, &msghdr, flags);
	dbprintf("echoed %d\n", n);
	return n;
E 7
I 7
	register struct savebuf *s = (struct savebuf *)malloc(n + sizeof *s);
	if (s == 0)
		return;
	insque(s, savebuf.s_prev);
	s->s_n = n;
	s->s_flags = flags;
	bcopy(readbuf, (char *)(s + 1), n);
}

answerback(ns)
{
	int n;
	register struct savebuf *s = savebuf.s_next, *t;
	static struct iovec iov[1];
	static struct msghdr msghdr = { 0, 0, iov, 1, 0, 0, 0};
	while (s != &savebuf) {
		iov->iov_len = s->s_n;
		iov->iov_base = (char *)(s + 1);
		n = sendmsg(ns, &msghdr, s->s_flags);
		dbprintf("echoed %d\n", n);
		t = s; s = s->s_next; remque(t); free((char *)t);
	}
E 7
}

dumpit(what, where, n)
char *what; unsigned short *where; int n;
{
	unsigned short *s = where;
	unsigned short *z = where + (n+1)/2;
	int count = 0;
I 9
	if (dumpnodata)
		return;
E 9
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
I 10
}

sel_recvwait(fd)
int fd;
{
	int x;
	do {
		FD_ZERO(&readfds);
		FD_ZERO(&exceptfds);
		FD_SET(fd, &readfds);
		FD_SET(fd, &exceptfds);
		x = select(fd+1, &readfds, (fd_set *)0, &exceptfds, (void *)0);
		dbprintf("select returns %d\n", x);
	} while (x <= 0 ||
		 (FD_ISSET(fd,&readfds) == 0 && FD_ISSET(fd,&exceptfds) == 0));
}

#include <sys/syscall.h>
/* Here for gdb trapping */
setsockopt(s, level, optname, optval, optlen)
int s, level, optname, optlen;
const void *optval;
{

	dbprintf("setsocket called s %d, level 0x%x, optname %d, optlen %d\n",
			s, level, optname, optlen);
	dumpit("", optval, optlen);
	return syscall(SYS_setsockopt, s, level, optname, optval, optlen);
E 10
}
E 1
