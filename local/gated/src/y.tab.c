extern char *malloc(), *realloc();

# line 2 "parser.y"
/*
 *  $Id: parser.y,v 1.75 1993/07/26 17:26:23 jch Exp $
 */

/* %(Copyright.header) */


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
@BEGIN:	PROTO_DVMRP
#include "dvmrp.h"
@END:	PROTO_DVMRP
@BEGIN:	PROTO_ISODE_SNMP
#include "snmp_isode.h"
@END:	PROTO_ISODE_SNMP
@BEGIN:	PROTO_ISIS
#include "isis.h"
#include "isis_test.h"
#include "isis_globals.h"
@END:	PROTO_ISIS
  
char parse_error[LINE_MAX] = { 0 };
char *parse_filename = 0;

static	proto_t	parse_proto;			/* For correctly tagging ADV lists */
static	proto_t	parse_export_proto;		/* For checking metrics */
static	gw_entry	**parse_gwlist;
#if	defined(PROTO_SLSP) || defined(PROTO_EGP) || defined(PROTO_BGP)
static	gw_entry	*parse_gwp;		/* To fake a list for EGP and BGP */
#endif
static  char *parse_serv_proto;
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
@END:	PROTO_OSPF
@BEGIN:	PROTO_SLSP
static slsp_instance *slsp_instance;
static slsp_gateway *slsp_gateway;
@END:	PROTO_SLSP
static if_info parse_ifi;	/* Used for configuring interfaces that do not exist */

u_int parse_state = PS_INITIAL;
proto_t protos_seen = 0;

PROTOTYPE(yyerror,
	  static void,
	  (const char *));

#define	free_string(s)	task_mem_free((task *) 0, (caddr_t) s); s = 0
#define	free_charstr(s)	task_mem_free((task *) 0, (caddr_t) (s)->ptr); (s)->ptr = (char *) 0; (s)->len = (s)->type = 0
#define	free_bytestr(s)	task_mem_free((task *) 0, (caddr_t) (s)->ptr); (s)->ptr = (byte *) 0; (s)->len = (s)->type = 0

#define	PARSE_ERROR	yyerror(parse_error); yynerrs++; YYERROR;

#define	PROTO_SEEN(proto) \
	if (BIT_TEST(protos_seen, RTPROTO_BIT(proto))) { \
	    sprintf(parse_error, "parse_proto_seen: duplicate %s clause", gd_lower(trace_state(rt_proto_bits, proto))); \
	    PARSE_ERROR; \
	} else { \
	    BIT_SET(protos_seen, RTPROTO_BIT(proto)); \
	    parse_proto = proto; \
	} \

#ifdef	PROTO_ASPATHS
static unsigned	aspath_state;
static asmatch_t *aspath_current;

#define	ASPATH_NEXT_STATE	if (aspath_state++ == ASP_BITS) { \
	sprintf(parse_error, "too many AS path regexp states"); \
	PARSE_ERROR; \
    }
#endif	/* PROTO_ASPATHS */


# line 115 "parser.y"
typedef union  {
    long	num;
    u_long	u_num;
    bytestr	hex;
    charstr	str;
    flag_t	flag;
    time_t	time;
    as_t	as;
    proto_t	proto;
    pmet_t	metric;
    pref_t	pref;
    if_addr	*ifap;
    if_addr_entry	*ifae;
    adv_entry	*adv;
    gw_entry	*gwp;
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
#if	defined(PROTO_ASPATHS)
    asmatch_t	*asp_match;
    struct {
	u_short	begin;
	u_short end;
    } asp_range;
    struct {
	flag_t	start[1 + ASP_ACC/ASP_WORD];
	flag_t	state[1 + ASP_ACC/ASP_WORD];
    } asp_stack;
#endif	/* PROTO_ASPATHS */
#endif	/* GATED_LEXER */
} YYSTYPE;
