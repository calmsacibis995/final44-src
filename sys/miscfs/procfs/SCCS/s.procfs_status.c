h62189
s 00002/00002/00117
d D 8.4 94/06/15 12:30:52 pendry 4 3
c merge in netbsd changes.
c security fixes, curproc becomes symlink, misc other trash.
e
s 00005/00005/00114
d D 8.3 94/02/17 09:22:17 pendry 3 2
c cleanup formatting
e
s 00002/00002/00117
d D 8.2 94/01/21 20:00:12 bostic 2 1
c copyright typo
e
s 00119/00000/00000
d D 8.1 94/01/05 12:34:11 pendry 1 0
c date and time created 94/01/05 12:34:11 by pendry
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1993 The Regents of the University of California.
E 2
 * Copyright (c) 1993 Jan-Simon Pendry
D 2
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * From:
 *	$Id: procfs_status.c,v 3.1 1993/12/15 09:40:17 jsp Exp $
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/resource.h>
#include <sys/resourcevar.h>
#include <miscfs/procfs/procfs.h>

int
procfs_dostatus(curp, p, pfs, uio)
	struct proc *curp;
	struct proc *p;
	struct pfsnode *pfs;
	struct uio *uio;
{
	struct session *sess;
	struct tty *tp;
	struct ucred *cr;
	char *ps;
	char *sep;
	int pid, ppid, pgid, sid;
	int i;
	int xlen;
	int error;
	char psbuf[256];		/* XXX - conservative */

	if (uio->uio_rw != UIO_READ)
		return (EOPNOTSUPP);

	pid = p->p_pid;
	ppid = p->p_pptr ? p->p_pptr->p_pid : 0,
	pgid = p->p_pgrp->pg_id;
	sess = p->p_pgrp->pg_session;
	sid = sess->s_leader ? sess->s_leader->p_pid : 0;

/* comm pid ppid pgid sid maj,min ctty,sldr start ut st wmsg uid groups ... */

	ps = psbuf;
	bcopy(p->p_comm, ps, MAXCOMLEN);
	ps[MAXCOMLEN] = '\0';
	ps += strlen(ps);
	ps += sprintf(ps, " %d %d %d %d ", pid, ppid, pgid, sid);

	if ((p->p_flag&P_CONTROLT) && (tp = sess->s_ttyp))
		ps += sprintf(ps, "%d,%d ", major(tp->t_dev), minor(tp->t_dev));
	else
		ps += sprintf(ps, "%d,%d ", -1, -1);

	sep = "";
	if (sess->s_ttyvp) {
		ps += sprintf(ps, "%sctty", sep);
		sep = ",";
	}
	if (SESS_LEADER(p)) {
		ps += sprintf(ps, "%ssldr", sep);
		sep = ",";
	}
	if (*sep != ',')
		ps += sprintf(ps, "noflags");

	if (p->p_flag & P_INMEM)
D 3
		ps += sprintf(ps, " %d %d",
E 3
I 3
		ps += sprintf(ps, " %d,%d",
E 3
			p->p_stats->p_start.tv_sec,
			p->p_stats->p_start.tv_usec);
	else
D 3
		ps += sprintf(ps, " -1 -1");
E 3
I 3
		ps += sprintf(ps, " -1,-1");
E 3
	
	{
		struct timeval ut, st;

		calcru(p, &ut, &st, (void *) 0);
D 3
		ps += sprintf(ps, " %d %d %d %d",
E 3
I 3
		ps += sprintf(ps, " %d,%d %d,%d",
E 3
			ut.tv_sec,
			ut.tv_usec,
			st.tv_sec,
			st.tv_usec);
	}

	ps += sprintf(ps, " %s",
		(p->p_wchan && p->p_wmesg) ? p->p_wmesg : "nochan");

	cr = p->p_ucred;

D 3
	ps += sprintf(ps, " %d %d", cr->cr_uid, cr->cr_gid);
E 3
I 3
D 4
	ps += sprintf(ps, " %d", cr->cr_uid, cr->cr_gid);
E 4
I 4
	ps += sprintf(ps, " %d", cr->cr_uid);
E 4
E 3
	for (i = 0; i < cr->cr_ngroups; i++)
D 3
		ps += sprintf(ps, " %d", cr->cr_groups[i]);
E 3
I 3
		ps += sprintf(ps, ",%d", cr->cr_groups[i]);
E 3
	ps += sprintf(ps, "\n");

	xlen = ps - psbuf;
	xlen -= uio->uio_offset;
	ps = psbuf + uio->uio_offset;
D 4
	xlen = min(xlen, uio->uio_resid);
E 4
I 4
	xlen = imin(xlen, uio->uio_resid);
E 4
	if (xlen <= 0)
		error = 0;
	else
		error = uiomove(ps, xlen, uio);

	return (error);
}
E 1
