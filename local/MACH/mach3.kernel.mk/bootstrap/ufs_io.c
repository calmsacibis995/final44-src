/* 
 * Mach Operating System
 * Copyright (c) 1993 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 * HISTORY
 * $Log:	ufs_io.c,v $
 * Revision 2.2  93/11/17  16:01:14  dbg
 * 	Changed "" includes to <>.
 * 	[93/09/23            dbg]
 * 
 * 	Created, splitting out ufs-specific code from old file_io.c
 * 	[93/08/30            af]
 * 
 */

/*
 * Stand-alone file reading package.
 * Berkeley FFS specific code (UFS).
 */

#include <strings.h>
#include <device/device_types.h>
#include <device/device.h>

#include <mach/mach_traps.h>
#include <mach/mach_interface.h>

#include <file_io.h>
#include <dir.h>

#define private static

/*
 * Free file buffers, but don't close file.
 */
private void
free_file_buffers(
	register struct ufs_file	*ufp)
{
	register int level;

	/*
	 * Free the indirect blocks
	 */
	for (level = 0; level < NIADDR; level++) {
	    if (ufp->f_blk[level] != 0) {
		(void) vm_deallocate(mach_task_self(),
				     ufp->f_blk[level],
				     ufp->f_blksize[level]);
		ufp->f_blk[level] = 0;
	    }
	    ufp->f_blkno[level] = -1;
	}

	/*
	 * Free the data block
	 */
	if (ufp->f_buf != 0) {
	    (void) vm_deallocate(mach_task_self(),
				 ufp->f_buf,
				 ufp->f_buf_size);
	    ufp->f_buf = 0;
	}
	ufp->f_buf_blkno = -1;
}

/*
 * Read a new inode into a file structure.
 */
private int
read_inode(
	ino_t			inumber,
	register struct file	*fp)
{
	vm_offset_t		buf;
	mach_msg_type_number_t	buf_size;
	register struct fs	*fs;
	daddr_t			disk_block;
	kern_return_t		rc;

	fs = fp->u.ufs.f_fs;
	disk_block = itod(fs, inumber);

	rc = device_read(fp->f_dev,
			 0,
			 (recnum_t) fsbtodb(fs, disk_block),
			 (int) fs->fs_bsize,
			 (char **)&buf,
			 &buf_size);
	if (rc != KERN_SUCCESS)
	    return (rc);

	{
	    register struct dinode *dp;

	    dp = (struct dinode *)buf;
	    dp += itoo(fs, inumber);
	    fp->u.ufs.i_ic = dp->di_ic;
	    if ((fp->u.ufs.i_mode & IFMT) == IFDIR)
		fp->f_flags |= F_DIR;
	    else
		fp->f_flags &= ~F_DIR;
	}

	(void) vm_deallocate(mach_task_self(), buf, buf_size);

	/*
	 * Clear out the old buffers
	 */
	free_file_buffers(&fp->u.ufs);

	return (0);	 
}

/*
 * Given an offset in a file, find the disk block number that
 * contains that block.
 */
private int
block_map(
	struct file	*fp,
	daddr_t		file_block,
	daddr_t		*disk_block_p)	/* out */
{
	int		level;
	int		idx;
	daddr_t		ind_block_num;
	kern_return_t	rc;

	vm_offset_t	olddata[NIADDR+1];
	vm_size_t	oldsize[NIADDR+1];

	/*
	 * Index structure of an inode:
	 *
	 * i_db[0..NDADDR-1]	hold block numbers for blocks
	 *			0..NDADDR-1
	 *
	 * i_ib[0]		index block 0 is the single indirect
	 *			block
	 *			holds block numbers for blocks
	 *			NDADDR .. NDADDR + NINDIR(fs)-1
	 *
	 * i_ib[1]		index block 1 is the double indirect
	 *			block
	 *			holds block numbers for INDEX blocks
	 *			for blocks
	 *			NDADDR + NINDIR(fs) ..
	 *			NDADDR + NINDIR(fs) + NINDIR(fs)**2 - 1
	 *
	 * i_ib[2]		index block 2 is the triple indirect
	 *			block
	 *			holds block numbers for double-indirect
	 *			blocks for blocks
	 *			NDADDR + NINDIR(fs) + NINDIR(fs)**2 ..
	 *			NDADDR + NINDIR(fs) + NINDIR(fs)**2
	 *				+ NINDIR(fs)**3 - 1
	 */

	mutex_lock(&fp->f_lock);

	if (file_block < NDADDR) {
	    /* Direct block. */
	    *disk_block_p = fp->u.ufs.i_db[file_block];
	    mutex_unlock(&fp->f_lock);
	    return (0);
	}

	file_block -= NDADDR;

	/*
	 * nindir[0] = NINDIR
	 * nindir[1] = NINDIR**2
	 * nindir[2] = NINDIR**3
	 *	etc
	 */
	for (level = 0; level < NIADDR; level++) {
	    if (file_block < fp->u.ufs.f_nindir[level])
		break;
	    file_block -= fp->u.ufs.f_nindir[level];
	}
	if (level == NIADDR) {
	    /* Block number too high */
	    mutex_unlock(&fp->f_lock);
	    return (FS_NOT_IN_FILE);
	}

	ind_block_num = fp->u.ufs.i_ib[level];

	/*
	 * Initialize array of blocks to free.
	 */
	for (idx = 0; idx < NIADDR; idx++)
	    oldsize[idx] = 0;

	for (; level >= 0; level--) {

	    vm_offset_t	data;
	    mach_msg_type_number_t	size;

	    if (ind_block_num == 0)
		break;

	    if (fp->u.ufs.f_blkno[level] == ind_block_num) {
		/*
		 *	Cache hit.  Just pick up the data.
		 */

		data = fp->u.ufs.f_blk[level];
	    }
	    else {
		/*
		 *	Drop our lock while doing the read.
		 *	(The f_dev and f_fs fields don`t change.)
		 */
		mutex_unlock(&fp->f_lock);

		rc = device_read(fp->f_dev,
				0,
				(recnum_t) fsbtodb(fp->u.ufs.f_fs, ind_block_num),
				fp->u.ufs.f_fs->fs_bsize,
				(char **)&data,
				&size);
		if (rc != KERN_SUCCESS)
		    return (rc);

		/*
		 *	See if we can cache the data.  Need a write lock to
		 *	do this.  While we hold the write lock, we can`t do
		 *	*anything* which might block for memory.  Otherwise
		 *	a non-privileged thread might deadlock with the
		 *	privileged threads.  We can`t block while taking the
		 *	write lock.  Otherwise a non-privileged thread
		 *	blocked in the vm_deallocate (while holding a read
		 *	lock) will block a privileged thread.  For the same
		 *	reason, we can`t take a read lock and then use
		 *	lock_read_to_write.
		 */

		mutex_lock(&fp->f_lock);

		olddata[level] = fp->u.ufs.f_blk[level];
		oldsize[level] = fp->u.ufs.f_blksize[level];

		fp->u.ufs.f_blkno[level] = ind_block_num;
		fp->u.ufs.f_blk[level] = data;
		fp->u.ufs.f_blksize[level] = size;

		/*
		 *	Return to holding a read lock, and
		 *	dispose of old data.
		 */

	    }

	    if (level > 0) {
		idx = file_block / fp->u.ufs.f_nindir[level-1];
		file_block %= fp->u.ufs.f_nindir[level-1];
	    }
	    else
		idx = file_block;

	    ind_block_num = ((daddr_t *)data)[idx];
	}

	mutex_unlock(&fp->f_lock);

	/*
	 * After unlocking the file, free any blocks that
	 * we need to free.
	 */
	for (idx = 0; idx < NIADDR; idx++)
	    if (oldsize[idx] != 0)
		(void) vm_deallocate(mach_task_self(),
				     olddata[idx],
				     oldsize[idx]);

	*disk_block_p = ind_block_num;
	return (0);
}

/*
 * Read a portion of a file into an internal buffer.  Return
 * the location in the buffer and the amount in the buffer.
 */
private int
buf_read_file(
	register struct file	*fp,
	vm_offset_t		offset,
	vm_offset_t		*buf_p,		/* out */
	vm_size_t		*size_p)	/* out */
{
	register struct fs	*fs;
	vm_offset_t		off;
	register daddr_t	file_block;
	daddr_t			disk_block;
	int			rc;
	vm_offset_t		block_size;

	if (offset >= fp->u.ufs.i_size)
	    return (FS_NOT_IN_FILE);

	fs = fp->u.ufs.f_fs;

	off = blkoff(fs, offset);
	file_block = lblkno(fs, offset);
	block_size = blksize(fs, &fp->u.ufs, file_block);

	if (file_block != fp->u.ufs.f_buf_blkno) {
	    rc = block_map(fp, file_block, &disk_block);
	    if (rc != 0)
		return (rc);

	    if (fp->u.ufs.f_buf)
		(void)vm_deallocate(mach_task_self(),
				    fp->u.ufs.f_buf,
				    fp->u.ufs.f_buf_size);

	    if (disk_block == 0) {
		(void)vm_allocate(mach_task_self(),
				  &fp->u.ufs.f_buf,
				  block_size,
				  TRUE);
		fp->u.ufs.f_buf_size = block_size;
	    }
	    else {
		rc = device_read(fp->f_dev,
				0,
				(recnum_t) fsbtodb(fs, disk_block),
				(int) block_size,
				(char **) &fp->u.ufs.f_buf,
				(mach_msg_type_number_t *)&fp->u.ufs.f_buf_size);
	    }
	    if (rc)
		return (rc);

	    fp->u.ufs.f_buf_blkno = file_block;
	}

	/*
	 * Return address of byte in buffer corresponding to
	 * offset, and size of remainder of buffer after that
	 * byte.
	 */
	*buf_p = fp->u.ufs.f_buf + off;
	*size_p = block_size - off;

	/*
	 * But truncate buffer at end of file.
	 */
	if (*size_p > fp->u.ufs.i_size - offset)
	    *size_p = fp->u.ufs.i_size - offset;

	return (0);
}

/*
 * Search a directory for a name and return its
 * i_number.
 */
private int
search_directory(
	char *		name,
	register struct file *fp,
	ino_t		*inumber_p)	/* out */
{
	vm_offset_t	buf;
	vm_size_t	buf_size;
	vm_offset_t	offset;
	register struct direct *dp;
	int		length;
	kern_return_t	rc;

	length = strlen(name);

	offset = 0;
	while (offset < fp->u.ufs.i_size) {
	    rc = buf_read_file(fp, offset, &buf, &buf_size);
	    if (rc != KERN_SUCCESS)
		return (rc);

	    dp = (struct direct *)buf;
	    if (dp->d_ino != 0) {
		if (dp->d_namlen == length &&
		    !strcmp(name, dp->d_name))
	    	{
		    /* found entry */
		    *inumber_p = dp->d_ino;
		    return (0);
		}
	    }
	    offset += dp->d_reclen;
	}
	return (FS_NO_ENTRY);
}

private int
read_fs(
	mach_port_t dev,
	struct fs **fsp)
{
	register struct fs *fs;
	vm_offset_t	buf;
	mach_msg_type_number_t	buf_size;
	int		error;

	error = device_read(dev, 0, (recnum_t) SBLOCK, SBSIZE,
			    (char **) &buf, &buf_size);
	if (error)
	    return (error);

	fs = (struct fs *)buf;
	if (fs->fs_magic != FS_MAGIC ||
	    fs->fs_bsize > MAXBSIZE ||
	    fs->fs_bsize < sizeof(struct fs))
		error = FS_INVALID_FS;

	/* don't read cylinder groups - we aren't modifying anything */

	if (fsp)
		*fsp = fs;
	if (error || fsp == (struct fs **)0)
		(void) vm_deallocate(mach_task_self(), buf, buf_size);
	return error;
}

/*
 * Say if the filesystem looks like a UFS one.
 */
private boolean_t
isa_ufs(
	register struct file	*fp)
{
	if (read_fs(fp->f_dev, (struct fs **)0) == 0)
		return TRUE;
	return FALSE;
}

private int
mount_fs(
	register struct file	*fp)
{
	register struct fs *fs;
	int error;

	error = read_fs(fp->f_dev, &fp->u.ufs.f_fs);
	if (error)
	    return (error);
	fs = fp->u.ufs.f_fs;

	/*
	 * Calculate indirect block levels.
	 */
	{
	    register int	mult;
	    register int	level;

	    mult = 1;
	    for (level = 0; level < NIADDR; level++) {
		mult *= NINDIR(fs);
		fp->u.ufs.f_nindir[level] = mult;
	    }
	}

	return (0);
}

private void
unmount_fs(
	register struct file	*fp)
{
	if (file_is_structured(fp)) {
	    (void) vm_deallocate(mach_task_self(),
				 (vm_offset_t) fp->u.ufs.f_fs,
				 SBSIZE);
	    fp->u.ufs.f_fs = 0;
	}
}

/*
 * Open a UFS file.
 */
private int
ufs_open_file(
	struct file	*fp,
	char		path[MAXPATHLEN+1])
{
	register char	*cp, *component;
	register int	c;	/* char */
	register int	rc;
	ino_t		inumber, parent_inumber;
	int		nlinks = 0;

	if (path == 0 || *path == '\0') {
	    return FS_NO_ENTRY;
	}

	rc = mount_fs(fp);
	if (rc)
	    return rc;

	inumber = (ino_t) ROOTINO;
	if ((rc = read_inode(inumber, fp)) != 0) {
	    printf("can't read root inode\n");
	    return rc;
	}

	cp = path;

	while (*cp) {

	    /*
	     * Check that current node is a directory.
	     */
	    if ((fp->u.ufs.i_mode & IFMT) != IFDIR)
		return (FS_NOT_DIRECTORY);

	    /*
	     * Remove extra separators
	     */
	    while (*cp == '/')
		cp++;

	    /*
	     * Get next component of path name.
	     */
	    component = cp;
	    {
		register int	len = 0;

		while ((c = *cp) != '\0' && c != '/') {
		    if (len++ > MAXNAMLEN)
			return (FS_NAME_TOO_LONG);
		    if (c & 0200)
			return (FS_INVALID_PARAMETER);
		    cp++;
		}
		*cp = 0;
	    }

	    /*
	     * Look up component in current directory.
	     * Save directory inumber in case we find a
	     * symbolic link.
	     */
	    parent_inumber = inumber;
	    rc = search_directory(component, fp, &inumber);
	    if (rc)
		return rc;

	    *cp = c;

	    /*
	     * Open next component.
	     */
	    if ((rc = read_inode(inumber, fp)) != 0)
		return rc;

	    /*
	     * Check for symbolic link.
	     */
	    if ((fp->u.ufs.i_mode & IFMT) == IFLNK) {

		int	link_len = fp->u.ufs.i_size;
		int	len;

		len = strlen(cp) + 1;

		if (link_len + len >= MAXPATHLEN - 1)
		    return (FS_NAME_TOO_LONG);

		if (++nlinks > MAXSYMLINKS)
		    return (FS_SYMLINK_LOOP);

		ovbcopy(cp, &path[link_len], len);

#ifdef	IC_FASTLINK
		if ((fp->u.ufs.i_flags & IC_FASTLINK) != 0) {
		    bcopy(fp->u.ufs.i_symlink, path, (unsigned) link_len);
		}
		else
#endif	IC_FASTLINK
		{
		    /*
		     * Read file for symbolic link
		     */
		    vm_offset_t	buf;
		    mach_msg_type_number_t	buf_size;
		    daddr_t	disk_block;
		    register struct fs *fs = fp->u.ufs.f_fs;

		    (void) block_map(fp, (daddr_t)0, &disk_block);
		    rc = device_read(fp->f_dev,
				     0,
				     (recnum_t) fsbtodb(fs, disk_block),
				     (int) blksize(fs, &fp->u.ufs, 0),
				     (char **) &buf,
				     &buf_size);
		    if (rc)
			return rc;

		    bcopy((char *)buf, path, (unsigned)link_len);
		    (void) vm_deallocate(mach_task_self(), buf, buf_size);
		}

		/*
		 * If relative pathname, restart at parent directory.
		 * If absolute pathname, restart at root.
		 * If pathname begins '/dev/<device>/',
		 *	restart at root of that device.
		 */
		cp = path;
		if (*cp != '/') {
		    inumber = parent_inumber;
		}
		else if (!strprefix(cp, "/dev/")) {
		    inumber = (ino_t)ROOTINO;
		}
		else
		    return FS_ISA_SYMLINK;

		if ((rc = read_inode(inumber, fp)) != 0)
		    return rc;
	    }
	}

	/*
	 * Found terminal component.
	 */
	return 0;
}

/*
 * Close file - free all storage used.
 */
void
ufs_close_file(
	register struct file	*fp)
{
	/*
	 * Free the disk super-block.
	 */
	unmount_fs(fp);

	/*
	 * Free the inode and data buffers.
	 */
	free_file_buffers(&fp->u.ufs);
}

/*
 * Copy a portion of a file into kernel memory.
 * Cross block boundaries when necessary.
 */
private int
ufs_read_file(
	register struct file	*fp,
	vm_offset_t		offset,
	vm_offset_t		start,
	vm_size_t		size,
	vm_size_t		*resid)	/* out */
{
	int			rc;
	register vm_size_t	csize;
	vm_offset_t		buf;
	vm_size_t		buf_size;

	while (size != 0) {
	    rc = buf_read_file(fp, offset, &buf, &buf_size);
	    if (rc)
		return (rc);

	    csize = size;
	    if (csize > buf_size)
		csize = buf_size;
	    if (csize == 0)
		break;

	    bcopy((char *)buf, (char *)start, csize);

	    offset += csize;
	    start  += csize;
	    size   -= csize;
	}
	if (resid)
	    *resid = size;

	return (0);
}


/*
 * Make a file_direct from a file.
 */
private int
ufs_make_file_direct(
	struct file	*fp,
	register struct file_direct *fdp)
{
	struct fs	*fs;
	long		num_blocks, i;
	vm_offset_t	buffer;
	vm_size_t	size;
	int		rc;

	rc = read_fs(fp->f_dev, &fs);
	if (rc)
		return rc;

	fdp->fd_dev = fp->f_dev;
	fdp->fd_blocks = (daddr_t *) 0;
	fdp->fd_size = 0;
	fdp->fd_bsize = fs->fs_bsize;
	fdp->fd_bshift = fs->fs_bshift;
	fdp->fd_fsbtodb = fs->fs_fsbtodb;

	(void) vm_deallocate(mach_task_self(),
			     (vm_offset_t) fs,
			     SBSIZE);

	/*
	 * Now add the blocks from file to a file_direct.
	 */
	fs = fp->u.ufs.f_fs;

	/* calculate number of blocks in the file, ignoring fragments */

	num_blocks = lblkno(fs, fp->u.ufs.i_size);

	/* allocate memory for a bigger array */

	size = (num_blocks + fdp->fd_size) * sizeof(daddr_t);
	rc = vm_allocate(mach_task_self(), &buffer, size, TRUE);
	if (rc != KERN_SUCCESS)
		return rc;

	/* lookup new block addresses */

	for (i = 0; i < num_blocks; i++) {
		daddr_t disk_block;

		rc = block_map(fp, (daddr_t) i, &disk_block);
		if (rc != 0) {
			(void) vm_deallocate(mach_task_self(), buffer, size);
			return rc;
		}

		((daddr_t *) buffer)[fdp->fd_size + i] = disk_block;
	}

	/* copy old addresses and install the new array */

	if (fdp->fd_blocks != 0) {
		bcopy((char *) fdp->fd_blocks, (char *) buffer,
		      fdp->fd_size * sizeof(daddr_t));

		(void) vm_deallocate(mach_task_self(),
				(vm_offset_t) fdp->fd_blocks,
				(vm_size_t) (fdp->fd_size * sizeof(daddr_t)));
	}
	fdp->fd_blocks = (daddr_t *) buffer;
	fdp->fd_size += num_blocks;

	/* deallocate cached blocks */

	free_file_buffers(&fp->u.ufs);

	return 0;
}

/*
 * Exported interface
 */

struct filesystem_ops ufs_ops = {
	isa_ufs,
	ufs_open_file,
	ufs_close_file,
	ufs_read_file,
	ufs_make_file_direct
};
