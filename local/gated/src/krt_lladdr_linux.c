/*
 *  $Id: krt_lladdr_linux.c,v 1.3.2.3 1995/05/01 16:24:52 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_KVM
#define	INCLUDE_CTYPE
#define	INCLUDE_ETHER
#define	INCLUDE_IF
#include "include.h"
#include "krt.h"
#include "krt_var.h"


sockaddr_un *
krt_lladdr __PF1(ifr, struct ifreq *)
{

    if (task_ioctl(krt_task->task_socket, 
		   (u_long) SIOCGIFHWADDR, 
		   (caddr_t) ifr, 
		   sizeof (*ifr)) < 0) {
	trace_log_tp(krt_task,                                         
		     0,                                          
		     LOG_ERR,                                    
		     ("krt_lladdr_linux: %s: ioctl SIOCGIFHWADDR: %m", 
		      ifr->ifr_name));                           
	return (sockaddr_un *) 0;
    }                                                                   

    return sockbuild_ll(LL_8022, (byte *) ifr->ifr_hwaddr.sa_data, IFHWADDRLEN);
}


/*
 * %(Copyright)
 */
