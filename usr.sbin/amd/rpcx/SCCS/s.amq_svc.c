h64603
s 00002/00002/00108
d D 8.1 93/06/06 12:07:19 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00109
d D 5.4 92/02/09 08:45:15 pendry 4 3
c merge in new release
e
s 00003/00002/00107
d D 5.3 91/05/12 15:58:24 pendry 3 2
c checkpoint for network tape
e
s 00014/00001/00095
d D 5.2 91/03/17 13:45:56 pendry 2 1
c from amd5.3 alpha11
e
s 00096/00000/00000
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
 * $Id: amq_svc.c,v 5.2 90/06/23 22:20:17 jsp Rel $
E 2
I 2
D 3
 * $Id: amq_svc.c,v 5.2.1.2 91/03/17 17:39:38 jsp Alpha $
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
 * $Id: amq_svc.c,v 5.2.1.3 91/05/07 22:18:53 jsp Alpha $
E 4
I 4
 * $Id: amq_svc.c,v 5.2.2.1 1992/02/09 15:09:26 jsp beta $
E 4
 *
E 3
 */

#include "am.h"
#include "amq.h"
extern bool_t xdr_amq_mount_info_qelem();

void
amq_program_1(rqstp, transp)
	struct svc_req *rqstp;
	SVCXPRT *transp;
{
	union {
		amq_string amqproc_mnttree_1_arg;
		amq_string amqproc_umnt_1_arg;
		amq_setopt amqproc_setopt_1_arg;
I 2
		amq_string amqproc_mount_1_arg;
E 2
	} argument;
	char *result;
	bool_t (*xdr_argument)(), (*xdr_result)();
	char *(*local)();

	switch (rqstp->rq_proc) {
	case AMQPROC_NULL:
		xdr_argument = xdr_void;
		xdr_result = xdr_void;
		local = (char *(*)()) amqproc_null_1;
		break;

	case AMQPROC_MNTTREE:
		xdr_argument = xdr_amq_string;
		xdr_result = xdr_amq_mount_tree_p;
		local = (char *(*)()) amqproc_mnttree_1;
		break;

	case AMQPROC_UMNT:
		xdr_argument = xdr_amq_string;
		xdr_result = xdr_void;
		local = (char *(*)()) amqproc_umnt_1;
		break;

	case AMQPROC_STATS:
		xdr_argument = xdr_void;
		xdr_result = xdr_amq_mount_stats;
		local = (char *(*)()) amqproc_stats_1;
		break;

	case AMQPROC_EXPORT:
		xdr_argument = xdr_void;
		xdr_result = xdr_amq_mount_tree_list;
		local = (char *(*)()) amqproc_export_1;
		break;

	case AMQPROC_SETOPT:
		xdr_argument = xdr_amq_setopt;
		xdr_result = xdr_int;
		local = (char *(*)()) amqproc_setopt_1;
		break;

	case AMQPROC_GETMNTFS:
		xdr_argument = xdr_void;
		xdr_result = xdr_amq_mount_info_qelem;
		local = (char *(*)()) amqproc_getmntfs_1;
I 2
		break;

	case AMQPROC_MOUNT:
		xdr_argument = xdr_amq_string;
		xdr_result = xdr_int;
		local = (char *(*)()) amqproc_mount_1;
		break;

	case AMQPROC_GETVERS:
		xdr_argument = xdr_void;
		xdr_result = xdr_amq_string;
		local = (char *(*)()) amqproc_getvers_1;
E 2
		break;

	default:
		svcerr_noproc(transp);
		return;
	}
	bzero((char *)&argument, sizeof(argument));
	if (!svc_getargs(transp, xdr_argument, &argument)) {
		svcerr_decode(transp);
		return;
	}
	result = (*local)(&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, xdr_result, result)) {
		svcerr_systemerr(transp);
	}
	if (!svc_freeargs(transp, xdr_argument, &argument)) {
		plog(XLOG_FATAL, "unable to free rpc arguments in amqprog_1");
		going_down(1);
	}
}

E 1
