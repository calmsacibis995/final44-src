h41205
s 00011/00003/00143
d D 6.5 95/04/29 10:09:48 bostic 5 4
c It failed to compile on the sparc because `swapresponse' was
c ifdef'ed on vax, sun, i386 (but not sparc).  I made it pass gcc2 -Wall.
c From: Chris Torek <torek@BSDI.COM>
e
s 00005/00004/00141
d D 6.4 94/04/02 15:19:08 bostic 4 3
c put redistributable notice on it, I'm putting it in 4.4BSD-Lite
e
s 00002/00001/00143
d D 6.3 92/10/17 13:36:41 bostic 3 2
c lint to make gcc shut up
e
s 00001/00000/00143
d D 6.2 86/07/29 09:37:22 mckusick 2 1
c fill in fields that are checked
e
s 00143/00000/00000
d D 6.1 86/07/29 09:36:02 mckusick 1 0
c date and time created 86/07/29 09:36:02 by mckusick
e
u
U
t
T
I 1
D 4
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
 * Copyright (c) 1983, 1985
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
E 4
 */

/* from "@(#)look_up.c	5.1 (Berkeley) 6/6/85"; */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint

#include "talk_ctl.h"
I 5
#include <machine/endian.h>
#include <string.h>
#include <unistd.h>
E 5

I 5
int	look_for_invite __P((CTL_RESPONSE *));
void	swapresponse __P((CTL_RESPONSE *));
E 5

/*
 * See if the local daemon has a invitation for us
 */
I 5
int
E 5
check_local()
{
	CTL_RESPONSE response;

	/* the rest of msg was set up in get_names */
	msg.ctl_addr = ctl_addr;
	/* must be initiating a talk */
	if (!look_for_invite(&response))
		return (0);
	/*
	 * There was an invitation waiting for us, 
	 * so connect with the other (hopefully waiting) party 
	 */
	current_state = "Waiting to connect with caller";
again:
	swapresponse(&response);
I 2
	response.addr.sin_family = AF_INET;
E 2
D 3
	if (connect(sockt, &response.addr, sizeof(response.addr)) != -1)
E 3
I 3
	if (connect(sockt,
	    (struct sockaddr *)&response.addr, sizeof(response.addr)) != -1)
E 3
		return (1);
	if (errno == EINTR)
		goto again;
	if (errno == ECONNREFUSED) {
		/*
		 * The caller gave up, but his invitation somehow
		 * was not cleared. Clear it and initiate an 
		 * invitation. (We know there are no newer invitations,
		 * the talkd works LIFO.)
		 */
		ctl_transact(his_machine_addr, msg, DELETE, &response);
		close(sockt);
		open_sockt();
		return (0);
	}
	p_error("Unable to connect with initiator");
	/*NOTREACHED*/
}

/*
 * Look for an invitation on 'machine'
 */
I 5
int
E 5
look_for_invite(response)
	CTL_RESPONSE *response;
{
D 5
	struct in_addr machine_addr;
E 5

	current_state = "Checking for invitation on caller's machine";
	ctl_transact(his_machine_addr, msg, LOOK_UP, response);
	/* the switch is for later options, such as multiple invitations */
	switch (response->answer) {

	case SUCCESS:
		msg.id_num = response->id_num;
		return (1);

	default :
		/* there wasn't an invitation waiting for us */
		return (0);
	}
}

/*  
 * heuristic to detect if need to reshuffle CTL_RESPONSE structure
 */

#define swapshort(a) (((a << 8) | ((unsigned short) a >> 8)) & 0xffff)
#define swaplong(a) ((swapshort(a) << 16) | (swapshort(((unsigned)a >> 16))))

D 5
#ifdef sun
E 5
I 5
#if BYTE_ORDER == BIG_ENDIAN
E 5
struct ctl_response_vax {
	char type;
	char answer;
	short junk;
	int id_num;
	struct sockaddr_in addr;
};

I 5
void
E 5
swapresponse(rsp)
	CTL_RESPONSE *rsp;
{
	struct ctl_response_vax swaprsp;
	
	if (rsp->addr.sin_family != AF_INET) {
		bcopy(rsp, &swaprsp, sizeof(CTL_RESPONSE));
		swaprsp.addr.sin_family = swapshort(swaprsp.addr.sin_family);
		if (swaprsp.addr.sin_family == AF_INET) {
			rsp->addr = swaprsp.addr;
			rsp->type = swaprsp.type;
			rsp->answer = swaprsp.answer;
			rsp->id_num = swaplong(swaprsp.id_num);
		}
	}
}
#endif

D 5
#ifdef vax
E 5
I 5
#if BYTE_ORDER == LITTLE_ENDIAN
E 5
struct ctl_response_sun {
	char type;
	char answer;
	unsigned short id_num2;
	unsigned short id_num1;
	short sin_family;
	short sin_port;
	short sin_addr2;
	short sin_addr1;
};

I 5
void
E 5
swapresponse(rsp)
	CTL_RESPONSE *rsp;
{
	struct ctl_response_sun swaprsp;
	
	if (rsp->addr.sin_family != AF_INET) {
		bcopy(rsp, &swaprsp, sizeof(struct ctl_response_sun));
		if (swaprsp.sin_family == swapshort(AF_INET)) {
			rsp->type = swaprsp.type;
			rsp->answer = swaprsp.answer;
			rsp->id_num = swapshort(swaprsp.id_num1)
			    | (swapshort(swaprsp.id_num2) << 16);
			rsp->addr.sin_family = swapshort(swaprsp.sin_family);
 			rsp->addr.sin_port = swaprsp.sin_port;
			rsp->addr.sin_addr.s_addr =
			    swaprsp.sin_addr2 | (swaprsp.sin_addr1 << 16);
		}
	}
}
#endif
E 1
