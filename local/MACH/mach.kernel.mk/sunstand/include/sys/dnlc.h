/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	dnlc.h,v $
 * Revision 2.2  89/07/11  23:35:38  jjc
 * 	     Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)dnlc.h 2.8 88/02/08 SMI	*/

/*
 * Copyright (c) 1984 Sun Microsystems Inc.
 */

/*
 * This structure describes the elements in the cache of recent
 * names looked up.
 */

#define	NC_NAMLEN	15	/* maximum name segment length we bother with*/

struct	ncache {
	struct	ncache	*hash_next, *hash_prev;	/* hash chain, MUST BE FIRST */
	struct 	ncache	*lru_next, *lru_prev;	/* LRU chain */
	struct	vnode	*vp;			/* vnode the name refers to */
	struct	vnode	*dp;			/* vno of parent of name */
	char		namlen;			/* length of name */
	char		name[NC_NAMLEN];	/* segment name */
	struct	ucred	*cred;			/* credentials */
};

/*
 * Stats on usefulness of name cache.
 */
struct	ncstats {
	int	hits;		/* hits that we can really use */
	int	misses;		/* cache misses */
	int	enters;		/* number of enters done */
	int	dbl_enters;	/* number of enters tried when already cached */
	int	long_enter;	/* long names tried to enter */
	int	long_look;	/* long names tried to look up */
	int	lru_empty;	/* LRU list empty */
	int	purges;		/* number of purges of cache */
};

#define	ANYCRED	((struct ucred *) -1)
#define	NOCRED	((struct ucred *) 0)

int	ncsize;
struct	ncache *ncache;
