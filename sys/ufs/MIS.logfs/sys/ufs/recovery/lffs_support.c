#include <stdio.h>
#include <stddef.h>
#include <db.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/time.h>
#include <ufs/ffs/fs.h>
#include <ufs/ufs/dinode.h>
#include <fsck.h>
#include "lffs_globs.h"

/*
 * Set or Clear inode bitmap and update all cylinder group and
 * file system summary information.  
 */
lffs_inode_setclr(ino_t ino, int isdir, int allocit)
{
	struct bufarea *bp;
	struct cg *cgp;
	char *mapp;
	int cg, bit_is_set, bitpos;
	int bbase, blk;
	int delta;

	if (verbose)
		fprintf(stderr, "lffs_inode_setclr: %sallocating inode %d\n",
		    allocit ? "" : "de", ino);
	/*
	 * Read the cylinder group block.  We need to fix the inode
	 * bitmap and the totals of inodes and directories.
	 */
	bread(fswritefd, (char *) bp,
	    cgtod(fs, (cg = itog(fs, ino))), fs->fs_bsize);
	cgp = bp->b_un.b_cg;
	mapp = cg_inosused(cgp);
	bitpos = ino % fs->fs_ipg;
	bit_is_set = isset(mapp, bitpos);

	delta = 0;
	if (!allocit && bit_is_set) {
		clrbit(mapp, bitpos);
		delta = 1;
	} else if (allocit && !bit_is_set) {
		setbit(mapp, bitpos);
		delta = -1;
	}
	if (delta) {
		cgp->cg_cs.cs_nifree += delta;
		fs->fs_cstotal.cs_nifree += delta;
		fs->fs_cs(fs, cg).cs_nifree += delta;
		if (isdir) {
			cgp->cg_cs.cs_ndir -= delta;
			fs->fs_cstotal.cs_ndir -= delta;
			fs->fs_cs(fs, cg).cs_ndir -= delta;
		}
		bwrite(bp);
	}
}

/*
 * Set or Clear frag bitmap and update all cylinder group and
 * file system summary information.  For block bitmaps, a 1
 * indicates free and a 0 indicates inuse.
 */
void
lffs_frag_setclr(daddr_t start, int nfrags, int allocit)
{
	struct bufarea *bp;
	struct cg *cgp;
	char *mapp;
	int cg, bit_is_clr, bitpos, i;
	int bbase, blk;
	int delta;
	int wasblock;

	if (verbose)
		fprintf(stderr,
		    "lffs_frag_setclr: %sallocating %d frags at %d\n",
		    allocit ? "" : "de", nfrags, start);

	/*
	 * Read the cylinder group block. 
	 */
	bread(fswritefd, (char *) bp,
	    cgtod(fs, dtog(fs, start)), fs->fs_bsize);
	cgp = bp->b_un.b_cg;
	mapp = cg_blksfree(cgp);

	delta = 0;	/* Counts FREE things */
	start = dtogd(fs, start);

	/* Do fragment accounting; if no delta; no need to write */
	bbase = start - fragnum(fs, start);
	wasblock = ffs_isblock(fs, mapp, fragstoblks(fs, bbase));
	if (!wasblock) {
		/* Account for "undoing" the entire block. */
		blk = blkmap(fs, mapp, bbase);
		ffs_fragacct(fs, blk, cgp->cg_frsum, -1);
	}

	for (i = 0, bitpos = start; i < nfrags; i++, bitpos++) {
		bit_is_clr = isclr(mapp, bitpos);

		if (!allocit && bit_is_clr) {
			setbit(mapp, bitpos);
			delta++;
		} else if (allocit && !bit_is_clr) {
			clrbit(mapp, bitpos);
			delta--;
		}
	}

	if (delta) {
		if (delta == fs->fs_frag) {
			delta = delta > 0 ? 1 : -1;
			/* Processed entire block */
			cgp->cg_cs.cs_nbfree += delta;
			fs->fs_cstotal.cs_nbfree += delta;
			fs->fs_cs(fs, cg).cs_nbfree += delta;
			cg_blks(fs, cgp, cg)[cbtorpos(fs, start)] += delta;
			cg_blktot(cgp)[cg] += delta;
		} else {
			/* Processed some fragments */
			if (wasblock) {
				assert(delta < 0);
				/* If we split up a block, do accounting. */
				cgp->cg_cs.cs_nbfree -= 1;
				fs->fs_cstotal.cs_nbfree -= 1;
				fs->fs_cs(fs, cg).cs_nbfree -= 1;
				cg_blks(fs, cgp, cg)[cbtorpos(fs, start)] -= 1;
				cg_blktot(cgp)[cg] -= 1;
				delta += fs->fs_frag;
			}
			/* Check if we created a new block */
			if (ffs_isblock(fs, mapp, fragstoblks(fs, bbase))) {
				assert(delta > 0);
				/* If we created a new block, count it. */
				cgp->cg_cs.cs_nbfree += 1;
				fs->fs_cstotal.cs_nbfree += 1;
				fs->fs_cs(fs, cg).cs_nbfree += 1;
				cg_blks(fs, cgp, cg)[cbtorpos(fs, start)] += 1;
				cg_blktot(cgp)[cg] += 1;
				delta -= fs->fs_frag;
			}
			cgp->cg_cs.cs_nffree += delta;
			fs->fs_cstotal.cs_nffree += delta;
			fs->fs_cs(fs, cg).cs_nffree += delta;
		}
	}
	if (!ffs_isblock(fs, mapp, fragstoblks(fs, bbase))) {
		/* Account for "doing" the entire block. */
		blk = blkmap(fs, mapp, bbase);
		ffs_fragacct(fs, blk, cgp->cg_frsum, 1);
	}

	if (delta)
		dirty(bp);
}

daddr_t
lffs_findblock(int nfrags, daddr_t pref)
{
	struct bufarea *bp;
	struct cg *cgp;
	char *mapp;
	int cg, i, j, k, frags;

	if (nfrags <= 0 || nfrags > fs->fs_frag)
		return (0);

	cg = dtog(fs, pref);
	do {
		bread(fswritefd, (char *) bp, cgtod(fs, cg), fs->fs_bsize);
		cgp = bp->b_un.b_cg;
		mapp = cg_blksfree(cgp);

		for (i = 0; i < cgp->cg_ndblk; i += fs->fs_frag) {
			for (j = 0; j <= fs->fs_frag - nfrags; j++) {

				/* If block is inuse, cannot start here. */
				if (isclr(mapp, i + j))
					continue;

				/* Check for length. */
				for (k = 1; k < nfrags; k++)
					if (isclr(mapp, i + j + k))
						break;

				/* If this wasn't long enough, keep looping. */
				if (k < frags) {
					j += k;
					continue;
				}

				/* Found some space. */
				if (verbose)
					fprintf(stderr, "%s %d frags at %d\n",
					    "lffs_findblock: found", nfrags,
					    cg * fs->fs_fpg + i + j);
				return (cg * fs->fs_fpg + i + j);
			}
		}
		cg = (cg + 1) % fs->fs_ncg;
	} while (cg != dtog(fs, pref));

	return(0);
}

int
lffs_checkfrag(int nfrags, daddr_t start)
{
	struct bufarea *bp;
	char *mapp;
	struct cg *cgp;
	int i, ret, bitpos;

	bread(fswritefd, (char *) bp,
	    cgtod(fs, dtog(fs, start)), fs->fs_bsize);
	cgp = bp->b_un.b_cg;
	mapp = cg_blksfree(cgp);

	bitpos = dtogd(fs, start);
	ret = 1;

	for (i = 0; i < nfrags; i++)
		ret = ret && isclr(mapp, bitpos + i);
	
	return(ret);
}
