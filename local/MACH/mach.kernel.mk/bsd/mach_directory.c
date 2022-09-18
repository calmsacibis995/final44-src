/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	mach_directory.c,v $
 * Revision 2.16  90/07/03  16:32:23  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  17:47:42  mrt]
 * 
 * Revision 2.15  89/10/10  10:46:37  mwyoung
 * 	Make fast symbolic links an architecture-independent option.
 * 	[89/05/12  16:00:07  mwyoung]
 * 
 * Revision 2.14  89/03/09  19:29:22  rpd
 * 	More cleanup.
 * 
 * Revision 2.13  89/02/25  14:42:43  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.12  89/02/09  04:31:48  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.11  89/01/31  01:20:35  rpd
 * 	namei: check for error from scan_name_segment.  Found by
 * 	boykin@encore.com.
 * 	[88/12/05            dlb]
 * 
 * Revision 2.10  89/01/15  16:18:04  rpd
 * 	Use decl_simple_lock_data.
 * 	[89/01/15  14:48:58  rpd]
 * 
 * Revision 2.9  88/10/18  03:14:45  mwyoung
 * 	lint: Don't bother to count entries in directory_release().
 * 	[88/10/08            mwyoung]
 * 
 * Revision 2.8  88/08/25  18:11:06  mwyoung
 * 	Collapse CS_ conditionals.
 * 	[88/08/22  21:05:52  mwyoung]
 * 	
 * 	Increase the size of HASHENTRYZONEMAX.  A large Venus cache directory
 * 	easily overwhelms a 256K hash_entry zone.  Add some diagnostic stuff.
 * 	[88/08/16  00:21:47  mwyoung]
 * 	
 * 	Eliminate hc diagnostics about unused variables.
 * 	[88/08/11  18:43:06  mwyoung]
 * 
 * Revision 2.7  88/08/10  11:38:31  rvb
 * branchmerge added both my and rpd's fix for sys/cmu_syscalls.h -> sys/tables.h
 * 
 * Revision 2.6  88/08/09  17:50:50  rvb
 * Fix bug in name_buffer_lock locking.  alloc_buffer could give up
 * lock to soon.
 * 
 * Revision 2.5  88/07/21  22:41:29  rpd
 * Added include of "sys/table.h", for UMODE_NOFOLLOW.
 * 
 * 15-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Correct locking in alloc_buffer(); problem discovery and
 *	solution by Rick Rashid.
 *
 *  2-Jun-88  David Golub (dbg) at Carnegie-Mellon University
 *	Installed bug fix from Jay Kistler for "not found" returns when
 *	the caller is not expecting to transfer into Vice.
 *	[ V5.1(XF27) ]
 *
 * 17-Feb-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Use a separate lock for the name buffer list.
 *
 * 16-Feb-88  Richard Sanzi (sanzi) at Carnegie-Mellon University
 *	Modified direnter() to NOT use bp after doing a bwrite().
 *
 * 15-Jan-88  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Added increment of u.u_rfsncnt to conform with rename
 *	conventions in rfs code.
 *
 * 26-Aug-87  Jay Kistler (jjk) at Carnegie Mellon University
 *	VICE:  Reset the u_rmt_requested flag before the return in the
 *	block that Mike created for the ERANGE facility.  NOTE to future
 *	modifiers of this code:  if you add a new return statement
 *	ANYWHERE in namei(), it MUST be preceded by a resetting of the
 *	u_rmt_requested flag or subsequent Vice fs calls may panic.
 *
 * 18-Dec-87  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Fixed direnter to avoid adding file entry to cache if there is an
 *	error writing the directory.  Directory is flushed from cache on
 *	such an error.
 *
 * 11-Nov-87  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Modified dirremove and dirrewrite to no longer make use of
 *	directory state information passed to them in name_params.  This
 *	eliminates errors due to stale data which can corrupt a
 *	directory.
 *
 * 21-Oct-87  Richard Sanzi (sanzi) at Carnegie-Mellon University
 *	Modified code in dirremove() and direnter() to avoid deadlocking
 *	on a block from the buffer cache when calling
 *	directory_file_enter().  These routines now release their buffer
 *	before calling directory_file_enter().
 *
 * 20-Oct-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	CS_GENERIC: Include sys/syscall.h to define UMODE_NOFOLLOW for rfs.
 *
 *  3-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 30-Sep-87  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Removed special zone macros and replaced them with new
 *	ADD_TO_ZONE and REMOVE_FROM_ZONE macros from zalloc.h.
 *
 * 18-Aug-87  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Fixed directory_scan to properly maintain entry reference count.
 *
 * 17-Aug-87  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Cleanup, addition of some comments.  Better locking.  Static
 *	HASHSIZE.
 *
 * 29-May-87  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Created.
 *
 */

/* 
 *	Current state:
 *		Debugging changes of 11/Nov and 21/Oct.
 *
 *	TODO list:
 *		Streamlining simple lookup case somewhat.
 */
 
#include <mach_rfs.h>
#include <mach_debug.h>
#include <mach_fastlink.h>
#include <vice.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/inode.h>
#include <sys/fs.h>
#include <sys/mount.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <kern/zalloc.h>
#include <sys/table.h>

#if	MACH_DEBUG
boolean_t	namei_print = FALSE;
int		namei_count = 0;
#endif	MACH_DEBUG

struct	buf *blkatoff();
caddr_t dir_alloc();
void	directory_file_enter();
void	directory_release();

#define DEFAULTHASHSIZE 	32
#define DIRHASHSIZE 		1024
#define SMALLNAMELEN 		12
#define MEDIUMNAMELEN 		32
#define BIGNAMELEN		256
#define HASHENTRYZONEMAX	(2*1024*1024)

/*
 * This is a static so that it can be varied by adb 
 * and we can see what size is really a good one.
 */
int	HASHSIZE		= DEFAULTHASHSIZE;
int	HASHMASK		= DEFAULTHASHSIZE-1;
int	hash_entry_zone_max	= HASHENTRYZONEMAX;

/*
 * Sleepable version of locking package.  This should really be
 * in lock.h or lock.c.  We need a sleepable vesion so that
 * we can have pageable zones.
 */
lock_data_t	dir_lock_data;
lock_t		dir_lock = &dir_lock_data;

/*
 * Lock management.
 * The directory cache data structures and their use is complex
 * enough that, for now, we use a single, recursive lock rather
 * than attempt to lock-manage individual data structures.
 */
#define set_directory_lock	lock_write(dir_lock)
#define clear_directory_lock	lock_done(dir_lock)

/*
 * Zone management macros for mach_directory.
 * These routines allow for pageable directory zones.
 * All operate under the global directory lock.
 */

#define ZALLOC_CAN_SLEEP(zone, ret, type) 				\
{ 									\
	register zone_t	z = (zone); 					\
	(ret) = (type)zalloc(z); 					\
}

#define hash_dev_ino(dev, ino) ((dev ^ ino)&(DIRHASHSIZE-1))

struct hash_entry {
	struct hash_entry * 	next;
	char *			name;
	int			name_length;
	int			reclen;
	int			prev_size;
	ino_t			ino;
	off_t			dir_offset;
};

struct dir_hash_entry {
	struct dir_hash_entry *	next;
	int			last_unused;	
	int			ref_count;
	off_t			last_off;	/* Last open space*/
	dev_t			dev;
	ino_t			ino;
	struct hash_entry **	hash_table;
} ** dir_hash_table;


int	namei_first_time 	= TRUE;
int	next_directory_index 	= 0;

zone_t	hash_table_zone, hash_entry_zone, dir_hash_entry_zone;
zone_t  dir_hash_table_zone;
zone_t	small_name_zone, medium_name_zone, big_name_zone;

decl_simple_lock_data(,name_buffer_lock)
struct	buf *free_name_buffer;

/*
 * Macros for various CMU related features:
 *
 * VICE		- CMU ITC Vice file system hooks into namei
 */


#define increment_inode_count(dp)	iincr_chk(dp)
#define increment_quoted	quoted++	
#define QUOTED	3

#if	VICE
#define clear_vice_request	u.u_rmt_requested = 0
#else	VICE
#define clear_vice_request
#endif	VICE


/*
 * Basic macros for various useful functions.
 */

#define file_hash(input_name, ret)				\
{								\
	register char * name_0 = input_name;			\
	register int	sum_0 = 0;				\
	if (name_0 != NULL) {					\
		while (*name_0 != 0) {				\
			sum_0 = sum_0^(unsigned char)*name_0++;	\
		}						\
	}							\
	ret = (sum_0 & HASHMASK);				\
}

#define isdotdot(name_params) 					\
	(name_params->ni_dent.d_namlen == 2    &&		\
	 name_params->ni_dent.d_name[0] == '.' &&		\
	 name_params->ni_dent.d_name[1] == '.')	


#define alloc_buffer(name_buffer)				\
{								\
	simple_lock(&name_buffer_lock);				\
	*name_buffer = free_name_buffer;			\
	if (*name_buffer == NULL) {				\
		simple_unlock(&name_buffer_lock);		\
		*name_buffer = geteblk(MAXPATHLEN);		\
	} else {						\
		free_name_buffer = (*name_buffer)->av_forw;	\
		simple_unlock(&name_buffer_lock);		\
	}							\
}

#define free_buffer(name_buffer) 				\
{ 								\
	simple_lock(&name_buffer_lock);				\
	name_buffer->av_forw = free_name_buffer; 		\
	free_name_buffer = name_buffer;				\
	simple_unlock(&name_buffer_lock);			\
}

/*
 * Externally called version of free_buffer.
 */
void
nameifree(nbp)
	struct buf *nbp;
{
	free_buffer(nbp);
}

/*
 * Initialization routine.  Called on first use of namei.
 */
void
init_name_directory()
{
	register int 	i;

	lock_init(dir_lock, TRUE);
	simple_lock_init(&name_buffer_lock);

	dir_hash_table_zone = zinit(sizeof(struct hash_entry *)*DIRHASHSIZE,
				4096,
				4096,
				TRUE,
				"directory_hash_table_zone");

	ZALLOC_CAN_SLEEP(dir_hash_table_zone, dir_hash_table, struct dir_hash_entry **);
	for (i = 0; i < DIRHASHSIZE; i++) dir_hash_table[i] = NULL;

	hash_table_zone = zinit(sizeof(struct hash_entry *)*HASHSIZE,
				64*1024, 16*1024,
				TRUE, "hash_table_zone");

	hash_entry_zone = zinit(sizeof(struct hash_entry),
				hash_entry_zone_max, 64*1024,
				TRUE, "hash_entry_zone");

	dir_hash_entry_zone = zinit(sizeof(struct hash_entry),
				32*1024, 4*1024,
				TRUE, "directory_hash_entry_zone");

	small_name_zone = zinit(SMALLNAMELEN,
				hash_entry_zone_max, 32*1024,
				TRUE, "small_name_zone");

	medium_name_zone = zinit(MEDIUMNAMELEN,
				hash_entry_zone_max, 8*1024,
				TRUE, "medium_name_zone");

	big_name_zone = zinit(BIGNAMELEN,
				hash_entry_zone_max, 4096,
				TRUE, "big_name_zone");

}

/*
 * Allocate memory from a zone.  If the zone is empty, this routine
 * will attempt to release one or more directories from the cache
 * until the zone is no longer empty.  The strategy for release is
 * roughly fifo and acheived by a "clock" hand pointer incremented
 * around the dir_hash_table data structure.
 */

caddr_t
dir_alloc(zone)
	zone_t	zone;
{
	caddr_t 			tmp;
	register struct dir_hash_entry *hash_bucket;
	register struct dir_hash_entry *last_entry;
	

	REMOVE_FROM_ZONE(zone, tmp, caddr_t);
	while (tmp == NULL) {
		if (zone->cur_size + zone->alloc_size <= zone->max_size) {
			ZALLOC_CAN_SLEEP(zone, tmp, caddr_t);
			continue;
		}

		next_directory_index++;
		if (next_directory_index >= DIRHASHSIZE) 
			next_directory_index = 0;

		last_entry = (struct dir_hash_entry *)
				&dir_hash_table[next_directory_index];
		hash_bucket = dir_hash_table[next_directory_index];
		while (hash_bucket != NULL) {
			if (hash_bucket->ref_count == 0) {
				last_entry->next = hash_bucket->next;
				directory_release(hash_bucket);
				ADD_TO_ZONE(dir_hash_entry_zone,hash_bucket);
			} else 	last_entry = hash_bucket;
			hash_bucket = last_entry->next;
		}

		REMOVE_FROM_ZONE(zone, tmp, caddr_t);
	}

	return (tmp);
}

hash_entry_release(entry) 
	register struct hash_entry *	entry;
{
	if (entry->name_length < SMALLNAMELEN) {
		ADD_TO_ZONE(small_name_zone, entry->name);
	}
	else if (entry->name_length < MEDIUMNAMELEN) {
		ADD_TO_ZONE(medium_name_zone, entry->name);
	}
	else {
	    ADD_TO_ZONE(big_name_zone, entry->name);
	}

	ADD_TO_ZONE(hash_entry_zone, entry);
}

struct dir_hash_entry *
dir_lookup(dev, ino) 
	register dev_t				dev;
	register ino_t				ino;
{
	register struct dir_hash_entry *	hash_bucket;

	hash_bucket = dir_hash_table[hash_dev_ino(dev,ino)];
	while (hash_bucket != NULL) {
		if (hash_bucket->dev == dev && hash_bucket->ino == ino)
			return (hash_bucket);
		hash_bucket = hash_bucket->next;
	}
	return (NULL);
}


void
dir_enter(dev, ino)
	dev_t			dev;
	ino_t			ino;
{									
	register struct dir_hash_entry *	entry;
	int					hash_offset;

	entry = (struct dir_hash_entry *) dir_alloc(dir_hash_entry_zone);
									
	hash_offset = hash_dev_ino(dev, ino);
	entry->next = dir_hash_table[hash_offset];
	dir_hash_table[hash_offset] = entry;				

	entry->dev 		= dev;
	entry->ino 		= ino;
	entry->last_off		= 0;
	entry->hash_table	= NULL;
	entry->ref_count	= 0;
}

void
dir_remove(dev, ino)
	register dev_t	dev;
	register ino_t	ino;
{
	register struct dir_hash_entry *	last_entry;
	register struct dir_hash_entry *	hash_bucket;

	last_entry = 
	   (struct dir_hash_entry *)&dir_hash_table[hash_dev_ino(dev,ino)];
	hash_bucket = dir_hash_table[hash_dev_ino(dev,ino)];

	while (hash_bucket != NULL) {
		if (hash_bucket->dev == dev && hash_bucket->ino == ino) {
			last_entry->next = hash_bucket->next;
			directory_release(hash_bucket);
			ADD_TO_ZONE(dir_hash_entry_zone, hash_bucket);
			return;
		}
		last_entry = hash_bucket;
		hash_bucket = hash_bucket->next;
	}
}

void
directory_release(entry)
	register struct dir_hash_entry *	entry;
{
	register int			i;
	register struct hash_entry *	bucket;
	register struct hash_entry *	last_entry;
	register struct hash_entry **	hash_table;

	if (entry != NULL) {
		if ((hash_table = entry->hash_table) != NULL) {
			for (i = 0; i < HASHSIZE; i++) {
				if ((bucket = hash_table[i]) != NULL) {
					hash_table[i] = NULL;
					while (bucket != NULL) {
					    last_entry = bucket->next;
					    hash_entry_release(bucket);
					    bucket = last_entry;
					}
				}
			}
			entry->hash_table = NULL;
			ADD_TO_ZONE(hash_table_zone, hash_table);
		}
	}
}

off_t
directory_scan(inode_pointer, space_needed, parent_entry)
	struct inode *		inode_pointer;
	int			space_needed;
	struct dir_hash_entry *	parent_entry;
{
	struct fs* 		fs;
	off_t			cur_offset 	= 0;
	int			prev_size	= 0;
	off_t			offset_in_block	= 0;
	off_t			last_offset;
	struct buf *		buffer 		= NULL;

	fs  = inode_pointer->i_fs;
	
	if (parent_entry != NULL) {
		/* Make sure we do not deallocate parent_entry! */
		parent_entry->ref_count++;
		if (parent_entry->hash_table == NULL) {
			register int 		i;
			parent_entry->hash_table =
			     (struct hash_entry **)dir_alloc(hash_table_zone);
			for (i = 0; i < HASHSIZE; i++)
				(parent_entry->hash_table)[i] = NULL;
		}
	}

	last_offset = roundup(inode_pointer->i_size, DIRBLKSIZ);

	while (cur_offset < last_offset) {
		int		record_length;
		int		dir_size;
		struct direct * dir_entry;

		if (blkoff(fs, cur_offset) == 0) {
			if (buffer != NULL) brelse(buffer);
			buffer=blkatoff(inode_pointer,cur_offset,(char **)0);
			if (buffer == NULL) {
				if (parent_entry != NULL) 
					parent_entry->ref_count--;
				return (cur_offset);
			}
			offset_in_block = 0;
		}

		if ((cur_offset & DIRBLKSIZ-1) == 0) prev_size = 0;

		dir_entry = (struct direct *)(buffer->b_un.b_addr + 
					      offset_in_block);

		record_length = dir_entry->d_reclen;

		if (record_length == 0) {
			dirbad(inode_pointer, cur_offset, "bad entry");
			cur_offset += DIRBLKSIZ - (cur_offset&(DIRBLKSIZ-1));
			offset_in_block += DIRBLKSIZ - 
					   (offset_in_block & (DIRBLKSIZ-1));
			continue;
		}

		dir_size = DIRSIZ(dir_entry);
		if (dir_entry->d_ino == 0) dir_size = 0;

		if ((dir_entry->d_ino != 0) &&
		    (record_length >= dir_size) &&
		    (space_needed == 0)) {
			directory_file_enter(inode_pointer, 
				      dir_entry->d_name,
				      dir_entry->d_namlen,
				      dir_entry->d_ino,
				      cur_offset,
				      prev_size,
				      record_length);
		} else if ((space_needed > 0) && 
 		  	   ((record_length - dir_size) >= space_needed)) {
			 	if (buffer != NULL) brelse(buffer);
				if (parent_entry != NULL) 
					parent_entry->ref_count--;
				return(cur_offset);
		}

		prev_size = record_length;
		cur_offset += record_length;
		offset_in_block += record_length;
	}

 	if (buffer != NULL) brelse(buffer);
	if (parent_entry != NULL) parent_entry->ref_count--;
	return(last_offset);
}

struct hash_entry *
directory_file_lookup(ip, name, last_entry)
	register struct inode *	ip;
	char *			name;
	struct hash_entry **	last_entry;
{
	struct hash_entry ** 		hash_table;
	register struct hash_entry *	hash_bucket;
	register struct dir_hash_entry *parent_entry;
	int				hash_offset;

	parent_entry = dir_lookup(ip->i_dev, ip->i_number);
	while (parent_entry == NULL) {
		/* Add new directory to cache if this inode is a directory. */
		if ((ip->i_mode&IFMT) != IFDIR) return (NULL);
		dir_enter(ip->i_dev, ip->i_number);
		parent_entry = dir_lookup(ip->i_dev, ip->i_number);
	}

	if (parent_entry->hash_table == NULL) {
		(void) directory_scan(ip, 0, parent_entry);
	}

	hash_table = parent_entry->hash_table;
	file_hash(name, hash_offset);
	hash_bucket = hash_table[hash_offset];

	if (last_entry != NULL)
		*last_entry = (struct hash_entry *)&hash_table[hash_offset];

	while (hash_bucket != NULL) {
		if ((name[hash_bucket->name_length] == '\0') &&
		    !bcmp(hash_bucket->name, name,hash_bucket->name_length)) {
			return (hash_bucket);
		}
		if (last_entry != NULL)
			*last_entry = hash_bucket;
		hash_bucket = hash_bucket->next;
	}
	return (NULL);
}

void
directory_file_enter(dp,c_name,c_len,c_ino,c_offset,c_prev_size,c_reclen) 
	struct inode *		dp;
	char *			c_name;
	int			c_len;
	ino_t			c_ino;
	off_t			c_offset;
	int			c_prev_size;
	int			c_reclen;
{									
	register struct hash_entry *	entry;
	struct dir_hash_entry *		dir_entry;
	struct hash_entry **		hash_table;
	int				hash_offset;

	entry = (struct hash_entry *)dir_alloc(hash_entry_zone);	
									
	entry->ino		= c_ino;				
	entry->dir_offset	= c_offset; 				
	entry->prev_size	= c_prev_size;			
									
	if (c_len < SMALLNAMELEN) 
		entry->name	= (char *) dir_alloc(small_name_zone);
	else if (c_len < MEDIUMNAMELEN)
		entry->name	= (char *) dir_alloc(medium_name_zone);
	else	entry->name	= (char *) dir_alloc(big_name_zone);

	entry->name_length	= c_len;				
	entry->reclen		= c_reclen;				
									
	(void) copystr(c_name, entry->name, c_len, (u_int *)0);	

	/*
	 * Once we have built an entry, see if there is a place to put
	 * it.  We do the work in this order in case the directory itself
	 * was deallocated while we were allocating storage.
	 */

	dir_entry = dir_lookup(dp->i_dev, dp->i_number);
	if (dir_entry != NULL) {
		hash_table = dir_entry->hash_table;
		if (hash_table != NULL) {
			file_hash(c_name, hash_offset);
			entry->next = hash_table[hash_offset];
			hash_table[hash_offset] = entry;
			return;
		}
	}

	/* 
	 * In this case, there is no place to put entry. So just release it.
	 */
	hash_entry_release(entry);
}

void
directory_file_remove(dp, name)
	register struct inode *	dp;
	char *			name;
{
	register struct hash_entry * 	entry;
	struct hash_entry *		last_entry;

	entry = directory_file_lookup(dp, name, &last_entry);
	if (entry != NULL) {
		last_entry->next = entry->next;
		hash_entry_release(entry);
	}
}

char *
scan_name_segment(name_params, cp)
	struct nameidata *	name_params;
	register char *		cp;
{
	register int	i;
	register char *	ncp;
	int 		flag;

	/*
	 * Parse next portion of name pointed to by cp.
	 * Leave result in name_params.
	 */

	flag = name_params->ni_nameiop & DELETE;
	ncp = name_params->ni_dent.d_name;

	i = 0;
	while ((*cp != 0) && (*cp != '/')) {
		if ((i++) > MAXNAMLEN) {
			u.u_error = ENAMETOOLONG;
			return (NULL);
		}
		if ((*ncp = *cp) & 0200)
			if ((*cp & 0377) == ('/'|0200) || (!flag)) {
				u.u_error = EINVAL;
				return (NULL);
			}
		ncp++; cp++;
	}

	name_params->ni_dent.d_namlen = i;
	*ncp = '\0';
	return ((i == 0) ? NULL : cp);
}

struct inode * 
namei(name_params)
	struct nameidata * name_params;
{
	register char *		cp;	/* pointer into pathname argument */

	/* these variables refer to things which must be freed or unlocked */

	register struct inode *	dp = 0;	/* the directory we are searching */
	register struct fs *	fs;	/* file system that directory is in */
	
	/* buffer storing pathname argument*/
	struct buf *		name_buffer;

	/* these variables hold information about the search for a slot */

	/* number of symbolic links taken */
	int 			nlink = 0;

	struct inode *		pdp;	/* saved dp during symlink work */
	int 			error, i, rfs_flag;
	int 			lock_parent;
	int 			flag;	/* op ie, LOOKUP, CREATE, or DELETE */
	int 			quoted = 0;
	int  			okremote;

	struct hash_entry *	entry;

	/*
	 * namei is self-initializing!
	 */
	if (namei_first_time) {
		init_name_directory();
		namei_first_time = FALSE;
	}

	/* Allocate buffer to store name: */
	alloc_buffer(&name_buffer);

	/* Copy name into allocated buffer: */
	if (name_params->ni_segflg == UIO_SYSSPACE) {
		error = copystr((caddr_t) name_params->ni_dirp, 
				(caddr_t) name_buffer->b_un.b_addr, 
				MAXPATHLEN, (u_int *) 0);
	}
	else {
		error = copyinstr((caddr_t) name_params->ni_dirp, 
				  (caddr_t) name_buffer->b_un.b_addr, 
				  MAXPATHLEN, (u_int *) 0);
	}
	if (error) {
		u.u_error = error;
		goto bad;
	}

#if	MACH_DEBUG
	if (namei_print)
		uprintf("namei: flags=0x%x, program=%s, name=%s\n",
				name_params->ni_nameiop,
				u.u_comm,
				name_buffer->b_un.b_addr);
	namei_count++;	/* Not worth locking */
#endif	MACH_DEBUG

	/* Setup flags for future reference. */
	flag = name_params->ni_nameiop &~ 
			(KEEPNAMEBUF|OKREMOTE|LOCKPARENT|NOCACHE|FOLLOW);
	lock_parent = name_params->ni_nameiop & LOCKPARENT;

	u.u_rfsncnt++;	/* Tell rfs code how many times namei is called. */
			/* Used for renames. */

#if	VICE
	/* Vice counter */
	u.u_rmt_ncnt++;
#endif	VICE

	/* Set flag for remote file system parsing. */
	rfs_flag = URFS_CDIR;
	okremote = ((name_params->ni_nameiop&OKREMOTE) != 0
		     &&
		     (u.u_modes&UMODE_NOFOLLOW) == 0
		   );

	/* We come here whenever we must start parsing name from scratch. */
reroot:

#if	VICE
startdir:
	/* Check for Vice error case */
	if (u.u_rmt_path_buf != NULL)
	    panic("namei:  u.u_rmt_path_buf != NULL");
	u.u_rmt_dev = NODEV;
#endif	VICE

	cp = name_buffer->b_un.b_addr;
	
	/* Check for leading "/" or "//": */
	if (*cp == '/') {

		/* Strip extra "/" characters in filename. */
		while (*cp == '/') {
			cp++;
			increment_quoted;
		}
		
		/* We start at either local root or remote root. */
		if ((dp = u.u_rdir) == NULL)
			dp = rootdir;
		else
			rfs_flag = URFS_RDIR;	
	}	
	else {
#if	VICE
		if (u.u_rmtWd.dev != NODEV) {	/* Send request to Venus */
		    	u.u_rmt_dev = u.u_rmtWd.dev;
		    	goto remote;
		}
#endif	VICE
		/* We start from current directory. */
		dp = u.u_cdir;
	}

	/* 
	 * Now we are going to be using the directory inode pointer
	 * (dp).  We must get it's file system pointer and lock the
	 * inode to insure we are the only user.
	 */	
	fs = dp->i_fs;
	ILOCK(dp);
	increment_inode_count(dp);

	/*
	 * Setup name_params block for return if necessary. 
	 */

	name_params->ni_pdir = (struct inode *)0xc0000000;
	name_params->ni_endoff = 0;

	/*
	 * Check if base directory is remote.
	 */
	if ((u.u_rfs&rfs_flag) && (okremote && u.u_rfscode != 0)) 
		goto rfsdir;

	/*
	 * Never follow trailing symbolic links if that mode has
	 * been set for the process.
	 */
	if (u.u_modes & UMODE_NOFOLLOW)
		name_params->ni_nameiop &= ~FOLLOW;


	/* Now, scan next name component and process: */
dirloop:
	/*
	 * Check accessiblity of directory.
	 */
	if ((dp->i_mode&IFMT) != IFDIR) {
		u.u_error = ENOTDIR;
		goto bad;
	}
	if (access(dp, IEXEC))
		goto bad;

dirloop2:
	if (quoted < QUOTED)
		quoted = 0;

	u.u_error = 0;
	cp = scan_name_segment(name_params, cp);
	if (cp == NULL) {
		if (u.u_error)
			goto bad;

		/* Name is null or bad in some way. */
		if ((flag != LOOKUP) || lock_parent) {
			u.u_error = EISDIR;
			goto bad;
		}
		free_buffer(name_buffer);
		clear_vice_request;
		return (dp);
	}
	
	set_directory_lock;

	entry = directory_file_lookup(dp, name_params->ni_dent.d_name, NULL);

	if (entry == NULL) {

		clear_directory_lock;

		/* 
	 	 * We could not find the file. This is ok only if we
		 * are creating a new file.
		 */

		if ((flag == CREATE) &&
		    (*cp == '\0') &&
		    (dp->i_nlink != 0)) {
			/* 
			 * We are creating a new entry.  Check if ok
			 * and return.
			 */
			if (access(dp, IWRITE)) goto bad;
			dp->i_flag |= IUPD | ICHG;
			free_buffer(name_buffer);
			name_params->ni_pdir = dp;
			clear_vice_request;
			return (NULL);
		}

		/* Otherwise, we have an error. */
		u.u_error = ENOENT;
		goto bad;
	}

	/* 
	 * Entry found.  Now check each possible case for handling it.
	 */
	name_params->ni_dent.d_ino    = entry->ino;
	name_params->ni_dent.d_reclen = entry->reclen;
	name_params->ni_dent.d_namlen = entry->name_length;
	name_params->ni_offset 	      = entry->dir_offset;
	name_params->ni_count  	      = entry->prev_size;

	clear_directory_lock;

	/*
	 * Check for file deletion case.
	 */
	if (flag == DELETE && *cp == '\0') {
		/* We want to delete this file.  Check for ok. */
		if (access(dp, IWRITE)) goto bad;

		pdp = dp;
		name_params->ni_pdir = pdp;
		if (lock_parent) {
			if (dp->i_number == entry->ino) {
				increment_inode_count(dp);
			} else {
				dp = iget(dp->i_dev, fs, entry->ino);
				if (dp == NULL) {
					iput(pdp);
					goto bad;
				}
				
				if ((pdp->i_mode & ISVTX) &&
				    u.u_uid != 0 &&
				    u.u_uid != pdp->i_uid &&
				    dp->i_uid != u.u_uid) {
					iput(pdp);
					u.u_error = EPERM;
					goto bad;
				}
			}
		}
		free_buffer(name_buffer);
		clear_vice_request;
		return (dp);
	}


	/*
	 * Special handling for ".." allowing chdir out of mounted
	 * file system: indirect .. in root inode to reevaluate
	 * in directory file system was mounted on.
	 */
	if (isdotdot(name_params)) {
		if (dp == u.u_rdir) {
#if	MACH_RFS
			/*
			 *  If we are about to go above the logical root
			 *  directory and the process has indicated that it
			 *  does not want this to happen transparently, return
			 *  a designated error instead of continuing.  The
			 *  error used is chosen to not overlap any others
			 *  errors that may be legitimately returned so that
			 *  the process make take appropriate action as
			 *  required.
			 *
			 *  Normally, the calling process has set this flag in
			 *  order to specially processon the remainder of the
			 *  path name following the reference to the super-root
			 *  so, provided that the keep name buffer flag was
			 *  specified, update the name pointer and arrange to
			 *  save the buffer for the caller.
			 */
			if (u.u_rfs&URFS_EROOT) {
				/*
				 *  If I understand this code, this shouldn't
				 *  be possible ...
				 */
				iput(dp);
				if (name_params->ni_nameiop&KEEPNAMEBUF) {
					name_params->ni_dirp = cp;
					name_params->ni_nameiop &= ~KEEPNAMEBUF;
					*ni_nbpp(name_params) = name_buffer;
				} else {
					free_buffer(name_buffer);
				}
				u.u_error = ERANGE;
				clear_vice_request;
				return(NULL);
			}
			if (rfs_rdir != u.u_rdir)
#endif	MACH_RFS
				name_params->ni_dent.d_ino = dp->i_number;
		} else if (name_params->ni_dent.d_ino == ROOTINO &&
		   dp->i_number == ROOTINO) {
			for (i = 1; i < NMOUNT; i++)
			if (mount[i].m_bufp != NULL &&
			   mount[i].m_dev == dp->i_dev) {
				iput(dp);
				dp = mount[i].m_inodp;
				ILOCK(dp);
				increment_inode_count(dp);
				fs = dp->i_fs;
				cp -= 2;     /* back over .. */
				goto dirloop2;
			}
		}
	}

	/*
	 * If rewriting (rename), return the inode and the
	 * information required to rewrite the present directory
	 * Must get inode of directory entry to verify it's a
	 * regular file, or empty directory.  
	 */
	if ((flag == CREATE && lock_parent) && *cp == 0) {
		if (access(dp, IWRITE))
			goto bad;
		name_params->ni_pdir = dp;		/* for dirrewrite() */
		/*
		 * Careful about locking second inode. 
		 * This can only occur if the target is ".". 
		 */
		if (dp->i_number == name_params->ni_dent.d_ino) {
			u.u_error = EISDIR;		/* XXX */
			goto bad;
		}
		dp = iget(dp->i_dev, fs, name_params->ni_dent.d_ino);
		if (dp == NULL) {
			iput(name_params->ni_pdir);
			goto bad;
		}
		free_buffer(name_buffer);
		clear_vice_request;
		return (dp);
	}

	/*
	 * Check for symbolic link, which may require us to massage the
	 * name before we continue translation.  We do not `iput' the
	 * directory because we may need it again if the symbolic link
	 * is relative to the current directory.  Instead we save it
	 * unlocked as "pdp".  We must get the target inode before unlocking
	 * the directory to insure that the inode will not be removed
	 * before we get it.  We prevent deadlock by always fetching
	 * inodes from the root, moving down the directory tree. Thus
	 * when following backward pointers ".." we must unlock the
	 * parent directory before getting the requested directory.
	 * There is a potential race condition here if both the current
	 * and parent directories are removed before the `iget' for the
	 * inode associated with ".." returns.  We hope that this occurs
	 * infrequently since we cannot avoid this race condition without
	 * implementing a sophisticated deadlock detection algorithm.
	 * Note also that this simple deadlock detection scheme will not
	 * work if the file system has any hard links other than ".."
	 * that point backwards in the directory structure.
	 */
	pdp = dp;
	if (isdotdot(name_params)) {
		IUNLOCK(pdp);	/* race to get the inode */
		dp = iget(dp->i_dev, fs, name_params->ni_dent.d_ino);
		if (dp == NULL)
			goto bad2;
	} else if (dp->i_number == name_params->ni_dent.d_ino) {
		increment_inode_count(dp);
	} else {
		dp = iget(dp->i_dev, fs, name_params->ni_dent.d_ino);
		IUNLOCK(pdp);
		if (dp == NULL)
			goto bad2;
	}

#if	MACH_RFS
	/* 
	 *  Check for remote name.
	 */
	if (okremote &&
            quoted < QUOTED &&
            u.u_rfscode != 0 && isrfslnk(dp)) {
	  	extern struct inode *rfs_namei();
 
		irele(pdp);
		/*
		 *  We enter here if the current/root directory was determined
		 *  to be remote and it is the base for the path name.  The
		 *  entire name will be interpreted remotely.
		 */
rfsdir:
		/*
		 *  The only time we should pass the null string through is
		 *  when this was the entire original name.  Otherwise, if the
		 *  residual name is null at this point, it actually represents
		 *  the remote root (e.g.  from a name like "/../q").  Since
		 *  the remote file system code may pass a name back to us
		 *  through the same pointer, change the name to "/" in place
		 *  within the buffer rather than setting it to a constant string.
		 */
		if (*cp == 0 && cp != name_buffer->b_un.b_addr)
			*--cp = '/';
		name_params->ni_dirp = cp;
		*ni_nbpp(name_params) = name_buffer;
		dp = rfs_namei(dp, name_params);
		if (u.u_error == ELOCAL)
		{
			u.u_error = 0;
			name_buffer->b_un.b_addr[0] = '/';
			name_buffer->b_un.b_addr[1] = '.';
			name_buffer->b_un.b_addr[2] = '.';
			goto reroot;
		}
		/*
		 *  This flag may be set on entry to namei() but is not checked
		 *  until we are about to release the buffer so it may also be
		 *  set before returning from rfs_namei() above if convenient.
		 *  We clear the flag on return to indicate that the buffer
		 *  has indeed been kept (to simplify figuring this out in the
		 *  caller).
		 */
		if (name_params->ni_nameiop&KEEPNAMEBUF)
		{
			name_params->ni_nameiop &= ~KEEPNAMEBUF;
		}
		else
		{
			free_buffer(name_buffer);
			*ni_nbpp(name_params) = NULL;		/* safety */
		}
		clear_vice_request;
		return(dp);
	}
#endif	MACH_RFS
	fs = dp->i_fs;

	/*
	 * Check for symbolic link
	 */
	if ((dp->i_mode & IFMT) == IFLNK && quoted < QUOTED &&
			((name_params->ni_nameiop & FOLLOW) || *cp == '/')) {
		u_int pathlen = strlen(cp) + 1;

		if (dp->i_size + pathlen >= MAXPATHLEN - 1) {
			u.u_error = ENAMETOOLONG;
			goto bad2;
		}
		if (++nlink > MAXSYMLINKS) {
			u.u_error = ELOOP;
			goto bad2;
		}
		ovbcopy(cp, name_buffer->b_un.b_addr + dp->i_size, pathlen);
#if	MACH_FASTLINK
		/*
		 *	Encore UMAX fast symbolic link support
		 */
		if (use_fastlinks && (dp->i_icflags & IC_FASTLINK) != 0) {
			copystr(dp->i_symlink, name_buffer->b_un.b_addr,
				(int)dp->i_size, (u_int *)0);
		}
		else {
#endif	MACH_FASTLINK
			u.u_error =
			 rdwri(UIO_READ, dp, name_buffer->b_un.b_addr,
				(int)dp->i_size, (off_t)0, 1, (int *)0);
			if (u.u_error)
				goto bad2;
#if	MACH_FASTLINK
		}
#endif	MACH_FASTLINK
		cp = name_buffer->b_un.b_addr;
		iput(dp);
		if (*cp == '/') {
			irele(pdp);
			while (*cp == '/')
			{
 				cp++;
				increment_quoted;
			}
			if ((dp = u.u_rdir) == NULL)
				dp = rootdir;
			ILOCK(dp);
			increment_inode_count(dp);
		} else {
			dp = pdp;
			ILOCK(dp);
		}
		fs = dp->i_fs;
		goto dirloop;
	}

	/*
	 * Not a symbolic link.  If more pathname,
	 * continue at next component, else return.
	 */
	if (*cp == '/') {
		while (*cp == '/')
		{
 			cp++;
			increment_quoted;
		}
		irele(pdp);
		goto dirloop;
	}

	free_buffer(name_buffer);

	if (lock_parent)
		name_params->ni_pdir = pdp;
	else
		irele(pdp);

	clear_vice_request;
	return (dp);

	/* 
	 * Entry points to the ITC/Remote file system
	 * (as well as destinations for real errors--UGH!!!).
	 *
	 * bad2:   jumped to when pathname expansion encounters
	 *         a node with a Vice fs mounted on it.
	 *
	 * remote: jumped to at the start of a relative pathname
	 *         expansion when the currdir is in Vice.
	 */

bad2:
	irele(pdp);

remote:
bad:
	if (dp)
		iput(dp);

#if	VICE
	if (u.u_rmt_dev != NODEV && !u.u_error)
	    if (!u.u_rmt_requested)
	    {
		u.u_error = EINVAL;
	    }
	    else
	    {
		extern struct inode	*rmt_namei();

		if (*cp != '/' && cp > name_buffer->b_un.b_addr)
			*--cp = '/';		/* Hack so that paths relative
						   to remote file system root
						   always begin with '/' */
		name_params->ni_dirp = cp;
		dp = rmt_namei(name_params, name_buffer);
		if (!u.u_error)			/* New pathname returned */
			if (++nlink > MAXSYMLINKS) {
				u.u_error = ELOOP;
				goto bad;
			}
			else
				goto startdir;	/* Retry */
		else {
			free_buffer(name_buffer);
			clear_vice_request;
			return(NULL);
		}
	    }
#endif	VICE

	free_buffer(name_buffer);
	clear_vice_request;
	return (NULL);
}

dirbad(ip, offset, how)
	struct inode *ip;
	off_t offset;
	char *how;
{

	printf("%s: bad dir ino %d at offset %d: %s\n",
	    ip->i_fs->fs_fsmnt, ip->i_number, offset, how);
}

/*
 * Write a directory entry after a call to namei, using the parameters
 * which it left in the u. area.  The argument ip is the inode which
 * the new directory entry will refer to.  
 * The u. area field name_params->ni_pdir is
 * a pointer to the directory to be written, which was left locked by
 * namei.
 */
direnter(ip, name_params)
	struct inode *ip;
	register struct nameidata *name_params;
{
	register struct direct *ep, *nep;
	register struct inode *	dp = name_params->ni_pdir;
	struct buf *		bp;
	int			offset;
	int 			spacefree, error = 0;
	u_int 			dsize;
	int 			newentrysize;
	char *			dirbuf;
	struct dir_hash_entry *	dir_entry;
	struct hash_entry *	file_entry;
	char			name_buffer[MAXNAMLEN + 1];
	char			next_name_buffer[MAXNAMLEN + 1];	

	set_directory_lock;
	
	name_params->ni_dent.d_ino = ip->i_number;
	nep = &name_params->ni_dent;
	newentrysize = DIRSIZ(nep);

	dir_entry = dir_lookup(dp->i_dev, dp->i_number);
	if (dir_entry != NULL) {
		if (((offset = dir_entry->last_off) == 0) ||
		     (dir_entry->last_unused < newentrysize))
			offset = directory_scan(dp, newentrysize, NULL);
	} else 
		offset = directory_scan(dp, newentrysize, NULL);

	if (offset == roundup(dp->i_size, DIRBLKSIZ)) {
		/*
		 * If offset is at end of directory
		 * directory_scan could find no space in the
		 * directory. In this case 
		 * offset will be on a 
		 * block boundary and we will write the new entry into a fresh
		 * block.
		 */
		name_params->ni_dent.d_reclen = DIRBLKSIZ;
		error = rdwri(UIO_WRITE, dp, (caddr_t)&name_params->ni_dent,
		    newentrysize, offset, 1, (int *)0);
		if (DIRBLKSIZ > dp->i_fs->fs_fsize)
			panic("wdir: blksize"); /* XXX-should grow w/bmap()*/
		else
			dp->i_size = roundup(dp->i_size, DIRBLKSIZ);

		/*
		 * Only enter name in cache if there is no error.
		 * If there is an error, flush the cache.
		 */
		if (error) {
			printf("Flushing cache on directory write error.\n");
			dir_remove(dp->i_dev, dp->i_number);
		} else {
			dir_entry = dir_lookup(dp->i_dev, dp->i_number);
			if (dir_entry != NULL) {
				dir_entry->last_off = offset;
				dir_entry->last_unused= DIRBLKSIZ-newentrysize;
				directory_file_enter(dp, 
					      nep->d_name,
					      nep->d_namlen,
					      ip->i_number,
					      offset,
					      0,
					      DIRBLKSIZ);
			}
		}

		iput(dp);

		clear_directory_lock;

		return (error);
	}

	/*
	 * We have found space at "offset" for the new
	 * entry in the range offset to offset+count
	 * in the directory.
	 */

	/*
	 * Get the block containing the space for the new directory
	 * entry.  Should return error by result instead of u.u_error.
	 */
	bp = blkatoff(dp, offset, (char **)&dirbuf);
	if (bp == 0) {
		iput(dp);

		clear_directory_lock;

		return (u.u_error);
	}

	ep = (struct direct *)dirbuf;
	if (ep->d_ino == 0) {
		dsize = 0;
		name_params->ni_dent.d_reclen = spacefree = ep->d_reclen;
		bcopy((caddr_t)&name_params->ni_dent,
			(caddr_t)ep,(u_int)newentrysize);
		if ((offset + dsize + spacefree) & (DIRBLKSIZ-1)) {
			/*
		 	 * We must get the name of the next entry.
		 	 */
			copystr(((struct direct *)
				((char *)ep + spacefree))->d_name,
				next_name_buffer,MAXNAMLEN,0);
		}
		bwrite(bp);
		
	} else {
		dsize = DIRSIZ(ep);
		spacefree = ep->d_reclen - dsize;
		if (spacefree < newentrysize) panic("wdir: compact2");
		name_params->ni_dent.d_reclen = spacefree;

		/*
		 * To avoid deadlocking on bp, we must copy out the
		 * file name and release the buffer before calling 
		 * directory_file_lookup().
		 */
		copystr(ep->d_name,name_buffer,MAXNAMLEN,0);
		if ((offset + dsize + spacefree) & (DIRBLKSIZ-1)) {
			/*
		 	 * We must get the name of the next entry now.
		 	 */
			copystr(((struct direct *)
				((char *)ep+ep->d_reclen))->d_name,
				next_name_buffer,MAXNAMLEN,0);
		}
		ep->d_reclen = dsize;

		ep = (struct direct *)((char *)ep + dsize);
		bcopy((caddr_t)&name_params->ni_dent,
			(caddr_t)ep,(u_int)newentrysize);
		bwrite(bp);		
	    	file_entry = directory_file_lookup(dp, name_buffer, NULL);
		if (file_entry != NULL) {
			file_entry->reclen = dsize;
		}
	}

	/* 
	 * Enter cache entry for file we have put in directory.
	 */
	dir_entry = dir_lookup(dp->i_dev, dp->i_number);
	if (dir_entry != NULL) {
		/* Update last known hole information. */
		dir_entry->last_off = offset + dsize;
		dir_entry->last_unused = spacefree-newentrysize;

		directory_file_enter(dp, 
			       nep->d_name,
			       nep->d_namlen,
			       ip->i_number,
			       offset+dsize,
			       dsize,
			       spacefree);
	}

	/* Update cache entry for next file in directory. */
	if ((offset + dsize + spacefree) & (DIRBLKSIZ-1)) {
		file_entry = directory_file_lookup(dp, next_name_buffer, NULL);
		if (file_entry != NULL) {
			file_entry->prev_size = spacefree;
		}
	}

	dp->i_flag |= IUPD|ICHG;
	iput(dp);

	clear_directory_lock;

	return (error);
}

/*
 * Remove a directory entry after a call to namei.
 * name_params contains the inode pointer of the
 * directory we are in and the name of the file
 * being deleted.  (It also contains other information
 * which may be wrong and is not used.)
 */
dirremove(name_params)
	register struct nameidata *name_params;
{
	register struct inode *	dp = name_params->ni_pdir;
	register struct buf *	bp;
	struct direct *		ep;
	struct direct 		direct_copy;
	struct direct *		ep_copy = &direct_copy;
	char 			name_buffer[MAXNAMLEN + 1];
	struct direct * 	next_ep = (struct direct *) NULL;
	struct dir_hash_entry *	dir_entry;
	struct hash_entry * 	file_entry;
	char *			file_name = name_params->ni_dent.d_name;
	ino_t			file_ino;
	int			reclen, prev_size, dir_offset;

	set_directory_lock;

	/*
	 * Return here if there is a cache consistency failure.
	 */
restart:
	/*
	 * Find file_name again in directory cache.  (Cache may have
	 * changed since lookup.
	 */
	file_entry = directory_file_lookup(dp, file_name, NULL);
	if (file_entry == NULL) {
		printf("Trying to delete a non-existant file.\n");
		clear_directory_lock;
		return (0);
	}

	dir_offset = file_entry->dir_offset;
	prev_size  = file_entry->prev_size;
	file_ino   = file_entry->ino;
	reclen	   = file_entry->reclen;

	if (prev_size == 0) {
		/*
		 * First entry in block: set d_ino to zero.
		 */
		name_params->ni_dent.d_ino = 0;
		(void) rdwri(UIO_WRITE, dp, (caddr_t)&name_params->ni_dent,
		    		(int)DIRSIZ(&name_params->ni_dent), 
				dir_offset, 1, (int *)0);
	} else {
		/*
		 * Collapse new free space into previous entry.
		 */
		bp = blkatoff(dp, dir_offset - prev_size, (char **)&ep);
		if (bp == 0) {
			clear_directory_lock;
			return (0);
		}

		if (ep->d_reclen != prev_size) {
			printf("Mismatched sizes: %d, %d\n",
						ep->d_reclen, prev_size);
			printf("Files: %s, %s\n", ep->d_name, file_name);
			printf("Inodes: %d, %d\n",ep->d_ino, file_ino);

			/* Uncache directory and try again */
			brelse(bp);
			dir_remove(dp->i_dev, dp->i_number);
			goto restart;			
		}
		ep->d_reclen += reclen;
		
		/*
		 * Before the following directory_file_lookup(), we must
		 * free the buffer that we currently own, otherwise, we could
		 * deadlock in directory_scan() when it tries to
		 * allocate a buffer.  Thus we copy the information from the
		 * buffer to the stack in preparation for releasing the buffer
		 */

		copystr(ep->d_name,ep_copy->d_name,ep->d_namlen + 1,0);
		ep_copy->d_ino = ep->d_ino;
		ep_copy->d_reclen = ep->d_reclen;
		 
		if ((dir_offset + reclen) & (DIRBLKSIZ-1)) {		
			next_ep = (struct direct *) ((char *)ep+ep->d_reclen);
			copystr(next_ep->d_name,name_buffer,MAXNAMLEN,0);
		}
	
		bwrite(bp);
		ep = ep_copy;
		
		if (ep->d_ino) {
			file_entry=directory_file_lookup(dp,ep->d_name,NULL);
			if (file_entry != NULL) 
				file_entry->reclen = ep->d_reclen;
		}
		if (next_ep) {
			file_entry=directory_file_lookup(dp,name_buffer,NULL);
			if (file_entry != NULL) 
				file_entry->prev_size = ep->d_reclen;
		}
		dp->i_flag |= IUPD|ICHG;
	}

	dir_entry = dir_lookup(dp->i_dev, dp->i_number);
	if (dir_entry != NULL) {
		dir_entry->last_off = 0;
		directory_file_remove(dp, file_name);
		dir_remove(dp->i_dev, file_ino);
	}

	clear_directory_lock;
	return (1);
}

/*
 * Rewrite an existing directory entry to point at the inode
 * supplied.  The parameters describing the directory entry are
 * set up by a call to namei.
 */
dirrewrite(dp, ip, name_params)
	struct inode *dp, *ip;
	struct nameidata *name_params;
{
	struct hash_entry * file_entry;
	int		    dir_offset;

	set_directory_lock;

	file_entry=directory_file_lookup(dp,name_params->ni_dent.d_name,NULL);

	if (file_entry != NULL) {
		name_params->ni_dent.d_ino = ip->i_number;
		file_entry->ino = ip->i_number;
		dir_offset = file_entry->dir_offset;
		u.u_error = rdwri(UIO_WRITE,dp,(caddr_t)&name_params->ni_dent,
				(int)DIRSIZ(&name_params->ni_dent), 
				dir_offset, 1, (int *)0);
		dir_remove(dp->i_dev, name_params->ni_dent.d_ino);
	} 

	iput(dp);
	clear_directory_lock;
}

/*
 * Return buffer with contents of block "offset"
 * from the beginning of directory "ip".  If "res"
 * is non-zero, fill it in with a pointer to the
 * remaining space in the directory.
 */
struct buf *
blkatoff(ip, offset, res)
	struct inode *ip;
	off_t offset;
	char **res;
{
	register struct fs *fs = ip->i_fs;
	daddr_t lbn = lblkno(fs, offset);
	int bsize = blksize(fs, ip, lbn);
	register struct buf *bp;
	daddr_t bn;

	u.u_error = 0;

	bn = bmap(ip, lbn, B_READ, bsize);

	if (u.u_error)
		return (0);

	if (bn == (daddr_t)-1) {
		dirbad(ip, offset, "hole in dir");
		return (0);
	}
	bp = bread(ip->i_dev, fsbtodb(fs, bn), bsize);
	if (bp->b_flags & B_ERROR) {
		brelse(bp);
		return (0);
	}
	if (res)
		*res = bp->b_un.b_addr + blkoff(fs, offset);
	return (bp);
}

/*
 * Check if a directory is empty or not.
 * Inode supplied must be locked.
 *
 * Using a struct dirtemplate here is not precisely
 * what we want, but better than using a struct direct.
 *
 * NB: does not handle corrupted directories.
 */
dirempty(ip, parentino)
	register struct inode *ip;
	ino_t parentino;
{
	register off_t off;
	struct dirtemplate dbuf;
	register struct direct *dp = (struct direct *)&dbuf;
	int error, count;

#define MINDIRSIZ (sizeof (struct dirtemplate) / 2)

	for (off = 0; off < ip->i_size; off += dp->d_reclen) {
		error = rdwri(UIO_READ, ip, (caddr_t)dp, MINDIRSIZ,
		    off, 1, &count);
		/*
		 * Since we read MINDIRSIZ, residual must
		 * be 0 unless we're at end of file.
		 */
		if (error || count != 0)
			return (0);
		/* avoid infinite loops */
		if (dp->d_reclen == 0)
			return (0);
		/* skip empty entries */
		if (dp->d_ino == 0)
			continue;
		/* accept only "." and ".." */
		if (dp->d_namlen > 2)
			return (0);
		if (dp->d_name[0] != '.')
			return (0);
		/*
		 * At this point d_namlen must be 1 or 2.
		 * 1 implies ".", 2 implies ".." if second
		 * char is also "."
		 */
		if (dp->d_namlen == 1)
			continue;
		if (dp->d_name[1] == '.' && dp->d_ino == parentino)
			continue;
		return (0);
	}
	return (1);
}

/*
 * Check if source directory is in the path of the target directory.
 * Target is supplied locked, source is unlocked.
 * The target is always iput() before returning.
 */
checkpath(source, target)
	struct inode *source, *target;
{
	struct dirtemplate dirbuf;
	register struct inode *ip;
	int error = 0;

	ip = target;
	if (ip->i_number == source->i_number) {
		error = EEXIST;
		goto out;
	}
	if (ip->i_number == ROOTINO)
		goto out;

	for (;;) {
		if ((ip->i_mode&IFMT) != IFDIR) {
			error = ENOTDIR;
			break;
		}
		error = rdwri(UIO_READ, ip, (caddr_t)&dirbuf,
			sizeof (struct dirtemplate), (off_t)0, 1, (int *)0);
		if (error != 0)
			break;
		if (dirbuf.dotdot_namlen != 2 ||
		    dirbuf.dotdot_name[0] != '.' ||
		    dirbuf.dotdot_name[1] != '.') {
			error = ENOTDIR;
			break;
		}
		if (dirbuf.dotdot_ino == source->i_number) {
			error = EINVAL;
			break;
		}
		if (dirbuf.dotdot_ino == ROOTINO)
			break;
		iput(ip);
		ip = iget(ip->i_dev, ip->i_fs, dirbuf.dotdot_ino);
		if (ip == NULL) {
			error = u.u_error;
			break;
		}
	}

out:
	if (error == ENOTDIR)
		printf("checkpath: .. not a directory\n");
	if (ip != NULL)
		iput(ip);
	return (error);
}

nchinit()
{
}

nchinval(dev)
	register dev_t dev;
{
	register int i;
	register struct dir_hash_entry *hash_bucket;
	register struct dir_hash_entry *last_entry;

	set_directory_lock;

	for (i=0; i < DIRHASHSIZE; i++) {
		last_entry = (struct dir_hash_entry *)&dir_hash_table[i];
		hash_bucket = dir_hash_table[i];
		while (hash_bucket != NULL) {
			if (hash_bucket->dev == dev || (dev == -1)) {
				last_entry->next = hash_bucket->next;
				directory_release(hash_bucket);
				ADD_TO_ZONE(dir_hash_entry_zone, hash_bucket);
			} else 	last_entry = hash_bucket;
			hash_bucket = last_entry->next;
		}
	}

	clear_directory_lock;
}

cacheinvalall()
{
	nchinval(-1);
}



