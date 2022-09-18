h41987
s 00002/00002/00223
d D 8.1 93/06/06 12:07:22 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00224
d D 5.4 92/02/09 08:45:17 pendry 4 3
c merge in new release
e
s 00003/00002/00222
d D 5.3 91/05/12 15:58:25 pendry 3 2
c checkpoint for network tape
e
s 00001/00001/00223
d D 5.2 91/03/17 13:45:59 pendry 2 1
c from amd5.3 alpha11
e
s 00224/00000/00000
d D 5.1 90/07/19 15:50:30 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: amq_xdr.c,v 5.2 90/06/23 22:20:14 jsp Rel $
E 2
I 2
D 3
 * $Id: amq_xdr.c,v 5.2.1.1 90/10/21 22:30:16 jsp Exp $
E 2
 *
E 3
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
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
 * $Id: amq_xdr.c,v 5.2.1.2 91/05/07 22:18:51 jsp Alpha $
E 4
I 4
 * $Id: amq_xdr.c,v 5.2.2.1 1992/02/09 15:09:23 jsp beta $
E 4
 *
E 3
 */

#include "am.h"
#include "amq.h"


bool_t
xdr_amq_string(xdrs, objp)
	XDR *xdrs;
	amq_string *objp;
{
	if (!xdr_string(xdrs, objp, AMQ_STRLEN)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_time_type(xdrs, objp)
	XDR *xdrs;
	time_type *objp;
{
	if (!xdr_long(xdrs, objp)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_amq_mount_tree(xdrs, objp)
	XDR *xdrs;
	amq_mount_tree *objp;
{
	if (!xdr_amq_string(xdrs, &objp->mt_mountinfo)) {
		return (FALSE);
	}
	if (!xdr_amq_string(xdrs, &objp->mt_directory)) {
		return (FALSE);
	}
	if (!xdr_amq_string(xdrs, &objp->mt_mountpoint)) {
		return (FALSE);
	}
	if (!xdr_amq_string(xdrs, &objp->mt_type)) {
		return (FALSE);
	}
	if (!xdr_time_type(xdrs, &objp->mt_mounttime)) {
		return (FALSE);
	}
	if (!xdr_u_short(xdrs, &objp->mt_mountuid)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->mt_getattr)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->mt_lookup)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->mt_readdir)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->mt_readlink)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->mt_statfs)) {
		return (FALSE);
	}
	if (!xdr_pointer(xdrs, (char **)&objp->mt_next, sizeof(amq_mount_tree), xdr_amq_mount_tree)) {
		return (FALSE);
	}
	if (!xdr_pointer(xdrs, (char **)&objp->mt_child, sizeof(amq_mount_tree), xdr_amq_mount_tree)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_amq_mount_tree_p(xdrs, objp)
	XDR *xdrs;
	amq_mount_tree_p *objp;
{
	if (!xdr_pointer(xdrs, (char **)objp, sizeof(amq_mount_tree), xdr_amq_mount_tree)) {
		return (FALSE);
	}
	return (TRUE);
}



bool_t
xdr_amq_mount_info(xdrs, objp)
	XDR *xdrs;
	amq_mount_info *objp;
{
	if (!xdr_amq_string(xdrs, &objp->mi_type)) {
		return (FALSE);
	}
	if (!xdr_amq_string(xdrs, &objp->mi_mountpt)) {
		return (FALSE);
	}
	if (!xdr_amq_string(xdrs, &objp->mi_mountinfo)) {
		return (FALSE);
	}
	if (!xdr_amq_string(xdrs, &objp->mi_fserver)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->mi_error)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->mi_refc)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->mi_up)) {
		return (FALSE);
	}
	return (TRUE);
}



bool_t
xdr_amq_mount_info_list(xdrs, objp)
	XDR *xdrs;
	amq_mount_info_list *objp;
{
	if (!xdr_array(xdrs, (char **)&objp->amq_mount_info_list_val, (u_int *)&objp->amq_mount_info_list_len, ~0, sizeof(amq_mount_info), xdr_amq_mount_info)) {
		return (FALSE);
	}
	return (TRUE);
}



bool_t
xdr_amq_mount_tree_list(xdrs, objp)
	XDR *xdrs;
	amq_mount_tree_list *objp;
{
	if (!xdr_array(xdrs, (char **)&objp->amq_mount_tree_list_val, (u_int *)&objp->amq_mount_tree_list_len, ~0, sizeof(amq_mount_tree_p), xdr_amq_mount_tree_p)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_amq_mount_stats(xdrs, objp)
	XDR *xdrs;
	amq_mount_stats *objp;
{
	if (!xdr_int(xdrs, &objp->as_drops)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->as_stale)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->as_mok)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->as_merr)) {
		return (FALSE);
	}
	if (!xdr_int(xdrs, &objp->as_uerr)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_amq_opt(xdrs, objp)
	XDR *xdrs;
	amq_opt *objp;
{
	if (!xdr_enum(xdrs, (enum_t *)objp)) {
		return (FALSE);
	}
	return (TRUE);
}




bool_t
xdr_amq_setopt(xdrs, objp)
	XDR *xdrs;
	amq_setopt *objp;
{
	if (!xdr_amq_opt(xdrs, &objp->as_opt)) {
		return (FALSE);
	}
	if (!xdr_amq_string(xdrs, &objp->as_str)) {
		return (FALSE);
	}
	return (TRUE);
}


E 1
