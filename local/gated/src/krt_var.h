/*
 * $Id: krt_var.h,v 1.13.2.6 1995/05/08 17:02:51 jch Exp $
 */

/* %(Copyright.header) */


/* Kernel interface definitions */

extern const bits krt_flag_bits[];	/* Route flag bits */
extern rt_entry krt_rt;			/* For faking route changes */
extern gw_entry *krt_gwp;
extern gw_entry *krt_gwp_remnant;

#define        KRT_PACKET_MAX  1024            /* Maximum routing socket packet we expect */

/**/

#if	defined(INCLUDE_KVM) && !defined(KVM_TYPE_NONE)
/* KVM stuff */
#ifdef	KVM_TYPE_RENO
#define	KVM_OPENFILES(nl, core, swap, flags, buf)	((kvm_openfiles(nl, core, swap) < 0) ? NULL : TRUE)
#define	KVM_OPEN_DEFINE(buf)	
#define	KVM_OPEN_ERROR(buf)	kvm_geterr()
#define	KVM_GETERR(kd, string)		kvm_geterr()
#endif	/* KVM_TYPE_RENO */

#ifdef	KVM_TYPE_BSD44
#define	KVM_OPENFILES(nl, core, swap, flags, buf)	kvm_openfiles(nl, core, swap, flags, buf)
#define	KVM_OPEN_DEFINE(buf)	char buf[LINE_MAX]
#define	KVM_OPEN_ERROR(buf)	buf
#define	KVM_WITH_KD
#define	KVM_GETERR(kd, string)		kvm_geterr(kd)
#ifndef	INCLUDE_KVM_WORKS
#define	INCLUDE_KVM_WORKS
#endif
#endif	/* KVM_TYPE_BSD44 */

#ifdef	KVM_TYPE_SUNOS4
#define	KVM_OPENFILES(nl, core, swap, flags, buf)	kvm_open(nl, core, swap, flags, "kvm")
#define	KVM_OPEN_DEFINE(buf)
#define	KVM_OPEN_ERROR(buf)	"kvm_open error"
#define	KVM_WITH_KD
#define	KVM_GETERR(kd, string)		string
#ifndef	INCLUDE_KVM_WORKS
#define	INCLUDE_KVM_WORKS
#endif
#endif	/* KVM_OPEN_SUNOS */

#ifdef	KVM_TYPE_OTHER
#define	KVM_OPENFILES(nl, core, swap, flags, buf)	kvm_openfiles(nl, core, swap, flags, buf)
#define	KVM_OPEN_DEFINE(buf)	char buf[LINE_MAX]
#define	KVM_OPEN_ERROR(buf)	buf
#define	KVM_WITH_KD
#define	KVM_GETERR(kd, string)		kvm_geterr(kd)
typedef struct __kvm kvm_t;

PROTOTYPE(kvm_openfiles,
	  extern kvm_t *,
	  (char *,
	   char *,
	   char *,
	   int,
	   char *));
PROTOTYPE(kvm_read,
	  extern int,
	  (kvm_t *,
	   u_long,
	   void_t,
	   size_t));
PROTOTYPE(kvm_write,
	  extern int,
	  (kvm_t *,
	   u_long,
	   void_t,
	   size_t));
PROTOTYPE(kvm_close,
	  extern int,
	  (kvm_t *));
PROTOTYPE(kvm_geterr,
	  extern char *,
	  (kvm_t *));
#ifdef	INCLUDE_NLIST
PROTOTYPE(kvm_nlist,
	  extern int,
	  (kvm_t *,
	   NLIST_T *,
	   size_t));
#endif	/* INCLUDE_NLIST */
#endif	/* KVM_TYPE_OTHER */

#ifdef	INCLUDE_KVM_WORKS
#include <kvm.h>
#endif

#ifdef	KVM_WITH_KD
extern kvm_t	*kd;

#ifdef	KVM_TYPE_OTHER

#define	KVM_NLIST(kd, nl, sz)		kvm_nlist(kd, nl, sz)
#else	/* KVM_TYPE_OTHER */
#define	KVM_NLIST(kd, nl, sz)		kvm_nlist(kd, nl)
#endif	/* KVM_TYPE_OTHER */
#define	KVM_READ(kd, addr, buf, nbytes)	kvm_read(kd, (u_long) (addr), (void_t) (buf), nbytes)
#define	KVM_CLOSE(kd)			kvm_close(kd)

#else	/* KVM_WITH_KD */
extern int kd;

#define	KVM_NLIST(kd, nl, sz)		kvm_nlist(nl)
#define	KVM_READ(kd, addr, buf, nbytes)	kvm_read((u_long) (addr), (void_t) (buf), nbytes)
#define	KVM_CLOSE(kd)			kvm_close()
#endif	/* KVM_WITH_KD */

#endif	/* INCLUDE_KVM && !KVM_TYPE_NONE */

/**/
/* Return codes from krt_addrcheck */

#define	KRT_ADDR_OK	1	/* Address is OK */
#define	KRT_ADDR_IGNORE	0	/* Ignore this address */
#define	KRT_ADDR_BOGUS	-1	/* Bogus, delete it */
#define	KRT_ADDR_MC	-2	/* Multicast default specification */

/**/
/* Routing table scanning routines */

#ifdef	KRT_RTREAD_KMEM

extern u_long krt_rthashsize;
extern u_long krt_rthash[2];
#define	KRT_RTHOST	0
#define	KRT_RTNET	1
#endif	/* KRT_RTREAD_KMEM */

#ifdef	KRT_RTREAD_RADIX
extern u_long krt_radix_head;
#endif	/* KRT_RTREAD_RADIX */

/**/
/* Routing table manipulation routines */

#ifdef	KRT_RT_IOCTL
#define	RTM_ADD		((u_long) SIOCADDRT)
#define	RTM_DELETE	((u_long) SIOCDELRT)
#endif	/* KRT_RT_IOCTL */

/**/
/* Symbols */

PROTOTYPE(krt_symbols,
	  extern int,
	  (task *));
#ifdef	SIOCGNETOPT
PROTOTYPE(krt_netopts,
	  extern int,
	  (task *));
#endif	/* SIOCGNETOPT */

/**/

/* Routing socket */

PROTOTYPE(krt_recv,
	  extern void,
	  (task *));

/**/

/* LL addr */

#ifdef	KRT_LLADDR_NONE
#define	krt_lladdr(ifr)	((sockaddr_un *) 0)
#else	/* KRT_LLADDR_NONE */
#ifdef	KRT_LLADDR_KMEM
extern u_long krt_ifnet;
#endif

#ifdef	INCLUDE_IF
PROTOTYPE(krt_lladdr,
	  extern sockaddr_un *,
	  (struct ifreq *));
#endif	/* INCLUDE_IF */
#endif	/* KRT_LLADDR_NONE */

/**/

/* Routing socket and kerninfo support */

#if	defined(KRT_RT_SOCK) && defined(INCLUDE_ROUTE)
/*
 *	Support code for use with the getkerninfo() call and the routing socket.
 */

#ifdef	RTM_IFINFO
#define	RTM_MAX		(RTM_IFINFO + 1)
#else	/* RTM_IFINFO */
#define	RTM_MAX		(RTM_RESOLVE + 1)
#endif	/* RTM_IFINFO */

#ifndef	RTAX_DST
/*
 * Index offsets for sockaddr array for alternate internal encoding.
 */
#define RTAX_DST	0	/* destination sockaddr present */
#define RTAX_GATEWAY	1	/* gateway sockaddr present */
#define RTAX_NETMASK	2	/* netmask sockaddr present */
#define RTAX_GENMASK	3	/* cloning mask sockaddr present */
#define RTAX_IFP	4	/* interface name sockaddr present */
#define RTAX_IFA	5	/* interface addr sockaddr present */
#define RTAX_AUTHOR	6	/* sockaddr for author of redirect */
#define	RTAX_BRD	7	/* broadcast address */
#define	RTAX_DOWNSTREAM	8	/* multicast downstream intf */
#define RTAX_MAX	9	/* size of array to allocate */
#endif	/* RTAX_DST */

typedef struct {
	flag_t rti_addrs;
	sockaddr_un *rti_info[RTAX_MAX];
} krt_addrinfo;

#define	RTAX_LIST(i)	for (i = 0; i < RTAX_MAX; i++)
#define	RTAX_LIST_END(i)

#define	RTM_ADDR(ap)	ap = (struct sockaddr *) \
    ((caddr_t) ap + (ap->sa_len ? ROUNDUP(ap->sa_len, sizeof (u_long)) : sizeof(u_long)))


extern const bits rtm_type_bits[];


PROTOTYPE(krt_xaddrs,
	  extern krt_addrinfo *,
	  (register struct rt_msghdr *,
	   size_t));
PROTOTYPE(krt_trace_msg,
	  void,
	  (task *,
	   const char *,
	   struct rt_msghdr *,
	   size_t,
	   krt_addrinfo *,
	   int,
	   int));
#if	defined(KRT_IFREAD_KINFO) && defined(INCLUDE_IF)
PROTOTYPE(krt_ifaddr,
	  extern void,
	  (task *,
	   struct ifa_msghdr *,
	   krt_addrinfo *,
	   if_link *));
#endif	/* defined(KRT_IFREAD_KINFO) && defined(INCLUDE_IF) */
#ifdef	KRT_RTREAD_KINFO
PROTOTYPE(krt_rtaddrs,
	  int,
	  (krt_addrinfo *,
	   rt_parms *,
	   sockaddr_un **,
	   flag_t));
#endif	/* KRT_RTREAD_KINFO */
#endif	/* KRT_RT_SOCK && INCLUDE_ROUTE */

/**/

/* Routing table interface */

#define	KRT_OP_SUCCESS	0	/* operation successful (or unrecoverable error) */
#define	KRT_OP_NOCANDO	KRT_OP_SUCCESS
#define	KRT_OP_DEFER	1	/* operation failed (ENETUNREACH), defer this install for later */
#define	KRT_OP_FULL	2	/* operation failed (table full), defer all installs for later */
#define	KRT_OP_BLOCKED	3	/* can't install this route or any more now, defer all until krt_unblock() */
#define	KRT_OP_PARTIAL	4	/* bit set when route delete succeeded, route add failed */
#define	KRT_OP_PARTIAL_DEFER	(KRT_OP_DEFER|KRT_OP_PARTIAL)
#define	KRT_OP_PARTIAL_FULL	(KRT_OP_FULL|KRT_OP_PARTIAL)
#define	KRT_OP_PARTIAL_BLOCKED	(KRT_OP_BLOCKED|KRT_OP_PARTIAL)

PROTOTYPE(krt_change,
	  extern int,
	  (task *,
	   sockaddr_un *,
	   sockaddr_un *,
	   krt_parms *,
	   krt_parms *));
PROTOTYPE(krt_rth_reset,
	  extern void,
	  (rt_head *,
	   flag_t,
	   int,
	   sockaddr_un **,
	   if_addr **));
PROTOTYPE(krt_dst_reset,
	  extern void,
	  (sockaddr_un *,
	   sockaddr_un *,
	   flag_t,
	   int,
	   sockaddr_un **,
	   if_addr **));
PROTOTYPE(krt_change_start,
	  extern int,
	  (task *));
PROTOTYPE(krt_change_end,
	  extern int,
	  (task *));
PROTOTYPE(krt_unblock,
	  extern void,
	  (void));
PROTOTYPE(krt_make_router,
	  extern sockaddr_un *,
	  (int,
	   flag_t));


/* Options supported by this kernel */

extern flag_t krt_rt_support;

#define	KRTS_REJECT	BIT(0x01)	/* Supports reject routes */
#define	KRTS_BLACKHOLE	BIT(0x02)	/* Supports blackhole routes */
#define	KRTS_VAR_MASK	BIT(0x04)	/* Supports variable mask routes */
#define	KRTS_HOST	BIT(0x08)	/* Supports host routes */
#define	KRTS_MULTIPATH	BIT(0x10)	/* Supports multipath routes */

/**/

/* General prototypes */


PROTOTYPE(krt_trace,
	  void,
	  (task *,
	   const char *,
	   const char *,
	   sockaddr_un *,
	   sockaddr_un *,
	   sockaddr_un *,
	   flag_t,
	   const char *,
	   int));
#ifndef	KRT_RTREAD_KINFO
PROTOTYPE(krt_rtread_add,
	  extern void,
	  (task *,
	   rt_parms *,
	   flag_t,
	   int,
	   const char *));
#endif	/* KRT_RTREAD_KINFO */
#if	defined(IP_MULTICAST) && !defined(KRT_IPMULTI_RTSOCK)
PROTOTYPE(krt_multicast_install,
	  extern int,
	  (sockaddr_un *,
	   sockaddr_un *));
#ifdef	RTM_CHANGE
PROTOTYPE(krt_multicast_change,
	  extern void,
	  (int,
	   rt_parms *));
#endif	/* RTM_CHANGE */
PROTOTYPE(krt_multicast_dump,
	  extern void,
	  (task *,
	   FILE *));
#endif	/* defined(IP_MULTICAST) && !defined(KRT_IPMULTI_RTSOCK) */
#if defined(INCLUDE_ROUTE) && defined(KRT_RT_SOCK) && defined(KRT_IPMULTI_RTSOCK)
PROTOTYPE(krt_action,
	  extern int,
	  (task *, struct rt_msghdr *));
#endif	/* KRT_RT_SOCK && KRT_IPMULTI_RTSOCK */
#ifdef	IFT_OTHER
PROTOTYPE(krt_type_to_ll,
	  extern int,
	  (int));
#endif	/* IFT_OTHER */
PROTOTYPE(krt_rtread,
	  extern int,
	  (task *));
PROTOTYPE(krt_rtadd,
	  extern const char *,
	  (rt_parms *,
	   flag_t));
PROTOTYPE(krt_delq_add,
	  extern void,
	  (rt_parms *));
PROTOTYPE(krt_addrcheck,
	  extern int,
	  (rt_parms *));
PROTOTYPE(krt_if_flags,
	  extern flag_t,
	  (int));
PROTOTYPE(krt_flags_to_state,
	  extern flag_t,
	  (flag_t));
PROTOTYPE(krt_age_create,
	  extern void,
	  (void));
PROTOTYPE(krt_ifread,
	  extern int,
	  (flag_t));

/*
 * %(Copyright)
 */
