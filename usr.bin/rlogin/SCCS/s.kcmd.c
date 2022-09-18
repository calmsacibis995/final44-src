h35901
s 00004/00000/00277
d D 8.2 93/08/19 13:44:37 mckusick 10 9
c add ifdef's for KERBEROS
e
s 00002/00002/00275
d D 8.1 93/06/06 16:09:33 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00272
d D 5.8 93/03/06 20:35:39 leres 8 7
c Minor indentation fixes.
e
s 00080/00082/00197
d D 5.7 93/03/04 18:31:47 bostic 7 6
c Craig Leres prototyping fixes, plus some of mine
e
s 00011/00013/00268
d D 5.6 90/06/01 17:40:53 bostic 6 5
c put reasonable SCCS headers on
e
s 00001/00011/00280
d D 5.5 90/06/01 17:32:46 bostic 5 4
c new copyright notice
e
s 00001/00000/00290
d D 5.4 90/05/11 22:57:25 kfall 4 3
c include kerberosIV/des.h before kerberosIV/krb.h
e
s 00005/00005/00285
d D 5.3 90/04/03 12:06:17 bostic 3 2
c include files moved to kerberosIV, not /usr/include
e
s 00011/00009/00279
d D 5.2 89/08/29 14:29:11 kfall 2 1
c wait even less time on Kerb. failure; fix error msgs
e
s 00288/00000/00000
d D 5.1 89/08/20 14:21:14 kfall 1 0
c date and time created 89/08/20 14:21:14 by kfall
e
u
U
f b 
t
T
I 1
/*
D 6
 *	$Source: /mit/kerberos/src/appl/bsd/RCS/kcmd.c,v $
 *	$Header: kcmd.c,v 4.16 89/05/17 10:54:31 jtkohl Exp $
E 6
I 6
D 9
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
E 6
 */

#ifndef lint
D 6
static char *rcsid_kcmd_c =
"$Header: kcmd.c,v 4.16 89/05/17 10:54:31 jtkohl Exp $";
#endif lint
#define LIBC_SCCS
E 6
I 6
static char Xsccsid[] = "derived from @(#)rcmd.c 5.17 (Berkeley) 6/27/88";
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 6

D 7
/*
D 6
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 *	$Source: /mit/kerberos/src/appl/bsd/RCS/kcmd.c,v $
 *	$Header: kcmd.c,v 4.16 89/05/17 10:54:31 jtkohl Exp $
E 6
 *
D 5
 * Redistribution and use in source and binary forms are permitted
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
E 5
I 5
D 6
 * %sccs.include.redist.c%
E 6
I 6
 * static char *rcsid_kcmd_c =
 * "$Header: kcmd.c,v 4.16 89/05/17 10:54:31 jtkohl Exp $";
E 6
E 5
 */
D 6

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "derived from @(#)rcmd.c	5.17 (Berkeley) 6/27/88";
#endif /* LIBC_SCCS and not lint */
E 6

E 7
D 3
#include <stdio.h>
#include <ctype.h>
#include <pwd.h>
E 3
#include <sys/param.h>
#include <sys/file.h>
D 7
#include <sys/signal.h>
E 7
#include <sys/socket.h>
#include <sys/stat.h>

#include <netinet/in.h>
I 7
#include <arpa/inet.h>
E 7

D 7
#include <netdb.h>
#include <errno.h>
E 7
I 4
#include <kerberosIV/des.h>
E 4
D 3
#include <krb.h>
#include <kparse.h>
E 3
I 3
#include <kerberosIV/krb.h>
#include <kerberosIV/kparse.h>
I 7

#include <ctype.h>
#include <errno.h>
#include <netdb.h>
E 7
#include <pwd.h>
I 7
#include <signal.h>
E 7
#include <stdio.h>
D 7
#include <ctype.h>
E 7
I 7
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
E 7
E 3

D 7
#ifndef MAXHOSTNAMELEN 
E 7
I 7
#include "krb.h"

#ifndef MAXHOSTNAMELEN
E 7
#define MAXHOSTNAMELEN 64
#endif

D 7
extern	errno;
char	*index(), *malloc(), *krb_realmofhost();

E 7
#define	START_PORT	5120	 /* arbitrary */

I 7
int	getport __P((int *));

int
E 7
kcmd(sock, ahost, rport, locuser, remuser, cmd, fd2p, ticket, service, realm,
D 7
      cred, schedule, msg_data, laddr, faddr, authopts)
int *sock;
char **ahost;
u_short rport;
char *locuser, *remuser, *cmd;
int *fd2p;
KTEXT ticket;
char *service;
char *realm;
CREDENTIALS *cred;
Key_schedule schedule;
MSG_DAT *msg_data;
struct sockaddr_in *laddr, *faddr;
long authopts;
E 7
I 7
    cred, schedule, msg_data, laddr, faddr, authopts)
	int *sock;
	char **ahost;
	u_short rport;
	char *locuser, *remuser, *cmd;
	int *fd2p;
	KTEXT ticket;
	char *service;
	char *realm;
	CREDENTIALS *cred;
	Key_schedule schedule;
	MSG_DAT *msg_data;
	struct sockaddr_in *laddr, *faddr;
	long authopts;
E 7
{
	int s, timo = 1, pid;
	long oldmask;
	struct sockaddr_in sin, from;
	char c;
#ifdef ATHENA_COMPAT
	int lport = IPPORT_RESERVED - 1;
#else
	int lport = START_PORT;
D 7
#endif ATHENA_COMPAT
E 7
I 7
#endif
E 7
	struct hostent *hp;
	int rc;
	char *host_save;
	int status;

	pid = getpid();
	hp = gethostbyname(*ahost);
D 7
	if (hp == 0) {
E 7
I 7
	if (hp == NULL) {
E 7
		/* fprintf(stderr, "%s: unknown host\n", *ahost); */
		return (-1);
	}

D 7
    host_save = malloc(strlen(hp->h_name) + 1);
    strcpy(host_save, hp->h_name);
    *ahost = host_save;
E 7
I 7
	host_save = malloc(strlen(hp->h_name) + 1);
	strcpy(host_save, hp->h_name);
	*ahost = host_save;
E 7

I 10
#ifdef KERBEROS
E 10
D 7
    /* If realm is null, look up from table */
    if ((realm == NULL) || (realm[0] == '\0')) {
	realm = krb_realmofhost(host_save);
    }
E 7
I 7
	/* If realm is null, look up from table */
	if (realm == NULL || realm[0] == '\0')
		realm = krb_realmofhost(host_save);
I 10
#endif /* KERBEROS */
E 10
E 7

	oldmask = sigblock(sigmask(SIGURG));
	for (;;) {
D 8
	s = getport(&lport);
E 8
I 8
		s = getport(&lport);
E 8
		if (s < 0) {
			if (errno == EAGAIN)
D 2
				fprintf(stderr, "socket: All ports in use\n");
E 2
I 2
				fprintf(stderr,
					"kcmd(socket): All ports in use\n");
E 2
			else
D 2
				perror("rcmd: socket");
E 2
I 2
				perror("kcmd: socket");
E 2
			sigsetmask(oldmask);
			return (-1);
		}
		fcntl(s, F_SETOWN, pid);
		sin.sin_family = hp->h_addrtype;
#if defined(ultrix) || defined(sun)
		bcopy(hp->h_addr, (caddr_t)&sin.sin_addr, hp->h_length);
#else
		bcopy(hp->h_addr_list[0], (caddr_t)&sin.sin_addr, hp->h_length);
D 7
#endif /* defined(ultrix) || defined(sun) */
E 7
I 7
#endif
E 7
		sin.sin_port = rport;
D 7
		if (connect(s, (struct sockaddr *)&sin, sizeof (sin)) >= 0)
E 7
I 7
		if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) >= 0)
E 7
			break;
		(void) close(s);
		if (errno == EADDRINUSE) {
			lport--;
			continue;
		}
D 8
	/*
	 * don't wait very long for Kerberos rcmd.
	 */
	if (errno == ECONNREFUSED && timo <= 4) {
E 8
I 8
		/*
		 * don't wait very long for Kerberos rcmd.
		 */
		if (errno == ECONNREFUSED && timo <= 4) {
E 8
D 2
			sleep(timo);
E 2
I 2
			/* sleep(timo); don't wait at all here */
E 2
			timo *= 2;
			continue;
		}
#if !(defined(ultrix) || defined(sun))
		if (hp->h_addr_list[1] != NULL) {
			int oerrno = errno;

			fprintf(stderr,
D 2
			    "connect to address %s: ", inet_ntoa(sin.sin_addr));
E 2
I 2
			    "kcmd: connect to address %s: ",
			    inet_ntoa(sin.sin_addr));
E 2
			errno = oerrno;
D 7
			perror(0);
E 7
I 7
			perror(NULL);
E 7
			hp->h_addr_list++;
			bcopy(hp->h_addr_list[0], (caddr_t)&sin.sin_addr,
			    hp->h_length);
			fprintf(stderr, "Trying %s...\n",
				inet_ntoa(sin.sin_addr));
			continue;
		}
#endif /* !(defined(ultrix) || defined(sun)) */
		if (errno != ECONNREFUSED)
			perror(hp->h_name);
		sigsetmask(oldmask);
		return (-1);
	}
	lport--;
	if (fd2p == 0) {
		write(s, "", 1);
		lport = 0;
	} else {
		char num[8];
D 7
	int s2 = getport(&lport), s3;
		int len = sizeof (from);
E 7
I 7
		int s2 = getport(&lport), s3;
		int len = sizeof(from);
E 7

D 7
	if (s2 < 0) {
	    status = -1;
E 7
I 7
		if (s2 < 0) {
			status = -1;
E 7
			goto bad;
D 7
	}
E 7
I 7
		}
E 7
		listen(s2, 1);
		(void) sprintf(num, "%d", lport);
D 7
		if (write(s, num, strlen(num)+1) != strlen(num)+1) {
E 7
I 7
		if (write(s, num, strlen(num) + 1) != strlen(num) + 1) {
E 7
D 2
			perror("write: setting up stderr");
E 2
I 2
			perror("kcmd(write): setting up stderr");
E 2
			(void) close(s2);
D 7
	    status = -1;
E 7
I 7
			status = -1;
E 7
			goto bad;
		}
		s3 = accept(s2, (struct sockaddr *)&from, &len);
		(void) close(s2);
		if (s3 < 0) {
D 2
			perror("accept");
E 2
I 2
			perror("kcmd:accept");
E 2
			lport = 0;
			status = -1;
			goto bad;
		}
		*fd2p = s3;
		from.sin_port = ntohs((u_short)from.sin_port);
		if (from.sin_family != AF_INET ||
		    from.sin_port >= IPPORT_RESERVED) {
			fprintf(stderr,
D 2
			    "socket: protocol failure in circuit setup.\n");
E 2
I 2
			 "kcmd(socket): protocol failure in circuit setup.\n");
I 7
			status = -1;
E 7
E 2
			goto bad2;
		}
	}
D 7
    /*
     * Kerberos-authenticated service.  Don't have to send locuser,
     * since its already in the ticket, and we'll extract it on
     * the other side.
     */
    /* (void) write(s, locuser, strlen(locuser)+1); */
E 7
I 7
	/*
	 * Kerberos-authenticated service.  Don't have to send locuser,
	 * since its already in the ticket, and we'll extract it on
	 * the other side.
	 */
	/* (void) write(s, locuser, strlen(locuser)+1); */
E 7

D 7
    /* set up the needed stuff for mutual auth, but only if necessary */
    if (authopts & KOPT_DO_MUTUAL) {
	int sin_len;
	*faddr = sin;
E 7
I 7
	/* set up the needed stuff for mutual auth, but only if necessary */
	if (authopts & KOPT_DO_MUTUAL) {
		int sin_len;
		*faddr = sin;
E 7

D 7
	sin_len = sizeof (struct sockaddr_in);
	if (getsockname(s, (struct sockaddr *)laddr, &sin_len) < 0) {
D 2
	    perror("getsockname");
E 2
I 2
	    perror("kcmd(getsockname)");
E 2
	    status = -1;
	    goto bad2;
E 7
I 7
		sin_len = sizeof(struct sockaddr_in);
		if (getsockname(s, (struct sockaddr *)laddr, &sin_len) < 0) {
			perror("kcmd(getsockname)");
			status = -1;
			goto bad2;
		}
E 7
	}
I 10
#ifdef KERBEROS
E 10
D 7
    }
    if ((status = krb_sendauth(authopts, s, ticket, service, *ahost,
E 7
I 7
	if ((status = krb_sendauth(authopts, s, ticket, service, *ahost,
E 7
			       realm, (unsigned long) getpid(), msg_data,
			       cred, schedule,
			       laddr,
			       faddr,
			       "KCMDV0.1")) != KSUCCESS)
D 7
	goto bad2;
E 7
I 7
		goto bad2;
I 10
#endif /* KERBEROS */
E 10
E 7

	(void) write(s, remuser, strlen(remuser)+1);
	(void) write(s, cmd, strlen(cmd)+1);

D 7
    if ((rc=read(s, &c, 1)) != 1) {
	if (rc==-1) {
		perror(*ahost);
	} else {
D 2
	    fprintf(stderr,"rcmd: bad connection with remote host\n");
E 2
I 2
	    fprintf(stderr,"kcmd: bad connection with remote host\n");
E 2
	}
	status = -1;
E 7
I 7
	if ((rc = read(s, &c, 1)) != 1) {
		if (rc == -1)
			perror(*ahost);
		else
			fprintf(stderr,"kcmd: bad connection with remote host\n");
		status = -1;
E 7
		goto bad2;
	}
D 7
	if (c != 0) {
E 7
I 7
	if (c != '\0') {
E 7
		while (read(s, &c, 1) == 1) {
			(void) write(2, &c, 1);
			if (c == '\n')
				break;
		}
D 7
	status = -1;
E 7
I 7
		status = -1;
E 7
		goto bad2;
	}
	sigsetmask(oldmask);
D 7
    *sock = s;
    return (KSUCCESS);
E 7
I 7
	*sock = s;
	return (KSUCCESS);
E 7
bad2:
	if (lport)
		(void) close(*fd2p);
bad:
	(void) close(s);
	sigsetmask(oldmask);
D 7
    return (status);
E 7
I 7
	return (status);
E 7
}

I 7
int
E 7
getport(alport)
	int *alport;
{
	struct sockaddr_in sin;
	int s;

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
		return (-1);
	for (;;) {
		sin.sin_port = htons((u_short)*alport);
D 7
		if (bind(s, (struct sockaddr *)&sin, sizeof (sin)) >= 0)
E 7
I 7
		if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) >= 0)
E 7
			return (s);
		if (errno != EADDRINUSE) {
			(void) close(s);
			return (-1);
		}
		(*alport)--;
#ifdef ATHENA_COMPAT
		if (*alport == IPPORT_RESERVED/2) {
#else
		if (*alport == IPPORT_RESERVED) {
D 7
#endif ATHENA_COMPAT
E 7
I 7
#endif
E 7
			(void) close(s);
			errno = EAGAIN;		/* close */
			return (-1);
		}
	}
}
D 7

E 7
E 1
