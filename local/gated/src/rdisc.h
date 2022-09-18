/*
 *  $Id: rdisc.h,v 1.2.2.1 1995/01/10 13:35:37 jch Exp $
 */

/* %(Copyright.header) */

#define	RDISC_DOING_OFF		0
#define	RDISC_DOING_SERVER	1
#define	RDISC_DOING_CLIENT	2

/* Server stuff */
#define RDISC_MAX_INITIAL_ADVERT_INTERVAL 	16	/* seconds */
#define RDISC_MAX_INITIAL_ADVERTISEMENTS	3	/* transmissions */
#define RDISC_MAX_RESPONSE_DELAY		2	/* seconds */
#define RDISC_MAX_ADINTERVAL_DEFAULT 		600

#define RDISC_CONFIG_MAXADVINT  1
#define RDISC_CONFIG_MINADVINT  2
#define RDISC_CONFIG_LIFETIME   3
#define RDISC_CONFIG_MAX        4

#define RDISC_CONFIG_IFA_IGNORE     1
#define RDISC_CONFIG_IFA_BROADCAST  2
#define RDISC_CONFIG_IFA_PREFERENCE 3
#define RDISC_IFA_CONFIG_MAX        4

/* Client stuff */
#define	RDISC_MAX_SOLICITATION_DELAY	1	/* seconds */
#define	RDISC_SOLICITATION_INTERVAL	3	/* interval */
#define	RDISC_MAX_SOLICITATIONS		3

#define	RDISC_CONFIG_CLIENT_DISABLE	1
#define	RDISC_CONFIG_CLIENT_BROADCAST	2
#define	RDISC_CONFIG_CLIENT_QUIET	3
#define	RDISC_CONFIG_CLIENT_MAX		4


#define	RDISC_LIFETIME_MIN	3
#define	RDISC_LIFETIME_MAX	9000

#define RDISC_LIMIT_MAXADVINT   4, 1800
#define RDISC_LIMIT_MINADVINT   3, 1800
#define RDISC_LIMIT_LIFETIME    RDISC_LIFETIME_MIN, RDISC_LIFETIME_MAX
#define RDISC_LIMIT_PREFERENCE  (u_int) 0x80000000, 0x7fffffff

#define RDISC_PREFERENCE_INELIGIBLE     0x80000000
#define	RDISC_PREFERENCE_DEFAULT	0

extern int doing_rdisc;
extern const bits rdisc_trace_types[];
extern trace *rdisc_trace_options;
extern adv_entry *rdisc_server_address_policy;
extern adv_entry *rdisc_interface_policy;
extern pref_t rdisc_client_preference;

PROTOTYPE(rdisc_init,
	  extern void,
	  (void));

PROTOTYPE(rdisc_var_init,
	  extern void,
	  (void));
	  
/*
 * %(Copyright)
 */
