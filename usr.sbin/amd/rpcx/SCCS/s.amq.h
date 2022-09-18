h31630
s 00002/00002/00125
d D 8.1 93/06/06 12:07:14 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00126
d D 5.4 92/02/09 08:45:08 pendry 4 3
c merge in new release
e
s 00003/00002/00124
d D 5.3 91/05/12 15:58:33 pendry 3 2
c checkpoint for network tape
e
s 00005/00001/00121
d D 5.2 91/03/17 13:45:46 pendry 2 1
c from amd5.3 alpha11
e
s 00122/00000/00000
d D 5.1 90/07/19 15:50:28 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: amq.h,v 5.2 90/06/23 22:20:13 jsp Rel $
E 2
I 2
D 3
 * $Id: amq.h,v 5.2.1.2 91/03/17 17:39:26 jsp Alpha $
E 2
 *
E 3
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: amq.h,v 5.2.1.3 91/05/07 22:18:49 jsp Alpha $
E 4
I 4
 * $Id: amq.h,v 5.2.2.1 1992/02/09 15:09:22 jsp beta $
E 4
 *
E 3
 */

#define AMQ_STRLEN 1024

typedef char *amq_string;
bool_t xdr_amq_string();


typedef long *time_type;
bool_t xdr_time_type();


struct amq_mount_tree {
	amq_string mt_mountinfo;
	amq_string mt_directory;
	amq_string mt_mountpoint;
	amq_string mt_type;
	time_type mt_mounttime;
	u_short mt_mountuid;
	int mt_getattr;
	int mt_lookup;
	int mt_readdir;
	int mt_readlink;
	int mt_statfs;
	struct amq_mount_tree *mt_next;
	struct amq_mount_tree *mt_child;
};
typedef struct amq_mount_tree amq_mount_tree;
bool_t xdr_amq_mount_tree();


typedef amq_mount_tree *amq_mount_tree_p;
bool_t xdr_amq_mount_tree_p();


struct amq_mount_info {
	amq_string mi_type;
	amq_string mi_mountpt;
	amq_string mi_mountinfo;
	amq_string mi_fserver;
	int mi_error;
	int mi_refc;
	int mi_up;
};
typedef struct amq_mount_info amq_mount_info;
bool_t xdr_amq_mount_info();


typedef struct {
	u_int amq_mount_info_list_len;
	amq_mount_info *amq_mount_info_list_val;
} amq_mount_info_list;
bool_t xdr_amq_mount_info_list();


typedef struct {
	u_int amq_mount_tree_list_len;
	amq_mount_tree_p *amq_mount_tree_list_val;
} amq_mount_tree_list;
bool_t xdr_amq_mount_tree_list();


struct amq_mount_stats {
	int as_drops;
	int as_stale;
	int as_mok;
	int as_merr;
	int as_uerr;
};
typedef struct amq_mount_stats amq_mount_stats;
bool_t xdr_amq_mount_stats();


enum amq_opt {
	AMOPT_DEBUG = 0,
	AMOPT_LOGFILE = 1,
	AMOPT_XLOG = 2,
	AMOPT_FLUSHMAPC = 3
};
typedef enum amq_opt amq_opt;
bool_t xdr_amq_opt();


struct amq_setopt {
	amq_opt as_opt;
	amq_string as_str;
};
typedef struct amq_setopt amq_setopt;
bool_t xdr_amq_setopt();


#define AMQ_PROGRAM ((u_long)300019)
#define AMQ_VERSION ((u_long)1)
#define AMQPROC_NULL ((u_long)0)
extern voidp amqproc_null_1();
#define AMQPROC_MNTTREE ((u_long)1)
extern amq_mount_tree_p *amqproc_mnttree_1();
#define AMQPROC_UMNT ((u_long)2)
extern voidp amqproc_umnt_1();
#define AMQPROC_STATS ((u_long)3)
extern amq_mount_stats *amqproc_stats_1();
#define AMQPROC_EXPORT ((u_long)4)
extern amq_mount_tree_list *amqproc_export_1();
#define AMQPROC_SETOPT ((u_long)5)
extern int *amqproc_setopt_1();
#define AMQPROC_GETMNTFS ((u_long)6)
extern amq_mount_info_list *amqproc_getmntfs_1();
I 2
#define AMQPROC_MOUNT ((u_long)7)
extern int *amqproc_mount_1();
#define AMQPROC_GETVERS ((u_long)8)
extern amq_string *amqproc_getvers_1();
E 2

E 1
