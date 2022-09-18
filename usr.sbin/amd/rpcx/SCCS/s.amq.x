h04180
s 00002/00002/00157
d D 8.1 93/06/06 12:08:12 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00158
d D 5.4 92/02/09 08:45:10 pendry 4 3
c merge in new release
e
s 00003/00002/00156
d D 5.3 91/05/12 15:58:32 pendry 3 2
c checkpoint for network tape
e
s 00013/00001/00145
d D 5.2 91/03/17 13:45:50 pendry 2 1
c from amd5.3 alpha11
e
s 00146/00000/00000
d D 5.1 90/07/19 15:50:29 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: amq.x,v 5.2 90/06/23 22:20:11 jsp Rel $
E 2
I 2
D 3
 * $Id: amq.x,v 5.2.1.2 91/03/17 17:39:36 jsp Alpha $
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
 * $Id: amq.x,v 5.2.1.3 91/05/07 22:18:48 jsp Alpha $
E 4
I 4
 * $Id: amq.x,v 5.2.2.1 1992/02/09 15:09:20 jsp beta $
E 4
 *
E 3
 */

/*
 * Protocol description used by the amq program
 */

const AMQ_STRLEN = 1024;	/* Maximum length of a pathname */

/*
 * The type dirpath is the pathname of a directory
 */
typedef string amq_string<AMQ_STRLEN>;

/*
 * The type time_type should correspond to the system time_t
 */
typedef long time_type;

/*
 * A tree of what is mounted
 */
struct amq_mount_tree {
	amq_string	mt_mountinfo;	/* Mounted filesystem */
	amq_string 	mt_directory;	/* Virtual mount */
	amq_string 	mt_mountpoint;	/* Mount point */
	amq_string	mt_type;	/* Filesystem type */
	time_type	mt_mounttime;	/* Mount time */
	u_short		mt_mountuid;	/* Mounter */
	int		mt_getattr;	/* Count of getattrs */
	int		mt_lookup;	/* Count of lookups */
	int		mt_readdir;	/* Count of readdirs */
	int		mt_readlink;	/* Count of readlinks */
	int		mt_statfs;	/* Count of statfss */
	amq_mount_tree	*mt_next;	/* Sibling mount tree */
	amq_mount_tree	*mt_child;	/* Child mount tree */
};
typedef amq_mount_tree *amq_mount_tree_p;

/*
 * List of mounted filesystems
 */
struct amq_mount_info {
	amq_string	mi_type;	/* Type of mount */
	amq_string	mi_mountpt;	/* Mount point */
	amq_string	mi_mountinfo;	/* Mount info */
	amq_string	mi_fserver;	/* Fileserver */
	int		mi_error;	/* Error code */
	int		mi_refc;	/* References */
	int		mi_up;		/* Filesystem available */
};
typedef amq_mount_info amq_mount_info_list<>;

/*
 * A list of mount trees
 */
typedef amq_mount_tree_p amq_mount_tree_list<>;

/*
 * System wide stats
 */
struct amq_mount_stats {
	int	as_drops;	/* Dropped requests */
	int	as_stale;	/* Stale NFS handles */
	int	as_mok;		/* Succesful mounts */
	int	as_merr;	/* Failed mounts */
	int	as_uerr;	/* Failed unmounts */
};

enum amq_opt {
	AMOPT_DEBUG=0,
	AMOPT_LOGFILE=1,
	AMOPT_XLOG=2,
	AMOPT_FLUSHMAPC=3
};

struct amq_setopt {
	amq_opt	as_opt;		/* Option */
	amq_string as_str;	/* String */
};

program AMQ_PROGRAM {
	version AMQ_VERSION {
		/*
		 * Does no work. It is made available in all RPC services
		 * to allow server reponse testing and timing
		 */
		void
		AMQPROC_NULL(void) = 0;

		/*
		 * Returned the mount tree descending from
		 * the given directory.  The directory must
		 * be a top-level mount point of the automounter.
		 */
		amq_mount_tree_p
		AMQPROC_MNTTREE(amq_string) = 1;

		/*
		 * Force a timeout unmount on the specified directory.
		 */
		void
		AMQPROC_UMNT(amq_string) = 2;

		/*
		 * Obtain system wide statistics from the automounter
		 */
		amq_mount_stats
		AMQPROC_STATS(void) = 3;

		/*
		 * Obtain full tree
		 */
		amq_mount_tree_list
		AMQPROC_EXPORT(void) = 4;

		/*
		 * Control debug options.
		 * Return status:
		 *	-1: debug not available
		 *	 0: everything wonderful
		 *	>0: number of options not recognised
		 */
		int
		AMQPROC_SETOPT(amq_setopt) = 5;

		/*
		 * List of mounted filesystems
		 */
		amq_mount_info_list
		AMQPROC_GETMNTFS(void) = 6;
I 2

		/*
		 * Mount a filesystem
		 */
		int
		AMQPROC_MOUNT(amq_string) = 7;

		/*
		 * Get version info
		 */
		amq_string
		AMQPROC_GETVERS(void) = 8;
E 2
	} = 1;
} = 300019;	/* Allocated by Sun, 89/8/29 */
E 1
