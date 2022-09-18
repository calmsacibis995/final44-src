
/* dvmrp.h */
#define	DVMRP_LIMIT_METRIC	0, 127
#define	DVMRP_LIMIT_THRESHOLD	0, 127

#define	IF_CONFIG_METRIC		1
#define	IF_CONFIG_THRESHOLD		2
#define	IF_CONFIG_IGNORE		3
#define	IF_CONFIG_LCLADDR		4
#define	IF_CONFIG_MAX			5

extern int doing_dvmrp;
extern adv_entry *dvrp_policy;

/* dvmrp.c */

int doing_dvmrp;
adv_entry *dvrp_policy;

int
dvmrp_parse_tunnel __PF3(peer, sockaddr_un *,
			 list, config_entry *,
			 parse_error, char *)
{
    config_entry *cp;
    struct dvm_vif *tun;

    VIF_LIST(tun) {
	if (sockaddrcmp_in(tun->vif_rmt_addr, peer)) {
	    sprintf(parse_error, "duplicate tunnel to %A",
		    tun->vif_rmt_addr);
	    return TRUE;
	}
    } VIF_LIST_END(tun) ;

    tun = (struct dvm_vif *) task_block_alloc(dvm_vif_index);
    tun->vif_rmt_addr = peer;
    tun->vif_metric = tun->vif_threshold = (metric_t) -1;

    CONFIG_LIST(cp, list) {
	switch (cp->config_type) {
	case DVMRP_CONFIG_METRIC:
	    tun->vif_metric = (metric_t) cp->config_data;
	    break;

	case DVMRP_CONFIG_THRESHOLD:
	    tun->vif_thresold = (metric_t) cp->config_data;
	    break;

	case DVMRP_CONFIG_LCLADDR:
	    tun->vif_addrent_lcl = (if_addr_entry *) cp->config_data;
	    break;
	}
    } CONFIG_LIST_END(cp, list) ;

    if (tun->vif_metric == (metric_t) -1
	|| tun->vif_threshold == (metric_t) -1) {
	/* Something is missing */

	sprintf(parse_error, "missing metric and/or threshold");
	return TRUE;
    }
    /* XXX - Put it in the list */

    return FALSE;
}


static void
dvmrp_ifachange __PF2(tp, task *,
		   ifap, if_addr *)
{
    struct dvm_vif *vif = (struct dvm_vif *) ifap->ifa_ps[RTPROTO_DVMRP].ips_data;

    if (socktype(ifap->ifa_addr) != AF_INET
	|| !BIT_TEST(ifap->ifa_state, IFS_MULTICAST)) {
	/* Not Inet or not multicast capable - ignore it */

	/* XXX - What about P2P interfaces */
	return;
    }
    
    switch (ifap->ifa_change) {
    case IFC_NOCHANGE:
    case IFC_ADD:
	if (BIT_TEST(ifap->ifa_state, IFS_UP)) {
	Up:
	    {
		metric_t metric = 0;
		metric_t threshold = 0;
		int ignore = 0;
		config_entry **list = config_resolv(dvmrp_policy,
						    ifap,
						    DVMRP_CONFIG_MAX);

		if (list) {
		    int type = DVMRP_CONFIG_MAX;
		    config_entry *cp;

		    /* Fill in the parameters */
		    while (--type) {
			if (cp = list[type]) {
			    switch (type) {
			    case DVMRP_CONFIG_METRIC:
				metric = (metric_t) cp->config_data;
				break;

			    case DVMRP_CONFIG_THRESHOLD:
				threshold = (metric_t) cp->config_data;
				break;

			    case DVMRP_CONFIG_IGNORE:
				ignore = (int) cp->config_data;
				break;

			    default:
				assert(FALSE);
				break;
			    }
			}
		    }

		    config_resolv_free(list, DVMRP_CONFIG_MAX);
		}

		if (!vif) {
		    /* No current interface */

		    if (!ignore) {
			/* Create a VIF */

			vif = dvm_new_intf(ifap);
			ifap->ifa_ps[RTPROTO_DVMRP].ips_data = (void_t) vif;
			vif->vif_metric = metric;
			vif->vif_threshold = threshold;
		    }
		} else if (vif) {
		    /* Existing interface */

		    if (ignore) {
			/* Delete a VIF */

			dvm_remove_intf(vif);
			ifap->ifa_ps[RTPROTO_DVMRP].ips_data = (void_t) 0;
		    } else {
			/* Something may have changed */

			/* XXX - Is it OK just to assign them? */
			vif->vif_metric = metric;
			vif->vif_threshold = threshold;
		    }
		}
	    }
	}
	break;
	
    case IFC_DELETE:
	break;
	
    case IFC_DELETE|IFC_UPDOWN:
    Down:
	if (vif) {
	    /* This interface has gone down, delete the VIF */

	    dvm_remove_intf(vif);
	    ifap->ifa_ps[RTPROTO_DVMRP].ips_data = (void_t) 0;
	}
	break;

    default:
	/* Something has changed */

	if (BIT_TEST(ifap->ifa_change, IFC_UPDOWN)) {
	    if (BIT_TEST(ifap->ifa_state, IFS_UP)) {
		/* Transition to UP */

		goto Up;
	    } else {
		/* Transition to DOWN */

		goto Down;
	    }
	}

	if (vif) {
	    /* MTU */
	    /* METRIC */
	    if (BIT_TEST(ifap->ifa_change, IFC_BROADCAST)) {
		/* Broadcast changed */

		/* XXX - Do you do anything with the broadcast? */
	    }
	    if (BIT_TEST(ifap->ifa_change, IFC_NETMASK)) {
		/* Netmask changed */

		/* XXX - Do you do anything with the netmask? */
		/* XXX - Are there some neighbors we can no longer see? */
	    }
	    if (BIT_TEST(ifap->ifa_change, IFC_ADDR)) {
		/* Local address of P2P changed */

		/* XXX - What to do here */
	    }
	}
	break;
    }

    /* Check for tunnel changes */
    VIF_LIST(vif) {
	if (vif->vif_lcladdr) {
	    if (vif->vif_lcladdr->ifae_n_if && !vif_is_up(vif)) {
		/* Start tunnel */

		/* XXX */
	    } else if (!vif->vif_lcladdr->ifae_n_if && vif_is_up(vif)) {
		/* Stop tunnel */

		/* XXX */
	    }
	}
    } VIF_LIST_END(vif) ;
}
