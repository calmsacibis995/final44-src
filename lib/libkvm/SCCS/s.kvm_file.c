h08756
s 00009/00007/00155
d D 8.2 94/08/20 22:55:25 mckusick 8 7
c use new queue.h data structures
e
s 00002/00002/00160
d D 8.1 93/06/04 16:53:22 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00161
d D 5.5 93/05/28 17:52:47 bostic 6 5
c lint
e
s 00004/00003/00158
d D 5.4 93/05/28 17:48:47 bostic 5 4
c check in for Keith S. who neither wrote nor fixed it ;-}
e
s 00016/00014/00145
d D 5.3 93/03/31 16:46:56 mckusick 4 3
c convert from kinfo to sysctl
e
s 00001/00001/00158
d D 5.2 92/05/26 14:40:21 bostic 3 1
c update copyright year
e
s 00004/00000/00159
d R 5.2 92/05/26 14:37:31 bostic 2 1
c add LBL credit line
e
s 00159/00000/00000
d D 5.1 92/04/27 17:15:54 sklower 1 0
c date and time created 92/04/27 17:15:54 by sklower
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1989 The Regents of the University of California.
E 3
I 3
D 7
 * Copyright (c) 1989, 1992 The Regents of the University of California.
E 3
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1989, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

/*
 * File list interface for kvm.  pstat, fstat and netstat are 
 * users of this code, so we've factored it out into a separate module.
 * Thus, we keep this grunge out of the other kvm applications (i.e.,
 * most other applications are interested only in open/close/read/nlist).
 */

#include <sys/param.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/exec.h>
#define KERNEL
#include <sys/file.h>
#undef KERNEL
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <nlist.h>
#include <kvm.h>

#include <vm/vm.h>
#include <vm/vm_param.h>
#include <vm/swap_pager.h>

D 4
#include <sys/kinfo.h>
E 4
I 4
#include <sys/sysctl.h>
E 4

#include <limits.h>
#include <ndbm.h>
#include <paths.h>

#include "kvm_private.h"

#define KREAD(kd, addr, obj) \
D 5
	(kvm_read(kd, addr, (char *)(obj), sizeof(*obj)) != sizeof(*obj))
E 5
I 5
	(kvm_read(kd, addr, obj, sizeof(*obj)) != sizeof(*obj))
E 5

/*
 * Get file structures.
 */
static
kvm_deadfiles(kd, op, arg, filehead_o, nfiles)
	kvm_t *kd;
	int op, arg, nfiles;
D 5
	off_t filehead_o;
E 5
I 5
	long filehead_o;
E 5
{
	int buflen = kd->arglen, needed = buflen, error, n = 0;
D 8
	struct file *fp, file, *filehead;
E 8
I 8
	struct file *fp, file;
	struct filelist filehead;
E 8
	register char *where = kd->argspc;
	char *start = where;

	/*
	 * first copyout filehead
	 */
	if (buflen > sizeof (filehead)) {
		if (KREAD(kd, filehead_o, &filehead)) {
			_kvm_err(kd, kd->program, "can't read filehead");
			return (0);
		}
		buflen -= sizeof (filehead);
		where += sizeof (filehead);
D 8
		*(struct file **)kd->argspc = filehead;
E 8
I 8
		*(struct filelist *)kd->argspc = filehead;
E 8
	}
	/*
	 * followed by an array of file structures
	 */
D 8
	for (fp = filehead; fp != NULL; fp = fp->f_filef) {
E 8
I 8
	for (fp = filehead.lh_first; fp != 0; fp = fp->f_list.le_next) {
E 8
		if (buflen > sizeof (struct file)) {
D 5
			if (KREAD(kd, (off_t)fp, ((struct file *)where))) {
E 5
I 5
D 6
			if (KREAD(kd, fp, ((struct file *)where))) {
E 6
I 6
			if (KREAD(kd, (long)fp, ((struct file *)where))) {
E 6
E 5
				_kvm_err(kd, kd->program, "can't read kfp");
				return (0);
			}
			buflen -= sizeof (struct file);
I 5
			fp = (struct file *)where;
E 5
			where += sizeof (struct file);
			n++;
		}
	}
	if (n != nfiles) {
		_kvm_err(kd, kd->program, "inconsistant nfiles");
		return (0);
	}
	return (nfiles);
}

char *
kvm_getfiles(kd, op, arg, cnt)
	kvm_t *kd;
	int op, arg;
	int *cnt;
{
D 4
	int size, st, nfiles;
E 4
I 4
	int mib[2], size, st, nfiles;
E 4
D 8
	struct file *filehead, *fp, *fplim;
E 8
I 8
	struct file *fp, *fplim;
	struct filelist filehead;
E 8

	if (ISALIVE(kd)) {
		size = 0;
D 4
		st = getkerninfo(op, NULL, &size, arg);
		if (st <= 0) {
E 4
I 4
		mib[0] = CTL_KERN;
		mib[1] = KERN_FILE;
		st = sysctl(mib, 2, NULL, &size, NULL, 0);
		if (st == -1) {
E 4
			_kvm_syserr(kd, kd->program, "kvm_getprocs");
			return (0);
		}
		if (kd->argspc == 0)
D 4
			kd->argspc = (char *)_kvm_malloc(kd, st);
		else if (kd->arglen < st)
			kd->argspc = (char *)_kvm_realloc(kd, kd->argspc, st);
E 4
I 4
			kd->argspc = (char *)_kvm_malloc(kd, size);
		else if (kd->arglen < size)
			kd->argspc = (char *)_kvm_realloc(kd, kd->argspc, size);
E 4
		if (kd->argspc == 0)
			return (0);
D 4
		size = kd->arglen = st;
		st = getkerninfo(op, kd->argspc, &size, arg);
		if (st < sizeof(filehead)) {
E 4
I 4
		kd->arglen = size;
		st = sysctl(mib, 2, kd->argspc, &size, NULL, 0);
		if (st == -1 || size < sizeof(filehead)) {
E 4
			_kvm_syserr(kd, kd->program, "kvm_getfiles");
			return (0);
		}
D 8
		filehead = *(struct file **)kd->argspc;
E 8
I 8
		filehead = *(struct filelist *)kd->argspc;
E 8
		fp = (struct file *)(kd->argspc + sizeof (filehead));
		fplim = (struct file *)(kd->argspc + size);
D 8
		for (nfiles = 0; filehead && (fp < fplim); nfiles++, fp++)
			filehead = fp->f_filef;
E 8
I 8
		for (nfiles = 0; filehead.lh_first && (fp < fplim); nfiles++, fp++)
			filehead.lh_first = fp->f_list.le_next;
E 8
	} else {
		struct nlist nl[3], *p;

		nl[0].n_name = "_filehead";
		nl[1].n_name = "_nfiles";
		nl[2].n_name = 0;

		if (kvm_nlist(kd, nl) != 0) {
			for (p = nl; p->n_type != 0; ++p)
				;
			_kvm_err(kd, kd->program,
				 "%s: no such symbol", p->n_name);
			return (0);
		}
		if (KREAD(kd, nl[0].n_value, &nfiles)) {
			_kvm_err(kd, kd->program, "can't read nfiles");
			return (0);
		}
		size = sizeof(filehead) + (nfiles + 10) * sizeof(struct file);
		if (kd->argspc == 0)
D 4
			kd->argspc = (char *)_kvm_malloc(kd, st);
		else if (kd->arglen < st)
			kd->argspc = (char *)_kvm_realloc(kd, kd->argspc, st);
E 4
I 4
			kd->argspc = (char *)_kvm_malloc(kd, size);
		else if (kd->arglen < size)
			kd->argspc = (char *)_kvm_realloc(kd, kd->argspc, size);
E 4
		if (kd->argspc == 0)
			return (0);
D 4
		size = kd->arglen = st;
E 4
I 4
		kd->arglen = size;
E 4
		nfiles = kvm_deadfiles(kd, op, arg, nl[1].n_value, nfiles);
		if (nfiles == 0)
			return (0);
	}
	*cnt = nfiles;
	return (kd->argspc);
}
E 1
