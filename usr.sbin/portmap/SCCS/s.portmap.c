h00571
s 00005/00005/00510
d D 8.1 93/06/06 14:03:33 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00006/00498
d D 5.4 91/04/19 13:51:48 bostic 4 3
c new copyright; att/bsd/shared
e
s 00008/00005/00496
d D 5.3 91/03/26 23:04:57 donn 3 2
c Even cleaner, thanks to gcc -W -Wunused and ANSI / POSIX include files.
e
s 00067/00049/00434
d D 5.2 90/09/27 10:42:17 mckusick 2 1
c lint (from Torek)
e
s 00483/00000/00000
d D 5.1 90/08/23 15:59:31 mckusick 1 0
c from Sun RPC version 4.0
e
u
U
t
T
I 1
D 4
/*
 * Copyright (c) 1984 by Sun Microsystems, Inc.
E 4
I 4
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
E 4
 *
D 4
 *	%W% (Berkeley) %G%
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

D 4
/* @(#)portmap.c	2.3 88/08/11 4.0 RPCSRC */
E 4
#ifndef lint
D 4
static	char sccsid[] = "@(#)portmap.c 1.32 87/08/06 Copyr 1984 Sun Micro";
#endif
E 4
I 4
D 5
char copyright[] =
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
E 5
I 5
static char copyright[] =
"%Z% Copyright (c) 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 5
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
@(#)portmap.c	2.3 88/08/11 4.0 RPCSRC
static char sccsid[] = "@(#)portmap.c 1.32 87/08/06 Copyr 1984 Sun Micro";
*/
E 4

/*
 * portmap.c, Implements the program,version to port number mapping for
 * rpc.
 */

/*
 * Sun RPC is a product of Sun Microsystems, Inc. and is provided for
 * unrestricted use provided that this legend is included on all tape
 * media and as a part of the software program in whole or part.  Users
 * may copy or modify Sun RPC without charge, but are not authorized
 * to license or distribute it to anyone else except as part of a product or
 * program developed by the user.
 * 
 * SUN RPC IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING THE
 * WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE OR TRADE PRACTICE.
 * 
 * Sun RPC is provided with no support and without any obligation on the
 * part of Sun Microsystems, Inc. to assist in its use, correction,
 * modification or enhancement.
 * 
 * SUN MICROSYSTEMS, INC. SHALL HAVE NO LIABILITY WITH RESPECT TO THE
 * INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY SUN RPC
 * OR ANY PART THEREOF.
 * 
 * In no event will Sun Microsystems, Inc. be liable for any lost revenue
 * or profits or other special, indirect and consequential damages, even if
 * Sun has been advised of the possibility of such damages.
 * 
 * Sun Microsystems, Inc.
 * 2550 Garcia Avenue
 * Mountain View, California  94043
 */

#include <rpc/rpc.h>
#include <rpc/pmap_prot.h>
#include <stdio.h>
I 2
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
I 3
#include <unistd.h>
E 3
E 2
#include <netdb.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <sys/signal.h>
I 2
#include <sys/resource.h>
E 2

D 2
char *malloc();
E 2
D 3
int reg_service();
E 3
I 3
void reg_service();
E 3
void reap();
I 3
static void callit();
E 3
struct pmaplist *pmaplist;
D 2
static int debugging = 0;
E 2
I 2
int debugging = 0;
extern int errno;
E 2

D 2
main()
E 2
I 2
main(argc, argv)
	int argc;
	char **argv;
E 2
{
	SVCXPRT *xprt;
D 2
	int sock, pid, t;
E 2
I 2
	int sock, c;
E 2
	struct sockaddr_in addr;
	int len = sizeof(struct sockaddr_in);
	register struct pmaplist *pml;

D 2
#ifndef DEBUG
	pid = fork();
	if (pid < 0) {
		perror("portmap: fork");
E 2
I 2
	while ((c = getopt(argc, argv, "d")) != EOF) {
		switch (c) {

		case 'd':
			debugging = 1;
			break;

		default:
			(void) fprintf(stderr, "usage: %s [-d]\n", argv[0]);
			exit(1);
		}
	}

	if (!debugging && daemon(0, 0)) {
		(void) fprintf(stderr, "portmap: fork: %s", strerror(errno));
E 2
		exit(1);
	}
D 2
	if (pid != 0)
		exit(0);
	for (t = 0; t < 20; t++)
		close(t);
 	open("/", 0);
 	dup2(0, 1);
 	dup2(0, 2);
 	t = open("/dev/tty", 2);
 	if (t >= 0) {
 		ioctl(t, TIOCNOTTY, (char *)0);
 		close(t);
 	}
#endif
E 2
I 2

	openlog("portmap", debugging ? LOG_PID | LOG_PERROR : LOG_PID,
	    LOG_DAEMON);

E 2
	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
D 2
		perror("portmap cannot create socket");
E 2
I 2
		syslog(LOG_ERR, "cannot create udp socket: %m");
E 2
		exit(1);
	}

	addr.sin_addr.s_addr = 0;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PMAPPORT);
	if (bind(sock, (struct sockaddr *)&addr, len) != 0) {
D 2
		perror("portmap cannot bind");
E 2
I 2
		syslog(LOG_ERR, "cannot bind udp: %m");
E 2
		exit(1);
	}

	if ((xprt = svcudp_create(sock)) == (SVCXPRT *)NULL) {
D 2
		fprintf(stderr, "couldn't do udp_create\n");
E 2
I 2
		syslog(LOG_ERR, "couldn't do udp_create");
E 2
		exit(1);
	}
	/* make an entry for ourself */
	pml = (struct pmaplist *)malloc((u_int)sizeof(struct pmaplist));
	pml->pml_next = 0;
	pml->pml_map.pm_prog = PMAPPROG;
	pml->pml_map.pm_vers = PMAPVERS;
	pml->pml_map.pm_prot = IPPROTO_UDP;
	pml->pml_map.pm_port = PMAPPORT;
	pmaplist = pml;

	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
D 2
		perror("portmap cannot create socket");
E 2
I 2
		syslog(LOG_ERR, "cannot create tcp socket: %m");
E 2
		exit(1);
	}
	if (bind(sock, (struct sockaddr *)&addr, len) != 0) {
D 2
		perror("portmap cannot bind");
E 2
I 2
		syslog(LOG_ERR, "cannot bind udp: %m");
E 2
		exit(1);
	}
	if ((xprt = svctcp_create(sock, RPCSMALLMSGSIZE, RPCSMALLMSGSIZE))
	    == (SVCXPRT *)NULL) {
D 2
		fprintf(stderr, "couldn't do tcp_create\n");
E 2
I 2
		syslog(LOG_ERR, "couldn't do tcp_create");
E 2
		exit(1);
	}
	/* make an entry for ourself */
	pml = (struct pmaplist *)malloc((u_int)sizeof(struct pmaplist));
	pml->pml_map.pm_prog = PMAPPROG;
	pml->pml_map.pm_vers = PMAPVERS;
	pml->pml_map.pm_prot = IPPROTO_TCP;
	pml->pml_map.pm_port = PMAPPORT;
	pml->pml_next = pmaplist;
	pmaplist = pml;

	(void)svc_register(xprt, PMAPPROG, PMAPVERS, reg_service, FALSE);

	(void)signal(SIGCHLD, reap);
	svc_run();
D 2
	fprintf(stderr, "run_svc returned unexpectedly\n");
E 2
I 2
	syslog(LOG_ERR, "run_svc returned unexpectedly");
E 2
	abort();
}

I 2
#ifndef lint
/* need to override perror calls in rpc library */
void
perror(what)
D 3
	char *what;
E 3
I 3
	const char *what;
E 3
{

	syslog(LOG_ERR, "%s: %m", what);
}
#endif

E 2
static struct pmaplist *
find_service(prog, vers, prot)
D 2
	u_long prog;
	u_long vers;
E 2
I 2
	u_long prog, vers, prot;
E 2
{
	register struct pmaplist *hit = NULL;
	register struct pmaplist *pml;

	for (pml = pmaplist; pml != NULL; pml = pml->pml_next) {
		if ((pml->pml_map.pm_prog != prog) ||
			(pml->pml_map.pm_prot != prot))
			continue;
		hit = pml;
		if (pml->pml_map.pm_vers == vers)
		    break;
	}
	return (hit);
}

/* 
 * 1 OK, 0 not
 */
I 3
void
E 3
reg_service(rqstp, xprt)
	struct svc_req *rqstp;
	SVCXPRT *xprt;
{
	struct pmap reg;
	struct pmaplist *pml, *prevpml, *fnd;
	int ans, port;
	caddr_t t;
	
D 2
#ifdef DEBUG
	fprintf(stderr, "server: about do a switch\n");
#endif
E 2
I 2
	if (debugging)
		(void) fprintf(stderr, "server: about do a switch\n");
E 2
	switch (rqstp->rq_proc) {

	case PMAPPROC_NULL:
		/*
		 * Null proc call
		 */
D 2
		if ((!svc_sendreply(xprt, xdr_void, NULL)) && debugging) {
E 2
I 2
		if (!svc_sendreply(xprt, xdr_void, (caddr_t)0) && debugging) {
E 2
			abort();
		}
		break;

	case PMAPPROC_SET:
		/*
		 * Set a program,version to port mapping
		 */
		if (!svc_getargs(xprt, xdr_pmap, &reg))
			svcerr_decode(xprt);
		else {
			/*
			 * check to see if already used
			 * find_service returns a hit even if
			 * the versions don't match, so check for it
			 */
			fnd = find_service(reg.pm_prog, reg.pm_vers, reg.pm_prot);
			if (fnd && fnd->pml_map.pm_vers == reg.pm_vers) {
				if (fnd->pml_map.pm_port == reg.pm_port) {
					ans = 1;
					goto done;
				}
				else {
					ans = 0;
					goto done;
				}
			} else {
				/* 
				 * add to END of list
				 */
				pml = (struct pmaplist *)
				    malloc((u_int)sizeof(struct pmaplist));
				pml->pml_map = reg;
				pml->pml_next = 0;
				if (pmaplist == 0) {
					pmaplist = pml;
				} else {
					for (fnd= pmaplist; fnd->pml_next != 0;
					    fnd = fnd->pml_next);
					fnd->pml_next = pml;
				}
				ans = 1;
			}
		done:
			if ((!svc_sendreply(xprt, xdr_long, (caddr_t)&ans)) &&
			    debugging) {
D 2
				fprintf(stderr, "svc_sendreply\n");
E 2
I 2
				(void) fprintf(stderr, "svc_sendreply\n");
E 2
				abort();
			}
		}
		break;

	case PMAPPROC_UNSET:
		/*
		 * Remove a program,version to port mapping.
		 */
		if (!svc_getargs(xprt, xdr_pmap, &reg))
			svcerr_decode(xprt);
		else {
			ans = 0;
			for (prevpml = NULL, pml = pmaplist; pml != NULL; ) {
				if ((pml->pml_map.pm_prog != reg.pm_prog) ||
					(pml->pml_map.pm_vers != reg.pm_vers)) {
					/* both pml & prevpml move forwards */
					prevpml = pml;
					pml = pml->pml_next;
					continue;
				}
				/* found it; pml moves forward, prevpml stays */
				ans = 1;
				t = (caddr_t)pml;
				pml = pml->pml_next;
				if (prevpml == NULL)
					pmaplist = pml;
				else
					prevpml->pml_next = pml;
				free(t);
			}
			if ((!svc_sendreply(xprt, xdr_long, (caddr_t)&ans)) &&
			    debugging) {
D 2
				fprintf(stderr, "svc_sendreply\n");
E 2
I 2
				(void) fprintf(stderr, "svc_sendreply\n");
E 2
				abort();
			}
		}
		break;

	case PMAPPROC_GETPORT:
		/*
		 * Lookup the mapping for a program,version and return its port
		 */
		if (!svc_getargs(xprt, xdr_pmap, &reg))
			svcerr_decode(xprt);
		else {
			fnd = find_service(reg.pm_prog, reg.pm_vers, reg.pm_prot);
			if (fnd)
				port = fnd->pml_map.pm_port;
			else
				port = 0;
			if ((!svc_sendreply(xprt, xdr_long, (caddr_t)&port)) &&
			    debugging) {
D 2
				fprintf(stderr, "svc_sendreply\n");
E 2
I 2
				(void) fprintf(stderr, "svc_sendreply\n");
E 2
				abort();
			}
		}
		break;

	case PMAPPROC_DUMP:
		/*
		 * Return the current set of mapped program,version
		 */
		if (!svc_getargs(xprt, xdr_void, NULL))
			svcerr_decode(xprt);
		else {
			if ((!svc_sendreply(xprt, xdr_pmaplist,
			    (caddr_t)&pmaplist)) && debugging) {
D 2
				fprintf(stderr, "svc_sendreply\n");
E 2
I 2
				(void) fprintf(stderr, "svc_sendreply\n");
E 2
				abort();
			}
		}
		break;

	case PMAPPROC_CALLIT:
		/*
		 * Calls a procedure on the local machine.  If the requested
		 * procedure is not registered this procedure does not return
		 * error information!!
		 * This procedure is only supported on rpc/udp and calls via 
		 * rpc/udp.  It passes null authentication parameters.
		 */
		callit(rqstp, xprt);
		break;

	default:
		svcerr_noproc(xprt);
		break;
	}
}


/*
 * Stuff for the rmtcall service
 */
#define ARGSIZE 9000

D 3
typedef struct encap_parms {
E 3
I 3
struct encap_parms {
E 3
	u_long arglen;
	char *args;
};

static bool_t
xdr_encap_parms(xdrs, epp)
	XDR *xdrs;
	struct encap_parms *epp;
{

	return (xdr_bytes(xdrs, &(epp->args), &(epp->arglen), ARGSIZE));
}

D 3
typedef struct rmtcallargs {
E 3
I 3
struct rmtcallargs {
E 3
	u_long	rmt_prog;
	u_long	rmt_vers;
	u_long	rmt_port;
	u_long	rmt_proc;
	struct encap_parms rmt_args;
};

static bool_t
xdr_rmtcall_args(xdrs, cap)
	register XDR *xdrs;
	register struct rmtcallargs *cap;
{

	/* does not get a port number */
	if (xdr_u_long(xdrs, &(cap->rmt_prog)) &&
	    xdr_u_long(xdrs, &(cap->rmt_vers)) &&
	    xdr_u_long(xdrs, &(cap->rmt_proc))) {
		return (xdr_encap_parms(xdrs, &(cap->rmt_args)));
	}
	return (FALSE);
}

static bool_t
xdr_rmtcall_result(xdrs, cap)
	register XDR *xdrs;
	register struct rmtcallargs *cap;
{
	if (xdr_u_long(xdrs, &(cap->rmt_port)))
		return (xdr_encap_parms(xdrs, &(cap->rmt_args)));
	return (FALSE);
}

/*
 * only worries about the struct encap_parms part of struct rmtcallargs.
 * The arglen must already be set!!
 */
static bool_t
xdr_opaque_parms(xdrs, cap)
	XDR *xdrs;
	struct rmtcallargs *cap;
{

	return (xdr_opaque(xdrs, cap->rmt_args.args, cap->rmt_args.arglen));
}

/*
 * This routine finds and sets the length of incoming opaque paraters
 * and then calls xdr_opaque_parms.
 */
static bool_t
xdr_len_opaque_parms(xdrs, cap)
	register XDR *xdrs;
	struct rmtcallargs *cap;
{
	register u_int beginpos, lowpos, highpos, currpos, pos;

	beginpos = lowpos = pos = xdr_getpos(xdrs);
	highpos = lowpos + ARGSIZE;
	while ((int)(highpos - lowpos) >= 0) {
		currpos = (lowpos + highpos) / 2;
		if (xdr_setpos(xdrs, currpos)) {
			pos = currpos;
			lowpos = currpos + 1;
		} else {
			highpos = currpos - 1;
		}
	}
	xdr_setpos(xdrs, beginpos);
	cap->rmt_args.arglen = pos - beginpos;
	return (xdr_opaque_parms(xdrs, cap));
}

/*
 * Call a remote procedure service
 * This procedure is very quiet when things go wrong.
 * The proc is written to support broadcast rpc.  In the broadcast case,
 * a machine should shut-up instead of complain, less the requestor be
 * overrun with complaints at the expense of not hearing a valid reply ...
 *
 * This now forks so that the program & process that it calls can call 
 * back to the portmapper.
 */
D 3
static
E 3
I 3
static void
E 3
callit(rqstp, xprt)
	struct svc_req *rqstp;
	SVCXPRT *xprt;
{
	struct rmtcallargs a;
	struct pmaplist *pml;
	u_short port;
	struct sockaddr_in me;
D 2
	int pid, socket = -1;
E 2
I 2
	int pid, so = -1;
E 2
	CLIENT *client;
	struct authunix_parms *au = (struct authunix_parms *)rqstp->rq_clntcred;
	struct timeval timeout;
	char buf[ARGSIZE];

	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	a.rmt_args.args = buf;
	if (!svc_getargs(xprt, xdr_rmtcall_args, &a))
D 2
	    return;
	if ((pml = find_service(a.rmt_prog, a.rmt_vers, IPPROTO_UDP)) == NULL)
	    return;
E 2
I 2
		return;
	if ((pml = find_service(a.rmt_prog, a.rmt_vers,
	    (u_long)IPPROTO_UDP)) == NULL)
		return;
E 2
	/*
	 * fork a child to do the work.  Parent immediately returns.
	 * Child exits upon completion.
	 */
	if ((pid = fork()) != 0) {
D 2
		if (debugging && (pid < 0)) {
			fprintf(stderr, "portmap CALLIT: cannot fork.\n");
		}
E 2
I 2
		if (pid < 0)
			syslog(LOG_ERR, "CALLIT (prog %lu): fork: %m",
			    a.rmt_prog);
E 2
		return;
	}
	port = pml->pml_map.pm_port;
	get_myaddress(&me);
	me.sin_port = htons(port);
D 2
	client = clntudp_create(&me, a.rmt_prog, a.rmt_vers, timeout, &socket);
E 2
I 2
	client = clntudp_create(&me, a.rmt_prog, a.rmt_vers, timeout, &so);
E 2
	if (client != (CLIENT *)NULL) {
		if (rqstp->rq_cred.oa_flavor == AUTH_UNIX) {
			client->cl_auth = authunix_create(au->aup_machname,
			   au->aup_uid, au->aup_gid, au->aup_len, au->aup_gids);
		}
		a.rmt_port = (u_long)port;
		if (clnt_call(client, a.rmt_proc, xdr_opaque_parms, &a,
		    xdr_len_opaque_parms, &a, timeout) == RPC_SUCCESS) {
D 2
			svc_sendreply(xprt, xdr_rmtcall_result, &a);
E 2
I 2
			svc_sendreply(xprt, xdr_rmtcall_result, (caddr_t)&a);
E 2
		}
		AUTH_DESTROY(client->cl_auth);
		clnt_destroy(client);
	}
D 2
	(void)close(socket);
E 2
I 2
	(void)close(so);
E 2
	exit(0);
}

void
reap()
{
D 2
	while (wait3(NULL, WNOHANG, NULL) > 0);
E 2
I 2
	while (wait3((int *)NULL, WNOHANG, (struct rusage *)NULL) > 0);
E 2
}
E 1
