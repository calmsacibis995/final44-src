h08306
s 00001/00001/00141
d D 8.2 95/05/04 16:24:17 mckusick 10 9
c MOUNT types become names
e
s 00002/00002/00140
d D 8.1 93/06/04 18:55:37 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00139
d D 5.6 93/06/04 17:33:54 cgd 8 7
c require an argument for hfs_cleanerd which specifies fs to clean.
e
s 00004/00004/00138
d D 5.5 92/12/18 06:35:10 margo 7 6
c Pass flag argument to get_fs_info, mmap_segment, munmap_segment, and 
c reread_fs_info to indicate use of mmap or not.
e
s 00001/00001/00141
d D 5.4 92/08/28 18:12:35 bostic 6 5
c Clean segments 1 at a time.
e
s 00002/00002/00140
d D 5.3 92/08/26 12:39:12 bostic 5 4
c PRINT_INODE had incorrect argument.
e
s 00005/00006/00137
d D 5.2 92/08/21 12:00:08 bostic 4 3
c Change markv calling to take a single array containing blocks
e
s 00016/00012/00127
d D 5.1 92/08/06 12:38:22 bostic 3 2
c integrate into the source tree, yank to 5.1, minor lint
e
s 00100/00208/00039
d D 1.2 92/08/06 12:27:12 bostic 2 1
c Version 2 cleaner
e
s 00247/00000/00000
d D 1.1 92/07/21 14:31:17 bostic 1 0
c date and time created 92/07/21 14:31:17 by bostic
e
u
U
t
T
I 3
/*-
D 9
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 3
I 1
/*
 * The LFS user-level library will be used when writing cleaners and
D 3
 * checkers for LFS file systems.  It will have facilities
 * for finding and parsing LFS segments.
E 3
I 3
 * checkers for LFS file systems.  It will have facilities for finding
 * and parsing LFS segments.
E 3
 */

I 2
#define DUMP_SUM_HEADER		0x0001
#define DUMP_INODE_ADDRS	0x0002
#define DUMP_FINFOS		0x0004
#define	DUMP_ALL		0xFFFF

E 2
#define IFILE_NAME "ifile"

D 3
#ifndef TRUE
#define TRUE	(1)
#define FALSE	(0)
#endif

E 3
I 2
/*
 * Cleaner parameters
 *	BUSY_LIM: lower bound of the number of segments currently available
 *		as a percentage of the total number of free segments possibly
 *		available.
 *	IDLE_LIM: Same as BUSY_LIM but used when the system is idle.
 *	MIN_SEGS: Minimum number of segments you should always have.
 *		I have no idea what this should be, but it should probably
 *		be a function of lfsp.
 *	NUM_TO_CLEAN: Number of segments to clean at once.  Again, this
 *		should probably be based on the file system size and how
 *		full or empty the segments being cleaned are.
 */

#define	BUSY_LIM	0.50
#define	IDLE_LIM	0.90
D 3
#define	MIN_SEGS(lfsp)	(3)
E 3
I 3

#define	MIN_SEGS(lfsp)		(3)
E 3
D 6
#define	NUM_TO_CLEAN(fsp)	(5)
E 6
I 6
#define	NUM_TO_CLEAN(fsp)	(1)
E 6

#define MAXLOADS	3
D 3
#define	ONE_MIN	0
#define	FIVE_MIN 1
#define	FIFTEEN_MIN 2
E 3
I 3
#define	ONE_MIN		0
#define	FIVE_MIN	1
#define	FIFTEEN_MIN	2
E 3

E 2
typedef struct fs_info {
	struct	statfs	*fi_statfsp;	/* fsstat info from getfsstat */
D 2
	struct	lfs	*fi_lfsp;	/* superblock */
					/*
					 * shared cleaner info data 
					 * (from top of ifile) 
					 */
	CLEANERINFO	*fi_cip;
E 2
I 2
	struct	lfs	fi_lfs;		/* superblock */
	CLEANERINFO	*fi_cip;	/* Cleaner info from ifile */
E 2
	SEGUSE	*fi_segusep;		/* segment usage table (from ifile) */
	IFILE	*fi_ifilep;		/* ifile table (from ifile) */
	u_long	fi_daddr_shift;		/* shift to get byte offset of daddr */
	u_long	fi_ifile_count;		/* # entries in the ifile table */
D 2
	u_long	fi_ifile_length;	/* length of the ifile */
E 2
I 2
	off_t	fi_ifile_length;	/* length of the ifile */
E 2
} FS_INFO;

D 2

#define fsid		(fsp->fi_statfsp->f_fsid)
#define statfsp		(fsp->fi_statfsp)
#define lfsp		(fsp->fi_lfsp)
#define cip		(fsp->fi_cip)
#define segusep		(fsp->fi_segusep)
#define ifilep		(fsp->fi_ifilep)
#define ifile_count	(fsp->fi_ifile_count)
#define ifile_length	(fsp->fi_ifile_length)

E 2
/* 
 * XXX: size (in bytes) of a segment
 *	should lfs_bsize be fsbtodb(fs,1), blksize(fs), or lfs_dsize? 
 */
D 2
#define seg_size(fs) ((fs)->lfs_ssize<<(fs)->lfs_bshift)
E 2
I 2
#define seg_size(fs) ((fs)->lfs_ssize << (fs)->lfs_bshift)
E 2

/* daddr -> byte offset */
D 2
#define datobyte(fs, da) ((da)<<(fs)->fi_daddr_shift)
#define bytetoda(fs, byte) ((byte)>>(fs)->fi_daddr_shift)
E 2
I 2
#define datobyte(fs, da) ((da) << (fs)->fi_daddr_shift)
#define bytetoda(fs, byte) ((byte) >> (fs)->fi_daddr_shift)
E 2

D 2
#define CLEANSIZE(fs)	(CLEANSIZE_SU(fs) << fs->lfs_bshift)
#define SEGTABSIZE(fs)	(SEGTABSIZE_SU(fs) << fs->lfs_bshift)
E 2
I 2
#define CLEANSIZE(fsp)	(fsp->fi_lfs.lfs_cleansz << fsp->fi_lfs.lfs_bshift)
#define SEGTABSIZE(fsp)	(fsp->fi_lfs.lfs_segtabsz << fsp->fi_lfs.lfs_bshift)
E 2

D 2
#define IFILE_ENTRY(fs, if, i)	((IFILE*)((caddr_t)(if) + \
	(fs)->lfs_bsize*((i)/(fs)->lfs_ifpb) + \
	sizeof(IFILE)*((i)%(fs)->lfs_ifpb)))
#define SEGUSE_ENTRY(fs, su, i) ((SEGUSE*)((caddr_t)(su) + \
	(fs)->lfs_bsize*((i)/(fs)->lfs_sepb) + \
	sizeof(IFILE)*((i)%(fs)->lfs_sepb)))
E 2
I 2
#define IFILE_ENTRY(fs, if, i) \
	((IFILE *)((caddr_t)(if) + ((i) / (fs)->lfs_ifpb << (fs)->lfs_bshift)) \
	+ (i) % (fs)->lfs_ifpb)
E 2

D 2
/*
 * fs_getmntinfo:
 *
 *    This function will get information on all mounted file systems
 * with the given type.  It will return the number of mounted file
 * systems with the right type.  It will return in *buf a pointer to
 * the array of statfs structures.
 */
extern int
fs_getmntinfo __P((struct statfs **buf, int type));
E 2
I 2
#define SEGUSE_ENTRY(fs, su, i) \
	((SEGUSE *)((caddr_t)(su) + (fs)->lfs_bsize * ((i) / (fs)->lfs_sepb)) +\
	(i) % (fs)->lfs_sepb)
E 2

D 2
/*
 * get_fs_info:
 *
 * get all the information available on a file system
 */
extern int
get_fs_info __P((struct statfs *lstatfsp, FS_INFO **fspp, int count));
E 2
I 2
__BEGIN_DECLS
int	 dump_summary __P((struct lfs *, SEGSUM *, u_long, daddr_t **));
void	 err __P((const int, const char *, ...));
D 8
int	 fs_getmntinfo __P((struct statfs **, int));
E 8
I 8
D 10
int	 fs_getmntinfo __P((struct statfs **, char *, int));
E 10
I 10
int	 fs_getmntinfo __P((struct statfs **, char *, char *));
E 10
E 8
int	 get __P((int, off_t, void *, size_t));
D 7
FS_INFO	*get_fs_info __P((struct statfs *, int));
E 7
I 7
D 8
FS_INFO	*get_fs_info __P((struct statfs *, int, int));
E 8
I 8
FS_INFO	*get_fs_info __P((struct statfs *, int));
E 8
E 7
D 4
int 	 lfs_segmapv __P((FS_INFO *, int, caddr_t, BLOCK_INFO **, int *,
	     INODE_INFO **, int *));
E 4
I 4
int 	 lfs_segmapv __P((FS_INFO *, int, caddr_t, BLOCK_INFO **, int *));
E 4
D 7
int	 mmap_segment __P((FS_INFO *, int, caddr_t *));
void	 munmap_segment __P((FS_INFO *, caddr_t));
void	 reread_fs_info __P((FS_INFO *, int));
E 7
I 7
int	 mmap_segment __P((FS_INFO *, int, caddr_t *, int));
void	 munmap_segment __P((FS_INFO *, caddr_t, int));
D 8
void	 reread_fs_info __P((FS_INFO *, int, int));
E 8
I 8
void	 reread_fs_info __P((FS_INFO *, int));
E 8
E 7
void	 toss __P((void *, int *, size_t,
	      int (*)(const void *, const void *, const void *), void *));
E 2

D 2
extern void
free_fs_info __P((FS_INFO *fsp, int count));

/* 
 * get_superblock: 
 *    gets the superblock from disk (possibly in face of errors) 
 */
extern int
get_superblock __P((FS_INFO *fsp, struct lfs *sbp));


/* 
 * get_ifile: 
 *    This function will map the ifile into memory.  It returns
 * NULL on failure.
 */
extern int
get_ifile __P((FS_INFO *fsp));

E 2
/*
D 2
 * segmapv:
 *
 *   This function will scan a segment and return a list of
 * <inode, blocknum> pairs which indicate which blocks were
 * contained as live data within the segment at some point
 * (it may have "died" since then).  Any given pair will be 
 * listed at most once.
E 2
I 2
 * USEFUL DEBUGGING FUNCTIONS:
E 2
 */
D 2
extern int 
lfs_segmapv __P((FS_INFO *fsp, int seg, caddr_t seg_buf, 
		BLOCK_INFO **blocks, int *bcount, 
		INODE_INFO **inodes, int *icount));
E 2
I 2
#ifdef VERBOSE
#define PRINT_FINFO(fp, ip) { \
	(void)printf("    %s %s%d version %d nblocks %d\n", \
	    (ip)->if_version > (fp)->fi_version ? "TOSSING" : "KEEPING", \
	    "FINFO for inode: ", (fp)->fi_ino, \
	    (fp)->fi_version, (fp)->fi_nblocks); \
	fflush(stdout); \
}
E 2

D 2
/* 
 * this will parse a partial segment and create a vector of block_info's
 * for live data blocks for live inodes.  It will not include blocks or 
 * inodes from files with new version numbers.  
 */
extern void
pseg_blocks __P((FS_INFO *fsp, int seg, SEGSUM *s, caddr_t seg_buf, 
		BLOCK_INFO **blocks, int *count));
E 2
I 2
D 4
#define PRINT_IINFO(b, iip) { \
E 4
I 4
D 5
#define PRINT_INODE(b, iip) { \
E 5
I 5
#define PRINT_INODE(b, bip) { \
E 5
E 4
	(void) printf("\t%s inode: %d daddr: 0x%lx create: %s\n", \
D 4
	    b ? "KEEPING" : "TOSSING", (iip)->ii_inode, (iip)->ii_daddr, \
	    ctime((time_t *)&(iip)->ii_segcreate)); \
E 4
I 4
	    b ? "KEEPING" : "TOSSING", (bip)->bi_inode, (bip)->bi_daddr, \
	    ctime((time_t *)&(bip)->bi_segcreate)); \
E 4
	fflush(stdout); \
}
E 2

D 2
/* 
 * this will parse a partial segment and create a vector of inode_info's
 * for live inodes.  It will not include blocks or inodes from files 
 * with new version numbers.  
 */
extern void
pseg_inodes __P((FS_INFO *fsp, int seg, SEGSUM *s, caddr_t seg_buf, 
		INODE_INFO **inodes, int *count));
E 2
I 2
#define PRINT_BINFO(bip) { \
	(void)printf("\tinode: %d lbn: %d daddr: 0x%lx create: %s\n", \
	    (bip)->bi_inode, (bip)->bi_lbn, (bip)->bi_daddr, \
	    ctime((time_t *)&(bip)->bi_segcreate)); \
	fflush(stdout); \
}
E 2

D 2
/* 
 * return the size of the partial segment in bytes. 
 */
extern u_long
pseg_size __P((FS_INFO *fsp, SEGSUM *s));
E 2
I 2
#define PRINT_SEGUSE(sup, n) { \
	(void)printf("Segment %d nbytes=%lu\tflags=%c%c%c ninos=%d nsums=%d lastmod: %s\n", \
			n, (sup)->su_nbytes, \
			(sup)->su_flags & SEGUSE_DIRTY ? 'D' : 'C', \
			(sup)->su_flags & SEGUSE_ACTIVE ? 'A' : ' ', \
			(sup)->su_flags & SEGUSE_SUPERBLOCK ? 'S' : ' ', \
			(sup)->su_ninos, (sup)->su_nsums, \
			ctime((time_t *)&(sup)->su_lastmod)); \
	fflush(stdout); \
}
E 2

I 2
void	 dump_super __P((struct lfs *));
void	 dump_cleaner_info __P((void *));
void	 print_SEGSUM __P(( struct lfs *, SEGSUM *));
void	 print_CLEANERINFO __P((CLEANERINFO *));
#else
#define	PRINT_FINFO(fp, ip)
D 4
#define	PRINT_IINFO(b, iip)
E 4
I 4
D 5
#define	PRINT_INODE(b, iip)
E 5
I 5
#define	PRINT_INODE(b, bip)
E 5
E 4
#define PRINT_BINFO(bip)
#define	PRINT_SEGUSE(sup, n)
#define	dump_cleaner_info(cip)
#define	dump_super(lfsp)
#endif
E 2
D 3

E 3
D 2
/* 
 * join block list b with list a (eliminating duplicates), leaving result
 * in list a.
 */
extern void
pseg_bjoin __P((FS_INFO *fsp, BLOCK_INFO **ablocks, int *acount, 
		BLOCK_INFO *bblocks, int bcount));


/* 
 * join inode list b with list a (eliminating duplicates), leaving result
 * in list a.
 */
extern void
pseg_ijoin __P((FS_INFO *fsp, INODE_INFO **ainodes, int *acount, 
		INODE_INFO *binodes, int bcount));


/* is the segsum block valid? return TRUE if it is, FALSE otherwise */
extern int 
segsum_valid __P((FS_INFO *fsp, SEGSUM *ssp));


/*
 * pseg_valid:
 *
 * returns 1 if the partial segment is valid, and 0 if it is invalid.
 * it uses the checksums to verify validity.
 */	 
extern int
pseg_valid __P((FS_INFO *fsp, SEGSUM *ssp));


/* 
 * pseg_finfos:
 * 
 * get array of FINFO pointers for partial segment
 * return the array in finfos, and the size of the array in count
 */
extern void
pseg_finfos __P((FS_INFO *fsp, SEGSUM *ssp, FINFO ***finfos, int *count));

/*
 * blocksize:
 *
 * returns the size (in bytes) of a (logical) block.
 * this is used because lfs uses different block sizes, depending
 * on the logical # of the block.  Lfs uses various sizes so
 * it doesn't need fragments.
 */ 
extern u_long
blocksize __P((FS_INFO *fsp, int index));

/*
 * finfo_size:
 *
 * returns the size in bytes of an FINFO structure 
 */
extern u_long
finfo_size __P((FINFO *finfop));
	
/*
 * Simple, general purpose, fast checksum.  Data must be short-aligned.
 * Returns a u_long in case we ever want to do something more rigorous.
 *
 * XXX
 * Use the TCP/IP checksum instead.
 */
extern u_long
cksum __P((register void *str, register size_t len));

/* 
 * read a segment into a memory buffer
 */
extern int
mmap_segment __P((FS_INFO *fsp, int segment, caddr_t *seg_buf));

extern void
munmap_segment __P((FS_INFO *fsp, caddr_t seg_buf));


/*
 * USEFUL DEBUGGING TOOLS:
 */

extern void
print_IFILE __P((IFILE *p));

extern void
print_SEGUSE __P((SEGUSE *p));

extern void
print_CLEANERINFO __P((CLEANERINFO *p));

extern void
print_SEGSUM __P((SEGSUM *p));

extern void
print_time_t __P((time_t t));

extern void
print_BLOCK_INFO __P((BLOCK_INFO *p));

extern void
print_INODE_INFO __P((INODE_INFO *p));

extern void
print_FINFO __P((FINFO *p));

extern void
print_lfs __P((struct lfs *p));

E 2
I 2
__END_DECLS
E 2
E 1
