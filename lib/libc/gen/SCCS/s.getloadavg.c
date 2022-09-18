h40621
s 00002/00002/00043
d D 8.1 93/06/04 12:02:47 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00043
d D 6.7 93/05/25 00:00:33 torek 7 6
c pedantically ANSI, i.e., nothing after #else/#endif
e
s 00001/00001/00043
d D 6.6 93/04/27 17:33:07 bostic 6 5
c <sys/sysctl.h> now needs <sys/param.h>
e
s 00012/00048/00032
d D 6.5 93/04/27 15:26:44 bostic 5 4
c move kmem version of getloadavg to kvm library
e
s 00006/00003/00074
d D 6.4 93/03/31 16:54:03 mckusick 4 3
c convert from getkerninfo to sysctl
e
s 00029/00019/00048
d D 6.3 92/02/25 17:09:27 mckusick 3 2
c use getkerninfo to get load information (fallback to /dev/kmem if
c getkerninfo is not available)
e
s 00019/00036/00048
d D 6.2 90/06/29 00:15:34 marc 2 1
c use kvm library
e
s 00084/00000/00000
d D 6.1 89/05/29 16:36:20 mckusick 1 0
c date and time created 89/05/29 16:36:20 by mckusick
e
u
U
t
T
I 1
D 2
/*
E 2
I 2
/*-
E 2
D 8
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif LIBC_SCCS and not lint
E 2
I 2
#endif /* LIBC_SCCS and not lint */
E 2

D 5
#include <sys/param.h>
E 5
D 6
#include <sys/types.h>
E 6
I 6
#include <sys/param.h>
E 6
D 5
#include <sys/file.h>
I 3
#include <sys/kernel.h>
E 5
I 5
#include <sys/time.h>
#include <sys/resource.h>
E 5
D 4
#include <sys/kinfo.h>
E 4
I 4
#include <sys/sysctl.h>
#include <vm/vm_param.h>
E 4
E 3
D 2

E 2
D 5
#include <nlist.h>
E 5
D 2
#include <paths.h>
E 2

D 2
static char *kmem = _PATH_KMEM;
static char *vmunix = _PATH_UNIX;

E 2
D 5
static struct nlist nl[] = {
	{ "_averunnable" },
#define	X_AVERUNNABLE	0
	{ "_fscale" },
#define	X_FSCALE	1
	{ "" },
};
E 5
I 5
#include <stdlib.h>
E 5

/*
D 5
 *  getloadavg() -- Get system load averages.
E 5
I 5
 * getloadavg() -- Get system load averages.
E 5
 *
D 5
 *  Put `nelem' samples into `loadavg' array.
 *  Return number of samples retrieved, or -1 on error.
E 5
I 5
 * Put `nelem' samples into `loadavg' array.
 * Return number of samples retrieved, or -1 on error.
E 5
 */
I 5
int
E 5
getloadavg(loadavg, nelem)
	double loadavg[];
	int nelem;
{
D 2
	off_t lseek();
E 2
D 5
	static int need_nlist = 1;
E 5
D 3
	fixpt_t	averunnable[3];
	int fscale, kmemfd, i;
I 2
	int alreadyopen;
E 3
I 3
	struct loadavg loadinfo;
D 5
	int size, kmemfd, i;
	int alreadyopen = 1;
D 4
	int fscale;
E 4
I 4
	int mib[2], fscale;
E 5
I 5
D 7
	int size, i, mib[2];
E 7
I 7
	int i, mib[2];
	size_t size;
E 7
E 5
E 4
E 3
E 2

D 2
	/* nlist() is slow; cache result */
E 2
I 2
D 3
	if ((alreadyopen = kvm_openfiles(NULL, NULL, NULL)) == -1)
		return (-1);
	/* 
	 * cache nlist 
	 */
E 2
	if (need_nlist) {
D 2
		if (nlist(vmunix, nl) != 0)
			return (-1);
		if (nl[X_AVERUNNABLE].n_type == 0 || nl[X_FSCALE].n_type == 0)
			return (-1);
E 2
I 2
		if (kvm_nlist(nl) != 0)
E 3
I 3
D 5
	size = sizeof(loadinfo);
E 5
D 4
	if (getkerninfo(KINFO_LOADAVG, &loadinfo, &size, 0) < 0) {
E 4
I 4
	mib[0] = CTL_VM;
	mib[1] = VM_LOADAVG;
D 5
	if (sysctl(mib, 2, &loadinfo, &size, NULL, 0) < 0) {
E 4
		if ((alreadyopen = kvm_openfiles(NULL, NULL, NULL)) == -1)
			return (-1);
		/* 
		 * cache nlist 
		 */
		if (need_nlist) {
			if (kvm_nlist(nl) != 0)
				goto bad;
			need_nlist = 0;
		}
		if (kvm_read((off_t)nl[X_AVERUNNABLE].n_value,
		    (char *)&loadinfo, sizeof(loadinfo)) != size)
E 3
			goto bad;
E 2
D 3
		need_nlist = 0;
E 3
I 3
		/*
		 * Old kernel have fscale separately; if not found assume
		 * running new format.
		 */
		if (kvm_read( (off_t)nl[X_FSCALE].n_value, (char *)&fscale, 
		    sizeof(fscale)) == sizeof(fscale))
			loadinfo.fscale = fscale;
E 3
	}
E 5
I 5
	size = sizeof(loadinfo);
	if (sysctl(mib, 2, &loadinfo, &size, NULL, 0) < 0)
		return (-1);

E 5
D 2

	if ((kmemfd = open(kmem, O_RDONLY, 0)) < 0)
		return (-1);
	if (lseek(kmemfd, (off_t)nl[X_AVERUNNABLE].n_value, L_SET) == -1)
E 2
I 2
D 3
	if (kvm_read((off_t)nl[X_AVERUNNABLE].n_value, (char *)averunnable, 
	    sizeof(averunnable)) != sizeof(averunnable))
E 2
		goto bad;
D 2
	if (read(kmemfd, (char *)averunnable, sizeof(averunnable)) < 0)
E 2
I 2
	if (kvm_read( (off_t)nl[X_FSCALE].n_value, (char *)&fscale, 
	    sizeof(fscale)) != sizeof(fscale))
E 2
		goto bad;
D 2
	if (lseek(kmemfd, (off_t)nl[X_FSCALE].n_value, L_SET) == -1)
		goto bad;
	if (read(kmemfd, (char *)&fscale, sizeof(fscale)) < 0)
		goto bad;
	(void) close(kmemfd);

E 2
	nelem = MIN(nelem, sizeof(averunnable) / sizeof(averunnable[0]));
E 3
I 3
	nelem = MIN(nelem, sizeof(loadinfo.ldavg) / sizeof(fixpt_t));
E 3
	for (i = 0; i < nelem; i++)
D 3
		loadavg[i] = (double) averunnable[i] / fscale;
E 3
I 3
		loadavg[i] = (double) loadinfo.ldavg[i] / loadinfo.fscale;
E 3
I 2
D 5
	if (!alreadyopen)
		kvm_close();
E 5
E 2
	return (nelem);
D 5

bad:
D 2
	(void) close(kmemfd);
E 2
I 2
	if (!alreadyopen)
		kvm_close();
E 2
	return (-1);
E 5
}
E 1
