h15160
s 00003/00003/00127
d D 8.2 95/02/19 07:49:54 cgd 9 8
c ktr_syscall members are ints now.  store argsize rather than narg.
e
s 00002/00002/00128
d D 8.1 93/06/02 19:53:57 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00001/00117
d D 7.5 92/01/14 12:11:54 marc 7 6
c account for context switches
e
s 00017/00002/00101
d D 7.4 91/05/07 20:11:35 marc 6 5
c add root trace flag
e
s 00001/00011/00102
d D 7.3 90/06/28 21:59:09 bostic 5 4
c new copyright notice
e
s 00025/00011/00088
d D 7.2 90/06/28 15:23:24 marc 4 3
c split out descend and inherit attributes; add signal tracing
e
s 00000/00000/00099
d D 7.1 89/09/04 14:30:45 karels 3 2
c rev 7
e
s 00039/00004/00060
d D 1.2 89/05/01 23:24:08 marc 2 1
c add generic i/o tracing -- other minor nots
e
s 00064/00000/00000
d D 1.1 88/12/14 03:00:11 marc 1 0
c date and time created 88/12/14 03:00:11 by marc
e
u
U
t
T
I 1
/*
I 2
D 8
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 5
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */

/*
E 2
D 4
 * operations to ktrace system call  (op & 0x3)
E 4
I 4
 * operations to ktrace system call  (KTROP(op))
E 4
 */
D 4
#define KTROP_SET		0	/* set traces */
#define KTROP_CLEAR		1	/* clear traces */
E 4
I 4
#define KTROP_SET		0	/* set trace points */
#define KTROP_CLEAR		1	/* clear trace points */
E 4
#define KTROP_CLEARFILE		2	/* stop all tracing to file */
I 4
#define	KTROP(o)		((o)&3)	/* macro to extract operation */
E 4
D 2

E 2
I 2
/*
D 4
 * flags to OR in with operation
E 4
I 4
 * flags (ORed in with operation)
E 4
 */
E 2
D 4
#define KTROP_INHERITFLAG	4	/* pass to children flag */
E 4
I 4
#define KTRFLAG_DESCEND		4	/* perform op on all children too */
E 4

/*
 * ktrace record header
 */
struct ktr_header {
I 2
	int	ktr_len;		/* length of buf */
E 2
	short	ktr_type;		/* trace record type */
D 2
	short	ktr_len;		/* length of buf */
E 2
	pid_t	ktr_pid;		/* process id */
	char	ktr_comm[MAXCOMLEN+1];	/* command name */
	struct	timeval ktr_time;	/* timestamp */
	caddr_t	ktr_buf;
};

/*
 * Test for kernel trace point
 */
D 7
#define KTRPOINT(p, type)	((p)->p_traceflag & (1<<(type)))
E 7
I 7
#define KTRPOINT(p, type)	\
	(((p)->p_traceflag & ((1<<(type))|KTRFAC_ACTIVE)) == (1<<(type)))
E 7
I 2

E 2
/*
D 2
 * ktrace record types
E 2
I 2
D 4
 * ktrace record types - add new ones here
E 4
I 4
 * ktrace record types
E 4
E 2
 */

/*
 * KTR_SYSCALL - system call record
 */
D 4
#define KTR_SYSCALL	0x1
E 4
I 4
#define KTR_SYSCALL	1
E 4
struct ktr_syscall {
D 9
	short	ktr_code;		/* syscall number */
	short	ktr_narg;		/* number of arguments */
E 9
I 9
	int	ktr_code;		/* syscall number */
	int	ktr_argsize;		/* size of arguments */
E 9
	/*
D 9
	 * followed by ktr_narg ints
E 9
I 9
	 * followed by ktr_argsize/sizeof(register_t) 'register_t's
E 9
	 */
};

/*
 * KTR_SYSRET - return from system call record
 */
D 4
#define KTR_SYSRET	0x2
E 4
I 4
#define KTR_SYSRET	2
E 4
struct ktr_sysret {
	short	ktr_code;
	short	ktr_eosys;
	int	ktr_error;
	int	ktr_retval;
};

/*
 * KTR_NAMEI - namei record
 */
D 4
#define KTR_NAMEI	0x3
E 4
I 4
#define KTR_NAMEI	3
E 4
D 2
/* record contains pathname */
E 2
I 2
	/* record contains pathname */
E 2

/*
I 2
 * KTR_GENIO - trace generic process i/o
 */
D 4
#define KTR_GENIO	0x4
E 4
I 4
#define KTR_GENIO	4
E 4
struct ktr_genio {
	int	ktr_fd;
	enum	uio_rw ktr_rw;
	/*
	 * followed by data successfully read/written
	 */
};

/*
E 2
D 4
 * kernel trace facilities
E 4
I 4
 * KTR_PSIG - trace processed signal
E 4
 */
I 4
#define	KTR_PSIG	5
struct ktr_psig {
	int	signo;
	sig_t	action;
	int	mask;
	int	code;
};

/*
I 7
 * KTR_CSW - trace context switches
 */
#define KTR_CSW		6
struct ktr_csw {
	int	out;	/* 1 if switch out, 0 if switch in */
	int	user;	/* 1 if usermode (ivcsw), 0 if kernel (vcsw) */
};

/*
E 7
D 6
 * kernel trace points
E 6
I 6
 * kernel trace points (in p_traceflag)
E 6
 */
I 6
#define KTRFAC_MASK	0x00ffffff
E 6
E 4
#define KTRFAC_SYSCALL	(1<<KTR_SYSCALL)
#define KTRFAC_SYSRET	(1<<KTR_SYSRET)
#define KTRFAC_NAMEI	(1<<KTR_NAMEI)
I 2
#define KTRFAC_GENIO	(1<<KTR_GENIO)
I 4
#define	KTRFAC_PSIG	(1<<KTR_PSIG)
I 7
#define KTRFAC_CSW	(1<<KTR_CSW)
E 7
D 6
#define KTRFAC_INHERIT	0x80000000
E 6
I 6
/*
 * trace flags (also in p_traceflags)
 */
#define KTRFAC_ROOT	0x80000000	/* root set this trace */
#define KTRFAC_INHERIT	0x40000000	/* pass trace flags to children */
I 7
#define KTRFAC_ACTIVE	0x20000000	/* ktrace logging in progress, ignore */
E 7

#ifndef	KERNEL

#include <sys/cdefs.h>

__BEGIN_DECLS
int	ktrace __P((const char *, int, int, pid_t));
__END_DECLS

#endif	/* !KERNEL */
E 6
E 4
E 2
E 1
