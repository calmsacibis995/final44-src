h48116
s 00072/00015/00237
d D 7.6 91/07/15 20:54:03 sklower 6 5
c first; allow turning on/off kernel listeners;
c secondly, for echoing, keep copy of data to verify when qbit sent;
c thirdly, minor tweak for gcc (#s instead of "s").
e
s 00012/00003/00240
d D 7.5 91/05/07 13:28:53 bostic 5 4
c new copyright; att/bsd/shared
e
s 00003/00005/00240
d D 7.4 91/05/07 13:16:52 sklower 4 3
c Revise copyright notice
e
s 00014/00004/00231
d D 7.3 91/04/29 18:26:27 sklower 3 2
c add repeat feature for stimulating large amounts of data.
e
s 00003/00003/00232
d D 7.2 90/11/13 14:34:13 sklower 2 1
c initial working version of test programs
e
s 00235/00000/00000
d D 7.1 90/10/30 16:32:15 sklower 1 0
c date and time created 90/10/30 16:32:15 by sklower
e
u
U
t
T
I 1
D 4
/*
E 4
I 4
/*-
E 4
D 5
 * Copyright (c) 1988, 1990 Regents of the University of California.
E 5
I 5
 * Copyright (c) 1988, 1991 The Regents of the University of California.
E 5
 * All rights reserved.
 *
 * %sccs.include.redist.c%
I 4
D 5
 *
 * %W% (Berkeley) %G%
E 5
E 4
 */
I 5

#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1988, 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 5
D 4
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 4
/*
D 3
 * This is a test program to be a source for TP4 connections.
E 3
I 3
 * This is a test program to be a source for X.25 connections.
E 3
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/ioctl.h>
#include <net/route.h>
#include <net/if.h>
#include <netccitt/x25.h>

#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <netdb.h>


#define dbprintf if(verbose)printf
D 6
#define try(a,b,c) {x = (a b);dbprintf("%s%s returns %d\n",c,"a",x);\
		    if (x < 0) {perror("a"); exit(1);}}
E 6
I 6
#ifdef __STDC__
#define try(a,b,c) {x = (a b); dbprintf("%s%s returns %d\n",c,#a,x);\
		if(x<0) {perror(#a); exit(1);}}
#else
#define try(a,b,c) {x = (a b); dbprintf("%s%s returns %d\n",c,"a",x);\
		if(x<0) {perror("a"); exit(1);}}
#endif
E 6

fd_set	readfds, writefds, exceptfds;
long size, count = 10;
int verbose = 1, selectp, type = SOCK_STREAM, nobuffs, errno, playtag = 0;
D 6
int verify = 0, mqdata;
E 6
I 6
int verify = 0, mqdata, protolisten = 0, echop = 0;
unsigned char protodata[2] = {0, 1};
E 6
short portnumber = 3000;
struct sockaddr_x25 to;
char your_it[] = "You're it!";
char *port, *conndata, data_msg[2048];
struct iovec iov[1] = {data_msg};
union {
    struct {
	    struct cmsghdr	cmhdr;
	    char		cmdata[128 - sizeof (struct cmsghdr)];
    } cm;
    char data[128];
} cm;
struct msghdr msg = { 0, 0, iov, 1, 0, 0, 0};

main(argc, argv)
int argc;
char *argv[];
{
	register char **av = argv;
	register char *cp;
	u_long len;
	int handy;

	while(--argc > 0) {
		av++;
		if (strcmp(*av,"dest")==0) {
			av++;
			ccitt_addr(*av, &to);
			argc--;
		} else if (strcmp(*av,"count")==0) {
			av++;
			sscanf(*av,"%ld",&count);
			argc--;
		} else if (strcmp(*av,"size")==0) {
			av++;
			sscanf(*av,"%ld",&size);
D 6
		}
E 6
I 6
			argc--;
		} else if (strcmp(*av,"protolisten")==0) {
			av++;
			protolisten = 1;
			sscanf(*av,"%ld",&handy);
			argc--;
			protodata[0] = handy;
		} else if (strcmp(*av,"protonolisten")==0) {
			av++;
			protolisten = 1;
			sscanf(*av,"%ld",&handy);
			argc--;
			protodata[0] = handy;
			protodata[1] = 0;
		} 
E 6
	}
D 3
	tisrc();
E 3
I 3
	xisrc();
E 3
}

D 3
tisrc() {
E 3
I 3
xisrc() {
E 3
	int x, s, pid, on = 1, flags = 8, n;

	try(socket, (AF_CCITT, type, 0),"");
	s = x;

	/*try(setsockopt, (s, SOL_SOCKET, SO_DEBUG, &on, sizeof (on)), "");*/

I 6
	if (protolisten) {
		try(setsockopt, (s, CCITTPROTO_X25, PK_PRLISTEN,
					protodata, sizeof (protodata)), "");
	    exit(0);
	}

E 6
	to.x25_opts.op_flags |= X25_MQBIT;
	try(connect, (s, (struct sockaddr *) &to, to.x25_len), "");

	if (selectp) {
		FD_ZERO(&writefds); FD_SET(s, &writefds);
		select(1, &writefds, 0, 0, 0);
	}
	while (count-- > 0) {
		if (size <= 0 && get_record(&flags) == EOF)
			exit(0);
		n = put_record(s, flags);
		if (n < iov->iov_len) {
			if (n==-1 && errno == 55) {
				nobuffs++;
				count++;
				continue;
			}
			fprintf(stderr, "wrote %d < %d, count %d,",
						n, iov->iov_len, count);
			perror("due to");
		}
	}
	if (playtag) {
		printf("Tag time!\n");
		iov->iov_base = your_it;
		iov->iov_len = sizeof your_it;
		sendmsg(s, &msg, MSG_EOR);
		sendmsg(s, &msg, MSG_EOR);
		iov->iov_base = data_msg;
		iov->iov_len = sizeof data_msg;
		try(recvmsg, (s, &msg, flags), " playtag ");
	}
	if (nobuffs) {
		printf("looped %d times waiting for bufs\n", nobuffs);
	}
}
int localsize;
char dupbuf[4096];

I 6
struct savebuf {
	struct savebuf *s_next;
	struct savebuf *s_prev;
	int	s_n;
	int	s_flags;
} savebuf = {&savebuf, &savebuf};

void
savedata(n, flags)
int n;
{
	register struct savebuf *s = (struct savebuf *)malloc(n + sizeof *s);
	if (s == 0)
		return;
	insque(s, savebuf.s_prev);
	s->s_n = n;
	s->s_flags = flags;
	if (verify)
		bcopy(iov->iov_base, (char *)(s + 1), n);
}

checkback(ns)
int ns;
{
	int n;
	register struct savebuf *s = savebuf.s_next, *t;
	while (s != &savebuf) {
		iov->iov_len = s->s_n;
		n = recvmsg(ns, &msg, s->s_flags);
		dbprintf("echoed %d\n", n);
		if (verify && 
		    (n != s->s_n || bcmp((char *)(s + 1), iov->iov_base, n)))
			dbprintf("mismatched data or length was %d got %d\n",
				s->s_n, n);
		t = s; s = s->s_next; remque(t); free((char *)t);
	}
}

E 6
put_record(s, flags)
int s, flags;
{
	int fd, buflen;
	char *buf;
	int x, saved_x;

	msg.msg_flags = flags;
	if (verbose) {
		unsigned short *zp, *zlim;
		if (msg.msg_controllen) {
			zp = (unsigned short *)&(cm.cm.cmhdr.cmsg_len);
			printf("(CMessage Type is %x) ", cm.cm.cmhdr.cmsg_type);
			printf("CMsg data: ");
			x = msg.msg_controllen;
			zlim = zp + ((x + 1) / 2);
			while (zp < zlim) printf("%x ", *zp++);
			putchar ('\n');
		}
		if (iov->iov_len) {
			printf("sending: %s %s",
			(flags & MSG_OOB ? "(OOB Data)" : ""),
				(flags & MSG_EOR ? "(Record Mark)" : ""));
			x = localsize;
			zp = (unsigned short *)data_msg;
			zlim = zp + ((x + 1) / 2);
			while (zp < zlim) printf("%x ", *zp++);
			putchar ('\n');
		}
	}
D 6
	if (verify) {
		buflen = iov->iov_len;
		bcopy(iov->iov_base, dupbuf, buflen);
	}
E 6
I 6
	if (echop)
		savedata(iov->iov_len, flags);
E 6
	try(sendmsg, (s, &msg, flags), " put_record ");
	saved_x = x;
D 6
	while (verify && buflen > 0) {
		iov->iov_len = buflen;
		iov->iov_base = dupbuf;
		try(recvmsg, (s, &msg, flags), " put_record ");
		printf("verify got %d\n", x);
		buflen -= x;
	}
E 6
I 6
	if (echop && (iov->iov_base[0] & 0x80))
		checkback(s);
E 6
	msg.msg_control = 0;
	return (saved_x);
}
int *datasize = &iov->iov_len;
char *cp, *cplim;

get_control_data(type, level)
{

	datasize = (int *)&msg.msg_controllen;
	cp = cm.cm.cmdata;
	cplim = cp + sizeof(cm.cm.cmdata);
	cm.cm.cmhdr.cmsg_level = level;
	cm.cm.cmhdr.cmsg_type = type;
	msg.msg_control = cm.data;
}



get_record(flags)
int *flags;
{
	int factor = 1, x = 0;
	char workbuf[10240];
I 3
	static repeatcount, repeatsize;
E 3

I 3
	if (repeatcount > 0) {
		repeatcount--;
		return;
	}
E 3
	*flags = 0;
	*datasize = 0;
	datasize = &iov->iov_len;
	cp = data_msg + 1;
D 2
	cplim  = cp + sizeof(data_msg);
E 2
I 2
	cplim  = data_msg + sizeof(data_msg);
E 2

D 2
	data_msg[0] = 0;
E 2
I 2
	*data_msg = 0;
E 2
	for(;;) {
		x = scanf("%s", workbuf);
		if (x == EOF)
			break;
		if (strcmp(workbuf, "oob") == 0)
			*flags |= MSG_OOB;
		else if (strcmp(workbuf, "qbit") == 0)
			*data_msg |= 0x80;
		else if (strcmp(workbuf, "mbit") == 0)
			*data_msg |= 0x40;
		else if (strcmp(workbuf, "eom") == 0)
			*flags |= MSG_EOR;
		else if (strcmp(workbuf, "factor") == 0) {
			x = scanf("%d", &factor);
			if (factor <= 0) factor = 1;
			if (x == EOF)
				break;
I 3
		} else if (strcmp(workbuf, "repeat") == 0) {
			x = scanf("%d", &repeatcount);
			if (repeatcount <= 0) repeatcount = 1;
			if (x == EOF)
				break;
E 3
		} else {
			int len = strlen(workbuf);
D 2
			localsize = 0;
E 2
I 2
			localsize = 1;
E 2
			while ((factor-- > 0) &&
			       ((cp + len) < cplim)) {
					strcpy(cp, workbuf);
					cp += len;
					localsize += len;
			}
			*datasize = localsize;
			if (datasize != &iov->iov_len) {
				*datasize += sizeof(cm.cm.cmhdr);
D 3
				cm.cm.cmhdr.cmsg_len = *datasize;
E 3
I 3
				repeatsize = cm.cm.cmhdr.cmsg_len = *datasize;
E 3
			}
			break;
		}
	}
	errno = 0;
	return (x);
}
E 1
