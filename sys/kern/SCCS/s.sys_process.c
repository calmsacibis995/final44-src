h01289
s 00017/00014/00287
d D 8.6 95/02/14 10:40:28 cgd 64 63
c new syscall arg conventions.
e
s 00005/00000/00296
d D 8.5 94/01/21 17:17:56 bostic 63 62
c add USL's copyright notice
e
s 00007/00000/00289
d D 8.4 94/01/05 10:04:33 mckusick 62 61
c add mips cruft to sys_process.c
e
s 00010/00010/00279
d D 8.3 93/09/23 15:37:17 bostic 61 60
c changes for 4.4BSD-Lite requested by USL
e
s 00001/00001/00288
d D 8.2 93/09/21 07:36:20 bostic 60 59
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00287
d D 8.1 93/06/10 21:58:46 bostic 59 58
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00002/00282
d D 7.39 93/06/09 17:20:26 mckusick 58 56
c alignment nits for word aligned architectures
e
s 00003/00002/00282
d R 7.39 93/06/06 11:56:10 mckusick 57 56
c alignment nits for word aligned architectures
e
s 00003/00003/00281
d D 7.38 93/06/04 16:19:52 mckusick 56 55
c sync up definition of ptrace_args with reality
e
s 00001/00001/00283
d D 7.37 93/05/11 21:04:22 akito 55 54
c add luna68k define
e
s 00001/00001/00283
d D 7.36 93/02/04 19:21:41 ralph 54 53
c changed the name of exit() to exit1() because gcc2 thinks it
c knows that exit() doesn't return.
e
s 00018/00017/00266
d D 7.35 92/12/27 08:59:19 hibler 53 52
c move HPUXCOMPAT code to MD files and account for new stack alignment
e
s 00005/00003/00278
d D 7.34 92/10/24 13:48:16 bostic 52 51
c don't allow process to attach to itself
e
s 00010/00010/00271
d D 7.33 92/10/11 10:38:29 bostic 51 50
c make kernel includes standard
e
s 00007/00006/00274
d D 7.32 92/09/21 21:14:18 hibler 50 49
c check for "trace me" right off the bat
c check return value of pfind before trying attach
e
s 00001/00001/00279
d D 7.31 92/07/15 14:47:15 mckusick 49 48
c vm_map_protect wants range to byte past end of affected range
e
s 00007/00006/00273
d D 7.30 92/07/10 21:06:54 torek 48 47
c ANSIfy syscall args
e
s 00000/00034/00279
d D 7.29 92/07/08 00:51:20 torek 47 46
c profil moves to subr_prof.c
e
s 00013/00004/00300
d D 7.28 92/06/24 00:22:19 torek 46 44
c fix up profile clock start/stop; watch out for tick during changes
e
s 00007/00002/00302
d R 7.28 92/06/24 00:12:36 torek 45 44
c fix start/stop profclock calls
e
s 00048/00003/00256
d D 7.27 92/06/23 19:56:55 mckusick 44 43
c add ptrace ATTACH/DETACH
e
s 00002/00003/00257
d D 7.26 92/06/20 11:56:17 mckusick 43 42
c notify clock routines when a process requests profiling
e
s 00001/00001/00259
d D 7.25 92/06/04 14:50:56 mckusick 42 41
c add support for luna68k from Omron
e
s 00005/00005/00255
d D 7.24 92/02/05 16:42:35 mckusick 41 40
c p_regs moves to p_md.md_regs
e
s 00007/00001/00253
d D 7.23 92/01/13 14:25:04 marc 40 38
c mips changes
e
s 00000/00000/00254
d R 7.23 91/11/19 23:49:06 torek 39 38
c purge seg.h
e
s 00007/00004/00247
d D 7.22 91/05/11 15:14:37 mckusick 38 37
c clarify comments
e
s 00005/00004/00246
d D 7.21 91/05/09 21:18:21 bostic 37 36
c new copyright; att/bsd/shared
e
s 00023/00000/00227
d D 7.20 91/05/09 18:34:04 mckusick 36 35
c profil moves from kern_clock.c to sys_process.c
e
s 00007/00006/00220
d D 7.19 91/05/06 17:54:22 karels 35 34
c shouldn't have used p_addr to get current process regs
c (p_regs is relative to kernel stack; this is machine-dependent!)
e
s 00007/00007/00219
d D 7.18 91/05/04 16:31:05 karels 34 33
c u. is gone, pcb is at p_addr
e
s 00004/00002/00222
d D 7.17 91/04/20 16:09:34 karels 33 32
c fake out ptrace
e
s 00011/00010/00213
d D 7.16 91/03/17 15:42:06 karels 32 31
c more-or-less working with new proc & user structs
e
s 00013/00000/00210
d D 7.15 91/01/08 18:36:27 william 31 30
c added 386 trap frame redefinition, only used in procxmit()
e
s 00013/00030/00197
d D 7.14 90/12/05 17:10:25 mckusick 30 29
c update for new VM
e
s 00004/00005/00223
d D 7.13 90/08/24 09:34:48 mckusick 29 28
c lint, minor cleanup
e
s 00005/00005/00223
d D 7.12 90/06/28 17:11:18 karels 28 27
c RETURN => return, remove syscontext.h
e
s 00002/00002/00226
d D 7.11 90/06/25 10:54:28 karels 27 26
c expunge p_cursig, using p_xstat instead for stop signals;
c expunge u_code
e
s 00016/00016/00212
d D 7.10 90/06/21 18:00:53 mckusick 26 25
c new system call convention
e
s 00002/00002/00226
d D 7.9 90/06/21 17:44:48 mckusick 25 24
c chgprot returns error code
e
s 00017/00017/00211
d D 7.8 90/06/06 00:06:48 mckusick 24 23
c expunge more u.u_procp
e
s 00019/00002/00209
d D 7.7 90/05/15 15:54:07 mckusick 23 22
c "update for hp300 support from Utah"
e
s 00007/00007/00204
d D 7.6 89/05/09 17:02:39 mckusick 22 21
c merge in vnodes
e
s 00004/00004/00207
d D 7.5 89/04/25 14:42:35 mckusick 21 20
c ../machine => machine
e
s 00004/00000/00207
d D 7.4 87/12/10 18:41:49 karels 20 19
c watch out for bogus combinations of vax options with compat mode
e
s 00001/00011/00206
d D 7.3 87/01/13 10:57:26 karels 19 18
c mv machine dependent
e
s 00015/00001/00202
d D 7.2 86/11/03 12:00:18 karels 18 17
c merge in tahoe support
e
s 00001/00001/00202
d D 7.1 86/06/05 00:08:17 mckusick 17 16
c 4.3BSD release version
e
s 00012/00021/00191
d D 6.6 86/02/20 15:58:46 karels 16 15
c cleanups from Sam: format, spl's, ptrace defs
e
s 00001/00001/00211
d D 6.5 85/11/26 12:37:33 karels 15 14
c now can use XTRC again instead of IXMOD
e
s 00007/00001/00205
d D 6.4 85/06/08 14:44:13 mckusick 14 13
c Add copyright
e
s 00001/00001/00205
d D 6.3 84/11/20 11:24:04 karels 13 12
c (ugly) changes to avoid executing/writing traced text segments
c (need regions done right!)
e
s 00011/00011/00195
d D 6.2 84/08/29 20:22:16 bloom 12 11
c Change to includes.  no more ../h
e
s 00000/00000/00206
d D 6.1 83/07/29 06:37:37 sam 11 10
c 4.2 distribution
e
s 00000/00018/00206
d D 5.10 83/07/01 02:19:30 sam 10 9
c purge #if sun's
e
s 00002/00001/00222
d D 5.9 83/05/18 02:02:38 sam 9 8
c from sun
e
s 00015/00004/00208
d D 5.8 82/12/17 11:46:21 sam 8 7
c sun merge
e
s 00004/00004/00208
d D 5.7 82/10/31 14:14:42 root 7 6
c change #if to #ifdef
e
s 00001/00001/00211
d D 5.6 82/10/31 00:51:14 root 6 5
c typo
e
s 00028/00010/00184
d D 5.5 82/10/31 00:48:04 root 5 4
c fixes in merging with 68k
e
s 00000/00001/00194
d D 5.4 82/10/10 15:56:05 root 4 3
c header files to vax directories
e
s 00000/00002/00195
d D 5.3 82/09/04 09:18:12 root 3 2
c don't need vlimit.h
e
s 00178/00000/00019
d D 5.2 82/07/24 18:11:01 root 2 1
c merge with calder
e
s 00019/00000/00000
d D 5.1 82/07/15 20:22:23 root 1 0
c date and time created 82/07/15 20:22:23 by root
e
u
U
f i 
t
T
I 1
D 14
/*	%M%	%I%	%E%	*/
E 14
I 14
D 37
/*
D 17
 * Copyright (c) 1982 Regents of the University of California.
E 17
I 17
D 22
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 22
I 22
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 22
E 17
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 37
I 37
/*-
D 59
 * Copyright (c) 1982, 1986, 1989 The Regents of the University of California.
 * All rights reserved.
E 59
I 59
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 63
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 63
E 59
 *
 * %sccs.include.proprietary.c%
E 37
 *
 *	%W% (Berkeley) %G%
 */
E 14

I 19
#define IPCREG
E 19
I 8
D 21
#include "../machine/reg.h"
#include "../machine/psl.h"
#include "../machine/pte.h"

E 21
E 8
D 12
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/proc.h"
#include "../h/inode.h"
D 8
#include "../h/reg.h"
E 8
#include "../h/text.h"
#include "../h/seg.h"
D 4
#include "../h/mtpr.h"
E 4
D 8
#include "../h/pte.h"
#include "../h/psl.h"
E 8
#include "../h/vm.h"
#include "../h/buf.h"
D 3
#include "../h/vlimit.h"
E 3
#include "../h/acct.h"
E 12
I 12
D 51
#include "param.h"
D 22
#include "systm.h"
#include "dir.h"
E 22
D 26
#include "user.h"
E 26
I 26
D 28
#include "syscontext.h"
E 28
I 28
D 33
#include "user.h"
E 33
E 28
E 26
#include "proc.h"
D 22
#include "inode.h"
E 22
I 22
#include "vnode.h"
E 22
D 30
#include "text.h"
E 30
D 40
#include "seg.h"
E 40
D 22
#include "vm.h"
E 22
#include "buf.h"
D 22
#include "acct.h"
E 22
I 16
#include "ptrace.h"
E 51
I 51
#include <sys/param.h>
I 64
#include <sys/systm.h>
E 64
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/buf.h>
#include <sys/ptrace.h>
E 51
I 21

I 64
#include <sys/mount.h>
#include <sys/syscallargs.h>

E 64
D 51
#include "machine/reg.h"
#include "machine/psl.h"
I 33
#include "vm/vm.h"
E 33
D 30
#include "machine/pte.h"
E 30
I 30
D 32
#include "../vm/vm_page.h"
#include "../vm/vm_prot.h"
E 32
I 32
#include "vm/vm_page.h"
E 51
I 51
#include <machine/reg.h>
#include <machine/psl.h>
#include <vm/vm.h>
#include <vm/vm_page.h>
E 51
D 33
#include "vm/vm_prot.h"
E 33
E 32
E 30
E 21
E 16
E 12
D 3

E 3
I 2

I 33
D 51
#include "user.h"
E 51
I 51
#include <sys/user.h>
E 51

E 33
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
D 56
	int	*ip_addr;
E 56
I 56
	caddr_t	ip_addr;
E 56
	int	ip_data;
} ipc;

/*
D 38
 * sys-trace system call.
E 38
I 38
 * Process debugging system call.
E 38
 */
I 48
D 64
struct ptrace_args {
	int	req;
D 56
	int	pid;
	int	*addr;
E 56
I 56
	pid_t	pid;
	caddr_t	addr;
E 56
	int	data;
};
E 64
E 48
D 26
ptrace()
{
	register struct proc *p;
	register struct a {
E 26
I 26
ptrace(curp, uap, retval)
	struct proc *curp;
D 48
	register struct args {
E 26
		int	req;
		int	pid;
		int	*addr;
		int	data;
	} *uap;
E 48
I 48
D 64
	register struct ptrace_args *uap;
E 48
I 26
	int *retval;
E 64
I 64
	struct ptrace_args /* {
		syscallarg(int) req;
		syscallarg(pid_t) pid;
		syscallarg(caddr_t) addr;
		syscallarg(int) data;
	} */ *uap;
	register_t *retval;
E 64
{
	register struct proc *p;
I 44
	int error;
E 44
E 26

I 50
D 64
	if (uap->req <= 0) {
E 64
I 64
	if (SCARG(uap, req) <= 0) {
E 64
D 61
		curp->p_flag |= STRC;
E 61
I 61
		curp->p_flag |= P_TRACED;
E 61
		return (0);
	}
E 50
I 44
D 64
	p = pfind(uap->pid);
E 64
I 64
	p = pfind(SCARG(uap, pid));
E 64
I 50
	if (p == 0)
		return (ESRCH);
E 50
D 64
	if (uap->req == PT_ATTACH) {
E 64
I 64
	if (SCARG(uap, req) == PT_ATTACH) {
E 64
		/*
D 52
		 * Must be root if the process has used set user or
		 * group privileges or does not belong to the real
		 * user. Must not be already traced.
E 52
I 52
		 * Must be root if the process has used set user or group
		 * privileges or does not belong to the real user.  Must
		 * not be already traced.  Can't attach to ourselves.
E 52
		 */
D 61
		if ((p->p_flag & SUGID ||
E 61
I 61
		if ((p->p_flag & P_SUGID ||
E 61
		    p->p_cred->p_ruid != curp->p_cred->p_ruid) &&
		    (error = suser(p->p_ucred, &p->p_acflag)) != 0)
			return (error);
D 61
		if (p->p_flag & STRC)
E 61
I 61
		if (p->p_flag & P_TRACED)
E 61
			return (EALREADY);	/* ??? */
I 52
		if (p->p_pid == curp->p_pid)
			return (EINVAL);
E 52
		/*
		 * It would be nice if the tracing relationship was separate
		 * from the parent relationship but that would require
		 * another set of links in the proc struct or for "wait"
		 * to scan the entire proc table.  To make life easier,
		 * we just re-parent the process we're trying to trace.
		 * The old parent is remembered so we can put things back
		 * on a "detach".
		 */
D 61
		p->p_flag |= STRC;
E 61
I 61
		p->p_flag |= P_TRACED;
E 61
		p->p_oppid = p->p_pptr->p_pid;
		proc_reparent(p, curp);
		psignal(p, SIGSTOP);
		return (0);
	}
E 44
D 26
	uap = (struct a *)u.u_ap;
E 26
D 50
	if (uap->req <= 0) {
D 26
		u.u_procp->p_flag |= STRC;
		return;
E 26
I 26
		curp->p_flag |= STRC;
D 28
		RETURN (0);
E 28
I 28
		return (0);
E 28
E 26
	}
D 44
	p = pfind(uap->pid);
E 44
D 9
	if (p == 0 || p->p_stat != SSTOP || p->p_ppid != u.u_procp->p_pid) {
E 9
I 9
D 26
	if (p == 0 || p->p_stat != SSTOP || p->p_ppid != u.u_procp->p_pid ||
	    !(p->p_flag & STRC)) {
E 9
		u.u_error = ESRCH;
		return;
	}
E 26
I 26
D 32
	if (p == 0 || p->p_stat != SSTOP || p->p_ppid != curp->p_pid ||
E 32
I 32
	if (p == 0 || p->p_stat != SSTOP || p->p_pptr != curp ||
E 32
	    !(p->p_flag & STRC))
E 50
I 50
D 61
	if (p->p_stat != SSTOP || p->p_pptr != curp || !(p->p_flag & STRC))
E 61
I 61
	if (p->p_stat != SSTOP || p->p_pptr != curp || !(p->p_flag & P_TRACED))
E 61
E 50
D 28
		RETURN (ESRCH);
E 28
I 28
		return (ESRCH);
E 28
E 26
	while (ipc.ip_lock)
		sleep((caddr_t)&ipc, IPCPRI);
	ipc.ip_lock = p->p_pid;
D 64
	ipc.ip_data = uap->data;
	ipc.ip_addr = uap->addr;
	ipc.ip_req = uap->req;
E 64
I 64
	ipc.ip_data = SCARG(uap, data);
	ipc.ip_addr = SCARG(uap, addr);
	ipc.ip_req = SCARG(uap, req);
E 64
D 61
	p->p_flag &= ~SWTED;
E 61
I 61
	p->p_flag &= ~P_WAITED;
E 61
	while (ipc.ip_req > 0) {
		if (p->p_stat==SSTOP)
D 60
			setrun(p);
E 60
I 60
			setrunnable(p);
E 60
		sleep((caddr_t)&ipc, IPCPRI);
	}
D 26
	u.u_r.r_val1 = ipc.ip_data;
	if (ipc.ip_req < 0)
		u.u_error = EIO;
E 26
I 26
	*retval = ipc.ip_data;
E 26
	ipc.ip_lock = 0;
	wakeup((caddr_t)&ipc);
I 26
	if (ipc.ip_req < 0)
D 28
		RETURN (EIO);
	RETURN (0);
E 28
I 28
		return (EIO);
	return (0);
E 28
E 26
}
D 19

D 5
int ipcreg[] = {R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,AP,FP,SP,PC};
E 5
I 5
D 7
#if vax
E 7
I 7
D 16
#ifdef vax
E 16
I 16
#if defined(vax)
E 16
E 7
#define	NIPCREG 16
D 10
#endif
D 7
#if sun
E 7
I 7
#ifdef sun
E 7
#define	NIPCREG 17
#endif
E 10
int ipcreg[NIPCREG] =
D 7
#if vax
E 7
I 7
D 10
#ifdef vax
E 10
E 7
	{R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,AP,FP,SP,PC};
#endif
I 18
#if defined(tahoe)
#define	NIPCREG 18
int ipcreg[NIPCREG] =
	{R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,R12,FP,SP,PC,RACH,RACL};
#endif
E 19
E 18
D 7
#if sun
E 7
I 7
D 10
#ifdef sun
E 7
	{R0,R1,R2,R3,R4,R5,R6,R7,AR0,AR1,AR2,AR3,AR4,AR5,AR6,AR7,PC};
#endif
E 10

D 6
#define	PHYSOFF(p, o)
E 6
I 6
D 35
#define	PHYSOFF(p, o) \
E 6
	((physadr)(p)+((o)/sizeof(((physadr)0)->r[0])))
E 35
I 35
#define	PHYSOFF(p, o) ((caddr_t)(p) + (o))
I 58
#if defined(hp300) || defined(luna68k)
#define PHYSALIGNED(a) (((int)(a) & (sizeof(short) - 1)) == 0)
#else
#define PHYSALIGNED(a) (((int)(a) & (sizeof(int) - 1)) == 0)
#endif
E 58

E 35
I 31
#if defined(i386)
#undef        PC
#undef        SP
#undef        PS
#undef        R0
#undef        R1

#define       PC      tEIP
#define       SP      tESP
#define       PS      tEFLAGS
#define       R0      tEDX
#define       R1      tECX
#endif
E 31

E 5
/*
D 38
 * Code that the child process
 * executes to implement the command
 * of the parent process in tracing.
E 38
I 38
 * Transmit a tracing request from the parent to the child process
 * being debugged. This code runs in the context of the child process
 * to fulfill the command requested by the parent.
E 38
 */
D 24
procxmt()
E 24
I 24
D 61
procxmt(p)
E 61
I 61
trace_req(p)
E 61
	register struct proc *p;
E 24
{
D 24
	register int i;
	register *p;
E 24
I 24
D 53
	register int i, *poff;
E 53
I 53
	register int i, *poff, *regs;
E 53
I 35
	extern char kstack[];
E 35
E 24
D 30
	register struct text *xp;
I 22
	struct vattr vattr;
E 30
D 29
	struct vnode *vp;
E 29
E 22

D 24
	if (ipc.ip_lock != u.u_procp->p_pid)
E 24
I 24
	if (ipc.ip_lock != p->p_pid)
E 24
		return (0);
D 24
	u.u_procp->p_slptime = 0;
E 24
I 24
	p->p_slptime = 0;
I 33
D 34
	u.u_kproc.kp_proc.p_regs = p->p_regs;	/* u.u_ar0 */
E 34
I 34
D 41
	p->p_addr->u_kproc.kp_proc.p_regs = p->p_regs;	/* u.u_ar0 */
E 41
I 41
D 53
	p->p_addr->u_kproc.kp_proc.p_md.md_regs = p->p_md.md_regs; /* u.u_ar0 */
E 53
I 53
	regs = p->p_md.md_regs;
	p->p_addr->u_kproc.kp_proc.p_md.md_regs = regs; /* u.u_ar0 */
E 53
E 41
E 34
E 33
E 24
	i = ipc.ip_req;
	ipc.ip_req = 0;
	switch (i) {

D 16
	/* read user I */
	case 1:
E 16
I 16
	case PT_READ_I:			/* read the child's text space */
E 16
		if (!useracc((caddr_t)ipc.ip_addr, 4, B_READ))
			goto error;
		ipc.ip_data = fuiword((caddr_t)ipc.ip_addr);
		break;

D 16
	/* read user D */
	case 2:
E 16
I 16
	case PT_READ_D:			/* read the child's data space */
E 16
		if (!useracc((caddr_t)ipc.ip_addr, 4, B_READ))
			goto error;
		ipc.ip_data = fuword((caddr_t)ipc.ip_addr);
		break;

D 16
	/* read u */
	case 3:
E 16
I 16
	case PT_READ_U:			/* read the child's u. */
I 23
D 53
#ifdef HPUXCOMPAT
D 34
		if (u.u_pcb.pcb_flags & PCB_HPUXTRACE)
E 34
I 34
		if (p->p_addr->u_pcb.pcb_flags & PCB_HPUXTRACE)
E 34
			i = hpuxtobsduoff(ipc.ip_addr);
		else
#endif
E 53
E 23
E 16
		i = (int)ipc.ip_addr;
D 23
		if (i<0 || i >= ctob(UPAGES))
E 23
I 23
D 35
		if (i<0 || i > ctob(UPAGES)-sizeof(int))
E 35
I 35
D 58
		if ((u_int) i > ctob(UPAGES)-sizeof(int) || (i & 1) != 0)
E 58
I 58
		if ((u_int) i > ctob(UPAGES)-sizeof(int) || !PHYSALIGNED(i))
E 58
E 35
E 23
			goto error;
D 5
		ipc.ip_data = ((physadr)&u)->r[i>>2];
E 5
I 5
D 34
		ipc.ip_data = *(int *)PHYSOFF(&u, i);
E 34
I 34
		ipc.ip_data = *(int *)PHYSOFF(p->p_addr, i);
E 34
E 5
		break;

D 16
	/* write user I */
	/* Must set up to allow writing */
	case 4:
E 16
I 16
	case PT_WRITE_I:		/* write the child's text space */
E 16
D 30
		/*
		 * If text, must assure exclusive use
		 */
D 24
		if (xp = u.u_procp->p_textp) {
E 24
I 24
		if (xp = p->p_textp) {
E 24
D 22
			if (xp->x_count!=1 || xp->x_iptr->i_mode&ISVTX)
E 22
I 22
D 29
			vp = xp->x_vptr;
			VOP_GETATTR(vp, &vattr, u.u_cred);
			if (xp->x_count!=1 || (vattr.va_mode & VSVTX))
E 29
I 29
			if (xp->x_count != 1 ||
			    VOP_GETATTR(xp->x_vptr, &vattr, u.u_cred) ||
			    (vattr.va_mode & VSVTX))
E 29
E 22
				goto error;
D 13
			xp->x_iptr->i_flag &= ~ITEXT;
E 13
I 13
D 15
			xp->x_iptr->i_flag |= IXMOD;	/* XXX */
E 15
I 15
			xp->x_flag |= XTRC;
E 15
E 13
		}
		i = -1;
E 30
D 5
		if (chgprot((caddr_t)ipc.ip_addr, RW) &&
		    chgprot((caddr_t)ipc.ip_addr+(sizeof(int)-1), RW))
			i = suiword((caddr_t)ipc.ip_addr, ipc.ip_data);
		(void) chgprot((caddr_t)ipc.ip_addr, RO);
		(void) chgprot((caddr_t)ipc.ip_addr+(sizeof(int)-1), RO);
E 5
I 5
		if ((i = suiword((caddr_t)ipc.ip_addr, ipc.ip_data)) < 0) {
D 25
			if (chgprot((caddr_t)ipc.ip_addr, RW) &&
			    chgprot((caddr_t)ipc.ip_addr+(sizeof(int)-1), RW))
E 25
I 25
D 30
			if (!chgprot((caddr_t)ipc.ip_addr, RW) &&
			    !chgprot((caddr_t)ipc.ip_addr+(sizeof(int)-1), RW))
E 30
I 30
			vm_offset_t sa, ea;
			int rv;

			sa = trunc_page((vm_offset_t)ipc.ip_addr);
D 49
			ea = round_page((vm_offset_t)ipc.ip_addr+sizeof(int)-1);
E 49
I 49
			ea = round_page((vm_offset_t)ipc.ip_addr+sizeof(int));
E 49
D 32
			rv = vm_map_protect(p->p_map, sa, ea,
E 32
I 32
			rv = vm_map_protect(&p->p_vmspace->vm_map, sa, ea,
E 32
					VM_PROT_DEFAULT, FALSE);
			if (rv == KERN_SUCCESS) {
E 30
E 25
				i = suiword((caddr_t)ipc.ip_addr, ipc.ip_data);
D 30
			(void) chgprot((caddr_t)ipc.ip_addr, RO);
			(void) chgprot((caddr_t)ipc.ip_addr+(sizeof(int)-1), RO);
E 30
I 30
D 32
				(void) vm_map_protect(p->p_map, sa, ea,
					VM_PROT_READ|VM_PROT_EXECUTE, FALSE);
E 32
I 32
				(void) vm_map_protect(&p->p_vmspace->vm_map,
					sa, ea, VM_PROT_READ|VM_PROT_EXECUTE,
					FALSE);
E 32
			}
E 30
		}
E 5
		if (i < 0)
			goto error;
D 18
		if (xp)
E 18
I 18
D 30
#if defined(tahoe)
		/* make sure the old value is not in cache */
D 24
		ckeyrelease(u.u_procp->p_ckey);
		u.u_procp->p_ckey = getcodekey();
E 24
I 24
		ckeyrelease(p->p_ckey);
		p->p_ckey = getcodekey();
E 24
#endif
		if (xp) {
E 18
			xp->x_flag |= XWRIT;
I 18
#if defined(tahoe)
D 24
			xp->x_ckey = u.u_procp->p_ckey;
E 24
I 24
			xp->x_ckey = p->p_ckey;
E 24
#endif
		}
E 30
E 18
		break;

D 16
	/* write user D */
	case 5:
E 16
I 16
	case PT_WRITE_D:		/* write the child's data space */
E 16
		if (suword((caddr_t)ipc.ip_addr, 0) < 0)
			goto error;
		(void) suword((caddr_t)ipc.ip_addr, ipc.ip_data);
		break;

D 16
	/* write u */
	case 6:
E 16
I 16
	case PT_WRITE_U:		/* write the child's u. */
I 23
D 53
#ifdef HPUXCOMPAT
D 34
		if (u.u_pcb.pcb_flags & PCB_HPUXTRACE)
E 34
I 34
		if (p->p_addr->u_pcb.pcb_flags & PCB_HPUXTRACE)
E 34
			i = hpuxtobsduoff(ipc.ip_addr);
		else
#endif
E 53
E 23
E 16
		i = (int)ipc.ip_addr;
I 40
#ifdef mips
D 58
		poff = (int *)PHYSOFF(curproc->p_addr, i);
E 58
I 58
		poff = (int *)PHYSOFF(p->p_addr, i);
E 58
#else
E 40
D 5
		p = (int *)&((physadr)&u)->r[i>>2];
		for (i=0; i<16; i++)
E 5
I 5
D 24
		p = (int *)PHYSOFF(&u, i);
E 24
I 24
D 34
		poff = (int *)PHYSOFF(&u, i);
E 34
I 34
D 35
		poff = (int *)PHYSOFF(p->p_addr, i);
E 35
I 35
		poff = (int *)PHYSOFF(kstack, i);
I 40
#endif
E 40
E 35
E 34
E 24
		for (i=0; i<NIPCREG; i++)
E 5
D 24
			if (p == &u.u_ar0[ipcreg[i]])
E 24
I 24
D 32
			if (poff == &u.u_ar0[ipcreg[i]])
E 32
I 32
D 41
			if (poff == &p->p_regs[ipcreg[i]])
E 41
I 41
D 53
			if (poff == &p->p_md.md_regs[ipcreg[i]])
E 53
I 53
			if (poff == &regs[ipcreg[i]])
E 53
E 41
E 32
E 24
				goto ok;
D 24
		if (p == &u.u_ar0[PS]) {
E 24
I 24
D 32
		if (poff == &u.u_ar0[PS]) {
E 32
I 32
D 41
		if (poff == &p->p_regs[PS]) {
E 41
I 41
D 53
		if (poff == &p->p_md.md_regs[PS]) {
E 53
I 53
D 55
#if defined(hp300)
E 55
I 55
#if defined(hp300) || defined(luna68k)
E 55
		/*
		 * In the new frame layout, PS/PC are skewed by 2 bytes.
		 */
		regs = (int *)((short *)regs + 1);
		if (poff == &regs[PC])
			goto ok;
#endif
		if (poff == &regs[PS]) {
E 53
E 41
E 32
E 24
D 5
			ipc.ip_data |= PSL_CURMOD|PSL_PRVMOD;
E 5
I 5
			ipc.ip_data |= PSL_USERSET;
E 5
D 23
			ipc.ip_data &=  ~PSL_USERCLR;
E 23
I 23
			ipc.ip_data &= ~PSL_USERCLR;
E 23
I 20
#ifdef PSL_CM_CLR
			if (ipc.ip_data & PSL_CM)
				ipc.ip_data &= ~PSL_CM_CLR;
#endif
E 20
I 8
D 10
#ifdef sun
			if (ipc.ip_data & PSL_T)
				traceon();
			else
				traceoff();
#endif
E 10
E 8
			goto ok;
		}
I 23
D 42
#if defined(hp300)
E 42
I 42
#if defined(hp300) || defined(luna68k)
E 42
#ifdef FPCOPROC
D 24
		if (p >= (int *)u.u_pcb.pcb_fpregs.fpf_regs &&
		    p <= (int *)&u.u_pcb.pcb_fpregs.fpf_fpiar)
E 24
I 24
D 34
		if (poff >= (int *)u.u_pcb.pcb_fpregs.fpf_regs &&
		    poff <= (int *)&u.u_pcb.pcb_fpregs.fpf_fpiar)
E 34
I 34
D 35
		if (poff >= (int *)p->p_addr->u_pcb.pcb_fpregs.fpf_regs &&
		    poff <= (int *)&p->p_addr->u_pcb.pcb_fpregs.fpf_fpiar)
E 35
I 35
		if (poff >= (int *)&((struct user *)kstack)->u_pcb.pcb_fpregs.fpf_regs &&
		    poff <= (int *)&((struct user *)kstack)->u_pcb.pcb_fpregs.fpf_fpiar)
E 35
E 34
E 24
			goto ok;
#endif
#endif
E 23
		goto error;

	ok:
D 24
		*p = ipc.ip_data;
E 24
I 24
		*poff = ipc.ip_data;
E 24
		break;

D 16
	/* set signal and continue */
	/* one version causes a trace-trap */
	case 9:
	case 7:
E 16
I 16
	case PT_STEP:			/* single step the child */
	case PT_CONTINUE:		/* continue the child */
I 62
#ifndef mips
E 62
I 53
		regs = (int *)((short *)regs + 1);
I 62
#endif
E 62
E 53
I 44
		if ((unsigned)ipc.ip_data >= NSIG)
			goto error;
E 44
E 16
		if ((int)ipc.ip_addr != 1)
D 32
			u.u_ar0[PC] = (int)ipc.ip_addr;
E 32
I 32
D 41
			p->p_regs[PC] = (int)ipc.ip_addr;
E 41
I 41
D 53
			p->p_md.md_regs[PC] = (int)ipc.ip_addr;
E 53
I 53
			regs[PC] = (int)ipc.ip_addr;
E 53
E 41
E 32
D 44
		if ((unsigned)ipc.ip_data > NSIG)
			goto error;
E 44
D 24
		u.u_procp->p_cursig = ipc.ip_data;	/* see issig */
E 24
I 24
D 27
		p->p_cursig = ipc.ip_data;	/* see issig */
E 27
I 27
D 61
		p->p_xstat = ipc.ip_data;	/* see issig */
E 61
I 61
		p->p_xstat = ipc.ip_data;	/* see issignal */
I 62
#ifdef mips
		if (i == PT_STEP && cpu_singlestep(p))
			goto error;
#else
E 62
E 61
I 40
#ifdef PSL_T
		/* need something more machine independent here... */
E 40
E 27
E 24
D 8
		if (i == 9)
E 8
I 8
D 16
		if (i == 9) 
E 16
I 16
		if (i == PT_STEP) 
E 16
D 10
#ifdef sun
			traceon();
#else
E 10
E 8
D 32
			u.u_ar0[PS] |= PSL_T;
E 32
I 32
D 41
			p->p_regs[PS] |= PSL_T;
E 41
I 41
D 53
			p->p_md.md_regs[PS] |= PSL_T;
E 53
I 53
			regs[PS] |= PSL_T;
I 62
#endif
E 62
E 53
E 41
I 40
#endif
E 40
E 32
I 8
D 10
#endif
E 10
E 8
		wakeup((caddr_t)&ipc);
		return (1);

D 16
	/* force exit */
	case 8:
E 16
I 16
	case PT_KILL:			/* kill the child process */
E 16
		wakeup((caddr_t)&ipc);
D 24
		exit(u.u_procp->p_cursig);
E 24
I 24
D 27
		exit(p, p->p_cursig);
E 27
I 27
D 29
		exit(p, p->p_xstat);
E 29
I 29
D 54
		exit(p, (int)p->p_xstat);
E 54
I 54
		exit1(p, (int)p->p_xstat);
E 54
I 44

	case PT_DETACH:			/* stop tracing the child */
I 53
		regs = (int *)((short *)regs + 1);
E 53
		if ((unsigned)ipc.ip_data >= NSIG)
			goto error;
		if ((int)ipc.ip_addr != 1)
D 53
			p->p_md.md_regs[PC] = (int)ipc.ip_addr;
E 53
I 53
			regs[PC] = (int)ipc.ip_addr;
E 53
D 61
		p->p_xstat = ipc.ip_data;	/* see issig */
		p->p_flag &= ~STRC;
E 61
I 61
		p->p_xstat = ipc.ip_data;	/* see issignal */
		p->p_flag &= ~P_TRACED;
E 61
		if (p->p_oppid != p->p_pptr->p_pid) {
                        register struct proc *pp = pfind(p->p_oppid);

                        if (pp)
                                proc_reparent(p, pp);
		}
		p->p_oppid = 0;
		wakeup((caddr_t)&ipc);
		return (1);
E 44
E 29
E 27
E 24

	default:
	error:
		ipc.ip_req = -1;
	}
	wakeup((caddr_t)&ipc);
	return (0);
}
I 36
D 47

I 38
/*
 * Process debugging system call.
 */
E 38
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
D 46
	register struct uprof *upp = &p->p_stats->p_prof;

E 46
I 46
	register struct uprof *upp;
	int s;
	
	upp = &p->p_stats->p_prof;
	s = splhigh();	/* block profile interrupts while changing state */
E 46
	upp->pr_base = uap->bufbase;
	upp->pr_size = uap->bufsize;
	upp->pr_off = uap->pcoffset;
	upp->pr_scale = uap->pcscale;
D 43
#ifdef PROFTIMER
	initprofclock();
#endif
E 43
I 43
D 46
	if (uap->pcscale)
		startprofclock(p);
E 46
I 46
	if (uap->pcscale) {
		if ((p->p_flag & SPROFIL) == 0)
			startprofclock(p);
	} else {
		if (p->p_flag & SPROFIL)
			stopprofclock(p);
	}
	splx(s);
E 46
E 43
	return (0);
}
E 47
E 36
E 2
E 1
