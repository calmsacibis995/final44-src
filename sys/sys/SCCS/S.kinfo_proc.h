h21285
s 00009/00000/00055
d D 7.2 92/02/05 22:26:36 torek 2 1
c sparc vmspace is too big to include in its entirety
e
s 00055/00000/00000
d D 7.1 91/05/09 20:39:21 bostic 1 0
c date and time created 91/05/09 20:39:21 by bostic
e
u
U
t
T
I 1
/*
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef _KINFO_PROC_H_
#define	_KINFO_PROC_H_

#ifndef KERNEL
#include <sys/time.h>
#include <sys/ucred.h>
#include <sys/proc.h>
#include <vm/vm.h>
#endif

/* 
 * getkerninfo() proc ops return arrays of augmented proc structures:
 */
struct kinfo_proc {
	struct	proc kp_proc;			/* proc structure */
	struct	eproc {
		struct	proc *e_paddr;		/* address of proc */
		struct	session *e_sess;	/* session pointer */
		struct	pcred e_pcred;		/* process credentials */
		struct	ucred e_ucred;		/* current credentials */
I 2
#ifdef sparc
		struct {
			segsz_t	vm_rssize;	/* resident set size */
			segsz_t	vm_tsize;	/* text size */
			segsz_t	vm_dsize;	/* data size */
			segsz_t	vm_ssize;	/* stack size */
		} e_vm;
#else
E 2
		struct	vmspace e_vm;		/* address space */
I 2
#endif
E 2
		pid_t	e_ppid;			/* parent process id */
		pid_t	e_pgid;			/* process group id */
		short	e_jobc;			/* job control counter */
		dev_t	e_tdev;			/* controlling tty dev */
		pid_t	e_tpgid;		/* tty process group id */
		struct	session *e_tsess;	/* tty session pointer */
#define	WMESGLEN	7
		char	e_wmesg[WMESGLEN+1];	/* wchan message */
		segsz_t e_xsize;		/* text size */
		short	e_xrssize;		/* text rss */
		short	e_xccount;		/* text references */
		short	e_xswrss;
		long	e_flag;
#define	EPROC_CTTY	0x01	/* controlling tty vnode active */
#define	EPROC_SLEADER	0x02	/* session leader */
		char	e_login[MAXLOGNAME];	/* setlogin() name */
		long	e_spare[4];
	} kp_eproc;
};

#ifdef KERNEL
void	fill_eproc __P((struct proc *, struct eproc *));
#endif

#endif	/* !_KINFO_PROC_H_ */
E 1
