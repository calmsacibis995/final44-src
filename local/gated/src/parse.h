/*
 * $Id: parse.h,v 1.18.2.1 1995/04/02 03:21:35 jch Exp $
 */

/* %(Copyright.header) */

/* Tracing */

#define	TR_PARSE	TR_USER_1
#define	TR_ADV		TR_USER_2


#define	PS_INITIAL	0
#define	PS_OPTIONS	1
#define	PS_INTERFACE	2
#define	PS_DEFINE	3
#define	PS_PROTO	4
#define	PS_ROUTE	5
#define	PS_CONTROL	6
#define	PS_MIN		PS_OPTIONS
#define	PS_MAX		PS_CONTROL

#define	LIMIT_AS		1, 65534
#define	LIMIT_PREFERENCE	0, 255
#define	LIMIT_PORT		0, 65535
#define	LIMIT_NATURAL		0, (u_int) -1
#define	LIMIT_MINUTES		0, 59
#define	LIMIT_SECONDS		0, 59

#define	FI_MAX	10			/* Maxiumum %include nesting level */

typedef struct {
    metric_t metric;			/* Actual metric */
    int state;				/* Metric state */
} pmet_t;

typedef struct {
    byte *ptr;			/* Pointer to the byte string */
    size_t len;				/* Length of string */
    flag_t type;			/* Original format of string */
} bytestr;

typedef struct {
    char *ptr;				/* Pointer to the byte string */
    size_t len;				/* Length of string */
    flag_t type;			/* Original format of string */
} charstr;

#define	PARSE_METRIC_CLEAR(x)		(x)->metric = (metric_t) 0, (x)->state = PARSE_METRICS_UNSET
#define	PARSE_METRIC_SET(x, y)		(x)->metric = y, (x)->state = PARSE_METRICS_SET
#define	PARSE_METRIC_INFINITY(x)	(x)->state = PARSE_METRICS_INFINITY
#define	PARSE_METRIC_RESTRICT(x)	(x)->state = PARSE_METRICS_RESTRICT
#define	PARSE_METRIC_ALTERNATE(x, y)	(x)->metric = y, (x)->state = PARSE_METRICS_ALTERNATE
#define	PARSE_METRIC_ISSET(x)		((x)->state != PARSE_METRICS_UNSET)
#define	PARSE_METRIC_ISINFINITY(x)	((x)->state == PARSE_METRICS_INFINITY)
#define	PARSE_METRIC_ISRESTRICT(x)	((x)->state == PARSE_METRICS_RESTRICT)
#define	PARSE_METRIC_ISALTERNATE(x)	((x)->state == PARSE_METRICS_ALTERNATE)

#define	PARSE_METRICS_UNSET		0		/* Metric has not yet been set */
#define	PARSE_METRICS_SET		1		/* Metric has been set */
#define	PARSE_METRICS_INFINITY		2		/* Metric set to infinity */
#define	PARSE_METRICS_RESTRICT		3		/* Metric is set to restrict (policy) */
#define	PARSE_METRICS_ALTERNATE		4		/* Alternate metric */

extern u_int parse_state;

PROTOTYPE(parse_where,
	  extern char *,
	  (void));
PROTOTYPE(parse_open,
	  extern int,
	  (char *));
PROTOTYPE(yylex,
	  extern int,
	  (void));

extern int yynerrs;
extern int yylineno;
extern char parse_error[];
extern char *parse_filename;
extern char *parse_directory;
extern proto_t protos_seen;
extern sockaddr_un parse_addr;

PROTOTYPE(yyparse,
	  extern int,
	  (void));
PROTOTYPE(parse_keyword,
	  extern int,
	  (char *,
	   u_int));			/* Lookup a token given a keyword */
PROTOTYPE(parse_keyword_lookup,
	  extern const char *,
	  (int));			/* Lookup a keyword given a token */
PROTOTYPE(parse_parse,
	  extern int,
	  (const char *));		/* Parse the config file */
PROTOTYPE(parse_strdump,
	  char *,
	  (char *));			/* Return a pointer to a duplicate string */
PROTOTYPE(parse_where,
	  char *,
	  (void));			/* Return pointer to a string  giving current file and line */
PROTOTYPE(parse_limit_check,
	  int,
	  (const char *type,
	   u_int value,
	   u_int lower,
	   u_int upper));		/* Limit check an integer */
PROTOTYPE(parse_addr_hostname,
	  sockaddr_un *,
	  (char *,
	   char *));			/* Lookup a string as a host name */
PROTOTYPE(parse_addr_netname,
	  sockaddr_un *,
	  (char *,
	   char *));			/* Lookup a string as a network name */
PROTOTYPE(parse_adv_append,
	  int,
	  (adv_entry **,
	   adv_entry *));		/* Append one advlist to another */
PROTOTYPE(parse_gw_flag,
	  int,
	  (adv_entry *,
	   proto_t,
	   flag_t));			/* Set flag in gw_entry for each element in list */
PROTOTYPE(parse_new_state,
	  int,
	  (int));			/* Switch to a new state if it is a logical progression */
								/* from the current state */
PROTOTYPE(parse_metric_check,
	  int,
	  (proto_t,
	   pmet_t *));	/* Verify a specified metric */
PROTOTYPE(parse_adv_propagate_metric,
	  adv_entry *,
	  (adv_entry *,
	   proto_t,
	   pmet_t *,
	   adv_entry *));			/* Set metric in list for elements without metrics */
PROTOTYPE(parse_adv_propagate_preference,
	  adv_entry *,
	  (adv_entry *,
	   proto_t,
	   pmet_t *,
	   adv_entry *));			/* Set preference in list for elements without metrics */
PROTOTYPE(parse_adv_propagate_config,
	  adv_entry *,
	  (adv_entry *,
	   config_list *,
	   proto_t));
PROTOTYPE(parse_adv_preference,
	  void,
	  (adv_entry *,
	   proto_t,
	   pref_t));			/* Set preference in list for elements without preference */
PROTOTYPE(parse_adv_as,
	  int,
	  (adv_entry **,
	   adv_entry *));		/* Append this list to the list for the specified exterior protocol */
PROTOTYPE(parse_args,
	  int,
	  (int,
	   char **));


/*
 * %(Copyright)
 */
