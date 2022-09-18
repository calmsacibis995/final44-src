h54180
s 00002/00002/00275
d D 8.1 93/06/06 11:57:22 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00276
d D 5.4 92/02/09 08:44:13 pendry 4 3
c merge in new release
e
s 00003/00002/00274
d D 5.3 91/05/12 15:59:53 pendry 3 2
c checkpoint for network tape
e
s 00001/00013/00275
d D 5.2 91/03/17 13:44:05 pendry 2 1
c from amd5.3 alpha11
e
s 00288/00000/00000
d D 5.1 91/03/17 11:02:53 pendry 1 0
c date and time created 91/03/17 11:02:53 by pendry
e
u
U
t
T
I 1
/*
D 3
 * $Id: wr_fstab.c,v 5.2.1.2 90/12/21 16:46:52 jsp Alpha $
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
 * $Id: wr_fstab.c,v 5.2.1.3 91/05/07 22:19:14 jsp Alpha $
E 4
I 4
 * $Id: wr_fstab.c,v 5.2.2.1 1992/02/09 15:09:49 jsp beta $
E 4
 *
E 3
 */

#include "../fsinfo/fsinfo.h"

/* ---------- AIX 1 ------------------------------ */

/*
 * AIX 1 format
 */
static void write_aix1_dkfstab(ef, dp)
FILE *ef;
disk_fs *dp;
{
	char *hp = strdup(dp->d_host->h_hostname);
	char *p = strchr(hp, '.');
	if (p)
		*p = '\0';

	fprintf(ef, "\n%s:\n\tdev = %s\n\tvfs = %s\n\ttype = %s\n\tlog = %s\n\tvol = %s\n\topts = %s\n\tmount = true\n\tcheck = true\n\tfree = false\n",
		dp->d_mountpt,
		dp->d_dev,
		dp->d_fstype,
		dp->d_fstype,
		dp->d_log,
		dp->d_mountpt,
		dp->d_opts);
	free(hp);
}

static void write_aix1_dkrmount(ef, hn, fp)
FILE *ef;
char *hn;
fsmount *fp;
{
	char *h = strdup(fp->f_ref->m_dk->d_host->h_hostname);
	char *hp = strdup(h);
	char *p = strchr(hp, '.');
	if (p)
		*p = '\0';
	domain_strip(h, hn);
	fprintf(ef, "\n%s:\n\tsite = %s\n\tdev = %s:%s\n\tvfs = %s\n\ttype = %s\n\tvol = %s\n\topts = %s\n\tmount = true\n\tcheck = true\n\tfree = false\n",
		fp->f_localname,
		hp,
		h,
		fp->f_volname,
		fp->f_fstype,
		fp->f_fstype,
		fp->f_localname,
		fp->f_opts);

	free(hp);
	free(h);
}

/* ---------- AIX 3 ------------------------------ */

/*
 * AIX 3 format
 */
static void write_aix3_dkfstab(ef, dp)
FILE *ef;
disk_fs *dp;
{
	if (strcmp(dp->d_fstype, "jfs") == 0 && strncmp(dp->d_dev, "/dev/", 5) == 0 && !dp->d_log)
		error("aix 3 needs a log device for journalled filesystem (jfs) mounts");

	fprintf(ef, "\n%s:\n\tdev = %s\n\tvfs = %s\n\ttype = %s\n\tlog = %s\n\tvol = %s\n\topts = %s\n\tmount = true\n\tcheck = true\n\tfree = false\n",
		dp->d_mountpt,
		dp->d_dev,
		dp->d_fstype,
		dp->d_fstype,
		dp->d_log,
		dp->d_mountpt,
		dp->d_opts);
}

static void write_aix3_dkrmount(ef, hn, fp)
FILE *ef;
char *hn;
fsmount *fp;
{
	char *h = strdup(fp->f_ref->m_dk->d_host->h_hostname);
	domain_strip(h, hn);
	fprintf(ef, "\n%s:\n\tdev = %s:%s\n\tvfs = %s\n\ttype = %s\n\tvol = %s\n\topts = %s\n\tmount = true\n\tcheck = true\n\tfree = false\n",
		fp->f_localname,
		h,
		fp->f_volname,
		fp->f_fstype,
		fp->f_fstype,
		fp->f_localname,
		fp->f_opts);

	free(h);
}

/* ---------- Ultrix ----------------------------- */

static void write_ultrix_dkfstab(ef, dp)
FILE *ef;
disk_fs *dp;
{
	fprintf(ef, "%s:%s:%s:%s:%d:%d\n",
		dp->d_dev,
		dp->d_mountpt,
		dp->d_fstype,
		dp->d_opts,
		dp->d_freq,
		dp->d_passno);
}

static void write_ultrix_dkrmount(ef, hn, fp)
FILE *ef;
char *hn;
fsmount *fp;
{
	char *h = strdup(fp->f_ref->m_dk->d_host->h_hostname);
	domain_strip(h, hn);
	fprintf(ef, "%s@%s:%s:%s:%s:0:0\n",
		fp->f_volname,
		h,
		fp->f_localname,
		fp->f_fstype,
		fp->f_opts);
	free(h);
}

/* ---------- Generic ---------------------------- */

/*
 * Generic (BSD, SunOS, HPUX) format
 */
static void write_generic_dkfstab(ef, dp)
FILE *ef;
disk_fs *dp;
{
	fprintf(ef, "%s %s %s %s %d %d\n",
		dp->d_dev,
		dp->d_mountpt,
		dp->d_fstype,
		dp->d_opts,
		dp->d_freq,
		dp->d_passno);
}

static void write_generic_dkrmount(ef, hn, fp)
FILE *ef;
char *hn;
fsmount *fp;
{
	char *h = strdup(fp->f_ref->m_dk->d_host->h_hostname);
	domain_strip(h, hn);
	fprintf(ef, "%s:%s %s %s %s 0 0\n",
		h,
		fp->f_volname,
		fp->f_localname,
		fp->f_fstype,
		fp->f_opts);
	free(h);
}

/* ----------------------------------------------- */

static struct os_fstab_type {
	char *os_name;
	void (*op_fstab)();
	void (*op_mount)();
} os_tabs[] = {
	{ "aix1", write_aix1_dkfstab, write_aix1_dkrmount },		/* AIX 1 */
	{ "aix3", write_aix3_dkfstab, write_aix3_dkrmount },		/* AIX 3 */
	{ "generic", write_generic_dkfstab, write_generic_dkrmount },	/* Generic */
	{ "u2_0", write_ultrix_dkfstab, write_ultrix_dkrmount },	/* Ultrix */
	{ "u3_0", write_ultrix_dkfstab, write_ultrix_dkrmount },	/* Ultrix */
	{ "u4_0", write_ultrix_dkfstab, write_ultrix_dkrmount },	/* Ultrix */
	{ 0, 0, 0 }
};

#define	GENERIC_OS_NAME "generic"

static struct os_fstab_type *find_fstab_type(hp)
host *hp;
{
	struct os_fstab_type *op = 0;
	char *os_name = 0;

again:;
	if (os_name == 0) {
		if (ISSET(hp->h_mask, HF_OS))
			os_name = hp->h_os;
		else
			os_name = GENERIC_OS_NAME;
	}

	for (op = os_tabs; op->os_name; op++)
		if (strcmp(os_name, op->os_name) == 0)
			return op;

	os_name = GENERIC_OS_NAME;
	goto again;
}

static int write_dkfstab(ef, q, output)
FILE *ef;
qelem *q;
void (*output)();
{
	int errors = 0;
	disk_fs *dp;

	ITER(dp, disk_fs, q)
		if (strcmp(dp->d_fstype, "export") != 0)
			(*output)(ef, dp);

	return errors;
}

static int write_dkrmount(ef, q, hn, output)
FILE *ef;
qelem *q;
char *hn;
void (*output)();
{
	int errors = 0;
	fsmount *fp;

	ITER(fp, fsmount, q)
		(*output)(ef, hn, fp);

	return errors;
}

int write_fstab(q)
qelem *q;
{
	int errors = 0;

	if (fstab_pref) {
		host *hp;
		show_area_being_processed("write fstab", 4);
		ITER(hp, host, q) {
			if (hp->h_disk_fs || hp->h_mount) {
				FILE *ef = pref_open(fstab_pref, hp->h_hostname, gen_hdr, hp->h_hostname);
				if (ef) {
					struct os_fstab_type *op = find_fstab_type(hp);
					show_new(hp->h_hostname);
					if (hp->h_disk_fs)
						errors += write_dkfstab(ef, hp->h_disk_fs, op->op_fstab);
					else
						log("No local disk mounts on %s", hp->h_hostname);

					if (hp->h_mount)
						errors += write_dkrmount(ef, hp->h_mount, hp->h_hostname, op->op_mount);

					pref_close(ef);
				}
			} else {
				error("no disk mounts on %s", hp->h_hostname);
			}
		}
	}

	return errors;
}
E 1
