/*
 * Copyright (c) 1994
 *	The President and Fellows of Harvard University.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by Harvard University
 *	and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	$Id: wafs_bmap.c,v 1.4 1994/10/04 17:02:11 margo Exp $
 * For version 1, we are going to make all the operations that we do
 * not need ENOTSUP.  For version2, we can decide which ones we ultimately
 * need to support.
 */
#ifdef CLFS
/*
 * CLFS
 * $Log: wafs_bmap.c,v $
 * Revision 1.4  1994/10/04  17:02:11  margo
 * Make 4.4Lite version compile under BSD4.4-Lite.
 *
 * Revision 1.1  1994/10/04  16:51:12  margo
 * Initial revision
 *
 * Revision 1.2  1994/09/27  18:53:34  jat
 * Fixed includes for alternate AIX/SPARC building.
 *
 * Revision 1.1  1994/09/26  18:47:41  mis
 * Initial WAFS checkin.
 *
 */
#endif
static char *rcsid = "$Id: wafs_bmap.c,v 1.4 1994/10/04 17:02:11 margo Exp $";

#ifdef CLFS
#include <sys/compat.h>
#include <sys/errno.h>

#include <ufs/ufs/quota.h>
#include <ufs/ufs/ufsmount.h>
#include <ufs/ufs/inode.h>

#else /* CLFS */

#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/stat.h>
#include <sys/buf.h>
#include <sys/proc.h>
#include <sys/mount.h>
#include <sys/vnode.h>
#include <sys/uio.h>
#endif /* CLFS */

#include <ufs/wafs/wafs.h>
#include <ufs/wafs/wnode.h>

int
wafs_bmap(ap)
	struct vop_bmap_args /* {
		struct vnode *a_vp;
		daddr_t a_bn;
		struct vnode **a_vpp;
		daddr_t *a_bnp;
		int *a_runp;
	} */ *ap;
{
	struct wafs *wafs;
	struct wnode *wp;
	daddr_t lbn;	/* Logical Block Number */
	daddr_t boff;	/* Offset in file system for block */
	int interval_blocks;	/* Number of blocks between superblocks */
	int blocks_to_skip;	/* Number of blocks of superblocks that
				   come before the data block */

	wp = VTOW(ap->a_vp);
	if (ap->a_vpp != NULL)
		*ap->a_vpp = wp->w_devvp;
	if (ap->a_bnp == NULL)	/* No place to return block number */
		return(0);

	lbn = ap->a_bn;
	wafs = wp->w_fs;

	/*
	 * To translate the logical block number to the physical one,
	 * we first have to factor out the number of times we have
	 * overflowed the circular buffer.  Then we need to factor
	 * in the number of superblocks passed in the current
	 * iteration.
	 */
	interval_blocks = WAFS_INTERVAL_SHIFT(wafs);
	boff = WAFS_BLOCK_OFF(wafs, lbn);
	blocks_to_skip = WAFS_BLOCKS_SKIP(wafs, lbn);
	if (ap->a_runp)
		*ap->a_runp = interval_blocks - (boff & interval_blocks - 1);
	*ap->a_bnp = fsbtodb(wafs, boff + blocks_to_skip) + SBLOCK;
	return(0);
}
