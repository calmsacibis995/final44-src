/*
 * $Id: krt.h,v 1.20.2.4 1995/04/17 17:18:32 jch Exp $
 */

/* %(Copyright.header) */


/* Kernel interface definitions */

extern char *krt_version_kernel;
extern gw_entry *krt_gw_list;
extern task *krt_task;
extern task_timer *krt_timer_ifcheck;
extern const bits kernel_trace_types[];
extern trace *kernel_trace_options;
extern u_long krt_n_routes;		/* Number of routes currently in the kernel */

#ifdef	KRT_IFREAD_KINFO
/* Scan less frequently because we should see notification */
#define	KRT_T_IFCHECK	(time_t) 60
#else	/* KRT_IFREAD_KINFO */
/* Scan often so we notice changes quickly */
#define	KRT_T_IFCHECK	(time_t) 15
#endif	/* KRT_IFREAD_KINFO */
#define	KRT_T_EXPIRE_DEFAULT	(time_t) 180

/* For parser */
#define	KRT_LIMIT_SCANTIMER	KRT_T_IFCHECK, 3600
#define	KRT_LIMIT_EXPIRE	0,900

extern time_t krt_t_expire;

/**/

#define	KRT_COUNT_UNLIMITED	((u_long) -1)

/*
 * Routes to install in flash routine
 */
#define	KRT_FLASH_INTERFACE	0	/* Only interface routes in flash */
#define	KRT_FLASH_INTERNAL	1	/* Interface and internal routes */
#define	KRT_FLASH_ALL		2	/* All routes */

#define	KRT_FLASH_DEFAULT	KRT_FLASH_INTERFACE

/*
 * Number of routes to install in the flash routine
 */
#define	KRT_MIN_FLASH_INSTALL_COUNT	0
#define	KRT_MAX_FLASH_INSTALL_COUNT	KRT_COUNT_UNLIMITED
#define	KRT_LIMIT_FLASH		KRT_MIN_FLASH_INSTALL_COUNT, (u_int) KRT_MAX_FLASH_INSTALL_COUNT
#define	KRT_DEF_FLASH_INSTALL_COUNT	20

/*
 * Priority for the background job
 */
#define	KRT_INSTALL_PRIO_LOW	0	/* Low priority */
#define	KRT_INSTALL_PRIO_FLASH	1	/* Flash priority */
#define	KRT_INSTALL_PRIO_HIGH	2	/* High priority */

#define	KRT_INSTALL_PRIO_DEFAULT	KRT_INSTALL_PRIO_LOW

/*
 * Number of routes to install at a shot in background
 */
#define	KRT_MIN_INSTALL_COUNT	1
#define	KRT_MAX_INSTALL_COUNT	KRT_COUNT_UNLIMITED
#define	KRT_LIMIT_INSTALL	KRT_MIN_INSTALL_COUNT, (u_int) KRT_MAX_INSTALL_COUNT
#define	KRT_DEF_INSTALL_COUNT	120

extern int krt_flash_routes;	
extern u_long krt_flash_install_count;
extern int krt_install_priority;
extern u_long krt_install_count;

#define	KRT_LIMIT_ROUTES	0, (u_int) KRT_COUNT_UNLIMITED

extern u_long krt_limit_routes;	/* Maximum number of routes allowed in kernel */

/*
 * Krt options
 */
#define	KRT_OPT_NOCHANGE	BIT(0x01)	/* Always do delete/add's */
#define	KRT_OPT_NOFLUSH		BIT(0x02)	/* Don't flush at termination */
#define	KRT_OPT_NOINSTALL	BIT(0x04)	/* Don't install routes in kernel */

extern flag_t krt_options;

/**/

/* Kernel routing table interface */

typedef struct _krt_parms {
    proto_t krtp_protocol;
    flag_t krtp_state;
#ifdef	IP_MULTICAST_ROUTING
    pref_t krtp_preference;
    metric_t krtp_metric;
#endif	/* IP_MULTICAST_ROUTING */
    int krtp_n_gw;
    sockaddr_un **krtp_routers;
#define	krtp_router	krtp_routers[0]
    if_addr **krtp_ifaps;
#define	krtp_ifap	krtp_ifaps[0]
} krt_parms;


/* Tracing */

#define	TR_KRT_INDEX_PACKETS	0	/* All packets */
#define	TR_KRT_INDEX_ROUTES	1	/* Routing table changes */
#define	TR_KRT_INDEX_REDIRECT	2	/* Redirect packets we receive */
#define	TR_KRT_INDEX_INTERFACE	3	/* Interface status changes */
#define	TR_KRT_INDEX_OTHER	4	/* Anything else */

#define	TR_KRT_PACKET_ROUTE	 	TR_DETAIL_1
#define	TR_KRT_PACKET_REDIRECT		TR_DETAIL_2
#define	TR_KRT_PACKET_INTERFACE		TR_DETAIL_3
#define	TR_KRT_PACKET_OTHER		TR_DETAIL_4

#define	TR_KRT_INFO		TR_USER_1
#define	TR_KRT_REQUEST		TR_USER_2
#define	TR_KRT_REMNANTS		TR_USER_3
#define	TR_KRT_SYMBOLS		TR_USER_4
#define	TR_KRT_IFLIST		TR_USER_5

/**/

PROTOTYPE(krt_family_init,
	  extern void,
	  (void));
PROTOTYPE(krt_init,
	  extern void,
	  (void));
PROTOTYPE(krt_var_init,
	  extern void,
	  (void));
PROTOTYPE(krt_flash,
	  extern void,
	  (rt_list *rtl));
PROTOTYPE(krt_delete_dst,
	  extern void,
	  (task *,
	   sockaddr_un *,
	   sockaddr_un *,
	   proto_t,
	   flag_t,
	   int,
	   sockaddr_un **,
	   if_addr **));
PROTOTYPE(krt_kernel_rt,
	  extern krt_parms *,
	  (rt_head *));
PROTOTYPE(krt_state_to_flags,
	  extern flag_t,
	  (flag_t));
PROTOTYPE(krt_ifcheck,
	  extern void,
	  (void));
#ifdef	IP_MULTICAST
PROTOTYPE(krt_multicast_add,
	  extern void,
	  (sockaddr_un *));
PROTOTYPE(krt_multicast_delete,
	  extern void,
	  (sockaddr_un *));
#endif	/* IP_MULTICAST */

/*
 * %(Copyright)
 */
