h52709
s 00002/00002/00316
d D 8.2 95/03/30 11:29:05 mckusick 31 30
c CTL_FS => CTL_VFS
e
s 00002/00002/00316
d D 8.1 93/06/02 19:55:33 bostic 30 29
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00020/00316
d D 7.28 93/05/25 17:14:35 mckusick 29 28
c gone are things that belonged in pathconf
e
s 00001/00005/00335
d D 7.27 93/05/24 15:25:07 bostic 28 27
c per-process limits are resources, not sysctl(3) variables
e
s 00011/00003/00329
d D 7.26 93/05/23 13:39:43 bostic 27 26
c add KERN_MAXUPROC, KERN_MAXUFILES, USER_STREAM_MAX and
c USER_TZNAME_MAX for POSIX 1003.1
e
s 00003/00001/00329
d D 7.25 93/05/20 12:44:33 mckusick 26 25
c add boottime
e
s 00090/00019/00240
d D 7.24 93/05/04 08:59:35 bostic 25 23
c fold rest of POSIX 1003.1, 1003.2 configurable system variables into sysctl
e
s 00003/00001/00258
d R 7.24 93/05/03 17:00:02 bostic 24 23
c add POSIX 1003.2 version
e
s 00003/00003/00256
d D 7.23 93/05/01 13:51:12 mckusick 23 22
c delete hardware speed, add machine byte order
e
s 00009/00005/00250
d D 7.22 93/04/27 14:45:43 bostic 22 21
c protect against multiple inclusion (user.h includes it)
c unbalanced endif's
e
s 00052/00000/00204
d D 7.21 93/04/27 14:33:15 mckusick 21 20
c move in kinfo_proc definition from kinfo_proc.h and retire kinfo_proc.h
e
s 00005/00003/00199
d D 7.20 93/04/27 00:46:47 mckusick 20 19
c add KERN_MAXVNODES
e
s 00007/00005/00195
d D 7.19 93/04/20 17:13:16 mckusick 19 18
c add KERN_PROF
e
s 00033/00000/00167
d D 7.18 93/04/19 00:19:27 mckusick 18 17
c add support for debugging variables
e
s 00051/00034/00116
d D 7.17 93/04/18 00:22:59 mckusick 17 16
c define sysctl types; specify types for sysctl names
e
s 00021/00021/00129
d D 7.16 93/03/04 17:57:51 bostic 16 15
c change buffer lengths of sysctl(2) to be size_t's
c change array size of sysctl(2) to be u_int's
e
s 00002/00001/00148
d D 7.15 93/03/02 18:21:19 mckusick 15 14
c need proc parameter to be passed through
e
s 00009/00007/00140
d D 7.14 93/02/28 23:31:55 mckusick 14 13
c add securelevel
e
s 00115/00049/00032
d D 7.13 93/02/04 01:30:28 mckusick 13 12
c kinfo.h becomes sysctl.h; merged in contribution from BSDI
e
s 00010/00000/00071
d D 7.12 92/02/25 17:18:27 mckusick 12 11
c add stubs for getting load average and clock rate
e
s 00001/00000/00070
d D 7.11 92/02/18 15:36:08 sklower 11 10
c add new kinfo for interface list
e
s 00005/00000/00065
d D 7.10 91/08/28 15:29:44 mckusick 10 9
c add support to get vmtotal structure calculated
e
s 00005/00000/00060
d D 7.9 91/06/26 13:58:53 marc 9 8
c KINFO_FILE
e
s 00001/00001/00059
d D 7.8 91/02/24 16:22:12 bostic 8 7
c getkerninfo takes a void *, not a char *
e
s 00007/00000/00053
d D 7.7 91/02/22 10:19:37 donn 7 6
c Prototype declarations.
e
s 00000/00005/00053
d D 7.6 91/02/08 18:20:10 bostic 6 5
c only kvm.h included kinfo.h, and there wasn't any reason it should
e
s 00005/00001/00053
d D 7.5 91/02/05 17:04:12 bostic 5 4
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00011/00053
d D 7.4 90/06/28 21:58:59 bostic 4 3
c new copyright notice
e
s 00006/00023/00058
d D 7.3 90/06/28 15:23:45 marc 3 2
c 
e
s 00040/00008/00041
d D 7.2 90/02/16 17:06:43 marc 2 1
c checkpoint state of eproc as of fri morning
e
s 00049/00000/00000
d D 7.1 90/02/01 14:32:02 marc 1 0
c date and time created 90/02/01 14:32:02 by marc
e
u
U
t
T
I 1
/*
D 13
 * Copyright (c) 1989 The Regents of the University of California.
E 13
I 13
D 30
 * Copyright (c) 1989, 1993 The Regents of the University of California.
E 13
 * All rights reserved.
E 30
I 30
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 30
 *
I 13
 * This code is derived from software contributed to Berkeley by
 * Mike Karels at Berkeley Software Design, Inc.
 *
E 13
D 4
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */

I 22
#ifndef _SYS_SYSCTL_H_
#define	_SYS_SYSCTL_H_

E 22
I 5
D 6
#ifndef _KINFO_H_
#define	_KINFO_H_

E 6
E 5
/*
I 21
 * These are for the eproc structure defined below.
 */
#ifndef KERNEL
#include <sys/time.h>
#include <sys/ucred.h>
#include <sys/proc.h>
#include <vm/vm.h>
#endif

/*
E 21
D 13
 * Get kernel info
E 13
I 13
D 16
 * Definitions for sysctl call.
 * The sysctl call uses a hierarchical name for objects
 * that can be examined or modified.
 * The name is expressed as a sequence of integers.
 * Like a file path name, the meaning of each component
 * depends on its place in the hierarchy.
 * The top-level and kern identifiers are defined here,
 * and other identifiers are defined in the respective
 * subsystem header files.
E 16
I 16
 * Definitions for sysctl call.  The sysctl call uses a hierarchical name
 * for objects that can be examined or modified.  The name is expressed as
 * a sequence of integers.  Like a file path name, the meaning of each
 * component depends on its place in the hierarchy.  The top-level and kern
 * identifiers are defined here, and other identifiers are defined in the
 * respective subsystem header files.
E 16
E 13
 */
D 5

E 5
D 13
#define ki_op(x)		((x)&0x0000ffff)
#define ki_type(x)		((x)&0x0000ff00)
E 13

D 13
/* 
 * proc info 
 */
#define	KINFO_PROC		(0<<8)
#define KINFO_PROC_ALL	(KINFO_PROC|0)	/* everything */
#define	KINFO_PROC_PID	(KINFO_PROC|1)	/* by process id */
#define	KINFO_PROC_PGRP	(KINFO_PROC|2)	/* by process group id */
#define	KINFO_PROC_SESSION (KINFO_PROC|3)	/* by session of pid */
#define	KINFO_PROC_TTY	(KINFO_PROC|4)	/* by controlling tty */
#define	KINFO_PROC_UID	(KINFO_PROC|5)	/* by effective uid */
#define	KINFO_PROC_RUID	(KINFO_PROC|6)	/* by real uid */
E 13
I 13
#define CTL_MAXNAME	12	/* largest number of components supported */
E 13

D 2
/* proc ops return arrays of these */
E 2
I 2
D 3
/* 
 * proc ops return arrays of augmented proc structures
 */
E 2
struct kinfo_proc {
	struct	proc kp_proc;		/* proc structure */
D 2
	struct	proc *kp_paddr;		/* address of proc */
	struct	session *kp_sess;	/* session pointer */
	pid_t	kp_pgid;		/* process group id */
	short	kp_jobc;		/* job control counter */
	dev_t	kp_tdev;		/* controlling tty */
	pid_t	kp_tpgid;		/* foreground process group id */
	struct	session *kp_tsess;	/* terminal session pointer */
E 2
I 2
	struct	eproc {
		struct	proc *e_paddr;		/* address of proc */
		struct	session *e_sess;	/* session pointer */
		pid_t	e_pgid;		/* process group id */
		short	e_jobc;		/* job control counter */
		dev_t	e_tdev;		/* controlling tty */
		pid_t	e_tpgid;		/* tty process group id */
		struct	session *e_tsess;	/* tty session pointer */
#define	WMESGLEN	7
		char	e_wmesg[WMESGLEN+1];	/* wchan message */
		size_t	e_xsize;		/* text size */
		short	e_xrssize;		/* text rss */
		short	e_xccount;		/* text references */
		short	e_xswrss;
		long	e_spare[8];
	} kp_eproc;
E 2
};
E 3
I 2
/*
I 17
 * Each subsystem defined by sysctl defines a list of variables
 * for that subsystem. Each name is either a node with further 
 * levels defined below it, or it is a leaf of some particular
 * type given below. Each sysctl level defines a set of name/type
 * pairs to be used by sysctl(1) in manipulating the subsystem.
 */
struct ctlname {
	char	*ctl_name;	/* subsystem name */
	int	ctl_type;	/* type of name */
};
#define	CTLTYPE_NODE	1	/* name is a node */
#define	CTLTYPE_INT	2	/* name describes an integer */
#define	CTLTYPE_STRING	3	/* name describes a string */
#define	CTLTYPE_QUAD	4	/* name describes a 64-bit number */
#define	CTLTYPE_STRUCT	5	/* name describes a structure */

/*
E 17
D 13
 * Routing table
E 13
I 13
 * Top-level identifiers
E 13
 */
D 13
#define ki_af(x)		(((x)&0x00ff0000) >> 16)
D 3
#define KINFO_RT	(1<<8)
E 3
I 3
#define KINFO_RT		(1<<8)
E 3
#define KINFO_RT_DUMP	(KINFO_RT|1)	/* dump; may limit to a.f. */
#define KINFO_RT_FLAGS	(KINFO_RT|2)	/* by flags, e.g. RESOLVING */
I 11
#define KINFO_RT_IFLIST (KINFO_RT|3)	/* survey interface list */
E 13
I 13
#define	CTL_UNSPEC	0		/* unused */
#define	CTL_KERN	1		/* "high kernel": proc, limits */
#define	CTL_VM		2		/* virtual memory */
D 31
#define	CTL_FS		3		/* file system, mount type is next */
E 31
I 31
#define	CTL_VFS		3		/* file system, mount type is next */
E 31
#define	CTL_NET		4		/* network, see socket.h */
#define	CTL_DEBUG	5		/* debugging parameters */
#define	CTL_HW		6		/* generic cpu/io */
#define	CTL_MACHDEP	7		/* machine dependent */
D 25
#define	CTL_MAXID	8		/* number of valid top-level ids */
E 25
I 25
#define	CTL_USER	8		/* user-level */
#define	CTL_MAXID	9		/* number of valid top-level ids */
E 25
E 13
E 11
I 3

D 13
/*
 * vnodes
 */
#define	KINFO_VNODE		(2<<8)
E 13
I 13
#define CTL_NAMES { \
D 17
	"unspec", \
	"kern", \
	"vm", \
	"fs", \
	"net", \
	"debug", \
	"hw", \
	"machdep", \
E 17
I 17
	{ 0, 0 }, \
	{ "kern", CTLTYPE_NODE }, \
	{ "vm", CTLTYPE_NODE }, \
D 31
	{ "fs", CTLTYPE_NODE }, \
E 31
I 31
	{ "vfs", CTLTYPE_NODE }, \
E 31
	{ "net", CTLTYPE_NODE }, \
	{ "debug", CTLTYPE_NODE }, \
	{ "hw", CTLTYPE_NODE }, \
	{ "machdep", CTLTYPE_NODE }, \
I 25
	{ "user", CTLTYPE_NODE }, \
E 25
E 17
}
E 13
E 3

/*
I 9
D 13
 * file structures
E 13
I 13
 * CTL_KERN identifiers
E 13
 */
D 13
#define KINFO_FILE		(3<<8)
E 13
I 13
D 25
#define	KERN_OSTYPE	 1		/* string: system version */
#define	KERN_OSRELEASE	 2		/* string: system release */
#define	KERN_OSREV	 3		/* int: system revision */
#define	KERN_VERSION	 4		/* string: compile time info */
D 20
#define	KERN_POSIX1	 5		/* int: POSIX.1 version */
E 20
I 20
#define	KERN_MAXVNODES	 5		/* int: max vnodes */
E 20
#define	KERN_MAXPROC	 6		/* int: max simultaneous processes */
#define	KERN_MAXFILES	 7		/* int: max open files */
#define	KERN_ARGMAX	 8		/* int: max arguments to exec */
D 14
#define	KERN_HOSTNAME	 9		/* string: hostname */
#define	KERN_HOSTID	10		/* int: host identifier */
#define	KERN_CLOCKRATE	11		/* struct clockrate */
#define	KERN_VNODE	12		/* vnode structures */
#define	KERN_PROC	13		/* process entries */
#define	KERN_FILE	14		/* file entries */
#define	KERN_MAXID	15		/* number of valid kern ids */
E 14
I 14
#define	KERN_SECURELVL	 9		/* int: system security level */
#define	KERN_HOSTNAME	10		/* string: hostname */
#define	KERN_HOSTID	11		/* int: host identifier */
D 19
#define	KERN_CLOCKRATE	12		/* struct clockrate */
#define	KERN_VNODE	13		/* vnode structures */
#define	KERN_PROC	14		/* process entries */
#define	KERN_FILE	15		/* file entries */
#define	KERN_MAXID	16		/* number of valid kern ids */
E 19
I 19
#define	KERN_CLOCKRATE	12		/* struct: struct clockrate */
#define	KERN_VNODE	13		/* struct: vnode structures */
#define	KERN_PROC	14		/* struct: process entries */
#define	KERN_FILE	15		/* struct: file entries */
#define	KERN_PROF	16		/* node: kernel profiling info */
D 20
#define	KERN_MAXID	17		/* number of valid kern ids */
E 20
I 20
#define	KERN_POSIX1	17		/* int: POSIX.1 version */
#define	KERN_MAXID	18		/* number of valid kern ids */
E 25
I 25
#define	KERN_OSTYPE	 	 1	/* string: system version */
#define	KERN_OSRELEASE	 	 2	/* string: system release */
#define	KERN_OSREV	 	 3	/* int: system revision */
#define	KERN_VERSION	 	 4	/* string: compile time info */
#define	KERN_MAXVNODES	 	 5	/* int: max vnodes */
D 27
#define	KERN_MAXPROC	 	 6	/* int: max simultaneous processes */
E 27
I 27
#define	KERN_MAXPROC	 	 6	/* int: max processes */
E 27
#define	KERN_MAXFILES	 	 7	/* int: max open files */
#define	KERN_ARGMAX	 	 8	/* int: max arguments to exec */
#define	KERN_SECURELVL	 	 9	/* int: system security level */
#define	KERN_HOSTNAME		10	/* string: hostname */
#define	KERN_HOSTID		11	/* int: host identifier */
#define	KERN_CLOCKRATE		12	/* struct: struct clockrate */
#define	KERN_VNODE		13	/* struct: vnode structures */
#define	KERN_PROC		14	/* struct: process entries */
#define	KERN_FILE		15	/* struct: file entries */
#define	KERN_PROF		16	/* node: kernel profiling info */
#define	KERN_POSIX1		17	/* int: POSIX.1 version */
#define	KERN_NGROUPS		18	/* int: # of supplemental group ids */
#define	KERN_JOB_CONTROL	19	/* int: is job control available */
#define	KERN_SAVED_IDS		20	/* int: saved set-user/group-ID */
D 29
#define	KERN_LINK_MAX		21	/* int: max file link count */
#define	KERN_MAX_CANON		22	/* int: max bytes in term canon input */
#define	KERN_MAX_INPUT		23	/* int: max bytes in term input */
#define	KERN_NAME_MAX		24	/* int: max bytes in file name */
#define	KERN_PATH_MAX		25	/* int: max bytes in pathname */
#define	KERN_PIPE_BUF		26	/* int: max bytes for atomic pipe  */
#define	KERN_CHOWN_RESTRICTED	27	/* int: chown requires privilege */
#define	KERN_NO_TRUNC		28	/* int: no path truncation */
#define	KERN_VDISABLE		29	/* int: terminal character disable */
D 26
#define	KERN_MAXID		30	/* number of valid kern ids */
E 26
I 26
#define	KERN_BOOTTIME		30	/* struct: time kernel was booted */
D 27
#define	KERN_MAXID		31	/* number of valid kern ids */
E 27
I 27
D 28
#define	KERN_MAXUPROC	 	31	/* int: max processes per uid */
#define	KERN_MAXUFILES	 	32	/* int: max open files per uid */
#define	KERN_MAXID		33	/* number of valid kern ids */
E 28
I 28
#define	KERN_MAXID		31	/* number of valid kern ids */
E 29
I 29
#define	KERN_BOOTTIME		21	/* struct: time kernel was booted */
#define	KERN_MAXID		22	/* number of valid kern ids */
E 29
E 28
E 27
E 26
E 25
E 20
E 19
E 14
E 13

D 13
/*
I 10
 * vmtotal structure
 */
#define KINFO_METER		(4<<8)
E 13
I 13
#define CTL_KERN_NAMES { \
D 17
	"unspec", \
	"ostype", \
	"osrelease", \
	"osrevision", \
	"version", \
	"posix1version", \
	"maxproc", \
	"maxfiles", \
	"argmax", \
I 14
	"securelevel", \
E 14
	"hostname", \
	"hostid", \
	"clockrate", \
	"vnode", \
	"proc", \
	"file", \
E 17
I 17
	{ 0, 0 }, \
	{ "ostype", CTLTYPE_STRING }, \
	{ "osrelease", CTLTYPE_STRING }, \
	{ "osrevision", CTLTYPE_INT }, \
	{ "version", CTLTYPE_STRING }, \
D 20
	{ "posix1version", CTLTYPE_INT }, \
E 20
I 20
	{ "maxvnodes", CTLTYPE_INT }, \
E 20
	{ "maxproc", CTLTYPE_INT }, \
	{ "maxfiles", CTLTYPE_INT }, \
	{ "argmax", CTLTYPE_INT }, \
	{ "securelevel", CTLTYPE_INT }, \
	{ "hostname", CTLTYPE_STRING }, \
	{ "hostid", CTLTYPE_INT }, \
	{ "clockrate", CTLTYPE_STRUCT }, \
	{ "vnode", CTLTYPE_STRUCT }, \
	{ "proc", CTLTYPE_STRUCT }, \
	{ "file", CTLTYPE_STRUCT }, \
I 19
	{ "profiling", CTLTYPE_NODE }, \
I 20
	{ "posix1version", CTLTYPE_INT }, \
I 25
	{ "ngroups", CTLTYPE_INT }, \
	{ "job_control", CTLTYPE_INT }, \
	{ "saved_ids", CTLTYPE_INT }, \
D 29
	{ "link_max", CTLTYPE_INT }, \
	{ "max_canon", CTLTYPE_INT }, \
	{ "max_input", CTLTYPE_INT }, \
	{ "name_max", CTLTYPE_INT }, \
	{ "path_max", CTLTYPE_INT }, \
	{ "pipe_buf", CTLTYPE_INT }, \
	{ "chown_restricted", CTLTYPE_INT }, \
	{ "no_trunc", CTLTYPE_INT }, \
	{ "vdisable", CTLTYPE_INT }, \
E 29
I 26
	{ "boottime", CTLTYPE_STRUCT }, \
I 27
D 28
	{ "maxuproc", CTLTYPE_INT }, \
	{ "maxufiles", CTLTYPE_INT }, \
E 28
E 27
E 26
E 25
E 20
E 19
E 17
}
E 13

D 13
/*
I 12
 * load average structure
E 13
I 13
/* 
 * KERN_PROC subtypes
E 13
 */
D 13
#define KINFO_LOADAVG		(5<<8)
E 13
I 13
#define KERN_PROC_ALL		0	/* everything */
#define	KERN_PROC_PID		1	/* by process id */
#define	KERN_PROC_PGRP		2	/* by process group id */
#define	KERN_PROC_SESSION	3	/* by session of pid */
#define	KERN_PROC_TTY		4	/* by controlling tty */
#define	KERN_PROC_UID		5	/* by effective uid */
#define	KERN_PROC_RUID		6	/* by real uid */
E 13

I 21
/* 
 * KERN_PROC subtype ops return arrays of augmented proc structures:
 */
struct kinfo_proc {
	struct	proc kp_proc;			/* proc structure */
	struct	eproc {
		struct	proc *e_paddr;		/* address of proc */
		struct	session *e_sess;	/* session pointer */
		struct	pcred e_pcred;		/* process credentials */
		struct	ucred e_ucred;		/* current credentials */
#ifdef sparc
		struct {
			segsz_t	vm_rssize;	/* resident set size */
			segsz_t	vm_tsize;	/* text size */
			segsz_t	vm_dsize;	/* data size */
			segsz_t	vm_ssize;	/* stack size */
		} e_vm;
#else
		struct	vmspace e_vm;		/* address space */
#endif
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

E 21
/*
D 13
 * clock rate structure
E 13
I 13
 * CTL_HW identifiers
E 13
 */
D 13
#define KINFO_CLOCKRATE		(6<<8)
E 13
I 13
#define	HW_MACHINE	 1		/* string: machine class */
#define	HW_MODEL	 2		/* string: specific machine model */
#define	HW_NCPU		 3		/* int: number of cpus */
D 23
#define	HW_CPUSPEED	 4		/* int: relative cpuspeed */
E 23
I 23
#define	HW_BYTEORDER	 4		/* int: machine byte order */
E 23
#define	HW_PHYSMEM	 5		/* int: total memory */
#define	HW_USERMEM	 6		/* int: non-kernel memory */
#define	HW_PAGESIZE	 7		/* int: software page size */
#define	HW_DISKNAMES	 8		/* strings: disk drive names */
D 23
#define	HW_DISKSTATS	 9		/* diskstats[] */
E 23
I 23
#define	HW_DISKSTATS	 9		/* struct: diskstats[] */
E 23
#define	HW_MAXID	10		/* number of valid hw ids */
E 13

I 13
#define CTL_HW_NAMES { \
D 17
	"unspec", \
	"machine", \
	"model", \
	"ncpu", \
	"cpuspeed", \
	"physmem", \
	"usermem", \
	"pagesize", \
	"disknames", \
	"diskstats", \
E 17
I 17
	{ 0, 0 }, \
	{ "machine", CTLTYPE_STRING }, \
	{ "model", CTLTYPE_STRING }, \
	{ "ncpu", CTLTYPE_INT }, \
D 23
	{ "cpuspeed", CTLTYPE_INT }, \
E 23
I 23
	{ "byteorder", CTLTYPE_INT }, \
E 23
	{ "physmem", CTLTYPE_INT }, \
	{ "usermem", CTLTYPE_INT }, \
	{ "pagesize", CTLTYPE_INT }, \
	{ "disknames", CTLTYPE_STRUCT }, \
	{ "diskstats", CTLTYPE_STRUCT }, \
I 25
}

/*
 * CTL_USER definitions
 */
#define	USER_CS_PATH		 1	/* string: _CS_PATH */
#define	USER_BC_BASE_MAX	 2	/* int: BC_BASE_MAX */
#define	USER_BC_DIM_MAX		 3	/* int: BC_DIM_MAX */
#define	USER_BC_SCALE_MAX	 4	/* int: BC_SCALE_MAX */
#define	USER_BC_STRING_MAX	 5	/* int: BC_STRING_MAX */
#define	USER_COLL_WEIGHTS_MAX	 6	/* int: COLL_WEIGHTS_MAX */
#define	USER_EXPR_NEST_MAX	 7	/* int: EXPR_NEST_MAX */
#define	USER_LINE_MAX		 8	/* int: LINE_MAX */
#define	USER_RE_DUP_MAX		 9	/* int: RE_DUP_MAX */
#define	USER_POSIX2_VERSION	10	/* int: POSIX2_VERSION */
#define	USER_POSIX2_C_BIND	11	/* int: POSIX2_C_BIND */
#define	USER_POSIX2_C_DEV	12	/* int: POSIX2_C_DEV */
#define	USER_POSIX2_CHAR_TERM	13	/* int: POSIX2_CHAR_TERM */
#define	USER_POSIX2_FORT_DEV	14	/* int: POSIX2_FORT_DEV */
#define	USER_POSIX2_FORT_RUN	15	/* int: POSIX2_FORT_RUN */
#define	USER_POSIX2_LOCALEDEF	16	/* int: POSIX2_LOCALEDEF */
#define	USER_POSIX2_SW_DEV	17	/* int: POSIX2_SW_DEV */
#define	USER_POSIX2_UPE		18	/* int: POSIX2_UPE */
D 27
#define	USER_MAXID		19	/* number of valid user ids */
E 27
I 27
#define	USER_STREAM_MAX		19	/* int: POSIX2_STREAM_MAX */
#define	USER_TZNAME_MAX		20	/* int: POSIX2_TZNAME_MAX */
#define	USER_MAXID		21	/* number of valid user ids */
E 27

#define	CTL_USER_NAMES { \
	{ 0, 0 }, \
	{ "cs_path", CTLTYPE_STRING }, \
	{ "bc_base_max", CTLTYPE_INT }, \
	{ "bc_dim_max", CTLTYPE_INT }, \
	{ "bc_scale_max", CTLTYPE_INT }, \
	{ "bc_string_max", CTLTYPE_INT }, \
	{ "coll_weights_max", CTLTYPE_INT }, \
	{ "expr_nest_max", CTLTYPE_INT }, \
	{ "line_max", CTLTYPE_INT }, \
	{ "re_dup_max", CTLTYPE_INT }, \
	{ "posix2_version", CTLTYPE_INT }, \
	{ "posix2_c_bind", CTLTYPE_INT }, \
	{ "posix2_c_dev", CTLTYPE_INT }, \
	{ "posix2_char_term", CTLTYPE_INT }, \
	{ "posix2_fort_dev", CTLTYPE_INT }, \
	{ "posix2_fort_run", CTLTYPE_INT }, \
	{ "posix2_localedef", CTLTYPE_INT }, \
	{ "posix2_sw_dev", CTLTYPE_INT }, \
	{ "posix2_upe", CTLTYPE_INT }, \
I 27
	{ "stream_max", CTLTYPE_INT }, \
	{ "tzname_max", CTLTYPE_INT }, \
E 27
E 25
E 17
}

I 18
/*
 * CTL_DEBUG definitions
 *
 * Second level identifier specifies which debug variable.
 * Third level identifier specifies which stucture component.
 */
#define	CTL_DEBUG_NAME		0	/* string: variable name */
#define	CTL_DEBUG_VALUE		1	/* int: variable value */
#define	CTL_DEBUG_MAXID		20

E 18
D 22
#ifdef KERNEL
I 18
#ifdef DEBUG
E 22
I 22
#ifdef	KERNEL
#ifdef	DEBUG
E 22
/*
 * CTL_DEBUG variables.
 *
 * These are declared as separate variables so that they can be
 * individually initialized at the location of their associated
 * variable. The loader prevents multiple use by issuing errors
 * if a variable is initialized in more than one place. They are
 * aggregated into an array in debug_sysctl(), so that it can
 * conveniently locate them when querried. If more debugging
 * variables are added, they must also be declared here and also
 * entered into the array.
 */
struct ctldebug {
	char	*debugname;	/* name of debugging variable */
	int	*debugvar;	/* pointer to debugging variable */
};
extern struct ctldebug debug0, debug1, debug2, debug3, debug4;
extern struct ctldebug debug5, debug6, debug7, debug8, debug9;
extern struct ctldebug debug10, debug11, debug12, debug13, debug14;
extern struct ctldebug debug15, debug16, debug17, debug18, debug19;
D 22
#endif /* DEBUG */
E 22
I 22
#endif	/* DEBUG */
E 22

E 18
E 13
/*
E 12
E 10
E 9
D 13
 * Locking and stats
E 13
I 13
 * Internal sysctl function calling convention:
I 16
 *
E 16
 *	(*sysctlfn)(name, namelen, oldval, oldlenp, newval, newlen);
D 16
 * The name parameter points at the next component of the name
 * to be interpreted.  The namelen parameter is the number of integers
 * in the name.
E 16
I 16
 *
 * The name parameter points at the next component of the name to be
 * interpreted.  The namelen parameter is the number of integers in
 * the name.
E 16
E 13
 */
I 13
D 15
typedef int (sysctlfn) __P((int *, u_int, void *, u_int *, void *, u_int));
E 15
I 15
D 16
typedef int (sysctlfn) __P((int *, u_int, void *, u_int *, void *, u_int,
	struct proc *));
E 15
int sysctl_int __P((void *, u_int *, void *, u_int, int *));
int sysctl_rdint __P((void *, u_int *, void *, int));
int sysctl_string __P((void *, u_int *, void *, u_int, char *, int));
int sysctl_rdstring __P((void *, u_int *, void *, char *));
int sysctl_rdstruct __P((void *, u_int *, void *, void *, int));
E 16
I 16
typedef int (sysctlfn)
    __P((int *, u_int, void *, size_t *, void *, size_t, struct proc *));
E 16
E 13

D 13
struct kinfo_lock {
	int	kl_lock;
	int	kl_want;
	int	kl_locked;
};

#ifdef KERNEL
extern struct kinfo_lock kinfo_lock;
I 7
#else

E 13
I 13
D 16
#else /* KERNEL */
E 16
I 16
int sysctl_int __P((void *, size_t *, void *, size_t, int *));
int sysctl_rdint __P((void *, size_t *, void *, int));
int sysctl_string __P((void *, size_t *, void *, size_t, char *, int));
int sysctl_rdstring __P((void *, size_t *, void *, char *));
int sysctl_rdstruct __P((void *, size_t *, void *, void *, int));
I 21
void fill_eproc __P((struct proc *, struct eproc *));
E 21

D 22
#else /* !KERNEL */
E 22
I 22
#else	/* !KERNEL */
E 22
E 16
E 13
#include <sys/cdefs.h>

__BEGIN_DECLS
D 8
int	getkerninfo __P((int, char *, int *, int));
E 8
I 8
D 13
int	getkerninfo __P((int, void *, int *, int));
E 13
I 13
D 16
int	sysctl __P((int *, int, void *, int *, void *, int));
E 16
I 16
int	sysctl __P((int *, u_int, void *, size_t *, void *, size_t));
E 16
E 13
E 8
__END_DECLS
E 7
D 13
#endif
E 13
I 13
D 22
#endif /* KERNEL */
E 22
I 22
#endif	/* KERNEL */
#endif	/* !_SYS_SYSCTL_H_ */
E 22
E 13
I 5
D 6

#endif /* !_KINFO_H_ */
E 6
E 5
E 2
E 1
