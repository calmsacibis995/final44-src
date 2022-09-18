h45861
s 00002/00002/00153
d D 8.1 93/06/06 12:07:16 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00154
d D 5.4 92/02/09 08:45:12 pendry 4 3
c merge in new release
e
s 00003/00002/00152
d D 5.3 91/05/12 15:58:27 pendry 3 2
c checkpoint for network tape
e
s 00032/00003/00122
d D 5.2 91/03/17 13:45:52 pendry 2 1
c from amd5.3 alpha11
e
s 00125/00000/00000
d D 5.1 90/07/19 15:50:29 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: amq_clnt.c,v 5.2 90/06/23 22:20:16 jsp Rel $
E 2
I 2
D 3
 * $Id: amq_clnt.c,v 5.2.1.2 91/03/17 17:39:38 jsp Alpha $
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
 * $Id: amq_clnt.c,v 5.2.1.3 91/05/07 22:18:52 jsp Alpha $
E 4
I 4
 * $Id: amq_clnt.c,v 5.2.2.1 1992/02/09 15:09:24 jsp beta $
E 4
 *
E 3
 */

#include "am.h"
#include "amq.h"

D 2
/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };
E 2
I 2
static struct timeval TIMEOUT = { ALLOWED_MOUNT_TIME, 0 };
E 2

voidp
amqproc_null_1(argp, clnt)
	voidp argp;
	CLIENT *clnt;
{
	static char res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, AMQPROC_NULL, xdr_void, argp, xdr_void, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return ((voidp)&res);
}


amq_mount_tree_p *
amqproc_mnttree_1(argp, clnt)
	amq_string *argp;
	CLIENT *clnt;
{
	static amq_mount_tree_p res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, AMQPROC_MNTTREE, xdr_amq_string, argp, xdr_amq_mount_tree_p, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&res);
}


voidp
amqproc_umnt_1(argp, clnt)
	amq_string *argp;
	CLIENT *clnt;
{
	static char res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, AMQPROC_UMNT, xdr_amq_string, argp, xdr_void, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return ((voidp)&res);
}


amq_mount_stats *
amqproc_stats_1(argp, clnt)
	voidp argp;
	CLIENT *clnt;
{
	static amq_mount_stats res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, AMQPROC_STATS, xdr_void, argp, xdr_amq_mount_stats, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&res);
}


amq_mount_tree_list *
amqproc_export_1(argp, clnt)
	voidp argp;
	CLIENT *clnt;
{
	static amq_mount_tree_list res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, AMQPROC_EXPORT, xdr_void, argp, xdr_amq_mount_tree_list, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&res);
}

int *
amqproc_setopt_1(argp, clnt)
	amq_setopt *argp;
	CLIENT *clnt;
{
	static int res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, AMQPROC_SETOPT, xdr_amq_setopt, argp, xdr_int, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&res);
}


amq_mount_info_list *
amqproc_getmntfs_1(argp, clnt)
	voidp argp;
	CLIENT *clnt;
{
	static amq_mount_info_list res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, AMQPROC_GETMNTFS, xdr_void, argp, xdr_amq_mount_info_list, &res, TIMEOUT) != RPC_SUCCESS) {
I 2
		return (NULL);
	}
	return (&res);
}


int *
amqproc_mount_1(argp, clnt)
	voidp argp;
	CLIENT *clnt;
{
	static int res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, AMQPROC_MOUNT, xdr_amq_string, argp, xdr_int, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&res);
}


amq_string *
amqproc_getvers_1(argp, clnt)
	voidp argp;
	CLIENT *clnt;
{
	static amq_string res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, AMQPROC_GETVERS, xdr_void, argp, xdr_amq_string, &res, TIMEOUT) != RPC_SUCCESS) {
E 2
		return (NULL);
	}
	return (&res);
}

E 1
