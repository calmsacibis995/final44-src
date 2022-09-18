h58670
s 00033/00009/00636
d D 8.3 95/05/24 19:39:53 margo 16 15
c Make changes so that the cleaner supports fragments.
e
s 00002/00002/00643
d D 8.2 95/05/04 16:24:18 mckusick 15 14
c MOUNT types become names
e
s 00002/00002/00643
d D 8.1 93/06/04 18:55:45 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00644
d D 5.11 93/06/04 18:34:59 cgd 13 12
c if statfs fails when rereading, exit; fs is unmounted
e
s 00041/00048/00604
d D 5.10 93/06/04 17:34:00 cgd 12 11
c require an argument for hfs_cleanerd which specifies fs to clean.
e
s 00004/00003/00648
d D 5.9 93/05/17 11:11:19 bostic 11 10
c lint, bcopy -> memmove
e
s 00075/00068/00576
d D 5.8 92/12/18 06:36:21 margo 10 9
c Pass flag around to indicate use of mmap instead of read.
e
s 00002/00001/00642
d D 5.7 92/11/01 11:15:08 bostic 9 8
c Verify that segment doesn't exceed maximum size.
e
s 00024/00002/00619
d D 5.6 92/10/24 09:59:54 margo 8 7
c Add diagnostics to check summary size.  Fix compare routine so 
c it always sorts negative numbers (except -1) last.
e
s 00003/00000/00618
d D 5.5 92/09/03 08:26:24 margo 7 6
c Set version number in BLOCK_INFO structures
e
s 00010/00004/00608
d D 5.4 92/08/26 12:39:38 bostic 6 5
c Don't look up ifile inode in ifile.
e
s 00034/00091/00578
d D 5.3 92/08/21 12:00:32 bostic 5 4
c Change markv calling convention to take a single array containing
c both blocks and inodes.
e
s 00001/00001/00668
d D 5.2 92/08/06 13:30:21 bostic 4 3
c don't wait in getmntinfo
e
s 00011/00000/00658
d D 5.1 92/08/06 12:38:25 bostic 3 2
c integrate into the source tree, yank to 5.1, minor lint
e
s 00432/00738/00226
d D 1.2 92/08/06 12:27:22 bostic 2 1
c Version 2 cleaner
e
s 00964/00000/00000
d D 1.1 92/07/21 14:31:17 bostic 1 0
c date and time created 92/07/21 14:31:17 by bostic
e
u
U
t
T
I 3
/*-
D 14
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 3
I 1
D 2

E 2
#include <sys/param.h>
#include <sys/time.h>
D 2
#include <sys/uio.h>
#include <sys/vnode.h>
E 2
#include <sys/stat.h>
#include <sys/mount.h>
I 10
#include <sys/types.h>
#include <sys/mman.h>
E 10

#include <ufs/ufs/dinode.h>
#include <ufs/lfs/lfs.h>
D 2
#include <ufs/lfs/lfs_extern.h>
E 2

#include <fcntl.h>
#include <stdio.h>
D 11
#include <unistd.h>
E 11
I 2
#include <stdlib.h>
#include <string.h>
I 11
#include <unistd.h>

E 11
E 2
#include "clean.h"

I 2
void	 add_blocks __P((FS_INFO *, BLOCK_INFO *, int *, SEGSUM *, caddr_t,
	     daddr_t, daddr_t));
D 5
void	 add_inodes __P((FS_INFO *, INODE_INFO *, int *, SEGSUM *, caddr_t,
E 5
I 5
void	 add_inodes __P((FS_INFO *, BLOCK_INFO *, int *, SEGSUM *, caddr_t,
E 5
	     daddr_t));
int	 bi_compare __P((const void *, const void *));
int	 bi_toss __P((const void *, const void *, const void *));
D 10
void	 get_ifile __P((FS_INFO *));
E 10
I 10
void	 get_ifile __P((FS_INFO *, int));
E 10
int	 get_superblock __P((FS_INFO *, struct lfs *));
D 5
int	 ii_compare __P((const void *, const void *));
int	 ii_toss __P((const void *, const void *, const void *));
E 5
int	 pseg_valid __P((FS_INFO *, SEGSUM *));

E 2
/*
D 2
 * fs_getmntinfo:
 *
 *    This function will get information on all mounted file systems
E 2
I 2
D 12
 * This function will get information on all mounted file systems
E 2
 * of a given type.
E 12
I 12
 * This function will get information on a a filesystem which matches
 * the name and type given.  If a "name" is in a filesystem of the given
 * type, then buf is filled with that filesystem's info, and the
 * a non-zero value is returned.
E 12
 */
int
D 12
fs_getmntinfo(buf, type)
E 12
I 12
fs_getmntinfo(buf, name, type)
E 12
	struct	statfs	**buf;
I 12
	char	*name;
E 12
D 15
	int	type;
E 15
I 15
	char	*type;
E 15
{
D 2
	int	i;
	int	count;
	int	tcount;
	struct	statfs	*tstatfsp;
E 2
I 2
D 12
	struct statfs *tstatfsp;
	struct statfs *sbp;
	int count, i, tcount;
E 12
I 12
	/* allocate space for the filesystem info */
	*buf = (struct statfs *)malloc(sizeof(struct statfs));
	if (*buf == NULL)
		return 0;
E 12
E 2

D 4
	tcount = getmntinfo(&tstatfsp, 0);
E 4
I 4
D 12
	tcount = getmntinfo(&tstatfsp, MNT_NOWAIT);
E 4

	if (tcount < 0) {
D 2
		perror ("fs_getmntinfo: getmntinfo failed");
		return -1;
E 2
I 2
		err(0, "getmntinfo failed");
		return (-1);
E 12
I 12
	/* grab the filesystem info */
	if (statfs(name, *buf) < 0) {
		free(*buf);
		return 0;
E 12
E 2
	}

D 2
	for (count = 0, i = 0 ; i < tcount ; i ++)
		if (type == 0 || tstatfsp[i].f_type == type)
			++ count;
E 2
I 2
D 12
	for (count = 0, i = 0; i < tcount ; ++i)
		if (tstatfsp[i].f_type == type)
			++count;
E 2

D 2
	if (count > 0) {
		*buf = (struct statfs *)
			malloc(count*sizeof(struct statfs));
		if (*buf == 0) { perror ("fs_getmntinfo: out of space"); exit (1); }
		for (i = 0, count = 0 ; i < tcount ; i ++) {
			if (type == 0 || tstatfsp[i].f_type == type) {
				(*buf)[count] = tstatfsp[i];
				++count;
E 2
I 2
	if (count) {
		if (!(*buf = (struct statfs *)
			malloc(count * sizeof(struct statfs))))
			err(1, "fs_getmntinfo: out of space");
		for (i = 0, sbp = *buf; i < tcount ; ++i) {
			if (tstatfsp[i].f_type == type) {
				*sbp = tstatfsp[i];
				++sbp;
E 2
			}
		}
E 12
I 12
	/* check to see if it's the one we want */
D 15
	if (((*buf)->f_type != type) ||
E 15
I 15
	if (strcmp((*buf)->f_fstypename, type) ||
E 15
	    strncmp(name, (*buf)->f_mntonname, MNAMELEN)) {
		/* "this is not the filesystem you're looking for */
		free(*buf);
		return 0;
E 12
D 2
		return count;
E 2
	}
D 2
	return 0;
E 2
I 2
D 12
	return (count);
E 12
I 12

	return 1;
E 12
E 2
}

/*
D 2
 * get_fs_info:
 *
 * get all the information available on a file system
E 2
I 2
 * Get all the information available on an LFS file system.
D 12
 * Returns an array of FS_INFO structures, NULL on error.
E 12
I 12
 * Returns an pointer to an FS_INFO structure, NULL on error.
E 12
E 2
 */
D 2
int
get_fs_info (lstatfsp, fspp, count)
	struct  statfs  *lstatfsp;	/* IN: array of statfs structs */
	FS_INFO **fspp;			/* OUT: resulting array of FS_INFOs */
	int	count;			/* IN: number of file systems */
E 2
I 2
FS_INFO *
D 10
get_fs_info (lstatfsp, count)
E 10
I 10
D 12
get_fs_info (lstatfsp, count, use_mmap)
E 10
	struct statfs *lstatfsp;	/* IN: array of statfs structs */
	int count;			/* IN: number of file systems */
E 12
I 12
get_fs_info (lstatfsp, use_mmap)
	struct statfs *lstatfsp;	/* IN: pointer to statfs struct */
E 12
I 10
	int use_mmap;			/* IN: mmap or read */
E 10
E 2
{
I 2
D 12
	FS_INFO	*fp, *fsp;
E 12
I 12
	FS_INFO	*fsp;
E 12
E 2
	int	i;
D 2
	caddr_t	ifp;
	FS_INFO	*fsp;
E 2
	
D 2
	*fspp = (FS_INFO *)malloc(count * sizeof(FS_INFO));
E 2
I 2
D 10
	fsp = (FS_INFO *)malloc(count * sizeof(FS_INFO));
E 10
I 10
D 12
	fsp = (FS_INFO *)calloc(count, sizeof(FS_INFO));
E 12
I 12
	fsp = (FS_INFO *)malloc(sizeof(FS_INFO));
	if (fsp == NULL)
		return NULL;
	bzero(fsp, sizeof(FS_INFO));
E 12
E 10
E 2

D 2
	for (i = 0 ; i < count ; i++) {
		fsp = *fspp + i;
		statfsp = lstatfsp + i;
		lfsp = (struct lfs *)malloc (LFS_SBPAD);
		if (get_superblock (fsp, lfsp) < 0) {
			perror("get_fs_info: get_superblock failed");
			return -1;
		}
		fsp->fi_daddr_shift = lfsp->lfs_bshift - lfsp->lfs_fsbtodb;
		if (get_ifile (fsp) < 0) {
			perror("get_fs_info: get_ifile failed");
			return -1;
		}
E 2
I 2
D 12
	for (fp = fsp, i = 0; i < count; ++i, ++fp) {
		fp->fi_statfsp = lstatfsp++;
		if (get_superblock (fp, &fp->fi_lfs))
			err(1, "get_fs_info: get_superblock failed");
		fp->fi_daddr_shift =
		     fp->fi_lfs.lfs_bshift - fp->fi_lfs.lfs_fsbtodb;
D 10
		get_ifile (fp);
E 10
I 10
		get_ifile (fp, use_mmap);
E 10
E 2
	}
E 12
I 12
	fsp->fi_statfsp = lstatfsp;
	if (get_superblock (fsp, &fsp->fi_lfs))
		err(1, "get_fs_info: get_superblock failed");
	fsp->fi_daddr_shift =
	     fsp->fi_lfs.lfs_bshift - fsp->fi_lfs.lfs_fsbtodb;
	get_ifile (fsp, use_mmap);
E 12
D 2
	return 0;
E 2
I 2
	return (fsp);
E 2
}

D 2
/* this is needed temporarily, because of the bug in mmap'ed files */
E 2
I 2
/*
 * If we are reading the ifile then we need to refresh it.  Even if
 * we are mmapping it, it might have grown.  Finally, we need to 
 * refresh the file system information (statfs) info.
 */
E 2
void
D 2
free_fs_info (fsp, count)
	FS_INFO *fsp;	/* IN: array of fs_infos we will dispose of */
	int	count;	/* IN: number of file systems */
E 2
I 2
D 10
reread_fs_info(fsp, count)
E 10
I 10
D 12
reread_fs_info(fsp, count, use_mmap)
E 10
	FS_INFO *fsp;	/* IN: array of fs_infos to free */
	int count;	/* IN: number of file systems */
E 12
I 12
reread_fs_info(fsp, use_mmap)
	FS_INFO *fsp;	/* IN: prointer fs_infos to reread */
E 12
I 11
	int use_mmap;
E 11
E 2
{
D 2
	int	i;
	caddr_t	fsp_base = (caddr_t)fsp;
E 2
I 2
	int i;
E 2
	
D 2
	for (i = 0 ; i < count ; i++, fsp++) {
		/* free superblock */
		free (lfsp);
		/* sdp points to the beginning of the ifile area */
#ifndef MMAP_WORKS
		free (cip);
E 2
I 2
D 12
	for (i = 0; i < count; ++i, ++fsp) {
		if (statfs(fsp->fi_statfsp->f_mntonname, fsp->fi_statfsp))
			err(0, "reread_fs_info: statfs failed");
D 10
#ifdef MMAP_WORKS
		if (munmap(fsp->fi_cip, fsp->fi_ifile_length) < 0)
			err(0, "reread_fs_info: munmap failed");
E 2
#else
D 2
		if (munmap (cip, ifile_length) < 0) {
			perror("free_fs_info: munmap failed\n");
		}
E 2
I 2
		free (fsp->fi_cip);
E 2
#endif /* MMAP_WORKS */
I 2
		get_ifile (fsp);
E 10
I 10
		get_ifile (fsp, use_mmap);
E 10
E 2
	}
E 12
I 12
	if (statfs(fsp->fi_statfsp->f_mntonname, fsp->fi_statfsp))
D 13
		err(0, "reread_fs_info: statfs failed");
E 13
I 13
		err(1, "reread_fs_info: statfs failed");
E 13
	get_ifile (fsp, use_mmap);
E 12
D 2
	
	free (fsp_base);
E 2
}

/* 
D 2
 * get_superblock: 
 *    gets the superblock from disk (possibly in face of errors) 
E 2
I 2
 * Gets the superblock from disk (possibly in face of errors) 
E 2
 */
int
get_superblock (fsp, sbp)
D 2
	FS_INFO *fsp;	/* IN: array of fs_infos we will dispose of */
	struct	lfs	*sbp;
E 2
I 2
	FS_INFO *fsp;		/* local file system info structure */
	struct lfs *sbp;
E 2
{
D 2
        int 	fid;
	char	mntfromname[MNAMELEN+1];
E 2
I 2
	char mntfromname[MNAMELEN+1];
        int fid;
E 2

	strcpy(mntfromname, "/dev/r");
D 2
	strcat(mntfromname, statfsp->f_mntfromname+5);
E 2
I 2
	strcat(mntfromname, fsp->fi_statfsp->f_mntfromname+5);
E 2

	if ((fid = open(mntfromname, O_RDONLY, (mode_t)0)) < 0) {
D 2
		perror("get_superblock: bad open");
		return -1;
E 2
I 2
		err(0, "get_superblock: bad open");
		return (-1);
E 2
	}

D 2
	if(lseek (fid, LFS_LABELPAD, SEEK_SET) != LFS_LABELPAD) {
		perror("get_superblock: bad seek");
		return -1;
	}
	if(read (fid, (char *)sbp, LFS_SBPAD) != LFS_SBPAD) {
		perror("get_superblock: bad read");
		return -1;
	}
E 2
I 2
	get(fid, LFS_LABELPAD, sbp, sizeof(struct lfs));
E 2
	close (fid);
	
D 2
	return 0;
E 2
I 2
	return (0);
E 2
}

/* 
D 2
 * get_ifile: 
 *    This function will map the ifile into memory.  It returns
 * NULL on failure.
E 2
I 2
 * This function will map the ifile into memory.  It causes a
 * fatal error on failure.
E 2
 */
D 2
int
E 2
I 2
void
E 2
D 10
get_ifile (fsp)
E 10
I 10
get_ifile (fsp, use_mmap)
E 10
	FS_INFO	*fsp;
I 10
	int use_mmap;

E 10
{
D 2
	int	fid;
	int	count;
	caddr_t	ifp = NULL;
	char    *ifile_name;
	struct	stat file_stat;
E 2
I 2
	struct stat file_stat;
	caddr_t ifp;
	char *ifile_name;
	int count, fid;
E 2

D 2
	ifile_name = (char *)
		malloc(strlen(statfsp->f_mntonname)+strlen(IFILE_NAME)+2);
	strcpy(ifile_name, statfsp->f_mntonname);
	strcat(ifile_name, "/");
	strcat(ifile_name, IFILE_NAME);
E 2
I 2
	ifp = NULL;
D 5
	sync();
E 5
	ifile_name = malloc(strlen(fsp->fi_statfsp->f_mntonname) +
	    strlen(IFILE_NAME)+2);
	strcat(strcat(strcpy(ifile_name, fsp->fi_statfsp->f_mntonname), "/"),
	    IFILE_NAME);
E 2

D 2
	if ((fid = open(ifile_name, O_RDWR, (mode_t)0)) < 0) {
		perror("get_ifile: bad open");
		return -1;
	}
E 2
I 2
	if ((fid = open(ifile_name, O_RDWR, (mode_t)0)) < 0)
		err(1, "get_ifile: bad open");
E 2

D 2
	if(fstat (fid, &file_stat)) {
		perror("get_ifile: fstat failed");
		return -1;
	}
	ifile_length = file_stat.st_size;
E 2
I 2
	if (fstat (fid, &file_stat))
		err(1, "get_ifile: fstat failed");
E 2

I 2
D 10
	fsp->fi_ifile_length = file_stat.st_size;
E 10
I 10
	if (use_mmap && file_stat.st_size == fsp->fi_ifile_length) {
		(void) close(fid);
		return;
	}
E 10

E 2
	/* get the ifile */
D 10
#ifndef MMAP_WORKS
D 2
	ifp = (caddr_t)malloc (ifile_length);
	if (ifp == 0) {
		perror ("get_ifile: malloc failed, out of memory?"); 
		return -1;
	}
	count = read (fid, ifp, ifile_length);
E 2
I 2
	if (!(ifp = malloc ((size_t)fsp->fi_ifile_length)))
		err (1, "get_ifile: malloc failed"); 
E 10
I 10
	if (use_mmap) {
		if (fsp->fi_cip)
			munmap((caddr_t)fsp->fi_cip, fsp->fi_ifile_length);
		ifp = mmap ((caddr_t)0, file_stat.st_size,
		    PROT_READ|PROT_WRITE, 0, fid, (off_t)0);
		if (ifp ==  (caddr_t)(-1))
			err(1, "get_ifile: mmap failed");
	} else {
		if (fsp->fi_cip)
			free(fsp->fi_cip);
		if (!(ifp = malloc (file_stat.st_size)))
			err (1, "get_ifile: malloc failed"); 
E 10
redo_read:
D 10
	count = read (fid, ifp, (size_t) fsp->fi_ifile_length);
E 10
I 10
		count = read (fid, ifp, (size_t) file_stat.st_size);
E 10
E 2

D 2
	if (count != ifile_length) {
		perror("get_ifile: bad ifile read"); 
		return -1;
E 2
I 2
D 10
	if (count < 0)
		err(1, "get_ifile: bad ifile read"); 
	else if (count < (int)fsp->fi_ifile_length) {
		err(0, "get_ifile");
		if (lseek(fid, 0, SEEK_SET) < 0)
			err(1, "get_ifile: bad ifile lseek"); 
		goto redo_read;
E 10
I 10
		if (count < 0)
			err(1, "get_ifile: bad ifile read"); 
		else if (count < file_stat.st_size) {
			err(0, "get_ifile");
			if (lseek(fid, 0, SEEK_SET) < 0)
				err(1, "get_ifile: bad ifile lseek"); 
			goto redo_read;
		}
E 10
E 2
	}
D 10
#else	/* MMAP_WORKS */
D 2
	ifp = mmap ((caddr_t)0, ifile_length, PROT_READ|PROT_WRITE,
E 2
I 2
	ifp = mmap ((caddr_t)0, (size_t) fsp->fi_ifile_length, PROT_READ|PROT_WRITE,
E 2
		MAP_FILE|MAP_SHARED, fid, (off_t)0);
D 2
	if (ifp < 0) {
		perror("get_ifile: mmap failed");
		return NULL;
	}
E 2
I 2
	if (ifp < 0)
		err(1, "get_ifile: mmap failed");
E 2
#endif	/* MMAP_WORKS */

E 10
I 10
	fsp->fi_ifile_length = file_stat.st_size;
E 10
	close (fid);

D 2
	cip = (CLEANERINFO*)ifp;
	segusep = (SEGUSE*)(ifp + CLEANSIZE(lfsp));
	ifilep  = (IFILE*)(ifp + CLEANSIZE(lfsp) + SEGTABSIZE(lfsp));
	/* # of bytes in ifile table */
	ifile_count = ifile_length - (CLEANSIZE(lfsp) + SEGTABSIZE(lfsp));
	/* # of ifile entries in ifile table */
	ifile_count = (ifile_count / lfsp->lfs_bsize) * lfsp->lfs_ifpb;
E 2
I 2
	fsp->fi_cip = (CLEANERINFO *)ifp;
	fsp->fi_segusep = (SEGUSE *)(ifp + CLEANSIZE(fsp));
	fsp->fi_ifilep  = (IFILE *)((caddr_t)fsp->fi_segusep + SEGTABSIZE(fsp));

	/*
	 * The number of ifile entries is equal to the number of blocks
	 * blocks in the ifile minus the ones allocated to cleaner info
	 * and segment usage table multiplied by the number of ifile
	 * entries per page.
	 */
	fsp->fi_ifile_count = (fsp->fi_ifile_length >> fsp->fi_lfs.lfs_bshift -
	    fsp->fi_lfs.lfs_cleansz - fsp->fi_lfs.lfs_segtabsz) *
	    fsp->fi_lfs.lfs_ifpb;

E 2
	free (ifile_name);
D 2
	return 0;
E 2
}

D 2

E 2
/*
D 2
 * segmapv:
 *
 *   This function will scan a segment and return a list of
E 2
I 2
 * This function will scan a segment and return a list of
E 2
 * <inode, blocknum> pairs which indicate which blocks were
D 2
 * contained as live data within the segment at some point
 * (it may have "died" since then).  Any given pair will be 
 * listed at most once.
E 2
I 2
 * contained as live data within the segment when the segment
 * summary was read (it may have "died" since then).  Any given
 * pair will be listed at most once.
E 2
 */
int 
D 5
lfs_segmapv(fsp, seg, seg_buf, blocks, bcount, inodes, icount)
E 5
I 5
lfs_segmapv(fsp, seg, seg_buf, blocks, bcount)
E 5
D 2
	FS_INFO *fsp;		/* pointer to super block */
	int	seg;		/* the segment id */
	caddr_t	seg_buf;	/* the buffer containing the segment's data */
				/* OUT: array of block_info for live blocks */
	BLOCK_INFO	**blocks;
	int	*bcount;	/* OUT: number of active blocks in segment */
				/* OUT: array of inode_info for live inodes */
	INODE_INFO	**inodes;
	int	*icount;	/* OUT: number of active inodes in segment */
E 2
I 2
	FS_INFO *fsp;		/* pointer to local file system information */
	int seg;		/* the segment number */
	caddr_t seg_buf;	/* the buffer containing the segment's data */
	BLOCK_INFO **blocks;	/* OUT: array of block_info for live blocks */
	int *bcount;		/* OUT: number of active blocks in segment */
D 5
	INODE_INFO **inodes;	/* OUT: array of inode_info for live inodes */
	int *icount; 		/* OUT: number of active inodes in segment */
E 5
E 2
{
D 2
	caddr_t	s;
	caddr_t	endofseg;
	int	nextsum;
	u_long	sb_off;
	time_t	timestamp;
	
	*bcount = 0;
	*blocks = (BLOCK_INFO *)malloc (sizeof(BLOCK_INFO));
	
	*icount = 0;
	*inodes = (INODE_INFO *)malloc(sizeof(INODE_INFO));
E 2
I 2
	BLOCK_INFO *bip;
D 5
	INODE_INFO *iip;
E 5
	SEGSUM *sp;
	SEGUSE *sup;
I 8
	FINFO *fip;
E 8
	struct lfs *lfsp;
	caddr_t s, segend;
	daddr_t pseg_addr, seg_addr;
D 5
	int nblocks, num_iblocks;
E 5
I 5
D 8
	int nelem, nblocks;
E 8
I 8
D 16
	int i, nelem, nblocks, sumsize;
E 16
I 16
	int i, nelem, nblocks, nsegs, sumsize;
E 16
E 8
E 5
	time_t timestamp;
E 2

D 2
	sb_off = (SEGUSE_ENTRY(lfsp, segusep, seg)->su_flags & SEGUSE_SUPERBLOCK) ?
		LFS_SBPAD : 0;
E 2
I 2
	lfsp = &fsp->fi_lfs;
D 5
	num_iblocks = lfsp->lfs_ssize;
	if (!(bip = malloc(lfsp->lfs_ssize * sizeof(BLOCK_INFO))))
E 5
I 5
	nelem = 2 * lfsp->lfs_ssize;
	if (!(bip = malloc(nelem * sizeof(BLOCK_INFO))))
E 5
		goto err0;
D 5
	if (!(iip = malloc(lfsp->lfs_ssize * sizeof(INODE_INFO))))
		goto err1;
E 5
E 2

D 2
	for (s = seg_buf + sb_off, endofseg = seg_buf + seg_size(lfsp), 
	     timestamp = 0 ; 
	     s < endofseg ; 
	     s += pseg_size (fsp, (SEGSUM*)s)) {
		BLOCK_INFO	*pblocks;
		int		pbcount;
		INODE_INFO	*pinodes;
		int		picount;
E 2
I 2
	sup = SEGUSE_ENTRY(lfsp, fsp->fi_segusep, seg);
	s = seg_buf + (sup->su_flags & SEGUSE_SUPERBLOCK ? LFS_SBPAD : 0);
	seg_addr = sntoda(lfsp, seg);
	pseg_addr = seg_addr + (sup->su_flags & SEGUSE_SUPERBLOCK ? btodb(LFS_SBPAD) : 0);
#ifdef VERBOSE
		printf("\tsegment buffer at: 0x%x\tseg_addr 0x%x\n", s, seg_addr);
#endif /* VERBOSE */
E 2

I 2
	*bcount = 0;
D 5
	*icount = 0;
E 5
D 16
	for (segend = seg_buf + seg_size(lfsp), timestamp = 0; s < segend; ) {
E 16
I 16
	for (nsegs = 0, timestamp = 0; nsegs < sup->su_nsums; nsegs++) {
E 16
		sp = (SEGSUM *)s;
I 8

I 16
		nblocks = pseg_valid(fsp, sp);
		if (nblocks <= 0) {
			printf("Warning: invalid segment summary at 0x%x\n",
			    pseg_addr);
			break;
		}

E 16
E 8
E 2
#ifdef VERBOSE
D 2
		printf("lfs_segmapv: seg_buf = 0x%x, pseg_buf = 0x%x, offset = %lu (0x%x), pseg = \n\t",
			(u_int)seg_buf, (u_int)s, 
			(u_int)s - (u_int)seg_buf - (u_int)sb_off,
			(u_int)s - (u_int)seg_buf - (u_int)sb_off);
/* this can cause core dumps when printing an invalid segsum
 *		print_SEGSUM ((SEGSUM*)s);
 *		printf("\n");
 *		printf("pseg_size = %lu\n", pseg_size(fsp, (SEGSUM*)s));
 */
E 2
I 2
		printf("\tpartial at: 0x%x\n", pseg_addr);
		print_SEGSUM(lfsp, sp);
E 2
		fflush(stdout);
#endif /* VERBOSE */

D 2
		/* we have hit the end of the valid data */
		if (! pseg_valid (fsp, (SEGSUM*)s)) break;
E 2
I 2
D 16
		nblocks = pseg_valid(fsp, sp);
		if (nblocks <= 0)
			break;
E 2

E 16
D 2
		/* we have gone back in time and hit old data */
		if (timestamp > ((SEGSUM*)s)->ss_create) break;

E 2
I 2
		/* Check if we have hit old data */
		if (timestamp > ((SEGSUM*)s)->ss_create)
			break;
E 2
		timestamp = ((SEGSUM*)s)->ss_create;

I 8
#ifdef DIAGNOSTIC
		/* Verfiy size of summary block */
		sumsize = sizeof(SEGSUM) +
		    (sp->ss_ninos + INOPB(lfsp) - 1) / INOPB(lfsp);
D 16
		for (fip = (FINFO *)(sp + 1); i < sp->ss_nfinfo; ++i) {
E 16
I 16
		for (i = 0, fip = (FINFO *)(sp + 1); i < sp->ss_nfinfo; ++i) {
E 16
			sumsize += sizeof(FINFO) +
			    (fip->fi_nblocks - 1) * sizeof(daddr_t);
			fip = (FINFO *)(&fip->fi_blocks[fip->fi_nblocks]);
		}
		if (sumsize > LFS_SUMMARY_SIZE) {
			fprintf(stderr,
			    "Segment %d summary block too big: %d\n",
			    seg, sumsize);
			exit(1);
		}
#endif

E 8
D 2
		/* get the block and inode list */
		pseg_blocks (fsp, seg, (SEGSUM*)s, seg_buf, 
			&pblocks, &pbcount);
		pseg_bjoin  (fsp, blocks, bcount, pblocks, pbcount);
E 2
I 2
D 5
		/*
		 * Right now we die if we run out of room, we could probably
		 * recover if we were smart.
		 */
		if (*icount + sp->ss_ninos > num_iblocks) {
			num_iblocks = *icount + sp->ss_ninos;
			iip = realloc (iip, num_iblocks * sizeof(INODE_INFO));
			if (!iip)
				goto err1;
E 5
I 5
		if (*bcount + nblocks + sp->ss_ninos > nelem) {
			nelem = *bcount + nblocks + sp->ss_ninos;
			bip = realloc (bip, nelem * sizeof(BLOCK_INFO));
			if (!bip)
				goto err0;
E 5
		}
D 5
		add_inodes(fsp, iip, icount, sp, seg_buf, seg_addr);
E 5
		add_blocks(fsp, bip, bcount, sp, seg_buf, seg_addr, pseg_addr);
I 5
		add_inodes(fsp, bip, bcount, sp, seg_buf, seg_addr);
E 5
		pseg_addr += fsbtodb(lfsp, nblocks) +
		    bytetoda(fsp, LFS_SUMMARY_SIZE);
		s += (nblocks << lfsp->lfs_bshift) + LFS_SUMMARY_SIZE;
	}
D 5
	qsort(iip, *icount, sizeof(INODE_INFO), ii_compare);
E 5
	qsort(bip, *bcount, sizeof(BLOCK_INFO), bi_compare);
D 5
	toss(iip, icount, sizeof(INODE_INFO), ii_toss, NULL);
E 5
	toss(bip, bcount, sizeof(BLOCK_INFO), bi_toss, NULL);
#ifdef VERBOSE
	{
		BLOCK_INFO *_bip;
D 5
		INODE_INFO *_iip;
E 5
		int i;
E 2

D 2
		pseg_inodes (fsp, seg, (SEGSUM*)s, seg_buf, 
			&pinodes, &picount);
		pseg_ijoin  (fsp, inodes, icount, pinodes, picount);
		
		/* free the temporary tables */
		free (pblocks);
		free (pinodes);
E 2
I 2
		printf("BLOCK INFOS\n");
		for (_bip = bip, i=0; i < *bcount; ++_bip, ++i)
			PRINT_BINFO(_bip);
D 5
		printf("INODE INFOS\n");
		for (_iip = iip, i=0; i < *icount; ++_iip, ++i)
			PRINT_IINFO(1, _iip);
E 5
E 2
	}
I 2
#endif
	*blocks = bip;
D 5
	*inodes = iip;
E 5
	return (0);

D 5
err1:	free(bip);
E 5
err0:	*bcount = 0;
D 5
	*icount = 0;
E 5
	return (-1);
E 2
	
}

/* 
D 2
 * this will parse a partial segment and create a vector of block_info's
 * for live data and a vector of inode_info's for live inodes.  It will 
 * not include blocks or inodes from files with new version numbers.  
E 2
I 2
 * This will parse a partial segment and fill in BLOCK_INFO structures
 * for each block described in the segment summary.  It will not include
 * blocks or inodes from files with new version numbers.  
E 2
 */
void
D 2
pseg_blocks (fsp, seg, s, seg_buf, blocks, count)
E 2
I 2
add_blocks (fsp, bip, countp, sp, seg_buf, segaddr, psegaddr)
E 2
	FS_INFO *fsp;		/* pointer to super block */
D 2
	int	seg;		/* the segment id */
	SEGSUM	*s;		/* (unvalidated) segsum pointer */
	caddr_t	seg_buf;	/* the buffer containing the segment's data */
				/* OUT: array of block_info for live blocks */
	BLOCK_INFO	**blocks;
	int	*count;		/* OUT: number of active blocks in segment */
E 2
I 2
	BLOCK_INFO *bip;	/* Block info array */
	int *countp;		/* IN/OUT: number of blocks in array */
	SEGSUM	*sp;		/* segment summmary pointer */
	caddr_t seg_buf;	/* buffer containing segment */
	daddr_t segaddr;	/* address of this segment */
	daddr_t psegaddr;	/* address of this partial segment */
E 2
{
D 2
	FINFO	**finfos;
	int	finfoc;
	int	blockc;
	int	i;
	int	j;
	int	ninob;		/* number of inode blocks passed */
	daddr_t	seg_daddr;
	daddr_t	*cur_iaddrp;	/* pointer to current inode block */
	u_long	offset;		/* the offset (in bytes) within the segment */
E 2
I 2
	IFILE	*ifp;
	FINFO	*fip;
	caddr_t	bp;
D 5
	daddr_t	*dp;
	daddr_t *iaddrp;	/* pointer to current inode block */
E 5
I 5
	daddr_t	*dp, *iaddrp;
E 5
	int db_per_block, i, j;
I 16
	int db_frag;
E 16
	u_long page_size;
I 16
long *lp;
E 16
E 2

D 2
	*count = 0;
	*blocks = NULL;
	
	pseg_finfos (fsp, s, &finfos, &finfoc);

E 2
#ifdef VERBOSE
D 2
	for(i=0;i<finfoc;i++){print_FINFO(finfos[i]);printf("\n");fflush(stdout);}
	printf("pseg_blocks: finfoc = %d\n", finfoc);fflush(stdout);
E 2
I 2
	printf("FILE INFOS\n");
E 2
#endif
I 2
	db_per_block = fsbtodb(&fsp->fi_lfs, 1);
	page_size = fsp->fi_lfs.lfs_bsize;
	bp = seg_buf + datobyte(fsp, psegaddr - segaddr) + LFS_SUMMARY_SIZE;
	bip += *countp;
	psegaddr += bytetoda(fsp, LFS_SUMMARY_SIZE);
	iaddrp = (daddr_t *)((caddr_t)sp + LFS_SUMMARY_SIZE);
	--iaddrp;
	for (fip = (FINFO *)(sp + 1), i = 0; i < sp->ss_nfinfo;
	    ++i, fip = (FINFO *)(&fip->fi_blocks[fip->fi_nblocks])) {
E 2

D 2
	/* count how many blocks are held by live FINFO's */
	for (i = 0, blockc = 0 ; i < finfoc ; ++i)
		if (finfos[i]->fi_version == 
		    IFILE_ENTRY(lfsp, ifilep, finfos[i]->fi_ino)->if_version) 
			blockc += finfos[i]->fi_nblocks;

	if (finfoc == 0 || blockc == 0) return;
	
	ninob = 0;
	offset = LFS_SUMMARY_SIZE + ((u_int)s - (u_int)seg_buf) + 
		s->ss_next * datobyte(fsp, 1<<lfsp->lfs_bshift);
	cur_iaddrp = (daddr_t*)(s->ss_ninos == 0 ? 0 :
	    (char *)s + LFS_SUMMARY_SIZE - sizeof(daddr_t));
	seg_daddr = sntoda(lfsp, seg);
	*blocks = (BLOCK_INFO *)malloc (blockc*sizeof(BLOCK_INFO));

	for (i = 0 ; i < finfoc ; i ++) {
		FINFO		*f = finfos[i];

		if (f->fi_version != IFILE_ENTRY(lfsp, ifilep, f->fi_ino)->if_version) 
E 2
I 2
		ifp = IFILE_ENTRY(&fsp->fi_lfs, fsp->fi_ifilep, fip->fi_ino);
		PRINT_FINFO(fip, ifp);
		if (ifp->if_version > fip->fi_version)
E 2
			continue;
D 2

#ifdef VERBOSE
		printf("finfo %d = ", i);
		print_FINFO(f);
		printf("\n");
		fflush(stdout);
		printf("IFILE entry for file %d = ", f->fi_ino);
		print_IFILE (IFILE_ENTRY(lfsp, ifilep, f->fi_ino));
		printf("\n");
		fflush(stdout);
#endif
		for (j = 0 ; j < finfos[i]->fi_nblocks ; j ++) {
			BLOCK_INFO	*b = &(*blocks)[*count];
		
			/*
			 * XXX: 
			 * this changes if we have variable size blocks
			 */
			for (;cur_iaddrp && 
			    seg_daddr + bytetoda(fsp, offset) == *cur_iaddrp; 
			    offset += datobyte(fsp, 1<<lfsp->lfs_bshift)) {
				if (ninob <= (s->ss_ninos + INOPB(lfsp) - 1) 
				    / INOPB(lfsp)) {
					++ninob;
					--cur_iaddrp;
				} else
					cur_iaddrp = NULL;
E 2
I 2
		dp = &(fip->fi_blocks[0]);
		for (j = 0; j < fip->fi_nblocks; j++, dp++) {
			while (psegaddr == *iaddrp) {
				psegaddr += db_per_block;
				bp += page_size;
				--iaddrp;
E 2
			}
D 2
			b->bi_inode = f->fi_ino;
			b->bi_lbn = f->fi_blocks[j];
			b->bi_daddr = seg_daddr + bytetoda(fsp, offset);
			b->bi_segcreate = s->ss_create;
			b->bi_bp = seg_buf + offset;
			
			(*count) ++;
			offset += blocksize(fsp, b->bi_lbn);
#ifdef VERBOSE
			printf("\tb[%d] = ", j);
			print_BLOCK_INFO(b);
			printf("\n");
			fflush(stdout);
#endif
E 2
I 2
			bip->bi_inode = fip->fi_ino;
			bip->bi_lbn = *dp;
			bip->bi_daddr = psegaddr;
			bip->bi_segcreate = (time_t)(sp->ss_create);
			bip->bi_bp = bp;
I 7
			bip->bi_version = ifp->if_version;
E 7
D 16
			psegaddr += db_per_block;
			bp += page_size;
E 16
I 16
			if (fip->fi_lastlength == page_size) {
				bip->bi_size = page_size;
				psegaddr += db_per_block;
				bp += page_size;
			} else {
				db_frag = fragstodb(&(fsp->fi_lfs), 
				    numfrags(&(fsp->fi_lfs),
				    fip->fi_lastlength));
#ifdef VERBOSE
				printf("lastlength, frags: %d, %d, %d\n", 
				    fip->fi_lastlength, temp,
				    bytetoda(fsp, temp));
				fflush(stdout);
#endif
				bip->bi_size = fip->fi_lastlength;
				bp += fip->fi_lastlength;
				psegaddr += db_frag;
			}
E 16
			++bip;
			++(*countp);
E 2
		}
	}
D 2
	free (finfos);
E 2
}

I 2
/*
 * For a particular segment summary, reads the inode blocks and adds
 * INODE_INFO structures to the array.  Returns the number of inodes
 * actually added.
 */
E 2
void
D 2
pseg_inodes (fsp, seg, s, seg_buf, inodes, count)
E 2
I 2
D 5
add_inodes (fsp, iip, countp, sp, seg_buf, seg_addr)
E 5
I 5
add_inodes (fsp, bip, countp, sp, seg_buf, seg_addr)
E 5
E 2
	FS_INFO *fsp;		/* pointer to super block */
D 2
	int	seg;		/* the segment id */
	SEGSUM	*s;		/* (unvalidated) segsum pointer */
E 2
I 2
D 5
	INODE_INFO *iip;
E 5
I 5
	BLOCK_INFO *bip;	/* block info array */
E 5
	int *countp;		/* pointer to current number of inodes */
	SEGSUM *sp;		/* segsum pointer */
E 2
	caddr_t	seg_buf;	/* the buffer containing the segment's data */
D 2
				/* OUT: array of inode_info for live inodes */
	INODE_INFO	**inodes;
	int	*count;		/* OUT: number of active inodes in segment */
E 2
I 2
	daddr_t	seg_addr;	/* disk address of seg_buf */
E 2
{
D 2
	int	i;
	ino_t	inum;
	daddr_t	*daddrp, i_daddr, seg_daddr;
	struct	dinode	*di;
E 2
I 2
	struct dinode *di;
	struct lfs *lfsp;
	IFILE *ifp;
D 5
	INODE_INFO *ip;
E 5
I 5
	BLOCK_INFO *bp;
E 5
	daddr_t	*daddrp;
	ino_t inum;
	int i;
E 2
	
D 2
	*count = 0;
	*inodes = NULL;

	if (s->ss_ninos <= 0) return;
E 2
I 2
	if (sp->ss_ninos <= 0)
		return;
E 2
	
D 2
	*inodes = (INODE_INFO *)malloc (s->ss_ninos * sizeof(INODE_INFO));

	seg_daddr = sntoda(lfsp, seg);

E 2
I 2
D 5
	ip = iip + *countp;
E 5
I 5
	bp = bip + *countp;
E 5
	lfsp = &fsp->fi_lfs;
E 2
#ifdef VERBOSE
D 2
	printf("pseg_inodes:\n");
	print_SEGSUM(s);
	printf("\n");
	fflush(stdout);
E 2
I 2
D 5
	(void) printf("INODE_INFOS:\n");
E 5
I 5
	(void) printf("INODES:\n");
E 5
E 2
#endif
D 2

	daddrp = (daddr_t *)((caddr_t)s + LFS_SUMMARY_SIZE);

	for (i = 0 ; i < s->ss_ninos ; ++i) {

E 2
I 2
	daddrp = (daddr_t *)((caddr_t)sp + LFS_SUMMARY_SIZE);
	for (i = 0; i < sp->ss_ninos; ++i) {
E 2
		if (i % INOPB(lfsp) == 0) {
D 2
			i_daddr = *--daddrp;
			if (datosn(lfsp, i_daddr) != seg ||
			    datobyte(fsp, i_daddr - seg_daddr) > seg_size(lfsp)) {
				printf("pseg_inodes: bad i_daddr\n");
				print_SEGSUM(s);
				printf("\n");
				fflush(stdout);
				printf("i_daddr = %d, seg_daddr = %d, offset = %d, pseg_size = %d\n",
				    i_daddr, seg_daddr, i_daddr - seg_daddr, 
				    pseg_size(fsp, (SEGSUM*)s));
				fflush(stdout);
			}
			di = (struct dinode *)
				(seg_buf + datobyte(fsp, i_daddr - seg_daddr));
E 2
I 2
			--daddrp;
			di = (struct dinode *)(seg_buf +
			    ((*daddrp - seg_addr) << fsp->fi_daddr_shift));
E 2
		} else 
			++di;
		
D 10
		inum = di->di_inum;
E 10
I 10
		inum = di->di_inumber;
E 10
I 2
D 5
		ip->ii_daddr = *daddrp;
		ip->ii_inode = inum;
		ip->ii_dinode = di;
		ip->ii_segcreate = sp->ss_create;
E 5
I 5
		bp->bi_lbn = LFS_UNUSED_LBN;
		bp->bi_inode = inum;
		bp->bi_daddr = *daddrp;
		bp->bi_bp = di;
		bp->bi_segcreate = sp->ss_create;
E 5
E 2

D 2
		if (IFILE_ENTRY(lfsp, ifilep, inum)->if_daddr == i_daddr) {
			(*inodes)[*count].ii_inode = inum;
			(*inodes)[*count].ii_daddr = i_daddr;
			(*inodes)[*count].ii_segcreate = s->ss_create;
			(*inodes)[*count].ii_dinode = di;
		
			(*count) ++;
E 2
I 2
D 6
		ifp = IFILE_ENTRY(lfsp, fsp->fi_ifilep, inum);
D 5
		PRINT_IINFO(ifp->if_daddr == *daddrp, ip);
E 5
I 5
		PRINT_INODE(ifp->if_daddr == *daddrp, ip);
E 5
		if (ifp->if_daddr == *daddrp) {
E 6
I 6
		if (inum == LFS_IFILE_INUM) {
I 7
			bp->bi_version = 1;	/* Ifile version should be 1 */
E 7
E 6
D 5
			ip++;
E 5
I 5
			bp++;
E 5
			++(*countp);
E 2
D 6
		} 
E 6
I 6
			PRINT_INODE(1, bp);
		} else {
			ifp = IFILE_ENTRY(lfsp, fsp->fi_ifilep, inum);
			PRINT_INODE(ifp->if_daddr == *daddrp, bp);
I 7
			bp->bi_version = ifp->if_version;
E 7
			if (ifp->if_daddr == *daddrp) {
				bp++;
				++(*countp);
			} 
		}
E 6
	}
}

D 2
/* return the size of the partial segment in bytes. */
u_long
pseg_size (fsp, s)
	FS_INFO *fsp;   /* pointer to super block */
	SEGSUM	*s;	/* segsum pointer */
{
	int	i;
	int	j;
	FINFO	**finfos;
	int	finfoc;
	u_long	size = LFS_SUMMARY_SIZE;
	
	pseg_finfos (fsp, s, &finfos, &finfoc);
	for (i = 0 ; i < finfoc ; i ++) 
	for (j = 0 ; j < finfos[i]->fi_nblocks ; j ++) 
		size += blocksize(fsp, finfos[i]->fi_blocks[j]);

	/* inodes are packed INOPB inodes per block */
	/* there can be unused space in an inode block */
	size += datobyte(fsp, fsbtodb(lfsp,1)*((s->ss_ninos+INOPB(lfsp)-1)/INOPB(lfsp)));

	return size;
}

/* 
 * join block list b with list a (eliminating duplicates), leaving result
 * in list a.
 */
void
pseg_bjoin (fsp, ablocks, acount, bblocks, bcount)
	FS_INFO *fsp;   /* pointer to file system info */
				/* INOUT: array of live blocks block_info */
	BLOCK_INFO	**ablocks;
	int	*acount;	/* INOUT: number of active blocks */
				/* IN: array of live blocks block_info */
	BLOCK_INFO	*bblocks;
	int	bcount;	/* IN: number of active blocks */
{
	int	i;
	int	j;
	BLOCK_INFO	*abp;
	BLOCK_INFO	*bbp;

#ifdef VERBOSE
	printf("pseg_bjoin: *acount = %d, bcount = %d\n", *acount, bcount);
/**/
	printf("ablocks = \n");
	for(i=0;i<*acount;i++){print_BLOCK_INFO((*ablocks)+i); printf("\n");}
/**/
	printf("bblocks = \n");
	for(i=0;i<bcount;i++){print_BLOCK_INFO(bblocks+i); printf("\n");}
/**/
	fflush(stdout);
/**/
#endif

	for (i = 0, bbp = bblocks ; i < bcount ; ++i, ++bbp) {
		for (j = 0, abp = *ablocks ; j < *acount ; ++j, ++abp) {
			if (abp->bi_inode == bbp->bi_inode
				&& abp->bi_lbn == bbp->bi_lbn) {
				/* the data is for the same file and logical block */
				if (abp->bi_segcreate < bbp->bi_segcreate)
					*abp = *bbp;
				break;
			}
		}
		if (j == *acount) {
			/* this is a block we haven't seen before */
			*ablocks = (BLOCK_INFO*)
				realloc (*ablocks, sizeof(BLOCK_INFO)*(*acount + 1));
			(*ablocks)[*acount] = *bbp;
			(*acount) ++;
		}
	}
}

/* 
 * join block list b with list a (eliminating duplicates), leaving result
 * in list a.
 */
void
pseg_ijoin (fsp, ainodes, acount, binodes, bcount)
	FS_INFO *fsp;   /* pointer to file system info */
				/* INOUT: array of live inodes inode_info */
	INODE_INFO	**ainodes;
	int	*acount;	/* INOUT: number of active inodes */
				/* IN: array of live inodes inode_info */
	INODE_INFO	*binodes;
	int	bcount;		/* IN: number of active inodes */
{
	int	i;
	int	j;
	daddr_t	daddr;
	INODE_INFO	*aip;
	INODE_INFO	*bip;

	/* we assume that we have no duplicate live inodes on "a" and "b" */
	
	/* eliminate dead inodes from "a" */
	for (i = 0, aip = *ainodes ; i < *acount ; ++aip ) {
		daddr = IFILE_ENTRY(lfsp, ifilep, aip->ii_inode)->if_daddr;
		if (daddr != aip->ii_daddr) 
			*aip = (*ainodes)[--(*acount)];
		else 	i++;
	}

	/* eliminate dead inodes from "b" */
	for (i = 0, bip = binodes ; i < bcount ; ++bip) {
		daddr = IFILE_ENTRY(lfsp, ifilep, bip->ii_inode)->if_daddr;
		if (daddr != bip->ii_daddr) {
			/* don't really need to do this, only we don't want
			   to lose any inodes, just in case */
			INODE_INFO	tmp;
			tmp = *bip;
			*bip = binodes[bcount];
			binodes[bcount] = tmp;
			bcount --;
		}
		else	i++;
	}
	/* append "b" to "a" */
	if (bcount > 0) {
		*ainodes = (INODE_INFO *)realloc ((void *)*ainodes,
			(*acount + bcount + 1)*sizeof(INODE_INFO));
		for (i = 0 ; i < bcount ; i ++)
			(*ainodes)[(*acount)++] = binodes[i];
	}
}

/* is the segsum block valid? return TRUE if it is, FALSE otherwise */
int 
segsum_valid (fsp, ssp)
	FS_INFO *fsp;   /* pointer to file system info */
	SEGSUM	*ssp;	/* pointer to segment summary block */
{
	u_long	sumsum;

	/* check segsum block checksum */
	sumsum = cksum(&ssp->ss_datasum, 
	    LFS_SUMMARY_SIZE - sizeof(ssp->ss_sumsum));

	if (sumsum != ssp->ss_sumsum) return FALSE;
	
	return TRUE;
}

E 2
/*
D 2
 * pseg_valid:
 *
 * returns 1 if the partial segment is valid, and 0 if it is invalid.
 * it uses the checksums to verify validity.
E 2
I 2
 * Checks the summary checksum and the data checksum to determine if the
 * segment is valid or not.  Returns the size of the partial segment if it
 * is valid, * and 0 otherwise.  Use dump_summary to figure out size of the
 * the partial as well as whether or not the checksum is valid.
E 2
 */	 
int
pseg_valid (fsp, ssp)
	FS_INFO *fsp;   /* pointer to file system info */
D 2
	SEGSUM	*ssp;	/* pointer to segment summary block */
E 2
I 2
	SEGSUM *ssp;	/* pointer to segment summary block */
E 2
{
D 2
	u_long	datasum;
	u_long	size;
	int	nblocks;
	int	i;
	u_long	*datap;
E 2
	caddr_t	p;
I 2
	int i, nblocks;
	u_long *datap;
I 16

	if (ssp->ss_magic != SS_MAGIC)
		return(0);
E 16
I 8
D 11
	SEGUSE *sup;
E 11
E 8
E 2

D 2
	/* check segsum block checksum */
	if (segsum_valid (fsp, ssp) == FALSE) return FALSE;

	return TRUE;
E 2
I 2
D 9
	if ((nblocks = dump_summary(&fsp->fi_lfs, ssp, 0, NULL)) <= 0)
E 9
I 9
	if ((nblocks = dump_summary(&fsp->fi_lfs, ssp, 0, NULL)) <= 0 ||
	    nblocks > fsp->fi_lfs.lfs_ssize - 1)
E 9
		return(0);
E 2
		
D 2
	/* check data/inode block(s) checksum too... */
	size = pseg_size (fsp, ssp);
	nblocks = size/fsbtodb(lfsp, 1);
	datap = (u_long*)malloc(sizeof(u_long)*nblocks);
E 2
I 2
	/* check data/inode block(s) checksum too */
	datap = (u_long *)malloc(nblocks * sizeof(u_long));
E 2
	p = (caddr_t)ssp + LFS_SUMMARY_SIZE;
D 2
	for (i = 0 ; i < nblocks ; i ++) {
E 2
I 2
	for (i = 0; i < nblocks; ++i) {
E 2
		datap[i] = *((u_long *)p);
D 2
		p += lfsp->lfs_bsize;
E 2
I 2
		p += fsp->fi_lfs.lfs_bsize;
E 2
	}
D 2
	datasum = cksum ((void *)datap, nblocks*sizeof(u_long));
	if (datasum != ssp->ss_datasum) return FALSE;
E 2
I 2
	if (cksum ((void *)datap, nblocks * sizeof(u_long)) != ssp->ss_datasum)
		return (0);
E 2
	
D 2
	return TRUE;
E 2
I 2
	return (nblocks);
E 2
}

D 2
/* get array of FINFO pointers for partial segment */
void
pseg_finfos (fsp, ssp, finfos, count)
	FS_INFO	*fsp;   /* pointer to file system info */
	SEGSUM	*ssp;	/* pointer to segment summary block */
	FINFO	***finfos;	/* OUT: return an array of FINFO pointers */
	int	*count;		/* OUT: return size of array */
{
	caddr_t	p = (caddr_t)ssp + sizeof(SEGSUM);
	int	i;
	FINFO	*fip;
	
	*count = 0;
	*finfos = NULL;
E 2

D 2
	if (ssp->ss_nfinfo > 0)
		*finfos = (FINFO**)malloc (ssp->ss_nfinfo*sizeof(FINFO*));

	for (i = 0 ; i < ssp->ss_nfinfo ; i ++) {
		fip = (FINFO *)p;
		(*finfos)[*count] = fip;
		(*count) ++;
		p += finfo_size (fip);
	}
}

/*
 * blocksize:
 *
 * returns the size (in bytes) of a (logical) block.
 * this is used because lfs uses different block sizes, depending
 * on the logical # of the block.  Lfs uses various sizes so
 * it doesn't need fragments.
 */ 
u_long
blocksize (fsp, index)
	FS_INFO *fsp;   /* pointer to file system info */
	int	index;	/* logical block # w/in file */
{
	return lfsp->lfs_bsize;	/* XXX: blocksize might depend on
					the logical block number */
}

/*
 * finfo_size
 *
 * returns the size in bytes of an FINFO structure 
 */
u_long
finfo_size (finfop)
	FINFO	*finfop;
{
	return sizeof(FINFO) + sizeof(long)*(finfop->fi_nblocks-1);
}
	

E 2
/* #define MMAP_SEGMENT */
/* 
 * read a segment into a memory buffer
 */
int
D 2
mmap_segment (fsp, segment, seg_buf)
	FS_INFO	*fsp;		/* file system information */
	int	segment;	/* the index of the segment to be cleaned */
	caddr_t	*seg_buf;	/* pointer to buffer area */
E 2
I 2
D 10
mmap_segment (fsp, segment, segbuf)
E 10
I 10
mmap_segment (fsp, segment, segbuf, use_mmap)
E 10
	FS_INFO *fsp;		/* file system information */
	int segment;		/* segment number */
	caddr_t *segbuf;	/* pointer to buffer area */
I 10
	int use_mmap;		/* mmap instead of read */
E 10
E 2
{
D 2
	off_t	seg_daddr;	/* base disk address of segment */
	int	fid;		/* fildes for file system device */
	char	mntfromname[MNAMELEN+2];
E 2
I 2
	struct lfs *lfsp;
	int fid;		/* fildes for file system device */
	daddr_t seg_daddr;	/* base disk address of segment */
	off_t seg_byte;
	size_t ssize;
	char mntfromname[MNAMELEN+2];
E 2

I 2
	lfsp = &fsp->fi_lfs;

E 2
	/* get the disk address of the beginning of the segment */
	seg_daddr = sntoda(lfsp, segment);
I 2
	seg_byte = datobyte(fsp, seg_daddr);
	ssize = seg_size(lfsp);
E 2

	strcpy(mntfromname, "/dev/r");
D 2
	strcat(mntfromname, statfsp->f_mntfromname+5);
E 2
I 2
	strcat(mntfromname, fsp->fi_statfsp->f_mntfromname+5);
E 2

	if ((fid = open(mntfromname, O_RDONLY, (mode_t)0)) < 0) {
D 2
		perror("mmap_segment: bad open");
		return -1;
E 2
I 2
		err(0, "mmap_segment: bad open");
		return (-1);
E 2
	}

D 10
#ifdef MMAP_SEGMENT
D 2
	*seg_buf = mmap ((caddr_t)0, seg_size(lfsp), PROT_READ,
		MAP_FILE, fid, (off_t)datobyte(fsp, seg_daddr));
	if ((long)*seg_buf < 0) {
		perror("mmap_segment: mmap failed");
		return NULL;
E 2
I 2
	*segbuf = mmap ((caddr_t)0, seg_size(lfsp), PROT_READ,
	    MAP_FILE, fid, seg_byte);
	if (*(long *)segbuf < 0) {
		err(0, "mmap_segment: mmap failed");
		return (NULL);
E 2
	}
#else /* MMAP_SEGMENT */
E 10
I 10
	if (use_mmap) {
		*segbuf = mmap ((caddr_t)0, seg_size(lfsp), PROT_READ,
		    0, fid, seg_byte);
		if (*(long *)segbuf < 0) {
			err(0, "mmap_segment: mmap failed");
			return (NULL);
		}
	} else {
E 10
D 2
	printf("mmap_segment: seg_daddr = %lu, seg_size = %lu, seg_offset = %lu\n", 
		seg_daddr, seg_size(lfsp), datobyte(fsp, seg_daddr));
E 2
I 2
#ifdef VERBOSE
D 10
	printf("mmap_segment\tseg_daddr: %lu\tseg_size: %lu\tseg_offset: %qu\n",
	    seg_daddr, ssize, seg_byte);
E 10
I 10
		printf("mmap_segment\tseg_daddr: %lu\tseg_size: %lu\tseg_offset: %qu\n",
		    seg_daddr, ssize, seg_byte);
E 10
#endif
E 2
D 10
	/* malloc the space for the buffer */
D 2
	*seg_buf = (caddr_t)malloc(seg_size(lfsp));
E 2
I 2
	*segbuf = malloc(ssize);
	if (!*segbuf) {
		err(0, "mmap_segment: malloc failed");
		return(NULL);
	}
E 10
I 10
		/* malloc the space for the buffer */
		*segbuf = malloc(ssize);
		if (!*segbuf) {
			err(0, "mmap_segment: malloc failed");
			return(NULL);
		}
E 10
E 2

D 10
	/* read the segment data into the buffer */
D 2
	if (datobyte(fsp, seg_daddr) != lseek (fid, datobyte(fsp, seg_daddr), SEEK_SET)) {
		perror ("mmap_segment: bad lseek");
		return -1;
E 2
I 2
	if (lseek (fid, seg_byte, SEEK_SET) != seg_byte) {
		err (0, "mmap_segment: bad lseek");
		free(*segbuf);
		return (-1);
E 10
I 10
		/* read the segment data into the buffer */
		if (lseek (fid, seg_byte, SEEK_SET) != seg_byte) {
			err (0, "mmap_segment: bad lseek");
			free(*segbuf);
			return (-1);
		}
		
		if (read (fid, *segbuf, ssize) != ssize) {
			err (0, "mmap_segment: bad read");
			free(*segbuf);
			return (-1);
		}
E 10
E 2
	}
D 10
	
D 2
	if (seg_size(lfsp) != read (fid, *seg_buf, seg_size(lfsp))) {
		perror ("mmap_segment: bad read");
		return -1;
E 2
I 2
	if (read (fid, *segbuf, ssize) != ssize) {
		err (0, "mmap_segment: bad read");
		free(*segbuf);
		return (-1);
E 2
	}
#endif /* MMAP_SEGMENT */
E 10
	close (fid);

D 2
	return 0;
E 2
I 2
	return (0);
E 2
}

void
D 10
munmap_segment (fsp, seg_buf)
E 10
I 10
munmap_segment (fsp, seg_buf, use_mmap)
E 10
D 2
	FS_INFO	*fsp;		/* file system information */
	caddr_t	seg_buf;	/* pointer to buffer area */
E 2
I 2
	FS_INFO *fsp;		/* file system information */
	caddr_t seg_buf;	/* pointer to buffer area */
I 10
	int use_mmap;		/* mmap instead of read/write */
E 10
E 2
{
D 10
#ifdef MMAP_SEGMENT
D 2
	munmap (seg_buf, seg_size(lfsp));
E 2
I 2
	munmap (seg_buf, seg_size(&fsp->fi_lfs));
E 2
#else /* MMAP_SEGMENT */
	free (seg_buf);
#endif /* MMAP_SEGMENT */
E 10
I 10
	if (use_mmap)
		munmap (seg_buf, seg_size(&fsp->fi_lfs));
	else
		free (seg_buf);
E 10
}


/*
 * USEFUL DEBUGGING TOOLS:
 */
D 2

E 2
void
D 2
print_IFILE (p)
	IFILE	*p;
E 2
I 2
print_SEGSUM (lfsp, p)
	struct lfs *lfsp;
	SEGSUM	*p;
E 2
{
D 2
	if (p) {
		if (p->if_daddr == 0) 
			printf("{free, if_version=%lu, if_nextfree=%lu}",
				p->if_version, p->if_nextfree);
		else
			printf("{if_version=%lu, if_daddr=%lu}", 
				p->if_version, p->if_daddr);
	}
E 2
I 2
	if (p)
		(void) dump_summary(lfsp, p, DUMP_ALL, NULL);
E 2
	else printf("0x0");
	fflush(stdout);
}

D 2
void
print_SEGUSE (p)
	SEGUSE	*p;
{
	if (p) {
		printf("{su_nbytes=%lu, su_flags=%c%c%c, su_lastmod=",
			p->su_nbytes, 
			((p->su_flags & SEGUSE_DIRTY) ? 'D' : 'C'),
			((p->su_flags & SEGUSE_ACTIVE) ? 'A' : ' '),
			((p->su_flags & SEGUSE_SUPERBLOCK) ? 'S' : ' '));
			print_time_t(p->su_lastmod);
			printf("}");
	}
	else 
		printf("0x0");
	fflush(stdout);
}

void
print_CLEANERINFO (p)
	CLEANERINFO	*p;
E 2
I 2
int
bi_compare(a, b)
	const void *a;
	const void *b;
E 2
{
D 2
	if (p) printf("{clean=%lu, dirty=%lu}", p->clean, p->dirty);
	else printf("0x0");
	fflush(stdout);
}
E 2
I 2
	const BLOCK_INFO *ba, *bb;
	int diff;
E 2

D 2
void
print_SEGSUM (p)
	SEGSUM	*p;
{
	if (p) {
		printf("{ss_sumsum=%lu, ss_datasum=%lu, ss_next=%lu, ",
			p->ss_sumsum, p->ss_datasum, p->ss_next);
		printf("ss_create=%lu, ss_nfinfo=%lu, ss_ninos=%lu",
			p->ss_create, p->ss_nfinfo, p->ss_ninos);
		printf("}");
	}
	else printf("0x0");
	fflush(stdout);
}
E 2
I 2
	ba = a;
	bb = b;
E 2

D 2
void
print_time_t (t)
	time_t	t;
E 2
I 2
	if (diff = (int)(ba->bi_inode - bb->bi_inode))
		return (diff);
D 5
	if (diff = (int)(ba->bi_lbn - bb->bi_lbn))
		return (diff);
E 5
I 5
	if (diff = (int)(ba->bi_lbn - bb->bi_lbn)) {
		if (ba->bi_lbn == LFS_UNUSED_LBN)
			return(-1);
		else if (bb->bi_lbn == LFS_UNUSED_LBN)
			return(1);
D 8
		else if (ba->bi_lbn < 0)
E 8
I 8
		else if (ba->bi_lbn < 0 && bb->bi_lbn >= 0)
E 8
			return(1);
I 8
		else if (bb->bi_lbn < 0 && ba->bi_lbn >= 0)
			return(-1);
E 8
		else
			return (diff);
	}
E 5
	if (diff = (int)(ba->bi_segcreate - bb->bi_segcreate))
		return (diff);
	diff = (int)(ba->bi_daddr - bb->bi_daddr);
	return (diff);
}	

int
bi_toss(dummy, a, b)
	const void *dummy;
	const void *a;
	const void *b;
E 2
{
D 2
	char temp[128];
	int len;
E 2
I 2
	const BLOCK_INFO *ba, *bb;
E 2

D 2
	strcpy (temp, ctime(&t));
	len = strlen(temp);
	if (temp[len-1] == '\n') temp[len-1] = 0;
	printf("%s", temp);
	fflush(stdout);
E 2
I 2
	ba = a;
	bb = b;

	return(ba->bi_inode == bb->bi_inode && ba->bi_lbn == bb->bi_lbn);
E 2
D 5
}

D 2
void
print_FINFO (p)
	FINFO	*p;
E 2
I 2
/*
 * Right now, we never look at the actually data being
 * passed to the kernel in iip->ii_dinode.  Therefore,
 * if the same inode appears twice in the same block
 * (i.e.  has the same disk address), it doesn't matter
 * which entry we pass.  However, if we get the kernel
 * to start looking at the dinode, then we will care
 * and we'll need some way to distinguish which inode
 * is the more recent one.
 */
int
ii_compare(a, b)
	const void *a;
	const void *b;
E 2
{
D 2
	int i;
E 2
I 2
	const INODE_INFO *ia, *ib;
	int diff;
E 2

D 2
	if (p) {
		printf("{fi_nblocks=%lu, fi_version=%lu, fi_ino=%lu, fi_blocks={",
			p->fi_nblocks, p->fi_version, p->fi_ino);
		for (i = 0 ; i < p->fi_nblocks ; i ++) {
			if (i > 0) printf(", ");
			printf("%ld", p->fi_blocks[i]);
		}
		printf("}}");
	} else printf("0x0");
	fflush(stdout);
}
E 2
I 2
	ia = a;
	ib = b;
E 2

D 2
void
print_BLOCK_INFO (p)
	BLOCK_INFO	*p;
{
	if (p) {
		printf("{bi_inode=%lu, bi_lbn=%ld, bi_daddr=%lu, bi_segcreate=",
			p->bi_inode, p->bi_lbn, p->bi_daddr);
		print_time_t(p->bi_segcreate);
		printf(", bi_bp = 0x%x}", p->bi_bp);
	}
	else
		printf("0x0");
	fflush(stdout);
E 2
I 2
	if (diff = (int)(ia->ii_inode - ib->ii_inode))
		return (diff);
	if (diff = (int)(ia->ii_segcreate - ib->ii_segcreate))
		return (diff);
	diff = (int)(ia->ii_daddr - ib->ii_daddr);
	return (diff);
E 2
}

D 2
void
print_INODE_INFO (p)
	INODE_INFO	*p;
E 2
I 2
int
ii_toss(dummy, a, b)
	const void *dummy;
	const void *a;
	const void *b;
E 2
{
D 2
	if (p) {
		printf("{ii_inode=%lu, ii_daddr=%lu, ii_segcreate=",
			p->ii_inode, p->ii_daddr);
		print_time_t (p->ii_segcreate);
		printf(", ii_dinode=0x%x}", p->ii_dinode);
	}
	else
		printf("0x0");
	fflush(stdout);
E 2
I 2
	const INODE_INFO *ia, *ib;

	ia = a;
	ib = b;

	return(ia->ii_inode == ib->ii_inode);
E 5
E 2
}

void
D 2
print_lfs (p)
	struct	lfs	*p;
E 2
I 2
toss(p, nump, size, dotoss, client)
	void *p;
	int *nump;
	size_t size;
	int (*dotoss) __P((const void *, const void *, const void *));
	void *client;
E 2
{
D 2
	int	i;
	
	if (p) {
		printf("{\n");
		printf("\tlfs_magic=0x%x\n", p->lfs_magic);
		printf("\tlfs_version=%lu\n", p->lfs_version);
		printf("\tlfs_size=%lu\n", p->lfs_size);
		printf("\tlfs_ssize=%lu\n", p->lfs_ssize);
		printf("\tlfs_dsize=%lu\n", p->lfs_dsize);
		printf("\tlfs_bsize=%lu\n", p->lfs_bsize);
		printf("\tlfs_fsize=%lu\n", p->lfs_fsize);
		printf("\tlfs_frag=%lu\n", p->lfs_frag);
		/* checkpoint region */
		printf("\tlfs_free=%lu\n", p->lfs_free);
		printf("\tlfs_bfree=%lu\n", p->lfs_bfree);
		printf("\tlfs_nfiles=%lu\n", p->lfs_nfiles);
		printf("\tlfs_idaddr=%lu\n", p->lfs_idaddr);
		printf("\tlfs_ifile=%lu\n", p->lfs_ifile);
		printf("\tlfs_lastseg=%lu\n", p->lfs_lastseg);
		printf("\tlfs_nextseg=%lu\n", p->lfs_nextseg);
		printf("\tlfs_curseg=%lu\n", p->lfs_curseg);
		printf("\tlfs_offset=%lu\n", p->lfs_offset);
		printf("\tlfs_tstamp=%lu\n", p->lfs_tstamp);
		/* configuration parameters */
		printf("\tlfs_minfree=%lu\n", p->lfs_minfree);
		/* these fields can be computed from the others */
		printf("\tlfs_dbpseg=%lu\n", p->lfs_dbpseg);
		printf("\tlfs_inopb=%lu\n", p->lfs_inopb);
		printf("\tlfs_ifpb=%lu\n", p->lfs_ifpb);
		printf("\tlfs_sepb=%lu\n", p->lfs_sepb);
		printf("\tlfs_nindir=%lu\n", p->lfs_nindir);
		printf("\tlfs_nseg=%lu\n", p->lfs_nseg);
		printf("\tlfs_nspf=%lu\n", p->lfs_nspf);
		printf("\tlfs_cleansz=%lu\n", p->lfs_cleansz);
		printf("\tlfs_segtabsz=%lu\n", p->lfs_segtabsz);
E 2
I 2
	int i;
	void *p1;
E 2

D 2
		printf("\tlfs_segmask=%lu\n", p->lfs_segmask);
		printf("\tlfs_segshift=%lu\n", p->lfs_segshift);
		printf("\tlfs_bmask=%lu\n", p->lfs_bmask);
		printf("\tlfs_bshift=%lu\n", p->lfs_bshift);
		printf("\tlfs_ffmask=%lu\n", p->lfs_ffmask);
		printf("\tlfs_ffshift=%lu\n", p->lfs_ffshift);
		printf("\tlfs_fbmask=%lu\n", p->lfs_fbmask);
		printf("\tlfs_fbshift=%lu\n", p->lfs_fbshift);
		printf("\tlfs_fsbtodb=%lu\n", p->lfs_fsbtodb);
		/* superblock offsets */
		printf("\tlfs_sboffs={");
		for (i = 0 ; i < LFS_MAXNUMSB ; i ++) {
			if (i > 0) printf(", ");
			printf("%lu", p->lfs_sboffs[i]);
		}
		printf("}\n");
E 2
I 2
	if (*nump == 0)
		return;
E 2

D 2
		printf("}");
E 2
I 2
	for (i = *nump; --i > 0;) {
		p1 = p + size;
		if (dotoss(client, p, p1)) {
D 11
			bcopy(p1, p, i * size);
E 11
I 11
			memmove(p, p1, i * size);
E 11
			--(*nump);
		} else 
			p += size;
E 2
	}
D 2
	else
		printf("0x0");
	fflush(stdout);
E 2
}
E 1
