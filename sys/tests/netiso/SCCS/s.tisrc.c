h46663
s 00018/00006/00422
d D 7.8 93/02/25 17:04:58 sklower 8 7
c tuba testing (TCP/CLNP)
e
s 00003/00003/00425
d D 7.7 92/05/04 18:00:30 sklower 7 6
c minor fixes made aug 22 1991
e
s 00093/00027/00335
d D 7.6 91/08/22 18:47:52 sklower 6 5
c use #a under gcc, set echo mode from command line; make echop work;
c semi-verbose mode -- dumpnodata; default to unlimit counts.
e
s 00009/00002/00353
d D 7.5 91/05/07 13:27:01 bostic 5 4
c main programs, use main copyright stub
e
s 00008/00009/00347
d D 7.4 91/05/04 13:47:07 sklower 4 3
c check in for network tape
e
s 00004/00004/00352
d D 7.3 91/04/29 18:29:13 sklower 3 2
c try out direct tp0 connection
e
s 00113/00044/00243
d D 7.2 91/04/25 18:14:20 sklower 2 1
c include support for clnp, mostly
e
s 00287/00000/00000
d D 7.1 90/06/27 12:13:36 sklower 1 0
c date and time created 90/06/27 12:13:36 by sklower
e
u
U
t
T
I 1
D 5
/*
D 2
 * Copyright (c) 1988, 1990 Regents of the University of California.
E 2
I 2
 * Copyright (c) 1989, 1990 Regents of the University of California.
E 5
I 5
/*-
 * Copyright (c) 1988, 1990 The Regents of the University of California.
E 5
E 2
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 */
I 5

#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1988, 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

E 5
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
D 2
 * This is a test program to be a source for TP4 connections.
E 2
I 2
 * This is a test program to be a source for ISO transport.
E 2
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/ioctl.h>
#include <net/route.h>
#include <net/if.h>
#define  TCPT_NTIMERS 4
#include <netiso/iso.h>
#include <netiso/tp_user.h>

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
		if (x<0) {perror(#a); exit(1);}}
#else
#define try(a,b,c) {x = (a b); dbprintf("%s%s returns %d\n",c,"a",x);\
		if (x<0) {perror("a");exit(1);}}
#endif
E 6

struct	iso_addr eon = {20, 0x47, 0, 6, 3, 0, 0, 0, 25 /*EGP for Berkeley*/};
I 4
struct	iso_addr *iso_addr();
E 4
struct  sockaddr_iso to_s = { sizeof(to_s), AF_ISO }, *to = &to_s;
I 8
struct  sockaddr_iso from_s = { sizeof(from_s), AF_ISO }, *from = 0;
E 8
I 2
struct  sockaddr_iso old_s = { sizeof(to_s), AF_ISO }, *old = &old_s;
I 3
struct	tp_conn_param tp_params;
E 3
E 2
fd_set	readfds, writefds, exceptfds;
D 6
long size, count = 10;
E 6
I 6
long size, count = 0;
E 6
D 8
int verbose = 1, selectp, type = SOCK_SEQPACKET, nobuffs, errno, playtag = 0;
D 2
int verify = 0;
E 2
I 2
D 3
int verify = 0, dgramp = 0, debug = 0;
E 3
I 3
D 6
int verify = 0, dgramp = 0, debug = 0, tp0mode = 1;
E 6
I 6
int echop = 0, dgramp = 0, debug = 0, tp0mode = 0, dumpnodata  = 0;
E 8
I 8
int verbose = 1, selectp, socktype = SOCK_SEQPACKET, nobuffs, errno, playtag = 0;
int echop = 0, dgramp = 0, debug = 0, tp0mode = 0, dumpnodata  = 0, tuba = 0;
E 8
E 6
E 3
E 2
short portnumber = 3000;
char your_it[] = "You're it!";
D 2
char *port, *conndata, data_msg[2048];
E 2
I 2
D 6
char *Servername, *conndata, data_msg[2048];
E 6
I 6
char *Servername, *conndata, data_msg[8192];
E 6
char Serverbuf[128];
char name[128];
E 2
struct iovec iov[1] = {data_msg};
union {
    struct {
	    struct cmsghdr	cmhdr;
D 2
	    char		cmdata[128 - sizeof (struct cmsghdr)];
E 2
I 2
	    char		cmdata[128 - sizeof(struct cmsghdr)];
E 2
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
D 2
	struct iso_addr iso_addr();
E 2
	u_long len;
	int handy;

	while(--argc > 0) {
		av++;
		if(strcmp(*av,"Servername")==0) {
			av++;
D 2
			port = *av;
E 2
I 2
			Servername = *av;
E 2
			argc--;
		} else if(strcmp(*av,"conndata")==0) {
			av++;
			conndata = *av;
			argc--;
		} else if(strcmp(*av,"host")==0) {
			av++;
D 2
			to_s.siso_addr = iso_addr(*av);
E 2
I 2
			to_s.siso_addr = *iso_addr(*av);
E 2
			argc--;
I 8
		} else if(strcmp(*av,"from")==0) {
			av++;
			from_s.siso_addr = *iso_addr(*av);
			from = &from_s;
			argc--;
E 8
		} else if(strcmp(*av,"port")==0) {
			av++;
			sscanf(*av,"%hd",&portnumber);
			argc--;
		} else if(strcmp(*av,"count")==0) {
			av++;
			sscanf(*av,"%ld",&count);
			argc--;
		} else if(strcmp(*av,"size")==0) {
			av++;
			sscanf(*av,"%ld",&size);
			iov->iov_len = size;
		} else if(strcmp(*av,"stream")==0) {
D 8
			type = SOCK_STREAM;
E 8
I 8
			socktype = SOCK_STREAM;
E 8
I 6
		} else if (strcmp(*av, "echo")==0) {
			echop++;
E 6
		} else if (strcmp(*av,"eon") == 0) {
			unsigned long l, inet_addr();

			l = inet_addr(*++av); argc--;
			to_s.siso_addr = eon;
			bcopy((char *)&l, &to_s.siso_data[15], 4);
		}
	}
D 2
	if (port) {
		to_s.siso_tlen = strlen(port);
		len =  1 + to_s.siso_nlen + strlen(port)
				+ sizeof(*to) - sizeof(struct iso_addr);
		if (len > sizeof(*to)) {
E 2
I 2
	maketoaddr();
	tisrc();
}

maketoaddr()
{
	if (Servername) {
		int tlen = strlen(Servername);
		int len =  tlen + TSEL(to) - (caddr_t) to;
		if (len < sizeof(*to)) len = sizeof(*to);
		if (len > to->siso_len) {
D 4
			if (old != &old_s) free(old);
			old = (struct sockaddr_iso *)malloc(len);
			*old = *to; /* We dont care if all old tsel is copied*/
			old->siso_len = len;
			if (to != &to_s) free(to);
E 4
I 4
			old = to;
E 4
E 2
			to = (struct sockaddr_iso *)malloc(len);
I 4
			*to = *old; /* We dont care if all old tsel is copied*/
			if (old != &to_s) free(old);
E 4
D 2
			bzero(to, len);
			*to = to_s;
			to->siso_len = len;
E 2
		}
D 2
		bcopy(port, TSEL(to), strlen(port));
E 2
I 2
D 4
		bcopy(Servername, TSEL(old), tlen);
E 4
I 4
		bcopy(Servername, TSEL(to), tlen);
		to->siso_tlen = tlen;
E 4
E 2
	} else {
D 2
		to_s.siso_tlen = sizeof(portnumber);
E 2
I 2
D 4
		old->siso_tlen = sizeof(portnumber);
E 4
I 4
		to->siso_tlen = sizeof(portnumber);
E 4
E 2
		portnumber = htons(portnumber);
D 2
		bcopy((char *)&portnumber, TSEL(to), sizeof(portnumber));
E 2
I 2
D 4
		bcopy((char *)&portnumber, TSEL(old), sizeof(portnumber));
E 4
I 4
		bcopy((char *)&portnumber, TSEL(to), sizeof(portnumber));
E 4
E 2
	}
D 2

	tisrc();
E 2
I 2
D 4
	bcopy(old, to, old->siso_len);
E 4
E 2
}

I 2
D 3

E 3
E 2
tisrc() {
D 3
	int x, s, pid, on = 1, flags = 8, n;
E 3
I 3
D 8
	int x, s, pid, on = 1, flags = 8, n, proto = tp0mode ? ISOPROTO_TP0: 0;
E 8
I 8
	int x, s, pid, on = 1, flags = 8, n;
	int proto = (tp0mode ? ISOPROTO_TP0 : (tuba ? ISOPROTO_TCP : 0 ));
	int socktype = (dgramp ? SOCK_DGRAM :
			(tuba ? SOCK_STREAM :SOCK_SEQPACKET));
E 8
E 3

I 2
D 8
	if (dgramp) type = SOCK_DGRAM;
E 2
D 3
	try(socket, (AF_ISO, type, 0),"");
E 3
I 3
	try(socket, (AF_ISO, type, proto),"");
E 8
I 8
	try(socket, (AF_ISO, socktype, proto),"");
E 8
E 3
	s = x;

D 2
	/*try(setsockopt, (s, SOL_SOCKET, SO_DEBUG, &on, sizeof (on)), "");*/

	if (conndata) doconndata(s);

	try(connect, (s, (struct sockaddr *) to, to->siso_len), "");

E 2
I 2
	if (debug)
		try(setsockopt, (s, SOL_SOCKET, SO_DEBUG, &on, sizeof on), "");
	if (dgramp == 0) {
		if (conndata)
			doconndata(s);
I 8
		if (from) {
			try(bind,
			    (s, (struct sockaddr *)from, from->siso_len), "");
		}
E 8
		try(connect, (s, (struct sockaddr *) to, to->siso_len), "");
I 6
		recv_cdata(s);
E 6
	}
E 2
	if (selectp) {
		FD_ZERO(&writefds); FD_SET(s, &writefds);
		select(1, &writefds, 0, 0, 0);
	}
D 6
	while (count-- > 0) {
E 6
I 6
	do {
E 6
		if (size <= 0 && get_record(&flags) == EOF)
			exit(0);
		n = put_record(s, flags);
		if (n < iov->iov_len) {
D 6
			if (n==-1 && errno == 55) {
E 6
I 6
			if (n == -1 && errno == 55) {
E 6
				nobuffs++;
D 6
				count++;
E 6
I 6
				if (count) ++count;
E 6
				continue;
			}
			fprintf(stderr, "wrote %d < %d, count %d,",
						n, iov->iov_len, count);
			perror("due to");
		}
D 6
	}
E 6
I 6
	} while (count == 0 || --count >= 1);
E 6
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
	if(nobuffs) {
		printf("looped %d times waiting for bufs\n", nobuffs);
	}
}
I 6

recv_cdata(s)
int s;
{
	int x;
	iov->iov_len = 0;
	msg.msg_controllen = sizeof(cm);
	msg.msg_control = (char *)&cm;
	try(recvmsg,(s, &msg, 0), "confirm data?");
	if (msg.msg_controllen)
		dumpit("", (u_short *)&cm, msg.msg_controllen);
	msg.msg_control = 0;
	msg.msg_controllen = 0;
}

E 6
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
	bcopy(iov->iov_base, (char *)(s + 1), n);
}

D 7
checkback(s)
int s;
E 7
I 7
checkback(fd)
int fd;
E 7
{
	int n, nn;
	register struct savebuf *s = savebuf.s_next, *t;
	register char *cp = data_msg;
	while (s != &savebuf) {
		nn = s->s_n;
		do {
			msg.msg_flags = 0;
			iov->iov_len = nn;
			iov->iov_base = cp;
D 7
			n = recvmsg(s, &msg, s->s_flags);
E 7
I 7
			n = recvmsg(fd, &msg, 0);
E 7
			cp += n;
			nn -= n;
		} while (dgramp == 0 && nn > 0 && !(msg.msg_flags & MSG_EOR));
		iov->iov_base = data_msg;
		if (dgramp) {
			if (msg.msg_namelen)
				dumpit("from: ", to, msg.msg_namelen);
			msg.msg_namelen = old->siso_len;
		}
		n = s->s_n - nn;
		dbprintf("echoed %d", n);
		if (nn)
			dbprintf(" instead of %d", s->s_n);
		if (bcmp((char *)(s + 1), data_msg, n))
			dbprintf(", with mismatched data");
		if (nn && (msg.msg_flags & MSG_EOR))
			dbprintf(" and with %d unchecked after EOR", nn);
		dbprintf("\n");
		t = s; s = s->s_next; remque(t); free((char *)t);
	}
}


E 6
put_record(s, flags)
int s, flags;
{
D 6
	int fd, buflen;
E 6
	char *buf;
D 2
	struct sockaddr *to;
E 2
	int x, saved_x;

	msg.msg_flags = flags;
	if (verbose) {
D 2
		unsigned short *zp, *zlim;
E 2
		if (msg.msg_controllen) {
D 2
			zp = (unsigned short *)&(cm.cm.cmhdr.cmsg_len);
E 2
			printf("(CMessage Type is %x) ", cm.cm.cmhdr.cmsg_type);
D 2
			printf("CMsg data: ");
			x = msg.msg_controllen;
			zlim = zp + ((x + 1) / 2);
			while (zp < zlim) printf("%x ", *zp++);
			putchar ('\n');
E 2
I 2
			dumpit("CMsg data:\n", &msg.msg_control, msg.msg_controllen);
E 2
		}
		if (iov->iov_len) {
			printf("sending: %s %s",
			(flags & MSG_OOB ? "(OOB Data)" : ""),
				(flags & MSG_EOR ? "(Record Mark)" : ""));
D 2
			x = localsize;
			zp = (unsigned short *)data_msg;
			zlim = zp + ((x + 1) / 2);
			while (zp < zlim) printf("%x ", *zp++);
			putchar ('\n');
E 2
I 2
			dumpit("data: ", data_msg, localsize);
E 2
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
I 2
	if (dgramp) {
		msg.msg_name = (caddr_t)to;
		msg.msg_namelen = to->siso_len;
	}
E 2
	try(sendmsg, (s, &msg, flags), " put_record ");
	saved_x = x;
D 6
	while (verify && buflen > 0) {
		iov->iov_len = buflen;
		iov->iov_base = dupbuf;
		try(recvmsg, (s, &msg, flags), " put_record ");
I 2
		if (dgramp) {
			if (msg.msg_namelen)
				dumpit("from: ", to, msg.msg_namelen);
			msg.msg_namelen = old->siso_len;
		}
E 2
		printf("verify got %d\n", x);
		buflen -= x;
	}
E 6
I 6
	if (echop && (flags & MSG_EOR))
		checkback(s);
E 6
I 2
	bcopy(old, to, old->siso_len);
E 2
	msg.msg_control = 0;
	return (saved_x);
}
I 2
dumpit(what, where, n)
char *what; unsigned short *where; int n;
{
	unsigned short *s = where;
	unsigned short *z = where + (n+1)/2;
	int count = 0;
D 6
	if (verbose == 0)
E 6
I 6
	if (dumpnodata)
E 6
		return;
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
E 2
int *datasize = &iov->iov_len;
char *cp, *cplim;

get_control_data(type)
{

	datasize = (int *)&msg.msg_controllen;
	cp = cm.cm.cmdata;
	cplim = cp + sizeof(cm.cm.cmdata);
	cm.cm.cmhdr.cmsg_level = SOL_TRANSPORT;
	cm.cm.cmhdr.cmsg_type = type;
	msg.msg_control = cm.data;
}

doconndata(s)
{
	get_control_data(TPOPT_CONN_DATA);
	*datasize = strlen(conndata) + sizeof(cm.cm.cmhdr);
	cm.cm.cmhdr.cmsg_len = *datasize;
	bcopy(conndata, cp, *datasize);
	put_record(s, 0);
}

I 2
get_altbuf(addrbuf)
char *addrbuf;
{
	if (dgramp == 0) {
		printf("illegal option for stream\n");
		return 1;
	}
	return (scanf("%s", addrbuf) == EOF ? 1 : 0);
}
E 2

D 2

E 2
get_record(flags)
int *flags;
{
D 2
	int factor = 1, x = 0;
E 2
I 2
	int factor = 1, x = 0, newaddr = 0;
	static repeatcount, repeatsize;
E 2
	char workbuf[10240];
I 2
	char addrbuf[128];
E 2

I 2
	if (repeatcount > 0) {
		repeatcount--;
		return;
	}

E 2
	*flags = 0;
	*datasize = 0;
	datasize = &iov->iov_len;
	cp = data_msg;
	cplim  = cp + sizeof(data_msg);

	for(;;) {
		x = scanf("%s", workbuf);
		if (x == EOF)
			break;
D 2
		if (strcmp(workbuf, "disc") == 0)
E 2
I 2
		if (strcmp(workbuf, "host") == 0) {
			if (get_altbuf(addrbuf))
				break;
			to->siso_addr = *iso_addr(addrbuf);
			newaddr = 1;
		} else if (strcmp(workbuf, "Servername") == 0) {
			if (get_altbuf(Serverbuf))
				break;
			Servername = Serverbuf;
			newaddr = 1;
		} else if (strcmp(workbuf, "port") == 0) {
			x = scanf("%hd", &portnumber);
			if (x == EOF)
				break;
			Servername = 0;
			newaddr = 1;
		} else if (strcmp(workbuf, "repeat") == 0) {
			x = scanf("%d", &repeatcount);
			if (repeatcount <= 0) repeatcount = 1;
			repeatcount--;
			if (x == EOF)
				break;
		} else if (strcmp(workbuf, "disc") == 0)
E 2
			x = get_control_data(TPOPT_DISC_DATA);
		else if (strcmp(workbuf, "cfrm") == 0)
			x = get_control_data(TPOPT_CFRM_DATA);
		else if (strcmp(workbuf, "oob") == 0)
			*flags |= MSG_OOB;
		else if (strcmp(workbuf, "eom") == 0)
			*flags |= MSG_EOR;
		else if (strcmp(workbuf, "factor") == 0) {
			x = scanf("%d", &factor);
			if (factor <= 0) factor = 1;
			if (x == EOF)
				break;
		} else {
			int len = strlen(workbuf);
			localsize = 0;
			while ((factor-- > 0) &&
			       ((cp + len) < cplim)) {
					strcpy(cp, workbuf);
					cp += len;
					localsize += len;
			}
			*datasize = localsize;
			if (datasize != &iov->iov_len) {
				*datasize += sizeof(cm.cm.cmhdr);
D 2
				cm.cm.cmhdr.cmsg_len = *datasize;
E 2
I 2
				repeatsize = cm.cm.cmhdr.cmsg_len = *datasize;
E 2
			}
			break;
		}
	}
	errno = 0;
I 2
	if (newaddr)
		maketoaddr();
E 2
	return (x);
}
E 1
