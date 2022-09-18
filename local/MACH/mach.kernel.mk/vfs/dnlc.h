/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	dnlc.h,v $
 * Revision 2.4  89/03/09  22:43:04  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  11:11:47  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  01:22:15  jsb
 * 	Include file references.
 * 	[89/01/17  15:08:18  jsb]
 * 
 */
/*	@(#)dnlc.h 1.1 86/07/07 SMI	*/

/*
 * Copyright (c) 1984 Sun Microsystems Inc.
 */

/*
 * This structure describes the elements in the cache of recent
 * names looked up.
 */

#define NC_NAMLEN	15	/* maximum name segment length we bother with*/

struct	ncache {
	struct	ncache	*hash_next, *hash_prev;	/* hash chain, MUST BE FIRST */
	struct 	ncache	*lru_next, *lru_prev;	/* LRU chain */
	struct	vnode	*vp;			/* vnode the name refers to */
	struct	vnode	*dp;			/* vno of parent of name */
	char		namlen;			/* length of name */
	char		name[NC_NAMLEN];	/* segment name */
	struct	ucred	*cred;			/* credentials */
};

#define ANYCRED	((struct ucred *) -1)
#define NOCRED	((struct ucred *) 0)

int	ncsize;
struct	ncache *ncache;
