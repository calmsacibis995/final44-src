h26504
s 00002/00002/00130
d D 8.1 93/06/06 16:09:43 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00005/00119
d D 1.7 93/03/04 18:31:48 bostic 8 6
c Craig Leres prototyping fixes, plus some of mine
e
s 00000/00049/00075
d D 1.6.1.1 90/10/21 18:15:52 mckusick 7 6
c delete data-stream encryption for the foreign sites (4.3-Reno)
e
s 00004/00000/00120
d D 1.6 90/09/27 21:46:17 mckusick 6 5
c break out -x functionality into #ifdef CRYPT
e
s 00010/00012/00110
d D 1.5 90/06/01 17:40:55 bostic 5 4
c put reasonable SCCS headers on
e
s 00001/00011/00121
d D 1.4 90/06/01 17:32:52 bostic 4 3
c new copyright notice
e
s 00001/00000/00131
d D 1.3 90/05/11 22:57:27 kfall 3 2
c include kerberosIV/des.h before kerberosIV/krb.h
e
s 00022/00011/00109
d D 1.2 90/04/08 18:02:04 bostic 2 1
c checked in for Kevin Fall
e
s 00120/00000/00000
d D 1.1 89/08/20 14:21:21 kfall 1 0
c date and time created 89/08/20 14:21:21 by kfall
e
u
U
f b 
t
T
I 1
/*
D 5
 *	$Source: /mit/kerberos/ucb/mit/kcmd/RCS/krcmd.c,v $
 *	$Header: /mit/kerberos/ucb/mit/kcmd/RCS/krcmd.c,v 5.1 89/07/25 15:38:44 kfall Exp Locker: kfall $
 */

#ifndef lint
static char *rcsid_kcmd_c =
"$Header: /mit/kerberos/ucb/mit/kcmd/RCS/krcmd.c,v 5.1 89/07/25 15:38:44 kfall Exp Locker: kfall $";
#endif lint
#define LIBC_SCCS

/*
E 5
D 9
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 4
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

#ifndef lint
D 5
static char sccsid[] = "@(#)krcmd.c	1.3 (Berkeley) 2/10/89";
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
E 5
#endif /* not lint */
I 5

/*
D 8
 *	$Source: /mit/kerberos/ucb/mit/kcmd/RCS/krcmd.c,v $
E 8
I 8
 *	$Source: /usr/src/usr.bin/rlogin/RCS/krcmd.c,v $
E 8
 *	$Header: /mit/kerberos/ucb/mit/kcmd/RCS/krcmd.c,v 5.1
 *		89/07/25 15:38:44 kfall Exp Locker: kfall $
 * static char *rcsid_kcmd_c =
 * "$Header: /mit/kerberos/ucb/mit/kcmd/RCS/krcmd.c,v 5.1 89/07/25 15:38:44
 *	kfall Exp Locker: kfall $";
 */
E 5

I 6
#ifdef KERBEROS
E 6
#include <sys/types.h>
D 8
#include <stdio.h>
E 8
I 8
#ifdef CRYPT
#include <sys/socket.h>
#endif

#include <netinet/in.h>

E 8
I 3
#include <kerberosIV/des.h>
E 3
D 2
#include <krb.h>
E 2
I 2
#include <kerberosIV/krb.h>
E 2

I 8
#include <stdio.h>

E 8
#define	SERVICE_NAME	"rcmd"

I 8
int	kcmd __P((int *, char **, u_short, char *, char *, char *, int *,
	    KTEXT, char *, char *, CREDENTIALS *, Key_schedule, MSG_DAT *,
	    struct sockaddr_in *, struct sockaddr_in *, long));

E 8
I 2
/*
 * krcmd: simplified version of Athena's "kcmd"
 *	returns a socket attached to the destination, -1 or krb error on error 
 *	if fd2p is non-NULL, another socket is filled in for it
 */

E 2
int
krcmd(ahost, rport, remuser, cmd, fd2p, realm)
	char	**ahost;
	u_short	rport;
	char	*remuser, *cmd;
	int	*fd2p;
	char	*realm;
{
D 2
	int		sock = -1, err;
E 2
I 2
	int		sock = -1, err = 0;
E 2
	KTEXT_ST	ticket;
D 2
	long authopts = 0L;
E 2
I 2
	long		authopts = 0L;
E 2

	err = kcmd(
		&sock,
		ahost,
		rport,
		NULL,	/* locuser not used */
		remuser,
		cmd,
		fd2p,
		&ticket,
		SERVICE_NAME,
		realm,
D 2
		NULL,	/* credentials not used */
		NULL,	/* key schedule not used */
		NULL,	/* MSG_DAT not used */
		NULL,	/* local addr not used */
		NULL,	/* foreign addr not used */
E 2
I 2
		(CREDENTIALS *)  NULL,		/* credentials not used */
		(bit_64 *) NULL,		/* key schedule not used */
		(MSG_DAT *) NULL,		/* MSG_DAT not used */
		(struct sockaddr_in *) NULL,	/* local addr not used */
		(struct sockaddr_in *) NULL,	/* foreign addr not used */
E 2
		authopts
	);

D 2
	if(err > KSUCCESS && err < MAX_KRB_ERRORS) {
E 2
I 2
	if (err > KSUCCESS && err < MAX_KRB_ERRORS) {
E 2
		fprintf(stderr, "krcmd: %s\n", krb_err_txt[err]);
		return(-1);
	}
I 2
	if (err < 0)
		return(-1);
E 2
	return(sock);
}

I 6
D 7
#ifdef CRYPT
E 6
D 8
#include <sys/socket.h>
#include <netinet/in.h>

E 8
int
krcmd_mutual(ahost, rport, remuser, cmd, fd2p, realm, cred, sched)
	char		**ahost;
	u_short		rport;
	char		*remuser, *cmd;
	int		*fd2p;
	char		*realm;
	CREDENTIALS	*cred;
	Key_schedule	sched;
{
	int		sock, err;
	KTEXT_ST	ticket;
	MSG_DAT		msg_dat;
	struct sockaddr_in	laddr, faddr;
	long authopts = KOPT_DO_MUTUAL;

	err = kcmd(
		&sock,
		ahost,
		rport,
		NULL,	/* locuser not used */
		remuser,
		cmd,
		fd2p,
		&ticket,
		SERVICE_NAME,
		realm,
		cred,		/* filled in */
		sched,		/* filled in */
D 2
		&msg_dat,	/* filled in? */
E 2
I 2
		&msg_dat,	/* filled in */
E 2
		&laddr,		/* filled in */
		&faddr,		/* filled in */
		authopts
	);

D 2
	if(err > KSUCCESS && err < MAX_KRB_ERRORS) {
E 2
I 2
	if (err > KSUCCESS && err < MAX_KRB_ERRORS) {
E 2
		fprintf(stderr, "krcmd_mutual: %s\n", krb_err_txt[err]);
		return(-1);
	}
I 2

	if (err < 0)
		return (-1);
E 2
	return(sock);
}
I 6
#endif /* CRYPT */
E 7
#endif /* KERBEROS */
E 6
E 1
