/*
 *  $Id: isis_netdutil.c,v 1.9 1992/12/07 03:16:53 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_TIME
#include "include.h"
#include "isis_includes.h"


extern int isis_snpa;
extern int errno;

#define rcvPath	"/tmp/netd.rcv"
int		rcvFd;

/*
 *	Create a socket to be used for transmitting datagrams to the
 *	netd process. Return fd created.
 */
int
netdTransmitSock()
{
	int	s;
	if ((s = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		return(-1);
	}
	return(s);
}

/*
 *	Create a socket to be used for receiving datagrams from the netd
 *	process. If path is null, create a unique name in /tmp made out of
 *	the process id. Otherwise, use path as the name. Return fd created.
 */
int
netdReceiveSock(path)
char *path;
{
	int	s;
	struct sockaddr_un	laddr;

#ifdef __GATED__
/* we are operating in gated environment, use its socket utility */
	if ((s = task_get_socket(AF_UNIX, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		return(-1);
	}
#else	/* __GATED__ */
	if ((s = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		return(-1);
	}
#endif	/* __GATED__ */
	laddr.sun_family = AF_UNIX;
	if (path == NULL) {
		char	buf[100];
#ifdef PROTO_ISIS
		sprintf(buf, "/tmp/netd.%d", isis_snpa);
#else
		sprintf(buf, "/tmp/netd.%d", getpid());
#endif
		strcpy(laddr.sun_path, buf);
	} else {
		strcpy(laddr.sun_path, path);
	}

	if (bind(s, &laddr, sizeof(laddr))) {
		if (errno == EADDRINUSE) {
			unlink(laddr.sun_path);
			if (bind(s, &laddr, sizeof(laddr)))
				perror("bind");
		} else {
			perror("bind");
		}
	}
	return(s);
}

int
netdRecvData(fd, hdr, buf, buflen, from)
int	fd;
struct netdHeader *hdr;
char *buf;
int	buflen;
struct sockaddr_un	*from;
{
	int cc;
	struct msghdr msghdr;
	struct iovec iovec[2];

	bzero((caddr_t)&msghdr, sizeof(msghdr));
	msghdr.msg_name = (caddr_t)from;
	msghdr.msg_namelen = sizeof(struct sockaddr_un);
	msghdr.msg_iov = iovec;
	msghdr.msg_iovlen = 2;

	iovec[0].iov_base = (caddr_t)hdr;
	iovec[0].iov_len = sizeof(struct netdHeader);
	iovec[1].iov_base = buf;
	iovec[1].iov_len = buflen;

	if ((cc = recvmsg(fd, &msghdr, 0)) < 0)
		perror("recvmsg");
	
	*from = hdr->src;
	return(cc);
}

/*
 *	Receive a packet from fd. Place into buf, and place from address
 *	into from. Fromlen must be the size of from. Return cc.
 */
int
netdReceive(fd, buf, buflen, from, fromlen, snpa)
int	fd;
char *buf;
int	buflen;
struct sockaddr_un	*from;
int			fromlen;
int			*snpa;
{
	int cc;
	struct netdHeader hdr;

	cc = netdRecvData(fd, &hdr, buf, buflen, from);
	*snpa = hdr.snpa;
	return(cc);
}

int
netdSendData(fd, to, hdr, buf, buflen)
int			fd;
struct sockaddr_un	*to;
struct netdHeader	*hdr;
char		*buf;
int			buflen;
{
	int cc;
	struct msghdr msghdr;
	struct iovec iovec[2];

	bzero((caddr_t)&msghdr, sizeof(msghdr));

	msghdr.msg_name = (caddr_t)to;
	msghdr.msg_namelen = sizeof(struct sockaddr_un);
	msghdr.msg_iov = iovec;

	msghdr.msg_iovlen = 1;
	iovec[0].iov_base = (caddr_t)hdr;
	iovec[0].iov_len = sizeof(struct netdHeader);

	if (buf) {
		iovec[1].iov_base = buf;
		iovec[1].iov_len = buflen;
		msghdr.msg_iovlen++;
	}
	check_send_trace(hdr->subnetId,hdr,buf,buflen);
	{
		extern int run_from_log;
		if (run_from_log) /* don't really try to send the msg */
			return (buflen + sizeof(*hdr));
	}
	if ((cc = sendmsg(fd, &msghdr, 0)) < 0)
		perror("netdSendData: sendmsg");
	
	return(cc);
}

void
netdTransmit(fd, subnetId, path, buf, buflen)
int	fd;
int subnetId;
char *path;
char *buf;
int	buflen;
{
	struct sockaddr_un	to;
	struct netdHeader hdr;

	to.sun_family = AF_UNIX;
	if (path == NULL)
		strcpy(to.sun_path, netdAddr);
	else
		strcpy(to.sun_path, path);

#ifdef PROTO_ISIS
	sprintf(hdr.src.sun_path, "/tmp/netd.%d", isis_snpa);
	hdr.snpa = isis_snpa;
#else
	sprintf(hdr.src.sun_path, "/tmp/netd.%d", getpid());
	hdr.snpa = getpid();
#endif
	hdr.subnetId = subnetId;
	hdr.op = OP_SEND;

	netdSendData(fd, &to, &hdr, buf, buflen);
}


void
netdJoinGroup(fd, subnetId)
int fd;
int	subnetId;
{
	struct sockaddr_un	to;
	struct netdHeader hdr;

	to.sun_family = AF_UNIX;
	strcpy(to.sun_path, netdAddr);

#ifdef PROTO_ISIS
	sprintf(hdr.src.sun_path, "/tmp/netd.%d", isis_snpa);
	hdr.snpa = isis_snpa;
#else
	sprintf(hdr.src.sun_path, "/tmp/netd.%d", getpid());
	hdr.snpa = getpid();
#endif
	hdr.subnetId = subnetId;
	hdr.op = OP_JOIN;

	netdSendData(fd, &to, &hdr, NULL, 0);
}


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
