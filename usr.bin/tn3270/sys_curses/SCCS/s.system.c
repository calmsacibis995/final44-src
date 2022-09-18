h01585
s 00002/00002/00725
d D 8.1 93/06/06 16:52:55 bostic 25 24
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00724
d D 4.5 91/04/26 16:01:21 bostic 24 23
c new copyright; att/bsd/shared
e
s 00005/00004/00732
d D 4.4 91/03/06 00:20:29 donn 23 22
c Don't use mktemp() on constants.
e
s 00007/00000/00729
d D 4.3 89/09/02 16:08:46 minshall 22 21
c Utilize apitrace.
e
s 00009/00004/00720
d D 4.2 89/05/30 22:53:51 minshall 21 20
c Don't complain if !-escape entered, but no API using command is run.
e
s 00000/00000/00724
d D 4.1 88/12/04 15:12:28 minshall 20 19
c Release 4.1
e
s 00002/00000/00722
d D 3.5 88/09/14 20:45:25 minshall 19 18
c Sun's of older vintage don't know about uid_t (sigh).
e
s 00055/00031/00667
d D 3.4 88/08/28 17:59:35 minshall 18 17
c Lint (and new copyrights).
e
s 00009/00018/00689
d D 3.3 88/03/28 11:55:25 bostic 17 16
c add Berkeley specific headers
e
s 00005/00001/00702
d D 3.2 88/01/05 15:01:03 minshall 16 15
c Changes for pyramid from sbanner1@cheops (S. John Banner).
e
s 00000/00000/00703
d D 3.1 87/08/11 10:20:09 minshall 15 14
c New version numbering.
e
s 00025/00000/00678
d D 1.14 87/07/17 10:04:37 minshall 14 13
c Install sccs headers and copyright notices.
e
s 00002/00002/00676
d D 1.13 87/07/15 15:26:35 minshall 13 12
c New directory structure.
e
s 00007/00000/00671
d D 1.12 87/07/15 14:11:46 minshall 12 11
c Make transparent output and input work.
e
s 00124/00055/00547
d D 1.11 87/07/09 10:37:29 minshall 11 10
c Fixes to keep from having to enter password all the time.
e
s 00013/00000/00589
d D 1.10 87/07/09 09:36:29 minshall 10 9
c Allow for compilation on 4.2 systems.
e
s 00008/00012/00581
d D 1.9 87/06/16 17:17:00 minshall 9 8
c Make things more consistent (server vs. client) and more logical.
e
s 00029/00021/00564
d D 1.8 87/06/16 12:40:59 minshall 8 7
c Performance enhancement.
e
s 00013/00009/00572
d D 1.7 87/06/15 23:32:49 minshall 7 6
c Some bug fixes, formatting changes, and larger access buffer.
e
s 00039/00028/00542
d D 1.6 87/06/15 14:54:26 minshall 6 5
c Add DISASSOCIATE request.  Name changes.
e
s 00030/00022/00540
d D 1.5 87/06/15 09:22:40 minshall 5 4
c This version works with ../apilib/test.c
e
s 00107/00055/00455
d D 1.4 87/06/12 13:53:06 minshall 4 3
c This version accepts connections from the other side.
e
s 00113/00177/00397
d D 1.3 87/06/12 08:48:02 minshall 3 2
c This version compiles; some stuff moved to ../apilib/api_exch.c.
e
s 00503/00005/00071
d D 1.2 87/06/11 11:48:32 minshall 2 1
c This version compiles with the API stuff in it.
e
s 00076/00000/00000
d D 1.1 87/06/09 20:46:54 minshall 1 0
c date and time created 87/06/09 20:46:54 by minshall
e
u
U
t
T
I 14
D 24
/*
D 17
 *	Copyright (c) 1984-1987 by the Regents of the
 *	University of California and by Gregory Glenn Minshall.
E 17
I 17
 * Copyright (c) 1988 Regents of the University of California.
E 24
I 24
/*-
D 25
 * Copyright (c) 1988 The Regents of the University of California.
E 24
 * All rights reserved.
E 25
I 25
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 25
E 17
 *
D 17
 *	Permission to use, copy, modify, and distribute these
 *	programs and their documentation for any purpose and
 *	without fee is hereby granted, provided that this
 *	copyright and permission appear on all copies and
 *	supporting documentation, the name of the Regents of
 *	the University of California not be used in advertising
 *	or publicity pertaining to distribution of the programs
 *	without specific prior permission, and notice be given in
 *	supporting documentation that copying and distribution is
 *	by permission of the Regents of the University of California
 *	and by Gregory Glenn Minshall.  Neither the Regents of the
 *	University of California nor Gregory Glenn Minshall make
 *	representations about the suitability of this software
 *	for any purpose.  It is provided "as is" without
 *	express or implied warranty.
E 17
I 17
D 24
 * Redistribution and use in source and binary forms are permitted
D 18
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 18
I 18
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
E 24
I 24
 * %sccs.include.redist.c%
E 24
E 18
E 17
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 17
#endif	/* not lint */
E 17
I 17
#endif /* not lint */
E 17

E 14
I 2
#include <sys/types.h>
I 12

D 16
#if	!defined(sun)
E 16
I 16
#if     defined(pyr)
#define fd_set fdset_t
#endif  /* defined(pyr) */

D 21
#if	!defined(sun) && !defined(pyr)
E 16
E 12
I 11
#include <sys/inode.h>
I 12
#else	/* !defined(sun) */
E 21
I 21
/*
 * Wouldn't it be nice if these REALLY were in <sys/inode.h>?  Or,
 * equivalently, if <sys/inode.h> REALLY existed?
 */
E 21
#define	IREAD	00400
#define	IWRITE	00200
D 21
#endif	/* !defined(sun) */
E 21

E 12
#include <sys/file.h>
#include <sys/time.h>
E 11
#include <sys/socket.h>
#include <netinet/in.h>
E 2
I 1
#include <sys/wait.h>

I 2
#include <errno.h>
extern int errno;

#include <netdb.h>
#include <signal.h>
E 2
#include <stdio.h>
I 23
#include <string.h>
E 23
I 2
#include <pwd.h>
E 2

#include "../general/general.h"
D 13
#include "../api/api.h"
I 2
D 3
#include "api_exch.h"
E 3
I 3
#include "../apilib/api_exch.h"
E 13
I 13
#include "../ctlr/api.h"
#include "../api/api_exch.h"
E 13
E 3
E 2

#include "../general/globals.h"

I 10
#ifndef	FD_SETSIZE
/*
 * The following is defined just in case someone should want to run
 * this telnet on a 4.2 system.
 *
 */
E 10

I 10
#define	FD_SET(n, p)	((p)->fds_bits[0] |= (1<<(n)))
#define	FD_CLR(n, p)	((p)->fds_bits[0] &= ~(1<<(n)))
#define	FD_ISSET(n, p)	((p)->fds_bits[0] & (1<<(n)))
#define FD_ZERO(p)	((p)->fds_bits[0] = 0)

#endif

E 10
static int shell_pid = 0;
I 11
static char key[50];			/* Actual key */
static char *keyname;			/* Name of file with key in it */
E 11

I 2
static char *ourENVlist[200];		/* Lots of room */

D 4
static int sock = -1;
E 4
I 4
static int
    sock = -1,				/* Connected socket */
    serversock;				/* Server (listening) socket */
E 4

static enum { DEAD, UNCONNECTED, CONNECTED } state;

I 18
static long
    storage_location;		/* Address we have */
static short
    storage_length = 0;		/* Length we have */
E 18
E 2
static int
I 2
D 3
    storage_address,		/* Address we have */
E 3
I 3
D 18
    storage_location,		/* Address we have */
E 3
    storage_length = 0,		/* Length we have */
E 18
    storage_must_send = 0,	/* Storage belongs on other side of wire */
    storage_accessed = 0;	/* The storage is accessed (so leave alone)! */

D 7
static long storage[250];
E 7
I 7
static long storage[1000];
E 7

D 3
union REGS inputRegs;
struct SREGS inputSregs;
E 3
I 3
static union REGS inputRegs;
static struct SREGS inputSregs;
E 3

I 22
extern int apitrace;
E 22
I 3

static void
E 3
kill_connection()
{
D 4
    state = DEAD;
    (void) close(sock);
    sock = -1;
E 4
I 4
    state = UNCONNECTED;
    if (sock != -1) {
	(void) close(sock);
	sock = -1;
    }
E 4
}


static int
E 2
D 3
child_died()
{
    union wait *status;
I 2
    register int pid;
E 2

D 2
    while ((pid = wait3(status, WNOHANG, 0)) > 0) {
E 2
I 2
    while ((pid = wait3(&status, WNOHANG, 0)) > 0) {
E 2
	if (pid == shell_pid) {
I 2
	    char inputbuffer[100];

E 2
	    shell_active = 0;
I 2
	    if (sock != -1) {
		(void) close(sock);
		sock = -1;
		printf("[Hit return to continue]");
		fflush(stdout);
		(void) gets(inputbuffer);
		setconnmode();
		ConnectScreen();	/* Turn screen on (if need be) */
	    }
E 2
	}
    }
    signal(SIGCHLD, child_died);
}

I 2
static int
nextchar()
{
    unsigned char c;

    if (read(sock, &c, 1) != 1) {
	return -1;
    } else {
	return c;
    }
}

static int
checktype(type)
int type;
{
    int was;

    if ((was = nextchar()) != type) {
	fprintf(stderr, "Wrong type of data.  Should be 0x%02x, was 0x%02x.\n",
		type, was);
	return -1;
    } else {
	return 0;
    }
}


static int
fill(where, length)
char	*where;
int	length;
{
    while (length) {
	int i;

	if ((i = read(sock, where, length)) < 0) {
	    perror("read");
	    return -1;
	} else {
	    length -= i;
	    where += i;
	}
    }
}


static int
nextlength()
{
    short length;

    if (fill(&length, sizeof length) == -1) {
	return -1;
    } else {
	return ntohs(length);
    }
}


static int
nextaddress()
{
    long address;

    return fill(&address, sizeof address);
}



static int
nextbytes(type, where, length)
int	type;
char	*where;
int	length;
{
    int was;

    if (checktype(type) == -1) {
	return -1;
    }
    if ((was = nextlength()) != length) {
	fprintf(stderr, "Type 0x%02x had bad length.  Should be %d, was %d.\n",
		type, length, was);
	return -1;
    } else {
	return fill(where, length);
    }
}

static int
E 3
nextstore()
{
D 3
    if (nextchar() != EXCH_HEREIS) {
E 3
I 3
    struct storage_descriptor sd;

D 5
    if (api_exch_incommand(EXCH_HEREIS) == -1) {
E 3
	fprintf(stderr, "Bad data from other side.\n");
	fprintf(stderr, "(Encountered at %s, %s.)\n", __FILE__, __LINE__);
	return -1;
    }
E 5
D 3
    if ((storage_address = nextaddress()) == -1) {
E 3
I 3
    if (api_exch_intype(EXCH_TYPE_STORE_DESC, sizeof sd, (char *)&sd) == -1) {
E 3
	storage_length = 0;
	return -1;
    }
D 3
    if ((storage_length = nextlength()) > sizeof storage) {
E 3
I 3
D 11
    storage_length = ntohs(sd.length);
    storage_location = ntohl(sd.location);
E 11
I 11
    storage_length = sd.length;
    storage_location = sd.location;
E 11
    if (storage_length > sizeof storage) {
E 3
	fprintf(stderr, "API client tried to send too much storage (%d).\n",
		storage_length);
I 3
	storage_length = 0;
E 3
	return -1;
    }
D 3
    return fill((char *)storage, storage_length);
E 3
I 3
D 5
    if (api_exch_intype(EXCH_TYPE_BYTES, storage_length, (char *)storage) == -1) {
	storage_length = 0;
	return -1;
E 5
I 5
D 9
    if (storage_length != 0) {
	if (api_exch_intype(EXCH_TYPE_BYTES, storage_length, (char *)storage)
							    == -1) {
	    storage_length = 0;
	    return -1;
	}
E 9
I 9
    if (api_exch_intype(EXCH_TYPE_BYTES, storage_length, (char *)storage)
							== -1) {
	storage_length = 0;
	return -1;
E 9
E 5
    }
I 5
    return 0;
E 5
E 3
}


static int
doreject(message)
char	*message;
{
I 3
    struct storage_descriptor sd;
E 3
    int length = strlen(message);
D 3
    char buffer[100];
E 3

D 3
    length = htons(length);
    sprintf(buffer, "%c%c%c%s", EXCH_REJECTED, length>>8, length&0xff, buffer);
    if (write(sock, buffer, length+3) != length+3) {
	perror("writing API socket");
E 3
I 3
D 6
    if (api_exch_outcommand(EXCH_REJECTED) == -1) {
E 6
I 6
    if (api_exch_outcommand(EXCH_CMD_REJECTED) == -1) {
E 6
E 3
	return -1;
    }
I 3
D 11
    sd.length = htons(length);
E 11
I 11
    sd.length = length;
E 11
D 4
    if (api_exch_outtype(EXCH_TYPE_BYTES, sizeof sd, (char *)&sd) == -1) {
E 4
I 4
    if (api_exch_outtype(EXCH_TYPE_STORE_DESC, sizeof sd, (char *)&sd) == -1) {
E 4
	return -1;
    }
    if (api_exch_outtype(EXCH_TYPE_BYTES, length, message) == -1) {
	return -1;
    }
E 3
    return 0;
}


E 2
/*
I 2
D 4
 * doconnect()
E 4
I 4
 * doassociate()
E 4
 *
 * Negotiate with the other side and try to do something.
I 11
 *
 * Returns:
 *
 *	-1:	Error in processing
 *	 0:	Invalid password entered
 *	 1:	Association OK
E 11
 */

static int
D 4
doconnect()
E 4
I 4
doassociate()
E 4
{
    struct passwd *pwent;
    char
	promptbuf[100],
	buffer[200];
D 3
    int promptlen, passwdlen;
E 3
D 18
    int length;
    int was;
E 18
I 3
    struct storage_descriptor sd;
I 18
    extern char *crypt();
E 18
E 3

D 11
    if ((pwent = getpwuid(geteuid())) == 0) {
	return -1;
    }
    sprintf(promptbuf, "Enter password for user %s:", pwent->pw_name);
D 3
    promptlen = strlen(promptbuf);
    passwdlen = strlen(pwent->pw_name);
    sprintf(buffer, "%c%c%c%s%c%c%s", EXCH_SEND_AUTH,
		promptlen>>8, promptlen&0xff, promptbuf,
		passwdlen>>8, passwdlen&0xff, pwent->pw_name);
    length = strlen(buffer);
    if (write(sock, buffer, length) != length) {
	perror("write to API socket");
E 3
I 3
D 4
    api_exch_outcommand(EXCH_SEND_AUTH);
    api_exch_outtype(EXCH_TYPE_BYTES, strlen(promptbuf), promptbuf);
    api_exch_outtype(EXCH_TYPE_BYTES, strlen(pwent->pw_name), pwent->pw_name);
E 4
I 4
D 6
    if (api_exch_outcommand(EXCH_SEND_AUTH) == -1) {
E 6
I 6
    if (api_exch_outcommand(EXCH_CMD_SEND_AUTH) == -1) {
E 6
	return -1;
    }
    sd.length = htons(strlen(promptbuf));
    if (api_exch_outtype(EXCH_TYPE_STORE_DESC, sizeof sd, (char *)&sd) == -1) {
	return -1;
    }
    if (api_exch_outtype(EXCH_TYPE_BYTES, strlen(promptbuf), promptbuf) == -1) {
	return -1;
    }
    sd.length = htons(strlen(pwent->pw_name));
    if (api_exch_outtype(EXCH_TYPE_STORE_DESC, sizeof sd, (char *)&sd) == -1) {
	return -1;
    }
    if (api_exch_outtype(EXCH_TYPE_BYTES,
			strlen(pwent->pw_name), pwent->pw_name) == -1) {
	return -1;
    }
E 4
D 6
    if (api_exch_incommand(EXCH_AUTH) == -1) {
E 6
I 6
    if (api_exch_incommand(EXCH_CMD_AUTH) == -1) {
E 6
E 3
	return -1;
    }
E 11
D 3
    if ((was = nextchar()) != EXCH_AUTH) {
	fprintf(stderr,
	    "API client sent command 0x%02x when EXCH_AUTH expected.\n", was);
E 3
I 3
    if (api_exch_intype(EXCH_TYPE_STORE_DESC, sizeof sd, (char *)&sd) == -1) {
	return -1;
E 3
    }
D 3
    if ((length = nextlength()) > sizeof buffer) {
E 3
I 3
D 11
    sd.length = ntohs(sd.length);
E 11
I 11
    sd.length = sd.length;
E 11
    if (sd.length > sizeof buffer) {
E 3
D 11
	doreject("Password entered was too long");
E 11
I 11
	doreject("(internal error) Authentication key too long");
E 11
D 4
	return 0;
E 4
I 4
	return -1;
E 4
    }
D 3
    if (fill(buffer, length) == -1) {
E 3
I 3
    if (api_exch_intype(EXCH_TYPE_BYTES, sd.length, buffer) == -1) {
E 3
	return -1;
    }
D 3
    buffer[length] = 0;
E 3
I 3
    buffer[sd.length] = 0;
E 3

D 11
    /* Is this the correct password? */
I 4
    if (strlen(pwent->pw_name)) {
	char *ptr;
	int i;
E 11
I 11
    if (strcmp(buffer, key) != 0) {
I 19
#if	(!defined(sun)) || defined(BSD) && (BSD >= 43)
E 19
D 18
	if ((pwent = getpwuid(geteuid())) == 0) {
E 18
I 18
	extern uid_t geteuid();
I 19
#endif	/* (!defined(sun)) || defined(BSD) && (BSD >= 43) */
E 19

	if ((pwent = getpwuid((int)geteuid())) == 0) {
E 18
	    return -1;
	}
	sprintf(promptbuf, "Enter password for user %s:", pwent->pw_name);
	if (api_exch_outcommand(EXCH_CMD_SEND_AUTH) == -1) {
	    return -1;
	}
	sd.length = strlen(promptbuf);
	if (api_exch_outtype(EXCH_TYPE_STORE_DESC, sizeof sd, (char *)&sd)
									== -1) {
	    return -1;
	}
	if (api_exch_outtype(EXCH_TYPE_BYTES, strlen(promptbuf), promptbuf)
									== -1) {
	    return -1;
	}
	sd.length = strlen(pwent->pw_name);
	if (api_exch_outtype(EXCH_TYPE_STORE_DESC, sizeof sd, (char *)&sd)
									== -1) {
	    return -1;
	}
	if (api_exch_outtype(EXCH_TYPE_BYTES,
			    strlen(pwent->pw_name), pwent->pw_name) == -1) {
	    return -1;
	}
	if (api_exch_incommand(EXCH_CMD_AUTH) == -1) {
	    return -1;
	}
	if (api_exch_intype(EXCH_TYPE_STORE_DESC, sizeof sd, (char *)&sd)
									== -1) {
	    return -1;
	}
	sd.length = sd.length;
	if (sd.length > sizeof buffer) {
	    doreject("Password entered was too long");
	    return -1;
	}
	if (api_exch_intype(EXCH_TYPE_BYTES, sd.length, buffer) == -1) {
	    return -1;
	}
	buffer[sd.length] = 0;
E 11

D 11
	ptr = pwent->pw_name;
	i = 0;
	while (i < sd.length) {
	    buffer[i++] ^= *ptr++;
	    if (*ptr == 0) {
		ptr = pwent->pw_name;
E 11
I 11
	/* Is this the correct password? */
	if (strlen(pwent->pw_name)) {
	    char *ptr;
	    int i;

	    ptr = pwent->pw_name;
	    i = 0;
	    while (i < sd.length) {
		buffer[i++] ^= *ptr++;
		if (*ptr == 0) {
		    ptr = pwent->pw_name;
		}
E 11
	    }
	}
D 11
    }
E 4
    if (strcmp(crypt(buffer, pwent->pw_passwd), pwent->pw_passwd) == 0) {
D 3
	char code = EXCH_CONNECTED;
	if (write(sock, &code, 1) != 1) {
	    perror("writing to API socket");
	    return -1;
	}
E 3
I 3
D 4
	api_exch_outcommand(EXCH_CONNECTED);
E 4
I 4
D 6
	if (api_exch_outcommand(EXCH_ASSOCIATED) == -1) {
E 6
I 6
	if (api_exch_outcommand(EXCH_CMD_ASSOCIATED) == -1) {
E 6
	    return -1;
I 5
	} else {
	    return 1;
E 11
I 11
	if (strcmp(crypt(buffer, pwent->pw_passwd), pwent->pw_passwd) != 0) {
	    doreject("Invalid password");
	    sleep(10);		/* Don't let us do too many of these */
	    return 0;
E 11
E 5
	}
I 11
    }
    if (api_exch_outcommand(EXCH_CMD_ASSOCIATED) == -1) {
	return -1;
E 11
E 4
E 3
    } else {
D 11
	doreject("Invalid password");
	sleep(10);		/* Don't let us do too many of these */
I 5
	return 0;
E 11
I 11
	return 1;
E 11
E 5
    }
D 5
    return 0;
E 5
}


void
freestorage()
{
D 3
    int i, j;
E 3
D 18
    char buffer[40];
E 18
I 3
    struct storage_descriptor sd;
E 3

    if (storage_accessed) {
	fprintf(stderr, "Internal error - attempt to free accessed storage.\n");
D 7
	fprintf(stderr, "(Enountered in file %s at line %s.)\n",
E 7
I 7
	fprintf(stderr, "(Encountered in file %s at line %d.)\n",
E 7
			__FILE__, __LINE__);
	quit();
    }
    if (storage_must_send == 0) {
	return;
    }
    storage_must_send = 0;
D 3
    i = htonl(storage_address);
    j = htonl(storage_length);
    sprintf(buffer, "%c%c%c%c%c%c%c",
		EXCH_HEREIS, i>>24, i>>16, i>>8, i, j>>8, j);
    if (write(sock, buffer, 5) != 5) {
	perror("writing to API socket");
E 3
I 3
D 6
    if (api_exch_outcommand(EXCH_HEREIS) == -1) {
E 6
I 6
    if (api_exch_outcommand(EXCH_CMD_HEREIS) == -1) {
E 6
E 3
	kill_connection();
	return;
    }
D 3
    if (write(sock, (char *)storage, storage_length) != storage_length) {
	perror("writing to API socket");
E 3
I 3
D 11
    sd.length = htons(storage_length);
    sd.location = htonl(storage_location);
E 11
I 11
    sd.length = storage_length;
    sd.location = storage_location;
E 11
    if (api_exch_outtype(EXCH_TYPE_STORE_DESC, sizeof sd, (char *)&sd) == -1) {
E 3
	kill_connection();
	return;
    }
I 3
D 5
    if (api_exch_outtype(EXCH_TYPE_BYTES, storage_length, (char *)storage) == -1) {
	kill_connection();
	return;
E 5
I 5
D 9
    if (storage_length != 0) {
	if (api_exch_outtype(EXCH_TYPE_BYTES, storage_length, (char *)storage)
								== -1) {
	    kill_connection();
	    return;
	}
E 9
I 9
    if (api_exch_outtype(EXCH_TYPE_BYTES, storage_length, (char *)storage)
							    == -1) {
	kill_connection();
	return;
E 9
E 5
    }
E 3
}


D 3
void
E 3
I 3
static int
E 3
D 8
getstorage(address, length)
E 8
I 8
getstorage(address, length, copyin)
I 18
long
    address;
E 18
int
D 18
    address,
E 18
    length,
    copyin;
E 8
{
D 3
    int i, j;
E 3
I 3
    struct storage_descriptor sd;
E 3
D 18
    char buffer[40];
E 18

    freestorage();
    if (storage_accessed) {
	fprintf(stderr,
		"Internal error - attempt to get while storage accessed.\n");
D 7
	fprintf(stderr, "(Enountered in file %s at line %s.)\n",
E 7
I 7
	fprintf(stderr, "(Encountered in file %s at line %d.)\n",
E 7
			__FILE__, __LINE__);
	quit();
    }
D 5
    if (storage_must_send == 0) {
	return;
    }
E 5
    storage_must_send = 0;
D 3
    i = htonl(storage_address);
    j = htonl(storage_length);
    sprintf(buffer, "%c%c%c%c%c%c%c",
		EXCH_GIMME, i>>24, i>>16, i>>8, i, j>>8, j);
    if (write(sock, buffer, 5) != 5) {
	perror("writing to API socket");
E 3
I 3
D 6
    if (api_exch_outcommand(EXCH_GIMME) == -1) {
E 6
I 6
    if (api_exch_outcommand(EXCH_CMD_GIMME) == -1) {
E 6
E 3
	kill_connection();
D 3
	return;
E 3
I 3
	return -1;
E 3
    }
I 5
    storage_location = address;
    storage_length = length;
E 5
I 3
D 8
    sd.location = htonl(storage_location);
    sd.length = htons(storage_length);
    if (api_exch_outtype(EXCH_TYPE_STORE_DESC, sizeof sd, (char *)&sd) == -1) {
	kill_connection();
	return -1;
E 8
I 8
    if (copyin) {
D 11
	sd.location = htonl(storage_location);
	sd.length = htons(storage_length);
E 11
I 11
D 18
	sd.location = storage_location;
E 18
I 18
	sd.location = (long)storage_location;
E 18
	sd.length = storage_length;
E 11
	if (api_exch_outtype(EXCH_TYPE_STORE_DESC,
					sizeof sd, (char *)&sd) == -1) {
	    kill_connection();
	    return -1;
	}
	if (api_exch_incommand(EXCH_CMD_HEREIS) == -1) {
	    fprintf(stderr, "Bad data from other side.\n");
	    fprintf(stderr, "(Encountered at %s, %d.)\n", __FILE__, __LINE__);
	    return -1;
	}
	if (nextstore() == -1) {
	    kill_connection();
	    return -1;
	}
E 8
    }
I 5
D 6
    if (api_exch_incommand(EXCH_HEREIS) == -1) {
E 6
I 6
D 8
    if (api_exch_incommand(EXCH_CMD_HEREIS) == -1) {
E 6
	fprintf(stderr, "Bad data from other side.\n");
D 7
	fprintf(stderr, "(Encountered at %s, %s.)\n", __FILE__, __LINE__);
E 7
I 7
	fprintf(stderr, "(Encountered at %s, %d.)\n", __FILE__, __LINE__);
E 7
	return -1;
    }
E 5
E 3
    if (nextstore() == -1) {
	kill_connection();
D 3
	return;
E 3
I 3
	return -1;
E 3
    }
E 8
I 3
    return 0;
E 3
}

I 18
/*ARGSUSED*/
E 18
void
movetous(local, es, di, length)
char
    *local;
D 18
int
E 18
I 18
unsigned int
E 18
    es,
    di;
int
    length;
{
I 18
    long where = SEG_OFF_BACK(es, di);

E 18
    if (length > sizeof storage) {
	fprintf(stderr, "Internal API error - movetous() length too long.\n");
	fprintf(stderr, "(detected in file %s, line %d)\n", __FILE__, __LINE__);
	quit();
    } else if (length == 0) {
	return;
    }
D 8
    getstorage(di, length);
E 8
I 8
D 18
    getstorage(di, length, 1);
E 8
D 3
    memcpy(local, storage+(di-storage_address), length);
E 3
I 3
    memcpy(local, storage+(di-storage_location), length);
E 18
I 18
    getstorage(where, length, 1);
    memcpy(local, (char *)(storage+((where-storage_location))), length);
I 22
    if (apitrace) {
	Dump('(', local, length);
    }
E 22
E 18
E 3
}

I 18
/*ARGSUSED*/
E 18
void
movetothem(es, di, local, length)
D 18
int
E 18
I 18
unsigned int
E 18
    es,
    di;
char
    *local;
int
    length;
{
I 18
    long where = SEG_OFF_BACK(es, di);

E 18
    if (length > sizeof storage) {
	fprintf(stderr, "Internal API error - movetothem() length too long.\n");
	fprintf(stderr, "(detected in file %s, line %d)\n", __FILE__, __LINE__);
	quit();
    } else if (length == 0) {
	return;
    }
    freestorage();
    memcpy((char *)storage, local, length);
I 22
    if (apitrace) {
	Dump(')', local, length);
    }
E 22
    storage_length = length;
D 3
    storage_address = di;
E 3
I 3
D 18
    storage_location = di;
E 18
I 18
    storage_location = where;
E 18
E 3
    storage_must_send = 1;
}


char *
D 8
access_api(location, length)
E 8
I 8
access_api(location, length, copyin)
I 18
char *
    location;
E 18
E 8
int
D 18
    location,
E 18
D 8
    length;
E 8
I 8
    length,
    copyin;			/* Do we need to copy in initially? */
E 8
{
    if (storage_accessed) {
	fprintf(stderr, "Internal error - storage accessed twice\n");
D 7
	fprintf(stderr, "(Encountered in file %s, line %s.)\n",
E 7
I 7
	fprintf(stderr, "(Encountered in file %s, line %d.)\n",
E 7
				__FILE__, __LINE__);
	quit();
    } else if (length != 0) {
D 7
	storage_accessed = 1;
E 7
	freestorage();
D 8
	getstorage(location, length);
E 8
I 8
D 18
	getstorage(location, length, copyin);
E 18
I 18
	getstorage((long)location, length, copyin);
E 18
E 8
I 7
	storage_accessed = 1;
E 7
    }
    return (char *) storage;
}

I 18
/*ARGSUSED*/
void
E 18
D 8
unaccess_api(location, local, length)
E 8
I 8
unaccess_api(location, local, length, copyout)
E 8
D 18
int	location;
E 18
I 18
char 	*location;
E 18
char	*local;
int	length;
I 18
int	copyout;
E 18
{
    if (storage_accessed == 0) {
	fprintf(stderr, "Internal error - unnecessary unaccess_api call.\n");
D 7
	fprintf(stderr, "(Encountered in file %s, line %s.)\n",
E 7
I 7
	fprintf(stderr, "(Encountered in file %s, line %d.)\n",
E 7
			__FILE__, __LINE__);
	quit();
    }
    storage_accessed = 0;
D 8
    storage_must_send = 1;	/* Needs to go back */
E 8
I 8
    storage_must_send = copyout;	/* if needs to go back */
E 8
}

I 4
/*
 * Accept a connection from an API client, aborting if the child dies.
 */
E 4

I 4
static int
doconnect()
{
    fd_set fdset;
    int i;

    sock = -1;
    FD_ZERO(&fdset);
    while (shell_active && (sock == -1)) {
	FD_SET(serversock, &fdset);
D 18
	if ((i = select(serversock+1, &fdset, 0, 0, 0)) < 0) {
E 18
I 18
	if ((i = select(serversock+1, &fdset,
		    (fd_set *)0, (fd_set *)0, (struct timeval *)0)) < 0) {
E 18
	    if (errno = EINTR) {
		continue;
	    } else {
		perror("in select waiting for API connection");
		return -1;
	    }
	} else {
D 18
	    i = accept(serversock, 0, 0);
E 18
I 18
	    i = accept(serversock, (struct sockaddr *)0, (int *)0);
E 18
	    if (i == -1) {
		perror("accepting API connection");
		return -1;
	    }
	    sock = i;
	}
    }
    /* If the process has already exited, we may need to close */
    if ((shell_active == 0) && (sock != -1)) {
I 18
	extern void setcommandmode();

E 18
	(void) close(sock);
	sock = -1;
	setcommandmode();	/* In case child_died sneaked in */
    }
I 18
    return 0;
E 18
}

E 4
/*
E 2
 * shell_continue() actually runs the command, and looks for API
 * requests coming back in.
 *
 * We are called from the main loop in telnet.c.
 */

int
shell_continue()
{
I 6
    int i;

E 6
I 2
    switch (state) {
    case DEAD:
	pause();			/* Nothing to do */
	break;
    case UNCONNECTED:
D 3
	if (nextchar() != EXCH_CONNECT) {
E 3
I 3
D 4
	if (api_exch_incommand(EXCH_CONNECT) == -1) {
E 4
I 4
	if (doconnect() == -1) {
I 21
	    kill_connection();
	    return -1;
	}
	/* At this point, it is possible that we've gone away */
	if (shell_active == 0) {
E 21
E 4
E 3
	    kill_connection();
D 4
	} else {
	    switch (doconnect()) {
	    case -1:
E 4
I 4
	    return -1;
	}
D 6
	if (api_exch_init(sock, "client") == -1) {
E 6
I 6
	if (api_exch_init(sock, "server") == -1) {
E 6
	    return -1;
	}
	while (state == UNCONNECTED) {
D 6
	    if (api_exch_incommand(EXCH_ASSOCIATE) == -1) {
E 6
I 6
	    if (api_exch_incommand(EXCH_CMD_ASSOCIATE) == -1) {
E 6
E 4
		kill_connection();
D 4
		break;
	    case 0:
		break;
	    case 1:
		state = CONNECTED;
E 4
I 4
		return -1;
	    } else {
		switch (doassociate()) {
		case -1:
		    kill_connection();
		    return -1;
		case 0:
		    break;
		case 1:
		    state = CONNECTED;
		}
E 4
	    }
	}
	break;
    case CONNECTED:
D 3
	if (nextchar() == EXCH_REQUEST) {
	    /* Eat up request packet. */
	    nextbytes(&inputRegs, sizeof inputRegs);
	    nextbytes(&inputSregs, sizeof inputSregs);
	    nextstore();		/* Initial storage sent */
	    handle_api(&inputRegs, &inputSregs);
	} else {
E 3
I 3
D 6
	if (api_exch_incommand(EXCH_REQUEST) == -1) {
E 3
	    kill_connection();
I 3
D 5
	} else if (api_exch_intype(EXCH_TYPE_BYTES, sizeof inputRegs,
E 5
I 5
	} else if (api_exch_intype(EXCH_TYPE_REGS, sizeof inputRegs,
E 5
				(char *)&inputRegs) == -1) {
	    kill_connection();
D 5
	} else if (api_exch_intype(EXCH_TYPE_BYTES, sizeof inputSregs,
E 5
I 5
	} else if (api_exch_intype(EXCH_TYPE_SREGS, sizeof inputSregs,
E 5
				(char *)&inputSregs) == -1) {
	    kill_connection();
	} else if (nextstore() == -1) {
	    kill_connection();
	} else {
	    handle_api(&inputRegs, &inputSregs);
	    freestorage();			/* Send any storage back */
	    if (api_exch_outcommand(EXCH_REPLY) == -1) {
E 6
I 6
	switch (i = api_exch_nextcommand()) {
	case EXCH_CMD_REQUEST:
	    if (api_exch_intype(EXCH_TYPE_REGS, sizeof inputRegs,
				    (char *)&inputRegs) == -1) {
E 6
		kill_connection();
D 5
	    } else if (api_exch_outtype(EXCH_TYPE_BYTES, sizeof inputRegs,
E 5
I 5
D 6
	    } else if (api_exch_outtype(EXCH_TYPE_REGS, sizeof inputRegs,
E 5
				(char *)&inputRegs) == -1) {
E 6
I 6
	    } else if (api_exch_intype(EXCH_TYPE_SREGS, sizeof inputSregs,
				    (char *)&inputSregs) == -1) {
E 6
		kill_connection();
D 5
	    } else if (api_exch_outtype(EXCH_TYPE_BYTES, sizeof inputSregs,
E 5
I 5
D 6
	    } else if (api_exch_outtype(EXCH_TYPE_SREGS, sizeof inputSregs,
E 5
				(char *)&inputSregs) == -1) {
E 6
I 6
	    } else if (nextstore() == -1) {
E 6
		kill_connection();
I 6
	    } else {
		handle_api(&inputRegs, &inputSregs);
		freestorage();			/* Send any storage back */
		if (api_exch_outcommand(EXCH_CMD_REPLY) == -1) {
		    kill_connection();
		} else if (api_exch_outtype(EXCH_TYPE_REGS, sizeof inputRegs,
				    (char *)&inputRegs) == -1) {
		    kill_connection();
		} else if (api_exch_outtype(EXCH_TYPE_SREGS, sizeof inputSregs,
				    (char *)&inputSregs) == -1) {
		    kill_connection();
		}
		/* Done, and it all worked! */
E 6
	    }
D 6
	    /* Done, and it all worked! */
E 6
I 6
	    break;
	case EXCH_CMD_DISASSOCIATE:
	    kill_connection();
	    break;
	default:
D 7
	    fprintf(stderr, "Looking for a REQUEST or DISASSOCIATE command\n");
	    fprintf(stderr, "\treceived 0x%02x.\n", i);
E 7
I 7
	    if (i != -1) {
		fprintf(stderr,
			"Looking for a REQUEST or DISASSOCIATE command\n");
		fprintf(stderr, "\treceived 0x%02x.\n", i);
	    }
E 7
	    kill_connection();
I 7
	    break;
E 7
E 6
E 3
	}
    }
E 2
    return shell_active;
}


I 3
D 23
static int
child_died()
E 23
I 23
static void
child_died(code)
E 23
{
D 18
    union wait *status;
E 18
I 18
    union wait status;
E 18
    register int pid;

D 18
    while ((pid = wait3(&status, WNOHANG, 0)) > 0) {
E 18
I 18
D 23
    while ((pid = wait3(&status, WNOHANG, (struct rusage *)0)) > 0) {
E 23
I 23
    while ((pid = wait3((int *)&status, WNOHANG, (struct rusage *)0)) > 0) {
E 23
E 18
	if (pid == shell_pid) {
	    char inputbuffer[100];
I 18
	    extern void setconnmode();
	    extern void ConnectScreen();
E 18

	    shell_active = 0;
	    if (sock != -1) {
		(void) close(sock);
		sock = -1;
D 5
		printf("[Hit return to continue]");
		fflush(stdout);
		(void) gets(inputbuffer);
E 5
D 4
		setconnmode();
		ConnectScreen();	/* Turn screen on (if need be) */
E 4
	    }
I 5
	    printf("[Hit return to continue]");
	    fflush(stdout);
	    (void) gets(inputbuffer);
E 5
I 4
	    setconnmode();
	    ConnectScreen();	/* Turn screen on (if need be) */
	    (void) close(serversock);
I 11
	    (void) unlink(keyname);
E 11
E 4
	}
    }
    signal(SIGCHLD, child_died);
}


E 3
/*
 * Called from telnet.c to fork a lower command.com.  We
 * use the spint... routines so that we can pick up
 * interrupts generated by application programs.
 */


int
shell(argc,argv)
int	argc;
char	*argv[];
{
D 2
    if ((shell_pid = fork()) {
	shell_active = 1;		/* We are running down below */
	child_killed();			/* Start up signal handler */
E 2
I 2
D 4
    int serversock, length;
E 4
I 4
    int length;
E 4
    struct sockaddr_in server;
    char sockNAME[100];
    static char **whereAPI = 0;
I 11
    int fd;
    struct timeval tv;
    long ikey;
    extern long random();
    extern char *mktemp();
I 18
    extern char *strcpy();
E 18
E 11

D 11
    /* First, create the socket which will be connected to */
E 11
I 11
    /* First, create verification file. */
    do {
D 23
	keyname = mktemp("/tmp/apiXXXXXX");
E 23
I 23
	keyname = mktemp(strdup("/tmp/apiXXXXXX"));
E 23
	fd = open(keyname, O_RDWR|O_CREAT|O_EXCL, IREAD|IWRITE);
    } while ((fd == -1) && (errno == EEXIST));

    if (fd == -1) {
	perror("open");
	return 0;
    }

    /* Now, get seed for random */

D 18
    if (gettimeofday(&tv, 0) == -1) {
E 18
I 18
    if (gettimeofday(&tv, (struct timezone *)0) == -1) {
E 18
	perror("gettimeofday");
	return 0;
    }
    srandom(tv.tv_usec);		/* seed random number generator */
    do {
	ikey = random();
    } while (ikey == 0);
D 18
    sprintf(key, "%lu\n", ikey);
E 18
I 18
    sprintf(key, "%lu\n", (unsigned long) ikey);
E 18
    if (write(fd, key, strlen(key)) != strlen(key)) {
	perror("write");
	return 0;
    }
    key[strlen(key)-1] = 0;		/* Get rid of newline */

    if (close(fd) == -1) {
	perror("close");
	return 0;
    }

    /* Next, create the socket which will be connected to */
E 11
    serversock = socket(AF_INET, SOCK_STREAM, 0);
    if (serversock < 0) {
	perror("opening API socket");
	return 0;
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 0;
D 18
    if (bind(serversock, &server, sizeof server) < 0) {
E 18
I 18
    if (bind(serversock, (struct sockaddr *)&server, sizeof server) < 0) {
E 18
	perror("binding API socket");
	return 0;
    }
    length = sizeof server;
D 18
    if (getsockname(serversock, &server, &length) < 0) {
E 18
I 18
    if (getsockname(serversock, (struct sockaddr *)&server, &length) < 0) {
E 18
	perror("getting API socket name");
	(void) close(serversock);
    }
    listen(serversock, 1);
    /* Get name to advertise in address list */
    strcpy(sockNAME, "API3270=");
    gethostname(sockNAME+strlen(sockNAME), sizeof sockNAME-strlen(sockNAME));
D 11
    if (strlen(sockNAME) > (sizeof sockNAME-10)) {
E 11
I 11
    if (strlen(sockNAME) > (sizeof sockNAME-(10+strlen(keyname)))) {
E 11
	fprintf(stderr, "Local hostname too large; using 'localhost'.\n");
	strcpy(sockNAME, "localhost");
    }
D 18
    sprintf(sockNAME+strlen(sockNAME), ":%d", ntohs(server.sin_port));
E 18
I 18
    sprintf(sockNAME+strlen(sockNAME), ":%u", ntohs(server.sin_port));
E 18
I 11
    sprintf(sockNAME+strlen(sockNAME), ":%s", keyname);
E 11

    if (whereAPI == 0) {
	char **ptr, **nextenv;
	extern char **environ;

	ptr = environ;
	nextenv = ourENVlist;
	while (*ptr) {
	    if (nextenv >= &ourENVlist[highestof(ourENVlist)-1]) {
		fprintf(stderr, "Too many environmental variables\n");
		break;
	    }
	    *nextenv++ = *ptr++;
	}
	whereAPI = nextenv++;
	*nextenv++ = 0;
	environ = ourENVlist;		/* New environment */
    }
    *whereAPI = sockNAME;

    child_died();			/* Start up signal handler */
    shell_active = 1;			/* We are running down below */
    if (shell_pid = vfork()) {
	if (shell_pid == -1) {
	    perror("vfork");
	    (void) close(serversock);
	} else {
D 4
	    fd_set fdset;
	    int i;

	    FD_ZERO(&fdset);
	    FD_SET(serversock, &fdset);
	    while (shell_active) {
		if ((i = select(serversock+1, &fdset, 0, 0, 0)) < 0) {
		    if (errno = EINTR) {
			continue;
		    } else {
			perror("in select waiting for API connection");
			break;
		    }
		} else {
		    i = accept(serversock, 0, 0);
		    if (i == -1) {
			perror("accepting API connection");
		    }
		    sock = i;
I 3
		    api_exch_init(sock);
		    state = UNCONNECTED;
E 3
		    break;
		}
	    }
	    (void) close(serversock);
	    /* If the process has already exited, we may need to close */
	    if ((shell_active == 0) && (sock != -1)) {
		(void) close(sock);
		sock = -1;
		setcommandmode();	/* In case child_died sneaked in */
	    }
E 4
I 4
	    state = UNCONNECTED;
E 4
	}
E 2
    } else {				/* New process */
	register int i;

	for (i = 3; i < 30; i++) {
	    (void) close(i);
	}
	if (argc == 1) {		/* Just get a shell */
	    char *cmdname;
I 2
	    extern char *getenv();
E 2

	    cmdname = getenv("SHELL");
	    execlp(cmdname, cmdname, 0);
	    perror("Exec'ing new shell...\n");
	    exit(1);
	} else {
	    execvp(argv[1], &argv[1]);
	    perror("Exec'ing command.\n");
	    exit(1);
	}
	/*NOTREACHED*/
    }
D 2
    return 1;			/* Go back to main loop */
E 2
I 2
    return shell_active;		/* Go back to main loop */
E 2
}
E 1
