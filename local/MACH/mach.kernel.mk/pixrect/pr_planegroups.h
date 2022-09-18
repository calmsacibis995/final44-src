/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pr_planegroups.h,v $
 * Revision 2.4  89/03/09  20:57:29  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:12:45  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
/*	@(#)pr_planegroups.h 1.2 86/10/08 SMI	*/

/*
 * Copyright 1986 by Sun Microsystems, Inc.
 */

#ifndef	PR_PLANEGROUPS_H_
#define PR_PLANEGROUPS_H_

/* Masks for frame buffer planes and plane group number */
#define PIX_ALL_PLANES		0x00FFFFFF
#define PIX_GROUP_MASK		0x7F

/* Macros to encode or extract group into or from attribute word */
#define PIX_GROUP(g)		((g) << 25)
#define PIX_ATTRGROUP(attr)	((unsigned)(attr) >> 25)

/* Flag bit which inhibits plane mask setting (for setting group only) */
#define PIX_DONT_SET_PLANES	(1 << 24)
 
/*  Plane groups definitions */
#define PIXPG_CURRENT		0
#define PIXPG_MONO		1
#define PIXPG_8BIT_COLOR	2
#define PIXPG_OVERLAY_ENABLE	3
#define PIXPG_OVERLAY	 	4
#define PIXPG_INVALID		127

/* Plane groups functions */
extern int pr_available_plane_groups();
extern int pr_get_plane_group();
extern void pr_set_plane_group();
extern void pr_set_planes();

#endif	PR_PLANEGROUPS_H_
