/*
 *  $Id: krt_lladdr_sunos4.c,v 1.5.2.2 1995/01/23 12:40:14 jch Exp $
 */

/* %(Copyright.header) */

#define	INCLUDE_TIME
#define	INCLUDE_IOCTL
#define	INCLUDE_ETHER
#define	INCLUDE_FILE
#define	INCLUDE_IF
#include "include.h"
#include "krt.h"
#include "krt_var.h"
#include <net/nit_if.h>

sockaddr_un *
krt_lladdr __PF1(ifr, struct ifreq *)
{
    static int s_nit = -2;
    sockaddr_un *addr = (sockaddr_un *) 0;

    switch (s_nit) {
    case -1:
	/* Previous open failed */
	break;

    case -2:
	/* Try to open it */
	NON_INTR(s_nit, open("/dev/nit", O_RDONLY));
	if (s_nit < 0) {
	    if (!BIT_MATCH(task_state, TASKS_TEST|TASKS_NODUMP)) {
		trace_only_tp(krt_task,
			      0,
			      ("krt_lladdr: open(\"/dev/nit\"): %m"));
	    }
	    break;
	}
	(void) task_floating_socket(krt_task, s_nit, "/dev/nit");
	/* Fall through */

    default:
	/* Bind the NIT socket to this interface */
	bzero ((caddr_t) &ifr->ifr_ifru, sizeof (ifr->ifr_ifru));
	if (task_ioctl(s_nit,
		       (u_long) NIOCBIND,
		       (caddr_t) ifr, 
		       sizeof (ifr)) < 0) {
	    int rc;
	    
	    trace_only_tp(krt_task,
			  0,
			  ("krt_lladdr: NIOCBIND could not bind to interface %.*s: %m",
			   IFNAMSIZ, ifr->ifr_name));

	    /* Close the socket */
	    NON_INTR(rc, close(s_nit));
	    if (rc < 0) {
		trace_only_tp(krt_task,
			      0,
			      ("krt_lladdr: close(\"/dev/nit\"): %m"));
	    }
	    s_nit = -1;
	    break;
	}

	bzero ((caddr_t) &ifr->ifr_ifru, sizeof (ifr->ifr_ifru));
	if (task_ioctl(s_nit,
		       (u_long) SIOCGIFADDR,
		       (caddr_t) ifr,
		       sizeof (ifr)) < 0) {
	    switch (errno) {
	    case EINVAL:
	    case EOPNOTSUPP:
		break;

	    default:
		trace_only_tp(krt_task,
			      0,
			      ("krt_lladdr: could not get link layer address for interface %.*s: %m",
			       IFNAMSIZ, ifr->ifr_name));
	    }
	    break;
	}

	addr = sockbuild_ll(LL_8022,
			    (byte *) ifr->ifr_addr.sa_data,
			    sizeof (struct ether_addr));
    }

    return addr;
}
