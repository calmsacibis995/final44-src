/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	spec_subr.c,v $
 * Revision 2.9  90/07/24  18:31:08  mrt
 * 	Removed static from stable declaration for debugging and bug
 * 	disappeared.
 * 	[90/07/24            mrt]
 * 
 * Revision 2.8  89/08/02  08:09:57  jsb
 * 	Eliminated MACH conditionals. Use zalloc in place of kalloc.
 * 	[89/07/31  16:41:22  jsb]
 * 
 * Revision 2.7  89/04/22  15:30:31  gm0w
 * 	Minor changes for HC.
 * 	[89/04/22            gm0w]
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.6  89/03/09  21:01:33  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  19:17:12  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  89/01/24  12:25:22  af
 * 	Fix for GCC -- pass2.
 * 	[89/01/24            rvb]
 * 
 * Revision 2.3  89/01/23  15:28:02  rvb
 * 	Forward declarations for GCC.
 * 	[89/01/22            rvb]
 * 
 * Revision 2.2  89/01/18  01:09:10  jsb
 * 	Include file references.
 * 	[89/01/17  15:05:02  jsb]
 *
 *  9-Mar-88 John Seamons (jks) at NeXT
 *	Attach vm_info structure to snode.
 *
 * 18-Jan-88  Gregg Kellogg (gk) at Next, Inc.
 *	STREAMS: added support for SVR2.1 streams and VSTR vnode type.
 *
 * 27-Oct-87  Peter King (king) at NeXT, Inc.
 *	Original Sun source, ported to Mach.
 *
 */ 

#include <streams.h>

/* @(#)spec_subr.c	1.3 87/06/30 3.2/4.3NFSSRC */
#ifndef	lint
static  char sccsid[] = "@(#)spec_subr.c 1.1 86/09/25 Copyr 1986 Sun Micro";
#endif

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */
#if	NeXT
#include <sys/xpr.h>
#endif	NeXT

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/inode.h>
#include <specfs/snode.h>
#include <kern/mfs.h>
#include <kern/kalloc.h>
#if	STREAMS
#include <sys/stream.h>
#include <sys/conf.h>
#endif	STREAMS

#ifdef	__GNU__
static int ssave();
static struct snode *sfind();
#else	__GNU__
struct snode *sfind();
#endif	__GNU__

#if	STREAMS
struct snode *sfind_str();
#endif	STREAMS

/*
 * Return a shadow special vnode for the given dev.
 * If no snode exists for this dev create one and put it
 * in a table hashed by dev,realvp.  If the snode for
 * this dev is already in the table return it (ref count is
 * incremented by sfind.  The snode will be flushed from the
 * table when spec_inactive calls sunsave.
 */
struct vnode *
specvp(vp, dev)
	struct vnode *vp;
	dev_t dev;
{
	register struct snode *sp;
	extern struct snode *fifosp();
	struct vattr va;

#if	NeXT
XPR(XPR_FS, ("specvp entered: thread = 0x%x dev = %d,%d\n", current_thread(), dev>>8, dev&0xff));
#endif	NeXT

#if	NeXT
tryagain:
#endif	NeXT
	if ((sp = sfind(dev, vp)) == NULL) {
		ZALLOC(specfs_snode_zone, sp, struct snode *);
		bzero((caddr_t)sp, sizeof (*sp));
		STOV(sp)->v_type = ITYPE_SPEC;

		/* init the times in the snode to those in the vnode */
		if (!VOP_GETATTR(vp, &va, u.u_cred)) {
			sp->s_atime = va.va_atime;
			sp->s_mtime = va.va_mtime;
			sp->s_ctime = va.va_ctime;
		}
		VN_HOLD(vp);
		STOV(sp)->v_mode = (STOV(sp)->v_mode&~VFMT)|(vp->v_mode&VFMT);
		if ((vp->v_mode&VFMT) == VBLK) {
			sp->s_bdevvp = (struct vnode *)bdevvp(dev);
		}
#if	STREAMS
		else if ((vp->v_mode&VFMT) == VSTR
			 || ((vp->v_mode&VFMT) == VCHR
			     && cdevsw[major(dev)].d_str))
		{
			struct snode *sp1 = sfind_str(dev);

			/*
			 * We only want one stdata structure
			 * per stream.
			 */
			if (sp1) {
				STOV(sp)->v_stream = STOV(sp1)->v_stream;
				VN_RELE(STOV(sp1));
			}
		}
#endif	STREAMS
		sp->s_realvp = vp;
		STOV(sp)->v_rdev = dev;
		STOV(sp)->v_count = 1;
		STOV(sp)->v_vfsp = vp->v_vfsp;
		STOV(sp)->v_vm_info = (struct vm_info*) zalloc (vm_info_zone);
		ssave(sp);
#if	NeXT
	} else if (sp->s_flag & SLOCKED) {
			/* This snode is being deactivated */
			sp->s_flag |= SWANT;
			(void) sleep((caddr_t)(sp), PINOD);
			goto tryagain;
#endif	NeXT
	}
	return (STOV(sp));
}

/*
 * Snode lookup stuff.
 * These routines maintain a table of snodes hashed by dev so
 * that the snode for an dev can be found if it already exists.
 * NOTE: STABLESIZE must be a power of 2 for stablehash to work!
 */

#define STABLESIZE	16
#define stablehash(dev)	((major(dev) + minor(dev)) & (STABLESIZE-1))

/* static */
struct snode *stable[STABLESIZE];

/*
 * Put a snode in the table
 */
static
ssave(sp)
	struct snode *sp;
{

	STOV(sp)->v_next = STOV(stable[stablehash(STOV(sp)->v_rdev)]);
	stable[stablehash(STOV(sp)->v_rdev)] = sp;
}

/*
 * Remove a snode from the table
 */
sunsave(sp)
	struct snode *sp;
{
	struct snode *st;
	struct snode *stprev = NULL;
	 
	st = stable[stablehash(STOV(sp)->v_rdev)]; 
	while (st != NULL) { 
		if (st == sp) { 
			if (stprev == NULL) {
				stable[stablehash(STOV(sp)->v_rdev)] = snode_next(st);
			} else {
				STOV(stprev)->v_next = STOV(st)->v_next;
			}
			break;
		}	
		stprev = st;
		st = snode_next(st);
	}	
	if (sp->s_realvp) {
		VN_RELE(sp->s_realvp);
		if (sp->s_bdevvp) {
			VN_RELE(sp->s_bdevvp);
		}
		sp->s_realvp = NULL;
	}
}

/*
 * Lookup a snode by dev,vp
 */
/* static */
struct snode *
sfind(dev, vp)
	dev_t dev;
	struct vnode *vp;
{
	register struct snode *st;
	 
	st = stable[stablehash(dev)]; 
	while (st != NULL) { 
		if (STOV(st)->v_rdev == dev && st->s_realvp == vp) {
			VN_HOLD(STOV(st));
			return (st); 
		}
		st = snode_next(st);
	}	
	return (NULL);
}

#if	STREAMS
/*
 * Lookup a snode by dev
 */
static
struct snode *
sfind_str(dev)
	dev_t dev;
{
	register struct snode *st;
	 
	st = stable[stablehash(dev)]; 
	while (st != NULL) { 
		if (STOV(st)->v_rdev == dev && (STOV(st)->v_mode&VFMT) == VSTR) {
			VN_HOLD(STOV(st));
			return (st); 
		}
		st = snode_next(st);
	}	
	return (NULL);
}
#endif	STREAMS


/*
 * Mark the accessed, updated, or changed times in an snode
 * with the current (unique) time
 */
smark(sp, flag)
	register struct snode *sp;
	register int flag;
{
	struct timeval ut;

#if	NeXT || MACH
	microtime(&ut);
#else	NeXT || MACH
	uniqtime(&ut);
#endif	NeXT || MACH
	sp->s_flag |= flag;
	if (flag & SACC)
		sp->s_atime = ut;
	if (flag & SUPD)
		sp->s_mtime = ut;
	if (flag & SCHG) {
		sp->s_ctime = ut;
	}
}
