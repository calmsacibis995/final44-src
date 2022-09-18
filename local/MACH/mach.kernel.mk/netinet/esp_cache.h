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
 * $Log:	esp_cache.h,v $
 * Revision 2.3  89/03/09  20:41:21  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:56:19  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
/*
 * $ Header: esp_cache.h,v 2.1 87/08/18 16:30:31 mrt Exp $
 */

/*
 * 	esp_cache.h		2/26/87
 *	Written by Erik Nordmark
 */

/* 
 * The server host cache used in the Entity State Protocol
 */

/*
 * The server cache 
 */
struct vmtpsce {
	struct vmtpsce	*ve_nextmap;	/* next pointer in hash bucket */
	struct vmtpsce	*ve_next;	/* next in LRU list of entries */
	struct vmtpeid	ve_server;
	union vmtp_addr ve_hostaddr;	/* last known address */
	struct ifnet	*ve_ifp;
	u_short		ve_gap;		/* interpacket gap to be used */
	u_short		ve_roundtrip;	/* estimated round-trip delay (ms) */
	u_short		ve_mtu;		/* max transmission unit in BLOCKS */
	struct princid	ve_principalid;	/* the server principal */
	u_char		ve_iflags;	/* internal flags (see below) */
	u_char		ve_flags;	/* external flags */
};

/*
 * Internal flags
 * Note that the touched bit isn't used for cache replacement but is intended
 * for the adaptive adjustment of the cache value for the interpacket gap 
 * (ve_gap). If communication have taken place with the server lately and
 * the gap is not zero, the gap should be decreased once in a while. 
 * Nor this code neither the adjustment when RETRY is received in vmtp_hdlrqa
 * is written yet, since the layered unix environment isn't open down to the
 * send queue at the driver!
 */
#define VEIF_USED	0x1		/* The entry is used */
#define VEIF_TOUCHED	0x2		/* The entry has been touched lately */
/*
 * External flags
 * The hostaddr flag is used to distinguish between a guess when a timeout
 * would cause a multicast looking for the server and a server that has 
 * disappered. (This info should probably be aged!)
 * The principal flag shows if ve_principalid field contains the principal. 
 */
#define VEF_HOSTADDR	0x1		/* Packets from the server has been */
					/* received from the address (i.e.  */
					/* it's not just a guess. */
#define VEF_PRINCIPAL	0x2		/* The principal field is set */

#define entry_used(sc)		((sc)->ve_iflags & VEIF_USED)
#define entry_touched(sc)	((sc)->ve_iflags & VEIF_TOUCHED)
#define entry_hostaddr(sc)	((sc)->ve_flags & VEF_HOSTADDR)
#define entry_principal(sc)	((sc)->ve_flags & VEF_PRINCIPAL)


#define ESP_SERVERCACHE_SIZE 	16
#define ESP_CACHEMAPSIZE	 8
#define ESP_CACHEFREQ	1	/* frequency at which the cache is scanned */

#if	(ESP_CACHEMAPSIZE & (ESP_CACHEMAPSIZE-1) == 0)
#define ESP_CACHEMAPOP	& (ESP_CACHEMAPSIZE-1)
#else
#define ESP_CACHEMAPOP	% ESP_CACHEMAPSIZE
#endif

#define esp_hash(e) 	\
	((((u_short *)(e))[0]^((u_short *)(e))[1]^((u_short *)(e))[2]^ \
	 ((u_short *)(e))[3]) ESP_CACHEMAPOP)




#ifdef	KERNEL
struct vmtpsce		veservers[ESP_SERVERCACHE_SIZE];	
struct vmtpsce		*vecachemap[ESP_CACHEMAPSIZE];
struct {
	struct vmtpsce *first, *last;
}			vesceLRU;	/* list of entries in LRU order */

struct vmtpsce *esp_allocentry();
struct vmtpsce *esp_findentry();

#endif	KERNEL


