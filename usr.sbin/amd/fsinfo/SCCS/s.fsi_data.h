h48838
s 00002/00002/00208
d D 8.1 93/06/06 11:56:47 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00209
d D 5.4 92/02/09 08:43:50 pendry 4 3
c merge in new release
e
s 00003/00002/00207
d D 5.3 91/05/12 15:59:46 pendry 3 2
c checkpoint for network tape
e
s 00001/00013/00208
d D 5.2 91/03/17 13:43:40 pendry 2 1
c from amd5.3 alpha11
e
s 00221/00000/00000
d D 5.1 91/03/17 11:02:37 pendry 1 0
c date and time created 91/03/17 11:02:37 by pendry
e
u
U
t
T
I 1
/*
D 3
 * $Id: fsi_data.h,v 5.2.1.2 90/12/21 16:42:16 jsp Alpha $
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
 * $Id: fsi_data.h,v 5.2.1.3 91/05/07 22:19:16 jsp Alpha $
E 4
I 4
 * $Id: fsi_data.h,v 5.2.2.1 1992/02/09 15:09:53 jsp beta $
E 4
 *
E 3
 */

typedef struct auto_tree auto_tree;
typedef struct automount automount;
typedef struct dict dict;
typedef struct dict_data dict_data;
typedef struct dict_ent dict_ent;
typedef struct disk_fs disk_fs;
typedef struct ether_if ether_if;
typedef struct fsmount fsmount;
typedef struct host host;
typedef struct ioloc ioloc;
typedef struct mount mount;
typedef struct qelem qelem;

/*
 * Linked lists...
 */
struct qelem {
	qelem *q_forw;
	qelem *q_back;
};

/*
 * Automount tree
 */
struct automount {
	qelem a_q;
	ioloc *a_ioloc;
	char *a_name;		/* Automount key */
	char *a_volname;	/* Equivalent volume to be referenced */
	char *a_symlink;	/* Symlink representation */
	qelem *a_mount;		/* Tree representation */
	dict_ent *a_mounted;
};

/*
 * List of automount trees
 */
struct auto_tree {
	qelem t_q;
	ioloc *t_ioloc;
	char *t_defaults;
	qelem *t_mount;
};
	
/*
 * A host
 */
struct host {
	qelem q;
	int h_mask;
	ioloc *h_ioloc;
	fsmount *h_netroot, *h_netswap;
#define HF_HOST	0
	char *h_hostname;	/* The full name of the host */
	char *h_lochost;	/* The name of the host with local domains stripped */
	char *h_hostpath;	/* The filesystem path to the host (cf compute_hostpath) */
#define	HF_ETHER 1
	qelem *h_ether;
#define	HF_CONFIG 2
	qelem *h_config;
#define	HF_ARCH 3
	char *h_arch;
#define	HF_CLUSTER 4
	char *h_cluster;
#define	HF_OS 5
	char *h_os;
	qelem *h_disk_fs;
	qelem *h_mount;
};

/*
 * An ethernet interface
 */
struct ether_if {
	qelem e_q;
	int e_mask;
	ioloc *e_ioloc;
	char *e_if;
#define	EF_INADDR 0
	struct in_addr e_inaddr;
#define	EF_NETMASK 1
	u_long e_netmask;
#define	EF_HWADDR 2
	char *e_hwaddr;
};

/*
 * Disk filesystem structure.
 *
 * If the DF_* numbers are changed
 * disk_fs_strings in analyze.c will
 * need updating.
 */
struct disk_fs {
	qelem d_q;
	int d_mask;
	ioloc *d_ioloc;
	host *d_host;
	char *d_mountpt;
	char *d_dev;
#define	DF_FSTYPE	0
	char *d_fstype;
#define	DF_OPTS		1
	char *d_opts;
#define	DF_DUMPSET	2
	char *d_dumpset;
#define	DF_PASSNO	3
	int d_passno;
#define	DF_FREQ		4
	int d_freq;
#define	DF_MOUNT	5
	qelem *d_mount;
#define	DF_LOG		6
	char *d_log;
};
#define	DF_REQUIRED	((1<<DF_FSTYPE)|(1<<DF_OPTS)|(1<<DF_PASSNO)|(1<<DF_MOUNT))

/*
 * A mount tree
 */
struct mount {
	qelem m_q;
	ioloc *m_ioloc;
	int m_mask;
#define	DM_VOLNAME	0
	char *m_volname;
#define	DM_EXPORTFS	1
	char *m_exportfs;
#define	DM_SEL		2
	char *m_sel;
	char *m_name;
	int m_name_len;
	mount *m_parent;
	disk_fs *m_dk;
	mount *m_exported;
	qelem *m_mount;
};

/*
 * Additional filesystem mounts
 *
 * If the FM_* numbers are changed
 * disk_fs_strings in analyze.c will
 * need updating.
 */
struct fsmount {
	qelem f_q;
	mount *f_ref;
	ioloc *f_ioloc;
	int f_mask;
#define	FM_LOCALNAME	0
	char *f_localname;
#define	FM_VOLNAME	1
	char *f_volname;
#define	FM_FSTYPE	2
	char *f_fstype;
#define	FM_OPTS		3
	char *f_opts;
#define	FM_FROM		4
	char *f_from;
};
#define	FM_REQUIRED	((1<<FM_VOLNAME)|(1<<FM_FSTYPE)|(1<<FM_OPTS)|(1<<FM_FROM)|(1<<FM_LOCALNAME))
#define	FM_NETROOT	0x01
#define	FM_NETSWAP	0x02
#define	FM_NETBOOT	(FM_NETROOT|FM_NETSWAP)

#define	DICTHASH	5
struct dict_ent {
	dict_ent *de_next;
	char *de_key;
	int de_count;
	qelem de_q;
};

/*
 * Dictionaries ...
 */
struct dict_data {
	qelem dd_q;
	char *dd_data;
};

struct dict {
	dict_ent *de[DICTHASH];
};

/*
 * Source text location for error reports
 */
struct ioloc {
	int i_line;
	char *i_file;
};
E 1
