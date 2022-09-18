/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	authunix_prot.c,v $
 * Revision 2.4  89/03/09  20:58:02  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:13:32  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  00:58:50  jsb
 * 	Include file references.
 * 	[89/01/17  15:04:25  jsb]
 * 
 */
/* @(#)authunix_prot.c	1.6 87/09/18 3.2/4.3NFSSRC */
/* @(#)authunix_prot.c	1.3 86/12/23 NFSSRC */
#ifndef	lint
static char sccsid[] = "@(#)authunix_prot.c 1.1 86/09/24 Copyr 1984 Sun Micro";
#endif

/*
 * authunix_prot.c
 * XDR for UNIX style authentication parameters for RPC
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
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

/*
 * XDR for unix authentication parameters.
 */
bool_t
xdr_authunix_parms(xdrs, p)
	register XDR *xdrs;
	register struct authunix_parms *p;
{

	if (xdr_u_long(xdrs, &(p->aup_time))
	    && xdr_string(xdrs, &(p->aup_machname), MAX_MACHINE_NAME)
	    && xdr_int(xdrs, &(p->aup_uid))
	    && xdr_int(xdrs, &(p->aup_gid))
	    && xdr_array(xdrs, (caddr_t *)&(p->aup_gids),
		    &(p->aup_len), NGRPS, sizeof(int), xdr_int) ) {
		return (TRUE);
	}
	return (FALSE);
}

#ifdef	KERNEL
/*
 * XDR kernel unix auth parameters.
 * Goes out of the u struct directly.
 * NOTE: this is an XDR_ENCODE only routine.
 */
xdr_authkern(xdrs)
	register XDR *xdrs;
{
	gid_t	*gp;
	int	 uid = (int)u.u_uid;
	int	 gid = (int)u.u_gid;
	int	 len;
	int	*lp;
	int	 groups[NGRPS];
	char	*name = hostname;

	if (xdrs->x_op != XDR_ENCODE) {
		return (FALSE);
	}

	for (gp = &u.u_groups[NGRPS]; gp > u.u_groups; gp--) {
		if (gp[-1] != NOGROUP) {
			break;
		}
	}
	len = gp - u.u_groups;
	for (lp = groups, gp = u.u_groups; lp < &groups[len]; gp++, lp++ )
                *lp = (int) *gp;

	lp = groups;
        if (xdr_u_long(xdrs, (u_long *)&time.tv_sec)
            && xdr_string(xdrs, &name, MAX_MACHINE_NAME)
            && xdr_int(xdrs, &uid)
            && xdr_int(xdrs, &gid)
	    && xdr_array(xdrs, (caddr_t *)&lp, (u_int *)&len, NGRPS,
	       sizeof (int), xdr_int) ) {
			return (TRUE);
	}
	return (FALSE);
}
#endif
