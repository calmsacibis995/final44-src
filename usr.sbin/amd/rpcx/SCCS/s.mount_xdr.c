h56947
s 00002/00002/00178
d D 8.1 93/06/06 12:07:29 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00179
d D 5.4 92/02/09 08:45:20 pendry 4 3
c merge in new release
e
s 00003/00002/00177
d D 5.3 91/05/12 15:58:29 pendry 3 2
c checkpoint for network tape
e
s 00001/00001/00178
d D 5.2 91/03/17 13:46:06 pendry 2 1
c from amd5.3 alpha11
e
s 00179/00000/00000
d D 5.1 90/07/19 15:50:32 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: mount_xdr.c,v 5.2 90/06/23 22:20:21 jsp Rel $
E 2
I 2
D 3
 * $Id: mount_xdr.c,v 5.2.1.1 90/10/21 22:30:21 jsp Exp $
E 2
 *
E 3
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: mount_xdr.c,v 5.2.1.2 91/05/07 22:18:55 jsp Alpha $
E 4
I 4
 * $Id: mount_xdr.c,v 5.2.2.1 1992/02/09 15:09:28 jsp beta $
E 4
 *
E 3
 */

#include "am.h"
#include "mount.h"


bool_t
xdr_fhandle(xdrs, objp)
	XDR *xdrs;
	fhandle objp;
{
	if (!xdr_opaque(xdrs, objp, FHSIZE)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_fhstatus(xdrs, objp)
	XDR *xdrs;
	fhstatus *objp;
{
	if (!xdr_u_int(xdrs, &objp->fhs_status)) {
		return (FALSE);
	}
	switch (objp->fhs_status) {
	case 0:
		if (!xdr_fhandle(xdrs, objp->fhstatus_u.fhs_fhandle)) {
			return (FALSE);
		}
		break;
	}
	return (TRUE);
}




bool_t
xdr_dirpath(xdrs, objp)
	XDR *xdrs;
	dirpath *objp;
{
	if (!xdr_string(xdrs, objp, MNTPATHLEN)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_name(xdrs, objp)
	XDR *xdrs;
	name *objp;
{
	if (!xdr_string(xdrs, objp, MNTNAMLEN)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_mountlist(xdrs, objp)
	XDR *xdrs;
	mountlist *objp;
{
	if (!xdr_pointer(xdrs, (char **)objp, sizeof(struct mountbody), xdr_mountbody)) {
		return (FALSE);
	}
	return (TRUE);
}



bool_t
xdr_mountbody(xdrs, objp)
	XDR *xdrs;
	mountbody *objp;
{
	if (!xdr_name(xdrs, &objp->ml_hostname)) {
		return (FALSE);
	}
	if (!xdr_dirpath(xdrs, &objp->ml_directory)) {
		return (FALSE);
	}
	if (!xdr_mountlist(xdrs, &objp->ml_next)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_groups(xdrs, objp)
	XDR *xdrs;
	groups *objp;
{
	if (!xdr_pointer(xdrs, (char **)objp, sizeof(struct groupnode), xdr_groupnode)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_groupnode(xdrs, objp)
	XDR *xdrs;
	groupnode *objp;
{
	if (!xdr_name(xdrs, &objp->gr_name)) {
		return (FALSE);
	}
	if (!xdr_groups(xdrs, &objp->gr_next)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_exports(xdrs, objp)
	XDR *xdrs;
	exports *objp;
{
	if (!xdr_pointer(xdrs, (char **)objp, sizeof(struct exportnode), xdr_exportnode)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_exportnode(xdrs, objp)
	XDR *xdrs;
	exportnode *objp;
{
	if (!xdr_dirpath(xdrs, &objp->ex_dir)) {
		return (FALSE);
	}
	if (!xdr_groups(xdrs, &objp->ex_groups)) {
		return (FALSE);
	}
	if (!xdr_exports(xdrs, &objp->ex_next)) {
		return (FALSE);
	}
	return (TRUE);
}


E 1
