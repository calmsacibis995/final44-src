h07436
s 00004/00004/00059
d D 8.2 94/12/08 22:39:39 mckusick 3 2
c only fail when trying to add one too many groups (from cgd)
e
s 00002/00002/00061
d D 8.1 93/06/04 12:02:36 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00063/00000/00000
d D 5.1 91/11/12 18:47:23 mckusick 1 0
c date and time created 91/11/12 18:47:23 by mckusick
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

/*
 * get credential
 */
#include <sys/types.h>
#include <string.h>
#include <grp.h>

int
getgrouplist(uname, agroup, groups, grpcnt)
	const char *uname;
	int agroup;
	register int *groups;
	int *grpcnt;
{
	register struct group *grp;
	register struct passwd *pw;
	register int i, ngroups;
	int ret, maxgroups;

	ret = 0;
	ngroups = 0;
	maxgroups = *grpcnt;
	/*
	 * When installing primary group, duplicate it;
	 * the first element of groups is the effective gid
	 * and will be overwritten when a setgid file is executed.
	 */
	groups[ngroups++] = agroup;
	if (maxgroups > 1)
		groups[ngroups++] = agroup;
	/*
	 * Scan the group file to find additional groups.
	 */
	setgrent();
	while (grp = getgrent()) {
		if (grp->gr_gid == agroup)
			continue;
D 3
		if (ngroups >= maxgroups) {
			ret = -1;
			break;
		}
E 3
		for (i = 0; grp->gr_mem[i]; i++) {
			if (!strcmp(grp->gr_mem[i], uname)) {
I 3
				if (ngroups >= maxgroups) {
					ret = -1;
					break;
				}
E 3
				groups[ngroups++] = grp->gr_gid;
				break;
			}
		}
	}
	endgrent();
	*grpcnt = ngroups;
	return (ret);
}
E 1
