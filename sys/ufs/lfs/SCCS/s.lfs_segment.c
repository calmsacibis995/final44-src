h54893
s 00024/00011/01116
d D 8.10 95/06/10 05:46:53 margo 66 65
c Do wakeups on both generic cleaner location as well as lfs_nextseg 
c in case running with multiple cleaners.  Also, make mods to lock correctly 
c during segment writing.
e
s 00006/00003/01121
d D 8.9 95/05/14 00:29:14 mckusick 65 64
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00067/00028/01057
d D 8.8 95/05/08 12:16:44 mckusick 64 63
c update from margo
e
s 00018/00018/01067
d D 8.7 95/03/21 00:28:00 mckusick 63 62
c daddr_t => ufs_daddr_t
e
s 00001/00001/01084
d D 8.6 95/01/02 23:26:38 mckusick 62 61
c You can't do pointer arithmetic on a void* in ANSI C (from mycroft)
e
s 00003/00007/01082
d D 8.5 94/01/04 22:17:44 bostic 61 60
c lint
e
s 00021/00038/01068
d D 8.4 93/12/30 16:16:13 mckusick 60 59
c vget now locks optionally; new queue structure; no longer need
c non-locking version of vget; no longer need ufs_inactive expansion
e
s 00005/00004/01101
d D 8.3 93/09/23 16:15:16 bostic 59 58
c changes for 4.4BSD-Lite requested by USL
e
s 00018/00019/01087
d D 8.2 93/09/21 07:30:25 bostic 58 57
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/01104
d D 8.1 93/06/11 16:27:50 bostic 57 56
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00175/00145/00931
d D 7.38 92/12/10 14:26:37 margo 56 55
c Make local routines (lfs_vref, lfs_vunref) global.  Remove argument 
c to lfs_writesuper.  Move allocation into lock and unlock routines. Recompute 
c number of locked buffers after a segment write because vinvalbuf might have 
c removed some.  Add statistics counting.  Allow writevnodes to write just files 
c with no dirty blocks (good for tossing vnodes out of the cache).  Turn off 
c direcotry operation locking.  Use MAXPHYS sized buffers.  Write only 1 super-
c block.  Write it asynchronously.
e
s 00004/00001/01072
d D 7.37 92/10/24 10:00:17 margo 55 54
c Don't construct 0 length partials
e
s 00016/00014/01057
d D 7.36 92/10/08 13:46:07 margo 54 53
c Use new queue structures.  Count finfos before you collect them in 
c case you have to write the segment in the middle.  Mark newly created buffers 
c B_DONE so bread will use them.
e
s 00001/00005/01070
d D 7.35 92/09/03 08:24:15 margo 53 52
c Make writeinode always return a value!  Get rid of debugging check.
e
s 00028/00016/01047
d D 7.34 92/09/02 08:01:31 margo 52 51
c Make lfs_vflush perform a checkpoint if necessary.  When computing 
c data checksums, get the data from the user space if the blocks are coming from 
c the cleaner.  Also, update segusage information before computing data checksum 
c since you may be checksumming segusage info.  Check for out of space condition.
e
s 00005/00008/01058
d D 7.33 92/08/28 18:11:57 bostic 51 50
c You may create dirty ifile blocks on a checkpoint if you dirty a 
c new segment.  Don't panic, just write them too.
e
s 00009/00003/01057
d D 7.32 92/08/27 22:18:31 bostic 50 49
c Make sure you don't use buffers after you brelse/bwrite them.  Also, 
c make sure to zero out allocated buffers.
e
s 00028/00007/01032
d D 7.31 92/08/26 18:25:07 bostic 49 48
c Hang temporary buffers off the devvp, not the ifile vnode.  Add 
c hack so that you can find fs on write buffers to keep track of iocount.
e
s 00017/00008/01022
d D 7.30 92/08/25 14:34:07 bostic 48 47
c Put a vnode pointer in the segment structure.
e
s 00172/00131/00858
d D 7.29 92/08/21 17:28:04 bostic 47 46
c Move SEGMENT structure definition to include for use by lfs_syscalls.
c Break lfs_gather into block-oriented interface for cleaner calls.  Count 
c segments used to trigger checkpoints. Restructure to work from lfs_markv call. 
c Many of the parameters from updatemeta and gather now live in the segment 
c structure.
e
s 00000/00033/00989
d D 7.28 92/08/01 15:40:41 bostic 46 45
c delete VERBOSE #ifdef's
e
s 00004/00003/01018
d D 7.27 92/08/01 15:29:31 bostic 45 44
c make sure initseg always gets called before writeseg; correct check
c for disk address in current partial; fix data checksum; fix byte accounting
c for seg use
e
s 00009/00009/01012
d D 7.26 92/07/25 17:28:29 bostic 44 43
c Ifile inode address is maintained in the superblock.  Don't bother filling in 
c the ifile, since this is never consulted and only dirties extra blocks.
e
s 00044/00029/00977
d D 7.25 92/07/23 16:28:26 bostic 43 42
c Do block accounting in terms of disk sectors, not file system blocks.
c Add two new fields to segusage table to record the number of inode blocks 
c and segment summary blocks in a segment.  Used for block accounting.  Before 
c writing a checkpoint, we need to turn off the ACTIVE bit for all segments 
c written since the last checkpoint.  This marks entire segusage table dirty so 
c we don't have to loop on ifile any more.
e
s 00014/00015/00992
d D 7.24 92/07/22 18:04:34 bostic 42 41
c don't end up with dirty ifile buffers after vflush of the ifile
c splbio cleanups, lint
e
s 00006/00000/01001
d D 7.23 92/07/20 16:22:37 bostic 41 40
c fix count allocation of indirect blocks
e
s 00003/00002/00998
d D 7.22 92/07/12 15:32:25 mckusick 40 39
c new location for fifofs and specfs
e
s 00009/00017/00991
d D 7.21 92/07/05 14:38:42 bostic 39 38
c delete USES_VOP_whatever (Kirk); use lfs_seglock/unlock instead of
c vfs_busy/unbusy
e
s 00138/00082/00870
d D 7.20 92/06/23 00:06:29 bostic 38 37
c directory ops, unmount, minor cleanup; from Margo Seltzer
e
s 00013/00007/00939
d D 7.19 92/05/15 12:21:18 heideman 37 36
c direct vop calls cleaned up by hand
e
s 00003/00001/00943
d D 7.18 92/05/14 17:29:34 heideman 36 23
c vnode interface conversion
e
s 00003/00001/00943
d R 7.18 92/05/14 17:05:47 heideman 35 23
c vnode interface conversion
e
s 00003/00001/00943
d R 7.18 92/05/14 16:46:43 heideman 34 23
c vnode interface conversion
e
s 00003/00001/00943
d R 7.18 92/05/14 16:36:37 heideman 33 23
c vnode interface conversion
e
s 00003/00001/00943
d R 7.18 92/05/14 15:57:00 heideman 32 23
c vnode interface conversion
e
s 00003/00001/00943
d R 7.18 92/05/14 15:42:39 heideman 31 23
c vnode interface conversion
e
s 00003/00001/00943
d R 7.18 92/05/14 14:48:35 heideman 30 23
c vnode interface conversion
e
s 00003/00001/00943
d R 7.18 92/05/14 12:52:11 heideman 29 23
c vnode interface conversion
e
s 00003/00001/00943
d R 7.18 92/05/14 11:49:36 heideman 28 23
c vnode interface conversion
e
s 00006/00000/00944
d R 7.18 92/05/14 10:29:54 heideman 27 23
c vnode interface conversion
e
s 00008/00001/00943
d R 7.18 92/05/13 23:08:25 heideman 26 23
c vnode interface conversion
e
s 00008/00001/00943
d R 7.18 92/05/13 18:55:02 heideman 25 23
c vnode interface conversion
e
s 00008/00001/00943
d R 7.18 92/05/13 18:27:06 heideman 24 23
c vnode interface conversion
e
s 00002/00002/00942
d D 7.17 92/05/04 17:21:24 bostic 23 22
c lint
e
s 00002/00002/00942
d D 7.16 92/04/08 14:44:32 staelin 22 21
c reacquire the dirtyblk list if write a segment during traversal;
c shouldn't be necessary, but not expensive and defensive
e
s 00012/00002/00932
d D 7.15 92/03/18 11:12:28 bostic 21 20
c free memory on sleep error
e
s 00005/00002/00929
d D 7.14 92/03/03 11:49:07 bostic 20 19
c set saveaddr to NULL, otherwise will re-free space next time the buffer
c gets used; change negative byte counts to printf's for now
e
s 00083/00058/00848
d D 7.13 92/02/28 17:02:25 bostic 19 18
c copy individual buffers into 56K chunks for disk I/O
e
s 00043/00026/00863
d D 7.12 92/02/27 17:12:13 staelin 18 17
c issue wakeup when enter a new segment (previous was too often and not
c often enough); fix sum_bytes_left leak in lfs_writefile; update segusage table
c correctly when rewriting an inode; check space before allocation, else can
c allocate unnecessarily; don't update last mod when rewriting a block; fix
c segment usage information when writing the segment
e
s 00007/00006/00882
d D 7.11 92/02/05 23:04:15 mckusick 17 16
c lint
e
s 00114/00042/00774
d D 7.10 92/02/04 12:40:21 bostic 16 15
c add lfs_vflush to flush a single vnode; permit flushing of blocks from
c a locked vnode (necessary for writes to a single vnode which are larger than
c the buffer cache); do match check before diagnostic checks
e
s 00001/00001/00815
d D 7.9 91/12/31 21:47:46 bostic 15 14
c set time before the checksum...
e
s 00132/00167/00684
d D 7.8 91/12/31 14:54:07 bostic 14 13
c datosn, sntoda moved to lfs.h; check v_dirtyblkhd in lfs_segwrite,
c before calling lfs_writefile; remove update of access time in IFILE, unused;
c set segment summary create time at write, not init time; don't include summary
c blocks in active bytes in segment
e
s 00099/00070/00752
d D 7.7 91/12/30 19:17:11 bostic 13 12
c lots of minor reworking, lock the IFILE vnode before writing it
e
s 00044/00033/00778
d D 7.6 91/12/14 16:54:49 bostic 12 11
c change lfs_newseg to do all the lastseg/curseg/newseg and su_flags
c ACTIVE/DIRTY updates; check SEGUSE_SUPERBLOCK not su_nbytes; update cleaner
c info in lfs_newseg; don't update segment usage table until blocks at least
c scheduled (it doesn't matter, just more intuitive)
e
s 00000/00001/00811
d D 7.5 91/12/13 16:06:04 bostic 11 10
c update the superblock
e
s 00212/00217/00600
d D 7.4 91/12/13 12:48:42 bostic 10 9
c major fixes to buffer queueing, segment structure; lots of cleanups,
c structural changes
e
s 00430/00565/00387
d D 7.3 91/12/06 16:44:46 bostic 9 8
c LFS version 2; partial segments, new framing structure -- major rework
e
s 00001/00001/00951
d D 7.2 91/11/05 15:33:22 mckusick 8 7
c reorganization to move ufsmount ops to be vnode ops
e
s 00040/00040/00912
d D 7.1 91/11/01 17:45:24 bostic 7 6
c don't typedef struct lfs for now
c UFS/FFS split for LFS version 1; lfs moves down one level
e
s 00026/00027/00926
d D 5.6 91/11/01 17:30:51 bostic 6 5
c minor cleanups, checkpoint before integration
e
s 00025/00031/00928
d D 5.5 91/10/10 11:04:14 bostic 5 4
c printf cleanup, it seems to work
e
s 00381/00297/00578
d D 5.4 91/10/09 11:19:11 bostic 4 3
c checkpoint after Margo's changes to make sync work
e
s 00150/00165/00725
d D 5.3 91/10/03 10:28:38 bostic 3 2
c checkpoint; lots of minor stuff, synchronization redone, some bug fixes
e
s 00515/00216/00375
d D 5.2 91/10/02 09:00:34 bostic 2 1
c checkpoint
e
s 00591/00000/00000
d D 5.1 91/09/25 14:34:19 bostic 1 0
c date and time created 91/09/25 14:34:19 by bostic
e
u
U
f b 
t
T
I 1
/*
D 57
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 57
I 57
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 57
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 2
D 6
#ifdef LOGFS
E 2
#include "param.h"
#include "systm.h"
#include "namei.h"
#include "resourcevar.h"
#include "kernel.h"
#include "file.h"
#include "stat.h"
#include "buf.h"
#include "proc.h"
#include "conf.h"
#include "vnode.h"
#include "specdev.h"
#include "fifo.h"
#include "malloc.h"
#include "mount.h"
#include "../ufs/lockf.h"
#include "../ufs/quota.h"
#include "../ufs/inode.h"
#include "../ufs/dir.h"
#include "../ufs/ufsmount.h"
#include "lfs.h"
#include "lfs_extern.h"
E 6
I 6
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/namei.h>
D 14
#include <sys/resourcevar.h>
E 14
#include <sys/kernel.h>
I 14
#include <sys/resourcevar.h>
E 14
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/buf.h>
#include <sys/proc.h>
#include <sys/conf.h>
#include <sys/vnode.h>
D 40
#include <sys/specdev.h>
#include <sys/fifo.h>
E 40
#include <sys/malloc.h>
#include <sys/mount.h>
I 40

#include <miscfs/specfs/specdev.h>
#include <miscfs/fifofs/fifo.h>
E 40
I 10
D 14
#include <sys/kernel.h>			/* XXX  delete when time goes away */
E 14
E 10
E 6

I 6
D 7
#include <ufs/quota.h>
#include <ufs/inode.h>
#include <ufs/dir.h>
#include <ufs/ufsmount.h>
E 7
I 7
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/dir.h>
#include <ufs/ufs/ufsmount.h>
I 54
#include <ufs/ufs/ufs_extern.h>
E 54
E 7

D 7
#include <lfs/lfs.h>
#include <lfs/lfs_extern.h>
E 7
I 7
#include <ufs/lfs/lfs.h>
#include <ufs/lfs/lfs_extern.h>
E 7

I 56
extern int count_lock_queue __P((void));

E 56
I 9
D 47
/* In-memory description of a segment about to be written. */
D 14
typedef struct segment SEGMENT;
E 14
struct segment {
D 14
	BUF	**bpp;			/* pointer to buffer array */
	BUF	**cbpp;			/* pointer to next available bp */
	BUF	*ibp;			/* buffer pointer to inode page */
E 14
I 14
	struct buf	**bpp;		/* pointer to buffer array */
	struct buf	**cbpp;		/* pointer to next available bp */
	struct buf	*ibp;		/* buffer pointer to inode page */
	struct finfo	*fip;		/* current fileinfo pointer */
E 14
	void	*segsum;		/* segment summary info */
	u_long	ninodes;		/* number of inodes in this segment */
	u_long	seg_bytes_left;		/* bytes left in segment */
	u_long	sum_bytes_left;		/* bytes left in summary block */
	u_long	seg_number;		/* number of this segment */
#define	SEGM_CKP	0x01		/* doing a checkpoint */
	u_long	seg_flags;		/* run-time flags for this segment */
D 14
	FINFO	*fip;			/* current fileinfo pointer */
E 14
};

E 47
I 47
#define MAX_ACTIVE	10
E 47
E 9
E 6
/*
D 2
Need to write the inodes out.
The indirect buffers need to be marked dirty
What about sync?  How do you wait on the last I/O?
Need to keep vnode v_numoutput up to date for pending writes.
E 2
I 2
D 3
Add a check so that if the segment is empty, you don't write it.
Write the code with lfs_ialloc to allocate a new page of inodes if you have to.
Make an incoming sync wait until the previous one finishes.  Keith
	will write this.  When this happens, we no longer have to be
	able to chain superblocks together and handle multiple segments
	writing -- Seems like we can call biowait to wait for an io.
	However, I don't think we want to wait on the summary I/O
	necessarily, because if we've got lots of dirty buffers piling
	up, it would be nice to process them and get the segment all
	ready to write.  Perhaps we can just wait before firing up the
	next set of writes, rather than waiting to start doing anything.
	Also -- my lfs_writesuper should wait until all the segment writes
	are done (I added a biowait, but we need to make sure that the SEGMENT
	structure hasn't been freed before we get there).
Need to keep vnode v_numoutput up to date for pending writes?
???Could actually fire off the datablock writes before you finish.  This
would give them a chance to get started earlier...
E 2
*/
E 3
I 3
D 9
 * Add a check so that if the segment is empty, you don't write it.
 *
 * Change lfs_ialloc to allocate a new page of inodes if you have to.
 *
 * Need to keep vnode v_numoutput up to date for pending writes?  Could
 * actually fire off the datablock writes before you finish.  This would give
 * them a chance to get started earlier.
E 9
I 9
 * Determine if it's OK to start a partial in this segment, or if we need
 * to go on to a new segment.
E 9
 */
I 9
#define	LFS_PARTIAL_FITS(fs) \
	((fs)->lfs_dbpseg - ((fs)->lfs_offset - (fs)->lfs_curseg) > \
	1 << (fs)->lfs_fsbtodb)
E 9
E 3

D 9
static int	 lfs_biocallback __P((BUF *));
D 7
static void	 lfs_endsum __P((LFS *, SEGMENT *, int));
I 2
static SEGMENT	*lfs_gather
		    __P((LFS *, SEGMENT *, VNODE *, int (*) __P((BUF *))));
E 2
static BUF	*lfs_newbuf __P((LFS *, daddr_t, size_t));
static SEGMENT	*lfs_newseg __P((LFS *));
D 4
static void	 lfs_newsum __P((LFS *, SEGMENT *));
E 4
I 4
static SEGMENT	*lfs_newsum __P((LFS *, SEGMENT *));
E 4
static daddr_t	 lfs_nextseg __P((LFS *));
D 2
static int	 lfs_updatemeta __P((LFS *, INODE *, FINFO *, BUF **));
static SEGMENT	*lfs_writefile __P((SEGMENT *, LFS *, VNODE *));
static void	 lfs_writemeta __P((void));
E 2
I 2
D 4
static void	 lfs_updatemeta __P((LFS *, SEGMENT *, INODE *, daddr_t *, 
E 4
I 4
static void	 lfs_updatemeta __P((LFS *, SEGMENT *, INODE *, daddr_t *,
E 4
		     BUF **, int));
D 3
static void	 lfs_writeckp __P((LFS *, SEGMENT *));
E 3
I 3
static SEGMENT	*lfs_writeckp __P((LFS *, SEGMENT *));
E 3
D 4
static SEGMENT	*lfs_writefile __P((SEGMENT *, LFS *, VNODE *, int));
static SEGMENT	*lfs_writeinode __P((LFS *, SEGMENT *, VNODE *));
E 4
I 4
static SEGMENT	*lfs_writefile __P((LFS *, SEGMENT *, VNODE *, int));
static SEGMENT	*lfs_writeinode __P((LFS *, SEGMENT *, INODE *));
E 4
E 2
static void	 lfs_writeseg __P((LFS *, SEGMENT *));
I 3
static void	 lfs_writesum __P((LFS *));
E 3
D 2
static void	 shellsort __P((BUF **, u_long *, register int));
E 2
I 2
D 4
static void	 lfs_writesuper __P((LFS *, SEGMENT *));
E 4
I 4
static void	 lfs_writesuper __P((LFS *));
E 7
I 7
static void	 lfs_endsum __P((struct lfs *, SEGMENT *, int));
static SEGMENT	*lfs_gather __P((struct lfs *,
		     SEGMENT *, VNODE *, int (*) __P((BUF *))));
static BUF	*lfs_newbuf __P((struct lfs *, daddr_t, size_t));
static SEGMENT	*lfs_newseg __P((struct lfs *));
static SEGMENT	*lfs_newsum __P((struct lfs *, SEGMENT *));
E 9
I 9
D 14
#define	datosn(fs, daddr)	/* disk address to segment number */ \
	(((daddr) - (fs)->lfs_sboffs[0]) / fsbtodb((fs), (fs)->lfs_ssize))

#define sntoda(fs, sn) 		/* segment number to disk address */ \
	((daddr_t)((sn) * ((fs)->lfs_ssize << (fs)->lfs_fsbtodb) + \
	    (fs)->lfs_sboffs[0]))

D 13
static int	 lfs_callback __P((BUF *));
static void	 lfs_gather __P((struct lfs *,
		     SEGMENT *, VNODE *, int (*) __P((struct lfs *, BUF *))));
I 10
static void	 lfs_initseg __P((struct lfs *, SEGMENT *));
E 10
static BUF	*lfs_newbuf __P((struct lfs *, SEGMENT *, daddr_t, size_t));
D 10
static void	 lfs_newseg __P((struct lfs *, SEGMENT *));
E 9
static daddr_t	 lfs_nextseg __P((struct lfs *));
E 10
I 10
D 12
static daddr_t	 lfs_newseg __P((struct lfs *));
E 12
I 12
static void	 lfs_newseg __P((struct lfs *));
E 12
E 10
static void	 lfs_updatemeta __P((struct lfs *,
D 9
		     SEGMENT *, INODE *, daddr_t *, BUF **, int));
static SEGMENT	*lfs_writeckp __P((struct lfs *, SEGMENT *));
static SEGMENT	*lfs_writefile __P((struct lfs *, SEGMENT *, VNODE *, int));
static SEGMENT	*lfs_writeinode __P((struct lfs *, SEGMENT *, INODE *));
E 9
I 9
		     SEGMENT *, VNODE *, daddr_t *, BUF **, int));
static void	 lfs_writefile __P((struct lfs *, SEGMENT *, VNODE *));
static void	 lfs_writeinode __P((struct lfs *, SEGMENT *, INODE *));
E 9
static void	 lfs_writeseg __P((struct lfs *, SEGMENT *));
D 9
static void	 lfs_writesum __P((struct lfs *));
static void	 lfs_writesuper __P((struct lfs *));
E 7
E 4
static int	 match_data __P((BUF *));
static int	 match_dindir __P((BUF *));
static int	 match_indir __P((BUF *));
I 4
D 7
static daddr_t	 next __P((LFS *, SEGMENT *, int *));
E 7
I 7
static daddr_t	 next __P((struct lfs *, SEGMENT *, int *));
E 9
I 9
static void	 lfs_writesuper __P((struct lfs *, SEGMENT *));
static int	 match_data __P((struct lfs *, BUF *));
static int	 match_dindir __P((struct lfs *, BUF *));
static int	 match_indir __P((struct lfs *, BUF *));
static int	 match_tindir __P((struct lfs *, BUF *));
E 9
E 7
E 4
static void	 shellsort __P((BUF **, daddr_t *, register int));
E 13
I 13
int	 lfs_callback __P((BUF *));
void	 lfs_gather __P((struct lfs *,
	    SEGMENT *, VNODE *, int (*) __P((struct lfs *, BUF *))));
void	 lfs_initseg __P((struct lfs *, SEGMENT *));
void	 lfs_iset __P((INODE *, daddr_t, time_t));
int	 lfs_match_data __P((struct lfs *, BUF *));
int	 lfs_match_dindir __P((struct lfs *, BUF *));
int	 lfs_match_indir __P((struct lfs *, BUF *));
int	 lfs_match_tindir __P((struct lfs *, BUF *));
BUF	*lfs_newbuf __P((struct lfs *, SEGMENT *, daddr_t, size_t));
E 14
I 14
D 23
int	 lfs_callback __P((struct buf *));
E 23
I 23
void	 lfs_callback __P((struct buf *));
E 23
void	 lfs_gather __P((struct lfs *, struct segment *,
	     struct vnode *, int (*) __P((struct lfs *, struct buf *))));
I 47
int	 lfs_gatherblock __P((struct segment *, struct buf *, int *));
E 47
D 56
void	 lfs_initseg __P((struct lfs *, struct segment *));
E 56
D 63
void	 lfs_iset __P((struct inode *, daddr_t, time_t));
E 63
I 63
void	 lfs_iset __P((struct inode *, ufs_daddr_t, time_t));
E 63
int	 lfs_match_data __P((struct lfs *, struct buf *));
int	 lfs_match_dindir __P((struct lfs *, struct buf *));
int	 lfs_match_indir __P((struct lfs *, struct buf *));
int	 lfs_match_tindir __P((struct lfs *, struct buf *));
D 47
struct buf *
D 19
	 lfs_newbuf __P((struct lfs *, struct segment *, daddr_t, size_t));
E 19
I 19
	 lfs_newbuf __P((struct lfs *, daddr_t, size_t));
E 47
E 19
E 14
void	 lfs_newseg __P((struct lfs *));
D 14
void	 lfs_shellsort __P((BUF **, daddr_t *, register int));
E 14
I 14
D 63
void	 lfs_shellsort __P((struct buf **, daddr_t *, register int));
E 63
I 63
void	 lfs_shellsort __P((struct buf **, ufs_daddr_t *, register int));
E 63
E 14
D 47
void	 lfs_updatemeta __P((struct lfs *,
D 14
	    SEGMENT *, VNODE *, daddr_t *, BUF **, int));
void	 lfs_writefile __P((struct lfs *, SEGMENT *, VNODE *));
void	 lfs_writeinode __P((struct lfs *, SEGMENT *, INODE *));
void	 lfs_writeseg __P((struct lfs *, SEGMENT *));
void	 lfs_writesuper __P((struct lfs *, SEGMENT *));
E 14
I 14
	    struct segment *, struct vnode *, daddr_t *, struct buf **, int));
E 47
I 47
void	 lfs_supercallback __P((struct buf *));
D 48
void	 lfs_updatemeta __P((struct segment *, struct vnode *));
E 48
I 48
void	 lfs_updatemeta __P((struct segment *));
I 56
int	 lfs_vref __P((struct vnode *));
void	 lfs_vunref __P((struct vnode *));
E 56
E 48
E 47
void	 lfs_writefile __P((struct lfs *, struct segment *, struct vnode *));
D 38
void	 lfs_writeinode __P((struct lfs *, struct segment *, struct inode *));
void	 lfs_writeseg __P((struct lfs *, struct segment *));
E 38
I 38
int	 lfs_writeinode __P((struct lfs *, struct segment *, struct inode *));
int	 lfs_writeseg __P((struct lfs *, struct segment *));
E 38
D 56
void	 lfs_writesuper __P((struct lfs *, struct segment *));
E 56
I 56
void	 lfs_writesuper __P((struct lfs *));
E 56
I 38
void	 lfs_writevnodes __P((struct lfs *fs, struct mount *mp,
	    struct segment *sp, int dirops));
E 38
E 14
E 13
E 2

D 9
/*
 * XXX -- when we add fragments in here, we will need to allocate a larger
 * buffer pointer array (sp->bpp).
 */
E 9
I 9
int	lfs_allclean_wakeup;		/* Cleaner wakeup address. */

I 56
/* Statistics Counters */
#define DOSTATS
struct lfs_stats lfs_stats;

/* op values to lfs_writevnodes */
#define	VN_REG	0
#define	VN_DIROP	1
#define	VN_EMPTY	2

E 56
I 16
/*
 * Ifile and meta data blocks are not marked busy, so segment writes MUST be
 * single threaded.  Currently, there are two paths into lfs_segwrite, sync()
 * and getnewbuf().  They both mark the file system busy.  Lfs_vflush()
 * explicitly marks the file system busy.  So lfs_segwrite is safe.  I think.
 */

E 16
E 9
int
I 16
lfs_vflush(vp)
	struct vnode *vp;
{
	struct inode *ip;
	struct lfs *fs;
D 39
	struct mount *mp;
E 39
	struct segment *sp;
D 61
	int error, s;
E 61

D 46
#ifdef VERBOSE
	printf("lfs_vflush\n");
#endif
E 46
D 39
	mp = vp->v_mount;
	fs = VFSTOUFS(mp)->um_lfs;
E 39
I 39
	fs = VFSTOUFS(vp->v_mount)->um_lfs;
I 52
	if (fs->lfs_nactive > MAX_ACTIVE)
D 56
		return(lfs_segwrite(vp->v_mount, 1));
E 56
I 56
		return(lfs_segwrite(vp->v_mount, SEGM_SYNC|SEGM_CKP));
	lfs_seglock(fs, SEGM_SYNC);
	sp = fs->lfs_sp;
E 56

E 52
D 56
	lfs_seglock(fs);
E 56
E 39

D 56
	/*
D 39
	 * XXX
	 * check flags?
	 * mp->mnt_flag & (MNT_MLOCK|MNT_RDONLY|MNT_MPBUSY) ||
	 */
	if (vfs_busy(mp))
		return (0);

	/*
E 39
	 * Allocate a segment structure and enough space to hold pointers to
	 * the maximum possible number of buffers which can be described in a
	 * single summary block.
	 */
	sp = malloc(sizeof(struct segment), M_SEGMENT, M_WAITOK);
	sp->bpp = malloc(((LFS_SUMMARY_SIZE - sizeof(SEGSUM)) /
	    sizeof(daddr_t) + 1) * sizeof(struct buf *), M_SEGMENT, M_WAITOK);
	sp->seg_flags = SEGM_CKP;
I 48
	sp->vp = NULL;
E 48
D 45
	lfs_initseg(fs, sp);
E 45

	/*
	 * Keep a cumulative count of the outstanding I/O operations.  If the
	 * disk drive catches up with us it could go to zero before we finish,
	 * so we artificially increment it by one until we've scheduled all of
	 * the writes we intend to do.
	 */
	s = splbio();
D 19
	fs->lfs_iocount = 1;
E 19
I 19
	++fs->lfs_iocount;
E 19
	splx(s);

E 56
D 42
	if (vp->v_dirtyblkhd != NULL)
		lfs_writefile(fs, sp, vp);
E 42
	ip = VTOI(vp);
I 56
D 60
	if (vp->v_dirtyblkhd.le_next == NULL)
E 60
I 60
	if (vp->v_dirtyblkhd.lh_first == NULL)
E 60
		lfs_writevnodes(fs, vp->v_mount, sp, VN_EMPTY);

E 56
D 38
	lfs_writeinode(fs, sp, ip);
E 38
I 38
D 42
	(void) lfs_writeinode(fs, sp, ip);
E 38
	ip->i_flags &= ~(IMOD | IACC | IUPD | ICHG);
E 42
I 42
	do {
I 45
D 56
		lfs_initseg(fs, sp);
E 56
E 45
		do {
D 54
			if (vp->v_dirtyblkhd != NULL)
E 54
I 54
D 60
			if (vp->v_dirtyblkhd.le_next != NULL)
E 60
I 60
			if (vp->v_dirtyblkhd.lh_first != NULL)
E 60
E 54
				lfs_writefile(fs, sp, vp);
		} while (lfs_writeinode(fs, sp, ip));
D 47
		ip->i_flags &= ~(IMOD | IACC | IUPD | ICHG);
E 47
E 42

D 38
	lfs_writeseg(fs, sp);
E 38
I 38
D 39
	(void) lfs_writeseg(fs, sp);
E 39
I 39
D 42
	(void)lfs_writeseg(fs, sp);
E 42
I 42
	} while (lfs_writeseg(fs, sp) && ip->i_number == LFS_IFILE_INUM);
E 42
E 39
E 38

D 56
	/*
	 * If the I/O count is non-zero, sleep until it reaches zero.  At the
	 * moment, the user's process hangs around so we can sleep.
	 */
	s = splbio();
	if (--fs->lfs_iocount && (error =
D 17
	    tsleep(&fs->lfs_iocount, PRIBIO + 1, "lfs vflush", 0)))
E 17
I 17
D 19
	    tsleep((caddr_t)&fs->lfs_iocount, PRIBIO + 1, "lfs vflush", 0)))
E 19
I 19
D 21
	    tsleep(&fs->lfs_iocount, PRIBIO + 1, "lfs vflush", 0)))
E 21
I 21
	    tsleep(&fs->lfs_iocount, PRIBIO + 1, "lfs vflush", 0))) {
		free(sp->bpp, M_SEGMENT);
		free(sp, M_SEGMENT);
E 21
E 19
E 17
		return (error);
I 21
	}
E 21
	splx(s);
E 56
I 56
#ifdef DOSTATS
	++lfs_stats.nwrites;
	if (sp->seg_flags & SEGM_SYNC)
		++lfs_stats.nsync_writes;
	if (sp->seg_flags & SEGM_CKP)
		++lfs_stats.ncheckpoints;
#endif
E 56
D 39
	vfs_unbusy(mp);
E 39
I 39
	lfs_segunlock(fs);
E 39
D 56

I 21
	/*
	 * XXX
	 * Should be writing a checkpoint?
	 */
E 21
	free(sp->bpp, M_SEGMENT);
	free(sp, M_SEGMENT);

E 56
	return (0);
}

I 38
void
D 56
lfs_writevnodes(fs, mp, sp, dirops)
E 56
I 56
lfs_writevnodes(fs, mp, sp, op)
E 56
	struct lfs *fs;
	struct mount *mp;
	struct segment *sp;
D 56
	int dirops;
E 56
I 56
	int op;
E 56
{
	struct inode *ip;
	struct vnode *vp;
D 56
	int error, s;
E 56
I 56
D 61
	int error, s, active;
E 61
E 56

I 64
/* BEGIN HACK */
#define	VN_OFFSET	(((void *)&vp->v_mntvnodes.le_next) - (void *)vp)
#define	BACK_VP(VP)	((struct vnode *)(((void *)VP->v_mntvnodes.le_prev) - VN_OFFSET))
#define	BEG_OF_VLIST	((struct vnode *)(((void *)&mp->mnt_vnodelist.lh_first) - VN_OFFSET))

/* Find last vnode. */
loop:   for (vp = mp->mnt_vnodelist.lh_first;
	     vp && vp->v_mntvnodes.le_next != NULL;
	     vp = vp->v_mntvnodes.le_next);
	for (; vp && vp != BEG_OF_VLIST; vp = BACK_VP(vp)) {
/* END HACK */
/*
E 64
D 60
loop:	for (vp = mp->mnt_mounth; vp; vp = vp->v_mountf) {
E 60
I 60
loop:
	for (vp = mp->mnt_vnodelist.lh_first;
	     vp != NULL;
	     vp = vp->v_mntvnodes.le_next) {
I 64
*/
E 64
E 60
		/*
		 * If the vnode that we are about to sync is no longer
		 * associated with this mount point, start over.
		 */
		if (vp->v_mount != mp)
			goto loop;

D 56
		if (dirops && !(vp->v_flag & VDIROP) ||
		    !dirops && (vp->v_flag & VDIROP))
E 56
I 56
		/* XXX ignore dirops for now
		if (op == VN_DIROP && !(vp->v_flag & VDIROP) ||
		    op != VN_DIROP && (vp->v_flag & VDIROP))
E 56
			continue;
D 56
		/*
		 * XXX
		 * Up the ref count so we don't get tossed out of
		 * memory.
		 */
		VREF(vp);
E 56
I 56
		*/
E 56

I 56
D 60
		if (op == VN_EMPTY && vp->v_dirtyblkhd.le_next)
E 60
I 60
		if (op == VN_EMPTY && vp->v_dirtyblkhd.lh_first)
E 60
			continue;

		if (vp->v_type == VNON)
			continue;

		if (lfs_vref(vp))
			continue;

E 56
		/*
		 * Write the inode/file if dirty and it's not the
		 * the IFILE.
		 */
		ip = VTOI(vp);
D 58
		if ((ip->i_flag & (IMOD | IACC | IUPD | ICHG) ||
E 58
I 58
D 59
		if ((ip->i_flag & (IMODIFIED | IACCESS | IUPDATE | ICHANGE) ||
E 59
I 59
		if ((ip->i_flag &
		    (IN_ACCESS | IN_CHANGE | IN_MODIFIED | IN_UPDATE) ||
E 59
E 58
D 54
		    vp->v_dirtyblkhd != NULL) &&
E 54
I 54
D 60
		    vp->v_dirtyblkhd.le_next != NULL) &&
E 60
I 60
		    vp->v_dirtyblkhd.lh_first != NULL) &&
E 60
E 54
		    ip->i_number != LFS_IFILE_INUM) {
D 54
			if (vp->v_dirtyblkhd != NULL)
E 54
I 54
D 60
			if (vp->v_dirtyblkhd.le_next != NULL)
E 60
I 60
			if (vp->v_dirtyblkhd.lh_first != NULL)
E 60
E 54
				lfs_writefile(fs, sp, vp);
			(void) lfs_writeinode(fs, sp, ip);
D 47
			ip->i_flags &= ~(IMOD | IACC | IUPD | ICHG);
E 47
		}
		vp->v_flag &= ~VDIROP;
D 56
		vrele(vp);
E 56
I 56
		lfs_vunref(vp);
E 56
	}
}

E 38
int
E 16
D 2
lfs_segwrite(mp)
E 2
I 2
D 56
lfs_segwrite(mp, do_ckp)
E 56
I 56
lfs_segwrite(mp, flags)
E 56
E 2
D 14
	MOUNT *mp;
E 14
I 14
	struct mount *mp;
E 14
I 2
D 9
	int do_ckp;			/* do a checkpoint too */
E 9
I 9
D 56
	int do_ckp;			/* Do a checkpoint. */
E 56
I 56
	int flags;			/* Do a checkpoint. */
E 56
E 9
E 2
{
I 65
	struct proc *p = curproc;	/* XXX */
E 65
I 43
	struct buf *bp;
E 43
I 36
D 39
	USES_VOP_ISLOCKED;
E 39
E 36
D 4
	FINFO *fip;			/* current file info structure */
E 4
D 14
	INODE *ip;
E 14
I 14
	struct inode *ip;
E 14
D 7
	LFS *fs;
E 7
I 7
	struct lfs *fs;
E 7
D 14
	VNODE *vp;
	SEGMENT *sp;
E 14
I 14
	struct segment *sp;
	struct vnode *vp;
E 14
I 3
D 10
	int s;
E 10
I 10
D 16
	int s, error;
E 16
I 16
D 38
	int error, islocked, s;
E 38
I 38
D 43
	int error, s;
E 43
I 43
	SEGUSE *segusep;
D 63
	daddr_t ibno;
E 63
I 63
	ufs_daddr_t ibno;
E 63
D 47
	int error, i, s;
E 47
I 47
	CLEANERINFO *cip;
D 61
	int clean, error, i, s;
I 56
	int do_ckp;
E 61
I 61
	int clean, do_ckp, error, i;
E 61
E 56
E 47
E 43
E 38
E 16
E 10
E 3

I 14
D 16
	/*
	 * Ifile and meta data blocks are not marked busy, so segment writes
	 * must be single threaded.  Currently, there are two paths into this
	 * code, sync() and getnewbuf().  They both mark the file system busy,
	 * so lfs_segwrite is safe.  I think.
	 */
E 16
E 14
I 9
D 46
#ifdef VERBOSE
	printf("lfs_segwrite\n");
#endif
E 46
I 16
	fs = VFSTOUFS(mp)->um_lfs;
I 47

 	/*
 	 * If we have fewer than 2 clean segments, wait until cleaner
	 * writes.
 	 */
	do {
		LFS_CLEANERINFO(cip, fs, bp);
		clean = cip->clean;
		brelse(bp);
D 66
		if (clean <= 2) {
E 66
I 66
		if (clean <= 2 || fs->lfs_avail <= 0) {
E 66
D 64
			printf ("segs clean: %d\n", clean);
E 64
I 64
			/* printf ("segs clean: %d\n", clean); */
E 64
			wakeup(&lfs_allclean_wakeup);
I 66
			wakeup(&fs->lfs_nextseg);
E 66
			if (error = tsleep(&fs->lfs_avail, PRIBIO + 1,
			    "lfs writer", 0))
				return (error);
		}
D 66
	} while (clean <= 2 );
E 66
I 66
	} while (clean <= 2 || fs->lfs_avail <= 0);
E 66
E 47
I 39
D 56
	lfs_seglock(fs);
E 56
E 39
E 16
I 14

E 14
E 9
D 2
printf("lfs_segwrite: %s %s\n", mp->mnt_stat.f_mntonname, mp->mnt_stat.f_mntfromname);
E 2
D 10
	fs = VFSTOUFS(mp)->um_lfs;
I 4

E 10
D 9
#ifdef DIAGNOSTIC
	if (fs->lfs_seglist != NULL)
		panic("lfs_segwrite: seglist not NULL");
#endif

E 9
E 4
I 3
	/*
I 16
	 * Allocate a segment structure and enough space to hold pointers to
	 * the maximum possible number of buffers which can be described in a
	 * single summary block.
	 */
I 47
D 56
	do_ckp = do_ckp || fs->lfs_nactive > MAX_ACTIVE;
E 47
	sp = malloc(sizeof(struct segment), M_SEGMENT, M_WAITOK);
	sp->bpp = malloc(((LFS_SUMMARY_SIZE - sizeof(SEGSUM)) /
	    sizeof(daddr_t) + 1) * sizeof(struct buf *), M_SEGMENT, M_WAITOK);
	sp->seg_flags = do_ckp ? SEGM_CKP : 0;
I 48
	sp->vp = NULL;
E 48
	lfs_initseg(fs, sp);
E 56
I 56
	do_ckp = flags & SEGM_CKP || fs->lfs_nactive > MAX_ACTIVE;
	lfs_seglock(fs, flags | (do_ckp ? SEGM_CKP : 0));
	sp = fs->lfs_sp;
E 56

D 56
	/*
E 16
D 9
	 * LFS requires that the summary blocks be written after the rest of
	 * the segment, and that the super blocks (on checkpoint) be written
	 * last of all.  We keep a cumulative count of the outstanding blocks
	 * from all of the segments, and write these blocks when this count
	 * goes to zero.  If the disk drive catches up with us it could go
	 * to zero before we finish, so we artificially increment it by one
	 * until we've scheduled all of the writes we intend to do.  At the
	 * moment, the user's process hangs around so we can sleep; this should
	 * probably be redone using a kernel thread.
E 9
I 9
D 19
	 * If doing a checkpoint, we keep a cumulative count of the outstanding
	 * I/O operations.  If the disk drive catches up with us it could go to
	 * zero before we finish, so we artificially increment it by one until
	 * we've scheduled all of the writes we intend to do.
E 19
I 19
	 * Keep a cumulative count of the outstanding I/O operations.  If the
	 * disk drive catches up with us it could go to zero before we finish,
	 * so we artificially increment it by one until we've scheduled all of
	 * the writes we intend to do.  If not a checkpoint, we never do the
	 * final decrement, avoiding the wakeup in the callback routine.
E 19
E 9
	 */
I 10
D 16
	fs = VFSTOUFS(mp)->um_lfs;
E 16
E 10
D 9
	s = splbio();
	fs->lfs_iocount = 1;
	splx(s);
E 9
I 9
D 19
	if (do_ckp) {
		s = splbio();
		fs->lfs_iocount = 1;
		splx(s);
	}
E 19
I 19
	s = splbio();
D 38
	++fs->lfs_iocount;
E 38
I 38
D 42
	fs->lfs_iocount++;
E 42
I 42
	++fs->lfs_iocount;
E 42
E 38
	splx(s);
E 56
I 56
	lfs_writevnodes(fs, mp, sp, VN_REG);
E 56
E 19
E 9
D 4
	
E 4
I 4

E 4
E 3
D 2

E 2
D 9
	sp = lfs_newseg(fs);
E 9
I 9
D 16
	/*
	 * Allocate a segment structure and enough space to hold pointers to
	 * the maximum possible number of buffers which can be described in a
	 * single summary block.
	 */
D 14
	sp = malloc(sizeof(SEGMENT), M_SEGMENT, M_WAITOK);
E 14
I 14
	sp = malloc(sizeof(struct segment), M_SEGMENT, M_WAITOK);
E 14
	sp->bpp = malloc(((LFS_SUMMARY_SIZE - sizeof(SEGSUM)) /
D 14
	    sizeof(daddr_t) + 1) * sizeof(BUF *), M_SEGMENT, M_WAITOK);
E 14
I 14
	    sizeof(daddr_t) + 1) * sizeof(struct buf *), M_SEGMENT, M_WAITOK);
E 14
	sp->seg_flags = do_ckp ? SEGM_CKP : 0;
D 10
	lfs_newseg(fs, sp);
E 10
I 10
	lfs_initseg(fs, sp);
E 10
E 9
loop:
	for (vp = mp->mnt_mounth; vp; vp = vp->v_mountf) {
E 16
I 16
D 38
loop:	for (vp = mp->mnt_mounth; vp; vp = vp->v_mountf) {
E 16
		/*
		 * If the vnode that we are about to sync is no longer
		 * associated with this mount point, start over.
		 */
D 2
printf("lfs_segwrite: processing inum %d\n", VTOI(vp)->i_number);
E 2
		if (vp->v_mount != mp)
			goto loop;
E 38
I 38
D 56
	lfs_writevnodes(fs, mp, sp, 0);
E 56
I 56
	/* XXX ignore ordering of dirops for now */
	/* XXX
E 56
D 42
	s = splbio();
E 42
	fs->lfs_writer = 1;
	if (fs->lfs_dirops && (error =
	    tsleep(&fs->lfs_writer, PRIBIO + 1, "lfs writer", 0))) {
		free(sp->bpp, M_SEGMENT);
		free(sp, M_SEGMENT); 
		fs->lfs_writer = 0;
D 42
		splx(s);
		return(error);
E 42
I 42
		return (error);
E 42
	}
D 42
	splx(s);
E 42
E 38
D 16
		if (VOP_ISLOCKED(vp))
			continue;
E 16
I 9

D 10
		/* If nothing dirty, or it's the IFILE, skip it. */
E 10
I 10
D 16
		/*
		 * Write the inode/file if dirty and it's not the
		 * the IFILE.
		 */
E 10
E 9
		ip = VTOI(vp);
D 9
		if (ip->i_number == LFS_IFILE_INUM)
E 9
I 9
		if (ip->i_flag & (IMOD | IACC | IUPD | ICHG) == 0 &&
		    vp->v_dirtyblkhd == NULL ||
		    ip->i_number == LFS_IFILE_INUM)
E 9
			continue;
E 16
I 16
D 38
		islocked = VOP_ISLOCKED(vp);
E 38
I 38
D 56
	lfs_writevnodes(fs, mp, sp, 1);
E 56
I 56
	lfs_writevnodes(fs, mp, sp, VN_DIROP);
	*/
E 56
E 38
E 16
D 4
		if ((ip->i_flag & (IMOD|IACC|IUPD|ICHG)) == 0 &&
E 4
I 4
D 9
		if ((ip->i_flag & (IMOD | IACC | IUPD | ICHG)) == 0 &&
E 4
		    vp->v_dirtyblkhd == NULL)
			continue;
E 9
I 9

I 13
D 38
		/*
		 * XXX
		 * This is wrong, I think -- we should just wait until we
		 * get the vnode and go on.  Probably going to reschedule
		 * all of the writes we already scheduled...
		 */
E 13
E 9
D 16
		if (vget(vp))
E 16
I 16
		if (islocked)
			VREF(vp);
		else if (vget(vp))
E 16
I 14
{
printf("lfs_segment: failed to get vnode (tell Keith)!\n");
E 14
			goto loop;
I 14
}
E 14
D 2
		sp = lfs_writefile(sp, fs, vp);

		/* Need to take care of inode now */
printf("lfs_segwrite: need to add dinode %d to seg\n", ip->i_din.di_inum);
E 2
I 2
D 4
		sp = lfs_writefile(sp, fs, vp, do_ckp);
E 4
I 4
D 9
		sp = lfs_writefile(fs, sp, vp, do_ckp);
E 9
I 9
D 13
		lfs_writefile(fs, sp, vp);
E 13
I 13
D 16

		if (vp->v_dirtyblkhd != NULL)
			lfs_writefile(fs, sp, vp);
E 13
I 10
		lfs_writeinode(fs, sp, ip);
I 13
		ip->i_flags &= ~(IMOD | IACC | IUPD | ICHG);
E 13
E 10
E 9
E 4
E 2
		vput(vp);
E 16
I 16
		/*
		 * Write the inode/file if dirty and it's not the
		 * the IFILE.
		 */
		ip = VTOI(vp);
		if ((ip->i_flag & (IMOD | IACC | IUPD | ICHG) ||
		    vp->v_dirtyblkhd != NULL) &&
		    ip->i_number != LFS_IFILE_INUM) {
			if (vp->v_dirtyblkhd != NULL)
				lfs_writefile(fs, sp, vp);
			lfs_writeinode(fs, sp, ip);
			ip->i_flags &= ~(IMOD | IACC | IUPD | ICHG);
		}
		if (islocked)
			vrele(vp);
		else
			vput(vp);
E 16
	}
I 13
D 14
	/*
	 * XXX
	 * Should we always do the dirty blocks of the ifile?  Why just
	 * for a checkpoint.  No seeks are involved.
	 */
E 14
E 13
I 3
D 4

E 4
E 3
D 2
	/*
	 * Force stale file system control information to be flushed.
	 */
	lfs_writeseg(fs, sp);
/*	vflushbuf(ump->um_devvp, waitfor == MNT_WAIT ? B_SYNC : 0); */
printf("lfs_segwrite: returning from segwrite\n");
E 2
I 2
D 9
	if (do_ckp)
D 3
		lfs_writeckp(fs, sp);
E 3
I 3
		sp = lfs_writeckp(fs, sp);
E 9
I 9
	if (do_ckp) {
E 38
I 38
	/*
D 43
	 * If this is a checkpoint, we need to loop on both the ifile and
	 * the writeseg to make sure that we don't end up with any dirty
	 * buffers left when this is all over.
E 43
I 43
	 * If we are doing a checkpoint, mark everything since the
	 * last checkpoint as no longer ACTIVE.
E 43
	 */
I 43
	if (do_ckp)
		for (ibno = fs->lfs_cleansz + fs->lfs_segtabsz;
		     --ibno >= fs->lfs_cleansz; ) {
			if (bread(fs->lfs_ivnode, ibno, fs->lfs_bsize,
			    NOCRED, &bp))

				panic("lfs: ifile read");
D 58
			segusep = (SEGUSE *)bp->b_un.b_addr;
E 58
I 58
			segusep = (SEGUSE *)bp->b_data;
E 58
			for (i = fs->lfs_sepb; i--; segusep++)
				segusep->su_flags &= ~SEGUSE_ACTIVE;
				
D 47
			LFS_UBWRITE(bp);
E 47
I 47
			error = VOP_BWRITE(bp);
E 47
		}

E 43
	if (do_ckp || fs->lfs_doifile) {
I 51
redo:
E 51
D 43
redo:
E 43
E 38
D 13
		lfs_writefile(fs, sp, fs->lfs_ivnode);
		lfs_writeinode(fs, sp, VTOI(fs->lfs_ivnode));
E 13
I 13
		vp = fs->lfs_ivnode;
D 60
		while (vget(vp));
E 60
I 60
D 65
		while (vget(vp, 1));
E 65
I 65
		while (vget(vp, LK_EXCLUSIVE, p))
			continue;
E 65
E 60
		ip = VTOI(vp);
D 38
		if (vp->v_dirtyblkhd != NULL)
			lfs_writefile(fs, sp, vp);
		lfs_writeinode(fs, sp, ip);
E 38
I 38
D 43
		do {
			if (vp->v_dirtyblkhd != NULL)
				lfs_writefile(fs, sp, vp);
		} while (lfs_writeinode(fs, sp, ip) && do_ckp);
E 43
I 43
D 54
		if (vp->v_dirtyblkhd != NULL)
E 54
I 54
D 60
		if (vp->v_dirtyblkhd.le_next != NULL)
E 60
I 60
		if (vp->v_dirtyblkhd.lh_first != NULL)
E 60
E 54
			lfs_writefile(fs, sp, vp);
		(void)lfs_writeinode(fs, sp, ip);
E 43
E 38
D 47
		ip->i_flags &= ~(IMOD | IACC | IUPD | ICHG);
E 47
		vput(vp);
E 13
D 38
	}
E 9
E 3
D 4
	else
		lfs_writeseg(fs, sp);
E 4
I 4
	lfs_writeseg(fs, sp);
E 38
I 38
D 43
		if (lfs_writeseg(fs, sp) && do_ckp) {
			lfs_initseg(fs, sp);
			goto redo;
		}
E 43
I 43
D 51
		/*
		 * This should never happen because we just guaranteed
		 * that all the segment usage table blocks are dirty, so
		 * no new ones should get written.
		 */
		if (lfs_writeseg(fs, sp) && do_ckp)
			panic("lfs_segwrite: created dirty blocks on ckp");
E 51
I 51
D 56
		if (lfs_writeseg(fs, sp) && do_ckp) {
			lfs_initseg(fs, sp);
E 56
I 56
		if (lfs_writeseg(fs, sp) && do_ckp)
E 56
			goto redo;
D 56
		}
E 56
E 51
E 43
	} else
		(void) lfs_writeseg(fs, sp);
E 38

E 4
D 3
#ifdef NOTLFS
	vflushbuf(ump->um_devvp, waitfor == MNT_WAIT ? B_SYNC : 0);
#endif
E 3
I 3
D 9
	s = splbio();
	if (--fs->lfs_iocount)
		sleep(&fs->lfs_iocount, PRIBIO + 1);
	splx(s);
	lfs_writesum(fs);
	if (do_ckp)
D 4
		lfs_writesuper(fs, sp);
E 4
I 4
		lfs_writesuper(fs);
D 5
printf("After writesuper returning\n");

E 5
E 4
E 3
E 2
	return (0);
}

D 4
static int
E 4
I 4
static int					/* XXX should be void */
E 4
lfs_biocallback(bp)
	BUF *bp;
{
D 7
	LFS *fs;
E 7
I 7
	struct lfs *fs;
E 7
D 4
	SEGMENT *sp, *next_sp;
D 3
	UFSMOUNT *ump;
E 3
	VNODE *devvp;
E 4

E 9
I 2
	/*
D 3
	 * Grab the mount point for later (used to find the file system and
	 * block device) and, if the contents are valid, move the buffer back
	 * onto the clean list.
E 3
I 3
D 9
	 * XXX
	 * Reset the flags (probably wrong).  If the contents of the buffer
	 * are valid, move back onto the clean list.
E 9
I 9
	 * If the I/O count is non-zero, sleep until it reaches zero.  At the
	 * moment, the user's process hangs around so we can sleep.
E 9
E 3
	 */
I 56
	/* XXX ignore dirops for now
E 56
I 19
D 42
	s = splbio();
	--fs->lfs_iocount;
E 42
I 38
	fs->lfs_writer = 0;
	fs->lfs_doifile = 0;
	wakeup(&fs->lfs_dirops);
I 56
	*/
E 56

I 42
D 56
	s = splbio();
	--fs->lfs_iocount;
E 42
E 38
E 19
D 3
printf("lfs_biocallback: buffer %x\n", bp, bp->b_lblkno);
E 2
	ump = VFSTOUFS(bp->b_vp->v_mount);
E 3
I 3
D 9
	bp->b_flags &= ~(B_READ | B_DONE | B_ERROR | B_DELWRI);
	fs = VFSTOUFS(bp->b_vp->v_mount)->um_lfs;
E 3
I 2
	if (bp->b_flags & B_NOCACHE)
		bp->b_vp = NULL;
D 3
	else {
		bp->b_flags &= ~(B_READ | B_DONE | B_ERROR | B_DELWRI);
E 3
I 3
	else
E 3
		reassignbuf(bp, bp->b_vp);
D 3
	}
E 3
I 3
	brelse(bp);
E 9
I 9
	if (do_ckp) {
D 19
		s = splbio();
D 10
		if (--fs->lfs_iocount)
			(void)tsleep(&fs->lfs_iocount, PRIBIO + 1, "sync", 0);
E 10
I 10
D 14
		if (--fs->lfs_iocount &&
		    (error = tsleep(&fs->lfs_iocount, PRIBIO + 1, "sync", 0)))
E 14
I 14
D 17
		if (--fs->lfs_iocount && (error =
		    tsleep(&fs->lfs_iocount, PRIBIO + 1, "lfs sync", 0)))
E 17
I 17
		if (--fs->lfs_iocount &&
		    (error = tsleep((caddr_t)&fs->lfs_iocount, PRIBIO + 1,
		      "lfs sync", 0)))
E 19
I 19
		if (fs->lfs_iocount && (error =
D 21
		    tsleep(&fs->lfs_iocount, PRIBIO + 1, "lfs sync", 0)))
E 21
I 21
		    tsleep(&fs->lfs_iocount, PRIBIO + 1, "lfs sync", 0))) {
			free(sp->bpp, M_SEGMENT);
			free(sp, M_SEGMENT);
E 21
E 19
E 17
E 14
			return (error);
I 21
		}
E 21
E 10
		splx(s);
I 47
		fs->lfs_nactive = 0;
E 47
		lfs_writesuper(fs, sp);
D 19
	}
E 19
I 19
	} else 
		splx(s);
E 19
E 9
E 3

E 56
I 56
#ifdef DOSTATS
	++lfs_stats.nwrites;
	if (sp->seg_flags & SEGM_SYNC)
		++lfs_stats.nsync_writes;
	if (sp->seg_flags & SEGM_CKP)
		++lfs_stats.ncheckpoints;
#endif
E 56
I 39
	lfs_segunlock(fs);
D 56

E 39
I 5
D 9
#ifdef SEGWRITE
E 5
E 2
D 3
	fs = ump->um_lfs;
	devvp = ump->um_devvp;
D 2
							/* XXX splbio(); */
printf("lfs_biocallback: iocount: %d\n", fs->lfs_iocount);
	if (--fs->lfs_iocount) {
E 2
I 2
	brelse(bp);		/* move up... XXX */
E 3
I 3
printf("callback: buffer: %x iocount %d\n", bp, fs->lfs_iocount);
I 5
#endif
E 5
	if (fs->lfs_iocount == 0)
		panic("lfs_biocallback: zero iocount\n");
E 9
I 9
D 12
	(void)free(sp->bpp, M_SEGMENT);
	(void)free(sp, M_SEGMENT);
E 12
I 12
	free(sp->bpp, M_SEGMENT);
	free(sp, M_SEGMENT);
E 12
E 9
E 3

E 56
D 3
printf("\nlfs_biocallback: iocount %d\n", fs->lfs_iocount);
	if (fs->lfs_iocount == 0) {
		/* Wake up any other syncs waiting on this file system. */
		return;
	}
	--fs->lfs_iocount;
	if (fs->lfs_iocount == 0) {
printf("\nlfs_biocallback: doing summary write\n");
E 2
		/* Fire off summary writes */
		for (sp = fs->lfs_seglist; sp; sp = next_sp) {
			next_sp = sp->nextp;
D 2
			(*(devvp->v_op->vop_strategy))(*(sp->cbpp - 1));
printf("free: segsum %x bpp %x sp %x\n", sp->segsum, sp->bpp, sp);
			free(sp->segsum, M_SEGMENT);
E 2
I 2
#ifdef MOVETONEWBUF
			(*(sp->cbpp - 1))->b_dev = bp->b_dev;
#endif
			(devvp->v_op->vop_strategy)(*(sp->cbpp - 1));
E 2
			free(sp->bpp, M_SEGMENT);
			free(sp, M_SEGMENT);
		}
	}
E 3
I 3
D 9
	if (--fs->lfs_iocount == 0)
		wakeup(&fs->lfs_iocount);
E 9
I 9
D 18
	/* Wake up any cleaning processes waiting on this file system. */
D 17
	wakeup(&fs->lfs_nextseg);
	wakeup(&lfs_allclean_wakeup);
E 17
I 17
	wakeup((caddr_t)&fs->lfs_nextseg);
	wakeup((caddr_t)&lfs_allclean_wakeup);
E 17
I 10
D 14
printf("sync returned\n");
E 14
I 14

E 18
E 14
E 10
	return (0);
E 9
E 3
}

I 4
D 9
/* Finish up a summary block. */
E 9
I 9
/*
 * Write the dirty blocks associated with a vnode.
 */
E 9
E 4
D 2

E 2
D 13
static void
E 13
I 13
void
E 13
D 9
lfs_endsum(fs, sp, calc_next)
E 9
I 9
lfs_writefile(fs, sp, vp)
E 9
D 7
	LFS *fs;
E 7
I 7
	struct lfs *fs;
E 7
D 14
	SEGMENT *sp;
D 3
	int calc_next;		/* if 1, calculate next, else -1 */
E 3
I 3
D 4
	int calc_next;		/* If 1 calculate next, else set to -1. */
E 4
I 4
D 9
	int calc_next;
E 9
I 9
	VNODE *vp;
E 14
I 14
	struct segment *sp;
	struct vnode *vp;
E 14
E 9
E 4
E 3
{
D 4
	BUF *bp;
E 4
D 9
	SEGSUM *ssp;
D 4
	daddr_t next_addr;
D 2
	int npages, nseg_pages;
E 2
I 2
	int npages, nseg_pages, nsums_per_blk;
E 4
I 4
	int nsums_per_blk;
E 9
I 9
	struct buf *bp;
D 14
	FINFO *fip;
E 14
I 14
	struct finfo *fip;
E 14
	IFILE *ifp;
D 14
	ino_t inum;
E 14
E 9
E 4
E 2

D 2
printf("lfs_endsum\n");
E 2
I 2
D 3
/* printf("lfs_endsum\n");		/**/
E 3
D 9
	if (sp->sbp == NULL)
		return;
E 9
I 9
D 46
#ifdef VERBOSE
	printf("lfs_writefile\n");
#endif
E 46
D 14
	inum = VTOI(vp)->i_number;
	if (vp->v_dirtyblkhd != NULL) {
		if (sp->seg_bytes_left < fs->lfs_bsize ||
		    sp->sum_bytes_left < sizeof(FINFO)) {
			lfs_writeseg(fs, sp);
D 10
			lfs_newseg(fs, sp);
E 10
I 10
			lfs_initseg(fs, sp);
E 10
		}
		sp->sum_bytes_left -= sizeof(FINFO) - sizeof(daddr_t);
E 14
I 14
	if (sp->seg_bytes_left < fs->lfs_bsize ||
D 56
	    sp->sum_bytes_left < sizeof(struct finfo)) {
E 56
I 56
	    sp->sum_bytes_left < sizeof(struct finfo))
E 56
D 38
		lfs_writeseg(fs, sp);
E 38
I 38
		(void) lfs_writeseg(fs, sp);
E 38
D 56
		lfs_initseg(fs, sp);
	}
E 56
I 56

E 56
D 63
	sp->sum_bytes_left -= sizeof(struct finfo) - sizeof(daddr_t);
E 63
I 63
	sp->sum_bytes_left -= sizeof(struct finfo) - sizeof(ufs_daddr_t);
E 63
I 54
	++((SEGSUM *)(sp->segsum))->ss_nfinfo;
E 54
E 14
E 9

E 2
D 9
	ssp = sp->segsum;
E 9
I 9
D 14
		fip = sp->fip;
		fip->fi_nblocks = 0;
		if (inum == LFS_IFILE_INUM)
			fip->fi_version = 1;
		else {
			LFS_IENTRY(ifp, fs, inum, bp);
			fip->fi_version = ifp->if_version;
D 13
			brelse(bp);
E 13
I 13
			LFS_IRELEASE(fs, bp);
E 13
		}
		fip->fi_ino = inum;
E 14
I 14
	fip = sp->fip;
	fip->fi_nblocks = 0;
	fip->fi_ino = VTOI(vp)->i_number;
	LFS_IENTRY(ifp, fs, fip->fi_ino, bp);
	fip->fi_version = ifp->if_version;
	brelse(bp);
E 14
E 9
D 3
	if (!calc_next)
		ssp->ss_nextsum = (daddr_t) -1;
I 2
	else
		ssp->ss_nextsum = sp->sum_addr - LFS_SUMMARY_SIZE / DEV_BSIZE;
E 3
I 3
D 4
	ssp->ss_nextsum = calc_next ?
	    sp->sum_addr - LFS_SUMMARY_SIZE / DEV_BSIZE : (daddr_t)-1;
E 4
E 3
E 2

D 2
	nseg_pages = sp->sum_num / (fs->lfs_bsize / LFS_SUMMARY_SIZE);
	if ((sp->sum_num % (fs->lfs_bsize / LFS_SUMMARY_SIZE)) == 0) {
E 2
I 2
D 3
	if ((sp->sum_num % (fs->lfs_bsize / LFS_SUMMARY_SIZE)) == (nsums_per_blk - 1)) {
E 3
I 3
D 9
	/*
D 4
	 * XXX
	 * I don't understand how sum_num works; the 0 base seems wrong.
E 4
I 4
	 * Compute the address of the next summary block if calc_next is set,
	 * otherwise end the chain.  If the summary block is full, close it
	 * by setting sp->sbp to NULL, so lfs_newsum will allocate a new one.
	 * Calculate the checksum last.
E 4
	 */
	nsums_per_blk = fs->lfs_bsize / LFS_SUMMARY_SIZE;
D 4
	if ((sp->sum_num % (fs->lfs_bsize / LFS_SUMMARY_SIZE)) ==
	    (nsums_per_blk - 1)) {
E 3
E 2
		/*
D 2
		 * May need to change the nextsum field on the previous
		 * summary header in which case we need to recompute the
		 * checksum as well.
E 2
I 2
D 3
		 * This buffer is now full.  Compute the next address if appropriate
		 * and the checksum, and close the buffer by setting sp->sbp NULL.
E 3
I 3
		 * This buffer is now full.  Compute the next address if
		 * appropriate and the checksum, and close the buffer by
		 * setting sp->sbp NULL.
E 3
E 2
		 */
D 2
		npages = nseg_pages + (sp->ninodes + INOPB(fs) - 1) / INOPB(fs);
		next_addr = fs->lfs_sboffs[0] + 
		    (sp->seg_number + 1) * fsbtodb(fs, fs->lfs_ssize)
		    - fsbtodb(fs, npages) - LFS_SUMMARY_SIZE / DEV_BSIZE;
		if (calc_next)
E 2
I 2
		if (calc_next) {
			nsums_per_blk = fs->lfs_bsize / LFS_SUMMARY_SIZE;
			nseg_pages = 1 + sp->sum_num / nsums_per_blk;
D 3
			npages = nseg_pages + (sp->ninodes + INOPB(fs) - 1) / INOPB(fs);
			next_addr = fs->lfs_sboffs[0] + 
			    (sp->seg_number + 1) * fsbtodb(fs, fs->lfs_ssize)
			    - fsbtodb(fs, (npages - 1)) - LFS_SUMMARY_SIZE / DEV_BSIZE;
E 3
I 3
			npages = nseg_pages +
			    (sp->ninodes + INOPB(fs) - 1) / INOPB(fs);
			next_addr = fs->lfs_sboffs[0] + (sp->seg_number + 1) *
			    fsbtodb(fs, fs->lfs_ssize) -
			    fsbtodb(fs, (npages - 1)) -
			    LFS_SUMMARY_SIZE / DEV_BSIZE;
E 3
E 2
			ssp->ss_nextsum = next_addr;
D 2
		ssp->ss_cksum = cksum(&ssp->ss_cksum, 
		    LFS_SUMMARY_SIZE - sizeof(ssp->ss_cksum));
		bp = lfs_newbuf(fs, sp->sum_addr, fs->lfs_bsize);
		bcopy(sp->segsum, bp->b_un.b_words, fs->lfs_bsize);
		bp->b_flags |= B_BUSY;
		if (nseg_pages != 1) {
			bp->b_flags |= B_CALL;
			bp->b_iodone = lfs_biocallback;
E 2
		}
D 2
		brelse(bp);
		sp->bpp[fs->lfs_ssize - npages] = bp;
		sp->segsum = (SEGSUM *)(sp->segsum + fs->lfs_bsize - 
		    LFS_SUMMARY_SIZE);
		sp->sum_addr = next_addr;
	} else {
		sp->sum_addr -= LFS_SUMMARY_SIZE / DEV_BSIZE;
		ssp->ss_nextsum = sp->sum_addr;
E 2
I 2
D 3
		ssp->ss_cksum = cksum(&ssp->ss_cksum, LFS_SUMMARY_SIZE - sizeof(ssp->ss_cksum));
E 3
I 3
		ssp->ss_cksum = cksum(&ssp->ss_cksum,
		    LFS_SUMMARY_SIZE - sizeof(ssp->ss_cksum));
E 4
I 4
	if (sp->nsums % nsums_per_blk == 0) {
		ssp->ss_nextsum =
		    calc_next ? next(fs, sp, NULL) +
		    (nsums_per_blk - 1) * LFS_SUMMARY_SIZE / DEV_BSIZE :
		    (daddr_t)-1;
E 4
E 3
		sp->sbp = NULL;
	} else
E 2
D 4
		/* Calculate cksum on previous segment summary */
		ssp->ss_cksum = cksum(&ssp->ss_cksum, 
		    LFS_SUMMARY_SIZE - sizeof(ssp->ss_cksum));
E 4
I 4
		ssp->ss_nextsum = calc_next ?
		    sp->sum_addr - LFS_SUMMARY_SIZE / DEV_BSIZE : (daddr_t)-1;
E 9
I 9
D 14
		/*
		 * It may not be necessary to write the meta-data blocks
		 * at this point, as the roll-forward recovery code should
		 * be able to reconstruct the list.
		 */
D 13
		lfs_gather(fs, sp, vp, match_data);
		lfs_gather(fs, sp, vp, match_indir);
		lfs_gather(fs, sp, vp, match_dindir);
E 13
I 13
		lfs_gather(fs, sp, vp, lfs_match_data);
		lfs_gather(fs, sp, vp, lfs_match_indir);
		lfs_gather(fs, sp, vp, lfs_match_dindir);
E 14
I 14
	/*
	 * It may not be necessary to write the meta-data blocks at this point,
	 * as the roll-forward recovery code should be able to reconstruct the
	 * list.
	 */
	lfs_gather(fs, sp, vp, lfs_match_data);
	lfs_gather(fs, sp, vp, lfs_match_indir);
	lfs_gather(fs, sp, vp, lfs_match_dindir);
E 14
E 13
#ifdef TRIPLE
D 13
		lfs_gather(fs, sp, vp, match_tindir);
E 13
I 13
D 14
		lfs_gather(fs, sp, vp, lfs_match_tindir);
E 14
I 14
	lfs_gather(fs, sp, vp, lfs_match_tindir);
E 14
E 13
#endif
E 9

D 9
	ssp->ss_cksum =
	    cksum(&ssp->ss_cksum, LFS_SUMMARY_SIZE - sizeof(ssp->ss_cksum));
E 9
I 9
D 14
		fip = sp->fip;
E 14
I 14
	fip = sp->fip;
E 14
D 56
#ifdef META
D 14
		printf("lfs_writefile: adding %d blocks\n", fip->fi_nblocks);
E 14
I 14
	printf("lfs_writefile: adding %d blocks\n", fip->fi_nblocks);
E 14
#endif
E 56
D 14
		if (fip->fi_nblocks != 0) {
			++((SEGSUM *)(sp->segsum))->ss_nfinfo;
			sp->fip = (FINFO *)((caddr_t)fip + sizeof(FINFO) +
			    sizeof(daddr_t) * (fip->fi_nblocks - 1));
		}
E 14
I 14
	if (fip->fi_nblocks != 0) {
D 54
		++((SEGSUM *)(sp->segsum))->ss_nfinfo;
E 54
		sp->fip =
		    (struct finfo *)((caddr_t)fip + sizeof(struct finfo) +
D 63
		    sizeof(daddr_t) * (fip->fi_nblocks - 1));
E 63
I 63
		    sizeof(ufs_daddr_t) * (fip->fi_nblocks - 1));
E 63
I 47
		sp->start_lbp = &sp->fip->fi_blocks[0];
E 47
E 14
D 18
	}
E 18
I 18
D 54
	} else
E 54
I 54
	} else {
E 54
D 63
		sp->sum_bytes_left += sizeof(struct finfo) - sizeof(daddr_t);
E 63
I 63
		sp->sum_bytes_left += sizeof(struct finfo) - sizeof(ufs_daddr_t);
E 63
I 54
		--((SEGSUM *)(sp->segsum))->ss_nfinfo;
	}
E 54
E 18
D 10
	/* If this isn't the ifile, update the inode. */
	if (inum != LFS_IFILE_INUM)
		lfs_writeinode(fs, sp, VTOI(vp));
E 10
E 9
E 4
D 2
		sp->segsum -= LFS_SUMMARY_SIZE;
E 2
I 2
}

D 9
static SEGMENT *
E 9
I 9
D 13
static void
E 13
I 13
D 38
void
E 38
I 38
int
E 38
E 13
I 10
lfs_writeinode(fs, sp, ip)
	struct lfs *fs;
D 14
	SEGMENT *sp;
	INODE *ip;
E 14
I 14
	struct segment *sp;
	struct inode *ip;
E 14
{
D 13
	BUF *bp;
E 13
I 13
D 14
	BUF *bp, *ibp;
E 14
I 14
	struct buf *bp, *ibp;
E 14
	IFILE *ifp;
E 13
D 18
	daddr_t next_addr;
E 18
I 18
	SEGUSE *sup;
D 63
	daddr_t daddr;
E 63
I 63
	ufs_daddr_t daddr;
E 63
E 18
I 13
	ino_t ino;
E 13
D 47
	int ndx;
E 47
I 47
D 56
	int error, ndx;
E 56
I 56
	int error, i, ndx;
E 56
E 47
I 38
	int redo_ifile = 0;
E 38

I 47
D 58
	if (!(ip->i_flag & (IMOD | IACC | IUPD | ICHG)))
E 58
I 58
D 59
	if (!(ip->i_flag & (IMODIFIED | IACCESS | IUPDATE | ICHANGE)))
E 59
I 59
	if (!(ip->i_flag & (IN_ACCESS | IN_CHANGE | IN_MODIFIED | IN_UPDATE)))
E 59
E 58
D 53
		return;
E 53
I 53
		return(0);
E 53

E 47
D 46
#ifdef VERBOSE
	printf("lfs_writeinode\n");
#endif
E 46
	/* Allocate a new inode block if necessary. */
	if (sp->ibp == NULL) {
		/* Allocate a new segment if necessary. */
		if (sp->seg_bytes_left < fs->lfs_bsize ||
D 56
		    sp->sum_bytes_left < sizeof(daddr_t)) {
E 56
I 56
D 63
		    sp->sum_bytes_left < sizeof(daddr_t))
E 63
I 63
		    sp->sum_bytes_left < sizeof(ufs_daddr_t))
E 63
E 56
D 38
			lfs_writeseg(fs, sp);
E 38
I 38
			(void) lfs_writeseg(fs, sp);
E 38
D 56
			lfs_initseg(fs, sp);
		}
E 56

		/* Get next inode block. */
D 18
		next_addr = fs->lfs_offset;
E 18
I 18
		daddr = fs->lfs_offset;
E 18
		fs->lfs_offset += fsbtodb(fs, 1);
		sp->ibp = *sp->cbpp++ =
D 18
		    lfs_newbuf(fs, sp, next_addr, fs->lfs_bsize);
E 18
I 18
D 19
		    lfs_newbuf(fs, sp, daddr, fs->lfs_bsize);
E 19
I 19
D 47
		    lfs_newbuf(fs, daddr, fs->lfs_bsize);
E 19
E 18

E 47
I 47
D 49
		    lfs_newbuf(fs->lfs_ivnode, daddr, fs->lfs_bsize);
E 49
I 49
		    lfs_newbuf(VTOI(fs->lfs_ivnode)->i_devvp, daddr,
		    fs->lfs_bsize);
I 56
		/* Zero out inode numbers */
		for (i = 0; i < INOPB(fs); ++i)
D 58
			sp->ibp->b_un.b_dino[i].di_inumber = 0;
E 58
I 58
			((struct dinode *)sp->ibp->b_data)[i].di_inumber = 0;
E 58
E 56
E 49
		++sp->start_bpp;
		fs->lfs_avail -= fsbtodb(fs, 1);
E 47
D 19
		/* Set remaining space counter. */
E 19
I 19
		/* Set remaining space counters. */
E 19
		sp->seg_bytes_left -= fs->lfs_bsize;
D 63
		sp->sum_bytes_left -= sizeof(daddr_t);
D 13
		ndx = LFS_SUMMARY_SIZE / sizeof(daddr_t) - 
E 13
I 13
		ndx = LFS_SUMMARY_SIZE / sizeof(daddr_t) -
E 63
I 63
		sp->sum_bytes_left -= sizeof(ufs_daddr_t);
		ndx = LFS_SUMMARY_SIZE / sizeof(ufs_daddr_t) -
E 63
E 13
		    sp->ninodes / INOPB(fs) - 1;
D 18
		((daddr_t *)(sp->segsum))[ndx] = next_addr;
E 18
I 18
D 63
		((daddr_t *)(sp->segsum))[ndx] = daddr;
E 63
I 63
		((ufs_daddr_t *)(sp->segsum))[ndx] = daddr;
E 63
E 18
	}

D 13
	/* Copy the new inode onto the inode page.
E 13
I 13
D 14
	/*
	 * Update the inode times and copy the inode onto the inode page.
	 *
E 13
	 * XXX
	 * Do struct assignment.
	 */
E 14
I 14
	/* Update the inode times and copy the inode onto the inode page. */
I 49
D 58
	if (ip->i_flag & IMOD)
E 58
I 58
D 59
	if (ip->i_flag & IMODIFIED)
E 59
I 59
	if (ip->i_flag & IN_MODIFIED)
E 59
E 58
		--fs->lfs_uinodes;
E 49
E 14
I 13
	ITIMES(ip, &time, &time);
I 47
D 58
	ip->i_flag &= ~(IMOD | IACC | IUPD | ICHG);
E 58
I 58
D 59
	ip->i_flag &= ~(IMODIFIED | IACCESS | IUPDATE | ICHANGE);
E 59
I 59
	ip->i_flag &= ~(IN_ACCESS | IN_CHANGE | IN_MODIFIED | IN_UPDATE);
E 59
E 58
D 49
	--fs->lfs_uinodes;
E 49
E 47
E 13
	bp = sp->ibp;
D 14
	bcopy(&ip->i_din,
	    bp->b_un.b_dino + (sp->ninodes % INOPB(fs)), sizeof(DINODE));
E 14
I 14
D 58
	bp->b_un.b_dino[sp->ninodes % INOPB(fs)] = ip->i_din;
E 58
I 58
	((struct dinode *)bp->b_data)[sp->ninodes % INOPB(fs)] = ip->i_din;
E 58
E 14
D 47

E 47
	/* Increment inode count in segment summary block. */
	++((SEGSUM *)(sp->segsum))->ss_ninos;

	/* If this page is full, set flag to allocate a new page. */
	if (++sp->ninodes % INOPB(fs) == 0)
		sp->ibp = NULL;

	/*
D 13
	 * If updating the ifile, update the super-block; otherwise, update
	 * the ifile itself.  In either case, turn off inode update flags.
E 13
I 13
	 * If updating the ifile, update the super-block.  Update the disk
	 * address and access times for this inode in the ifile.
D 14
	 *
	 * XXX
	 * The access time in the ifile is currently unused.
E 14
E 13
	 */
D 13
	if (ip->i_number == LFS_IFILE_INUM)
E 13
I 13
	ino = ip->i_number;
D 44
	if (ino == LFS_IFILE_INUM)
E 44
I 44
	if (ino == LFS_IFILE_INUM) {
		daddr = fs->lfs_idaddr;
E 44
E 13
		fs->lfs_idaddr = bp->b_blkno;
I 44
	} else {
		LFS_IENTRY(ifp, fs, ino, ibp);
		daddr = ifp->if_daddr;
		ifp->if_daddr = bp->b_blkno;
D 47
		LFS_UBWRITE(ibp);
E 47
I 47
		error = VOP_BWRITE(ibp);
E 47
	}
E 44
D 13
	else
		lfs_iset(ip, bp->b_blkno, ip->i_atime);
	ip->i_flags &= ~(IMOD | IACC | IUPD | ICHG);
E 13
I 13

D 44
	LFS_IENTRY(ifp, fs, ino, ibp);
I 18
	daddr = ifp->if_daddr;
E 18
	ifp->if_daddr = bp->b_blkno;
D 14
	ifp->if_st_atime = ip->i_atime;
	LFS_IWRITE(fs, ibp);
E 14
I 14
	LFS_UBWRITE(ibp);
I 38
	redo_ifile = (ino == LFS_IFILE_INUM && !(ibp->b_flags & B_GATHERED));
E 38
I 18

E 44
D 38
	if (daddr != LFS_UNUSED_DADDR) {
E 38
I 38
	/*
	 * No need to update segment usage if there was no former inode address
	 * or if the last inode address is in the current partial segment.
	 */
	if (daddr != LFS_UNUSED_DADDR && 
D 45
	    !(daddr >= fs->lfs_curseg && daddr <= ifp->if_daddr) ) {
E 45
I 45
	    !(daddr >= fs->lfs_lastpseg && daddr <= bp->b_blkno)) {
E 45
E 38
		LFS_SEGENTRY(sup, fs, datosn(fs, daddr), bp);
#ifdef DIAGNOSTIC
D 38
		if (sup->su_nbytes < sizeof(struct dinode))
E 38
I 38
		if (sup->su_nbytes < sizeof(struct dinode)) {
E 38
D 20
			panic("lfs: negative bytes (segment %d)\n",
E 20
I 20
			/* XXX -- Change to a panic. */
			printf("lfs: negative bytes (segment %d)\n",
E 20
			    datosn(fs, daddr));
I 38
			panic("negative bytes");
		}
E 38
#endif
		sup->su_nbytes -= sizeof(struct dinode);
I 50
		redo_ifile =
		    (ino == LFS_IFILE_INUM && !(bp->b_flags & B_GATHERED));
E 50
D 47
		LFS_UBWRITE(bp);
E 47
I 47
		error = VOP_BWRITE(bp);
E 47
I 38
D 44
		redo_ifile |= 
		    (ino == LFS_IFILE_INUM && !(bp->b_flags & B_GATHERED));
E 44
I 44
D 50
		redo_ifile = (ino == LFS_IFILE_INUM && !(bp->b_flags & B_GATHERED));
E 50
E 44
E 38
	}
I 38
D 42
	return(redo_ifile);
E 42
I 42
	return (redo_ifile);
E 42
E 38
E 18
E 14
E 13
}

I 47
int
lfs_gatherblock(sp, bp, sptr)
	struct segment *sp;
	struct buf *bp;
	int *sptr;
{
	struct lfs *fs;
	int version;

	/*
	 * If full, finish this segment.  We may be doing I/O, so
	 * release and reacquire the splbio().
	 */
I 48
#ifdef DIAGNOSTIC
	if (sp->vp == NULL)
		panic ("lfs_gatherblock: Null vp in segment");
#endif
E 48
	fs = sp->fs;
D 63
	if (sp->sum_bytes_left < sizeof(daddr_t) ||
E 63
I 63
	if (sp->sum_bytes_left < sizeof(ufs_daddr_t) ||
E 63
D 64
	    sp->seg_bytes_left < fs->lfs_bsize) {
E 64
I 64
	    sp->seg_bytes_left < bp->b_bcount) {
E 64
		if (sptr)
			splx(*sptr);
D 48
		lfs_updatemeta(sp, bp->b_vp);
E 48
I 48
		lfs_updatemeta(sp);
E 48

D 54
		/* Add the current file to the segment summary. */
		++((SEGSUM *)(sp->segsum))->ss_nfinfo;

E 54
		version = sp->fip->fi_version;
		(void) lfs_writeseg(fs, sp);
D 56
		lfs_initseg(fs, sp);
E 56

		sp->fip->fi_version = version;
D 48
		sp->fip->fi_ino = VTOI(bp->b_vp)->i_number;
E 48
I 48
		sp->fip->fi_ino = VTOI(sp->vp)->i_number;
E 48
D 54

E 54
I 54
		/* Add the current file to the segment summary. */
		++((SEGSUM *)(sp->segsum))->ss_nfinfo;
E 54
		sp->sum_bytes_left -= 
D 63
		    sizeof(struct finfo) - sizeof(daddr_t);
E 63
I 63
		    sizeof(struct finfo) - sizeof(ufs_daddr_t);
E 63

		if (sptr)
			*sptr = splbio();
		return(1);
	}

	/* Insert into the buffer list, update the FINFO block. */
I 49
D 53
if (bp->b_vp == sp->fs->lfs_ivnode &&
((bp->b_lblkno == 0 && (bp->b_un.b_daddr[0] > 26 || bp->b_un.b_daddr[1] > 26)) ||
(bp->b_lblkno > 2)))
	printf ("Bad ifile block\n");
E 53
E 49
	bp->b_flags |= B_GATHERED;
	*sp->cbpp++ = bp;
	sp->fip->fi_blocks[sp->fip->fi_nblocks++] = bp->b_lblkno;

D 63
	sp->sum_bytes_left -= sizeof(daddr_t);
E 63
I 63
	sp->sum_bytes_left -= sizeof(ufs_daddr_t);
E 63
D 56
	sp->seg_bytes_left -= bp->b_bufsize;
E 56
I 56
D 64
	sp->seg_bytes_left -= fs->lfs_bsize;
E 64
I 64
	sp->seg_bytes_left -= bp->b_bcount;
E 64
E 56
	return(0);
}

E 47
D 13
static void
E 13
I 13
void
E 13
E 10
E 9
lfs_gather(fs, sp, vp, match)
D 7
	LFS *fs;
E 7
I 7
	struct lfs *fs;
E 7
D 14
	SEGMENT *sp;
	VNODE *vp;
D 9
	int (*match) __P((BUF *));
E 9
I 9
	int (*match) __P((struct lfs *, BUF *));
E 14
I 14
	struct segment *sp;
	struct vnode *vp;
	int (*match) __P((struct lfs *, struct buf *));
E 14
E 9
{
D 14
	BUF **bpp, *bp, *nbp;
	FINFO *fip;
	INODE *ip;
E 14
I 14
D 38
	struct buf **bpp, *bp, *nbp;
E 38
I 38
D 47
	struct buf **bpp, *bp;
struct buf *lastbp;
E 38
	struct finfo *fip;
	struct inode *ip;
E 14
D 4
	int count, s, version;
E 4
	daddr_t *lbp, *start_lbp;
I 4
	u_long version;
E 47
I 47
	struct buf *bp;
E 47
	int s;
E 4

I 48
	sp->vp = vp;
E 48
I 9
D 46
#ifdef VERBOSE
	printf("lfs_gather\n");
#endif
E 46
E 9
D 47
	ip = VTOI(vp);
	bpp = sp->cbpp;
	fip = sp->fip;
D 4
	version = fip->fi_version;
E 4
	start_lbp = lbp = &fip->fi_blocks[fip->fi_nblocks];
D 4
	count = 0;
E 4

D 22
	s = splbio();
E 22
I 22
loop:	s = splbio();
E 22
D 38
	for (bp = vp->v_dirtyblkhd; bp; bp = nbp) {
		nbp = bp->b_blockf;
I 10
		/*
		 * XXX
D 18
		 * Should probably sleep on any BUSY buffer if
		 * doing an fsync?
E 18
I 18
		 * Should sleep on any BUSY buffer if doing an fsync?
E 18
		 */
E 10
D 4
		if ((bp->b_flags & B_BUSY))
E 4
I 4
D 16
		if (bp->b_flags & B_BUSY)
E 16
I 16
		if (bp->b_flags & B_BUSY || !match(fs, bp))
E 38
I 38
	lastbp = NULL;
	for (bp = vp->v_dirtyblkhd; bp; lastbp = bp, bp = bp->b_blockf) {
E 47
I 47
	s = splbio();
D 54
loop:	for (bp = vp->v_dirtyblkhd; bp; bp = bp->b_blockf) {
E 54
I 54
D 60
loop:	for (bp = vp->v_dirtyblkhd.le_next; bp; bp = bp->b_vnbufs.qe_next) {
E 60
I 60
D 64
loop:	for (bp = vp->v_dirtyblkhd.lh_first; bp; bp = bp->b_vnbufs.le_next) {
E 64
I 64
/* This is a hack to see if ordering the blocks in LFS makes a difference. */
/* BEGIN HACK */
#define	BUF_OFFSET	(((void *)&bp->b_vnbufs.le_next) - (void *)bp)
#define	BACK_BUF(BP)	((struct buf *)(((void *)BP->b_vnbufs.le_prev) - BUF_OFFSET))
#define	BEG_OF_LIST	((struct buf *)(((void *)&vp->v_dirtyblkhd.lh_first) - BUF_OFFSET))


/*loop:	for (bp = vp->v_dirtyblkhd.lh_first; bp; bp = bp->b_vnbufs.le_next) {*/
/* Find last buffer. */
loop:   for (bp = vp->v_dirtyblkhd.lh_first; bp && bp->b_vnbufs.le_next != NULL;
	    bp = bp->b_vnbufs.le_next);
	for (; bp && bp != BEG_OF_LIST; bp = BACK_BUF(bp)) {
/* END HACK */
E 64
E 60
E 54
E 47
		if (bp->b_flags & B_BUSY || !match(fs, bp) ||
		    bp->b_flags & B_GATHERED)
E 38
E 16
E 4
			continue;
I 16
D 18

E 18
E 16
I 4
#ifdef DIAGNOSTIC
E 4
D 9
		if ((bp->b_flags & B_DELWRI) == 0)
D 4
			panic("lfs_write: not dirty");
E 4
I 4
			panic("lfs_gather: not dirty");
E 9
I 9
		if (!(bp->b_flags & B_DELWRI))
D 10
			panic("lfs_gather: buffer not B_DELWRI");
E 10
I 10
			panic("lfs_gather: bp not B_DELWRI");
E 10
		if (!(bp->b_flags & B_LOCKED))
D 10
			panic("lfs_gather: buffer not B_LOCKED");
E 10
I 10
			panic("lfs_gather: bp not B_LOCKED");
E 10
E 9
#endif
E 4
D 9
		if (!match(bp))
E 9
I 9
D 16
		if (!match(fs, bp))
E 9
			continue;
I 4

E 16
D 9
		/* Remove the buffer from the free lists, prepare it for I/O. */
E 4
		bremfree(bp);
		bp->b_flags |= B_BUSY | B_CALL;
D 3
		bp->b_dev = VTOI(fs->lfs_ivnode)->i_dev;
E 3
		bp->b_iodone = lfs_biocallback;
I 3
		bp->b_dev = VTOI(fs->lfs_ivnode)->i_dev;
E 3

E 9
D 4
		*lbp++ = bp->b_lblkno;
E 4
I 4
D 18
		/* Insert into the buffer list, update the FINFO block. */
E 4
		*sp->cbpp++ = bp;
D 4
		fip->fi_nblocks++;
E 4
I 4
		++fip->fi_nblocks;
		*lbp++ = bp->b_lblkno;

E 18
E 4
D 9
		sp->sum_bytes_left -= sizeof(daddr_t);
		sp->seg_bytes_left -= bp->b_bufsize;
D 4
		if (sp->sum_bytes_left < sizeof(daddr_t) || 
E 4
I 4

E 9
D 47
		/*
D 9
		 * Allocate a new summary block (and, possibly, a new segment)
		 * if necessary.  In this case we sort the blocks we've done
		 * so far and assign disk addresses so we can start the new
		 * block correctly.  We may be doing I/O, so we need to release
		 * the splbio() before anything else.
E 9
I 9
		 * If full, finish this segment.  We may be doing I/O, so
		 * release and reacquire the splbio().
E 9
		 */
I 9
D 18
		sp->sum_bytes_left -= sizeof(daddr_t);
		sp->seg_bytes_left -= bp->b_bufsize;
E 18
E 9
		if (sp->sum_bytes_left < sizeof(daddr_t) ||
E 4
		    sp->seg_bytes_left < fs->lfs_bsize) {
D 4
			/*
			 * We are about to allocate a new summary block
			 * and possibly a new segment.  So, we need to
			 * sort the blocks we've done so far, and assign
			 * the disk addresses, so we can start a new block
			 * correctly.  We may be doing I/O so we need to
			 * release the s lock before doing anything.
			 */
E 4
			splx(s);
D 4
			lfs_updatemeta(fs, sp, ip, start_lbp, bpp,
			    lbp - start_lbp);
E 4
I 4
			lfs_updatemeta(fs,
D 9
			    sp, ip, start_lbp, bpp, lbp - start_lbp);
E 9
I 9
			    sp, vp, start_lbp, bpp, lbp - start_lbp);
E 9
E 4

D 4
			/* Put this file in the segment summary */
			((SEGSUM *)(sp->segsum))->ss_nfinfo++;
E 4
I 4
			/* Add the current file to the segment summary. */
			++((SEGSUM *)(sp->segsum))->ss_nfinfo;
E 4

I 4
			version = fip->fi_version;
E 4
D 9
			if (sp->seg_bytes_left < fs->lfs_bsize) {
				lfs_writeseg(fs, sp);
				sp = lfs_newseg(fs);
			} else if (sp->sum_bytes_left < sizeof(daddr_t))
D 4
				lfs_newsum(fs, sp);
E 4
I 4
				sp = lfs_newsum(fs, sp);
E 9
I 9
D 38
			lfs_writeseg(fs, sp);
E 38
I 38
			(void) lfs_writeseg(fs, sp);
E 38
D 10
			lfs_newseg(fs, sp);
E 10
I 10
			lfs_initseg(fs, sp);
E 10
E 9

D 9
			/* A new FINFO either way. */
E 9
E 4
			fip = sp->fip;
D 4
			fip->fi_ino = ip->i_number;
E 4
			fip->fi_version = version;
D 4
			bpp = sp->cbpp;
D 3
			/* You know that you have a new FINFO either way */
E 3
I 3
			/* You know that you have a new FINFO either way. */
E 4
I 4
			fip->fi_ino = ip->i_number;
E 4
E 3
			start_lbp = lbp = fip->fi_blocks;
I 4

I 18
			sp->sum_bytes_left -= 
			    sizeof(struct finfo) - sizeof(daddr_t);

E 18
			bpp = sp->cbpp;
E 47
I 47
		if (lfs_gatherblock(sp, bp, &s))
E 47
E 4
D 22
			s = splbio();
E 22
I 22
			goto loop;
E 22
D 47
		}
I 18

		/* Insert into the buffer list, update the FINFO block. */
I 38
		bp->b_flags |= B_GATHERED;
E 38
		*sp->cbpp++ = bp;
		++fip->fi_nblocks;
		*lbp++ = bp->b_lblkno;

		sp->sum_bytes_left -= sizeof(daddr_t);
		sp->seg_bytes_left -= bp->b_bufsize;
E 47
E 18
E 2
	}
I 2
	splx(s);
D 9
	lfs_updatemeta(fs, sp, ip, start_lbp, bpp, lbp - start_lbp);
D 3

E 3
D 4
	return(sp);
E 4
I 4
	return (sp);
E 9
I 9
D 47
	lfs_updatemeta(fs, sp, vp, start_lbp, bpp, lbp - start_lbp);
E 47
I 47
D 48
	lfs_updatemeta(sp, vp);
E 48
I 48
	lfs_updatemeta(sp);
	sp->vp = NULL;
E 48
E 47
E 9
E 4
E 2
}

I 47

E 47
I 4
/*
D 9
 * Allocate a new buffer header.
 */
E 4
I 2
D 3

E 3
E 2
static BUF *
lfs_newbuf(fs, daddr, size)
D 7
	LFS *fs;
E 7
I 7
	struct lfs *fs;
E 7
	daddr_t daddr;
	size_t size;
{
	BUF *bp;
D 3
	VNODE *devvp;
E 3

D 2
printf("lfs_newbuf\n");
E 2
	bp = getnewbuf();
	bremhash(bp);
D 3

	/*
	 * XXX
	 * Need a devvp, but this isn't a particularly clean way to get one.
I 2
	 * devvp = VTOI(fs->lfs_ivnode)->i_devvp;
E 2
	 */
D 2
	devvp = VTOI(fs->lfs_ivnode)->i_devvp;
E 2
I 2
#ifdef NOTWORKING
	devvp = VFSTOUFS(fs->lfs_ivnode->v_mount)->um_devvp;
E 2
	bgetvp(devvp, bp);
I 2
#endif
E 3
	bp->b_vp = fs->lfs_ivnode;
D 3
	bp->b_dev = VTOI(fs->lfs_ivnode)->i_dev;
E 3
E 2
	bp->b_bcount = 0;
D 2
	bp->b_lblkno = daddr;
	bp->b_blkno = daddr;
E 2
I 2
	bp->b_blkno = bp->b_lblkno = daddr;
E 2
	bp->b_error = 0;
	bp->b_resid = 0;
I 2
D 3
	bp->b_flags |= B_CALL | B_DELWRI | B_NOCACHE | B_WRITE;
E 3
I 3
	bp->b_flags |= B_DELWRI | B_NOCACHE;
E 3
	bp->b_iodone = lfs_biocallback;
D 3
#ifdef PROBABLYWRONG
E 2
	binshash(bp, BUFHASH(devvp, daddr));
I 2
#endif
E 3
I 3
	bp->b_dev = VTOI(fs->lfs_ivnode)->i_dev;
E 3
E 2
	allocbuf(bp, size);
I 2
D 3
#ifdef PROBABLYWRONG
	reassignbuf(bp, devvp);
#endif
E 3
E 2
	return (bp);
}

D 3

/*
 * Start a new segment
 */
E 3
I 3
D 4
/* Start a new segment. */
E 4
I 4
/*
E 9
D 10
 * Start a new segment.
 */
E 4
E 3
D 9
static SEGMENT *
lfs_newseg(fs)
E 9
I 9
static void
lfs_newseg(fs, sp)
E 9
D 7
	LFS *fs;
E 7
I 7
	struct lfs *fs;
I 9
	SEGMENT *sp;
E 9
E 7
{
I 4
	FINFO *fip;
E 4
D 9
	SEGMENT *sp;
E 9
	SEGUSE *sup;
I 4
	SEGSUM *ssp;
I 9
	struct buf *bp;
E 9
	daddr_t lbn, *lbnp;
I 9
	int nblocks;
E 9
E 4

D 3
printf("lfs_newseg\n");
	/* Get buffer space to write out a segment */
E 3
I 3
D 5
printf("lfs_newseg: new segment %x\n", fs->lfs_nextseg);

E 5
E 3
D 9
	sp = malloc(sizeof(SEGMENT), M_SEGMENT, M_WAITOK);
I 2
D 3
	sp->ibp = NULL;
	sp->sbp = NULL;
E 3
I 3
	sp->nextp = NULL;
E 3
E 2
	sp->cbpp = sp->bpp =
	    malloc(fs->lfs_ssize * sizeof(BUF *), M_SEGMENT, M_WAITOK);
D 3
	sp->nextp = NULL;
E 3
I 3
	sp->ibp = sp->sbp = NULL;
E 3
D 4
	sp->sum_bytes_left = LFS_SUMMARY_SIZE;
	sp->seg_bytes_left = (fs->lfs_segmask + 1) - LFS_SUMMARY_SIZE;
E 4
I 4
	sp->seg_bytes_left = (fs->lfs_segmask + 1);
E 4
	sp->saddr = fs->lfs_nextseg;
I 2
D 3
printf("lfs_newseg: About to write segment %lx\n", sp->saddr);
E 3
E 2
	sp->sum_addr = sp->saddr + sp->seg_bytes_left / DEV_BSIZE;
	sp->ninodes = 0;
D 4
	sp->sum_num = -1;
E 4
I 4
	sp->nsums = 0;
E 4
D 2
	sp->seg_number = (sp->saddr - fs->lfs_sboffs[0]) /
	    fsbtodb(fs, fs->lfs_ssize);
E 2
I 2
	sp->seg_number =
	    (sp->saddr - fs->lfs_sboffs[0]) / fsbtodb(fs, fs->lfs_ssize);
E 2

E 9
I 9
#ifdef VERBOSE
	printf("lfs_newseg\n");
#endif
E 9
D 3
	/* initialize segment summary info */
	lfs_newsum(fs, sp);
E 3
I 3
D 4
	/* Bump the segment count. */
E 4
I 4
	/* Advance to the next segment. */
E 4
D 9
	fs->lfs_nextseg = lfs_nextseg(fs);
E 9
I 9
	if (!LFS_PARTIAL_FITS(fs)) {
printf("allocating a new segment\n");
		fs->lfs_curseg = fs->lfs_offset = fs->lfs_nextseg;
		fs->lfs_nextseg = lfs_nextseg(fs);
		sp->seg_number = datosn(fs, fs->lfs_curseg);
		sp->seg_bytes_left = fs->lfs_dbpseg * DEV_BSIZE;
E 9
D 4
	lfs_newsum(fs, sp);			/* Init sp->segsum. */
E 4

E 3
D 4
	sup = fs->lfs_segtab + sp->seg_number;
E 4
I 4
D 9
	/* Initialize the summary block. */
	sp = lfs_newsum(fs, sp);
E 4

I 4
	/*
	 * If su_nbytes non-zero after the segment was cleaned, the segment
	 * contains a super-block.  Add segment summary information to not
	 * allocate over it.
	 */
	sup = fs->lfs_segtab + sp->seg_number;
E 4
	if (sup->su_nbytes != 0) {
D 3
		/* This is a segment containing a super block */
E 3
I 3
D 4
		/* This is a segment containing a super block. */
E 3
		FINFO *fip;
		daddr_t lbn, *lbnp;
I 2
		SEGSUM *ssp;
E 2

E 4
I 2
		ssp = (SEGSUM *)sp->segsum;
D 4
		ssp->ss_nfinfo++;
E 4
I 4
		++ssp->ss_nfinfo;
E 4
E 2
		fip = sp->fip;
		fip->fi_nblocks = LFS_SBPAD >> fs->lfs_bshift;
		fip->fi_version = 1;
		fip->fi_ino = LFS_UNUSED_INUM;
D 4
		sp->saddr += fsbtodb(fs, fip->fi_nblocks);
E 4
		lbnp = fip->fi_blocks;
D 4
		for (lbn = 0; lbn < fip->fi_nblocks; lbn++)
E 4
I 4
		for (lbn = 0; lbn < fip->fi_nblocks; ++lbn)
E 4
			*lbnp++ = lbn;
I 4
		sp->saddr += fsbtodb(fs, fip->fi_nblocks);
E 4
		sp->seg_bytes_left -= sup->su_nbytes;
D 4
		sp->sum_bytes_left -= 
E 4
I 4
		sp->sum_bytes_left -=
E 4
		    sizeof(FINFO) + (fip->fi_nblocks - 1) * sizeof(daddr_t);
		sp->fip = (FINFO *)lbnp;
	}
D 4
	return(sp);
E 4
I 4
	return (sp);
E 4
}

D 3

E 3
D 4
static void
E 4
I 4
static SEGMENT *
E 4
lfs_newsum(fs, sp)
D 7
	LFS *fs;
E 7
I 7
	struct lfs *fs;
E 7
	SEGMENT *sp;
{
	SEGSUM *ssp;
D 2
	void *sum;
E 2
I 2
D 4
	int npages, nseg_pages, sums_per_blk;
E 4
I 4
	int nblocks;
E 4
E 2

D 5
printf("lfs_newsum\n");
I 4

E 5
E 4
D 2
	sp->sum_num++;
	if (sp->sum_num == 0) {
		sum = malloc(fs->lfs_bsize, M_SEGMENT, M_WAITOK);
		sp->segsum = sum + fs->lfs_bsize - LFS_SUMMARY_SIZE;
		ssp = sp->segsum;
		ssp->ss_next = fs->lfs_nextseg = lfs_nextseg(fs);
		ssp->ss_prev = fs->lfs_lastseg;
E 2
I 2
	lfs_endsum(fs, sp, 1);
D 4
	++sp->sum_num;
E 4
I 4

	/* Allocate a new buffer if necessary. */
E 4
	if (sp->sbp == NULL) {
D 4
		/* Allocate a new buffer. */
E 4
I 4
		/* Allocate a new segment if necessary. */
E 4
		if (sp->seg_bytes_left < fs->lfs_bsize) {
			lfs_writeseg(fs, sp);
			sp = lfs_newseg(fs);
		}
D 4
		sums_per_blk = fs->lfs_bsize / LFS_SUMMARY_SIZE;
		nseg_pages = 1 + sp->sum_num / sums_per_blk;
		npages = nseg_pages + (sp->ninodes + INOPB(fs) - 1) / INOPB(fs);
		sp->sum_addr = fs->lfs_sboffs[0] + 
		    (sp->seg_number + 1) * fsbtodb(fs, fs->lfs_ssize)
		    - fsbtodb(fs, npages);
		sp->sbp = lfs_newbuf(fs, sp->sum_addr, fs->lfs_bsize);
I 3
		if (sp->sum_num != 0)
			sp->sbp->b_flags |= B_CALL;
E 3
		sp->bpp[fs->lfs_ssize - npages] = sp->sbp;
printf("Inserting summary block, address %x at index %d\n",
sp->sbp->b_lblkno, fs->lfs_ssize - npages);
E 4
I 4

		/* Get the next summary block. */
		sp->sum_addr = next(fs, sp, &nblocks);

E 9
		/*
D 9
		 * Get a new buffer and enter into the buffer list from
		 * the top of the list.
E 9
I 9
		 * If su_nbytes is non-zero after the segment was cleaned,
		 * the segment contains a super-block.  Update offset and
		 * summary address to skip over the superblock.
E 9
		 */
D 9
		sp->sbp = sp->bpp[fs->lfs_ssize - (nblocks + 1)] =
		    lfs_newbuf(fs, sp->sum_addr, fs->lfs_bsize);

E 4
		sp->seg_bytes_left -= fs->lfs_bsize;
I 4

		/*
		 * Do a callback for all but the very last summary block in
		 * the segment, for which we wait.
		 */
		if (sp->nsums != 0)
			sp->sbp->b_flags |= B_CALL;
		/*
		 * Fill in the block from the end.  The summary block is filled
		 * in from the end to the beginning so that the last summary
		 * is the last thing written, verifying the entire block.  This
		 * should go away when fragments are available.
		 */
E 4
D 3
		sp->segsum = sp->sbp->b_un.b_addr + fs->lfs_bsize - LFS_SUMMARY_SIZE;
E 3
I 3
		sp->segsum =
		    sp->sbp->b_un.b_addr + fs->lfs_bsize - LFS_SUMMARY_SIZE;
E 3
		sp->sum_addr += (fs->lfs_bsize - LFS_SUMMARY_SIZE) / DEV_BSIZE;
I 4

I 5
#ifdef SEGWRITE
E 5
		printf("alloc summary: bp %x, lblkno %x, bp index %d\n",
		    sp->sbp, sp->sbp->b_lblkno, fs->lfs_ssize - nblocks);
I 5
#endif
E 9
I 9
		LFS_SEGENTRY(sup, fs, sp->seg_number, bp); 
		if (sup->su_nbytes != 0) {
			fs->lfs_offset += LFS_SBPAD / DEV_BSIZE;
			sp->seg_bytes_left -= LFS_SBPAD;
		}
		brelse(bp);
printf("done allocating new seg\n");
E 9
E 5
E 4
E 2
	} else {
D 2
		lfs_endsum(fs, sp, 1);
		ssp = sp->segsum;
		ssp->ss_next = ssp->ss_next;
		ssp->ss_prev = ssp->ss_prev;
E 2
I 2
D 9
		sp->segsum -= LFS_SUMMARY_SIZE;
		sp->sum_addr -= LFS_SUMMARY_SIZE / DEV_BSIZE;
E 9
I 9
printf("using old segment\n");
		sp->seg_number = datosn(fs, fs->lfs_curseg);
		sp->seg_bytes_left = (fs->lfs_dbpseg -
		    (fs->lfs_offset - fs->lfs_curseg)) * DEV_BSIZE;
E 9
E 2
	}
I 4
D 9
	++sp->nsums;
E 9
E 4

I 9
	sp->ibp = NULL;
	sp->ninodes = 0;

	/* Get a new buffer for SEGSUM and enter it into the buffer list. */
	sp->cbpp = sp->bpp;
	*sp->cbpp = lfs_newbuf(fs, sp, fs->lfs_offset, LFS_SUMMARY_SIZE);
	sp->segsum = (*sp->cbpp)->b_un.b_addr;
	++sp->cbpp;
	fs->lfs_offset += LFS_SUMMARY_SIZE / DEV_BSIZE;

E 9
I 4
	/* Set point to SEGSUM, initialize it. */
E 4
I 2
	ssp = sp->segsum;
D 3
	ssp->ss_next = fs->lfs_nextseg = lfs_nextseg(fs);
E 3
I 3
	ssp->ss_next = fs->lfs_nextseg;
E 3
D 9
	ssp->ss_prev = fs->lfs_lastseg;
D 4

E 2
	/* Initialize segment summary info. */
	sp->fip = (FINFO *)(sp->segsum + sizeof(SEGSUM));
I 2
	sp->fip->fi_nblocks = 0;
E 4
E 2
	ssp->ss_nextsum = (daddr_t)-1;
E 9
	ssp->ss_create = time.tv_sec;
I 4
	ssp->ss_nfinfo = ssp->ss_ninos = 0;
E 4

D 4
	ssp->ss_nfinfo = 0;
	ssp->ss_ninos = 0;
	sp->sum_bytes_left -= LFS_SUMMARY_SIZE;	
	sp->seg_bytes_left -= LFS_SUMMARY_SIZE;	
E 4
I 4
	/* Set pointer to first FINFO, initialize it. */
	sp->fip = (FINFO *)(sp->segsum + sizeof(SEGSUM));

I 9
	sp->seg_bytes_left -= LFS_SUMMARY_SIZE;
E 9
	sp->sum_bytes_left = LFS_SUMMARY_SIZE - sizeof(SEGSUM);
D 9
	return (sp);
E 9
E 4
}

D 4
#define seginc(fs, sn)	((sn + 1) % fs->lfs_nseg)
E 4
I 4
#define seginc(fs, sn)		/* increment segment number */ \
	(((sn) + 1) % (fs)->lfs_nseg)
I 9

E 9
/*
 * Return the next segment to write.
 */
E 4
static daddr_t
lfs_nextseg(fs)
D 7
	LFS *fs;
E 7
I 7
	struct lfs *fs;
E 7
{
D 9
	int segnum, sn;
E 9
I 9
	SEGUSE *sup;
	struct buf *bp;
	int cont, segnum, sn;
E 9
D 4
	SEGUSE *sup;
E 4

I 9
#ifdef VERBOSE
	printf("lfs_nextseg\n");
#endif
E 9
D 2
printf("lfs_nextseg\n");
E 2
D 4
	segnum = satosn(fs, fs->lfs_nextseg);
D 2
	for (sn = seginc(fs, sn); sn != segnum; sn = seginc(fs, sn)) {
		sup = &fs->lfs_segtab[sn];
		if (!(sup->su_flags & SEGUSE_DIRTY))
E 2
I 2
	for (sn = seginc(fs, segnum); sn != segnum; sn = seginc(fs, sn))
		if (!(fs->lfs_segtab[sn].su_flags & SEGUSE_DIRTY))
E 2
			break;
E 4
I 4
	segnum = sn = datosn(fs, fs->lfs_nextseg);
D 9
	while ((sn = seginc(fs, sn)) != segnum &&
	    fs->lfs_segtab[sn].su_flags & SEGUSE_DIRTY);
E 9
I 9
	do {
		cont = (sn = seginc(fs, sn)) != segnum;
		if (cont) {
			LFS_SEGENTRY(sup, fs, sn, bp);
			cont = sup->su_flags & SEGUSE_DIRTY;
			brelse(bp);
		}
	} while (cont);
E 9
E 4
D 2
	}
E 2
I 2

E 2
	if (sn == segnum)
		panic("lfs_nextseg: file system full");		/* XXX */
D 4
	return(sntosa(fs, sn));
E 4
I 4
	return (sntoda(fs, sn));
E 4
}

/*
E 10
D 4
 * Update the metadata that points to the blocks listed in the FIP
E 4
I 4
 * Update the metadata that points to the blocks listed in the FINFO
E 4
 * array.
 */
D 2
static
lfs_updatemeta(fs, ip, fip, bpp)
E 2
I 2
D 13
static void
E 13
I 13
void
E 13
D 9
lfs_updatemeta(fs, sp, ip, lbp, bpp, nblocks)
E 9
I 9
D 47
lfs_updatemeta(fs, sp, vp, lbp, bpp, nblocks)
E 9
E 2
D 7
	LFS *fs;
E 7
I 7
	struct lfs *fs;
E 47
I 47
D 48
lfs_updatemeta(sp, vp)
E 48
I 48
lfs_updatemeta(sp)
E 48
E 47
E 7
I 2
D 14
	SEGMENT *sp;
E 2
D 9
	INODE *ip;
E 9
I 9
	VNODE *vp;
E 14
I 14
	struct segment *sp;
D 48
	struct vnode *vp;
E 48
E 14
E 9
D 2
	FINFO *fip;
E 2
I 2
D 47
	daddr_t *lbp;
E 2
D 14
	BUF **bpp;
E 14
I 14
	struct buf **bpp;
E 14
I 2
	int nblocks;
E 47
E 2
{
I 36
D 39
	USES_VOP_BWRITE;
E 39
E 36
D 10
	SEGUSE *segup;
D 2
	BUF **lbpp, *bp;
E 2
I 2
D 4
	BUF **lbpp, *bp, *mbp;
E 2
	daddr_t da, iblkno;
D 2
	int error, i, oldsegnum;
	long lbn, *lbp;
E 2
I 2
	int db_per_fsb, error, i, oldsegnum;
E 4
I 4
	BUF **lbpp, *bp;
E 10
I 10
	SEGUSE *sup;
D 14
	BUF *bp;
E 14
I 14
	struct buf *bp;
I 47
	struct lfs *fs;
I 48
	struct vnode *vp;
E 48
E 47
E 14
E 10
I 9
D 54
	INDIR a[NIADDR], *ap;
E 54
I 54
	struct indir a[NIADDR + 2], *ap;
E 54
D 14
	INODE *ip;
E 14
I 14
	struct inode *ip;
E 14
E 9
D 10
	daddr_t daddr, iblkno;
E 10
I 10
D 63
	daddr_t daddr, lbn, off;
E 63
I 63
	ufs_daddr_t daddr, lbn, off;
E 63
E 10
D 9
	int db_per_fsb, error, i;
E 9
I 9
D 47
	int db_per_fsb, error, i, num;
E 47
I 47
D 64
	int db_per_fsb, error, i, nblocks, num;
E 64
I 64
	int error, i, nblocks, num;
E 64
E 47
E 9
E 4
D 10
	long lbn;
E 10
E 2

I 48
	vp = sp->vp;
E 48
I 9
D 46
#ifdef VERBOSE
	printf("lfs_updatemeta\n");
#endif
E 46
E 9
D 2
printf("lfs_updatemeta\n");	
	for (lbpp= bpp, lbp = fip->fi_blocks, i = 0; 
	    i < fip->fi_nblocks; i++, lbp++, bp++) {
		lbn = *lbp;
E 2
I 2
D 4
printf("lfs_updatemeta of %d blocks\n", nblocks);	
D 3
	if ((nblocks == 0) && (ip->i_flag & (IMOD|IACC|IUPD|ICHG)) == 0)
E 3
I 3
	if (nblocks == 0 && (ip->i_flag & (IMOD | IACC | IUPD | ICHG)) == 0)
E 4
I 4
D 47
	if (nblocks == 0)
E 47
I 47
	nblocks = &sp->fip->fi_blocks[sp->fip->fi_nblocks] - sp->start_lbp;
I 64
	if (nblocks < 0)
		panic("This is a bad thing\n");
E 64
D 48
	if (nblocks == 0) 
E 48
I 48
	if (vp == NULL || nblocks == 0) 
E 48
E 47
E 4
E 3
		return;
I 4
D 5
printf("lfs_updatemeta of %d blocks\n", nblocks);
E 5
E 4

D 4
	/* First sort the blocks and add disk addresses */
E 4
I 4
D 10
	/* Sort the blocks and add disk addresses */
E 10
I 10
	/* Sort the blocks. */
E 10
E 4
D 13
	shellsort(bpp, lbp, nblocks);
E 13
I 13
D 47
	lfs_shellsort(bpp, lbp, nblocks);
E 47
I 47
	if (!(sp->seg_flags & SEGM_CLEAN))
		lfs_shellsort(sp->start_bpp, sp->start_lbp, nblocks);
E 47
E 13

I 10
	/*
I 64
	 * Record the length of the last block in case it's a fragment.
	 * If there are indirect blocks present, they sort last.  An
	 * indirect block will be lfs_bsize and its presence indicates
	 * that you cannot have fragments.
	 */
	sp->fip->fi_lastlength = sp->start_bpp[nblocks - 1]->b_bcount;

	/*
E 64
	 * Assign disk addresses, and update references to the logical
	 * block and the segment usage information.
	 */
I 47
	fs = sp->fs;
E 47
E 10
D 9
	db_per_fsb = 1 << fs->lfs_fsbtodb;
E 9
I 9
D 64
	db_per_fsb = fsbtodb(fs, 1);
E 64
E 9
D 4
	for (lbpp = bpp, i = 0; i < nblocks; i++, lbpp++) {
E 4
I 4
D 10
	for (lbpp = bpp, i = 0; i < nblocks; ++i, ++lbpp) {
E 4
D 9
		(*lbpp)->b_blkno = sp->saddr;
		sp->saddr += db_per_fsb;
E 9
I 9
		(*lbpp)->b_blkno = fs->lfs_offset;
E 10
I 10
D 47
	for (i = nblocks; i--; ++bpp) {
		lbn = *lbp++;
		(*bpp)->b_blkno = off = fs->lfs_offset;
E 47
I 47
	for (i = nblocks; i--; ++sp->start_bpp) {
		lbn = *sp->start_lbp++;
		(*sp->start_bpp)->b_blkno = off = fs->lfs_offset;
E 47
E 10
D 64
		fs->lfs_offset += db_per_fsb;
E 64
I 64
		fs->lfs_offset +=
		    fragstodb(fs, numfrags(fs, (*sp->start_bpp)->b_bcount));
E 64
E 9
D 10
	}
E 10

D 4
	for (lbpp = bpp, i = 0; i < nblocks; i++, lbpp++) {
E 4
I 4
D 10
	for (lbpp = bpp, i = 0; i < nblocks; ++i, ++lbpp) {
E 4
		lbn = lbp[i];
E 10
D 5
printf("lfs_updatemeta: block %d\n", lbn);
E 5
E 2
D 4
		if (error = lfs_bmap(ip, lbn, &da))
D 2
			return(error);
E 2
I 2
		    panic("lfs_updatemeta: lfs_bmap returned error");
E 4
I 4
D 8
		if (error = lfs_bmap(ip, lbn, &daddr))
E 8
I 8
D 9
		if (error = lfs_bmap(ITOV(ip), lbn, NULL, &daddr))
E 8
			panic("lfs_updatemeta: lfs_bmap");
E 4
E 2

D 4
		if (da) {
I 2
			/* Update segment usage information */
E 2
			oldsegnum = (da - fs->lfs_sboffs[0]) /
			    fsbtodb(fs, fs->lfs_ssize);
			segup = fs->lfs_segtab+oldsegnum;
E 4
I 4
		/* Update in-core copy of old segment usage information. */
E 9
I 9
D 54
		if (error = lfs_bmaparray(vp, lbn, &daddr, a, &num))
D 10
			panic("lfs_updatemeta: lfs_bmaparray");
E 10
I 10
D 14
			panic("lfs_updatemeta: lfs_bmaparray returned %d",
			    error);
E 10
#ifdef META
		printf("daddr: %d num: %d\n", daddr, num);
		if (num != 0) {
			int x;
D 10
			printf("Array from bmaparray:\n");
E 10
I 10
			printf("array from bmaparray:\n");
E 10
			for (x = 0; x < num; x++)
				printf("\tlbn %d off %d\n", a[x].in_lbn, a[x].in_off);
		}
#endif
E 14
I 14
			panic("lfs_updatemeta: lfs_bmaparray %d", error);
E 54
I 54
		if (error = ufs_bmaparray(vp, lbn, &daddr, a, &num, NULL))
			panic("lfs_updatemeta: ufs_bmaparray %d", error);
E 54
E 14
D 10
		/* Update segment usage information. */
E 9
		if (daddr != UNASSIGNED) {
D 9
			segup = fs->lfs_segtab + datosn(fs, daddr);
E 9
I 9
			LFS_SEGENTRY(segup, fs, datosn(fs, daddr), bp);
E 9
E 4
			segup->su_lastmod = time.tv_sec;
D 4
			if ((segup->su_nbytes -= fs->lfs_bsize) < 0)
				printf("lfs_updatemeta: negative bytes %s %d\n",
					"in segment", oldsegnum);
E 4
I 4
#ifdef DIAGNOSTIC
D 5
			if (segup->su_nbytes < fs->lfs_bsize) {
				printf("lfs: negative bytes (segment %d)\n",
E 5
I 5
			if (segup->su_nbytes < fs->lfs_bsize)
				panic("lfs: negative bytes (segment %d)\n",
E 5
D 9
				    segup - fs->lfs_segtab);
E 9
I 9
					datosn(fs, daddr));
E 9
D 5
				panic("lfs: negative bytes in segment\n");
			}
E 5
#endif
			segup->su_nbytes -= fs->lfs_bsize;
I 9
			lfs_bwrite(bp);
E 9
E 4
		}

D 2
		/* Now change whoever points to lbn */
		if (lbn < NDADDR)
E 2
I 2
D 9
		/*
D 4
		 * Now change whoever points to lbn.  We could start with the
E 4
I 4
		 * Now change whomever points to lbn.  We could start with the
E 4
		 * smallest (most negative) block number in these if clauses,
		 * but we assume that indirect blocks are least common, and
D 4
		 * handle them separately.
E 4
I 4
		 * handle them separately.  The test for < 0 is correct and
		 * minimizes the path in the common case.
E 4
		 */
D 4
		bp = NULL;
		if (lbn < 0) {
			if (lbn < -NIADDR) {
printf("lfs_updatemeta: changing indirect block %d\n", D_INDIR);
				if (error = bread(ITOV(ip), D_INDIR, 
				    fs->lfs_bsize, NOCRED, &bp))
				    panic("lfs_updatemeta: error on bread");
E 4
I 4
#define	BREAD(bno) \
	if (error = bread(ITOV(ip), (bno), fs->lfs_bsize, NOCRED, &bp)) \
		panic("lfs_updatemeta: bread");
E 4

D 4
				bp->b_un.b_daddr[-lbn % NINDIR(fs)] = 
E 4
I 4
		if (lbn < 0)
			if (lbn < -NIADDR) {
E 9
I 9
		/* Now change whomever points to lbn. */
E 10
		ip = VTOI(vp);
		switch (num) {
		case 0:
E 9
I 5
D 14
#ifdef META
E 5
D 9
				printf("meta: update indirect block %d\n",
				    D_INDIR);
E 9
I 9
			printf("update inode for direct block %d\n", lbn);
E 9
I 5
#endif
E 14
E 5
D 9
				BREAD(D_INDIR);
				bp->b_un.b_daddr[-lbn % NINDIR(fs)] =
E 4
				    (*lbpp)->b_blkno;
D 4
			} else
				ip->i_din.di_ib[-lbn-1] = (*lbpp)->b_blkno;
			
		} else if (lbn < NDADDR) 
E 2
			ip->i_din.di_db[lbn] = (*lbpp)->b_blkno;
		else if ((lbn -= NDADDR) < NINDIR(fs)) {
printf("lfs_updatemeta: changing indirect block %d\n", S_INDIR);
D 2
			error = bread(ITOV(ip), S_INDIR, fs->lfs_bsize, 
			    NOCRED, &bp);
			if (error)
				return(error);
E 2
I 2
			if (error = bread(ITOV(ip), S_INDIR, fs->lfs_bsize, 
			    NOCRED, &bp))
			    panic("lfs_updatemeta: bread returned error");

E 4
I 4
				lfs_bwrite(bp);
			} else {
				ip->i_ib[-lbn-1] = (*lbpp)->b_blkno;
		} else if (lbn < NDADDR) {
E 9
D 10
			ip->i_db[lbn] = (*lbpp)->b_blkno;
E 10
I 10
			ip->i_db[lbn] = off;
E 10
D 9
		} else if ((lbn -= NDADDR) < NINDIR(fs)) {
E 9
I 9
			break;
		case 1:
D 10
			ip->i_ib[a[0].in_off] = (*lbpp)->b_blkno;
E 10
I 10
			ip->i_ib[a[0].in_off] = off;
E 10
			break;
		default:
			ap = &a[num - 1];
E 9
I 5
D 14
#ifdef META
E 5
D 9
			printf("meta: update indirect block %d\n", S_INDIR);
E 9
I 9
			printf("update indirect block %d offset %d\n",
D 13
			    ap->in_lbn, ap->in_off); 
E 13
I 13
			    ap->in_lbn, ap->in_off);
E 13
E 9
I 5
#endif
E 14
E 5
D 9
			BREAD(S_INDIR);
E 4
E 2
			bp->b_un.b_daddr[lbn] = (*lbpp)->b_blkno;
E 9
I 9
			if (bread(vp, ap->in_lbn, fs->lfs_bsize, NOCRED, &bp))
				panic("lfs_updatemeta: bread bno %d",
				    ap->in_lbn);
I 41
			/*
			 * Bread may create a new indirect block which needs
			 * to get counted for the inode.
			 */
D 43
			if (bp->b_blkno == -1 && !(bp->b_flags & B_CACHE))
E 43
I 43
			if (bp->b_blkno == -1 && !(bp->b_flags & B_CACHE)) {
I 47
D 64
printf ("Updatemeta allocating indirect block: shouldn't happen\n");
E 47
E 43
				ip->i_blocks += btodb(fs->lfs_bsize);
I 43
				fs->lfs_bfree -= btodb(fs->lfs_bsize);
E 64
I 64
				ip->i_blocks += fsbtodb(fs, 1);
				fs->lfs_bfree -= fragstodb(fs, fs->lfs_frag);
E 64
			}
E 43
E 41
D 10
			bp->b_un.b_daddr[ap->in_off] = (*lbpp)->b_blkno;
E 10
I 10
D 58
			bp->b_un.b_daddr[ap->in_off] = off;
E 58
I 58
D 63
			((daddr_t *)bp->b_data)[ap->in_off] = off;
E 63
I 63
			((ufs_daddr_t *)bp->b_data)[ap->in_off] = off;
E 63
E 58
E 10
E 9
D 2
			brelse(bp);
E 2
D 4
		} else if ( (lbn = (lbn - NINDIR(fs)) / NINDIR(fs)) < 
			    NINDIR(fs)) {

			iblkno = - (lbn + NIADDR + 1);
printf("lfs_updatemeta: changing indirect block %d\n", iblkno);
D 2
			error = bread(ITOV(ip), iblkno, fs->lfs_bsize, NOCRED, 
			    &bp);
			if (error)
				return(error);
E 2
I 2
			if (error = bread(ITOV(ip), iblkno, fs->lfs_bsize, 
			    NOCRED, &bp))
			    panic("lfs_updatemeta: bread returned error");

E 4
I 4
D 36
			lfs_bwrite(bp);
E 36
I 36
			VOP_BWRITE(bp);
E 36
D 9
		} else if ((lbn =
		    (lbn - NINDIR(fs)) / NINDIR(fs)) < NINDIR(fs)) {
			iblkno = -(lbn + NIADDR + 1);
I 5
#ifdef META
E 5
			printf("meta: update indirect block %d\n", iblkno);
I 5
#endif
E 5
			BREAD(iblkno);
E 4
E 2
			bp->b_un.b_daddr[lbn % NINDIR(fs)] = (*lbpp)->b_blkno;
D 4
		}
		else
D 2
			return(EFBIG);
E 2
I 2
			panic("lfs_updatemeta: logical block number too large");
		if (bp)
E 4
			lfs_bwrite(bp);
I 4
		} else
			panic("lfs_updatemeta: logical block number too large");
E 4
E 2
	}
D 2
	return(0);
E 2
}

I 2
D 3
static void
E 3
I 3
static SEGMENT *
E 3
lfs_writeckp(fs, sp)
D 7
	LFS *fs;
E 7
I 7
	struct lfs *fs;
E 7
	SEGMENT *sp;
{
	BUF *bp;
	FINFO *fip;
	INODE *ip;
	SEGUSE *sup;
I 3
	void *xp;
E 3
	daddr_t *lbp;
	int bytes_needed, i;
D 3
	void *xp;
E 3

D 5
printf("lfs_writeckp\n");
E 5
	/*
	 * This will write the dirty ifile blocks, but not the segusage
	 * table nor the ifile inode.
	 */
D 4
	sp = lfs_writefile(sp, fs, fs->lfs_ivnode, 1);
E 4
I 4
	sp = lfs_writefile(fs, sp, fs->lfs_ivnode, 1);
E 4

	/*
D 4
	 * Make sure that the segment usage table and the ifile inode will
	 * fit in this segment.  If they won't, put them in the next segment
E 4
I 4
	 * If the segment usage table and the ifile inode won't fit in this
	 * segment, put them in the next one.
E 4
	 */
	bytes_needed = fs->lfs_segtabsz << fs->lfs_bshift;
	if (sp->ninodes % INOPB(fs) == 0)
		bytes_needed += fs->lfs_bsize;

	if (sp->seg_bytes_left < bytes_needed) {
		lfs_writeseg(fs, sp);
		sp = lfs_newseg(fs);
D 4
	} else if (sp->sum_bytes_left < (fs->lfs_segtabsz * sizeof(daddr_t)))
		lfs_newsum(fs, sp);
E 4
I 4
		++((SEGSUM *)(sp->segsum))->ss_nfinfo;
	} else if (sp->sum_bytes_left < fs->lfs_segtabsz * sizeof(daddr_t)) {
		sp = lfs_newsum(fs, sp);
		++((SEGSUM *)(sp->segsum))->ss_nfinfo;
	}
E 4

#ifdef DEBUG
	if (sp->seg_bytes_left < bytes_needed)
		panic("lfs_writeckp: unable to write checkpoint");
#endif
D 4

E 4
	/*
D 3
	 * Now, update the segment usage information and the ifile inode and
	 * and write it out
E 3
I 3
	 * Update the segment usage information and the ifile inode
	 * and write it out.
E 3
	 */
D 3

E 3
	sup = fs->lfs_segtab + sp->seg_number;
D 3
	sup->su_nbytes = (fs->lfs_segmask + 1) - sp->seg_bytes_left + 
	    bytes_needed;
E 3
I 3
	sup->su_nbytes =
	    (fs->lfs_segmask + 1) - sp->seg_bytes_left + bytes_needed;
E 3
	sup->su_lastmod = time.tv_sec;
	sup->su_flags = SEGUSE_DIRTY;

D 3
	/* Get buffers for the segusage table and write it out */
E 3
I 3
D 4
	/* Get buffers for the segusage table and write it out. */
E 4
I 4
	/*
	 * Get buffers for the segusage table and write it out.  Don't
	 * bother updating the FINFO pointer, it's not used after this.
	 */
E 4
E 3
	ip = VTOI(fs->lfs_ivnode);
	fip = sp->fip;
	lbp = &fip->fi_blocks[fip->fi_nblocks];
D 4
	for (xp = fs->lfs_segtab, i = 0; i < fs->lfs_segtabsz; 
	    i++, xp += fs->lfs_bsize, lbp++) {
E 4
I 4
	for (xp = fs->lfs_segtab, i = 0; i < fs->lfs_segtabsz;
	    xp += fs->lfs_bsize, ++i, ++lbp) {
E 4
D 3
		bp = lfs_newbuf(fs, sp->saddr, fs->lfs_bsize);
		*sp->cbpp++ = bp;
E 3
I 3
		*sp->cbpp++ = bp = lfs_newbuf(fs, sp->saddr, fs->lfs_bsize);
		bp->b_flags |= B_CALL;
E 3
D 4
		bcopy(xp, bp->b_un.b_words, fs->lfs_bsize);
		ip->i_din.di_db[i] = sp->saddr;
E 4
I 4
		bcopy(xp, bp->b_un.b_addr, fs->lfs_bsize);
		ip->i_db[i] = sp->saddr;
E 4
		sp->saddr += (1 << fs->lfs_fsbtodb);
		*lbp = i;
D 4
		fip->fi_nblocks++;
E 4
I 4
		++fip->fi_nblocks;
E 4
	}
D 4
	sp = lfs_writeinode(fs, sp, fs->lfs_ivnode);
	lfs_writeseg(fs, sp);
D 3
	lfs_writesuper(fs, sp);
E 3
I 3
	return (sp);
E 4
I 4
	return (lfs_writeinode(fs, sp, VTOI(fs->lfs_ivnode)));
E 4
E 3
}

E 2
/*
D 2
 * Returns 0 if the entire file fit into the current segment and
 * summary region, 1 if not.
E 2
D 4
 * XXX -- I think we need to figure out what to do if we write
 * the segment and find more dirty blocks when we're done.
E 4
I 4
 * Write the dirty blocks associated with a vnode.
E 4
 */
static SEGMENT *
D 2
lfs_writefile(sp, fs, vp)
E 2
I 2
D 4
lfs_writefile(sp, fs, vp, do_ckp)
E 2
	SEGMENT *sp;
E 4
I 4
lfs_writefile(fs, sp, vp, do_ckp)
E 4
D 7
	LFS *fs;
E 7
I 7
	struct lfs *fs;
E 7
I 4
	SEGMENT *sp;
E 4
	VNODE *vp;
I 2
	int do_ckp;
E 2
{
D 2
	register BUF *bp;
	BUF **bpp, *nbp;
E 2
	FINFO *fip;
D 3
	INODE *ip;
E 3
I 3
	ino_t inum;
E 3
D 2
	int db_per_fsb, error, i;
	int ret_val, s;
	long *lbp;
E 2

D 3
	/* initialize the FINFO structure */
	ip = VTOI(vp);
printf("lfs_writefile: node %d\n", ip->i_number);
loop:
E 3
I 3
D 4
	/* Initialize the FINFO structure. */
E 4
	inum = VTOI(vp)->i_number;
D 4
printf("lfs_writefile: node %d\n", inum);
	sp->fip->fi_ino = inum;
E 3
D 2
	fip = sp->fip;
	fip->fi_nblocks = 0;
	fip->fi_ino = ip->i_number;
	fip->fi_version = lfs_getversion(fs, ip->i_number);
	lbp = fip->fi_blocks;
	
	bpp = sp->cbpp;
	s = splbio();
	for (bp = vp->v_dirtyblkhd; bp; bp = nbp) {
		nbp = bp->b_blockf;
printf("lfs_writefile: disk block num %d flags %x\n", bp->b_blkno, bp->b_flags);
		if ((bp->b_flags & B_BUSY))
			continue;
		if ((bp->b_flags & B_DELWRI) == 0)
			panic("lfs_write: not dirty");
		bremfree(bp);
		bp->b_flags |= (B_BUSY | B_CALL);
		bp->b_iodone = lfs_biocallback;
E 2
I 2
	sp->fip->fi_nblocks = 0;
D 3
	sp->fip->fi_ino = ip->i_number;
	if (ip->i_number != LFS_IFILE_INUM)
		sp->fip->fi_version = lfs_getversion(fs, ip->i_number);
	else
		sp->fip->fi_version = 1;
E 3
I 3
	sp->fip->fi_version =
	    inum == LFS_IFILE_INUM ? 1 : lfs_getversion(fs, inum);
E 4
I 4
D 5
	printf("lfs_writefile: node %d\n", inum);
E 5
E 4
E 3
E 2

D 2
		/* UFS does the bawrites and bwrites here; we don't */
		*lbp++ = bp->b_lblkno;		/* UPDATE META HERE */
		*sp->cbpp++ = bp;
		fip->fi_nblocks++;
		sp->sum_bytes_left -= sizeof(daddr_t);
		sp->seg_bytes_left -= bp->b_bufsize;
		if (sp->sum_bytes_left < sizeof(daddr_t) || 
		    sp->seg_bytes_left < fs->lfs_bsize) {
			/*
			 * We are about to allocate a new summary block
			 * and possibly a new segment.  So, we need to
			 * sort the blocks we've done so far, and assign
			 * the disk addresses, so we can start a new block
			 * correctly.  We may be doing I/O so we need to
			 * release the s lock before doing anything.
			 */
			splx(s);
			if (error = lfs_updatemeta(fs, ip, fip, bpp))
				panic("lfs_writefile: error from lfs_updatemeta\n");
E 2
I 2
D 4
	sp = lfs_gather(fs, sp, vp, match_data);
	if (do_ckp) {
		sp = lfs_gather(fs, sp, vp, match_indir);
		sp = lfs_gather(fs, sp, vp, match_dindir);
	}
E 4
I 4
	if (vp->v_dirtyblkhd != NULL) {
		if (sp->seg_bytes_left < fs->lfs_bsize) {
			lfs_writeseg(fs, sp);
			sp = lfs_newseg(fs);
		} else if (sp->sum_bytes_left < sizeof(FINFO))
			sp = lfs_newsum(fs, sp);
		sp->sum_bytes_left -= sizeof(FINFO) - sizeof(daddr_t);
E 4
E 2

D 2
			/* Put this file in the segment summary */
E 2
I 2
D 4
(void)printf("lfs_writefile: adding %d blocks to segment\n",
sp->fip->fi_nblocks);
	/* 
D 3
	 * Update the inode for this file and reflect new inode
	 * address in the ifile.  If this is the ifile, don't update
	 * the inode, because we're checkpointing and will update the
	 * inode with the segment usage information (so we musn't
	 * bump the finfo pointer either).
E 3
I 3
	 * Update the inode for this file and reflect new inode address in
	 * the ifile.  If this is the ifile, don't update the inode, because
	 * we're checkpointing and will update the inode with the segment
	 * usage information (so we musn't bump the finfo pointer either).
E 3
	 */
D 3
	if (ip->i_number != LFS_IFILE_INUM) {
E 3
I 3
	if (inum != LFS_IFILE_INUM) {
E 3
		sp = lfs_writeinode(fs, sp, vp);
E 4
		fip = sp->fip;
D 4
		if (fip->fi_nblocks) {
E 2
			((SEGSUM *)(sp->segsum))->ss_nfinfo++;
D 2

			if (sp->seg_bytes_left < fs->lfs_bsize) {
				lfs_writeseg(fs, sp);
				sp = lfs_newseg(fs);
			} else if (sp->sum_bytes_left < sizeof(daddr_t))
				lfs_newsum(fs, sp);
			fip = sp->fip;
			s = splbio();
E 2
I 2
			sp->fip = (FINFO *)((u_long)fip + sizeof(FINFO) + 
			    sizeof(u_long) * fip->fi_nblocks - 1);
E 4
I 4
		fip->fi_nblocks = 0;
		fip->fi_version =
		    inum == LFS_IFILE_INUM ? 1 : lfs_getversion(fs, inum);
		fip->fi_ino = inum;

		sp = lfs_gather(fs, sp, vp, match_data);
		if (do_ckp) {
			sp = lfs_gather(fs, sp, vp, match_indir);
			sp = lfs_gather(fs, sp, vp, match_dindir);
E 9
E 4
E 2
		}
I 10

		/* Update segment usage information. */
D 56
		if (daddr != UNASSIGNED) {
E 56
I 56
		if (daddr != UNASSIGNED &&
		    !(daddr >= fs->lfs_lastpseg && daddr <= off)) {
E 56
			LFS_SEGENTRY(sup, fs, datosn(fs, daddr), bp);
D 18
			sup->su_lastmod = time.tv_sec;
E 18
#ifdef DIAGNOSTIC
D 38
			if (sup->su_nbytes < fs->lfs_bsize)
E 38
I 38
D 64
			if (sup->su_nbytes < fs->lfs_bsize) {
E 64
I 64
			if (sup->su_nbytes < (*sp->start_bpp)->b_bcount) {
E 64
E 38
D 20
				panic("lfs: negative bytes (segment %d)\n",
E 20
I 20
				/* XXX -- Change to a panic. */
				printf("lfs: negative bytes (segment %d)\n",
E 20
				    datosn(fs, daddr));
I 66
				printf("lfs: bp = 0x%x, addr = 0x%x\n",
						bp, bp->b_un.b_addr);
E 66
I 38
				panic ("Negative Bytes");
			}
E 38
#endif
D 64
			sup->su_nbytes -= fs->lfs_bsize;
E 64
I 64
			sup->su_nbytes -= (*sp->start_bpp)->b_bcount;
E 64
D 13
			lfs_bwrite(bp);
E 13
I 13
D 14
			LFS_IWRITE(fs, bp);
E 14
I 14
D 47
			LFS_UBWRITE(bp);
E 47
I 47
			error = VOP_BWRITE(bp);
E 47
E 14
E 13
		}
E 10
I 4
D 9

		fip = sp->fip;
D 5
		printf("lfs_writefile: adding %d blocks\n", fip->fi_nblocks);
E 5

I 5
#ifdef META
		printf("lfs_writefile: adding %d blocks\n", fip->fi_nblocks);
#endif
E 5
		/*
		 * If this is the ifile, always update the file count as we'll
		 * be adding the segment usage information even if we didn't
		 * write any blocks.  Also, don't update the FINFO pointer for
		 * the ifile as the segment usage information hasn't yet been
		 * added.
		 */
		if (inum == LFS_IFILE_INUM)
			++((SEGSUM *)(sp->segsum))->ss_nfinfo;
		else if (fip->fi_nblocks != 0) {
			++((SEGSUM *)(sp->segsum))->ss_nfinfo;
			sp->fip = (FINFO *)((caddr_t)fip + sizeof(FINFO) +
			    sizeof(daddr_t) * (fip->fi_nblocks - 1));
		}
E 9
E 4
D 2

E 2
	}
D 2
	splx(s);
	db_per_fsb = 1 << fs->lfs_fsbtodb;
	shellsort(bpp, (u_long *)fip->fi_blocks, fip->fi_nblocks);
	for (bp = *bpp, i = 0; i < fip->fi_nblocks; i++, bp++) {
		bp->b_blkno = sp->saddr;
		sp->saddr += db_per_fsb;
		/* 
		 * Update the meta data now for this file.  If we've filled
		 * a segment, then we'll have to wait until the next segment
		 * to write out the updated metadata.
		 */
		lfs_writemeta();
	}
(void)printf("lfs_writefile: adding %d blocks to segment\n", fip->fi_nblocks);
	if (fip->fi_nblocks) {
		((SEGSUM *)(sp->segsum))->ss_nfinfo++;
		sp->fip = (FINFO *)((u_long)fip + sizeof(FINFO) + 
		    sizeof(u_long) * (fip->fi_nblocks - 1));
	}
E 2
D 4
	return(sp);
E 4
I 4
D 9

	/* If this isn't the ifile, update the inode. */
	if (inum != LFS_IFILE_INUM)
		sp = lfs_writeinode(fs, sp, VTOI(vp));
	return (sp);
E 9
E 4
}

I 10
/*
 * Start a new segment.
 */
E 10
D 2
static void
lfs_writemeta()
E 2
I 2
D 9
static SEGMENT *
E 9
I 9
D 13
static void
E 13
I 13
D 56
void
E 13
E 9
D 4
lfs_writeinode(fs, sp, vp)
E 4
I 4
D 10
lfs_writeinode(fs, sp, ip)
E 10
I 10
lfs_initseg(fs, sp)
E 56
I 56
int
lfs_initseg(fs)
E 56
E 10
E 4
D 7
	LFS *fs;
E 7
I 7
	struct lfs *fs;
E 7
D 14
	SEGMENT *sp;
E 14
I 14
D 56
	struct segment *sp;
E 56
E 14
D 4
	VNODE *vp;
E 4
I 4
D 10
	INODE *ip;
E 10
E 4
E 2
{
I 56
	struct segment *sp;
E 56
D 2
	printf("lfs_writemeta (STUB)\n");
E 2
I 2
D 10
	BUF *bp;
D 4
	INODE *ip;
	SEGSUM *ssp;
	daddr_t iaddr, next_addr;
	int npages, nseg_pages, sums_per_blk;
	struct dinode *dip;
E 4
I 4
	daddr_t next_addr;
D 9
	int nblocks;
E 9
I 9
	int nblocks, ndx;
E 10
I 10
	SEGUSE *sup;
	SEGSUM *ssp;
	struct buf *bp;
D 61
	daddr_t lbn, *lbnp;
E 61
I 56
	int repeat;
E 56
E 10
E 9
E 4

I 56
	sp = fs->lfs_sp;

	repeat = 0;
E 56
I 9
D 46
#ifdef VERBOSE
D 10
	printf("lfs_writeinode\n");
E 10
I 10
	printf("lfs_initseg\n");
E 10
#endif
E 46
E 9
D 5
printf("lfs_writeinode\n");
E 5
D 4
	sums_per_blk = fs->lfs_bsize / LFS_SUMMARY_SIZE;
E 4
I 4
D 10
	/* Allocate a new inode block if necessary. */
E 4
	if (sp->ibp == NULL) {
D 4
		/* Allocate a new buffer. */
E 4
I 4
		/* Allocate a new segment if necessary. */
E 4
D 9
		if (sp->seg_bytes_left < fs->lfs_bsize) {
E 9
I 9
		if (sp->seg_bytes_left < fs->lfs_bsize ||
		    sp->sum_bytes_left < sizeof(daddr_t)) {
E 9
			lfs_writeseg(fs, sp);
D 9
			sp = lfs_newseg(fs);
E 9
I 9
			lfs_newseg(fs, sp);
E 10
I 10
	/* Advance to the next segment. */
D 12
	if (1 || !LFS_PARTIAL_FITS(fs)) {
		LFS_SEGENTRY(sup, fs, datosn(fs, fs->lfs_curseg), bp);
		sup->su_flags &= ~SEGUSE_ACTIVE;
		lfs_bwrite(bp);
		fs->lfs_curseg = fs->lfs_offset = fs->lfs_nextseg;
		fs->lfs_nextseg = lfs_newseg(fs);
E 12
I 12
	if (!LFS_PARTIAL_FITS(fs)) {
I 18
		/* Wake up any cleaning procs waiting on this file system. */
D 19
		wakeup((caddr_t)&fs->lfs_nextseg);
		wakeup((caddr_t)&lfs_allclean_wakeup);
E 19
I 19
D 56
		wakeup(&fs->lfs_nextseg);
E 56
		wakeup(&lfs_allclean_wakeup);
I 66
		wakeup(&fs->lfs_nextseg);
E 66
E 19

E 18
		lfs_newseg(fs);
I 56
		repeat = 1;
E 56
		fs->lfs_offset = fs->lfs_curseg;
E 12
		sp->seg_number = datosn(fs, fs->lfs_curseg);
		sp->seg_bytes_left = fs->lfs_dbpseg * DEV_BSIZE;

		/*
D 12
		 * If su_nbytes is non-zero after the segment was cleaned,
		 * the segment contains a super-block.  Update offset and
		 * summary address to skip over the superblock.
E 12
I 12
		 * If the segment contains a superblock, update the offset
		 * and summary address to skip over it.
E 12
		 */
D 13
		LFS_SEGENTRY(sup, fs, sp->seg_number, bp); 
E 13
I 13
		LFS_SEGENTRY(sup, fs, sp->seg_number, bp);
E 13
D 12
		if (sup->su_nbytes != 0) {
E 12
I 12
		if (sup->su_flags & SEGUSE_SUPERBLOCK) {
E 12
			fs->lfs_offset += LFS_SBPAD / DEV_BSIZE;
			sp->seg_bytes_left -= LFS_SBPAD;
E 10
E 9
		}
I 10
D 13
		brelse(bp);
E 13
I 13
D 14
		LFS_IRELEASE(fs, bp);
E 14
I 14
		brelse(bp);
E 14
E 13
	} else {
		sp->seg_number = datosn(fs, fs->lfs_curseg);
		sp->seg_bytes_left = (fs->lfs_dbpseg -
		    (fs->lfs_offset - fs->lfs_curseg)) * DEV_BSIZE;
	}
I 38
	fs->lfs_lastpseg = fs->lfs_offset;
E 38
E 10
D 4
		nseg_pages = (sp->sum_num + sums_per_blk) / sums_per_blk;
		npages = nseg_pages + (sp->ninodes + INOPB(fs)) / INOPB(fs);
		next_addr = fs->lfs_sboffs[0] + 
		    (sp->seg_number + 1) * fsbtodb(fs, fs->lfs_ssize)
		    - fsbtodb(fs, npages);
		sp->ibp = lfs_newbuf(fs, next_addr, fs->lfs_bsize);
E 4
I 4

I 47
	sp->fs = fs;
E 47
D 10
		/* Get next inode block. */
D 9
		next_addr = next(fs, sp, &nblocks);
E 9
I 9
		next_addr = fs->lfs_offset;
		fs->lfs_offset += fsbtodb(fs, 1);
		sp->ibp = *sp->cbpp++ =
		    lfs_newbuf(fs, sp, next_addr, fs->lfs_bsize);
E 10
I 10
	sp->ibp = NULL;
	sp->ninodes = 0;
E 10
E 9

D 9
		/*
		 * Get a new buffer and enter into the buffer list from
		 * the top of the list.
		 */
		sp->ibp = sp->bpp[fs->lfs_ssize - (nblocks + 1)] =
		    lfs_newbuf(fs, next_addr, fs->lfs_bsize);
E 4
D 3
		sp->ibp->b_flags |= B_BUSY;
E 3
I 3
		sp->ibp->b_flags |= B_CALL;
E 3
D 4
		sp->bpp[fs->lfs_ssize - npages] = sp->ibp;
E 4
I 4

E 9
D 10
		/* Set remaining space counter. */
E 4
		sp->seg_bytes_left -= fs->lfs_bsize;
I 9
		sp->sum_bytes_left -= sizeof(daddr_t);
		ndx = LFS_SUMMARY_SIZE / sizeof(daddr_t) - 
		    sp->ninodes / INOPB(fs) - 1;
		((daddr_t *)(sp->segsum))[ndx] = next_addr;
E 9
D 4
printf("alloc inode block @ daddr %x, bp = %x inserted at %d\n", 
next_addr, sp->ibp, fs->lfs_ssize - npages);
E 4
I 4
D 5

		printf("alloc inode: bp %x, lblkno %x, bp index %d\n",
		    sp->sbp, sp->sbp->b_lblkno, fs->lfs_ssize - nblocks);
E 5
E 4
	}
E 10
I 10
	/* Get a new buffer for SEGSUM and enter it into the buffer list. */
	sp->cbpp = sp->bpp;
D 19
	*sp->cbpp = lfs_newbuf(fs, sp, fs->lfs_offset, LFS_SUMMARY_SIZE);
E 19
I 19
D 47
	*sp->cbpp = lfs_newbuf(fs, fs->lfs_offset, LFS_SUMMARY_SIZE);
E 47
I 47
D 49
	*sp->cbpp =
	    lfs_newbuf(fs->lfs_ivnode, fs->lfs_offset, LFS_SUMMARY_SIZE);
E 49
I 49
	*sp->cbpp = lfs_newbuf(VTOI(fs->lfs_ivnode)->i_devvp, fs->lfs_offset,
	     LFS_SUMMARY_SIZE);
E 49
E 47
E 19
D 58
	sp->segsum = (*sp->cbpp)->b_un.b_addr;
E 58
I 58
	sp->segsum = (*sp->cbpp)->b_data;
E 58
I 56
	bzero(sp->segsum, LFS_SUMMARY_SIZE);
E 56
D 47
	++sp->cbpp;
E 47
I 47
	sp->start_bpp = ++sp->cbpp;
E 47
	fs->lfs_offset += LFS_SUMMARY_SIZE / DEV_BSIZE;
E 10
D 4
	ip = VTOI(vp);
E 4
I 4

D 9
	/* Copy the new inode onto the inode page. */
E 9
I 9
D 10
	/* Copy the new inode onto the inode page.
	 * XXX
	 * Do struct assignment.
	 */
E 9
E 4
	bp = sp->ibp;
D 4
	dip = bp->b_un.b_dino + (sp->ninodes % INOPB(fs));
	bcopy(&ip->i_din, dip, sizeof(struct dinode));
	iaddr = bp->b_blkno;
	++sp->ninodes;
	ssp = sp->segsum;
	++ssp->ss_ninos;
	if (sp->ninodes % INOPB(fs) == 0)
E 4
I 4
	bcopy(&ip->i_din,
	    bp->b_un.b_dino + (sp->ninodes % INOPB(fs)), sizeof(DINODE));
E 10
I 10
	/* Set point to SEGSUM, initialize it. */
	ssp = sp->segsum;
	ssp->ss_next = fs->lfs_nextseg;
D 14
	ssp->ss_create = time.tv_sec;
E 14
	ssp->ss_nfinfo = ssp->ss_ninos = 0;
I 64
	ssp->ss_magic = SS_MAGIC;
E 64
E 10

D 10
	/* Increment inode count in segment summary block. */
	++((SEGSUM *)(sp->segsum))->ss_ninos;
E 10
I 10
	/* Set pointer to first FINFO, initialize it. */
D 14
	sp->fip = (FINFO *)(sp->segsum + sizeof(SEGSUM));
E 14
I 14
D 62
	sp->fip = (struct finfo *)(sp->segsum + sizeof(SEGSUM));
E 62
I 62
	sp->fip = (struct finfo *)((caddr_t)sp->segsum + sizeof(SEGSUM));
E 62
E 14
	sp->fip->fi_nblocks = 0;
I 47
	sp->start_lbp = &sp->fip->fi_blocks[0];
I 64
	sp->fip->fi_lastlength = 0;
E 64
E 47
E 10

D 10
	/* If this page is full, set flag to allocate a new page. */
	if (++sp->ninodes % INOPB(fs) == 0)
E 4
		sp->ibp = NULL;
E 10
I 10
	sp->seg_bytes_left -= LFS_SUMMARY_SIZE;
	sp->sum_bytes_left = LFS_SUMMARY_SIZE - sizeof(SEGSUM);
I 56

	return(repeat);
E 56
}
E 10
I 4

D 10
	/*
	 * If updating the ifile, update the super-block; otherwise, update
D 9
	 * the ifile itself.  In either case, turn of inode update flags.
E 9
I 9
	 * the ifile itself.  In either case, turn off inode update flags.
E 9
	 */
E 4
	if (ip->i_number == LFS_IFILE_INUM)
D 4
		fs->lfs_idaddr = iaddr;
E 4
I 4
		fs->lfs_idaddr = bp->b_blkno;
E 4
	else
D 4
		lfs_iset(ip, iaddr, ip->i_atime);	/* Update ifile */
	ip->i_flags &= ~(IMOD|IACC|IUPD|ICHG);		/* make inode clean */
	return(sp);
E 4
I 4
		lfs_iset(ip, bp->b_blkno, ip->i_atime);
	ip->i_flags &= ~(IMOD | IACC | IUPD | ICHG);
E 10
I 10
/*
 * Return the next segment to write.
 */
D 12
static daddr_t
E 12
I 12
D 13
static void
E 13
I 13
void
E 13
E 12
lfs_newseg(fs)
	struct lfs *fs;
{
I 12
	CLEANERINFO *cip;
E 12
	SEGUSE *sup;
	struct buf *bp;
D 12
	int isdirty, segnum, sn;
E 12
I 12
D 47
	int curseg, isdirty, sn;
E 47
I 47
D 61
	int curseg, error, isdirty, sn;
E 61
I 61
	int curseg, isdirty, sn;
E 61
E 47
E 12

D 46
#ifdef VERBOSE
	printf("lfs_newseg\n");
#endif
E 46
D 12
	segnum = datosn(fs, fs->lfs_nextseg);
	LFS_SEGENTRY(sup, fs, segnum, bp);
	sup->su_flags |= SEGUSE_ACTIVE;
E 12
I 12
D 43
	/*
	 * Turn off the active bit for the current segment, turn on the
	 * active and dirty bits for the next segment, update the cleaner
	 * info.  Set the current segment to the next segment, get a new
	 * next segment.
	 */
	LFS_SEGENTRY(sup, fs, datosn(fs, fs->lfs_curseg), bp);
	sup->su_flags &= ~SEGUSE_ACTIVE;
E 12
D 13
	lfs_bwrite(bp);
E 13
I 13
D 14
	LFS_IWRITE(fs, bp);
E 14
I 14
	LFS_UBWRITE(bp);
E 43
I 43
        LFS_SEGENTRY(sup, fs, datosn(fs, fs->lfs_nextseg), bp);
D 52
        sup->su_flags |= SEGUSE_DIRTY;
E 52
I 52
        sup->su_flags |= SEGUSE_DIRTY | SEGUSE_ACTIVE;
E 52
I 49
	sup->su_nbytes = 0;
	sup->su_nsums = 0;
	sup->su_ninos = 0;
E 49
D 47
        LFS_UBWRITE(bp);
E 47
I 47
        (void) VOP_BWRITE(bp);
E 47
E 43
E 14
E 13
D 12
	for (sn = segnum;;) {
E 12
I 12

D 43
	LFS_SEGENTRY(sup, fs, datosn(fs, fs->lfs_nextseg), bp);
D 38
	sup->su_flags |= SEGUSE_ACTIVE | SEGUSE_DIRTY;
E 38
I 38
	sup->su_flags |= SEGUSE_ACTIVE | SEGUSE_DIRTY | SEGUSE_LIVELOG;
E 38
D 13
	lfs_bwrite(bp);
E 13
I 13
D 14
	LFS_IWRITE(fs, bp);
E 14
I 14
	LFS_UBWRITE(bp);
E 14
E 13

E 43
	LFS_CLEANERINFO(cip, fs, bp);
	--cip->clean;
	++cip->dirty;
D 13
	lfs_bwrite(bp);
E 13
I 13
D 14
	LFS_IWRITE(fs, bp);
E 14
I 14
D 47
	LFS_UBWRITE(bp);
E 47
I 47
	(void) VOP_BWRITE(bp);
E 47
E 14
E 13

	fs->lfs_lastseg = fs->lfs_curseg;
	fs->lfs_curseg = fs->lfs_nextseg;
	for (sn = curseg = datosn(fs, fs->lfs_curseg);;) {
E 12
		sn = (sn + 1) % fs->lfs_nseg;
D 12
		if (sn == segnum)
E 12
I 12
		if (sn == curseg)
E 12
			panic("lfs_nextseg: no clean segments");
		LFS_SEGENTRY(sup, fs, sn, bp);
		isdirty = sup->su_flags & SEGUSE_DIRTY;
D 13
		brelse(bp);
E 13
I 13
D 14
		LFS_IRELEASE(fs, bp);
E 14
I 14
		brelse(bp);
E 14
E 13
		if (!isdirty)
			break;
	}
I 43

I 47
	++fs->lfs_nactive;
E 47
E 43
D 12
	return (sntoda(fs, sn));
E 12
I 12
	fs->lfs_nextseg = sntoda(fs, sn);
I 56
#ifdef DOSTATS
	++lfs_stats.segsused;
#endif
E 56
E 12
E 10
D 9
	return (sp);
E 9
E 4
E 2
}

D 13
static void
E 13
I 13
D 38
void
E 38
I 38
int
E 38
E 13
lfs_writeseg(fs, sp)
D 7
	LFS *fs;
E 7
I 7
	struct lfs *fs;
E 7
D 14
	SEGMENT *sp;
E 14
I 14
	struct segment *sp;
E 14
{
I 47
	extern int locked_queue_count;
E 47
I 37
D 39
	USES_VOP_STRATEGY;
E 39
E 37
D 2
	BUF **bpp, *bp;
E 2
I 2
D 9
	BUF **bpp;
E 9
I 9
D 10
	BUF **bpp, *bp, *nbp;
E 10
I 10
D 14
	BUF **bpp, *bp;
E 14
I 14
D 19
	struct buf **bpp, *bp;
E 19
I 19
	struct buf **bpp, *bp, *cbp;
E 19
E 14
E 10
E 9
E 2
D 4
	SEGSUM *ssp;
E 4
	SEGUSE *sup;
D 4
	VNODE *devvp;
	int nblocks, nbuffers, ninode_blocks, nsegsums, nsum_pb;
D 3
	int i, metaoff, nmeta;
I 2
struct buf **xbp; int xi;
E 3
I 3
	int i, metaoff, nmeta, s;
E 4
I 4
D 9
	int i, nblocks, s, (*strategy) __P((BUF *));
E 9
I 9
D 14
	SEGSUM *segp;
E 14
I 14
	SEGSUM *ssp;
E 14
	dev_t i_dev;
D 38
	u_long *datap, *dp;
E 38
E 9
D 19
	void *pmeta;
I 9
D 12
	int flags, i, nblocks, s, (*strategy) __P((BUF *));
E 12
I 12
D 14
	int flags, i, nblocks, s, (*strategy)__P((BUF *));
E 14
I 14
	int flags, i, nblocks, s, (*strategy)__P((struct buf *));
E 19
I 19
D 64
	size_t size;
E 64
D 37
	int ch_per_blk, i, nblocks, num, s, (*strategy)__P((struct buf *));
E 37
I 37
D 38
	int ch_per_blk, i, nblocks, num, s, (*strategy)__P((struct vop_strategy_args *));
E 38
I 38
	u_long *datap, *dp;
D 47
	int ch_per_blk, do_again, i, nblocks, num, s;
E 47
I 47
D 61
	int ch_per_blk, do_again, error, i, nblocks, num, s;
E 61
I 61
D 64
	int ch_per_blk, do_again, i, nblocks, num, s;
E 64
I 64
	int do_again, i, nblocks, s;
E 64
E 61
E 47
	int (*strategy)__P((struct vop_strategy_args *));
I 39
	struct vop_strategy_args vop_strategy_a;
I 43
	u_short ninos;
E 43
E 39
E 38
E 37
	char *p;
I 64
D 66
long *lp;
E 66
E 64
E 19
E 14
E 12
E 9
E 4
E 3
E 2

I 9
D 46
#ifdef VERBOSE
	printf("lfs_writeseg\n");
#endif
E 46
I 14
D 38
	if ((nblocks = sp->cbpp - sp->bpp) == 0)
E 38
I 38
D 47
	/* Checkpoint always writes superblock, even if no data blocks. */
	if ((nblocks = sp->cbpp - sp->bpp) == 0 && !(sp->seg_flags & SEGM_CKP))
E 47
I 47
	/*
	 * If there are no buffers other than the segment summary to write
	 * and it is not a checkpoint, don't do anything.  On a checkpoint,
	 * even if there aren't any buffers, you need to write the superblock.
	 */
D 55
	if ((nblocks = sp->cbpp - sp->bpp) == 1 && !(sp->seg_flags & SEGM_CKP))
E 55
I 55
D 56
	if ((nblocks = sp->cbpp - sp->bpp) == 1) {
		brelvp(*sp->cbpp);
		free(*sp->cbpp, M_SEGMENT);
E 56
I 56
	if ((nblocks = sp->cbpp - sp->bpp) == 1)
E 56
E 55
E 47
E 38
D 42
		return;
E 42
I 42
		return (0);
I 55
D 56
	}
E 56
E 55
E 42

I 52
D 64
	ssp = (SEGSUM *)sp->segsum;

E 64
	/* Update the segment usage information. */
	LFS_SEGENTRY(sup, fs, sp->seg_number, bp);
I 64

	/* Loop through all blocks, except the segment summary. */
	for (bpp = sp->bpp; ++bpp < sp->cbpp; )
		sup->su_nbytes += (*bpp)->b_bcount;

	ssp = (SEGSUM *)sp->segsum;

E 64
	ninos = (ssp->ss_ninos + INOPB(fs) - 1) / INOPB(fs);
D 64
	sup->su_nbytes += nblocks - 1 - ninos << fs->lfs_bshift;
E 64
	sup->su_nbytes += ssp->ss_ninos * sizeof(struct dinode);
	sup->su_nbytes += LFS_SUMMARY_SIZE;
	sup->su_lastmod = time.tv_sec;
	sup->su_ninos += ninos;
	++sup->su_nsums;
	do_again = !(bp->b_flags & B_GATHERED);
	(void)VOP_BWRITE(bp);
E 52
D 18
	/* Update the segment usage information. */
	LFS_SEGENTRY(sup, fs, sp->seg_number, bp);
	sup->su_nbytes += nblocks - 1 << fs->lfs_bshift;
	sup->su_lastmod = time.tv_sec;
	LFS_UBWRITE(bp);

E 18
E 14
D 10
printf("nblocks %d sum bytes %d seg bytes %d\n",
sp->cbpp - sp->bpp, sp->sum_bytes_left, sp->seg_bytes_left);
E 10
E 9
D 5
printf("lfs_writeseg\n");
E 5
D 2
	ssp = sp->segsum;
	nsum_pb = fs->lfs_bsize / LFS_SUMMARY_SIZE;
	/*
	 * This is a hack because we're currently allocating summary segments
	 * in full blocks.  It will go away when we do fragments, when we'll
	 * allocate fragment sized summary blocks.
	 */
	do {
		sp->sum_num++;
		lfs_endsum(fs, sp, 0);
	} while (sp->sum_num % nsum_pb);
	nbuffers = sp->cbpp - sp->bpp;
	nsegsums = (sp->sum_num + nsum_pb - 1) / nsum_pb;
	ninode_blocks = (sp->ninodes + INOPB(fs) - 1)/INOPB(fs);
E 2
I 2
D 4
	fs->lfs_lastseg = sntosa(fs, sp->seg_number);
E 4
I 4
D 12
	/* Update superblock segment address. */
	fs->lfs_lastseg = sntoda(fs, sp->seg_number);
D 10

E 10
D 9
	/* Finish up any summary block. */
E 4
	lfs_endsum(fs, sp, 0);
E 2

D 2
	/* Do checksum for last segment summary */
	ssp->ss_cksum = cksum(&ssp->ss_cksum, 
		    LFS_SUMMARY_SIZE - sizeof(ssp->ss_cksum));

E 2
I 2
D 3
#ifdef HELLNO
E 2
	/* Finish off any inodes */
I 2
	if (sp->ibp)
		brelse(sp->ibp);
#endif
E 2

E 3
	/*
	 * Copy inode and summary block buffer pointers down so they are
D 2
	 * contiguous with the page buffer pointers
E 2
I 2
	 * contiguous with the page buffer pointers.
E 2
	 */
D 2
	nmeta = 1 + ninode_blocks + nsegsums;
E 2
I 2
D 4
	ssp = sp->segsum;
	nsum_pb = fs->lfs_bsize / LFS_SUMMARY_SIZE;
	nbuffers = sp->cbpp - sp->bpp;
I 3
	/*
	 * XXX
	 * Why isn't this (sp->sum_num + nsum_pb - 1) / nsum_pb;
	 */
E 3
	nsegsums = 1 + sp->sum_num / nsum_pb;
	ninode_blocks = (sp->ninodes + INOPB(fs) - 1) / INOPB(fs);
	nmeta = ninode_blocks + nsegsums;
E 2
	metaoff = fs->lfs_ssize - nmeta;
I 2
	nblocks = nbuffers + nmeta;
E 2
	if (sp->bpp + metaoff != sp->cbpp)
D 2
		bcopy(sp->bpp+metaoff, sp->cbpp, sizeof(BUF *)  * nmeta);
E 2
I 2
		bcopy(sp->bpp + metaoff, sp->cbpp, sizeof(BUF *) * nmeta);
	sp->cbpp += nmeta;
E 4
I 4
	(void)next(fs, sp, &nblocks);
	pmeta = (sp->bpp + fs->lfs_ssize) - nblocks;
	if (pmeta != sp->cbpp)
		bcopy(pmeta, sp->cbpp, sizeof(BUF *) * nblocks);
	sp->cbpp += nblocks;
E 9
	nblocks = sp->cbpp - sp->bpp;
E 4
E 2
D 9

D 2
	nblocks = nbuffers + ninode_blocks + nsegsums;
	
E 2
	sup = fs->lfs_segtab + sp->seg_number;
	sup->su_nbytes = nblocks << fs->lfs_bshift;
E 9
I 9
	
	LFS_SEGENTRY(sup, fs, sp->seg_number, bp);
	sup->su_nbytes += LFS_SUMMARY_SIZE + (nblocks - 1 << fs->lfs_bshift);
E 9
	sup->su_lastmod = time.tv_sec;
	sup->su_flags = SEGUSE_DIRTY;
I 9
	lfs_bwrite(bp);
E 9

E 12
	/*
D 2
	 * Since we need to guarantee that our last buffer gets written last,
E 2
I 2
D 9
	 * Since we need to guarantee that the summary block gets written last,
E 2
	 * we issue the writes in two sets.  The first n-1 buffers first, and
D 3
	 * then, after they've completed, the last 1 buffer.  Only when that
E 3
I 3
	 * then, after they've completed, the summary buffer.  Only when that
E 3
D 2
	 * final write completes is the segment actually written.
E 2
I 2
	 * final write completes is the segment valid.
E 9
I 9
D 10
	 * Compute checksum across data and then across summary.
E 10
I 10
D 14
	 * Compute checksum across data and then across summary;
	 * the first block (the summary block) is skipped.
E 14
I 14
	 * Compute checksum across data and then across summary; the first
	 * block (the summary block) is skipped.  Set the create time here
	 * so that it's guaranteed to be later than the inode mod times.
E 14
E 10
	 *
	 * XXX
	 * Fix this to do it inline, instead of malloc/copy.
E 9
E 2
	 */
I 12
D 14
	nblocks = sp->cbpp - sp->bpp;
E 14
E 12
D 4
	devvp = VFSTOUFS(fs->lfs_ivnode->v_mount)->um_devvp;
D 2
/* MIS -- THIS COULD BE BAD IF WE GOT INTERRUPTED IN THE MIDDLE OF THIS */
	fs->lfs_iocount += nblocks - 1;
E 2
I 2
D 3
	/*
	 * Since no writes are yet scheduled, no need to block here; if we
	 * scheduled the writes at multiple points, we'd need an splbio()
	 * here.
	 */
	fs->lfs_iocount = nblocks - 1;
E 3
I 3
	--nblocks;				/* Don't count summary. */
E 4
I 4
D 9
	--nblocks;			/* Don't count last summary block. */
E 9
I 9
D 10
printf("malloc...\n");
E 10
	datap = dp = malloc(nblocks * sizeof(u_long), M_SEGMENT, M_WAITOK);
D 10
	for (bpp = sp->bpp, i = 0; i < nblocks - 1; ++i, ++bpp)
		*dp++ = (*bpp)->b_un.b_words[0];
E 10
I 10
D 52
	for (bpp = sp->bpp, i = nblocks - 1; i--;)
		*dp++ = (*++bpp)->b_un.b_words[0];
E 10
D 13
		
E 13
I 13
D 14

E 13
	segp = (SEGSUM *)sp->segsum;
	segp->ss_datasum = cksum(datap, nblocks * sizeof(u_long));
D 13
	segp->ss_sumsum = cksum(&segp->ss_datasum, 
E 13
I 13
	segp->ss_sumsum = cksum(&segp->ss_datasum,
E 13
	    LFS_SUMMARY_SIZE - sizeof(segp->ss_sumsum));
E 14
I 14
	ssp = (SEGSUM *)sp->segsum;
E 52
I 52
	for (bpp = sp->bpp, i = nblocks - 1; i--;) {
		if ((*++bpp)->b_flags & B_INVAL) {
			if (copyin((*bpp)->b_saveaddr, dp++, sizeof(u_long)))
				panic("lfs_writeseg: copyin failed");
		} else
D 58
			*dp++ = (*bpp)->b_un.b_words[0];
E 58
I 58
			*dp++ = ((u_long *)(*bpp)->b_data)[0];
E 58
	}
E 52
I 15
	ssp->ss_create = time.tv_sec;
E 15
D 45
	ssp->ss_datasum = cksum(datap, nblocks * sizeof(u_long));
E 45
I 45
	ssp->ss_datasum = cksum(datap, (nblocks - 1) * sizeof(u_long));
E 45
	ssp->ss_sumsum =
	    cksum(&ssp->ss_datasum, LFS_SUMMARY_SIZE - sizeof(ssp->ss_sumsum));
D 15
	ssp->ss_create = time.tv_sec;
E 15
E 14
E 9
E 4
D 10

E 10
E 3
E 2
D 9
	sp->nextp = fs->lfs_seglist;
	fs->lfs_seglist = sp;
E 9
I 9
D 12
	(void)free(datap, M_SEGMENT);
E 12
I 12
	free(datap, M_SEGMENT);
E 12
D 10
printf("malloc done\n");
E 10
E 9
D 2
	for (bpp = sp->bpp, i = 0; i < (nblocks - 1); i++) {
		bp = *bpp;
printf("lfs_writeseg: buffer: ino %d lbn %d flags %lx\n", VTOI(bp->b_vp)->i_number, bp->b_lblkno, bp->b_flags);
		(*(devvp->v_op->vop_strategy))(*bpp++);
	}
E 2
I 2
D 51

E 51
I 38
D 52
	/* Update the segment usage information. */
	LFS_SEGENTRY(sup, fs, sp->seg_number, bp);
D 43
	sup->su_nbytes += nblocks - 1 - 
	    (ssp->ss_ninos + INOPB(fs) - 1) / INOPB(fs) << fs->lfs_bshift;
E 43
I 43
	ninos = (ssp->ss_ninos + INOPB(fs) - 1) / INOPB(fs);
	sup->su_nbytes += nblocks - 1 - ninos << fs->lfs_bshift;
E 43
	sup->su_nbytes += ssp->ss_ninos * sizeof(struct dinode);
I 45
	sup->su_nbytes += LFS_SUMMARY_SIZE;
E 45
	sup->su_lastmod = time.tv_sec;
I 43
	sup->su_flags |= SEGUSE_ACTIVE;
	sup->su_ninos += ninos;
	++sup->su_nsums;
I 50
	do_again = !(bp->b_flags & B_GATHERED);
E 50
E 43
D 47
	LFS_UBWRITE(bp);
E 47
I 47
	(void)VOP_BWRITE(bp);
E 52
I 52
#ifdef DIAGNOSTIC
	if (fs->lfs_bfree < fsbtodb(fs, ninos) + LFS_SUMMARY_SIZE / DEV_BSIZE)
		panic("lfs_writeseg: No diskspace for summary");
#endif
E 52
E 47
I 43
	fs->lfs_bfree -= (fsbtodb(fs, ninos) + LFS_SUMMARY_SIZE / DEV_BSIZE);
E 43
D 50
	do_again = !(bp->b_flags & B_GATHERED);
E 50

E 38
I 9
D 19
	/*
	 * When we gathered the blocks for I/O we did not mark them busy or
	 * remove them from the freelist.  As we do this, turn off the B_LOCKED
	 * bit so the future brelse will put them on the LRU list, and add the
	 * B_CALL flags if we're doing a checkpoint so we can count I/O's.  LFS
	 * requires that the super blocks (on checkpoint) be written after all
	 * the segment data.
	 */
E 19
	i_dev = VTOI(fs->lfs_ivnode)->i_dev;
D 37
	strategy = VTOI(fs->lfs_ivnode)->i_devvp->v_op->vop_strategy;
E 37
I 37
	strategy = VTOI(fs->lfs_ivnode)->i_devvp->v_op[VOFFSET(vop_strategy)];
E 37

E 9
D 3
	for (bpp = sp->bpp, i = 0; i < (nblocks - 1); i++, ++bpp)
		/* (*(devvp->v_op->vop_strategy)) */ sdstrategy(*bpp);
E 3
I 3
D 19
	s = splbio();
D 9
	fs->lfs_iocount += nblocks;
E 9
I 9
	if (sp->seg_flags & SEGM_CKP) {
		fs->lfs_iocount += nblocks;
D 10
 		flags = B_BUSY | B_CALL;
E 10
I 10
 		flags = B_ASYNC | B_BUSY | B_CALL;
E 10
	} else
D 10
		flags = B_BUSY;
printf("Nblocks: %d\n", nblocks);
E 10
I 10
		flags = B_ASYNC | B_BUSY;
E 10
	for (bpp = sp->bpp, i = nblocks; i--;) {
		bp = *bpp++;
		bp->b_flags |= flags;
D 10
		bp->b_flags &= ~(B_DONE | B_ERROR | B_READ | B_DELWRI | B_LOCKED);
E 10
I 10
		bp->b_flags &=
		    ~(B_DONE | B_ERROR | B_READ | B_DELWRI | B_LOCKED);
E 10
		bp->b_dev = i_dev;
		bp->b_iodone = lfs_callback;
D 10
#ifdef notdef
printf("bp: %x flags: %x blkno %d lblkno %d\n", bp, bp->b_flags, bp->b_blkno, bp->b_lblkno);
#endif
E 10
		if (!(bp->b_flags & B_NOCACHE)) {
			bremfree(bp);
			reassignbuf(bp, bp->b_vp);
E 19
I 19
	/*
	 * When we simply write the blocks we lose a rotation for every block
	 * written.  To avoid this problem, we allocate memory in chunks, copy
D 56
	 * the buffers into the chunk and write the chunk.  56K was chosen as
	 * some driver/controllers can't handle unsigned 16 bit transfers.
E 56
I 56
	 * the buffers into the chunk and write the chunk.  MAXPHYS is the
	 * largest size I/O devices can handle.
E 56
	 * When the data is copied to the chunk, turn off the the B_LOCKED bit
	 * and brelse the buffer (which will move them to the LRU list).  Add
	 * the B_CALL flag to the buffer header so we can count I/O's for the
	 * checkpoints and so we can release the allocated memory.
	 *
	 * XXX
	 * This should be removed if the new virtual memory system allows us to
	 * easily make the buffers contiguous in kernel memory and if that's
	 * fast enough.
	 */
D 56
#define	LFS_CHUNKSIZE	(56 * 1024)
	ch_per_blk = LFS_CHUNKSIZE / fs->lfs_bsize;
E 56
I 56
D 64
	ch_per_blk = MAXPHYS / fs->lfs_bsize;
E 64
E 56
	for (bpp = sp->bpp, i = nblocks; i;) {
D 64
		num = ch_per_blk;
		if (num > i)
			num = i;
		i -= num;
		size = num * fs->lfs_bsize;

E 64
D 47
		cbp = lfs_newbuf(fs, (*bpp)->b_blkno, 0);
E 47
I 47
D 49
		cbp = lfs_newbuf(fs->lfs_ivnode, (*bpp)->b_blkno, size);
E 49
I 49
		cbp = lfs_newbuf(VTOI(fs->lfs_ivnode)->i_devvp,
D 64
		    (*bpp)->b_blkno, size);
E 64
I 64
		    (*bpp)->b_blkno, MAXPHYS);
E 64
E 49
E 47
		cbp->b_dev = i_dev;
D 47
		cbp->b_flags = B_ASYNC | B_BUSY | B_CALL;
		cbp->b_iodone = lfs_callback;
		cbp->b_saveaddr = cbp->b_un.b_addr;
		cbp->b_un.b_addr = malloc(size, M_SEGMENT, M_WAITOK);
E 47
I 47
		cbp->b_flags |= B_ASYNC | B_BUSY;
I 64
		cbp->b_bcount = 0;
E 64
E 47

		s = splbio();
		++fs->lfs_iocount;
D 58
		for (p = cbp->b_un.b_addr; num--;) {
E 58
I 58
D 64
		for (p = cbp->b_data; num--;) {
E 58
			bp = *bpp++;
E 64
I 64
		for (p = cbp->b_data; i && cbp->b_bcount < MAXPHYS; i--) {
			bp = *bpp;
			if (bp->b_bcount > (MAXPHYS - cbp->b_bcount))
				break;
			bpp++;

E 64
D 47
			bcopy(bp->b_un.b_addr, p, bp->b_bcount);
E 47
I 47
			/*
			 * Fake buffers from the cleaner are marked as B_INVAL.
			 * We need to copy the data from user space rather than
			 * from the buffer indicated.
			 * XXX == what do I do on an error?
			 */
			if (bp->b_flags & B_INVAL) {
				if (copyin(bp->b_saveaddr, p, bp->b_bcount))
					panic("lfs_writeseg: copyin failed");
			} else
D 58
				bcopy(bp->b_un.b_addr, p, bp->b_bcount);
E 58
I 58
				bcopy(bp->b_data, p, bp->b_bcount);
I 64
D 66

E 66
E 64
E 58
E 47
			p += bp->b_bcount;
I 64
			cbp->b_bcount += bp->b_bcount;
E 64
D 38
			bp->b_flags &=
			    ~(B_DONE | B_ERROR | B_READ | B_DELWRI | B_LOCKED);
			if (!(bp->b_flags & B_NOCACHE)) {
E 38
I 38
D 47
			bp->b_flags &= ~(B_DONE | B_ERROR | B_READ | B_DELWRI |
E 47
I 47
			if (bp->b_flags & B_LOCKED)
				--locked_queue_count;
			bp->b_flags &= ~(B_ERROR | B_READ | B_DELWRI |
E 47
			     B_LOCKED | B_GATHERED);
D 47
			if (!(bp->b_flags & (B_NOCACHE | B_INVAL))) {
E 47
I 47
			if (bp->b_flags & B_CALL) {
				/* if B_CALL, it was created with newbuf */
				brelvp(bp);
I 56
				if (!(bp->b_flags & B_INVAL))
D 58
					free(bp->b_un.b_addr, M_SEGMENT);
E 58
I 58
					free(bp->b_data, M_SEGMENT);
E 58
E 56
				free(bp, M_SEGMENT);
			} else {
E 47
E 38
				bremfree(bp);
I 54
				bp->b_flags |= B_DONE;
E 54
				reassignbuf(bp, bp->b_vp);
I 47
				brelse(bp);
E 47
			}
D 47
			brelse(bp);
E 47
E 19
		}
I 50
		++cbp->b_vp->v_numoutput;
E 50
I 19
		splx(s);
D 58
		cbp->b_bcount = p - cbp->b_un.b_addr;
E 58
I 58
D 64
		cbp->b_bcount = p - (char *)cbp->b_data;
E 64
E 58
I 49
		/*
		 * XXXX This is a gross and disgusting hack.  Since these
		 * buffers are physically addressed, they hang off the
		 * device vnode (devvp).  As a result, they have no way
		 * of getting to the LFS superblock or lfs structure to
		 * keep track of the number of I/O's pending.  So, I am
		 * going to stuff the fs into the saveaddr field of
		 * the buffer (yuk).
		 */
		cbp->b_saveaddr = (caddr_t)fs;
E 49
D 37
		(strategy)(cbp);
E 37
I 37
		vop_strategy_a.a_desc = VDESC(vop_strategy);
		vop_strategy_a.a_bp = cbp;
		(strategy)(&vop_strategy_a);
E 37
E 19
	}
E 9
D 19
	splx(s);
E 19
I 4
D 9

	strategy =
	    VFSTOUFS(fs->lfs_ivnode->v_mount)->um_devvp->v_op->vop_strategy;
E 4
	for (bpp = sp->bpp, i = 0; i < nblocks; ++i, ++bpp)
D 4
		(devvp->v_op->vop_strategy)(*bpp);
E 4
I 4
		(strategy)(*bpp);
E 9
I 9
D 13
	
E 13
I 13
D 38

E 13
D 19
	for (bpp = sp->bpp, i = nblocks; i--;)
		(strategy)(*bpp++);
I 18

E 19
	/* Update the segment usage information. */
	LFS_SEGENTRY(sup, fs, sp->seg_number, bp);
	sup->su_nbytes += nblocks - 1 - 
	    (ssp->ss_ninos + INOPB(fs) - 1) / INOPB(fs) << fs->lfs_bshift;
	sup->su_nbytes += ssp->ss_ninos * sizeof(struct dinode);
	sup->su_lastmod = time.tv_sec;
	LFS_UBWRITE(bp);
E 38
I 38
D 42
	return(do_again);
E 42
I 42
D 56
	return (do_again);
E 56
I 56
	/*
	 * XXX
	 * Vinvalbuf can move locked buffers off the locked queue
	 * and we have no way of knowing about this.  So, after
	 * doing a big write, we recalculate how many bufers are
	 * really still left on the locked queue.
	 */
	locked_queue_count = count_lock_queue();
	wakeup(&locked_queue_count);
#ifdef DOSTATS
	++lfs_stats.psegwrites;
	lfs_stats.blocktot += nblocks - 1;
	if (fs->lfs_sp->seg_flags & SEGM_SYNC)
		++lfs_stats.psyncwrites;
	if (fs->lfs_sp->seg_flags & SEGM_CLEAN) {
		++lfs_stats.pcleanwrites;
		lfs_stats.cleanblocks += nblocks - 1;
	}
#endif
	return (lfs_initseg(fs) || do_again);
E 56
E 42
E 38
E 18
I 12
D 14

	/* Update the segment usage information. */
	LFS_SEGENTRY(sup, fs, sp->seg_number, bp);
	sup->su_nbytes += LFS_SUMMARY_SIZE + (nblocks - 1 << fs->lfs_bshift);
	sup->su_lastmod = time.tv_sec;
D 13
	lfs_bwrite(bp);
E 13
I 13
	LFS_IWRITE(fs, bp);
E 14
E 13
E 12
E 9
E 4
E 3
E 2
}

I 2
D 13
static void
E 13
I 13
void
E 13
I 3
D 9
lfs_writesum(fs)
E 9
I 9
D 56
lfs_writesuper(fs, sp)
E 56
I 56
lfs_writesuper(fs)
E 56
E 9
D 7
	LFS *fs;
E 7
I 7
	struct lfs *fs;
I 9
D 14
	SEGMENT *sp;
E 14
I 14
D 56
	struct segment *sp;
E 56
E 14
E 9
E 7
{
I 37
D 39
	USES_VOP_STRATEGY;
E 39
E 37
D 14
	BUF *bp;
E 14
I 14
	struct buf *bp;
E 14
D 9
	SEGMENT *next_sp, *sp;
E 9
I 9
	dev_t i_dev;
E 9
D 4
	VNODE *devvp;
E 4
I 4
D 14
	int (*strategy) __P((BUF *));
E 14
I 14
D 37
	int (*strategy) __P((struct buf *));
E 37
I 37
	int (*strategy) __P((struct vop_strategy_args *));
I 50
	int s;
E 50
I 39
	struct vop_strategy_args vop_strategy_a;
E 39
E 37
E 14
E 4

I 10
D 11
	return;
E 11
E 10
D 5
printf("lfs_writesum\n");
E 5
D 4
	devvp = NULL;
E 4
I 4
D 9
	strategy =
	    VFSTOUFS(fs->lfs_ivnode->v_mount)->um_devvp->v_op->vop_strategy;
E 4
	for (sp = fs->lfs_seglist; sp; sp = next_sp) {
		bp = *(sp->cbpp - 1);
D 4
		if (devvp == NULL)
			devvp = VFSTOUFS(bp->b_vp->v_mount)->um_devvp;
		(devvp->v_op->vop_strategy)(bp);
E 4
I 4
		(strategy)(bp);
E 4
		biowait(bp);
I 5
		bp->b_vp = NULL;		/* No associated vnode. */
		brelse(bp);
E 9
I 9
D 46
#ifdef VERBOSE
	printf("lfs_writesuper\n");
#endif
E 46
D 10
printf("lfs_writesuper\n");
E 10
	i_dev = VTOI(fs->lfs_ivnode)->i_dev;
D 37
	strategy = VTOI(fs->lfs_ivnode)->i_devvp->v_op->vop_strategy;
E 37
I 37
	strategy = VTOI(fs->lfs_ivnode)->i_devvp->v_op[VOFFSET(vop_strategy)];
E 37
E 9

E 5
D 9
		next_sp = sp->nextp;
		free(sp->bpp, M_SEGMENT);
		free(sp, M_SEGMENT);
	}
I 4
	/* Segment list is done. */
	fs->lfs_seglist = NULL;
E 4
}

static void
E 3
D 4
lfs_writesuper(fs, sp)
E 4
I 4
lfs_writesuper(fs)
E 4
D 7
	LFS *fs;
E 7
I 7
	struct lfs *fs;
E 7
D 4
	SEGMENT *sp;
E 4
{
	BUF *bp;
D 4
	VNODE *devvp;
E 4
I 4
	int (*strategy) __P((BUF *));
E 4

D 5
printf("lfs_writesuper\n");
E 5
I 5
	strategy =
	    VFSTOUFS(fs->lfs_ivnode->v_mount)->um_devvp->v_op->vop_strategy;

E 9
E 5
D 3
	/* Wait for segment write to complete */
	/* XXX probably should do this biowait(*(sp->cbpp - 1)); */

E 3
D 4
	/* Get a buffer for the super block */
E 4
I 4
	/* Checksum the superblock and copy it into a buffer. */
E 4
D 7
	fs->lfs_cksum = cksum(fs, sizeof(LFS) - sizeof(fs->lfs_cksum));
E 7
I 7
	fs->lfs_cksum = cksum(fs, sizeof(struct lfs) - sizeof(fs->lfs_cksum));
E 7
D 9
	bp = lfs_newbuf(fs, fs->lfs_sboffs[0], LFS_SBPAD);
D 3
	bp->b_flags &= ~B_CALL;
	bp->b_vp = NULL;
	bp->b_iodone = NULL;
E 3
D 7
	bcopy(fs, bp->b_un.b_lfs, sizeof(LFS));
E 7
I 7
	bcopy(fs, bp->b_un.b_lfs, sizeof(struct lfs));
E 9
I 9
D 19
	bp = lfs_newbuf(fs, sp, fs->lfs_sboffs[0], LFS_SBPAD);
E 19
I 19
D 47
	bp = lfs_newbuf(fs, fs->lfs_sboffs[0], LFS_SBPAD);
E 47
I 47
D 49
	bp = lfs_newbuf(fs->lfs_ivnode, fs->lfs_sboffs[0], LFS_SBPAD);
E 49
I 49
	bp = lfs_newbuf(VTOI(fs->lfs_ivnode)->i_devvp, fs->lfs_sboffs[0],
	    LFS_SBPAD);
E 49
E 47
E 19
D 58
	*bp->b_un.b_lfs = *fs;
E 58
I 58
	*(struct lfs *)bp->b_data = *fs;
E 58
E 9
E 7

D 4
	/* Write the first superblock; wait. */
	devvp = VFSTOUFS(fs->lfs_ivnode->v_mount)->um_devvp;
D 3
#ifdef MOVETONEWBUF
	bp->b_dev = devvp->v_rdev;
#endif
	(*devvp->v_op->vop_strategy)(bp);
E 3
I 3
	(devvp->v_op->vop_strategy)(bp);
E 4
I 4
D 5
	/* Write the first superblock. */
	strategy =
	    VFSTOUFS(fs->lfs_ivnode->v_mount)->um_devvp->v_op->vop_strategy;
E 5
I 5
D 56
	/* Write the first superblock (wait). */
E 56
I 56
	/* XXX Toggle between first two superblocks; for now just write first */
E 56
I 9
	bp->b_dev = i_dev;
D 10
	bp->b_flags &= ~(B_DONE | B_ERROR | B_READ | B_DELWRI);
E 10
D 56
	bp->b_flags |= B_BUSY;
I 10
D 47
	bp->b_flags &= ~(B_DONE | B_ERROR | B_READ | B_DELWRI);
E 47
I 47
	bp->b_flags &= ~(B_DONE | B_CALL | B_ERROR | B_READ | B_DELWRI);
E 56
I 56
	bp->b_flags |= B_BUSY | B_CALL | B_ASYNC;
	bp->b_flags &= ~(B_DONE | B_ERROR | B_READ | B_DELWRI);
	bp->b_iodone = lfs_supercallback;
E 56
E 47
E 10
E 9
E 5
D 37
	(strategy)(bp);
E 37
I 37
	vop_strategy_a.a_desc = VDESC(vop_strategy);
	vop_strategy_a.a_bp = bp;
I 50
	s = splbio();
D 56
	bp->b_vp->v_numoutput += 2;
E 56
I 56
	++bp->b_vp->v_numoutput;
E 56
	splx(s);
E 50
	(strategy)(&vop_strategy_a);
E 37
E 4
E 3
D 56
	biowait(bp);
I 9
D 10
printf("lfs_writesuper: first write returned\n");
E 10
E 9
D 4
	
	/* Now, write the second one for which we don't have to wait */
E 4
I 4

D 5
	/* Write the second superblock. */
E 5
I 5
	/* Write the second superblock (don't wait). */
E 5
E 4
D 9
	bp->b_flags &= ~B_DONE;
I 5
	bp->b_flags |= B_ASYNC;
	bp->b_vp = NULL;			/* No associated vnode. */
E 9
E 5
	bp->b_blkno = bp->b_lblkno = fs->lfs_sboffs[1];
I 10
D 47
	bp->b_flags |= B_ASYNC | B_BUSY;
E 47
I 47
	bp->b_flags |= B_CALL | B_ASYNC | B_BUSY;
E 47
E 10
I 9
	bp->b_flags &= ~(B_DONE | B_ERROR | B_READ | B_DELWRI);
I 47
	bp->b_iodone = lfs_supercallback;
E 47
E 9
D 3
	(*devvp->v_op->vop_strategy)(bp);
E 3
I 3
D 4
	(devvp->v_op->vop_strategy)(bp);
E 4
I 4
D 37
	(strategy)(bp);
E 37
I 37
	(strategy)(&vop_strategy_a);
E 56
E 37
E 4
D 5

	bp->b_vp = NULL;			/* No associated vnode. */
I 4
	biowait(bp);
E 4
E 3
	brelse(bp);
I 4
printf("lfs_writesuper is returning\n");
E 5
E 4
}

D 4
/* Block match routines used when traversing the dirty block chain. */
E 4
I 4
/*
 * Logical block number match routines used when traversing the dirty block
 * chain.
 */
D 6
int
E 6
I 6
D 13
static int
E 6
E 4
D 9
match_data(bp)
E 9
I 9
match_data(fs, bp)
E 13
I 13
int
lfs_match_data(fs, bp)
E 13
	struct lfs *fs;
E 9
D 14
	BUF *bp;
E 14
I 14
	struct buf *bp;
E 14
{
D 4
	return(bp->b_lblkno >= 0);
E 4
I 4
	return (bp->b_lblkno >= 0);
E 4
}
D 3

E 3

I 4
D 6
int
E 6
I 6
D 13
static int
E 6
E 4
D 9
match_dindir(bp)
E 9
I 9
match_indir(fs, bp)
E 13
I 13
int
lfs_match_indir(fs, bp)
E 13
	struct lfs *fs;
E 9
D 14
	BUF *bp;
E 14
I 14
	struct buf *bp;
E 14
{
D 4
	return(bp->b_lblkno == D_INDIR);
E 4
I 4
D 9
	return (bp->b_lblkno == D_INDIR);
E 9
I 9
	int lbn;

	lbn = bp->b_lblkno;
	return (lbn < 0 && (-lbn - NDADDR) % NINDIR(fs) == 0);
E 9
E 4
}

E 2
D 9
/*
I 2
 * These are single indirect blocks.  There are three types:
D 4
 * 	the one in the inode (address S_INDIR = -1).
 * 	the ones that hang off of D_INDIR the double indirect in the inode.
 * 		these all have addresses in the range -2NINDIR to -(3NINDIR-1)
 *	the ones that hang off of double indirect that hang off of the
 *		triple indirect.  These all have addresses < -(NINDIR^2).
 * Since we currently don't support, triple indirect blocks, this gets simpler.
 * We just need to look for block numbers less than -NIADDR.
E 4
I 4
 *
 * the one in the inode (lblkno == S_INDIR, or -1).
 * the ones that hang off of the double indirect in the inode (D_INDIR);
 *    these all have addresses in the range -2NINDIR to -(3NINDIR-1).
 * the ones that hang off of the double indirect that hangs off of the
 *    triple indirect.  These all have addresses < -(NINDIR^2).
 *
 * Since we currently don't support triple indirect blocks, this gets
 * simpler, and we just look for block numbers less than -NIADDR.
E 4
 */
E 9
I 4
D 6
int
E 6
I 6
D 13
static int
E 6
E 4
D 9
match_indir(bp)
E 9
I 9
match_dindir(fs, bp)
E 13
I 13
int
lfs_match_dindir(fs, bp)
E 13
	struct lfs *fs;
E 9
D 14
	BUF *bp;
E 14
I 14
	struct buf *bp;
E 14
{
D 4
	return(bp->b_lblkno == S_INDIR || bp->b_lblkno < -NIADDR);
E 4
I 4
D 9
	return (bp->b_lblkno == S_INDIR || bp->b_lblkno < -NIADDR);
E 9
I 9
	int lbn;

	lbn = bp->b_lblkno;
	return (lbn < 0 && (-lbn - NDADDR) % NINDIR(fs) == 1);
E 9
}

D 9
/* Get the next inode/summary block. */
static daddr_t
next(fs, sp, nbp)
E 9
I 9
D 13
static int
match_tindir(fs, bp)
E 13
I 13
int
lfs_match_tindir(fs, bp)
E 13
E 9
D 7
	LFS *fs;
E 7
I 7
	struct lfs *fs;
E 7
D 9
	SEGMENT *sp;
	int *nbp;
E 9
I 9
D 14
	BUF *bp;
E 14
I 14
	struct buf *bp;
E 14
E 9
{
D 9
	int nblocks, nino_blocks, nseg_blocks, sums_per_block;
E 9
I 9
	int lbn;
E 9

D 9
	/* Fs blocks allocated to summary blocks. */
	sums_per_block = fs->lfs_bsize / LFS_SUMMARY_SIZE;
	nseg_blocks = (sp->nsums + sums_per_block - 1) / sums_per_block;
E 9
I 9
	lbn = bp->b_lblkno;
	return (lbn < 0 && (-lbn - NDADDR) % NINDIR(fs) == 2);
}
E 9

D 9
	/* Fs blocks allocated to inodes. */
	nino_blocks = (sp->ninodes + INOPB(fs) - 1) / INOPB(fs);
E 9
I 9
/*
 * Allocate a new buffer header.
 */
D 13
static BUF *
E 13
I 13
D 14
BUF *
E 14
I 14
struct buf *
E 14
E 13
D 19
lfs_newbuf(fs, sp, daddr, size)
E 19
I 19
D 47
lfs_newbuf(fs, daddr, size)
E 19
	struct lfs *fs;
E 47
I 47
lfs_newbuf(vp, daddr, size)
	struct vnode *vp;
E 47
D 14
	SEGMENT *sp;
E 14
I 14
D 19
	struct segment *sp;
E 19
E 14
D 63
	daddr_t daddr;
E 63
I 63
	ufs_daddr_t daddr;
E 63
	size_t size;
{
D 14
	BUF *bp;
E 14
I 14
	struct buf *bp;
I 47
	size_t nbytes;
E 47
E 14
E 9

D 9
	/* Total number of fs blocks allocated. */
	nblocks = nseg_blocks + nino_blocks;
E 9
I 9
D 46
#ifdef VERBOSE
	printf("lfs_newbuf\n");
#endif
E 46
D 47
	bp = getnewbuf();
	bremhash(bp);
	bgetvp(fs->lfs_ivnode, bp);
	bp->b_bcount = 0;
E 47
I 47
	nbytes = roundup(size, DEV_BSIZE);
D 56
	bp = malloc(sizeof(struct buf) + nbytes, M_SEGMENT, M_WAITOK);
D 50
	bzero(bp, sizeof(struct buf));
E 50
I 50
	bzero(bp, sizeof(struct buf) + nbytes);
E 56
I 56
	bp = malloc(sizeof(struct buf), M_SEGMENT, M_WAITOK);
	bzero(bp, sizeof(struct buf));
	if (nbytes)
D 58
		bp->b_un.b_addr =
		    malloc(nbytes, M_SEGMENT, M_WAITOK);
E 58
I 58
		bp->b_data = malloc(nbytes, M_SEGMENT, M_WAITOK);
E 58
E 56
E 50
	bgetvp(vp, bp);
D 56
	bp->b_un.b_addr = (caddr_t)(bp + 1);
E 56
	bp->b_bufsize = size;
	bp->b_bcount = size;
E 47
	bp->b_lblkno = daddr;
	bp->b_blkno = daddr;
	bp->b_error = 0;
	bp->b_resid = 0;
D 19
	allocbuf(bp, size);
E 19
I 19
D 47
	if (size)
		allocbuf(bp, size);
E 19
	bp->b_flags |= B_NOCACHE;
I 19
	bp->b_saveaddr = NULL;
E 19
I 10
	binshash(bp, &bfreelist[BQ_AGE]);
E 47
I 47
	bp->b_iodone = lfs_callback;
D 48
	bp->b_flags |= B_CALL | B_NOCACHE;
E 48
I 48
	bp->b_flags |= B_BUSY | B_CALL | B_NOCACHE;
E 48
E 47
E 10
	return (bp);
}
E 9

D 9
	if (nbp)
		*nbp = nblocks;
E 9
I 9
D 13
/*
 * The buffer cache callback routine.  
 */
static int					/* XXX should be void */
E 13
I 13
D 23
int						/* XXX should be void */
E 23
I 23
void
E 23
E 13
lfs_callback(bp)
D 14
	BUF *bp;
E 14
I 14
	struct buf *bp;
E 14
{
	struct lfs *fs;
E 9

D 9
	/*
	 * The disk address of the new inode/summary block is the address of
	 * the start of the segment after this one minus the number of blocks
	 * that we've already used.
	 */
	return (sntoda(fs, sp->seg_number + 1) - fsbtodb(fs, nblocks + 1));
E 9
I 9
D 10
#ifdef VERBOSE
printf("lfs_callback\n");
#endif
E 10
D 49
	fs = VFSTOUFS(bp->b_vp->v_mount)->um_lfs;
E 49
I 49
	fs = (struct lfs *)bp->b_saveaddr;
E 49
#ifdef DIAGNOSTIC
	if (fs->lfs_iocount == 0)
		panic("lfs_callback: zero iocount\n");
#endif
	if (--fs->lfs_iocount == 0)
D 10
{
printf("io: wakeup call\n");
E 10
D 17
		wakeup(&fs->lfs_iocount);
E 17
I 17
D 19
		wakeup((caddr_t)&fs->lfs_iocount);
E 19
I 19
		wakeup(&fs->lfs_iocount);
E 19
E 17
D 10
}
E 10
I 10

I 19
D 47
	if (bp->b_saveaddr) {
		free(bp->b_un.b_addr, M_SEGMENT);
		bp->b_un.b_addr = bp->b_saveaddr;
I 20
		bp->b_saveaddr = NULL;
E 20
	}
E 19
E 10
	brelse(bp);
E 47
I 47
	brelvp(bp);
I 56
D 58
	free(bp->b_un.b_addr, M_SEGMENT);
E 58
I 58
	free(bp->b_data, M_SEGMENT);
E 58
E 56
	free(bp, M_SEGMENT);
E 47
E 9
E 4
}

I 47
void
lfs_supercallback(bp)
	struct buf *bp;
{
	brelvp(bp);
I 56
D 58
	free(bp->b_un.b_addr, M_SEGMENT);
E 58
I 58
	free(bp->b_data, M_SEGMENT);
E 58
E 56
	free(bp, M_SEGMENT);
}

E 47
/*
E 2
 * Shellsort (diminishing increment sort) from Data Structures and
 * Algorithms, Aho, Hopcraft and Ullman, 1983 Edition, page 290;
 * see also Knuth Vol. 3, page 84.  The increments are selected from
 * formula (8), page 95.  Roughly O(N^3/2).
 */
/*
 * This is our own private copy of shellsort because we want to sort
 * two parallel arrays (the array of buffer pointers and the array of
 * logical block numbers) simultaneously.  Note that we cast the array
 * of logical block numbers to a unsigned in this routine so that the
 * negative block numbers (meta data blocks) sort AFTER the data blocks.
 */
D 13
static void
shellsort(bp_array, lb_array, nmemb)
E 13
I 13
void
lfs_shellsort(bp_array, lb_array, nmemb)
E 13
D 14
	BUF **bp_array;
E 14
I 14
	struct buf **bp_array;
E 14
D 2
	u_long *lb_array;
E 2
I 2
D 63
	daddr_t *lb_array;
E 63
I 63
	ufs_daddr_t *lb_array;
E 63
E 2
	register int nmemb;
{
	static int __rsshell_increments[] = { 4, 1, 0 };
	register int incr, *incrp, t1, t2;
D 14
	BUF *bp_temp;
E 14
I 14
	struct buf *bp_temp;
E 14
	u_long lb_temp;

	for (incrp = __rsshell_increments; incr = *incrp++;)
		for (t1 = incr; t1 < nmemb; ++t1)
			for (t2 = t1 - incr; t2 >= 0;)
				if (lb_array[t2] > lb_array[t2 + incr]) {
					lb_temp = lb_array[t2];
					lb_array[t2] = lb_array[t2 + incr];
					lb_array[t2 + incr] = lb_temp;
					bp_temp = bp_array[t2];
					bp_array[t2] = bp_array[t2 + incr];
					bp_array[t2 + incr] = bp_temp;
					t2 -= incr;
				} else
					break;
}
I 47

I 56
/*
D 60
 * Check VXLOCK.  Return 1 if the vnode is locked.  Otherwise, bump the
 * ref count, removing the vnode from the free list if it is on it.
E 60
I 60
 * Check VXLOCK.  Return 1 if the vnode is locked.  Otherwise, vget it.
E 60
 */
lfs_vref(vp)
	register struct vnode *vp;
{
I 65
	struct proc *p = curproc;	/* XXX */
E 65
D 60
	register struct vnode *vq;
	extern struct vnode *vfreeh;
	extern struct vnode **vfreet;
E 60

D 65
	if (vp->v_flag & VXLOCK)
E 65
I 65
	if (vp->v_flag & VXLOCK)	/* XXX */
E 65
		return(1);
D 60

	if (vp->v_usecount == 0) {
		if (vq = vp->v_freef)
			vq->v_freeb = vp->v_freeb;
		else
			vfreet = vp->v_freeb;
		*vp->v_freeb = vq;
		vp->v_freef = NULL;
		vp->v_freeb = NULL;
	}
	VREF(vp);
	return (0);
E 60
I 60
D 65
	return (vget(vp, 0));
E 65
I 65
	return (vget(vp, 0, p));
E 65
E 60
}

I 66
/*
 * This is vrele except that we do not want to VOP_INACTIVE this vnode. We
 * inline vrele here to avoid the vn_lock and VOP_INACTIVE call at the end.
 */
E 66
void
lfs_vunref(vp)
	register struct vnode *vp;
{
D 60
	extern struct vnode *vfreeh;
	extern struct vnode **vfreet;
E 60
I 60
D 66
	extern int lfs_no_inactive;
E 66
I 66
	struct proc *p = curproc;				/* XXX */
	extern struct simplelock vnode_free_list_slock;		/* XXX */
	extern TAILQ_HEAD(freelst, vnode) vnode_free_list;	/* XXX */
E 66
E 60

I 66
	simple_lock(&vp->v_interlock);
	vp->v_usecount--;
	if (vp->v_usecount > 0) {
		simple_unlock(&vp->v_interlock);
		return;
	}
E 66
D 60
	--vp->v_usecount;

E 60
	/*
D 60
	 * return to free list
E 60
I 60
D 66
	 * This is vrele except that we do not want to VOP_INACTIVE
	 * this vnode. Rather than inline vrele here, we use a global
	 * flag to tell lfs_inactive not to run. Yes, its gross.
E 66
I 66
	 * insert at tail of LRU list
E 66
E 60
	 */
D 60
	if (vp->v_usecount == 0) {
		*vfreet = vp;
		vp->v_freeb = vfreet;
		vp->v_freef = NULL;
		vfreet = &vp->v_freef;
	}
	return;
E 60
I 60
D 66
	lfs_no_inactive = 1;
	vrele(vp);
	lfs_no_inactive = 0;
E 66
I 66
	simple_lock(&vnode_free_list_slock);
	TAILQ_INSERT_TAIL(&vnode_free_list, vp, v_freelist);
	simple_unlock(&vnode_free_list_slock);
	simple_unlock(&vp->v_interlock);
E 66
E 60
}
E 56
E 47
I 2
D 6
#endif /* LOGFS */
E 6
E 2
E 1
