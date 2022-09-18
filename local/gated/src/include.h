/*
 * $Id: include.h,v 1.34.2.6 1994/11/15 02:38:26 jch Exp $
 */

/* %(Copyright.header) */


#ifndef	_GATED_INCLUDE_H
#define	_GATED_INCLUDE_H

#include "defines.h"

#if	defined(_IBMR2) && !defined(_BSD)
#define	_BSD	1
#endif

#include <sys/param.h>			/* Was types */
#ifdef	INCLUDE_TYPES
#include <sys/types.h>
#endif	/* INCLUDE_TYPES */
#ifdef	INCLUDE_BSDTYPES
#include <sys/bsdtypes.h>
#endif	/* INCLUDE_TYPES */
#ifdef	INCLUDE_STREAMIO
#include <sys/stream.h>
#endif	/* INCLUDE_STREAMIO */
#include <sys/uio.h>

#include <sys/socket.h>
#ifdef	UNDEF_RCVBUF
#undef	SO_RCVBUF
#endif

#include <stdio.h>
#if	!defined(NO_STDLIB_H)
#include <stdlib.h>
#endif
#if	!defined(NO_STDDEF_H)
#include <stddef.h>
#endif
#ifdef	MALLOC_OK
#ifdef	INCLUDE_MALLOC
#include <malloc.h>
#endif
#endif
#include <netdb.h>
#include <sys/errno.h>
#ifdef	SYSV
#undef ENAMETOOLONG
#undef ENOTEMPTY
#include <net/errno.h>
#endif
#ifdef	INCLUDE_STRING
#include <string.h>
#else
#include <strings.h>
#endif

#ifdef	INCLUDE_TIME
#ifndef	NO_INCLUDE_TIME
#include <time.h>
#endif
#include <sys/time.h>
#endif

#ifndef	NO_MBUF_H
#include <sys/mbuf.h>
#endif	/* NO_MBUF_H */
#ifdef	INCLUDE_IF
#include <net/if.h>
#endif	/* INCLUDE_IF */

#ifdef	PROTO_UNIX
#include <sys/un.h>
#endif

#if	defined(PROTO_INET)
#include <netinet/in.h>
#ifdef	linux
#include <bsd/bsd.h>
#include <linux/in_systm.h>       
#include <bsd/netinet/ip_var.h>   
#include <bsd/netinet/ip.h>       
#else /* linux */
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#endif	/* linux */
#if	!defined(HPUX7_X) && !defined(linux)
#include <arpa/inet.h>
#endif	/* !defined(HPUX7_X) && !defined(linux) */
#ifdef	INCLUDE_ETHER
#if	defined(AIX) && !defined(_IBMR2)
#include <sys/if_ieee802.h>
#else
#if	defined(_IBMR2) && !defined(IPPROTO_TP)	/* AIX 3.1 */
#include <netinet/in_netarp.h>
#else	/* defined(_IBMR2) && !defined(IPPROTO_TP) */
#ifdef	linux
#include <linux/if_ether.h>
#else	/* linux */
#include <netinet/if_ether.h>
#endif	/* linux */
#endif	/* defined(_IBMR2) && !defined(IPPROTO_TP) */
#endif	/* defined(AIX) && !define(_IBMR2) */
#endif	/* INCLUDE_ETHER */
#if	defined(INCLUDE_MROUTE) && defined(IFF_MULTICAST) && defined(PROTO_INET) && defined(IP_MULTICAST_ROUTING)
#include <netinet/ip_mroute.h>
#endif

#ifdef	INCLUDE_UDP
#ifdef	linux
#include <linux/udp.h>
#else	/* linux */
#include <netinet/udp.h>
#endif	/* linux */
#endif
#ifdef	INCLUDE_UDP_VAR
#include <netinet/udp_var.h>
#endif
#endif	/* PROTO_INET */

#if	defined(PROTO_ISO)
#include <netiso/iso.h>
#ifdef	INCLUDE_ISO_VAR
#include <netiso/iso_var.h>
#endif	/* INCLUDE_ISO_VAR */
#ifdef	INCLUDE_CLNP
#include <netiso/clnp.h>
#endif
#ifdef	INCLUDE_ESIS
#include <netiso/esis.h>
#endif
#ifdef	INCLUDE_SNPA
#include <netiso/iso_snpac.h>
#endif
#endif	/* PROTO_ISO */

#ifdef	INCLUDE_ROUTE
#include <net/route.h>
#undef	KERNEL
#endif

#ifdef	INCLUDE_PATHS
#include <paths.h>
#endif
#include "paths.h"

#ifdef	INCLUDE_WAIT
#include <sys/wait.h>
#ifdef	notdef
#include <sys/resource.h>
#endif
#endif

#include "config.h"

#ifdef	INCLUDE_UNISTD
#include <unistd.h>
#endif

#if	defined(INCLUDE_IF_DL) && defined(INCLUDE_IF)
#include <net/if_dl.h>
#endif	/* defined(INCLUDE_IF_DL) && defined(INCLUDE_IF) */
#if	defined(INCLUDE_IF_TYPES) && defined(SOCKADDR_DL) && !defined(IFT_ETHER)
#include <net/if_types.h>
#endif

#if	defined(AIX)
#include <sys/syslog.h>
#else				/* defined(AIX) */
#include <syslog.h>
#endif				/* defined(AIX) */

#ifdef	INCLUDE_SIGNAL
#include <signal.h>
#endif

#ifdef	INCLUDE_FILE
#include <sys/file.h>
#ifdef	INCLUDE_FCNTL
#include <sys/fcntl.h>
#endif
#endif

#if	!defined(NO_STAT) && defined(INCLUDE_STAT)
#include <sys/stat.h>
#endif

#ifdef	INCLUDE_IOCTL
#ifdef	INCLUDE_SOCKIO
#include <sys/sockio.h>
#endif	/* INCLUDE_SOCKIO */
#ifdef	INCLUDE_SIOCTL
#include <sys/sioctl.h>
#endif	/* INCLUDE_SIOCTL */
#ifdef	INCLUDE_STREAMIO
#include <sys/stropts.h>
#else	/* INCLUDE_STREAMIO */
#include <sys/ioctl.h>
#endif	/* INCLUDE_STREAMIO */
#endif	/* INCLUDE_IOCTL */

#ifdef	INCLUDE_NLIST
#include <nlist.h>
#endif

#ifdef	INCLUDE_KINFO
#ifdef	USE_SYSCTL
#include <sys/sysctl.h>
#else	/* USE_SYSCTL */
#if	(defined(KRT_RTREAD_KINFO) \
	 || defined(KRT_IFREAD_KINFO)) \
    && !defined(KINFO_RT_DUMP)
#include <sys/kinfo.h>
#endif
#endif	/* USE_SYSCTL */
#endif	/* INCLUDE_KINFO */

#if	defined(INCLUDE_NETOPT_IBMR2) && defined(_IBMR2) && !defined(SIOCGNETOPT)
#include <net/netopt.h>
#endif

#ifdef	INCLUDE_CTYPE
#include <ctype.h>
#endif

#if	defined(INCLUDE_DIRENT) && defined(HAVE_DIRENT)
#include <dirent.h>
#endif

#ifdef	STDARG
#ifndef	va_arg
#include <stdarg.h>
#endif	/* va_arg */
#else	/* STDARG */
#include <varargs.h>
#endif	/* STDARG */

#ifdef	INCLUDE_ISODE_SNMP
#include "objects.h"
#include "smux.h"
#undef	sprintf
#endif

#ifndef	MALLOC_OK
#undef	malloc
#define	malloc()	assert(FALSE)
#undef	calloc
#define	calloc()	assert(FALSE)
#undef	realloc
#define	realloc()	assert(FALSE)
#undef	free
#define	free()		assert(FALSE)
#endif	/* MALLOC_OK */

#include "defs.h"
#include "sockaddr.h"
#include "str.h"
#ifdef	PROTO_ASPATHS
#include "aspath.h"
#include "asmatch.h"
#endif
#include "policy.h"
#ifdef	INCLUDE_RT_VAR
#include "rt_var.h"
#endif
#include "rt_table.h"
#include "if.h"
#include "task.h"
#include "trace.h"
#ifndef	INCLUDE_UNISTD
#include "unix.h"
#endif

#endif	/* _GATED_INCLUDE_H */


/*
 * %(Copyright)
 */
