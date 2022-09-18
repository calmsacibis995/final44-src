/*
 *  $Id: sysconf.c,v 1.9 1992/10/08 19:59:11 jch Exp $
 */

/* %(Copyright.header) */


#include "include.h"

/*
 *	Emulation of sysconf() systems that define _SC_OPEN_MAX but
 *	don't have sysconf().  Keith?
 */

#ifdef	_SC_OPEN_MAX
#if	__GNUC__ >= 2
PROTOTYPE(sysconf,
	  long,
	  (int));
#endif	/* __GNUC__ >= 2*/
long
sysconf(type)
int type;
{
    long ret = 0;
    
    switch (type) {
    case _SC_OPEN_MAX:
	ret = getdtablesize();
	break;

#ifdef	_SC_PAGE_SIZE
    case _SC_PAGE_SIZE:
	ret = getpagetsize();
	break;
#endif	/* _SC_PAGE_SIZE */

#ifdef	POSIX_VERSION
    case _SC_VERSION:
	ret = POSIX_VERSION;
	break;
#endif	/* POSIX_VERSION */

    default:
	abort();
    }

    return ret;
}
#endif	/* _SC_OPEN_MAX */


/*
 * %(Copyright)
 */
