/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	auth_des.h,v $
 * Revision 2.2  89/07/11  23:27:08  jjc
 * 	     Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*      @(#)auth_des.h 1.3 88/02/08 SMI      */

/*
 * auth_des.h, Protocol for DES style authentication for RPC
 *  
 * Copyright (C) 1986, Sun Microsystems, Inc.
 */

#ifndef _AUTH_DES_
#define _AUTH_DES_

/*
 * There are two kinds of "names": fullnames and nicknames
 */
enum authdes_namekind {
	ADN_FULLNAME, 
	ADN_NICKNAME
};

/*
 * A fullname contains the network name of the client, 
 * a conversation key and the window
 */
struct authdes_fullname {
	char *name;		/* network name of client, up to MAXNETNAMELEN */
	des_block key;		/* conversation key */
	u_long window;		/* encrypted window */
};


/*
 * A credential 
 */
struct authdes_cred {
	enum authdes_namekind adc_namekind;
	struct authdes_fullname adc_fullname;
	u_long adc_nickname;
};



/*
 * A des authentication verifier 
 */
struct authdes_verf {
	union {
		struct timeval adv_ctime;	/* clear time */
		des_block adv_xtime;		/* crypt time */
	} adv_time_u;
	u_long adv_int_u;
};

/*
 * des authentication verifier: client variety
 *
 * adv_timestamp is the current time.
 * adv_winverf is the credential window + 1.
 * Both are encrypted using the conversation key.
 */
#define adv_timestamp	adv_time_u.adv_ctime
#define adv_xtimestamp	adv_time_u.adv_xtime
#define adv_winverf	adv_int_u

/*
 * des authentication verifier: server variety
 *
 * adv_timeverf is the client's timestamp + client's window
 * adv_nickname is the server's nickname for the client.
 * adv_timeverf is encrypted using the conversation key.
 */
#define adv_timeverf	adv_time_u.adv_ctime
#define adv_xtimeverf	adv_time_u.adv_xtime
#define adv_nickname	adv_int_u

#endif /* ndef _AUTH_DES_ */
