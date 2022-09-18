/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ucred.h,v $
 * Revision 2.2  89/07/12  00:16:44  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)ucred.h	1.4 88/02/08 SMI	*/

#ifndef _sys_ucred_h
#define _sys_ucred_h

#include <sys/label.h>
#include <sys/audit.h>

/*
 * User credential structure
 */
struct ucred {
 	u_short		cr_ref;			/* reference count */
 	short 	 	cr_uid;			/* effective user id */
 	short  		cr_gid;			/* effective group id */
 	short		cr_auid;		/* user id, for auditing */
 	short  		cr_ruid;		/* real user id */
 	short		cr_rgid;		/* real group id */
 	int    		cr_groups[NGROUPS];	/* groups, 0 terminated */
 	blabel_t	cr_label;		/* Mandatory Access Control */
 	audit_state_t	cr_audit;		/* audit_state */
};

#ifdef KERNEL
#define	crhold(cr)	(cr)->cr_ref++
void crfree();
struct ucred *crget();
struct ucred *crcopy();
struct ucred *crdup();
struct ucred *crgetcred();
#endif KERNEL

#endif !_sys_ucred_h
