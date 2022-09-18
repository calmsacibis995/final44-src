/*
 *  $Id: isis_netd.h,v 1.9 1992/12/07 03:16:51 jch Exp $
 */

/* %(Copyright.header) */


#ifndef _netd_h
#define _netd_h

#define netdAddr	"/tmp/netd"

extern netdTransmitSock();
extern netdReceiveSock();
extern void netdTransmit();
extern netdReceive();

#define	MAXGROUP	100
#define	OP_SEND		1
#define	OP_JOIN		2
/* #define	OP_LEAVE	3 */

struct netdHeader {
	int					snpa;	/* fake the MAC addr here */
	int					op;
	int					subnetId;
	struct sockaddr_un	src;
};
#endif _netd_h


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
