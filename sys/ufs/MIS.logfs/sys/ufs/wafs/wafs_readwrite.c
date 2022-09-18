#ifdef CLFS
/*
 * CLFS
 * $Log: wafs_readwrite.c,v $
 * Revision 1.5  1994/12/27  18:08:46  margo
 * Check for logwrap and force a checkpoint when it happens.  Use
 * wafs->wafs_minfree to decide when to force the checkpoint.
 *
 * Revision 1.4  1994/11/29  14:31:31  margo
 * Open on a wafs must be handled specially since the file offset is
 * usually set to 0 and 0 may no longer exist on the file system.
 *
 * Revision 1.3  1994/11/15  22:12:37  margo
 * Make sure read and write treat headers symmetrically with
 * respect to the header.length field.   header was being counted in the length
 * field in read.
 *
 * Revision 1.2  1994/10/04  17:02:24  margo
 * Make 4.4Lite version compile under BSD4.4-Lite.
 *
 * Revision 1.1  1994/09/27  18:53:32  jat
 * Fixed includes for alternate AIX/SPARC building.
 *
 */
#endif
/*
 * Copyright (c) 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *	The President and Fellows of Harvard University.
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
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
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
 *	$Id: wafs_readwrite.c,v 1.5 1994/12/27 18:08:46 margo Exp $
 */
static char *rcsid = "$Id: wafs_readwrite.c,v 1.5 1994/12/27 18:08:46 margo Exp $";


#ifdef CLFS
#include <sys/compat.h>
#include <sys/bsd_types.h>
#include <sys/bsd_param.h>
#include <clfs_param.h>
#include <sys/cdefs.h>
#include <sys/ucred.h>
#include <sys/intr.h>
#include <sys/sleep.h>

#include <sys/param.h>
#include <sys/vnode.h>
#include <sys/socket.h>
#include <sys/mbuf.h>
#include <sys/file.h>
#include <sys/disklabel.h>
#include <sys/filio.h>
#include <sys/errno.h>
#include <sys/malloc.h>

#include <miscfs/specfs/specdev.h>
#include <ufs/ufs/quota.h>
#include <ufs/ufs/ufsmount.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/ufs_extern.h>

#else /* CLFS */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/resourcevar.h>
#include <sys/kernel.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/buf.h>
#include <sys/filedesc.h>
#include <sys/proc.h>
#include <sys/conf.h>
#include <sys/mount.h>
#include <sys/vnode.h>
#include <sys/malloc.h>
#include <sys/time.h>
#include <sys/uio.h>

#include <vm/vm.h>

#include <miscfs/specfs/specdev.h>
#include <miscfs/fifofs/fifo.h>
#include <ufs/ufs/quota.h>
#include <ufs/ufs/ufsmount.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/ufs_extern.h>
#endif /* CLFS */

#include <ufs/wafs/wafs.h>
#include <ufs/wafs/wnode.h>
#include <ufs/wafs/wafs_extern.h>
#include <ufs/wafs/lffs.h>

#ifdef AIX
extern struct timestruc_t tod;
#endif

/*
 * Vnode op for reading.  The offset is a log sequence number
 * and should refer to the beginning of a log record.
 */
/* ARGSUSED */
wafs_read(ap)
	struct vop_read_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
{
	register struct vnode *vp;
	register struct wnode *wp;
	register struct uio *uio;
	register struct wafs *wafs;
	struct timeval tv;
	struct wafs_header header;
	struct buf *bp;
	daddr_t lbn, bn;
	off_t diff, record_end;
	long onpage;
	int error = 0;
	int extra = 0;
	long size, n, on, recbytes;
	long rec_on;

	vp = ap->a_vp;
	wp = VTOW(vp);
	uio = ap->a_uio;

#ifdef DIAGNOSTIC
	if (uio->uio_rw != UIO_READ)
		panic("wafs_read mode");
#endif
	if (uio->uio_resid == 0)
		return (0);
	wafs = wp->w_fs;
	header.rectype = wp->w_type;
	/*
	 * Most file systems have to check to see if we are accessing
	 * something that exceeds the maximum allowed file size.  Since
	 * wafs is a circular structure, we never have to worry about
	 * a maximum.  However, since we do wrap, the beginning of the
	 * WAFS may not be at offset 0.  If we get a read for offset 0,
	 * we automatically adjust to be the begining of log.  If we get
	 * a read request for anything non-0 but before the current
	 * beginning of a the log,  we return an error.
	 */
	if (uio->uio_offset == 0) {
		uio->uio_offset = wp->w_tail;
		extra = wp->w_tail;
	}else if (uio->uio_offset < wp->w_tail)
		return(EPERM);
	/*
	 * lbn is the logical block currently being read.
	 * on is the offset on the page where we will begin reading.
	 * n is the maximum number of bytes we will read on this iteration.
	 * diff is the number of bytes between the beginning of the read
	 * and the end of the file/log.
	 */
	n = uio->uio_resid;
	do {
		lbn = lblkno(wafs, uio->uio_offset);
		on = blkoff(wafs, uio->uio_offset);
		diff = wp->w_head - uio->uio_offset;
		if (diff <= 0)
			return (0);

		/* Clustering should be easy; need to figure how to do it */
		error = bread(vp, lbn, wafs->wafs_bsize, NOCRED, &bp);
		if (error) {
			brelse(bp);
			return (error);
		}

		/*
		 * Skip over any page headers.
		 */
		if (on == 0) {
			on += sizeof(wafs_page_header_t);
			uio->uio_offset += sizeof(wafs_page_header_t);
			extra += sizeof(wafs_page_header_t);
		}

		/*
		 * Figure out if we have a record header to examine.
		 * There are two cases to check.  If we are reading
		 * sequentially, then the last read will have left
		 * the record offset and length of the previous record
		 * and we can just check that.  If we are not reading
		 * sequentially, then we have to check where records
		 * begin on the new page.
		 */
		recbytes = 0;
		if (uio->uio_offset != wp->w_nextrec) {
			/* Not on a record boundary. */
			for (rec_on = sizeof(wafs_page_header_t); rec_on < on;){
				bcopy(bp->b_data + rec_on, &header,
		    		    sizeof(struct wafs_header));
				rec_on += sizeof(struct wafs_header) +
				    header.length;
			}
			recbytes = rec_on - on;
			wp->w_nextrec = lbn << wafs->wafs_bsize + rec_on;
			wp->w_type = header.rectype;
			
		}
		if (recbytes == 0) {
			/*
			 * If the only thing on this page is a
			 * header, then we need to skip to the
			 * next page.
			 */
			if ((onpage = wafs->wafs_bsize - on) <=
			    sizeof(struct wafs_header)) {
				uio->uio_offset += onpage;
				extra += onpage;
				brelse(bp);
				header.rectype = WAFS_NORECORD;
				continue;
			}
			bcopy(bp->b_data + on, &header,
			    sizeof(struct wafs_header));
			uio->uio_offset += sizeof(struct wafs_header);
			on += sizeof(struct wafs_header);
			extra += sizeof(struct wafs_header);
			recbytes = header.length;
			wp->w_nextrec = uio->uio_offset + header.length;
			wp->w_type = header.rectype;
		} 


		/*
		 * Figure out how many bytes we can read on this page.
		 */
		n = min((unsigned)(wafs->wafs_bsize - on), uio->uio_resid);
		n = min(n, recbytes);
		if (diff < n)
			n = diff;
#ifdef AIX
		error = uiomove(bp->b_data + on, (int)n, UIO_READ, uio);
#else
		error = uiomove(bp->b_data + on, (int)n, uio);
#endif
		if (n + on == wafs->wafs_bsize)
			bp->b_flags |= B_AGE;
		brelse(bp);
		/*
		 * Stop looping if 1) we've read a full record. 2) we have
		 * used up all of the buffer space provide by the user, or
		 * 3) we have detected an error.
		 */
	} while (error == 0 && uio->uio_resid > 0 && n != 0 &&
	    header.rectype != WAFS_ENDREC && header.rectype != WAFS_RECORD);

	if (!error) {
#ifdef AIX
		tv = *((struct timeval *)&tod);
#else
		tv = time;
#endif
		error = VOP_UPDATE(vp, &tv, NULL, 0);
	}
	uio->uio_resid -= extra;
	return (error);
}

/*
 * Vnode op for writing.  We return the LSN rather than the number of bytes
 * written.  If you cannot write all the bytes, consider the record not
 * written as partial writes do not help us in the least.
 */
wafs_write(ap)
	struct vop_write_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
{
	register struct vnode *vp = ap->a_vp;
	register struct uio *uio = ap->a_uio;
	register struct wnode *wp = VTOW(vp);
	register struct wafs *wafs;
	int ioflag = ap->a_ioflag;

	off_t this_lsn;

	struct timeval tv;
	struct buf *bp;
	struct wafs_header header;
	wafs_page_header_t page_header;
	daddr_t lbn, bn;
	int n, on, flags;
	int size, resid, error = 0;
	int current_size;

#ifdef DIAGNOSTIC
	if (uio->uio_rw != UIO_WRITE)
		panic("wafs_write mode");
#endif
	/* We may not need this check; we can just enforce it. */
	if (!(ioflag & IO_APPEND))
		return(EINVAL);
	/*
	 * XXX I think that we can avoid locking wnode for extended
	 * periods of time if we first compute the final size, update
	 * wp->w_head(lastlsn?), and unlock the wnode.
	 */

	/* uio->uio_resid contains the length of the log record. */
	if (uio->uio_resid == 0)
		return (0);

	wafs = wp->w_fs;

	/*
	 * Maybe this should be above the vnode op call, but so long as
	 * file servers have no limits, i don't think it matters
	 */
	n = resid = uio->uio_resid;
	uio->uio_offset = wp->w_head;
	header.rectype = WAFS_RECORD;
	header.length = 0;
	flags = 0;
	if (ioflag & IO_SYNC)
		flags = B_SYNC;
	do {
		lbn = lblkno(wafs, uio->uio_offset);
		on = blkoff(wafs, uio->uio_offset);

		/* Write record header: WAFS_RECORD or WAFS_CONTINUE. */
		if (wafs->wafs_bsize - on <= sizeof(struct wafs_header)) {
			this_lsn = (lbn + 1) << wafs->wafs_bshift;
			uio->uio_offset = this_lsn;
			continue;
		}
		current_size = uio->uio_resid + sizeof(struct wafs_header);
		n = min((unsigned)(wafs->wafs_bsize - on), current_size);
		if (resid != uio->uio_resid)
			header.rectype = WAFS_CONTINUE;
		else if (n < current_size)
			header.rectype = WAFS_BEGINREC;

		if (n < wafs->wafs_bsize)
			flags |= B_CLRBUF;
		else
			flags &= ~B_CLRBUF;

		size = wafs->wafs_bsize;
		if (error = bread(vp, lbn, size, ap->a_cred, &bp))
			break;
		(void) vnode_pager_uncache(vp);
		if (on == 0) {
			/* This is a new page. Check for log wrap. */
			if (!wafs->wafs_inchkpt &&
			    BLOCK_DIFF(wafs, wp->w_tail, uio->uio_offset) >=
			    ((100 - wafs->wafs_minfree) * wafs->wafs_size)/100)
				VFS_SYNC(vp->v_mount, 1, ap->a_cred, NULL);

			/* Write a timestamp. */
#ifdef AIX
			page_header = *((struct timeval *)&tod);
#else
			page_header = time;
#endif
			bcopy(&page_header, bp->b_data + on,
			    sizeof(wafs_page_header_t));
			on += sizeof(wafs_page_header_t);
			uio->uio_offset += sizeof(wafs_page_header_t);
			size -= sizeof(wafs_page_header_t);
		}
		n = min(n, size - bp->b_resid) - sizeof(struct wafs_header);
		header.length = n;
		bcopy(&header, bp->b_data + on,
		      sizeof(struct wafs_header));
		uio->uio_offset += sizeof(struct wafs_header);
		on += sizeof(struct wafs_header);
#ifdef AIX
		error = uiomove(bp->b_data + on, n, UIO_WRITE, uio);
#else
		error = uiomove(bp->b_data + on, n, uio);
#endif
		if (ioflag & IO_SYNC) {
			(void) bwrite(bp);
			wp->w_lastlsn = wp->w_head - 1;
		} else if (n + on == wafs->wafs_bsize) {
			bp->b_flags |= B_AGE;
			bawrite(bp);
		} else {
			bdwrite(bp);
		}
	} while (error == 0 && uio->uio_resid > 0 && n != 0);

	if (error && (ioflag & IO_UNIT)) {
		uio->uio_offset = wp->w_head;
		uio->uio_resid = resid;
	}
	wp->w_head = uio->uio_offset;
	if (!error) {
#ifdef AIX
		tv = *((struct timeval *)&tod);
#else
		tv = time;
#endif
		error = VOP_UPDATE(vp, NULL, &tv, ioflag & IO_SYNC);
	}
	if (uio->uio_resid != 0)
		printf("Short write\n");
	return (error);

/* XXX BSD calculates the return value in file system independent code;
   this is a problem for us since we want to return a different value. */
}

