h48364
s 00007/00004/00129
d D 8.3 95/04/28 16:11:59 bostic 18 17
c basically you can screw with people's terminals by replacing the
c remote user name with escape codes and the like.  This change
c vis(3)ifies that the remote user name before displaying it.
c From: Adam Glass <glass@NetBSD.ORG>
e
s 00002/00001/00131
d D 8.2 94/01/07 15:15:43 bostic 17 16
c sprintf->snprintf, remove duplicate '/' in file name
e
s 00002/00002/00130
d D 8.1 93/06/04 19:06:22 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00131
d D 5.12 91/11/06 08:27:16 bostic 15 14
c don't terminate with a period, then cut and paste doesn't work
e
s 00006/00001/00126
d D 5.11 91/08/01 16:49:40 marc 14 12
c make timeout dependent on RING_WAIT so as to not stack up
e
s 00006/00001/00126
d R 5.11 91/08/01 16:47:33 marc 13 12
c make timeout dependent on RING_WAIT (time when client will try re-inviting the callee)
e
s 00014/00055/00113
d D 5.10 91/08/01 16:37:21 marc 12 11
c use ttymsg.c from wall(1) for notifying user (doesn't fork unless it has to)
e
s 00007/00007/00161
d D 5.9 91/02/26 11:40:11 bostic 11 10
c ANSI fixes (one real bug!)
e
s 00001/00011/00167
d D 5.8 90/06/01 15:55:17 bostic 10 9
c new copyright notice
e
s 00002/00001/00176
d D 5.7 89/05/11 14:33:44 bostic 9 8
c file reorg, pathnames.h, paths.h
e
s 00010/00005/00167
d D 5.6 88/06/18 14:10:38 bostic 8 7
c install approved copyright notice
e
s 00009/00003/00163
d D 5.5 88/05/20 11:53:28 bostic 7 6
c add Berkeley specific header
e
s 00006/00006/00160
d D 5.4 87/10/22 11:18:37 bostic 6 5
c ANSI C; sprintf now returns an int.
e
s 00001/00001/00165
d D 5.3 86/03/13 18:05:03 mckusick 5 4
c setgid to group "write" so that terminals need not be world writable
e
s 00016/00018/00150
d D 5.2 86/03/13 17:12:49 mckusick 4 3
c new version from sam@monet.berkeley.edu
e
s 00007/00001/00161
d D 5.1 85/06/06 09:16:16 dist 3 2
c Add copyright
e
s 00114/00160/00048
d D 1.2 84/04/11 15:13:05 karels 2 1
c reformatting; convert daemon for inetd; add keywords
e
s 00208/00000/00000
d D 1.1 84/04/11 15:02:40 karels 1 0
c date and time created 84/04/11 15:02:40 by karels
e
u
U
t
T
I 3
/*
D 16
 * Copyright (c) 1983 Regents of the University of California.
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
D 10
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 8
E 7
 */

E 3
I 1
D 2
/* $Header: /a/guest/moore/talk/RCS/announce.c,v 1.8 83/07/06 00:16:57 moore Exp $ */
E 2
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif
E 3
I 3
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7
E 3
E 2

D 4
#include "ctl.h"

E 4
I 4
#include <sys/types.h>
I 12
#include <sys/uio.h>
E 12
E 4
#include <sys/stat.h>
D 11
#include <sgtty.h>
#include <sys/ioctl.h>
E 11
#include <sys/time.h>
D 11
#include <stdio.h>
E 11
#include <sys/wait.h>
I 11
#include <sys/socket.h>
#include <protocols/talkd.h>
#include <sgtty.h>
E 11
#include <errno.h>
I 4
#include <syslog.h>
E 4
D 11

D 4
char *sprintf();
E 4
I 4
#include <protocols/talkd.h>
E 11
I 11
#include <unistd.h>
#include <stdio.h>
#include <string.h>
I 18
#include <vis.h>
E 18
E 11
I 9
#include <paths.h>
E 9
E 4

D 4
extern int errno;
extern char hostname[];
int nofork = 0;		/* to be set from the debugger */
E 4
I 4
D 11
extern	int errno;
extern	char hostname[];
E 11
I 11
extern char hostname[];
E 11
E 4

/*
I 4
 * Announce an invitation to talk.
D 12
 *
E 4
 * Because the tty driver insists on attaching a terminal-less
 * process to any terminal that it writes on, we must fork a child
 * to protect ourselves
E 12
 */
D 4

E 4
D 12
announce(request, remote_machine)
D 2
CTL_MSG *request;
char *remote_machine;
E 2
I 2
	CTL_MSG *request;
	char *remote_machine;
E 2
{
D 2
    int pid, val, status;
E 2
I 2
	int pid, val, status;
E 2

D 2
    if (nofork) {
	return(announce_proc(request, remote_machine));
    }

    if ( pid = fork() ) {

	    /* we are the parent, so wait for the child */

	if (pid == -1) {
		/* the fork failed */
	    return(FAILED);
E 2
I 2
D 4
	if (nofork)
		return(announce_proc(request, remote_machine));
E 4
	if (pid = fork()) {
		/* we are the parent, so wait for the child */
		if (pid == -1)		/* the fork failed */
D 4
			return(FAILED);
E 4
I 4
			return (FAILED);
E 4
		do {
			val = wait(&status);
			if (val == -1) {
				if (errno == EINTR)
					continue;
				/* shouldn't happen */
D 4
				perror("wait");
E 4
I 4
				syslog(LOG_WARNING, "announce: wait: %m");
E 4
				return (FAILED);
			}
		} while (val != pid);
		if (status&0377 > 0)	/* we were killed by some signal */
			return (FAILED);
		/* Get the second byte, this is the exit/return code */
		return ((status >> 8) & 0377);
E 2
	}
D 2

	do {
	    val = wait(&status);
	    if (val == -1) {
		if (errno == EINTR) {
		    continue;
		} else {
			/* shouldn't happen */
		    print_error("wait");
		    return(FAILED);
		}
	    }
	} while (val != pid);

	if (status&0377 > 0) {
		/* we were killed by some signal */
	    return(FAILED);
	}

	    /* Get the second byte, this is the exit/return code */

	return((status>>8)&0377);

    } else {
	    /* we are the child, go and do it */
E 2
I 2
	/* we are the child, go and do it */
E 2
	_exit(announce_proc(request, remote_machine));
D 2
    }
E 2
}
E 12
	
D 2

    /* See if the user is accepting messages. If so, announce that 
       a talk is requested.
     */

E 2
I 2
/*
 * See if the user is accepting messages. If so, announce that 
 * a talk is requested.
 */
E 2
D 12
announce_proc(request, remote_machine)
E 12
I 12
announce(request, remote_machine)
E 12
D 2
CTL_MSG *request;
char *remote_machine;
E 2
I 2
	CTL_MSG *request;
	char *remote_machine;
E 2
{
D 2
    int pid, status;
    char full_tty[32];
    FILE *tf;
    struct stat stbuf;
E 2
I 2
D 12
	int pid, status;
E 12
	char full_tty[32];
	FILE *tf;
	struct stat stbuf;
E 2

D 2

    (void) sprintf(full_tty, "/dev/%s", request->r_tty);

    if (access(full_tty, 0) != 0) {
	return(FAILED);
    }

    if ((tf = fopen(full_tty, "w")) == NULL) {
	return(PERMISSION_DENIED);
    }

	/* open gratuitously attaches the talkd to
	   any tty it opens, so disconnect us from the
	   tty before we catch a signal */

    ioctl(fileno(tf), TIOCNOTTY, (struct sgttyb *) 0);

    if (fstat(fileno(tf), &stbuf) < 0) {
	return(PERMISSION_DENIED);
    }

    if ((stbuf.st_mode&02) == 0) {
	return(PERMISSION_DENIED);
    }

    print_mesg(tf, request, remote_machine);
    fclose(tf);
    return(SUCCESS);
E 2
I 2
D 4
	(void) sprintf(full_tty, "/dev/%s", request->r_tty);
E 4
I 4
D 6
	sprintf(full_tty, "/dev/%s", request->r_tty);
E 6
I 6
D 9
	(void)sprintf(full_tty, "/dev/%s", request->r_tty);
E 9
I 9
D 17
	(void)sprintf(full_tty, "%s/%s", _PATH_DEV, request->r_tty);
E 17
I 17
	(void)snprintf(full_tty, sizeof(full_tty),
	    "%s%s", _PATH_DEV, request->r_tty);
E 17
E 9
E 6
E 4
D 12
	if (access(full_tty, 0) != 0)
		return (FAILED);
	if ((tf = fopen(full_tty, "w")) == NULL)
E 12
I 12
	if (stat(full_tty, &stbuf) < 0 || (stbuf.st_mode&020) == 0)
E 12
		return (PERMISSION_DENIED);
D 12
	/*
D 4
	 * Open gratuitously attaches the talkd to
	 * any tty it opens, so disconnect us from the
	 * tty before we catch a signal
E 4
I 4
	 * On first tty open, the server will have
	 * it's pgrp set, so disconnect us from the
	 * tty before we catch a signal.
E 4
	 */
	ioctl(fileno(tf), TIOCNOTTY, (struct sgttyb *) 0);
	if (fstat(fileno(tf), &stbuf) < 0)
		return (PERMISSION_DENIED);
D 5
	if ((stbuf.st_mode&02) == 0)
E 5
I 5
	if ((stbuf.st_mode&020) == 0)
E 5
		return (PERMISSION_DENIED);
	print_mesg(tf, request, remote_machine);
	fclose(tf);
	return (SUCCESS);
E 12
I 12
	return (print_mesg(request->r_tty, tf, request, remote_machine));
E 12
E 2
}

#define max(a,b) ( (a) > (b) ? (a) : (b) )
#define N_LINES 5
D 18
#define N_CHARS 120
E 18
I 18
#define N_CHARS 256
E 18

D 2
    /*
     * build a block of characters containing the message. 
     * It is sent blank filled and in a single block to
     * try to keep the message in one piece if the recipient
     * in in vi at the time
     */

E 2
I 2
/*
 * Build a block of characters containing the message. 
 * It is sent blank filled and in a single block to
 * try to keep the message in one piece if the recipient
 * in in vi at the time
 */
E 2
D 12
print_mesg(tf, request, remote_machine)
E 12
I 12
print_mesg(tty, tf, request, remote_machine)
	char *tty;
E 12
D 2
FILE *tf;
CTL_MSG *request;
char *remote_machine;
E 2
I 2
	FILE *tf;
	CTL_MSG *request;
	char *remote_machine;
E 2
{
D 2
    struct timeval clock;
    struct timezone zone;
    struct tm *localtime();
    struct tm *localclock;
    char line_buf[N_LINES][N_CHARS];
    int sizes[N_LINES];
    char big_buf[N_LINES*N_CHARS];
    char *bptr, *lptr;
    int i, j, max_size;
E 2
I 2
	struct timeval clock;
	struct timezone zone;
	struct tm *localtime();
	struct tm *localclock;
I 12
	struct iovec iovec;
E 12
	char line_buf[N_LINES][N_CHARS];
	int sizes[N_LINES];
	char big_buf[N_LINES*N_CHARS];
D 12
	char *bptr, *lptr;
E 12
I 12
D 18
	char *bptr, *lptr, *ttymsg();
E 18
I 18
	char *bptr, *lptr, *vis_user;
E 18
E 12
	int i, j, max_size;
E 2

D 2
    i = 0;
    max_size = 0;

    gettimeofday(&clock, &zone);
    localclock = localtime( &clock.tv_sec );

    sprintf(line_buf[i], " ");

    sizes[i] = strlen(line_buf[i]);
    max_size = max(max_size, sizes[i]);
    i++;

    sprintf(line_buf[i], "Message from Talk_Daemon@%s at %d:%02d ...",
E 2
I 2
	i = 0;
	max_size = 0;
	gettimeofday(&clock, &zone);
	localclock = localtime( &clock.tv_sec );
D 6
	sprintf(line_buf[i], " ");
E 6
I 6
	(void)sprintf(line_buf[i], " ");
E 6
	sizes[i] = strlen(line_buf[i]);
	max_size = max(max_size, sizes[i]);
	i++;
D 6
	sprintf(line_buf[i], "Message from Talk_Daemon@%s at %d:%02d ...",
E 6
I 6
	(void)sprintf(line_buf[i], "Message from Talk_Daemon@%s at %d:%02d ...",
E 6
E 2
	hostname, localclock->tm_hour , localclock->tm_min );
D 2

    sizes[i] = strlen(line_buf[i]);
    max_size = max(max_size, sizes[i]);
    i++;

    sprintf(line_buf[i], "talk: connection requested by %s@%s.",
E 2
I 2
	sizes[i] = strlen(line_buf[i]);
	max_size = max(max_size, sizes[i]);
	i++;
I 18
	vis_user = (char *) malloc(strlen(request->l_name) * 4 + 1);
	strvis(vis_user, request->l_name, VIS_CSTYLE);
E 18
D 6
	sprintf(line_buf[i], "talk: connection requested by %s@%s.",
E 6
I 6
D 15
	(void)sprintf(line_buf[i], "talk: connection requested by %s@%s.",
E 15
I 15
	(void)sprintf(line_buf[i], "talk: connection requested by %s@%s",
E 15
E 6
E 2
D 18
		request->l_name, remote_machine);
E 18
I 18
		vis_user, remote_machine);
E 18
D 2

    sizes[i] = strlen(line_buf[i]);
    max_size = max(max_size, sizes[i]);
    i++;

    sprintf(line_buf[i], "talk: respond with:  talk %s@%s",
E 2
I 2
	sizes[i] = strlen(line_buf[i]);
	max_size = max(max_size, sizes[i]);
	i++;
D 6
	sprintf(line_buf[i], "talk: respond with:  talk %s@%s",
E 6
I 6
	(void)sprintf(line_buf[i], "talk: respond with:  talk %s@%s",
E 6
E 2
D 18
		request->l_name, remote_machine);
E 18
I 18
		vis_user, remote_machine);
E 18
D 2

    sizes[i] = strlen(line_buf[i]);
    max_size = max(max_size, sizes[i]);
    i++;

    sprintf(line_buf[i], " ");

    sizes[i] = strlen(line_buf[i]);
    max_size = max(max_size, sizes[i]);
    i++;

    bptr = big_buf;
    *(bptr++) = '';	/* send something to wake them up */
    *(bptr++) = '\r';	/* add a \r in case of raw mode */
    *(bptr++) = '\n';
    for(i = 0; i < N_LINES; i++) {

	    /* copy the line into the big buffer */

	lptr = line_buf[i];
	while (*lptr != '\0') {
	    *(bptr++) = *(lptr++);
	}

	    /* pad out the rest of the lines with blanks */

	for(j = sizes[i]; j < max_size + 2; j++) {
	    *(bptr++) = ' ';
	}

E 2
I 2
	sizes[i] = strlen(line_buf[i]);
	max_size = max(max_size, sizes[i]);
	i++;
D 6
	sprintf(line_buf[i], " ");
E 6
I 6
	(void)sprintf(line_buf[i], " ");
E 6
	sizes[i] = strlen(line_buf[i]);
	max_size = max(max_size, sizes[i]);
	i++;
	bptr = big_buf;
D 4
	*(bptr++) = ''; /* send something to wake them up */
E 2
	*(bptr++) = '\r';	/* add a \r in case of raw mode */
	*(bptr++) = '\n';
E 4
I 4
	*bptr++ = ''; /* send something to wake them up */
	*bptr++ = '\r';	/* add a \r in case of raw mode */
	*bptr++ = '\n';
E 4
D 2
    }
    *bptr = '\0';

    fprintf(tf, big_buf);
    fflush(tf);
    ioctl(fileno(tf), TIOCNOTTY, (struct sgttyb *) 0);
E 2
I 2
	for (i = 0; i < N_LINES; i++) {
		/* copy the line into the big buffer */
		lptr = line_buf[i];
		while (*lptr != '\0')
			*(bptr++) = *(lptr++);
		/* pad out the rest of the lines with blanks */
		for (j = sizes[i]; j < max_size + 2; j++)
			*(bptr++) = ' ';
		*(bptr++) = '\r';	/* add a \r in case of raw mode */
		*(bptr++) = '\n';
	}
	*bptr = '\0';
D 12
	fprintf(tf, big_buf);
	fflush(tf);
	ioctl(fileno(tf), TIOCNOTTY, (struct sgttyb *) 0);
E 12
I 12
	iovec.iov_base = big_buf;
	iovec.iov_len = bptr - big_buf;
D 14
	if (ttymsg(&iovec, 1, tty, 30) != NULL)
E 14
I 14
	/*
	 * we choose a timeout of RING_WAIT-5 seconds so that we don't
	 * stack up processes trying to write messages to a tty
	 * that is permanently blocked.
	 */
	if (ttymsg(&iovec, 1, tty, RING_WAIT - 5) != NULL)
E 14
		return (FAILED);

	return (SUCCESS);
E 12
E 2
}
E 1
