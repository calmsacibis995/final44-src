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
 * $Log:	esp_probe.h,v $
 * Revision 2.3  89/03/09  20:42:05  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:57:04  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
 

/*
 * $ Header: esp_probe.h,v 2.1 87/08/18 16:30:57 mrt Exp $
 */

/*
 * 	esp_probe.h	0.1	3/21/87
 *	Written by Erik Nordmark
 */

/*
 * Data returned by probeentity(). The first four parameters should be set
 * by the invoker. es_request is modified to show what is actually present in
 * the result.
 * The principal and password are truncated if they don't fit in es_length 
 * bytes. es_princlen and es_pwdlen reflect their true length.
 *
 * Note: it is not possible to get both the effective principal id and 
 * password or principal in the same probe. If conflicting information is
 * requested in the same probe the effective principal will not be given.
 */
struct espprobedata {
	u_short		es_request;	/* ses below */
	struct vmtpeid 	es_probedent;	/* the entity to be probed */
	int		es_length;	/* length of es_data */
	char		*es_data;	/* to be used for es_password and */
					/* es_principal */
	u_long		es_code;	/* vmtp response code */
	unsigned	es_inpktgap:6;	/* interpacket gap */
	unsigned	es_mtu:16;	/* mtu of probedent */
	union vmtp_addr es_hostaddr;	
	u_long		es_transid;
	int		es_roundtrip;
	int		es_timelimit;	/* for auth and encrypt information */
	struct procid	es_processid;
	struct princid	es_principalid;
	struct princid	es_effprincipalid;
	int		es_princlen;
	int		es_pwdlen;
	char		*es_principal;	/* null terminated string */
	char 		*es_password;	/* null terminated string */
	u_long		es_encryptqual;
	union vmtpkey	es_key;
};

/*
 * Probe requests: 
 */
#define EPR_NEW		0x01	/* don't use info in the csr - always probe */
#define EPR_COMM	0x02	/* communication state: transid, mtu, */
				/* inpktgap, roundtrip and hostaddress. */
#define EPR_PROC	0x04	/* processid */
#define EPR_PRINC	0x08	/* principalid and principal if length > 0 */
#define EPR_EFFP	0x10	/* effective principalid */
#define EPR_PWD		0x20	/* password */
#define EPR_TLIMIT	0x40	/* timelimit for authentication info */
#define EPR_ENCRYPT	0x80	/* key and encryptqual; only if secure */
				/* communication. */

#define esp_newinfo(r)			((r) & EPR_NEW)
#define esp_communicationinfo(r)	((r) & EPR_COMM)
#define esp_processinfo(r)		((r) & EPR_PROC)
#define esp_principalinfo(r)		((r) & EPR_PRINC)
#define esp_effprincinfo(r)		((r) & EPR_EFFP)
#define esp_pwdinfo(r)			((r) & EPR_PWD)
#define esp_timelimitinfo(r)		((r) & EPR_TLIMIT)
#define esp_encryptinfo(r)		((r) & EPR_ENCRYPT)

