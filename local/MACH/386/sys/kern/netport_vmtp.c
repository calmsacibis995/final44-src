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
 * $Log:	netport_vmtp.c,v $
 * Revision 2.4  89/03/09  20:14:45  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  18:07:17  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/08/06  18:24:18  rpd
 * Moved from sys/mach_ipc_netport.h to kern/ipc_netport.h.
 * 
 * 22-Jan-88  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Fixed to lower the spl before entering the ipc code.
 *
 * 18-Jan-88  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created.
 *
 */

/*
 * File:	netport_vmtp.c
 * Purpose:
 *	Front-end to the VMTP system for the netport system
 *	implementing network IPC in the kernel.
 */

/*
 * This module is derived from the old kern/mach_ipc_vmtp.c, which combined
 * the functions of netport_vmtp.c and mach_ipc_netport.c.
 */

#include <sys/types.h>
#include <kern/queue.h>
#include <kern/lock.h>
#include <mach/boolean.h>
#include <kern/zalloc.h>
#include <mach/message.h>
#include <kern/kern_port.h>
#include <kern/kern_msg.h>
#include <mach/kern_return.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>

#include <net/if.h>
#include <net/route.h>

#include <netinet/in.h>
#include <netinet/in_pcb.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/vmtp_so.h>
#include <netinet/vmtp.h>
#include <netinet/vmtp_var.h>

#include <kern/ipc_netport.h>


/*
 * Zone for kmsg's to be used for incoming messages.
 */
extern zone_t	netport_kmsg_zone;

/*
 * Bogus magic number
 */
#define SERVER_EID_FLTM		654321

/*
 * eid to be used for the IPC server
 */
struct vmtpeid	ipc_vmtp_server;

#define vm_ipccode		vm_shortdata[0]
/*
 * vm_netport is used locally to communicate a reference
 * to the client netport to the VMTP module. It is stored
 * in the local csr and not sent over the net! So I guess
 * this is really a hack...
 */
#define vm_netport		vm_shortdata[2]

/*
 * Macros to derive a VMTP eid from a trid obtained from a client and vice-versa.
 */
#define SET_EID(eid,trid)	{				\
	(eid).ve_fltm = (trid).v1; (eid).ve_inaddr = (trid).v2; }
#define SET_TRID(trid,eid)	{				\
	(trid).v1 = (eid).ve_fltm; (trid).v2 = (eid).ve_inaddr; }



/*
 * netport_vmtp_sendrequest --
 *
 * Send a request through the VMTP interface.
 *
 * Parameters:
 *
 *	client_id	: an identifier assigned by the client to this transaction
 *	kmsg		: the data to be sent
 *	len		: the length of the data in kmsg
 *	to		: the destination of the request
 *	crypt_level	: whether the data should be encrypted
 *
 * Results:
 *
 *	TR_SUCCESS or a specific failure code.
 *
 * Side effects:
 *
 * Design:
 *
 * Note:
 *
 */
int netport_vmtp_sendrequest(client_id,kmsg,len,to,crypt_level)
int		client_id;
kern_msg_t	kmsg;
int		len;
netaddr_t	to;
int		crypt_level;
{
	struct vmtpeid		client_eid;
	struct vmtpeid		server_eid;
	struct vmtpmcb		mcb;
	char			*segment;
	u_long			segmentCnt;
	kern_return_t		ret;

	(void) mach_vmtp_alloceid(PORT_NULL, &client_eid);
	server_eid.ve_fltm = SERVER_EID_FLTM;
	server_eid.ve_inaddr = to;

	mcb.vm_eid  	= server_eid;
	mcb.vm_code 	= VU_SDA | VU_REQ;
	mcb.vm_ipccode 	= IPC_SUCCESS;
	mcb.vm_netport 	= client_id;

	segment		= (char *) &kmsg->netmsg_hdr;
	segmentCnt 	= mcb.vm_segsize = len;

	ret = mach_vmtp_invoke(PORT_NULL, client_eid, INVOKE_REQ,
				       		&mcb, segment, &segmentCnt);

	if (ret == KERN_SUCCESS) {
		return TR_SUCCESS;
	} else {
		(void) mach_vmtp_freeeid(PORT_NULL, client_eid);
		return TR_SEND_FAILURE;
	}
}



/*
 * netport_vmtp_sendreply --
 *
 * Send a response through the VMTP interface.
 *
 * Parameters:
 *
 *	trid		: transport-level ID for a previous operation on this
 *			  transaction
 *	code		: a return code to be passed to the client.
 *	kmsg		: the data to be sent
 *	len		: the length of the data in kmsg
 *	crypt_level	: whether the data should be encrypted
 *
 * Results:
 *
 *	TR_SUCCESS or a specific failure code.
 *
 * Side effects:
 *
 * Design:
 *
 * Note:
 *
 */
int netport_vmtp_sendreply(trid,code,kmsg,len,crypt_level)
trid_t		trid;
int		code;
kern_msg_t	kmsg;
int		len;
int		crypt_level;
{
	struct vmtpmcb		mcb;
	char			*segment;
	u_long			segmentCnt;

	SET_EID(mcb.vm_client, trid);
	mcb.vm_code 		= (kmsg ? VU_SDA : 0);
	mcb.vm_ipccode	 	= code;
	if (kmsg) {
		segment = (char *)&kmsg->netmsg_hdr;
	} else {
		segment = NULL;
	}
	segmentCnt 	= mcb.vm_segsize = len;

	(void)mach_vmtp_reply(PORT_NULL, ipc_vmtp_server, &mcb, segment, 
								segmentCnt);
}


/*
 * This procedure is called from the VMTP input routine
 * when a reply is delivered.
 */
void
netmsg_input_rq(eid)
	struct vmtpeid		eid;
{
	struct vmtpmcb		mcb;
	char			*segment;
	int			segmentCnt;
	register
	kern_msg_t		kmsgptr;
	kern_return_t		ret;
	trid_t			trid;
/*	int			ipccode; */
	int			s;

	/*
	 * Allocate space to get the request, and get it
	 * from the VMTP module.
	 */
	ZGET(netport_kmsg_zone, kmsgptr, kern_msg_t);
	if (kmsgptr == KERN_MSG_NULL) {
		segmentCnt = 0;
		ret = mach_vmtp_getrequest(PORT_NULL, eid, &mcb,
					   (char *)0, &segmentCnt);
		SET_TRID(trid,mcb.vm_client);
		netport_vmtp_sendreply(trid,IPC_ABORT_REQUEST,0,0,0);
		return;
	}

	kmsgptr->home_zone = netport_kmsg_zone;

	segment = (char *)&(kmsgptr->netmsg_hdr);
	segmentCnt = NETPORT_MSG_SIZE_MAX;
	ret = mach_vmtp_getrequest(PORT_NULL,eid,&mcb,segment,&segmentCnt);
	if (ret != KERN_SUCCESS) {
		printf("netmsg_input_rq called, but no request available!\n");
		ZFREE(netport_kmsg_zone, kmsgptr);
		return;
	}

	/*
	 * Call the netport handler routine.
	 */
	if (!vmtp_ok(mcb.vm_code)) {
/*		ipccode = TR_FAILURE; */
		SET_TRID(trid,mcb.vm_client);
		netport_vmtp_sendreply(trid,IPC_ABORT_REQUEST,0,0,0);
	} else {
/*		ipccode = mcb.vm_ipccode; */
		SET_TRID(trid,mcb.vm_client);
		s = spl0();
		netport_handle_rq(TR_VMTP_ENTRY,trid,kmsgptr,segmentCnt,
						mcb.vm_client.ve_inaddr,0,0);
		splx(s);
	}

	return;
}


/*
 * This procedure is called from the VMTP input routine
 * when a reply is delivered.
 */
void
netmsg_input_rp(eid)
	struct vmtpeid		eid;
{
	struct vmtpmcb		mcb;
	char			*segment;
	int			segmentCnt;
	register
	kern_msg_t		kmsgptr;
	kern_return_t		ret;
	int			ipccode;
	int			s;

	/*
	 * Allocate space to get the response, and get it
	 * from the VMTP module.
	 */
	ZGET(netport_kmsg_zone, kmsgptr, kern_msg_t);
	if (kmsgptr == KERN_MSG_NULL) {
		segment    = (char *) 0;
		segmentCnt = 0;
		mcb.vm_code= 0;
		ret = mach_vmtp_invoke(PORT_NULL, eid,
			         INVOKE_RESP, &mcb, segment, &segmentCnt);
		/*
		 * We should try to find the waiting client and
		 * clean it up, but how? XXX
		 * -> get the netport from the mcb!
		 */
		return;
	}

	kmsgptr->home_zone = netport_kmsg_zone;

	segment = (char *)&kmsgptr->netmsg_hdr;
	segmentCnt = NETPORT_MSG_SIZE_MAX;

	mcb.vm_code = VU_WRA;
	ret = mach_vmtp_invoke(PORT_NULL, eid,
				INVOKE_RESP, &mcb, segment, &segmentCnt);

	if (ret != KERN_SUCCESS) {
		printf("netmsg_input_rp called, but no response available\n");
		ZFREE(netport_kmsg_zone, kmsgptr);
		return;
	}

	(void) mach_vmtp_freeeid(PORT_NULL, eid);

	/*
	 * Call the netport handler routine.
	 */
	if (!vmtp_ok(mcb.vm_code)) {
		ipccode = TR_FAILURE;
	} else {
		ipccode = mcb.vm_ipccode;
	}
	s = spl0();
	netport_handle_rp((int)(mcb.vm_netport),ipccode,kmsgptr,segmentCnt);
	splx(s);

	return;
}



/*
 * netport_vmtp_init --
 *
 * Initialises the VMTP transport protocol.
 *
 * Parameters:
 *
 * Results:
 *
 *	FALSE : we failed to initialise the VMTP transport protocol.
 *	TRUE  : we were successful.
 *
 * Side effects:
 *
 *	Initialises the VMTP protocol entry point in the switch array.
 *
 */
boolean_t netport_vmtp_init()
{
	(void)mach_vmtp_init(PORT_NULL,NULL);
	ipc_vmtp_server.ve_fltm = SERVER_EID_FLTM;
	ipc_vmtp_server.ve_inaddr = vmtp_hostid;
	(void)mach_vmtp_initserver(PORT_NULL,ipc_vmtp_server,PORT_NULL);

	/*
	 * Set up the entry in the transport switch.
	 */
	transport_switch[TR_VMTP_ENTRY].sendrequest = netport_vmtp_sendrequest;
	transport_switch[TR_VMTP_ENTRY].sendreply = netport_vmtp_sendreply;

	return (TRUE);
}


