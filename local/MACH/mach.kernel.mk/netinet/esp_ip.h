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
 * $Log:	esp_ip.h,v $
 * Revision 2.3  89/03/09  20:41:40  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:56:39  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */

/*
 * $ Header: esp_ip.h,v 1.1 87/08/18 16:30:41 dpj Exp $
 */

/*
 * esp_ip.h			2/27/87
 * Written by Erik Nordmark
 */

struct espiphdr {
	struct vmtp_header	ei_hdr;	
	struct esphdr		ei_esp;
};

#define ei_ifp		ei_hdr.vh_ifp
#define ei_addr		ei_hdr.vh_addr
#define ei_type		ei_hdr.vh_type
#define ei_len		ei_hdr.vh_len
#define ei_ttl		ei_hdr.vh_ttl
#define ei_multicast	ei_hdr.vh_multicast
#define ei_src		ei_addr

#define ei_probedent	ei_esp.eh_probedent
#define ei_transid	ei_esp.eh_transid
#define ei_tmstamp	ei_esp.eh_tmstamp
#define ei_probingent	ei_esp.eh_probingent
#define ei_code		ei_esp.eh_code
#define eiq_coresident	ei_esp.eh.eh_req.eh_coresident
#define eiq_mtu		ei_esp.eh.eh_req.eh_mtu	
#define eip_mtu		ei_esp.eh.eh_resp.eh_mtu
#define eip_authent	ei_esp.eh.eh_resp.eh_authent

#define getei_version(ei)	geteh_version((ei)->ei_esp)
#define getei_domain(ei)	geteh_domain((ei)->ei_esp)
#define getei_length(ei)	geteh_length((ei)->ei_esp)
#define getei_inpktgap(ei)	geteh_inpktgap((ei)->ei_esp)
#define getei_priority(ei)	geteh_priority((ei)->ei_esp)
#define getei_control(ei)	geteh_control((ei)->ei_esp)
#define getei_fnctcode(ei)	geteh_fnctcode((ei)->ei_esp)
#define setei_version(ei,val)	seteh_version((ei)->ei_esp,val)
#define setei_domain(ei,val)	seteh_domain((ei)->ei_esp,val)
#define setei_length(ei,val)	seteh_length((ei)->ei_esp,val)
#define setei_inpktgap(ei,val)	seteh_inpktgap((ei)->ei_esp,val)
#define setei_priority(ei,val)	seteh_priority((ei)->ei_esp,val)
#define setei_control(ei,val)	seteh_control((ei)->ei_esp,val)
#define setei_fnctcode(ei,val)	seteh_fnctcode((ei)->ei_esp,val)

#define orei_control(ei,val)	oreh_control((ei)->ei_esp,val)
#define andei_control(ei,val)	andeh_control((ei)->ei_esp,val)

#define geteiq_authdomain(ei)	getehq_authdomain((ei)->ei_esp)
#define geteiq_authversion(ei)	getehq_authversion((ei)->ei_esp)
#define geteip_authdomain(ei)	getehp_authdomain((ei)->ei_esp)
#define geteip_authversion(ei)	getehp_authversion((ei)->ei_esp)
#define seteiq_authdomain(ei,val)	setehq_authdomain((ei)->ei_esp,val)
#define seteiq_authversion(ei,val)	setehq_authversion((ei)->ei_esp,val)
#define seteip_authdomain(ei,val)	setehp_authdomain((ei)->ei_esp,val)
#define seteip_authversion(ei,val)	setehp_authversion((ei)->ei_esp,val)


