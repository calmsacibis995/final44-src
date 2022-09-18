h15549
s 00003/00013/00339
d D 5.2 93/05/29 11:22:32 bostic 2 1
c new copyright notice
e
s 00352/00000/00000
d D 5.1 89/05/16 09:01:56 bostic 1 0
c date and time created 89/05/16 09:01:56 by bostic
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1989 The Regents of the University of California.
E 2
I 2
/*-
 * Copyright (c) 1993 The Regents of the University of California.
E 2
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Bill Jolitz.
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

/*
 * externalconnect:
 *	send a message to connection daemon via UNIX domain socket
 *	containing a resource request and preparation instructions;
 *	expect a response message containing either the file descriptor
 *	of the resource and method of preparation, or an connection
 *	error status explaining why it could not be done.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/uio.h>
#include <connect.h>

static struct fdsocket {
	int fd;
	int sock;
	int state ;
}	fdsockets[MAXCONNECTS];
static nfds = 0, inprocess = -1 ;

externalconnect (cdp, opts, optlen, efd)
	struct connectdomain *cdp ;
	char *opts ; int optlen ; int efd ;
{
	int sock, n, i, fd, rv ;
	struct sockaddr_un rqsts;
	struct iovec iov[4];
	struct msghdr msg ;
	int constatus, rqstfmt;


	sock = socket (AF_UNIX, SOCK_STREAM, 0) ;
	if (sock < 0) {
		perror("externalconnect: stream socket") ;
		exit(1) ;
	}
	rqsts.sun_family = AF_UNIX ;
	strcpy (rqsts.sun_path,"/dev/connect") ;
	if (connect (sock, &rqsts, sizeof (rqsts)) < 0) {
		perror ("externalconnect: connect /dev/connect") ;
		exit (1) ;
	}
	
	/* record evidence of communication, so that multiple
	   outstandings/aborts are possible */
	if (!nfds)
		for (i = 0; i < MAXCONNECTS ; i++) {
			fdsockets[i].fd = -1;
			fdsockets[i].sock = -1;
			fdsockets[i].state = -1; } ;
	fdsockets[nfds].sock = sock ;
	fdsockets[nfds].state = CDNEWREQUEST ;
	inprocess = nfds++ ;
	

	/* send connnection request message */
	rqstfmt = CDNEWREQUEST;
	msg.msg_name = "";
	msg.msg_namelen = 0 ;
	iov[0].iov_base = (caddr_t) &rqstfmt ;
	iov[0].iov_len = sizeof (rqstfmt) ;
	iov[1].iov_base = (caddr_t) cdp ;
	iov[1].iov_len = CDSIZE(cdp) ;
	iov[2].iov_base = (caddr_t) opts;
	iov[2].iov_len = optlen ;
	msg.msg_iov = iov;
	msg.msg_iovlen = 3;
	if (efd) {
		msg.msg_accrights = (caddr_t) &efd ;
		msg.msg_accrightslen = sizeof (efd) ;
	} else	msg.msg_accrightslen = 0;

	if (sendmsg (sock, &msg, 0) < 0) {
		perror("externalconnection: sendmsg") ;
		exit(1) ;
	}

	/* recieve message from connection daemon */
	msg.msg_name = "" ;
	msg.msg_namelen = 0 ;
	iov[0].iov_base = (caddr_t) &rqstfmt ;
	iov[0].iov_len = sizeof(rqstfmt) ;
	iov[1].iov_base = (caddr_t) &constatus ;
	iov[1].iov_len = sizeof(constatus) ;
	iov[2].iov_base = (caddr_t) opts;
	iov[2].iov_len = optlen ;
	msg.msg_iov = iov;
	msg.msg_iovlen = 3;
	msg.msg_accrights = (caddr_t) &fd ;
	msg.msg_accrightslen = sizeof (fd) ;

	if (recvmsg (sock, &msg, 0) < 0) {
		perror("externalconnection: recvmsg") ;
		exit(1) ;
	}

	/* did we succeed? */
	inprocess = -1 ;
	if (msg.msg_accrightslen >= sizeof (fd)) {
/* XXX needs more work */
		fdsockets[nfds-1].fd = fd ;
		fdsockets[nfds-1].state = CDNEWRESPONSE ;
		return (fd) ;
	} else {
		nfds--;
		close (sock) ;
		return (constatus) ;
	}
}

/*
 * externalfinish: send back file descriptor we got from
 *	external connect for a well-behaved close. We
 *	will wait for close just to be able to report
 *	back any trouble.
 */
externalfinish (fd)
	int fd ;
{
	int sock, n, i, rv ;
	struct iovec iov[2];
	struct msghdr msg ;
	int constatus, rqstfmt;
	struct fdsocket *fdp;


	fdp = fdsockets ;
	/* find socket associated with file descriptor */
	for (i = 0; i < nfds ; i++,fdp++)
		if (fdp->fd == fd) break;

	/* not found at all */
	if (i > nfds || !nfds) {
		if (inprocess >= 0) externalabort(-1);
		return (-1) ;
	}

	sock = fdp->sock ;

	/* never was open */
	if (sock < 0) return (-2) ;

	/* is there an outstanding request on this guy? */
	if (ISCDREQUEST(fdp->state)) externalabort(fdp->fd);
	
	/* mark as closed */
	fdp->fd = -1 ;


	/* send finish request message */
	inprocess = rqstfmt = CDFINISHREQUEST;
	msg.msg_name = "";
	msg.msg_namelen = 0 ;
	iov[0].iov_base = (caddr_t) &rqstfmt ;
	iov[0].iov_len = sizeof (rqstfmt) ;
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;
	msg.msg_accrights = (caddr_t) &fd ;
	msg.msg_accrightslen = sizeof (fd) ;

	if (sendmsg (sock, &msg, 0) < 0) {
		perror("externalfinish: sendmsg") ;
		return (-3) ;
	}

	/* recieve message from connection daemon */
	msg.msg_name = "" ;
	msg.msg_namelen = 0 ;
	iov[0].iov_base = (caddr_t) &rqstfmt ;
	iov[0].iov_len = sizeof(rqstfmt) ;
	iov[1].iov_base = (caddr_t) &constatus ;
	iov[1].iov_len = sizeof(constatus) ;
	msg.msg_iov = iov;
	msg.msg_iovlen = 2;
	msg.msg_accrights = 0 ;
	msg.msg_accrightslen = 0;

	if (recvmsg (sock, &msg, 0) < 0) {
		perror("externalfinish: recvmsg") ;
		return (-4) ;
	}
	inprocess = -1 ;
	close (fd) ;
	close (sock) ;

	if (rqstfmt != CDFINISHRESPONSE) return (-5) ;
	return (constatus) ;
}

/*
 * externalabort: if we have an outstanding request,
 *	cancel it and return immediately. If the request
 *	was the initial open, the connection will never
 *	return a file descriptor, otherwise connection
 *	status is unaffected. This  routine is mean to be
 *	called from interrupt routines. 
 */
externalabort (fd)
	int fd ;
{
	int sock, n, i, rv ;
	struct iovec iov[2];
	struct msghdr msg ;
	int constatus, rqstfmt;
	struct fdsocket *fdp;


	fdp = fdsockets ;
	/* if we don't know who we are, abort current connection */
	if (fd < 0) {
		/* but nothing's going on... */
		if (inprocess < 0) return (-1) ;
		fdp += inprocess ;
	} else	{
		/* find socket associated with file descriptor */
		for (i = 0; i < nfds ; i++,fdp++)
			if (fdp->fd == fd) break;

		/* not found at all */
		if (i > nfds || !nfds)
			return (-1) ;
	}

	sock = fdp->sock ;

	/* never was open */
	if (sock < 0) return (-2) ;

	/* is there not an outstanding request on this guy? */
	if (!ISCDREQUEST(fdp->state)) return (-3) ;
	
	/* send abort request message */
	rqstfmt = CDCANCELREQUEST;
	msg.msg_name = "";
	msg.msg_namelen = 0 ;
	iov[0].iov_base = (caddr_t) &rqstfmt ;
	iov[0].iov_len = sizeof (rqstfmt) ;
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;
	msg.msg_accrights = (caddr_t) &fd ;
	msg.msg_accrightslen = sizeof (fd) ;

	if (sendmsg (sock, &msg, MSG_OOB) < 0) {
		perror("externalabort: sendmsg") ;
		return (-4) ;
	}
	return (0) ;
}

/*
 * externaloption: send a bag of options to be done to the file descriptor
 *	we got from externalconnect. Options are passed as value-result.
 */
externaloption (fd, opts, optlen)
	int fd ;
	char *opts ;
	int *optlen ;
{
	int sock, n, i, rv ;
	struct iovec iov[3];
	struct msghdr msg ;
	int constatus, rqstfmt;
	struct fdsocket *fdp;


	fdp = fdsockets ;
	/* find socket associated with file descriptor */
	for (i = 0; i < nfds ; i++,fdp++)
		if (fdp->fd == fd) break;

	/* not found at all */
	if (i > nfds || !nfds)
		return (-1) ;

	sock = fdp->sock ;

	/* never was open */
	if (sock < 0) return (-2) ;

	/* is there an outstanding request on this guy? */
	if (ISCDREQUEST(fdp->state)) return (-3) ;
	
	/* mark as closed */
	fdp->fd = -1 ;

	/* send finish request message */
	inprocess = rqstfmt = CDOPTIONREQUEST;
	msg.msg_name = "";
	msg.msg_namelen = 0 ;
	iov[0].iov_base = (caddr_t) &rqstfmt ;
	iov[0].iov_len = sizeof (rqstfmt) ;
	iov[1].iov_base = (caddr_t) opts ;
	iov[1].iov_len = *optlen ;
	msg.msg_iov = iov;
	msg.msg_iovlen = 2;
	msg.msg_accrights = (caddr_t) &fd ;
	msg.msg_accrightslen = sizeof (fd) ;

	if (sendmsg (sock, &msg, 0) < 0) {
		perror("externaloption: sendmsg") ;
		return (-3) ;
	}

	/* recieve message from connection daemon */
	msg.msg_name = "" ;
	msg.msg_namelen = 0 ;
	iov[0].iov_base = (caddr_t) &rqstfmt ;
	iov[0].iov_len = sizeof(rqstfmt) ;
	iov[1].iov_base = (caddr_t) &constatus ;
	iov[1].iov_len = sizeof(constatus) ;
	iov[2].iov_base = (caddr_t) opts ;
	iov[2].iov_len = *optlen ;
	msg.msg_iov = iov;
	msg.msg_iovlen = 3;
	msg.msg_accrights = 0 ;
	msg.msg_accrightslen = 0;

	if (recvmsg (sock, &msg, 0) < 0) {
		perror("externaloption: recvmsg") ;
		return (-4) ;
	}
	inprocess = -1 ;

	if (rqstfmt != CDOPTIONRESPONSE) return (-5) ;
	return (constatus) ;
}
E 1
