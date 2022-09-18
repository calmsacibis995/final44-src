h35431
s 00020/00051/00018
d D 8.1 94/01/21 18:46:02 mckusick 2 1
c update for 4.4BSD-Lite
e
s 00069/00000/00000
d D 1.1 91/05/11 15:31:08 mckusick 1 0
c date and time created 91/05/11 15:31:08 by mckusick
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1982, 1986, 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1982, 1986, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 2
 *
 * %sccs.include.redist.c%
 *
D 2
 *	from: @(#)kern_exec.c	7.43 (Berkeley) 5/9/91
E 2
I 2
 *	from: @(#)kern_exec.c	8.1 (Berkeley) 6/10/93
E 2
 */

D 2
#include "param.h"
#include "systm.h"
#include "filedesc.h"
#include "kernel.h"
#include "proc.h"
#include "mount.h"
#include "malloc.h"
#include "namei.h"
#include "vnode.h"
#include "seg.h"
#include "file.h"
#include "acct.h"
#include "exec.h"
#include "ktrace.h"
#include "resourcevar.h"
E 2
I 2
#include <sys/param.h>
#include <sys/errno.h>
#include <sys/proc.h>
E 2

D 2
#include "machine/cpu.h"
#include "machine/reg.h"

#include "mman.h"
#include "vm/vm.h"
#include "vm/vm_param.h"
#include "vm/vm_map.h"
#include "vm/vm_kern.h"
#include "vm/vm_pager.h"

#include "signalvar.h"
#include "kinfo_proc.h"

#ifdef HPUXCOMPAT
#include "user.h"			/* for pcb */
#include "hp300/hpux/hpux_exec.h"
#endif

#ifdef COPY_SIGCODE
extern char sigcode[], esigcode[];
#define	szsigcode	(esigcode - sigcode)
#else
#define	szsigcode	0
#endif

E 2
/*
 * exec system call
 */
I 2
struct execve_args {
	char	*fname;
	char	**argp;
	char	**envp;
};
E 2
/* ARGSUSED */
D 2
execve(p, uap, retval)
	register struct proc *p;
	register struct args {
		char	*fname;
		char	**argp;
		char	**envp;
	} *uap;
	int *retval;
E 2
I 2
execve(a1, a2, a3)
	struct proc *a1;
	struct execve_args *a2;
	int *a3;
E 2
{

	/*
	 * Body deleted.
	 */
	return (ENOSYS);
}
E 1
