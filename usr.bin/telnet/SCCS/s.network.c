h47809
s 00002/00002/00149
d D 8.2 93/12/15 11:35:58 dab 22 21
c Add support for new ENVIRON command.
c Latest Kerberos V code from MIT (includes new
c options '-f' and '-F' to control the forwarding
c of credentials.)  Various bugfixes to keep some
c C compilers happy.
e
s 00002/00002/00149
d D 8.1 93/06/06 16:33:07 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00149
d D 5.4 93/05/20 10:49:27 dab 20 18
c Mostly, this changes all the "#if defined(ENCRYPTION)"
c lines to "#ifdef ENCRYPTION".  This will allow unifdef
c to be used to strip out the encryption code for
c foreign exports.  This also fixes up the usage statement.
e
s 00002/00002/00149
d R 5.4 93/05/20 10:37:18 dab 19 18
c Mostly this changes "#if defined(ENCRYPTION)" to
c "#ifdef ENCRYPTION".  This will allow unifdef to be
e
s 00001/00001/00150
d D 5.3 92/12/18 14:06:48 dab 18 17
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00010/00005/00141
d D 5.2 91/03/01 01:32:01 dab 17 16
c Telnet AUTHENTICATION option
c Telnet ENCRYPT option (test version)
c Function prototypes
e
s 00000/00000/00146
d D 5.1 90/09/14 10:42:05 borman 16 15
c Bump the sccs id to 5.1
e
s 00002/00001/00144
d D 1.15 90/06/28 12:57:14 borman 15 14
c Lots of bugfixes, add the ENVIRON and X-DISPLAY-LOC
c options, "-l user" to the command line, diagnostic flags.
e
s 00001/00011/00144
d D 1.14 90/06/01 17:45:27 bostic 14 13
c new copyright notice
e
s 00010/00005/00145
d D 1.13 88/06/29 20:15:21 bostic 13 12
c install approved copyright notice
e
s 00007/00003/00143
d D 1.12 88/06/27 22:19:17 minshall 12 11
c Fix up lint errors.
e
s 00016/00000/00130
d D 1.11 88/03/08 10:30:52 bostic 11 10
c add Berkeley specific copyright
e
s 00011/00016/00119
d D 1.10 88/01/07 15:26:41 minshall 10 9
c Make SYNCH work (ie: urgent (ie: ring markers)).
e
s 00020/00003/00115
d D 1.9 87/11/23 20:37:53 minshall 9 8
c Fixes from Dave Borman.
e
s 00004/00148/00114
d D 1.8 87/10/27 16:01:43 minshall 8 7
c Make stilloob use global rather than passed variable.  Remove
c some routines which (maybe) belong in telnet.c.
e
s 00003/00002/00259
d D 1.7 87/10/23 15:15:38 minshall 7 6
c Try to move system dependent stuff to system dependent files.
e
s 00008/00008/00253
d D 1.6 87/10/23 11:57:17 minshall 6 5
c Make the ring buffer a two-state buffer (supplier and consumer)
c rather than a three-state buffer (supplier, sender, and acker).
e
s 00001/00001/00260
d D 1.5 87/10/10 17:45:45 minshall 5 4
c sending is also acking.
e
s 00011/00004/00250
d D 1.4 87/10/10 16:11:09 minshall 4 3
c This version (appears to) works.
e
s 00057/00027/00197
d D 1.3 87/10/10 14:27:16 minshall 3 2
c This is the first version to get near rings.  It compiles,
c but doesn't work.
e
s 00014/00080/00210
d D 1.2 87/09/25 16:06:42 minshall 2 1
c Cut down on number of extern's.
e
s 00290/00000/00000
d D 1.1 87/09/11 15:40:40 minshall 1 0
c date and time created 87/09/11 15:40:40 by minshall
e
u
U
t
T
I 11
/*
D 21
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 21
I 21
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 21
 *
D 14
 * Redistribution and use in source and binary forms are permitted
D 13
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 13
I 13
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
E 14
I 14
 * %sccs.include.redist.c%
E 14
E 13
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 11
I 1
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <errno.h>

#include <arpa/telnet.h>

I 3
#include "ring.h"

E 3
#include "defines.h"
#include "externs.h"
I 9
#include "fdset.h"
E 9

D 3
char	netobuf[2*BUFSIZ], *nfrontp, *nbackp;
static char	*neturg;		/* one past last byte of urgent data */
E 3
I 3
D 7
Ring	netoring;
char	netobuf[2*BUFSIZ];
E 7
I 7
D 17
Ring	netoring, netiring;
char	netobuf[2*BUFSIZ], netibuf[BUFSIZ];
E 17
I 17
Ring		netoring, netiring;
unsigned char	netobuf[2*BUFSIZ], netibuf[BUFSIZ];
E 17
E 7
E 3

/*
 * Initialize internal network data structures.
 */

I 17
    void
E 17
init_network()
{
D 3
    nfrontp = nbackp = netobuf;
E 3
I 3
D 12
    ring_init(&netoring, netobuf, sizeof netobuf);
I 7
    ring_init(&netiring, netibuf, sizeof netibuf);
E 12
I 12
    if (ring_init(&netoring, netobuf, sizeof netobuf) != 1) {
	exit(1);
    }
    if (ring_init(&netiring, netibuf, sizeof netibuf) != 1) {
	exit(1);
    }
E 12
E 7
E 3
    NetTrace = stdout;
}


/*
 * Check to see if any out-of-band data exists on a socket (for
 * Telnet "synch" processing).
 */

D 17
int
E 17
I 17
    int
E 17
D 8
stilloob(s)
int	s;		/* socket number */
E 8
I 8
stilloob()
E 8
{
    static struct timeval timeout = { 0 };
    fd_set	excepts;
    int value;

    do {
	FD_ZERO(&excepts);
D 8
	FD_SET(s, &excepts);
	value = select(s+1, (fd_set *)0, (fd_set *)0, &excepts, &timeout);
E 8
I 8
	FD_SET(net, &excepts);
	value = select(net+1, (fd_set *)0, (fd_set *)0, &excepts, &timeout);
E 8
    } while ((value == -1) && (errno == EINTR));

    if (value < 0) {
	perror("select");
D 12
	quit();
E 12
I 12
	(void) quit();
I 15
	/* NOTREACHED */
E 15
E 12
    }
D 8
    if (FD_ISSET(s, &excepts)) {
E 8
I 8
    if (FD_ISSET(net, &excepts)) {
E 8
	return 1;
    } else {
	return 0;
    }
}


/*
I 2
 *  setneturg()
 *
 *	Sets "neturg" to the current location.
 */

D 17
void
E 17
I 17
    void
E 17
setneturg()
{
D 3
    neturg = NETLOC()-1;	/* Some systems are off by one XXX */
E 3
I 3
    ring_mark(&netoring);
E 3
}


/*
E 2
 *  netflush
 *		Send as much data as possible to the network,
 *	handling requests for urgent data.
 *
 *		The return value indicates whether we did any
 *	useful work.
 */


D 17
int
E 17
I 17
    int
E 17
netflush()
{
D 9
    int n;
E 9
I 9
D 10
    register int n, n0, n1;
E 10
I 10
    register int n, n1;
E 10
E 9

I 17
D 18
#if	defined(ENCRYPT)
E 18
I 18
D 20
#if	defined(ENCRYPTION)
E 20
I 20
#ifdef	ENCRYPTION
E 20
E 18
    if (encrypt_output)
	ring_encrypt(&netoring, encrypt_output);
D 20
#endif
E 20
I 20
#endif	/* ENCRYPTION */
E 20
E 17
D 3
    if ((n = nfrontp - nbackp) > 0) {
	if (!neturg) {
	    n = send(net, nbackp, n, 0);	/* normal write */
E 3
I 3
D 6
    if ((n = ring_unsent_consecutive(&netoring)) > 0) {
E 6
I 6
D 9
    if ((n = ring_full_consecutive(&netoring)) > 0) {
E 9
I 9
D 10
    n0 = ring_full_count(&netoring);
E 10
    if ((n1 = n = ring_full_consecutive(&netoring)) > 0) {
E 9
E 6
	if (!ring_at_mark(&netoring)) {
D 6
	    n = send(net, netoring.send, n, 0);	/* normal write */
E 6
I 6
D 22
	    n = send(net, netoring.consume, n, 0);	/* normal write */
E 22
I 22
	    n = send(net, (char *)netoring.consume, n, 0); /* normal write */
E 22
E 6
E 3
	} else {
D 3
	    n = neturg - nbackp;
E 3
	    /*
	     * In 4.2 (and 4.3) systems, there is some question about
	     * what byte in a sendOOB operation is the "OOB" data.
	     * To make ourselves compatible, we only send ONE byte
	     * out of band, the one WE THINK should be OOB (though
	     * we really have more the TCP philosophy of urgent data
	     * rather than the Unix philosophy of OOB data).
	     */
D 3
	    if (n > 1) {
		n = send(net, nbackp, n-1, 0);	/* send URGENT all by itself */
	    } else {
		n = send(net, nbackp, n, MSG_OOB);	/* URGENT data */
	    }
E 3
I 3
D 6
	    n = send(net, netoring.send, 1, MSG_OOB);/* URGENT data */
E 6
I 6
D 22
	    n = send(net, netoring.consume, 1, MSG_OOB);/* URGENT data */
E 22
I 22
	    n = send(net, (char *)netoring.consume, 1, MSG_OOB);/* URGENT data */
E 22
E 6
E 3
	}
    }
    if (n < 0) {
	if (errno != ENOBUFS && errno != EWOULDBLOCK) {
I 9
D 10
	abortit:
E 10
E 9
	    setcommandmode();
	    perror(hostname);
D 15
	    NetClose(net);
E 15
I 15
	    (void)NetClose(net);
E 15
D 3
	    neturg = 0;
E 3
I 3
	    ring_clear_mark(&netoring);
E 3
	    longjmp(peerdied, -1);
	    /*NOTREACHED*/
	}
	n = 0;
    }
    if (netdata && n) {
D 3
	Dump('>', nbackp, n);
E 3
I 3
D 6
	Dump('>', netoring.send, n);
E 6
I 6
	Dump('>', netoring.consume, n);
E 6
E 3
    }
D 3
    nbackp += n;
    if (nbackp >= neturg) {
	neturg = 0;
    }
    if (nbackp == nfrontp) {
	nbackp = nfrontp = netobuf;
    }
E 3
I 3
D 5
    ring_sent(&netoring, n);
E 5
I 5
D 6
    ring_sent_acked(&netoring, n);
E 6
I 6
D 9
    ring_consumed(&netoring, n);
E 9
I 9
    if (n) {
D 10
	if (n1 == n && n0 > n && !ring_at_mark(&netoring)) {
	    n1 = send(net, netoring.bottom, n0 - n, 0);
	    if (n1 < 0) {
		if (errno != ENOBUFS && errno != EWOULDBLOCK) {
		    goto abortit;
		}
	    }
	    if (netdata && n1) {
		Dump('>', netoring.bottom, n1);
	    }
	    n += n1;
	}
E 10
	ring_consumed(&netoring, n);
I 10
	/*
	 * If we sent all, and more to send, then recurse to pick
	 * up the other half.
	 */
	if ((n1 == n) && ring_full_consecutive(&netoring)) {
	    (void) netflush();
	}
	return 1;
    } else {
	return 0;
E 10
    }
E 9
E 6
E 5
E 3
D 10
    return n > 0;
E 10
D 8
}

/*
 * nextitem()
 *
 *	Return the address of the next "item" in the TELNET data
 * stream.  This will be the address of the next character if
 * the current address is a user data character, or it will
 * be the address of the character following the TELNET command
 * if the current address is a TELNET IAC ("I Am a Command")
 * character.
 */

static char *
nextitem(current)
char	*current;
{
    if ((*current&0xff) != IAC) {
	return current+1;
    }
    switch (*(current+1)&0xff) {
    case DO:
    case DONT:
    case WILL:
    case WONT:
	return current+3;
    case SB:		/* loop forever looking for the SE */
	{
	    register char *look = current+2;

	    for (;;) {
		if ((*look++&0xff) == IAC) {
		    if ((*look++&0xff) == SE) {
			return look;
		    }
		}
	    }
	}
    default:
	return current+2;
    }
}
I 3

E 3
/*
 * netclear()
 *
 *	We are about to do a TELNET SYNCH operation.  Clear
 * the path to the network.
 *
 *	Things are a bit tricky since we may have sent the first
 * byte or so of a previous TELNET command into the network.
 * So, we have to scan the network buffer from the beginning
 * until we are up to where we want to be.
 *
 *	A side effect of what we do, just to keep things
 * simple, is to clear the urgent data pointer.  The principal
 * caller should be setting the urgent data pointer AFTER calling
 * us in any case.
 */

D 2
static void
E 2
I 2
void
E 2
netclear()
{
I 3
#if	0	/* XXX */
E 3
    register char *thisitem, *next;
    char *good;
#define	wewant(p)	((nfrontp > p) && ((*p&0xff) == IAC) && \
				((*(p+1)&0xff) != EC) && ((*(p+1)&0xff) != EL))

    thisitem = netobuf;

D 3
    while ((next = nextitem(thisitem)) <= nbackp) {
E 3
I 3
    while ((next = nextitem(thisitem)) <= netobuf.send) {
E 3
	thisitem = next;
    }

    /* Now, thisitem is first before/at boundary. */

    good = netobuf;	/* where the good bytes go */

D 3
    while (nfrontp > thisitem) {
E 3
I 3
    while (netoring.add > thisitem) {
E 3
	if (wewant(thisitem)) {
	    int length;

	    next = thisitem;
	    do {
		next = nextitem(next);
	    } while (wewant(next) && (nfrontp > next));
	    length = next-thisitem;
	    memcpy(good, thisitem, length);
	    good += length;
	    thisitem = next;
	} else {
	    thisitem = nextitem(thisitem);
	}
    }

D 3
    nbackp = netobuf;
    nfrontp = good;		/* next byte to be sent */
    neturg = 0;
E 3
I 3
#endif	/* 0 */
    ring_init(&netoring, netobuf, sizeof netobuf);
}

#include <varargs.h>

void
netoprint(va_alist)
va_dcl
{
    va_list ap;
    char buffer[100];		/* where things go */
D 4
    char *ptr = buffer;
E 4
I 4
    char *ptr;
E 4
    char *format;
I 4
    char *string;
E 4
    int i;

    va_start(ap);

    format = va_arg(ap, char *);
I 4
    ptr = buffer;
E 4

    while ((i = *format++) != 0) {
	if (i == '%') {
	    i = *format++;
	    switch (i) {
	    case 'c':
D 4
		i = va_arg(ap, char);
		NETADD(i);
E 4
I 4
		*ptr++ = va_arg(ap, int);
E 4
		break;
I 4
	    case 's':
		string = va_arg(ap, char *);
D 6
		ring_add_data(&netoring, buffer, ptr-buffer);
		ring_add_data(&netoring, string, strlen(string));
E 6
I 6
		ring_supply_data(&netoring, buffer, ptr-buffer);
		ring_supply_data(&netoring, string, strlen(string));
E 6
		ptr = buffer;
		break;
E 4
	    case 0:
D 4
		ExitString("netoprint: trailing %.\n", 1);
E 4
I 4
		ExitString("netoprint: trailing %%.\n", 1);
E 4
		/*NOTREACHED*/
	    default:
		ExitString("netoprint: unknown format character.\n", 1);
		/*NOTREACHED*/
	    }
	} else {
	    *ptr++ = i;
	}
    }
D 6
    ring_add_data(&netoring, buffer, ptr-buffer);
E 6
I 6
    ring_supply_data(&netoring, buffer, ptr-buffer);
E 8
E 6
E 3
D 2
}

/*
 * These routines add various telnet commands to the data stream.
 */

void
xmitAO()
{
    NET2ADD(IAC, AO);
    if (autoflush) {
	doflush();
    }
}


void
xmitEL()
{
    NET2ADD(IAC, EL);
}

void
xmitEC()
{
    NET2ADD(IAC, EC);
}


#if	defined(NOT43)
int
#else	/* defined(NOT43) */
void
#endif	/* defined(NOT43) */
dosynch()
{
    netclear();			/* clear the path to the network */
    NET2ADD(IAC, DM);
    neturg = NETLOC()-1;	/* Some systems are off by one XXX */

#if	defined(NOT43)
    return 0;
#endif	/* defined(NOT43) */
}

void
doflush()
{
    NET2ADD(IAC, DO);
    NETADD(TELOPT_TM);
    flushline = 1;
    flushout = 1;
    ttyflush();
    /* do printoption AFTER flush, otherwise the output gets tossed... */
    printoption("<SENT", doopt, TELOPT_TM, 0);
}

void
intp()
{
    NET2ADD(IAC, IP);
    if (autoflush) {
	doflush();
    }
    if (autosynch) {
	dosynch();
    }
}

void
sendbrk()
{
    NET2ADD(IAC, BREAK);
    if (autoflush) {
	doflush();
    }
    if (autosynch) {
	dosynch();
    }
E 2
}
E 1
