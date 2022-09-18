h37763
s 00002/00002/00053
d D 8.1 93/06/04 16:54:02 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00051
d D 5.3 92/05/26 14:37:38 bostic 3 2
c add LBL credit line
e
s 00011/00009/00040
d D 5.2 92/05/18 18:45:21 sklower 2 1
c formatting cleanup (checking by torek for sklower)
e
s 00049/00000/00000
d D 5.1 92/04/01 18:44:50 mckusick 1 0
c from Steve McCanne
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
I 3
 * This code is derived from software developed by the Computer Systems
 * Engineering group at Lawrence Berkeley Laboratory under DARPA contract
 * BG 91-66 and contributed to Berkeley.
 *
E 3
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct __kvm {
	/*
	 * a string to be prepended to error messages
	 * provided for compatibility with sun's interface
	 * if this value is null, errors are saved in errbuf[]
	 */
	const char *program;
	char	*errp;		/* XXX this can probably go away */
	char	errbuf[_POSIX2_LINE_MAX];
D 2
	DBM	*db;
E 2
I 2
	DB	*db;
E 2
#define ISALIVE(kd) ((kd)->vmfd >= 0)
	int	pmfd;		/* physical memory file (or crashdump) */
	int	vmfd;		/* virtual memory file (-1 if crashdump) */
	int	swfd;		/* swap file (e.g., /dev/drum) */
	int	nlfd;		/* namelist file (e.g., /vmunix) */
	struct kinfo_proc *procbase;
	char	*argspc;	/* (dynamic) storage for argv strings */
	int	arglen;		/* length of the above */
	char	**argv;		/* (dynamic) storage for argv pointers */
	int	argc;		/* length of above (not actual # present) */
	/*
	 * Kernel virtual address translation state.  This only gets filled
	 * in for dead kernels; otherwise, the running kernel (i.e. kmem)
	 * will do the translations for us.  It could be big, so we
	 * only allocate it if necessary.
	 */
	struct vmstate *vmst;
};

/*
 * Functions used internally by kvm, but across kvm modules.
 */
D 2
int _kvm_kvatop __P((kvm_t *, u_long, u_long *));
int _kvm_uvatop __P((kvm_t *, const struct proc *, u_long, u_long *));
int _kvm_initvtop __P((kvm_t *));
void _kvm_freevtop __P((kvm_t *));
void _kvm_err __P((kvm_t *kd, const char *program, const char *fmt, ...));
void _kvm_syserr __P((kvm_t *kd, const char *program, const char *fmt, ...));
void *_kvm_malloc __P((kvm_t *kd, size_t));
void _kvm_freeprocs __P((kvm_t *kd));
E 2
I 2
void	 _kvm_err __P((kvm_t *kd, const char *program, const char *fmt, ...));
void	 _kvm_freeprocs __P((kvm_t *kd));
void	 _kvm_freevtop __P((kvm_t *));
int	 _kvm_initvtop __P((kvm_t *));
int	 _kvm_kvatop __P((kvm_t *, u_long, u_long *));
void	*_kvm_malloc __P((kvm_t *kd, size_t));
void	*_kvm_realloc __P((kvm_t *kd, void *, size_t));
void	 _kvm_syserr
	    __P((kvm_t *kd, const char *program, const char *fmt, ...));
int	 _kvm_uvatop __P((kvm_t *, const struct proc *, u_long, u_long *));
E 2
E 1
