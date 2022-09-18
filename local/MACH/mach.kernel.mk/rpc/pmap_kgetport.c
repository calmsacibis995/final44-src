/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pmap_kgetport.c,v $
 * Revision 2.5  89/04/22  15:27:48  gm0w
 * 	Added include of <vfs/vfs.h> to get new macro definitions.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.4  89/03/09  20:58:35  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:14:15  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  01:00:46  jsb
 * 	Include file references.
 * 	[89/01/17  15:03:25  jsb]
 * 
 *
 *  3-Nov-87  Peter King (king) at NeXT, Inc.
 *	Changed struct pmap to struct portmap.
 *
 */ 

/* @(#)pmap_kgetport.c	1.2 87/06/22 3.2/4.3NFSSRC */
/* @(#)pmap_kgetport.c	1.4 87/03/17 NFSSRC */
#ifndef	lint
static char sccsid[] = "@(#)pmap_kgetport.c 1.1 86/09/24 Copyr 1986 Sun Micro";
#endif

/*
 * pmap_kgetport.c
 * Kernel interface to pmap rpc service.
 *
 * Copyright (C) 1986, Sun Microsystems, Inc.
 */

#include <sys/param.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <rpc/types.h>
#include <netinet/in.h>
#include <vfs/vfs.h>
#include <rpc/xdr.h>
#include <rpc/auth.h>
#include <rpc/clnt.h>
#include <rpc/rpc_msg.h>
#include <rpc/pmap_prot.h>

#include <sys/socket.h>
#include <net/if.h>

static struct ucred cred;
#define retries 4
static struct timeval tottimeout = { 1, 0 };


/*
 * Find the mapped port for program,version.
 * Calls the pmap service remotely to do the lookup.
 *
 * The 'address' argument is used to locate the portmapper, then
 * modified to contain the port number, if one was found.  If no
 * port number was found, 'address'->sin_port returns unchanged.
 *
 * Returns:	 0  if port number successfully found for 'program'
 *		-1  (<0) if 'program' was not registered
 *		 1  (>0) if there was an error contacting the portmapper
 */
int
pmap_kgetport(address, program, version, protocol)
	struct sockaddr_in *address;
	u_long program;
	u_long version;
	u_long protocol;
{
	u_short port = 0;
	register CLIENT *client;
	struct portmap parms;
	int error = 0;
	struct sockaddr_in tmpaddr;

	/* copy 'address' so that it doesn't get trashed */
	tmpaddr = *address;

	tmpaddr.sin_port = htons(PMAPPORT);
	client = clntkudp_create(&tmpaddr, PMAPPROG, PMAPVERS, retries, &cred);

	if (client != (CLIENT *)NULL) {
		parms.pm_prog = program;
		parms.pm_vers = version;
		parms.pm_prot = protocol;
		parms.pm_port = 0;  /* not needed or used */
		if (CLNT_CALL(client, PMAPPROC_GETPORT, xdr_pmap, &parms,
		    xdr_u_short, &port, tottimeout) != RPC_SUCCESS){
			error = 1;	/* error contacting portmapper */
		} else if (port == 0) {
			error = -1;	/* program not registered */
		} else {
			address->sin_port = htons(port);  /* save the port # */
		}
		AUTH_DESTROY(client->cl_auth);
		CLNT_DESTROY(client);
	}

	return (error);
}

/*
 * getport_loop -- kernel interface to pmap_kgetport()
 *
 * Talks to the portmapper using the sockaddr_in supplied by 'address',
 * to lookup the specified 'program'.
 *
 * Modifies 'address'->sin_port by rewriting the port number, if one
 * was found.  If a port number was not found (ie, return value != 0),
 * then 'address'->sin_port is left unchanged.
 *
 * If the portmapper does not respond, prints console message (once).
 * Retries forever, unless a signal is received.
 *
 * Returns:	 0  the port number was successfully put into 'address'
 *		-1  (<0) the requested process is not registered.
 *		 1  (>0) the portmapper did not respond and a signal occurred.
 */
getport_loop(address, program, version, protocol)
	struct sockaddr_in *address;
	u_long program;
	u_long version;
	u_long protocol;
{
	register int pe = 0;
	register int i = 0;

	/* sit in a tight loop until the portmapper responds */
	while ((i = pmap_kgetport(address, program, version, protocol)) > 0) {

		/* test to see if a signal has come in */
		if (ISSIG(u.u_procp)) {
			printf("Portmapper not responding; giving up\n");
			goto out;		/* got a signal */
		}
		/* print this message only once */
		if (pe++ == 0) {
			printf("Portmapper not responding; still trying\n");
		}
	}				/* go try the portmapper again */

	/* got a response...print message if there was a delay */
	if (pe != 0) {
		printf("Portmapper ok\n");
	}
out:
	return(i);	/* may return <0 if program not registered */
}
