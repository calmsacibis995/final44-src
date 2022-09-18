h58985
s 00001/00001/00079
d D 8.3 94/07/03 14:36:17 mckusick 6 5
c int => gid_t (from ralph)
e
s 00001/00001/00079
d D 8.2 94/03/27 13:45:41 pendry 5 4
c missing #includes
e
s 00002/00002/00078
d D 8.1 93/06/05 11:04:05 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00080
d D 5.1 92/07/13 15:47:31 pendry 3 2
c move to rev 5
e
s 00008/00007/00072
d D 1.2 92/07/12 09:03:53 pendry 2 1
c checkpoint
e
s 00079/00000/00000
d D 1.1 92/07/09 14:47:42 pendry 1 0
c date and time created 92/07/09 14:47:42 by pendry
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 * All rights reserved.
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * $Id: pt_file.c,v 1.1 1992/05/25 21:43:09 jsp Exp jsp $
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
I 5
#include <string.h>
E 5
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/syslog.h>

#include "portald.h"

int portal_file(pcr, key, v, so, fdp)
struct portal_cred *pcr;
char *key;
char **v;
int so;
int *fdp;
{
	int fd;
D 5
	int gid;
E 5
	char pbuf[MAXPATHLEN];
	int error;
I 2
D 6
	int gidset[NGROUPS];
E 6
I 6
	gid_t gidset[NGROUPS];
E 6
	int i;
E 2

	pbuf[0] = '/';
	strcpy(pbuf+1, key + (v[1] ? strlen(v[1]) : 0));

#ifdef DEBUG
D 2
	printf("path = %s, uid = %d, gid = %d\n", pbuf, pcr->pcr_uid, pcr->pcr_gid);
E 2
I 2
	printf("path = %s, uid = %d, gid = %d\n", pbuf, pcr->pcr_uid, pcr->pcr_groups[0]);
E 2
#endif

D 2
	if (setregid(0, pcr->pcr_gid) < 0)
		return (errno);
E 2
I 2
	for (i = 0; i < pcr->pcr_ngroups; i++)
		gidset[i] = pcr->pcr_groups[i];
E 2

D 2
	gid = pcr->pcr_gid;
	if (setgroups(1, &gid) < 0)
E 2
I 2
	if (setgroups(pcr->pcr_ngroups, gidset) < 0)
E 2
		return (errno);

D 2
	if (setreuid(0, pcr->pcr_uid) < 0)
E 2
I 2
	if (seteuid(pcr->pcr_uid) < 0)
E 2
		return (errno);

	fd = open(pbuf, O_RDWR|O_CREAT, 0666);
	if (fd < 0)
		error = errno;
	else
		error = 0;

D 2
	if (setreuid(0, 0) < 0 || setregid(0, 0) < 0) {
E 2
I 2
	if (seteuid((uid_t) 0) < 0) {	/* XXX - should reset gidset too */
E 2
		error = errno;
		syslog(LOG_ERR, "setcred: %s", strerror(error));
		if (fd >= 0) {
			(void) close(fd);
			fd = -1;
		}
	}

	if (error == 0)
		*fdp = fd;

#ifdef DEBUG
	fprintf(stderr, "pt_file returns *fdp = %d, error = %d\n", *fdp, error);
#endif

	return (error);
}
E 1
