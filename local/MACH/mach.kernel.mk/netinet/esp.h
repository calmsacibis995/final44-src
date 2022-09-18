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
 * $Log:	esp.h,v $
 * Revision 2.3  89/03/09  20:41:08  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:56:07  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
 
/*
 * $ Header: esp.h,v 2.1 87/08/18 16:30:23 mrt Exp $
 */

/*
 * esp.h			2/27/87
 * Written by Erik Nordmark
 */

/*
 * TODO
 */

/* 
 * Basic defintions for the Entity State Protocol
 */

/*
 * The authentification returned in a ProbeResponse for AuthVersion 1 
 */
struct av1 {
	struct procid	ai_processid;		/* process identifier */
	struct princid	ai_principalid;		/* principal identifier */
	struct princid  ai_effprincipalid;	/* effective principal id */
};

/*
 * The authentification returned in a ProbeResponse for Authversion 2 
 */
struct av2 {
	struct procid	ai_processid;		/* process identifier */
	struct princid	ai_principalid;		/* principal identifier */
	u_long		ai_reserved;		/* not used */
	u_long		ai_authsize;		/* authenticator size */
};

 
/*
 * The authentification returned in a ProbeResponse for AuthVersion 3 
 * The first four fields are encrypted with the conversation key.
 */
struct av3 {
	u_long	ai_cksum;	/* checksum for the response data */
	u_long 	ai_transid;	/* transaction id - encrypted */
	u_long	ai_tmstamp;	/* timestamp - encrypted */
	u_long	ai_reserved;	/* not used */
	u_long	ai_encryptqual;	/* encryption qualifier */
	u_long 	ai_authsize;	/* authenticator size */
};

union espauth {
	struct av1	au_av1;
	struct av2	au_av2;
	struct av3	au_av3;
};

/*
 * The packet header
 */
struct esphdr {
	struct vmtpeid 	eh_probedent;	/* entity being probed */
	u_long		eh_vdl;		/* Version, domain and length */
	u_long		eh_ipcf;	/* Gap, prioriy, control, function */
/* 
 * This field is divided into the following fields: (in order as of spec.)
 *	unsigned	eh_version:4;	version of the protocol 
 *	unsigned	eh_domain:12;	client naming domain 
 *	unsigned	eh_length:16;	packet length
 *	unsigned	eh_control:16;	control flags, see below 
 *	unsigned	eh_inpktgap:8;	interpacket gap 
 *	unsigned	eh_priority:4;	priority, see below 
 *	unsigned	eh_fnctcode:4;	function code, see below
 */
	u_long		eh_transid;	/* transaction id */
 	u_long		eh_tmstamp;	/* probe time stamp */
 	struct vmtpeid	eh_probingent;	/* probing entity */
 	u_long		eh_code;	/* control codes */
 	union {
	    struct {
		struct vmtpeid 	eh_coresident; 	/* coresident entity */
		u_short		eh_adav;
/*
 * Divided into (in true order):
 *		unsigned 	eh_authversion:4; authentication version 
 *		unsigned 	eh_authdomain:12; authentication domain 
 */
		u_short		eh_mtu;		/* maximum transmission unit */
		u_long		eh_reserved[4];	/* not used */
	    } eh_req;
	    struct {
		u_short		eh_adav;
/*
 * Divided into (in true order):
 *		unsigned 	eh_authversion:4; authentication version 
 *		unsigned 	eh_authdomain:12; authentication domain 
 */
		u_short		eh_mtu;		/* maximum transmission unit */
		union espauth	eh_authent; 	/* depends on version */
	    } eh_resp;
	} eh;
#define ehq_coresident	eh.eh_req.eh_coresident
#define ehq_mtu		eh.eh_req.eh_mtu
#define ehp_mtu		eh.eh_resp.eh_mtu
#define ehp_authent	eh.eh_resp.eh_authent
};

/*
 * Selectors for the fields eh_vdl, eh_ipcf and eh_adav.
 */
#define geteh_version(eh)	((((eh).eh_vdl)>>28) & 0xf)
#define geteh_domain(eh)	((((eh).eh_vdl)>>16) & 0xfff)
#define geteh_length(eh)	(((eh).eh_vdl) & 0xffff)
#define geteh_control(eh)	((((eh).eh_ipcf)>>16) & 0xffff)
#define geteh_inpktgap(eh)	((((eh).eh_ipcf)>>8) & 0xff)
#define geteh_priority(eh)	((((eh).eh_ipcf)>>4) & 0xf)
#define geteh_fnctcode(eh)	(((eh).eh_ipcf) & 0xf)
#define seteh_version(eh,val)	{ (eh).eh_vdl &= 0x0fffffff; \
				  (eh).eh_vdl |= ((val) & 0xf)<<28; }
#define seteh_domain(eh,val)	{ (eh).eh_vdl &= 0xf000ffff; \
				  (eh).eh_vdl |= ((val) & 0xfff)<<16; }
#define seteh_length(eh,val)	{ (eh).eh_vdl &= 0xffff0000; \
				  (eh).eh_vdl |= ((val) & 0xffff); }
#define seteh_control(eh,val)	{ (eh).eh_ipcf &= 0x0000ffff; \
				  (eh).eh_ipcf |= ((val) & 0xffff)<<16; }
#define seteh_inpktgap(eh,val)	{ (eh).eh_ipcf &= 0xffff00ff; \
				  (eh).eh_ipcf |= ((val) & 0xff)<<8; }
#define seteh_priority(eh,val)	{ (eh).eh_ipcf &= 0xffffff0f; \
				  (eh).eh_ipcf |= ((val) & 0xf)<<4; }
#define seteh_fnctcode(eh,val)	{ (eh).eh_ipcf &= 0xfffffff0; \
				  (eh).eh_ipcf |= ((val) & 0xf); }
#define oreh_control(eh,val)	\
			(eh).eh_ipcf |= (((val) & 0xffff)<<16)
#define andeh_control(eh,val)	\
			(eh).eh_ipcf &= (0x0000ffff | ((val)<<16))


#define geteh_authdomain(adav)	((adav)>>12)
#define geteh_authversion(adav)	((adav) & 0x0fff)
#define seteh_authdomain(adav,value)	{ adav &= 0x0fff; \
					  adav |= ((value) & 0xf)<<12; }
#define seteh_authversion(adav,value)	{ adav &= 0xf000; \
					  adav |= (value) & 0x0fff; }

#define getehq_authdomain(h)	geteh_authdomain((h).eh.eh_req.eh_adav)
#define getehq_authversion(h)	geteh_authversion((h).eh.eh_req.eh_adav)
#define getehp_authdomain(h)	geteh_authdomain((h).eh.eh_resp.eh_adav)
#define getehp_authversion(h)	geteh_authversion((h).eh.eh_resp.eh_adav)
#define setehq_authdomain(h,val)	\
			seteh_authdomain(h.eh.eh_req.eh_adav,val)
#define setehq_authversion(h,val)	\
			seteh_authversion(h.eh.eh_req.eh_adav,val)
#define setehp_authdomain(h,val)	\
			seteh_authdomain(h.eh.eh_resp.eh_adav,val)
#define setehp_authversion(h,val)	\
			seteh_authversion(h.eh.eh_resp.eh_adav,val)
 
/*
#define getehq_authdomain(eh)	((eh).eh.eh_req.eh_adav>>12)
#define getehq_authversion(eh)	((eh).eh.eh_req.eh_adav & 0x0fff)
#define getehp_authdomain(eh)	((eh).eh.eh_resp.eh_adav>>12)
#define getehp_authversion(eh)	((eh).eh.eh_resp.eh_adav & 0x0fff)
#define setehq_authdomain(eh,val)	\
			{ eh.eh.eh_req.eh_adav &= 0x0fff; \
			  eh.eh.eh_req.eh_adav |= ((val) & 0xf)<<12; }
#define setehq_authversion(eh,val)	\
			{ eh.eh.eh_req.eh_adav &= 0xf000; \
			  eh.eh.eh_req.eh_adav |= (val) & 0x0fff; }	
#define setehp_authdomain(eh,val)	\
			{ eh.eh.eh_resp.eh_adav &= 0x0fff; \
			  eh.eh.eh_resp.eh_adav |= ((val) & 0xf)<<12; }
#define setehp_authversion(eh,val)	\
			{ eh.eh.eh_resp.eh_adav &= 0xf000; \
			  eh.eh.eh_resp.eh_adav |= (val) & 0x0fff; }	
 */

/*
 * Control codes 
 */
#define ECTL_NPE	0x002	/* notify the probing entity */
#define ECTL_SOP	0x008	/* signal the vmtp module */
#define EC_CRE		VU_CRE	/* coresident entity */
#define EC_SDA		VU_SDA	/* segment data appended */
#define EC_REQ		VU_REQ	/* request; else response */

#define esp_notifyprobing(control) ((control) & ECTL_NPE)
#define esp_signalprobe(control) ((control) & ECTL_SOP)
#define esp_coresident(code) ((code) & EC_CRE)
#define esp_segmentdata(code) ((code) & EC_SDA)
#define esp_request(code) ((code) & EC_REQ)

#define ESP_MINPROBE	0x01	/* short probe */
#define ESP_FULLPROBE	0x02	/* long probe */
#define ESP_PROBEBLOCK	0x03	/* probe a block of entity identifiers */

#define esp_minprobe(code) ((code) & 0x00fffff == ESP_MINPROBE)
#define esp_fullprobe(code) ((code) & 0x00fffff == ESP_FULLPROBE)
#define esp_probeblock(code) ((code) & 0x00fffff == ESP_PROBEBLOCK)

#define esp_authdomainserved(d) \
		((d) == 1 || (d) == 2)
#define esp_authversionserved(v) \
		((v) == 1 || (v) == 2 || (v) == 3)	 

#define esp_securedomain(d) \
		((d) == 2)


/*
 * Encryption qualifiers in AuthDomain 2
 */
#define ENCRYPT_NONE	0	
#define ENCRYPT_DESCBC	1	/* CBC mode of DES */
#define ENCRYPT_XOR	2	/* xor with a 32 bit key */



