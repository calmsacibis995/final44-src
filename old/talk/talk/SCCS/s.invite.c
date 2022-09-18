h51592
s 00005/00001/00156
d D 5.4 95/04/29 10:09:47 bostic 4 3
c It failed to compile on the sparc because `swapresponse' was
c ifdef'ed on vax, sun, i386 (but not sparc).  I made it pass gcc2 -Wall.
c From: Chris Torek <torek@BSDI.COM>
e
s 00005/00004/00152
d D 5.3 94/04/02 15:19:06 bostic 3 2
c put redistributable notice on it, I'm putting it in 4.4BSD-Lite
e
s 00004/00002/00152
d D 5.2 92/10/17 13:36:38 bostic 2 1
c lint to make gcc shut up
e
s 00154/00000/00000
d D 5.1 92/10/17 13:30:26 bostic 1 0
c date and time created 92/10/17 13:30:26 by bostic
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
 * Copyright (c) 1983, 1985
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
static char sccsid[] = "@(#)invite.c	5.1 (Berkeley) 6/6/85";
#endif not lint

#include "talk_ctl.h"
#include <sys/time.h>
#include <signal.h>
#include <setjmp.h>
I 4
#include <unistd.h>
E 4

/*
 * There wasn't an invitation waiting, so send a request containing
 * our sockt address to the remote talk daemon so it can invite
 * him 
 */

/*
 * The msg.id's for the invitations
 * on the local and remote machines.
 * These are used to delete the 
 * invitations.
 */
int	local_id, remote_id;
void	re_invite();
jmp_buf invitebuf;

I 4
void
E 4
invite_remote()
{
D 4
	int nfd, read_mask, template, new_sockt;
E 4
I 4
	int new_sockt;
E 4
	struct itimerval itimer;
	CTL_RESPONSE response;

	itimer.it_value.tv_sec = RING_WAIT;
	itimer.it_value.tv_usec = 0;
	itimer.it_interval = itimer.it_value;
	if (listen(sockt, 5) != 0)
		p_error("Error on attempt to listen for caller");
	msg.addr = my_addr;
	msg.id_num = -1;		/* an impossible id_num */
	invitation_waiting = 1;
	announce_invite();
	/*
	 * Shut off the automatic messages for a while,
	 * so we can use the interupt timer to resend the invitation
	 */
	end_msgs();
	setitimer(ITIMER_REAL, &itimer, (struct itimerval *)0);
	message("Waiting for your party to respond");
	signal(SIGALRM, re_invite);
	(void) setjmp(invitebuf);
	while ((new_sockt = accept(sockt, 0, 0)) < 0) {
		if (errno == EINTR)
			continue;
		p_error("Unable to connect with your party");
	}
	close(sockt);
	sockt = new_sockt;

	/*
	 * Have the daemons delete the invitations now that we
	 * have connected.
	 */
	current_state = "Waiting for your party to respond";
	start_msgs();

	msg.id_num = local_id;
	ctl_transact(my_machine_addr, msg, DELETE, &response);
	msg.id_num = remote_id;
	ctl_transact(his_machine_addr, msg, DELETE, &response);
	invitation_waiting = 0;
}

/*
 * Routine called on interupt to re-invite the callee
 */
void
re_invite()
{

	message("Ringing your party again");
	current_line++;
	/* force a re-announce */
	msg.id_num = remote_id + 1;
	announce_invite();
	longjmp(invitebuf, 1);
}

/*
 * Transmit the invitation and process the response
 */
I 4
void
E 4
announce_invite()
{
	CTL_RESPONSE response;

	current_state = "Trying to connect to your party's talk daemon";
	ctl_transact(his_machine_addr, msg, ANNOUNCE, &response);
	remote_id = response.id_num;
	if (response.answer != SUCCESS) {
		switch (response.answer) {
			
		case NOT_HERE :
			message("Your party is not logged on");
			break;

		case MACHINE_UNKNOWN :
			message("Target machine does not recognize us");
			break;

		case UNKNOWN_REQUEST :
			message("Target machine can not handle remote talk");
			break;

		case FAILED :
			message("Target machine is too confused to talk to us");
			break;

		case PERMISSION_DENIED :
			message("Your party is refusing messages");
			break;
		}
		quit();
	}
	/* leave the actual invitation on my talk daemon */
	ctl_transact(my_machine_addr, msg, LEAVE_INVITE, &response);
	local_id = response.id_num;
}
	
/*
 * Tell the daemon to remove your invitation
 */
I 4
void
E 4
send_delete()
{

	msg.type = DELETE;
	/*
	 * This is just a extra clean up, so just send it
	 * and don't wait for an answer
	 */
	msg.id_num = remote_id;
	daemon_addr.sin_addr = his_machine_addr;
D 2
	if (sendto(ctl_sockt, &msg, sizeof(CTL_MSG), 0, &daemon_addr,
E 2
I 2
	if (sendto(ctl_sockt, &msg, sizeof(CTL_MSG), 0,
	    (struct sockaddr *)&daemon_addr,
E 2
	    sizeof(daemon_addr)) != sizeof(CTL_MSG))
		perror("send_delete remote");
	msg.id_num = local_id;
	daemon_addr.sin_addr = my_machine_addr;
D 2
	if (sendto(ctl_sockt, &msg, sizeof(CTL_MSG), 0, &daemon_addr,
E 2
I 2
	if (sendto(ctl_sockt, &msg, sizeof(CTL_MSG), 0,
	    (struct sockaddr *)&daemon_addr,
E 2
	    sizeof(daemon_addr)) != sizeof(CTL_MSG))
		perror("send_delete local");
}
E 1
