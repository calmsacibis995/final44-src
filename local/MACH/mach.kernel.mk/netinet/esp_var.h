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
 * $Log:	esp_var.h,v $
 * Revision 2.3  89/03/09  20:42:37  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:57:34  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
/*
 * $ Header: esp_var.h,v 2.1 87/08/18 16:31:11 mrt Exp $
 */

/*
 * esp_var.h			2/27/87
 * Written by Erik Nordmark
 */

/*
 * The header for the authenticator used in authversion 2
 * Followed by password and principal.
 * The maximum length of the authenticatior is 512 bytes.
 */
struct av2auth {
	u_long		av2a_timelimit;	/* time since Dec 31, 1969 expires */
	u_short		av2a_pwdlen;	/* password length */
	u_short 	av2a_princlen; 	/* principal length */
};

/*
 * The header for the authenticator used in authversion 3
 * Followed by key and principal.
 * The maximum length of the authenticatior is 512 bytes.
 */
struct av3auth {
	u_long		av3a_cksum;	/* checksum for authenticator */
	u_long		av3a_timelimit;	/* time since Dec 31, 1969 expires */
	struct procid	av3a_processid;	/* process identifier */
	struct princid	av3a_principalid; /* principal indentifier */
	u_short 	av3a_princlen; 	/* principal length */
	u_short		av3a_keylen;	/* key length */
};

/*
 * Offsets from the beginning of the ei mbuf
 * Assumes that the headers for the authenticators (struct av2auth and av3auth)
 * have been pulled up into the same mbuf as the ei header.
 */
#define av2a_principaloff(av2aptr) \
	(sizeof(struct espiphdr) + sizeof(struct av2auth))
#define av2a_passwordoff(av2aptr) \
	(sizeof(struct espiphdr) + sizeof(struct av2auth) + \
	(av2aptr)->av2a_princlen)
#define av3a_principaloff(av3aptr) \
	(sizeof(struct espiphdr) + sizeof(struct av3auth))
#define av3a_keyoff(av3aptr) \
	(sizeof(struct espiphdr) + sizeof(struct av3auth) + \
	(av3aptr)->av3a_princlen)

#define av3a_off \
	(sizeof(struct espiphdr))
#define av3aresp_off /* offset for response data */ \
	(sizeof(struct espiphdr) - sizeof(struct av3))

/* 
 * Finding the authenticator and the strings in it.
 * Note: assumes the authenticator header has been pulled up into the 
 * same mbuf as the ei header
 */
#define eitoav2auth(ei) \
		(struct av2auth *)((caddr_t)(ei) + sizeof(struct espiphdr))

#define eitoav3auth(ei) \
		(struct av3auth *)((caddr_t)(ei) + sizeof(struct espiphdr))

/*
 * Random things ...
 */

#define mtutoblocks(b)\
	(((b) - sizeof(struct vmtpiphdr) - VMTP_CKSUMLEN)/ VMTP_BLKSIZE)

#define esp_time(t)	/* Time in milliseconds */ 	\
	{						\
		struct timeval avt;			\
							\
		microtime(&avt);			\
		t =  avt.tv_sec * 1000 + avt.tv_usec / 1000; \
	}

#define ET_ROUNDTRIP	VTS_ROUNDTRIP	
#define ET_RETRANSMIT	2*ET_ROUNDTRIP	/* time to wait for a probe response */
#define ESP_MAXREXMTCNT	5		/* max retransmissions */
#define ESP_SCANINTERVAL 30		/* scan csr's every 30 seconds */
#define ESP_MAXVERIFYINT 20		/* require at most 10 minutes between */
					/* hearing from an entity */
#define ESP_PROBEBLOCKSIZE 1024		/* for ESP_PROBEBLOCK requests */

#ifdef	KERNEL
int esp_hdlestimeo(), esp_hdltimeo(); 
union vmtpkey esp_getmasterkey();

#endif	KERNEL



