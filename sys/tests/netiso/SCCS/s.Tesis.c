h50158
s 00013/00005/00128
d D 7.1 91/05/07 13:26:59 bostic 2 1
c main programs, use main copyright stub
e
s 00133/00000/00000
d D 1.1 91/05/07 13:11:23 sklower 1 0
c date and time created 91/05/07 13:11:23 by sklower
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1988, 1990 Regents of the University of California.
E 2
I 2
/*-
 * Copyright (c) 1988, 1990 The Regents of the University of California.
E 2
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 */
D 2
/* Modifications
 * Copyright (c) 1990 Robert Hagens
 */
E 2
I 2

E 2
#ifndef lint
I 2
char copyright[] =
"%Z% Copyright (c) 1988, 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
E 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
I 2

/* Modifications
 * Copyright (c) 1990 Robert Hagens
 */
E 2

/*
 * This is a test program to listen to esis packets.
 */
#include <sys/param.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
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
#define try(a,b,c) {x = (a b); dbprintf("%s%s returns %d\n",c,"a",x);\
		if(x<0) {perror("a"); myexit(0);}}


struct  ifreq ifr;
short port = 3000;
struct  sockaddr_iso faddr, laddr = { sizeof(laddr), AF_ISO };
struct  sockaddr_iso *siso = &laddr;
char **xenvp;

long size, count = 10, forkp, confp, echop, mynamep, verbose = 1, playtag = 0;
long records, intercept = 0, isode_mode;

char buf[2048];
char your_it[] = "You're it!";

char *Servername;

main(argc, argv, envp)
int argc;
char *argv[];
char *envp[];
{
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
	int x, s, pid, on = 1, loop = 0, n, fromlen, flags = 0;
	extern int errno;

	try(socket, (AF_ISO, SOCK_DGRAM, ISOPROTO_ESIS),"");
	s = x;

	for(;;) {
		fromlen = sizeof(name);
		try(recvfrom, (s, readbuf, sizeof(readbuf), flags,
			name, &fromlen), "");
		n = x;
		dumpit("connection from:", name, fromlen);
		dumpit("packet is:", readbuf, n);
	}
}
answerback(flags, n, ns)
{
	msghdr.msg_controllen = 0;
	msghdr.msg_iovlen = 1;
	iov->iov_len = n;
	n = sendmsg(ns, &msghdr, flags);
	dbprintf("echoed %d\n", n);
	return n;
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
