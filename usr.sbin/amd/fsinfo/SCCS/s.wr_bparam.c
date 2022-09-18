h52072
s 00002/00002/00073
d D 8.1 93/06/06 11:57:13 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00074
d D 5.4 92/02/09 08:44:06 pendry 4 3
c merge in new release
e
s 00003/00002/00072
d D 5.3 91/05/12 15:59:51 pendry 3 2
c checkpoint for network tape
e
s 00001/00013/00073
d D 5.2 91/03/17 13:43:59 pendry 2 1
c from amd5.3 alpha11
e
s 00086/00000/00000
d D 5.1 91/03/17 11:02:50 pendry 1 0
c date and time created 91/03/17 11:02:50 by pendry
e
u
U
t
T
I 1
/*
D 3
 * $Id: wr_bparam.c,v 5.2.1.2 90/12/21 16:46:49 jsp Alpha $
 *
E 3
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
D 2
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: wr_bparam.c,v 5.2.1.3 91/05/07 22:19:10 jsp Alpha $
E 4
I 4
 * $Id: wr_bparam.c,v 5.2.2.1 1992/02/09 15:09:46 jsp beta $
E 4
 *
E 3
 */

#include "../fsinfo/fsinfo.h"

/*
 * Write a host/path in NFS format
 */
static int write_nfsname(ef, fp, hn)
FILE *ef;
fsmount *fp;
char *hn;
{
	int errors = 0;
	char *h = strdup(fp->f_ref->m_dk->d_host->h_hostname);
	domain_strip(h, hn);
	fprintf(ef, "%s:%s", h, fp->f_volname);
	free(h);
	return errors;
}

/*
 * Write a bootparams entry for a host
 */
static int write_boot_info(ef, hp)
FILE *ef;
host *hp;
{
	int errors = 0;
	fprintf(ef, "%s\troot=", hp->h_hostname);
	errors += write_nfsname(ef, hp->h_netroot, hp->h_hostname);
	fputs(" swap=", ef);
	errors += write_nfsname(ef, hp->h_netswap, hp->h_hostname);
	fputs("\n", ef);

	return 0;
}

/*
 * Output a bootparams file
 */
int write_bootparams(q)
qelem *q;
{
	int errors = 0;

	if (bootparams_pref) {
		FILE *ef = pref_open(bootparams_pref, "bootparams", info_hdr, "bootparams");
		if (ef) {
			host *hp;
			ITER(hp, host, q)
				if (hp->h_netroot && hp->h_netswap)
					errors += write_boot_info(ef, hp);
			errors += pref_close(ef);
		} else {
			errors++;
		}
	}

	return errors;
}
E 1
