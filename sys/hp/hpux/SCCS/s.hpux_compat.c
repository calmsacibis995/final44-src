h45812
s 00025/00025/02200
d D 8.5 95/02/19 07:59:38 cgd 59 58
c use argsize for unimplemented function printfs.  new names for fcns.
e
s 00085/00015/02140
d D 8.4 94/02/13 10:47:19 hibler 58 57
c support for fcntl file locking
e
s 00005/00000/02150
d D 8.3 93/11/16 16:28:23 hibler 57 56
c add CLKTICK sysconf call
e
s 00111/00012/02039
d D 8.2 93/09/09 14:47:49 hibler 56 55
c bring up to HP-UX 9.x level
e
s 00002/00002/02049
d D 8.1 93/07/08 11:32:41 bostic 55 54
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00120/00084/01931
d D 7.37 93/07/08 10:53:11 hibler 54 52
c add support for O_NONBLOCK (in conjunction with FNDELAY and FIOSNBIO)
e
s 00002/00002/02013
d R 8.1 93/06/14 16:08:37 bostic 53 52
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/02014
d D 7.36 93/06/14 16:08:25 bostic 52 50
c make function names match system call names
e
s 00002/00002/02013
d R 8.1 93/06/10 21:24:31 bostic 51 50
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/02013
d D 7.35 93/05/17 15:30:43 mckusick 50 49
c old get/setrlimt are COMPAT_43
e
s 00003/00000/02012
d D 7.34 93/05/12 20:30:21 mckusick 49 48
c requires COMPAT_43 to build
e
s 00172/00043/01840
d D 7.33 92/12/27 09:06:15 hibler 48 47
c latest Utah version
e
s 00029/00028/01854
d D 7.32 92/10/11 09:01:41 bostic 47 46
c make kernel includes standard
e
s 00051/00016/01831
d D 7.31 92/08/03 14:16:03 hibler 46 45
c get things working again for a wider range of HP-UX binaries
e
s 00013/00011/01834
d D 7.30 92/07/15 21:12:17 mckusick 45 44
c need to pass down proc pointers
e
s 00000/00000/01845
d D 7.29 92/07/13 11:27:53 mckusick 44 43
x 40
c osetreuid and osetregid are back, so we can use them again
e
s 00002/00002/01908
d D 7.28 92/07/12 17:50:57 pendry 43 42
c MIN -> min
e
s 00226/00183/01684
d D 7.27 92/07/10 20:43:19 torek 42 40
c ANSIfy syscall args
e
s 00229/00184/01683
d R 7.27 92/07/10 18:48:44 torek 41 40
c ANSIfy syscall args
e
s 00070/00005/01797
d D 7.26 92/07/09 16:30:19 torek 40 39
c have to inline expand setreuid and setregid since they no longer 
c exist in kern_prot.c
e
s 00049/00021/01753
d D 7.25 92/07/09 15:55:35 hibler 39 38
c move HPUXCOMPAT code for shmctl to here from sysv_shm.c
e
s 00004/00002/01770
d D 7.24 92/07/07 19:07:08 torek 38 37
c new resource usage calculations
e
s 00000/00003/01772
d D 7.23 92/07/03 01:09:43 mckusick 37 36
c delete USES
e
s 00007/00007/01768
d D 7.22 92/06/19 19:30:11 mckusick 36 35
c timeval => timespec in vattr and dinode
e
s 00083/00009/01692
d D 7.21 92/06/05 15:22:10 hibler 35 34
c merge latest Utah hp300 code including 68040 support
e
s 00003/00000/01698
d D 7.20 92/05/14 17:25:43 heideman 34 19
c vnode interface conversion
e
s 00003/00000/01698
d R 7.20 92/05/14 16:59:46 heideman 33 19
c vnode interface conversion
e
s 00003/00000/01698
d R 7.20 92/05/14 16:42:13 heideman 32 19
c vnode interface conversion
e
s 00003/00000/01698
d R 7.20 92/05/14 16:32:06 heideman 31 19
c vnode interface conversion
e
s 00003/00000/01698
d R 7.20 92/05/14 15:49:47 heideman 30 19
c vnode interface conversion
e
s 00003/00000/01698
d R 7.20 92/05/14 15:38:13 heideman 29 19
c vnode interface conversion
e
s 00003/00000/01698
d R 7.20 92/05/14 14:44:22 heideman 28 19
c vnode interface conversion
e
s 00003/00000/01698
d R 7.20 92/05/14 12:47:05 heideman 27 19
c vnode interface conversion
e
s 00003/00000/01698
d R 7.20 92/05/14 11:44:08 heideman 26 19
c vnode interface conversion
e
s 00003/00000/01698
d R 7.20 92/05/14 10:24:59 heideman 25 19
c vnode interface conversion
e
s 00003/00000/01698
d R 7.20 92/05/13 23:02:50 heideman 24 19
c vnode interface conversion
e
s 00003/00000/01698
d R 7.20 92/05/13 18:50:58 heideman 23 19
c vnode interface conversion
e
s 00003/00000/01698
d R 7.20 92/05/13 18:22:43 heideman 22 19
c vnode interface conversion
e
s 00003/00000/01698
d R 7.20 92/05/13 18:12:13 heideman 21 19
c vnode interface conversion
e
s 00003/00000/01698
d R 7.20 92/05/13 17:56:50 heideman 20 19
c vnode interface conversion
e
s 00009/00006/01689
d D 7.19 92/05/13 15:16:13 mckusick 19 18
c make off_t and dev_t's explicitly their old sizes
e
s 00006/00006/01689
d D 7.18 92/02/05 17:22:09 mckusick 18 17
c p_regs moves to p_md.md_regs
e
s 00017/00030/01678
d D 7.17 92/02/04 14:27:55 mckusick 17 16
c new namei calling convention
e
s 00014/00017/01694
d D 7.16 91/05/30 15:55:06 mckusick 16 15
c make file flags more consistent; delete dead code
e
s 00061/00012/01650
d D 7.15 91/05/07 10:03:55 hibler 15 14
c update from utah
e
s 00029/00029/01633
d D 7.14 91/05/04 19:52:23 karels 14 13
c u. is gone, use p_addr (or kstack for regs); current include conventions
e
s 00105/00078/01557
d D 7.13 91/04/20 17:46:42 karels 13 12
c new proc struct, substructs; rm OFILE*; new namei, VOP conventions;
c fix includes; execv now for hpux only
e
s 00024/00017/01611
d D 7.12 91/01/11 00:00:45 mckusick 12 11
c add dynamically allocated file descriptors
e
s 00022/00022/01606
d D 7.11 90/12/16 16:36:15 bostic 11 10
c kernel reorg
e
s 00201/00046/01439
d D 7.10 90/12/05 19:04:35 mckusick 10 9
c update from Mike Hibler for new VM and other machine support
e
s 00072/00072/01413
d D 7.9 90/06/28 19:34:58 karels 9 8
c RETURN => return, remove syscontext.h
e
s 00007/00007/01478
d D 7.8 90/06/24 19:09:33 mckusick 8 7
c purge use of u_r.r_time and u_r.r_off
e
s 00465/00421/01020
d D 7.7 90/06/22 18:00:44 hibler 7 6
c eliminate use of u_error
e
s 00012/00011/01429
d D 7.6 90/06/08 18:21:26 karels 6 5
c convert copen to use open
e
s 00034/00004/01406
d D 7.5 90/05/25 15:36:11 mckusick 5 4
c "update from Mike Hibler at Utah"
e
s 00008/00007/01402
d D 7.4 90/05/16 23:10:23 karels 4 3
c attempt to convert wait, pause
e
s 00001/00001/01408
d D 7.3 90/05/16 20:23:20 mckusick 3 2
c mount structure elements now start mnt_ instead of m_
e
s 00001/00001/01408
d D 7.2 90/05/15 22:05:41 mckusick 2 1
c use proper include files
e
s 01409/00000/00000
d D 7.1 90/05/08 22:18:38 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 55
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 55
I 55
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 55
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 10
 * from: Utah $Hdr: hpux_compat.c 1.33 89/08/23$
E 10
I 10
D 15
 * from: Utah $Hdr: hpux_compat.c 1.3 90/09/17$
E 15
I 15
D 35
 * from: Utah $Hdr: hpux_compat.c 1.41 91/04/06$
E 35
I 35
D 39
 * from: Utah $Hdr: hpux_compat.c 1.42 92/01/20$
E 39
I 39
D 48
 * from: Utah $Hdr: hpux_compat.c 1.43 92/04/23$
E 48
I 48
D 54
 * from: Utah $Hdr: hpux_compat.c 1.55 92/12/26$
E 54
I 54
D 56
 * from: Utah $Hdr: hpux_compat.c 1.59 93/06/15$
E 56
I 56
 * from: Utah $Hdr: hpux_compat.c 1.64 93/08/05$
E 56
E 54
E 48
E 39
E 35
E 15
E 10
 *
 *	%W% (Berkeley) %G%
 */

/*
D 39
 * Various HPUX compatibility routines
E 39
I 39
 * Various HP-UX compatibility routines
E 39
 */

#ifdef HPUXCOMPAT
I 49
#ifndef COMPAT_43
#define COMPAT_43
#endif
E 49

D 11
#include "param.h"
#include "systm.h"
D 9
#include "syscontext.h"
E 9
I 9
#include "user.h"
E 9
#include "kernel.h"
#include "proc.h"
#include "buf.h"
#include "wait.h"
#include "file.h"
#include "vnode.h"
#include "ioctl.h"
#include "uio.h"
#include "ptrace.h"
#include "stat.h"
#include "syslog.h"
#include "malloc.h"
#include "mount.h"
#include "ipc.h"
E 11
I 11
D 14
#include "sys/param.h"
#include "sys/systm.h"
D 13
#include "sys/user.h"
E 13
I 13
#include "sys/signalvar.h"
E 13
#include "sys/kernel.h"
I 12
#include "sys/filedesc.h"
E 12
#include "sys/proc.h"
#include "sys/buf.h"
#include "sys/wait.h"
#include "sys/file.h"
I 13
#include "sys/namei.h"
E 13
#include "sys/vnode.h"
#include "sys/ioctl.h"
D 13
#include "sys/uio.h"
E 13
#include "sys/ptrace.h"
#include "sys/stat.h"
#include "sys/syslog.h"
#include "sys/malloc.h"
#include "sys/mount.h"
#include "sys/ipc.h"
I 13
#include "sys/user.h"
E 14
I 14
D 47
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
E 47
I 47
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
I 48
#include <sys/mman.h>
E 48
E 47
E 14
E 13
E 11

D 11
#include "machine/cpu.h"
#include "machine/reg.h"
#include "machine/psl.h"
#include "machine/vmparam.h"
E 11
I 11
D 13
#include "../include/cpu.h"
#include "../include/reg.h"
#include "../include/psl.h"
#include "../include/vmparam.h"
E 13
I 13
D 47
#include "machine/cpu.h"
#include "machine/reg.h"
#include "machine/psl.h"
#include "machine/vmparam.h"
E 13
E 11
#include "hpux.h"
#include "hpux_termio.h"
E 47
I 47
#include <machine/cpu.h>
#include <machine/reg.h>
#include <machine/psl.h>
#include <machine/vmparam.h>
E 47
D 48

E 48
I 47
#include <hp/hpux/hpux.h>
#include <hp/hpux/hpux_termio.h>

E 47
#ifdef DEBUG
int unimpresponse = 0;
#endif

D 10
/* "tick" value for HZ==50 */
int hpuxtick = 1000000 / 50;

E 10
/* SYS5 style UTSNAME info */
struct hpuxutsname protoutsname = {
D 48
	"4.4bsd", "", "2.0", "B", "9000/3?0", ""
E 48
I 48
	"4.4bsd", "", "0.5", "B", "9000/3?0", ""
E 48
};

/* 6.0 and later style context */
I 35
#if defined(HP380)
char hpux040context[] =
    "standalone HP-MC68040 HP-MC68881 HP-MC68020 HP-MC68010 localroot default";
#endif
E 35
#ifdef FPCOPROC
char hpuxcontext[] =
	"standalone HP-MC68881 HP-MC68020 HP-MC68010 localroot default";
#else
char hpuxcontext[] =
	"standalone HP-MC68020 HP-MC68010 localroot default";
#endif

/* YP domainname */
char	domainname[MAXHOSTNAMELEN] = "unknown";
int	domainnamelen = 7;

D 56
#define NERR	79
E 56
I 56
#define NERR	83
E 56
#define BERR	1000

/* indexed by BSD errno */
short bsdtohpuxerrnomap[NERR] = {
/*00*/	  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,
/*10*/	 10,  45,  12,  13,  14,  15,  16,  17,  18,  19,
/*20*/	 20,  21,  22,  23,  24,  25,  26,  27,  28,  29,
/*30*/	 30,  31,  32,  33,  34, 246, 245, 244, 216, 217,
/*40*/	218, 219, 220, 221, 222, 223, 224, 225, 226, 227,
/*50*/	228, 229, 230, 231, 232, 233, 234, 235, 236, 237,
/*60*/	238, 239, 249, 248, 241, 242, 247,BERR,BERR,BERR,
D 56
/*70*/   70,  71,BERR,BERR,BERR,BERR,BERR,  46,BERR
E 56
I 56
/*70*/   70,  71,BERR,BERR,BERR,BERR,BERR,  46, 251,BERR,
/*80*/ BERR,BERR,  11
E 56
};

D 7
notimp(code, nargs)
E 7
I 7
D 59
notimp(p, uap, retval, code, nargs)
E 59
I 59
notimp(p, uap, retval, code, argsize)
E 59
	struct proc *p;
D 59
	int *uap, *retval;
	int code, nargs;
E 59
I 59
	register_t *uap, *retval;
	int code, argsize;
E 59
E 7
{
I 7
	int error = 0;
E 7
#ifdef DEBUG
D 7
	int *argp = u.u_ap;
E 7
I 7
	register int *argp = uap;
E 7
	extern char *hpuxsyscallnames[];

D 39
	printf("HPUX %s(", hpuxsyscallnames[code]);
E 39
I 39
	printf("HP-UX %s(", hpuxsyscallnames[code]);
E 39
D 59
	if (nargs)
		while (nargs--)
			printf("%x%c", *argp++, nargs? ',' : ')');
E 59
I 59
	if (argsize)
		while (argsize -= sizeof (register_t))
			printf("%x%c", *argp++, argsize? ',' : ')');
E 59
	else
		printf(")");
	printf("\n");
	switch (unimpresponse) {
	case 0:
D 7
		nosys();
E 7
I 7
		error = nosys(p, uap, retval);
E 7
		break;
	case 1:
D 7
		u.u_error = EINVAL;
E 7
I 7
		error = EINVAL;
E 7
		break;
	}
#else
D 7
	nosys();
E 7
I 7
	error = nosys(p, uap, retval);
E 7
#endif
D 7
	uprintf("HPUX system call %d not implemented\n", code);
E 7
I 7
	uprintf("HP-UX system call %d not implemented\n", code);
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

I 56
/*
 * HP-UX fork and vfork need to map the EAGAIN return value appropriately.
 */
hpuxfork(p, uap, retval)
	struct proc *p;
	struct hpuxwait3_args *uap;
	int *retval;
{
	int error;

	error = fork(p, uap, retval);
	if (error == EAGAIN)
		error = OEAGAIN;
	return (error);
}

hpuxvfork(p, uap, retval)
	struct proc *p;
	struct hpuxwait3_args *uap;
	int *retval;

{
	int error;

	error = vfork(p, uap, retval);
	if (error == EAGAIN)
		error = OEAGAIN;
	return (error);
}

E 56
I 42
struct hpuxexecv_args {
	char	*fname;
	char	**argp;
	char	**envp;
};
E 42
I 13
hpuxexecv(p, uap, retval)
	struct proc *p;
D 42
	struct args {
		char	*fname;
		char	**argp;
		char	**envp;
	} *uap;
E 42
I 42
	struct hpuxexecv_args *uap;
E 42
	int *retval;
{
	extern int execve();

	uap->envp = NULL;
	return (execve(p, uap, retval));
}

E 13
/*
D 39
 * HPUX versions of wait and wait3 actually pass the parameters
E 39
I 39
 * HP-UX versions of wait and wait3 actually pass the parameters
E 39
 * (status pointer, options, rusage) into the kernel rather than
D 4
 * handling it in the C library stub.  We also need to map any
 * termination signal from BSD to HPUX.
E 4
I 4
D 5
 * handling it in the C library stub.  For now, use COMPAT_43 version
 * of wait (owait), as it's most convenient (it leaves the status
 * in rval2 where we can muck with it before copying out).
 * We also need to map any termination signal from BSD to HPUX.
E 5
I 5
 * handling it in the C library stub.  We also need to map any
D 39
 * termination signal from BSD to HPUX.
E 39
I 39
 * termination signal from BSD to HP-UX.
E 39
E 5
E 4
 */
I 42
struct hpuxwait3_args {
	int	*status;
	int	options;
	int	rusage;
};
E 42
D 7
hpuxwait3()
{
	struct a {
E 7
I 7
hpuxwait3(p, uap, retval)
	struct proc *p;
D 42
	struct args {
E 7
		int	*status;
		int	options;
		int	rusage;
D 7
	} *uap = (struct a *)u.u_ap;

E 7
I 7
	} *uap;
E 42
I 42
	struct hpuxwait3_args *uap;
E 42
	int *retval;
{
E 7
	/* rusage pointer must be zero */
D 7
	if (uap->rusage) {
		u.u_error = EINVAL;
		return;
	}
E 7
I 7
	if (uap->rusage)
D 9
		RETURN (EINVAL);
E 9
I 9
		return (EINVAL);
E 9
E 7
D 13
	u.u_ar0[PS] = PSL_ALLCC;
	u.u_ar0[R0] = uap->options;
	u.u_ar0[R1] = uap->rusage;
E 13
I 13
D 18
	p->p_regs[PS] = PSL_ALLCC;
	p->p_regs[R0] = uap->options;
	p->p_regs[R1] = uap->rusage;
E 18
I 18
	p->p_md.md_regs[PS] = PSL_ALLCC;
	p->p_md.md_regs[R0] = uap->options;
	p->p_md.md_regs[R1] = uap->rusage;
E 18
E 13
D 7
	hpuxwait();
E 7
I 7
D 9
	RETURN (hpuxwait(p, uap, retval));
E 9
I 9
	return (hpuxwait(p, uap, retval));
E 9
E 7
}

I 42
struct hpuxwait_args {
	int	*status;
};
E 42
D 7
hpuxwait()
{
	int sig, *statp;
	struct a {
E 7
I 7
hpuxwait(p, uap, retval)
	struct proc *p;
D 42
	struct args {
E 7
		int	*status;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
E 42
I 42
	struct hpuxwait_args *uap;
E 42
	int *retval;
{
	int sig, *statp, error;
E 7

	statp = uap->status;	/* owait clobbers first arg */
D 7
	owait();
E 7
I 7
D 59
	error = owait(p, uap, retval);
E 59
I 59
	error = compat_43_wait(p, uap, retval);
E 59
E 7
I 5
	/*
	 * HP-UX wait always returns EINTR when interrupted by a signal
	 * (well, unless its emulating a BSD process, but we don't bother...)
	 */
D 7
	if (u.u_error == ERESTART)
		u.u_error = EINTR;
	if (u.u_error)
		return;
	sig = u.u_r.r_val2 & 0xFF;
E 7
I 7
	if (error == ERESTART)
		error = EINTR;
	if (error)
D 9
		RETURN (error);
E 9
I 9
		return (error);
E 9
	sig = retval[1] & 0xFF;
E 7
	if (sig == WSTOPPED) {
D 7
		sig = (u.u_r.r_val2 >> 8) & 0xFF;
		u.u_r.r_val2 = (bsdtohpuxsig(sig) << 8) | WSTOPPED;
E 7
I 7
		sig = (retval[1] >> 8) & 0xFF;
		retval[1] = (bsdtohpuxsig(sig) << 8) | WSTOPPED;
E 7
	} else if (sig)
D 7
		u.u_r.r_val2 = (u.u_r.r_val2 & 0xFF00) |
E 7
I 7
		retval[1] = (retval[1] & 0xFF00) |
E 7
			bsdtohpuxsig(sig & 0x7F) | (sig & 0x80);
	if (statp)
D 7
		if (suword((caddr_t)statp, u.u_r.r_val2))
			u.u_error = EFAULT;
E 7
I 7
		if (suword((caddr_t)statp, retval[1]))
			error = EFAULT;
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

I 42
struct hpuxwaitpid_args {
	int	pid;
	int	*status;
	int	options;
	struct	rusage *rusage;	/* wait4 arg */
};
E 42
D 7
hpuxwaitpid()
{
	int sig, *statp;
	struct a {
E 7
I 7
hpuxwaitpid(p, uap, retval)
	struct proc *p;
D 42
	struct args {
E 7
		int	pid;
		int	*status;
		int	options;
		struct	rusage *rusage;	/* wait4 arg */
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
E 42
I 42
	struct hpuxwaitpid_args *uap;
E 42
	int *retval;
{
D 46
	int sig, *statp, error;
E 46
I 46
	int rv, sig, xstat, error;
E 46
E 7

	uap->rusage = 0;
D 7
	wait4();
E 7
I 7
	error = wait4(p, uap, retval);
E 7
E 5
	/*
	 * HP-UX wait always returns EINTR when interrupted by a signal
	 * (well, unless its emulating a BSD process, but we don't bother...)
	 */
D 4
	if (u.u_eosys == RESTARTSYS) {
		u.u_eosys = NORMALRETURN;
E 4
I 4
D 7
	if (u.u_error == ERESTART)
E 4
		u.u_error = EINTR;
D 4
	}
E 4
	if (u.u_error)
		return;
	sig = u.u_r.r_val2 & 0xFF;
E 7
I 7
	if (error == ERESTART)
		error = EINTR;
	if (error)
D 9
		RETURN (error);
E 9
I 9
		return (error);
E 9
D 46
	sig = retval[1] & 0xFF;
E 7
	if (sig == WSTOPPED) {
D 7
		sig = (u.u_r.r_val2 >> 8) & 0xFF;
		u.u_r.r_val2 = (bsdtohpuxsig(sig) << 8) | WSTOPPED;
E 7
I 7
		sig = (retval[1] >> 8) & 0xFF;
		retval[1] = (bsdtohpuxsig(sig) << 8) | WSTOPPED;
E 7
	} else if (sig)
D 7
		u.u_r.r_val2 = (u.u_r.r_val2 & 0xFF00) |
E 7
I 7
		retval[1] = (retval[1] & 0xFF00) |
E 7
			bsdtohpuxsig(sig & 0x7F) | (sig & 0x80);
	if (statp)
D 7
		if (suword((caddr_t)statp, u.u_r.r_val2))
			u.u_error = EFAULT;
E 7
I 7
		if (suword((caddr_t)statp, retval[1]))
			error = EFAULT;
E 46
I 46
	if (uap->status) {
		/*
		 * Wait4 already wrote the status out to user space,
		 * pull it back, change the signal portion, and write
		 * it back out.
		 */
		rv = fuword((caddr_t)uap->status);
		if (WIFSTOPPED(rv)) {
			sig = WSTOPSIG(rv);
			rv = W_STOPCODE(bsdtohpuxsig(sig));
		} else if (WIFSIGNALED(rv)) {
			sig = WTERMSIG(rv);
			xstat = WEXITSTATUS(rv);
			rv = W_EXITCODE(xstat, bsdtohpuxsig(sig)) |
				WCOREDUMP(rv);
		}
		(void)suword((caddr_t)uap->status, rv);
	}
E 46
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

/*
I 54
 * Old creat system call.
 */
struct hpuxcreat_args {
	char	*fname;
	int	fmode;
};
hpuxcreat(p, uap, retval)
	struct proc *p;
	register struct hpuxcreat_args *uap;
	int *retval;
{
	struct nargs {
		char	*fname;
		int	mode;
		int	crtmode;
	} openuap;

	openuap.fname = uap->fname;
	openuap.crtmode = uap->fmode;
	openuap.mode = O_WRONLY | O_CREAT | O_TRUNC;
	return (open(p, &openuap, retval));
}

/*
 * XXX extensions to the fd_ofileflags flags.
 * Hate to put this there, but they do need to be per-file.
 */
#define UF_NONBLOCK_ON	0x10
#define	UF_FNDELAY_ON	0x20
#define	UF_FIONBIO_ON	0x40

/*
E 54
 * Must remap some bits in the mode mask.
 * O_CREAT, O_TRUNC, and O_EXCL must be remapped,
D 54
 * O_SYNCIO (0100000) is removed entirely.
E 54
I 54
 * O_NONBLOCK is remapped and remembered,
 * O_FNDELAY is remembered,
 * O_SYNCIO is removed entirely.
E 54
 */
I 42
struct hpuxopen_args {
	char	*fname;
	int	mode;
	int	crtmode;
};
E 42
D 6
hpuxopen(scp)
	register struct syscontext *scp;
{
	struct a {
E 6
I 6
hpuxopen(p, uap, retval)
	struct proc *p;
D 7
	struct args {
E 7
I 7
D 42
	register struct args {
E 7
E 6
		char	*fname;
		int	mode;
		int	crtmode;
D 6
	} *uap = (struct a *) scp->sc_ap;
	struct nameidata *ndp = &scp->sc_nd;
E 6
I 6
	} *uap;
E 42
I 42
	register struct hpuxopen_args *uap;
E 42
	int *retval;
{
E 6
D 54
	int mode;
E 54
I 54
	int mode, error;
E 54

	mode = uap->mode;
D 54
	uap->mode &= ~(HPUXFSYNCIO|HPUXFEXCL|HPUXFTRUNC|HPUXFCREAT);
E 54
I 54
	uap->mode &=
		~(HPUXNONBLOCK|HPUXFSYNCIO|HPUXFEXCL|HPUXFTRUNC|HPUXFCREAT);
E 54
	if (mode & HPUXFCREAT) {
		/*
		 * simulate the pre-NFS behavior that opening a
		 * file for READ+CREATE ignores the CREATE (unless
		 * EXCL is set in which case we will return the
		 * proper error).
		 */
D 13
		if ((mode & HPUXFEXCL) || ((mode-FOPEN) & FWRITE))
E 13
I 13
		if ((mode & HPUXFEXCL) || (FFLAGS(mode) & FWRITE))
E 13
D 16
			uap->mode |= FCREAT;
E 16
I 16
			uap->mode |= O_CREAT;
E 16
	}
	if (mode & HPUXFTRUNC)
D 16
		uap->mode |= FTRUNC;
E 16
I 16
		uap->mode |= O_TRUNC;
E 16
	if (mode & HPUXFEXCL)
D 16
		uap->mode |= FEXCL;
E 16
I 16
		uap->mode |= O_EXCL;
E 16
D 6
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
	RETURN (copen(scp, uap->mode-FOPEN, uap->crtmode &~ scp->sc_cmask, ndp,
		&scp->sc_retval1));
E 6
I 6
D 9
	RETURN (open(p, uap, retval));
E 9
I 9
D 54
	return (open(p, uap, retval));
E 54
I 54
	if (mode & HPUXNONBLOCK)
		uap->mode |= O_NDELAY;
	error = open(p, uap, retval);
	/*
	 * Record non-blocking mode for fcntl, read, write, etc.
	 */
	if (error == 0 && (uap->mode & O_NDELAY))
		p->p_fd->fd_ofileflags[*retval] |=
			(mode & HPUXNONBLOCK) ? UF_NONBLOCK_ON : UF_FNDELAY_ON;
	return (error);
E 54
E 9
E 6
}

I 46
D 54
/*
 * Old creat system call.
 */
struct hpuxcreat_args {
	char	*fname;
	int	fmode;
};
hpuxcreat(p, uap, retval)
	struct proc *p;
	register struct hpuxcreat_args *uap;
	int *retval;
{
	struct nargs {
		char	*fname;
		int	mode;
		int	crtmode;
	} openuap;

	openuap.fname = uap->fname;
	openuap.crtmode = uap->fmode;
	openuap.mode = O_WRONLY | O_CREAT | O_TRUNC;
	return (open(p, &openuap, retval));
}

E 46
I 15
/* XXX */
#define	UF_FNDELAY_ON	0x20
#define	UF_FIONBIO_ON	0x40
/* XXX */

E 54
I 42
struct hpuxfcntl_args {
	int	fdes;
	int	cmd;
	int	arg;
};
E 42
E 15
D 7
hpuxfcntl()
{
	register struct a {
E 7
I 7
hpuxfcntl(p, uap, retval)
	struct proc *p;
D 42
	register struct args {
E 7
		int	fdes;
		int	cmd;
		int	arg;
D 7
	} *uap = (struct a *)u.u_ap;
	int mode;
E 7
I 7
	} *uap;
E 42
I 42
	register struct hpuxfcntl_args *uap;
E 42
	int *retval;
{
D 58
	int mode, error;
I 15
	char *fp;
E 58
I 58
	int mode, error, flg = F_POSIX;
	struct file *fp;
	char *pop;
	struct hpuxflock hfl;
	struct flock fl;
	struct vnode *vp;
E 58
E 15
E 7

I 15
D 58
	if (uap->cmd == F_GETFL || uap->cmd == F_SETFL) {
		if ((unsigned)uap->fdes >= p->p_fd->fd_nfiles ||
		    p->p_fd->fd_ofiles[uap->fdes] == NULL)
			return (EBADF);
		fp = &p->p_fd->fd_ofileflags[uap->fdes];
	}
E 58
I 58
	if ((unsigned)uap->fdes >= p->p_fd->fd_nfiles ||
	    (fp = p->p_fd->fd_ofiles[uap->fdes]) == NULL)
		return (EBADF);
	pop = &p->p_fd->fd_ofileflags[uap->fdes];
E 58
E 15
	switch (uap->cmd) {
	case F_SETFL:
I 54
		if (uap->arg & HPUXNONBLOCK)
D 58
			*fp |= UF_NONBLOCK_ON;
E 58
I 58
			*pop |= UF_NONBLOCK_ON;
E 58
		else
D 58
			*fp &= ~UF_NONBLOCK_ON;
E 58
I 58
			*pop &= ~UF_NONBLOCK_ON;
E 58
E 54
I 15
D 16
		if (uap->arg & FNDELAY)
E 16
I 16
D 56
		if (uap->arg & FNONBLOCK)
E 56
I 56
		if (uap->arg & HPUXNDELAY)
E 56
E 16
D 58
			*fp |= UF_FNDELAY_ON;
E 58
I 58
			*pop |= UF_FNDELAY_ON;
E 58
D 54
		else {
E 54
I 54
		else
E 54
D 58
			*fp &= ~UF_FNDELAY_ON;
D 54
			if (*fp & UF_FIONBIO_ON)
D 16
				uap->arg |= FNDELAY;
E 16
I 16
				uap->arg |= FNONBLOCK;
E 16
		}
E 15
		uap->arg &= ~(HPUXFSYNCIO|HPUXFREMOTE|FUSECACHE);
E 54
I 54
		if (*fp & (UF_NONBLOCK_ON|UF_FNDELAY_ON|UF_FIONBIO_ON))
E 58
I 58
			*pop &= ~UF_FNDELAY_ON;
		if (*pop & (UF_NONBLOCK_ON|UF_FNDELAY_ON|UF_FIONBIO_ON))
E 58
			uap->arg |= FNONBLOCK;
I 58
		else
			uap->arg &= ~FNONBLOCK;
E 58
		uap->arg &= ~(HPUXNONBLOCK|HPUXFSYNCIO|HPUXFREMOTE);
E 54
		break;
	case F_GETFL:
	case F_DUPFD:
	case F_GETFD:
	case F_SETFD:
		break;
I 58

	case HPUXF_SETLKW:
		flg |= F_WAIT;
		/* Fall into F_SETLK */

	case HPUXF_SETLK:
		if (fp->f_type != DTYPE_VNODE)
			return (EBADF);
		vp = (struct vnode *)fp->f_data;
		/* Copy in the lock structure */
		error = copyin((caddr_t)uap->arg, (caddr_t)&hfl, sizeof (hfl));
		if (error)
			return (error);
		fl.l_start = hfl.hl_start;
		fl.l_len = hfl.hl_len;
		fl.l_pid = hfl.hl_pid;
		fl.l_type = hfl.hl_type;
		fl.l_whence = hfl.hl_whence;
		if (fl.l_whence == SEEK_CUR)
			fl.l_start += fp->f_offset;
		switch (fl.l_type) {

		case F_RDLCK:
			if ((fp->f_flag & FREAD) == 0)
				return (EBADF);
			p->p_flag |= P_ADVLOCK;
			return (VOP_ADVLOCK(vp, (caddr_t)p, F_SETLK, &fl, flg));

		case F_WRLCK:
			if ((fp->f_flag & FWRITE) == 0)
				return (EBADF);
			p->p_flag |= P_ADVLOCK;
			return (VOP_ADVLOCK(vp, (caddr_t)p, F_SETLK, &fl, flg));

		case F_UNLCK:
			return (VOP_ADVLOCK(vp, (caddr_t)p, F_UNLCK, &fl,
				F_POSIX));

		default:
			return (EINVAL);
		}

	case F_GETLK:
		if (fp->f_type != DTYPE_VNODE)
			return (EBADF);
		vp = (struct vnode *)fp->f_data;
		/* Copy in the lock structure */
		error = copyin((caddr_t)uap->arg, (caddr_t)&hfl, sizeof (hfl));
		if (error)
			return (error);
		fl.l_start = hfl.hl_start;
		fl.l_len = hfl.hl_len;
		fl.l_pid = hfl.hl_pid;
		fl.l_type = hfl.hl_type;
		fl.l_whence = hfl.hl_whence;
		if (fl.l_whence == SEEK_CUR)
			fl.l_start += fp->f_offset;
		if (error = VOP_ADVLOCK(vp, (caddr_t)p, F_GETLK, &fl, F_POSIX))
			return (error);
		hfl.hl_start = fl.l_start;
		hfl.hl_len = fl.l_len;
		hfl.hl_pid = fl.l_pid;
		hfl.hl_type = fl.l_type;
		hfl.hl_whence = fl.l_whence;
		return (copyout((caddr_t)&hfl, (caddr_t)uap->arg, sizeof (hfl)));

E 58
	default:
D 7
		u.u_error = EINVAL;
		return;
E 7
I 7
D 9
		RETURN (EINVAL);
E 9
I 9
		return (EINVAL);
E 9
E 7
	}
D 7
	fcntl();
	if (u.u_error == 0 && uap->arg == F_GETFL) {
		mode = u.u_r.r_val1;
		u.u_r.r_val1 &= ~(FCREAT|FTRUNC|FEXCL|FUSECACHE);
E 7
I 7
	error = fcntl(p, uap, retval);
D 15
	if (error == 0 && uap->arg == F_GETFL) {
E 15
I 15
	if (error == 0 && uap->cmd == F_GETFL) {
E 15
		mode = *retval;
D 16
		*retval &= ~(FCREAT|FTRUNC|FEXCL|FUSECACHE);
I 15
		if ((mode & FNDELAY) && (*fp & UF_FNDELAY_ON) == 0)
			*retval &= ~FNDELAY;
E 15
E 7
		if (mode & FCREAT)
E 16
I 16
D 54
		*retval &= ~(O_CREAT|O_TRUNC|O_EXCL|FUSECACHE);
		if ((mode & FNONBLOCK) && (*fp & UF_FNDELAY_ON) == 0)
			*retval &= ~FNONBLOCK;
E 54
I 54
		*retval &= ~(O_CREAT|O_TRUNC|O_EXCL);
		if (mode & FNONBLOCK) {
D 58
			if (*fp & UF_NONBLOCK_ON)
E 58
I 58
			if (*pop & UF_NONBLOCK_ON)
E 58
				*retval |= HPUXNONBLOCK;
D 58
			if ((*fp & UF_FNDELAY_ON) == 0)
E 58
I 58
			if ((*pop & UF_FNDELAY_ON) == 0)
E 58
D 56
				*retval &= ~FNONBLOCK;
E 56
I 56
				*retval &= ~HPUXNDELAY;
E 56
		}
E 54
		if (mode & O_CREAT)
E 16
D 7
			u.u_r.r_val1 |= HPUXFCREAT;
E 7
I 7
			*retval |= HPUXFCREAT;
E 7
D 16
		if (mode & FTRUNC)
E 16
I 16
		if (mode & O_TRUNC)
E 16
D 7
			u.u_r.r_val1 |= HPUXFTRUNC;
E 7
I 7
			*retval |= HPUXFTRUNC;
E 7
D 16
		if (mode & FEXCL)
E 16
I 16
		if (mode & O_EXCL)
E 16
D 7
			u.u_r.r_val1 |= HPUXFEXCL;
E 7
I 7
			*retval |= HPUXFEXCL;
E 7
	}
I 7
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

/*
D 54
 * Read and write should return a 0 count when an operation
D 15
 * on a VNODE would block, not an error.  Sockets appear to
 * return EWOULDBLOCK (at least in 6.2).  This is probably
 * not entirely correct, since the behavior is only defined
 * for pipes and tty type devices.
E 15
I 15
 * on a VNODE would block, not an error.
E 54
I 54
 * Read and write calls.  Same as BSD except for non-blocking behavior.
 * There are three types of non-blocking reads/writes in HP-UX checked
 * in the following order:
E 54
 *
D 54
 * In 6.2 and 6.5 sockets appear to return EWOULDBLOCK.
D 16
 * In 7.0 the behavior for sockets depends on whether FNDELAY is in effect.
E 16
I 16
 * In 7.0 the behavior for sockets depends on whether FNONBLOCK is in effect.
E 54
I 54
 *	O_NONBLOCK: return -1 and errno == EAGAIN
 *	O_NDELAY:   return 0
 *	FIOSNBIO:   return -1 and errno == EWOULDBLOCK
E 54
E 16
E 15
 */
I 42
D 54
struct hpuxread_args {
	int	fd;
E 54
I 54
struct hpuxrw_args {
	int fd;
E 54
};
I 54

E 54
E 42
D 7
hpuxread()
{
	struct a {
E 7
I 7
hpuxread(p, uap, retval)
	struct proc *p;
D 42
	struct args {
E 7
		int	fd;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
E 42
I 42
D 54
	struct hpuxread_args *uap;
E 54
I 54
	struct hpuxrw_args *uap;
E 54
E 42
	int *retval;
{
	int error;
E 7

D 7
	read();
	if (u.u_error == EWOULDBLOCK &&
E 7
I 7
	error = read(p, uap, retval);
D 54
	if (error == EWOULDBLOCK &&
E 7
D 12
	    u.u_ofile[uap->fd]->f_type == DTYPE_VNODE) {
E 12
I 12
D 13
	    (OFILE(p->p_fd, uap->fd))->f_type == DTYPE_VNODE) {
E 13
I 13
D 15
	    p->p_fd->fd_ofiles[uap->fd]->f_type == DTYPE_VNODE) {
E 15
I 15
	    (p->p_fd->fd_ofiles[uap->fd]->f_type == DTYPE_VNODE ||
	     p->p_fd->fd_ofileflags[uap->fd] & UF_FNDELAY_ON)) {
E 15
E 13
E 12
D 7
		u.u_error = 0;
		u.u_r.r_val1 = 0;
E 7
I 7
		error = 0;
		*retval = 0;
E 54
I 54
	if (error == EWOULDBLOCK) {
		char *fp = &p->p_fd->fd_ofileflags[uap->fd];

		if (*fp & UF_NONBLOCK_ON) {
			*retval = -1;
D 56
			error = EAGAIN;
E 56
I 56
			error = OEAGAIN;
E 56
		} else if (*fp & UF_FNDELAY_ON) {
			*retval = 0;
			error = 0;
		}
E 54
E 7
	}
I 7
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

I 42
D 54
struct hpuxwrite_args {
	int	fd;
};
E 54
E 42
D 7
hpuxwrite()
{
	struct a {
E 7
I 7
hpuxwrite(p, uap, retval)
	struct proc *p;
D 42
	struct args {
E 7
		int	fd;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
E 42
I 42
D 54
	struct hpuxwrite_args *uap;
E 54
I 54
	struct hpuxrw_args *uap;
E 54
E 42
	int *retval;
{
	int error;
E 7

D 7
	write();
	if (u.u_error == EWOULDBLOCK &&
E 7
I 7
	error = write(p, uap, retval);
D 54
	if (error == EWOULDBLOCK &&
E 7
D 12
	    u.u_ofile[uap->fd]->f_type == DTYPE_VNODE) {
E 12
I 12
D 13
	    (OFILE(p->p_fd, uap->fd))->f_type == DTYPE_VNODE) {
E 13
I 13
D 15
	    p->p_fd->fd_ofiles[uap->fd]->f_type == DTYPE_VNODE) {
E 15
I 15
	    (p->p_fd->fd_ofiles[uap->fd]->f_type == DTYPE_VNODE ||
	     p->p_fd->fd_ofileflags[uap->fd] & UF_FNDELAY_ON)) {
E 15
E 13
E 12
D 7
		u.u_error = 0;
		u.u_r.r_val1 = 0;
E 7
I 7
		error = 0;
		*retval = 0;
E 54
I 54
	if (error == EWOULDBLOCK) {
		char *fp = &p->p_fd->fd_ofileflags[uap->fd];

		if (*fp & UF_NONBLOCK_ON) {
			*retval = -1;
D 56
			error = EAGAIN;
E 56
I 56
			error = OEAGAIN;
E 56
		} else if (*fp & UF_FNDELAY_ON) {
			*retval = 0;
			error = 0;
		}
E 54
E 7
	}
I 7
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

I 42
D 54
struct hpuxreadv_args {
	int	fd;
};
E 54
E 42
D 7
hpuxreadv()
{
	struct a {
E 7
I 7
hpuxreadv(p, uap, retval)
	struct proc *p;
D 42
	struct args {
E 7
		int	fd;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
E 42
I 42
D 54
	struct hpuxreadv_args *uap;
E 54
I 54
	struct hpuxrw_args *uap;
E 54
E 42
	int *retval;
{
	int error;
E 7

D 7
	readv();
	if (u.u_error == EWOULDBLOCK &&
E 7
I 7
	error = readv(p, uap, retval);
D 54
	if (error == EWOULDBLOCK &&
E 7
D 12
	    u.u_ofile[uap->fd]->f_type == DTYPE_VNODE) {
E 12
I 12
D 13
	    (OFILE(p->p_fd, uap->fd))->f_type == DTYPE_VNODE) {
E 13
I 13
D 15
	    p->p_fd->fd_ofiles[uap->fd]->f_type == DTYPE_VNODE) {
E 15
I 15
	    (p->p_fd->fd_ofiles[uap->fd]->f_type == DTYPE_VNODE ||
	     p->p_fd->fd_ofileflags[uap->fd] & UF_FNDELAY_ON)) {
E 15
E 13
E 12
D 7
		u.u_error = 0;
		u.u_r.r_val1 = 0;
E 7
I 7
		error = 0;
		*retval = 0;
E 54
I 54
	if (error == EWOULDBLOCK) {
		char *fp = &p->p_fd->fd_ofileflags[uap->fd];

		if (*fp & UF_NONBLOCK_ON) {
			*retval = -1;
D 56
			error = EAGAIN;
E 56
I 56
			error = OEAGAIN;
E 56
		} else if (*fp & UF_FNDELAY_ON) {
			*retval = 0;
			error = 0;
		}
E 54
E 7
	}
I 7
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

I 42
D 54
struct hpuxwritev_args {
	int	fd;
};
E 54
E 42
D 7
hpuxwritev()
{
	struct a {
E 7
I 7
hpuxwritev(p, uap, retval)
	struct proc *p;
D 42
	struct args {
E 7
		int	fd;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
E 42
I 42
D 54
	struct hpuxwritev_args *uap;
E 54
I 54
	struct hpuxrw_args *uap;
E 54
E 42
	int *retval;
{
	int error;
E 7

D 7
	writev();
	if (u.u_error == EWOULDBLOCK &&
E 7
I 7
	error = writev(p, uap, retval);
D 54
	if (error == EWOULDBLOCK &&
E 7
D 12
	    u.u_ofile[uap->fd]->f_type == DTYPE_VNODE) {
E 12
I 12
D 13
	    (OFILE(p->p_fd, uap->fd))->f_type == DTYPE_VNODE) {
E 13
I 13
D 15
	    p->p_fd->fd_ofiles[uap->fd]->f_type == DTYPE_VNODE) {
E 15
I 15
	    (p->p_fd->fd_ofiles[uap->fd]->f_type == DTYPE_VNODE ||
	     p->p_fd->fd_ofileflags[uap->fd] & UF_FNDELAY_ON)) {
E 15
E 13
E 12
D 7
		u.u_error = 0;
		u.u_r.r_val1 = 0;
E 7
I 7
		error = 0;
		*retval = 0;
E 54
I 54
	if (error == EWOULDBLOCK) {
		char *fp = &p->p_fd->fd_ofileflags[uap->fd];

		if (*fp & UF_NONBLOCK_ON) {
			*retval = -1;
D 56
			error = EAGAIN;
E 56
I 56
			error = OEAGAIN;
E 56
		} else if (*fp & UF_FNDELAY_ON) {
			*retval = 0;
			error = 0;
		}
E 54
E 7
	}
I 7
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

/*
 * 4.3bsd dup allows dup2 to come in on the same syscall entry
D 39
 * and hence allows two arguments.  HPUX dup has only one arg.
E 39
I 39
 * and hence allows two arguments.  HP-UX dup has only one arg.
E 39
 */
I 42
struct hpuxdup_args {
	int	i;
};
E 42
D 7
hpuxdup()
{
	register struct a {
E 7
I 7
hpuxdup(p, uap, retval)
	struct proc *p;
D 42
	register struct args {
E 7
		int	i;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
E 42
I 42
	register struct hpuxdup_args *uap;
E 42
	int *retval;
{
I 12
	register struct filedesc *fdp = p->p_fd;
E 12
E 7
	struct file *fp;
D 7
	int j;
E 7
I 7
	int fd, error;
E 7

D 7
	if ((unsigned)uap->i >= NOFILE || (fp = u.u_ofile[uap->i]) == NULL) {
		u.u_error = EBADF;
		return;
	}
	u.u_error = ufalloc(0, &j);
	if (u.u_error)
		return;
	u.u_r.r_val1 = j;
D 6
	dupit(j, fp, u.u_pofile[uap->i] &~ UF_EXCLOSE);
E 6
I 6
	u.u_ofile[j] = fp;
	u.u_pofile[j] = u.u_pofile[uap->i] &~ UF_EXCLOSE;
E 7
I 7
D 12
	if ((unsigned)uap->i >= NOFILE || (fp = u.u_ofile[uap->i]) == NULL)
E 12
I 12
D 13
	if (((unsigned)uap->i) >= fdp->fd_maxfiles ||
	    (fp = OFILE(fdp, uap->i)) == NULL)
E 13
I 13
	if (((unsigned)uap->i) >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[uap->i]) == NULL)
E 13
E 12
D 9
		RETURN (EBADF);
E 9
I 9
		return (EBADF);
E 9
D 12
	if (error = ufalloc(0, &fd))
E 12
I 12
D 13
	if (error = ufalloc(fdp, 0, &fd))
E 13
I 13
	if (error = fdalloc(p, 0, &fd))
E 13
E 12
D 9
		RETURN (error);
E 9
I 9
		return (error);
E 9
D 12
	*retval = fd;
	u.u_ofile[fd] = fp;
	u.u_pofile[fd] = u.u_pofile[uap->i] &~ UF_EXCLOSE;
E 12
I 12
D 13
	OFILE(fdp, fd) = fp;
	OFILEFLAGS(fdp, fd) = OFILEFLAGS(fdp, uap->i) &~ UF_EXCLOSE;
E 13
I 13
	fdp->fd_ofiles[fd] = fp;
	fdp->fd_ofileflags[fd] = fdp->fd_ofileflags[uap->i] &~ UF_EXCLOSE;
E 13
E 12
E 7
	fp->f_count++;
D 7
	if (j > u.u_lastfile)
		u.u_lastfile = j;
E 7
I 7
D 12
	if (fd > u.u_lastfile)
		u.u_lastfile = fd;
E 12
I 12
	if (fd > fdp->fd_lastfile)
		fdp->fd_lastfile = fd;
	*retval = fd;
E 12
D 9
	RETURN (0);
E 9
I 9
	return (0);
E 9
E 7
E 6
}

I 42
struct hpuxutssys_args {
	struct hpuxutsname *uts;
	int dev;
	int request;
};
E 42
D 7
hpuxuname()
{
	register struct a {
E 7
I 7
D 10
hpuxuname(p, uap, retval)
E 10
I 10
hpuxutssys(p, uap, retval)
E 10
	struct proc *p;
D 42
	register struct args {
E 7
		struct hpuxutsname *uts;
		int dev;
		int request;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
E 42
I 42
	register struct hpuxutssys_args *uap;
E 42
	int *retval;
{
E 7
	register int i;
I 7
	int error;
E 7

	switch (uap->request) {
	/* uname */
	case 0:
		/* fill in machine type */
		switch (machineid) {
		case HP_320:
			protoutsname.machine[6] = '2';
			break;
		/* includes 318 and 319 */
		case HP_330:
			protoutsname.machine[6] = '3';
			break;
		case HP_340:
			protoutsname.machine[6] = '4';
			break;
		case HP_350:
			protoutsname.machine[6] = '5';
			break;
		case HP_360:
			protoutsname.machine[6] = '6';
			break;
		case HP_370:
			protoutsname.machine[6] = '7';
			break;
I 7
		/* includes 345 */
		case HP_375:
			protoutsname.machine[6] = '7';
			protoutsname.machine[7] = '5';
			break;
I 39
		/* includes 425 */
		case HP_380:
			protoutsname.machine[6] = '8';
			break;
I 48
		case HP_433:
			protoutsname.machine[5] = '4';
			protoutsname.machine[6] = '3';
			protoutsname.machine[7] = '3';
			break;
E 48
E 39
E 7
		}
		/* copy hostname (sans domain) to nodename */
D 15
		for (i = 0; i < 9 && hostname[i] != '.'; i++)
E 15
I 15
		for (i = 0; i < 8 && hostname[i] != '.'; i++)
E 15
			protoutsname.nodename[i] = hostname[i];
I 15
		protoutsname.nodename[i] = '\0';
E 15
D 7
		u.u_error = copyout((caddr_t)&protoutsname, (caddr_t)uap->uts,
				    sizeof(struct hpuxutsname));
E 7
I 7
		error = copyout((caddr_t)&protoutsname, (caddr_t)uap->uts,
				sizeof(struct hpuxutsname));
E 7
		break;
D 10
	/* ustat - who cares? */
	case 2:
E 10
I 10

	/* gethostname */
	case 5:
		/* uap->dev is length */
		if (uap->dev > hostnamelen + 1)
			uap->dev = hostnamelen + 1;
		error = copyout((caddr_t)hostname, (caddr_t)uap->uts,
				uap->dev);
		break;

	case 1:	/* ?? */
	case 2:	/* ustat */
	case 3:	/* ?? */
	case 4:	/* sethostname */
E 10
	default:
D 7
		u.u_error = EINVAL;
E 7
I 7
		error = EINVAL;
E 7
		break;
	}
I 7
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

I 42
struct hpuxsysconf_args {
	int	name;
};
E 42
I 35
hpuxsysconf(p, uap, retval)
	struct proc *p;
D 42
	struct args {
		int	name;
	} *uap;
E 42
I 42
	struct hpuxsysconf_args *uap;
E 42
	int *retval;
{
	switch (uap->name) {

I 57
	/* clock ticks per second */
	case HPUX_SYSCONF_CLKTICK:
		*retval = hz;
		break;

E 57
	/* open files */
	case HPUX_SYSCONF_OPENMAX:
		*retval = NOFILE;
		break;

	/* architecture */
	case HPUX_SYSCONF_CPUTYPE:
		switch (machineid) {
		case HP_320:
		case HP_330:
		case HP_350:
			*retval = HPUX_SYSCONF_CPUM020;
			break;
		case HP_340:
		case HP_360:
		case HP_370:
		case HP_375:
			*retval = HPUX_SYSCONF_CPUM030;
			break;
		case HP_380:
I 48
		case HP_433:
E 48
			*retval = HPUX_SYSCONF_CPUM040;
			break;
		}
		break;
	default:
D 39
		uprintf("HPUX sysconf(%d) not implemented\n", uap->name);
E 39
I 39
		uprintf("HP-UX sysconf(%d) not implemented\n", uap->name);
E 39
		return (EINVAL);
	}
	return (0);
}

I 42
struct hpuxstat_args {
	char	*fname;
	struct hpuxstat *hsb;
};
E 42
E 35
D 7
hpuxstat()
{
	struct a {
E 7
I 7
hpuxstat(p, uap, retval)
	struct proc *p;
D 42
	struct args {
E 7
		char	*fname;
		struct hpuxstat *hsb;
D 7
	} *uap = (struct a *)u.u_ap;

	u.u_error = hpuxstat1(uap->fname, uap->hsb, FOLLOW);
E 7
I 7
	} *uap;
E 42
I 42
	struct hpuxstat_args *uap;
E 42
	int *retval;
{
D 9
	RETURN (hpuxstat1(uap->fname, uap->hsb, FOLLOW));
E 9
I 9
D 45
	return (hpuxstat1(uap->fname, uap->hsb, FOLLOW));
E 45
I 45
	return (hpuxstat1(uap->fname, uap->hsb, FOLLOW, p));
E 45
E 9
E 7
}

I 42
struct hpuxlstat_args {
	char	*fname;
	struct hpuxstat *hsb;
};
E 42
D 7
hpuxlstat()
{
	struct a {
E 7
I 7
hpuxlstat(p, uap, retval)
	struct proc *p;
D 42
	struct args {
E 7
		char	*fname;
D 7
		struct	hpuxstat *hsb;
	} *uap = (struct a *) u.u_ap;

	u.u_error = hpuxstat1(uap->fname, uap->hsb, NOFOLLOW);
E 7
I 7
		struct hpuxstat *hsb;
	} *uap;
E 42
I 42
	struct hpuxlstat_args *uap;
E 42
	int *retval;
{
D 9
	RETURN (hpuxstat1(uap->fname, uap->hsb, NOFOLLOW));
E 9
I 9
D 45
	return (hpuxstat1(uap->fname, uap->hsb, NOFOLLOW));
E 45
I 45
	return (hpuxstat1(uap->fname, uap->hsb, NOFOLLOW, p));
E 45
E 9
E 7
}

I 42
struct hpuxfstat_args {
	int	fdes;
	struct	hpuxstat *hsb;
};
E 42
D 7
hpuxfstat()
{
	register struct file *fp;
	register struct a {
E 7
I 7
hpuxfstat(p, uap, retval)
	struct proc *p;
D 42
	register struct args {
E 7
		int	fdes;
		struct	hpuxstat *hsb;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
E 42
I 42
	register struct hpuxfstat_args *uap;
E 42
	int *retval;
{
I 12
	register struct filedesc *fdp = p->p_fd;
E 12
	register struct file *fp;
E 7
	struct stat sb;
I 7
	int error;
E 7

D 12
	if ((unsigned)uap->fdes >= NOFILE ||
D 7
	    (fp = u.u_ofile[uap->fdes]) == NULL) {
		u.u_error = EBADF;
		return;
	}
E 7
I 7
	    (fp = u.u_ofile[uap->fdes]) == NULL)
E 12
I 12
D 13
	if (((unsigned)uap->fdes) >= fdp->fd_maxfiles ||
	    (fp = OFILE(fdp, uap->fdes)) == NULL)
E 13
I 13
	if (((unsigned)uap->fdes) >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[uap->fdes]) == NULL)
E 13
E 12
D 9
		RETURN (EBADF);
E 9
I 9
		return (EBADF);
E 9

E 7
	switch (fp->f_type) {

	case DTYPE_VNODE:
D 7
		u.u_error = vn_stat((struct vnode *)fp->f_data, &sb);
E 7
I 7
D 45
		error = vn_stat((struct vnode *)fp->f_data, &sb);
E 45
I 45
		error = vn_stat((struct vnode *)fp->f_data, &sb, p);
E 45
E 7
		break;

	case DTYPE_SOCKET:
D 7
		u.u_error = soo_stat((struct socket *)fp->f_data, &sb);
E 7
I 7
D 45
		error = soo_stat((struct socket *)fp->f_data, &sb);
E 45
I 45
		error = soo_stat((struct socket *)fp->f_data, &sb, p);
E 45
E 7
		break;

	default:
		panic("fstat");
		/*NOTREACHED*/
	}
	/* is this right for sockets?? */
D 7
	if (u.u_error == 0)
		u.u_error = bsdtohpuxstat(&sb, uap->hsb);
E 7
I 7
	if (error == 0)
		error = bsdtohpuxstat(&sb, uap->hsb);
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

I 42
struct hpuxulimit_args {
	int	cmd;
	long	newlimit;
};
E 42
D 7
hpuxulimit()
{
	struct a {
E 7
I 7
hpuxulimit(p, uap, retval)
	struct proc *p;
D 42
	register struct args {
E 7
		int	cmd;
		long	newlimit;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
E 42
I 42
	register struct hpuxulimit_args *uap;
E 42
D 8
	int *retval;
E 8
I 8
D 19
	off_t *retval;
E 19
I 19
	long *retval;
E 19
E 8
{
E 7
	struct rlimit *limp;
I 7
	int error = 0;
E 7

D 13
	limp = &u.u_rlimit[RLIMIT_FSIZE];
E 13
I 13
	limp = &p->p_rlimit[RLIMIT_FSIZE];
E 13
	switch (uap->cmd) {
	case 2:
		uap->newlimit *= 512;
		if (uap->newlimit > limp->rlim_max &&
D 7
		    (u.u_error = suser(u.u_cred, &u.u_acflag)))
E 7
I 7
D 13
		    (error = suser(u.u_cred, &u.u_acflag)))
E 13
I 13
		    (error = suser(p->p_ucred, &p->p_acflag)))
E 13
E 7
			break;
		limp->rlim_cur = limp->rlim_max = uap->newlimit;
		/* else fall into... */

	case 1:
D 7
		u.u_r.r_off = limp->rlim_max / 512;
E 7
I 7
D 8
		u.u_r.r_off = limp->rlim_max / 512;		/* XXX */
E 8
I 8
D 10
		*retval = limp->rlim_max / 512;		/* XXX */
E 10
I 10
		*retval = limp->rlim_max / 512;
E 10
E 8
E 7
		break;

	case 3:
D 13
		limp = &u.u_rlimit[RLIMIT_DATA];
D 7
		u.u_r.r_off = ctob(u.u_tsize) + limp->rlim_max;
E 7
I 7
D 8
		u.u_r.r_off = ctob(u.u_tsize) + limp->rlim_max;	/* XXX */
E 8
I 8
D 10
		*retval = ctob(u.u_tsize) + limp->rlim_max;	/* XXX */
E 10
I 10
		*retval = ctob(u.u_tsize) + limp->rlim_max;
E 13
I 13
		limp = &p->p_rlimit[RLIMIT_DATA];
		*retval = ctob(p->p_vmspace->vm_tsize) + limp->rlim_max;
E 13
E 10
E 8
E 7
		break;

	default:
D 7
		u.u_error = EINVAL;
E 7
I 7
		error = EINVAL;
E 7
		break;
	}
I 7
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

/*
 * Map "real time" priorities 0 (high) thru 127 (low) into nice
 * values -16 (high) thru -1 (low).
 */
I 42
struct hpuxrtprio_args {
	int pid;
	int prio;
};
E 42
D 7
hpuxrtprio()
{
	register struct a {
E 7
I 7
hpuxrtprio(cp, uap, retval)
	struct proc *cp;
D 42
	register struct args {
E 7
		int pid;
		int prio;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
E 42
I 42
	register struct hpuxrtprio_args *uap;
E 42
	int *retval;
{
E 7
	struct proc *p;
D 7
	int nice;
E 7
I 7
	int nice, error;
E 7

	if (uap->prio < RTPRIO_MIN && uap->prio > RTPRIO_MAX &&
D 7
	    uap->prio != RTPRIO_NOCHG && uap->prio != RTPRIO_RTOFF) {
		u.u_error = EINVAL;
		return;
	}
E 7
I 7
	    uap->prio != RTPRIO_NOCHG && uap->prio != RTPRIO_RTOFF)
D 9
		RETURN (EINVAL);
E 9
I 9
		return (EINVAL);
E 9
E 7
	if (uap->pid == 0)
D 7
		p = u.u_procp;
	else if ((p = pfind(uap->pid)) == 0) {
		u.u_error = ESRCH;
		return;
	}
E 7
I 7
		p = cp;
	else if ((p = pfind(uap->pid)) == 0)
D 9
		RETURN (ESRCH);
E 9
I 9
		return (ESRCH);
E 9
E 7
	nice = p->p_nice;
	if (nice < NZERO)
D 7
		u.u_r.r_val1 = (nice + 16) << 3;
E 7
I 7
		*retval = (nice + 16) << 3;
E 7
	else
D 7
		u.u_r.r_val1 = RTPRIO_RTOFF;
E 7
I 7
		*retval = RTPRIO_RTOFF;
E 7
	switch (uap->prio) {

	case RTPRIO_NOCHG:
D 7
		return;
E 7
I 7
D 9
		RETURN (0);
E 9
I 9
		return (0);
E 9
E 7

	case RTPRIO_RTOFF:
		if (nice >= NZERO)
D 7
			return;
E 7
I 7
D 9
			RETURN (0);
E 9
I 9
			return (0);
E 9
E 7
		nice = NZERO;
		break;

	default:
		nice = (uap->prio >> 3) - 16;
		break;
	}
D 7
	donice(p, nice);
	if (u.u_error == EACCES)
		u.u_error = EPERM;
E 7
I 7
	error = donice(cp, p, nice);
	if (error == EACCES)
		error = EPERM;
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

I 42
struct hpuxadvise_args {
	int	arg;
};
E 42
D 7
/*
 * Kudos to HP folks for using such mnemonic names so I could figure
 * out what this guy does.
 */
hpuxadvise()
{
	struct a {
E 7
I 7
hpuxadvise(p, uap, retval)
	struct proc *p;
D 42
	struct args {
E 7
		int	arg;
D 7
	} *uap = (struct a *) u.u_ap;
E 7
I 7
	} *uap;
E 42
I 42
	struct hpuxadvise_args *uap;
E 42
	int *retval;
{
	int error = 0;
E 7

	switch (uap->arg) {
	case 0:
D 14
		u.u_pcb.pcb_flags |= PCB_HPUXMMAP;
E 14
I 14
D 48
		p->p_addr->u_pcb.pcb_flags |= PCB_HPUXMMAP;
E 48
I 48
		p->p_md.md_flags |= MDP_HPUXMMAP;
E 48
E 14
		break;
	case 1:
		ICIA();
		break;
	case 2:
		DCIA();
		break;
	default:
D 7
		u.u_error = EINVAL;
E 7
I 7
		error = EINVAL;
E 7
		break;
	}
I 7
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

I 42
struct hpuxptrace_args {
	int	req;
	int	pid;
	int	*addr;
	int	data;
};
E 42
D 7
hpuxptrace()
{
	struct a {
E 7
I 7
hpuxptrace(p, uap, retval)
	struct proc *p;
D 42
	struct args {
E 7
		int	req;
		int	pid;
		int	*addr;
		int	data;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
E 42
I 42
	struct hpuxptrace_args *uap;
E 42
	int *retval;
{
D 48
	int error;
E 48
I 48
	int error, isps = 0;
	struct proc *cp;
E 48
E 7

D 48
	if (uap->req == PT_STEP || uap->req == PT_CONTINUE) {
E 48
I 48
	switch (uap->req) {
	/* map signal */
	case PT_STEP:
	case PT_CONTINUE:
E 48
		if (uap->data) {
			uap->data = hpuxtobsdsig(uap->data);
			if (uap->data == 0)
				uap->data = NSIG;
		}
I 48
		break;
	/* map u-area offset */
	case PT_READ_U:
	case PT_WRITE_U:
		/*
		 * Big, cheezy hack: hpuxtobsduoff is really intended
		 * to be called in the child context (procxmt) but we
		 * do it here in the parent context to avoid hacks in
		 * the MI sys_process.c file.  This works only because
		 * we can access the child's md_regs pointer and it
		 * has the correct value (the child has already trapped
		 * into the kernel).
		 */
		if ((cp = pfind(uap->pid)) == 0)
			return (ESRCH);
		uap->addr = (int *) hpuxtobsduoff(uap->addr, &isps, cp);

		/*
		 * Since HP-UX PS is only 16-bits in ar0, requests
		 * to write PS actually contain the PS in the high word
		 * and the high half of the PC (the following register)
		 * in the low word.  Move the PS value to where BSD
		 * expects it.
		 */
		if (isps && uap->req == PT_WRITE_U)
			uap->data >>= 16;
		break;
E 48
	}
D 7
	ptrace();
E 7
I 7
	error = ptrace(p, uap, retval);
I 48
	/*
	 * Align PS as HP-UX expects it (see WRITE_U comment above).
	 * Note that we do not return the high part of PC like HP-UX
	 * would, but the HP-UX debuggers don't require it.
	 */
	if (isps && error == 0 && uap->req == PT_READ_U)
		*retval <<= 16;
E 48
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

I 42
struct hpuxgetdomainname_args {
	char	*domainname;
	u_int	len;
};
E 42
D 7
hpuxgetdomainname()
{
	register struct a {
E 7
I 7
hpuxgetdomainname(p, uap, retval)
	struct proc *p;
D 42
	register struct args {
E 7
		char	*domainname;
		u_int	len;
D 7
	} *uap = (struct a *)u.u_ap;

E 7
I 7
	} *uap;
E 42
I 42
	register struct hpuxgetdomainname_args *uap;
E 42
	int *retval;
{
E 7
	if (uap->len > domainnamelen + 1)
		uap->len = domainnamelen + 1;
D 7
	u.u_error = copyout(domainname, uap->domainname, uap->len);
E 7
I 7
D 9
	RETURN (copyout(domainname, uap->domainname, uap->len));
E 9
I 9
	return (copyout(domainname, uap->domainname, uap->len));
E 9
E 7
}

I 42
struct hpuxsetdomainname_args {
	char	*domainname;
	u_int	len;
};
E 42
D 7
hpuxsetdomainname()
{
	register struct a {
E 7
I 7
hpuxsetdomainname(p, uap, retval)
	struct proc *p;
D 42
	register struct args {
E 7
		char	*domainname;
		u_int	len;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
E 42
I 42
	register struct hpuxsetdomainname_args *uap;
E 42
	int *retval;
{
	int error;
E 7

D 7
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
		return;
	if (uap->len > sizeof (domainname) - 1) {
		u.u_error = EINVAL;
		return;
	}
E 7
I 7
D 13
	if (error = suser(u.u_cred, &u.u_acflag))
E 13
I 13
	if (error = suser(p->p_ucred, &p->p_acflag))
E 13
D 9
		RETURN (error);
E 9
I 9
		return (error);
E 9
	if (uap->len > sizeof (domainname) - 1)
D 9
		RETURN (EINVAL);
E 9
I 9
		return (EINVAL);
E 9
E 7
	domainnamelen = uap->len;
D 7
	u.u_error = copyin(uap->domainname, domainname, uap->len);
E 7
I 7
	error = copyin(uap->domainname, domainname, uap->len);
E 7
	domainname[domainnamelen] = 0;
I 7
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

#ifdef SYSVSHM
I 39
D 47
#include "shm.h"
E 47
I 47
#include <sys/shm.h>
E 47

E 39
D 7
hpuxshmat()
E 7
I 7
hpuxshmat(p, uap, retval)
	struct proc *p;
	int *uap, *retval;
E 7
{
D 7
	shmat(u.u_ap);
E 7
I 7
D 9
	RETURN (shmat(p, uap, retval));
E 9
I 9
	return (shmat(p, uap, retval));
E 9
E 7
}

D 7
hpuxshmctl()
E 7
I 7
D 39
hpuxshmctl(p, uap, retval)
	struct proc *p;
	int *uap, *retval;
E 7
{
D 7
	shmctl(u.u_ap);
E 7
I 7
D 9
	RETURN (shmctl(p, uap, retval));
E 9
I 9
	return (shmctl(p, uap, retval));
E 9
E 7
}

E 39
D 7
hpuxshmdt()
E 7
I 7
hpuxshmdt(p, uap, retval)
	struct proc *p;
	int *uap, *retval;
E 7
{
D 7
	shmdt(u.u_ap);
E 7
I 7
D 9
	RETURN (shmdt(p, uap, retval));
E 9
I 9
	return (shmdt(p, uap, retval));
E 9
E 7
}

D 7
hpuxshmget()
E 7
I 7
hpuxshmget(p, uap, retval)
	struct proc *p;
	int *uap, *retval;
E 7
{
D 7
	shmget(u.u_ap);
E 7
I 7
D 9
	RETURN (shmget(p, uap, retval));
E 9
I 9
	return (shmget(p, uap, retval));
E 9
E 7
}
I 39

I 56
hpuxshmctl(p, uap, retval)
	struct proc *p;
	int *uap, *retval;
{
	return (hpuxshmctl1(p, uap, retval, 0));
}

hpuxnshmctl(p, uap, retval)
	struct proc *p;
	int *uap, *retval;
{
	return (hpuxshmctl1(p, uap, retval, 1));
}

E 56
/*
 * Handle HP-UX specific commands.
 */
I 42
struct hpuxshmctl_args {
	int shmid;
	int cmd;
	caddr_t buf;
};
E 42
D 56
hpuxshmctl(p, uap, retval)
E 56
I 56
hpuxshmctl1(p, uap, retval, isnew)
E 56
	struct proc *p;
D 42
	struct args {
		int shmid;
		int cmd;
		caddr_t buf;
	} *uap;
E 42
I 42
	struct hpuxshmctl_args *uap;
E 42
	int *retval;
I 56
	int isnew;
E 56
{
	register struct shmid_ds *shp;
	register struct ucred *cred = p->p_ucred;
I 56
	struct hpuxshmid_ds sbuf;
E 56
	int error;

	if (error = shmvalid(uap->shmid))
		return (error);
	shp = &shmsegs[uap->shmid % SHMMMNI];
D 56
	if (uap->cmd == SHM_LOCK || uap->cmd == SHM_UNLOCK) {
E 56
I 56
	switch (uap->cmd) {
	case SHM_LOCK:
	case SHM_UNLOCK:
E 56
		/* don't really do anything, but make them think we did */
		if (cred->cr_uid && cred->cr_uid != shp->shm_perm.uid &&
		    cred->cr_uid != shp->shm_perm.cuid)
			return (EPERM);
		return (0);
I 56

	case IPC_STAT:
		if (!isnew)
			break;
		error = ipcaccess(&shp->shm_perm, IPC_R, cred);
		if (error == 0) {
			sbuf.shm_perm.uid = shp->shm_perm.uid;
			sbuf.shm_perm.gid = shp->shm_perm.gid;
			sbuf.shm_perm.cuid = shp->shm_perm.cuid;
			sbuf.shm_perm.cgid = shp->shm_perm.cgid;
			sbuf.shm_perm.mode = shp->shm_perm.mode;
			sbuf.shm_perm.seq = shp->shm_perm.seq;
			sbuf.shm_perm.key = shp->shm_perm.key;
			sbuf.shm_segsz = shp->shm_segsz;
			sbuf.shm_ptbl = shp->shm_handle;	/* XXX */
			sbuf.shm_lpid = shp->shm_lpid;
			sbuf.shm_cpid = shp->shm_cpid;
			sbuf.shm_nattch = shp->shm_nattch;
			sbuf.shm_cnattch = shp->shm_nattch;	/* XXX */
			sbuf.shm_atime = shp->shm_atime;
			sbuf.shm_dtime = shp->shm_dtime;
			sbuf.shm_ctime = shp->shm_ctime;
			error = copyout((caddr_t)&sbuf, uap->buf, sizeof sbuf);
		}
		return (error);

	case IPC_SET:
		if (!isnew)
			break;
		if (cred->cr_uid && cred->cr_uid != shp->shm_perm.uid &&
		    cred->cr_uid != shp->shm_perm.cuid) {
			return (EPERM);
		}
		error = copyin(uap->buf, (caddr_t)&sbuf, sizeof sbuf);
		if (error == 0) {
			shp->shm_perm.uid = sbuf.shm_perm.uid;
			shp->shm_perm.gid = sbuf.shm_perm.gid;
			shp->shm_perm.mode = (shp->shm_perm.mode & ~0777)
				| (sbuf.shm_perm.mode & 0777);
			shp->shm_ctime = time.tv_sec;
		}
		return (error);
E 56
	}
	return (shmctl(p, uap, retval));
}
E 39
#endif

/*
 * Fake semaphore routines, just don't return an error.
 * Should be adequate for starbase to run.
 */
I 42
struct hpuxsemctl_args {
	int semid;
	u_int semnum;
	int cmd;
	int arg;
};
E 42
D 7
hpuxsemctl()
{
	struct a {
E 7
I 7
hpuxsemctl(p, uap, retval)
	struct proc *p;
D 42
	struct args {
E 7
		int semid;
		u_int semnum;
		int cmd;
		int arg;
D 7
	} *uap = (struct a *)u.u_ap;

E 7
I 7
	} *uap;
E 42
I 42
	struct hpuxsemctl_args *uap;
E 42
	int *retval;
{
E 7
	/* XXX: should do something here */
I 7
D 9
	RETURN (0);
E 9
I 9
	return (0);
E 9
E 7
}

I 42
struct hpuxsemget_args {
	key_t key;
	int nsems;
	int semflg;
};
E 42
D 7
hpuxsemget()
{
	struct a {
E 7
I 7
hpuxsemget(p, uap, retval)
	struct proc *p;
D 42
	struct args {
E 7
		key_t key;
		int nsems;
		int semflg;
D 7
	} *uap = (struct a *)u.u_ap;

E 7
I 7
	} *uap;
E 42
I 42
	struct hpuxsemget_args *uap;
E 42
	int *retval;
{
E 7
	/* XXX: should do something here */
I 7
D 9
	RETURN (0);
E 9
I 9
	return (0);
E 9
E 7
}

I 42
struct hpuxsemop_args {
	int semid;
	struct sembuf *sops;
	u_int nsops;
};
E 42
D 7
hpuxsemop()
{
	struct a {
E 7
I 7
hpuxsemop(p, uap, retval)
	struct proc *p;
D 42
	struct args {
E 7
		int semid;
		struct sembuf *sops;
		u_int nsops;
D 7
	} *uap = (struct a *)u.u_ap;

E 7
I 7
	} *uap;
E 42
I 42
	struct hpuxsemop_args *uap;
E 42
	int *retval;
{
E 7
	/* XXX: should do something here */
I 7
D 9
	RETURN (0);
E 9
I 9
	return (0);
E 9
E 7
}

I 48
/*
 * HP-UX mmap() emulation (mainly for shared library support).
 */
struct hpuxmmap_args {
	caddr_t	addr;
	int	len;
	int	prot;
	int	flags;
	int	fd;
	long	pos;
};
hpuxmmap(p, uap, retval)
	struct proc *p;
	struct hpuxmmap_args *uap;
	int *retval;
{
	struct mmap_args {
		caddr_t	addr;
		int	len;
		int	prot;
		int	flags;
		int	fd;
		long	pad;
		off_t	pos;
	} nargs;

	nargs.addr = uap->addr;
	nargs.len = uap->len;
	nargs.prot = uap->prot;
	nargs.flags = uap->flags &
		~(HPUXMAP_FIXED|HPUXMAP_REPLACE|HPUXMAP_ANON);
	if (uap->flags & HPUXMAP_FIXED)
		nargs.flags |= MAP_FIXED;
	if (uap->flags & HPUXMAP_ANON)
		nargs.flags |= MAP_ANON;
	nargs.fd = (nargs.flags & MAP_ANON) ? -1 : uap->fd;
	nargs.pos = uap->pos;
D 52
	return (smmap(p, &nargs, retval));
E 52
I 52
	return (mmap(p, &nargs, retval));
E 52
}

E 48
D 39
/* convert from BSD to HPUX errno */
E 39
I 39
/* convert from BSD to HP-UX errno */
E 39
bsdtohpuxerrno(err)
	int err;
{
	if (err < 0 || err >= NERR)
		return(BERR);
	return((int)bsdtohpuxerrnomap[err]);
}

D 45
hpuxstat1(fname, hsb, follow)
E 45
I 45
hpuxstat1(fname, hsb, follow, p)
E 45
	char *fname;
	struct hpuxstat *hsb;
	int follow;
I 45
	struct proc *p;
E 45
{
D 13
	register struct nameidata *ndp = &u.u_nd;
	struct stat sb;
E 13
I 13
D 17
	register struct nameidata *ndp;
E 17
E 13
	int error;
I 13
	struct stat sb;
	struct nameidata nd;
E 13

I 13
D 17
	ndp = &nd;
E 13
	ndp->ni_nameiop = LOOKUP | LOCKLEAF | follow;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = fname;
D 13
	if (error = namei(ndp))
E 13
I 13
	if (error = namei(ndp, curproc))
E 17
I 17
D 45
	NDINIT(&nd, LOOKUP, follow | LOCKLEAF, UIO_USERSPACE, fname, curproc);
E 45
I 45
	NDINIT(&nd, LOOKUP, follow | LOCKLEAF, UIO_USERSPACE, fname, p);
E 45
	if (error = namei(&nd))
E 17
E 13
		return (error);
D 17
	error = vn_stat(ndp->ni_vp, &sb);
	vput(ndp->ni_vp);
E 17
I 17
D 45
	error = vn_stat(nd.ni_vp, &sb);
E 45
I 45
	error = vn_stat(nd.ni_vp, &sb, p);
E 45
	vput(nd.ni_vp);
E 17
	if (error == 0)
		error = bsdtohpuxstat(&sb, hsb);
	return (error);
}

#include "grf.h"
I 35
#if NGRF > 0
#ifdef __STDC__
extern int grfopen(dev_t dev, int oflags, int devtype, struct proc *p);
#else
extern int grfopen();
#endif
#endif
E 35

I 35
#define	NHIL	1	/* XXX */
#if NHIL > 0
#ifdef __STDC__
extern int hilopen(dev_t dev, int oflags, int devtype, struct proc *p);
#else
extern int hilopen();
#endif
#endif

D 47
#include "conf.h"
E 47
I 47
#include <sys/conf.h>
E 47

E 35
bsdtohpuxstat(sb, hsb)
	struct stat *sb;
	struct hpuxstat *hsb;
{
	struct hpuxstat ds;

	bzero((caddr_t)&ds, sizeof(ds));
D 19
	ds.hst_dev = sb->st_dev;
E 19
I 19
	ds.hst_dev = (u_short)sb->st_dev;
E 19
	ds.hst_ino = (u_long)sb->st_ino;
	ds.hst_mode = sb->st_mode;
	ds.hst_nlink = sb->st_nlink;
	ds.hst_uid = (u_short)sb->st_uid;
	ds.hst_gid = (u_short)sb->st_gid;
I 48
	ds.hst_rdev = bsdtohpuxdev(sb->st_rdev);

E 48
D 35
#if NGRF > 0
E 35
	/* XXX: I don't want to talk about it... */
D 35
	if ((sb->st_mode & S_IFMT) == S_IFCHR && major(sb->st_rdev) == 10)
		ds.hst_rdev = grfdevno(sb->st_rdev);
	else
E 35
I 35
	if ((sb->st_mode & S_IFMT) == S_IFCHR) {
#if NGRF > 0
		if (cdevsw[major(sb->st_rdev)].d_open == grfopen)
			ds.hst_rdev = grfdevno(sb->st_rdev);
E 35
#endif
I 35
#if NHIL > 0
		if (cdevsw[major(sb->st_rdev)].d_open == hilopen)
			ds.hst_rdev = hildevno(sb->st_rdev);
#endif
		;
D 48
	} else
E 35
		ds.hst_rdev = bsdtohpuxdev(sb->st_rdev);
E 48
I 48
	}
E 48
D 19
	ds.hst_size = sb->st_size;
E 19
I 19
	if (sb->st_size < (quad_t)1 << 32)
		ds.hst_size = (long)sb->st_size;
	else
		ds.hst_size = -2;
E 19
	ds.hst_atime = sb->st_atime;
	ds.hst_mtime = sb->st_mtime;
	ds.hst_ctime = sb->st_ctime;
	ds.hst_blksize = sb->st_blksize;
	ds.hst_blocks = sb->st_blocks;
	return(copyout((caddr_t)&ds, (caddr_t)hsb, sizeof(ds)));
}

hpuxtobsdioctl(com)
	int com;
{
	switch (com) {
	case HPUXTIOCSLTC:
		com = TIOCSLTC; break;
	case HPUXTIOCGLTC:
		com = TIOCGLTC; break;
	case HPUXTIOCSPGRP:
		com = TIOCSPGRP; break;
	case HPUXTIOCGPGRP:
		com = TIOCGPGRP; break;
	case HPUXTIOCLBIS:
		com = TIOCLBIS; break;
	case HPUXTIOCLBIC:
		com = TIOCLBIC; break;
	case HPUXTIOCLSET:
		com = TIOCLSET; break;
	case HPUXTIOCLGET:
		com = TIOCLGET; break;
I 56
	case HPUXTIOCGWINSZ:
		com = TIOCGWINSZ; break;
	case HPUXTIOCSWINSZ:
		com = TIOCSWINSZ; break;
E 56
	}
	return(com);
}

/*
D 39
 * HPUX ioctl system call.  The differences here are:
E 39
I 39
 * HP-UX ioctl system call.  The differences here are:
E 39
 *	IOC_IN also means IOC_VOID if the size portion is zero.
D 15
 *	no FIOCLEX/FIONCLEX/FIONBIO/FIOASYNC/FIOGETOWN/FIOSETOWN
E 15
I 15
 *	no FIOCLEX/FIONCLEX/FIOASYNC/FIOGETOWN/FIOSETOWN
E 15
 *	the sgttyb struct is 2 bytes longer
 */
I 42
struct hpuxioctl_args {
	int	fdes;
	int	cmd;
	caddr_t	cmarg;
};
E 42
D 7
hpuxioctl()
{
	register struct file *fp;
	struct a {
E 7
I 7
hpuxioctl(p, uap, retval)
	struct proc *p;
D 42
	register struct args {
E 7
		int	fdes;
		int	cmd;
		caddr_t	cmarg;
D 7
	} *uap = (struct a *)u.u_ap;
	register int com;
E 7
I 7
	} *uap;
E 42
I 42
	register struct hpuxioctl_args *uap;
E 42
	int *retval;
{
I 12
	register struct filedesc *fdp = p->p_fd;
E 12
	register struct file *fp;
	register int com, error;
E 7
	register u_int size;
	caddr_t memp = 0;
#define STK_PARAMS	128
	char stkbuf[STK_PARAMS];
	caddr_t data = stkbuf;

	com = uap->cmd;

	/* XXX */
D 7
	if (com == HPUXTIOCGETP || com == HPUXTIOCSETP) {
		getsettty(uap->fdes, com, uap->cmarg);
		return;
	}
E 7
I 7
	if (com == HPUXTIOCGETP || com == HPUXTIOCSETP)
D 9
		RETURN (getsettty(uap->fdes, com, uap->cmarg));
E 9
I 9
D 12
		return (getsettty(uap->fdes, com, uap->cmarg));
E 12
I 12
		return (getsettty(p, uap->fdes, com, uap->cmarg));
E 12
E 9
E 7

D 12
	if ((unsigned)uap->fdes >= NOFILE ||
D 7
	    (fp = u.u_ofile[uap->fdes]) == NULL) {
		u.u_error = EBADF;
		return;
	}
	if ((fp->f_flag & (FREAD|FWRITE)) == 0) {
		u.u_error = EBADF;
		return;
	}
E 7
I 7
	    (fp = u.u_ofile[uap->fdes]) == NULL)
E 12
I 12
D 13
	if (((unsigned)uap->fdes) >= fdp->fd_maxfiles ||
	    (fp = OFILE(fdp, uap->fdes)) == NULL)
E 13
I 13
	if (((unsigned)uap->fdes) >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[uap->fdes]) == NULL)
E 13
E 12
D 9
		RETURN (EBADF);
E 9
I 9
		return (EBADF);
E 9
	if ((fp->f_flag & (FREAD|FWRITE)) == 0)
D 9
		RETURN (EBADF);
E 9
I 9
		return (EBADF);
E 9
E 7

	/*
	 * Interpret high order word to find
	 * amount of data to be copied to/from the
	 * user's address space.
	 */
	size = IOCPARM_LEN(com);
D 7
	if (size > IOCPARM_MAX) {
		u.u_error = EFAULT;
		return;
	}
E 7
I 7
	if (size > IOCPARM_MAX)
D 9
		RETURN (ENOTTY);
E 9
I 9
		return (ENOTTY);
E 9
E 7
	if (size > sizeof (stkbuf)) {
D 7
		memp = (caddr_t)malloc((u_long)IOCPARM_MAX, M_IOCTLOPS,
		    M_WAITOK);
E 7
I 7
		memp = (caddr_t)malloc((u_long)size, M_IOCTLOPS, M_WAITOK);
E 7
		data = memp;
	}
	if (com&IOC_IN) {
		if (size) {
D 7
			u.u_error = copyin(uap->cmarg, data, (u_int)size);
			if (u.u_error) {
E 7
I 7
			error = copyin(uap->cmarg, data, (u_int)size);
			if (error) {
E 7
				if (memp)
					free(memp, M_IOCTLOPS);
D 7
				return;
E 7
I 7
D 9
				RETURN (error);
E 9
I 9
				return (error);
E 9
E 7
			}
		} else
			*(caddr_t *)data = uap->cmarg;
	} else if ((com&IOC_OUT) && size)
		/*
D 7
		 * Zero the buffer on the stack so the user
		 * always gets back something deterministic.
E 7
I 7
		 * Zero the buffer so the user always
		 * gets back something deterministic.
E 7
		 */
		bzero(data, size);
	else if (com&IOC_VOID)
		*(caddr_t *)data = uap->cmarg;

	switch (com) {
I 15

	case HPUXFIOSNBIO:
	{
		char *ofp = &fdp->fd_ofileflags[uap->fdes];
		int tmp;

		if (*(int *)data)
			*ofp |= UF_FIONBIO_ON;
		else
			*ofp &= ~UF_FIONBIO_ON;
		/*
D 16
		 * Only set/clear if FNDELAY not in effect
E 16
I 16
D 54
		 * Only set/clear if FNONBLOCK not in effect
E 54
I 54
		 * Only set/clear if O_NONBLOCK/FNDELAY not in effect
E 54
E 16
		 */
D 54
		if ((*ofp & UF_FNDELAY_ON) == 0) {
D 16
			if (tmp = (fp->f_flag & FNDELAY))
				fp->f_flag |= FNDELAY;
			else
				fp->f_flag &= ~FNDELAY;
E 16
I 16
			tmp = fp->f_flag & FNONBLOCK;
E 54
I 54
		if ((*ofp & (UF_NONBLOCK_ON|UF_FNDELAY_ON)) == 0) {
			tmp = *ofp & UF_FIONBIO_ON;
E 54
E 16
			error = (*fp->f_ops->fo_ioctl)(fp, FIONBIO,
						       (caddr_t)&tmp, p);
		}
		break;
	}
E 15

	case HPUXTIOCCONS:
		*(int *)data = 1;
D 7
		u.u_error = (*fp->f_ops->fo_ioctl)(fp, TIOCCONS, data);
E 7
I 7
D 13
		error = (*fp->f_ops->fo_ioctl)(fp, TIOCCONS, data);
E 13
I 13
		error = (*fp->f_ops->fo_ioctl)(fp, TIOCCONS, data, p);
E 13
E 7
		break;

	/* BSD-style job control ioctls */
	case HPUXTIOCLBIS:
	case HPUXTIOCLBIC:
	case HPUXTIOCLSET:
		*(int *)data &= HPUXLTOSTOP;
		if (*(int *)data & HPUXLTOSTOP)
			*(int *)data = LTOSTOP;
		/* fall into */
I 56

	/* simple mapping cases */
E 56
	case HPUXTIOCLGET:
	case HPUXTIOCSLTC:
	case HPUXTIOCGLTC:
	case HPUXTIOCSPGRP:
	case HPUXTIOCGPGRP:
I 56
	case HPUXTIOCGWINSZ:
	case HPUXTIOCSWINSZ:
E 56
D 7
		u.u_error = (*fp->f_ops->fo_ioctl)(fp, hpuxtobsdioctl(com), data);
		if (u.u_error == 0 && com == HPUXTIOCLGET) {
E 7
I 7
D 13
		error = (*fp->f_ops->fo_ioctl)(fp, hpuxtobsdioctl(com), data);
E 13
I 13
		error = (*fp->f_ops->fo_ioctl)
			(fp, hpuxtobsdioctl(com), data, p);
E 13
		if (error == 0 && com == HPUXTIOCLGET) {
E 7
			*(int *)data &= LTOSTOP;
			if (*(int *)data & LTOSTOP)
				*(int *)data = HPUXLTOSTOP;
		}
		break;

D 46
	/* SYS 5 termio */
E 46
I 46
	/* SYS 5 termio and POSIX termios */
E 46
	case HPUXTCGETA:
	case HPUXTCSETA:
	case HPUXTCSETAW:
	case HPUXTCSETAF:
I 46
	case HPUXTCGETATTR:
	case HPUXTCSETATTR:
	case HPUXTCSETATTRD:
	case HPUXTCSETATTRF:
E 46
D 7
		u.u_error = hpuxtermio(fp, com, data);
E 7
I 7
D 13
		error = hpuxtermio(fp, com, data);
E 13
I 13
D 56
		error = hpuxtermio(fp, com, data, p);
E 56
I 56
		error = hpuxtermio(uap->fdes, com, data, p);
E 56
E 13
E 7
		break;

	default:
D 7
		u.u_error = (*fp->f_ops->fo_ioctl)(fp, com, data);
E 7
I 7
D 13
		error = (*fp->f_ops->fo_ioctl)(fp, com, data);
E 13
I 13
		error = (*fp->f_ops->fo_ioctl)(fp, com, data, p);
E 13
E 7
		break;
	}
	/*
	 * Copy any data to user, size was
	 * already set and checked above.
	 */
D 7
	if (u.u_error == 0 && (com&IOC_OUT) && size)
		u.u_error = copyout(data, uap->cmarg, (u_int)size);
E 7
I 7
	if (error == 0 && (com&IOC_OUT) && size)
		error = copyout(data, uap->cmarg, (u_int)size);
E 7
	if (memp)
		free(memp, M_IOCTLOPS);
I 7
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

/*
 * Man page lies, behaviour here is based on observed behaviour.
 */
I 42
struct hpuxgetcontext_args {
	char *buf;
	int len;
};
E 42
D 7
hpuxgetcontext()
{
	struct a {
E 7
I 7
hpuxgetcontext(p, uap, retval)
	struct proc *p;
D 42
	struct args {
E 7
		char *buf;
		int len;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
E 42
I 42
	struct hpuxgetcontext_args *uap;
E 42
	int *retval;
{
E 7
	int error = 0;
	register int len;

I 35
#if defined(HP380)
	if (machineid == HP_380) {
D 43
		len = MIN(uap->len, sizeof(hpux040context));
E 43
I 43
		len = min(uap->len, sizeof(hpux040context));
E 43
		if (len)
			error = copyout(hpux040context, uap->buf, len);
		if (error == 0)
			*retval = sizeof(hpux040context);
		return (error);
	}
#endif
E 35
D 43
	len = MIN(uap->len, sizeof(hpuxcontext));
E 43
I 43
	len = min(uap->len, sizeof(hpuxcontext));
E 43
	if (len)
		error = copyout(hpuxcontext, uap->buf, (u_int)len);
D 7
	if (!error)
		u.u_r.r_val1 = sizeof(hpuxcontext);
	return(error);
E 7
I 7
	if (error == 0)
		*retval = sizeof(hpuxcontext);
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

/*
D 10
 * XXX: simple recognition hack to see if we can make grmd work.
 */
D 7
hpuxlockf()
{
	struct a {
E 7
I 7
hpuxlockf(p, uap, retval)
	struct proc *p;
	struct args {
E 7
		int fd;
		int func;
		long size;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
	int *retval;
{
E 7
#ifdef DEBUG
	log(LOG_DEBUG, "%d: lockf(%d, %d, %d)\n",
D 7
	    u.u_procp->p_pid, uap->fd, uap->func, uap->size);
E 7
I 7
	    p->p_pid, uap->fd, uap->func, uap->size);
E 7
#endif
D 7
	return(0);
E 7
I 7
D 9
	RETURN (0);
E 9
I 9
	return (0);
E 9
E 7
}

/*
E 10
 * This is the equivalent of BSD getpgrp but with more restrictions.
 * Note we do not check the real uid or "saved" uid.
 */
I 42
struct hpuxgetpgrp2_args {
	int pid;
};
E 42
D 7
hpuxgetpgrp2()
E 7
I 7
hpuxgetpgrp2(cp, uap, retval)
	struct proc *cp;
D 42
	register struct args {
		int pid;
	} *uap;
E 42
I 42
	register struct hpuxgetpgrp2_args *uap;
E 42
	int *retval;
E 7
{
	register struct proc *p;
D 7
	register struct a {
		int pid;
	} *uap = (struct a *)u.u_ap;
E 7

	if (uap->pid == 0)
D 7
		uap->pid = u.u_procp->p_pid;
E 7
I 7
		uap->pid = cp->p_pid;
E 7
	p = pfind(uap->pid);
D 7
	if (p == 0) {
		u.u_error = ESRCH;
		return;
	}
	if (u.u_uid && p->p_uid != u.u_uid && !inferior(p)) {
		u.u_error = EPERM;
		return;
	}
	u.u_r.r_val1 = p->p_pgid;
E 7
I 7
	if (p == 0)
D 9
		RETURN (ESRCH);
E 9
I 9
		return (ESRCH);
E 9
D 13
	if (u.u_uid && p->p_uid != u.u_uid && !inferior(p))
E 13
I 13
	if (cp->p_ucred->cr_uid && p->p_ucred->cr_uid != cp->p_ucred->cr_uid &&
	    !inferior(p))
E 13
D 9
		RETURN (EPERM);
E 9
I 9
		return (EPERM);
E 9
	*retval = p->p_pgid;
D 9
	RETURN (0);
E 9
I 9
	return (0);
E 9
E 7
}

/*
 * This is the equivalent of BSD setpgrp but with more restrictions.
 * Note we do not check the real uid or "saved" uid or pgrp.
 */
I 42
struct hpuxsetpgrp2_args {
	int	pid;
	int	pgrp;
};
E 42
D 7
hpuxsetpgrp2()
{
	struct a {
E 7
I 7
hpuxsetpgrp2(p, uap, retval)
	struct proc *p;
D 42
	struct args {
E 7
		int	pid;
		int	pgrp;
D 7
	} *uap = (struct a *)u.u_ap;

E 7
I 7
	} *uap;
E 42
I 42
	struct hpuxsetpgrp2_args *uap;
E 42
	int *retval;
{
E 7
	/* empirically determined */
D 7
	if (uap->pgrp < 0 || uap->pgrp >= 30000) {
		u.u_error = EINVAL;
		return;
	}
	setpgrp();
E 7
I 7
	if (uap->pgrp < 0 || uap->pgrp >= 30000)
D 9
		RETURN (EINVAL);
	RETURN (setpgrp(p, uap, retval));
E 9
I 9
		return (EINVAL);
D 13
	return (setpgrp(p, uap, retval));
E 13
I 13
	return (setpgid(p, uap, retval));
E 13
E 9
E 7
}

/*
I 10
D 40
 * XXX Same as BSD setre[ug]id right now.  Need to consider saved ids.
E 40
I 40
 * XXX Same as old BSD setre[ug]id right now.  Need to consider saved ids.
E 40
 */
I 42
struct hpuxsetresuid_args {
	int	ruid;
	int	euid;
	int	suid;
};
E 42
I 40
/* ARGSUSED */
E 40
hpuxsetresuid(p, uap, retval)
D 40
	struct proc *p;
E 40
I 40
	register struct proc *p;
E 40
D 42
	struct args {
		int	ruid;
		int	euid;
		int	suid;
	} *uap;
E 42
I 42
	struct hpuxsetresuid_args *uap;
E 42
	int *retval;
{
D 40
D 59
	return (osetreuid(p, uap, retval));
E 59
I 59
	return (compat_43_setreuid(p, uap, retval));
E 59
E 40
I 40
	register struct pcred *pc = p->p_cred;
	register uid_t ruid, euid;
	int error;

	if (uap->ruid == -1)
		ruid = pc->p_ruid;
	else
		ruid = uap->ruid;
	/*
	 * Allow setting real uid to previous effective, for swapping real and
	 * effective.  This should be:
	 *
	 * if (ruid != pc->p_ruid &&
	 *     (error = suser(pc->pc_ucred, &p->p_acflag)))
	 */
	if (ruid != pc->p_ruid && ruid != pc->pc_ucred->cr_uid /* XXX */ &&
	    (error = suser(pc->pc_ucred, &p->p_acflag)))
		return (error);
	if (uap->euid == -1)
		euid = pc->pc_ucred->cr_uid;
	else
		euid = uap->euid;
	if (euid != pc->pc_ucred->cr_uid && euid != pc->p_ruid &&
	    euid != pc->p_svuid && (error = suser(pc->pc_ucred, &p->p_acflag)))
		return (error);
	/*
	 * Everything's okay, do it.  Copy credentials so other references do
	 * not see our changes.
	 */
	pc->pc_ucred = crcopy(pc->pc_ucred);
	pc->pc_ucred->cr_uid = euid;
	pc->p_ruid = ruid;
	p->p_flag |= SUGID;
	return (0);
E 40
}

I 42
struct hpuxsetresgid_args {
	int	rgid;
	int	egid;
	int	sgid;
};
E 42
I 40
/* ARGSUSED */
E 40
hpuxsetresgid(p, uap, retval)
D 40
	struct proc *p;
E 40
I 40
	register struct proc *p;
E 40
D 42
	struct args {
		int	rgid;
		int	egid;
		int	sgid;
	} *uap;
E 42
I 42
	struct hpuxsetresgid_args *uap;
E 42
	int *retval;
{
D 40
D 59
	return (osetregid(p, uap, retval));
E 59
I 59
	return (compat_43_setregid(p, uap, retval));
E 59
E 40
I 40
	register struct pcred *pc = p->p_cred;
	register gid_t rgid, egid;
	int error;

	if (uap->rgid == -1)
		rgid = pc->p_rgid;
	else
		rgid = uap->rgid;
	/*
	 * Allow setting real gid to previous effective, for swapping real and
	 * effective.  This didn't really work correctly in 4.[23], but is
	 * preserved so old stuff doesn't fail.  This should be:
	 *
	 * if (rgid != pc->p_rgid &&
	 *     (error = suser(pc->pc_ucred, &p->p_acflag)))
	 */
	if (rgid != pc->p_rgid && rgid != pc->pc_ucred->cr_groups[0] /* XXX */ &&
	    (error = suser(pc->pc_ucred, &p->p_acflag)))
		return (error);
	if (uap->egid == -1)
		egid = pc->pc_ucred->cr_groups[0];
	else
		egid = uap->egid;
	if (egid != pc->pc_ucred->cr_groups[0] && egid != pc->p_rgid &&
	    egid != pc->p_svgid && (error = suser(pc->pc_ucred, &p->p_acflag)))
		return (error);
	pc->pc_ucred = crcopy(pc->pc_ucred);
	pc->pc_ucred->cr_groups[0] = egid;
	pc->p_rgid = rgid;
	p->p_flag |= SUGID;
	return (0);
E 40
}

I 48
struct hpuxrlimit_args {
	u_int	which;
	struct	orlimit *rlp;
};
hpuxgetrlimit(p, uap, retval)
	struct proc *p;
	struct hpuxrlimit_args *uap;
	int *retval;
{
	if (uap->which > HPUXRLIMIT_NOFILE)
		return (EINVAL);
	if (uap->which == HPUXRLIMIT_NOFILE)
		uap->which = RLIMIT_NOFILE;
D 50
	return (getrlimit(p, uap, retval));
E 50
I 50
D 59
	return (ogetrlimit(p, uap, retval));
E 59
I 59
	return (compat_43_getrlimit(p, uap, retval));
E 59
E 50
}

hpuxsetrlimit(p, uap, retval)
	struct proc *p;
	struct hpuxrlimit_args *uap;
	int *retval;
{
	if (uap->which > HPUXRLIMIT_NOFILE)
		return (EINVAL);
	if (uap->which == HPUXRLIMIT_NOFILE)
		uap->which = RLIMIT_NOFILE;
D 50
	return (setrlimit(p, uap, retval));
E 50
I 50
D 59
	return (osetrlimit(p, uap, retval));
E 59
I 59
	return (compat_43_setrlimit(p, uap, retval));
E 59
E 50
}

E 48
/*
 * XXX: simple recognition hack to see if we can make grmd work.
 */
I 42
struct hpuxlockf_args {
	int fd;
	int func;
	long size;
};
E 42
hpuxlockf(p, uap, retval)
	struct proc *p;
D 42
	struct args {
		int fd;
		int func;
		long size;
	} *uap;
E 42
I 42
	struct hpuxlockf_args *uap;
E 42
	int *retval;
{
D 46
#ifdef DEBUG
	log(LOG_DEBUG, "%d: lockf(%d, %d, %d)\n",
	    p->p_pid, uap->fd, uap->func, uap->size);
#endif
E 46
	return (0);
}

I 42
struct hpuxgetaccess_args {
	char	*path;
	int	uid;
	int	ngroups;
	int	*gidset;
	void	*label;
	void	*privs;
};
E 42
hpuxgetaccess(p, uap, retval)
	register struct proc *p;
D 42
	register struct args {
		char	*path;
		int	uid;
		int	ngroups;
		int	*gidset;
		void	*label;
		void	*privs;
	} *uap;
E 42
I 42
	register struct hpuxgetaccess_args *uap;
E 42
	int *retval;
{
I 34
D 37
	USES_VOP_ACCESS;
E 37
E 34
D 13
	struct nameidata *ndp = &u.u_nd;
E 13
I 13
D 17
	struct nameidata *ndp;
E 17
E 13
	int lgroups[NGROUPS];
	int error = 0;
	register struct ucred *cred;
	register struct vnode *vp;
I 17
	struct nameidata nd;
E 17

	/*
	 * Build an appropriate credential structure
	 */
D 13
	cred = crdup(ndp->ni_cred);
E 13
I 13
	cred = crdup(p->p_ucred);
E 13
	switch (uap->uid) {
	case 65502:	/* UID_EUID */
		break;
	case 65503:	/* UID_RUID */
D 13
		cred->cr_uid = p->p_ruid;
E 13
I 13
		cred->cr_uid = p->p_cred->p_ruid;
E 13
		break;
	case 65504:	/* UID_SUID */
		error = EINVAL;
		break;
	default:
		if (uap->uid > 65504)
			error = EINVAL;
		cred->cr_uid = uap->uid;
		break;
	}
	switch (uap->ngroups) {
	case -1:	/* NGROUPS_EGID */
		cred->cr_ngroups = 1;
		break;
	case -5:	/* NGROUPS_EGID_SUPP */
		break;
	case -2:	/* NGROUPS_RGID */
		cred->cr_ngroups = 1;
D 13
		cred->cr_gid = p->p_rgid;
E 13
I 13
		cred->cr_gid = p->p_cred->p_rgid;
E 13
		break;
	case -6:	/* NGROUPS_RGID_SUPP */
D 13
		cred->cr_gid = p->p_rgid;
E 13
I 13
		cred->cr_gid = p->p_cred->p_rgid;
E 13
		break;
	case -3:	/* NGROUPS_SGID */
	case -7:	/* NGROUPS_SGID_SUPP */
		error = EINVAL;
		break;
	case -4:	/* NGROUPS_SUPP */
		if (cred->cr_ngroups > 1)
			cred->cr_gid = cred->cr_groups[1];
		else
			error = EINVAL;
		break;
	default:
		if (uap->ngroups > 0 && uap->ngroups <= NGROUPS)
			error = copyin((caddr_t)uap->gidset,
				       (caddr_t)&lgroups[0],
				       uap->ngroups * sizeof(lgroups[0]));
		else
			error = EINVAL;
		if (error == 0) {
			int gid;

			for (gid = 0; gid < uap->ngroups; gid++)
				cred->cr_groups[gid] = lgroups[gid];
			cred->cr_ngroups = uap->ngroups;
		}
		break;
	}
	/*
	 * Lookup file using caller's effective IDs.
	 */
	if (error == 0) {
D 17
		ndp->ni_nameiop = LOOKUP | FOLLOW | LOCKLEAF;
		ndp->ni_segflg = UIO_USERSPACE;
		ndp->ni_dirp = uap->path;
D 13
		error = namei(ndp);
E 13
I 13
		error = namei(ndp, p);
E 17
I 17
		NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE,
			uap->path, p);
		error = namei(&nd);
E 17
E 13
	}
	if (error) {
		crfree(cred);
		return (error);
	}
	/*
	 * Use the constructed credentials for access checks.
	 */
D 17
	vp = ndp->ni_vp;
E 17
I 17
	vp = nd.ni_vp;
E 17
	*retval = 0;
D 13
	if (VOP_ACCESS(vp, VREAD, cred) == 0)
E 13
I 13
	if (VOP_ACCESS(vp, VREAD, cred, p) == 0)
E 13
		*retval |= R_OK;
D 13
	if (vn_writechk(vp) == 0 && VOP_ACCESS(vp, VWRITE, cred) == 0)
E 13
I 13
	if (vn_writechk(vp) == 0 && VOP_ACCESS(vp, VWRITE, cred, p) == 0)
E 13
		*retval |= W_OK;
	/* XXX we return X_OK for root on VREG even if not */
D 13
	if (VOP_ACCESS(vp, VEXEC, cred) == 0)
E 13
I 13
	if (VOP_ACCESS(vp, VEXEC, cred, p) == 0)
E 13
		*retval |= X_OK;
	vput(vp);
	crfree(cred);
	return (error);
}

D 48
/*
E 10
D 39
 * Brutal hack!  Map HPUX u-area offsets into BSD u offsets.
E 39
I 39
 * Brutal hack!  Map HP-UX u-area offsets into BSD u offsets.
E 39
 * No apologies offered, if you don't like it, rewrite it!
 */

E 48
I 14
extern char kstack[];
E 14
#define UOFF(f)		((int)&((struct user *)0)->f)
#define HPUOFF(f)	((int)&((struct hpuxuser *)0)->f)

/* simplified FP structure */
struct bsdfp {
	int save[54];
	int reg[24];
	int ctrl[3];
};

D 48
hpuxtobsduoff(off)
	int *off;
E 48
I 48
/*
 * Brutal hack!  Map HP-UX u-area offsets into BSD k-stack offsets.
 */
hpuxtobsduoff(off, isps, p)
	int *off, *isps;
	struct proc *p;
E 48
{
I 13
D 18
	register int *ar0 = curproc->p_regs;
E 18
I 18
D 48
	register int *ar0 = curproc->p_md.md_regs;
E 48
I 48
	register int *ar0 = p->p_md.md_regs;
E 48
E 18
E 13
	struct hpuxfp *hp;
	struct bsdfp *bp;
	register u_int raddr;

I 48
	*isps = 0;

E 48
D 13
	/* u_ar0 field */
E 13
I 13
	/* u_ar0 field; procxmt puts in U_ar0 */
E 13
	if ((int)off == HPUOFF(hpuxu_ar0))
D 13
		return(UOFF(u_ar0));
E 13
I 13
		return(UOFF(U_ar0));
E 13

#ifdef FPCOPROC
D 48
	/* 68881 registers from PCB */
E 48
I 48
	/* FP registers from PCB */
E 48
	hp = (struct hpuxfp *)HPUOFF(hpuxu_fp);
	bp = (struct bsdfp *)UOFF(u_pcb.pcb_fpregs);
	if (off >= hp->hpfp_ctrl && off < &hp->hpfp_ctrl[3])
		return((int)&bp->ctrl[off - hp->hpfp_ctrl]);
	if (off >= hp->hpfp_reg && off < &hp->hpfp_reg[24])
		return((int)&bp->reg[off - hp->hpfp_reg]);
#endif

	/*
	 * Everything else we recognize comes from the kernel stack,
	 * so we convert off to an absolute address (if not already)
	 * for simplicity.
	 */
	if (off < (int *)ctob(UPAGES))
D 14
		off = (int *)((u_int)off + (u_int)&u);
E 14
I 14
		off = (int *)((u_int)off + (u_int)kstack);
E 14

	/*
D 48
	 * 68020 registers.
E 48
I 48
	 * General registers.
E 48
D 39
	 * We know that the HPUX registers are in the same order as ours.
E 39
I 39
	 * We know that the HP-UX registers are in the same order as ours.
E 39
	 * The only difference is that their PS is 2 bytes instead of a
	 * padded 4 like ours throwing the alignment off.
	 */
D 13
	if (off >= u.u_ar0 && off < &u.u_ar0[18]) {
E 13
I 13
	if (off >= ar0 && off < &ar0[18]) {
E 13
		/*
		 * PS: return low word and high word of PC as HP-UX would
		 * (e.g. &u.u_ar0[16.5]).
I 48
		 *
		 * XXX we don't do this since HP-UX adb doesn't rely on
		 * it and passing such an offset to procxmt will cause
		 * it to fail anyway.  Instead, we just set the offset
		 * to PS and let hpuxptrace() shift up the value returned.
E 48
		 */
D 13
		if (off == &u.u_ar0[PS])
			raddr = (u_int) &((short *)u.u_ar0)[PS*2+1];
E 13
I 13
D 48
		if (off == &ar0[PS])
E 48
I 48
		if (off == &ar0[PS]) {
#if 0
E 48
			raddr = (u_int) &((short *)ar0)[PS*2+1];
I 48
#else
			raddr = (u_int) &ar0[(int)(off - ar0)];
#endif
			*isps = 1;
		}
E 48
E 13
		/*
D 48
		 * PC: off will be &u.u_ar0[16.5]
E 48
I 48
		 * PC: off will be &u.u_ar0[16.5] since HP-UX saved PS
		 * is only 16 bits.
E 48
		 */
D 13
		else if (off == (int *)&(((short *)u.u_ar0)[PS*2+1]))
			raddr = (u_int) &u.u_ar0[PC];
E 13
I 13
		else if (off == (int *)&(((short *)ar0)[PS*2+1]))
			raddr = (u_int) &ar0[PC];
E 13
		/*
		 * D0-D7, A0-A7: easy
		 */
		else
D 13
			raddr = (u_int) &u.u_ar0[(int)(off - u.u_ar0)];
E 13
I 13
			raddr = (u_int) &ar0[(int)(off - ar0)];
E 13
D 14
		return((int)(raddr - (u_int)&u));
E 14
I 14
		return((int)(raddr - (u_int)kstack));
E 14
	}

	/* everything else */
	return(-1);
}

/*
D 39
 * Kludge up a uarea dump so that HPUX debuggers can find out
E 39
I 39
 * Kludge up a uarea dump so that HP-UX debuggers can find out
E 39
 * what they need.  IMPORTANT NOTE: we do not EVEN attempt to
 * convert the entire user struct.
 */
hpuxdumpu(vp, cred)
	struct vnode *vp;
	struct ucred *cred;
{
I 13
	struct proc *p = curproc;
E 13
	int error;
	struct hpuxuser *faku;
	struct bsdfp *bp;
	short *foop;

	faku = (struct hpuxuser *)malloc((u_long)ctob(1), M_TEMP, M_WAITOK);
	/*
	 * Make sure there is no mistake about this
	 * being a real user structure.
	 */
	bzero((caddr_t)faku, ctob(1));
	/*
	 * Fill in the process sizes.
	 */
D 13
	faku->hpuxu_tsize = u.u_tsize;
	faku->hpuxu_dsize = u.u_dsize;
	faku->hpuxu_ssize = u.u_ssize;
E 13
I 13
	faku->hpuxu_tsize = p->p_vmspace->vm_tsize;
	faku->hpuxu_dsize = p->p_vmspace->vm_dsize;
	faku->hpuxu_ssize = p->p_vmspace->vm_ssize;
E 13
	/*
	 * Fill in the exec header for CDB.
	 * This was saved back in exec().  As far as I can tell CDB
	 * only uses this information to verify that a particular
	 * core file goes with a particular binary.
	 */
D 14
	bcopy((caddr_t)u.u_pcb.pcb_exec,
E 14
I 14
D 48
	bcopy((caddr_t)p->p_addr->u_pcb.pcb_exec,
E 48
I 48
	bcopy((caddr_t)p->p_addr->u_md.md_exec,
E 48
E 14
	      (caddr_t)&faku->hpuxu_exdata, sizeof (struct hpux_exec));
	/*
	 * Adjust user's saved registers (on kernel stack) to reflect
D 39
	 * HPUX order.  Note that HPUX saves the SR as 2 bytes not 4
E 39
I 39
	 * HP-UX order.  Note that HP-UX saves the SR as 2 bytes not 4
E 39
	 * so we have to move it up.
	 */
D 13
	faku->hpuxu_ar0 = u.u_ar0;
	foop = (short *) u.u_ar0;
E 13
I 13
D 18
	faku->hpuxu_ar0 = p->p_regs;
	foop = (short *) p->p_regs;
E 18
I 18
	faku->hpuxu_ar0 = p->p_md.md_regs;
	foop = (short *) p->p_md.md_regs;
E 18
E 13
	foop[32] = foop[33];
	foop[33] = foop[34];
	foop[34] = foop[35];
#ifdef FPCOPROC
	/*
D 39
	 * Copy 68881 registers from our PCB format to HPUX format
E 39
I 39
	 * Copy 68881 registers from our PCB format to HP-UX format
E 39
	 */
D 14
	bp = (struct bsdfp *) &u.u_pcb.pcb_fpregs;
E 14
I 14
	bp = (struct bsdfp *) &p->p_addr->u_pcb.pcb_fpregs;
E 14
	bcopy((caddr_t)bp->save, (caddr_t)faku->hpuxu_fp.hpfp_save,
	      sizeof(bp->save));
	bcopy((caddr_t)bp->ctrl, (caddr_t)faku->hpuxu_fp.hpfp_ctrl,
	      sizeof(bp->ctrl));
	bcopy((caddr_t)bp->reg, (caddr_t)faku->hpuxu_fp.hpfp_reg,
	      sizeof(bp->reg));
#endif
	/*
	 * Slay the dragon
	 */
	faku->hpuxu_dragon = -1;
	/*
	 * Dump this artfully constructed page in place of the
	 * user struct page.
	 */
D 13
	error = vn_rdwr(UIO_WRITE, vp,
			(caddr_t)faku, ctob(1), (off_t)0,
			UIO_SYSSPACE, IO_NODELOCKED|IO_UNIT, cred, (int *)0);
E 13
I 13
	error = vn_rdwr(UIO_WRITE, vp, (caddr_t)faku, ctob(1), (off_t)0,
			UIO_SYSSPACE, IO_NODELOCKED|IO_UNIT, cred,
D 14
			(int *)0, (struct proc *)0);
E 14
I 14
			(int *)NULL, p);
E 14
E 13
	/*
	 * Dump the remaining UPAGES-1 pages normally
	 */
	if (!error) 
D 14
		error = vn_rdwr(UIO_WRITE, vp, ((caddr_t)&u)+ctob(1),
E 14
I 14
		error = vn_rdwr(UIO_WRITE, vp, kstack + ctob(1),
E 14
				ctob(UPAGES-1), (off_t)ctob(1), UIO_SYSSPACE,
D 13
				IO_NODELOCKED|IO_UNIT, cred, (int *)0);
E 13
I 13
D 14
				IO_NODELOCKED|IO_UNIT, cred, (int *)0,
				(struct proc *)0);
E 14
I 14
				IO_NODELOCKED|IO_UNIT, cred, (int *)NULL, p);
E 14
E 13
	free((caddr_t)faku, M_TEMP);
	return(error);
}

/*
 * The remaining routines are essentially the same as those in kern_xxx.c
 * and vfs_xxx.c as defined under "#ifdef COMPAT".  We replicate them here
 * to avoid HPUXCOMPAT dependencies in those files and to make sure that
 * HP-UX compatibility still works even when COMPAT is not defined.
I 48
 *
 * These are still needed as of HP-UX 7.05.
E 48
 */
I 46
#ifdef COMPAT_OHPUX

E 46
D 35
/* #ifdef COMPAT */

E 35
I 10
#define HPUX_HZ	50

E 10
D 2
#include "../h/times.h"
E 2
I 2
D 11
#include "../sys/times.h"
E 11
I 11
D 47
#include "sys/times.h"
E 47
I 47
D 48
#include <sys/times.h>
E 48
I 48
#include "sys/times.h"
E 48
E 47
E 11
E 2

/* from old timeb.h */
struct hpuxtimeb {
	time_t	time;
	u_short	millitm;
	short	timezone;
	short	dstflag;
};

/* ye ole stat structure */
struct	ohpuxstat {
D 19
	dev_t	ohst_dev;
E 19
I 19
	u_short	ohst_dev;
E 19
	u_short	ohst_ino;
	u_short ohst_mode;
	short  	ohst_nlink;
	short  	ohst_uid;
	short  	ohst_gid;
D 19
	dev_t	ohst_rdev;
E 19
I 19
	u_short	ohst_rdev;
E 19
	int	ohst_size;
	int	ohst_atime;
	int	ohst_mtime;
	int	ohst_ctime;
};

/*
D 7
 * Right now the following two routines are the same as the 4.3
 * osetuid/osetgid calls.  Eventually they need to be changed to
 * implement the notion of "saved" ids (whatever that means).
 */
ohpuxsetuid()
{
	register uid;
	register struct a {
		int	uid;
	} *uap = (struct a *)u.u_ap;

	uid = uap->uid;
	if (uid != u.u_procp->p_ruid && uid != u.u_cred->cr_uid &&
	    (u.u_error = suser(u.u_cred, &u.u_acflag)))
		return;
	if (u.u_cred->cr_ref > 1)
		u.u_cred = crcopy(u.u_cred);
	u.u_cred->cr_uid = uid;
	u.u_procp->p_uid = uid;
	u.u_procp->p_ruid = uid;
}

ohpuxsetgid()
{
	register gid;
	register struct a {
		int	gid;
	} *uap = (struct a *)u.u_ap;

	gid = uap->gid;
	if (u.u_procp->p_rgid != gid && u.u_cred->cr_groups[0] != gid &&
	    (u.u_error = suser(u.u_cred, &u.u_acflag)))
		return;
	if (u.u_cred->cr_ref > 1)
		u.u_cred = crcopy(u.u_cred);
	u.u_procp->p_rgid = gid;
	u.u_cred->cr_groups[0] = gid;
}

/*
E 7
 * SYS V style setpgrp()
 */
D 7
ohpuxsetpgrp()
E 7
I 7
D 59
ohpuxsetpgrp(p, uap, retval)
E 59
I 59
compat_43_hpuxsetpgrp(p, uap, retval)
E 59
	register struct proc *p;
	int *uap, *retval;
E 7
{
D 7
	register struct proc *p = u.u_procp;

E 7
	if (p->p_pid != p->p_pgid)
D 13
		pgmv(p, p->p_pid, 0);
E 13
I 13
		enterpgrp(p, p->p_pid, 0);
E 13
D 7
	u.u_r.r_val1 = p->p_pgid;
E 7
I 7
	*retval = p->p_pgid;
I 10
	return (0);
E 10
E 7
}

I 42
struct ohpuxtime_args {
	long	*tp;
};
E 42
D 7
ohpuxtime()
{
	register struct a {
E 7
I 7
D 59
ohpuxtime(p, uap, retval)
E 59
I 59
compat_43_hpuxtime(p, uap, retval)
E 59
	struct proc *p;
D 42
	register struct args {
E 7
		long	*tp;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
D 8
	int *retval;
E 8
I 8
	time_t *retval;
E 42
I 42
	register struct ohpuxtime_args *uap;
	int *retval;
E 42
E 8
{
D 10
	int error;
E 10
I 10
	int error = 0;
E 10
E 7

	if (uap->tp)
D 7
		u.u_error = copyout((caddr_t)&time.tv_sec, (caddr_t)uap->tp,
				    sizeof (long));
	u.u_r.r_time = time.tv_sec;
E 7
I 7
		error = copyout((caddr_t)&time.tv_sec, (caddr_t)uap->tp,
				sizeof (long));
D 8
	u.u_r.r_time = time.tv_sec;		/* XXX */
E 8
I 8
D 10
	*retval = time.tv_sec;		/* XXX */
E 10
I 10
D 42
	*retval = time.tv_sec;
E 42
I 42
	*(time_t *)retval = time.tv_sec;
E 42
E 10
E 8
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

I 42
struct ohpuxstime_args {
	int	time;
};
E 42
D 7
ohpuxstime()
{
	register struct a {
E 7
I 7
D 59
ohpuxstime(p, uap, retval)
E 59
I 59
compat_43_hpuxstime(p, uap, retval)
E 59
	struct proc *p;
D 42
	register struct args {
E 7
		int	time;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
E 42
I 42
	register struct ohpuxstime_args *uap;
E 42
	int *retval;
{
E 7
	struct timeval tv;
D 7
	int s;
E 7
I 7
	int s, error;
E 7

	tv.tv_sec = uap->time;
	tv.tv_usec = 0;
D 7
	u.u_error = suser(u.u_cred, &u.u_acflag);
	if (u.u_error)
		return;
E 7
I 7
D 13
	if (error = suser(u.u_cred, &u.u_acflag))
E 13
I 13
	if (error = suser(p->p_ucred, &p->p_acflag))
E 13
D 9
		RETURN (error);
E 9
I 9
		return (error);
E 9
E 7

	/* WHAT DO WE DO ABOUT PENDING REAL-TIME TIMEOUTS??? */
	boottime.tv_sec += tv.tv_sec - time.tv_sec;
	s = splhigh(); time = tv; splx(s);
	resettodr();
I 7
D 9
	RETURN (0);
E 9
I 9
	return (0);
E 9
E 7
}

I 42
struct ohpuxftime_args {
	struct	hpuxtimeb *tp;
};
E 42
D 7
ohpuxftime()
{
	register struct a {
E 7
I 7
D 59
ohpuxftime(p, uap, retval)
E 59
I 59
compat_43_hpuxftime(p, uap, retval)
E 59
	struct proc *p;
D 42
	register struct args {
E 7
		struct	hpuxtimeb *tp;
	} *uap;
E 42
I 42
	register struct ohpuxftime_args *uap;
E 42
I 7
	int *retval;
{
E 7
	struct hpuxtimeb tb;
	int s;

D 7
	uap = (struct a *)u.u_ap;
E 7
	s = splhigh();
	tb.time = time.tv_sec;
	tb.millitm = time.tv_usec / 1000;
	splx(s);
	tb.timezone = tz.tz_minuteswest;
	tb.dstflag = tz.tz_dsttime;
D 7
	u.u_error = copyout((caddr_t)&tb, (caddr_t)uap->tp, sizeof (tb));
E 7
I 7
D 9
	RETURN (copyout((caddr_t)&tb, (caddr_t)uap->tp, sizeof (tb)));
E 9
I 9
	return (copyout((caddr_t)&tb, (caddr_t)uap->tp, sizeof (tb)));
E 9
E 7
}

I 42
struct ohpuxalarm_args {
	int	deltat;
};
E 42
D 7
ohpuxalarm()
{
	register struct a {
E 7
I 7
D 59
ohpuxalarm(p, uap, retval)
E 59
I 59
compat_43_hpuxalarm(p, uap, retval)
E 59
	register struct proc *p;
D 42
	register struct args {
E 7
		int	deltat;
D 7
	} *uap = (struct a *)u.u_ap;
	register struct proc *p = u.u_procp;
E 7
I 7
	} *uap;
E 42
I 42
	register struct ohpuxalarm_args *uap;
E 42
	int *retval;
{
E 7
	int s = splhigh();

	untimeout(realitexpire, (caddr_t)p);
	timerclear(&p->p_realtimer.it_interval);
D 7
	u.u_r.r_val1 = 0;
E 7
I 7
	*retval = 0;
E 7
	if (timerisset(&p->p_realtimer.it_value) &&
	    timercmp(&p->p_realtimer.it_value, &time, >))
D 7
		u.u_r.r_val1 = p->p_realtimer.it_value.tv_sec - time.tv_sec;
E 7
I 7
		*retval = p->p_realtimer.it_value.tv_sec - time.tv_sec;
E 7
	if (uap->deltat == 0) {
		timerclear(&p->p_realtimer.it_value);
		splx(s);
D 7
		return;
E 7
I 7
D 9
		RETURN (0);
E 9
I 9
		return (0);
E 9
E 7
	}
	p->p_realtimer.it_value = time;
	p->p_realtimer.it_value.tv_sec += uap->deltat;
	timeout(realitexpire, (caddr_t)p, hzto(&p->p_realtimer.it_value));
	splx(s);
I 7
D 9
	RETURN (0);
E 9
I 9
	return (0);
E 9
E 7
}

I 42
struct ohpuxnice_args {
	int	niceness;
};
E 42
D 7
ohpuxnice()
{
	register struct a {
E 7
I 7
D 59
ohpuxnice(p, uap, retval)
E 59
I 59
compat_43_hpuxnice(p, uap, retval)
E 59
	register struct proc *p;
D 42
	register struct args {
E 7
		int	niceness;
D 7
	} *uap = (struct a *)u.u_ap;
	register struct proc *p = u.u_procp;
E 7
I 7
	} *uap;
E 42
I 42
	register struct ohpuxnice_args *uap;
E 42
	int *retval;
{
	int error;
E 7

D 7
	donice(p, (p->p_nice-NZERO)+uap->niceness);
	u.u_r.r_val1 = p->p_nice - NZERO;
E 7
I 7
	error = donice(p, p, (p->p_nice-NZERO)+uap->niceness);
	if (error == 0)
		*retval = p->p_nice - NZERO;
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

I 42
struct ohpuxtimes_args {
	struct	tms *tmsb;
};
E 42
D 7
ohpuxtimes()
{
	register struct a {
E 7
I 7
D 59
ohpuxtimes(p, uap, retval)
E 59
I 59
compat_43_hpuxtimes(p, uap, retval)
E 59
	struct proc *p;
D 42
	register struct args {
E 7
		struct	tms *tmsb;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
D 8
	int *retval;
E 8
I 8
	time_t *retval;
E 42
I 42
	register struct ohpuxtimes_args *uap;
	int *retval;
E 42
E 8
{
I 38
	struct timeval ru, rs;
E 38
E 7
	struct tms atms;
I 7
	int error;
E 7

D 10
	atms.tms_utime = scale50(&u.u_ru.ru_utime);
	atms.tms_stime = scale50(&u.u_ru.ru_stime);
	atms.tms_cutime = scale50(&u.u_cru.ru_utime);
	atms.tms_cstime = scale50(&u.u_cru.ru_stime);
E 10
I 10
D 13
	atms.tms_utime = hpuxscale(&u.u_ru.ru_utime);
	atms.tms_stime = hpuxscale(&u.u_ru.ru_stime);
	atms.tms_cutime = hpuxscale(&u.u_cru.ru_utime);
	atms.tms_cstime = hpuxscale(&u.u_cru.ru_stime);
E 13
I 13
D 38
	atms.tms_utime = hpuxscale(&p->p_utime);
	atms.tms_stime = hpuxscale(&p->p_stime);
E 38
I 38
	calcru(p, &ru, &rs, NULL);
	atms.tms_utime = hpuxscale(&ru);
	atms.tms_stime = hpuxscale(&rs);
E 38
	atms.tms_cutime = hpuxscale(&p->p_stats->p_cru.ru_utime);
	atms.tms_cstime = hpuxscale(&p->p_stats->p_cru.ru_stime);
E 13
E 10
D 7
	u.u_error = copyout((caddr_t)&atms, (caddr_t)uap->tmsb, sizeof (atms));
	if (u.u_error == 0)
		u.u_r.r_time = scale50(&time) - scale50(&boottime);
E 7
I 7
	error = copyout((caddr_t)&atms, (caddr_t)uap->tmsb, sizeof (atms));
	if (error == 0)
D 8
		u.u_r.r_time = scale50(&time) - scale50(&boottime); /* XXX */
E 8
I 8
D 10
		*retval = scale50(&time) - scale50(&boottime); /* XXX */
E 10
I 10
D 42
		*retval = hpuxscale(&time) - hpuxscale(&boottime);
E 42
I 42
		*(time_t *)retval = hpuxscale(&time) - hpuxscale(&boottime);
E 42
E 10
E 8
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

D 10
scale50(tvp)
E 10
I 10
/*
 * Doesn't exactly do what the documentation says.
 * What we really do is return 1/HPUX_HZ-th of a second since that
 * is what HP-UX returns.
 */
hpuxscale(tvp)
E 10
	register struct timeval *tvp;
{
D 10
	extern int hpuxtick;

	/*
	 * Doesn't exactly do what the documentation says.
	 * What we really do is return 50th of a second since that
	 * is what HZ is on all bobcats I know of.
	 */
	return ((tvp->tv_sec * 50 + tvp->tv_usec / hpuxtick));
E 10
I 10
	return (tvp->tv_sec * HPUX_HZ + tvp->tv_usec * HPUX_HZ / 1000000);
E 10
}

/*
 * Set IUPD and IACC times on file.
 * Can't set ICHG.
 */
I 42
struct ohpuxutime_args {
	char	*fname;
	time_t	*tptr;
};
E 42
D 7
ohpuxutime()
{
E 7
I 7
D 59
ohpuxutime(p, uap, retval)
E 59
I 59
compat_43_hpuxutime(p, uap, retval)
E 59
	struct proc *p;
E 7
D 42
	register struct a {
		char	*fname;
		time_t	*tptr;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
E 42
I 42
	register struct ohpuxutime_args *uap;
E 42
	int *retval;
{
I 34
D 37
	USES_VOP_SETATTR;
E 37
E 34
I 13
	register struct vnode *vp;
D 17
	register struct nameidata *ndp;
E 17
E 13
E 7
	struct vattr vattr;
	time_t tv[2];
D 13
	register struct vnode *vp;
	register struct nameidata *ndp = &u.u_nd;
E 13
I 7
	int error;
I 13
	struct nameidata nd;
E 13
E 7

I 13
D 17
	ndp = &nd;
E 17
E 13
	if (uap->tptr) {
D 7
		u.u_error =
			copyin((caddr_t)uap->tptr, (caddr_t)tv, sizeof (tv));
		if (u.u_error)
			return;
E 7
I 7
		error = copyin((caddr_t)uap->tptr, (caddr_t)tv, sizeof (tv));
		if (error)
D 9
			RETURN (error);
E 9
I 9
			return (error);
E 9
E 7
	} else
		tv[0] = tv[1] = time.tv_sec;
D 17
	ndp->ni_nameiop = LOOKUP | FOLLOW | LOCKLEAF;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
E 17
	vattr_null(&vattr);
D 36
	vattr.va_atime.tv_sec = tv[0];
	vattr.va_atime.tv_usec = 0;
	vattr.va_mtime.tv_sec = tv[1];
	vattr.va_mtime.tv_usec = 0;
E 36
I 36
	vattr.va_atime.ts_sec = tv[0];
	vattr.va_atime.ts_nsec = 0;
	vattr.va_mtime.ts_sec = tv[1];
	vattr.va_mtime.ts_nsec = 0;
E 36
D 7
	if (u.u_error = namei(ndp))
		return;
E 7
I 7
D 13
	if (error = namei(ndp))
E 13
I 13
D 17
	if (error = namei(ndp, p))
E 17
I 17
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->fname, p);
	if (error = namei(&nd))
E 17
E 13
D 9
		RETURN (error);
E 9
I 9
		return (error);
E 9
E 7
D 17
	vp = ndp->ni_vp;
E 17
I 17
	vp = nd.ni_vp;
E 17
D 3
	if (vp->v_mount->m_flag & M_RDONLY)
E 3
I 3
	if (vp->v_mount->mnt_flag & MNT_RDONLY)
E 3
D 7
		u.u_error = EROFS;
E 7
I 7
		error = EROFS;
E 7
	else
D 7
		u.u_error = VOP_SETATTR(vp, &vattr, ndp->ni_cred);
E 7
I 7
D 13
		error = VOP_SETATTR(vp, &vattr, ndp->ni_cred);
E 13
I 13
D 17
		error = VOP_SETATTR(vp, &vattr, ndp->ni_cred, p);
E 17
I 17
		error = VOP_SETATTR(vp, &vattr, nd.ni_cnd.cn_cred, p);
E 17
E 13
E 7
	vput(vp);
I 7
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

D 7
ohpuxpause()
E 7
I 7
D 59
ohpuxpause(p, uap, retval)
E 59
I 59
compat_43_hpuxpause(p, uap, retval)
E 59
	struct proc *p;
	int *uap, *retval;
E 7
{
D 7

E 7
D 4
	for (;;)
		sleep((caddr_t)&u, PSLEP);
E 4
I 4
D 14
	(void) tsleep((caddr_t)&u, PPAUSE | PCATCH, "pause", 0);
E 14
I 14
	(void) tsleep(kstack, PPAUSE | PCATCH, "pause", 0);
E 14
	/* always return EINTR rather than ERESTART... */
D 9
	RETURN (EINTR);
E 9
I 9
	return (EINTR);
E 9
E 4
}

/*
 * The old fstat system call.
 */
I 42
struct ohpuxfstat_args {
	int	fd;
	struct ohpuxstat *sb;
};
E 42
D 7
ohpuxfstat()
{
	register struct a {
E 7
I 7
D 59
ohpuxfstat(p, uap, retval)
E 59
I 59
compat_43_hpuxfstat(p, uap, retval)
E 59
	struct proc *p;
D 42
	register struct args {
E 7
		int	fd;
		struct ohpuxstat *sb;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
E 42
I 42
	register struct ohpuxfstat_args *uap;
E 42
	int *retval;
{
I 12
	register struct filedesc *fdp = p->p_fd;
E 12
E 7
	struct file *fp;
D 7
	extern struct file *getinode();
E 7

D 7
	if ((unsigned)uap->fd >= NOFILE || (fp = u.u_ofile[uap->fd]) == NULL) {
		u.u_error = EBADF;
		return;
	}
	if (fp->f_type != DTYPE_VNODE) {
		u.u_error = EINVAL;
		return;
	}
	u.u_error = ohpuxstat1((struct vnode *)fp->f_data, uap->sb);
E 7
I 7
D 12
	if ((unsigned)uap->fd >= NOFILE || (fp = u.u_ofile[uap->fd]) == NULL)
E 12
I 12
D 13
	if (((unsigned)uap->fd) >= fdp->fd_maxfiles ||
	    (fp = OFILE(fdp, uap->fd)) == NULL)
E 13
I 13
	if (((unsigned)uap->fd) >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[uap->fd]) == NULL)
E 13
E 12
D 9
		RETURN (EBADF);
E 9
I 9
		return (EBADF);
E 9
	if (fp->f_type != DTYPE_VNODE)
D 9
		RETURN (EINVAL);
	RETURN (ohpuxstat1((struct vnode *)fp->f_data, uap->sb));
E 9
I 9
		return (EINVAL);
D 45
	return (ohpuxstat1((struct vnode *)fp->f_data, uap->sb));
E 45
I 45
D 59
	return (ohpuxstat1((struct vnode *)fp->f_data, uap->sb, p));
E 59
I 59
	return (compat_43_hpuxstat1((struct vnode *)fp->f_data, uap->sb, p));
E 59
E 45
E 9
E 7
}

/*
 * Old stat system call.  This version follows links.
 */
I 42
struct ohpuxstat_args {
	char	*fname;
	struct ohpuxstat *sb;
};
E 42
D 7
ohpuxstat()
{
	register struct a {
E 7
I 7
D 59
ohpuxstat(p, uap, retval)
E 59
I 59
compat_43_hpuxstat(p, uap, retval)
E 59
	struct proc *p;
D 42
	register struct args {
E 7
		char	*fname;
		struct ohpuxstat *sb;
D 7
	} *uap = (struct a *)u.u_ap;
E 7
I 7
	} *uap;
E 42
I 42
	register struct ohpuxstat_args *uap;
E 42
	int *retval;
{
E 7
D 13
	register struct nameidata *ndp = &u.u_nd;
E 13
I 13
D 17
	register struct nameidata *ndp;
E 17
E 13
I 7
	int error;
I 13
	struct nameidata nd;
E 13
E 7

I 13
D 17
	ndp = &nd;
E 13
	ndp->ni_nameiop = LOOKUP | LOCKLEAF | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
D 7
	if (u.u_error = namei(ndp))
		return;
	u.u_error = ohpuxstat1(ndp->ni_vp, uap->sb);
E 7
I 7
D 13
	if (error = namei(ndp))
E 13
I 13
	if (error = namei(ndp, p))
E 17
I 17
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->fname, p);
	if (error = namei(&nd))
E 17
E 13
D 9
		RETURN (error);
E 9
I 9
		return (error);
E 9
D 17
	error = ohpuxstat1(ndp->ni_vp, uap->sb);
E 7
	vput(ndp->ni_vp);
E 17
I 17
D 45
	error = ohpuxstat1(nd.ni_vp, uap->sb);
E 45
I 45
D 59
	error = ohpuxstat1(nd.ni_vp, uap->sb, p);
E 59
I 59
	error = compat_43_hpuxstat1(nd.ni_vp, uap->sb, p);
E 59
E 45
	vput(nd.ni_vp);
E 17
I 7
D 9
	RETURN (error);
E 9
I 9
	return (error);
E 9
E 7
}

int
D 45
ohpuxstat1(vp, ub)
E 45
I 45
D 59
ohpuxstat1(vp, ub, p)
E 59
I 59
compat_43_hpuxstat1(vp, ub, p)
E 59
E 45
D 48
	register struct vnode *vp;
E 48
I 48
	struct vnode *vp;
E 48
	struct ohpuxstat *ub;
I 45
	struct proc *p;
E 45
{
I 34
D 37
	USES_VOP_GETATTR;
E 37
E 34
D 48
	struct ohpuxstat ds;
	struct vattr vattr;
	register int error;
E 48
I 48
	struct ohpuxstat ohsb;
	struct stat sb;
	int error;
E 48

D 13
	error = VOP_GETATTR(vp, &vattr, u.u_cred);
E 13
I 13
D 45
	error = VOP_GETATTR(vp, &vattr, curproc->p_ucred, curproc);
E 45
I 45
D 48
	error = VOP_GETATTR(vp, &vattr, p->p_ucred, p);
E 48
I 48
	error = vn_stat(vp, &sb, p);
E 48
E 45
E 13
	if (error)
D 48
		return(error);
	/*
	 * Copy from inode table
	 */
	ds.ohst_dev = vattr.va_fsid;
	ds.ohst_ino = (short)vattr.va_fileid;
	ds.ohst_mode = (u_short)vattr.va_mode;
	ds.ohst_nlink = vattr.va_nlink;
	ds.ohst_uid = (short)vattr.va_uid;
	ds.ohst_gid = (short)vattr.va_gid;
D 19
	ds.ohst_rdev = (dev_t)vattr.va_rdev;
E 19
I 19
	ds.ohst_rdev = (u_short)vattr.va_rdev;
E 19
	ds.ohst_size = (int)vattr.va_size;
D 36
	ds.ohst_atime = (int)vattr.va_atime.tv_sec;
	ds.ohst_mtime = (int)vattr.va_mtime.tv_sec;
	ds.ohst_ctime = (int)vattr.va_ctime.tv_sec;
E 36
I 36
	ds.ohst_atime = (int)vattr.va_atime.ts_sec;
	ds.ohst_mtime = (int)vattr.va_mtime.ts_sec;
	ds.ohst_ctime = (int)vattr.va_ctime.ts_sec;
E 36
	return (copyout((caddr_t)&ds, (caddr_t)ub, sizeof(ds)));
E 48
I 48
		return (error);

	ohsb.ohst_dev = sb.st_dev;
	ohsb.ohst_ino = sb.st_ino;
	ohsb.ohst_mode = sb.st_mode;
	ohsb.ohst_nlink = sb.st_nlink;
	ohsb.ohst_uid = sb.st_uid;
	ohsb.ohst_gid = sb.st_gid;
	ohsb.ohst_rdev = sb.st_rdev;
	if (sb.st_size < (quad_t)1 << 32)
		ohsb.ohst_size = sb.st_size;
	else
		ohsb.ohst_size = -2;
	ohsb.ohst_atime = sb.st_atime;
	ohsb.ohst_mtime = sb.st_mtime;
	ohsb.ohst_ctime = sb.st_ctime;
	return (copyout((caddr_t)&ohsb, (caddr_t)ub, sizeof(ohsb)));
E 48
}
I 46
#endif
E 46
D 35
/* #endif */

E 35
#endif
E 1
