h62028
s 00005/00004/00053
d D 8.2 94/04/02 15:20:51 bostic 2 1
c put redistributable notice on it, I'm putting it in 4.4BSD-Lite
e
s 00057/00000/00000
d D 8.1 94/04/02 15:20:02 bostic 1 0
c date and time created 94/04/02 15:20:02 by bostic
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
/*-
 * Copyright (c) 1983, 1985
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
E 2
 *
 *	@(#)ctl.h	5.1 (Berkeley) 6/6/85
 */

/*
 * ctl.h describes the structure that
 * talk and talkd pass back and forth.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define	NAME_SIZE	9
#define	TTY_SIZE	16
#define	HOST_NAME_LENGTH 256

#define MAX_LIFE	60	/* max time daemon saves invitations */
/* RING_WAIT should be 10's of seconds less than MAX_LIFE */
#define RING_WAIT	30	/* time to wait before refreshing invitation */

/* type values */
#define LEAVE_INVITE	0
#define LOOK_UP		1
#define DELETE		2
#define ANNOUNCE	3

/* answer values */
#define SUCCESS		0
#define NOT_HERE	1
#define FAILED		2
#define MACHINE_UNKNOWN	3
#define PERMISSION_DENIED 4
#define UNKNOWN_REQUEST	5

typedef struct ctl_response {
	char	type;
	char	answer;
	int	id_num;
	struct	sockaddr_in addr;
} CTL_RESPONSE;

typedef struct ctl_msg {
	char	type;
	char	l_name[NAME_SIZE];
	char	r_name[NAME_SIZE];
	int	id_num;
	int	pid;
	char	r_tty[TTY_SIZE];
	struct	sockaddr_in addr;
	struct	sockaddr_in ctl_addr;
} CTL_MSG;
E 1
