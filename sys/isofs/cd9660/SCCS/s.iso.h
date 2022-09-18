h48885
s 00000/00001/00242
d D 8.6 95/05/10 10:53:45 mckusick 6 5
c lint
e
s 00003/00001/00240
d D 8.5 95/03/30 14:25:19 mckusick 5 4
c add cd9660_sysctl; fix prototype for cd9660_init
e
s 00054/00042/00187
d D 8.4 94/12/05 21:52:43 mckusick 4 3
c update from mycroft
e
s 00004/00005/00225
d D 8.3 94/07/13 16:15:31 mckusick 3 2
c update for 4.4BSD-Lite (from mycroft)
e
s 00013/00013/00217
d D 8.2 94/01/23 23:50:49 mckusick 2 1
c isofs => cd9660 naming convention
e
s 00230/00000/00000
d D 8.1 94/01/21 18:28:54 mckusick 1 0
c from Mike Hibler
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley
 * by Pace Willisson (pace@blitz.com).  The Rock Ridge Extension
 * Support code is derived from software contributed to Berkeley
 * by Atsushi Murai (amurai@spec.co.jp).
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define ISODCL(from, to) (to - from + 1)

struct iso_volume_descriptor {
	char type[ISODCL(1,1)]; /* 711 */
	char id[ISODCL(2,6)];
	char version[ISODCL(7,7)];
	char data[ISODCL(8,2048)];
};

/* volume descriptor types */
#define ISO_VD_PRIMARY 1
#define ISO_VD_END 255

#define ISO_STANDARD_ID "CD001"
#define ISO_ECMA_ID     "CDW01"

struct iso_primary_descriptor {
	char type			[ISODCL (  1,   1)]; /* 711 */
	char id				[ISODCL (  2,   6)];
	char version			[ISODCL (  7,   7)]; /* 711 */
	char unused1			[ISODCL (  8,   8)];
	char system_id			[ISODCL (  9,  40)]; /* achars */
	char volume_id			[ISODCL ( 41,  72)]; /* dchars */
	char unused2			[ISODCL ( 73,  80)];
	char volume_space_size		[ISODCL ( 81,  88)]; /* 733 */
	char unused3			[ISODCL ( 89, 120)];
	char volume_set_size		[ISODCL (121, 124)]; /* 723 */
	char volume_sequence_number	[ISODCL (125, 128)]; /* 723 */
	char logical_block_size		[ISODCL (129, 132)]; /* 723 */
	char path_table_size		[ISODCL (133, 140)]; /* 733 */
	char type_l_path_table		[ISODCL (141, 144)]; /* 731 */
	char opt_type_l_path_table	[ISODCL (145, 148)]; /* 731 */
	char type_m_path_table		[ISODCL (149, 152)]; /* 732 */
	char opt_type_m_path_table	[ISODCL (153, 156)]; /* 732 */
	char root_directory_record	[ISODCL (157, 190)]; /* 9.1 */
	char volume_set_id		[ISODCL (191, 318)]; /* dchars */
	char publisher_id		[ISODCL (319, 446)]; /* achars */
	char preparer_id		[ISODCL (447, 574)]; /* achars */
	char application_id		[ISODCL (575, 702)]; /* achars */
	char copyright_file_id		[ISODCL (703, 739)]; /* 7.5 dchars */
	char abstract_file_id		[ISODCL (740, 776)]; /* 7.5 dchars */
	char bibliographic_file_id	[ISODCL (777, 813)]; /* 7.5 dchars */
	char creation_date		[ISODCL (814, 830)]; /* 8.4.26.1 */
	char modification_date		[ISODCL (831, 847)]; /* 8.4.26.1 */
	char expiration_date		[ISODCL (848, 864)]; /* 8.4.26.1 */
	char effective_date		[ISODCL (865, 881)]; /* 8.4.26.1 */
	char file_structure_version	[ISODCL (882, 882)]; /* 711 */
	char unused4			[ISODCL (883, 883)];
	char application_data		[ISODCL (884, 1395)];
	char unused5			[ISODCL (1396, 2048)];
};
#define ISO_DEFAULT_BLOCK_SIZE		2048

struct iso_directory_record {
	char length			[ISODCL (1, 1)]; /* 711 */
	char ext_attr_length		[ISODCL (2, 2)]; /* 711 */
D 4
	unsigned char extent		[ISODCL (3, 10)]; /* 733 */
	unsigned char size		[ISODCL (11, 18)]; /* 733 */
E 4
I 4
	u_char extent			[ISODCL (3, 10)]; /* 733 */
	u_char size			[ISODCL (11, 18)]; /* 733 */
E 4
	char date			[ISODCL (19, 25)]; /* 7 by 711 */
	char flags			[ISODCL (26, 26)];
	char file_unit_size		[ISODCL (27, 27)]; /* 711 */
	char interleave			[ISODCL (28, 28)]; /* 711 */
	char volume_sequence_number	[ISODCL (29, 32)]; /* 723 */
	char name_len			[ISODCL (33, 33)]; /* 711 */
D 4
	char name			[0];
E 4
I 4
	char name			[1];			/* XXX */
E 4
};
/* can't take sizeof(iso_directory_record), because of possible alignment
   of the last entry (34 instead of 33) */
#define ISO_DIRECTORY_RECORD_SIZE	33

struct iso_extended_attributes {
D 4
	unsigned char owner		[ISODCL (1, 4)]; /* 723 */
	unsigned char group		[ISODCL (5, 8)]; /* 723 */
	unsigned char perm		[ISODCL (9, 10)]; /* 9.5.3 */
E 4
I 4
	u_char owner			[ISODCL (1, 4)]; /* 723 */
	u_char group			[ISODCL (5, 8)]; /* 723 */
	u_char perm			[ISODCL (9, 10)]; /* 9.5.3 */
E 4
	char ctime			[ISODCL (11, 27)]; /* 8.4.26.1 */
	char mtime			[ISODCL (28, 44)]; /* 8.4.26.1 */
	char xtime			[ISODCL (45, 61)]; /* 8.4.26.1 */
	char ftime			[ISODCL (62, 78)]; /* 8.4.26.1 */
	char recfmt			[ISODCL (79, 79)]; /* 711 */
	char recattr			[ISODCL (80, 80)]; /* 711 */
D 4
	unsigned char reclen		[ISODCL (81, 84)]; /* 723 */
E 4
I 4
	u_char reclen			[ISODCL (81, 84)]; /* 723 */
E 4
	char system_id			[ISODCL (85, 116)]; /* achars */
	char system_use			[ISODCL (117, 180)];
	char version			[ISODCL (181, 181)]; /* 711 */
	char len_esc			[ISODCL (182, 182)]; /* 711 */
	char reserved			[ISODCL (183, 246)];
D 4
	unsigned char len_au		[ISODCL (247, 250)]; /* 723 */
E 4
I 4
	u_char len_au			[ISODCL (247, 250)]; /* 723 */
E 4
};

/* CD-ROM Format type */
enum ISO_FTYPE  { ISO_FTYPE_DEFAULT, ISO_FTYPE_9660, ISO_FTYPE_RRIP, ISO_FTYPE_ECMA };

#ifndef	ISOFSMNT_ROOT
#define	ISOFSMNT_ROOT	0
#endif

struct iso_mnt {
	int im_flags;

	struct mount *im_mountp;
	dev_t im_dev;
	struct vnode *im_devvp;

	int logical_block_size;
	int im_bshift;
	int im_bmask;
	
	int volume_space_size;
D 6
	char im_fsmnt[50];
E 6
	struct netexport im_export;
	
	char root[ISODCL (157, 190)];
	int root_extent;
	int root_size;
	enum ISO_FTYPE  iso_ftype;
	
	int rr_skip;
	int rr_skip0;
};

#define VFSTOISOFS(mp)	((struct iso_mnt *)((mp)->mnt_data))

D 4
#define iso_blkoff(imp, loc) ((loc) & (imp)->im_bmask)
#define iso_lblkno(imp, loc) ((loc) >> (imp)->im_bshift)
#define iso_blksize(imp, ip, lbn) ((imp)->logical_block_size)
#define iso_lblktosize(imp, blk) ((blk) << (imp)->im_bshift)
E 4
I 4
#define blkoff(imp, loc)	((loc) & (imp)->im_bmask)
#define lblktosize(imp, blk)	((blk) << (imp)->im_bshift)
#define lblkno(imp, loc)	((loc) >> (imp)->im_bshift)
#define blksize(imp, ip, lbn)	((imp)->logical_block_size)
E 4

D 2
int isofs_mount __P((struct mount *,
E 2
I 2
int cd9660_mount __P((struct mount *,
E 2
	    char *, caddr_t, struct nameidata *, struct proc *));
D 2
int isofs_start __P((struct mount *, int, struct proc *));
int isofs_unmount __P((struct mount *, int, struct proc *));
int isofs_root __P((struct mount *, struct vnode **));
int isofs_quotactl __P((struct mount *, int, uid_t, caddr_t, struct proc *));
int isofs_statfs __P((struct mount *, struct statfs *, struct proc *));
int isofs_sync __P((struct mount *, int, struct ucred *, struct proc *));
int isofs_vget __P((struct mount *, ino_t, struct vnode **));
int isofs_fhtovp __P((struct mount *, struct fid *, struct mbuf *,
E 2
I 2
int cd9660_start __P((struct mount *, int, struct proc *));
int cd9660_unmount __P((struct mount *, int, struct proc *));
int cd9660_root __P((struct mount *, struct vnode **));
int cd9660_quotactl __P((struct mount *, int, uid_t, caddr_t, struct proc *));
int cd9660_statfs __P((struct mount *, struct statfs *, struct proc *));
int cd9660_sync __P((struct mount *, int, struct ucred *, struct proc *));
int cd9660_vget __P((struct mount *, ino_t, struct vnode **));
int cd9660_fhtovp __P((struct mount *, struct fid *, struct mbuf *,
E 2
	    struct vnode **, int *, struct ucred **));
D 2
int isofs_vptofh __P((struct vnode *, struct fid *));
int isofs_init __P(());
E 2
I 2
int cd9660_vptofh __P((struct vnode *, struct fid *));
D 5
int cd9660_init __P(());
E 5
I 5
int cd9660_init __P((struct vfsconf *));
#define cd9660_sysctl ((int (*) __P((int *, u_int, void *, size_t *, void *, \
                                    size_t, struct proc *)))eopnotsupp)
E 5
E 2

D 4
struct iso_node;
int iso_blkatoff __P((struct iso_node *ip, long offset, struct buf **bpp)); 
E 4
D 3
int iso_iget __P((struct iso_node *xp, ino_t ino, int relocated,
		  struct iso_node **ipp, struct iso_directory_record *isodir));
int iso_iput __P((struct iso_node *ip)); 
int iso_ilock __P((struct iso_node *ip)); 
int iso_iunlock __P((struct iso_node *ip)); 
E 3
D 2
int isofs_mountroot __P((void)); 
E 2
I 2
int cd9660_mountroot __P((void)); 
E 2

D 2
extern int (**isofs_vnodeop_p)();
E 2
I 2
extern int (**cd9660_vnodeop_p)();
I 3
extern int (**cd9660_specop_p)();
#ifdef FIFO
extern int (**cd9660_fifoop_p)();
#endif
E 3
E 2

D 4
extern inline int
E 4
I 4
static __inline int
E 4
isonum_711(p)
D 4
	unsigned char *p;
E 4
I 4
	u_char *p;
E 4
{
	return *p;
}

D 4
extern inline int
E 4
I 4
static __inline int
E 4
isonum_712(p)
	char *p;
{
	return *p;
}

D 4
extern inline int
isonum_721(p)
	unsigned char *p;
E 4
I 4
#ifndef UNALIGNED_ACCESS

static __inline int
isonum_723(p)
	u_char *p;
E 4
{
D 4
	return *p|((char)p[1] << 8);
E 4
I 4
	return *p|(p[1] << 8);
E 4
}

D 4
extern inline int
isonum_722(p)
	unsigned char *p;
E 4
I 4
static __inline int
isonum_733(p)
	u_char *p;
E 4
{
D 4
	return ((char)*p << 8)|p[1];
E 4
I 4
	return *p|(p[1] << 8)|(p[2] << 16)|(p[3] << 24);
E 4
}

D 4
extern inline int
E 4
I 4
#else /* UNALIGNED_ACCESS */

#if BYTE_ORDER == LITTLE_ENDIAN

static __inline int
E 4
isonum_723(p)
D 4
	unsigned char *p;
E 4
I 4
	u_char *p
E 4
{
D 4
	return isonum_721(p);
E 4
I 4
	return *(u_int16t *)p;
E 4
}

D 4
extern inline int
isonum_731(p)
	unsigned char *p;
E 4
I 4
static __inline int
isonum_733(p)
	u_char *p;
E 4
{
D 4
	return *p|(p[1] << 8)|(p[2] << 16)|(p[3] << 24);
E 4
I 4
	return *(u_int32t *)p;
E 4
}

D 4
extern inline int
isonum_732(p)
	unsigned char *p;
E 4
I 4
#endif

#if BYTE_ORDER == BIG_ENDIAN

static __inline int
isonum_723(p)
	u_char *p
E 4
{
D 4
	return (*p << 24)|(p[1] << 16)|(p[2] << 8)|p[3];
E 4
I 4
	return *(u_int16t *)(p + 2);
E 4
}

D 4
extern inline int
E 4
I 4
static __inline int
E 4
isonum_733(p)
D 4
	unsigned char *p;
E 4
I 4
	u_char *p;
E 4
{
D 4
	return isonum_731(p);
E 4
I 4
	return *(u_int32t *)(p + 4);
E 4
}

D 4
int isofncmp __P((unsigned char *, int, unsigned char *, int));
void isofntrans __P((unsigned char *, int, unsigned char *, unsigned short *,
		     int, int));
E 4
I 4
#endif

#endif /* UNALIGNED_ACCESS */

int isofncmp __P((u_char *, int, u_char *, int));
void isofntrans __P((u_char *, int, u_char *, u_short *, int, int));
ino_t isodirino __P((struct iso_directory_record *, struct iso_mnt *));
E 4

/*
 * Associated files have a leading '='.
 */
#define	ASSOCCHAR	'='
E 1
