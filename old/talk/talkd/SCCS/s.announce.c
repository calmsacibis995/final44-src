h51697
s 00005/00004/00162
d D 5.3 94/04/02 15:23:55 bostic 3 2
c put redistributable notice on it, I'm putting it in 4.4BSD-Lite
e
s 00000/00002/00166
d D 5.2 89/04/12 12:43:01 bostic 2 1
c ANSI C sprintf
e
s 00168/00000/00000
d D 5.1 89/04/12 12:42:25 bostic 1 0
c date and time created 89/04/12 12:42:25 by bostic
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
static char sccsid[] = "@(#)announce.c	5.1 (Berkeley) 6/6/85";
#endif not lint

#include "ctl.h"

#include <sys/stat.h>
#include <sgtty.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

D 2
char *sprintf();

E 2
extern int errno;
extern char hostname[];
int nofork = 0;		/* to be set from the debugger */

/*
 * Because the tty driver insists on attaching a terminal-less
 * process to any terminal that it writes on, we must fork a child
 * to protect ourselves
 */

announce(request, remote_machine)
	CTL_MSG *request;
	char *remote_machine;
{
	int pid, val, status;

	if (nofork)
		return(announce_proc(request, remote_machine));
	if (pid = fork()) {
		/* we are the parent, so wait for the child */
		if (pid == -1)		/* the fork failed */
			return(FAILED);
		do {
			val = wait(&status);
			if (val == -1) {
				if (errno == EINTR)
					continue;
				/* shouldn't happen */
				perror("wait");
				return (FAILED);
			}
		} while (val != pid);
		if (status&0377 > 0)	/* we were killed by some signal */
			return (FAILED);
		/* Get the second byte, this is the exit/return code */
		return ((status >> 8) & 0377);
	}
	/* we are the child, go and do it */
	_exit(announce_proc(request, remote_machine));
}
	
/*
 * See if the user is accepting messages. If so, announce that 
 * a talk is requested.
 */
announce_proc(request, remote_machine)
	CTL_MSG *request;
	char *remote_machine;
{
	int pid, status;
	char full_tty[32];
	FILE *tf;
	struct stat stbuf;

	(void) sprintf(full_tty, "/dev/%s", request->r_tty);
	if (access(full_tty, 0) != 0)
		return (FAILED);
	if ((tf = fopen(full_tty, "w")) == NULL)
		return (PERMISSION_DENIED);
	/*
	 * Open gratuitously attaches the talkd to
	 * any tty it opens, so disconnect us from the
	 * tty before we catch a signal
	 */
	ioctl(fileno(tf), TIOCNOTTY, (struct sgttyb *) 0);
	if (fstat(fileno(tf), &stbuf) < 0)
		return (PERMISSION_DENIED);
	if ((stbuf.st_mode&020) == 0)
		return (PERMISSION_DENIED);
	print_mesg(tf, request, remote_machine);
	fclose(tf);
	return (SUCCESS);
}

#define max(a,b) ( (a) > (b) ? (a) : (b) )
#define N_LINES 5
#define N_CHARS 120

/*
 * Build a block of characters containing the message. 
 * It is sent blank filled and in a single block to
 * try to keep the message in one piece if the recipient
 * in in vi at the time
 */
print_mesg(tf, request, remote_machine)
	FILE *tf;
	CTL_MSG *request;
	char *remote_machine;
{
	struct timeval clock;
	struct timezone zone;
	struct tm *localtime();
	struct tm *localclock;
	char line_buf[N_LINES][N_CHARS];
	int sizes[N_LINES];
	char big_buf[N_LINES*N_CHARS];
	char *bptr, *lptr;
	int i, j, max_size;

	i = 0;
	max_size = 0;
	gettimeofday(&clock, &zone);
	localclock = localtime( &clock.tv_sec );
	sprintf(line_buf[i], " ");
	sizes[i] = strlen(line_buf[i]);
	max_size = max(max_size, sizes[i]);
	i++;
	sprintf(line_buf[i], "Message from Talk_Daemon@%s at %d:%02d ...",
	hostname, localclock->tm_hour , localclock->tm_min );
	sizes[i] = strlen(line_buf[i]);
	max_size = max(max_size, sizes[i]);
	i++;
	sprintf(line_buf[i], "talk: connection requested by %s@%s.",
		request->l_name, remote_machine);
	sizes[i] = strlen(line_buf[i]);
	max_size = max(max_size, sizes[i]);
	i++;
	sprintf(line_buf[i], "talk: respond with:  /usr/old/talk %s@%s",
		request->l_name, remote_machine);
	sizes[i] = strlen(line_buf[i]);
	max_size = max(max_size, sizes[i]);
	i++;
	sprintf(line_buf[i], " ");
	sizes[i] = strlen(line_buf[i]);
	max_size = max(max_size, sizes[i]);
	i++;
	bptr = big_buf;
	*(bptr++) = ''; /* send something to wake them up */
	*(bptr++) = '\r';	/* add a \r in case of raw mode */
	*(bptr++) = '\n';
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
	fprintf(tf, big_buf);
	fflush(tf);
	ioctl(fileno(tf), TIOCNOTTY, (struct sgttyb *) 0);
}
E 1
