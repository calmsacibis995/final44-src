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
 * $Log:	mfs.h,v $
 * Revision 2.9  89/04/22  15:24:23  gm0w
 * 	Updated with new NBC code from rfr.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.8  89/03/09  20:14:13  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/25  18:06:39  gm0w
 * 	Kernel code cleanup.
 * 	Put entire file under #indef KERNEL.
 * 	[89/02/15            mrt]
 * 
 * Revision 2.6  89/02/07  01:03:14  mwyoung
 * Relocated from sys/mfs.h
 * 
 * Revision 2.5  89/01/18  01:17:16  jsb
 * 	Vnode support: add vnode_size field to vm_info; declare vm_info_zone.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.4  88/10/18  03:38:49  mwyoung
 * 	Add pager_request port.
 * 	[88/09/18            mwyoung]
 * 
 * Revision 2.3  88/08/24  02:35:56  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:17:29  mwyoung]
 * 
 * Revision 2.2  88/07/17  19:01:33  mwyoung
 * Use new memory object types.
 * 
 *
 * 11-Jun-87  William Bolosky (bolosky) at Carnegie-Mellon University
 *	Changed pager_id to pager.
 *
 * 30-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 */
/*
 *	File:	mfs.h
 *	Author:	Avadis Tevanian, Jr.
 *	Copyright (C) 1987, Avadis Tevanian, Jr.
 *
 *	Header file for mapped file system support.
 *
 */ 

#ifndef	_KERN_MFS_H_
#define _KERN_MFS_H_

#include <mach_afs.h>

#include <mach/memory_object.h>
#include <kern/lock.h>
#include <kern/queue.h>
#include <kern/zalloc.h>
#include <vm/vm_object.h>
#include <sys/types.h>

/*
 *	Associated with each mapped file is information about its
 *	corresponding VM window.  This information is kept in the following
 *	vm_info structure.
 */
struct vm_info {
	memory_object_t	pager;		/* memory object (global name) */
	memory_object_control_t
			pager_request;	/* control port (global name) */
	int		locker;		/* thread holding lock (debug) */
	short		map_count;	/* number of times mapped */
	short		use_count;	/* number of times in use */
	vm_offset_t	va;		/* mapped virtual address */
	vm_size_t	size;		/* mapped size */
	vm_offset_t	offset;		/* offset into file at va */
	vm_size_t	inode_size;	/* inode size (not reflected in ip) */
	lock_data_t	lock;		/* lock for changing window */
	vm_object_t	object;		/* object [for KERNEL flushing] */
	queue_chain_t	lru_links;	/* lru queue links */
	struct identity	*identity;	/* inode identity */
	int		error;		/* holds error codes */
	int		queued:1,	/* on lru queue? */
			dirty:1,	/* range needs flushing? */
			close_flush:1,	/* flush on close */
			mapped:1;	/* mapped into KERNEL VM? */
};

extern zone_t	vm_info_zone;

#define VM_INFO_NULL	((struct vm_info *) 0)

#if	MACH_AFS
#define	MFS_ABLE(vp)	(((vp)->v_mode&VFMT) == VREG && (vp)->v_type != ITYPE_AFS)
#else	MACH_AFS
#define	MFS_ABLE(vp)	(((vp)->v_mode&VFMT) == VREG)
#endif	MACH_AFS

#endif	_KERN_MFS_H_
