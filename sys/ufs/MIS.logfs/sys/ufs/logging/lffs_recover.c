#include <stddef.h>
#include <db.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/signal.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/proc.h>
#include <sys/dirent.h>
#include <ufs/ufs/dir.h>
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#include <ufs/ffs/fs.h>
#include <fsck.h>
#include <sys/queue.h>
#include "lffs.h"
#include "lffs_auto.h"
#include "lffs_roll.h"
#include "lffs_globs.h"

#define FATAL_DADDR	-1

int adddir_space(DB *dbp, struct dinode *dip);
int check_for_abort(DB *dbp, u_long op, ino_t ino, long gen);
void name_recover(DB *dbp, ino_t dir_ino, long dir_gen, ino_t f_ino,
    char *f_name, long f_mode, struct timeval *optime, int add_name,
    int undo);
void recover_fail(void);

/*
 * When we encounter a logical block allocation, we create
 * an entry on the logical block list so that we can correctly
 * pair up the logical allocation with the physical allocation.
 */
struct logical_block {
	TAILQ_ENTRY(logical_block) links;
	ino_t	inum;
	int	op;
	daddr_t	lbn;
};
TAILQ_HEAD(lhead, logical_block) logical_head;

/*
 * Inode allocation is recorded so that it can be associated with the
 * correct create operation.
 */
struct ialloc_block {
	TAILQ_ENTRY(ialloc_block) links;
	ino_t inum;
};
TAILQ_HEAD(ihead, ialloc_block) ialloc_head;

/*
 * Directory creations are recorded so that we can perform removal
 * of deleted directories if the system crashed after the rmdir, but
 * before the actual directory has been removed.
 */
struct mkdir_entry {
	TAILQ_ENTRY(mkdir_entry) links;
	ino_t	dot_ino;
	ino_t	dot_dot_ino;
};
TAILQ_HEAD(mhead, mkdir_entry) mkdir_head;
/*
 * Symlinks that have names that do not fit into the inode will
 * have an associated ALLOC operation.  When we process the
 * SYMLINK record we need to save the new name and inode number
 * in case the alloc log record was never written.
 */
struct symlink_entry {
	TAILQ_ENTRY(symlink_entry) links;
	ino_t	link_ino;
	int	length;
	char	*name;
};
TAILQ_HEAD(shead, symlink_entry) symlink_head;

/*
 * Deletions are recorded in a list so that if the corresponding
 * deallocation operations are not present in the log, we can
 * process them correctly.
 */
struct unlink_entry {
	TAILQ_ENTRY(unlink_entry) links;
	ino_t	unlink_ino;
	long	unlink_gen;
	struct dinode din;
};
TAILQ_HEAD(uhead, unlink_entry) unlink_head;

void
init_recovery()
{
	TAILQ_INIT(&logical_head);
	TAILQ_INIT(&ialloc_head);
	TAILQ_INIT(&unlink_head);
	TAILQ_INIT(&mkdir_head);
	TAILQ_INIT(&symlink_head);
}

void
CREATE_RECOVER(DB *dbp, CREATE_args *argp)
{
	struct bufarea *bp;
	struct mkdir_entry *mp;
	struct slot freedir;
	struct dirent *dp;
	int undo, len;
	ino_t ino;
	struct dinode *dip;

	if (verbose)
		printf("Recovering Create\n");
	ino = argp->new_inum;
	undo =  check_for_abort(dbp, argp->type, ino,  argp->new_gen);

	/* First, remove corresponding IALLOC and set bitmap. */
	remove_ialloc(argp->new_inum);

	lffs_inode_setclr(ino, argp->type == LFFS_MKDIR, !undo);

	/* Now get the new inode */
	dip = ginode(argp->new_inum);
	if (dip->di_gen < argp->new_gen && !undo) {
		if (verbose)
			printf("\trecreating newly created inode %d\n",
			    argp->new_inum);
		if (!no_update) {
			clearinode(dip);
			dip->di_mode = argp->new_mode;
			dip->di_nlink = argp->type == LFFS_MKDIR ? 2 : 1;;
			TIMEVAL_TO_TIMESPEC(&argp->time, &dip->di_atime);
			TIMEVAL_TO_TIMESPEC(&argp->time, &dip->di_mtime);
			TIMEVAL_TO_TIMESPEC(&argp->time, &dip->di_ctime);
			dip->di_gen = argp->new_gen;
			dip->di_uid = argp->new_uid;
			dip->di_gid = argp->new_gid;
			inodirty();
		}

		if (argp->type == LFFS_MKDIR) {
			mp = (void *) malloc(sizeof(struct mkdir_entry));
			if (mp == NULL)
				recover_fail();
			mp->dot_ino = argp->new_inum;
			mp->dot_dot_ino = argp->dir_inum;
			TAILQ_INSERT_TAIL(&mkdir_head, mp, links);
		}
	} else if (dip->di_gen == argp->new_gen && undo) {
		/* File exists and it should not; undo it. */
		if (verbose)
			printf("\trecovering undo of inode create: %d\n",
			    argp->new_inum);
		if (!no_update) {
			bzero(dip, sizeof(struct dinode));
			inodirty();
		}
	}

	name_recover(dbp, argp->dir_inum, argp->dir_gen, argp->new_inum,
	    argp->new_name, argp->new_mode, &argp->time, 1 /* add */, undo);
	free(argp);
}

void
IALLOC_RECOVER(DB *dbp, IALLOC_args *argp)
{
	struct ialloc_block *iap;

	if (verbose)
		printf("recovering ialloc %d\n", argp->new_inum);

	iap = (void *)malloc(sizeof(struct ialloc_block));
	if (iap == NULL)
		recover_fail();

	iap->inum = argp->new_inum;
	TAILQ_INSERT_TAIL(&ialloc_head, iap, links);
	free(argp);
}

void
REMOVE_RECOVER(DB *dbp, REMOVE_args *argp)
{
	struct dirent *dirp;
	struct unlink_entry *uep;
	struct dinode *dip;
	struct slot loc;
	ino_t ino;
	int len, undo;

	ino = argp->rem_dip->di_inumber;
	undo =  check_for_abort(dbp, argp->type, ino, argp->rem_dip->di_gen);

	if (verbose)
		printf("recovering remove of inode %d\n", ino);

	/* First update the inode bitmap. */
	lffs_inode_setclr(ino, argp->type == LFFS_MKDIR, undo);

	/* Remove (or add) the entry from the parent directory. */
	name_recover(dbp, argp->dir_inum, argp->dir_gen,
	    argp->rem_dip->di_inumber, argp->rem_name, argp->rem_dip->di_mode,
	    &argp->time, 0 /* !addname */, undo);

	/*
	 * The only remaining processing is deallocating the blocks.
	 * This should be accomplished through separate log messages.
	 * We leave the delete message on the linked list and when the
	 * 0th block is deallocated, we remove it.  At the end of recovery
	 * if the operation is still on the linked list, then we have to
	 * explicitly handle the deallocations.  In fact, we do not zero
	 * the inode here -- we leave that for either the dealloc of block
	 * 0 or in the final post-pass where we pick up unrecovered
	 * deletes.
	 */
	uep = (struct unlink_entry *)malloc(sizeof(struct unlink_entry));
	uep->unlink_ino = argp->rem_dip->di_inumber;
	uep->unlink_gen = argp->rem_dip->di_gen;
	bcopy(argp->rem_dip, uep->din, sizeof(struct dinode));
	TAILQ_INSERT_TAIL(&unlink_head, uep, links);
	return;
}

void
LINK_RECOVER(DB *dbp, LINK_args *argp)
{

	struct dinode *dip;
	ino_t ino;
	int op_happened, undo;

	ino = argp->link_inum;
	undo = check_for_abort(dbp, argp->type, ino, argp->link_gen);

	printf("recovering link of inode %d\n", ino);

	/*
	 * Recover the name from the parent directory and update parent
	 * directory inode.
	 */
	name_recover(dbp, argp->dir_inum, argp->dir_gen, ino, argp->new_name,
	    IFLNK /* mode=!dir */, &argp->time, 1 /* addname */, undo);

	/* Now fix the link inode. */
	dip = ginode(ino);
	op_happened = (dip->di_ctime.ts_sec > argp->time.tv_sec ||
	    dip->di_ctime.ts_sec == argp->time.tv_sec &&
	    (dip->di_ctime.ts_nsec * 1000) >= argp->time.tv_usec);

	if (!undo && !op_happened) {
		if (verbose)
			printf("\tincrementing link count\n");
		if (!no_update) {
			TIMEVAL_TO_TIMESPEC(&argp->time, &dip->di_ctime);
			dip->di_nlink = argp->new_link_nlink;
			inodirty();
		}
	} else if (undo && op_happened) {
		if (verbose)
			printf("\tundoing link increment\n");
		if (!no_update) {
			dip->di_nlink = argp->new_link_nlink - 1;
			inodirty();
		}
	}
	free(argp);
}
void
SYMLINK_RECOVER(DB *dbp, SYMLINK_args *argp)
{
	int undo, len;
	ino_t ino;
	struct dinode *dip;
	struct symlink_entry *sep;

	ino = argp->new_inum;
	undo =  check_for_abort(dbp, argp->type, ino,  argp->new_gen);

	printf("Recovering symlink %d\n", ino);

	/* First, remove corresponding IALLOC and set bitmap. */
	remove_ialloc(argp->new_inum);

	lffs_inode_setclr(ino, 0 /* !directory */, !undo);

	/* Now get the new inode */
	dip = ginode(argp->new_inum);
	len = strlen(argp->link_name);
	if (dip->di_gen < argp->new_gen && !undo) {
		if (verbose)
			printf("\trecovering inode %d\n", ino);

		if (!no_update) {
			clearinode(dip);
			dip->di_mode = argp->new_mode;
			dip->di_nlink = 1;
			TIMEVAL_TO_TIMESPEC(&argp->time, &dip->di_atime);
			TIMEVAL_TO_TIMESPEC(&argp->time, &dip->di_mtime);
			TIMEVAL_TO_TIMESPEC(&argp->time, &dip->di_ctime);
			dip->di_gen = argp->new_gen;
			dip->di_uid = argp->new_uid;
			dip->di_gid = argp->new_gid;
		}

		if (len < fs->fs_maxsymlinklen) {
			if (verbose)
				printf("\tlength stored in inode\n");
			if (!no_update) {
				dip->di_size = len;
				bcopy(argp->link_name, dip->di_shortlink, len);
			}
		} else {
			/*
			 * There should be a block allocation record later,
			 * and we'll have to put the link name intothat
			 * block.
			 */
			sep = (struct symlink_entry *)
			    malloc(sizeof(struct symlink_entry));
			sep->link_ino = ino;
			sep->length = len;
			sep->name = (char *)malloc(len);
			bcopy(argp->link_name, sep->name, len);
			TAILQ_INSERT_TAIL(&symlink_head, sep, links);
		}
		if (!no_update)
			inodirty();
	} else if (dip->di_gen == argp->new_gen && undo) {
		/*
		 * File exists and it should not; undo it.  In the undo
		 * case, there should never be a block allocated with a
		 * long symbolic name in it, so we do not need to worry
		 * about recovering it.
		 */
		if (verbose)
			printf("\tprocessing undo\n");
		if (!no_update) {
			bzero(dip, sizeof(struct dinode));
			inodirty();
		}
	}

	/* Now fix the directory name. */
	name_recover(dbp, argp->dir_inum, argp->dir_gen, argp->new_inum,
	    argp->new_name, argp->new_mode, &argp->time, 1 /* add */, undo);

	free(argp);
}

/*
 * I grab the renamed inode's mode from the on-disk inode.  It's
 * possible that this is wrong and I should explicilty log the
 * mode.  Right now, I don't think it matters, but this requires
 * some more thought.
 */

void
RENAME_RECOVER(DB *dbp, RENAME_args *argp)
{
	struct dinode *dip;
	struct dirent *dp;
	int op_happened, undo;
	u_short mode;

	undo = check_for_abort(dbp, argp->type, argp->ren_inum, argp->ren_gen);
	printf("recovering rename %d\n", argp->ren_inum);

	/* Get the renamed inode. */
	dip = ginode(argp->ren_inum);
	mode = dip->di_mode;

	op_happened = (dip->di_ctime.ts_sec > argp->time.tv_sec ||
	    dip->di_ctime.ts_sec == argp->time.tv_sec &&
	    (dip->di_ctime.ts_nsec * 1000) >= argp->time.tv_usec);

	if (!op_happened && dip->di_mode & IFDIR) {
		/* If a directory was moved, we need to change its .. */
		dp = finddir(dip, "..", 2, NULL);
		if (!dp)
			recover_fail();

		/* This gets marked dirty and written automatically. */
		dp->d_fileno = argp->new_dir_inum;
	}

	/* Recover the old parent directory. */
	name_recover(dbp, argp->old_dir_inum, argp->old_dir_gen,
	    argp->ren_inum, argp->old_name, mode, &argp->time,
	    0 /* !addname */, undo);
	/* Recover the new parent directory. */
	name_recover(dbp, argp->new_dir_inum, argp->new_dir_gen,
	    argp->ren_inum, argp->new_name, mode, &argp->time,
	    1 /* addname */, undo);

	free(argp);
}

void
ALLOC_RECOVER(DB *dbp, ALLOC_args *argp)
{
	struct unlink_entry *uap;
	struct symlink_entry *sep;
	struct bufarea *bp;
	struct dinode *dip;

	if (verbose)
		printf("recovering alloc %d phys block %d log block %d\n",
		    argp->inum, argp->pbn, argp->lbn);

	/* If this is a DIRALLOC, we've already handled it. */
	if (argp->type != LFFS_DIRALLOC) {
		/* Update bitmaps for this block. */
		lffs_frag_setclr(argp->pbn, argp->nfrags,
		    argp->type != LFFS_DEALLOC);

		/*
		 * Verify that the inode is still valid and if so,
		 * zero out the block pointer.
		 */
		dip = ginode(argp->inum);
		if (dip->di_mode & IFLNK) {
			/* Make sure that name is written to block. */
			bp = getdatablk(argp->pbn,
			    dblksize(fs, dip, argp->pbn));
			for (sep = symlink_head.tqh_first; sep != NULL; 
			    sep = sep->links.tqe_next)
				if (sep->link_ino == argp->inum) {
					TAILQ_REMOVE(&symlink_head, sep, links);
					if (!no_update) {
						bcopy(sep->name, bp->b_un.b_buf,
						    sep->length);
						dirty(bp);
					}
					free(sep->name);
					free(sep);
					break;
				}
		}
		if (argp->type != LFFS_FEXTEND && dip->di_gen == argp->gen &&
		    !no_update)
			bindex(dip, argp->lbn, 0);
	}


	/* If this is the deallocation for block 0, check for a delete. */
	if (argp->type == LFFS_DEALLOC && argp->lbn == 0) {
		for (uap = unlink_head.tqh_first; uap != NULL; 
		    uap = uap->links.tqe_next)
			if (uap->unlink_ino == argp->inum &&
			    uap->unlink_gen == argp->gen) {
				TAILQ_REMOVE(&unlink_head, uap, links);
				break;
			}
	}

	free(argp);

}

void
ABORT_RECOVER(DB *dbp, ABORT_args *argp)
{
/* RECOVERY CODE GOES HERE */
	return;
}
void
LOGICAL_RECOVER(DB *dbp, LOGICAL_args *argp)
{
	struct logical_block *lbp;

	printf("recovering logical log operation %d lbn %d\n", argp->inum,
	    argp->lbn);

	if (argp->type == LFFS_LOGICAL) {
		lbp = (struct logical_block *)malloc(sizeof(struct logical_block));
		if (lbp == NULL)
			recover_fail();

		lbp->inum =  argp->inum;
		lbp->lbn = argp->lbn;
		lbp->op = argp->type;
		TAILQ_INSERT_TAIL(&logical_head, lbp, links);
	}

	/*
	 * If type is DIRLOGICAL, this has already been
	 * recovered in the preceding DIRECTORY op.
	 */

	free(argp);
}

void
lffs_apply_record(DB *dbp, long type, void *rp)
{
	switch(type) {
		case REC_CREATE:
			CREATE_RECOVER(dbp, rp);
			return;
		case REC_IALLOC:
			IALLOC_RECOVER(dbp, rp);
			return;
		case REC_REMOVE:
			REMOVE_RECOVER(dbp, rp);
			return;
		case REC_LINK:
			LINK_RECOVER(dbp, rp);
			return;
		case REC_SYMLINK:
			SYMLINK_RECOVER(dbp, rp);
			return;
		case REC_RENAME:
			RENAME_RECOVER(dbp, rp);
			return;
		case REC_ALLOC:
			ALLOC_RECOVER(dbp, rp);
			return;
		case REC_ABORT:
			ABORT_RECOVER(dbp, rp);
			return;
		case REC_LOGICAL:
			LOGICAL_RECOVER(dbp, rp);
			return;
	}
}

/* CUSTOM CODE HERE */

int
check_for_abort(DB *dbp, u_long op, ino_t ino, long gen)
{
	struct preop pop;
	DBT key, data;
	int stat;

	pop.gen = gen;
	pop.ino = ino;
	pop.op = op;
	pop.lbn = 0;
	key.data = &pop;
	key.size = sizeof(struct preop);
	data.data = NULL;
	data.size = 0;

	stat = (dbp->get)(dbp, &key, &data, 0);
	if (stat < 0) {
		perror("Internal hash error");
		return(1);
	} else if (stat == 0)	{
		/* Op aborted */
		if (verbose) 
			printf("%s op aborted: %d 0x%x\n",
			    log_names[op], ino, gen);
		return(1);
	}
	return(0);
}

int
remove_ialloc(ino_t inum)
{
	struct ialloc_block *iap;

	for (iap = ialloc_head.tqh_first; iap != NULL; 
	    iap = iap->links.tqe_next)
		if (iap->inum == inum) {
			TAILQ_REMOVE(&ialloc_head, iap, links);
			return(1);
		}
	return(0);
}

daddr_t
get_lbn(ino_t inum, int op)
{
	struct logical_block *lbp;
	daddr_t lbn;

	for (lbp = logical_head.tqh_first; lbp != NULL; 
	    lbp = lbp->links.tqe_next)
		if (lbp->inum == inum && lbp->op == op) {
			TAILQ_REMOVE(&logical_head, lbp, links);
			lbn = lbp->lbn;
			free(lbp);
			return(lbn);
		}
	return(FATAL_DADDR);
}

void
recover_fail(void)
{
	printf("Fatal recovery error\n");
	exit(1);
}

int
adddir_space(DB *dbp, struct dinode *dip)
{
	DBT data, key;
	struct preop pop;
	struct dirop dop;
	daddr_t alloc_bn, last_lbn, bn;
	int blksize;
	int frags;
	int stat;
	/*
	 * There are two possibilities.  If the allocation
	 * messages made it to disk, we should have entries
	 * in the hash table that tell us what blocks to
	 * allocate.  If not, then we will have to do the
	 * allocation manually.
	 */

	alloc_bn = lblkno(fs, dip->di_size + 1);

	data.data = NULL;
	data.size = 0;
	key.data = &pop;
	key.size = sizeof(struct preop);

	pop.gen = dip->di_gen;
	pop.op = LFFS_DIRALLOC;
	pop.ino = dip->di_inumber;
	pop.lbn = alloc_bn;
	stat = (dbp->get)(dbp, &data, &key, 0);
	if (stat < 0)
		recover_fail();
	if (stat == 0) {
		/* Record the allocation. */
		assert(data.size == sizeof(struct dirop));
		bcopy(data.data, &dop, sizeof(struct dirop));
		lffs_frag_setclr(dop.pbn, dop.nfrags, 1);
		bn = dop.pbn;
	} else {
		/*
		 * The allocation never got in the log.  We'll have
		 * to allocate it.
		 * There are three cases to check:
		 * 1. Add fragment in place.
		 * 2. Move fragments to new place.
		 * 3. Find a brand new block.
		 */

		last_lbn = lblkno(fs, dip->di_size - 1);
		dip->di_size += DIRBLKSIZ;
		if ((bn = bmap(dip, last_lbn)) == 0)
			recover_fail();
		if ((blksize = dblksize(fs, dip, last_lbn)) != fs->fs_bsize) {

			/* Allocating a fragment. */
			frags = numfrags(fs, blksize);
			if (fragnum(fs, bn) != fragnum(fs, bn + 1) ||
			    !lffs_checkfrag(1, bn + 1)) {
				/* Case 1: can allocate next frag. */
				lffs_frag_setclr(bn + 1, 1, 1);
			} else {
				/* Case 2: Need to move fragments. */
				lffs_frag_setclr(bn, frags, 0);
				bn = lffs_findblock(frags + 1, bn);
				lffs_frag_setclr(bn, frags + 1, 1);
				bn = bindex(dip, last_lbn, bn);
			}
		} else {
			/*
			 * Case 3: Need to begin a new block.  Find
			 * a large enough block, then update the inode.
			 */
			last_lbn++;
			bn = lffs_findblock(fragnum(fs,
			    dblksize(fs, dip, last_lbn)), bn);
			bn = bindex(dip, last_lbn, bn);
		}

	}
	return(bn != 0);
}

/*
 * This code handles any addition/deletion from a directory and
 * any associated undo operations.
 */
void
name_recover(DB *dbp, ino_t dir_ino, long dir_gen, ino_t f_ino, char *f_name, 
    long f_mode, struct timeval *optime, int add_name, int undo)
{
	struct dinode *dip;
	struct dirent *dp;
	struct slot freedir;
	int len;
	int op_happened;


	/* Find the parent directory. */
	dip = ginode(dir_ino);
	if (dip->di_gen != dir_gen)
		return;

	op_happened = (dip->di_ctime.ts_sec > optime->tv_sec ||
	    dip->di_ctime.ts_sec == optime->tv_sec &&
	    (dip->di_ctime.ts_nsec * 1000) >= optime->tv_usec);

	if (op_happened && undo) {
		/* The op happened, but we should have undone it. */
		if (f_mode & IFDIR)
			dip->di_nlink += add_name ? -1 : 1;
		inodirty();
	} else if (!op_happened && !undo) {
		/*
		 * The operation did not happen, but it should have.
		 */
		if (f_mode & IFDIR)
			dip->di_nlink += add_name ? 1 : -1;
		TIMEVAL_TO_TIMESPEC(optime, &dip->di_ctime);
		inodirty();
	}

	/* Fix the parent directory */
	len = strlen(f_name);
	dp = finddir(dip, f_name, len, &freedir);

	if (dp && ((add_name && undo) || (!add_name && !undo))) {
		/* Need to remove entry. */
		if (remdir(dip, dp, &freedir))
			recover_fail();
	} else if (!dp && ((add_name && !undo) || (!add_name && undo))) {
		/* Need to add entry. */
		if (add_entry(dip, f_ino, f_name, len, f_mode, &freedir)) {
			/* We were unable to add new entry. */
			if (!adddir_space(dbp, dip))
				recover_fail();
			if(add_entry(dip, f_ino, f_name, len, f_mode, &freedir))
				recover_fail();
		}
	}
	return;
}
