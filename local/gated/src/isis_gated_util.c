/*
 *  isis_gated_util.c,v 1.11 1993/01/07 22:39:20 jch Exp
 */

/* %(Copyright.header) */


#define	INCLUDE_IF
#include "include.h"
#include "isis_includes.h"

#if (_BSD > 43) || (BSD > 43)

extern int run_from_log; /* suppress output under simulation */

void
ReceiveSock __PF1(tp, task *)
{
#define	SOCKETBUF (64*1024)

	tp->task_socket = task_get_socket(tp, AF_ISO, SOCK_DGRAM, ISOPROTO_ESIS);
	if (tp->task_socket < 0) {
		task_quit(errno);
	}
	if (task_set_option(tp, TASKOPTION_RECVBUF, min(task_maxpacket, SOCKETBUF)) < 0) {
		task_quit(errno);
	}
	if (task_set_option(tp, TASKOPTION_SENDBUF, min(task_maxpacket, SOCKETBUF)) < 0) {
		task_quit(errno);
	}
	if (task_set_option(tp, TASKOPTION_NONBLOCKING, TRUE) < 0) {
		task_quit(errno);
	}
}

int
Transmit(c, macAddr, buf, len)
CircuitEntry	*c;
MACAddress	macAddr;
u_char		*buf;
int		len;
{
	struct sockaddr_dl whereto;
	struct sockaddr_dl *to = &whereto;
	int cc;

	/* set up destination information */
	bzero( (char *)&whereto, sizeof(struct sockaddr));
	to->sdl_family = AF_LINK;
	to->sdl_index = c->kernindex;
	to->sdl_nlen = 0;
	to->sdl_alen = sizeof(MACAddress);
	bcopy((char *)macAddr, (char *)LLADDR(to), sizeof(MACAddress));
	to->sdl_len = sizeof(whereto);

	if (run_from_log)
		return(0); /* do nothing */
	/*
	{
		int pinoped;
		printf("TRANSMIT BUFFER:\n");
		for (pinoped=0;pinoped<len;pinoped++) printf("%02x ",buf[pinoped]);
		printf("\n");
	}
	*/
	cc = sendto(c->fd, buf, len, 0, (struct sockaddr *) &whereto, sizeof(whereto));
	if ( cc < 0)
		perror("sendto");

	return(0);
}

int
RecvData(fd,indx,buf,buflen,src)
int fd;
int *indx;
char *buf;
int buflen;
MACAddress src;
{
	struct sockaddr_dl from;
	int len, fromlen = sizeof(from);

	len = recvfrom(fd, buf, buflen, 0, (struct sockaddr *) &from, &fromlen);
	if (len >= 0) {
		*indx = from.sdl_index;
		bzero((caddr_t) src, sizeof(MACAddress));
		bcopy((caddr_t) LLADDR(&from), (caddr_t) src, sizeof(MACAddress));
	}
	return(len);
}
#else /* dummy stubs */
void
ReceiveSock(){}
int
Transmit __PF0(void)
{
return(0);
}
void
RecvData(){}
#endif	/* (_BSD > 43) */


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
