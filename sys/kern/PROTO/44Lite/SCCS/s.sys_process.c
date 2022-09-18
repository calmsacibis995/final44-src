h50195
s 00024/00050/00024
d D 8.1 94/01/21 18:46:11 mckusick 3 2
c update for 4.4BSD-Lite
e
s 00000/00005/00074
d D 1.2 91/06/28 15:47:09 karels 2 1
c not so verbose about the "trade secrets"
e
s 00079/00000/00000
d D 1.1 91/05/11 15:31:10 mckusick 1 0
c date and time created 91/05/11 15:31:10 by mckusick
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
 *	from: @(#)sys_process.c	7.22 (Berkeley) 5/11/91
E 3
I 3
 *	from: @(#)sys_process.c	8.1 (Berkeley) 6/10/93
E 3
 */

D 3
#define IPCREG
#include "param.h"
#include "proc.h"
#include "vnode.h"
#include "seg.h"
#include "buf.h"
#include "ptrace.h"
E 3
I 3
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/errno.h>
E 3

D 3
#include "machine/reg.h"
#include "machine/psl.h"
#include "vm/vm.h"
#include "vm/vm_page.h"

#include "user.h"

E 3
/*
 * Process debugging system call.
 */
D 3
ptrace(curp, uap, retval)
	struct proc *curp;
	register struct args {
		int	req;
		int	pid;
		int	*addr;
		int	data;
	} *uap;
	int *retval;
E 3
I 3
struct ptrace_args {
	int	req;
	pid_t	pid;
	caddr_t	addr;
	int	data;
};
ptrace(a1, a2, a3)
	struct proc *a1;
	struct ptrace_args *a2;
	int *a3;
E 3
{

	/*
	 * Body deleted.
	 */
	return (ENOSYS);
}

D 2
/*
 * Transmit a tracing request from the parent to the child process
 * being debugged. This code runs in the context of the child process
 * to fulfill the command requested by the parent.
 */
E 2
D 3
procxmt(p)
	register struct proc *p;
E 3
I 3
trace_req(a1)
	struct proc *a1;
E 3
{

	/*
	 * Body deleted.
	 */
	return (0);
D 3
}

/*
 * Enable process profiling system call.
 */
/* ARGSUSED */
profil(p, uap, retval)
	struct proc *p;
	register struct args {
		short	*bufbase;
		unsigned bufsize;
		unsigned pcoffset;
		unsigned pcscale;
	} *uap;
	int *retval;
{

	/*
	 * Body deleted.
	 */
	return (ENOSYS);
E 3
}
E 1
