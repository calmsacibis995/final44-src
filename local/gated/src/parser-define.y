%{
/*
 *  $Header: /u2/gated-alpha.feb3/src/RCS/parser.y,v 1.3 92/04/06 14:47:18 root Exp $
 */

/*%Copyright%*/
/************************************************************************
*									*
*	GateD, Release 3						*
*									*
*	Copyright (c) 1990,1991,1992 by Cornell University		*
*	    All rights reserved.					*
*									*
*	THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY		*
*	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, WITHOUT		*
*	LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTABILITY		*
*	AND FITNESS FOR A PARTICULAR PURPOSE.				*
*									*
*	Royalty-free licenses to redistribute GateD Release		*
*	3 in whole or in part may be obtained by writing to:		*
*									*
*	    GateDaemon Project						*
*	    Information Technologies/Network Resources			*
*	    143 Caldwell Hall						*
*	    Cornell University						*
*	    Ithaca, NY 14853-2602					*
*									*
*	GateD is based on Kirton's EGP, UC Berkeley's routing		*
*	daemon	 (routed), and DCN's HELLO routing Protocol.		*
*	Development of Release 2 has been supported by the		*
*	National Science Foundation.					*
*									*
*	Please forward bug fixes, enhancements and questions to the	*
*	gated mailing list: gated-people@gated.cornell.edu.		*
*									*
*	Authors:							*
*									*
*		Jeffrey C Honig <jch@gated.cornell.edu>			*
*		Scott W Brim <swb@gated.cornell.edu>			*
*									*
*************************************************************************
*									*
*      Portions of this software may fall under the following		*
*      copyrights:							*
*									*
*	Copyright (c) 1988 Regents of the University of California.	*
*	All rights reserved.						*
*									*
*	Redistribution and use in source and binary forms are		*
*	permitted provided that the above copyright notice and		*
*	this paragraph are duplicated in all such forms and that	*
*	any documentation, advertising materials, and other		*
*	materials related to such distribution and use			*
*	acknowledge that the software was developed by the		*
*	University of California, Berkeley.  The name of the		*
*	University may not be used to endorse or promote		*
*	products derived from this software without specific		*
*	prior written permission.  THIS SOFTWARE IS PROVIDED		*
*	``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES,	*
*	INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF	*
*	MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.		*
*									*
************************************************************************/


#define	INCLUDE_STAT

#include "include.h"
#include "parse.h"
#include "krt.h"
#ifdef	PROTO_RIP
#include "rip.h"
#endif	/* PROTO_RIP */
#ifdef	PROTO_HELLO
#include "hello.h"
#endif	/* PROTO_HELLO */
@BEGIN:	PROTO_OSPF
#include "ospf.h"
@END:	PROTO_OSPF
@BEGIN:	PROTO_IDPR
#include "idpr.h"
@END:	PROTO_IDPR
#ifdef	PROTO_EGP
#include "egp.h"
#endif	/* PROTO_EGP */
#ifdef	PROTO_BGP
#include "bgp.h"
#endif	/* PROTO_BGP */
#ifdef	PROTO_ISODE_SNMP
#include "snmp_isode.h"
#endif	/* PROTO_ISODE_SNMP */
#ifdef	PROTO_ASPATHS
#include "aspath.h"
#endif	/* PROTO_ASPATHS */

char parse_error[BUFSIZ];
char *parse_filename;
char *parse_directory;

static	int	parse_group_index;
static	proto_t	parse_proto;
static	proto_t	parse_export_proto;
static	gw_entry	**parse_gwlist;
static	gw_entry	*parse_gwp;
static  char *parse_serv_proto;
static	pmet_t parse_preference;
static	pmet_t parse_metric;
static	struct if_info parse_ifi;
@BEGIN:	PROTO_EGP
static	egp_neighbor *ngp, egp_group, *gr_ngp;
@END:	PROTO_EGP
@BEGIN:	PROTO_BGP
static	bgpPeer *bnp;
static	bgpPeerGroup *bgp;
static 	struct bgp_conf *bcp;
@END:	PROTO_BGP
@BEGIN:	PROTO_OSPF
static struct INTF *ospf_INTF;
static struct AREA *ospf_AREA;
@END:	PROTO_OSPF

int parse_state = -1;
proto_t protos_seen;
sockaddr_un parse_addr;
#if	defined(PROTO_EGP) || defined(PROTO_BGP)
adv_entry	**parse_import_list;
adv_entry	**parse_export_list;
#endif

static void yyerror();			/* Log a parsing error */

#define	free_string(s)	task_mem_free((task *) 0, (caddr_t) s); s = 0
#define	free_charstr(s)	task_mem_free((task *) 0, (caddr_t) (s)->ptr); (s)->ptr = (char *) 0; (s)->len = (s)->type = 0
#define	free_bytestr(s)	task_mem_free((task *) 0, (caddr_t) (s)->ptr); (s)->ptr = (byte *) 0; (s)->len = (s)->type = 0

#define	PARSE_ERROR	yyerror(parse_error); yynerrs++; YYERROR;
#define	PROTO_SEEN	if (protos_seen & (1 << parse_proto)) {\
    sprintf(parse_error, "parse_proto_seen: duplicate %s clause",\
		gd_lower(trace_state(rt_proto_bits, parse_proto)));\
	PARSE_ERROR; } else BIT_SET(protos_seen, 1 << parse_proto)

#ifdef	PROTO_ASPATHS
static unsigned	aspath_state;
static asmatch_t *aspath_current;

#define	ASPATH_NEXT_STATE	if (aspath_state++ == BITS) { \
	sprintf(parse_error, "too many AS path regexp states"); \
	PARSE_ERROR; \
    }
#endif	/* PROTO_ASPATHS */

%}

/* Global */
%union {
    long	num;
    bytestr	hex;
    charstr	str;
    flag_t	flag;
    time_t	time;
    as_t	as;
    proto_t	proto;
    pmet_t	metric;
    pref_t	pref;
    if_entry	*ifp;
    adv_entry	*adv;
    gw_entry	*gwp;
    sockaddr_un	*sockaddr;
    struct in_addr	in_addr;
    dest_mask	dm;
@BEGIN:	PROTO_OSPF
    struct NBR	*ospf_NBR;
@END:	PROTO_OSPF
#if	defined(PROTO_ASPATHS)
    asmatch_t	*asp_match;
    struct {
	u_short	begin;
	u_short end;
    } asp_range;
    struct {
	flag_t	start[1+ACC/WORD];
	flag_t	state[1+ACC/WORD];
    } asp_stack;
#endif	/* PROTO_ASPATHS */
}

/* Lexer tokens */
%token		L_EOS
%token	<num>	L_NUMBER
%token	<str>	L_STRING L_HNAME L_KEYWORD
%token	<hex>	L_HEXSTRING L_OCTETSTRING L_HEXSTRING_ODD

/* Keyword tokens */    
%token	<num>	T_DIRECT T_INTERFACE T_INTERFACES T_PROTO T_METRIC T_INFINITY
%token	<num>	T_LEX T_PARSE T_CONFIG T_ADV T_DEFAULT T_DEFAULTS
%token	<num>	T_YYDEBUG T_YYSTATE T_YYQUIT T_DEBUG
%token	<num>	T_INCLUDE T_DIRECTORY
%token	<num>	T_ON T_OFF T_GATEWAY T_PREFERENCE T_DEFAULTMETRIC T_NONBROADCAST T_BROADCAST T_TYPE
%token	<num>	T_POINTOPOINT T_MULTICAST T_NETMASK T_DEFINE
%token	<num>	T_NOP	/* Filler for conditional clauses */
/* BGP and EGP */
%token	<num>	T_ASIN T_ASOUT T_NEIGHBOR T_GROUP
%token	<num>	T_VIA
%token	<metric>	T_METRICOUT
%token	<num>	T_GENDEFAULT T_NOGENDEFAULT T_VERSION T_DEFAULTIN T_DEFAULTOUT
@BEGIN:	PROTO_EGP
%token	<num>	T_EGP 
%token	<num>	T_MAXUP T_SOURCENET T_PKTSIZE T_P1 T_P2
%type	<flag>	egp_trace_options
@END:	PROTO_EGP
@BEGIN:	PROTO_BGP
%token	<num>	T_BGP T_HOLDTIME T_ALLOW T_TEST
%type	<num>	bgp_linktype
%type	<flag>	bgp_trace_options
@END:	PROTO_BGP
@BEGIN:	PROTO_ASPATHS
/* AS Paths */    
%token	<num>	T_ASPATH T_ORIGIN T_INCOMPLETE T_ANY
%type	<asp_match>	aspath_match
%type	<asp_stack>	aspath_regex aspath_sum aspath_symbol aspath_term
%type	<asp_range>	aspath_range
%type	<flag>		aspath_origin_list aspath_origins aspath_origin
@END:	PROTO_ASPATHS
/* RIP and HELLO */
%token	<num>	T_TRUSTEDGATEWAYS T_SOURCEGATEWAYS
@BEGIN:	PROTO_RIP
%token	<num>	T_RIP T_NORIPOUT T_NORIPIN T_NOCHECKZERO
%type	<flag>	rip_trace_options rip_interface_option rip_interface_options
%type	<proto>	rip_prop_init
@END:	PROTO_RIP
@BEGIN:	PROTO_HELLO
%token	<num>	T_HELLO T_NOHELLOOUT T_NOHELLOIN
%type	<flag>	hello_trace_options hello_interface_option hello_interface_options
%type	<proto>	hello_prop_init
@END:	PROTO_HELLO
@BEGIN:	PROTO_OSPF
%token <num>	T_OSPF T_OSPF_ASE T_AREA T_NETWORKS T_BACKBONE T_VIRTUALLINK T_STUB
%token <num>	T_RXMITINTERVAL T_INFTRANSDELAY T_ROUTERPRIORITY T_HELLOINTERVAL T_ROUTERDEADINTERVAL
%token <num>	T_POLLINTERVAL T_ROUTERS T_NEIGHBORID T_TRANSITAREA T_TAG
%token <num>	T_ENABLE T_DISABLE T_ELIGIBLE T_MONITORAUTHKEY
%token <num>	T_DD T_REQUEST T_LSU T_ACK T_RECEIVE T_LSA_BLD T_LSA_RX T_LSA_TX T_SPF T_TRAP
%token <num>	T_EXPORTINTERVAL T_EXPORTLIMIT    
%type	<metric>	ospf_cost_option ospf_cost ospf_type_option ospf_type
%type	<metric>	ospf_tag_option ospf_tag_as ospf_tag_as_option ospf_tag
%type	<num>	ospf_auth_type
%type	<hex>	ospf_auth_key
%type	<num>	ospf_area ospf_area_option
%type	<num>	ospf_priority ospf_priority_option ospf_eligible_option
%type	<ospf_NBR>	ospf_router_eligible ospf_router_eligible_list
%type	<flag>	ospf_trace_options ospf_trace_option
%type	<proto>	ospf_prop_init ospf_ase_prop_init export_ospf_ase
@END:	PROTO_OSPF
@BEGIN:	PROTO_IDPR
%token	<num>	T_IDPR T_ENCAP
@END:	PROTO_IDPR
/* SNMP */
@BEGIN:	PROTO_SNMP
%token	<num>	T_SNMP
%token	<port>	T_PORT
%type	<flag>	snmp_trace_options
@END:	PROTO_SNMP
/* Redirects */
%token	<num>	T_REDIRECT T_NOICMPIN T_ICMP
%type	<flag>	redirect_trace_options redirect_interface_option redirect_interface_options
/* Authentication */
%token	<num>	T_AUTHTYPE T_AUTHKEY T_NONE T_SIMPLE
/* Interface */
%token	<num>	T_PASSIVE T_SIMPLEX
/* Control */
/* %token	<num>	T_ANNOUNCE T_NOANNOUNCE T_LISTEN T_NOLISTEN     */
%token	<num>	T_STATIC T_MARTIANS T_RETAIN
%token	<num>	T_EXPORT T_IMPORT T_SUMMARY
%token	<num>	T_HOST T_MASK T_REJECT T_RESTRICT
%type	<dm>	route_dest
%type	<flag>	rtf_options rts_options   
/* AS control */
%token	<num>	T_AS T_ROUTERID T_IGP T_LOCAL
/* Tracing */
%token		T_OPTIONS T_NOINSTALL T_NOSEND
%token	<num>	T_TRACEOPTIONS T_TRACEFILE T_REPLACE
%token	<num>	T_ALL T_GENERAL T_INTERNAL T_EXTERNAL T_ROUTE T_UPDATE T_KERNEL
%token	<num>	T_TASK T_TIMER T_NOSTAMP T_MARK

%type	<num>	number				/* A decimal, hex, or octet string number */
%type	<hex>	byte_string			/* A L_HEXSTRING or L_OCTETSTRING */
%type	<metric>	metric metric_option metric_restrict_option
%type	<time>	time
%type	<num>	onoff_option
%type	<flag>	trace_options trace_option trace_option_global trace_options_none
%type	<flag>	trace_trace_options_none trace_trace_options
%type	<flag>	interface_option_list interface_option
%type	<num>	trace_replace
%type	<proto>	proto_interior proto_exterior control_exterior
%type	<proto>	import_interior export_interior 
%type	<proto> summary_interior
%type	<adv>	summary_list summary summary_masks summary_mask   
%type	<proto> prop_default prop_direct prop_static prop_kernel
%type	<as>	as as_identity
%type	<adv>	as_list as_list_option
%type	<pref>	preference
%type	<metric>	preference_option preference_restrict_option
%type	<ifp>	interface
%type	<sockaddr>	ip_addr mask host network interface_addr
%type	<in_addr>	in_addr
%type	<gwp>	gateway
%type	<dm>	dest_mask host_mask network_mask
%type	<adv>	interface_adv interface_list interface_all interface_all_adv interface_all_list gateway_list
%type	<adv>	dest_mask_list
%type	<adv>	import_list import_listen import_option
%type	<adv>	prop_source prop_source_list prop_source_option
%type	<adv>	prop_restrict prop_restrict_list prop_restrict_option
%type	<str>	string host_name
%type	<num>	port

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
				trace(TR_CONFIG, 0, "parse: %s yydebug %s ;",
					parse_where(),
					yydebug ? "on" : "off");
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
				trace(TR_CONFIG, 0, "parse: %s yystate %d ;",
					parse_where(),
					parse_state);
#endif	/* YYDEBUG */
			}
		| T_YYQUIT L_EOS
			{
#if	YYDEBUG != 0
				trace(TR_CONFIG, 0, "parse: %s yyquit ;",
					parse_where());
				task_quit(0);
#endif	/* YYDEBUG */
			}
		| '%' T_INCLUDE string L_EOS
			{
			    char *name = $3.ptr;

			    switch (*name) {
			    case '/':
				break;

			    default:
				name = task_mem_malloc((task *) 0, strlen(name) + strlen(parse_directory) + 2);

				strcpy(name, parse_directory);
				strcat(name, "/");
				strcat(name, $3.ptr);
				free_charstr(&$3);
			    }
				
			    if (parse_include(name)) {
				PARSE_ERROR;
			    }
			    /* String is freed by parse_eof() */
			}
		| '%' T_DIRECTORY string L_EOS
			{
#ifndef	vax11c
			    struct stat stbuf;

			    if (stat($3.ptr, &stbuf) < 0) {
				sprintf(parse_error, "stat(%s): %m",
					$3.ptr);
				PARSE_ERROR;
			    }

			    switch (stbuf.st_mode & S_IFMT) {
			    case S_IFDIR:
				break;

			    default:
				sprintf(parse_error, "%s is not a directory",
					$3.ptr);
				PARSE_ERROR;
			    }
#endif	/* vax11c */
			    if (parse_directory) {
				free_string(parse_directory);
			    }
			    if ($3.ptr[$3.len-1] == '/') {
				$3.ptr[$3.len-1] = (char) 0;
			    }
			    parse_directory = $3.ptr;
			    trace(TR_PARSE, 0, "parse: %s included file prefeix now %s",
				  parse_where(),
				  parse_directory);
			}
		;

/*  */

trace_statement	: T_TRACEOPTIONS trace_trace_options_none L_EOS
			{
			    if ($2) {
				if (trace_flags) {
				    trace_flags = trace_flags_save = $2;
				    trace_display(trace_flags, TR_PARSE);
				} else if (trace_opened) {
				    trace_flags = trace_flags_save = $2;
				    trace_display(trace_flags, TR_PARSE);
				}
			    } else {
				if (trace_flags) {
				    trace_flags = trace_flags_save = $2;
				    trace_display(trace_flags, TR_PARSE);
				    trace_off();
				}
			    }
			}
		| T_TRACEFILE string trace_replace L_EOS
			{
			    if (trace_flags) {
				trace_flags_save = trace_flags;
				trace_off();
			    }
			    if (trace_file) {
				free_string(trace_file);
			    }
			    trace_on((trace_file = $2.ptr), $3);
			}
		;

trace_replace	: /* Empty */	{ $$ = TRUE; }
		| T_REPLACE	{ $$ = FALSE; }
		;

trace_trace_options_none : T_NONE					{ $$ = (flag_t) 0; }
		| trace_trace_options					{ $$ = $$; }
		;
		
trace_trace_options	: trace_option					{ $$ = $1; }
		| trace_option_global					{ $$ = $1; }
		| trace_trace_options trace_option			{ $$ = $1 | $2; }
		| trace_trace_options trace_option_global		{ $$ = $1 | $2; }
		;

trace_options_none : T_NONE						{ $$ = (flag_t) 0; }
		| trace_options						{ $$ = $1; }

trace_options	: trace_option						{ $$ = $1; }
		| trace_options trace_option				{ $$ = $1 | $2; }
		;

/* Trace options that can only be specified globally */
trace_option_global	: T_NOSTAMP	{ $$ = TR_NOSTAMP; }
		| T_MARK	{ $$ = TR_MARK; }
		| T_LEX		{ $$ = TR_LEX; }
		| T_PARSE	{ $$ = TR_PARSE; }
		| T_CONFIG	{ $$ = TR_CONFIG; }
		| T_ADV		{ $$ = TR_ADV; }
		;

/* Trace options that can be specified anywhere */
trace_option	: T_ALL		{ $$ = TR_ALL; }
		| T_GENERAL	{ $$ = TR_INT|TR_EXT|TR_RT; }
		| T_INTERNAL	{ $$ = TR_INT; }
		| T_EXTERNAL	{ $$ = TR_EXT; }
		| T_ROUTE	{ $$ = TR_RT; }
		| T_UPDATE	{ $$ = TR_UPDATE; }
		| T_TASK	{ $$ = TR_TASK; }
		| T_TIMER	{ $$ = TR_TIMER; }
		| T_PROTO	{ $$ = TR_PROTOCOL; }
		| T_KERNEL	{ $$ = TR_KRT; }
@BEGIN:	PROTO_BGP
		| T_BGP		{ $$ = TR_BGP; }
@END:	PROTO_BGP
@BEGIN:	PROTO_EGP
		| T_EGP		{ $$ = TR_EGP; }
@END:	PROTO_EGP
@BEGIN:	PROTO_HELLO
		| T_HELLO	{ $$ = TR_HELLO; }
@END:	PROTO_HELLO
@BEGIN:	PROTO_ICMP
		| T_ICMP	{ $$ = TR_ICMP; }
@END:	PROTO_ICMP
@BEGIN:	PROTO_OSPF
		| T_OSPF	{ $$ = TR_OSPF; }
@END:	PROTO_OSPF
@BEGIN:	PROTO_RIP
		| T_RIP		{ $$ = TR_RIP; }
@END:	PROTO_RIP
@BEGIN:	PROTO_SNMP
		| T_SNMP	{ $$ = TR_SNMP; }
@END:	PROTO_SNMP
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
		: T_AS as L_EOS
			{
			    rt_autonomous_system = $2;
			    trace(TR_CONFIG, 0, "parse: %s autonomoussystem %d ;",
				  parse_where(),
				  rt_autonomous_system);
			}
    		| T_ROUTERID interface L_EOS
			{
			    if (BIT_TEST($2->int_state, IFS_LOOPBACK)) {
				sprintf(parse_error, "parse: interface %A (%.*s) not valid for routerid",
					$2->int_addr,
					IFNAMSIZ, $2->int_name);
				PARSE_ERROR;
			    }
			    if (rt_inet_routerid && !sockaddrcmp(rt_inet_routerid, IF_LCLADDR($2))) {
				/* Free the old one if not defined or they are not the same */
				sockfree(rt_inet_routerid);
				rt_inet_routerid = (sockaddr_un *) 0;
			    }
			    if (!rt_inet_routerid) {
				/* Duplicate this one if they are different */
				rt_inet_routerid = sockdup(IF_LCLADDR($2));
			    }
			    trace(TR_CONFIG, 0, "parse: %s routerid %A ;",
				  parse_where(),
				  rt_inet_routerid);
			}
		| T_MARTIANS '{' dest_mask_list '}' L_EOS
			{
			    adv_entry *adv = adv_compress($3);
			    
			    martian_list = parse_adv_append(martian_list, adv, TRUE);
			    if (!martian_list) {
				PARSE_ERROR;
			    }
			    parse_adv_list("martians", (char *)0, (adv_entry *)0, adv);
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


option		: T_NOINSTALL
			{
			    krt_install = FALSE;
			}
		| T_GENDEFAULT preference_option
			{
			    rt_default_needed = TRUE;
			    if (PARSE_METRIC_ISSET(&$2)) {
				rt_default_preference = $2.metric;
			    }
			}
		| T_NOSEND
			{
			    task_newstate(TASKS_NOSEND, 0);
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
			    parse_proto = RTPROTO_DIRECT;
			}
			'{' interface_stmts '}' L_EOS
			{
			    PROTO_SEEN;
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
		: T_OPTIONS
			{
			    /* Initialize variables used */
			    PARSE_METRIC_CLEAR(&parse_metric);
			    PARSE_METRIC_CLEAR(&parse_preference);
			}
    		interface_all_list interface_option_list
			{
			    parse_interface($3, $4, &parse_metric, &parse_preference);
			}
		| T_DEFINE host
			{
			    bzero((caddr_t) &parse_ifi, sizeof (parse_ifi));

			    parse_ifi.ifi_addr = $2;

			    BIT_SET(parse_ifi.ifi_state, IFS_CONFIG);
			}
			interface_type_options interface_common_options
			{
			    static u_int ifindex = 0;
			    
			    (void) sprintf(parse_ifi.ifi_name,
					   "config%u",
					   ifindex);
			    
			    if_conf_add(&parse_ifi);
			} 
		;

interface_type_options
		: T_BROADCAST host
			{
			    parse_ifi.ifi_broadaddr = $2;
			    BIT_SET(parse_ifi.ifi_state, IFS_BROADCAST);
			}
		| T_POINTOPOINT host
			{
			    parse_ifi.ifi_lcladdr = $2;
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
			    parse_ifi.ifi_subnetmask = $2;
			}
		| T_MULTICAST
			{
#ifdef	HAVE_MULTICAST
			    BIT_SET(parse_ifi.ifi_state, IFS_MULTICAST);
#else	/* HAVE_MULTICAST */
			    (void) sprintf(parse_error,
					   "system does not support MULTICAST");
			    PARSE_ERROR;
#endif	/* HAVE_MULTICAST */
			}
		;

interface_option_list
		: interface_option
			{
			    $$ = $1;
			}
		| interface_option_list interface_option
			{
			    $$ = $1 | $2;
			}
		;

interface_option
		: T_METRIC metric
			{
			    parse_metric = $2;
			    if (parse_metric_check(RTPROTO_DIRECT, &parse_metric)) {
				PARSE_ERROR;
			    }
			    $$ = 0;
			}
		| T_PREFERENCE preference
			{
			    PARSE_METRIC_SET(&parse_preference, $2);
			    $$ = 0;
			}
		| T_PASSIVE
			{
			    $$ = IFS_NOAGE;
			}
		| T_SIMPLEX
			{
			    $$ = IFS_SIMPLEX;
			}
		;

interface_all_list
		: T_ALL
			{
			    $$ = adv_alloc(ADVFT_ANY|ADVF_FIRST, (proto_t) 0, 1);
			}
		| interface_all
			{
			    BIT_SET($1->adv_flag, ADVF_FIRST);
			    $$ = $1;
			}
		| interface_all_list interface_all
			{
			    $$ = parse_adv_append($1, $2, TRUE);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		;

interface_all	: interface_all_adv
			{
			    switch ($1->adv_flag & ADVF_TYPE) {

			    case ADVFT_IFN:
				trace(TR_PARSE, 0, "parse: %s INTERFACE: %.*s*",
				      parse_where(),
				      IFNAMSIZ,
				      $$->adv_ifn);
				break;
				
			    case ADVFT_IFP:
				trace(TR_PARSE, 0, "parse: %s INTERFACE: %A (%.*s)",
				      parse_where(),
				      $$->adv_ifp->int_addr,
				      IFNAMSIZ, $$->adv_ifp->int_name);
				break;
			    }
			}
		;

interface_all_adv
		: ip_addr
			{
			    $$ = adv_alloc(ADVFT_IFP, (proto_t) 0, 1);

			    $$->adv_ifp = if_withaddr($1);
			    if (!$$->adv_ifp) {
				(void) sprintf(parse_error, "Invalid interface at '%A'",
					       $1);
				PARSE_ERROR;
			    }
			    sockfree($1);
			}
		| host_name
			{
			    sockaddr_un *addr;

			    if (addr = parse_addr_hostname(&$1)) {
				$$ = adv_alloc(ADVFT_IFP, (proto_t) 0, 1);

				$$->adv_ifp = if_withaddr(addr);
				if (!$$->adv_ifp) {
				    (void) sprintf(parse_error, "Invalid interface at '%s'",
						   $1);
				    PARSE_ERROR;
				}
			    } else {
				if ($1.type == L_KEYWORD && $1.len <= IFNAMSIZ) {
				    $$ = adv_alloc(ADVFT_IFN, (proto_t) 0, 1);
				    strncpy($$->adv_ifn, (const char *) $1.ptr, $1.len);
				} else {
				    PARSE_ERROR;
				}
			    }
			    free_charstr(&$1);
			}
		;

interface_list	: interface_adv
			{
			    BIT_SET($1->adv_flag, ADVF_FIRST);
			    $$ = $1;
			}
		| interface_list interface_adv
			{
			    $$ = parse_adv_append($1, $2, TRUE);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		;

interface_adv	: interface
			{
			    $$ = adv_alloc(ADVFT_IFP, (proto_t) 0, 1);
			    $$->adv_ifp = $1;
			}
		;

interface	: interface_addr
			{
			    $$ = if_withaddr($1);
			    if (!$$) {
				(void) sprintf(parse_error, "Invalid interface at '%A'",
					       $1);
				PARSE_ERROR;
			    }
			    sockfree($1);
			    trace(TR_PARSE, 0, "parse: %s INTERFACE: %A (%.*s)",
				  parse_where(),
				  $$->int_addr,
				  IFNAMSIZ, $$->int_name);
			}
		;

interface_addr	: ip_addr
			{
			    $$ = $1;
			}
		| host_name
			{
			    sockaddr_un *addr;
			    
			    addr = parse_addr_hostname(&$1);
			    if (!addr) {
				PARSE_ERROR;
			    }
			    $$ = sockdup(addr);
			    free_charstr(&$1);
			}
		;

/*  */

proto_order	: /* Empty */
			{
				if (parse_new_state(PS_PROTO)) {
					PARSE_ERROR;
				}
			}
		;

proto_statement	: redirect_statement L_EOS
@BEGIN:	PROTO_BGP
		| bgp_statement L_EOS
@END:	PROTO_BGP
@BEGIN:	PROTO_EGP
		| egp_statement L_EOS
@END:	PROTO_EGP
@BEGIN:	PROTO_HELLO
		| hello_statement L_EOS
@END:	PROTO_HELLO
@BEGIN:	PROTO_OSPF
    		| ospf_statement L_EOS
@END:	PROTO_OSPF
@BEGIN:	PROTO_IDPR
    		| idpr_statement L_EOS
@END:	PROTO_IDPR
@BEGIN:	PROTO_RIP
		| rip_statement L_EOS
@END:	PROTO_RIP
@BEGIN:	PROTO_SNMP
		| snmp_statement L_EOS
@END:	PROTO_SNMP
		;

/*  */

@BEGIN:	PROTO_RIP

rip_statement	: T_RIP
			{
			    parse_proto = RTPROTO_RIP;
			    parse_gwlist = &rip_gw_list;

			    rip_var_init();
			}
    		onoff_option rip_group
			{
			    PROTO_SEEN;

			    switch ($3) {
			    case T_OFF:
				BIT_RESET(rip_flags, RIPF_ON);
				break;

			    case T_ON:
				BIT_SET(rip_flags, RIPF_ON);
				break;
			    }
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
		| T_TRACEOPTIONS rip_trace_options
			{
			    rip_trace_flags =  $2;
			}
		| T_NOCHECKZERO
			{
			    BIT_SET(rip_flags, RIPF_NOCHECK);
			}
		| T_INTERFACE
			{
			    /* Initialize variables used */
			    PARSE_METRIC_CLEAR(&parse_metric);
			    PARSE_METRIC_CLEAR(&parse_preference);
			}
		interface_all_list rip_interface_options
			{
			    parse_interface($3, $4, (pmet_t *) 0, (pmet_t *) 0);
			}
		| T_TRUSTEDGATEWAYS gateway_list
			{
			    rip_n_trusted += parse_gw_flag($2, RTPROTO_RIP, GWF_TRUSTED);
			    if (!rip_n_trusted) {
				PARSE_ERROR;
			    }
			}
		| T_SOURCEGATEWAYS gateway_list
			{
			    rip_n_source += parse_gw_flag($2, RTPROTO_RIP, GWF_SOURCE);
			    if (!rip_n_source) {
				PARSE_ERROR;
			    }
			    BIT_SET(rip_flags, RIPF_SOURCE);
			}
		;

rip_interface_options
		: rip_interface_option
			{
			    $$ = $1;
			}
		| rip_interface_options rip_interface_option
			{
			    $$ = $1 | $2;
			}
		;

rip_interface_option
		: T_NORIPIN
			{
			    $$ = IFS_NORIPIN;
			}
		| T_NORIPOUT
			{
			    $$ = IFS_NORIPOUT;
			}
		;

rip_trace_options
		: trace_options
    		;


rip_prop_init	: T_RIP
			{
				$$ = parse_proto = RTPROTO_RIP;
				parse_gwlist = &rip_gw_list;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
			}
		;

@END:	PROTO_RIP

/*  */

@BEGIN:	PROTO_HELLO

hello_statement	: T_HELLO
			{
			    parse_proto = RTPROTO_HELLO;
			    parse_gwlist = &hello_gw_list;

			    hello_var_init();
			}
		onoff_option hello_group
			{
			    PROTO_SEEN;

			    switch ($3) {
			    case T_OFF:
				BIT_RESET(hello_flags, HELLOF_ON);
				break;

			    case T_ON:
				BIT_SET(hello_flags, HELLOF_ON);
				break;
			    }
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
		| T_TRACEOPTIONS hello_trace_options
			{
			    hello_trace_flags =  $2;
			}
		| T_INTERFACE
			{
			    /* Initialize variables used */
			    PARSE_METRIC_CLEAR(&parse_metric);
			    PARSE_METRIC_CLEAR(&parse_preference);
			}
		interface_all_list hello_interface_options
			{
			    parse_interface($3, $4, (pmet_t *) 0, (pmet_t *) 0);
			}
		| T_TRUSTEDGATEWAYS gateway_list
			{
			    hello_n_trusted += parse_gw_flag($2, RTPROTO_HELLO, GWF_TRUSTED);
			    if (!hello_n_trusted) {
				PARSE_ERROR;
			    }
			}
		| T_SOURCEGATEWAYS gateway_list
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
			{
			    $$ = $1;
			}
		| hello_interface_options hello_interface_option
			{
			    $$ = $1 | $2;
			}
		;

hello_interface_option
		: T_NOHELLOIN
			{
			    $$ = IFS_NOHELLOIN;
			}
		| T_NOHELLOOUT
			{
			    $$ = IFS_NOHELLOOUT;
			}
		;

hello_trace_options
		: trace_options
    		;


hello_prop_init	: T_HELLO
			{
				$$ = parse_proto = RTPROTO_HELLO;
				parse_gwlist = &hello_gw_list;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
			}
		;
@END:	PROTO_HELLO

    
/*  */

@BEGIN:	PROTO_OSPF

ospf_statement	: T_OSPF
			{
			    if (!rt_inet_routerid) {
				sprintf(parse_error, "Router ID not defined");
				PARSE_ERROR;
			    }
			    if (!ospf.router_id) {
				ospf.router_id = sockdup(rt_inet_routerid);
			    }

			    parse_proto = RTPROTO_OSPF;
			    parse_gwlist = &ospf.gw_list;

			    /* Somewhere around here is where we will figure out which OSPF global structure we are */
			    /* refering to and initialize it once we support multiple instantations of OSPF that is. */
			    /* For now, just initialize the fields in the global structure. */
			    ospf_var_init();
			}
		onoff_option ospf_group
			{
			    PROTO_SEEN;

			    if ($3 == T_OFF) {
				ospf.ospf_admin_stat = OSPF_DISABLED;
				trace(TR_CONFIG, 0, "parse: %s ospf off ;",
				      parse_where());
			    } else {
				if (ospf_parse_valid_check(parse_error)) {
				    PARSE_ERROR;
				}
				ospf.ospf_admin_stat = OSPF_ENABLED;
			    }
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
		| T_TRACEOPTIONS ospf_trace_options
			{
			    ospf.trace_flags = $2;
			}
		| T_EXPORTINTERVAL time
			{
			    ospf.export_interval = $2;
			}
		| T_EXPORTLIMIT number
			{
			    ospf.export_limit = $2;
			}
		| T_MONITORAUTHKEY ospf_auth_key
			{
			    ospf.mon_authtype = OSPF_AUTH_SIMPLE;
			    bcopy((caddr_t) $2.ptr, (caddr_t) ospf.mon_authkey, OSPF_AUTH_SIZE);

			    free_bytestr(&$2);
			}
		| ospf_area_option
			{
			    if ($1 != OSPF_BACKBONE && (ospf.vcnt || ospf.acnt)) {
				sprintf(parse_error, "'backbone' area must be specified last");
				PARSE_ERROR;
			    }
			    ospf_AREA = ospf_parse_area_alloc($1);
			    ospf_AREA->authtype = OSPF_AUTH_NONE;		/* Default to no authentication */
			    
			}
		'{' ospf_area_stmts '}'
			{
			    /* XXX - ospf_parse_area_check(ospf_AREA); */
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
		| T_TAG ospf_tag	/* XXX - need it to be ospf_tag_as */
			{
			    ospf.export_tag = htonl($2.metric);
			}
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
			    ospf_AREA->authtype = $2;
			}
		| T_STUB ospf_cost_option
			{
			    if (ospf_AREA->area_id == OSPF_BACKBONE) {
				(void) sprintf(parse_error, "stub option not valid for backbone");
				PARSE_ERROR;
			    }
			    
			    if (PARSE_METRIC_ISSET(&$2)) {
				ospf_AREA->ext_option = EXT_OPT_STUB;
				ospf_AREA->dflt_metric = $2.metric;
			    } else {
				ospf_AREA->ext_option = EXT_OPT_NODEFAULT;
			    }
			}    
		| T_NETWORKS '{' dest_mask_list '}'
			{
			    adv_entry *adv;

			    if (ospf_AREA->nrcnt) {
				(void) sprintf(parse_error, "net range already specified");
				PARSE_ERROR;
			    }

			    /* Install each of the entries */
			    ADV_LIST($3, adv) {
				ospf_add_net(ospf_AREA,
					      sock2ip(adv->adv_dm.dm_dest),
					      sock2ip(adv->adv_dm.dm_mask));
			    } ADV_LIST_END($3, adv) ;

			    adv_free_list($3);
			}
		| T_INTERFACE ospf_interface_groups
			{
			    ospf_parse_intf_check(ospf_INTF);
			}
    		| T_VIRTUALLINK T_NEIGHBORID ip_addr T_TRANSITAREA ospf_area
			{
			    char ospf_error[BUFSIZ];

			    ospf_INTF = (struct INTF *) 0;

			    if (ospf_AREA->area_id != OSPF_BACKBONE) {
				sprintf(parse_error, "virtual links only allowed in 'backbone' area");
				PARSE_ERROR;
			    }
			    
			    ospf_INTF = ospf_parse_virt_alloc(ospf_AREA, ospf_error);

			    if (!ospf_INTF) {
				sprintf(parse_error, "virtual-link: %s",
					ospf_error);
				PARSE_ERROR;
			    }

			    /* Neighbor ID */
			    ospf_INTF->nbr.nbr_id = $3;

			    /* Transit area */
			    if (!$5) {
				sprintf(parse_error, "transit-area can not be the `backbone` area");
				PARSE_ERROR;
			    }
			    ospf_INTF->transarea = ospf_parse_trans_area($5);
			    if (!ospf_INTF->transarea) {
				sprintf(parse_error, "transit-area not previously specified");
				PARSE_ERROR;
			    }
			}
		'{' ospf_common_options '}'
		;

ospf_interface_groups
		: interface ospf_cost_option
			{
			    char ospf_error[BUFSIZ];


			    ospf_INTF = (struct INTF *) 0;

			    if (BIT_TEST($1->int_state, IFS_POINTOPOINT)) {
				ospf_INTF = ospf_parse_intf_alloc(ospf_AREA, POINT_TO_POINT, $1, ospf_error);
			    } else if (BIT_TEST($1->int_state, IFS_MULTICAST)) {
				ospf_INTF = ospf_parse_intf_alloc(ospf_AREA, BROADCAST, $1, ospf_error);
			    } else {
				if (BIT_TEST(int_flags, IFS_MULTICAST)) {
				    strcpy(ospf_error, "multicast not supported on this interface");
				} else {
				    strcpy(ospf_error, "system does not support multicast");
				}
			    }

			    if (!ospf_INTF) {
				sprintf(parse_error, "interface %A(%.*s): %s",
					$1->int_addr,
					IFNAMSIZ, $1->int_name,
					ospf_error);
				PARSE_ERROR;
			    }

			    if (PARSE_METRIC_ISSET(&$2)) {
				ospf_INTF->cost = $2.metric;
			    } else {
				ospf_INTF->cost = $1->int_metric + OSPF_HOP;
			    }
			}
		'{' ospf_common_options '}'
    		| interface T_NONBROADCAST ospf_cost_option
			{
			    char ospf_error[BUFSIZ];

			    ospf_INTF = (struct INTF *) 0;
			    PARSE_METRIC_CLEAR(&parse_metric);

			    if (BIT_TEST($1->int_state, IFS_POINTOPOINT)) {
				strcpy(ospf_error, "non-broadcast specification not valid for a point-to-point interface");
			    } else {
				ospf_INTF = ospf_parse_intf_alloc(ospf_AREA, NONBROADCAST, $1, ospf_error);
			    }

			    if (!ospf_INTF) {
				sprintf(parse_error, "interface %A(%s): %s",
					$1->int_addr,
					ospf_error);
				PARSE_ERROR;
			    }

			    if (PARSE_METRIC_ISSET(&$3)) {
				ospf_INTF->cost = $3.metric;
			    } else {
				ospf_INTF->cost = $1->int_metric + OSPF_HOP;
			    }
			}
		'{' ospf_nobroadcast_options '}'
		;

ospf_common_options	: /* Empty */
		| ospf_common_options ospf_common_option L_EOS
		| ospf_common_options error L_EOS
			{
				yyerrok;
			}
		;

ospf_nobroadcast_options	: /* Empty */
		| ospf_nobroadcast_options ospf_common_option L_EOS
		| ospf_nobroadcast_options ospf_nobroadcast_option L_EOS
		| ospf_nobroadcast_options error L_EOS
			{
				yyerrok;
			}
		;

ospf_common_option	: T_ENABLE
			{
			    ospf_INTF->admstat = OSPF_INTF_ENABLE;
			}
		| T_DISABLE
			{
			    ospf_INTF->admstat = OSPF_INTF_DISABLE;
			}
		| T_RXMITINTERVAL time
			{
			    if (parse_limit_check("retransmit-interval", $2, OSPF_LIMIT_RETRANSMITINTERVAL)) {
				PARSE_ERROR;
			    }
			    ospf_INTF->retrans_timer = $2;
			}
		| T_INFTRANSDELAY time
			{
			    if (parse_limit_check("transit-delay", $2, OSPF_LIMIT_TRANSITDELAY)) {
				PARSE_ERROR;
			    }
			    ospf_INTF->transdly = $2;
			}
		| T_ROUTERPRIORITY ospf_priority
			{
			    ospf_INTF->pri = $2;

			    switch (ospf_INTF->type) {
			    case BROADCAST:
			    case NONBROADCAST:
				ospf_INTF->nbr.pri = $2;
				break;
			    }
			}
		| T_HELLOINTERVAL time
			{
			    if (parse_limit_check("hello-interval", $2, OSPF_LIMIT_HELLOINTERVAL)) {
				PARSE_ERROR;
			    }
			    ospf_INTF->hello_timer = $2;
			}
		| T_ROUTERDEADINTERVAL time
			{
			    if (parse_limit_check("router-dead-interval", $2, OSPF_LIMIT_ROUTERDEADINTERVAL)) {
				PARSE_ERROR;
			    }
			    ospf_INTF->dead_timer = $2;
			}
		| T_AUTHKEY ospf_auth_key
			{
			    /* Side-effect: The authentication type must be specified first */

			    switch (ospf_AREA->authtype) {
			    case OSPF_AUTH_NONE:
				sprintf(parse_error, "authentication-key specified when authentication-type is none");
				PARSE_ERROR;
				break;

			    case OSPF_AUTH_SIMPLE:
				/* Simple password */
				bcopy((caddr_t) $2.ptr, (caddr_t) ospf_INTF->authkey, OSPF_AUTH_SIZE);
				break;

			    default:
				sprintf(parse_error, "unknown authentication type: %d");
				PARSE_ERROR;
				break;
			    }

			    free_bytestr(&$2);
			}
		;

ospf_nobroadcast_option
		: T_POLLINTERVAL time
			{
			    if (parse_limit_check("poll-interval", $2, OSPF_LIMIT_POLLINTERVAL)) {
				PARSE_ERROR;
			    }
			    ospf_INTF->poll_timer = $2;
			}
		| T_ROUTERS '{' ospf_router_eligible_list '}'
			{
			    struct NBR *nbr, *next = $3;

			    while (nbr = next) {
				next = nbr->next;
				nbr->next = (struct NBR *) 0;

				nbr_enq(ospf_INTF, nbr);
			    }
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
			    if (parse_limit_check("export-type", $1, OSPF_LIMIT_EXPORTTYPE)) {
				PARSE_ERROR;
			    }
			    PARSE_METRIC_SET(&$$, $1);
			}
		;

/* OSPF External route tag */
ospf_tag_as_option
		: /* Empty */
			{
			    PARSE_METRIC_CLEAR(&$$);
			}
		| T_TAG ospf_tag_as
			{
			    $$ = $2;
			}
		;

ospf_tag_as	: ospf_tag
			{
			    $$ = $1;
			}
		| T_AS
			{
			    PARSE_METRIC_INFINITY(&$$);
			}
		;

ospf_tag_option	: /* Empty */
			{
			    PARSE_METRIC_CLEAR(&$$);
			}
		| T_TAG ospf_tag
			{
			    $$ = $2;
			}
		;

ospf_tag	: number
			{
			    if (parse_limit_check("external-route-tag", $1, OSPF_LIMIT_TAG)) {
				PARSE_ERROR;
			    }
			    PARSE_METRIC_SET(&$$, $1);
			}
/* XXX - various tag options */
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
			    if (parse_limit_check("area-number", $1, OSPF_LIMIT_AREA)) {
				PARSE_ERROR;
			    }
			    $$ = htonl($1);
			}
		;

ospf_auth_type	: L_NUMBER
			{
			    if (parse_limit_check("authentication-type", $1, OSPF_LIMIT_AUTHTYPE)) {
				PARSE_ERROR;
			    }
			    $$ = $1;
			}
		| T_NONE
			{
			    $$ = OSPF_AUTH_NONE;
			}
		| T_SIMPLE
			{
			    $$ = OSPF_AUTH_SIMPLE;
			}
		;

ospf_auth_key	: string
			{
			    if ($1.len > OSPF_AUTH_SIZE) {
				sprintf(parse_error, "authentication-key \"%s\"%d longer than %d characters",
					$1.ptr,
					$1.len,
					OSPF_AUTH_SIZE);
				PARSE_ERROR;
			    }

			    $$.type = $1.type;
			    $$.len = OSPF_AUTH_SIZE;
			    $$.ptr = (byte *) task_mem_calloc((task *) 0, 1, OSPF_AUTH_SIZE);
			    
			    /* Left justify the authentication key */
			    strncpy((caddr_t) $$.ptr, $1.ptr, $1.len);

			    free_charstr(&$1);
			}
		| L_NUMBER
			{
			    int offset = OSPF_AUTH_SIZE - sizeof ($1);

			    $$.type = L_NUMBER;
			    $$.len = OSPF_AUTH_SIZE;
			    $$.ptr = (byte *) task_mem_calloc((task *) 0, 1, OSPF_AUTH_SIZE);

			    /* Right justify the authentication key */
			    bcopy((caddr_t) &$1, (caddr_t) $$.ptr + offset, sizeof($1));
			}
		| byte_string
			{
			    int offset = OSPF_AUTH_SIZE - $1.len;

			    if (offset < 0) {
				sprintf(parse_error, "authentication-key longer than %d characters",
					sizeof (ospf_INTF->authkey));
				PARSE_ERROR;
			    }

			    $$.type = $1.type;
			    $$.len = OSPF_AUTH_SIZE;
			    $$.ptr = (byte *) task_mem_calloc((task *) 0, 1, OSPF_AUTH_SIZE);

			    /* Right justify the authentication key */
			    bcopy((caddr_t) $1.ptr, (caddr_t) $$.ptr + offset, $1.len);

			    free_bytestr(&$1);
			}
    		;

ospf_router_eligible_list
		: ospf_router_eligible L_EOS
			{
			    $$ = $1;
			}
		| ospf_router_eligible_list ospf_router_eligible L_EOS
			{
			    ($$ = $2)->next = $1;
			}
		| ospf_router_eligible_list error L_EOS
			{
			    yyerrok;
			}
    		;

ospf_router_eligible
		: gateway ospf_eligible_option
			{
			    $$ = (struct NBR *) task_mem_calloc((task *) 0, 1, sizeof (struct NBR));

			    $$->nbr_addr = sockdup($1->gw_addr);
			    $$->pri = $2;
			    $$->ifp = ospf_INTF->ifp;
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

ospf_priority_option	: /* Empty */
			{
			    $$ = 0;
			}
		| T_ROUTERPRIORITY ospf_priority
			{
			    $$ = $2;
			}
		;

ospf_priority	: L_NUMBER
			{
			    if (parse_limit_check("priority", $1, OSPF_LIMIT_DRPRIORITY)) {
				PARSE_ERROR;
			    }
			    $$ = $1;
			}
		;

ospf_prop_init	: T_OSPF
			{
				$$ = parse_proto = RTPROTO_OSPF;
				parse_gwlist = (gw_entry **) 0;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
			}
		;

ospf_ase_prop_init
		: T_OSPF_ASE
			{
				/* Make sure this PS type is known */
				adv_psfunc_add(RTPROTO_OSPF_ASE, &ospf_adv_psfunc);

				$$ = parse_proto = RTPROTO_OSPF_ASE;
				parse_gwlist = (gw_entry **) 0;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
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
		: trace_option			{ $$ = $1; }
		| T_DD				{ $$ = TR_OSPF_DD; }
		| T_REQUEST			{ $$ = TR_OSPF_REQ; }
		| T_LSU				{ $$ = TR_OSPF_LSU; }
		| T_ACK				{ $$ = TR_OSPF_ACK; }
		| T_RECEIVE			{ $$ = TR_OSPF_RX; }
		| T_LSA_BLD			{ $$ = TR_OSPF_LSA_BLD; }
		| T_LSA_TX			{ $$ = TR_OSPF_LSA_TX; }
		| T_LSA_RX			{ $$ = TR_OSPF_LSA_RX; }
		| T_SPF				{ $$ = TR_OSPF_SPF; }
		| T_TRAP			{ $$ = TR_OSPF_TRAP; }
		;


@END:	PROTO_OSPF
    
/*  */

@BEGIN:	PROTO_IDPR

idpr_statement	: T_IDPR onoff_option T_ENCAP onoff_option string
			{
			    parse_proto = RTPROTO_IDPR;
			    PROTO_SEEN;
			    
			    doing_idpr = ($2 == T_OFF) ? FALSE : TRUE;
			    idpr_encap_active = ($4 == T_OFF) ? FALSE : TRUE;
			    trace(TR_CONFIG, 0, "parse: %s idpr %s encap %s;",
				  parse_where(), 
				  doing_idpr ? "on" : "off",
				  idpr_encap_active ? "on" : "off");
			    strcpy(idpr_db_name,$5.ptr);
 			}
		;

@END:	PROTO_IDPR

/*  */

@BEGIN:	PROTO_EGP

egp_statement	: T_EGP onoff_option
			{
			    parse_proto = RTPROTO_EGP;

			    doing_egp = ($2 == T_ON) ? TRUE : FALSE;

			    egp_var_init();
			}
		egp_group
			{
 			        PROTO_SEEN;

				if (!doing_egp) {
					trace(TR_CONFIG, 0, "parse: %s egp off ;",
					      parse_where());
				} else {
					if (!rt_autonomous_system) {
						(void) sprintf(parse_error, "autonomous-system not specified");
						PARSE_ERROR;
					}
					if (!egp_neighbors) {
						(void) sprintf(parse_error, "no EGP neighbors specified");
						PARSE_ERROR;
					}

#if	defined(PROTO_SNMP)
					egp_sort_neighbors();
#endif	/* defined(PROTO_SNMP) */

					if (BIT_TEST(trace_flags, TR_CONFIG)) {
					    trace(TR_CONFIG, 0, "parse: %s egp on {",
						  parse_where());
					    trace(TR_CONFIG, 0, "parse: %s   preference %d ;",
						  parse_where(),
						  egp_preference);
					    trace(TR_CONFIG, 0, "parse: %s   defaultmetric %d ;",
						  parse_where(),
						    egp_default_metric);

					    gr_ngp = (egp_neighbor *) 0;
					    EGP_LIST(ngp) {
						if (gr_ngp != ngp->ng_gr_head) {
						    if (gr_ngp) {
							trace(TR_CONFIG, 0, "parse: %s   } ;",
							      parse_where());
						    }
						    gr_ngp = ngp->ng_gr_head;
						    tracef("parse: %s   group",
							   parse_where());
						    if (BIT_TEST(ngp->ng_options, NGO_VERSION)) {
							tracef(" version %d", ngp->ng_version);
						    }
						    if (BIT_TEST(ngp->ng_options, NGO_MAXACQUIRE)) {
							tracef(" maxup %d", ngp->ng_gr_acquire);
						    }
						    if (BIT_TEST(ngp->ng_options, NGO_ASIN)) {
							tracef(" asin %d", ngp->ng_asin);
						    }
						    if (BIT_TEST(ngp->ng_options, NGO_ASOUT)) {
							tracef(" asout %d", ngp->ng_asout);
						    }
						    if (BIT_TEST(ngp->ng_options, NGO_PREFERENCE)) {
							tracef(" preference %d", ngp->ng_preference);
						    }
						    trace(TR_CONFIG, 0, " {");
						}
						tracef("parse: %s     neighbor %s",
						       parse_where(),
						       ngp->ng_name);
 						if (BIT_TEST(ngp->ng_options, NGO_P1)) {
 						    tracef(" p1 %#T",
 							   ngp->ng_P1);
 						}
 						if (BIT_TEST(ngp->ng_options, NGO_P2)) {
 						    tracef(" p2 %#T",
 							   ngp->ng_P2);
 						}
						if (BIT_TEST(ngp->ng_options, NGO_INTERFACE)) {
						    tracef(" intf %A",
							   ngp->ng_ifp->int_addr);
						}
						if (BIT_TEST(ngp->ng_options, NGO_SADDR)) {
						    tracef(" sourcenet %A",
							   ngp->ng_saddr);
						}
						if (BIT_TEST(ngp->ng_options, NGO_GATEWAY)) {
						    tracef(" gateway %A",
							   ngp->ng_gateway);
						}
#ifdef	VIA_HACK
						if (BIT_TEST(ngp->ng_options, NGO_VIA)) {
						    tracef(" via %A",
							   ngp->ng_via);
						}
#endif	/* VIA_HACK */
						if (BIT_TEST(ngp->ng_options, NGO_METRICOUT)) {
						    tracef(" egpmetricout %d", ngp->ng_metricout);
						}
						if (BIT_TEST(ngp->ng_options, NGO_NOGENDEFAULT)) {
						    tracef(" nogendefault");
						}
						if (BIT_TEST(ngp->ng_options, NGO_DEFAULTIN)) {
						    tracef(" importdefault");
						}
						if (BIT_TEST(ngp->ng_options, NGO_DEFAULTOUT)) {
						    tracef(" exportdefault");
						}
						trace(TR_CONFIG, 0, " ;");
					    } EGP_LIST_END ;
 					    trace(TR_CONFIG, 0, "parse: %s   } ;",
						  parse_where());
 					    trace(TR_CONFIG, 0, "parse: %s } ;",
						  parse_where());
					}
				}
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
		| T_DEFAULTMETRIC metric
			{
			    if (parse_metric_check(RTPROTO_EGP, &$2)) {
				PARSE_ERROR;
			    }
			    egp_default_metric = $2.metric;
			}
		| T_PKTSIZE number
			{
			    if (parse_limit_check("packetsize", $2, EGP_LIMIT_PKTSIZE)) {
				PARSE_ERROR;
			    }
			    egp_pktsize = $2;
			}
		| T_TRACEOPTIONS egp_trace_options
			{
			    egp_trace_flags =  $2;
			}
		| T_GROUP
			{
			    /* Clear group structure and set fill pointer */
			    bzero((caddr_t) &egp_group, sizeof(egp_group));
			    ngp = &egp_group;
			    ngp->ng_trace_flags = egp_trace_flags;
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
			    ngp = egp_peer_alloc(&egp_group);

			    /* This neighbor is head of the group */
			    if (!gr_ngp) {
				gr_ngp = ngp;
			    }
			    parse_gwlist = &parse_gwp;
			}
		host egp_peer_options
                        {
			    int add = TRUE;
			    egp_neighbor *ngp2;

			    /* Set neighbor's address */
			    ngp->ng_addr = $3;
			    ngp->ng_gw.gw_proto = RTPROTO_EGP;
			    strcpy(ngp->ng_name, inet_ntoa(sock2in(ngp->ng_addr)));

			    /* Set group pointer and count this neighbor */
			    ngp->ng_gr_head = gr_ngp;
			    ngp->ng_gr_index = parse_group_index;
			    gr_ngp->ng_gr_number++;

			    EGP_LIST(ngp2) {
				if (sockaddrcmp_in(ngp->ng_addr, ngp2->ng_addr)) {
				    if (BIT_TEST(ngp2->ng_flags, NGF_DELETE)) {
					if (!egp_neighbor_changed(ngp2, ngp)) {
					    BIT_RESET(ngp2->ng_flags, NGF_DELETE);
					    egp_peer_free(ngp);
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
			    } EGP_LIST_END ;
			    
			    /* Add this neighbor to end of the list */
			    if (add) {
				insque((struct qelem *) ngp, (struct qelem *) egp_neighbor_head.ng_back);
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
		: T_ASIN as
			{
				BIT_SET(ngp->ng_options, NGO_ASIN);
				ngp->ng_asin = $2;
			}
		| T_ASOUT as
			{
				BIT_SET(ngp->ng_options, NGO_ASOUT);
				ngp->ng_asout = $2;
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
		| T_PREFERENCE preference
			{
				BIT_SET(ngp->ng_options, NGO_PREFERENCE);
				ngp->ng_preference = $2;
			}
		| T_TRACEOPTIONS egp_trace_options
			{
			    ngp->ng_trace_flags = egp_trace_flags;
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
		| T_GATEWAY gateway
			{
			    BIT_SET(ngp->ng_options, NGO_GATEWAY);
			    ngp->ng_gateway = sockdup($2->gw_addr);
			    gw_freelist(*parse_gwlist);
			    parse_gwlist = (gw_entry **) 0;
			    parse_gwp = (gw_entry *) 0;
			}
		| T_VIA host
			{
#ifdef	VIA_HACK
			    BIT_SET(ngp->ng_options, NGO_VIA);
			    ngp->ng_via = $2;
#endif	/* VIA_HACK */
			}
		| T_INTERFACE interface
			{
				BIT_SET(ngp->ng_options, NGO_INTERFACE);
				ngp->ng_ifp = $2;
			}
		| T_SOURCENET network
			{
				BIT_SET(ngp->ng_options, NGO_SADDR);
				ngp->ng_saddr = $2;
			}
 		| T_P1 time
 			{
 			    if (parse_limit_check("P1", $2, EGP_P1, MAXHELLOINT)) {
 				PARSE_ERROR;
 			    }
 			    BIT_SET(ngp->ng_options, NGO_P1);
 			    ngp->ng_P1 = $2;
 			}
 		| T_P2 time
 			{
 			    if (parse_limit_check("P2", $2, EGP_P2, MAXPOLLINT)) {
 				PARSE_ERROR;
 			    }
 			    BIT_SET(ngp->ng_options, NGO_P2);
 			    ngp->ng_P2 = $2;
			}
		;

egp_trace_options
		:	trace_options
		;

@END:	PROTO_EGP
    
/*  */

@BEGIN:	PROTO_BGP

bgp_statement	: T_BGP
			{
			    bgp_trace_flags = trace_flags;
			    parse_proto = RTPROTO_BGP;
			}
		onoff_option bgp_group
			{
			    PROTO_SEEN;

			    if ($3 == T_OFF) {
				doing_bgp = FALSE;
				trace(TR_CONFIG, 0, "parse: %s bgp off ;",
				      parse_where());
			    } else {
				doing_bgp = TRUE;
				if (!rt_autonomous_system) {
				    (void) sprintf(parse_error, "autonomous-system not specified");
				    PARSE_ERROR;
				}
				if (!bgp_n_peers) {
				    (void) sprintf(parse_error, "no BGP peers specified");
				    PARSE_ERROR;
				}
			    }
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
				bgp_preference = $2;
			}
		| T_DEFAULTMETRIC metric
			{
			    if (parse_metric_check(RTPROTO_BGP, &$2)) {
				PARSE_ERROR;
			    }
			    bgp_default_metric = $2.metric;
			}
		| T_TRACEOPTIONS bgp_trace_options
			{
			    bgp_trace_flags = $2;
			}
		| T_GROUP T_TYPE bgp_linktype T_ASIN as
			{
			    bgpPeerGroup *bgp2;

			    /* Allocate a Group structure */
			    bgp = task_mem_calloc((task *) 0, 1, sizeof (*bgp));

			    /* Set the type and AS */
			    bgp->bgpg_type = $3;
			    bgp->bgpg_asin = $5;

			    /* Check for duplicates */
			    BGP_GROUP_LIST(bgp2) {
				if (bgp2->bgpg_type == bgp->bgpg_type &&
				    bgp2->bgpg_asin == bgp->bgpg_asin) {

				    /* Identical group */
				    if (BIT_TEST(bp2->bgpg_flags, BGPGF_DELETE)) {

					/* Previous group */
					if (!bgp_group_changed(bgp2, bgp)) {

					    /* Not changed, use old one */
					    BIT_RESET(bgp2->bgpg_flags, BGPF_DELETE);
						
					    task_mem_free((task *) 0, (caddr_t) bgp);

					    bgp = bgp2;
					    break;
					}
				    } else {
					(void) sprintf(parse_error, "duplicate BGP group ASin %d type %s",
						       bgp->bgpg_asin,
						       trace_state(bgp_type_bits, bgp->bgp_type));
					PARSE_ERROR;
				    }
				}
			    } BGP_GROUP_LIST_END ;

			    /* Point at this configuration information */
			    bcp = &bgp->bgp_conf;

			    /* Inherit global trace flags */
			    bgp->bgpg_trace_flags = bgp_trace_flags;
			}
		bgp_group_options '{' bgp_peer_stmts '}'
			{
			    /* Insert on end of group list */
			    if (!bgp_groups) {
				/* First group */
				bgp_groups = bgp;
			    } else {
				bgpPeerGroup *bgp2;

				/* Find end of list and append new one */
				BGP_GROUP_LIST(bgp2) {
				    if (!bgp2->bgpg_next) {
					bgp2->bgpg_next = bgp;
					break;
				    }
				} BGP_GROUP_LIST_END(bgp2) ;
			    }
			}
		;

bgp_group_options
		: /* Empty */
		| bgp_group_options bgp_group_option
		| bgp_group_options bgp_peer_option
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
			    bnp = (bgpPeer *) task_mem_calloc((task *) 0, 1, sizeof(bgpPeer));

			    /* Inherit default configutation */
			    bnp->bgp_conf = bgp->bgp_conf;	/* struct copy */

			    /* Bind to this group */
			    bnp->bgp_group = bgp;
			    
			    parse_gwlist = &parse_gwp;
			}
		host bgp_peer_options
			{
			    /* Set peer address */
			    bnp->bgp_addr = $3;
			    bnp->bgp_gw.gw_proto = RTPROTO_BGP;
			    strcpy(bnp->bgp_name, inet_ntoa(sock2in(bnp->bgp_addr)));

			    /* Add to end of peer list */
			    if (!bgp->bgpg_peers) {

				/* First peer */
				bgp_peers = bnp;
				bgp_n_peers++;
			    } else {
				bgpPeer *bnp2;

				/* Not first peer, search for another */
				BGP_PEER_LIST(bgp, bnp2) {
				    if (sockaddrcmp_in(bnp->bgp_addr, bnp2->bgp_addr)) {

					/* Same peer */
					if (BIT_TEST(bnp2->bgp_flags, BGPF_DELETE)) {

					    /* Old peer */
					    if (!bgp_peer_changed(bnp2, bnp)) {

						/* Identical, use old one */
						BIT_RESET(bnp2->bgp_flags, BGPF_DELETE);
						sockfree(bnp->bgp_addr);
						task_mem_free((task *) 0, (caddr_t) bnp);
						break;
					    } else {
						/* XXX - is this necessary? */
						bnp->bgp_flags = BGPF_WAIT;
					    }
					} else {

					    /* Duplicate peer */
					    (void) sprintf(parse_error, "duplicate BGP peer at %A",
						    bnp->bgp_addr);
					    PARSE_ERROR;
					}
				    }

				    if (!bnp2->bgp_next) {

					/* Append this one to end of list */
					bnp2->bgp_next = bnp;
					bgp_n_peers++;
					break;
				    }
				} BGP_PEER_LISTEND ;
			    }
			}
		;

bgp_group_option : T_ALLOW '{' dest_mask_list '}'
			{
			    adv_entry *adv = adv_compress($3);
			    
			    bgp->allow = parse_adv_append(bgp->allow, adv, TRUE);
			    if (!bgp->allow) {
				PARSE_ERROR;
			    }
			    parse_adv_list("allow", (char *)0, (adv_entry *)0, adv);
			}
		;

bgp_peer_option	: T_METRICOUT metric
			{
			    if (parse_metric_check(RTPROTO_BGP, &$2)) {
				PARSE_ERROR;
			    }
			    BIT_SET(bcp->bgpc_options, BGPO_METRICOUT);
			    bcp->bgpc_metricout = $2.metric;
			}
		| T_ASOUT as
			{
				BIT_SET(bcp->bgpc_options, BGPO_ASOUT);
				bcp->bgpc_asout = $2;
			}
		| T_NOGENDEFAULT
			{
				BIT_SET(bcp->bgpc_options, BGPO_NOGENDEFAULT);
			}
		| T_GATEWAY gateway
			{
				BIT_SET(bcp->bgpc_options, BGPO_GATEWAY);
				bcp->bgpc_gateway = sockdup($2->gw_addr);
				gw_freelist(*parse_gwlist);
				parse_gwlist = (gw_entry **) 0;
				parse_gwp = (gw_entry *) 0;
			}
		| T_PREFERENCE preference
			{
				BIT_SET(bcp->bgpc_options, BGPO_PREFERENCE);
				bcp->bgpc_preference = $2;
			}
		| T_INTERFACE interface
			{
				BIT_SET(bcp->bgpc_options, BGPO_INTERFACE);
				bcp->bgpc_interface = $2;
			}
		| T_HOLDTIME time
			{
				BIT_SET(bcp->bgpc_options, BGPO_HOLDTIME);
				bcp->bgpc_holdtime_out = $2;
			}
		| T_TRACEOPTIONS bgp_trace_options
			{
			    bcp->bgpc_trace_flags = $2;
			}
		| T_VERSION L_NUMBER
			{
			    switch ($2) {
			    case 2:
			    case 3:
				break;
			    default:
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
		;

bgp_linktype	: T_INTERNAL
			{
				$$ = BGPG_INTERNAL
			}
		| T_EXTERNAL
			{
				$$ = BGPG_EXTERNAL;
			}
		| T_TEST
			{
				$$ = BGPG_TEST;
			}
		;

bgp_trace_options
		: trace_options
		;

@END:	PROTO_BGP

/*  */

redirect_statement	: T_REDIRECT
			{
#if	defined(PROTO_ICMP) || defined(ROUTING_SOCKET)
			    redirect_trace_flags = trace_flags;
				redirect_preference = RTPREF_REDIRECT;
			    parse_proto = RTPROTO_REDIRECT;
			    parse_gwlist = &redirect_gw_list;
#endif	/* defined(PROTO_ICMP) || defined(ROUTING_SOCKET) */
			}
		onoff_option redirect_group
			{
#if	defined(PROTO_ICMP) || defined(ROUTING_SOCKET)
			    PROTO_SEEN;

			    if ($3 == T_OFF) {
				BIT_SET(rt_ignore_redirects, 1 << RTPROTO_REDIRECT);
			    } else {
				BIT_RESET(rt_ignore_redirects, 1 << RTPROTO_REDIRECT);
			    }
#endif	/* defined(PROTO_ICMP) || defined(ROUTING_SOCKET) */
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
#if	defined(PROTO_ICMP) || defined(ROUTING_SOCKET)
				redirect_preference = $2;
#endif	/* defined(PROTO_ICMP) || defined(ROUTING_SOCKET) */
			}
		| T_INTERFACE
			{
			    /* Initialize variables used */
			    PARSE_METRIC_CLEAR(&parse_metric);
			    PARSE_METRIC_CLEAR(&parse_preference);
			}
		interface_all_list redirect_interface_options
			{
#if	defined(PROTO_ICMP) || defined(ROUTING_SOCKET)
				parse_interface($3, $4, (pmet_t *) 0, (pmet_t *) 0);
#endif	/* defined(PROTO_ICMP) || defined(ROUTING_SOCKET) */
			}
		| T_TRUSTEDGATEWAYS gateway_list
			{
#if	defined(PROTO_ICMP) || defined(ROUTING_SOCKET)
				redirect_n_trusted += parse_gw_flag($2, RTPROTO_REDIRECT, GWF_TRUSTED);
				if (!redirect_n_trusted) {
					PARSE_ERROR;
				}
#endif	/* defined(PROTO_ICMP) || defined(ROUTING_SOCKET) */
			}
		| T_TRACEOPTIONS redirect_trace_options
			{
			    redirect_trace_flags = $2;
			}
		;

redirect_interface_options
		: redirect_interface_option
			{
			    $$ = $1;
			}
		| redirect_interface_options redirect_interface_option
			{
			    $$ = $1 | $2;
			}
		;

redirect_interface_option
		: T_NOICMPIN
			{
#if	defined(PROTO_ICMP) || defined(ROUTING_SOCKET)
				$$ = IFS_NOICMPIN;
#endif	/* defined(PROTO_ICMP) || defined(ROUTING_SOCKET) */
			}
		;

redirect_trace_options
		: trace_options
		;

/*  */

@BEGIN:	PROTO_SNMP

snmp_statement	: T_SNMP
		        {
			    snmp_trace_flags = trace_flags;
			}
		onoff_option snmp_group
			{
			    /* XXX - trace options */
			    parse_proto = RTPROTO_SNMP;
			    PROTO_SEEN;

			    doing_snmp = ($3 == T_OFF) ? FALSE : TRUE;
			    trace(TR_CONFIG, 0, "parse: %s snmp %s ;",
				  parse_where(),
				  doing_snmp ? "on" : "off");
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
    		| T_TRACEOPTIONS snmp_trace_options
			{
			    snmp_trace_flags = $2;
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

snmp_trace_options
		: trace_options
		;

@END:	PROTO_SNMP

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
			    trace(TR_CONFIG, 0, "parse: %s static {",
				  parse_where());
			}
		'{' route_stmts '}'
			{
			    rt_close(rt_task, (gw_entry *) 0, 0, NULL);
			    trace(TR_CONFIG, 0, "parse: %s } ;",
				  parse_where());
			}
		;

route_stmts	: route_stmt L_EOS
		| route_stmts route_stmt L_EOS
		| error L_EOS
			{
				yyerrok;
			}
		;

route_stmt	: route_dest T_GATEWAY gateway_list preference_option rts_options rtf_options
			{
			    int i;
			    int host = $1.dm_mask == inet_mask_host;
			    int n_gw = 0;
			    pref_t preference = PARSE_METRIC_ISSET(&$4) ? $4.metric : RTPREF_STATIC;
			    flag_t table;
			    rt_entry *rt;
			    adv_entry *adv;
			    sockaddr_un *routers[RT_N_MULTIPATH];

			    ADV_LIST($3, adv) {
				if (n_gw >= RT_N_MULTIPATH) {
				    (void) sprintf(parse_error, "Multipath configured for %d, too many specified",
						   RT_N_MULTIPATH);
				    PARSE_ERROR;
				}
				routers[n_gw++] = adv->adv_gwp->gw_addr;
				adv->adv_gwp->gw_task = rt_task;
			    } ADV_LIST_END($3, adv) ;
			    
			    /* XXX - Another inet dependency */
			    table = host ? RTS_HOSTROUTE : RTS_INTERIOR;

			    if (rt = rt_locate(table, $1.dm_dest, $1.dm_mask, RTPROTO_STATIC)) {
				if (BIT_TEST(rt->rt_state, RTS_NOAGE)) {
				    (void) sprintf(parse_error, "duplicate static route to %A",
						   $1.dm_dest);
				    PARSE_ERROR;
				}
				rt_delete(rt);
			    }
			    rt = rt_add($1.dm_dest,
					host ? (sockaddr_un *) 0 : $1.dm_mask,
					n_gw, routers,
					rt_gwp,
					0,
					table | RTS_NOAGE | $5,
					RTF_GATEWAY | $6,
					preference);
			    if (!rt) {
				(void) sprintf(parse_error, "error adding static route to %A/%A",
					       $1.dm_dest,
					       $1.dm_mask);
				PARSE_ERROR;
			    }
			    sockfree($1.dm_dest);
			    tracef("parse: %s   %A",
				   parse_where(),
				   rt->rt_dest);
			    if (!host) {
				tracef(" mask %A",
				       rt->rt_dest_mask);
			    }
			    trace(TR_CONFIG, 0, " gateway");
			    for (i = 0; i < n_gw; i++) {
				tracef("%c%A",
				       i ? ',' : ' ',
				       rt->rt_routers[i]);
			    }
			    trace(TR_CONFIG, 0, " preference %d %s;",
				  preference,
				  gd_lower(trace_bits(rt_flag_bits, $5)));

			    adv_free_list($3);
			}
		| route_dest T_INTERFACE interface preference_option rts_options rtf_options
			{
			    int host = $1.dm_mask == inet_mask_host;
			    pref_t preference = PARSE_METRIC_ISSET(&$4) ? $4.metric : RTPREF_STATIC;
			    flag_t table;
			    rt_entry *rt;
			    sockaddr_un *addr;

			    table = host ? RTS_HOSTROUTE : RTS_INTERIOR;

#ifdef	P2P_RT_LOCAL
			    addr = IF_LCLADDR($3);
#else	/* P2P_RT_LOCAL */
			    if (BIT_TEST($3->int_state, IFS_POINTOPOINT)) {
				/* A network route to a P2P interface */
				/* may end up pointing at the wrong */
				/* interface in the kernel if we use */
				/* the local address, so use the */
				/* destination address */
				addr = host ? $3->int_addr : $3->int_lcladdr;
			    } else {
				addr = $3->int_addr;
			    }
#endif	/* P2P_RT_LOCAL */
				    
			    if (rt = rt_locate(table, $1.dm_dest, $1.dm_mask, RTPROTO_STATIC)) {
				if (BIT_TEST(rt->rt_state, RTS_NOAGE)) {
				    (void) sprintf(parse_error, "duplicate interface route to %A",
						   $1.dm_dest);
				    PARSE_ERROR;
				}
				rt_delete(rt);
			    }
			    rt = rt_add($1.dm_dest,
					host ? (sockaddr_un *) 0 : $1.dm_mask,
					1, &addr,
					rt_gwp,
					$3->int_metric,
					table | RTS_NOAGE | $5,
					$6,
					preference);
			    if (!rt) {
				(void) sprintf(parse_error, "error adding interface route to %A/%A",
					       $1.dm_dest,
					       $1.dm_mask);
				PARSE_ERROR;
			    }
			    sockfree($1.dm_dest);
			    tracef("parse: %s   %A",
				   parse_where(),
				   rt->rt_dest);
			    if (!host) {
				tracef(" mask %A",
				       rt->rt_dest_mask);
			    }
			    trace(TR_CONFIG, 0, " interface %A preference %d %s;",
				  $3->int_addr,
				  preference,
				  gd_lower(trace_bits(rt_flag_bits, $5)));
			}
		;

route_dest	: host_mask
			{
			    $$ = $1;			/* struct copy */
			}
    		| network_mask
			{
#ifndef	VARIABLE_MASKS
			    sockaddr_un *ifmask = if_subnetmask(sock2in($1.dm_dest));
			    u_long mask = ifmask ? sock2ip(ifmask) : inet_netmask($1.dm_dest);

			    if (mask != sock2ip($1.dm_mask)) {
				sprintf(parse_error, "variable subnet masks not supported on this system");
				PARSE_ERROR;
			    }
#endif	/* VARIABLE_MASKS */
			    $$ = $1;			/* struct copy */
			}
    		| T_DEFAULT
			{
			    $$.dm_dest = sockdup(inet_addr_default);
			    $$.dm_mask = inet_mask_default;
			    trace(TR_PARSE, 0, "parse: %s DEST: %A MASK: %A",
				  parse_where(),
				  $$.dm_dest,
				  $$.dm_mask);
			}
    		;

rts_options	: /* Empty */
			{
			    $$ = 0;
			}
		| T_RETAIN
			{
			    $$ = RTS_RETAIN;
			}
		;

rtf_options	: /* Empty */
			{
			    $$ = 0;
			}
		| T_REJECT
			{
#ifdef	RTF_REJECT
			    $$ = RTF_REJECT;
#else	/* RTF_REJECT */
			    sprintf(parse_error, "reject option not supported on this system");
			    PARSE_ERROR;
#endif	/* RTF_REJECT */
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
		: T_IMPORT T_PROTO control_exterior T_AS as preference_restrict_option import_option L_EOS
			{
#if	defined(PROTO_EGP) || defined(PROTO_BGP)
				adv_entry *adv;

				/*
				 *	Tack the list of destinations onto the end of the list
				 *	for neighbors with the specified AS.
				 */
				adv = adv_alloc(ADVFT_AS, $3, 1);
				adv->adv_as = $5;
				adv->adv_list = $7;
				if (PARSE_METRIC_ISSET(&$6)) {
				    if (PARSE_METRIC_ISRESTRICT(&$6)) {
					BIT_SET(adv->adv_flag, ADVF_NO);
				    } else {
					BIT_SET(adv->adv_flag, ADVFOT_PREFERENCE);
					adv->adv_result.res_preference = $6.metric;
				    }
				}

				if (!parse_adv_as(parse_import_list, adv)) {
				    PARSE_ERROR;
				}

				parse_adv_list("import", "", adv, adv->adv_list);
#endif	/* defined(PROTO_EGP) || defined(PROTO_BGP) */
			}
@BEGIN:	PROTO_BGP
		| T_IMPORT T_PROTO T_BGP aspath_match preference_restrict_option import_option L_EOS
			{
				adv_entry *adv;

				/* Make sure this PS type is known */
				adv_psfunc_add(RTPROTO_BGP, &aspath_adv_psfunc);

				/*
				 *	Tack the list of destinations onto the end of the list
				 *	for neighbors with the specified AS.
				 */
				adv = adv_alloc(ADVFT_PS, RTPROTO_BGP, 1);
				adv->adv_ps = (caddr_t) $4;
				adv->adv_list = $6;
				if (PARSE_METRIC_ISSET(&$5)) {
				    if (PARSE_METRIC_ISRESTRICT(&$5)) {
					BIT_SET(adv->adv_flag, ADVF_NO);
				    } else {
					BIT_SET(adv->adv_flag, ADVFOT_PREFERENCE);
					adv->adv_result.res_preference = $5.metric;
				    }
				}

				bgp_import_paths = parse_adv_append(bgp_import_paths, adv, TRUE);
				if (!bgp_import_paths) {
				    PARSE_ERROR;
				}

				parse_adv_list("import", "", adv, adv->adv_list);
			}
@END:	PROTO_BGP
		| T_IMPORT T_PROTO import_interior preference_restrict_option import_option L_EOS
			{
				adv_entry *adv;

				/*
				 *	Append the dest_mask list to the end of the import list
				 *	for the specified protocol.
				 */
				adv = adv_alloc((flag_t) 0, $3, 1);
				adv->adv_list = $5;
				if (PARSE_METRIC_ISSET(&$4)) {
				    if (PARSE_METRIC_ISRESTRICT(&$4)) {
					BIT_SET(adv->adv_flag, ADVF_NO);
				    } else {
					BIT_SET(adv->adv_flag, ADVFOT_PREFERENCE);
					adv->adv_result.res_preference = $4.metric;
				    }
				}

				switch ($3) {
#ifdef	PROTO_HELLO
				case RTPROTO_HELLO:
				    hello_import_list = parse_adv_append(hello_import_list, adv, TRUE);
				    if (!hello_import_list) {
					PARSE_ERROR;
				    }
				    break;
#endif	/* PROTO_HELLO */
#if	defined(PROTO_ICMP) || defined(ROUTING_SOCKET)
				case RTPROTO_REDIRECT:
				    redirect_import_list = parse_adv_append(redirect_import_list, adv, TRUE);
				    if (!redirect_import_list) {
					PARSE_ERROR;
				    }
				    break;
#endif	/* defined(PROTO_ICMP) || defined(ROUTING_SOCKET) */
#ifdef	PROTO_RIP
				case RTPROTO_RIP:
				    rip_import_list = parse_adv_append(rip_import_list, adv, TRUE);
				    if (!rip_import_list) {
					PARSE_ERROR;
				    }
				    break;
#endif	/* PROTO_RIP */
				}
				parse_adv_list("import", "", adv, adv->adv_list);
			}
		| T_IMPORT T_PROTO import_interior T_INTERFACE interface_list preference_restrict_option import_option L_EOS
			{
				adv_entry *adv, *advn, **int_adv = (adv_entry **) 0;
				adv_entry *adv_import = $7;

				switch ($3) {
#ifdef	PROTO_HELLO
					case RTPROTO_HELLO:
						int_adv = parse_adv_interface(&hello_int_import);
						break;
#endif	/* PROTO_HELLO */
#if	defined(PROTO_ICMP) || defined(ROUTING_SOCKET)
					case RTPROTO_REDIRECT:
						int_adv = parse_adv_interface(&redirect_int_import);
						break;
#endif	/* defined(PROTO_ICMP) || defined(ROUTING_SOCKET) */
#ifdef	PROTO_RIP
					case RTPROTO_RIP:
						int_adv = parse_adv_interface(&rip_int_import);
						break;
#endif	/* PROTO_RIP */
				}

				ADV_LIST($5, adv) {
				    adv->adv_proto = $3;
				    if (PARSE_METRIC_ISSET(&$6)) {
					if (PARSE_METRIC_ISRESTRICT(&$6)) {
					    BIT_SET(adv->adv_flag, ADVF_NO);
					} else {
					    BIT_SET(adv->adv_flag, ADVFOT_PREFERENCE);
					    adv->adv_result.res_preference = $6.metric;
					}
				    }
				    adv->adv_list = parse_adv_append(adv->adv_list, adv_import, FALSE);
				} ADV_LIST_END($5, adv) ;
				adv = $5;
				adv_free_list(adv_import);
				parse_adv_list("import", "", adv, adv->adv_list);
				do {
					advn = adv->adv_next;
					adv->adv_next = NULL;
					adv->adv_flag = (adv->adv_flag & ~ADVF_TYPE) | ADVFT_ANY;
					if (!(int_adv[adv->adv_ifp->int_index - 1] =
					    parse_adv_append(INT_CONTROL(int_adv, adv->adv_ifp), adv, TRUE))) {
						PARSE_ERROR;
					}
				} while (adv = advn);
			}
		| T_IMPORT T_PROTO import_interior T_GATEWAY gateway_list preference_restrict_option import_option L_EOS
			{
				/*
				 * A side effect is that import_interior sets parse_gwlist for gateway_list
				 */
				adv_entry *adv, *advn;
				adv_entry *adv_import = $7;

				/* Set the protocol and preference (if applicable). */
				/* Append the import list to each gateway */
				ADV_LIST($5, adv) {
				    adv->adv_proto = $3;
				    if (PARSE_METRIC_ISSET(&$6)) {
					if (PARSE_METRIC_ISRESTRICT(&$6)) {
					    BIT_SET(adv->adv_flag, ADVF_NO);
					} else {
					    BIT_SET(adv->adv_flag, ADVFOT_PREFERENCE);
					    adv->adv_result.res_preference = $6.metric;
					}
				    }
				    adv->adv_list = parse_adv_append(adv->adv_list, adv_import, FALSE);
				} ADV_LIST_END($5, adv) ;
				adv_free_list(adv_import);

				/* Append each gateway entry to the list for the specified gateway */
				adv = $5;
				parse_adv_list("import", "", adv, adv->adv_list);
				do {
					advn = adv->adv_next;
					adv->adv_next = NULL;
					/* Reset the type */
					adv->adv_flag = (adv->adv_flag & ~ADVF_TYPE) | ADVFT_ANY;
					adv->adv_gwp->gw_import = parse_adv_append(adv->adv_gwp->gw_import, adv, TRUE);
					if (!adv->adv_gwp->gw_import) {
						PARSE_ERROR;
					}
				} while (adv = advn);
			}
@BEGIN:	PROTO_OSPF
		| T_IMPORT T_PROTO T_OSPF_ASE ospf_type_option ospf_tag_option preference_restrict_option import_option L_EOS
			{
				adv_entry *adv;
				adv_entry *adv_import = $7;

				/* Make sure this PS type is known */
				adv_psfunc_add(RTPROTO_OSPF_ASE, &ospf_adv_psfunc);

				/*
				 *	Append the dest_mask list to the end of the OSPF import list.
				 */
				adv = adv_alloc(ADVFT_PS, RTPROTO_OSPF_ASE, 1);
				adv->adv_list = adv_import;
				adv->adv_ps = (caddr_t) adv;

				BIT_SET(adv->adv_flag, ADVFOT_FLAG);
				/* Set Type (Do I really want to support this) */
				if (PARSE_METRIC_ISSET(&$4)) {
				    adv->adv_result.res_flag = $4.metric;
				} else {
				    adv->adv_result.res_flag = OSPF_EXPORT_TYPE1 | OSPF_EXPORT_TYPE2;
				}

				/* Set Tag */
				if (PARSE_METRIC_ISSET(&$5)) {
				    BIT_SET(adv->adv_flag, ADVFOT_METRIC);
				    BIT_SET(adv->adv_result.res_flag, OSPF_EXPORT_TAG);
				    adv->adv_result.res_metric = $5.metric;
				}

				/* Set Preference */
				if (PARSE_METRIC_ISSET(&$6)) {
				    if (PARSE_METRIC_ISRESTRICT(&$6)) {
					BIT_SET(adv->adv_flag, ADVF_NO);
				    } else {
					BIT_SET(adv->adv_flag, ADVFOT_PREFERENCE);
					adv->adv_result.res_preference = $6.metric;
				    }
				}

				ospf.import_list = parse_adv_append(ospf.import_list, adv, TRUE);
				if (!ospf.import_list) {
				    PARSE_ERROR;
				}
				parse_adv_list("import", "", adv, adv->adv_list);
			}
@END:	PROTO_OSPF
		| T_EXPORT T_PROTO control_exterior T_AS as metric_restrict_option prop_source_option L_EOS
			{
#if	defined(PROTO_EGP) || defined(PROTO_BGP)
				adv_entry *adv;
				adv_entry *adv_prop = $7;

				/*
				 *	Tack the list of destinations onto the end of the list
				 *	for neighbors with the specified AS.
				 */
				adv = adv_alloc(ADVFT_AS, $3, 1);
				adv->adv_as = $5;
				adv->adv_list = adv_prop;
				if (PARSE_METRIC_ISRESTRICT(&$6)) {
				    BIT_SET(adv->adv_flag, ADVF_NO);
				} else if (PARSE_METRIC_ISSET(&$6)) {
				    BIT_SET(adv->adv_flag, ADVFOT_METRIC);
				    adv->adv_result.res_metric = $6.metric;
				}

				if (!parse_adv_as(parse_export_list, adv)) {
				    PARSE_ERROR;
				}

				parse_adv_prop_list(adv);
#endif	/* defined(PROTO_EGP) || defined(PROTO_BGP) */
			}
		| T_EXPORT T_PROTO export_interior metric_restrict_option prop_source_option L_EOS
			{
				adv_entry *adv;
				adv_entry *adv_prop = $5;

				/*
				 *	Append the dest_mask list to the end of the export list
				 *	for the specified protocol.
				 */
				adv = adv_alloc((flag_t) 0, $3, 1);
				adv->adv_list = adv_prop;
				if (PARSE_METRIC_ISRESTRICT(&$4)) {
				    BIT_SET(adv->adv_flag, ADVF_NO);
				} else if (PARSE_METRIC_ISSET(&$4)) {
				    BIT_SET(adv->adv_flag, ADVFOT_METRIC);
				    adv->adv_result.res_metric = $4.metric;
				}

				switch ($3) {
#ifdef	PROTO_HELLO
					case RTPROTO_HELLO:
						hello_export_list = parse_adv_append(hello_export_list, adv, TRUE);
						if (!hello_export_list) {
							PARSE_ERROR;
						}
						break;
#endif	/* PROTO_HELLO */
#ifdef	PROTO_RIP
					case RTPROTO_RIP:
						rip_export_list = parse_adv_append(rip_export_list, adv, TRUE);
						if (!rip_export_list) {
							PARSE_ERROR;
						}
						break;
#endif	/* PROTO_RIP */
				}
				parse_adv_prop_list(adv);
			}
		| T_EXPORT T_PROTO export_interior T_INTERFACE interface_list metric_restrict_option prop_source_option L_EOS
			{
				adv_entry *adv, *advn, **int_adv = (adv_entry **) 0;
				adv_entry *adv_prop = $7;

				switch ($3) {
#ifdef	PROTO_HELLO
					case RTPROTO_HELLO:
						int_adv = parse_adv_interface(&hello_int_export);
						break;
#endif	/* PROTO_HELLO */
#ifdef	PROTO_RIP
					case RTPROTO_RIP:
						int_adv = parse_adv_interface(&rip_int_export);
						break;
#endif	/* PROTO_RIP */
				}

				ADV_LIST($5, adv) {
				    adv->adv_proto = $3;
				    if (PARSE_METRIC_ISRESTRICT(&$6)) {
					BIT_SET(adv->adv_flag, ADVF_NO);
				    } else if (PARSE_METRIC_ISSET(&$6)) {
					BIT_SET(adv->adv_flag, ADVFOT_METRIC);
					adv->adv_result.res_metric = $6.metric;
				    }
				    adv->adv_list = parse_adv_append(adv->adv_list, adv_prop, FALSE);
				} ADV_LIST_END($5, adv) ;
				adv = $5;
				adv_free_list(adv_prop);
				parse_adv_prop_list(adv);
				do {
					advn = adv->adv_next;
					adv->adv_next = NULL;
					if (!(int_adv[adv->adv_ifp->int_index - 1] =
					    parse_adv_append(INT_CONTROL(int_adv, adv->adv_ifp), adv, TRUE))) {
						PARSE_ERROR;
					}
				} while (adv = advn);
			}
		| T_EXPORT T_PROTO export_interior T_GATEWAY gateway_list metric_restrict_option prop_source_option L_EOS
			{
			    /*
			     * A side effect is that prop_interior sets parse_gwlist for gateway_list
			     */
			    adv_entry *adv, *advn;
			    adv_entry *adv_prop = $7;

			    ADV_LIST($5, adv) {
				adv->adv_proto = $3;
				if (PARSE_METRIC_ISRESTRICT(&$6)) {
				    BIT_SET(adv->adv_flag, ADVF_NO);
				} else if (PARSE_METRIC_ISSET(&$6)) {
				    BIT_SET(adv->adv_flag, ADVFOT_METRIC);
				    adv->adv_result.res_metric = $6.metric;
				}
				adv->adv_list = parse_adv_append(adv->adv_list, adv_prop, FALSE);
			    } ADV_LIST_END($5, adv) ;
			    adv = $5;
			    adv_free_list(adv_prop);
			    parse_adv_prop_list(adv);
			    do {
				advn = adv->adv_next;
				adv->adv_next = NULL;
				adv->adv_gwp->gw_export = parse_adv_append(adv->adv_gwp->gw_export, adv, TRUE);
				if (!adv->adv_gwp->gw_export) {
				    PARSE_ERROR;
				}
			    } while (adv = advn);
			}
@BEGIN:	PROTO_OSPF
    		| T_EXPORT T_PROTO export_ospf_ase ospf_type_option ospf_tag_as_option metric_option prop_source_option L_EOS
			{
			    adv_entry *adv;

			    /* If we export then we are a border router */
			    IAmASBorderRtr = TRUE;

			    /* Make sure this PS type is known */
			    adv_psfunc_add(RTPROTO_OSPF_ASE, &ospf_adv_psfunc);

			    /*
			     *	Append the dest_mask list to the end of the export list
			     *	for the specified protocol.
			     */
			    adv = adv_alloc(ADVFT_PS, RTPROTO_OSPF_ASE, 1);
			    adv->adv_ps = (caddr_t) adv;
			    adv->adv_list = $7;

			    /* Metric */
			    if (PARSE_METRIC_ISSET(&$6)) {
				BIT_SET(adv->adv_flag, ADVFOT_METRIC);
				adv->adv_result.res_metric = $6.metric;
			    }

			    /* Type */
			    if (PARSE_METRIC_ISSET(&$4)) {
				BIT_SET(adv->adv_flag, ADVFOT_FLAG);
				adv->adv_result.res_flag = $4.metric;
			    }

			    /* Tag */
			    if (PARSE_METRIC_ISINFINITY(&$5)) {
				BIT_SET(adv->adv_result.res_flag, OSPF_EXPORT_TAG_AS);
			    } else if (PARSE_METRIC_ISSET(&$5)) {
				BIT_SET(adv->adv_flag, ADVFOT_METRIC2);
				BIT_SET(adv->adv_result.res_flag, OSPF_EXPORT_TAG|OSPF_EXPORT_TAG_METRIC2);
				adv->adv_result.res_metric2 = $5.metric;
			    }

			    ospf.export_list = parse_adv_append(ospf.export_list, adv, TRUE);
			    if (!ospf.export_list) {
				PARSE_ERROR;
			    }
			    parse_adv_prop_list(adv);
			}
@END:	PROTO_OSPF
		| T_SUMMARY T_PROTO summary_interior '{' summary_list '}' L_EOS
			{
			    $5->adv_flag = ADVFT_ANY;
			    $5->adv_proto = $3;

			    sum_lists[$3] = parse_adv_append(sum_lists[$3], $5, TRUE);
			    if (!sum_lists[$3]) {
				PARSE_ERROR;
			    }
			}
		;	

/*  */

/* Support for summary clauses */

summary_interior	: T_ALL
			{
#if	defined(PROTO_ICMP) || defined(ROUTING_SOCKET)
				$$ = parse_proto = RTPROTO_ANY;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
#endif	/* defined(PROTO_ICMP) || defined(ROUTING_SOCKET) */
			}
@BEGIN:	PROTO_HELLO
		| T_HELLO
			{
				$$ = parse_proto = RTPROTO_HELLO;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
			}
@END:	PROTO_HELLO
@BEGIN:	PROTO_RIP
		| T_RIP
			{
				$$ = parse_proto = RTPROTO_RIP;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
			}
@END:	PROTO_RIP
@BEGIN:	PROTO_OSPF
		| T_OSPF
			{
				$$ = parse_proto = RTPROTO_OSPF;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
			}
		| T_OSPF_ASE
			{
				$$ = parse_proto = RTPROTO_OSPF_ASE;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
			}
@END:	PROTO_OSPF
		;

summary_list	: summary
			{
			    $$ = $1;
			}
		| summary_list summary
			{
			    $$ = parse_adv_append($1, $2, TRUE);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		| summary_list error
			{
			    yyerrok;
			}
		;

summary		: T_MASK mask preference_option '{' summary_masks '}' L_EOS
			{
			    $$ = adv_alloc(0, 0, 1);
			    $$->adv_list = $5;
			    if (PARSE_METRIC_ISSET(&$3)) {
				BIT_SET($$->adv_flag, ADVFOT_PREFERENCE);
				$$->adv_result.res_preference = $3.metric;
			    }

			    $$->adv_result.res_mask = $2;
			}
		;

summary_masks	: /* Empty */
			{
				$$ = (adv_entry *) 0;
			}
		| summary_masks summary_mask L_EOS
			{
			    $$ = parse_adv_dm_append($1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		| summary_masks error L_EOS
			{
				yyerrok;
			}
		;

summary_mask	: dest_mask preference_option
			{
			    if (!mask_contig($1.dm_mask)) {
				sprintf(parse_error, "Mask %A contains non-contiguous bits, not supported",
					$1.dm_mask);
				PARSE_ERROR;
			    }
			    $$ = adv_alloc(ADVFT_DM, parse_proto, 1);
			    $$->adv_dm = $1;
			    if (PARSE_METRIC_ISSET(&$2)) {
				BIT_SET($$->adv_flag, ADVFOT_PREFERENCE);
				$$->adv_result.res_preference = $2.metric;
			    }
			}
		;

/*  */

/* Support for import clauses */

control_exterior	: proto_exterior
			{
			    parse_export_proto = $$ = $1;

			    switch ($1) {
#if	defined(PROTO_EGP)
			    case RTPROTO_EGP:
				parse_import_list = &egp_import_list;
				parse_export_list = &egp_export_list;
				break;
#endif

#if	defined(PROTO_BGP)
			    case RTPROTO_BGP:
				parse_import_list = &bgp_import_list;
				parse_export_list = &bgp_export_list;
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

import_interior	: T_REDIRECT
			{
#if	defined(PROTO_ICMP) || defined(ROUTING_SOCKET)
				$$ = parse_proto = RTPROTO_REDIRECT;
				parse_gwlist = &redirect_gw_list;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
#endif	/* defined(PROTO_ICMP) || defined(ROUTING_SOCKET) */
			}
@BEGIN:	PROTO_HELLO
		| T_HELLO
			{
				$$ = parse_proto = RTPROTO_HELLO;
				parse_gwlist = &hello_gw_list;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
			}
@END:	PROTO_HELLO
@BEGIN:	PROTO_RIP
		| T_RIP
			{
				$$ = parse_proto = RTPROTO_RIP;
				parse_gwlist = &rip_gw_list;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
			}
@END:	PROTO_RIP
		;

import_option	: /* Empty */
			{
			    $$ = (adv_entry *) 0;
			}
		| '{' import_list '}'
			{
			    $$ = adv_compress($2);
			}
		;

import_list	: /* Empty */
			{
				$$ = (adv_entry *) 0;
			}
		| import_list import_listen L_EOS
			{
			    
			    $$ = parse_adv_dm_append($1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		| import_list error L_EOS
			{
				yyerrok;
			}
		;

import_listen	: dest_mask preference_restrict_option
			{
				$$ = adv_alloc(ADVFT_DM, parse_proto, 1);
				$$->adv_dm = $1;
				if (PARSE_METRIC_ISSET(&$2)) {
				    if (PARSE_METRIC_ISRESTRICT(&$2)) {
					BIT_SET($$->adv_flag, ADVF_NO);
				    } else {
					BIT_SET($$->adv_flag, ADVFOT_PREFERENCE);
					$$->adv_result.res_preference = $2.metric;
				    }
				}
			}
		;

/*  */

/* Support for Export clauses */

export_interior	: proto_interior
			{
			    $$ = parse_export_proto = $1;
			}
		;

@BEGIN:	PROTO_OSPF
export_ospf_ase	: T_OSPF_ASE
			{
			    $$ = parse_export_proto = RTPROTO_OSPF_ASE;
			    trace(TR_PARSE, 0, "parse: %s PROTO: %s",
				  parse_where(),
				  gd_lower(trace_state(rt_proto_bits, $$)));
			}
		;
@END:	PROTO_OSPF

prop_source_option
		: /* Empty */
			{
				$$ = (adv_entry *) 0;
			}
		| '{' prop_source_list '}'
			{
				$$ = $2;
			}
		;
    
prop_source_list
		: /* Empty */
			{
				$$ = (adv_entry *) 0;
			}
		| prop_source_list prop_source L_EOS
			{
				$$ = parse_adv_append($1, $2, TRUE);
				if (!$$) {
					PARSE_ERROR;
				}
			}
		| prop_source_list error L_EOS
			{
				yyerrok;
			}
		;

prop_source	: T_PROTO proto_exterior T_AS as metric_restrict_option prop_restrict_option
			{
				$$ = adv_alloc(ADVFT_AS | ADVF_FIRST, (proto_t) 0, 1);
				$$->adv_as = $4;
				$$ = parse_adv_propagate($$, $2, $5, $6);
			}
@BEGIN:	PROTO_BGP
		| T_PROTO T_BGP aspath_match metric_restrict_option prop_restrict_option
			{
			    /* Make sure this PS type is known */
			    adv_psfunc_add(RTPROTO_BGP, &aspath_adv_psfunc);

			    $$ = adv_alloc(ADVFT_PS | ADVF_FIRST, (proto_t) 0, 1);
			    $$->adv_ps = (caddr_t) $3;
			    $$ = parse_adv_propagate($$, RTPROTO_BGP, $4, $5);
			}
@END:	PROTO_BGP
    /* Interfaces */
		| T_PROTO prop_direct metric_restrict_option prop_restrict_option
			{
				$$ = adv_alloc(ADVFT_ANY | ADVF_FIRST, (proto_t) 0, 1);
				$$ = parse_adv_propagate($$, $2, $3, $4);
			}
		| T_PROTO prop_direct T_INTERFACE interface_list metric_restrict_option prop_restrict_option
			{
				$$ = parse_adv_propagate($4, $2, $5, $6);
			}
    /* Static routes */
		| T_PROTO prop_static metric_restrict_option prop_restrict_option
			{
				$$ = adv_alloc(ADVFT_ANY | ADVF_FIRST, (proto_t) 0, 1);
				$$ = parse_adv_propagate($$, $2, $3, $4);
			}
		| T_PROTO prop_static T_INTERFACE interface_list metric_restrict_option prop_restrict_option
			{
				$$ = parse_adv_propagate($4, $2, $5, $6);
			}
    /* Kernel static routes (routing socket) */
		| T_PROTO prop_kernel metric_restrict_option prop_restrict_option
			{
				$$ = adv_alloc(ADVFT_ANY | ADVF_FIRST, (proto_t) 0, 1);
				$$ = parse_adv_propagate($$, $2, $3, $4);
			}
		| T_PROTO prop_kernel T_INTERFACE interface_list metric_restrict_option prop_restrict_option
			{
				$$ = parse_adv_propagate($4, $2, $5, $6);
			}
    /* Internal default route */
		| T_PROTO prop_default metric_restrict_option prop_restrict_option
			{
				$$ = adv_alloc(ADVFT_ANY | ADVF_FIRST, (proto_t) 0, 1);
				$$ = parse_adv_propagate($$, $2, $3, $4);
			}
@BEGIN:	PROTO_RIP
    /* RIP Imports */
		| T_PROTO rip_prop_init metric_restrict_option prop_restrict_option
			{
				$$ = adv_alloc(ADVFT_ANY | ADVF_FIRST, (proto_t) 0, 1);
				$$ = parse_adv_propagate($$, $2, $3, $4);
			}
		| T_PROTO rip_prop_init T_INTERFACE interface_list metric_restrict_option prop_restrict_option
			{
				$$ = parse_adv_propagate($4, $2, $5, $6);
			}
		| T_PROTO rip_prop_init T_GATEWAY gateway_list metric_restrict_option prop_restrict_option
			{
				$$ = parse_adv_propagate($4, $2, $5, $6);
			}
@END:	PROTO_RIP
@BEGIN:	PROTO_HELLO
    /* HELLO Imports */
		| T_PROTO hello_prop_init metric_restrict_option prop_restrict_option
			{
				$$ = adv_alloc(ADVFT_ANY | ADVF_FIRST, (proto_t) 0, 1);
				$$ = parse_adv_propagate($$, $2, $3, $4);
			}
		| T_PROTO hello_prop_init T_INTERFACE interface_list metric_restrict_option prop_restrict_option
			{
				$$ = parse_adv_propagate($4, $2, $5, $6);
			}
		| T_PROTO hello_prop_init T_GATEWAY gateway_list metric_restrict_option prop_restrict_option
			{
				$$ = parse_adv_propagate($4, $2, $5, $6);
			}
@END:	PROTO_HELLO
@BEGIN: PROTO_OSPF
    /* OSPF imports */
		| T_PROTO ospf_prop_init metric_restrict_option prop_restrict_option
			{
			    $$ = adv_alloc(ADVFT_ANY | ADVF_FIRST, (proto_t) 0, 1);
			    $$ = parse_adv_propagate($$, $2, $3, $4);
			}
		| T_PROTO ospf_ase_prop_init ospf_type_option ospf_tag_option metric_option prop_restrict_option
			{
			    $$ = adv_alloc(ADVFT_PS | ADVF_FIRST, (proto_t) 0, 1);

			    $$->adv_ps = (caddr_t) $$;
			    
			    BIT_SET($$->adv_flag, ADVFOT_FLAG);
			    /* Set Type (Do I really want to support this) */
			    if (PARSE_METRIC_ISSET(&$3)) {
				$$->adv_result.res_flag = $4.metric;
			    } else {
				$$->adv_result.res_flag = OSPF_EXPORT_TYPE1 | OSPF_EXPORT_TYPE2;
			    }

			    /* Set Tag */
			    if (PARSE_METRIC_ISSET(&$4)) {
				BIT_SET($$->adv_flag, ADVFOT_METRIC);
				BIT_SET($$->adv_result.res_flag, OSPF_EXPORT_TAG);
				$$->adv_result.res_metric = $4.metric;
			    }

			    $$ = parse_adv_propagate($$, $2, $5, $6);
			}
		| T_PROTO ospf_ase_prop_init T_RESTRICT prop_restrict_option
			{
			    pmet_t metric;

			    PARSE_METRIC_RESTRICT(&metric);
			    
			    $$ = adv_alloc(ADVFT_ANY | ADVF_FIRST, (proto_t) 0, 1);
			    $$ = parse_adv_propagate($$, $2, metric, $4);
			}
@END:	PROTO_OSPF
		;

prop_direct	: T_DIRECT
			{
				$$ = parse_proto = RTPROTO_DIRECT;
				parse_gwlist = (gw_entry **)0;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
			}
		;

prop_static	: T_STATIC
			{
				$$ = parse_proto = RTPROTO_STATIC;
				parse_gwlist = &rt_gw_list;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
			}
		;

prop_kernel	: T_KERNEL
			{
				$$ = parse_proto = RTPROTO_KRT;
				parse_gwlist = &krt_gw_list;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
			}
		;

prop_default	: T_DEFAULT
			{
				$$ = parse_proto = RTPROTO_DEFAULT;
				parse_gwlist = (gw_entry **)0;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
			}
		;

prop_restrict_option
		: /* Empty */
			{
				$$ = (adv_entry *) 0;
			}
		| '{' prop_restrict_list '}'
			{
				$$ = adv_compress($2);
			}
		;


prop_restrict_list
		: /* Empty */
			{
			    $$ = (adv_entry *) 0;
			}
		| prop_restrict_list prop_restrict L_EOS
			{
			    $$ = parse_adv_dm_append($1, $2);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		| prop_restrict_list error L_EOS
			{
			    yyerrok;
			}
		;

prop_restrict	: dest_mask metric_restrict_option
			{
			    $$ = adv_alloc(ADVFT_DM, (proto_t) 0, 1);
			    $$->adv_dm = $1;
			    if (PARSE_METRIC_ISRESTRICT(&$2)) {
				BIT_SET($$->adv_flag, ADVF_NO);
			    } else if (PARSE_METRIC_ISSET(&$2)) {
				$$->adv_result.res_metric = $2.metric;
				BIT_SET($$->adv_flag, ADVFOT_METRIC);
			    }
			}
		;

/*  */

/* Addresses */
dest_mask_list	: /* Empty */
			{
			    $$ = (adv_entry *) 0;
			}
		| dest_mask_list dest_mask L_EOS
			{
			    $$ = adv_alloc(ADVFT_DM, (proto_t) 0, 1);
			    $$->adv_dm = $2;
			    $$ = parse_adv_dm_append($1, $$);
			    if (!$$) {
				PARSE_ERROR;
			    }
			}
		| dest_mask_list error L_EOS
			{
			    yyerrok;
			}
		;
		
	
/* Destination and mask pair used for control lists */
dest_mask	: T_ALL
			{
			    /* XXX - need to specify a generic protocol */
			    $$.dm_dest = sockdup(inet_addr_any);
			    $$.dm_mask = inet_mask_default;
			    trace(TR_PARSE, 0, "parse: %s DEST: %A MASK: %A",
				  parse_where(),
				  $$.dm_dest,
				  $$.dm_mask);
			}
		| T_DEFAULT
			{
			    $$.dm_dest = sockdup(inet_addr_default);
			    $$.dm_mask = inet_mask_host;
			    trace(TR_PARSE, 0, "parse: %s DEST: %A MASK: %A",
				  parse_where(),
				  $$.dm_dest,
				  $$.dm_mask);
			}
		| host_mask
			{
			    $$ = $1;			/* struct copy */
			}
		| network_mask
			{
			    $$ = $1;			/* struct copy */
			}
		;

mask		: ip_addr
			{
			    $$ = mask_locate($1);
			    sockfree($1);
			    trace(TR_PARSE, 0, "parse: %s MASK: %A",
				  parse_where(),
				  $$);
			}
		;

/* Gateway list */
gateway_list	: gateway
			{
				$$ = adv_alloc(ADVFT_GW | ADVF_FIRST, (proto_t) 0, 1);
				$$->adv_gwp = $1;
			}
		| gateway_list gateway
			{
				$$ = adv_alloc(ADVFT_GW, (proto_t) 0, 1);
				$$->adv_gwp = $2;
				$$ = parse_adv_append($1, $$, TRUE);
				if (!$$) {
					PARSE_ERROR;
				}
			}
		;

/* A gateway is a host on an attached network */
gateway		: host
			{
			    /*
			     *	Make sure host is on a locally attached network then
			     *	find or create a gw structure for it.  Requires that
			     *	parse_proto and parse_gwlist are previously set
			     */
			    if (!if_withdst($1)) {
				(void) sprintf(parse_error, "gateway not a host address on an attached network: '%A'",
					       $1);
				PARSE_ERROR;
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
					   (time_t) 0,
					   $1);
			    trace(TR_PARSE, 0, "parse: %s GATEWAY: %A  PROTO: %s",
				  parse_where(),
				  $$->gw_addr,
				  gd_lower(trace_state(rt_proto_bits, $$->gw_proto)));
			    sockfree($1);
			}
		;

/* A host is a host */
host		: ip_addr
			{
			    $$ = $1;
			    trace(TR_PARSE, 0, "parse: %s HOST: %A",
				  parse_where(),
				  $$);
			}
		| host_name
			{ 
			    sockaddr_un *addr;
			    
			    addr = parse_addr_hostname(&$1);
			    if (!addr) {
				PARSE_ERROR;
			    }
			    $$ = sockdup(addr);
			    trace(TR_PARSE, 0, "parse: %s HOST: %A",
				  parse_where(),
				  $$);
			    free_charstr(&$1);
			}
		;

host_mask	: T_HOST host
			{
			    $$.dm_dest = $2;
			    $$.dm_mask = inet_mask_host;
			    trace(TR_PARSE, 0, "parse: %s DEST: %A MASK: %A",
				  parse_where(),
				  $$.dm_dest,
				  $$.dm_mask);
			}
		;

/* A network is a network */
network		: ip_addr
			{
			    $$ = $1;
			    trace(TR_PARSE, 0, "parse: %s NETWORK: %A",
				  parse_where(),
				  $$);
			}
		| host_name
			{
			    sockaddr_un *addr;
			    
			    addr = parse_addr_netname(&$1);
			    if (!addr) {
				PARSE_ERROR;
			    }
			    $$ = sockdup(addr);
			    trace(TR_PARSE, 0, "parse: %s NETWORK: %A",
				  parse_where(),
				  $$);
			    free_charstr(&$1);
			}
		;
network_mask	: network
			{
			    if (sock2ip($1) != inet_wholenetof(sock2in($1))) {
				sprintf(parse_error, "host or mask option needed");
				PARSE_ERROR;
			    }
			    $$.dm_dest = $1;
			    $$.dm_mask = mask_inet_natural($1);
			    trace(TR_PARSE, 0, "parse: %s DEST: %A MASK: %A",
				  parse_where(),
				  $$.dm_dest,
				  $$.dm_mask);
			}
		| network T_MASK mask
			{
			    register byte *ap = $1->a.sa_data;
			    register byte *mp = $3->a.sa_data;
			    register byte *alp = ap + socksize($1) - (ap - (byte *) $1);
			    register byte *mlp = mp + socksize($3) - (mp - (byte *) $3);

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
			    trace(TR_PARSE, 0, "parse: %s DEST: %A MASK: %A",
				  parse_where(),
				  $$.dm_dest,
				  $$.dm_mask);
			}
		;

/* IP address */
ip_addr		: in_addr
			{
			    sockaddr_un addr;
			    
			    sockclear_in(&addr);
			    sock2in(&addr) = $1;	/* struct copy */

			    $$ = sockdup(&addr);

			    trace(TR_PARSE, 0, "parse: %s IP_ADDR: %A",
				  parse_where(),
				  $$);
			}
		;

in_addr		: L_NUMBER
			{
			    u_long addr = $1;
			    
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
			    u_long addr = 0;

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
			    free_bytestr(&$1);
			}
		;


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
			{
			    $$ = $1;
			}
		;

/* Protocols */
proto_interior	: T_NOP
			{
			    $$ = 0;
			}
@BEGIN:	PROTO_RIP
    		| T_RIP
			{
				parse_proto = $$ = RTPROTO_RIP;
				parse_gwlist = &rip_gw_list;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
			}
@END:	PROTO_RIP
@BEGIN:	PROTO_HELLO
		| T_HELLO
			{
				parse_proto = $$ = RTPROTO_HELLO;
				parse_gwlist = &hello_gw_list;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
			}
@END:	PROTO_HELLO
		;

proto_exterior	: T_NOP
			{
			    $$ = 0;
			}
@BEGIN:	PROTO_EGP
		| T_EGP
			{
				$$ = RTPROTO_EGP;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
			}
@END:	PROTO_EGP
@BEGIN:	PROTO_BGP
		| T_BGP
			{
				$$ = RTPROTO_BGP;
				trace(TR_PARSE, 0, "parse: %s PROTO: %s",
					parse_where(),
					gd_lower(trace_state(rt_proto_bits, $$)));
			}
@END:	PROTO_BGP
		;

onoff_option	: T_ON		{ $$ = T_ON; }
		| T_OFF		{ $$ = T_OFF; }
		;

/* Metric */

metric		: number
			{
			    PARSE_METRIC_SET(&$$, $1);
			    trace(TR_PARSE, 0, "parse: %s METRIC: %d",
				  parse_where(),
				  $$);
			}
		| T_INFINITY
			{
			    PARSE_METRIC_INFINITY(&$$);
			    trace(TR_PARSE, 0, "parse: %s METRIC: infinity",
				  parse_where(),
				  $$);
			}
		;

metric_option	: /* Empty */
			{
			    PARSE_METRIC_CLEAR(&$$);
			}
		| T_METRIC metric
			{
			    $$ = $2;
			}
		;
		
metric_restrict_option
		: /* Empty */
			{
			    PARSE_METRIC_CLEAR(&$$);
			}
		| T_RESTRICT
			{
			    PARSE_METRIC_RESTRICT(&$$);
			}
		| T_METRIC metric
			{
			    if (parse_metric_check(parse_export_proto, &$2)) {
				PARSE_ERROR;
			    }
			    $$ = $2;
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
			{
			    $$ = $1;
			}
		| T_RESTRICT
			{
			    PARSE_METRIC_RESTRICT(&$$);
			}
		;

preference	: L_NUMBER
			{
				if (parse_limit_check("preference", $1, LIMIT_PREFERENCE)) {
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
				trace(TR_PARSE, 0, "parse: %s STRING: \"%s\" length: %d",
				      parse_where(),
				      $$.ptr,
				      $$.len);
			}
		;


number		: L_NUMBER
			{
			    $$ = $1;
			}
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
			    free_bytestr(&$1);
			}
		;


byte_string	: L_HEXSTRING
			{
			    $$ = $1;
			}
		| L_OCTETSTRING
			{
			    $$ = $1;
			}
		| L_HEXSTRING_ODD
			{
			    sprintf(parse_error, "hex string contains an odd number of digits");
			    PARSE_ERROR;
			}
		;

time		: L_NUMBER
			{
			  	if (parse_limit_check("seconds", $1, LIMIT_NATURAL)) {
				  	PARSE_ERROR;
				};
				$$ = $1;
			}
		| L_NUMBER ':' L_NUMBER
			{
			  	if (parse_limit_check("minutes", $1, LIMIT_NATURAL)) {
				  	PARSE_ERROR;
				}
			  	if (parse_limit_check("seconds", $3, LIMIT_SECONDS)) {
				  	PARSE_ERROR;
				}
				$$ = ($1 * 60) + $3;
			}
		| L_NUMBER ':' L_NUMBER ':' L_NUMBER
			{
			  	if (parse_limit_check("hours", $1, LIMIT_NATURAL)) {
				  	PARSE_ERROR;
				}
			  	if (parse_limit_check("minutes", $3, LIMIT_MINUTES)) {
				  	PARSE_ERROR;
				}
			  	if (parse_limit_check("seconds", $5, LIMIT_SECONDS)) {
				  	PARSE_ERROR;
				}
				$$ = (($1 * 60) + $3) * 60 + $5;
			}
		;

/* Internet ports */
port		: L_NUMBER
			{
			    if (parse_limit_check("port", $1, LIMIT_PORT)) {
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

			    trace(TR_PARSE, 0, "parse: %s PORT %s (%d)",
				  parse_where(),
				  $1.ptr,
				  ntohs($$));
			}
		;

/**/
/* Autonomous systems */

as_identity	: as
			{
			    $$ = $1;
			}
		| T_LOCAL
			{
			    $$ = 0;
			}
		;

as		: L_NUMBER
			{
				if (parse_limit_check("autonomous system", $1, LIMIT_AS)) {
					PARSE_ERROR;
				}
				$$ = $1;
			}
		;

as_list		: as
			{
				$$ = adv_alloc(ADVFT_AS | ADVF_FIRST, (proto_t) 0, 1);
				$$->adv_as = $1;
			}
		| as_list as
			{
				$$ = adv_alloc(ADVFT_AS, (proto_t) 0, 1);
				$$->adv_as = $2;
				$$ = parse_adv_append($1, $$, TRUE);
				if (!$$) {
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

/**/
@BEGIN:	PROTO_ASPATHS
/* AS paths */

aspath_match	: T_ASPATH
			{
			    aspath_state = 0;
			    aspath_current = (asmatch_t *) task_mem_calloc((task *) 0, 1, sizeof (asmatch_t));
			}
		aspath_regex T_ORIGIN aspath_origin
    			{
			    $$ = aspath_current;
			    $$->origin_mask = $5;
			    trace(TR_PARSE, 0, "%s: path %X origins %s",
				  parse_where(),
				  $$,
				  aspath_adv_origins($$->origin_mask));
			    aspath_current = (asmatch_t *) 0;
			}
    		;

aspath_origin	: T_ANY
			{
			    /* Set all bits on */
			    $$ = -1;
			}
		| aspath_origin_list
    			{
			    $$ = $1;
			}
		;

aspath_origin_list
		: aspath_origins
			{
			    $$ = $1;
			}
		| aspath_origin_list '|' aspath_origins
			{
			    $$ = $1 | $3;
			}
		;

aspath_origins	: T_IGP
			{
			    $$ = (1<<PATH_ORG_IGP);
			}
@BEGIN:	PROTO_EGP
		| T_EGP
			{
			    $$ = (1<<PATH_ORG_EGP);
			}
@END:	PROTO_EGP
		| T_INCOMPLETE
    			{
			    $$ = (1<<PATH_ORG_XX);
			}
		;
    
aspath_regex	: aspath_sum
			{
			    NFA_ASG($$.start, $1.start);
			    NFA_ASG(aspath_current->start, $$.start);
			    trace(TR_PARSE, 0, "%s: REDUCED:	regex : sum",
				  parse_where());
			}
		| aspath_sum '|' aspath_regex
			{
			    NFA_OR($$.start, $1.start, $3.start);
			    NFA_OR($$.state, $1.state, $3.state);
			    NFA_ASG(aspath_current->start, $$.start);
			    trace(TR_PARSE, 0, "%s: REDUCED:	regex : sum | regex",
				  parse_where());
			}
		;

aspath_sum	: aspath_term
			{
			    trace(TR_PARSE, 0, "%s: REDUCED:	sum : term",
				  parse_where());
			}
		| aspath_term aspath_sum
			{
			    int i;
			    
			    NFA_OR($$.state, $1.state, $2.state);

			    for (i = 0; i < ACC; i++) {
				int nonzero;
				
				if (NFA_ISSET($1.state, i)) {
				    if (NFA_ISSET(aspath_current->nfa[i].next, ACC)) {
					NFA_CLR(aspath_current->nfa[i].next, ACC);
					NFA_OR(aspath_current->nfa[i].next, aspath_current->nfa[i].next, $2.start);
				    }
				    NFA_CLR($1.state, i);
				    NFA_NONZERO($1.state, nonzero);
				    if (nonzero) {
					break;
				    }
				}
			    }
			    if (i > ACC) {
				YYERROR;
			    }
			    if (NFA_ISSET($1.start, ACC)) {
				NFA_CLR($1.start, ACC);
				NFA_OR($1.start, $1.start, $2.start);
			    }
			    NFA_ASG($$.start, $1.start);
			    trace(TR_PARSE, 0, "%s: REDUCED:	sum : term sum",
				  parse_where());
			}
		;

aspath_term	: aspath_symbol
			{
			    trace(TR_PARSE, 0, "%s: REDUCED:	term : symbol",
				  parse_where());
			}
		| aspath_symbol '*'
			{
			    int i;
			    
			    for (i = 0; i < ACC; i++) {
				int nonzero;
				
				if (NFA_ISSET($1.state, i)) {
				    if (NFA_ISSET(aspath_current->nfa[i].next, ACC)) {
					NFA_OR(aspath_current->nfa[i].next, aspath_current->nfa[i].next, $1.start);
				    }
				    NFA_CLR($1.state, i);
				    NFA_NONZERO($1.state, nonzero);
				    if (nonzero) {
					break;
				    }
				}
			    }
			    NFA_ASG($$.start, $1.start);
			    NFA_SET($$.start, ACC);
			    trace(TR_PARSE, 0, "%s: REDUCED:	term : symbol *",
				  parse_where());
			}
		| aspath_symbol '+'
			{
			    int i;
			    
			    for (i = 0; i < ACC; i++) {
				if (NFA_ISSET($1.state, i)) {
				    int nonzero;
				    
				    if (NFA_ISSET(aspath_current->nfa[i].next, ACC)) {
					NFA_OR(aspath_current->nfa[i].next, aspath_current->nfa[i].next, $1.start);
				    }
				    NFA_CLR($1.state, i);
				    NFA_NONZERO($1.state, nonzero);
				    if (nonzero) {
					break;
				    }
				}
			    }
			    NFA_ASG($$.start, $1.start);
			    trace(TR_PARSE, 0, "%s: REDUCED:	term : symbol +",
				  parse_where());
			}
		| aspath_symbol '?'
			{
			    NFA_ASG($$.start, $1.start);
			    NFA_SET($$.start, ACC);
			    trace(TR_PARSE, 0, "%s: REDUCED:	term : symbol ?",
				  parse_where());
			}
		| aspath_symbol '{' aspath_range '}'
			{
			    int copy;
			    flag_t finalstate[1+ACC/WORD];
			    flag_t newstate[1+ACC/WORD];
			    flag_t oldstate[1+ACC/WORD];
			    flag_t newstart[1+ACC/WORD];
			    
			    NFA_ASG(finalstate, $1.state);
			    NFA_ASG(newstate, $1.state);
			    NFA_ASG($$.start, $1.start);
			    NFA_ASG(newstart, $1.start);
			    if (!$3.begin) {
				NFA_SET($$.start, ACC);
			    }
			    for (copy = 1; copy < $3.begin; copy++) {
				int i;
				
				NFA_ASG(oldstate, $1.state);
				NFA_ZERO(newstart);
				NFA_ZERO(newstate);
				for (i = 0; i < ACC; i++) {
				    if (NFA_ISSET($1.state, i)) {
					aspath_current->nfa[aspath_state].as = aspath_current->nfa[i].as;
					NFA_ASG(aspath_current->nfa[aspath_state].next, aspath_current->nfa[i].next);
					NFA_SHIFT(aspath_current->nfa[aspath_state].next, aspath_state-i);
					NFA_SET(newstate, aspath_state);
					if (NFA_ISSET($1.start, i)) {
					    int nonzero;
					    
					    NFA_SET(newstart, aspath_state);
					    ASPATH_NEXT_STATE;
					    NFA_CLR($1.state, i);
					    NFA_NONZERO($1.state, nonzero);
					    if (nonzero) {
						break;
					    }
					}
				    }
				    if (NFA_ISSET($$.start, ACC)) {
					NFA_OR($$.start,$$.start,newstart);
				    }
				    for (i = 0; i < ACC; i++) {
					if (NFA_ISSET(oldstate, i)) {
					    int nonzero;
					    
					    if (NFA_ISSET(aspath_current->nfa[i].next, ACC)) {
						if (copy < $3.begin) {
						    NFA_CLR(aspath_current->nfa[i].next,ACC);
						}
						NFA_OR(aspath_current->nfa[i].next, aspath_current->nfa[i].next, newstart);
					    }
					    NFA_CLR(oldstate, i);
					    NFA_NONZERO(oldstate, nonzero);
					    if (nonzero) {
						break;
					    }
					}
				    }
				    NFA_OR(finalstate, finalstate, newstate);
				    NFA_ASG($1.start, newstart);
				    NFA_ASG($1.state, newstate);
				}
				if ($3.end) {
				    for (i = 0; i < ACC; i++) {
					if (NFA_ISSET(newstate, i)) {
					    int nonzero;
					    
					    if (NFA_ISSET(aspath_current->nfa[i].next, ACC)) {
						NFA_OR(aspath_current->nfa[i].next, aspath_current->nfa[i].next, newstart);
					    }
					    NFA_CLR(newstate, i);
					    NFA_NONZERO(newstate, nonzero);
					    if (nonzero) {
						break;
					    }
					}
				    }
				}	
				NFA_ASG($$.state, finalstate);
				trace(TR_PARSE, 0, "%s: REDUCED:	term : symbol { range }",
				      parse_where());
			    }
			}
		;

aspath_symbol	: as
			{
			    NFA_ZERO($$.start);
			    NFA_ZERO($$.state);
			    NFA_SET($$.start, aspath_state);
			    NFA_SET($$.state, aspath_state);
			    aspath_current->nfa[aspath_state].as = htons($1);
			    NFA_SET(aspath_current->nfa[aspath_state].next, ACC);
			    ASPATH_NEXT_STATE;
			    trace(TR_PARSE, 0, "%s: REDUCED:	symbol : as",
				  parse_where());
			}
		| '.'
			{
			    NFA_ZERO($$.start);
			    NFA_ZERO($$.state);
			    NFA_SET($$.start, aspath_state);
			    NFA_SET($$.state, aspath_state);
			    NFA_SET(aspath_current->nfa[aspath_state].next, ACC);
			    aspath_current->nfa[aspath_state].as = 0;
			    ASPATH_NEXT_STATE;
			    trace(TR_PARSE, 0, "%s: REDUCED:	symbol : .",
				  parse_where());
			}
		| '(' aspath_regex ')'
			{
			    NFA_ASG($$.state, $2.state);
			    NFA_ASG($$.start, $2.start);
			    trace(TR_PARSE, 0, "%s: REDUCED:	symbol : ( regex )",
				  parse_where());
			}

aspath_range	: number
			{
			    $$.begin = $1;
			    $$.end = 0;
			    if (!$1) {
				sprintf(parse_error, "invalid range start: %d",
					$1);
				PARSE_ERROR;
			    }
			    trace(TR_PARSE, 0, "%s: RANGE: {%d}",
				  parse_where(),
				  $$.begin);
			}
		| number ','
			{
			    $$.begin = $1;
			    $$.end = 1;
			    if (!$1) {
				sprintf(parse_error, "invalid range start: %d",
					$1);
				PARSE_ERROR;
			    }
			    trace(TR_PARSE, 0, "%s: RANGE: {%d,}",
				  parse_where(),
				  $$.begin);
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
			    trace(TR_PARSE, 0, "%s: RANGE: {%d,%d}",
				  parse_where(),
				  $$.begin,
				  $$.end);
			}
		;
@END:	PROTO_ASPATHS

%%

/*
 *	Log any parsing errors
 */
static void
yyerror(s)
char *s;
{
	byte *cp;

	trace(TR_ALL, 0, NULL);
	tracef("parse: %s %s",
		parse_where(),
		s);

	switch (yychar) {
	case L_HEXSTRING:
	case L_HEXSTRING_ODD:
	    tracef(" at '");
	    for (cp = yylval.hex.ptr; (cp - yylval.hex.ptr) < yylval.hex.len; cp++) {
		tracef("%02x", *cp);
	    }
	    tracef("'");
	    break;
	case L_OCTETSTRING:
	    tracef(" at '");
	    for (cp = yylval.hex.ptr; (cp - yylval.hex.ptr) < yylval.hex.len; cp++) {
		tracef("%s%u",
		       (cp == yylval.hex.ptr) ? "" : ".",
		       *cp);
	    }
	    tracef("'");
	    break;
	case L_NUMBER:
	    tracef(" at '%d'",
		   yylval.num);
	    break;
	case L_EOS:
	    tracef(" at 'end-of-statement'");
	    break;
	default:
	    if (!parse_keyword_lookup(yychar)) {
#if	YYDEBUG != 0
#ifdef	YYTRANSLATE
		tracef(" at '%s'",
		       yytname[YYTRANSLATE(yychar)]);
#else	/* YYTRANSLATE */
		tracef(" at '%s'",
		       yyname[yychar]);
#endif	/* YYTRANSLATE */
#endif	/* YYDEBUG */
		break;
	    }
	    /* Fall Through */
	case L_STRING:
	case L_HNAME:
	case L_KEYWORD:
	    tracef(" at '%s' length %d",
		   yylval.str.ptr,
		   yylval.str.len);
	    break;
#ifdef	YYEMPTY
	case YYEMPTY:
	    break;
#endif	/* YYEMPTY */
	}
	trace(TR_ALL, LOG_ERR, NULL);
	trace(TR_ALL, 0, NULL);
}
