h54976
s 00002/00002/00041
d D 8.1 93/06/02 20:05:38 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00042
d D 5.11 93/04/27 11:12:39 bostic 12 11
c add kvm_getloadavg
e
s 00001/00000/00041
d D 5.10 92/07/11 22:40:04 leres 11 10
c Add prototype for kvm_getfiles().
e
s 00001/00000/00040
d D 5.9 92/05/26 18:50:31 bostic 10 9
c declare kinfo_proc as a structure, kinfo.h not necessarily included
e
s 00011/00011/00029
d D 5.8 92/05/26 18:34:03 bostic 9 8
c kvm_read, kvm_write take pointers to void *, not char *
e
s 00018/00011/00022
d D 5.7 92/04/01 17:52:45 mckusick 8 7
c update from Steve McCanne for Sun compatible kvm
e
s 00001/00001/00032
d D 5.6 91/04/23 17:04:33 bostic 7 6
c ummm, well, we took a vote -- it's a void * agian
e
s 00001/00001/00032
d D 5.5 91/04/23 16:41:22 bostic 6 5
c kvm_read really takes an offset, even though it may a kernel pointer
e
s 00006/00000/00027
d D 5.4 91/04/23 16:16:41 bostic 5 4
c prototype some more kvm functions
e
s 00006/00001/00021
d D 5.3 91/04/03 16:12:30 bostic 4 3
c protect all user-level include files against reinclusion
e
s 00008/00013/00014
d D 5.2 91/02/12 20:13:26 bostic 3 2
c don't need to prepend key with type byte any more;
c should never have included sys/kinfo.h;
c use <paths.h> for /var/run pathname; wordsmith function prototypes
e
s 00007/00013/00019
d D 5.1 91/02/08 18:17:08 bostic 2 1
c ANSI style declarations
e
s 00032/00000/00000
d D 1.1 90/06/26 14:23:54 marc 1 0
c date and time created 90/06/26 14:23:54 by marc
e
u
U
t
T
I 1
/*-
D 13
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 3
#include <sys/kinfo.h>
E 3
I 2
D 4
#include <sys/cdefs.h>
E 4
I 4
#ifndef _KVM_H_
#define	_KVM_H_
E 4
E 2

D 3
/*
 * type byte prepending key
 */
#define	KVMDB_NLIST	1
#define	KVMDB_DEVS	2
E 3
I 3
/* Default version symbol. */
#define	VRS_SYM		"_version"
#define	VRS_KEY		"VERSION"
E 3

I 8
#include <nlist.h>
E 8
I 4
#include <sys/cdefs.h>

E 4
D 3
#define	KVMDBDIR	"/var/run"

E 3
D 2
#if __STDC__ || c_plusplus
extern	struct proc *kvm_nextproc(void);
extern	struct eproc *kvm_geteproc(const struct proc *);
extern	struct user *kvm_getu(const struct proc *);
extern	char *kvm_getargs(const struct proc *, const struct user *);
extern	char *kvm_geterr(void);
#else
extern	struct proc *kvm_nextproc();
extern	struct eproc *kvm_geteproc();
extern	struct user *kvm_getu();
extern	char *kvm_getargs();
extern	char *kvm_geterr();
#endif
E 2
I 2
__BEGIN_DECLS
I 5
D 8
struct proc;
struct user;
E 5
D 3
struct proc *kvm_nextproc __P((void));
struct eproc *kvm_geteproc __P((const struct proc *));
struct user *kvm_getu __P((const struct proc *));
char *kvm_getargs __P((const struct proc *, const struct user *));
char *kvm_geterr __P((void));
E 3
I 3
char		*kvm_getargs __P((const struct proc *, const struct user *));
struct eproc	*kvm_geteproc __P((const struct proc *));
char		*kvm_geterr __P((void));
I 5
int		 kvm_getprocs __P((int, int));
E 5
struct user	*kvm_getu __P((const struct proc *));
struct proc	*kvm_nextproc __P((void));
I 5
int		 kvm_nlist __P((struct nlist *));
int		 kvm_openfiles __P((const char *, const char *, const char *));
D 6
int		 kvm_read __P((void *, void *, int));
E 6
I 6
D 7
int		 kvm_read __P((off_t, void *, int));
E 7
I 7
int		 kvm_read __P((void *, void *, int));
E 8
I 8

typedef struct __kvm kvm_t;

I 10
struct kinfo_proc;
E 10
D 9
kvm_t	*kvm_open __P((const char *, const char *, const char *, int,
		       const char *));
kvm_t	*kvm_openfiles __P((const char *, const char *, const char *, int,
			    char *));
int	 kvm_close __P((kvm_t *));
int	 kvm_read __P((kvm_t *, unsigned long, char *, unsigned int));
int	 kvm_write __P((kvm_t *, unsigned long, const char *, unsigned int));
int	 kvm_nlist __P((kvm_t *, struct nlist *));
char	*kvm_geterr __P((kvm_t *));

struct kinfo_proc *kvm_getprocs __P((kvm_t *, int, int, int *));
E 9
I 9
int	  kvm_close __P((kvm_t *));
E 9
char	**kvm_getargv __P((kvm_t *, const struct kinfo_proc *, int));
char	**kvm_getenvv __P((kvm_t *, const struct kinfo_proc *, int));
I 9
char	 *kvm_geterr __P((kvm_t *));
I 12
int	  kvm_getloadavg __P((kvm_t *, double [], int));
E 12
I 11
char	 *kvm_getfiles __P((kvm_t *, int, int, int *));
E 11
struct kinfo_proc *
	  kvm_getprocs __P((kvm_t *, int, int, int *));
int	  kvm_nlist __P((kvm_t *, struct nlist *));
kvm_t	 *kvm_open
	    __P((const char *, const char *, const char *, int, const char *));
kvm_t	 *kvm_openfiles
	    __P((const char *, const char *, const char *, int, char *));
int	  kvm_read __P((kvm_t *, unsigned long, void *, unsigned int));
int	  kvm_write __P((kvm_t *, unsigned long, const void *, unsigned int));
E 9

E 8
E 7
E 6
E 5
E 3
__END_DECLS
I 4

#endif /* !_KVM_H_ */
E 4
E 2
E 1
