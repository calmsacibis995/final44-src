h07086
s 00002/00002/00254
d D 8.1 93/06/10 23:33:07 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00023/00023/00233
d D 7.4 92/10/11 11:29:21 bostic 4 3
c make kernel includes standard
e
s 00032/00026/00224
d D 7.3 92/09/13 11:58:56 ralph 3 2
c fix gcc2 warnings
e
s 00001/00001/00249
d D 7.2 92/03/28 21:46:13 ralph 2 1
c changes for p_md.md_regs
e
s 00250/00000/00000
d D 7.1 92/01/07 20:51:01 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
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
 * the Systems Programming Group of the University of Utah Computer
 * Science Department and Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: hpux_compat.c 1.41 91/04/06$
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Various ULTRIX compatibility routines
 */

#ifdef ULTRIXCOMPAT

D 4
#include "param.h"
#include "systm.h"
#include "signalvar.h"
#include "kernel.h"
#include "filedesc.h"
#include "proc.h"
#include "buf.h"
#include "wait.h"
#include "file.h"
#include "namei.h"
#include "vnode.h"
#include "ioctl.h"
#include "ptrace.h"
#include "stat.h"
#include "syslog.h"
#include "malloc.h"
#include "mount.h"
#include "ipc.h"
#include "user.h"
E 4
I 4
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/signalvar.h>
#include <sys/kernel.h>
#include <sys/filedesc.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <sys/namei.h>
#include <sys/vnode.h>
#include <sys/ioctl.h>
#include <sys/ptrace.h>
#include <sys/stat.h>
#include <sys/syslog.h>
#include <sys/malloc.h>
#include <sys/mount.h>
#include <sys/ipc.h>
#include <sys/user.h>
E 4

D 4
#include "machine/cpu.h"
#include "machine/reg.h"
#include "machine/psl.h"
#include "machine/vmparam.h"
E 4
I 4
#include <machine/cpu.h>
#include <machine/reg.h>
#include <machine/psl.h>
#include <machine/vmparam.h>
E 4

#ifdef DEBUG
int unimpresponse = 0;
#endif

/* YP domainname */
char	domainname[MAXHOSTNAMELEN] = "unknown";
int	domainnamelen = 7;

notimp(p, uap, retval)
	struct proc *p;
	void *uap;
	int *retval;
{
	int error = 0;
#ifdef notdef
	register int *argp = uap;
	extern char *ultrixsyscallnames[];

	printf("ULTRIX %s(", ultrixsyscallnames[code]);
	if (nargs)
		while (nargs--)
			printf("%x%c", *argp++, nargs? ',' : ')');
	else
		printf(")");
	printf("\n");
	switch (unimpresponse) {
	case 0:
		error = nosys(p, uap, retval);
		break;
	case 1:
		error = EINVAL;
		break;
	}
#else
D 2
	uprintf("ULTRIX system call %d not implemented\n", p->p_regs[V0]);
E 2
I 2
	uprintf("ULTRIX system call %d not implemented\n", p->p_md.md_regs[V0]);
E 2
	error = nosys(p, uap, retval);
#endif
	return (error);
}

I 3
struct wait3_args {
	int	*status;
	int	options;
	int	rusage;
};

E 3
ultrixwait3(p, uap, retval)
	struct proc *p;
D 3
	struct args {
		int	*status;
		int	options;
		int	rusage;
	} *uap;
E 3
I 3
	struct wait3_args *uap;
E 3
	int *retval;
{
	struct {
		int	pid;
		int	*status;
		int	options;
		struct	rusage *rusage;
		int	compat;
	} bsd_uap;

	/* rusage pointer must be zero */
	if (uap->rusage)
		return (EINVAL);
	bsd_uap.pid = WAIT_ANY;
	bsd_uap.status = uap->status;
	bsd_uap.options = 0;
	bsd_uap.rusage = 0;
	bsd_uap.compat = 0;
	return (wait1(p, &bsd_uap, retval));
}

I 3
struct domainname_args {
	char	*domainname;
	u_int	len;
};

E 3
ultrixgetdomainname(p, uap, retval)
	struct proc *p;
D 3
	register struct args {
		char	*domainname;
		u_int	len;
	} *uap;
E 3
I 3
	register struct domainname_args *uap;
E 3
	int *retval;
{
	if (uap->len > domainnamelen + 1)
		uap->len = domainnamelen + 1;
	return (copyout(domainname, uap->domainname, uap->len));
}

ultrixsetdomainname(p, uap, retval)
	struct proc *p;
D 3
	register struct args {
		char	*domainname;
		u_int	len;
	} *uap;
E 3
I 3
	register struct domainname_args *uap;
E 3
	int *retval;
{
	int error;

	if (error = suser(p->p_ucred, &p->p_acflag))
		return (error);
	if (uap->len > sizeof (domainname) - 1)
		return (EINVAL);
	domainnamelen = uap->len;
	error = copyin(uap->domainname, domainname, uap->len);
	domainname[domainnamelen] = 0;
	return (error);
}

I 3
struct getpgrp_args {
	int pid;
};

E 3
/*
 * This is the equivalent of BSD getpgrp but with more restrictions.
 * Note we do not check the real uid or "saved" uid.
 */
ultrixgetpgrp(cp, uap, retval)
	struct proc *cp;
D 3
	register struct args {
		int pid;
	} *uap;
E 3
I 3
	register struct getpgrp_args *uap;
E 3
	int *retval;
{
	register struct proc *p;

	if (uap->pid == 0)
		uap->pid = cp->p_pid;
	p = pfind(uap->pid);
	if (p == 0)
		return (ESRCH);
	if (cp->p_ucred->cr_uid && p->p_ucred->cr_uid != cp->p_ucred->cr_uid &&
	    !inferior(p))
		return (EPERM);
	*retval = p->p_pgid;
	return (0);
}

I 3
struct setpgrp_args {
	int	pid;
	int	pgrp;
} *uap;
E 3
/*
 * This is the equivalent of BSD setpgrp but with more restrictions.
 * Note we do not check the real uid or "saved" uid or pgrp.
 */
ultrixsetpgrp(p, uap, retval)
	struct proc *p;
D 3
	struct args {
		int	pid;
		int	pgrp;
	} *uap;
E 3
I 3
	struct setpgrp_args *uap;
E 3
	int *retval;
{
	/* empirically determined */
	if (uap->pgrp < 0 || uap->pgrp >= 30000)
		return (EINVAL);
	return (setpgid(p, uap, retval));
}

I 3
struct sigvec_args {
	int	signo;
	struct	sigvec *nsv;
	struct	sigvec *osv;
	caddr_t	sigcode;	/* handler return address */
};

E 3
ultrixsigvec(p, uap, retval)
	struct proc *p;
D 3
	register struct args {
		int	signo;
		struct	sigvec *nsv;
		struct	sigvec *osv;
		caddr_t	sigcode;	/* handler return address */
	} *uap;
E 3
I 3
	register struct sigvec_args *uap;
E 3
	int *retval;
{
	return (osigvec(p, uap, retval));
}

ultrixsigcleanup(p, uap, retval)
	struct proc *p;
	void *uap;
	int *retval;
{
	printf("ultrixsigcleanup %s %d\n", p->p_comm, p->p_pid); /* XXX */
	return (ENOSYS);
}

ultrixsigreturn(p, uap, retval)
	struct proc *p;
	void *uap;
	int *retval;
{
	printf("ultrixsigreturn %s %d\n", p->p_comm, p->p_pid); /* XXX */
	return (ENOSYS);
}

/*
 * Switch process from ULTRIX emulation to BSD.
 */
ultrixtobsd(p, uap, retval)
	struct proc *p;
	void *uap;
	int *retval;
{

	p->p_md.md_flags &= ~MDP_ULTRIX;
	return (0);
}

ultrixgetsysinfo(p, uap, retval)
	struct proc *p;
	void *uap;
	int *retval;
{

	/*
	 * Just return a 0.  This says that the requested information is
	 * not available which is certainly true for the most part.
	 */
	retval[0] = 0;
	return (0);
}

#endif
E 1
