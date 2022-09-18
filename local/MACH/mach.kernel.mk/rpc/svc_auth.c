/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	svc_auth.c,v $
 * Revision 2.4  89/03/09  20:59:41  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:15:24  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  01:04:06  jsb
 * 	Include file references.
 * 	[89/01/17  14:32:45  jsb]
 * 
 */
/* @(#)svc_auth.c	1.3 87/09/18 3.2/4.3NFSSRC */
/* @(#)svc_auth.c	1.3 87/03/02 NFSSRC */
#ifndef	lint
static char sccsid[] = "@(#)svc_auth.c 1.1 86/09/24 Copyr 1984 Sun Micro";
#endif

/*
 * svc_auth.c, Server-side rpc authenticator interface.
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 */

#ifdef	KERNEL
#include <sys/param.h>
#include <netinet/in.h>
#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/auth.h>
#include <rpc/clnt.h>
#include <rpc/rpc_msg.h>
#include <rpc/svc.h>
#include <rpc/svc_auth.h>
#else
#include <rpc/rpc.h>
#endif

/*
 * svcauthsw is the bdevsw of server side authentication. 
 * 
 * Server side authenticators are called from authenticate by
 * using the client auth struct flavor field to index into svcauthsw.
 * The server auth flavors must implement a routine that looks  
 * like: 
 * 
 *	enum auth_stat 
 *	flavorx_auth(rqst, msg)
 *		register struct svc_req *rqst; 
 *		register struct rpc_msg *msg;
 *  
 */

enum auth_stat _svcauth_null();		/* no authentication */
enum auth_stat _svcauth_unix();		/* unix style (uid, gids) */
enum auth_stat _svcauth_short();	/* short hand unix style */

static struct {
	enum auth_stat (*authenticator)();
} svcauthsw[] = {
	_svcauth_null,			/* AUTH_NULL */
	_svcauth_unix,			/* AUTH_UNIX */
	_svcauth_short,			/* AUTH_SHORT */
	_svcauth_null			/* AUTH_DES */
};
#define AUTH_MAX	3		/* HIGHEST AUTH NUMBER */


/*
 * The call rpc message, msg has been obtained from the wire.  The msg contains
 * the raw form of credentials and verifiers.  authenticate returns AUTH_OK
 * if the msg is successfully authenticated.  If AUTH_OK then the routine also
 * does the following things:
 * set rqst->rq_xprt->verf to the appropriate response verifier;
 * sets rqst->rq_client_cred to the "cooked" form of the credentials.
 *
 * NB: rqst->rq_cxprt->verf must be pre-alloctaed;
 * its length is set appropriately.
 *
 * The caller still owns and is responsible for msg->u.cmb.cred and
 * msg->u.cmb.verf.  The authentication system retains ownership of
 * rqst->rq_client_cred, the cooked credentials.
 */
enum auth_stat
_authenticate(rqst, msg)
	register struct svc_req *rqst;
	struct rpc_msg *msg;
{
	register int cred_flavor;

	rqst->rq_cred = msg->rm_call.cb_cred;
	rqst->rq_xprt->xp_verf.oa_flavor = _null_auth.oa_flavor;
	rqst->rq_xprt->xp_verf.oa_length = 0;
	cred_flavor = rqst->rq_cred.oa_flavor;
	if ((cred_flavor <= AUTH_MAX) && (cred_flavor >= AUTH_NULL)) {
		return ((*(svcauthsw[cred_flavor].authenticator))(rqst, msg));
	}

	return (AUTH_REJECTEDCRED);
}

enum auth_stat
_svcauth_null(/*rqst, msg*/)
	/*struct svc_req *rqst;
	struct rpc_msg *msg;*/
{

	return (AUTH_OK);
}
