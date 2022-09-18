h37085
s 00003/00004/00165
d D 4.3 82/08/01 19:20:07 sam 3 2
c new ioctl's
e
s 00007/00005/00162
d D 4.2 82/06/26 22:18:42 sam 2 1
c macro-ized common expression
e
s 00167/00000/00000
d D 4.1 82/06/26 14:01:31 sam 1 0
c date and time created 82/06/26 14:01:31 by sam
e
u
U
t
T
I 1
/*	%M%	%I%	%E%	*/

/*
 *	Extended File System
 *
 * Protocol:
 *
 *	send:	EFS_ACCESS	<name> <mode> <ruid> <rgid>
 *	reply:	EFS_OK
 *	reply:	EFS_ERROR	<errno>
 *
 *	send:	EFS_CHMOD	<name> <mode> <uid> <gid>
 *	reply:	EFS_OK
 *	reply:	EFS_ERROR	<errno>
 *
 *	send:	EFS_CHOWN	<name> <owner> <group> <uid> <gid>
 *	reply:	EFS_OK
 *	reply:	EFS_ERROR	<errno>
 *
 *	send:	EFS_CLOSE
 *	reply:	EFS_OK
 *	reply:	EFS_ERROR	<errno>
 *
 *	send:	EFS_CREAT	<name> <mode> <umask> <uid> <gid>
 *	reply:	EFS_OK
 *	reply:	EFS_ERROR	<errno>
 *
 *	send:	EFS_FSTAT	
 *	reply:	EFS_OK		<data>...
 *	reply:	EFS_ERROR	<errno>
 *
 *	send:	EFS_IOCTL
 *	reply:	EFS_OK		<data>...
 *	reply:	EFS_ERROR	<errno>
 *
 *	send:	EFS_LINK	<name1> <name2> <uid> <gid>
 *	reply:	EFS_OK
 *	reply:	EFS_ERROR	<errno>
 *
 *	send:	EFS_LSTAT	<name> <uid> <gid>
 *	reply:	EFS_OK		<data>...
 *	reply:	EFS_ERROR	<errno>
 *
 *	send:	EFS_OPEN	<name> <mode> <uid> <gid>
 *	reply:	EFS_OK		<size>
 *	reply:	EFS_ERROR	<errno>
 *
 *	send:	EFS_READ	<offset> <count>
 *	reply:	EFS_OK		<data>...
 *	reply:	EFS_ERROR	<errno>
 *
 *	send:	EFS_READLINK	<name> <uid> <gid>
 *	reply:	EFS_OK		<data>...
 *	reply:	EFS_ERROR	<errno>
 *
 *	send:	EFS_STAT	<name> <uid> <gid>
 *	reply:	EFS_OK		<data>...
 *	reply:	EFS_ERROR	<errno>
 *
 *	send:	EFS_SYMLINK	<name1> <name2> <uid> <gid>
 *	reply:	EFS_OK
 *	reply:	EFS_ERROR	<errno>
 *
 *	send:	EFS_UNLINK	<name> <uid> <gid>
 *	reply:	EFS_OK
 *	reply:	EFS_ERROR	<errno>
 *
 *	send:	EFS_UTIME	<name> <uid> <gid>
 *	reply:	EFS_OK
 *	reply:	EFS_ERROR	<errno>
 *
 *	send:	EFS_WRITE	<offset> <count> <data>...
 *	reply:	EFS_OK
 *	reply:	EFS_ERROR	<errno>
 *
 */
D 3

#define	EFSIOSHTAB	(('e'<<8)|0)		/* set hosttable */
#define	EFSIOGHTAB	(('e'<<8)|1)		/* get hosttable */

E 3
#define EFS_NHT 	10
#define EFS_HTMAX	32
#define EFS_NPB		32

struct efs_controlblock {
	u_char	efs_cmd;		/* command */
	char	efs_error;		/* return error code */
	union {
		struct {
			short	efs_a_uid;	/* user id */
			short	efs_a_gid;	/* group id */
			int	efs_a_grps[NGRPS/(sizeof(int)*8)];
						/* group bit array */
			union {
				struct {
					short	efs_aa_owner;	/* user id */
					short	efs_aa_group;	/* group id */
				} efs_aa;
				struct {
					short	efs_ab_cmask;	/* cmask */
					short	efs_ab_mode;	/* mode */
				} efs_ab;
				time_t 	efs_ac_time[2];		/* utime */
			} efs_a_un;
		} efs_a;
		struct {
			u_long	efs_b_count;	/* bytes remaining for IO */
			off_t	efs_b_offset;	/* offset in file for IO */
		} efs_b;
		off_t	efs_c_size;		/* size of file or transfer */
	} efs_un;
};

#define efs_uid		efs_un.efs_a.efs_a_uid
#define efs_gid		efs_un.efs_a.efs_a_gid
#define efs_grps	efs_un.efs_a.efs_a_grps
#define efs_owner	efs_un.efs_a.efs_a_un.efs_aa.efs_aa_owner
#define efs_group	efs_un.efs_a.efs_a_un.efs_aa.efs_aa_group
#define efs_cmask	efs_un.efs_a.efs_a_un.efs_ab.efs_ab_cmask
#define efs_mode	efs_un.efs_a.efs_a_un.efs_ab.efs_ab_mode
#define efs_time	efs_un.efs_a.efs_a_un.efs_ac_time
#define efs_count	efs_un.efs_b.efs_b_count
#define efs_offset	efs_un.efs_b.efs_b_offset
#define efs_size	efs_un.efs_c_size

#define	EFS_ACCESS	0
#define	EFS_CHMOD	1
#define	EFS_CHOWN	2
#define	EFS_CLOSE	3
#define	EFS_CREAT	4
#define	EFS_FSTAT	5
#define	EFS_LINK	6
#define	EFS_OPEN	7
#define	EFS_READ	8
#define	EFS_STAT	9
#define	EFS_UNLINK	10
#define	EFS_UTIME	11
#define	EFS_WRITE	12
#define	EFS_IOCTL	13
#define	EFS_LSTAT	14
#define EFS_READLINK	15
#define EFS_SYMLINK	16
#define	EFS_OK		100
#define	EFS_ERROR	101

/* The hosttable relates a host name to a network address */

struct hosttable {
	char ht_name[EFS_HTMAX];
	struct sockaddr_in ht_addr;
} efs_hosttable[EFS_NHT];
I 3

#define	EFSIOSHTAB	_IOW(e, 0, struct efs_hosttable) /* set hosttable */
#define	EFSIOGHTAB	_IOR(e, 1, struct efs_hosttable) /* get hosttable */
E 3

#ifdef KERNEL
D 2

E 2
int efs_major;		/* major device of efs char special routines */
I 2
#define	efsinode(ip) \
	(((ip)->i_mode&IFMT) == IFCHR && \
	major((ip)->i_rdev) == efs_major && minor((ip)->i_rdev) == 0)
E 2

D 2
/* The patchboard connects file pointers on the local machine and sockets
	on the remote machine */

E 2
I 2
/*
 * The patchboard connects file pointers on the local
 * machine and sockets on the remote machine
 */
E 2
struct patchboard {
	struct file *pb_fp;		/* file pointer associated with pb */
	struct socket *pb_so;		/* socket associated with pb */
	off_t pb_filesize;		/* size of remote file */
	struct patchboard *pb_link;	/* link to next free pb */
} efs_patchboard[EFS_NPB], *efs_freepb;
D 2

E 2
#endif
E 1
