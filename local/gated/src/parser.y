%{
/*
 *  $Id: parser.y,v 1.131.2.26 1995/04/02 03:21:37 jch Exp $
 */

/* %(Copyright.header) */


#define	MALLOC_OK
#include "include.h"
@BEGIN:	PROTO_INET
#include "inet.h"
@END:	PROTO_INET
@BEGIN:	PROTO_ISO
#include "iso.h"
@END:	PROTO_ISO
#include "parse.h"
#include "krt.h"
@BEGIN:	PROTO_RIP
#include "rip.h"
@END:	PROTO_RIP
@BEGIN:	PROTO_HELLO
#include "hello.h"
@END:	PROTO_HELLO
@BEGIN:	PROTO_ICMP
#include "icmp.h"
@END:	PROTO_ICMP
@BEGIN:	PROTO_OSPF
#include "ospf.h"
@END:	PROTO_OSPF
@BEGIN:	PROTO_IDPR
#include "idpr.h"
@END:	PROTO_IDPR
@BEGIN:	PROTO_EGP
#include "egp.h"
@END:	PROTO_EGP
@BEGIN:	PROTO_BGP
#include "bgp.h"
@END:	PROTO_BGP
@BEGIN:	PROTO_IGMP
#include "igmp.h"
@END:	PROTO_IGMP
@BEGIN:	PROTO_DVMRP
#include "dvmrp.h"
@END:	PROTO_DVMRP
@BEGIN:	PROTO_PIM
#include "pim.h"
@END:	PROTO_PIM
@BEGIN:	PROTO_ISODE_SNMP
#include "snmp_isode.h"
@END:	PROTO_ISODE_SNMP
@BEGIN:	PROTO_ISIS
#include "isis.h"
#include "isis_test.h"
#include "isis_globals.h"
@END:	PROTO_ISIS
@BEGIN:	PROTO_SLSP
#include "slsp.h"
@END:	PROTO_SLSP
@BEGIN:	PROTO_RDISC
#include "rdisc.h"
@END:	PROTO_RDISC

#undef	vsprintf

#ifdef	notdef
#define	free(a)		task_mem_free((task *) 0, a)
#define	malloc(a)	task_mem_malloc((task *) 0, a)
#define	calloc(a, b)	task_mem_calloc((task *) 0, a, b)
#define	realloc(a, b)	task_mem_realloc((task *) 0, a, b)
#define	strdup(a)	task_mem_strdup((task *) 0, a)
#endif	/* notdef */

char parse_error[LINE_MAX] = { 0 };
char *parse_filename = 0;

static	proto_t	parse_proto;			/* For correctly tagging ADV lists */
static	proto_t	parse_export_proto;		/* For checking metrics */
static	gw_entry	**parse_gwlist;
@BEGIN:	PROTO_INET
static	gw_entry	*parse_gwp;		/* To fake a list for EGP and BGP */
@END:	PROTO_INET
@BEGIN:	PARSE_PORT
static  char *parse_serv_proto;
@END:	PARSE_PORT
static	int	parse_contig_masks = TRUE;	/* Masks must be contiguous */
@BEGIN:	PROTO_EGP
static	int parse_group_index;
static	egp_neighbor *ngp, egp_group, *gr_ngp;
@END:	PROTO_EGP
@BEGIN:	PROTO_BGP
static	bgpPeer *bnp;
static	bgpPeerGroup *bgp;
static 	struct bgp_conf *bcp;
@END:	PROTO_BGP
@BEGIN:	PROTO_OSPF
static struct AREA *ospf_AREA;
static size_t ospf_auth_length;
@END:	PROTO_OSPF
@BEGIN:	PROTO_SLSP
static slsp_instance *slsp_parse_instance;
static slsp_gateway *slsp_parse_gateway;
@END:	PROTO_SLSP
static if_info parse_ifi;	/* Used for configuring interfaces that do not exist */

u_int parse_state = PS_INITIAL;
proto_t protos_seen = 0;

PROTOTYPE(yyerror,
	  static void,
	  (const char *));

#define	free_string(s)	task_mem_free((task *) 0, (caddr_t) s); s = 0
#define	free_charstr(s)	task_mem_free((task *) 0, (caddr_t) (s).ptr); (s).ptr = (char *) 0; (s).len = (s).type = 0
#define	free_bytestr(s)	task_mem_free((task *) 0, (caddr_t) (s).ptr); (s).ptr = (byte *) 0; (s).len = (s).type = 0

#define	PARSE_ERROR	yyerror(parse_error); yynerrs++; YYERROR;

#define	PROTO_SEEN(proto) \
	if (BIT_TEST(protos_seen, RTPROTO_BIT(proto))) { \
	    sprintf(parse_error, "parse_proto_seen: duplicate %s clause", gd_lower(trace_state(rt_proto_bits, proto))); \
	    PARSE_ERROR; \
	} else { \
	    BIT_SET(protos_seen, RTPROTO_BIT(proto)); \
	    parse_proto = proto; \
	} \

%}

/* Global */
%union {
    long	num;
    u_long	u_num;
    bytestr	hex;
    charstr	str;
    flag_t	flag;
    time_t	time;
    utime_t	utime;
    as_t	as;
    proto_t	proto;
    pmet_t	metric;
    pref_t	pref;
    if_addr	*ifap;
    if_addr_entry	*ifae;
    adv_entry	*adv;
    gw_entry	*gwp;
    void_t	vt;
    sockaddr_un	*sockaddr;
    trace_file	*trace_file;
#ifdef	PROTO_INET
    struct in_addr in_addr;
#endif	/* PROTO_INET */
    dest_mask	dm;
    struct {
	pmet_t metric;
	adv_entry *adv;
    } metric_adv ;
    struct {
	proto_t proto;
	adv_entry **import_list;
	adv_entry **export_list;
	gw_entry **gw_list;
    } proto_lists;
    config_entry *config;
    config_list *conflist;
#ifndef	GATED_LEXER
#ifdef	PROTO_OSPF
    ospf_config_router *ospf_router;
#endif	/* PROTO_OSPF */
#ifdef	PROTO_ASPATHS
    as_path *aspath;
    asmatch_t *asp_match;
    asp_range asp_range;
    asp_stack asp_stack;
#endif	/* PROTO_ASPATHS */
#endif	/* GATED_LEXER */
}

/* Lexer tokens */
%token			L_EOS L_ERROR
%token	<num>		L_NUMBER
%token	<str>		L_STRING L_HNAME L_KEYWORD
%token	<hex>		L_HEXSTRING L_OCTETSTRING
@BEGIN:	PROTO_ISO
%token	<hex>		L_ISOADDR
@END:	PROTO_ISO

/* Keyword tokens */    
%token	<num>		T_DIRECT T_INTERFACE T_INTERFACES T_LCLADDR
%token	<num>		T_PROTO T_METRIC T_METRICIN T_METRICOUT T_INFINITY T_DOWN
%token	<num>		T_PARSE T_ADV T_DEFAULT T_DEFAULTS
%token	<num>		T_YYDEBUG T_YYSTATE T_YYQUIT T_DEBUG
%token	<num>		T_SYSLOG T_UPTO T_EMERG T_ALERT T_CRIT T_ERR T_WARNING T_NOTICE T_INFO
%token	<num>		T_ON T_OFF T_GATEWAY T_PREFERENCE T_PREFERENCE2
%token	<num>		T_DEFAULTMETRIC T_NONBROADCAST T_BROADCAST T_TYPE
%token	<num>		T_POINTOPOINT T_MULTICAST T_NETMASK T_DEFINE
%token	<num>		T_INTERNAL T_EXTERNAL
%token	<num>		T_IGNORE

/* Filler for conditional clauses */
%token			T_NOP T_NOP1
%token	<dm>		T_NOP_DM
%token	<adv>		T_NOP_ADV
%token	<proto>		T_NOP_PROTO
%token	<sockaddr>	T_NOP_SOCKADDR

%type	<num>		syslog_level syslog_mask
%type	<time>		mark_time    

/* BGP and EGP */
%token	<num>		T_PEERAS T_LOCALAS T_NEIGHBOR T_GROUP
%token	<num>		T_NOGENDEFAULT T_VERSION
%token	<num>		T_ACQUIRE T_TTL
%type	<num>		inet_ttl
@BEGIN:	PROTO_EGP
%token	<num>		T_MAXUP T_SOURCENET T_PKTSIZE T_P1 T_P2 T_DEFAULTIN T_DEFAULTOUT
%type	<u_num>		egp_trace_option_index    
%type	<flag>		egp_trace_options_none egp_trace_options egp_trace_option
%type	<proto>		egp_prop_init    
@END:	PROTO_EGP
@BEGIN:	PROTO_BGP
%token	<num>		T_BGP T_HOLDTIME T_TEST T_KEEP T_SENDBUF T_RECVBUF T_OPEN T_KEEPALIVE T_INDELAY T_OUTDELAY
%token	<num>		T_ROUTING T_ANALRETENTIVE T_KEEPALIVESALWAYS T_NOAGGRID T_NOAUTHCHECK T_SETPREF
%token	<num>		T_NOV4ASLOOP T_V3ASLOOPOKAY T_LOGUPDOWN
%type	<num>		bgp_linktype bgp_kbufsize
%type	<flag>		bgp_trace_options_none bgp_trace_options bgp_trace_option
%type	<u_num>		bgp_trace_option_index
%type	<proto>		bgp_prop_init bgp_proto_option bgp_proto
%type	<dm>		bgp_allow
%type	<adv>		bgp_allow_list bgp_interface
@END:	PROTO_BGP

/* Needed for both EGP and AS paths */    
%token	<num>		T_EGP 

@BEGIN:	PROTO_ASPATHS
/* AS Paths */    
%token	<num>		T_ASPATH T_ORIGIN T_INCOMPLETE T_ANY T_LOOPS
%type	<asp_match>	aspath_match
%type	<asp_stack>	aspath_regex aspath_sum aspath_symbol aspath_term
%type	<asp_range>	aspath_range
%type	<flag>		aspath_origin_list aspath_origins aspath_origin
%type	<proto>		aspath_prop_init    
/* Tags */
%token	<num>		T_TAG
%type	<metric>	tag_option tag_as tag_as_option tag
%type	<proto>		tag_prop_init
@END:	PROTO_ASPATHS

/* Kernel */
%token	<num>		T_KERNEL T_SYMBOLS T_REMNANTS T_IFLIST T_ROUTES
%token	<num>		T_NOCHANGE T_NOFLUSHATEXIT T_REMNANTHOLDTIME
%token	<num>		T_HIGHER T_LOWER T_FLASH T_INTERIOR T_BACKGROUND T_LIMIT
%type	<u_num>		kernel_trace_option_index
%type	<flag>		kernel_trace_options_none kernel_trace_options kernel_trace_option
%type	<flag>		kernel_flash_type kernel_bg_type
   
/* RIP and HELLO */
%token	<num>		T_TRUSTEDGATEWAYS T_SOURCEGATEWAYS
%token	<num>		T_RIP
@BEGIN:	PROTO_RIP
%token	<num>		T_RIPOUT T_NORIPOUT T_RIPIN T_NORIPIN T_NOCHECKZERO
%type	<config>	rip_interface_option rip_interface_options
%type	<u_num>		rip_trace_option_index rip_auth_type
%type	<flag>		rip_trace_options_none rip_trace_options rip_trace_option rip_v2_options
%type	<proto>		rip_prop_init
%type	<vt>		rip_auth
@END:	PROTO_RIP

@BEGIN:	PROTO_HELLO
%token	<num>		T_HELLOOUT T_HELLOIN T_NOHELLOOUT T_NOHELLOIN
%type	<config>	hello_interface_option hello_interface_options    
%type	<u_num>		hello_trace_option_index    
%type	<flag>		hello_trace_options_none hello_trace_options hello_trace_option
%type	<proto>		hello_prop_init
@END:	PROTO_HELLO

@BEGIN:	PROTO_OSPF
%token <num>		T_OSPF T_OSPF_ASE T_NETWORKS T_BACKBONE T_VIRTUALLINK T_STUB T_STUBHOSTS
%token <num>		T_RXMITINTERVAL T_INFTRANSDELAY
%token <num>		T_POLLINTERVAL T_ROUTERS T_NEIGHBORID T_TRANSITAREA
%token <num>		T_ELIGIBLE T_MONITORAUTH T_MONITORAUTHKEY T_NOMULTICAST
%token <num>		T_DD T_ACK T_LSA_BLD T_LSA_RX T_LSA_TX
%token <num>		T_EXPORTINTERVAL T_EXPORTLIMIT    
%token <num>		T_FIRST T_EVERY
%type	<adv>		ospf_interface
%type	<conflist>	ospf_common ospf_nonbroadcast
%type	<config>	ospf_common_options ospf_common_option ospf_nonbroadcast_options ospf_nonbroadcast_option
%type	<metric>	ospf_cost_option ospf_cost ospf_type_option ospf_type
%type	<hex>		ospf_auth_type ospf_auth_key ospf_auth
%type	<u_num>		ospf_area ospf_area_option
%type	<u_num>		ospf_syslog_first ospf_syslog_every
%type	<num>		ospf_priority ospf_eligible_option
%type	<ospf_router>	ospf_router_eligible ospf_router_eligible_list
%type	<flag>		ospf_trace_options_none ospf_trace_options ospf_trace_option
%type	<u_num>		ospf_trace_option_index    
%type	<proto>		ospf_prop_init ospf_ase_prop_init export_ospf_ase
%type	<flag>		ospf_area_range_option
%type	<dm>		ospf_area_range
%type	<adv>		ospf_area_range_list    
@END:	PROTO_OSPF

@BEGIN:	PROTO_ISIS
%token	<num>		T_ISIS T_IP T_DUAL T_CIRCUIT T_SYSTEMID T_SNPA
%token	<num>		T_LEVEL T_IPREACH T_TROLL T_SET T_PREFIX
%token	<num>		T_INTDOMINFO
%type	<num>		isis_option isis_mode isis_level ipreach_type prefix_type
%type	<flag>		isis_trace_options isis_trace_option
%type	<proto>		isis_prop_init export_isis    
@END:	PROTO_ISIS

/* OSPF and ISIS */
%token	<num>		T_AREA T_SPF

/* OSPF and SLSP */
%token <num>		T_HELLO T_HELLOINTERVAL T_ROUTERDEADINTERVAL

/* OSPF and ISIS and SLSP */
%token	<num>		T_PRIORITY

/* OSPF and IGMP and DVMRP and PIM */
%token	<num>		T_ENABLE T_DISABLE

/* IGMP and PIM */
%token	<num>		T_QUERY T_QUERYINTERVAL

/* ISIS and PIM */
%token	<num>		T_MODE

@BEGIN: PROTO_IGMP
/* IGMP */
%token	<num>		T_IGMP T_REPORT T_MTRACE T_LEAVE T_TIMEOUTINTERVAL
%type	<config>	igmp_interface_option igmp_interface_options    
%type	<u_num>		igmp_trace_option_index    
%type	<flag>		igmp_trace_options_none igmp_trace_options igmp_trace_option
@END:	PROTO_IGMP

@BEGIN:	PROTO_DVMRP
/* DVMRP */
%token	<num>		T_DVMRP T_THRESHOLD T_RATELIMIT T_TUNNEL
%type	<config>	dvmrp_interface_option dvmrp_interface_options    
%type	<u_num>		dvmrp_trace_option_index    
%type	<flag>		dvmrp_trace_options_none dvmrp_trace_options dvmrp_trace_option
@END:	PROTO_DVMRP

/* PIM and SNMP  */
%token	<num>		T_REGISTER

@BEGIN: PROTO_PIM
/* PIM */
%token	<num>		T_PIM T_DENSE T_SPARSE T_RP
%token	<num>		T_JOIN T_PRUNE T_GRAFT T_ASSERT
%token	<num>		T_ROUTERTIMEOUT T_PRUNETIMEOUT T_INACTIVITYTIMEOUT
%token	<num>		T_GRAFTACKTIMEOUT
%type	<config>	pim_interface_option pim_interface_options    
%type	<u_num>		pim_trace_option_index    
%type	<flag>		pim_trace_options_none pim_trace_options pim_trace_option
@END:	PROTO_PIM

@BEGIN:	PROTO_IDPR
/* IDPR */
%token	<num>		T_IDPR
%type	<str>		idpr_config_file    
@END:	PROTO_IDPR

/* SNMP */
%token	<num>		T_SNMP
@BEGIN:	PROTO_SNMP
%token	<num>		T_RESOLVE
%type	<flag>		snmp_trace_options_none snmp_trace_options snmp_trace_option
@END:	PROTO_SNMP

@BEGIN:	PROTO_SLSP
/* SLSP */
%token	<num>		T_SLSP T_INSTANCE T_NODE T_NODEMASK
%type	<config>	slsp_interface slsp_interfaces
%type	<time>		slsp_hello slsp_dead
%type	<metric>	slsp_cost    
%type	<num>		slsp_priority    
%type	<u_num>		slsp_trace_option_index
%type	<flag>		slsp_trace_options_none slsp_trace_options slsp_trace_option
%type	<proto>		slsp_prop_init
@END:	PROTO_SLSP

@BEGIN:	PROTO_RDISC
/* Router Discovery */
%token	<num>		T_SERVER T_CLIENT
%type	<num>		rdisc_choice
%type	<flag>		rdisc_trace_options_none rdisc_trace_options rdisc_trace_option
/* Server */
%token	<num>		T_ADDRESS T_MAXADVINTERVAL T_MINADVINTERVAL T_LIFETIME T_ADVERTISE T_INELIGIBLE
%type	<config>	rdisc_server_phys_option rdisc_server_phys_options rdisc_server_addr_option rdisc_server_addr_options
/* Client */
%token	<num>		T_SOLICIT T_QUIET
%type	<config>	rdisc_client_phys_option rdisc_client_phys_options
@END:	PROTO_RDISC

@BEGIN:	PROTO_ICMP
/* ICMP */
%token	<num>		T_ICMP T_ROUTERDISCOVERY
%type	<u_num>		icmp_trace_option_index
%type	<flag>		icmp_trace_options_none icmp_trace_options icmp_trace_option
@END:	PROTO_ICMP

/* Redirects */
%token	<num>		T_REDIRECT T_REDIRECTS T_NOREDIRECTS
%type	<config>	redirect_interface_option redirect_interface_options
%type	<flag>		redirect_trace_options_none redirect_trace_options redirect_trace_option

/* Authentication */
%token	<num>		T_AUTHTYPE T_AUTHKEY T_NONE T_SIMPLE T_AUTH T_MD5 T_SECONDARY

/* Interface */
%token	<num>		T_PASSIVE T_SIMPLEX T_STRICTIFS T_SCANINTERVAL

/* Control */
%token	<num>		T_STATIC T_MARTIANS T_RETAIN
%token	<num>		T_EXPORT T_IMPORT T_EXACT T_REFINE
%token	<num>		T_HOST T_MASK T_MASKLEN T_REJECT T_BLACKHOLE T_RESTRICT T_ALLOW
%type	<dm>		route_dest
@BEGIN:	PROTO_ASPATHS
%type	<aspath>	route_aspath
@END:	PROTO_ASPATHS
%type	<flag>		rts_options rts_option   
%token	<num>		T_ANNOUNCE T_LISTEN
%type	<vt>		import_listen_option prop_announce_option

/* AS control */
%token	<num>		T_AS T_ROUTERID T_IGP

/* Tracing */
%token			T_OPTIONS T_NOINSTALL T_NOSEND T_NORESOLV T_MARK
%token	<num>		T_TRACEOPTIONS T_EXCEPT T_REPLACE T_SIZE T_FILES T_K T_M
%token	<num>		T_ALL T_ROUTE T_STATE T_POLICY T_NORMAL T_GENERAL T_TASK T_TIMER T_NOSTAMP T_UPDATE
%token	<num>		T_DETAIL T_SEND T_RECEIVE T_ERROR T_PACKETS T_RESPONSE T_REQUEST T_OTHER T_TRAP
@BEGIN:	PROTO_ISIS
/* additional tracing for IS-IS */
%token  <num>   	TISIS_IIH TISIS_DUMPLSP TISIS_EVENTS TISIS_LANADJ
%token  <num>   	TISIS_FLOODING TISIS_BUILDLSP TISIS_CSNP TISIS_PSNP
%token  <num>   	TISIS_LSPINPUT TISIS_P2PADJ TISIS_LSPDB 
%token	<num>		TISIS_PATHS TISIS_LSPCONTENT TISIS_SUMMARY
@END:	PROTO_ISIS    

%type	<num>		neg_number number		/* A decimal, hex, or octet string number */
%type	<hex>		byte_string			/* A L_HEXSTRING or L_OCTETSTRING */
%type	<metric>	metric metric_option metric_restrict_option
%type	<time>		time
%token	<num>		L_USEC
@BEGIN:	PARSE_UTIME
%type	<utime>		utime
@END:	PARSE_UTIME
%type	<num>		onoff_option
%type	<flag>		trace_option trace_option_global
%type	<flag>		trace_trace_options_none trace_trace_options
%type	<flag>		trace_option_detail trace_option_sendrecv
%type	<flag>		trace_control_options trace_control_option
%type	<trace_file>	trace_file_option
%type	<num>		trace_size    
%type	<config>	interface_define_options interface_define_option
%type	<flag>		trace_replace
%type	<proto>		proto_exterior
%type	<proto_lists>	control_exterior import_interior export_interior proto_interior

%token	<num>		T_AGGREGATE T_GENERATE T_BRIEF
%type	<flag>		aggregate_options

%type	<proto> 	prop_default prop_direct prop_static prop_kernel prop_aggregate
@BEGIN:	AUTONOMOUS_SYSTEM
%type	<as>		as
@BEGIN:	PARSE_ASLIST
%type	<adv>		as_list as_list_option
@END:	PARSE_ASLIST
%type	<u_num>		as_loop_option
@END:	AUTONOMOUS_SYSTEM
%type	<pref>		preference
%type	<metric>	preference_option preference_restrict_option
%type	<ifae>		interface_local    
%type	<sockaddr>	interface_addr addr host mask
@BEGIN:	PROTO_INET
%token	<num>		T_INET    
%type	<in_addr>	in_addr
%token	<num>		T_GENDEFAULT
%type	<sockaddr>	addr_inet host_inet network_inet mask_inet
%type	<dm>		dest_mask_inet host_mask_inet network_mask_inet network_mask_flags_inet all_mask_inet default_mask_inet
%type	<dm>		aggregate_dest_inet
%type	<dm>		martian_inet
%type	<adv>		martian_list_inet
%type	<sockaddr>	default_gateway_option
%type	<gwp>		gateway_inet
%type	<adv>	 	gateway_list_inet aggregate_list_inet aggregate_proto_inet
%type	<proto>		aggregate_protos_inet
@END:	PROTO_INET
@BEGIN:	PROTO_ISO
%token	<num>		T_ISO
%type	<sockaddr>	addr_iso host_iso network_iso mask_iso
%type	<dm>		dest_mask_iso host_mask_iso network_mask_iso network_mask_flags_iso all_mask_iso default_mask_iso
%type	<dm>		aggregate_dest_iso
%type	<dm>		martian_iso
%type	<adv>		martian_list_iso
%type	<gwp>		gateway_iso
%type	<adv>	 	gateway_list_iso aggregate_list_iso aggregate_proto_iso
%type	<proto>		aggregate_protos_iso
@END:	PROTO_ISO
%type	<num>		dm_flags
%type	<adv>		interface_all interface_all_adv interface_list interface_list_option interface_all_list
@BEGIN:	PARSE_LINK
%type	<adv>		intf_phys_all intf_phys_all_adv intf_phys_list intf_phys_all_list
@END:	PARSE_LINK
%type	<adv>		interface_gateway_list gateway_list
%type	<flag>		martian_option
@BEGIN:	PROTO_INET
%type	<adv>		import_list_inet import_listen_inet
%type	<metric_adv>	import_option_inet
%type	<adv>		prop_source_inet prop_source_list_inet
%type	<adv>		prop_restrict_inet prop_restrict_list_inet prop_restrict_list_option_inet
%type	<metric_adv>	prop_source_option_inet prop_metric_option_inet
@END:	PROTO_INET
@BEGIN:	PROTO_ISO
%type	<adv>		import_list_iso import_listen_iso
%type	<metric_adv>	import_option_iso
%type	<adv>		prop_source_iso prop_source_list_iso
%type	<adv>		prop_restrict_iso prop_restrict_list_iso prop_restrict_list_option_iso
%type	<metric_adv>	prop_source_option_iso prop_metric_option_iso
@END:	PROTO_ISO
%type	<str>		string host_name
@BEGIN:	PARSE_PORT
%token	<port>		T_PORT
%type	<num>		port
@END:	PARSE_PORT

%%

config		: /* Empty */
		| statements
		;

statements	: statement
		| statements statement
		;

statement	: parse_statement
		| trace_statement
		| option_order option_statement
		| interface_order interface_statement
		| define_order define_statement
		| proto_order proto_statement
		| route_order route_statement
		| control_order control_statement
		| error L_EOS
			{
				yyerrok;
			}
		| L_EOS
		;

/*  */

parse_statement	: T_YYDEBUG onoff_option L_EOS
			{
#if	YYDEBUG != 0
			    if ($2 == T_OFF) {
				yydebug = 0;
			    } else {
				yydebug = 1;
			    }
#endif	/* YYDEBUG */
			}
		| T_YYSTATE L_NUMBER L_EOS
			{
#if	YYDEBUG != 0
			    if ($2 < 0 || $2 > PS_MAX) {
				(void) sprintf(parse_error, "invalid yystate value: %d",
					       $2);
				PARSE_ERROR;
			    }
			    parse_state = $2;
#endif	/* YYDEBUG */
			}
		| T_YYQUIT L_EOS
			{
#if	YYDEBUG != 0
			    task_quit(0);
#endif	/* YYDEBUG */
			}
		;

/*  */

trace_statement	: T_TRACEOPTIONS trace_file_option trace_control_option trace_trace_options_none L_EOS
			{
			    if ($2 && !BIT_TEST(task_state, TASKS_TEST)) {

				trace_store(trace_global, $4, $3, $2, (bits *) 0);

				if ($4) {
				    /* Turn on or change tracing */

				    trace_on($2);
				} else {
				    /* Turn off tracing */

				    trace_off($2);
				}
				trace_display(trace_global, TR_ALL);
			    }
			}
		;

trace_file_option
		: /* Empty */
			{
			    $$ = trace_file_locate((char *) 0,
						   (off_t) 0,
						   (u_int) 0,
						   (flag_t) 0);
			}
		| string trace_replace
			{
			    $$ = trace_file_locate($1.ptr,
						   (off_t) 0,
						   (u_int) 0,
						   $2);
			}
		| string trace_replace T_SIZE trace_size T_FILES number
			{
			    if (parse_limit_check("file-size",
						  (u_int) $4,
						  TRACE_LIMIT_FILE_SIZE)) {
				PARSE_ERROR;
			    }

			    if (parse_limit_check("files",
						  (u_int) $6,
						  TRACE_LIMIT_FILE_COUNT)) {
				PARSE_ERROR;
			    }

			    $$ = trace_file_locate($1.ptr,
						   $4,
						   (u_int) $6,
						   $2);
			}
		;

trace_size	: number
		| number T_K
			{
			    $$ = $1 * 1024;
			}
		| number T_M
			{
			    $$ = $1 * 1024 * 1024;
			}
		;

trace_replace	: /* Empty */
			{
			    $$ = 0;
			}
		| T_REPLACE
			{
			    $$ = TRF_REPLACE;
			}
		;

trace_control_option
		: /* Empty */
			{
			    $$ = 0;
			}
		| trace_control_option trace_control_options
			{
			    $$ = $1 | $2;
			}
		;

trace_control_options
		: T_NOSTAMP
			{
			    $$ = TRC_NOSTAMP;
			}
		;

trace_trace_options_none
    		: T_NONE
			{
			    $$ = (flag_t) 0;
			}
		| trace_trace_options
			{
			    $$ = $1;
			}
		| trace_trace_options T_EXCEPT trace_trace_options
			{
			    $$ = $1 & ~ $2;
			}
		;
		
trace_trace_options
		: trace_option
			{
			    $$ = $1;
			}
		| trace_option_global
			{
			    $$ = $1;
			}
		| trace_trace_options trace_option
			{
			    $$ = $1 | $2;
			}
		| trace_trace_options trace_option_global
			{
			    $$ = $1 | $2;
			}
		;

/* Trace options that can only be specified globally */
trace_option_global
		: T_PARSE
			{
			    $$ = TR_PARSE;
			}
		| T_ADV
			{
#ifdef	TR_ADV
			    $$ = TR_ADV;
#else	/* TR_ADV */
			    $$ = 0;
#endif	/* TR_ADV */
			}
		;

/* Trace options that can be specified anywhere */
trace_option	: T_ROUTE
			{
			    $$ = TR_ROUTE;
			}
		| T_NORMAL
			{
			    $$ = TR_NORMAL;
			}
		| T_GENERAL
			{
			    $$ = TR_GENERAL;
			}
		| T_STATE
			{
			    $$ = TR_STATE;
			}
		| T_POLICY
			{
			    $$ = TR_POLICY;
			}
    		| T_TASK
			{
			    $$ = TR_TASK;
			}
		| T_TIMER
			{
			    $$ = TR_TIMER;
			}
		| T_ALL
			{
			    $$ = TR_ALL;
			}
		;

trace_option_detail
		: /* Empty */
			{
			    $$ = (flag_t) 0;
			}
		| T_DETAIL
			{
			    $$ = TR_PARSE_DETAIL;
			}
		;

trace_option_sendrecv
		: /* Empty */
			{
			    $$ = (flag_t) 0;
			}
		| T_SEND
			{
			    $$ = TR_PARSE_SEND;
			}
		| T_RECEIVE
			{
			    $$ = TR_PARSE_RECV;
			}
		;


/*  */

define_order	: /*Empty */
			{
				if (parse_new_state(PS_DEFINE)) {
					PARSE_ERROR;
				}
			}
		;

define_statement
		: T_NOP
@BEGIN:	PROTO_INET
		| T_MARTIANS
			{
			    parse_contig_masks = FALSE;
			}
			'{' martian_list_inet '}' L_EOS
			{
			    parse_contig_masks = TRUE;

			    SI_MARTIANS(AF_INET) = $4;
			}
@END:	PROTO_INET
@BEGIN:	PROTO_ISO
		| T_ISO T_MARTIANS
			{
			    parse_contig_masks = FALSE;
			}
			'{' martian_list_iso '}' L_EOS
			{
			    parse_contig_masks = TRUE;

			    SI_MARTIANS(AF_ISO) = $5;
			}
@END:	PROTO_ISO
@BEGIN:	AUTONOMOUS_SYSTEM
		| T_AS as as_loop_option L_EOS
			{
			    if (inet_autonomous_system) {
				(void) sprintf(parse_error, "autonomous-system already specified");
				PARSE_ERROR;
			    }
			    inet_autonomous_system = $2;
#ifdef	PROTO_ASPATHS
			    aslocal_set(inet_autonomous_system, $3);
#endif	/* PROTO_ASPATHS */
			}
@END:	AUTONOMOUS_SYSTEM
@BEGIN:	ROUTER_ID    
    		| T_ROUTERID host_inet L_EOS
			{
			    if (inet_parse_routerid($2, parse_error)) {
				PARSE_ERROR;
			    }
			}
@END:	ROUTER_ID
		;

@BEGIN:	PROTO_INET
martian_list_inet
		: /* Empty */
			{
			    $$ = SI_MARTIANS(AF_INET);
			}
		| martian_list_inet martian_inet martian_option L_EOS
			{
			    adv_entry *adv = adv_alloc(ADVFT_DM | $3, (proto_t) 0);

			    adv->adv_dm = $2;
			    $$ = adv_destmask_insert(parse_error, $1, adv);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		| martian_list_inet error L_EOS
			{
			    yyerrok;
			}
		;

martian_inet	: host_mask_inet
		| network_mask_flags_inet
		| default_mask_inet
		;
@END:	PROTO_INET
@BEGIN:	PROTO_ISO
martian_list_iso : /* Empty */
			{
			    $$ = SI_MARTIANS(AF_ISO);
			}
		| martian_list_iso martian_iso martian_option L_EOS
			{
			    adv_entry *adv = adv_alloc(ADVFT_DM | $3, (proto_t) 0);

			    adv->adv_dm = $2;
			    $$ = adv_destmask_insert(parse_error, $1, adv);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		| martian_list_iso error L_EOS
			{
			    yyerrok;
			}
		;

martian_iso	: host_mask_iso
		| network_mask_flags_iso
		| default_mask_iso
		;
@END:	PROTO_ISO

martian_option	: /* Empty */
			{
			    $$ = ADVF_NO;
			}
		| T_ALLOW
			{
			    $$ = (flag_t) 0;
			}
		;

/**/

option_order	: /*Empty */
			{
				if (parse_new_state(PS_OPTIONS)) {
					PARSE_ERROR;
				}
			}
		;

option_statement
    		: T_OPTIONS option_list L_EOS
    		;

option_list	: option
		| option_list option
		;


option		: T_NOSEND
			{
			    task_newstate(TASKS_NOSEND, 0);
			}
		| T_NORESOLV
			{
			    task_newstate(TASKS_NORESOLV, 0);
			}
		| T_SYSLOG syslog_mask
			{
#ifdef	LOG_DAEMON
			    (void) setlogmask($2);
#else	/* LOG_DAEMON */
			    (void) sprintf(parse_error, "system does not support setlogmask()");
			    PARSE_ERROR;
#endif	/* LOG_DAEMON */
			}
		| T_MARK mark_time
			{
			    task_mark_interval = $2;
			}
@BEGIN:	PROTO_INET
		| T_GENDEFAULT preference_option default_gateway_option
			{
			    rt_default_needed = TRUE;
			    if (PARSE_METRIC_ISSET(&$2)) {
				rt_default_rtparms.rtp_preference = $2.metric;
			    }
			    rt_default_rtparms.rtp_router = $3;
			}
@END:	PROTO_INET
		;


@BEGIN:	PROTO_INET
default_gateway_option
		: /* Empty */
			{
			    $$ = (sockaddr_un *) 0;
			}
		| T_GATEWAY
			{
			    parse_gwlist = &parse_gwp;
			}
		gateway_inet
			{
			    $$ = sockdup($3->gw_addr);
			    gw_freelist(*parse_gwlist);
			    *parse_gwlist = parse_gwp = (gw_entry *) 0;
			}
			;
@END:	PROTO_INET

mark_time	:	/* Empty */
			{
			    $$ = TIME_MARK;
			}
		|	time
			{
			    $$ = $1;
			}
		;

syslog_mask	:	syslog_level
			{
#ifdef	LOG_DAEMON
			    $$ = LOG_MASK($1);
#endif	/* LOG_DAEMON */
			}
		|	T_UPTO syslog_level
			{
#ifdef	LOG_DAEMON
			    $$ = LOG_UPTO($2);
#endif	/* LOG_DAEMON */
			}
		|	syslog_mask syslog_level
			{
#ifdef	LOG_DAEMON
			    $$ = $1 | LOG_MASK($2);
#endif	/* LOG_DAEMON */
			}
		;

syslog_level	: T_EMERG
			{
			    $$ = LOG_EMERG;
			}
		| T_ALERT
			{
			    $$ = LOG_ALERT;
			}
		| T_CRIT
			{
			    $$ = LOG_CRIT;
			}
		| T_ERR
			{
			    $$ = LOG_ERR;
			}
		| T_WARNING
			{
			    $$ = LOG_WARNING;
			}
		| T_NOTICE
			{
			    $$ = LOG_NOTICE;
			}
		| T_INFO
			{
			    $$ = LOG_INFO;
			}
		| T_DEBUG
			{
			    $$ = LOG_EMERG;
			}
    		;

/*  */

interface_order	: /*Empty */
			{
			    if (parse_new_state(PS_INTERFACE)) {
				PARSE_ERROR;
			    }
			}
		;

interface_statement	
		: T_INTERFACES
			{
			    PROTO_SEEN(RTPROTO_DIRECT);
			}
			'{' interface_stmts '}' L_EOS
			{
			    parse_proto = (proto_t) 0;
			}
		;

interface_stmts
		: /* Empty */
    		| interface_stmts interface_stmt L_EOS
    		| interface_stmts error L_EOS
			{
			    yyerrok;
			}
    		;

interface_stmt
		: T_OPTIONS interface_options
		| T_INTERFACE interface_all_list interface_define_options
			{
			    config_list *list = config_list_alloc($3, 0);

			    parse_adv_propagate_config($2, list, (proto_t) 0);

			    if (parse_adv_append(&int_policy, $2)) {
				PARSE_ERROR;
			    }

			    config_list_free(list);
			}
		| T_DEFINE host_inet
			{
			    bzero((caddr_t) &parse_ifi, sizeof (parse_ifi));

			    parse_ifi.ifi_addr = $2;
			}
			interface_type_options interface_common_options
			{
			    if (if_parse_add(&parse_ifi, parse_error)) {
				PARSE_ERROR;
			    }
			}
		;

interface_options
		: interface_option
		| interface_options interface_option
		;

interface_option
		: T_STRICTIFS
			{
			    task_newstate(TASKS_STRICTIFS, 0);
			}
		| T_SCANINTERVAL time
			{
			    if (parse_limit_check("scan-interval",
						  (u_int) $2,
						  KRT_LIMIT_SCANTIMER)) {
				PARSE_ERROR;
			    }
			    
			    task_timer_set(krt_timer_ifcheck,
					   $2,
					   (time_t) 0);
			}
		;

interface_type_options
		: T_BROADCAST host
			{
			    parse_ifi.ifi_addr_broadcast = $2;
			    BIT_SET(parse_ifi.ifi_state, IFS_BROADCAST);
			}
		| T_POINTOPOINT host
			{
			    parse_ifi.ifi_addr_local = $2;
			    BIT_SET(parse_ifi.ifi_state, IFS_POINTOPOINT);
			}
		| /* Empty */
			{
			}
		;

interface_common_options
		: /* Empty */
		| interface_common_options interface_common_option
		;

interface_common_option
		: T_NETMASK mask
			{
			    parse_ifi.ifi_netmask = $2;
			}
		| T_MULTICAST
			{
			    BIT_SET(parse_ifi.ifi_state, IFS_MULTICAST);
			}
		;

interface_define_options
		: interface_define_option
		| interface_define_options interface_define_option
			{
			    $$ = config_append($1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		;

interface_define_option
		: T_PREFERENCE preference
			{
			    $$ = config_alloc(IF_CONFIG_PREFERENCE_UP, GS2A($2));
			}
		| T_DOWN T_PREFERENCE preference
			{
			    $$ = config_alloc(IF_CONFIG_PREFERENCE_DOWN, GS2A($3));
			}
		| T_PASSIVE
			{
			    $$ = config_alloc(IF_CONFIG_PASSIVE, GS2A(TRUE));
			}
		| T_SIMPLEX
			{
			    $$ = config_alloc(IF_CONFIG_SIMPLEX, GS2A(TRUE));
			}
		| T_REJECT
			{
			    $$ = config_alloc(IF_CONFIG_REJECT, GS2A(TRUE));
			}
		| T_BLACKHOLE
			{
			    $$ = config_alloc(IF_CONFIG_BLACKHOLE, GS2A(TRUE));
			}
@BEGIN:	PROTO_ASPATHS
		| T_AS as
			{
			    $$ = config_alloc(IF_CONFIG_AS, GS2A($2));
			}
@END:	PROTO_ASPATHS
		;

interface_list_option
		: /* Empty */
			{
			    $$ = adv_alloc(ADVFT_ANY|ADVF_FIRST, (proto_t) 0);
			}
		| T_INTERFACE interface_list
			{
			    $$ = $2;
			}
		;

interface_gateway_list
		: interface_list_option
			{
			    $$ = $1;
			    parse_proto = (proto_t) 0;
			    parse_gwlist = (gw_entry **) 0;
			}
		| T_GATEWAY gateway_list
			{
			    $$ = $2;
			    parse_proto = (proto_t) 0;
			    parse_gwlist = (gw_entry **) 0;
			}
		;

interface_all_list
		: T_ALL
			{
			    $$ = adv_alloc(ADVFT_ANY|ADVF_FIRST, (proto_t) 0);
			}
		| interface_list
		;

interface_list
		: interface_all
			{
			    BIT_SET($1->adv_flag, ADVF_FIRST);
			    $$ = $1;
			}
		| interface_list interface_all
			{
			    $$ = $1;
			    if (parse_adv_append(&$$, $2)) {
				PARSE_ERROR;
			    }
			}
		;

interface_all	: interface_all_adv
			{
			    switch ($1->adv_flag & ADVF_TYPE) {

			    case ADVFT_IFN:
				trace_tf(trace_global,
					 TR_PARSE,
					 0,
					 ("parse: %s INTERFACE: %A*",
					  parse_where(),
					  $$->adv_ifn->ifae_addr));
				break;
				
			    case ADVFT_IFAE:
				trace_tf(trace_global,
					 TR_PARSE,
					 0,
					 ("parse: %s INTERFACE: %A",
					  parse_where(),
					  $$->adv_ifae->ifae_addr));
			    }
			}
		;

interface_all_adv
		: host_name
			{
			    int valid_ifname = 0;

			    switch ($1.type) {
			    case L_KEYWORD:
			    case L_STRING:
				if ($1.len < IFL_NAMELEN) {
				    valid_ifname++;
				}
				break;

			    default:
				break;
			    }

			    if (valid_ifname) {
				/* First try to look up as an interface name */

				$$ = if_parse_name($1.ptr, FALSE);
			    } else {
				/* Doesn't meet the criteria to be a name */

				$$ = (adv_entry *) 0;
			    }
			    
			    if (!$$ && !BIT_TEST(task_state, TASKS_NORESOLV)) {
				/* Try to resolve as a host name */

				sockaddr_un *addr = parse_addr_hostname($1.ptr, parse_error);

				if (addr) {
				    $$ = if_parse_address(addr);
				}

			    }

			    if (!$$) {
				if (valid_ifname && !BIT_TEST(task_state, TASKS_STRICTIFS)) {
				    /* Assume it is a reference to an interface that does not exist */

				    $$ = if_parse_name($1.ptr, TRUE);
				} else {
				    /* Time to give up */
				    
				    (void) sprintf(parse_error, "Interface not found at '%s'",
						   $1.ptr);
				    PARSE_ERROR;
				}
			    }
				
			    free_charstr($1);
			}
		| addr
			{
			    $$ = if_parse_address($1);
			    if (!$$) {
				(void) sprintf(parse_error, "Interface not found at '%A'",
					       $1);
				PARSE_ERROR;
			    }

			    sockfree($1);
			}
		;

interface_local	: interface_addr
			{
			    if_addr *ifap;
			    
			    ifap = if_withlcladdr($1, FALSE);
			    if (ifap) {
				$$ = ifae_alloc(ifap->ifa_addrent_local);
			    } else {
				if (BIT_TEST(task_state, TASKS_STRICTIFS)) {
				    (void) sprintf(parse_error, "Invalid interface at '%A'",
						   $1);
				    PARSE_ERROR;
				} else {
				    $$ = ifae_locate($1, &if_local_list);
				}
			    }
			    sockfree($1);
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s LOCAL ADDRESS: %A",
				      parse_where(),
				      $$->ifae_addr));
			}
		;

interface_addr	: addr
		| host_name
			{
			    sockaddr_un *addr;

			    addr = parse_addr_hostname($1.ptr, parse_error);
			    if (!addr) {
				/* Name resolution failure */

				PARSE_ERROR;
			    }
			    $$ = sockdup(addr);
			    free_charstr($1);
			}
		;

/**/

@BEGIN:	PARSE_LINK
/* Physical interfaces */

intf_phys_all_list
		: T_ALL
			{
			    $$ = adv_alloc(ADVFT_ANY|ADVF_FIRST, (proto_t) 0);
			}
		| intf_phys_list
		;

intf_phys_list
		: intf_phys_all
			{
			    BIT_SET($1->adv_flag, ADVF_FIRST);
			    $$ = $1;
			}
		| intf_phys_list intf_phys_all
			{
			    $$ = $1;
			    if (parse_adv_append(&$$, $2)) {
				PARSE_ERROR;
			    }
			}
		;

intf_phys_all	: intf_phys_all_adv
			{
			    switch ($1->adv_flag & ADVF_TYPE) {

			    case ADVFT_IFN:
				trace_tf(trace_global,
					 TR_PARSE,
					 0,
					 ("parse: %s LINK: %A*",
					  parse_where(),
					  $$->adv_ifn->ifae_addr));
				break;
				
			    case ADVFT_IFAE:
				trace_tf(trace_global,
					 TR_PARSE,
					 0,
					 ("parse: %s LINK: %A",
					  parse_where(),
					  $$->adv_ifae->ifae_addr));
			    }
			}
		;

intf_phys_all_adv
		: host_name
			{
			    int valid_ifname = 0;

			    switch ($1.type) {
			    case L_KEYWORD:
			    case L_STRING:
				if ($1.len < IFL_NAMELEN) {
				    valid_ifname++;
				}
				break;

			    default:
				break;
			    }

			    if (valid_ifname) {
				/* First try to look up as an interface name */

				$$ = if_parse_name($1.ptr, FALSE);
			    } else {
				/* Doesn't meet the criteria to be a name */

				(void) sprintf(parse_error, "Physical interface not found at '%s'",
					       $1.ptr);
				PARSE_ERROR;
			    }
			}
		/* XXX - Need to allow physical address */
		;
@END:	PARSE_LINK

/*  */

proto_order	: /* Empty */
			{
			    if (parse_new_state(PS_PROTO)) {
				PARSE_ERROR;
			    }
			}
		;

proto_statement	: redirect_statement L_EOS
		| kernel_statement L_EOS
@BEGIN:	PROTO_BGP
		| bgp_statement L_EOS
@END:	PROTO_BGP
@BEGIN:	PROTO_IGMP
		| igmp_statement L_EOS
@END:	PROTO_IGMP
@BEGIN:	PROTO_DVMRP
		| dvmrp_statement L_EOS
@END:	PROTO_DVMRP
@BEGIN:	PROTO_PIM
		| pim_statement L_EOS
@END:	PROTO_PIM
@BEGIN:	PROTO_EGP
		| egp_statement L_EOS
@END:	PROTO_EGP
@BEGIN:	PROTO_HELLO
		| hello_statement L_EOS
@END:	PROTO_HELLO
@BEGIN:	PROTO_ICMP
		| icmp_statement L_EOS
@END:	PROTO_ICMP
@BEGIN:	PROTO_OSPF
    		| ospf_statement L_EOS
@END:	PROTO_OSPF
@BEGIN:	PROTO_ISIS
    		| isis_statement L_EOS
@END:	PROTO_ISIS
@BEGIN:	PROTO_SLSP
		| slsp_statement L_EOS
@END:	PROTO_SLSP
@BEGIN:	PROTO_RDISC
		| rdisc_statement L_EOS
@END:	PROTO_RDISC
@BEGIN:	PROTO_IDPR
    		| idpr_statement L_EOS
@END:	PROTO_IDPR
		| rip_statement L_EOS
		| snmp_statement L_EOS
		;

/*  */

kernel_statement
		: T_KERNEL
			{
			    kernel_trace_options = trace_set_global(kernel_trace_types,
								    TR_KRT_SYMBOLS|TR_KRT_IFLIST);
			}
		 '{' kernel_group '}'
		;

kernel_group	: /* Empty */
		| kernel_group kernel_stmt L_EOS
		| kernel_group error L_EOS
		;

kernel_stmt	: T_TRACEOPTIONS trace_file_option trace_control_option kernel_trace_options_none
			{
			    trace_store(kernel_trace_options, $4, $3, $2, kernel_trace_types);
			}
		| T_OPTIONS kernel_options {}
		| T_REMNANTHOLDTIME time
			{
			    if (parse_limit_check("remnantholdtime",
						  (u_int) $2,
						  KRT_LIMIT_EXPIRE)) {
				PARSE_ERROR;
			    }
			    krt_t_expire = $2;
			}
		| T_FLASH kernel_flash_options {}
		| T_BACKGROUND kernel_bg_options {}
		| T_ROUTES number
			{
			    if (parse_limit_check("routes",
						  (u_int) $2,
						  KRT_LIMIT_ROUTES)) {
				PARSE_ERROR;
			    }
			    krt_limit_routes = $2;
			}
		;

kernel_options	: kernel_option
		| kernel_options kernel_option
		;

kernel_option	: T_NOCHANGE
			{
			    BIT_SET(krt_options, KRT_OPT_NOCHANGE);
			}
		| T_NOFLUSHATEXIT
			{
			    BIT_SET(krt_options, KRT_OPT_NOFLUSH);
			}
		;

kernel_flash_options
		: kernel_flash_option
		| kernel_flash_options kernel_flash_option
		;

kernel_flash_option
		: T_TYPE kernel_flash_type
			{
			    krt_flash_routes = $2;
			}
		| T_LIMIT neg_number
			{
			    if (parse_limit_check("flash limit",
						  (u_int) $2,
						  KRT_LIMIT_FLASH)) {
				PARSE_ERROR;
			    }
			    krt_flash_install_count = $2;
			}
		;

kernel_flash_type
		: T_INTERFACE
			{
			    $$ = KRT_FLASH_INTERFACE;
			}
		| T_INTERIOR
			{
			    $$ = KRT_FLASH_INTERNAL;
			}
		| T_ALL
			{
			    $$ = KRT_FLASH_ALL;
			}
		;

kernel_bg_options
		: kernel_bg_option
		| kernel_bg_options kernel_bg_option
		;

kernel_bg_option
		: T_PRIORITY kernel_bg_type
			{
			    krt_install_priority = $2;
			}
		| T_LIMIT number
			{
			    if (parse_limit_check("install limit",
						  (u_int) $2,
						  KRT_LIMIT_INSTALL)) {
				PARSE_ERROR;
			    }
			    krt_install_count = $2;
			}
		;

kernel_bg_type
		: T_FLASH
			{
			    $$ = KRT_INSTALL_PRIO_FLASH;
			}
		| T_HIGHER
			{
			    $$ = KRT_INSTALL_PRIO_HIGH;
			}
		| T_LOWER
			{
			    $$ = KRT_INSTALL_PRIO_LOW;
			}
		;

kernel_trace_options_none
		: T_NONE
			{
			    $$ = (flag_t) 0;
			}
		| kernel_trace_options
			{
			    $$ = $1;
			}
		| kernel_trace_options T_EXCEPT kernel_trace_options
			{
			    $$ = $1 & ~$3;
			}
    		;

kernel_trace_options
		: kernel_trace_option
			{
			    $$ = $1;
			}
		| kernel_trace_options kernel_trace_option
			{
			    $$ = $1 | $2;
			}
		;

kernel_trace_option
		: trace_option
    		| trace_option_detail trace_option_sendrecv kernel_trace_option_index
			{
			    $$ = trace_parse_packet($1, $2, $3);
			}
		| T_SYMBOLS
			{
			    $$ = TR_KRT_SYMBOLS;
			}
		| T_REMNANTS
			{
			    $$ = TR_KRT_REMNANTS;
			}
		| T_IFLIST
			{
			    $$ = TR_KRT_IFLIST;
			}
		| T_REQUEST
			{
			    $$ = TR_KRT_REQUEST;
			}
@BEGIN:	KRT_RT_SOCK
		| T_INFO
			{
			    $$ = TR_KRT_INFO;
			}
@END:	KRT_RT_SOCK
		;

kernel_trace_option_index
		: T_PACKETS
			{
			    $$ = TR_KRT_INDEX_PACKETS;
			}
		| T_ROUTES
			{
			    $$ = TR_KRT_INDEX_ROUTES;
			}
@BEGIN:	KRT_RT_SOCK
		| T_REDIRECT
			{
			    $$ = TR_KRT_INDEX_REDIRECT;
			}
		| T_INTERFACE
			{
			    $$ = TR_KRT_INDEX_INTERFACE;
			}
		| T_OTHER
			{
			    $$ = TR_KRT_INDEX_OTHER;
			}
@END:	KRT_RT_SOCK
    		;

/*  */

@BEGIN:	PROTO_RIP

rip_statement	: T_RIP
			{
			    PROTO_SEEN(RTPROTO_RIP);

			    parse_gwlist = &rip_gw_list;

			    rip_trace_options = trace_set_global(rip_trace_types,
								 (flag_t) 0);
			}
    		onoff_option rip_group
			{
			    switch ($3) {
			    case T_OFF:
				BIT_RESET(rip_flags, RIPF_ON);
				break;

			    case T_ON:
				BIT_SET(rip_flags, RIPF_ON);
				break;
			    }

			    parse_proto = (proto_t) 0;
			    parse_gwlist = (gw_entry **) 0;
			}
		;

rip_group	: /* Empty */
		| '{' rip_group_stmts '}'
		;

rip_group_stmts	: /* Empty */
		| rip_group_stmts rip_group_stmt L_EOS
		| rip_group_stmts error L_EOS
			{
			    yyerrok;
			}
		;

rip_group_stmt	: T_PREFERENCE preference
			{
			    rip_preference = $2;
			}
		| T_DEFAULTMETRIC metric
			{
			    if (parse_metric_check(RTPROTO_RIP, &$2)) {
				PARSE_ERROR;
			    }
			    rip_default_metric = $2.metric;
			}
		| T_BROADCAST
			{
			    BIT_RESET(rip_flags, RIPF_CHOOSE);
			    BIT_SET(rip_flags, RIPF_BROADCAST);
			}
		| T_NONBROADCAST
			{
			    BIT_RESET(rip_flags, RIPF_CHOOSE|RIPF_BROADCAST);
			}
		| T_TRACEOPTIONS trace_file_option trace_control_option rip_trace_options_none
			{
			    trace_store(rip_trace_options, $4, $3, $2, rip_trace_types);
			}
		| T_NOCHECKZERO
			{
			    BIT_SET(rip_flags, RIPF_NOCHECK);
			}
		| T_INTERFACE interface_all_list rip_interface_options
			{
			    config_list *list = config_list_alloc($3, rip_config_free);

			    parse_adv_propagate_config($2, list, RTPROTO_RIP);

			    if (parse_adv_append(&rip_int_policy, $2)) {
				PARSE_ERROR;
			    }

			    config_list_free(list);
			}
		| T_TRUSTEDGATEWAYS gateway_list_inet
			{
			    rip_n_trusted += parse_gw_flag($2, RTPROTO_RIP, GWF_TRUSTED);
			    if (!rip_n_trusted) {
				PARSE_ERROR;
			    }
			}
		| T_SOURCEGATEWAYS gateway_list_inet
			{
			    rip_n_source += parse_gw_flag($2, RTPROTO_RIP, GWF_SOURCE);
			    if (!rip_n_source) {
				PARSE_ERROR;
			    }
			    BIT_SET(rip_flags, RIPF_SOURCE);
			}
		| T_QUERY T_AUTH rip_auth
			{
			    rip_auth_query = (struct rip_authinfo *) $3;
			}
		;

rip_interface_options
		: rip_interface_option
		| rip_interface_options rip_interface_option
			{
			    $$ = config_append($1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		;

rip_interface_option
		: T_RIPIN
			{
			    $$ = config_alloc(RIP_CONFIG_IN, GS2A(TRUE));
			}
		| T_NORIPIN
			{
			    $$ = config_alloc(RIP_CONFIG_IN, GS2A(FALSE));
			}
		| T_RIPOUT
			{
			    $$ = config_alloc(RIP_CONFIG_OUT, GS2A(TRUE));
			}
		| T_NORIPOUT
			{
			    $$ = config_alloc(RIP_CONFIG_OUT, GS2A(FALSE));
			}
		| T_METRICIN metric
			{
			    if (parse_metric_check(RTPROTO_RIP, &$2)) {
				PARSE_ERROR;
			    }
			    $$ = config_alloc(RIP_CONFIG_METRICIN, GS2A($2.metric));
			}
		| T_METRICOUT metric
			{
			    if (parse_metric_check(RTPROTO_RIP, &$2)) {
				PARSE_ERROR;
			    }
			    $$ = config_alloc(RIP_CONFIG_METRICOUT, GS2A($2.metric));
			}
		| T_AUTH rip_auth
			{
			    $$ = config_alloc(RIP_CONFIG_AUTH, $2);
			}
		| T_SECONDARY T_AUTH rip_auth
			{
			    $$ = config_alloc(RIP_CONFIG_AUTH2, $3);
			}
		| T_VERSION L_NUMBER rip_v2_options
			{
			    flag_t flag;
			    
			    switch ($2) {
			    case 1:
				if ($3) {
				    (void) sprintf(parse_error, "options not valid with version 1");
				    PARSE_ERROR;
				}
				flag = RIP_IFPS_V1;
				break;

			    case 2:
				if ($3) {
				    flag = $3;
				} else {
				    /* This means whatever options the interface is capable of */
#ifdef	IP_MULTICAST
				    flag = RIP_IFPS_V2;
#else	/* IP_MULTICAST */
				    flag = RIP_IFPS_V2BC;
#endif	/* IP_MULTICAST */
				}
				break;

			    default:
				(void) sprintf(parse_error, "invalid version");
				PARSE_ERROR;
			    }
			    $$ = config_alloc(RIP_CONFIG_FLAG, GS2A(flag));
			}
		;

rip_v2_options	: /* Empty */
			{
			    $$ = 0;
			}
		| T_MULTICAST
			{
			    $$ = RIP_IFPS_V2MC;
			}
		| T_BROADCAST
			{
			    $$ = RIP_IFPS_V2BC;
			}
		;

rip_auth	: T_NONE
			{
			    $$ = (void_t) &rip_auth_none;
			}
		| rip_auth_type string
			{
			    struct rip_authinfo *ap = (struct rip_authinfo *) task_block_alloc(rip_auth_block_index);

			    if ($2.len > RIP_AUTH_SIZE) {
				sprintf(parse_error, "authentication-key \"%s\"%d longer than %d characters",
					$2.ptr,
					$2.len,
					RIP_AUTH_SIZE);
				PARSE_ERROR;
			    }

			    ap->auth_family = RIP_AF_AUTH;
			    ap->auth_type = htons((u_int16) $1);
			    /* Left justify the authentication key */
			    (void) strncpy((caddr_t) ap->auth_data, $2.ptr, RIP_AUTH_SIZE);

			    free_charstr($2);

			    $$ = (void_t) ap;
			}
		;

rip_auth_type	: /* Empty */
			{
			    $$ = RIP_AUTH_SIMPLE;
			}
		| T_SIMPLE
			{
			    $$ = RIP_AUTH_SIMPLE;
			}
		| T_MD5
			{
			    $$ = RIP_AUTH_MD5;
			}
		;

rip_trace_options_none
		: T_NONE
			{
			    $$ = (flag_t) 0;
			}
		| rip_trace_options
			{
			    $$ = $1;
			}
		| rip_trace_options T_EXCEPT rip_trace_options
			{
			    $$ = $1 & ~$3;
			}
    		;

rip_trace_options
		: rip_trace_option
			{
			    $$ = $1;
			}
		| rip_trace_options rip_trace_option
			{
			    $$ = $1 | $2;
			}
		;

rip_trace_option
		: trace_option
    		| trace_option_detail trace_option_sendrecv rip_trace_option_index
			{
			    $$ = trace_parse_packet($1, $2, $3);
			}
		;

rip_trace_option_index
		: T_PACKETS
			{
			    $$ = TR_RIP_INDEX_PACKETS;
			}
		| T_REQUEST
			{
			    $$ = TR_RIP_INDEX_REQUEST;
			}
		| T_RESPONSE
			{
			    $$ = TR_RIP_INDEX_RESPONSE;
			}
		| T_OTHER
			{
			    $$ = TR_RIP_INDEX_OTHER;
			}
    		;

rip_prop_init	: T_RIP
			{
			    $$ = parse_proto = RTPROTO_RIP;
			    parse_gwlist = &rip_gw_list;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s PROTO: %s",
				      parse_where(),
				      gd_lower(trace_state(rt_proto_bits, $$))));
			}
		;

@END:	PROTO_RIP
@BEGIN:	NOT PROTO_RIP
rip_statement	: T_RIP T_OFF
			{
			}
		;
@END:	NOT PROTO_RIP

/*  */

@BEGIN:	PROTO_HELLO

hello_statement	: T_HELLO
			{
			    PROTO_SEEN(RTPROTO_HELLO);

			    parse_gwlist = &hello_gw_list;

			    hello_trace_options = trace_set_global(hello_trace_types,
								   (flag_t) 0);
			}
		onoff_option hello_group
			{
			    switch ($3) {
			    case T_OFF:
				BIT_RESET(hello_flags, HELLOF_ON);
				break;

			    case T_ON:
				BIT_SET(hello_flags, HELLOF_ON);
				break;
			    }
			    
			    parse_proto = (proto_t) 0;
			    parse_gwlist = (gw_entry **) 0;
			}
		;

hello_group	: /* Empty */
		| '{' hello_group_stmts '}'
		;

hello_group_stmts
		: /* Empty */
		| hello_group_stmts hello_group_stmt L_EOS
		| hello_group_stmts error L_EOS
			{
			    yyerrok;
			}
		;

hello_group_stmt
		: T_PREFERENCE preference
			{
			    hello_preference = $2;
			}
		| T_DEFAULTMETRIC metric
			{
			    if (parse_metric_check(RTPROTO_HELLO, &$2)) {
				PARSE_ERROR;
			    }
			    hello_default_metric = $2.metric;
			}
		| T_BROADCAST
			{
			    hello_flags = (hello_flags & ~HELLOF_CHOOSE) | HELLOF_BROADCAST;
			}
		| T_NONBROADCAST
			{
			    hello_flags = hello_flags & ~(HELLOF_CHOOSE|HELLOF_BROADCAST);
			}
		| T_TRACEOPTIONS trace_file_option trace_control_option hello_trace_options_none
			{
			    trace_store(hello_trace_options, $4, $3, $2, hello_trace_types);
			}
		| T_INTERFACE interface_all_list hello_interface_options
			{
			    config_list *list = config_list_alloc($3, 0);

			    parse_adv_propagate_config($2, list, RTPROTO_HELLO);

			    if (parse_adv_append(&hello_int_policy, $2)) {
				PARSE_ERROR;
			    }

			    config_list_free(list);
			}
		| T_TRUSTEDGATEWAYS gateway_list_inet
			{
			    hello_n_trusted += parse_gw_flag($2, RTPROTO_HELLO, GWF_TRUSTED);
			    if (!hello_n_trusted) {
				PARSE_ERROR;
			    }
			}
		| T_SOURCEGATEWAYS gateway_list_inet
			{
			    hello_n_source += parse_gw_flag($2, RTPROTO_HELLO, GWF_SOURCE);
			    if (!hello_n_source) {
				PARSE_ERROR;
			    }
			    BIT_SET(hello_flags, HELLOF_SOURCE);
			}
		;

hello_interface_options
		: hello_interface_option
		| hello_interface_options hello_interface_option
			{
			    $$ = config_append($1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		;

hello_interface_option
		: T_HELLOIN
			{
			    $$ = config_alloc(HELLO_CONFIG_IN, GS2A(TRUE));
			}
		| T_NOHELLOIN
			{
			    $$ = config_alloc(HELLO_CONFIG_IN, GS2A(FALSE));
			}
		| T_HELLOOUT
			{
			    $$ = config_alloc(HELLO_CONFIG_OUT, GS2A(TRUE));
			}
		| T_NOHELLOOUT
			{
			    $$ = config_alloc(HELLO_CONFIG_OUT, GS2A(FALSE));
			}
		| T_METRICIN metric
			{
			    if (parse_metric_check(RTPROTO_HELLO, &$2)) {
				PARSE_ERROR;
			    }
			    $$ = config_alloc(HELLO_CONFIG_METRICIN, GS2A($2.metric));
			}
		| T_METRICOUT metric
			{
			    if (parse_metric_check(RTPROTO_HELLO, &$2)) {
				PARSE_ERROR;
			    }
			    $$ = config_alloc(HELLO_CONFIG_METRICOUT, GS2A($2.metric));
			}
		;

hello_trace_options_none
		: T_NONE
			{
			    $$ = (flag_t) 0;
			}
		| hello_trace_options
			{
			    $$ = $1;
			}
		| hello_trace_options T_EXCEPT hello_trace_options
			{
			    $$ = $1 & ~$3;
			}
    		;

hello_trace_options
		: hello_trace_option
			{
			    $$ = $1;
			}
		| hello_trace_options hello_trace_option
			{
			    $$ = $1 | $2;
			}
		;

hello_trace_option
		: trace_option
    		| trace_option_detail trace_option_sendrecv hello_trace_option_index
			{
			    $$ = trace_parse_packet($1, $2, $3);
			}
		;

hello_trace_option_index
		: T_PACKETS
			{
			    $$ = TR_HELLO_INDEX_PACKETS;
			}
    		;


hello_prop_init	: T_HELLO
			{
			    $$ = parse_proto = RTPROTO_HELLO;
			    parse_gwlist = &hello_gw_list;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s PROTO: %s",
				      parse_where(),
				      gd_lower(trace_state(rt_proto_bits, $$))));
			}
		;
@END:	PROTO_HELLO

    
/*  */

@BEGIN:	PROTO_OSPF

ospf_statement	: T_OSPF
			{
			    PROTO_SEEN(RTPROTO_OSPF);

			    parse_gwlist = &ospf.gw_list;

			    ospf.trace_options = trace_set_global(ospf_trace_types,
								  (flag_t) 0);

			    /* Somewhere around here is where we will figure out which OSPF global structure we are */
			    /* refering to and initialize it once we support multiple instantations of OSPF that is. */
			}
		onoff_option ospf_group
			{
			    if ($3 == T_OFF) {
				ospf.ospf_admin_stat = OSPF_DISABLED;
			    } else {
				if (ospf_parse_valid_check(parse_error)) {
				    PARSE_ERROR;
				}
				ospf.ospf_admin_stat = OSPF_ENABLED;
			    }

			    parse_proto = (proto_t) 0;
			    parse_gwlist = (gw_entry **) 0;
			}
		;

ospf_group	: /* Empty */
		| '{' ospf_group_stmts '}'
		;

ospf_group_stmts	: /* Empty */
		| ospf_group_stmts ospf_group_stmt L_EOS
		| ospf_group_stmts error L_EOS
			{
				yyerrok;
			}
		;

ospf_group_stmt	: T_DEFAULTS '{' ospf_defaults '}'
			{
			}
		| T_TRACEOPTIONS trace_file_option trace_control_option ospf_trace_options_none
			{
			    trace_store(ospf.trace_options, $4, $3, $2, ospf_trace_types);
			}
		| T_EXPORTINTERVAL time
			{
			    ospf.export_interval = $2;
			}
		| T_EXPORTLIMIT number
			{
			    ospf.export_limit = $2;
			}
		| T_MONITORAUTH ospf_auth
			{
			    ospf.mon_auth.auth_type = $2.type;
			    ospf.mon_auth.auth_length = $2.len;
			    bcopy($2.ptr, (caddr_t) ospf.mon_auth.auth_key, $2.len);
			}
		| T_MONITORAUTHKEY
			{
			    ospf_auth_length = OSPF_AUTH_SIMPLE_SIZE;
			}
		ospf_auth_key
			{
			    ospf.mon_auth.auth_type = OSPF_AUTH_SIMPLE;
			    ospf.mon_auth.auth_length = OSPF_AUTH_SIMPLE_SIZE;
			    bcopy($3.ptr, (caddr_t) ospf.mon_auth.auth_key, $3.len);
			}
		| T_SYSLOG ospf_syslog_first ospf_syslog_every
			{
			    ospf.log_first = $2;
			    ospf.log_every = $3;
			}
		| ospf_area_option
			{
			    ospf_AREA = ospf_parse_area_alloc($1, parse_error);
			    if (!ospf_AREA) {
				PARSE_ERROR;
			    }
			    ospf_AREA->authtype = OSPF_AUTH_NONE;		/* Default to no authentication */
			}
		'{' ospf_area_stmts '}'
			{
			    if (ospf_parse_area_check(ospf_AREA, parse_error)) {
				PARSE_ERROR;
			    }
			}
		;

ospf_syslog_first
		: /* Empty */
			{
			    $$ = OSPF_LOG_FIRST;
			}
		| T_FIRST number
			{
			    if (parse_limit_check("syslog first",
						  (u_int) $2,
						  OSPF_LIMIT_LOG_FIRST)) {
				PARSE_ERROR;
			    }
			    $$ = $2;
			}
		;

ospf_syslog_every
		: /* Empty */
			{
			    $$ = OSPF_LOG_EVERY;
			}
		| T_EVERY number
			{
			    if (parse_limit_check("syslog every",
						  (u_int) $2,
						  OSPF_LIMIT_LOG_EVERY)) {
				PARSE_ERROR;
			    }
			    $$ = $2;
			}
		;

ospf_defaults	: /* Empty */
		| ospf_defaults ospf_default L_EOS
    		| ospf_defaults error L_EOS
			{
			    yyerrok;
			}
		;

ospf_default	: T_PREFERENCE preference
			{
			    ospf.preference_ase = $2;
			}
		| T_METRIC ospf_cost
			{
			    ospf.export_metric = $2.metric;
			}
@BEGIN:	PROTO_ASPATHS
		| T_TAG tag_as
			{
			    switch ($2.state) {
			    case PARSE_METRICS_SET:
				ospf.export_tag = $2.metric;
				break;

			    case PARSE_METRICS_ALTERNATE:
				ospf.export_tag = PATH_OSPF_TAG_TRUSTED |
				    (($2.metric << PATH_OSPF_TAG_USR_SHIFT) & PATH_OSPF_TAG_USR_MASK);
				break;
			    }
			}
@END:	PROTO_ASPATHS
		| T_TYPE ospf_type
			{
			    ospf.export_type = $2.metric;
			}
		;

ospf_area_stmts	: /* Empty */
    		| ospf_area_stmts ospf_area_stmt L_EOS
    		| ospf_area_stmts error L_EOS
			{
			    yyerrok;
			}
		;

ospf_area_stmt	: T_AUTHTYPE ospf_auth_type
			{
			    ospf_AREA->authtype = $2.type;
			    ospf_auth_length = $2.len;
			}
		| T_STUB ospf_cost_option
			{
			    if (ospf_AREA->area_id == OSPF_BACKBONE) {
				(void) sprintf(parse_error, "stub option not valid for backbone");
				PARSE_ERROR;
			    }

			    /* This is a stub */
			    BIT_SET(ospf_AREA->area_flags, OSPF_AREAF_STUB);

			    /* And we inject a default */
			    if (PARSE_METRIC_ISSET(&$2)) {
				BIT_SET(ospf_AREA->area_flags, OSPF_AREAF_STUB_DEFAULT);
				ospf_AREA->dflt_metric = $2.metric;
			    }
			}    
		| T_STUBHOSTS '{' ospf_stub_list '}' {}
		| T_NETWORKS '{' ospf_area_range_list '}'
			{
			    register dest_mask_internal *dmi;

			    if (ospf_AREA->nrcnt) {
				(void) sprintf(parse_error, "net range already specified");
				PARSE_ERROR;
			    }

			    /* Install each of the entries */
			    DMI_WALK_ALL($3->adv_dm.dm_internal, dmi, adv) {
				ospf_parse_add_net(ospf_AREA,
						   adv->adv_dm.dm_dest,
						   adv->adv_dm.dm_mask,
						   adv->adv_result.res_flag);
			    } DMI_WALK_ALL_END($3->adv_dm.dm_internal, dmi, adv) ;

			    adv_free_list($3);
			}
		| T_INTERFACE ospf_interface
			{
			    if (parse_adv_append(&ospf_AREA->intf_policy, $2)) {
				PARSE_ERROR;
			    }
			}
    		| T_VIRTUALLINK T_NEIGHBORID host T_TRANSITAREA ospf_area ospf_common
			{
			    struct INTF *vif;

			    vif = ospf_parse_virt_parse(ospf_AREA, $3, $5, $6, parse_error);
			    if (!vif) {
				PARSE_ERROR;
			    }

			    config_list_free($6);
			}
		;

ospf_interface
		: interface_all_list ospf_cost_option ospf_common
			{
			    config_list *list = $3;

			    if (PARSE_METRIC_ISSET(&$2)) {

				list = config_list_add(list,
						       config_alloc(OSPF_CONFIG_COST,
								    GS2A($2.metric)),
						       ospf_config_free);
				if (!list) {
				    PARSE_ERROR;
				}
			    }

			    parse_adv_propagate_config($1, list, RTPROTO_OSPF);

			    config_list_free(list);

			    $$ = $1;
			}
		| interface_all_list T_NONBROADCAST ospf_cost_option ospf_nonbroadcast
			{
			    config_list *list = $4;

			    list = config_list_add(list,
						   config_alloc(OSPF_CONFIG_TYPE,
								GS2A(NONBROADCAST)),
						   ospf_config_free);
			    if (!list) {
				PARSE_ERROR;
			    }
			    
			    if (PARSE_METRIC_ISSET(&$3)) {

				list = config_list_add(list,
						       config_alloc(OSPF_CONFIG_COST,
								    GS2A($3.metric)),
						       ospf_config_free);
				if (!list) {
				    PARSE_ERROR;
				}
			    }

			    parse_adv_propagate_config($1, list, RTPROTO_OSPF);

			    config_list_free(list);

			    $$ = $1;
			}
		;

ospf_common	: /* Empty */
			{
			    $$ = (config_list *) 0;
			}
		| '{' ospf_common_options '}'
			{
			    $$ = config_list_alloc($2, ospf_config_free);
			}
		;

ospf_common_options
		: ospf_common_option L_EOS
		| ospf_common_options ospf_common_option L_EOS
			{
			    $$ = config_append($1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		| ospf_common_options error L_EOS
			{
				yyerrok;
			}
		;

ospf_nonbroadcast
		: /* Empty */
			{
			    $$ = (config_list *) 0;
			}
		| '{' ospf_nonbroadcast_options '}'
			{
			    $$ = config_list_alloc($2, ospf_config_free);
			}
		;

ospf_nonbroadcast_options
		: ospf_nonbroadcast_option L_EOS
		| ospf_nonbroadcast_options ospf_nonbroadcast_option L_EOS
			{
			    $$ = config_append($1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		| ospf_nonbroadcast_options error L_EOS
			{
				yyerrok;
			}
		;

ospf_common_option
		: T_ENABLE
			{
			    $$ = config_alloc(OSPF_CONFIG_ENABLE, GS2A(TRUE));
			}
		| T_DISABLE
			{
			    $$ = config_alloc(OSPF_CONFIG_ENABLE, GS2A(FALSE));
			}
		| T_RXMITINTERVAL time
			{
			    if (parse_limit_check("retransmit-interval",
						  (u_int) $2,
						  OSPF_LIMIT_RETRANSMITINTERVAL)) {
				PARSE_ERROR;
			    }
			    $$ = config_alloc(OSPF_CONFIG_RETRANSMIT, GS2A($2));
			}
		| T_INFTRANSDELAY time
			{
			    if (parse_limit_check("transit-delay",
						  (u_int) $2,
						  OSPF_LIMIT_TRANSITDELAY)) {
				PARSE_ERROR;
			    }
			    $$ = config_alloc(OSPF_CONFIG_TRANSIT, GS2A($2));
			}
		| T_PRIORITY ospf_priority
			{
			    $$ = config_alloc(OSPF_CONFIG_PRIORITY, GS2A($2));
			}
		| T_HELLOINTERVAL time
			{
			    if (parse_limit_check("hello-interval",
						  (u_int) $2,
						  OSPF_LIMIT_HELLOINTERVAL)) {
				PARSE_ERROR;
			    }
			    $$ = config_alloc(OSPF_CONFIG_HELLO, GS2A($2));
			}
		| T_ROUTERDEADINTERVAL time
			{
			    if (parse_limit_check("router-dead-interval",
						  (u_int) $2,
						  OSPF_LIMIT_ROUTERDEADINTERVAL)) {
				PARSE_ERROR;
			    }
			    $$ = config_alloc(OSPF_CONFIG_ROUTERDEAD, GS2A($2));
			}
		| T_NOMULTICAST
			{
			    $$ = config_alloc(OSPF_CONFIG_NOMULTI, GS2A(TRUE));
			}
		| T_AUTH ospf_auth
			{
			    ospf_auth *oap = (ospf_auth *) task_block_alloc(ospf_auth_index);

			    oap->auth_type = $2.type;
			    oap->auth_length = $2.len;
			    bcopy($2.ptr, (caddr_t) oap->auth_key, $2.len);
			    free_bytestr($2);

			    $$ = config_alloc(OSPF_CONFIG_AUTH, GS2A(oap));
			}
		| T_SECONDARY T_AUTH ospf_auth
			{
			    ospf_auth *oap = (ospf_auth *) task_block_alloc(ospf_auth_index);

			    oap->auth_type = $3.type;
			    oap->auth_length = $3.len;
			    bcopy($3.ptr, (caddr_t) oap->auth_key, $3.len);
			    free_bytestr($3);

			    $$ = config_alloc(OSPF_CONFIG_AUTH2, GS2A(oap));
			}
		| T_AUTHKEY ospf_auth_key
			{
			    /* Side-effect: The authentication type must be specified first */

			    ospf_auth *oap = (ospf_auth *) task_block_alloc(ospf_auth_index);
			    
			    switch (ospf_AREA->authtype) {
			    case OSPF_AUTH_NONE:
				sprintf(parse_error, "authentication-key specified when authentication-type is none");
				PARSE_ERROR;
				/* break; */

			    case OSPF_AUTH_SIMPLE:
				/* Simple password */
				break;

			    case OSPF_AUTH_MD5:
				/* MD5 crypto checksum */
				break;
				
			    default:
				sprintf(parse_error, "unknown authentication type: %d",
					ospf_AREA->authtype);
				PARSE_ERROR;
			    }

			    oap->auth_type = ospf_AREA->authtype;
			    oap->auth_length = $2.len;
			    bcopy($2.ptr, (caddr_t) oap->auth_key, $2.len);

			    $$ = config_alloc(OSPF_CONFIG_AUTH, GS2A(oap));

			    free_bytestr($2);
			}
		;

ospf_nonbroadcast_option
		: ospf_common_option
		| T_POLLINTERVAL time
			{
			    if (parse_limit_check("poll-interval",
						  (u_int) $2,
						  OSPF_LIMIT_POLLINTERVAL)) {
				PARSE_ERROR;
			    }
			    $$ = config_alloc(OSPF_CONFIG_POLL, GS2A($2));
			}
		| T_ROUTERS '{' ospf_router_eligible_list '}'
			{
			    $$ = config_alloc(OSPF_CONFIG_ROUTERS, GS2A($3));
			}
		;

/* OSPF costs */
ospf_cost_option	: /* Empty */
			{
			    PARSE_METRIC_CLEAR(&$$);
			}
		| T_METRIC ospf_cost
			{
				$$ = $2;
			}
		;

ospf_cost	: metric
			{
			    $$ = $1;
			    if (parse_metric_check(RTPROTO_OSPF, &$$)) {
				PARSE_ERROR;
			    }
			}
		;

/* OSPF external route type */
ospf_type_option	: /* Empty */
			{
			    PARSE_METRIC_CLEAR(&$$);
			}
		| T_TYPE ospf_type
			{
			    $$ = $2;
			}
		;

ospf_type	: L_NUMBER
			{
			    if (parse_limit_check("export-type",
						  (u_int) $1,
						  OSPF_LIMIT_EXPORTTYPE)) {
				PARSE_ERROR;
			    }
			    PARSE_METRIC_SET(&$$, $1);
			}
		;

ospf_area_option
		: T_AREA ospf_area
			{
			    $$ = $2;
			}
		| T_BACKBONE
			{
			    $$ = OSPF_BACKBONE;
			}
		;

ospf_area	: number
			{
			    if (parse_limit_check("area-number",
						  (u_int) $1,
						  OSPF_LIMIT_AREA)) {
				PARSE_ERROR;
			    }
			    $$ = htonl((u_int32) $1);
			}
		;

ospf_auth	: ospf_auth_type
			{
			    ospf_auth_length = $1.len;
			}
		 ospf_auth_key
			{
			    /* Copy the key */
			    $$ = $3;	/* struct copy */
			    /* And get type type */
			    $$.type = $1.type;
			}
		;

ospf_auth_type	: T_NONE
			{
			    $$.type = OSPF_AUTH_NONE;
			    $$.len = 0;
			    
			}
		| T_SIMPLE
			{
			    $$.type = OSPF_AUTH_SIMPLE;
			    $$.len = OSPF_AUTH_SIMPLE_SIZE;
			}
		| T_MD5
			{
			    $$.type = OSPF_AUTH_MD5;
			    $$.len = OSPF_AUTH_MD5_SIZE;
			}
		;

ospf_auth_key	: string
			{
			    if ($1.len > ospf_auth_length) {
				sprintf(parse_error, "authentication-key \"%s\"%d longer than %d characters",
					$1.ptr,
					$1.len,
					ospf_auth_length);
				PARSE_ERROR;
			    }

			    $$.ptr = (byte *) task_mem_calloc((task *) 0, sizeof (u_int32), OSPF_AUTH_SIZE);
			    $$.len = ospf_auth_length;
			    $$.type = 0;

			    /* Left justify */
			    strncpy((caddr_t) $$.ptr, $1.ptr, $$.len);

			    free_charstr($1);
			}
		| L_NUMBER
			{
			    $$.ptr = (byte *) task_mem_calloc((task *) 0, sizeof (u_int32), OSPF_AUTH_SIZE);
			    $$.len = ospf_auth_length;
			    $$.type = 0;

			    /* Right justify the key */
			    bcopy((caddr_t) &$1,
				  $$.ptr + ospf_auth_length - sizeof ($1),
				  sizeof ($1));
			}
		| byte_string
			{
			    if ($1.len > ospf_auth_length) {
				sprintf(parse_error, "authentication-key longer than %d characters",
					ospf_auth_length);
				PARSE_ERROR;
			    }

			    $$.ptr = (byte *) task_mem_calloc((task *) 0, sizeof (u_int32), OSPF_AUTH_SIZE);
			    $$.len = ospf_auth_length;
			    $$.type = 0;

			    /* Right justify the key */
			    bcopy((caddr_t) $1.ptr,
				  $$.ptr + ospf_auth_length - $1.len,
				  $1.len);

			    free_bytestr($1);
			}
    		;



ospf_stub_list	: ospf_stub L_EOS
    		| ospf_stub_list ospf_stub L_EOS
    		| ospf_stub_list error L_EOS
			{
			    yyerrok;
			}
    		;

ospf_stub	: host T_METRIC ospf_cost
			{
			    ospf_parse_add_host(ospf_AREA, sock2ip($1), $3.metric);

			    sockfree($1);
			}
		;

ospf_router_eligible_list
		: ospf_router_eligible L_EOS
		| ospf_router_eligible_list ospf_router_eligible L_EOS
			{
			    ($$ = $2)->ocr_next = $1;
			}
		| ospf_router_eligible_list error L_EOS
			{
			    yyerrok;
			}
    		;

ospf_router_eligible
		: gateway_inet ospf_eligible_option
			{
			    $$ = ospf_parse_router_alloc(sock2in($1->gw_addr), (u_int) $2);
			}
		;

ospf_eligible_option
		: /* Empty */
			{
			    $$ = 0;
			}
		| T_ELIGIBLE
			{
			    $$ = 1;
			}
		;

ospf_priority	: L_NUMBER
			{
			    if (parse_limit_check("priority",
						  (u_int) $1,
						  OSPF_LIMIT_DRPRIORITY)) {
				PARSE_ERROR;
			    }
			    $$ = $1;
			}
		;

ospf_prop_init	: T_OSPF
			{
			    $$ = parse_proto = RTPROTO_OSPF;
			    parse_gwlist = (gw_entry **) 0;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s PROTO: %s",
				      parse_where(),
				      gd_lower(trace_state(rt_proto_bits, $$))));
			}
		;

ospf_ase_prop_init
		: T_OSPF_ASE
			{
			    /* Make sure this PS type is known */
			    adv_psfunc_add(RTPROTO_OSPF_ASE, &ospf_adv_psfunc);

			    $$ = parse_proto = RTPROTO_OSPF_ASE;
			    parse_gwlist = (gw_entry **) 0;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s PROTO: %s",
				      parse_where(),
				      gd_lower(trace_state(rt_proto_bits, $$))));
			}
		;

ospf_trace_options_none
		: T_NONE
			{
			    $$ = (flag_t) 0;
			}
		| ospf_trace_options
			{
			    $$ = $1;
			}
		| ospf_trace_options T_EXCEPT ospf_trace_options
			{
			    $$ = $1 & ~$3;
			}
    		;

ospf_trace_options
		: ospf_trace_option
			{
			    $$ = $1;
			}
		| ospf_trace_options ospf_trace_option
			{
			    $$ = $1 | $2;
			}
		;

ospf_trace_option
		: trace_option
    		| trace_option_detail trace_option_sendrecv ospf_trace_option_index
			{
			    $$ = trace_parse_packet($1, $2, $3);
			}
		| T_LSA_BLD
			{
			    $$ = TR_OSPF_LSA_BLD;
			}
		| T_LSA_TX
			{
			    $$ = TR_OSPF_LSA_TX;
			}
		| T_LSA_RX
			{
			    $$ = TR_OSPF_LSA_RX;
			}
		| T_SPF
			{
			    $$ = TR_OSPF_SPF;
			}
		| T_TRAP
			{
			    $$ = TR_OSPF_TRAP;
			}
		| T_DEBUG
			{
#ifdef	DEBUG
			    $$ = TR_OSPF_DEBUG;
#else	/* DEBUG */
			    $$ = 0;
#endif	/* DEBUG */
			}
		;

ospf_trace_option_index
		: T_PACKETS
			{
			    $$ = TR_OSPF_INDEX_PACKETS;
			}
		| T_HELLO
			{
			    $$ = TR_OSPF_INDEX_HELLO;
			}
		| T_DD
			{
			    $$ = TR_OSPF_INDEX_DD;
			}
		| T_REQUEST
			{
			    $$ = TR_OSPF_INDEX_LSR;
			}
		| T_UPDATE
			{
			    $$ = TR_OSPF_INDEX_LSU;
			}
		| T_ACK
			{
			    $$ = TR_OSPF_INDEX_ACK;
			}
		;
		

ospf_area_range_list
		: /* Empty */
			{
			    $$ = (adv_entry *) 0;
			}
		| ospf_area_range_list ospf_area_range ospf_area_range_option L_EOS
			{
			    if (sock2ip($2.dm_dest) == INADDR_ANY) {
				sprintf(parse_error, "invalid range %A/%A",
					$2.dm_dest,
					$2.dm_mask);
				PARSE_ERROR;
			    }
			    $$ = adv_alloc(ADVFT_DM, (proto_t) 0);
			    $$->adv_dm = $2;
			    $$->adv_result.res_flag = $3;
			    $$ = adv_destmask_insert(parse_error, $1, $$);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		| ospf_area_range_list error L_EOS
			{
			    yyerrok;
			}
		
		;

ospf_area_range	: host_mask_inet
		| network_mask_inet
		;

ospf_area_range_option
		: /* Empty */
			{
			    $$ = Advertise;
			}
		| T_RESTRICT
			{
			    $$ = DoNotAdvertise;
			}
  		;

@END:	PROTO_OSPF
    
/*  */

@BEGIN:	PROTO_ISIS

/* ISIS protocol statements & etc, in the format of other protocols */

isis_statement  : T_ISIS
                        {
			    PROTO_SEEN(RTPROTO_ISIS);

#ifdef	notyet
			    parse_gwlist = &isis.gw_list;
#endif	/* notyet */

			    isis_trace_options = trace_set_global(isis_trace_types,
								  (flag_t) 0);

			    /* XXX - should be done by above */
			    isis_plevel = 1;
                        }
		  isis_option isis_group 
			{

			    ip_supported = 0;
			    clnp_supported = 0;
			    switch ($3) {
			    case T_OFF:
				break;
			    /* XXX - Check validity of configuration for the following */
			    case T_IP:
				ip_supported = 1;
				doing_isis = TRUE;
				break;
			    case T_ISO:
				clnp_supported = 1;
				doing_isis = TRUE;
				break;
			    case T_ON:
			    case T_DUAL:
				ip_supported = clnp_supported = 1;
				doing_isis = TRUE;
			    }

			    parse_proto = (proto_t) 0;
#ifdef	notdef
			    parse_gwlist = (gw_entry **) 0;
#endif	/* notdef */
			}
		;

isis_option	: onoff_option
		| T_IP		{ $$ = T_IP; }
		| T_ISO		{ $$ = T_ISO; }
		| T_DUAL	{ $$ = T_DUAL; }
		;

isis_group      : /* Empty */
                | '{' isis_group_stmts '}'
		;

isis_group_stmts	: /* Empty */
		| isis_group_stmts isis_group_stmt L_EOS
		| isis_group_stmts error L_EOS
			{
				yyerrok;
			}
		;

isis_group_stmt	: isis_level
			{
			    isis_plevel = $1;
			}
		| T_CIRCUIT string
			{
			    if (BIT_TEST(task_state, TASKS_RECONFIG)) {
				if ((isis_ci = isis_GetIspcByName($2)) == 0) {
				    /* this is a config of a new circuit */    
				    isis_ci = ++isis_circuits_parsed;
				    bzero(&isis_ca[isis_ci], sizeof(struct is_pc));
				    strcpy(isis_ca[isis_ci].name, $2.ptr);
			    	    /* isis_init_ca(&isis_ca[isis_ci], $2); */
				    trace_tf(trace_global,
					     TR_PARSE,
					     0,
					     ("parse: %s IS-IS reconfig parsed new circuit #%d -> %s",
					      parse_where(),
					      isis_ci,
					      $2));
				} else {
				    trace_tf(trace_global,
					     TR_PARSE,
					     0,
					     ("parse: %s IS-IS reconfig parsed existing circuit #%d -> %s",
					      parse_where(),
					      isis_ci,
					      $2));
				} 
			    } else {
				/* remember new circuit */
			    	isis_ci = ++isis_circuits_parsed;
				trace_tf(trace_global,
					 TR_PARSE,
					 0,
					 ("parse: %s IS-IS config parsed new circuit #%d -> %s",
					  parse_where(),
					  isis_ci,
					  $2));
				bzero(&isis_ca[isis_ci], sizeof(struct is_pc));
				strcpy(isis_ca[isis_ci].name, $2.ptr);
			    	/* isis_init_ca(&isis_ca[isis_ci], $2); */
			    }
			}
		isis_coptions
			{
			}
		| T_SYSTEMID string
			{
			    isis_set_sysid($2);
			}
		| T_TRACEOPTIONS isis_trace_options
			{
			    isis_save_trace($2);
			}
		| T_SNPA number
			{
			    /* we need an index in lieu of the NSAP address; used to use getpid */
			    isis_snpa = $2;
			}
		| T_AREA string
			{
			    isis_saveArea($2);
			}
		| T_IPREACH isis_level ipreach_type network_inet mask T_METRIC number 
			{
			    save_ipreach($2,$3,&$4,&$5,$7);
			}
		| T_PREFIX prefix_type T_METRIC number string
			{
			    isis_savePrefix($5.ptr, $4, $2);
			}
		| T_INTDOMINFO string
			{
			    isis_saveInterDomInfo($2);
			}
		| T_SET L_KEYWORD number
			{
			    isis_set_parm($2.ptr, $3);
			}
    		/* nothing else for now */
		;

isis_level	: T_LEVEL number
			{
			    $$ = $2;
			}
		| /* empty */
			{
			    $$ = 1;
			}
		;

isis_mode	: T_IP
			{
			    $$ = T_IP;
			}
                | T_ISO
			{
			    $$ = T_ISO;
			}
                | T_DUAL
			{
			    $$ = T_DUAL;
			}
                ;

isis_coptions	: /* Empty */
		| isis_coptions isis_coption
		;

isis_coption	: T_METRIC isis_level number
			{
			    if ($2 == 2) {
				isis_ca[isis_ci].l2metric = $3;
			    } else {
				isis_ca[isis_ci].metric = $3;
			    }
			}
		| T_PRIORITY isis_level number
			{
			    if ($2 == 2) {
				isis_ca[isis_ci].l2prior = $3;
			    } else {
				isis_ca[isis_ci].prior = $3;
			    }
			}
		;

ipreach_type	: T_INTERNAL
			{
			    $$ = ISIS_INTERNAL;
			}
		| T_EXTERNAL
			{
			    $$ = ISIS_EXTERNAL;
			}
		| TISIS_SUMMARY
			{
			    $$ = ISIS_SUMMARY;
			}
		;

prefix_type	: T_INTERNAL
			{
			    $$ = ISIS_INTERNAL;
			}
		| T_EXTERNAL
			{
			    $$ = ISIS_EXTERNAL;
			}
		;

isis_trace_options	: isis_trace_option
			| isis_trace_options isis_trace_option
				{
				    $$ = $1 | $2;
				}
			| isis_trace_options T_EXCEPT isis_trace_option
				{
				    $$ = $1 & ~$2;
				}
			;

isis_trace_option
    		: T_ALL         { $$ = T_ISISALL; }
		| TISIS_IIH		{ $$ = T_DUMPIIH; }
		| TISIS_DUMPLSP         { $$ = T_DUMPLSP; }
		| TISIS_EVENTS          { $$ = T_EVENTS; }
		| TISIS_LANADJ          { $$ = T_LANADJ; }
		| TISIS_FLOODING        { $$ = T_FLOODING; }
		| TISIS_BUILDLSP        { $$ = T_BUILDLSP; }
		| TISIS_CSNP            { $$ = T_CSNP; }
		| TISIS_PSNP            { $$ = T_PSNP; }
		| TISIS_LSPINPUT        { $$ = T_LSPINPUT; }
		| TISIS_P2PADJ          { $$ = T_P2PADJ; }
		| T_SPF             	{ $$ = T_TRSPF; }
		| TISIS_LSPDB           { $$ = T_DUMPDB; }
		| T_ROUTE		{ $$ = T_ROUTE2; }
		| T_UPDATE		{ $$ = T_ROUTE1; }
		| TISIS_PATHS		{ $$ = T_ROUTE3; }
		| TISIS_LSPCONTENT	{ $$ = T_LSPCONTENT; }
		;


isis_prop_init	: T_ISIS
			{
			    $$ = parse_proto = RTPROTO_ISIS;
			    parse_gwlist = (gw_entry **) 0;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s PROTO: %s",
				      parse_where(),
				      gd_lower(trace_state(rt_proto_bits, $$))));
			}
		;

@END:	PROTO_ISIS

/*  */

@BEGIN:	PROTO_SLSP

slsp_statement : T_SLSP
			{
			    PROTO_SEEN(RTPROTO_SLSP);

			    slsp_global_trace_options = trace_set_global(slsp_trace_types,
								  (flag_t) 0);
                        }
		onoff_option slsp_group
			{

			    switch ($3) {
			    case T_OFF:
				doing_slsp = FALSE;
				break;
				
			    case T_ON:
				/* XXX - Check validity of configuration */
				doing_slsp = TRUE;
			    }

			    parse_proto = (proto_t) 0;
			}
		;
    
slsp_group      : /* Empty */
                | '{' slsp_group_stmts '}'
		;

slsp_group_stmts
		: /* Empty */
		| slsp_group_stmts slsp_group_stmt L_EOS
		| slsp_group_stmts error L_EOS
			{
				yyerrok;
			}
		;

slsp_group_stmt	: T_INSTANCE T_NODE network_mask_inet T_NODEMASK mask_inet preference_option
			{
			    slsp_parse_instance = slsp_parse_instance_alloc($3.dm_dest,
									    $3.dm_mask,
									    $5);

			    if (PARSE_METRIC_ISSET(&$6)) {
				slsp_parse_instance->slsp_preference = $6.metric;
			    }
			}
		  '{' slsp_instance_list '}'
			{
			    if (slsp_parse_instance_check(&slsp_parse_instance, parse_error)) {
				PARSE_ERROR;
			    }
			}
		| T_TRACEOPTIONS trace_file_option trace_control_option slsp_trace_options_none
			{
			    trace_store(slsp_global_trace_options, $4, $3, $2, slsp_trace_types);
			}
		;

slsp_instance_list
		: slsp_instance L_EOS
		| slsp_instance_list slsp_instance L_EOS
		;

slsp_instance	: T_DEFAULTS '{' slsp_defaults '}' {}
		| T_TRACEOPTIONS trace_file_option trace_control_option slsp_trace_options_none
			{
			    trace_store(slsp_parse_instance->slsp_trace_options, $4, $3, $2, slsp_trace_types);
			}
		| T_INTERFACE interface_all_list slsp_interfaces
			{
			    config_list *list = config_list_alloc($3, slsp_config_free);

			    parse_adv_propagate_config($2, list, RTPROTO_SLSP);

			    if (parse_adv_append(&slsp_parse_instance->slsp_policy, $2)) {
				PARSE_ERROR;
			    }

			    config_list_free(list);
			}
		| T_NEIGHBOR
			{
			    parse_gwlist = &parse_gwp;
			}
		  gateway_inet
			{
			    slsp_parse_gateway = slsp_parse_gateway_alloc(slsp_parse_instance, $3->gw_addr);

			    gw_freelist(*parse_gwlist);
			    parse_gwlist = (gw_entry **) 0;
			    parse_gwp = (gw_entry *) 0;
			}
		  slsp_gateway_list
			{
			    if (slsp_parse_gateway_check(slsp_parse_instance, &slsp_parse_gateway, parse_error)) {
				PARSE_ERROR;
			    }
			}
		;


slsp_defaults	: slsp_default
		| slsp_defaults slsp_default
		;

slsp_default	: slsp_hello
			{
			    slsp_parse_instance->slsp_def_hellointerval = $1;
			}
		| slsp_dead
			{
			    slsp_parse_instance->slsp_def_routerdeadinterval = $1;
			}
		| slsp_cost
			{
			    slsp_parse_instance->slsp_def_cost = $1.metric;
			}
		| slsp_priority
			{
			    slsp_parse_instance->slsp_def_priority = $1;
			}
		;

slsp_interfaces
		: slsp_interface
		| slsp_interfaces slsp_interface
			{
			    $$ = config_append($1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		;

slsp_interface	: slsp_hello
			{
			    $$ = config_alloc(SLSP_CONFIG_HELLO, GS2A($1));
			}
		| slsp_dead
			{
			    $$ = config_alloc(SLSP_CONFIG_ROUTER, GS2A($1));
			}
		| slsp_cost
			{
			    $$ = config_alloc(SLSP_CONFIG_COST, GS2A($1.metric));
			}
		| slsp_priority
			{
			    $$ = config_alloc(SLSP_CONFIG_PRIORITY, GS2A($1));
			}
		| T_TRACEOPTIONS trace_file_option trace_control_option slsp_trace_options_none
			{
			    trace *trp = (trace *) 0;
			    
			    trace_store(trp, $4, $3, $2, slsp_trace_types);

			    if (trp) {
				$$ = config_alloc(SLSP_CONFIG_TRACE, GS2A(trp));
			    } else {
				$$ = (config_entry *) 0;
			    }
			}
		;

slsp_gateway_list
		: slsp_gateway
		| slsp_gateway_list slsp_gateway
		;

slsp_gateway	: slsp_hello
			{
			    slsp_parse_gateway->slsp_gw_hellointerval = $1;
			}
		| slsp_dead
			{
			    slsp_parse_gateway->slsp_gw_routerdeadinterval = $1;
			}
		| slsp_cost
			{
			    slsp_parse_gateway->slsp_gw_cost = $1.metric;
			}
		| slsp_priority
			{
			    slsp_parse_gateway->slsp_gw_priority = $1;
			}
		| T_TRACEOPTIONS trace_file_option trace_control_option slsp_trace_options_none
			{
			    trace_store(slsp_parse_gateway->slsp_gw_trace_options, $4, $3, $2, slsp_trace_types);
			}
		;

slsp_hello	: T_HELLOINTERVAL time
			{
			    $$ = $2;
			    if (parse_limit_check("hello-interval",
						  (u_int) $$,
						  SLSP_LIMIT_HELLOINTERVAL)) {
				PARSE_ERROR;
			    }
			}
		;

slsp_dead	: T_ROUTERDEADINTERVAL time
			{
			    $$ = $2;
			    if (parse_limit_check("router-dead-interval",
						  (u_int) $$,
						  SLSP_LIMIT_ROUTERDEADINTERVAL)) {
				PARSE_ERROR;
			    }
			}
		;

slsp_cost	: T_METRIC metric
			{
			    $$ = $2;
			    if (parse_metric_check(RTPROTO_SLSP, &$$)) {
				PARSE_ERROR;
			    }
			}
		;

slsp_priority	: T_PRIORITY L_NUMBER
			{
			    $$ = $2;
			    if (parse_limit_check("priority",
						  (u_int) $$,
						  SLSP_LIMIT_PRIORITY)) {
				PARSE_ERROR;
			    }
			}
		;

slsp_trace_options_none
		: T_NONE
			{
			    $$ = (flag_t) 0;
			}
		| slsp_trace_options
			{
			    $$ = $1;
			}
		| slsp_trace_options T_EXCEPT slsp_trace_options
			{
			    $$ = $1 & ~$3;
			}
    		;

slsp_trace_options
		: slsp_trace_option
			{
			    $$ = $1;
			}
		| slsp_trace_options slsp_trace_option
			{
			    $$ = $1 | $2;
			}
		;

slsp_trace_option
		: trace_option
    		| trace_option_detail trace_option_sendrecv slsp_trace_option_index
			{
			    $$ = trace_parse_packet($1, $2, $3);
			}
		| T_SPF
			{
			    $$ = TR_OSPF_SPF;
			}
		;

slsp_trace_option_index
		: T_PACKETS
			{
			    $$ = TR_SLSP_INDEX_PACKETS;
			}
		| T_REQUEST
			{
			    $$ = TR_SLSP_INDEX_HELLO;
			}
		| T_RESPONSE
			{
			    $$ = TR_SLSP_INDEX_LSP;
			}
    		;

slsp_prop_init	: T_SLSP
			{
			    $$ = parse_proto = RTPROTO_SLSP;
			    parse_gwlist = (gw_entry **) 0;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s PROTO: %s",
				      parse_where(),
				      gd_lower(trace_state(rt_proto_bits, $$))));
			}
		;

@END:	PROTO_SLSP    

/*  */

@BEGIN:	PROTO_RDISC

rdisc_statement : T_ROUTERDISCOVERY
			{
			    PROTO_SEEN(RTPROTO_RDISC);

			    rdisc_trace_options = trace_set_global(rdisc_trace_types,
								  (flag_t) 0);
                        }
		rdisc_choice
			{
			    doing_rdisc = $3;

			    parse_proto = (proto_t) 0;
			}
		;

rdisc_choice	: T_SERVER onoff_option rdisc_server_group
			{

			    switch ($2) {
			    case T_OFF:
				$$ = RDISC_DOING_OFF;
				break;
				
			    case T_ON:
				/* XXX - Check validity of */
				/* configuration */
				$$ = RDISC_DOING_SERVER;
			    }
			}
		| T_CLIENT onoff_option rdisc_client_group
			{

			    switch ($2) {
			    case T_OFF:
				$$ = RDISC_DOING_OFF;
				break;
				
			    case T_ON:
				/* XXX - Check validity of configuration */
				$$ = RDISC_DOING_CLIENT;
			    }
			}
		;

/* Server stuff */    
rdisc_server_group
		: /* Empty */
                | '{' rdisc_server_group_stmts '}'
		;

rdisc_server_group_stmts
		: /* Empty */
		| rdisc_server_group_stmts rdisc_server_group_stmt L_EOS
		| rdisc_server_group_stmts error L_EOS
			{
			    yyerrok;
			}
		;

rdisc_server_group_stmt
		: T_INTERFACE intf_phys_all_list rdisc_server_phys_options
			{
			    config_list *list = config_list_alloc($3, 0);

			    parse_adv_propagate_config($2, list, 0);

			    if (parse_adv_append(&rdisc_interface_policy, $2)) {
				PARSE_ERROR;
			    }

			    config_list_free(list);
			}
		| T_ADDRESS interface_all_list rdisc_server_addr_options
			{
			    config_list *list = config_list_alloc($3, 0);

			    parse_adv_propagate_config($2, list, 0);

			    if (parse_adv_append(&rdisc_server_address_policy, $2)) {
				PARSE_ERROR;
			    }

			    config_list_free(list);
			}
		| T_TRACEOPTIONS trace_file_option trace_control_option rdisc_trace_options_none
			{
			    trace_store(rdisc_trace_options, $4, $3, $2, rdisc_trace_types);
			}
		;

rdisc_server_phys_options
		: rdisc_server_phys_option
		| rdisc_server_phys_options rdisc_server_phys_option
			{
			    $$ = config_append($1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		;

rdisc_server_phys_option
		: T_MAXADVINTERVAL time
			{
			    if (parse_limit_check("maxadvertisementlinterval",
						  (u_int) $2,
						  RDISC_LIMIT_MAXADVINT)) {
				PARSE_ERROR;
			    }
			    $$ = config_alloc(RDISC_CONFIG_MAXADVINT, GS2A($2));
			}
		| T_MINADVINTERVAL time
			{
			    if (parse_limit_check("minadvertisementlinterval",
						  (u_int) $2,
						  RDISC_LIMIT_MINADVINT)) {
				PARSE_ERROR;
			    }
			    $$ = config_alloc(RDISC_CONFIG_MINADVINT, GS2A($2));
			}
		| T_LIFETIME time
			{
			    if (parse_limit_check("advertisementlifetime",
						  (u_int) $2,
						  RDISC_LIMIT_LIFETIME)) {
				PARSE_ERROR;
			    }
			    $$ = config_alloc(RDISC_CONFIG_LIFETIME, GS2A($2));
			}
		;

rdisc_server_addr_options
		: rdisc_server_addr_option
		| rdisc_server_addr_options rdisc_server_addr_option
			{
			    $$ = config_append($1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		;

rdisc_server_addr_option
		: T_ADVERTISE
			{
			    $$ = config_alloc(RDISC_CONFIG_IFA_IGNORE, GS2A(FALSE));
			}
		| T_IGNORE
			{
			    $$ = config_alloc(RDISC_CONFIG_IFA_IGNORE, GS2A(TRUE));
			}
		| T_BROADCAST
			{
			    $$ = config_alloc(RDISC_CONFIG_IFA_BROADCAST, GS2A(TRUE));
			}
		| T_MULTICAST
			{
			    $$ = config_alloc(RDISC_CONFIG_IFA_BROADCAST, GS2A(FALSE));
			}
		| T_INELIGIBLE
			{
			    $$ = config_alloc(RDISC_CONFIG_IFA_PREFERENCE, GS2A(RDISC_PREFERENCE_INELIGIBLE));
			}
		| T_PREFERENCE neg_number
			{
			  s_int32 pref = $2;

			  if (pref == RDISC_PREFERENCE_INELIGIBLE) {
			    (void) sprintf(parse_error,
					   "invalid preference value: %x, use `ineligible'",
					   $2);
			    PARSE_ERROR;
			  }
			  $$ = config_alloc(RDISC_CONFIG_IFA_PREFERENCE, GS2A($2));
			}
		;

/* Client stuff */
rdisc_client_group
		: /* Empty */
                | '{' rdisc_client_group_stmts '}'
		;

rdisc_client_group_stmts
		: /* Empty */
		| rdisc_client_group_stmts rdisc_client_group_stmt L_EOS
		| rdisc_client_group_stmts error L_EOS
			{
			    yyerrok;
			}
		;

rdisc_client_group_stmt
		: T_PREFERENCE preference
			{
			    rdisc_client_preference = $2;
			}
		| T_INTERFACE intf_phys_all_list rdisc_client_phys_options
			{
			    config_list *list = config_list_alloc($3, 0);

			    parse_adv_propagate_config($2, list, 0);

			    if (parse_adv_append(&rdisc_interface_policy, $2)) {
				PARSE_ERROR;
			    }

			    config_list_free(list);
			}
		| T_TRACEOPTIONS trace_file_option trace_control_option rdisc_trace_options_none
			{
			    trace_store(rdisc_trace_options, $4, $3, $2, rdisc_trace_types);
			}
		;

rdisc_client_phys_options
		: rdisc_client_phys_option
		| rdisc_client_phys_options rdisc_client_phys_option
			{
			    $$ = config_append($1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		;

rdisc_client_phys_option
		: T_DISABLE
			{
			    $$ = config_alloc(RDISC_CONFIG_CLIENT_DISABLE, GS2A(TRUE));
			}
		| T_ENABLE
			{
			    $$ = config_alloc(RDISC_CONFIG_CLIENT_DISABLE, GS2A(FALSE));
			}
		| T_BROADCAST
			{
			    $$ = config_alloc(RDISC_CONFIG_CLIENT_BROADCAST, GS2A(TRUE));
			}
		| T_MULTICAST
			{
			    $$ = config_alloc(RDISC_CONFIG_CLIENT_BROADCAST, GS2A(FALSE));
			}
		| T_QUIET
			{
			    $$ = config_alloc(RDISC_CONFIG_CLIENT_QUIET, GS2A(TRUE));
			}
		| T_SOLICIT
			{
			    $$ = config_alloc(RDISC_CONFIG_CLIENT_QUIET, GS2A(FALSE));
			}
		;

/* Common stuff */
rdisc_trace_options_none
		: T_NONE
			{
			    $$ = (flag_t) 0;
			}
		| rdisc_trace_options
			{
			    $$ = $1;
			}
		| rdisc_trace_options T_EXCEPT rdisc_trace_options
			{
			    $$ = $1 & ~$3;
			}
    		;

rdisc_trace_options
		: rdisc_trace_option
			{
			    $$ = $1;
			}
		| rdisc_trace_options rdisc_trace_option
			{
			    $$ = $1 | $2;
			}
		;

rdisc_trace_option
		: trace_option
		;
@END:	PROTO_RDISC

/*  */

@BEGIN:	PROTO_IDPR

idpr_statement	: T_IDPR onoff_option idpr_config_file
			{
			    PROTO_SEEN(RTPROTO_IDPR);
			    
			    doing_idpr = ($2 == T_OFF) ? FALSE : TRUE;
			    (void) strcpy(idpr_db_name, $3.ptr);
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s idpr %s config = %s",
				      parse_where(), 
				      doing_idpr ? "on" : "off",
				      idpr_db_name));
			    parse_proto = (proto_t) 0;
 			}
		;

idpr_config_file
		: string
		| /* Empty */
			{
			    $$.ptr = task_mem_strdup((task *) 0, IDPR_CONFIG_DEFAULT);
			    $$.len = strlen($$.ptr);
			}
		;

@END:	PROTO_IDPR

/*  */

@BEGIN:	PROTO_EGP

egp_statement	: T_EGP
			{
			    PROTO_SEEN(RTPROTO_EGP);

			    parse_gwlist = &parse_gwp;

			    egp_trace_options = trace_set_global(egp_trace_types,
								 (flag_t) 0);
			}
		onoff_option egp_group
			{
			    switch ($3) {
			    case T_ON:
				doing_egp = TRUE;

				if (!inet_autonomous_system) {
				    (void) sprintf(parse_error, "autonomous-system not specified");
				    PARSE_ERROR;
				}
				if (!egp_neighbors) {
				    (void) sprintf(parse_error, "no EGP neighbors specified");
				    PARSE_ERROR;
				}

#if	defined(PROTO_SNMP)
				egp_sort_neighbors((egp_neighbor *) 0);
#endif	/* defined(PROTO_SNMP) */
				break;

			    case T_OFF:
				doing_egp = FALSE;
			    }

			    parse_proto = (proto_t) 0;
			    parse_gwlist = (gw_entry **) 0;
			}
		;

egp_group	: /* Empty */
		| '{' egp_group_stmts '}'
		;

egp_group_stmts	: /* Empty */
		| egp_group_stmts egp_group_stmt L_EOS
		| egp_group_stmts error L_EOS
			{
			    yyerrok;
			}
		;

egp_group_stmt	: T_PREFERENCE preference
			{
			    egp_preference = $2;
			}
		| T_PREFERENCE2 preference
			{
			    egp_preference2 = $2;
			}
		| T_DEFAULTMETRIC metric
			{
			    if (parse_metric_check(RTPROTO_EGP, &$2)) {
				PARSE_ERROR;
			    }
			    egp_default_metric = $2.metric;
			}
		| T_PKTSIZE number
			{
			    if (parse_limit_check("packetsize",
						  (u_int) $2,
						  EGP_LIMIT_PKTSIZE)) {
				PARSE_ERROR;
			    }
			    egp_pktsize = $2;
			}
		| T_TRACEOPTIONS trace_file_option trace_control_option egp_trace_options_none
			{
			    trace_store(egp_trace_options, $4, $3, $2, egp_trace_types);
			}
		| T_GROUP
			{
			    /* Clear group structure and set fill pointer */
			    bzero((caddr_t) &egp_group, sizeof(egp_group));
			    ngp = &egp_group;
			    ngp->ng_trace_options = trace_alloc(egp_trace_options);
			    /* First neighbor in group is head of group */
			    gr_ngp = (egp_neighbor *) 0;
			    parse_group_index++;
			}
		egp_group_options '{' egp_peer_stmts '}'
			{
			    if (gr_ngp->ng_gr_acquire > gr_ngp->ng_gr_number) {
				(void) sprintf(parse_error,
					       "maxacquire %u is greater than number of neighbors %u in group %d",
					       gr_ngp->ng_gr_acquire,
					       gr_ngp->ng_gr_number,
					       parse_group_index);
				PARSE_ERROR;
			    } else if (!gr_ngp->ng_gr_acquire) {
				gr_ngp->ng_gr_acquire = gr_ngp->ng_gr_number;
			    }

			}
		;

egp_peer_stmts	: /* Empty */
		| egp_peer_stmts egp_peer_stmt L_EOS
		| egp_peer_stmts error L_EOS
			{
			    yyerrok;
			}
		;

egp_peer_stmt	: T_NEIGHBOR
			{
			    ngp = egp_ngp_alloc(&egp_group);

			    if (!gr_ngp) {
				/* This neighbor is head of the group */

				gr_ngp = ngp;
			    } else {
				/* Not the head of the group, inherit the trace options */

				ngp->ng_trace_options = trace_alloc(gr_ngp->ng_trace_options);
			    }
			    parse_gwlist = &parse_gwp;
			}
		host_inet egp_peer_options
                        {
			    int add = TRUE;
			    egp_neighbor *ngp2;

			    /* Set neighbor's address */
			    ngp->ng_addr = $3;
			    ngp->ng_gw.gw_proto = RTPROTO_EGP;
			    ngp->ng_gw.gw_rtq.rtq_forw = ngp->ng_gw.gw_rtq.rtq_back = &ngp->ng_gw.gw_rtq;
			    (void) sprintf(ngp->ng_name, "%A",
					   ngp->ng_addr);

			    /* Set group pointer and count this neighbor */
			    ngp->ng_gr_head = gr_ngp;
			    ngp->ng_gr_index = parse_group_index;
			    gr_ngp->ng_gr_number++;

			    EGP_LIST(ngp2) {
				if (sockaddrcmp_in(ngp->ng_addr, ngp2->ng_addr)) {
				    if (BIT_TEST(ngp2->ng_flags, NGF_DELETE)) {
					if (!egp_neighbor_changed(ngp2, ngp)) {
					    BIT_RESET(ngp2->ng_flags, NGF_DELETE);
					    egp_ngp_free(ngp);
					    add = FALSE;
					    break;
					} else {
					    ngp->ng_flags = NGF_WAIT;
					}
				    } else {
					(void) sprintf(parse_error, "duplicate EGP neighbor at %A",
						       ngp->ng_addr);
					PARSE_ERROR;
				    }
				}
			    } EGP_LIST_END(ngp2) ;
			    
			    /* Add this neighbor to end of the list */
			    if (add) {
				INSQUE(ngp, egp_neighbor_head.ng_back);
				egp_neighbors++;
			    }
			}
		;

egp_group_options
		: /* Empty */
		| egp_group_options egp_group_option
		| egp_group_options egp_peer_option
		;

egp_group_option
		: T_PEERAS as
			{
			    BIT_SET(ngp->ng_options, NGO_PEERAS);
			    ngp->ng_peer_as = $2;
			}
		| T_LOCALAS as
			{
			    BIT_SET(ngp->ng_options, NGO_LOCALAS);
			    ngp->ng_local_as = $2;
#ifdef	PROTO_ASPATHS
			    aslocal_set($2, 0);
#endif	/* PROTO_ASPATHS */
			}
		| T_MAXUP L_NUMBER
			{
			    /* XXX - Limit check maxup value */
			    BIT_SET(ngp->ng_options, NGO_MAXACQUIRE);
			    ngp->ng_gr_acquire = $2;
			}
		| T_VERSION L_NUMBER
			{
			    if ( !(EGPVMASK & (1 << ($2 - 2))) ) {
				(void) sprintf(parse_error, "unsupported EGP version: %d",
					       $2);
				PARSE_ERROR;
			    }
			    BIT_SET(ngp->ng_options, NGO_VERSION);
			    ngp->ng_version = $2;
			}
		;

egp_peer_options
		: /* Empty */
		| egp_peer_options egp_peer_option
		;

egp_peer_option	: T_METRICOUT metric
			{
			    if (parse_metric_check(RTPROTO_EGP, &$2)) {
				PARSE_ERROR;
			    }
			    ngp->ng_metricout = $2.metric;
			    BIT_SET(ngp->ng_options, NGO_METRICOUT);
			}
		| T_NOGENDEFAULT
			{
			    BIT_SET(ngp->ng_options, NGO_NOGENDEFAULT);
			}
		| T_DEFAULTIN
			{
			    BIT_SET(ngp->ng_options, NGO_DEFAULTIN);
			}
		| T_DEFAULTOUT
			{
			    BIT_SET(ngp->ng_options, NGO_DEFAULTOUT);
			}
		| T_GATEWAY gateway_inet
			{
			    BIT_SET(ngp->ng_options, NGO_GATEWAY);
			    ngp->ng_gateway = sockdup($2->gw_addr);
			    gw_freelist(*parse_gwlist);
			    parse_gwlist = (gw_entry **) 0;
			    parse_gwp = (gw_entry *) 0;
			}
		| T_LCLADDR interface_local
			{
			    BIT_SET(ngp->ng_options, NGO_LCLADDR);
			    ngp->ng_lcladdr = $2;
			}
		| T_SOURCENET network_inet
			{
			    BIT_SET(ngp->ng_options, NGO_SADDR);
			    ngp->ng_saddr = $2;
			}
 		| T_P1 time
 			{
 			    if (parse_limit_check("P1",
						  (u_int) $2,
						  EGP_LIMIT_P1)) {
 				PARSE_ERROR;
 			    }
 			    BIT_SET(ngp->ng_options, NGO_P1);
 			    ngp->ng_P1 = $2;
 			}
 		| T_P2 time
 			{
 			    if (parse_limit_check("P2",
						  (u_int) $2,
						  EGP_LIMIT_P2)) {
 				PARSE_ERROR;
 			    }
 			    BIT_SET(ngp->ng_options, NGO_P2);
 			    ngp->ng_P2 = $2;
			}
		| T_TTL inet_ttl
			{
			    BIT_SET(ngp->ng_options, NGO_TTL);
			    ngp->ng_ttl = $2;
			}
		| T_PREFERENCE preference
			{
			    BIT_SET(ngp->ng_options, NGO_PREFERENCE);
			    ngp->ng_preference = $2;
			}
		| T_PREFERENCE2 preference
			{
			    BIT_SET(ngp->ng_options, NGO_PREFERENCE2);
			    ngp->ng_preference2 = $2;
			}
		| T_TRACEOPTIONS trace_file_option trace_control_option egp_trace_options_none
			{
			    trace_store(ngp->ng_trace_options, $4, $3, $2, egp_trace_types);
			}
		;


egp_trace_options_none
		: T_NONE
			{
			    $$ = (flag_t) 0;
			}
		| egp_trace_options
			{
			    $$ = $1;
			}
		| egp_trace_options T_EXCEPT egp_trace_options
			{
			    $$ = $1 & ~$3;
			}
    		;

egp_trace_options
		: egp_trace_option
			{
			    $$ = $1;
			}
		| egp_trace_options egp_trace_option
			{
			    $$ = $1 | $2;
			}
		;

egp_trace_option
		: trace_option
    		| trace_option_detail trace_option_sendrecv egp_trace_option_index
			{
			    $$ = trace_parse_packet($1, $2, $3);
			}
		| T_DEBUG
			{
#ifdef	DEBUG
			    $$ = TR_EGP_DEBUG;
#else	/* DEBUG */
			    $$ = 0;
#endif	/* DEBUG */
			}
		;

egp_trace_option_index
		: T_PACKETS
			{
			    $$ = TR_EGP_INDEX_PACKETS;
			}
		| T_UPDATE
			{
			    $$ = TR_EGP_INDEX_UPDATE;
			}
		| T_ACQUIRE
			{
			    $$ = TR_EGP_INDEX_ACQUIRE;
			}
		| T_HELLO
			{
			    $$ = TR_EGP_INDEX_HELLO;
			}
		;

egp_prop_init
		: T_EGP
			{
			    $$ = parse_proto = RTPROTO_EGP;
			    parse_gwlist = (gw_entry **) 0;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s PROTO: %s",
				      parse_where(),
				      gd_lower(trace_state(rt_proto_bits, $$))));
			}
		;


@END:	PROTO_EGP
    
/*  */

@BEGIN:	PROTO_BGP

bgp_statement	: T_BGP
			{
			    PROTO_SEEN(RTPROTO_BGP);

			    parse_gwlist = &parse_gwp;

			    bgp_default_trace_options = trace_set_global(bgp_trace_types,
									 (flag_t) 0);
			}
		onoff_option bgp_group
			{
			    switch ($3) {
			    case T_ON:
				doing_bgp = TRUE;

				if (!bgp_conf_check(parse_error)) {
				    PARSE_ERROR;
				}
				break;

			    case T_OFF:
				doing_bgp = FALSE;
			    }

			    parse_proto = (proto_t) 0;
			    parse_gwlist = (gw_entry **) 0;
			}
		;

bgp_group	: /* Empty */
		| '{' bgp_group_stmts '}'
		;

bgp_group_stmts	: /* Empty */
		| bgp_group_stmts bgp_group_stmt L_EOS
		| bgp_group_stmts error L_EOS
			{
			    yyerrok;
			}
		;

bgp_group_stmt	: T_PREFERENCE preference
			{
			    bgp_default_preference = $2;
			}
		| T_PREFERENCE2 preference
			{
			    bgp_default_preference2 = $2;
			}
		| T_DEFAULTMETRIC metric
			{
			    if (parse_metric_check(RTPROTO_BGP, &$2)) {
				PARSE_ERROR;
			    }
			    bgp_default_metric = $2.metric;
			}
		| T_TRACEOPTIONS trace_file_option trace_control_option bgp_trace_options_none
			{
			    trace_store(bgp_default_trace_options, $4, $3, $2, bgp_trace_types);
			}
		| T_GROUP T_TYPE bgp_linktype T_PEERAS as bgp_proto_option bgp_interface
			{
			    /* Allocate a Group structure */
			    bgp = bgp_conf_group_alloc();

			    /* Set the type and AS */
			    bgp->bgpg_type = $3;
			    bgp->bgpg_peer_as = $5;

			    /* Point at this configuration information */
			    bcp = &bgp->bgpg_conf;

			    /* Inherit global trace flags */
			    bgp->bgpg_trace_options = trace_alloc(bgp_default_trace_options);

			    /* Set the protocol for routing peers */
			    bgp->bgpg_proto = $6;

			    /* Set the interface policy */
			    bgp->bgpg_ifap_policy = $7;
			}
		bgp_peer_options
			{
			    /* Add this group */
			    bgp = bgp_conf_group_add(bgp, parse_error);
			    if (!bgp) {
				PARSE_ERROR;
			    }
			}
		'{' bgp_peer_stmts '}'
			{
			    /* Check group */
			    if (!bgp_conf_group_check(bgp, parse_error)) {
				PARSE_ERROR;
			    }
			}
		;

bgp_peer_options
		: /* Empty */
		| bgp_peer_options bgp_peer_option
		;

bgp_peer_stmts	: /* Empty */
		| bgp_peer_stmts bgp_peer_stmt L_EOS
		| bgp_peer_stmts error L_EOS
			{
				yyerrok;
			}
		;

bgp_peer_stmt	: T_NEIGHBOR
    			{
			    /* Allocate this peer */
			    bnp = bgp_conf_peer_alloc(bgp);

			    /* Point at this configuration information */
			    bcp = &bnp->bgp_conf;
			}
		host bgp_peer_options
			{
			    /* Set peer address */
			    bnp->bgp_addr = $3;

			    bnp = bgp_conf_peer_add(bgp, bnp, parse_error);
			    if (!bnp) {
				PARSE_ERROR;
			    }
			}
		| T_ALLOW
			{
			    parse_contig_masks = FALSE;
			}
			'{' bgp_allow_list '}'
			{
			    parse_contig_masks = TRUE;

			    bgp->bgpg_allow = adv_destmask_finish($4);
			}
		;

bgp_peer_option	: T_METRICOUT metric
			{
			    if (parse_metric_check(RTPROTO_BGP, &$2)) {
				PARSE_ERROR;
			    }
			    BIT_SET(bcp->bgpc_options, BGPO_METRIC_OUT);
			    bcp->bgpc_metric_out = $2.metric;
			}
		| T_LOCALAS as
			{
			    BIT_SET(bcp->bgpc_options, BGPO_LOCAL_AS);
			    bcp->bgpc_local_as = $2;
			    aslocal_set($2, 0);
			}
		| T_NOGENDEFAULT
			{
			    BIT_SET(bcp->bgpc_options, BGPO_NOGENDEFAULT);
			}
		| T_GATEWAY gateway_inet
			{
			    if (bcp->bgpc_gateway) {
				/* Free the old one */
				sockfree(bcp->bgpc_gateway);
			    }
			    BIT_SET(bcp->bgpc_options, BGPO_GATEWAY);
			    bcp->bgpc_gateway = sockdup($2->gw_addr);
			    gw_freelist(*parse_gwlist);
			    *parse_gwlist = parse_gwp = (gw_entry *) 0;
			}
		| T_PREFERENCE preference
			{
			    BIT_SET(bcp->bgpc_options, BGPO_PREFERENCE);
			    bcp->bgpc_preference = $2;
			}
		| T_PREFERENCE2 preference
			{
			    BIT_SET(bcp->bgpc_options, BGPO_PREFERENCE2);
			    bcp->bgpc_preference2 = $2;
			}
		| T_LCLADDR interface_local
			{
			    if (bcp->bgpc_lcladdr) {
				/* Free the old one */
				ifae_free(bcp->bgpc_lcladdr);
			    }
			    BIT_SET(bcp->bgpc_options, BGPO_LCLADDR);
			    bcp->bgpc_lcladdr = $2;
			}
		| T_HOLDTIME time
			{
			    if (parse_limit_check("hold time",
						  (u_int) $2,
						  BGP_LIMIT_HOLDTIME)) {
				PARSE_ERROR;
			    }
			    BIT_SET(bcp->bgpc_options, BGPO_HOLDTIME);
			    bcp->bgpc_holdtime_out = $2;
			}
		| T_TRACEOPTIONS trace_file_option trace_control_option bgp_trace_options_none
			{
			    trace_store(bcp->bgpc_trace_options, $4, $3, $2, bgp_trace_types);
			}
		| T_VERSION L_NUMBER
			{
			    if (!BGP_KNOWN_VERSION($2)) {
				(void) sprintf(parse_error, "unsupported BGP version: %d",
					       $2);
				PARSE_ERROR;
			    }
			    BIT_SET(bcp->bgpc_options, BGPO_VERSION);
			    bcp->bgpc_conf_version = $2;
			}
		| T_PASSIVE
			{
			    BIT_SET(bcp->bgpc_options, BGPO_PASSIVE);
			}
		| T_KEEP T_ALL
			{
			    BIT_SET(bcp->bgpc_options, BGPO_KEEPALL);
			}
		| T_KEEP T_NONE
			{
			    BIT_SET(bcp->bgpc_options, BGPO_KEEPNONE);
			}
		| T_ANALRETENTIVE
			{
			    BIT_SET(bcp->bgpc_options, BGPO_ANALRETENTIVE);
			}
		| T_KEEPALIVESALWAYS
			{
			    BIT_SET(bcp->bgpc_options, BGPO_KEEPALIVESALWAYS);
			}
		| T_NOAGGRID
			{
			    BIT_SET(bcp->bgpc_options, BGPO_NOAGGRID);
			}
		| T_NOAUTHCHECK
			{
			    BIT_SET(bcp->bgpc_options, BGPO_NOAUTHCHECK);
			}
		| T_SETPREF preference
			{
			    BIT_SET(bcp->bgpc_options, BGPO_SETPREF);
			    bcp->bgpc_setpref = $2;
			}
		| T_SENDBUF bgp_kbufsize
			{
			    bcp->bgpc_send_bufsize = $2;
			}
		| T_RECVBUF bgp_kbufsize
			{
			    bcp->bgpc_recv_bufsize = $2;
			}
		| T_INDELAY time
			{
			    bcp->bgpc_rti_time = $2;
			}
		| T_OUTDELAY time
			{
			    bcp->bgpc_rto_time = $2;
			}
		| T_TTL inet_ttl
			{
			    BIT_SET(bcp->bgpc_options, BGPO_TTL);
			    bcp->bgpc_ttl = $2;
			}
		| T_NOV4ASLOOP
			{
			    BIT_SET(bcp->bgpc_options, BGPO_NOV4ASLOOP);
			}
		| T_V3ASLOOPOKAY
			{
			    BIT_SET(bcp->bgpc_options, BGPO_V3ASLOOPOKAY);
			}
		| T_LOGUPDOWN
			{
			    BIT_SET(bcp->bgpc_options, BGPO_LOGUPDOWN);
			}
		;

bgp_kbufsize	: number
			{
			    if (parse_limit_check("kernel buffer size",
						  (u_int) $1,
						  BGP_LIMIT_KBUF)) {
				PARSE_ERROR;
			    }
			    $$ = $1;
			}
		;

bgp_linktype	: T_INTERNAL
			{
			    $$ = BGPG_INTERNAL;
			}
		| T_EXTERNAL
			{
			    $$ = BGPG_EXTERNAL;
			}
		| T_IGP
			{
			    $$ = BGPG_INTERNAL_IGP;
			}
		| T_ROUTING
			{
			    $$ = BGPG_INTERNAL_RT;
			}
		| T_TEST
			{
			    $$ = BGPG_TEST;
			}
		;

bgp_trace_options_none
		: T_NONE
			{
			    $$ = (flag_t) 0;
			}
		| bgp_trace_options
			{
			    $$ = $1;
			}
		| bgp_trace_options T_EXCEPT bgp_trace_options
			{
			    $$ = $1 & ~$3;
			}
    		;

bgp_trace_options
		: bgp_trace_option
			{
			    $$ = $1;
			}
		| bgp_trace_options bgp_trace_option
			{
			    $$ = $1 | $2;
			}
		;

bgp_proto_option
		: /* Empty */
			{
			    $$ = (proto_t) 0;
			}
		| T_PROTO bgp_proto
			{
			    $$ = $2;
			}
		;

bgp_proto
		: T_NOP_PROTO
			{
			    assert(FALSE);
			}
@BEGIN:	PROTO_RIP
		| T_RIP
			{
			    $$ = RTPROTO_RIP;
			}
@END:	PROTO_RIP
@BEGIN:	PROTO_HELLO
		| T_HELLO
			{
			    $$ = RTPROTO_HELLO;
			}
@END:	PROTO_HELLO
@BEGIN:	PROTO_OSPF
		| T_OSPF
			{
			    $$ = RTPROTO_OSPF;
			}
@END:	PROTO_OSPF
@BEGIN:	PROTO_ISIS
		| T_ISIS
			{
			    $$ = RTPROTO_ISIS;
			}
@END:	PROTO_ISIS
@BEGIN:	PROTO_SLSP
		| T_SLSP
			{
			    $$ = RTPROTO_SLSP;
			}
@END:	PROTO_SLSP
		;

bgp_interface	: /* Empty */
			{
			    $$ = (adv_entry *) 0;
			}
		| T_INTERFACE interface_all_list
			{
			    parse_adv_propagate_config($2, (config_list *) 0, RTPROTO_BGP);

			    $$ = $2;
			}
		;

bgp_trace_option
		: trace_option
		| T_ASPATH
			{
			    $$ = TR_BGP_ASPATH;
			}
    		| trace_option_detail trace_option_sendrecv bgp_trace_option_index
			{
			    $$ = trace_parse_packet($1, $2, $3);
			}
		;

bgp_trace_option_index
		: T_PACKETS
			{
			    $$ = TR_BGP_INDEX_PACKETS;
			}
		| T_OPEN
			{
			    $$ = TR_BGP_INDEX_OPEN;
			}
		| T_UPDATE
			{
			    $$ = TR_BGP_INDEX_UPDATE;
			}
		| T_KEEPALIVE
			{
			    $$ = TR_BGP_INDEX_KEEPALIVE;
			}
		;

bgp_prop_init
		: T_BGP
			{
			    $$ = parse_proto = RTPROTO_BGP;
			    parse_gwlist = (gw_entry **) 0;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s PROTO: %s",
				      parse_where(),
				      gd_lower(trace_state(rt_proto_bits, $$))));
			}
		;


bgp_allow_list	: /* Empty */
			{
			    $$ = bgp->bgpg_allow;
			}
		| bgp_allow_list bgp_allow L_EOS
			{
			    $$ = adv_alloc(ADVFT_DM, (proto_t) 0);
			    $$->adv_dm = $2;
			    $$ = adv_destmask_insert(parse_error, $1, $$);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		| bgp_allow_list error L_EOS
			{
			    yyerrok;
			}
		;
		
	
/* Destination and mask pair used for control lists */
bgp_allow	: all_mask_inet
		| host_mask_inet
		| network_mask_inet
		;

@END:	PROTO_BGP

/*  */

@BEGIN:	PROTO_ICMP

icmp_statement	: T_ICMP
			{
			    icmp_trace_options = trace_set_global(icmp_trace_types,
								  (flag_t) 0);
			}
		'{' icmp_group_stmts '}'
		;

icmp_group_stmts
		: /* Empty */
		| icmp_group_stmts icmp_group_stmt L_EOS
		| icmp_group_stmts error L_EOS
			{
			    yyerrok;
			}
		;


icmp_group_stmt
		: T_TRACEOPTIONS trace_file_option trace_control_option icmp_trace_options_none
			{
			    trace_store(icmp_trace_options, $4, $3, $2, icmp_trace_types);
			}
		;

icmp_trace_options_none
		: T_NONE
			{
			    $$ = (flag_t) 0;
			}
		| icmp_trace_options
			{
			    $$ = $1;
			}
		| icmp_trace_options T_EXCEPT icmp_trace_options
			{
			    $$ = $1 & ~$3;
			}
    		;

icmp_trace_options
		: icmp_trace_option
			{
			    $$ = $1;
			}
		| icmp_trace_options icmp_trace_option
			{
			    $$ = $1 | $2;
			}
		;

icmp_trace_option
		: trace_option
    		| trace_option_detail trace_option_sendrecv icmp_trace_option_index
			{
			    $$ = trace_parse_packet($1, $2, $3);
			}
		;

icmp_trace_option_index
		: T_PACKETS
			{
			    $$ = TR_ICMP_INDEX_PACKETS;
			}
		| T_REDIRECT
			{
			    $$ = TR_ICMP_INDEX_REDIRECT;
			}
		| T_ROUTERDISCOVERY
			{
			    $$ = TR_ICMP_INDEX_ROUTER;
			}
		| T_INFO
			{
			    $$ = TR_ICMP_INDEX_INFO;
			}
		| T_ERROR
			{
			    $$ = TR_ICMP_INDEX_ERROR;
			}
    		;


@END:	PROTO_ICMP

/*  */

redirect_statement
		: T_REDIRECT
			{
#if	defined(PROTO_ICMP) || defined(KRT_RT_SOCK)
			    PROTO_SEEN(RTPROTO_REDIRECT);

			    parse_gwlist = &redirect_gw_list;

			    redirect_trace_options = trace_set_global(redirect_trace_types,
								      (flag_t) 0);
#endif	/* defined(PROTO_ICMP) || defined(KRT_RT_SOCK) */
			}
		onoff_option redirect_group
			{
#if	defined(PROTO_ICMP) || defined(KRT_RT_SOCK)
			    switch ($3) {
			    case T_ON:
				/* Enabled by default */
				break;

			    case T_OFF:
				redirect_disable(RTPROTO_REDIRECT);
				break;
			    }

			    parse_proto = (proto_t) 0;
			    parse_gwlist = (gw_entry **) 0;
#endif	/* defined(PROTO_ICMP) || defined(KRT_RT_SOCK) */
			}
		;

redirect_group	: /* Empty */
		| '{' redirect_group_stmts '}'
		;

redirect_group_stmts
		: /* Empty */
		| redirect_group_stmts redirect_group_stmt L_EOS
		| redirect_group_stmts error L_EOS
			{
			    yyerrok;
			}
		;

redirect_group_stmt	: T_PREFERENCE preference
			{
#if	defined(PROTO_ICMP) || defined(KRT_RT_SOCK)
			    redirect_preference = $2;
#endif	/* defined(PROTO_ICMP) || defined(KRT_RT_SOCK) */
			}
		| T_INTERFACE interface_all_list redirect_interface_options
			{
#if	defined(PROTO_ICMP) || defined(KRT_RT_SOCK)
			    config_list *list = config_list_alloc($3, 0);

			    parse_adv_propagate_config($2, list, RTPROTO_REDIRECT);

			    if (parse_adv_append(&redirect_int_policy, $2)) {
				PARSE_ERROR;
			    }

			    config_list_free(list);
#endif	/* defined(PROTO_ICMP) || defined(KRT_RT_SOCK) */
			}
		| T_TRUSTEDGATEWAYS gateway_list
			{
#if	defined(PROTO_ICMP) || defined(KRT_RT_SOCK)
			    redirect_n_trusted += parse_gw_flag($2, RTPROTO_REDIRECT, GWF_TRUSTED);
			    if (!redirect_n_trusted) {
				PARSE_ERROR;
			    }
#endif	/* defined(PROTO_ICMP) || defined(KRT_RT_SOCK) */
			}
		| T_TRACEOPTIONS trace_file_option trace_control_option redirect_trace_options_none
			{
			    trace_store(redirect_trace_options, $4, $3, $2, redirect_trace_types);
			}
		;

redirect_interface_options
		: redirect_interface_option
		| redirect_interface_options redirect_interface_option
			{
			    $$ = config_append($1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		;

redirect_interface_option
		: T_REDIRECTS
			{
#if	defined(PROTO_ICMP) || defined(KRT_RT_SOCK)
			    $$ = config_alloc(REDIRECT_CONFIG_IN, GS2A(TRUE));
#endif	/* defined(PROTO_ICMP) || defined(KRT_RT_SOCK) */
			}
		| T_NOREDIRECTS
			{
#if	defined(PROTO_ICMP) || defined(KRT_RT_SOCK)
			    $$ = config_alloc(REDIRECT_CONFIG_IN, GS2A(FALSE));
#endif	/* defined(PROTO_ICMP) || defined(KRT_RT_SOCK) */
			}
		;

redirect_trace_options_none
		: T_NONE
			{
			    $$ = (flag_t) 0;
			}
		| redirect_trace_options
			{
			    $$ = $1;
			}
		| redirect_trace_options T_EXCEPT redirect_trace_options
			{
			    $$ = $1 & ~$3;
			}
    		;

redirect_trace_options
		: redirect_trace_option
			{
			    $$ = $1;
			}
		| redirect_trace_options redirect_trace_option
			{
			    $$ = $1 | $2;
			}
		;

redirect_trace_option
		: trace_option
		;

/*  */

@BEGIN:	PROTO_IGMP

igmp_statement	: T_IGMP
			{
			    PROTO_SEEN(RTPROTO_IGMP);

			    igmp_trace_options =
				trace_set_global(igmp_trace_types, (flag_t) 0);
			}
    		onoff_option igmp_group
			{
			    switch ($3) {
			    case T_OFF:
				BIT_RESET(igmp_config_status, IGMP_ENABLED);

				break;

			    case T_ON:
				BIT_SET(igmp_config_status, IGMP_ENABLED);
				break;
			    }
			}
		;

igmp_group	: /* Empty */
		| '{' igmp_group_stmts '}'
		;

igmp_group_stmts	: /* Empty */
		| igmp_group_stmts igmp_group_stmt L_EOS
		| igmp_group_stmts error L_EOS
			{
			    yyerrok;
			}
		;

igmp_group_stmt	: T_INTERFACE interface_all_list igmp_interface_options
			{
			    config_list *list = config_list_alloc($3, 0);

			    parse_adv_propagate_config($2, list, (proto_t) 0);

			    if (parse_adv_append(&igmp_int_policy, $2)) {
				PARSE_ERROR;
			    }

			    config_list_free(list);
			}
		| T_TRACEOPTIONS trace_file_option trace_control_option igmp_trace_options_none
			{
			    trace_store(igmp_trace_options, $4, $3, $2, igmp_trace_types);
			}
		| T_QUERYINTERVAL time
			{
			    if (parse_limit_check("query-interval",
						  (u_int) $2,
						  IGMP_LIMIT_QUERYINTERVAL)) {
				PARSE_ERROR;
			    }
			    igmp_default_queryinterval = $2;
			}
		| T_TIMEOUTINTERVAL time
			{
			    if (parse_limit_check("timeout-interval",
						  (u_int) $2,
						  IGMP_LIMIT_TIMEOUTINTERVAL)) {
				PARSE_ERROR;
			    }
			    igmp_default_timeoutinterval = $2;
			}
		;

igmp_interface_options
		: igmp_interface_option
		| igmp_interface_options igmp_interface_option
			{
			    $$ = config_append($1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		;

igmp_interface_option
		: T_ENABLE
			{
			    $$ = config_alloc(IGMP_CONFIG_ENABLE, (void_t) TRUE);
			}
		| T_DISABLE
			{
			    $$ = config_alloc(IGMP_CONFIG_DISABLE, (void_t) TRUE);
			}
		;

igmp_trace_options_none
		: T_NONE
			{
			    $$ = (flag_t) 0;
			}
		| igmp_trace_options
			{
			    $$ = $1;
			}
		| igmp_trace_options T_EXCEPT igmp_trace_options
			{
			    $$ = $1 & ~$3;
			}
    		;

igmp_trace_options
		: igmp_trace_option
			{
			    $$ = $1;
			}
		| igmp_trace_options igmp_trace_option
			{
			    $$ = $1 | $2;
			}
		;

igmp_trace_option
		: trace_option
    		| trace_option_detail trace_option_sendrecv igmp_trace_option_index
			{
			    $$ = trace_parse_packet($1, $2, $3);
			}
		;

igmp_trace_option_index
		: T_PACKETS
			{
			    $$ = TR_IGMP_INDEX_PACKETS;
			}
		| T_QUERY
			{
			    $$ = TR_IGMP_INDEX_QUERY;
			}
		| T_REPORT
			{
			    $$ = TR_IGMP_INDEX_REPORT;
			}
		| T_LEAVE
			{
			    $$ = TR_IGMP_INDEX_LEAVE;
			}
		| T_MTRACE
			{
			    $$ = TR_IGMP_INDEX_MTRACE;
			}
    		;

@END:	PROTO_IGMP

@BEGIN:	PROTO_DVMRP

dvmrp_statement : T_DVMRP
			{
			    PROTO_SEEN(RTPROTO_DVMRP);

			    dvmrp_trace_options = trace_set_global(dvmrp_trace_types,
								   (flag_t) 0);
                        }
		onoff_option dvmrp_group
			{

			    switch ($3) {
			    case T_OFF:
				BIT_RESET(dvmrp_config_status, IGMP_ENABLED);
				break;
				
			    case T_ON:
				/* XXX - Check validity of configuration */
				BIT_SET(dvmrp_config_status, IGMP_ENABLED);
			    }

			    parse_proto = (proto_t) 0;
			}
		;
    
dvmrp_group	: /* Empty */
                | '{' dvmrp_group_stmts '}'
		;

dvmrp_group_stmts	: /* Empty */
		| dvmrp_group_stmts dvmrp_group_stmt L_EOS
		| dvmrp_group_stmts error L_EOS
			{
				yyerrok;
			}
		;

dvmrp_group_stmt
		: T_INTERFACE interface_all_list dvmrp_interface_options
			{
			    config_list *list = config_list_alloc($3, 0);

			    parse_adv_propagate_config($2, list, (proto_t) 0);

			    if (parse_adv_append(&dvmrp_int_policy, $2)) {
				PARSE_ERROR;
			    }

			    config_list_free(list);
			}
		| T_TUNNEL host_inet T_LCLADDR interface_local dvmrp_interface_options
			{
			    if (dvmrp_parse_tunnel($2, $4, $5, parse_error)) {
				PARSE_ERROR;
			    }
			    /* Sorta gross */
			    config_list_free(config_list_alloc($5, 0));
			}
		| T_TRACEOPTIONS trace_file_option trace_control_option dvmrp_trace_options_none
			{
			    trace_store(dvmrp_trace_options, $4, $3, $2, dvmrp_trace_types);
			}
		;

dvmrp_interface_options
		: dvmrp_interface_option
		| dvmrp_interface_options dvmrp_interface_option
			{
			    $$ = config_append($1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		;

dvmrp_interface_option
		: T_ENABLE
			{
			    $$ = config_alloc(DVMRP_CONFIG_ENABLE, (void_t) TRUE);
			}
		| T_DISABLE
			{
			    $$ = config_alloc(DVMRP_CONFIG_DISABLE, (void_t) TRUE);
			}
		| T_METRIC metric
			{
			    if (parse_metric_check(RTPROTO_DVMRP, &$2)) {
				PARSE_ERROR;
			    }
			    $$ = config_alloc(DVMRP_CONFIG_METRIC, GS2A($2.metric));
			}
		| T_THRESHOLD number
			{
			    if (parse_limit_check("dvmrp threshold",
						  (u_int) $2,
						  DVMRP_LIMIT_THRESHOLD)) {
				PARSE_ERROR;
			    }
			    $$ = config_alloc(DVMRP_CONFIG_THRESHOLD, GS2A($2));
			}
		| T_RATELIMIT number
			{
			    if (parse_limit_check("dvmrp rate limit",
						  (u_int) $2,
						  DVMRP_LIMIT_RATE)) {
				PARSE_ERROR;
			    }
			    $$ = config_alloc(DVMRP_CONFIG_RATELIMIT, GS2A($2));
			}
		;
dvmrp_trace_options_none
		: T_NONE
			{
			    $$ = (flag_t) 0;
			}
		| dvmrp_trace_options
			{
			    $$ = $1;
			}
		| dvmrp_trace_options T_EXCEPT dvmrp_trace_options
			{
			    $$ = $1 & ~$3;
			}
    		;

dvmrp_trace_options
		: dvmrp_trace_option
			{
			    $$ = $1;
			}
		| dvmrp_trace_options dvmrp_trace_option
			{
			    $$ = $1 | $2;
			}
		;

dvmrp_trace_option
		: trace_option
    		| trace_option_detail trace_option_sendrecv dvmrp_trace_option_index
			{
			    $$ = trace_parse_packet($1, $2, $3);
			}
		;

dvmrp_trace_option_index
		: T_PACKETS
			{
			    $$ = TR_IGMP_INDEX_PACKETS;
			}
		| T_QUERY
			{
			    $$ = TR_IGMP_INDEX_QUERY;
			}
		| T_REPORT
			{
			    $$ = TR_IGMP_INDEX_REPORT;
			}
		| T_MTRACE
			{
			    $$ = TR_IGMP_INDEX_MTRACE;
			}
    		;



@END:	PROTO_DVMRP


/*  */

@BEGIN:	PROTO_PIM

pim_statement	: T_PIM
			{
			    PROTO_SEEN(RTPROTO_PIM);

			    pim_trace_options =
				trace_set_global(pim_trace_types, (flag_t) 0);
			}
    		onoff_option pim_group
			{
			    switch ($3) {
			    case T_OFF:
				BIT_RESET(pim_config_status, PIM_ENABLED);

				break;

			    case T_ON:
				BIT_SET(pim_config_status, PIM_ENABLED);
				break;
			    }
			}
		;

pim_group	: /* Empty */
		| '{' pim_group_stmts '}'
		;

pim_group_stmts	: /* Empty */
		| pim_group_stmts pim_group_stmt L_EOS
		| pim_group_stmts error L_EOS
			{
			    yyerrok;
			}
		;

pim_group_stmt	: T_INTERFACE interface_all_list pim_interface_options
			{
			    config_list *list = config_list_alloc($3, 0);

			    parse_adv_propagate_config($2, list, (proto_t) 0);

			    if (parse_adv_append(&pim_int_policy, $2)) {
				PARSE_ERROR;
			    }

			    config_list_free(list);
			}
		| T_TRACEOPTIONS trace_file_option trace_control_option pim_trace_options_none
			{
			    trace_store(pim_trace_options, $4, $3, $2, pim_trace_types);
			}
		| T_QUERYINTERVAL time
			{
			    if (parse_limit_check("query-interval",
						  (u_int) $2,
						  PIM_LIMIT_QUERYINTERVAL)) {
				PARSE_ERROR;
			    }
			    pim_default_queryinterval = $2;
			    pim_default_routertimeout = 3 * $2;
			}
		| T_ROUTERTIMEOUT time
			{
			    if (parse_limit_check("router-timeout",
						  (u_int) $2,
						  PIM_LIMIT_ROUTERTIMEOUT)) {
				PARSE_ERROR;
			    }
			    pim_default_routertimeout = $2;
			}
		| T_PRUNETIMEOUT time
			{
			    if (parse_limit_check("prune-timeout",
						  (u_int) $2,
						  PIM_LIMIT_PRUNETIMEOUT)) {
				PARSE_ERROR;
			    }
			    pim_default_prunetimeout = $2;
			}
		| T_INACTIVITYTIMEOUT time
			{
			    if (parse_limit_check("inactivity-timeout",
						  (u_int) $2,
						  PIM_LIMIT_INACTIVITYTIMEOUT)) {
				PARSE_ERROR;
			    }
			    pim_default_inactivitytimeout = $2;
			}
		| T_GRAFTACKTIMEOUT time
			{
			    if (parse_limit_check("graftack-timeout",
						  (u_int) $2,
						  PIM_LIMIT_GRAFTACKTIMEOUT)) {
				PARSE_ERROR;
			    }
			    pim_default_graftacktimeout = $2;
			}
		| T_PREFERENCE '{' pim_proto_statements '}' L_EOS
			{
			}
		;

pim_proto_statements
		: /* Empty */
    		| pim_proto_statements pim_proto_statement L_EOS
    		| pim_proto_statements error L_EOS
			{
			    yyerrok;
			}
    		;

pim_proto_statement
    		: T_DIRECT preference
			{
			    pim_set_pref(RTPROTO_DIRECT, $2);
			}
    		| T_KERNEL preference
			{
			    pim_set_pref(RTPROTO_KERNEL, $2);
			}
    		| T_STATIC preference
			{
			    pim_set_pref(RTPROTO_STATIC, $2);
			}
@BEGIN: PROTO_OSPF
    		| T_OSPF preference
			{
			    pim_set_pref(RTPROTO_OSPF, $2);
			}
    		| T_OSPFASE preference
			{
			    pim_set_pref(RTPROTO_OSPF_ASE, $2);
			}
@END: PROTO_OSPF
@BEGIN: PROTO_RIP
    		| T_RIP preference
			{
			    pim_set_pref(RTPROTO_RIP, $2);
			}
@END: PROTO_RIP
@BEGIN: PROTO_HELLO
    		| T_HELLO preference
			{
			    pim_set_pref(RTPROTO_HELLO, $2);
			}
@END: PROTO_HELLO
@BEGIN: PROTO_BGP
    		| T_BGP preference
			{
			    pim_set_pref(RTPROTO_BGP, $2);
			}
@END: PROTO_BGP
@BEGIN: PROTO_EGP
    		| T_EGP preference
			{
			    pim_set_pref(RTPROTO_EGP, $2);
			}
@END: PROTO_EGP
@BEGIN: PROTO_IDRP
    		| T_IDRP preference
			{
			    pim_set_pref(RTPROTO_IDRP, $2);
			}
@END: PROTO_IDRP
@BEGIN: PROTO_ISIS
    		| T_ISIS preference
			{
			    pim_set_pref(RTPROTO_ISIS, $2);
			}
@END: PROTO_ISIS
@BEGIN: PROTO_SLSP
    		| T_SLSP preference
			{
			    pim_set_pref(RTPROTO_SLSP, $2);
			}
@END: PROTO_SLSP
		;

pim_interface_options
		: pim_interface_option
		| pim_interface_options pim_interface_option
			{
			    $$ = config_append($1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		;

pim_interface_option
		: T_ENABLE
			{
			    $$ = config_alloc(PIM_CONFIG_ENABLE, (void_t) TRUE);
			}
		| T_DISABLE
			{
			    $$ = config_alloc(PIM_CONFIG_DISABLE, (void_t) TRUE);
			}
		| T_MODE T_DENSE
			{
			    $$ = config_alloc(PIM_CONFIG_MODE, (void_t) FALSE);
			}
		| T_MODE T_SPARSE
			{
			    $$ = config_alloc(PIM_CONFIG_MODE, (void_t) TRUE);
			}
		;

pim_trace_options_none
		: T_NONE
			{
			    $$ = (flag_t) 0;
			}
		| pim_trace_options
			{
			    $$ = $1;
			}
		| pim_trace_options T_EXCEPT pim_trace_options
			{
			    $$ = $1 & ~$3;
			}
    		;

pim_trace_options
		: pim_trace_option
			{
			    $$ = $1;
			}
		| pim_trace_options pim_trace_option
			{
			    $$ = $1 | $2;
			}
		;

pim_trace_option
		: trace_option
    		| trace_option_detail trace_option_sendrecv pim_trace_option_index
			{
			    $$ = trace_parse_packet($1, $2, $3);
			}
		;

pim_trace_option_index
		: T_PACKETS
			{
			    $$ = TR_PIM_INDEX_PACKETS;
			}
		| T_QUERY
			{
			    $$ = TR_PIM_INDEX_QUERY;
			}
		| T_REGISTER
			{
			    $$ = TR_PIM_INDEX_REGISTER;
			}
		| T_RP
			{
			    $$ = TR_PIM_INDEX_RP;
			}
		| T_JOIN
			{
			    $$ = TR_PIM_INDEX_JOIN;
			}
		| T_PRUNE
			{
			    $$ = TR_PIM_INDEX_PRUNE;
			}
		| T_GRAFT
			{
			    $$ = TR_PIM_INDEX_GRAFT;
			}
		| T_ASSERT
			{
			    $$ = TR_PIM_INDEX_ASSERT;
			}
    		;

@END:	PROTO_PIM


/*  */    

@BEGIN:	PROTO_SNMP

snmp_statement	: T_SNMP
		        {
			    PROTO_SEEN(RTPROTO_SNMP);

			    snmp_trace_options = trace_set_global(snmp_trace_types,
								  (flag_t) 0);
			}
		onoff_option snmp_group
			{
			    /* XXX - trace options */

			    switch ($3) {
			    case T_ON:
				doing_snmp = TRUE;
				break;

			    case T_OFF:
				doing_snmp = FALSE;
				break;
			    }

			    parse_proto = (proto_t) 0;
			}
		;

snmp_group	: /* Empty */
		| '{' snmp_group_stmts '}'
		;

snmp_group_stmts
		: /* Empty */
		| snmp_group_stmts snmp_group_stmt L_EOS
		| snmp_group_stmts error L_EOS
			{
				yyerrok;
			}
		;

snmp_group_stmt
    		: T_PREFERENCE preference
			{
			    snmp_preference = $2;
			}
    		| T_TRACEOPTIONS trace_file_option trace_control_option snmp_trace_options_none
			{
			    trace_store(snmp_trace_options, $4, $3, $2, snmp_trace_types);
			}
		| T_PORT port
			{
			    snmp_port = $2;
			}
		| T_DEBUG
			{
			    snmp_debug = TRUE;
			}
		;

snmp_trace_options_none
		: T_NONE
			{
			    $$ = (flag_t) 0;
			}
		| snmp_trace_options
			{
			    $$ = $1;
			}
		| snmp_trace_options T_EXCEPT snmp_trace_options
			{
			    $$ = $1 & ~$3;
			}
    		;

snmp_trace_options
		: snmp_trace_option
			{
			    $$ = $1;
			}
		| snmp_trace_options snmp_trace_option
			{
			    $$ = $1 | $2;
			}
		;

snmp_trace_option
		: trace_option
		| T_RECEIVE
			{
			    $$ = TR_SNMP_RECV;
			}
		| T_REGISTER
			{
			    $$ = TR_SNMP_REGISTER;
			}
		| T_RESOLVE
			{
			    $$ = TR_SNMP_RESOLVE;
			}
		| T_TRAP
			{
			    $$ = TR_SNMP_TRAP;
			}
		;

@END:	PROTO_SNMP
@BEGIN:	NOT PROTO_SNMP
snmp_statement	: T_SNMP T_OFF
			{
			}
		;
@END:	NOT PROTO_SNMP

/*  */

route_order	: /* Empty */
			{
			    if (parse_new_state(PS_ROUTE)) {
				PARSE_ERROR;
			    }
			}
		;

route_statement : T_STATIC
			{
			    /* Need to set this for static routes, not used for interface routes */
			    parse_proto = RTPROTO_STATIC;
			    parse_gwlist = &rt_gw_list;
			    rt_open(rt_task);
			}
		'{' route_stmts '}'
			{
			    rt_close(rt_task, (gw_entry *) 0, 0, NULL);
			    parse_proto = (proto_t) 0;
			    parse_gwlist = (gw_entry **) 0;
			}
		;

route_stmts	: route_stmt L_EOS
		| route_stmts route_stmt L_EOS
		| error L_EOS
			{
				yyerrok;
			}
		;

route_stmt	: route_dest T_INTERFACE interface_all preference_option rts_options
			{
			    /* Route to an interface */

			    if (rt_parse_route($1.dm_dest,
					       $1.dm_mask,
					       (adv_entry *) 0,
					       $3,
					       PARSE_METRIC_ISSET(&$4) ? (pref_t) $4.metric : RTPREF_STATIC,
					       $5,
					       parse_error)) {
				PARSE_ERROR;
			    }

			    sockfree($1.dm_dest);
			}
@BEGIN:	PROTO_ASPATHS
		| route_dest T_GATEWAY gateway_list interface_list_option route_aspath preference_option rts_options
			{
			    /* Route to a gateway */

			    if (rt_parse_route_aspath($1.dm_dest,
						      $1.dm_mask,
						      $3,
						      $4,
						      PARSE_METRIC_ISSET(&$6) ? (pref_t) $6.metric : RTPREF_STATIC,
						      $7 | RTS_GATEWAY,
						      $5,
						      parse_error)) {
				PARSE_ERROR;
			    }

			    sockfree($1.dm_dest);
			}
@END:	PROTO_ASPATHS
@BEGIN:	NOT PROTO_ASPATHS
		| route_dest T_GATEWAY gateway_list interface_list_option preference_option rts_options
			{
			    /* Route to a gateway */

			    if (rt_parse_route($1.dm_dest,
					       $1.dm_mask,
					       $3,
					       $4,
					       PARSE_METRIC_ISSET(&$5) ? (pref_t) $5.metric : RTPREF_STATIC,
					       $6 | RTS_GATEWAY,
					       parse_error)) {
				PARSE_ERROR;
			    }

			    sockfree($1.dm_dest);
			}
@END:	NOT PROTO_ASPATHS
		;

@BEGIN:	PROTO_ASPATHS
route_aspath	: /* Empty */
			{
			    $$ = (as_path *) 0;
			}
		| T_AS as
			{
			    $$ = aspath_create($2);
			}
		;
@END:	PROTO_ASPATHS

route_dest	: T_NOP_DM
			{
			    assert(FALSE);
			}
@BEGIN:	PROTO_INET
		| host_mask_inet
    		| network_mask_inet
    		| T_DEFAULT
			{
			    $$.dm_dest = sockdup(inet_addr_default);
			    $$.dm_mask = inet_mask_default;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s DEST: %A MASK: %A",
				      parse_where(),
				      $$.dm_dest,
				      $$.dm_mask));
			}
@END:	PROTO_INET
@BEGIN:	PROTO_ISO
		| host_mask_iso
    		| network_mask_iso
		| T_ISO T_DEFAULT
			{
			    $$.dm_dest = sockdup(iso_addr_default);
			    $$.dm_mask = iso_mask_default;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s DEST: %A MASK: %A",
				      parse_where(),
				      $$.dm_dest,
				      $$.dm_mask));
			}
@END:	PROTO_ISO
    		;

rts_options	: /* Empty */
			{
			    $$ = 0;
			}
		| rts_options rts_option
			{
			    $$ = $1 | $2;
			}
		;

rts_option	: T_RETAIN
			{
			    $$ = RTS_RETAIN;
			}
		| T_REJECT
			{
			    $$ = RTS_REJECT;
			}
		| T_BLACKHOLE
			{
			    $$ = RTS_BLACKHOLE;
			}
		| T_NOINSTALL
			{
			    $$ = RTS_NOTINSTALL;
			}
		;

/*  */

control_order	: /* Empty */
			{
			    if (parse_new_state(PS_CONTROL)) {
				PARSE_ERROR;
			    }
			}
		;
		
control_statement
		: T_NOP1
			{
			    assert(FALSE);
			}
@BEGIN:	AUTONOMOUS_SYSTEM
		| T_IMPORT T_PROTO control_exterior T_AS as import_option_inet L_EOS
			{
#if	defined(PROTO_EGP) || defined(PROTO_BGP)
			    adv_entry *adv;
			    pmet_t *pp = &$6.metric;

			    /*
			     *	Tack the list of destinations onto the end of the list
			     *	for neighbors with the specified AS.
			     */
			    adv = adv_alloc(ADVFT_AS, $3.proto);
			    adv->adv_as = $5;
			    adv->adv_list = $6.adv;
			    if (PARSE_METRIC_ISSET(pp)) {
				if (PARSE_METRIC_ISRESTRICT(pp)) {
				    BIT_SET(adv->adv_flag, ADVF_NO);
				} else {
				    BIT_SET(adv->adv_flag, ADVFOT_PREFERENCE);
				    adv->adv_result.res_preference = pp->metric;
				}
			    }

			    if (!parse_adv_as($3.import_list, adv)) {
				PARSE_ERROR;
			    }
#endif	/* defined(PROTO_EGP) || defined(PROTO_BGP) */
			}
@END:	AUTONOMOUS_SYSTEM
@BEGIN:	PROTO_BGP
		| T_IMPORT T_PROTO T_BGP aspath_match import_option_inet L_EOS
			{
			    adv_entry *adv;
			    pmet_t *pp = &$5.metric;

			    /*
			     *	Tack the list of destinations onto the end of the list
			     *	for neighbors with the specified AS.
			     */
			    adv = adv_alloc(ADVFT_ASPATH, RTPROTO_BGP);
			    adv->adv_aspath = $4;
			    adv->adv_list = $5.adv;
			    if (PARSE_METRIC_ISSET(pp)) {
				if (PARSE_METRIC_ISRESTRICT(pp)) {
				    BIT_SET(adv->adv_flag, ADVF_NO);
				} else {
				    BIT_SET(adv->adv_flag, ADVFOT_PREFERENCE);
				    adv->adv_result.res_preference = pp->metric;
				}
			    }

			    if (parse_adv_append(&bgp_import_aspath_list, adv)) {
				PARSE_ERROR;
			    }
			}
@END:	PROTO_BGP
		| T_IMPORT T_PROTO import_interior interface_gateway_list import_option_inet L_EOS
			{
			    /*
			     *	Append the dest_mask list to the end of the import list
			     *	for the specified protocol.
			     */
			    (void) parse_adv_propagate_preference($4, $3.proto, &$5.metric, $5.adv);

			    switch ($4->adv_flag & ADVF_TYPE) {
			    case ADVFT_GW:
				/* Gateway list */
			        {
				    adv_entry *adv = $4;
				    adv_entry *advn;

				    do {
					advn = adv->adv_next;
					adv->adv_next = NULL;
					/* Reset the type */
					adv->adv_flag = (adv->adv_flag & ~ADVF_TYPE) | ADVFT_ANY;
					if (parse_adv_append(&adv->adv_gwp->gw_import, adv)) {
					    PARSE_ERROR;
					}
				    } while ((adv = advn));
				}
				break;

			    case ADVFT_ANY:
				/* Global list */
				if (parse_adv_append($3.import_list, $4)) {
				    PARSE_ERROR;
				}
				break;

			    case ADVFT_IFN:
			    case ADVFT_IFAE:
				/* Interface list */
				if (parse_adv_append(&int_import[$3.proto], $4)) {
				    PARSE_ERROR;
				}
				break;

			    default:
				assert(FALSE);
			    }
			}
@BEGIN:	PROTO_OSPF
		| T_IMPORT T_PROTO T_OSPF_ASE tag_option import_option_inet L_EOS
			{
			    adv_entry *adv;
			    pmet_t *pp = &$5.metric;

			    /* Make sure this PS type is known */
			    adv_psfunc_add(RTPROTO_OSPF_ASE, &ospf_adv_psfunc);

			    /*
			     *	Append the dest_mask list to the end of the OSPF import list.
			     */
			    adv = adv_alloc(ADVFT_PS, RTPROTO_OSPF_ASE);
			    adv->adv_list = $5.adv;
			    adv->adv_ps = (caddr_t) adv;

			    /* Set Tag */
			    if (PARSE_METRIC_ISSET(&$4)) {
				BIT_SET(adv->adv_flag, ADVFOT_METRIC);
				BIT_SET(adv->adv_result.res_flag, OSPF_EXPORT_TAG);
				adv->adv_result.res_metric = $4.metric;
			    }

			    /* Set Preference */
			    if (PARSE_METRIC_ISSET(pp)) {
				if (PARSE_METRIC_ISRESTRICT(pp)) {
				    BIT_SET(adv->adv_flag, ADVF_NO);
				} else {
				    BIT_SET(adv->adv_flag, ADVFOT_PREFERENCE);
				    adv->adv_result.res_preference = pp->metric;
				}
			    }

			    if (parse_adv_append(&ospf.import_list, adv)) {
				PARSE_ERROR;
			    }
			}
@END:	PROTO_OSPF
@BEGIN:	PROTO_ISIS
		| T_IMPORT T_PROTO T_ISIS import_option_iso L_EOS
			{
			    adv_entry *adv;
			    pmet_t *pp = &$4.metric;

			    /*
			     *	Append the dest_mask list to the end of the ISIS import list.
			     */
			    adv = adv_alloc(ADVFT_ANY, RTPROTO_ISIS);
			    adv->adv_list = $4.adv;

			    /* Set Preference */
			    if (PARSE_METRIC_ISSET(pp)) {
				if (PARSE_METRIC_ISRESTRICT(pp)) {
				    BIT_SET(adv->adv_flag, ADVF_NO);
				} else {
				    BIT_SET(adv->adv_flag, ADVFOT_PREFERENCE);
				    adv->adv_result.res_preference = pp->metric;
				}
			    }

			    if (parse_adv_append(&isis_import_list_iso, adv)) {
				PARSE_ERROR;
			    }
			}
@BEGIN:	PROTO_INET
		| T_IMPORT T_PROTO T_ISIS T_IP import_option_iso L_EOS
			{
			    adv_entry *adv;
			    pmet_t *pp = &$5.metric;

			    /*
			     *	Append the dest_mask list to the end of the ISIS import list.
			     */
			    adv = adv_alloc(ADVFT_ANY, RTPROTO_ISIS);
			    adv->adv_list = $5.adv;

			    /* Set Preference */
			    if (PARSE_METRIC_ISSET(pp)) {
				if (PARSE_METRIC_ISRESTRICT(pp)) {
				    BIT_SET(adv->adv_flag, ADVF_NO);
				} else {
				    BIT_SET(adv->adv_flag, ADVFOT_PREFERENCE);
				    adv->adv_result.res_preference = pp->metric;
				}
			    }

			    if (parse_adv_append(&isis_import_list_ip, adv)) {
				PARSE_ERROR;
			    }
			}
@END:	PROTO_INET
@END:	PROTO_ISIS
@BEGIN:	AUTONOMOUS_SYSTEM
		| T_EXPORT T_PROTO control_exterior T_AS as prop_source_option_inet L_EOS
			{
#if	defined(PROTO_EGP) || defined(PROTO_BGP)
			    adv_entry *adv;
			    adv_entry *adv_prop = $6.adv;
			    pmet_t *mp = &$6.metric;

			    /*
			     *	Tack the list of destinations onto the end of the list
			     *	for neighbors with the specified AS.
			     */
			    adv = adv_alloc(ADVFT_AS, $3.proto);
			    adv->adv_as = $5;
			    adv->adv_list = adv_prop;
			    if (PARSE_METRIC_ISRESTRICT(mp)) {
				BIT_SET(adv->adv_flag, ADVF_NO);
			    } else if (PARSE_METRIC_ISSET(mp)) {
				BIT_SET(adv->adv_flag, ADVFOT_METRIC);
				adv->adv_result.res_metric = mp->metric;
			    }

			    if (!parse_adv_as($3.export_list, adv)) {
				PARSE_ERROR;
			    }
#endif	/* defined(PROTO_EGP) || defined(PROTO_BGP) */
			}
@END:	AUTONOMOUS_SYSTEM
		| T_EXPORT T_PROTO export_interior interface_gateway_list prop_source_option_inet L_EOS
			{
			    /*
			     *	Append the dest_mask list to the end of the export list
			     *	for the specified protocol.
			     */

			    (void) parse_adv_propagate_metric($4, $3.proto, &$5.metric, $5.adv);

			    switch ($4->adv_flag & ADVF_TYPE) {
			    case ADVFT_GW:
				/* Gateway list */
			        {
				    adv_entry *adv = $4;
				    adv_entry *advn;
				
				    do {
					advn = adv->adv_next;
					adv->adv_next = NULL;
					if (parse_adv_append(&adv->adv_gwp->gw_export, adv)) {
					    PARSE_ERROR;
					}
				    } while ((adv = advn));
				}
				break;

			    case ADVFT_ANY:
				/* Global list for the protocol */
				if (parse_adv_append($3.export_list, $4)) {
				    PARSE_ERROR;
				}
				break;

			    case ADVFT_IFN:
			    case ADVFT_IFAE:
				/* Interface list */
				if (parse_adv_append(&int_export[$3.proto], $4)) {
				    PARSE_ERROR;
				}
				break;

			    default:
				assert(FALSE);
			    }
			}
@BEGIN:	PROTO_OSPF
    		| T_EXPORT T_PROTO export_ospf_ase ospf_type_option tag_as_option prop_source_option_inet L_EOS
			{
			    adv_entry *adv;
			    adv_entry *adv_prop = $6.adv;
			    pmet_t *mp = &$6.metric;

			    /* If we export then we are a border router */
			    ospf.asbr = TRUE;

			    /* Make sure this PS type is known */
			    adv_psfunc_add(RTPROTO_OSPF_ASE, &ospf_adv_psfunc);

			    /*
			     *	Append the dest_mask list to the end of the export list
			     *	for the specified protocol.
			     */
			    adv = adv_alloc(ADVFT_PS, RTPROTO_OSPF_ASE);
			    adv->adv_ps = (caddr_t) adv;
			    adv->adv_list = adv_prop;

			    /* Metric */
			    if (PARSE_METRIC_ISRESTRICT(mp)) {
				BIT_SET(adv->adv_flag, ADVF_NO);
			    } else if (PARSE_METRIC_ISSET(mp)) {
				BIT_SET(adv->adv_flag, ADVFOT_METRIC);
				adv->adv_result.res_metric = mp->metric;
			    }

			    /* Type */
			    if (PARSE_METRIC_ISSET(&$4)) {
				BIT_SET(adv->adv_flag, ADVFOT_FLAG);
				adv->adv_result.res_flag = $4.metric;
			    }

			    /* Tag */
			    switch ($5.state) {
			    case PARSE_METRICS_SET:
				BIT_SET(adv->adv_flag, ADVFOT_METRIC2|ADVFOT_FLAG);
				BIT_SET(adv->adv_result.res_flag, OSPF_EXPORT_TAG|OSPF_EXPORT_TAG_METRIC2);
				adv->adv_result.res_metric2 = $5.metric;
				break;

			    case PARSE_METRICS_ALTERNATE:
				BIT_SET(adv->adv_flag, ADVFOT_METRIC2|ADVFOT_FLAG);
				BIT_SET(adv->adv_result.res_flag, OSPF_EXPORT_TAG|OSPF_EXPORT_TAG_METRIC2);
				adv->adv_result.res_metric2 = PATH_OSPF_TAG_TRUSTED |
				    (($5.metric << PATH_OSPF_TAG_USR_SHIFT) & PATH_OSPF_TAG_USR_MASK);
				break;
			    }

			    if (parse_adv_append(&ospf.export_list, adv)) {
				PARSE_ERROR;
			    }
			}
@END:	PROTO_OSPF
@BEGIN:	PROTO_ISIS
    		| T_EXPORT T_PROTO export_isis prop_source_option_iso L_EOS
			{
			    adv_entry *adv;
			    adv_entry *adv_prop = $4.adv;
			    pmet_t *mp = &$4.metric;

			    adv = adv_alloc(ADVFT_ANY, RTPROTO_ISIS);
			    adv->adv_list = adv_prop;

			    /* Metric */
			    if (PARSE_METRIC_ISRESTRICT(mp)) {
				BIT_SET(adv->adv_flag, ADVF_NO);
			    } else if (PARSE_METRIC_ISSET(mp)) {
				BIT_SET(adv->adv_flag, ADVFOT_METRIC);
				adv->adv_result.res_metric = mp->metric;
			    }

			    if (parse_adv_append(&isis_export_list_iso, adv)) {
				PARSE_ERROR;
			    }
			}
@BEGIN:	PROTO_INET
    		| T_EXPORT T_PROTO export_isis T_IP prop_source_option_inet L_EOS
			{
			    adv_entry *adv;
			    adv_entry *adv_prop = $5.adv;
			    pmet_t *mp = &$5.metric;

			    adv = adv_alloc(ADVFT_ANY, RTPROTO_ISIS);
			    adv->adv_list = adv_prop;

			    /* Metric */
			    if (PARSE_METRIC_ISRESTRICT(mp)) {
				BIT_SET(adv->adv_flag, ADVF_NO);
			    } else if (PARSE_METRIC_ISSET(mp)) {
				BIT_SET(adv->adv_flag, ADVFOT_METRIC);
				adv->adv_result.res_metric = mp->metric;
			    }

			    if (parse_adv_append(&isis_export_list_ip, adv)) {
				PARSE_ERROR;
			    }
			}
@END:	PROTO_INET
@END:	PROTO_ISIS
@BEGIN:	PROTO_INET
		| T_AGGREGATE aggregate_dest_inet preference_option aggregate_options '{' aggregate_list_inet '}' L_EOS
			{
			    adv_entry *adv;
			    pmet_t *pp = &$3;

			    /*
			     *	Tack the list of destinations onto the end of the list
			     *	for neighbors with the specified AS.
			     */
			    adv = adv_alloc(ADVFT_DM | $4, 0);
			    adv->adv_dm = $2;	/* struct copy */
			    BIT_RESET(adv->adv_dm.dm_flags, DMF_EXACT);
			    BIT_SET(adv->adv_dm.dm_flags, DMF_REFINE);
			    adv->adv_list = $6;
			    if (PARSE_METRIC_ISSET(pp)) {
				if (PARSE_METRIC_ISRESTRICT(pp)) {
				    BIT_SET(adv->adv_flag, ADVF_NO);
				} else {
				    BIT_SET(adv->adv_flag, ADVFOT_PREFERENCE);
				    adv->adv_result.res_preference = pp->metric;
				}
			    }

			    aggregate_list_inet = adv_destmask_insert(parse_error, aggregate_list_inet, adv);
			    if (!aggregate_list_inet) {
				PARSE_ERROR;
			    }
			}
		| T_GENERATE aggregate_dest_inet preference_option '{' aggregate_list_inet '}' L_EOS
			{
			    adv_entry *adv;
			    pmet_t *pp = &$3;

			    /*
			     *	Tack the list of destinations onto the end of the list
			     *	for neighbors with the specified AS.
			     */
			    adv = adv_alloc(ADVFT_DM | ADVF_AGGR_GENERATE, 0);
			    adv->adv_dm = $2;	/* struct copy */
			    BIT_RESET(adv->adv_dm.dm_flags, DMF_EXACT);
			    BIT_SET(adv->adv_dm.dm_flags, DMF_REFINE);
			    adv->adv_list = $5;
			    if (PARSE_METRIC_ISSET(pp)) {
				if (PARSE_METRIC_ISRESTRICT(pp)) {
				    BIT_SET(adv->adv_flag, ADVF_NO);
				} else {
				    BIT_SET(adv->adv_flag, ADVFOT_PREFERENCE);
				    adv->adv_result.res_preference = pp->metric;
				}
			    }

			    aggregate_list_inet = adv_destmask_insert(parse_error, aggregate_list_inet, adv);
			    if (!aggregate_list_inet) {
				PARSE_ERROR;
			    }
			}
@END:	PROTO_INET
@BEGIN:	PROTO_ISO
		| T_AGGREGATE aggregate_dest_iso preference_option aggregate_options '{' aggregate_list_iso '}' L_EOS
			{
			    adv_entry *adv;
			    pmet_t *pp = &$3;

			    /*
			     *	Tack the list of destinations onto the end of the list
			     *	for neighbors with the specified AS.
			     */
			    adv = adv_alloc(ADVFT_DM | $4, 0);
			    adv->adv_dm = $2;	/* struct copy */
			    BIT_RESET(adv->adv_dm.dm_flags, DMF_EXACT);
			    BIT_SET(adv->adv_dm.dm_flags, DMF_REFINE);
			    adv->adv_list = $6;
			    if (PARSE_METRIC_ISSET(pp)) {
				if (PARSE_METRIC_ISRESTRICT(pp)) {
				    BIT_SET(adv->adv_flag, ADVF_NO);
				} else {
				    BIT_SET(adv->adv_flag, ADVFOT_PREFERENCE);
				    adv->adv_result.res_preference = pp->metric;
				}
			    }

			    aggregate_list_iso = adv_destmask_insert(parse_error, aggregate_list_iso, adv);
			    if (!aggregate_list_iso) {
				PARSE_ERROR;
			    }
			}
		| T_GENERATE aggregate_dest_iso preference_option '{' aggregate_list_iso '}' L_EOS
			{
			    adv_entry *adv;
			    pmet_t *pp = &$3;

			    /*
			     *	Tack the list of destinations onto the end of the list
			     *	for neighbors with the specified AS.
			     */
			    adv = adv_alloc(ADVFT_DM | ADVF_AGGR_GENERATE, 0);
			    adv->adv_dm = $2;	/* struct copy */
			    BIT_RESET(adv->adv_dm.dm_flags, DMF_EXACT);
			    BIT_SET(adv->adv_dm.dm_flags, DMF_REFINE);
			    adv->adv_list = $5;
			    if (PARSE_METRIC_ISSET(pp)) {
				if (PARSE_METRIC_ISRESTRICT(pp)) {
				    BIT_SET(adv->adv_flag, ADVF_NO);
				} else {
				    BIT_SET(adv->adv_flag, ADVFOT_PREFERENCE);
				    adv->adv_result.res_preference = pp->metric;
				}
			    }

			    aggregate_list_iso = adv_destmask_insert(parse_error, aggregate_list_iso, adv);
			    if (!aggregate_list_iso) {
				PARSE_ERROR;
			    }
			}
@END:	PROTO_ISO
		;	

/*  */

/* Support for aggregate clauses */

aggregate_options
		: /* Empty */
			{
			    $$ = 0;
			}
		| T_BRIEF
			{
			    $$ = ADVF_AGGR_BRIEF;
			}
		;

@BEGIN:	PROTO_INET
aggregate_dest_inet
		: network_mask_inet
		| default_mask_inet
		;

aggregate_list_inet
		: aggregate_proto_inet
			{
			    $$ = $1;
			    BIT_SET($$->adv_flag, ADVF_FIRST);
			}
		| aggregate_list_inet aggregate_proto_inet
			{
			    $$ = $1;
			    if (parse_adv_append(&$$, $2)) {
				PARSE_ERROR;
			    }
			}
		| aggregate_list_inet error L_EOS
			{
			    yyerrok;
			}
		;

aggregate_proto_inet
		: T_PROTO aggregate_protos_inet import_option_inet L_EOS
			{
			    pmet_t *pp = &$3.metric;
			    
			    $$ = adv_alloc(ADVFT_ANY, $2);
			    $$->adv_list = $3.adv;
			    if (PARSE_METRIC_ISSET(pp)) {
				if (PARSE_METRIC_ISRESTRICT(pp)) {
				    BIT_SET($$->adv_flag, ADVF_NO);
				} else {
				    BIT_SET($$->adv_flag, ADVFOT_PREFERENCE);
				    $$->adv_result.res_preference = pp->metric;
				}
			    }
			}
@BEGIN:	AUTONOMOUS_SYSTEM
		| T_PROTO aggregate_protos_inet T_AS as import_option_inet L_EOS
			{
			    pmet_t *pp = &$5.metric;
			    
			    $$ = adv_alloc(ADVFT_AS, $2);
			    $$->adv_as = $4;
			    $$->adv_list = $5.adv;
			    if (PARSE_METRIC_ISSET(pp)) {
				if (PARSE_METRIC_ISRESTRICT(pp)) {
				    BIT_SET($$->adv_flag, ADVF_NO);
				} else {
				    BIT_SET($$->adv_flag, ADVFOT_PREFERENCE);
				    $$->adv_result.res_preference = pp->metric;
				}
			    }
			}
@END:	AUTONOMOUS_SYSTEM
@BEGIN:	PROTO_ASPATHS
		| T_PROTO aggregate_protos_inet aspath_match import_option_inet L_EOS
			{
			    pmet_t *pp = &$4.metric;
			    
			    $$ = adv_alloc(ADVFT_ASPATH, $2);
			    $$->adv_aspath = $3;
			    $$->adv_list = $4.adv;
			    if (PARSE_METRIC_ISSET(pp)) {
				if (PARSE_METRIC_ISRESTRICT(pp)) {
				    BIT_SET($$->adv_flag, ADVF_NO);
				} else {
				    BIT_SET($$->adv_flag, ADVFOT_PREFERENCE);
				    $$->adv_result.res_preference = pp->metric;
				}
			    }
			}
    		| T_PROTO aggregate_protos_inet T_TAG tag import_option_inet L_EOS
			{
			    pmet_t *pp = &$5.metric;
			    
			    $$ = adv_alloc(ADVFT_TAG, (proto_t) $2);
			    $$->adv_tag = $4.metric;
			    $$->adv_list = $5.adv;
			    if (PARSE_METRIC_ISSET(pp)) {
				if (PARSE_METRIC_ISRESTRICT(pp)) {
				    BIT_SET($$->adv_flag, ADVF_NO);
				} else {
				    BIT_SET($$->adv_flag, ADVFOT_PREFERENCE);
				    $$->adv_result.res_preference = pp->metric;
				}
			    }
			}
@END:	PROTO_ASPATHS
		;

aggregate_protos_inet
		: T_ALL
			{
			    $$ = RTPROTO_ANY;
			}
		| T_DIRECT
			{
			    $$ = RTPROTO_DIRECT;
			}
		| T_STATIC
			{
			    $$ = RTPROTO_STATIC;
			}
		| T_KERNEL
			{
			    $$ = RTPROTO_KERNEL;
			}
		| T_AGGREGATE
			{
			    $$ = RTPROTO_AGGREGATE;
			}
@BEGIN:	PROTO_HELLO
		| T_HELLO
			{
			    $$ = RTPROTO_HELLO;
			}
@END:	PROTO_HELLO
@BEGIN:	PROTO_RIP
		| T_RIP
			{
			    $$ = RTPROTO_RIP;
			}
@END:	PROTO_RIP
@BEGIN:	PROTO_OSPF
		| T_OSPF
			{
			    $$ = RTPROTO_OSPF;
			}
		| T_OSPF_ASE
			{
			    $$ = RTPROTO_OSPF_ASE;
			}
@END:	PROTO_OSPF
@BEGIN:	PROTO_ISIS
		| T_ISIS
			{
			    $$ = RTPROTO_ISIS;
			}
@END:	PROTO_ISIS
@BEGIN:	PROTO_SLSP
		| T_SLSP
			{
			    $$ = RTPROTO_SLSP;
			}
@END:	PROTO_SLSP
@BEGIN:	PROTO_BGP
		| T_BGP
			{
			    $$ = RTPROTO_BGP;
			}
@END:	PROTO_BGP
@BEGIN:	PROTO_EGP
		| T_EGP
			{
			    $$ = RTPROTO_EGP;
			}
@END:	PROTO_EGP
@BEGIN:	PROTO_SNMP
		| T_SNMP
			{
			    $$ = RTPROTO_SNMP;
			}
@END:	PROTO_SNMP
		;
@END:	PROTO_INET

@BEGIN:	PROTO_ISO
aggregate_dest_iso
		: T_ISO network_mask_iso
			{
			    $$ = $2;
			}
		| T_ISO default_mask_iso
			{
			    $$ = $2;
			}
		;

aggregate_list_iso
		: aggregate_proto_iso
			{
			    $$ = $1;
			    BIT_SET($$->adv_flag, ADVF_FIRST);
			}
		| aggregate_list_iso aggregate_proto_iso
			{
			    $$ = $1;
			    if (parse_adv_append(&$$, $2)) {
				PARSE_ERROR;
			    }
			}
		| aggregate_list_iso error L_EOS
			{
			    yyerrok;
			}
		;

aggregate_proto_iso
		: T_PROTO aggregate_protos_iso import_option_iso L_EOS
			{
			    pmet_t *pp = &$3.metric;
			    
			    $$ = adv_alloc(ADVFT_ANY, $2);
			    $$->adv_list = $3.adv;
			    if (PARSE_METRIC_ISSET(pp)) {
				if (PARSE_METRIC_ISRESTRICT(pp)) {
				    BIT_SET($$->adv_flag, ADVF_NO);
				} else {
				    BIT_SET($$->adv_flag, ADVFOT_PREFERENCE);
				    $$->adv_result.res_preference = pp->metric;
				}
			    }
			}
		;

aggregate_protos_iso
		: T_ALL
			{
			    $$ = RTPROTO_ANY;
			}
		| T_STATIC
			{
			    $$ = RTPROTO_STATIC;
			}
		| T_KERNEL
			{
			    $$ = RTPROTO_KERNEL;
			}
		| T_AGGREGATE
			{
			    $$ = RTPROTO_AGGREGATE;
			}
@BEGIN:	PROTO_ISIS
		| T_ISIS
			{
			    $$ = RTPROTO_ISIS;
			}
@END:	PROTO_ISIS
@BEGIN:	PROTO_IDRP
		| T_IDRP
			{
			    $$ = RTPROTO_IDRP;
			}
@END:	PROTO_IDRP
@BEGIN:	PROTO_SNMP
		| T_SNMP
			{
			    $$ = RTPROTO_SNMP;
			}
@END:	PROTO_SNMP
		;
@END:	PROTO_ISO

/*  */

/* Support for import clauses */

control_exterior	: proto_exterior
			{
			    parse_export_proto = $$.proto = $1;

			    switch ($1) {
#if	defined(PROTO_EGP)
			    case RTPROTO_EGP:
				$$.import_list = &egp_import_list;
				$$.export_list = &egp_export_list;
				break;
#endif

#if	defined(PROTO_BGP)
			    case RTPROTO_BGP:
				$$.import_list = &bgp_import_list;
				$$.export_list = &bgp_export_list;
				break;
#endif

			    default:
				(void) sprintf(parse_error,
					       "unknown import protocol: %s",
					       gd_lower(trace_state(rt_proto_bits, $1)));
				PARSE_ERROR;
			    }
			}
		;


import_listen_option
		: /* Empty */
			{
			}
		| T_LISTEN
			{
			    trace_log_tf(trace_global,
					 0,
					 LOG_WARNING,
					 ("parse: %s use of the ``listen'' keyword is deprecated; removal is recommended",
					  parse_where()));
			}
		;

import_interior : proto_interior
			{
			    $$ = $1;
			    
			    parse_proto = $1.proto;
			    parse_gwlist = $1.gw_list;

			    if (!$1.import_list) {
				(void) sprintf(parse_error,
					       "unknown import protocol: %s",
					       gd_lower(trace_state(rt_proto_bits, $1.proto)));
				PARSE_ERROR;
			    }
			    
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s PROTO: %s",
				      parse_where(),
				      gd_lower(trace_state(rt_proto_bits, $1.proto))));
			}
		;


@BEGIN:	PROTO_INET
/* IP Import stuff */

import_option_inet
		: T_RESTRICT
			{
			    PARSE_METRIC_RESTRICT(&$$.metric);
			    $$.adv = (adv_entry *) 0;
			}
		| preference_option '{' import_list_inet '}'
			{
			    $$.metric = $1;
			    $$.adv = adv_destmask_finish($3);
			}
		;

import_list_inet
		: /* Empty */
			{
			    $$ = (adv_entry *) 0;
			}
		| import_list_inet import_listen_inet L_EOS
			{
			    
			    $$ = adv_destmask_insert(parse_error, $1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		| import_list_inet error L_EOS
			{
			    yyerrok;
			}
		;

import_listen_inet
		: import_listen_option
			{
			    parse_contig_masks = FALSE;
			}	
		dest_mask_inet preference_restrict_option
			{
			    parse_contig_masks = TRUE;

			    if ($3.dm_dest
				&& (socktype($3.dm_dest) != AF_INET)) {
				sprintf(parse_error, "address not INET");
				PARSE_ERROR
			    }

			    $$ = adv_alloc(ADVFT_DM, (proto_t) 0);
			    $$->adv_dm = $3;
			    if (PARSE_METRIC_ISSET(&$4)) {
				if (PARSE_METRIC_ISRESTRICT(&$4)) {
				    BIT_SET($$->adv_flag, ADVF_NO);
				} else {
				    BIT_SET($$->adv_flag, ADVFOT_PREFERENCE);
				    $$->adv_result.res_preference = $4.metric;
				}
			    }
			}
		;
@END:	PROTO_INET

@BEGIN:	PROTO_ISO
/* ISO Import stuff */

import_option_iso	: T_RESTRICT
			{
			    PARSE_METRIC_RESTRICT(&$$.metric);
			    $$.adv = (adv_entry *) 0;
			}
		| preference_option '{' import_list_iso '}'
			{
			    $$.metric = $1;
			    $$.adv = adv_destmask_finish($3);
			}
		;

import_list_iso	: /* Empty */
			{
			    $$ = (adv_entry *) 0;
			}
		| import_list_iso import_listen_iso L_EOS
			{
			    
			    $$ = adv_destmask_insert(parse_error, $1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		| import_list_iso error L_EOS
			{
			    yyerrok;
			}
		;

import_listen_iso
		: import_listen_option
			{
			    parse_contig_masks = FALSE;
			}
		dest_mask_iso preference_restrict_option
			{
			    parse_contig_masks = TRUE;

			    if ($3.dm_dest
				&& (socktype($3.dm_dest) != AF_ISO)) {
				sprintf(parse_error, "address not ISO");
				PARSE_ERROR
			    }

			    $$ = adv_alloc(ADVFT_DM, (proto_t) 0);
			    $$->adv_dm = $3;
			    if (PARSE_METRIC_ISSET(&$4)) {
				if (PARSE_METRIC_ISRESTRICT(&$4)) {
				    BIT_SET($$->adv_flag, ADVF_NO);
				} else {
				    BIT_SET($$->adv_flag, ADVFOT_PREFERENCE);
				    $$->adv_result.res_preference = $4.metric;
				}
			    }
			}
		;
@END:	PROTO_ISO

/*  */

/* Support for Export clauses */

export_interior : proto_interior
			{
			    $$ = $1;
			    
			    parse_export_proto = parse_proto = $1.proto;
			    parse_gwlist = $1.gw_list;

			    if (!$1.export_list) {
				(void) sprintf(parse_error,
					       "unknown export protocol: %s",
					       gd_lower(trace_state(rt_proto_bits, $1.proto)));
				PARSE_ERROR;
			    }
			    
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s PROTO: %s",
				      parse_where(),
				      gd_lower(trace_state(rt_proto_bits, $1.proto))));
			}
		;


@BEGIN:	PROTO_OSPF
export_ospf_ase	: T_OSPF_ASE
			{
			    $$ = parse_export_proto = RTPROTO_OSPF_ASE;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s PROTO: %s",
				      parse_where(),
				      gd_lower(trace_state(rt_proto_bits, $$))));
			}
		;
@END:	PROTO_OSPF

@BEGIN:	PROTO_ISIS
export_isis	: T_ISIS
			{
			    $$ = parse_export_proto = RTPROTO_ISIS;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s PROTO: %s",
				      parse_where(),
				      gd_lower(trace_state(rt_proto_bits, $$))));
			}
@END:	PROTO_ISIS

prop_announce_option
		: /* Empty */
			{
			}
		| T_ANNOUNCE
			{
			    trace_log_tf(trace_global,
					 0,
					 LOG_WARNING,
					 ("parse: %s use of the ``announce'' keyword is deprecated; removal is recommended",
					  parse_where()));
			}
		;


@BEGIN:	PROTO_ISO
prop_source_option_iso
    		: T_RESTRICT
			{
			    PARSE_METRIC_RESTRICT(&$$.metric);
			    $$.adv = (adv_entry *) 0;
			}
		| metric_option '{' prop_source_list_iso '}'
			{
			    $$.metric = $1;
			    $$.adv = $3;
			}
		;

prop_source_list_iso
		: /* Empty */
			{
			    $$ = (adv_entry *) 0;
			}
		| prop_source_list_iso prop_source_iso L_EOS
			{
			    $$ = $1;
			    if (parse_adv_append(&$$, $2)) {
				PARSE_ERROR;
			    }
			}
		| prop_source_list_iso error L_EOS
			{
			    yyerrok;
			}
		;

prop_source_iso	: T_PROTO prop_direct interface_list_option prop_metric_option_iso
			{
			    $$ = parse_adv_propagate_metric($3, $2, &$4.metric, $4.adv);
			    parse_proto = (proto_t) 0;
			}
    /* Static routes */
		| T_PROTO prop_static interface_list_option prop_metric_option_iso
			{
			    $$ = parse_adv_propagate_metric($3, $2, &$4.metric, $4.adv);
			    parse_proto = (proto_t) 0;
			    parse_gwlist = (gw_entry **) 0;
			}
    /* Aggregate routes */
		| T_PROTO prop_aggregate prop_metric_option_iso
			{
			    $$ = parse_adv_propagate_metric(adv_alloc(ADVFT_ANY | ADVF_FIRST,
								      (proto_t) 0),
							    $2,
							    &$3.metric,
							    $3.adv);
			    parse_proto = (proto_t) 0;
			}	
    /* Kernel static routes (routing socket) */
		| T_PROTO prop_kernel interface_list_option prop_metric_option_iso
			{
			    $$ = parse_adv_propagate_metric($3, $2, &$4.metric, $4.adv);
			    parse_proto = (proto_t) 0;
			    parse_gwlist = (gw_entry **) 0;
			}
@BEGIN:	PROTO_ISIS
    /* ISIS imports */
		| T_PROTO isis_prop_init prop_metric_option_iso
			{
			    $$ = parse_adv_propagate_metric(adv_alloc(ADVFT_ANY | ADVF_FIRST,
								      (proto_t) 0),
							    $2,
							    &$3.metric,
							    $3.adv);
			    parse_proto = (proto_t) 0;
			}
@END:	PROTO_ISIS
		;

prop_metric_option_iso
    		: T_RESTRICT
			{
			    PARSE_METRIC_RESTRICT(&$$.metric);
			    $$.adv = (adv_entry *) 0;
			}
		| metric_option prop_restrict_list_option_iso
			{
			    $$.metric = $1;
			    $$.adv = $2;
			}
		;

prop_restrict_list_option_iso
		:	/* Empty */
			{
			    $$ = (adv_entry *) 0;
			}
		| '{' prop_restrict_list_iso '}'
			{
			    $$ = adv_destmask_finish($2);
			}
		;
    

prop_restrict_list_iso
		: /* Empty */
			{
			    $$ = (adv_entry *) 0;
			}
		| prop_restrict_list_iso prop_restrict_iso L_EOS
			{
			    $$ = adv_destmask_insert(parse_error, $1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		| prop_restrict_list_iso error L_EOS
			{
			    yyerrok;
			}
		;

prop_restrict_iso
		: prop_announce_option
			{
			    parse_contig_masks = FALSE;
			}
		dest_mask_iso metric_restrict_option
			{
			    parse_contig_masks = TRUE;

			    if ($3.dm_dest
				&& (socktype($3.dm_dest) != AF_ISO)) {
				sprintf(parse_error, "address not ISO");
				PARSE_ERROR
			    }

			    $$ = adv_alloc(ADVFT_DM, (proto_t) 0);
			    $$->adv_dm = $3;
			    if (PARSE_METRIC_ISRESTRICT(&$4)) {
				BIT_SET($$->adv_flag, ADVF_NO);
			    } else if (PARSE_METRIC_ISSET(&$4)) {
				$$->adv_result.res_metric = $4.metric;
				BIT_SET($$->adv_flag, ADVFOT_METRIC);
			    }
			}
		;

@END:	PROTO_ISO

@BEGIN:	PROTO_INET
prop_source_option_inet
    		: T_RESTRICT
			{
			    PARSE_METRIC_RESTRICT(&$$.metric);
			    $$.adv = (adv_entry *) 0;
			}
		| metric_option '{' prop_source_list_inet '}'
			{
			    $$.metric = $1;
			    $$.adv = $3;
			}
		;

prop_source_list_inet
		: /* Empty */
			{
			    $$ = (adv_entry *) 0;
			}
		| prop_source_list_inet prop_source_inet L_EOS
			{
			    $$ = $1;
			    if (parse_adv_append(&$$, $2)) {
				PARSE_ERROR;
			    }
			}
		| prop_source_list_inet error L_EOS
			{
			    yyerrok;
			}
		;

prop_source_inet
    /* Interfaces */
		: T_PROTO prop_direct interface_list_option prop_metric_option_inet
			{
			    $$ = parse_adv_propagate_metric($3, $2, &$4.metric, $4.adv);
			    parse_proto = (proto_t) 0;
			}
    /* Static routes */
		| T_PROTO prop_static interface_list_option prop_metric_option_inet
			{
			    $$ = parse_adv_propagate_metric($3, $2, &$4.metric, $4.adv);
			    parse_proto = (proto_t) 0;
			    parse_gwlist = (gw_entry **) 0;
			}
    /* Aggregate routes */
		| T_PROTO prop_aggregate prop_metric_option_inet
			{
			    $$ = parse_adv_propagate_metric(adv_alloc(ADVFT_ANY | ADVF_FIRST,
								      (proto_t) 0),
							    $2,
							    &$3.metric,
							    $3.adv);
			    parse_proto = (proto_t) 0;
			}	
    /* Kernel static routes (routing socket) */
		| T_PROTO prop_kernel interface_list_option prop_metric_option_inet
			{
			    $$ = parse_adv_propagate_metric($3, $2, &$4.metric, $4.adv);
			    parse_proto = (proto_t) 0;
			    parse_gwlist = (gw_entry **) 0;
			}
    /* Internal default route */
		| T_PROTO prop_default prop_metric_option_inet
			{
			    $$ = parse_adv_propagate_metric(adv_alloc(ADVFT_ANY | ADVF_FIRST,
								      (proto_t) 0),
							    $2,
							    &$3.metric,
							    $3.adv);
			    parse_proto = (proto_t) 0;
			}
@BEGIN:	AUTONOMOUS_SYSTEM
		| T_PROTO proto_exterior T_AS as prop_metric_option_inet
			{
			    $$ = parse_adv_propagate_metric(adv_alloc(ADVFT_AS | ADVF_FIRST,
								      (proto_t) 0),
							    $2,
							    &$5.metric,
							    $5.adv);
			    $$->adv_as = $4;
			    parse_proto = (proto_t) 0;
			}
@END:	AUTONOMOUS_SYSTEM
@BEGIN:	PROTO_ASPATHS
    /* AS paths */
		| T_PROTO aspath_prop_init aspath_match prop_metric_option_inet
			{
			    $$ = parse_adv_propagate_metric(adv_alloc(ADVFT_ASPATH | ADVF_FIRST,
								      (proto_t) 0),
							    $2,
							    &$4.metric,
							    $4.adv);
			    $$->adv_aspath = $3;
			    parse_proto = (proto_t) 0;
			    parse_gwlist = (gw_entry **) 0;
			}
    /* Tags */
    		| T_PROTO tag_prop_init T_TAG tag prop_metric_option_inet
			{
			    $$ = parse_adv_propagate_metric(adv_alloc(ADVFT_TAG|ADVF_FIRST,
								      (proto_t) 0),
							    $2,
							    &$5.metric,
							    $5.adv);
			    $$->adv_tag = $4.metric;
			    parse_proto = (proto_t) 0;
			    parse_gwlist = (gw_entry **) 0;
			}
@END:	PROTO_ASPATHS
@BEGIN:	PROTO_RIP
    /* RIP Imports */
		| T_PROTO rip_prop_init interface_gateway_list prop_metric_option_inet
			{
			    $$ = parse_adv_propagate_metric($3, $2, &$4.metric, $4.adv);
			    parse_proto = (proto_t) 0;
			    parse_gwlist = (gw_entry **) 0;
			}
@END:	PROTO_RIP
@BEGIN:	PROTO_HELLO
    /* HELLO Imports */
		| T_PROTO hello_prop_init interface_gateway_list prop_metric_option_inet
			{
			    $$ = parse_adv_propagate_metric($3, $2, &$4.metric, $4.adv);
			    parse_proto = (proto_t) 0;
			    parse_gwlist = (gw_entry **) 0;
			}
@END:	PROTO_HELLO
@BEGIN: PROTO_OSPF
    /* OSPF imports */
		| T_PROTO ospf_prop_init prop_metric_option_inet
			{
			    $$ = parse_adv_propagate_metric(adv_alloc(ADVFT_ANY | ADVF_FIRST,
								      (proto_t) 0),
							    $2,
							    &$3.metric,
							    $3.adv);
			    parse_proto = (proto_t) 0;
			}
		| T_PROTO ospf_ase_prop_init prop_metric_option_inet
			{
			    $$ = parse_adv_propagate_metric(adv_alloc(ADVFT_ANY | ADVF_FIRST,
								      (proto_t) 0),
							    $2,
							    &$3.metric,
							    $3.adv);
			    parse_proto = (proto_t) 0;
			}
@END:	PROTO_OSPF
@BEGIN:	PROTO_SLSP
    /* SLSP imports */
		| T_PROTO slsp_prop_init prop_metric_option_inet
			{
			    $$ = parse_adv_propagate_metric(adv_alloc(ADVFT_ANY | ADVF_FIRST,
								      (proto_t) 0),
							    $2,
							    &$3.metric,
							    $3.adv);
			    parse_proto = (proto_t) 0;
			}
@END:	PROTO_SLSP
@BEGIN:	PROTO_ISIS
    /* ISIS imports */
		| T_PROTO isis_prop_init prop_metric_option_inet
			{
			    $$ = parse_adv_propagate_metric(adv_alloc(ADVFT_ANY | ADVF_FIRST,
								      (proto_t) 0),
							    $2,
							    &$3.metric,
							    $3.adv);
			    parse_proto = (proto_t) 0;
			}
@END:	PROTO_ISIS
		;

prop_direct	: T_DIRECT
			{
			    $$ = parse_proto = RTPROTO_DIRECT;
			    parse_gwlist = (gw_entry **) 0;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s PROTO: %s",
				      parse_where(),
				      gd_lower(trace_state(rt_proto_bits, $$))));
			}
		;

prop_static	: T_STATIC
			{
			    $$ = parse_proto = RTPROTO_STATIC;
			    parse_gwlist = &rt_gw_list;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s PROTO: %s",
				      parse_where(),
				      gd_lower(trace_state(rt_proto_bits, $$))));
			}
		;

prop_aggregate	: T_AGGREGATE
			{
			    $$ = parse_proto = RTPROTO_AGGREGATE;
			    parse_gwlist = (gw_entry **) 0;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s PROTO: %s",
				      parse_where(),
				      gd_lower(trace_state(rt_proto_bits, $$))));
			}
		;

prop_kernel	: T_KERNEL
			{
			    $$ = parse_proto = RTPROTO_KERNEL;
			    parse_gwlist = &krt_gw_list;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s PROTO: %s",
				      parse_where(),
				      gd_lower(trace_state(rt_proto_bits, $$))));
			}
		;

prop_default	: T_DEFAULT
			{
			    $$ = parse_proto = RTPROTO_DEFAULT;
			    parse_gwlist = (gw_entry **) 0;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s PROTO: %s",
				      parse_where(),
				      gd_lower(trace_state(rt_proto_bits, $$))));
			}
		;

@BEGIN:	PROTO_INET
prop_metric_option_inet
    		: T_RESTRICT
			{
			    PARSE_METRIC_RESTRICT(&$$.metric);
			    $$.adv = (adv_entry *) 0;
			}
		| metric_option prop_restrict_list_option_inet
			{
			    $$.metric = $1;
			    $$.adv = $2;
			}
		;

prop_restrict_list_option_inet
		:	/* Empty */
			{
			    $$ = (adv_entry *) 0;
			}
		| '{' prop_restrict_list_inet '}'
			{
			    $$ = adv_destmask_finish($2);
			}
		;
    

prop_restrict_list_inet
		: /* Empty */
			{
			    $$ = (adv_entry *) 0;
			}
		| prop_restrict_list_inet prop_restrict_inet L_EOS
			{
			    $$ = adv_destmask_insert(parse_error, $1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		| prop_restrict_list_inet error L_EOS
			{
			    yyerrok;
			}
		;

prop_restrict_inet
		: prop_announce_option
			{
			    parse_contig_masks = FALSE;
			}
		dest_mask_inet metric_restrict_option
			{
			    parse_contig_masks = TRUE;

			    if ($3.dm_dest
				&& (socktype($3.dm_dest) != AF_INET)) {
				sprintf(parse_error, "address not INET");
				PARSE_ERROR
			    }

			    $$ = adv_alloc(ADVFT_DM, (proto_t) 0);
			    $$->adv_dm = $3;
			    if (PARSE_METRIC_ISRESTRICT(&$4)) {
				BIT_SET($$->adv_flag, ADVF_NO);
			    } else if (PARSE_METRIC_ISSET(&$4)) {
				$$->adv_result.res_metric = $4.metric;
				BIT_SET($$->adv_flag, ADVFOT_METRIC);
			    }
			}
		;
@END:	PROTO_INET

/*  */

@BEGIN:	PROTO_INET

/* Addresses */

/* IP address */

dest_mask_inet	: all_mask_inet
		| default_mask_inet
		| host_mask_inet
		| network_mask_flags_inet
		;

all_mask_inet	: T_ALL
			{
			    $$.dm_dest = sockdup(inet_addr_default);
			    $$.dm_mask = inet_mask_default;
			    $$.dm_flags = (flag_t) 0;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s DEST: all",
				      parse_where()));
			}
		;

default_mask_inet
		: T_DEFAULT
			{
			    $$.dm_dest = sockdup(inet_addr_default);
			    $$.dm_mask = inet_mask_default;
			    $$.dm_flags = (flag_t) DMF_EXACT;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s DEST: %A",
				      parse_where(),
				      $$.dm_dest));
			}
		;

/* Gateway list */
gateway_list_inet
		: gateway_inet
			{
			    $$ = adv_alloc(ADVFT_GW | ADVF_FIRST, (proto_t) 0);
			    $$->adv_gwp = $1;
			}
		| gateway_list_inet gateway_inet
			{
			    adv_entry *adv = adv_alloc(ADVFT_GW, (proto_t) 0);

			    adv->adv_gwp = $2;
			    $$ = $1;
			    if (parse_adv_append(&$$, adv)) {
				PARSE_ERROR;
			    }
			}
		;

/* A gateway is a host on an attached network */
gateway_inet	: host_inet
			{
			    /*
			     *	Make sure host is on a locally attached network then
			     *	find or create a gw structure for it.  Requires that
			     *	parse_proto and parse_gwlist are previously set
			     */
			    if (!if_parse_withdst($1)) {
				(void) sprintf(parse_error, "gateway not a host address on an attached network: '%A'",
					       $1);
				if (BIT_TEST(task_state, TASKS_STRICTIFS)) {
				    PARSE_ERROR;
				} else {
				    yyerror(parse_error);
				}
			    }
			    if (!parse_gwlist) {
				(void) sprintf(parse_error, "gateway specification not valid for %s",
					       trace_state(rt_proto_bits, parse_proto));
				PARSE_ERROR;
			    }
			    $$ = gw_locate(parse_gwlist,
					   parse_proto,
					   (task *) 0,
					   (as_t) 0,
					   (as_t) 0,
					   $1,
					   (flag_t) 0);
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s GATEWAY: %A  PROTO: %s",
				      parse_where(),
				      $$->gw_addr,
				      gd_lower(trace_state(rt_proto_bits, $$->gw_proto))));
			    sockfree($1);
			}
		;

host_inet	: host_name
			{ 
			    sockaddr_un *addr;

			    addr = parse_addr_hostname($1.ptr, parse_error);
			    if (!addr) {
				/* Name resolution failure */
				
				PARSE_ERROR;
			    }
			    $$ = sockdup(addr);
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s HOST: %A",
				      parse_where(),
				      $$));
			    free_charstr($1);
			}
		| addr_inet
			{
			    $$ = $1;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s HOST: %A",
				      parse_where(),
				      $$));
			}
		;

host_mask_inet	: T_HOST host_inet
			{
			    $$.dm_dest = $2;
			    $$.dm_mask = inet_mask_host;
			    $$.dm_flags = DMF_EXACT;

			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s DEST: %A",
				      parse_where(),
				      $$.dm_dest));
			}
		;

network_inet	: host_name
			{
			    sockaddr_un *addr;

			    addr = parse_addr_netname($1.ptr, parse_error);
			    if (!addr) {
				/* Name resolution failure */

				PARSE_ERROR;
			    }
			    $$ = sockdup(addr);
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s NETWORK: %A",
				      parse_where(),
				      $$));
			    free_charstr($1);
			}
		| addr_inet
			{
			    $$ = $1;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s NETWORK: %A",
				      parse_where(),
				      $$));
			}
		;

network_mask_inet
		: network_inet
			{
			    $$.dm_dest = $1;
			    $$.dm_mask = inet_mask_natural($1);
			    $$.dm_flags = (flag_t) 0;
			    if (sock2ip($$.dm_dest) & ~sock2ip($$.dm_mask)) {
				sprintf(parse_error, "host or mask option needed");
				PARSE_ERROR;
			    }
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s DEST: %A MASK: %A",
				      parse_where(),
				      $$.dm_dest,
				      $$.dm_mask));
			}
		| network_inet T_MASKLEN number
			{
			    $$.dm_dest = $1;
			    if (parse_limit_check("inet mask bits",
						  (u_int) $3,
						  INET_LIMIT_MASKLEN)) {
				PARSE_ERROR;
			    }
			    $$.dm_mask = inet_masks[$3];
			    $$.dm_flags = (flag_t) 0;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s DEST: %A MASK: %A",
				      parse_where(),
				      $$.dm_dest,
				      $$.dm_mask));
			}
		| network_inet T_MASK mask_inet
			{
			    register byte *ap = $1->a.ga_data;
			    register byte *mp = $3->a.ga_data;
			    register byte *alp = (byte *) $1 + socksize($1);
			    register byte *mlp = (byte *) $3 + socksize($3);

			    /* Skip zero fields */
			    while (!*ap && ap < alp) {
				ap++, mp++;
			    }
			    
			    while (ap < alp) {
				if (mp < mlp) {
				    if (*ap++ & ~*mp++) {
					break;
				    }
				} else {
				    if (*ap++) {
					break;
				    }
				}
			    }
			    if (ap < alp) {
				sprintf(parse_error, "Non-masked bits not zero for %A mask %A",
					$1,
					$3);
				PARSE_ERROR;
			    }

			    $$.dm_dest = $1;
			    $$.dm_mask = $3;
			    $$.dm_flags = (flag_t) 0;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s DEST: %A MASK: %A",
				      parse_where(),
				      $$.dm_dest,
				      $$.dm_mask));
			}
		;

network_mask_flags_inet
		: network_mask_inet dm_flags
			{
			    $$ = $1;
			    $$.dm_flags = $2;
			}
		;

mask_inet	: in_addr
			{
			    $$ = inet_mask_locate($1.s_addr);
			    if (!$$) {
				if (parse_contig_masks) {
				    (void) sprintf(parse_error, "mask not contiguous");
				    PARSE_ERROR;
				} else {
				    $$ = mask_locate(sockbuild_in(0, $1.s_addr));
				}
			    }
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s MASK: %A",
				      parse_where(),
				      $$));
			}
		;


addr_inet	: in_addr
			{
			    $$ = sockdup(sockbuild_in(0, $1.s_addr));

			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s IP_ADDR: %A",
				      parse_where(),
				      $$));
			}
		;


in_addr		: L_NUMBER
			{
			    u_int32 addr = $1;
			    
			    if (addr) {
				/* Normalize the address */
				while (!(addr & 0xff000000)) {
				    addr <<= 8;
				}
			    }
			    $$.s_addr = htonl(addr);
			}
		| byte_string
			{
			    int i;
			    u_int32 addr = 0;

			    if ($1.len > sizeof(addr)) {
				sprintf(parse_error, "octet or hex string too long to be an IP address");
				PARSE_ERROR;
			    }

			    for (i = 0; i < sizeof(addr); i++) {
				addr <<= 8;
				if (i < $1.len) {
				    BIT_SET(addr, $1.ptr[i]);
				}
			    }
			    $$.s_addr = htonl(addr);
			    free_bytestr($1);
			}
		;

/* TTLs */
inet_ttl	: L_NUMBER
			{
			    if (parse_limit_check("ttl",
						  (u_int) $1,
						  INET_LIMIT_TTL)) {
				PARSE_ERROR;
			    }
			    $$ = $1;
			}
		;

@END:	PROTO_INET

/**/

@BEGIN:	PROTO_ISO

dest_mask_iso	: all_mask_iso
		| default_mask_iso
		| network_mask_flags_iso
		| host_mask_iso
		;

all_mask_iso	: T_ALL
			{
			    $$.dm_dest = sockdup(iso_addr_default);
			    $$.dm_mask = iso_mask_natural(iso_mask_default);
			    $$.dm_flags = (flag_t) 0;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s DEST: iso all",
				      parse_where()));
			}
		;

default_mask_iso
		: T_DEFAULT
			{
			    $$.dm_dest = sockdup(iso_addr_default);
			    $$.dm_dest = iso_mask_natural(iso_addr_default);
			    $$.dm_flags = (flag_t) DMF_EXACT;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s DEST: iso all",
				      parse_where()));
			}
		;

/* Gateway list */
gateway_list_iso
		: gateway_iso
			{
			    $$ = adv_alloc(ADVFT_GW | ADVF_FIRST, (proto_t) 0);
			    $$->adv_gwp = $1;
			}
		| gateway_list_iso gateway_iso
			{
			    adv_entry *adv = adv_alloc(ADVFT_GW, (proto_t) 0);

			    adv->adv_gwp = $2;
			    $$ = $1;
			    if (parse_adv_append(&$$, adv)) {
				PARSE_ERROR;
			    }
			}
		;

/* A gateway is a host on an attached network */
gateway_iso	: host_iso
			{
			    /*
			     *	Make sure host is on a locally attached network then
			     *	find or create a gw structure for it.  Requires that
			     *	parse_proto and parse_gwlist are previously set
			     */
			    if (!if_parse_withdst($1)) {
				(void) sprintf(parse_error, "gateway not a host address on an attached network: '%A'",
					       $1);
				if (BIT_TEST(task_state, TASKS_STRICTIFS)) {
				    PARSE_ERROR;
				} else {
				    yyerror(parse_error);
				}
			    }
			    if (!parse_gwlist) {
				(void) sprintf(parse_error, "gateway specification not valid for %s",
					       trace_state(rt_proto_bits, parse_proto));
				PARSE_ERROR;
			    }
			    $$ = gw_locate(parse_gwlist,
					   parse_proto,
					   (task *) 0,
					   (as_t) 0,
					   (as_t) 0,
					   $1,
					   (flag_t) 0);
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s GATEWAY: %A  PROTO: %s",
				      parse_where(),
				      $$->gw_addr,
				      gd_lower(trace_state(rt_proto_bits, $$->gw_proto))));
			    sockfree($1);
			}
		;

host_iso	: addr_iso
			{
			    $$ = $1;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s HOST: %A",
				      parse_where(),
				      $$));
			}
		;

host_mask_iso	: T_HOST host_iso
			{
			    $$.dm_dest = $2;
			    $$.dm_mask = iso_mask_natural($2);
			    $$.dm_flags = DMF_EXACT;

			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s DEST: %A",
				      parse_where(),
				      $$.dm_dest));
			}
		;

network_iso	: addr_iso
			{
			    $$ = $1;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s NETWORK: %A",
				      parse_where(),
				      $$));
			}
		;

network_mask_iso
		: network_iso
			{
			    $$.dm_dest = $1;
			    $$.dm_mask = iso_mask_natural($1);
			    $$.dm_flags = (flag_t) 0;

			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s DEST: %A MASK: %A",
				      parse_where(),
				      $$.dm_dest,
				      $$.dm_mask));
			}
		| network_iso T_MASKLEN number
			{
			    $$.dm_dest = $1;
			    if (parse_limit_check("iso mask bits",
						  (u_int) $3,
						  ISO_LIMIT_MASKLEN)) {
				PARSE_ERROR;
			    }
			    $$.dm_mask = iso_masks[$3];
			    $$.dm_flags = (flag_t) 0;

			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s DEST: %A MASK: %A",
				      parse_where(),
				      $$.dm_dest,
				      $$.dm_mask));
			}
		| network_iso T_MASK mask_iso
			{
			    register byte *ap = $1->a.ga_data;
			    register byte *mp = $3->a.ga_data;
			    register byte *alp = (byte *) $1 + socksize($1);
			    register byte *mlp = (byte *) $3 + socksize($3);

			    /* Skip zero fields */
			    while (!*ap && ap < alp) {
				ap++, mp++;
			    }
			    
			    while (ap < alp) {
				if (mp < mlp) {
				    if (*ap++ & ~*mp++) {
					break;
				    }
				} else {
				    if (*ap++) {
					break;
				    }
				}
			    }
			    if (ap < alp) {
				sprintf(parse_error, "Non-masked bits not zero for %A mask %A",
					$1,
					$3);
				PARSE_ERROR;
			    }

			    $$.dm_dest = $1;
			    $$.dm_mask = $3;
			    $$.dm_flags = (flag_t) 0;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s DEST: %A MASK: %A",
				      parse_where(),
				      $$.dm_dest,
				      $$.dm_mask));
			}
		;

network_mask_flags_iso
		: network_mask_iso dm_flags
			{
			    $$ = $1;
			    $$.dm_flags = $2;
			}
		;

mask_iso	: addr_iso
			{
			    $$ = iso_mask_locate($1);
			    sockfree($1);
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s MASK: %A",
				      parse_where(),
				      $$));
			}
		;

addr_iso	: L_ISOADDR
			{
			    if ($1.len > ISO_MAXADDRLEN) {
				sprintf(parse_error, "ISO address has too many bytes (%d), %d maximum",
					$1.len,
					ISO_MAXADDRLEN);
				PARSE_ERROR;
			    }
			    
			    $$ = sockdup(sockbuild_iso($1.ptr, $1.len));

			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s ADDR_ISO: %A",
				      parse_where(),
				      $$));

			    free_bytestr($1);
			}
@END:	PROTO_ISO

/* Common to both */

host		: T_NOP_SOCKADDR
			{
			    assert(FALSE);
			}
@BEGIN:	PROTO_INET
		| host_inet
@END:	PROTO_INET
@BEGIN:	PROTO_ISO
		| host_iso
@END:	PROTO_ISO
		;

mask		: T_NOP_SOCKADDR
			{
			    assert(FALSE);
			}
@BEGIN:	PROTO_INET
		| mask_inet
@END:	PROTO_INET
@BEGIN:	PROTO_ISO
		| mask_iso
@END:	PROTO_ISO
		;

addr		: T_NOP_SOCKADDR
			{
			    assert(FALSE);
			}
@BEGIN:	PROTO_INET
		| addr_inet
@END:	PROTO_INET
@BEGIN:	PROTO_ISO
		| addr_iso
@END:	PROTO_ISO
		;

gateway_list	: T_NOP_ADV
			{
			    assert(FALSE);
			}
@BEGIN:	PROTO_INET
		| gateway_list_inet
@END:	PROTO_INET
@BEGIN:	PROTO_ISO
		| gateway_list_iso
@END:	PROTO_ISO
		;

dm_flags	: /* Empty */
			{
			    $$ = (flag_t) 0;
			}
		| T_EXACT
			{
			    $$ = DMF_EXACT;
			}
		| T_REFINE
			{
			    $$ = DMF_REFINE;
			}
		;


@END:	PROTO_INET

/* Host name */
host_name	: L_HNAME
			{
			    $$ = $1;
			    $$.ptr = task_mem_strdup((task *) 0, $1.ptr);
			}
		| L_KEYWORD
			{
			    $$ = $1;
			    $$.ptr = task_mem_strdup((task *) 0, $1.ptr);
			}
		| string
		;

/* Protocols */
proto_interior	: T_REDIRECT
			{
#if	defined(PROTO_ICMP) || defined(KRT_RT_SOCK)
			    $$.proto = RTPROTO_REDIRECT;
			    $$.import_list = &redirect_import_list;
			    $$.export_list = (adv_entry **) 0;
			    $$.gw_list = &redirect_gw_list;
#endif	/* defined(PROTO_ICMP) || defined(KRT_RT_SOCK) */
			}
@BEGIN:	PROTO_HELLO
		| T_HELLO
			{
			    $$.proto = RTPROTO_HELLO;
			    $$.import_list = &hello_import_list;
			    $$.export_list = &hello_export_list;
			    $$.gw_list = &hello_gw_list;
			}
@END:	PROTO_HELLO
@BEGIN:	PROTO_RIP
		| T_RIP
			{
			    $$.proto = RTPROTO_RIP;
			    $$.import_list = &rip_import_list;
			    $$.export_list = &rip_export_list;
			    $$.gw_list = &rip_gw_list;
			}
@END:	PROTO_RIP
		;


proto_exterior	: T_NOP_PROTO
			{
			    assert(FALSE);
			}
@BEGIN:	PROTO_EGP
		| egp_prop_init
@END:	PROTO_EGP
@BEGIN:	PROTO_BGP
		| bgp_prop_init
@END:	PROTO_BGP
		;

onoff_option	: T_ON		{ $$ = T_ON; }
		| T_OFF		{ $$ = T_OFF; }
		;

/* Metric */

metric		: number
			{
			    PARSE_METRIC_SET(&$$, $1);
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s METRIC: %d",
				      parse_where(),
				      $$.metric));
			}
		| T_INFINITY
			{
			    PARSE_METRIC_INFINITY(&$$);
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s METRIC: infinity",
				      parse_where()));
			}
		;

metric_option	: /* Empty */
			{
			    PARSE_METRIC_CLEAR(&$$);
			}
		| T_METRIC metric
			{
			    if (parse_metric_check(parse_export_proto, &$2)) {
				PARSE_ERROR;
			    }
			    $$ = $2;
			}
		;
		
metric_restrict_option
		: metric_option
			{
			    $$ = $1;
			}
		| T_RESTRICT
			{
			    PARSE_METRIC_RESTRICT(&$$);
			}
		;
		
/* Preference */
preference_option
		: /* Empty */
			{
			    PARSE_METRIC_CLEAR(&$$);
			}
		| T_PREFERENCE preference
			{
			    PARSE_METRIC_SET(&$$, $2);
			}
		;

preference_restrict_option
		: preference_option
		| T_RESTRICT
			{
			    PARSE_METRIC_RESTRICT(&$$);
			}
		;

preference	: L_NUMBER
			{
			    if (parse_limit_check("preference",
						  (u_int) $1,
						  LIMIT_PREFERENCE)) {
				PARSE_ERROR;
			    }
			    $$ = $1;
			}
		;


/* Numbers and such */
string		: L_STRING
			{
			    /* Remove quotes from the string if present */
			    char *cp;

			    $$ = $1;
				
			    switch (*$$.ptr) {
			    case '<':
				*$$.ptr = '>';
				/* Fall through */

			    case '"':
				cp = &$$.ptr[$$.len-1];
				if (*cp == *$$.ptr) {
				    *cp = (char) 0;
				    $$.len -= 2;
				    cp = $$.ptr + 1;
				    break;
				}
				/* Fall Through */

			    default:
				cp = $$.ptr;
			    }

			    $$.ptr = task_mem_strdup((task *) 0, cp);
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s STRING: \"%s\" length: %d",
				      parse_where(),
				      $$.ptr,
				      $$.len));
			}
		;


neg_number	: L_NUMBER
		| '-' L_NUMBER
			{
			    $$ = -$2;
			}
		;

number		: L_NUMBER
		| byte_string
			{
			    int i = 0;
			    int len = sizeof($$);

			    $$ = 0;
			    if ($1.len > len) {
				sprintf(parse_error, "octet or hex string too long to be a number");
				PARSE_ERROR;
			    } else if ($1.len < len) {
				len = $1.len;
			    }
			    while (i < len) {
				$$ = ($$ << 8) | $1.ptr[i++];
			    }
			    free_bytestr($1);
			}
		;


byte_string	: L_HEXSTRING
		| L_OCTETSTRING
		;

@BEGIN:	PARSE_UTIME
utime		: time '.' L_USEC
			{
			    $$.ut_sec = $1;
			    $$.ut_usec = $3;
			}
		;
@END:	PARSE_UTIME

time		: L_NUMBER
			{
			    if (parse_limit_check("seconds",
						  (u_int) $1,
						  LIMIT_NATURAL)) {
				PARSE_ERROR;
			    };
			    $$ = $1;
			}
		| L_NUMBER ':' L_NUMBER
			{
			    if (parse_limit_check("minutes",
						  (u_int) $1,
						  LIMIT_NATURAL)) {
				PARSE_ERROR;
			    }
			    if (parse_limit_check("seconds",
						  (u_int) $3,
						  LIMIT_SECONDS)) {
				PARSE_ERROR;
			    }
			    $$ = ($1 * 60) + $3;
			}
		| L_NUMBER ':' L_NUMBER ':' L_NUMBER
			{
			    if (parse_limit_check("hours",
						  (u_int) $1,
						  LIMIT_NATURAL)) {
				PARSE_ERROR;
			    }
			    if (parse_limit_check("minutes",
						  (u_int) $3,
						  LIMIT_MINUTES)) {
				PARSE_ERROR;
			    }
			    if (parse_limit_check("seconds",
						  (u_int) $5,
						  LIMIT_SECONDS)) {
				PARSE_ERROR;
			    }
			    $$ = (($1 * 60) + $3) * 60 + $5;
			}
		;

/* Internet ports */
@BEGIN:	PARSE_PORT
port		: L_NUMBER
			{
			    if (parse_limit_check("port",
						  (u_int) $1,
						  LIMIT_PORT)) {
				PARSE_ERROR;
			    }
			    $$ = htons($1);
			}
		| L_KEYWORD
			{
			    const struct servent *sp;

			    if (!(sp = getservbyname($1.ptr, parse_serv_proto))) {
				(void) sprintf(parse_error, "unknown protocol %s/%s",
					$1.ptr, parse_serv_proto);
				PARSE_ERROR;
			    }

			    $$ = sp->s_port;

			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s PORT %s (%d)",
				      parse_where(),
				      $1.ptr,
				      ntohs($$)));
			}
		;
@END:	PARSE_PORT

/**/
@BEGIN:	AUTONOMOUS_SYSTEM
/* Autonomous systems */

as_loop_option	: /* Empty */
			{
			    $$ = 1;
			}
@BEGIN:	PROTO_ASPATHS
		| T_LOOPS L_NUMBER
			{
			    if (parse_limit_check("as loop limit",
						  (u_int) $2,
						  LIMIT_AS_LOOPS)) {
				PARSE_ERROR;
			    }
			    $$ = $2;
			}
@END:	PROTO_ASPATHS
		;


as		: L_NUMBER
			{
			    if (parse_limit_check("autonomous system",
						  (u_int) $1,
						  LIMIT_AS)) {
				PARSE_ERROR;
			    }
			    $$ = $1;
			}
		;

@BEGIN:	PARSE_ASLIST
as_list		: as
			{
			    $$ = adv_alloc(ADVFT_AS | ADVF_FIRST, (proto_t) 0);
			    $$->adv_as = $1;
			}
		| as_list as
			{
			    adv_entry *adv = adv_alloc(ADVFT_AS, (proto_t) 0);

			    adv->adv_as = $2;
			    $$ = $1;
			    if (parse_adv_append(&$$, adv)) {
				PARSE_ERROR;
			    }
			}
		;

as_list_option	: /* Empty */
			{
			    $$ = (adv_entry *) 0;
			}
		| T_AS as_list
			{
			    $$ = $2;
			}
		;
@END:	PARSE_ASLIST

@END:	AUTONOMOUS_SYSTEM
/**/
@BEGIN:	PROTO_ASPATHS
/* Tags */

/* Route tags */
tag_as_option
		: /* Empty */
			{
			    PARSE_METRIC_CLEAR(&$$);
			}
		| T_TAG tag_as
			{
			    $$ = $2;
			}
		;

tag_as		: tag
		| T_AS
			{
			    PARSE_METRIC_ALTERNATE(&$$, 0);
			}
		| T_AS number
			{
			    if (parse_limit_check("external-route-tag",
						  (u_int) $2,
						  PATH_OSPF_TAG_USR_LIMIT)) {
				PARSE_ERROR;
			    }
			    PARSE_METRIC_ALTERNATE(&$$, $2);
			}
		;

tag_option	: /* Empty */
			{
			    PARSE_METRIC_CLEAR(&$$);
			}
		| T_TAG tag
			{
			    $$ = $2;
			}
		;

tag	: number
			{
			    if (parse_limit_check("external-route-tag",
						  (u_int) $1,
						  PATH_OSPF_TAG_LIMIT)) {
				PARSE_ERROR;
			    }
			    PARSE_METRIC_SET(&$$, $1);
			}
/* XXX - various tag options */
		;

tag_prop_init
		: proto_exterior
@BEGIN:	PROTO_RIP
		| rip_prop_init 
@END:	PROTO_RIP
@BEGIN:	PROTO_HELLO
		| hello_prop_init 
@END:	PROTO_HELLO
@BEGIN:	PROTO_OSPF
		| ospf_prop_init
		| ospf_ase_prop_init
@END:	PROTO_OSPF
		;

/**/
/* AS paths */

aspath_prop_init
		: T_ALL
			{
			    $$ = parse_proto = RTPROTO_ANY;
			    parse_gwlist = (gw_entry **) 0;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("parse: %s PROTO: %s",
				      parse_where(),
				      gd_lower(trace_state(rt_proto_bits, $$))));
			}
		| proto_exterior
@BEGIN:	PROTO_RIP
		| rip_prop_init 
@END:	PROTO_RIP
@BEGIN:	PROTO_HELLO
		| hello_prop_init 
@END:	PROTO_HELLO
@BEGIN:	PROTO_OSPF
		| ospf_prop_init
		| ospf_ase_prop_init
@END:	PROTO_OSPF
		;

aspath_match	: T_ASPATH
			{
			    aspath_init_regex();
			}
		aspath_regex T_ORIGIN aspath_origin
    			{
			    $$ = aspath_consume_current($3);
			    $$->origin_mask = $5;
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("%s: path %X origins %s",
				      parse_where(),
				      $$,
				      aspath_adv_origins($$->origin_mask)));
			}
    		;

aspath_origin :
			{
			    /* Set all bits on */
			    $$ = (flag_t) -1;
			}
		| T_ANY
			{
			    /* Set all bits on */
			    $$ = (flag_t) -1;
			}
		| aspath_origin_list
			{
			    $$ = $1;
			}
		;

aspath_origin_list
		: aspath_origins
		| aspath_origin_list '|' aspath_origins
			{
			    $$ = $1 | $3;
			}
		;

aspath_origins	: T_IGP
			{
			    $$ = (1 << PATH_ORG_IGP);
			}
		| T_EGP
			{
			    $$ = (1 << PATH_ORG_EGP);
			}
		| T_INCOMPLETE
    			{
			    $$ = (1 << PATH_ORG_XX);
			}
		;
    
aspath_regex	: aspath_sum
			{
			    aspath_simple_regex(&$$, &$1);
			}
		| aspath_regex '|' aspath_sum
			{
			    aspath_merge_regex(&$$, &$1, &$3);
			}
		;

aspath_sum	: aspath_term
			{
			    aspath_copy_regex(&$$, &$1);
			}
		| aspath_sum aspath_term
			{
			    if(!aspath_prepend_regex(&$$, &$1, &$2)) {
				YYERROR;
			    }
			}
		;

aspath_term	: aspath_symbol
			{
			    aspath_copy_regex(&$$, &$1);
			}
		| aspath_symbol '*'
			{
			    aspath_zero_or_more_term(&$$, &$1);
			}
		| aspath_symbol '+'
			{
			    aspath_one_or_more_term(&$$, &$1);
			}
		| aspath_symbol '?'
			{
			    aspath_zero_or_one_term(&$$, &$1);
			}
		| aspath_symbol '{' aspath_range '}'
			{
			    if (!aspath_range_term(&$$, &$1, &$3)) {
				sprintf(parse_error,
					"too many AS path regexp states");
				PARSE_ERROR;
			    }
			}
		;

aspath_symbol	: as
			{
			    if (!aspath_as_transition(&$$, $1)) {
				sprintf(parse_error,
					"too many AS path regexp states");
				PARSE_ERROR;
			    }
			}
		| '.'
			{
			    if (!aspath_any_transition(&$$)) {
				sprintf(parse_error,
					"too many AS path regexp states");
				PARSE_ERROR;
			    }
			}
		| '(' aspath_regex ')'
			{
			    aspath_copy_regex(&$$, &$2);
			}

aspath_range	: number
			{
			    $$.begin = $1;
			    $$.end = $1;
			    if (!$1) {
				sprintf(parse_error, "invalid range start: %d",
					$1);
				PARSE_ERROR;
			    }
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("%s: RANGE: {%d}",
				      parse_where(),
				      $$.begin));
			}
		| number ','
			{
			    $$.begin = $1;
			    $$.end = 0;
			    if (!$1) {
				sprintf(parse_error, "invalid range start: %d",
					$1);
				PARSE_ERROR;
			    }
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("%s: RANGE: {%d,}",
				      parse_where(),
				      $$.begin));
			}
		| number ',' number
			{
			    $$.begin = $1;
			    $$.end = $3;
			    if (!$1) {
				sprintf(parse_error, "invalid range start: %d",
					$1);
				PARSE_ERROR;
			    }
			    if ($3 < $1 || !$3) {
				sprintf(parse_error, "invalid range end: %d",
					$3);
				PARSE_ERROR;
			    }
			    trace_tf(trace_global,
				     TR_PARSE,
				     0,
				     ("%s: RANGE: {%d,%d}",
				      parse_where(),
				      $$.begin,
				      $$.end));
			}
		;
@END:	PROTO_ASPATHS
%%

/*
 *	Log any parsing errors
 */
static void
yyerror(s)
const char *s;
{
    byte *cp;

    tracef("parse: %s ",
	   parse_where());

    switch (yychar) {
    case L_HEXSTRING:
	tracef("%s at '",
	       s);
	for (cp = yylval.hex.ptr; (cp - yylval.hex.ptr) < yylval.hex.len; cp++) {
	    tracef("%02x",
		   *cp);
	}
	tracef("'");
	break;	

    case L_OCTETSTRING:
	tracef("%s at '",
	       s);
	for (cp = yylval.hex.ptr; (cp - yylval.hex.ptr) < yylval.hex.len; cp++) {
	    tracef("%s%u",
		   (cp == yylval.hex.ptr) ? "" : ".",
		   *cp);
	}
	tracef("'");
	break;	

    case L_NUMBER:
	tracef("%s at '%d'",
	       s,
	       yylval.num);
	break;

    case L_EOS:
	tracef("%s at 'end-of-statement'",
	       s);
	break;

    case L_ERROR:
	tracef("%s",
	       parse_error);
	break;

#ifdef	YYEOF
    case YYEOF:
#else	/* YYEOF */
    case 0:
#endif	/* YYEOF */
	tracef("%s at 'end-of-file'",
	       s);
	break;

    default:
	if (!parse_keyword_lookup(yychar)) {
#if	YYDEBUG != 0
#ifdef	YYTRANSLATE
	    tracef("%s at '%s'",
		   s,
		   yytname[YYTRANSLATE(yychar)]);
#else	/* YYTRANSLATE */
	    tracef("%s at '%s'",
		   s,
		   yyname[yychar]);
#endif	/* YYTRANSLATE */
#else	/* YYDEBUG */
	    tracef("%s",
		   s);
#endif	/* YYDEBUG */
	    break;
	}
	tracef("%s at '%s' (%u) length %d",
	       s,
	       yylval.str.ptr,
	       yylval.str.type,
	       yylval.str.len);
	break;

    case L_STRING:
    case L_HNAME:
    case L_KEYWORD:
	tracef("%s at '%s' length %d",
	       s,
	       yylval.str.ptr,
	       yylval.str.len);
	break;

#ifdef	YYEMPTY
    case YYEMPTY:
	tracef("%s",
	       s);
	break;
#endif	/* YYEMPTY */
    }
    trace_log_tf(trace_global,
		 TRC_NL_BEFORE|TRC_NL_AFTER,
		 LOG_ERR,
		 (NULL));
}



/*
 * %(Copyright)
 */
