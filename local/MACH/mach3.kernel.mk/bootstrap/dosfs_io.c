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
 * $Log:	dosfs_io.c,v $
 * Revision 2.2  93/11/17  15:58:15  dbg
 * 
 * 	Changed "" includes to <>.
 * 	[93/09/23            dbg]
 * 
 * 	Created, from our DosFs code.
 * 	[93/09/09            af]
 * 
 */
/*
 *	File: dosfs_io.c
 * 	Author: Alessandro Forin, Carnegie Mellon University
 *	Date:	9/93
 *
 *	Stand-alone file reading package for MS-DOS.
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
#define	DOS_MAXNAMLEN 11
#define DOS_ROOTINO 1

#define private static

#undef	lblkno
#define	lblkno(_f_,_o_)	((_o_) / (_f_)->f_blocksize)
#undef	blkoff
#define	blkoff(_f_,_o_)	((_o_) % (_f_)->f_blocksize)

/*
 * 	File allocation table (FAT) utils
 */
private unsigned short
fat_get_entry(
	unsigned short	*fat,
	unsigned int	fbits,
	unsigned int	entry)
{
	if (entry < 2)
		return 0xffff;

	if (fbits == 16)
		return fat[entry];

	else if (fbits != 12) {
		printf("Bad fatbits %d", fbits);
		return 0xffff;
	}

	fbits = (entry * 3) / 4;/* 12/16 == 3/4 */

	switch (entry & 0x3) {
	case 0:
		fbits = fat[fbits];
		break;
	case 1:
		fbits = (fat[fbits] >> 12) | (fat[fbits + 1] << 4);
		break;
	case 2:
		fbits = (fat[fbits] >>  8) | (fat[fbits + 1] << 8);
		break;
	case 3:
		fbits = fat[fbits] >> 4;
		break;
	}

	fbits &= 0xfff;
	if ((fbits & 0xff0) == 0xff0)
		fbits |= 0xf000;/* make specials always 16 bits */

	return fbits;
}

/*
 * Given an offset in a file, find the disk block number that
 * contains that block.
 */
private int
block_map(
	struct dosfs_file	*dfp,
	daddr_t			file_block,
	daddr_t			*disk_block_p)	/* out */
{
	daddr_t			ret;
	kern_return_t		rc;

	if (dfp->e_inum <= DOS_ROOTINO) {
		*disk_block_p = dfp->f_root_start + (file_block * dfp->f_clsize);
	} else {
		ret = dfp->e_inum;
                while (file_block > 0) {
                        /*
                         * Which one is the next block in the file ?
                         */
                        ret = (daddr_t) fat_get_entry(dfp->f_fat, dfp->f_fatbits, ret);

                        if ((ret == 0) || ((ret & 0xfff0) == 0xfff0)) {
                                return -1;
                        }
                        file_block--;
                }
                /* first cluster is no. 2 */
                ret = ((ret - 2) * dfp->f_clsize) + dfp->f_clstart;
		*disk_block_p = ret;
	}
	return (0);
}

/*
 * Length of a directory
 */
private vm_size_t
dosfs_dirlen(
	struct dosfs_file	*dfp,
	daddr_t			clusterno)
{
	if (clusterno > DOS_ROOTINO) {
		int len = 0;
		do {
			clusterno = fat_get_entry(dfp->f_fat, dfp->f_fatbits, clusterno);
			len++;
		} while (clusterno && (clusterno < 0xfff8));
		return (len * dfp->f_blocksize);
	}
	/* len of root */
	return (dfp->f_clstart - dfp->f_root_start) * DEV_BSIZE;
}

/*
 * Read a portion of a file into an internal buffer.  Return
 * the location in the buffer and the amount in the buffer.
 */
private int
buf_read_file(fp, offset, buf_p, size_p)
	register struct file	*fp;
	vm_offset_t		offset;
	vm_offset_t		*buf_p;		/* out */
	vm_size_t		*size_p;	/* out */
{
	vm_offset_t		off;
	register daddr_t	file_block;
	daddr_t			disk_block;
	int			rc;

	if (offset >= fp->u.dos.e_size)
	    return (FS_NOT_IN_FILE);

	off = blkoff(&fp->u.dos, offset);
	file_block = lblkno(&fp->u.dos, offset);

	if (file_block != fp->u.dos.f_buf_blkno) {
	    rc = block_map(&fp->u.dos, file_block, &disk_block);
	    if (rc != 0)
		return (rc);

	    if (fp->u.dos.f_buf)
		(void)vm_deallocate(mach_task_self(),
				    fp->u.dos.f_buf,
				    fp->u.dos.f_buf_size);

	    rc = device_read(fp->f_dev, 0,
	    		     (recnum_t) disk_block,
			     (int) fp->u.dos.f_blocksize,
			     (char **) &fp->u.dos.f_buf,
			     &fp->u.dos.f_buf_size);
	    if (rc)
		return (rc);

	    fp->u.dos.f_buf_blkno = file_block;
	}

	/*
	 * Return address of byte in buffer corresponding to
	 * offset, and size of remainder of buffer after that
	 * byte.
	 */
	*buf_p = fp->u.dos.f_buf + off;
	*size_p = fp->u.dos.f_blocksize - off;

	/*
	 * But truncate buffer at end of file.
	 */
	if (*size_p > fp->u.dos.e_size - offset)
	    *size_p = fp->u.dos.e_size - offset;

	return (0);
}

/*
 * Search a directory for a name and return its
 * i_number.
 */
private int
search_directory(
	char *		name,
	register struct file *fp)
{
	vm_offset_t	buf;
	vm_size_t	buf_size;
	vm_offset_t	offset;
	register struct dosfs_directory_record *dp;
	int		length;
	kern_return_t	rc;

	length = strlen(name);

	offset = 0;
	while (offset < fp->u.dos.e_size) {
	    boolean_t	match = FALSE;
	    rc = buf_read_file(fp, offset, &buf, &buf_size);
	    if (rc != KERN_SUCCESS)
		return (rc);

	    dp = (struct dosfs_directory_record *)buf;
	    {
		register const unsigned char *s1, *s2;
		s1 = (unsigned char *)name;
		s2 = dp->name;
		while (*s1++ == *s2++)
		    if (*s1 == 0) break;
		match = (*s1 == 0) && (*s2 == ' ' || length == 11);	/* good nuf */
	    }
	    if (match) {
		/* found entry */
		fp->u.dos.e_inum = dosfsnum_16(dp->start);
		fp->u.dos.e = *dp;
		if (dp->attr & DOS_ATTR_DIR) {
		    fp->u.dos.e_size = dosfs_dirlen(&fp->u.dos, fp->u.dos.e_inum);
		    fp->f_flags |= F_DIR;
		} else {
		    fp->u.dos.e_size = dosfsnum_32(dp->size);
		    fp->f_flags &= ~F_DIR;
		}
		fp->u.dos.f_buf_blkno = -1;
		return (0);
	    }
	    offset += sizeof(*dp);
	}
	return (FS_NO_ENTRY);
}

private int
mount_fs(
	register struct file	*fp,
	boolean_t		only_check)
{
	int	error, i;
	register struct dosfs_bootsector *vdp;
	vm_offset_t	buf;
	vm_size_t	buf_size;
	vm_size_t	fatlen;
	vm_offset_t	fat;
	daddr_t		fatstart;

	error = device_read(fp->f_dev, 0, (recnum_t) MDOS_LABELSECTOR,
			    MDOS_SECTOR_SIZE, (char **) &buf, &buf_size);
	if (error) {
	    return (error);
	}

	/*
	 * Label
	 */
	vdp = (struct dosfs_bootsector *)buf;
	if (dosfsnum_16(vdp->label.magic) != BIOS_LABEL_MAGIC) {
		error = FS_INVALID_FS;
		goto out;
	}
	if (only_check)
		goto out;

	fp->u.dos.f_blocksize = dosfsnum_16(vdp->secsiz) * vdp->clsiz;

        i = dosfsnum_16(vdp->psect);
        if (i == 0)
                i = dosfsnum_32(vdp->bigsect);
	fp->u.dos.f_fatbits =  (i > 4087) ? 16 : 12;
	fatlen = dosfsnum_16(vdp->fatlen);
	fatstart = dosfsnum_16(vdp->nrsvsect);
	fp->u.dos.f_root_start = fatstart + (vdp->nfat * fatlen);
	fatstart = (fatstart * MDOS_SECTOR_SIZE) / DEV_BSIZE;
	fatlen *= DEV_BSIZE;
	i = dosfsnum_16(vdp->dirents) * MDOS_DIR_SIZE;
	i = (i + MDOS_SECTOR_SIZE - 1) / (unsigned) MDOS_SECTOR_SIZE;
	fp->u.dos.f_clstart = i + fp->u.dos.f_root_start;
	fp->u.dos.f_clsize = vdp->clsiz;

	fp->u.dos.e_inum = DOS_ROOTINO;
	fp->u.dos.e_size = dosfsnum_16(vdp->dirents) * sizeof(struct dosfs_directory_record);
	fp->u.dos.e.attr = DOS_ATTR_DIR;

	/*
	 * Done with label, read FAT in
	 */
	(void) vm_deallocate(mach_task_self(), buf, buf_size);
	error = device_read(fp->f_dev, 0, (recnum_t) fatstart, fatlen,
			   (char **) &fat, &buf_size);
	if (error)
		return (error);
	fp->u.dos.f_fat = (unsigned short *)fat;
	fp->u.dos.f_fat_len = fatlen;
	fp->u.dos.f_buf_blkno = -1;

	return (0);
out:
	(void) vm_deallocate(mach_task_self(), buf, buf_size);
	return error;
}

/*
 * Say if the filesystem looks like a DOS one.
 */
private boolean_t
isa_dosfs(
	register struct file	*fp)
{
	if (mount_fs(fp, TRUE) == 0)
		return TRUE;
	return FALSE;
}


/*
 * Open a DOS file.
 */
private int
dosfs_open_file(
	struct file	*fp,
	char		path[MAXPATHLEN+1])
{
	register char	*cp, *ncp;
	register int	c;	/* char */
	register int	rc;
	int		nlinks = 0;
	vm_size_t	parent_inumber;

	char	component[DOS_MAXNAMLEN+1];
	
	if (path == 0 || *path == '\0') {
	    return (FS_NO_ENTRY);
	}

	rc = mount_fs(fp, FALSE);
	if (rc)
	    return rc;

	cp = path;		/* file */

	while (*cp) {

	    /*
	     * Check that current node is a directory.
	     */
	    if ((fp->u.dos.e.attr & DOS_ATTR_DIR) == 0)
		return FS_NOT_DIRECTORY;

	    /*
	     * Remove extra separators
	     */
	    while (*cp == '/')
		cp++;

	    /*
	     * Get next component of path name.
	     */
	    {
		register int	len = 0;

		ncp = component;
		while ((c = *cp) != '\0' && c != '/') {
		    if (len++ > DOS_MAXNAMLEN)
			return FS_NAME_TOO_LONG;

		    if (c & 0200)
			return FS_INVALID_PARAMETER;

		    *ncp++ = c;
		    cp++;
		}
		*ncp = 0;
	    }

	    /*
	     * Look up component in current directory.
	     * If found it gets cached in fp.
	     */
	    parent_inumber = fp->u.dos.e_inum;
	    rc = search_directory(component, fp);
	    if (rc)
		return rc;

	    /*
	     * Check for symbolic link.
	     */
	    if ((fp->u.dos.e.attr & (DOS_ATTR_DOSFS_TYPE|DOS_ATTR_DIR))
	    	 == DOS_ATTR_DOSFS_TYPE) {

		int	link_len = fp->u.dos.e_size;
		int	len, mode;

		mode = dosfsnum_16(fp->u.dos.e.res_ext.mnt_ext.mode);
		if ((mode & DOSFS_IFMT) != DOSFS_IFLNK)
			continue;

		len = strlen(cp) + 1;

		if (link_len + len >= MAXPATHLEN - 1)
		    return (FS_NAME_TOO_LONG);

		if (++nlinks > MAXSYMLINKS)
		    return (FS_SYMLINK_LOOP);

		ovbcopy(cp, &path[link_len], len);

		{
		    /*
		     * Read file for symbolic link
		     */
		    vm_offset_t	buf;
		    vm_size_t	buf_size;

		    rc = buf_read_file(fp, (vm_offset_t)0, &buf, &buf_size);

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
		    fp->u.dos.e_inum = parent_inumber;
		}
		else if (!strprefix(cp, "/dev/")) {
		    fp->u.dos.e_inum = DOS_ROOTINO;
		}
		else
		    return FS_ISA_SYMLINK;

		fp->u.dos.e.attr = DOS_ATTR_DIR;
		fp->f_flags |= F_DIR;
		fp->u.dos.f_buf_blkno = -1;
		fp->u.dos.e_size = dosfs_dirlen(&fp->u.dos, fp->u.dos.e_inum);
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
private void
free_file_buffers(
	register struct file	*fp)
{
	/*
	 * Free the FAT table
	 */
	if (fp->u.dos.f_fat)
		(void)vm_deallocate(mach_task_self(),
				    (vm_offset_t)fp->u.dos.f_fat,
				    fp->u.dos.f_fat_len);

	/*
	 * Free the inode and data buffers.
	 */
	if (fp->u.dos.f_buf)
		(void)vm_deallocate(mach_task_self(),
				    fp->u.dos.f_buf,
				    fp->u.dos.f_buf_size);

}

/*
 * Copy a portion of a file into kernel memory.
 * Cross block boundaries when necessary.
 */
private int
dosfs_read_file(
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
		return rc;

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
dosfs_make_file_direct(
	struct file	*fp,
	register struct file_direct *fdp)
{
	long		num_blocks, i;
	vm_offset_t	buffer;
	vm_size_t	size;
	int		rc;

	fdp->fd_dev = fp->f_dev;
	fdp->fd_blocks = (daddr_t *) 0;
	fdp->fd_size = 0;
	fdp->fd_bsize = fp->u.dos.f_blocksize;
	fdp->fd_bshift = log2(fdp->fd_bsize);
	fdp->fd_fsbtodb = log2(fp->u.dos.f_clsize);

	/*
	 * Now add the blocks from file to a file_direct.
	 */

	/* calculate number of blocks in the file, ignoring fragments */

	num_blocks = lblkno(&fp->u.dos, fp->u.dos.e_size);

	/* allocate memory for a bigger array */

	size = (num_blocks + fdp->fd_size) * sizeof(daddr_t);
	rc = vm_allocate(mach_task_self(), &buffer, size, TRUE);
	if (rc != KERN_SUCCESS)
		return rc;

	/* lookup new block addresses */

	for (i = 0; i < num_blocks; i++) {
		daddr_t disk_block;

		rc = block_map(&fp->u.dos, (daddr_t) i, &disk_block);
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

	free_file_buffers(fp);

	return 0;
}

/*
 * Exported interface
 */

struct filesystem_ops dosfs_ops = {
	isa_dosfs,
	dosfs_open_file,
	free_file_buffers,
	dosfs_read_file,
	dosfs_make_file_direct
};
