h10728
s 00002/00002/00364
d D 8.4 93/12/10 19:39:26 mckusick 8 7
c new names for USL
e
s 00009/00009/00357
d D 8.3 93/09/23 16:45:09 bostic 7 6
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00364
d D 8.2 93/09/21 08:00:02 bostic 6 5
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00364
d D 8.1 93/06/11 15:17:30 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00007/00356
d D 7.4 93/04/20 23:44:13 torek 4 3
c update from elf
e
s 00011/00011/00352
d D 7.3 92/10/11 12:57:27 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00358
d D 7.2 92/07/21 16:54:41 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00358/00000/00000
d D 7.1 92/07/13 00:44:42 torek 1 0
c date and time created 92/07/13 00:44:42 by torek
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1982, 1986, 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */

D 3
#include "sys/param.h"
#include "sys/proc.h"
#include "sys/vnode.h"
#include "sys/buf.h"
#include "sys/malloc.h"
#include "sys/ptrace.h"
#include "sys/user.h"
E 3
I 3
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/buf.h>
#include <sys/malloc.h>
#include <sys/ptrace.h>
#include <sys/user.h>
E 3

D 3
#include "vm/vm.h"
#include "vm/vm_page.h"
E 3
I 3
#include <vm/vm.h>
#include <vm/vm_page.h>
E 3

D 3
#include "machine/psl.h"
#include "machine/reg.h"
E 3
I 3
#include <machine/psl.h>
#include <machine/reg.h>
E 3

/*
 * Priority for tracing
 */
#define	IPCPRI	PZERO

/*
 * Tracing variables.
 * Used to pass trace command from
 * parent to child being traced.
 * This data base cannot be
 * shared and is locked
 * per user.
 */
struct {
	int	ip_lock;
	int	ip_req;
	int	ip_error;
	union {
		char	un_any[4];
		struct {
			int	wd_data;
			caddr_t	wd_addr;
		} un_wd;
		struct	trapframe un_tf;
		struct	fpstate un_f;
	} ip_un;
} ipc;
#define	ip_any	ip_un.un_any
#define	ip_data	ip_un.un_wd.wd_data
#define	ip_addr	ip_un.un_wd.wd_addr
#define	ip_tf	ip_un.un_tf
#define	ip_f	ip_un.un_f

/*
 * Process debugging system call.
 */
struct ptrace_args {
	int	req;
	int	pid;
	caddr_t	addr;
	int	data;
};
ptrace(curp, uap, retval)
	struct proc *curp;
	register struct ptrace_args *uap;
	int *retval;
{
	register struct proc *p;
	register enum { t_oneword, t_regin, t_regout } type;
	register size_t size;
	register int error;

	if (uap->req == PT_TRACE_ME) {
D 7
		curp->p_flag |= STRC;
E 7
I 7
		curp->p_flag |= P_TRACED;
E 7
D 4
		curp->p_oppid = 0;	/* XXX put in the zeroed section */
E 4
		return (0);
	}
	if ((p = pfind(uap->pid)) == NULL)
		return (ESRCH);
	switch (uap->req) {

	case PT_READ_I:
	case PT_READ_D:
	case PT_WRITE_I:
	case PT_WRITE_D:
	case PT_CONTINUE:
	case PT_KILL:
	case PT_DETACH:
		type = t_oneword;
		size = 0;
		break;

	case PT_ATTACH:
		/*
D 4
		 * Must be root if the process has used set user or
		 * group privileges or does not belong to the real
		 * user. Must not be already traced.
E 4
I 4
		 * Must be root if the process has used set user or group
		 * privileges or does not belong to the real user.  Must
		 * not be already traced.  Can't attach to ourselves.
E 4
		 */
D 7
		if ((p->p_flag & SUGID ||
E 7
I 7
		if ((p->p_flag & P_SUGID ||
E 7
		    p->p_cred->p_ruid != curp->p_cred->p_ruid) &&
		    (error = suser(p->p_ucred, &p->p_acflag)) != 0)
			return (error);
D 7
		if (p->p_flag & STRC)
E 7
I 7
		if (p->p_flag & P_TRACED)
E 7
			return (EALREADY);	/* ??? */
I 4
		if (p == curp)
			return (EINVAL);
E 4
		/*
		 * It would be nice if the tracing relationship was separate
		 * from the parent relationship but that would require
		 * another set of links in the proc struct or for "wait"
		 * to scan the entire proc table.  To make life easier,
		 * we just re-parent the process we're trying to trace.
		 * The old parent is remembered so we can put things back
		 * on a "detach".
		 */
D 7
		p->p_flag |= STRC;
E 7
I 7
		p->p_flag |= P_TRACED;
E 7
		p->p_oppid = p->p_pptr->p_pid;
		proc_reparent(p, curp);
I 4
		if (p->p_stat == SSTOP)
D 6
			setrun(p);		/* long enough to stop */
E 6
I 6
			setrunnable(p);		/* long enough to stop */
E 6
E 4
		psignal(p, SIGSTOP);
		return (0);

	case PT_GETREGS:
		type = t_regout;
		size = sizeof(struct trapframe);
		break;

	case PT_SETREGS:
		type = t_regin;
		size = sizeof(struct trapframe);
		break;

	case PT_GETFPREGS:
		type = t_regout;
		size = sizeof(struct fpstate);
		break;

	case PT_SETFPREGS:
		type = t_regin;
		size = sizeof(struct fpstate);
		break;

	default:
		return (EINVAL);
	}
D 7
	if (p->p_stat != SSTOP || p->p_pptr != curp || !(p->p_flag & STRC))
E 7
I 7
	if (p->p_stat != SSTOP || p->p_pptr != curp || !(p->p_flag & P_TRACED))
E 7
		return (ESRCH);
	while (ipc.ip_lock)
		sleep((caddr_t)&ipc, IPCPRI);
	ipc.ip_lock = p->p_pid;
	ipc.ip_req = uap->req;
	ipc.ip_error = 0;
	switch (type) {

	case t_oneword:
		ipc.ip_addr = uap->addr;
		ipc.ip_data = uap->data;
		break;

	case t_regin:
		if ((error = copyin(uap->addr, ipc.ip_any, size)) != 0)
			return (error);
		break;

	case t_regout:
		break;

	default:
		panic("ptrace");
	}
D 7
	p->p_flag &= ~SWTED;
E 7
I 7
	p->p_flag &= ~P_WAITED;
E 7
	do {
		if (p->p_stat == SSTOP)
D 6
			setrun(p);
E 6
I 6
			setrunnable(p);
E 6
		sleep((caddr_t)&ipc, IPCPRI);
	} while (ipc.ip_req > 0);
	if ((error = ipc.ip_error) == 0) {
		if (type == t_oneword)
			*retval = ipc.ip_data;
		else if (type == t_regout)
			error = copyout(ipc.ip_any, uap->addr, size);
	}
	ipc.ip_lock = 0;
	wakeup((caddr_t)&ipc);
	return (error);
}

/*
 * Write text space by unprotecting, writing, and reprotecting.
 */
static int
writetext(p, addr, data, len)
	struct proc *p;
	caddr_t addr, data;
	int len;
{
	vm_offset_t sa, ea;
	vm_map_t map;
	int error;

	map = &p->p_vmspace->vm_map;
	sa = trunc_page((vm_offset_t)addr);
D 4
	ea = round_page((vm_offset_t)addr + len - 1);
E 4
I 4
	ea = round_page((vm_offset_t)addr + len);
E 4
	if (vm_map_protect(map, sa, ea, VM_PROT_DEFAULT, 0) != KERN_SUCCESS)
		return (-1);
	error = copyout(data, addr, len);
	(void) vm_map_protect(map, sa, ea, VM_PROT_READ|VM_PROT_EXECUTE, 0);
	return (error);
}

/*
 * Transmit a tracing request from the parent to the child process
 * being debugged.  This code runs in the context of the child process
 * to fulfill the command requested by the parent.
 */
D 8
procxmt(p)
E 8
I 8
trace_req(p)
E 8
	register struct proc *p;
{
	register int req, error, sig, pc, psr;
	register caddr_t addr;
	register struct trapframe *tf, *utf;
	register struct fpstate *fs, *oldfs;
	extern struct fpstate initfpstate;

	if (ipc.ip_lock != p->p_pid)
		return (0);
	p->p_slptime = 0;
	req = ipc.ip_req;
	ipc.ip_req = 0;
	error = 0;
	switch (req) {

	case PT_READ_I:			/* read the child's text space */
	case PT_READ_D:			/* read the child's data space */
		write_user_windows();
		(void) rwindow_save(p);	/* ignore unwritable windows */
		error = copyin(ipc.ip_addr, ipc.ip_any, sizeof(int));
		break;

	case PT_WRITE_I:		/* write the child's text space */
	case PT_WRITE_D:		/* write the child's data space */
		addr = ipc.ip_addr;
		write_user_windows();
		(void) rwindow_save(p);
		error = copyout(ipc.ip_any, addr, sizeof(int));
		if (error && req == PT_WRITE_I)
			error = writetext(p, addr, ipc.ip_any, sizeof(int));
		break;

	case PT_CONTINUE:		/* continue the child */
		sig = ipc.ip_data;
		if ((unsigned)sig >= NSIG) {
			error = EINVAL;
			break;
		}
		pc = (int)ipc.ip_addr;
		if (pc & 3) {
			if (pc != 1) {
				error = EINVAL;
				break;
			}
		} else {
			tf = p->p_md.md_tf;
			tf->tf_pc = pc;
			tf->tf_npc = pc + 4;
		}
D 7
		p->p_xstat = sig;	/* see issig */
E 7
I 7
		p->p_xstat = sig;	/* see issignal */
E 7
		wakeup((caddr_t)&ipc);
		return (1);

	case PT_KILL:			/* kill the child process */
		wakeup((caddr_t)&ipc);
D 4
		exit(p, (int)p->p_xstat);
E 4
I 4
		exit1(p, (int)p->p_xstat);
E 4

	case PT_DETACH:			/* stop tracing the child */
		sig = ipc.ip_data;
		if ((unsigned)sig >= NSIG) {
			error = EINVAL;
			break;
		}
		pc = (int)ipc.ip_addr;
		if (pc & 3) {
			if (pc != 1) {
				error = EINVAL;
				break;
			}
		} else {
			tf = p->p_md.md_tf;
			tf->tf_pc = pc;
			tf->tf_npc = pc + 4;
		}
D 7
		p->p_xstat = sig;	/* see issig */
		p->p_flag &= ~STRC;
E 7
I 7
		p->p_xstat = sig;	/* see issignal */
		p->p_flag &= ~P_TRACED;
E 7
		if (p->p_oppid != p->p_pptr->p_pid) {
                        register struct proc *pp = pfind(p->p_oppid);

                        if (pp)
                                proc_reparent(p, pp);
		}
		p->p_oppid = 0;
		wakeup((caddr_t)&ipc);
		return (1);

	case PT_GETREGS:
		copywords((caddr_t)p->p_md.md_tf, (caddr_t)&ipc.ip_tf,
			  sizeof(struct trapframe));
		ipc.ip_tf.tf_global[0] = 0; /* XXX */
		break;

	case PT_SETREGS:
		tf = p->p_md.md_tf;
		utf = &ipc.ip_tf;
		if ((utf->tf_pc | utf->tf_npc) & 3) {
			error = EINVAL;
			break;
		}
		psr = (tf->tf_psr & ~PSR_ICC) | (utf->tf_psr & PSR_ICC);
		copywords((caddr_t)utf, (caddr_t)tf, sizeof(*tf));
		tf->tf_psr = psr;
		break;

	case PT_GETFPREGS:
		if ((fs = p->p_md.md_fpstate) == NULL)
			fs = &initfpstate;
		else if (p == fpproc)
			savefpstate(fs);
		copywords((caddr_t)fs, (caddr_t)&ipc.ip_f, sizeof *fs);
		break;

	case PT_SETFPREGS:
		fs = &ipc.ip_f;
		if ((fs->fs_fsr & FSR_MBZ) != 0 || fs->fs_qsize) {
			error = EINVAL;
			break;
		}
		oldfs = p->p_md.md_fpstate;
		if (oldfs == NULL)
			p->p_md.md_fpstate = oldfs = malloc(sizeof *oldfs,
			    M_SUBPROC, M_WAITOK);
		else if (p == fpproc) {
			savefpstate(oldfs);
			fpproc = NULL;
			p->p_md.md_tf->tf_psr &= ~PSR_EF;
		}
		copywords((caddr_t)fs, (caddr_t)oldfs, sizeof *oldfs);
		break;

	default:
D 8
		panic("procxmt");
E 8
I 8
		panic("trace_req");
E 8
	}
	ipc.ip_error = error;
	wakeup((caddr_t)&ipc);
	return (0);
}
E 1
