/*
 *  $Id: h_errno.c,v 1.9 1993/03/22 02:41:43 jch Exp $
 */

/* %(Copyright.header) */

#include <netdb.h>

/*
 *	Fake h_errno for systems that define it in netdb.h but do not provide it.
 */

#ifndef	HOST_NOT_FOUND
#define	HOST_NOT_FOUND	1
#endif	/* HOST_NOT_FOUND */

int h_errno = HOST_NOT_FOUND;


/*
 * %(Copyright)
 */
