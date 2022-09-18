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
 * $Log:	vmtp_hdlrq.c,v $
 * Revision 2.4  89/03/09  20:49:07  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:04:14  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * Revision 2.2  88/08/24  02:04:34  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  22:09:59  mwyoung]
 * 
 * 16-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	MACH_NP: Changed external call to netmsg_input_rq().
 *
 * 12-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	MACH_NP: added a call to the kernel netport code when
 *	appropriate.
 *
 *  1-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Updated from new VMTP sources from Stanford (June 87).
 *
 *  2-Jun-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Do not retransmit a response for a duplicate request arriving
 *	after the server has given up in RECVREQ. The vihdr is not properly
 *	set up in that case, and we end up sending a message to ourselves!
 *
 * 29-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources.
 *
 */

#include <mach_vmtp.h>
#include <mach_np.h>

/*
 * $ Header: vmtp_hdlrq.c,v 2.2 88/08/24 02:04:34 mwyoung Exp $
 */

/*
 *     vmtp_hdlrq.c    0.1    10/19/86
 *    Written by Joyo Wijaya and Erik Nordmark
 */

/*
 * TODO
 */

#ifdef	FORWARD_DEBUG
#define VMTP_DEBUG
#define VMTPDEBUG
#define ESP_DEBUG
#endif

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>

#include <net/if.h>
#include <net/route.h>

#include "in.h"
#include "in_pcb.h"
#include "in_systm.h"
#include "ip.h"
#include "ip_var.h"
#include "vmtp_so.h"
#include "vmtp.h"
#include "vmtp_ip.h"
#include "vmtp_var.h"
#include "vmtp_send.h"
#include "vmtp_group.h"
#include "esp.h"
#include "esp_ip.h"
#include "esp_var.h"
#include "vmtp_ether.h"

/*
 * MACRO
 */
#define vmtp_firstgroupser(group) vmtp_maptoserver(vmtp_firstgroupmember(group))


/*
 * MACRO
 * Send an acknowledgement - vmtp_sendrqa() frees the data after the header
 * and sends the header portion.
 */
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
#define vmtp_ackunless(cond, m, vi, ack)        \
    if (cond) 					\
        m_freem(m);                        	\
    else {                                	\
        printf("vmtp_hdlrq(): ack\n");       	\
        vmtp_sendrqa(NULL, vi, ack);   		\
    }
#else
#define vmtp_ackunless(cond, m, vi, ack)	\
    if (cond) 					\
        m_freem(m);  				\
    else {         				\
        vmtp_sendrqa(NULL, vi, ack); 		\
    }
#endif	VMTP_DEBUG

#if	MACH_NP
extern struct vmtpeid	ipc_vmtp_server;
extern void		netmsg_input_rq();
#endif	MACH_NP


/*
 * Called by vmtp_input() when a request packet is received.
 * Process the request packet.
 * Running at splimp() from the mapping to the csr until the timer is stopped.
 */
vmtp_hdlrq(vi)
    register struct vmtpiphdr *vi;
{
    struct mbuf 	*m = dtom(vi);
    register struct vmtpcsr 	*csr;
    register struct vmtpser 	*ser;
    register u_short 		control = getvi_control(vi);
    int 			error;
    register int s = splimp();  

#if	VMTP_DEBUG
    printf("vmtp_hdlrq(0x%x), dlvrmsk=0x%x\n", (u_long)vi, vi->vi_dlvrmsk);
#endif


    /*
     * Locate remote client csr.
     */
    csr = vmtp_maptocsr(vi->vi_client, vremotecsrmap);

    if (csr == NULL) {

/* *** BEGIN NEW CLIENT *** */

        splx(s);
#if	VMTPDEBUG
        printf("vmtp_hdlrq(): New remote client\n");
#endif
        /*
         * New client.
         */

        /*
         * Locate the server entity record.
         */
        ser = vmtp_maptoserver(vi->vi_server);
        if (ser == NULL) 
            if (vmtp_groupeid(vi->vi_server)) { 
                if ((ser = vmtp_firstgroupser(vi->vi_server)) == NULL) {
                    /* 
                     * Group has no members
                     */
#if	VMTPDEBUG
        	    printf("vmtp_hdlrq(): no members in this group\n");
		    vmtp_dumpeid(&vi->vi_server, "vi_server", "vmtp_hdlrq");
#endif
                    m_freem(m);
                    return;
		}
	    } else if (vi->vi_multicast) {
#if	VMTPDEBUG
        	    printf("vmtp_hdlrq(): multicast - discarding\n");
#endif
                    m_freem(m);
                    return;

            } else {
                /* 
                 * Server entity does not exist.
                 */
                vmtp_ackunless(0, m, vi, VMTP_NONEXIST);
                return;
            }

        if (vmtp_securityreq(ser) && !vmtp_securepacket(vi->vi_type)) {
            /* 
             * Server requires security but transaction isn't 
             * secure.
             */
            vmtp_ackunless(0, m, vi, VMTP_SECUREREQ);
            return;
        }

        if (vmtp_notfirstpg(control) ||
            vmtp_notlastpg(control)) {
            /*
             * Streaming not supported.
             */
            vmtp_ackunless(0, m, vi, VMTP_NOSTREAMING);
            return;
        }

        /*
         * Allocate and initialize a new remote csr.
         * Insert the csr into the map. 
         */
        if ((csr = vmtp_newcsr(vi->vi_client, vremotecsrmap)) == NULL) {
            /*
             * No csr is available.
             */
            vmtp_ackunless(vmtp_groupeid(vi->vi_server), m, vi, VMTP_BUSY);
            return;
        }

        /*
         * Set some initial/default values. They are used
         * if the probe isn't sent.
         */
        csr->vc_hostaddr = vi->vi_src;
	csr->vc_ifp = vi->vi_ifp;
	csr->vc_inpktgap = getvi_inpktgap(vi);
        csr->vc_mtu = VMTP_MAXBLKPACKET;
        csr->vc_roundtrip = VTS_ROUNDTRIP * 20;     /* in ms */
        csr->vc_encryptqual = ENCRYPT_NONE;
        csr->vc_hdltimeo = vmtp_hdlrcsrtimeo;
    	csr->vc_flags = VCF_NONE;

        if (vmtp_authreq(ser) && csr->vc_state != VC_AWAITPROBE) {
#ifdef	ESP_DEBUG
            printf("vmtp_hdlrq(): authentication required\n");
#endif
            *csr->vc_vihdr = *vi;
            csr->vc_state = VC_AWAITPROBE;
            csr->vc_dlvrmsk = 0;

#define ei ((struct espiphdr *)csr->vc_vihdr)            
            seteiq_authdomain(ei, vmtp_securityreq(ser) ? 2 : 1);
            seteiq_authversion(ei, vmtp_securityreq(ser) ? 3 : 2);
            ei->eiq_mtu = vmtp_mtu(csr);
            esp_time(ei->ei_tmstamp);
            csr->vc_tmstamp = ei->ei_tmstamp;
            ei->ei_code = ESP_FULLPROBE;
            setei_control(ei, ECTL_SOP);
	    if (vmtp_groupeid(vi->vi_server) && vmtp_delayedresp(control)) {
		timeout(esp_delayedprobe, csr, 0);
		m_freem(m);
		return;
	    }
            esp_sendprq(csr, ei);
            vmtp_starttimer(csr, ET_RETRANSMIT);
            m_freem(m);
            return;
#undef ei
        }
        *csr->vc_vihdr = *vi;
        csr->vc_state = VC_RECVREQ;
        csr->vc_dlvrmsk = 0;
    }

/* *** END NEW CLIENT *** */

    else {
	/* 
	 * Check if destined for this vmtp module (multicast)
	 * and that the server exists.
	 */
        ser = vmtp_maptoserver(vi->vi_server);
        if (ser == NULL) 
            if (vmtp_groupeid(vi->vi_server)) { 
                if ((ser = vmtp_firstgroupser(vi->vi_server)) == NULL) {
                    /* 
                     * Group has no members
                     */
#if	VMTPDEBUG
        	    printf("vmtp_hdlrq(): no members in this group\n");
		    vmtp_dumpeid(&vi->vi_server, "vi_server", "vmtp_hdlrq");
#endif
		    splx(s);
                    m_freem(m);
                    return;
		}
	    } else if (vi->vi_multicast) {
#if	VMTPDEBUG
        	    printf("vmtp_hdlrq(): multicast - discarding\n");
#endif
                    m_freem(m);
                    return;

            } else {
                /* 
                 * Server entity does not exist.
                 */
		splx(s);
                vmtp_ackunless(0, m, vi, VMTP_NONEXIST);
                return;
            }

        if (csr->vc_state == VC_AWAITREQ) {
            /*
             * Used after a probe response was received and before 
             * the first following request packet and also when
	     * the csr was created by vmtp_probe().
             */
#if	VMTPDEBUG
            printf("vmtp_hdlrq(): awaited a request\n");
#endif
            *csr->vc_vihdr = *vi;
            csr->vc_state = VC_RECVREQ;
            csr->vc_dlvrmsk = 0;
            if (csr->vc_dataseg) {
                if (vcf_mbuf(csr)) {
                    m_freem(csr->vc_dataseg);
                }
                csr->vc_dataseg = NULL;
            }
        }
        if (csr->vc_transid == vi->vi_transid) {

/* *** BEGIN CURRENT TRANSACTION *** */

            /*
             * Matches current transaction.
             */
#if	VMTPDEBUG
            printf("vmtp_hdlrq(): matches current transaction\n");
#endif

            /* Note: retransmissions caused by request acks with RETRY
             * will be addressed to a group member on this host and not
             * to the group.
	     * If forwarding the csr will contain the new server and not the 
	     * old (forwarding) one, but retransmissions have the old one.
             */
            if (!vmtp_sameeid(csr->vc_server, vi->vi_server) && 
	      !vcf_forwarding(csr)) { 
	        if (vcf_group(csr)) { 
#if	VMTPDEBUG
            printf("vmtp_hdlrq(): NOT same entity (group): make same! \n");
#endif
                    vi->vi_server = csr->vc_origserver;
                } else {
                    splx(s);
#if	VMTPDEBUG
            	    printf("vmtp_hdlrq(): vc_flags = 0x%x\n", csr->vc_flags);
#endif
                    vmtp_ackunless(0, m, vi, VMTP_PROERROR);
                    return;
        	}
	    }

            if (csr->vc_state == VC_AWAITPROBE) {
                /*
                 * Drop the packet and let the timeout mechanisms
                 * re-probe the guy if necessery. (the probe reponse
                 * might be on its way!)
                 */
                splx(s);
#if	VMTPDEBUG
            printf("vmtp_hdlrq(): in VC_AWAITPROBE - dropping\n");
#endif
                m_freem(m);
                return;
            }

	    /*
	     * A gross hack to make local forwarding work. The csr is both
	     * being forwarded to and from to both vcf_recvforward and
	     * vcf_forwarding is set.
	     */
            if (getvi_fnctcode(vi) == VMTP_FWDREQ &&
	      csr->vc_state == VC_PROCESSING && 
	      vcf_recvforward(csr) && vcf_forwarding(csr) &&
	      vmtp_localaddr(vi->vi_src)) {
#if	VMTPDEBUG
        	printf("vmtp_hdlrq(): local frq\n");
#endif
                *csr->vc_vihdr = *vi;
                csr->vc_state = VC_RECVREQ;
                csr->vc_dlvrmsk = 0;
                if (csr->vc_dataseg) {
                    if (vcf_mbuf(csr)) {
                        m_freem(csr->vc_dataseg);
                    }
                    csr->vc_dataseg = NULL;
                }
		if (!vmtp_datagram(vi->vi_code))
		    csr->vc_flags |= VCF_NILFWDRQ;
		goto local_frq;
	    }

retry:
            if (csr->vc_state == VC_PROCESSING) {
		if (vcf_group(csr)) {
			csr = vmtp_nextcsr(csr);
			if (csr != NULL) {
#if	VMTPDEBUG
        			printf("vmtp_hdlrq(): RETRYING csr\n");
#endif
				goto retry;
			}
		}
                splx(s);
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
        printf("vmtp_hdlrq(): a duplicate or too old request\n");
#endif
                vmtp_ackunless(0, m, vi, VMTP_OK);
                return;
            }

	    /*
	     * Check for conflicts between frq and rq packets comming at the
	     * same time. The first one with the current transid committed
	     * to that type of request.
	     */
            if (getvi_fnctcode(vi) != getvi_fnctcode(csr->vc_vihdr) &&
		csr->vc_state != VC_RESPONDED) {
#ifdef	FORWARD_DEBUG
                printf("vmtp_hdlrq(): frq-rq conflict causes drop!\n");
#endif
                splx(s);
                m_freem(m);
                return;
            }


            if (!vmtp_stoptimer(csr)) {
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
                printf("vmtp_hdlrq(): STOPTIMER FAILED\n");
#endif
                splx(s);
                m_freem(m);
                return;
            }    
local_frq:
            splx(s);

            if (csr->vc_state == VC_RESPONDED) {
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
                printf("vmtp_hdlrq(): a responded request\n");
#endif
#ifdef	MACH
		/*
		 * Ignore weird case of server giving up in RECVREQ,
		 * then receiving a duplicate request. (DPJ)
		 */
		if (vmtp_invalidresp(csr->vc_code)) {
			vmtp_starttimer(csr, vts_discardcsr(csr));
			m_freem(m);
	                return;
		}
#endif	MACH

                /*
                 * Duplicate.
                 */
                if (vmtp_respdiscarded(csr->vc_code) && vcf_group(csr)) {
#if	VMTPDEBUG
                    printf("vmtp_hdlrq(): discarded and multicast\n");
#endif
                    vmtp_starttimer(csr, vts_discardcsr(csr));
                    m_freem(m);
                    return;
                }
		/*
		 * Detect if a forwarding operation has been redone to many
		 * times and if so tell the client.
		 * The VCF_REDO flag is used below to tell forward() not to 
		 * reset the retransmission count and set the APG bit in the
		 * forward request.
		 */
		if (vcf_forwarding(csr) &&
		  ++csr->vc_rexmtcnt > VMTP_MAXREXMTCNT) {
#ifdef	FORWARD_DEBUG
                    printf("vmtp_hdlrq(): forwarded and TIMED OUT!\n");
#endif
		    vi->vi_server = csr->vc_server;
		    vmtp_sendrqa(NULL, vi, VMTP_REXMTTIMEO);
		    vmtp_starttimer(csr, vts_discardcsr(csr));
		    return;
		}
		/*
		 * Retransmit response/redo request:
		 * At the forwarder the request will be redone if the 
		 * response/forward was idempotent. This is subject to 
		 * race conditions if the new server refuses retransmitted
		 * forward requests while accepting the first one(s) 
		 * (retransmitted one caused by redoing the transaction or
		 * just retransmitting the frq) which can cause the
		 * forwarded request to be done multiple times at the new server
	 	 * even if its response isn't idempotent. (Idependent of whether
		 * the forward was idempotent)
		 */
                if (!vmtp_datagram(csr->vc_code)) {
		    /*
		     * If forwarded check if a rqa has to be sent to keep
		     * the client happy.
		     */
		    if (vcf_forwarding(csr) && 
		      vmtp_acknowledgepg(getvi_control(vi))) {
			union vmtp_addr tempaddr;
			struct ifnet *tempifp;
#ifdef	FORWARD_DEBUG
                        printf("vmtp_hdlrq(): forwarded => send rqa\n");
#endif
			tempaddr = csr->vc_hostaddr;
			tempifp = csr->vc_ifp;
			csr->vc_hostaddr = vi->vi_src;
			csr->vc_ifp = vi->vi_ifp;
			vmtp_sendrqa(csr, vi, VMTP_OK);
			csr->vc_hostaddr = tempaddr;
			csr->vc_ifp = tempifp;
		    }
                    /*
                     * Resend response. If the response has been
                     * discarded, only the mcb will be sent.
		     * Note if the request has been forwarded this will cause
		     * the forward request or forward response to be 
		     * retransmitted.
                     */
                    if (vmtp_segmentdata(csr->vc_code) && csr->vc_dataseg) {
                        csr->vc_txmsk = vmtp_usrdlvrmskset(csr->vc_code)
                                          ? csr->vc_usrdlvrmsk 
                                          : vmtp_segsizetomsk(csr->vc_segsize);
                    } else {
                        csr->vc_txmsk = 0;
                    }
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
                    printf("vmtp_hdlrq(): resend response\n");
#endif
                    if (error = vmtp_sendpg(csr, VMTP_RETRANSMIT, 0)) {
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
                        printf("vmtp_hdlrq(): resend failed (%d)\n", error);
#endif
                    }
                    if (vmtp_respdiscarded(csr->vc_code) ||
                        !vmtp_acknowledgepg(getvi_control(csr->vc_vihdr)))
                        vmtp_starttimer(csr, vts_discardcsr(csr));
                    else
                        vmtp_starttimer(csr, vts_retransmit(csr));
                    m_freem(m);
                    return;
                }
                else {
                    /*
                     * Idempotent reply.
                     * Redo request to provide response.
                     */
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
                    printf("vmtp_hdlrq(): redo request\n");
#endif
		    if (vcf_group(csr))
			vmtp_csrcleanup(csr);
		    if (vcf_forwarding(csr)) {
			/*
			 * VCF_FORWARDING is reset since the redoing is
			 * conceptually a new request (w.r.t. forwarding).
			 * VCF_RECVFORWARD is reset since the request
			 * could have been forwarded locally.
			 * VCF_REDO is SET to avoid resetting the timeout count
			 * when forwarding and setting the APG in the frq.
			 * Note: if a local forward is done and the forwarders
			 * operation isn't idempotent but the reply is, this
			 * will cause the operation to be redone at both
			 * the forwarder and the replying server, which violates
			 * the semantics of non-idempotency!! (This can be 
			 * solved if the server remebers (in the VMTP module) 
			 * that the request was received as a non-idempotent frq
			 * and turns of the idempotency bit in the reply. This
			 * is only needed for local forwards.)
			 */
#ifdef	FORWARD_DEBUG
                        printf("vmtp_hdlrq(): redoing: reset flag et.c.\n");
#endif
			csr->vc_flags &= ~(VCF_FORWARDING | VCF_RECVFORWARD);
			csr->vc_flags |= VCF_REDO;
			csr->vc_hostaddr = vi->vi_src;
			csr->vc_ifp = vi->vi_ifp;
		    }

                    *csr->vc_vihdr = *vi;
                    csr->vc_state = VC_RECVREQ;
                    csr->vc_dlvrmsk = 0;
                    if (csr->vc_dataseg) {
                        if (vcf_mbuf(csr)) {
                            m_freem(csr->vc_dataseg);
                        }
                        csr->vc_dataseg = NULL;
                    }
                    csr->vc_flags &= ~(VCF_RECVFORWARD | VCF_MBUF | VCF_GROUP |
					VCF_NILFWDRQ);
                }
            }
        

            else {  
		/* 
		 * csr->vc_state == VC_RECVREQ 
		 * (or VC_PROCESSING if local frq)
		 */
#if	VMTPDEBUG
                printf("vmtp_hdlrq(): receiving request\n");
#endif

            }            
        }

/* *** END CURRENT TRANSACTION *** */

/* *** BEGIN OLD TRANSACTION *** */
 
        else if ((csr->vc_transid > vi->vi_transid && 
	  (u_long)(csr->vc_transid - vi->vi_transid) < (u_long)0x80000000) ||
	   (u_long)(vi->vi_transid - csr->vc_transid) > (u_long)0x80000000) {
            splx(s);
#if	VMTPDEBUG  || VMTP_RETRANS_DEBUG
            printf("vmtp_hdlrq(): Old transaction\n");
#endif
            /*
             * Old Transaction.
             */
            m_freem(m);
            return;
        }

/* *** END OLD TRANSACTION *** */

/* *** BEGIN NEW TRANSACTION *** */

        else {
            /*
             * Otherwise, a new message transaction for an existing csr.
             */
#if	VMTPDEBUG
            printf("vmtp_hdlrq(): A new transaction for an existing csr\n");
#endif
            if (csr->vc_state == VC_AWAITPROBE) {
                /*
                 * Drop the packet and let the timeout mechanisms
                 * re-probe the guy if necessery. (the probe reponse
                 * might be on its way!)
                 */
                splx(s);
#if	VMTPDEBUG
                printf("vmtp_hdlrq(): in VC_AWAITPROBE - dropping\n");
#endif
                m_freem(m);
                return;
            }

            if (csr->vc_state != VC_RESPONDED) {
                /* 
                 * Handling datagrams and multicast requests that
                 * are not taken care of by the server yet:
                 *
                 * Drop datagrams if they come too fast. If the
                 * client sends a (normal) request after a 
                 * datagram, the datagram will be thrown away
                 * if not processed already.
                 * Note that the probability of dropping the
                 * new datagram request is very small - only if the 
                 * csr has been removed from the server's queue but
                 * not yet reinserted into the timeout queue. For
                 * multicast request the old one will be dropped
                 * even if being serviced by the server.
                 */
                struct vmtpsynq *q;
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
                printf("vmtp_hdlrq(): old transaction UNPROCESSED\n");
#endif
                
                if ((q = csr->vc_qhead) != NULL) {
                    /*
                     * Remove old request - ready to put the new in the csr.
                     * Note that the ser below need not be the same as the ser
		     * found by the mapping. Especially, if local forwarding 
		     * is done the request can be processed at the new server
		     * and will be removed if a new transaction is sent to the
		     * forwarder!
                     */
                    vmtp_synqdeq(csr);
                    if (q->vq_type = VQ_SERVER)
#define ser ((struct vmtpser *)q)
                        if (ser->vs_cnext == &ser->vs_queue.vq_queue) {
                            ser->vs_flags &=  ~VS_REQQUEUED;
                        }
#undef ser
		    if (vcf_group(csr))
			vmtp_csrcleanup(csr);
                    if (csr->vc_dataseg) {
                        if (vcf_mbuf(csr)) {
                            m_freem(csr->vc_dataseg);
                        }
                        csr->vc_dataseg = NULL;
                    }
	            csr->vc_flags = VCF_NONE;
                    splx(s);
                } else {
                    /* not in queue or being processed */
                    splx(s);
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
         printf("vmtp_hdlrq(): unprocessed: not in queue or being processed\n");
#endif
                    m_freem(m);
                    return;
                }
            }

            else {
                if (!vmtp_stoptimer(csr)) {
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
                    printf("vmtp_hdlrq(): STOPTIMER FAILED\n");
#endif
                    splx(s);
                    m_freem(m);
                    return;
                }    
	        if (vcf_group(csr))
		    vmtp_csrcleanup(csr);
                splx(s);
            }


            if (vmtp_securityreq(ser) && !vmtp_securepacket(vi->vi_type)) {
                /* 
                 * Server requires security but transaction isn't
                 * secure.
                 */
                vmtp_ackunless(0, m, vi, VMTP_SECUREREQ);
                vmtp_starttimer(csr, vts_discardcsr(csr));
                return;
             }

            if (vmtp_notfirstpg(control) ||
                vmtp_notlastpg(control)) {
                /*
                 * Streaming not supported.
                 */
                vmtp_ackunless(0, m, vi, VMTP_NOSTREAMING);
                vmtp_starttimer(csr, vts_discardcsr(csr));
                return;
            }

            if (vmtp_authreq(ser) && 
              !vmtp_sameeid(csr->vc_server, vi->vi_server)) {
                struct vmtpser *ser1;

		/*
		 * Check if a probe version 2 was sent for previous server.
		 * Don't bother checking group members.
		 */
                ser1 = vmtp_maptoserver(csr->vc_server);
		if (!ser1 || !vmtp_authreq(ser1)) {
		    /*
		     * Probe the client for authentication info
		     */
#ifdef	ESP_DEBUG
                    printf("vmtp_hdlrq(): authentication required - probe\n");
#endif
	            *csr->vc_vihdr = *vi;
	            csr->vc_state = VC_AWAITPROBE;
                    csr->vc_dlvrmsk = 0;
	            if (csr->vc_dataseg) {
        	        if (vcf_mbuf(csr)) {
                	    m_freem(csr->vc_dataseg);
	                }
        	        csr->vc_dataseg = NULL;
	            }

#define ei ((struct espiphdr *)csr->vc_vihdr)            
	            seteiq_authdomain(ei, vmtp_securityreq(ser) ? 2 : 1);
	            seteiq_authversion(ei, vmtp_securityreq(ser) ? 3 : 2);
	            ei->eiq_mtu = vmtp_mtu(csr);
	            esp_time(ei->ei_tmstamp);
	            csr->vc_tmstamp = ei->ei_tmstamp;
	            ei->ei_code = ESP_FULLPROBE;
	            setei_control(ei, ECTL_SOP);
	    	    if (vmtp_groupeid(vi->vi_server) && 
		      vmtp_delayedresp(control)) {
			timeout(esp_delayedprobe, csr, 0);
			m_freem(m);
			return;
		    }
	            esp_sendprq(csr, ei);
	            vmtp_starttimer(csr, ET_RETRANSMIT);
	            m_freem(m);
	            return;
#undef ei
		}
	    }

            *csr->vc_vihdr = *vi;
            csr->vc_state = VC_RECVREQ;
            csr->vc_dlvrmsk = 0;
            if (csr->vc_dataseg) {
                if (vcf_mbuf(csr)) {
                    m_freem(csr->vc_dataseg);
                }
                csr->vc_dataseg = NULL;
            }
            if (getvi_fnctcode(vi) == VMTP_REQ) {
                /* 
                 * Reset the host address in case this request 'passed'
                 * a forward request on the way in. (We're running below splimp
		 * during the call form hdlfrq to hdlrq.)
                 */
                csr->vc_hostaddr = vi->vi_src;
		csr->vc_ifp = vi->vi_ifp;
		csr->vc_inpktgap = getvi_inpktgap(vi);
                csr->vc_flags = VCF_NONE;
    	    } else
		csr->vc_flags &= ~(VCF_MBUF | VCF_GROUP | 
				   VCF_NILFWDRQ | VCF_REDO);
        }
/* *** END NEW TRANSACTION *** */
    }


    /*
     * Now proceed to store the data segment, and if the request is
     * complete then queue the csr into server queue and wake up
     * the server if necessary.
     */

    if (vmtp_segmentdata(csr->vc_code)) {
        csr->vc_flags |= VCF_MBUF;
        vmtp_savesegment(csr, vi);
    }
    else
        m_freem(m);

    if (vmtp_segmentdata(csr->vc_code) && 
      csr->vc_dlvrmsk != (vmtp_usrdlvrmskset(csr->vc_code)
                ? csr->vc_usrdlvrmsk 
                : vmtp_segsizetomsk(csr->vc_segsize))) {
#if	VMTPDEBUG
        printf("vmtp_hdlrq(): Not everything received yet!\n");
#endif
        /* Not everything received yet! */
        csr->vc_rexmtcnt = 0;
        vmtp_starttimer(csr, vts_receivepg(csr));
        return;
    }


    /*
     * We have received last packet in packet group.
     *
     * Deliver request message.
     */
    csr->vc_state = VC_PROCESSING;


    if (vcf_recvforward(csr)) {
	/*
	 * Idempotent forward is not the same as datagram as to the
	 * state transitions at the server receiving it. (Datagram will
	 * cause the state to be RESPONDED immediately when they are received.)
	 */
#ifdef	FORWARD_DEBUG
    	printf("vmtp_hdlrq(): resetting DGM bit\n");    
#endif
	csr->vc_code &= ~VU_DGM;
    }

    if (vmtp_groupeid(csr->vc_server)) {
#if	VMTPDEBUG
        printf("vmtp_hdlrq(): delivering to a group\n");
#endif
        csr->vc_flags |= VCF_GROUP;
        csr->vc_origserver = csr->vc_server;     
	if (vmtp_tomanager(csr->vc_server))
		return vmtp_manager(csr);
        vmtp_delivertogroup(csr, csr->vc_server);
        return;
    }

    if (vmtp_conditional(csr->vc_code) && !vmtp_waiting(ser)) {
        /* discard csr */
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
        printf("vmtp_hdlrq(): Server busy - VMTP_NOTAWAIT\n");    
#endif
        vmtp_sendrqa(csr,csr->vc_vihdr, VMTP_NOTAWAIT);
        vmtp_freecsr(csr, vremotecsrmap);
	return;
    }

    if (vmtp_acknowledgepg(control)) {
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
        printf("vmtp_hdlrq(): APG set - VMTP_OK\n");    
#endif
        vmtp_sendrqa(csr, csr->vc_vihdr, VMTP_OK);
    }
        
#if	VMTP_DEBUG
    printf("vmtp_hdlrq(): queueing request!\n");    
#endif
    vmtp_queuerequest(csr, ser);
#if	MACH_NP
	if (vmtp_sameeid(ipc_vmtp_server,ser->vs_server)) {
		netmsg_input_rq(ser->vs_server);
	} else
#endif	MACH_NP
    wakeup(ser);

} /* vmtp_hdlrq */




