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
 * $Log:	esp_timeout.c,v $
 * Revision 2.3  89/03/09  20:42:31  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:57:29  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
 
#include <mach_vmtp.h>

/*
 * $ Header: esp_timeout.c,v 2.1 87/08/18 16:31:09 mrt Exp $
 */

/*
 * 	esp_timeout.c		2/26/87
 *	Written by Erik Nordmark
 */

/*
 * Note:
 *	esp_hdltimeo should only be used for probe_entity() related
 * 	probes. When a server probes a client as a part of a message
 *	transaction the normal vmtp_hdlrcsrtimeo should be used.
 */

/*
 * TODO
 *
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
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
#include "vmtp_buf.h"
#include "esp.h"
#include "esp_ip.h"
#include "esp_var.h"
#include "esp_cache.h"

/* 
 * Handle esp timeouts. When the client is worken up one has to make sure that
 * wakeup is on the csr that the process is sleeping on, since it might have
 * used another csr for both sending the probe and timeouts.
 */
esp_hdltimeo(csr)
    register struct vmtpcsr *csr;
{
    register struct espiphdr *ei = (struct espiphdr *)csr->vc_vihdr;

#ifdef	ESP_DEBUG
    printf("esp_hdltimeo(): csr = 0x%x\n", csr);
#endif

    if (++csr->vc_rexmtcnt >= ESP_MAXREXMTCNT) {
      struct vmtpcsr *csr1;
#ifdef	ESP_DEBUG
        printf("esp_hdltimeo(): no more retransmissions\n");
#endif
        csr1 = vmtp_maptocsr(csr->vc_client, vremotecsrmap);
        if (csr1 == NULL) {
#ifdef	ESP_DEBUG
        printf("esp_hdltimeo(): EVERYONE seems to have LEFT!\n");
#endif
            if (vcf_mbuf(csr)) {
                m_freem(csr->vc_dataseg);
            }
            m_free(dtom(csr->vc_vihdr));
            vmtp_dealloccsr(csr);
            return;
        }
        csr1->vc_probecode = VMTP_REXMTTIMEO;
        csr1->vc_action = VCA_DELIVER;
        wakeup(csr1);
        return;
    }

    esp_time(ei->ei_tmstamp);
    csr->vc_tmstamp = ei->ei_tmstamp;

#ifdef	ESP_DEBUG
    printf("esp_hdltimeo(): retransmitting, tmstamp = 0x%x\n", ei->ei_tmstamp);
#endif
    esp_sendprq(csr, ei);
    vmtp_starttimer(csr, ET_RETRANSMIT);
} /* esp_hdltimeo */

/*
 * Entity state timeout: scan all csr's
 */
esp_hdlestimeo()
{
    register struct vmtpcsr *csr;
    register int i;

#ifdef	ESP_DEBUG
    printf("esp_hdlestimeo(): starting to scan csr's\n");
#endif
    for (i = 0; i < VMTP_HASHMAPSIZE; i++) {
        for (csr = vremotecsrmap[i]; csr != NULL; csr = csr->vc_next) {
            if (++csr->vc_verifyint > ESP_MAXVERIFYINT) {
                int s = splimp();
                if (csr->vc_qhead) {
                    if (csr->vc_qhead->vq_type == VQ_SERVER && 
		      !vmtp_isreceived(csr,(struct vmtpser *)csr->vc_qhead)) {
#ifdef	ESP_DEBUG
		        printf("esp_hdlestimeo(): signaling the server!!!\n");
#endif
                        vmtp_signal((struct vmtpser *)csr->vc_qhead, csr);
                    }
                    vmtp_synqdeq(csr);
#ifdef	ESP_DEBUG
            printf("esp_hdlestimeo(): discarding a csr!!!\n");
#endif
                    vmtp_freecsr(csr, vremotecsrmap);
                    splx(s);
                } else {
                    splx(s);
/* #ifdef ESP_DEBUG */
		    printf("esp_hdlestimeo(): can't discard csr!!!\n");
		    vmtp_dumpeid(&csr->vc_client, "client", "esp_hdlestimeo"); 
/* #endif */
                }
            } else if (csr->vc_verifyint > 
                   ESP_MAXVERIFYINT - ESP_MAXREXMTCNT) {
                struct mbuf *m;
                struct espiphdr *ei;
#ifdef	ESP_DEBUG
                printf("esp_hdlestimeo(): probing!!!!!!\n");
#endif
                m = vmtp_copyvihdr(csr->vc_vihdr);
                if (!m) {
#ifdef	ESP_DEBUG
                printf("esp_hdlestimeo(): no buffers\n");
#endif
                    continue;
                }

                ei = mtod(m, struct espiphdr *);
                ei->ei_transid = 0;
                esp_time(ei->ei_tmstamp);
                csr->vc_tmstamp = ei->ei_tmstamp;
                seteiq_authversion(ei, 1);
                seteiq_authdomain(ei, 
                  (csr->vc_encryptqual == ENCRYPT_NONE) ? 1 : 2);
                ei->eiq_mtu = vmtp_mtu(csr);
                setei_control(ei, 0);
                ei->ei_code = ESP_MINPROBE;
                esp_sendprq(csr, ei); 
                m_free(dtom(ei));
            }
        }
    }

#ifdef	ESP_DEBUG
    printf("esp_hdlesttimeo(): DONE to scan csr's\n");
#endif

    timeout(esp_hdlestimeo, (caddr_t)0, hz*ESP_SCANINTERVAL);
} /* esp_hdlestimeo */

