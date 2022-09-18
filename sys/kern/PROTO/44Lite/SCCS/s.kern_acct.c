h41394
s 00004/00005/00097
d D 8.3 95/05/25 13:22:19 mckusick 7 5
c new system call argument convention
e
s 00003/00004/00098
d R 8.3 95/05/25 13:20:21 mckusick 6 5
c new system call argument convention
e
s 00014/00002/00088
d D 8.2 94/06/02 18:35:15 mckusick 5 3
c have to check for dead vnodes when checking whether to do accounting
e
s 00013/00001/00089
d R 8.2 94/06/02 18:32:53 mckusick 4 3
c have to check for dead vnodes when checking whether to do accounting
e
s 00059/00070/00031
d D 8.1 94/01/21 18:45:59 mckusick 3 2
c update for 4.4BSD-Lite
e
s 00002/00000/00099
d D 1.2 91/06/29 19:20:34 mckusick 2 1
c fix syntax errors
e
s 00099/00000/00000
d D 1.1 91/05/11 15:31:08 mckusick 1 0
c date and time created 91/05/11 15:31:08 by mckusick
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 3
I 3
/*-
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 3
 *
 * %sccs.include.redist.c%
 *
D 3
 *	from: @(#)kern_acct.c	7.18 (Berkeley) 5/11/91
E 3
I 3
D 5
 *	from: @(#)kern_acct.c	8.1 (Berkeley) 6/14/93
E 5
I 5
D 7
 *	from: @(#)kern_acct.c	8.4 (Berkeley) 6/2/94
E 7
I 7
 *	from: @(#)kern_acct.c 8.8 (Berkeley) 5/14/95
E 7
E 5
E 3
 */

D 3
#include "param.h"
#include "systm.h"
#include "namei.h"
#include "resourcevar.h"
#include "proc.h"
#include "ioctl.h"
#include "termios.h"
#include "tty.h"
#include "vnode.h"
#include "mount.h"
#include "kernel.h"
#include "file.h"
#include "acct.h"
#include "syslog.h"
E 3
I 3
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/mount.h>
#include <sys/vnode.h>
#include <sys/file.h>
#include <sys/syslog.h>
#include <sys/kernel.h>
E 3

D 3
/*
 * Values associated with enabling and disabling accounting
 */
int	acctsuspend = 2;	/* stop accounting when < 2% free space left */
int	acctresume = 4;		/* resume when free space risen to > 4% */
struct	timeval chk = { 15, 0 };/* frequency to check space for accounting */
I 2
struct  vnode *acctp;		/* file to which to do accounting */
struct  vnode *savacctp;	/* file to which to do accounting when space */
E 3
I 3
D 7
struct acct_args {
	char	*fname;
};
E 7
acct(a1, a2, a3)
	struct proc *a1;
D 7
	struct acct_args *a2;
E 7
I 7
	struct acct_args /* {
		syscallarg(char *) path;
	} */ *a2;
E 7
	int *a3;
{
	/*
	 * Body deleted.
	 */
	return (ENOSYS);
}
E 3
E 2

D 3
/*
 * Enable or disable process accounting.
 *
 * If a non-null filename is given, that file is used to store accounting
 * records on process exit. If a null filename is given process accounting
 * is suspended. If accounting is enabled, the system checks the amount
 * of freespace on the filesystem at timeval intervals. If the amount of
 * freespace is below acctsuspend percent, accounting is suspended. If
 * accounting has been suspended, and freespace rises above acctresume,
 * accounting is resumed.
 */
/* ARGSUSED */
sysacct(p, uap, retval)
	struct proc *p;
	struct args {
		char	*fname;
	} *uap;
	int *retval;
E 3
I 3
acct_process(a1)
	struct proc *a1;
E 3
{

	/*
	 * Body deleted.
	 */
D 3
	return (ENOSYS);
E 3
I 3
	return;
E 3
}

/*
 * Periodically check the file system to see if accounting
D 5
 * should be turned on or off.
E 5
I 5
 * should be turned on or off. Beware the case where the vnode
 * has been vgone()'d out from underneath us, e.g. when the file
 * system containing the accounting file has been forcibly unmounted.
E 5
 */
D 3
acctwatch(resettime)
	struct timeval *resettime;
E 3
I 3

/*
 * Values associated with enabling and disabling accounting
 */
int	acctsuspend = 2;	/* stop accounting when < 2% free space left */
int	acctresume = 4;		/* resume when free space risen to > 4% */
int	acctchkfreq = 15;	/* frequency (in seconds) to check space */

/*
 * SHOULD REPLACE THIS WITH A DRIVER THAT CAN BE READ TO SIMPLIFY.
 */
struct	vnode *acctp;
struct	vnode *savacctp;

/* ARGSUSED */
void
acctwatch(a)
	void *a;
E 3
{
	struct statfs sb;

	if (savacctp) {
I 5
		if (savacctp->v_type == VBAD) {
			(void) vn_close(savacctp, FWRITE, NOCRED, NULL);
			savacctp = NULL;
			return;
		}
E 5
		(void)VFS_STATFS(savacctp->v_mount, &sb, (struct proc *)0);
		if (sb.f_bavail > acctresume * sb.f_blocks / 100) {
			acctp = savacctp;
			savacctp = NULL;
			log(LOG_NOTICE, "Accounting resumed\n");
I 3
		}
	} else {
		if (acctp == NULL)
E 3
			return;
I 5
		if (acctp->v_type == VBAD) {
			(void) vn_close(acctp, FWRITE, NOCRED, NULL);
			acctp = NULL;
			return;
		}
E 5
I 3
		(void)VFS_STATFS(acctp->v_mount, &sb, (struct proc *)0);
		if (sb.f_bavail <= acctsuspend * sb.f_blocks / 100) {
			savacctp = acctp;
			acctp = NULL;
			log(LOG_NOTICE, "Accounting suspended\n");
E 3
		}
	}
D 3
	if (acctp == NULL)
		return;
	(void)VFS_STATFS(acctp->v_mount, &sb, (struct proc *)0);
	if (sb.f_bavail <= acctsuspend * sb.f_blocks / 100) {
		savacctp = acctp;
		acctp = NULL;
		log(LOG_NOTICE, "Accounting suspended\n");
	}
	timeout(acctwatch, (caddr_t)resettime, hzto(resettime));
}

/*
 * This routine calculates an accounting record for a process and,
 * if accounting is enabled, writes it to the accounting file.
 */
acct(p)
	register struct proc *p;
{

	/*
	 * Body deleted.
	 */
	return;
E 3
I 3
	timeout(acctwatch, NULL, acctchkfreq * hz);
E 3
}
E 1
