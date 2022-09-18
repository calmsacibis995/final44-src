h45486
s 00002/00002/00096
d D 8.1 93/06/06 12:07:24 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00097
d D 5.4 92/02/09 08:45:19 pendry 4 3
c merge in new release
e
s 00017/00000/00081
d D 5.3 91/05/12 15:58:28 pendry 3 2
c checkpoint for network tape
e
s 00000/00014/00081
d D 5.2 91/03/17 13:46:01 pendry 2 1
c from amd5.3 alpha11
e
s 00095/00000/00000
d D 5.1 90/07/19 15:50:31 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 3
/*
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
 *
D 4
 * $Id: mount.h,v 5.2.1.2 91/05/07 22:18:54 jsp Alpha $
E 4
I 4
 * $Id: mount.h,v 5.2.2.1 1992/02/09 15:09:27 jsp beta $
E 4
 *
 */

E 3
I 1
D 2
/*
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 2
#define MNTPATHLEN 1024
#define MNTNAMLEN 255
#define FHSIZE 32

typedef char fhandle[FHSIZE];
bool_t xdr_fhandle();


struct fhstatus {
	u_int fhs_status;
	union {
		fhandle fhs_fhandle;
	} fhstatus_u;
};
typedef struct fhstatus fhstatus;
bool_t xdr_fhstatus();


typedef char *dirpath;
bool_t xdr_dirpath();


typedef char *name;
bool_t xdr_name();


typedef struct mountbody *mountlist;
bool_t xdr_mountlist();


struct mountbody {
	name ml_hostname;
	dirpath ml_directory;
	mountlist ml_next;
};
typedef struct mountbody mountbody;
bool_t xdr_mountbody();


typedef struct groupnode *groups;
bool_t xdr_groups();


struct groupnode {
	name gr_name;
	groups gr_next;
};
typedef struct groupnode groupnode;
bool_t xdr_groupnode();


typedef struct exportnode *exports;
bool_t xdr_exports();


struct exportnode {
	dirpath ex_dir;
	groups ex_groups;
	exports ex_next;
};
typedef struct exportnode exportnode;
bool_t xdr_exportnode();


#define MOUNTPROG ((u_long)100005)
#define MOUNTVERS ((u_long)1)
#define MOUNTPROC_NULL ((u_long)0)
extern voidp mountproc_null_1();
#define MOUNTPROC_MNT ((u_long)1)
extern fhstatus *mountproc_mnt_1();
#define MOUNTPROC_DUMP ((u_long)2)
extern mountlist *mountproc_dump_1();
#define MOUNTPROC_UMNT ((u_long)3)
extern voidp mountproc_umnt_1();
#define MOUNTPROC_UMNTALL ((u_long)4)
extern voidp mountproc_umntall_1();
#define MOUNTPROC_EXPORT ((u_long)5)
extern exports *mountproc_export_1();
#define MOUNTPROC_EXPORTALL ((u_long)6)
extern exports *mountproc_exportall_1();

E 1
