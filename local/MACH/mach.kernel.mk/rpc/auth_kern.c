/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	auth_kern.c,v $
 * Revision 2.5  89/08/02  08:05:45  jsb
 * 	Eliminated MACH conditionals. Replaced kallocs with zallocs.
 * 	[89/07/31  16:54:11  jsb]
 * 
 * Revision 2.4  89/03/09  20:57:56  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:13:20  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  00:58:16  jsb
 * 	Include file references; include mach.h!
 * 	[89/01/17  14:28:12  jsb]
 * 
 *
 * 28-Oct-87  Peter King (king) at NeXT, Inc.
 *	Original Sun source, ported to Mach
 */ 

/* @(#)auth_kern.c	1.5 87/09/09 3.2/4.3NFSSRC */
/* @(#)auth_kern.c	1.3 86/12/23 NFSSRC */
#ifndef	lint
static char sccsid[] = "@(#)auth_kern.c 1.1 86/09/24 Copyr 1984 Sun Micro";
#endif

/*
 * auth_kern.c, Implements UNIX style authentication parameters in the kernel. 
 *  
 * Copyright (C) 1984, Sun Microsystems, Inc. 
 *
 * Interfaces with svc_auth_unix on the server.  See auth_unix.c for the user
 * level implementation of unix auth.
 *
 */


#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/auth.h>
#include <rpc/auth_unix.h>
#include <netinet/in.h>

/*
 * Unix authenticator operations vector
 */
void	authkern_nextverf();
bool_t	authkern_marshal();
bool_t	authkern_validate();
bool_t	authkern_refresh();
void	authkern_destroy();

static struct auth_ops auth_kern_ops = {
	authkern_nextverf,
	authkern_marshal,
	authkern_validate,
	authkern_refresh,
	authkern_destroy
};


/*
 * Create a kernel unix style authenticator.
 * Returns an auth handle.
 */
AUTH *
authkern_create()
{
	register AUTH *auth;

	/*
	 * Allocate and set up auth handle
	 */
	ZALLOC(rpc_auth_zone, auth, AUTH *);
	bzero(auth, (u_int)sizeof(*auth));
	auth->ah_ops = &auth_kern_ops;
	auth->ah_verf = _null_auth;
	return (auth);
}

/*
 * authkern operations
 */
/*ARGSUSED*/
void
authkern_nextverf(auth)
	AUTH *auth;
{

	/* no action necessary */
}

bool_t
authkern_marshal(auth, xdrs)
	AUTH *auth;
	XDR *xdrs;
{
	char	*sercred;
	XDR	xdrm;
	struct	opaque_auth *cred;
	bool_t	ret = FALSE;
	register gid_t *gp, *gpend;
	register int convint, gidlen, credsize;
	register long *ptr;

	/*
	 * First we try a fast path to get through
	 * this very common operation.
	 */
#if	NGRPS > NGROUPS || NGRPS > 8
	/*
	 *  NGRPS (auth_unix.h) must not be declared greater than
	 *  NGROUPS (param.h).  See comment in auth_unix.h.
	 *  This statement should cause a compiler error.
	 */
	ERROR-SEE_COMMENT;
#endif
	gp = u.u_groups;
	gpend = &u.u_groups[NGRPS];
	while (gpend > u.u_groups && gpend[-1] == NOGROUP)
		gpend--;
	gidlen = gpend - gp;
	credsize = 4 + 4 + roundup(hostnamelen, 4) + 4 + 4 + 4 + gidlen * 4;
	ptr = XDR_INLINE(xdrs, 4 + 4 + credsize + 4 + 4);
	if (ptr) {
		/*
		 * We can do the fast path.
		 */
		IXDR_PUT_LONG(ptr, AUTH_UNIX);	/* cred flavor */
		IXDR_PUT_LONG(ptr, credsize);	/* cred len */
		IXDR_PUT_LONG(ptr, time.tv_sec);
		IXDR_PUT_LONG(ptr, hostnamelen);
		bcopy(hostname, (caddr_t)ptr, (u_int)hostnamelen);
		ptr += roundup(hostnamelen, 4) / 4;
		convint = (int)u.u_uid;
		IXDR_PUT_LONG(ptr, convint);
		convint = (int)u.u_gid;
		IXDR_PUT_LONG(ptr, convint);
		IXDR_PUT_LONG(ptr, gidlen);
		while (gp < gpend) {
			convint = (int)*gp++;
			IXDR_PUT_LONG(ptr, convint);
		}
		IXDR_PUT_LONG(ptr, AUTH_NULL);	/* verf flavor */
		IXDR_PUT_LONG(ptr, 0);	/* verf len */
		return (TRUE);
	}
	ZALLOC(rpc_sercred_zone, sercred, char *);
	/*
	 * serialize u struct stuff into sercred
	 */
	xdrmem_create(&xdrm, sercred, MAX_AUTH_BYTES, XDR_ENCODE);
	if (! xdr_authkern(&xdrm)) {
		printf("authkern_marshal: xdr_authkern failed\n");
		ret = FALSE;
		goto done;
	}

	/*
	 * Make opaque auth credentials that point at serialized u struct
	 */
	cred = &(auth->ah_cred);
	cred->oa_length = XDR_GETPOS(&xdrm);
	cred->oa_flavor = AUTH_UNIX;
	cred->oa_base = sercred;

	/*
	 * serialize credentials and verifiers (null)
	 */
	if ((xdr_opaque_auth(xdrs, &(auth->ah_cred)))
	    && (xdr_opaque_auth(xdrs, &(auth->ah_verf)))) {
		ret = TRUE;
	} else {
		ret = FALSE;
	}
done:
	ZFREE(rpc_sercred_zone, sercred);
	return (ret);
}

/*ARGSUSED*/
bool_t
authkern_validate(auth, verf)
	AUTH *auth;
	struct opaque_auth verf;
{

	return (TRUE);
}

/*ARGSUSED*/
bool_t
authkern_refresh(auth)
	AUTH *auth;
{
}

void
authkern_destroy(auth)
	register AUTH *auth;
{

	ZFREE(rpc_auth_zone, auth);
}
