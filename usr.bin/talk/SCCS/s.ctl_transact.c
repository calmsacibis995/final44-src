h64084
s 00002/00002/00085
d D 8.1 93/06/06 16:31:08 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00002/00079
d D 5.8 91/03/01 19:06:06 bostic 11 10
c ANSI, local include files shouldn't include include files
e
s 00001/00011/00080
d D 5.7 90/06/01 17:43:32 bostic 10 9
c new copyright notice
e
s 00000/00013/00091
d D 5.6 89/08/16 12:18:59 karels 9 8
c there aren't sa_len's in the packet, don't keep putting them in
c and taking them out
e
s 00013/00000/00091
d D 5.5 89/05/08 11:46:04 kfall 8 7
c zero out sa_len field when sending out on net (hack!)
e
s 00010/00005/00081
d D 5.4 88/06/29 20:22:14 bostic 7 6
c install approved copyright notice
e
s 00009/00003/00077
d D 5.3 88/05/20 12:36:58 bostic 6 5
c add Berkeley specific header
e
s 00021/00024/00059
d D 5.2 86/03/13 17:40:15 mckusick 5 4
c new version from sam@monet.berkeley.edu
e
s 00007/00001/00076
d D 5.1 85/06/06 09:17:02 dist 4 3
c Add copyright
e
s 00004/00004/00073
d D 1.3 85/06/03 12:21:29 bloom 3 2
c fix select problem 
e
s 00063/00083/00014
d D 1.2 84/04/11 15:13:28 karels 2 1
c reformatting; convert daemon for inetd; add keywords
e
s 00097/00000/00000
d D 1.1 84/04/11 15:02:47 karels 1 0
c date and time created 84/04/11 15:02:47 by karels
e
u
U
t
T
I 4
/*
D 12
 * Copyright (c) 1983 Regents of the University of California.
D 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
D 10
 * Redistribution and use in source and binary forms are permitted
D 7
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 7
I 7
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 7
E 6
 */

E 4
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif
E 4
I 4
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6
E 4

E 2
I 1
D 11
#include "talk_ctl.h"
E 11
I 11
#include <sys/types.h>
#include <sys/socket.h>
E 11
#include <sys/time.h>
I 11
#include <netinet/in.h>
#include <protocols/talkd.h>
#include <errno.h>
#include "talk_ctl.h"
E 11

D 2
#define CTL_WAIT 2	/* the amount of time to wait for a 
			   response, in seconds */
E 2
I 2
#define CTL_WAIT 2	/* time to wait for a response, in seconds */
E 2

D 2

    /*
     * SOCKDGRAM is unreliable, so we must repeat messages if we have
     * not recieved an acknowledgement within a reasonable amount
     * of time
     */

E 2
I 2
/*
 * SOCKDGRAM is unreliable, so we must repeat messages if we have
 * not recieved an acknowledgement within a reasonable amount
 * of time
 */
E 2
D 5
ctl_transact(target, msg, type, response)
E 5
I 5
ctl_transact(target, msg, type, rp)
E 5
D 2
struct in_addr target;
CTL_MSG msg;
int type;
CTL_RESPONSE *response;
E 2
I 2
	struct in_addr target;
	CTL_MSG msg;
	int type;
D 5
	CTL_RESPONSE *response;
E 5
I 5
	CTL_RESPONSE *rp;
E 5
E 2
{
D 2
    struct sockaddr junk;
    int read_mask;
    int ctl_mask;
    int nready;
    int cc;
    int junk_size;
    struct timeval wait;
E 2
I 2
D 5
	struct sockaddr junk;
	int read_mask;
	int ctl_mask;
	int nready;
	int cc;
	int junk_size;
E 5
I 5
	int read_mask, ctl_mask, nready, cc;
E 5
	struct timeval wait;
E 2

D 2
    wait.tv_sec = CTL_WAIT;
    wait.tv_usec = 0;
E 2
I 2
D 3
	wait.tv_sec = CTL_WAIT;
	wait.tv_usec = 0;
E 3
	msg.type = type;
	daemon_addr.sin_addr = target;
	daemon_addr.sin_port = daemon_port;
	ctl_mask = 1 << ctl_sockt;
E 2

D 2
    msg.type = type;

    daemon_addr.sin_addr = target;
    daemon_addr.sin_port = daemon_port;

    ctl_mask = 1 << ctl_sockt;

E 2
	/*
D 5
	 * keep sending the message until a response of the right
	 * type is obtained
E 5
I 5
	 * Keep sending the message until a response of
	 * the proper type is obtained.
E 5
	 */
D 2
    do {
	    /* keep sending the message until a response is obtained */

E 2
	do {
I 3
		wait.tv_sec = CTL_WAIT;
		wait.tv_usec = 0;
D 5

E 3
D 2
	    cc = sendto(ctl_sockt, (char *)&msg, sizeof(CTL_MSG), 0,
			&daemon_addr, sizeof(daemon_addr));

	    if (cc != sizeof(CTL_MSG)) {
		if (errno == EINTR) {
			/* we are returning from an interupt */
		    continue;
		} else {
		    p_error("Error on write to talk daemon");
		}
	    }

	    read_mask = ctl_mask;

	    while ((nready = select(32, &read_mask, 0, 0, &wait)) < 0) {
		if (errno == EINTR) {
			/* we are returning from an interupt */
		    continue;
		} else {
		    p_error("Error on waiting for response from daemon");
		}
	    }
	} while (nready == 0);

	    /* keep reading while there are queued messages 
	       (this is not necessary, it just saves extra
	       request/acknowledgements being sent)
	     */

	do {

	    junk_size = sizeof(junk);
	    cc = recvfrom(ctl_sockt, (char *) response,
			   sizeof(CTL_RESPONSE), 0, &junk, &junk_size );
	    if (cc < 0) {
		if (errno == EINTR) {
		    continue;
		}
		p_error("Error on read from talk daemon");
	    }

	    read_mask = ctl_mask;

		/* an immediate poll */

	    timerclear(&wait);
	    nready = select(32, &read_mask, 0, 0, &wait);

	} while ( nready > 0 && response->type != type);

    } while (response->type != type);
E 2
I 2
		/* keep sending the message until a response is obtained */
E 5
I 5
		/* resend message until a response is obtained */
E 5
		do {
I 8
D 9
#ifdef	MSG_EOR
			/*
			 * New sockaddr structure has 1st 8bits as
			 * length field.  We have to zero these out
			 * to be compatible with old talkd's (yech)
			 */
			msg.addr.sa_len = 0;
			msg.ctl_addr.sa_len = 0;
#endif
E 9
E 8
D 5
			cc = sendto(ctl_sockt, (char *)&msg, sizeof(CTL_MSG), 0,
				&daemon_addr, sizeof(daemon_addr));
			if (cc != sizeof(CTL_MSG)) {
E 5
I 5
			cc = sendto(ctl_sockt, (char *)&msg, sizeof (msg), 0,
D 11
				&daemon_addr, sizeof (daemon_addr));
E 11
I 11
			    (struct sockaddr *)&daemon_addr,
			    sizeof (daemon_addr));
E 11
I 8
D 9
#ifdef	MSG_EOR
			msg.addr.sa_len = sizeof(struct sockaddr_in);
			msg.ctl_addr.sa_len = sizeof(struct sockaddr_in);
#endif
E 9
E 8
			if (cc != sizeof (msg)) {
E 5
				if (errno == EINTR)
					continue;
				p_error("Error on write to talk daemon");
			}
			read_mask = ctl_mask;
D 3
			nready = select(32, &read_mask, 0, 0, &wait);
			while (nready < 0) {
E 3
I 3
D 5
			if ((nready = select(32, &read_mask, 0, 0, &wait)) < 0) {
E 5
I 5
			nready = select(32, &read_mask, 0, 0, &wait);
			if (nready < 0) {
E 5
E 3
				if (errno == EINTR)
					continue;
				p_error("Error waiting for daemon response");
			}
		} while (nready == 0);
D 5
		/* keep reading while there are queued messages 
		   (this is not necessary, it just saves extra
		   request/acknowledgements being sent)
E 5
I 5
		/*
		 * Keep reading while there are queued messages 
		 * (this is not necessary, it just saves extra
		 * request/acknowledgements being sent)
E 5
		 */
		do {
D 5
			junk_size = sizeof(junk);
			cc = recvfrom(ctl_sockt, (char *)response,
			    sizeof (CTL_RESPONSE), 0, &junk, &junk_size);
E 5
I 5
			cc = recv(ctl_sockt, (char *)rp, sizeof (*rp), 0);
E 5
			if (cc < 0) {
				if (errno == EINTR)
					continue;
				p_error("Error on read from talk daemon");
			}
			read_mask = ctl_mask;
			/* an immediate poll */
			timerclear(&wait);
			nready = select(32, &read_mask, 0, 0, &wait);
D 5
		} while (nready > 0 && response->type != type);
	} while (response->type != type);
E 5
I 5
		} while (nready > 0 && (rp->vers != TALK_VERSION ||
		    rp->type != type));
	} while (rp->vers != TALK_VERSION || rp->type != type);
	rp->id_num = ntohl(rp->id_num);
	rp->addr.sa_family = ntohs(rp->addr.sa_family);
E 5
E 2
}
E 1
