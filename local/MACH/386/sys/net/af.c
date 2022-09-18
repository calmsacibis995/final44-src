/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	af.c,v $
 * Revision 2.3  89/03/09  20:38:19  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:53:22  gm0w
 * 	Added MACH copyright.
 * 	[89/02/12            gm0w]
 * 
 */
/*
 * Copyright (c) 1983, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)af.c	7.1 (Berkeley) 6/4/86
 */

#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include "af.h"

/*
 * Address family support routines
 */
int	null_hash(), null_netmatch();
#define AFNULL \
	{ null_hash,	null_netmatch }

#ifdef	INET
extern int inet_hash(), inet_netmatch();
#define AFINET \
	{ inet_hash,	inet_netmatch }
#else
#define AFINET	AFNULL
#endif

#ifdef	NS
extern int ns_hash(), ns_netmatch();
#define AFNS \
	{ ns_hash,	ns_netmatch }
#else
#define AFNS	AFNULL
#endif

struct afswitch afswitch[AF_MAX] = {
	AFNULL,	AFNULL,	AFINET,	AFINET,	AFNULL,
	AFNULL,	AFNS,	AFNULL,	AFNULL,	AFNULL,
	AFNULL, AFNULL, AFNULL, AFNULL, AFNULL,
	AFNULL, AFNULL,					/* through 16 */
};

null_init()
{
	register struct afswitch *af;

	for (af = afswitch; af < &afswitch[AF_MAX]; af++)
		if (af->af_hash == (int (*)())NULL) {
			af->af_hash = null_hash;
			af->af_hash = null_hash;
		}
}

/*ARGSUSED*/
null_hash(addr, hp)
	struct sockaddr *addr;
	struct afhash *hp;
{

	hp->afh_nethash = hp->afh_hosthash = 0;
}

/*ARGSUSED*/
null_netmatch(a1, a2)
	struct sockaddr *a1, *a2;
{

	return (0);
}
