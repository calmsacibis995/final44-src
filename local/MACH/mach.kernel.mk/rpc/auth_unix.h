/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	auth_unix.h,v $
 * Revision 2.3  89/02/25  19:13:27  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  00:58:33  jsb
 * 	Include file references.
 * 	[89/01/17  14:37:13  jsb]
 * 
 */
/* @(#)auth_unix.h	1.2 87/09/03 3.2/4.3NFSSRC */
/* @(#)auth_unix.h	1.2 86/10/28 NFSSRC */
/*      @(#)auth_unix.h 1.1 86/09/24 SMI      */

/*
 * auth_unix.h, Protocol for UNIX style authentication parameters for RPC
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 */

/*
 * The system is very weak.  The client uses no encryption for  it
 * credentials and only sends null verifiers.  The server sends backs
 * null verifiers or optionally a verifier that suggests a new short hand
 * for the credentials.
 */

/* The machine name is part of a credential; it may not exceed 255 bytes */
#define MAX_MACHINE_NAME 255

/*
 * gids compose part of a credential; there may not be more than 8.  This is
 * because we've violated the RPC protocol spec by passing NGRPS (which has
 * always been 8) as 'maxsize' to the xdr_array call that parses incoming
 * auth_unix structures.  The UNIX Authentication section of the RPC spec says
 * that a maximum of 10 gids can be passed.  If you follow the spec, you won't
 * be able to talk to NFS servers based on this code (which is most of them).
 */
/* NGRPS also cannot be greater than NGROUPS */
#define NGRPS 8

/*
 * Unix style credentials.
 */
struct authunix_parms {
	u_long	 aup_time;
	char	*aup_machname;
	int	 aup_uid;
	int	 aup_gid;
	u_int	 aup_len;
	int	*aup_gids;
};

extern bool_t xdr_authunix_parms();

/* 
 * If a response verifier has flavor AUTH_SHORT, 
 * then the body of the response verifier encapsulates the following structure;
 * again it is serialized in the obvious fashion.
 */
struct short_hand_verf {
	struct opaque_auth new_cred;
};
