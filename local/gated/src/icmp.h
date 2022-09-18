/*
 * $Id: icmp.h,v 1.10.2.1 1994/09/08 16:09:59 jch Exp $
 */

/* %(Copyright.header) */


#define	ICMP_PACKET_MAX	2048	/* Maximum ICMP packet size we expect */

extern task *icmp_task;
extern trace *icmp_trace_options;
extern const bits icmp_trace_types[];
#ifdef	ICMP_MAXTYPE
extern _PROTOTYPE(icmp_methods[ICMP_MAXTYPE],
		   void,
		   (task *,
		    sockaddr_un *,
		    sockaddr_un *,
		    struct icmp *,
		    size_t));
#endif	/* ICMP_MAXTYPE */

/* Tracing */

#define	TR_ICMP_DETAIL_REDIRECT	TR_DETAIL_1
#define	TR_ICMP_DETAIL_ROUTER	TR_DETAIL_2
#define	TR_ICMP_DETAIL_INFO	TR_DETAIL_3
#define	TR_ICMP_DETAIL_ERROR	TR_DETAIL_4

#define	TR_ICMP_INDEX_PACKETS	0
#define	TR_ICMP_INDEX_REDIRECT	1
#define	TR_ICMP_INDEX_ROUTER	2
#define	TR_ICMP_INDEX_INFO	3
#define	TR_ICMP_INDEX_ERROR	4

   
PROTOTYPE(icmp_var_init,
	  extern void,
	  (void));
PROTOTYPE(icmp_init,
	  extern void,
	  (void));
#if	defined(ICMP_SEND) && defined(ICMP_MAXTYPE)
PROTOTYPE(icmp_send,
	  extern int,
	  (struct icmp *,
	   size_t,
	   sockaddr_un *,
	   if_addr *,
	   flag_t));
#endif	/* defined(ICMP_SEND) && defined(ICMP_MAXTYPE) */


/*
 * %(Copyright)
 */
