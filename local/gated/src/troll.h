/*
 *  $Id: troll.h,v 1.9 1992/12/07 03:17:45 jch Exp $
 */

/* %(Copyright.header) */


#ifndef TROLL_H
#define TROLL_H

#define	OP_SEND		1
#define	OP_JOIN		2
#define	OP_LEAVE	4

#define MAXNETMESSAGE 1488

typedef struct NetMessage {
	int snpa;	/* sender sets this to their own snpa */
	int subnetId;
/* HDRSZ is      snpa      + subnetId */
#define HDRSZ (sizeof(int) + sizeof(int))
	short flags;
	short buflen;
	char buf[MAXNETMESSAGE];
} NetMessage;

struct host {
	int snpa;
	u_short port;
	struct in_addr addr;
	struct host *next;
};

struct network {
	int subnetId;
	struct host *hostlist;
	struct network *next;
};

#define TROLL 0177777

#endif


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
