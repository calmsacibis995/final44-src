/*
 *  isis_trollutil.c,v 1.11 1993/01/07 22:40:07 jch Exp
 */

/* %(Copyright.header) */


#include "include.h"
#include "isis_includes.h"

extern int isis_snpa;
extern int errno;

short	knowTroll;
struct sockaddr_in trolladdr;

/*
 *	Create a socket to be used for transmitting datagrams to the
 *	troll process. Return fd created.
 */
int
trollTransmitSock()
{
	int	s;
	struct hostent *gethostbyname();

	if (!knowTroll) {
		struct hostent *hp;
		char name[MAXHOSTNAMELEN];

		gethostname(name, MAXHOSTNAMELEN);
		if ((hp = gethostbyname(name)) == NULL) {
			fprintf(stderr, "Can't get hostname\n");
			return(-1);
		}
		trolladdr.sin_family = AF_INET;
		bcopy(hp->h_addr, (char*)&trolladdr.sin_addr, hp->h_length);
		trolladdr.sin_port = htons(TROLL);
		knowTroll++;
	}
#ifdef __GATED__
/* we are operating in gated environment, use its socket utility */
	if ((s = task_floating_socket(isis_task,
				      task_get_socket(isis_task, AF_INET, SOCK_DGRAM, 0),
				      "trollTransmit")) < 0) {
		perror("socket");
		return(-1);
	}
#else	/* __GATED__ */
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		return(-1);
	}
#endif /* __GATED */
	return(s);
}

/*
 *	Create a socket to be used for receiving datagrams from the troll
 *	process. If path is null, create a unique name in /tmp made out of
 *	the process id. Otherwise, use path as the name. Return fd created.
 */
int
trollReceiveSock()
{
	int	s;
	struct sockaddr_in	laddr;

	if (!knowTroll) {
		struct hostent *hp;
		char name[MAXHOSTNAMELEN];

		gethostname(name, MAXHOSTNAMELEN);
		if ((hp = gethostbyname(name)) == NULL) {
			fprintf(stderr, "Can't get hostname\n");
			return(-1);
		}
		trolladdr.sin_family = AF_INET;
		bcopy(hp->h_addr, (char*)&trolladdr.sin_addr, hp->h_length);
		trolladdr.sin_port = htons(TROLL);
		knowTroll++;
	}
#ifdef __GATED__
/* we are operating in gated environment, use its socket utility */
	if ((s = task_floating_socket(isis_task,
				      task_get_socket(isis_task, AF_INET, SOCK_DGRAM, 0),
				      "trollReceive")) < 0) {
		perror("socket");
		return(-1);
	}
#else	/* __GATED__ */
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		return(-1);
	}
#endif	/* __GATED__ */
	laddr.sin_family = AF_INET;
	laddr.sin_addr.s_addr = INADDR_ANY; /* let the kernel fill this in */
	laddr.sin_port = 0;					/* let the kernel choose a port */
	if (bind(s, (struct sockaddr *)&laddr, sizeof laddr) < 0) {
			perror("bind");
	}
	{
		int len = sizeof(laddr);
		if (getsockname(s, (struct sockaddr *) &laddr, &len))
			perror("getsockname FAILS:");
		else
			printf("Listen on port %d\n", ntohs(laddr.sin_port));
	}
	return(s);
}


int
trollRecvData(fd, hdr)
int	fd;
struct NetMessage *hdr;
{
	int cc;
	struct sockaddr_in from;
	int len = sizeof(struct sockaddr_in);

	cc = recvfrom(fd, (char *)hdr, sizeof(struct NetMessage), 0,
			(struct sockaddr *)&from, &len);
	if (cc < 0)
		perror("recvfrom");
	
	return(cc);
}

/*
 *	Receive a packet from fd. Place into buf, and place from address
 *	into from. Fromlen must be the size of from. Return cc.
 */
int
trollReceive(fd, buf, buflen, from, fromlen, snpa)
int	fd;
char *buf;
int	buflen;
struct sockaddr_un	*from;
int			fromlen;
int			*snpa;
{
	int cc;
	struct NetMessage hdr;

	cc = trollRecvData(fd, &hdr);
	*snpa = hdr.snpa;
	return(cc);
}


int
trollSendData(fd, hdr, size)
int			fd;
struct NetMessage	*hdr;
int 		size;			/* Size of hdr */
{
#ifdef notdef
	int cc;
	int len = sizeof(trolladdr);
	struct netdHeader nhdr;

	nhdr.snpa = hdr->snpa;
	nhdr.subnetId = hdr->subnetId;

	check_send_trace(0,&nhdr,hdr->buf,hdr->buflen);
	{
		extern int run_from_log;
		if (run_from_log) /* don't really try to send the msg */
			return (size);
	}

	cc = sendto(fd, (char *)hdr, size, 0,
		(struct sockaddr *)&trolladdr, len);
	if (cc < 0)
		perror("trollSendData: sendto");
	
	return(cc);
#else	/* notdef */
	return(0);
#endif	/* notdef */
}


int
trollTransmit(c, macAddr, buf, buflen)
CircuitEntry	*c;
MACAddress		macAddr;
char *buf;
int	buflen;
{
	struct NetMessage hdr;

	hdr.snpa = isis_snpa;
	hdr.subnetId = c->simSubnetId;
	hdr.flags = OP_SEND;
	if (buflen > MAXNETMESSAGE) {
		fprintf(stderr, "trollTransmit: buffer to large\n");
		return(-1);
	}
	hdr.buflen = buflen;
	bcopy(buf, hdr.buf, buflen);

	trollSendData(c->fd, &hdr, sizeof(hdr));

	return 0;
}


void
trollJoinGroup(fd, subnetId)
int fd;
int	subnetId;
{
	struct NetMessage hdr;

	hdr.snpa = isis_snpa;
	hdr.subnetId = subnetId;
	hdr.flags = OP_JOIN;
	hdr.buflen = 0;

	trollSendData(fd, &hdr, sizeof(hdr));
}


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
