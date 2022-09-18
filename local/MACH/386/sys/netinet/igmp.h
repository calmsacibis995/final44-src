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
 * $Log:	igmp.h,v $
 * Revision 2.3  89/03/09  20:43:29  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:58:27  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 */
/*
 *	igmp.h
 */

/*
 * Internet Group Management Protocol Definitions.
 * Per RFC 988.
 */

#include "igmproto.h"

#if	IGMPROTO

/*
 * Structure of an igmp header.
 */
struct igmp {
	u_char		igmp_type;		/* type of message, see below */
	u_char		igmp_code;		/* type sub code */
	u_short		igmp_cksum;		/* ones complement cksum of struct */
	u_long		igmp_ident;
	struct in_addr 	igmp_groupaddr;		/* IP host group address */
	u_long		igmp_key1;		/* first 32 bits of access key */
	u_long		igmp_key2;		/* second 32 bits of access key */
};


/*
 * Definition of type and code field values.
 */

#define IGMP_PACKET_LENGTH	   20	/* all types are the same length      */

#define IGMP_CREATE_GROUP_REQUEST  1	/* IGMP packet types                  */
#define IGMP_CREATE_GROUP_REPLY    2
#define IGMP_JOIN_GROUP_REQUEST    3
#define IGMP_JOIN_GROUP_REPLY      4
#define IGMP_LEAVE_GROUP_REQUEST   5
#define IGMP_LEAVE_GROUP_REPLY     6
#define IGMP_CONFIRM_GROUP_REQUEST 7
#define IGMP_CONFIRM_GROUP_REPLY   8
#define IGMP_MEMBERSHIP_UPDATE	   9

#define IGMP_MAXTYPE		   9

#define IGMP_IS_A_REQUEST( type )  ( (type) & 1 )  /* all requests are odd */

#define IGMP_PUBLIC_GROUP	   0	/* option codes for CREATE_GROUP      */
#define IGMP_PRIVATE_GROUP	   1

/* External IGMP reply codes */

#define IGMP_REQUEST_GRANTED	   0	
#define IGMP_NO_RESOURCES	   1
#define IGMP_INVALID_CODE	   2
#define IGMP_INVALID_GROUP_ADDRESS 3
#define IGMP_INVALID_ACCESS_KEY	   4

#define IGMP_MAXCODE		   4

/* Internal reply codes */

#define IGMP_NOT_REMOTE	   	   242
#define IGMP_NO_INTERFACE	   243
#define IGMP_NO_INTERNAL_RESOURCES 244
#define IGMP_NO_REPLY		   245
#define IGMP_SEND_UPDATE	   246
#define IGMP_NO_RESPONSE	   247
#define IGMP_INVALID_TYPE	   248
#define IGMP_NO_PERMISSION	   249
#define IGMP_SOCKET_IN_USE	   250
#define IGMP_NO_SOCKET		   251
#define IGMP_REQUEST_SENT	   252
#define IGMP_ALREADY_A_MEMBER	   253
#define IGMP_NOT_A_MEMBER	   254

#define IGMP_RC_UNSET		   255

#define IGMP_SLEEP_PRIORITY	   (PZERO + 1)
#define IGMP_REQUEST_TRANS_LIMIT   5
#define IGMP_REQUEST_INTERVAL      2	/* seconds */
#define SLOWTIMEO_FREQUENCY        2	/* times/second this goes off */

/* Because slowtimeo is called every 500ms and we want retransmission every */
/* IGMP_REQUEST_INTERVAL seconds ... */
#define IGMP_SLOWTIMEO_COUNTDOWN  (IGMP_REQUEST_INTERVAL * SLOWTIMEO_FREQUENCY)
#define IGMP_MIN_CONFIRM_INTERVAL  15	/* seconds */
#define IGMP_MAX_CONFIRM_INTERVAL  30	/* seconds */

#define IGMP_RANDOM_CONFIRM_INTERVAL	\
	(IGMP_MIN_CONFIRM_INTERVAL +	\
	 random() % (IGMP_MAX_CONFIRM_INTERVAL - IGMP_MIN_CONFIRM_INTERVAL))

#endif	IGMPROTO
