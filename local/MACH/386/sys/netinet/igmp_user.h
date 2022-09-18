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
 * $Log:	igmp_user.h,v $
 * Revision 2.3  89/03/09  20:43:54  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:58:52  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 */
/*
 *	igmp_user.h
 */

#include "igmproto.h"

#if	IGMPROTO

#define SIOCIGMPREQ _IOWR(i,29,struct igmpreqargs)

struct igmpreqargs {
	char	ifr_name[IFNAMSIZ];	/* Interface name */
	u_char  type;
	u_char  code;
	struct  in_addr groupaddr;
	u_long	key1;
	u_long	key2;
	u_char	loopback;		/* Boolean for Create and Join only */
};   

#endif	IGMPROTO
