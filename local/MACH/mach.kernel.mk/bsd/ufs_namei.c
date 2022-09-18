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
 * $Log:	ufs_namei.c,v $
 * Revision 2.12  90/07/03  16:33:40  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  17:46:50  mrt]
 * 
 * Revision 2.11  89/10/10  10:47:47  mwyoung
 * 	Allow RFS links to be either symbolic link nodes or regular
 * 	file nodes.
 * 	[89/05/12  16:01:53  mwyoung]
 * 
 * Revision 2.10  89/04/22  15:22:21  gm0w
 * 	Changed RFS code to return EINVAL during lookup for syscalls that
 * 	are not implemented under RFS.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.9  89/04/05  12:55:43  rvb
 * 	Make i386 do ovbcopy correctly.
 * 	[89/04/03            rvb]
 * 
 * Revision 2.8  89/03/09  19:33:16  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/26  11:29:26  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  89/02/09  04:35:27  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.5  89/01/23  22:09:14  af
 * 	Changes for I386: ovbcopy -> bcopy
 * 	[89/01/09            rvb]
 * 
 * Revision 2.4  88/08/25  18:12:21  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Yet more debugging.
 * 	[88/08/15  02:27:06  mwyoung]
 * 	
 * 	More debugging stuff.
 * 	[88/08/13  18:32:04  mwyoung]
 * 	
 * 	Toss in some code to watch namei() calls... not turned on yet.
 * 	[88/08/11  18:44:26  mwyoung]
 * 
 * Revision 2.3  88/07/15  15:38:27  mja
 * Fixed to include <sys/table.h> instead of <sys/syscall.h> for
 * UMODE_* definitions.
 * 
 * 21-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Installed bug fix from Jay Kistler for "not found" returns when
 *	the caller is not expecting to transfer into Vice.
 *	[ V5.1(XF23) ]
 *
 * 26-Aug-87  Jay Kistler (jjk) at Carnegie Mellon University
 *	VICE:  Reset the u_rmt_requested flag before the return in the
 *	block that Mike created for the ERANGE facility.  NOTE to future
 *	modifiers of this code:  if you add a new return statement
 *	ANYWHERE in namei(), it MUST be preceded by a resetting of the
 *	u_rmt_requested flag or subsequent Vice fs calls may panic.
 *
 * 05-Feb-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Modified namei() to upon request return ERANGE error for any
 *	pathname that traverses above the logical root with the side-
 *	effect of leaving the remainder in the U area pathname buffer
 *	so that the caller can make use of it (e.g. to return it back
 *	to the remote file server which wants to force such names to be
 *	handled remotely), also updated to interpret special ELOCAL
 *	return from rfs_namei() as a direction to continue the pathname
 *	interpretation locally.
 *	[ V5.1(F2) ]
 *
 * 26-Jan-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE:  Remove KEEPNAMEBUF handling for Vice as it turned out
 *	not to be necessary.
 *
 * 23-Dec-86  David L. Black (dlb) at Carnegie-Mellon University
 *	MULTIMAX: make namei understand Encore (UMAX) fast symbolic links.
 *
 *  2-Dec-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE:  Merged in ITC/Andrew hooks.
 *
 * 19-May-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS:  Changed to bump count variable on each namei() call
 *	and use new KEEPNAMEBUF flag to prevent name buffer from being
 *	released on return from rfs_namei();  added new nameifree()
 *	routine to return name buffer to free list.
 *	[V1(1)].
 *
 * 16-Feb-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Added definition of ovbcopy as bcopy for the RT.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 26-Aug-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_ICHK:  Added inode count consistency check macros.
 *	[V1(1)].
 *
 * 20-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS:  Added remote name hook into rfs_namei() if OKREMOTE
 *	flag is supplied in call; disabled restriction against changing
 *	above the root for now.
 *	CS_QUOTE:  Added interim quoting mechanism for remote and
 *	symbolic links.
 *	[V1(1)]
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)ufs_namei.c	7.1 (Berkeley) 6/5/86
 */

#include <mach_debug.h>
#include <vice.h>
#include <cputypes.h>

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
#include <sys/table.h>

#if	MACH_DEBUG
boolean_t	namei_print = FALSE;
boolean_t	namei_debug = FALSE;
int		namei_count = 0;
extern
void		namei_debug_name();
#endif	MACH_DEBUG

#if	defined(ibmrt)
#define ovbcopy(at,to,ln) bcopy(at,to,ln)
#endif	defined(ibmrt)

struct	buf *blkatoff();
struct	buf *freenamebuf;
int	dirchk = 0;

long	nextinodeid;		/* unique id generator */
struct	inode *rootdir;		/* pointer to inode of root directory */

/*
 * Structures associated with name cacheing.
 */
#define NCHHASH		32	/* size of hash table */

#if	((NCHHASH)&((NCHHASH)-1)) != 0
#define NHASH(h, i, d)	((unsigned)((h) + (i) + 13 * (int)(d)) % (NCHHASH))
#else
#define NHASH(h, i, d)	((unsigned)((h) + (i) + 13 * (int)(d)) & ((NCHHASH)-1))
#endif

union nchash {
	union	nchash *nch_head[2];
	struct	namecache *nch_chain[2];
} nchash[NCHHASH];
#define nch_forw	nch_chain[0]
#define nch_back	nch_chain[1]

struct	namecache *nchhead, **nchtail;	/* LRU chain pointers */
struct	nchstats nchstats;		/* cache effectiveness statistics */

/*
 * Convert a pathname into a pointer to a locked inode.
 * This is a very central and rather complicated routine.
 * If the file system is not maintained in a strict tree hierarchy,
 * this can result in a deadlock situation (see comments in code below).
 *
 * The flag argument is LOOKUP, CREATE, or DELETE depending on whether
 * the name is to be looked up, created, or deleted. When CREATE or
 * DELETE is specified, information usable in creating or deleteing a
 * directory entry is also calculated. If flag has LOCKPARENT or'ed
 * into it and the target of the pathname exists, namei returns both
 * the target and its parent directory locked. When creating and
 * LOCKPARENT is specified, the target may not be ".".  When deleting
 * and LOCKPARENT is specified, the target may be ".", but the caller
 * must check to insure it does an irele and iput instead of two iputs.
 *
 * The FOLLOW flag is set when symbolic links are to be followed
 * when they occur at the end of the name translation process.
 * Symbolic links are always followed for all other pathname
 * components other than the last.
 *
 * The segflg defines whether the name is to be copied from user
 * space or kernel space.
 *
 * Name caching works as follows:
 *
 * Names found by directory scans are retained in a cache
 * for future reference.  It is managed LRU, so frequently
 * used names will hang around.  Cache is indexed by hash value
 * obtained from (ino,dev,name) where ino & dev refer to the
 * directory containing name.
 *
 * For simplicity (and economy of storage), names longer than
 * a maximum length of NCHNAMLEN are not cached; they occur
 * infrequently in any case, and are almost never of interest.
 *
 * Upon reaching the last segment of a path, if the reference
 * is for DELETE, or NOCACHE is set (rewrite), and the
 * name is located in the cache, it will be dropped.
 *
 * Overall outline of namei:
 *
 *	copy in name
 *	get starting directory
 * dirloop:
 *	check accessibility of directory
 * dirloop2:
 *	copy next component of name to ndp->ni_dent
 *	handle degenerate case where name is null string
 *	look for name in cache, if found, then if at end of path
 *	  and deleting or creating, drop it, else to haveino
 *	search for name in directory, to found or notfound
 * notfound:
 *	if creating, return locked directory, leaving info on avail. slots
 *	else return error
 * found:
 *	if at end of path and deleting, return information to allow delete
 *	if at end of path and rewriting (CREATE and LOCKPARENT), lock target
 *	  inode and return info to allow rewrite
 *	if .. and on mounted filesys, look in mount table for parent
 *	if not at end, add name to cache; if at end and neither creating
 *	  nor deleting, add name to cache
 * haveino:
 *	if symbolic link, massage name in buffer and continue at dirloop
 *	if more components of name, do next level at dirloop
 *	return the answer as locked inode
 *
 * NOTE: (LOOKUP | LOCKPARENT) currently returns the parent inode,
 *	 but unlocked.
 */
struct inode *
namei(ndp)
	register struct nameidata *ndp;
{
	register char *cp;		/* pointer into pathname argument */
/* these variables refer to things which must be freed or unlocked */
	register struct inode *dp = 0;	/* the directory we are searching */
	register struct namecache *ncp;	/* cache slot for entry */
	register struct fs *fs;		/* file system that directory is in */
	register struct buf *bp = 0;	/* a buffer of directory entries */
	register struct direct *ep;	/* the current directory entry */
	int entryoffsetinblock;		/* offset of ep in bp's buffer */
	register struct buf *nbp;	/* buffer storing path name argument */
/* these variables hold information about the search for a slot */
	enum {NONE, COMPACT, FOUND} slotstatus;
	int slotoffset = -1;		/* offset of area with free space */
	int slotsize;			/* size of area at slotoffset */
	int slotfreespace;		/* amount of space free in slot */
	int slotneeded;			/* size of the entry we're seeking */
/* */
	int numdirpasses;		/* strategy for directory search */
	int endsearch;			/* offset to end directory search */
	int prevoff;			/* ndp->ni_offset of previous entry */
	int nlink = 0;			/* number of symbolic links taken */
	struct inode *pdp;		/* saved dp during symlink work */
	int error, i;
	int lockparent;
	int docache;			/* == 0 do not cache last component */
	int makeentry;			/* != 0 if name to be added to cache */
	unsigned hash;			/* value of name hash for entry */
	union nchash *nhp;		/* cache chain head for entry */
	int isdotdot;			/* != 0 if current name is ".." */
	int flag;			/* op ie, LOOKUP, CREATE, or DELETE */
	off_t enduseful;		/* pointer past last used dir slot */
	short quoted = 0;
	int  nofollow;
#define QUOTED	3

#if	MACH_RFS
	int  okremote;
	extern struct inode *rfs_rdir;
 
	i = URFS_CDIR;
	lockparent = ndp->ni_nameiop & LOCKPARENT;
	okremote = (ndp->ni_nameiop&OKREMOTE) != 0;
	docache = (ndp->ni_nameiop & NOCACHE) ^ NOCACHE;
	flag = ndp->ni_nameiop &~ (KEEPNAMEBUF|OKREMOTE|LOCKPARENT|NOCACHE|FOLLOW);
	u.u_rfsncnt++;
#else	MACH_RFS

	lockparent = ndp->ni_nameiop & LOCKPARENT;
	docache = (ndp->ni_nameiop & NOCACHE) ^ NOCACHE;
	flag = ndp->ni_nameiop &~ (LOCKPARENT|NOCACHE|FOLLOW);
#endif	MACH_RFS
	nofollow = (u.u_modes&UMODE_NOFOLLOW) != 0;
#if	VICE
	u.u_rmt_ncnt++;
#endif	VICE
	if (flag == DELETE || lockparent)
		docache = 0;
	/*
	 * Get a buffer for the name to be translated, and copy the
	 * name into the buffer.
	 */
	nbp = freenamebuf;
	if (nbp == NULL)
		nbp = geteblk(MAXPATHLEN);
	else
		freenamebuf = nbp->av_forw;
	if (ndp->ni_segflg == UIO_SYSSPACE)
		error = copystr(ndp->ni_dirp, nbp->b_un.b_addr, MAXPATHLEN,
		    (u_int *)0);
	else
		error = copyinstr(ndp->ni_dirp, nbp->b_un.b_addr, MAXPATHLEN,
		    (u_int *)0);
	if (error) {
		u.u_error = error;
		goto bad;
	}

#if	MACH_DEBUG
	if (namei_print)
		uprintf("namei: flags=0x%x, program=%s, name=%s\n",
				ndp->ni_nameiop,
				u.u_comm,
				nbp->b_un.b_addr);
	namei_count++;	/* Not worth locking */
#if	0
	if (namei_debug)
		namei_debug_name(nbp->b_un.b_addr);
#endif	0
#endif	MACH_DEBUG

#if	MACH_RFS
reroot:
#endif	MACH_RFS
	/*
	 * Get starting directory.
	 */
#if	VICE
startdir:
	if (u.u_rmt_path_buf != NULL)
	    panic("namei:  u.u_rmt_path_buf != NULL");
	u.u_rmt_dev = NODEV;
#endif	VICE
	cp = nbp->b_un.b_addr;
	if (*cp == '/') {
		while (*cp == '/') {
 			cp++;
			quoted++;
		}
		if ((dp = u.u_rdir) == NULL)
			dp = rootdir;
#if	MACH_RFS
		else
			i = URFS_RDIR;
#endif	MACH_RFS
	} else
#if	VICE
	{
		if (u.u_rmtWd.dev != NODEV)	/* Send request to Venus */
		{
		    u.u_rmt_dev = u.u_rmtWd.dev;
		    goto remote;
		}
#endif	VICE
		dp = u.u_cdir;
#if	VICE
	}
	if (dp == NULL)			/* DEBUG */
		panic("namei:  dp == NULL");
#endif	VICE

	fs = dp->i_fs;
	ILOCK(dp);
	iincr_chk(dp);
	ndp->ni_pdir = (struct inode *)0xc0000000;		/* illegal */
	ndp->ni_endoff = 0;
#if	MACH_RFS
	/*
	 *  Check if base directory is remote.  If this lookup/system call is
	 *  not prepared to handle a remote name, we're out of luck (this will
	 *  be detected below when the remote file inode is found not to be a
	 *  directory).
	 */
	if ((u.u_rfs&i) && okremote && !nofollow && u.u_rfscode != 0)
		goto rfsdir;
#endif	MACH_RFS
 
	/*
	 *  Never follow trailing symbolic links if that mode
	 *  has been set for the process.
	 */
	if (nofollow)
		ndp->ni_nameiop &= ~FOLLOW;

	/*
	 * We come to dirloop to search a new directory.
	 * The directory must be locked so that it can be
	 * iput, and fs must be already set to dp->i_fs.
	 */
dirloop:
	/*
	 * Check accessiblity of directory.
	 */
	if ((dp->i_mode&IFMT) != IFDIR) {
#if	MACH_RFS
		if (!okremote && !nofollow &&
		    (quoted < QUOTED) && (u.u_rfscode != 0) && isrfslnk(dp))
			u.u_error = EINVAL;
		else
#endif	MACH_RFS
		u.u_error = ENOTDIR;
		goto bad;
	}
	if (access(dp, IEXEC))
		goto bad;

dirloop2:
	if (quoted < QUOTED)
		quoted = 0;

	/*
	 * Copy next component of name to ndp->ni_dent.
	 */
	hash = 0;
	for (i = 0; *cp != 0 && *cp != '/'; cp++) {
		if (i >= MAXNAMLEN) {
			u.u_error = ENAMETOOLONG;
			goto bad;
		}
		if (*cp & 0200)
			if ((*cp&0377) == ('/'|0200) || flag != DELETE) {
				u.u_error = EINVAL;
				goto bad;
			}
		ndp->ni_dent.d_name[i++] = *cp;
		hash += (unsigned char)*cp * i;
	}
	ndp->ni_dent.d_namlen = i;
	ndp->ni_dent.d_name[i] = '\0';
	isdotdot = (i == 2 &&
		ndp->ni_dent.d_name[0] == '.' && ndp->ni_dent.d_name[1] == '.');
	makeentry = 1;
	if (*cp == '\0' && docache == 0)
		makeentry = 0;

	if (isdotdot)
		makeentry = 0;

	/*
	 * Check for degenerate name (e.g. / or "")
	 * which is a way of talking about a directory,
	 * e.g. like "/." or ".".
	 */
	if (ndp->ni_dent.d_name[0] == '\0') {
		if (flag != LOOKUP || lockparent) {
			u.u_error = EISDIR;
			goto bad;
		}
		nbp->av_forw = freenamebuf;
		freenamebuf = nbp;
#if	VICE
		u.u_rmt_requested = 0;
#endif	VICE
		return (dp);
	}

	/*
	 * We now have a segment name to search for, and a directory to search.
	 *
	 * Before tediously performing a linear scan of the directory,
	 * check the name cache to see if the directory/name pair
	 * we are looking for is known already.  We don't do this
	 * if the segment name is long, simply so the cache can avoid
	 * holding long names (which would either waste space, or
	 * add greatly to the complexity).
	 */
	if (ndp->ni_dent.d_namlen > NCHNAMLEN) {
		nchstats.ncs_long++;
		makeentry = 0;
	} else {
		nhp = &nchash[NHASH(hash, dp->i_number, dp->i_dev)];
		for (ncp = nhp->nch_forw; ncp != (struct namecache *)nhp;
		    ncp = ncp->nc_forw) {
			if (ncp->nc_ino == dp->i_number &&
			    ncp->nc_dev == dp->i_dev &&
			    ncp->nc_nlen == ndp->ni_dent.d_namlen &&
			    !bcmp(ncp->nc_name, ndp->ni_dent.d_name,
				(unsigned)ncp->nc_nlen))
				break;
		}
		if (ncp == (struct namecache *)nhp) {
			nchstats.ncs_miss++;
			ncp = NULL;
		} else {
			if (ncp->nc_id != ncp->nc_ip->i_id)
				nchstats.ncs_falsehits++;
			else if (!makeentry)
				nchstats.ncs_badhits++;
			else {
				/*
				 * move this slot to end of LRU
				 * chain, if not already there
				 */
				if (ncp->nc_nxt) {
					/* remove from LRU chain */
					*ncp->nc_prev = ncp->nc_nxt;
					ncp->nc_nxt->nc_prev = ncp->nc_prev;

					/* and replace at end of it */
					ncp->nc_nxt = NULL;
					ncp->nc_prev = nchtail;
					*nchtail = ncp;
					nchtail = &ncp->nc_nxt;
				}

				/*
				 * Get the next inode in the path.
				 * See comment above other `IUNLOCK' code for
				 * an explaination of the locking protocol.
				 */
				pdp = dp;
#if	MACH_RFS
				if (!isdotdot || dp != u.u_rdir || rfs_rdir == u.u_rdir)
#else	MACH_RFS
				if (!isdotdot || dp != u.u_rdir)
#endif	MACH_RFS
					dp = ncp->nc_ip;
				if (dp == NULL)
					panic("namei: null cache ino");
				if (pdp == dp)
					dp->i_count++;
				else if (isdotdot) {
					IUNLOCK(pdp);
					igrab(dp);
				} else {
					igrab(dp);
					IUNLOCK(pdp);
				}

				/*
				 * Verify that the inode that we got
				 * did not change while we were waiting
				 * for it to be locked.
				 */
				if (ncp->nc_id != ncp->nc_ip->i_id) {
					iput(dp);
					ILOCK(pdp);
					dp = pdp;
					nchstats.ncs_falsehits++;
				} else {
					ndp->ni_dent.d_ino = dp->i_number;
					/* ni_dent.d_reclen is garbage ... */
					nchstats.ncs_goodhits++;
					goto haveino;
				}
			}

			/*
			 * Last component and we are renaming or deleting,
			 * the cache entry is invalid, or otherwise don't
			 * want cache entry to exist.
			 */
			/* remove from LRU chain */
			*ncp->nc_prev = ncp->nc_nxt;
			if (ncp->nc_nxt)
				ncp->nc_nxt->nc_prev = ncp->nc_prev;
			else
				nchtail = ncp->nc_prev;
			remque(ncp);		/* remove from hash chain */
			/* insert at head of LRU list (first to grab) */
			ncp->nc_nxt = nchhead;
			ncp->nc_prev = &nchhead;
			nchhead->nc_prev = &ncp->nc_nxt;
			nchhead = ncp;
			/* and make a dummy hash chain */
			ncp->nc_forw = ncp;
			ncp->nc_back = ncp;
			ncp = NULL;
		}
	}

	/*
	 * Suppress search for slots unless creating
	 * file and at end of pathname, in which case
	 * we watch for a place to put the new file in
	 * case it doesn't already exist.
	 */
	slotstatus = FOUND;
	if (flag == CREATE && *cp == 0) {
		slotstatus = NONE;
		slotfreespace = 0;
		slotneeded = DIRSIZ(&ndp->ni_dent);
	}
	/*
	 * If this is the same directory that this process
	 * previously searched, pick up where we last left off.
	 * We cache only lookups as these are the most common
	 * and have the greatest payoff. Caching CREATE has little
	 * benefit as it usually must search the entire directory
	 * to determine that the entry does not exist. Caching the
	 * location of the last DELETE has not reduced profiling time
	 * and hence has been removed in the interest of simplicity.
	 */
	if (flag != LOOKUP || dp->i_number != u.u_ncache.nc_inumber ||
	    dp->i_dev != u.u_ncache.nc_dev) {
		ndp->ni_offset = 0;
		numdirpasses = 1;
	} else {
		if (u.u_ncache.nc_prevoffset > dp->i_size)
			u.u_ncache.nc_prevoffset = 0;
		ndp->ni_offset = u.u_ncache.nc_prevoffset;
		entryoffsetinblock = blkoff(fs, ndp->ni_offset);
		if (entryoffsetinblock != 0) {
			bp = blkatoff(dp, ndp->ni_offset, (char **)0);
			if (bp == 0)
				goto bad;
		}
		numdirpasses = 2;
		nchstats.ncs_2passes++;
	}
	endsearch = roundup(dp->i_size, DIRBLKSIZ);
	enduseful = 0;

searchloop:
	while (ndp->ni_offset < endsearch) {
		/*
		 * If offset is on a block boundary,
		 * read the next directory block.
		 * Release previous if it exists.
		 */
		if (blkoff(fs, ndp->ni_offset) == 0) {
			if (bp != NULL)
				brelse(bp);
			bp = blkatoff(dp, ndp->ni_offset, (char **)0);
			if (bp == 0)
				goto bad;
			entryoffsetinblock = 0;
		}
		/*
		 * If still looking for a slot, and at a DIRBLKSIZE
		 * boundary, have to start looking for free space again.
		 */
		if (slotstatus == NONE &&
		    (entryoffsetinblock&(DIRBLKSIZ-1)) == 0) {
			slotoffset = -1;
			slotfreespace = 0;
		}
		/*
		 * Get pointer to next entry.
		 * Full validation checks are slow, so we only check
		 * enough to insure forward progress through the
		 * directory. Complete checks can be run by patching
		 * "dirchk" to be true.
		 */
		ep = (struct direct *)(bp->b_un.b_addr + entryoffsetinblock);
		if (ep->d_reclen == 0 ||
		    dirchk && dirbadentry(ep, entryoffsetinblock)) {
			dirbad(dp, ndp->ni_offset, "mangled entry");
			i = DIRBLKSIZ - (entryoffsetinblock & (DIRBLKSIZ - 1));
			ndp->ni_offset += i;
			entryoffsetinblock += i;
			continue;
		}

		/*
		 * If an appropriate sized slot has not yet been found,
		 * check to see if one is available. Also accumulate space
		 * in the current block so that we can determine if
		 * compaction is viable.
		 */
		if (slotstatus != FOUND) {
			int size = ep->d_reclen;

			if (ep->d_ino != 0)
				size -= DIRSIZ(ep);
			if (size > 0) {
				if (size >= slotneeded) {
					slotstatus = FOUND;
					slotoffset = ndp->ni_offset;
					slotsize = ep->d_reclen;
				} else if (slotstatus == NONE) {
					slotfreespace += size;
					if (slotoffset == -1)
						slotoffset = ndp->ni_offset;
					if (slotfreespace >= slotneeded) {
						slotstatus = COMPACT;
						slotsize = ndp->ni_offset +
						      ep->d_reclen - slotoffset;
					}
				}
			}
		}

		/*
		 * Check for a name match.
		 */
		if (ep->d_ino) {
			if (ep->d_namlen == ndp->ni_dent.d_namlen &&
			    !bcmp(ndp->ni_dent.d_name, ep->d_name,
				(unsigned)ep->d_namlen))
				goto found;
		}
		prevoff = ndp->ni_offset;
		ndp->ni_offset += ep->d_reclen;
		entryoffsetinblock += ep->d_reclen;
		if (ep->d_ino)
			enduseful = ndp->ni_offset;
	}
/* notfound: */
	/*
	 * If we started in the middle of the directory and failed
	 * to find our target, we must check the beginning as well.
	 */
	if (numdirpasses == 2) {
		numdirpasses--;
		ndp->ni_offset = 0;
		endsearch = u.u_ncache.nc_prevoffset;
		goto searchloop;
	}
	/*
	 * If creating, and at end of pathname and current
	 * directory has not been removed, then can consider
	 * allowing file to be created.
	 */
	if (flag == CREATE && *cp == 0 && dp->i_nlink != 0) {
		/*
		 * Access for write is interpreted as allowing
		 * creation of files in the directory.
		 */
		if (access(dp, IWRITE))
			goto bad;
		/*
		 * Return an indication of where the new directory
		 * entry should be put.  If we didn't find a slot,
		 * then set ndp->ni_count to 0 indicating that the new
		 * slot belongs at the end of the directory. If we found
		 * a slot, then the new entry can be put in the range
		 * [ndp->ni_offset .. ndp->ni_offset + ndp->ni_count)
		 */
		if (slotstatus == NONE) {
			ndp->ni_offset = roundup(dp->i_size, DIRBLKSIZ);
			ndp->ni_count = 0;
			enduseful = ndp->ni_offset;
		} else {
			ndp->ni_offset = slotoffset;
			ndp->ni_count = slotsize;
			if (enduseful < slotoffset + slotsize)
				enduseful = slotoffset + slotsize;
		}
		ndp->ni_endoff = roundup(enduseful, DIRBLKSIZ);
		dp->i_flag |= IUPD|ICHG;
		if (bp)
			brelse(bp);
		nbp->av_forw = freenamebuf;
		freenamebuf = nbp;
		/*
		 * We return with the directory locked, so that
		 * the parameters we set up above will still be
		 * valid if we actually decide to do a direnter().
		 * We return NULL to indicate that the entry doesn't
		 * currently exist, leaving a pointer to the (locked)
		 * directory inode in ndp->ni_pdir.
		 */
		ndp->ni_pdir = dp;
#if	VICE
		u.u_rmt_requested = 0;
#endif	VICE
		return (NULL);
	}
	u.u_error = ENOENT;
	goto bad;
found:
	if (numdirpasses == 2)
		nchstats.ncs_pass2++;
	/*
	 * Check that directory length properly reflects presence
	 * of this entry.
	 */
	if (entryoffsetinblock + DIRSIZ(ep) > dp->i_size) {
		dirbad(dp, ndp->ni_offset, "i_size too small");
		dp->i_size = entryoffsetinblock + DIRSIZ(ep);
		dp->i_flag |= IUPD|ICHG;
	}

	/*
	 * Found component in pathname.
	 * If the final component of path name, save information
	 * in the cache as to where the entry was found.
	 */
	if (*cp == '\0' && flag == LOOKUP) {
		u.u_ncache.nc_prevoffset = ndp->ni_offset &~ (DIRBLKSIZ - 1);
		u.u_ncache.nc_inumber = dp->i_number;
		u.u_ncache.nc_dev = dp->i_dev;
	}
	/*
	 * Save directory entry's inode number and reclen in ndp->ni_dent,
	 * and release directory buffer.
	 */
	ndp->ni_dent.d_ino = ep->d_ino;
	ndp->ni_dent.d_reclen = ep->d_reclen;
	brelse(bp);
	bp = NULL;

	/*
	 * If deleting, and at end of pathname, return
	 * parameters which can be used to remove file.
	 * If the lockparent flag isn't set, we return only
	 * the directory (in ndp->ni_pdir), otherwise we go
	 * on and lock the inode, being careful with ".".
	 */
	if (flag == DELETE && *cp == 0) {
		/*
		 * Write access to directory required to delete files.
		 */
		if (access(dp, IWRITE))
			goto bad;
		ndp->ni_pdir = dp;		/* for dirremove() */
		/*
		 * Return pointer to current entry in ndp->ni_offset,
		 * and distance past previous entry (if there
		 * is a previous entry in this block) in ndp->ni_count.
		 * Save directory inode pointer in ndp->ni_pdir for dirremove().
		 */
		if ((ndp->ni_offset&(DIRBLKSIZ-1)) == 0)
			ndp->ni_count = 0;
		else
			ndp->ni_count = ndp->ni_offset - prevoff;
		if (lockparent) {
			if (dp->i_number == ndp->ni_dent.d_ino) {
				iincr_chk(dp);
			} else {
				dp = iget(dp->i_dev, fs, ndp->ni_dent.d_ino);
				if (dp == NULL) {
					iput(ndp->ni_pdir);
					goto bad;
				}
				/*
				 * If directory is "sticky", then user must own
				 * the directory, or the file in it, else he
				 * may not delete it (unless he's root). This
				 * implements append-only directories.
				 */
				if ((ndp->ni_pdir->i_mode & ISVTX) &&
				    u.u_uid != 0 &&
				    u.u_uid != ndp->ni_pdir->i_uid &&
				    dp->i_uid != u.u_uid) {
					iput(ndp->ni_pdir);
					u.u_error = EPERM;
					goto bad;
				}
			}
		}
		nbp->av_forw = freenamebuf;
		freenamebuf = nbp;
#if	VICE
		u.u_rmt_requested = 0;
#endif	VICE
		return (dp);
	}

	/*
	 * Special handling for ".." allowing chdir out of mounted
	 * file system: indirect .. in root inode to reevaluate
	 * in directory file system was mounted on.
	 */
	if (isdotdot) {
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
				if (bp)
					panic("namei:EROOT");
				iput(dp);
				if (ndp->ni_nameiop&KEEPNAMEBUF) {
					ndp->ni_dirp = cp;
					ndp->ni_nameiop &= ~KEEPNAMEBUF;
					*ni_nbpp(ndp) = nbp;
				} else {
					nbp->av_forw = freenamebuf;
					freenamebuf = nbp;
				}
				u.u_error = ERANGE;
#if	VICE
				u.u_rmt_requested = 0;
#endif	VICE
				return(NULL);
			}
			if (rfs_rdir != u.u_rdir)
#endif	MACH_RFS
			{
				ndp->ni_dent.d_ino = dp->i_number;
				makeentry = 0;
			}
		} else if (ndp->ni_dent.d_ino == ROOTINO &&
		   dp->i_number == ROOTINO) {
			for (i = 1; i < NMOUNT; i++)
			if (mount[i].m_bufp != NULL &&
			   mount[i].m_dev == dp->i_dev) {
				iput(dp);
				dp = mount[i].m_inodp;
				ILOCK(dp);
				iincr_chk(dp);
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
	if ((flag == CREATE && lockparent) && *cp == 0) {
		if (access(dp, IWRITE))
			goto bad;
		ndp->ni_pdir = dp;		/* for dirrewrite() */
		/*
		 * Careful about locking second inode. 
		 * This can only occur if the target is ".". 
		 */
		if (dp->i_number == ndp->ni_dent.d_ino) {
			u.u_error = EISDIR;		/* XXX */
			goto bad;
		}
		dp = iget(dp->i_dev, fs, ndp->ni_dent.d_ino);
		if (dp == NULL) {
			iput(ndp->ni_pdir);
			goto bad;
		}
		nbp->av_forw = freenamebuf;
		freenamebuf = nbp;
#if	VICE
		u.u_rmt_requested = 0;
#endif	VICE
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
	if (isdotdot) {
		IUNLOCK(pdp);	/* race to get the inode */
		dp = iget(dp->i_dev, fs, ndp->ni_dent.d_ino);
		if (dp == NULL)
			goto bad2;
	} else if (dp->i_number == ndp->ni_dent.d_ino) {
		iincr_chk(dp);	/* we want ourself, ie "." */
	} else {
		dp = iget(dp->i_dev, fs, ndp->ni_dent.d_ino);
		IUNLOCK(pdp);
		if (dp == NULL)
			goto bad2;
	}

	/*
	 * Insert name into cache if appropriate.
	 */
#if	MACH_RFS
	if (makeentry && !(okremote && !nofollow && quoted < QUOTED &&
			   u.u_rfscode != 0 && isrfslnk(dp))) {
#else	MACH_RFS
	if (makeentry) {
#endif	MACH_RFS
		if (ncp != NULL)
			panic("namei: duplicating cache");
		/*
		 * Free the cache slot at head of lru chain.
		 */
		if (ncp = nchhead) {
			/* remove from lru chain */
			*ncp->nc_prev = ncp->nc_nxt;
			if (ncp->nc_nxt)
				ncp->nc_nxt->nc_prev = ncp->nc_prev;
			else
				nchtail = ncp->nc_prev;
			remque(ncp);		/* remove from old hash chain */
			/* grab the inode we just found */
			ncp->nc_ip = dp;
			/* fill in cache info */
			ncp->nc_ino = pdp->i_number;	/* parents inum */
			ncp->nc_dev = pdp->i_dev;	/* & device */
			ncp->nc_idev = dp->i_dev;	/* our device */
			ncp->nc_id = dp->i_id;		/* identifier */
			ncp->nc_nlen = ndp->ni_dent.d_namlen;
			bcopy(ndp->ni_dent.d_name, ncp->nc_name,
			    (unsigned)ncp->nc_nlen);
			/* link at end of lru chain */
			ncp->nc_nxt = NULL;
			ncp->nc_prev = nchtail;
			*nchtail = ncp;
			nchtail = &ncp->nc_nxt;
			/* and insert on hash chain */
			insque(ncp, nhp);
		}
	}

haveino:
#if	MACH_RFS
	/* 
	 *  Check for remote name.
	 */
	if (okremote && !nofollow && (quoted < QUOTED) && (u.u_rfscode != 0) && isrfslnk(dp)) {
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
		if (*cp == 0 && cp != nbp->b_un.b_addr)
			*--cp = '/';
		ndp->ni_dirp = cp;
		*ni_nbpp(ndp) = nbp;
		dp = rfs_namei(dp, ndp);
		if (u.u_error == ELOCAL)
		{
			u.u_error = 0;
			nbp->b_un.b_addr[0] = '/';
			nbp->b_un.b_addr[1] = '.';
			nbp->b_un.b_addr[2] = '.';
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
		if (ndp->ni_nameiop&KEEPNAMEBUF)
		{
			ndp->ni_nameiop &= ~KEEPNAMEBUF;
		}
		else
		{
			nbp->av_forw = freenamebuf;
			freenamebuf = nbp;
			*ni_nbpp(ndp) = NULL;		/* safety */
		}
#if	VICE
		u.u_rmt_requested = 0;
#endif	VICE
		return(dp);
	}
#endif	MACH_RFS
	fs = dp->i_fs;

	/*
	 * Check for symbolic link
	 */
	if ((dp->i_mode & IFMT) == IFLNK && quoted < QUOTED &&
			((ndp->ni_nameiop & FOLLOW) || *cp == '/')) {
		u_int pathlen = strlen(cp) + 1;

		if (dp->i_size + pathlen >= MAXPATHLEN - 1) {
			u.u_error = ENAMETOOLONG;
			goto bad2;
		}
		if (++nlink > MAXSYMLINKS) {
			u.u_error = ELOOP;
			goto bad2;
		}
		ovbcopy(cp, nbp->b_un.b_addr + dp->i_size, pathlen);
#if	MACH_FASTLINK
		/*
		 *	Encore UMAX fast symbolic link support
		 */
		if ((dp->i_icflags & IC_FASTLINK) != 0 && use_fastlinks)
			copystr(dp->i_symlink, nbp->b_un.b_addr,
				(int)dp->i_size, (u_int *)0);
		else
#endif	MACH_FASTLINK
		u.u_error =
		    rdwri(UIO_READ, dp, nbp->b_un.b_addr, (int)dp->i_size,
			(off_t)0, 1, (int *)0);
		if (u.u_error)
			goto bad2;
		cp = nbp->b_un.b_addr;
		iput(dp);
		if (*cp == '/') {
			irele(pdp);
			while (*cp == '/') {
 				cp++;
				quoted++;
			}
			if ((dp = u.u_rdir) == NULL)
				dp = rootdir;
			ILOCK(dp);
			iincr_chk(dp);
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
		while (*cp == '/') {
 			cp++;
			quoted++;
		}
		irele(pdp);
		goto dirloop;
	}
	nbp->av_forw = freenamebuf;
	freenamebuf = nbp;
	if (lockparent)
		ndp->ni_pdir = pdp;
	else
		irele(pdp);
#if	VICE
	u.u_rmt_requested = 0;
#endif	VICE
	return (dp);

#if	VICE
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
#endif	VICE
bad2:
	irele(pdp);

#if	VICE
remote:
#endif	VICE
bad:
	if (bp)
		brelse(bp);
	if (dp)
		iput(dp);
#if	VICE
	if (nbp == NULL)			/* DEBUG */
		panic("namei:  nbp == NULL!!!");
	if (u.u_rmt_dev != NODEV && !u.u_error)
	    if (!u.u_rmt_requested)
	    {
		u.u_error = EINVAL;
	    }
	    else
	    {
		extern struct inode	*rmt_namei();

		if (*cp != '/' && cp > nbp->b_un.b_addr)
			*--cp = '/';		/* Hack so that paths relative
						   to remote file system root
						   always begin with '/' */
		ndp->ni_dirp = cp;
		dp = rmt_namei(ndp, nbp);
		if (!u.u_error)			/* New pathname returned */
			if (++nlink > MAXSYMLINKS)
			{
				u.u_error = ELOOP;
				goto bad;
			}
			else
				goto startdir;	/* Retry */
		else
		{
			nbp->av_forw = freenamebuf;
			freenamebuf = nbp;
			u.u_rmt_requested = 0;
			return(NULL);
		}
	    }
#endif	VICE

	nbp->av_forw = freenamebuf;
	freenamebuf = nbp;
#if	VICE
	u.u_rmt_requested = 0;
#endif	VICE
	return (NULL);
}

#if	MACH_RFS
nameifree(nbp)
	struct buf *nbp;
{
	nbp->av_forw = freenamebuf;
	freenamebuf = nbp;
}
#endif	MACH_RFS

dirbad(ip, offset, how)
	struct inode *ip;
	off_t offset;
	char *how;
{

	printf("%s: bad dir ino %d at offset %d: %s\n",
	    ip->i_fs->fs_fsmnt, ip->i_number, offset, how);
}

/*
 * Do consistency checking on a directory entry:
 *	record length must be multiple of 4
 *	entry must fit in rest of its DIRBLKSIZ block
 *	record must be large enough to contain entry
 *	name is not longer than MAXNAMLEN
 *	name must be as long as advertised, and null terminated
 */
dirbadentry(ep, entryoffsetinblock)
	register struct direct *ep;
	int entryoffsetinblock;
{
	register int i;

	if ((ep->d_reclen & 0x3) != 0 ||
	    ep->d_reclen > DIRBLKSIZ - (entryoffsetinblock & (DIRBLKSIZ - 1)) ||
	    ep->d_reclen < DIRSIZ(ep) || ep->d_namlen > MAXNAMLEN)
		return (1);
	for (i = 0; i < ep->d_namlen; i++)
		if (ep->d_name[i] == '\0')
			return (1);
	return (ep->d_name[i]);
}

/*
 * Write a directory entry after a call to namei, using the parameters
 * which it left in the u. area.  The argument ip is the inode which
 * the new directory entry will refer to.  The u. area field ndp->ni_pdir is
 * a pointer to the directory to be written, which was left locked by
 * namei.  Remaining parameters (ndp->ni_offset, ndp->ni_count) indicate
 * how the space for the new entry is to be gotten.
 */
direnter(ip, ndp)
	struct inode *ip;
	register struct nameidata *ndp;
{
	register struct direct *ep, *nep;
	register struct inode *dp = ndp->ni_pdir;
	struct buf *bp;
	int loc, spacefree, error = 0;
	u_int dsize;
	int newentrysize;
	char *dirbuf;

	ndp->ni_dent.d_ino = ip->i_number;
	newentrysize = DIRSIZ(&ndp->ni_dent);
	if (ndp->ni_count == 0) {
		/*
		 * If ndp->ni_count is 0, then namei could find no space in the
		 * directory. In this case ndp->ni_offset will be on a directory
		 * block boundary and we will write the new entry into a fresh
		 * block.
		 */
		if (ndp->ni_offset&(DIRBLKSIZ-1))
			panic("wdir: newblk");
		ndp->ni_dent.d_reclen = DIRBLKSIZ;
		error = rdwri(UIO_WRITE, dp, (caddr_t)&ndp->ni_dent,
		    newentrysize, ndp->ni_offset, 1, (int *)0);
		if (DIRBLKSIZ > dp->i_fs->fs_fsize)
			panic("wdir: blksize"); /* XXX - should grow w/bmap() */
		else
			dp->i_size = roundup(dp->i_size, DIRBLKSIZ);
		iput(dp);
		return (error);
	}

	/*
	 * If ndp->ni_count is non-zero, then namei found space for the new
	 * entry in the range ndp->ni_offset to ndp->ni_offset + ndp->ni_count.
	 * in the directory.  To use this space, we may have to compact
	 * the entries located there, by copying them together towards
	 * the beginning of the block, leaving the free space in
	 * one usable chunk at the end.
	 */

	/*
	 * Increase size of directory if entry eats into new space.
	 * This should never push the size past a new multiple of
	 * DIRBLKSIZE.
	 *
	 * N.B. - THIS IS AN ARTIFACT OF 4.2 AND SHOULD NEVER HAPPEN.
	 */
	if (ndp->ni_offset + ndp->ni_count > dp->i_size)
		dp->i_size = ndp->ni_offset + ndp->ni_count;
	/*
	 * Get the block containing the space for the new directory
	 * entry.  Should return error by result instead of u.u_error.
	 */
	bp = blkatoff(dp, ndp->ni_offset, (char **)&dirbuf);
	if (bp == 0) {
		iput(dp);
		return (u.u_error);
	}
	/*
	 * Find space for the new entry.  In the simple case, the
	 * entry at offset base will have the space.  If it does
	 * not, then namei arranged that compacting the region
	 * ndp->ni_offset to ndp->ni_offset+ndp->ni_count would yield the space.
	 */
	ep = (struct direct *)dirbuf;
	dsize = DIRSIZ(ep);
	spacefree = ep->d_reclen - dsize;
	for (loc = ep->d_reclen; loc < ndp->ni_count; ) {
		nep = (struct direct *)(dirbuf + loc);
		if (ep->d_ino) {
			/* trim the existing slot */
			ep->d_reclen = dsize;
			ep = (struct direct *)((char *)ep + dsize);
		} else {
			/* overwrite; nothing there; header is ours */
			spacefree += dsize;	
		}
		dsize = DIRSIZ(nep);
		spacefree += nep->d_reclen - dsize;
		loc += nep->d_reclen;
		bcopy((caddr_t)nep, (caddr_t)ep, dsize);
	}
	/*
	 * Update the pointer fields in the previous entry (if any),
	 * copy in the new entry, and write out the block.
	 */
	if (ep->d_ino == 0) {
		if (spacefree + dsize < newentrysize)
			panic("wdir: compact1");
		ndp->ni_dent.d_reclen = spacefree + dsize;
	} else {
		if (spacefree < newentrysize)
			panic("wdir: compact2");
		ndp->ni_dent.d_reclen = spacefree;
		ep->d_reclen = dsize;
		ep = (struct direct *)((char *)ep + dsize);
	}
	bcopy((caddr_t)&ndp->ni_dent, (caddr_t)ep, (u_int)newentrysize);
	bwrite(bp);
	dp->i_flag |= IUPD|ICHG;
	if (ndp->ni_endoff && ndp->ni_endoff < dp->i_size)
		itrunc(dp, (u_long)ndp->ni_endoff);
	iput(dp);
	return (error);
}

/*
 * Remove a directory entry after a call to namei, using the
 * parameters which it left in the u. area.  The u. entry
 * ni_offset contains the offset into the directory of the
 * entry to be eliminated.  The ni_count field contains the
 * size of the previous record in the directory.  If this
 * is 0, the first entry is being deleted, so we need only
 * zero the inode number to mark the entry as free.  If the
 * entry isn't the first in the directory, we must reclaim
 * the space of the now empty record by adding the record size
 * to the size of the previous entry.
 */
dirremove(ndp)
	register struct nameidata *ndp;
{
	register struct inode *dp = ndp->ni_pdir;
	register struct buf *bp;
	struct direct *ep;

	if (ndp->ni_count == 0) {
		/*
		 * First entry in block: set d_ino to zero.
		 */
		ndp->ni_dent.d_ino = 0;
		(void) rdwri(UIO_WRITE, dp, (caddr_t)&ndp->ni_dent,
		    (int)DIRSIZ(&ndp->ni_dent), ndp->ni_offset, 1, (int *)0);
	} else {
		/*
		 * Collapse new free space into previous entry.
		 */
		bp = blkatoff(dp, ndp->ni_offset - ndp->ni_count, (char **)&ep);
		if (bp == 0)
			return (0);
		ep->d_reclen += ndp->ni_dent.d_reclen;
		bwrite(bp);
		dp->i_flag |= IUPD|ICHG;
	}
	return (1);
}

/*
 * Rewrite an existing directory entry to point at the inode
 * supplied.  The parameters describing the directory entry are
 * set up by a call to namei.
 */
dirrewrite(dp, ip, ndp)
	struct inode *dp, *ip;
	struct nameidata *ndp;
{

	ndp->ni_dent.d_ino = ip->i_number;
	u.u_error = rdwri(UIO_WRITE, dp, (caddr_t)&ndp->ni_dent,
		(int)DIRSIZ(&ndp->ni_dent), ndp->ni_offset, 1, (int *)0);
	iput(dp);
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

/*
 * Name cache initialization, from main() when we are booting
 */
nchinit()
{
	register union nchash *nchp;
	register struct namecache *ncp;

	nchhead = 0;
	nchtail = &nchhead;
	for (ncp = namecache; ncp < &namecache[nchsize]; ncp++) {
		ncp->nc_forw = ncp;			/* hash chain */
		ncp->nc_back = ncp;
		ncp->nc_nxt = NULL;			/* lru chain */
		*nchtail = ncp;
		ncp->nc_prev = nchtail;
		nchtail = &ncp->nc_nxt;
		/* all else is zero already */
	}
	for (nchp = nchash; nchp < &nchash[NCHHASH]; nchp++) {
		nchp->nch_head[0] = nchp;
		nchp->nch_head[1] = nchp;
	}
}

/*
 * Cache flush, called when filesys is umounted to
 * remove entries that would now be invalid
 *
 * The line "nxtcp = nchhead" near the end is to avoid potential problems
 * if the cache lru chain is modified while we are dumping the
 * inode.  This makes the algorithm O(n^2), but do you think I care?
 */
nchinval(dev)
	register dev_t dev;
{
	register struct namecache *ncp, *nxtcp;

	for (ncp = nchhead; ncp; ncp = nxtcp) {
		nxtcp = ncp->nc_nxt;
		if (ncp->nc_ip == NULL ||
		    (ncp->nc_idev != dev && ncp->nc_dev != dev))
			continue;
		/* free the resources we had */
		ncp->nc_idev = NODEV;
		ncp->nc_dev = NODEV;
		ncp->nc_id = NULL;
		ncp->nc_ino = 0;
		ncp->nc_ip = NULL;
		remque(ncp);		/* remove entry from its hash chain */
		ncp->nc_forw = ncp;	/* and make a dummy one */
		ncp->nc_back = ncp;
		/* delete this entry from LRU chain */
		*ncp->nc_prev = nxtcp;
		if (nxtcp)
			nxtcp->nc_prev = ncp->nc_prev;
		else
			nchtail = ncp->nc_prev;
		/* cause rescan of list, it may have altered */
		nxtcp = nchhead;
		/* put the now-free entry at head of LRU */
		ncp->nc_nxt = nxtcp;
		ncp->nc_prev = &nchhead;
		nxtcp->nc_prev = &ncp->nc_nxt;
		nchhead = ncp;
	}
}

/*
 * Name cache invalidation of all entries.
 */
cacheinvalall()
{
	register struct namecache *ncp;

	for (ncp = namecache; ncp < &namecache[nchsize]; ncp++)
		ncp->nc_id = 0;
}

#if	MACH_DEBUG
#if	0
char		*namei_debug_buffer = 0;
char		*namei_debug_buffer_next;
char		*namei_debug_buffer_end;
lock_data_t	namei_debug_buffer_lock;
#include <vm/vm_kern.h>

#define NAMEI_DEBUG_BUFFER_SIZE		(100*MAXPATHLEN)
void	namei_debug_name(path)
	register
	char		*path;
{
	lock_write(&namei_debug_buffer_lock);
	while (namei_debug_buffer == 0) {
		vm_offset_t	new_buffer;

		if (vm_allocate(kernel_map, &new_buffer, NAMEI_DEBUG_BUFFER_SIZE, TRUE) != KERN_SUCCESS) {
			printf("namei: unable to allocate debugging buffer\n");
			namei_debug = FALSE;
			return;
		}
		if (namei_debug_buffer == 0) {
			namei_debug_buffer_next =
			namei_debug_buffer = (char *) new_buffer;
			namei_debug_buffer_end = namei_debug_buffer_next + NAMEI_DEBUG_BUFFER_SIZE;
		}
		 else {
			(void) vm_deallocate(kernel_map, &new_buffer, NAMEI_DEBUG_BUFFER_SIZE, TRUE);
		}
	}
	do {
		*namei_debug_buffer_next++ = *path++;
		if (namei_debug_buffer_next == namei_debug_buffer_end)
			namei_debug_buffer_next = namei_debug_buffer;
	} while (*path != 0);

	lock_done(&namei_debug_buffer_lock);
}

void	namei_debug_init()
{
	lock_init(&namei_debug_buffer_lock, TRUE);
}
#endif	0
#endif	MACH_DEBUG
