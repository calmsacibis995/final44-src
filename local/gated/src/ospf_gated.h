/*
 * $Id: ospf_gated.h,v 1.38.2.5 1994/09/20 15:48:51 jch Exp $
 */

/* %(Copyright.header) */


#ifndef OSPF_PORT_H
#define OSPF_PORT_H


/* Convert global_tod to char string */
#define ospf_get_ctime() time_string

#define ospf_get_sys_time()

/* Checksum calculations */
#define	ospf_checksum_sum(cp, len, sum)	sum += iso_cksum((void_t) cp, (size_t) len, (byte *) &(cp)->ls_hdr.ls_chksum)

#define	ospf_checksum(cp, len)	(void) iso_cksum((void_t) cp, (size_t) len, (byte *) &(cp)->ls_hdr.ls_chksum)

#define	ospf_checksum_bad(cp, len)	iso_cksum((void_t) cp, (size_t) len, (byte *) 0)

#define	INTF_MTU(intf) \
		(size_t) ((((intf)->type == VIRTUAL_LINK) ? OSPF_MAXVPKT : (intf)->ifap->ifa_mtu) - OSPF_TRL_SIZE(intf))
#define	INTF_ADDR(intf)		sock2ip((intf)->ifap->ifa_addr)
#define	INTF_LCLADDR(intf)	sock2ip((intf)->ifap->ifa_addr_local)
#define	INTF_NET(intf)		sock2ip((intf)->ifap->ifa_net)
#define	INTF_MASK(intf)		sock2ip((intf)->ifap->ifa_netmask)


/* XXX - Maybe we need an intermediate structure? */
#define	ifa_ospf_intf	ifa_ps[RTPROTO_OSPF].ips_datas[0]
#define	ifa_ospf_nh	ifa_ps[RTPROTO_OSPF].ips_datas[1]
#define	ifa_ospf_nh_lcl	ifa_ps[RTPROTO_OSPF].ips_datas[2]

#define	IF_INTF(ifap)	((struct INTF *)(ifap)->ifa_ospf_intf)


#define	OSPF_IFPS_ALLSPF	IFPS_KEEP1	/* Joined All SPF group */
#define	OSPF_IFPS_ALLDR		IFPS_KEEP2	/* Joined All DR group */

#undef	INTF_STATUS_CHANGE

#define	ospf_ifchk(ifap)	BIT_TEST(ifap->ifa_state, IFS_UP)

#define IP_PROTOCOL(IP) (IP)->ip_p
#define IP_LENGTH(IP) 	(IP)->ip_len

#define	OSPF_AUTH_NONE			0	/* No authentication */
#define	OSPF_AUTH_SIMPLE		1	/* Simple password */
#define	OSPF_AUTH_MD5			2	/* MD5 crypto checksum */

/* Export types */
#define	OSPF_EXPORT_TYPE1	0x01
#define	OSPF_EXPORT_TYPE2	0x02

#define	OSPF_EXPORT_TAG		0x04		/* Tag is present */
#define	OSPF_EXPORT_TAG_METRIC2	0x08		/* Tag is in metric2 vs metric */
#define	OSPF_ADV_TAG(adv)	(BIT_TEST((adv)->adv_result.res_flag, OSPF_EXPORT_TAG_METRIC2) ? \
				 (adv)->adv_result.res_metric2 : (adv)->adv_result.res_metric)

/* Default syslog limits */
#define	OSPF_LOG_FIRST	16
#define	OSPF_LOG_EVERY	256

/* Defines for the parser */
#define	OSPF_LIMIT_COST			0, RTRLSInfinity
#define	OSPF_LIMIT_METRIC		0, ASELSInfinity
#define	OSPF_LIMIT_AREA			1, 0xffffffff
#define	OSPF_LIMIT_RETRANSMITINTERVAL	0, 0xffff
#define	OSPF_LIMIT_ROUTERDEADINTERVAL	0, 0xffff
#define	OSPF_LIMIT_HELLOINTERVAL	0, 0xff
#define	OSPF_LIMIT_POLLINTERVAL		0, 0xff
#define	OSPF_LIMIT_TRANSITDELAY		0, 0xffff
#define	OSPF_LIMIT_DRPRIORITY		0, 0xff
#define	OSPF_LIMIT_ACKTIMER		0, 0xffff
#define	OSPF_LIMIT_TAG			0, 0xffffffff
#define	OSPF_LIMIT_EXPORTTYPE		OSPF_EXPORT_TYPE1, OSPF_EXPORT_TYPE2
#define	OSPF_LIMIT_LOG_FIRST	0, (u_int) -1
#define	OSPF_LIMIT_LOG_EVERY	0, (u_int) -1

#define	OSPF_CONFIG_TYPE	1	/* Interface type */
#define	OSPF_CONFIG_COST	2	/* Interface cost */
#define	OSPF_CONFIG_ENABLE	3	/* Enable/disable */
#define	OSPF_CONFIG_RETRANSMIT	4	/* Retransmit interval */
#define	OSPF_CONFIG_TRANSIT	5	/* Transit delay */
#define	OSPF_CONFIG_PRIORITY	6	/* Priority */
#define	OSPF_CONFIG_HELLO	7	/* Hello interval */
#define	OSPF_CONFIG_ROUTERDEAD	8	/* Router dead interval */
#define	OSPF_CONFIG_AUTH	9	/* Authentication */
#define	OSPF_CONFIG_AUTH2	10	/* Authentication */
#define	OSPF_CONFIG_POLL	11	/* NBMA Poll interval */
#define	OSPF_CONFIG_ROUTERS	12	/* NBMA routers */
#define	OSPF_CONFIG_NOMULTI	13	/* For P2P interfaces */
#define	OSPF_CONFIG_MAX		14

typedef struct _ospf_config_router {
    struct _ospf_config_router *ocr_next;
    struct in_addr ocr_router;
    u_int ocr_priority;
} ospf_config_router ;

PROTOTYPE(ospf_config_free,
	  extern void,
	  (config_entry *));
PROTOTYPE(ospf_parse_router_alloc,
	  extern ospf_config_router *,
	  (struct in_addr,
	   u_int));

/* Defaults for ASE imports */
#define	OSPF_DEFAULT_METRIC	1
#define	OSPF_DEFAULT_TAG	PATH_OSPF_TAG_TRUSTED
#define	OSPF_DEFAULT_TYPE	OSPF_EXPORT_TYPE2

#ifdef	PROTO_ASPATHS
#define	ospf_path_tag_dump(as, tag)	sockbuild_str(aspath_tag_dump(as, tag))
#else	/* PROTO_ASPATHS */
#define	ospf_path_tag_dump(as, tag)	sockbuild_in(0, htonl(tag))
#endif	/* PROTO_ASPATHS */

#define	bgp_routesync_ospf(x)	0

#define	OSPF_HOP			1	/* Value to add to ifa_metric to get default interface cost */

extern adv_psfunc ospf_adv_psfunc;

#ifdef	IP_MULTICAST
extern sockaddr_un *ospf_addr_allspf;
extern sockaddr_un *ospf_addr_alldr;
#endif	/* IP_MULTICAST */

extern const bits ospf_trace_types[];		/* OSPF specific tracing flags */

PROTOTYPE(ospf_parse_area_alloc,
	  extern struct AREA *,
	  (u_int32,
	   char *));
PROTOTYPE(ospf_parse_area_check,
	  extern int,
	  (struct AREA *,
	   char *));
PROTOTYPE(ospf_parse_intf_alloc,
	  extern struct INTF *,
	  (struct AREA *,
	   int,
	   if_addr *));
PROTOTYPE(ospf_parse_virt_parse,
	  extern struct INTF *,
	  (struct AREA *,
	   sockaddr_un *,
	   u_int32,
	   config_list *,
	   char *));
PROTOTYPE(ospf_parse_intf_check,
	  extern void,
	  (struct INTF *intf));
PROTOTYPE(ospf_parse_valid_check,
	  extern int,
	  (char *));
PROTOTYPE(ospf_parse_add_net,
	  void,
	  (struct AREA *,
	   sockaddr_un *,
	   sockaddr_un *,
	   u_int));
PROTOTYPE(ospf_parse_add_host,
	  extern void,
	  (struct AREA *,
	   u_int32,
	   metric_t));
PROTOTYPE(ospf_init,
	  extern void,
	  (void));
PROTOTYPE(ospf_var_init,
	  extern void,
	  (void));
PROTOTYPE(ospf_txpkt,
	  extern void,
	  (struct OSPF_HDR *,
	   struct INTF *,
	   u_int,
	   size_t,
	   u_int32,
	   int));
PROTOTYPE(ospf_policy_init,
	  extern void,
	  (task *));
PROTOTYPE(ospf_policy_cleanup,
	  extern void,
	  (task *));
PROTOTYPE(ospf_freeRangeList,
	  extern void,
 	  (struct AREA *));
PROTOTYPE(ospf_freeHostsList,
	  extern void,
 	  (struct AREA *));
PROTOTYPE(ospf_multicast_alldr,
	  extern void,
	  (struct INTF *,
	   int));


/**/
/* Routing table */

#define IS_HOST(R) 		(RT_MASK(R) == HOST_NET_MASK)

/*
 * References for the the routing table access
 */

#define ORT_INFO(rt)	((OSPF_RT_INFO * ) (rt)->rt_data)
#define	ORT_INFO_VALID(rt)	((rt) && (rt)->rt_data)
#define ORT_DTYPE(rt) 	(ORT_INFO(rt)->dtype)
#define ORT_ETYPE(rt) 	(ORT_INFO(rt)->etype)
#define ORT_CHANGE(rt) 	(ORT_INFO(rt)->change)
#define ORT_PTYPE(rt) 	(ORT_INFO(rt)->ptype)
#define ORT_REV(rt) 	(ORT_INFO(rt)->revision)
#define ORT_AREA(rt) 	(ORT_INFO(rt)->area)
#define ORT_COST(rt)	(ORT_INFO(rt)->cost)
#define ORT_NH(rt,I) 	 (ORT_INFO(rt)->nh_ndx[I]->nh_addr)
#define ORT_IO_NDX(rt,I) (ORT_INFO(rt)->nh_ndx[I]->nh_ifap)
#define ORT_NH_NDX(rt,I) (ORT_INFO(rt)->nh_ndx[I])
#define ORT_NH_CNT(rt) 	(ORT_INFO(rt)->nh_cnt)
#define ORT_ADVRTR(rt) 	(ORT_INFO(rt)->advrtr)
#define ORT_OSPF_PREF(rt) (ORT_INFO(rt)->preference)
#define ORT_V(rt) 	(ORT_INFO(rt)->v)

/* OSPF's routing table structure */

#define RT_DEST(rt) 	sock2ip((rt)->rt_dest)
#define	RT_MASK(rt)	sock2ip((rt)->rt_dest_mask)
#define	RT_NEXTHOP(rt)	sock2ip(RT_ROUTER(rt))

/*
 *  For exporting gated routes to OSPF.
 */
typedef struct _ospf_export_entry {
    struct _ospf_export_entry *forw;
    struct _ospf_export_entry *back;
    rt_entry *old_rt;		/* points at route with bit set, if any */
    struct LSDB *db;		/* points to LS db entry, if any */
    rt_entry *new_rt;		/* points at exportable active route, if any */
    metric_t metric;
    u_int32 tag;
    struct in_addr forward;
} ospf_export_entry;


/**/
/* Timers */

PROTOTYPE(ospf_ifdown,
	  extern void,
	  (struct INTF *));
PROTOTYPE(ospf_ifup,
	  extern void,
	  (struct INTF *));
PROTOTYPE(tq_hellotmr,
	  extern void,
	  (task_timer *,
	   time_t));
PROTOTYPE(tq_adjtmr,
	  extern void,
	  (task_timer *,
	   time_t));
PROTOTYPE(tq_lsa_lock,
	  extern void,
	  (task_timer *,
	   time_t));
PROTOTYPE(tq_IntLsa,
	  extern void,
	  (task_timer *,
	   time_t));
PROTOTYPE(tq_SumLsa,
	  extern void,
	  (task_timer *,
	   time_t));
PROTOTYPE(tq_retrans,
	  extern void,
	  (task_timer *,
	   time_t));
PROTOTYPE(tq_ack,
	  extern void,
	  (task_timer *,
	   time_t));
PROTOTYPE(tq_int_age,
	  extern void,
	  (task_timer *,
	   time_t));
PROTOTYPE(tq_sum_age,
	  extern void,
	  (task_timer *,
	   time_t));
PROTOTYPE(tq_ase_age,
	  extern void,
	  (task_timer *,
	   time_t));

/* SNMP support */
#ifdef	PROTO_SNMP
PROTOTYPE(ospf_init_mib,
	  extern void,
	  (int));
PROTOTYPE(o_intf_get,
	  extern void,
	  (void));
PROTOTYPE(o_vintf_get,
	  extern void,
	  (void));
#endif	/* PROTO_SNMP */

#endif	/* OSPF_PORT_H */


/*
 * %(Copyright)
 * %(Copyright.OSPF)
 */
